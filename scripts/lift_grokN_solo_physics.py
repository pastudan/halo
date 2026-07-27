#!/usr/bin/env python3
"""grokN-solo: collision/physics commons + tiff_get_bounds + structure_bsp leaf."""
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

LIFTS.clear()

from prove_inventory_batch4 import ensure_oracle, flip_kb  # noqa: E402
from tu_compile import docker_compile  # noqa: E402
from unicorn_c_campaign import (  # noqa: E402
    KB_PATH,
    append_ledger,
    clear_pass,
    count_ported,
)

SEEDS = 100
TIMEOUT = 90.0

L(
    0x7F570,
    "bitmaps/tiff_file.c",
    "tiff_get_bounds",
    """
/* tiff_get_bounds (0x7f570) — readable C lift. */
char tiff_get_bounds(file_ref_t *info, void *out_width, void *out_height)
{
  char path[256];
  int tiff;
  void (*getfield)(int, int, void *);

  file_reference_get_name(info, 0xd, path);
  tiff = FUN_0006d8e0(path, (const char *)0x2658a4);
  if (!tiff)
    return 0;
  getfield = (void (*)(int, int, void *))TIFFGetField;
  getfield(tiff, 0x100, out_width);
  getfield(tiff, 0x101, out_height);
  FUN_00064ee0(tiff);
  return 1;
}
""",
    "char tiff_get_bounds(file_ref_t *info, void *out_width, void *out_height);",
)

L(
    0x150AC0,
    "kb_common_stubs.c",
    "FUN_00150ac0",
    """
/* FUN_00150ac0 (0x150ac0) — readable C lift: point inside any phys sphere. */
char FUN_00150ac0(int *data, int *point)
{
  float local[3];
  void *block;
  int count;
  short i;
  void *elem;
  float dx, dy, dz;
  float dist_sq;
  float radius;

  real_matrix3x3_transform_point((char *)data + 8, (float *)point, local);
  block = (char *)data[1] + 0x74;
  count = *(int *)((char *)data[1] + 0x74);
  if (count <= 0)
    return 0;
  for (i = 0; i < count; i++) {
    elem = tag_block_get_element(block, i, 0x80);
    radius = *(float *)((char *)elem + 0x68);
    dx = *(float *)((char *)elem + 0x38) - local[0];
    dy = *(float *)((char *)elem + 0x3c) - local[1];
    dz = *(float *)((char *)elem + 0x40) - local[2];
    dist_sq = dx * dx + dy * dy + dz * dz;
    if (dist_sq <= radius * radius)
      return 1;
  }
  return 0;
}
""",
    "char FUN_00150ac0(int *data, int *point);",
)

L(
    0x1509C0,
    "kb_common_stubs.c",
    "FUN_001509c0",
    """
/* FUN_001509c0 (0x1509c0) — readable C lift: build object phys feature state. */
char FUN_001509c0(int *out, int obj_idx)
{
  void *obj;
  void *obj_tag;
  void *phys;
  float *matrix;
  float *forward;
  float *up;
  float *right;
  float local[3];
  float *position;

  obj = object_get_and_verify_type(obj_idx, -1);
  obj_tag = tag_get(0x6f626a65, *(int *)obj);
  if (*(int *)((char *)obj_tag + 0x8c) == -1)
    return 0;
  out[0] = obj_idx;
  phys = tag_get(0x70687973, *(int *)((char *)obj_tag + 0x8c));
  out[1] = (int)phys;
  matrix = (float *)((char *)out + 8);
  matrix[0] = 1.0f;
  position = (float *)((char *)out + 0x30);
  object_get_world_position(obj_idx, (vector3_t *)position);
  forward = (float *)((char *)out + 0xc);
  up = (float *)((char *)out + 0x24);
  object_get_orientation(obj_idx, forward, up);
  right = (float *)((char *)out + 0x18);
  right[0] = up[1] * forward[2] - forward[1] * up[2];
  right[1] = forward[0] * up[2] - up[0] * forward[2];
  right[2] = up[0] * forward[1] - forward[0] * up[1];
  local[0] = -*(float *)((char *)phys + 0xc);
  local[1] = -*(float *)((char *)phys + 0x10);
  local[2] = -*(float *)((char *)phys + 0x14);
  matrix_transform_point(matrix, local, local);
  position[0] = local[0];
  position[1] = local[1];
  position[2] = local[2];
  return 1;
}
""",
    "char FUN_001509c0(int *out, int obj_idx);",
)

L(
    0x150790,
    "kb_common_stubs.c",
    "FUN_00150790",
    """
/* FUN_00150790 (0x150790) — readable C lift: phys spheres -> collision features. */
char FUN_00150790(void *phys_state, float *origin, float radius, float param_5,
                  float param_6, void *features)
{
  void *phys;
  void *block;
  int count;
  short i;
  void *elem;
  float world_point[3];
  float sphere_radius;
  int radius_bits;
  short *hdr;

  (void)origin;
  (void)radius;
  phys = *(void **)((char *)phys_state + 4);
  block = (char *)phys + 0x74;
  count = *(int *)((char *)phys + 0x74);
  for (i = 0; i < count; i++) {
    elem = tag_block_get_element(block, i, 0x80);
    matrix_transform_point((float *)((char *)phys_state + 8),
                           (float *)((char *)elem + 0x38), world_point);
    sphere_radius = *(float *)((char *)elem + 0x68) *
                    *(float *)((char *)phys_state + 8) +
                    param_6;
    radius_bits = *(int *)&sphere_radius;
    collision_features_from_point((int)world_point, param_5, radius_bits,
                                  *(int *)phys_state, -1, 0, 0xff, -1, features);
  }
  hdr = (short *)features;
  if (hdr[0] != 0 || hdr[1] != 0 || hdr[2] != 0)
    return 1;
  return 0;
}
""",
    "char FUN_00150790(void *phys_state, float *origin, float radius, float param_5, float param_6, void *features);",
)

L(
    0x150B60,
    "kb_common_stubs.c",
    "FUN_00150b60",
    """
/* FUN_00150b60 (0x150b60) — readable C lift: ray vs phys spheres. */
char FUN_00150b60(void *features, float *origin, float *direction,
                  float *out_t_plane)
{
  float local_origin[3];
  float local_dir[3];
  float normal[3];
  float t_slot;
  float *matrix;
  void *phys;
  void *block;
  int count;
  short i;
  void *elem;
  char hit;
  float best_t;
  float hit_x, hit_y, hit_z;

  hit = 0;
  matrix = (float *)((char *)features + 8);
  out_t_plane[0] = 3.402823466e+38f;
  real_matrix3x3_transform_point(matrix, origin, local_origin);
  real_matrix3x3_transform_vector(matrix, direction, local_dir);
  phys = *(void **)((char *)features + 4);
  block = (char *)phys + 0x74;
  count = *(int *)((char *)phys + 0x74);
  if (count <= 0)
    return 0;
  for (i = 0; i < count; i++) {
    elem = tag_block_get_element(block, i, 0x80);
    /* XBE arg order: center, radius, ray_origin, ray_dir, out_t, out_normal */
    if (FUN_0010d380((float *)((char *)elem + 0x38),
                     *(float *)((char *)elem + 0x68), local_origin, local_dir,
                     &t_slot, normal)) {
      best_t = out_t_plane[0];
      if (!(best_t <= t_slot)) {
        out_t_plane[0] = t_slot;
        out_t_plane[1] = normal[0];
        out_t_plane[2] = normal[1];
        out_t_plane[3] = normal[2];
        hit_x = local_dir[0] * t_slot + local_origin[0];
        hit_y = local_dir[1] * t_slot + local_origin[1];
        hit_z = local_dir[2] * t_slot + local_origin[2];
        out_t_plane[4] = hit_x * out_t_plane[1] + hit_y * out_t_plane[2] +
                         hit_z * out_t_plane[3];
        hit = 1;
      }
    }
  }
  if (hit)
    FUN_0010a1c0(matrix, out_t_plane + 1, out_t_plane + 1);
  return hit;
}
""",
    "char FUN_00150b60(void *features, float *origin, float *direction, float *out_t_plane);",
)

L(
    0x1508B0,
    "kb_common_stubs.c",
    "FUN_001508b0",
    """
/* FUN_001508b0 (0x1508b0) — readable C lift: debug-draw phys spheres. */
void FUN_001508b0(int *state)
{
  void *obj;
  void *obj_tag;
  float center[3];
  float *matrix;
  void *phys;
  void *block;
  int count;
  short i;
  void *elem;
  float world_point[3];
  float axis_a[3];
  float axis_b[3];
  float radius;

  obj = object_get_and_verify_type(state[0], -1);
  obj_tag = tag_get(0x6f626a65, *(int *)obj);
  matrix = (float *)((char *)state + 8);
  phys = (void *)state[1];
  matrix_transform_point(matrix, (float *)((char *)phys + 0xc), center);
  FUN_0018a990(1, center, (float *)((char *)state + 0xc),
               (float *)((char *)state + 0x24), *(float *)((char *)obj_tag + 4));
  block = (char *)phys + 0x74;
  count = *(int *)((char *)phys + 0x74);
  for (i = 0; i < count; i++) {
    elem = tag_block_get_element(block, i, 0x80);
    matrix_transform_point(matrix, (float *)((char *)elem + 0x38), world_point);
    matrix_transform_vector(matrix, (float *)((char *)elem + 0x44), axis_a);
    matrix_transform_vector(matrix, (float *)((char *)elem + 0x50), axis_b);
    radius = *(float *)((char *)elem + 0x68);
    FUN_00189540(1, world_point, radius, *(void **)0x2ee6c4);
    FUN_0018a990(1, world_point, axis_a, axis_b, radius * *(float *)0x253398);
  }
}
""",
    "void FUN_001508b0(int *state);",
)

L(
    0x1935F0,
    "structures/structure_bsp_definitions.c",
    "structure_bsp_find_material_for_surface",
    """
/* structure_bsp_find_material_for_surface (0x1935f0) — readable C lift. */
void structure_bsp_find_material_for_surface(void *scenario, int surface_index,
                                             int16_t *out_collection_index,
                                             int16_t *out_geometry_index)
{
  void *collections;
  int16_t lo;
  int16_t hi;
  int16_t mid;
  void *coll;
  void *geoms;
  void *first_geom;
  void *last_geom;
  void *geom;
  int start;
  int end;

  *out_collection_index = 0;
  collections = (char *)scenario + 0x104;
  hi = (int16_t)(*(int16_t *)((char *)scenario + 0x104) - 1);
  lo = 0;
  if (hi > 0) {
    while (hi > lo) {
      mid = (int16_t)(lo + ((hi - lo) >> 1));
      *out_collection_index = mid;
      coll = tag_block_get_element(collections, mid, 0x20);
      geoms = (char *)coll + 0x14;
      first_geom = tag_block_get_element(geoms, 0, 0x100);
      if (surface_index < *(int *)((char *)first_geom + 0x14)) {
        hi = (int16_t)(*out_collection_index - 1);
        *out_collection_index = hi;
      } else {
        last_geom = tag_block_get_element(
            geoms, *(int *)geoms - 1, 0x100);
        end = *(int *)((char *)last_geom + 0x14) +
              *(int *)((char *)first_geom + 0x18);
        /* match XBE: last elem for end uses first_geom's +0x18? No — asm: */
        /* re-fetch last for +0x14 and prior last's +0x18 */
        {
          void *last2 = tag_block_get_element(geoms, *(int *)geoms - 1, 0x100);
          void *last1 = tag_block_get_element(geoms, *(int *)geoms - 1, 0x100);
          (void)last1;
          end = *(int *)((char *)last2 + 0x14) +
                *(int *)((char *)last_geom + 0x18);
        }
        /* Prefer exact asm: edi=first last fetch, eax=second last fetch */
        {
          void *elem_a;
          void *elem_b;
          elem_a = tag_block_get_element(geoms, *(int *)geoms - 1, 0x100);
          elem_b = tag_block_get_element(geoms, *(int *)geoms - 1, 0x100);
          end = *(int *)((char *)elem_b + 0x14) +
                *(int *)((char *)elem_a + 0x18);
        }
        if (surface_index < end)
          break;
        lo = (int16_t)(*out_collection_index + 1);
        *out_collection_index = lo;
      }
      if (!(hi > lo))
        break;
    }
  }

  coll = tag_block_get_element(collections, *out_collection_index, 0x20);
  geoms = (char *)coll + 0x14;
  *out_geometry_index = 0;
  hi = *(int16_t *)geoms;
  lo = 0;
  if (hi > 0) {
    while (lo < hi) {
      mid = (int16_t)(lo + ((hi - lo) >> 1));
      *out_geometry_index = mid;
      geom = tag_block_get_element(geoms, mid, 0x100);
      start = *(int *)((char *)geom + 0x14);
      if (surface_index < start) {
        hi = (int16_t)(*out_geometry_index - 1);
        *out_geometry_index = hi;
      } else {
        end = start + *(int *)((char *)geom + 0x18);
        if (surface_index < end)
          break;
        lo = (int16_t)(*out_geometry_index + 1);
        *out_geometry_index = lo;
      }
    }
  }

  geom = tag_block_get_element(geoms, *out_geometry_index, 0x100);
  start = *(int *)((char *)geom + 0x14);
  if (surface_index < start) {
    display_assert((const char *)0x2b2c74, (const char *)0x2b2bf8, 0x66, 1);
    system_exit(-1);
  }
  end = start + *(int *)((char *)geom + 0x18);
  if (surface_index >= end) {
    display_assert((const char *)0x2b2c30, (const char *)0x2b2bf8, 0x67, 1);
    system_exit(-1);
  }
}
""",
    "void structure_bsp_find_material_for_surface(void *scenario, int surface_index, int16_t *out_collection_index, int16_t *out_geometry_index);",
)


def run_uni(name: str, addr: int) -> dict:
    outj = ROOT / "artifacts" / "equivalence" / f"uni_{addr:08x}_s{SEEDS}.json"
    logp = ROOT / "artifacts" / "equivalence" / f"{name}_smoke.log"
    outj.parent.mkdir(parents=True, exist_ok=True)
    cmd = [
        sys.executable,
        str(ROOT / "tools/equivalence/unicorn_diff.py"),
        name,
        "--allow-stubs",
        "--no-stub-arg-trace",
        "--seeds",
        str(SEEDS),
        "-q",
        "--output-json",
        str(outj),
    ]
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
        proc = subprocess.CompletedProcess(cmd, 124, exc.stdout or "", "timeout")
    text = (proc.stdout or "") + (proc.stderr or "")
    logp.write_text(text, encoding="utf-8", errors="replace")
    m = re.search(r"(\d+) passed, (\d+) failed, (\d+) errors", text)
    passed = failed = errors = None
    if m:
        passed, failed, errors = map(int, m.groups())
    elif outj.exists():
        try:
            payload = json.loads(outj.read_text())
            passed = payload.get("passed", payload.get("seeds_passed"))
            failed = payload.get("failed", payload.get("seeds_failed"))
            errors = payload.get("errors", payload.get("seeds_errors"))
        except Exception:
            pass
    return {
        "passed": passed,
        "failed": failed,
        "errors": errors,
        "dt": round(time.time() - t0, 2),
        "timeout": timed_out,
        "tail": text[-1000:],
    }


def merge_remote() -> None:
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
        return
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


def main() -> int:
    # Fix structure_bsp body: write a clean version without the draft mess
    LIFTS[0x1935F0] = (
        "structures/structure_bsp_definitions.c",
        "structure_bsp_find_material_for_surface",
        """
/* structure_bsp_find_material_for_surface (0x1935f0) — readable C lift. */
void structure_bsp_find_material_for_surface(void *scenario, int surface_index,
                                             int16_t *out_collection_index,
                                             int16_t *out_geometry_index)
{
  void *collections;
  int16_t lo;
  int16_t hi;
  int16_t mid;
  void *coll;
  void *geoms;
  void *elem;
  void *elem_a;
  void *elem_b;
  int start;
  int end;

  *out_collection_index = 0;
  collections = (char *)scenario + 0x104;
  hi = (int16_t)(*(int16_t *)((char *)scenario + 0x104) - 1);
  lo = 0;
  if (hi > 0) {
    for (;;) {
      mid = (int16_t)(lo + ((hi - lo) >> 1));
      *out_collection_index = mid;
      coll = tag_block_get_element(collections, mid, 0x20);
      geoms = (char *)coll + 0x14;
      elem = tag_block_get_element(geoms, 0, 0x100);
      if (surface_index < *(int *)((char *)elem + 0x14)) {
        hi = (int16_t)(*out_collection_index - 1);
        *out_collection_index = hi;
      } else {
        elem_a = tag_block_get_element(geoms, *(int *)geoms - 1, 0x100);
        elem_b = tag_block_get_element(geoms, *(int *)geoms - 1, 0x100);
        end = *(int *)((char *)elem_b + 0x14) +
              *(int *)((char *)elem_a + 0x18);
        if (surface_index < end)
          break;
        lo = (int16_t)(*out_collection_index + 1);
        *out_collection_index = lo;
      }
      if (hi <= lo)
        break;
    }
  }

  coll = tag_block_get_element(collections, *out_collection_index, 0x20);
  geoms = (char *)coll + 0x14;
  *out_geometry_index = 0;
  hi = *(int16_t *)geoms;
  lo = 0;
  if (hi > 0) {
    for (;;) {
      mid = (int16_t)(lo + ((hi - lo) >> 1));
      *out_geometry_index = mid;
      elem = tag_block_get_element(geoms, mid, 0x100);
      start = *(int *)((char *)elem + 0x14);
      if (surface_index < start) {
        hi = (int16_t)(*out_geometry_index - 1);
        *out_geometry_index = hi;
      } else {
        end = start + *(int *)((char *)elem + 0x18);
        if (surface_index < end)
          break;
        lo = (int16_t)(*out_geometry_index + 1);
        *out_geometry_index = lo;
      }
      if (lo >= hi)
        break;
    }
  }

  elem = tag_block_get_element(geoms, *out_geometry_index, 0x100);
  start = *(int *)((char *)elem + 0x14);
  if (surface_index < start) {
    display_assert((const char *)0x2b2c74, (const char *)0x2b2bf8, 0x66, 1);
    system_exit(-1);
  }
  end = start + *(int *)((char *)elem + 0x18);
  if (surface_index >= end) {
    display_assert((const char *)0x2b2c30, (const char *)0x2b2bf8, 0x67, 1);
    system_exit(-1);
  }
}
""".strip()
        + "\n",
        "void structure_bsp_find_material_for_surface(void *scenario, int surface_index, int16_t *out_collection_index, int16_t *out_geometry_index);",
    )

    order = [
        (0x7F570, "tiff_get_bounds", "bitmaps/tiff_file.c"),
        (0x150AC0, "FUN_00150ac0", "kb_common_stubs.c"),
        (0x1509C0, "FUN_001509c0", "kb_common_stubs.c"),
        (0x150790, "FUN_00150790", "kb_common_stubs.c"),
        (0x150B60, "FUN_00150b60", "kb_common_stubs.c"),
        (0x1508B0, "FUN_001508b0", "kb_common_stubs.c"),
        (0x1935F0, "structure_bsp_find_material_for_surface", "structures/structure_bsp_definitions.c"),
    ]

    results = apply_lifts([a for a, _, _ in order])
    print(f"lifted {results}", flush=True)
    if not any(r.get("ok") for r in results):
        return 1

    # Update kb decls for lifted symbols
    kb = json.loads(KB_PATH.read_text(encoding="utf-8"))
    decl_map = {a: LIFTS[a][3] for a in LIFTS if LIFTS[a][3]}
    for o in kb.get("objects", []):
        for fn in o.get("functions") or []:
            if not isinstance(fn, dict) or not fn.get("addr"):
                continue
            a = int(fn["addr"], 16)
            if a in decl_map:
                fn["decl"] = decl_map[a]
                if LIFTS[a][1] and not fn.get("name"):
                    fn["name"] = LIFTS[a][1]
    KB_PATH.write_text(json.dumps(kb, indent=2) + "\n", encoding="utf-8")

    r = subprocess.run(
        [
            sys.executable,
            str(ROOT / "tools/analysis/knowledge.py"),
            "--gen-header",
            str(ROOT / "build/generated/decl.h"),
        ],
        cwd=ROOT,
        capture_output=True,
        text=True,
    )
    if r.returncode != 0:
        print("regen FAIL", (r.stderr or r.stdout)[-600:], flush=True)
        return 1

    proven = []
    for addr, name, src in order:
        print(f"== compile {src} / prove {name} ==", flush=True)
        if not docker_compile(src):
            print(f"COMPILE FAIL {src}", flush=True)
            continue
        if not ensure_oracle(addr):
            print(f"oracle FAIL {name}", flush=True)
            continue
        res = run_uni(name, addr)
        print(name, res.get("passed"), res.get("failed"), res.get("errors"), res.get("dt"), flush=True)
        if not clear_pass(res, SEEDS):
            # retry by hex
            res2 = run_uni(hex(addr), addr)
            print("retry", hex(addr), res2.get("passed"), res2.get("failed"), res2.get("errors"), flush=True)
            if clear_pass(res2, SEEDS):
                res = res2
            else:
                print("FAIL", (res.get("tail") or "")[-500:], flush=True)
                continue
        kb = json.loads(KB_PATH.read_text(encoding="utf-8"))
        if flip_kb(kb, addr):
            KB_PATH.write_text(json.dumps(kb, indent=2) + "\n", encoding="utf-8")
        append_ledger(
            {
                "addr": hex(addr),
                "name": name,
                "source": src,
                "ok": True,
                "passed": 100,
                "failed": 0,
                "errors": 0,
                "seeds": 100,
                "phase": "grokN-solo-physics",
            }
        )
        proven.append(name)

    if not proven:
        print("no proofs", flush=True)
        return 1

    merge_remote()
    files = [
        "kb.json",
        "tools/equivalence/leaf_cache.json",
        "scripts/lift_grokN_solo_physics.py",
        "src/halo/bitmaps/tiff_file.c",
        "src/halo/kb_common_stubs.c",
        "src/halo/structures/structure_bsp_definitions.c",
    ]
    subprocess.run(["git", "add", *files], cwd=ROOT, capture_output=True)
    sample = ", ".join(proven[:4])
    if len(proven) > 4:
        sample += ", ..."
    msg = f"lift(track-a): {sample} Unicorn-prove {len(proven)}."
    cr = subprocess.run(
        ["git", "commit", "-m", msg], cwd=ROOT, capture_output=True, text=True
    )
    print("commit", cr.returncode, cr.stdout[-200:] if cr.stdout else cr.stderr[-200:], flush=True)
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
    print("pushed", pr.returncode, pr.stderr[-300:] if pr.stderr else pr.stdout[-300:], flush=True)
    t, f = count_ported(json.loads(KB_PATH.read_text(encoding="utf-8")))
    print(f"PROVEN {proven}", flush=True)
    print(f"TIP {t}/{t+f}", flush=True)
    return 0 if proven and pr.returncode == 0 else 1


if __name__ == "__main__":
    raise SystemExit(main())
