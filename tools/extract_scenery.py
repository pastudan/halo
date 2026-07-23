#!/usr/bin/env python3
"""Extract Halo 1 scenario scenery (trees, rocks, props) to GLB + placements.

Usage: .venv/bin/python tools/extract_scenery.py assets/b30.map web/public

Outputs:
  scenery.glb    one named node per scenery palette entry ("pal_<i>"), meshes
                 at model origin, diffuse textures embedded
  scenery.json   {"models": {i: tag_path}, "instances": [{"m": i,
                 "p": [x,y,z] (three.js meters), "r": [yaw,pitch,roll] (halo
                 radians)}]}

Model geometry comes from the cache's model data section (gbxmodel parts
reference it by offset). Vertices are 68-byte uncompressed model verts in
model space; triangles are strips. LOD: superhigh, permutation 0.
"""
import json
import struct
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parent))
from extract_bsp import (  # noqa: E402
    TRANSPARENT_CLASSES, TextureBank, build_glb, find_enum_field,
    halo_to_gltf, pick_base_map,
)

MODEL_VERT_SIZE = 68  # pos 3f, normal 3f, binormal 3f, tangent 3f, uv 2f, nodes/weights

# palette entries with no useful render geometry (effects, invisible collision)
SKIP_SUBSTRINGS = ("emitters", "lens", "door_blast_collision")


def find_model_dep(block, depth=0):
    nm = getattr(block, "NAME_MAP", None)
    if nm is None or depth > 4:
        return None
    for field in nm:
        try:
            child = getattr(block, field)
        except Exception:
            continue
        if hasattr(child, "tag_class") and hasattr(child, "filepath"):
            if child.tag_class.enum_name in ("gbxmodel", "model") and child.filepath:
                return child
        elif hasattr(child, "NAME_MAP"):
            found = find_model_dep(child, depth + 1)
            if found is not None:
                return found
    return None


def strip_to_tris(idx):
    """Halo strip -> triangle list, alternating winding, degenerates dropped.
    Winding is emitted flipped (matches the BSP exporter's axis mirror)."""
    tris = []
    for i in range(len(idx) - 2):
        a, b, c = idx[i], idx[i + 1], idx[i + 2]
        if a < 0 or b < 0 or c < 0 or a == b or b == c or a == c:
            continue
        if i % 2 == 0:
            tris.extend((a, c, b))
        else:
            tris.extend((a, b, c))
    return tris


def extract_model(halo_map, mod2_id, shader_texture):
    """Return list of primitive dicts for a gbxmodel (superhigh LOD, perm 0)."""
    meta = halo_map.get_meta(mod2_id)
    ti = halo_map.tag_index
    f = halo_map.map_data

    u_scale = meta.base_map_u_scale or 1.0
    v_scale = meta.base_map_v_scale or 1.0
    shaders = meta.shaders.STEPTREE
    geometries = meta.geometries.STEPTREE

    prims = []
    for region in meta.regions.STEPTREE:
        perms = region.permutations.STEPTREE
        if not perms:
            continue
        geom_idx = perms[0].superhigh_geometry_block
        if geom_idx < 0 or geom_idx >= len(geometries):
            continue
        for part in geometries[geom_idx].parts.STEPTREE:
            mi = part.model_meta_info
            if mi.vertex_count == 0 or mi.index_count == 0:
                continue

            f.seek(ti.model_data_offset + mi.vertices_offset)
            vraw = f.read(mi.vertex_count * MODEL_VERT_SIZE)
            f.seek(ti.model_data_offset + ti.vertex_data_size + mi.indices_offset)
            iraw = f.read((mi.index_count + 2) * 2)
            idx = struct.unpack("<%dh" % (mi.index_count + 2), iraw)

            positions = bytearray(mi.vertex_count * 12)
            normals = bytearray(mi.vertex_count * 12)
            uvs = bytearray(mi.vertex_count * 8)
            mn = [1e30, 1e30, 1e30]
            mx = [-1e30, -1e30, -1e30]
            for i in range(mi.vertex_count):
                o = i * MODEL_VERT_SIZE
                px, py, pz, nx, ny, nz = struct.unpack_from("<6f", vraw, o)
                u, v = struct.unpack_from("<2f", vraw, o + 48)
                gx, gy, gz = halo_to_gltf(px, py, pz)
                struct.pack_into("<3f", positions, i * 12, gx, gy, gz)
                struct.pack_into("<3f", normals, i * 12, nx, nz, -ny)
                struct.pack_into("<2f", uvs, i * 8, u * u_scale, v * v_scale)
                for a in range(3):
                    g = (gx, gy, gz)[a]
                    if g < mn[a]: mn[a] = g
                    if g > mx[a]: mx[a] = g

            tri_idx = strip_to_tris(idx)
            if not tri_idx:
                continue
            indices = struct.pack("<%dH" % len(tri_idx), *tri_idx)

            sdep = shaders[part.shader_index].shader if part.shader_index < len(shaders) else None
            sinfo = shader_texture(sdep) if sdep is not None and sdep.filepath else \
                {"image": None, "alpha": False, "class": "unknown", "blend": None}
            shader_path = (sdep.filepath if sdep is not None else "unknown")
            transparent = sinfo["class"] in TRANSPARENT_CLASSES

            prims.append({
                "positions": bytes(positions), "normals": bytes(normals),
                "uvs": bytes(uvs), "uv2": None,
                "indices": indices, "vert_count": mi.vertex_count,
                "index_count": len(tri_idx), "index_u32": False,
                "name": shader_path, "pos_min": mn, "pos_max": mx,
                "image": sinfo["image"], "transparent": transparent,
                "alpha_test": sinfo["alpha"] and not transparent,
                "extras": {
                    "shader": shader_path,
                    "shader_class": sinfo["class"],
                    "blend": sinfo.get("blend"),
                    "lightmap": None,
                },
            })
    return prims


def main():
    map_path, out_dir = sys.argv[1], Path(sys.argv[2])
    out_dir.mkdir(parents=True, exist_ok=True)

    from refinery.core import RefineryCore
    core = RefineryCore()
    core.load_map(map_path)
    m = core.active_map
    print(f"map: {m.map_name} engine: {m.engine}")
    bank = TextureBank(m)

    scnr_id = next(i for i, r in enumerate(m.tag_index.tag_index)
                   if r.class_1.enum_name == "scenario")
    scnr = m.get_meta(scnr_id)
    palette = scnr.sceneries_palette.STEPTREE
    placements = scnr.sceneries.STEPTREE

    # shared texture/image dedup across all models
    images = []
    shader_cache = {}

    def shader_texture(dep):
        sid = dep.id & 0xFFFF
        if sid in shader_cache:
            return shader_cache[sid]
        info = {"image": None, "alpha": False, "class": "unknown", "blend": None}
        try:
            ref = m.tag_index.tag_index[sid]
            info["class"] = ref.class_1.enum_name
            smeta = m.get_meta(sid)
            if info["class"] in TRANSPARENT_CLASSES:
                info["blend"] = find_enum_field(smeta, "framebuffer_blend_function")
            base = pick_base_map(smeta)
            if base is not None and base.filepath:
                res = bank.bitmap_png(base.id & 0xFFFF)
                if res:
                    images.append({"png": res[0]})
                    info["image"] = len(images) - 1
                    info["alpha"] = res[1]
        except Exception as e:
            print(f"  ! shader {dep.filepath}: {e}")
        shader_cache[sid] = info
        return info

    primitives = []
    nodes = []
    models = {}   # palette index -> tag path (only those exported)
    for pi, entry in enumerate(palette):
        path = entry.name.filepath
        if not path or any(s in path for s in SKIP_SUBSTRINGS):
            continue
        try:
            scen_meta = m.get_meta(entry.name.id & 0xFFFF)
            mdep = find_model_dep(scen_meta)
            if mdep is None:
                continue
            prims = extract_model(m, mdep.id & 0xFFFF, shader_texture)
        except Exception as e:
            print(f"  ! {path}: {e}")
            continue
        if not prims:
            continue
        start = len(primitives)
        primitives.extend(prims)
        nodes.append({"name": f"pal_{pi}", "prims": list(range(start, len(primitives)))})
        models[pi] = path
        nv = sum(p["vert_count"] for p in prims)
        print(f"  pal_{pi} {path.split(chr(92))[-1]}: {len(prims)} parts, {nv} verts")

    instances = []
    for s in placements:
        if s.type not in models:
            continue
        if getattr(s.not_placed, "data", 0):
            continue
        p = s.position
        r = s.rotation
        instances.append({
            "m": s.type,
            "p": [round(v, 3) for v in halo_to_gltf(p.x, p.y, p.z)],
            "r": [round(r.y, 4), round(r.p, 4), round(r.r, 4)],
        })

    out_glb = out_dir / "scenery.glb"
    build_glb(primitives, images, out_glb, nodes=nodes)
    (out_dir / "scenery.json").write_text(json.dumps(
        {"models": models, "instances": instances}, separators=(",", ":")))
    print(f"  {len(nodes)} models, {len(instances)} instances, {len(images)} textures "
          f"-> {out_glb} ({out_glb.stat().st_size/1e6:.1f} MB)")


if __name__ == "__main__":
    main()
