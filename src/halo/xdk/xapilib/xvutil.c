/* kb object stubs -> xdk/xapilib/xvutil.c */

/* --- XAPILIB:xvutil.obj batch drafts (2026-07-26) --- */

/* FUN_001d04f1 (0x1d04f1) — XBE naked draft (batch 321). */
#if defined(__clang__)
static void (*const b1d04f1_c1d4464)(void) = FUN_001d4464;

__attribute__((naked, noinline))
void FUN_001d04f1(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xc, %%esp\n\t"
      "leal -0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $4\n\t"
      "leal -0x4(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0xc(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x11\n\t"
      "call *%[c1d4464]\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_001d04f1_1\n\t"
      "testb $2, -0x4(%%ebp)\n\t"
      "je .LFUN_001d04f1_1\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      ".LFUN_001d04f1_1:\n\t"
      "xorl %%eax, %%eax\n\t"
      "incl %%eax\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      :
      : [c1d4464] "m"(b1d04f1_c1d4464)
      : "memory");
}
#else
#error "FUN_001d04f1: clang naked draft required"
#endif


/* 0x1d051d */
void GetLocalTime(void *system_time)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* FUN_001d0581 (0x1d0581) — readable C lift (deref global). */
int FUN_001d0581(void)
{
  return **(int **)0x253140;
}

/* FUN_001d0589 (0x1d0589) — XBE naked draft (batch 321). */
#if defined(__clang__)


__attribute__((naked, noinline))
void FUN_001d0589(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x18, %%esp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "movl 0x4(%%eax), %%eax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "leal -0x18(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "call *0x253138\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "movw -0x18(%%ebp), %%cx\n\t"
      "movw %%cx, (%%eax)\n\t"
      "movw -0x16(%%ebp), %%cx\n\t"
      "movw %%cx, 0x2(%%eax)\n\t"
      "movw -0x14(%%ebp), %%cx\n\t"
      "movw %%cx, 0x6(%%eax)\n\t"
      "movw -0xa(%%ebp), %%cx\n\t"
      "movw %%cx, 0x4(%%eax)\n\t"
      "movw -0x12(%%ebp), %%cx\n\t"
      "movw %%cx, 0x8(%%eax)\n\t"
      "movw -0x10(%%ebp), %%cx\n\t"
      "movw %%cx, 0xa(%%eax)\n\t"
      "movw -0xe(%%ebp), %%cx\n\t"
      "movw %%cx, 0xc(%%eax)\n\t"
      "movw -0xc(%%ebp), %%cx\n\t"
      "movw %%cx, 0xe(%%eax)\n\t"
      "xorl %%eax, %%eax\n\t"
      "incl %%eax\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "FUN_001d0589: clang naked draft required"
#endif


/* 0x1d05f4 */
bool SystemTimeToFileTime(void *system_time, void *file_time)
{
  int eax = 0;

  /* test (char)eax, (char)eax -> jne 0x1d0654 */
  XapiSetLastNTError(0xc000000d);
  return 0;

  (void)eax;
}

/* FUN_001d0669 (0x1d0669) — XBE naked draft (batch 344). */
#if defined(__clang__)


__attribute__((naked, noinline))
void FUN_001d0669(void)
{
  __asm__ volatile(
      "movl 0x4(%%esp), %%eax\n\t"
      "movl 0x8(%%esp), %%ecx\n\t"
      "movl (%%eax), %%edx\n\t"
      "movl 0x4(%%eax), %%eax\n\t"
      "pushl %%esi\n\t"
      "movl (%%ecx), %%esi\n\t"
      "movl 0x4(%%ecx), %%ecx\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "ja .LFUN_001d0669_3\n\t"
      "jb .LFUN_001d0669_1\n\t"
      "cmpl %%esi, %%edx\n\t"
      "jae .LFUN_001d0669_2\n\t"
      ".LFUN_001d0669_1:\n\t"
      "orl $0xffffffff, %%eax\n\t"
      "jmp .LFUN_001d0669_5\n\t"
      ".LFUN_001d0669_2:\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jb .LFUN_001d0669_4\n\t"
      "ja .LFUN_001d0669_3\n\t"
      "cmpl %%esi, %%edx\n\t"
      "jbe .LFUN_001d0669_4\n\t"
      ".LFUN_001d0669_3:\n\t"
      "xorl %%eax, %%eax\n\t"
      "incl %%eax\n\t"
      "jmp .LFUN_001d0669_5\n\t"
      ".LFUN_001d0669_4:\n\t"
      "xorl %%eax, %%eax\n\t"
      ".LFUN_001d0669_5:\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "FUN_001d0669: clang naked draft required"
#endif


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


/* GetTimeZoneInformation (0x1d08aa) — XBE naked draft (batch 321). */
#if defined(__clang__)
static void (*const b1d08aa_c1d0447)(void) = FUN_001d0447;
static void __stdcall (*const b1d08aa_c1d2268)(unsigned int error) = (void *)SetLastError;
static void (*const b1d08aa_c1d06a0)(void) = FUN_001d06a0;
static void (*const b1d08aa_c1dd620)(void) = __allmul;

__attribute__((naked, noinline))
void GetTimeZoneInformation(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x28, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "leal 0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "call *%[c1d0447]\n\t"
      "cmpl %%ebx, %%eax\n\t"
      "je .LGetTimeZoneInformation_1\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d2268]\n\t"
      "orl $0xffffffff, %%eax\n\t"
      "jmp .LGetTimeZoneInformation_10\n\t"
      ".LGetTimeZoneInformation_1:\n\t"
      "cmpl %%ebx, 0x8(%%ebp)\n\t"
      "pushl %%edi\n\t"
      "jne .LGetTimeZoneInformation_2\n\t"
      "movl %%ebx, 0x54(%%esi)\n\t"
      "xorl %%eax, %%eax\n\t"
      "leal 0x44(%%esi), %%edi\n\t"
      ".byte 0xab\n\t"
      ".byte 0xab\n\t"
      ".byte 0xab\n\t"
      ".byte 0xab\n\t"
      "movl %%ebx, 0xa8(%%esi)\n\t"
      "xorl %%eax, %%eax\n\t"
      "leal 0x98(%%esi), %%edi\n\t"
      ".byte 0xab\n\t"
      ".byte 0xab\n\t"
      ".byte 0xab\n\t"
      ".byte 0xab\n\t"
      "pushl $0x10\n\t"
      "popl %%ecx\n\t"
      "xorl %%eax, %%eax\n\t"
      "leal 0x58(%%esi), %%edi\n\t"
      "rep stosl\n\t"
      ".LGetTimeZoneInformation_2:\n\t"
      "leal -0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *0x25313c\n\t"
      "cmpw %%bx, 0x46(%%esi)\n\t"
      "je .LGetTimeZoneInformation_9\n\t"
      "cmpw %%bx, 0x9a(%%esi)\n\t"
      "je .LGetTimeZoneInformation_9\n\t"
      "pushl $1\n\t"
      "leal -0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x28(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal 0x44(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d06a0]\n\t"
      "testb %%al, %%al\n\t"
      "je .LGetTimeZoneInformation_9\n\t"
      "pushl $1\n\t"
      "leal -0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x20(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal 0x98(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d06a0]\n\t"
      "testb %%al, %%al\n\t"
      "je .LGetTimeZoneInformation_9\n\t"
      "movl (%%esi), %%eax\n\t"
      "imull $0x3c, %%eax, %%eax\n\t"
      "pushl %%ebx\n\t"
      "cdq\n\t"
      "movl $0x989680, %%edi\n\t"
      "pushl %%edi\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c1dd620]\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "movl 0x54(%%esi), %%eax\n\t"
      "imull $0x3c, %%eax, %%eax\n\t"
      "pushl %%ebx\n\t"
      "movl %%edx, -0xc(%%ebp)\n\t"
      "cdq\n\t"
      "pushl %%edi\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c1dd620]\n\t"
      "addl -0x10(%%ebp), %%eax\n\t"
      "movl %%edx, %%ebx\n\t"
      "adcl -0xc(%%ebp), %%ebx\n\t"
      "addl -0x20(%%ebp), %%eax\n\t"
      "pushl $0\n\t"
      "adcl -0x1c(%%ebp), %%ebx\n\t"
      "movl %%eax, -0x18(%%ebp)\n\t"
      "movl 0xa8(%%esi), %%eax\n\t"
      "imull $0x3c, %%eax, %%eax\n\t"
      "cdq\n\t"
      "pushl %%edi\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c1dd620]\n\t"
      "addl -0x10(%%ebp), %%eax\n\t"
      "adcl -0xc(%%ebp), %%edx\n\t"
      "addl -0x28(%%ebp), %%eax\n\t"
      "adcl -0x24(%%ebp), %%edx\n\t"
      "cmpl %%edx, %%ebx\n\t"
      "jg .LGetTimeZoneInformation_6\n\t"
      "jl .LGetTimeZoneInformation_3\n\t"
      "cmpl %%eax, -0x18(%%ebp)\n\t"
      "jae .LGetTimeZoneInformation_6\n\t"
      ".LGetTimeZoneInformation_3:\n\t"
      "cmpl %%ebx, -0x4(%%ebp)\n\t"
      "jl .LGetTimeZoneInformation_5\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "jg .LGetTimeZoneInformation_4\n\t"
      "cmpl -0x18(%%ebp), %%ecx\n\t"
      "jb .LGetTimeZoneInformation_5\n\t"
      ".LGetTimeZoneInformation_4:\n\t"
      "cmpl %%edx, -0x4(%%ebp)\n\t"
      "jg .LGetTimeZoneInformation_5\n\t"
      "jl .LGetTimeZoneInformation_8\n\t"
      "cmpl %%eax, %%ecx\n\t"
      "jb .LGetTimeZoneInformation_8\n\t"
      ".LGetTimeZoneInformation_5:\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "incl %%ebx\n\t"
      "jmp .LGetTimeZoneInformation_9\n\t"
      ".LGetTimeZoneInformation_6:\n\t"
      "cmpl %%edx, -0x4(%%ebp)\n\t"
      "jl .LGetTimeZoneInformation_8\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "jg .LGetTimeZoneInformation_7\n\t"
      "cmpl %%eax, %%ecx\n\t"
      "jb .LGetTimeZoneInformation_8\n\t"
      ".LGetTimeZoneInformation_7:\n\t"
      "cmpl %%ebx, -0x4(%%ebp)\n\t"
      "jg .LGetTimeZoneInformation_8\n\t"
      "jl .LGetTimeZoneInformation_5\n\t"
      "cmpl -0x18(%%ebp), %%ecx\n\t"
      "jb .LGetTimeZoneInformation_5\n\t"
      ".LGetTimeZoneInformation_8:\n\t"
      "pushl $2\n\t"
      "popl %%ebx\n\t"
      ".LGetTimeZoneInformation_9:\n\t"
      "movl %%ebx, %%eax\n\t"
      "popl %%edi\n\t"
      ".LGetTimeZoneInformation_10:\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      :
      : [c1d0447] "m"(b1d08aa_c1d0447), [c1d2268] "m"(b1d08aa_c1d2268), [c1d06a0] "m"(b1d08aa_c1d06a0), [c1dd620] "m"(b1d08aa_c1dd620)
      : "memory");
}
#else
#error "GetTimeZoneInformation: clang naked draft required"
#endif


/* FUN_001d0a06 (0x1d0a06) — XBE naked draft (batch 331). */
#if defined(__clang__)
static void (*const b1d0a06_c1d08aa)(void) = GetTimeZoneInformation;
static void (*const b1d0a06_c1dd620)(void) = __allmul;

__attribute__((naked, noinline))
void FUN_001d0a06(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "leal -0x74(%%esp), %%ebp\n\t"
      "subl $0xac, %%esp\n\t"
      "leal -0x38(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d08aa]\n\t"
      "subl $0, %%eax\n\t"
      "je .LFUN_001d0a06_4\n\t"
      "decl %%eax\n\t"
      "je .LFUN_001d0a06_3\n\t"
      "decl %%eax\n\t"
      "je .LFUN_001d0a06_1\n\t"
      "xorl %%eax, %%eax\n\t"
      "jmp .LFUN_001d0a06_5\n\t"
      ".LFUN_001d0a06_1:\n\t"
      "movl 0x70(%%ebp), %%ecx\n\t"
      ".LFUN_001d0a06_2:\n\t"
      "movl -0x38(%%ebp), %%eax\n\t"
      "addl %%ecx, %%eax\n\t"
      "jmp .LFUN_001d0a06_5\n\t"
      ".LFUN_001d0a06_3:\n\t"
      "movl 0x1c(%%ebp), %%ecx\n\t"
      "jmp .LFUN_001d0a06_2\n\t"
      ".LFUN_001d0a06_4:\n\t"
      "movl -0x38(%%ebp), %%eax\n\t"
      ".LFUN_001d0a06_5:\n\t"
      "imull $0x3c, %%eax, %%eax\n\t"
      "pushl $0\n\t"
      "cdq\n\t"
      "pushl $0x989680\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c1dd620]\n\t"
      "movl 0x7c(%%ebp), %%ecx\n\t"
      "movl %%eax, (%%ecx)\n\t"
      "movl %%edx, 0x4(%%ecx)\n\t"
      "addl $0x74, %%ebp\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      :
      : [c1d08aa] "m"(b1d0a06_c1d08aa), [c1dd620] "m"(b1d0a06_c1dd620)
      : "memory");
}
#else
#error "FUN_001d0a06: clang naked draft required"
#endif


/* FUN_001d0a5c (0x1d0a5c) — XBE naked draft (batch 314). */
#if defined(__clang__)
static void (*const b1d0a5c_c1d0a06)(void) = FUN_001d0a06;

__attribute__((naked, noinline))
void FUN_001d0a5c(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x28, %%esp\n\t"
      "leal -0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *0x25313c\n\t"
      "leal -0x10(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d0a06]\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "subl -0x10(%%ebp), %%eax\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "sbbl -0xc(%%ebp), %%ecx\n\t"
      "movl %%eax, -0x18(%%ebp)\n\t"
      "leal -0x28(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x18(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl %%ecx, -0x14(%%ebp)\n\t"
      "call *0x253138\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movw -0x28(%%ebp), %%cx\n\t"
      "movw %%cx, (%%eax)\n\t"
      "movw -0x26(%%ebp), %%cx\n\t"
      "movw %%cx, 0x2(%%eax)\n\t"
      "movw -0x1a(%%ebp), %%cx\n\t"
      "movw %%cx, 0x4(%%eax)\n\t"
      "movw -0x24(%%ebp), %%cx\n\t"
      "movw %%cx, 0x6(%%eax)\n\t"
      "movw -0x22(%%ebp), %%cx\n\t"
      "movw %%cx, 0x8(%%eax)\n\t"
      "movw -0x20(%%ebp), %%cx\n\t"
      "movw %%cx, 0xa(%%eax)\n\t"
      "movw -0x1e(%%ebp), %%cx\n\t"
      "movw %%cx, 0xc(%%eax)\n\t"
      "movw -0x1c(%%ebp), %%cx\n\t"
      "movw %%cx, 0xe(%%eax)\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      :
      : [c1d0a06] "m"(b1d0a5c_c1d0a06)
      : "memory");
}
#else
#error "FUN_001d0a5c: clang naked draft required"
#endif


/* FUN_001d0adb (0x1d0adb) — XBE naked draft (batch 337). */
#if defined(__clang__)
static void (*const b1d0adb_c1d0a06)(void) = FUN_001d0a06;

__attribute__((naked, noinline))
void FUN_001d0adb(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d0a06]\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "movl (%%ecx), %%eax\n\t"
      "subl -0x8(%%ebp), %%eax\n\t"
      "movl 0x4(%%ecx), %%ecx\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "sbbl -0x4(%%ebp), %%ecx\n\t"
      "movl %%eax, (%%edx)\n\t"
      "xorl %%eax, %%eax\n\t"
      "movl %%ecx, 0x4(%%edx)\n\t"
      "incl %%eax\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      :
      : [c1d0a06] "m"(b1d0adb_c1d0a06)
      : "memory");
}
#else
#error "FUN_001d0adb: clang naked draft required"
#endif


/* FUN_001d0b06 (0x1d0b06) — XBE naked draft (batch 337). */
#if defined(__clang__)
static void (*const b1d0b06_c1d0a06)(void) = FUN_001d0a06;

__attribute__((naked, noinline))
void FUN_001d0b06(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d0a06]\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "movl (%%ecx), %%eax\n\t"
      "addl -0x8(%%ebp), %%eax\n\t"
      "movl 0x4(%%ecx), %%ecx\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "adcl -0x4(%%ebp), %%ecx\n\t"
      "movl %%eax, (%%edx)\n\t"
      "xorl %%eax, %%eax\n\t"
      "movl %%ecx, 0x4(%%edx)\n\t"
      "incl %%eax\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      :
      : [c1d0a06] "m"(b1d0b06_c1d0a06)
      : "memory");
}
#else
#error "FUN_001d0b06: clang naked draft required"
#endif


/* FUN_001d0b31 (0x1d0b31) — XBE naked draft (batch 360). */
#if defined(__clang__)
static void (*const b1d0b31_c1d5842)(void) = (void *)FUN_001d5842;
static void __stdcall (*const b1d0b31_c1d2268)(unsigned int error) = (void *)SetLastError;

__attribute__((naked, noinline))
void FUN_001d0b31(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "andl $5, %%eax\n\t"
      "movl $0x1000, %%ecx\n\t"
      "orl %%ecx, %%eax\n\t"
      "cmpl %%ecx, %%edx\n\t"
      "jae .LFUN_001d0b31_2\n\t"
      "testl %%edx, %%edx\n\t"
      "jne .LFUN_001d0b31_1\n\t"
      "orl $2, %%eax\n\t"
      "jmp .LFUN_001d0b31_3\n\t"
      ".LFUN_001d0b31_1:\n\t"
      "movl %%ecx, %%edx\n\t"
      ".LFUN_001d0b31_2:\n\t"
      "cmpl %%edx, 0xc(%%ebp)\n\t"
      "jbe .LFUN_001d0b31_3\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      ".LFUN_001d0b31_3:\n\t"
      "pushl %%esi\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl 0xc(%%ebp)\n\t"
      "pushl %%edx\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d5842]\n\t"
      "movl %%eax, %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LFUN_001d0b31_4\n\t"
      "pushl $8\n\t"
      "call *%[c1d2268]\n\t"
      ".LFUN_001d0b31_4:\n\t"
      "movl %%esi, %%eax\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c1d5842] "m"(b1d0b31_c1d5842), [c1d2268] "m"(b1d0b31_c1d2268)
      : "memory");
}
#else
#error "FUN_001d0b31: clang naked draft required"
#endif


/* FUN_001d0b9c (0x1d0b9c) — readable C lift (HeapFree BOOL wrapper). */
unsigned int __stdcall FUN_001d0b9c(void *a, void *b, void *c)
{
  return (unsigned int)(unsigned char)FUN_001d6ca8(a, (unsigned int)(uintptr_t)b, c);
}

/* 0x1d0bb3 */
void FUN_001d0bb3(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* FUN_001d0c02 (0x1d0c02) — readable C lift (HeapFree-style). */
void __stdcall FUN_001d0c02(void *ptr)
{
  extern void *DAT_00632a28;
  FUN_001d52c4(DAT_00632a28, 0, ptr);
}

void * LocalFree(void *ptr)
{
  (void)FUN_001d6ca8(0, 0, ptr);
  return NULL;
}

/* FUN_001d0bb9 (0x1d0bb9) — readable C lift (HeapAlloc-style wrapper). */
void *__stdcall FUN_001d0bb9(unsigned int flags, unsigned int size)
{
  extern void *DAT_00632a28;
  return FUN_001d5c66(DAT_00632a28, (flags >> 3) & 8, (int)size);
}

/* FUN_001d0c16 (0x1d0c16) — readable C lift (HeapFree-style wrapper). */
void *__stdcall FUN_001d0c16(void *ptr)
{
  extern void *DAT_00632a28;
  if (FUN_001d6ca8(DAT_00632a28, 0, ptr))
    return 0;
  return ptr;
}

/* FUN_001d0c48 (0x1d0c48) — readable C lift (HeapAlloc-style wrapper). */
void *__stdcall FUN_001d0c48(int flags, int size)
{
  extern void *DAT_00632a28;
  return FUN_001d5c66(DAT_00632a28, ((unsigned int)flags >> 3) & 8, size);
}

/* FUN_001d0c65 (0x1d0c65) — readable C lift (HeapReAlloc-style wrapper). */
void *__stdcall FUN_001d0c65(void *ptr, int size, int flags)
{
  extern void *DAT_00632a28;
  unsigned int mode;
  if ((flags & 0x40) != 0)
    mode = 8;
  else
    mode = (~((unsigned int)flags << 3)) & 0x10;
  return FUN_001d703b(DAT_00632a28, mode, ptr, size);
}

/* FUN_001d0c91 (0x1d0c91) — XBE naked draft (batch 376). */
#if defined(__clang__)
static void __stdcall (*const b1d0c91_c1d2296)(int status) = (void *)XapiSetLastNTError;

__attribute__((naked, noinline))
void FUN_001d0c91(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl 0x14(%%ebp)\n\t"
      "leal 0xc(%%ebp), %%eax\n\t"
      "pushl 0x10(%%ebp)\n\t"
      "pushl %%eax\n\t"
      "pushl $0\n\t"
      "leal 0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *0x253148\n\t"
      "testl %%eax, %%eax\n\t"
      "jl .LFUN_001d0c91_1\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "jmp .LFUN_001d0c91_2\n\t"
      ".LFUN_001d0c91_1:\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d2296]\n\t"
      "xorl %%eax, %%eax\n\t"
      ".LFUN_001d0c91_2:\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c1d2296] "m"(b1d0c91_c1d2296)
      : "memory");
}
#else
#error "FUN_001d0c91: clang naked draft required"
#endif


/* FUN_001d0cbf (0x1d0cbf) — XBE naked draft (batch 365). */
#if defined(__clang__)
static void __stdcall (*const b1d0cbf_c1d2296)(int status) = (void *)XapiSetLastNTError;

__attribute__((naked, noinline))
void FUN_001d0cbf(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "testb $0x80, 0x11(%%ebp)\n\t"
      "je .LFUN_001d0cbf_1\n\t"
      "cmpl $0, 0xc(%%ebp)\n\t"
      "je .LFUN_001d0cbf_1\n\t"
      "pushl $0xc000000d\n\t"
      "jmp .LFUN_001d0cbf_3\n\t"
      ".LFUN_001d0cbf_1:\n\t"
      "pushl 0x10(%%ebp)\n\t"
      "leal 0xc(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal 0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *0x25314c\n\t"
      "testl %%eax, %%eax\n\t"
      "jl .LFUN_001d0cbf_2\n\t"
      "xorl %%eax, %%eax\n\t"
      "incl %%eax\n\t"
      "jmp .LFUN_001d0cbf_4\n\t"
      ".LFUN_001d0cbf_2:\n\t"
      "pushl %%eax\n\t"
      ".LFUN_001d0cbf_3:\n\t"
      "call *%[c1d2296]\n\t"
      "xorl %%eax, %%eax\n\t"
      ".LFUN_001d0cbf_4:\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c1d2296] "m"(b1d0cbf_c1d2296)
      : "memory");
}
#else
#error "FUN_001d0cbf: clang naked draft required"
#endif


/* FUN_001d0cfb (0x1d0cfb) — XBE naked draft (batch 370). */
#if defined(__clang__)
static void __stdcall (*const b1d0cfb_c1d2296)(int status) = (void *)XapiSetLastNTError;

__attribute__((naked, noinline))
void FUN_001d0cfb(void)
{
  __asm__ volatile(
      "pushl 0x10(%%esp)\n\t"
      "leal 0xc(%%esp), %%eax\n\t"
      "pushl 0x10(%%esp)\n\t"
      "pushl %%eax\n\t"
      "leal 0x10(%%esp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *0x253150\n\t"
      "testl %%eax, %%eax\n\t"
      "jl .LFUN_001d0cfb_1\n\t"
      "xorl %%eax, %%eax\n\t"
      "incl %%eax\n\t"
      "jmp .LFUN_001d0cfb_2\n\t"
      ".LFUN_001d0cfb_1:\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d2296]\n\t"
      "xorl %%eax, %%eax\n\t"
      ".LFUN_001d0cfb_2:\n\t"
      "ret\n\t"
      :
      : [c1d2296] "m"(b1d0cfb_c1d2296)
      : "memory");
}
#else
#error "FUN_001d0cfb: clang naked draft required"
#endif


/* 0x1d0da1 */
void xbox_query_global_memory_status(void *status)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* FUN_001d0df0 (0x1d0df0) — XBE naked draft (batch 360). */
#if defined(__clang__)
static void __stdcall (*const b1d0df0_c1d2296)(int status) = (void *)XapiSetLastNTError;

__attribute__((naked, noinline))
bool FUN_001d0df0(const char *path __attribute__((unused)), unsigned int attributes __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x44, %%esp\n\t"
      "pushl 0x8(%%ebp)\n\t"
      "leal -0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *0x2530e4\n\t"
      "pushl $0x4020\n\t"
      "leal -0x8(%%ebp), %%eax\n\t"
      "movl %%eax, -0x18(%%ebp)\n\t"
      "pushl $7\n\t"
      "leal -0x10(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x1c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x100100\n\t"
      "leal 0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl $0xfffffffd, -0x1c(%%ebp)\n\t"
      "movl $0x40, -0x14(%%ebp)\n\t"
      "call *0x253160\n\t"
      "testl %%eax, %%eax\n\t"
      "jge .LFUN_001d0df0_1\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d2296]\n\t"
      "xorl %%eax, %%eax\n\t"
      "jmp .LFUN_001d0df0_4\n\t"
      ".LFUN_001d0df0_1:\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl $0xa\n\t"
      "popl %%ecx\n\t"
      "xorl %%eax, %%eax\n\t"
      "leal -0x44(%%ebp), %%edi\n\t"
      "rep stosl\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "andl $0x3127, %%eax\n\t"
      "orl $0x80, %%eax\n\t"
      "pushl $4\n\t"
      "movl %%eax, -0x24(%%ebp)\n\t"
      "pushl $0x28\n\t"
      "leal -0x44(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x10(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl 0x8(%%ebp)\n\t"
      "call *0x25315c\n\t"
      "pushl 0x8(%%ebp)\n\t"
      "movl %%eax, %%esi\n\t"
      "call *0x253090\n\t"
      "testl %%esi, %%esi\n\t"
      "jl .LFUN_001d0df0_2\n\t"
      "xorl %%eax, %%eax\n\t"
      "incl %%eax\n\t"
      "jmp .LFUN_001d0df0_3\n\t"
      ".LFUN_001d0df0_2:\n\t"
      "pushl %%esi\n\t"
      "call *%[c1d2296]\n\t"
      "xorl %%eax, %%eax\n\t"
      ".LFUN_001d0df0_3:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      ".LFUN_001d0df0_4:\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      :
      : [c1d2296] "m"(b1d0df0_c1d2296)
      : "memory");
}
#else
#error "FUN_001d0df0: clang naked draft required"
#endif

/* WaitForSingleObject (0x1d0336) — readable C lift. */
int __stdcall WaitForSingleObject(int handle, int timeout_ms)
{
  return FUN_001d00b9(handle, timeout_ms, 0);
}

/* FUN_001d0362 (0x1d0362) — readable C lift (Sleep-style). */
void __stdcall FUN_001d0362(int ms)
{
  FUN_001d01c4(ms, 0);
}

/* FUN_001cfde0 (0x1cfde0) — readable C lift (TEB TLS slot). */
int FUN_001cfde0(void)
{
  void *teb;
  __asm__ volatile("movl %%fs:0x28, %0" : "=r"(teb));
  return *(int *)((char *)teb + 0x12c);
}


/* FUN_001d0348 (0x1d0348) — readable C lift (WaitForMultipleObjects). */
int __stdcall FUN_001d0348(int nCount, void *handles, int waitAll, int timeout_ms)
{
  return FUN_001d0144(nCount, handles, waitAll, timeout_ms, 0);
}

/* ResetEvent (0x1cfeca) — readable C lift. */
int __stdcall ResetEvent(void *handle)
{
  int (__stdcall *nt_clear)(void *) = *(int (__stdcall **)(void *))0x2530ec;
  int status = nt_clear(handle);
  if (status < 0) {
    XapiSetLastNTError(status);
    return 0;
  }
  return 1;
}
