# Portable Halo engine slices (Track B)

Freestanding C compiled to WASM for the browser viewer. Logic here is intended
to converge with reimplementations validated on Track A (`halo-re` XBE patch).

Until RE’d bodies land, modules may contain **scaffolded** implementations
documented as such — replace with binary-matched C as each function is reversed.

## Layout

```
engine/
  include/          public headers
  src/
    collision_bsp.c   structure-BSP queries (collision_usage slice)
    player_control.c  biped desire / move / jump (player_control slice)
    wasm_api.c        WASM exports (engine_* + legacy phys_* aliases)
  tests/golden/       raycast / step fixtures (fill from xemu captures)
  build.sh            → web/public/engine.wasm
```

## Build

Requires wasi-sdk under `toolchain/` (same as legacy `physics/build.sh`):

```bash
./engine/build.sh
```

## Viewer hook

[`web/src/physics.js`](../web/src/physics.js) loads `/engine.wasm` (falls back
to `/halo_phys.wasm` if missing). HUD shows `wasm-engine` when the engine core
is active.
