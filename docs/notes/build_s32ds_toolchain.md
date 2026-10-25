# Ghi chú: Build S32DS, toolchain và cấu hình project

Phạm vi: `firmware/{application,bootloader}/.cproject`, `.project`, `software/tools/build.sh`.

## 1. Phải dùng NXP GCC 11.4

- MemMap của RTD dùng `#pragma GCC section`. Chỉ **NXP GCC** (S32DS: `S32DS/build_tools/gcc_v11.4/...`) hỗ trợ pragma này.
- GNU Arm Embedded bản thường (vd. 10.2 trong `C:/Program Files (x86)/GNU Arm Embedded Toolchain`) chỉ báo `-Wunknown-pragmas` rồi **bỏ qua**. Code RTD khi đó không vào đúng section (`.mcal_text`, `.acfls_code_rom`…), và build vẫn "qua".

## 2. Cờ build đã chốt (Debug_FLASH, Release_FLASH)

| Mục | Giá trị | Ghi chú |
|---|---|---|
| Define | `CPU_S32K144HFT0VLLT S32K1XX S32K144 GCC USE_SW_VECTOR_MODE EU_DISABLE_ANSILIB_CALLS I_CACHE_ENABLE ENABLE_FPU` | Theo Makefile ví dụ CAN của NXP. Debug thêm `DET_ENABLED` |
| FPU | `-mfpu=fpv4-sp-d16 -mfloat-abi=hard` | Template S32DS mặc định là **soft-float**. Phải đặt ở cả toolchain lẫn từng tool |
| Thư viện | newlib-nano, nosys (`newlib_nano_noio`) | Template dùng `rdimon` (semihosting) |
| C | `-std=c99 -Wall -Wextra -fno-short-enums -funsigned-char` | |
| Linker | `-nostartfiles -Wl,--no-enum-size-warning --gc-sections` | |

- `-fno-short-enums` làm linker cảnh báo "uses variable-size enums" với libgcc/newlib. Ví dụ NXP cũng gặp, nên tắt bằng `--no-enum-size-warning`.
- `DET_ENABLED` điều khiển `<MOD>_DEV_ERROR_DETECT` trong `cfg/<Mod>_Cfg.h`.

## 3. Đã bỏ template S32DS

- Đã xoá `Project_Settings/Startup_Code`, `include/` (device header SDK) và `S32K144_64_{flash,ram}.ld`.
- `include/S32K144.h` của template **trùng tên** với `mcal/Base/header/S32K144.h` của RTD, nên không được đưa lại vào include path.
- Đã bỏ cấu hình `Debug_RAM`/`Release_RAM`, vì không có linker RAM phù hợp với memory map Mock.

## 4. Đường dẫn: luôn tương đối

- `.project`: linked folder `common` → `PARENT-1-PROJECT_LOC/common`.
- `.cproject`: include và linker dùng `${ProjDirPath}/...` hoặc `${ProjDirPath}/../common/...`.
- File `*.args`/`makefile` trong `Debug_FLASH/` chứa đường dẫn tuyệt đối. Đây là output build và đã bị ignore, không ảnh hưởng.
- Đường dẫn tuyệt đối duy nhất được phép là đường dẫn **cài tool**: `S32DS_ROOT` (mặc định `C:/NXP/S32DS.3.6.10`) trong `build.sh` và `gen_vscode.py`.

## 5. Sửa `.cproject`

- Đóng S32DS (hoặc close project) trước khi sửa `.cproject` bằng tay hay bằng script, nếu không IDE sẽ ghi đè.
- Sửa xong `.cproject` thì chạy `python software/tools/gen_vscode.py` để VSCode khớp lại (`docs/notes/vscode_intellisense.md`).
- `.settings/language.settings.xml` do S32DS tự sinh (cache `env-hash`), đã ignore và không còn track trong git.

## 6. Headless build (`software/tools/build.sh`)

- `s32dsc.exe` tự thoát sau khi build xong. Script chờ tiến trình thoát, còn timeout (`TIMEOUT_S`) chỉ để kill khi bị treo. Không được đếm số dòng "Build Finished/Failed" (cách cũ): khi thư mục `<config>/` đã có từ lần build trước, `-cleanBuild` chạy clean **2 lần**, và lần clean thứ hai luôn báo `No rule to make target 'clean'` → "Build Failed". Đếm dòng thì script kill `s32dsc` ngay sau bước clean, lần chạy nào sau lần đầu cũng báo thiếu `.elf`.
- Kết quả chỉ tính các dòng của "**** Build of configuration …", bỏ qua "Clean-only build". Lỗi clean thứ hai ở trên cũng xảy ra trong IDE khi bấm Clean 2 lần liên tiếp. Lỗi đó vô hại.
- Dòng "Managed Build system manifest file error … ghs …" là nhiễu của plugin GHS không cài, bỏ qua.
- Một lần build cả 4 cấu hình mất khoảng 4–5 phút, chủ yếu là thời gian S32DS khởi động và import project.
- Cách dùng: `bash software/tools/build.sh [application|bootloader|all] [Debug_FLASH|Release_FLASH|all]`. Script kiểm tra luôn memory map (xem `startup_linker_memory.md`).

## 7. Git

- `.gitignore` cũ có `**/Debug*/`, bắt nhầm `Project_Settings/Debugger/`, nên file `.launch` không được commit. Đã đổi thành `**/Debug_FLASH/`, `**/Release_FLASH/`…
- `.gitattributes`: `*.sh`, `*.py`, `*.json` luôn LF. Nếu không, `build.sh` sẽ hỏng khi clone với `core.autocrlf=true`.
- `git rm` với nhiều pathspec sẽ huỷ **toàn bộ** lệnh nếu có một pathspec không khớp. Kiểm tra `git status` sau mỗi lần xoá.
