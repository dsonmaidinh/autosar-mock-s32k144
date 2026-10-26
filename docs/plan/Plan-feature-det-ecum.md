# Plan: dev nhánh `feature/det-ecum` (Det + EcuM + scheduler)

Trạng thái: **nháp, chờ duyệt** (26/10/2026).
Nguồn: `docs/Mock.docx` mục 3.10 (Det), 3.11 (EcuM), 1.9 (Bảng 8: phụ thuộc và thứ tự init), bảng commit "Branch feature/det-ecum" (D-01…D-04).

## 1. Mục tiêu nhánh

Theo `Mock.docx`:

> Sprint S1. Det ghi lỗi lập trình và lỗi runtime theo R24-11. EcuM khởi tạo module theo thứ tự và chạy task 1 ms / 10 ms. Đây là chỗ để các module sau "cắm" vào.

**Kết thúc nhánh:**
- Cả BL và App khởi động qua `EcuM_Init()`, rồi chạy `Os_Sched_Run()` với tick 1 ms thật (LPIT0).
- Det hoạt động đúng DET_SRS_001…004.
- Các module BSW còn là khung vẫn được gọi `Init` và `MainFunction` đúng thứ tự và chu kỳ. Nhánh sau chỉ việc viết thân hàm, không phải động vào EcuM.

## 2. Requirement phải đạt

| SRS | Nội dung (rút gọn) | SWS | Test |
|---|---|---|---|
| DET_SRS_001 | `Det_ReportError` lưu (ModuleId, InstanceId, ApiId, ErrorId) vào log, gọi hook, rồi **dừng** (`Det_StopHook`: vòng lặp + `__BKPT`). Có chống gọi đệ quy (`Det_InReport`). Chỉ khi DevErrorDetect = ON | SWS_Det_00009, 00026, 00035 | DET-TC-01 |
| DET_SRS_002 | Gọi trước `Det_Init` → dừng, **không** ghi log, **không** gọi hook | SWS_Det_00208 | DET-TC-02 |
| DET_SRS_003 | `Det_ReportRuntimeError` ghi log, trả về `E_OK`, chạy tiếp. Không phụ thuộc DevErrorDetect | SWS_Det_01001 | DET-TC-03 |
| DET_SRS_004 | Runtime error trước `Det_Init` → trả về `E_OK` ngay, không làm gì thêm | SWS_Det_00024 | DET-TC-04 |
| ECUM_SRS_001 | Thứ tự init: Det → Dem_PreInit → Mcu (clock, mode) → Port → Gpt → Can_43_FLEXCAN → CanIf → CanTp → PduR → Dem → ComM → CanSM → Dcm | SWS_EcuM_02411, 04145 (tailored) | ECUM-TC-01 |
| ECUM_SRS_002 | CanTp_MainFunction mỗi 1 ms. Can_43_FLEXCAN_MainFunction_Mode, CanSM, ComM_MainFunction_CAN0, Dcm, Dem mỗi 10 ms. Jitter ≤ 1 ms; task 10 ms chạy 100 ± 1 lần/giây; có overrun counter | — (project) | ECUM-TC-02 |
| ECUM_SRS_003 | `Dem_RestartOperationCycle(POWER)` sau `Dem_Init` (chỉ App) | SWS_Dem_00194 | ECUM-TC-03 |
| ECUM_SRS_004 | Reset bằng `Mcu_PerformReset()` **sau khi** response chẩn đoán đã được confirm. Tester nhận `51 01`, rồi ECU khởi động lại trong < 100 ms | SWS_Dcm_01423 | ECUM-TC-04 |
| OP-DET-01 | Log 32 bản ghi; xuất log qua debugger watch | — | — |
| OP-ECUM-01 | Bare-metal: chỉ có StartPreOS, thay StartOS bằng vòng lặp scheduler | — | — |

## 3. Hiện trạng code

Nhánh `feature/det-ecum` hiện **trùng develop** (`923b4c6`), chưa có commit riêng.

| File | Trạng thái |
|---|---|
| `common/bsw/Det/{include,src}` | Khung: header đủ API R24-11, thân hàm trống. `Det_ConfigType` mới có `Det_Dummy` |
| `*/cfg/Det_Cfg.{h,c}` | Khung `Det_Config = { 0U }` |
| `common/ecum/src/EcuM.c`, `EcuM_Callout.c`, `Os_Sched.c` | Khung, có TODO ghi SRS |
| `mcal_cfg/src/Gpt_PBcfg.c` | Đã gắn notification `Os_Sched_TickNotification` cho `GptChannel_Tick1ms` (LPIT0 ch0) |
| `mcal_cfg/src/IntCtrl_Ip_Cfg.c` | Ngắt LPIT0_Ch0 (prio 3) và 3 ngắt CAN0 (prio 2) đã bật |
| `*/src/main.c` | `BM_Main()` (chỉ BL) → `EcuM_Init()` → `Os_Sched_Run()` |

## 4. Vấn đề phát hiện, cần chốt trước khi code

| # | Vấn đề | Ảnh hưởng | Đề xuất |
|---|---|---|---|
| Q1 | **Develop chưa có bản fix linker** (`*(.x.*)`). Fix hiện chỉ nằm trên `feature/bootloader` (`cc18c16`) và `feature/application` (`8b4fab7`) | Ngay khi `EcuM_Init` gọi Mcu, Port hay Gpt, link sẽ lỗi `will not fit in region int_flash_config` (guide 03, mục 9.4) | Merge `feature/bootloader` và `feature/application` vào develop trước, rồi merge develop vào det-ecum. Phương án thay thế: cherry-pick 2 commit fix làm commit đầu của nhánh |
| Q2 | **`Mcu_PerformReset` đang bị tắt**: `POWER_IP_PERFORM_RESET_API = STD_OFF` (`Power_Ip_Cfg_Defines.h`) | Không gọi được hàm mà ECUM_SRS_004 yêu cầu | Bật `McuPerformResetApi` trong `Mcu.xdm`, rồi Generate. Đây là thay đổi `mcal_cfg`, là việc của nhánh platform. Phương án thay thế: tạm ghi `SCB->AIRCR = SYSRESETREQ` trong `EcuM_AL_Reset` và ghi deviation |
| Q3 | Commit D-01 trong doc ghi "import Det from classic-platform (copy)". Quy ước đã chốt (`docs/notes/bsw_sws_r24-11.md` mục 1) là không copy thân hàm GPL | Mâu thuẫn giữa doc và quy ước | **Tự viết** `Det.c` theo SWS. Chỉ tham khảo hành vi của classic-platform. D-01 đổi thành "khung + cấu hình" |
| Q4 | Doc D-03 ghi tạo `EcuM_Cfg.h`, nhưng tên này **đã có**: `mcal_cfg/include/EcuM_Cfg.h` do EB Tresos sinh | Trùng tên header, include nhầm | Đặt switch theo từng image vào file mới `*/cfg/EcuM_ImageCfg.h` |
| Q5 | Thứ tự trong ECUM_SRS_001 thiếu các module mà RTD bắt buộc init: `OsIf_Init`, `Platform_Init` (ngắt), `Dio` (không có Init), và `Mem_43_INFLS_Init` (chỉ BL) | Không init `Platform_Init` thì ngắt LPIT/CAN không chạy | Thêm vào `EcuM_AL_DriverInitOne` theo bảng 5.2 và ghi vào note "tailoring". Không đổi thứ tự các module mà SRS đã nêu |
| Q6 | ECUM_SRS_004 "reset sau khi confirm response" phụ thuộc Dcm (confirmation `51 01`), mà Dcm chưa có | ECUM-TC-04 chưa test được trong nhánh này | Nhánh này làm `EcuM_AL_Reset(ECUM_RESET_MCU)` và cơ chế "reset trì hoãn". Dcm (B-04/X-xx) gọi cơ chế này từ callback confirmation. TC-04 chạy sau, khi có Dcm |
| Q7 | Dem chỉ có ở App (`bsw/Dem` bị loại khỏi build BL) | `EcuM.c` dùng chung phải bỏ Dem khi build BL | Dùng switch `ECUM_USE_DEM` trong `EcuM_ImageCfg.h` (Q4) |

## 5. Thiết kế

### 5.1 Det (`common/bsw/Det`)

```c
typedef struct {                 /* Det.h – Det_ConfigType (thay Det_Dummy) */
    void (*ErrorHook)(uint16 ModuleId, uint8 InstanceId, uint8 ApiId, uint8 ErrorId);   /* NULL = không có hook */
    void (*RuntimeErrorHook)(uint16, uint8, uint8, uint8);
} Det_ConfigType;

typedef struct {                 /* một bản ghi log */
    uint16 ModuleId; uint8 InstanceId; uint8 ApiId; uint8 ErrorId;
    uint8  Kind;                 /* DEV / RUNTIME / TRANSIENT */
} Det_LogEntryType;
```

| Thành phần | Hành vi |
|---|---|
| `Det_ErrorLog[DET_LOG_SIZE]` (32, `Det_Cfg.h`) | Ring buffer; `Det_LogIndex`, `Det_LogOverflow`. Biến toàn cục `volatile`, để debugger watch được (OP-DET-01) |
| `Det_Init(cfg)` | Lưu cfg, xoá log, đặt `Det_Initialized = TRUE` |
| `Det_ReportError` | Chưa init → `Det_StopHook()` (DET_SRS_002). Đã init → ghi log → gọi hook (nếu có, và `Det_InReport == FALSE`) → `Det_StopHook()` |
| `Det_StopHook()` | `__asm("BKPT #0")` + `for(;;)`. Hàm riêng để đặt breakpoint |
| `Det_ReportRuntimeError` | Chưa init → `return E_OK` (DET_SRS_004). Đã init → ghi log → gọi runtime hook → `return E_OK` |
| `Det_ReportTransientFault` | Ghi log, trả về `E_OK` (ngoài SRS, làm tối thiểu) |
| `Det_Start`, `Det_GetVersionInfo` | Theo SWS; NULL → `DET_E_PARAM_POINTER` |

> **Release build:** `Det_ReportError` vẫn được compile, nhưng các module không gọi nó vì `<MOD>_DEV_ERROR_DETECT = STD_OFF` khi không có `DET_ENABLED`. Runtime error vẫn hoạt động ở cả Release (DET_SRS_003).

### 5.2 EcuM (`common/ecum`)

```
EcuM_Init()                                   SWS_EcuM_02411 / 04145 (tailored)
├── EcuM_AL_DriverInitZero()                  SWS_EcuM_02905
│   ├── Det_Init(&Det_Config)                 [1]
│   └── Dem_PreInit()                         [0]  #if ECUM_USE_DEM
├── EcuM_AL_DriverInitOne()                   SWS_EcuM_02907
│   ├── OsIf_Init(NULL_PTR)                   (Q5 – RTD Base)
│   ├── Mcu_Init(&Mcu_Config)                 [2]
│   ├── Mcu_InitClock(McuClockSettingConfig_0)    MCU_NO_PLL = ON → không chờ PLL
│   ├── Mcu_SetMode(McuModeSettingConf_0)
│   ├── Platform_Init(NULL_PTR)               (Q5 – bật ngắt theo IntCtrl_Ip_Cfg)
│   ├── Port_Init(&Port_Config)               [2]
│   ├── Gpt_Init(&Gpt_Config)                 [2]
│   ├── Mem_43_INFLS_Init(&Mem_43_INFLS_Config)   #if ECUM_USE_MEM_INFLS (chỉ BL)
│   ├── Can_43_FLEXCAN_Init(&Can_43_FLEXCAN_Config)   [3]
│   ├── CanIf_Init(&CanIf_Config)             [4]
│   ├── CanTp_Init(&CanTp_Config)             [5]
│   ├── PduR_Init(&PduR_Config)               [6]
│   ├── Dem_Init(&Dem_Config)                 [7]  #if ECUM_USE_DEM
│   ├── Dem_RestartOperationCycle(DemConf_DemOperationCycle_POWER)  ECUM_SRS_003
│   ├── ComM_Init(&ComM_Config)               [8]
│   ├── CanSM_Init(&CanSM_Config)             [8]
│   └── Dcm_Init(&Dcm_Config)                 [9]
├── (App) CDD_CanTest_Init()                  nếu ECUM_USE_CDD_CANTEST
└── Os_Sched_Init()                           ECUM_SRS_002
```

**File mới `bootloader/cfg/EcuM_ImageCfg.h` và `application/cfg/EcuM_ImageCfg.h`:**

| Switch | BL | App |
|---|---|---|
| `ECUM_USE_DEM` | `STD_OFF` | `STD_ON` |
| `ECUM_USE_MEM_INFLS` | `STD_ON` | `STD_OFF` |
| `ECUM_USE_CDD_CANTEST` | `STD_OFF` | `STD_ON` |

**Reset (ECUM_SRS_004, Q6):**
- `EcuM_AL_Reset(ECUM_RESET_MCU)` gọi `Mcu_PerformReset()` (sau khi giải quyết Q2).
- Thêm API dự án `EcuM_RequestReset(EcuM_ResetType)`: đặt cờ, rồi task 10 ms gọi `EcuM_AL_Reset` ở vòng kế tiếp. Dcm gọi API này **trong callback confirmation** của response `51 01`, nên response chắc chắn đã đi ra bus trước khi reset.
- API này đánh dấu là extension của dự án (OP-ECUM-01), vì SWS dùng `EcuM_SelectShutdownTarget` + `EcuM_GoDown`, mà bản tailored không có shutdown target.

### 5.3 Scheduler (`common/ecum/src/Os_Sched.c`)

```
LPIT0_Ch0 IRQ (1 ms) ──► Gpt notification ──► Os_Sched_TickNotification(): Os_TickCount++   (chỉ tăng đếm)

Os_Sched_Run():  for(;;)
    if (Os_TickCount != Os_LastTick)            ← có tick mới
        nếu lệch > 1 tick → Os_OverrunCount++   (task trước chạy quá 1 ms)
        Os_Task_1ms()                            CanTp_MainFunction
        mỗi 10 tick → Os_Task_10ms()             Can_43_FLEXCAN_MainFunction_Mode, CanSM_MainFunction,
                                                 ComM_MainFunction_CAN0, Dcm_MainFunction,
                                                 Dem_MainFunction (#if ECUM_USE_DEM),
                                                 (App) CDD_CanTest_MainFunction
                                                 + xử lý EcuM_RequestReset
```

- `Os_Sched_Init()`: `Gpt_EnableNotification(GptConf_GptChannelConfiguration_GptChannel_Tick1ms)`, rồi `Gpt_StartTimer(ch, OS_SCHED_TICK_VALUE)`.
- `OS_SCHED_TICK_VALUE` tính từ clock LPIT trong `Mcu.xdm` (số tick của LPIT trong 1 ms). Kiểm tra giá trị này khi code: đo bằng scope, không đoán.
- Biến đếm `volatile uint32`, đọc trong vòng lặp. Lệnh đọc 32 bit trên Cortex-M4 là atomic, nên không cần khoá ngắt.
- Đo ECUM-TC-02: dùng một chân Dio (LED, hoặc chân test nếu được chốt) để toggle trong task 1 ms / 10 ms, bật bằng `OS_SCHED_TIMING_PIN` (chỉ Debug).

## 6. Commit (theo D-01…D-04 của doc, đã chỉnh theo mục 4)

| # | Commit message | Nội dung | Cần trước | Kiểm chứng |
|---|---|---|---|---|
| D-00 | *(không phải commit của nhánh)* | Q1: develop có fix linker, merge develop vào det-ecum | — | `build.sh all all` OK |
| D-01 | `feat(det): add Det configuration and error log types` | `Det_ConfigType` (hook), `Det_LogEntryType`, `DET_LOG_SIZE = 32` trong `*/cfg/Det_Cfg.h`, `Det_Config` thật trong `Det_Cfg.c` (BL, App) | D-00 | Build OK |
| D-02 | `feat(det): implement error logging, stop hook and runtime errors` | `Det.c` theo 5.1 (DET_SRS_001…004) | D-01 | DET-TC-01…04 (mục 7) |
| D-03 | `feat(ecum): implement EcuM_Init sequence` | `EcuM.c`, `EcuM_Callout.c` theo 5.2; `EcuM_ImageCfg.h` (BL, App); bỏ `Test_LedBlink` khỏi luồng nếu còn | D-02, Q2 (phần reset) | ECUM-TC-01 |
| D-04 | `feat(ecum): add 1 ms/10 ms task table with overrun counter` | `Os_Sched.c` theo 5.3, `OS_SCHED_TICK_VALUE` | D-03 | ECUM-TC-02 |
| D-05 | `feat(ecum): add deferred reset via EcuM_RequestReset` | `EcuM_RequestReset` + `EcuM_AL_Reset` | D-04, Q2 | Gọi thử từ debugger → reset < 100 ms. TC-04 đầy đủ chờ Dcm |
| D-06 | `docs(notes): EcuM tailoring and Det usage` | `docs/notes/det_ecum.md`: thứ tự init thật, các module thêm vào (Q5), `EcuM_RequestReset`, cách đọc log Det | D-05 | — |

Mỗi commit đều phải qua `bash software/tools/build.sh all all`: 0 lỗi, không có warning mới.

## 7. Kiểm chứng

| Test | Cách làm | Đạt khi |
|---|---|---|
| DET-TC-01 | Debug_FLASH: gọi `Can_43_FLEXCAN_Write(0, NULL_PTR)` sau init | Dừng ở `Det_StopHook`; `Det_ErrorLog[0]` = (80, 0, 0x06, 0x01), tức `CAN_43_FLEXCAN_MODULE_ID`, instance 0, `CAN_43_FLEXCAN_SID_WRITE`, `CAN_43_FLEXCAN_E_PARAM_POINTER` |
| DET-TC-02 | Gọi `Det_ReportError` trước `Det_Init` (code test tạm thời) | Dừng; log rỗng; hook không được gọi |
| DET-TC-03 | `Det_ReportRuntimeError(...)` sau init (CanIf chưa có thì gọi trực tiếp) | Log có bản ghi, chương trình chạy tiếp, trả về `E_OK` |
| DET-TC-04 | `Det_ReportRuntimeError` trước init | Trả về `E_OK`, log rỗng |
| ECUM-TC-01 | Breakpoint hoặc trace từng `*_Init` | Đúng thứ tự 5.2; `Det_ErrorLog` rỗng sau init |
| ECUM-TC-02 | Toggle chân trong task, đo bằng scope/logic analyzer | 1 ms ± jitter ≤ 1 ms; 10 ms chạy 100 ± 1 lần/giây; `Os_OverrunCount = 0` |
| ECUM-TC-03 | — | Hoãn tới khi có Dem (M-xx), dùng `19 02 FF` |
| ECUM-TC-04 | — | Hoãn tới khi có Dcm (B-04 / X-xx), dùng `11 01` |

DET-TC-01…04 chạy được trên target bằng debugger. `tests/unit` hiện trống; viết unit test trên host là việc riêng (chưa có framework), nên không nằm trong nhánh này.

## 8. Cần người dùng chốt

1. **Q1:** đưa fix linker vào develop bằng cách merge `feature/bootloader` / `feature/application`, hay cherry-pick vào det-ecum?
2. **Q2:** bật `McuPerformResetApi` trong EB Tresos (sửa `mcal_cfg`), hay tạm dùng `SCB->AIRCR`?
3. **Q3:** đồng ý tự viết Det (không copy classic-platform)?
4. **Q4/Q6:** đồng ý tên `EcuM_ImageCfg.h` và API mở rộng `EcuM_RequestReset`?
5. **Chân đo timing** cho ECUM-TC-02: dùng LED xanh (PTD0) hay một chân test riêng (phải thêm vào `Port.xdm`)?
6. **Push:** sau mỗi commit có push không, hay để bạn tự push?
