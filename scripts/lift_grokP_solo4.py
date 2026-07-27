#!/usr/bin/env python3
"""grokP-solo4: more exclusive hs + dynavobgeom leaves."""
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
    0xC8F40,
    "hs/hs_runtime.c",
    "FUN_000c8f40",
    """
/* FUN_000c8f40 (0xc8f40) — readable C lift: coerce script expr list types. */
char FUN_000c8f40(int16_t function_index, int root_datum)
{
  char *root;
  char *node;
  int child;
  char ok;

  root = (char *)datum_get(*(data_t **)0x5aa6c8, root_datum);
  node = (char *)datum_get(*(data_t **)0x5aa6c8, *(int *)(root + 0x10));
  child = *(int *)(node + 8);
  ok = 1;
  if (function_index < 0x18 || function_index > 0x1a) {
    display_assert((const char *)0x27d2b0, (const char *)0x27cdc0, 0x2ae, 1);
    system_exit(-1);
  }
  while (child != -1) {
    node = (char *)datum_get(*(data_t **)0x5aa6c8, child);
    ok = 1;
    if (*(int *)0x46b6fc) {
      display_assert((const char *)0x27cbd4, (const char *)0x27bd0c, 0x48e, 1);
      system_exit(-1);
    }
    if (*(short *)(node + 4) == 0) {
      *(short *)(node + 4) = 9;
      node = (char *)datum_get(*(data_t **)0x5aa6c8, child);
      if ((*(unsigned char *)(node + 6) & 1) != 0) {
        *(short *)(node + 2) = 9;
        ok = (char)FUN_000c73a0(child);
      } else {
        ok = (char)FUN_000c74c0(child);
      }
    }
    node = (char *)datum_get(*(data_t **)0x5aa6c8, child);
    child = *(int *)(node + 8);
    if (!ok)
      break;
  }
  return ok;
}
""",
    "char FUN_000c8f40(int16_t function_index, int root_datum);",
)

L(
    0x168CD0,
    "rasterizer/xbox/rasterizer_xbox_dynavobgeom.c",
    "FUN_00168cd0",
    """
/* FUN_00168cd0 (0x168cd0) — readable C lift: create dynamic vertex buffer. */
unsigned char FUN_00168cd0(void *obj, short type, int count, void *src, int nbytes)
{
  short stride;
  unsigned char ok;
  int hr;
  void *vb;
  void *locked;

  stride = (short)FUN_00180050(type);
  if (!obj) {
    display_assert((const char *)0x2a19cc, (const char *)0x2a2b58, 0x18, 1);
    system_exit(-1);
  }
  if ((int)stride * count != nbytes && src) {
    display_assert((const char *)0x2a2b2c, (const char *)0x2a2b58, 0x19, 1);
    system_exit(-1);
  }
  ok = 1;
  if (count == 0)
    ok = 0;
  if (!*(int *)0x476ab0) {
    ok = 0;
  } else if (ok) {
    vb = 0;
    hr = D3DDevice_CreateVertexBuffer((unsigned)nbytes, 8, 0, 1, &vb);
    if (hr < 0) {
      ok = 0;
      FUN_00167ff0(hr, (const char *)0x2a2a90);
    } else {
      ok = 1;
    }
    if (!vb) {
      ok = 0;
      vb = 0;
    } else if (!ok) {
      vb = 0;
    }
    if (src) {
      if (!ok)
        goto fail;
      locked = 0;
      *(short *)0x325652 = 2;
      D3DVertexBuffer_Lock((int)vb, 0, nbytes, (int)&locked, 0);
      *(short *)0x325652 = 0;
      if (!locked) {
        ok = 0;
        locked = 0;
        goto fail;
      }
      csmemcpy(locked, src, (unsigned)nbytes);
      *(short *)obj = type;
      *(int *)((char *)obj + 4) = count;
      *(int *)((char *)obj + 8) = 0;
      *(void **)((char *)obj + 0xc) = src;
      *(void **)((char *)obj + 0x10) = vb;
      return 1;
    }
    if (ok)
      return ok;
  fail:
    csmemset(obj, 0, 0x14);
    error(2, (const char *)0x2a2a54);
  }
  return ok;
}
""",
    "unsigned char FUN_00168cd0(void *obj, short type, int count, void *src, int nbytes);",
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
            "scripts/lift_grokP_solo4.py",
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
    print("apply lifts...", flush=True)
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
            print(" already", flush=True)
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
                "phase": "grokP-solo4",
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
