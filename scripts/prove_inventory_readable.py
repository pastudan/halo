#!/usr/bin/env python3
"""Unicorn-prove readable-C functions whose addresses are in /tmp/next_naked.json."""
from __future__ import annotations

import json
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "scripts"))
from prove_inventory_batch4 import flip_kb, ensure_oracle  # noqa: E402
from unicorn_c_campaign import (  # noqa: E402
    KB_PATH,
    append_ledger,
    clear_pass,
    count_ported,
    git_commit_flips,
    inventory_readable,
    run_unicorn,
)


def main() -> int:
    inv_path = Path("/tmp/next_naked.json")
    inv_addrs = {int(x["addr"], 16) for x in json.loads(inv_path.read_text())}
    kb = json.loads(KB_PATH.read_text(encoding="utf-8"))
    true0, false0 = count_ported(kb)
    readable = inventory_readable(kb)
    queue = [r for r in readable if r["addr_int"] in inv_addrs]
    print(f"inventory-readable queue={len(queue)} kb true={true0} false={false0}", flush=True)

    flips: list[str] = []
    shas: list[str] = []
    tested = 0
    for r in queue:
        ai = r["addr_int"]
        name = r["name"]
        print(f"\n== {hex(ai)} {name} ==", flush=True)
        if not ensure_oracle(ai):
            print("  oracle FAIL", flush=True)
            append_ledger(
                {"addr": hex(ai), "name": name, "ok": False, "phase": "oracle", "lifter": "inv"}
            )
            continue
        res = run_unicorn(name, ai, 100, timeout=35.0)
        ok = clear_pass(res, 100)
        print(
            f"  ok={ok} {res.get('passed')}/{res.get('failed')}/{res.get('errors')} dt={res.get('dt')}",
            flush=True,
        )
        if not ok:
            # retry via addr in case of name collision
            res2 = run_unicorn(hex(ai), ai, 100, timeout=35.0)
            if clear_pass(res2, 100):
                res = res2
                ok = True
                print(
                    f"  retry-addr ok={ok} {res.get('passed')}/{res.get('failed')}/{res.get('errors')}",
                    flush=True,
                )
        append_ledger(
            {
                "addr": hex(ai),
                "name": name,
                "ok": ok,
                "phase": "confirm100",
                "lifter": "inv",
                "passed": res.get("passed"),
                "failed": res.get("failed"),
                "errors": res.get("errors"),
            }
        )
        tested += 1
        if ok:
            kb = json.loads(KB_PATH.read_text(encoding="utf-8"))
            if flip_kb(kb, ai):
                flips.append(hex(ai))
                KB_PATH.write_text(json.dumps(kb, indent=2) + "\n", encoding="utf-8")
        if flips and len(flips) % 10 == 0:
            subprocess.run(
                ["git", "add", "kb.json", "tools/equivalence/leaf_cache.json"],
                cwd=ROOT,
                check=False,
            )
            sha = git_commit_flips(10)
            if sha:
                shas.append(sha)
                print(f"COMMIT {sha}", flush=True)

    rem = len(flips) % 10
    if rem:
        subprocess.run(
            ["git", "add", "kb.json", "tools/equivalence/leaf_cache.json"],
            cwd=ROOT,
            check=False,
        )
        sha = git_commit_flips(rem)
        if sha:
            shas.append(sha)
            print(f"COMMIT {sha}", flush=True)

    true1, false1 = count_ported(json.loads(KB_PATH.read_text(encoding="utf-8")))
    summary = {
        "tested": tested,
        "proven": len(flips),
        "flips": flips,
        "shas": shas,
        "true0": true0,
        "true1": true1,
    }
    Path("/tmp/inv_prove_summary.json").write_text(json.dumps(summary, indent=2))
    print("DONE", summary, flush=True)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
