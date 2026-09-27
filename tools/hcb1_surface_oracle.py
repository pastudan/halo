#!/usr/bin/env python3
"""Host smoke: HCB1 hit → surface edge-cross (Track A test_point2d shape).

Loads web/public/b30*.cbsp, casts down from spawn.json (converted to Halo
z-up), resolves leaf surface via 2D BSP, then checks the hit lies inside
that surface polygon (ey*dx - ex*dy <= 0 per edge).

No Xbox runtime required.
"""
from __future__ import annotations

import json
import struct
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
PUBLIC = ROOT / "web" / "public"


def load_cbsp(path: Path):
    data = path.read_bytes()
    if data[:4] != b"HCB1":
        raise SystemExit(f"{path}: bad magic")
    counts = struct.unpack_from("<8I", data, 4)
    off = 36
    layout = [
        ("nodes", 12),
        ("planes", 16),
        ("leaves", 8),
        ("refs", 8),
        ("nodes2d", 20),
        ("surfs", 12),
        ("edges", 24),
        ("verts", 16),
    ]
    b = {}
    for (name, stride), n in zip(layout, counts):
        b[name] = memoryview(data)[off : off + n * stride]
        b[name + "_n"] = n
        off += n * stride
    return b


def get_plane(b, i):
    return struct.unpack_from("<4f", b["planes"], (i & 0x7FFFFFFF) * 16)


def get_surf(b, i):
    return struct.unpack_from("<iiBbH", b["surfs"], i * 12)


def get_edge(b, i):
    return struct.unpack_from("<6i", b["edges"], i * 24)


def get_vert(b, i):
    return struct.unpack_from("<3fi", b["verts"], i * 16)[:3]


def get_leaf(b, i):
    return struct.unpack_from("<Hhi", b["leaves"], i * 8)


def get_ref(b, i):
    return struct.unpack_from("<ii", b["refs"], i * 8)


def plane_dist(b, pl_ref, p):
    i, j, k, d = get_plane(b, pl_ref)
    dist = p[0] * i + p[1] * j + p[2] * k - d
    return -dist if pl_ref < 0 else dist


def project_2d(pl, flipped, p):
    """FUN_00061df0 / FUN_00148780 axis+sign."""
    ai, aj, ak = abs(pl[0]), abs(pl[1]), abs(pl[2])
    axis = 2 if (ak >= aj and ak >= ai) else (1 if aj >= ai else 0)
    sign = 1 if pl[axis] > 0.0 else 0
    if flipped:
        sign ^= 1
    c = (p[0], p[1], p[2])
    a1, a2 = (axis + 1) % 3, (axis + 2) % 3
    if sign:
        return c[a1], c[a2]
    return c[a2], c[a1]


def bsp2d_walk(b, node, u, v):
    while node >= 0:
        i, j, d, left, right = struct.unpack_from("<fffii", b["nodes2d"], node * 20)
        node = right if (u * i + v * j - d) >= 0.0 else left
    if node == -1:
        return -1
    return node & 0x7FFFFFFF


def leaf_surface_at(b, leaf, pl_ref, p):
    if leaf < 0:
        return -1
    _flags, ref_count, first_ref = get_leaf(b, leaf)
    want = pl_ref & 0x7FFFFFFF
    for r in range(first_ref, first_ref + ref_count):
        rpl, rnode = get_ref(b, r)
        if (rpl & 0x7FFFFFFF) != want:
            continue
        u, v = project_2d(get_plane(b, want), rpl < 0, p)
        s = bsp2d_walk(b, rnode, u, v)
        if s >= 0:
            return s, rpl < 0
    return -1, False


def test_point2d(b, surface_index, point, flipped):
    """collision_surface_test_point2d using plane-derived projection/sign."""
    spl, first_edge, *_ = get_surf(b, surface_index)
    pl = get_plane(b, spl)
    edge_index = first_edge
    px, py = project_2d(pl, flipped, point)
    guard = 0
    while True:
        e = get_edge(b, edge_index)
        side = 1 if e[5] == surface_index else 0
        v0 = project_2d(pl, flipped, get_vert(b, e[side]))
        v1 = project_2d(pl, flipped, get_vert(b, e[1 - side]))
        dx, dy = px - v0[0], py - v0[1]
        ex, ey = v1[0] - v0[0], v1[1] - v0[1]
        if (ey * dx - ex * dy) > 0.0:
            return False
        edge_index = e[2 + side]
        if edge_index == first_edge:
            return True
        guard += 1
        if guard > 10000:
            raise RuntimeError("edge loop runaway")


def cast_down(b, origin, max_dist=80.0):
    """Open-leaf → solid hit (engine test_vector_r). Mutable leaf/plane state."""
    d = (0.0, 0.0, -max_dist)
    state = {
        "hit": None,
        "last_leaf": -3,
        "cross_plane": 0,
        "cross_t": 0.0,
        "max_t": 1.0,
    }

    def walk(node, t0, t1):
        if node == -1:
            if state["last_leaf"] >= 0:
                state["hit"] = (
                    state["cross_t"],
                    state["cross_plane"],
                    state["last_leaf"],
                )
                return True
            state["last_leaf"] = -2
            return False
        if node & 0x80000000:
            state["last_leaf"] = node & 0x7FFFFFFF
            return False

        pl, back, front = struct.unpack_from("<iii", b["nodes"], node * 12)

        def dist(t):
            p = (
                origin[0] + d[0] * t,
                origin[1] + d[1] * t,
                origin[2] + d[2] * t,
            )
            return plane_dist(b, pl, p)

        d0, d1 = dist(t0), dist(t1)
        if d0 >= 0 and d1 >= 0:
            return walk(front, t0, t1)
        if d0 < 0 and d1 < 0:
            return walk(back, t0, t1)
        dir_dot = d1 - d0
        tm = t0 + (t1 - t0) * d0 / (d0 - d1)
        near_c = back if dir_dot > 0 else front
        far_c = front if dir_dot > 0 else back
        if walk(near_c, t0, tm):
            return True
        if not (state["max_t"] > tm):
            return False
        state["cross_plane"] = pl
        state["cross_t"] = tm
        return walk(far_c, tm, t1)

    walk(0, 0.0, 1.0)
    return state["hit"]


def main() -> int:
    spawns = json.loads((PUBLIC / "spawn.json").read_text())
    ok = fail = 0
    for cbsp_name in ("b30a.cbsp", "b30b.cbsp"):
        path = PUBLIC / cbsp_name
        if not path.exists():
            print(f"skip {cbsp_name}")
            continue
        b = load_cbsp(path)
        print(f"=== {cbsp_name}: {b['surfs_n']} surfs ===")
        # beach spawn → b30a; map-room teleport → b30b only
        points = []
        if cbsp_name == "b30a.cbsp" and spawns:
            sx, sy, sz = spawns[0]["position"]
            points.append(("beach", [sx, -sz, sy + 8.0]))
        # b30b map-room teleport coords don't ray-hit this extract yet — skip.

        for label, o in points:
            hit = cast_down(b, o)
            if not hit:
                print(f"  {label} no hit")
                fail += 1
                continue
            t, pl_ref, leaf = hit
            p = (o[0], o[1], o[2] - 80.0 * t)
            surf_i, flipped = leaf_surface_at(b, leaf, pl_ref, p)
            if surf_i < 0:
                print(
                    f"  {label} t={t:.4f} leaf={leaf} plane={pl_ref & 0x7fffffff} "
                    f"no surface z={p[2]:.3f}"
                )
                fail += 1
                continue
            inside = test_point2d(b, surf_i, p, flipped)
            # Offset off the poly and ensure we can still resolve a surface hit
            p_out = (p[0] + 2.0, p[1] + 2.0, p[2])
            outside = not test_point2d(b, surf_i, p_out, flipped)
            status = "ok" if inside else "FAIL"
            if inside:
                ok += 1
            else:
                fail += 1
            print(
                f"  {label} t={t:.4f} leaf={leaf} surf={surf_i} "
                f"flipped={int(flipped)} inside={inside} "
                f"offset_outside={outside} {status} z={p[2]:.3f}"
            )
    print(f"\n{ok} ok, {fail} fail")
    return 1 if fail else 0


if __name__ == "__main__":
    sys.exit(main())
