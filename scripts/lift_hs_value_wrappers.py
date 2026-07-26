#!/usr/bin/env python3
"""Lift HS macro-eval wrappers that return a value via hs_return(thread, v).

Pattern A (local slot):
  push ecx; mov [ebp-4],0; args=evaluate(...); if(args){ v=F(args...); [ebp-4]=v; }
  hs_return(thread, [ebp-4]);

Pattern B (float bitcast / eax return):
  args=evaluate(...); if(args){ hs_return(thread, (int)F(...)); }
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
from lift_hs_macro_wrappers import (  # noqa: E402
    HS_EVAL,
    HS_RETURN,
    _cast_args,
    _param_types,
    callee_addr,
)

COMMIT_EVERY = 8


def c_ident(ai: int, name_by: dict, decl_by: dict) -> str | None:
    d = decl_by.get(ai) or ""
    m = re.search(r"(\w+)\s*\(", d)
    if m:
        return m.group(1)
    return name_by.get(ai)


def parse_arg_loads(loads: list[tuple[str, str]], decl_by: dict, name_by: dict):
    """Parse action call args from insn list ending with call ACTION."""
    if not loads or loads[-1][0] != "call":
        return None
    action_addr = callee_addr(loads[-1][1])
    if action_addr is None:
        return None
    action_name = c_ident(action_addr, name_by, decl_by)
    if not action_name:
        return None
    body = loads[:-1]
    reg: dict[str, str] = {}
    push_stack: list[str] = []
    i = 0
    while i < len(body):
        m, op = body[i]
        if m == "xor" and op in ("edx, edx", "ecx, ecx", "eax, eax"):
            reg[op.split(",")[0].strip()] = "0"
            i += 1
            continue
        if m == "mov":
            mm = re.match(
                r"(e[abcd]x), dword ptr \[eax(?: \+ (0x[0-9a-f]+|\d+))?\]", op
            )
            if mm:
                dst, off = mm.group(1), mm.group(2)
                o = int(off, 0) if off else 0
                if o % 4 != 0:
                    return None
                reg[dst] = f"args[{o // 4}]"
                i += 1
                continue
            mm = re.match(
                r"(d|c|a)x, word ptr \[eax(?: \+ (0x[0-9a-f]+|\d+))?\]", op
            )
            if mm:
                letter, off = mm.group(1), mm.group(2)
                o = int(off, 0) if off else 0
                full = {"d": "edx", "c": "ecx", "a": "eax"}[letter]
                reg[full] = (
                    f"(int16_t)(uint16_t)args[{o // 4}]"
                    if o % 4 == 0
                    else f"(int16_t)*(uint16_t *)((char *)args + {o})"
                )
                i += 1
                continue
            mm = re.match(
                r"(d|c|a)l, byte ptr \[eax(?: \+ (0x[0-9a-f]+|\d+))?\]", op
            )
            if mm:
                letter, off = mm.group(1), mm.group(2)
                o = int(off, 0) if off else 0
                full = {"d": "edx", "c": "ecx", "a": "eax"}[letter]
                reg[full] = f"(char)(uint8_t)*((unsigned char *)args + {o})"
                i += 1
                continue
            return None
        if m == "movsx":
            mm = re.match(
                r"(e[abcd]x), word ptr \[eax(?: \+ (0x[0-9a-f]+|\d+))?\]", op
            )
            if mm:
                dst, off = mm.group(1), mm.group(2)
                o = int(off, 0) if off else 0
                reg[dst] = (
                    f"(int16_t)(uint16_t)args[{o // 4}]"
                    if o % 4 == 0
                    else f"(int16_t)*(uint16_t *)((char *)args + {o})"
                )
                i += 1
                continue
            return None
        if m == "fld":
            mm = re.match(r"dword ptr \[eax(?: \+ (0x[0-9a-f]+|\d+))?\]", op)
            if not mm:
                return None
            o = int(mm.group(1), 0) if mm.group(1) else 0
            reg["st0"] = (
                f"*(float *)&args[{o // 4}]"
                if o % 4 == 0
                else f"*(float *)((char *)args + {o})"
            )
            i += 1
            continue
        if m == "sub" and op.startswith("esp,"):
            i += 1
            continue
        if m == "fstp":
            if "st0" not in reg:
                return None
            mm = re.match(r"dword ptr \[esp(?: \+ (0x[0-9a-f]+|\d+))?\]", op)
            if not mm:
                return None
            if "_float_slots" not in reg:
                reg["_float_slots"] = {}
            off = int(mm.group(1), 0) if mm.group(1) else 0
            reg["_float_slots"][off] = reg["st0"]
            i += 1
            continue
        if m == "push":
            if op in ("eax", "ecx", "edx"):
                expr = reg.get(op)
                if expr:
                    push_stack.append(expr)
                    i += 1
                    continue
                if op == "ecx" and "st0" in reg:
                    push_stack.append("__slot__")
                    i += 1
                    continue
                return None
            if re.match(r"-?0x[0-9a-fA-F]+|-?\d+$", op):
                push_stack.append(op)
                i += 1
                continue
            return None
        return None

    slots = reg.get("_float_slots")
    if isinstance(slots, dict) and slots:
        if any(p == "__slot__" for p in push_stack):
            ordered = [slots[k] for k in sorted(slots.keys())]
            new_stack = []
            fi = 0
            for p in push_stack:
                if p == "__slot__":
                    if fi >= len(ordered):
                        return None
                    new_stack.append(ordered[fi])
                    fi += 1
                else:
                    new_stack.append(p)
            if fi != len(ordered):
                return None
            push_stack = new_stack
        else:
            ordered = [slots[k] for k in sorted(slots.keys())]
            push_stack = push_stack + ordered
    if any(p == "__slot__" for p in push_stack):
        return None
    c_args = list(reversed(push_stack))
    c_args = _cast_args(action_addr, c_args, decl_by)
    pts = _param_types(decl_by.get(action_addr) or "")
    if pts and len(c_args) != len(pts):
        return None
    call = f"{action_name}({', '.join(c_args)})" if c_args else f"{action_name}()"
    return call


def try_emit(insns: list[str], name: str, name_by: dict, decl_by: dict) -> str | None:
    ops = []
    for line in insns:
        parts = line.strip().split(None, 1)
        ops.append((parts[0], parts[1] if len(parts) > 1 else ""))
    if not ops or ops[-1][0] not in ("ret", "retn"):
        return None
    body = ops[:-1]
    while body and body[-1][0] == "pop" and body[-1][1] in ("ebp", "esi"):
        body = body[:-1]
    if body and body[-1][0] == "mov" and body[-1][1] == "esp, ebp":
        body = body[:-1]
    if not (
        len(body) >= 12
        and body[0] == ("push", "ebp")
        and body[1] == ("mov", "ebp, esp")
    ):
        return None
    text = " | ".join(f"{m} {o}" for m, o in body)
    if "0xcc560" not in text or "0xcbf80" not in text:
        return None

    # Locate evaluate call
    eval_i = None
    for i, (m, o) in enumerate(body):
        if m == "call" and callee_addr(o) == HS_EVAL:
            eval_i = i
            break
    if eval_i is None:
        return None
    rest = body[eval_i + 1 :]
    if not rest or rest[0][0] != "add":
        return None
    rest = rest[1:]
    if len(rest) < 2 or not (rest[0][0] == "test" and rest[0][1] == "eax, eax"):
        return None
    if rest[1][0] != "je":
        return None
    mid = rest[2:]
    if mid and mid[-1][0] == "add":
        mid = mid[:-1]

    # Find hs_return
    hr_i = None
    for i, (m, o) in enumerate(mid):
        if m == "call" and callee_addr(o) == HS_RETURN:
            hr_i = i
            break
    if hr_i is None or hr_i < 2:
        return None
    if not (mid[hr_i - 1][0] == "push" and mid[hr_i - 1][1] == "esi"):
        return None
    ret_push = mid[hr_i - 2]
    if ret_push[0] != "push":
        return None

    action_part = mid[: hr_i - 2]

    # Pattern: call F; mov byte/word/dword [ebp-4], al/ax/eax; mov r32,[ebp-4]; push r32
    if ret_push[1] in ("eax", "ecx", "edx") and len(action_part) >= 2:
        ap = list(action_part)
        # strip mov r32, [ebp-4]
        if (
            ap
            and ap[-1][0] == "mov"
            and "ebp - 4" in ap[-1][1]
            and ap[-1][1].startswith(ret_push[1] + ",")
        ):
            ap = ap[:-1]
        if ap and ap[-1][0] == "mov" and "ptr [ebp - 4]" in ap[-1][1]:
            store = ap[-1]
            ap = ap[:-1]
            call = parse_arg_loads(ap, decl_by, name_by)
            if call:
                if "byte ptr" in store[1]:
                    cast = "(int)(unsigned char)"
                elif "word ptr" in store[1]:
                    cast = "(int)(unsigned short)"
                else:
                    cast = "(int)"
                return (
                    f"void {name}(int16_t function_index, int thread_datum, char init)\n"
                    f"{{\n"
                    f"  int *args = (int *)hs_macro_function_evaluate(function_index, thread_datum, init);\n"
                    f"  if (args) {{\n"
                    f"    hs_return(thread_datum, {cast}{call});\n"
                    f"  }}\n"
                    f"}}\n"
                )

    # Pattern: push eax after call (return value in eax) — ret_push == eax
    if ret_push[1] == "eax":
        call = parse_arg_loads(action_part, decl_by, name_by)
        if not call:
            return None
        return (
            f"void {name}(int16_t function_index, int thread_datum, char init)\n"
            f"{{\n"
            f"  int *args = (int *)hs_macro_function_evaluate(function_index, thread_datum, init);\n"
            f"  if (args) {{\n"
            f"    hs_return(thread_datum, (int){call});\n"
            f"  }}\n"
            f"}}\n"
        )

    # Pattern: float result via fstp [ebp-x]; mov edx,[ebp-x]; push edx
    if ret_push[1] == "edx" and action_part:
        # look for call then fstp local then mov edx, local
        # simplify: find last call, then require fstp + mov edx
        call_i = None
        for i in range(len(action_part) - 1, -1, -1):
            if action_part[i][0] == "call":
                call_i = i
                break
        if call_i is None:
            return None
        after = action_part[call_i + 1 :]
        before = action_part[: call_i + 1]
        call = parse_arg_loads(before, decl_by, name_by)
        if not call:
            return None
        # after: fstp [ebp-8]; mov edx,[ebp-8]  OR just use float return bitcast
        if any(m == "fstp" for m, _ in after):
            return (
                f"void {name}(int16_t function_index, int thread_datum, char init)\n"
                f"{{\n"
                f"  int *args = (int *)hs_macro_function_evaluate(function_index, thread_datum, init);\n"
                f"  if (args) {{\n"
                f"    float _fv = {call};\n"
                f"    hs_return(thread_datum, *(int *)&_fv);\n"
                f"  }}\n"
                f"}}\n"
            )
    return None


def commit_chunk(n: int) -> str | None:
    subprocess.run(["git", "add", "-u", "src/halo/hs", "kb.json"], cwd=ROOT, check=False)
    subprocess.run(
        [
            "git",
            "add",
            "kb.json",
            "tools/equivalence/leaf_cache.json",
            "scripts/lift_hs_value_wrappers.py",
            "scripts/lift_hs_macro_wrappers.py",
        ],
        cwd=ROOT,
        check=False,
    )
    msg = f"lift(track-a): HS value-return wrappers + Unicorn-prove {n} (ported:true)."
    r = subprocess.run(["git", "commit", "-m", msg], cwd=ROOT, capture_output=True, text=True)
    if r.returncode != 0:
        print("commit failed", r.stdout, r.stderr, file=sys.stderr)
        return None
    sha = subprocess.run(
        ["git", "rev-parse", "HEAD"], cwd=ROOT, capture_output=True, text=True
    ).stdout.strip()
    git_push()
    print(f"COMMIT+PUSH {sha}", flush=True)
    return sha


def main() -> int:
    kb = json.loads(KB_PATH.read_text(encoding="utf-8"))
    name_by, decl_by, src_by, ported = {}, {}, {}, {}
    for o in kb.get("objects", []):
        src = o.get("source") or ""
        for fn in o.get("functions") or []:
            if not isinstance(fn, dict) or not fn.get("addr"):
                continue
            ai = int(fn["addr"], 16)
            name_by[ai] = func_name(fn) or f"FUN_{ai:08x}"
            decl_by[ai] = fn.get("decl") or ""
            src_by[ai] = src
            ported[ai] = fn.get("ported")
    by_addr, starts = load_kb(KB_PATH)
    xbe = Xbe((ROOT / "halo-patched" / "cachebeta.xbe").read_bytes())
    md = Cs(CS_ARCH_X86, CS_MODE_32)
    true0, _ = count_ported(kb)
    flips, shas, since = [], [], 0

    for i, ai in enumerate(starts):
        if ported.get(ai) is not False:
            continue
        src = src_by.get(ai) or ""
        if "hs/" not in src and "game/players" not in src:
            continue
        end = starts[i + 1] if i + 1 < len(starts) else ai + 120
        if end - ai > 120:
            continue
        sp = resolve_src(src)
        if not sp:
            continue
        name = name_by[ai]
        lines = sp.read_text(encoding="utf-8", errors="replace").splitlines()
        if not is_naked_near_def(lines, name, hex(ai)):
            continue
        try:
            raw = xbe_bytes(xbe, ai, min(end, ai + 120))
        except Exception:
            continue
        insns = []
        for insn in md.disasm(raw, ai):
            insns.append(f"{insn.mnemonic} {insn.op_str}".strip())
            if insn.mnemonic in ("ret", "retn"):
                break
        else:
            continue
        body = try_emit(insns, name, name_by, decl_by)
        if not body:
            continue
        c_src = f"/* {name} (0x{ai:x}) — readable C lift (HS value-return wrapper). */\n{body}"
        text = sp.read_text(encoding="utf-8", errors="replace")
        span = find_naked_block(text, name, ai)
        if span is None:
            print(f"skip locate {hex(ai)} {name}", flush=True)
            continue
        new_text = text[: span[0]] + c_src + "\n" + text[span[1] :]
        if ("uint16_t" in c_src or "uintptr_t" in c_src) and "#include <stdint.h>" not in new_text:
            new_text = "#include <stdint.h>\n" + new_text
        sp.write_text(new_text, encoding="utf-8")
        print(f"LIFTED {hex(ai)} {name}", flush=True)
        for stale in (ROOT / "build").rglob(sp.name + ".obj"):
            try:
                stale.unlink()
            except OSError:
                pass
        if not ensure_oracle(ai):
            sp.write_text(text, encoding="utf-8")
            print("  oracle FAIL", flush=True)
            continue
        res = run_unicorn(hex(ai), ai, 100, timeout=45.0)
        ok = clear_pass(res, 100)
        if not ok:
            res2 = run_unicorn(name, ai, 100, timeout=45.0)
            if clear_pass(res2, 100):
                res, ok = res2, True
        print(f"  ok={ok} {res.get('passed')}/{res.get('failed')}/{res.get('errors')}", flush=True)
        append_ledger(
            {
                "addr": hex(ai),
                "name": name,
                "ok": ok,
                "phase": "hs_value",
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
    summary = {"proven": len(flips), "flips": flips, "shas": shas, "true0": true0, "true1": true1}
    Path("/tmp/hs_value_summary.json").write_text(json.dumps(summary, indent=2))
    print("DONE", summary, flush=True)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
