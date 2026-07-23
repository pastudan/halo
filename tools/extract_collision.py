#!/usr/bin/env python3
"""Extract Halo 1 collision BSPs + player movement constants for the physics core.

Usage: .venv/bin/python tools/extract_collision.py assets/b30.map web/public

Outputs:
  <bsp>.cbsp        binary collision BSP (native Halo coords/units, z-up, world units)
  constants.json    player movement constants from the globals + player biped tags

.cbsp layout (little-endian):
  char[4]  magic "HCB1"
  u32      counts[8]: bsp3d_nodes, planes, leaves, bsp2d_references,
                      bsp2d_nodes, surfaces, edges, vertices
  then the raw arrays, in that order, with the original in-cache layouts:
    bsp3d_node: i32 plane, i32 back_child, i32 front_child            (12 B)
    plane:      f32 i, j, k, d                                        (16 B)
    leaf:       u16 flags, i16 bsp2d_ref_count, i32 first_bsp2d_ref   (8 B)
    bsp2d_ref:  i32 plane, i32 bsp2d_node                             (8 B)
    bsp2d_node: f32 plane_i, plane_j, plane_d, i32 left, i32 right    (20 B)
    surface:    i32 plane, i32 first_edge, u8 flags, i8 breakable,
                i16 material                                          (12 B)
    edge:       i32 start_vert, end_vert, forward_edge, reverse_edge,
                    left_surface, right_surface                       (24 B)
    vertex:     f32 x, y, z, i32 first_edge                           (16 B)

Node child encoding (original engine semantics):
  child >= 0        -> bsp3d node index
  child == -1       -> outside the bsp (empty)
  child & 0x80000000 (other) -> leaf index (child & 0x7FFFFFFF)
"""
import json
import struct
import sys
from pathlib import Path

ARRAYS = (
    ("bsp3d_nodes", 12, "<3i"),
    ("planes", 16, "<4f"),
    ("leaves", 8, "<Hhi"),
    ("bsp2d_references", 8, "<2i"),
    ("bsp2d_nodes", 20, "<3f2i"),
    ("surfaces", 12, "<2iBbh"),
    ("edges", 24, "<6i"),
    ("vertices", 16, "<3fi"),
)


def block_bytes(block, item_size, fmt):
    tree = block.STEPTREE
    if isinstance(tree, (bytes, bytearray)):
        return bytes(tree)
    out = bytearray()
    for item in tree:
        vals = []
        for v in item:
            vals.append(int(v.data) if hasattr(v, "data") else v)
        out += struct.pack(fmt, *vals)
    return bytes(out)


def export_cbsp(meta, out_path):
    bsp = meta.collision_bsp.STEPTREE[0]
    payloads = []
    counts = []
    for name, size, fmt in ARRAYS:
        data = block_bytes(getattr(bsp, name), size, fmt)
        assert len(data) % size == 0, f"{name}: {len(data)} % {size}"
        counts.append(len(data) // size)
        payloads.append(data)
    with open(out_path, "wb") as f:
        f.write(b"HCB1")
        f.write(struct.pack("<8I", *counts))
        for p in payloads:
            f.write(p)
    print(f"  {out_path}: " +
          ", ".join(f"{n}={c}" for (n, _, _), c in zip(ARRAYS, counts)) +
          f"  ({out_path.stat().st_size/1e6:.1f} MB)")


def main():
    map_path, out_dir = sys.argv[1], Path(sys.argv[2])
    out_dir.mkdir(parents=True, exist_ok=True)

    from refinery.core import RefineryCore
    core = RefineryCore()
    core.load_map(map_path)
    m = core.active_map
    print(f"map: {m.map_name} engine: {m.engine}")

    matg_id = None
    for i, ref in enumerate(m.tag_index.tag_index):
        cls = ref.class_1.enum_name
        if cls == "scenario_structure_bsp":
            name = ref.path.split("\\")[-1]
            export_cbsp(m.get_meta(i), out_dir / f"{name}.cbsp")
        elif cls == "globals":
            matg_id = i

    # ---- movement constants
    matg = m.get_meta(matg_id)
    pinfo = matg.player_informations.STEPTREE[0]
    unit_dep = pinfo.unit
    bipd = m.get_meta(unit_dep.id & 0xFFFF)
    attrs = bipd.bipd_attrs
    move = attrs.movement
    cam = attrs.camera_collision_and_autoaim
    jump = attrs.jumping_and_landing

    # Raw tag values: speeds are wu/s; accelerations and jump velocity are
    # per-tick (reclaimer displays them scaled by UNIT_SCALE).
    constants = {
        "ticks_per_second": 30,
        "player_unit": unit_dep.filepath,
        # wu/s
        "walking_speed": pinfo.walking_speed,
        "double_speed_multiplier": pinfo.double_speed_multiplier,
        "run_forward": pinfo.run_forward,
        "run_backward": pinfo.run_backward,
        "run_sideways": pinfo.run_sideways,
        # wu/tick^2
        "run_acceleration": pinfo.run_acceleration,
        "airborne_acceleration": pinfo.airborne_acceleration,
        # wu/tick
        "jump_velocity": jump.jump_velocity,
        # wu
        "standing_camera_height": cam.standing_camera_height,
        "crouching_camera_height": cam.crouching_camera_height,
        "standing_collision_height": cam.standing_collision_height,
        "crouching_collision_height": cam.crouching_collision_height,
        "collision_radius": cam.collision_radius,
        # engine constant (hardcoded in blam, not in tags), wu/tick^2
        "gravity": 3.5651205e-3,
        # biped movement tuning
        "moving_turning_speed": move.moving_turning_speed if hasattr(move, "moving_turning_speed") else None,
    }
    (out_dir / "constants.json").write_text(json.dumps(constants, indent=1))
    print(f"  constants: {json.dumps({k: v for k, v in constants.items() if isinstance(v, (int, float))}, indent=1)}")


if __name__ == "__main__":
    main()
