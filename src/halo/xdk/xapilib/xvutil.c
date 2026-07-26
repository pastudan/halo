/* kb object stubs -> xdk/xapilib/xvutil.c */

/* --- XAPILIB:xvutil.obj batch drafts (2026-07-26) --- */

/* 0x1d04f1 */
void FUN_001d04f1(void)
{
  int eax = 0;
  int ebp = 0;

  FUN_001d4464();
  /* test eax, eax -> jne 0x1d0518 */
  /* relift: test byte ptr [ebp - 4], 2 -> je 0x1d0518 */

  (void)eax;
  (void)ebp;
}

/* 0x1d051d */
void GetLocalTime(void *system_time)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x1d0581 */
int FUN_001d0581(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
  return 0;
}

/* 0x1d0589 */
void FUN_001d0589(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x1d05f4 */
bool SystemTimeToFileTime(void *system_time, void *file_time)
{
  int eax = 0;

  /* test (char)eax, (char)eax -> jne 0x1d0654 */
  XapiSetLastNTError(0xc000000d);
  return 0;

  (void)eax;
}

/* 0x1d0669 */
void FUN_001d0669(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* FUN_001d06a0 (0x1d06a0) — XBE naked draft (batch 302). */
#if defined(__clang__)
static void (*const b1d06a0_c1d0589)(void) = FUN_001d0589;
static bool __stdcall (*const b1d06a0_c1d05f4)(void *system_time, void *file_time) = (void *)SystemTimeToFileTime;

__attribute__((naked, noinline))
void FUN_001d06a0(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x4c, %%esp\n\t"
      "pushl %%ebx\n\t"
      "movl 0x10(%%ebp), %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "leal -0x38(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "call *%[c1d0589]\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "cmpw $0, (%%esi)\n\t"
      "je .LFUN_001d06a0_2\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "pushl %%edi\n\t"
      "pushl %%esi\n\t"
      "call *%[c1d05f4]\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_001d06a0_7\n\t"
      "movl 0x4(%%edi), %%eax\n\t"
      "cmpl 0x4(%%ebx), %%eax\n\t"
      "jg .LFUN_001d06a0_1\n\t"
      "jl .LFUN_001d06a0_7\n\t"
      "movl (%%edi), %%eax\n\t"
      "cmpl (%%ebx), %%eax\n\t"
      "jb .LFUN_001d06a0_7\n\t"
      ".LFUN_001d06a0_1:\n\t"
      "movb $1, %%al\n\t"
      "jmp .LFUN_001d06a0_8\n\t"
      ".LFUN_001d06a0_2:\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x6(%%esi), %%ax\n\t"
      "cmpw $5, %%ax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "jg .LFUN_001d06a0_7\n\t"
      "testw %%ax, %%ax\n\t"
      "je .LFUN_001d06a0_7\n\t"
      "andb $0, 0xb(%%ebp)\n\t"
      "xorl %%edi, %%edi\n\t"
      "movw 0x4(%%esi), %%di\n\t"
      "xorl %%eax, %%eax\n\t"
      "cmpb $0, 0x14(%%ebp)\n\t"
      "movw 0x2(%%esi), %%ax\n\t"
      "movl %%edi, -0xc(%%ebp)\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "jne .LFUN_001d06a0_4\n\t"
      "movzwl -0x36(%%ebp), %%ecx\n\t"
      "movswl %%ax, %%edx\n\t"
      "cmpl %%ecx, %%edx\n\t"
      "movl -0x38(%%ebp), %%ecx\n\t"
      "jge .LFUN_001d06a0_3\n\t"
      "incl %%ecx\n\t"
      "jmp .LFUN_001d06a0_5\n\t"
      ".LFUN_001d06a0_3:\n\t"
      "movl %%ecx, 0x14(%%ebp)\n\t"
      "jg .LFUN_001d06a0_6\n\t"
      "movb $1, 0xb(%%ebp)\n\t"
      "jmp .LFUN_001d06a0_6\n\t"
      ".LFUN_001d06a0_4:\n\t"
      "movl -0x38(%%ebp), %%ecx\n\t"
      ".LFUN_001d06a0_5:\n\t"
      "movl %%ecx, 0x14(%%ebp)\n\t"
      ".LFUN_001d06a0_6:\n\t"
      "movw 0x14(%%ebp), %%cx\n\t"
      "movl 0x253144, %%ebx\n\t"
      "andw $0, -0x1a(%%ebp)\n\t"
      "movw %%ax, -0x26(%%ebp)\n\t"
      "movw 0x8(%%esi), %%ax\n\t"
      "movw %%ax, -0x22(%%ebp)\n\t"
      "movw 0xa(%%esi), %%ax\n\t"
      "movw %%ax, -0x20(%%ebp)\n\t"
      "movw 0xc(%%esi), %%ax\n\t"
      "movw %%ax, -0x1e(%%ebp)\n\t"
      "movw 0xe(%%esi), %%ax\n\t"
      "movw %%ax, -0x1c(%%ebp)\n\t"
      "leal -0x18(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x28(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movw %%cx, -0x28(%%ebp)\n\t"
      "movw $1, -0x24(%%ebp)\n\t"
      "call *%%ebx\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_001d06a0_10\n\t"
      ".LFUN_001d06a0_7:\n\t"
      "xorb %%al, %%al\n\t"
      ".LFUN_001d06a0_8:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      ".LFUN_001d06a0_9:\n\t"
      "movl -0xc(%%ebp), %%edi\n\t"
      ".LFUN_001d06a0_10:\n\t"
      "leal -0x4c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x18(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *0x253138\n\t"
      "movl -0x3e(%%ebp), %%eax\n\t"
      "cmpw %%di, %%ax\n\t"
      "jle .LFUN_001d06a0_11\n\t"
      "subl %%eax, %%edi\n\t"
      "addl $7, %%edi\n\t"
      "jmp .LFUN_001d06a0_12\n\t"
      ".LFUN_001d06a0_11:\n\t"
      "jge .LFUN_001d06a0_13\n\t"
      "subl %%eax, %%edi\n\t"
      ".LFUN_001d06a0_12:\n\t"
      "addw %%di, -0x24(%%ebp)\n\t"
      ".LFUN_001d06a0_13:\n\t"
      "movl -0x24(%%ebp), %%edi\n\t"
      "xorl %%eax, %%eax\n\t"
      "incl %%eax\n\t"
      "cmpw %%ax, -0x8(%%ebp)\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "jle .LFUN_001d06a0_15\n\t"
      ".LFUN_001d06a0_14:\n\t"
      "addw $7, -0x24(%%ebp)\n\t"
      "leal -0x18(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x28(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%%ebx\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001d06a0_15\n\t"
      "leal -0x4c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x18(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *0x253138\n\t"
      "incl -0x4(%%ebp)\n\t"
      "movw -0x4(%%ebp), %%ax\n\t"
      "cmpw -0x8(%%ebp), %%ax\n\t"
      "movl -0x48(%%ebp), %%edi\n\t"
      "jl .LFUN_001d06a0_14\n\t"
      ".LFUN_001d06a0_15:\n\t"
      "leal -0x18(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x28(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movw %%di, -0x24(%%ebp)\n\t"
      "call *%%ebx\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001d06a0_7\n\t"
      "cmpb $0, 0xb(%%ebp)\n\t"
      "movl -0x14(%%ebp), %%edx\n\t"
      "movl -0x18(%%ebp), %%edi\n\t"
      "je .LFUN_001d06a0_17\n\t"
      "movzwl -0x32(%%ebp), %%eax\n\t"
      "movswl -0x24(%%ebp), %%ecx\n\t"
      "cmpl %%eax, %%ecx\n\t"
      "jl .LFUN_001d06a0_16\n\t"
      "jne .LFUN_001d06a0_17\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "cmpl 0x4(%%eax), %%edx\n\t"
      "jg .LFUN_001d06a0_17\n\t"
      "jl .LFUN_001d06a0_16\n\t"
      "cmpl (%%eax), %%edi\n\t"
      "jae .LFUN_001d06a0_17\n\t"
      ".LFUN_001d06a0_16:\n\t"
      "andb $0, 0xb(%%ebp)\n\t"
      "incl 0x14(%%ebp)\n\t"
      "movw 0x14(%%ebp), %%ax\n\t"
      "andw $0, -0x1a(%%ebp)\n\t"
      "movw %%ax, -0x28(%%ebp)\n\t"
      "movw -0x10(%%ebp), %%ax\n\t"
      "movw %%ax, -0x26(%%ebp)\n\t"
      "movw 0x8(%%esi), %%ax\n\t"
      "movw %%ax, -0x22(%%ebp)\n\t"
      "movw 0xa(%%esi), %%ax\n\t"
      "movw %%ax, -0x20(%%ebp)\n\t"
      "movw 0xc(%%esi), %%ax\n\t"
      "movw %%ax, -0x1e(%%ebp)\n\t"
      "movw 0xe(%%esi), %%ax\n\t"
      "movw %%ax, -0x1c(%%ebp)\n\t"
      "leal -0x18(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x28(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movw $1, -0x24(%%ebp)\n\t"
      "call *%%ebx\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_001d06a0_9\n\t"
      "jmp .LFUN_001d06a0_7\n\t"
      ".LFUN_001d06a0_17:\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "movl %%edi, (%%eax)\n\t"
      "movl %%edx, 0x4(%%eax)\n\t"
      "jmp .LFUN_001d06a0_1\n\t"
      :
      : [c1d0589] "m"(b1d06a0_c1d0589), [c1d05f4] "m"(b1d06a0_c1d05f4)
      : "memory");
}
#else
#error "FUN_001d06a0: clang naked draft required"
#endif


/* 0x1d08aa */
void GetTimeZoneInformation(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int ebp = 0;

  FUN_001d0447();
  /* cmp eax, ebx -> je 0x1d08d3 */
  SetLastError(eax);
  /* relift: cmp word ptr [esi + 0x46], (int16_t)ebx -> je 0x1d09fd */
  /* relift: cmp word ptr [esi + 0x9a], (int16_t)ebx -> je 0x1d09fd */
  FUN_001d06a0();
  /* test (char)eax, (char)eax -> je 0x1d09fd */
  FUN_001d06a0();
  /* test (char)eax, (char)eax -> je 0x1d09fd */
  __allmul();
  __allmul();
  __allmul();
  /* cmp ebx, edx -> jg 0x1d09e0 */
  /* relift: cmp dword ptr [ebp - 0x18], eax -> jae 0x1d09e0 */
  /* relift: cmp dword ptr [ebp - 4], ebx -> jl 0x1d09db */
  /* relift: cmp ecx, dword ptr [ebp - 0x18] -> jb 0x1d09db */
  /* relift: cmp dword ptr [ebp - 4], edx -> jg 0x1d09db */
  /* cmp ecx, eax -> jb 0x1d09fa */
  /* relift: cmp dword ptr [ebp - 4], edx -> jl 0x1d09fa */
  /* cmp ecx, eax -> jb 0x1d09fa */
  /* relift: cmp dword ptr [ebp - 4], ebx -> jg 0x1d09fa */
  /* relift: cmp ecx, dword ptr [ebp - 0x18] -> jb 0x1d09db */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)ebp;
}

/* 0x1d0a06 */
void FUN_001d0a06(void)
{
  GetTimeZoneInformation();
  __allmul();
}

/* 0x1d0a5c */
void FUN_001d0a5c(void)
{
  FUN_001d0a06();
}

/* 0x1d0adb */
void FUN_001d0adb(void)
{
  FUN_001d0a06();
}

/* 0x1d0b06 */
void FUN_001d0b06(void)
{
  FUN_001d0a06();
}

/* 0x1d0b31 */
void FUN_001d0b31(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int ebp = 0;

  /* cmp edx, ecx -> jae 0x1d0b53 */
  /* test edx, edx -> jne 0x1d0b51 */
  /* relift: cmp dword ptr [ebp + 0xc], edx -> jbe 0x1d0b5b */
  FUN_001d5842();
  /* test esi, esi -> jne 0x1d0b79 */
  SetLastError(0);
  FUN_001d4e37();
  /* test eax, eax -> jne 0x1d0b90 */
  SetLastError(0);

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)ebp;
}

/* 0x1d0b9c */
void FUN_001d0b9c(void)
{
  FUN_001d6ca8();
}

/* 0x1d0bb3 */
void FUN_001d0bb3(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x1d0bb9 */
void * FUN_001d0bb9(unsigned int flags, unsigned int size)
{
  int eax = 0;

  FUN_001d5c66();
  /* test (char)eax, 0x40 -> je 0x1d0be3 */
  FUN_001d703b();
  return NULL;

  (void)eax;
}

/* 0x1d0c02 */
void FUN_001d0c02(void)
{
  FUN_001d52c4();
}

/* 0x1d0c16 */
void * LocalFree(void *ptr)
{
  FUN_001d6ca8();
  return NULL;
}

/* 0x1d0c48 */
void FUN_001d0c48(void)
{
  FUN_001d5c66();
}

/* 0x1d0c65 */
void FUN_001d0c65(void)
{
  int eax = 0;

  /* test (char)eax, 0x40 -> je 0x1d0c72 */
  FUN_001d703b();

  (void)eax;
}

/* 0x1d0c91 */
void FUN_001d0c91(void)
{
  int eax = 0;

  /* test eax, eax -> jl 0x1d0cb3 */
  XapiSetLastNTError(0);

  (void)eax;
}

/* 0x1d0cbf */
void FUN_001d0cbf(void)
{
  int eax = 0;
  int ebp = 0;

  /* relift: test byte ptr [ebp + 0x11], 0x80 -> je 0x1d0cd5 */
  /* relift: cmp dword ptr [ebp + 0xc], 0 -> je 0x1d0cd5 */
  /* test eax, eax -> jl 0x1d0cef */
  XapiSetLastNTError(0);

  (void)eax;
  (void)ebp;
}

/* 0x1d0cfb */
void FUN_001d0cfb(void)
{
  int eax = 0;

  /* test eax, eax -> jl 0x1d0d1c */
  XapiSetLastNTError(0);
  /* test eax, eax -> jl 0x1d0d3e */
  XapiSetLastNTError(0);
  FUN_001d0c91();
  FUN_001d0cbf();
  /* relift: tail-call FUN_001d0cfb(); */
  /* relift: FUN_001d0d27(0, 0, 0); */

  (void)eax;
}

/* 0x1d0da1 */
void xbox_query_global_memory_status(void *status)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x1d0df0 */
bool FUN_001d0df0(const char *path, unsigned int attributes)
{
  int eax = 0;
  int ebx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  /* test eax, eax -> jge 0x1d0e43 */
  XapiSetLastNTError(0);
  /* test esi, esi -> jl 0x1d0e88 */
  XapiSetLastNTError(0);
  /* test eax, eax -> jl 0x1d0ed4 */
  XapiSetLastNTError(0);
  /* test eax, eax -> jl 0x1d0f57 */
  XapiSetLastNTError(0);
  /* test eax, eax -> jge 0x1d0fb2 */
  /* test esi, esi -> jl 0x1d0feb */
  XapiSetLastNTError(0);
  /* test eax, eax -> jge 0x1d104c */
  XapiSetLastNTError(0);
  /* test esi, esi -> jl 0x1d107a */
  XapiSetLastNTError(0);
  /* relift: test word ptr [esp + 4], 0xfff -> je 0x1d1098 */
  /* test eax, eax -> jl 0x1d10a8 */
  XapiSetLastNTError(0);
  /* relift: test byte ptr [esi + 0x38], 0x10 -> je 0x1d1174 */
  FUN_001d10bd();
  /* relift: cmp dword ptr [esi + 0x2c], 0 -> jne 0x1d11a6 */
  /* cmp eax, ebx -> jae 0x1d1195 */
  /* relift: cmp dword ptr [edi], ebx -> jae 0x1d11a6 */
  /* relift: cmp dword ptr [ebp + 0x10], 0 -> jl 0x1d11a8 */
  /* relift: cmp dword ptr [edi], ebx -> jb 0x1d11c9 */
  /* relift: cmp dword ptr [ebp + 0x10], 0xc000000f -> jne 0x1d11e2 */
  return 0;

  (void)eax;
  (void)ebx;
  (void)esi;
  (void)edi;
  (void)ebp;
}
