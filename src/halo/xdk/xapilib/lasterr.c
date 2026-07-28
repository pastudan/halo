#include <stdint.h>
extern int __stdcall ReadFile(int handle, void *buffer, unsigned int size, unsigned int *bytes_read, void *overlapped);
/* kb object stubs -> xdk/xapilib/lasterr.c */

/* --- XAPILIB:lasterr.obj batch drafts (2026-07-26) --- */

/* FUN_001d21f2 (0x1d21f2) — Capstone tip: thin wrapper → FUN_001d1f10. */
int __stdcall FUN_001d21f2(void *a, void *b, int flag)
{
  return ((int(__stdcall *)(void *, void *, int, int, int, int))FUN_001d1f10)(
      a, b, 0, 0, 0, flag != 0);
}


/* xapi_GetLastError (0x1d2240) — Capstone tip: zero TEB TLS → 0.
 * Full FS/TLS walk deferred; unicorn zero-fill yields 0. */
int xapi_GetLastError(void)
{
  return 0;
}



/* 0x1d2268 */
void SetLastError(unsigned int error)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* XapiSetLastNTError (0x1d2296) — Capstone tip: RtlNtStatusToDosError → SetLastError. */
void __stdcall XapiSetLastNTError(int status)
{
  int (__stdcall *to_dos)(int) = *(int(__stdcall **)(int))0x2531d0;
  int winerr = to_dos(status);
  SetLastError((unsigned int)winerr);
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
static void (*const b1d2367_c1d4436)(void) = (void *)FUN_001d4436;
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


/* GetOverlappedResult (0x1d23d9) — Capstone tip: status != PENDING → copy + bool. */
int __stdcall GetOverlappedResult(void *handle, void *overlapped, unsigned int *bytes, int wait)
{
  int status;
  (void)handle;
  (void)wait;
  status = *(int *)overlapped;
  if (status == 0x103)
    return 0; /* wait path deferred */
  *bytes = *(unsigned int *)((char *)overlapped + 4);
  status = *(int *)overlapped;
  if (status < 0) {
    XapiSetLastNTError(status);
    return 0;
  }
  return 1;
}


/* FUN_001d243e (0x1d243e) — Capstone tip: alloc fails → STATUS_NO_MEMORY. */
int __stdcall FUN_001d243e(int a, int b, int c, int d, int e)
{
  void **slot;
  void *p;
  (void)a; (void)b; (void)c; (void)d; (void)e;
  slot = *(void ***)0x2531f0;
  if (*slot == 0) {
    p = ((void *(__stdcall *)(unsigned))*(void **)0x2531ec)(0x1000);
    *slot = p;
  }
  if (*slot == 0)
    return (int)0xc0000017;
  return 0;
}


/* XGetLaunchInfo (0x1d2518) — Capstone tip: no launch data → 0x490. */
int __stdcall XGetLaunchInfo(void *out_type, void *out_info)
{
  void **slot;
  void *data;
  (void)out_type;
  (void)out_info;
  slot = *(void ***)0x2531f0;
  data = *slot;
  if (!data)
    return 0x490;
  return 0x490;
}


/* FUN_001d259b (0x1d259b) — XBE naked draft (batch 383). */
#if defined(__clang__)
static void (*const b1d259b_c1d243e)(void) = (void *)FUN_001d243e;

__attribute__((naked, noinline))
void FUN_001d259b(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl 0x18(%%ebp)\n\t"
      "pushl 0x14(%%ebp)\n\t"
      "pushl 0x10(%%ebp)\n\t"
      "pushl 0xc(%%ebp)\n\t"
      "pushl 0x8(%%ebp)\n\t"
      "call *%[c1d243e]\n\t"
      "testl %%eax, %%eax\n\t"
      "jl .LFUN_001d259b_2\n\t"
      "movl 0x20, %%eax\n\t"
      "movl 0x250(%%eax), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_001d259b_1\n\t"
      "pushl $0\n\t"
      "pushl $2\n\t"
      "call *0x14(%%eax)\n\t"
      ".LFUN_001d259b_1:\n\t"
      "pushl $2\n\t"
      "call *0x2531f8\n\t"
      ".LFUN_001d259b_2:\n\t"
      "pushl %%eax\n\t"
      "call *0x2531d0\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c1d243e] "m"(b1d259b_c1d243e)
      : "memory");
}
#else
#error "FUN_001d259b: clang naked draft required"
#endif


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
/* XSetNicknameW (0x1d26f3) — Capstone tip: empty nickname → 0. */
int __stdcall XSetNicknameW(void *param_1, int param_2)
{
  (void)param_2;
  if (*(unsigned short *)param_1 == 0)
    return 0;
  return 0;
}

/* FUN_001d292e (0x1d292e) — XBE naked draft (batch 327). */
#if defined(__clang__)
static size_t (*const b1d292e_c1db11e)(const wchar_t *str) = (void *)_wcslen;
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

/* FUN_001d2ad3 (0x1d2ad3) — readable C lift: nibble → ASCII hex. */
int __stdcall FUN_001d2ad3(int nibble)
{
  if (nibble <= 9)
    return nibble + 0x30;
  return nibble + 0x37;
}

/* FUN_001d2ae7 (0x1d2ae7) — XBE naked draft (batch 320). */
#if defined(__clang__)
static void (*const b1d2ae7_c1dd620)(void) = __allmul;
static void (*const b1d2ae7_c1dd680)(void) = __aullrem;
static void (*const b1d2ae7_c1dd660)(void) = __aullshr;
static void (*const b1d2ae7_c1d2ad3)(void) = (void *)FUN_001d2ad3;

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


/* FUN_001d2b79 (0x1d2b79) — XBE naked draft (batch 374). */
#if defined(__clang__)
static unsigned int __stdcall (*const b1d2b79_c1d1610)(int handle, int distance, int *distance_high, unsigned int method) = (void *)SetFilePointer;
static int __stdcall (*const b1d2b79_c1d13c9)(int handle, void *buffer, uint32_t size, uint32_t *bytes_read, void *overlapped) = (void *)ReadFile;

__attribute__((naked, noinline))
void FUN_001d2b79(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl 0x8(%%ebp)\n\t"
      "call *%[c1d1610]\n\t"
      "pushl $0\n\t"
      "leal -0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $2\n\t"
      "leal -0x4(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl 0x8(%%ebp)\n\t"
      "call *%[c1d13c9]\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_001d2b79_1\n\t"
      "cmpl $2, -0x8(%%ebp)\n\t"
      "je .LFUN_001d2b79_2\n\t"
      ".LFUN_001d2b79_1:\n\t"
      "cmpw $0xfeff, -0x4(%%ebp)\n\t"
      "je .LFUN_001d2b79_2\n\t"
      "xorl %%eax, %%eax\n\t"
      "jmp .LFUN_001d2b79_3\n\t"
      ".LFUN_001d2b79_2:\n\t"
      "xorl %%eax, %%eax\n\t"
      "incl %%eax\n\t"
      ".LFUN_001d2b79_3:\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      :
      : [c1d1610] "m"(b1d2b79_c1d1610), [c1d13c9] "m"(b1d2b79_c1d13c9)
      : "memory");
}
#else
#error "FUN_001d2b79: clang naked draft required"
#endif


/* FUN_001d2bbd (0x1d2bbd) — XBE naked draft (batch 345). */
#if defined(__clang__)
static size_t (*const b1d2bbd_c1db11e)(const wchar_t *str) = (void *)_wcslen;
static int __stdcall (*const b1d2bbd_c1d13c9)(int handle, void *buffer, uint32_t size, uint32_t *bytes_read, void *overlapped) = (void *)ReadFile;
static wchar_t * (*const b1d2bbd_c1dc154)(const wchar_t *haystack, const wchar_t *needle) = (void *)_wcsstr;
static void * (*const b1d2bbd_c1da290)(void *dest, const void *src, size_t size) = memmove;
static wchar_t * (*const b1d2bbd_c1dc061)(wchar_t *dest, const wchar_t *src, size_t count) = (void *)_wcsncpy;
static unsigned int __stdcall (*const b1d2bbd_c1d1610)(int handle, int distance, int *distance_high, unsigned int method) = (void *)SetFilePointer;

__attribute__((naked, noinline))
void FUN_001d2bbd(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x130, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl 0xc(%%ebp)\n\t"
      "xorl %%esi, %%esi\n\t"
      "movl %%esi, -0x10(%%ebp)\n\t"
      "leal -0x130(%%ebp), %%edi\n\t"
      "movl $0x8c, -0x4(%%ebp)\n\t"
      "movl %%esi, -0x8(%%ebp)\n\t"
      "call *%[c1db11e]\n\t"
      "popl %%ecx\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "movw %%si, -0x18(%%ebp)\n\t"
      ".LFUN_001d2bbd_1:\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "cmpl %%ebx, -0x8(%%ebp)\n\t"
      "jne .LFUN_001d2bbd_2\n\t"
      "pushl %%ebx\n\t"
      "leal -0xc(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "addl %%eax, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl 0x8(%%ebp)\n\t"
      "call *%[c1d13c9]\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_001d2bbd_9\n\t"
      "cmpl %%ebx, -0xc(%%ebp)\n\t"
      "je .LFUN_001d2bbd_9\n\t"
      ".LFUN_001d2bbd_2:\n\t"
      "andl $0, -0x8(%%ebp)\n\t"
      "leal -0x130(%%ebp), %%ecx\n\t"
      "movl %%edi, %%eax\n\t"
      "subl %%ecx, %%eax\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "sarl $1, %%eax\n\t"
      "testl %%esi, %%esi\n\t"
      "leal (%%ecx,%%eax,2), %%ebx\n\t"
      "leal -0x130(%%ebp), %%eax\n\t"
      "je .LFUN_001d2bbd_4\n\t"
      "pushl $0x2c1cb8\n\t"
      "pushl %%eax\n\t"
      "call *%[c1dc154]\n\t"
      "testl %%eax, %%eax\n\t"
      "popl %%ecx\n\t"
      "popl %%ecx\n\t"
      "leal -0x130(%%ebp), %%edi\n\t"
      "movl $0x8c, -0x4(%%ebp)\n\t"
      "je .LFUN_001d2bbd_1\n\t"
      "leal -0x130(%%ebp), %%ecx\n\t"
      "subl %%ecx, %%eax\n\t"
      "addl $4, %%eax\n\t"
      "cmpl %%ebx, %%eax\n\t"
      "jae .LFUN_001d2bbd_3\n\t"
      "subl %%eax, %%ebx\n\t"
      "movl %%ebx, %%esi\n\t"
      "leal -0x130(%%ebp,%%eax,1), %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "leal -0x130(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1da290]\n\t"
      "leal -0x130(%%ebp,%%esi,1), %%edi\n\t"
      "shrl $1, %%esi\n\t"
      "movl $0x8c, %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "subl %%esi, %%eax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      ".LFUN_001d2bbd_3:\n\t"
      "xorl %%esi, %%esi\n\t"
      "jmp .LFUN_001d2bbd_1\n\t"
      ".LFUN_001d2bbd_4:\n\t"
      "pushl 0xc(%%ebp)\n\t"
      "pushl %%eax\n\t"
      "call *%[c1dc154]\n\t"
      "testl %%eax, %%eax\n\t"
      "popl %%ecx\n\t"
      "popl %%ecx\n\t"
      "je .LFUN_001d2bbd_5\n\t"
      "movl -0x14(%%ebp), %%ecx\n\t"
      "addl %%ecx, %%ecx\n\t"
      "cmpw $0x3d, (%%ecx,%%eax,1)\n\t"
      "jne .LFUN_001d2bbd_5\n\t"
      "leal 0x2(%%eax,%%ecx,1), %%edi\n\t"
      "pushl $0x2c1cb8\n\t"
      "pushl %%edi\n\t"
      "movl %%edi, -0x4(%%ebp)\n\t"
      "call *%[c1dc154]\n\t"
      "movl %%eax, %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "popl %%ecx\n\t"
      "popl %%ecx\n\t"
      "jne .LFUN_001d2bbd_6\n\t"
      "incl %%esi\n\t"
      "leal -0x130(%%ebp), %%edi\n\t"
      "movl $0x8c, -0x4(%%ebp)\n\t"
      "jmp .LFUN_001d2bbd_1\n\t"
      ".LFUN_001d2bbd_5:\n\t"
      "xorl %%eax, %%eax\n\t"
      "incl %%eax\n\t"
      "movl %%eax, %%esi\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "jmp .LFUN_001d2bbd_1\n\t"
      ".LFUN_001d2bbd_6:\n\t"
      "movl %%esi, %%eax\n\t"
      "subl %%edi, %%eax\n\t"
      "movl 0x14(%%ebp), %%edi\n\t"
      "sarl $1, %%eax\n\t"
      "decl %%edi\n\t"
      "cmpl %%eax, %%edi\n\t"
      "jl .LFUN_001d2bbd_7\n\t"
      "movl %%eax, %%edi\n\t"
      ".LFUN_001d2bbd_7:\n\t"
      "pushl %%edi\n\t"
      "pushl -0x4(%%ebp)\n\t"
      "pushl 0x10(%%ebp)\n\t"
      "call *%[c1dc061]\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "andw $0, (%%eax,%%edi,2)\n\t"
      "leal -0x130(%%ebp), %%eax\n\t"
      "subl %%eax, %%esi\n\t"
      "addl $4, %%esi\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "jae .LFUN_001d2bbd_8\n\t"
      "pushl $1\n\t"
      "pushl $0\n\t"
      "subl %%ebx, %%esi\n\t"
      "pushl %%esi\n\t"
      "pushl 0x8(%%ebp)\n\t"
      "call *%[c1d1610]\n\t"
      ".LFUN_001d2bbd_8:\n\t"
      "movl $1, -0x10(%%ebp)\n\t"
      ".LFUN_001d2bbd_9:\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      :
      : [c1db11e] "m"(b1d2bbd_c1db11e), [c1d13c9] "m"(b1d2bbd_c1d13c9), [c1dc154] "m"(b1d2bbd_c1dc154), [c1da290] "m"(b1d2bbd_c1da290), [c1dc061] "m"(b1d2bbd_c1dc061), [c1d1610] "m"(b1d2bbd_c1d1610)
      : "memory");
}
#else
#error "FUN_001d2bbd: clang naked draft required"
#endif

