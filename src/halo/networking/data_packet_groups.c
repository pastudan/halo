/* --- data_packet_groups.obj batch drafts (2026-07-26) --- */

/* 0x11abb0 */
void data_packet_group_append_packet_header(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;

  display_assert((char *)0x0028f318, (char *)0x0028f1f0, 172, 0);
  system_exit(0);
  /* relift: cmp word ptr [edi], 0 -> jge 0x11ac12 */
  display_assert((char *)0x0028f3c4, (char *)0x0028f1f0, 173, 0);
  system_exit(0);
  /* test (int16_t)ebx, (int16_t)ebx -> jl 0x11ac24 */
  /* relift: cmp (int16_t)ebx, word ptr [eax + 4] -> jl 0x11ac44 */
  display_assert((char *)0x0028f380, (char *)0x0028f1f0, 174, 0);
  system_exit(0);
  /* cmp ecx, eax -> jae 0x11ac7d */
  FUN_00118be0((void *)0x003220c0, (void *)(uintptr_t)esi, 0);
  /* mem[0x0046e804] = eax */
  /* mem[0x0046e804] = eax */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)esi;
  (void)edi;
}

/* 0x11aca0 */
bool encode_packet_group(group_definition *group, void *data, char *encoded_buf, int32_t *encoded_size, int16_t type, int one)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;

  display_assert((char *)0x0028f408, (char *)0x0028f1f0, 132, 0);
  system_exit(0);
  /* test (int16_t)esi, (int16_t)esi -> jl 0x11ace3 */
  /* relift: cmp (int16_t)esi, word ptr [edi + 4] -> jl 0x11ad03 */
  display_assert((char *)0x0028f380, (char *)0x0028f1f0, 133, 0);
  system_exit(0);
  /* test ebx, ebx -> je 0x11ad11 */
  /* test eax, eax -> jne 0x11ad31 */
  display_assert((char *)0x0028f318, (char *)0x0028f1f0, 134, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x11ad61 */
  display_assert((char *)0x0028f3f4, (char *)0x0028f1f0, 139, 0);
  system_exit(0);
  FUN_0011b650(0, 0, (void *)(uintptr_t)ecx, (char *)(uintptr_t)ebx, (void *)(uintptr_t)eax, 0);
  /* test (char)eax, (char)eax -> je 0x11ada2 */
  data_packet_group_append_packet_header();
  /* test (char)eax, (char)eax -> jne 0x11ada9 */
  /* mem[0x0046e804] = eax */
  return 0;

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)esi;
  (void)edi;
}

/* 0x11add0 */
void compute_packet_field_sizes(packet_definition *def, short *param_2, short *param_3, short *param_4)
{
  int eax = 0;
  int ecx = 0;
  int esi = 0;

  /* test (int16_t)eax, (int16_t)eax -> jl 0x11ae03 */
  /* cmp (int16_t)eax, 0xa -> jl 0x11ae34 */
  csprintf((char *)0x005ab100, (char *)0x0028f450);
  display_assert((char *)(uintptr_t)eax, (char *)0, 0, 0);
  system_exit(0);
  /* relift: cmp word ptr [esi + 2], 0 -> jg 0x11ae6c */
  csprintf((char *)0x005ab100, (char *)0x0028f41c);
  display_assert((char *)(uintptr_t)eax, (char *)0, 0, 0);
  system_exit(0);
  /* relift: cmp (int16_t)eax, word ptr [esi + 4] -> jl 0x11af20 */
  /* cmp (int16_t)eax, (int16_t)ecx -> jle 0x11ae8c */
  /* test (int16_t)ecx, (int16_t)ecx -> jne 0x11af20 */
  /* cmp eax, 9 -> ja 0x11af03 */
  /* relift: tail-call compute_packet_field_sizes(); */
  display_assert((char *)0, (char *)0x0028f498, 193, 0);
  system_exit(0);
  /* test ecx, ecx -> je 0x11af5d */

  (void)eax;
  (void)ecx;
  (void)esi;
}

/* _data_packet_encode (0x11afa0) — XBE naked draft (batch 109). */
#if defined(__clang__)
static int (*const b11afa0_c119cc0)(int *param_1, int param_2, short param_3, int param_4) = FUN_00119cc0;
static bool (*const b11afa0_c11a230)(int *state, const char *source, short max_length) = FUN_0011a230;
static void (*const b11afa0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b11afa0_exitfn)(int) = system_exit;
static bool (*const b11afa0_c119df0)(int *param_1, int param_2, int param_3) = FUN_00119df0;
static void (*const b11afa0_c11add0)(packet_definition *def, short *param_2, short *param_3, short *param_4) = compute_packet_field_sizes;
static void (*const b11afa0_c11afa0)(int param_1, int *param_2, short param_3, void *param_4, short param_5, int param_6, short *param_7) = _data_packet_encode;

__attribute__((naked, noinline))
void _data_packet_encode(int param_1 __attribute__((unused)), int *param_2 __attribute__((unused)), short param_3 __attribute__((unused)), void *param_4 __attribute__((unused)), short param_5 __attribute__((unused)), int param_6 __attribute__((unused)), short *param_7 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x18, %%esp\n\t"
      "movl 0x1c(%%ebp), %%eax\n\t"
      "cmpw $9, (%%eax)\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x14(%%ebp), %%edi\n\t"
      "movl %%eax, %%esi\n\t"
      "movl %%edi, -0x10(%%ebp)\n\t"
      "je .L_data_packet_encode_30\n\t"
      "pushl %%ebx\n\t"
      "movl 0xc(%%ebp), %%ebx\n\t"
      ".L_data_packet_encode_1:\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "cmpw 0x4(%%esi), %%cx\n\t"
      "jl .L_data_packet_encode_23\n\t"
      "movw 0x6(%%esi), %%ax\n\t"
      "cmpw %%ax, %%cx\n\t"
      "jle .L_data_packet_encode_2\n\t"
      "testw %%ax, %%ax\n\t"
      "jne .L_data_packet_encode_23\n\t"
      ".L_data_packet_encode_2:\n\t"
      "movswl (%%esi), %%eax\n\t"
      "cmpl $8, %%eax\n\t"
      "ja .L_data_packet_encode_22\n\t"
      "jmp *.L_data_packet_encode_jt0(,%%eax,4)\n\t"
      ".L_data_packet_encode_3:\n\t"
      "pushl $1\n\t"
      ".L_data_packet_encode_4:\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x2(%%esi), %%ax\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "call *%[c119cc0]\n\t"
      "addl $0x10, %%esp\n\t"
      "jmp .L_data_packet_encode_29\n\t"
      ".L_data_packet_encode_5:\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x2(%%esi), %%cx\n\t"
      "pushl $-2\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "call *%[c119cc0]\n\t"
      "addl $0x10, %%esp\n\t"
      "jmp .L_data_packet_encode_29\n\t"
      ".L_data_packet_encode_6:\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x2(%%esi), %%dx\n\t"
      "pushl $-4\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "call *%[c119cc0]\n\t"
      "addl $0x10, %%esp\n\t"
      "jmp .L_data_packet_encode_29\n\t"
      ".L_data_packet_encode_7:\n\t"
      "pushl $-8\n\t"
      "jmp .L_data_packet_encode_4\n\t"
      ".L_data_packet_encode_8:\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x2(%%esi), %%cx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "call *%[c11a230]\n\t"
      "addl $0xc, %%esp\n\t"
      "jmp .L_data_packet_encode_29\n\t"
      ".L_data_packet_encode_9:\n\t"
      "movw (%%edi), %%di\n\t"
      "testw %%di, %%di\n\t"
      "jl .L_data_packet_encode_10\n\t"
      "cmpw 0x2(%%esi), %%di\n\t"
      "jle .L_data_packet_encode_11\n\t"
      ".L_data_packet_encode_10:\n\t"
      "pushl $1\n\t"
      "pushl $0xfd\n\t"
      "pushl $0x28f498\n\t"
      "pushl $0x28f4f0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".L_data_packet_encode_11:\n\t"
      "testw %%di, %%di\n\t"
      "jl .L_data_packet_encode_12\n\t"
      "cmpw 0x2(%%esi), %%di\n\t"
      "jle .L_data_packet_encode_13\n\t"
      ".L_data_packet_encode_12:\n\t"
      "xorl %%edi, %%edi\n\t"
      ".L_data_packet_encode_13:\n\t"
      "movswl 0x2(%%esi), %%edx\n\t"
      "movswl %%di, %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "call *%[c119df0]\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "pushl $1\n\t"
      "pushl %%edi\n\t"
      "addl $2, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "call *%[c119cc0]\n\t"
      "movl -0x10(%%ebp), %%edi\n\t"
      "addl $0x1c, %%esp\n\t"
      "jmp .L_data_packet_encode_29\n\t"
      ".L_data_packet_encode_14:\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x2(%%esi), %%cx\n\t"
      "pushl $1\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "call *%[c119cc0]\n\t"
      "addl $0x10, %%esp\n\t"
      "jmp .L_data_packet_encode_29\n\t"
      ".L_data_packet_encode_15:\n\t"
      "movl -0x10(%%ebp), %%edx\n\t"
      "movw (%%edi), %%di\n\t"
      "leal -0xc(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "addl $2, %%edx\n\t"
      "leal 0xa(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl %%edx, -0x14(%%ebp)\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "pushl $0\n\t"
      "pushl %%edx\n\t"
      "call *%[c11add0]\n\t"
      "addl $0x10, %%esp\n\t"
      "testw %%di, %%di\n\t"
      "jl .L_data_packet_encode_16\n\t"
      "cmpw 0x2(%%esi), %%di\n\t"
      "jle .L_data_packet_encode_17\n\t"
      ".L_data_packet_encode_16:\n\t"
      "pushl $1\n\t"
      "pushl $0x119\n\t"
      "pushl $0x28f498\n\t"
      "pushl $0x28f4c0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".L_data_packet_encode_17:\n\t"
      "testw %%di, %%di\n\t"
      "jl .L_data_packet_encode_18\n\t"
      "cmpw 0x2(%%esi), %%di\n\t"
      "jle .L_data_packet_encode_19\n\t"
      ".L_data_packet_encode_18:\n\t"
      "xorl %%edi, %%edi\n\t"
      ".L_data_packet_encode_19:\n\t"
      "movswl 0x2(%%esi), %%eax\n\t"
      "movswl %%di, %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "call *%[c119df0]\n\t"
      "addl $0xc, %%esp\n\t"
      "testw %%di, %%di\n\t"
      "jle .L_data_packet_encode_21\n\t"
      "movzwl %%di, %%edx\n\t"
      "movl %%edx, -0x18(%%ebp)\n\t"
      "leal (%%esp), %%esp\n\t"
      ".L_data_packet_encode_20:\n\t"
      "movl -0x14(%%ebp), %%edi\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "pushl $0\n\t"
      "leal 0xa(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edx\n\t"
      "call *%[c11afa0]\n\t"
      "movswl -0x8(%%ebp), %%eax\n\t"
      "addl %%eax, %%edi\n\t"
      "movl -0x18(%%ebp), %%eax\n\t"
      "addl $0x1c, %%esp\n\t"
      "decl %%eax\n\t"
      "movl %%edi, -0x14(%%ebp)\n\t"
      "movl %%eax, -0x18(%%ebp)\n\t"
      "jne .L_data_packet_encode_20\n\t"
      ".L_data_packet_encode_21:\n\t"
      "movswl -0xc(%%ebp), %%eax\n\t"
      "movl -0x10(%%ebp), %%edi\n\t"
      "leal (%%eax,%%eax,4), %%ecx\n\t"
      "leal (%%esi,%%ecx,2), %%esi\n\t"
      "jmp .L_data_packet_encode_29\n\t"
      ".L_data_packet_encode_22:\n\t"
      "pushl $1\n\t"
      "pushl $0x129\n\t"
      "jmp .L_data_packet_encode_28\n\t"
      ".L_data_packet_encode_23:\n\t"
      "movswl (%%esi), %%eax\n\t"
      "cmpl $8, %%eax\n\t"
      "ja .L_data_packet_encode_27\n\t"
      "jmp *.L_data_packet_encode_jt1(,%%eax,4)\n\t"
      ".L_data_packet_encode_24:\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x2(%%esi), %%dx\n\t"
      "pushl $1\n\t"
      "pushl %%edx\n\t"
      "pushl $0\n\t"
      "pushl %%ebx\n\t"
      "call *%[c119cc0]\n\t"
      "addl $0x10, %%esp\n\t"
      "jmp .L_data_packet_encode_29\n\t"
      ".L_data_packet_encode_25:\n\t"
      "pushl $1\n\t"
      "pushl $1\n\t"
      "leal -0x1(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "call *%[c119cc0]\n\t"
      "addl $0x10, %%esp\n\t"
      "jmp .L_data_packet_encode_29\n\t"
      ".L_data_packet_encode_26:\n\t"
      "movswl 0x2(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0\n\t"
      "pushl %%ebx\n\t"
      "call *%[c119df0]\n\t"
      "addl $0xc, %%esp\n\t"
      "jmp .L_data_packet_encode_29\n\t"
      ".L_data_packet_encode_27:\n\t"
      "pushl $1\n\t"
      "pushl $0x144\n\t"
      ".L_data_packet_encode_28:\n\t"
      "pushl $0x28f498\n\t"
      "pushl $0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".L_data_packet_encode_29:\n\t"
      "movswl 0x8(%%esi), %%edx\n\t"
      "addl %%edx, %%edi\n\t"
      "addl $0xa, %%esi\n\t"
      "cmpw $9, (%%esi)\n\t"
      "movl %%edi, -0x10(%%ebp)\n\t"
      "jne .L_data_packet_encode_1\n\t"
      "movl 0x1c(%%ebp), %%eax\n\t"
      "popl %%ebx\n\t"
      ".L_data_packet_encode_30:\n\t"
      "movl 0x20(%%ebp), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .L_data_packet_encode_31\n\t"
      "subl %%eax, %%esi\n\t"
      "movl $0x66666667, %%eax\n\t"
      "imull %%esi\n\t"
      "sarl $2, %%edx\n\t"
      "movl %%edx, %%eax\n\t"
      "shrl $0x1f, %%eax\n\t"
      "leal 0x1(%%edx,%%eax,1), %%edx\n\t"
      "movw %%dx, (%%ecx)\n\t"
      ".L_data_packet_encode_31:\n\t"
      "movl 0x18(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .L_data_packet_encode_32\n\t"
      "subl 0x14(%%ebp), %%edi\n\t"
      "movw %%di, (%%eax)\n\t"
      ".L_data_packet_encode_32:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".L_data_packet_encode_jt0:\n\t"
      ".long .L_data_packet_encode_29\n\t"
      ".long .L_data_packet_encode_3\n\t"
      ".long .L_data_packet_encode_5\n\t"
      ".long .L_data_packet_encode_6\n\t"
      ".long .L_data_packet_encode_7\n\t"
      ".long .L_data_packet_encode_8\n\t"
      ".long .L_data_packet_encode_9\n\t"
      ".long .L_data_packet_encode_15\n\t"
      ".long .L_data_packet_encode_14\n\t"
      ".text\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".L_data_packet_encode_jt1:\n\t"
      ".long .L_data_packet_encode_29\n\t"
      ".long .L_data_packet_encode_24\n\t"
      ".long .L_data_packet_encode_24\n\t"
      ".long .L_data_packet_encode_24\n\t"
      ".long .L_data_packet_encode_24\n\t"
      ".long .L_data_packet_encode_25\n\t"
      ".long .L_data_packet_encode_26\n\t"
      ".long .L_data_packet_encode_26\n\t"
      ".long .L_data_packet_encode_24\n\t"
      ".text\n\t"
      :
      : [c119cc0] "m"(b11afa0_c119cc0), [c11a230] "m"(b11afa0_c11a230), [assert] "m"(b11afa0_assert), [exitfn] "m"(b11afa0_exitfn), [c119df0] "m"(b11afa0_c119df0), [c11add0] "m"(b11afa0_c11add0), [c11afa0] "m"(b11afa0_c11afa0)
      : "memory");
}
#else
#error "_data_packet_encode: clang naked draft required"
#endif

