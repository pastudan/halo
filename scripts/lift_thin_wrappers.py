#!/usr/bin/env python3
"""Auto-lift thin named-callee naked wrappers across gameplay domains; Unicorn-prove."""
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

SKIP_SRC = ("xdk/", "d3d", "dsound", "libcmt", "bink", "xnet", "xapilib", "kb_common")
COMMIT_EVERY = 8


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


def cdecl_sig(decl: str, name: str) -> str:
    d = re.sub(r"\s*@<\w+>", "", decl or "")
    d = re.sub(r"/\*\s*@<\w+>\s*\*/", "", d)
    d = re.sub(r"\s+", " ", d).strip()
    if not d.endswith(";"):
        d += ";"
    if name not in d:
        return f"void {name}(void)"
    return d[:-1]


def params(sig: str) -> list[str]:
    m = re.search(r"\(([^)]*)\)", sig)
    if not m:
        return []
    raw = m.group(1).strip()
    if not raw or raw == "void":
        return []
    return [p.strip().split()[-1].strip("*") for p in raw.split(",") if p.strip()]


def try_emit(insns: list[str], decl: str, name: str, name_by: dict) -> str | None:
    ops = []
    for line in insns:
        parts = line.strip().split(None, 1)
        if parts:
            ops.append((parts[0], parts[1] if len(parts) > 1 else ""))
    if not ops or ops[-1][0] not in ("ret", "retn"):
        return None
    body = ops[:-1]
    sig = cdecl_sig(decl, name)
    ps = params(sig)
    is_void = "void" in sig.split("(")[0]

    def callee(addr_s: str) -> str | None:
        m = re.search(r"0x([0-9a-fA-F]+)", addr_s)
        return name_by.get(int(m.group(1), 16)) if m else None

    # push imm; call F; pop ecx / add esp,4
    if (
        len(body) == 3
        and body[0][0] == "push"
        and body[1][0] == "call"
        and body[2][0] in ("pop", "add")
        and re.match(r"-?0x[0-9a-fA-F]+|-?\d+$", body[0][1])
    ):
        fn = callee(body[1][1])
        if not fn:
            return None
        ret = "" if is_void else "return "
        return f"{sig}\n{{\n  {ret}{fn}({body[0][1]});\n}}\n"

    # call F; push imm; call G; pop ecx
    if (
        len(body) == 4
        and body[0][0] == "call"
        and body[1][0] == "push"
        and body[2][0] == "call"
        and body[3] == ("pop", "ecx")
    ):
        f1, f2 = callee(body[0][1]), callee(body[2][1])
        if not f1 or not f2:
            return None
        return f"{sig}\n{{\n  {f1}();\n  {f2}({body[1][1]});\n}}\n"

    # lights_*: mov eax,[g]; push eax; call F; … push imm; call G; add esp,8; ret
    if (
        len(body) == 6
        and body[0][0] == "mov"
        and "dword ptr [" in body[0][1]
        and body[1][0] == "push"
        and body[1][1] == "eax"
        and body[2][0] == "call"
        and body[3][0] == "push"
        and body[4][0] == "call"
        and body[5][0] == "add"
    ):
        f1, f2 = callee(body[2][1]), callee(body[4][1])
        g = re.search(r"\[0x([0-9a-fA-F]+)\]", body[0][1])
        if f1 and f2 and g:
            return (
                f"{sig}\n{{\n"
                f"  {f1}(*(void **)0x{g.group(1)});\n"
                f"  {f2}({body[3][1]});\n"
                f"}}\n"
            )

    if not (
        len(body) >= 3
        and body[0] == ("push", "ebp")
        and body[1] == ("mov", "ebp, esp")
        and body[-1] == ("pop", "ebp")
    ):
        return None
    mid = body[2:-1]

    # profile activate/deactivate: push edi; mov edi,arg; push imm; call F; add; pop edi
    if (
        len(mid) == 6
        and mid[0] == ("push", "edi")
        and mid[1][0] == "mov"
        and mid[1][1].startswith("edi,")
        and mid[2][0] == "push"
        and mid[3][0] == "call"
        and mid[4][0] == "add"
        and mid[5] == ("pop", "edi")
    ):
        fn = callee(mid[3][1])
        if not fn or not ps:
            return None
        return f"{sig}\n{{\n  (void){ps[0]};\n  {fn}({mid[2][1]});\n}}\n"

    # push ebx; mov ebx,[ebp+8]; push imm/addr; call F; add esp,4; pop ebx
    if (
        len(mid) == 6
        and mid[0] == ("push", "ebx")
        and mid[1] == ("mov", "ebx, dword ptr [ebp + 8]")
        and mid[2][0] == "push"
        and mid[3][0] == "call"
        and mid[4][0] == "add"
        and mid[5] == ("pop", "ebx")
    ):
        fn = callee(mid[3][1])
        imm = mid[2][1]
        # if imm is a code pointer with a name, use the name (function ptr)
        m = re.match(r"0x([0-9a-fA-F]+)$", imm)
        arg = imm
        if m:
            nm = name_by.get(int(m.group(1), 16))
            if nm:
                arg = nm
        if not fn or not ps:
            return None
        return f"{sig}\n{{\n  (void){ps[0]};\n  {fn}({arg});\n}}\n"

    # F(arg0, 0)
    if (
        len(mid) == 5
        and mid[0] == ("mov", "eax, dword ptr [ebp + 8]")
        and mid[1] == ("push", "0")
        and mid[2] == ("push", "eax")
        and mid[3][0] == "call"
        and mid[4][0] == "add"
    ):
        fn = callee(mid[3][1])
        if not fn or not ps:
            return None
        return f"{sig}\n{{\n  {fn}({ps[0]}, 0);\n}}\n"

    # recorded_animation_play style: mov eax,[ebp+0xc]; push imm; push eax; mov eax,[ebp+8]; call; add
    if (
        len(mid) == 6
        and mid[0] == ("mov", "eax, dword ptr [ebp + 0xc]")
        and mid[1][0] == "push"
        and mid[2] == ("push", "eax")
        and mid[3] == ("mov", "eax, dword ptr [ebp + 8]")
        and mid[4][0] == "call"
        and mid[5][0] == "add"
    ):
        fn = callee(mid[4][1])
        if not fn or len(ps) < 2:
            return None
        ret = "" if is_void else "return "
        return f"{sig}\n{{\n  {ret}{fn}({ps[0]}, {ps[1]}, {mid[1][1]});\n}}\n"

    # stdcall one-arg
    if (
        len(mid) == 3
        and mid[0] == ("mov", "eax, dword ptr [ebp + 8]")
        and mid[1] == ("push", "eax")
        and mid[2][0] == "call"
    ):
        fn = callee(mid[2][1])
        if not fn or not ps:
            return None
        ret = "" if is_void else "return "
        return f"{sig}\n{{\n  {ret}{fn}({ps[0]});\n}}\n"

    # cdecl one-arg
    if (
        len(mid) == 4
        and mid[0] == ("mov", "eax, dword ptr [ebp + 8]")
        and mid[1] == ("push", "eax")
        and mid[2][0] == "call"
        and mid[3][0] == "add"
    ):
        fn = callee(mid[2][1])
        if not fn or not ps:
            return None
        ret = "" if is_void else "return "
        return f"{sig}\n{{\n  {ret}{fn}({ps[0]});\n}}\n"

    # 2-arg forward
    if (
        len(mid) == 6
        and mid[0] == ("mov", "eax, dword ptr [ebp + 0xc]")
        and mid[1] == ("mov", "ecx, dword ptr [ebp + 8]")
        and mid[2] == ("push", "eax")
        and mid[3] == ("push", "ecx")
        and mid[4][0] == "call"
        and mid[5][0] == "add"
    ):
        fn = callee(mid[4][1])
        if not fn or len(ps) < 2:
            return None
        ret = "" if is_void else "return "
        return f"{sig}\n{{\n  {ret}{fn}({ps[0]}, {ps[1]});\n}}\n"

    # 3-arg forward: mov eax,[ebp+0x14]; mov ecx,[ebp+0x10]; mov edx,[ebp+0xc]; push*3; call; add
    if (
        len(mid) == 8
        and mid[0][0] == "mov"
        and "ebp + 0x14" in mid[0][1]
        and mid[1][0] == "mov"
        and "ebp + 0x10" in mid[1][1]
        and mid[2][0] == "mov"
        and "ebp + 0xc" in mid[2][1]
        and mid[3][0] == "push"
        and mid[4][0] == "push"
        and mid[5][0] == "push"
        and mid[6][0] == "call"
        and mid[7][0] == "add"
    ):
        fn = callee(mid[6][1])
        if not fn or len(ps) < 3:
            return None
        ret = "" if is_void else "return "
        return f"{sig}\n{{\n  {ret}{fn}({ps[0]}, {ps[1]}, {ps[2]});\n}}\n"

    # TIFF 2-arg + trailing 0
    if (
        len(mid) >= 6
        and mid[0] == ("mov", "eax, dword ptr [ebp + 0xc]")
        and mid[1] == ("mov", "ecx, dword ptr [ebp + 8]")
        and mid[2] == ("push", "0")
        and mid[3] == ("push", "eax")
        and mid[4] == ("push", "ecx")
        and mid[5][0] == "call"
    ):
        fn = callee(mid[5][1])
        if not fn or len(ps) < 2:
            return None
        ret = "" if is_void else "return "
        return f"{sig}\n{{\n  {ret}{fn}({ps[0]}, {ps[1]}, 0);\n}}\n"

    # global + arg: mov eax,[ebp+8]; mov ecx,[imm]; push eax; push ecx; call; add
    if (
        len(mid) == 7
        and mid[0] == ("mov", "eax, dword ptr [ebp + 8]")
        and mid[1][0] == "mov"
        and mid[1][1].startswith("ecx, dword ptr [0x")
        and mid[2] == ("push", "eax")
        and mid[3] == ("push", "ecx")
        and mid[4][0] == "call"
        and mid[5][0] == "add"
    ):
        # len may be 6 without trailing junk
        pass
    if (
        len(mid) == 6
        and mid[0] == ("mov", "eax, dword ptr [ebp + 8]")
        and mid[1][0] == "mov"
        and "ecx, dword ptr [0x" in mid[1][1]
        and mid[2] == ("push", "eax")
        and mid[3] == ("push", "ecx")
        and mid[4][0] == "call"
        and mid[5][0] == "add"
    ):
        fn = callee(mid[4][1])
        g = re.search(r"\[0x([0-9a-fA-F]+)\]", mid[1][1])
        if not fn or not ps or not g:
            return None
        ret = "" if is_void else "return "
        return (
            f"{sig}\n{{\n  {ret}{fn}(*(void **)0x{g.group(1)}, {ps[0]});\n}}\n"
        )


    # object_get + tag_get → return 1
    if (
        len(mid) == 10
        and mid[0] == ("mov", "eax, dword ptr [ebp + 8]")
        and mid[1][0] == "push"
        and mid[2] == ("push", "eax")
        and mid[3][0] == "call"
        and mid[4][0] == "mov"
        and "ecx, dword ptr [eax]" in mid[4][1]
        and mid[5] == ("push", "ecx")
        and mid[6][0] == "push"
        and mid[7][0] == "call"
        and mid[8][0] == "add"
        and mid[9] == ("mov", "al, 1")
    ):
        f1, f2 = callee(mid[3][1]), callee(mid[7][1])
        if f1 and f2 and ps:
            ret = "" if is_void else "return "
            return (
                f"{sig}\n{{\n"
                f"  void *obj = {f1}({ps[0]}, {mid[1][1]});\n"
                f"  {f2}(*(void **)obj, {mid[6][1]});\n"
                f"  {ret}1;\n"
                f"}}\n"
            )

    # datum_get from global + fld float field
    if (
        len(mid) == 7
        and mid[0][0] == "movsx"
        and "word ptr [ebp + 8]" in mid[0][1]
        and mid[1][0] == "mov"
        and "ecx, dword ptr [0x" in mid[1][1]
        and mid[2] == ("push", "eax")
        and mid[3] == ("push", "ecx")
        and mid[4][0] == "call"
        and mid[5][0] == "add"
        and mid[6][0] == "fld"
    ):
        fn = callee(mid[4][1])
        g = re.search(r"\[0x([0-9a-fA-F]+)\]", mid[1][1])
        off_m = re.search(r"\[eax(?: \+ (0x[0-9a-f]+|\d+))?\]", mid[6][1])
        if fn and g and off_m and ps:
            o = int(off_m.group(1), 0) if off_m.group(1) else 0
            ret = "" if is_void else "return "
            return (
                f"{sig}\n{{\n"
                f"  void *d = {fn}(*(void **)0x{g.group(1)}, {ps[0]});\n"
                f"  {ret}*(float *)((char *)d + 0x{o:x});\n"
                f"}}\n"
            )

    return None


def commit_chunk(n: int) -> str | None:
    subprocess.run(["git", "add", "-u", "src/halo", "kb.json"], cwd=ROOT, check=False)
    subprocess.run(
        [
            "git",
            "add",
            "kb.json",
            "tools/equivalence/leaf_cache.json",
            "scripts/lift_thin_wrappers.py",
        ],
        cwd=ROOT,
        check=False,
    )
    msg = f"lift(track-a): thin wrappers + Unicorn-prove {n} (ported:true)."
    r = subprocess.run(["git", "commit", "-m", msg], cwd=ROOT, capture_output=True, text=True)
    if r.returncode != 0:
        print("commit failed:", r.stdout, r.stderr, file=sys.stderr)
        return None
    sha = subprocess.run(
        ["git", "rev-parse", "HEAD"], cwd=ROOT, capture_output=True, text=True
    ).stdout.strip()
    git_push()
    print(f"COMMIT+PUSH {sha}", flush=True)
    return sha


def main() -> int:
    kb, name_by, decl_by, src_by, ported = load_kb_names()
    by_addr, starts = load_kb(KB_PATH)
    xbe = Xbe((ROOT / "halo-patched" / "cachebeta.xbe").read_bytes())
    md = Cs(CS_ARCH_X86, CS_MODE_32)
    true0, _ = count_ported(kb)
    flips: list[str] = []
    shas: list[str] = []
    since = 0
    cache: dict[Path, list[str]] = {}

    for i, ai in enumerate(starts):
        if ported.get(ai) is not False:
            continue
        src = src_by.get(ai) or ""
        if any(s in src.lower() for s in SKIP_SRC):
            continue
        end = starts[i + 1] if i + 1 < len(starts) else ai + 64
        size = end - ai
        if size > 96:
            continue
        sp = resolve_src(src)
        if not sp:
            continue
        if sp not in cache:
            cache[sp] = sp.read_text(encoding="utf-8", errors="replace").splitlines()
        name = name_by[ai]
        if not is_naked_near_def(cache[sp], name, hex(ai)):
            continue
        try:
            raw = xbe_bytes(xbe, ai, min(end, ai + 64))
        except Exception:
            continue
        insns = []
        for insn in md.disasm(raw, ai):
            insns.append(f"{insn.mnemonic} {insn.op_str}".strip())
            if insn.mnemonic in ("ret", "retn"):
                break
        else:
            continue
        # skip HS macro-eval (handled elsewhere)
        joined = " ".join(insns)
        if "0xcc560" in joined and "0xcbf80" in joined:
            continue
        decl = decl_by.get(ai) or f"void {name}(void);"
        body = try_emit(insns, decl, name, name_by)
        if not body:
            continue
        # raw-cast guard: reject new 0x function casts in body (globals ok as *(T*)0x)
        if re.search(r"\(\s*(void|int|char|[^*)]+)\s*\(\s*\*", body):
            continue
        c_src = f"/* {name} (0x{ai:x}) — readable C lift (thin wrapper). */\n{body}"
        text = sp.read_text(encoding="utf-8", errors="replace")
        span = find_naked_block(text, name, ai)
        if span is None:
            print(f"skip locate {hex(ai)} {name}", flush=True)
            continue
        sp.write_text(text[: span[0]] + c_src + "\n" + text[span[1] :], encoding="utf-8")
        cache[sp] = sp.read_text(encoding="utf-8", errors="replace").splitlines()
        print(f"LIFTED {hex(ai)} {name}", flush=True)
        for stale in (ROOT / "build").rglob(sp.name + ".obj"):
            try:
                stale.unlink()
            except OSError:
                pass
        if not ensure_oracle(ai):
            sp.write_text(text, encoding="utf-8")
            cache[sp] = text.splitlines()
            print("  oracle FAIL", flush=True)
            continue
        res = run_unicorn(name, ai, 100, timeout=40.0)
        ok = clear_pass(res, 100)
        if not ok:
            res2 = run_unicorn(hex(ai), ai, 100, timeout=40.0)
            if clear_pass(res2, 100):
                res, ok = res2, True
        print(f"  ok={ok} {res.get('passed')}/{res.get('failed')}/{res.get('errors')}", flush=True)
        append_ledger(
            {
                "addr": hex(ai),
                "name": name,
                "ok": ok,
                "phase": "lift_thin",
                "passed": res.get("passed"),
                "failed": res.get("failed"),
                "errors": res.get("errors"),
            }
        )
        if not ok:
            sp.write_text(text, encoding="utf-8")
            cache[sp] = text.splitlines()
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
            cache[sp] = text.splitlines()
            print("  REVERT raw-cast", flush=True)
            continue
        kb = json.loads(KB_PATH.read_text(encoding="utf-8"))
        if flip_kb(kb, ai):
            flips.append(hex(ai))
            since += 1
            ported[ai] = True
            KB_PATH.write_text(json.dumps(kb, indent=2) + "\n", encoding="utf-8")
        if since >= COMMIT_EVERY:
            sha = commit_chunk(since)
            if sha:
                shas.append(sha)
            since = 0

    if since:
        sha = commit_chunk(since)
        if sha:
            shas.append(sha)

    true1, _ = count_ported(json.loads(KB_PATH.read_text(encoding="utf-8")))
    summary = {
        "proven": len(flips),
        "flips": flips,
        "shas": shas,
        "true0": true0,
        "true1": true1,
    }
    Path("/tmp/thin_lift_summary.json").write_text(json.dumps(summary, indent=2))
    print("DONE", summary, flush=True)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
