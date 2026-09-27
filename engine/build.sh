#!/bin/sh
# Build portable engine slices → web/public/engine.wasm (+ legacy halo_phys.wasm copy).
set -e
cd "$(dirname "$0")"
ROOT="$(cd .. && pwd)"
CLANG="$ROOT/toolchain/wasi-sdk-33.0-arm64-macos/bin/clang"
if [ ! -x "$CLANG" ]; then
  echo "wasi-sdk clang not found at $CLANG" >&2
  exit 1
fi
OUT="$ROOT/web/public/engine.wasm"
$CLANG --target=wasm32 -O2 -nostdlib \
  -Iinclude \
  -Wl,--no-entry \
  -Wl,-z,stack-size=1048576 \
  -o "$OUT" \
  src/collision_bsp.c \
  src/player_control.c \
  src/wasm_api.c
# Keep legacy filename so old bookmarks / caches still work during migration.
cp "$OUT" "$ROOT/web/public/halo_phys.wasm"
ls -la "$OUT" "$ROOT/web/public/halo_phys.wasm"
