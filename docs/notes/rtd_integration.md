# Ghi chú: Tích hợp NXP RTD 2.0.0 với BSW của dự án

Phạm vi: `firmware/common/mcal/`, `firmware/common/mcal_cfg/`, các header BSW mà RTD include.

## 1. Macro AR version giữ 4.7.0

- RTD 2.0.0 (AUTOSAR 4.7) kiểm tra version của header module khác và báo `#error` nếu lệch (khi **không** define `DISABLE_MCAL_INTERMODULE_ASR_CHECK`). Các header bị kiểm tra:
  - `Det.h` → `DET_AR_RELEASE_*`
  - `Dem.h` → `DEM_AR_RELEASE_*` (chỉ khi Mcu bật báo lỗi Dem)
  - `CanIf.h`, `CanIf_Can.h` → `CANIF_AR_RELEASE_*`, `CANIF_CAN_AR_RELEASE_*`
  - `EcuM.h`, `EcuM_Externals.h` → `ECUM_AR_RELEASE_*`, `ECUM_CBK_AR_RELEASE_*` (Gpt khi bật wakeup)
- Vì vậy mọi BSW đặt `AR_RELEASE 4.7.0`, còn **chữ ký API theo R24-11**. Không dùng `DISABLE_MCAL_INTERMODULE_ASR_CHECK`.

## 2. Header mà RTD cần từ BSW

| Header | Lý do | Ghi chú |
|---|---|---|
| `CanIf_Can.h` | `Can_43_FLEXCAN.c` và `_Ipw.c` include file này | R24-11 ghi callback CanIf "available via CanIf.h". `CanIf_Can.h` chỉ include lại `CanIf.h` và thêm macro `CANIF_CAN_*` |
| `EcuM_Externals.h` | `Gpt.h` include khi `GPT_WAKEUP_FUNCTIONALITY_API == STD_ON` | Cung cấp macro `ECUM_CBK_*` |
| `Dem.h` | `Mcu_Dem_Wrapper.h`, `Mcu_PBcfg.c` | Hiện `MCU_DISABLE_DEM_REPORT_ERROR_STATUS = STD_ON`. Nếu bật lên, cần event ID của Dem trong cấu hình Mcu |

Các callback tuỳ chọn mà RTD gọi đều được bao bởi switch cấu hình:
- `CanIf_ErrorNotification`, `CanIf_ControllerErrorStatePassive`: `CAN_43_FLEXCAN_ERROR_INTERRUPT_SUPPORT`.
- `CanIf_TriggerTransmit`: `CAN_43_FLEXCAN_TRIGGER_TRANSMIT_USED` (đang OFF).
- `CanIf_CurrentIcomConfiguration`: Icom (đang OFF).

`CanIf` đã khai báo hai callback lỗi phòng khi bật error interrupt.

## 3. SchM của RTD lấy từ gói Rte

- `firmware/common/mcal/Rte/{include,src}` copy từ plugin `Rte_TS_T40D2M20I0R0`, chỉ 7 module đang dùng: Can_43_FLEXCAN, Dio, Gpt, Mcu, Mem_43_INFLS, Platform, Port. File SchM này cài đặt exclusive area bằng `OsIf`.
- **Không copy** `Rte_Dem_Type.h`: file này định nghĩa `Dem_EventIdType`/`Dem_EventStatusType` trùng với `Dem_Types.h`. MCAL không dùng file đó.
- Thêm module MCAL mới (vd. Spi) thì copy thêm `SchM_<Mod>.{c,h}` tương ứng.

## 4. Tên callback trong cấu hình EB Tresos phải khớp code

- Gpt: notification của `GptChannel_Tick1ms` = `Os_Sched_TickNotification` (`Gpt_PBcfg.c`), được khai báo trong `ecum/include/Os_Sched.h`. Đổi tên ở Tresos thì phải đổi cả code.
- Tên handler ngắt trong Platform/IntCtrl phải trùng tên ISR của RTD. Sai tên thì build vẫn qua, nhưng ngắt sẽ nhảy vào handler mặc định (guide 02, mục 12).

## 5. Mem_43_INFLS chạy access code từ RAM

- Linker cung cấp các symbol `Fls_ACEraseRomStart`/`Size`, `Fls_ACWriteRomStart`/`Size` và section `.acfls_code_ram`. `Mem_43_INFLS_Ipw.c` cần các symbol này (BL_SRS_011, RSK-04).
- Chỉ build Mem_43_INFLS trong BL. App exclude `mcal/Mem_43_INFLS`, `Mem_43_INFLS_Cfg.c`, `Ftfc_Mem_InFls_Ip_Cfg.c`, `SchM_Mem_43_INFLS.c`.

## 6. Module chưa cấu hình

- `mcal/Spi` có source nhưng chưa có `Spi_Cfg.h`, nên bị exclude trong cả hai project. Chỉ bật lại khi cần cấu hình UJA1169 (OP-HW-01).

## 7. Warning còn lại là của RTD

- Ở Release (`-O`), `mcal/Mcu/src/Ram_Ip.c` sinh 6 warning `-Warray-bounds`. Đây là code gốc của NXP, không sửa. Nếu buộc phải sửa thì theo quy tắc `MOCK_PATCH` ở guide 02, mục 13.
