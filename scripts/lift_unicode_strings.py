#!/usr/bin/env python3
"""Hand-lift unicode string assert wrappers (80–400B) → Docker → Unicorn-prove."""
from __future__ import annotations

import json
import re
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "scripts"))
from lift_inventory_batch4 import find_naked_block  # noqa: E402
from prove_inventory_batch4 import ensure_oracle, flip_kb  # noqa: E402
from tu_compile import docker_compile  # noqa: E402
from unicorn_c_campaign import (  # noqa: E402
    KB_PATH,
    append_ledger,
    clear_pass,
    count_ported,
    git_push,
    is_naked_near_def,
    run_unicorn,
)

COMMIT_EVERY = 8
FILE = "0x2b45b4"

# (addr, name, body, decl)
LIFTS: list[tuple[int, str, str, str]] = []


def L(addr: int, name: str, body: str, decl: str) -> None:
    LIFTS.append((addr, name, body.strip() + "\n", decl if decl.endswith(";") else decl + ";"))


def A(msg: str, line: str | int, indent: str = "    ") -> str:
    return (
        f"{indent}display_assert((const char *){msg}, (const char *){FILE}, {line}, 1);\n"
        f"{indent}system_exit(-1);\n"
    )


# --- simple length / compare / span wrappers ---
L(
    0x19D8C0,
    "ustrlen",
    f"""
/* ustrlen (0x19d8c0) — readable C lift. */
int ustrlen(const unsigned short *s)
{{
  size_t n;
  if (s == NULL) {{
{A('0x27b838', '0xc2')}  }}
  n = _wcslen((const wchar_t *)s);
  if (n >= 0x8000) {{
{A('0x2b483c', '0xc4')}  }}
  return (int)n;
}}
""",
    "int ustrlen(const unsigned short *s);",
)

L(
    0x19D810,
    "ustrcmp",
    f"""
/* ustrcmp (0x19d810) — readable C lift. */
int ustrcmp(const wchar_t *s1, const wchar_t *s2)
{{
  if (s1 == NULL || s2 == NULL) {{
{A('0x2b4828', '0xb5')}  }}
  if (_wcslen(s1) >= 0x8000) {{
{A('0x2b4800', '0xb6')}  }}
  if (_wcslen(s2) >= 0x8000) {{
{A('0x2b47d8', '0xb7')}  }}
  return _wcscmp(s1, s2);
}}
""",
    "int ustrcmp(const wchar_t *s1, const wchar_t *s2);",
)

L(
    0x19DC20,
    "ustrncmp",
    f"""
/* ustrncmp (0x19dc20) — readable C lift. */
int ustrncmp(const wchar_t *s1, const wchar_t *s2, size_t count)
{{
  if (s1 == NULL || s2 == NULL) {{
{A('0x2b4828', '0x12a')}  }}
  if (count >= 0x8000) {{
{A('0x2b48c4', '0x12b')}  }}
  return _wcsncmp(s1, s2, count);
}}
""",
    "int ustrncmp(const wchar_t *s1, const wchar_t *s2, size_t count);",
)

L(
    0x19D930,
    "ustrnlen",
    f"""
/* ustrnlen (0x19d930) — readable C lift. */
size_t ustrnlen(const wchar_t *s, size_t max_len)
{{
  size_t n = 0;
  if (s == NULL) {{
{A('0x27b838', '0xd0')}  }}
  if (max_len != 0) {{
    while (n < max_len) {{
      wchar_t c = s[n];
      if (c == 0)
        break;
      n++;
    }}
  }}
  if (n >= 0x8000) {{
{A('0x2b483c', '0xd6')}  }}
  return n;
}}
""",
    "size_t ustrnlen(const wchar_t *s, size_t max_len);",
)

L(
    0x19DB80,
    "ustrncat",
    f"""
/* ustrncat (0x19db80) — readable C lift. */
wchar_t *ustrncat(wchar_t *dest, const wchar_t *src, size_t count)
{{
  if (dest == NULL || src == NULL) {{
{A('0x2b4660', '0x111')}  }}
  if (_wcslen(dest) >= 0x8000) {{
{A('0x2b47b4', '0x112')}  }}
  if (count >= 0x8000) {{
{A('0x2b48c4', '0x113')}  }}
  return _wcsncat(dest, src, count);
}}
""",
    "wchar_t *ustrncat(wchar_t *dest, const wchar_t *src, size_t count);",
)

L(
    0x19DA20,
    "ustrcoll",
    f"""
/* ustrcoll (0x19da20) — readable C lift. */
int ustrcoll(const wchar_t *s1, const wchar_t *s2)
{{
  if (s1 == NULL || s2 == NULL) {{
{A('0x2b4828', '0xeb')}  }}
  if (_wcslen(s1) >= 0x8000) {{
{A('0x2b4800', '0xec')}  }}
  if (_wcslen(s2) >= 0x8000) {{
{A('0x2b47d8', '0xed')}  }}
  return FUN_001dbfa7(s1, s2);
}}
""",
    "int ustrcoll(const wchar_t *s1, const wchar_t *s2);",
)

L(
    0x19DAD0,
    "ustrcspn",
    f"""
/* ustrcspn (0x19dad0) — readable C lift. */
size_t ustrcspn(const wchar_t *s, const wchar_t *reject)
{{
  if (s == NULL || reject == NULL) {{
{A('0x2b48ac', '0xf7')}  }}
  if (_wcslen(s) >= 0x8000) {{
{A('0x2b4858', '0xf8')}  }}
  if (_wcslen(reject) >= 0x8000) {{
{A('0x2b4880', '0xf9')}  }}
  return _wcscspn(s, reject);
}}
""",
    "size_t ustrcspn(const wchar_t *s, const wchar_t *reject);",
)

L(
    0x19DE20,
    "ustrspn",
    f"""
/* ustrspn (0x19de20) — readable C lift. */
size_t ustrspn(const wchar_t *s, const wchar_t *accept)
{{
  if (s == NULL || accept == NULL) {{
{A('0x2b48ac', '0x158')}  }}
  if (_wcslen(s) >= 0x8000) {{
{A('0x2b4858', '0x159')}  }}
  if (_wcslen(accept) >= 0x8000) {{
{A('0x2b4880', '0x15a')}  }}
  return _wcsspn(s, accept);
}}
""",
    "size_t ustrspn(const wchar_t *s, const wchar_t *accept);",
)

L(
    0x19E300,
    "ustrcasecmp",
    f"""
/* ustrcasecmp (0x19e300) — readable C lift. */
int ustrcasecmp(const wchar_t *s1, const wchar_t *s2)
{{
  if (s1 == NULL || s2 == NULL) {{
{A('0x2b4828', '0x1c7')}  }}
  if (_wcslen(s1) >= 0x8000) {{
{A('0x2b4800', '0x1c8')}  }}
  if (_wcslen(s2) >= 0x8000) {{
{A('0x2b47d8', '0x1c9')}  }}
  return __wcsicmp(s1, s2);
}}
""",
    "int ustrcasecmp(const wchar_t *s1, const wchar_t *s2);",
)

L(
    0x19E3B0,
    "ustrncasecmp",
    f"""
/* ustrncasecmp (0x19e3b0) — readable C lift. */
int ustrncasecmp(const wchar_t *s1, const wchar_t *s2, size_t count)
{{
  if (s1 == NULL || s2 == NULL) {{
{A('0x2b4828', '0x1d8')}  }}
  if (_wcslen(s1) >= 0x8000) {{
{A('0x2b4800', '0x1d9')}  }}
  if (_wcslen(s2) >= 0x8000) {{
{A('0x2b47d8', '0x1da')}  }}
  return __wcsnicmp(s1, s2, count);
}}
""",
    "int ustrncasecmp(const wchar_t *s1, const wchar_t *s2, size_t count);",
)

L(
    0x19DFF0,
    "ustrxfrm",
    f"""
/* ustrxfrm (0x19dff0) — readable C lift. */
size_t ustrxfrm(wchar_t *dest, const wchar_t *src, size_t count)
{{
  if (dest == NULL || src == NULL) {{
{A('0x2b4660', '0x17c')}  }}
  if (_wcslen(dest) >= 0x8000) {{
{A('0x2b47b4', '0x17d')}  }}
  if (_wcslen(src) >= 0x8000) {{
{A('0x2b4790', '0x17e')}  }}
  if (count >= 0x8000) {{
{A('0x2b492c', '0x17f')}  }}
  return FUN_001dc257(dest, src, count);
}}
""",
    "size_t ustrxfrm(wchar_t *dest, const wchar_t *src, size_t count);",
)

L(
    0x19E250,
    "ustrnupr",
    f"""
/* ustrnupr (0x19e250) — readable C lift.
 * Asserts count < 0x8000 but transforms the whole NUL-terminated string
 * via FUN_001da8e3 (same CRT leaf as utolower). */
wchar_t *ustrnupr(wchar_t *s, size_t count)
{{
  typedef unsigned short (*towlower_fn)(unsigned short);
  wchar_t *p;
  if (s == NULL) {{
{A('0x27b838', '0x1b3')}  }}
  if (_wcslen(s) >= 0x8000) {{
{A('0x2b4858', '0x1b4')}  }}
  if (count >= 0x8000) {{
{A('0x2b492c', '0x1b5')}  }}
  p = s;
  if (*p != 0) {{
    do {{
      *p = (wchar_t)((towlower_fn)FUN_001da8e3)((unsigned short)*p);
      p++;
    }} while (*p != 0);
  }}
  return s;
}}
""",
    "wchar_t *ustrnupr(wchar_t *s, size_t count);",
)

L(
    0x19E6C0,
    "ufgets",
    f"""
/* ufgets (0x19e6c0) — readable C lift. */
wchar_t *ufgets(wchar_t *buffer, int count, void *stream)
{{
  if (buffer == NULL) {{
{A('0x27b838', '0x26c')}  }}
  if (_wcslen(buffer) >= 0x8000) {{
{A('0x2b4858', '0x26d')}  }}
  if (count >= 0x8000) {{
{A('0x2b483c', '0x26e')}  }}
  return _fgetws(buffer, count, stream);
}}
""",
    "wchar_t *ufgets(wchar_t *buffer, int count, void *stream);",
)

L(
    0x19E760,
    "ufputs",
    f"""
/* ufputs (0x19e760) — readable C lift. */
int ufputs(const wchar_t *s, void *stream)
{{
  if (s == NULL) {{
{A('0x27b838', '0x278')}  }}
  if (_wcslen(s) >= 0x8000) {{
{A('0x2b4858', '0x279')}  }}
  if (stream == NULL) {{
{A('0x2b4948', '0x27a')}  }}
  return _fputws(s, stream);
}}
""",
    "int ufputs(const wchar_t *s, void *stream);",
)

L(
    0x19EBD0,
    "uvprintf",
    f"""
/* uvprintf (0x19ebd0) — readable C lift. */
int uvprintf(const wchar_t *format, char *args)
{{
  if (format == NULL) {{
{A('0x263510', '0x323')}  }}
  if (_wcslen(format) >= 0x8000) {{
{A('0x2b4950', '0x324')}  }}
  return _vprintf(format, args);
}}
""",
    "int uvprintf(const wchar_t *format, char *args);",
)

L(
    0x19EB50,
    "uvfprintf",
    f"""
/* uvfprintf (0x19eb50) — readable C lift. */
int uvfprintf(void *stream, const wchar_t *format, char *args)
{{
  if (stream == NULL || format == NULL) {{
{A('0x2b49b8', '0x318')}  }}
  if (_wcslen(format) >= 0x8000) {{
{A('0x2b4950', '0x319')}  }}
  return _vfwprintf(stream, format, args);
}}
""",
    "int uvfprintf(void *stream, const wchar_t *format, char *args);",
)

L(
    0x19EC40,
    "uvsnprintf",
    f"""
/* uvsnprintf (0x19ec40) — readable C lift. */
int uvsnprintf(wchar_t *buffer, size_t count, const wchar_t *format, char *args)
{{
  if (buffer == NULL || format == NULL) {{
{A('0x2b49a4', '0x330')}  }}
  if (_wcslen(buffer) >= 0x8000) {{
{A('0x2b4858', '0x331')}  }}
  if (_wcslen(format) >= 0x8000) {{
{A('0x2b4950', '0x332')}  }}
  return _vsnwprintf(buffer, count, format, args);
}}
""",
    "int uvsnprintf(wchar_t *buffer, size_t count, const wchar_t *format, char *args);",
)

L(
    0x19ECF0,
    "uvsprintf",
    f"""
/* uvsprintf (0x19ecf0) — readable C lift. */
int uvsprintf(wchar_t *buffer, const wchar_t *format, char *args)
{{
  if (buffer == NULL || format == NULL) {{
{A('0x2b49a4', '0x349')}  }}
  if (_wcslen(buffer) >= 0x8000) {{
{A('0x2b4858', '0x34a')}  }}
  if (_wcslen(format) >= 0x8000) {{
{A('0x2b4950', '0x34b')}  }}
  return FUN_001dcace(buffer, format, args);
}}
""",
    "int uvsprintf(wchar_t *buffer, const wchar_t *format, char *args);",
)

L(
    0x19F160,
    "ustrtol",
    f"""
/* ustrtol (0x19f160) — readable C lift. */
long ustrtol(const wchar_t *s, wchar_t **endptr, int base)
{{
  if (s == NULL) {{
{A('0x2b4a94', '0x3c7')}  }}
  if (_wcslen(s) >= 0x8000) {{
{A('0x2b4a70', '0x3c8')}  }}
  return FUN_001dd1d1(s, endptr, base);
}}
""",
    "long ustrtol(const wchar_t *s, wchar_t **endptr, int base);",
)

L(
    0x19F1D0,
    "ustrtoul",
    f"""
/* ustrtoul (0x19f1d0) — readable C lift. */
unsigned long ustrtoul(const wchar_t *s, wchar_t **endptr, int base)
{{
  if (s == NULL) {{
{A('0x2b4a94', '0x3d3')}  }}
  if (_wcslen(s) >= 0x8000) {{
{A('0x2b4a70', '0x3d4')}  }}
  return FUN_001dd1e8(s, endptr, base);
}}
""",
    "unsigned long ustrtoul(const wchar_t *s, wchar_t **endptr, int base);",
)

L(
    0x19F240,
    "ustrtod",
    f"""
/* ustrtod (0x19f240) — readable C lift. */
double ustrtod(const wchar_t *s, wchar_t **endptr)
{{
  if (s == NULL) {{
{A('0x2b4a94', '0x3de')}  }}
  if (_wcslen(s) >= 0x8000) {{
{A('0x2b4a70', '0x3df')}  }}
  return FUN_001dd1ff(s, endptr);
}}
""",
    "double ustrtod(const wchar_t *s, wchar_t **endptr);",
)

L(
    0x19E980,
    "uprintf",
    f"""
/* uprintf (0x19e980) — readable C lift. */
int uprintf(const wchar_t *format, ...)
{{
  char *args;
  if (format == NULL) {{
{A('0x263510', '0x2bb')}  }}
  if (_wcslen(format) >= 0x8000) {{
{A('0x2b4950', '0x2bc')}  }}
  args = (char *)((char *)&format + sizeof(format));
  return _vprintf(format, args);
}}
""",
    "int uprintf(const wchar_t *format, ...);",
)


def sync_decl(name: str, decl: str) -> None:
    path = ROOT / "build" / "generated" / "decl.h"
    if not path.exists():
        return
    d = decl.strip().rstrip(";")
    text = path.read_text(encoding="utf-8", errors="replace")
    pat = re.compile(rf"^HFUNC\s+.+\b{re.escape(name)}\s*\([^;\n]*\);$", re.M)
    new_text, n = pat.subn(f"HFUNC {d};", text, count=1)
    if n:
        path.write_text(new_text, encoding="utf-8")


def update_kb_decl(addr: int, decl: str) -> None:
    kb = json.loads(KB_PATH.read_text(encoding="utf-8"))
    for o in kb.get("objects", []):
        for fn in o.get("functions") or []:
            if isinstance(fn, dict) and fn.get("addr") and int(fn["addr"], 16) == addr:
                fn["decl"] = decl if decl.endswith(";") else decl + ";"
                KB_PATH.write_text(json.dumps(kb, indent=2) + "\n", encoding="utf-8")
                return


def commit_chunk(n: int, flips: list[str]) -> str | None:
    subprocess.run(
        [
            "git",
            "add",
            "kb.json",
            "src/halo/text/unicode.c",
            "scripts/lift_unicode_strings.py",
            "tools/equivalence/leaf_cache.json",
        ],
        cwd=ROOT,
        check=False,
    )
    msg = f"lift(track-a): unicode string Unicorn-prove {n} (ported:true)."
    r = subprocess.run(["git", "commit", "-m", msg], cwd=ROOT, capture_output=True, text=True)
    if r.returncode != 0:
        print("commit failed", r.stdout, r.stderr, flush=True)
        return None
    sha = subprocess.run(
        ["git", "rev-parse", "HEAD"], cwd=ROOT, capture_output=True, text=True
    ).stdout.strip()
    git_push()
    print(f"COMMIT+PUSH {sha} flips={flips[-n:]}", flush=True)
    return sha


def main() -> int:
    true0, false0 = count_ported(json.loads(KB_PATH.read_text(encoding="utf-8")))
    print(f"start true={true0} false={false0} lifts={len(LIFTS)}", flush=True)
    sp = ROOT / "src" / "halo" / "text" / "unicode.c"
    flips: list[str] = []
    shas: list[str] = []
    since = 0

    for ai, name, body, decl in LIFTS:
        kb = json.loads(KB_PATH.read_text(encoding="utf-8"))
        ported = None
        for o in kb["objects"]:
            for fn in o.get("functions") or []:
                if isinstance(fn, dict) and fn.get("addr") and int(fn["addr"], 16) == ai:
                    ported = fn.get("ported")
        if ported is not False:
            print(f"skip {hex(ai)} {name} ported={ported}", flush=True)
            continue
        text = sp.read_text(encoding="utf-8", errors="replace")
        if not is_naked_near_def(text.splitlines(), name, hex(ai)):
            print(f"skip not naked {hex(ai)} {name}", flush=True)
            continue
        span = find_naked_block(text, name, ai) or find_naked_block(
            text, f"FUN_{ai:08x}", ai
        )
        if not span:
            print(f"skip locate {hex(ai)} {name}", flush=True)
            continue
        update_kb_decl(ai, decl)
        sync_decl(name, decl)
        new_text = text[: span[0]] + body + "\n" + text[span[1] :]
        if "uintptr_t" in body and "#include <stdint.h>" not in new_text:
            new_text = "#include <stdint.h>\n" + new_text
        sp.write_text(new_text, encoding="utf-8")
        print(f"\n== {hex(ai)} {name} ==", flush=True)
        if not docker_compile("text/unicode.c"):
            sp.write_text(text, encoding="utf-8")
            print("  compile FAIL — revert", flush=True)
            continue
        if not ensure_oracle(ai):
            sp.write_text(text, encoding="utf-8")
            print("  oracle FAIL — revert", flush=True)
            continue
        res = run_unicorn(name, ai, 100, timeout=45.0)
        ok = clear_pass(res, 100)
        if not ok:
            res2 = run_unicorn(hex(ai), ai, 100, timeout=45.0)
            if clear_pass(res2, 100) or (res2.get("passed") or 0) > (res.get("passed") or 0):
                res = res2
            ok = clear_pass(res, 100)
        print(
            f"  ok={ok} {res.get('passed')}/{res.get('failed')}/{res.get('errors')} "
            f"dt={res.get('dt')}",
            flush=True,
        )
        append_ledger(
            {
                "addr": hex(ai),
                "name": name,
                "ok": ok,
                "phase": "unicode_strings",
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
            KB_PATH.write_text(json.dumps(kb, indent=2) + "\n", encoding="utf-8")
            flips.append(hex(ai))
            since += 1
            print(f"  FLIP total={len(flips)}", flush=True)
        if since >= COMMIT_EVERY:
            sha = commit_chunk(since, flips)
            if sha:
                shas.append(sha)
            since = 0

    if since:
        sha = commit_chunk(since, flips)
        if sha:
            shas.append(sha)

    true1, false1 = count_ported(json.loads(KB_PATH.read_text(encoding="utf-8")))
    summary = {
        "proven": len(flips),
        "flips": flips,
        "shas": shas,
        "true0": true0,
        "true1": true1,
        "false1": false1,
    }
    Path("/tmp/lift_unicode_strings.json").write_text(json.dumps(summary, indent=2))
    print("DONE", summary, flush=True)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
