#!/usr/bin/env python3
"""Unicorn-prove already-readable jmp/alias forwarders (ported:false).

Also lifts remaining naked symbol-bounded jmp thunks when locate works.
"""
from __future__ import annotations

import json
import re
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "scripts"))
sys.path.insert(0, str(ROOT / "tools" / "equivalence"))

from capstone import CS_ARCH_X86, CS_MODE_32, Cs  # noqa: E402
from xbe import Xbe  # noqa: E402
from xbe_to_coff import load_kb, xbe_bytes  # noqa: E402
from lift_inventory_batch4 import find_naked_block  # noqa: E402
from prove_inventory_batch4 import ensure_oracle, flip_kb  # noqa: E402
from unicorn_c_campaign import (  # noqa: E402
    KB_PATH,
    append_ledger,
    clear_pass,
    count_ported,
    func_name,
    git_push,
    is_naked_near_def,
    resolve_src,
    run_unicorn,
)
import lift_jmp_thunks as jt  # noqa: E402
import lift_thin_wrappers as ltw  # noqa: E402

COMMIT_EVERY = 12


def main() -> int:
    import argparse

    ap = argparse.ArgumentParser()
    ap.add_argument("--limit", type=int, default=0)
    ap.add_argument("--seeds", type=int, default=100)
    ap.add_argument("--timeout", type=float, default=40.0)
    ap.add_argument("--commit-every", type=int, default=COMMIT_EVERY)
    ap.add_argument("--no-push", action="store_true")
    ap.add_argument("--lift-naked", action="store_true")
    args = ap.parse_args()

    jt.merge_remote_kb()
    kb, name_by, decl_by, src_by, ported = ltw.load_kb_names()
    _, starts = load_kb(KB_PATH)
    xbe = Xbe((ROOT / "halo-patched" / "cachebeta.xbe").read_bytes())
    md = Cs(CS_ARCH_X86, CS_MODE_32)
    true0, false0 = count_ported(kb)

    jobs = []
    for i, ai in enumerate(starts):
        if ported.get(ai) is not False:
            continue
        src = src_by.get(ai) or ""
        if any(s in src.lower() for s in jt.SKIP_SRC):
            continue
        end = starts[i + 1] if i + 1 < len(starts) else ai + 32
        if end - ai > 32:
            continue
        ops = jt.disasm_bounded(xbe, md, ai, end)
        decl = decl_by.get(ai) or f"void {name_by[ai]}(void);"
        got = jt.try_emit_thunk(ops, decl, name_by[ai], name_by)
        if not got:
            continue
        body, tgt = got
        sp = resolve_src(src)
        if not sp:
            continue
        naked = is_naked_near_def(sp.read_text(errors="replace").splitlines(), name_by[ai], hex(ai))
        jobs.append(
            {
                "addr": ai,
                "name": name_by[ai],
                "src": src,
                "path": sp,
                "body": body,
                "tgt": tgt,
                "naked": naked,
            }
        )

    # Prefer already-readable, then ported targets
    jobs.sort(
        key=lambda j: (
            0 if not j["naked"] else 1,
            0 if ported.get(j["tgt"]) is True else 1,
            j["addr"],
        )
    )
    if args.limit:
        jobs = jobs[: args.limit]

    print(
        f"alias jobs={len(jobs)} readable={sum(1 for j in jobs if not j['naked'])} "
        f"naked={sum(1 for j in jobs if j['naked'])} kb true={true0} false={false0}",
        flush=True,
    )

    flips = []
    shas = []
    touched: set[Path] = set()
    since = 0

    for job in jobs:
        ai = job["addr"]
        name = job["name"]
        sp = job["path"]
        print(
            f"\n== {hex(ai)} {name} -> {hex(job['tgt'])} "
            f"{name_by.get(job['tgt'])} [{'naked' if job['naked'] else 'prove'}] ==",
            flush=True,
        )
        orig = None
        if job["naked"]:
            if not args.lift_naked:
                print("  skip naked (pass --lift-naked)", flush=True)
                continue
            text = sp.read_text(encoding="utf-8", errors="replace")
            span = find_naked_block(text, name, ai) or find_naked_block(
                text, f"FUN_{ai:08x}", ai
            )
            if span is None:
                # Fallback: replace clang/#else/#endif block by comment marker
                print("  locate FAIL", flush=True)
                continue
            c_src = f"/* {name} (0x{ai:x}) — readable C lift (jmp thunk). */\n{job['body']}"
            orig = text
            sp.write_text(text[: span[0]] + c_src + "\n" + text[span[1] :], encoding="utf-8")
            for stale in (ROOT / "build").rglob(sp.name + ".obj"):
                try:
                    stale.unlink()
                except OSError:
                    pass

        if not ensure_oracle(ai):
            if orig is not None:
                sp.write_text(orig, encoding="utf-8")
            print("  oracle FAIL", flush=True)
            continue
        res = run_unicorn(hex(ai), ai, args.seeds, timeout=args.timeout)
        ok = clear_pass(res, args.seeds)
        if not ok:
            res2 = run_unicorn(name, ai, args.seeds, timeout=args.timeout)
            if clear_pass(res2, args.seeds):
                res, ok = res2, True
        print(
            f"  ok={ok} {res.get('passed')}/{res.get('failed')}/{res.get('errors')} "
            f"rc={res.get('rc')}",
            flush=True,
        )
        append_ledger(
            {
                "addr": hex(ai),
                "name": name,
                "ok": ok,
                "phase": "prove_jmp_alias",
                "passed": res.get("passed"),
                "failed": res.get("failed"),
                "errors": res.get("errors"),
            }
        )
        if not ok:
            if orig is not None:
                sp.write_text(orig, encoding="utf-8")
                print("  REVERT", flush=True)
            continue
        kb = json.loads(KB_PATH.read_text(encoding="utf-8"))
        if flip_kb(kb, ai):
            flips.append(hex(ai))
            since += 1
            ported[ai] = True
            KB_PATH.write_text(json.dumps(kb, indent=2) + "\n", encoding="utf-8")
            touched.add(sp)
            print(f"  FLIP total={len(flips)}", flush=True)
        if args.commit_every and since >= args.commit_every:
            sha = jt.commit_chunk(since, touched, do_push=not args.no_push)
            # rewrite commit message via amending is forbidden; leave jmp thunk msg
            if sha:
                shas.append(sha)
            since = 0
            touched.clear()

    if since:
        # custom commit
        jt.merge_remote_kb()
        files = ["kb.json", "scripts/prove_jmp_aliases.py", "scripts/lift_jmp_thunks.py"]
        for p in touched:
            try:
                files.append(str(p.relative_to(ROOT)))
            except ValueError:
                pass
        subprocess.run(["git", "add"] + files, cwd=ROOT, check=False)
        subprocess.run(
            [
                "git",
                "commit",
                "-m",
                f"verify(track-a): unicorn-prove {since} jmp/alias forwarders (ported:true).",
            ],
            cwd=ROOT,
            check=False,
        )
        if not args.no_push:
            try:
                git_push()
            except SystemExit:
                pass
        shas.append(
            subprocess.run(
                ["git", "rev-parse", "HEAD"], cwd=ROOT, capture_output=True, text=True
            ).stdout.strip()
        )

    true1, false1 = count_ported(json.loads(KB_PATH.read_text(encoding="utf-8")))
    summary = {
        "proven": len(flips),
        "flips": flips,
        "shas": shas,
        "true0": true0,
        "true1": true1,
        "false1": false1,
    }
    Path("/tmp/prove_jmp_alias_summary.json").write_text(json.dumps(summary, indent=2))
    print("DONE", summary, flush=True)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
