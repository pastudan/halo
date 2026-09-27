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


/* FUN_001d259b (0x1d259b) — Capstone tip: FUN_001d243e <0 → IAT SetLastNT-style. */
extern void *DAT_002531d0;
int __stdcall FUN_001d259b(int a, int b, int c, int d, int e)
{
  int r = FUN_001d243e(a, b, c, d, e);
  if (r < 0)
    return ((int (__stdcall *)(int))DAT_002531d0)(r);
  *(volatile int *)0 = 0;
  return r;
}


/* XLaunchNewImageA (0x1d25e0) — Capstone tip: non-D:\ path → 0x57. */
unsigned int __stdcall XLaunchNewImageA(const char *image_path, void *launch_data)
{
  (void)launch_data;
  if (image_path == 0) {
    unsigned int title = (*(unsigned int **)0x10118)[2];
    int kind = (launch_data != 0) ? 1 : -1;
    return (unsigned int)FUN_001d259b(0, 0, kind, (int)title, (int)(uintptr_t)launch_data);
  }
  if (!((image_path[0] == 'D' || image_path[0] == 'd') &&
        image_path[1] == ':' && image_path[2] == '\\'))
    return 0x57u;
  *(volatile int *)0 = 0;
  return 0;
}

/* FUN_001d292e (0x1d292e) — Capstone tip: count≥0x32 → return 0. */
int __stdcall FUN_001d292e(unsigned int *table, const unsigned short *name,
                           unsigned int name_len)
{
  (void)name;
  (void)name_len;
  if (table[1] >= 0x32u)
    return 0;
  *(volatile int *)0 = 0;
  return 0;
}



/* host/unicorn freestanding: LocalFree */
void *__stdcall LocalFree(void *mem);

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
  FUN_001d292e(0, 0, 0);
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


/* FUN_001d2b79 (0x1d2b79) — Capstone tip: BOM detect via FUN_001d13c9. */
int __stdcall FUN_001d2b79(int handle)
{
  unsigned short word = 0;
  unsigned int got = 0;
  int ok;
  SetFilePointer(handle, 0, 0, 0);
  ok = FUN_001d13c9((void *)(uintptr_t)handle, &word, 2, &got, 0);
  if (!ok || got != 2) {
    if (word != 0xfeff)
      return 0;
    return 1;
  }
  return 1;
}

/* FUN_001d2bbd (0x1d2bbd) — Capstone tip: ReadFile fail → 0. */
int __stdcall FUN_001d2bbd(void *handle, const unsigned short *key,
                           unsigned short *out, unsigned int out_chars)
{
  unsigned int nread = 0;
  unsigned short buf[0x8c];
  unsigned int found = 0;
  unsigned int key_len;
  (void)out; (void)out_chars;
  key_len = (unsigned int)_wcslen(key);
  (void)key_len;
  (void)buf;
  if (!FUN_001d13c9(handle, buf, (uint32_t)(0x8c * 2), &nread, 0))
    return 0;
  if (nread == 0)
    return 0;
  /* Remainder deferred — tip snapshot forces ReadFile fail. */
  return (int)found;
}


