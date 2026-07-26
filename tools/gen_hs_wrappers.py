#!/usr/bin/env python3
"""Generate draft C for hs.obj HS macro / return wrappers from XBE patterns."""
from __future__ import annotations

import json
import re
from collections import Counter
from pathlib import Path

from capstone import CS_ARCH_X86, CS_MODE_32, Cs
from xbe import Xbe

ROOT = Path(__file__).resolve().parents[1]
OBJECT = "hs.obj"


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
            if o.get("name") == OBJECT
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
    callee = {}
    kinds = Counter()

    for i, (a, f) in enumerate(addrs):
        if f.get("ported") is not None:
            continue
        end = addrs[i + 1][0] if i + 1 < len(addrs) else a + 0x80
        if end - a > 160:
            continue
        data = get_bytes(a, end)
        insns = list(md.disasm(data, a))
        calls = [
            int(x.op_str, 16)
            for x in insns
            if x.mnemonic == "call" and x.op_str.startswith("0x")
        ]
        wname = re.search(
            r"([A-Za-z_][A-Za-z0-9_]*)\s*\(",
            f.get("decl", "void FUN(void);"),
        ).group(1)
        ah = f["addr"]

        # no-eval: mid + hs_return
        if 0xCBF80 in calls and 0xCC560 not in calls and len(calls) == 2:
            mid = [c for c in calls if c != 0xCBF80][0]
            mid_name = addr_name.get(mid, f"FUN_{mid:08x}")
            ret_zero = any(
                x.mnemonic == "push" and x.op_str in ("0", "0x0") for x in insns
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
                callee[mid] = f"void {mid_name}(void);"
            else:
                body = (
                    f"void {wname}(int16_t function_index, int thread_datum, char init)\n"
                    "{\n"
                    "  (void)function_index;\n"
                    "  (void)init;\n"
                    f"  hs_return(thread_datum, {mid_name}());\n"
                    "}"
                )
                callee[mid] = f"int {mid_name}(void);"
            gen.append((ah, wname, body))
            kinds["noeval"] += 1
            continue

        if 0xCC560 not in calls or 0xCBF80 not in calls:
            continue
        mids = [c for c in calls if c not in (0xCC560, 0xCBF80)]
        if len(mids) != 1:
            continue
        mid = mids[0]
        mid_name = addr_name.get(mid, f"FUN_{mid:08x}")
        ret_zero = any(
            x.mnemonic == "push" and x.op_str in ("0", "0x0") for x in insns
        )

        saw = False
        refs = []
        for x in insns:
            if x.mnemonic == "call" and x.op_str == hex(0xCC560):
                saw = True
                continue
            if not saw:
                continue
            if x.mnemonic == "call" and x.op_str == hex(mid):
                break
            m = re.search(
                r"(dword|word|byte) ptr \[eax(?: \+ ((?:0x)?[0-9a-f]+))?\]",
                x.op_str,
            )
            if m and x.mnemonic in ("mov", "movsx", "movzx", "fld", "fild"):
                off = int(m.group(2), 0) if m.group(2) else 0
                if x.mnemonic == "fld":
                    kind = "float"
                elif x.mnemonic == "movsx":
                    kind = "sword"
                elif m.group(1) == "byte":
                    kind = "byte"
                elif m.group(1) == "word":
                    kind = "word"
                else:
                    kind = "dword"
                refs.append((kind, off))

        byoff = {}
        for kind, off in refs:
            prev = byoff.get(off)
            if prev is None or kind == "float":
                byoff[off] = kind
        offs = sorted(byoff)

        exprs = []
        params = []
        for j, o in enumerate(offs):
            kind = byoff[o]
            if kind == "float":
                exprs.append(f"*(float *)(args + {o})")
                params.append(f"float a{j}")
            elif kind == "byte":
                exprs.append(f"(int)*(uint8_t *)(args + {o})")
                params.append(f"int a{j}")
            elif kind == "word":
                exprs.append(f"(int)*(uint16_t *)(args + {o})")
                params.append(f"int a{j}")
            elif kind == "sword":
                exprs.append(f"(int)*(int16_t *)(args + {o})")
                params.append(f"int a{j}")
            else:
                exprs.append(f"*(int *)(args + {o})")
                params.append(f"int a{j}")

        if not exprs:
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
                callee[mid] = f"void {mid_name}(void);"
            else:
                body = (
                    f"void {wname}(int16_t function_index, int thread_datum, char init)\n"
                    "{\n"
                    "  if (hs_macro_function_evaluate(function_index, thread_datum, init))\n"
                    f"    hs_return(thread_datum, {mid_name}());\n"
                    "}"
                )
                callee[mid] = f"int {mid_name}(void);"
        else:
            joined = ", ".join(exprs)
            pjoined = ", ".join(params)
            if ret_zero:
                callee[mid] = f"void {mid_name}({pjoined});"
                call = (
                    f"    {mid_name}({joined});\n"
                    "    hs_return(thread_datum, 0);"
                )
            else:
                callee[mid] = f"int {mid_name}({pjoined});"
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
        gen.append((ah, wname, body))
        kinds["eval"] += 1

    out = ROOT / "artifacts/hs_wrappers_gen.c"
    out.write_text("\n\n".join(g[2] for g in gen) + "\n")
    print("generated", len(gen), kinds, "->", out)

    text = (ROOT / "kb.json").read_text()
    for ah, wname, _ in gen:
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

    for mid, decl in callee.items():
        ah = hex(mid)
        m = re.search(
            r'\{\s*"addr":\s*"%s",\s*"decl":\s*"[^"]*"'
            r'(?:,\s*"name":\s*"[^"]*")?'
            r'(?:,\s*"ported":\s*(?:true|false))?\s*\}' % ah,
            text,
        )
        if not m or "ported" in m.group(0):
            continue
        # only replace trivial void decls
        if "void);" not in m.group(0) and m.group(0).count(",") > 0:
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
    for ah, wname, _ in gen:
        if ah in have:
            continue
        al.append(
            {
                "addr": ah,
                "name": wname,
                "object": OBJECT,
                "reason": "draft lift pending VC71/equivalence — keep inactive until scored",
                "since": "2026-07-25",
            }
        )
    al_path.write_text(json.dumps(al, indent=2) + "\n")
    print("kb+allowlist updated")


if __name__ == "__main__":
    main()
