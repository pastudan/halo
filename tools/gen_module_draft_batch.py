#!/usr/bin/env python3
"""Generate draft batch impl + disasm for any kb object module."""
from __future__ import annotations

import argparse
import json
import re
from pathlib import Path

from capstone import CS_ARCH_X86, CS_MODE_32, Cs
from xbe import Xbe

ROOT = Path(__file__).resolve().parents[1]


def slug(name: str) -> str:
    return re.sub(r"[^a-z0-9]+", "_", name.replace(".obj", "").lower()).strip("_")


def strip_c_comments(s: str) -> str:
    return re.sub(r"/\*.*?\*/", "", s, flags=re.DOTALL)


def sanitize_decl_for_c(decl: str) -> str:
    decl = strip_c_comments(decl)
    return re.sub(r"\s*@<[^>]+>", "", decl)


def clean_param_name(name: str) -> str:
    name = strip_c_comments(name)
    name = re.sub(r"@<[^>]+>", "", name).strip()
    if not name or not re.match(r"^[A-Za-z_]", name):
        return "unused_arg"
    return name


def fn_name(decl: str, addr: str) -> str:
    m = re.search(r"([A-Za-z_][A-Za-z0-9_]*)\s*\(", decl or "")
    if m:
        return m.group(1)
    return f"FUN_{int(addr, 16):08x}"


def existing_fn_names(src_text: str) -> set[str]:
    return set(
        re.findall(
            r"^(?:static\s+)?(?:inline\s+)?(?:[\w\s*]+?\s+)([A-Za-z_][A-Za-z0-9_]*)\s*\(",
            src_text,
            re.M,
        )
    )


def load_decls(object_name: str, *, skip_existing: bool = False) -> dict[str, str]:
    kb = json.loads((ROOT / "kb.json").read_text())
    obj = next(o for o in kb["objects"] if o["name"] == object_name)
    existing: set[str] = set()
    if skip_existing:
        src_rel = obj.get("source")
        if src_rel:
            src_path = ROOT / "src" / "halo" / src_rel
            if src_path.is_file():
                existing = existing_fn_names(src_path.read_text())
    decls: dict[str, str] = {}
    for f in obj["functions"]:
        if f.get("ported") is not None:
            continue
        addr = f["addr"].lower()
        decl = (f.get("decl") or f"void {fn_name('', addr)}(void);").strip()
        if not decl.endswith(";"):
            decl += ";"
        name = fn_name(decl, addr)
        if name in existing:
            continue
        decls[addr] = decl
    return decls


def parse_params(decl: str) -> list[str]:
    m = re.search(r"\(([^)]*)\)", decl)
    if not m:
        return []
    params = m.group(1).strip()
    if not params or params == "void":
        return []
    out: list[str] = []
    depth = 0
    cur: list[str] = []
    for ch in params:
        if ch == "(":
            depth += 1
        elif ch == ")":
            depth -= 1
        elif ch == "," and depth == 0:
            out.append("".join(cur).strip())
            cur = []
            continue
        cur.append(ch)
    if cur:
        out.append("".join(cur).strip())
    names: list[str] = []
    for p in out:
        p = re.sub(r"\[[^\]]*\]", "", p).strip()
        tok = re.split(r"\s+", p.replace("*", " ").strip())
        if tok:
            names.append(clean_param_name(tok[-1]))
    return names


def ret_kind(decl: str) -> str:
    head = decl.split("(", 1)[0].strip()
    if head.startswith("void ") and "*" not in head:
        return "void"
    if "*" in head:
        return "ptr"
    if re.search(r"\bchar\b", head):
        return "char"
    if re.search(r"\b(int|short|long|bool|float|double|wchar_t|size_t|uint|int64_t|int32_t|int16_t)\b", head):
        return "scalar"
    return "void"


def gen_stub_body(decl: str) -> str:
    c_decl = sanitize_decl_for_c(decl)
    params = parse_params(c_decl)
    lines = [f"  (void){p};" for p in params]
    kind = ret_kind(c_decl)
    if kind == "ptr":
        lines.append("  return NULL;")
    elif kind == "char":
        lines.append("  return 0;")
    elif kind == "scalar":
        lines.append("  return 0;")
    inner = "\n".join(lines)
    return f"{c_decl.split(';')[0]}\n{{\n{inner}\n}}\n"


def write_disasm(object_name: str, decls: dict[str, str], out: Path) -> None:
    xbe = Xbe.from_file(str(ROOT / "halo-patched/cachebeta.xbe"))
    md = Cs(CS_ARCH_X86, CS_MODE_32)
    kb = json.loads((ROOT / "kb.json").read_text())
    obj = next(o for o in kb["objects"] if o["name"] == object_name)
    fns = sorted(obj["functions"], key=lambda f: int(f["addr"], 16))
    addrs = [(int(f["addr"], 16), f) for f in fns]

    def get_bytes(va: int, end: int) -> bytes:
        for sec in xbe.sections.values():
            s = sec.header.virtual_addr
            if s <= va < s + sec.header.virtual_size:
                return bytes(sec.data[va - s : end - s])
        raise RuntimeError(hex(va))

    lines: list[str] = []
    for i, (va, f) in enumerate(addrs):
        if f.get("ported") is not None:
            continue
        end = addrs[i + 1][0] if i + 1 < len(addrs) else va + 0x200
        data = get_bytes(va, min(end, va + 0x2000))
        insns = list(md.disasm(data, va))
        addr = f["addr"].lower()
        label = fn_name(decls.get(addr, ""), addr)
        lines.append(f"\n=== {label} @ {f['addr']} end~{end:08x} ===")
        for ins in insns[:120]:
            if ins.address >= end:
                break
            lines.append(f"  {ins.address:08x}: {ins.mnemonic:<8} {ins.op_str}")
    out.parent.mkdir(parents=True, exist_ok=True)
    out.write_text("\n".join(lines) + "\n")
    print(f"wrote {out} ({len(lines)} lines)")


def main() -> None:
    ap = argparse.ArgumentParser()
    ap.add_argument("--object", required=True)
    args = ap.parse_args()
    object_name = args.object
    s = slug(object_name)
    decls = load_decls(object_name, skip_existing=True)
    if not decls:
        raise SystemExit(f"no unset symbols in {object_name}")

    disasm_out = ROOT / "artifacts" / f"{s}_batch_disasm.txt"
    impl_out = ROOT / "tools" / f"{s}_batch_impl.c"
    frag_out = ROOT / "tools" / f"{s}_batch_fragment.c"

    write_disasm(object_name, decls, disasm_out)
    parts = [f"/* --- {object_name} batch drafts (2026-07-26) --- */\n"]
    for addr in sorted(decls.keys(), key=lambda x: int(x, 16)):
        parts.append(f"/* {addr} */\n{gen_stub_body(decls[addr])}")
    text = "\n".join(parts)
    impl_out.write_text(text)
    frag_out.write_text(text)
    print(f"wrote {impl_out} ({len(decls)} drafts)")


if __name__ == "__main__":
    main()
