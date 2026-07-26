#!/usr/bin/env python3
"""Auto-lift packed jmp / frame-tail-jmp thunks (16-byte aliases) → Unicorn-prove.

Patterns (symbol-bounded):
  jmp TARGET
  push ebp; mov ebp,esp; pop ebp; jmp TARGET

Emits a cdecl forwarder matching kb decl params. Prefer gameplay sources;
skip xdk/d3d/libcmt. Pull-before-push; union remote ported:true.
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
import lift_thin_wrappers as ltw  # noqa: E402

SKIP_SRC = ("xdk/", "d3d", "dsound", "libcmt", "bink", "xnet", "xapilib", "kb_common")
COMMIT_EVERY = 10
MAX_SIZE = 32


def load_kb_names():
    kb = json.loads(KB_PATH.read_text(encoding="utf-8"))
    name_by, decl_by, src_by, ported = {}, {}, {}, {}
    for o in kb.get("objects", []):
        src = o.get("source") or ""
        for fn in o.get("functions") or []:
            if not isinstance(fn, dict) or not fn.get("addr"):
                continue
            ai = int(fn["addr"], 16)
            nm = func_name(fn) or f"FUN_{ai:08x}"
            name_by[ai] = nm
            decl_by[ai] = fn.get("decl") or ""
            src_by[ai] = src
            ported[ai] = fn.get("ported")
    return kb, name_by, decl_by, src_by, ported


def merge_remote_kb() -> None:
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
    try:
        theirs = json.loads(r.stdout)
    except json.JSONDecodeError:
        return
    ours = json.loads(KB_PATH.read_text(encoding="utf-8"))
    tmap = {}
    for o in theirs.get("objects", []):
        for fn in o.get("functions") or []:
            if isinstance(fn, dict) and fn.get("addr") and fn.get("ported") is True:
                tmap[int(fn["addr"], 16)] = True
    n = 0
    for o in ours.get("objects", []):
        for fn in o.get("functions") or []:
            if not isinstance(fn, dict) or not fn.get("addr"):
                continue
            ai = int(fn["addr"], 16)
            if tmap.get(ai) and fn.get("ported") is not True:
                fn["ported"] = True
                n += 1
    if n:
        KB_PATH.write_text(json.dumps(ours, indent=2) + "\n", encoding="utf-8")
        print(f"merged {n} remote ported:true", flush=True)


def disasm_bounded(xbe: Xbe, md: Cs, ai: int, end: int) -> list[tuple[str, str]]:
    raw = xbe_bytes(xbe, ai, max(1, min(end, ai + 64) - ai))
    ops: list[tuple[str, str]] = []
    for insn in md.disasm(raw, ai):
        if insn.address >= end:
            break
        ops.append((insn.mnemonic, insn.op_str))
        if insn.mnemonic in ("ret", "retn", "jmp"):
            break
    return ops


def try_emit_thunk(
    ops: list[tuple[str, str]], decl: str, name: str, name_by: dict
) -> tuple[str, int] | None:
    """Return (c_body, target_addr) or None."""
    target = None
    if (
        len(ops) == 4
        and ops[0] == ("push", "ebp")
        and ops[1] == ("mov", "ebp, esp")
        and ops[2] == ("pop", "ebp")
        and ops[3][0] == "jmp"
    ):
        m = re.search(r"0x([0-9a-fA-F]+)", ops[3][1])
        if m:
            target = int(m.group(1), 16)
    elif len(ops) == 1 and ops[0][0] == "jmp":
        m = re.search(r"0x([0-9a-fA-F]+)", ops[0][1])
        if m:
            target = int(m.group(1), 16)
    if target is None:
        return None
    fn = name_by.get(target)
    if not fn:
        return None
    # don't self-jmp
    if fn == name:
        return None
    sig = ltw.cdecl_sig(decl, name)
    ps = ltw.params(sig)
    is_void = "void" in sig.split("(")[0]
    args = ", ".join(ps)
    ret = "" if is_void else "return "
    body = f"{sig}\n{{\n  {ret}{fn}({args});\n}}\n"
    return body, target


def commit_chunk(n: int, touched: set[Path], do_push: bool = True) -> str | None:
    merge_remote_kb()
    files = ["kb.json", "scripts/lift_jmp_thunks.py"]
    for p in touched:
        try:
            files.append(str(p.relative_to(ROOT)))
        except ValueError:
            files.append(str(p))
    subprocess.run(["git", "add"] + files, cwd=ROOT, check=False)
    msg = f"lift(track-a): jmp thunks + Unicorn-prove {n} (ported:true)."
    r = subprocess.run(
        ["git", "commit", "-m", msg], cwd=ROOT, capture_output=True, text=True
    )
    if r.returncode != 0:
        print("commit failed:", r.stdout, r.stderr, file=sys.stderr)
        return None
    sha = subprocess.run(
        ["git", "rev-parse", "HEAD"], cwd=ROOT, capture_output=True, text=True
    ).stdout.strip()
    if do_push:
        try:
            git_push()
        except SystemExit as e:
            print("push failed", e, flush=True)
    print(f"COMMIT+PUSH {sha}", flush=True)
    return sha


def main() -> int:
    import argparse

    ap = argparse.ArgumentParser()
    ap.add_argument("--limit", type=int, default=0)
    ap.add_argument("--commit-every", type=int, default=COMMIT_EVERY)
    ap.add_argument("--seeds", type=int, default=100)
    ap.add_argument("--timeout", type=float, default=40.0)
    ap.add_argument("--no-push", action="store_true")
    ap.add_argument("--prefer-ported-targets", action="store_true")
    args = ap.parse_args()

    merge_remote_kb()
    kb, name_by, decl_by, src_by, ported = load_kb_names()
    _, starts = load_kb(KB_PATH)
    xbe = Xbe((ROOT / "halo-patched" / "cachebeta.xbe").read_bytes())
    md = Cs(CS_ARCH_X86, CS_MODE_32)
    true0, false0 = count_ported(kb)

    jobs = []
    for i, ai in enumerate(starts):
        if ported.get(ai) is not False:
            continue
        src = src_by.get(ai) or ""
        if any(s in src.lower() for s in SKIP_SRC):
            continue
        end = starts[i + 1] if i + 1 < len(starts) else ai + MAX_SIZE
        if end - ai > MAX_SIZE:
            continue
        sp = resolve_src(src)
        if not sp:
            continue
        name = name_by[ai]
        if not is_naked_near_def(sp.read_text(errors="replace").splitlines(), name, hex(ai)):
            continue
        ops = disasm_bounded(xbe, md, ai, end)
        decl = decl_by.get(ai) or f"void {name}(void);"
        got = try_emit_thunk(ops, decl, name, name_by)
        if not got:
            continue
        body, tgt = got
        if args.prefer_ported_targets and ported.get(tgt) is not True:
            continue
        jobs.append((ai, name, src, sp, body, tgt))

    # Prefer targets already ported:true
    jobs.sort(key=lambda j: (0 if ported.get(j[5]) is True else 1, j[0]))
    if args.limit:
        jobs = jobs[: args.limit]

    print(
        f"jmp-thunk jobs={len(jobs)} kb true={true0} false={false0}",
        flush=True,
    )

    flips: list[str] = []
    shas: list[str] = []
    touched: set[Path] = set()
    since = 0

    for ai, name, src, sp, body, tgt in jobs:
        print(
            f"\n== {hex(ai)} {name} -> {hex(tgt)} {name_by.get(tgt)} ({src}) ==",
            flush=True,
        )
        c_src = f"/* {name} (0x{ai:x}) — readable C lift (jmp thunk). */\n{body}"
        text = sp.read_text(encoding="utf-8", errors="replace")
        if not is_naked_near_def(text.splitlines(), name, hex(ai)):
            print("  not naked anymore", flush=True)
            continue
        span = find_naked_block(text, name, ai)
        if span is None:
            span = find_naked_block(text, f"FUN_{ai:08x}", ai)
        if span is None:
            print("  locate FAIL", flush=True)
            continue
        sp.write_text(text[: span[0]] + c_src + "\n" + text[span[1] :], encoding="utf-8")
        for stale in (ROOT / "build").rglob(sp.name + ".obj"):
            try:
                stale.unlink()
            except OSError:
                pass
        if not ensure_oracle(ai):
            sp.write_text(text, encoding="utf-8")
            print("  oracle FAIL", flush=True)
            continue
        res = run_unicorn(hex(ai), ai, args.seeds, timeout=args.timeout)
        ok = clear_pass(res, args.seeds)
        if not ok:
            res2 = run_unicorn(name, ai, args.seeds, timeout=args.timeout)
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
                "phase": "lift_jmp_thunk",
                "target": hex(tgt),
                "passed": res.get("passed"),
                "failed": res.get("failed"),
                "errors": res.get("errors"),
            }
        )
        if not ok:
            sp.write_text(text, encoding="utf-8")
            print("  REVERT", flush=True)
            continue
        rc = subprocess.run(
            [sys.executable, str(ROOT / "tools/audit/check_raw_casts.py")],
            cwd=ROOT,
            capture_output=True,
            text=True,
        )
        if rc.returncode != 0:
            sp.write_text(text, encoding="utf-8")
            print("  REVERT raw-cast", flush=True)
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
            sha = commit_chunk(since, touched, do_push=not args.no_push)
            if sha:
                shas.append(sha)
            since = 0
            touched.clear()

    if since:
        sha = commit_chunk(since, touched, do_push=not args.no_push)
        if sha:
            shas.append(sha)

    true1, false1 = count_ported(json.loads(KB_PATH.read_text(encoding="utf-8")))
    summary = {
        "proven": len(flips),
        "flips": flips,
        "shas": shas,
        "true0": true0,
        "true1": true1,
        "false1": false1,
    }
    Path("/tmp/jmp_thunk_summary.json").write_text(json.dumps(summary, indent=2))
    print("DONE", summary, flush=True)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
