# Phase 4 deepeners (scaffolded)

After Phase 3 thin walk works, expand without changing dual-track architecture.

## Scenery / object collision

- Extract collision models from `gbxmodel` / collision geometry tags
  (stub: `tools/extract_object_collision.py` — placeholder until RE’d object
  collision path lands).
- Feed hulls into `engine/` alongside structure BSPs.
- Biped vs scenery is out of scope for the thin milestone (BSP walls only).

## Remaining shader classes

Stage-program compilers for:

- `shader_transparent_glass`
- `shader_transparent_plasma`
- `shader_transparent_meter`
- `shader_transparent_generic`

Extend `tools/extract_stage_programs.py` COMPILERS map; interpreter grows only
by new **ops**, not per-class GLSL forks.

## Atmospheric fog

RE `render` / rasterizer fog setup from Track A; until then viewer keeps the
simple three.js `Fog` in `main.js` as a stand-in. Document RE targets in
`halo-re/kb.json` under rasterizer modules.

## Bumped cubemap

`shader_environment` reflection_type `bumped_cubemap` needs bump-map sampling
into reflection vector — stage op `cube_fresnel_bumped` once bump bitmaps and
RE’d math are wired.

## Cache / tag loader

Long pole: load `.map` in WASM instead of MEK JSON dumps. Depends on RE’d
`tag_files` / `cache` modules. Extractors remain until then.
