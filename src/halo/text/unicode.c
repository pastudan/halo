#include <stdarg.h>

wchar_t *ustrncpy(wchar_t *dest, wchar_t *src, size_t count)
{
  assert_halt(dest && src);
  assert_halt(count < 0x8000);
  _wcsncpy(dest, src, count);
  return dest;
}

/* unicode_sprintf — bounded wide-char printf.
 * Validates buffer, buffer_size in (0, 0x8000], and wcslen(format) < 0x8000,
 * then forwards to the CRT _vsnwprintf with the caller's va_list. */
void unicode_sprintf(wchar_t *buffer, int buffer_size, const wchar_t *format,
                     ...)
{
  va_list args;

  assert_halt(buffer);
  assert_halt((unsigned int)buffer_size > 0 &&
              (unsigned int)buffer_size <= 0x8000);
  assert_halt(_wcslen(format) < 0x8000);

  va_start(args, format);
  _vsnwprintf(buffer, buffer_size, format, (char *)args);
  va_end(args);
}

/* wide_to_ascii — convert a wide string to an ASCII byte string.
 * Returns NULL if the string won't fit in the buffer or contains
 * any non-ASCII characters (code points >= 0x80). Otherwise copies
 * the low byte of each wide character and null-terminates the result. */
char *wide_to_ascii(const wchar_t *unicode, char *ascii, int size)
{
  unsigned int length;
  unsigned int i;

  assert_halt(unicode && ascii);
  length = _wcslen(unicode);
  assert_halt(length < 0x8000);

  if (length > (unsigned int)(size - 1))
    return NULL;

  for (i = 0; i < length; i++) {
    if ((unicode[i] & 0xFF80) != 0)
      return NULL;
  }

  for (i = 0; i < length; i++) {
    ascii[i] = (char)unicode[i];
  }

  ascii[i] = '\0';
  return ascii;
}

wchar_t *ascii_to_wide(const char *ascii, wchar_t *unicode, size_t length)
{
  int len;
  int i;

  assert_halt(ascii && unicode);
  len = csstrlen(ascii);
  assert_halt(len < 0x8000);

  if (length < (size_t)(len * 2 + 2))
    return NULL;

  unicode[len] = 0;
  for (i = len - 1; i >= 0; i--)
    unicode[i] = (int16_t)ascii[i];

  return unicode;
}
/* --- unicode.obj batch drafts (2026-07-26) --- */

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

/* 0x19f540 — validate/snap a limp-noodle joint against parent bone limits. */
#if defined(__clang__)
static float (*const bln_norm)(float *) = normalize3d;
static void (*const bln_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const bln_exitfn)(int) = system_exit;
static void (*const bln_d99490)(float *, float *, float *) = FUN_00099490;
static void (*const bln_minv)(float *, float *) = matrix_inverse;
static void (*const bln_mscale)(float *, float *, float *) = matrix_scale_transform_vector;
static void (*const bln_rots)(float *, float *, float, float) = rotate_vector3d_by_sincos;
static void *(*const bln_get)(int, int) = object_get_and_verify_type;
static char (*const bln_c4dab0)(int, int) = FUN_0014dab0;
static void *(*const bln_elem)(void *, int, int) = tag_block_get_element;
static void *(*const bln_tag)(int, int) = tag_get;
static void (*const bln_ffloor)(void) = FUN_001d94f0;

__attribute__((naked, noinline))
char biped_limp_noodle_valid_joint_rotation(int unit_handle __attribute__((unused)), short node_index __attribute__((unused)), void *node_block __attribute__((unused)), float *out_pos __attribute__((unused)), unsigned int *visited_bits __attribute__((unused)), float *candidate_pos __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xe4, %%esp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "pushl $1\n\t"
      "pushl %%eax\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "call *%[get]\n\t"
      "movl (%%eax), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x62697064\n\t"
      "call *%[tag]\n\t"
      "movl 0x44(%%eax), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x616e7472\n\t"
      "call *%[tag]\n\t"
      "movl %%eax, %%edi\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "pushl $0x40\n\t"
      "pushl %%eax\n\t"
      "leal 0x68(%%edi), %%ebx\n\t"
      "pushl %%ebx\n\t"
      "call *%[elem]\n\t"
      "movswl 0x24(%%eax), %%ecx\n\t"
      "pushl $0x40\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "movl %%eax, -0x28(%%ebp)\n\t"
      "call *%[elem]\n\t"
      "movl %%eax, %%edx\n\t"
      "movl 0x60(%%edi), %%eax\n\t"
      "movl %%eax, -0x24(%%ebp)\n\t"
      "addl $0x30, %%esp\n\t"
      "flds -0x24(%%ebp)\n\t"
      "movl %%edx, -0x2c(%%ebp)\n\t"
      "fabs\n\t"
      "fcompl 0x2533d0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .Lbiped_limp_noodle_valid_joint_rotation_1\n\t"
      "flds -0x24(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .Lbiped_limp_noodle_valid_joint_rotation_1\n\t"
      "flds -0x24(%%ebp)\n\t"
      "fcomps 0x2b4b74\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lbiped_limp_noodle_valid_joint_rotation_2\n\t"
      ".Lbiped_limp_noodle_valid_joint_rotation_1:\n\t"
      "movl $0x3cf5c28f, -0x24(%%ebp)\n\t"
      ".Lbiped_limp_noodle_valid_joint_rotation_2:\n\t"
      "movl -0x28(%%ebp), %%ecx\n\t"
      "movw 0x24(%%ecx), %%cx\n\t"
      "testw %%cx, %%cx\n\t"
      "je .Lbiped_limp_noodle_valid_joint_rotation_6\n\t"
      "testb $4, 0x28(%%edx)\n\t"
      "jne .Lbiped_limp_noodle_valid_joint_rotation_6\n\t"
      "movl 0xc(%%ebp), %%ebx\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "movswl %%cx, %%ecx\n\t"
      "movl %%ebx, %%eax\n\t"
      "imull $0x34, %%ecx, %%ecx\n\t"
      "imull $0x34, %%eax, %%eax\n\t"
      "flds 0x28(%%eax,%%edx,1)\n\t"
      "fsubs 0x28(%%ecx,%%edx,1)\n\t"
      "fstps -0x1c(%%ebp)\n\t"
      "flds 0x2c(%%eax,%%edx,1)\n\t"
      "fsubs 0x2c(%%ecx,%%edx,1)\n\t"
      "leal (%%ecx,%%edx,1), %%edi\n\t"
      "leal 0x28(%%eax,%%edx,1), %%eax\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "leal -0x1c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "flds 0x8(%%eax)\n\t"
      "fsubs 0x30(%%edi)\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "flds (%%esi)\n\t"
      "fsubs 0x28(%%edi)\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "flds 0x4(%%esi)\n\t"
      "fsubs 0x2c(%%edi)\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "flds 0x8(%%esi)\n\t"
      "fsubs 0x30(%%edi)\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "call *%[norm]\n\t"
      "leal -0x10(%%ebp), %%eax\n\t"
      "fstp %%st(0)\n\t"
      "pushl %%eax\n\t"
      "call *%[norm]\n\t"
      "fstp %%st(0)\n\t"
      "flds -0x8(%%ebp)\n\t"
      "leal -0x58(%%ebp), %%ecx\n\t"
      "fmuls -0x18(%%ebp)\n\t"
      "pushl %%ecx\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fmuls -0x14(%%ebp)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0x58(%%ebp)\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fmuls -0x10(%%ebp)\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fmuls -0x1c(%%ebp)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0x54(%%ebp)\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fmuls -0x1c(%%ebp)\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fmuls -0x10(%%ebp)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0x50(%%ebp)\n\t"
      "call *%[norm]\n\t"
      "fstp %%st(0)\n\t"
      "flds -0x8(%%ebp)\n\t"
      "addl $0xc, %%esp\n\t"
      "fmuls -0x14(%%ebp)\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fmuls -0x18(%%ebp)\n\t"
      "faddp %%st(1)\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fmuls -0x1c(%%ebp)\n\t"
      "faddp %%st(1)\n\t"
      "fsts -0x20(%%ebp)\n\t"
      "fsubs 0x2533c8\n\t"
      "fabs\n\t"
      "fcompl 0x2533d0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .Lbiped_limp_noodle_valid_joint_rotation_7\n\t"
      "flds -0x20(%%ebp)\n\t"
      "call *%[ffloor]\n\t"
      "fstps -0x4c(%%ebp)\n\t"
      "leal -0xb0(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "call *%[minv]\n\t"
      "movl -0x2c(%%ebp), %%edi\n\t"
      "movswl 0x24(%%edi), %%ecx\n\t"
      "imull $0x34, %%ecx, %%ecx\n\t"
      "leal -0xe4(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "addl 0x10(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[minv]\n\t"
      "leal -0x7c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x58(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0xb0(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[mscale]\n\t"
      "movl -0x28(%%ebp), %%edx\n\t"
      "movswl 0x24(%%edx), %%eax\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "imull $0x34, %%eax, %%eax\n\t"
      "leal 0x4(%%eax,%%ecx,1), %%edx\n\t"
      "movl (%%edx), %%eax\n\t"
      "movl %%eax, -0x1c(%%ebp)\n\t"
      "movl 0x4(%%edx), %%ecx\n\t"
      "movl %%ecx, -0x18(%%ebp)\n\t"
      "movl 0x8(%%edx), %%edx\n\t"
      "leal -0x1c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x1c(%%ebp), %%ecx\n\t"
      "movl %%edx, -0x14(%%ebp)\n\t"
      "pushl %%ecx\n\t"
      "leal -0xe4(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[mscale]\n\t"
      "movb 0x28(%%edi), %%al\n\t"
      "addl $0x28, %%esp\n\t"
      "testb $2, %%al\n\t"
      "je .Lbiped_limp_noodle_valid_joint_rotation_5\n\t"
      "movl -0x28(%%ebp), %%eax\n\t"
      "movswl 0x24(%%eax), %%ecx\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "imull $0x34, %%ecx, %%ecx\n\t"
      "leal (%%ecx,%%edx,1), %%eax\n\t"
      "leal 0x1c(%%eax), %%ecx\n\t"
      "movl (%%ecx), %%edx\n\t"
      "movl %%edx, -0x38(%%ebp)\n\t"
      "movl 0x4(%%ecx), %%edx\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "movl %%edx, -0x34(%%ebp)\n\t"
      "leal -0x38(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "addl $0x28, %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x48(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl %%ecx, -0x30(%%ebp)\n\t"
      "call *%[d99490]\n\t"
      "addl $0xc, %%esp\n\t"
      "flds -0x44(%%ebp)\n\t"
      "fmuls 0x4(%%esi)\n\t"
      "flds -0x40(%%ebp)\n\t"
      "fmuls 0x8(%%esi)\n\t"
      "faddp %%st(1)\n\t"
      "flds -0x48(%%ebp)\n\t"
      "fmuls (%%esi)\n\t"
      "faddp %%st(1)\n\t"
      "fsubs -0x3c(%%ebp)\n\t"
      "fmuls 0x255e94\n\t"
      "flds -0x38(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fadds (%%esi)\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "flds -0x34(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fadds 0x4(%%esi)\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "flds -0x30(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fadds 0x8(%%esi)\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fmuls -0x44(%%ebp)\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fmuls -0x48(%%ebp)\n\t"
      "faddp %%st(1)\n\t"
      "flds -0x40(%%ebp)\n\t"
      "fmuls -0x8(%%ebp)\n\t"
      "faddp %%st(1)\n\t"
      "fsubs -0x3c(%%ebp)\n\t"
      "fabs\n\t"
      "fcompl 0x2533d0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .Lbiped_limp_noodle_valid_joint_rotation_3\n\t"
      "pushl $1\n\t"
      "pushl $0xe7\n\t"
      "pushl $0x2b4b48\n\t"
      "pushl $0x2b4b00\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lbiped_limp_noodle_valid_joint_rotation_3:\n\t"
      "movl -0x28(%%ebp), %%ecx\n\t"
      "flds -0x10(%%ebp)\n\t"
      "movswl 0x24(%%ecx), %%edx\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "imull $0x34, %%edx, %%edx\n\t"
      "fsubs 0x28(%%edx,%%eax,1)\n\t"
      "fstps -0x64(%%ebp)\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fsubs 0x2c(%%edx,%%eax,1)\n\t"
      "leal 0x28(%%edx,%%eax,1), %%eax\n\t"
      "fstps -0x60(%%ebp)\n\t"
      "flds -0x8(%%ebp)\n\t"
      "leal -0x64(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "fsubs 0x8(%%eax)\n\t"
      "fstps -0x5c(%%ebp)\n\t"
      "call *%[norm]\n\t"
      "leal -0x70(%%ebp), %%edx\n\t"
      "fstp %%st(0)\n\t"
      "pushl %%edx\n\t"
      "leal -0x64(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0xb0(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[mscale]\n\t"
      "flds -0x6c(%%ebp)\n\t"
      "fmuls 0x30(%%edi)\n\t"
      "addl $0x10, %%esp\n\t"
      "flds -0x68(%%ebp)\n\t"
      "fmuls 0x34(%%edi)\n\t"
      "faddp %%st(1)\n\t"
      "flds -0x70(%%ebp)\n\t"
      "fmuls 0x2c(%%edi)\n\t"
      "movl 0x14(%%ebp), %%edi\n\t"
      "faddp %%st(1)\n\t"
      "fsubs 0x2533c8\n\t"
      "fabs\n\t"
      "fcompl 0x2533d0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .Lbiped_limp_noodle_valid_joint_rotation_8\n\t"
      "movl 0x18(%%ebp), %%eax\n\t"
      "movl %%ebx, %%edx\n\t"
      "sarl $5, %%edx\n\t"
      "leal (%%eax,%%edx,4), %%eax\n\t"
      "movl %%ebx, %%ecx\n\t"
      "andl $0x1f, %%ecx\n\t"
      "movl $1, %%edx\n\t"
      "shll %%cl, %%edx\n\t"
      "movl (%%eax), %%ecx\n\t"
      "orl %%edx, %%ecx\n\t"
      "movl %%ecx, (%%eax)\n\t"
      "flds 0x8(%%edi)\n\t"
      "fcomps -0x8(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .Lbiped_limp_noodle_valid_joint_rotation_4\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl -0x24(%%ebp), %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "leal -0x10(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c4dab0]\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lbiped_limp_noodle_valid_joint_rotation_4\n\t"
      "movl -0x10(%%ebp), %%ecx\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "movl %%edi, %%eax\n\t"
      "movl %%ecx, (%%eax)\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movl %%edx, 0x4(%%eax)\n\t"
      "movl %%ecx, 0x8(%%eax)\n\t"
      ".Lbiped_limp_noodle_valid_joint_rotation_4:\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "jmp .Lbiped_limp_noodle_valid_joint_rotation_8\n\t"
      ".Lbiped_limp_noodle_valid_joint_rotation_5:\n\t"
      "flds -0x4c(%%ebp)\n\t"
      "movl -0x20(%%ebp), %%edx\n\t"
      "fsin\n\t"
      "pushl %%edx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x7c(%%ebp), %%eax\n\t"
      "leal -0x1c(%%ebp), %%ecx\n\t"
      "fstps (%%esp)\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[rots]\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fmuls 0x30(%%edi)\n\t"
      "addl $0x10, %%esp\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fmuls 0x34(%%edi)\n\t"
      "faddp %%st(1)\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fmuls 0x2c(%%edi)\n\t"
      "faddp %%st(1)\n\t"
      "fsts -0x20(%%ebp)\n\t"
      "fsubs 0x2533c8\n\t"
      "fabs\n\t"
      "fcompl 0x2533d0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .Lbiped_limp_noodle_valid_joint_rotation_7\n\t"
      "flds -0x20(%%ebp)\n\t"
      "call *%[ffloor]\n\t"
      "fabs\n\t"
      "flds 0x38(%%edi)\n\t"
      "fcompp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lbiped_limp_noodle_valid_joint_rotation_7\n\t"
      "movl 0x14(%%ebp), %%edx\n\t"
      "flds 0x8(%%edx)\n\t"
      "fcomps 0x8(%%esi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lbiped_limp_noodle_valid_joint_rotation_7\n\t"
      "movl 0x18(%%ebp), %%ecx\n\t"
      "movl %%ebx, %%eax\n\t"
      "sarl $5, %%eax\n\t"
      "leal (%%ecx,%%eax,4), %%eax\n\t"
      "movl %%ebx, %%ecx\n\t"
      "andl $0x1f, %%ecx\n\t"
      "movl $1, %%edx\n\t"
      "shll %%cl, %%edx\n\t"
      "movl (%%eax), %%ecx\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "orl %%edx, %%ecx\n\t"
      "movl %%ecx, (%%eax)\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      "movl %%esi, %%eax\n\t"
      "movl (%%eax), %%edx\n\t"
      "movl %%edx, (%%ecx)\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl %%edx, 0x4(%%ecx)\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl %%eax, 0x8(%%ecx)\n\t"
      "jmp .Lbiped_limp_noodle_valid_joint_rotation_7\n\t"
      ".Lbiped_limp_noodle_valid_joint_rotation_6:\n\t"
      "movl 0xc(%%ebp), %%ebx\n\t"
      ".Lbiped_limp_noodle_valid_joint_rotation_7:\n\t"
      "movl 0x14(%%ebp), %%edi\n\t"
      ".Lbiped_limp_noodle_valid_joint_rotation_8:\n\t"
      "movl -0x2c(%%ebp), %%ecx\n\t"
      "testb $4, 0x28(%%ecx)\n\t"
      "jne .Lbiped_limp_noodle_valid_joint_rotation_9\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lbiped_limp_noodle_valid_joint_rotation_11\n\t"
      ".Lbiped_limp_noodle_valid_joint_rotation_9:\n\t"
      "movl -0x28(%%ebp), %%edx\n\t"
      "movswl 0x24(%%edx), %%eax\n\t"
      "movl %%eax, %%ecx\n\t"
      "andl $0x1f, %%ecx\n\t"
      "movl $1, %%edx\n\t"
      "shll %%cl, %%edx\n\t"
      "movl 0x18(%%ebp), %%ecx\n\t"
      "sarl $5, %%eax\n\t"
      "testl %%edx, (%%ecx,%%eax,4)\n\t"
      "je .Lbiped_limp_noodle_valid_joint_rotation_10\n\t"
      "flds 0x8(%%edi)\n\t"
      "fcomps 0x8(%%esi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lbiped_limp_noodle_valid_joint_rotation_10\n\t"
      "movl %%ebx, %%eax\n\t"
      "sarl $5, %%eax\n\t"
      "leal (%%ecx,%%eax,4), %%eax\n\t"
      "movl %%ebx, %%ecx\n\t"
      "andl $0x1f, %%ecx\n\t"
      "movl $1, %%edx\n\t"
      "shll %%cl, %%edx\n\t"
      "orl %%edx, (%%eax)\n\t"
      "movl (%%esi), %%eax\n\t"
      "movl %%eax, (%%edi)\n\t"
      "movl 0x4(%%esi), %%ecx\n\t"
      "movl %%ecx, 0x4(%%edi)\n\t"
      "movl 0x8(%%esi), %%edx\n\t"
      "movl %%edx, 0x8(%%edi)\n\t"
      "popl %%edi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lbiped_limp_noodle_valid_joint_rotation_10:\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      ".Lbiped_limp_noodle_valid_joint_rotation_11:\n\t"
      "popl %%edi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [norm] "m"(bln_norm), [assert] "m"(bln_assert), [exitfn] "m"(bln_exitfn), [d99490] "m"(bln_d99490), [minv] "m"(bln_minv), [mscale] "m"(bln_mscale), [rots] "m"(bln_rots), [get] "m"(bln_get), [c4dab0] "m"(bln_c4dab0), [elem] "m"(bln_elem), [tag] "m"(bln_tag), [ffloor] "m"(bln_ffloor)
      : "memory");
}
#else
char biped_limp_noodle_valid_joint_rotation(int unit_handle, int16_t node_index,
                                            void *node_block, float *out_pos,
                                            unsigned int *visited_bits,
                                            float *candidate_pos)
{
  char *unit;
  char *bipd;
  char *antr;
  char *node_def;
  char *parent_def;
  char *parent_node;
  char *node;
  float frame_scale;
  float *node_pos;
  float *parent_pos;
  int16_t parent_index;
  float bone[3];
  float cand[3];
  float axis[3];
  float dot;
  float angle;
  float inv_parent[12];
  float inv_node[12];
  float local_axis[3];
  float local_dir[3];
  float plane[4];
  float snapped[3];
  float delta[3];
  float rotated[3];
  char changed;
  unsigned int tiny = 0x3cf5c28fu;

  changed = 0;
  unit = (char *)object_get_and_verify_type(unit_handle, 1);
  bipd = (char *)tag_get(0x62697064, *(int *)unit);
  antr = (char *)tag_get(0x616e7472, *(int *)(bipd + 0x44));
  node_def = (char *)tag_block_get_element((void *)(antr + 0x68), node_index, 0x40);
  parent_index = *(int16_t *)(node_def + 0x24);
  parent_def =
      (char *)tag_block_get_element((void *)(antr + 0x68), parent_index, 0x40);
  frame_scale = *(float *)(antr + 0x60);
  if (fabsf(frame_scale) > *(double *)0x2533d0 || frame_scale < 0.0f ||
      !(frame_scale <= *(float *)0x2b4b74))
    frame_scale = *(float *)&tiny;

  if (parent_index == 0 || (*(unsigned char *)(parent_def + 0x28) & 4) != 0)
    goto inherit_check;

  node = (char *)node_block + (int)node_index * 0x34;
  parent_node = (char *)node_block + (int)parent_index * 0x34;
  node_pos = (float *)(node + 0x28);
  parent_pos = (float *)(parent_node + 0x28);

  bone[0] = node_pos[0] - parent_pos[0];
  bone[1] = node_pos[1] - parent_pos[1];
  bone[2] = node_pos[2] - parent_pos[2];
  cand[0] = candidate_pos[0] - parent_pos[0];
  cand[1] = candidate_pos[1] - parent_pos[1];
  cand[2] = candidate_pos[2] - parent_pos[2];
  normalize3d(bone);
  normalize3d(cand);
  axis[0] = cand[2] * bone[1] - cand[1] * bone[2];
  axis[1] = bone[2] * cand[0] - cand[2] * bone[0];
  axis[2] = cand[1] * bone[0] - bone[1] * cand[0];
  normalize3d(axis);
  dot = cand[0] * bone[0] + cand[1] * bone[1] + cand[2] * bone[2];
  if (fabsf(dot - *(float *)0x2533c8) > *(double *)0x2533d0)
    goto inherit_check;
  angle = acosf(dot);

  matrix_inverse((float *)parent_node, inv_parent);
  matrix_inverse((float *)((char *)node_block +
                           (int)*(int16_t *)(parent_def + 0x24) * 0x34),
                 inv_node);
  matrix_scale_transform_vector(inv_parent, axis, local_axis);
  local_dir[0] = *(float *)(node + 4);
  local_dir[1] = *(float *)(node + 8);
  local_dir[2] = *(float *)(node + 0xc);
  matrix_scale_transform_vector(inv_node, local_dir, local_dir);

  if ((*(unsigned char *)(parent_def + 0x28) & 2) != 0) {
    float dist;
    FUN_00099490(plane, (float *)(parent_node + 0x28),
                 (float *)(parent_node + 0x1c));
    dist = (plane[0] * candidate_pos[0] + plane[1] * candidate_pos[1] +
            plane[2] * candidate_pos[2] - plane[3]) *
           *(float *)0x255e94;
    snapped[0] = candidate_pos[0] + plane[0] * dist;
    snapped[1] = candidate_pos[1] + plane[1] * dist;
    snapped[2] = candidate_pos[2] + plane[2] * dist;
    if (fabsf(plane[0] * snapped[0] + plane[1] * snapped[1] +
              plane[2] * snapped[2] - plane[3]) > *(double *)0x2533d0) {
      display_assert((char *)0x2b4b00, (char *)0x2b4b48, 0xe7, 1);
      system_exit(-1);
    }
    delta[0] = snapped[0] - parent_pos[0];
    delta[1] = snapped[1] - parent_pos[1];
    delta[2] = snapped[2] - parent_pos[2];
    normalize3d(delta);
    matrix_scale_transform_vector(inv_parent, delta, rotated);
    if (fabsf(rotated[0] * local_dir[0] + rotated[1] * local_dir[1] +
              rotated[2] * local_dir[2] - *(float *)0x2533c8) >
        *(double *)0x2533d0)
      goto inherit_check;
    visited_bits[node_index >> 5] |= 1u << (node_index & 31);
    if (!(out_pos[2] < snapped[2]) &&
        !FUN_0014dab0((int)(uintptr_t)snapped, *(int *)&frame_scale)) {
      out_pos[0] = snapped[0];
      out_pos[1] = snapped[1];
      out_pos[2] = snapped[2];
    }
    changed = 1;
  } else {
    rotate_vector3d_by_sincos(local_dir, local_axis, sinf(angle), cosf(angle));
    dot = local_dir[0] * *(float *)(parent_def + 0x2c) +
          local_dir[1] * *(float *)(parent_def + 0x30) +
          local_dir[2] * *(float *)(parent_def + 0x34);
    if (fabsf(dot - *(float *)0x2533c8) > *(double *)0x2533d0)
      goto inherit_check;
    if (!(fabsf(acosf(dot)) < *(float *)(parent_def + 0x38)))
      goto inherit_check;
    if (!(out_pos[2] > candidate_pos[2]))
      goto inherit_check;
    visited_bits[node_index >> 5] |= 1u << (node_index & 31);
    out_pos[0] = candidate_pos[0];
    out_pos[1] = candidate_pos[1];
    out_pos[2] = candidate_pos[2];
    changed = 1;
  }

inherit_check:
  if ((*(unsigned char *)(parent_def + 0x28) & 4) == 0 && changed)
    return 1;
  {
    int16_t p = *(int16_t *)(node_def + 0x24);
    if ((visited_bits[p >> 5] & (1u << (p & 31))) != 0 &&
        out_pos[2] > candidate_pos[2]) {
      visited_bits[node_index >> 5] |= 1u << (node_index & 31);
      out_pos[0] = candidate_pos[0];
      out_pos[1] = candidate_pos[1];
      out_pos[2] = candidate_pos[2];
      return 1;
    }
  }
  return changed;
}
#endif


/* 0x19fa20 — limp-noodle iteration: constrain child nodes toward parents. */
void FUN_0019fa20(int unit_handle, void *node_block)
{
  char *unit;
  char *bipd;
  char *antr;
  float frame_scale;
  unsigned char steps;
  unsigned char max_steps;
  float step_frac;
  unsigned int tiny = 0x3cf5c28fu;
  unsigned int visited[8];
  char collision_scratch[0x300];
  int16_t queue[0xa4];
  int queue_len;
  int i;
  char *node_def;
  int16_t node_index;
  int16_t parent_index;
  float *node_pos;
  float *parent_pos;
  float zero_vel[3];
  float new_pos[3];
  float new_vel[3];

  unit = (char *)object_get_and_verify_type(unit_handle, 1);
  bipd = (char *)tag_get(0x62697064, *(int *)unit);
  antr = (char *)tag_get(0x616e7472, *(int *)(bipd + 0x44));
  frame_scale = *(float *)(antr + 0x60);

  if (*(int16_t *)0x4761d8 >= 0x20) {
    display_assert((char *)0x253440, (char *)0x2b4b48, 0x13f, 1);
    system_exit(-1);
  }
  {
    int16_t depth = *(int16_t *)0x4761d8;
    *(int16_t *)(0x5a8c80 + (int)depth * 2) = 0x12;
    *(int16_t *)0x4761d8 = (int16_t)(depth + 1);
  }
  if (fabsf(frame_scale) > *(double *)0x2533d0 || frame_scale < 0.0f ||
      !(frame_scale <= *(float *)0x2b4b74))
    frame_scale = *(float *)&tiny;

  max_steps = *(unsigned char *)(unit + 0x47d);
  steps = *(unsigned char *)(unit + 0x47c);
  if (max_steps == 0 || max_steps >= 0x1e)
    return;
  step_frac = (float)(steps + 1) / (float)max_steps;
  if (fabsf(step_frac) > *(double *)0x2533d0)
    return;
  if (steps >= max_steps)
    return;

  FUN_0014ec30(0xc0a8, (float *)(unit + 0xc),
               *(float *)(unit + 0x5c) + *(float *)0x255d90, frame_scale,
               frame_scale, unit_handle, (void *)0x4d9de8);
  csmemset(visited, 0, sizeof(visited));

  queue_len = 1;
  queue[0] = 0;
  for (i = 0; i < queue_len && i < 0xa0; i++) {
    node_index = queue[i];
    node_def =
        (char *)tag_block_get_element((void *)(antr + 0x68), node_index, 0x40);
    if (node_index == 0) {
      if (queue_len < 0xa0 && queue_len < *(int *)(antr + 0x68)) {
        queue[queue_len] = (int16_t)queue_len;
        queue_len++;
      }
      continue;
    }
    parent_index = *(int16_t *)(node_def + 0x24);
    node_pos = (float *)((char *)node_block + (int)node_index * 0x34 + 0x28);
    parent_pos =
        (float *)((char *)node_block + (int)parent_index * 0x34 + 0x28);
    zero_vel[0] = 0.0f;
    zero_vel[1] = 0.0f;
    zero_vel[2] = 0.0f;

    if (!FUN_0014dab0((int)(uintptr_t)node_pos, *(int *)&frame_scale)) {
      FUN_0014f2c0(node_pos, zero_vel, (short *)0x4d9de8, new_pos, new_vel, 3,
                   (int)(uintptr_t)collision_scratch);
      if (fabsf(new_pos[0]) <= *(double *)0x2533d0 &&
          fabsf(new_pos[1]) <= *(double *)0x2533d0) {
        biped_limp_noodle_valid_joint_rotation(unit_handle, node_index,
                                               node_block, new_pos, visited,
                                               node_pos);
      }
    }

    /* Pull child toward parent by the step fraction (structural constraint). */
    {
      float scale = step_frac * *(float *)0x2b4b7c;
      float dx = node_pos[0] - parent_pos[0];
      float dy = node_pos[1] - parent_pos[1];
      float dz = node_pos[2] - parent_pos[2];
      node_pos[0] = parent_pos[0] + dx * (1.0f - scale);
      node_pos[1] = parent_pos[1] + dy * (1.0f - scale);
      node_pos[2] = parent_pos[2] + dz * (1.0f - scale);
    }

    if (queue_len < 0xa0 && queue_len < *(int *)(antr + 0x68)) {
      queue[queue_len] = (int16_t)queue_len;
      queue_len++;
    }
  }
  (void)bipd;
}
