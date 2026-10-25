# 02 – Cấu hình Mock ECU (Bootloader + Application) bằng EB Tresos

Hướng dẫn từng thao tác trong EB Tresos để cấu hình MCAL theo **Bảng 7 – Cấu hình phần mềm** (`docs/Mock.docx` mục 1.8), từ lúc thêm module tới khi Generate ra `firmware/common/mcal_cfg` với **0 error**. Mọi ảnh chụp từ project `MockECU_Cfg` thật. Làm [Hướng dẫn 01](01_Setup_EB_Tresos.md) trước.

## Table of Contents

1. [**Description**](#1-description)
2. [**Chọn phương án cấu hình**](#2-chọn-phương-án-cấu-hình)
3. [**Cấu trúc thư mục**](#3-cấu-trúc-thư-mục)
4. [**Thao tác chung trong EB Tresos**](#4-thao-tác-chung-trong-eb-tresos)
5. [**Thêm module vào project**](#5-thêm-module-vào-project)
6. [**Mcu – clock**](#6-mcu--clock)
7. [**Port – chân**](#7-port--chân)
8. [**Dio – kênh LED**](#8-dio--kênh-led)
9. [**Gpt – tick 1 ms**](#9-gpt--tick-1-ms)
10. [**Can_43_FLEXCAN – CAN 500 kbit/s**](#10-can_43_flexcan--can-500-kbits)
11. [**Mem_43_INFLS – vùng flash**](#11-mem_43_infls--vùng-flash)
12. [**Platform – ngắt và Generate**](#12-platform--ngắt-và-generate)
13. [**Define sinh ra – dùng trong code**](#13-define-sinh-ra--dùng-trong-code)
14. [**Lưu ý code tĩnh còn thiếu**](#14-lưu-ý-code-tĩnh-còn-thiếu)
15. [**Phần không cấu hình bằng EB Tresos**](#15-phần-không-cấu-hình-bằng-eb-tresos)
16. [**Kiểm chứng**](#16-kiểm-chứng)

## 1. Description

_<-- Back to [Table of Contents](#table-of-contents)_

Mock ECU có 2 image chạy trên cùng một chip:

- **Bootloader** (0x0000_0000): chạy đầu tiên, nhận phần mềm mới qua CAN, ghi flash.
- **Application** (0x0002_0000): chạy CAN, UDS, DTC.

Câu hỏi đặt ra: 2 image này dùng **chung 1 cấu hình EB Tresos** hay **mỗi image 1 cấu hình riêng**?

## 2. Chọn phương án cấu hình

_<-- Back to [Table of Contents](#table-of-contents)_

| Tiêu chí | A. Chung 1 cấu hình | B. Mỗi image 1 cấu hình |
|---|---|---|
| Clock, chân, CAN bit timing | Định nghĩa **1 lần**, 2 image chắc chắn giống nhau | Phải giữ 2 bản giống nhau bằng tay, dễ lệch |
| Số project EB Tresos | 1 (`MockECU_Cfg`) | 2 (`MockECU_App_Cfg`, `MockECU_FBL_Cfg`) |
| Module thừa | App có cấu hình `Mem_43_INFLS` dù không dùng. Linker `--gc-sections` loại bỏ code không gọi, nên không tốn flash | Không thừa |
| Khác biệt BL / App | Không khác được trong MCAL (cả 2 dùng CAN ngắt, cùng mailbox) | Khác tuỳ ý (ví dụ BL dùng polling) |
| Phù hợp quy tắc "mọi branch dùng chung nền tảng" | **Rất phù hợp**: chỉ 1 nơi sửa, trên branch `platform/*` | Kém hơn: 2 nơi sửa |
| Công sức cho Fresher | Thấp | Gấp đôi |

**Chốt: phương án A – chung 1 cấu hình EB Tresos.**

Lý do:
- Thiết kế ở `docs/Mock.docx` cho 2 image dùng **cùng** clock, cùng chân, cùng CAN 500 kbit/s và cùng mailbox (mục 1.6, 1.8). Không có tham số MCAL nào khác nhau.
- Điểm khác giữa BL và App nằm ở **BSW** (Dcm session, security, dịch vụ) và **linker**, cả 2 đều nằm ngoài EB Tresos (mục 5). Phần đó tách riêng trong `cfg/` của từng project.
- Nếu sau này BL cần MCAL khác (ví dụ CAN polling), lúc đó mới tách thành phương án B bằng cách copy `MockECU_Cfg` thành `MockECU_FBL_Cfg`.

## 3. Cấu trúc thư mục

_<-- Back to [Table of Contents](#table-of-contents)_

Cấu trúc này thay cho cây ở mục 5.2 của `docs/Mock.docx` (bản cũ coi cả repo là 1 project S32DS). Ký hiệu `(P-xx)` là commit tạo ra file, theo roadmap.

```
mock-ecu-s32k144/
├── README.md, .gitignore, .gitmodules
│
├── firmware/
│   ├── mcal_config/                       # ★ EB Tresos – CHỈ sửa trên branch platform/*
│   │   └── MockECU_Cfg/                   # project EB Tresos dùng chung cho BL + App
│   │       ├── .project, .prefs/pref_general.xdm
│   │       ├── config/                    # Mcu, Port, Dio, Gpt, Platform, BaseNXP, Resource,
│   │       │                              # Can_43_FLEXCAN, Mem_43_INFLS, (Spi).xdm   (P-04…P-09, F-01)
│   │
│   ├── common/                            # code dùng chung cho 2 image
│   │   ├── mcal/                          # source tĩnh RTD 2.0.0 – không sửa
│   │   │   └── Base, Platform, Mcu, Port, Dio, Gpt, Can_43_FLEXCAN, Mem_43_INFLS, Rte
│   │   ├── mcal_cfg/{include,src}         # ★ code EB Tresos sinh ra – KHÔNG sửa tay, CÓ commit
│   │   ├── bsw/                           # từ classic-platform, đã sửa cho R24-11 / RTD
│   │   │   └── Det, CanIf, PduR, CanTp, CanSM, ComM, Dem, Dcm   (mỗi module: inc/, src/)
│   │   ├── ecum/                          # EcuM rút gọn + scheduler 1 ms / 10 ms   (P-03, D-03)
│   │   ├── stubs/                         # debug.h, SchM_*.h, Rte_Dcm.h, NvM.h ...
│   │   └── boot_shared/Boot_Shared.h      # địa chỉ, magic, struct metadata (App + BL)
│   │
│   ├── application/                       # project S32DS "application"
│   │   ├── src/main.c
│   │   ├── src/app/                       # Dcm_Callout_App.c, DummySwc.c, AppVersion.h
│   │   ├── src/cdd/CDD_CanTest/           # frame 0x3A0 / 0x2B0
│   │   ├── cfg/                           # cấu hình BSW của App: CanIf, PduR, CanTp, CanSM,
│   │   │                                  # ComM, Dem, Dcm, Det, EcuM (*_Cfg.h, *_PBcfg.c)
│   │   ├── Project_Settings/Linker_Files/app.ld
│   │   └── (link) ../common/mcal, ../common/mcal_cfg
│   │
│   ├── bootloader/                        # project S32DS "bootloader"
│   │   ├── src/main.c
│   │   ├── src/boot_manager/              # BM_Main.c, BM_Request.c, BM_Jump.c
│   │   ├── src/fbl/                       # Fbl_Flash.c, Fbl_Download.c, Fbl_Routines.c,
│   │   │                                  # Fbl_Crc32.c, Fbl_Metadata.c, Dcm_Callout_Bl.c
│   │   ├── cfg/                           # cấu hình BSW của BL (không có Dem)
│   │   ├── Project_Settings/Linker_Files/bl.ld
│   │   └── (link) giống application
│   │
│   └── tests/
│       ├── unit/                          # Unity, chạy trên PC
│       ├── stubs/                         # Can_Stub.c, Det_Stub.c, DcmStub.c
│       └── target/                        # test chạy trên board (ghi / đọc flash)
│
├── software/
│   ├── tester/                            # pytest + python-can / udsoncan (HIL)
│   ├── flasher/                           # flash_app.py
│   └── tools/                             # build.sh, requirements.txt
│
├── hardware/
│   ├── evb_s32k144/                       # schematic, pinout
│   └── test_bench/                        # sơ đồ đấu PCAN, ảnh setup
│
├── reference/
│   ├── 00_Document/                       # Reference Manual, schematic, bài học
│   └── github/                            # submodule (chỉ đọc)
│
└── docs/
    ├── guides/                            # 01_Setup_EB_Tresos.md, 02_MockECU_MCAL_Config.md
    ├── Mock.docx, COM_stack.docx, DIAG_stack.docx
    ├── Autosar asm 2/, SWS/
    └── reports/                           # báo cáo test IP1–IP5, release note
```

**Quy tắc ngắn:**
- Cái gì **giống nhau** giữa BL và App → `firmware/common/` hoặc `firmware/mcal_config/`.
- Cái gì **khác nhau** → `firmware/application/` hoặc `firmware/bootloader/`.
- Sửa `mcal_config/` → luôn generate lại, rồi build **cả 2** project trước khi commit.


## 4. Thao tác chung trong EB Tresos

_<-- Back to [Table of Contents](#table-of-contents)_

Phần này dùng lại cho mọi module ở mục 5–11. Đọc 1 lần cho quen tay.

| Thao tác | Cách làm | Ghi chú |
|---|---|---|
| Mở editor module | Project Explorer → mở `MockECU_Cfg (CORTEXM, S32K14X)` → mở module → **double-click** dòng con (vd `Mcu`) | Editor mở thành 1 tab, mỗi tab con là 1 container |
| Thêm phần tử vào bảng | Nút **+** (xanh lá) góc phải bảng | Thêm 1 dòng mặc định `<Tên>_0`, `<Tên>_1`... |
| Thêm đủ phần tử bắt buộc | Nút **Add required elements** (hình người xanh) | Dùng khi lỗi *"has not enough children ... allowed are 42"* |
| Mở 1 dòng để sửa | Chọn dòng → nút **bút chì** (Edit) góc phải bảng, hoặc double-click | Editor chuyển xuống container đó |
| Quay lại container cha | Nút **mũi tên lên** (Navigate one container upward) góc phải tiêu đề | |
| Ô bị khoá (icon máy tính/hình tam giác) | Bấm **mũi tên nhỏ** cạnh ô → **Set manually edited** để sửa tay, hoặc **Calculate value** để Tresos tự tính lại | Giá trị *calculated* được tính từ ô khác |
| Đổi tên container | Sửa ô **Name** trên cùng → Tab. Nếu hỏi *Adapt references?* → **Yes** | Tên này sinh ra define symbolic (mục 13) |
| Lưu | `Ctrl+S` (1 module) hoặc `Ctrl+Shift+S` (tất cả) | Tab có dấu `*` là chưa lưu |
| Xem lỗi | Tab **Problems View** (dưới). Rê chuột lên dòng lỗi để đọc hết | Lỗi đỏ chặn Generate, warning vàng thì không |

Thứ tự làm (module sau tham chiếu module trước): **Mcu → Port → Dio → Gpt → Can → Mem → Platform → Generate**.

---

## 5. Thêm module vào project

_<-- Back to [Table of Contents](#table-of-contents)_

1. Chuột phải dòng **`MockECU_Cfg (CORTEXM, S32K14X)`** (dòng con, không phải dòng project ngoài cùng) → **Module Configurations...**

![Config_image_01.png](../Images/MCAL_Config/Config_image_01.png)

2. Cột trái **Available Modules** → mở **No Cluster** → chọn module (vd `Can_43_FLEXCAN (V2.0.0, AS4.7.0)`) → bấm **mũi tên trên cùng** giữa 2 cột. Module in mờ là đã có.

![Config_image_02.png](../Images/MCAL_Config/Config_image_02.png)

3. Làm lần lượt cho **Can_43_FLEXCAN**, **Gpt**, **Mem_43_INFLS**. Module sang cột phải với Enable + Generate đã tick → **OK**.

![Config_image_03.png](../Images/MCAL_Config/Config_image_03.png)

4. Cây Project Explorer hiện đủ module mới.

![Config_image_04.png](../Images/MCAL_Config/Config_image_04.png)

> **Giải thích:** Problems View lúc này báo **7 error** – bình thường, vì 3 module mới chưa có phần tử bắt buộc (controller, kênh timer, vùng flash...). Mục 6–11 sửa hết từng lỗi.

**Kiểm tra đường dẫn generate** (đã làm ở 01): chuột phải `MockECU_Cfg` → **Properties → Configuration Project → Code Generator** → *Default Generation Path* = `..\..\common\mcal_cfg`.

![Config_image_05.png](../Images/MCAL_Config/Config_image_05.png)

---

## 6. Mcu – clock

_<-- Back to [Table of Contents](#table-of-contents)_

Mcu quyết định tần số cho CPU và từng ngoại vi. Gpt và Can sau này **tham chiếu** clock từ đây.

#### <ins>6.1 Mở Mcu và clock setting<ins>

Double-click **Mcu** → tab **McuModuleConfiguration** → bảng **McuClockSettingConfig** → mở `McuClockSettingConfig_0` (template đã có sẵn).

![Config_image_06.png](../Images/MCAL_Config/Config_image_06.png)

#### <ins>6.2 Kiểm tra clock hệ thống (tab General)<ins>

| Ô | Giá trị | Giải thích |
|---|---|---|
| Run System Clock Select | `FIRC_CLK` | Nguồn 48 MHz nội, không cần thạch anh |
| Run Core / Bus / Slow Clock Divider | 1 / 1 / 3 | Core 48, Bus 48, Flash 16 MHz (Bảng 7) |

![Config_image_07.png](../Images/MCAL_Config/Config_image_07.png)

#### <ins>6.3 Kiểm tra SOSC (tab McuSOSCClockConfig)<ins>

| Ô | Giá trị | Giải thích |
|---|---|---|
| SOSC Frequency | 8000000 | Thạch anh 8 MHz trên EVB |
| SOSC Divider 2 | 1 | SOSCDIV2 = 8 MHz – nguồn clock cho FlexCAN và LPIT |

![Config_image_08.png](../Images/MCAL_Config/Config_image_08.png)

#### <ins>6.4 Bật clock ngoại vi (tab McuPeripheralClockConfig)<ins>

Trong bảng, cột **Enable peripheral** của **FLEXCAN0** và **LPIT0** phải được tick (template đã tick sẵn).

![Config_image_09.png](../Images/MCAL_Config/Config_image_09.png)

LPIT0 cần chọn nguồn clock: mở dòng `LPIT0` → **Peripheral Clock Select** = `SOSCDIV2_CLK`.

![Config_image_10.png](../Images/MCAL_Config/Config_image_10.png)

Ô **Peripheral Clock Frequency** còn `0.0` → bấm mũi tên cạnh ô → **Calculate value**.

![Config_image_11.png](../Images/MCAL_Config/Config_image_11.png)

Kết quả: 8000000 Hz.

![Config_image_12.png](../Images/MCAL_Config/Config_image_12.png)

> **Giải thích:** Không bật clock ngoại vi thì thanh ghi của FlexCAN/LPIT không truy cập được (HardFault khi init).

#### <ins>6.5 Tạo Clock Reference Point (tab McuClockReferencePoint)<ins>

*Reference point* là "ổ cắm clock" để module khác cắm vào. Gpt và Can không đọc thẳng Mcu, mà chọn 1 reference point.

1. Bảng có sẵn `McuClockReferencePoint_0` (của template). Bấm **+** 2 lần → thêm 2 dòng.

![Config_image_13.png](../Images/MCAL_Config/Config_image_13.png)

2. Mở dòng index 1 → đổi Name = `McuClockRefPoint_LPIT0` → Tab. Hỏi *Adapt references* → **Yes**.

![Config_image_14.png](../Images/MCAL_Config/Config_image_14.png)

3. **Mcu Clock Frequency Select** = `LPIT0_CLK` (gõ tên để lọc danh sách).

![Config_image_15.png](../Images/MCAL_Config/Config_image_15.png)

4. Ô **Mcu Clock Reference Point Frequency** → mũi tên → **Calculate value** → 8000000.

![Config_image_16.png](../Images/MCAL_Config/Config_image_16.png)

5. Về bảng (mũi tên lên) → mở dòng index 2 → Name = `McuClockRefPoint_FLEXCAN0`, **Frequency Select** = `SOSCDIV2_CLK`, Calculate → 8000000.

![Config_image_17.png](../Images/MCAL_Config/Config_image_17.png)

6. `Ctrl+S`.

---

## 7. Port – chân

_<-- Back to [Table of Contents](#table-of-contents)_

Port quyết định **mỗi chân làm gì** (GPIO hay CAN, vào hay ra). Template có sẵn 1 pin (PTD0).

1. Double-click **Port** → tab **PortContainer** → mở `PortContainer_0` → tab **PortPin**.

![Config_image_18.png](../Images/MCAL_Config/Config_image_18.png)

![Config_image_19.png](../Images/MCAL_Config/Config_image_19.png)

2. Mở `PortPin_0` (có sẵn) và sửa:

| Ô | Giá trị | Giải thích |
|---|---|---|
| Name | `LED_BLUE_PTD0` | Sinh define `PortConf_PortPin_LED_BLUE_PTD0` |
| PortPin Pcr | 96 | Số chân = Port × 32 + Pin. PORTA=0, B=1, C=2, **D=3**, E=4 → 3×32+0 |
| PortPin Mode | `GPIO` | |
| PortPin Direction | `PORT_PIN_OUT` | |
| PortPin Level Value | `PORT_PIN_LEVEL_HIGH` | LED trên EVB sáng mức thấp → HIGH = tắt khi khởi động |

![Config_image_20.png](../Images/MCAL_Config/Config_image_20.png)

![Config_image_81.png](../Images/MCAL_Config/Config_image_81.png)

3. Về bảng PortPin → **+** 4 lần. Xuất hiện thêm **lỗi** `PortNumberOfPortPins ... out of range` – xử lý ở bước 6.

![Config_image_21.png](../Images/MCAL_Config/Config_image_21.png)

4. Sửa từng pin mới (mở dòng → sửa → mũi tên lên):

| Name | Pcr | Mode | Direction | Level |
|---|---|---|---|---|
| `LED_RED_PTD15` | 111 (3×32+15) | GPIO | PORT_PIN_OUT | HIGH |
| `LED_GREEN_PTD16` | 112 (3×32+16) | GPIO | PORT_PIN_OUT | HIGH |
| `CAN0_RX_PTE4` | 132 (4×32+4) | `CAN0_RX` | (tự đặt) | – |
| `CAN0_TX_PTE5` | 133 (4×32+5) | `CAN0_TX` | (tự đặt) | – |

![Config_image_82.png](../Images/MCAL_Config/Config_image_82.png)

![Config_image_22.png](../Images/MCAL_Config/Config_image_22.png)

Với PTE4, danh sách **PortPin Mode** chỉ hiện các chức năng chân đó có → chọn `CAN0_RX`. Đây là cách kiểm tra nhanh chân có đúng với schematic không.

![Config_image_23.png](../Images/MCAL_Config/Config_image_23.png)

![Config_image_24.png](../Images/MCAL_Config/Config_image_24.png)

Kết quả bảng:

![Config_image_25.png](../Images/MCAL_Config/Config_image_25.png)

5. **Sửa lỗi số pin:** về `PortContainer_0` → tab **General** → ô **PortNumberOfPortPins** đang = 1 → mũi tên → **Calculate value**.

![Config_image_26.png](../Images/MCAL_Config/Config_image_26.png)

Kết quả = 5, lỗi biến mất (Problems View quay về 7 error).

![Config_image_27.png](../Images/MCAL_Config/Config_image_27.png)

6. `Ctrl+S`.

---

## 8. Dio – kênh LED

_<-- Back to [Table of Contents](#table-of-contents)_

Dio cho code **đọc/ghi** chân đã cấu hình GPIO ở Port. Mỗi DioChannel sinh 1 define để gọi `Dio_WriteChannel()`.

1. Double-click **Dio** → tab General: **Dio Flip Channel Api** đã tick (cho phép `Dio_FlipChannel()`).

![Config_image_28.png](../Images/MCAL_Config/Config_image_28.png)

2. Tab **DioPort** → mở `DioPort_0`: **Dio Port Id = 3** (PORTD).

![Config_image_29.png](../Images/MCAL_Config/Config_image_29.png)

3. Tab **DioChannel** → **+** 2 lần. Lỗi *DioChannelId is repeated* – vì 3 kênh cùng Id 0.

![Config_image_30.png](../Images/MCAL_Config/Config_image_30.png)

4. Mở từng kênh, sửa Name và **Dio Channel Id** (= số pin trong port, không phải Pcr):

| Name | Dio Channel Id |
|---|---|
| `LED_BLUE` | 0 |
| `LED_RED` | 15 |
| `LED_GREEN` | 16 |

![Config_image_31.png](../Images/MCAL_Config/Config_image_31.png)

![Config_image_32.png](../Images/MCAL_Config/Config_image_32.png)

5. `Ctrl+S`. Problems View về 7 error.

---

## 9. Gpt – tick 1 ms

_<-- Back to [Table of Contents](#table-of-contents)_

Gpt tạo ngắt định kỳ 1 ms cho scheduler (`common/ecum/Os_Sched.c`). Dùng **LPIT0 kênh 0**, clock 8 MHz → 1 ms = 8000 tick.

#### <ins>9.1 Sửa lỗi GptPredefTimer1usEnablingGrade<ins>

Double-click **Gpt** → tab General → kéo xuống **GptDriverConfiguration** → **GptPredefTimer1usEnablingGrade** = `GPT_PREDEF_TIMER_1US_DISABLED`.

![Config_image_33.png](../Images/MCAL_Config/Config_image_33.png)

![Config_image_34.png](../Images/MCAL_Config/Config_image_34.png)

> **Giải thích:** predefined timer 1 µs là bộ đếm thời gian chạy tự do theo chuẩn AUTOSAR; Mock không dùng. Bật mà không cấp phần cứng → lỗi. Còn 6 error.

![Config_image_35.png](../Images/MCAL_Config/Config_image_35.png)

#### <ins>9.2 Clock reference<ins>

Tab **GptClockReferencePoint** → **+** → mở dòng → **GptClockReference** = `.../McuClockRefPoint_LPIT0` (tạo ở 6.5).

![Config_image_36.png](../Images/MCAL_Config/Config_image_36.png)

![Config_image_37.png](../Images/MCAL_Config/Config_image_37.png)

#### <ins>9.3 Bảng phần cứng GptHwConfiguration<ins>

Tab **GptHwConfiguration** trống → lỗi *"has 0 child – allowed are 42"*. Bấm **Add required elements** (KHÔNG bấm + 42 lần).

![Config_image_38.png](../Images/MCAL_Config/Config_image_38.png)

![Config_image_39.png](../Images/MCAL_Config/Config_image_39.png)

Dòng **LPIT_0_CH_0**: tick **GptIsrEnable** và **GptChannelIsUsed**.

![Config_image_40.png](../Images/MCAL_Config/Config_image_40.png)

> **Giải thích:** 42 dòng = mọi kênh timer của chip (LPIT 4, FTM 32, LPTMR, SRTC...). Tick dòng nào thì driver mới sinh code + ISR cho kênh đó.

#### <ins>9.4 Khai báo LPIT module<ins>

Tab **GptLpit** → **+** → `GptLpit_0`: **Lpit Hardware Module** = `LPIT_0`.

![Config_image_41.png](../Images/MCAL_Config/Config_image_41.png)

Tab **GptLpitChannels** → **+** → **LPit Channel** = `CH_0`. Lỗi mới *"the channel does have reference, please select GptChannelConfiguration"* – sẽ hết sau 9.5.

![Config_image_42.png](../Images/MCAL_Config/Config_image_42.png)

#### <ins>9.5 Kênh logic GptChannelConfiguration<ins>

Về Gpt → tab **GptChannelConfiguration** → **+** → mở dòng mới:

![Config_image_43.png](../Images/MCAL_Config/Config_image_43.png)

| Ô | Giá trị | Giải thích |
|---|---|---|
| Name | `GptChannel_Tick1ms` | → define `GptConf_GptChannelConfiguration_GptChannel_Tick1ms` |
| GptHwIp | `LPIT` | |
| GptModuleRef | `.../GptLpit_0/GptLpitChannels_0` | Nối kênh logic với kênh phần cứng |
| GptChannelMode | `GPT_CH_MODE_CONTINUOUS` | Tự nạp lại → ngắt đều đặn |
| GptChannelClkSrcRef | `.../GptClockReferencePoint_0` | |
| GptChannelTickFrequency | Calculate value → 8000000 | |
| GptChannelTickValueMax | 4294967295 | LPIT 32-bit |
| GptNotification | `Os_Sched_TickNotification` | Hàm callback viết trong `common/ecum` |

![Config_image_44.png](../Images/MCAL_Config/Config_image_44.png)

![Config_image_45.png](../Images/MCAL_Config/Config_image_45.png)

![Config_image_46.png](../Images/MCAL_Config/Config_image_46.png)

![Config_image_47.png](../Images/MCAL_Config/Config_image_47.png)

![Config_image_48.png](../Images/MCAL_Config/Config_image_48.png)

> Chu kỳ 1 ms **không** đặt ở đây – code gọi `Gpt_StartTimer(GptConf_..._Tick1ms, 8000U)`.

`Ctrl+Shift+S`. Còn **3 error** (Can ×2, Mem ×1).

---

## 10. Can_43_FLEXCAN – CAN 500 kbit/s

_<-- Back to [Table of Contents](#table-of-contents)_

#### <ins>10.1 Controller<ins>

Double-click **Can_43_FLEXCAN** → tab **CanController** → **+** → mở `CanController_0`.

![Config_image_49.png](../Images/MCAL_Config/Config_image_49.png)

| Ô | Giá trị | Giải thích |
|---|---|---|
| Can Hardware Channel | `FLEXCAN_0` | Chân PTE4/PTE5 nối FLEXCAN0 |
| Can Rx / Tx / BusOff Processing Type | `INTERRUPT` | Bảng 7 |
| Can FD ISO | bỏ tick | CAN classic |
| Can Clock from Bus (CTRL[CLK_SRC]) | **bỏ tick** | Dùng clock dao động (SOSCDIV2 8 MHz) thay vì bus 48 MHz → bit timing ổn định |

![Config_image_50.png](../Images/MCAL_Config/Config_image_50.png)

**CanCpuClockRef** = `.../McuClockRefPoint_FLEXCAN0` (6.5).

![Config_image_51.png](../Images/MCAL_Config/Config_image_51.png)

#### <ins>10.2 Baudrate<ins>

Tab **CanControllerBaudrateConfig** → **+** → mở dòng. Mặc định 20 kbit/s:

![Config_image_52.png](../Images/MCAL_Config/Config_image_52.png)

| Ô | Giá trị |
|---|---|
| Name | `CanBaudrate_500k` |
| Can Controller Prescaler | 1 |
| Can Controller BaudRate (Kbps) | 500 |
| Propagation / Phase 1 / Phase 2 / Resynch Jump Width | 7 / 6 / 2 / 2 |

![Config_image_53.png](../Images/MCAL_Config/Config_image_53.png)

> **Giải thích:** 1 bit = Sync(1) + Prop(7) + Seg1(6) + Seg2(2) = **16 tq**. 8 MHz / 1 / 16 = **500 kbit/s**. Sample point = (1+7+6)/16 = **87,5 %**. Đổi baudrate → chỉ đổi prescaler/segment sao cho công thức này đúng.

Về `CanController_0` → **Can Controller Default Baudrate** = `.../CanBaudrate_500k`. Còn 2 error.

![Config_image_54.png](../Images/MCAL_Config/Config_image_54.png)

#### <ins>10.3 Hardware Object (mailbox)<ins>

Về Can → tab **CanHardwareObject** → **+** → mở dòng:

![Config_image_55.png](../Images/MCAL_Config/Config_image_55.png)

Tạo 4 object:

| Name | Implementation | Object Type | Controller Ref | CanHwFilter (Code / Mask) | Dùng cho |
|---|---|---|---|---|---|
| `HRH_Rx_0x2B0` | FULL | RECEIVE | CanController_0 | 0x2B0 / 0x7FF | CDD_CanTest echo |
| `HRH_Rx_Diag` | BASIC | RECEIVE | CanController_0 | 0x7C0 / 0x7C0 | 0x7E0 + 0x7DF (UDS) |
| `HTH_Tx_0x3A0` | FULL | TRANSMIT | CanController_0 | – | CDD_CanTest 100 ms |
| `HTH_Tx_Diag_0x7E8` | FULL | TRANSMIT | CanController_0 | – | UDS response |

![Config_image_83.png](../Images/MCAL_Config/Config_image_83.png)

![Config_image_84.png](../Images/MCAL_Config/Config_image_84.png)

Object RECEIVE bắt buộc có filter: tab **CanHwFilter** → **+** → mở → nhập Code/Mask (gõ `0x2B0` được, Tresos tự đổi sang thập phân 688).

![Config_image_56.png](../Images/MCAL_Config/Config_image_56.png)

![Config_image_57.png](../Images/MCAL_Config/Config_image_57.png)

> **Giải thích filter:** frame được nhận khi `(ID & Mask) == (Code & Mask)`. Mask 0x7FF = khớp đúng 1 ID. Mask 0x7C0 = chỉ so 5 bit cao → nhận 0x7C0…0x7FF, gồm cả 0x7DF và 0x7E0; CanIf lọc tiếp theo PDU.

![Config_image_58.png](../Images/MCAL_Config/Config_image_58.png)

![Config_image_59.png](../Images/MCAL_Config/Config_image_59.png)

![Config_image_60.png](../Images/MCAL_Config/Config_image_60.png)

![Config_image_61.png](../Images/MCAL_Config/Config_image_61.png)

Kết quả: 4 object, Can hết lỗi (còn 1 error của Mem).

![Config_image_62.png](../Images/MCAL_Config/Config_image_62.png)

> **Lưu ý MB8/9/16/17 trong Bảng 7:** RTD tự xếp mailbox theo thứ tự object (Can Object ID 0..3), không cho chọn số MB trực tiếp. Điều quan trọng với tầng trên là **handle** (`HRH_Rx_0x2B0` = 0...), không phải số MB vật lý. Ghi nhận để cập nhật Bảng 7.

`Ctrl+Shift+S`.

---

## 11. Mem_43_INFLS – vùng flash

_<-- Back to [Table of Contents](#table-of-contents)_

1. Double-click **Mem_43_INFLS** → tab General: giữ **Mem Access Code Erase/Write = 0x1FFF8100** (code xoá/ghi chạy từ RAM – bắt buộc vì không thể vừa chạy code vừa ghi cùng 1 bank flash).

![Config_image_63.png](../Images/MCAL_Config/Config_image_63.png)

2. Tab **MemInstance** → **Add required elements** (hoặc +) → `MemInstance_0`.

![Config_image_64.png](../Images/MCAL_Config/Config_image_64.png)

3. Mở `MemInstance_0` → tab **MemSectorBatch** → **+** → mở. Mặc định là D-Flash (`FLS_DATA_ARRAY_0...`, 0x10000000):

![Config_image_65.png](../Images/MCAL_Config/Config_image_65.png)

4. **Mem Physical Sector** → gõ `FLS_CODE` để lọc → chọn `FLS_CODE_ARRAY_0_BLOCK_0_S032`.

![Config_image_66.png](../Images/MCAL_Config/Config_image_66.png)

> **Giải thích:** P-Flash S32K144 chia sector 4 KB. Sector 32 = 32 × 0x1000 = **0x0002_0000** = đầu vùng App.

5. **Mem Start Address** đang đỏ (vẫn là địa chỉ D-Flash) → mũi tên → **Set manually edited** rồi lại mũi tên → **Calculate value** → `0x20000`. Làm tương tự **Mem Erase Sector Size** → `0x1000`.

![Config_image_67.png](../Images/MCAL_Config/Config_image_67.png)

6. **Mem Number Of Sectors** = **96** (0x20000 → 0x7FFFF = 384 KB / 4 KB). Name = `PFlash_App_0x20000`.

![Config_image_68.png](../Images/MCAL_Config/Config_image_68.png)

> Vùng 0x0000_0000–0x0001_FFFF (Bootloader) **không** khai báo → Mem từ chối xoá/ghi vùng BL.

`Ctrl+Shift+S` → **Problems View: 0 error** (còn 4 warning, xem 12.3).

---

## 12. Platform – ngắt và Generate

_<-- Back to [Table of Contents](#table-of-contents)_

#### <ins>12.1 Bảng ngắt<ins>

Không cấu hình bước này vẫn generate được, nhưng ISR không chạy → Gpt/Can không có ngắt.

1. Double-click **Platform** → tab **Interrupt Controller** → **+** → mở `IntCtrlConfig_0` → tab **Interrupt Configuration**.

![Config_image_69.png](../Images/MCAL_Config/Config_image_69.png)

![Config_image_70.png](../Images/MCAL_Config/Config_image_70.png)

2. **+** → mở dòng. Mặc định `DMA0_IRQn`, `undefined_handler`:

![Config_image_71.png](../Images/MCAL_Config/Config_image_71.png)

3. **Interrupt Name** → gõ để lọc → chọn, tick **Interrupt Enabled**, nhập **Priority** và **Handler**:

![Config_image_72.png](../Images/MCAL_Config/Config_image_72.png)

| Interrupt Name | Priority | Handler |
|---|---|---|
| `LPIT0_Ch0_IRQn` | 3 | `LPIT_0_CH_0_ISR` |
| `CAN0_ORed_0_15_MB_IRQn` | 2 | `CAN0_ORED_0_15_MB_IRQHandler` |
| `CAN0_ORed_16_31_MB_IRQn` | 2 | `CAN0_ORED_16_31_MB_IRQHandler` |
| `CAN0_ORed_IRQn` | 2 | `CAN0_ORED_IRQHandler` |

![Config_image_73.png](../Images/MCAL_Config/Config_image_73.png)

![Config_image_74.png](../Images/MCAL_Config/Config_image_74.png)

> **Giải thích:** số priority nhỏ = ưu tiên cao. CAN (2) cao hơn tick (3) để không mất frame. Tên handler phải trùng tên hàm ISR trong code RTD – lấy theo ví dụ `9_CAN_driver` của Bootcamp; sai tên → build vẫn qua nhưng ngắt nhảy vào handler mặc định.

#### <ins>12.2 Generate<ins>

1. `Ctrl+Shift+S` → chuột phải `MockECU_Cfg (CORTEXM, S32K14X)` → **Generate Project**.

![Config_image_75.png](../Images/MCAL_Config/Config_image_75.png)

Nếu còn error, Tresos hỏi *Project contains errors... start generation?* → **No**, quay lại sửa.

![Config_image_76.png](../Images/MCAL_Config/Config_image_76.png)

2. Kết quả trong `firmware/common/mcal_cfg/`:

| Thư mục | File mới của Mock |
|---|---|
| `include/` | `Can_43_FLEXCAN_Cfg.h`, `Gpt_Cfg.h`, `LPit_Gpt_Ip_Cfg.h`, `Mem_43_INFLS_Cfg.h`, `Port_Cfg.h`, `Dio_Cfg.h`, `IntCtrl_Ip_Cfg.h`... (59 file) |
| `src/` | `Can_43_FLEXCAN_PBcfg.c`, `FlexCAN_Ip_PBcfg.c`, `Gpt_PBcfg.c`, `Mem_43_INFLS_Cfg.c`, `Port_Ci_Port_Ip_PBcfg.c`, `IntCtrl_Ip_Cfg.c`... (30 file) |
| `output/` | `*.epc` (10 file) |

#### <ins>12.3 Warning còn lại (không chặn)<ins>

| Warning | Ý nghĩa | Xử lý |
|---|---|---|
| `EcuMOSResource`, `EcuMDefaultAppMode` does not refer to nodes | EcuM demo của template trỏ OS không có | Bỏ qua (Mock dùng EcuM tự viết) |
| `CanSupportTTCANRef`, `CanCpuClockRefAlternate` | Tham chiếu tuỳ chọn để trống | Bỏ qua |
| Error Log: *User should add CanIf into user's configuration* | Generator Can nhắc chưa có CanIf trong project | Bỏ qua – CanIf lấy từ classic-platform, cấu hình tay ở `cfg/` |

![Config_image_77.png](../Images/MCAL_Config/Config_image_77.png)

![Config_image_78.png](../Images/MCAL_Config/Config_image_78.png)

---

## 13. Define sinh ra – dùng trong code

_<-- Back to [Table of Contents](#table-of-contents)_

Đọc thật từ `firmware/common/mcal_cfg/include` sau khi generate:

| File | Define | Từ đâu ra |
|---|---|---|
| `Dio_Cfg.h` | `DioConf_DioChannel_LED_RED ((uint16)0x006fU)` | Name kênh Dio. 0x6F = 111 = 3×32+15 |
| `Dio_Cfg.h` | `DIO_FLIP_CHANNEL_API (STD_ON)` | Checkbox Dio Flip Channel Api |
| `Port_Cfg.h` | `PortConf_PortPin_CAN0_RX_PTE4  3` | Name pin, số = index trong bảng |
| `Gpt_Cfg.h` | `GptConf_GptChannelConfiguration_GptChannel_Tick1ms (0U)` | Name kênh Gpt |
| `Can_43_FLEXCAN_Cfg.h` | `HRH_Rx_0x2B0 ((Can_HwHandleType)0U)` … `HTH_Tx_Diag_0x7E8 (3U)` | Name hardware object = handle cho CanIf |
| `Mcu_Cfg.h` | `McuClockSettingConfig_0`, `McuModeSettingConf_0` | Name container Mcu |

Ví dụ dùng:
```c
Mcu_Init(&Mcu_Config);
Mcu_InitClock(McuClockSettingConfig_0);
Mcu_SetMode(McuModeSettingConf_0);
Port_Init(&Port_Config);
Gpt_Init(&Gpt_Config);
Gpt_EnableNotification(GptConf_GptChannelConfiguration_GptChannel_Tick1ms);
Gpt_StartTimer(GptConf_GptChannelConfiguration_GptChannel_Tick1ms, 8000U); /* 1 ms @ 8 MHz */
Dio_WriteChannel(DioConf_DioChannel_LED_RED, STD_LOW);                    /* LED sáng */
```

**Muốn đổi / thêm define:**

| Muốn | Làm ở | Không làm |
|---|---|---|
| Đổi tên `LED_RED` | Name trong Dio → Generate → sửa code | Sửa `Dio_Cfg.h` (generate lại là mất) |
| Thêm LED / chân | PortPin (mục 7) + DioChannel (mục 8) | |
| Bật API (vd Dev Error Detect) | Checkbox tab General của module | `#define` tay |
| Tên ngắn kiểu ứng dụng | Header của mình, vd `App_IoMap.h`: `#define LED_ERR DioConf_DioChannel_LED_RED` | Thêm vào file sinh ra |
| Thiếu tính năng MCAL | Wrapper/CDD trong code mình | Sửa `common/mcal/*/src` |
| Bug thật trong RTD | Sửa bản copy `common/mcal`, đánh dấu `/* MOCK_PATCH: ... */`, ghi `docs/reports/mcal_patches.md`, commit riêng | Sửa trong `C:\EB\tresos\plugins` |

---

## 14. Lưu ý code tĩnh còn thiếu

_<-- Back to [Table of Contents](#table-of-contents)_

`firmware/common/mcal/Can_43_FLEXCAN` và `Mem_43_INFLS` hiện **trống**. Generate chỉ sinh cấu hình, không copy code tĩnh. Trước khi build phải copy từ plugin (01 – mục 5):

```bash
P=/c/NXP/SW32K1_S32M24x_RTD_R21-11_2.0.0/eclipse/plugins   # đường dẫn plugin thật trên máy (thấy trong Error Log)
for M in Can_43_FLEXCAN Mem_43_INFLS; do
  cp -r $P/${M}_TS_T40D2M20I0R0/{include,src} firmware/common/mcal/$M/
done
```

Nối vào project App/BL làm ở bước sau.

---

## 15. Phần không cấu hình bằng EB Tresos

_<-- Back to [Table of Contents](#table-of-contents)_

Các dòng còn lại của Bảng 7 không thuộc MCAL, nên được viết tay trong file C:

| Nhóm (Bảng 7) | Nằm ở | App | BL |
|---|---|---|---|
| ISO-TP: padding 0xAA, BS 0, STmin 0, timeout 1000 ms | `cfg/CanTp_Cfg.c` | ✓ | ✓ |
| UDS: P2 / P2* / S3, session, security, buffer Dcm | `cfg/Dcm_Cfg.h`, `cfg/Dcm_LCfg.c` | 256 B, level 01 | 1026 B, level 11 |
| Lịch chạy MainFunction | `common/ecum/Os_Sched.c` | ✓ | ✓ |
| Bus-off 10 ms / 1000 ms | `cfg/CanSM_Cfg.c` | ✓ | ✓ |
| Phân vùng bộ nhớ | `Project_Settings/Linker_Files/app.ld`, `bl.ld` | app.ld | bl.ld |
| Cờ vào BL 0x2000_6FF0, CRC-32 | `common/boot_shared/Boot_Shared.h` | ✓ | ✓ |
| Det bật / tắt | Symbol `DET_ENABLED` theo cấu hình build | Debug | Debug |
| Cờ build `-Wall -Wextra` | Project Properties của S32DS | ✓ | ✓ |

## 16. Kiểm chứng

_<-- Back to [Table of Contents](#table-of-contents)_

| Bước | Cách kiểm | Kết quả đúng |
|---|---|---|
| Generate | EB Tresos → Generate Project | 0 lỗi, 0 cảnh báo |
| Build | S32DS build `application` và `bootloader` | 0 lỗi |
| Clock | Đọc thanh ghi SCG bằng debugger | SYS = FIRC 48 MHz, SOSCDIV2 = 8 MHz |
| Chân | Đọc `PORTE->PCR[4]`, `PCR[5]` | MUX = 5 |
| Tick | Toggle LED trong task 10 ms, đo scope | Chu kỳ 20 ms |
| CAN | Gửi frame bằng PCAN 500 kbit/s | ECU ACK, đo 1 bit = 2,000 µs |
