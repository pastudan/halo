#!/usr/bin/env python3
"""Generate unicode.obj batch draft implementations + disassembly artifact."""
from __future__ import annotations

import json
import re
from pathlib import Path

from capstone import CS_ARCH_X86, CS_MODE_32, Cs
from xbe import Xbe

ROOT = Path(__file__).resolve().parents[1]
IMPL = ROOT / "tools" / "unicode_batch_impl.c"
FRAG = ROOT / "tools" / "unicode_batch_fragment.c"
DISASM_OUT = ROOT / "artifacts" / "unicode_batch_disasm.txt"
OBJECT = "unicode.obj"

DECLS = {
    "0x19d810": "int ustrcmp(const wchar_t *s1, const wchar_t *s2);",
    "0x19d8c0": "int ustrlen(const unsigned short *s);",
    "0x19d930": "size_t ustrnlen(const wchar_t *s, size_t max_len);",
    "0x19d9b0": "wchar_t *ustrchr(const wchar_t *s, wchar_t c);",
    "0x19da20": "int ustrcoll(const wchar_t *s1, const wchar_t *s2);",
    "0x19dad0": "size_t ustrcspn(const wchar_t *s, const wchar_t *reject);",
    "0x19db80": "wchar_t *ustrncat(wchar_t *dest, const wchar_t *src, size_t count);",
    "0x19dc20": "int ustrncmp(const wchar_t *s1, const wchar_t *s2, size_t count);",
    "0x19dd00": "wchar_t *ustrpbrk(const wchar_t *s, const wchar_t *accept);",
    "0x19ddb0": "wchar_t *ustrrchr(const wchar_t *s, wchar_t c);",
    "0x19de20": "size_t ustrspn(const wchar_t *s, const wchar_t *accept);",
    "0x19ded0": "wchar_t *ustrstr(const wchar_t *haystack, const wchar_t *needle);",
    "0x19df80": "wchar_t *ustrtok(wchar_t *s, const wchar_t *delim);",
    "0x19dff0": "size_t ustrxfrm(wchar_t *dest, const wchar_t *src, size_t count);",
    "0x19e0c0": "wchar_t *ustrlwr(wchar_t *s);",
    "0x19e130": "wchar_t *ustrupr(wchar_t *s);",
    "0x19e1a0": "wchar_t *ustrnlwr(wchar_t *s, size_t count);",
    "0x19e250": "wchar_t *ustrnupr(wchar_t *s, size_t count);",
    "0x19e300": "int ustrcasecmp(const wchar_t *s1, const wchar_t *s2);",
    "0x19e3b0": "int ustrncasecmp(const wchar_t *s1, const wchar_t *s2, size_t count);",
    "0x19e460": "int uisalpha(int c);",
    "0x19e480": "int uisupper(int c);",
    "0x19e4a0": "int uislower(int c);",
    "0x19e4c0": "int uisdigit(int c);",
    "0x19e4e0": "int uisxdigit(int c);",
    "0x19e500": "int uisspace(int c);",
    "0x19e520": "int uispunct(int c);",
    "0x19e540": "int uisalnum(int c);",
    "0x19e560": "int uisprint(int c);",
    "0x19e580": "int uisgraph(int c);",
    "0x19e5a0": "int uiscntrl(int c);",
    "0x19e5c0": "int utoupper(int c);",
    "0x19e5e0": "int utolower(int c);",
    "0x19e600": "int ufgetc(void *stream);",
    "0x19e640": "int ufputc(int c, void *stream);",
    "0x19e680": "int uungetc(int c, void *stream);",
    "0x19e6c0": "wchar_t *ufgets(wchar_t *buffer, int count, void *stream);",
    "0x19e760": "int ufputs(const wchar_t *s, void *stream);",
    "0x19e800": "wchar_t *ugets(wchar_t *buffer);",
    "0x19e870": "int uputs(const wchar_t *s);",
    "0x19e8e0": "int ufprintf(void *stream, const wchar_t *format, ...);",
    "0x19e980": "int uprintf(const wchar_t *format, ...);",
    "0x19eaa0": "int usprintf(wchar_t *buffer, const wchar_t *format, ...);",
    "0x19eb50": "int uvfprintf(void *stream, const wchar_t *format, char *args);",
    "0x19ebd0": "int uvprintf(const wchar_t *format, char *args);",
    "0x19ec40": "int uvsnprintf(wchar_t *buffer, size_t count, const wchar_t *format, char *args);",
    "0x19ecf0": "int uvsprintf(wchar_t *buffer, const wchar_t *format, char *args);",
    "0x19eda0": "void *ufdopen(int fd, const wchar_t *mode);",
    "0x19ee40": "void *ufopen(const wchar_t *path, const wchar_t *mode);",
    "0x19eee0": "int ufclose(void *stream);",
    "0x19ef20": "void *ufreopen(const wchar_t *path, const wchar_t *mode, void *stream);",
    "0x19efd0": "void uperror(const wchar_t *prefix);",
    "0x19f040": "void *upopen(const wchar_t *command, const wchar_t *mode);",
    "0x19f0e0": "int uremove(const wchar_t *path);",
    "0x19f150": "wchar_t *utmpnam(wchar_t *buffer);",
    "0x19f160": "long ustrtol(const wchar_t *s, wchar_t **endptr, int base);",
    "0x19f1d0": "unsigned long ustrtoul(const wchar_t *s, wchar_t **endptr, int base);",
    "0x19f240": "double ustrtod(const wchar_t *s, wchar_t **endptr);",
    "0x19f2b0": "int uatoi(const wchar_t *s);",
    "0x19f320": "wchar_t *uctime(const void *timeptr);",
    "0x19f360": "wchar_t *uasctime(const void *timeptr);",
    "0x19f4f0": "wchar_t *FUN_0019f4f0(int param);",
    "0x19f530": "uint8_t FUN_0019f530(int unit_handle);",
    "0x19f540": "char biped_limp_noodle_valid_joint_rotation(int unit_handle, int16_t node_index, void *node_block);",
    "0x19fa20": "void FUN_0019fa20(int unit_handle, void *node_block);",
}


def write_disasm() -> None:
    xbe = Xbe.from_file(str(ROOT / "halo-patched/cachebeta.xbe"))
    md = Cs(CS_ARCH_X86, CS_MODE_32)
    kb = json.loads((ROOT / "kb.json").read_text())
    obj = next(o for o in kb["objects"] if o["name"] == OBJECT)
    fns = sorted(obj["functions"], key=lambda f: int(f["addr"], 16))
    addrs = [(int(f["addr"], 16), f) for f in fns]
    addr_name: dict[int, str] = {}
    for o in kb["objects"]:
        for f in o.get("functions", []):
            m = re.search(r"([A-Za-z_][A-Za-z0-9_]*)\s*\(", f.get("decl") or "")
            if m:
                addr_name[int(f["addr"], 16)] = m.group(1)

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
        data = get_bytes(va, min(end, va + 0x3000))
        insns = list(md.disasm(data, va))
        trimmed = []
        for ins in insns:
            if ins.address >= end:
                break
            trimmed.append(ins)
        name = re.search(r"([A-Za-z_][A-Za-z0-9_]*)\s*\(", DECLS.get(f["addr"], ""))
        label = name.group(1) if name else f["addr"]
        lines.append(
            f"\n=== {label} @ {f['addr']} end~{end:08x} insns={len(trimmed)} ==="
        )
        for ins in trimmed[:400]:
            line = f"  {ins.address:08x}: {ins.mnemonic:<8} {ins.op_str}"
            if ins.mnemonic == "call" and ins.op_str.startswith("0x"):
                tgt = ins.op_str.split()[0]
                try:
                    t = int(tgt, 16)
                    line += f"  ; {addr_name.get(t, tgt)}"
                except ValueError:
                    pass
            lines.append(line)
        if len(trimmed) > 400:
            lines.append(f"  ... ({len(trimmed) - 400} more insns)")
    DISASM_OUT.parent.mkdir(parents=True, exist_ok=True)
    DISASM_OUT.write_text("\n".join(lines) + "\n")
    print(f"wrote {DISASM_OUT} ({len(lines)} lines)")


def gen_impl() -> str:
    return r'''/* --- unicode.obj batch drafts (2026-07-26) --- */

static void unicode_assert_string(const wchar_t *s)
{
  assert_halt(s);
  assert_halt(_wcslen(s) < 0x8000);
}

static void unicode_assert_two_strings(const wchar_t *a, const wchar_t *b)
{
  assert_halt(a && b);
  assert_halt(_wcslen(a) < 0x8000);
  assert_halt(_wcslen(b) < 0x8000);
}

static void unicode_assert_count(size_t count)
{
  assert_halt(count < 0x8000);
}

/* 0x19d810 */
int ustrcmp(const wchar_t *s1, const wchar_t *s2)
{
  unicode_assert_two_strings(s1, s2);
  return _wcscmp(s1, s2);
}

/* 0x19d8c0 */
int ustrlen(const unsigned short *s)
{
  int len;

  assert_halt(s);
  len = (int)_wcslen((const wchar_t *)s);
  assert_halt(len < 0x8000);
  return len;
}

/* 0x19d930 */
size_t ustrnlen(const wchar_t *s, size_t max_len)
{
  size_t n;

  assert_halt(s);
  n = 0;
  while (n < max_len && s[n] != 0)
    n++;
  assert_halt(n < 0x8000);
  return n;
}

/* 0x19d9b0 */
wchar_t *ustrchr(const wchar_t *s, wchar_t c)
{
  unicode_assert_string(s);
  return _wcschr(s, c);
}

/* 0x19da20 */
int ustrcoll(const wchar_t *s1, const wchar_t *s2)
{
  unicode_assert_two_strings(s1, s2);
  return FUN_001dbfa7(s1, s2);
}

/* 0x19dad0 */
size_t ustrcspn(const wchar_t *s, const wchar_t *reject)
{
  unicode_assert_two_strings(s, reject);
  return _wcscspn(s, reject);
}

/* 0x19db80 */
wchar_t *ustrncat(wchar_t *dest, const wchar_t *src, size_t count)
{
  assert_halt(dest && src);
  unicode_assert_string(dest);
  unicode_assert_count(count);
  return _wcsncat(dest, src, count);
}

/* 0x19dc20 */
int ustrncmp(const wchar_t *s1, const wchar_t *s2, size_t count)
{
  assert_halt(s1 && s2);
  unicode_assert_count(count);
  return _wcsncmp(s1, s2, count);
}

/* 0x19dd00 */
wchar_t *ustrpbrk(const wchar_t *s, const wchar_t *accept)
{
  unicode_assert_two_strings(s, accept);
  return _wcspbrk(s, accept);
}

/* 0x19ddb0 */
wchar_t *ustrrchr(const wchar_t *s, wchar_t c)
{
  unicode_assert_string(s);
  return _wcsrchr(s, c);
}

/* 0x19de20 */
size_t ustrspn(const wchar_t *s, const wchar_t *accept)
{
  unicode_assert_two_strings(s, accept);
  return _wcsspn(s, accept);
}

/* 0x19ded0 */
wchar_t *ustrstr(const wchar_t *haystack, const wchar_t *needle)
{
  unicode_assert_two_strings(haystack, needle);
  return _wcsstr(haystack, needle);
}

/* 0x19df80 */
wchar_t *ustrtok(wchar_t *s, const wchar_t *delim)
{
  unicode_assert_string(s);
  return _wcstok(s, delim);
}

/* 0x19dff0 */
size_t ustrxfrm(wchar_t *dest, const wchar_t *src, size_t count)
{
  assert_halt(dest && src);
  unicode_assert_string(src);
  unicode_assert_count(count);
  return FUN_001dc257(dest, src, count);
}

/* 0x19e0c0 */
wchar_t *ustrlwr(wchar_t *s)
{
  unicode_assert_string(s);
  return FUN_001e6805(s);
}

/* 0x19e130 */
wchar_t *ustrupr(wchar_t *s)
{
  unicode_assert_string(s);
  return FUN_001e6831(s);
}

/* 0x19e1a0 */
wchar_t *ustrnlwr(wchar_t *s, size_t count)
{
  assert_halt(s);
  unicode_assert_count(count);
  return FUN_001dc27c(s, count);
}

/* 0x19e250 */
wchar_t *ustrnupr(wchar_t *s, size_t count)
{
  assert_halt(s);
  unicode_assert_count(count);
  return FUN_001da8e3(s, count);
}

/* 0x19e300 */
int ustrcasecmp(const wchar_t *s1, const wchar_t *s2)
{
  unicode_assert_two_strings(s1, s2);
  return __wcsicmp(s1, s2);
}

/* 0x19e3b0 */
int ustrncasecmp(const wchar_t *s1, const wchar_t *s2, size_t count)
{
  unicode_assert_two_strings(s1, s2);
  return __wcsnicmp(s1, s2, count);
}

/* 0x19e460 */
int uisalpha(int c)
{
  return FUN_001dc3e9(c, 0x103);
}

/* 0x19e480 */
int uisupper(int c)
{
  return FUN_001dc3e9(c, 1);
}

/* 0x19e4a0 */
int uislower(int c)
{
  return FUN_001dc3e9(c, 2);
}

/* 0x19e4c0 */
int uisdigit(int c)
{
  return FUN_001dc3e9(c, 4);
}

/* 0x19e4e0 */
int uisxdigit(int c)
{
  return FUN_001dc3e9(c, 0x80);
}

/* 0x19e500 */
int uisspace(int c)
{
  return FUN_001dc3e9(c, 8);
}

/* 0x19e520 */
int uispunct(int c)
{
  return FUN_001dc3e9(c, 0x10);
}

/* 0x19e540 */
int uisalnum(int c)
{
  return FUN_001dc3e9(c, 0x107);
}

/* 0x19e560 */
int uisprint(int c)
{
  return FUN_001dc3e9(c, 0x100);
}

/* 0x19e580 */
int uisgraph(int c)
{
  return FUN_001dc3e9(c, 0x117);
}

/* 0x19e5a0 */
int uiscntrl(int c)
{
  return FUN_001dc3e9(c, 0x20);
}

/* 0x19e5c0 */
int utoupper(int c)
{
  wchar_t ch;

  ch = (wchar_t)c;
  FUN_001dc27c(&ch, 1);
  return (int)(unsigned short)ch;
}

/* 0x19e5e0 */
int utolower(int c)
{
  wchar_t ch;

  ch = (wchar_t)c;
  FUN_001da8e3(&ch, 1);
  return (int)(unsigned short)ch;
}

/* 0x19e600 */
int ufgetc(void *stream)
{
  assert_halt(stream);
  return _fgetwc(stream);
}

/* 0x19e640 */
int ufputc(int c, void *stream)
{
  assert_halt(stream);
  return _fputwc(c, stream);
}

/* 0x19e680 */
int uungetc(int c, void *stream)
{
  assert_halt(stream);
  return _ungetwc(c, stream);
}

/* 0x19e6c0 */
wchar_t *ufgets(wchar_t *buffer, int count, void *stream)
{
  assert_halt(buffer && stream);
  assert_halt(count > 0 && count <= 0x8000);
  return _fgetws(buffer, count, stream);
}

/* 0x19e760 */
int ufputs(const wchar_t *s, void *stream)
{
  assert_halt(s && stream);
  unicode_assert_string(s);
  return _fputws(s, stream);
}

/* 0x19e800 */
wchar_t *ugets(wchar_t *buffer)
{
  assert_halt(buffer);
  return __getws(buffer);
}

/* 0x19e870 */
int uputs(const wchar_t *s)
{
  unicode_assert_string(s);
  return __putws(s);
}

/* 0x19e8e0 */
int ufprintf(void *stream, const wchar_t *format, ...)
{
  va_list args;
  int result;

  assert_halt(stream && format);
  unicode_assert_string(format);
  va_start(args, format);
  result = _vfwprintf(stream, format, (char *)args);
  va_end(args);
  return result;
}

/* 0x19e980 */
int uprintf(const wchar_t *format, ...)
{
  va_list args;
  int result;

  unicode_assert_string(format);
  va_start(args, format);
  result = _vprintf(format, (char *)args);
  va_end(args);
  return result;
}

/* 0x19eaa0 */
int usprintf(wchar_t *buffer, const wchar_t *format, ...)
{
  va_list args;
  int result;

  assert_halt(buffer && format);
  unicode_assert_string(buffer);
  unicode_assert_string(format);
  va_start(args, format);
  result = FUN_001dcace(buffer, format, (char *)args);
  va_end(args);
  return result;
}

/* 0x19eb50 */
int uvfprintf(void *stream, const wchar_t *format, char *args)
{
  assert_halt(stream && format);
  unicode_assert_string(format);
  return _vfwprintf(stream, format, args);
}

/* 0x19ebd0 */
int uvprintf(const wchar_t *format, char *args)
{
  unicode_assert_string(format);
  return _vprintf(format, args);
}

/* 0x19ec40 */
int uvsnprintf(wchar_t *buffer, size_t count, const wchar_t *format, char *args)
{
  assert_halt(buffer && format);
  unicode_assert_string(format);
  unicode_assert_count(count);
  return _vsnwprintf(buffer, count, format, args);
}

/* 0x19ecf0 */
int uvsprintf(wchar_t *buffer, const wchar_t *format, char *args)
{
  assert_halt(buffer && format);
  unicode_assert_string(buffer);
  unicode_assert_string(format);
  return FUN_001dcace(buffer, format, args);
}

/* 0x19eda0 */
void *ufdopen(int fd, const wchar_t *mode)
{
  assert_halt(mode);
  unicode_assert_string(mode);
  return FUN_001dcb6c(fd, mode);
}

/* 0x19ee40 */
void *ufopen(const wchar_t *path, const wchar_t *mode)
{
  unicode_assert_two_strings(path, mode);
  return FUN_001dccf5(path, mode);
}

/* 0x19eee0 */
int ufclose(void *stream)
{
  assert_halt(stream);
  return crt_fclose(stream);
}

/* 0x19ef20 */
void *ufreopen(const wchar_t *path, const wchar_t *mode, void *stream)
{
  assert_halt(stream);
  unicode_assert_two_strings(path, mode);
  return __wfreopen(path, mode, stream);
}

/* 0x19efd0 */
void uperror(const wchar_t *prefix)
{
  unicode_assert_string(prefix);
  FUN_001dcd6e(prefix);
}

/* 0x19f040 */
void *upopen(const wchar_t *command, const wchar_t *mode)
{
  unicode_assert_two_strings(command, mode);
  assert_halt(_wcslen(mode) < 4);
  return NULL;
}

/* 0x19f0e0 */
int uremove(const wchar_t *path)
{
  unicode_assert_string(path);
  return FUN_001dce6e(path);
}

/* 0x19f150 */
wchar_t *utmpnam(wchar_t *buffer)
{
  return FUN_001dcf51(buffer);
}

/* 0x19f160 */
long ustrtol(const wchar_t *s, wchar_t **endptr, int base)
{
  unicode_assert_string(s);
  return FUN_001dd1d1(s, endptr, base);
}

/* 0x19f1d0 */
unsigned long ustrtoul(const wchar_t *s, wchar_t **endptr, int base)
{
  unicode_assert_string(s);
  return FUN_001dd1e8(s, endptr, base);
}

/* 0x19f240 */
double ustrtod(const wchar_t *s, wchar_t **endptr)
{
  unicode_assert_string(s);
  return FUN_001dd1ff(s, endptr);
}

/* 0x19f2b0 */
int uatoi(const wchar_t *s)
{
  unicode_assert_string(s);
  return FUN_001dd3d4(s);
}

/* 0x19f320 */
wchar_t *uctime(const void *timeptr)
{
  assert_halt(timeptr);
  return __wctime(timeptr);
}

/* 0x19f360 */
wchar_t *uasctime(const void *timeptr)
{
  assert_halt(timeptr);
  return __wasctime(timeptr);
}

/* 0x19f4f0 */
wchar_t *FUN_0019f4f0(int param)
{
  *(uint16_t *)0x4d9be8 = 0;
  FUN_001dd576(param);
  usprintf((wchar_t *)0x4d9be8, (const wchar_t *)0x2b4af4, param);
  return (wchar_t *)0x4d9be8;
}

/* 0x19f530 */
uint8_t FUN_0019f530(int unit_handle)
{
  return 0x14;
}

/* 0x19f540 — biped_limp_noodle_valid_joint_rotation (large; stub draft) */
char biped_limp_noodle_valid_joint_rotation(int unit_handle, int16_t node_index,
                                            void *node_block)
{
  (void)unit_handle;
  (void)node_index;
  (void)node_block;
  return 0;
}

/* 0x19fa20 — unit animation node setup (large; stub draft) */
void FUN_0019fa20(int unit_handle, void *node_block)
{
  (void)unit_handle;
  (void)node_block;
}
'''


def main() -> None:
    write_disasm()
    text = gen_impl()
    IMPL.write_text(text)
    FRAG.write_text(text)
    print(f"wrote {IMPL} ({len(DECLS)} drafts)")


if __name__ == "__main__":
    main()
