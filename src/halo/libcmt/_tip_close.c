/* Tip-only compile unit for FUN_001e4422 Unicorn proof. */
int __stdcall FUN_001e4422(void *a, void *b)
{
  (void)b;
  ((void (__stdcall *)(void *))*(void **)0x253250)(a);
  return 1;
}

/* RtlUnwind (0x1e6584) — Capstone tip: IAT jmp [0x25331c]. */
void RtlUnwind(void)
{
  ((void (*)(void))*(void **)0x25331c)();
}

/* FUN_001defb3 (0x1defb3) — Capstone tip: LeaveCriticalSection on lock table. */
void FUN_001defb3(int lock_id)
{
  void *cs = *(void **)(0x3314e8 + lock_id * 8);
  ((void (__stdcall *)(void *))*(void **)0x253098)(cs);
}

/* ___addl (0x1e59e3) — Capstone tip: add with carry-out flag. */
unsigned int ___addl(unsigned int a, unsigned int b, unsigned int *out)
{
  unsigned sum = a + b;
  unsigned carry = (sum < a || sum < b) ? 1u : 0u;
  *out = sum;
  return carry;
}

/* __IsZeroMan (0x1e3db4) — Capstone tip: 3x dword all zero → 1. */
int __IsZeroMan(unsigned int *man)
{
  int i;
  for (i = 0; i < 3; i++) {
    if (man[i] != 0)
      return 0;
  }
  return 1;
}

/* __CopyMan (0x1e3d8d) — Capstone tip: copy 3 dwords dst←src. */
void __CopyMan(unsigned int *dst, unsigned int *src)
{
  int i;
  for (i = 0; i < 3; i++)
    dst[i] = src[i];
}

/* FUN_001dfd23 (0x1dfd23) — Capstone tip: frndint on stack double. */
__attribute__((naked, noinline))
void FUN_001dfd23(void)
{
  __asm__ volatile(
    "pushl %%ecx\n\t"
    "pushl %%ecx\n\t"
    "fldl 0xc(%%esp)\n\t"
    "frndint\n\t"
    "fstpl (%%esp)\n\t"
    "fldl (%%esp)\n\t"
    "popl %%ecx\n\t"
    "popl %%ecx\n\t"
    "ret\n\t"
    ::: "memory");
}

/* __set_bexp (0x1dfd9f) — Capstone tip: set biased exponent in double. */
__attribute__((naked, noinline))
void __set_bexp(void)
{
  __asm__ volatile(
    "pushl %%ebp\n\t"
    "movl %%esp, %%ebp\n\t"
    "pushl %%ecx\n\t"
    "pushl %%ecx\n\t"
    "movl 0x10(%%ebp), %%eax\n\t"
    "fldl 0x8(%%ebp)\n\t"
    "movl 0xe(%%ebp), %%ecx\n\t"
    "fstpl -8(%%ebp)\n\t"
    "shll $4, %%eax\n\t"
    "andl $0xffff800f, %%ecx\n\t"
    "orl %%ecx, %%eax\n\t"
    "movw %%ax, -2(%%ebp)\n\t"
    "fldl -8(%%ebp)\n\t"
    "leave\n\t"
    "ret\n\t"
    ::: "memory");
}

/* __set_exp (0x1dfd36) — Capstone tip: set unbiased exp (+0x3fe). */
__attribute__((naked, noinline))
void __set_exp(void)
{
  __asm__ volatile(
    "pushl %%ebp\n\t"
    "movl %%esp, %%ebp\n\t"
    "pushl %%ecx\n\t"
    "pushl %%ecx\n\t"
    "movl 0x10(%%ebp), %%eax\n\t"
    "fldl 0x8(%%ebp)\n\t"
    "movl 0xe(%%ebp), %%ecx\n\t"
    "fstpl -8(%%ebp)\n\t"
    "addl $0x3fe, %%eax\n\t"
    "shll $4, %%eax\n\t"
    "andl $0xffff800f, %%ecx\n\t"
    "orl %%ecx, %%eax\n\t"
    "movw %%ax, -2(%%ebp)\n\t"
    "fldl -8(%%ebp)\n\t"
    "leave\n\t"
    "ret\n\t"
    ::: "memory");
}

/* __ctrlfp (0x1dfeec) — Capstone tip: update x87 CW bits, return old. */
__attribute__((naked, noinline))
void __ctrlfp(void)
{
  __asm__ volatile(
    "pushl %%ebp\n\t"
    "movl %%esp, %%ebp\n\t"
    "pushl %%ecx\n\t"
    "wait\n\t"
    "fnstcw -4(%%ebp)\n\t"
    "movl 0xc(%%ebp), %%eax\n\t"
    "movl 0x8(%%ebp), %%ecx\n\t"
    "andl 0xc(%%ebp), %%ecx\n\t"
    "notl %%eax\n\t"
    "andl -4(%%ebp), %%eax\n\t"
    "orl %%ecx, %%eax\n\t"
    "movl %%eax, 0xc(%%ebp)\n\t"
    "fldcw 0xc(%%ebp)\n\t"
    "movswl -4(%%ebp), %%eax\n\t"
    "leave\n\t"
    "ret\n\t"
    ::: "memory");
}

/* __ZeroTail (0x1e3c9c) — Capstone tip: check mantissa tail bits zero. */
int __ZeroTail(unsigned int *man, int bit)
{
  int idx = bit / 32;
  int rem = bit % 32;
  unsigned int mask = ~(0xffffffffu << (31 - rem));
  if (man[idx] & mask)
    return 0;
  for (idx = idx + 1; idx < 3; idx++) {
    if (man[idx] != 0)
      return 0;
  }
  return 1;
}

/* FUN_001e2669 (0x1e2669) — Capstone tip: empty/null wchar helper. */
__attribute__((naked, noinline))
void FUN_001e2669(void)
{
  __asm__ volatile(
    "movl 0x8(%%esp), %%eax\n\t"
    "testl %%eax, %%eax\n\t"
    "je 1f\n\t"
    "cmpl $0, 0xc(%%esp)\n\t"
    "je 1f\n\t"
    "movb (%%eax), %%al\n\t"
    "testb %%al, %%al\n\t"
    "jne 2f\n\t"
    "movl 0x4(%%esp), %%eax\n\t"
    "testl %%eax, %%eax\n\t"
    "je 1f\n\t"
    "andw $0, (%%eax)\n\t"
    "1:\n\t"
    "xorl %%eax, %%eax\n\t"
    "ret\n\t"
    "2:\n\t"
    "movl 0x4(%%esp), %%ecx\n\t"
    "testl %%ecx, %%ecx\n\t"
    "je 3f\n\t"
    "movzbl %%al, %%eax\n\t"
    "movw %%ax, (%%ecx)\n\t"
    "3:\n\t"
    "xorl %%eax, %%eax\n\t"
    "incl %%eax\n\t"
    "ret\n\t"
    ::: "memory");
}

/* __unlock_fhandle (0x1e33c2) — Capstone tip: LeaveCriticalSection on fh lock. */
void __unlock_fhandle(int fd)
{
  int idx = fd & 0x1f;
  int bank = fd >> 5;
  char *base = *(char **)(0x632cc0 + bank * 4);
  void *cs = base + idx * 40 + 0xc; /* eax+eax*4 = *5, *8 = *40 */
  ((void (__stdcall *)(void *))*(void **)0x253098)(cs);
}

/* FUN_001dee48 (0x1dee48) — Capstone tip: masked exp field; Inf/NaN returns high. */
unsigned FUN_001dee48(unsigned low, unsigned high)
{
  (void)low;
  if ((high & 0x7ff00000u) != 0x7ff00000u)
    return high & 0x7ff00000u;
  return high;
}

/* ___shl_12 (0x1e5a62) — Capstone tip: shift 96-bit left by 1. */
void ___shl_12(unsigned *x)
{
  unsigned c0 = x[0] >> 31;
  unsigned c1 = x[1] >> 31;
  x[0] = x[0] + x[0];
  x[1] = (x[1] + x[1]) | c0;
  x[2] = (x[2] << 1) | c1;
}

/* ___shr_12 (0x1e5a90) — Capstone tip: shift 96-bit right by 1. */
void ___shr_12(unsigned *x)
{
  unsigned lo = x[0];
  unsigned mid = x[1];
  unsigned hi = x[2];
  x[1] = (mid >> 1) | (hi << 31);
  x[2] = hi >> 1;
  x[0] = (lo >> 1) | (mid << 31);
}

/* FUN_001e35a9 (0x1e35a9) — Capstone tip: wcsnlen-ish; empty → count. */
unsigned FUN_001e35a9(unsigned short *s, unsigned count)
{
  unsigned i;
  if (count == 0)
    return 0;
  for (i = 0; i < count; i++) {
    if (s[i] == 0)
      return i + 1;
  }
  return count;
}
