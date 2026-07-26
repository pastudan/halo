/* kb object stubs -> libcmt/stricmp.c */

/* --- LIBCMT:stricmp.obj batch drafts (2026-07-26) --- */

/* 0x1dd1d1 */
long FUN_001dd1d1(const wchar_t *s, wchar_t **endptr, int base)
{
  FUN_001dd00c();
  return 0;
}

/* 0x1dd1e8 */
unsigned long FUN_001dd1e8(const wchar_t *s, wchar_t **endptr, int base)
{
  FUN_001dd00c();
  return 0;
}

/* 0x1dd1ff */
double FUN_001dd1ff(const wchar_t *s, wchar_t **endptr)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int esi = 0;
  int ebp = 0;

  FUN_001dd5c8();
  FUN_001dc3e9(0, 0);
  /* test eax, eax -> je 0x1dd244 */
  FUN_001dc3e9(0, 0);
  /* test eax, eax -> jne 0x1dd22c */
  _wcslen((wchar_t *)(uintptr_t)ebx);
  FUN_001d90e0();
  _wcslen((wchar_t *)(uintptr_t)ebx);
  _malloc();
  /* test eax, eax -> jne 0x1dd2ab */
  FUN_001db777();
  /* relift: relift: fld qword ptr [0x2602c0] */
  /* relift: cmp word ptr [ebx], 0 -> je 0x1dd2ea */
  FUN_001e2879();
  /* test eax, eax -> jle 0x1dd2ea */
  /* relift: cmp word ptr [esi], 0 -> jne 0x1dd2c9 */
  FUN_001e1e20();
  /* relift: cmp dword ptr [ebp - 0x20], 0 -> je 0x1dd315 */
  FUN_001dde24();
  /* test eax, eax -> je 0x1dd324 */
  /* test (int16_t)ecx, 0x240 -> je 0x1dd33a */
  /* test eax, eax -> je 0x1dd36c */
  /* test (char)ecx, 0x81 -> je 0x1dd34f */
  /* relift: relift: fld qword ptr [0x331934] */
  /* relift: cmp word ptr [ebx], 0x2d -> jne 0x1dd356 */
  /* test (char)ecx, 1 -> je 0x1dd369 */
  FUN_001db777();
  __SEH_epilog();
  return 0;

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)esi;
  (void)ebp;
}

/* 0x1dd375 */
void __wtol(void)
{
  int eax = 0;

  FUN_001dc3e9(0, 0);
  /* cmp eax, 0x2b -> jne 0x1dd3ab */
  __wchartodigit();

  (void)eax;
}

/* 0x1dd3d4 */
int FUN_001dd3d4(const wchar_t *s)
{
  int eax = 0;

  FUN_001dc3e9(0, 0);
  /* cmp eax, 0x2b -> jne 0x1dd3ab */
  __wchartodigit();
  return 0;

  (void)eax;
}

/* 0x1dd3d9 */
void __wtoi64(void)
{
  int eax = 0;

  FUN_001dc3e9(0, 0);
  /* cmp eax, 0x2b -> jne 0x1dd413 */
  __allmul();
  __wchartodigit();

  (void)eax;
}

/* 0x1dd467 */
wchar_t *__wctime(const void *timeptr)
{
  int eax = 0;

  crt_localtime((void *)0);
  __wasctime((void *)(uintptr_t)eax);
  return NULL;

  (void)eax;
}

/* 0x1dd480 */
void _store_dt(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x1dd49a */
wchar_t *__wasctime(const void *timeptr)
{
  int ecx = 0;
  int esi = 0;

  FUN_001dff91();
  /* relift: cmp dword ptr [esi + 0x40], 0 -> jne 0x1dd4bf */
  _malloc();
  /* cmp ecx, 3 -> jl 0x1dd4d6 */
  _store_dt();
  _store_dt();
  _store_dt();
  _store_dt();
  _store_dt();
  _store_dt();
  return NULL;

  (void)ecx;
  (void)esi;
}

/* 0x1dd576 */
int FUN_001dd576(int param)
{
  int ecx = 0;
  int edx = 0;
  int esi = 0;

  FUN_001dff91();
  /* relift: cmp dword ptr [esi + 0x24], 0 -> jne 0x1dd59b */
  _malloc();
  /* cmp edx, ecx -> jge 0x1dd5b2 */
  /* test (char)ecx, (char)ecx -> jne 0x1dd5bb */
  return 0;

  (void)ecx;
  (void)edx;
  (void)esi;
}

/* 0x1dd5c8 */
void FUN_001dd5c8(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x1dd601 */
void __SEH_epilog(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x1dd620 */
void __allmul(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x1dd660 */
void __aullshr(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x1dd680 */
void __aullrem(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x1dd6f5 */
void FUN_001dd6f5(void)
{
  FUN_001e2984();
  __flsbuf();
  __flsbuf();
}

/* 0x1dd770 */
void __aulldiv(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x1dd7e0 */
void __allshr(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x1dd801 */
int crt_stricmp(const char *a, const char *b)
{
  int ebx = 0;
  int ecx = 0;

  /* relift: cmp dword ptr [0x4fc25c], 0 -> jne 0x1dd80f */
  crt_tolower(0);
  crt_tolower(0);
  /* cmp ebx, ecx -> je 0x1dd81a */
  return 0;

  (void)ebx;
  (void)ecx;
}

/* 0x1dd850 */
void __alldiv(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x1dd8fa */
void __copysign(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x1dd91b */
void __chgsign(void)
{
  FUN_001e3a9a();
}

/* 0x1dd957 */
void FUN_001dd957(void)
{
  int eax = 0;

  __ctrlfp();
  __sptype();
  /* cmp eax, 2 -> jle 0x1dd9b3 */
  /* cmp eax, 3 -> jne 0x1dd9be */
  __handle_qnan1();
  __ctrlfp();
  /* relift: relift: fcomp qword ptr [0x2602c0] */
  /* relift: relift: fld qword ptr [0x331718] */
  FUN_001dfbd2();
  FUN_001dfe1f();
  __ctrlfp();

  (void)eax;
}

/* FUN_001dda3d (0x1dda3d) — XBE naked draft (batch 300). */
#if defined(__clang__)
static void (*const b1dda3d_c1dfeec)(void) = __ctrlfp;
static void (*const b1dda3d_c1dfe1f)(void) = FUN_001dfe1f;
static void (*const b1dda3d_c1dfd36)(void) = __set_exp;
static void (*const b1dda3d_c1dfc72)(void) = FUN_001dfc72;
static void (*const b1dda3d_c1dfb73)(void) = __handle_qnan2;

__attribute__((naked, noinline))
void FUN_001dda3d(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x14, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl $0xffff, %%esi\n\t"
      "pushl %%esi\n\t"
      "pushl $0x133f\n\t"
      "call *%[c1dfeec]\n\t"
      "movl 0xe(%%ebp), %%edi\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "popl %%ecx\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "popl %%ecx\n\t"
      "movl $0x7ff0, %%ecx\n\t"
      "movl %%edi, %%eax\n\t"
      "andw %%cx, %%ax\n\t"
      "cmpw %%cx, %%ax\n\t"
      "je .LFUN_001dda3d_1\n\t"
      "movl 0x16(%%ebp), %%eax\n\t"
      "andw %%cx, %%ax\n\t"
      "cmpw %%cx, %%ax\n\t"
      "jne .LFUN_001dda3d_5\n\t"
      ".LFUN_001dda3d_1:\n\t"
      "movl $0x7ff8, %%eax\n\t"
      "andl %%eax, %%edi\n\t"
      "cmpw %%cx, %%di\n\t"
      "movl $0x7ffff, %%ebx\n\t"
      "jne .LFUN_001dda3d_2\n\t"
      "testl %%ebx, 0xc(%%ebp)\n\t"
      "jne .LFUN_001dda3d_3\n\t"
      "testl %%edx, %%edx\n\t"
      "jne .LFUN_001dda3d_3\n\t"
      ".LFUN_001dda3d_2:\n\t"
      "movl 0x16(%%ebp), %%esi\n\t"
      "andl %%eax, %%esi\n\t"
      "cmpw %%cx, %%si\n\t"
      "jne .LFUN_001dda3d_4\n\t"
      "testl %%ebx, 0x14(%%ebp)\n\t"
      "jne .LFUN_001dda3d_3\n\t"
      "cmpl $0, 0x10(%%ebp)\n\t"
      "je .LFUN_001dda3d_4\n\t"
      ".LFUN_001dda3d_3:\n\t"
      "pushl -0x4(%%ebp)\n\t"
      "fldl 0x8(%%ebp)\n\t"
      "faddl 0x10(%%ebp)\n\t"
      "subl $0x18, %%esp\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "fldl 0x10(%%ebp)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "fldl 0x8(%%ebp)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x26\n\t"
      "pushl $8\n\t"
      "jmp .LFUN_001dda3d_22\n\t"
      ".LFUN_001dda3d_4:\n\t"
      "cmpw %%ax, %%di\n\t"
      "je .LFUN_001dda3d_24\n\t"
      "cmpw %%ax, %%si\n\t"
      "je .LFUN_001dda3d_24\n\t"
      "movl $0xffff, %%esi\n\t"
      ".LFUN_001dda3d_5:\n\t"
      "fldl 0x8(%%ebp)\n\t"
      "fldl 0x10(%%ebp)\n\t"
      "fcomp %%st(1)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .LFUN_001dda3d_6\n\t"
      "pushl %%esi\n\t"
      "fstp %%st(0)\n\t"
      "pushl -0x4(%%ebp)\n\t"
      "call *%[c1dfeec]\n\t"
      "fldl 0x8(%%ebp)\n\t"
      "popl %%ecx\n\t"
      "popl %%ecx\n\t"
      "jmp .LFUN_001dda3d_25\n\t"
      ".LFUN_001dda3d_6:\n\t"
      "fldl 0x2602c0\n\t"
      "fld %%st(1)\n\t"
      "fcomp %%st(1)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .LFUN_001dda3d_8\n\t"
      "fldl 0x10(%%ebp)\n\t"
      "movl $1, -0x14(%%ebp)\n\t"
      "fcomp %%st(2)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_001dda3d_7\n\t"
      "andl $0, -0x10(%%ebp)\n\t"
      "jmp .LFUN_001dda3d_8\n\t"
      ".LFUN_001dda3d_7:\n\t"
      "movl $0x80000000, -0x10(%%ebp)\n\t"
      ".LFUN_001dda3d_8:\n\t"
      "fld %%st(1)\n\t"
      "fcomp %%st(1)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_001dda3d_9\n\t"
      "fldl 0x10(%%ebp)\n\t"
      "fcomp %%st(2)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .LFUN_001dda3d_10\n\t"
      ".LFUN_001dda3d_9:\n\t"
      "fld %%st(1)\n\t"
      "fcomp %%st(1)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_001dda3d_11\n\t"
      "fldl 0x10(%%ebp)\n\t"
      "fcomp %%st(2)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_001dda3d_11\n\t"
      ".LFUN_001dda3d_10:\n\t"
      "testl %%edx, %%edx\n\t"
      "fstp %%st(0)\n\t"
      "leal -0x1(%%edx), %%eax\n\t"
      "fstp %%st(0)\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "jne .LFUN_001dda3d_17\n\t"
      "decl %%eax\n\t"
      "jmp .LFUN_001dda3d_15\n\t"
      ".LFUN_001dda3d_11:\n\t"
      "fld %%st(1)\n\t"
      "fcomp %%st(1)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_001dda3d_12\n\t"
      "fldl 0x10(%%ebp)\n\t"
      "fcomp %%st(2)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .LFUN_001dda3d_13\n\t"
      ".LFUN_001dda3d_12:\n\t"
      "fld %%st(1)\n\t"
      "fcompp\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_001dda3d_16\n\t"
      "fldl 0x10(%%ebp)\n\t"
      "fcompp\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_001dda3d_17\n\t"
      "jmp .LFUN_001dda3d_14\n\t"
      ".LFUN_001dda3d_13:\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      ".LFUN_001dda3d_14:\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "incl %%edx\n\t"
      "testl %%edx, %%edx\n\t"
      "movl %%edx, -0x14(%%ebp)\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "jne .LFUN_001dda3d_17\n\t"
      "incl %%eax\n\t"
      ".LFUN_001dda3d_15:\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "jmp .LFUN_001dda3d_17\n\t"
      ".LFUN_001dda3d_16:\n\t"
      "fstp %%st(0)\n\t"
      ".LFUN_001dda3d_17:\n\t"
      "testw %%cx, -0xe(%%ebp)\n\t"
      "jne .LFUN_001dda3d_19\n\t"
      "testl $0xfffff, -0x10(%%ebp)\n\t"
      "jne .LFUN_001dda3d_18\n\t"
      "cmpl $0, -0x14(%%ebp)\n\t"
      "je .LFUN_001dda3d_19\n\t"
      ".LFUN_001dda3d_18:\n\t"
      "fldl -0x14(%%ebp)\n\t"
      "leal -0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ecx\n\t"
      "fstpl (%%esp)\n\t"
      "call *%[c1dfe1f]\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "addl $0x600, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ecx\n\t"
      "fstpl (%%esp)\n\t"
      "call *%[c1dfd36]\n\t"
      "addl $0xc, %%esp\n\t"
      "pushl -0x4(%%ebp)\n\t"
      "subl $0x18, %%esp\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "fldl 0x10(%%ebp)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "fldl 0x8(%%ebp)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x26\n\t"
      "pushl $0x12\n\t"
      "jmp .LFUN_001dda3d_22\n\t"
      ".LFUN_001dda3d_19:\n\t"
      "cmpl $0x7ff00000, -0x10(%%ebp)\n\t"
      "jne .LFUN_001dda3d_20\n\t"
      "cmpl $0, -0x14(%%ebp)\n\t"
      "je .LFUN_001dda3d_21\n\t"
      ".LFUN_001dda3d_20:\n\t"
      "cmpl $0xfff00000, -0x10(%%ebp)\n\t"
      "jne .LFUN_001dda3d_23\n\t"
      "cmpl $0, -0x14(%%ebp)\n\t"
      "jne .LFUN_001dda3d_23\n\t"
      ".LFUN_001dda3d_21:\n\t"
      "fldl -0x14(%%ebp)\n\t"
      "leal -0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ecx\n\t"
      "fstpl (%%esp)\n\t"
      "call *%[c1dfe1f]\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "addl $0xfffffa00, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ecx\n\t"
      "fstpl (%%esp)\n\t"
      "call *%[c1dfd36]\n\t"
      "addl $0xc, %%esp\n\t"
      "pushl -0x4(%%ebp)\n\t"
      "subl $0x18, %%esp\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "fldl 0x10(%%ebp)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "fldl 0x8(%%ebp)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x26\n\t"
      "pushl $0x11\n\t"
      ".LFUN_001dda3d_22:\n\t"
      "call *%[c1dfc72]\n\t"
      "addl $0x24, %%esp\n\t"
      "jmp .LFUN_001dda3d_25\n\t"
      ".LFUN_001dda3d_23:\n\t"
      "pushl %%esi\n\t"
      "pushl -0x4(%%ebp)\n\t"
      "call *%[c1dfeec]\n\t"
      "fldl -0x14(%%ebp)\n\t"
      "popl %%ecx\n\t"
      "popl %%ecx\n\t"
      "jmp .LFUN_001dda3d_25\n\t"
      ".LFUN_001dda3d_24:\n\t"
      "pushl -0x4(%%ebp)\n\t"
      "fldl 0x10(%%ebp)\n\t"
      "subl $0x10, %%esp\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "fldl 0x8(%%ebp)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x26\n\t"
      "call *%[c1dfb73]\n\t"
      "addl $0x18, %%esp\n\t"
      ".LFUN_001dda3d_25:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      :
      : [c1dfeec] "m"(b1dda3d_c1dfeec), [c1dfe1f] "m"(b1dda3d_c1dfe1f), [c1dfd36] "m"(b1dda3d_c1dfd36), [c1dfc72] "m"(b1dda3d_c1dfc72), [c1dfb73] "m"(b1dda3d_c1dfb73)
      : "memory");
}
#else
#error "FUN_001dda3d: clang naked draft required"
#endif


/* 0x1ddcc6 */
void FUN_001ddcc6(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x1ddd09 */
void FUN_001ddd09(void)
{
  int ecx = 0;
  int edx = 0;
  int ebp = 0;

  /* cmp (int16_t)edx, (int16_t)ecx -> jne 0x1ddd4a */
  __sptype();
  /* relift: test dword ptr [ebp + 0xc], 0xfffff -> jne 0x1ddd65 */
  /* relift: cmp dword ptr [ebp + 8], 0 -> je 0x1ddd75 */
  /* relift: relift: fcomp qword ptr [0x2602c0] */

  (void)ecx;
  (void)edx;
  (void)ebp;
}

/* 0x1ddda3 */
void FUN_001ddda3(void)
{
  int esi = 0;
  int ebp = 0;

  FUN_001dd5c8();
  /* relift: cmp dword ptr [ebp + 8], esi -> je 0x1dde6b */
  /* relift: cmp dword ptr [0x632ca0], 3 -> jne 0x1dde5c */
  FUN_001df055();
  FUN_001dde73();
  /* relift: cmp dword ptr [ebp - 0x1c], esi -> jne 0x1dde6b */
  FUN_001d0bb3();
  FUN_001d0b9c();
  __SEH_epilog();
  FUN_001defb3();

  (void)esi;
  (void)ebp;
}

/* 0x1ddda8 */
void FUN_001ddda8(void)
{
  __nh_malloc();
  FUN_001e3c37();
}

/* 0x1dddbf */
void FUN_001dddbf(void)
{
  int eax = 0;

  /* test eax, eax -> jne 0x1dddc8 */
  /* relift: cmp dword ptr [0x632ca0], 1 -> je 0x1dddd7 */
  FUN_001d0bb3();
  FUN_001d5c66();

  (void)eax;
}

/* 0x1ddde6 */
void __nh_malloc(void)
{
  int eax = 0;

  /* relift: cmp dword ptr [esp + 4], -0x20 -> ja 0x1dde0f */
  FUN_001dddbf();
  /* relift: cmp dword ptr [esp + 8], eax -> je 0x1dde11 */
  __callnewh();

  (void)eax;
}

/* 0x1dde12 */
void _malloc(void)
{
  __nh_malloc();
}

/* 0x1dde24 */
void FUN_001dde24(void)
{
  int esi = 0;
  int ebp = 0;

  FUN_001dd5c8();
  /* relift: cmp dword ptr [ebp + 8], esi -> je 0x1dde6b */
  /* relift: cmp dword ptr [0x632ca0], 3 -> jne 0x1dde5c */
  FUN_001df055();
  FUN_001dde73();
  /* relift: cmp dword ptr [ebp - 0x1c], esi -> jne 0x1dde6b */
  FUN_001d0bb3();
  FUN_001d0b9c();
  __SEH_epilog();

  (void)esi;
  (void)ebp;
}

/* 0x1dde73 */
void FUN_001dde73(void)
{
  FUN_001defb3();
}

/* 0x1dde7c */
void __forcdecpt(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;

  crt_tolower(0);
  FUN_001e153d();
  /* test eax, eax -> jne 0x1dde90 */
  /* relift: relift: mov (char)ecx, byte ptr [0x3317c0] */
  /* test (char)ecx, (char)ecx -> jne 0x1ddec5 */
  /* relift: relift: mov (char)ebx, byte ptr [0x3317c0] */
  /* cmp (char)ecx, (char)ebx -> je 0x1ddeec */
  /* test (char)ecx, (char)ecx -> jne 0x1ddee1 */
  /* test (char)ecx, (char)ecx -> je 0x1ddf1d */
  /* cmp (char)ecx, 0x65 -> je 0x1ddf06 */
  /* cmp (char)ecx, 0x45 -> je 0x1ddf06 */
  /* test (char)ecx, (char)ecx -> jne 0x1ddef5 */
  /* relift: cmp byte ptr [eax], 0x30 -> je 0x1ddf08 */
  /* relift: cmp byte ptr [eax], (char)ebx -> jne 0x1ddf13 */
  /* relift: relift: fcomp qword ptr [0x2602c0] */
  /* test (char)eax, 1 -> jne 0x1ddf36 */

  (void)eax;
  (void)ebx;
  (void)ecx;
}

/* 0x1ddf39 */
void __fassign(void)
{
  FUN_001e4048();
  FUN_001e40a3();
}

/* 0x1ddf77 */
void FUN_001ddf77(void)
{
  int ecx = 0;
  int edx = 0;
  int esi = 0;

  /* test esi, esi -> je 0x1ddf99 */
  /* test dl, dl -> jne 0x1ddf81 */
  memmove((void *)(uintptr_t)ecx, (void *)0, 0);

  (void)ecx;
  (void)edx;
  (void)esi;
}

/* 0x1ddf9a */
void FUN_001ddf9a(void)
{
  int eax = 0;
  int ecx = 0;
  int edi = 0;

  FUN_001ddf77();
  /* test edi, edi -> jle 0x1ddfe6 */
  /* relift: relift: mov (char)ecx, byte ptr [0x3317c0] */
  /* relift: cmp byte ptr [eax], 0x30 -> je 0x1de03c */
  /* cmp eax, 0x64 -> jl 0x1de029 */
  /* cmp eax, 0xa -> jl 0x1de039 */

  (void)eax;
  (void)ecx;
  (void)edi;
}

/* 0x1de043 */
void FUN_001de043(void)
{
  FUN_001e4209();
  FUN_001e40d0();
  FUN_001ddf9a();
}

/* 0x1de0a3 */
void FUN_001de0a3(void)
{
  int eax = 0;
  int edi = 0;
  int ebp = 0;

  /* relift: cmp byte ptr [ebp + 0x10], 0 -> je 0x1de0d0 */
  /* relift: cmp eax, dword ptr [ebp + 0xc] -> jne 0x1de0d0 */
  /* test eax, eax -> jg 0x1de0f3 */
  FUN_001ddf77();
  /* relift: cmp dword ptr [ebp + 0xc], 0 -> jle 0x1de142 */
  FUN_001ddf77();
  /* relift: relift: mov (char)eax, byte ptr [0x3317c0] */
  /* test edi, edi -> jge 0x1de142 */
  /* relift: cmp byte ptr [ebp + 0x10], 0 -> jne 0x1de11e */
  /* relift: cmp dword ptr [ebp + 0xc], edi -> jl 0x1de121 */
  FUN_001ddf77();

  (void)eax;
  (void)edi;
  (void)ebp;
}

/* 0x1de14a */
void FUN_001de14a(void)
{
  FUN_001e4209();
  FUN_001e40d0();
  FUN_001de0a3();
}

/* 0x1de19c */
void FUN_001de19c(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;

  FUN_001e4209();
  FUN_001e40d0();
  /* cmp eax, -4 -> jl 0x1de210 */
  /* cmp eax, ebx -> jge 0x1de210 */
  /* test (char)ecx, (char)ecx -> je 0x1de1fd */
  /* test (char)eax, (char)eax -> jne 0x1de1f3 */
  FUN_001de0a3();
  FUN_001ddf9a();

  (void)eax;
  (void)ebx;
  (void)ecx;
}

/* 0x1de229 */
void __cfltcvt(void)
{
  int ebp = 0;

  /* relift: cmp dword ptr [ebp + 0x10], 0x65 -> je 0x1de264 */
  /* relift: cmp dword ptr [ebp + 0x10], 0x45 -> je 0x1de264 */
  /* relift: cmp dword ptr [ebp + 0x10], 0x66 -> jne 0x1de251 */
  FUN_001de14a();
  FUN_001de19c();
  FUN_001de043();

  (void)ebp;
}

/* 0x1de27a */
void FUN_001de27a(void)
{
  __controlfp();
}

/* 0x1de28c */
void __flsbuf(void)
{
  int eax = 0;
  int ebx = 0;
  int esi = 0;

  /* test (char)eax, 0x40 -> jne 0x1de398 */
  /* test (char)eax, 1 -> je 0x1de2c5 */
  /* test (char)eax, 0x10 -> je 0x1de398 */
  /* cmp esi, 0x331050 -> je 0x1de2ef */
  /* cmp esi, 0x331070 -> jne 0x1de2fa */
  __isatty();
  __getbuf();
  __write();
  /* cmp ebx, -1 -> je 0x1de34c */
  /* relift: test byte ptr [eax + 4], 0x20 -> je 0x1de364 */
  __lseek();
  __write();

  (void)eax;
  (void)ebx;
  (void)esi;
}

/* 0x1de3a5 */
void FUN_001de3a5(void)
{
  int eax = 0;
  int ecx = 0;

  /* relift: test byte ptr [ecx + 0xc], 0x40 -> je 0x1de3b1 */
  /* relift: cmp dword ptr [ecx + 8], 0 -> je 0x1de3d5 */
  __flsbuf();
  /* cmp eax, -1 -> jne 0x1de3d5 */

  (void)eax;
  (void)ecx;
}

/* 0x1de3d8 */
void FUN_001de3d8(void)
{
  int esi = 0;
  int ebp = 0;

  FUN_001de3a5();
  /* relift: cmp dword ptr [esi], -1 -> je 0x1de3f9 */
  /* relift: cmp dword ptr [ebp + 0xc], 0 -> jg 0x1de3e0 */

  (void)esi;
  (void)ebp;
}

/* 0x1de3fc */
void FUN_001de3fc(void)
{
  int esi = 0;
  int edi = 0;

  /* relift: cmp dword ptr [edi + 8], 0 -> jne 0x1de429 */
  FUN_001de3a5();
  /* relift: cmp dword ptr [esi], -1 -> je 0x1de430 */
  /* relift: cmp dword ptr [esp + 0xc], 0 -> jg 0x1de416 */

  (void)esi;
  (void)edi;
}

/* FUN_001de452 (0x1de452) — XBE naked draft (batch 297). */
#if defined(__clang__)
static void (*const b1de452_c1de3a5)(void) = FUN_001de3a5;
static void (*const b1de452_c1e2879)(void) = FUN_001e2879;
static void (*const b1de452_c1e42b0)(void) = __aulldvrm;
static void (*const b1de452_c1de3d8)(void) = FUN_001de3d8;
static void (*const b1de452_c1de3fc)(void) = FUN_001de3fc;

__attribute__((naked, noinline))
void FUN_001de452(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x24c, %%esp\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "pushl %%ebx\n\t"
      "movb (%%eax), %%bl\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "testb %%bl, %%bl\n\t"
      "movl %%ecx, -0xc(%%ebp)\n\t"
      "movl %%ecx, -0x14(%%ebp)\n\t"
      "je .LFUN_001de452_93\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "jmp .LFUN_001de452_2\n\t"
      ".LFUN_001de452_1:\n\t"
      "movl -0x30(%%ebp), %%ecx\n\t"
      ".LFUN_001de452_2:\n\t"
      "incl 0xc(%%ebp)\n\t"
      "xorl %%eax, %%eax\n\t"
      "cmpl %%eax, -0x14(%%ebp)\n\t"
      "jl .LFUN_001de452_92\n\t"
      "cmpb $0x20, %%bl\n\t"
      "jl .LFUN_001de452_3\n\t"
      "cmpb $0x78, %%bl\n\t"
      "jg .LFUN_001de452_3\n\t"
      "movsbl %%bl, %%eax\n\t"
      "movsbl 0x2c7658(%%eax), %%eax\n\t"
      "andl $0xf, %%eax\n\t"
      ".LFUN_001de452_3:\n\t"
      "movsbl 0x2c7678(%%ecx,%%eax,8), %%eax\n\t"
      "pushl $7\n\t"
      "sarl $4, %%eax\n\t"
      "popl %%ecx\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "movl %%eax, -0x30(%%ebp)\n\t"
      "ja .LFUN_001de452_91\n\t"
      "jmp *.LFUN_001de452_jt(,%%eax,4)\n\t"
      ".LFUN_001de452_4:\n\t"
      "xorl %%eax, %%eax\n\t"
      "orl $0xffffffff, -0x10(%%ebp)\n\t"
      "movl %%eax, -0x34(%%ebp)\n\t"
      "movl %%eax, -0x2c(%%ebp)\n\t"
      "movl %%eax, -0x20(%%ebp)\n\t"
      "movl %%eax, -0x1c(%%ebp)\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "movl %%eax, -0x24(%%ebp)\n\t"
      "jmp .LFUN_001de452_91\n\t"
      ".LFUN_001de452_5:\n\t"
      "movsbl %%bl, %%eax\n\t"
      "subl $0x20, %%eax\n\t"
      "je .LFUN_001de452_9\n\t"
      "subl $3, %%eax\n\t"
      "je .LFUN_001de452_8\n\t"
      "subl $8, %%eax\n\t"
      "je .LFUN_001de452_7\n\t"
      "decl %%eax\n\t"
      "decl %%eax\n\t"
      "je .LFUN_001de452_6\n\t"
      "subl $3, %%eax\n\t"
      "jne .LFUN_001de452_91\n\t"
      "orl $8, -0x4(%%ebp)\n\t"
      "jmp .LFUN_001de452_91\n\t"
      ".LFUN_001de452_6:\n\t"
      "orl $4, -0x4(%%ebp)\n\t"
      "jmp .LFUN_001de452_91\n\t"
      ".LFUN_001de452_7:\n\t"
      "orl $1, -0x4(%%ebp)\n\t"
      "jmp .LFUN_001de452_91\n\t"
      ".LFUN_001de452_8:\n\t"
      "orb $0x80, -0x4(%%ebp)\n\t"
      "jmp .LFUN_001de452_91\n\t"
      ".LFUN_001de452_9:\n\t"
      "orl $2, -0x4(%%ebp)\n\t"
      "jmp .LFUN_001de452_91\n\t"
      ".LFUN_001de452_10:\n\t"
      "cmpb $0x2a, %%bl\n\t"
      "jne .LFUN_001de452_11\n\t"
      "addl $4, 0x10(%%ebp)\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "movl -0x4(%%eax), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%eax, -0x20(%%ebp)\n\t"
      "jge .LFUN_001de452_91\n\t"
      "orl $4, -0x4(%%ebp)\n\t"
      "negl -0x20(%%ebp)\n\t"
      "jmp .LFUN_001de452_91\n\t"
      ".LFUN_001de452_11:\n\t"
      "movl -0x20(%%ebp), %%eax\n\t"
      "movsbl %%bl, %%ecx\n\t"
      "leal (%%eax,%%eax,4), %%eax\n\t"
      "leal -0x30(%%ecx,%%eax,2), %%eax\n\t"
      "movl %%eax, -0x20(%%ebp)\n\t"
      "jmp .LFUN_001de452_91\n\t"
      ".LFUN_001de452_12:\n\t"
      "andl $0, -0x10(%%ebp)\n\t"
      "jmp .LFUN_001de452_91\n\t"
      ".LFUN_001de452_13:\n\t"
      "cmpb $0x2a, %%bl\n\t"
      "jne .LFUN_001de452_14\n\t"
      "addl $4, 0x10(%%ebp)\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "movl -0x4(%%eax), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "jge .LFUN_001de452_91\n\t"
      "orl $0xffffffff, -0x10(%%ebp)\n\t"
      "jmp .LFUN_001de452_91\n\t"
      ".LFUN_001de452_14:\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "movsbl %%bl, %%ecx\n\t"
      "leal (%%eax,%%eax,4), %%eax\n\t"
      "leal -0x30(%%ecx,%%eax,2), %%eax\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "jmp .LFUN_001de452_91\n\t"
      ".LFUN_001de452_15:\n\t"
      "cmpb $0x49, %%bl\n\t"
      "je .LFUN_001de452_18\n\t"
      "cmpb $0x68, %%bl\n\t"
      "je .LFUN_001de452_17\n\t"
      "cmpb $0x6c, %%bl\n\t"
      "je .LFUN_001de452_16\n\t"
      "cmpb $0x77, %%bl\n\t"
      "jne .LFUN_001de452_91\n\t"
      "orb $8, -0x3(%%ebp)\n\t"
      "jmp .LFUN_001de452_91\n\t"
      ".LFUN_001de452_16:\n\t"
      "orl $0x10, -0x4(%%ebp)\n\t"
      "jmp .LFUN_001de452_91\n\t"
      ".LFUN_001de452_17:\n\t"
      "orl $0x20, -0x4(%%ebp)\n\t"
      "jmp .LFUN_001de452_91\n\t"
      ".LFUN_001de452_18:\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "movb (%%ecx), %%al\n\t"
      "cmpb $0x36, %%al\n\t"
      "jne .LFUN_001de452_19\n\t"
      "cmpb $0x34, 0x1(%%ecx)\n\t"
      "jne .LFUN_001de452_19\n\t"
      "incl %%ecx\n\t"
      "incl %%ecx\n\t"
      "orb $0x80, -0x3(%%ebp)\n\t"
      "movl %%ecx, 0xc(%%ebp)\n\t"
      "jmp .LFUN_001de452_91\n\t"
      ".LFUN_001de452_19:\n\t"
      "cmpb $0x33, %%al\n\t"
      "jne .LFUN_001de452_20\n\t"
      "cmpb $0x32, 0x1(%%ecx)\n\t"
      "jne .LFUN_001de452_20\n\t"
      "incl %%ecx\n\t"
      "incl %%ecx\n\t"
      "andb $0x7f, -0x3(%%ebp)\n\t"
      "movl %%ecx, 0xc(%%ebp)\n\t"
      "jmp .LFUN_001de452_91\n\t"
      ".LFUN_001de452_20:\n\t"
      "cmpb $0x64, %%al\n\t"
      "je .LFUN_001de452_91\n\t"
      "cmpb $0x69, %%al\n\t"
      "je .LFUN_001de452_91\n\t"
      "cmpb $0x6f, %%al\n\t"
      "je .LFUN_001de452_91\n\t"
      "cmpb $0x75, %%al\n\t"
      "je .LFUN_001de452_91\n\t"
      "cmpb $0x78, %%al\n\t"
      "je .LFUN_001de452_91\n\t"
      "cmpb $0x58, %%al\n\t"
      "je .LFUN_001de452_91\n\t"
      "andl $0, -0x30(%%ebp)\n\t"
      ".LFUN_001de452_21:\n\t"
      "movl 0x3317b4, %%ecx\n\t"
      "andl $0, -0x24(%%ebp)\n\t"
      "movzbl %%bl, %%eax\n\t"
      "testb $0x80, 0x1(%%ecx,%%eax,2)\n\t"
      "je .LFUN_001de452_22\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "leal -0x14(%%ebp), %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "call *%[c1de3a5]\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "movb (%%eax), %%bl\n\t"
      "incl 0xc(%%ebp)\n\t"
      ".LFUN_001de452_22:\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "leal -0x14(%%ebp), %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "call *%[c1de3a5]\n\t"
      "jmp .LFUN_001de452_91\n\t"
      ".LFUN_001de452_23:\n\t"
      "movsbl %%bl, %%eax\n\t"
      "cmpl $0x67, %%eax\n\t"
      "jg .LFUN_001de452_48\n\t"
      "cmpl $0x65, %%eax\n\t"
      "jge .LFUN_001de452_28\n\t"
      "cmpl $0x58, %%eax\n\t"
      "jg .LFUN_001de452_31\n\t"
      "je .LFUN_001de452_58\n\t"
      "subl $0x43, %%eax\n\t"
      "je .LFUN_001de452_29\n\t"
      "decl %%eax\n\t"
      "decl %%eax\n\t"
      "je .LFUN_001de452_27\n\t"
      "decl %%eax\n\t"
      "decl %%eax\n\t"
      "je .LFUN_001de452_27\n\t"
      "subl $0xc, %%eax\n\t"
      "jne .LFUN_001de452_81\n\t"
      "testw $0x830, -0x4(%%ebp)\n\t"
      "jne .LFUN_001de452_24\n\t"
      "orb $8, -0x3(%%ebp)\n\t"
      ".LFUN_001de452_24:\n\t"
      "movl -0x10(%%ebp), %%ecx\n\t"
      "cmpl $-1, %%ecx\n\t"
      "jne .LFUN_001de452_25\n\t"
      "movl $0x7fffffff, %%ecx\n\t"
      ".LFUN_001de452_25:\n\t"
      "addl $4, 0x10(%%ebp)\n\t"
      "testw $0x810, -0x4(%%ebp)\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "movl -0x4(%%eax), %%eax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "je .LFUN_001de452_52\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_001de452_26\n\t"
      "movl $0x2c76dc, -0x8(%%ebp)\n\t"
      ".LFUN_001de452_26:\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movl $1, -0x24(%%ebp)\n\t"
      "jmp .LFUN_001de452_50\n\t"
      ".LFUN_001de452_27:\n\t"
      "movl $1, -0x34(%%ebp)\n\t"
      "addb $0x20, %%bl\n\t"
      ".LFUN_001de452_28:\n\t"
      "orl $0x40, -0x4(%%ebp)\n\t"
      "xorl %%edi, %%edi\n\t"
      "cmpl %%edi, -0x10(%%ebp)\n\t"
      "leal -0x24c(%%ebp), %%eax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "jge .LFUN_001de452_41\n\t"
      "movl $6, -0x10(%%ebp)\n\t"
      "jmp .LFUN_001de452_42\n\t"
      ".LFUN_001de452_29:\n\t"
      "testw $0x830, -0x4(%%ebp)\n\t"
      "jne .LFUN_001de452_30\n\t"
      "orb $8, -0x3(%%ebp)\n\t"
      ".LFUN_001de452_30:\n\t"
      "addl $4, 0x10(%%ebp)\n\t"
      "testw $0x810, -0x4(%%ebp)\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "je .LFUN_001de452_35\n\t"
      "movswl -0x4(%%eax), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x24c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1e2879]\n\t"
      "testl %%eax, %%eax\n\t"
      "popl %%ecx\n\t"
      "popl %%ecx\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "jge .LFUN_001de452_36\n\t"
      "movl $1, -0x2c(%%ebp)\n\t"
      "jmp .LFUN_001de452_36\n\t"
      ".LFUN_001de452_31:\n\t"
      "subl $0x5a, %%eax\n\t"
      "je .LFUN_001de452_37\n\t"
      "subl $9, %%eax\n\t"
      "je .LFUN_001de452_30\n\t"
      "decl %%eax\n\t"
      "jne .LFUN_001de452_81\n\t"
      ".LFUN_001de452_32:\n\t"
      "orl $0x40, -0x4(%%ebp)\n\t"
      ".LFUN_001de452_33:\n\t"
      "movl $0xa, -0xc(%%ebp)\n\t"
      ".LFUN_001de452_34:\n\t"
      "movl -0x4(%%ebp), %%ebx\n\t"
      "movl $0x8000, %%esi\n\t"
      "testl %%ebx, %%esi\n\t"
      "je .LFUN_001de452_64\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "movl (%%ecx), %%eax\n\t"
      "movl 0x4(%%ecx), %%edx\n\t"
      "addl $8, %%ecx\n\t"
      "movl %%ecx, 0x10(%%ebp)\n\t"
      "jmp .LFUN_001de452_68\n\t"
      ".LFUN_001de452_35:\n\t"
      "movb -0x4(%%eax), %%al\n\t"
      "movb %%al, -0x24c(%%ebp)\n\t"
      "movl $1, -0xc(%%ebp)\n\t"
      ".LFUN_001de452_36:\n\t"
      "leal -0x24c(%%ebp), %%eax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "jmp .LFUN_001de452_81\n\t"
      ".LFUN_001de452_37:\n\t"
      "addl $4, 0x10(%%ebp)\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "movl -0x4(%%eax), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_001de452_39\n\t"
      "movl 0x4(%%eax), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .LFUN_001de452_39\n\t"
      "testb $8, -0x3(%%ebp)\n\t"
      "movswl (%%eax), %%eax\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "je .LFUN_001de452_38\n\t"
      "cdq\n\t"
      "subl %%edx, %%eax\n\t"
      "sarl $1, %%eax\n\t"
      "movl $1, -0x24(%%ebp)\n\t"
      "jmp .LFUN_001de452_80\n\t"
      ".LFUN_001de452_38:\n\t"
      "andl $0, -0x24(%%ebp)\n\t"
      "jmp .LFUN_001de452_80\n\t"
      ".LFUN_001de452_39:\n\t"
      "movl $0x2c76d4, %%eax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "leal 0x1(%%eax), %%edx\n\t"
      ".LFUN_001de452_40:\n\t"
      "movb (%%eax), %%cl\n\t"
      "incl %%eax\n\t"
      "testb %%cl, %%cl\n\t"
      "jne .LFUN_001de452_40\n\t"
      "jmp .LFUN_001de452_47\n\t"
      ".LFUN_001de452_41:\n\t"
      "jne .LFUN_001de452_42\n\t"
      "cmpb $0x67, %%bl\n\t"
      "jne .LFUN_001de452_42\n\t"
      "movl $1, -0x10(%%ebp)\n\t"
      ".LFUN_001de452_42:\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "pushl -0x34(%%ebp)\n\t"
      "addl $8, %%eax\n\t"
      "pushl -0x10(%%ebp)\n\t"
      "movl %%eax, 0x10(%%ebp)\n\t"
      "movl -0x4(%%eax), %%eax\n\t"
      "movl %%eax, -0x40(%%ebp)\n\t"
      "movsbl %%bl, %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x24c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x44(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl %%ecx, -0x44(%%ebp)\n\t"
      "call *0x3314a0\n\t"
      "movl -0x4(%%ebp), %%esi\n\t"
      "addl $0x14, %%esp\n\t"
      "andl $0x80, %%esi\n\t"
      "je .LFUN_001de452_43\n\t"
      "cmpl %%edi, -0x10(%%ebp)\n\t"
      "jne .LFUN_001de452_43\n\t"
      "leal -0x24c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *0x3314ac\n\t"
      "popl %%ecx\n\t"
      ".LFUN_001de452_43:\n\t"
      "cmpb $0x67, %%bl\n\t"
      "jne .LFUN_001de452_44\n\t"
      "cmpl %%edi, %%esi\n\t"
      "jne .LFUN_001de452_44\n\t"
      "leal -0x24c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *0x3314a4\n\t"
      "popl %%ecx\n\t"
      ".LFUN_001de452_44:\n\t"
      "cmpb $0x2d, -0x24c(%%ebp)\n\t"
      "jne .LFUN_001de452_45\n\t"
      "orb $1, -0x3(%%ebp)\n\t"
      "leal -0x24b(%%ebp), %%eax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      ".LFUN_001de452_45:\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "leal 0x1(%%eax), %%edx\n\t"
      ".LFUN_001de452_46:\n\t"
      "movb (%%eax), %%cl\n\t"
      "incl %%eax\n\t"
      "testb %%cl, %%cl\n\t"
      "jne .LFUN_001de452_46\n\t"
      ".LFUN_001de452_47:\n\t"
      "subl %%edx, %%eax\n\t"
      "jmp .LFUN_001de452_80\n\t"
      ".LFUN_001de452_48:\n\t"
      "subl $0x69, %%eax\n\t"
      "je .LFUN_001de452_32\n\t"
      "subl $5, %%eax\n\t"
      "je .LFUN_001de452_61\n\t"
      "decl %%eax\n\t"
      "je .LFUN_001de452_60\n\t"
      "decl %%eax\n\t"
      "je .LFUN_001de452_57\n\t"
      "subl $3, %%eax\n\t"
      "je .LFUN_001de452_24\n\t"
      "decl %%eax\n\t"
      "decl %%eax\n\t"
      "je .LFUN_001de452_33\n\t"
      "subl $3, %%eax\n\t"
      "jne .LFUN_001de452_81\n\t"
      "movl $0x27, -0x28(%%ebp)\n\t"
      "jmp .LFUN_001de452_59\n\t"
      ".LFUN_001de452_49:\n\t"
      "decl %%ecx\n\t"
      "cmpw $0, (%%eax)\n\t"
      "je .LFUN_001de452_51\n\t"
      "incl %%eax\n\t"
      "incl %%eax\n\t"
      ".LFUN_001de452_50:\n\t"
      "testl %%ecx, %%ecx\n\t"
      "jne .LFUN_001de452_49\n\t"
      ".LFUN_001de452_51:\n\t"
      "subl -0x8(%%ebp), %%eax\n\t"
      "sarl $1, %%eax\n\t"
      "jmp .LFUN_001de452_80\n\t"
      ".LFUN_001de452_52:\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_001de452_53\n\t"
      "movl $0x2c76d4, -0x8(%%ebp)\n\t"
      ".LFUN_001de452_53:\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "jmp .LFUN_001de452_55\n\t"
      ".LFUN_001de452_54:\n\t"
      "decl %%ecx\n\t"
      "cmpb $0, (%%eax)\n\t"
      "je .LFUN_001de452_56\n\t"
      "incl %%eax\n\t"
      ".LFUN_001de452_55:\n\t"
      "testl %%ecx, %%ecx\n\t"
      "jne .LFUN_001de452_54\n\t"
      ".LFUN_001de452_56:\n\t"
      "subl -0x8(%%ebp), %%eax\n\t"
      "jmp .LFUN_001de452_80\n\t"
      ".LFUN_001de452_57:\n\t"
      "movl $8, -0x10(%%ebp)\n\t"
      ".LFUN_001de452_58:\n\t"
      "movl %%ecx, -0x28(%%ebp)\n\t"
      ".LFUN_001de452_59:\n\t"
      "testb $0x80, -0x4(%%ebp)\n\t"
      "movl $0x10, -0xc(%%ebp)\n\t"
      "je .LFUN_001de452_34\n\t"
      "movb -0x28(%%ebp), %%al\n\t"
      "addb $0x51, %%al\n\t"
      "movb $0x30, -0x18(%%ebp)\n\t"
      "movb %%al, -0x17(%%ebp)\n\t"
      "movl $2, -0x1c(%%ebp)\n\t"
      "jmp .LFUN_001de452_34\n\t"
      ".LFUN_001de452_60:\n\t"
      "testb $0x80, -0x4(%%ebp)\n\t"
      "movl $8, -0xc(%%ebp)\n\t"
      "je .LFUN_001de452_34\n\t"
      "orb $2, -0x3(%%ebp)\n\t"
      "jmp .LFUN_001de452_34\n\t"
      ".LFUN_001de452_61:\n\t"
      "addl $4, 0x10(%%ebp)\n\t"
      "testb $0x20, -0x4(%%ebp)\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "movl -0x4(%%eax), %%eax\n\t"
      "je .LFUN_001de452_62\n\t"
      "movw -0x14(%%ebp), %%cx\n\t"
      "movw %%cx, (%%eax)\n\t"
      "jmp .LFUN_001de452_63\n\t"
      ".LFUN_001de452_62:\n\t"
      "movl -0x14(%%ebp), %%ecx\n\t"
      "movl %%ecx, (%%eax)\n\t"
      ".LFUN_001de452_63:\n\t"
      "movl $1, -0x2c(%%ebp)\n\t"
      "jmp .LFUN_001de452_91\n\t"
      ".LFUN_001de452_64:\n\t"
      "addl $4, 0x10(%%ebp)\n\t"
      "testb $0x20, %%bl\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "je .LFUN_001de452_67\n\t"
      "testb $0x40, %%bl\n\t"
      "je .LFUN_001de452_66\n\t"
      "movswl -0x4(%%eax), %%eax\n\t"
      ".LFUN_001de452_65:\n\t"
      "cdq\n\t"
      "jmp .LFUN_001de452_68\n\t"
      ".LFUN_001de452_66:\n\t"
      "movzwl -0x4(%%eax), %%eax\n\t"
      "jmp .LFUN_001de452_65\n\t"
      ".LFUN_001de452_67:\n\t"
      "testb $0x40, %%bl\n\t"
      "movl -0x4(%%eax), %%eax\n\t"
      "jne .LFUN_001de452_65\n\t"
      "xorl %%edx, %%edx\n\t"
      ".LFUN_001de452_68:\n\t"
      "testb $0x40, %%bl\n\t"
      "je .LFUN_001de452_70\n\t"
      "testl %%edx, %%edx\n\t"
      "jg .LFUN_001de452_70\n\t"
      "jl .LFUN_001de452_69\n\t"
      "testl %%eax, %%eax\n\t"
      "jae .LFUN_001de452_70\n\t"
      ".LFUN_001de452_69:\n\t"
      "negl %%eax\n\t"
      "adcl $0, %%edx\n\t"
      "negl %%edx\n\t"
      "orb $1, -0x3(%%ebp)\n\t"
      ".LFUN_001de452_70:\n\t"
      "testl %%esi, -0x4(%%ebp)\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl %%edx, %%edi\n\t"
      "jne .LFUN_001de452_71\n\t"
      "xorl %%edi, %%edi\n\t"
      ".LFUN_001de452_71:\n\t"
      "cmpl $0, -0x10(%%ebp)\n\t"
      "jge .LFUN_001de452_72\n\t"
      "movl $1, -0x10(%%ebp)\n\t"
      "jmp .LFUN_001de452_73\n\t"
      ".LFUN_001de452_72:\n\t"
      "andl $0xfffffff7, -0x4(%%ebp)\n\t"
      ".LFUN_001de452_73:\n\t"
      "movl %%ebx, %%eax\n\t"
      "orl %%edi, %%eax\n\t"
      "jne .LFUN_001de452_74\n\t"
      "andl $0, -0x1c(%%ebp)\n\t"
      ".LFUN_001de452_74:\n\t"
      "leal -0x4d(%%ebp), %%esi\n\t"
      ".LFUN_001de452_75:\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "decl -0x10(%%ebp)\n\t"
      "testl %%eax, %%eax\n\t"
      "jg .LFUN_001de452_76\n\t"
      "movl %%ebx, %%eax\n\t"
      "orl %%edi, %%eax\n\t"
      "je .LFUN_001de452_78\n\t"
      ".LFUN_001de452_76:\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "cdq\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "call *%[c1e42b0]\n\t"
      "addl $0x30, %%ecx\n\t"
      "cmpl $0x39, %%ecx\n\t"
      "movl %%ebx, -0x38(%%ebp)\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl %%edx, %%edi\n\t"
      "jle .LFUN_001de452_77\n\t"
      "addl -0x28(%%ebp), %%ecx\n\t"
      ".LFUN_001de452_77:\n\t"
      "movb %%cl, (%%esi)\n\t"
      "decl %%esi\n\t"
      "jmp .LFUN_001de452_75\n\t"
      ".LFUN_001de452_78:\n\t"
      "leal -0x4d(%%ebp), %%eax\n\t"
      "subl %%esi, %%eax\n\t"
      "incl %%esi\n\t"
      "testb $2, -0x3(%%ebp)\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "movl %%esi, -0x8(%%ebp)\n\t"
      "je .LFUN_001de452_81\n\t"
      "movl %%esi, %%ecx\n\t"
      "cmpb $0x30, (%%ecx)\n\t"
      "jne .LFUN_001de452_79\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_001de452_81\n\t"
      ".LFUN_001de452_79:\n\t"
      "decl -0x8(%%ebp)\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movb $0x30, (%%ecx)\n\t"
      "incl %%eax\n\t"
      ".LFUN_001de452_80:\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      ".LFUN_001de452_81:\n\t"
      "cmpl $0, -0x2c(%%ebp)\n\t"
      "jne .LFUN_001de452_91\n\t"
      "movl -0x4(%%ebp), %%ebx\n\t"
      "testb $0x40, %%bl\n\t"
      "je .LFUN_001de452_85\n\t"
      "testb $1, %%bh\n\t"
      "je .LFUN_001de452_82\n\t"
      "movb $0x2d, -0x18(%%ebp)\n\t"
      "jmp .LFUN_001de452_84\n\t"
      ".LFUN_001de452_82:\n\t"
      "xorl %%eax, %%eax\n\t"
      "incl %%eax\n\t"
      "testb %%bl, %%al\n\t"
      "je .LFUN_001de452_83\n\t"
      "movb $0x2b, -0x18(%%ebp)\n\t"
      "movl %%eax, -0x1c(%%ebp)\n\t"
      "jmp .LFUN_001de452_85\n\t"
      ".LFUN_001de452_83:\n\t"
      "testb $2, %%bl\n\t"
      "je .LFUN_001de452_85\n\t"
      "movb $0x20, -0x18(%%ebp)\n\t"
      ".LFUN_001de452_84:\n\t"
      "movl $1, -0x1c(%%ebp)\n\t"
      ".LFUN_001de452_85:\n\t"
      "movl -0x20(%%ebp), %%esi\n\t"
      "subl -0x1c(%%ebp), %%esi\n\t"
      "subl -0xc(%%ebp), %%esi\n\t"
      "testb $0xc, %%bl\n\t"
      "jne .LFUN_001de452_86\n\t"
      "pushl 0x8(%%ebp)\n\t"
      "leal -0x14(%%ebp), %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl $0x20\n\t"
      "call *%[c1de3d8]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_001de452_86:\n\t"
      "pushl -0x1c(%%ebp)\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "leal -0x14(%%ebp), %%eax\n\t"
      "leal -0x18(%%ebp), %%ecx\n\t"
      "call *%[c1de3fc]\n\t"
      "testb $8, %%bl\n\t"
      "popl %%ecx\n\t"
      "je .LFUN_001de452_87\n\t"
      "testb $4, %%bl\n\t"
      "jne .LFUN_001de452_87\n\t"
      "pushl %%edi\n\t"
      "pushl %%esi\n\t"
      "pushl $0x30\n\t"
      "leal -0x14(%%ebp), %%eax\n\t"
      "call *%[c1de3d8]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_001de452_87:\n\t"
      "cmpl $0, -0x24(%%ebp)\n\t"
      "je .LFUN_001de452_89\n\t"
      "cmpl $0, -0xc(%%ebp)\n\t"
      "jle .LFUN_001de452_89\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "movl -0x8(%%ebp), %%ebx\n\t"
      "movl %%eax, -0x38(%%ebp)\n\t"
      ".LFUN_001de452_88:\n\t"
      "decl -0x38(%%ebp)\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw (%%ebx), %%ax\n\t"
      "pushl %%eax\n\t"
      "leal -0x4c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1e2879]\n\t"
      "incl %%ebx\n\t"
      "popl %%ecx\n\t"
      "incl %%ebx\n\t"
      "testl %%eax, %%eax\n\t"
      "popl %%ecx\n\t"
      "jle .LFUN_001de452_90\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "pushl %%eax\n\t"
      "leal -0x14(%%ebp), %%eax\n\t"
      "leal -0x4c(%%ebp), %%ecx\n\t"
      "call *%[c1de3fc]\n\t"
      "cmpl $0, -0x38(%%ebp)\n\t"
      "popl %%ecx\n\t"
      "jne .LFUN_001de452_88\n\t"
      "jmp .LFUN_001de452_90\n\t"
      ".LFUN_001de452_89:\n\t"
      "pushl -0xc(%%ebp)\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "leal -0x14(%%ebp), %%eax\n\t"
      "call *%[c1de3fc]\n\t"
      "popl %%ecx\n\t"
      ".LFUN_001de452_90:\n\t"
      "testb $4, -0x4(%%ebp)\n\t"
      "je .LFUN_001de452_91\n\t"
      "pushl 0x8(%%ebp)\n\t"
      "leal -0x14(%%ebp), %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl $0x20\n\t"
      "call *%[c1de3d8]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_001de452_91:\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "movb (%%eax), %%bl\n\t"
      "testb %%bl, %%bl\n\t"
      "jne .LFUN_001de452_1\n\t"
      ".LFUN_001de452_92:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      ".LFUN_001de452_93:\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "popl %%ebx\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_001de452_jt:\n\t"
      ".long .LFUN_001de452_21\n\t"
      ".long .LFUN_001de452_4\n\t"
      ".long .LFUN_001de452_5\n\t"
      ".long .LFUN_001de452_10\n\t"
      ".long .LFUN_001de452_12\n\t"
      ".long .LFUN_001de452_13\n\t"
      ".long .LFUN_001de452_15\n\t"
      ".long .LFUN_001de452_23\n\t"
      ".text\n\t"
      :
      : [c1de3a5] "m"(b1de452_c1de3a5), [c1e2879] "m"(b1de452_c1e2879), [c1e42b0] "m"(b1de452_c1e42b0), [c1de3d8] "m"(b1de452_c1de3d8), [c1de3fc] "m"(b1de452_c1de3fc)
      : "memory");
}
#else
#error "FUN_001de452: clang naked draft required"
#endif

