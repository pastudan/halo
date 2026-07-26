#!/usr/bin/env python3
"""Generate draft C for players.obj HS macro wrappers from XBE patterns."""
from __future__ import annotations

import json
import re
from pathlib import Path

from capstone import CS_ARCH_X86, CS_MODE_32, Cs
from xbe import Xbe

ROOT = Path(__file__).resolve().parents[1]
ALREADY = {
    "0xbdf40",
    "0xbdf80",
    "0xbdfa0",
    "0xbe0d0",
    "0xbe110",
    "0xbe150",
    "0xbe190",
    "0xbe1d0",
    "0xbe210",
    "0xbe250",
}


def main() -> None:
    xbe = Xbe.from_file(str(ROOT / "halo-patched/cachebeta.xbe"))
    md = Cs(CS_ARCH_X86, CS_MODE_32)
    kb = json.loads((ROOT / "kb.json").read_text())

    addr_name = {}
    for o in kb["objects"]:
        for f in o.get("functions", []):
            d = f.get("decl") or ""
            m = re.search(r"([A-Za-z_][A-Za-z0-9_]*)\s*\(", d)
            if m:
                addr_name[int(f["addr"], 16)] = m.group(1)

    fns = [
        f
        for o in kb["objects"]
        if o.get("name") == "players.obj"
        for f in o["functions"]
    ]
    fns = sorted(fns, key=lambda f: int(f["addr"], 16))
    addrs = [(int(f["addr"], 16), f) for f in fns]

    def get_bytes(va: int, end: int) -> bytes:
        for sec in xbe.sections.values():
            s = sec.header.virtual_addr
            if s <= va < s + sec.header.virtual_size:
                return bytes(sec.data[va - s : end - s])
        raise RuntimeError(hex(va))

    generated = []
    callee_decls = {}

    for i, (a, f) in enumerate(addrs):
        if f.get("ported") is not None:
            continue
        ah = f["addr"]
        if ah in ALREADY:
            continue
        end = addrs[i + 1][0] if i + 1 < len(addrs) else a + 0x40
        if end - a > 128:
            continue
        data = get_bytes(a, end)
        insns = list(md.disasm(data, a))
        call_targets = [
            int(insn.op_str, 16)
            for insn in insns
            if insn.mnemonic == "call" and insn.op_str.startswith("0x")
        ]
        if 0xCC560 not in call_targets or 0xCBF80 not in call_targets:
            continue
        mids = [c for c in call_targets if c not in (0xCC560, 0xCBF80)]
        if len(mids) != 1:
            continue
        mid = mids[0]

        saw_eval = False
        pushes_before_mid = 0
        for insn in insns:
            if insn.mnemonic == "call" and insn.op_str == hex(0xCC560):
                saw_eval = True
                continue
            if not saw_eval:
                continue
            if insn.mnemonic == "call" and insn.op_str == hex(mid):
                break
            if insn.mnemonic == "push":
                pushes_before_mid += 1

        before_ret = []
        for idx, insn in enumerate(insns):
            if insn.mnemonic == "call" and insn.op_str == hex(0xCBF80):
                j = idx - 1
                while j >= 0 and insns[j].mnemonic in ("push", "mov"):
                    if insns[j].mnemonic == "push":
                        before_ret.append(insns[j].op_str)
                    j -= 1
                break
        ret_zero = ("0" in before_ret) or ("0x0" in before_ret)

        nargs = pushes_before_mid
        if nargs > 3:
            continue

        loads = []
        saw_eval = False
        for insn in insns:
            if insn.mnemonic == "call" and insn.op_str == hex(0xCC560):
                saw_eval = True
                continue
            if not saw_eval:
                continue
            if insn.mnemonic == "call" and insn.op_str == hex(mid):
                break
            op = insn.op_str
            if insn.mnemonic == "mov":
                m = re.search(
                    r"dword ptr \[eax(?: \+ (0x[0-9a-f]+))?\]", op
                )
                if m and op.split(",")[0].strip() in (
                    "eax",
                    "ecx",
                    "edx",
                    "ebx",
                    "esi",
                    "edi",
                ):
                    off = int(m.group(1), 16) if m.group(1) else 0
                    loads.append(("dword", off))
                    continue
                m = re.search(
                    r"dx, word ptr \[eax(?: \+ (0x[0-9a-f]+))?\]", op
                )
                if m:
                    off = int(m.group(1), 16) if m.group(1) else 0
                    loads.append(("word", off))
                    continue
            if insn.mnemonic == "movsx" and "word ptr [eax" in op:
                m = re.search(
                    r"word ptr \[eax(?: \+ (0x[0-9a-f]+))?\]", op
                )
                off = int(m.group(1), 16) if m and m.group(1) else 0
                loads.append(("sword", off))

        if nargs > 0 and len(loads) != nargs:
            if not loads:
                loads = [("dword", 4 * i) for i in range(nargs)]
            else:
                continue

        mid_name = addr_name.get(mid, f"FUN_{mid:08x}")
        if mid not in callee_decls:
            if nargs == 0:
                callee_decls[mid] = (
                    f"void {mid_name}(void);"
                    if ret_zero
                    else f"int {mid_name}(void);"
                )
            else:
                params = ", ".join(f"int a{i}" for i in range(nargs))
                callee_decls[mid] = (
                    f"void {mid_name}({params});"
                    if ret_zero
                    else f"int {mid_name}({params});"
                )

        wname = re.search(
            r"([A-Za-z_][A-Za-z0-9_]*)\s*\(",
            f.get("decl", "void FUN(void);"),
        ).group(1)

        lines = [
            f"void {wname}(int16_t function_index, int thread_datum, char init)",
            "{",
        ]
        if nargs == 0:
            lines += [
                "  (void)function_index;",
                "  (void)init;",
            ]
            if ret_zero:
                lines += [
                    f"  {mid_name}();",
                    "  hs_return(thread_datum, 0);",
                ]
            else:
                lines.append(f"  hs_return(thread_datum, {mid_name}());")
        else:
            lines += [
                "  char *args;",
                "  args = (char *)hs_macro_function_evaluate("
                "function_index, thread_datum, init);",
                "  if (args) {",
            ]
            call_args = []
            for t, off in loads:
                if t == "dword":
                    call_args.append(f"*(int *)(args + {off})")
                elif t == "word":
                    call_args.append(f"(int)*(uint16_t *)(args + {off})")
                else:
                    call_args.append(f"(int)*(int16_t *)(args + {off})")
            joined = ", ".join(call_args)
            if ret_zero:
                lines += [
                    f"    {mid_name}({joined});",
                    "    hs_return(thread_datum, 0);",
                ]
            else:
                lines.append(
                    f"    hs_return(thread_datum, {mid_name}({joined}));"
                )
            lines.append("  }")
        lines.append("}")
        generated.append((ah, wname, "\n".join(lines)))

    out = ROOT / "artifacts/players_hs_wrappers_gen.c"
    out.write_text("\n\n".join(g[2] for g in generated) + "\n")
    print(f"generated {len(generated)} wrappers -> {out}")

    text = (ROOT / "kb.json").read_text()
    for ah, wname, _ in generated:
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

    for mid, decl in callee_decls.items():
        ah = hex(mid)
        m = re.search(
            r'\{\s*"addr":\s*"%s",\s*"decl":\s*"[^"]*"'
            r'(?:,\s*"ported":\s*(?:true|false))?\s*\}' % ah,
            text,
        )
        if not m:
            print("miss callee", ah, decl)
            continue
        if '"ported"' in m.group(0):
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
    for ah, wname, _ in generated:
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
