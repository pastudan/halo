/* --- transport_address.obj batch drafts (2026-07-26) --- */

/* transport_address_equivalent (0x81a90) — XBE naked draft (batch 133). */
#if defined(__clang__)
static void (*const b81a90_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b81a90_exitfn)(int) = system_exit;
static int (*const b81a90_c8da40)(const void *a, const void *b, int size) = csmemcmp;

__attribute__((naked, noinline))
void transport_address_equivalent(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "pushl %%edi\n\t"
      "jne .Ltransport_address_equivalent_1\n\t"
      "pushl $1\n\t"
      "pushl $0x3b\n\t"
      "pushl $0x265ffc\n\t"
      "pushl $0x266090\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Ltransport_address_equivalent_1:\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .Ltransport_address_equivalent_2\n\t"
      "pushl $1\n\t"
      "pushl $0x3c\n\t"
      "pushl $0x265ffc\n\t"
      "pushl $0x26608c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Ltransport_address_equivalent_2:\n\t"
      "movb 0x335090, %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Ltransport_address_equivalent_3\n\t"
      "pushl $1\n\t"
      "pushl $0x3d\n\t"
      "pushl $0x265ffc\n\t"
      "pushl $0x265fe4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Ltransport_address_equivalent_3:\n\t"
      "cmpw $4, 0x10(%%esi)\n\t"
      "je .Ltransport_address_equivalent_4\n\t"
      "pushl $1\n\t"
      "pushl $0x3f\n\t"
      "pushl $0x265ffc\n\t"
      "pushl $0x266060\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Ltransport_address_equivalent_4:\n\t"
      "cmpw $4, 0x10(%%edi)\n\t"
      "je .Ltransport_address_equivalent_5\n\t"
      "pushl $1\n\t"
      "pushl $0x40\n\t"
      "pushl $0x265ffc\n\t"
      "pushl $0x266034\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Ltransport_address_equivalent_5:\n\t"
      "movw 0x10(%%esi), %%ax\n\t"
      "movw 0x10(%%edi), %%cx\n\t"
      "cmpw %%cx, %%ax\n\t"
      "movzwl %%ax, %%eax\n\t"
      "ja .Ltransport_address_equivalent_6\n\t"
      "movzwl %%cx, %%eax\n\t"
      ".Ltransport_address_equivalent_6:\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%esi\n\t"
      "call *%[c8da40]\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Ltransport_address_equivalent_7\n\t"
      "movw 0x12(%%esi), %%ax\n\t"
      "cmpw 0x12(%%edi), %%ax\n\t"
      "jne .Ltransport_address_equivalent_7\n\t"
      "popl %%edi\n\t"
      "movl $1, %%eax\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Ltransport_address_equivalent_7:\n\t"
      "popl %%edi\n\t"
      "xorl %%eax, %%eax\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b81a90_assert), [exitfn] "m"(b81a90_exitfn), [c8da40] "m"(b81a90_c8da40)
      : "memory");
}
#else
#error "transport_address_equivalent: clang naked draft required"
#endif


/* 0x81b90 */
const char *transport_address_to_string(void *addr)
{
  int esi = 0;

  /* test esi, esi -> jne 0x81bb8 */
  display_assert((char *)0x002660f8, (char *)0x00265ffc, 74, 0);
  system_exit(0);
  /* relift: cmp word ptr [esi + 0x10], 4 -> je 0x81bdc */
  display_assert((char *)0x002660cc, (char *)0x00265ffc, 75, 0);
  system_exit(0);
  /* cmp (int16_t)eax, 4 -> jne 0x81c24 */
  snprintf((char *)0x00334f90, 256, (char *)0x002660b8);
  /* cmp (int16_t)eax, 0x10 -> jne 0x81c6d */
  snprintf((char *)0x00334f90, 256, (char *)0x00266094);
  return NULL;

  (void)esi;
}

/* 0x81c80 */
const char *FUN_00081c80(int error_code)
{
  int eax = 0;
  int ecx = 0;
  int esi = 0;

  /* cmp eax, 0x17 -> ja 0x81d42 */
  /* test esi, esi -> jne 0x81de1 */
  display_assert((char *)0x00266450, (char *)0x00266458, 57, 0);
  system_exit(0);
  /* cmp eax, ecx -> jle 0x81df6 */
  return NULL;

  (void)eax;
  (void)ecx;
  (void)esi;
}

/* FUN_00081e00 (0x81e00) — XBE naked draft (batch 147). */
#if defined(__clang__)
static void (*const b81e00_c222de0)(void) = (void (*)(void))FUN_00222df7;
static void (*const b81e00_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b81e00_exitfn)(int) = system_exit;

__attribute__((naked, noinline))
void FUN_00081e00(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "movl %%ecx, 0x5ab210\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl %%edx, 0x5ab214\n\t"
      "movl 0x8(%%eax), %%ecx\n\t"
      "movl %%ecx, 0x5ab218\n\t"
      "movl 0xc(%%eax), %%edx\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "movl %%edx, 0x5ab21c\n\t"
      "movl (%%eax), %%ecx\n\t"
      "movl %%ecx, 0x5ab220\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl 0x335094, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%edx, 0x5ab224\n\t"
      "jne .LFUN_00081e00_1\n\t"
      "pushl $0x5ab210\n\t"
      "pushl $0x5ab220\n\t"
      "call *%[c222de0]\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_00081e00_1\n\t"
      "pushl $1\n\t"
      "pushl $0x5c\n\t"
      "pushl $0x266458\n\t"
      "pushl $0x26649c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00081e00_1:\n\t"
      "incl 0x335094\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c222de0] "m"(b81e00_c222de0), [assert] "m"(b81e00_assert), [exitfn] "m"(b81e00_exitfn)
      : "memory");
}
#else
#error "FUN_00081e00: clang naked draft required"
#endif

