#!/usr/bin/env python3
"""Inject forward declarations for top-level functions in a C source file."""
from __future__ import annotations

import argparse
import importlib.util
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
MARKER = "/* --- forward decls (auto) --- */"
SIG_RE = re.compile(
    r"(?ms)"
    r"(/\* 0x[0-9a-f]+ \*/\s*)"
    r"((?:static\s+)?(?:inline\s+)?"
    r"(?:__declspec\s*\([^)]*\)\s+)?"
    r"(?:[\w\s*]+?(?:\*|\s+)|[\w\s]+\*\s*)"
    r"(?:__stdcall\s+|__cdecl\s+|__fastcall\s+)?"
    r"[A-Za-z_][A-Za-z0-9_]*\s*"
    r"\((?:[^()\"']|\([^()\"']*\))*\))\s*\{"
)


def extract_sigs(text: str) -> list[str]:
    sigs: list[str] = []
    seen: set[str] = set()
    for m in SIG_RE.finditer(text):
        sig = re.sub(r"\s+", " ", m.group(2).strip())
        name_m = re.search(r"([A-Za-z_][A-Za-z0-9_]*)\s*\(", sig)
        if not name_m:
            continue
        name = name_m.group(1)
        if name in seen:
            continue
        seen.add(name)
        sigs.append(sig + ";")
    return sigs


def inject(path: Path) -> int:
    text = path.read_text()
    if MARKER in text:
        return 0
    sigs = extract_sigs(text)
    if not sigs:
        return 0
    block = MARKER + "\n" + "\n".join(sigs) + "\n\n"
    m = re.match(r"((?:/\*.*?\*/\s*)+)", text, flags=re.DOTALL)
    if m:
        text = text[: m.end()] + "\n" + block + text[m.end() :]
    else:
        text = block + text
    path.write_text(text)
    return len(sigs)


def main() -> None:
    ap = argparse.ArgumentParser()
    ap.add_argument("paths", nargs="+")
    args = ap.parse_args()
    total = 0
    for p in args.paths:
        n = inject(Path(p))
        if n:
            print(f"{p}: {n} forward decls")
            total += n
    print(f"TOTAL: {total}")


if __name__ == "__main__":
    main()
