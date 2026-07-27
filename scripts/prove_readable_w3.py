#!/usr/bin/env python3
"""Unicorn-prove already-readable ported:false leaves in compiling TUs."""
from __future__ import annotations

import json
import os
import re
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "scripts"))

from prove_inventory_batch4 import ensure_oracle, flip_kb  # noqa: E402
from tu_compile import docker_compile  # noqa: E402
from unicorn_c_campaign import (  # noqa: E402
    KB_PATH,
    append_ledger,
    clear_pass,
    count_ported,
    inventory_readable,
)

OK = {
    "networking/network_messages",
    "objects/objects",
    "objects/damage",
    "main/main",
    "items/items",
    "items/projectiles",
    "units/units",
    "game/cheats",
    "networking/message_header",
    "networking/network_client_manager",
    "hs/hs",
    "physics/point_physics",
    "interface/progress_bar",
    "ai/ai_debug",
}


def run_uni(name: str, addr: int, seeds: int = 100, timeout: float = 45.0) -> dict:
    outj = ROOT / "artifacts" / "equivalence" / f"uni_{addr:08x}_s{seeds}.json"
    cmd = [
        sys.executable,
        str(ROOT / "tools/equivalence/unicorn_diff.py"),
        name,
        "--allow-stubs",
        "--no-stub-arg-trace",
        "--seeds",
        str(seeds),
        "-q",
        "--output-json",
        str(outj),
    ]
    env = os.environ.copy()
    env.setdefault("BIPED_SIBLING_RESOLVE", "1")
    try:
        proc = subprocess.run(
            cmd, cwd=str(ROOT), capture_output=True, text=True, timeout=timeout, env=env
        )
    except subprocess.TimeoutExpired:
        return {
            "passed": 0,
            "failed": 0,
            "errors": 1,
            "tail": "TIMEOUT",
            "missing_candidate": False,
        }
    text = (proc.stdout or "") + (proc.stderr or "")
    m = re.search(r"(\d+) passed, (\d+) failed, (\d+) errors", text)
    p = f = e = None
    if m:
        p, f, e = map(int, m.groups())
    return {
        "passed": p,
        "failed": f,
        "errors": e,
        "tail": text[-300:],
        "missing_candidate": "missing_build" in text,
    }


def main() -> int:
    priority = [
        (0x11B950, "hashtable_set_user_data", "networking/network_messages.c"),
        (0x11C1D0, "FUN_0011c1d0", "networking/network_messages.c"),
        (0x11C1E0, "FUN_0011c1e0", "networking/network_messages.c"),
        (0x13DCB0, "FUN_0013dcb0", "objects/objects.c"),
        (0x138F10, "FUN_00138f10", "objects/damage.c"),
        (0xFFEB0, "FUN_000ffeb0", "main/main.c"),
    ]
    kb = json.loads(KB_PATH.read_text(encoding="utf-8"))
    readable = inventory_readable(kb)
    seen = {a for a, _, _ in priority}
    extras = []
    for r in readable:
        src = r["source"].replace("\\", "/")
        if not any(o in src for o in OK):
            continue
        if r["addr_int"] in seen:
            continue
        rel = src.split("src/halo/")[-1] if "src/halo/" in src else src
        extras.append((r["addr_int"], r["name"], rel))
    queue = priority + extras[:50]

    tus = sorted({t[2].replace("src/halo/", "") for t in queue})
    bad = set()
    for tu in tus:
        if not docker_compile(tu):
            print("BAD", tu, flush=True)
            bad.add(tu)
        else:
            print("OK", tu, flush=True)
    queue = [q for q in queue if q[2].replace("src/halo/", "") not in bad]

    true0, _ = count_ported(json.loads(KB_PATH.read_text(encoding="utf-8")))
    flips = []
    for addr, name, src in queue:
        print(f"\n== {hex(addr)} {name} ==", flush=True)
        if not ensure_oracle(addr):
            print("  oracle fail", flush=True)
            continue
        res = run_uni(hex(addr), addr)
        if not clear_pass(res, 100):
            res2 = run_uni(name, addr)
            if clear_pass(res2, 100) or (res2.get("passed") or 0) > (res.get("passed") or 0):
                res = res2
        ok = clear_pass(res, 100)
        print(
            f"  {res.get('passed')}/{res.get('failed')}/{res.get('errors')} ok={ok}",
            flush=True,
        )
        append_ledger(
            {
                "addr": hex(addr),
                "name": name,
                "ok": ok,
                "phase": "w3_readable",
                "passed": res.get("passed"),
                "failed": res.get("failed"),
                "errors": res.get("errors"),
            }
        )
        if not ok:
            continue
        rc = subprocess.run(
            [sys.executable, str(ROOT / "tools/audit/check_raw_casts.py")],
            cwd=ROOT,
            capture_output=True,
            text=True,
        )
        if rc.returncode != 0:
            print("  raw-cast fail", flush=True)
            continue
        kb = json.loads(KB_PATH.read_text(encoding="utf-8"))
        if flip_kb(kb, addr):
            KB_PATH.write_text(json.dumps(kb, indent=2) + "\n", encoding="utf-8")
            flips.append(name)
            print(f"  FLIP {len(flips)}", flush=True)
        if len(flips) >= 15:
            break

    print("FLIPS", flips, flush=True)
    true1, _ = count_ported(json.loads(KB_PATH.read_text(encoding="utf-8")))
    print(f"true {true1} delta {true1 - true0}", flush=True)
    Path("/tmp/w3_readable.json").write_text(json.dumps({"flips": flips, "true1": true1}))
    return 0 if flips else 1


if __name__ == "__main__":
    raise SystemExit(main())
