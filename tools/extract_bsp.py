#!/usr/bin/env python3
"""Extract Halo 1 (PC demo) BSP render geometry from a map cache file to GLB.

Usage: .venv/bin/python tools/extract_bsp.py assets/b30.map web/public

Outputs one .glb per scenario_structure_bsp tag, plus spawn.json with player
starting locations. Halo is Z-up; glTF is Y-up. We transform (x,y,z) ->
(x, z, -y) and scale world units (1 wu = 10 ft) to meters (x3.048).
"""
import hashlib
import json
import struct
import sys
from pathlib import Path

WU_TO_M = 3.048
VERT_SIZE = 56  # pos 3f, normal 3f, binormal 3f, tangent 3f, uv 2f


def halo_to_gltf(x, y, z):
    return (x * WU_TO_M, z * WU_TO_M, -y * WU_TO_M)


def shader_color(name):
    h = hashlib.md5(name.encode()).digest()
    # muted-ish palette
    return [0.25 + 0.6 * h[0] / 255, 0.25 + 0.6 * h[1] / 255, 0.25 + 0.6 * h[2] / 255, 1.0]


def build_glb(primitives, out_path):
    """primitives: list of dicts with keys positions (bytes), normals (bytes),
    uvs (bytes), indices (bytes), vert_count, index_count, index_u32, name,
    pos_min, pos_max."""
    bin_chunks = []
    buffer_views = []
    accessors = []
    materials = []
    prims_json = []
    offset = 0

    def add_view(data, target):
        nonlocal offset
        # 4-byte align
        pad = (-offset) % 4
        if pad:
            bin_chunks.append(b"\x00" * pad)
            offset += pad
        view = {"buffer": 0, "byteOffset": offset, "byteLength": len(data), "target": target}
        buffer_views.append(view)
        bin_chunks.append(data)
        offset += len(data)
        return len(buffer_views) - 1

    for p in primitives:
        pv = add_view(p["positions"], 34962)
        nv = add_view(p["normals"], 34962)
        tv = add_view(p["uvs"], 34962)
        iv = add_view(p["indices"], 34963)

        accessors.append({"bufferView": pv, "componentType": 5126, "count": p["vert_count"],
                          "type": "VEC3", "min": list(p["pos_min"]), "max": list(p["pos_max"])})
        pos_acc = len(accessors) - 1
        accessors.append({"bufferView": nv, "componentType": 5126, "count": p["vert_count"], "type": "VEC3"})
        nrm_acc = len(accessors) - 1
        accessors.append({"bufferView": tv, "componentType": 5126, "count": p["vert_count"], "type": "VEC2"})
        uv_acc = len(accessors) - 1
        accessors.append({"bufferView": iv, "componentType": 5125 if p["index_u32"] else 5123,
                          "count": p["index_count"], "type": "SCALAR"})
        idx_acc = len(accessors) - 1

        materials.append({
            "name": p["name"],
            "pbrMetallicRoughness": {
                "baseColorFactor": shader_color(p["name"]),
                "metallicFactor": 0.0,
                "roughnessFactor": 1.0,
            },
        })
        prims_json.append({
            "attributes": {"POSITION": pos_acc, "NORMAL": nrm_acc, "TEXCOORD_0": uv_acc},
            "indices": idx_acc,
            "material": len(materials) - 1,
        })

    gltf = {
        "asset": {"version": "2.0", "generator": "halo-nft extract_bsp"},
        "scene": 0,
        "scenes": [{"nodes": [0]}],
        "nodes": [{"mesh": 0, "name": out_path.stem}],
        "meshes": [{"primitives": prims_json}],
        "materials": materials,
        "accessors": accessors,
        "bufferViews": buffer_views,
        "buffers": [{"byteLength": offset}],
    }

    json_bytes = json.dumps(gltf, separators=(",", ":")).encode()
    json_bytes += b" " * ((-len(json_bytes)) % 4)
    bin_data = b"".join(bin_chunks)
    bin_data += b"\x00" * ((-len(bin_data)) % 4)

    total = 12 + 8 + len(json_bytes) + 8 + len(bin_data)
    with open(out_path, "wb") as f:
        f.write(struct.pack("<III", 0x46546C67, 2, total))
        f.write(struct.pack("<II", len(json_bytes), 0x4E4F534A))
        f.write(json_bytes)
        f.write(struct.pack("<II", len(bin_data), 0x004E4942))
        f.write(bin_data)


def extract_sbsp(meta, tag_path, out_path):
    surfaces_block = meta.surface if hasattr(meta, "surface") else meta.surfaces
    surfaces_raw = surfaces_block.STEPTREE
    if not isinstance(surfaces_raw, (bytes, bytearray)):
        # block form -> pack to bytes
        surfaces_raw = b"".join(struct.pack("<3h", s[0], s[1], s[2]) for s in surfaces_raw)

    primitives = []
    n_mats = 0
    n_tris = 0
    n_verts = 0
    for lm_i, lightmap in enumerate(meta.lightmaps.STEPTREE):
        for mat_i, mat in enumerate(lightmap.materials.STEPTREE):
            vert_count = mat.vertices_count
            if vert_count == 0 or mat.surface_count == 0:
                continue
            raw = mat.uncompressed_vertices.STEPTREE
            if len(raw) < vert_count * VERT_SIZE:
                print(f"  ! skipping material {lm_i}/{mat_i}: raw {len(raw)} < {vert_count * VERT_SIZE}")
                continue

            shader = mat.shader.filepath or "unknown"
            positions = bytearray(vert_count * 12)
            normals = bytearray(vert_count * 12)
            uvs = bytearray(vert_count * 8)
            mn = [1e30, 1e30, 1e30]
            mx = [-1e30, -1e30, -1e30]
            for i in range(vert_count):
                o = i * VERT_SIZE
                px, py, pz, nx, ny, nz = struct.unpack_from("<6f", raw, o)
                u, v = struct.unpack_from("<2f", raw, o + 48)
                gx, gy, gz = halo_to_gltf(px, py, pz)
                gnx, gny, gnz = nx, nz, -ny
                struct.pack_into("<3f", positions, i * 12, gx, gy, gz)
                struct.pack_into("<3f", normals, i * 12, gnx, gny, gnz)
                struct.pack_into("<2f", uvs, i * 8, u, v)
                if gx < mn[0]: mn[0] = gx
                if gy < mn[1]: mn[1] = gy
                if gz < mn[2]: mn[2] = gz
                if gx > mx[0]: mx[0] = gx
                if gy > mx[1]: mx[1] = gy
                if gz > mx[2]: mx[2] = gz

            # triangles
            first = mat.surfaces
            count = mat.surface_count
            tri_idx = []
            for s in range(first, first + count):
                a, b, c = struct.unpack_from("<3h", surfaces_raw, s * 6)
                tri_idx.extend((a, b, c))
            index_u32 = vert_count > 65535
            fmt = "<%dI" % len(tri_idx) if index_u32 else "<%dH" % len(tri_idx)
            indices = struct.pack(fmt, *tri_idx)

            primitives.append({
                "positions": bytes(positions), "normals": bytes(normals), "uvs": bytes(uvs),
                "indices": indices, "vert_count": vert_count, "index_count": len(tri_idx),
                "index_u32": index_u32, "name": shader, "pos_min": mn, "pos_max": mx,
            })
            n_mats += 1
            n_tris += count
            n_verts += vert_count

    build_glb(primitives, out_path)
    print(f"  {tag_path}: {n_mats} materials, {n_verts} verts, {n_tris} tris -> {out_path} ({out_path.stat().st_size/1e6:.1f} MB)")


def main():
    map_path, out_dir = sys.argv[1], Path(sys.argv[2])
    out_dir.mkdir(parents=True, exist_ok=True)

    from refinery.core import RefineryCore
    core = RefineryCore()
    core.load_map(map_path)
    m = core.active_map
    print(f"map: {m.map_name} engine: {m.engine}")

    scnr_id = None
    sbsp_ids = []
    for i, ref in enumerate(m.tag_index.tag_index):
        cls = ref.class_1.enum_name
        if cls == "scenario_structure_bsp":
            sbsp_ids.append((i, ref.path))
        elif cls == "scenario":
            scnr_id = i

    for tid, path in sbsp_ids:
        meta = m.get_meta(tid)
        name = path.split("\\")[-1]
        extract_sbsp(meta, path, out_dir / f"{name}.glb")

    # player spawn from scenario
    spawns = []
    if scnr_id is not None:
        scnr = m.get_meta(scnr_id)
        for loc in scnr.player_starting_locations.STEPTREE:
            p = loc.position
            spawns.append({
                "position": halo_to_gltf(p.x, p.y, p.z),
                "facing_deg": loc.facing,
            })
    (out_dir / "spawn.json").write_text(json.dumps(spawns, indent=1))
    print(f"  wrote {len(spawns)} spawns -> {out_dir/'spawn.json'}")


if __name__ == "__main__":
    main()
