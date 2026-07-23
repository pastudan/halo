#!/usr/bin/env python3
"""Extract Halo 1 (PC demo) BSP render geometry + textures from a map cache to GLB.

Usage: .venv/bin/python tools/extract_bsp.py assets/b30.map web/public

Outputs, per scenario_structure_bsp tag:
  <name>.glb            render geometry, diffuse textures embedded, TEXCOORD_1
                        lightmap UVs, per-material extras {shader, shader_class,
                        lightmap} naming a lightmap PNG
  textures/<name>_lm_<i>.png   baked lightmap atlases
Plus spawn.json with player starting locations.

Halo is Z-up right-handed; glTF is Y-up. Transform (x,y,z) -> (x, z, -y),
scale world units (1 wu = 10 ft) to meters (x3.048). Halo BSP triangle winding
is opposite its stored normals, so indices are emitted as (a, c, b).
"""
import io
import json
import struct
import sys
from pathlib import Path

from PIL import Image

WU_TO_M = 3.048
VERT_SIZE = 56       # pos 3f, normal 3f, binormal 3f, tangent 3f, uv 2f
LM_VERT_SIZE = 20    # incident light dir 3f, uv 2f
MAX_TEX = 512        # downscale diffuse textures to this edge at most

# shader classes that render transparent/blended
TRANSPARENT_CLASSES = {
    "shader_transparent_chicago", "shader_transparent_chicago_extended",
    "shader_transparent_generic", "shader_transparent_glass",
    "shader_transparent_water", "shader_transparent_plasma",
    "shader_transparent_meter",
}


def halo_to_gltf(x, y, z):
    return (x * WU_TO_M, z * WU_TO_M, -y * WU_TO_M)


# --------------------------------------------------------------------------
# bitmap decoding (Halo 1 PC formats -> RGBA bytes)
# --------------------------------------------------------------------------

def _565(v):
    r = (v >> 11) & 31
    g = (v >> 5) & 63
    b = v & 31
    return ((r * 255) // 31, (g * 255) // 63, (b * 255) // 31)


def decode_dxt1(data, w, h):
    out = bytearray(w * h * 4)
    bw, bh = (w + 3) // 4, (h + 3) // 4
    pos = 0
    for by in range(bh):
        for bx in range(bw):
            c0, c1, bits = struct.unpack_from("<HHI", data, pos)
            pos += 8
            r0, g0, b0 = _565(c0)
            r1, g1, b1 = _565(c1)
            if c0 > c1:
                pal = ((r0, g0, b0, 255), (r1, g1, b1, 255),
                       ((2 * r0 + r1) // 3, (2 * g0 + g1) // 3, (2 * b0 + b1) // 3, 255),
                       ((r0 + 2 * r1) // 3, (g0 + 2 * g1) // 3, (b0 + 2 * b1) // 3, 255))
            else:
                pal = ((r0, g0, b0, 255), (r1, g1, b1, 255),
                       ((r0 + r1) // 2, (g0 + g1) // 2, (b0 + b1) // 2, 255),
                       (0, 0, 0, 0))
            for py in range(4):
                y = by * 4 + py
                if y >= h:
                    break
                for px in range(4):
                    x = bx * 4 + px
                    if x >= w:
                        continue
                    c = pal[(bits >> (2 * (py * 4 + px))) & 3]
                    o = (y * w + x) * 4
                    out[o:o + 4] = bytes(c)
    return bytes(out)


def _dxt_color_block(data, pos, alphas, out, w, h, bx, by):
    c0, c1, bits = struct.unpack_from("<HHI", data, pos)
    r0, g0, b0 = _565(c0)
    r1, g1, b1 = _565(c1)
    pal = ((r0, g0, b0), (r1, g1, b1),
           ((2 * r0 + r1) // 3, (2 * g0 + g1) // 3, (2 * b0 + b1) // 3),
           ((r0 + 2 * r1) // 3, (g0 + 2 * g1) // 3, (b0 + 2 * b1) // 3))
    for py in range(4):
        y = by * 4 + py
        if y >= h:
            break
        for px in range(4):
            x = bx * 4 + px
            if x >= w:
                continue
            i = py * 4 + px
            c = pal[(bits >> (2 * i)) & 3]
            o = (y * w + x) * 4
            out[o] = c[0]
            out[o + 1] = c[1]
            out[o + 2] = c[2]
            out[o + 3] = alphas[i]


def decode_dxt3(data, w, h):
    out = bytearray(w * h * 4)
    bw, bh = (w + 3) // 4, (h + 3) // 4
    pos = 0
    for by in range(bh):
        for bx in range(bw):
            abits = struct.unpack_from("<Q", data, pos)[0]
            alphas = [(((abits >> (4 * i)) & 15) * 255) // 15 for i in range(16)]
            _dxt_color_block(data, pos + 8, alphas, out, w, h, bx, by)
            pos += 16
    return bytes(out)


def decode_dxt5(data, w, h):
    out = bytearray(w * h * 4)
    bw, bh = (w + 3) // 4, (h + 3) // 4
    pos = 0
    for by in range(bh):
        for bx in range(bw):
            a0, a1 = data[pos], data[pos + 1]
            abits = int.from_bytes(data[pos + 2:pos + 8], "little")
            if a0 > a1:
                apal = [a0, a1] + [((7 - i) * a0 + i * a1) // 7 for i in range(1, 7)]
            else:
                apal = [a0, a1] + [((5 - i) * a0 + i * a1) // 5 for i in range(1, 5)] + [0, 255]
            alphas = [apal[(abits >> (3 * i)) & 7] for i in range(16)]
            _dxt_color_block(data, pos + 8, alphas, out, w, h, bx, by)
            pos += 16
    return bytes(out)


def decode_16bit(data, w, h, fmt):
    out = bytearray(w * h * 4)
    for i in range(w * h):
        v = data[2 * i] | (data[2 * i + 1] << 8)
        o = i * 4
        if fmt == "r5g6b5":
            r, g, b = _565(v)
            a = 255
        elif fmt == "a1r5g5b5":
            a = 255 if (v & 0x8000) else 0
            r = (((v >> 10) & 31) * 255) // 31
            g = (((v >> 5) & 31) * 255) // 31
            b = ((v & 31) * 255) // 31
        else:  # a4r4g4b4
            a = (((v >> 12) & 15) * 255) // 15
            r = (((v >> 8) & 15) * 255) // 15
            g = (((v >> 4) & 15) * 255) // 15
            b = ((v & 15) * 255) // 15
        out[o], out[o + 1], out[o + 2], out[o + 3] = r, g, b, a
    return bytes(out)


def decode_32bit(data, w, h, fmt):
    out = bytearray(w * h * 4)
    opaque = fmt == "x8r8g8b8"
    for i in range(w * h):
        b, g, r, a = data[4 * i:4 * i + 4]
        o = i * 4
        out[o], out[o + 1], out[o + 2] = r, g, b
        out[o + 3] = 255 if opaque else a
    return bytes(out)


def decode_8bit(data, w, h, fmt):
    out = bytearray(w * h * 4)
    for i in range(w * h):
        v = data[i]
        o = i * 4
        if fmt == "a8":
            out[o] = out[o + 1] = out[o + 2] = 255
            out[o + 3] = v
        else:  # y8 and anything else monochrome-ish
            out[o] = out[o + 1] = out[o + 2] = v
            out[o + 3] = 255
    return bytes(out)


def mip0_size(fmt, w, h):
    if fmt in ("dxt1",):
        return ((w + 3) // 4) * ((h + 3) // 4) * 8
    if fmt in ("dxt3", "dxt5"):
        return ((w + 3) // 4) * ((h + 3) // 4) * 16
    if fmt in ("r5g6b5", "a1r5g5b5", "a4r4g4b4", "a8y8"):
        return w * h * 2
    if fmt in ("a8r8g8b8", "x8r8g8b8"):
        return w * h * 4
    return w * h  # 8-bit


def decode_bitmap(fmt, data, w, h):
    if fmt == "dxt1":
        return decode_dxt1(data, w, h)
    if fmt == "dxt3":
        return decode_dxt3(data, w, h)
    if fmt == "dxt5":
        return decode_dxt5(data, w, h)
    if fmt in ("r5g6b5", "a1r5g5b5", "a4r4g4b4"):
        return decode_16bit(data, w, h, fmt)
    if fmt in ("a8r8g8b8", "x8r8g8b8"):
        return decode_32bit(data, w, h, fmt)
    if fmt in ("a8", "y8", "p8", "p8_bump"):
        return decode_8bit(data, w, h, fmt)
    if fmt == "a8y8":
        out = bytearray(w * h * 4)
        for i in range(w * h):
            y, a = data[2 * i], data[2 * i + 1]
            o = i * 4
            out[o] = out[o + 1] = out[o + 2] = y
            out[o + 3] = a
        return bytes(out)
    return None


# --------------------------------------------------------------------------
# tag helpers
# --------------------------------------------------------------------------

def is_dependency(block):
    nm = getattr(block, "NAME_MAP", None)
    return nm is not None and "filepath" in nm and "tag_class" in nm


def find_bitm_deps(block, out, name="", depth=0):
    """Recursively collect (field_name, dep_block) for all bitm dependencies."""
    if depth > 6:
        return
    nm = getattr(block, "NAME_MAP", None)
    if nm is None:
        return
    for field in nm:
        try:
            child = getattr(block, field)
        except Exception:
            continue
        if is_dependency(child):
            try:
                if child.tag_class.enum_name == "bitmap" and child.filepath:
                    out.append((field, child))
            except Exception:
                pass
        elif hasattr(child, "NAME_MAP"):
            find_bitm_deps(child, out, field, depth + 1)
        elif hasattr(child, "STEPTREE") and hasattr(child.STEPTREE, "__iter__") \
                and not isinstance(child.STEPTREE, (bytes, bytearray, str)):
            for sub in child.STEPTREE:
                if hasattr(sub, "NAME_MAP"):
                    find_bitm_deps(sub, out, field, depth + 1)


BASE_MAP_PRIORITY = ("base_map", "diffuse_map", "bitmap", "map")
BASE_MAP_EXCLUDE = ("detail", "micro", "bump", "cube", "reflection", "ripple",
                    "multipurpose", "vector", "noise")


def find_enum_field(block, want, depth=0):
    """Recursively find the first enum field named `want`, return enum_name."""
    if depth > 6:
        return None
    nm = getattr(block, "NAME_MAP", None)
    if nm is None:
        return None
    for field in nm:
        try:
            child = getattr(block, field)
        except Exception:
            continue
        if field == want and hasattr(child, "enum_name"):
            return child.enum_name
        if hasattr(child, "NAME_MAP"):
            found = find_enum_field(child, want, depth + 1)
            if found is not None:
                return found
    return None


def pick_base_map(shader_meta):
    deps = []
    find_bitm_deps(shader_meta, deps)
    deps = [(n, d) for n, d in deps if not any(x in n for x in BASE_MAP_EXCLUDE)]
    for want in BASE_MAP_PRIORITY:
        for name, dep in deps:
            if name == want:
                return dep
    return deps[0][1] if deps else None


class TextureBank:
    """Decodes bitm tags to PNG bytes, cached by tag id."""

    def __init__(self, halo_map):
        self.map = halo_map
        self.rsrc = halo_map.maps.get("bitmaps")  # demo/PC external bitmaps.map
        self.cache = {}

    def read_pixels(self, meta, b, size):
        if hasattr(b.flags, "data_in_resource_map") and b.flags.data_in_resource_map:
            if self.rsrc is None:
                return None
            self.rsrc.map_data.seek(b.pixels_offset)
            return self.rsrc.map_data.read(size)
        px = meta.processed_pixel_data.STEPTREE
        return px[b.pixels_offset: b.pixels_offset + size]

    def bitmap_png(self, bitm_id, sub=0, max_edge=MAX_TEX):
        key = (bitm_id, sub, max_edge)
        if key in self.cache:
            return self.cache[key]
        result = None
        try:
            meta = self.map.get_meta(bitm_id)
            blocks = meta.bitmaps.STEPTREE
            if sub < len(blocks):
                b = blocks[sub]
                fmt = b.format.enum_name
                w, h = b.width, b.height
                data = self.read_pixels(meta, b, mip0_size(fmt, w, h))
                rgba = decode_bitmap(fmt, data, w, h) if data else None
                if rgba:
                    img = Image.frombytes("RGBA", (w, h), rgba)
                    if max(w, h) > max_edge:
                        s = max_edge / max(w, h)
                        img = img.resize((max(1, int(w * s)), max(1, int(h * s))),
                                         Image.LANCZOS)
                    has_alpha = img.getextrema()[3][0] < 255
                    if not has_alpha:
                        img = img.convert("RGB")
                    buf = io.BytesIO()
                    img.save(buf, "PNG", optimize=True)
                    result = (buf.getvalue(), has_alpha)
        except Exception as e:
            print(f"  ! bitmap {bitm_id} failed: {e}")
        self.cache[key] = result
        return result


# --------------------------------------------------------------------------
# GLB writer
# --------------------------------------------------------------------------

def build_glb(primitives, images, out_path, nodes=None):
    """primitives: list of dicts (see extract_sbsp). images: list of dicts
    {png: bytes} shared by primitives via 'image' index.
    nodes: optional list of {"name": str, "prims": [primitive indices]} to
    emit multiple named meshes (default: one mesh with everything)."""
    bin_chunks = []
    buffer_views = []
    accessors = []
    offset = 0

    def add_view(data, target=None):
        nonlocal offset
        pad = (-offset) % 4
        if pad:
            bin_chunks.append(b"\x00" * pad)
            offset += pad
        view = {"buffer": 0, "byteOffset": offset, "byteLength": len(data)}
        if target:
            view["target"] = target
        buffer_views.append(view)
        bin_chunks.append(data)
        offset += len(data)
        return len(buffer_views) - 1

    gltf_images = []
    gltf_textures = []
    for im in images:
        view = add_view(im["png"])
        gltf_images.append({"bufferView": view, "mimeType": "image/png"})
        gltf_textures.append({"source": len(gltf_images) - 1, "sampler": 0})

    samplers = [{"magFilter": 9729, "minFilter": 9987, "wrapS": 10497, "wrapT": 10497}]

    materials = []
    prims_json = []
    for p in primitives:
        pv = add_view(p["positions"], 34962)
        nv = add_view(p["normals"], 34962)
        tv = add_view(p["uvs"], 34962)
        attrs = {}
        accessors.append({"bufferView": pv, "componentType": 5126, "count": p["vert_count"],
                          "type": "VEC3", "min": list(p["pos_min"]), "max": list(p["pos_max"])})
        attrs["POSITION"] = len(accessors) - 1
        accessors.append({"bufferView": nv, "componentType": 5126,
                          "count": p["vert_count"], "type": "VEC3"})
        attrs["NORMAL"] = len(accessors) - 1
        accessors.append({"bufferView": tv, "componentType": 5126,
                          "count": p["vert_count"], "type": "VEC2"})
        attrs["TEXCOORD_0"] = len(accessors) - 1
        if p.get("uv2") is not None:
            uv2v = add_view(p["uv2"], 34962)
            accessors.append({"bufferView": uv2v, "componentType": 5126,
                              "count": p["vert_count"], "type": "VEC2"})
            attrs["TEXCOORD_1"] = len(accessors) - 1
        iv = add_view(p["indices"], 34963)
        accessors.append({"bufferView": iv, "componentType": 5125 if p["index_u32"] else 5123,
                          "count": p["index_count"], "type": "SCALAR"})
        idx_acc = len(accessors) - 1

        mat = {
            "name": p["name"],
            "pbrMetallicRoughness": {
                "metallicFactor": 0.0,
                "roughnessFactor": 1.0,
            },
            "extras": p["extras"],
        }
        if p.get("image") is not None:
            mat["pbrMetallicRoughness"]["baseColorTexture"] = {"index": p["image"], "texCoord": 0}
        else:
            mat["pbrMetallicRoughness"]["baseColorFactor"] = [0.6, 0.6, 0.6, 1.0]
        if p.get("transparent"):
            mat["alphaMode"] = "BLEND"
            mat["doubleSided"] = True
        elif p.get("alpha_test"):
            mat["alphaMode"] = "MASK"
            mat["alphaCutoff"] = 0.5
            mat["doubleSided"] = True
        materials.append(mat)
        prims_json.append({"attributes": attrs, "indices": idx_acc,
                           "material": len(materials) - 1})

    if nodes is None:
        gltf_nodes = [{"mesh": 0, "name": out_path.stem}]
        meshes = [{"primitives": prims_json}]
    else:
        gltf_nodes = []
        meshes = []
        for nd in nodes:
            meshes.append({"primitives": [prims_json[i] for i in nd["prims"]]})
            gltf_nodes.append({"mesh": len(meshes) - 1, "name": nd["name"]})

    gltf = {
        "asset": {"version": "2.0", "generator": "halo-ring extract_bsp"},
        "scene": 0,
        "scenes": [{"nodes": list(range(len(gltf_nodes)))}],
        "nodes": gltf_nodes,
        "meshes": meshes,
        "materials": materials,
        "accessors": accessors,
        "bufferViews": buffer_views,
        "buffers": [{"byteLength": offset}],
    }
    if gltf_images:
        gltf["images"] = gltf_images
        gltf["textures"] = gltf_textures
        gltf["samplers"] = samplers

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


# --------------------------------------------------------------------------
# BSP extraction
# --------------------------------------------------------------------------

def extract_sbsp(halo_map, bank, meta, tag_path, out_dir):
    name = tag_path.split("\\")[-1]
    surfaces_block = meta.surface if hasattr(meta, "surface") else meta.surfaces
    surfaces_raw = surfaces_block.STEPTREE
    if not isinstance(surfaces_raw, (bytes, bytearray)):
        surfaces_raw = b"".join(struct.pack("<3h", s[0], s[1], s[2]) for s in surfaces_raw)

    # ---- lightmap atlas PNGs (written as standalone files, clamped sampling)
    tex_dir = out_dir / "textures"
    tex_dir.mkdir(parents=True, exist_ok=True)
    lm_files = {}  # lightmap bitmap_index -> filename
    lm_bitm_id = None
    if meta.lightmap_bitmaps.filepath:
        lm_bitm_id = meta.lightmap_bitmaps.id & 0xFFFF
    if lm_bitm_id is not None:
        used = sorted({lm.bitmap_index for lm in meta.lightmaps.STEPTREE
                       if lm.bitmap_index >= 0})
        for i in used:
            res = bank.bitmap_png(lm_bitm_id, sub=i, max_edge=2048)
            if res:
                fname = f"{name}_lm_{i}.png"
                (tex_dir / fname).write_bytes(res[0])
                lm_files[i] = f"textures/{fname}"

    # ---- diffuse textures, deduped per shader
    shader_tex = {}   # shader tag id -> dict(image=idx into images, ...) or None
    images = []

    def shader_texture(dep):
        sid = dep.id & 0xFFFF
        if sid in shader_tex:
            return shader_tex[sid]
        info = None
        try:
            ref = halo_map.tag_index.tag_index[sid]
            cls = ref.class_1.enum_name
            smeta = halo_map.get_meta(sid)
            base = pick_base_map(smeta)
            blend = None
            if cls in TRANSPARENT_CLASSES:
                blend = find_enum_field(smeta, "framebuffer_blend_function")
            info = {"image": None, "alpha": False, "class": cls, "blend": blend}
            if base is not None and base.filepath:
                res = bank.bitmap_png(base.id & 0xFFFF)
                if res:
                    png, has_alpha = res
                    images.append({"png": png})
                    info["image"] = len(images) - 1
                    info["alpha"] = has_alpha
        except Exception as e:
            print(f"  ! shader {dep.filepath}: {e}")
            info = {"image": None, "alpha": False, "class": "unknown", "blend": None}
        shader_tex[sid] = info
        return info

    primitives = []
    n_tris = n_verts = 0
    for lightmap in meta.lightmaps.STEPTREE:
        lm_file = lm_files.get(lightmap.bitmap_index)
        for mat in lightmap.materials.STEPTREE:
            vert_count = mat.vertices_count
            if vert_count == 0 or mat.surface_count == 0:
                continue
            raw = mat.uncompressed_vertices.STEPTREE
            if len(raw) < vert_count * VERT_SIZE:
                continue

            shader_path = mat.shader.filepath or "unknown"
            sinfo = shader_texture(mat.shader)

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
                struct.pack_into("<3f", positions, i * 12, gx, gy, gz)
                struct.pack_into("<3f", normals, i * 12, nx, nz, -ny)
                struct.pack_into("<2f", uvs, i * 8, u, v)
                if gx < mn[0]: mn[0] = gx
                if gy < mn[1]: mn[1] = gy
                if gz < mn[2]: mn[2] = gz
                if gx > mx[0]: mx[0] = gx
                if gy > mx[1]: mx[1] = gy
                if gz > mx[2]: mx[2] = gz

            # lightmap UVs follow render verts in the same raw block
            uv2 = None
            lm_count = mat.lightmap_vertices_count
            if lm_file and lm_count == vert_count and \
                    len(raw) >= vert_count * VERT_SIZE + lm_count * LM_VERT_SIZE:
                uv2 = bytearray(vert_count * 8)
                base_off = vert_count * VERT_SIZE
                for i in range(vert_count):
                    lu, lv = struct.unpack_from(
                        "<2f", raw, base_off + i * LM_VERT_SIZE + 12)
                    struct.pack_into("<2f", uv2, i * 8, lu, lv)

            # triangles; winding flipped (a, c, b) to match stored normals
            tri_idx = []
            for s in range(mat.surfaces, mat.surfaces + mat.surface_count):
                a, b, c = struct.unpack_from("<3h", surfaces_raw, s * 6)
                tri_idx.extend((a, c, b))
            index_u32 = vert_count > 65535
            fmt = "<%dI" % len(tri_idx) if index_u32 else "<%dH" % len(tri_idx)
            indices = struct.pack(fmt, *tri_idx)

            transparent = sinfo["class"] in TRANSPARENT_CLASSES
            primitives.append({
                "positions": bytes(positions), "normals": bytes(normals),
                "uvs": bytes(uvs), "uv2": bytes(uv2) if uv2 else None,
                "indices": indices, "vert_count": vert_count,
                "index_count": len(tri_idx), "index_u32": index_u32,
                "name": shader_path, "pos_min": mn, "pos_max": mx,
                "image": sinfo["image"], "transparent": transparent,
                "extras": {
                    "shader": shader_path,
                    "shader_class": sinfo["class"],
                    "blend": sinfo.get("blend"),
                    "lightmap": lm_file,
                },
            })
            n_tris += mat.surface_count
            n_verts += vert_count

    out_path = out_dir / f"{name}.glb"
    build_glb(primitives, images, out_path)
    print(f"  {tag_path}: {len(primitives)} materials, {n_verts} verts, "
          f"{n_tris} tris, {len(images)} textures, {len(lm_files)} lightmaps "
          f"-> {out_path} ({out_path.stat().st_size/1e6:.1f} MB)")


def main():
    map_path, out_dir = sys.argv[1], Path(sys.argv[2])
    out_dir.mkdir(parents=True, exist_ok=True)

    from refinery.core import RefineryCore
    core = RefineryCore()
    core.load_map(map_path)
    m = core.active_map
    print(f"map: {m.map_name} engine: {m.engine}")
    bank = TextureBank(m)

    scnr_id = None
    for i, ref in enumerate(m.tag_index.tag_index):
        cls = ref.class_1.enum_name
        if cls == "scenario_structure_bsp":
            extract_sbsp(m, bank, m.get_meta(i), ref.path, out_dir)
        elif cls == "scenario":
            scnr_id = i

    spawns = []
    if scnr_id is not None:
        scnr = m.get_meta(scnr_id)
        for loc in scnr.player_starting_locations.STEPTREE:
            p = loc.position
            spawns.append({
                "position": halo_to_gltf(p.x, p.y, p.z),
                "facing_rad": loc.facing,
            })
    (out_dir / "spawn.json").write_text(json.dumps(spawns, indent=1))
    print(f"  wrote {len(spawns)} spawns -> {out_dir/'spawn.json'}")


if __name__ == "__main__":
    main()
