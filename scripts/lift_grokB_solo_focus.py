#!/usr/bin/env python3
"""grokB-solo: LIBCMT/XAPI/XNET small leaves → readable C + Unicorn 100/0/0."""
from __future__ import annotations

import json
import re
import subprocess
import sys
import time
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "scripts"))
sys.path.insert(0, str(ROOT / "tools" / "equivalence"))

from lift_inventory_batch4 import L, LIFTS, cast_stale_fnptrs  # noqa: E402

LIFTS.clear()

from prove_inventory_batch4 import ensure_oracle, flip_kb  # noqa: E402
from tu_compile import docker_compile  # noqa: E402
from unicorn_c_campaign import (  # noqa: E402
    KB_PATH,
    append_ledger,
    clear_pass,
    count_ported,
    run_unicorn,
)

SEEDS = 100
TIMEOUT = 60.0


def find_block(text: str, name: str, addr: int):
    """Locate naked draft OR stub body keyed by addr/name."""
    addr_hex = f"0x{addr:x}"
    alt = {name, f"FUN_{addr:08x}", f"FUN_{addr:08X}"}
    for nm in alt:
        pat = re.compile(
            rf"/\*[^*]*\b{re.escape(addr_hex)}\b[^*]*\*/\s*"
            rf"#if defined\(__clang__\)\s*"
            rf"(?:static[\s\S]*?)?"
            rf"__attribute__\(\(naked[^\)]*\)\)\s*"
            rf"[\w\s\*]+?\b{re.escape(nm)}\s*\([\s\S]*?#endif\s*\n",
            re.M | re.I,
        )
        m = pat.search(text)
        if m:
            return m.start(), m.end()
        pat2 = re.compile(
            rf"/\*[^*]*\b{re.escape(addr_hex)}\b[^*]*\*/\s*"
            rf"(?:__attribute__\([^\)]*\)\s*)*"
            rf"[\w\s\*]+\b{re.escape(nm)}\s*\([^{{]*\)\s*\{{[\s\S]*?\n\}}\s*\n",
            re.M | re.I,
        )
        m = pat2.search(text)
        if m:
            return m.start(), m.end()
    return None


def apply_lifts_flex(addrs=None):
    selected = addrs if addrs else sorted(LIFTS.keys())
    by_source: dict[str, list[int]] = {}
    names: set[str] = set()
    for a in selected:
        by_source.setdefault(LIFTS[a][0], []).append(a)
        names.add(LIFTS[a][1])

    results = []
    for src, alist in by_source.items():
        path = ROOT / "src" / "halo" / src
        text = path.read_text(encoding="utf-8", errors="replace")
        before = text
        for a in sorted(alist, reverse=True):
            _source, name, body, decl = LIFTS[a]
            span = find_block(text, name, a)
            if span is None:
                print(f"FAIL locate {hex(a)} {name} in {src}", flush=True)
                results.append({"addr": hex(a), "ok": False, "err": "locate"})
                continue
            start, end = span
            text = text[:start] + body + "\n" + text[end:]
            print(f"lifted {hex(a)} {name}", flush=True)
            results.append({"addr": hex(a), "name": name, "ok": True, "decl": decl})
        if text != before:
            if ("uint8_t" in text or "uint16_t" in text or "uint32_t" in text) and (
                "#include <stdint.h>" not in text
            ):
                text = "#include <stdint.h>\n" + text
            text = cast_stale_fnptrs(text, names)
            path.write_text(text, encoding="utf-8")

    decl_map = {a: LIFTS[a][3] for a in selected if LIFTS[a][3]}
    if decl_map:
        kb = json.loads(KB_PATH.read_text(encoding="utf-8"))
        n = 0
        for obj in kb.get("objects", []):
            for fn in obj.get("functions") or []:
                if not isinstance(fn, dict) or not fn.get("addr"):
                    continue
                ai = int(fn["addr"], 16)
                if ai in decl_map:
                    fn["decl"] = decl_map[ai]
                    n += 1
        KB_PATH.write_text(json.dumps(kb, indent=2) + "\n", encoding="utf-8")
        print(f"updated {n} kb decls", flush=True)
    return results


# --- LIBCMT:wcslen.obj ---
L(
    0x1DB11E,
    "libcmt/wcslen.c",
    "_wcslen",
    """
/* _wcslen (0x1db11e) — readable C lift. */
size_t _wcslen(const wchar_t *str)
{
  const wchar_t *p = str;
  while (*p != 0)
    p++;
  return (size_t)(p - str);
}
""",
    "size_t _wcslen(const wchar_t *str);",
)

L(
    0x1DB134,
    "libcmt/wcslen.c",
    "_wcschr",
    """
/* _wcschr (0x1db134) — readable C lift. */
wchar_t *_wcschr(const wchar_t *s, wchar_t c)
{
  for (;;) {
    if (*s == c)
      return (wchar_t *)s;
    if (*s == 0)
      return 0;
    s++;
  }
}
""",
    "wchar_t *_wcschr(const wchar_t *s, wchar_t c);",
)

# --- LIBCMT:stricmp.obj ---
L(
    0x1DDCC6,
    "libcmt/stricmp.c",
    "FUN_001ddcc6",
    """
/* FUN_001ddcc6 (0x1ddcc6) — readable C lift: non-NaN/Inf double check. */
int FUN_001ddcc6(double x)
{
  unsigned short hi = *(unsigned short *)((char *)&x + 6);
  return (hi & 0x7ff0) != 0x7ff0;
}
""",
    "int FUN_001ddcc6(double x);",
)

L(
    0x1DE27A,
    "libcmt/stricmp.c",
    "FUN_001de27a",
    """
/* FUN_001de27a (0x1de27a) — readable C lift: __controlfp(0x10000, 0x30000). */
void FUN_001de27a(void)
{
  ((void (*)(unsigned int, unsigned int))__controlfp)(0x10000u, 0x30000u);
}
""",
    "void FUN_001de27a(void);",
)

L(
    0x1DDE73,
    "libcmt/stricmp.c",
    "FUN_001dde73",
    """
/* FUN_001dde73 (0x1dde73) — readable C lift. */
void FUN_001dde73(void)
{
  ((void (*)(int))FUN_001defb3)(4);
}
""",
    "void FUN_001dde73(void);",
)

L(
    0x1DDE12,
    "libcmt/stricmp.c",
    "_malloc",
    """
/* _malloc (0x1dde12) — readable C lift: nh_malloc(size, heap_flag). */
void *_malloc(size_t size)
{
  return ((void *(*)(size_t, int))__nh_malloc)(size, *(int *)0x4fc36c);
}
""",
    "void *_malloc(size_t size);",
)

L(
    0x1DD1D1,
    "libcmt/stricmp.c",
    "FUN_001dd1d1",
    """
/* FUN_001dd1d1 (0x1dd1d1) — readable C lift: wcstol wrapper (signed). */
long FUN_001dd1d1(const wchar_t *s, wchar_t **endptr, int base)
{
  return ((long (*)(const wchar_t *, wchar_t **, int, int))FUN_001dd00c)(s, endptr, base, 0);
}
""",
    "long FUN_001dd1d1(const wchar_t *s, wchar_t **endptr, int base);",
)

L(
    0x1DD1E8,
    "libcmt/stricmp.c",
    "FUN_001dd1e8",
    """
/* FUN_001dd1e8 (0x1dd1e8) — readable C lift: wcstoul wrapper (unsigned). */
unsigned long FUN_001dd1e8(const wchar_t *s, wchar_t **endptr, int base)
{
  return ((unsigned long (*)(const wchar_t *, wchar_t **, int, int))FUN_001dd00c)(
      s, endptr, base, 1);
}
""",
    "unsigned long FUN_001dd1e8(const wchar_t *s, wchar_t **endptr, int base);",
)

# --- LIBCMT:wcsncpy.obj ---
L(
    0x1DBFA7,
    "libcmt/wcsncpy.c",
    "FUN_001dbfa7",
    """
/* FUN_001dbfa7 (0x1dbfa7) — readable C lift: jmp thunk to _wcscmp. */
int FUN_001dbfa7(const wchar_t *s1, const wchar_t *s2)
{
  return _wcscmp(s1, s2);
}
""",
    "int FUN_001dbfa7(const wchar_t *s1, const wchar_t *s2);",
)

L(
    0x1DBFEF,
    "libcmt/wcsncpy.c",
    "_wcsncat",
    """
/* _wcsncat (0x1dbfef) — readable C lift. */
wchar_t *_wcsncat(wchar_t *dest, const wchar_t *src, size_t count)
{
  wchar_t *d = dest;
  while (*d != 0)
    d++;
  if (count == 0) {
    *d = 0;
    return dest;
  }
  for (;;) {
    wchar_t c = *src++;
    count--;
    *d++ = c;
    if (c == 0)
      return dest;
    if (count == 0) {
      *d = 0;
      return dest;
    }
  }
}
""",
    "wchar_t *_wcsncat(wchar_t *dest, const wchar_t *src, size_t count);",
)

L(
    0x1DC061,
    "libcmt/wcsncpy.c",
    "_wcsncpy",
    """
/* _wcsncpy (0x1dc061) — readable C lift. */
wchar_t *_wcsncpy(wchar_t *dest, const wchar_t *src, size_t count)
{
  wchar_t *d = dest;
  if (count != 0) {
    do {
      wchar_t c = *src++;
      *d++ = c;
      if (c == 0) {
        while (--count != 0)
          *d++ = 0;
        break;
      }
    } while (--count != 0);
  }
  return dest;
}
""",
    "wchar_t *_wcsncpy(wchar_t *dest, const wchar_t *src, size_t count);",
)

L(
    0x1DC09E,
    "libcmt/wcsncpy.c",
    "_wcspbrk",
    """
/* _wcspbrk (0x1dc09e) — readable C lift. */
wchar_t *_wcspbrk(const wchar_t *s, const wchar_t *accept)
{
  for (; *s != 0; s++) {
    const wchar_t *a;
    for (a = accept; *a != 0; a++) {
      if (*a == *s)
        return (wchar_t *)s;
    }
  }
  return 0;
}
""",
    "wchar_t *_wcspbrk(const wchar_t *s, const wchar_t *accept);",
)

L(
    0x1DC0DE,
    "libcmt/wcsncpy.c",
    "_wcsrchr",
    """
/* _wcsrchr (0x1dc0de) — readable C lift. */
wchar_t *_wcsrchr(const wchar_t *s, wchar_t c)
{
  const wchar_t *start = s;
  while (*s != 0)
    s++;
  for (;;) {
    if (*s == c)
      return (wchar_t *)s;
    if (s == start)
      return 0;
    s--;
  }
}
""",
    "wchar_t *_wcsrchr(const wchar_t *s, wchar_t c);",
)

L(
    0x1DC10E,
    "libcmt/wcsncpy.c",
    "_wcsspn",
    """
/* _wcsspn (0x1dc10e) — readable C lift. */
size_t _wcsspn(const wchar_t *s, const wchar_t *accept)
{
  const wchar_t *p = s;
  while (*p != 0) {
    const wchar_t *a = accept;
    while (*a != 0 && *a != *p)
      a++;
    if (*a == 0)
      break;
    p++;
  }
  return (size_t)(p - s);
}
""",
    "size_t _wcsspn(const wchar_t *s, const wchar_t *accept);",
)

L(
    0x1DC154,
    "libcmt/wcsncpy.c",
    "_wcsstr",
    """
/* _wcsstr (0x1dc154) — readable C lift. */
wchar_t *_wcsstr(const wchar_t *haystack, const wchar_t *needle)
{
  if (*needle == 0)
    return (wchar_t *)haystack;
  for (; *haystack != 0; haystack++) {
    const wchar_t *h = haystack;
    const wchar_t *n = needle;
    while (*n != 0 && *h == *n) {
      h++;
      n++;
    }
    if (*n == 0)
      return (wchar_t *)haystack;
  }
  return 0;
}
""",
    "wchar_t *_wcsstr(const wchar_t *haystack, const wchar_t *needle);",
)

L(
    0x1DC257,
    "libcmt/wcsncpy.c",
    "FUN_001dc257",
    """
/* FUN_001dc257 (0x1dc257) — readable C lift: wcsncpy then wcslen(src). */
size_t FUN_001dc257(wchar_t *dest, const wchar_t *src, size_t count)
{
  if (dest)
    _wcsncpy(dest, src, count);
  return _wcslen(src);
}
""",
    "size_t FUN_001dc257(wchar_t *dest, const wchar_t *src, size_t count);",
)

L(
    0x1DC27C,
    "libcmt/wcsncpy.c",
    "FUN_001dc27c",
    """
/* FUN_001dc27c (0x1dc27c) — readable C lift: towupper-ish. */
unsigned short FUN_001dc27c(unsigned short c)
{
  if (c == 0xffff)
    return c;
  if (*(int *)0x4fc25c == 0) {
    if (c >= 0x61 && c <= 0x7a)
      return (unsigned short)(c - 0x20);
    return c;
  }
  if (c < 0x100)
    ((void (*)(unsigned short, int))FUN_001dc3e9)(c, 2);
  return c;
}
""",
    "unsigned short FUN_001dc27c(unsigned short c);",
)

# --- XNET ---
L(
    0x1D8B64,
    "xdk/xnet/xnet.c",
    "XGetSectionSize",
    """
/* XGetSectionSize (0x1d8b64) — readable C lift. */
unsigned int __stdcall XGetSectionSize(void *section)
{
  return *(unsigned int *)((char *)section + 8);
}
""",
    "unsigned int __stdcall XGetSectionSize(void *section);",
)

# --- XAPILIB:xvutil ---
L(
    0x1D0581,
    "xdk/xapilib/xvutil.c",
    "FUN_001d0581",
    """
/* FUN_001d0581 (0x1d0581) — readable C lift: IAT double-deref getter. */
int FUN_001d0581(void)
{
  return **(int **)0x253140;
}
""",
    "int FUN_001d0581(void);",
)

L(
    0x1D0C48,
    "xdk/xapilib/xvutil.c",
    "FUN_001d0c48",
    """
/* FUN_001d0c48 (0x1d0c48) — readable C lift. */
void *__stdcall FUN_001d0c48(int flags, int size)
{
  return ((void *(__stdcall *)(void *, int, int))FUN_001d5c66)(
      *(void **)0x632a28, (flags >> 3) & 8, size);
}
""",
    "void *__stdcall FUN_001d0c48(int flags, int size);",
)

# --- XAPILIB:lasterr ---
L(
    0x1D2AD3,
    "xdk/xapilib/lasterr.c",
    "FUN_001d2ad3",
    """
/* FUN_001d2ad3 (0x1d2ad3) — readable C lift: nibble → ASCII hex. */
int __stdcall FUN_001d2ad3(int nibble)
{
  if (nibble <= 9)
    return nibble + 0x30;
  return nibble + 0x37;
}
""",
    "int __stdcall FUN_001d2ad3(int nibble);",
)

# --- LIBCMT:close.obj mantissa helpers ---
L(
    0x1E3D8D,
    "libcmt/close.c",
    "__CopyMan",
    """
/* __CopyMan (0x1e3d8d) — readable C lift: copy 3 dwords src→dst. */
void __CopyMan(unsigned int *dst, unsigned int *src)
{
  int i;
  for (i = 0; i < 3; i++) {
    *dst++ = *src++;
  }
}
""",
    "void __CopyMan(unsigned int *dst, unsigned int *src);",
)

L(
    0x1E3DB4,
    "libcmt/close.c",
    "__IsZeroMan",
    """
/* __IsZeroMan (0x1e3db4) — readable C lift. */
int __IsZeroMan(unsigned int *man)
{
  int i;
  for (i = 0; i < 3; i++) {
    if (man[i] != 0)
      return 0;
  }
  return 1;
}
""",
    "int __IsZeroMan(unsigned int *man);",
)

L(
    0x1E3C9C,
    "libcmt/close.c",
    "__ZeroTail",
    """
/* __ZeroTail (0x1e3c9c) — readable C lift. */
int __ZeroTail(unsigned int *man, int bit)
{
  int idx;
  int rem;
  unsigned int mask;
  unsigned int tmp;

  idx = bit / 32;
  rem = bit % 32;
  tmp = 0xffffffffu;
  mask = ~(tmp << (31 - rem));
  if (man[idx] & mask)
    return 0;
  for (idx = idx + 1; idx < 3; idx++) {
    if (man[idx] != 0)
      return 0;
  }
  return 1;
}
""",
    "int __ZeroTail(unsigned int *man, int bit);",
)

# --- XAPILIB:physmem ---
L(
    0x1D4436,
    "xdk/xapilib/physmem.c",
    "FUN_001d4436",
    """
/* FUN_001d4436 (0x1d4436) — readable C lift: ms → relative LARGE_INTEGER. */
long long *__stdcall FUN_001d4436(long long *out, unsigned int ms)
{
  unsigned long long prod;
  if (ms == 0xffffffffu) {
    return 0;
  }
  prod = (unsigned long long)ms * 10000ull;
  *out = -(long long)prod;
  return out;
}
""",
    "long long *__stdcall FUN_001d4436(long long *out, unsigned int ms);",
)

L(
    0x1D4DD3,
    "xdk/xapilib/physmem.c",
    "FUN_001d4dd3",
    """
/* FUN_001d4dd3 (0x1d4dd3) — readable C lift: Rtl heap entry → base. */
void *__stdcall FUN_001d4dd3(unsigned char *entry)
{
  if (entry[5] & 8)
    return entry - 0x18;
  return entry + (((unsigned int)*(unsigned short *)entry) << 4) - 0x10;
}
""",
    "void *__stdcall FUN_001d4dd3(void *entry);",
)


def merge_remote_ported() -> int:
    subprocess.run(
        ["git", "fetch", "pastudan", "track-a-collision-bsp"],
        cwd=ROOT,
        capture_output=True,
    )
    r = subprocess.run(
        ["git", "show", "pastudan/track-a-collision-bsp:kb.json"],
        cwd=ROOT,
        capture_output=True,
        text=True,
    )
    if r.returncode != 0:
        return 0
    remote = json.loads(r.stdout)
    local = json.loads(KB_PATH.read_text(encoding="utf-8"))
    remote_true = set()
    for o in remote.get("objects", []):
        for fn in o.get("functions") or []:
            if isinstance(fn, dict) and fn.get("ported") is True and fn.get("addr"):
                remote_true.add(int(fn["addr"], 16))
    n = 0
    for o in local.get("objects", []):
        for fn in o.get("functions") or []:
            if not isinstance(fn, dict) or not fn.get("addr"):
                continue
            a = int(fn["addr"], 16)
            if a in remote_true and fn.get("ported") is False:
                fn["ported"] = True
                n += 1
    if n:
        KB_PATH.write_text(json.dumps(local, indent=2) + "\n", encoding="utf-8")
        print(f"merged {n} remote ported:true", flush=True)
    return n


def commit_push(names: list[str]) -> None:
    merge_remote_ported()
    subprocess.run(
        ["git", "add", "kb.json", "src/halo", "tools/equivalence/leaf_cache.json"],
        cwd=ROOT,
        capture_output=True,
    )
    msg = f"lift(track-a): {', '.join(names[:6])} Unicorn-prove {len(names)}."
    r = subprocess.run(["git", "commit", "-m", msg], cwd=ROOT, capture_output=True, text=True)
    if r.returncode != 0:
        print("commit failed", r.stdout, r.stderr, flush=True)
        return
    # fetch/rebase then push
    subprocess.run(
        ["git", "fetch", "pastudan", "track-a-collision-bsp"],
        cwd=ROOT,
        capture_output=True,
    )
    subprocess.run(
        ["git", "rebase", "pastudan/track-a-collision-bsp"],
        cwd=ROOT,
        capture_output=True,
    )
    pr = subprocess.run(
        ["git", "push", "pastudan", "HEAD:track-a-collision-bsp"],
        cwd=ROOT,
        capture_output=True,
        text=True,
    )
    sys.stdout.write(pr.stdout or "")
    sys.stderr.write(pr.stderr or "")
    print(f"pushed: {msg}", flush=True)


def fix_tu_preflight() -> None:
    """Minimal compile blockers in target TUs."""
    # wcsncpy forward decls
    p = ROOT / "src/halo/libcmt/wcsncpy.c"
    t = p.read_text(encoding="utf-8")
    t2 = t.replace("void _memchr(void);", "void *_memchr(const void *s, int c, size_t n);")
    t2 = t2.replace(
        "wchar_t *FUN_001dc27c(wchar_t *s, size_t count);",
        "unsigned short FUN_001dc27c(unsigned short c);",
    )
    # stub body of _memchr if void _memchr(void) {
    t2 = re.sub(
        r"\nvoid _memchr\(void\)\n\{\n[\s\S]*?\n\}\n",
        "\nvoid *_memchr(const void *s, int c, size_t n)\n{\n  (void)s; (void)c; (void)n;\n  return 0;\n}\n",
        t2,
        count=1,
    )
    if t2 != t:
        p.write_text(t2, encoding="utf-8")
        print("preflight wcsncpy decls", flush=True)

    # close.c
    p = ROOT / "src/halo/libcmt/close.c"
    t = p.read_text(encoding="utf-8")
    t2 = t.replace("UnhandledExceptionFilter();", "UnhandledExceptionFilter(0);")
    t2 = t2.replace("void FUN_001e65eb(void);", "int FUN_001e65eb(int a0, void *tmp);")
    t2 = re.sub(
        r"\nvoid FUN_001e65eb\(void\)\n\{",
        "\nint FUN_001e65eb(int a0, void *tmp)\n{\n  (void)a0; (void)tmp;",
        t2,
        count=1,
    )
    if t2 != t:
        p.write_text(t2, encoding="utf-8")
        print("preflight close.c", flush=True)

    # lasterr ReadFile forward (undeclared in naked fnptrs)
    p = ROOT / "src/halo/xdk/xapilib/lasterr.c"
    t = p.read_text(encoding="utf-8")
    if "ReadFile(" in t and "extern int __stdcall ReadFile" not in t:
        insert = (
            "extern int __stdcall ReadFile(int handle, void *buffer, unsigned int size, "
            "unsigned int *bytes_read, void *overlapped);\n"
        )
        if t.startswith("/* kb"):
            nl = t.find("\n")
            t = t[: nl + 1] + insert + t[nl + 1 :]
        else:
            t = insert + t
        p.write_text(t, encoding="utf-8")
        print("preflight lasterr ReadFile", flush=True)

    # physmem — drop conflicting local protos include if present? skip heavy; try compile later
    # xvutil signatures fixed by lifts for 0c48; fix 0c65 forward if needed
    p = ROOT / "src/halo/xdk/xapilib/xvutil.c"
    t = p.read_text(encoding="utf-8")
    # If still naked with void FUN_001d0c65(void), replace signature in naked later via lift skip
    if "void *__stdcall FUN_001d0c65" not in t and "FUN_001d0c65" in t:
        t2 = t.replace(
            "__attribute__((naked, noinline))\nvoid FUN_001d0c65(void)",
            "__attribute__((naked, noinline))\nvoid *__stdcall FUN_001d0c65(void *ptr, int size, int flags)",
        )
        if t2 != t:
            p.write_text(t2, encoding="utf-8")
            print("preflight xvutil FUN_001d0c65 sig", flush=True)


def main() -> int:
    print("preflight...", flush=True)
    fix_tu_preflight()

    print("apply lifts...", flush=True)
    results = apply_lifts_flex(sorted(LIFTS.keys()))
    ok_lift = [r for r in results if r.get("ok")]
    print(f"lifted {len(ok_lift)}/{len(results)}", flush=True)
    for r in results:
        if not r.get("ok"):
            print(" lift-fail", r, flush=True)

    print("regen decl.h...", flush=True)
    r = subprocess.run(
        [
            sys.executable,
            str(ROOT / "tools/analysis/knowledge.py"),
            "--gen-header",
            str(ROOT / "build/generated/decl.h"),
        ],
        cwd=ROOT,
        capture_output=True,
        text=True,
    )
    if r.returncode != 0:
        print("regen FAIL", (r.stderr or r.stdout)[-500:], flush=True)
        return 1

    tus = sorted({LIFTS[a][0] for a in LIFTS})
    compile_ok = {}
    for src in tus:
        print("compile", src, flush=True)
        compile_ok[src] = docker_compile(src)
        if not compile_ok[src]:
            print("COMPILE FAIL", src, flush=True)

    lands: list[str] = []
    fails: list[dict] = []
    for addr in sorted(LIFTS.keys()):
        src, name, _body, _decl = LIFTS[addr]
        print(f"\n== prove {hex(addr)} {name} ==", flush=True)
        if not compile_ok.get(src):
            print(" skip compile-failed TU", flush=True)
            fails.append({"addr": hex(addr), "name": name, "err": "tu_compile"})
            continue
        kb0 = json.loads(KB_PATH.read_text(encoding="utf-8"))
        already = False
        for o in kb0.get("objects", []):
            for fn in o.get("functions") or []:
                if (
                    isinstance(fn, dict)
                    and fn.get("addr")
                    and int(fn["addr"], 16) == addr
                    and fn.get("ported") is True
                ):
                    already = True
        if already and name == "_wcschr":
            # re-prove after body fix
            already = False
        if already:
            print(" already ported:true", flush=True)
            continue
        if not ensure_oracle(addr):
            print(" oracle FAIL", flush=True)
            fails.append({"addr": hex(addr), "name": name, "err": "oracle"})
            continue
        t0 = time.time()
        res = run_unicorn(hex(addr), addr, SEEDS, timeout=TIMEOUT)
        if not clear_pass(res, SEEDS):
            res2 = run_unicorn(name, addr, SEEDS, timeout=TIMEOUT)
            if clear_pass(res2, SEEDS):
                res = res2
        print(
            f" {res.get('passed')}/{res.get('failed')}/{res.get('errors')} "
            f"dt={time.time()-t0:.1f} to={res.get('timeout')}",
            flush=True,
        )
        if not clear_pass(res, SEEDS):
            print(" FAIL", (res.get("tail") or "")[-350:], flush=True)
            fails.append(
                {
                    "addr": hex(addr),
                    "name": name,
                    "passed": res.get("passed"),
                    "failed": res.get("failed"),
                    "errors": res.get("errors"),
                }
            )
            continue
        kb = json.loads(KB_PATH.read_text(encoding="utf-8"))
        # allow flip even if already true (wcschr re-body)
        flipped = flip_kb(kb, addr)
        if not flipped:
            for o in kb.get("objects", []):
                for fn in o.get("functions") or []:
                    if isinstance(fn, dict) and fn.get("addr") and int(fn["addr"], 16) == addr:
                        fn["ported"] = True
                        flipped = True
        if not flipped:
            print(" flip miss", flush=True)
            fails.append({"addr": hex(addr), "name": name, "err": "flip"})
            continue
        KB_PATH.write_text(json.dumps(kb, indent=2) + "\n", encoding="utf-8")
        append_ledger(
            {
                "addr": hex(addr),
                "name": name,
                "source": src,
                "ok": True,
                "passed": res["passed"],
                "failed": 0,
                "errors": 0,
                "seeds": SEEDS,
                "phase": "grokB-solo-libxdk",
            }
        )
        lands.append(name)
        print(" FLIP", name, flush=True)

    t, f = count_ported(json.loads(KB_PATH.read_text(encoding="utf-8")))
    print(f"\nLANDS ({len(lands)}): {lands}", flush=True)
    print(f"FAILS ({len(fails)}): {fails}", flush=True)
    print(f"TIP {t}/{t+f} ({100 * t / (t + f):.2f}%)", flush=True)
    if lands:
        commit_push(lands)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
