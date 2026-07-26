#!/usr/bin/env python3
"""Second-pass HS wrapper generator: no-eval stubs + remaining evaluate wrappers."""
from __future__ import annotations

import json
import re
from collections import Counter
from pathlib import Path

from capstone import CS_ARCH_X86, CS_MODE_32, Cs
from xbe import Xbe

ROOT = Path(__file__).resolve().parents[1]


def main() -> None:
    xbe = Xbe.from_file(str(ROOT / "halo-patched/cachebeta.xbe"))
    md = Cs(CS_ARCH_X86, CS_MODE_32)
    kb = json.loads((ROOT / "kb.json").read_text())

    addr_name = {}
    for o in kb["objects"]:
        for f in o.get("functions", []):
            m = re.search(r"([A-Za-z_][A-Za-z0-9_]*)\s*\(", f.get("decl") or "")
            if m:
                addr_name[int(f["addr"], 16)] = m.group(1)

    fns = sorted(
        [
            f
            for o in kb["objects"]
            if o.get("name") == "players.obj"
            for f in o["functions"]
        ],
        key=lambda f: int(f["addr"], 16),
    )
    addrs = [(int(f["addr"], 16), f) for f in fns]

    def get_bytes(va: int, end: int) -> bytes:
        for sec in xbe.sections.values():
            s = sec.header.virtual_addr
            if s <= va < s + sec.header.virtual_size:
                return bytes(sec.data[va - s : end - s])
        raise RuntimeError(hex(va))

    gen = []
    callee_fix = {}

    for i, (a, f) in enumerate(addrs):
        if f.get("ported") is not None:
            continue
        ah = f["addr"]
        end = addrs[i + 1][0] if i + 1 < len(addrs) else a + 0x40
        if end - a > 128:
            continue
        data = get_bytes(a, end)
        insns = list(md.disasm(data, a))
        calls = [
            int(insn.op_str, 16)
            for insn in insns
            if insn.mnemonic == "call" and insn.op_str.startswith("0x")
        ]
        wname = re.search(
            r"([A-Za-z_][A-Za-z0-9_]*)\s*\(",
            f.get("decl", "void FUN(void);"),
        ).group(1)

        # no-eval: mid + hs_return
        if 0xCBF80 in calls and 0xCC560 not in calls and len(calls) == 2:
            mid = [c for c in calls if c != 0xCBF80][0]
            mid_name = addr_name.get(mid, f"FUN_{mid:08x}")
            ret_zero = False
            for idx, insn in enumerate(insns):
                if insn.mnemonic == "call" and insn.op_str == hex(0xCBF80):
                    for j in range(idx - 1, max(-1, idx - 5), -1):
                        if insns[j].mnemonic == "push" and insns[j].op_str in (
                            "0",
                            "0x0",
                        ):
                            ret_zero = True
                    break
            if ret_zero:
                body = (
                    f"void {wname}(int16_t function_index, int thread_datum, char init)\n"
                    "{\n"
                    "  (void)function_index;\n"
                    "  (void)init;\n"
                    f"  {mid_name}();\n"
                    "  hs_return(thread_datum, 0);\n"
                    "}"
                )
                callee_fix[mid] = f"void {mid_name}(void);"
            else:
                body = (
                    f"void {wname}(int16_t function_index, int thread_datum, char init)\n"
                    "{\n"
                    "  (void)function_index;\n"
                    "  (void)init;\n"
                    f"  hs_return(thread_datum, {mid_name}());\n"
                    "}"
                )
                callee_fix[mid] = f"int {mid_name}(void);"
            gen.append((ah, wname, body, "noeval"))
            continue

        if 0xCC560 not in calls or 0xCBF80 not in calls:
            continue
        mids = [c for c in calls if c not in (0xCC560, 0xCBF80)]
        if len(mids) != 1:
            continue
        mid = mids[0]
        mid_name = addr_name.get(mid, f"FUN_{mid:08x}")
        has_fld = any(insn.mnemonic.startswith("fld") for insn in insns)

        if has_fld:
            saw = False
            has_int0 = False
            float_offs = []
            for insn in insns:
                if insn.mnemonic == "call" and insn.op_str == hex(0xCC560):
                    saw = True
                    continue
                if not saw:
                    continue
                if insn.mnemonic == "call" and insn.op_str == hex(mid):
                    break
                if insn.mnemonic == "mov" and re.search(
                    r"dword ptr \[eax\]$", insn.op_str
                ):
                    has_int0 = True
                if insn.mnemonic == "fld":
                    m = re.search(
                        r"dword ptr \[eax \+ (0x[0-9a-f]+)\]", insn.op_str
                    )
                    if m:
                        float_offs.append(int(m.group(1), 16))
            float_offs = sorted(set(float_offs))
            if has_int0 and float_offs == [4, 8]:
                callee_fix[mid] = (
                    f"void {mid_name}(int a0, float a1, float a2);"
                )
                body = (
                    f"void {wname}(int16_t function_index, int thread_datum, char init)\n"
                    "{\n"
                    "  char *args;\n"
                    "  args = (char *)hs_macro_function_evaluate("
                    "function_index, thread_datum, init);\n"
                    "  if (args) {\n"
                    f"    {mid_name}(*(int *)args, *(float *)(args + 4), "
                    "*(float *)(args + 8));\n"
                    "    hs_return(thread_datum, 0);\n"
                    "  }\n"
                    "}"
                )
                gen.append((ah, wname, body, "float"))
            continue

        saw = False
        pushes = 0
        loads = []
        for insn in insns:
            if insn.mnemonic == "call" and insn.op_str == hex(0xCC560):
                saw = True
                continue
            if not saw:
                continue
            if insn.mnemonic == "call" and insn.op_str == hex(mid):
                break
            if insn.mnemonic == "push":
                pushes += 1
            if insn.mnemonic == "mov":
                m = re.search(
                    r"dword ptr \[eax(?: \+ ((?:0x)?[0-9a-f]+))?\]",
                    insn.op_str,
                )
                if m and insn.op_str.split(",")[0].strip() in (
                    "eax",
                    "ecx",
                    "edx",
                    "ebx",
                    "esi",
                    "edi",
                ):
                    off = int(m.group(1), 0) if m.group(1) else 0
                    loads.append(("dword", off))
                    continue
                m = re.search(
                    r"dx, word ptr \[eax(?: \+ ((?:0x)?[0-9a-f]+))?\]",
                    insn.op_str,
                )
                if m:
                    off = int(m.group(1), 0) if m.group(1) else 0
                    loads.append(("word", off))
            if insn.mnemonic == "movsx" and "word ptr [eax" in insn.op_str:
                m = re.search(
                    r"word ptr \[eax(?: \+ ((?:0x)?[0-9a-f]+))?\]",
                    insn.op_str,
                )
                off = int(m.group(1), 0) if m and m.group(1) else 0
                loads.append(("sword", off))

        if pushes > 3:
            continue
        if pushes > 0 and len(loads) != pushes:
            if not loads:
                loads = [("dword", 4 * i) for i in range(pushes)]
            else:
                continue

        ret_zero = any(
            insn.mnemonic == "push" and insn.op_str in ("0", "0x0")
            for insn in insns
        )

        if pushes == 0:
            body = (
                f"void {wname}(int16_t function_index, int thread_datum, char init)\n"
                "{\n"
                "  if (hs_macro_function_evaluate(function_index, thread_datum, init)) {\n"
                f"    hs_return(thread_datum, {mid_name}());\n"
                "  }\n"
                "}"
            )
            if ret_zero:
                body = (
                    f"void {wname}(int16_t function_index, int thread_datum, char init)\n"
                    "{\n"
                    "  (void)function_index;\n"
                    "  (void)init;\n"
                    f"  {mid_name}();\n"
                    "  hs_return(thread_datum, 0);\n"
                    "}"
                )
                callee_fix[mid] = f"void {mid_name}(void);"
            else:
                callee_fix[mid] = f"int {mid_name}(void);"
        else:
            exprs = []
            for t, off in loads:
                if t == "dword":
                    exprs.append(f"*(int *)(args + {off})")
                elif t == "word":
                    exprs.append(f"(int)*(uint16_t *)(args + {off})")
                else:
                    exprs.append(f"(int)*(int16_t *)(args + {off})")
            joined = ", ".join(exprs)
            params = ", ".join(f"int a{i}" for i in range(len(exprs)))
            if ret_zero:
                callee_fix[mid] = f"void {mid_name}({params});"
                call = (
                    f"    {mid_name}({joined});\n"
                    "    hs_return(thread_datum, 0);"
                )
            else:
                callee_fix[mid] = f"int {mid_name}({params});"
                call = f"    hs_return(thread_datum, {mid_name}({joined}));"
            body = (
                f"void {wname}(int16_t function_index, int thread_datum, char init)\n"
                "{\n"
                "  char *args;\n"
                "  args = (char *)hs_macro_function_evaluate("
                "function_index, thread_datum, init);\n"
                "  if (args) {\n"
                f"{call}\n"
                "  }\n"
                "}"
            )
        gen.append((ah, wname, body, "eval"))

    out = ROOT / "artifacts/players_hs_wrappers_gen2.c"
    out.write_text("\n\n".join(g[2] for g in gen) + "\n")
    print(
        "generated",
        len(gen),
        Counter(g[3] for g in gen),
        "->",
        out,
    )

    text = (ROOT / "kb.json").read_text()
    for ah, wname, _, _ in gen:
        decl = (
            f"void {wname}(int16_t function_index, int thread_datum, char init);"
        )
        m = re.search(
            r'\{\s*"addr":\s*"%s",\s*"decl":\s*"[^"]*"'
            r'(?:,\s*"ported":\s*(?:true|false))?\s*\}' % ah,
            text,
        )
        if not m:
            print("miss wrapper", ah)
            continue
        new = (
            "{\n"
            f'          "addr": "{ah}",\n'
            f'          "decl": "{decl}",\n'
            '          "ported": false\n'
            "        }"
        )
        text = text[: m.start()] + new + text[m.end() :]

    for mid, decl in callee_fix.items():
        ah = hex(mid)
        m = re.search(
            r'\{\s*"addr":\s*"%s",\s*"decl":\s*"[^"]*"'
            r'(?:,\s*"name":\s*"[^"]*")?'
            r'(?:,\s*"ported":\s*(?:true|false))?\s*\}' % ah,
            text,
        )
        if not m:
            print("miss callee", ah, decl)
            continue
        block = m.group(0)
        if "ported" in block:
            continue
        if "void);" not in block and block.count(",") > 0:
            continue
        new = (
            "{\n"
            f'          "addr": "{ah}",\n'
            f'          "decl": "{decl}"\n'
            "        }"
        )
        text = text[: m.start()] + new + text[m.end() :]

    (ROOT / "kb.json").write_text(text)
    json.loads(text)

    al_path = ROOT / "tools/audit/deactivation_allowlist.json"
    al = json.loads(al_path.read_text())
    have = {e["addr"] for e in al if isinstance(e, dict)}
    for ah, wname, _, _ in gen:
        if ah in have:
            continue
        al.append(
            {
                "addr": ah,
                "name": wname,
                "object": "players.obj",
                "reason": "draft lift pending VC71/equivalence — keep inactive until scored",
                "since": "2026-07-25",
            }
        )
    al_path.write_text(json.dumps(al, indent=2) + "\n")
    print("kb+allowlist updated")


if __name__ == "__main__":
    main()
