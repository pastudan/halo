# halo-ring

[![Track A decompilation](https://img.shields.io/endpoint?url=https://pastudan.github.io/halo/badge.json)](https://pastudan.github.io/halo/)
[![Ported functions](https://img.shields.io/endpoint?url=https://pastudan.github.io/halo/functions-badge.json)](https://github.com/pastudan/halo)
[![Unit Tests & Progress](https://github.com/pastudan/halo/actions/workflows/unit-tests-progress.yml/badge.svg)](https://github.com/pastudan/halo/actions/workflows/unit-tests-progress.yml)

**OG Halo, in the browser — via binary-faithful engine slices, not approximations.**

Eventually: the whole ring.

Track A progress detail: [`docs/DECOMP_PROGRESS.md`](docs/DECOMP_PROGRESS.md).

## Vision

Halo: Combat Evolved's campaign takes place *on* Installation 04 — but the game only ever
lets you touch ten small slices of it. The idea:

1. **Port OG Halo to the web browser** (WebGL/WASM) by reimplementing engine subsystems
   against the real binary ([stianeklund/halo](https://github.com/stianeklund/halo) / halo-re methodology), then
   compiling portable slices to WASM.
2. **Build the full ring.** Lay the original game's levels out across a complete, contiguous
   Halo ring — a megastructure ~10,000 km in circumference — with each OG level anchoring its
   region of the ring.
3. **Segment the ring into 1000+ parcels.** Each segment is ownable (NFT). Owners can build:
   create their own geometry inside their segment and commit it to IPFS, with the chain holding
   the canonical pointer. The ring becomes a persistent, player-authored world grown around the
   original campaign geometry.
4. **Massively multiplayer.** Everyone explores the same ring.

## Status / Roadmap

Dual-track plan (see [`docs/ENGINE.md`](docs/ENGINE.md)):

| Phase | Goal | Status |
|-------|------|--------|
| **0** | RE lab: `docs/ENGINE.md`, portable [`engine/`](engine/) WASM skeleton, viewer hook | done |
| **1** | Collision + `player_control` slice in `engine/` (denser biped hull); replace POC phys | scaffolded* |
| **2** | Stage-program materials (`stages.json` + strict interpreter) | scaffolded* |
| **3** | Thin end-to-end Silent Cartographer walk | integrated |
| **4** | Deepen: object collision, glass/plasma, fog, bumped cubemap; upstream to halo-re | docs/stubs |
| **5+** | Remaining campaign levels → ring / multiplayer / NFT | planned ([`docs/CAMPAIGN.md`](docs/CAMPAIGN.md)) |

\*Scaffolded = structure and browser path land now; **binary-matched** bodies require Track A
(Xbox XBE + Ghidra/xemu). Place `cachebeta.xbe` (MD5 `c7869590a1c64ad034e49a5ee0c02465`) in
`halo-re/halo-patched/` to unlock validation.

Also:

- [x] **POC geometry** — Silent Cartographer (`b30`) both BSPs in the browser
- [x] Tag-driven textures / lightmaps / scenery extractors
- [ ] Full binary-matched `player_control` / `collision_usage` (Track A)
- [ ] Rasterizer bind RE → regenerate `stages.json` from engine C

## How it works

```
Track A (truth)                         Track B (browser)
Xbox cachebeta.xbe                      PC Trial b30.map
  → halo-re C + XBE patch                 → tools/extract_*.py
  → xemu validate                           → engine/*.c → engine.wasm
                                            → stages.json → WebGL interpreter
                                            → web/ three.js shell
```

- **Engine** ([`engine/`](engine/)): freestanding C → WASM. Modules named after halo-re
  (`collision_bsp`, `player_control`). Build with `engine/build.sh`.
- **Materials**: [`tools/extract_stage_programs.py`](tools/extract_stage_programs.py) compiles
  shader tags into stage programs; [`web/src/stage_materials.js`](web/src/stage_materials.js)
  interprets them strictly.
- **Extraction** (`tools/`): MEK (`reclaimer`/`refinery`) dumps geometry, collision, shaders,
  scenery from the Trial cache until a RE’d tag loader exists.
- **halo-re/**: local clone for Track A (gitignored). Not shipped; see their README for XBE setup.

## Quickstart

```bash
# 1. Python env + extraction deps
python3 -m venv .venv
.venv/bin/pip install reclaimer refinery Pillow

# 2. Provide game files (see Legal): place b30.map and bitmaps.map in assets/

# 3. Extract + compile stage programs + build engine WASM
.venv/bin/python tools/extract_bsp.py assets/b30.map web/public
.venv/bin/python tools/extract_collision.py assets/b30.map web/public
.venv/bin/python tools/extract_shaders.py assets/b30.map web/public
.venv/bin/python tools/extract_stage_programs.py web/public/shaders.json web/public/stages.json
.venv/bin/python tools/extract_scenery.py assets/b30.map web/public
./engine/build.sh

# 4. Run the viewer
cd web && npm install && npm run dev
```

Debug: `?fly` enables noclip (disabled by default). `?jsphys` forces JS physics fallback.
HUD shows `WALK [wasm-engine]` when Track B is active.

## Legal

This repository contains **no game assets**. Halo: Combat Evolved is © Microsoft / Bungie.
The extraction pipeline runs against the **freely-distributed Halo Trial** (the official demo
Microsoft/Gearbox released for PC, which contains The Silent Cartographer), or your own copy of
the game. Extracted geometry/texture artifacts (`assets/`, `web/public/*.glb`) are derived from
copyrighted content and are gitignored — they must not be redistributed.

Xbox retail executables for Track A validation are likewise never committed; you must supply
`cachebeta.xbe` yourself (see [`docs/ENGINE.md`](docs/ENGINE.md)).

This is a research / preservation / interoperability project in the same spirit as
[halo-re](https://github.com/halo-re/halo). The NFT/ownership layer of the vision is an open
design question — selling anything derived from Microsoft's IP would require rights that this
project does not have; the ownership concept may ultimately apply only to player-authored
segments and original geometry.
