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


/* 0x1dbf75 */
int _wcscmp(const wchar_t *s1, const wchar_t *s2)
{
  /* relift: no calls detected — manual review */
  (void)0;
  return 0;
}

/* 0x1dbfa7 */
int FUN_001dbfa7(const wchar_t *s1, const wchar_t *s2)
{
  /* relift: no calls detected — manual review */
  (void)0;
  return 0;
}

/* 0x1dbfac */
size_t _wcscspn(const wchar_t *s, const wchar_t *reject)
{
  /* relift: no calls detected — manual review */
  (void)0;
  return 0;
}

/* 0x1dbfef */
wchar_t *_wcsncat(wchar_t *dest, const wchar_t *src, size_t count)
{
  /* relift: no calls detected — manual review */
  (void)0;
  return NULL;
}

/* 0x1dc02c */
int _wcsncmp(const wchar_t *s1, const wchar_t *s2, size_t count)
{
  /* relift: no calls detected — manual review */
  (void)0;
  return 0;
}

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

/* 0x1dc10e */
size_t _wcsspn(const wchar_t *s, const wchar_t *accept)
{
  /* relift: no calls detected — manual review */
  (void)0;
  return 0;
}

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

/* 0x1dc2c3 */
int __wcsicmp(const wchar_t *s1, const wchar_t *s2)
{
  int eax = 0;
  int ebx = 0;
  int edi = 0;

  /* cmp (int16_t)ebx, 0x41 -> jb 0x1dc2e9 */
  /* cmp (int16_t)ebx, 0x5a -> ja 0x1dc2e9 */
  /* cmp (int16_t)eax, 0x41 -> jb 0x1dc2fd */
  /* cmp (int16_t)eax, 0x5a -> ja 0x1dc2fd */
  /* test (int16_t)ebx, (int16_t)ebx -> je 0x1dc341 */
  /* cmp (int16_t)ebx, (int16_t)eax -> je 0x1dc2d5 */
  FUN_001da8e3((wchar_t *)(uintptr_t)eax, edi);
  FUN_001da8e3((wchar_t *)(uintptr_t)eax, 0);
  /* cmp (int16_t)ebx, (int16_t)eax -> je 0x1dc317 */
  return 0;

  (void)eax;
  (void)ebx;
  (void)edi;
}

/* 0x1dc34b */
int __wcsnicmp(const wchar_t *s1, const wchar_t *s2, size_t count)
{
  int eax = 0;
  int ebx = 0;
  int edi = 0;
  int ebp = 0;

  /* relift: cmp dword ptr [ebp + 0x10], eax -> je 0x1dc3e7 */
  /* cmp (int16_t)eax, 0x41 -> jb 0x1dc37c */
  /* cmp (int16_t)eax, 0x41 -> jb 0x1dc392 */
  /* cmp (int16_t)eax, 0x5a -> ja 0x1dc392 */
  /* test (int16_t)ebx, (int16_t)ebx -> je 0x1dc3de */
  /* cmp (int16_t)ebx, (int16_t)eax -> je 0x1dc368 */
  FUN_001da8e3((wchar_t *)(uintptr_t)eax, edi);
  FUN_001da8e3((wchar_t *)(uintptr_t)eax, 0);
  /* test (int16_t)ebx, (int16_t)ebx -> je 0x1dc3dc */
  /* cmp (int16_t)ebx, (int16_t)eax -> je 0x1dc3af */
  return 0;

  (void)eax;
  (void)ebx;
  (void)edi;
  (void)ebp;
}

/* 0x1dc3e9 */
int FUN_001dc3e9(int c, int mask)
{
  /* relift: no calls detected — manual review */
  (void)0;
  return 0;
}

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


/* 0x1dc512 */
int _fgetwc(void *stream)
{
  FUN_001dd5c8();
  __lock_file();
  __getwc_lk();
  FUN_001dc54a();
  __SEH_epilog();
  return 0;
}

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
