# halo-ring

**OG Halo, in the browser. Eventually: the whole ring.**

## Vision

Halo: Combat Evolved's campaign takes place *on* Installation 04 — but the game only ever
lets you touch ten small slices of it. The idea:

1. **Port OG Halo to the web browser** (WebGL/WASM). No install, click a link, you're on the beach
   of the Silent Cartographer.
2. **Build the full ring.** Lay the original game's levels out across a complete, contiguous
   Halo ring — a megastructure ~10,000 km in circumference — with each OG level anchoring its
   region of the ring.
3. **Segment the ring into 1000+ parcels.** Each segment is ownable (NFT). Owners can build:
   create their own geometry inside their segment and commit it to IPFS, with the chain holding
   the canonical pointer. The ring becomes a persistent, player-authored world grown around the
   original campaign geometry.
4. **Massively multiplayer.** Everyone explores the same ring. Walk (or fly, or drive) from the
   Pillar of Autumn's crash site to the Silent Cartographer's island, passing through hundreds of
   player-built segments on the way.

## Status / Roadmap

- [x] **Proof of concept** — The Silent Cartographer (`b30`) level geometry extracted from the
  original game files and rendered in the browser, navigable with WASD + mouse or gamepad.
  Both BSPs work: the island exterior and the underground map room.
- [ ] **Textures** — real diffuse maps + the original baked lightmaps. *(in progress)*
- [ ] **Physics** — faithful reimplementation of Halo's player movement (30Hz tick, collision
  BSP, biped movement constants from the actual game tags), in C compiled to WASM. *(in progress)*
- [ ] Remaining 9 campaign levels through the same pipeline.
- [ ] Ring assembly: level regions placed on a true ring; ring-scale sky/horizon (you should see
  the ring arc overhead from the ground).
- [ ] Multiplayer presence (shared exploration).
- [ ] Segment ownership + player-authored geometry on IPFS.

## How it works

```
Halo Trial (b30.map, bitmaps.map)          [not in repo — see Legal]
        │
        │  tools/extract_bsp.py        (refinery + reclaimer parse the cache file)
        ▼
glTF (.glb) render geometry + spawn.json + collision BSP + movement constants
        │
        │  web/ (three.js viewer)
        ▼
Browser: WASD/gamepad navigation, WASM physics tick
```

- **Extraction** (`tools/`): Python. Loads the Halo 1 PC-demo cache format via
  [refinery](https://pypi.org/project/refinery/)/[reclaimer](https://pypi.org/project/reclaimer/)
  (the MEK toolset), walks the `scenario_structure_bsp` tags, and exports render geometry
  (positions/normals/UVs/lightmap UVs per shader material) to GLB, plus textures decoded from
  the game's DXT bitmaps.
- **Viewer** (`web/`): Vite + three.js. Pointer-lock mouse look, WASD, gamepad, walk/fly modes.
- **Physics** (`physics/`): C, compiled to WASM. Structured after the original engine's layout
  (see [halo-re](https://github.com/halo-re/halo)'s `kb.json`: `point_physics`, `player_control`,
  `collision_usage`), running a fixed 30 ticks/sec update against the level's real collision BSP
  with movement constants pulled from the `cyborg` biped tag.

`halo-re/` is a local clone of the [halo-re](https://github.com/halo-re/halo) decompilation
project, used as reference for engine structure and naming. It is not built as part of this
project.

## Quickstart

```bash
# 1. Python env + extraction deps
python3 -m venv .venv
.venv/bin/pip install reclaimer refinery Pillow

# 2. Provide game files (see Legal): place b30.map and bitmaps.map in assets/

# 3. Extract geometry + textures
.venv/bin/python tools/extract_bsp.py assets/b30.map web/public

# 4. Run the viewer
cd web && npm install && npm run dev
```

## Legal

This repository contains **no game assets**. Halo: Combat Evolved is © Microsoft / Bungie.
The extraction pipeline runs against the **freely-distributed Halo Trial** (the official demo
Microsoft/Gearbox released for PC, which contains The Silent Cartographer), or your own copy of
the game. Extracted geometry/texture artifacts (`assets/`, `web/public/*.glb`) are derived from
copyrighted content and are gitignored — they must not be redistributed.

This is a research / preservation / interoperability project in the same spirit as
[halo-re](https://github.com/halo-re/halo). The NFT/ownership layer of the vision is an open
design question — selling anything derived from Microsoft's IP would require rights that this
project does not have; the ownership concept may ultimately apply only to player-authored
segments and original geometry.
