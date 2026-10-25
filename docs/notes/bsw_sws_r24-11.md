# Ghi chú: BSW theo SWS R24-11, khác biệt với classic-platform

Phạm vi: `firmware/common/bsw/*`, `firmware/common/ecum`, `firmware/common/stubs`, `firmware/{application,bootloader}/cfg`.
Plan gốc: `docs/plan/Plan-build-API-firmware-common.md`.

## 1. Quy ước chung của khung API

- Header đầy đủ: version, Service ID, mã lỗi DET/runtime, kiểu dữ liệu, prototype có doxygen ghi SWS ID và SRS ID.
- File `.c` chỉ có thân hàm trống: `(void)param;`, `/* TODO(<SRS>): SWS_xxx */`, và hàm có giá trị trả về thì trả mặc định an toàn (`E_NOT_OK`, `BUFREQ_E_NOT_OK`…).
- Không copy thân hàm của classic-platform (GPL). Prototype của repo khớp SWS thì giữ, không khớp thì sửa theo R24-11.
- `<MOD>_VENDOR_ID = 0xFFFF` là ID nội bộ dự án, không phải vendor đã đăng ký.
- `GetVersionInfo` là **hàm** (repo dùng macro).
- Các MainFunction được khai báo trong `stubs/SchM_<Mod>.h`, theo R24-11 "available via SchM_<Mod>.h".

## 2. Khác biệt cần nhớ khi import code classic-platform (C-01, T-02, X-04…)

| Module | Repo (4.0.3) | Khung (R24-11) |
|---|---|---|
| CanIf | `CanIf_ControllerModeType`, `CanIf_PduSetModeType`/`GetModeType` | `Can_ControllerStateType`, `CanIf_PduModeType` |
| CanTp | `RxIndication(PduInfoType*)`, `TxConfirmation(id)` | `const PduInfoType*`, `TxConfirmation(id, Std_ReturnType result)` |
| PduR / Dcm (TP) | `StartOfReception` không có `info`, `NotifResultType` | Có `const PduInfoType* info`, `Std_ReturnType result`, buffer `const` |
| CanSM | `ModeIndication(CanIf_ControllerModeType)`, callback trong `CanSM_Cbk.h` | `Can_ControllerStateType`, `CanSM_CanIf.h` |
| ComM | `ComM_UserHandleType` = **uint8**, `BusSM_ModeIndication(ComM_ModeType*)` | **uint16** (SWS_ComM_00670), mode truyền theo giá trị |
| Dem | `PreInit(ConfigPtr)`, `Init(void)`, Dcm↔Dem không có ClientId | `PreInit(void)`, `Init(ConfigPtr)`, **ClientId** + `Dem_SelectDTC`. Không áp dụng deviation OP-DEM-01 |
| Dcm callouts | `SetProgConditions(ptr)`, `WriteMemory` không có ErrorCode, `ProcessRequestDownload` không có MemoryIdentifier | Có `OpStatus`, `ErrorCode`, `MemoryIdentifier`; TransferExit tách record request/response |
| Det | `Det_Init(void)`, có `AddCbk` | `Det_Init(ConfigPtr)`, thêm `ReportRuntimeError`/`ReportTransientFault` |

## 3. Chỗ "lạ" ngay trong SWS

- `DCM_E_INVALID_VALUE` và `DCM_E_INTERFACE_RETURN_VALUE` **cùng bằng 0x02** (SWS_Dcm_00040). Giữ đúng như SWS.
- NRC 0x78 (response pending) **không** nằm trong `Dcm_NegativeResponseCodeType`; DSL tự sinh NRC này.
- `Dem_DTCOriginType` R24-11 không còn MIRROR. Chỉ có PRIMARY 0x0001, PERMANENT 0x0003, OBD_RELEVANT 0x0004.
- Mã lỗi DET của EcuM (SWS_EcuM_04032) "assigned by implementation", nên giá trị trong `EcuM.h` là giá trị dự án tự đặt.
- R24-11 chuyển `<User_RxIndication>`/`<User_TxConfirmation>` sang BSW General (SWS_CANIF_00011/00012 chỉ còn trong lịch sử). `CDD_CanTest` dùng dạng giống `CanTp_RxIndication`/`CanTp_TxConfirmation`.
- Mẫu `Xxx_Start` (SWS_Dcm_01203) ghi `ErrorCode` không có dấu `*`. Đó là lỗi đánh máy của SWS vì đây là tham số out; khung dùng `Dcm_NegativeResponseCodeType*`.

## 4. Thứ tự include Cfg

- `Det.h` và `CanSM.h` include `<Mod>_Cfg.h` **sau** typedef `ConfigType`, để file Cfg khai báo được `extern const <Mod>_ConfigType <Mod>_Config;`.
- Các module khác include `<Mod>_Types.h` bên trong `<Mod>_Cfg.h`.

## 5. Khác nhau giữa App và BL

- BL không có Dem (Bảng 2), nên trong `bootloader/cfg/CanSM_Cfg.h` đặt `CANSM_DEM_EVENT_BUS_OFF_ENABLED = STD_OFF`. Khi cài CanSM, mọi lời gọi `Dem_SetEventStatus` phải bọc bằng switch này.
- `Dcm_Externals.h` chỉ khai báo callout. App cài trong `src/app/Dcm_Callout_App.c`, BL cài trong `src/fbl/` (`Fbl_Download.c`, `Dcm_Callout_Bl.c`).
- Callout seed/key, DID, RID (`Xxx_GetSeed`, `Xxx_ReadData`, …) phụ thuộc cấu hình, nên khai báo cùng cấu hình Dcm (X-08, B-04).

## 6. Vì sao Dcm chưa chia Dsl/Dsd/Dsp

- DSL, DSD, DSP là cách chia **bên trong** module. SWS không có API cho chúng, nên khung chỉ có API ở `Dcm.h`, `Dcm_ComM.h`, `Dcm_Externals.h`.
- Doc quy định ở commit X-04: copy nguyên `Dcm_Dsl.c`, `Dcm_Dsd.c`, `Dcm_Dsp.c`, `Dcm_Internal.c` (giữ header GPL), rồi mới sửa ở X-05/X-06. Nếu tạo sẵn file rỗng cùng tên sẽ phá diff "bản gốc → bản sửa".
- Code của repo còn lỗi đã biết: `Dcm_Dsd.c:142` chưa chặn NRC 0x7E/0x7F với request functional (SWS_Dcm_00001). Lỗi này sửa ở X-06.
