/* Tip-only unit for LIBCMT stricmp CRT tips. */

/* __aullshr (0x1dd660) — Capstone tip: unsigned 64-bit shr edx:eax by cl. */
__attribute__((naked, noinline))
void __aullshr(void)
{
  __asm__ volatile(
    "cmpb $0x40, %%cl\n\t"
    "jae 1f\n\t"
    "cmpb $0x20, %%cl\n\t"
    "jae 2f\n\t"
    "shrdl %%cl, %%edx, %%eax\n\t"
    "shrl %%cl, %%edx\n\t"
    "ret\n\t"
    "2:\n\t"
    "movl %%edx, %%eax\n\t"
    "xorl %%edx, %%edx\n\t"
    "andb $0x1f, %%cl\n\t"
    "shrl %%cl, %%eax\n\t"
    "ret\n\t"
    "1:\n\t"
    "xorl %%eax, %%eax\n\t"
    "xorl %%edx, %%edx\n\t"
    "ret\n\t"
    ::: "memory");
}

/* __allshr (0x1dd7e0) — Capstone tip: signed 64-bit sar edx:eax by cl. */
__attribute__((naked, noinline))
void __allshr(void)
{
  __asm__ volatile(
    "cmpb $0x40, %%cl\n\t"
    "jae 1f\n\t"
    "cmpb $0x20, %%cl\n\t"
    "jae 2f\n\t"
    "shrdl %%cl, %%edx, %%eax\n\t"
    "sarl %%cl, %%edx\n\t"
    "ret\n\t"
    "2:\n\t"
    "movl %%edx, %%eax\n\t"
    "sarl $0x1f, %%edx\n\t"
    "andb $0x1f, %%cl\n\t"
    "sarl %%cl, %%eax\n\t"
    "ret\n\t"
    "1:\n\t"
    "sarl $0x1f, %%edx\n\t"
    "movl %%edx, %%eax\n\t"
    "ret\n\t"
    ::: "memory");
}

/* FUN_001ddcc6 (0x1ddcc6) — Capstone tip: double exponent not-all-ones. */
int FUN_001ddcc6(unsigned low, unsigned high)
{
  unsigned short ax = (unsigned short)(high >> 16);
  (void)low;
  return (ax & 0x7ff0) != 0x7ff0;
}

/* __allmul (0x1dd620) — Capstone tip: 64x64→64 mul. */
__attribute__((naked, noinline))
void __allmul(void)
{
  __asm__ volatile(
    "movl 0x8(%%esp), %%eax\n\t"
    "movl 0x10(%%esp), %%ecx\n\t"
    "orl %%eax, %%ecx\n\t"
    "movl 0xc(%%esp), %%ecx\n\t"
    "jne 1f\n\t"
    "movl 0x4(%%esp), %%eax\n\t"
    "mull %%ecx\n\t"
    "ret $0x10\n\t"
    "1:\n\t"
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
    "ret $0x10\n\t"
    ::: "memory");
}

/* __copysign (0x1dd8fa) — Capstone tip: copy sign bit between doubles. */
__attribute__((naked, noinline))
void __copysign(void)
{
  __asm__ volatile(
    "pushl %%ebp\n\t"
    "movl %%esp, %%ebp\n\t"
    "pushl %%ecx\n\t"
    "pushl %%ecx\n\t"
    "movl 0x8(%%ebp), %%eax\n\t"
    "movl %%eax, -8(%%ebp)\n\t"
    "movl 0x14(%%ebp), %%eax\n\t"
    "xorl 0xc(%%ebp), %%eax\n\t"
    "andl $0x7fffffff, %%eax\n\t"
    "xorl 0x14(%%ebp), %%eax\n\t"
    "movl %%eax, -4(%%ebp)\n\t"
    "fldl -8(%%ebp)\n\t"
    "leave\n\t"
    "ret\n\t"
    ::: "memory");
}

/* _store_dt (0x1dd480) — Capstone tip: write two decimal digits as wchar. */
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
    "leal 2(%%ecx), %%eax\n\t"
    "ret\n\t"
    ::: "memory");
}
