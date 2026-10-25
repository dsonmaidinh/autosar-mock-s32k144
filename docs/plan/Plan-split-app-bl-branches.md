# Plan: tách commit App/BL thành 2 nhánh, merge vào develop và push

Trạng thái: **đã duyệt (26/10/2026)**. Claude làm bước 0–4; người dùng tự làm bước 5–7 (merge App/BL vào develop, push).

Quyết định:
- `fbd8cc5` (refactor common) đưa vào nhánh platform.
- `261653d` (linker) **tách đôi**: `app.ld` → `feature/application`, `bl.ld` → `feature/bootloader`.
- Backup: `feature/platform-mcal-config-bk` = `b0ea2df` (người dùng đã tạo).

## 1. Hiện trạng (26/10/2026)

```
develop                       bb87b68  Merge 'feature/platform-mcal-config' (tới 931555a)
feature/platform-mcal-config  b0ea2df  hơn develop 23 commit, chưa push
main                          4424ff9  hơn origin/main 1 commit (chưa push)
origin (GitHub, private)      chỉ có main = 502d47b
```

23 commit của `feature/platform-mcal-config` tính từ `develop`:

| # | Commit | Nội dung | Đích |
|---|---|---|---|
| 1–11 | `720a2fd` … `1b582c2` | Khung API `firmware/common` (stubs, Det, EcuM, CanIf, PduR, CanTp, Dem, ComM, CanSM, Dcm, boot_shared) | platform (giữ nguyên) |
| 12 | `4275be2` | chore(mcal): Rte SchM | platform (giữ nguyên) |
| 13 | `261653d` | build(linker): `bl.ld` + `app.ld` | **tách đôi** → app / bl |
| 14 | `f7cf3d9` | build(app): `.cproject`/`.project` của application | app |
| 15 | `b9af6dd` | build(bl): `.cproject`/`.project` của bootloader | bl |
| 16 | `fbd8cc5` | refactor(det,cansm): include Cfg sau ConfigType | platform |
| 17 | `38e0ec9` | feat(app): cfg khung của App | app |
| 18 | `f58eb8e` | feat(bl): cfg khung của BL | bl |
| 19 | `ee32230` | feat(app): main + các thành phần App | app |
| 20 | `603612a` | feat(bl): main + BM + FBL | bl |
| 21 | `f36f54f` | ci: `software/tools/build.sh` | platform |
| 22 | `8e60b49` | chore(repo): `.gitignore`, `.gitattributes`, file launch | platform |
| 23 | `b0ea2df` | chore(vscode): cấu hình IntelliSense | platform |

Working tree:

| Thay đổi | Xử lý |
|---|---|
| `firmware/{application,bootloader}/.settings/language.settings.xml` | Chỉ là `env-hash` do S32DS tự ghi → `git restore`, không commit |
| `docs/plan/` | Commit: `Plan-build-API-firmware-common.md` + file plan này |
| `docs/notes/` | Commit: 5 file note theo chủ đề (mục 6) |

## 2. Lịch sử mục tiêu

```
feature/platform-mcal-config  …─4275be2─R─C─V1─V2─D
                                                  \
develop               bb87b68 ────────────────────M1──────────────M2────M3 ──▶ push
                                                   ├─A0─A1─A2─A3──┘      │
                                                   └─B0─B1─B2─B3─────────┘
                                   feature/application (A) / feature/bootloader (B)
```

- **feature/platform-mcal-config** (viết lại từ `4275be2`):
  `4275be2` → `fbd8cc5'` (R) → `f36f54f'` (C) → `8e60b49'` (V1) → `b0ea2df'` (V2) → `docs(plan)` → `docs(notes)` (D).
- **M1:** `merge --no-ff feature/platform-mcal-config` vào `develop`.
- **feature/application** (từ M1): A0 = phần `app.ld` của `261653d` → `f7cf3d9'` → `38e0ec9'` → `ee32230'`.
- **feature/bootloader** (từ M1): B0 = phần `bl.ld` của `261653d` → `b9af6dd'` → `f58eb8e'` → `603612a'`.
- **M2:** merge application vào develop. **M3:** merge bootloader vào develop. Cả hai dùng `--no-ff` (người dùng làm).

## 3. Kiểm tra khả thi

- Các commit app chỉ chạm `firmware/application/**`, commit bl chỉ chạm `firmware/bootloader/**`, nên cherry-pick không xung đột và hai nhánh merge độc lập.
- Phụ thuộc:
  - build(app)/build(bl) cần Rte (`4275be2`, đã ở M1) và linker của image (A0/B0, commit đầu tiên của nhánh).
  - cfg cần `fbd8cc5` (đã ở M1).
  - Vì vậy mỗi nhánh feature build độc lập được.
- `f36f54f`, `8e60b49`, `b0ea2df` chỉ thêm file hoặc sửa `.gitignore`, nên cherry-pick sạch. Có một điểm cần biết:
  - Ở M1, `build.sh` chưa chạy được (`.cproject` còn là template). Nó chỉ chạy được trên từng nhánh feature và trên develop sau M2/M3.
  - Ở M1, cấu hình VSCode đã trỏ tới `src/app`, `cfg/`… của trạng thái cuối. Sau M3, `.cproject` khớp lại nên `gen_vscode.py` **không sinh ra diff**.
- Nhánh chưa từng push nên viết lại history **không ảnh hưởng ai**.

## 4. Các bước

### Bước 0: chuẩn bị (Claude)
```bash
# backup: feature/platform-mcal-config-bk = b0ea2df (người dùng đã tạo)
git restore firmware/application/.settings/language.settings.xml \
            firmware/bootloader/.settings/language.settings.xml
```
Đóng S32DS trong lúc thao tác.

### Bước 1: viết lại feature/platform-mcal-config (Claude)
```bash
git switch -c tmp/platform 4275be2
git cherry-pick fbd8cc5 f36f54f 8e60b49 b0ea2df
git add docs/plan  && git commit     # docs(plan): add API skeleton and branch split plans
git add docs/notes && git commit     # docs(notes): add integration notes per topic
git branch -f feature/platform-mcal-config tmp/platform
git switch feature/platform-mcal-config && git branch -d tmp/platform
```
Kiểm chứng:
- `git log --oneline develop..HEAD` có 11 + 1 + 4 + 2 = 18 commit.
- `git diff b0ea2df HEAD --stat -- firmware/common software .vscode` không có khác biệt.

### Bước 2: merge platform → develop (M1) (Claude)
```bash
git switch develop
git merge --no-ff feature/platform-mcal-config -m "Merge branch 'feature/platform-mcal-config' into develop"
```

### Bước 3: feature/application (Claude)
```bash
git switch -c feature/application develop
git checkout 261653d -- firmware/application/Project_Settings/Linker_Files/app.ld
git commit       # build(linker): add app.ld from RTD linker
git cherry-pick f7cf3d9 38e0ec9 ee32230
bash software/tools/build.sh application all       # 0 lỗi, map OK
```

### Bước 4: feature/bootloader (Claude)
```bash
git switch -c feature/bootloader develop
git checkout 261653d -- firmware/bootloader/Project_Settings/Linker_Files/bl.ld
git commit       # build(linker): add bl.ld from RTD linker
git cherry-pick b9af6dd f58eb8e 603612a
bash software/tools/build.sh bootloader all        # 0 lỗi, map OK
```
Kiểm chứng thêm: ghép thử cả hai nhánh trên một nhánh tạm (`git merge --no-commit`), so `git diff b0ea2df` chỉ khác `docs/`, rồi huỷ (`git merge --abort`, xoá nhánh tạm).

### Bước 5: merge vào develop (M2, M3) (người dùng)
```bash
git switch develop
git merge --no-ff feature/application -m "Merge branch 'feature/application' into develop"
git merge --no-ff feature/bootloader  -m "Merge branch 'feature/bootloader' into develop"
```

### Bước 6: kiểm chứng trên develop (người dùng)
1. `git diff feature/platform-mcal-config-bk develop --stat`: **chỉ** thêm `docs/plan/*` và `docs/notes/*`.
2. `bash software/tools/build.sh all all`: 4 cấu hình 0 lỗi, mọi kiểm tra map OK.
3. `python software/tools/gen_vscode.py && git status`: không có diff.

### Bước 7: push lên GitHub (private repo) (người dùng)
```bash
git push -u origin develop
git push -u origin feature/platform-mcal-config feature/application feature/bootloader
```
- `develop` chứa commit `4424ff9` (scaffold) mà `origin/main` chưa có, nên commit này sẽ lên GitHub qua `develop`. **Không push `main`.**
- Không push nhánh backup `feature/platform-mcal-config-bk`.

## 5. Rollback

- Trước bước 7:
  - `git branch -f feature/platform-mcal-config feature/platform-mcal-config-bk`
  - `git branch -f develop bb87b68`
  - xoá `feature/application`, `feature/bootloader`.
- Sau bước 7: không force-push. Sửa bằng commit mới.

## 6. Ghi chú đi kèm (`docs/notes/`)

| File | Chủ đề |
|---|---|
| `startup_linker_memory.md` | RamInit xoá SRAM và cờ boot, `__INT_SRAM_END`, ECC sau POR, VTOR, `.flash_config` của App, vùng không link |
| `rtd_integration.md` | AR 4.7.0 và inter-module check, `CanIf_Can.h`/`EcuM_Externals.h`, Rte SchM, `Rte_Dem_Type.h`, tên callback Tresos, Mem_43_INFLS access code, Spi, warning `Ram_Ip.c` |
| `build_s32ds_toolchain.md` | NXP GCC và `#pragma GCC section`, cờ build/FPU/newlib, bỏ template, đường dẫn tương đối, `language.settings.xml`, headless build, các bẫy git |
| `bsw_sws_r24-11.md` | Quy ước khung, bảng khác biệt so với classic-platform 4.0.3, chỗ lạ của SWS, thứ tự include Cfg, App và BL, lý do Dcm chưa chia Dsl/Dsd/Dsp |
| `vscode_intellisense.md` | Mở thư mục nào dùng cấu hình nào, chạy lại `gen_vscode.py`, `S32DS_ROOT`, loại `reference/` |

## 7. Quyết định đã chốt

1. `fbd8cc5` vào platform; `261653d` tách đôi vào 2 nhánh feature.
2. Push `develop` + 3 nhánh feature (người dùng tự làm).
3. `language.settings.xml`: `git restore`, vẫn track file.
