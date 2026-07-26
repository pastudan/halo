#!/usr/bin/env python3
"""Auto-lift HS macro-eval wrappers: evaluate → optional action → hs_return(0).

Pattern (XBE):
  args = hs_macro_function_evaluate(fn, thread, init);
  if (args) { ACTION(args…); hs_return(thread, 0|eax); }
Matches prior proven readable-C style (hs_return after if) which Unicorn accepts.
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

HS_EVAL = 0xCC560
HS_RETURN = 0xCBF80
COMMIT_EVERY = 10


def kb_maps():
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


def disasm(xbe: Xbe, ai: int, end: int) -> list[tuple[str, str, int]]:
    md = Cs(CS_ARCH_X86, CS_MODE_32)
    raw = xbe_bytes(xbe, ai, min(end, ai + 128))
    out = []
    for insn in md.disasm(raw, ai):
        out.append((insn.mnemonic, insn.op_str, insn.address))
        if insn.mnemonic in ("ret", "retn"):
            break
    return out


def callee_addr(op: str) -> int | None:
    m = re.search(r"0x([0-9a-fA-F]+)", op)
    return int(m.group(1), 16) if m else None


def _param_types(decl: str) -> list[str]:
    m = re.search(r"\(([^)]*)\)", decl or "")
    if not m:
        return []
    raw = m.group(1).strip()
    if not raw or raw == "void":
        return []
    out = []
    for p in raw.split(","):
        p = re.sub(r"\s*@<\w+>", "", p)
        p = re.sub(r"\s+", " ", p).strip()
        if not p:
            continue
        # Normalize "char *name" / "char* name" / "char * name"
        p = re.sub(r"\*\s*(\w+)$", "*", p)  # drop trailing param name after *
        p = re.sub(r"\s+\w+$", "", p)  # drop trailing bare name
        p = re.sub(r"\s*\*\s*", " *", p).strip()
        out.append(p)
    return out


def _cast_args(action_addr: int, c_args: list[str], decl_by: dict) -> list[str]:
    """Cast int args to pointer types expected by callee decl."""
    decl = decl_by.get(action_addr) or ""
    pts = _param_types(decl)
    if not pts:
        return c_args
    out = []
    for i, a in enumerate(c_args):
        if i >= len(pts):
            out.append(a)
            continue
        pt = pts[i]
        if "*" in pt and "float" not in a and "args[" in a:
            # pointer param — cast int slot
            out.append(f"({pt})(uintptr_t){a}")
        else:
            out.append(a)
    return out


def parse_action(
    mid: list[tuple[str, str, int]], name_by: dict, decl_by: dict | None = None
) -> tuple[str, str] | None:
    """Return (action_c, ret_mode) where ret_mode is '0' or 'eax'."""
    decl_by = decl_by or {}
    # Find action call(s) then hs_return setup.
    # Strip trailing: push 0|eax; push esi; call hs_return; add esp, N
    if len(mid) < 4:
        return None
    # Locate hs_return call
    hr_i = None
    for i, (m, op, _) in enumerate(mid):
        if m == "call" and callee_addr(op) == HS_RETURN:
            hr_i = i
            break
    if hr_i is None or hr_i < 2:
        return None
    # push ret; push esi; call hs_return
    if mid[hr_i - 1] != ("push", "esi", mid[hr_i - 1][2]):
        # compare mnemonic/op only
        if not (mid[hr_i - 1][0] == "push" and mid[hr_i - 1][1] == "esi"):
            return None
    ret_push = mid[hr_i - 2]
    if ret_push[0] != "push":
        return None
    if ret_push[1] == "0":
        ret_mode = "0"
    elif ret_push[1] == "eax":
        ret_mode = "eax"
    else:
        return None

    body = mid[: hr_i - 2]
    # optional trailing add esp after action call is before push ret
    # body ends with call ACTION [, add esp]
    if body and body[-1][0] == "add":
        body = body[:-1]
    if not body or body[-1][0] != "call":
        return None
    action_addr = callee_addr(body[-1][1])
    if action_addr is None:
        return None
    # Prefer C identifier from decl (matches decl.h) over pretty kb name.
    action_name = None
    d = (decl_by or {}).get(action_addr) or ""
    m = re.search(r"(\w+)\s*\(", d)
    if m:
        action_name = m.group(1)
    if not action_name:
        action_name = name_by.get(action_addr)
    if not action_name:
        return None
    loads = body[:-1]

    # Parse stack pushes + loads into C args (reverse push order).
    # Represent each pushed value as a C expr string as we simulate.
    # We walk loads linearly, tracking register expressions.
    reg: dict[str, str] = {}
    push_stack: list[str] = []
    i = 0
    while i < len(loads):
        m, op, _ = loads[i]
        if m == "xor" and op in ("edx, edx", "ecx, ecx", "eax, eax"):
            dst = op.split(",")[0].strip()
            reg[dst] = "0"
            i += 1
            continue
        if m == "mov":
            # dword load from args
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
            # word into low of zero-extended reg: mov dx/cx/ax, word ptr [eax+off]
            mm = re.match(
                r"(d|c|a)x, word ptr \[eax(?: \+ (0x[0-9a-f]+|\d+))?\]", op
            )
            if mm:
                letter, off = mm.group(1), mm.group(2)
                o = int(off, 0) if off else 0
                full = {"d": "edx", "c": "ecx", "a": "eax"}[letter]
                reg[full] = f"(int16_t)(uint16_t)args[{o // 4}]" if o % 4 == 0 else None
                if o % 4 != 0:
                    # packed: treat as byte offset into args blob via char*
                    reg[full] = (
                        f"(int16_t)*(uint16_t *)((char *)args + {o})"
                    )
                i += 1
                continue
            # byte into low: mov dl/cl/al, byte ptr [eax+off]
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
            # movsx eax, word ptr [eax] / [eax+off]
            mm = re.match(
                r"(e[abcd]x), word ptr \[eax(?: \+ (0x[0-9a-f]+|\d+))?\]", op
            )
            # handled above for dx; movsx separately:
        if m == "movsx":
            mm = re.match(
                r"(e[abcd]x), word ptr \[eax(?: \+ (0x[0-9a-f]+|\d+))?\]", op
            )
            if mm:
                dst, off = mm.group(1), mm.group(2)
                o = int(off, 0) if off else 0
                if o % 4 == 0:
                    reg[dst] = f"(int16_t)(uint16_t)args[{o // 4}]"
                else:
                    reg[dst] = f"(int16_t)*(uint16_t *)((char *)args + {o})"
                i += 1
                continue
        if m == "fld":
            mm = re.match(
                r"dword ptr \[eax(?: \+ (0x[0-9a-f]+|\d+))?\]", op
            )
            if not mm:
                return None
            o = int(mm.group(1), 0) if mm.group(1) else 0
            # expect: push ecx / sub esp / fstp [esp…]
            # collect float expr; later fstp commits to stack
            reg["st0"] = (
                f"*(float *)&args[{o // 4}]"
                if o % 4 == 0
                else f"*(float *)((char *)args + {o})"
            )
            i += 1
            continue
        if m == "sub" and op.startswith("esp,"):
            # allocate stack slots for floats
            i += 1
            continue
        if m == "fstp":
            if "st0" not in reg:
                return None
            # fstp dword ptr [esp] or [esp + 4]
            mm = re.match(r"dword ptr \[esp(?: \+ (0x[0-9a-f]+|\d+))?\]", op)
            if not mm:
                return None
            # push-equivalent: place on stack at offset — simplify: append in order
            # We'll use a side list of float pushes by reconstructing at end.
            # Treat fstp [esp] as push float (after push ecx placeholder may exist)
            off = int(mm.group(1), 0) if mm.group(1) else 0
            # store into a float_slots map
            if "_float_slots" not in reg:
                reg["_float_slots"] = {}  # type: ignore
            reg["_float_slots"][off] = reg["st0"]  # type: ignore
            i += 1
            continue
        if m == "push":
            if op in ("eax", "ecx", "edx"):
                expr = reg.get(op)
                if expr:
                    push_stack.append(expr)
                    i += 1
                    continue
                # bare push ecx before fstp [esp] = float slot placeholder
                if op == "ecx" and "st0" in reg:
                    push_stack.append("__slot__")
                    i += 1
                    continue
                return None
            # immediate?
            if re.match(r"-?0x[0-9a-fA-F]+|-?\d+$", op):
                push_stack.append(op)
                i += 1
                continue
            return None
        return None

    # Merge float slots: if we have __slot__ entries and float_slots, fill them.
    slots = reg.get("_float_slots")
    if isinstance(slots, dict) and slots:
        # rebuild push_stack: typical pattern push ecx; fstp [esp]; means last push is float
        # or sub esp,8; fstp [esp+4]; fstp [esp]; push edx
        new_stack: list[str] = []
        # If float slots exist with push placeholders:
        if any(p == "__slot__" for p in push_stack):
            fi = 0
            ordered = [slots[k] for k in sorted(slots.keys())]
            for p in push_stack:
                if p == "__slot__":
                    if fi >= len(ordered):
                        return None
                    new_stack.append(ordered[fi])
                    fi += 1
                else:
                    new_stack.append(p)
            if fi != len(ordered):
                # floats stored without matching placeholders — append in offset order
                # before register pushes that follow in XBE (already in push_stack)
                return None
            push_stack = new_stack
        else:
            # sub esp form: floats were written to [esp]/ push_stack has register pushes only
            # XBE order: fstp high offs first often; then push regs. C args = regs then floats?
            # Example: fld [eax+8]; mov edx,[eax]; sub esp,8; fstp [esp+4]; fld [eax+4]; fstp [esp]; push edx
            # stack at call: [esp]=float1, [esp+4]=float2, [esp+8]=edx → F(edx, float1, float2)? 
            # cdecl: rightmost pushed first. Last push is first arg.
            # push order: (after sub/fstp) push edx → edx is first arg; floats already on stack as arg2,arg3
            ordered = [slots[k] for k in sorted(slots.keys())]
            # push_stack currently has the register pushes (first args)
            # full stack growing down: floats at low esp, then pushes
            # call sees: arg0=first push (last in push_stack reversed)... 
            # Actually after sub esp + fstp, esp points to float args; then push edx puts edx as new [esp]
            # so call args: [esp]=edx, [esp+4]=float@0, [esp+8]=float@4 → F(edx, f0, f1)
            push_stack = push_stack + ordered

    if any(p == "__slot__" for p in push_stack):
        return None

    # C args: reverse of push order
    c_args = list(reversed(push_stack))
    c_args = _cast_args(action_addr, c_args, decl_by)
    pts = _param_types(decl_by.get(action_addr) or "")
    # If kb arity disagrees with XBE pushes, call through a matching trampoline
    # typedef so we still compile (decl.h often under-specifies HS helpers).
    if pts and len(c_args) != len(pts):
        # Build a cdecl trampoline type from observed arg count (all int-sized).
        n = len(c_args)
        if n == 0:
            action = f"{action_name}();"
        else:
            params = ", ".join(["int"] * n)
            args = ", ".join(c_args)
            action = (
                f"((void (*)({params})){action_name})({args});"
            )
        return action, ret_mode
    action = f"{action_name}({', '.join(c_args)});" if c_args else f"{action_name}();"
    return action, ret_mode


def try_emit(
    insns: list[tuple[str, str, int]], name: str, name_by: dict, decl_by: dict | None = None
) -> str | None:
    if not insns or insns[-1][0] not in ("ret", "retn"):
        return None
    body = insns[:-1]
    # strip epilogue pop esi; pop ebp  (and optional mov esp,ebp)
    while body and body[-1][0] == "pop" and body[-1][1] in ("ebp", "esi", "ebx", "edi"):
        body = body[:-1]
    if body and body[-1] == ("mov", "esp, ebp", body[-1][2]) if False else (
        body[-1][0] == "mov" and body[-1][1] == "esp, ebp"
    ):
        body = body[:-1]
    # prologue
    if not (
        len(body) >= 10
        and body[0][0] == "push"
        and body[0][1] == "ebp"
        and body[1][0] == "mov"
        and body[1][1] == "ebp, esp"
    ):
        return None
    # find: push init; push thread; push fn; call hs_macro_function_evaluate
    # typical after push esi; mov esi, [ebp+0xc]
    ops = body[2:]
    # locate call HS_EVAL
    eval_i = None
    for i, (m, op, _) in enumerate(ops):
        if m == "call" and callee_addr(op) == HS_EVAL:
            eval_i = i
            break
    if eval_i is None:
        return None
    # after eval: add esp,0xc; test eax,eax; je X
    rest = ops[eval_i + 1 :]
    if not rest or rest[0][0] != "add":
        return None
    rest = rest[1:]
    if len(rest) < 2 or rest[0] != ("test", "eax, eax", rest[0][2]) and not (
        rest[0][0] == "test" and rest[0][1] == "eax, eax"
    ):
        return None
    if rest[1][0] != "je":
        return None
    mid = rest[2:]
    # mid may end with add esp before pops already stripped
    if mid and mid[-1][0] == "add":
        mid = mid[:-1]
    parsed = parse_action(mid, name_by, decl_by)
    if not parsed:
        return None
    action, ret_mode = parsed
    needs_stdint = "uintptr_t" in action or "uint16_t" in action or "uint8_t" in action
    header = "#include <stdint.h>\n" if needs_stdint else ""
    if ret_mode == "eax":
        if not action.endswith(";"):
            return None
        call_expr = action[:-1]
        return (
            f"{header}"
            f"void {name}(int16_t function_index, int thread_datum, char init)\n"
            f"{{\n"
            f"  int *args = (int *)hs_macro_function_evaluate(function_index, thread_datum, init);\n"
            f"  if (args) {{\n"
            f"    hs_return(thread_datum, (int){call_expr});\n"
            f"  }}\n"
            f"}}\n"
        )
    return (
        f"{header}"
        f"void {name}(int16_t function_index, int thread_datum, char init)\n"
        f"{{\n"
        f"  int *args = (int *)hs_macro_function_evaluate(function_index, thread_datum, init);\n"
        f"  if (args) {{\n"
        f"    {action}\n"
        f"  }}\n"
        f"  hs_return(thread_datum, 0);\n"
        f"}}\n"
    )


def commit_chunk(n: int) -> str | None:
    subprocess.run(["git", "add", "-u", "src/halo", "kb.json"], cwd=ROOT, check=False)
    subprocess.run(
        [
            "git",
            "add",
            "kb.json",
            "tools/equivalence/leaf_cache.json",
            "scripts/lift_hs_macro_wrappers.py",
        ],
        cwd=ROOT,
        check=False,
    )
    msg = f"lift(track-a): HS macro-eval wrappers + Unicorn-prove {n} (ported:true)."
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
    kb, name_by, decl_by, src_by, ported = kb_maps()
    by_addr, starts = load_kb(KB_PATH)
    xbe = Xbe((ROOT / "halo-patched" / "cachebeta.xbe").read_bytes())
    true0, _ = count_ported(kb)
    flips: list[str] = []
    shas: list[str] = []
    since = 0
    cache: dict[Path, list[str]] = {}

    for i, ai in enumerate(starts):
        if ported.get(ai) is not False:
            continue
        src = src_by.get(ai) or ""
        if "hs/" not in src and "game/players" not in src:
            continue
        end = starts[i + 1] if i + 1 < len(starts) else ai + 96
        if end - ai > 120:
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
            insns = disasm(xbe, ai, end)
        except Exception:
            continue
        # must call both helpers
        text_ins = " ".join(f"{m} {o}" for m, o, _ in insns)
        if hex(HS_EVAL) not in text_ins and "0xcc560" not in text_ins:
            continue
        if "0xcbf80" not in text_ins:
            continue
        body = try_emit(insns, name, name_by, decl_by)
        if not body:
            print(f"PARSE-FAIL {hex(ai)} {name}", flush=True)
            continue
        # strip leading include from body; apply once at file level if needed
        file_include = ""
        if body.startswith("#include <stdint.h>\n"):
            body = body[len("#include <stdint.h>\n") :]
            file_include = "#include <stdint.h>\n"
        c_src = f"/* {name} (0x{ai:x}) — readable C lift (HS macro-eval wrapper). */\n{body}"
        text = sp.read_text(encoding="utf-8", errors="replace")
        span = find_naked_block(text, name, ai)
        if span is None:
            print(f"skip locate {hex(ai)} {name}", flush=True)
            continue
        new_text = text[: span[0]] + c_src + "\n" + text[span[1] :]
        if file_include and "#include <stdint.h>" not in new_text:
            new_text = file_include + new_text
        elif ("uint16_t" in c_src or "uint8_t" in c_src or "uintptr_t" in c_src) and (
            "#include <stdint.h>" not in new_text
        ):
            new_text = "#include <stdint.h>\n" + new_text
        sp.write_text(new_text, encoding="utf-8")
        cache[sp] = new_text.splitlines()
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
        res = run_unicorn(name, ai, 100, timeout=45.0)
        ok = clear_pass(res, 100)
        if not ok:
            res2 = run_unicorn(hex(ai), ai, 100, timeout=45.0)
            if clear_pass(res2, 100):
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
                "phase": "hs_macro",
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
        # keep cdecl decl
        decl = f"void {name}(int16_t function_index, int thread_datum, char init);"
        for o in kb["objects"]:
            for fn in o.get("functions") or []:
                if isinstance(fn, dict) and fn.get("addr") and int(fn["addr"], 16) == ai:
                    fn["decl"] = decl
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
    Path("/tmp/hs_macro_summary.json").write_text(json.dumps(summary, indent=2))
    print("DONE", summary, flush=True)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
