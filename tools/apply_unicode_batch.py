#!/usr/bin/env python3
"""Apply unicode.obj batch drafts to kb + allowlist."""
from __future__ import annotations

import json
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
from gen_unicode_batch import DECLS  # noqa: E402

OBJECT = "unicode.obj"

HELPER_DECLS = {
    "0x1dbfa7": "int FUN_001dbfa7(const wchar_t *s1, const wchar_t *s2);",
    "0x1dc257": "size_t FUN_001dc257(wchar_t *dest, const wchar_t *src, size_t count);",
    "0x1dc3e9": "int FUN_001dc3e9(int c, int mask);",
    "0x1dcace": "int FUN_001dcace(wchar_t *buffer, const wchar_t *format, char *args);",
    "0x1dcb6c": "void *FUN_001dcb6c(int fd, const wchar_t *mode);",
    "0x1dccf5": "void *FUN_001dccf5(const wchar_t *path, const wchar_t *mode);",
    "0x1dcd6e": "void FUN_001dcd6e(const wchar_t *prefix);",
    "0x1dce6e": "int FUN_001dce6e(const wchar_t *path);",
    "0x1dcf51": "wchar_t *FUN_001dcf51(wchar_t *buffer);",
    "0x1dd1d1": "long FUN_001dd1d1(const wchar_t *s, wchar_t **endptr, int base);",
    "0x1dd1e8": "unsigned long FUN_001dd1e8(const wchar_t *s, wchar_t **endptr, int base);",
    "0x1dd1ff": "double FUN_001dd1ff(const wchar_t *s, wchar_t **endptr);",
    "0x1dd3d4": "int FUN_001dd3d4(const wchar_t *s);",
    "0x1dd576": "int FUN_001dd576(int param);",
    "0x1e6805": "wchar_t *FUN_001e6805(wchar_t *s);",
    "0x1e6831": "wchar_t *FUN_001e6831(wchar_t *s);",
    "0x1dc27c": "wchar_t *FUN_001dc27c(wchar_t *s, size_t count);",
    "0x1da8e3": "wchar_t *FUN_001da8e3(wchar_t *s, size_t count);",
}

CRT_STUB_DECLS = {
    "0x1dbf75": "int _wcscmp(const wchar_t *s1, const wchar_t *s2);",
    "0x1db134": "wchar_t *_wcschr(const wchar_t *s, wchar_t c);",
    "0x1dbfac": "size_t _wcscspn(const wchar_t *s, const wchar_t *reject);",
    "0x1dbfef": "wchar_t *_wcsncat(wchar_t *dest, const wchar_t *src, size_t count);",
    "0x1dc02c": "int _wcsncmp(const wchar_t *s1, const wchar_t *s2, size_t count);",
    "0x1dc09e": "wchar_t *_wcspbrk(const wchar_t *s, const wchar_t *accept);",
    "0x1dc0de": "wchar_t *_wcsrchr(const wchar_t *s, wchar_t c);",
    "0x1dc10e": "size_t _wcsspn(const wchar_t *s, const wchar_t *accept);",
    "0x1dc154": "wchar_t *_wcsstr(const wchar_t *haystack, const wchar_t *needle);",
    "0x1dc1b2": "wchar_t *_wcstok(wchar_t *s, const wchar_t *delim);",
    "0x1dc2c3": "int __wcsicmp(const wchar_t *s1, const wchar_t *s2);",
    "0x1dc34b": "int __wcsnicmp(const wchar_t *s1, const wchar_t *s2, size_t count);",
    "0x1dc512": "int _fgetwc(void *stream);",
    "0x1dc61e": "int _fputwc(int c, void *stream);",
    "0x1dc766": "int _ungetwc(int c, void *stream);",
    "0x1dc7ac": "wchar_t *_fgetws(wchar_t *buffer, int count, void *stream);",
    "0x1dc82c": "int _fputws(const wchar_t *s, void *stream);",
    "0x1dc89a": "wchar_t *__getws(wchar_t *buffer);",
    "0x1dc914": "int __putws(const wchar_t *s);",
    "0x1dc9a3": "int _vfwprintf(void *stream, const wchar_t *format, char *args);",
    "0x1dca00": "int _vprintf(const wchar_t *format, char *args);",
    "0x1dcd08": "void *__wfreopen(const wchar_t *path, const wchar_t *mode, void *stream);",
    "0x1dd467": "wchar_t *__wctime(const void *timeptr);",
    "0x1dd49a": "wchar_t *__wasctime(const void *timeptr);",
}


def patch_helper_decls(kb: dict) -> None:
    for addr, decl in {**HELPER_DECLS, **CRT_STUB_DECLS}.items():
        for o in kb["objects"]:
            for f in o.get("functions", []):
                if f.get("addr") == addr:
                    f["decl"] = decl
                    break


def main() -> None:
    kb = json.loads((ROOT / "kb.json").read_text())
    patch_helper_decls(kb)
    obj = next(o for o in kb["objects"] if o["name"] == OBJECT)
    for addr, decl in DECLS.items():
        for f in obj["functions"]:
            if f["addr"] == addr:
                f["decl"] = decl
                f["ported"] = False
                break

    al_path = ROOT / "tools/audit/deactivation_allowlist.json"
    al = json.loads(al_path.read_text())
    have_al = {e["addr"] for e in al if isinstance(e, dict)}
    for addr, decl in DECLS.items():
        if addr in have_al:
            continue
        name = re.search(r"([A-Za-z_][A-Za-z0-9_]*)\s*\(", decl).group(1)
        al.append(
            {
                "addr": addr,
                "name": name,
                "object": OBJECT,
                "reason": "draft lift pending VC71/equivalence — keep inactive until scored",
                "since": "2026-07-26",
            }
        )
    al_path.write_text(json.dumps(al, indent=2) + "\n")
    (ROOT / "kb.json").write_text(json.dumps(kb, indent=2) + "\n")
    print("kb+allowlist updated for", len(DECLS), "unicode drafts")


if __name__ == "__main__":
    main()
