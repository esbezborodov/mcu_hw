#!/usr/bin/env bash
# Build and flash the board through the on-board ST-LINK.
# Usage: ./flash.sh [debug|release]
set -euo pipefail

PRESET="${1:-debug}"
ELF="build/${PRESET}/encoder_7seg.elf"

"$(dirname "$0")/build.sh" "$PRESET"

openocd -f board/st_nucleo_f103rb.cfg \
    -c "program ${ELF} verify reset exit"
