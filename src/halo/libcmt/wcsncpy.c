/* kb object stubs -> libcmt/wcsncpy.c */

extern void RtlUnwind(void *a, void *b, void *c, void *d);

/* --- LIBCMT:wcsncpy.obj batch drafts (2026-07-26) --- */

/* 0x1dbc1e */

/* --- forward decls (auto) --- */
void FUN_001dbc1e(void);
void FUN_001dbc26(void);
void __global_unwind2(void);
void __local_unwind2(void);
void FUN_001dbdca(void);
void __seh_longjmp_unwind(void);
void _memchr(void);
int _wcscmp(const wchar_t *s1, const wchar_t *s2);
int FUN_001dbfa7(const wchar_t *s1, const wchar_t *s2);
size_t _wcscspn(const wchar_t *s, const wchar_t *reject);
wchar_t *_wcsncat(wchar_t *dest, const wchar_t *src, size_t count);
int _wcsncmp(const wchar_t *s1, const wchar_t *s2, size_t count);
wchar_t *_wcsncpy(wchar_t *dest, const wchar_t *src, size_t count);
wchar_t *_wcspbrk(const wchar_t *s, const wchar_t *accept);
wchar_t *_wcsrchr(const wchar_t *s, wchar_t c);
size_t _wcsspn(const wchar_t *s, const wchar_t *accept);
wchar_t *_wcsstr(const wchar_t *haystack, const wchar_t *needle);
wchar_t *_wcstok(wchar_t *s, const wchar_t *delim);
size_t FUN_001dc257(wchar_t *dest, const wchar_t *src, size_t count);
wchar_t *FUN_001dc27c(wchar_t *s, size_t count);
int __wcsicmp(const wchar_t *s1, const wchar_t *s2);
int __wcsnicmp(const wchar_t *s1, const wchar_t *s2, size_t count);
int FUN_001dc3e9(int c, int mask);
void __getwc_lk(void);
int _fgetwc(void *stream);
void FUN_001dc54a(void);
void FUN_001dc559(void);

void FUN_001dbc1e(void)
{
  __unlock_file();
}

/* FUN_001dbc26 (0x1dbc26) — XBE naked draft (batch 323). */
#if defined(__clang__)
static void (*const b1dbc26_c1dfeec)(void) = __ctrlfp;
static void (*const b1dbc26_c1dfdc4)(void) = __sptype;
static void (*const b1dbc26_c1dfb20)(void) = __handle_qnan1;
static void (*const b1dbc26_c1dfd23)(void) = FUN_001dfd23;
static void (*const b1dbc26_c1dfbd2)(void) = FUN_001dfbd2;

__attribute__((naked, noinline))
void FUN_001dbc26(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl $0xffff, %%esi\n\t"
      "pushl %%esi\n\t"
      "pushl 0x331488\n\t"
      "call *%[c1dfeec]\n\t"
      "fldl 0x8(%%ebp)\n\t"
      "popl %%ecx\n\t"
      "popl %%ecx\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl 0xe(%%ebp), %%eax\n\t"
      "pushl %%ecx\n\t"
      "andw $0x7ff0, %%ax\n\t"
      "cmpw $0x7ff0, %%ax\n\t"
      "pushl %%ecx\n\t"
      "fstpl (%%esp)\n\t"
      "jne .LFUN_001dbc26_3\n\t"
      "call *%[c1dfdc4]\n\t"
      "testl %%eax, %%eax\n\t"
      "popl %%ecx\n\t"
      "popl %%ecx\n\t"
      "jle .LFUN_001dbc26_2\n\t"
      "cmpl $2, %%eax\n\t"
      "jle .LFUN_001dbc26_1\n\t"
      "cmpl $3, %%eax\n\t"
      "jne .LFUN_001dbc26_2\n\t"
      "fldl 0x8(%%ebp)\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ecx\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0xc\n\t"
      "call *%[c1dfb20]\n\t"
      "addl $0x10, %%esp\n\t"
      "jmp .LFUN_001dbc26_7\n\t"
      ".LFUN_001dbc26_1:\n\t"
      "pushl %%esi\n\t"
      "pushl %%ebx\n\t"
      "call *%[c1dfeec]\n\t"
      "fldl 0x8(%%ebp)\n\t"
      "popl %%ecx\n\t"
      "popl %%ecx\n\t"
      "jmp .LFUN_001dbc26_7\n\t"
      ".LFUN_001dbc26_2:\n\t"
      "fldl 0x8(%%ebp)\n\t"
      "pushl %%ebx\n\t"
      "faddl 0x2573d8\n\t"
      "subl $0x10, %%esp\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "fldl 0x8(%%ebp)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0xc\n\t"
      "pushl $8\n\t"
      "jmp .LFUN_001dbc26_6\n\t"
      ".LFUN_001dbc26_3:\n\t"
      "call *%[c1dfd23]\n\t"
      "fstl -0x8(%%ebp)\n\t"
      "fcompl 0x8(%%ebp)\n\t"
      "popl %%ecx\n\t"
      "popl %%ecx\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .LFUN_001dbc26_5\n\t"
      ".LFUN_001dbc26_4:\n\t"
      "pushl %%esi\n\t"
      "pushl %%ebx\n\t"
      "call *%[c1dfeec]\n\t"
      "fldl -0x8(%%ebp)\n\t"
      "popl %%ecx\n\t"
      "popl %%ecx\n\t"
      "jmp .LFUN_001dbc26_7\n\t"
      ".LFUN_001dbc26_5:\n\t"
      "testb $0x20, %%bl\n\t"
      "jne .LFUN_001dbc26_4\n\t"
      "fldl -0x8(%%ebp)\n\t"
      "pushl %%ebx\n\t"
      "subl $0x10, %%esp\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "fldl 0x8(%%ebp)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0xc\n\t"
      "pushl $0x10\n\t"
      ".LFUN_001dbc26_6:\n\t"
      "call *%[c1dfbd2]\n\t"
      "addl $0x1c, %%esp\n\t"
      ".LFUN_001dbc26_7:\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      :
      : [c1dfeec] "m"(b1dbc26_c1dfeec), [c1dfdc4] "m"(b1dbc26_c1dfdc4), [c1dfb20] "m"(b1dbc26_c1dfb20), [c1dfd23] "m"(b1dbc26_c1dfd23), [c1dfbd2] "m"(b1dbc26_c1dfbd2)
      : "memory");
}
#else
#error "FUN_001dbc26: clang naked draft required"
#endif


/* 0x1dbcf4 */
void __global_unwind2(void)
{
  RtlUnwind(0, (void *)(uintptr_t)0x001dbd0c, 0, 0);
}

/* 0x1dbd36 */
void __local_unwind2(void)
{
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;

  /* cmp esi, -1 -> je 0x1dbd90 */
  /* relift: cmp esi, dword ptr [esp + 0x24] -> je 0x1dbd90 */
  /* relift: cmp dword ptr [ebx + esi*4 + 4], 0 -> jne 0x1dbd8e */
  FUN_001dbdca();
  /* relift: cmp dword ptr [ecx + 4], 0x1dbd14 -> jne 0x1dbdc0 */
  /* relift: cmp dword ptr [ecx + 8], edx -> jne 0x1dbdc0 */

  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
}

/* 0x1dbdca */
void FUN_001dbdca(void)
{
  int eax = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;

  /* relift: test dword ptr [eax + 4], 6 -> jne 0x1dbe8c */
  /* cmp esi, -1 -> je 0x1dbe85 */
  /* relift: cmp dword ptr [edi + ecx*4 + 4], 0 -> je 0x1dbe73 */
  __global_unwind2();
  __local_unwind2();
  /* relift: tail-call FUN_001dbdca(); */
  __local_unwind2();

  (void)eax;
  (void)ecx;
  (void)esi;
  (void)edi;
}

/* 0x1dbea9 */
void __seh_longjmp_unwind(void)
{

}

/* _memchr (0x1dbed0) — XBE naked draft (batch 310). */
#if defined(__clang__)


__attribute__((naked, noinline))
void _memchr(void)
{
  __asm__ volatile(
      "movl 0xc(%%esp), %%eax\n\t"
      "pushl %%ebx\n\t"
      "testl %%eax, %%eax\n\t"
      "je .L_memchr_6\n\t"
      "movl 0x8(%%esp), %%edx\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "movb 0xc(%%esp), %%bl\n\t"
      "testl $3, %%edx\n\t"
      "je .L_memchr_2\n\t"
      ".L_memchr_1:\n\t"
      "movb (%%edx), %%cl\n\t"
      "incl %%edx\n\t"
      "xorb %%bl, %%cl\n\t"
      "je .L_memchr_10\n\t"
      "decl %%eax\n\t"
      "je .L_memchr_6\n\t"
      "testl $3, %%edx\n\t"
      "jne .L_memchr_1\n\t"
      ".L_memchr_2:\n\t"
      "subl $4, %%eax\n\t"
      "jb .L_memchr_4\n\t"
      "pushl %%edi\n\t"
      "movl %%ebx, %%edi\n\t"
      "shll $8, %%ebx\n\t"
      "addl %%edi, %%ebx\n\t"
      "movl %%ebx, %%edi\n\t"
      "shll $0x10, %%ebx\n\t"
      "addl %%edi, %%ebx\n\t"
      "jmp .L_memchr_8\n\t"
      ".L_memchr_3:\n\t"
      "popl %%edi\n\t"
      ".L_memchr_4:\n\t"
      "addl $4, %%eax\n\t"
      "je .L_memchr_6\n\t"
      ".L_memchr_5:\n\t"
      "movb (%%edx), %%cl\n\t"
      "incl %%edx\n\t"
      "xorb %%bl, %%cl\n\t"
      "je .L_memchr_10\n\t"
      "decl %%eax\n\t"
      "jne .L_memchr_5\n\t"
      ".L_memchr_6:\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      ".L_memchr_7:\n\t"
      "subl $4, %%eax\n\t"
      "jb .L_memchr_3\n\t"
      ".L_memchr_8:\n\t"
      "movl (%%edx), %%ecx\n\t"
      "xorl %%ebx, %%ecx\n\t"
      "movl $0x7efefeff, %%edi\n\t"
      "addl %%ecx, %%edi\n\t"
      "xorl $0xffffffff, %%ecx\n\t"
      "xorl %%edi, %%ecx\n\t"
      "addl $4, %%edx\n\t"
      "andl $0x81010100, %%ecx\n\t"
      "je .L_memchr_7\n\t"
      "movl -0x4(%%edx), %%ecx\n\t"
      "xorb %%bl, %%cl\n\t"
      "je .L_memchr_13\n\t"
      "xorb %%bl, %%ch\n\t"
      "je .L_memchr_12\n\t"
      "shrl $0x10, %%ecx\n\t"
      "xorb %%bl, %%cl\n\t"
      "je .L_memchr_11\n\t"
      "xorb %%bl, %%ch\n\t"
      "je .L_memchr_9\n\t"
      "jmp .L_memchr_7\n\t"
      ".L_memchr_9:\n\t"
      "popl %%edi\n\t"
      ".L_memchr_10:\n\t"
      "leal -0x1(%%edx), %%eax\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      ".L_memchr_11:\n\t"
      "leal -0x2(%%edx), %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      ".L_memchr_12:\n\t"
      "leal -0x3(%%edx), %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      ".L_memchr_13:\n\t"
      "leal -0x4(%%edx), %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "_memchr: clang naked draft required"
#endif


/* _wcscmp (0x1dbf75) — XBE naked draft (batch 340). */
#if defined(__clang__)


__attribute__((naked, noinline))
int _wcscmp(const wchar_t *s1 __attribute__((unused)), const wchar_t *s2 __attribute__((unused)))
{
  __asm__ volatile(
      "movl 0x4(%%esp), %%edx\n\t"
      "pushl %%esi\n\t"
      "movl 0xc(%%esp), %%esi\n\t"
      "pushl %%edi\n\t"
      "jmp .L_wcscmp_2\n\t"
      ".L_wcscmp_1:\n\t"
      "testw %%cx, %%cx\n\t"
      "je .L_wcscmp_3\n\t"
      "incl %%edx\n\t"
      "incl %%edx\n\t"
      "incl %%esi\n\t"
      "incl %%esi\n\t"
      ".L_wcscmp_2:\n\t"
      "movw (%%esi), %%cx\n\t"
      "movzwl (%%edx), %%eax\n\t"
      "movzwl %%cx, %%edi\n\t"
      "subl %%edi, %%eax\n\t"
      "je .L_wcscmp_1\n\t"
      ".L_wcscmp_3:\n\t"
      "testl %%eax, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "jge .L_wcscmp_4\n\t"
      "orl $0xffffffff, %%eax\n\t"
      "ret\n\t"
      ".L_wcscmp_4:\n\t"
      "jle .L_wcscmp_5\n\t"
      "xorl %%eax, %%eax\n\t"
      "incl %%eax\n\t"
      ".L_wcscmp_5:\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "_wcscmp: clang naked draft required"
#endif


/* 0x1dbfa7 */
int FUN_001dbfa7(const wchar_t *s1, const wchar_t *s2)
{
  /* relift: no calls detected — manual review */
  (void)0;
  return 0;
}

/* _wcscspn (0x1dbfac) — XBE naked draft (batch 345). */
#if defined(__clang__)


__attribute__((naked, noinline))
size_t _wcscspn(const wchar_t *s __attribute__((unused)), const wchar_t *reject __attribute__((unused)))
{
  __asm__ volatile(
      "movl 0x4(%%esp), %%eax\n\t"
      "cmpw $0, (%%eax)\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "je .L_wcscspn_4\n\t"
      "movl 0x14(%%esp), %%ebx\n\t"
      "xorl %%edi, %%edi\n\t"
      "movw (%%ebx), %%di\n\t"
      ".L_wcscspn_1:\n\t"
      "testw %%di, %%di\n\t"
      "movl %%ebx, %%edx\n\t"
      "je .L_wcscspn_3\n\t"
      "movw (%%eax), %%si\n\t"
      "movl %%edi, %%ecx\n\t"
      ".L_wcscspn_2:\n\t"
      "cmpw %%si, %%cx\n\t"
      "je .L_wcscspn_4\n\t"
      "incl %%edx\n\t"
      "incl %%edx\n\t"
      "movw (%%edx), %%cx\n\t"
      "testw %%cx, %%cx\n\t"
      "jne .L_wcscspn_2\n\t"
      ".L_wcscspn_3:\n\t"
      "incl %%eax\n\t"
      "incl %%eax\n\t"
      "cmpw $0, (%%eax)\n\t"
      "jne .L_wcscspn_1\n\t"
      ".L_wcscspn_4:\n\t"
      "subl 0x10(%%esp), %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "sarl $1, %%eax\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "_wcscspn: clang naked draft required"
#endif


/* 0x1dbfef */
wchar_t *_wcsncat(wchar_t *dest, const wchar_t *src, size_t count)
{
  /* relift: no calls detected — manual review */
  (void)0;
  return NULL;
}

/* _wcsncmp (0x1dc02c) — XBE naked draft (batch 353). */
#if defined(__clang__)


__attribute__((naked, noinline))
int _wcsncmp(const wchar_t *s1 __attribute__((unused)), const wchar_t *s2 __attribute__((unused)), size_t count __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "cmpl $0, 0x10(%%ebp)\n\t"
      "jne .L_wcsncmp_1\n\t"
      "xorl %%eax, %%eax\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".L_wcsncmp_1:\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      ".L_wcsncmp_2:\n\t"
      "decl 0x10(%%ebp)\n\t"
      "je .L_wcsncmp_3\n\t"
      "movw (%%ecx), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "je .L_wcsncmp_3\n\t"
      "cmpw (%%edx), %%ax\n\t"
      "jne .L_wcsncmp_3\n\t"
      "incl %%ecx\n\t"
      "incl %%ecx\n\t"
      "incl %%edx\n\t"
      "incl %%edx\n\t"
      "jmp .L_wcsncmp_2\n\t"
      ".L_wcsncmp_3:\n\t"
      "movzwl (%%ecx), %%eax\n\t"
      "movzwl (%%edx), %%ecx\n\t"
      "subl %%ecx, %%eax\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "_wcsncmp: clang naked draft required"
#endif


/* 0x1dc061 */
wchar_t *_wcsncpy(wchar_t *dest, const wchar_t *src, size_t count)
{
  /* relift: no calls detected — manual review */
  (void)0;
  return NULL;
}

/* 0x1dc09e */
wchar_t *_wcspbrk(const wchar_t *s, const wchar_t *accept)
{
  /* relift: no calls detected — manual review */
  (void)0;
  return NULL;
}

/* 0x1dc0de */
wchar_t *_wcsrchr(const wchar_t *s, wchar_t c)
{
  /* relift: no calls detected — manual review */
  (void)0;
  return NULL;
}

/* _wcsspn (0x1dc10e) — XBE naked draft (batch 341). */
#if defined(__clang__)


__attribute__((naked, noinline))
size_t _wcsspn(const wchar_t *s __attribute__((unused)), const wchar_t *accept __attribute__((unused)))
{
  __asm__ volatile(
      "movl 0x4(%%esp), %%eax\n\t"
      "pushl %%ebx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw (%%eax), %%cx\n\t"
      "testw %%cx, %%cx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "je .L_wcsspn_4\n\t"
      "movl 0x14(%%esp), %%ebx\n\t"
      "xorl %%edi, %%edi\n\t"
      "movw (%%ebx), %%di\n\t"
      ".L_wcsspn_1:\n\t"
      "cmpw %%cx, %%di\n\t"
      "movl %%ebx, %%esi\n\t"
      "je .L_wcsspn_3\n\t"
      "movl %%edi, %%edx\n\t"
      ".L_wcsspn_2:\n\t"
      "testw %%dx, %%dx\n\t"
      "je .L_wcsspn_4\n\t"
      "incl %%esi\n\t"
      "incl %%esi\n\t"
      "movw (%%esi), %%dx\n\t"
      "cmpw %%cx, %%dx\n\t"
      "jne .L_wcsspn_2\n\t"
      ".L_wcsspn_3:\n\t"
      "incl %%eax\n\t"
      "incl %%eax\n\t"
      "movw (%%eax), %%cx\n\t"
      "testw %%cx, %%cx\n\t"
      "jne .L_wcsspn_1\n\t"
      ".L_wcsspn_4:\n\t"
      "subl 0x10(%%esp), %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "sarl $1, %%eax\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "_wcsspn: clang naked draft required"
#endif


/* 0x1dc154 */
wchar_t *_wcsstr(const wchar_t *haystack, const wchar_t *needle)
{
  /* relift: no calls detected — manual review */
  (void)0;
  return NULL;
}

/* 0x1dc1b2 */
wchar_t *_wcstok(wchar_t *s, const wchar_t *delim)
{
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  FUN_001dff91();
  /* cmp (int16_t)edx, (int16_t)ebx -> je 0x1dc203 */
  /* cmp (int16_t)edi, (int16_t)edx -> je 0x1dc1f4 */
  /* cmp (int16_t)edi, (int16_t)ebx -> jne 0x1dc1e5 */
  /* relift: cmp word ptr [esi], (int16_t)ebx -> je 0x1dc203 */
  /* cmp (int16_t)edx, (int16_t)ebx -> jne 0x1dc1db */
  /* cmp (int16_t)edx, (int16_t)edi -> je 0x1dc22d */
  /* cmp (int16_t)edx, (int16_t)ebx -> jne 0x1dc21e */
  /* relift: cmp word ptr [esi], (int16_t)ebx -> jne 0x1dc23b */
  /* relift: cmp word ptr [ecx], (int16_t)ebx -> jne 0x1dc211 */
  return NULL;

  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x1dc257 */
size_t FUN_001dc257(wchar_t *dest, const wchar_t *src, size_t count)
{
  int ebp = 0;

  /* relift: cmp dword ptr [ebp + 8], 0 -> je 0x1dc271 */
  _wcsncpy((wchar_t *)0, (wchar_t *)(uintptr_t)src, count);
  _wcslen((wchar_t *)(uintptr_t)src);
  return 0;

  (void)ebp;
}

/* 0x1dc27c */
wchar_t *FUN_001dc27c(wchar_t *s, size_t count)
{
  int esi = 0;

  /* cmp (int16_t)esi, (int16_t)eax -> je 0x1dc2c1 */
  /* relift: cmp dword ptr [0x4fc25c], 0 -> jne 0x1dc2ad */
  /* cmp (int16_t)esi, 0x61 -> jb 0x1dc2a8 */
  /* cmp (int16_t)esi, 0x7a -> ja 0x1dc2a8 */
  /* cmp (int16_t)esi, 0x100 -> jae 0x1dc2be */
  FUN_001dc3e9(0, 0);
  return NULL;

  (void)esi;
}

/* __wcsicmp (0x1dc2c3) — XBE naked draft (batch 339). */
#if defined(__clang__)
static wchar_t * (*const b1dc2c3_c1da8e3)(wchar_t *s, size_t count) = FUN_001da8e3;

__attribute__((naked, noinline))
int __wcsicmp(const wchar_t *s1 __attribute__((unused)), const wchar_t *s2 __attribute__((unused)))
{
  __asm__ volatile(
      "cmpl $0, 0x4fc25c\n\t"
      "pushl %%ebx\n\t"
      "jne .L__wcsicmp_4\n\t"
      "movl 0xc(%%esp), %%edx\n\t"
      "movl 0x8(%%esp), %%ecx\n\t"
      ".L__wcsicmp_1:\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "movw (%%ecx), %%bx\n\t"
      "cmpw $0x41, %%bx\n\t"
      "jb .L__wcsicmp_2\n\t"
      "cmpw $0x5a, %%bx\n\t"
      "ja .L__wcsicmp_2\n\t"
      "addl $0x20, %%ebx\n\t"
      ".L__wcsicmp_2:\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw (%%edx), %%ax\n\t"
      "cmpw $0x41, %%ax\n\t"
      "jb .L__wcsicmp_3\n\t"
      "cmpw $0x5a, %%ax\n\t"
      "ja .L__wcsicmp_3\n\t"
      "addl $0x20, %%eax\n\t"
      ".L__wcsicmp_3:\n\t"
      "incl %%ecx\n\t"
      "incl %%ecx\n\t"
      "incl %%edx\n\t"
      "incl %%edx\n\t"
      "testw %%bx, %%bx\n\t"
      "je .L__wcsicmp_7\n\t"
      "cmpw %%ax, %%bx\n\t"
      "je .L__wcsicmp_1\n\t"
      "jmp .L__wcsicmp_7\n\t"
      ".L__wcsicmp_4:\n\t"
      "pushl %%esi\n\t"
      "movl 0xc(%%esp), %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x14(%%esp), %%edi\n\t"
      ".L__wcsicmp_5:\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw (%%esi), %%ax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1da8e3]\n\t"
      "incl %%esi\n\t"
      "incl %%esi\n\t"
      "movl %%eax, %%ebx\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw (%%edi), %%ax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1da8e3]\n\t"
      "incl %%edi\n\t"
      "popl %%ecx\n\t"
      "incl %%edi\n\t"
      "testw %%bx, %%bx\n\t"
      "popl %%ecx\n\t"
      "je .L__wcsicmp_6\n\t"
      "cmpw %%ax, %%bx\n\t"
      "je .L__wcsicmp_5\n\t"
      ".L__wcsicmp_6:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      ".L__wcsicmp_7:\n\t"
      "movzwl %%ax, %%ecx\n\t"
      "movzwl %%bx, %%eax\n\t"
      "subl %%ecx, %%eax\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      :
      : [c1da8e3] "m"(b1dc2c3_c1da8e3)
      : "memory");
}
#else
#error "__wcsicmp: clang naked draft required"
#endif


/* __wcsnicmp (0x1dc34b) — XBE naked draft (batch 333). */
#if defined(__clang__)
static wchar_t * (*const b1dc34b_c1da8e3)(wchar_t *s, size_t count) = FUN_001da8e3;

__attribute__((naked, noinline))
int __wcsnicmp(const wchar_t *s1 __attribute__((unused)), const wchar_t *s2 __attribute__((unused)), size_t count __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "xorl %%eax, %%eax\n\t"
      "cmpl %%eax, 0x10(%%ebp)\n\t"
      "je .L__wcsnicmp_9\n\t"
      "cmpl %%eax, 0x4fc25c\n\t"
      "pushl %%ebx\n\t"
      "jne .L__wcsnicmp_5\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      ".L__wcsnicmp_1:\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw (%%ecx), %%ax\n\t"
      "cmpw $0x41, %%ax\n\t"
      "jb .L__wcsnicmp_2\n\t"
      "cmpw $0x5a, %%ax\n\t"
      "leal 0x20(%%eax), %%ebx\n\t"
      "jbe .L__wcsnicmp_3\n\t"
      ".L__wcsnicmp_2:\n\t"
      "movl %%eax, %%ebx\n\t"
      ".L__wcsnicmp_3:\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw (%%edx), %%ax\n\t"
      "cmpw $0x41, %%ax\n\t"
      "jb .L__wcsnicmp_4\n\t"
      "cmpw $0x5a, %%ax\n\t"
      "ja .L__wcsnicmp_4\n\t"
      "addl $0x20, %%eax\n\t"
      ".L__wcsnicmp_4:\n\t"
      "incl %%ecx\n\t"
      "incl %%ecx\n\t"
      "incl %%edx\n\t"
      "incl %%edx\n\t"
      "decl 0x10(%%ebp)\n\t"
      "je .L__wcsnicmp_8\n\t"
      "testw %%bx, %%bx\n\t"
      "je .L__wcsnicmp_8\n\t"
      "cmpw %%ax, %%bx\n\t"
      "je .L__wcsnicmp_1\n\t"
      "jmp .L__wcsnicmp_8\n\t"
      ".L__wcsnicmp_5:\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      ".L__wcsnicmp_6:\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw (%%esi), %%ax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1da8e3]\n\t"
      "incl %%esi\n\t"
      "incl %%esi\n\t"
      "movl %%eax, %%ebx\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw (%%edi), %%ax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1da8e3]\n\t"
      "incl %%edi\n\t"
      "popl %%ecx\n\t"
      "incl %%edi\n\t"
      "decl 0x10(%%ebp)\n\t"
      "popl %%ecx\n\t"
      "je .L__wcsnicmp_7\n\t"
      "testw %%bx, %%bx\n\t"
      "je .L__wcsnicmp_7\n\t"
      "cmpw %%ax, %%bx\n\t"
      "je .L__wcsnicmp_6\n\t"
      ".L__wcsnicmp_7:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      ".L__wcsnicmp_8:\n\t"
      "movzwl %%ax, %%ecx\n\t"
      "movzwl %%bx, %%eax\n\t"
      "subl %%ecx, %%eax\n\t"
      "popl %%ebx\n\t"
      ".L__wcsnicmp_9:\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c1da8e3] "m"(b1dc34b_c1da8e3)
      : "memory");
}
#else
#error "__wcsnicmp: clang naked draft required"
#endif


/* FUN_001dc3e9 (0x1dc3e9) — XBE naked draft (batch 355). */
#if defined(__clang__)


__attribute__((naked, noinline))
int FUN_001dc3e9(int c __attribute__((unused)), int mask __attribute__((unused)))
{
  __asm__ volatile(
      "cmpw $0xffff, 0x4(%%esp)\n\t"
      "je .LFUN_001dc3e9_1\n\t"
      "cmpw $0x100, 0x4(%%esp)\n\t"
      "jae .LFUN_001dc3e9_1\n\t"
      "movzwl 0x4(%%esp), %%eax\n\t"
      "movl 0x3317b8, %%ecx\n\t"
      "movw (%%ecx,%%eax,2), %%ax\n\t"
      "jmp .LFUN_001dc3e9_2\n\t"
      ".LFUN_001dc3e9_1:\n\t"
      "xorl %%eax, %%eax\n\t"
      ".LFUN_001dc3e9_2:\n\t"
      "movzwl 0x8(%%esp), %%ecx\n\t"
      "movzwl %%ax, %%eax\n\t"
      "andl %%ecx, %%eax\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "FUN_001dc3e9: clang naked draft required"
#endif


/* __getwc_lk (0x1dc41e) — XBE naked draft (batch 310). */
#if defined(__clang__)
static void (*const b1dc41e_c1e1abe)(void) = __filbuf;
static void (*const b1dc41e_c1e270c)(void) = _ungetc;
static void (*const b1dc41e_c1e2669)(void) = FUN_001e2669;
static int * (*const b1dc41e_c1db777)(void) = FUN_001db777;
static void (*const b1dc41e_c1e257d)(void) = __filwbuf;

__attribute__((naked, noinline))
void __getwc_lk(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "testb $0x40, 0xc(%%esi)\n\t"
      "pushl %%edi\n\t"
      "jne .L__getwc_lk_12\n\t"
      "movl 0x10(%%esi), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .L__getwc_lk_1\n\t"
      "movl %%eax, %%ecx\n\t"
      "sarl $5, %%ecx\n\t"
      "movl 0x632cc0(,%%ecx,4), %%ecx\n\t"
      "andl $0x1f, %%eax\n\t"
      "leal (%%eax,%%eax,4), %%eax\n\t"
      "leal (%%ecx,%%eax,8), %%eax\n\t"
      "jmp .L__getwc_lk_2\n\t"
      ".L__getwc_lk_1:\n\t"
      "movl $0x331608, %%eax\n\t"
      ".L__getwc_lk_2:\n\t"
      "testb $0x80, 0x4(%%eax)\n\t"
      "je .L__getwc_lk_12\n\t"
      "xorl %%edi, %%edi\n\t"
      "incl %%edi\n\t"
      "decl 0x4(%%esi)\n\t"
      "js .L__getwc_lk_3\n\t"
      "movl (%%esi), %%ecx\n\t"
      "movzbl (%%ecx), %%eax\n\t"
      "incl %%ecx\n\t"
      "movl %%ecx, (%%esi)\n\t"
      "jmp .L__getwc_lk_4\n\t"
      ".L__getwc_lk_3:\n\t"
      "pushl %%esi\n\t"
      "call *%[c1e1abe]\n\t"
      "popl %%ecx\n\t"
      ".L__getwc_lk_4:\n\t"
      "cmpl $-1, %%eax\n\t"
      "jne .L__getwc_lk_6\n\t"
      ".L__getwc_lk_5:\n\t"
      "orw $0xffff, %%ax\n\t"
      "jmp .L__getwc_lk_15\n\t"
      ".L__getwc_lk_6:\n\t"
      "movl 0x3317b4, %%ecx\n\t"
      "movb %%al, -0x4(%%ebp)\n\t"
      "movzbl %%al, %%eax\n\t"
      "testb $0x80, 0x1(%%ecx,%%eax,2)\n\t"
      "je .L__getwc_lk_10\n\t"
      "decl 0x4(%%esi)\n\t"
      "js .L__getwc_lk_7\n\t"
      "movl (%%esi), %%ecx\n\t"
      "movzbl (%%ecx), %%eax\n\t"
      "incl %%ecx\n\t"
      "movl %%ecx, (%%esi)\n\t"
      "jmp .L__getwc_lk_8\n\t"
      ".L__getwc_lk_7:\n\t"
      "pushl %%esi\n\t"
      "call *%[c1e1abe]\n\t"
      "popl %%ecx\n\t"
      ".L__getwc_lk_8:\n\t"
      "cmpl $-1, %%eax\n\t"
      "jne .L__getwc_lk_9\n\t"
      "movsbl -0x4(%%ebp), %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "call *%[c1e270c]\n\t"
      "popl %%ecx\n\t"
      "orw $0xffff, %%ax\n\t"
      "jmp .L__getwc_lk_14\n\t"
      ".L__getwc_lk_9:\n\t"
      "pushl $2\n\t"
      "movb %%al, -0x3(%%ebp)\n\t"
      "popl %%edi\n\t"
      ".L__getwc_lk_10:\n\t"
      "pushl %%edi\n\t"
      "leal -0x4(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal 0xa(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1e2669]\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "jne .L__getwc_lk_11\n\t"
      "call *%[c1db777]\n\t"
      "movl $0x2a, (%%eax)\n\t"
      "jmp .L__getwc_lk_5\n\t"
      ".L__getwc_lk_11:\n\t"
      "movw 0xa(%%ebp), %%ax\n\t"
      "jmp .L__getwc_lk_15\n\t"
      ".L__getwc_lk_12:\n\t"
      "addl $-2, 0x4(%%esi)\n\t"
      "js .L__getwc_lk_13\n\t"
      "movl (%%esi), %%ecx\n\t"
      "movw (%%ecx), %%ax\n\t"
      "addl $2, %%ecx\n\t"
      "movl %%ecx, (%%esi)\n\t"
      "jmp .L__getwc_lk_15\n\t"
      ".L__getwc_lk_13:\n\t"
      "pushl %%esi\n\t"
      "call *%[c1e257d]\n\t"
      ".L__getwc_lk_14:\n\t"
      "popl %%ecx\n\t"
      ".L__getwc_lk_15:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      :
      : [c1e1abe] "m"(b1dc41e_c1e1abe), [c1e270c] "m"(b1dc41e_c1e270c), [c1e2669] "m"(b1dc41e_c1e2669), [c1db777] "m"(b1dc41e_c1db777), [c1e257d] "m"(b1dc41e_c1e257d)
      : "memory");
}
#else
#error "__getwc_lk: clang naked draft required"
#endif


/* _fgetwc (0x1dc512) — XBE naked draft (batch 340). */
#if defined(__clang__)
static void (*const b1dc512_c1dd5c8)(void) = FUN_001dd5c8;
static void (*const b1dc512_c1d99ce)(void) = __lock_file;
static void (*const b1dc512_c1dc41e)(void) = __getwc_lk;
static void (*const b1dc512_c1dc54a)(void) = FUN_001dc54a;
static void (*const b1dc512_c1dd601)(void) = __SEH_epilog;

__attribute__((naked, noinline))
int _fgetwc(void *stream __attribute__((unused)))
{
  __asm__ volatile(
      "pushl $0xc\n\t"
      "pushl $0x2c7568\n\t"
      "call *%[c1dd5c8]\n\t"
      "pushl 0x8(%%ebp)\n\t"
      "call *%[c1d99ce]\n\t"
      "popl %%ecx\n\t"
      "andl $0, -0x4(%%ebp)\n\t"
      "pushl 0x8(%%ebp)\n\t"
      "call *%[c1dc41e]\n\t"
      "popl %%ecx\n\t"
      "movl %%eax, -0x1c(%%ebp)\n\t"
      "orl $0xffffffff, -0x4(%%ebp)\n\t"
      "call *%[c1dc54a]\n\t"
      "movw -0x1c(%%ebp), %%ax\n\t"
      "call *%[c1dd601]\n\t"
      "ret\n\t"
      :
      : [c1dd5c8] "m"(b1dc512_c1dd5c8), [c1d99ce] "m"(b1dc512_c1d99ce), [c1dc41e] "m"(b1dc512_c1dc41e), [c1dc54a] "m"(b1dc512_c1dc54a), [c1dd601] "m"(b1dc512_c1dd601)
      : "memory");
}
#else
#error "_fgetwc: clang naked draft required"
#endif


/* 0x1dc54a */
void FUN_001dc54a(void)
{
  __unlock_file();
}

/* FUN_001dc559 (0x1dc559) — XBE naked draft (batch 307). */
#if defined(__clang__)
static void (*const b1dc559_c1e2879)(void) = FUN_001e2879;
static int * (*const b1dc559_c1db777)(void) = FUN_001db777;
static void (*const b1dc559_c1de28c)(void) = __flsbuf;
static void (*const b1dc559_c1e2751)(void) = __flswbuf;

__attribute__((naked, noinline))
void FUN_001dc559(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0xc(%%ebp), %%esi\n\t"
      "testb $0x40, 0xc(%%esi)\n\t"
      "pushl %%edi\n\t"
      "jne .LFUN_001dc559_9\n\t"
      "movl 0x10(%%esi), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_001dc559_1\n\t"
      "movl %%eax, %%ecx\n\t"
      "sarl $5, %%ecx\n\t"
      "movl 0x632cc0(,%%ecx,4), %%ecx\n\t"
      "andl $0x1f, %%eax\n\t"
      "leal (%%eax,%%eax,4), %%eax\n\t"
      "leal (%%ecx,%%eax,8), %%eax\n\t"
      "jmp .LFUN_001dc559_2\n\t"
      ".LFUN_001dc559_1:\n\t"
      "movl $0x331608, %%eax\n\t"
      ".LFUN_001dc559_2:\n\t"
      "testb $0x80, 0x4(%%eax)\n\t"
      "je .LFUN_001dc559_9\n\t"
      "pushl 0x8(%%ebp)\n\t"
      "leal -0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1e2879]\n\t"
      "movl %%eax, %%ebx\n\t"
      "cmpl $-1, %%ebx\n\t"
      "popl %%ecx\n\t"
      "popl %%ecx\n\t"
      "jne .LFUN_001dc559_4\n\t"
      "call *%[c1db777]\n\t"
      "movl $0x2a, (%%eax)\n\t"
      ".LFUN_001dc559_3:\n\t"
      "orw $0xffff, %%ax\n\t"
      "jmp .LFUN_001dc559_11\n\t"
      ".LFUN_001dc559_4:\n\t"
      "xorl %%edi, %%edi\n\t"
      "testl %%ebx, %%ebx\n\t"
      "jle .LFUN_001dc559_8\n\t"
      ".LFUN_001dc559_5:\n\t"
      "decl 0x4(%%esi)\n\t"
      "js .LFUN_001dc559_6\n\t"
      "movl (%%esi), %%eax\n\t"
      "movb -0x8(%%ebp,%%edi,1), %%cl\n\t"
      "movb %%cl, (%%eax)\n\t"
      "movl (%%esi), %%ecx\n\t"
      "movzbl (%%ecx), %%eax\n\t"
      "incl %%ecx\n\t"
      "movl %%ecx, (%%esi)\n\t"
      "jmp .LFUN_001dc559_7\n\t"
      ".LFUN_001dc559_6:\n\t"
      "movsbl -0x8(%%ebp,%%edi,1), %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "call *%[c1de28c]\n\t"
      "popl %%ecx\n\t"
      "popl %%ecx\n\t"
      ".LFUN_001dc559_7:\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_001dc559_3\n\t"
      "incl %%edi\n\t"
      "cmpl %%ebx, %%edi\n\t"
      "jl .LFUN_001dc559_5\n\t"
      ".LFUN_001dc559_8:\n\t"
      "movw 0x8(%%ebp), %%ax\n\t"
      "jmp .LFUN_001dc559_11\n\t"
      ".LFUN_001dc559_9:\n\t"
      "addl $-2, 0x4(%%esi)\n\t"
      "js .LFUN_001dc559_10\n\t"
      "movl (%%esi), %%ecx\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movw %%ax, (%%ecx)\n\t"
      "addl $2, (%%esi)\n\t"
      "jmp .LFUN_001dc559_11\n\t"
      ".LFUN_001dc559_10:\n\t"
      "movzwl 0x8(%%ebp), %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "call *%[c1e2751]\n\t"
      "popl %%ecx\n\t"
      "popl %%ecx\n\t"
      ".LFUN_001dc559_11:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      :
      : [c1e2879] "m"(b1dc559_c1e2879), [c1db777] "m"(b1dc559_c1db777), [c1de28c] "m"(b1dc559_c1de28c), [c1e2751] "m"(b1dc559_c1e2751)
      : "memory");
}
#else
#error "FUN_001dc559: clang naked draft required"
#endif

/* --- LIBCMT:wcsncpy.obj orphan shells (2026-07-26) --- */

/* orphan 0x1dbea9 */
void FUN_001dbea9(void)
{
  __local_unwind2();
}
