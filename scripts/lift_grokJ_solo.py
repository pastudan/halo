#!/usr/bin/env python3
"""Track A grokJ-solo: tiny collision/objects/units/physics leaves → Unicorn 100/0/0."""
from __future__ import annotations

import json
import os
import re
import subprocess
import sys
import time
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "scripts"))
sys.path.insert(0, str(ROOT / "tools" / "equivalence"))

from lift_inventory_batch4 import apply_lifts, find_naked_block  # noqa: E402
from prove_inventory_batch4 import ensure_oracle, flip_kb  # noqa: E402
from tu_compile import docker_compile, regen_decl_h  # noqa: E402
from unicorn_c_campaign import (  # noqa: E402
    KB_PATH,
    append_ledger,
    clear_pass,
    count_ported,
    run_unicorn,
)

# addr -> (source, name, body, decl)
LIFTS: dict[int, tuple[str, str, str, str]] = {}


def L(addr: int, source: str, name: str, body: str, decl: str) -> None:
    LIFTS[addr] = (source, name, body.strip() + "\n", decl)


L(
    0x154540,
    "physics/point_physics.c",
    "FUN_00154540",
    """
/* FUN_00154540 (0x154540) — readable C lift from XBE leaf.
 * Asymmetric 1D rate integrate/dampen using coeffs[0..3] and signed scale. */
void FUN_00154540(float *accum, float *coeffs, float scale)
{
  float abs_scale;
  float a;
  float b;
  float lim;

  abs_scale = scale < 0.0f ? -scale : scale;
  a = abs_scale * coeffs[2];
  b = abs_scale * coeffs[3];

  if (scale > 0.0f) {
    if (*accum <= -b) {
      *accum = *accum + b;
    } else if (*accum >= 0.0f) {
      *accum = *accum + a;
    } else {
      *accum = (*accum / b + 1.0f) * a;
    }
    lim = abs_scale * coeffs[0];
    if (lim < *accum) {
      *accum = lim;
    }
  } else if (scale < 0.0f) {
    if (*accum >= b) {
      *accum = *accum - b;
    } else if (*accum <= 0.0f) {
      *accum = *accum - a;
    } else {
      *accum = (*accum / b - 1.0f) * a;
    }
    lim = -(abs_scale * coeffs[1]);
    if (lim > *accum) {
      *accum = lim;
    }
  }
}
""",
    "void FUN_00154540(float *accum, float *coeffs, float scale);",
)

L(
    0x14E940,
    "physics/collision_bsp.c",
    "FUN_0014e940",
    """
/* FUN_0014e940 (0x14e940) — readable C lift from XBE leaf.
 * Pill test against global collision BSP; fills a collision-result blob. */
char FUN_0014e940(int unused, float *origin, float *direction, float radius,
                  int pad0, int pad1, void *result)
{
  float t;
  float normal[3];
  char hit;
  unsigned char *res;
  float *res_f;
  void *bsp;
  unsigned int flt_max_bits;
  (void)unused;
  (void)pad0;
  (void)pad1;

  res = (unsigned char *)result;
  res_f = (float *)result;

  *(short *)(res + 0x00) = (short)-1;
  *(int *)(res + 0x04) = -1;
  *(short *)(res + 0x08) = (short)-1;
  *(int *)(res + 0x0c) = -1;
  *(short *)(res + 0x10) = (short)-1;
  res_f[5] = 1.0f; /* +0x14 */
  hit = 0;
  t = 0.0f;

  bsp = global_collision_bsp_get();
  if (collision_bsp_test_pill_new((int)bsp, 0, 0, (int)origin, (int)direction,
                                  radius, &t, normal)) {
    res_f[5] = t;
    res_f[9] = normal[0];
    res_f[10] = normal[1];
    res_f[11] = normal[2];
    *(short *)(res + 0x00) = 2;
    flt_max_bits = 0x7f7fffffu;
    res_f[12] = *(float *)&flt_max_bits; /* +0x30 */
    *(short *)(res + 0x34) = (short)-1;
    *(int *)(res + 0x44) = -1;
    *(int *)(res + 0x48) = -1;
    res[0x4c] = 0;
    res[0x4d] = 0;
    *(short *)(res + 0x4e) = (short)-1;
    hit = 1;
  }

  t = res_f[5];
  res_f[6] = origin[0] + t * direction[0];
  res_f[7] = origin[1] + t * direction[1];
  res_f[8] = origin[2] + t * direction[2];
  res_f[9] = 0.0f;
  res_f[10] = 0.0f;
  res_f[11] = 0.0f;
  return hit;
}
""",
    "char FUN_0014e940(int unused, float *origin, float *direction, float radius, int pad0, int pad1, void *result);",
)

L(
    0x14BDB0,
    "physics/collision_features.c",
    "collision_sphere_test_vector",
    """
/* collision_sphere_test_vector (0x14bdb0) — readable C lift from XBE leaf.
 * Ray vs sphere feature; writes hit t and contact plane. */
char collision_sphere_test_vector(void *sphere, float *origin, float *direction,
                                  float *out_t, float *out_plane)
{
  float *s;
  float dx, dy, dz;
  float radius;
  float c;
  float b;
  float a;
  float disc;
  float t;
  float mag;

  s = (float *)sphere;
  dx = s[3] - origin[0];
  dy = s[4] - origin[1];
  dz = s[5] - origin[2];
  radius = s[6];
  c = (dx * dx + dy * dy + dz * dz) - (radius * radius);

  if (!(c > 0.0f)) {
    *out_t = 0.0f;
  } else {
    b = dx * direction[0] + dy * direction[1] + dz * direction[2];
    if (!(b > 0.0f)) {
      return 0;
    }
    a = direction[0] * direction[0] + direction[1] * direction[1] +
        direction[2] * direction[2];
    disc = (b * b) - (a * c);
    if (disc < 0.0f) {
      return 0;
    }
    disc = sqrtf(disc);
    t = b - disc;
    if (!(t <= a)) {
      return 0;
    }
    *out_t = t / a;
  }

  t = *out_t;
  out_plane[0] = t * direction[0] - dx;
  out_plane[1] = t * direction[1] - dy;
  out_plane[2] = t * direction[2] - dz;
  mag = normalize3d(out_plane);
  if (mag == 0.0f) {
    out_plane[0] = 0.0f;
    out_plane[1] = 0.0f;
    out_plane[2] = 1.0f;
  }
  out_plane[3] = s[3] * out_plane[0] + s[4] * out_plane[1] + s[5] * out_plane[2] +
                 s[6];
  return 1;
}
""",
    "char collision_sphere_test_vector(void *sphere, float *origin, float *direction, float *out_t, float *out_plane);",
)

L(
    0x1493B0,
    "physics/collision_bsp.c",
    "collision_bsp_test_sphere",
    """
/* collision_bsp_test_sphere (0x1493b0) — readable C lift from XBE leaf.
 * Thin wrapper: build sphere state, recurse from node 0, return any-hit. */
int collision_bsp_test_sphere(int bsp, short flags, int breakable_surfaces,
                              int origin, float radius, int *results)
{
  int log_fn;
  collision_bsp_sphere_state state;

  log_fn = 6 + (bsp == *(int *)0x5064dc ? 1 : 0);
  collision_log_add_call((short)log_fn);
  collision_log_query_counter((void *)0x46f098);

  state.bsp = bsp;
  state.flags = (unsigned short)flags;
  state.pad0 = 0;
  state.breakable_surfaces = breakable_surfaces;
  state.origin = (float *)origin;
  state.radius = radius;
  state.results = results;
  state.plane_stack_count = 0;
  results[0xc0c / 4] = 0;
  results[0] = 0;
  results[0x404 / 4] = 0;
  results[0x808 / 4] = 0;

  bsp3d_test_sphere_recursive(&state, 0);
  collision_log_add_time((short)log_fn, *(unsigned int *)0x46f098,
                         *(int *)0x46f09c);

  if (results[0] > 0 || results[0x404 / 4] > 0) {
    return 1;
  }
  return 0;
}
""",
    "int collision_bsp_test_sphere(int bsp, short flags, int breakable_surfaces, int origin, float radius, int *results);",
)

def merge_remote_ported() -> int:
    subprocess.run(
        ["git", "fetch", "pastudan", "track-a-collision-bsp"],
        cwd=ROOT,
        capture_output=True,
    )
    r = subprocess.run(
        ["git", "show", "pastudan/track-a-collision-bsp:kb.json"],
        cwd=ROOT,
        capture_output=True,
        text=True,
    )
    if r.returncode != 0 or not r.stdout:
        return 0
    theirs = json.loads(r.stdout)
    ours = json.loads(KB_PATH.read_text(encoding="utf-8"))
    tmap = {
        int(fn["addr"], 16)
        for o in theirs.get("objects", [])
        for fn in o.get("functions") or []
        if isinstance(fn, dict) and fn.get("addr") and fn.get("ported") is True
    }
    n = 0
    for o in ours.get("objects", []):
        for fn in o.get("functions") or []:
            if (
                isinstance(fn, dict)
                and fn.get("addr")
                and int(fn["addr"], 16) in tmap
                and fn.get("ported") is not True
            ):
                fn["ported"] = True
                n += 1
    if n:
        KB_PATH.write_text(json.dumps(ours, indent=2) + "\n", encoding="utf-8")
        print(f"merged {n} remote ported:true", flush=True)
    return n


def locate_fn_block(text: str, name: str, addr: int) -> tuple[int, int] | None:
    span = find_naked_block(text, name, addr)
    if span:
        return span
    # Already-lifted readable C (or prior failed lift)
    pat = re.compile(
        rf"/\*[^*]*\b{name}\b[^*]*\(0x{addr:x}\)[\s\S]*?\n\}}\n",
        re.M | re.I,
    )
    m = pat.search(text)
    if m:
        return m.start(), m.end()
    return None


def apply_our_lifts(addrs: list[int]) -> list[dict]:
    results = []
    by_src: dict[str, list[int]] = {}
    for a in addrs:
        by_src.setdefault(LIFTS[a][0], []).append(a)
    for src, alist in by_src.items():
        path = ROOT / "src" / "halo" / src
        text = path.read_text(encoding="utf-8", errors="replace")
        before = text
        for a in sorted(alist, reverse=True):
            _s, name, body, decl = LIFTS[a]
            span = locate_fn_block(text, name, a)
            if span is None:
                print(f"FAIL locate {hex(a)} {name}", flush=True)
                results.append({"addr": hex(a), "ok": False, "err": "locate"})
                continue
            text = text[: span[0]] + body + "\n" + text[span[1] :]
            print(f"lifted {hex(a)} {name}", flush=True)
            results.append({"addr": hex(a), "name": name, "ok": True, "decl": decl})
            kb = json.loads(KB_PATH.read_text(encoding="utf-8"))
            for o in kb.get("objects", []):
                for fn in o.get("functions") or []:
                    if (
                        isinstance(fn, dict)
                        and fn.get("addr")
                        and int(fn["addr"], 16) == a
                    ):
                        fn["decl"] = decl
                        if not fn.get("name"):
                            fn["name"] = name
            KB_PATH.write_text(json.dumps(kb, indent=2) + "\n", encoding="utf-8")
        if text != before:
            path.write_text(text, encoding="utf-8")
    return results


def prove(name: str, addr: int, seeds: int = 100, timeout: float = 90.0) -> dict:
    if not ensure_oracle(addr):
        return {"ok": False, "err": "oracle", "passed": 0, "failed": 0, "errors": 0}
    env_extra = {"BIPED_SIBLING_RESOLVE": "1"}
    # run_unicorn already sets BIPED_SIBLING_RESOLVE
    res = run_unicorn(name, addr, seeds, timeout=timeout)
    if not clear_pass(res, seeds):
        res2 = run_unicorn(hex(addr), addr, seeds, timeout=timeout)
        if clear_pass(res2, seeds) or (res2.get("passed") or 0) > (res.get("passed") or 0):
            res = res2
    ok = clear_pass(res, seeds)
    return {
        "ok": ok,
        "passed": res.get("passed"),
        "failed": res.get("failed"),
        "errors": res.get("errors"),
        "rc": res.get("rc"),
        "tail": (res.get("tail") or "")[-300:],
    }


def commit_push(names: list[str]) -> str | None:
    merge_remote_ported()
    subprocess.run(
        ["git", "add", "kb.json", "tools/equivalence/leaf_cache.json"],
        cwd=ROOT,
        check=False,
    )
    subprocess.run(["git", "add", "-u", "src/halo"], cwd=ROOT, check=False)
    sample = ", ".join(names[:5])
    msg = f"lift(track-a): grokJ-solo Unicorn-prove {len(names)} ({sample})."
    r = subprocess.run(
        ["git", "commit", "-m", msg], cwd=ROOT, capture_output=True, text=True
    )
    if r.returncode != 0:
        print("commit failed", r.stdout, r.stderr, flush=True)
        return None
    sha = subprocess.run(
        ["git", "rev-parse", "HEAD"], cwd=ROOT, capture_output=True, text=True
    ).stdout.strip()
    subprocess.run(
        ["git", "pull", "--rebase", "pastudan", "track-a-collision-bsp"],
        cwd=ROOT,
        capture_output=True,
    )
    pr = subprocess.run(
        ["git", "push", "pastudan", "HEAD:track-a-collision-bsp"],
        cwd=ROOT,
        capture_output=True,
        text=True,
    )
    print(pr.stdout, pr.stderr, flush=True)
    print(f"COMMIT+PUSH {sha}", flush=True)
    return sha


def main() -> int:
    # Prefer smallest / no-list-walk first; skip vector wrapper until sphere walker proven
    order = [
        0x154540,  # pure float leaf
        0x14E940,  # pill wrapper, proven callees
        0x14BDB0,  # sphere feature math
        0x1493B0,  # sphere BSP wrapper
        # 0x149480 deferred — FUN_00148eb0 still naked/list-ish
    ]
    only = [int(x, 16) if x.startswith("0x") else int(x) for x in sys.argv[1:]]
    if only:
        order = only

    true0, false0 = count_ported(json.loads(KB_PATH.read_text(encoding="utf-8")))
    print(f"start true={true0} false={false0} tip={100*true0/(true0+false0):.2f}%", flush=True)

    apply_our_lifts(order)
    regen_decl_h()

    # compile touched TUs
    srcs = sorted({LIFTS[a][0] for a in order})
    for src in srcs:
        ok = docker_compile(src)
        print(f"compile {src}: {'ok' if ok else 'FAIL'}", flush=True)
        if not ok:
            return 1

    flips: list[str] = []
    for addr in order:
        name = LIFTS[addr][1]
        print(f"PROVE {hex(addr)} {name}", flush=True)
        res = prove(name, addr)
        print(
            f"  -> ok={res['ok']} {res.get('passed')}/{res.get('failed')}/{res.get('errors')} rc={res.get('rc')}",
            flush=True,
        )
        if res.get("tail") and not res["ok"]:
            print(res["tail"], flush=True)
        if res["ok"]:
            kb = json.loads(KB_PATH.read_text(encoding="utf-8"))
            if flip_kb(kb, addr):
                KB_PATH.write_text(json.dumps(kb, indent=2) + "\n", encoding="utf-8")
                flips.append(name)
                append_ledger(
                    {
                        "addr": hex(addr),
                        "name": name,
                        "ok": True,
                        "passed": res.get("passed"),
                        "failed": res.get("failed"),
                        "errors": res.get("errors"),
                        "tag": "grokJ-solo",
                    }
                )

    if flips:
        commit_push(flips)

    true1, false1 = count_ported(json.loads(KB_PATH.read_text(encoding="utf-8")))
    print(
        f"done flips={len(flips)} {flips} true={true1} false={false1} tip={100*true1/(true1+false1):.2f}%",
        flush=True,
    )
    return 0 if len(flips) >= 1 else 1


if __name__ == "__main__":
    raise SystemExit(main())
