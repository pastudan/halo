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
    decl = re.sub(r"\s*@<[^>]+>", "", decl)
    decl = re.sub(r"@\d+", "", decl)
    decl = re.sub(r"FID_conflict:", "", decl)
    decl = re.sub(r"\b__stdcall\b", "", decl)
    decl = re.sub(r"\b__cdecl\b", "", decl)
    decl = re.sub(r"\s+", " ", decl).strip()
    return decl


def clean_param_name(name: str) -> str:
    name = strip_c_comments(name)
    name = re.sub(r"@<[^>]+>", "", name).strip()
    if not name or not re.match(r"^[A-Za-z_]", name):
        return "unused_arg"
    return name


def fn_name(decl: str, addr: str) -> str:
    raw = strip_c_comments(decl or "")
    if "??" in raw or re.search(r"@[0-9A-Za-z_]*\s*\(", raw):
        return f"FUN_{int(addr, 16):08x}"
    m = re.search(r"([A-Za-z_][A-Za-z0-9_]*)\s*\(", raw)
    if m:
        return m.group(1)
    return f"FUN_{int(addr, 16):08x}"


FN_SIG_HEAD = (
    r"(?m)^(?!\s)"
    r"(?:static\s+)?(?:inline\s+)?"
    r"(?:__declspec\s*\([^)]*\)\s+)?"
    r"(?:(?:[\w\s*]+?(?:\*|\s+)|[\w\s]+\*\s*))"
    r"(?:__stdcall\s+|__cdecl\s+|__fastcall\s+)?"
)


def scan_balanced(text: str, start: int, open_ch: str, close_ch: str) -> int | None:
    if start >= len(text) or text[start] != open_ch:
        return None
    depth = 0
    for i in range(start, len(text)):
        ch = text[i]
        if ch == open_ch:
            depth += 1
        elif ch == close_ch:
            depth -= 1
            if depth == 0:
                return i
    return None


C_KEYWORDS = {
    "if",
    "for",
    "while",
    "switch",
    "return",
    "sizeof",
    "do",
    "else",
    "case",
    "default",
    "break",
    "continue",
    "goto",
}


def iter_fn_defs(text: str):
    """Yield (name, sig_start, body_start, body_end) for each top-level C function."""
    text = strip_c_comments(text)
    for m in re.finditer(FN_SIG_HEAD + r"([A-Za-z_][A-Za-z0-9_]*)\s*\(", text):
        name = m.group(1)
        if name in C_KEYWORDS:
            continue
        paren_open = m.end() - 1
        paren_close = scan_balanced(text, paren_open, "(", ")")
        if paren_close is None:
            continue
        i = paren_close + 1
        while i < len(text) and text[i].isspace():
            i += 1
        if i >= len(text) or text[i] != "{":
            continue
        body_start = i + 1
        body_end = scan_balanced(text, i, "{", "}")
        if body_end is None:
            continue
        yield name, m.start(), body_start, body_end


def existing_fn_names(src_text: str) -> set[str]:
    return {name for name, _, _, _ in iter_fn_defs(src_text)}


def find_function_def(src: str, name: str) -> tuple[int, int, int] | None:
    for fn, sig_start, body_start, body_end in iter_fn_defs(src):
        if fn == name:
            return sig_start, body_start, body_end
    return None


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


TYPE_KEYWORDS = {
    "void",
    "char",
    "short",
    "int",
    "long",
    "float",
    "double",
    "bool",
    "signed",
    "unsigned",
    "const",
    "struct",
    "enum",
    "union",
    "static",
    "register",
    "volatile",
    "size_t",
    "uint",
    "int64_t",
    "int32_t",
    "int16_t",
    "uint32_t",
    "uint16_t",
    "uint8_t",
    "wchar_t",
}


def param_list_span(decl: str) -> tuple[int, int] | None:
    start = decl.find("(")
    if start < 0:
        return None
    depth = 0
    for i in range(start, len(decl)):
        ch = decl[i]
        if ch == "(":
            depth += 1
        elif ch == ")":
            depth -= 1
            if depth == 0:
                return start, i
    return None


def split_param_strings(decl: str) -> list[str]:
    span = param_list_span(decl)
    if span is None:
        return []
    start, end = span
    params = decl[start + 1 : end].strip()
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
    return out


def parse_params(decl: str) -> list[str]:
    names: list[str] = []
    for i, p in enumerate(split_param_strings(decl)):
        p = strip_c_comments(re.sub(r"\[[^\]]*\]", "", p)).strip()
        if "..." in p:
            break
        m_ptr = re.search(r"\*\s*([A-Za-z_][A-Za-z0-9_]*)\s*\)", p)
        if m_ptr:
            names.append(clean_param_name(m_ptr.group(1)))
            continue
        tok = re.split(r"\s+", p.replace("*", " ").strip())
        cand = tok[-1] if tok else ""
        if (
            cand
            and cand not in TYPE_KEYWORDS
            and re.match(r"^[A-Za-z_]", cand)
        ):
            names.append(clean_param_name(cand))
        else:
            names.append(f"unused_arg_{i}")
    return names


def format_fn_signature(decl: str, param_names: list[str]) -> str:
    head = decl.split("(", 1)[0].strip()
    raw_params = split_param_strings(decl)
    if not raw_params:
        return f"{head}(void)"
    sig_params: list[str] = []
    for raw, name in zip(raw_params, param_names):
        raw = strip_c_comments(re.sub(r"\[[^\]]*\]", "", raw)).strip()
        if "..." in raw:
            sig_params.append("...")
            break
        if re.search(rf"\*\s*{re.escape(name)}\s*\)", raw):
            sig_params.append(raw)
            continue
        if re.search(rf"\b{re.escape(name)}\s*$", raw):
            sig_params.append(raw)
        else:
            sig_params.append(f"{raw} {name}")
    if any("..." in strip_c_comments(re.sub(r"\[[^\]]*\]", "", r)) for r in raw_params):
        if not sig_params or sig_params[-1] != "...":
            sig_params.append("...")
    return f"{head}({', '.join(sig_params)})"


def ret_kind(decl: str) -> str:
    head = decl.split("(", 1)[0].strip()
    if head.startswith("void ") and "*" not in head:
        return "void"
    if "*" in head:
        return "ptr"
    if re.search(r"\bchar\b", head):
        return "char"
    if re.search(r"\b(int|short|long|bool|float|double|wchar_t|size_t|uint|int64_t|int32_t|int16_t|uint32_t|uint16_t|uint8_t)\b", head):
        return "scalar"
    return "void"


def gen_stub_body(decl: str, addr: str | None = None) -> str:
    use_addr = addr.lower() if addr else "0x0"
    name = fn_name(decl, use_addr)
    raw = strip_c_comments(decl or "")
    c_decl = sanitize_decl_for_c(decl)
    if "??" in raw or re.search(r"@[0-9A-Za-z_]*\s*\(", raw):
        c_decl = f"void {name}(void);"
    else:
        san_name = fn_name(c_decl, use_addr)
        if san_name != name:
            c_decl = re.sub(
                rf"\b{re.escape(san_name)}\s*\(", f"{name}(", c_decl, count=1
            )
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
    sig = format_fn_signature(c_decl.rstrip(";"), params)
    return f"{sig}\n{{\n{inner}\n}}\n"


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
        parts.append(f"/* {addr} */\n{gen_stub_body(decls[addr], addr)}")
    text = "\n".join(parts)
    impl_out.write_text(text)
    frag_out.write_text(text)
    print(f"wrote {impl_out} ({len(decls)} drafts)")


if __name__ == "__main__":
    main()
