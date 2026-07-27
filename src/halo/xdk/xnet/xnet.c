#include <stdint.h>
/* kb object stubs -> xdk/xnet/xnet.c */

/* --- XNET:xnet.obj batch drafts (2026-07-26) --- */

/* XapiInitProcess (0x1d8259) — XBE naked draft (batch 353). */
#if defined(__clang__)
static void (*const b1d8259_c1d7749)(void) = (void *)FUN_001d7749;
static void (*const b1d8259_c1d5842)(void) = (void *)FUN_001d5842;
static int __stdcall (*const b1d8259_c1d7d21)(void *object_name_field) = (void *)FUN_001d7d21;
static void (*const b1d8259_c1d819f)(void) = (void *)FUN_001d819f;
static void (*const b1d8259_c1d3c95)(void) = (void *)XMountUtilityDrive;
static void (*const b1d8259_c1d81f4)(void) = (void *)XapiBootToDash;
static void (*const b1d8259_c1d454b)(void) = (void *)FUN_001d454b;

__attribute__((naked, noinline))
void XapiInitProcess(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x30, %%esp\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "xorl %%esi, %%esi\n\t"
      "call *%[c1d7749]\n\t"
      "pushl $0xc\n\t"
      "popl %%ecx\n\t"
      "xorl %%eax, %%eax\n\t"
      "leal -0x30(%%ebp), %%edi\n\t"
      "rep stosl\n\t"
      "leal -0x30(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "movl $0x30, -0x30(%%ebp)\n\t"
      "pushl 0x10138\n\t"
      "pushl 0x10134\n\t"
      "pushl %%esi\n\t"
      "pushl $2\n\t"
      "popl %%edi\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d5842]\n\t"
      "cmpl %%esi, %%eax\n\t"
      "movl %%eax, 0x632a28\n\t"
      "jne .LXapiInitProcess_2\n\t"
      ".LXapiInitProcess_1:\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "incl %%ecx\n\t"
      "movl %%ecx, %%eax\n\t"
      "jmp .LXapiInitProcess_9\n\t"
      ".LXapiInitProcess_2:\n\t"
      "testb $8, 0x10124\n\t"
      "jne .LXapiInitProcess_6\n\t"
      "pushl $0x32fd70\n\t"
      "call *%[c1d7d21]\n\t"
      "testl %%eax, %%eax\n\t"
      "jl .LXapiInitProcess_4\n\t"
      "pushl $0x32fd68\n\t"
      "pushl $0x32fd60\n\t"
      "call *0x253220\n\t"
      "cmpl %%esi, %%eax\n\t"
      "jge .LXapiInitProcess_3\n\t"
      "cmpl $0xc0000035, %%eax\n\t"
      "jne .LXapiInitProcess_1\n\t"
      ".LXapiInitProcess_3:\n\t"
      "movl 0x10118, %%eax\n\t"
      "leal 0xc(%%eax), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl 0x8(%%eax)\n\t"
      "call *%[c1d819f]\n\t"
      "cmpl %%esi, %%eax\n\t"
      "jge .LXapiInitProcess_5\n\t"
      "cmpl $0xc000007f, %%eax\n\t"
      "jne .LXapiInitProcess_4\n\t"
      "pushl $0x54\n\t"
      "popl %%ecx\n\t"
      "pushl $0x10\n\t"
      "movl %%edi, %%eax\n\t"
      "popl %%esi\n\t"
      "jmp .LXapiInitProcess_9\n\t"
      ".LXapiInitProcess_4:\n\t"
      "movl %%edi, %%ecx\n\t"
      "jmp .LXapiInitProcess_8\n\t"
      ".LXapiInitProcess_5:\n\t"
      "movl 0x10124, %%eax\n\t"
      "testb $1, %%al\n\t"
      "je .LXapiInitProcess_7\n\t"
      "andl %%edi, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d3c95]\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LXapiInitProcess_7\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl $1\n\t"
      "call *%[c1d81f4]\n\t"
      "jmp .LXapiInitProcess_7\n\t"
      ".LXapiInitProcess_6:\n\t"
      "pushl $0x32fd68\n\t"
      "pushl $0x32fd60\n\t"
      "call *0x253220\n\t"
      "cmpl %%esi, %%eax\n\t"
      "jge .LXapiInitProcess_7\n\t"
      "cmpl $0xc0000035, %%eax\n\t"
      "jne .LXapiInitProcess_1\n\t"
      ".LXapiInitProcess_7:\n\t"
      "movl 0x10118, %%eax\n\t"
      "movl 0xa4(%%eax), %%esi\n\t"
      "call *%[c1d454b]\n\t"
      "cmpl %%eax, %%esi\n\t"
      "jae .LXapiInitProcess_10\n\t"
      "pushl $4\n\t"
      "popl %%ecx\n\t"
      ".LXapiInitProcess_8:\n\t"
      "xorl %%eax, %%eax\n\t"
      "incl %%eax\n\t"
      ".LXapiInitProcess_9:\n\t"
      "pushl %%esi\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d81f4]\n\t"
      ".LXapiInitProcess_10:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      :
      : [c1d7749] "m"(b1d8259_c1d7749), [c1d5842] "m"(b1d8259_c1d5842), [c1d7d21] "m"(b1d8259_c1d7d21), [c1d819f] "m"(b1d8259_c1d819f), [c1d3c95] "m"(b1d8259_c1d3c95), [c1d81f4] "m"(b1d8259_c1d81f4), [c1d454b] "m"(b1d8259_c1d454b)
      : "memory");
}
#else
#error "XapiInitProcess: clang naked draft required"
#endif


/* 0x1d8368 */
int XapiFormatFATVolume(void *device_path)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  /* cmp eax, edi -> jge 0x1d83ac */
  XapiSetLastNTError(0);
  /* cmp ebx, edi -> jge 0x1d83e2 */
  FUN_001d8750(0);
  /* cmp esi, edi -> jge 0x1d841e */
  /* relift: cmp dword ptr [ebp - 0xc], edi -> jae 0x1d84b1 */
  __alldiv();
  /* cmp eax, 0xfff0 -> jae 0x1d8479 */
  /* cmp eax, edi -> ja 0x1d84b1 */
  /* cmp eax, esi -> jb 0x1d84c6 */
  /* relift: cmp dword ptr [ebp - 0x10], edi -> jbe 0x1d84c6 */
  SetLastError(112);
  FUN_001d0bb9(ecx, ebx);
  /* test esi, esi -> jne 0x1d84e6 */
  LocalFree((void *)(uintptr_t)esi);
  LocalFree((void *)(uintptr_t)esi);
  /* relift: cmp dword ptr [ebp - 0x14], edi -> jl 0x1d8674 */
  XapiSetLastNTError(0);
  /* test eax, eax -> je 0x1d8697 */
  /* cmp eax, -1 -> je 0x1d8697 */
  /* relift: cmp esi, dword ptr [esp + 8] -> jb 0x1d868a */
  /* test eax, eax -> je 0x1d86b6 */
  /* cmp eax, -1 -> je 0x1d86b6 */
  /* relift: cmp esi, dword ptr [esp + 8] -> jb 0x1d86a9 */
  return 0;

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* _cinit (0x1d86c3) — XBE naked draft (batch 329). */
#if defined(__clang__)


__attribute__((naked, noinline))
void _cinit(void)
{
  __asm__ volatile(
      "movl 0x331010, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .L_cinit_1\n\t"
      "call *%%eax\n\t"
      ".L_cinit_1:\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl $0x2c84e0, %%eax\n\t"
      "movl $0x2c84ec, %%edi\n\t"
      "cmpl %%edi, %%eax\n\t"
      "movl %%eax, %%esi\n\t"
      "jae .L_cinit_4\n\t"
      ".L_cinit_2:\n\t"
      "movl (%%esi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .L_cinit_3\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .L_cinit_3\n\t"
      "call *%%eax\n\t"
      ".L_cinit_3:\n\t"
      "addl $4, %%esi\n\t"
      "cmpl %%edi, %%esi\n\t"
      "jb .L_cinit_2\n\t"
      ".L_cinit_4:\n\t"
      "movl $0x2c84d0, %%esi\n\t"
      "movl %%esi, %%eax\n\t"
      "movl $0x2c84dc, %%edi\n\t"
      "cmpl %%edi, %%eax\n\t"
      "jae .L_cinit_7\n\t"
      ".L_cinit_5:\n\t"
      "movl (%%esi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .L_cinit_6\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .L_cinit_6\n\t"
      "call *%%eax\n\t"
      ".L_cinit_6:\n\t"
      "addl $4, %%esi\n\t"
      "cmpl %%edi, %%esi\n\t"
      "jb .L_cinit_5\n\t"
      ".L_cinit_7:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "_cinit: clang naked draft required"
#endif


/* _rtinit (0x1d871b) — XBE naked draft (batch 357). */
#if defined(__clang__)


__attribute__((naked, noinline))
void _rtinit(void)
{
  __asm__ volatile(
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl $0x2c84c0, %%eax\n\t"
      "movl $0x2c84cc, %%edi\n\t"
      "cmpl %%edi, %%eax\n\t"
      "movl %%eax, %%esi\n\t"
      "jae .L_rtinit_3\n\t"
      ".L_rtinit_1:\n\t"
      "movl (%%esi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .L_rtinit_2\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .L_rtinit_2\n\t"
      "call *%%eax\n\t"
      ".L_rtinit_2:\n\t"
      "addl $4, %%esi\n\t"
      "cmpl %%edi, %%esi\n\t"
      "jb .L_rtinit_1\n\t"
      ".L_rtinit_3:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "_rtinit: clang naked draft required"
#endif


/* 0x1d8750 */
unsigned int FUN_001d8750(unsigned int val)
{
  /* relift: no calls detected — manual review */
  (void)0;
  return 0;
}

/* 0x1d8766 */
int xCompareStringA(int flags, const char *a, int a_len, const char *b, int b_len)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int ebp = 0;

  /* relift: cmp dword ptr [ebp + 0x14], esi -> je 0x1d88df */
  /* relift: cmp dword ptr [ebp + 0x10], -1 -> jl 0x1d88df */
  /* relift: cmp dword ptr [ebp + 0x18], -1 -> jl 0x1d88df */
  /* relift: cmp dword ptr [ebp + 0x10], esi -> je 0x1d88c0 */
  /* test dl, dl -> je 0x1d88a9 */
  /* test (char)ebx, (char)ebx -> je 0x1d88b6 */
  /* test ecx, esi -> je 0x1d883e */
  /* test ecx, edx -> je 0x1d8825 */
  /* cmp esi, edx -> jae 0x1d881a */
  /* relift: cmp dword ptr [ebp - 4], 0 -> jne 0x1d8832 */
  /* test ecx, edx -> je 0x1d8855 */
  /* relift: cmp dword ptr [ebp - 4], 0 -> jne 0x1d884f */
  /* relift: cmp dword ptr [ebp + 8], 0 -> je 0x1d8868 */
  /* test ecx, esi -> jne 0x1d8836 */
  /* test ecx, edx -> jne 0x1d8899 */
  /* relift: cmp dword ptr [ebp - 8], 0 -> je 0x1d888d */
  /* test ecx, esi -> je 0x1d8880 */
  /* test ecx, edx -> je 0x1d888d */
  /* cmp esi, edx -> jb 0x1d88b1 */
  /* relift: cmp byte ptr [eax], 0 -> je 0x1d88c5 */
  /* relift: cmp dword ptr [ebp + 0x10], esi -> jne 0x1d88d1 */
  /* relift: cmp dword ptr [ebp + 0x18], esi -> jne 0x1d88d1 */
  SetLastError(87);
  return 0;

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)ebp;
}

/* FUN_001d88ef (0x1d88ef) — XBE naked draft (batch 304). */
#if defined(__clang__)
static void __stdcall (*const b1d88ef_c1d2268)(unsigned int error) = (void *)SetLastError;

__attribute__((naked, noinline))
void FUN_001d88ef(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "movl %%ecx, %%eax\n\t"
      "shrl $0xc, %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl %%ecx, %%edx\n\t"
      "xorl %%esi, %%esi\n\t"
      "notl %%eax\n\t"
      "andl $1, %%edx\n\t"
      "andl $4, %%ecx\n\t"
      "andl $1, %%eax\n\t"
      "cmpl %%esi, 0xc(%%ebp)\n\t"
      "pushl %%edi\n\t"
      "movl %%esi, -0x4(%%ebp)\n\t"
      "movl %%edx, -0x8(%%ebp)\n\t"
      "movl %%ecx, 0x8(%%ebp)\n\t"
      "je .LFUN_001d88ef_23\n\t"
      "cmpl %%esi, 0x14(%%ebp)\n\t"
      "je .LFUN_001d88ef_23\n\t"
      "cmpl $-1, 0x10(%%ebp)\n\t"
      "jl .LFUN_001d88ef_23\n\t"
      "cmpl $-1, 0x18(%%ebp)\n\t"
      "jl .LFUN_001d88ef_23\n\t"
      "cmpl %%esi, 0x10(%%ebp)\n\t"
      ".LFUN_001d88ef_1:\n\t"
      "je .LFUN_001d88ef_20\n\t"
      "cmpl %%esi, 0x18(%%ebp)\n\t"
      "movl $0x10000, %%ecx\n\t"
      "je .LFUN_001d88ef_19\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "cmpw %%si, (%%edx)\n\t"
      "je .LFUN_001d88ef_16\n\t"
      "movl 0x14(%%ebp), %%edx\n\t"
      "cmpw %%si, (%%edx)\n\t"
      "je .LFUN_001d88ef_18\n\t"
      "testl %%eax, %%eax\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "movl 0x14(%%ebp), %%esi\n\t"
      "movzbw (%%edx), %%dx\n\t"
      "movzbw (%%esi), %%bx\n\t"
      "movzwl %%dx, %%edi\n\t"
      "movl 0x32fd98(,%%edi,4), %%esi\n\t"
      "movzwl %%bx, %%ebx\n\t"
      "movl 0x32fd98(,%%ebx,4), %%edx\n\t"
      "je .LFUN_001d88ef_8\n\t"
      "testl %%esi, %%ecx\n\t"
      "je .LFUN_001d88ef_6\n\t"
      "testl %%edx, %%ecx\n\t"
      "je .LFUN_001d88ef_3\n\t"
      "cmpl %%edx, %%esi\n\t"
      "jae .LFUN_001d88ef_2\n\t"
      "movl $7, -0x4(%%ebp)\n\t"
      "jmp .LFUN_001d88ef_13\n\t"
      ".LFUN_001d88ef_2:\n\t"
      "jbe .LFUN_001d88ef_13\n\t"
      "movl $0xb, -0x4(%%ebp)\n\t"
      "jmp .LFUN_001d88ef_13\n\t"
      ".LFUN_001d88ef_3:\n\t"
      "cmpl $0, -0x4(%%ebp)\n\t"
      "jne .LFUN_001d88ef_4\n\t"
      "movl $4, -0x4(%%ebp)\n\t"
      ".LFUN_001d88ef_4:\n\t"
      "orl $1, -0x4(%%ebp)\n\t"
      ".LFUN_001d88ef_5:\n\t"
      "addl $2, 0xc(%%ebp)\n\t"
      "decl 0x10(%%ebp)\n\t"
      "jmp .LFUN_001d88ef_15\n\t"
      ".LFUN_001d88ef_6:\n\t"
      "testl %%edx, %%ecx\n\t"
      "je .LFUN_001d88ef_8\n\t"
      "cmpl $0, -0x4(%%ebp)\n\t"
      "jne .LFUN_001d88ef_7\n\t"
      "movl $8, -0x4(%%ebp)\n\t"
      ".LFUN_001d88ef_7:\n\t"
      "orl $2, -0x4(%%ebp)\n\t"
      "jmp .LFUN_001d88ef_9\n\t"
      ".LFUN_001d88ef_8:\n\t"
      "cmpl $0, 0x8(%%ebp)\n\t"
      "je .LFUN_001d88ef_10\n\t"
      "movl $0x20000, %%ecx\n\t"
      "testl %%esi, %%ecx\n\t"
      "jne .LFUN_001d88ef_5\n\t"
      "testl %%edx, %%ecx\n\t"
      "je .LFUN_001d88ef_10\n\t"
      ".LFUN_001d88ef_9:\n\t"
      "addl $2, 0x14(%%ebp)\n\t"
      "jmp .LFUN_001d88ef_14\n\t"
      ".LFUN_001d88ef_10:\n\t"
      "cmpl $0, -0x8(%%ebp)\n\t"
      "je .LFUN_001d88ef_12\n\t"
      "movl $0x100000, %%ecx\n\t"
      "testl %%esi, %%ecx\n\t"
      "je .LFUN_001d88ef_11\n\t"
      "leal 0x20(%%edi), %%esi\n\t"
      "orl $0x80000, %%esi\n\t"
      ".LFUN_001d88ef_11:\n\t"
      "testl %%edx, %%ecx\n\t"
      "je .LFUN_001d88ef_12\n\t"
      "leal 0x20(%%ebx), %%edx\n\t"
      "orl $0x80000, %%edx\n\t"
      ".LFUN_001d88ef_12:\n\t"
      "cmpl %%edx, %%esi\n\t"
      "jb .LFUN_001d88ef_17\n\t"
      "ja .LFUN_001d88ef_18\n\t"
      ".LFUN_001d88ef_13:\n\t"
      "addl $2, 0xc(%%ebp)\n\t"
      "addl $2, 0x14(%%ebp)\n\t"
      "decl 0x10(%%ebp)\n\t"
      ".LFUN_001d88ef_14:\n\t"
      "decl 0x18(%%ebp)\n\t"
      ".LFUN_001d88ef_15:\n\t"
      "xorl %%esi, %%esi\n\t"
      "cmpl %%esi, 0x10(%%ebp)\n\t"
      "jmp .LFUN_001d88ef_1\n\t"
      ".LFUN_001d88ef_16:\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "cmpw %%si, (%%eax)\n\t"
      "je .LFUN_001d88ef_21\n\t"
      ".LFUN_001d88ef_17:\n\t"
      "xorl %%eax, %%eax\n\t"
      "incl %%eax\n\t"
      "jmp .LFUN_001d88ef_24\n\t"
      ".LFUN_001d88ef_18:\n\t"
      "pushl $3\n\t"
      "popl %%eax\n\t"
      "jmp .LFUN_001d88ef_24\n\t"
      ".LFUN_001d88ef_19:\n\t"
      "cmpl %%esi, 0x10(%%ebp)\n\t"
      "jne .LFUN_001d88ef_22\n\t"
      ".LFUN_001d88ef_20:\n\t"
      "cmpl %%esi, 0x18(%%ebp)\n\t"
      "jne .LFUN_001d88ef_22\n\t"
      ".LFUN_001d88ef_21:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movl 0x3301c8(,%%eax,4), %%eax\n\t"
      "jmp .LFUN_001d88ef_24\n\t"
      ".LFUN_001d88ef_22:\n\t"
      "xorl %%eax, %%eax\n\t"
      "cmpl %%esi, 0x10(%%ebp)\n\t"
      "sete %%al\n\t"
      "leal 0x1(%%eax,%%eax,1), %%eax\n\t"
      "jmp .LFUN_001d88ef_24\n\t"
      ".LFUN_001d88ef_23:\n\t"
      "pushl $0x57\n\t"
      "call *%[c1d2268]\n\t"
      "xorl %%eax, %%eax\n\t"
      ".LFUN_001d88ef_24:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      :
      : [c1d2268] "m"(b1d88ef_c1d2268)
      : "memory");
}
#else
#error "FUN_001d88ef: clang naked draft required"
#endif


/* FUN_001d8a88 (0x1d8a88) — XBE naked draft (batch 341). */
#if defined(__clang__)
static void __stdcall (*const b1d8a88_c1d2268)(unsigned int error) = (void *)SetLastError;

__attribute__((naked, noinline))
void FUN_001d8a88(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x10, %%esp\n\t"
      "pushl %%ebx\n\t"
      "movl 0x2530e4, %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl 0x8(%%ebp)\n\t"
      "leal -0x10(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%%ebx\n\t"
      "movl 0x1011c, %%esi\n\t"
      "movl 0x10120, %%edi\n\t"
      "imull $0x38, %%esi, %%esi\n\t"
      "addl %%edi, %%esi\n\t"
      "jmp .LFUN_001d8a88_2\n\t"
      ".LFUN_001d8a88_1:\n\t"
      "pushl 0x14(%%edi)\n\t"
      "leal -0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%%ebx\n\t"
      "pushl $1\n\t"
      "leal -0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x10(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *0x253290\n\t"
      "testb %%al, %%al\n\t"
      ".byte 0x75, 0x1b\n\t"
      "addl $0x38, %%edi\n\t"
      ".LFUN_001d8a88_2:\n\t"
      "cmpl %%esi, %%edi\n\t"
      "jb .LFUN_001d8a88_1\n\t"
      "pushl $0x490\n\t"
      "call *%[c1d2268]\n\t"
      "orl $0xffffffff, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      :
      : [c1d2268] "m"(b1d8a88_c1d2268)
      : "memory");
}
#else
#error "FUN_001d8a88: clang naked draft required"
#endif


/* FUN_001d8aef (0x1d8aef) — XBE naked draft (batch 383). */
#if defined(__clang__)
static void __stdcall (*const b1d8aef_c1d2296)(int status) = (void *)XapiSetLastNTError;

__attribute__((naked, noinline))
void FUN_001d8aef(void)
{
  __asm__ volatile(
      "pushl %%esi\n\t"
      "movl 0x8(%%esp), %%esi\n\t"
      "pushl %%esi\n\t"
      "call *0x253294\n\t"
      "testl %%eax, %%eax\n\t"
      "jge .LFUN_001d8aef_1\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d2296]\n\t"
      "xorl %%eax, %%eax\n\t"
      "jmp .LFUN_001d8aef_2\n\t"
      ".LFUN_001d8aef_1:\n\t"
      "movl 0x4(%%esi), %%eax\n\t"
      ".LFUN_001d8aef_2:\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      :
      : [c1d2296] "m"(b1d8aef_c1d2296)
      : "memory");
}
#else
#error "FUN_001d8aef: clang naked draft required"
#endif


/* FUN_001d8b10 (0x1d8b10) — XBE naked draft (batch 372). */
#if defined(__clang__)
static void __stdcall (*const b1d8b10_c1d2296)(int status) = (void *)XapiSetLastNTError;

__attribute__((naked, noinline))
void FUN_001d8b10(void)
{
  __asm__ volatile(
      "pushl 0x4(%%esp)\n\t"
      "call *0x253298\n\t"
      "testl %%eax, %%eax\n\t"
      "jge .LFUN_001d8b10_1\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d2296]\n\t"
      "xorl %%eax, %%eax\n\t"
      "jmp .LFUN_001d8b10_2\n\t"
      ".LFUN_001d8b10_1:\n\t"
      "xorl %%eax, %%eax\n\t"
      "incl %%eax\n\t"
      ".LFUN_001d8b10_2:\n\t"
      "ret\n\t"
      :
      : [c1d2296] "m"(b1d8b10_c1d2296)
      : "memory");
}
#else
#error "FUN_001d8b10: clang naked draft required"
#endif


/* XGetSectionSize (0x1d8b64) — readable C lift. */
unsigned int __stdcall XGetSectionSize(void *section)
{
  return *(unsigned int *)((char *)section + 8);
}

/* XNetGetEthernetLinkStatus (0x1d8b76) — XBE naked draft (batch 327). */
#if defined(__clang__)
static void (*const b1d8b76_c1d0362)(void) = FUN_001d0362;

__attribute__((naked, noinline))
uint32_t XNetGetEthernetLinkStatus(void)
{
  __asm__ volatile(
      "pushl %%esi\n\t"
      "xorl %%esi, %%esi\n\t"
      ".LXNetGetEthernetLinkStatus_1:\n\t"
      "movl $0, %%eax\n\t"
      "movl $0x4ee4b4, %%ecx\n\t"
      "movl $1, %%edx\n\t"
      ".byte 0x0f, 0xb1, 0x11\n\t"
      "cmpl %%esi, %%eax\n\t"
      "je .LXNetGetEthernetLinkStatus_2\n\t"
      "pushl %%esi\n\t"
      "call *%[c1d0362]\n\t"
      "jmp .LXNetGetEthernetLinkStatus_1\n\t"
      ".LXNetGetEthernetLinkStatus_2:\n\t"
      "cmpl %%esi, 0x4ee4b0\n\t"
      "jne .LXNetGetEthernetLinkStatus_3\n\t"
      "pushl %%esi\n\t"
      "pushl %%esi\n\t"
      "call *0x2532e4\n\t"
      ".LXNetGetEthernetLinkStatus_3:\n\t"
      "pushl %%esi\n\t"
      "movl %%esi, 0x4ee4b4\n\t"
      "call *0x2532e0\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      :
      : [c1d0362] "m"(b1d8b76_c1d0362)
      : "memory");
}
#else
#error "XNetGetEthernetLinkStatus: clang naked draft required"
#endif


/* 0x1d8df8 */
void XcSHAUpdate(int a, int b, int c)
{
  if (a == 0 && b == 0 && c == 0) {
    return;
  }
  (void)a;
  (void)b;
  (void)c;
}

/* 0x1d8dfe */
void XcSHAInit(int ctx)
{
  if (ctx == 0) {
    return;
  }
  (void)ctx;
}

/* 0x1d8e04 */
void XcSHAFinal(int a, int b)
{
  if (a == 0 && b == 0) {
    return;
  }
  (void)a;
  (void)b;
}

/* 0x1d8e0a */
void ExQueryNonVolatileSetting(int a, int b, int c, int d)
{
  (void)a;
  (void)b;
  (void)c;
  (void)d;
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* relift: FUN_001d8b2e(0, 0); */
  /* relift: FUN_001d8b49(0, 0); */
  /* test eax, eax -> jge 0x1d8ffc */
  /* mem[0x003314a0] = eax */
  /* mem[0x003314a4] = 0x1dded4 */
  /* mem[0x003314a8] = 0x1ddf39 */
  /* mem[0x003314ac] = 0x1dde7c */
  /* mem[0x003314b0] = 0x1ddf1f */
  /* mem[0x003314b4] = eax */
  /* mem[0x004fc000] = ecx */
  FUN_001d9011();
  FUN_001de27a();
  /* test eax, eax -> je 0x1d90c7 */
  /* test edx, 0x7fffffff -> jne 0x1d908b */
  /* test eax, eax -> je 0x1d90ef */
  FUN_001de452();
  __flsbuf();
  FUN_001de452();
  FUN_001de452();
  __flsbuf();
  /* test esi, esi -> je 0x1d91ee */
  /* cmp edi, ecx -> jbe 0x1d925a */

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}
