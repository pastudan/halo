#!/usr/bin/env python3
"""grokP-solo5: actor_perception + hs_runtime exclusive leaves."""
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
    0x32940,
    "ai/actor_perception.c",
    "actor_expected_acknowledgement",
    """
/* actor_expected_acknowledgement (0x32940) — readable C lift. */
char actor_expected_acknowledgement(int actor_handle, int prop_handle)
{
  char *prop;
  char *other;
  int iter;
  char found;
  short state;
  float dx, dy, dz, dot;

  datum_get(*(data_t **)0x6325a4, actor_handle);
  prop = (char *)datum_get(*(data_t **)0x5ab23c, prop_handle);
  found = 0;
  state = *(short *)(prop + 0x24);
  if (state >= 4 && state <= 5) {
    display_assert((const char *)0x256318, (const char *)0x255fb0, 0xe22, 1);
    system_exit(-1);
  }
  FUN_00064540(&iter, actor_handle);
  other = (char *)FUN_00064570(&iter);
  while (other) {
    if (iter != prop_handle) {
      if (*(int *)(other + 0x18) == *(int *)(prop + 0x18) ||
          *(int *)(other + 0x1c) == *(int *)(prop + 0x1c) ||
          (*(unsigned char *)(prop + 0x60) && *(unsigned char *)(other + 0x60) &&
           ((*(short *)(other + 0x24) >= 4 && *(short *)(other + 0x24) <= 5) ||
            (*(short *)(other + 0x24) >= 2 && *(short *)(other + 0x24) <= 3)))) {
        dx = *(float *)(prop + 0xbc) - *(float *)(other + 0xbc);
        dy = *(float *)(prop + 0xc0) - *(float *)(other + 0xc0);
        if (dx * dx + dy * dy < *(float *)0x253dcc) {
          dz = *(float *)(other + 0xc4) - *(float *)(prop + 0xc4);
          if (dz < 0)
            dz = -dz;
          if (dz < *(double *)0x256310) {
            dot = *(float *)(other + 0xe8) * *(float *)(prop + 0xe8) +
                  *(float *)(other + 0xe4) * *(float *)(prop + 0xe4) +
                  *(float *)(other + 0xe0) * *(float *)(prop + 0xe0);
            if (dot > *(float *)0x253398)
              found = 1;
          }
        }
      }
    }
    other = (char *)FUN_00064570(&iter);
  }
  return found;
}
""",
    "char actor_expected_acknowledgement(int actor_handle, int prop_handle);",
)

L(
    0xC8720,
    "hs/hs_runtime.c",
    "FUN_000c8720",
    """
/* FUN_000c8720 (0xc8720) — readable C lift: coerce boolean/script expr types. */
char FUN_000c8720(int16_t function_index, int root_datum)
{
  char *root;
  char *node;
  int child;
  char ok;
  int count;
  const char *fname;
  void *entry;

  root = (char *)datum_get(*(data_t **)0x5aa6c8, root_datum);
  node = (char *)datum_get(*(data_t **)0x5aa6c8, *(int *)(root + 0x10));
  child = *(int *)(node + 8);
  ok = 1;
  if (function_index < 7 || function_index > 0xc) {
    display_assert((const char *)0x27cfe0, (const char *)0x27cdc0, 0x17d, 1);
    system_exit(-1);
  }
  count = 0;
  while (child != -1) {
    node = (char *)datum_get(*(data_t **)0x5aa6c8, child);
    ok = 1;
    if (*(int *)0x46b6fc) {
      display_assert((const char *)0x27cbd4, (const char *)0x27bd0c, 0x48e, 1);
      system_exit(-1);
    }
    if (*(short *)(node + 4) == 0) {
      *(short *)(node + 4) = 6;
      node = (char *)datum_get(*(data_t **)0x5aa6c8, child);
      if ((*(unsigned char *)(node + 6) & 1) != 0) {
        *(short *)(node + 2) = 6;
        ok = (char)FUN_000c73a0(child);
      } else {
        ok = (char)FUN_000c74c0(child);
      }
    }
    node = (char *)datum_get(*(data_t **)0x5aa6c8, child);
    child = *(int *)(node + 8);
    count++;
    if (!ok)
      break;
  }
  if (ok) {
    if (count < 2)
      goto fail_msg;
    if (function_index == 0xa && count > 2)
      goto fail_msg;
    return ok;
  }
fail_msg:
  if (function_index == 0xa)
    fname = (const char *)0x25386f;
  else
    fname = (const char *)0x27cfd0;
  entry = hs_function_table_get(function_index);
  crt_sprintf((char *)0x46b704, (const char *)0x27cfac,
              *(const char **)((char *)entry + 4), fname);
  *(int *)0x46b6fc = 0x46b704;
  node = (char *)datum_get(*(data_t **)0x5aa6c8, root_datum);
  *(int *)0x46b700 = *(int *)(node + 0xc);
  return 0;
}
""",
    "char FUN_000c8720(int16_t function_index, int root_datum);",
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
            "scripts/lift_grokP_solo5.py",
        ],
        cwd=ROOT,
        capture_output=True,
    )
    msg = f"lift(track-a): grokP {', '.join(names[:6])} Unicorn-prove {len(names)}."
    subprocess.run(["git", "commit", "-m", msg], cwd=ROOT, capture_output=True)
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
    results = apply_lifts(sorted(LIFTS.keys()))
    print(f"lifted {sum(1 for r in results if r.get('ok'))}/{len(results)}", flush=True)
    for r in results:
        if not r.get("ok"):
            print(" lift-fail", r, flush=True)
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
    for src in sorted({LIFTS[a][0] for a in LIFTS}):
        print("compile", src, flush=True)
        if not docker_compile(src):
            return 1

    lands: list[str] = []
    fails: list[dict] = []
    for addr in sorted(LIFTS.keys()):
        src, name, _b, _d = LIFTS[addr]
        print(f"\n== prove {hex(addr)} {name} ==", flush=True)
        kb0 = json.loads(KB_PATH.read_text(encoding="utf-8"))
        if any(
            isinstance(fn, dict)
            and fn.get("addr")
            and int(fn["addr"], 16) == addr
            and fn.get("ported") is True
            for o in kb0.get("objects", [])
            for fn in o.get("functions") or []
        ):
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
            fails.append({"addr": hex(addr), "name": name, **{k: res.get(k) for k in ("passed", "failed", "errors", "timeout")}})
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
                "phase": "grokP-solo5",
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
