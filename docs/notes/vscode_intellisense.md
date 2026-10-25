# Ghi chú: VSCode IntelliSense

Phạm vi: `.vscode/`, `firmware/{application,bootloader,common}/.vscode/`, `mock-ecu-s32k144.code-workspace`, `software/tools/gen_vscode.py`.

## 1. Mở thư mục nào cũng nhận diện được file

| Mở trong VSCode | Cấu hình C/C++ | Ghi chú |
|---|---|---|
| Thư mục gốc repo | `Application`, `Bootloader` | Chọn cấu hình ở thanh trạng thái (góc dưới phải) theo file đang sửa |
| `firmware/application` | `Application` | |
| `firmware/bootloader` | `Bootloader` | |
| `firmware/common` | `Application`, `Bootloader` | Header Cfg lấy từ `cfg/` của image đang chọn |
| `mock-ecu-s32k144.code-workspace` | Mỗi thư mục dùng cấu hình riêng | Nên dùng cách này: App và BL tự đúng, không cần chuyển cấu hình |

## 2. Nguồn của cấu hình

- `gen_vscode.py` đọc include và define của C compiler trong cấu hình **Debug_FLASH** ở `.cproject`. Vì vậy VSCode nhìn code giống hệt S32DS, kể cả `DET_ENABLED`.
- **Sửa `.cproject` thì chạy lại:** `python software/tools/gen_vscode.py`, rồi commit các file `.vscode/*.json` thay đổi.
- Mọi đường dẫn đều dạng `${workspaceFolder}/...` (tương đối).
- `S32DS_ROOT` (khối `env` trong `c_cpp_properties.json`) là giá trị duy nhất phụ thuộc máy, dùng làm `compilerPath` (NXP GCC 11.4). Máy cài S32DS ở chỗ khác thì sửa hằng `S32DS_ROOT` trong `gen_vscode.py` rồi chạy lại.

## 3. Loại trừ

- `reference/**` bị loại khỏi IntelliSense và kết quả tìm kiếm. classic-platform có `CanIf.h`, `Dcm.h`… trùng tên, nếu không loại thì "Go to Definition" sẽ nhảy nhầm sang bản 4.0.3. Muốn tìm trong `reference/` thì mở trực tiếp hoặc tắt `search.exclude`.
- `Debug_FLASH/`, `Release_FLASH/` (output build) và `mcal/Spi` (chưa cấu hình) cũng bị loại.

## 4. Liên kết kiểu file

- `*.h` → C (không phải C++). `*.xdm`, `*.epc` (EB Tresos), `.cproject`, `.project`, `*.launch` → XML.

## 5. Git

- `.gitignore` chỉ giữ lại `c_cpp_properties.json`, `settings.json`, `extensions.json` trong mọi thư mục `.vscode`. Các file cá nhân như `launch.json` hay `tasks.json` của riêng bạn vẫn bị ignore.
