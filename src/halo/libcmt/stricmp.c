/* kb object stubs -> libcmt/stricmp.c */

/* --- LIBCMT:stricmp.obj batch drafts (2026-07-26) --- */

/* FUN_001dd1d1 (0x1dd1d1) — readable C lift: wcstol wrapper (signed). */
long FUN_001dd1d1(const wchar_t *s, wchar_t **endptr, int base)
{
  return ((long (*)(const wchar_t *, wchar_t **, int, int))FUN_001dd00c)(s, endptr, base, 0);
}

/* FUN_001dd1e8 (0x1dd1e8) — readable C lift: wcstoul wrapper (unsigned). */
unsigned long FUN_001dd1e8(const wchar_t *s, wchar_t **endptr, int base)
{
  return ((unsigned long (*)(const wchar_t *, wchar_t **, int, int))FUN_001dd00c)(
      s, endptr, base, 1);
}

/* FUN_001dd1ff (0x1dd1ff) — XBE naked draft (batch 326). */
#if defined(__clang__)
static void (*const b1dd1ff_c1dd5c8)(void) = FUN_001dd5c8;
static int (*const b1dd1ff_c1dc3e9)(int c, int mask) = FUN_001dc3e9;
static size_t (*const b1dd1ff_c1db11e)(const wchar_t *str) = (void *)_wcslen;
static void (*const b1dd1ff_chkstk)(void) = FUN_001d90e0;
static void (*const b1dd1ff_c1dde12)(void) = (void *)_malloc;
static int * (*const b1dd1ff_c1db777)(void) = FUN_001db777;
static void (*const b1dd1ff_c1e2879)(void) = FUN_001e2879;
static void (*const b1dd1ff_c1e1e20)(void) = FUN_001e1e20;
static void (*const b1dd1ff_c1dde24)(void) = FUN_001dde24;
static void (*const b1dd1ff_c1dd601)(void) = __SEH_epilog;

__attribute__((naked, noinline))
double FUN_001dd1ff(const wchar_t *s __attribute__((unused)), wchar_t **endptr __attribute__((unused)))
{
  __asm__ volatile(
      "pushl $0x3c\n\t"
      "pushl $0x2c7650\n\t"
      "call *%[c1dd5c8]\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "movl %%ebx, -0x1c(%%ebp)\n\t"
      "xorl %%edi, %%edi\n\t"
      "movl %%edi, -0x20(%%ebp)\n\t"
      "movl %%edi, -0x24(%%ebp)\n\t"
      "pushl $8\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw (%%ebx), %%ax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1dc3e9]\n\t"
      "popl %%ecx\n\t"
      "popl %%ecx\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_001dd1ff_2\n\t"
      ".LFUN_001dd1ff_1:\n\t"
      "incl %%ebx\n\t"
      "incl %%ebx\n\t"
      "pushl $8\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw (%%ebx), %%ax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1dc3e9]\n\t"
      "popl %%ecx\n\t"
      "popl %%ecx\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_001dd1ff_1\n\t"
      "movl %%ebx, -0x1c(%%ebp)\n\t"
      ".LFUN_001dd1ff_2:\n\t"
      "wait\n\t"
      "movl %%edi, -0x4(%%ebp)\n\t"
      "pushl %%ebx\n\t"
      "call *%[c1db11e]\n\t"
      "popl %%ecx\n\t"
      "leal 0x2(%%eax,%%eax,1), %%eax\n\t"
      "addl $3, %%eax\n\t"
      "andl $0xfffffffc, %%eax\n\t"
      "call *%[chkstk]\n\t"
      "movl %%esp, -0x18(%%ebp)\n\t"
      "movl %%esp, %%eax\n\t"
      "movl %%eax, -0x28(%%ebp)\n\t"
      "wait\n\t"
      "orl $0xffffffff, -0x4(%%ebp)\n\t"
      "jmp .LFUN_001dd1ff_4\n\t"
      "xorl %%eax, %%eax\n\t"
      "incl %%eax\n\t"
      "ret\n\t"
      "movl -0x18(%%ebp), %%esp\n\t"
      "movl -0x1c(%%ebp), %%ebx\n\t"
      "pushl %%ebx\n\t"
      "call *%[c1db11e]\n\t"
      "leal 0x2(%%eax,%%eax,1), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1dde12]\n\t"
      "popl %%ecx\n\t"
      "popl %%ecx\n\t"
      "movl %%eax, -0x28(%%ebp)\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_001dd1ff_3\n\t"
      "call *%[c1db777]\n\t"
      "movl $0xc, (%%eax)\n\t"
      "wait\n\t"
      "orl $0xffffffff, -0x4(%%ebp)\n\t"
      "fldl 0x2602c0\n\t"
      "jmp .LFUN_001dd1ff_13\n\t"
      ".LFUN_001dd1ff_3:\n\t"
      "movl $1, -0x20(%%ebp)\n\t"
      "orl $0xffffffff, -0x4(%%ebp)\n\t"
      "movl -0x24(%%ebp), %%edi\n\t"
      ".LFUN_001dd1ff_4:\n\t"
      "cmpw $0, (%%ebx)\n\t"
      "je .LFUN_001dd1ff_6\n\t"
      "movl %%ebx, %%eax\n\t"
      "movl -0x28(%%ebp), %%ecx\n\t"
      "movl %%ecx, -0x2c(%%ebp)\n\t"
      "movl %%ebx, %%esi\n\t"
      ".LFUN_001dd1ff_5:\n\t"
      "movzwl (%%eax), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl -0x2c(%%ebp)\n\t"
      "call *%[c1e2879]\n\t"
      "popl %%ecx\n\t"
      "popl %%ecx\n\t"
      "testl %%eax, %%eax\n\t"
      "jle .LFUN_001dd1ff_6\n\t"
      "addl %%eax, %%edi\n\t"
      "incl -0x2c(%%ebp)\n\t"
      "incl %%esi\n\t"
      "incl %%esi\n\t"
      "movl %%esi, %%eax\n\t"
      "cmpw $0, (%%esi)\n\t"
      "jne .LFUN_001dd1ff_5\n\t"
      ".LFUN_001dd1ff_6:\n\t"
      "movl -0x28(%%ebp), %%eax\n\t"
      "andb $0, (%%eax,%%edi,1)\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "incl %%edi\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "leal -0x44(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1e1e20]\n\t"
      "addl $0x14, %%esp\n\t"
      "movl %%eax, %%esi\n\t"
      "cmpl $0, -0x20(%%ebp)\n\t"
      "je .LFUN_001dd1ff_7\n\t"
      "pushl -0x28(%%ebp)\n\t"
      "call *%[c1dde24]\n\t"
      "popl %%ecx\n\t"
      ".LFUN_001dd1ff_7:\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_001dd1ff_8\n\t"
      "movl 0x4(%%esi), %%ecx\n\t"
      "leal (%%ebx,%%ecx,2), %%ecx\n\t"
      "movl %%ecx, (%%eax)\n\t"
      ".LFUN_001dd1ff_8:\n\t"
      "movl (%%esi), %%ecx\n\t"
      "testw $0x240, %%cx\n\t"
      "je .LFUN_001dd1ff_9\n\t"
      "fldz\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_001dd1ff_13\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "movl %%ecx, (%%eax)\n\t"
      "jmp .LFUN_001dd1ff_13\n\t"
      ".LFUN_001dd1ff_9:\n\t"
      "testb $0x81, %%cl\n\t"
      "je .LFUN_001dd1ff_10\n\t"
      "fldl 0x331934\n\t"
      "cmpw $0x2d, (%%ebx)\n\t"
      "jne .LFUN_001dd1ff_11\n\t"
      "fchs\n\t"
      "jmp .LFUN_001dd1ff_11\n\t"
      ".LFUN_001dd1ff_10:\n\t"
      "testb $1, %%ch\n\t"
      "je .LFUN_001dd1ff_12\n\t"
      "fldz\n\t"
      ".LFUN_001dd1ff_11:\n\t"
      "fstpl -0x4c(%%ebp)\n\t"
      "call *%[c1db777]\n\t"
      "movl $0x22, (%%eax)\n\t"
      "fldl -0x4c(%%ebp)\n\t"
      "jmp .LFUN_001dd1ff_13\n\t"
      ".LFUN_001dd1ff_12:\n\t"
      "fldl 0x10(%%esi)\n\t"
      ".LFUN_001dd1ff_13:\n\t"
      "leal -0x58(%%ebp), %%esp\n\t"
      "call *%[c1dd601]\n\t"
      "ret\n\t"
      :
      : [c1dd5c8] "m"(b1dd1ff_c1dd5c8), [c1dc3e9] "m"(b1dd1ff_c1dc3e9), [c1db11e] "m"(b1dd1ff_c1db11e), [chkstk] "m"(b1dd1ff_chkstk), [c1dde12] "m"(b1dd1ff_c1dde12), [c1db777] "m"(b1dd1ff_c1db777), [c1e2879] "m"(b1dd1ff_c1e2879), [c1e1e20] "m"(b1dd1ff_c1e1e20), [c1dde24] "m"(b1dd1ff_c1dde24), [c1dd601] "m"(b1dd1ff_c1dd601)
      : "memory");
}
#else
#error "FUN_001dd1ff: clang naked draft required"
#endif


/* __wtol (0x1dd375) — XBE naked draft (batch 338). */
#if defined(__clang__)
static int (*const b1dd375_c1dc3e9)(int c, int mask) = FUN_001dc3e9;
static void (*const b1dd375_c1e38d1)(void) = __wchartodigit;

__attribute__((naked, noinline))
void __wtol(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "pushl %%edi\n\t"
      "jmp .L__wtol_2\n\t"
      ".L__wtol_1:\n\t"
      "incl %%esi\n\t"
      "incl %%esi\n\t"
      ".L__wtol_2:\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw (%%esi), %%ax\n\t"
      "pushl $8\n\t"
      "pushl %%eax\n\t"
      "call *%[c1dc3e9]\n\t"
      "testl %%eax, %%eax\n\t"
      "popl %%ecx\n\t"
      "popl %%ecx\n\t"
      "jne .L__wtol_1\n\t"
      "movzwl (%%esi), %%eax\n\t"
      "incl %%esi\n\t"
      "incl %%esi\n\t"
      "cmpl $0x2d, %%eax\n\t"
      "movl %%eax, 0x8(%%ebp)\n\t"
      "je .L__wtol_3\n\t"
      "cmpl $0x2b, %%eax\n\t"
      "jne .L__wtol_4\n\t"
      ".L__wtol_3:\n\t"
      "movzwl (%%esi), %%eax\n\t"
      "incl %%esi\n\t"
      "incl %%esi\n\t"
      ".L__wtol_4:\n\t"
      "xorl %%edi, %%edi\n\t"
      "jmp .L__wtol_6\n\t"
      ".L__wtol_5:\n\t"
      "leal (%%edi,%%edi,4), %%ecx\n\t"
      "leal (%%eax,%%ecx,2), %%edi\n\t"
      "movzwl (%%esi), %%eax\n\t"
      "incl %%esi\n\t"
      "incl %%esi\n\t"
      ".L__wtol_6:\n\t"
      "pushl %%eax\n\t"
      "call *%[c1e38d1]\n\t"
      "cmpl $-1, %%eax\n\t"
      "popl %%ecx\n\t"
      "jne .L__wtol_5\n\t"
      "cmpl $0x2d, 0x8(%%ebp)\n\t"
      "movl %%edi, %%eax\n\t"
      "jne .L__wtol_7\n\t"
      "negl %%eax\n\t"
      ".L__wtol_7:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c1dc3e9] "m"(b1dd375_c1dc3e9), [c1e38d1] "m"(b1dd375_c1e38d1)
      : "memory");
}
#else
#error "__wtol: clang naked draft required"
#endif


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

/* __wtoi64 (0x1dd3d9) — XBE naked draft (batch 326). */
#if defined(__clang__)
static int (*const b1dd3d9_c1dc3e9)(int c, int mask) = FUN_001dc3e9;
static void (*const b1dd3d9_c1dd620)(void) = __allmul;
static void (*const b1dd3d9_c1e38d1)(void) = __wchartodigit;

__attribute__((naked, noinline))
void __wtoi64(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xc, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "pushl %%edi\n\t"
      "jmp .L__wtoi64_2\n\t"
      ".L__wtoi64_1:\n\t"
      "incl %%esi\n\t"
      "incl %%esi\n\t"
      ".L__wtoi64_2:\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw (%%esi), %%ax\n\t"
      "pushl $8\n\t"
      "pushl %%eax\n\t"
      "call *%[c1dc3e9]\n\t"
      "testl %%eax, %%eax\n\t"
      "popl %%ecx\n\t"
      "popl %%ecx\n\t"
      "jne .L__wtoi64_1\n\t"
      "movzwl (%%esi), %%eax\n\t"
      "incl %%esi\n\t"
      "incl %%esi\n\t"
      "cmpl $0x2d, %%eax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "je .L__wtoi64_3\n\t"
      "cmpl $0x2b, %%eax\n\t"
      "jne .L__wtoi64_4\n\t"
      ".L__wtoi64_3:\n\t"
      "movzwl (%%esi), %%eax\n\t"
      "incl %%esi\n\t"
      "incl %%esi\n\t"
      ".L__wtoi64_4:\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "movl %%ebx, -0x8(%%ebp)\n\t"
      "jmp .L__wtoi64_6\n\t"
      ".L__wtoi64_5:\n\t"
      "pushl $0\n\t"
      "pushl $0xa\n\t"
      "pushl -0x8(%%ebp)\n\t"
      "pushl %%ebx\n\t"
      "call *%[c1dd620]\n\t"
      "movl %%eax, %%ecx\n\t"
      "movl %%edx, %%eax\n\t"
      "movl %%eax, 0x8(%%ebp)\n\t"
      "movl %%edi, %%eax\n\t"
      "cdq\n\t"
      "addl %%eax, %%ecx\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "adcl %%edx, %%eax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "movzwl (%%esi), %%eax\n\t"
      "incl %%esi\n\t"
      "movl %%ecx, %%ebx\n\t"
      "incl %%esi\n\t"
      ".L__wtoi64_6:\n\t"
      "pushl %%eax\n\t"
      "call *%[c1e38d1]\n\t"
      "movl %%eax, %%edi\n\t"
      "cmpl $-1, %%edi\n\t"
      "popl %%ecx\n\t"
      "jne .L__wtoi64_5\n\t"
      "cmpl $0x2d, -0x4(%%ebp)\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "movl %%ebx, %%eax\n\t"
      "jne .L__wtoi64_7\n\t"
      "negl %%eax\n\t"
      "adcl $0, %%edx\n\t"
      "negl %%edx\n\t"
      ".L__wtoi64_7:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      :
      : [c1dc3e9] "m"(b1dd3d9_c1dc3e9), [c1dd620] "m"(b1dd3d9_c1dd620), [c1e38d1] "m"(b1dd3d9_c1e38d1)
      : "memory");
}
#else
#error "__wtoi64: clang naked draft required"
#endif


/* 0x1dd467 */
wchar_t *__wctime(const void *timeptr)
{
  int eax = 0;

  crt_localtime((void *)0);
  __wasctime((void *)(uintptr_t)eax);
  return NULL;

  (void)eax;
}

/* _store_dt (0x1dd480) — XBE naked draft (batch 355). */
#if defined(__clang__)


__attribute__((naked, noinline))
void _store_dt(void)
{
  __asm__ volatile(
      "pushl %%esi\n\t"
      "cdq\n\t"
      "pushl $0xa\n\t"
      "popl %%esi\n\t"
      "idivl %%esi\n\t"
      "popl %%esi\n\t"
      "addl $0x30, %%eax\n\t"
      "movw %%ax, (%%ecx)\n\t"
      "incl %%ecx\n\t"
      "incl %%ecx\n\t"
      "addl $0x30, %%edx\n\t"
      "movw %%dx, (%%ecx)\n\t"
      "leal 0x2(%%ecx), %%eax\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "_store_dt: clang naked draft required"
#endif


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

/* FUN_001dd576 (0x1dd576) — XBE naked draft (batch 340). */
#if defined(__clang__)
static void (*const b1dd576_c1dff91)(void) = FUN_001dff91;
static void (*const b1dd576_c1dde12)(void) = (void *)_malloc;

__attribute__((naked, noinline))
int FUN_001dd576(int param __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%esi\n\t"
      "call *%[c1dff91]\n\t"
      "movl %%eax, %%esi\n\t"
      "cmpl $0, 0x24(%%esi)\n\t"
      "jne .LFUN_001dd576_1\n\t"
      "pushl $0x86\n\t"
      "call *%[c1dde12]\n\t"
      "movl %%eax, 0x24(%%esi)\n\t"
      "testl %%eax, %%eax\n\t"
      "popl %%ecx\n\t"
      "movl $0x4fc090, %%eax\n\t"
      "je .LFUN_001dd576_2\n\t"
      ".LFUN_001dd576_1:\n\t"
      "movl 0x24(%%esi), %%eax\n\t"
      ".LFUN_001dd576_2:\n\t"
      "movl 0x8(%%esp), %%edx\n\t"
      "testl %%edx, %%edx\n\t"
      "movl 0x331930, %%ecx\n\t"
      "jl .LFUN_001dd576_3\n\t"
      "cmpl %%ecx, %%edx\n\t"
      "jge .LFUN_001dd576_3\n\t"
      "movl %%edx, %%ecx\n\t"
      ".LFUN_001dd576_3:\n\t"
      "movl 0x331880(,%%ecx,4), %%edx\n\t"
      "movl %%eax, %%esi\n\t"
      ".LFUN_001dd576_4:\n\t"
      "movb (%%edx), %%cl\n\t"
      "incl %%edx\n\t"
      "movb %%cl, (%%esi)\n\t"
      "incl %%esi\n\t"
      "testb %%cl, %%cl\n\t"
      "jne .LFUN_001dd576_4\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      :
      : [c1dff91] "m"(b1dd576_c1dff91), [c1dde12] "m"(b1dd576_c1dde12)
      : "memory");
}
#else
#error "FUN_001dd576: clang naked draft required"
#endif


/* FUN_001dd5c8 (0x1dd5c8) — XBE naked draft (batch 343). */
#if defined(__clang__)


__attribute__((naked, noinline))
void FUN_001dd5c8(void)
{
  __asm__ volatile(
      "pushl $0x1dbdec\n\t"
      "movl 0, %%eax\n\t"
      "pushl %%eax\n\t"
      "movl %%esp, 0\n\t"
      "movl 0x10(%%esp), %%eax\n\t"
      "movl %%ebp, 0x10(%%esp)\n\t"
      "leal 0x10(%%esp), %%ebp\n\t"
      "subl %%eax, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movl %%esp, -0x18(%%ebp)\n\t"
      "pushl %%eax\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movl $0xffffffff, -0x4(%%ebp)\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "FUN_001dd5c8: clang naked draft required"
#endif


/* __SEH_epilog (0x1dd601) — XBE naked draft (batch 374). */
#if defined(__clang__)


__attribute__((naked, noinline))
void __SEH_epilog(void)
{
  __asm__ volatile(
      "movl -0x10(%%ebp), %%ecx\n\t"
      "movl %%ecx, 0\n\t"
      "popl %%ecx\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      ".byte 0xc9\n\t"
      "pushl %%ecx\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "__SEH_epilog: clang naked draft required"
#endif


/* __allmul (0x1dd620) — XBE naked draft (batch 340). */
#if defined(__clang__)


__attribute__((naked, noinline))
void __allmul(void)
{
  __asm__ volatile(
      "movl 0x8(%%esp), %%eax\n\t"
      "movl 0x10(%%esp), %%ecx\n\t"
      "orl %%eax, %%ecx\n\t"
      "movl 0xc(%%esp), %%ecx\n\t"
      "jne .L__allmul_1\n\t"
      "movl 0x4(%%esp), %%eax\n\t"
      "mull %%ecx\n\t"
      "ret\n\t"
      ".L__allmul_1:\n\t"
      "pushl %%ebx\n\t"
      "mull %%ecx\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl 0x8(%%esp), %%eax\n\t"
      "mull 0x14(%%esp)\n\t"
      "addl %%eax, %%ebx\n\t"
      "movl 0x8(%%esp), %%eax\n\t"
      "mull %%ecx\n\t"
      "addl %%ebx, %%edx\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "__allmul: clang naked draft required"
#endif


/* __aullshr (0x1dd660) — XBE naked draft (batch 312). */
#if defined(__clang__)


__attribute__((naked, noinline))
void __aullshr(void)
{
  __asm__ volatile(
      "cmpb $0x40, %%cl\n\t"
      "jae .L__aullshr_2\n\t"
      "cmpb $0x20, %%cl\n\t"
      "jae .L__aullshr_1\n\t"
      ".byte 0x0f, 0xad, 0xd0\n\t"
      "shrl %%cl, %%edx\n\t"
      "ret\n\t"
      ".L__aullshr_1:\n\t"
      "movl %%edx, %%eax\n\t"
      "xorl %%edx, %%edx\n\t"
      "andb $0x1f, %%cl\n\t"
      "shrl %%cl, %%eax\n\t"
      "ret\n\t"
      ".L__aullshr_2:\n\t"
      "xorl %%eax, %%eax\n\t"
      "xorl %%edx, %%edx\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "__aullshr: clang naked draft required"
#endif


/* __aullrem (0x1dd680) — XBE naked draft (batch 324). */
#if defined(__clang__)


__attribute__((naked, noinline))
void __aullrem(void)
{
  __asm__ volatile(
      "pushl %%ebx\n\t"
      "movl 0x14(%%esp), %%eax\n\t"
      "orl %%eax, %%eax\n\t"
      "jne .L__aullrem_1\n\t"
      "movl 0x10(%%esp), %%ecx\n\t"
      "movl 0xc(%%esp), %%eax\n\t"
      "xorl %%edx, %%edx\n\t"
      "divl %%ecx\n\t"
      "movl 0x8(%%esp), %%eax\n\t"
      "divl %%ecx\n\t"
      "movl %%edx, %%eax\n\t"
      "xorl %%edx, %%edx\n\t"
      "jmp .L__aullrem_5\n\t"
      ".L__aullrem_1:\n\t"
      "movl %%eax, %%ecx\n\t"
      "movl 0x10(%%esp), %%ebx\n\t"
      "movl 0xc(%%esp), %%edx\n\t"
      "movl 0x8(%%esp), %%eax\n\t"
      ".L__aullrem_2:\n\t"
      "shrl $1, %%ecx\n\t"
      ".byte 0xd1, 0xdb\n\t"
      "shrl $1, %%edx\n\t"
      ".byte 0xd1, 0xd8\n\t"
      "orl %%ecx, %%ecx\n\t"
      "jne .L__aullrem_2\n\t"
      "divl %%ebx\n\t"
      "movl %%eax, %%ecx\n\t"
      "mull 0x14(%%esp)\n\t"
      "xchgl %%eax, %%ecx\n\t"
      "mull 0x10(%%esp)\n\t"
      "addl %%ecx, %%edx\n\t"
      "jb .L__aullrem_3\n\t"
      "cmpl 0xc(%%esp), %%edx\n\t"
      "ja .L__aullrem_3\n\t"
      "jb .L__aullrem_4\n\t"
      "cmpl 0x8(%%esp), %%eax\n\t"
      "jbe .L__aullrem_4\n\t"
      ".L__aullrem_3:\n\t"
      "subl 0x10(%%esp), %%eax\n\t"
      "sbbl 0x14(%%esp), %%edx\n\t"
      ".L__aullrem_4:\n\t"
      "subl 0x8(%%esp), %%eax\n\t"
      "sbbl 0xc(%%esp), %%edx\n\t"
      "negl %%edx\n\t"
      "negl %%eax\n\t"
      "sbbl $0, %%edx\n\t"
      ".L__aullrem_5:\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "__aullrem: clang naked draft required"
#endif


/* FUN_001dd6f5 (0x1dd6f5) — XBE naked draft (batch 330). */
#if defined(__clang__)
static void (*const b1dd6f5_c1e2984)(void) = FUN_001e2984;
static void (*const b1dd6f5_c1de28c)(void) = __flsbuf;

__attribute__((naked, noinline))
void FUN_001dd6f5(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x20, %%esp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl %%eax, -0x18(%%ebp)\n\t"
      "movl %%eax, -0x20(%%ebp)\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "addl %%eax, %%eax\n\t"
      "movl %%eax, -0x1c(%%ebp)\n\t"
      "pushl %%esi\n\t"
      "leal 0x14(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl 0x10(%%ebp)\n\t"
      "leal -0x20(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl $0x42, -0x14(%%ebp)\n\t"
      "call *%[c1e2984]\n\t"
      "addl $0xc, %%esp\n\t"
      "decl -0x1c(%%ebp)\n\t"
      "movl %%eax, %%esi\n\t"
      "js .LFUN_001dd6f5_1\n\t"
      "movl -0x20(%%ebp), %%eax\n\t"
      "andb $0, (%%eax)\n\t"
      "incl -0x20(%%ebp)\n\t"
      "jmp .LFUN_001dd6f5_2\n\t"
      ".LFUN_001dd6f5_1:\n\t"
      "leal -0x20(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0\n\t"
      "call *%[c1de28c]\n\t"
      "popl %%ecx\n\t"
      "popl %%ecx\n\t"
      ".LFUN_001dd6f5_2:\n\t"
      "decl -0x1c(%%ebp)\n\t"
      "js .LFUN_001dd6f5_3\n\t"
      "movl -0x20(%%ebp), %%eax\n\t"
      "andb $0, (%%eax)\n\t"
      "jmp .LFUN_001dd6f5_4\n\t"
      ".LFUN_001dd6f5_3:\n\t"
      "leal -0x20(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0\n\t"
      "call *%[c1de28c]\n\t"
      "popl %%ecx\n\t"
      "popl %%ecx\n\t"
      ".LFUN_001dd6f5_4:\n\t"
      "movl %%esi, %%eax\n\t"
      "popl %%esi\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      :
      : [c1e2984] "m"(b1dd6f5_c1e2984), [c1de28c] "m"(b1dd6f5_c1de28c)
      : "memory");
}
#else
#error "FUN_001dd6f5: clang naked draft required"
#endif


/* __aulldiv (0x1dd770) — XBE naked draft (batch 324). */
#if defined(__clang__)


__attribute__((naked, noinline))
void __aulldiv(void)
{
  __asm__ volatile(
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x18(%%esp), %%eax\n\t"
      "orl %%eax, %%eax\n\t"
      "jne .L__aulldiv_1\n\t"
      "movl 0x14(%%esp), %%ecx\n\t"
      "movl 0x10(%%esp), %%eax\n\t"
      "xorl %%edx, %%edx\n\t"
      "divl %%ecx\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl 0xc(%%esp), %%eax\n\t"
      "divl %%ecx\n\t"
      "movl %%ebx, %%edx\n\t"
      "jmp .L__aulldiv_5\n\t"
      ".L__aulldiv_1:\n\t"
      "movl %%eax, %%ecx\n\t"
      "movl 0x14(%%esp), %%ebx\n\t"
      "movl 0x10(%%esp), %%edx\n\t"
      "movl 0xc(%%esp), %%eax\n\t"
      ".L__aulldiv_2:\n\t"
      "shrl $1, %%ecx\n\t"
      ".byte 0xd1, 0xdb\n\t"
      "shrl $1, %%edx\n\t"
      ".byte 0xd1, 0xd8\n\t"
      "orl %%ecx, %%ecx\n\t"
      "jne .L__aulldiv_2\n\t"
      "divl %%ebx\n\t"
      "movl %%eax, %%esi\n\t"
      "mull 0x18(%%esp)\n\t"
      "movl %%eax, %%ecx\n\t"
      "movl 0x14(%%esp), %%eax\n\t"
      "mull %%esi\n\t"
      "addl %%ecx, %%edx\n\t"
      "jb .L__aulldiv_3\n\t"
      "cmpl 0x10(%%esp), %%edx\n\t"
      "ja .L__aulldiv_3\n\t"
      "jb .L__aulldiv_4\n\t"
      "cmpl 0xc(%%esp), %%eax\n\t"
      "jbe .L__aulldiv_4\n\t"
      ".L__aulldiv_3:\n\t"
      "decl %%esi\n\t"
      ".L__aulldiv_4:\n\t"
      "xorl %%edx, %%edx\n\t"
      "movl %%esi, %%eax\n\t"
      ".L__aulldiv_5:\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "__aulldiv: clang naked draft required"
#endif


/* __allshr (0x1dd7e0) — XBE naked draft (batch 312). */
#if defined(__clang__)


__attribute__((naked, noinline))
void __allshr(void)
{
  __asm__ volatile(
      "cmpb $0x40, %%cl\n\t"
      "jae .L__allshr_2\n\t"
      "cmpb $0x20, %%cl\n\t"
      "jae .L__allshr_1\n\t"
      ".byte 0x0f, 0xad, 0xd0\n\t"
      "sarl %%cl, %%edx\n\t"
      "ret\n\t"
      ".L__allshr_1:\n\t"
      "movl %%edx, %%eax\n\t"
      "sarl $0x1f, %%edx\n\t"
      "andb $0x1f, %%cl\n\t"
      "sarl %%cl, %%eax\n\t"
      "ret\n\t"
      ".L__allshr_2:\n\t"
      "sarl $0x1f, %%edx\n\t"
      "movl %%edx, %%eax\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "__allshr: clang naked draft required"
#endif


/* crt_stricmp (0x1dd801) — XBE naked draft (batch 356). */
#if defined(__clang__)
static int (*const b1dd801_c1da1d8)(int c) = (void *)crt_tolower;

__attribute__((naked, noinline))
int crt_stricmp(const char *a __attribute__((unused)), const char *b __attribute__((unused)))
{
  __asm__ volatile(
      "cmpl $0, 0x4fc25c\n\t"
      "jne .Lcrt_stricmp_1\n\t"
      ".byte 0xe9, 0x41, 0x62, 0x00, 0x00\n\t"
      ".Lcrt_stricmp_1:\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0xc(%%esp), %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x14(%%esp), %%edi\n\t"
      ".Lcrt_stricmp_2:\n\t"
      "movzbl (%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1da1d8]\n\t"
      "movl %%eax, %%ebx\n\t"
      "movzbl (%%edi), %%eax\n\t"
      "pushl %%eax\n\t"
      "incl %%esi\n\t"
      "call *%[c1da1d8]\n\t"
      "popl %%ecx\n\t"
      "incl %%edi\n\t"
      "testl %%ebx, %%ebx\n\t"
      "popl %%ecx\n\t"
      "movl %%eax, %%ecx\n\t"
      "je .Lcrt_stricmp_3\n\t"
      "cmpl %%ecx, %%ebx\n\t"
      "je .Lcrt_stricmp_2\n\t"
      ".Lcrt_stricmp_3:\n\t"
      "popl %%edi\n\t"
      "movl %%ebx, %%eax\n\t"
      "popl %%esi\n\t"
      "subl %%ecx, %%eax\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      :
      : [c1da1d8] "m"(b1dd801_c1da1d8)
      : "memory");
}
#else
#error "crt_stricmp: clang naked draft required"
#endif


/* __alldiv (0x1dd850) — XBE naked draft (batch 313). */
#if defined(__clang__)


__attribute__((naked, noinline))
void __alldiv(void)
{
  __asm__ volatile(
      "pushl %%edi\n\t"
      "pushl %%esi\n\t"
      "pushl %%ebx\n\t"
      "xorl %%edi, %%edi\n\t"
      "movl 0x14(%%esp), %%eax\n\t"
      "orl %%eax, %%eax\n\t"
      "jge .L__alldiv_1\n\t"
      "incl %%edi\n\t"
      "movl 0x10(%%esp), %%edx\n\t"
      "negl %%eax\n\t"
      "negl %%edx\n\t"
      "sbbl $0, %%eax\n\t"
      "movl %%eax, 0x14(%%esp)\n\t"
      "movl %%edx, 0x10(%%esp)\n\t"
      ".L__alldiv_1:\n\t"
      "movl 0x1c(%%esp), %%eax\n\t"
      "orl %%eax, %%eax\n\t"
      "jge .L__alldiv_2\n\t"
      "incl %%edi\n\t"
      "movl 0x18(%%esp), %%edx\n\t"
      "negl %%eax\n\t"
      "negl %%edx\n\t"
      "sbbl $0, %%eax\n\t"
      "movl %%eax, 0x1c(%%esp)\n\t"
      "movl %%edx, 0x18(%%esp)\n\t"
      ".L__alldiv_2:\n\t"
      "orl %%eax, %%eax\n\t"
      "jne .L__alldiv_3\n\t"
      "movl 0x18(%%esp), %%ecx\n\t"
      "movl 0x14(%%esp), %%eax\n\t"
      "xorl %%edx, %%edx\n\t"
      "divl %%ecx\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl 0x10(%%esp), %%eax\n\t"
      "divl %%ecx\n\t"
      "movl %%ebx, %%edx\n\t"
      "jmp .L__alldiv_7\n\t"
      ".L__alldiv_3:\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl 0x18(%%esp), %%ecx\n\t"
      "movl 0x14(%%esp), %%edx\n\t"
      "movl 0x10(%%esp), %%eax\n\t"
      ".L__alldiv_4:\n\t"
      "shrl $1, %%ebx\n\t"
      ".byte 0xd1, 0xd9\n\t"
      "shrl $1, %%edx\n\t"
      ".byte 0xd1, 0xd8\n\t"
      "orl %%ebx, %%ebx\n\t"
      "jne .L__alldiv_4\n\t"
      "divl %%ecx\n\t"
      "movl %%eax, %%esi\n\t"
      "mull 0x1c(%%esp)\n\t"
      "movl %%eax, %%ecx\n\t"
      "movl 0x18(%%esp), %%eax\n\t"
      "mull %%esi\n\t"
      "addl %%ecx, %%edx\n\t"
      "jb .L__alldiv_5\n\t"
      "cmpl 0x14(%%esp), %%edx\n\t"
      "ja .L__alldiv_5\n\t"
      "jb .L__alldiv_6\n\t"
      "cmpl 0x10(%%esp), %%eax\n\t"
      "jbe .L__alldiv_6\n\t"
      ".L__alldiv_5:\n\t"
      "decl %%esi\n\t"
      ".L__alldiv_6:\n\t"
      "xorl %%edx, %%edx\n\t"
      "movl %%esi, %%eax\n\t"
      ".L__alldiv_7:\n\t"
      "decl %%edi\n\t"
      "jne .L__alldiv_8\n\t"
      "negl %%edx\n\t"
      "negl %%eax\n\t"
      "sbbl $0, %%edx\n\t"
      ".L__alldiv_8:\n\t"
      "popl %%ebx\n\t"
      "popl %%esi\n\t"
      "popl %%edi\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "__alldiv: clang naked draft required"
#endif


/* __copysign (0x1dd8fa) — XBE naked draft (batch 355). */
#if defined(__clang__)


__attribute__((naked, noinline))
void __copysign(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "xorl 0xc(%%ebp), %%eax\n\t"
      "andl $0x7fffffff, %%eax\n\t"
      "xorl 0x14(%%ebp), %%eax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "fldl -0x8(%%ebp)\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "__copysign: clang naked draft required"
#endif


/* __chgsign (0x1dd91b) — XBE naked draft (batch 328). */
#if defined(__clang__)


__attribute__((naked, noinline))
void __chgsign(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "movl %%eax, %%ecx\n\t"
      "notl %%ecx\n\t"
      "xorl %%eax, %%ecx\n\t"
      "andl $0x7fffffff, %%ecx\n\t"
      "notl %%eax\n\t"
      "xorl %%eax, %%ecx\n\t"
      "movl %%ecx, -0x4(%%ebp)\n\t"
      "fldl -0x8(%%ebp)\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "__chgsign: clang naked draft required"
#endif


/* FUN_001dd957 (0x1dd957) — XBE naked draft (batch 321). */
#if defined(__clang__)
static void (*const b1dd957_c1dfeec)(void) = __ctrlfp;
static void (*const b1dd957_c1dfdc4)(void) = __sptype;
static void (*const b1dd957_c1dfb20)(void) = __handle_qnan1;
static void (*const b1dd957_c1dfbd2)(void) = FUN_001dfbd2;
static void (*const b1dd957_c1dfe1f)(void) = FUN_001dfe1f;

__attribute__((naked, noinline))
void FUN_001dd957(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl $0xffff, %%esi\n\t"
      "pushl %%esi\n\t"
      "pushl $0x133f\n\t"
      "call *%[c1dfeec]\n\t"
      "fldl 0x8(%%ebp)\n\t"
      "movl %%eax, %%edi\n\t"
      "movl 0xe(%%ebp), %%eax\n\t"
      "andw $0x7ff0, %%ax\n\t"
      "cmpw $0x7ff0, %%ax\n\t"
      "popl %%ecx\n\t"
      "popl %%ecx\n\t"
      "jne .LFUN_001dd957_3\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ecx\n\t"
      "fstpl (%%esp)\n\t"
      "call *%[c1dfdc4]\n\t"
      "testl %%eax, %%eax\n\t"
      "popl %%ecx\n\t"
      "popl %%ecx\n\t"
      "jle .LFUN_001dd957_2\n\t"
      "cmpl $2, %%eax\n\t"
      "jle .LFUN_001dd957_1\n\t"
      "cmpl $3, %%eax\n\t"
      "jne .LFUN_001dd957_2\n\t"
      "fldl 0x8(%%ebp)\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ecx\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x25\n\t"
      "call *%[c1dfb20]\n\t"
      "addl $0x10, %%esp\n\t"
      "jmp .LFUN_001dd957_7\n\t"
      ".LFUN_001dd957_1:\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c1dfeec]\n\t"
      "popl %%ecx\n\t"
      "popl %%ecx\n\t"
      "jmp .LFUN_001dd957_6\n\t"
      ".LFUN_001dd957_2:\n\t"
      "fldl 0x8(%%ebp)\n\t"
      "pushl %%edi\n\t"
      "faddl 0x2573d8\n\t"
      "subl $0x10, %%esp\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "fldl 0x8(%%ebp)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x25\n\t"
      "pushl $8\n\t"
      "jmp .LFUN_001dd957_4\n\t"
      ".LFUN_001dd957_3:\n\t"
      "fcompl 0x2602c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .LFUN_001dd957_5\n\t"
      "fldl 0x331718\n\t"
      "pushl %%edi\n\t"
      "subl $0x10, %%esp\n\t"
      "fchs\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "fldl 0x8(%%ebp)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x25\n\t"
      "pushl $4\n\t"
      ".LFUN_001dd957_4:\n\t"
      "call *%[c1dfbd2]\n\t"
      "addl $0x1c, %%esp\n\t"
      "jmp .LFUN_001dd957_7\n\t"
      ".LFUN_001dd957_5:\n\t"
      "fldl 0x8(%%ebp)\n\t"
      "leal -0x4(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ecx\n\t"
      "fstpl (%%esp)\n\t"
      "call *%[c1dfe1f]\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "fstp %%st(0)\n\t"
      "decl %%eax\n\t"
      "movl %%eax, 0xc(%%ebp)\n\t"
      "fildl 0xc(%%ebp)\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "fstpl 0x8(%%ebp)\n\t"
      "call *%[c1dfeec]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001dd957_6:\n\t"
      "fldl 0x8(%%ebp)\n\t"
      ".LFUN_001dd957_7:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      :
      : [c1dfeec] "m"(b1dd957_c1dfeec), [c1dfdc4] "m"(b1dd957_c1dfdc4), [c1dfb20] "m"(b1dd957_c1dfb20), [c1dfbd2] "m"(b1dd957_c1dfbd2), [c1dfe1f] "m"(b1dd957_c1dfe1f)
      : "memory");
}
#else
#error "FUN_001dd957: clang naked draft required"
#endif


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


/* FUN_001ddcc6 (0x1ddcc6) — readable C lift: non-NaN/Inf double check. */
int FUN_001ddcc6(double x)
{
  unsigned short hi = *(unsigned short *)((char *)&x + 6);
  return (hi & 0x7ff0) != 0x7ff0;
}

/* FUN_001ddd09 (0x1ddd09) — XBE naked draft (batch 313). */
#if defined(__clang__)
static void (*const b1ddd09_c1dfdc4)(void) = __sptype;

__attribute__((naked, noinline))
void FUN_001ddd09(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl 0xe(%%ebp), %%eax\n\t"
      "movl $0x7ff0, %%ecx\n\t"
      "movl %%eax, %%edx\n\t"
      "andl %%ecx, %%edx\n\t"
      "cmpw %%cx, %%dx\n\t"
      "jne .LFUN_001ddd09_5\n\t"
      "fldl 0x8(%%ebp)\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ecx\n\t"
      "fstpl (%%esp)\n\t"
      "call *%[c1dfdc4]\n\t"
      "decl %%eax\n\t"
      "popl %%ecx\n\t"
      "popl %%ecx\n\t"
      "je .LFUN_001ddd09_4\n\t"
      "decl %%eax\n\t"
      "je .LFUN_001ddd09_3\n\t"
      "decl %%eax\n\t"
      "je .LFUN_001ddd09_1\n\t"
      "xorl %%eax, %%eax\n\t"
      "incl %%eax\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001ddd09_1:\n\t"
      "pushl $2\n\t"
      ".LFUN_001ddd09_2:\n\t"
      "popl %%eax\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001ddd09_3:\n\t"
      "pushl $4\n\t"
      "jmp .LFUN_001ddd09_2\n\t"
      ".LFUN_001ddd09_4:\n\t"
      "movl $0x200, %%eax\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001ddd09_5:\n\t"
      "andl $0x8000, %%eax\n\t"
      "testw %%dx, %%dx\n\t"
      "movl %%eax, %%ecx\n\t"
      "jne .LFUN_001ddd09_7\n\t"
      "testl $0xfffff, 0xc(%%ebp)\n\t"
      "jne .LFUN_001ddd09_6\n\t"
      "cmpl $0, 0x8(%%ebp)\n\t"
      "je .LFUN_001ddd09_7\n\t"
      ".LFUN_001ddd09_6:\n\t"
      "movl %%ecx, %%eax\n\t"
      "negl %%eax\n\t"
      "sbbl %%eax, %%eax\n\t"
      "andl $0xffffff90, %%eax\n\t"
      "addl $0x80, %%eax\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001ddd09_7:\n\t"
      "fldl 0x8(%%ebp)\n\t"
      "fcompl 0x2602c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "movl %%ecx, %%eax\n\t"
      "jp .LFUN_001ddd09_8\n\t"
      "negl %%eax\n\t"
      "sbbl %%eax, %%eax\n\t"
      "andl $0xffffffe0, %%eax\n\t"
      "addl $0x40, %%eax\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001ddd09_8:\n\t"
      "negl %%eax\n\t"
      "sbbl %%eax, %%eax\n\t"
      "andl $0xffffff08, %%eax\n\t"
      "addl $0x100, %%eax\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c1dfdc4] "m"(b1ddd09_c1dfdc4)
      : "memory");
}
#else
#error "FUN_001ddd09: clang naked draft required"
#endif


/* FUN_001ddda3 (0x1ddda3) — XBE naked draft (batch 305). */
#if defined(__clang__)
static void (*const b1ddda3_c1ddde6)(void) = __nh_malloc;
static void (*const b1ddda3_c1e3c37)(void) = FUN_001e3c37;
static void (*const b1ddda3_c1d0bb3)(void) = FUN_001d0bb3;
static void (*const b1ddda3_c1d5c66)(void) = FUN_001d5c66;
static void (*const b1ddda3_c1dddbf)(void) = FUN_001dddbf;
static void (*const b1ddda3_c1e3c81)(void) = __callnewh;
static void (*const b1ddda3_c1dd5c8)(void) = FUN_001dd5c8;
static void (*const b1ddda3_c1df055)(void) = FUN_001df055;
static void (*const b1ddda3_c1dde73)(void) = (void *)FUN_001dde73;
static void (*const b1ddda3_c1d0b9c)(void) = FUN_001d0b9c;
static void (*const b1ddda3_c1dd601)(void) = __SEH_epilog;

__attribute__((naked, noinline))
void FUN_001ddda3(void)
{
  __asm__ volatile(
      "jmp .LFUN_001ddda3_6\n\t"
      "pushl $1\n\t"
      "pushl 0x8(%%esp)\n\t"
      "call *%[c1ddde6]\n\t"
      "popl %%ecx\n\t"
      "popl %%ecx\n\t"
      "ret\n\t"
      "pushl $0x19\n\t"
      "call *%[c1e3c37]\n\t"
      "popl %%ecx\n\t"
      "ret\n\t"
      "movl 0x4(%%esp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_001ddda3_1\n\t"
      "incl %%eax\n\t"
      ".LFUN_001ddda3_1:\n\t"
      "cmpl $1, 0x632ca0\n\t"
      "je .LFUN_001ddda3_2\n\t"
      "addl $0xf, %%eax\n\t"
      "andl $0xfffffff0, %%eax\n\t"
      ".LFUN_001ddda3_2:\n\t"
      "pushl %%eax\n\t"
      "pushl $0\n\t"
      "call *%[c1d0bb3]\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d5c66]\n\t"
      "ret\n\t"
      "cmpl $-0x20, 0x4(%%esp)\n\t"
      "ja .LFUN_001ddda3_4\n\t"
      ".LFUN_001ddda3_3:\n\t"
      "pushl 0x4(%%esp)\n\t"
      "call *%[c1dddbf]\n\t"
      "testl %%eax, %%eax\n\t"
      "popl %%ecx\n\t"
      "jne .LFUN_001ddda3_5\n\t"
      "cmpl %%eax, 0x8(%%esp)\n\t"
      "je .LFUN_001ddda3_5\n\t"
      "pushl 0x4(%%esp)\n\t"
      "call *%[c1e3c81]\n\t"
      "testl %%eax, %%eax\n\t"
      "popl %%ecx\n\t"
      "jne .LFUN_001ddda3_3\n\t"
      ".LFUN_001ddda3_4:\n\t"
      "xorl %%eax, %%eax\n\t"
      ".LFUN_001ddda3_5:\n\t"
      "ret\n\t"
      "pushl 0x4fc36c\n\t"
      "pushl 0x8(%%esp)\n\t"
      "call *%[c1ddde6]\n\t"
      "popl %%ecx\n\t"
      "popl %%ecx\n\t"
      "ret\n\t"
      ".LFUN_001ddda3_6:\n\t"
      "pushl $0xc\n\t"
      "pushl $0x2c7660\n\t"
      "call *%[c1dd5c8]\n\t"
      "xorl %%esi, %%esi\n\t"
      "cmpl %%esi, 0x8(%%ebp)\n\t"
      "je .LFUN_001ddda3_8\n\t"
      "cmpl $3, 0x632ca0\n\t"
      "jne .LFUN_001ddda3_7\n\t"
      "pushl $4\n\t"
      "call *%[c1df055]\n\t"
      "popl %%ecx\n\t"
      "movl %%esi, -0x4(%%ebp)\n\t"
      "movl %%esi, -0x1c(%%ebp)\n\t"
      "orl $0xffffffff, -0x4(%%ebp)\n\t"
      "call *%[c1dde73]\n\t"
      "cmpl %%esi, -0x1c(%%ebp)\n\t"
      "jne .LFUN_001ddda3_8\n\t"
      ".LFUN_001ddda3_7:\n\t"
      "pushl 0x8(%%ebp)\n\t"
      "pushl %%esi\n\t"
      "call *%[c1d0bb3]\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d0b9c]\n\t"
      ".LFUN_001ddda3_8:\n\t"
      "call *%[c1dd601]\n\t"
      "ret\n\t"
      :
      : [c1ddde6] "m"(b1ddda3_c1ddde6), [c1e3c37] "m"(b1ddda3_c1e3c37), [c1d0bb3] "m"(b1ddda3_c1d0bb3), [c1d5c66] "m"(b1ddda3_c1d5c66), [c1dddbf] "m"(b1ddda3_c1dddbf), [c1e3c81] "m"(b1ddda3_c1e3c81), [c1dd5c8] "m"(b1ddda3_c1dd5c8), [c1df055] "m"(b1ddda3_c1df055), [c1dde73] "m"(b1ddda3_c1dde73), [c1d0b9c] "m"(b1ddda3_c1d0b9c), [c1dd601] "m"(b1ddda3_c1dd601)
      : "memory");
}
#else
#error "FUN_001ddda3: clang naked draft required"
#endif


/* 0x1ddda8 */
void FUN_001ddda8(void)
{
  __nh_malloc();
  FUN_001e3c37();
}

/* FUN_001dddbf (0x1dddbf) — XBE naked draft (batch 332). */
#if defined(__clang__)
static void (*const b1dddbf_c1d0bb3)(void) = FUN_001d0bb3;
static void (*const b1dddbf_c1d5c66)(void) = FUN_001d5c66;

__attribute__((naked, noinline))
void FUN_001dddbf(void)
{
  __asm__ volatile(
      "movl 0x4(%%esp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_001dddbf_1\n\t"
      "incl %%eax\n\t"
      ".LFUN_001dddbf_1:\n\t"
      "cmpl $1, 0x632ca0\n\t"
      "je .LFUN_001dddbf_2\n\t"
      "addl $0xf, %%eax\n\t"
      "andl $0xfffffff0, %%eax\n\t"
      ".LFUN_001dddbf_2:\n\t"
      "pushl %%eax\n\t"
      "pushl $0\n\t"
      "call *%[c1d0bb3]\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d5c66]\n\t"
      "ret\n\t"
      :
      : [c1d0bb3] "m"(b1dddbf_c1d0bb3), [c1d5c66] "m"(b1dddbf_c1d5c66)
      : "memory");
}
#else
#error "FUN_001dddbf: clang naked draft required"
#endif


/* __nh_malloc (0x1ddde6) — XBE naked draft (batch 343). */
#if defined(__clang__)
static void (*const b1ddde6_c1dddbf)(void) = FUN_001dddbf;
static void (*const b1ddde6_c1e3c81)(void) = __callnewh;

__attribute__((naked, noinline))
void __nh_malloc(void)
{
  __asm__ volatile(
      "cmpl $-0x20, 0x4(%%esp)\n\t"
      "ja .L__nh_malloc_2\n\t"
      ".L__nh_malloc_1:\n\t"
      "pushl 0x4(%%esp)\n\t"
      "call *%[c1dddbf]\n\t"
      "testl %%eax, %%eax\n\t"
      "popl %%ecx\n\t"
      "jne .L__nh_malloc_3\n\t"
      "cmpl %%eax, 0x8(%%esp)\n\t"
      "je .L__nh_malloc_3\n\t"
      "pushl 0x4(%%esp)\n\t"
      "call *%[c1e3c81]\n\t"
      "testl %%eax, %%eax\n\t"
      "popl %%ecx\n\t"
      "jne .L__nh_malloc_1\n\t"
      ".L__nh_malloc_2:\n\t"
      "xorl %%eax, %%eax\n\t"
      ".L__nh_malloc_3:\n\t"
      "ret\n\t"
      :
      : [c1dddbf] "m"(b1ddde6_c1dddbf), [c1e3c81] "m"(b1ddde6_c1e3c81)
      : "memory");
}
#else
#error "__nh_malloc: clang naked draft required"
#endif


/* _malloc (0x1dde12) — readable C lift: nh_malloc(size, heap_flag). */
void *_malloc(size_t size)
{
  return ((void *(*)(size_t, int))__nh_malloc)(size, *(int *)0x4fc36c);
}

/* FUN_001dde24 (0x1dde24) — XBE naked draft (batch 340). */
#if defined(__clang__)
static void (*const b1dde24_c1dd5c8)(void) = FUN_001dd5c8;
static void (*const b1dde24_c1df055)(void) = FUN_001df055;
static void (*const b1dde24_c1dde73)(void) = (void *)FUN_001dde73;
static void (*const b1dde24_c1d0bb3)(void) = FUN_001d0bb3;
static void (*const b1dde24_c1d0b9c)(void) = FUN_001d0b9c;
static void (*const b1dde24_c1dd601)(void) = __SEH_epilog;

__attribute__((naked, noinline))
void FUN_001dde24(void)
{
  __asm__ volatile(
      "pushl $0xc\n\t"
      "pushl $0x2c7660\n\t"
      "call *%[c1dd5c8]\n\t"
      "xorl %%esi, %%esi\n\t"
      "cmpl %%esi, 0x8(%%ebp)\n\t"
      "je .LFUN_001dde24_2\n\t"
      "cmpl $3, 0x632ca0\n\t"
      "jne .LFUN_001dde24_1\n\t"
      "pushl $4\n\t"
      "call *%[c1df055]\n\t"
      "popl %%ecx\n\t"
      "movl %%esi, -0x4(%%ebp)\n\t"
      "movl %%esi, -0x1c(%%ebp)\n\t"
      "orl $0xffffffff, -0x4(%%ebp)\n\t"
      "call *%[c1dde73]\n\t"
      "cmpl %%esi, -0x1c(%%ebp)\n\t"
      "jne .LFUN_001dde24_2\n\t"
      ".LFUN_001dde24_1:\n\t"
      "pushl 0x8(%%ebp)\n\t"
      "pushl %%esi\n\t"
      "call *%[c1d0bb3]\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d0b9c]\n\t"
      ".LFUN_001dde24_2:\n\t"
      "call *%[c1dd601]\n\t"
      "ret\n\t"
      :
      : [c1dd5c8] "m"(b1dde24_c1dd5c8), [c1df055] "m"(b1dde24_c1df055), [c1dde73] "m"(b1dde24_c1dde73), [c1d0bb3] "m"(b1dde24_c1d0bb3), [c1d0b9c] "m"(b1dde24_c1d0b9c), [c1dd601] "m"(b1dde24_c1dd601)
      : "memory");
}
#else
#error "FUN_001dde24: clang naked draft required"
#endif


/* FUN_001dde73 (0x1dde73) — readable C lift. */
void FUN_001dde73(void)
{
  ((void (*)(int))FUN_001defb3)(4);
}

/* __forcdecpt (0x1dde7c) — XBE naked draft (batch 345). */
#if defined(__clang__)
static int (*const b1dde7c_c1da1d8)(int c) = crt_tolower;
static void (*const b1dde7c_c1e153d)(void) = FUN_001e153d;

__attribute__((naked, noinline))
void __forcdecpt(void)
{
  __asm__ volatile(
      "pushl %%esi\n\t"
      "movl 0x8(%%esp), %%esi\n\t"
      "movsbl (%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1da1d8]\n\t"
      "cmpl $0x65, %%eax\n\t"
      "popl %%ecx\n\t"
      "je .L__forcdecpt_4\n\t"
      ".L__forcdecpt_1:\n\t"
      "incl %%esi\n\t"
      "cmpl $1, 0x3317bc\n\t"
      "movsbl (%%esi), %%eax\n\t"
      "jle .L__forcdecpt_2\n\t"
      "pushl $4\n\t"
      "pushl %%eax\n\t"
      "call *%[c1e153d]\n\t"
      "popl %%ecx\n\t"
      "popl %%ecx\n\t"
      "jmp .L__forcdecpt_3\n\t"
      ".L__forcdecpt_2:\n\t"
      "movl 0x3317b4, %%ecx\n\t"
      "movzbl (%%ecx,%%eax,2), %%eax\n\t"
      "andl $4, %%eax\n\t"
      ".L__forcdecpt_3:\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .L__forcdecpt_1\n\t"
      ".L__forcdecpt_4:\n\t"
      "movb (%%esi), %%al\n\t"
      "movb 0x3317c0, %%cl\n\t"
      "movb %%cl, (%%esi)\n\t"
      "incl %%esi\n\t"
      ".L__forcdecpt_5:\n\t"
      "movb (%%esi), %%cl\n\t"
      "movb %%al, (%%esi)\n\t"
      "movb %%cl, %%al\n\t"
      "movb (%%esi), %%cl\n\t"
      "incl %%esi\n\t"
      "testb %%cl, %%cl\n\t"
      "jne .L__forcdecpt_5\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      :
      : [c1da1d8] "m"(b1dde7c_c1da1d8), [c1e153d] "m"(b1dde7c_c1e153d)
      : "memory");
}
#else
#error "__forcdecpt: clang naked draft required"
#endif


/* __fassign (0x1ddf39) — XBE naked draft (batch 336). */
#if defined(__clang__)
static void (*const b1ddf39_c1e4048)(void) = FUN_001e4048;
static void (*const b1ddf39_c1e40a3)(void) = FUN_001e40a3;

__attribute__((naked, noinline))
void __fassign(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ecx\n\t"
      "cmpl $0, 0x8(%%ebp)\n\t"
      "pushl 0x10(%%ebp)\n\t"
      "je .L__fassign_1\n\t"
      "leal -0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1e4048]\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "popl %%ecx\n\t"
      "popl %%ecx\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movl %%ecx, (%%eax)\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movl %%ecx, 0x4(%%eax)\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      ".L__fassign_1:\n\t"
      "leal 0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1e40a3]\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "popl %%ecx\n\t"
      "popl %%ecx\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "movl %%ecx, (%%eax)\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      :
      : [c1e4048] "m"(b1ddf39_c1e4048), [c1e40a3] "m"(b1ddf39_c1e40a3)
      : "memory");
}
#else
#error "__fassign: clang naked draft required"
#endif


/* FUN_001ddf77 (0x1ddf77) — XBE naked draft (batch 380). */
#if defined(__clang__)
static void * (*const b1ddf77_c1da290)(void *dest, const void *src, size_t size) = (void *)memmove;

__attribute__((naked, noinline))
void FUN_001ddf77(void)
{
  __asm__ volatile(
      "testl %%esi, %%esi\n\t"
      "je .LFUN_001ddf77_2\n\t"
      "movl %%ecx, %%eax\n\t"
      "pushl %%edi\n\t"
      "leal 0x1(%%eax), %%edi\n\t"
      ".LFUN_001ddf77_1:\n\t"
      "movb (%%eax), %%dl\n\t"
      "incl %%eax\n\t"
      "testb %%dl, %%dl\n\t"
      "jne .LFUN_001ddf77_1\n\t"
      "subl %%edi, %%eax\n\t"
      "incl %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "addl %%esi, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1da290]\n\t"
      "addl $0xc, %%esp\n\t"
      "popl %%edi\n\t"
      ".LFUN_001ddf77_2:\n\t"
      "ret\n\t"
      :
      : [c1da290] "m"(b1ddf77_c1da290)
      : "memory");
}
#else
#error "FUN_001ddf77: clang naked draft required"
#endif


/* FUN_001ddf9a (0x1ddf9a) — XBE naked draft (batch 324). */
#if defined(__clang__)
static void (*const b1ddf9a_c1ddf77)(void) = FUN_001ddf77;

__attribute__((naked, noinline))
void FUN_001ddf9a(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "cmpb $0, 0x14(%%ebp)\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "je .LFUN_001ddf9a_1\n\t"
      "xorl %%eax, %%eax\n\t"
      "cmpl %%eax, 0xc(%%ebp)\n\t"
      "setg %%al\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "cmpl $0x2d, (%%ebx)\n\t"
      "sete %%cl\n\t"
      "movl %%eax, %%esi\n\t"
      "addl %%edi, %%ecx\n\t"
      "call *%[c1ddf77]\n\t"
      ".LFUN_001ddf9a_1:\n\t"
      "cmpl $0x2d, (%%ebx)\n\t"
      "movl %%edi, %%eax\n\t"
      "jne .LFUN_001ddf9a_2\n\t"
      "movb $0x2d, (%%edi)\n\t"
      "leal 0x1(%%edi), %%eax\n\t"
      ".LFUN_001ddf9a_2:\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "jle .LFUN_001ddf9a_3\n\t"
      "leal 0x1(%%eax), %%esi\n\t"
      "movb (%%esi), %%cl\n\t"
      "movb %%cl, (%%eax)\n\t"
      "movb 0x3317c0, %%cl\n\t"
      "movl %%esi, %%eax\n\t"
      "movb %%cl, (%%eax)\n\t"
      ".LFUN_001ddf9a_3:\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "cmpb %%cl, 0x14(%%ebp)\n\t"
      "movl $0x2c766c, %%esi\n\t"
      "sete %%cl\n\t"
      "addl %%eax, %%ecx\n\t"
      "addl %%edi, %%ecx\n\t"
      "cmpl $0, 0x10(%%ebp)\n\t"
      "movl %%ecx, %%edi\n\t"
      ".byte 0xa5\n\t"
      ".byte 0x66, 0xa5\n\t"
      "je .LFUN_001ddf9a_4\n\t"
      "movb $0x45, (%%ecx)\n\t"
      ".LFUN_001ddf9a_4:\n\t"
      "movl 0xc(%%ebx), %%eax\n\t"
      "incl %%ecx\n\t"
      "cmpb $0x30, (%%eax)\n\t"
      "je .LFUN_001ddf9a_8\n\t"
      "movl 0x4(%%ebx), %%eax\n\t"
      "decl %%eax\n\t"
      "jns .LFUN_001ddf9a_5\n\t"
      "negl %%eax\n\t"
      "movb $0x2d, (%%ecx)\n\t"
      ".LFUN_001ddf9a_5:\n\t"
      "incl %%ecx\n\t"
      "cmpl $0x64, %%eax\n\t"
      "jl .LFUN_001ddf9a_6\n\t"
      "cdq\n\t"
      "pushl $0x64\n\t"
      "popl %%esi\n\t"
      "idivl %%esi\n\t"
      "addb %%al, (%%ecx)\n\t"
      "movl %%edx, %%eax\n\t"
      ".LFUN_001ddf9a_6:\n\t"
      "incl %%ecx\n\t"
      "cmpl $0xa, %%eax\n\t"
      "jl .LFUN_001ddf9a_7\n\t"
      "cdq\n\t"
      "pushl $0xa\n\t"
      "popl %%esi\n\t"
      "idivl %%esi\n\t"
      "addb %%al, (%%ecx)\n\t"
      "movl %%edx, %%eax\n\t"
      ".LFUN_001ddf9a_7:\n\t"
      "addb %%al, 0x1(%%ecx)\n\t"
      ".LFUN_001ddf9a_8:\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c1ddf77] "m"(b1ddf9a_c1ddf77)
      : "memory");
}
#else
#error "FUN_001ddf9a: clang naked draft required"
#endif


/* FUN_001de043 (0x1de043) — XBE naked draft (batch 357). */
#if defined(__clang__)
static void (*const b1de043_c1e4209)(void) = (void *)FUN_001e4209;
static void (*const b1de043_c1e40d0)(void) = (void *)FUN_001e40d0;
static void (*const b1de043_c1ddf9a)(void) = (void *)FUN_001ddf9a;

__attribute__((naked, noinline))
void FUN_001de043(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x28, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "leal -0x28(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x10(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl 0x4(%%eax)\n\t"
      "pushl (%%eax)\n\t"
      "call *%[c1e4209]\n\t"
      "movl 0x10(%%ebp), %%esi\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "leal -0x10(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal 0x1(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "xorl %%eax, %%eax\n\t"
      "cmpl $0x2d, -0x10(%%ebp)\n\t"
      "sete %%al\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "testl %%esi, %%esi\n\t"
      "setg %%cl\n\t"
      "addl %%eax, %%edx\n\t"
      "addl %%edx, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1e40d0]\n\t"
      "pushl $0\n\t"
      "pushl 0x14(%%ebp)\n\t"
      "leal -0x10(%%ebp), %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl 0xc(%%ebp)\n\t"
      "call *%[c1ddf9a]\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "addl $0x2c, %%esp\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      :
      : [c1e4209] "m"(b1de043_c1e4209), [c1e40d0] "m"(b1de043_c1e40d0), [c1ddf9a] "m"(b1de043_c1ddf9a)
      : "memory");
}
#else
#error "FUN_001de043: clang naked draft required"
#endif


/* FUN_001de0a3 (0x1de0a3) — XBE naked draft (batch 337). */
#if defined(__clang__)
static void (*const b1de0a3_c1ddf77)(void) = FUN_001ddf77;

__attribute__((naked, noinline))
void FUN_001de0a3(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl %%eax, %%edi\n\t"
      "movl 0x4(%%edi), %%eax\n\t"
      "decl %%eax\n\t"
      "cmpb $0, 0x10(%%ebp)\n\t"
      "je .LFUN_001de0a3_1\n\t"
      "cmpl 0xc(%%ebp), %%eax\n\t"
      "jne .LFUN_001de0a3_1\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "cmpl $0x2d, (%%edi)\n\t"
      "sete %%cl\n\t"
      "addl %%eax, %%ecx\n\t"
      "addl 0x8(%%ebp), %%ecx\n\t"
      "movl %%ecx, %%eax\n\t"
      "movb $0x30, (%%eax)\n\t"
      "andb $0, 0x1(%%eax)\n\t"
      ".LFUN_001de0a3_1:\n\t"
      "cmpl $0x2d, (%%edi)\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "jne .LFUN_001de0a3_2\n\t"
      "movb $0x2d, (%%ebx)\n\t"
      "incl %%ebx\n\t"
      ".LFUN_001de0a3_2:\n\t"
      "movl 0x4(%%edi), %%eax\n\t"
      "xorl %%esi, %%esi\n\t"
      "incl %%esi\n\t"
      "testl %%eax, %%eax\n\t"
      "jg .LFUN_001de0a3_3\n\t"
      "movl %%ebx, %%ecx\n\t"
      "call *%[c1ddf77]\n\t"
      "movb $0x30, (%%ebx)\n\t"
      "incl %%ebx\n\t"
      "jmp .LFUN_001de0a3_4\n\t"
      ".LFUN_001de0a3_3:\n\t"
      "addl %%eax, %%ebx\n\t"
      ".LFUN_001de0a3_4:\n\t"
      "cmpl $0, 0xc(%%ebp)\n\t"
      "jle .LFUN_001de0a3_7\n\t"
      "movl %%ebx, %%ecx\n\t"
      "call *%[c1ddf77]\n\t"
      "movb 0x3317c0, %%al\n\t"
      "movb %%al, (%%ebx)\n\t"
      "movl 0x4(%%edi), %%edi\n\t"
      "incl %%ebx\n\t"
      "testl %%edi, %%edi\n\t"
      "jge .LFUN_001de0a3_7\n\t"
      "negl %%edi\n\t"
      "cmpb $0, 0x10(%%ebp)\n\t"
      "jne .LFUN_001de0a3_5\n\t"
      "cmpl %%edi, 0xc(%%ebp)\n\t"
      "jl .LFUN_001de0a3_6\n\t"
      ".LFUN_001de0a3_5:\n\t"
      "movl %%edi, 0xc(%%ebp)\n\t"
      ".LFUN_001de0a3_6:\n\t"
      "movl 0xc(%%ebp), %%esi\n\t"
      "movl %%ebx, %%ecx\n\t"
      "call *%[c1ddf77]\n\t"
      "movl %%esi, %%ecx\n\t"
      "movl %%ecx, %%edx\n\t"
      "shrl $2, %%ecx\n\t"
      "movl $0x30303030, %%eax\n\t"
      "movl %%ebx, %%edi\n\t"
      "rep stosl\n\t"
      "movl %%edx, %%ecx\n\t"
      "andl $3, %%ecx\n\t"
      "rep stosb\n\t"
      ".LFUN_001de0a3_7:\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c1ddf77] "m"(b1de0a3_c1ddf77)
      : "memory");
}
#else
#error "FUN_001de0a3: clang naked draft required"
#endif


/* FUN_001de14a (0x1de14a) — XBE naked draft (batch 365). */
#if defined(__clang__)
static void (*const b1de14a_c1e4209)(void) = (void *)FUN_001e4209;
static void (*const b1de14a_c1e40d0)(void) = (void *)FUN_001e40d0;
static void (*const b1de14a_c1de0a3)(void) = (void *)FUN_001de0a3;

__attribute__((naked, noinline))
void FUN_001de14a(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x28, %%esp\n\t"
      "pushl %%esi\n\t"
      "leal -0x28(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x10(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl 0x4(%%eax)\n\t"
      "pushl (%%eax)\n\t"
      "call *%[c1e4209]\n\t"
      "movl 0x10(%%ebp), %%esi\n\t"
      "leal -0x10(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "addl %%esi, %%eax\n\t"
      "pushl %%eax\n\t"
      "xorl %%eax, %%eax\n\t"
      "cmpl $0x2d, -0x10(%%ebp)\n\t"
      "sete %%al\n\t"
      "addl 0xc(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1e40d0]\n\t"
      "pushl $0\n\t"
      "pushl %%esi\n\t"
      "pushl 0xc(%%ebp)\n\t"
      "leal -0x10(%%ebp), %%eax\n\t"
      "call *%[c1de0a3]\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "addl $0x28, %%esp\n\t"
      "popl %%esi\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      :
      : [c1e4209] "m"(b1de14a_c1e4209), [c1e40d0] "m"(b1de14a_c1e40d0), [c1de0a3] "m"(b1de14a_c1de0a3)
      : "memory");
}
#else
#error "FUN_001de14a: clang naked draft required"
#endif


/* FUN_001de19c (0x1de19c) — XBE naked draft (batch 376). */
#if defined(__clang__)
static void (*const b1de19c_c1e4209)(void) = (void *)FUN_001e4209;
static void (*const b1de19c_c1e40d0)(void) = (void *)FUN_001e40d0;
static void (*const b1de19c_c1de0a3)(void) = (void *)FUN_001de0a3;
static void (*const b1de19c_c1ddf9a)(void) = (void *)FUN_001ddf9a;

__attribute__((naked, noinline))
void FUN_001de19c(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x28, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "leal -0x28(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x10(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl 0x4(%%eax)\n\t"
      "pushl (%%eax)\n\t"
      "call *%[c1e4209]\n\t"
      "movl -0xc(%%ebp), %%esi\n\t"
      "movl 0x10(%%ebp), %%ebx\n\t"
      "xorl %%eax, %%eax\n\t"
      "decl %%esi\n\t"
      "cmpl $0x2d, -0x10(%%ebp)\n\t"
      "sete %%al\n\t"
      "addl 0xc(%%ebp), %%eax\n\t"
      "movl %%eax, %%edi\n\t"
      "leal -0x10(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "call *%[c1e40d0]\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "addl $0x1c, %%esp\n\t"
      "decl %%eax\n\t"
      "cmpl %%eax, %%esi\n\t"
      "setl %%cl\n\t"
      "cmpl $-4, %%eax\n\t"
      "jl .LFUN_001de19c_3\n\t"
      "cmpl %%ebx, %%eax\n\t"
      "jge .LFUN_001de19c_3\n\t"
      "testb %%cl, %%cl\n\t"
      "je .LFUN_001de19c_2\n\t"
      ".LFUN_001de19c_1:\n\t"
      "movb (%%edi), %%al\n\t"
      "incl %%edi\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_001de19c_1\n\t"
      "andb %%al, -0x2(%%edi)\n\t"
      ".LFUN_001de19c_2:\n\t"
      "pushl $1\n\t"
      "pushl %%ebx\n\t"
      "pushl 0xc(%%ebp)\n\t"
      "leal -0x10(%%ebp), %%eax\n\t"
      "call *%[c1de0a3]\n\t"
      "addl $0xc, %%esp\n\t"
      "jmp .LFUN_001de19c_4\n\t"
      ".LFUN_001de19c_3:\n\t"
      "pushl $1\n\t"
      "pushl 0x14(%%ebp)\n\t"
      "pushl %%ebx\n\t"
      "pushl 0xc(%%ebp)\n\t"
      "leal -0x10(%%ebp), %%ebx\n\t"
      "call *%[c1ddf9a]\n\t"
      "addl $0x10, %%esp\n\t"
      ".LFUN_001de19c_4:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      :
      : [c1e4209] "m"(b1de19c_c1e4209), [c1e40d0] "m"(b1de19c_c1e40d0), [c1de0a3] "m"(b1de19c_c1de0a3), [c1ddf9a] "m"(b1de19c_c1ddf9a)
      : "memory");
}
#else
#error "FUN_001de19c: clang naked draft required"
#endif


/* __cfltcvt (0x1de229) — XBE naked draft (batch 335). */
#if defined(__clang__)
static void (*const b1de229_c1de14a)(void) = FUN_001de14a;
static void (*const b1de229_c1de19c)(void) = FUN_001de19c;
static void (*const b1de229_c1de043)(void) = FUN_001de043;

__attribute__((naked, noinline))
void __cfltcvt(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "cmpl $0x65, 0x10(%%ebp)\n\t"
      "je .L__cfltcvt_2\n\t"
      "cmpl $0x45, 0x10(%%ebp)\n\t"
      "je .L__cfltcvt_2\n\t"
      "cmpl $0x66, 0x10(%%ebp)\n\t"
      "jne .L__cfltcvt_1\n\t"
      "pushl 0x14(%%ebp)\n\t"
      "pushl 0xc(%%ebp)\n\t"
      "pushl 0x8(%%ebp)\n\t"
      "call *%[c1de14a]\n\t"
      "addl $0xc, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".L__cfltcvt_1:\n\t"
      "pushl 0x18(%%ebp)\n\t"
      "pushl 0x14(%%ebp)\n\t"
      "pushl 0xc(%%ebp)\n\t"
      "pushl 0x8(%%ebp)\n\t"
      "call *%[c1de19c]\n\t"
      "jmp .L__cfltcvt_3\n\t"
      ".L__cfltcvt_2:\n\t"
      "pushl 0x18(%%ebp)\n\t"
      "pushl 0x14(%%ebp)\n\t"
      "pushl 0xc(%%ebp)\n\t"
      "pushl 0x8(%%ebp)\n\t"
      "call *%[c1de043]\n\t"
      ".L__cfltcvt_3:\n\t"
      "addl $0x10, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c1de14a] "m"(b1de229_c1de14a), [c1de19c] "m"(b1de229_c1de19c), [c1de043] "m"(b1de229_c1de043)
      : "memory");
}
#else
#error "__cfltcvt: clang naked draft required"
#endif


/* FUN_001de27a (0x1de27a) — readable C lift: __controlfp(0x10000, 0x30000). */
void FUN_001de27a(void)
{
  ((void (*)(unsigned int, unsigned int))__controlfp)(0x10000u, 0x30000u);
}

/* __flsbuf (0x1de28c) — XBE naked draft (batch 312). */
#if defined(__clang__)
static void (*const b1de28c_c1e4278)(void) = __isatty;
static void (*const b1de28c_c1e28a4)(void) = __getbuf;
static void (*const b1de28c_c1df419)(void) = __write;
static void (*const b1de28c_c1e24d2)(void) = __lseek;

__attribute__((naked, noinline))
void __flsbuf(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0xc(%%ebp), %%esi\n\t"
      "movl 0xc(%%esi), %%eax\n\t"
      "testb $0x82, %%al\n\t"
      "movl 0x10(%%esi), %%ebx\n\t"
      "je .L__flsbuf_13\n\t"
      "testb $0x40, %%al\n\t"
      "jne .L__flsbuf_13\n\t"
      "testb $1, %%al\n\t"
      "je .L__flsbuf_1\n\t"
      "andl $0, 0x4(%%esi)\n\t"
      "testb $0x10, %%al\n\t"
      "je .L__flsbuf_13\n\t"
      "movl 0x8(%%esi), %%ecx\n\t"
      "andl $0xfffffffe, %%eax\n\t"
      "movl %%ecx, (%%esi)\n\t"
      "movl %%eax, 0xc(%%esi)\n\t"
      ".L__flsbuf_1:\n\t"
      "movl 0xc(%%esi), %%eax\n\t"
      "andl $0, 0x4(%%esi)\n\t"
      "andl $0, 0xc(%%ebp)\n\t"
      "andl $0xffffffef, %%eax\n\t"
      "orl $2, %%eax\n\t"
      "testw $0x10c, %%ax\n\t"
      "movl %%eax, 0xc(%%esi)\n\t"
      "jne .L__flsbuf_4\n\t"
      "cmpl $0x331050, %%esi\n\t"
      "je .L__flsbuf_2\n\t"
      "cmpl $0x331070, %%esi\n\t"
      "jne .L__flsbuf_3\n\t"
      ".L__flsbuf_2:\n\t"
      "pushl %%ebx\n\t"
      "call *%[c1e4278]\n\t"
      "testl %%eax, %%eax\n\t"
      "popl %%ecx\n\t"
      "jne .L__flsbuf_4\n\t"
      ".L__flsbuf_3:\n\t"
      "pushl %%esi\n\t"
      "call *%[c1e28a4]\n\t"
      "popl %%ecx\n\t"
      ".L__flsbuf_4:\n\t"
      "testw $0x108, 0xc(%%esi)\n\t"
      "pushl %%edi\n\t"
      "je .L__flsbuf_10\n\t"
      "movl 0x8(%%esi), %%eax\n\t"
      "movl (%%esi), %%edi\n\t"
      "leal 0x1(%%eax), %%ecx\n\t"
      "movl %%ecx, (%%esi)\n\t"
      "movl 0x18(%%esi), %%ecx\n\t"
      "subl %%eax, %%edi\n\t"
      "decl %%ecx\n\t"
      "testl %%edi, %%edi\n\t"
      "movl %%ecx, 0x4(%%esi)\n\t"
      "jle .L__flsbuf_5\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "call *%[c1df419]\n\t"
      "movl %%eax, 0xc(%%ebp)\n\t"
      "jmp .L__flsbuf_8\n\t"
      ".L__flsbuf_5:\n\t"
      "cmpl $-1, %%ebx\n\t"
      "je .L__flsbuf_6\n\t"
      "movl %%ebx, %%ecx\n\t"
      "sarl $5, %%ecx\n\t"
      "movl 0x632cc0(,%%ecx,4), %%ecx\n\t"
      "movl %%ebx, %%eax\n\t"
      "andl $0x1f, %%eax\n\t"
      "leal (%%eax,%%eax,4), %%eax\n\t"
      "leal (%%ecx,%%eax,8), %%eax\n\t"
      "jmp .L__flsbuf_7\n\t"
      ".L__flsbuf_6:\n\t"
      "movl $0x331608, %%eax\n\t"
      ".L__flsbuf_7:\n\t"
      "testb $0x20, 0x4(%%eax)\n\t"
      "je .L__flsbuf_9\n\t"
      "pushl $2\n\t"
      "pushl $0\n\t"
      "pushl %%ebx\n\t"
      "call *%[c1e24d2]\n\t"
      ".L__flsbuf_8:\n\t"
      "addl $0xc, %%esp\n\t"
      ".L__flsbuf_9:\n\t"
      "movl 0x8(%%esi), %%eax\n\t"
      "movb 0x8(%%ebp), %%cl\n\t"
      "movb %%cl, (%%eax)\n\t"
      "jmp .L__flsbuf_11\n\t"
      ".L__flsbuf_10:\n\t"
      "xorl %%edi, %%edi\n\t"
      "incl %%edi\n\t"
      "pushl %%edi\n\t"
      "leal 0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "call *%[c1df419]\n\t"
      "addl $0xc, %%esp\n\t"
      "movl %%eax, 0xc(%%ebp)\n\t"
      ".L__flsbuf_11:\n\t"
      "cmpl %%edi, 0xc(%%ebp)\n\t"
      "popl %%edi\n\t"
      "je .L__flsbuf_12\n\t"
      "orl $0x20, 0xc(%%esi)\n\t"
      "jmp .L__flsbuf_14\n\t"
      ".L__flsbuf_12:\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "andl $0xff, %%eax\n\t"
      "jmp .L__flsbuf_15\n\t"
      ".L__flsbuf_13:\n\t"
      "orl $0x20, %%eax\n\t"
      "movl %%eax, 0xc(%%esi)\n\t"
      ".L__flsbuf_14:\n\t"
      "orl $0xffffffff, %%eax\n\t"
      ".L__flsbuf_15:\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c1e4278] "m"(b1de28c_c1e4278), [c1e28a4] "m"(b1de28c_c1e28a4), [c1df419] "m"(b1de28c_c1df419), [c1e24d2] "m"(b1de28c_c1e24d2)
      : "memory");
}
#else
#error "__flsbuf: clang naked draft required"
#endif


/* FUN_001de3a5 (0x1de3a5) — XBE naked draft (batch 329). */
#if defined(__clang__)
static void (*const b1de3a5_c1de28c)(void) = __flsbuf;

__attribute__((naked, noinline))
void FUN_001de3a5(void)
{
  __asm__ volatile(
      "testb $0x40, 0xc(%%ecx)\n\t"
      "je .LFUN_001de3a5_1\n\t"
      "cmpl $0, 0x8(%%ecx)\n\t"
      "je .LFUN_001de3a5_4\n\t"
      ".LFUN_001de3a5_1:\n\t"
      "decl 0x4(%%ecx)\n\t"
      "js .LFUN_001de3a5_2\n\t"
      "movl (%%ecx), %%edx\n\t"
      "movb %%al, (%%edx)\n\t"
      "incl (%%ecx)\n\t"
      "movzbl %%al, %%eax\n\t"
      "jmp .LFUN_001de3a5_3\n\t"
      ".LFUN_001de3a5_2:\n\t"
      "movsbl %%al, %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "call *%[c1de28c]\n\t"
      "popl %%ecx\n\t"
      "popl %%ecx\n\t"
      ".LFUN_001de3a5_3:\n\t"
      "cmpl $-1, %%eax\n\t"
      "jne .LFUN_001de3a5_4\n\t"
      "orl %%eax, (%%esi)\n\t"
      "ret\n\t"
      ".LFUN_001de3a5_4:\n\t"
      "incl (%%esi)\n\t"
      "ret\n\t"
      :
      : [c1de28c] "m"(b1de3a5_c1de28c)
      : "memory");
}
#else
#error "FUN_001de3a5: clang naked draft required"
#endif


/* FUN_001de3d8 (0x1de3d8) — XBE naked draft (batch 338). */
#if defined(__clang__)
static void (*const b1de3d8_c1de3a5)(void) = FUN_001de3a5;

__attribute__((naked, noinline))
void FUN_001de3d8(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%esi\n\t"
      "movl %%eax, %%esi\n\t"
      "jmp .LFUN_001de3d8_2\n\t"
      ".LFUN_001de3d8_1:\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "movb 0x8(%%ebp), %%al\n\t"
      "decl 0xc(%%ebp)\n\t"
      "call *%[c1de3a5]\n\t"
      "cmpl $-1, (%%esi)\n\t"
      "je .LFUN_001de3d8_3\n\t"
      ".LFUN_001de3d8_2:\n\t"
      "cmpl $0, 0xc(%%ebp)\n\t"
      "jg .LFUN_001de3d8_1\n\t"
      ".LFUN_001de3d8_3:\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c1de3a5] "m"(b1de3d8_c1de3a5)
      : "memory");
}
#else
#error "FUN_001de3d8: clang naked draft required"
#endif


/* FUN_001de3fc (0x1de3fc) — XBE naked draft (batch 329). */
#if defined(__clang__)
static void (*const b1de3fc_c1de3a5)(void) = FUN_001de3a5;

__attribute__((naked, noinline))
void FUN_001de3fc(void)
{
  __asm__ volatile(
      "testb $0x40, 0xc(%%edi)\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl %%eax, %%esi\n\t"
      "movl %%ecx, %%ebx\n\t"
      "je .LFUN_001de3fc_2\n\t"
      "cmpl $0, 0x8(%%edi)\n\t"
      "jne .LFUN_001de3fc_2\n\t"
      "movl 0xc(%%esp), %%eax\n\t"
      "addl %%eax, (%%esi)\n\t"
      "jmp .LFUN_001de3fc_3\n\t"
      ".LFUN_001de3fc_1:\n\t"
      "movb (%%ebx), %%al\n\t"
      "decl 0xc(%%esp)\n\t"
      "movl %%edi, %%ecx\n\t"
      "call *%[c1de3a5]\n\t"
      "incl %%ebx\n\t"
      "cmpl $-1, (%%esi)\n\t"
      "je .LFUN_001de3fc_3\n\t"
      ".LFUN_001de3fc_2:\n\t"
      "cmpl $0, 0xc(%%esp)\n\t"
      "jg .LFUN_001de3fc_1\n\t"
      ".LFUN_001de3fc_3:\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      :
      : [c1de3a5] "m"(b1de3fc_c1de3a5)
      : "memory");
}
#else
#error "FUN_001de3fc: clang naked draft required"
#endif


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

