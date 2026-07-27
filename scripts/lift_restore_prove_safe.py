#!/usr/bin/env python3
"""Safe history-restore → Unicorn prove factory.

Restores pre-naked C from naked-intro^, force-rebuilds the TU, proves with
Unicorn 100/0/0, and ALWAYS reverts the file on compile/locate/extract failure
or non-perfect Unicorn. Never flips naked.
"""
from __future__ import annotations

import argparse
import json
import os
import re
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "scripts"))

from lift_grok_tracka_restore_prove import extract_func  # noqa: E402
from lift_inventory_batch4 import find_naked_block  # noqa: E402
from prove_inventory_batch4 import ensure_oracle, flip_kb  # noqa: E402
from tu_compile import docker_compile  # noqa: E402
from unicorn_c_campaign import count_ported, is_naked_near_def  # noqa: E402

os.environ.setdefault("BIPED_SIBLING_RESOLVE", "1")

NAKED_RE = re.compile(r"__attribute__\s*\(\s*\(\s*naked\b")
RESULTS_RE = re.compile(r"(\d+) passed, (\d+) failed, (\d+) errors")
SKIP_SUB = (
    "xdk",
    "libcmt",
    "tiff",
    "tif_",
    "bink",
    "d3d",
    "xapilib",
    "xboxkrnl",
    "xgraphic",
    "xmv",
    "xnet",
    "libm",
)


def find_intro_parent(name: str, addr: int, path: str) -> str | None:
    for needle in (f"/* {name} (0x", f"{name} (0x{addr:x})"):
        r = subprocess.run(
            ["git", "log", "-S", needle, "--format=%H", "--", path],
            cwd=ROOT,
            capture_output=True,
            text=True,
        )
        commits = [c for c in r.stdout.splitlines() if c]
        if commits:
            return f"{commits[0]}^"
    return None


def domain_rank(src: str, body_len: int, addr: int) -> tuple:
    s = 0
    if src.startswith("ai/"):
        s += 5
    if src.startswith("units/"):
        s += 5
    if src.startswith("math/"):
        s += 4
    if src.startswith("networking/") or "bungie_net" in src:
        s += 3
    if src.startswith("objects/") or src.startswith("structures/"):
        s += 3
    if src.startswith("interface/") or src.startswith("game/"):
        s += 2
    if "kb_common" in src:
        s -= 10
    if "rasterizer" in src:
        s -= 1
    return (-s, body_len, addr)


def uni(name: str, addr: int, seeds: int, timeout: float) -> tuple[int, int, int] | None:
    ensure_oracle(addr)
    env = {**os.environ, "BIPED_SIBLING_RESOLVE": "1"}
    try:
        r = subprocess.run(
            [
                sys.executable,
                "tools/equivalence/unicorn_diff.py",
                name,
                "--allow-stubs",
                "--no-stub-arg-trace",
                "--seeds",
                str(seeds),
                "-q",
            ],
            cwd=ROOT,
            capture_output=True,
            text=True,
            timeout=timeout,
            env=env,
        )
    except subprocess.TimeoutExpired:
        return None
    m = RESULTS_RE.search((r.stdout or "") + (r.stderr or ""))
    if not m:
        return None
    return tuple(map(int, m.groups()))  # type: ignore[return-value]


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--limit", type=int, default=40)
    ap.add_argument("--seeds", type=int, default=100)
    ap.add_argument("--timeout", type=float, default=90.0)
    ap.add_argument("--commit-every", type=int, default=3)
    ap.add_argument("--prefer", default="ai,units,math,networking,objects,structures,game,interface")
    args = ap.parse_args()
    prefer = [p.strip() for p in args.prefer.split(",") if p.strip()]

    kb = json.loads((ROOT / "kb.json").read_text())
    true0, false0 = count_ported(kb)
    print(f"start true={true0} false={false0}", flush=True)

    cands = []
    for o in kb["objects"]:
        src = o.get("source") or ""
        if any(x in src for x in SKIP_SUB):
            continue
        path = f"src/halo/{src}" if src.endswith(".c") else None
        if not path or not (ROOT / path).exists():
            continue
        text = (ROOT / path).read_text(errors="ignore")
        for fn in o.get("functions") or []:
            if not isinstance(fn, dict) or fn.get("ported") is not False:
                continue
            name = fn.get("name")
            addr_s = fn.get("addr")
            if not name or not addr_s:
                continue
            addr = int(addr_s, 16)
            naked = False
            for mm in re.finditer(rf"(?m)^[^\n]*\b{re.escape(name)}\s*\(", text):
                win = text[max(0, mm.start() - 220) : mm.start() + 40]
                if NAKED_RE.search(win) or "XBE naked" in win:
                    naked = True
                    break
            if not naked:
                continue
            cands.append((name, addr, src, path))

    # Build restorable with extractable parent bodies
    restorable = []
    for name, addr, src, path in cands:
        parent = find_intro_parent(name, addr, path)
        if not parent:
            continue
        try:
            old = subprocess.check_output(
                ["git", "show", f"{parent}:{path}"], cwd=ROOT, text=True
            )
        except subprocess.CalledProcessError:
            continue
        parent_naked = False
        for mm in re.finditer(rf"(?m)^[^\n]*\b{re.escape(name)}\s*\(", old):
            win = old[max(0, mm.start() - 220) : mm.start() + 40]
            if NAKED_RE.search(win) or "XBE naked" in win:
                parent_naked = True
                break
        if parent_naked:
            continue
        body = extract_func(old, name, addr)
        if not body:
            continue
        restorable.append((name, addr, src, path, parent, body))

    def pref_rank(t):
        name, addr, src, path, parent, body = t
        pref_i = 99
        for i, p in enumerate(prefer):
            if src.startswith(p + "/") or src.startswith(p):
                pref_i = i
                break
        base = domain_rank(src, len(body), addr)
        return (pref_i, *base)

    restorable = sorted(restorable, key=pref_rank)
    print(f"restorable={len(restorable)} (processing up to {args.limit})", flush=True)

    proven: list[str] = []
    skipped_tus: set[str] = set()
    processed = 0

    for name, addr, src, path, parent, body in restorable:
        if processed >= args.limit:
            break
        if src in skipped_tus:
            continue
        full = ROOT / path
        backup = full.read_text(encoding="utf-8", errors="replace")
        if not is_naked_near_def(backup.splitlines(), name, hex(addr)):
            continue
        processed += 1
        span = find_naked_block(backup, name, addr)
        if span is None:
            pat = re.compile(
                rf"/\*[^\n]*\b0x{addr:x}\b[\s\S]*?#if defined\(__clang__\)[\s\S]*?#endif\s*\n",
                re.I,
            )
            m = pat.search(backup)
            if not m:
                print(f"LOCATE_FAIL {name}", flush=True)
                continue
            span = (m.start(), m.end())
        start, end = span
        span_len = end - start
        if span_len > max(len(body) * 10, 80000):
            print(f"SPAN_GUARD {name} span={span_len} body={len(body)}", flush=True)
            continue
        new = backup[:start] + body + "\n" + backup[end:]
        if is_naked_near_def(new.splitlines(), name, hex(addr)):
            print(f"STILL_NAKED {name}", flush=True)
            continue
        full.write_text(new, encoding="utf-8")
        print(f"RESTORED {name} from {parent}", flush=True)

        for obj in (
            ROOT / "build/CMakeFiles/halo.dir/src/halo" / f"{src}.obj",
            ROOT / "build/CMakeFiles/halo.dir" / path.replace(".c", ".c.obj"),
        ):
            if obj.exists():
                obj.unlink()
        if not docker_compile(src):
            # Revert and keep trying other symbols in this TU. A single bad
            # extract must not blacklist the whole file for the rest of the run.
            print(f"COMPILE_FAIL revert {name} ({src})", flush=True)
            full.write_text(backup, encoding="utf-8")
            continue

        res = uni(name, addr, args.seeds, args.timeout)
        if res is None:
            print(f"UNI_FAIL/timeout revert {name}", flush=True)
            full.write_text(backup, encoding="utf-8")
            continue
        p, f, e = res
        print(f"UNI {name} {p}/{f}/{e}", flush=True)
        if p >= args.seeds and f == 0 and e == 0:
            if is_naked_near_def(full.read_text(errors="ignore").splitlines(), name, hex(addr)):
                print(f"BLOCK_NAKED_FLIP revert {name}", flush=True)
                full.write_text(backup, encoding="utf-8")
                continue
            if flip_kb(kb, addr):
                proven.append(name)
                (ROOT / "kb.json").write_text(json.dumps(kb, indent=2) + "\n")
                print(f"FLIP {name} n={len(proven)}", flush=True)
                if args.commit_every and len(proven) % args.commit_every == 0:
                    subprocess.run(["git", "add", "kb.json", path], cwd=ROOT, check=False)
                    msg = f"lift(track-a): {args.commit_every} Unicorn-prove restore batch (ported:true)."
                    # commit only if staged changes exist
                    st = subprocess.run(
                        ["git", "diff", "--cached", "--quiet"], cwd=ROOT
                    )
                    if st.returncode != 0:
                        subprocess.run(
                            ["git", "commit", "-m", msg],
                            cwd=ROOT,
                            check=False,
                        )
        else:
            # Revert non-perfect to keep tree healthy for next candidates
            print(f"REVERT nonperfect {name}", flush=True)
            full.write_text(backup, encoding="utf-8")

    (ROOT / "kb.json").write_text(json.dumps(kb, indent=2) + "\n")
    if proven:
        files = ["kb.json"]
        # stage any remaining modified sources for proven names
        subprocess.run(["git", "add", "-u", "src/halo", "kb.json"], cwd=ROOT, check=False)
        st = subprocess.run(["git", "diff", "--cached", "--quiet"], cwd=ROOT)
        if st.returncode != 0:
            subprocess.run(
                [
                    "git",
                    "commit",
                    "-m",
                    f"lift(track-a): {len(proven)} Unicorn-prove history-restore (ported:true).",
                ],
                cwd=ROOT,
                check=False,
            )

    true1, false1 = count_ported(json.loads((ROOT / "kb.json").read_text()))
    print(
        {
            "proven": proven,
            "n": len(proven),
            "processed": processed,
            "skipped_tus": sorted(skipped_tus),
            "true": true1,
            "false": false1,
            "delta": true1 - true0,
        },
        flush=True,
    )
    return 0 if proven else 1


if __name__ == "__main__":
    raise SystemExit(main())
