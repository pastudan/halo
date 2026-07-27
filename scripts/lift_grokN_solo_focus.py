#!/usr/bin/env python3
"""grokN-solo: hand-lift small sound/hs/ui leaves + Unicorn 100/0/0 prove/push."""
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
from lift_inventory_batch4 import L, LIFTS  # noqa: E402
from prove_inventory_batch4 import ensure_oracle, flip_kb  # noqa: E402
from tu_compile import docker_compile  # noqa: E402
from unicorn_c_campaign import (  # noqa: E402
    KB_PATH,
    append_ledger,
    clear_pass,
    count_ported,
)

SEEDS = 100
TIMEOUT = 80.0

# Clear any prior L() registrations from the imported module batch.
LIFTS.clear()

L(
    0xF3690,
    "interface/ui_widget_game_data_input_functions.c",
    "FUN_000f3690",
    """
/* FUN_000f3690 (0xf3690) — readable C lift. */
void FUN_000f3690(int *out_handles /*@<eax>*/, void *widget /*@<ecx>*/)
{
  void *child;
  int idx;
  unsigned int count;
  int sentinel;

  child = *(void **)((char *)widget + 0x34);
  if (*(void **)((char *)widget + 0x38) == child) {
    idx = *(short *)((char *)widget + 0x3c);
    out_handles[0] = idx;
    idx++;
    out_handles[1] = idx;
    count = *(unsigned short *)((char *)widget + 0x44);
    if ((unsigned int)idx == count)
      out_handles[1] = 0;
    idx = out_handles[1] + 1;
    out_handles[2] = idx;
    count = *(unsigned short *)((char *)widget + 0x44);
    if ((unsigned int)idx == count)
      out_handles[2] = 0;
  } else if (*(void **)((char *)widget + 0x38) ==
             *(void **)((char *)child + 0x2c)) {
    idx = *(short *)((char *)widget + 0x3c);
    out_handles[1] = idx;
    idx--;
    out_handles[0] = idx;
    if (idx < 0)
      out_handles[0] = *(unsigned short *)((char *)widget + 0x44) - 1;
    idx = out_handles[1] + 1;
    out_handles[2] = idx;
    count = *(unsigned short *)((char *)widget + 0x44);
    if ((unsigned int)idx == count)
      out_handles[2] = 0;
  } else {
    idx = *(short *)((char *)widget + 0x3c);
    out_handles[2] = idx;
    idx--;
    out_handles[1] = idx;
    if (idx < 0)
      out_handles[1] = *(unsigned short *)((char *)widget + 0x44) - 1;
    idx = out_handles[1] - 1;
    out_handles[0] = idx;
    if (idx < 0)
      out_handles[0] = *(unsigned short *)((char *)widget + 0x44) - 1;
  }

  sentinel = -1;
  count = *(unsigned short *)((char *)widget + 0x44);
  if ((unsigned int)out_handles[0] >= count)
    out_handles[0] = sentinel;
  if ((unsigned int)out_handles[1] >= count)
    out_handles[1] = sentinel;
  if ((unsigned int)out_handles[2] >= count)
    out_handles[2] = sentinel;
}
""",
    "void FUN_000f3690(int *out_handles /*@<eax>*/, void *widget /*@<ecx>*/);",
)

L(
    0xC8B90,
    "hs/hs_runtime.c",
    "FUN_000c8b90",
    """
/* FUN_000c8b90 (0xc8b90) — readable C lift. */
char FUN_000c8b90(int16_t node_type, int datum_index)
{
  char *node;
  char *parent;
  int child;
  int next;
  char result;

  result = 0;
  node = (char *)datum_get(*(data_t **)0x5aa6c8, datum_index);
  parent = (char *)datum_get(*(data_t **)0x5aa6c8, *(int *)(node + 0x10));
  child = *(int *)(parent + 8);
  if (node_type != 0x13) {
    display_assert((const char *)0x27d0fc, (const char *)0x27cdc0, 0x20e, 1);
    system_exit(-1);
  }
  if (child == -1) {
    *(int *)0x46b6fc = 0x27d0bc;
    node = (char *)datum_get(*(data_t **)0x5aa6c8, datum_index);
    *(int *)0x46b700 = *(int *)(node + 0xc);
    return result;
  }
  if (!hs_type_check(child, 7))
    return result;
  next = *(int *)((char *)datum_get(*(data_t **)0x5aa6c8, child) + 8);
  if (next == -1)
    return 1;
  if (!hs_type_check(next, 0xa))
    return result;
  return 1;
}
""",
    "char FUN_000c8b90(int16_t node_type, int datum_index);",
)

L(
    0xC8C50,
    "hs/hs_runtime.c",
    "FUN_000c8c50",
    """
/* FUN_000c8c50 (0xc8c50) — readable C lift. */
char FUN_000c8c50(int16_t function_index, int root_datum)
{
  char *node;
  char *parent;
  int a;
  int b;
  int c;
  char result;

  result = 0;
  if (function_index != 0x14) {
    display_assert((const char *)0x27d168, (const char *)0x27cdc0, 0x235, 1);
    system_exit(-1);
  }
  node = (char *)datum_get(*(data_t **)0x5aa6c8, root_datum);
  parent = (char *)datum_get(*(data_t **)0x5aa6c8, *(int *)(node + 0x10));
  a = *(int *)(parent + 8);
  if (a == -1) {
    *(int *)0x46b6fc = 0x27d120;
    node = (char *)datum_get(*(data_t **)0x5aa6c8, root_datum);
    *(int *)0x46b700 = *(int *)(node + 0xc);
    return result;
  }
  b = *(int *)((char *)datum_get(*(data_t **)0x5aa6c8, a) + 8);
  if (!hs_type_check(a, 5))
    return result;
  if (b == -1)
    return result;
  c = *(int *)((char *)datum_get(*(data_t **)0x5aa6c8, b) + 8);
  if (!hs_type_check(b, 7))
    return result;
  if (c == -1)
    return result;
  return (char)hs_type_check(c, 8);
}
""",
    "char FUN_000c8c50(int16_t function_index, int root_datum);",
)

L(
    0xC8E00,
    "hs/hs_runtime.c",
    "FUN_000c8e00",
    """
/* FUN_000c8e00 (0xc8e00) — readable C lift. */
char FUN_000c8e00(int16_t function_index, int root_datum)
{
  char result;
  void *entry;
  const char *name;
  char *node;

  datum_get(*(data_t **)0x5aa6c8, root_datum);
  result = 0;
  if (function_index != 0x16) {
    display_assert((const char *)0x27d228, (const char *)0x27cdc0, 0x27f, 1);
    system_exit(-1);
  }
  entry = hs_function_table_get(function_index);
  name = *(const char **)((char *)entry + 4);
  if (!FUN_000c55d0(name, (int *)&function_index, 1, root_datum))
    return result;
  node = (char *)datum_get(*(data_t **)0x5aa6c8, function_index);
  if (hs_type_check(function_index, 0))
    return 1;
  if (*(int *)0x46b6fc)
    return result;
  *(int *)0x46b6fc = 0x27d1e0;
  *(int *)0x46b700 = *(int *)(node + 0xc);
  return result;
}
""",
    "char FUN_000c8e00(int16_t function_index, int root_datum);",
)

L(
    0xC8D30,
    "hs/hs_runtime.c",
    "FUN_000c8d30",
    """
/* FUN_000c8d30 (0xc8d30) — readable C lift. */
char FUN_000c8d30(int16_t function_index, int root_datum)
{
  char result;
  void *entry;
  const char *name;
  char *node;
  void *elem;
  short t;

  result = 0;
  if (function_index != 0x15) {
    display_assert((const char *)0x27d1bc, (const char *)0x27cdc0, 0x25d, 1);
    system_exit(-1);
  }
  entry = hs_function_table_get(function_index);
  name = *(const char **)((char *)entry + 4);
  if (!FUN_000c55d0(name, (int *)&function_index, 1, root_datum))
    return result;
  node = (char *)datum_get(*(data_t **)0x5aa6c8, function_index);
  if (!hs_type_check(function_index, 0xa))
    return result;
  elem = tag_block_get_element(
      (char *)global_scenario_get() + 0x49c,
      (int)*(short *)(node + 0x10),
      0x5c);
  t = *(short *)((char *)elem + 0x20);
  if (t == 3 || t == 4) {
    *(int *)0x46b6fc = 0x27d194;
    *(int *)0x46b700 = *(int *)(node + 0xc);
    return result;
  }
  return 1;
}
""",
    "char FUN_000c8d30(int16_t function_index, int root_datum);",
)


def run_uni(name: str, addr: int) -> dict:
    outj = ROOT / "artifacts" / "equivalence" / f"uni_{addr:08x}_s{SEEDS}.json"
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
    except subprocess.TimeoutExpired:
        proc = subprocess.CompletedProcess(cmd, 124, "", "timeout")
        timed_out = True
    text = (proc.stdout or "") + (proc.stderr or "")
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
        "tail": text[-400:],
        "missing_candidate": "missing_build_object" in text
        or "cannot find build .obj" in text,
        "rc": proc.returncode,
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


def commit_push(names: list[str]) -> None:
    merge_remote()
    subprocess.run(
        [
            "git",
            "add",
            "kb.json",
            "tools/equivalence/leaf_cache.json",
            "src/halo/hs/hs_runtime.c",
            "src/halo/interface/ui_widget_game_data_input_functions.c",
            "scripts/lift_grokN_solo_focus.py",
        ],
        cwd=ROOT,
        check=False,
    )
    sample = ", ".join(names[:4])
    if len(names) > 4:
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
    ok_lift = [r for r in results if r.get("ok")]
    print(f"lifted {len(ok_lift)}/{len(results)}", flush=True)
    for r in results:
        if not r.get("ok"):
            print(" lift-fail", r, flush=True)

    # regen decl for register-arg f3690
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

    tus = sorted({LIFTS[a][0] for a in LIFTS})
    for src in tus:
        print("compile", src, flush=True)
        if not docker_compile(src):
            print("COMPILE FAIL", src, flush=True)
            return 1

    lands: list[str] = []
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
            continue
        res = run_uni(name, addr)
        print(
            f" {res.get('passed')}/{res.get('failed')}/{res.get('errors')} "
            f"dt={res['dt']} to={res['timeout']}",
            flush=True,
        )
        if not clear_pass(res, SEEDS):
            print(" FAIL", res.get("tail", "")[-240:], flush=True)
            continue
        kb = json.loads(KB_PATH.read_text(encoding="utf-8"))
        if not flip_kb(kb, addr):
            print(" flip miss", flush=True)
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
                "phase": "grokN-solo-focus",
            }
        )
        lands.append(name)
        print(" FLIP", name, flush=True)

    t, f = count_ported(json.loads(KB_PATH.read_text(encoding="utf-8")))
    print(f"\nLANDS ({len(lands)}): {lands}", flush=True)
    print(f"TIP {t}/{t+f} ({100*t/(t+f):.2f}%)", flush=True)
    if lands:
        commit_push(lands)
    return 0 if len(lands) >= 1 else 1


if __name__ == "__main__":
    raise SystemExit(main())
