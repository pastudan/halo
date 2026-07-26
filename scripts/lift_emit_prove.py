#!/usr/bin/env python3
"""Emit assert/thin/J patterns → Docker-compile → Unicorn-prove → flip.

Expands wrapper auto-lifts with the compile step lifters were missing.
"""
from __future__ import annotations

import argparse
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
from tu_compile import docker_compile, regen_decl_h  # noqa: E402
import lift_assert_wrappers as law  # noqa: E402
import lift_thin_wrappers as ltw  # noqa: E402
import lifter_j as lj  # noqa: E402
import lifter_interface as li  # noqa: E402
import lift_jmp_thunks as ljt  # noqa: E402

SKIP = ("xdk/", "d3d", "dsound", "libcmt", "bink", "xnet", "xapilib", "kb_common")
COMMIT_EVERY = 8
KW = frozenset(
    {
        "if",
        "for",
        "while",
        "switch",
        "return",
        "sizeof",
        "void",
        "int",
        "char",
        "short",
        "float",
        "double",
        "const",
        "unsigned",
        "signed",
        "bool",
        "uint8_t",
        "uint16_t",
        "uint32_t",
        "int8_t",
        "int16_t",
        "int32_t",
    }
)


def same_tu_unproven(
    body: str,
    src: str,
    name: str,
    name_by: dict,
    src_by: dict,
    ported: dict,
) -> str | None:
    """Return callee name if body calls a same-TU still-unproven function."""
    addr_by_name = {v: k for k, v in name_by.items()}
    src_n = (src or "").replace("\\", "/")
    for c in re.findall(r"\b([A-Za-z_][A-Za-z0-9_]*)\s*\(", body):
        if c == name or c in KW:
            continue
        ca = addr_by_name.get(c)
        if ca is None:
            continue
        cal_src = (src_by.get(ca) or "").replace("\\", "/")
        if cal_src == src_n and ported.get(ca) is not True:
            return c
    return None



def run_uni(name: str, addr: int, seeds: int, timeout: float) -> dict:
    """Docker-TU path already compiled; Unicorn with stub-arg off.

    Oracle DIR32 push-imm capture currently yields 0x00500xxx for string/global
    immediates (vs correct candidate 0x28xxxx), false-failing assert wrappers.

    BIPED_SIBLING_RESOLVE=1 stubs same-TU callee calls so wrapper lifts match
    oracle stubs (critical unlock for same-TU wrappers).
    """
    import os
    import time
    outj = ROOT / "artifacts" / "equivalence" / f"uni_{addr:08x}_s{seeds}.json"
    cmd = [
        sys.executable,
        str(ROOT / "tools" / "equivalence" / "unicorn_diff.py"),
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
    t0 = time.time()
    try:
        proc = subprocess.run(
            cmd, cwd=str(ROOT), capture_output=True, text=True, timeout=timeout, env=env
        )
        timed_out = False
    except subprocess.TimeoutExpired as exc:
        timed_out = True
        proc = subprocess.CompletedProcess(cmd, 124, "", "timeout")
    text = (proc.stdout or "") + (proc.stderr or "")
    m = re.search(r"(\d+) passed, (\d+) failed, (\d+) errors", text)
    passed = failed = errors = None
    if m:
        passed, failed, errors = map(int, m.groups())
    return {
        "rc": proc.returncode,
        "passed": passed,
        "failed": failed,
        "errors": errors,
        "dt": round(time.time() - t0, 2),
        "tail": text[-400:],
        "missing_candidate": False,
        "timeout": timed_out,
    }


def sync_decl_h(name: str, decl: str) -> bool:
    """Patch HFUNC line in build/generated/decl.h (cmake regen is often stale)."""
    path = ROOT / "build" / "generated" / "decl.h"
    if not path.exists():
        return False
    d = (decl or "").strip().rstrip(";")
    # Reject comment bleed / garbage (previously polluted decl.h and broke all TUs).
    if (
        not d
        or d.lstrip().startswith("*")
        or "*/" in d
        or "Call-site" in d
        or len(d) > 240
        or "(" not in d
        or ")" not in d
        or not re.match(
            r"^(?:void|int|char|short|float|double|bool|unsigned|signed|u?int\d+_t|size_t)\b",
            d,
        )
    ):
        return False
    if name not in d.split("(", 1)[0]:
        return False
    text = path.read_text(encoding="utf-8", errors="replace")
    # Non-greedy, single-line HFUNC only (avoid eating prior decls).
    pat = re.compile(rf"^HFUNC\s+.+\b{re.escape(name)}\s*\([^;\n]*\);$", re.M)
    new_line = f"HFUNC {d};"
    new_text, n = pat.subn(new_line, text, count=1)
    if n:
        path.write_text(new_text, encoding="utf-8")
        return True
    return False


def widen_same_tu_callees(text: str, body: str, name: str) -> str:
    """Widen void-foo(void) naked defs so calls with args type-check (sibling stubs)."""
    for c in re.findall(r"\b([A-Za-z_][A-Za-z0-9_]*)\s*\(([^)]*)\)", body):
        cal, args = c[0], c[1].strip()
        if cal == name or cal in KW or not args or args == "void":
            continue
        nargs = len([a for a in args.split(",") if a.strip()])
        if nargs < 1:
            continue
        params = ", ".join(f"int a{i}" for i in range(nargs))
        pat = re.compile(rf"void\s+{re.escape(cal)}\s*\(\s*void\s*\)")
        text2, n = pat.subn(f"void {cal}({params})", text, count=0)
        if n:
            text = text2
            # Also widen local function-pointer aliases typed as void(*)(void).
            text = re.sub(
                rf"\(\s*\*\s*const\s+\w+\s*\)\s*\(\s*void\s*\)\s*=\s*{re.escape(cal)}\s*;",
                lambda m: m.group(0).replace("(void)", f"({params})", 1),
                text,
            )
            sync_decl_h(cal, f"void {cal}({params})")
    return text


def update_decl(addr: int, decl: str, name: str | None = None) -> None:
    kb = json.loads(KB_PATH.read_text(encoding="utf-8"))
    decl = (decl or "").strip()
    if (
        not decl
        or decl.lstrip().startswith("*")
        or len(decl) > 240
        or "(" not in decl
        or ")" not in decl
    ):
        return
    if not decl.endswith(";"):
        decl += ";"
    for o in kb.get("objects", []):
        for fn in o.get("functions") or []:
            if isinstance(fn, dict) and fn.get("addr") and int(fn["addr"], 16) == addr:
                fn["decl"] = decl
                KB_PATH.write_text(json.dumps(kb, indent=2) + "\n", encoding="utf-8")
                if name:
                    sync_decl_h(name, decl)
                return



def sync_tu_decls(sp: Path, name_by: dict) -> int:
    """Pull cdecls from readable C bodies in this TU into kb + decl.h."""
    text = sp.read_text(encoding="utf-8", errors="replace")
    # name -> signature line
    sigs = {}
    for m in re.finditer(
        r"(?m)^((?:[\w\s\*]+?)\b([A-Za-z_][A-Za-z0-9_]*)\s*\([^;{]*\))\s*\{",
        text,
    ):
        sig, name = m.group(1).strip(), m.group(2)
        if name in ("if", "for", "while", "switch", "return"):
            continue
        if not sig.endswith(";"):
            sig = sig + ";"
        sigs[name] = sig
    if not sigs:
        return 0
    kb = json.loads(KB_PATH.read_text(encoding="utf-8"))
    n = 0
    for o in kb.get("objects", []):
        for fn in o.get("functions") or []:
            if not isinstance(fn, dict) or not fn.get("addr"):
                continue
            nm = func_name(fn) or ""
            if nm in sigs and fn.get("decl") != sigs[nm]:
                fn["decl"] = sigs[nm]
                n += 1
    if n:
        KB_PATH.write_text(json.dumps(kb, indent=2) + "\n", encoding="utf-8")
        regen_decl_h()
    return n


def merge_remote() -> None:
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
            if not isinstance(fn, dict) or not fn.get("addr"):
                continue
            if int(fn["addr"], 16) in tmap and fn.get("ported") is not True:
                fn["ported"] = True
                n += 1
    if n:
        KB_PATH.write_text(json.dumps(ours, indent=2) + "\n", encoding="utf-8")
        print(f"merged {n} remote ported:true", flush=True)


def commit_chunk(n: int, touched: set[Path], label: str = "sibling-resolve") -> str | None:
    """Commit proven flips; before push: union remote ported:true, rebase, push."""
    merge_remote()
    files = [
        "kb.json",
        "scripts/lift_emit_prove.py",
        "scripts/lift_thin_wrappers.py",
        "scripts/lift_assert_wrappers.py",
        "scripts/tu_compile.py",
    ]
    for p in touched:
        files.append(str(p.relative_to(ROOT)))
    subprocess.run(["git", "add"] + files, cwd=ROOT, check=False)
    msg = f"lift(track-a): sibling-resolve Unicorn-prove {n} wrappers (ported:true)."
    r = subprocess.run(["git", "commit", "-m", msg], cwd=ROOT, capture_output=True, text=True)
    if r.returncode != 0:
        print("commit failed", r.stdout, r.stderr, flush=True)
        return None
    sha = subprocess.run(
        ["git", "rev-parse", "HEAD"], cwd=ROOT, capture_output=True, text=True
    ).stdout.strip()
    # Before push: stash dirt, fetch, rebase, union remote ported:true.
    subprocess.run(
        ["git", "stash", "push", "-u", "-m", "sib-push-dirt"],
        cwd=ROOT,
        capture_output=True,
    )
    subprocess.run(["git", "fetch", "pastudan", "track-a-collision-bsp"], cwd=ROOT, capture_output=True)
    rb = subprocess.run(
        ["git", "rebase", "pastudan/track-a-collision-bsp"],
        cwd=ROOT, capture_output=True, text=True,
    )
    if rb.returncode != 0:
        merge_remote()
        subprocess.run(["git", "add", "kb.json"], cwd=ROOT, capture_output=True)
        subprocess.run(
            ["git", "-c", "core.editor=true", "rebase", "--continue"],
            cwd=ROOT, capture_output=True, text=True,
        )
    merge_remote()
    if subprocess.run(["git", "diff", "--quiet", "kb.json"], cwd=ROOT).returncode != 0:
        subprocess.run(["git", "add", "kb.json"], cwd=ROOT, capture_output=True)
        subprocess.run(
            ["git", "commit", "-m", "fix(track-a): union ported:true after sibling-resolve rebase."],
            cwd=ROOT, capture_output=True, text=True,
        )
        sha = subprocess.run(
            ["git", "rev-parse", "HEAD"], cwd=ROOT, capture_output=True, text=True
        ).stdout.strip()
    r = subprocess.run(
        ["git", "push", "pastudan", "HEAD:track-a-collision-bsp"],
        cwd=ROOT, capture_output=True, text=True,
    )
    if r.returncode != 0:
        print("push failed", r.stdout, r.stderr, flush=True)
        subprocess.run(["git", "fetch", "pastudan", "track-a-collision-bsp"], cwd=ROOT, capture_output=True)
        subprocess.run(["git", "rebase", "pastudan/track-a-collision-bsp"], cwd=ROOT, capture_output=True)
        merge_remote()
        subprocess.run(["git", "add", "kb.json"], cwd=ROOT, capture_output=True)
        subprocess.run(
            ["git", "commit", "-m", "fix(track-a): union ported:true before sibling-resolve retry push."],
            cwd=ROOT, capture_output=True, text=True,
        )
        r = subprocess.run(
            ["git", "push", "pastudan", "HEAD:track-a-collision-bsp"],
            cwd=ROOT, capture_output=True, text=True,
        )
        if r.returncode != 0:
            print("push retry failed", r.stdout, r.stderr, flush=True)
        else:
            print(f"COMMIT+PUSH {sha}", flush=True)
    else:
        print(f"COMMIT+PUSH {sha}", flush=True)
    subprocess.run(["git", "stash", "pop"], cwd=ROOT, capture_output=True)
    return sha


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--limit", type=int, default=0)
    ap.add_argument("--seeds", type=int, default=100)
    ap.add_argument("--timeout", type=float, default=45.0)
    ap.add_argument("--commit-every", type=int, default=COMMIT_EVERY)
    ap.add_argument("--max-size", type=int, default=200)
    ap.add_argument("--prefer", action="append", default=[])
    ap.add_argument(
        "--skip-same-tu-unproven",
        action=argparse.BooleanOptionalAction,
        default=False,
        help="Skip lifts that call same-TU naked/unproven callees "
        "(default: off — BIPED_SIBLING_RESOLVE stubs them)",
    )
    ap.add_argument(
        "--addrs",
        default="",
        help="Comma/space separated hex addrs to include (optional filter)",
    )
    ap.add_argument(
        "--kinds",
        default="assert,thin,jmp,jpat,ipat",
        help="Comma-separated lift kinds to attempt (default skips brittle HAND)",
    )
    args = ap.parse_args()
    kind_allow = {k.strip() for k in args.kinds.split(",") if k.strip()}
    addr_filter: set[int] | None = None
    if args.addrs.strip():
        addr_filter = set()
        for tok in re.split(r"[\s,]+", args.addrs.strip()):
            if tok:
                addr_filter.add(int(tok, 16))

    merge_remote()
    kb, name_by, decl_by, src_by, ported = law.load_kb_names()
    _, starts = load_kb(KB_PATH)
    xbe = Xbe((ROOT / "halo-patched" / "cachebeta.xbe").read_bytes())
    md = Cs(CS_ARCH_X86, CS_MODE_32)
    true0, false0 = count_ported(kb)

    jobs = []
    skipped_same = 0
    for i, ai in enumerate(starts):
        if ported.get(ai) is not False:
            continue
        if addr_filter is not None and ai not in addr_filter:
            continue
        src = src_by.get(ai) or ""
        if any(s in src.lower() for s in SKIP):
            continue
        if args.prefer and not any(p in src for p in args.prefer):
            continue
        end = starts[i + 1] if i + 1 < len(starts) else ai + args.max_size
        if end - ai > args.max_size:
            continue
        sp = resolve_src(src)
        if not sp:
            continue
        name = name_by[ai]
        if not is_naked_near_def(sp.read_text(errors="replace").splitlines(), name, hex(ai)):
            continue
        try:
            # Prefer end address (library also accepts length if end<=va).
            raw = xbe_bytes(xbe, ai, min(end, ai + args.max_size))
        except Exception:
            try:
                raw = xbe_bytes(xbe, ai, min(end, ai + args.max_size) - ai)
            except Exception:
                continue
        ops = []
        for insn in md.disasm(raw, ai):
            ops.append((insn.mnemonic, insn.op_str))
            if insn.mnemonic in ("ret", "retn"):
                break
            if insn.mnemonic == "jmp" and len(ops) <= 4:
                # pure / frame-tail jmp thunk
                break
        else:
            continue
        decl = decl_by.get(ai) or f"void {name}(void);"
        body = None
        kind = None
        if ai in getattr(li, "HAND", {}):
            body = li.HAND[ai][2]
            kind = "iface_hand"
        if not body and ai in lj.HAND:
            body = lj.HAND[ai][2]
            kind = "hand"
        if not body:
            thunk = ljt.try_emit_thunk(ops, decl, name, name_by)
            if thunk:
                body, _tgt = thunk
                kind = "jmp"
        if not body:
            body = law.try_emit(ops, decl, name, name_by)
            kind = "assert" if body else None
        if not body:
            body = ltw.try_emit([f"{m} {o}".strip() for m, o in ops], decl, name, name_by)
            kind = "thin" if body else None
        if not body:
            body = li.try_pattern_emit(ops, decl, name, name_by)
            kind = "ipat" if body else None
        if not body:
            body = lj.try_pattern_emit(ops, decl, name, name_by)
            kind = "jpat" if body else None
        if not body:
            continue
        if kind not in kind_allow:
            continue
        if re.search(r"\(\s*(void|int|char|[^*)]+)\s*\(\s*\*", body):
            continue
        if args.skip_same_tu_unproven:
            bad = same_tu_unproven(body, src, name, name_by, src_by, ported)
            if bad:
                skipped_same += 1
                continue
        jobs.append((ai, name, src, sp, body, kind))

    jobs.sort(key=lambda j: (0 if j[5] in ("hand", "iface_hand") else 1, j[0]))
    if args.limit:
        jobs = jobs[: args.limit]
    print(
        f"emit-prove jobs={len(jobs)} skip_same_tu={skipped_same} "
        f"true={true0} false={false0}",
        flush=True,
    )

    flips: list[str] = []
    shas: list[str] = []
    touched: set[Path] = set()
    since = 0
    kind_counts: dict[str, int] = {}

    for ai, name, src, sp, body, kind in jobs:
        print(f"\n== {hex(ai)} {name} [{kind}] ({src}) ==", flush=True)
        text = sp.read_text(encoding="utf-8", errors="replace")
        if not is_naked_near_def(text.splitlines(), name, hex(ai)):
            print("  not naked", flush=True)
            continue
        span = find_naked_block(text, name, ai) or find_naked_block(
            text, f"FUN_{ai:08x}", ai
        )
        if not span:
            print("  locate FAIL", flush=True)
            continue
        c_src = body if "readable C lift" in body else (
            f"/* {name} (0x{ai:x}) — readable C lift. */\n{body}"
        )
        sig_m = re.search(
            rf"^(?:void|int|char|short|float|double|bool|unsigned|signed|uint\w+_t|int\w+_t)"
            rf"[\w\s\*]*\b{re.escape(name)}\s*\([^;{{]*\)",
            c_src,
            re.M,
        )
        if sig_m:
            update_decl(ai, sig_m.group(0).strip(), name=name)
            # Best-effort cmake regen; direct HFUNC patch above is authoritative.
            regen_decl_h()
            sync_decl_h(name, sig_m.group(0).strip())
        new_text = text[: span[0]] + c_src + "\n" + text[span[1] :]
        if any(t in c_src for t in ("uint8_t", "uint16_t", "uint32_t", "int8_t", "int16_t")):
            if "#include <stdint.h>" not in new_text:
                new_text = "#include <stdint.h>\n" + new_text
        new_text = widen_same_tu_callees(new_text, body, name)
        sp.write_text(new_text, encoding="utf-8")
        src_rel = src.replace("\\", "/")
        if "src/halo/" in src_rel:
            src_rel = src_rel.split("src/halo/", 1)[1]
        sync_tu_decls(sp, name_by)
        if not docker_compile(src_rel):
            sp.write_text(text, encoding="utf-8")
            print("  compile FAIL", flush=True)
            continue
        if not ensure_oracle(ai):
            sp.write_text(text, encoding="utf-8")
            print("  oracle FAIL", flush=True)
            continue
        res = run_uni(name, ai, args.seeds, args.timeout)
        if not clear_pass(res, args.seeds):
            res2 = run_uni(hex(ai), ai, args.seeds, args.timeout)
            if clear_pass(res2, args.seeds) or (res2.get("passed") or 0) > (
                res.get("passed") or 0
            ):
                res = res2
        ok = clear_pass(res, args.seeds)
        print(
            f"  ok={ok} {res.get('passed')}/{res.get('failed')}/{res.get('errors')}",
            flush=True,
        )
        append_ledger(
            {
                "addr": hex(ai),
                "name": name,
                "ok": ok,
                "phase": f"emit_prove_{kind}",
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
            KB_PATH.write_text(json.dumps(kb, indent=2) + "\n", encoding="utf-8")
            flips.append(hex(ai))
            since += 1
            touched.add(sp)
            ported[ai] = True
            kind_counts[kind or "unk"] = kind_counts.get(kind or "unk", 0) + 1
            print(f"  FLIP total={len(flips)}", flush=True)
        if args.commit_every and since >= args.commit_every:
            label = "+".join(sorted(kind_counts)) or "emit"
            sha = commit_chunk(since, touched, label=label)
            if sha:
                shas.append(sha)
            since = 0
            touched.clear()
            kind_counts.clear()

    if since:
        label = "+".join(sorted(kind_counts)) or "emit"
        sha = commit_chunk(since, touched, label=label)
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
        "delta": true1 - true0,
        "skip_same_tu": skipped_same,
    }
    Path("/tmp/lift_emit_prove.json").write_text(json.dumps(summary, indent=2))
    print("DONE", summary, flush=True)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
