#!/usr/bin/env python3
"""grokP-solo3: exclusive dynavobgeom + hs non-hangers + ui_widget non list-walk."""
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
    0x160DC0,
    "rasterizer/xbox/rasterizer_xbox_dynavobgeom.c",
    "FUN_00160dc0",
    """
/* FUN_00160dc0 (0x160dc0) — readable C lift. */
void FUN_00160dc0(void *bitmap)
{
  short mode;
  unsigned int v;
  unsigned int seed;

  if (!*(int *)0x476ab0) {
    display_assert((const char *)0x29dc40, (const char *)0x2a18c0, 0x44, 1);
    system_exit(-1);
  }
  mode = *(short *)0x3256bc;
  if (mode != 0 && mode != 2 && mode != 6 && mode != 3 && mode != 4 &&
      mode != 7 && mode != 5 && mode != 8)
    return;
  if (!*(unsigned char *)0x3256c9)
    return;

  if (bitmap) {
    rasterizer_set_texture_bitmap_data(2, bitmap);
    D3DDevice_SetTextureStageState(2, 0xa, 3);
    D3DDevice_SetTextureStageState(2, 0xb, 3);
    v = (*(unsigned char *)0x3256ed != 0) ? 2u : 1u;
    D3DDevice_SetTextureStageState(2, 0xd, v);
    v = (*(unsigned char *)0x3256ed != 0) ? 2u : 1u;
    D3DDevice_SetTextureStageState(2, 0xe, v);
    v = (*(unsigned char *)0x3256ed != 0) ? 2u : 1u;
    D3DDevice_SetTextureStageState(2, 0xf, v);
    *(unsigned char *)0x47dca4 = 0;
  } else {
    D3DDevice_SetTexture(2, 0);
    *(unsigned char *)0x47dca4 = 1;
  }

  mode = *(short *)0x3256b0;
  if (mode <= 0)
    return;
  if (mode == 2) {
    *(float *)0x47dca0 = *(float *)0x3256e4;
    *(float *)0x47dc9c = *(float *)0x3256e4;
    *(float *)0x47dc98 = *(float *)0x3256e4;
    return;
  }
  seed = (unsigned int)bitmap;
  *(float *)0x47dc98 = random_math_real(&seed);
  *(float *)0x47dc9c = random_math_real(&seed);
  *(float *)0x47dca0 = random_math_real(&seed);
}
""",
    "void FUN_00160dc0(void *bitmap);",
)

L(
    0xC9C80,
    "hs/hs_runtime.c",
    "FUN_000c9c80",
    """
/* FUN_000c9c80 (0xc9c80) — readable C lift: permute object region by name. */
void FUN_000c9c80(int object_handle, int region_name, int variant)
{
  void *obj;
  void *tag;
  int model_index;
  void *model_tag;
  void *regions;
  int count;
  int i;
  short found;
  void *elem;

  if (object_handle == -1)
    return;
  obj = object_get_and_verify_type(object_handle, -1);
  tag = tag_get(0x6f626a65, *(int *)obj);
  found = -1;
  if (csstrcmp((const char *)region_name, (const char *)0x25386f) != 0) {
    model_index = *(int *)((char *)tag + 0x34);
    if (model_index != -1) {
      model_tag = tag_get(0x6d6f6465, model_index);
      regions = (char *)model_tag + 0xc4;
      count = *(int *)regions;
      for (i = 0; i < count; i++) {
        elem = tag_block_get_element(regions, i, 0x4c);
        if (crt_stricmp((const char *)elem, (const char *)region_name) == 0) {
          found = (short)i;
          break;
        }
      }
    }
  }
  object_permute_region(object_handle, (const char *)variant, found, 1);
}
""",
    "void FUN_000c9c80(int object_handle, int region_name, int variant);",
)

L(
    0xCA700,
    "hs/hs_runtime.c",
    "FUN_000ca700",
    """
/* FUN_000ca700 (0xca700) — readable C lift: allocate HS thread/stack data. */
void FUN_000ca700(void)
{
  data_t *threads;
  data_t *stack;
  int need;
  short i;
  int handle;

  threads = game_state_data_new((char *)0x2805e8, 0x100, 0x218);
  stack = game_state_data_new((char *)0x2805dc, 0x400, 8);
  *(data_t **)0x5aa6c4 = threads;
  *(data_t **)0x5aa6c0 = stack;
  if (!threads || !stack) {
    error(0, (const char *)0x280564);
    return;
  }
  need = (int)*(short *)0x27d504 * 2;
  if (need >= 0x400) {
    display_assert((const char *)0x280598, (const char *)0x2805bc, 0xa9, 1);
    system_exit(-1);
    stack = *(data_t **)0x5aa6c0;
  }
  data_delete_all(stack);
  for (i = 0; i < *(short *)0x27d504; i++) {
    handle = data_new_datum(*(data_t **)0x5aa6c0, (int)i | 0xaced0000);
    if (handle == -1) {
      display_assert((const char *)0x28058c, (const char *)0x2805bc, 0xb1, 1);
      system_exit(-1);
    }
  }
}
""",
    "void FUN_000ca700(void);",
)

L(
    0xC88B0,
    "hs/hs_runtime.c",
    "FUN_000c88b0",
    """
/* FUN_000c88b0 (0xc88b0) — readable C lift: hs type-check binary op args. */
char FUN_000c88b0(int16_t function_index, int root_datum)
{
  char ok;
  int out_handles[2];
  void *entry;
  const char *name;
  int left;
  int right;

  ok = 0;
  if (function_index != 0xd && function_index != 0xe) {
    display_assert((const char *)0x27d028, (const char *)0x27cdc0, 0x1bc, 1);
    system_exit(-1);
  }
  entry = hs_function_table_get(function_index);
  name = *(const char **)((char *)entry + 4);
  if (!FUN_000c55d0(name, out_handles, 2, root_datum))
    return 0;
  left = out_handles[0];
  right = out_handles[1];
  if (hs_type_check(left, 0)) {
    if (hs_type_check(
            right,
            *(short *)((char *)datum_get(*(data_t **)0x5aa6c8, left) + 4)))
      ok = 1;
  } else if (!*(int *)0x46b6fc) {
    if (hs_type_check(right, 0)) {
      if (hs_type_check(
              left,
              *(short *)((char *)datum_get(*(data_t **)0x5aa6c8, right) + 4)))
        ok = 1;
    } else if (!*(int *)0x46b6fc) {
      if (hs_type_check(left, 6) && hs_type_check(right, 6))
        ok = 1;
    }
  }
  return ok;
}
""",
    "char FUN_000c88b0(int16_t function_index, int root_datum);",
)

L(
    0xEA900,
    "interface/ui_widget.c",
    "FUN_000ea900",
    """
/* FUN_000ea900 (0xea900) — readable C lift: join network game from event. */
char FUN_000ea900(void *widget, void *event_data)
{
  void *client;
  void *ev;
  void *state_out;
  int16_t state;
  void *players;
  short local_idx;
  int i;
  char *base;

  (void)widget;
  ev = event_data;
  if (!ev) {
    display_assert((const char *)0x286184, (const char *)0x2859a4, 0x652, 1);
    system_exit(-1);
  }
  client = network_game_client_get();
  if (!client)
    return 1;
  state_out = ev;
  state = network_game_client_get_state(client, &state_out);
  if (state != 2)
    return 1;
  players = (void *)FUN_0012a0a0();
  local_idx = network_game_client_get_local_machine_index();
  if (!players) {
    display_assert((const char *)0x2861a8, (const char *)0x2859a4, 0x65b, 1);
    system_exit(-1);
  }
  if (local_idx != -1) {
    for (i = 0; i < 0x10; i++) {
      base = (char *)players + i * 0x20;
      if (network_player_is_valid(base + 0x226) &&
          (short)*(signed char *)(base + 0x242) == local_idx &&
          (short)*(signed char *)(base + 0x243) ==
              *(short *)((char *)ev + 2))
        return 1;
    }
  }
  if (!network_game_client_add_player(client, *(int16_t *)((char *)ev + 2)))
    network_game_log((const char *)0x28618c);
  return 1;
}
""",
    "char FUN_000ea900(void *widget, void *event_data);",
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
        "rc": proc.returncode,
        "passed": passed,
        "failed": failed,
        "errors": errors,
        "dt": round(time.time() - t0, 2),
        "timeout": timed_out,
        "tail": text[-800:],
    }


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


def commit_push(names: list[str]) -> None:
    merge_remote_ported()
    subprocess.run(
        [
            "git",
            "add",
            "kb.json",
            "src/halo",
            "tools/equivalence/leaf_cache.json",
            "scripts/lift_grokP_solo3.py",
        ],
        cwd=ROOT,
        capture_output=True,
    )
    msg = f"lift(track-a): grokP {', '.join(names[:6])} Unicorn-prove {len(names)}."
    subprocess.run(["git", "commit", "-m", msg], cwd=ROOT, capture_output=True)
    # rebase if needed then push
    subprocess.run(
        ["git", "pull", "--rebase", "pastudan", "track-a-collision-bsp"],
        cwd=ROOT,
        capture_output=True,
    )
    r = subprocess.run(
        ["git", "push", "pastudan", "HEAD:track-a-collision-bsp"],
        cwd=ROOT,
        capture_output=True,
        text=True,
    )
    print(f"pushed rc={r.returncode}: {msg}", flush=True)
    if r.returncode != 0:
        print((r.stderr or r.stdout)[-400:], flush=True)


def main() -> int:
    print("apply lifts...", flush=True)
    results = apply_lifts(sorted(LIFTS.keys()))
    ok_lift = [r for r in results if r.get("ok")]
    print(f"lifted {len(ok_lift)}/{len(results)}", flush=True)
    for r in results:
        if not r.get("ok"):
            print(" lift-fail", r, flush=True)
            return 1

    print("regen decl.h...", flush=True)
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
        print("regen FAIL", (r.stderr or r.stdout)[-400:], flush=True)
        return 1

    for src in sorted({LIFTS[a][0] for a in LIFTS}):
        print("compile", src, flush=True)
        if not docker_compile(src):
            return 1

    lands: list[str] = []
    fails: list[dict] = []
    for addr in sorted(LIFTS.keys()):
        src, name, _body, _decl = LIFTS[addr]
        print(f"\n== prove {hex(addr)} {name} ==", flush=True)
        kb0 = json.loads(KB_PATH.read_text(encoding="utf-8"))
        already = any(
            isinstance(fn, dict)
            and fn.get("addr")
            and int(fn["addr"], 16) == addr
            and fn.get("ported") is True
            for o in kb0.get("objects", [])
            for fn in o.get("functions") or []
        )
        if already:
            print(" already ported:true", flush=True)
            lands.append(name)
            continue
        if not ensure_oracle(addr):
            fails.append({"addr": hex(addr), "name": name, "err": "oracle"})
            continue
        res = run_uni(name, addr)
        print(
            f" {res.get('passed')}/{res.get('failed')}/{res.get('errors')} "
            f"dt={res['dt']} to={res['timeout']}",
            flush=True,
        )
        if not clear_pass(res, SEEDS):
            print(" FAIL", (res.get("tail") or "")[-300:], flush=True)
            fails.append(
                {
                    "addr": hex(addr),
                    "name": name,
                    "passed": res.get("passed"),
                    "failed": res.get("failed"),
                    "errors": res.get("errors"),
                    "timeout": res.get("timeout"),
                }
            )
            continue
        kb = json.loads(KB_PATH.read_text(encoding="utf-8"))
        if not flip_kb(kb, addr):
            fails.append({"addr": hex(addr), "name": name, "err": "flip"})
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
                "phase": "grokP-solo3",
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
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
