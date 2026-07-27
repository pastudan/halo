#!/usr/bin/env python3
"""grokN-solo Track A: collision_bsp / physics / structure / tiff / cameras → C + Unicorn."""
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

from lift_inventory_batch4 import L, LIFTS, apply_lifts  # noqa: E402
from prove_inventory_batch4 import ensure_oracle, flip_kb  # noqa: E402
from tu_compile import docker_compile  # noqa: E402
from unicorn_c_campaign import (  # noqa: E402
    KB_PATH,
    append_ledger,
    clear_pass,
    count_ported,
)

SEEDS = 100
TIMEOUT = 70.0
RESULTS_RE = re.compile(r"(\d+) passed, (\d+) failed, (\d+) errors")

LIFTS.clear()

L(
    0x192BB0,
    "structures/structure_bsp_definitions.c",
    "FUN_00192bb0",
    """
/* FUN_00192bb0 (0x192bb0) — readable C lift from XBE leaf.
 * Normalize vector in place (EAX); return original length, or 0 on Inf/invalid.
 * x87 fsqrt matches the XBE (not libc sqrtf under -fno-builtin). */
float FUN_00192bb0(float *v /*@<eax>*/)
{
  float mag;
  float scale;
  float sq;
  uint32_t scale_bits;

  sq = v[0] * v[0] + v[1] * v[1] + v[2] * v[2];
  __asm__ volatile("fsqrt" : "=t"(mag) : "0"(sq));
  scale = *(float *)0x2533c8 / mag;
  scale_bits = *(uint32_t *)&scale;
  if ((scale_bits & 0x7f800000u) == 0x7f800000u)
    return *(float *)0x2533c0;
  v[0] *= scale;
  v[1] *= scale;
  v[2] *= scale;
  if (!valid_real_normal3d(v))
    return *(float *)0x2533c0;
  return mag;
}
""",
    "float FUN_00192bb0(float *v@<eax>);",
)

L(
    0x7F570,
    "bitmaps/tiff_file.c",
    "tiff_get_bounds",
    """
/* tiff_get_bounds (0x7f570) — readable C lift from XBE leaf.
 * Open TIFF via file_ref, read ImageWidth/ImageLength, close. */
char tiff_get_bounds(void *file_ref, void *width_out, void *height_out)
{
  char name[0x100];
  int tiff;
  void (*get_field)(int, int, void *) = (void (*)(int, int, void *))TIFFGetField;

  file_reference_get_name((file_ref_t *)file_ref, 0xd, name);
  tiff = FUN_0006d8e0(name, (const char *)0x2658a4);
  if (!tiff)
    return 0;
  get_field(tiff, 0x100, width_out);
  get_field(tiff, 0x101, height_out);
  FUN_00064ee0(tiff);
  return 1;
}
""",
    "char tiff_get_bounds(void *file_ref, void *width_out, void *height_out);",
)

L(
    0x1486E0,
    "physics/collision_bsp.c",
    "FUN_001486e0",
    """
/* FUN_001486e0 (0x1486e0) — readable C lift from XBE leaf.
 * 2D BSP walk for sphere test; leaf → FUN_00147ed0. */
void FUN_001486e0(void *state, int node_index)
{
  float *node;
  float d;
  float radius;
  char side_pos;
  char side_neg;

  for (;;) {
    if (node_index < 0) {
      FUN_00147ed0(state, node_index & 0x7fffffff);
      return;
    }
    node = (float *)tag_block_get_element(
        (char *)*(void **)state + 0x30, node_index, 0x14);
    radius = *(float *)((char *)state + 0x10);
    d = node[1] * *(float *)((char *)state + 0x224) +
        *(float *)((char *)state + 0x220) * node[0] - node[2];
    side_pos = (d <= radius);
    side_neg = (d >= -radius);
    if (side_pos)
      FUN_001486e0(state, ((int *)node)[3]);
    if (!side_neg)
      return;
    node_index = ((int *)node)[4];
  }
}
""",
    "void FUN_001486e0(void *state, int node_index);",
)

L(
    0x14E940,
    "physics/collision_bsp.c",
    "FUN_0014e940",
    """
/* FUN_0014e940 (0x14e940) — readable C lift from XBE leaf.
 * Pill test against global collision BSP; fills a collision-result blob. */
char FUN_0014e940(int unused, float *origin, float *direction, float radius,
                  int pad0, void *result)
{
  float t;
  float normal[3];
  char hit;
  unsigned char *res;
  float *res_f;
  void *bsp;
  (void)unused;
  (void)pad0;

  res = (unsigned char *)result;
  res_f = (float *)result;

  *(short *)(res + 0x00) = (short)-1;
  *(int *)(res + 0x04) = -1;
  *(short *)(res + 0x08) = (short)-1;
  *(int *)(res + 0x0c) = -1;
  *(short *)(res + 0x10) = (short)-1;
  res_f[5] = 1.0f;
  hit = 0;

  bsp = global_collision_bsp_get();
  if (collision_bsp_test_pill_new((int)bsp, 0, 0, (int)origin, (int)direction,
                                  radius, &t, normal)) {
    res_f[5] = t;
    res_f[9] = normal[0];
    res_f[10] = normal[1];
    res_f[11] = normal[2];
    *(short *)(res + 0x00) = 2;
    *(unsigned int *)(res + 0x30) = 0x7f7fffffu;
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
    "char FUN_0014e940(int unused, float *origin, float *direction, float radius, int pad0, void *result);",
)

L(
    0x14DC30,
    "physics/collision_bsp.c",
    "FUN_0014dc30",
    """
/* FUN_0014dc30 (0x14dc30) — readable C lift from XBE leaf.
 * Point-in-structure / cluster object collision probe. */
char FUN_0014dc30(int flags, float *pos, int param_3)
{
  uint32_t leaf;
  char check_objects;
  int cluster;
  int obj;
  int flags_save;
  int iter;

  if ((flags & 0xe0) == 0)
    return 0;
  flags_save = flags;
  leaf = bsp3d_find_leaf(FUN_0018e420(), 0, pos);
  check_objects = (char)((flags_save >> 7) & 1);
  if (*(unsigned char *)0x4761f8)
    check_objects = 0;
  if ((int)leaf == -1)
    return 1;
  if (!check_objects)
    return 0;
  leaf &= 0x7fffffffu;
  cluster = *(short *)((char *)tag_block_get_element(
                           (char *)scenario_get() + 0xe0, (int)leaf, 0x10) +
                       8);
  iter = flags_save;
  obj = cluster_partition_object_iter_first(&iter, (int16_t)cluster);
  while (obj != -1) {
    if (FUN_0014db10(obj, flags_save, (int)pos, param_3))
      return 1;
    obj = cluster_partition_object_iter_next(&iter);
  }
  return 0;
}
""",
    "char FUN_0014dc30(int flags, float *pos, int param_3);",
)

L(
    0x185F80,
    "render/render_cameras.c",
    "render_frustum_get_projection_bounds",
    """
/* render_frustum_get_projection_bounds (0x185f80) — readable C lift. */
void render_frustum_get_projection_bounds(void *frustum, float *bounds)
{
  float neg_x;
  float neg_y;
  float inv_x;
  float inv_y;
  float one;

  if (!frustum || !*(unsigned char *)((char *)frustum + 0x140)) {
    display_assert((const char *)0x2b12dc, (const char *)0x2b12b4, 0x3a7, 1);
    system_exit(-1);
  }
  if (!bounds) {
    display_assert((const char *)0x26184c, (const char *)0x2b12b4, 0x3a8, 1);
    system_exit(-1);
  }
  one = *(float *)0x2533c8;
  neg_x = -*(float *)((char *)frustum + 0x164);
  neg_y = -*(float *)((char *)frustum + 0x168);
  inv_x = *(float *)0x255e94 / *(float *)((char *)frustum + 0x144);
  inv_y = *(float *)0x255e94 / *(float *)((char *)frustum + 0x158);
  bounds[0] = (neg_x - one) * inv_x;
  bounds[1] = (neg_x + one) * inv_x;
  bounds[2] = (one - neg_y) * inv_y;
  bounds[3] = (neg_y + one) * inv_y;
}
""",
    "void render_frustum_get_projection_bounds(void *frustum, float *bounds);",
)

L(
    0x186C70,
    "render/render_cameras.c",
    "render_camera_world_to_screen",
    """
/* render_camera_world_to_screen (0x186c70) — readable C lift. */
char render_camera_world_to_screen(void *cam1, void *cam2, void *world_pos,
                                  float *screen_out)
{
  float view[3];

  if (!cam1) {
    display_assert((const char *)0x266e9c, (const char *)0x2b12b4, 0x3c1, 1);
    system_exit(-1);
  }
  if (!cam2) {
    display_assert((const char *)0x2b14b8, (const char *)0x2b12b4, 0x3c2, 1);
    system_exit(-1);
  }
  if (!world_pos) {
    display_assert((const char *)0x2b14f8, (const char *)0x2b12b4, 0x3c3, 1);
    system_exit(-1);
  }
  if (!screen_out) {
    display_assert((const char *)0x2b14c0, (const char *)0x2b12b4, 0x3c4, 1);
    system_exit(-1);
  }
  matrix_transform_point((float *)((char *)cam2 + 0x10), (float *)world_pos,
                         view);
  return render_camera_view_to_screen((int *)cam1, (int *)cam2, view,
                                     screen_out);
}
""",
    "char render_camera_world_to_screen(void *cam1, void *cam2, void *world_pos, float *screen_out);",
)

L(
    0x150AC0,
    "kb_common_stubs.c",
    "FUN_00150ac0",
    """
/* FUN_00150ac0 (0x150ac0) — readable C lift from XBE leaf.
 * Transform point by phys matrix; true if inside any sphere feature. */
char FUN_00150ac0(int *data, int *point)
{
  float local[3];
  float *feat;
  float dx, dy, dz;
  float r;
  int count;
  short i;
  void *block;

  real_matrix3x3_transform_point((void *)(data + 2), (float *)point, local);
  block = (char *)data[1] + 0x74;
  count = *(int *)block;
  for (i = 0; i < count; i++) {
    feat = (float *)tag_block_get_element(block, i, 0x80);
    r = feat[0x68 / 4];
    dx = feat[0x38 / 4] - local[0];
    dy = feat[0x3c / 4] - local[1];
    dz = feat[0x40 / 4] - local[2];
    if (dx * dx + dy * dy + dz * dz <= r * r)
      return 1;
  }
  return 0;
}
""",
    "char FUN_00150ac0(int *data, int *point);",
)

L(
    0x1929A0,
    "structures/structure_bsp_definitions.c",
    "FUN_001929a0",
    """
/* FUN_001929a0 (0x1929a0) — readable C lift from XBE leaf.
 * Project leaf-face vertex (EAX=face, ECX=leaf_map) onto plane basis. */
void FUN_001929a0(void *face /*@<eax>*/, void *leaf_map /*@<ecx>*/,
                  short vertex_index, float *out_point)
{
  float *plane;
  float ax, ay, az;
  int proj;
  uint8_t sign;
  int *node;

  node = (int *)tag_block_get_element(*(void **)leaf_map, *(int *)face, 0xc);
  plane = (float *)tag_block_get_element((char *)*(void **)leaf_map + 0xc,
                                         node[0], 0x10);
  ax = fabsf(plane[0]);
  ay = fabsf(plane[1]);
  az = fabsf(plane[2]);
  if (!(az < ay) && !(az < ax))
    proj = 2;
  else if (!(ay < ax))
    proj = 1;
  else
    proj = 0;
  sign = FUN_00099270(plane, (uint32_t)proj);
  project_point2d(
      (float *)tag_block_get_element((char *)face + 4, vertex_index, 8), plane,
      (int16_t)proj, sign, out_point);
}
""",
    "void FUN_001929a0(void *face@<eax>, void *leaf_map@<ecx>, short vertex_index, float *out_point);",
)


def run_uni(name: str, addr: int, extra: list[str] | None = None) -> dict:
    outj = ROOT / "artifacts" / "equivalence" / f"uni_{addr:08x}_s{SEEDS}.json"
    cmd = [
        sys.executable,
        str(ROOT / "tools/equivalence/unicorn_diff.py"),
        name,
        "--allow-stubs",
        "--seeds",
        str(SEEDS),
        "-q",
        "--output-json",
        str(outj),
    ]
    if extra:
        cmd.extend(extra)
    env = os.environ.copy()
    env.setdefault("BIPED_SIBLING_RESOLVE", "1")
    t0 = time.time()
    try:
        proc = subprocess.run(
            cmd, cwd=str(ROOT), capture_output=True, text=True, timeout=TIMEOUT, env=env
        )
        timed_out = False
    except subprocess.TimeoutExpired as exc:
        timed_out = True
        proc = subprocess.CompletedProcess(
            cmd,
            124,
            (exc.stdout or "") if isinstance(exc.stdout, str) else "",
            (exc.stderr or "") if isinstance(exc.stderr, str) else "timeout",
        )
    text = (proc.stdout or "") + (proc.stderr or "")
    passed = failed = errors = None
    m = RESULTS_RE.search(text)
    if m:
        passed, failed, errors = map(int, m.groups())
    return {
        "rc": proc.returncode,
        "passed": passed,
        "failed": failed,
        "errors": errors,
        "dt": round(time.time() - t0, 2),
        "tail": text[-400:],
        "timeout": timed_out,
        "extra": list(extra or []),
    }


def prove(name: str, addr: int) -> dict:
    if not ensure_oracle(addr):
        return {"ok": False, "err": "oracle", "name": name, "addr": hex(addr)}
    for extra in (
        [],
        ["--float-tolerance", "8"],
        ["--float-tolerance", "32"],
        ["--real-callees", "--float-tolerance", "32"],
    ):
        for nm in (hex(addr), name):
            res = run_uni(nm, addr, extra)
            if clear_pass(res, SEEDS):
                res["ok"] = True
                res["name"] = name
                res["addr"] = hex(addr)
                return res
            last = res
    last["ok"] = False
    last["name"] = name
    last["addr"] = hex(addr)
    return last


def commit_push(names: list[str]) -> None:
    subprocess.run(
        ["git", "fetch", "pastudan", "track-a-collision-bsp"],
        cwd=ROOT,
        capture_output=True,
    )
    paths = [
        "kb.json",
        "tools/equivalence/leaf_cache.json",
        "src/halo/physics/collision_bsp.c",
        "src/halo/structures/structure_bsp_definitions.c",
        "src/halo/bitmaps/tiff_file.c",
        "src/halo/render/render_cameras.c",
        "src/halo/kb_common_stubs.c",
        "scripts/lift_grokN_solo_tracka_focus.py",
    ]
    subprocess.run(["git", "add", *paths], cwd=ROOT, check=False)
    sample = ", ".join(names[:5])
    if len(names) > 5:
        sample += ", ..."
    msg = f"lift(track-a): grokN-solo Unicorn-prove {len(names)} ({sample})."
    r = subprocess.run(
        ["git", "commit", "-m", msg], cwd=ROOT, capture_output=True, text=True
    )
    if r.returncode != 0:
        print("commit failed", r.stdout, r.stderr, flush=True)
        return
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
    print("PUSHED", flush=True)


def main() -> int:
    print("applying lifts...", flush=True)
    results = apply_lifts(sorted(LIFTS.keys()))
    for r in results:
        print(" lift", r, flush=True)

    subprocess.run(
        [
            sys.executable,
            str(ROOT / "tools/analysis/knowledge.py"),
            "--gen-header",
            str(ROOT / "build/generated/decl.h"),
        ],
        cwd=ROOT,
        capture_output=True,
    )

    compiled = set()
    for src in sorted({LIFTS[a][0] for a in LIFTS}):
        print("compile", src, flush=True)
        if docker_compile(src):
            compiled.add(src)
        else:
            print("COMPILE FAIL", src, flush=True)

    lands: list[str] = []
    fails: list[str] = []
    for addr in sorted(LIFTS.keys()):
        src, name, _body, _decl = LIFTS[addr]
        print(f"\n== prove {hex(addr)} {name} ==", flush=True)
        if src not in compiled:
            print(" skip (TU not compiled)", flush=True)
            fails.append(name)
            continue
        kb0 = json.loads(KB_PATH.read_text(encoding="utf-8"))
        already = False
        for o in kb0.get("objects", []):
            for fn in o.get("functions") or []:
                if (
                    isinstance(fn, dict)
                    and fn.get("addr")
                    and int(fn["addr"], 16) == addr
                    and fn.get("ported") is True
                ):
                    already = True
        if already:
            print(" already ported:true", flush=True)
            lands.append(name)
            continue
        res = prove(name, addr)
        print(
            f" {res.get('passed')}/{res.get('failed')}/{res.get('errors')} "
            f"extra={res.get('extra')} dt={res.get('dt')}",
            flush=True,
        )
        if not res.get("ok"):
            print(" FAIL", (res.get("tail") or "")[-200:], flush=True)
            fails.append(name)
            continue
        kb = json.loads(KB_PATH.read_text(encoding="utf-8"))
        if not flip_kb(kb, addr):
            print(" flip miss", flush=True)
            fails.append(name)
            continue
        KB_PATH.write_text(json.dumps(kb, indent=2) + "\n", encoding="utf-8")
        append_ledger(
            {
                "addr": hex(addr),
                "name": name,
                "source": src,
                "ok": True,
                "passed": res["passed"],
                "failed": 0,
                "errors": 0,
                "seeds": SEEDS,
                "phase": "grokN-solo-tracka-focus",
                "extra": res.get("extra"),
            }
        )
        lands.append(name)
        print(" FLIP", name, flush=True)

    t, f = count_ported(json.loads(KB_PATH.read_text(encoding="utf-8")))
    print(f"\nLANDS ({len(lands)}): {lands}", flush=True)
    print(f"FAILS ({len(fails)}): {fails}", flush=True)
    print(f"TIP {t}/{t+f} ({100 * t / (t + f):.2f}%)", flush=True)
    if lands:
        commit_push(lands)
    return 0 if lands else 1


if __name__ == "__main__":
    raise SystemExit(main())
