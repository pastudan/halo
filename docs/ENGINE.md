# Engine dual-track

This project is pivoting from custom approximations toward **binary-faithful
Halo CE subsystem reimplementation**, then compiling portable slices for the
browser. See the plan: *Halo-re → browser: thin end-to-end*.

## Two tracks

```
Track A (truth)                    Track B (browser)
─────────────────                  ─────────────────
Xbox cachebeta.xbe                 PC Trial b30.map / bitmaps.map
  → reverse in Ghidra/xemu           → MEK extractors (tools/)
  → C in halo-re/src                   → glTF + .cbsp + shaders.json
  → patch.py into XBE                  → engine/*.c → WASM
  → validate in xemu                   → web/ three.js shell
         │                                      ▲
         └──── share portable C ────────────────┘
```

| Track | Role |
|-------|------|
| **A** | Local `halo-re/` clone of [stianeklund/halo](https://github.com/stianeklund/halo) (active fork of [halo-re/halo](https://github.com/halo-re/halo)). XBE patch ground truth. |
| **B** | [`engine/`](../engine/) freestanding C → WASM. No Xbox kernel / D3D. |

`#ifdef HALO_XBE` / `#ifdef HALO_WASM` (or separate translation units) keep
platform glue out of shared logic.

## XBE pin (Track A)

| Item | Value |
|------|-------|
| Version | `01.10.12.2276` |
| MD5 | `c7869590a1c64ad034e49a5ee0c02465` |
| Filename | `cachebeta.xbe` in `halo-re/halo-patched/` |

Without this file, Track A cannot patch or validate. Supply your own copy —
never commit it. See [halo-re/README.md](../halo-re/README.md).

**Note:** The pinned MD5 is **not** Redump retail `default.xbe`. It matches the
Oct 12 2001 / build-2276 **beta** executable (`2276betaP.xbe` from the
“Halo 2276” debug pack), renamed to `cachebeta.xbe`. Retail disc `maps/` +
`bink/` still go alongside it in `halo-patched/`.

Verified locally: Docker `halo-re-build` produces `halo-patched/default.xbe`.

## When to replace POC code

| POC (approximation) | Replaced by | Phase |
|---------------------|-------------|-------|
| [`physics/halo_phys.c`](../physics/halo_phys.c) | [`engine/`](../engine/) collision + player_control | 1 |
| [`web/src/halo_materials.js`](../web/src/halo_materials.js) guesses | Stage-program interpreter ([`web/src/stage_materials.js`](../web/src/stage_materials.js)) | 2 |
| Viewer fly-as-escape | Debug-only (`?fly`) | 3 |

Keep MEK extractors until a RE’d cache/tag loader exists (Phase 4+).

## RE workflow (per function)

1. Discover / confirm symbol in Ghidra against pinned XBE.
2. Add or confirm declaration in `halo-re/kb.json`.
3. Implement in `halo-re/src/halo/**/*.c`; patch; verify in xemu.
4. Port the same logic into `engine/src/` (strip Xbox deps).
5. Rebuild WASM; compare against golden fixtures in `engine/tests/golden/`.
6. When ready, open an upstream PR to [stianeklund/halo](https://github.com/stianeklund/halo) (see [`UPSTREAM.md`](UPSTREAM.md)).

## Priority frontier (thin end-to-end)

From Track A `kb.json` + Silent Cartographer walk path:

1. **`collision_bsp_test_vector` / `FUN_00148eb0`** — structure BSP ray (lift drafted, `ported:false`)
2. **`FUN_00148780`** — leaf → surface resolver used by the vector test
3. Biped integration (`units/bipeds.c` callers) vs portable `engine/src/player_control.c`
4. Shader → D3D texture-stage bind for senv / swat / chicago / soso

## Build

```bash
# Track B WASM
engine/build.sh

# Track A readiness check
scripts/check_track_a.sh

# Track A build (requires XBE in halo-re/halo-patched/ + Homebrew LLVM or Docker)
#   brew install llvm
#   export PATH="/opt/homebrew/opt/llvm/bin:$PATH"
cd halo-re && cmake -Bbuild -S. -DCMAKE_TOOLCHAIN_FILE=$PWD/toolchains/llvm.cmake
cmake --build build
# Or: docker build/run per halo-re/README.md
```

## Community

- Homepage: https://blam.info/
- Progress / call graph: https://blam.info/progress/
- Discord: linked from halo-re README

Coordinate before re-implementing large frontiers already in flight upstream.
