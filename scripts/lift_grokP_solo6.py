#!/usr/bin/env python3
"""grokP-solo6: FUN_000c89c0 hs type-check (non-hanger)."""
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
    0xC89C0,
    "hs/hs_runtime.c",
    "FUN_000c89c0",
    """
/* FUN_000c89c0 (0xc89c0) — readable C lift: hs type-check compare/ops. */
char FUN_000c89c0(int16_t function_index, int root_datum)
{
  char ok;
  int out_handles[2];
  void *entry;
  const char *name;
  int left;
  int right;
  short t;
  char matched;

  ok = 0;
  if (function_index < 0xf || function_index > 0x12) {
    display_assert((const char *)0x27d078, (const char *)0x27cdc0, 0x1e3, 1);
    system_exit(-1);
  }
  entry = hs_function_table_get(function_index);
  name = *(const char **)((char *)entry + 4);
  if (!FUN_000c55d0(name, out_handles, 2, root_datum))
    return 0;
  left = out_handles[0];
  right = out_handles[1];
  matched = 0;
  if (hs_type_check(left, 0)) {
    t = *(short *)((char *)datum_get(*(data_t **)0x5aa6c8, left) + 4);
    if ((t >= 0x20 && t <= 0x24) || (t >= 6 && t <= 8)) {
      if (hs_type_check(right, t))
        ok = 1;
      matched = 1;
    }
  }
  if (!matched && !*(int *)0x46b6fc) {
    matched = 0;
    if (hs_type_check(right, 0)) {
      t = *(short *)((char *)datum_get(*(data_t **)0x5aa6c8, right) + 4);
      if ((t >= 0x20 && t <= 0x24) || (t >= 6 && t <= 8)) {
        if (hs_type_check(left, t))
          ok = 1;
        matched = 1;
      }
    }
    if (!matched && !*(int *)0x46b6fc) {
      if (hs_type_check(left, 6) && hs_type_check(right, 6))
        ok = 1;
    }
  }
  return ok;
}
""",
    "char FUN_000c89c0(int16_t function_index, int root_datum);",
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
        "tail": text[-800:],
    }


def main() -> int:
    # remove bogus helper from module namespace pollution — LIFTS only
    results = apply_lifts([0xC89C0])
    print(f"lifted {results}", flush=True)
    if not results or not results[0].get("ok"):
        return 1
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
    if not docker_compile("hs/hs_runtime.c"):
        return 1
    name = "FUN_000c89c0"
    addr = 0xC89C0
    print(f"== prove {name} ==", flush=True)
    if not ensure_oracle(addr):
        print("oracle FAIL", flush=True)
        return 1
    res = run_uni(name, addr)
    print(res.get("passed"), res.get("failed"), res.get("errors"), res.get("dt"), flush=True)
    if not clear_pass(res, SEEDS):
        print("FAIL", res.get("tail", "")[-400:], flush=True)
        return 1
    kb = json.loads(KB_PATH.read_text(encoding="utf-8"))
    flip_kb(kb, addr)
    KB_PATH.write_text(json.dumps(kb, indent=2) + "\n", encoding="utf-8")
    append_ledger(
        {
            "addr": hex(addr),
            "name": name,
            "source": "hs/hs_runtime.c",
            "ok": True,
            "passed": 100,
            "failed": 0,
            "errors": 0,
            "seeds": 100,
            "phase": "grokP-solo6",
        }
    )
    subprocess.run(
        ["git", "fetch", "pastudan", "track-a-collision-bsp"], cwd=ROOT, capture_output=True
    )
    r = subprocess.run(
        ["git", "show", "pastudan/track-a-collision-bsp:kb.json"],
        cwd=ROOT,
        capture_output=True,
        text=True,
    )
    if r.returncode == 0 and r.stdout:
        theirs = json.loads(r.stdout)
        ours = json.loads(KB_PATH.read_text(encoding="utf-8"))
        tmap = {
            int(fn["addr"], 16)
            for o in theirs.get("objects", [])
            for fn in o.get("functions") or []
            if isinstance(fn, dict) and fn.get("addr") and fn.get("ported") is True
        }
        for o in ours.get("objects", []):
            for fn in o.get("functions") or []:
                if (
                    isinstance(fn, dict)
                    and fn.get("addr")
                    and int(fn["addr"], 16) in tmap
                    and fn.get("ported") is not True
                ):
                    fn["ported"] = True
        KB_PATH.write_text(json.dumps(ours, indent=2) + "\n", encoding="utf-8")
    subprocess.run(
        [
            "git",
            "add",
            "kb.json",
            "src/halo/hs/hs_runtime.c",
            "tools/equivalence/leaf_cache.json",
            "scripts/lift_grokP_solo6.py",
        ],
        cwd=ROOT,
        capture_output=True,
    )
    subprocess.run(
        ["git", "commit", "-m", "lift(track-a): grokP FUN_000c89c0 Unicorn-prove 1."],
        cwd=ROOT,
        capture_output=True,
    )
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
    print("pushed", pr.returncode, flush=True)
    t, f = count_ported(json.loads(KB_PATH.read_text(encoding="utf-8")))
    print(f"TIP {t}/{t+f}", flush=True)
    return 0 if pr.returncode == 0 else 1


if __name__ == "__main__":
    raise SystemExit(main())
