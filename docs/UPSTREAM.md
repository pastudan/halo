# Upstream: Track A decompilation

Track A uses a local clone at `halo-re/` of
**[stianeklund/halo](https://github.com/stianeklund/halo)** (fork of
[halo-re/halo](https://github.com/halo-re/halo)).

Upstream `halo-re/halo` last moved in 2023 (~18 C files). The stianeklund fork
is the active frontier (~54% functions ported, same XBE pin). Prefer coordinating
with / contributing to that fork; open PRs against `halo-re/halo` only when a
change is small and clearly wanted on the historical tree.

## Local setup

```bash
# clone (directory name kept for path stability)
git clone https://github.com/stianeklund/halo.git halo-re

# stage pin + retail maps (never commit these)
# cachebeta.xbe MD5 c7869590a1c64ad034e49a5ee0c02465
# = Oct 12 2001 prototype 2276betaP.xbe renamed
cp …/2276betaP.xbe halo-re/halo-patched/cachebeta.xbe
# + maps/ and bink/ from a retail USA disc extract

docker build -t halo-re-build halo-re
docker run --rm -u $(id -u):$(id -g) -v "$PWD/halo-re":/work -w /work halo-re-build \
  bash -c 'cmake -Bbuild -S. -DCMAKE_TOOLCHAIN_FILE=toolchains/llvm.cmake && cmake --build build'
```

`scripts/check_track_a.sh` verifies the pin MD5 and clone presence.

## Candidates from this repo (portable slices)

| Area | Local path | Upstream target |
|------|------------|-----------------|
| Collision BSP queries | `engine/src/collision_bsp.c` | `src/halo/physics/collision_bsp.c` (`collision_bsp_test_vector` / `FUN_00148eb0`) |
| Player control biped | `engine/src/player_control.c` | desire in `game/player_control.c`; motion in `units/bipeds.c` |
| Texture-stage programs | `tools/extract_stage_programs.py` | docs / tooling (not XBE code) |

## Rules

1. Do not PR scaffolded / approximate bodies as if they were RE’d.
2. Each function must be validated via XBE patch + xemu (or fork equivalence tooling) before upstreaming.
3. Keep `kb.json` decls aligned with the Track A clone.
4. Coordinate on Discord / blam.info / the fork’s lift docs before claiming large frontiers.

## Status

- Pin staged and Docker build OK; local tree tracks [pastudan/halo](https://github.com/pastudan/halo) `track-a-collision-bsp` (from stianeklund).
- Draft lifts: `collision_bsp_test_vector` / `FUN_00148eb0` / `FUN_00148780` (`ported:false`). PR: https://github.com/pastudan/halo/pull/1 (CI green).
- Official verify blocked on VC71 (RXDK) / delinked objs / xemu BIOS — see [`TRACK_A.md`](TRACK_A.md).
