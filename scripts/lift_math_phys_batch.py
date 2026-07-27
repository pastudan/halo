#!/usr/bin/env python3
"""Naked→C lifts for math/models/physics leaves + Unicorn prove."""
from __future__ import annotations

import json
import re
import subprocess
import sys
import time
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "scripts"))
sys.path.insert(0, str(ROOT / "tools" / "equivalence"))

from lift_inventory_batch4 import find_naked_block  # noqa: E402
from prove_inventory_batch4 import ensure_oracle, flip_kb  # noqa: E402
from tu_compile import docker_compile, regen_decl_h  # noqa: E402
from unicorn_c_campaign import (  # noqa: E402
    KB_PATH,
    append_ledger,
    clear_pass,
    count_ported,
    run_unicorn,
)

LIFTS: dict[int, tuple[str, str, str, str | None]] = {}


def L(addr: int, source: str, name: str, body: str, decl: str | None = None):
    LIFTS[addr] = (source, name, body.strip() + "\n", decl)


L(
    0x10CC40,
    "math/real_math.c",
    "angles_to_vector",
    """
/* angles_to_vector (0x10cc40) — readable C lift from XBE leaf. */
void angles_to_vector(float *out, float *angles)
{
  float cp = cosf(angles[1]);
  out[0] = cosf(angles[0]) * cp;
  out[1] = sinf(angles[0]) * cp;
  out[2] = sinf(angles[1]);
}
""",
    "void angles_to_vector(float *out, float *angles);",
)

L(
    0x12F10,
    "math/vector_math.c",
    "magnitude3d",
    """
/* magnitude3d (0x12f10) — readable C lift from XBE leaf (normalize2d).
 * Returns 2D magnitude; normalizes v[0],v[1] in place when |mag| >= 1e-4. */
float magnitude3d(float *v)
{
  float mag = sqrtf(v[0] * v[0] + v[1] * v[1]);
  if ((double)fabsf(mag) < *(double *)0x2533d0) {
    return *(float *)0x2533c0;
  }
  {
    float inv = *(float *)0x2533c8 / mag;
    v[0] *= inv;
    v[1] *= inv;
  }
  return mag;
}
""",
    "float magnitude3d(float *v);",
)

L(
    0x10B270,
    "math/random_math.c",
    "random_real_range",
    """
/* random_real_range (0x10b270) — readable C lift from XBE leaf. */
float random_real_range(int *seed, float min, float max)
{
  unsigned int s = (unsigned int)(*seed * 0x19660d + 0x3c6ef35f);
  unsigned int r;
  float t;
  *seed = (int)s;
  r = s >> 16;
  t = (float)(int)r;
  if ((int)r < 0) {
    t += *(float *)0x25fb8c;
  }
  t *= *(float *)0x2647f4;
  return min + t * (max - min);
}
""",
    "float random_real_range(int *seed, float min, float max);",
)

L(
    0x106900,
    "math/geometry.c",
    "convex_polygon2d_verify",
    """
/* convex_polygon2d_verify (0x106900) — readable C lift from XBE leaf.
 * Rejects vertices with Inf/NaN float encodings. */
bool convex_polygon2d_verify(int16_t vertex_count, uint32_t *vertices)
{
  int16_t i;
  if (vertex_count <= 0) {
    return true;
  }
  for (i = 0; i < vertex_count; i++) {
    uint32_t *vert = vertices + (i * 2);
    if ((vert[0] & 0x7f800000u) == 0x7f800000u) {
      return false;
    }
    if ((vert[1] & 0x7f800000u) == 0x7f800000u) {
      return false;
    }
  }
  return true;
}
""",
    "bool convex_polygon2d_verify(int16_t vertex_count, uint32_t *vertices);",
)

L(
    0x147380,
    "physics/collision_bsp.c",
    "FUN_00147380",
    """
/* FUN_00147380 (0x147380) — readable C lift; thin wrapper (node_flags=-1). */
int FUN_00147380(int a0, int a1, int a2, int a3, int a4, int a5, int a6)
{
  return FUN_001470b0(a0, a1, -1, a2, a3, a4, a5, a6);
}
""",
    "int FUN_00147380(int a0, int a1, int a2, int a3, int a4, int a5, int a6);",
)

L(
    0x147660,
    "physics/collision_bsp.c",
    "render_debug_collision_bsp",
    """
/* render_debug_collision_bsp (0x147660) — readable C lift from XBE leaf. */
void render_debug_collision_bsp(int bsp, int matrix_or_flag)
{
  int count = *(int *)(bsp + 0x48);
  int i;
  for (i = 0; i < count; i++) {
    render_debug_collision_edge(bsp, i, matrix_or_flag, *(void **)0x2ee6d4);
  }
}
""",
    "void render_debug_collision_bsp(int bsp, int matrix_or_flag);",
)

L(
    0x146DB0,
    "physics/bsp3d.c",
    "bsp3d_find_leaf",
    """
/* bsp3d_find_leaf (0x146db0) — readable C lift from XBE leaf. */
uint32_t bsp3d_find_leaf(void *bsp3d, int root, void *point)
{
  float *p = (float *)point;
  int node = root;
  while (node >= 0) {
    int *node_el = (int *)tag_block_get_element(bsp3d, node, 0xc);
    float *plane =
        (float *)tag_block_get_element((char *)bsp3d + 0xc, node_el[0], 0x10);
    float d = plane[0] * p[0] + plane[1] * p[1] + plane[2] * p[2] - plane[3];
    int side = (d < *(float *)0x2533c0) ? 0 : 1;
    node = node_el[1 + side];
  }
  if (node == -1) {
    return 0xffffffffu;
  }
  return (uint32_t)(node & 0x7fffffff);
}
""",
    "uint32_t bsp3d_find_leaf(void *bsp3d, int root, void *point);",
)

L(
    0x146D40,
    "physics/bsp3d.c",
    "FUN_00146d40",
    """
/* FUN_00146d40 (0x146d40) — readable C lift from XBE leaf (2D BSP walk). */
uint32_t FUN_00146d40(void *bsp2d_nodes, float *point2d, int node_index)
{
  int node = node_index;
  if (node < 0) {
    goto done;
  }
  while (node >= 0) {
    float *el = (float *)tag_block_get_element(bsp2d_nodes, node, 0x14);
    float d = el[0] * point2d[0] + el[1] * point2d[1] - el[2];
    int side = (d < *(float *)0x2533c0) ? 0 : 1;
    node = ((int *)el)[3 + side];
  }
done:
  if (node == -1) {
    return 0xffffffffu;
  }
  return (uint32_t)(node & 0x7fffffff);
}
""",
    "uint32_t FUN_00146d40(void *bsp2d_nodes, float *point2d, int node_index);",
)

L(
    0x1473B0,
    "physics/collision_bsp.c",
    "collision_surface_edge_count",
    """
/* collision_surface_edge_count (0x1473b0) — readable C lift from XBE leaf. */
short collision_surface_edge_count(int bsp, int surface_index)
{
  int *surface;
  int first_edge;
  int edge;
  int count = 0;
  void *surfaces = (char *)bsp + 0x3c;
  void *edges = (char *)bsp + 0x48;

  surface = (int *)tag_block_get_element(surfaces, surface_index, 0xc);
  first_edge = surface[1];
  edge = first_edge;
  do {
    int *edge_el = (int *)tag_block_get_element(edges, edge, 0x18);
    int next_is_right = (edge_el[5] == surface_index);
    edge = edge_el[2 + next_is_right];
    count++;
  } while (edge != first_edge);
  return (short)count;
}
""",
    "short collision_surface_edge_count(int bsp, int surface_index);",
)


def apply_lifts(addrs: list[int] | None = None) -> list[dict]:
    selected = addrs if addrs else sorted(LIFTS.keys())
    by_source: dict[str, list[int]] = {}
    for a in selected:
        if a not in LIFTS:
            print(f"skip unknown {hex(a)}", file=sys.stderr)
            continue
        by_source.setdefault(LIFTS[a][0], []).append(a)

    results = []
    for src, alist in by_source.items():
        path = ROOT / "src" / "halo" / src
        text = path.read_text(encoding="utf-8", errors="replace")
        for a in sorted(alist, reverse=True):
            _source, name, body, decl = LIFTS[a]
            span = find_naked_block(text, name, a)
            if span is None:
                print(f"FAIL locate {hex(a)} {name} in {src}", file=sys.stderr)
                results.append({"addr": hex(a), "name": name, "ok": False, "err": "locate"})
                continue
            start, end = span
            block_len = end - start
            if block_len > 2500:
                print(f"ABORT >2500B {hex(a)} {name} len={block_len}", file=sys.stderr)
                results.append({"addr": hex(a), "name": name, "ok": False, "err": "too_big"})
                continue
            text = text[:start] + body + "\n" + text[end:]
            print(f"lifted {hex(a)} {name} (replaced {block_len}B)")
            results.append({"addr": hex(a), "name": name, "ok": True, "src": src})
        path.write_text(text, encoding="utf-8")
    return results


def set_decls(kb: dict) -> None:
    for a, (_s, _n, _b, decl) in LIFTS.items():
        if not decl:
            continue
        d = decl if decl.endswith(";") else decl + ";"
        for obj in kb.get("objects", []):
            for fn in obj.get("functions") or []:
                if isinstance(fn, dict) and fn.get("addr") and int(fn["addr"], 16) == a:
                    fn["decl"] = d


def prove(name: str, addr: int, seeds: int = 100, timeout: float = 45.0) -> dict:
    if not ensure_oracle(addr):
        return {"addr": hex(addr), "name": name, "ok": False, "err": "oracle"}
    res = run_unicorn(hex(addr), addr, seeds, timeout=timeout)
    if not clear_pass(res, seeds):
        res2 = run_unicorn(name, addr, seeds, timeout=timeout)
        if clear_pass(res2, seeds):
            res = res2
    ok = clear_pass(res, seeds)
    return {
        "addr": hex(addr),
        "name": name,
        "ok": ok,
        "passed": res.get("passed"),
        "failed": res.get("failed"),
        "errors": res.get("errors"),
        "rc": res.get("rc"),
        "detail": (res.get("tail") or "")[-300:],
    }


def main() -> int:
    import argparse

    ap = argparse.ArgumentParser()
    ap.add_argument("--apply-only", action="store_true")
    ap.add_argument("--prove-only", action="store_true")
    ap.add_argument("--seeds", type=int, default=100)
    ap.add_argument("--no-push", action="store_true")
    ap.add_argument("addrs", nargs="*", help="Optional hex addrs")
    args = ap.parse_args()

    addrs = [int(a, 16) for a in args.addrs] if args.addrs else sorted(LIFTS.keys())

    if not args.prove_only:
        applied = apply_lifts(addrs)
        kb = json.loads(KB_PATH.read_text(encoding="utf-8"))
        set_decls(kb)
        KB_PATH.write_text(json.dumps(kb, indent=2) + "\n", encoding="utf-8")
        if args.apply_only:
            print(json.dumps(applied, indent=2))
            return 0

        # ensure decl.h
        decl = ROOT / "build" / "generated" / "decl.h"
        if not decl.exists():
            print("regen decl.h...", flush=True)
            regen_decl_h()

        touched_src = sorted({LIFTS[a][0] for a in addrs if a in LIFTS})
        for src in touched_src:
            print(f"compile {src}...", flush=True)
            if not docker_compile(src):
                print(f"COMPILE FAIL {src}", flush=True)
                return 1

    proved = []
    kb = json.loads(KB_PATH.read_text(encoding="utf-8"))
    before = count_ported(kb)
    for a in addrs:
        if a not in LIFTS:
            continue
        name = LIFTS[a][1]
        # skip if still naked
        src = LIFTS[a][0]
        text = (ROOT / "src" / "halo" / src).read_text(encoding="utf-8", errors="replace")
        if "__attribute__((naked" in text[max(0, text.find(name) - 80) : text.find(name) + 80]:
            # more precise: find def
            pass
        from unicorn_c_campaign import is_naked_near_def, resolve_src

        sp = resolve_src(src)
        lines = sp.read_text(encoding="utf-8", errors="replace").splitlines()
        if is_naked_near_def(lines, name, hex(a)):
            print(f"SKIP still naked {hex(a)} {name}", flush=True)
            continue
        print(f"prove {hex(a)} {name}...", flush=True)
        t0 = time.time()
        r = prove(name, a, seeds=args.seeds)
        r["sec"] = round(time.time() - t0, 2)
        print(r, flush=True)
        append_ledger({**r, "campaign": "lift_math_phys_batch"})
        if r["ok"]:
            flip_kb(kb, a)
            proved.append(r)
    KB_PATH.write_text(json.dumps(kb, indent=2) + "\n", encoding="utf-8")
    after = count_ported(kb)
    print(f"proved {len(proved)}  ported {before}->{after}", flush=True)
    for r in proved:
        print(f"  PASS {r['addr']} {r['name']} {r['passed']}/{r['failed']}/{r['errors']}")

    if proved:
        files = ["kb.json", "scripts/lift_math_phys_batch.py"]
        files += [f"src/halo/{LIFTS[int(r['addr'], 16)][0]}" for r in proved]
        # unique
        files = list(dict.fromkeys(files))
        subprocess.run(["git", "add"] + files, cwd=ROOT, check=False)
        names = " ".join(r["name"] for r in proved)
        msg = f"lift(track-a): {' '.join(r['name'] for r in proved[:6])} Unicorn-prove ({len(proved)}) (ported:true)."
        if len(msg) > 90:
            msg = f"lift(track-a): math/physics Unicorn-prove {len(proved)} (ported:true)."
        subprocess.run(["git", "commit", "-m", msg], cwd=ROOT, check=False)
        if not args.no_push:
            subprocess.run(["git", "fetch", "pastudan", "track-a-collision-bsp"], cwd=ROOT)
            subprocess.run(
                ["git", "pull", "--rebase", "pastudan", "track-a-collision-bsp"],
                cwd=ROOT,
                check=False,
            )
            subprocess.run(
                ["git", "push", "pastudan", "HEAD:track-a-collision-bsp"],
                cwd=ROOT,
                check=False,
            )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
