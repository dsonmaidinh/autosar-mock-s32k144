# 01 – Setup EB Tresos cho Mock ECU

Phần này chỉ lo **setup**: hiểu các file, các công cụ, đưa project `MockECU_Cfg` về trạng thái generate được code vào `firmware/common/` và build được. **Cấu hình chi tiết từng module ở [Hướng dẫn 02](02_MockECU_MCAL_Config.md).**

## Table of Contents
1. [**Overview: các file và ý nghĩa**](#1-overview-các-file-và-ý-nghĩa)
2. [**Công cụ**](#2-công-cụ)
3. [**Hiện trạng**](#3-hiện-trạng)
4. [**Thao tác cơ bản trong EB Tresos**](#4-thao-tác-cơ-bản-trong-eb-tresos)
5. [**Copy code tĩnh MCAL vào common**](#5-copy-code-tĩnh-mcal-vào-common)
6. [**Nối vào project S32DS**](#6-nối-vào-project-s32ds)
7. [**Troubleshooting**](#7-troubleshooting)
8. [**Checklist**](#8-checklist)

---

## 1. Overview: các file và ý nghĩa

_<-- Back to [Table of Contents](#table-of-contents)_

Có 4 loại file, khác nhau ở chỗ **ai tạo ra** và **có được sửa tay không**:

| Loại | Ở đâu (repo) | Ai tạo ra | Sửa tay? |
|---|---|---|---|
| **Cấu hình** (`.xdm`) | `firmware/mcal_config/MockECU_Cfg/config/` | Bạn, qua giao diện EB Tresos | Chỉ sửa qua EB Tresos |
| **Code sinh ra** (`*_Cfg.h`, `*_PBcfg.c`...) | `firmware/common/mcal_cfg/` | EB Tresos khi Generate | **Không** – generate lại là mất |
| **Code tĩnh MCAL** (`Dio.c`, `Can_43_FLEXCAN.c`...) | `firmware/common/mcal/` | NXP (RTD 2.0.0), copy từ plugin | **Không** |
| **Code của bạn** (main, EcuM, BSW, App, FBL) | `firmware/common/{ecum,bsw,...}`, `application/src`, `bootloader/src` | Bạn | Có |

### 1.1 Project EB Tresos `MockECU_Cfg`

| File | Ý nghĩa |
|---|---|
| `.project` | File Eclipse: tên project, để EB Tresos nhận ra project |
| `.prefs/pref_general.xdm` | Cài đặt project: `ECUId`, `Target = CORTEXM`, `Derivate = S32K14X`, `ConfigurationPath = config`, **`GenerationPath`** (nơi đổ code ra) |
| `config/<Module>.xdm` | Toàn bộ giá trị cấu hình của 1 module (XML). Mỗi module trong cây ứng với 1 file |
| `config/SystemModel2.tdb` | Database nội bộ (cache) của EB Tresos. Không sửa |

Cây Project Explorer:
```
MockECU_Cfg                          ← project (thư mục)
├── MockECU_Cfg (CORTEXM, S32K14X)   ← "ECU configuration": chuột phải ở ĐÂY để Module Configurations / Verify / Generate
│   └── BaseNXP, Can_43_FLEXCAN, Dio, EcuM, Gpt, Mcu, Mem_43_INFLS, Platform, Port, Resource
└── config/*.xdm                     ← file thật trên đĩa
```

### 1.2 Code sinh ra – `firmware/common/mcal_cfg/`

| File | Ý nghĩa |
|---|---|
| `include/<Module>_Cfg.h` | Define pre-compile: bật/tắt API, số kênh, tên symbolic (`DioConf_DioChannel_...`) |
| `include/<Module>_PBcfg.h`, `src/<Module>_PBcfg.c` | Struct cấu hình (vd `Mcu_Config`, `Port_Config`) truyền vào `<Module>_Init()` |
| `include/*_Ip_Cfg*.h`, `src/*_Ip_*.c` | Cấu hình lớp IP (driver mức thanh ghi bên dưới API AUTOSAR): Clock_Ip, Port_Ci_Port_Ip, Gpio_Dio_Ip, IntCtrl_Ip... |
| `include/modules.h` | Danh sách module có trong project |
| `output/*.epc` | Bản xuất cấu hình chuẩn AUTOSAR (ECUC), không dùng khi build |

Ví dụ thật khi generate template: `Dio_Cfg.h/.c`, `Mcu_Cfg.h`, `Mcu_PBcfg.c`, `Clock_Ip_PBcfg.c`, `Port_Cfg.h`, `Port_PBcfg.c`, `Port_Ci_Port_Ip_PBcfg.c`, `Platform_Cfg.c`, `IntCtrl_Ip_Cfg.c`, `OsIf_Cfg.c`...

### 1.3 Code tĩnh MCAL – `firmware/common/mcal/`

```
<Module>/include/   Dio.h, Dio_Ipw.h, Gpio_Dio_Ip.h ...   ← API
<Module>/src/       Dio.c, Dio_Ipw.c, Gpio_Dio_Ip.c ...   ← code, đọc define từ *_Cfg.h
```
Code tĩnh `#include "Dio_Cfg.h"` → **cùng 1 code tĩnh** chạy với mọi cấu hình. Vì vậy App và BL dùng chung `common/mcal` + `common/mcal_cfg`.

---

## 2. Công cụ

_<-- Back to [Table of Contents](#table-of-contents)_

| Công cụ | Dùng để | Bước |
|---|---|---|
| **EB tresos Studio 29.0** (`C:\EB\tresos`) | Cấu hình MCAL, kiểm tra lỗi, generate code | 4 |
| **RTD 2.0.0 plugins** `<Module>_TS_T40D2M20I0R0` | Mỗi plugin có: (1) schema – các ô cấu hình bạn thấy, (2) generator – template sinh `*_Cfg.h/.c`, (3) code tĩnh `include/`, `src/`, (4) `examples/EBT/S32K1` | 5 |
| **Tài liệu RTD** `<Module>_UM` / `_IM` (trong `reference/github/AUTOSAR-MCAL-Embedded-Upskilling-Bootcamp/Documentation`) | Giải thích từng ô cấu hình, thứ tự init | Khi cần |
| **Git Bash / VS Code** | Copy file, xem và diff code sinh ra | 5 |
| **S32DS 3.6 / GCC 11.4** (hoặc `make` của template) | Build `application`, `bootloader` | 6 |
| **Ozone / S32DS Debugger** | Nạp, debug trên board | 6 |

Plugin nằm ở `C:\EB\tresos\plugins\` hoặc `C:\NXP\SW32K1_S32M24x_RTD_R21-11_2.0.0_P04\eclipse\plugins\` (theo README Bootcamp) – kiểm tra máy bạn dùng chỗ nào.

---

## 3. Hiện trạng

_<-- Back to [Table of Contents](#table-of-contents)_

| Mục | Trạng thái |
|---|---|
| `MockECU_Cfg` import vào workspace (không copy) | ✅ |
| ECU ID `MockECU_Cfg`, Target `CORTEXM`, Derivate `S32K14X` | ✅ |
| Default Generation Path = `..\..\common\mcal_cfg` | ✅ |
| Module từ template: BaseNXP, Dio, EcuM, Mcu, Platform, Port, Resource | ✅ |
| Module thêm mới: Can_43_FLEXCAN, Gpt, Mem_43_INFLS | ✅ đã thêm, **chưa cấu hình** → 7 lỗi, xử lý ở [02 – mục 4](02_MockECU_MCAL_Config.md#4-sửa-lỗi-sau-khi-thêm-module) |
| `firmware/common/mcal` có code tĩnh | ❌ → mục 5 |
| Project S32DS nối với MCAL | ❌ → mục 6 |

---

## 4. Thao tác cơ bản trong EB Tresos

_<-- Back to [Table of Contents](#table-of-contents)_

#### <ins>4.1 Đổi đường dẫn generate (đã làm)<ins>
Chuột phải `MockECU_Cfg` → **Properties** → **Configuration Project → Code Generator** → *Default Generation Path* = `..\..\common\mcal_cfg` (tính từ thư mục project; `..\..` = `firmware\`). Ô bị mờ thì tick *Use project specific settings*. Trang **ECU Configuration** cùng nhóm để xem ECU ID / Target / Derivate.

#### <ins>4.2 Thêm / bớt module<ins>
1. Mở `MockECU_Cfg` → **chuột phải dòng con `MockECU_Cfg (CORTEXM, S32K14X)`** → **Module Configurations...**
2. Cột **Available Modules** → mở **No Cluster** → click module (vd `Gpt (V2.0.0, AS4.7.0)`).
3. Bấm **mũi tên trên cùng** giữa 2 cột → module sang cột **Module Configurations** (Enable + Generate tick sẵn, file `config\<Module>.xdm`).
4. **OK**.

> - Trang *Properties → Configuration Project → Modules* chỉ để xem, mũi tên ở đó không thêm module vào project.
> - Module in mờ ở Available Modules = đã có trong project.
> - Bỏ tick **Generate** = giữ cấu hình nhưng không sinh code cho module đó.

#### <ins>4.3 Mở editor 1 module<ins>
Double-click module trong cây. Mỗi ô:
- icon **bút chì**: giá trị bạn đặt.
- icon *calculated*: giá trị tự tính – bấm icon cạnh ô để chuyển sang tự đặt.
- Danh sách có nút **+** để thêm phần tử.

Lưu: `Ctrl+S`.

#### <ins>4.4 Verify và Generate<ins>
- **Verify Project** (chuột phải dòng ECU configuration) → xem **Problems View**.
- **Generate Project** (chuột phải hoặc icon búa).
  Còn lỗi thì EB Tresos hỏi *"Project contains errors... start generation?"* → chọn **No**, sửa lỗi trước.
- Thành công: *Errors "0"*, code ra `firmware/common/mcal_cfg/`.

---

## 5. Copy code tĩnh MCAL vào common

_<-- Back to [Table of Contents](#table-of-contents)_

Git Bash ở gốc repo:
```bash
TPL=reference/github/AUTOSAR-MCAL-Embedded-Upskilling-Bootcamp/Tresos_Workspace/0_Template_Initial_File/template-s144
cp -r $TPL/Autosar/Mcal/* firmware/common/mcal/          # Base, Platform, Rte, Mcu, Port, Dio
```
Module template chưa có – lấy `include/` + `src/` từ plugin:
```bash
P=/c/EB/tresos/plugins        # hoặc /c/NXP/SW32K1_S32M24x_RTD_R21-11_2.0.0_P04/eclipse/plugins
for M in Gpt Can_43_FLEXCAN Mem_43_INFLS; do
  mkdir -p firmware/common/mcal/$M && cp -r $P/${M}_TS_T40D2M20I0R0/{include,src} firmware/common/mcal/$M/
done
```
Kiểm tra: mỗi `common/mcal/<Module>/` có `include/` và `src/`.

---

## 6. Nối vào project S32DS

_<-- Back to [Table of Contents](#table-of-contents)_

Làm cho cả `application` và `bootloader` (Project → Properties → C/C++ Build → Settings):
- **Linked Folder**: `PARENT-1-PROJECT_LOC/common/mcal`, `PARENT-1-PROJECT_LOC/common/mcal_cfg`.
- **Include paths**: `common/mcal/<Module>/include`, `common/mcal/Base/header`, `common/mcal/Platform/startup/include`, `common/mcal_cfg/include`.
- **Symbols** (lấy từ makefile template): `S32K1XX S32K144 GCC USE_SW_VECTOR_MODE DISABLE_MCAL_INTERMODULE_ASR_CHECK ENABLE_FPU`.
- Exclude `Project_Settings/Startup_Code` nếu dùng startup của RTD (`Platform/startup`).

Kiểm tra setup: `main.c` gọi `Mcu_Init(&Mcu_Config); Mcu_InitClock(McuClockSettingConfig_0); Mcu_SetMode(McuModeSettingConf_0); Port_Init(&Port_Config);` → build OK. (Cần generate thành công trước – xem 02.)

---

## 7. Troubleshooting

_<-- Back to [Table of Contents](#table-of-contents)_

| Hiện tượng | Nguyên nhân | Cách xử lý |
|---|---|---|
| Không thấy *Module Configurations...* | Chuột phải nhầm dòng project | Chuột phải dòng `MockECU_Cfg (CORTEXM, S32K14X)` |
| Mũi tên ở Properties → Modules không làm gì | Trang đó không quản lý module | Dùng hộp thoại 4.2 |
| Code ra `MockECU_Cfg/Build/cfg` | Generation path chưa đổi | Mục 4.1 |
| `Code generator canceled. Errors "1"` | Còn lỗi cấu hình | [02 – mục 4](02_MockECU_MCAL_Config.md#4-sửa-lỗi-sau-khi-thêm-module) |
| Available Modules không có Gpt/Can/Mem | Thiếu plugin | Kiểm tra thư mục plugins (mục 2) |
| Build không thấy `*_Cfg.h` | Thiếu include `common/mcal_cfg/include` | Mục 6 |

---

## 8. Checklist

_<-- Back to [Table of Contents](#table-of-contents)_

- [x] `MockECU_Cfg` import, generation path `..\..\common\mcal_cfg`
- [x] Đủ module trong Module Configurations
- [ ] `common/mcal` có code tĩnh (mục 5)
- [ ] S32DS nối include / linked folder / symbols (mục 6)
- [ ] → Sang [Hướng dẫn 02](02_MockECU_MCAL_Config.md) để cấu hình và generate
