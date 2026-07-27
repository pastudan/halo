#!/usr/bin/env python3
"""Synthesize MSVC-style i386 COFF .obj files from cachebeta.xbe.

Produces per-function oracle objects under delinked/functions/<hex8>.obj so
Unicorn equivalence (tools/equivalence/unicorn_diff.py) can run without Ghidra
for many functions. Relocations are recovered via Capstone:

  E8 near call          -> IMAGE_REL_I386_REL32 (0x14) to FUN_<target> / kb name
  abs imm/disp in range -> IMAGE_REL_I386_DIR32 (0x6)  to DAT_/FUN_<addr>
  relocated dword       -> zeroed in .text (delinker convention)

Examples:
  python3 tools/equivalence/xbe_to_coff.py --addr 0x193a80 \\
      --out delinked/functions/00193a80.obj
  python3 tools/equivalence/xbe_to_coff.py --batch-ported-false-c --limit 50
"""
from __future__ import annotations

import argparse
import bisect
import json
import re
import struct
import sys
from dataclasses import dataclass, field
from pathlib import Path
from typing import Optional

from capstone import CS_ARCH_X86, CS_MODE_32, CS_OP_IMM, Cs
from capstone.x86 import X86_GRP_JUMP
from xbe import Xbe

# Allow `python3 tools/equivalence/xbe_to_coff.py` and package-relative imports.
_TOOLS_EQ = Path(__file__).resolve().parent
if str(_TOOLS_EQ) not in sys.path:
    sys.path.insert(0, str(_TOOLS_EQ))

from coff_loader import IMAGE_REL_I386_DIR32, extract_function, load_coff  # noqa: E402

ROOT = Path(__file__).resolve().parents[2]
DEFAULT_XBE = ROOT / "halo-patched" / "cachebeta.xbe"
DEFAULT_KB = ROOT / "kb.json"
DEFAULT_OBJDIFF = ROOT / "objdiff.json"
DEFAULT_OUT_DIR = ROOT / "delinked" / "functions"

IMAGE_FILE_MACHINE_I386 = 0x014C
IMAGE_SCN_CNT_CODE = 0x00000020
IMAGE_SCN_MEM_EXECUTE = 0x20000000
IMAGE_SCN_MEM_READ = 0x40000000
TEXT_CHARS = IMAGE_SCN_CNT_CODE | IMAGE_SCN_MEM_EXECUTE | IMAGE_SCN_MEM_READ  # 0x60000020
COMMENT_CHARS = 0x00000A00

IMAGE_SYM_CLASS_EXTERNAL = 2
IMAGE_SYM_CLASS_STATIC = 3
IMAGE_SYM_CLASS_FILE = 103
IMAGE_SYM_DEBUG = 0xFFFE  # 65534

SYM_TYPE_FUNCTION = 0x20

# Typical Halo CE (Xbox) address windows used by the delinker heuristics.
CODE_ADDR_LO = 0x00010000
CODE_ADDR_HI = 0x00300000
DATA_ADDR_LO = 0x00200000
DATA_ADDR_HI = 0x00800000

COMMENT_BYTES = b"xbe-to-coff synthesizer v1.0.0\x00\x00\x00\x00"  # 33 bytes

COFF_HEADER_FMT = "<HHIIIHH"
SECTION_HEADER_FMT = "<8sIIIIIIHHI"
SYMBOL_ENTRY_SIZE = 18
RELOC_SIZE = 10


@dataclass
class RelocSite:
    offset: int  # offset within .text
    reloc_type: int
    symbol: str


@dataclass
class SynthResult:
    addr: int
    name: str
    code: bytes
    relocs: list[RelocSite] = field(default_factory=list)
    labels: list[tuple[int, str]] = field(default_factory=list)  # (offset, name)


def xbe_bytes(xbe: Xbe, va: int, end: int) -> bytes:
    """Return [va, end) from the XBE image (same helper as compare_xbe_pe).

    If ``end <= va``, treat ``end`` as a length (legacy/buggy call sites).
    """
    if end <= va:
        end = va + end
    for sec in xbe.sections.values():
        start = sec.header.virtual_addr
        if start <= va < start + sec.header.virtual_size:
            return bytes(sec.data[va - start : end - start])
    raise ValueError(f"va {va:#x} not in XBE")


def _decl_func_name(decl: str) -> Optional[str]:
    if not decl:
        return None
    m = re.search(r"(\w+)\s*\(", decl)
    return m.group(1) if m else None


def load_kb(path: Path) -> tuple[dict[int, dict], list[int]]:
    """Return (addr -> {name, ported, ...}, sorted function addresses)."""
    kb = json.loads(path.read_text(encoding="utf-8"))
    by_addr: dict[int, dict] = {}
    for obj in kb.get("objects", []):
        if not isinstance(obj, dict):
            continue
        src = obj.get("source") or ""
        obj_name = obj.get("name") or ""
        for fn in obj.get("functions") or []:
            if not isinstance(fn, dict) or not fn.get("addr"):
                continue
            addr = int(fn["addr"], 16)
            name = (
                fn.get("name")
                or _decl_func_name(fn.get("decl") or "")
                or f"FUN_{addr:08x}"
            )
            by_addr[addr] = {
                "addr": addr,
                "name": name,
                "ported": fn.get("ported"),
                "decl": fn.get("decl") or "",
                "source": src,
                "obj_name": obj_name,
            }
    addrs = sorted(by_addr)
    return by_addr, addrs


def resolve_symbol_name(addr: int, by_addr: dict[int, dict], code_hi: int) -> str:
    """Name an absolute address as FUN_/kb-name or DAT_."""
    ent = by_addr.get(addr)
    if ent is not None:
        return ent["name"]
    if CODE_ADDR_LO <= addr < min(code_hi, CODE_ADDR_HI):
        return f"FUN_{addr:08x}"
    return f"DAT_{addr:08x}"


def _is_halo_abs_addr(val: int) -> bool:
    u = val & 0xFFFFFFFF
    if CODE_ADDR_LO <= u < CODE_ADDR_HI:
        return True
    if DATA_ADDR_LO <= u < DATA_ADDR_HI:
        return True
    return False


def _trim_trailing_pad(code: bytes) -> bytes:
    while code and code[-1] in (0x90, 0xCC):
        code = code[:-1]
    return code


def extract_function_bytes(
    xbe: Xbe,
    addr: int,
    next_addr: Optional[int],
    max_span: int = 0x10000,
) -> bytes:
    """Slice function bytes from XBE; prefer next kb addr, else RET heuristic."""
    if next_addr is not None and next_addr > addr:
        end = min(next_addr, addr + max_span)
        code = xbe_bytes(xbe, addr, end)
        return _trim_trailing_pad(code)

    # Fallback: scan forward for a RET (+ optional align nop), capped.
    probe = xbe_bytes(xbe, addr, addr + max_span)
    md = Cs(CS_ARCH_X86, CS_MODE_32)
    end_off = None
    for insn in md.disasm(probe, addr):
        off = insn.address + insn.size - addr
        if insn.mnemonic == "ret":
            end_off = off
            # Keep a single trailing 0x90 nop if present (XBE align style).
            if off < len(probe) and probe[off] == 0x90:
                end_off = off + 1
            break
        if insn.mnemonic == "int3":
            end_off = insn.address - addr
            break
    if end_off is None:
        raise ValueError(f"no function end found for {addr:#x}")
    return _trim_trailing_pad(probe[:end_off])


def synthesize_relocs(
    code: bytes,
    addr: int,
    by_addr: dict[int, dict],
    code_hi: int,
) -> tuple[bytes, list[RelocSite], list[tuple[int, str]]]:
    """Disassemble, emit reloc sites, zero relocated dwords, collect LAB_*."""
    md = Cs(CS_ARCH_X86, CS_MODE_32)
    md.detail = True
    out = bytearray(code)
    relocs: list[RelocSite] = []
    label_offs: set[int] = set()
    end = addr + len(code)

    for insn in md.disasm(code, addr):
        off = insn.address - addr
        raw = insn.bytes

        # Local jump targets -> LAB_* (no reloc).
        if X86_GRP_JUMP in insn.groups and insn.mnemonic != "call":
            if insn.operands and insn.operands[0].type == CS_OP_IMM:
                tgt = insn.operands[0].imm & 0xFFFFFFFF
                if addr <= tgt < end:
                    label_offs.add(tgt - addr)

        # Near call: E8 rel32
        if insn.mnemonic == "call" and len(raw) == 5 and raw[0] == 0xE8:
            tgt = insn.operands[0].imm & 0xFFFFFFFF
            sym = resolve_symbol_name(tgt, by_addr, code_hi)
            relocs.append(RelocSite(off + 1, 0x14, sym))  # IMAGE_REL_I386_REL32
            out[off + 1 : off + 5] = b"\x00\x00\x00\x00"
            continue

        # Near jmp: E9 rel32 to *external* target (tail-call thunks).
        # Local jmps stay as LAB_* (handled above); without REL32 the oracle
        # keeps a VA-relative displacement and Unicorn FETCH_UNMAPPED-crashes.
        if insn.mnemonic == "jmp" and len(raw) == 5 and raw[0] == 0xE9:
            tgt = insn.operands[0].imm & 0xFFFFFFFF
            if not (addr <= tgt < end):
                sym = resolve_symbol_name(tgt, by_addr, code_hi)
                relocs.append(RelocSite(off + 1, 0x14, sym))  # IMAGE_REL_I386_REL32
                out[off + 1 : off + 5] = b"\x00\x00\x00\x00"
                continue

        # Absolute 32-bit immediates / displacements encoded in the insn.
        candidates: list[tuple[int, int]] = []  # (byte_offset_in_insn, value)
        if insn.disp_offset and insn.disp_offset + 4 <= len(raw):
            disp = struct.unpack_from("<I", raw, insn.disp_offset)[0]
            candidates.append((insn.disp_offset, disp))
        if insn.imm_offset and insn.imm_offset + 4 <= len(raw):
            imm = struct.unpack_from("<I", raw, insn.imm_offset)[0]
            # Arithmetic immediates are scalars (e.g. imul eax,eax,0x19660d for
            # the NR LCG). Treating them as DIR32 zeros the constant and breaks
            # Unicorn oracles. Only mov/push-style immediates are VA candidates.
            if insn.mnemonic not in (
                "mov",
                "push",
                "movzx",
                "movsx",
            ):
                imm = None
            # push imm32 is overloaded for both pointer args and size scalars
            # (csmemset/debug_malloc). Reject .text-window immediates that are
            # not kb function entries — those are almost always sizes
            # (e.g. push 0x85b2c before csmemset in ai_debug_initialize).
            # Keep .rdata/.data pushes (string literals, BSS pointers).
            if imm is not None and insn.mnemonic == "push":
                u = imm & 0xFFFFFFFF
                if CODE_ADDR_LO <= u < 0x253080 and u not in by_addr:
                    imm = None
            if imm is not None:
                # Skip relative encodings: encoded dword must equal Capstone's
                # absolute operand when the operand is an address-bearing imm.
                candidates.append((insn.imm_offset, imm))

        seen_off: set[int] = set()
        for byte_off, val in candidates:
            if byte_off in seen_off:
                continue
            if not _is_halo_abs_addr(val):
                continue
            # Confirm the dword in the instruction really is this absolute value
            # (filters relative jcc/call encodings where Capstone exposes abs tgt).
            enc = struct.unpack_from("<I", raw, byte_off)[0]
            if enc != (val & 0xFFFFFFFF):
                continue
            # Relative jcc/jmp encode a displacement, not an absolute VA — skip.
            # Absolute indirect jumps (`jmp/call dword ptr [imm32]`) still need DIR32.
            if (
                X86_GRP_JUMP in insn.groups
                and insn.operands
                and insn.operands[0].type == CS_OP_IMM
            ):
                continue
            tgt = val & 0xFFFFFFFF
            site = off + byte_off
            # In-function absolutes (switch jump-table base / local ptr) → LAB_*.
            if addr <= tgt < end:
                label_offs.add(tgt - addr)
                sym = f"LAB_{tgt:08x}"
            else:
                sym = resolve_symbol_name(tgt, by_addr, code_hi)
            relocs.append(RelocSite(site, IMAGE_REL_I386_DIR32, sym))
            out[site : site + 4] = b"\x00\x00\x00\x00"
            seen_off.add(byte_off)

    # Switch jump-table payloads: `jmp dword ptr [reg*4 + table]` where table
    # holds absolute in-function VAs. Capstone does not emit imm relocs for the
    # table body — fix them up so Unicorn does not FETCH_UNMAPPED.
    table_bases: list[int] = []
    for insn in md.disasm(code, addr):
        if insn.mnemonic != "jmp" or "dword ptr" not in insn.op_str or "*4" not in insn.op_str:
            continue
        if insn.disp_offset and insn.disp_offset + 4 <= len(insn.bytes):
            tab = struct.unpack_from("<I", insn.bytes, insn.disp_offset)[0]
            if addr <= tab < end:
                table_bases.append(tab)
    reloc_offs = {r.offset for r in relocs}
    for tab in table_bases:
        i = tab - addr
        while i + 4 <= len(out):
            if i in reloc_offs:
                break
            val = struct.unpack_from("<I", out, i)[0]
            if not (addr <= val < end):
                break
            label_offs.add(val - addr)
            relocs.append(RelocSite(i, IMAGE_REL_I386_DIR32, f"LAB_{val:08x}"))
            out[i : i + 4] = b"\x00\x00\x00\x00"
            reloc_offs.add(i)
            i += 4

    relocs.sort(key=lambda r: r.offset)
    labels = sorted((o, f"LAB_{addr + o:08x}") for o in label_offs)
    return bytes(out), relocs, labels


def _pack_name(name: str, string_table: bytearray) -> bytes:
    """8-byte COFF name field; long names go through the string table."""
    raw = name.encode("ascii")
    if len(raw) <= 8:
        return raw.ljust(8, b"\x00")
    # String table starts with size dword; first string payload at offset 4.
    off = len(string_table)
    string_table.extend(raw + b"\x00")
    return struct.pack("<II", 0, off)


def _append_symbol(
    symtab: bytearray,
    string_table: bytearray,
    name: str,
    value: int,
    section_num: int,
    sym_type: int,
    storage_class: int,
    aux: Optional[bytes] = None,
) -> int:
    """Append a symbol (+ optional aux). Returns symbol table index."""
    idx = len(symtab) // SYMBOL_ENTRY_SIZE
    naux = 1 if aux is not None else 0
    symtab.extend(_pack_name(name, string_table))
    symtab.extend(struct.pack("<IHHBB", value, section_num & 0xFFFF, sym_type, storage_class, naux))
    if aux is not None:
        if len(aux) != SYMBOL_ENTRY_SIZE:
            raise ValueError(f"aux record must be {SYMBOL_ENTRY_SIZE} bytes")
        symtab.extend(aux)
    return idx


def build_coff(result: SynthResult, out_name: str) -> bytes:
    """Assemble a minimal MSVC-style i386 COFF object for one function."""
    text = result.code
    relocs = result.relocs

    # --- Symbol / string tables (built first so we know indices for relocs) ---
    string_table = bytearray(struct.pack("<I", 0))  # size filled at end
    symtab = bytearray()

    # .file + aux (filename)
    file_aux = out_name.encode("ascii")[:18].ljust(18, b"\x00")
    _append_symbol(
        symtab, string_table, ".file", 0, IMAGE_SYM_DEBUG, 0, IMAGE_SYM_CLASS_FILE, file_aux
    )

    # .text + aux (length, nrelocs as Ghidra-style u32/u32)
    text_aux = struct.pack("<II", len(text), len(relocs)) + b"\x00" * 10
    _append_symbol(
        symtab, string_table, ".text", 0, 1, 0, IMAGE_SYM_CLASS_STATIC, text_aux
    )

    # Defined function symbol
    _append_symbol(
        symtab,
        string_table,
        result.name,
        0,
        1,
        SYM_TYPE_FUNCTION,
        IMAGE_SYM_CLASS_EXTERNAL,
    )

    # Local LAB_* first so jump-table DIR32 relocs bind here (not externals).
    sym_index: dict[str, int] = {}
    for off, lab in result.labels:
        sym_index[lab] = _append_symbol(
            symtab, string_table, lab, off, 1, 0, IMAGE_SYM_CLASS_STATIC
        )

    # External reloc symbols (unique); skip names already defined locally.
    for r in relocs:
        if r.symbol in sym_index:
            continue
        idx = _append_symbol(
            symtab,
            string_table,
            r.symbol,
            0,
            0,  # external
            SYM_TYPE_FUNCTION,
            IMAGE_SYM_CLASS_EXTERNAL,
        )
        sym_index[r.symbol] = idx

    struct.pack_into("<I", string_table, 0, len(string_table))

    # --- Section payloads ---
    reloc_blob = bytearray()
    for r in relocs:
        reloc_blob.extend(
            struct.pack("<IIH", r.offset, sym_index[r.symbol], r.reloc_type)
        )

    comment = COMMENT_BYTES
    if len(comment) != 33:
        comment = comment.ljust(33, b"\x00")[:33]

    # Layout: header + 2 section hdrs | .text | relocs | .comment | symtab | strtab
    nsections = 2
    header_size = 20
    sec_hdrs_size = 40 * nsections
    text_off = header_size + sec_hdrs_size
    reloc_off = text_off + len(text) if relocs else 0
    comment_off = (reloc_off + len(reloc_blob)) if relocs else (text_off + len(text))
    sym_ptr = comment_off + len(comment)
    nsymbols = len(symtab) // SYMBOL_ENTRY_SIZE

    buf = bytearray()
    buf.extend(
        struct.pack(
            COFF_HEADER_FMT,
            IMAGE_FILE_MACHINE_I386,
            nsections,
            0,  # TimeDateStamp
            sym_ptr,
            nsymbols,
            0,  # SizeOfOptionalHeader
            0,  # Characteristics
        )
    )

    # .text section header
    buf.extend(
        struct.pack(
            SECTION_HEADER_FMT,
            b".text\x00\x00\x00",
            0,  # VirtualSize
            0,  # VirtualAddress
            len(text),
            text_off,
            reloc_off,
            0,  # PointerToLinenumbers
            len(relocs),
            0,  # NumberOfLinenumbers
            TEXT_CHARS,
        )
    )
    # .comment section header
    buf.extend(
        struct.pack(
            SECTION_HEADER_FMT,
            b".comment",
            0,
            0,
            len(comment),
            comment_off,
            0,
            0,
            0,
            0,
            COMMENT_CHARS,
        )
    )

    assert len(buf) == text_off
    buf.extend(text)
    if relocs:
        assert len(buf) == reloc_off
        buf.extend(reloc_blob)
    assert len(buf) == comment_off
    buf.extend(comment)
    assert len(buf) == sym_ptr
    buf.extend(symtab)
    buf.extend(string_table)
    return bytes(buf)


def xbe_code_hi(xbe: Xbe) -> int:
    """End VA of the primary .text section (exclusive)."""
    text = xbe.sections.get(".text")
    if text is not None:
        return text.header.virtual_addr + text.header.virtual_size
    # Fallback: first section
    sec = next(iter(xbe.sections.values()))
    return sec.header.virtual_addr + sec.header.virtual_size


def synthesize_function(
    xbe: Xbe,
    addr: int,
    by_addr: dict[int, dict],
    sorted_addrs: list[int],
) -> SynthResult:
    next_addr = None
    i = bisect.bisect_right(sorted_addrs, addr)
    if i < len(sorted_addrs):
        next_addr = sorted_addrs[i]

    raw = extract_function_bytes(xbe, addr, next_addr)
    code_hi = xbe_code_hi(xbe)
    text, relocs, labels = synthesize_relocs(raw, addr, by_addr, code_hi)
    ent = by_addr.get(addr)
    name = ent["name"] if ent else f"FUN_{addr:08x}"
    return SynthResult(addr=addr, name=name, code=text, relocs=relocs, labels=labels)


def write_obj(result: SynthResult, out_path: Path) -> None:
    out_path.parent.mkdir(parents=True, exist_ok=True)
    blob = build_coff(result, out_path.name)
    out_path.write_bytes(blob)


def validate_roundtrip(out_path: Path, name: str, expect_len: Optional[int] = None) -> int:
    """Load via coff_loader.extract_function; return code length."""
    sl = extract_function(str(out_path), name)
    if expect_len is not None and len(sl.code) != expect_len:
        raise SystemExit(
            f"validation failed: extract_function len={len(sl.code)} expected {expect_len}"
        )
    # Also ensure load_coff accepts the file
    load_coff(str(out_path))
    return len(sl.code)


def _batch_targets(
    by_addr: dict[int, dict],
    objdiff_path: Path,
    out_dir: Path,
    limit: int,
    force: bool,
) -> list[int]:
    """Prefer objdiff-referenced missing oracles among ported:false + C source."""
    addrs: list[int] = []
    seen: set[int] = set()

    if objdiff_path.exists():
        units = json.loads(objdiff_path.read_text(encoding="utf-8")).get("units", [])
        for unit in units:
            base = unit.get("base_path") or ""
            if not base.startswith("delinked/functions/"):
                continue
            stem = Path(base).stem
            if not re.fullmatch(r"[0-9a-fA-F]{8}", stem):
                continue
            addr = int(stem, 16)
            ent = by_addr.get(addr)
            if ent is None or ent.get("ported") is not False:
                continue
            if not ent.get("source"):
                continue
            out = out_dir / f"{addr:08x}.obj"
            if out.exists() and not force:
                continue
            if addr not in seen:
                seen.add(addr)
                addrs.append(addr)
            if limit and len(addrs) >= limit:
                return addrs

    # Fallback: any ported:false with C source, ascending address
    if limit == 0 or len(addrs) < limit:
        for addr in sorted(by_addr):
            ent = by_addr[addr]
            if ent.get("ported") is not False or not ent.get("source"):
                continue
            out = out_dir / f"{addr:08x}.obj"
            if out.exists() and not force:
                continue
            if addr not in seen:
                seen.add(addr)
                addrs.append(addr)
            if limit and len(addrs) >= limit:
                break
    return addrs


def main(argv: Optional[list[str]] = None) -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--addr", help="Function VA (e.g. 0x193a80)")
    ap.add_argument("--out", type=Path, help="Output .obj path")
    ap.add_argument("--xbe", type=Path, default=DEFAULT_XBE, help="Path to cachebeta.xbe")
    ap.add_argument("--kb", type=Path, default=DEFAULT_KB, help="Path to kb.json")
    ap.add_argument(
        "--batch-ported-false-c",
        action="store_true",
        help="Generate oracles for ported:false functions that have C source",
    )
    ap.add_argument("--limit", type=int, default=0, help="Max functions in batch mode (0=all)")
    ap.add_argument(
        "--out-dir",
        type=Path,
        default=DEFAULT_OUT_DIR,
        help="Batch output directory (default delinked/functions)",
    )
    ap.add_argument("--force", action="store_true", help="Overwrite existing .obj files")
    ap.add_argument(
        "--objdiff",
        type=Path,
        default=DEFAULT_OBJDIFF,
        help="objdiff.json used to prioritize batch targets",
    )
    args = ap.parse_args(argv)

    if not args.batch_ported_false_c and not args.addr:
        ap.error("provide --addr or --batch-ported-false-c")

    if not args.xbe.exists():
        print(f"ERROR: XBE not found: {args.xbe}", file=sys.stderr)
        return 2

    by_addr, sorted_addrs = load_kb(args.kb)
    xbe = Xbe.from_file(str(args.xbe))

    if args.addr:
        addr = int(args.addr, 0)
        out = args.out or (args.out_dir / f"{addr:08x}.obj")
        result = synthesize_function(xbe, addr, by_addr, sorted_addrs)
        write_obj(result, out)
        print(
            f"wrote {out}  name={result.name}  len={len(result.code)}  "
            f"relocs={len(result.relocs)}  labels={len(result.labels)}"
        )
        n = validate_roundtrip(out, result.name)
        print(f"validate: extract_function OK len={n}")
        return 0

    # Batch mode
    targets = _batch_targets(by_addr, args.objdiff, args.out_dir, args.limit, args.force)
    ok = fail = 0
    for addr in targets:
        out = args.out_dir / f"{addr:08x}.obj"
        try:
            result = synthesize_function(xbe, addr, by_addr, sorted_addrs)
            write_obj(result, out)
            validate_roundtrip(out, result.name)
            print(
                f"OK  {addr:#010x}  {result.name:<40}  "
                f"len={len(result.code):<5} relocs={len(result.relocs)}"
            )
            ok += 1
        except Exception as exc:  # noqa: BLE001 — batch continues
            print(f"FAIL {addr:#010x}  {exc}", file=sys.stderr)
            fail += 1
    print(f"batch done: ok={ok} fail={fail} total={len(targets)}")
    return 0 if fail == 0 else 1


if __name__ == "__main__":
    raise SystemExit(main())
