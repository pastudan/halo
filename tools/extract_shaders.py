#!/usr/bin/env python3
"""Extract full Halo 1 shader tag parameters + referenced textures.

Usage: .venv/bin/python tools/extract_shaders.py assets/b30.map web/public

Outputs:
  shaders.json                 tag path -> parameter dict per shader class
  textures/tex_<id>.png        2D bitmaps (mip0, capped at 512px)
  textures/tex_<id>_f<0-5>.png cubemap faces (D3D order +x -x +y -y +z -z;
                               PC cache layout is mip-major, so mip0 holds
                               all 6 faces consecutively)

The viewer (web/src/halo_materials.js) rebuilds each shader class's fixed-
function math as GLSL from these parameters.
"""
import json
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parent))
from extract_bsp import decode_bitmap, mip0_size  # noqa: E402
from PIL import Image  # noqa: E402
import io  # noqa: E402

MAX_TEX = 512

SHADER_CLASSES = (
    "shader_environment", "shader_model", "shader_transparent_water",
    "shader_transparent_chicago", "shader_transparent_chicago_extended",
    "shader_transparent_generic", "shader_transparent_glass",
    "shader_transparent_meter", "shader_transparent_plasma",
)


class TexExporter:
    def __init__(self, halo_map, tex_dir):
        self.map = halo_map
        self.rsrc = halo_map.maps.get("bitmaps")
        self.tex_dir = tex_dir
        self.cache = {}

    def read_pixels(self, meta, b, size):
        if hasattr(b.flags, "data_in_resource_map") and b.flags.data_in_resource_map:
            if self.rsrc is None:
                return None
            self.rsrc.map_data.seek(b.pixels_offset)
            return self.rsrc.map_data.read(size)
        px = meta.processed_pixel_data.STEPTREE
        return px[b.pixels_offset: b.pixels_offset + size]

    def _save_png(self, rgba, w, h, path):
        img = Image.frombytes("RGBA", (w, h), rgba)
        if max(w, h) > MAX_TEX:
            s = MAX_TEX / max(w, h)
            img = img.resize((max(1, int(w * s)), max(1, int(h * s))), Image.LANCZOS)
        has_alpha = img.getextrema()[3][0] < 255
        if not has_alpha:
            img = img.convert("RGB")
        buf = io.BytesIO()
        img.save(buf, "PNG", optimize=True)
        path.write_bytes(buf.getvalue())
        return has_alpha

    def export(self, dep):
        """dep -> {"tex": relpath, "alpha": bool} | {"cube": relprefix} | None"""
        if dep is None or not dep.filepath:
            return None
        bid = dep.id & 0xFFFF
        if bid in self.cache:
            return self.cache[bid]
        result = None
        try:
            meta = self.map.get_meta(bid)
            b = meta.bitmaps.STEPTREE[0]
            fmt = b.format.enum_name
            w, h = b.width, b.height
            size = mip0_size(fmt, w, h)
            if b.type.enum_name == "cubemap":
                data = self.read_pixels(meta, b, size * 6)
                if data:
                    for f in range(6):
                        rgba = decode_bitmap(fmt, data[f * size:(f + 1) * size], w, h)
                        self._save_png(rgba, w, h, self.tex_dir / f"tex_{bid}_f{f}.png")
                    result = {"cube": f"textures/tex_{bid}", "size": w}
            else:
                data = self.read_pixels(meta, b, size)
                rgba = decode_bitmap(fmt, data, w, h) if data else None
                if rgba:
                    has_alpha = self._save_png(rgba, w, h, self.tex_dir / f"tex_{bid}.png")
                    result = {"tex": f"textures/tex_{bid}.png", "alpha": has_alpha}
        except Exception as e:
            print(f"  ! bitmap {dep.filepath}: {e}")
        self.cache[bid] = result
        return result


def rgb(c):
    return [round(c.r, 4), round(c.g, 4), round(c.b, 4)]


def anim(a):
    return {"function": a.function.enum_name, "period": round(a.period, 4),
            "scale": round(a.scale, 4)}


def extract_senv(meta, tex):
    a = meta.senv_attrs
    d = a.diffuse
    out = {
        "class": "shader_environment",
        "type": a.environment_shader.type.enum_name,
        "alpha_tested": bool(a.environment_shader.flags.alpha_tested),
        "base": tex.export(d.base_map),
        "detail_function": d.detail_map_function.enum_name,
        "primary_detail": tex.export(d.primary_detail_map),
        "primary_detail_scale": round(d.primary_detail_map_scale, 4),
        "secondary_detail": tex.export(d.secondary_detail_map),
        "secondary_detail_scale": round(d.secondary_detail_map_scale, 4),
        "micro_detail": tex.export(d.micro_detail_map),
        "micro_detail_scale": round(d.micro_detail_map_scale, 4),
        "micro_detail_function": d.micro_detail_map_function.enum_name,
        "material_color": rgb(d.material_color),
    }
    il = a.self_illumination
    if il.map.filepath:
        out["self_illum"] = {"map": tex.export(il.map),
                             "scale": round(il.map_scale, 4),
                             "color": rgb(il.primary_on_color)}
    r = a.reflection
    if r.cube_map.filepath:
        out["reflection"] = {
            "type": r.reflection_type.enum_name,
            "cube": tex.export(r.cube_map),
            "perpendicular_brightness": round(r.perpendicular_brightness, 4),
            "parallel_brightness": round(r.parallel_brightness, 4),
            "perpendicular_tint": rgb(a.specular.perpendicular_tint_color),
            "parallel_tint": rgb(a.specular.parallel_tint_color),
            "specular_brightness": round(a.specular.brightness, 4),
        }
    return out


def extract_soso(meta, tex):
    a = meta.soso_attrs
    mp = a.maps
    fl = a.model_shader.flags
    out = {
        "class": "shader_model",
        "two_sided": bool(fl.two_sided),
        "alpha_tested": not fl.not_alpha_tested,
        "u_scale": round(mp.map_u_scale, 4) or 1.0,
        "v_scale": round(mp.map_v_scale, 4) or 1.0,
        "base": tex.export(mp.diffuse_map),
        "detail": tex.export(mp.detail_map),
        "detail_function": mp.detail_function.enum_name,
        "detail_scale": round(mp.detail_map_scale, 4) or 1.0,
        "detail_v_scale": round(mp.detail_map_v_scale, 4),
    }
    r = a.reflection
    if r.cube_map.filepath:
        out["reflection"] = {
            "cube": tex.export(r.cube_map),
            "perpendicular_brightness": round(r.perpendicular_brightness, 4),
            "parallel_brightness": round(r.parallel_brightness, 4),
            "perpendicular_tint": rgb(r.perpendicular_tint_color),
            "parallel_tint": rgb(r.parallel_tint_color),
        }
    return out


def extract_swat(meta, tex):
    a = meta.swat_attrs
    w = a.water_shader
    return {
        "class": "shader_transparent_water",
        "alpha_modulates_reflection": bool(w.flags.base_map_alpha_modulates_reflection),
        "base": tex.export(w.base_map),
        "perpendicular_brightness": round(w.perpendicular_brightness, 4),
        "perpendicular_tint": rgb(w.perpendicular_tint_color),
        "parallel_brightness": round(w.parallel_brightness, 4),
        "parallel_tint": rgb(w.parallel_tint_color),
        "reflection_cube": tex.export(w.reflection_map),
        "ripple_scale": round(w.ripple_scale, 4),
        "ripple_maps": tex.export(w.ripple_maps),
        "ripples": [{
            "contribution": round(r.contribution_factor, 4),
            "angle": round(r.animation_angle, 4),
            "velocity": round(r.animation_velocity, 4),
            "repeats": round(r.map_repeats, 4) or 1.0,
        } for r in a.ripples.STEPTREE],
    }


def stage_map(mp, tex):
    return {
        "map": tex.export(mp.bitmap),
        "color_function": mp.color_function.enum_name,
        "alpha_function": mp.alpha_function.enum_name,
        "u_scale": round(mp.map_u_scale, 4) or 1.0,
        "v_scale": round(mp.map_v_scale, 4) or 1.0,
        "u_offset": round(mp.map_u_offset, 4),
        "v_offset": round(mp.map_v_offset, 4),
        "u_anim": anim(mp.u_animation),
        "v_anim": anim(mp.v_animation),
    }


def extract_chicago(meta, tex, extended):
    a = meta.scex_attrs if extended else meta.schi_attrs
    cs = a.chicago_shader_extended if extended else a.chicago_shader
    maps = (a.four_stage_maps if extended else a.maps).STEPTREE
    return {
        "class": "shader_transparent_chicago" + ("_extended" if extended else ""),
        "blend": cs.framebuffer_blend_function.enum_name,
        "alpha_tested": bool(cs.chicago_shader_flags.alpha_tested),
        "two_sided": bool(cs.chicago_shader_flags.two_sided),
        "maps": [stage_map(mp, tex) for mp in maps],
    }


def extract_generic(meta, tex, cls):
    """fallback: first bitmap dependency as base map"""
    from extract_bsp import pick_base_map
    base = pick_base_map(meta)
    return {"class": cls, "base": tex.export(base) if base is not None else None}


def main():
    map_path, out_dir = sys.argv[1], Path(sys.argv[2])
    tex_dir = out_dir / "textures"
    tex_dir.mkdir(parents=True, exist_ok=True)

    from refinery.core import RefineryCore
    core = RefineryCore()
    core.load_map(map_path)
    m = core.active_map
    print(f"map: {m.map_name} engine: {m.engine}")
    tex = TexExporter(m, tex_dir)

    shaders = {}
    counts = {}
    for i, ref in enumerate(m.tag_index.tag_index):
        cls = ref.class_1.enum_name
        if cls not in SHADER_CLASSES:
            continue
        counts[cls] = counts.get(cls, 0) + 1
        try:
            meta = m.get_meta(i)
            if cls == "shader_environment":
                out = extract_senv(meta, tex)
            elif cls == "shader_model":
                out = extract_soso(meta, tex)
            elif cls == "shader_transparent_water":
                out = extract_swat(meta, tex)
            elif cls == "shader_transparent_chicago":
                out = extract_chicago(meta, tex, extended=False)
            elif cls == "shader_transparent_chicago_extended":
                out = extract_chicago(meta, tex, extended=True)
            else:
                out = extract_generic(meta, tex, cls)
            shaders[ref.path] = out
        except Exception as e:
            print(f"  ! {ref.path}: {e}")

    (out_dir / "shaders.json").write_text(json.dumps(shaders, separators=(",", ":")))
    print(f"  classes: {counts}")
    print(f"  {len(shaders)} shaders, {len(tex.cache)} textures -> {out_dir/'shaders.json'}")


if __name__ == "__main__":
    main()
