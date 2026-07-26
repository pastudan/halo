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

/* 0x19f540 — biped_limp_noodle_valid_joint_rotation (large; stub draft) */
char biped_limp_noodle_valid_joint_rotation(int unit_handle, int16_t node_index,
                                            void *node_block)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int edi = 0;

  object_get_and_verify_type(0, 0);
  tag_get('dpib', 0);
  tag_get('rtna', 0);
  tag_block_get_element((void *)(uintptr_t)ebx, 0, 64);
  tag_block_get_element((void *)(uintptr_t)ebx, 0, 64);
  /* test (char)eax, 0x41 -> jne 0x19f5dd */
  /* test (int16_t)ecx, (int16_t)ecx -> je 0x19f9a4 */
  /* relift: test byte ptr [edx + 0x28], 4 -> jne 0x19f9a4 */
  normalize3d((float *)0);
  normalize3d((float *)(uintptr_t)eax);
  normalize3d((float *)0);
  FUN_001d94f0();
  matrix_inverse((float *)(uintptr_t)edi, (float *)(uintptr_t)edx);
  matrix_inverse((float *)(uintptr_t)ecx, (float *)0);
  matrix_scale_transform_vector((float *)(uintptr_t)ecx, (float *)(uintptr_t)eax, (float *)(uintptr_t)edx);
  matrix_scale_transform_vector((float *)(uintptr_t)edx, (float *)(uintptr_t)ecx, (float *)(uintptr_t)eax);
  /* test (char)eax, 2 -> je 0x19f8fb */
  FUN_00099490();
  display_assert((char *)0x002b4b00, (char *)0x002b4b48, 231, 0);
  system_exit(0);
  normalize3d((float *)0);
  matrix_scale_transform_vector((float *)(uintptr_t)ecx, (float *)(uintptr_t)eax, (float *)(uintptr_t)edx);
  /* test (char)eax, 1 -> jne 0x19f8f2 */
  FUN_0014dab0(0, 0);
  /* test (char)eax, (char)eax -> jne 0x19f8f2 */
  rotate_vector3d_by_sincos((float *)(uintptr_t)ecx, (float *)(uintptr_t)eax, 0.0f, 0.0f);
  FUN_001d94f0();
  /* test (char)eax, 0x41 -> jne 0x19f9a7 */
  /* test (char)eax, 0x41 -> jne 0x19f9a7 */
  /* relift: test byte ptr [ecx + 0x28], 4 -> jne 0x19f9ba */
  /* test (char)eax, (char)eax -> jne 0x19fa16 */
  /* relift: test dword ptr [ecx + eax*4], edx -> je 0x19fa13 */
  /* test (char)eax, 0x41 -> jne 0x19fa13 */
  return 0;

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)edi;
}

/* 0x19fa20 — unit animation node setup (large; stub draft) */
void FUN_0019fa20(int unit_handle, void *node_block)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  object_get_and_verify_type(0, 0);
  tag_get('dpib', 0);
  tag_get('rtna', 0);
  display_assert((char *)0x00253440, (char *)0x002b4b48, 319, 0);
  system_exit(0);
  /* test (char)eax, 0x41 -> jne 0x19fae0 */
  /* test (char)ecx, (char)ecx -> jbe 0x1a01bc */
  /* cmp (char)ecx, 0x1e -> jae 0x1a01bc */
  /* cmp dl, (char)ecx -> jae 0x1a018b */
  FUN_0014ec30(49320, (float *)(uintptr_t)esi, 0.0f, 0.0f, 0.0f, 0, (void *)0);
  csmemset((void *)(uintptr_t)edx, 0, 0);
  tag_block_get_element((void *)(uintptr_t)edx, 0, 0);
  FUN_0014dab0(0, 0);
  /* test (char)eax, (char)eax -> jne 0x19fca0 */
  FUN_0014f2c0((float *)(uintptr_t)edi, (float *)(uintptr_t)eax, (void *)0x004d9de8, (float *)(uintptr_t)edx, (float *)(uintptr_t)ecx, 0, 0);
  biped_limp_noodle_valid_joint_rotation(0, edx, (void *)(uintptr_t)esi);
  FUN_0014df70(0, (float *)0, (float *)0, 0, (void *)0);
  /* test (char)eax, (char)eax -> je 0x19fef8 */
  FUN_0014dab0(0, 0x3cf5c28f);
  FUN_0014dab0(0, 0x3cf5c28f);
  /* cmp eax, 2 -> jne 0x19fe2f */

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}
