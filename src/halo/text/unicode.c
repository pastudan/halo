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

/* ustrcmp (0x19d810) — readable C lift. */
int ustrcmp(const wchar_t *s1, const wchar_t *s2)
{
  if (s1 == NULL || s2 == NULL) {
    display_assert((const char *)0x2b4828, (const char *)0x2b45b4, 0xb5, 1);
    system_exit(-1);
  }
  if (_wcslen(s1) >= 0x8000) {
    display_assert((const char *)0x2b4800, (const char *)0x2b45b4, 0xb6, 1);
    system_exit(-1);
  }
  if (_wcslen(s2) >= 0x8000) {
    display_assert((const char *)0x2b47d8, (const char *)0x2b45b4, 0xb7, 1);
    system_exit(-1);
  }
  return _wcscmp(s1, s2);
}

/* ustrlen (0x19d8c0) — readable C lift. */
int ustrlen(const unsigned short *s)
{
  size_t n;
  if (s == NULL) {
    display_assert((const char *)0x27b838, (const char *)0x2b45b4, 0xc2, 1);
    system_exit(-1);
  }
  n = _wcslen((const wchar_t *)s);
  if (n >= 0x8000) {
    display_assert((const char *)0x2b483c, (const char *)0x2b45b4, 0xc4, 1);
    system_exit(-1);
  }
  return (int)n;
}

/* ustrnlen (0x19d930) — readable C lift. */
size_t ustrnlen(const wchar_t *s, size_t max_len)
{
  size_t n = 0;
  if (s == NULL) {
    display_assert((const char *)0x27b838, (const char *)0x2b45b4, 0xd0, 1);
    system_exit(-1);
  }
  if (max_len != 0) {
    while (n < max_len) {
      wchar_t c = s[n];
      if (c == 0)
        break;
      n++;
    }
  }
  if (n >= 0x8000) {
    display_assert((const char *)0x2b483c, (const char *)0x2b45b4, 0xd6, 1);
    system_exit(-1);
  }
  return n;
}

/* 0x19d9b0 */
wchar_t *ustrchr(const wchar_t *s, wchar_t c)
{
  unicode_assert_string(s);
  return _wcschr(s, c);
}

/* ustrcoll (0x19da20) — readable C lift. */
int ustrcoll(const wchar_t *s1, const wchar_t *s2)
{
  if (s1 == NULL || s2 == NULL) {
    display_assert((const char *)0x2b4828, (const char *)0x2b45b4, 0xeb, 1);
    system_exit(-1);
  }
  if (_wcslen(s1) >= 0x8000) {
    display_assert((const char *)0x2b4800, (const char *)0x2b45b4, 0xec, 1);
    system_exit(-1);
  }
  if (_wcslen(s2) >= 0x8000) {
    display_assert((const char *)0x2b47d8, (const char *)0x2b45b4, 0xed, 1);
    system_exit(-1);
  }
  return FUN_001dbfa7(s1, s2);
}

/* ustrcspn (0x19dad0) — readable C lift. */
size_t ustrcspn(const wchar_t *s, const wchar_t *reject)
{
  if (s == NULL || reject == NULL) {
    display_assert((const char *)0x2b48ac, (const char *)0x2b45b4, 0xf7, 1);
    system_exit(-1);
  }
  if (_wcslen(s) >= 0x8000) {
    display_assert((const char *)0x2b4858, (const char *)0x2b45b4, 0xf8, 1);
    system_exit(-1);
  }
  if (_wcslen(reject) >= 0x8000) {
    display_assert((const char *)0x2b4880, (const char *)0x2b45b4, 0xf9, 1);
    system_exit(-1);
  }
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

/* ustrncmp (0x19dc20) — XBE naked draft (batch 270). */
#if defined(__clang__)
static void (*const b19dc20_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b19dc20_exitfn)(int) = system_exit;
static int (*const b19dc20_c1dc02c)(const wchar_t *s1, const wchar_t *s2, size_t count) = _wcsncmp;

__attribute__((naked, noinline))
int ustrncmp(const wchar_t *s1 __attribute__((unused)), const wchar_t *s2 __attribute__((unused)), size_t count __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ebx\n\t"
      "movl 0xc(%%ebp), %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "pushl %%edi\n\t"
      "je .Lustrncmp_1\n\t"
      "testl %%ebx, %%ebx\n\t"
      "jne .Lustrncmp_2\n\t"
      ".Lustrncmp_1:\n\t"
      "pushl $1\n\t"
      "pushl $0x12a\n\t"
      "pushl $0x2b45b4\n\t"
      "pushl $0x2b4828\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lustrncmp_2:\n\t"
      "movl 0x10(%%ebp), %%edi\n\t"
      "cmpl $0x8000, %%edi\n\t"
      "jb .Lustrncmp_3\n\t"
      "pushl $1\n\t"
      "pushl $0x12b\n\t"
      "pushl $0x2b45b4\n\t"
      "pushl $0x2b48c4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lustrncmp_3:\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "call *%[c1dc02c]\n\t"
      "addl $0xc, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b19dc20_assert), [exitfn] "m"(b19dc20_exitfn), [c1dc02c] "m"(b19dc20_c1dc02c)
      : "memory");
}
#else
#error "ustrncmp: clang naked draft required"
#endif


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

/* ustrspn (0x19de20) — readable C lift. */
size_t ustrspn(const wchar_t *s, const wchar_t *accept)
{
  if (s == NULL || accept == NULL) {
    display_assert((const char *)0x2b48ac, (const char *)0x2b45b4, 0x158, 1);
    system_exit(-1);
  }
  if (_wcslen(s) >= 0x8000) {
    display_assert((const char *)0x2b4858, (const char *)0x2b45b4, 0x159, 1);
    system_exit(-1);
  }
  if (_wcslen(accept) >= 0x8000) {
    display_assert((const char *)0x2b4880, (const char *)0x2b45b4, 0x15a, 1);
    system_exit(-1);
  }
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

/* ustrxfrm (0x19dff0) — XBE naked draft (batch 260). */
#if defined(__clang__)
static void (*const b19dff0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b19dff0_exitfn)(int) = system_exit;
static size_t (*const b19dff0_c1db11e)(const wchar_t *str) = _wcslen;
static size_t (*const b19dff0_c1dc257)(wchar_t *dest, const wchar_t *src, size_t count) = FUN_001dc257;

__attribute__((naked, noinline))
size_t ustrxfrm(wchar_t *dest __attribute__((unused)), const wchar_t *src __attribute__((unused)), size_t count __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ebx\n\t"
      "movl 0xc(%%ebp), %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "je .Lustrxfrm_1\n\t"
      "testl %%ebx, %%ebx\n\t"
      "jne .Lustrxfrm_2\n\t"
      ".Lustrxfrm_1:\n\t"
      "pushl $1\n\t"
      "pushl $0x17c\n\t"
      "pushl $0x2b45b4\n\t"
      "pushl $0x2b4660\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lustrxfrm_2:\n\t"
      "pushl %%edi\n\t"
      "call *%[c1db11e]\n\t"
      "addl $4, %%esp\n\t"
      "cmpl $0x8000, %%eax\n\t"
      "jb .Lustrxfrm_3\n\t"
      "pushl $1\n\t"
      "pushl $0x17d\n\t"
      "pushl $0x2b45b4\n\t"
      "pushl $0x2b47b4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lustrxfrm_3:\n\t"
      "pushl %%ebx\n\t"
      "call *%[c1db11e]\n\t"
      "addl $4, %%esp\n\t"
      "cmpl $0x8000, %%eax\n\t"
      "jb .Lustrxfrm_4\n\t"
      "pushl $1\n\t"
      "pushl $0x17e\n\t"
      "pushl $0x2b45b4\n\t"
      "pushl $0x2b4790\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lustrxfrm_4:\n\t"
      "movl 0x10(%%ebp), %%esi\n\t"
      "cmpl $0x8000, %%esi\n\t"
      "jb .Lustrxfrm_5\n\t"
      "pushl $1\n\t"
      "pushl $0x17f\n\t"
      "pushl $0x2b45b4\n\t"
      "pushl $0x2b492c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lustrxfrm_5:\n\t"
      "pushl %%esi\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "call *%[c1dc257]\n\t"
      "addl $0xc, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b19dff0_assert), [exitfn] "m"(b19dff0_exitfn), [c1db11e] "m"(b19dff0_c1db11e), [c1dc257] "m"(b19dff0_c1dc257)
      : "memory");
}
#else
#error "ustrxfrm: clang naked draft required"
#endif


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

/* ustrnlwr (0x19e1a0) — readable C lift. */
wchar_t *ustrnlwr(wchar_t *s, size_t count)
{
  extern char DAT_0027b838[];
  extern char DAT_002b45b4[];
  extern char DAT_002b4858[];
  extern char DAT_002b492c[];
  wchar_t *p;
  if (!s) {
    display_assert(DAT_0027b838, DAT_002b45b4, 0x19f, 1);
    system_exit(-1);
  }
  if (_wcslen(s) >= 0x8000) {
    display_assert(DAT_002b4858, DAT_002b45b4, 0x1a0, 1);
    system_exit(-1);
  }
  if (count >= 0x8000) {
    display_assert(DAT_002b492c, DAT_002b45b4, 0x1a1, 1);
    system_exit(-1);
  }
  p = s;
  if (*p != 0) {
    do {
      *p = (wchar_t)FUN_001dc27c((unsigned short)*p);
      p++;
    } while (*p != 0);
  }
  return s;
}
/* ustrnupr (0x19e250) — readable C lift. */
wchar_t *ustrnupr(wchar_t *s, size_t count)
{
  extern char DAT_0027b838[];
  extern char DAT_002b45b4[];
  extern char DAT_002b4858[];
  extern char DAT_002b492c[];
  wchar_t *p;
  if (!s) {
    display_assert(DAT_0027b838, DAT_002b45b4, 0x1b3, 1);
    system_exit(-1);
  }
  if (_wcslen(s) >= 0x8000) {
    display_assert(DAT_002b4858, DAT_002b45b4, 0x1b4, 1);
    system_exit(-1);
  }
  if (count >= 0x8000) {
    display_assert(DAT_002b492c, DAT_002b45b4, 0x1b5, 1);
    system_exit(-1);
  }
  p = s;
  if (*p != 0) {
    do {
      *p = (wchar_t)FUN_001da8e3((unsigned short)*p);
      p++;
    } while (*p != 0);
  }
  return s;
}
/* ustrcasecmp (0x19e300) — readable C lift. */
int ustrcasecmp(const wchar_t *s1, const wchar_t *s2)
{
  if (s1 == NULL || s2 == NULL) {
    display_assert((const char *)0x2b4828, (const char *)0x2b45b4, 0x1c7, 1);
    system_exit(-1);
  }
  if (_wcslen(s1) >= 0x8000) {
    display_assert((const char *)0x2b4800, (const char *)0x2b45b4, 0x1c8, 1);
    system_exit(-1);
  }
  if (_wcslen(s2) >= 0x8000) {
    display_assert((const char *)0x2b47d8, (const char *)0x2b45b4, 0x1c9, 1);
    system_exit(-1);
  }
  return __wcsicmp(s1, s2);
}

/* ustrncasecmp (0x19e3b0) — readable C lift. */
int ustrncasecmp(const wchar_t *s1, const wchar_t *s2, size_t count)
{
  if (s1 == NULL || s2 == NULL) {
    display_assert((const char *)0x2b4828, (const char *)0x2b45b4, 0x1d8, 1);
    system_exit(-1);
  }
  if (_wcslen(s1) >= 0x8000) {
    display_assert((const char *)0x2b4800, (const char *)0x2b45b4, 0x1d9, 1);
    system_exit(-1);
  }
  if (_wcslen(s2) >= 0x8000) {
    display_assert((const char *)0x2b47d8, (const char *)0x2b45b4, 0x1da, 1);
    system_exit(-1);
  }
  return __wcsnicmp(s1, s2, count);
}

/* uisalpha (0x19e460) — readable C lift. */
int uisalpha(int c)
{
  return FUN_001dc3e9(c, 0x103);
}

/* uisupper (0x19e480) — readable C lift. */
int uisupper(int c)
{
  return FUN_001dc3e9(c, 1);
}

/* uislower (0x19e4a0) — readable C lift. */
int uislower(int c)
{
  return FUN_001dc3e9(c, 2);
}

/* uisdigit (0x19e4c0) — readable C lift. */
int uisdigit(int c)
{
  return FUN_001dc3e9(c, 4);
}

/* uisxdigit (0x19e4e0) — readable C lift. */
int uisxdigit(int c)
{
  return FUN_001dc3e9(c, 0x80);
}

/* uisspace (0x19e500) — readable C lift. */
int uisspace(int c)
{
  return FUN_001dc3e9(c, 8);
}

/* uispunct (0x19e520) — readable C lift. */
int uispunct(int c)
{
  return FUN_001dc3e9(c, 0x10);
}

/* uisalnum (0x19e540) — readable C lift. */
int uisalnum(int c)
{
  return FUN_001dc3e9(c, 0x107);
}

/* uisprint (0x19e560) — readable C lift. */
int uisprint(int c)
{
  return FUN_001dc3e9(c, 0x157);
}

/* uisgraph (0x19e580) — readable C lift. */
int uisgraph(int c)
{
  return FUN_001dc3e9(c, 0x117);
}

/* uiscntrl (0x19e5a0) — readable C lift. */
int uiscntrl(int c)
{
  return FUN_001dc3e9(c, 0x20);
}

/* utoupper (0x19e5c0) — readable C lift. */
int utoupper(int c)
{
  typedef unsigned short (*towupper_fn)(unsigned short);
  return (int)((towupper_fn)FUN_001dc27c)((unsigned short)c);
}

/* utolower (0x19e5e0) — readable C lift. */
int utolower(int c)
{
  typedef unsigned short (*towlower_fn)(unsigned short);
  return (int)((towlower_fn)FUN_001da8e3)((unsigned short)c);
}

/* ufgetc (0x19e600) — readable C lift (assert wrapper). */
int ufgetc(void *stream)
{
  if (stream == NULL) {
    display_assert((const char *)0x2b4948, (const char *)0x2b45b4, 0x24d, 1);
    system_exit(-1);
  }
  return _fgetwc(stream);
}

/* ufputc (0x19e640) — readable C lift (assert wrapper). */
int ufputc(int c, void *stream)
{
  if (stream == NULL) {
    display_assert((const char *)0x2b4948, (const char *)0x2b45b4, 0x257, 1);
    system_exit(-1);
  }
  return _fputwc(c, stream);
}

/* uungetc (0x19e680) — readable C lift (assert wrapper). */
int uungetc(int c, void *stream)
{
  if (stream == NULL) {
    display_assert((const char *)0x2b4948, (const char *)0x2b45b4, 0x261, 1);
    system_exit(-1);
  }
  return _ungetwc(c, stream);
}

/* 0x19e6c0 */
wchar_t *ufgets(wchar_t *buffer, int count, void *stream)
{
  assert_halt(buffer && stream);
  assert_halt(count > 0 && count <= 0x8000);
  return _fgetws(buffer, count, stream);
}

/* ufputs (0x19e760) — readable C lift. */
int ufputs(const wchar_t *s, void *stream)
{
  if (s == NULL) {
    display_assert((const char *)0x27b838, (const char *)0x2b45b4, 0x278, 1);
    system_exit(-1);
  }
  if (_wcslen(s) >= 0x8000) {
    display_assert((const char *)0x2b4858, (const char *)0x2b45b4, 0x279, 1);
    system_exit(-1);
  }
  if (stream == NULL) {
    display_assert((const char *)0x2b4948, (const char *)0x2b45b4, 0x27a, 1);
    system_exit(-1);
  }
  return _fputws(s, stream);
}

/* 0x19e800 */
wchar_t *ugets(wchar_t *buffer)
{
  assert_halt(buffer);
  return __getws(buffer);
}

/* uputs (0x19e870) — readable C lift. */
int uputs(const wchar_t *s)
{
  if (s == NULL) {
    display_assert((const char *)0x27b838, (const char *)0x2b45b4, 0x299, 1);
    system_exit(-1);
  }
  if ((unsigned)_wcslen(s) >= 0x8000) {
    display_assert((const char *)0x2b4858, (const char *)0x2b45b4, 0x29a, 1);
    system_exit(-1);
  }
  return __putws(s);
}

/* ufprintf (0x19e8e0) — XBE naked draft (batch 275). */
#if defined(__clang__)
static void (*const b19e8e0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b19e8e0_exitfn)(int) = system_exit;
static size_t (*const b19e8e0_c1db11e)(const wchar_t *str) = _wcslen;
static int (*const b19e8e0_c1dc9a3)(void *stream, const wchar_t *format, char *args) = _vfwprintf;

__attribute__((naked, noinline))
int ufprintf(void *stream __attribute__((unused)), const wchar_t *format __attribute__((unused)), ...)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .Lufprintf_1\n\t"
      "pushl $1\n\t"
      "pushl $0x2a8\n\t"
      "pushl $0x2b45b4\n\t"
      "pushl $0x2b4948\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lufprintf_1:\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lufprintf_2\n\t"
      "pushl $1\n\t"
      "pushl $0x2a9\n\t"
      "pushl $0x2b45b4\n\t"
      "pushl $0x263510\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lufprintf_2:\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1db11e]\n\t"
      "addl $4, %%esp\n\t"
      "cmpl $0x8000, %%eax\n\t"
      "jb .Lufprintf_3\n\t"
      "pushl $1\n\t"
      "pushl $0x2aa\n\t"
      "pushl $0x2b45b4\n\t"
      "pushl $0x2b4950\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lufprintf_3:\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "leal 0x10(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%esi\n\t"
      "call *%[c1dc9a3]\n\t"
      "addl $0xc, %%esp\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b19e8e0_assert), [exitfn] "m"(b19e8e0_exitfn), [c1db11e] "m"(b19e8e0_c1db11e), [c1dc9a3] "m"(b19e8e0_c1dc9a3)
      : "memory");
}
#else
#error "ufprintf: clang naked draft required"
#endif


/* uprintf (0x19e980) — readable C lift. */
int uprintf(const wchar_t *format, ...)
{
  char *args;
  if (format == NULL) {
    display_assert((const char *)0x263510, (const char *)0x2b45b4, 0x2bb, 1);
    system_exit(-1);
  }
  if (_wcslen(format) >= 0x8000) {
    display_assert((const char *)0x2b4950, (const char *)0x2b45b4, 0x2bc, 1);
    system_exit(-1);
  }
  args = (char *)((char *)&format + sizeof(format));
  return _vprintf(format, args);
}

/* usprintf (0x19eaa0) — XBE naked draft (batch 278). */
#if defined(__clang__)
static void (*const b19eaa0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b19eaa0_exitfn)(int) = system_exit;
static size_t (*const b19eaa0_c1db11e)(const wchar_t *str) = _wcslen;
static int (*const b19eaa0_c1dcace)(wchar_t *buffer, const wchar_t *format, char *args) = FUN_001dcace;

__attribute__((naked, noinline))
int usprintf(wchar_t *buffer __attribute__((unused)), const wchar_t *format __attribute__((unused)), ...)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .Lusprintf_1\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lusprintf_2\n\t"
      ".Lusprintf_1:\n\t"
      "pushl $1\n\t"
      "pushl $0x2ef\n\t"
      "pushl $0x2b45b4\n\t"
      "pushl $0x2b49a4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lusprintf_2:\n\t"
      "pushl %%esi\n\t"
      "call *%[c1db11e]\n\t"
      "addl $4, %%esp\n\t"
      "cmpl $0x8000, %%eax\n\t"
      "jb .Lusprintf_3\n\t"
      "pushl $1\n\t"
      "pushl $0x2f0\n\t"
      "pushl $0x2b45b4\n\t"
      "pushl $0x2b4858\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lusprintf_3:\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1db11e]\n\t"
      "addl $4, %%esp\n\t"
      "cmpl $0x8000, %%eax\n\t"
      "jb .Lusprintf_4\n\t"
      "pushl $1\n\t"
      "pushl $0x2f1\n\t"
      "pushl $0x2b45b4\n\t"
      "pushl $0x2b4950\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lusprintf_4:\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "leal 0x10(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%esi\n\t"
      "call *%[c1dcace]\n\t"
      "addl $0xc, %%esp\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b19eaa0_assert), [exitfn] "m"(b19eaa0_exitfn), [c1db11e] "m"(b19eaa0_c1db11e), [c1dcace] "m"(b19eaa0_c1dcace)
      : "memory");
}
#else
#error "usprintf: clang naked draft required"
#endif


/* uvfprintf (0x19eb50) — readable C lift. */
int uvfprintf(void *stream, const wchar_t *format, char *args)
{
  if (stream == NULL || format == NULL) {
    display_assert((const char *)0x2b49b8, (const char *)0x2b45b4, 0x318, 1);
    system_exit(-1);
  }
  if (_wcslen(format) >= 0x8000) {
    display_assert((const char *)0x2b4950, (const char *)0x2b45b4, 0x319, 1);
    system_exit(-1);
  }
  return _vfwprintf(stream, format, args);
}

/* uvprintf (0x19ebd0) — readable C lift. */
int uvprintf(const wchar_t *format, char *args)
{
  if (format == NULL) {
    display_assert((const char *)0x263510, (const char *)0x2b45b4, 0x323, 1);
    system_exit(-1);
  }
  if (_wcslen(format) >= 0x8000) {
    display_assert((const char *)0x2b4950, (const char *)0x2b45b4, 0x324, 1);
    system_exit(-1);
  }
  return _vprintf(format, args);
}

/* uvsnprintf (0x19ec40) — readable C lift. */
int uvsnprintf(wchar_t *buffer, size_t count, const wchar_t *format, char *args)
{
  if (buffer == NULL || format == NULL) {
    display_assert((const char *)0x2b49a4, (const char *)0x2b45b4, 0x330, 1);
    system_exit(-1);
  }
  if (_wcslen(buffer) >= 0x8000) {
    display_assert((const char *)0x2b4858, (const char *)0x2b45b4, 0x331, 1);
    system_exit(-1);
  }
  if (_wcslen(format) >= 0x8000) {
    display_assert((const char *)0x2b4950, (const char *)0x2b45b4, 0x332, 1);
    system_exit(-1);
  }
  return _vsnwprintf(buffer, count, format, args);
}

/* uvsprintf (0x19ecf0) — readable C lift. */
int uvsprintf(wchar_t *buffer, const wchar_t *format, char *args)
{
  if (buffer == NULL || format == NULL) {
    display_assert((const char *)0x2b49a4, (const char *)0x2b45b4, 0x349, 1);
    system_exit(-1);
  }
  if (_wcslen(buffer) >= 0x8000) {
    display_assert((const char *)0x2b4858, (const char *)0x2b45b4, 0x34a, 1);
    system_exit(-1);
  }
  if (_wcslen(format) >= 0x8000) {
    display_assert((const char *)0x2b4950, (const char *)0x2b45b4, 0x34b, 1);
    system_exit(-1);
  }
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

/* ufclose (0x19eee0) — readable C lift (assert wrapper). */
int ufclose(void *stream)
{
  if (stream == NULL) {
    display_assert((const char *)0x2b4948, (const char *)0x2b45b4, 0x384, 1);
    system_exit(-1);
  }
  return crt_fclose(stream);
}

/* 0x19ef20 */
void *ufreopen(const wchar_t *path, const wchar_t *mode, void *stream)
{
  assert_halt(stream);
  unicode_assert_two_strings(path, mode);
  return __wfreopen(path, mode, stream);
}

/* uperror (0x19efd0) — readable C lift. */
void uperror(const wchar_t *prefix)
{
  if (prefix == NULL) {
    display_assert((const char *)0x27b838, (const char *)0x2b45b4, 0x39a, 1);
    system_exit(-1);
  }
  if ((unsigned)_wcslen(prefix) >= 0x8000) {
    display_assert((const char *)0x2b4858, (const char *)0x2b45b4, 0x39b, 1);
    system_exit(-1);
  }
  FUN_001dcd6e(prefix);
}

/* 0x19f040 */
void *upopen(const wchar_t *command, const wchar_t *mode)
{
  unicode_assert_two_strings(command, mode);
  assert_halt(_wcslen(mode) < 4);
  return NULL;
}

/* uremove (0x19f0e0) — readable C lift. */
int uremove(const wchar_t *path)
{
  if (path == NULL) {
    display_assert((const char *)0x2b49f8, (const char *)0x2b45b4, 0x3b2, 1);
    system_exit(-1);
  }
  if ((unsigned)_wcslen(path) >= 0x8000) {
    display_assert((const char *)0x2b49d4, (const char *)0x2b45b4, 0x3b3, 1);
    system_exit(-1);
  }
  return FUN_001dce6e(path);
}

/* 0x19f150 */
wchar_t *utmpnam(wchar_t *buffer)
{
  return FUN_001dcf51(buffer);
}

/* ustrtol (0x19f160) — readable C lift. */
long ustrtol(const wchar_t *s, wchar_t **endptr, int base)
{
  if (s == NULL) {
    display_assert((const char *)0x2b4a94, (const char *)0x2b45b4, 0x3c7, 1);
    system_exit(-1);
  }
  if (_wcslen(s) >= 0x8000) {
    display_assert((const char *)0x2b4a70, (const char *)0x2b45b4, 0x3c8, 1);
    system_exit(-1);
  }
  return FUN_001dd1d1(s, endptr, base);
}

/* ustrtoul (0x19f1d0) — readable C lift. */
unsigned long ustrtoul(const wchar_t *s, wchar_t **endptr, int base)
{
  if (s == NULL) {
    display_assert((const char *)0x2b4a94, (const char *)0x2b45b4, 0x3d3, 1);
    system_exit(-1);
  }
  if (_wcslen(s) >= 0x8000) {
    display_assert((const char *)0x2b4a70, (const char *)0x2b45b4, 0x3d4, 1);
    system_exit(-1);
  }
  return FUN_001dd1e8(s, endptr, base);
}

/* ustrtod (0x19f240) — readable C lift. */
double ustrtod(const wchar_t *s, wchar_t **endptr)
{
  if (s == NULL) {
    display_assert((const char *)0x2b4a94, (const char *)0x2b45b4, 0x3de, 1);
    system_exit(-1);
  }
  if (_wcslen(s) >= 0x8000) {
    display_assert((const char *)0x2b4a70, (const char *)0x2b45b4, 0x3df, 1);
    system_exit(-1);
  }
  return FUN_001dd1ff(s, endptr);
}

/* uatoi (0x19f2b0) — readable C lift. */
int uatoi(const wchar_t *s)
{
  if (s == NULL) {
    display_assert((const char *)0x27b838, (const char *)0x2b45b4, 0x3ea, 1);
    system_exit(-1);
  }
  if ((unsigned)_wcslen(s) >= 0x8000) {
    display_assert((const char *)0x2b4858, (const char *)0x2b45b4, 0x3eb, 1);
    system_exit(-1);
  }
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
#if defined(__clang__)
static void (*const a9fa20_assert)(const char *, const char *, int, bool) = display_assert;
static void *(*const a9fa20_memset)(void *, int, unsigned int) = csmemset;
static void (*const a9fa20_exitfn)(int) = system_exit;
static void *(*const a9fa20_get)(int, int) = object_get_and_verify_type;
static char (*const a9fa20_c4dab0)(int, int) = FUN_0014dab0;
static bool (*const a9fa20_ray)(unsigned int, float *, float *, int, short *) = FUN_0014df70;
static bool (*const a9fa20_c4ec30)(int, float *, float, float, float, int, void *) = FUN_0014ec30;
static short (*const a9fa20_c4f2c0)(float *, float *, short *, float *, float *, short, int) = FUN_0014f2c0;
static void *(*const a9fa20_elem)(void *, int, int) = tag_block_get_element;
static char (*const a9fa20_bln)(int, short, void *, float *, unsigned int *, float *) = biped_limp_noodle_valid_joint_rotation;
static void *(*const a9fa20_tag)(int, int) = tag_get;

__attribute__((naked, noinline))
void FUN_0019fa20(int unit_handle __attribute__((unused)), void *node_block __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x300, %%esp\n\t"
      "pushl %%ebx\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl $1\n\t"
      "pushl %%ebx\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl (%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x62697064\n\t"
      "call *%[tag]\n\t"
      "movl 0x44(%%eax), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x616e7472\n\t"
      "movl %%eax, -0x4c(%%ebp)\n\t"
      "call *%[tag]\n\t"
      "movl %%eax, %%edi\n\t"
      "movl 0x60(%%edi), %%edx\n\t"
      "addl $0x18, %%esp\n\t"
      "cmpw $0x20, 0x4761d8\n\t"
      "movl %%edx, -0x8(%%ebp)\n\t"
      "jl .LFUN_0019fa20_1\n\t"
      "pushl $1\n\t"
      "pushl $0x13f\n\t"
      "pushl $0x2b4b48\n\t"
      "pushl $0x253440\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0019fa20_1:\n\t"
      "flds -0x8(%%ebp)\n\t"
      "movw 0x4761d8, %%ax\n\t"
      "fabs\n\t"
      "movswl %%ax, %%ecx\n\t"
      "fcompl 0x2533d0\n\t"
      "incw %%ax\n\t"
      "movw %%ax, 0x4761d8\n\t"
      "movw $0x12, 0x5a8c80(,%%ecx,2)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .LFUN_0019fa20_2\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .LFUN_0019fa20_2\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fcomps 0x2b4b74\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_0019fa20_3\n\t"
      ".LFUN_0019fa20_2:\n\t"
      "movl $0x3cf5c28f, -0x8(%%ebp)\n\t"
      ".LFUN_0019fa20_3:\n\t"
      "movb 0x47d(%%esi), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "jbe .LFUN_0019fa20_34\n\t"
      "cmpb $0x1e, %%cl\n\t"
      "jae .LFUN_0019fa20_34\n\t"
      "movb 0x47c(%%esi), %%dl\n\t"
      "movzbl %%dl, %%eax\n\t"
      "incl %%eax\n\t"
      "movl %%eax, -0x20(%%ebp)\n\t"
      "movzbl %%cl, %%eax\n\t"
      "fildl -0x20(%%ebp)\n\t"
      "movl %%eax, -0x20(%%ebp)\n\t"
      "fidivl -0x20(%%ebp)\n\t"
      "fsts -0x3c(%%ebp)\n\t"
      "fabs\n\t"
      "fcompl 0x2533d0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .LFUN_0019fa20_34\n\t"
      "cmpb %%cl, %%dl\n\t"
      "jae .LFUN_0019fa20_32\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "flds 0x5c(%%esi)\n\t"
      "fadds 0x255d90\n\t"
      "pushl $0x4d9de8\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0\n\t"
      "pushl %%ecx\n\t"
      "fstps (%%esp)\n\t"
      "addl $0xc, %%esi\n\t"
      "pushl %%esi\n\t"
      "pushl $0xc0a8\n\t"
      "call *%[c4ec30]\n\t"
      "pushl $8\n\t"
      "leal -0xbc(%%ebp), %%edx\n\t"
      "pushl $0\n\t"
      "pushl %%edx\n\t"
      "call *%[memset]\n\t"
      "addl $0x28, %%esp\n\t"
      "addl $0x68, %%edi\n\t"
      "movl $0, -0x20(%%ebp)\n\t"
      "movl %%edi, -0x48(%%ebp)\n\t"
      "jmp .LFUN_0019fa20_4\n\t"
      "leal (%%esp), %%esp\n\t"
      "movl %%edi, %%edi\n\t"
      ".LFUN_0019fa20_4:\n\t"
      "xorl %%eax, %%eax\n\t"
      "movl $1, -0xc(%%ebp)\n\t"
      "movw %%ax, -0x148(%%ebp)\n\t"
      ".LFUN_0019fa20_5:\n\t"
      "movl -0x48(%%ebp), %%edx\n\t"
      "movswl %%ax, %%ecx\n\t"
      "movw -0x148(%%ebp,%%ecx,2), %%si\n\t"
      "movswl %%si, %%edi\n\t"
      "pushl $0x40\n\t"
      "incl %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%edx\n\t"
      "movl %%eax, -0x44(%%ebp)\n\t"
      "movl %%edi, -0x4(%%ebp)\n\t"
      "call *%[elem]\n\t"
      "addl $0xc, %%esp\n\t"
      "testw %%si, %%si\n\t"
      "movl %%eax, -0x40(%%ebp)\n\t"
      "je .LFUN_0019fa20_29\n\t"
      "flds -0x3c(%%ebp)\n\t"
      "movl 0xc(%%ebp), %%esi\n\t"
      "imull $0x34, %%edi, %%edi\n\t"
      "fmuls 0x2b4b7c\n\t"
      "fstps -0x24(%%ebp)\n\t"
      "movl $0, -0x2c(%%ebp)\n\t"
      "movl $0, -0x28(%%ebp)\n\t"
      "movswl 0x24(%%eax), %%eax\n\t"
      "flds 0x28(%%edi,%%esi,1)\n\t"
      "imull $0x34, %%eax, %%eax\n\t"
      "fsubs 0x28(%%eax,%%esi,1)\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "flds 0x2c(%%edi,%%esi,1)\n\t"
      "fsubs 0x2c(%%eax,%%esi,1)\n\t"
      "leal 0x28(%%edi,%%esi,1), %%edi\n\t"
      "leal 0x28(%%eax,%%esi,1), %%ebx\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "movl -0x20(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "flds 0x8(%%edi)\n\t"
      "fsubs 0x8(%%ebx)\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "jne .LFUN_0019fa20_6\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "call *%[c4dab0]\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_0019fa20_6\n\t"
      "leal -0x300(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $3\n\t"
      "leal -0xb4(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0xc8(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x4d9de8\n\t"
      "leal -0x2c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "call *%[c4f2c0]\n\t"
      "flds -0xb4(%%ebp)\n\t"
      "fabs\n\t"
      "addl $0x1c, %%esp\n\t"
      "fcompl 0x2533d0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_0019fa20_6\n\t"
      "flds -0xb0(%%ebp)\n\t"
      "fabs\n\t"
      "fcompl 0x2533d0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_0019fa20_6\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "leal -0xbc(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edi\n\t"
      "pushl %%esi\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "leal -0xc8(%%ebp), %%esi\n\t"
      "call *%[bln]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0019fa20_6:\n\t"
      "flds (%%edi)\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "fsubs (%%ebx)\n\t"
      "leal -0x9c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "leal -0x18(%%ebp), %%edx\n\t"
      "flds 0x4(%%edi)\n\t"
      "pushl %%edx\n\t"
      "fsubs 0x4(%%ebx)\n\t"
      "leal -0xa8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0xc0a8\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "flds 0x8(%%edi)\n\t"
      "fsubs 0x8(%%ebx)\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fmuls 0x25abcc\n\t"
      "fsubrs (%%ebx)\n\t"
      "fstps -0xa8(%%ebp)\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fmuls 0x25abcc\n\t"
      "fsubrs 0x4(%%ebx)\n\t"
      "fstps -0xa4(%%ebp)\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fmuls 0x25abcc\n\t"
      "fsubrs 0x8(%%ebx)\n\t"
      "fstps -0xa0(%%ebp)\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fmuls 0x2b4b78\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fmuls 0x2b4b78\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fmuls 0x2b4b78\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "call *%[ray]\n\t"
      "addl $0x14, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0019fa20_23\n\t"
      "pushl %%esi\n\t"
      "pushl $0x3cf5c28f\n\t"
      "pushl %%edi\n\t"
      "call *%[c4dab0]\n\t"
      "pushl %%esi\n\t"
      "pushl $0x3cf5c28f\n\t"
      "pushl %%ebx\n\t"
      "movb %%al, -0x1c(%%ebp)\n\t"
      "call *%[c4dab0]\n\t"
      "movzbl -0x1c(%%ebp), %%ecx\n\t"
      "movb %%al, -0x1b(%%ebp)\n\t"
      "movzbl %%al, %%eax\n\t"
      "addl $0x18, %%esp\n\t"
      "addl %%ecx, %%eax\n\t"
      "je .LFUN_0019fa20_23\n\t"
      "cmpl $2, %%eax\n\t"
      "jne .LFUN_0019fa20_12\n\t"
      "flds -0x74(%%ebp)\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "fmuls -0x74(%%ebp)\n\t"
      "flds -0x70(%%ebp)\n\t"
      "fmuls -0x70(%%ebp)\n\t"
      "faddp %%st(1)\n\t"
      "flds -0x78(%%ebp)\n\t"
      "fmuls -0x78(%%ebp)\n\t"
      "faddp %%st(1)\n\t"
      "movl %%edi, %%edi\n\t"
      ".LFUN_0019fa20_7:\n\t"
      "testl %%ecx, %%ecx\n\t"
      "movl %%edi, %%eax\n\t"
      "je .LFUN_0019fa20_8\n\t"
      "movl %%ebx, %%eax\n\t"
      ".LFUN_0019fa20_8:\n\t"
      "flds -0x74(%%ebp)\n\t"
      "fmuls 0x4(%%eax)\n\t"
      "flds -0x70(%%ebp)\n\t"
      "fmuls 0x8(%%eax)\n\t"
      "faddp %%st(1)\n\t"
      "flds -0x78(%%ebp)\n\t"
      "fmuls (%%eax)\n\t"
      "faddp %%st(1)\n\t"
      "fsubs -0x6c(%%ebp)\n\t"
      "fdiv %%st(1), %%st(0)\n\t"
      "fchs\n\t"
      "fcoms 0x2533c0\n\t"
      "fsts -0x38(%%ebp,%%ecx,4)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .LFUN_0019fa20_9\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fmuls 0x254e04\n\t"
      "fadd %%st(1), %%st(0)\n\t"
      "fstps -0x38(%%ebp,%%ecx,4)\n\t"
      ".LFUN_0019fa20_9:\n\t"
      "leal 0x1(%%ecx), %%edx\n\t"
      "fstp %%st(0)\n\t"
      "testl %%edx, %%edx\n\t"
      "movl %%edi, %%eax\n\t"
      "je .LFUN_0019fa20_10\n\t"
      "movl %%ebx, %%eax\n\t"
      ".LFUN_0019fa20_10:\n\t"
      "flds -0x74(%%ebp)\n\t"
      "fmuls 0x4(%%eax)\n\t"
      "flds -0x70(%%ebp)\n\t"
      "fmuls 0x8(%%eax)\n\t"
      "faddp %%st(1)\n\t"
      "flds -0x78(%%ebp)\n\t"
      "fmuls (%%eax)\n\t"
      "faddp %%st(1)\n\t"
      "fsubs -0x6c(%%ebp)\n\t"
      "fdiv %%st(1), %%st(0)\n\t"
      "fchs\n\t"
      "fcoms 0x2533c0\n\t"
      "fsts -0x34(%%ebp,%%ecx,4)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .LFUN_0019fa20_11\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fmuls 0x254e04\n\t"
      "fadd %%st(1), %%st(0)\n\t"
      "fstps -0x34(%%ebp,%%ecx,4)\n\t"
      ".LFUN_0019fa20_11:\n\t"
      "addl $2, %%ecx\n\t"
      "fstp %%st(0)\n\t"
      "cmpl $2, %%ecx\n\t"
      "jl .LFUN_0019fa20_7\n\t"
      "fstp %%st(0)\n\t"
      "jmp .LFUN_0019fa20_17\n\t"
      ".LFUN_0019fa20_12:\n\t"
      "xorl %%edx, %%edx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      ".LFUN_0019fa20_13:\n\t"
      "movb -0x1c(%%ebp,%%ecx,1), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0019fa20_19\n\t"
      "cmpl %%edx, %%ecx\n\t"
      "movl %%edi, %%eax\n\t"
      "je .LFUN_0019fa20_14\n\t"
      "movl %%ebx, %%eax\n\t"
      ".LFUN_0019fa20_14:\n\t"
      "flds -0x74(%%ebp)\n\t"
      "fmuls 0x4(%%eax)\n\t"
      "flds -0x70(%%ebp)\n\t"
      "fmuls 0x8(%%eax)\n\t"
      "faddp %%st(1)\n\t"
      "flds -0x78(%%ebp)\n\t"
      "fmuls (%%eax)\n\t"
      "faddp %%st(1)\n\t"
      "fsubs -0x6c(%%ebp)\n\t"
      "flds -0x74(%%ebp)\n\t"
      "fmuls -0x74(%%ebp)\n\t"
      "flds -0x70(%%ebp)\n\t"
      "fmuls -0x70(%%ebp)\n\t"
      "faddp %%st(1)\n\t"
      "flds -0x78(%%ebp)\n\t"
      "fmuls -0x78(%%ebp)\n\t"
      "faddp %%st(1)\n\t"
      ".byte 0xde, 0xf9\n\t"
      "fchs\n\t"
      "fcoms 0x2533c0\n\t"
      "fsts -0x38(%%ebp,%%ecx,4)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .LFUN_0019fa20_15\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fmuls 0x254e04\n\t"
      "fadd %%st(1), %%st(0)\n\t"
      "fstps -0x38(%%ebp,%%ecx,4)\n\t"
      ".LFUN_0019fa20_15:\n\t"
      "fstp %%st(0)\n\t"
      ".LFUN_0019fa20_16:\n\t"
      "incl %%ecx\n\t"
      "cmpl $2, %%ecx\n\t"
      "jl .LFUN_0019fa20_13\n\t"
      ".LFUN_0019fa20_17:\n\t"
      "xorl %%edx, %%edx\n\t"
      ".LFUN_0019fa20_18:\n\t"
      "flds -0x38(%%ebp,%%edx,4)\n\t"
      "fabs\n\t"
      "fcompl 0x2533d0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .LFUN_0019fa20_22\n\t"
      "testl %%edx, %%edx\n\t"
      "jne .LFUN_0019fa20_20\n\t"
      "movl %%edi, %%ecx\n\t"
      "movl %%edi, %%eax\n\t"
      "jmp .LFUN_0019fa20_21\n\t"
      ".LFUN_0019fa20_19:\n\t"
      "movl %%edx, -0x38(%%ebp,%%ecx,4)\n\t"
      "jmp .LFUN_0019fa20_16\n\t"
      ".LFUN_0019fa20_20:\n\t"
      "movl %%ebx, %%ecx\n\t"
      "movl %%ebx, %%eax\n\t"
      ".LFUN_0019fa20_21:\n\t"
      "flds -0x3c(%%ebp)\n\t"
      "fmuls -0x38(%%ebp,%%edx,4)\n\t"
      "flds -0x78(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fadds (%%eax)\n\t"
      "fstps (%%ecx)\n\t"
      "flds -0x74(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fadds 0x4(%%eax)\n\t"
      "fstps 0x4(%%ecx)\n\t"
      "flds -0x70(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fadds 0x8(%%eax)\n\t"
      "fstps 0x8(%%ecx)\n\t"
      "fstp %%st(0)\n\t"
      ".LFUN_0019fa20_22:\n\t"
      "incl %%edx\n\t"
      "cmpl $2, %%edx\n\t"
      "jl .LFUN_0019fa20_18\n\t"
      ".LFUN_0019fa20_23:\n\t"
      "flds (%%edi)\n\t"
      "movl -0x4c(%%ebp), %%eax\n\t"
      "fsubs (%%ebx)\n\t"
      "movl 0x34(%%eax), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x6d6f6465\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "flds 0x4(%%edi)\n\t"
      "fsubs 0x4(%%ebx)\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "flds 0x8(%%edi)\n\t"
      "fsubs 0x8(%%ebx)\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "call *%[tag]\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "pushl $0x9c\n\t"
      "pushl %%edx\n\t"
      "addl $0xb8, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "flds (%%ebx)\n\t"
      "fsubs (%%edi)\n\t"
      "movl 0x44(%%eax), %%eax\n\t"
      "flds 0x4(%%ebx)\n\t"
      "movl %%eax, -0x30(%%ebp)\n\t"
      "fsubs 0x4(%%edi)\n\t"
      "addl $0x14, %%esp\n\t"
      "flds 0x8(%%ebx)\n\t"
      "fsubs 0x8(%%edi)\n\t"
      "fld %%st(0)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fld %%st(2)\n\t"
      "fmul %%st(3), %%st(0)\n\t"
      "faddp %%st(1)\n\t"
      "fld %%st(3)\n\t"
      "fmul %%st(4), %%st(0)\n\t"
      "faddp %%st(1)\n\t"
      "fsqrt\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "flds -0x30(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jnp .LFUN_0019fa20_26\n\t"
      "flds -0x30(%%ebp)\n\t"
      "fcomps 0x253f34\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .LFUN_0019fa20_26\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_0019fa20_26\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fcomps 0x254cd0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_0019fa20_26\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fabs\n\t"
      "fcoml 0x2533d0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .LFUN_0019fa20_25\n\t"
      "flds -0x30(%%ebp)\n\t"
      "fabs\n\t"
      "fcompl 0x2533d0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .LFUN_0019fa20_28\n\t"
      "flds -0x30(%%ebp)\n\t"
      "fcomps -0x4(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .LFUN_0019fa20_28\n\t"
      "fcompl 0x2533d0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .LFUN_0019fa20_29\n\t"
      "flds -0x30(%%ebp)\n\t"
      "movl -0x40(%%ebp), %%ecx\n\t"
      "cmpw $0, 0x24(%%ecx)\n\t"
      "fsubs -0x4(%%ebp)\n\t"
      "fdivs -0x4(%%ebp)\n\t"
      "je .LFUN_0019fa20_24\n\t"
      "fmuls 0x253398\n\t"
      "leal -0x300(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $3\n\t"
      "fsts -0x4(%%ebp)\n\t"
      "leal -0x2c(%%ebp), %%eax\n\t"
      "fchs\n\t"
      "pushl %%eax\n\t"
      "flds -0x18(%%ebp)\n\t"
      "pushl %%ebx\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "pushl $0x4d9de8\n\t"
      "leal -0x2c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "fstps -0x2c(%%ebp)\n\t"
      "pushl %%ebx\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fstps -0x28(%%ebp)\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fstps -0x24(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "call *%[c4f2c0]\n\t"
      "flds -0x18(%%ebp)\n\t"
      "leal -0x300(%%ebp), %%edx\n\t"
      "fmuls -0x4(%%ebp)\n\t"
      "pushl %%edx\n\t"
      "pushl $3\n\t"
      "leal -0x2c(%%ebp), %%eax\n\t"
      "fstps -0x2c(%%ebp)\n\t"
      "pushl %%eax\n\t"
      "flds -0x14(%%ebp)\n\t"
      "pushl %%edi\n\t"
      "fmuls -0x4(%%ebp)\n\t"
      "pushl $0x4d9de8\n\t"
      "leal -0x2c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "fstps -0x28(%%ebp)\n\t"
      "pushl %%edi\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fmuls -0x4(%%ebp)\n\t"
      "fstps -0x24(%%ebp)\n\t"
      "call *%[c4f2c0]\n\t"
      "addl $0x38, %%esp\n\t"
      "jmp .LFUN_0019fa20_29\n\t"
      ".LFUN_0019fa20_24:\n\t"
      "flds -0x18(%%ebp)\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "fstps -0x2c(%%ebp)\n\t"
      "pushl %%edi\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fstps -0x28(%%ebp)\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fstps -0x24(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "call *%[c4dab0]\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_0019fa20_29\n\t"
      "leal -0x300(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $3\n\t"
      "leal -0x2c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "pushl $0x4d9de8\n\t"
      "leal -0x2c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "call *%[c4f2c0]\n\t"
      "addl $0x1c, %%esp\n\t"
      "jmp .LFUN_0019fa20_29\n\t"
      ".LFUN_0019fa20_25:\n\t"
      "fstp %%st(0)\n\t"
      ".LFUN_0019fa20_26:\n\t"
      "movl -0x40(%%ebp), %%ecx\n\t"
      "movw 0x20(%%ecx), %%ax\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .LFUN_0019fa20_27\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "movswl %%dx, %%esi\n\t"
      "incl %%edx\n\t"
      "movw %%ax, -0x148(%%ebp,%%esi,2)\n\t"
      "movl %%edx, -0xc(%%ebp)\n\t"
      ".LFUN_0019fa20_27:\n\t"
      "movw 0x22(%%ecx), %%cx\n\t"
      "cmpw $-1, %%cx\n\t"
      "je .LFUN_0019fa20_31\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "movswl %%ax, %%edx\n\t"
      "incl %%eax\n\t"
      "movw %%cx, -0x148(%%ebp,%%edx,2)\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "jmp .LFUN_0019fa20_31\n\t"
      ".LFUN_0019fa20_28:\n\t"
      "fstp %%st(0)\n\t"
      ".LFUN_0019fa20_29:\n\t"
      "movl -0x40(%%ebp), %%ecx\n\t"
      "movw 0x20(%%ecx), %%ax\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .LFUN_0019fa20_30\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "movswl %%dx, %%esi\n\t"
      "incl %%edx\n\t"
      "movw %%ax, -0x148(%%ebp,%%esi,2)\n\t"
      "movl %%edx, -0xc(%%ebp)\n\t"
      ".LFUN_0019fa20_30:\n\t"
      "movw 0x22(%%ecx), %%ax\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .LFUN_0019fa20_31\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "movswl %%cx, %%edx\n\t"
      "incl %%ecx\n\t"
      "movw %%ax, -0x148(%%ebp,%%edx,2)\n\t"
      "movl %%ecx, -0xc(%%ebp)\n\t"
      ".LFUN_0019fa20_31:\n\t"
      "movl -0x44(%%ebp), %%eax\n\t"
      "cmpw -0xc(%%ebp), %%ax\n\t"
      "jne .LFUN_0019fa20_5\n\t"
      "movl -0x20(%%ebp), %%eax\n\t"
      "incl %%eax\n\t"
      "cmpl $4, %%eax\n\t"
      "movl %%eax, -0x20(%%ebp)\n\t"
      "jl .LFUN_0019fa20_4\n\t"
      ".LFUN_0019fa20_32:\n\t"
      "cmpw $1, 0x4761d8\n\t"
      "jg .LFUN_0019fa20_33\n\t"
      "pushl $1\n\t"
      "pushl $0x212\n\t"
      "pushl $0x2b4b48\n\t"
      "pushl $0x253418\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0019fa20_33:\n\t"
      "decw 0x4761d8\n\t"
      ".LFUN_0019fa20_34:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(a9fa20_assert), [memset] "m"(a9fa20_memset), [exitfn] "m"(a9fa20_exitfn), [get] "m"(a9fa20_get), [c4dab0] "m"(a9fa20_c4dab0), [ray] "m"(a9fa20_ray), [c4ec30] "m"(a9fa20_c4ec30), [c4f2c0] "m"(a9fa20_c4f2c0), [elem] "m"(a9fa20_elem), [bln] "m"(a9fa20_bln), [tag] "m"(a9fa20_tag)
      : "memory");
}
#else
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
#endif

