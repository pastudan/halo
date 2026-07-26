/* kb object stubs -> xdk/xapilib/lasterr.c */

/* --- XAPILIB:lasterr.obj batch drafts (2026-07-26) --- */

/* FUN_001d21f2 (0x1d21f2) — XBE naked draft (batch 316). */
#if defined(__clang__)
static void (*const b1d21f2_c1d1f10)(void) = FUN_001d1f10;

__attribute__((naked, noinline))
void FUN_001d21f2(void)
{
  __asm__ volatile(
      "xorl %%eax, %%eax\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "cmpl %%eax, 0xc(%%esp)\n\t"
      "setne %%cl\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl 0x18(%%esp)\n\t"
      "pushl 0x18(%%esp)\n\t"
      "call *%[c1d1f10]\n\t"
      "ret\n\t"
      :
      : [c1d1f10] "m"(b1d21f2_c1d1f10)
      : "memory");
}
#else
#error "FUN_001d21f2: clang naked draft required"
#endif


/* 0x1d2240 */
int xapi_GetLastError(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
  return 0;
}

/* 0x1d2268 */
void SetLastError(unsigned int error)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x1d2296 */
void XapiSetLastNTError(int status)
{
  int edx = 0;

  SetLastError(edx);

  (void)edx;
}

/* FUN_001d22ad (0x1d22ad) — XBE naked draft (batch 319). */
#if defined(__clang__)
static void __stdcall (*const b1d22ad_c1d2296)(int status) = (void *)XapiSetLastNTError;

__attribute__((naked, noinline))
void FUN_001d22ad(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x10, %%esp\n\t"
      "pushl %%esi\n\t"
      "movl 0xc(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%esi, 0xc(%%ebp)\n\t"
      "jne .LFUN_001d22ad_1\n\t"
      "pushl 0x14(%%ebp)\n\t"
      "leal 0xc(%%ebp), %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl $0x1f0003\n\t"
      "pushl %%eax\n\t"
      "call *0x2531d4\n\t"
      "testl %%eax, %%eax\n\t"
      "jge .LFUN_001d22ad_1\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d2296]\n\t"
      "jmp .LFUN_001d22ad_2\n\t"
      ".LFUN_001d22ad_1:\n\t"
      "cmpl $-1, 0x8(%%ebp)\n\t"
      "je .LFUN_001d22ad_3\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "pushl $0x1e\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "pushl $8\n\t"
      "leal -0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x10(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl 0x8(%%ebp)\n\t"
      "call *0x25315c\n\t"
      "testl %%eax, %%eax\n\t"
      "jge .LFUN_001d22ad_4\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d2296]\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LFUN_001d22ad_2\n\t"
      "pushl 0xc(%%ebp)\n\t"
      "call *0x253090\n\t"
      ".LFUN_001d22ad_2:\n\t"
      "xorl %%eax, %%eax\n\t"
      "jmp .LFUN_001d22ad_5\n\t"
      ".LFUN_001d22ad_3:\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_001d22ad_4\n\t"
      "andl $0, 0xc(%%ebp)\n\t"
      "pushl $0xc000000d\n\t"
      "call *%[c1d2296]\n\t"
      ".LFUN_001d22ad_4:\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      ".LFUN_001d22ad_5:\n\t"
      "popl %%esi\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      :
      : [c1d2296] "m"(b1d22ad_c1d2296)
      : "memory");
}
#else
#error "FUN_001d22ad: clang naked draft required"
#endif


/* FUN_001d2367 (0x1d2367) — XBE naked draft (batch 316). */
#if defined(__clang__)
static void (*const b1d2367_c1d4436)(void) = FUN_001d4436;
static void __stdcall (*const b1d2367_c1d2268)(unsigned int error) = (void *)SetLastError;
static void __stdcall (*const b1d2367_c1d2296)(int status) = (void *)XapiSetLastNTError;

__attribute__((naked, noinline))
void FUN_001d2367(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x10, %%esp\n\t"
      "pushl 0x18(%%ebp)\n\t"
      "leal -0x10(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d4436]\n\t"
      "pushl %%eax\n\t"
      "leal -0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal 0x18(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl 0x10(%%ebp)\n\t"
      "pushl 0x8(%%ebp)\n\t"
      "call *0x2531dc\n\t"
      "testl %%eax, %%eax\n\t"
      "movl $0x102, %%ecx\n\t"
      "jl .LFUN_001d2367_2\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "je .LFUN_001d2367_2\n\t"
      "cmpl $0, -0x8(%%ebp)\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "movl 0x18(%%ebp), %%ecx\n\t"
      "movl %%ecx, (%%eax)\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movl %%ecx, (%%eax)\n\t"
      "jge .LFUN_001d2367_1\n\t"
      "pushl -0x8(%%ebp)\n\t"
      "jmp .LFUN_001d2367_4\n\t"
      ".LFUN_001d2367_1:\n\t"
      "xorl %%eax, %%eax\n\t"
      "incl %%eax\n\t"
      "jmp .LFUN_001d2367_6\n\t"
      ".LFUN_001d2367_2:\n\t"
      "movl 0x14(%%ebp), %%edx\n\t"
      "andl $0, (%%edx)\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jne .LFUN_001d2367_3\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1d2268]\n\t"
      "jmp .LFUN_001d2367_5\n\t"
      ".LFUN_001d2367_3:\n\t"
      "pushl %%eax\n\t"
      ".LFUN_001d2367_4:\n\t"
      "call *%[c1d2296]\n\t"
      ".LFUN_001d2367_5:\n\t"
      "xorl %%eax, %%eax\n\t"
      ".LFUN_001d2367_6:\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      :
      : [c1d4436] "m"(b1d2367_c1d4436), [c1d2268] "m"(b1d2367_c1d2268), [c1d2296] "m"(b1d2367_c1d2296)
      : "memory");
}
#else
#error "FUN_001d2367: clang naked draft required"
#endif


/* 0x1d23d9 */
void GetOverlappedResult(void)
{
  int eax = 0;
  int esi = 0;

  /* relift: cmp dword ptr [esi], 0x103 -> jne 0x1d241e */
  /* relift: cmp dword ptr [esp + 0x14], 0 -> je 0x1d2402 */
  /* test eax, eax -> jne 0x1d23f8 */
  WaitForSingleObject(0, 0);
  /* cmp eax, 0x102 -> jne 0x1d241a */
  SetLastError(996);
  /* test eax, eax -> jne 0x1d2438 */
  /* test esi, esi -> jl 0x1d2432 */
  XapiSetLastNTError(0);

  (void)eax;
  (void)esi;
}

/* 0x1d243e */
void FUN_001d243e(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int ebp = 0;

  /* test eax, eax -> jne 0x1d2475 */
  /* relift: cmp dword ptr [ebp + 0xc], 0 -> jne 0x1d248c */
  /* relift: cmp dword ptr [ebp + 8], 0 -> je 0x1d250f */
  FUN_001d789a((char *)(uintptr_t)ebx, (char *)(uintptr_t)0, 519);
  /* test (char)ecx, (char)ecx -> jne 0x1d24ee */
  FUN_001d789a((char *)(uintptr_t)eax, (char *)0, 0);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)ebp;
}

/* XGetLaunchInfo (0x1d2518) — XBE naked draft (batch 331). */
#if defined(__clang__)


__attribute__((naked, noinline))
void XGetLaunchInfo(void)
{
  __asm__ volatile(
      "movl 0x2531f0, %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .LXGetLaunchInfo_2\n\t"
      "movl (%%ecx), %%eax\n\t"
      "cmpl $2, %%eax\n\t"
      "je .LXGetLaunchInfo_1\n\t"
      "cmpl $3, %%eax\n\t"
      "je .LXGetLaunchInfo_1\n\t"
      "movl 0x10118, %%edx\n\t"
      "movl 0x4(%%ecx), %%ecx\n\t"
      "cmpl 0x8(%%edx), %%ecx\n\t"
      "jne .LXGetLaunchInfo_2\n\t"
      ".LXGetLaunchInfo_1:\n\t"
      "movl 0x4(%%esp), %%ecx\n\t"
      "movl %%eax, (%%ecx)\n\t"
      "movl 0x2531f0, %%eax\n\t"
      "pushl %%esi\n\t"
      "movl (%%eax), %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x10(%%esp), %%edi\n\t"
      "addl $0x400, %%esi\n\t"
      "movl $0x300, %%ecx\n\t"
      "rep movsl\n\t"
      "movl 0x2531f0, %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "andl $0, (%%eax)\n\t"
      "pushl %%ecx\n\t"
      "call *0x2531f4\n\t"
      "popl %%edi\n\t"
      "xorl %%eax, %%eax\n\t"
      "popl %%esi\n\t"
      "jmp .LXGetLaunchInfo_3\n\t"
      ".LXGetLaunchInfo_2:\n\t"
      "movl $0x490, %%eax\n\t"
      ".LXGetLaunchInfo_3:\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "XGetLaunchInfo: clang naked draft required"
#endif


/* 0x1d259b */
void FUN_001d259b(void)
{
  int eax = 0;

  FUN_001d243e();
  /* test eax, eax -> jl 0x1d25d5 */
  /* test eax, eax -> je 0x1d25cd */

  (void)eax;
}

/* 0x1d25e0 */
int XLaunchNewImageA(const char *image_path, void *launch_data)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int esi = 0;

  /* cmp esi, ebx -> je 0x1d2612 */
  /* cmp (char)eax, 0x44 -> je 0x1d25fe */
  /* cmp (char)eax, 0x64 -> jne 0x1d260a */
  /* relift: cmp byte ptr [esi + 1], 0x3a -> jne 0x1d260a */
  /* relift: cmp byte ptr [esi + 2], 0x5c -> je 0x1d2631 */
  /* cmp eax, ebx -> jl 0x1d26b4 */
  /* cmp ecx, eax -> ja 0x1d269e */
  FUN_001d789a((char *)(uintptr_t)eax, (char *)(uintptr_t)eax, 0);
  /* cmp (char)ecx, (char)ebx -> jne 0x1d26b6 */
  FUN_001d259b();
  return 0;

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)esi;
}

/* 0x1d26f3 */
int XSetNicknameW(void *param_1, int param_2)
{
  int eax = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  /* relift: cmp word ptr [edi], (int16_t)esi -> jne 0x1d270f */
  /* relift: cmp dword ptr [ebp - 0x1c], 0xd48 -> je 0x1d2791 */
  /* relift: cmp dword ptr [ebp - 0xc], esi -> jl 0x1d2911 */
  FUN_001d7a59();
  /* relift: cmp eax, dword ptr [edi - 4] -> jne 0x1d27d5 */
  __wcsicmp((wchar_t *)0, (wchar_t *)(uintptr_t)edi);
  /* relift: cmp dword ptr [ebp - 8], 0x32 -> jb 0x1d27af */
  /* relift: cmp dword ptr [ebp + 0xc], esi -> jne 0x1d2801 */
  FUN_001d7a59();
  /* cmp ecx, 0x32 -> jne 0x1d2810 */
  /* relift: cmp dword ptr [ebp - 0x10], esi -> jne 0x1d2840 */
  /* cmp ecx, esi -> jne 0x1d2844 */
  _wcscmp((wchar_t *)(uintptr_t)eax, (wchar_t *)(uintptr_t)eax);
  /* cmp ecx, esi -> je 0x1d2867 */
  /* cmp ecx, eax -> jae 0x1d284d */
  memmove((void *)(uintptr_t)eax, (void *)(uintptr_t)eax, eax);
  FUN_001d7a59();
  /* relift: cmp dword ptr [ebp - 0xc], esi -> jge 0x1d28d2 */
  /* cmp edi, esi -> jl 0x1d2903 */
  FUN_001d7a59();
  /* cmp eax, 0xc0000034 -> je 0x1d2882 */
  return 0;

  (void)eax;
  (void)ecx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* FUN_001d292e (0x1d292e) — XBE naked draft (batch 327). */
#if defined(__clang__)
static size_t (*const b1d292e_c1db11e)(const wchar_t *str) = _wcslen;
static int (*const b1d292e_c1dc2c3)(const wchar_t *s1, const wchar_t *s2) = __wcsicmp;
static void (*const b1d292e_c1db180)(void) = _wcscpy;

__attribute__((naked, noinline))
void FUN_001d292e(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "movl 0x10118, %%eax\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "pushl %%edi\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "jmp .LFUN_001d292e_7\n\t"
      ".LFUN_001d292e_1:\n\t"
      "movl 0x4(%%esi), %%eax\n\t"
      "imull $0x44, %%eax, %%eax\n\t"
      "leal 0x10(%%eax,%%esi,1), %%eax\n\t"
      "xorl %%edi, %%edi\n\t"
      "cmpw %%di, (%%eax)\n\t"
      "je .LFUN_001d292e_6\n\t"
      "pushl %%eax\n\t"
      "call *%[c1db11e]\n\t"
      "cmpl 0x10(%%ebp), %%eax\n\t"
      "popl %%ecx\n\t"
      "jae .LFUN_001d292e_6\n\t"
      "movl 0x8(%%esi), %%eax\n\t"
      "cmpl %%edi, %%eax\n\t"
      "je .LFUN_001d292e_2\n\t"
      "movl 0x4(%%esi), %%ecx\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "imull $0x44, %%ecx, %%ecx\n\t"
      "cmpl 0xc(%%ecx,%%esi,1), %%edx\n\t"
      "jne .LFUN_001d292e_6\n\t"
      ".LFUN_001d292e_2:\n\t"
      "cmpl %%edi, %%eax\n\t"
      "movl %%edi, 0x8(%%ebp)\n\t"
      "jne .LFUN_001d292e_5\n\t"
      "cmpl %%edi, 0x4(%%esi)\n\t"
      "jbe .LFUN_001d292e_5\n\t"
      "leal 0x10(%%esi), %%ebx\n\t"
      ".LFUN_001d292e_3:\n\t"
      "movl 0x4(%%esi), %%eax\n\t"
      "imull $0x44, %%eax, %%eax\n\t"
      "leal 0x10(%%eax,%%esi,1), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "call *%[c1dc2c3]\n\t"
      "testl %%eax, %%eax\n\t"
      "popl %%ecx\n\t"
      "popl %%ecx\n\t"
      "je .LFUN_001d292e_4\n\t"
      "incl %%edi\n\t"
      "addl $0x44, %%ebx\n\t"
      "cmpl 0x4(%%esi), %%edi\n\t"
      "jb .LFUN_001d292e_3\n\t"
      "jmp .LFUN_001d292e_5\n\t"
      ".LFUN_001d292e_4:\n\t"
      "movl $1, 0x8(%%ebp)\n\t"
      ".LFUN_001d292e_5:\n\t"
      "cmpl $0, 0x8(%%esi)\n\t"
      "jne .LFUN_001d292e_9\n\t"
      "cmpl $0, 0x8(%%ebp)\n\t"
      "je .LFUN_001d292e_9\n\t"
      ".LFUN_001d292e_6:\n\t"
      "incl 0x4(%%esi)\n\t"
      ".LFUN_001d292e_7:\n\t"
      "cmpl $0x32, 0x4(%%esi)\n\t"
      "jb .LFUN_001d292e_1\n\t"
      "xorl %%eax, %%eax\n\t"
      ".LFUN_001d292e_8:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      ".LFUN_001d292e_9:\n\t"
      "movl 0x4(%%esi), %%eax\n\t"
      "imull $0x44, %%eax, %%eax\n\t"
      "leal 0x10(%%eax,%%esi,1), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl 0xc(%%ebp)\n\t"
      "call *%[c1db180]\n\t"
      "incl 0x4(%%esi)\n\t"
      "popl %%ecx\n\t"
      "xorl %%eax, %%eax\n\t"
      "popl %%ecx\n\t"
      "incl %%eax\n\t"
      "jmp .LFUN_001d292e_8\n\t"
      :
      : [c1db11e] "m"(b1d292e_c1db11e), [c1dc2c3] "m"(b1d292e_c1dc2c3), [c1db180] "m"(b1d292e_c1db180)
      : "memory");
}
#else
#error "FUN_001d292e: clang naked draft required"
#endif


/* 0x1d29eb */
int FUN_001d29eb(int param_1, void *param_2, int param_3)
{
  int eax = 0;
  int ebx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  /* cmp eax, edi -> jl 0x1d2ac5 */
  FUN_001d0bb9(edi, 3412);
  /* cmp esi, edi -> je 0x1d2a7f */
  /* relift: cmp dword ptr [ebp - 8], ebx -> je 0x1d2a86 */
  FUN_001d292e();
  /* test eax, eax -> jne 0x1d2aac */
  /* relift: cmp dword ptr [ebp + 8], edi -> jge 0x1d2abd */
  /* cmp esi, edi -> je 0x1d2ac5 */
  LocalFree((void *)(uintptr_t)esi);
  /* cmp esi, edi -> je 0x1d2ac5 */
  return 0;

  (void)eax;
  (void)ebx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x1d2ad3 */
void FUN_001d2ad3(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* FUN_001d2ae7 (0x1d2ae7) — XBE naked draft (batch 320). */
#if defined(__clang__)
static void (*const b1d2ae7_c1dd620)(void) = __allmul;
static void (*const b1d2ae7_c1dd680)(void) = __aullrem;
static void (*const b1d2ae7_c1dd660)(void) = __aullshr;
static void (*const b1d2ae7_c1d2ad3)(void) = FUN_001d2ad3;

__attribute__((naked, noinline))
void FUN_001d2ae7(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ecx\n\t"
      "andl $0, -0x8(%%ebp)\n\t"
      "andl $0, -0x4(%%ebp)\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw (%%esi), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "pushl %%edi\n\t"
      "je .LFUN_001d2ae7_2\n\t"
      "movl %%eax, %%edi\n\t"
      ".LFUN_001d2ae7_1:\n\t"
      "pushl $0\n\t"
      "pushl $0x10000\n\t"
      "pushl -0x4(%%ebp)\n\t"
      "pushl -0x8(%%ebp)\n\t"
      "call *%[c1dd620]\n\t"
      "movl %%eax, %%ecx\n\t"
      "movzwl %%di, %%eax\n\t"
      "movl %%edx, %%ebx\n\t"
      "cdq\n\t"
      "pushl $0xffff\n\t"
      "addl %%eax, %%ecx\n\t"
      "pushl $-0x3b\n\t"
      "adcl %%edx, %%ebx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1dd680]\n\t"
      "incl %%esi\n\t"
      "incl %%esi\n\t"
      "xorl %%edi, %%edi\n\t"
      "movw (%%esi), %%di\n\t"
      "testw %%di, %%di\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      "jne .LFUN_001d2ae7_1\n\t"
      ".LFUN_001d2ae7_2:\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "pushl $0xb\n\t"
      "popl %%esi\n\t"
      "xorl %%ebx, %%ebx\n\t"
      ".LFUN_001d2ae7_3:\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "movl %%ebx, %%ecx\n\t"
      "call *%[c1dd660]\n\t"
      "andl $0xf, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d2ad3]\n\t"
      "movb %%al, (%%esi,%%edi,1)\n\t"
      "addl $4, %%ebx\n\t"
      "decl %%esi\n\t"
      "cmpl $0x2c, %%ebx\n\t"
      "jle .LFUN_001d2ae7_3\n\t"
      "andb $0, 0xc(%%edi)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      :
      : [c1dd620] "m"(b1d2ae7_c1dd620), [c1dd680] "m"(b1d2ae7_c1dd680), [c1dd660] "m"(b1d2ae7_c1dd660), [c1d2ad3] "m"(b1d2ae7_c1d2ad3)
      : "memory");
}
#else
#error "FUN_001d2ae7: clang naked draft required"
#endif


/* 0x1d2b79 */
void FUN_001d2b79(void)
{
  int eax = 0;
  int ebp = 0;

  SetFilePointer(0, 0, (void *)0, 0);
  ReadFile(0, (void *)(uintptr_t)eax, 0, (void *)(uintptr_t)eax, (void *)0);
  /* test eax, eax -> je 0x1d2baa */
  /* relift: cmp dword ptr [ebp - 8], 2 -> je 0x1d2bb6 */
  /* relift: cmp word ptr [ebp - 4], 0xfeff -> je 0x1d2bb6 */

  (void)eax;
  (void)ebp;
}

/* 0x1d2bbd */
void FUN_001d2bbd(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  _wcslen((wchar_t *)(uintptr_t)0);
  /* relift: cmp dword ptr [ebp - 8], ebx -> jne 0x1d2c1a */
  ReadFile(0, (void *)(uintptr_t)edi, eax, (void *)0, (void *)0);
  /* test eax, eax -> je 0x1d2d3e */
  /* relift: cmp dword ptr [ebp - 0xc], ebx -> je 0x1d2d3e */
  _wcsstr((wchar_t *)(uintptr_t)eax, (wchar_t *)0x002c1cb8);
  /* cmp eax, ebx -> jae 0x1d2c96 */
  memmove((void *)(uintptr_t)eax, (void *)(uintptr_t)eax, esi);
  _wcsstr((wchar_t *)(uintptr_t)eax, (wchar_t *)(uintptr_t)0);
  /* relift: cmp word ptr [ecx + eax], 0x3d -> jne 0x1d2ce5 */
  _wcsstr((wchar_t *)(uintptr_t)edi, (wchar_t *)0x002c1cb8);
  /* cmp edi, eax -> jl 0x1d2d02 */
  _wcsncpy((wchar_t *)(uintptr_t)0, (wchar_t *)0, edi);
  /* cmp esi, ebx -> jae 0x1d2d37 */
  SetFilePointer(0, 0, (void *)0, 0);
  /* test (char)eax, (char)eax -> jne 0x1d2d64 */
  /* test dl, dl -> jne 0x1d2d6e */
  /* test (char)ebx, (char)ebx -> jne 0x1d2d82 */
  /* test (char)ebx, (char)ebx -> jne 0x1d2d98 */
  /* cmp edi, 0x103 -> jae 0x1d2dbf */
  /* cmp edi, 0xf7 -> jge 0x1d2e3e */
  /* test dl, dl -> jne 0x1d2dd9 */
  CreateFileA((char *)(uintptr_t)eax, 0x80000000, 0, 0, 0, ebx, 0);
  FUN_001d2b79();
  /* relift: tail-call FUN_001d2bbd(); */
  CloseHandle(0);
  CreateFileA((char *)0, 0x80100000, esi, esi, 0, 0, esi);
  /* cmp edi, -1 -> je 0x1d2eb7 */
  FUN_001d2b79();
  /* test eax, eax -> je 0x1d2eaa */
  /* relift: tail-call FUN_001d2bbd(); */
  /* test eax, eax -> je 0x1d2eaa */
  _wcscmp((wchar_t *)(uintptr_t)eax, (wchar_t *)(uintptr_t)0);
  CloseHandle(0);
  xapi_GetLastError();
  CreateFileA((char *)0, 0xc0000000, 0, 0, 0, 0x02000000, 0);
  /* cmp esi, -1 -> je 0x1d2f1d */
  CloseHandle(0);
  /* test (char)ecx, (char)ecx -> jne 0x1d2f36 */
  /* test (char)ecx, (char)ecx -> jne 0x1d2f49 */
  FUN_001d2ae7();
  /* test dl, dl -> jne 0x1d2f73 */
  /* test (char)ecx, (char)ecx -> jne 0x1d2f97 */
  FUN_001d2e48();
  /* test eax, eax -> je 0x1d3135 */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}
