#!/usr/bin/env python3
"""Compile shaders.json → stages.json (explicit D3D-like texture stage programs).

Phase 2 of the dual-track plan: materials are driven by a machine-readable
stage program, not ad-hoc GLSL per class. Until Track A recovers the exact
rasterizer bind functions, these programs are derived from documented Halo 1
fixed-function setup (tag fields → texture stages) — the same mapping the
engine uses, expressed as data the browser must interpret strictly.

Usage:
  .venv/bin/python tools/extract_stage_programs.py web/public/shaders.json \\
      web/public/stages.json
"""
import json
import sys
from pathlib import Path


def detail_op(fn):
    """Map Halo detail_function enum → stage combine op."""
    return {
        "multiply": "modulate",
        "double_biased_multiply": "modulate2x",
        "double_biased_add": "add_signed2x",
    }.get(fn, "modulate2x")


def senv_program(def_):
    stages = []
    stages.append({
        "op": "sample", "map": "base", "uv": "texcoord0",
        "out": "r0", "tex": def_.get("base"),
    })
    # blended: lerp primary/secondary by base alpha; else primary*secondary or one
    has_p = bool(def_.get("primary_detail") and def_.get("primary_detail", {}).get("tex"))
    has_s = bool(def_.get("secondary_detail") and def_.get("secondary_detail", {}).get("tex"))
    has_m = bool(def_.get("micro_detail") and def_.get("micro_detail", {}).get("tex"))
    detail_fn = detail_op(def_.get("detail_function", "double_biased_multiply"))

    if has_p and has_s and def_.get("type") == "blended":
        stages.append({
            "op": "sample", "map": "detail_p", "uv": "texcoord0",
            "scale": def_.get("primary_detail_scale", 1),
            "out": "r1", "tex": def_["primary_detail"],
        })
        stages.append({
            "op": "sample", "map": "detail_s", "uv": "texcoord0",
            "scale": def_.get("secondary_detail_scale", 1),
            "out": "r2", "tex": def_["secondary_detail"],
        })
        stages.append({"op": "lerp", "a": "r2", "b": "r1", "t": "r0.a", "out": "r3"})
        stages.append({"op": detail_fn, "a": "r0", "b": "r3", "out": "r0", "space": "gamma"})
    elif has_p or has_s:
        key = "primary_detail" if has_p else "secondary_detail"
        sc = def_.get("primary_detail_scale" if has_p else "secondary_detail_scale", 1)
        stages.append({
            "op": "sample", "map": "detail", "uv": "texcoord0",
            "scale": sc, "out": "r1", "tex": def_[key],
        })
        stages.append({"op": detail_fn, "a": "r0", "b": "r1", "out": "r0", "space": "gamma"})

    if has_m:
        stages.append({
            "op": "sample", "map": "micro", "uv": "texcoord0",
            "scale": def_.get("micro_detail_scale", 1),
            "out": "r1", "tex": def_["micro_detail"],
        })
        stages.append({
            "op": detail_op(def_.get("micro_detail_function", "double_biased_multiply")),
            "a": "r0", "b": "r1", "out": "r0", "space": "gamma",
        })

    if def_.get("material_color") and def_["material_color"] != [1, 1, 1]:
        stages.append({"op": "modulate_const", "a": "r0", "rgb": def_["material_color"], "out": "r0"})

    refl = def_.get("reflection")
    if refl and refl.get("cube"):
        stages.append({
            "op": "cube_fresnel",
            "cube": refl["cube"],
            "perp_rgb": refl.get("perpendicular_tint", [1, 1, 1]),
            "perp_b": refl.get("perpendicular_brightness", 0),
            "par_rgb": refl.get("parallel_tint", [1, 1, 1]),
            "par_b": refl.get("parallel_brightness", 0),
            "mask": "r0.a",
            "add_to": "r0",
        })

    return {
        "class": "shader_environment",
        "alpha_tested": bool(def_.get("alpha_tested")),
        "lightmap": True,
        "stages": stages,
        "source": "tag→stage (awaiting Track A rasterizer bind RE)",
    }


def soso_program(def_):
    stages = [{
        "op": "sample", "map": "base", "uv": "texcoord0",
        "u_scale": def_.get("u_scale", 1), "v_scale": def_.get("v_scale", 1),
        "out": "r0", "tex": def_.get("base"),
    }]
    if def_.get("detail") and def_["detail"].get("tex"):
        stages.append({
            "op": "sample", "map": "detail", "uv": "texcoord0",
            "u_scale": (def_.get("u_scale", 1) * def_.get("detail_scale", 1)),
            "v_scale": (def_.get("v_scale", 1) * (def_.get("detail_v_scale") or def_.get("detail_scale", 1))),
            "out": "r1", "tex": def_["detail"],
        })
        stages.append({
            "op": detail_op(def_.get("detail_function", "double_biased_multiply")),
            "a": "r0", "b": "r1", "out": "r0", "space": "gamma",
        })
    return {
        "class": "shader_model",
        "alpha_tested": bool(def_.get("alpha_tested")),
        "two_sided": bool(def_.get("two_sided")),
        "lightmap": False,
        "stages": stages,
        "source": "tag→stage (awaiting Track A rasterizer bind RE)",
    }


def swat_program(def_):
    return {
        "class": "shader_transparent_water",
        "lightmap": False,
        "transparent": True,
        "stages": [
            {"op": "sample", "map": "mask", "uv": "texcoord0", "out": "r0", "tex": def_.get("base")},
            {
                "op": "water_ripples",
                "ripple_tex": def_.get("ripple_maps"),
                "ripple_scale": def_.get("ripple_scale", 1),
                "ripples": def_.get("ripples", []),
                "out": "n",
            },
            {
                "op": "cube_fresnel",
                "cube": def_.get("reflection_cube"),
                "perp_rgb": def_.get("perpendicular_tint", [1, 1, 1]),
                "perp_b": def_.get("perpendicular_brightness", 0),
                "par_rgb": def_.get("parallel_tint", [1, 1, 1]),
                "par_b": def_.get("parallel_brightness", 0),
                "mask": "r0.a" if def_.get("alpha_modulates_reflection") else None,
                "normal": "n",
                "out": "r1",
            },
            {"op": "water_composite", "refl": "r1", "mask": "r0", "out": "r0"},
        ],
        "source": "tag→stage (awaiting Track A rasterizer bind RE)",
    }


def chicago_program(def_):
    stages = []
    for i, m in enumerate(def_.get("maps") or []):
        if not m.get("map") or not m["map"].get("tex"):
            continue
        stages.append({
            "op": "sample", "map": f"s{i}", "uv": "texcoord0",
            "u_scale": m.get("u_scale", 1), "v_scale": m.get("v_scale", 1),
            "u_offset": m.get("u_offset", 0), "v_offset": m.get("v_offset", 0),
            "u_anim": m.get("u_anim"), "v_anim": m.get("v_anim"),
            "out": f"r{i}", "tex": m["map"],
        })
        if i == 0:
            stages.append({"op": "mov", "a": "r0", "out": "cur"})
        else:
            stages.append({
                "op": "chicago_combine",
                "fn": m.get("color_function", "multiply"),
                "a": "cur", "b": f"r{i}", "out": "cur",
            })
    return {
        "class": def_.get("class", "shader_transparent_chicago"),
        "blend": def_.get("blend", "alpha_blend"),
        "alpha_tested": bool(def_.get("alpha_tested")),
        "two_sided": bool(def_.get("two_sided")),
        "transparent": True,
        "lightmap": False,
        "stages": stages,
        "source": "tag→stage (awaiting Track A rasterizer bind RE)",
    }


def glass_plasma_stub(def_):
    """Phase 4: glass/plasma/meter — base map only until stage ops are RE'd."""
    return {
        "class": def_.get("class"),
        "transparent": True,
        "lightmap": False,
        "stages": [{
            "op": "sample", "map": "base", "uv": "texcoord0",
            "out": "r0", "tex": def_.get("base"),
        }],
        "source": "Phase 4 stub — awaiting Track A shader bind RE",
    }


COMPILERS = {
    "shader_environment": senv_program,
    "shader_model": soso_program,
    "shader_transparent_water": swat_program,
    "shader_transparent_chicago": chicago_program,
    "shader_transparent_chicago_extended": chicago_program,
    "shader_transparent_glass": glass_plasma_stub,
    "shader_transparent_plasma": glass_plasma_stub,
    "shader_transparent_meter": glass_plasma_stub,
    "shader_transparent_generic": glass_plasma_stub,
}


def main():
    src = Path(sys.argv[1])
    dst = Path(sys.argv[2])
    shaders = json.loads(src.read_text())
    stages = {}
    skipped = 0
    for path, def_ in shaders.items():
        cls = def_.get("class")
        fn = COMPILERS.get(cls)
        if not fn:
            skipped += 1
            continue
        stages[path] = fn(def_)
    dst.write_text(json.dumps({
        "version": 1,
        "note": "Stage programs for strict WebGL interpreter. Replace with "
                "dumps from RE'd rasterizer bind once Track A lands.",
        "programs": stages,
    }, separators=(",", ":")))
    print(f"  {len(stages)} stage programs, {skipped} shader classes skipped → {dst}")


if __name__ == "__main__":
    main()
