# Plan: tài liệu hướng dẫn linker script (lấy `bl.ld` làm ví dụ)

Trạng thái: **nháp, chờ duyệt**.
Output dự kiến: `docs/guides/03_Linker_Script_Bootloader.md`, nối tiếp `01_Setup_EB_Tresos.md` và `02_MockECU_MCAL_Config.md`.

## 0. Mục tiêu và người đọc

**Người đọc:** sinh viên hoặc dev embedded mới vào dự án. Đã biết C và biết cơ bản MCU là gì, nhưng chưa từng đọc linker script.

**Sau khi đọc xong, người đọc làm được (mục tiêu đo được):**
1. Vẽ lại memory map của S32K144: Flash, SRAM_L, SRAM_U. Chỉ ra BL, App, stack và cờ boot nằm ở đâu.
2. Đọc `bl.ld` và trả lời được với một biến hoặc hàm bất kỳ: nó nằm ở đâu khi nạp (LMA), ở đâu khi chạy (VMA), và ai copy hoặc xoá nó.
3. Mở `bootloader.map` để tìm địa chỉ và kích thước của một hàm, biết module nào chiếm nhiều flash nhất, và biết section nào bị `--gc-sections` bỏ.
4. Tự sửa cấu hình một cách an toàn: đổi kích thước vùng BL, thêm một vùng noinit, thêm một section mới, chỉnh heap hoặc stack. Biết cách kiểm tra bằng `build.sh`, `objdump -h` và file `.map`.
5. Tự chẩn đoán được hai lỗi thật đã gặp trong dự án: section mồ côi tràn vào `int_flash_config`, và RamInit xoá mất cờ boot.

## 1. Phương pháp sư phạm

- **Đi từ tổng quan tới chi tiết (zoom-in):** chip → bản đồ bộ nhớ → pipeline build → cấu trúc file `.ld` → từng khối → file `.map` → thực hành. Mỗi bước chỉ thêm một lớp khái niệm mới.
- **Một ví dụ xuyên suốt:** theo dấu 4 "nhân vật" từ file `.c` tới địa chỉ trên chip:
  - một hàm (`Dio_FlipChannel`)
  - một hằng (`Port_Config`, nằm ở `.mcal_const_cfg`)
  - một biến có giá trị khởi tạo (`.data`)
  - một biến không khởi tạo (`.bss`)
  - và thêm cờ `.boot_noinit`

  Mỗi chương gặp lại cả 4 nhân vật, nhờ vậy người đọc thấy mạch liền.
- **Phép so sánh dễ nhớ:**
  - `MEMORY` là "lô đất".
  - `SECTIONS` là "bản xếp đồ vào lô".
  - Input section là "thùng hàng" do compiler đóng.
  - LMA là "địa chỉ kho" và VMA là "địa chỉ sử dụng". Startup là "người bốc hàng" từ kho ra chỗ dùng.
- **Số liệu thật:** dùng `objdump -h` và `.map` của chính dự án, không dùng ví dụ tự bịa.
- **Ngăn hiểu nhầm:** mỗi chương có một ô "Hay nhầm", ví dụ:
  - `NOLOAD` không có nghĩa là không chiếm RAM.
  - `ALIGN(2048)` có thể làm phí RAM.
  - `*(.text)` không khớp `.text.foo`.
- **Kiểm tra hiểu:** cuối mỗi chương có 2–3 câu hỏi ngắn; đáp án đặt ở phụ lục.
- **Bài thực hành:** chương cuối có bài tập trên code thật, kèm cách tự kiểm chứng kết quả.

## 2. Pipeline của tài liệu (mục lục chi tiết)

### Chương 1. Vì sao cần linker script

Bức tranh 1 trang: cùng một code C, nhưng nếu không có linker script thì linker không biết flash bắt đầu từ 0x0, cũng không biết RAM bắt đầu từ 0x1FFF8000.

Linker script trả lời 3 câu hỏi:
- Chip có những vùng nhớ nào?
- Đặt cái gì vào vùng nào?
- Startup cần những địa chỉ nào để chạy?

### Chương 2. Bộ nhớ của S32K144 (phần cứng)

- **Flash 512 KB:**
  - P-Flash bắt đầu từ 0x0000_0000, sector 4 KB.
  - Vùng Flash Configuration Field ở 0x400–0x40F: các byte bảo mật, FSEC và FOPT. Ghi sai chỗ này có thể **khoá chip**.
- **SRAM 64 KB** chia 2 khối:
  - SRAM_L: 0x1FFF_8000–0x1FFF_FFFF
  - SRAM_U: 0x2000_0000–0x2000_6FFF

  Hai khối liền địa chỉ nên linker coi như một vùng (`int_sram`). Có ECC, nên phải ghi khởi tạo trước khi đọc. Đây là lý do có `RamInit`.
- **Bảng vector Cortex-M4:**
  - Phần cứng đọc SP ban đầu ở 0x0 và Reset vector ở 0x4.
  - `VTOR` cho phép chuyển bảng vector sang chỗ khác.
- **Hình 1:** memory map của cả chip, chia BL, App, metadata, RAM. Lấy từ `docs/Mock.docx` 1.10.

### Chương 3. Từ `.c` đến `.elf`: pipeline build trong S32DS

Hình 2: `.c/.s` → compiler (`.o` chứa **input section**) → linker (+ `bl.ld`) → `.elf` (**output section**) → `.map`, `.siz`, `.srec/.hex` → debugger nạp vào flash.

- S32DS lấy linker script ở đâu: trong `.cproject`, mục `scriptfile = ${ProjDirPath}/Project_Settings/Linker_Files/bl.ld`. Các cờ liên quan: `--gc-sections` và `-ffunction-sections`.
- Input section đến từ đâu:
  - Mặc định là `.text`, `.rodata`, `.data`, `.bss`.
  - Với RTD, cơ chế `<Mod>_MemMap.h` (`MCAL_START_SEC_CODE` → `.mcal_text`…) đổi tên section.
  - Khi bật `-ffunction-sections`, tên section có thêm hậu tố `.<tên hàm>`. Nối sang chương 9.
- Debugger chỉ nạp những gì có **LMA nằm trong flash**. RAM được dựng lúc chạy.

### Chương 4. Cấu trúc tổng thể của `bl.ld`

Bản đồ file theo dòng, để người đọc biết mình đang ở đâu:

| Khối | Dòng | Vai trò |
|---|---|---|
| Header + comment memory map | 1–34 | Bản tóm tắt của dự án |
| `MEMORY` | 37–47 | Khai báo "lô đất" |
| `HEAP_SIZE`, `ENTRY` | 50–52 | Tham số và điểm vào |
| `SECTIONS`, phần flash | 57–124 | Vector, flash config, code và hằng |
| `SECTIONS`, phần RAM | 126–222 | exidx, vector RAM, data, bss, code Fls, heap, results, noinit |
| Symbol cho startup | 224–264 | "Hợp đồng" giữa linker và startup |

Cú pháp tối thiểu cần biết (chỉ những gì file dùng):
- `.` (location counter)
- `ALIGN`
- `KEEP`
- `*(pattern)`
- `> region`
- `AT(addr)`
- `NOLOAD`
- `PROVIDE`
- `ORIGIN()`, `LENGTH()`, `ADDR()`, `DEFINED()`

### Chương 5. Khối `MEMORY`: chia lô đất

- Giải thích từng dòng trong 8 region, kèm bảng: start, end, size, và lý do chọn kích thước đó.
- Vì sao `int_flash` dài `0x1FBF0`: để vùng BL kết thúc đúng ở 0x1FFFF, chừa phần còn lại cho App.
- Vì sao **không** khai báo vùng App trong `bl.ld`: BL không link vùng đó, chỉ FBL ghi vào lúc chạy.
- Vì sao stack giảm 16 byte và có `ram_rsvd2` dài 0: dùng làm mốc cuối SRAM.
- **Hay nhầm:** region chỉ là giới hạn. Region không tự đặt gì vào trong; việc đặt là của `SECTIONS`.

### Chương 6. Khối `SECTIONS`, phần flash

Dạy theo từng output section, mỗi cái trả lời 4 câu: gom gì, đặt vào region nào, vì sao theo thứ tự này, và ai dùng nó.

- **`.flash_interrupts`:**
  - `KEEP(*(.intc_vector))`. Vì sao cần `KEEP`: không có `KEEP` thì `--gc-sections` sẽ bỏ, vì không ai "gọi" bảng vector.
  - `ALIGN(2048)` ở địa chỉ 0 không tốn gì.
  - Các symbol `__interrupts_rom_*`.
- **`.flash_config`:** 16 byte cố định ở 0x400. Liên hệ BL_SRS_012. App bỏ section này bằng `/DISCARD/` (so sánh với `app.ld`).
- **`.flash`:** thứ tự gom gồm startup/systeminit → text → mcal_text → code Fls (`acfls_*`) → init/fini → rodata → mcal_const* → `__init_table`/`__zero_table` → `acmcu_code_rom` → `_etext`/`__DATA_ROM`.
  - Giải thích pattern `*(.x)` và `*(.x.*)`.
  - Vì sao `__DATA_ROM` đứng cuối: đó là nơi đặt **bản gốc** của `.data` trong flash.
- **Số liệu thật:** `.flash` = 0x60C0 byte tại 0x410, tức BL mới dùng khoảng 24 KB trên khoảng 127 KB.

### Chương 7. Khối `SECTIONS`, phần RAM: LMA và VMA

Đây là chương **trọng tâm**, dạy chậm.

- **Hình 3:** biến `.data` có 2 địa chỉ. LMA = 0x64D0 (trong flash), VMA = 0x1FFF_8B10 (trong RAM). Startup copy từ LMA sang VMA.
- **`.sram_data AT(__DATA_ROM)`:** gom `.ramcode`, `.data` và `mcal_data*`.
- **`.sram_bss (NOLOAD)`:** không có bản trong flash, startup ghi 0. `ALIGN(16)`.
- **`.sram_interrupts`:** chỉ chừa chỗ (`. += size`), startup copy bảng vector vào đây rồi ghi VTOR.
  - **Hay nhầm (số thật):** section dài 0xA08 trong khi bảng vector chỉ 0x310. Lý do là `ALIGN(2048)` (yêu cầu căn lề của VTOR theo kích thước bảng) làm phí khoảng 0x6F8 byte RAM.
- **`.acfls_code_ram`:** chừa chỗ để chạy code ghi flash từ RAM. Lý do: không đọc lệnh từ flash được trong lúc chính flash đó đang bị xoá hoặc ghi. Các symbol `Fls_AC*` và `_ERASE/_WRITE_FUNC_ADDRESS_`.
- **`.heap`:** `HEAP_SIZE` có giá trị mặc định 0x200, và có thể ghi đè bằng `__heap_size__`.
- **`int_results`:** 256 byte ở 0x1FFF8000, dùng cho RTD.
- **`.boot_noinit`:**
  - Vùng `NOLOAD` nằm ngoài vùng RamInit xoá.
  - Cờ boot dùng chung giữa App và BL.
  - Rủi ro ECC sau power-on reset (link sang `docs/notes/startup_linker_memory.md` mục 1).
- **`.ARM.exidx` / `.ARM.extab`:** dùng cho unwind C++. Với dự án C thuần thì kích thước gần như bằng 0.
  - **Điểm cần soi:** section này đặt `> int_sram` nhưng không có `AT`, nên LMA nằm trong RAM. Debugger không nạp được nội dung. Dự án không dùng exception nên không sao, nhưng cần ghi chú cho người đọc biết. Cần xác nhận lại trước khi viết.

### Chương 8. Symbol: "hợp đồng" giữa linker và startup

Dòng 224–264, đặt cạnh trình tự khởi động thật:

**Hình 4:** pipeline reset theo `startup_cm4.s` và `startup.c`:
1. Reset_Handler
2. Đặt SP = `__Stack_start_c0`
3. RamInit: xoá `[__INT_SRAM_START, __INT_SRAM_END)` để khởi tạo ECC
4. SystemInit
5. `init_data_bss`: dùng `__INIT_TABLE` để copy `.data`, dùng `__ZERO_TABLE` để xoá `.bss`, copy bảng vector sang RAM
6. Ghi VTOR = `__RAM_INTERRUPT_START`
7. `main`

Kèm theo là bảng symbol → file dùng nó → mục đích. Ví dụ:
- `__RAM_INIT = 1` bật RamInit.
- `__INT_SRAM_END = ORIGIN(int_sram_noinit)` là chỗ dự án sửa so với bản gốc của RTD.

**Kết của chương:** quay lại 4 nhân vật và chỉ ra ai chạm vào từng nhân vật, vào lúc nào.

### Chương 9. Đọc file `.map`

Học trên `firmware/bootloader/Debug_FLASH/bootloader.map`. Các phần của file theo thứ tự:
1. Archive members (vì sao kéo theo một file của newlib)
2. **Discarded input sections** (những gì `--gc-sections` đã bỏ)
3. **Memory Configuration**
4. **Linker script and memory map**

Kỹ năng thực hành:
- Tìm một hàm: tìm tên hàm, đọc cột địa chỉ, kích thước, file `.o`.
- Đọc một dòng input section dạng `.mcal_text.Dio_FlipChannel 0x... 0x.. ./common/...Dio.o`.
- Tính dung lượng còn trống của một region.
- Dò section mồ côi: section `.mcal_*` nằm lạc sau `.flash_config`.
- Công cụ phụ trợ:
  - `arm-none-eabi-size` (text/data/bss có nghĩa gì; vì sao flash dùng = text + data)
  - `objdump -h` (cột VMA/LMA)
  - `nm --size-sort`

**Case study 1:** lỗi section mồ côi khi bật `-ffunction-sections`. Lỗi tràn 3516 B, vì sao develop không lộ lỗi, cách sửa. Tóm tắt từ notes mục 6.

### Chương 10. Quản lý bộ nhớ trong thực tế: cấu hình và kiểm tra

- **Checklist khi sửa `.ld`:**
  1. Sửa `MEMORY` và comment ở đầu file cho khớp nhau.
  2. Giữ ranh giới BL/App ở 0x20000 cho khớp với `app.ld` và `Boot_Shared.h`.
  3. Chạy `build.sh` (có kiểm tra memory map).
  4. Soát `.map`.
- **Công thức nhanh:** flash dùng = `.flash` + `.sram_data` (bản LMA). RAM dùng = data + bss + vector RAM + heap + stack.
- **So sánh `bl.ld` với `app.ld`:** một bảng các điểm khác nhau (origin 0x20000, `/DISCARD/ .flash_config`…).
- **Case study 2:** RamInit xoá mất cờ boot. Nguyên nhân, cách sửa `__INT_SRAM_END`, hệ quả ECC sau power-on reset.

### Chương 11. Bài tập thực hành (có cách tự kiểm chứng)

1. Tìm địa chỉ và kích thước của `Test_LedBlink` và `Port_Init` trong `.map`, rồi đối chiếu bằng `nm`.
2. Thêm một biến `uint32 g_counter = 5;`, rồi trả lời: LMA và VMA của nó là gì? Flash tăng bao nhiêu?
3. Đổi `HEAP_SIZE` thành 0x400, rồi xem section nào dịch chuyển.
4. (Suy nghĩ, không commit) Nếu BL vượt 128 KB thì lỗi linker trông thế nào, và phải sửa những file nào?
5. Giải thích vì sao bỏ `KEEP` ở `.flash_interrupts` thì chip không chạy được.

### Phụ lục

- A. Bảng tra nhanh cú pháp linker script dùng trong dự án.
- B. Đáp án câu hỏi cuối chương.
- C. Danh sách file cần mở khi học:
  - `bl.ld`, `app.ld`
  - `startup_cm4.s`, `startup.c`
  - `Mcu_MemMap.h` (ví dụ MemMap)
  - `Boot_Shared.h`
  - `bootloader.map`
  - `docs/notes/startup_linker_memory.md`
- D. Tài liệu ngoài: GNU ld manual (Scripts), S32K1xx Reference Manual (Memory map, Flash config field), ARMv7-M ARM (VTOR).

## 3. Phạm vi: có gì và không có gì

**Có:** mọi kiến thức cần để hiểu và tự sửa `bl.ld` của dự án.

**Không soạn**, vì không thật sự cần cho mục tiêu:
- Cú pháp ld nâng cao chưa dùng: `OVERLAY`, `INSERT`, `SORT`…
- Linker của IAR/GHS (thư mục `ghs/` và `iar/`)
- Chi tiết thuật toán FBL ghi flash
- MPU, cache: S32K144 không có cache dữ liệu đáng kể, nên `no_cacheable` chỉ nhắc một câu.

## 4. Hình minh hoạ cần vẽ (Mermaid hoặc ASCII trong md)

1. Memory map của toàn chip, chia BL, App, RAM.
2. Pipeline build `.c` → `.o` → linker → `.elf` → `.map` → nạp flash.
3. LMA và VMA của `.data`, mũi tên copy do startup thực hiện.
4. Trình tự reset và symbol mà mỗi bước dùng.
5. Sơ đồ phóng to SRAM với vị trí từng section theo số thật của `objdump -h`.

## 5. Các bước thực hiện (sau khi duyệt)

1. Lấy số liệu thật: `objdump -h`, các phần của `.map`, `nm`. Build từ nhánh nào thì ghi rõ commit đó vào tài liệu.
2. Xác minh hai điểm chưa chắc trước khi viết:
   - Hành vi LMA của `.ARM.exidx`.
   - Lý do chính xác của `ALIGN(2048)` cho bảng vector RAM: tra yêu cầu căn lề VTOR trong ARMv7-M.
3. Viết chương 1–4: tổng quan.
4. Viết chương 5–8: chi tiết `bl.ld` và startup.
5. Viết chương 9–11 và phụ lục.
6. Rà soát: mỗi số liệu phải có nguồn (file hoặc lệnh), mỗi chương phải có câu hỏi kiểm tra, và các link tới notes phải đúng.
7. Commit `docs(guides): add linker script guide for the bootloader`. Nhánh và việc push do người dùng quyết định.

## 6. Cần người dùng chốt

- Tên file và vị trí output: `docs/guides/03_Linker_Script_Bootloader.md`, được không?
- Viết bằng tiếng Việt, giữ nguyên thuật ngữ tiếng Anh (section, region, LMA/VMA…), được không?
- Có cần chương so sánh `app.ld` đầy đủ không, hay chỉ một bảng điểm khác nhau như ở chương 10?
- Commit lên nhánh nào?
