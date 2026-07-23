#!/bin/sh
# Build halo_phys.c -> web/public/halo_phys.wasm (freestanding wasm32).
set -e
cd "$(dirname "$0")"
CLANG=../toolchain/wasi-sdk-33.0-arm64-macos/bin/clang
$CLANG --target=wasm32 -O2 -nostdlib \
  -Wl,--no-entry \
  -Wl,-z,stack-size=1048576 \
  -o ../web/public/halo_phys.wasm \
  halo_phys.c
ls -la ../web/public/halo_phys.wasm
