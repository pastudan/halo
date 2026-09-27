# Campaign levels (Phase 5+)

Thin end-to-end on Silent Cartographer (`b30`) must land before expanding.

## Pipeline per level

1. Obtain legal map cache (retail / Trial as applicable).
2. Run extractors:
   ```bash
   .venv/bin/python tools/extract_bsp.py assets/<map>.map web/public/<map>
   .venv/bin/python tools/extract_collision.py assets/<map>.map web/public
   .venv/bin/python tools/extract_shaders.py assets/<map>.map web/public
   .venv/bin/python tools/extract_stage_programs.py web/public/shaders.json web/public/stages.json
   .venv/bin/python tools/extract_scenery.py assets/<map>.map web/public
   ```
3. Load in viewer (multi-map registry — not yet implemented; today hardcodes b30).
4. Exercise engine WASM collision + stage materials on that level’s BSPs.

## Remaining campaign (Halo CE)

| Code | Level |
|------|-------|
| a10 | The Pillar of Autumn |
| a30 | Halo |
| a50 | The Truth and Reconciliation |
| b30 | The Silent Cartographer *(current)* |
| b40 | Assault on the Control Room |
| c10 | 343 Guilty Spark |
| c20 | The Library |
| c40 | Two Betrayals |
| d20 | Keyes |
| d40 | The Maw |

## Ring vision (after campaign engine trust)

See [README.md](../README.md): place levels on Installation 04 ring geometry,
multiplayer presence, player-authored NFT segments on IPFS. None of that starts
until Phase 3 exit criteria are met for b30.
