/* kb object stubs -> xdk/xapilib/fileio.c */

/* --- XAPILIB:fileio.obj batch drafts (2026-07-26) --- */

/* 0x1d0e96 */
int file_get_full_attributes(const char *path)
{
  int eax = 0;

  /* test eax, eax -> jl 0x1d0ed4 */
  XapiSetLastNTError(0);
  return 0;

  (void)eax;
}

/* FUN_001d0ee1 (0x1d0ee1) — XBE naked draft (batch 329). */
#if defined(__clang__)
static void __stdcall (*const b1d0ee1_c1d2296)(int status) = (void *)XapiSetLastNTError;

__attribute__((naked, noinline))
void FUN_001d0ee1(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x4c, %%esp\n\t"
      "pushl 0x8(%%ebp)\n\t"
      "leal -0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *0x2530e4\n\t"
      "leal -0x8(%%ebp), %%eax\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "leal -0x4c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x14(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl $0xfffffffd, -0x14(%%ebp)\n\t"
      "movl $0x40, -0xc(%%ebp)\n\t"
      "call *0x253164\n\t"
      "testl %%eax, %%eax\n\t"
      "jl .LFUN_001d0ee1_1\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "movl -0x1c(%%ebp), %%ecx\n\t"
      "movl %%ecx, (%%eax)\n\t"
      "movl -0x4c(%%ebp), %%ecx\n\t"
      "movl %%ecx, 0x4(%%eax)\n\t"
      "movl -0x48(%%ebp), %%ecx\n\t"
      "movl %%ecx, 0x8(%%eax)\n\t"
      "movl -0x44(%%ebp), %%ecx\n\t"
      "movl %%ecx, 0xc(%%eax)\n\t"
      "movl -0x40(%%ebp), %%ecx\n\t"
      "movl %%ecx, 0x10(%%eax)\n\t"
      "movl -0x3c(%%ebp), %%ecx\n\t"
      "movl %%ecx, 0x14(%%eax)\n\t"
      "movl -0x38(%%ebp), %%ecx\n\t"
      "movl %%ecx, 0x18(%%eax)\n\t"
      "movl -0x20(%%ebp), %%ecx\n\t"
      "movl %%ecx, 0x1c(%%eax)\n\t"
      "movl -0x24(%%ebp), %%ecx\n\t"
      "movl %%ecx, 0x20(%%eax)\n\t"
      "xorl %%eax, %%eax\n\t"
      "incl %%eax\n\t"
      "jmp .LFUN_001d0ee1_2\n\t"
      ".LFUN_001d0ee1_1:\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d2296]\n\t"
      "xorl %%eax, %%eax\n\t"
      ".LFUN_001d0ee1_2:\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      :
      : [c1d2296] "m"(b1d0ee1_c1d2296)
      : "memory");
}
#else
#error "FUN_001d0ee1: clang naked draft required"
#endif


/* MoveFileA (0x1d0f63) — XBE naked draft (batch 327). */
#if defined(__clang__)
static void __stdcall (*const b1d0f63_c1d2296)(int status) = (void *)XapiSetLastNTError;

__attribute__((naked, noinline))
void MoveFileA(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x2c, %%esp\n\t"
      "pushl %%esi\n\t"
      "movl 0x2530e4, %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl 0x8(%%ebp)\n\t"
      "leal -0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%%esi\n\t"
      "pushl $-3\n\t"
      "popl %%edi\n\t"
      "pushl $0x4020\n\t"
      "leal -0x8(%%ebp), %%eax\n\t"
      "movl %%eax, -0x18(%%ebp)\n\t"
      "pushl $7\n\t"
      "leal -0x10(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x1c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x110000\n\t"
      "leal 0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl %%edi, -0x1c(%%ebp)\n\t"
      "movl $0x40, -0x14(%%ebp)\n\t"
      "call *0x253160\n\t"
      "testl %%eax, %%eax\n\t"
      "jge .LMoveFileA_1\n\t"
      "pushl %%eax\n\t"
      "jmp .LMoveFileA_3\n\t"
      ".LMoveFileA_1:\n\t"
      "pushl 0xc(%%ebp)\n\t"
      "andb $0, -0x2c(%%ebp)\n\t"
      "leal -0x24(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl %%edi, -0x28(%%ebp)\n\t"
      "call *%%esi\n\t"
      "pushl $0xa\n\t"
      "pushl $0x10\n\t"
      "leal -0x2c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x10(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl 0x8(%%ebp)\n\t"
      "call *0x25315c\n\t"
      "pushl 0x8(%%ebp)\n\t"
      "movl %%eax, %%esi\n\t"
      "call *0x253090\n\t"
      "testl %%esi, %%esi\n\t"
      "jl .LMoveFileA_2\n\t"
      "xorl %%eax, %%eax\n\t"
      "incl %%eax\n\t"
      "jmp .LMoveFileA_4\n\t"
      ".LMoveFileA_2:\n\t"
      "pushl %%esi\n\t"
      ".LMoveFileA_3:\n\t"
      "call *%[c1d2296]\n\t"
      "xorl %%eax, %%eax\n\t"
      ".LMoveFileA_4:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      :
      : [c1d2296] "m"(b1d0f63_c1d2296)
      : "memory");
}
#else
#error "MoveFileA: clang naked draft required"
#endif


/* 0x1d0ff9 */
bool DeleteFileA(const char *path)
{
  int eax = 0;
  int esi = 0;

  /* test eax, eax -> jge 0x1d104c */
  XapiSetLastNTError(0);
  /* test esi, esi -> jl 0x1d107a */
  XapiSetLastNTError(0);
  /* relift: test word ptr [esp + 4], 0xfff -> je 0x1d1098 */
  /* test eax, eax -> jl 0x1d10a8 */
  XapiSetLastNTError(0);
  return 0;

  (void)eax;
  (void)esi;
}

/* FUN_001d10bd (0x1d10bd) — XBE naked draft (batch 304). */
#if defined(__clang__)
static void (*const b1d10bd_c1d10bd)(void) = FUN_001d10bd;

__attribute__((naked, noinline))
void FUN_001d10bd(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x24, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x10(%%ebp), %%esi\n\t"
      "xorl %%eax, %%eax\n\t"
      "pushl %%edi\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "movb $1, -0x8(%%ebp)\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "movl $0xc351, %%ebx\n\t"
      ".LFUN_001d10bd_1:\n\t"
      "pushl -0x8(%%ebp)\n\t"
      "leal -0x18(%%ebp), %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl $1\n\t"
      "pushl $0x146\n\t"
      "pushl %%esi\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl 0x8(%%ebp)\n\t"
      "call *0x253170\n\t"
      "andb $0, -0x8(%%ebp)\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%eax, 0x10(%%ebp)\n\t"
      "jl .LFUN_001d10bd_5\n\t"
      "incl -0x4(%%ebp)\n\t"
      "testb $0x10, 0x38(%%esi)\n\t"
      "je .LFUN_001d10bd_2\n\t"
      "movl 0x3c(%%esi), %%eax\n\t"
      "andb $0, 0x40(%%eax,%%esi,1)\n\t"
      "leal 0x40(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x10(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *0x2530e4\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl %%eax, -0x24(%%ebp)\n\t"
      "pushl $0x4021\n\t"
      "leal -0x10(%%ebp), %%eax\n\t"
      "movl %%eax, -0x20(%%ebp)\n\t"
      "pushl $3\n\t"
      "leal -0x18(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x24(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x100001\n\t"
      "leal 0xc(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl $0x40, -0x1c(%%ebp)\n\t"
      "call *0x253160\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%eax, 0x10(%%ebp)\n\t"
      "jl .LFUN_001d10bd_3\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl 0xc(%%ebp)\n\t"
      "call *%[c1d10bd]\n\t"
      "pushl 0xc(%%ebp)\n\t"
      "movl %%eax, 0x10(%%ebp)\n\t"
      "call *0x253090\n\t"
      "jmp .LFUN_001d10bd_3\n\t"
      ".LFUN_001d10bd_2:\n\t"
      "cmpl $0, 0x2c(%%esi)\n\t"
      "jne .LFUN_001d10bd_4\n\t"
      "movl 0x28(%%esi), %%ecx\n\t"
      "movl %%ecx, %%eax\n\t"
      "andl $0x3fff, %%eax\n\t"
      "negl %%eax\n\t"
      "sbbl %%eax, %%eax\n\t"
      "negl %%eax\n\t"
      "shrl $0xe, %%ecx\n\t"
      "addl %%ecx, %%eax\n\t"
      "cmpl %%ebx, %%eax\n\t"
      "jae .LFUN_001d10bd_3\n\t"
      "addl %%eax, (%%edi)\n\t"
      ".LFUN_001d10bd_3:\n\t"
      "cmpl %%ebx, (%%edi)\n\t"
      "jae .LFUN_001d10bd_4\n\t"
      "cmpl $0, 0x10(%%ebp)\n\t"
      "jl .LFUN_001d10bd_5\n\t"
      "xorl %%eax, %%eax\n\t"
      "jmp .LFUN_001d10bd_1\n\t"
      ".LFUN_001d10bd_4:\n\t"
      "movl %%ebx, (%%edi)\n\t"
      ".LFUN_001d10bd_5:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "shll $6, %%eax\n\t"
      "movl %%eax, %%ecx\n\t"
      "andl $0x3fff, %%ecx\n\t"
      "negl %%ecx\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "negl %%ecx\n\t"
      "shrl $0xe, %%eax\n\t"
      "addl %%eax, %%ecx\n\t"
      "addl %%ecx, (%%edi)\n\t"
      "cmpl %%ebx, (%%edi)\n\t"
      "jb .LFUN_001d10bd_6\n\t"
      "movl %%ebx, (%%edi)\n\t"
      ".LFUN_001d10bd_6:\n\t"
      "cmpl $0x80000006, 0x10(%%ebp)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "je .LFUN_001d10bd_7\n\t"
      "cmpl $0xc000000f, 0x10(%%ebp)\n\t"
      "jne .LFUN_001d10bd_8\n\t"
      ".LFUN_001d10bd_7:\n\t"
      "andl $0, 0x10(%%ebp)\n\t"
      ".LFUN_001d10bd_8:\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      :
      : [c1d10bd] "m"(b1d10bd_c1d10bd)
      : "memory");
}
#else
#error "FUN_001d10bd: clang naked draft required"
#endif


/* FUN_001d11e9 (0x1d11e9) — XBE naked draft (batch 320). */
#if defined(__clang__)
static void (*const b1d11e9_c1d10bd)(void) = FUN_001d10bd;
static void __stdcall (*const b1d11e9_c1d2296)(int status) = (void *)XapiSetLastNTError;

__attribute__((naked, noinline))
void FUN_001d11e9(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x1a0, %%esp\n\t"
      "pushl %%esi\n\t"
      "pushl 0x8(%%ebp)\n\t"
      "leal -0x18(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *0x2530e4\n\t"
      "leal -0x18(%%ebp), %%eax\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "leal -0x58(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x10(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl $0xfffffffd, -0x10(%%ebp)\n\t"
      "movl $0x40, -0x8(%%ebp)\n\t"
      "call *0x253164\n\t"
      "movl %%eax, %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jl .LFUN_001d11e9_5\n\t"
      "testb $0x10, -0x28(%%ebp)\n\t"
      "je .LFUN_001d11e9_1\n\t"
      "andl $0, 0x8(%%ebp)\n\t"
      "pushl $0x4021\n\t"
      "pushl $3\n\t"
      "leal -0x20(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x10(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x100001\n\t"
      "leal -0x4(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *0x253160\n\t"
      "movl %%eax, %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jl .LFUN_001d11e9_5\n\t"
      "leal -0x1a0(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal 0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl -0x4(%%ebp)\n\t"
      "call *%[c1d10bd]\n\t"
      "pushl -0x4(%%ebp)\n\t"
      "movl %%eax, %%esi\n\t"
      "call *0x253090\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "jmp .LFUN_001d11e9_4\n\t"
      ".LFUN_001d11e9_1:\n\t"
      "cmpl $0, -0x2c(%%ebp)\n\t"
      "je .LFUN_001d11e9_2\n\t"
      "movl $0xc351, %%eax\n\t"
      "jmp .LFUN_001d11e9_3\n\t"
      ".LFUN_001d11e9_2:\n\t"
      "movl -0x30(%%ebp), %%ecx\n\t"
      "movl %%ecx, %%eax\n\t"
      "andl $0x3fff, %%eax\n\t"
      "negl %%eax\n\t"
      "sbbl %%eax, %%eax\n\t"
      "shrl $0xe, %%ecx\n\t"
      "negl %%eax\n\t"
      "addl %%ecx, %%eax\n\t"
      "movl $0xc351, %%ecx\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "movl %%eax, 0x8(%%ebp)\n\t"
      "jbe .LFUN_001d11e9_4\n\t"
      "movl %%ecx, %%eax\n\t"
      ".LFUN_001d11e9_3:\n\t"
      "movl %%eax, 0x8(%%ebp)\n\t"
      ".LFUN_001d11e9_4:\n\t"
      "testl %%esi, %%esi\n\t"
      "jge .LFUN_001d11e9_6\n\t"
      ".LFUN_001d11e9_5:\n\t"
      "pushl %%esi\n\t"
      "call *%[c1d2296]\n\t"
      "xorl %%eax, %%eax\n\t"
      ".LFUN_001d11e9_6:\n\t"
      "popl %%esi\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      :
      : [c1d10bd] "m"(b1d11e9_c1d10bd), [c1d2296] "m"(b1d11e9_c1d2296)
      : "memory");
}
#else
#error "FUN_001d11e9: clang naked draft required"
#endif


/* FUN_001d12c1 (0x1d12c1) — XBE naked draft (batch 321). */
#if defined(__clang__)
static void (*const b1d12c1_c1d1f10)(void) = FUN_001d1f10;
static bool __stdcall (*const b1d12c1_c1d0ff9)(const char *path) = (void *)DeleteFileA;
static bool (*const b1d12c1_c1d0df0)(const char *path, unsigned int attributes) = FUN_001d0df0;
static void __stdcall (*const b1d12c1_c1d2296)(int status) = (void *)XapiSetLastNTError;

__attribute__((naked, noinline))
void FUN_001d12c1(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x2c, %%esp\n\t"
      "pushl %%ebx\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x2530e4, %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "leal -0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%%esi\n\t"
      "pushl $-3\n\t"
      "popl %%edi\n\t"
      "pushl $0x4020\n\t"
      "leal -0x8(%%ebp), %%eax\n\t"
      "movl %%eax, -0x18(%%ebp)\n\t"
      "pushl $7\n\t"
      "leal -0x10(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x1c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x110000\n\t"
      "leal 0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl %%edi, -0x1c(%%ebp)\n\t"
      "movl $0x40, -0x14(%%ebp)\n\t"
      "call *0x253160\n\t"
      "testl %%eax, %%eax\n\t"
      "jge .LFUN_001d12c1_1\n\t"
      "pushl %%eax\n\t"
      "jmp .LFUN_001d12c1_5\n\t"
      ".LFUN_001d12c1_1:\n\t"
      "movb 0x18(%%ebp), %%al\n\t"
      "pushl 0xc(%%ebp)\n\t"
      "andb $1, %%al\n\t"
      "movb %%al, -0x2c(%%ebp)\n\t"
      "leal -0x24(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl %%edi, -0x28(%%ebp)\n\t"
      "call *%%esi\n\t"
      "pushl $0xa\n\t"
      "pushl $0x10\n\t"
      "leal -0x2c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x10(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl 0x8(%%ebp)\n\t"
      "call *0x25315c\n\t"
      "pushl 0x8(%%ebp)\n\t"
      "movl %%eax, %%esi\n\t"
      "call *0x253090\n\t"
      "testl %%esi, %%esi\n\t"
      "jl .LFUN_001d12c1_2\n\t"
      "xorl %%eax, %%eax\n\t"
      "incl %%eax\n\t"
      "jmp .LFUN_001d12c1_6\n\t"
      ".LFUN_001d12c1_2:\n\t"
      "cmpl $0xc00000d4, %%esi\n\t"
      "jne .LFUN_001d12c1_4\n\t"
      "testb $2, 0x18(%%ebp)\n\t"
      "je .LFUN_001d12c1_4\n\t"
      "xorl %%eax, %%eax\n\t"
      "cmpb %%al, -0x2c(%%ebp)\n\t"
      "sete %%al\n\t"
      "orl $4, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0\n\t"
      "pushl 0x14(%%ebp)\n\t"
      "pushl 0x10(%%ebp)\n\t"
      "pushl 0xc(%%ebp)\n\t"
      "pushl %%ebx\n\t"
      "call *%[c1d1f10]\n\t"
      "movl %%eax, %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_001d12c1_3\n\t"
      "pushl %%ebx\n\t"
      "call *%[c1d0ff9]\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_001d12c1_3\n\t"
      "pushl $0x80\n\t"
      "pushl %%ebx\n\t"
      "call *%[c1d0df0]\n\t"
      "pushl %%ebx\n\t"
      "call *%[c1d0ff9]\n\t"
      ".LFUN_001d12c1_3:\n\t"
      "movl %%esi, %%eax\n\t"
      "jmp .LFUN_001d12c1_6\n\t"
      ".LFUN_001d12c1_4:\n\t"
      "pushl %%esi\n\t"
      ".LFUN_001d12c1_5:\n\t"
      "call *%[c1d2296]\n\t"
      "xorl %%eax, %%eax\n\t"
      ".LFUN_001d12c1_6:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      :
      : [c1d1f10] "m"(b1d12c1_c1d1f10), [c1d0ff9] "m"(b1d12c1_c1d0ff9), [c1d0df0] "m"(b1d12c1_c1d0df0), [c1d2296] "m"(b1d12c1_c1d2296)
      : "memory");
}
#else
#error "FUN_001d12c1: clang naked draft required"
#endif


/* 0x1d13c9 */
int ReadFile(int handle, void *buffer, uint32_t size, uint32_t *bytes_read, void *overlapped)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;

  /* cmp edi, ebx -> je 0x1d13dd */
  /* cmp esi, ebx -> je 0x1d144c */
  /* cmp eax, ebx -> jl 0x1d1437 */
  /* cmp eax, edi -> je 0x1d1437 */
  /* cmp eax, ebx -> je 0x1d1432 */
  /* cmp eax, ecx -> jne 0x1d14a7 */
  /* cmp eax, ebx -> je 0x1d1449 */
  /* cmp eax, 0x103 -> jne 0x1d147c */
  /* cmp eax, ebx -> jl 0x1d1487 */
  /* cmp eax, ebx -> jl 0x1d1487 */
  /* cmp eax, 0xc0000011 -> jne 0x1d1492 */
  /* cmp ecx, 0x80000000 -> jne 0x1d14a7 */
  XapiSetLastNTError(0);
  return 0;

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)esi;
  (void)edi;
}

/* 0x1d14b6 */
int WriteFile(int handle, void *buffer, uint32_t size, uint32_t *bytes_written, void *overlapped)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* cmp edi, ebx -> je 0x1d14ca */
  /* cmp esi, ebx -> je 0x1d152d */
  /* cmp edx, ecx -> je 0x1d157d */
  /* cmp eax, edi -> je 0x1d157d */
  /* cmp eax, ebx -> je 0x1d1528 */
  /* cmp eax, 0x103 -> jne 0x1d155d */
  /* cmp eax, ebx -> jl 0x1d1568 */
  /* cmp eax, ebx -> jl 0x1d1568 */
  /* cmp ecx, 0x80000000 -> jne 0x1d157d */
  XapiSetLastNTError(0);
  return 0;

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x1d158c */
bool SetEndOfFile(int handle)
{
  int eax = 0;

  /* test eax, eax -> jge 0x1d15b5 */
  XapiSetLastNTError(0);
  /* test eax, eax -> jl 0x1d1603 */
  /* test eax, eax -> jl 0x1d1603 */
  XapiSetLastNTError(0);
  return 0;

  (void)eax;
}

/* 0x1d1610 */
unsigned int SetFilePointer(int handle, int distance, int *distance_high, unsigned int method)
{
  int eax = 0;
  int ebx = 0;
  int ebp = 0;

  /* test eax, eax -> jl 0x1d167c */
  /* test eax, eax -> jge 0x1d1687 */
  XapiSetLastNTError(0);
  /* relift: cmp dword ptr [ebp - 8], 0 -> jae 0x1d16ac */
  /* test ebx, ebx -> jne 0x1d16c0 */
  /* test eax, 0x7fffffff -> je 0x1d16c0 */
  SetLastError(87);
  /* test eax, eax -> jl 0x1d16f4 */
  /* test ebx, ebx -> je 0x1d16e2 */
  /* relift: cmp dword ptr [ebp - 8], -1 -> jne 0x1d16ef */
  SetLastError(0);
  XapiSetLastNTError(0);
  /* test ebx, ebx -> je 0x1d1703 */
  return 0;

  (void)eax;
  (void)ebx;
  (void)ebp;
}

/* FUN_001d170a (0x1d170a) — XBE naked draft (batch 322). */
#if defined(__clang__)
static void __stdcall (*const b1d170a_c1d2268)(unsigned int error) = (void *)SetLastError;
static void __stdcall (*const b1d170a_c1d2296)(int status) = (void *)XapiSetLastNTError;

__attribute__((naked, noinline))
void FUN_001d170a(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x48, %%esp\n\t"
      "movl 0x18(%%ebp), %%eax\n\t"
      "subl $0, %%eax\n\t"
      "je .LFUN_001d170a_2\n\t"
      "decl %%eax\n\t"
      "je .LFUN_001d170a_1\n\t"
      "decl %%eax\n\t"
      "jne .LFUN_001d170a_1\n\t"
      "pushl $0x22\n\t"
      "pushl $0x38\n\t"
      "leal -0x48(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x10(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl 0x8(%%ebp)\n\t"
      "call *0x253180\n\t"
      "testl %%eax, %%eax\n\t"
      "jl .LFUN_001d170a_7\n\t"
      "movl -0x20(%%ebp), %%ecx\n\t"
      "addl 0xc(%%ebp), %%ecx\n\t"
      "movl -0x1c(%%ebp), %%eax\n\t"
      "adcl 0x10(%%ebp), %%eax\n\t"
      "jmp .LFUN_001d170a_3\n\t"
      ".LFUN_001d170a_1:\n\t"
      "pushl $0xe\n\t"
      "pushl $8\n\t"
      "leal -0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x10(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl 0x8(%%ebp)\n\t"
      "call *0x253180\n\t"
      "testl %%eax, %%eax\n\t"
      "jl .LFUN_001d170a_7\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "addl %%eax, %%ecx\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "adcl %%edx, %%eax\n\t"
      "jmp .LFUN_001d170a_3\n\t"
      ".LFUN_001d170a_2:\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      ".LFUN_001d170a_3:\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "jg .LFUN_001d170a_5\n\t"
      "jl .LFUN_001d170a_4\n\t"
      "testl %%ecx, %%ecx\n\t"
      "jae .LFUN_001d170a_5\n\t"
      ".LFUN_001d170a_4:\n\t"
      "pushl $0x83\n\t"
      "call *%[c1d2268]\n\t"
      "jmp .LFUN_001d170a_8\n\t"
      ".LFUN_001d170a_5:\n\t"
      "pushl $0xe\n\t"
      "pushl $8\n\t"
      "leal -0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x10(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl 0x8(%%ebp)\n\t"
      "call *0x25315c\n\t"
      "testl %%eax, %%eax\n\t"
      "jl .LFUN_001d170a_7\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_001d170a_6\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movl %%ecx, (%%eax)\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movl %%ecx, 0x4(%%eax)\n\t"
      ".LFUN_001d170a_6:\n\t"
      "xorl %%eax, %%eax\n\t"
      "incl %%eax\n\t"
      "jmp .LFUN_001d170a_9\n\t"
      ".LFUN_001d170a_7:\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d2296]\n\t"
      ".LFUN_001d170a_8:\n\t"
      "xorl %%eax, %%eax\n\t"
      ".LFUN_001d170a_9:\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      :
      : [c1d2268] "m"(b1d170a_c1d2268), [c1d2296] "m"(b1d170a_c1d2296)
      : "memory");
}
#else
#error "FUN_001d170a: clang naked draft required"
#endif


/* FUN_001d17d2 (0x1d17d2) — XBE naked draft (batch 317). */
#if defined(__clang__)
static void __stdcall (*const b1d17d2_c1d2296)(int status) = (void *)XapiSetLastNTError;

__attribute__((naked, noinline))
void FUN_001d17d2(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "leal -0x70(%%esp), %%ebp\n\t"
      "subl $0x94, %%esp\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl $1\n\t"
      "pushl $0x18\n\t"
      "leal -0x24(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal 0x68(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl 0x78(%%ebp)\n\t"
      "call *0x253184\n\t"
      "movl $0xc0000000, %%esi\n\t"
      "movl %%eax, %%ecx\n\t"
      "andl %%esi, %%ecx\n\t"
      "cmpl %%esi, %%ecx\n\t"
      "je .LFUN_001d17d2_1\n\t"
      "movl -0x1c(%%ebp), %%eax\n\t"
      "movl 0x253180, %%edi\n\t"
      "pushl $6\n\t"
      "movl %%eax, 0x48(%%ebp)\n\t"
      "pushl $8\n\t"
      "leal 0x60(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal 0x68(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl 0x78(%%ebp)\n\t"
      "call *%%edi\n\t"
      "movl %%eax, %%ecx\n\t"
      "andl %%esi, %%ecx\n\t"
      "cmpl %%esi, %%ecx\n\t"
      "je .LFUN_001d17d2_1\n\t"
      "movl 0x64(%%ebp), %%eax\n\t"
      "movl %%eax, 0x58(%%ebp)\n\t"
      "movl 0x60(%%ebp), %%eax\n\t"
      "pushl $0x22\n\t"
      "movl %%eax, 0x5c(%%ebp)\n\t"
      "pushl $0x38\n\t"
      "leal -0xc(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal 0x68(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl 0x78(%%ebp)\n\t"
      "call *%%edi\n\t"
      "movl %%eax, %%ecx\n\t"
      "andl %%esi, %%ecx\n\t"
      "cmpl %%esi, %%ecx\n\t"
      "je .LFUN_001d17d2_1\n\t"
      "movl 0x24(%%ebp), %%eax\n\t"
      "movl %%eax, 0x2c(%%ebp)\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "andl $0, 0x54(%%ebp)\n\t"
      "movl 0x7c(%%ebp), %%edi\n\t"
      "movl %%eax, 0x30(%%ebp)\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movl %%eax, 0x34(%%ebp)\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movl %%eax, 0x38(%%ebp)\n\t"
      "movl (%%ebp), %%eax\n\t"
      "movl %%eax, 0x3c(%%ebp)\n\t"
      "movl 0x4(%%ebp), %%eax\n\t"
      "movl %%eax, 0x40(%%ebp)\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl %%eax, 0x44(%%ebp)\n\t"
      "movl 0x20(%%ebp), %%eax\n\t"
      "movl %%eax, 0x4c(%%ebp)\n\t"
      "movl 0x1c(%%ebp), %%eax\n\t"
      "movl %%eax, 0x50(%%ebp)\n\t"
      "pushl $0xd\n\t"
      "popl %%ecx\n\t"
      "leal 0x2c(%%ebp), %%esi\n\t"
      "xorl %%eax, %%eax\n\t"
      "rep movsl\n\t"
      "incl %%eax\n\t"
      "jmp .LFUN_001d17d2_2\n\t"
      ".LFUN_001d17d2_1:\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d2296]\n\t"
      "xorl %%eax, %%eax\n\t"
      ".LFUN_001d17d2_2:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "addl $0x70, %%ebp\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      :
      : [c1d2296] "m"(b1d17d2_c1d2296)
      : "memory");
}
#else
#error "FUN_001d17d2: clang naked draft required"
#endif


/* FUN_001d18aa (0x1d18aa) — XBE naked draft (batch 331). */
#if defined(__clang__)
static void __stdcall (*const b1d18aa_c1d2296)(int status) = (void *)XapiSetLastNTError;

__attribute__((naked, noinline))
void FUN_001d18aa(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x40, %%esp\n\t"
      "pushl $0x22\n\t"
      "pushl $0x38\n\t"
      "leal -0x40(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl 0x8(%%ebp)\n\t"
      "call *0x253180\n\t"
      "testl %%eax, %%eax\n\t"
      "jl .LFUN_001d18aa_4\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_001d18aa_1\n\t"
      "movl -0x40(%%ebp), %%ecx\n\t"
      "movl %%ecx, (%%eax)\n\t"
      "movl -0x3c(%%ebp), %%ecx\n\t"
      "movl %%ecx, 0x4(%%eax)\n\t"
      ".LFUN_001d18aa_1:\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_001d18aa_2\n\t"
      "movl -0x38(%%ebp), %%ecx\n\t"
      "movl %%ecx, (%%eax)\n\t"
      "movl -0x34(%%ebp), %%ecx\n\t"
      "movl %%ecx, 0x4(%%eax)\n\t"
      ".LFUN_001d18aa_2:\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_001d18aa_3\n\t"
      "movl -0x30(%%ebp), %%ecx\n\t"
      "movl %%ecx, (%%eax)\n\t"
      "movl -0x2c(%%ebp), %%ecx\n\t"
      "movl %%ecx, 0x4(%%eax)\n\t"
      ".LFUN_001d18aa_3:\n\t"
      "xorl %%eax, %%eax\n\t"
      "incl %%eax\n\t"
      "jmp .LFUN_001d18aa_5\n\t"
      ".LFUN_001d18aa_4:\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d2296]\n\t"
      "xorl %%eax, %%eax\n\t"
      ".LFUN_001d18aa_5:\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      :
      : [c1d2296] "m"(b1d18aa_c1d2296)
      : "memory");
}
#else
#error "FUN_001d18aa: clang naked draft required"
#endif


/* 0x1d1910 */
bool SetFileTime(int handle, void *creation_time, void *last_access_time, void *last_write_time)
{
  int eax = 0;

  /* test eax, eax -> je 0x1d1946 */
  /* test eax, eax -> je 0x1d1958 */
  /* test eax, eax -> jl 0x1d1976 */
  XapiSetLastNTError(0);
  return 0;

  (void)eax;
}

/* FUN_001d1982 (0x1d1982) — XBE naked draft (batch 369). */
#if defined(__clang__)
static void __stdcall (*const b1d1982_c1d2296)(int status) = (void *)XapiSetLastNTError;

__attribute__((naked, noinline))
void FUN_001d1982(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl 0x8(%%ebp)\n\t"
      "call *0x253188\n\t"
      "testl %%eax, %%eax\n\t"
      "jl .LFUN_001d1982_1\n\t"
      "xorl %%eax, %%eax\n\t"
      "incl %%eax\n\t"
      "jmp .LFUN_001d1982_2\n\t"
      ".LFUN_001d1982_1:\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d2296]\n\t"
      "xorl %%eax, %%eax\n\t"
      ".LFUN_001d1982_2:\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      :
      : [c1d2296] "m"(b1d1982_c1d2296)
      : "memory");
}
#else
#error "FUN_001d1982: clang naked draft required"
#endif


/* FUN_001d19a9 (0x1d19a9) — XBE naked draft (batch 351). */
#if defined(__clang__)
static void __stdcall (*const b1d19a9_c1d2296)(int status) = (void *)XapiSetLastNTError;

__attribute__((naked, noinline))
void FUN_001d19a9(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x40, %%esp\n\t"
      "pushl $0x22\n\t"
      "pushl $0x38\n\t"
      "leal -0x40(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl 0x8(%%ebp)\n\t"
      "call *0x253180\n\t"
      "testl %%eax, %%eax\n\t"
      "jge .LFUN_001d19a9_1\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d2296]\n\t"
      "xorl %%eax, %%eax\n\t"
      "jmp .LFUN_001d19a9_2\n\t"
      ".LFUN_001d19a9_1:\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "movl -0x18(%%ebp), %%ecx\n\t"
      "movl %%ecx, (%%eax)\n\t"
      "movl -0x14(%%ebp), %%ecx\n\t"
      "movl %%ecx, 0x4(%%eax)\n\t"
      "xorl %%eax, %%eax\n\t"
      "incl %%eax\n\t"
      ".LFUN_001d19a9_2:\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      :
      : [c1d2296] "m"(b1d19a9_c1d2296)
      : "memory");
}
#else
#error "FUN_001d19a9: clang naked draft required"
#endif


/* FUN_001d19e7 (0x1d19e7) — XBE naked draft (batch 341). */
#if defined(__clang__)
static void __stdcall (*const b1d19e7_c1d2296)(int status) = (void *)XapiSetLastNTError;

__attribute__((naked, noinline))
void FUN_001d19e7(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "movl 0x8(%%eax), %%ecx\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "movl 0xc(%%eax), %%ecx\n\t"
      "movl %%ecx, -0x4(%%ebp)\n\t"
      "leal -0x8(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl 0x10(%%ebp)\n\t"
      "pushl 0xc(%%ebp)\n\t"
      "pushl %%eax\n\t"
      "pushl 0x18(%%ebp)\n\t"
      "pushl 0x25318c\n\t"
      "pushl $0\n\t"
      "pushl 0x8(%%ebp)\n\t"
      "call *0x253178\n\t"
      "movl $0xc0000000, %%ecx\n\t"
      "movl %%eax, %%edx\n\t"
      "andl %%ecx, %%edx\n\t"
      "cmpl %%ecx, %%edx\n\t"
      "jne .LFUN_001d19e7_1\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d2296]\n\t"
      "xorl %%eax, %%eax\n\t"
      "jmp .LFUN_001d19e7_2\n\t"
      ".LFUN_001d19e7_1:\n\t"
      "xorl %%eax, %%eax\n\t"
      "incl %%eax\n\t"
      ".LFUN_001d19e7_2:\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      :
      : [c1d2296] "m"(b1d19e7_c1d2296)
      : "memory");
}
#else
#error "FUN_001d19e7: clang naked draft required"
#endif


/* FUN_001d1a38 (0x1d1a38) — XBE naked draft (batch 341). */
#if defined(__clang__)
static void __stdcall (*const b1d1a38_c1d2296)(int status) = (void *)XapiSetLastNTError;

__attribute__((naked, noinline))
void FUN_001d1a38(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "movl 0x8(%%eax), %%ecx\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "movl 0xc(%%eax), %%ecx\n\t"
      "movl %%ecx, -0x4(%%ebp)\n\t"
      "leal -0x8(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl 0x10(%%ebp)\n\t"
      "pushl 0xc(%%ebp)\n\t"
      "pushl %%eax\n\t"
      "pushl 0x18(%%ebp)\n\t"
      "pushl 0x25318c\n\t"
      "pushl $0\n\t"
      "pushl 0x8(%%ebp)\n\t"
      "call *0x25317c\n\t"
      "movl $0xc0000000, %%ecx\n\t"
      "movl %%eax, %%edx\n\t"
      "andl %%ecx, %%edx\n\t"
      "cmpl %%ecx, %%edx\n\t"
      "jne .LFUN_001d1a38_1\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d2296]\n\t"
      "xorl %%eax, %%eax\n\t"
      "jmp .LFUN_001d1a38_2\n\t"
      ".LFUN_001d1a38_1:\n\t"
      "xorl %%eax, %%eax\n\t"
      "incl %%eax\n\t"
      ".LFUN_001d1a38_2:\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      :
      : [c1d2296] "m"(b1d1a38_c1d2296)
      : "memory");
}
#else
#error "FUN_001d1a38: clang naked draft required"
#endif


/* FUN_001d1a89 (0x1d1a89) — XBE naked draft (batch 313). */
#if defined(__clang__)
static void __stdcall (*const b1d1a89_c1d2296)(int status) = (void *)XapiSetLastNTError;

__attribute__((naked, noinline))
void FUN_001d1a89(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl 0x1c(%%ebp)\n\t"
      "movl 0x24(%%ebp), %%esi\n\t"
      "pushl 0x18(%%ebp)\n\t"
      "movl %%ecx, %%eax\n\t"
      "pushl 0x14(%%ebp)\n\t"
      "andl $0xffff0000, %%eax\n\t"
      "pushl 0x10(%%ebp)\n\t"
      "cmpl $0x90000, %%eax\n\t"
      "setne %%al\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "pushl %%ecx\n\t"
      "je .LFUN_001d1a89_5\n\t"
      "cmpb %%bl, %%al\n\t"
      "movl 0x10(%%esi), %%eax\n\t"
      "movl $0x103, (%%esi)\n\t"
      "pushl %%esi\n\t"
      "movl %%eax, %%ecx\n\t"
      "je .LFUN_001d1a89_1\n\t"
      "andb $1, %%cl\n\t"
      "negb %%cl\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "notl %%ecx\n\t"
      "andl %%esi, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "pushl 0x8(%%ebp)\n\t"
      "call *0x253194\n\t"
      "jmp .LFUN_001d1a89_2\n\t"
      ".LFUN_001d1a89_1:\n\t"
      "andb $1, %%cl\n\t"
      "negb %%cl\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "notl %%ecx\n\t"
      "andl %%esi, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "pushl 0x8(%%ebp)\n\t"
      "call *0x253190\n\t"
      ".LFUN_001d1a89_2:\n\t"
      "movl $0xc0000000, %%ecx\n\t"
      "movl %%eax, %%edx\n\t"
      "andl %%ecx, %%edx\n\t"
      "cmpl %%ecx, %%edx\n\t"
      "je .LFUN_001d1a89_3\n\t"
      "movl 0x20(%%ebp), %%ecx\n\t"
      "cmpl %%ebx, %%ecx\n\t"
      "je .LFUN_001d1a89_3\n\t"
      "movl 0x4(%%esi), %%edx\n\t"
      "movl %%edx, (%%ecx)\n\t"
      ".LFUN_001d1a89_3:\n\t"
      "cmpl %%ebx, %%eax\n\t"
      "jl .LFUN_001d1a89_10\n\t"
      "cmpl $0x103, %%eax\n\t"
      "je .LFUN_001d1a89_10\n\t"
      ".LFUN_001d1a89_4:\n\t"
      "xorl %%eax, %%eax\n\t"
      "incl %%eax\n\t"
      "jmp .LFUN_001d1a89_11\n\t"
      ".LFUN_001d1a89_5:\n\t"
      "cmpb %%bl, %%al\n\t"
      "leal -0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ebx\n\t"
      "pushl 0x8(%%ebp)\n\t"
      "je .LFUN_001d1a89_6\n\t"
      "call *0x253194\n\t"
      "jmp .LFUN_001d1a89_7\n\t"
      ".LFUN_001d1a89_6:\n\t"
      "call *0x253190\n\t"
      ".LFUN_001d1a89_7:\n\t"
      "cmpl $0x103, %%eax\n\t"
      "jne .LFUN_001d1a89_8\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ebx\n\t"
      "pushl 0x8(%%ebp)\n\t"
      "call *0x253174\n\t"
      "cmpl %%ebx, %%eax\n\t"
      "jl .LFUN_001d1a89_9\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      ".LFUN_001d1a89_8:\n\t"
      "cmpl %%ebx, %%eax\n\t"
      "jl .LFUN_001d1a89_9\n\t"
      "movl 0x20(%%ebp), %%eax\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movl %%ecx, (%%eax)\n\t"
      "jmp .LFUN_001d1a89_4\n\t"
      ".LFUN_001d1a89_9:\n\t"
      "movl $0xc0000000, %%ecx\n\t"
      "movl %%eax, %%edx\n\t"
      "andl %%ecx, %%edx\n\t"
      "cmpl %%ecx, %%edx\n\t"
      "je .LFUN_001d1a89_10\n\t"
      "movl 0x20(%%ebp), %%ecx\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "movl %%edx, (%%ecx)\n\t"
      ".LFUN_001d1a89_10:\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d2296]\n\t"
      "xorl %%eax, %%eax\n\t"
      ".LFUN_001d1a89_11:\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      :
      : [c1d2296] "m"(b1d1a89_c1d2296)
      : "memory");
}
#else
#error "FUN_001d1a89: clang naked draft required"
#endif


/* FUN_001d1b87 (0x1d1b87) — XBE naked draft (batch 314). */
#if defined(__clang__)
static void __stdcall (*const b1d1b87_c1d2296)(int status) = (void *)XapiSetLastNTError;

__attribute__((naked, noinline))
void FUN_001d1b87(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x10, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x14(%%ebp), %%edi\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "cmpl %%ebx, %%edi\n\t"
      "je .LFUN_001d1b87_1\n\t"
      "movl %%ebx, (%%edi)\n\t"
      ".LFUN_001d1b87_1:\n\t"
      "movl 0x18(%%ebp), %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "je .LFUN_001d1b87_5\n\t"
      "movl 0x8(%%esi), %%eax\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "movl 0xc(%%esi), %%eax\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "movl 0x10(%%esi), %%eax\n\t"
      "leal -0x10(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl 0x10(%%ebp)\n\t"
      "movl %%eax, %%ecx\n\t"
      "pushl 0xc(%%ebp)\n\t"
      "andb $1, %%cl\n\t"
      "negb %%cl\n\t"
      "pushl %%esi\n\t"
      "movl $0x103, %%edi\n\t"
      "movl %%edi, (%%esi)\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "notl %%ecx\n\t"
      "andl %%esi, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "pushl 0x8(%%ebp)\n\t"
      "call *0x253198\n\t"
      "cmpl %%ebx, %%eax\n\t"
      "jl .LFUN_001d1b87_3\n\t"
      "cmpl %%edi, %%eax\n\t"
      "je .LFUN_001d1b87_3\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "cmpl %%ebx, %%eax\n\t"
      "je .LFUN_001d1b87_2\n\t"
      "movl 0x4(%%esi), %%ecx\n\t"
      "movl %%ecx, (%%eax)\n\t"
      ".LFUN_001d1b87_2:\n\t"
      "xorl %%eax, %%eax\n\t"
      "incl %%eax\n\t"
      "jmp .LFUN_001d1b87_11\n\t"
      ".LFUN_001d1b87_3:\n\t"
      "movl $0xc0000011, %%ecx\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jne .LFUN_001d1b87_9\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "cmpl %%ebx, %%eax\n\t"
      "je .LFUN_001d1b87_4\n\t"
      "movl %%ebx, (%%eax)\n\t"
      ".LFUN_001d1b87_4:\n\t"
      "pushl %%ecx\n\t"
      "jmp .LFUN_001d1b87_10\n\t"
      ".LFUN_001d1b87_5:\n\t"
      "pushl %%ebx\n\t"
      "pushl 0x10(%%ebp)\n\t"
      "leal -0x8(%%ebp), %%eax\n\t"
      "pushl 0xc(%%ebp)\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ebx\n\t"
      "pushl 0x8(%%ebp)\n\t"
      "call *0x253198\n\t"
      "cmpl $0x103, %%eax\n\t"
      "jne .LFUN_001d1b87_6\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ebx\n\t"
      "pushl 0x8(%%ebp)\n\t"
      "call *0x253174\n\t"
      "cmpl %%ebx, %%eax\n\t"
      "jl .LFUN_001d1b87_7\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      ".LFUN_001d1b87_6:\n\t"
      "cmpl %%ebx, %%eax\n\t"
      "jl .LFUN_001d1b87_7\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movl %%eax, (%%edi)\n\t"
      "jmp .LFUN_001d1b87_2\n\t"
      ".LFUN_001d1b87_7:\n\t"
      "cmpl $0xc0000011, %%eax\n\t"
      "jne .LFUN_001d1b87_8\n\t"
      "movl %%ebx, (%%edi)\n\t"
      "jmp .LFUN_001d1b87_2\n\t"
      ".LFUN_001d1b87_8:\n\t"
      "movl %%eax, %%ecx\n\t"
      "andl $0xc0000000, %%ecx\n\t"
      "cmpl $0x80000000, %%ecx\n\t"
      "jne .LFUN_001d1b87_9\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movl %%ecx, (%%edi)\n\t"
      ".LFUN_001d1b87_9:\n\t"
      "pushl %%eax\n\t"
      ".LFUN_001d1b87_10:\n\t"
      "call *%[c1d2296]\n\t"
      "xorl %%eax, %%eax\n\t"
      ".LFUN_001d1b87_11:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      :
      : [c1d2296] "m"(b1d1b87_c1d2296)
      : "memory");
}
#else
#error "FUN_001d1b87: clang naked draft required"
#endif


/* FUN_001d1c74 (0x1d1c74) — XBE naked draft (batch 316). */
#if defined(__clang__)
static void __stdcall (*const b1d1c74_c1d2296)(int status) = (void *)XapiSetLastNTError;

__attribute__((naked, noinline))
void FUN_001d1c74(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x10, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x14(%%ebp), %%edi\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "cmpl %%ebx, %%edi\n\t"
      "je .LFUN_001d1c74_1\n\t"
      "movl %%ebx, (%%edi)\n\t"
      ".LFUN_001d1c74_1:\n\t"
      "movl 0x18(%%ebp), %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "je .LFUN_001d1c74_3\n\t"
      "movl 0x8(%%esi), %%eax\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "movl 0xc(%%esi), %%eax\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "movl 0x10(%%esi), %%eax\n\t"
      "leal -0x10(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl 0x10(%%ebp)\n\t"
      "movl %%eax, %%ecx\n\t"
      "pushl 0xc(%%ebp)\n\t"
      "andb $1, %%cl\n\t"
      "negb %%cl\n\t"
      "pushl %%esi\n\t"
      "movl $0x103, %%edi\n\t"
      "movl %%edi, (%%esi)\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "notl %%ecx\n\t"
      "andl %%esi, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "pushl 0x8(%%ebp)\n\t"
      "call *0x25319c\n\t"
      "movl $0xc0000000, %%ecx\n\t"
      "movl %%eax, %%edx\n\t"
      "andl %%ecx, %%edx\n\t"
      "cmpl %%ecx, %%edx\n\t"
      "je .LFUN_001d1c74_6\n\t"
      "cmpl %%edi, %%eax\n\t"
      "je .LFUN_001d1c74_6\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "cmpl %%ebx, %%eax\n\t"
      "je .LFUN_001d1c74_2\n\t"
      "movl 0x4(%%esi), %%ecx\n\t"
      "movl %%ecx, (%%eax)\n\t"
      ".LFUN_001d1c74_2:\n\t"
      "xorl %%eax, %%eax\n\t"
      "incl %%eax\n\t"
      "jmp .LFUN_001d1c74_7\n\t"
      ".LFUN_001d1c74_3:\n\t"
      "pushl %%ebx\n\t"
      "pushl 0x10(%%ebp)\n\t"
      "leal -0x8(%%ebp), %%eax\n\t"
      "pushl 0xc(%%ebp)\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ebx\n\t"
      "pushl 0x8(%%ebp)\n\t"
      "call *0x25319c\n\t"
      "cmpl $0x103, %%eax\n\t"
      "jne .LFUN_001d1c74_4\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ebx\n\t"
      "pushl 0x8(%%ebp)\n\t"
      "call *0x253174\n\t"
      "cmpl %%ebx, %%eax\n\t"
      "jl .LFUN_001d1c74_5\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      ".LFUN_001d1c74_4:\n\t"
      "cmpl %%ebx, %%eax\n\t"
      "jl .LFUN_001d1c74_5\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movl %%eax, (%%edi)\n\t"
      "jmp .LFUN_001d1c74_2\n\t"
      ".LFUN_001d1c74_5:\n\t"
      "movl %%eax, %%ecx\n\t"
      "andl $0xc0000000, %%ecx\n\t"
      "cmpl $0x80000000, %%ecx\n\t"
      "jne .LFUN_001d1c74_6\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movl %%ecx, (%%edi)\n\t"
      ".LFUN_001d1c74_6:\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d2296]\n\t"
      "xorl %%eax, %%eax\n\t"
      ".LFUN_001d1c74_7:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      :
      : [c1d2296] "m"(b1d1c74_c1d2296)
      : "memory");
}
#else
#error "FUN_001d1c74: clang naked draft required"
#endif


/* 0x1d1d4a */
unsigned int GetFileSize(int handle, unsigned int *high_size)
{
  int eax = 0;
  int ebp = 0;

  FUN_001d19a9();
  /* test eax, eax -> je 0x1d1d7a */
  /* test eax, eax -> je 0x1d1d6b */
  /* relift: cmp dword ptr [ebp - 8], -1 -> jne 0x1d1d7e */
  SetLastError(0);
  return 0;

  (void)eax;
  (void)ebp;
}

/* 0x1d1d85 */
int CreateFileA(const char * unused_arg_0, uint32_t unused_arg_1, uint32_t unused_arg_2, uint32_t unused_arg_3, uint32_t unused_arg_4, uint32_t unused_arg_5, uint32_t unused_arg_6)
{
  int eax = 0;
  int ebx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  XapiSetLastNTError(0xc000000d);
  /* relift: cmp word ptr [ebp - 0xc], (int16_t)ebx -> jbe 0x1d1e06 */
  /* relift: cmp byte ptr [eax + edi - 1], 0x5c -> jne 0x1d1e06 */
  /* cmp esi, ebx -> jge 0x1d1ee2 */
  XapiSetLastNTError(0);
  /* cmp esi, 0xc0000035 -> jne 0x1d1ec5 */
  /* cmp esi, 0xc00000ba -> jne 0x1d1edd */
  /* relift: cmp dword ptr [ebp + 8], ebx -> je 0x1d1ed6 */
  SetLastError(0);
  /* relift: cmp dword ptr [ebp + 0x18], 2 -> jne 0x1d1eee */
  /* relift: cmp dword ptr [ebp - 0x10], 3 -> je 0x1d1efa */
  /* relift: cmp dword ptr [ebp + 0x18], 4 -> jne 0x1d1f01 */
  /* relift: cmp dword ptr [ebp - 0x10], 1 -> jne 0x1d1f01 */
  SetLastError(ebx);
  return 0;

  (void)eax;
  (void)ebx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* FUN_001d1f10 (0x1d1f10) — XBE naked draft (batch 312). */
#if defined(__clang__)
static void __stdcall (*const b1d1f10_c1d2268)(unsigned int error) = (void *)SetLastError;
static void __stdcall (*const b1d1f10_c1d2296)(int status) = (void *)XapiSetLastNTError;

__attribute__((naked, noinline))
void FUN_001d1f10(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "leal -0x60(%%esp), %%ebp\n\t"
      "subl $0x9c, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "pushl $4\n\t"
      "leal -0x14(%%ebp), %%eax\n\t"
      "movl $0x10000, %%ebx\n\t"
      "pushl %%ebx\n\t"
      "movl $0xfffffffd, -0x4(%%ebp)\n\t"
      "movl $0x40, 0x4(%%ebp)\n\t"
      "movl %%eax, (%%ebp)\n\t"
      "call *0x2531a8\n\t"
      "xorl %%edi, %%edi\n\t"
      "cmpl %%edi, %%eax\n\t"
      "movl %%eax, 0x48(%%ebp)\n\t"
      "jne .LFUN_001d1f10_1\n\t"
      "pushl $8\n\t"
      "call *%[c1d2268]\n\t"
      "xorl %%eax, %%eax\n\t"
      "jmp .LFUN_001d1f10_19\n\t"
      ".LFUN_001d1f10_1:\n\t"
      "pushl %%esi\n\t"
      "pushl 0x68(%%ebp)\n\t"
      "movl 0x2530e4, %%esi\n\t"
      "leal -0x14(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%%esi\n\t"
      "pushl $0x60\n\t"
      "pushl $1\n\t"
      "leal 0x40(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x4(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x80100000\n\t"
      "leal 0x50(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *0x253160\n\t"
      "cmpl %%edi, %%eax\n\t"
      "movl %%eax, 0x68(%%ebp)\n\t"
      "jge .LFUN_001d1f10_4\n\t"
      ".LFUN_001d1f10_2:\n\t"
      "pushl %%ebx\n\t"
      "pushl 0x48(%%ebp)\n\t"
      "call *0x2531a4\n\t"
      "pushl 0x68(%%ebp)\n\t"
      ".LFUN_001d1f10_3:\n\t"
      "call *%[c1d2296]\n\t"
      "xorl %%eax, %%eax\n\t"
      "jmp .LFUN_001d1f10_18\n\t"
      ".LFUN_001d1f10_4:\n\t"
      "pushl $0x22\n\t"
      "pushl $0x38\n\t"
      "leal 0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal 0x40(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl 0x50(%%ebp)\n\t"
      "call *0x253180\n\t"
      "cmpl %%edi, %%eax\n\t"
      "movl %%eax, 0x68(%%ebp)\n\t"
      "jge .LFUN_001d1f10_5\n\t"
      "pushl 0x50(%%ebp)\n\t"
      "call *0x253090\n\t"
      "jmp .LFUN_001d1f10_2\n\t"
      ".LFUN_001d1f10_5:\n\t"
      "pushl 0x6c(%%ebp)\n\t"
      "leal -0x14(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%%esi\n\t"
      "movl 0x7c(%%ebp), %%eax\n\t"
      "andb $1, %%al\n\t"
      "negb %%al\n\t"
      "pushl $0x64\n\t"
      "sbbl %%eax, %%eax\n\t"
      "andl $0xfffffffd, %%eax\n\t"
      "addl $5, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl $0x80\n\t"
      "leal 0x30(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal 0x40(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x4(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x40100000\n\t"
      "leal 0x54(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *0x2531a0\n\t"
      "movl %%eax, %%esi\n\t"
      "cmpl %%edi, %%esi\n\t"
      "jge .LFUN_001d1f10_6\n\t"
      "pushl 0x50(%%ebp)\n\t"
      "call *0x253090\n\t"
      "pushl %%ebx\n\t"
      "pushl 0x48(%%ebp)\n\t"
      "call *0x2531a4\n\t"
      "pushl %%esi\n\t"
      "jmp .LFUN_001d1f10_3\n\t"
      ".LFUN_001d1f10_6:\n\t"
      "cmpl %%edi, 0x70(%%ebp)\n\t"
      "movl %%edi, 0x58(%%ebp)\n\t"
      "movl %%edi, 0x5c(%%ebp)\n\t"
      "je .LFUN_001d1f10_7\n\t"
      "pushl 0x74(%%ebp)\n\t"
      "pushl 0x54(%%ebp)\n\t"
      "pushl 0x50(%%ebp)\n\t"
      "pushl $1\n\t"
      "pushl $1\n\t"
      "pushl %%edi\n\t"
      "pushl %%edi\n\t"
      "pushl 0x34(%%ebp)\n\t"
      "pushl 0x30(%%ebp)\n\t"
      "pushl %%edi\n\t"
      "pushl %%edi\n\t"
      "pushl 0x34(%%ebp)\n\t"
      "pushl 0x30(%%ebp)\n\t"
      "call *0x70(%%ebp)\n\t"
      "cmpl $3, %%eax\n\t"
      "jne .LFUN_001d1f10_9\n\t"
      "movl %%edi, 0x70(%%ebp)\n\t"
      ".LFUN_001d1f10_7:\n\t"
      "movl 0x30(%%ebp), %%eax\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "movl 0x34(%%ebp), %%eax\n\t"
      "pushl $0x14\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "pushl $8\n\t"
      "leal -0xc(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal 0x40(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl 0x54(%%ebp)\n\t"
      "call *0x25315c\n\t"
      "movl %%eax, %%esi\n\t"
      "cmpl %%edi, %%esi\n\t"
      "jl .LFUN_001d1f10_15\n\t"
      "movl 0x5c(%%ebp), %%eax\n\t"
      "cmpl 0x34(%%ebp), %%eax\n\t"
      "jg .LFUN_001d1f10_14\n\t"
      "jge .LFUN_001d1f10_12\n\t"
      ".LFUN_001d1f10_8:\n\t"
      "leal 0x58(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl 0x48(%%ebp)\n\t"
      "leal 0x40(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%edi\n\t"
      "pushl %%edi\n\t"
      "pushl 0x50(%%ebp)\n\t"
      "call *0x253178\n\t"
      "movl %%eax, %%esi\n\t"
      "cmpl %%edi, %%esi\n\t"
      "jl .LFUN_001d1f10_15\n\t"
      "movl 0x44(%%ebp), %%eax\n\t"
      "leal 0x58(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl 0x48(%%ebp)\n\t"
      "movl %%eax, 0x68(%%ebp)\n\t"
      "leal 0x40(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%edi\n\t"
      "pushl %%edi\n\t"
      "pushl 0x54(%%ebp)\n\t"
      "call *0x25317c\n\t"
      "movl %%eax, %%esi\n\t"
      "cmpl %%edi, %%esi\n\t"
      "jl .LFUN_001d1f10_15\n\t"
      "movl 0x58(%%ebp), %%eax\n\t"
      "addl 0x68(%%ebp), %%eax\n\t"
      "adcl %%edi, 0x5c(%%ebp)\n\t"
      "cmpl %%edi, 0x70(%%ebp)\n\t"
      "movl %%eax, 0x58(%%ebp)\n\t"
      "je .LFUN_001d1f10_11\n\t"
      "pushl 0x74(%%ebp)\n\t"
      "pushl 0x54(%%ebp)\n\t"
      "pushl 0x50(%%ebp)\n\t"
      "pushl %%edi\n\t"
      "pushl $1\n\t"
      "pushl 0x5c(%%ebp)\n\t"
      "pushl %%eax\n\t"
      "pushl 0x34(%%ebp)\n\t"
      "pushl 0x30(%%ebp)\n\t"
      "pushl 0x5c(%%ebp)\n\t"
      "pushl %%eax\n\t"
      "pushl 0x34(%%ebp)\n\t"
      "pushl 0x30(%%ebp)\n\t"
      "call *0x70(%%ebp)\n\t"
      "cmpl $3, %%eax\n\t"
      "jne .LFUN_001d1f10_10\n\t"
      "movl %%edi, 0x70(%%ebp)\n\t"
      "jmp .LFUN_001d1f10_11\n\t"
      ".LFUN_001d1f10_9:\n\t"
      "cmpl %%edi, %%eax\n\t"
      "je .LFUN_001d1f10_7\n\t"
      "movl $0xc0000240, %%esi\n\t"
      "jmp .LFUN_001d1f10_15\n\t"
      ".LFUN_001d1f10_10:\n\t"
      "cmpl %%edi, %%eax\n\t"
      "jne .LFUN_001d1f10_13\n\t"
      ".LFUN_001d1f10_11:\n\t"
      "movl 0x5c(%%ebp), %%eax\n\t"
      "cmpl 0x34(%%ebp), %%eax\n\t"
      "jl .LFUN_001d1f10_8\n\t"
      "jg .LFUN_001d1f10_14\n\t"
      ".LFUN_001d1f10_12:\n\t"
      "movl 0x58(%%ebp), %%eax\n\t"
      "cmpl 0x30(%%ebp), %%eax\n\t"
      "jb .LFUN_001d1f10_8\n\t"
      "jmp .LFUN_001d1f10_14\n\t"
      ".LFUN_001d1f10_13:\n\t"
      "movl $0xc0000240, %%esi\n\t"
      ".LFUN_001d1f10_14:\n\t"
      "cmpl %%edi, %%esi\n\t"
      "jl .LFUN_001d1f10_15\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl %%eax, -0x3c(%%ebp)\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "movl %%eax, -0x38(%%ebp)\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "movl %%eax, -0x34(%%ebp)\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "movl %%eax, -0x30(%%ebp)\n\t"
      "movl 0x18(%%ebp), %%eax\n\t"
      "movl %%eax, -0x2c(%%ebp)\n\t"
      "movl 0x1c(%%ebp), %%eax\n\t"
      "movl %%eax, -0x28(%%ebp)\n\t"
      "movl 0x20(%%ebp), %%eax\n\t"
      "movl %%eax, -0x24(%%ebp)\n\t"
      "movl 0x24(%%ebp), %%eax\n\t"
      "movl %%eax, -0x20(%%ebp)\n\t"
      "movl 0x38(%%ebp), %%eax\n\t"
      "pushl $4\n\t"
      "movl %%eax, -0x1c(%%ebp)\n\t"
      "pushl $0x28\n\t"
      "leal -0x3c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal 0x40(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl 0x54(%%ebp)\n\t"
      "call *0x25315c\n\t"
      "movl %%eax, %%esi\n\t"
      ".LFUN_001d1f10_15:\n\t"
      "pushl %%ebx\n\t"
      "pushl 0x48(%%ebp)\n\t"
      "call *0x2531a4\n\t"
      "pushl 0x50(%%ebp)\n\t"
      "movl 0x253090, %%ebx\n\t"
      "call *%%ebx\n\t"
      "cmpl %%edi, %%esi\n\t"
      "jge .LFUN_001d1f10_16\n\t"
      "pushl $0xd\n\t"
      "pushl $1\n\t"
      "leal 0x4f(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal 0x40(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl 0x54(%%ebp)\n\t"
      "movb $1, 0x4f(%%ebp)\n\t"
      "call *0x25315c\n\t"
      "pushl %%esi\n\t"
      "call *%[c1d2296]\n\t"
      "jmp .LFUN_001d1f10_17\n\t"
      ".LFUN_001d1f10_16:\n\t"
      "xorl %%edi, %%edi\n\t"
      "incl %%edi\n\t"
      ".LFUN_001d1f10_17:\n\t"
      "pushl 0x54(%%ebp)\n\t"
      "call *%%ebx\n\t"
      "movl %%edi, %%eax\n\t"
      ".LFUN_001d1f10_18:\n\t"
      "popl %%esi\n\t"
      ".LFUN_001d1f10_19:\n\t"
      "popl %%edi\n\t"
      "popl %%ebx\n\t"
      "addl $0x60, %%ebp\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      :
      : [c1d2268] "m"(b1d1f10_c1d2268), [c1d2296] "m"(b1d1f10_c1d2296)
      : "memory");
}
#else
#error "FUN_001d1f10: clang naked draft required"
#endif

