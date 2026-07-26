/* cseries_initialize (0x8d830) — initialise debug allocation and profiling
 * subsystems, then clear the profiling-enable flag. */
void cseries_initialize(void)
{
  FUN_0008e650();
  FUN_0008f630();
  *(uint8_t *)0x449ef1 = 0;
}

/* cseries_dispose (0x8d850) — thunk → debug_dump_memory_for_file(NULL). */
void cseries_dispose(void)
{
  FUN_0008f1e0();
}

/* string_to_tag (0x8d860) — byte-swap the 4-character tag stored at *param_1
 * so it can be compared as a uint32 regardless of endianness. */
uint32_t string_to_tag(uint32_t *param_1)
{
  uint32_t v;
  v = *param_1;
  return ((v & 0xff0000) | v >> 0x10) >> 8 | ((v & 0xff00) | v << 0x10) << 8;
}

/* tag_to_string (0x8d890) — byte-swap param_1 and write it to *param_2,
 * then null-terminate the byte immediately after the stored value. */
uint32_t *tag_to_string(uint32_t param_1, uint32_t *param_2)
{
  *param_2 = ((param_1 & 0xff0000) | param_1 >> 0x10) >> 8 |
             ((param_1 & 0xff00) | param_1 << 0x10) << 8;
  *(uint8_t *)(param_2 + 1) = 0;
  return param_2;
}

/* strnlen (0x8d8d0) — bounded strlen: count non-null chars in s up to n.
 * Returns the number of characters before the first null, at most n. */
int strnlen(const char *s, int n)
{
  int count;
  char c;

  count = 0;
  if (0 < n) {
    do {
      c = *s;
      s = s + 1;
      if (c == '\0')
        return count;
      count = count + 1;
    } while (count < n);
  }
  return count;
}

/* strnupr (0x8d8f0) — convert up to n characters of s to uppercase in
 * place using the CRT toupper function. Returns s. */
char *strnupr(char *s, int n)
{
  char c;
  char *p;

  p = s;
  if (*p == '\0')
    return s;
  do {
    if (n-- <= 0)
      break;
    c = (char)crt_toupper((unsigned char)*p);
    *p = c;
    c = p[1];
    p++;
  } while (c != '\0');
  return s;
}

/* strnlwr (0x8d930) — convert up to n characters of s to lowercase in
 * place using the CRT tolower function. Returns s. */
char *strnlwr(char *s, int n)
{
  char c;
  char *p;

  p = s;
  if (*p == '\0')
    return s;
  do {
    if (n-- <= 0)
      break;
    c = (char)crt_tolower((unsigned char)*p);
    *p = c;
    c = p[1];
    p++;
  } while (c != '\0');
  return s;
}

/* strupr (0x8d970) — convert entire string s to uppercase in place using
 * the CRT toupper function. Returns s. */
char *strupr(char *s)
{
  char *p;
  char c;

  p = s;
  c = *p;
  while (c != '\0') {
    c = crt_toupper(*p);
    *p = c;
    p++;
    c = *p;
  }
  return s;
}

#include <stdarg.h>

/* Convert a string to lowercase in place and return it. */
char *csstr_tolower(char *s)
{
  char *p = s;
  while (*p != '\0') {
    if (*p >= 'A' && *p <= 'Z')
      *p = *p + ('a' - 'A');
    p++;
  }
  return s;
}

char *csprintf(char *buffer, const char *format, ...)
{
  va_list args;
  va_start(args, format);
  vsprintf(buffer, format, (char *)args);
  va_end(args);
  return buffer;
}

void display_assert(const char *reason, const char *filepath, int lineno,
                    bool halt)
{
  error(2, "EXCEPTION %s in %s,#%d: %s [rev=%s]", halt ? "halt" : "warn",
        filepath, lineno, reason ? reason : "<no reason given>",
        build_rev ? build_rev : "unknown");
  if (halt) {
    stack_walk(0);
  }
}

/* Byte-compare two buffers with assertions on non-null pointers and
 * reasonable size. Returns 0 if equal, non-zero otherwise. */
int csmemcmp(const void *a, const void *b, int size)
{
  const uint8_t *pa = a;
  const uint8_t *pb = b;
  int i;

  assert_halt(a && b);
  assert_halt((unsigned int)size <= 0x10000000);

  for (i = 0; i < size; i++) {
    if (pa[i] != pb[i])
      return (pa[i] < pb[i]) ? -1 : 1;
  }
  return 0;
}

void csmemmove(void *destination, const void *source, unsigned int size)
{
  assert_halt(destination && source);
  assert_halt(size >= 0 && size <= MAXIMUM_MEMCPY_MEMMOVE_SIZE);
  memmove(destination, source, size);
}

void *csmemset(void *buffer, int c, size_t size)
{
  uint32_t *dst32;
  uint8_t *dst8;
  uint32_t fill;
  size_t i;
  uint8_t b;

  assert_halt(buffer);
  assert_halt(size <= MAXIMUM_MEMSET_SIZE);

  b = (uint8_t)c;
  fill = (b << 24) | (b << 16) | (b << 8) | b;

  dst32 = (uint32_t *)buffer;
  for (i = size >> 2; i != 0; i--)
    *dst32++ = fill;

  dst8 = (uint8_t *)dst32;
  for (i = size & 3; i != 0; i--)
    *dst8++ = b;

  return buffer;
}

/* csstrcmp — string comparison with NULL-pointer assertion.
 * Uses an unrolled-by-2 byte comparison loop matching the original MSVC
 * codegen. Returns -1 if s1 < s2, 0 if equal, 1 if s1 > s2. */
int csstrcmp(const char *s1, const char *s2)
{
  unsigned char c1, c2;

  assert_halt(s1 && s2);

  for (;;) {
    c1 = *(unsigned char *)s1;
    c2 = *(unsigned char *)s2;
    if (c1 != c2)
      break;
    if (c1 == 0)
      return 0;

    c1 = ((unsigned char *)s1)[1];
    c2 = ((unsigned char *)s2)[1];
    if (c1 != c2)
      break;
    s1 += 2;
    s2 += 2;
    if (c1 == 0)
      return 0;
  }

  if (c1 < c2)
    return -1;
  return 1;
}

/* csstrcat — bounded string concatenation with assertions. */
char *csstrcat(char *destination, const char *source, size_t max_size)
{
  if (!destination || !source)
    return NULL;
  assert_halt(max_size < MAXIMUM_STRING_SIZE);

  crt_strncat(destination, source, max_size);
  return destination;
}

/* Forward declaration for CRT strncmp (available in XDK/CRT but not pulled
 * in by our Xbox target headers by default). */
extern int strncmp(const char *s1, const char *s2, unsigned int n);

/* 0x8ddd0 — Validated strncmp wrapper. Asserts both strings are non-null and
 * size is within MAXIMUM_STRING_SIZE, then delegates to strncmp. */
int csstrncmp(char *s1, char *s2, unsigned int size)
{
  assert_halt(s1 && s2);
  assert_halt(size <= 0x1fff);
  return strncmp(s1, s2, size);
}

#ifdef strncpy
#undef strncpy
#endif

void *csstrncpy(char *destination, const char *source, size_t size)
{
  assert_halt(destination && source);
  assert_halt(size < MAXIMUM_STRING_SIZE);

  strncpy(destination, source, size);

  return destination;
}

/* csstrtok — tokenize a string with an assertion on delimiters. */
char *csstrtok(char *string, const char *delimiters)
{
  assert_halt(delimiters);

  return crt_strtok(string, delimiters);
}

#ifdef strlen
#undef strlen
#endif

int csstrlen(const char *s1)
{
  int size;

  assert_halt(s1);
  size = xbox_strlen(s1);
  assert_halt(size >= 0 && size < MAXIMUM_STRING_SIZE);

  return size;
}

/* csstrcpy — inline string copy with size and overlap assertions.
 * Measures source length, asserts it's within bounds and non-overlapping,
 * then copies byte-by-byte. */
char *csstrcpy(char *destination, const char *source)
{
  const char *s;
  int source_size;
  char c;

  s = source;
  do {
    c = *s;
    s++;
  } while (c != 0);
  source_size = (int)(s - (source + 1));

  assert_halt(source_size >= 0 && source_size < MAXIMUM_STRING_SIZE);
  assert_halt(source + source_size < destination ||
              destination + source_size < source);

  {
    int offset = (int)destination - (int)source;
    const char *p = source;
    do {
      c = *p;
      *(char *)((int)p + offset) = c;
      p++;
    } while (c != 0);
  }

  return destination;
}

void *csmemcpy(void *destination, void *source, size_t size)
{
  uint32_t *dst32;
  uint32_t *src32;
  uint8_t *dst8;
  uint8_t *src8;
  size_t i;

  assert_halt(destination && source);
  assert_halt(size < MAXIMUM_MEMCPY_MEMMOVE_SIZE);
  assert_halt((uint8_t *)source + size <= (uint8_t *)destination ||
              (uint8_t *)destination + size <= (uint8_t *)source);

  dst32 = (uint32_t *)destination;
  src32 = (uint32_t *)source;
  for (i = size >> 2; i != 0; i--)
    *dst32++ = *src32++;

  dst8 = (uint8_t *)dst32;
  src8 = (uint8_t *)src32;
  for (i = size & 3; i != 0; i--)
    *dst8++ = *src8++;

  return destination;
}

/* csstricmp (0x8e190) — XBE naked draft (batch 87). */
#if defined(__clang__)
static char (*const b8e190_c92d60)(int16_t a1) = stack_walk;
static void (*const b8e190_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;
static void (*const b8e190_exitfn)(int) = system_exit;
static wchar_t * (*const b8e190_c1da8e3)(wchar_t *s, size_t count) = FUN_001da8e3;

__attribute__((naked, noinline))
int csstricmp(const char *s1 __attribute__((unused)), const char *s2 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ebx\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "testl %%ebx, %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "je .Lcsstricmp_1\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .Lcsstricmp_2\n\t"
      ".Lcsstricmp_1:\n\t"
      "pushl $0\n\t"
      "call *%[c92d60]\n\t"
      "pushl $0x267908\n\t"
      "pushl $0x18d\n\t"
      "pushl $0x267878\n\t"
      "pushl $0x267834\n\t"
      "pushl $0x267810\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x20, %%esp\n\t"
      ".Lcsstricmp_2:\n\t"
      "movsbw (%%ebx), %%ax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1da8e3]\n\t"
      "movsbw (%%edi), %%cx\n\t"
      "movzwl %%ax, %%esi\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1da8e3]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%esi, %%esi\n\t"
      "movzwl %%ax, %%eax\n\t"
      "je .Lcsstricmp_4\n\t"
      "subl %%edi, %%ebx\n\t"
      ".Lcsstricmp_3:\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lcsstricmp_5\n\t"
      "cmpl %%eax, %%esi\n\t"
      "jne .Lcsstricmp_6\n\t"
      "movsbw 0x1(%%ebx,%%edi,1), %%dx\n\t"
      "incl %%edi\n\t"
      "pushl %%edx\n\t"
      "call *%[c1da8e3]\n\t"
      "movzwl %%ax, %%esi\n\t"
      "movsbw (%%edi), %%ax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1da8e3]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%esi, %%esi\n\t"
      "movzwl %%ax, %%eax\n\t"
      "jne .Lcsstricmp_3\n\t"
      ".Lcsstricmp_4:\n\t"
      "popl %%edi\n\t"
      "negl %%eax\n\t"
      "popl %%esi\n\t"
      "sbbl %%eax, %%eax\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lcsstricmp_5:\n\t"
      "xorl %%eax, %%eax\n\t"
      "popl %%edi\n\t"
      "testl %%esi, %%esi\n\t"
      "popl %%esi\n\t"
      "setne %%al\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lcsstricmp_6:\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "cmpl %%eax, %%esi\n\t"
      "setg %%cl\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "leal -0x1(%%ecx,%%ecx,1), %%ecx\n\t"
      "movl %%ecx, %%eax\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c92d60] "m"(b8e190_c92d60), [c8f390] "m"(b8e190_c8f390), [exitfn] "m"(b8e190_exitfn), [c1da8e3] "m"(b8e190_c1da8e3)
      : "memory");
}
#else
#error "csstricmp: clang naked draft required"
#endif

