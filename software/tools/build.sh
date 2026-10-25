#!/usr/bin/env bash
# Headless build of the S32DS projects (application, bootloader) and memory map checks.
#
# usage: software/tools/build.sh [application|bootloader|all] [Debug_FLASH|Release_FLASH|all]
#
# Environment:
#   S32DS_ROOT  S32 Design Studio install dir (default: C:/NXP/S32DS.3.6.10)
#
# All paths are relative to the repository; a temporary Eclipse workspace is used so
# the repository never receives a .metadata folder.

set -u

REPO_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
S32DS_ROOT="${S32DS_ROOT:-C:/NXP/S32DS.3.6.10}"
S32DSC="$S32DS_ROOT/eclipse/s32dsc.exe"
GCC_BIN="$S32DS_ROOT/S32DS/build_tools/gcc_v11.4/gcc-11.4-arm32-eabi/bin"
OBJDUMP="$GCC_BIN/arm-none-eabi-objdump"

PROJECTS="${1:-all}"
CONFIGS="${2:-all}"
[ "$PROJECTS" = "all" ] && PROJECTS="bootloader application"
[ "$CONFIGS" = "all" ] && CONFIGS="Debug_FLASH Release_FLASH"

TIMEOUT_S=600

to_win() { if command -v cygpath >/dev/null 2>&1; then cygpath -w "$1"; else echo "$1"; fi; }

if [ ! -x "$S32DSC" ] && [ ! -f "$S32DSC" ]; then
    echo "ERROR: s32dsc not found at $S32DSC (set S32DS_ROOT)" >&2
    exit 2
fi

WS="$(mktemp -d)"
LOG="$WS/build.log"
trap 'rm -rf "$WS"' EXIT

args=(-nosplash -application org.eclipse.cdt.managedbuilder.core.headlessbuild -data "$(to_win "$WS")")
expected=0
for p in $PROJECTS; do
    args+=(-import "$(to_win "$REPO_ROOT/firmware/$p")")
    for c in $CONFIGS; do
        args+=(-cleanBuild "$p/$c")
        expected=$((expected + 1))
    done
done

echo "Building: $PROJECTS ($CONFIGS)"
"$S32DSC" "${args[@]}" >"$LOG" 2>&1 &
pid=$!

# s32dsc may keep running after the last build: wait for the build results, then stop it.
elapsed=0
while kill -0 "$pid" 2>/dev/null; do
    done_count=$(grep -cE 'Build (Finished|Failed)' "$LOG" 2>/dev/null || true)
    [ "${done_count:-0}" -ge "$expected" ] && break
    [ "$elapsed" -ge "$TIMEOUT_S" ] && { echo "ERROR: timeout after ${TIMEOUT_S}s" >&2; break; }
    sleep 2
    elapsed=$((elapsed + 2))
done
sleep 2
kill "$pid" 2>/dev/null
command -v taskkill >/dev/null 2>&1 && taskkill //F //IM s32dsc.exe >/dev/null 2>&1

grep -E '(error|warning):' "$LOG" | sed -E "s#.*/firmware/#firmware/#" | sort | uniq
grep -E 'Build (Finished|Failed)' "$LOG"

rc=0
grep -q 'Build Failed' "$LOG" && rc=1
[ "$(grep -cE 'Build Finished' "$LOG")" -lt "$expected" ] && rc=1

# Memory map checks (docs/Mock.docx 1.10)
check_section() { # elf section expected_vma
    local vma
    vma=$("$OBJDUMP" -h "$1" | awk -v s="$2" '$2 == s { print $4 }')
    if [ "$vma" = "$3" ]; then echo "  OK   $2 @ 0x$vma"; else echo "  FAIL $2 @ 0x${vma:-none} (expected 0x$3)"; rc=1; fi
}
for p in $PROJECTS; do
    for c in $CONFIGS; do
        elf="$REPO_ROOT/firmware/$p/$c/$p.elf"
        [ -f "$elf" ] || { echo "FAIL missing $elf"; rc=1; continue; }
        echo "$p/$c:"
        check_section "$elf" .boot_noinit 20006ff0
        if [ "$p" = "bootloader" ]; then
            check_section "$elf" .flash_interrupts 00000000
            check_section "$elf" .flash_config 00000400
        else
            check_section "$elf" .flash_interrupts 00020000
            if "$OBJDUMP" -h "$elf" | grep -q '\.flash_config'; then echo "  FAIL .flash_config present"; rc=1; else echo "  OK   no .flash_config"; fi
        fi
        "$GCC_BIN/arm-none-eabi-size" "$elf" | tail -1
    done
done

exit $rc
