#!/usr/bin/env python3
"""Track A grokN: prove readable-C focus-domain falses via Unicorn 100/0/0."""
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

from prove_inventory_batch4 import ensure_oracle, flip_kb  # noqa: E402
from tu_compile import docker_compile  # noqa: E402
from unicorn_c_campaign import (  # noqa: E402
    KB_PATH,
    append_ledger,
    clear_pass,
    count_ported,
    func_name,
    is_naked_near_def,
    resolve_src,
)

FOCUS = (
    "networking/",
    "tag_files/",
    "saved",
    "cache/",
    "cseries/",
    "structures/",
    "physics/",
    "interface/",
    "bitmaps/",
)
SKIP = (
    "xdk/",
    "libcmt",
    "bink",
    "d3d",
    "dsound",
    "xnet",
    "xapilib",
    "kb_common",
    "tiff",
)
COMMIT_EVERY = 5
TIMEOUT = 80.0
SEEDS = 100


def run_uni(name: str, addr: int) -> dict:
    outj = ROOT / "artifacts" / "equivalence" / f"uni_{addr:08x}_s{SEEDS}.json"
    outj.parent.mkdir(parents=True, exist_ok=True)
    logp = ROOT / "artifacts" / "equivalence" / f"{name}_smoke.log"
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
        "tail": text[-500:],
        "missing_candidate": "missing_build_object" in text
        or "cannot find build .obj" in text,
    }


def inventory() -> list[dict]:
    kb = json.loads(KB_PATH.read_text(encoding="utf-8"))
    cache: dict[Path, list[str]] = {}
    out: list[dict] = []
    for obj in kb.get("objects", []):
        src = (obj.get("source") or "").replace("\\", "/")
        if any(x in src.lower() for x in SKIP):
            continue
        if not any(d in src for d in FOCUS):
            continue
        if "cseries/" in src:
            pass
        sp = resolve_src(obj.get("source") or "")
        if sp is None:
            continue
        if sp not in cache:
            cache[sp] = sp.read_text(encoding="utf-8", errors="replace").splitlines()
        lines = cache[sp]
        for fn in obj.get("functions") or []:
            if not isinstance(fn, dict) or not fn.get("addr"):
                continue
            if fn.get("ported") is not False:
                continue
            name = func_name(fn)
            addr = fn["addr"]
            if "cseries/" in src and name and "rdtsc" in name.lower():
                continue
            if is_naked_near_def(lines, name, addr):
                continue
            out.append(
                {
                    "addr": addr,
                    "addr_int": int(addr, 16),
                    "name": name or f"FUN_{int(addr, 16):08x}",
                    "src": src,
                    "sp": sp,
                    "fn": fn,
                }
            )
    out.sort(key=lambda r: (r["src"], r["addr_int"]))
    return out


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


def commit_push(n: int, names: list[str]) -> str | None:
    merge_remote_ported()
    subprocess.run(
        ["git", "add", "kb.json", "tools/equivalence/leaf_cache.json"],
        cwd=ROOT,
        check=False,
    )
    subprocess.run(["git", "add", "-u", "src/halo"], cwd=ROOT, check=False)
    sample = ", ".join(names[:4])
    if len(names) > 4:
        sample += ", ..."
    msg = f"lift(track-a): grokN Unicorn-prove {n} ({sample})."
    r = subprocess.run(
        ["git", "commit", "-m", msg], cwd=ROOT, capture_output=True, text=True
    )
    if r.returncode != 0:
        print("commit failed", r.stdout, r.stderr, flush=True)
        return None
    sha = subprocess.run(
        ["git", "rev-parse", "HEAD"], cwd=ROOT, capture_output=True, text=True
    ).stdout.strip()
    subprocess.run(
        ["git", "fetch", "pastudan", "track-a-collision-bsp"],
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
    print(pr.stdout, pr.stderr, flush=True)
    print(f"COMMIT+PUSH {sha}", flush=True)
    return sha


def main() -> int:
    limit = int(sys.argv[1]) if len(sys.argv) > 1 else 0
    rows = inventory()
    if limit:
        rows = rows[:limit]
    true0, false0 = count_ported(json.loads(KB_PATH.read_text(encoding="utf-8")))
    print(f"queue={len(rows)} true={true0} false={false0}", flush=True)

    flips: list[str] = []
    pending_names: list[str] = []
    since = 0
    blockers: list[dict] = []
    compiled: set[str] = set()

    for r in rows:
        name, ai, src = r["name"], r["addr_int"], r["src"]
        print(f"\n== {hex(ai)} {name} ({src}) ==", flush=True)
        src_rel = src.replace("\\", "/")
        if src_rel.startswith("src/halo/"):
            src_rel = src_rel[len("src/halo/") :]
        if src_rel not in compiled:
            if not docker_compile(src_rel):
                blockers.append({"addr": hex(ai), "name": name, "why": "compile"})
                print("  compile FAIL", flush=True)
                continue
            compiled.add(src_rel)
        if not ensure_oracle(ai):
            blockers.append({"addr": hex(ai), "name": name, "why": "oracle"})
            print("  oracle FAIL", flush=True)
            continue
        res = run_uni(name, ai)
        if not clear_pass(res, SEEDS):
            res2 = run_uni(hex(ai), ai)
            if clear_pass(res2, SEEDS) or (res2.get("passed") or 0) > (
                res.get("passed") or 0
            ):
                res = res2
                name = hex(ai)
        ok = clear_pass(res, SEEDS)
        print(
            f"  ok={ok} {res.get('passed')}/{res.get('failed')}/{res.get('errors')} "
            f"{res.get('dt')}s",
            flush=True,
        )
        append_ledger(
            {
                "addr": hex(ai),
                "name": name,
                "ok": ok,
                "phase": "grokN_prove",
                "passed": res.get("passed"),
                "failed": res.get("failed"),
                "errors": res.get("errors"),
                "dt": res.get("dt"),
                "timeout": res.get("timeout"),
            }
        )
        if not ok:
            blockers.append(
                {
                    "addr": hex(ai),
                    "name": r["name"],
                    "why": "unicorn",
                    "score": f"{res.get('passed')}/{res.get('failed')}/{res.get('errors')}",
                    "timeout": res.get("timeout"),
                }
            )
            continue
        kb = json.loads(KB_PATH.read_text(encoding="utf-8"))
        if flip_kb(kb, ai):
            KB_PATH.write_text(json.dumps(kb, indent=2) + "\n", encoding="utf-8")
            flips.append(hex(ai))
            pending_names.append(r["name"])
            since += 1
            print(f"  FLIP total={len(flips)}", flush=True)
        if since >= COMMIT_EVERY:
            commit_push(since, pending_names)
            since = 0
            pending_names = []

    if since:
        commit_push(since, pending_names)

    true1, false1 = count_ported(json.loads(KB_PATH.read_text(encoding="utf-8")))
    summary = {
        "proven": len(flips),
        "flips": flips,
        "true0": true0,
        "true1": true1,
        "delta": true1 - true0,
        "blockers": blockers[:40],
        "blocker_n": len(blockers),
    }
    outp = ROOT / "artifacts" / "equivalence" / "grokN_prove_summary.json"
    outp.write_text(json.dumps(summary, indent=2) + "\n", encoding="utf-8")
    print("DONE", summary, flush=True)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
