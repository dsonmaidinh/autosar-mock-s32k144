# Ghi chú: Startup RTD, linker và memory map

Phạm vi: `firmware/bootloader/Project_Settings/Linker_Files/bl.ld`, `firmware/application/Project_Settings/Linker_Files/app.ld`, `firmware/common/mcal/Platform/startup/`, `firmware/common/boot_shared/Boot_Shared.h`.
Liên quan: `docs/Mock.docx` mục 1.10, 1.11; BL_SRS_001…004, BL_SRS_012; RSK-03.

## 1. RamInit của RTD xoá SRAM, trong đó có cờ boot

- `startup_cm4.s` (nhãn `RamInit`) ghi 0 vào toàn bộ vùng `[__INT_SRAM_START, __INT_SRAM_END)` để khởi tạo ECC của SRAM.
- Trong linker gốc của RTD, `__INT_SRAM_END = 0x2000_7000`, tức là vùng xoá bao luôn cờ boot ở `0x2000_6FF0`. App ghi cờ, reset sang BL, và cờ đã bị xoá trước khi BL kịp đọc.
- **Đã sửa:** trong cả `bl.ld` và `app.ld`, `__INT_SRAM_END = ORIGIN(int_sram_noinit)` (= `0x2000_6FF0`).
- **Hệ quả:** sau **power-on reset**, 16 byte ở `0x2000_6FF0` chưa được khởi tạo ECC. Đọc vùng này có thể gây lỗi ECC.
  → `BM_CheckBootRequest()` phải kiểm tra nguyên nhân reset trước (`RCM->SRS`, bit `RCM_SRS_POR_MASK`). Nếu là POR thì ghi (xoá) record trước, rồi mới đọc ở các lần reset sau.
- Điểm này đã ghi trong comment của `bl.ld` và `BM_Request.h`.

## 2. Bảng vector và VTOR

- RTD đặt `USE_SW_VECTOR_MODE`: startup copy bảng vector từ flash (`.flash_interrupts`) sang RAM (`.sram_interrupts`), rồi ghi `VTOR = __RAM_INTERRUPT_START`.
- App **không cần** tự ghi `SCB->VTOR = 0x0002_0000` như doc B-02 ghi. Startup của App copy bảng vector từ `0x0002_0000` (`int_flash_interrupts` trong `app.ld`) rồi trỏ VTOR vào bản copy trên RAM.
- BL vẫn phải ghi `VTOR = 0x0002_0000` trước khi nhảy (BL_SRS_003), vì đoạn từ lúc nhảy tới lúc startup của App chạy xong vẫn có thể xảy ra exception.

## 3. Flash Configuration Field (0x400) chỉ thuộc BL

- `startup_cm4.s` luôn sinh section `.flash_config`, cả khi build App.
- `app.ld` bỏ section này bằng `/DISCARD/ : { *(.flash_config) }`. Nếu không bỏ, linker sẽ tự đặt section mồ côi này vào đâu đó trong vùng flash của App (RSK-03).
- `build.sh` kiểm tra: App **không** có `.flash_config`; BL có `.flash_config` ở `0x0000_0400`.

## 4. Các vùng không link

- Sector metadata `0x0007_F000–0x0007_FFFF` không nằm trong `app.ld`: `int_flash` của App kết thúc ở `0x0007_EFFF`. Chỉ FBL ghi vùng này.
- Code của BL dừng ở `0x0001_FFFF` (`int_flash` dài `0x1_FBF0`). Cần theo dõi kích thước qua file `.map` (OP-BL-01, RSK-06).

## 5. Stack và vùng noinit

- Stack: `0x2000_6000`, dài `0xFF0` (giảm 16 byte so với RTD).
- `.boot_noinit` (NOLOAD) ở `0x2000_6FF0`, dài `0x10`. Biến đặt vào đây bằng `BOOT_SHARED_NOINIT` (`__attribute__((section(".boot_noinit")))`).
- `Boot_RequestType` có compile-time check kích thước bằng đúng 16 byte (`Boot_Shared.h`).

## 6. `-ffunction-sections` và section mồ côi của RTD

- Cả hai project bật `-ffunction-sections` và `--gc-sections`. Khi đó NXP GCC đổi tên section của RTD theo từng hàm: `.mcal_text` → `.mcal_text.Mcu_Init`, `.mcal_const_cfg` → `.mcal_const_cfg.<var>`…
- Linker gốc của RTD chỉ khớp tên chính xác (`*(.mcal_text)`), nên các section `.mcal_text.*` thành **section mồ côi**. ld tự chèn chúng sau section có cùng thuộc tính, ở đây là `int_flash_config` (16 byte ở `0x400`), gây lỗi `will not fit in region int_flash_config` (lần đầu tràn 3516 B).
- **Vì sao develop vẫn build được:** khi chưa có ai gọi hàm MCAL (EcuM/BM còn thân trống), `--gc-sections` bỏ hết các section này, nên không có section mồ côi. Lỗi chỉ lộ ra khi có code gọi Mcu/Port/Dio thật (ví dụ `Test_LedBlink` trên `test/bootloader`, hoặc khi implement `EcuM_AL_DriverInitOne`). Linker cũ đã sai từ đầu, chỉ là chưa bị kích hoạt.
- **Đã sửa** (commit `fix(linker): place RTD sections ...` trên `feature/bootloader` cho `bl.ld` và `feature/application` cho `app.ld`): thêm pattern `.*` cạnh tên gốc trong `bl.ld` và `app.ld`: `mcal_text`, `mcal_const*`, `mcal_data*`, `mcal_bss*`, `ramcode`, `acfls/acmem/acmcu_code_rom`. Không tắt `-ffunction-sections`, vì tắt thì gc không bỏ được code thừa nữa và binary to ra.
- Cách kiểm tra: trong `.map` không được có section `.mcal_*` nào nằm ngoài output section đã khai báo, và `arm-none-eabi-nm` phải cho địa chỉ hàm MCAL trong `int_flash`, không nằm ở `0x400–0x40F`.
