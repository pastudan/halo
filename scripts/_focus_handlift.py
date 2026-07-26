#!/usr/bin/env python3
"""Hand-lift focus AI framed leaves → Unicorn 100/0/0 → commit+push."""
from __future__ import annotations

import json
import os
import subprocess
import sys
import time
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "scripts"))
sys.path.insert(0, str(ROOT / "tools" / "equivalence"))

from unicorn_c_campaign import KB_PATH, count_ported, resolve_src  # noqa: E402
from prove_inventory_batch4 import flip_kb  # noqa: E402
from lift_ai_campaign import (  # noqa: E402
    apply_body,
    load_names,
    merge_remote_kb,
    patch_decl_h,
    prove_addr,
    set_kb_decl,
)

START = time.time()
BUDGET = 85 * 60
TARGET = 20
SEEDS = 100
TIMEOUT = 60.0
os.environ["BIPED_SIBLING_RESOLVE"] = "1"

LIFTS: list[tuple[int, str, str, str, str | None]] = [
    (
        0x60200,
        "FUN_00060200",
        "ai/path.c",
        """/* FUN_00060200 (0x60200) — readable C lift. */
float FUN_00060200(void *path, int16_t heap_index)
{
  int16_t mapped;
  int16_t count;
  int idx;

  mapped = FUN_00060140(path, heap_index);
  count = *(int16_t *)((char *)path + 0x2c);
  if (mapped < 0 || mapped >= count || count > 0x80) {
    display_assert((const char *)0x25e9b0, (const char *)0x25ea14, 0x28, 1);
    system_exit(-1);
  }
  idx = (int)mapped + 2;
  return *(float *)((char *)path + (idx + idx * 4) * 8);
}
""",
        "float FUN_00060200(void *path, int16_t heap_index);",
    ),
    (
        0x1C0E0,
        "FUN_0001c0e0",
        "ai/actions.c",
        """/* FUN_0001c0e0 (0x1c0e0) — readable C lift. */
char FUN_0001c0e0(int actor_handle, char param_2, int state_data)
{
  char *actor;
  char *state;
  char result;

  actor = (char *)datum_get(*(data_t **)0x6325a4, actor_handle);
  state = (char *)state_data;
  result = 0;
  if (state == 0) {
    display_assert((const char *)0x25334c, (const char *)0x253f7c, 0x21, 1);
    system_exit(-1);
  }
  csmemset(state, 0, 0x18);
  if (actor[0x160] != 0) {
    return result;
  }
  state[1] = actor[0x1cc];
  state[2] = param_2;
  *(int *)(state + 8) = game_time_get();
  *(short *)(state + 0xe) = 0;
  *(short *)(state + 0xc) = 0x78;
  state[3] = 1;
  *(short *)(state + 0x10) = random_range(
      (unsigned int *)get_global_random_seed_address(), 0x12c, 0x258);
  return 1;
}
""",
        "char FUN_0001c0e0(int actor_handle, char param_2, int state_data);",
    ),
    (
        0x5F490,
        "path_attractor_weight",
        "ai/path.c",
        """/* path_attractor_weight (0x5f490) — readable C lift. */
float path_attractor_weight(void *path_state, float *node_pos, float *step_pos, float *out_dist)
{
  float closest[3];
  float *attractor;
  float dx, dy, dz;
  float dist_sq;
  float radius;
  float weight;
  float dist;

  attractor = (float *)((char *)path_state + 0x28);
  weight = 0.0f;
  dist = 3.402823466e+38f; /* FLT_MAX-ish 0x7f7fffff */
  closest_point_to_attractor(node_pos, step_pos, attractor, closest);
  dx = closest[0] - attractor[0];
  dy = closest[1] - attractor[1];
  dz = closest[2] - attractor[2];
  dist_sq = dx * dx + dy * dy + dz * dz;
  radius = *(float *)((char *)path_state + 0x38);
  if (dist_sq < radius * radius) {
    dist = __builtin_sqrtf(dist_sq);
    weight = (*(float *)0x2533c8 - dist / radius) * *(float *)((char *)path_state + 0x3c);
  }
  if (out_dist == 0) {
    display_assert((const char *)0x25e5c4, (const char *)0x25e0ac, 0x65f, 1);
    system_exit(-1);
  }
  *out_dist = dist;
  return weight;
}
""",
        "float path_attractor_weight(void *path_state, float *node_pos, float *step_pos, float *out_dist);",
    ),
    (
        0x53BF0,
        "FUN_00053bf0",
        "ai/encounters.c",
        """/* FUN_00053bf0 (0x53bf0) — readable C lift. */
void FUN_00053bf0(void)
{
  int16_t vals[3];

  vals[0] = 0x96;
  vals[1] = 0x12c;
  vals[2] = 0x1c2;
  crt_sprintf(
      (char *)0x5ab280,
      (const char *)0x25c218,
      (int)*(int16_t *)0x5ac76e,
      (int)*(int16_t *)0x5ac7f6,
      (int)*(int16_t *)0x5ac87e);
  FUN_00053800((void *)0x5ab280, 3, vals);
}
""",
        "void FUN_00053bf0(void);",
    ),
    (
        0x24060,
        "FUN_00024060",
        "ai/actor_firing_position.c",
        """/* FUN_00024060 (0x24060) — readable C lift. */
void FUN_00024060(void *unused, void *actor_meta, int16_t count, void *entries)
{
  int16_t n;
  char *ent;
  char *meta;
  float threshold;
  float score;
  int i;

  (void)unused;
  n = count;
  if (n <= 0) {
    return;
  }
  meta = (char *)actor_meta;
  ent = (char *)entries + 8;
  for (i = 0; i < (int)(unsigned short)n; i++) {
    if (ent[0x28] != 0) {
      score = 0.0f;
      threshold = *(float *)(meta + 0x18) * *(float *)0x253398;
      if (*(float *)ent < threshold) {
        score = 8.0f; /* 0x41000000 */
      } else if (*(float *)ent < *(float *)(meta + 0x18)) {
        score = (*(float *)(meta + 0x18) - *(float *)ent) * (*(float *)0x2533c8 / threshold)
                * *(float *)0x253f78;
        if (!(score < *(float *)0x2533c0 || score > *(float *)0x254cb8)) {
          /* in range */
        } else {
          display_assert((const char *)0x254c5c, (const char *)0x254c8c, 0x81, 1);
          system_exit(-1);
        }
      }
      *(float *)(ent + 0x30) = *(float *)(ent + 0x30) + score;
    }
    ent += 0x3c;
  }
}
""",
        "void FUN_00024060(void *unused, void *actor_meta, int16_t count, void *entries);",
    ),
]


def regen_decl() -> None:
    subprocess.run(
        [
            sys.executable,
            "tools/analysis/knowledge.py",
            "--gen-header",
            "build/generated/decl.h",
        ],
        cwd=ROOT,
        capture_output=True,
    )


def commit_push(name: str, paths: set[Path]) -> str | None:
    merge_remote_kb()
    for p in paths:
        if p:
            subprocess.run(["git", "add", str(p)], cwd=ROOT, check=False)
    subprocess.run(
        ["git", "add", "kb.json", "tools/equivalence/leaf_cache.json", "scripts/unicorn_c_campaign.py"],
        cwd=ROOT,
        check=False,
    )
    subprocess.run(["git", "add", "-u", "src/halo"], cwd=ROOT, check=False)
    msg = f"lift(track-a): {name} Unicorn-prove (ported:true)."
    r = subprocess.run(["git", "commit", "-m", msg], cwd=ROOT, capture_output=True, text=True)
    if r.returncode != 0:
        print("  commit fail:", (r.stderr or r.stdout)[-400:], flush=True)
        return None
    subprocess.run(["git", "stash", "push", "-u", "-m", "tmp-push"], cwd=ROOT, capture_output=True)
    subprocess.run(["git", "fetch", "pastudan", "track-a-collision-bsp"], cwd=ROOT, capture_output=True)
    rb = subprocess.run(
        ["git", "rebase", "pastudan/track-a-collision-bsp"],
        cwd=ROOT,
        capture_output=True,
        text=True,
    )
    if rb.returncode != 0:
        print("  rebase warn:", (rb.stderr or rb.stdout)[-300:], flush=True)
        subprocess.run(["git", "rebase", "--abort"], cwd=ROOT, capture_output=True)
    subprocess.run(["git", "stash", "pop"], cwd=ROOT, capture_output=True)
    merge_remote_kb()
    pr = subprocess.run(
        ["git", "push", "pastudan", "HEAD:track-a-collision-bsp"],
        cwd=ROOT,
        capture_output=True,
        text=True,
    )
    if pr.returncode != 0:
        print("  push warn:", (pr.stderr or "")[-400:], flush=True)
    return subprocess.run(
        ["git", "rev-parse", "--short", "HEAD"], cwd=ROOT, capture_output=True, text=True
    ).stdout.strip()


def main() -> int:
    regen_decl()
    (ROOT / "build" / "equivalence").mkdir(parents=True, exist_ok=True)
    kb0 = json.loads(KB_PATH.read_text())
    t0, f0 = count_ported(kb0)
    print(f"baseline true={t0} false={f0}", flush=True)

    _, name_by, decl_by, src_by, ported = load_names()
    proved: list[str] = []
    blockers: list[tuple[str, str]] = []

    for addr, name, src, body, new_decl in LIFTS:
        if time.time() - START > BUDGET or len(proved) >= TARGET:
            break
        if ported.get(addr) is True:
            print(f"skip true {name}", flush=True)
            continue
        print(f"\n== lift {hex(addr)} {name} ==", flush=True)
        path = resolve_src(src)
        if not path:
            blockers.append((name, "no_src"))
            continue
        orig_decl = decl_by.get(addr)
        if new_decl:
            # Reject prose / register annotations in kb decls.
            if "@<" in new_decl or "static " in new_decl:
                blockers.append((name, "prose_decl"))
                continue
            set_kb_decl(addr, new_decl)
            patch_decl_h(name, new_decl)
            regen_decl()
        orig, err = apply_body(path, name, addr, body)
        if err:
            print(f"  apply FAIL {err}", flush=True)
            if new_decl and orig_decl:
                set_kb_decl(addr, orig_decl)
            blockers.append((name, f"apply:{err}"))
            continue
        res = prove_addr(name, addr, SEEDS, TIMEOUT, src=src)
        print(
            f"  unicorn {res.get('passed')}/{res.get('failed')}/{res.get('errors')} "
            f"ok={res.get('ok')} err={res.get('err')}",
            flush=True,
        )
        if not res.get("ok"):
            path.write_text(orig, encoding="utf-8")
            if new_decl and orig_decl:
                set_kb_decl(addr, orig_decl)
                regen_decl()
            print("  REVERT", flush=True)
            blockers.append(
                (name, res.get("err") or f"{res.get('passed')}/{res.get('failed')}/{res.get('errors')}")
            )
            continue
        rc = subprocess.run(
            [sys.executable, "tools/audit/check_raw_casts.py"],
            cwd=ROOT,
            capture_output=True,
            text=True,
        )
        if rc.returncode != 0:
            path.write_text(orig, encoding="utf-8")
            if new_decl and orig_decl:
                set_kb_decl(addr, orig_decl)
            print("  REVERT raw-cast", flush=True)
            blockers.append((name, "raw-cast"))
            continue
        kb = json.loads(KB_PATH.read_text())
        if not flip_kb(kb, addr):
            blockers.append((name, "flip"))
            continue
        KB_PATH.write_text(json.dumps(kb, indent=2) + "\n")
        sha = commit_push(name, {path})
        print(f"  PROVED {name} sha={sha}", flush=True)
        proved.append(name)
        _, name_by, decl_by, src_by, ported = load_names()
        ported[addr] = True

    kb1 = json.loads(KB_PATH.read_text())
    t1, f1 = count_ported(kb1)
    summary = {
        "true0": t0,
        "false0": f0,
        "true1": t1,
        "false1": f1,
        "delta": t1 - t0,
        "proved": proved,
        "blockers": blockers,
        "elapsed": time.time() - START,
    }
    Path("/tmp/focus_handlift_summary.json").write_text(json.dumps(summary, indent=2))
    print("\n=== FINAL ===", flush=True)
    print(summary, flush=True)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
