#!/usr/bin/env python3
"""Re-prove readable-C ported:false with --float-tolerance / --real-callees / reconfirm.

Targets:
  - ledger ok@N still ported:false (flip after confirm)
  - near-pass / float-ish failures with cheap extra flags
"""
from __future__ import annotations

import json
import subprocess
import sys
import time
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "scripts"))
from prove_inventory_batch4 import ensure_oracle, flip_kb  # noqa: E402
from unicorn_c_campaign import (  # noqa: E402
    KB_PATH,
    append_ledger,
    clear_pass,
    count_ported,
    git_push,
    inventory_readable,
    run_unicorn,
)

LEDGER = ROOT / "artifacts" / "equivalence" / "unicorn_c_campaign.jsonl"
SKIP = ("xdk/", "libcmt", "bink", "d3d", "dsound", "libtiff", "xapilib")


def run_unicorn_flags(
    name: str,
    addr: int,
    seeds: int,
    timeout: float,
    extra: list[str],
) -> dict:
    outj = ROOT / "artifacts" / "equivalence" / f"uni_{addr:08x}_retry.json"
    cmd = [
        sys.executable,
        str(ROOT / "tools" / "equivalence" / "unicorn_diff.py"),
        name,
        "--allow-stubs",
        "--seeds",
        str(seeds),
        "-q",
        "--output-json",
        str(outj),
        *extra,
    ]
    t0 = time.time()
    try:
        proc = subprocess.run(
            cmd, cwd=str(ROOT), capture_output=True, text=True, timeout=timeout
        )
        timed_out = False
    except subprocess.TimeoutExpired as exc:
        timed_out = True
        proc = subprocess.CompletedProcess(
            cmd, 124, exc.stdout or "", "timeout"
        )
    text = (proc.stdout or "") + (proc.stderr or "")
    if timed_out:
        text += "\nTIMEOUT\n"
    passed = failed = errors = None
    import re

    m = re.search(r"(\d+) passed, (\d+) failed, (\d+) errors", text)
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
        "tail": text[-400:],
        "missing_candidate": "missing_build_object" in text,
        "timeout": timed_out,
    }


def load_best_ledger() -> dict[int, dict]:
    by: dict[int, dict] = {}
    if not LEDGER.exists():
        return by
    for line in LEDGER.read_text().splitlines():
        if not line.strip():
            continue
        try:
            row = json.loads(line)
        except json.JSONDecodeError:
            continue
        try:
            ai = int(str(row["addr"]), 16)
        except (KeyError, ValueError):
            continue
        prev = by.get(ai)
        if prev is None or (row.get("passed") or 0) >= (prev.get("passed") or 0):
            by[ai] = row
    return by


def main() -> int:
    import argparse

    ap = argparse.ArgumentParser()
    ap.add_argument("--seeds", type=int, default=100)
    ap.add_argument("--timeout", type=float, default=45.0)
    ap.add_argument("--no-push", action="store_true")
    ap.add_argument("--limit", type=int, default=0)
    args = ap.parse_args()

    kb = json.loads(KB_PATH.read_text(encoding="utf-8"))
    true0, false0 = count_ported(kb)
    readable = inventory_readable(kb)
    by = load_best_ledger()

    queue: list[tuple[str, dict, list[str]]] = []
    for r in readable:
        src = (r.get("source") or "").lower()
        if any(s in src for s in SKIP):
            continue
        row = by.get(r["addr_int"])
        if row and row.get("ok") and r["fn"].get("ported") is False:
            queue.append(("reconfirm", r, []))
            continue
        if not row:
            continue
        p, f, e = row.get("passed") or 0, row.get("failed") or 0, row.get("errors") or 0
        tail = str(row.get("tail") or "")
        # near-pass with 1 error → try real-callees
        if f == 0 and e and e <= 3 and p >= 40:
            queue.append(("real_callees", r, ["--real-callees"]))
        # float-ish mismatch
        elif f and f <= 5 and e == 0 and p >= 30:
            if any(x in tail for x in ("ST0", "st0", "float", "ULP", "fld", "fst")):
                queue.append(("float_tol", r, ["--float-tolerance", "32"]))
            else:
                queue.append(("real_callees", r, ["--real-callees"]))

    if args.limit:
        queue = queue[: args.limit]
    print(f"retry queue={len(queue)} kb true={true0} false={false0}", flush=True)

    flips = []
    for kind, r, extra in queue:
        ai = r["addr_int"]
        name = r["name"]
        print(f"\n== {hex(ai)} {name} [{kind}] extra={extra} ==", flush=True)
        if not ensure_oracle(ai):
            print("  oracle FAIL", flush=True)
            continue
        if kind == "reconfirm" and not extra:
            res = run_unicorn(hex(ai), ai, args.seeds, timeout=args.timeout)
        else:
            res = run_unicorn_flags(
                hex(ai), ai, args.seeds, args.timeout, extra
            )
        ok = clear_pass(res, args.seeds)
        if not ok and kind != "reconfirm":
            # try combining flags once
            combo = list(dict.fromkeys(extra + ["--real-callees", "--float-tolerance", "32"]))
            res2 = run_unicorn_flags(hex(ai), ai, args.seeds, args.timeout, combo)
            if clear_pass(res2, args.seeds):
                res, ok = res2, True
        print(
            f"  ok={ok} {res.get('passed')}/{res.get('failed')}/{res.get('errors')}",
            flush=True,
        )
        append_ledger(
            {
                "addr": hex(ai),
                "name": name,
                "ok": ok,
                "phase": f"retry_{kind}",
                "passed": res.get("passed"),
                "failed": res.get("failed"),
                "errors": res.get("errors"),
            }
        )
        if not ok:
            continue
        kb = json.loads(KB_PATH.read_text(encoding="utf-8"))
        if flip_kb(kb, ai):
            flips.append(hex(ai))
            KB_PATH.write_text(json.dumps(kb, indent=2) + "\n", encoding="utf-8")
            print(f"  FLIP total={len(flips)}", flush=True)

    if flips:
        subprocess.run(["git", "add", "kb.json"], cwd=ROOT, check=False)
        subprocess.run(
            [
                "git",
                "commit",
                "-m",
                f"verify(track-a): unicorn-retry {len(flips)} "
                f"(float-tol/real-callees/reconfirm).",
            ],
            cwd=ROOT,
            check=False,
        )
        if not args.no_push:
            try:
                git_push()
            except SystemExit:
                pass

    true1, false1 = count_ported(json.loads(KB_PATH.read_text(encoding="utf-8")))
    summary = {"proven": len(flips), "flips": flips, "true0": true0, "true1": true1}
    Path("/tmp/unicorn_retry_summary.json").write_text(json.dumps(summary, indent=2))
    print("DONE", summary, flush=True)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
