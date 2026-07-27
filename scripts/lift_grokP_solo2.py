#!/usr/bin/env python3
"""grokP-solo2: exclusive remaining rasterizer/dynavobgeom + hs non-hangers +
actor_perception small/medium + ui_widget non list-walk → Unicorn 100/0/0.

Avoids O-solo commons (actor_get_vision_distances 0x2f470) and ui list_prev/next.
"""
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
TIMEOUT = 120.0

# --- hs_runtime non-hangers (already-C bodies re-applied for kb decl sync) ---

L(
    0xC95F0,
    "hs/hs_runtime.c",
    "FUN_000c95f0",
    """
/* FUN_000c95f0 (0xc95f0) — readable C lift: collect object list from players. */
int FUN_000c95f0(void)
{
  int list_handle;
  int player;
  char *node;
  int obj;

  list_handle = FUN_000ce200();
  player = data_next_index(*(data_t **)0x5aa6d4, -1);
  while (player != -1) {
    node = (char *)datum_get(*(data_t **)0x5aa6d4, player);
    obj = *(int *)(node + 0x34);
    if (obj != -1)
      FUN_000ce2b0(list_handle, obj);
    player = data_next_index(*(data_t **)0x5aa6d4, player);
  }
  return list_handle;
}
""",
    "int FUN_000c95f0(void);",
)

L(
    0xCE3C0,
    "hs/hs_runtime.c",
    "FUN_000ce3c0",
    """
/* FUN_000ce3c0 (0xce3c0) — readable C lift. */
void FUN_000ce3c0(void)
{
  int index;
  short *datum;

  for (index = data_next_index(*(data_t **)0x5aa698, -1); index != -1;
       index = data_next_index(*(data_t **)0x5aa698, index)) {
    datum = (short *)datum_get(*(void **)0x5aa698, index);
    if (datum[2] == 0)
      object_list_delete(index);
  }
}
""",
    "void FUN_000ce3c0(void);",
)

L(
    0xC9650,
    "hs/hs_runtime.c",
    "FUN_000c9650",
    """
/* FUN_000c9650 (0xc9650) — readable C lift: set/clear game-flag bit from list. */
char FUN_000c9650(int16_t game_flag, int list_handle, char set_flag)
{
  int iter;
  int obj;
  char flag;
  int idx;
  unsigned int *word;
  unsigned int bit;

  flag = set_flag;
  obj = FUN_000ce450(list_handle, &iter);
  while (obj != -1) {
    if (FUN_0018ef00((int)game_flag, obj)) {
      if (!flag) {
        flag = 1;
        goto set_bit;
      }
    } else if (flag) {
      flag = 0;
      goto clear_bit;
    }
    obj = FUN_000ce320(list_handle, &iter);
  }
  if (!flag)
    goto clear_bit;

set_bit:
  idx = (int)game_flag;
  word = (unsigned int *)(0x5aa6a0 + ((idx >> 5) * 4));
  bit = 1u << (idx & 0x1f);
  *word |= bit;
  return flag;

clear_bit:
  idx = (int)game_flag;
  word = (unsigned int *)(0x5aa6a0 + ((idx >> 5) * 4));
  bit = 1u << (idx & 0x1f);
  *word &= ~bit;
  return flag;
}
""",
    "char FUN_000c9650(int16_t game_flag, int list_handle, char set_flag);",
)

L(
    0xC9770,
    "hs/hs_runtime.c",
    "FUN_000c9770",
    """
/* FUN_000c9770 (0xc9770) — readable C lift: any list unit facing param. */
char FUN_000c9770(int list_handle, int param, float distance)
{
  int iter;
  int obj;

  obj = FUN_000ce450(list_handle, &iter);
  while (obj != -1) {
    if (object_try_and_get_and_verify_type(obj, 3) &&
        FUN_000c9700(obj, param, distance))
      return 1;
    obj = FUN_000ce320(list_handle, &iter);
  }
  return 0;
}
""",
    "char FUN_000c9770(int list_handle, int param, float distance);",
)

L(
    0xC9840,
    "hs/hs_runtime.c",
    "FUN_000c9840",
    """
/* FUN_000c9840 (0xc9840) — readable C lift: any list unit near cutscene flag. */
char FUN_000c9840(int list_handle, int16_t scenario_index, float distance)
{
  int iter;
  int obj;
  void *elem;

  obj = FUN_000ce450(list_handle, &iter);
  while (obj != -1) {
    if (object_try_and_get_and_verify_type(obj, 3) && scenario_index != 0) {
      elem = tag_block_get_element(
          (char *)global_scenario_get() + 0x4e4, (int)scenario_index, 0x5c);
      if (FUN_001aa430(obj, (float *)((char *)elem + 0x24),
                       distance * *(float *)0x253d4c))
        return 1;
    }
    obj = FUN_000ce320(list_handle, &iter);
  }
  return 0;
}
""",
    "char FUN_000c9840(int list_handle, int16_t scenario_index, float distance);",
)

L(
    0xCA430,
    "hs/hs_runtime.c",
    "FUN_000ca430",
    """
/* FUN_000ca430 (0xca430) — readable C lift: teleport players failing cluster. */
void FUN_000ca430(int16_t game_flag, int16_t scenario_index)
{
  int player;
  char *node;
  int unit;

  for (player = data_next_index(*(data_t **)0x5aa6d4, -1); player != -1;
       player = data_next_index(*(data_t **)0x5aa6d4, player)) {
    node = (char *)datum_get(*(data_t **)0x5aa6d4, player);
    unit = *(int *)(node + 0x34);
    if (unit != -1 && !FUN_0018ef00((int)game_flag, unit))
      FUN_000ca160(scenario_index, 1, 1, unit);
  }
}
""",
    "void FUN_000ca430(int16_t game_flag, int16_t scenario_index);",
)

# --- dynavobgeom render-state setup (like proven 0x160c30) ---

L(
    0x162790,
    "rasterizer/xbox/rasterizer_xbox_dynavobgeom.c",
    "FUN_00162790",
    """
/* FUN_00162790 (0x162790) — readable C lift. */
void FUN_00162790(void)
{
  short mode;
  unsigned int color;
  unsigned int blend;
  unsigned int zwrite;

  if (!*(int *)0x476ab0) {
    display_assert((const char *)0x29dc40, (const char *)0x2a18c0, 0x399, 1);
    system_exit(-1);
  }
  FUN_0016f910(8);
  mode = *(short *)0x3256bc;
  if (mode != 0 && mode != 1 && mode != 3 && mode != 4 && mode != 7 &&
      mode != 5 && mode != 8)
    return;
  if (!*(unsigned char *)0x3256cc)
    return;

  D3DDevice_SetRenderState_CullMode(0x901);
  color = 0x10101;
  if (*(unsigned char *)0x3256f5)
    color += 0x1000000;
  D3DDevice_SetRenderState_Simple(0x40358, color);
  *(unsigned int *)0x1fb7a4 = color;
  D3DDevice_SetRenderState_Simple(0x40304, 1);
  *(unsigned int *)0x1fb784 = 1;
  blend = (mode == 1) ? 1u : 0x306u;
  D3DDevice_SetRenderState_Simple(0x40344, blend);
  *(unsigned int *)0x1fb790 = blend;
  zwrite = (mode == 1) ? 1u : 0u;
  D3DDevice_SetRenderState_Simple(0x40348, zwrite);
  *(unsigned int *)0x1fb794 = zwrite;
  D3DDevice_SetRenderState_Simple(0x40350, 0x8006);
  *(unsigned int *)0x1fb7c0 = 0x8006;
  D3DDevice_SetRenderState_Simple(0x40300, 0);
  *(unsigned int *)0x1fb788 = 0;
  D3DDevice_SetRenderState_ZEnable(mode != 1);
  D3DDevice_SetRenderState_Simple(0x40354, 0x202);
  *(unsigned int *)0x1fb77c = 0x202;
  D3DDevice_SetRenderState_Simple(0x4035c, 0);
  *(unsigned int *)0x1fb798 = 0;
  D3DDevice_SetRenderState_ZBias(0);
  FUN_00158ae0(5);
}
""",
    "void FUN_00162790(void);",
)

L(
    0x1643E0,
    "rasterizer/xbox/rasterizer_xbox_dynavobgeom.c",
    "FUN_001643e0",
    """
/* FUN_001643e0 (0x1643e0) — readable C lift. */
void FUN_001643e0(void)
{
  if (!*(int *)0x476ab0) {
    display_assert((const char *)0x29dc40, (const char *)0x2a18c0, 0x815, 1);
    system_exit(-1);
  }
  FUN_0016f910(0xd);
  if (*(short *)0x3256bc != 0)
    return;
  if (!*(unsigned char *)0x3256d0)
    return;
  if (!*(unsigned char *)0x3256d2)
    return;
  if (*(short *)0x3256b0 != 0)
    return;

  D3DDevice_SetRenderState_CullMode(0x901);
  D3DDevice_SetRenderState_Simple(0x40358, 0x1000000);
  *(unsigned int *)0x1fb7a4 = 0x1000000;
  D3DDevice_SetRenderState_Simple(0x40304, 1);
  *(unsigned int *)0x1fb784 = 1;
  D3DDevice_SetRenderState_Simple(0x40344, 0x304);
  *(unsigned int *)0x1fb790 = 0x304;
  D3DDevice_SetRenderState_Simple(0x40348, 0);
  *(unsigned int *)0x1fb794 = 0;
  D3DDevice_SetRenderState_Simple(0x40350, 0x8006);
  *(unsigned int *)0x1fb7c0 = 0x8006;
  D3DDevice_SetRenderState_Simple(0x40300, 0);
  *(unsigned int *)0x1fb788 = 0;
  D3DDevice_SetRenderState_ZEnable(1);
  D3DDevice_SetRenderState_Simple(0x40354, 0x202);
  *(unsigned int *)0x1fb77c = 0x202;
  D3DDevice_SetRenderState_Simple(0x4035c, 0);
  *(unsigned int *)0x1fb798 = 0;
  D3DDevice_SetRenderState_ZBias(0);

  csmemset((void *)0x5a5ac0, 0, 0xf0);
  *(int *)0x5a5b98 = 1;
  *(int *)0x5a5b94 = 2;
  *(int *)0x5a5ae8 = 0x80b050;
  *(int *)0x5a5b48 = 0x8010000;
  *(int *)0x5a5b74 = 0x20c0;
  *(int *)0x5a5ac4 = 0x2c120c20;
  *(int *)0x5a5b2c = 0xc00;
  *(int *)0x5a5ae0 = 0;
  *(int *)0x5a5ae4 = 0x1c00;
  rasterizer_set_pixel_shader((void *)0x5a5ac0);
}
""",
    "void FUN_001643e0(void);",
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
            cmd,
            cwd=str(ROOT),
            capture_output=True,
            text=True,
            timeout=TIMEOUT,
            env=env,
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
        "tail": text[-600:],
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
        ["git", "add", "kb.json", "src/halo", "tools/equivalence/leaf_cache.json",
         "scripts/lift_grokP_solo2.py"],
        cwd=ROOT,
        capture_output=True,
    )
    msg = f"lift(track-a): grokP {', '.join(names[:6])} Unicorn-prove {len(names)}."
    subprocess.run(["git", "commit", "-m", msg], cwd=ROOT, capture_output=True)
    subprocess.run(
        ["git", "push", "pastudan", "HEAD:track-a-collision-bsp"],
        cwd=ROOT,
        capture_output=True,
    )
    print(f"pushed: {msg}", flush=True)


def main() -> int:
    print("apply lifts...", flush=True)
    results = apply_lifts(sorted(LIFTS.keys()))
    ok_lift = [r for r in results if r.get("ok")]
    print(f"lifted {len(ok_lift)}/{len(results)}", flush=True)
    for r in results:
        if not r.get("ok"):
            print(" lift-fail", r, flush=True)

    print("regen decl.h (local knowledge.py)...", flush=True)
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

    tus = sorted({LIFTS[a][0] for a in LIFTS})
    for src in tus:
        print("compile", src, flush=True)
        if not docker_compile(src):
            print("COMPILE FAIL", src, flush=True)
            return 1

    lands: list[str] = []
    fails: list[dict] = []
    for addr in sorted(LIFTS.keys()):
        src, name, _body, _decl = LIFTS[addr]
        print(f"\n== prove {hex(addr)} {name} ==", flush=True)
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
        if not ensure_oracle(addr):
            print(" oracle FAIL", flush=True)
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
            print(" flip miss", flush=True)
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
                "phase": "grokP-solo2",
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
