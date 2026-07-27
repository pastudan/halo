/* FUN_0017ff50: stub (0x17ff50) */
void FUN_0017ff50(void)
{
}

/* rasterizer_frame_statistics.c */

/* FUN_0017ff60 (0x17ff60) — readable C lift. */
extern char DAT_002af728[];
void FUN_0017ff60(void)
{
  void *p;

  p = *(void **)0x47ec40;
  if (p != NULL)
    FUN_0008ef70(p, DAT_002af728, 0x345);
}

/* rasterizer_geometry.c */

/* scale byte 0-255 to float via constant at 0x261518 (0x17ff80) */
float FUN_0017ff80(unsigned char param_1)
{
  return (float)param_1 * *(float *)0x261518;
}

/* scale signed short to float: (2*param_1 + 1.0f) * scale (0x17ffa0) */
float FUN_0017ffa0(short param_1)
{
  return ((float)(int)param_1 + (float)(int)param_1 + *(float *)0x2533c8) *
         *(float *)0x2647f4;
}

/* decode packed 32-bit normal to float[3] output, returns param_1 (0x17ffc0) */
float *FUN_0017ffc0(float *param_1, unsigned int param_2)
{
  float fVar1;
  fVar1 = (float)(int)((param_2 >> 0xb) << 0x15) * *(float *)0x29ba04;
  *param_1 =
    ((float)(int)(param_2 << 0x15) * *(float *)0x29ba04 + *(float *)0x2533c8) *
    *(float *)0x2afe34;
  param_1[1] = (fVar1 + *(float *)0x2533c8) * *(float *)0x2afe34;
  param_1[2] = ((float)(int)(param_2 & 0xffc00000) * *(float *)0x2afe30 +
                *(float *)0x2533c8) *
               *(float *)0x28c8e0;
  return param_1;
}

/* FUN_00180050 (0x180050) — readable C lift from XBE leaf. */
int FUN_00180050(short param_1)
{
  extern char DAT_002a0228[];
  extern char DAT_002afe38[];

  if (param_1 < 0 || param_1 >= 0xc) {
    display_assert(DAT_002a0228, DAT_002afe38, 0xaa, true);
    system_exit(-1);
  }
  return (int)*(short *)(0x2afe14 + (int)param_1 * 2);
}




/* FUN_001800b0 (0x1800b0) — XBE naked draft (batch 79). */
#if defined(__clang__)
static void (*const b1800b0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1800b0_exitfn)(int) = system_exit;
static void (*const b1800b0_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;
static float * (*const b1800b0_c17ffc0)(float *param_1, unsigned int param_2) = FUN_0017ffc0;

__attribute__((naked, noinline))
void FUN_001800b0(short param_1 __attribute__((unused)), int param_2 __attribute__((unused)), int param_3 __attribute__((unused)), int param_4 __attribute__((unused)), int param_5 __attribute__((unused)), int param_6 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x24, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x10(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "pushl %%edi\n\t"
      "jne .LFUN_001800b0_1\n\t"
      "pushl $1\n\t"
      "pushl $0x118\n\t"
      "pushl $0x2afe38\n\t"
      "pushl $0x2b0084\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001800b0_1:\n\t"
      "movl 0x18(%%ebp), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .LFUN_001800b0_2\n\t"
      "pushl $1\n\t"
      "pushl $0x119\n\t"
      "pushl $0x2afe38\n\t"
      "pushl $0x263b58\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001800b0_2:\n\t"
      "movswl 0x8(%%ebp), %%eax\n\t"
      "decl %%eax\n\t"
      "je .LFUN_001800b0_13\n\t"
      "subl $2, %%eax\n\t"
      "je .LFUN_001800b0_9\n\t"
      "subl $2, %%eax\n\t"
      "je .LFUN_001800b0_3\n\t"
      "pushl $0x2b004c\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001800b0_3:\n\t"
      "movl 0xc(%%ebp), %%ebx\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      "movl %%ebx, %%eax\n\t"
      "imull $0x44, %%eax, %%eax\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "je .LFUN_001800b0_4\n\t"
      "pushl $1\n\t"
      "pushl $0x145\n\t"
      "pushl $0x2afe38\n\t"
      "pushl $0x2b0008\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001800b0_4:\n\t"
      "movl 0x1c(%%ebp), %%eax\n\t"
      "movl %%ebx, %%ecx\n\t"
      "shll $5, %%ecx\n\t"
      "cmpl %%eax, %%ecx\n\t"
      "je .LFUN_001800b0_5\n\t"
      "pushl $1\n\t"
      "pushl $0x146\n\t"
      "pushl $0x2afe38\n\t"
      "pushl $0x2affc4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001800b0_5:\n\t"
      "testl %%ebx, %%ebx\n\t"
      "jle .LFUN_001800b0_17\n\t"
      "addl $0x18, %%esi\n\t"
      "addl $0x10, %%edi\n\t"
      "nop\n\t"
      ".LFUN_001800b0_6:\n\t"
      "leal -0x10(%%edi), %%edx\n\t"
      "movl (%%edx), %%ecx\n\t"
      "leal -0x18(%%esi), %%eax\n\t"
      "movl %%ecx, (%%eax)\n\t"
      "movl 0x4(%%edx), %%ecx\n\t"
      "movl %%ecx, 0x4(%%eax)\n\t"
      "movl 0x8(%%edx), %%edx\n\t"
      "movl %%edx, 0x8(%%eax)\n\t"
      "movl -0x4(%%edi), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0xc(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c17ffc0]\n\t"
      "movl (%%eax), %%ecx\n\t"
      "leal -0xc(%%esi), %%edx\n\t"
      "movl %%ecx, (%%edx)\n\t"
      "movl 0x4(%%eax), %%ecx\n\t"
      "movl %%ecx, 0x4(%%edx)\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl %%eax, 0x8(%%edx)\n\t"
      "movl (%%edi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x18(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c17ffc0]\n\t"
      "movl (%%eax), %%edx\n\t"
      "movl %%esi, %%ecx\n\t"
      "movl %%edx, (%%ecx)\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl %%edx, 0x4(%%ecx)\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl %%eax, 0x8(%%ecx)\n\t"
      "movl 0x4(%%edi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x24(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c17ffc0]\n\t"
      "movl (%%eax), %%edx\n\t"
      "leal 0xc(%%esi), %%ecx\n\t"
      "movl %%edx, (%%ecx)\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl %%edx, 0x4(%%ecx)\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl %%eax, 0x8(%%ecx)\n\t"
      "movswl 0x8(%%edi), %%ecx\n\t"
      "movl %%ecx, 0x8(%%ebp)\n\t"
      "movl $3, %%ecx\n\t"
      "addl $0x18, %%esp\n\t"
      "fildl 0x8(%%ebp)\n\t"
      ".byte 0xdc, 0xc0\n\t"
      "fadds 0x2533c8\n\t"
      "fmuls 0x2647f4\n\t"
      "fstps 0x18(%%esi)\n\t"
      "movswl 0xa(%%edi), %%edx\n\t"
      "movl %%edx, 0x8(%%ebp)\n\t"
      "fildl 0x8(%%ebp)\n\t"
      ".byte 0xdc, 0xc0\n\t"
      "fadds 0x2533c8\n\t"
      "fmuls 0x2647f4\n\t"
      "fstps 0x1c(%%esi)\n\t"
      "movzbl 0xc(%%edi), %%eax\n\t"
      "cdq\n\t"
      "idivl %%ecx\n\t"
      "testl %%edx, %%edx\n\t"
      "je .LFUN_001800b0_7\n\t"
      "pushl $1\n\t"
      "pushl $0x155\n\t"
      "pushl $0x2afe38\n\t"
      "pushl $0x2affb0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001800b0_7:\n\t"
      "movzbl 0xd(%%edi), %%eax\n\t"
      "cdq\n\t"
      "movl $3, %%ecx\n\t"
      "idivl %%ecx\n\t"
      "testl %%edx, %%edx\n\t"
      "je .LFUN_001800b0_8\n\t"
      "pushl $1\n\t"
      "pushl $0x156\n\t"
      "pushl $0x2afe38\n\t"
      "pushl $0x2aff9c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001800b0_8:\n\t"
      "movzbl 0xc(%%edi), %%ecx\n\t"
      "movl $0x55555556, %%eax\n\t"
      "imull %%ecx\n\t"
      "movl %%edx, %%eax\n\t"
      "shrl $0x1f, %%eax\n\t"
      "addl %%eax, %%edx\n\t"
      "movw %%dx, 0x20(%%esi)\n\t"
      "movzbl 0xd(%%edi), %%ecx\n\t"
      "movl $0x55555556, %%eax\n\t"
      "imull %%ecx\n\t"
      "movl %%edx, %%ecx\n\t"
      "shrl $0x1f, %%ecx\n\t"
      "addl %%ecx, %%edx\n\t"
      "movw %%dx, 0x22(%%esi)\n\t"
      "movzbl 0xe(%%edi), %%edx\n\t"
      "movl %%edx, 0x8(%%ebp)\n\t"
      "addl $0x44, %%esi\n\t"
      "addl $0x20, %%edi\n\t"
      "decl %%ebx\n\t"
      "fildl 0x8(%%ebp)\n\t"
      "fmuls 0x261518\n\t"
      "fsts -0x20(%%esi)\n\t"
      "flds 0x2533c8\n\t"
      ".byte 0xd8, 0xe1\n\t"
      "fstps -0x1c(%%esi)\n\t"
      "fstp %%st(0)\n\t"
      "jne .LFUN_001800b0_6\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001800b0_9:\n\t"
      "movl 0xc(%%ebp), %%ebx\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      "leal (%%ebx,%%ebx,4), %%eax\n\t"
      "shll $2, %%eax\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "je .LFUN_001800b0_10\n\t"
      "pushl $1\n\t"
      "pushl $0x133\n\t"
      "pushl $0x2afe38\n\t"
      "pushl $0x2aff48\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001800b0_10:\n\t"
      "movl 0x1c(%%ebp), %%eax\n\t"
      "leal (,%%ebx,8), %%ecx\n\t"
      "cmpl %%eax, %%ecx\n\t"
      "je .LFUN_001800b0_11\n\t"
      "pushl $1\n\t"
      "pushl $0x134\n\t"
      "pushl $0x2afe38\n\t"
      "pushl $0x2afef8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001800b0_11:\n\t"
      "testl %%ebx, %%ebx\n\t"
      "jle .LFUN_001800b0_17\n\t"
      "addl $0x10, %%esi\n\t"
      "addl $6, %%edi\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_001800b0_12:\n\t"
      "movl -0x6(%%edi), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x24(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c17ffc0]\n\t"
      "movl (%%eax), %%edx\n\t"
      "leal -0x10(%%esi), %%ecx\n\t"
      "movl %%edx, (%%ecx)\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl %%edx, 0x4(%%ecx)\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl %%eax, 0x8(%%ecx)\n\t"
      "movswl -0x2(%%edi), %%ecx\n\t"
      "movl %%ecx, 0x8(%%ebp)\n\t"
      "addl $8, %%esp\n\t"
      "addl $0x14, %%esi\n\t"
      "fildl 0x8(%%ebp)\n\t"
      "addl $8, %%edi\n\t"
      "decl %%ebx\n\t"
      ".byte 0xdc, 0xc0\n\t"
      "fadds 0x2533c8\n\t"
      "fmuls 0x2647f4\n\t"
      "fstps -0x18(%%esi)\n\t"
      "movswl -0x8(%%edi), %%edx\n\t"
      "movl %%edx, 0x8(%%ebp)\n\t"
      "fildl 0x8(%%ebp)\n\t"
      ".byte 0xdc, 0xc0\n\t"
      "fadds 0x2533c8\n\t"
      "fmuls 0x2647f4\n\t"
      "fstps -0x14(%%esi)\n\t"
      "jne .LFUN_001800b0_12\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001800b0_13:\n\t"
      "movl 0xc(%%ebp), %%ebx\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      "movl %%ebx, %%eax\n\t"
      "imull $0x38, %%eax, %%eax\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "je .LFUN_001800b0_14\n\t"
      "pushl $1\n\t"
      "pushl $0x11f\n\t"
      "pushl $0x2afe38\n\t"
      "pushl $0x2afeb0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001800b0_14:\n\t"
      "movl 0x1c(%%ebp), %%eax\n\t"
      "movl %%ebx, %%ecx\n\t"
      "shll $5, %%ecx\n\t"
      "cmpl %%eax, %%ecx\n\t"
      "je .LFUN_001800b0_15\n\t"
      "pushl $1\n\t"
      "pushl $0x120\n\t"
      "pushl $0x2afe38\n\t"
      "pushl $0x2afe68\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001800b0_15:\n\t"
      "testl %%ebx, %%ebx\n\t"
      "jle .LFUN_001800b0_17\n\t"
      "addl $0x18, %%esi\n\t"
      "addl $0x10, %%edi\n\t"
      ".LFUN_001800b0_16:\n\t"
      "leal -0x10(%%edi), %%edx\n\t"
      "movl (%%edx), %%ecx\n\t"
      "leal -0x18(%%esi), %%eax\n\t"
      "movl %%ecx, (%%eax)\n\t"
      "movl 0x4(%%edx), %%ecx\n\t"
      "movl %%ecx, 0x4(%%eax)\n\t"
      "movl 0x8(%%edx), %%edx\n\t"
      "movl %%edx, 0x8(%%eax)\n\t"
      "movl -0x4(%%edi), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x24(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c17ffc0]\n\t"
      "movl (%%eax), %%ecx\n\t"
      "leal -0xc(%%esi), %%edx\n\t"
      "movl %%ecx, (%%edx)\n\t"
      "movl 0x4(%%eax), %%ecx\n\t"
      "movl %%ecx, 0x4(%%edx)\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl %%eax, 0x8(%%edx)\n\t"
      "movl (%%edi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x18(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c17ffc0]\n\t"
      "movl (%%eax), %%edx\n\t"
      "movl %%esi, %%ecx\n\t"
      "movl %%edx, (%%ecx)\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl %%edx, 0x4(%%ecx)\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl %%eax, 0x8(%%ecx)\n\t"
      "movl 0x4(%%edi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0xc(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c17ffc0]\n\t"
      "movl (%%eax), %%edx\n\t"
      "leal 0xc(%%esi), %%ecx\n\t"
      "movl %%edx, (%%ecx)\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl %%edx, 0x4(%%ecx)\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl %%eax, 0x8(%%ecx)\n\t"
      "movl 0x8(%%edi), %%ecx\n\t"
      "movl %%ecx, 0x18(%%esi)\n\t"
      "movl 0xc(%%edi), %%edx\n\t"
      "movl %%edx, 0x1c(%%esi)\n\t"
      "addl $0x18, %%esp\n\t"
      "addl $0x38, %%esi\n\t"
      "addl $0x20, %%edi\n\t"
      "decl %%ebx\n\t"
      "jne .LFUN_001800b0_16\n\t"
      ".LFUN_001800b0_17:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b1800b0_assert), [exitfn] "m"(b1800b0_exitfn), [c8f390] "m"(b1800b0_c8f390), [c17ffc0] "m"(b1800b0_c17ffc0)
      : "memory");
}
#else
#error "FUN_001800b0: clang naked draft required"
#endif


/* FUN_00180500 (0x180500) — XBE naked draft (batch 93). */
#if defined(__clang__)
static void (*const b180500_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b180500_exitfn)(int) = system_exit;

__attribute__((naked, noinline))
void FUN_00180500(float *param_1 __attribute__((unused)), float *param_2 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "pushl %%edi\n\t"
      "jne .LFUN_00180500_1\n\t"
      "pushl $1\n\t"
      "pushl $0x1b6\n\t"
      "pushl $0x2afe38\n\t"
      "pushl $0x29cb70\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00180500_1:\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .LFUN_00180500_2\n\t"
      "pushl $1\n\t"
      "pushl $0x1b7\n\t"
      "pushl $0x2afe38\n\t"
      "pushl $0x25bb20\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00180500_2:\n\t"
      "movl (%%esi), %%eax\n\t"
      "movl %%eax, (%%edi)\n\t"
      "movl 0x4(%%esi), %%ecx\n\t"
      "movl %%ecx, 0x4(%%edi)\n\t"
      "movl 0x8(%%esi), %%edx\n\t"
      "movl %%edx, 0x8(%%edi)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b180500_assert), [exitfn] "m"(b180500_exitfn)
      : "memory");
}
#else
#error "FUN_00180500: clang naked draft required"
#endif


/* rasterizer_geometry_vertex_get_normal: unpack normal from compressed vertex
 * +0xc (0x180570) */
void FUN_00180570(int param_1, float *param_2)
{
  float local_out[3];
  float *result;
  if (param_1 == 0) {
    display_assert("vertex",
                   "c:\\halo\\SOURCE\\rasterizer\\rasterizer_geometry.c", 0x1c2,
                   1);
    system_exit(-1);
  }
  if (param_2 == 0) {
    display_assert("normal",
                   "c:\\halo\\SOURCE\\rasterizer\\rasterizer_geometry.c", 0x1c3,
                   1);
    system_exit(-1);
  }
  result = FUN_0017ffc0(local_out, *(unsigned int *)(param_1 + 0x0c));
  param_2[0] = result[0];
  param_2[1] = result[1];
  param_2[2] = result[2];
}

/* FUN_001805f0 (0x1805f0) — XBE naked draft (batch 94). */
#if defined(__clang__)
static void (*const b1805f0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1805f0_exitfn)(int) = system_exit;

__attribute__((naked, noinline))
void FUN_001805f0(int param_1 __attribute__((unused)), float *param_2 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "pushl %%edi\n\t"
      "jne .LFUN_001805f0_1\n\t"
      "pushl $1\n\t"
      "pushl $0x1ce\n\t"
      "pushl $0x2afe38\n\t"
      "pushl $0x29cb70\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001805f0_1:\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .LFUN_001805f0_2\n\t"
      "pushl $1\n\t"
      "pushl $0x1cf\n\t"
      "pushl $0x2afe38\n\t"
      "pushl $0x2b0094\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001805f0_2:\n\t"
      "movl 0x18(%%esi), %%eax\n\t"
      "movl %%eax, (%%edi)\n\t"
      "movl 0x1c(%%esi), %%ecx\n\t"
      "movl %%ecx, 0x4(%%edi)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b1805f0_assert), [exitfn] "m"(b1805f0_exitfn)
      : "memory");
}
#else
#error "FUN_001805f0: clang naked draft required"
#endif


/* rasterizer_geometry_vertex_get_normal_packed: unpack normal from packed value
 * ptr (0x180660) */
void FUN_00180660(unsigned int *param_1, float *param_2)
{
  float local_out[3];
  float *result;
  if (param_1 == 0) {
    display_assert("vertex",
                   "c:\\halo\\SOURCE\\rasterizer\\rasterizer_geometry.c", 0x1da,
                   1);
    system_exit(-1);
  }
  if (param_2 == 0) {
    display_assert("normal",
                   "c:\\halo\\SOURCE\\rasterizer\\rasterizer_geometry.c", 0x1db,
                   1);
    system_exit(-1);
  }
  result = FUN_0017ffc0(local_out, *param_1);
  param_2[0] = result[0];
  param_2[1] = result[1];
  param_2[2] = result[2];
}

/* rasterizer_geometry_vertex_get_texcoord_short: decode compressed short
 * texcoords from vertex to float[2] output (0x1806e0) */
void FUN_001806e0(int param_1, float *param_2)
{
  if (param_1 == 0) {
    display_assert("vertex",
                   "c:\\halo\\SOURCE\\rasterizer\\rasterizer_geometry.c", 0x1e6,
                   1);
    system_exit(-1);
  }
  if (param_2 == 0) {
    display_assert("texcoord",
                   "c:\\halo\\SOURCE\\rasterizer\\rasterizer_geometry.c", 0x1e7,
                   1);
    system_exit(-1);
  }
  *param_2 = ((float)(int)*(short *)(param_1 + 4) +
              (float)(int)*(short *)(param_1 + 4) + *(float *)0x2533c8) *
             *(float *)0x2647f4;
  param_2[1] = ((float)(int)*(short *)(param_1 + 6) +
                (float)(int)*(short *)(param_1 + 6) + *(float *)0x2533c8) *
               *(float *)0x2647f4;
}

extern double floor(double);

/* FUN_001807d0 (0x1807d0) — XBE naked draft (batch 354). */
#if defined(__clang__)


__attribute__((naked, noinline))
unsigned char FUN_001807d0(float param_1 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "flds 0x8(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_001807d0_1\n\t"
      "flds 0x2533c0\n\t"
      "jmp .LFUN_001807d0_3\n\t"
      ".LFUN_001807d0_1:\n\t"
      "flds 0x8(%%ebp)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_001807d0_2\n\t"
      "flds 0x2533c8\n\t"
      "jmp .LFUN_001807d0_3\n\t"
      ".LFUN_001807d0_2:\n\t"
      "flds 0x8(%%ebp)\n\t"
      ".LFUN_001807d0_3:\n\t"
      "fmuls 0x2602c8\n\t"
      "fstps 0x8(%%ebp)\n\t"
      "flds 0x8(%%ebp)\n\t"
      "fistps -0x4(%%ebp)\n\t"
      "movb -0x4(%%ebp), %%al\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "FUN_001807d0: clang naked draft required"
#endif


/* FUN_001808f0 (0x1808f0) — XBE naked draft (batch 317). */
#if defined(__clang__)
static void (*const b1808f0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1808f0_exitfn)(int) = system_exit;
static char * (*const b1808f0_c8d9d0)(char *buffer, const char *format, ...) = csprintf;
static double (*const b1808f0_c1d9c2b)(double x) = floor;
static float * (*const b1808f0_c17ffc0)(float *param_1, unsigned int param_2) = FUN_0017ffc0;

__attribute__((naked, noinline))
unsigned int FUN_001808f0(float *param_1 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x10, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "pushl %%edi\n\t"
      "jne .LFUN_001808f0_1\n\t"
      "pushl $1\n\t"
      "pushl $0x45\n\t"
      "pushl $0x2afe38\n\t"
      "pushl $0x2a3e7c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001808f0_1:\n\t"
      "flds (%%esi)\n\t"
      "fcomps 0x255e94\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_001808f0_2\n\t"
      "flds (%%esi)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .LFUN_001808f0_2\n\t"
      "flds 0x4(%%esi)\n\t"
      "fcomps 0x255e94\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_001808f0_2\n\t"
      "flds 0x4(%%esi)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .LFUN_001808f0_2\n\t"
      "flds 0x8(%%esi)\n\t"
      "fcomps 0x255e94\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_001808f0_2\n\t"
      "flds 0x8(%%esi)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jnp .LFUN_001808f0_3\n\t"
      ".LFUN_001808f0_2:\n\t"
      "movl 0x8(%%esi), %%eax\n\t"
      "flds 0x8(%%esi)\n\t"
      "movl 0x4(%%esi), %%ecx\n\t"
      "movl (%%esi), %%edx\n\t"
      "pushl $1\n\t"
      "pushl $0x4e\n\t"
      "pushl $0x2afe38\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "subl $0x18, %%esp\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds 0x4(%%esi)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds (%%esi)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x2b011c\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x2c, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001808f0_3:\n\t"
      "flds (%%esi)\n\t"
      "subl $8, %%esp\n\t"
      "fmuls 0x2b0118\n\t"
      "fstpl (%%esp)\n\t"
      "call *%[c1d9c2b]\n\t"
      "fstps 0x8(%%ebp)\n\t"
      "addl $8, %%esp\n\t"
      "flds 0x8(%%ebp)\n\t"
      "fistps -0x4(%%ebp)\n\t"
      "flds 0x4(%%esi)\n\t"
      "fmuls 0x2b0118\n\t"
      "movl -0x4(%%ebp), %%edi\n\t"
      "subl $8, %%esp\n\t"
      "andl $0x7ff, %%edi\n\t"
      "fstpl (%%esp)\n\t"
      "call *%[c1d9c2b]\n\t"
      "fstps 0x8(%%ebp)\n\t"
      "addl $8, %%esp\n\t"
      "flds 0x8(%%ebp)\n\t"
      "fistps -0x4(%%ebp)\n\t"
      "flds 0x8(%%esi)\n\t"
      "fmuls 0x2b0114\n\t"
      "movl -0x4(%%ebp), %%ebx\n\t"
      "subl $8, %%esp\n\t"
      "andl $0x7ff, %%ebx\n\t"
      "fstpl (%%esp)\n\t"
      "call *%[c1d9c2b]\n\t"
      "fstps 0x8(%%ebp)\n\t"
      "addl $8, %%esp\n\t"
      "flds 0x8(%%ebp)\n\t"
      "fistps -0x4(%%ebp)\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "andl $0x3ff, %%eax\n\t"
      "shll $0xb, %%eax\n\t"
      "orl %%ebx, %%eax\n\t"
      "shll $0xb, %%eax\n\t"
      "movl %%eax, %%ebx\n\t"
      "orl %%edi, %%ebx\n\t"
      "leal -0x10(%%ebp), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "call *%[c17ffc0]\n\t"
      "movl (%%eax), %%ecx\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl %%ecx, -0x10(%%ebp)\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fsubs (%%esi)\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "addl $8, %%esp\n\t"
      "movl %%edx, -0xc(%%ebp)\n\t"
      "fabs\n\t"
      "fcompl 0x28b800\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .LFUN_001808f0_4\n\t"
      "pushl $1\n\t"
      "pushl $0x5c\n\t"
      "pushl $0x2afe38\n\t"
      "pushl $0x2b00fc\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001808f0_4:\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fsubs 0x4(%%esi)\n\t"
      "fabs\n\t"
      "fcompl 0x28b800\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .LFUN_001808f0_5\n\t"
      "pushl $1\n\t"
      "pushl $0x5d\n\t"
      "pushl $0x2afe38\n\t"
      "pushl $0x2b00e4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001808f0_5:\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fsubs 0x8(%%esi)\n\t"
      "fabs\n\t"
      "fcompl 0x28b800\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .LFUN_001808f0_6\n\t"
      "pushl $1\n\t"
      "pushl $0x5e\n\t"
      "pushl $0x2afe38\n\t"
      "pushl $0x2b00cc\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001808f0_6:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebx, %%eax\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b1808f0_assert), [exitfn] "m"(b1808f0_exitfn), [c8d9d0] "m"(b1808f0_c8d9d0), [c1d9c2b] "m"(b1808f0_c1d9c2b), [c17ffc0] "m"(b1808f0_c17ffc0)
      : "memory");
}
#else
#error "FUN_001808f0: clang naked draft required"
#endif


/* FUN_00180b10 (0x180b10) — XBE naked draft (batch 305). */
#if defined(__clang__)
static void (*const b180b10_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b180b10_exitfn)(int) = system_exit;
static double (*const b180b10_c1d9c2b)(double x) = floor;
static float * (*const b180b10_c17ffc0)(float *param_1, unsigned int param_2) = FUN_0017ffc0;

__attribute__((naked, noinline))
unsigned int FUN_00180b10(float *param_1 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x10, %%esp\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "pushl %%edi\n\t"
      "jne .LFUN_00180b10_1\n\t"
      "pushl $1\n\t"
      "pushl $0x68\n\t"
      "pushl $0x2afe38\n\t"
      "pushl $0x2a3e7c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00180b10_1:\n\t"
      "flds (%%esi)\n\t"
      "fcomps 0x255e94\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00180b10_2\n\t"
      "flds 0x255e94\n\t"
      "jmp .LFUN_00180b10_4\n\t"
      ".LFUN_00180b10_2:\n\t"
      "flds (%%esi)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00180b10_3\n\t"
      "flds 0x2533c8\n\t"
      "jmp .LFUN_00180b10_4\n\t"
      ".LFUN_00180b10_3:\n\t"
      "flds (%%esi)\n\t"
      ".LFUN_00180b10_4:\n\t"
      "fmuls 0x2b0118\n\t"
      "pushl %%ebx\n\t"
      "subl $8, %%esp\n\t"
      "fstpl (%%esp)\n\t"
      "call *%[c1d9c2b]\n\t"
      "fstps 0x8(%%ebp)\n\t"
      "addl $8, %%esp\n\t"
      "flds 0x8(%%ebp)\n\t"
      "fistps -0x4(%%ebp)\n\t"
      "flds 0x4(%%esi)\n\t"
      "fcomps 0x255e94\n\t"
      "movl -0x4(%%ebp), %%ebx\n\t"
      "andl $0x7ff, %%ebx\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00180b10_5\n\t"
      "flds 0x255e94\n\t"
      "jmp .LFUN_00180b10_7\n\t"
      ".LFUN_00180b10_5:\n\t"
      "flds 0x4(%%esi)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00180b10_6\n\t"
      "flds 0x2533c8\n\t"
      "jmp .LFUN_00180b10_7\n\t"
      ".LFUN_00180b10_6:\n\t"
      "flds 0x4(%%esi)\n\t"
      ".LFUN_00180b10_7:\n\t"
      "fmuls 0x2b0118\n\t"
      "subl $8, %%esp\n\t"
      "fstpl (%%esp)\n\t"
      "call *%[c1d9c2b]\n\t"
      "fstps 0x8(%%ebp)\n\t"
      "addl $8, %%esp\n\t"
      "flds 0x8(%%ebp)\n\t"
      "fistps -0x4(%%ebp)\n\t"
      "flds 0x8(%%esi)\n\t"
      "fcomps 0x255e94\n\t"
      "movl -0x4(%%ebp), %%edi\n\t"
      "andl $0x7ff, %%edi\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00180b10_8\n\t"
      "flds 0x255e94\n\t"
      "jmp .LFUN_00180b10_10\n\t"
      ".LFUN_00180b10_8:\n\t"
      "flds 0x8(%%esi)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00180b10_9\n\t"
      "flds 0x2533c8\n\t"
      "jmp .LFUN_00180b10_10\n\t"
      ".LFUN_00180b10_9:\n\t"
      "flds 0x8(%%esi)\n\t"
      ".LFUN_00180b10_10:\n\t"
      "fmuls 0x2b0114\n\t"
      "subl $8, %%esp\n\t"
      "fstpl (%%esp)\n\t"
      "call *%[c1d9c2b]\n\t"
      "fstps 0x8(%%ebp)\n\t"
      "addl $8, %%esp\n\t"
      "flds 0x8(%%ebp)\n\t"
      "fistps -0x4(%%ebp)\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "andl $0x3ff, %%eax\n\t"
      "shll $0xb, %%eax\n\t"
      "orl %%edi, %%eax\n\t"
      "shll $0xb, %%eax\n\t"
      "movl %%eax, %%edi\n\t"
      "orl %%ebx, %%edi\n\t"
      "leal -0x10(%%ebp), %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[c17ffc0]\n\t"
      "movl (%%eax), %%ecx\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl %%ecx, -0x10(%%ebp)\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fsubs (%%esi)\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "addl $8, %%esp\n\t"
      "movl %%edx, -0xc(%%ebp)\n\t"
      "fabs\n\t"
      "popl %%ebx\n\t"
      "fcompl 0x28b800\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .LFUN_00180b10_11\n\t"
      "pushl $1\n\t"
      "pushl $0x76\n\t"
      "pushl $0x2afe38\n\t"
      "pushl $0x2b00fc\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00180b10_11:\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fsubs 0x4(%%esi)\n\t"
      "fabs\n\t"
      "fcompl 0x28b800\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .LFUN_00180b10_12\n\t"
      "pushl $1\n\t"
      "pushl $0x77\n\t"
      "pushl $0x2afe38\n\t"
      "pushl $0x2b00e4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00180b10_12:\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fsubs 0x8(%%esi)\n\t"
      "fabs\n\t"
      "fcompl 0x28b800\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .LFUN_00180b10_13\n\t"
      "pushl $1\n\t"
      "pushl $0x78\n\t"
      "pushl $0x2afe38\n\t"
      "pushl $0x2b00cc\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00180b10_13:\n\t"
      "movl %%edi, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b180b10_assert), [exitfn] "m"(b180b10_exitfn), [c1d9c2b] "m"(b180b10_c1d9c2b), [c17ffc0] "m"(b180b10_c17ffc0)
      : "memory");
}
#else
#error "FUN_00180b10: clang naked draft required"
#endif


/* FUN_00180d10 (0x180d10) — XBE naked draft (batch 304). */
#if defined(__clang__)
static void (*const b180d10_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b180d10_exitfn)(int) = system_exit;
static void (*const b180d10_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;
static unsigned int (*const b180d10_c180b10)(float *param_1) = FUN_00180b10;
static short (*const b180d10_c180890)(float f) = FUN_00180890;

__attribute__((naked, noinline))
void FUN_00180d10(short type __attribute__((unused)), int count __attribute__((unused)), int compressed_out __attribute__((unused)), int compressed_size __attribute__((unused)), void *uncompressed __attribute__((unused)), int uncompressed_size __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x18(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "pushl %%edi\n\t"
      "jne .LFUN_00180d10_1\n\t"
      "pushl $1\n\t"
      "pushl $0xc2\n\t"
      "pushl $0x2afe38\n\t"
      "pushl $0x2b0084\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00180d10_1:\n\t"
      "movl 0x10(%%ebp), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .LFUN_00180d10_2\n\t"
      "pushl $1\n\t"
      "pushl $0xc3\n\t"
      "pushl $0x2afe38\n\t"
      "pushl $0x263b58\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00180d10_2:\n\t"
      "movswl 0x8(%%ebp), %%eax\n\t"
      "subl $0, %%eax\n\t"
      "je .LFUN_00180d10_11\n\t"
      "subl $2, %%eax\n\t"
      "je .LFUN_00180d10_7\n\t"
      "subl $2, %%eax\n\t"
      "je .LFUN_00180d10_3\n\t"
      "pushl $0x2b0140\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00180d10_3:\n\t"
      "movl 0xc(%%ebp), %%ebx\n\t"
      "movl 0x1c(%%ebp), %%ecx\n\t"
      "movl %%ebx, %%eax\n\t"
      "imull $0x44, %%eax, %%eax\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "je .LFUN_00180d10_4\n\t"
      "pushl $1\n\t"
      "pushl $0xef\n\t"
      "pushl $0x2afe38\n\t"
      "pushl $0x2b0008\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00180d10_4:\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "movl %%ebx, %%ecx\n\t"
      "shll $5, %%ecx\n\t"
      "cmpl %%eax, %%ecx\n\t"
      "je .LFUN_00180d10_5\n\t"
      "pushl $1\n\t"
      "pushl $0xf0\n\t"
      "pushl $0x2afe38\n\t"
      "pushl $0x2affc4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00180d10_5:\n\t"
      "testl %%ebx, %%ebx\n\t"
      "jle .LFUN_00180d10_15\n\t"
      "addl $0x10, %%edi\n\t"
      "addl $0x18, %%esi\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_00180d10_6:\n\t"
      "leal -0x18(%%esi), %%edx\n\t"
      "movl (%%edx), %%ecx\n\t"
      "leal -0x10(%%edi), %%eax\n\t"
      "movl %%ecx, (%%eax)\n\t"
      "movl 0x4(%%edx), %%ecx\n\t"
      "movl %%ecx, 0x4(%%eax)\n\t"
      "movl 0x8(%%edx), %%edx\n\t"
      "movl %%edx, 0x8(%%eax)\n\t"
      "leal -0xc(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c180b10]\n\t"
      "pushl %%esi\n\t"
      "movl %%eax, -0x4(%%edi)\n\t"
      "call *%[c180b10]\n\t"
      "leal 0xc(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl %%eax, (%%edi)\n\t"
      "call *%[c180b10]\n\t"
      "movl %%eax, 0x4(%%edi)\n\t"
      "movl 0x18(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c180890]\n\t"
      "movw %%ax, 0x8(%%edi)\n\t"
      "movl 0x1c(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c180890]\n\t"
      "movw %%ax, 0xa(%%edi)\n\t"
      "movb 0x20(%%esi), %%al\n\t"
      "movb $3, %%cl\n\t"
      "imulb %%cl\n\t"
      "movb %%al, 0xc(%%edi)\n\t"
      "movb 0x22(%%esi), %%al\n\t"
      "movb %%cl, %%dl\n\t"
      "imulb %%dl\n\t"
      "movb %%al, 0xd(%%edi)\n\t"
      "movl 0x24(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c180890]\n\t"
      "movw %%ax, 0xe(%%edi)\n\t"
      "addl $0x18, %%esp\n\t"
      "addl $0x44, %%esi\n\t"
      "addl $0x20, %%edi\n\t"
      "decl %%ebx\n\t"
      "jne .LFUN_00180d10_6\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00180d10_7:\n\t"
      "movl 0xc(%%ebp), %%ebx\n\t"
      "movl 0x1c(%%ebp), %%eax\n\t"
      "leal (%%ebx,%%ebx,4), %%ecx\n\t"
      "shll $2, %%ecx\n\t"
      "cmpl %%eax, %%ecx\n\t"
      "je .LFUN_00180d10_8\n\t"
      "pushl $1\n\t"
      "pushl $0xdd\n\t"
      "pushl $0x2afe38\n\t"
      "pushl $0x2aff48\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00180d10_8:\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "leal (,%%ebx,8), %%edx\n\t"
      "cmpl %%eax, %%edx\n\t"
      "je .LFUN_00180d10_9\n\t"
      "pushl $1\n\t"
      "pushl $0xde\n\t"
      "pushl $0x2afe38\n\t"
      "pushl $0x2afef8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00180d10_9:\n\t"
      "testl %%ebx, %%ebx\n\t"
      "jle .LFUN_00180d10_15\n\t"
      "addl $6, %%edi\n\t"
      "addl $0x10, %%esi\n\t"
      "movl %%edi, %%edi\n\t"
      ".LFUN_00180d10_10:\n\t"
      "leal -0x10(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c180b10]\n\t"
      "movl %%eax, -0x6(%%edi)\n\t"
      "movl -0x4(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c180890]\n\t"
      "movw %%ax, -0x2(%%edi)\n\t"
      "movl (%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c180890]\n\t"
      "movw %%ax, (%%edi)\n\t"
      "addl $0xc, %%esp\n\t"
      "addl $0x14, %%esi\n\t"
      "addl $8, %%edi\n\t"
      "decl %%ebx\n\t"
      "jne .LFUN_00180d10_10\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00180d10_11:\n\t"
      "movl 0xc(%%ebp), %%ebx\n\t"
      "movl 0x1c(%%ebp), %%ecx\n\t"
      "movl %%ebx, %%eax\n\t"
      "imull $0x38, %%eax, %%eax\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "je .LFUN_00180d10_12\n\t"
      "pushl $1\n\t"
      "pushl $0xc9\n\t"
      "pushl $0x2afe38\n\t"
      "pushl $0x2afeb0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00180d10_12:\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "movl %%ebx, %%ecx\n\t"
      "shll $5, %%ecx\n\t"
      "cmpl %%eax, %%ecx\n\t"
      "je .LFUN_00180d10_13\n\t"
      "pushl $1\n\t"
      "pushl $0xca\n\t"
      "pushl $0x2afe38\n\t"
      "pushl $0x2afe68\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00180d10_13:\n\t"
      "testl %%ebx, %%ebx\n\t"
      "jle .LFUN_00180d10_15\n\t"
      "addl $0x10, %%edi\n\t"
      "addl $0x18, %%esi\n\t"
      "leal (%%ebx), %%ebx\n\t"
      ".LFUN_00180d10_14:\n\t"
      "leal -0x18(%%esi), %%edx\n\t"
      "movl (%%edx), %%ecx\n\t"
      "leal -0x10(%%edi), %%eax\n\t"
      "movl %%ecx, (%%eax)\n\t"
      "movl 0x4(%%edx), %%ecx\n\t"
      "movl %%ecx, 0x4(%%eax)\n\t"
      "movl 0x8(%%edx), %%edx\n\t"
      "movl %%edx, 0x8(%%eax)\n\t"
      "leal -0xc(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c180b10]\n\t"
      "pushl %%esi\n\t"
      "movl %%eax, -0x4(%%edi)\n\t"
      "call *%[c180b10]\n\t"
      "leal 0xc(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl %%eax, (%%edi)\n\t"
      "call *%[c180b10]\n\t"
      "movl %%eax, 0x4(%%edi)\n\t"
      "movl 0x18(%%esi), %%edx\n\t"
      "movl %%edx, 0x8(%%edi)\n\t"
      "movl 0x1c(%%esi), %%eax\n\t"
      "movl %%eax, 0xc(%%edi)\n\t"
      "addl $0xc, %%esp\n\t"
      "addl $0x38, %%esi\n\t"
      "addl $0x20, %%edi\n\t"
      "decl %%ebx\n\t"
      "jne .LFUN_00180d10_14\n\t"
      ".LFUN_00180d10_15:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b180d10_assert), [exitfn] "m"(b180d10_exitfn), [c8f390] "m"(b180d10_c8f390), [c180b10] "m"(b180d10_c180b10), [c180890] "m"(b180d10_c180890)
      : "memory");
}
#else
#error "FUN_00180d10: clang naked draft required"
#endif


/* rasterizer_lights.c */

/* FUN_00181150 (0x181150) — readable C lift from XBE leaf. */
void FUN_00181150(void)
{
  csmemset((void *)0x4bed80, 0, 0x7722);
  csmemset((void *)0x47ed60, 0, 0x40020);
  *(int *)0x4d0480 = 0;
}




/* rasterizer_lights_reset_stat: zero stat counter at 0x5a37e0 (0x1812b0) */
void FUN_001812b0(void)
{
  *(int *)0x5a37e0 = 0;
}

/* FUN_00181410: stub (0x181410) */
void FUN_00181410(void)
{
}

/* FUN_00181900 (0x181900) — XBE naked draft (batch 369). */
#if defined(__clang__)
static void * (*const b181900_c18e3c0)(void) = (void *)global_scenario_get;
static void *(*const b181900_elem)(void *, int, int) = tag_block_get_element;
static void (*const b181900_perp)(float *, float *) = perpendicular3d;
static float (*const b181900_norm)(float *) = normalize3d;
static unsigned int (*const b181900_c180b10)(float *param_1) = (void *)FUN_00180b10;
static void *(*const b181900_tag)(int, int) = tag_get;
static void (*const b181900_c181670)(int *params) = (void *)FUN_00181670;

__attribute__((naked, noinline))
void FUN_00181900(short param_1 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x54, %%esp\n\t"
      "movb 0x3256d7, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00181900_5\n\t"
      "movw 0x46e008, %%ax\n\t"
      "cmpw $1, %%ax\n\t"
      "jg .LFUN_00181900_5\n\t"
      "jne .LFUN_00181900_1\n\t"
      "cmpw $1, 0x31fa98\n\t"
      "jg .LFUN_00181900_5\n\t"
      ".LFUN_00181900_1:\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "call *%[c18e3c0]\n\t"
      "movl %%eax, %%esi\n\t"
      "movswl 0x8(%%ebp), %%eax\n\t"
      "pushl $0x68\n\t"
      "pushl %%eax\n\t"
      "leal 0x134(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[elem]\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpw %%bx, 0x42(%%eax)\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "jbe .LFUN_00181900_4\n\t"
      "leal 0x128(%%esi), %%edx\n\t"
      "addl $0x11c, %%esi\n\t"
      "pushl %%edi\n\t"
      "movl %%edx, -0x8(%%ebp)\n\t"
      "movl %%esi, -0xc(%%ebp)\n\t"
      "jmp .LFUN_00181900_3\n\t"
      ".LFUN_00181900_2:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_00181900_3:\n\t"
      "movzwl 0x40(%%eax), %%edi\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "pushl $0x10\n\t"
      "addl %%ebx, %%edi\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "movl %%eax, %%esi\n\t"
      "movzbl 0xf(%%esi), %%ecx\n\t"
      "pushl $0x10\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[elem]\n\t"
      "movsbl 0xd(%%esi), %%ecx\n\t"
      "movsbl 0xe(%%esi), %%edx\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "movsbl 0xc(%%esi), %%eax\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "leal -0x2c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "fildl -0x10(%%ebp)\n\t"
      "movl %%ecx, -0x10(%%ebp)\n\t"
      "leal -0x20(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "fmuls 0x2820c0\n\t"
      "fstps -0x20(%%ebp)\n\t"
      "fildl -0x10(%%ebp)\n\t"
      "movl %%edx, -0x10(%%ebp)\n\t"
      "fmuls 0x2820c0\n\t"
      "fstps -0x1c(%%ebp)\n\t"
      "fildl -0x10(%%ebp)\n\t"
      "fmuls 0x2820c0\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "call *%[perp]\n\t"
      "leal -0x20(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[norm]\n\t"
      "fstp %%st(0)\n\t"
      "leal -0x2c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[norm]\n\t"
      "fstp %%st(0)\n\t"
      "leal -0x20(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c180b10]\n\t"
      "leal -0x2c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl %%eax, -0x44(%%ebp)\n\t"
      "call *%[c180b10]\n\t"
      "movl %%eax, -0x40(%%ebp)\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "movl 0xc(%%eax), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x6c656e73\n\t"
      "call *%[tag]\n\t"
      "movl %%eax, -0x54(%%ebp)\n\t"
      "movl (%%esi), %%edx\n\t"
      "movl %%edx, -0x50(%%ebp)\n\t"
      "movl 0x4(%%esi), %%eax\n\t"
      "movl %%eax, -0x4c(%%ebp)\n\t"
      "movl 0x8(%%esi), %%ecx\n\t"
      "orl $0xffffffff, %%eax\n\t"
      "movl %%ecx, -0x48(%%ebp)\n\t"
      "movl %%eax, -0x3c(%%ebp)\n\t"
      "movw %%ax, -0x38(%%ebp)\n\t"
      "movb 0x50654a, %%al\n\t"
      "movl %%edi, %%edx\n\t"
      "leal -0x54(%%ebp), %%ecx\n\t"
      "sarl $0x10, %%edx\n\t"
      "pushl %%ecx\n\t"
      "movb $0, -0x31(%%ebp)\n\t"
      "movw %%dx, -0x36(%%ebp)\n\t"
      "movw %%di, -0x34(%%ebp)\n\t"
      "movb %%al, -0x32(%%ebp)\n\t"
      "call *%[c181670]\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "addl $0x3c, %%esp\n\t"
      "incl %%ebx\n\t"
      "movzwl 0x42(%%edx), %%eax\n\t"
      "cmpl %%eax, %%ebx\n\t"
      "jl .LFUN_00181900_2\n\t"
      "popl %%edi\n\t"
      ".LFUN_00181900_4:\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      ".LFUN_00181900_5:\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c18e3c0] "m"(b181900_c18e3c0), [elem] "m"(b181900_elem), [perp] "m"(b181900_perp), [norm] "m"(b181900_norm), [c180b10] "m"(b181900_c180b10), [tag] "m"(b181900_tag), [c181670] "m"(b181900_c181670)
      : "memory");
}
#else
#error "FUN_00181900: clang naked draft required"
#endif


/* FUN_00181a90 (0x181a90) — XBE naked draft (batch 356). */
#if defined(__clang__)
static void (*const b181a90_c16f910)(int16_t profile) = (void *)FUN_0016f910;
static void (*const b181a90_c17cfc0)(int param_1, int param_2) = (void *)FUN_0017cfc0;
static int * (*const b181a90_c181020)(short index) = (void *)FUN_00181020;
static float * (*const b181a90_c17ffc0)(float *param_1, unsigned int param_2) = (void *)FUN_0017ffc0;
static void (*const b181a90_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b181a90_exitfn)(int) = system_exit;
static float *(*const b181a90_vsca)(float *, float *, float, float *) = vector3d_scale_add;
static int (*const b181a90_c17d030)(float *position, int vis_index, int index) = (void *)FUN_0017d030;
static void (*const b181a90_c17d020)(void) = (void *)FUN_0017d020;
static void (*const b181a90_c16fa40)(int16_t profile) = (void *)FUN_0016fa40;

__attribute__((naked, noinline))
void FUN_00181a90(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x2c, %%esp\n\t"
      "pushl $0x17\n\t"
      "call *%[c16f910]\n\t"
      "movb 0x3256d7, %%al\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00181a90_11\n\t"
      "movw 0x46e008, %%ax\n\t"
      "cmpw $1, %%ax\n\t"
      "jg .LFUN_00181a90_11\n\t"
      "jne .LFUN_00181a90_1\n\t"
      "cmpw $1, 0x31fa98\n\t"
      "jg .LFUN_00181a90_11\n\t"
      ".LFUN_00181a90_1:\n\t"
      "pushl %%ebx\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "cmpw %%bx, 0x5a5bc0\n\t"
      "jne .LFUN_00181a90_10\n\t"
      "cmpl %%ebx, 0x4d0480\n\t"
      "jle .LFUN_00181a90_10\n\t"
      "pushl $1\n\t"
      "pushl $6\n\t"
      "call *%[c17cfc0]\n\t"
      "movl 0x4d0480, %%eax\n\t"
      "addl $8, %%esp\n\t"
      "cmpl %%ebx, %%eax\n\t"
      "jle .LFUN_00181a90_9\n\t"
      "pushl %%esi\n\t"
      "movl %%ebx, -0x4(%%ebp)\n\t"
      "pushl %%edi\n\t"
      ".LFUN_00181a90_2:\n\t"
      "movl %%ebx, %%esi\n\t"
      "call *%[c181020]\n\t"
      "movl %%eax, %%edi\n\t"
      "movl 0x10(%%edi), %%eax\n\t"
      "movl (%%edi), %%esi\n\t"
      "pushl %%eax\n\t"
      "leal -0x2c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c17ffc0]\n\t"
      "movl (%%eax), %%edx\n\t"
      "movl 0x4(%%eax), %%ecx\n\t"
      "movl %%edx, -0x20(%%ebp)\n\t"
      "movl 0x8(%%eax), %%edx\n\t"
      "movzbl 0x22(%%edi), %%eax\n\t"
      "andl $0xffffff7f, %%eax\n\t"
      "addl $8, %%esp\n\t"
      "cmpw 0x5a5bc2, %%ax\n\t"
      "movl %%ecx, -0x1c(%%ebp)\n\t"
      "movl %%edx, -0x18(%%ebp)\n\t"
      "jne .LFUN_00181a90_8\n\t"
      "movswl 0x14(%%esi), %%eax\n\t"
      "subl $0, %%eax\n\t"
      "movl 0x10(%%esi), %%ecx\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "je .LFUN_00181a90_5\n\t"
      "decl %%eax\n\t"
      "je .LFUN_00181a90_4\n\t"
      "decl %%eax\n\t"
      "je .LFUN_00181a90_3\n\t"
      "pushl $1\n\t"
      "pushl $0x1e2\n\t"
      "pushl $0x2b01b4\n\t"
      "pushl $0x2b05ec\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "jmp .LFUN_00181a90_7\n\t"
      ".LFUN_00181a90_3:\n\t"
      "leal 0x4(%%edi), %%edx\n\t"
      "movl (%%edx), %%eax\n\t"
      "movl 0x4(%%edx), %%ecx\n\t"
      "movl 0x8(%%edx), %%edx\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "movl %%ecx, -0x10(%%ebp)\n\t"
      "movl %%edx, -0xc(%%ebp)\n\t"
      "jmp .LFUN_00181a90_7\n\t"
      ".LFUN_00181a90_4:\n\t"
      "flds 0x10(%%esi)\n\t"
      "leal -0x14(%%ebp), %%eax\n\t"
      "fmuls 0x254e68\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "leal -0x20(%%ebp), %%ecx\n\t"
      "fstps (%%esp)\n\t"
      "pushl %%ecx\n\t"
      "leal 0x4(%%edi), %%edx\n\t"
      "pushl %%edx\n\t"
      "jmp .LFUN_00181a90_6\n\t"
      ".LFUN_00181a90_5:\n\t"
      "flds 0x10(%%esi)\n\t"
      "leal -0x14(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "fchs\n\t"
      "pushl %%ecx\n\t"
      "fstps (%%esp)\n\t"
      "pushl $0x5a5bd4\n\t"
      "leal 0x4(%%edi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      ".LFUN_00181a90_6:\n\t"
      "call *%[vsca]\n\t"
      "addl $0x10, %%esp\n\t"
      ".LFUN_00181a90_7:\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "leal -0x14(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c17d030]\n\t"
      "addl $0xc, %%esp\n\t"
      "movl %%eax, 0x24(%%edi)\n\t"
      ".LFUN_00181a90_8:\n\t"
      "movl 0x4d0480, %%ecx\n\t"
      "incl %%ebx\n\t"
      "movswl %%bx, %%eax\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "jl .LFUN_00181a90_2\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      ".LFUN_00181a90_9:\n\t"
      "call *%[c17d020]\n\t"
      ".LFUN_00181a90_10:\n\t"
      "popl %%ebx\n\t"
      ".LFUN_00181a90_11:\n\t"
      "pushl $0x17\n\t"
      "call *%[c16fa40]\n\t"
      "addl $4, %%esp\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c16f910] "m"(b181a90_c16f910), [c17cfc0] "m"(b181a90_c17cfc0), [c181020] "m"(b181a90_c181020), [c17ffc0] "m"(b181a90_c17ffc0), [assert] "m"(b181a90_assert), [exitfn] "m"(b181a90_exitfn), [vsca] "m"(b181a90_vsca), [c17d030] "m"(b181a90_c17d030), [c17d020] "m"(b181a90_c17d020), [c16fa40] "m"(b181a90_c16fa40)
      : "memory");
}
#else
#error "FUN_00181a90: clang naked draft required"
#endif


/* FUN_00181c20 (0x181c20) — XBE naked draft (batch 79). */
#if defined(__clang__)
static void (*const b181c20_c16f910)(int16_t profile) = FUN_0016f910;
static void (*const b181c20_c17cfc0)(int param_1, int param_2) = FUN_0017cfc0;
static void (*const b181c20_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b181c20_exitfn)(int) = system_exit;
static unsigned char * (*const b181c20_c181060)(void *lens_flare_params) = FUN_00181060;
static float * (*const b181c20_c17ffc0)(float *param_1, unsigned int param_2) = FUN_0017ffc0;
static float (*const b181c20_c17ff80)(unsigned char param_1) = FUN_0017ff80;
static float (*const b181c20_c181420)(void *lens_flare_params, short rotation_fn) = FUN_00181420;
static float (*const b181c20_norm)(float *) = normalize3d;
static void *(*const b181c20_elem)(void *, int, int) = tag_block_get_element;
static unsigned char (*const b181c20_c180770)(float alpha) = FUN_00180770;
static float (*const b181c20_c10a5e0)(int16_t function_type, float input) = FUN_0010a5e0;
static float * (*const b181c20_c7c270)(float *out_color, uint32_t flags, float *rgb_lower_bound, float *rgb_upper_bound, float blend) = FUN_0007c270;
static void (*const b181c20_c10b820)(float a, float b, float blend, float *out) = scalars_interpolate;
static unsigned int (*const b181c20_d1c90)(float *) = FUN_000d1c90;
static char (*const b181c20_c17cfd0)(int param_1, int param_2, short param_3) = FUN_0017cfd0;
static void (*const b181c20_c17cfe0)(int tex_flags) = FUN_0017cfe0;
static void (*const b181c20_c158ae0)(int mode) = FUN_00158ae0;
static void (*const b181c20_c17d010)(float *position, float radius, float *scale2d, float angle, uint32_t color) = FUN_0017d010;
static void (*const b181c20_c17d020)(void) = FUN_0017d020;
static void (*const b181c20_c169fd0)(int *param_1) = FUN_00169fd0;
static void (*const b181c20_c16fa40)(int16_t profile) = FUN_0016fa40;

__attribute__((naked, noinline))
void FUN_00181c20(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xb4, %%esp\n\t"
      "pushl $0x19\n\t"
      "call *%[c16f910]\n\t"
      "movb 0x3256d7, %%al\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00181c20_47\n\t"
      "cmpw $0, 0x5a5bc0\n\t"
      "jne .LFUN_00181c20_47\n\t"
      "movl 0x4d0480, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jle .LFUN_00181c20_47\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl $0\n\t"
      "pushl $5\n\t"
      "call *%[c17cfc0]\n\t"
      "movl 0x4d0480, %%eax\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%ecx, -0x78(%%ebp)\n\t"
      "jle .LFUN_00181c20_40\n\t"
      "xorl %%esi, %%esi\n\t"
      "movl %%edi, %%edi\n\t"
      ".LFUN_00181c20_1:\n\t"
      "testw %%cx, %%cx\n\t"
      "jl .LFUN_00181c20_2\n\t"
      "cmpl %%eax, %%esi\n\t"
      "jl .LFUN_00181c20_3\n\t"
      ".LFUN_00181c20_2:\n\t"
      "pushl $1\n\t"
      "pushl $0x43\n\t"
      "pushl $0x2b01b4\n\t"
      "pushl $0x2b0174\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00181c20_3:\n\t"
      "leal (%%esi,%%esi,4), %%ebx\n\t"
      "leal 0x4c6480(,%%ebx,8), %%ebx\n\t"
      "movl %%ebx, %%eax\n\t"
      "call *%[c181060]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x10(%%ebx), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0xb4(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c17ffc0]\n\t"
      "movl (%%eax), %%edx\n\t"
      "movl 0x4(%%eax), %%ecx\n\t"
      "movl %%edx, -0x68(%%ebp)\n\t"
      "movl 0x8(%%eax), %%edx\n\t"
      "movzbl 0x22(%%ebx), %%eax\n\t"
      "andl $0xffffff7f, %%eax\n\t"
      "addl $8, %%esp\n\t"
      "cmpw 0x5a5bc2, %%ax\n\t"
      "movl %%ecx, -0x64(%%ebp)\n\t"
      "movl %%edx, -0x60(%%ebp)\n\t"
      "jne .LFUN_00181c20_39\n\t"
      "movl 0x24(%%ebx), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "movl (%%ebx), %%edi\n\t"
      "movl %%edi, -0x20(%%ebp)\n\t"
      "jle .LFUN_00181c20_39\n\t"
      "movzbl 0x1b(%%ebx), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "jbe .LFUN_00181c20_39\n\t"
      "movl 0xc4(%%edi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jle .LFUN_00181c20_39\n\t"
      "leal 0x4(%%ebx), %%edx\n\t"
      "movl (%%edx), %%eax\n\t"
      "movl %%eax, -0x74(%%ebp)\n\t"
      "flds -0x74(%%ebp)\n\t"
      "fsubs 0x5a5bc8\n\t"
      "movl 0x4(%%edx), %%eax\n\t"
      "movl 0x8(%%edx), %%edx\n\t"
      "movl %%eax, -0x70(%%ebp)\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "movl %%edx, -0x6c(%%ebp)\n\t"
      "flds -0x70(%%ebp)\n\t"
      "movzbl (%%esi), %%eax\n\t"
      "fsubs 0x5a5bcc\n\t"
      "movl %%eax, -0x28(%%ebp)\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "flds -0x6c(%%ebp)\n\t"
      "fsubs 0x5a5bd0\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "flds 0x5a5bdc\n\t"
      "fmuls -0x10(%%ebp)\n\t"
      "flds 0x5a5bd8\n\t"
      "fmuls -0x14(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fmuls 0x5a5bd4\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fstps -0x1c(%%ebp)\n\t"
      "flds 0x5a5bd4\n\t"
      "fmuls -0x1c(%%ebp)\n\t"
      "flds 0x5a5bd8\n\t"
      "fmuls -0x1c(%%ebp)\n\t"
      "flds 0x5a5bdc\n\t"
      "fmuls -0x1c(%%ebp)\n\t"
      "fstps -0x40(%%ebp)\n\t"
      "fxch %%st(1)\n\t"
      "fsubs -0x18(%%ebp)\n\t"
      "fstps -0x48(%%ebp)\n\t"
      "fsubs -0x14(%%ebp)\n\t"
      "flds -0x40(%%ebp)\n\t"
      "fsubs -0x10(%%ebp)\n\t"
      "flds -0x48(%%ebp)\n\t"
      ".byte 0xdc, 0xc0\n\t"
      "fstps -0x48(%%ebp)\n\t"
      "fxch %%st(1)\n\t"
      ".byte 0xdc, 0xc0\n\t"
      "fstps -0x44(%%ebp)\n\t"
      ".byte 0xdc, 0xc0\n\t"
      "fstps -0x40(%%ebp)\n\t"
      "fildl -0x28(%%ebp)\n\t"
      "fmuls 0x261518\n\t"
      "fstps -0x28(%%ebp)\n\t"
      "flds 0x1c(%%edi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00181c20_5\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fsubs 0x1c(%%edi)\n\t"
      "flds 0x18(%%edi)\n\t"
      "fsubs 0x1c(%%edi)\n\t"
      ".byte 0xde, 0xf9\n\t"
      "fcoms 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00181c20_4\n\t"
      "fstp %%st(0)\n\t"
      "movl $0, -0xc(%%ebp)\n\t"
      "jmp .LFUN_00181c20_6\n\t"
      ".LFUN_00181c20_4:\n\t"
      "fcoms 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00181c20_7\n\t"
      "fstp %%st(0)\n\t"
      ".LFUN_00181c20_5:\n\t"
      "movl $0x3f800000, -0xc(%%ebp)\n\t"
      ".LFUN_00181c20_6:\n\t"
      "pushl %%ecx\n\t"
      "call *%[c17ff80]\n\t"
      "flds -0x28(%%ebp)\n\t"
      "fmuls -0xc(%%ebp)\n\t"
      "movw 0x80(%%edi), %%di\n\t"
      "movl %%ebx, %%esi\n\t"
      ".byte 0xde, 0xc9\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "call *%[c181420]\n\t"
      "movl -0x20(%%ebp), %%edi\n\t"
      "fmuls 0x84(%%edi)\n\t"
      "leal -0x18(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "fstps -0x98(%%ebp)\n\t"
      "flds 0x5a5c6c\n\t"
      "fmuls -0x10(%%ebp)\n\t"
      "flds 0x5a5c68\n\t"
      "fmuls -0x14(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fmuls 0x5a5c64\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds 0x5a5c78\n\t"
      "fmuls -0x10(%%ebp)\n\t"
      "flds 0x5a5c74\n\t"
      "fmuls -0x14(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fmuls 0x5a5c70\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fpatan\n\t"
      "fmuls 0x2b073c\n\t"
      "fstps -0x9c(%%ebp)\n\t"
      "flds 0x8(%%edi)\n\t"
      "fsubs 0xc(%%edi)\n\t"
      "fdivrs 0x2533c8\n\t"
      "fsts -0x4(%%ebp)\n\t"
      "fmuls 0xc(%%edi)\n\t"
      "fchs\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "call *%[norm]\n\t"
      "fstp %%st(0)\n\t"
      "addl $8, %%esp\n\t"
      "flds 0x5a5bdc\n\t"
      "movl $0x3f800000, -0x8c(%%ebp)\n\t"
      "fmuls -0x60(%%ebp)\n\t"
      "flds 0x5a5bd8\n\t"
      "fmuls -0x64(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds -0x68(%%ebp)\n\t"
      "fmuls 0x5a5bd4\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fmuls -0x4(%%ebp)\n\t"
      "fsubrs -0x8(%%ebp)\n\t"
      "fcoms 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00181c20_8\n\t"
      "fstp %%st(0)\n\t"
      "movl $0, -0x88(%%ebp)\n\t"
      "jmp .LFUN_00181c20_10\n\t"
      ".LFUN_00181c20_7:\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "jmp .LFUN_00181c20_6\n\t"
      ".LFUN_00181c20_8:\n\t"
      "fcoms 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00181c20_9\n\t"
      "fstp %%st(0)\n\t"
      "movl $0x3f800000, -0x88(%%ebp)\n\t"
      "jmp .LFUN_00181c20_10\n\t"
      ".LFUN_00181c20_9:\n\t"
      "fstps -0x88(%%ebp)\n\t"
      ".LFUN_00181c20_10:\n\t"
      "flds -0x60(%%ebp)\n\t"
      "fmuls -0x10(%%ebp)\n\t"
      "flds -0x64(%%ebp)\n\t"
      "fmuls -0x14(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds -0x68(%%ebp)\n\t"
      "fmuls -0x18(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fmuls -0x4(%%ebp)\n\t"
      "fsubrs -0x8(%%ebp)\n\t"
      "fcoms 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00181c20_11\n\t"
      "fstp %%st(0)\n\t"
      "movl $0, -0x84(%%ebp)\n\t"
      "jmp .LFUN_00181c20_13\n\t"
      ".LFUN_00181c20_11:\n\t"
      "fcoms 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00181c20_12\n\t"
      "fstp %%st(0)\n\t"
      "movl $0x3f800000, -0x84(%%ebp)\n\t"
      "jmp .LFUN_00181c20_13\n\t"
      ".LFUN_00181c20_12:\n\t"
      "fstps -0x84(%%ebp)\n\t"
      ".LFUN_00181c20_13:\n\t"
      "flds 0x5a5bdc\n\t"
      "fmuls -0x10(%%ebp)\n\t"
      "flds 0x5a5bd8\n\t"
      "fmuls -0x14(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fmuls 0x5a5bd4\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fmuls -0x4(%%ebp)\n\t"
      "fadds -0x8(%%ebp)\n\t"
      "fcoms 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00181c20_14\n\t"
      "fstp %%st(0)\n\t"
      "movl $0, -0x80(%%ebp)\n\t"
      "jmp .LFUN_00181c20_16\n\t"
      ".LFUN_00181c20_14:\n\t"
      "fcoms 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00181c20_15\n\t"
      "fstp %%st(0)\n\t"
      "movl $0x3f800000, -0x80(%%ebp)\n\t"
      "jmp .LFUN_00181c20_16\n\t"
      ".LFUN_00181c20_15:\n\t"
      "fstps -0x80(%%ebp)\n\t"
      ".LFUN_00181c20_16:\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00181c20_39\n\t"
      "xorl %%edx, %%edx\n\t"
      "movb 0x23(%%ebx), %%dl\n\t"
      "pushl %%edx\n\t"
      "call *%[c17ff80]\n\t"
      "fstps -0x7c(%%ebp)\n\t"
      "movl 0xc4(%%edi), %%eax\n\t"
      "leal 0xc4(%%edi), %%ecx\n\t"
      "xorl %%esi, %%esi\n\t"
      "addl $4, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%esi, -0x2c(%%ebp)\n\t"
      "jle .LFUN_00181c20_39\n\t"
      "xorl %%eax, %%eax\n\t"
      "movl %%edi, %%edi\n\t"
      ".LFUN_00181c20_17:\n\t"
      "pushl $0x80\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[elem]\n\t"
      "movl %%eax, %%edi\n\t"
      "flds 0x34(%%edi)\n\t"
      "movswl 0x3c(%%edi), %%eax\n\t"
      "flds 0x38(%%edi)\n\t"
      "addl $0xc, %%esp\n\t"
      "testw %%si, %%si\n\t"
      ".byte 0xd8, 0xe1\n\t"
      "fmuls -0x7c(%%ebp)\n\t"
      ".byte 0xd8, 0xc1\n\t"
      "fmuls -0x8c(%%ebp,%%eax,4)\n\t"
      "fmuls -0xc(%%ebp)\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "jne .LFUN_00181c20_18\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movl %%ecx, -0xc(%%ebp)\n\t"
      ".LFUN_00181c20_18:\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00181c20_38\n\t"
      "flds 0x28(%%edi)\n\t"
      "flds 0x2c(%%edi)\n\t"
      ".byte 0xd8, 0xe1\n\t"
      "fmuls -0x7c(%%ebp)\n\t"
      ".byte 0xd8, 0xc1\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x40(%%edi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .LFUN_00181c20_19\n\t"
      "flds 0x44(%%edi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .LFUN_00181c20_19\n\t"
      "flds 0x48(%%edi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .LFUN_00181c20_19\n\t"
      "flds 0x4c(%%edi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .LFUN_00181c20_19\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c180770]\n\t"
      "movzbl %%al, %%esi\n\t"
      "movl 0x18(%%ebx), %%eax\n\t"
      "shll $0x18, %%esi\n\t"
      "andl $0xffffff, %%eax\n\t"
      "addl $4, %%esp\n\t"
      "orl %%eax, %%esi\n\t"
      "movl $0x3f800000, -0x5c(%%ebp)\n\t"
      "jmp .LFUN_00181c20_30\n\t"
      ".LFUN_00181c20_19:\n\t"
      "cmpw $1, 0x72(%%edi)\n\t"
      "leal 0x44(%%edi), %%ecx\n\t"
      "movl (%%ecx), %%edx\n\t"
      "movl 0x4(%%ecx), %%eax\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "movl %%edx, -0x54(%%ebp)\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "movl %%eax, -0x50(%%ebp)\n\t"
      "movl %%ecx, -0x4c(%%ebp)\n\t"
      "movl %%edx, -0x58(%%ebp)\n\t"
      "jle .LFUN_00181c20_29\n\t"
      "flds 0x74(%%edi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .LFUN_00181c20_20\n\t"
      "pushl $1\n\t"
      "pushl $0x28b\n\t"
      "pushl $0x2b01b4\n\t"
      "pushl $0x2b0718\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00181c20_20:\n\t"
      "flds 0x5a5e18\n\t"
      "xorl %%eax, %%eax\n\t"
      "fadds 0x78(%%edi)\n\t"
      "movw 0x72(%%edi), %%ax\n\t"
      "pushl %%ecx\n\t"
      "fdivs 0x74(%%edi)\n\t"
      "fstps (%%esp)\n\t"
      "pushl %%eax\n\t"
      "call *%[c10a5e0]\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "movl -0x8(%%ebp), %%esi\n\t"
      "xorl %%eax, %%eax\n\t"
      "movb 0x70(%%edi), %%al\n\t"
      "pushl %%esi\n\t"
      "leal 0x64(%%edi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal 0x54(%%edi), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x38(%%ebp), %%ecx\n\t"
      "andl $3, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c7c270]\n\t"
      "movl 0x60(%%edi), %%eax\n\t"
      "movl 0x50(%%edi), %%ecx\n\t"
      "leal -0x3c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c10b820]\n\t"
      "flds -0x3c(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "addl $0x2c, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_00181c20_21\n\t"
      "flds -0x3c(%%ebp)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jnp .LFUN_00181c20_22\n\t"
      ".LFUN_00181c20_21:\n\t"
      "pushl $1\n\t"
      "pushl $0x29b\n\t"
      "pushl $0x2b01b4\n\t"
      "pushl $0x2b06dc\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00181c20_22:\n\t"
      "flds -0x38(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_00181c20_23\n\t"
      "flds -0x38(%%ebp)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jnp .LFUN_00181c20_24\n\t"
      ".LFUN_00181c20_23:\n\t"
      "pushl $1\n\t"
      "pushl $0x29c\n\t"
      "pushl $0x2b01b4\n\t"
      "pushl $0x2b06a0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00181c20_24:\n\t"
      "flds -0x34(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_00181c20_25\n\t"
      "flds -0x34(%%ebp)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jnp .LFUN_00181c20_26\n\t"
      ".LFUN_00181c20_25:\n\t"
      "pushl $1\n\t"
      "pushl $0x29d\n\t"
      "pushl $0x2b01b4\n\t"
      "pushl $0x2b0664\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00181c20_26:\n\t"
      "flds -0x30(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_00181c20_27\n\t"
      "flds -0x30(%%ebp)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jnp .LFUN_00181c20_28\n\t"
      ".LFUN_00181c20_27:\n\t"
      "pushl $1\n\t"
      "pushl $0x29e\n\t"
      "pushl $0x2b01b4\n\t"
      "pushl $0x2b0628\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00181c20_28:\n\t"
      "flds -0x3c(%%ebp)\n\t"
      "fmuls -0x58(%%ebp)\n\t"
      "fstps -0x58(%%ebp)\n\t"
      "flds -0x54(%%ebp)\n\t"
      "fmuls -0x38(%%ebp)\n\t"
      "fstps -0x54(%%ebp)\n\t"
      "flds -0x50(%%ebp)\n\t"
      "fmuls -0x34(%%ebp)\n\t"
      "fstps -0x50(%%ebp)\n\t"
      "flds -0x4c(%%ebp)\n\t"
      "fmuls -0x30(%%ebp)\n\t"
      "fstps -0x4c(%%ebp)\n\t"
      ".LFUN_00181c20_29:\n\t"
      "leal -0x58(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[d1c90]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x40(%%edi), %%eax\n\t"
      "addl $4, %%esp\n\t"
      "movl %%eax, -0x5c(%%ebp)\n\t"
      ".LFUN_00181c20_30:\n\t"
      "cmpw $0, -0x2c(%%ebp)\n\t"
      "jne .LFUN_00181c20_31\n\t"
      "flds -0x98(%%ebp)\n\t"
      "movl -0x20(%%ebp), %%ecx\n\t"
      "fadds 0x20(%%edi)\n\t"
      "movl 0xa0(%%ecx), %%edx\n\t"
      "movl 0xa4(%%ecx), %%eax\n\t"
      "movl %%edx, -0x94(%%ebp)\n\t"
      "fstps -0x24(%%ebp)\n\t"
      "movl %%eax, -0x90(%%ebp)\n\t"
      "jmp .LFUN_00181c20_32\n\t"
      ".LFUN_00181c20_31:\n\t"
      "movl 0x20(%%edi), %%ecx\n\t"
      "movl %%ecx, -0x24(%%ebp)\n\t"
      "movl -0x20(%%ebp), %%ecx\n\t"
      "movl $0x3f800000, -0x90(%%ebp)\n\t"
      "movl $0x3f800000, -0x94(%%ebp)\n\t"
      ".LFUN_00181c20_32:\n\t"
      "movw (%%edi), %%ax\n\t"
      "testb $1, %%al\n\t"
      "je .LFUN_00181c20_33\n\t"
      "flds -0x24(%%ebp)\n\t"
      "fadds -0x9c(%%ebp)\n\t"
      "fstps -0x24(%%ebp)\n\t"
      ".LFUN_00181c20_33:\n\t"
      "testb $4, %%al\n\t"
      "je .LFUN_00181c20_34\n\t"
      "flds -0x28(%%ebp)\n\t"
      "fadds 0x2533c8\n\t"
      "fmuls -0x4(%%ebp)\n\t"
      "fmuls 0x253398\n\t"
      "fstps -0x4(%%ebp)\n\t"
      ".LFUN_00181c20_34:\n\t"
      "testb $2, %%al\n\t"
      "je .LFUN_00181c20_35\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fmuls -0x1c(%%ebp)\n\t"
      "fstps -0x4(%%ebp)\n\t"
      ".LFUN_00181c20_35:\n\t"
      "flds 0x1c(%%edi)\n\t"
      "movl 0x2c(%%ecx), %%eax\n\t"
      "flds -0x48(%%ebp)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x4(%%edi), %%dx\n\t"
      "fadds -0x74(%%ebp)\n\t"
      "fstps -0xa8(%%ebp)\n\t"
      "flds -0x44(%%ebp)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl $0\n\t"
      "fadds -0x70(%%ebp)\n\t"
      "fstps -0xa4(%%ebp)\n\t"
      "flds -0x40(%%ebp)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fadds -0x6c(%%ebp)\n\t"
      "fstps -0xa0(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "call *%[c17cfd0]\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00181c20_39\n\t"
      "movl -0x5c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c17cfe0]\n\t"
      "movb (%%edi), %%al\n\t"
      "addl $4, %%esp\n\t"
      "testb $8, %%al\n\t"
      "je .LFUN_00181c20_36\n\t"
      "movb 0x22(%%ebx), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jns .LFUN_00181c20_36\n\t"
      "pushl $2\n\t"
      "jmp .LFUN_00181c20_37\n\t"
      ".LFUN_00181c20_36:\n\t"
      "pushl $0\n\t"
      ".LFUN_00181c20_37:\n\t"
      "call *%[c158ae0]\n\t"
      "flds -0x24(%%ebp)\n\t"
      "fmuls 0x253d4c\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "addl $4, %%esp\n\t"
      "pushl %%esi\n\t"
      "pushl %%ecx\n\t"
      "fstps (%%esp)\n\t"
      "leal -0x94(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "leal -0xa8(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c17d010]\n\t"
      "movl -0x2c(%%ebp), %%esi\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00181c20_38:\n\t"
      "movl -0x20(%%ebp), %%ecx\n\t"
      "movl 0xc4(%%ecx), %%edx\n\t"
      "incl %%esi\n\t"
      "addl $0xc4, %%ecx\n\t"
      "movswl %%si, %%eax\n\t"
      "cmpl %%edx, %%eax\n\t"
      "movl %%esi, -0x2c(%%ebp)\n\t"
      "jl .LFUN_00181c20_17\n\t"
      ".LFUN_00181c20_39:\n\t"
      "movl -0x78(%%ebp), %%ecx\n\t"
      "movl 0x4d0480, %%eax\n\t"
      "incl %%ecx\n\t"
      "movswl %%cx, %%esi\n\t"
      "cmpl %%eax, %%esi\n\t"
      "movl %%ecx, -0x78(%%ebp)\n\t"
      "jl .LFUN_00181c20_1\n\t"
      ".LFUN_00181c20_40:\n\t"
      "pushl $0\n\t"
      "call *%[c158ae0]\n\t"
      "addl $4, %%esp\n\t"
      "call *%[c17d020]\n\t"
      "movb 0x3256fe, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00181c20_46\n\t"
      "movl 0x4d0480, %%eax\n\t"
      "xorl %%edi, %%edi\n\t"
      "testl %%eax, %%eax\n\t"
      "jle .LFUN_00181c20_46\n\t"
      "xorl %%esi, %%esi\n\t"
      "movl $0x42480000, %%ebx\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_00181c20_41:\n\t"
      "testw %%di, %%di\n\t"
      "jl .LFUN_00181c20_42\n\t"
      "cmpl %%eax, %%esi\n\t"
      "jl .LFUN_00181c20_43\n\t"
      ".LFUN_00181c20_42:\n\t"
      "pushl $1\n\t"
      "pushl $0x43\n\t"
      "pushl $0x2b01b4\n\t"
      "pushl $0x2b0174\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00181c20_43:\n\t"
      "leal (%%esi,%%esi,4), %%eax\n\t"
      "movl 0x4c64a4(,%%eax,8), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "leal 0x4c6480(,%%eax,8), %%eax\n\t"
      "jle .LFUN_00181c20_45\n\t"
      "movzbl 0x22(%%eax), %%edx\n\t"
      "andl $0xffffff7f, %%edx\n\t"
      "cmpw 0x5a5bc2, %%dx\n\t"
      "jne .LFUN_00181c20_45\n\t"
      "movl (%%eax), %%ecx\n\t"
      "cmpl %%ebx, 0x10(%%ecx)\n\t"
      "je .LFUN_00181c20_44\n\t"
      "testb $1, 0x30(%%ecx)\n\t"
      "je .LFUN_00181c20_45\n\t"
      ".LFUN_00181c20_44:\n\t"
      "pushl %%eax\n\t"
      "call *%[c169fd0]\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_00181c20_45:\n\t"
      "movl 0x4d0480, %%eax\n\t"
      "incl %%edi\n\t"
      "movswl %%di, %%esi\n\t"
      "cmpl %%eax, %%esi\n\t"
      "jl .LFUN_00181c20_41\n\t"
      ".LFUN_00181c20_46:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      ".LFUN_00181c20_47:\n\t"
      "pushl $0x19\n\t"
      "call *%[c16fa40]\n\t"
      "addl $4, %%esp\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c16f910] "m"(b181c20_c16f910), [c17cfc0] "m"(b181c20_c17cfc0), [assert] "m"(b181c20_assert), [exitfn] "m"(b181c20_exitfn), [c181060] "m"(b181c20_c181060), [c17ffc0] "m"(b181c20_c17ffc0), [c17ff80] "m"(b181c20_c17ff80), [c181420] "m"(b181c20_c181420), [norm] "m"(b181c20_norm), [elem] "m"(b181c20_elem), [c180770] "m"(b181c20_c180770), [c10a5e0] "m"(b181c20_c10a5e0), [c7c270] "m"(b181c20_c7c270), [c10b820] "m"(b181c20_c10b820), [d1c90] "m"(b181c20_d1c90), [c17cfd0] "m"(b181c20_c17cfd0), [c17cfe0] "m"(b181c20_c17cfe0), [c158ae0] "m"(b181c20_c158ae0), [c17d010] "m"(b181c20_c17d010), [c17d020] "m"(b181c20_c17d020), [c169fd0] "m"(b181c20_c169fd0), [c16fa40] "m"(b181c20_c16fa40)
      : "memory");
}
#else
#error "FUN_00181c20: clang naked draft required"
#endif


/* rasterizer_memory_pool.c */

/* rasterizer_memory_pool_new (0x1824e0) — readable C lift from XBE leaf. */
char rasterizer_memory_pool_new(void)
{
  extern char DAT_002b077c[];
  extern char DAT_002b0740[];
  void *pool;

  pool = debug_malloc(0x18000, false, DAT_002b077c, 0x13);
  *(void **)0x4d0488 = pool;
  if (pool == 0) {
    error(2, DAT_002b0740);
    return 0;
  }
  return 1;
}




/* rasterizer_memory_pool_reset: reset pool allocation cursor to zero (0x182520)
 */
void rasterizer_memory_pool_reset(void)
{
  *(int *)0x4d048c = 0;
}

/* rasterizer_memory_pool_alloc (0x182530) — readable C lift from XBE leaf. */
void *rasterizer_memory_pool_alloc(void *data, int size)
{
  extern char DAT_002b07b0[];
  int used;
  void *dest;

  used = *(int *)0x4d048c;
  if (used + size > 0x18000) {
    error(2, DAT_002b07b0);
    return 0;
  }
  dest = (char *)*(void **)0x4d0488 + used;
  *(int *)0x4d048c = used + size;
  if (data != 0) {
    csmemcpy(dest, data, (size_t)size);
  }
  return dest;
}




/* rasterizer_memory_pool_copy (0x182590) — readable C lift from XBE leaf. */
int rasterizer_memory_pool_copy(int data, int size)
{
  extern char DAT_002b07dc[];
  extern char DAT_002b077c[];

  if (data == 0) {
    display_assert(DAT_002b07dc, DAT_002b077c, 0x42, true);
    system_exit(-1);
  }
  return rasterizer_memory_pool_alloc(data, size);
}




/* FUN_001825d0: stub (0x1825d0) */
void FUN_001825d0(void)
{
}

/* rasterizer_memory_pool_delete (0x1825e0) — readable C lift from XBE leaf. */
void rasterizer_memory_pool_delete(void)
{
  extern char DAT_002b077c[];
  void *pool;

  pool = *(void **)0x4d0488;
  if (pool != 0) {
    debug_free(pool, DAT_002b077c, 0x50);
  }
  *(void **)0x4d0488 = 0;
  *(void **)0x4d048c = 0;
}




/* rasterizer_swizzle.c */

/* rasterizer_swizzle_compute_masks (0x182690) — XBE naked draft (batch 85). */
#if defined(__clang__)
static int16_t (*const b182690_c108db0)(unsigned int value) = FUN_00108db0;
static void (*const b182690_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b182690_exitfn)(int) = system_exit;

__attribute__((naked, noinline))
void rasterizer_swizzle_compute_masks(short param_1 __attribute__((unused)), short param_2 __attribute__((unused)), unsigned short param_3 __attribute__((unused)), unsigned short param_4 __attribute__((unused)), unsigned int *param_5 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $8, %%esp\n\t"
      "movswl 0x8(%%ebp), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[c108db0]\n\t"
      "movswl 0xc(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl %%eax, %%esi\n\t"
      "movl %%esi, -0x4(%%ebp)\n\t"
      "call *%[c108db0]\n\t"
      "addl $8, %%esp\n\t"
      "cmpw %%ax, %%si\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "movl %%eax, 0x8(%%ebp)\n\t"
      "jg .Lrasterizer_swizzle_compute_masks_1\n\t"
      "movl %%esi, 0x8(%%ebp)\n\t"
      ".Lrasterizer_swizzle_compute_masks_1:\n\t"
      "movswl 0x8(%%ebp), %%ecx\n\t"
      "movl $1, %%eax\n\t"
      "shll %%cl, %%eax\n\t"
      "movl %%ecx, 0xc(%%ebp)\n\t"
      "decl %%eax\n\t"
      "cmpw $0x3f, %%ax\n\t"
      "jg .Lrasterizer_swizzle_compute_masks_2\n\t"
      "movswl 0x10(%%ebp), %%edx\n\t"
      "movswl %%ax, %%eax\n\t"
      "movl %%edx, %%esi\n\t"
      "andl %%eax, %%esi\n\t"
      "movzwl 0x2b07e0(,%%esi,2), %%edi\n\t"
      "movswl 0x14(%%ebp), %%esi\n\t"
      "movl %%esi, %%ebx\n\t"
      "andl %%eax, %%ebx\n\t"
      "movzwl 0x2b07e0(,%%ebx,2), %%eax\n\t"
      "jmp .Lrasterizer_swizzle_compute_masks_4\n\t"
      ".Lrasterizer_swizzle_compute_masks_2:\n\t"
      "movswl %%ax, %%ebx\n\t"
      "sarl $6, %%ebx\n\t"
      "cmpl $0x3f, %%ebx\n\t"
      "jle .Lrasterizer_swizzle_compute_masks_3\n\t"
      "pushl $1\n\t"
      "pushl $0x56\n\t"
      "pushl $0x2b087c\n\t"
      "pushl $0x2b086c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrasterizer_swizzle_compute_masks_3:\n\t"
      "movswl 0x10(%%ebp), %%edx\n\t"
      "movswl 0x14(%%ebp), %%esi\n\t"
      "movl %%edx, %%eax\n\t"
      "sarl $6, %%eax\n\t"
      "andl %%ebx, %%eax\n\t"
      "movzwl 0x2b07e0(,%%eax,2), %%edi\n\t"
      "movl %%edx, %%ecx\n\t"
      "andl $0x3f, %%ecx\n\t"
      "movzwl 0x2b07e0(,%%ecx,2), %%eax\n\t"
      "movl %%esi, %%ecx\n\t"
      "sarl $6, %%ecx\n\t"
      "andl %%ebx, %%ecx\n\t"
      "shll $0xc, %%edi\n\t"
      "orl %%eax, %%edi\n\t"
      "movzwl 0x2b07e0(,%%ecx,2), %%eax\n\t"
      "movl %%esi, %%ecx\n\t"
      "andl $0x3f, %%ecx\n\t"
      "movzwl 0x2b07e0(,%%ecx,2), %%ecx\n\t"
      "shll $0xc, %%eax\n\t"
      "orl %%ecx, %%eax\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      ".Lrasterizer_swizzle_compute_masks_4:\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "shll $1, %%eax\n\t"
      "cmpw %%bx, -0x4(%%ebp)\n\t"
      "jle .Lrasterizer_swizzle_compute_masks_5\n\t"
      "sarl %%cl, %%edx\n\t"
      "addl %%ecx, %%ecx\n\t"
      "shll %%cl, %%edx\n\t"
      "movl 0x18(%%ebp), %%ecx\n\t"
      "movl %%eax, 0x4(%%ecx)\n\t"
      "orl %%edx, %%edi\n\t"
      "movl %%edi, (%%ecx)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lrasterizer_swizzle_compute_masks_5:\n\t"
      "cmpw %%bx, -0x8(%%ebp)\n\t"
      "jle .Lrasterizer_swizzle_compute_masks_6\n\t"
      "sarl %%cl, %%esi\n\t"
      "addl %%ecx, %%ecx\n\t"
      "shll %%cl, %%esi\n\t"
      "orl %%esi, %%eax\n\t"
      ".Lrasterizer_swizzle_compute_masks_6:\n\t"
      "movl 0x18(%%ebp), %%ecx\n\t"
      "movl %%edi, (%%ecx)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%eax, 0x4(%%ecx)\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c108db0] "m"(b182690_c108db0), [assert] "m"(b182690_assert), [exitfn] "m"(b182690_exitfn)
      : "memory");
}
#else
#error "rasterizer_swizzle_compute_masks: clang naked draft required"
#endif


/* rasterizer_swizzle_interleave_bits (0x1827c0) — XBE naked draft (batch 90). */
#if defined(__clang__)


__attribute__((naked, noinline))
void rasterizer_swizzle_interleave_bits(short param_1 __attribute__((unused)), short param_2 __attribute__((unused)), short param_3 __attribute__((unused)), unsigned int param_4 __attribute__((unused)), unsigned int param_5 __attribute__((unused)), unsigned int param_6 __attribute__((unused)), unsigned int *param_7 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $8, %%esp\n\t"
      "pushl %%ebx\n\t"
      "xorl %%eax, %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "xorl %%edi, %%edi\n\t"
      "movl $1, %%edx\n\t"
      ".Lrasterizer_swizzle_interleave_bits_1:\n\t"
      "cmpw 0x8(%%ebp), %%dx\n\t"
      "movl %%eax, %%esi\n\t"
      "jge .Lrasterizer_swizzle_interleave_bits_2\n\t"
      "movl 0x14(%%ebp), %%ebx\n\t"
      "sarl $1, 0x14(%%ebp)\n\t"
      "movb %%al, %%cl\n\t"
      "andl $1, %%ebx\n\t"
      "shll %%cl, %%ebx\n\t"
      "orl %%ebx, -0x4(%%ebp)\n\t"
      "incl %%eax\n\t"
      ".Lrasterizer_swizzle_interleave_bits_2:\n\t"
      "cmpw 0xc(%%ebp), %%dx\n\t"
      "jge .Lrasterizer_swizzle_interleave_bits_3\n\t"
      "movl 0x18(%%ebp), %%ebx\n\t"
      "sarl $1, 0x18(%%ebp)\n\t"
      "movb %%al, %%cl\n\t"
      "andl $1, %%ebx\n\t"
      "shll %%cl, %%ebx\n\t"
      "orl %%ebx, -0x8(%%ebp)\n\t"
      "incl %%eax\n\t"
      ".Lrasterizer_swizzle_interleave_bits_3:\n\t"
      "cmpw 0x10(%%ebp), %%dx\n\t"
      "jge .Lrasterizer_swizzle_interleave_bits_4\n\t"
      "movl 0x1c(%%ebp), %%ebx\n\t"
      "sarl $1, 0x1c(%%ebp)\n\t"
      "andl $1, %%ebx\n\t"
      "movb %%al, %%cl\n\t"
      "shll %%cl, %%ebx\n\t"
      "orl %%ebx, %%edi\n\t"
      "incl %%eax\n\t"
      ".Lrasterizer_swizzle_interleave_bits_4:\n\t"
      "shll $1, %%edx\n\t"
      "cmpw %%ax, %%si\n\t"
      "jne .Lrasterizer_swizzle_interleave_bits_1\n\t"
      "movl 0x20(%%ebp), %%eax\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "movl %%edi, 0x8(%%eax)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ecx, (%%eax)\n\t"
      "movl %%edx, 0x4(%%eax)\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "rasterizer_swizzle_interleave_bits: clang naked draft required"
#endif


/* rasterizer_swizzle_bitmap_mipmaps: compute total swizzle buffer size
 * needed for all mipmaps of a bitmap (0x183290).
 * Returns total byte count, aligned to 128 bytes (or x6 for cubemaps). */
int FUN_00183290(void *param_1)
{
  int bitmap;
  short sVar2;
  short height;
  int iVar4;
  int mip_size;
  int mip_index;
  int row_pitch;
  int local_8;

  bitmap = (int)param_1;
  iVar4 = 0;
  local_8 = 0;
  sVar2 = FUN_00183120((void *)param_1);
  mip_index = 0;
  if (-1 < (int)sVar2) {
    do {
      mip_size = bitmap_mipmap_get_pixel_data_size((void *)bitmap, mip_index);
      if ((*(unsigned char *)(bitmap + 0xe) & 0x10) != 0) {
        /* swizzled/tiled: add per-row padding */
        if ((short)mip_index != 0) {
          display_assert("mipmap_index==0",
                         "c:\\halo\\SOURCE\\rasterizer\\rasterizer_swizzle.c",
                         0x1fa, 1);
          system_exit(-1);
        }
        if ((*(unsigned char *)(bitmap + 0xe) & 2) != 0) {
          display_assert("!TEST_FLAG(bitmap->flags, _bitmap_compressed_bit)",
                         "c:\\halo\\SOURCE\\rasterizer\\rasterizer_swizzle.c",
                         0x1fb, 1);
          system_exit(-1);
        }
        row_pitch = bitmap_mipmap_get_row_pitch((void *)bitmap, mip_index);
        height = (short)bitmap_mipmap_get_height((void *)bitmap, mip_index);
        mip_size = mip_size + (int)height * (-row_pitch & 0x3f);
      }
      if (*(short *)(bitmap + 10) == 2) {
        /* cubemap: divide per-face */
        mip_size = mip_size / 6;
      }
      iVar4 = local_8 + mip_size;
      mip_index = mip_index + 1;
      local_8 = iVar4;
    } while ((short)mip_index <= sVar2);
  }
  /* align total to 128 bytes */
  iVar4 = iVar4 + (-iVar4 & 0x7f);
  if (*(short *)(bitmap + 10) == 2) {
    /* cubemap: multiply back by 6 */
    return iVar4 * 6;
  }
  return iVar4;
}

/* FUN_00183390 (0x183390) — XBE naked draft (batch 314). */
#if defined(__clang__)
static int (*const b183390_c183290)(void *bitmap) = FUN_00183290;
static void (*const b183390_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b183390_exitfn)(int) = system_exit;
static void * (*const b183390_c8ee60)(uint32_t size, bool zero, const char *file, int line) = debug_malloc;
static void (*const b183390_c182e00)(int param_1) = FUN_00182e00;
static int16_t (*const b183390_c183120)(void *bitmap) = FUN_00183120;
static void * (*const b183390_c7d000)(void *bitmap, short mipmap_index) = bitmap_mipmap_address;
static int (*const b183390_c7d960)(void *bitmap, int mipmap_index) = bitmap_mipmap_get_pixel_data_size;
static int (*const b183390_c7d9f0)(void *bitmap, int mipmap_index) = bitmap_mipmap_get_row_pitch;
static void * (*const b183390_c8e0b0)(void *destination, void *source, size_t size) = csmemcpy;
static void *(*const b183390_memset)(void *, int, unsigned int) = csmemset;
static void (*const b183390_c8ef70)(void *ptr, const char *file, int line) = debug_free;
static void (*const b183390_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;

__attribute__((naked, noinline))
int FUN_00183390(int bitmap __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x20, %%esp\n\t"
      "pushl %%ebx\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "call *%[c183290]\n\t"
      "movl %%eax, %%esi\n\t"
      "xorl %%eax, %%eax\n\t"
      "addl $4, %%esp\n\t"
      "xorl %%edi, %%edi\n\t"
      "cmpw $2, 0xa(%%ebx)\n\t"
      "movl %%esi, -0x1c(%%ebp)\n\t"
      "setne %%al\n\t"
      "decl %%eax\n\t"
      "andl $5, %%eax\n\t"
      "incl %%eax\n\t"
      "movl %%eax, -0x18(%%ebp)\n\t"
      "movl 0x2c(%%ebx), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_00183390_1\n\t"
      "pushl $1\n\t"
      "pushl $0x225\n\t"
      "pushl $0x2b087c\n\t"
      "pushl $0x264c30\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00183390_1:\n\t"
      "pushl $0x228\n\t"
      "pushl $0x2b087c\n\t"
      "pushl $0\n\t"
      "pushl %%esi\n\t"
      "call *%[c8ee60]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $0x10, %%esp\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%esi, -0x4(%%ebp)\n\t"
      "je .LFUN_00183390_17\n\t"
      "pushl %%ebx\n\t"
      "call *%[c182e00]\n\t"
      "addl $4, %%esp\n\t"
      "cmpw $0, -0x18(%%ebp)\n\t"
      "movl $0, -0x10(%%ebp)\n\t"
      "jle .LFUN_00183390_14\n\t"
      ".LFUN_00183390_2:\n\t"
      "pushl %%ebx\n\t"
      "call *%[c183120]\n\t"
      "xorl %%esi, %%esi\n\t"
      "addl $4, %%esp\n\t"
      "testw %%ax, %%ax\n\t"
      "movl %%esi, -0xc(%%ebp)\n\t"
      "movl %%eax, -0x20(%%ebp)\n\t"
      "jl .LFUN_00183390_13\n\t"
      "jmp .LFUN_00183390_4\n\t"
      ".LFUN_00183390_3:\n\t"
      "movl -0xc(%%ebp), %%esi\n\t"
      ".LFUN_00183390_4:\n\t"
      "pushl %%esi\n\t"
      "pushl %%ebx\n\t"
      "call *%[c7d000]\n\t"
      "pushl %%esi\n\t"
      "pushl %%ebx\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "call *%[c7d960]\n\t"
      "movl %%eax, %%esi\n\t"
      "movswl -0x10(%%ebp), %%eax\n\t"
      "movw 0x2b0860(,%%eax,2), %%cx\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpw $2, 0xa(%%ebx)\n\t"
      "jne .LFUN_00183390_5\n\t"
      "movl $0x2aaaaaab, %%eax\n\t"
      "imull %%esi\n\t"
      "movl %%edx, %%eax\n\t"
      "shrl $0x1f, %%eax\n\t"
      "addl %%eax, %%edx\n\t"
      "movl %%edx, %%esi\n\t"
      ".LFUN_00183390_5:\n\t"
      "testb $0x10, 0xe(%%ebx)\n\t"
      "je .LFUN_00183390_16\n\t"
      "cmpw $0, -0x10(%%ebp)\n\t"
      "jne .LFUN_00183390_6\n\t"
      "testw %%cx, %%cx\n\t"
      "je .LFUN_00183390_7\n\t"
      ".LFUN_00183390_6:\n\t"
      "pushl $1\n\t"
      "pushl $0x24c\n\t"
      "pushl $0x2b087c\n\t"
      "pushl $0x2b0988\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00183390_7:\n\t"
      "movl -0xc(%%ebp), %%esi\n\t"
      "testw %%si, %%si\n\t"
      "je .LFUN_00183390_8\n\t"
      "pushl $1\n\t"
      "pushl $0x24d\n\t"
      "pushl $0x2b087c\n\t"
      "pushl $0x29dfec\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00183390_8:\n\t"
      "testb $2, 0xe(%%ebx)\n\t"
      "je .LFUN_00183390_9\n\t"
      "pushl $1\n\t"
      "pushl $0x24e\n\t"
      "pushl $0x2b087c\n\t"
      "pushl $0x264df0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00183390_9:\n\t"
      "pushl %%esi\n\t"
      "pushl %%ebx\n\t"
      "call *%[c7d9f0]\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "movl %%eax, %%esi\n\t"
      "movl %%esi, %%ebx\n\t"
      "negl %%ebx\n\t"
      "addl $8, %%esp\n\t"
      "andl $0x3f, %%ebx\n\t"
      "cmpw $0, 0x6(%%ecx)\n\t"
      "movl $0, -0x14(%%ebp)\n\t"
      "jle .LFUN_00183390_11\n\t"
      ".LFUN_00183390_10:\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%edx\n\t"
      "addl %%edi, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c8e0b0]\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "pushl %%ebx\n\t"
      "addl %%esi, %%edi\n\t"
      "addl %%edi, %%ecx\n\t"
      "pushl $0\n\t"
      "pushl %%ecx\n\t"
      "call *%[memset]\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "addl %%esi, %%ecx\n\t"
      "addl $0x18, %%esp\n\t"
      "addl %%ebx, %%edi\n\t"
      "incl %%eax\n\t"
      "cmpw 0x6(%%edx), %%ax\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "jl .LFUN_00183390_10\n\t"
      ".LFUN_00183390_11:\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      ".LFUN_00183390_12:\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "incl %%eax\n\t"
      "cmpw -0x20(%%ebp), %%ax\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "jle .LFUN_00183390_3\n\t"
      ".LFUN_00183390_13:\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "movl %%edi, %%esi\n\t"
      "negl %%esi\n\t"
      "andl $0x7f, %%esi\n\t"
      "pushl %%esi\n\t"
      "addl %%edi, %%edx\n\t"
      "pushl $0\n\t"
      "pushl %%edx\n\t"
      "call *%[memset]\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "addl %%esi, %%edi\n\t"
      "incl %%eax\n\t"
      "cmpw -0x18(%%ebp), %%ax\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "jl .LFUN_00183390_2\n\t"
      "movl -0x4(%%ebp), %%esi\n\t"
      ".LFUN_00183390_14:\n\t"
      "cmpl -0x1c(%%ebp), %%edi\n\t"
      "je .LFUN_00183390_15\n\t"
      "pushl $1\n\t"
      "pushl $0x271\n\t"
      "pushl $0x2b087c\n\t"
      "pushl $0x2b0978\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00183390_15:\n\t"
      "movl -0x1c(%%ebp), %%eax\n\t"
      "movl 0x2c(%%ebx), %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%ecx\n\t"
      "call *%[c8e0b0]\n\t"
      "pushl $0x275\n\t"
      "pushl $0x2b087c\n\t"
      "pushl %%esi\n\t"
      "call *%[c8ef70]\n\t"
      "addl $0x18, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00183390_16:\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "movswl %%cx, %%eax\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "imull %%esi, %%eax\n\t"
      "pushl %%esi\n\t"
      "addl %%edx, %%eax\n\t"
      "pushl %%eax\n\t"
      "addl %%edi, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c8e0b0]\n\t"
      "addl $0xc, %%esp\n\t"
      "addl %%esi, %%edi\n\t"
      "jmp .LFUN_00183390_12\n\t"
      ".LFUN_00183390_17:\n\t"
      "pushl $0x2b0928\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c183290] "m"(b183390_c183290), [assert] "m"(b183390_assert), [exitfn] "m"(b183390_exitfn), [c8ee60] "m"(b183390_c8ee60), [c182e00] "m"(b183390_c182e00), [c183120] "m"(b183390_c183120), [c7d000] "m"(b183390_c7d000), [c7d960] "m"(b183390_c7d960), [c7d9f0] "m"(b183390_c7d9f0), [c8e0b0] "m"(b183390_c8e0b0), [memset] "m"(b183390_memset), [c8ef70] "m"(b183390_c8ef70), [c8f390] "m"(b183390_c8f390)
      : "memory");
}
#else
#error "FUN_00183390: clang naked draft required"
#endif


/* rasterizer_text_cache_initialize: init hardware text cache (0x183650) */
int rasterizer_text_cache_initialize(void)
{
  int texture_handle;
  char success;

  if (*(char *)0x4d04a0 != 0) {
    display_assert("!hardware_character_cache.initialized",
                   "c:\\halo\\SOURCE\\rasterizer\\rasterizer_text.c", 0x76, 1);
    system_exit(-1);
  }

  texture_handle = (int)bitmap_2d_new(128, 128, 0, 9);
  if (texture_handle != 0) {
    csmemset((void *)0x4d04a0, 0, 0x810);
    success = FUN_00168370((void *)texture_handle);
    if (success != 0) {
      *(int *)0x4d04ac = texture_handle;
      *(char *)0x4d04a0 = 1;
      return 1;
    }
  }

  error(2, "### ERROR failed to initialize hardware text cache");
  return 0;
}

/* rasterizer_text_set_shadow_color: set text shadow color (0x1836e0) */
void rasterizer_text_set_shadow_color(const void *color)
{
  *(int *)0x4d0cb0 = (int)color;
}

/* rasterizer_text_cache_flush: invalidate all cached characters (0x1836f0) */
void rasterizer_text_cache_flush(void)
{
  int *slot;
  int i;

  if (*(char *)0x4d04a0 != 0) {
    slot = (int *)0x4d04b0;
    for (i = 0; i < 256; i++) {
      if (*slot != 0) {
        *(short *)(*slot + 0xc) = -1;
      }
      *slot = 0;
      slot += 2;
    }
  }
}

/* rasterizer_text_cache_dispose (0x183720) — readable C lift from XBE leaf. */
void rasterizer_text_cache_dispose(void)
{
  if (*(unsigned char *)0x4d04a0 != 0) {
    rasterizer_text_cache_flush();
    bitmap_delete(*(void **)0x4d04ac);
    *(unsigned char *)0x4d04a0 = 0;
  }
}




/* rasterizer_text.c — hardware character cache and text rendering.
 *
 * Address range: 0x183650 - 0x184060
 */

#define HARDWARE_CHARACTER_CACHE_BITMAP_WIDTH 128
#define HARDWARE_CHARACTER_CACHE_BITMAP_HEIGHT 128
#define MAXIMUM_HARDWARE_CHARACTERS 256

/* Hardware character cache (0x4d04a0, 0x810 bytes):
 *   +0x00 (byte):   initialized
 *   +0x02 (ushort): read_index   (wraps at 256)
 *   +0x04 (ushort): write_index  (wraps at 256)
 *   +0x06 (short):  cursor_x
 *   +0x08 (short):  cursor_y
 *   +0x0a (short):  max_char_height
 *   +0x0c (int):    texture_handle
 *   +0x10-0x810:    character_table[256] entries (8 bytes each):
 *       +0x0 (int*):   character pointer
 *       +0x4 (short):  screen_x
 *       +0x6 (short):  screen_y
 */

/* rasterizer_text_get_character_position (0x183770) — XBE naked draft (batch 91). */
#if defined(__clang__)
static void (*const b183770_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b183770_exitfn)(int) = system_exit;

__attribute__((naked, noinline))
void rasterizer_text_get_character_position(short index __attribute__((unused)), short *out_y __attribute__((unused)), short *out_x __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%esi\n\t"
      "movw %%ax, %%si\n\t"
      "movb 0x4d04a0, %%al\n\t"
      "testb %%al, %%al\n\t"
      "pushl %%edi\n\t"
      "movswl %%si, %%edi\n\t"
      "leal 0x4d04b0(,%%edi,8), %%edi\n\t"
      "jne .Lrasterizer_text_get_character_position_1\n\t"
      "pushl $1\n\t"
      "pushl $0x255\n\t"
      "pushl $0x2b0a0c\n\t"
      "pushl $0x2b0a9c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrasterizer_text_get_character_position_1:\n\t"
      "testw %%si, %%si\n\t"
      "jl .Lrasterizer_text_get_character_position_2\n\t"
      "cmpw $0x100, %%si\n\t"
      "jl .Lrasterizer_text_get_character_position_3\n\t"
      ".Lrasterizer_text_get_character_position_2:\n\t"
      "pushl $1\n\t"
      "pushl $0x256\n\t"
      "pushl $0x2b0a0c\n\t"
      "pushl $0x2b0a48\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrasterizer_text_get_character_position_3:\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .Lrasterizer_text_get_character_position_4\n\t"
      "testl %%ebx, %%ebx\n\t"
      "jne .Lrasterizer_text_get_character_position_5\n\t"
      ".Lrasterizer_text_get_character_position_4:\n\t"
      "pushl $1\n\t"
      "pushl $0x257\n\t"
      "pushl $0x2b0a0c\n\t"
      "pushl $0x2b0a38\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrasterizer_text_get_character_position_5:\n\t"
      "movw 0x4(%%edi), %%ax\n\t"
      "movw %%ax, (%%esi)\n\t"
      "movw 0x6(%%edi), %%cx\n\t"
      "popl %%edi\n\t"
      "movw %%cx, (%%ebx)\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b183770_assert), [exitfn] "m"(b183770_exitfn)
      : "memory");
}
#else
#error "rasterizer_text_get_character_position: clang naked draft required"
#endif


/* rasterizer_text_evict_character (0x183820) — XBE naked draft (batch 97). */
#if defined(__clang__)
static void (*const b183820_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b183820_exitfn)(int) = system_exit;
static void (*const b183820_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;

__attribute__((naked, noinline))
void rasterizer_text_evict_character(int **slot __attribute__((unused)))
{
  __asm__ volatile(
      "testl %%esi, %%esi\n\t"
      "jne .Lrasterizer_text_evict_character_1\n\t"
      "pushl $1\n\t"
      "pushl $0x262\n\t"
      "pushl $0x2b0a0c\n\t"
      "pushl $0x2b0aec\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrasterizer_text_evict_character_1:\n\t"
      "movl (%%esi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lrasterizer_text_evict_character_3\n\t"
      "movw $0xffff, 0xc(%%eax)\n\t"
      "movl (%%esi), %%eax\n\t"
      "movw 0xe(%%eax), %%cx\n\t"
      "cmpw 0x325748, %%cx\n\t"
      "jne .Lrasterizer_text_evict_character_2\n\t"
      "pushl $0x2b0ac4\n\t"
      "pushl $3\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      ".Lrasterizer_text_evict_character_2:\n\t"
      "movl $0, (%%esi)\n\t"
      ".Lrasterizer_text_evict_character_3:\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b183820_assert), [exitfn] "m"(b183820_exitfn), [c8f390] "m"(b183820_c8f390)
      : "memory");
}
#else
#error "rasterizer_text_evict_character: clang naked draft required"
#endif


/* rasterizer_text_cache_character (0x183880) — XBE naked draft (batch 80). */
#if defined(__clang__)
static void (*const b183880_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b183880_exitfn)(int) = system_exit;
static void (*const b183880_c183820)(int **slot) = rasterizer_text_evict_character;
static void (*const b183880_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;
static void * (*const b183880_c7c940)(void *bitmap, short x, short y, short mipmap_index) = bitmap_2d_address;
static void (*const b183880_c168b10)(void *bitmap) = FUN_00168b10;

__attribute__((naked, noinline))
void rasterizer_text_cache_character(void *font_character __attribute__((unused)), void *font __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "movb 0x4d04a0, %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lrasterizer_text_cache_character_1\n\t"
      "pushl $1\n\t"
      "pushl $0x279\n\t"
      "pushl $0x2b0a0c\n\t"
      "pushl $0x2b0a9c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrasterizer_text_cache_character_1:\n\t"
      "movw 0xc(%%edi), %%ax\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .Lrasterizer_text_cache_character_4\n\t"
      "testw %%ax, %%ax\n\t"
      "jl .Lrasterizer_text_cache_character_2\n\t"
      "cmpw $0x100, %%ax\n\t"
      "jl .Lrasterizer_text_cache_character_3\n\t"
      ".Lrasterizer_text_cache_character_2:\n\t"
      "pushl $1\n\t"
      "pushl $0x27d\n\t"
      "pushl $0x2b0a0c\n\t"
      "pushl $0x2b0bf8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrasterizer_text_cache_character_3:\n\t"
      "movswl 0xc(%%edi), %%eax\n\t"
      "cmpl 0x4d04b0(,%%eax,8), %%edi\n\t"
      "je .Lrasterizer_text_cache_character_22\n\t"
      "pushl $1\n\t"
      "pushl $0x27e\n\t"
      "pushl $0x2b0a0c\n\t"
      "pushl $0x2b0b90\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lrasterizer_text_cache_character_4:\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl $0x80, %%esi\n\t"
      "cmpw %%si, 0x4(%%edi)\n\t"
      "jle .Lrasterizer_text_cache_character_5\n\t"
      "pushl $1\n\t"
      "pushl $0x285\n\t"
      "pushl $0x2b0a0c\n\t"
      "pushl $0x2b0b48\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrasterizer_text_cache_character_5:\n\t"
      "cmpw %%si, 0x6(%%edi)\n\t"
      "jle .Lrasterizer_text_cache_character_6\n\t"
      "pushl $1\n\t"
      "pushl $0x286\n\t"
      "pushl $0x2b0a0c\n\t"
      "pushl $0x2b0b00\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrasterizer_text_cache_character_6:\n\t"
      "movw 0x325748, %%cx\n\t"
      "movswl 0x4(%%edi), %%edx\n\t"
      "movw %%cx, 0xe(%%edi)\n\t"
      "movswl 0x4d04a6, %%eax\n\t"
      "addl %%eax, %%edx\n\t"
      "cmpl %%esi, %%edx\n\t"
      "jle .Lrasterizer_text_cache_character_7\n\t"
      "movw 0x4d04aa, %%cx\n\t"
      "xorl %%eax, %%eax\n\t"
      "addw %%cx, 0x4d04a8\n\t"
      "movw %%ax, 0x4d04a6\n\t"
      "movw %%ax, 0x4d04aa\n\t"
      ".Lrasterizer_text_cache_character_7:\n\t"
      "movswl 0x6(%%edi), %%edx\n\t"
      "movswl 0x4d04a8, %%eax\n\t"
      "addl %%eax, %%edx\n\t"
      "cmpl %%esi, %%edx\n\t"
      "jle .Lrasterizer_text_cache_character_9\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw %%ax, 0x4d04a8\n\t"
      "movw %%ax, 0x4d04a6\n\t"
      "movw %%ax, 0x4d04aa\n\t"
      "movw 0x4d04a2, %%ax\n\t"
      "cmpw 0x4d04a4, %%ax\n\t"
      "je .Lrasterizer_text_cache_character_10\n\t"
      "jmp .Lrasterizer_text_cache_character_8\n\t"
      "leal (%%esp), %%esp\n\t"
      "nop\n\t"
      ".Lrasterizer_text_cache_character_8:\n\t"
      "movswl %%ax, %%esi\n\t"
      "cmpw $0, 0x4d04b6(,%%esi,8)\n\t"
      "leal 0x4d04b0(,%%esi,8), %%esi\n\t"
      "jle .Lrasterizer_text_cache_character_10\n\t"
      "call *%[c183820]\n\t"
      "xorl %%eax, %%eax\n\t"
      "movb 0x4d04a2, %%al\n\t"
      "incb %%al\n\t"
      "andl $0xff, %%eax\n\t"
      "cmpw 0x4d04a4, %%ax\n\t"
      "movw %%ax, 0x4d04a2\n\t"
      "jne .Lrasterizer_text_cache_character_8\n\t"
      "jmp .Lrasterizer_text_cache_character_10\n\t"
      ".Lrasterizer_text_cache_character_9:\n\t"
      "movw 0x4d04a2, %%ax\n\t"
      ".Lrasterizer_text_cache_character_10:\n\t"
      "movw 0x6(%%edi), %%cx\n\t"
      "movw 0x4d04aa, %%dx\n\t"
      "cmpw %%dx, %%cx\n\t"
      "jle .Lrasterizer_text_cache_character_13\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "movw 0x4d04a8, %%bx\n\t"
      "addw %%dx, %%bx\n\t"
      "movl 0x4d04a8, %%edx\n\t"
      "addl %%edx, %%ecx\n\t"
      "cmpw 0x4d04a4, %%ax\n\t"
      "movl %%ecx, -0x4(%%ebp)\n\t"
      "je .Lrasterizer_text_cache_character_12\n\t"
      "nop\n\t"
      ".Lrasterizer_text_cache_character_11:\n\t"
      "movswl %%ax, %%esi\n\t"
      "movw 0x4d04b6(,%%esi,8), %%cx\n\t"
      "cmpw %%bx, %%cx\n\t"
      "leal 0x4d04b0(,%%esi,8), %%esi\n\t"
      "jl .Lrasterizer_text_cache_character_12\n\t"
      "cmpw -0x4(%%ebp), %%cx\n\t"
      "jge .Lrasterizer_text_cache_character_12\n\t"
      "call *%[c183820]\n\t"
      "xorl %%eax, %%eax\n\t"
      "movb 0x4d04a2, %%al\n\t"
      "incb %%al\n\t"
      "andl $0xff, %%eax\n\t"
      "cmpw 0x4d04a4, %%ax\n\t"
      "movw %%ax, 0x4d04a2\n\t"
      "jne .Lrasterizer_text_cache_character_11\n\t"
      ".Lrasterizer_text_cache_character_12:\n\t"
      "movw 0x6(%%edi), %%cx\n\t"
      "movw %%cx, 0x4d04aa\n\t"
      ".Lrasterizer_text_cache_character_13:\n\t"
      "xorl %%edx, %%edx\n\t"
      "movb 0x4d04a4, %%dl\n\t"
      "incb %%dl\n\t"
      "andl $0xff, %%edx\n\t"
      "cmpw %%ax, %%dx\n\t"
      "jne .Lrasterizer_text_cache_character_17\n\t"
      "movswl %%ax, %%esi\n\t"
      "leal 0x4d04b0(,%%esi,8), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .Lrasterizer_text_cache_character_14\n\t"
      "pushl $1\n\t"
      "pushl $0x262\n\t"
      "pushl $0x2b0a0c\n\t"
      "pushl $0x2b0aec\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrasterizer_text_cache_character_14:\n\t"
      "movl (%%esi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lrasterizer_text_cache_character_16\n\t"
      "movw 0x325748, %%cx\n\t"
      "movw $0xffff, 0xc(%%eax)\n\t"
      "movl (%%esi), %%eax\n\t"
      "cmpw %%cx, 0xe(%%eax)\n\t"
      "jne .Lrasterizer_text_cache_character_15\n\t"
      "pushl $0x2b0ac4\n\t"
      "pushl $3\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      ".Lrasterizer_text_cache_character_15:\n\t"
      "movl $0, (%%esi)\n\t"
      ".Lrasterizer_text_cache_character_16:\n\t"
      "xorl %%edx, %%edx\n\t"
      "movb 0x4d04a2, %%dl\n\t"
      "incb %%dl\n\t"
      "andl $0xff, %%edx\n\t"
      "movw %%dx, 0x4d04a2\n\t"
      ".Lrasterizer_text_cache_character_17:\n\t"
      "movw 0x4d04a4, %%ax\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "movswl %%ax, %%ebx\n\t"
      "movw %%ax, 0xc(%%edi)\n\t"
      "leal 0x4d04b0(,%%ebx,8), %%ebx\n\t"
      "movl %%edi, (%%ebx)\n\t"
      "movw 0x4d04a6, %%ax\n\t"
      "movw %%ax, 0x4(%%ebx)\n\t"
      "movw 0x4d04a8, %%cx\n\t"
      "movw %%cx, 0x6(%%ebx)\n\t"
      "movl 0x94(%%edx), %%esi\n\t"
      "addl 0x10(%%edi), %%esi\n\t"
      "cmpw $0, 0x6(%%edi)\n\t"
      "movl $0, -0x4(%%ebp)\n\t"
      "jle .Lrasterizer_text_cache_character_21\n\t"
      "leal (%%esp), %%esp\n\t"
      ".Lrasterizer_text_cache_character_18:\n\t"
      "movl 0x4d04ac, %%edx\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x6(%%ebx), %%ax\n\t"
      "addw -0x4(%%ebp), %%ax\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x4(%%ebx), %%cx\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c7c940]\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpw %%cx, 0x4(%%edi)\n\t"
      "jle .Lrasterizer_text_cache_character_20\n\t"
      "jmp .Lrasterizer_text_cache_character_19\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".Lrasterizer_text_cache_character_19:\n\t"
      "xorl %%edx, %%edx\n\t"
      "movb (%%esi), %%dh\n\t"
      "addl $2, %%eax\n\t"
      "orl $0xfff, %%edx\n\t"
      "movw %%dx, -0x2(%%eax)\n\t"
      "incl %%esi\n\t"
      "incl %%ecx\n\t"
      "cmpw 0x4(%%edi), %%cx\n\t"
      "jl .Lrasterizer_text_cache_character_19\n\t"
      ".Lrasterizer_text_cache_character_20:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "incl %%eax\n\t"
      "cmpw 0x6(%%edi), %%ax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "jl .Lrasterizer_text_cache_character_18\n\t"
      ".Lrasterizer_text_cache_character_21:\n\t"
      "movl 0x4d04ac, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c168b10]\n\t"
      "movw 0x4(%%edi), %%cx\n\t"
      "addw %%cx, 0x4d04a6\n\t"
      "xorl %%edx, %%edx\n\t"
      "movb 0x4d04a4, %%dl\n\t"
      "addl $4, %%esp\n\t"
      "incb %%dl\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "andl $0xff, %%edx\n\t"
      "movw %%dx, 0x4d04a4\n\t"
      ".Lrasterizer_text_cache_character_22:\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b183880_assert), [exitfn] "m"(b183880_exitfn), [c183820] "m"(b183880_c183820), [c8f390] "m"(b183880_c8f390), [c7c940] "m"(b183880_c7c940), [c168b10] "m"(b183880_c168b10)
      : "memory");
}
#else
#error "rasterizer_text_cache_character: clang naked draft required"
#endif


/* rasterizer_text_draw_cached_char (0x183c00) — XBE naked draft (batch 86). */
#if defined(__clang__)
static void (*const b183c00_c183880)(void *font_character, void *font) = rasterizer_text_cache_character;
static void (*const b183c00_c183770)(short index, short *out_y, short *out_x) = rasterizer_text_get_character_position;
static void (*const b183c00_c1741d0)(float *quad) = FUN_001741d0;

__attribute__((naked, noinline))
void rasterizer_text_draw_cached_char(void *arg0 __attribute__((unused)), void *font __attribute__((unused)), void *font_character __attribute__((unused)), unsigned int color __attribute__((unused)), short x __attribute__((unused)), short y __attribute__((unused)), int screen_x __attribute__((unused)), int screen_y __attribute__((unused)), short width __attribute__((unused)), short height __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x54, %%esp\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "pushl %%edi\n\t"
      "movl 0x10(%%ebp), %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[c183880]\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0xc(%%edi), %%ax\n\t"
      "addl $4, %%esp\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .Lrasterizer_text_draw_cached_char_1\n\t"
      "pushl %%ebx\n\t"
      "leal 0x10(%%ebp), %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%ecx\n\t"
      "leal -0x4(%%ebp), %%ebx\n\t"
      "call *%[c183770]\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "movl 0x24(%%ebp), %%esi\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "movl 0x20(%%ebp), %%edi\n\t"
      "addl %%esi, %%edx\n\t"
      "movswl 0x18(%%ebp), %%esi\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "movl %%eax, -0x1c(%%ebp)\n\t"
      "movl %%eax, -0x30(%%ebp)\n\t"
      "movl %%eax, -0x44(%%ebp)\n\t"
      "movswl 0x28(%%ebp), %%eax\n\t"
      "movl %%esi, 0x10(%%ebp)\n\t"
      "addl %%eax, %%esi\n\t"
      "fildl 0x10(%%ebp)\n\t"
      "addl %%edi, %%ecx\n\t"
      "movswl 0x1c(%%ebp), %%edi\n\t"
      "fsts -0x18(%%ebp)\n\t"
      "fstps -0x54(%%ebp)\n\t"
      "movl %%esi, 0x10(%%ebp)\n\t"
      "movswl 0x2c(%%ebp), %%esi\n\t"
      "fildl 0x10(%%ebp)\n\t"
      "movl %%edi, 0x10(%%ebp)\n\t"
      "fsts -0x2c(%%ebp)\n\t"
      "addl %%esi, %%edi\n\t"
      "fstps -0x40(%%ebp)\n\t"
      "movswl %%cx, %%ecx\n\t"
      "fildl 0x10(%%ebp)\n\t"
      "movl %%edi, 0x10(%%ebp)\n\t"
      "fsts -0x3c(%%ebp)\n\t"
      "fstps -0x50(%%ebp)\n\t"
      "fildl 0x10(%%ebp)\n\t"
      "movl %%ecx, 0x10(%%ebp)\n\t"
      "addl %%eax, %%ecx\n\t"
      "movswl %%dx, %%eax\n\t"
      "fsts -0x14(%%ebp)\n\t"
      "leal -0x54(%%ebp), %%edx\n\t"
      "fstps -0x28(%%ebp)\n\t"
      "pushl %%edx\n\t"
      "fildl 0x10(%%ebp)\n\t"
      "movl %%ecx, 0x10(%%ebp)\n\t"
      "fsts -0x10(%%ebp)\n\t"
      "fstps -0x4c(%%ebp)\n\t"
      "fildl 0x10(%%ebp)\n\t"
      "movl %%eax, 0x10(%%ebp)\n\t"
      "addl %%esi, %%eax\n\t"
      "fsts -0x24(%%ebp)\n\t"
      "fstps -0x38(%%ebp)\n\t"
      "fildl 0x10(%%ebp)\n\t"
      "movl %%eax, 0x10(%%ebp)\n\t"
      "fsts -0x34(%%ebp)\n\t"
      "fstps -0x48(%%ebp)\n\t"
      "fildl 0x10(%%ebp)\n\t"
      "fsts -0xc(%%ebp)\n\t"
      "fstps -0x20(%%ebp)\n\t"
      "call *%[c1741d0]\n\t"
      "addl $8, %%esp\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      ".Lrasterizer_text_draw_cached_char_1:\n\t"
      "popl %%edi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c183880] "m"(b183c00_c183880), [c183770] "m"(b183c00_c183770), [c1741d0] "m"(b183c00_c1741d0)
      : "memory");
}
#else
#error "rasterizer_text_draw_cached_char: clang naked draft required"
#endif


/* rasterizer_text_draw_cached_chars (0x183cf0) — XBE naked draft (batch 84). */
#if defined(__clang__)
static void (*const b183cf0_c183880)(void *font_character, void *font) = rasterizer_text_cache_character;
static void (*const b183cf0_c183770)(short index, short *out_y, short *out_x) = rasterizer_text_get_character_position;
static void (*const b183cf0_c1741d0)(float *quad) = FUN_001741d0;

__attribute__((naked, noinline))
void rasterizer_text_draw_cached_chars(void *arg0 __attribute__((unused)), void *font __attribute__((unused)), void *font_character __attribute__((unused)), unsigned int color __attribute__((unused)), short x __attribute__((unused)), short y __attribute__((unused)), int offset_x __attribute__((unused)), int offset_y __attribute__((unused)), short width __attribute__((unused)), short height __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x7c, %%esp\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "pushl %%edi\n\t"
      "movl 0x10(%%ebp), %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[c183880]\n\t"
      "addl $4, %%esp\n\t"
      "cmpw $-1, 0xc(%%edi)\n\t"
      "je .Lrasterizer_text_draw_cached_chars_5\n\t"
      "movl 0x4d0cb0, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "movl $0x3f800000, -0x14(%%ebp)\n\t"
      "movl $0x3f800000, -0x10(%%ebp)\n\t"
      "jne .Lrasterizer_text_draw_cached_chars_1\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "andl $0xff000000, %%eax\n\t"
      ".Lrasterizer_text_draw_cached_chars_1:\n\t"
      "movswl 0x2c(%%ebp), %%edi\n\t"
      "movl %%eax, -0x18(%%ebp)\n\t"
      "movswl 0x18(%%ebp), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movswl 0x28(%%ebp), %%esi\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "leal (%%esi,%%eax,1), %%ecx\n\t"
      "fildl -0xc(%%ebp)\n\t"
      "movswl 0x1c(%%ebp), %%eax\n\t"
      "fstps -0x1c(%%ebp)\n\t"
      "movl %%ecx, -0xc(%%ebp)\n\t"
      "leal (%%edi,%%eax,1), %%edx\n\t"
      "fildl -0xc(%%ebp)\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "fstps -0x20(%%ebp)\n\t"
      "fildl -0xc(%%ebp)\n\t"
      "movl %%edx, -0xc(%%ebp)\n\t"
      "fstps -0x24(%%ebp)\n\t"
      "fildl -0xc(%%ebp)\n\t"
      "fstps -0x28(%%ebp)\n\t"
      ".Lrasterizer_text_draw_cached_chars_2:\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "leal -0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movw 0xc(%%ecx), %%ax\n\t"
      "leal -0xc(%%ebp), %%ebx\n\t"
      "call *%[c183770]\n\t"
      "movl -0x8(%%ebp), %%ebx\n\t"
      "movl 0x20(%%ebp), %%edx\n\t"
      "movl 0x24(%%ebp), %%eax\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "addl %%edx, %%ebx\n\t"
      "movl %%ebx, -0x8(%%ebp)\n\t"
      "movb -0x1(%%ebp), %%bl\n\t"
      "addl %%eax, %%ecx\n\t"
      "movl -0x18(%%ebp), %%eax\n\t"
      "addl $4, %%esp\n\t"
      "testb %%bl, %%bl\n\t"
      "movl %%ecx, -0xc(%%ebp)\n\t"
      "jne .Lrasterizer_text_draw_cached_chars_3\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      ".Lrasterizer_text_draw_cached_chars_3:\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "movl %%eax, -0x30(%%ebp)\n\t"
      "fadds -0x14(%%ebp)\n\t"
      "movl %%eax, -0x44(%%ebp)\n\t"
      "movl %%eax, -0x58(%%ebp)\n\t"
      "movl %%eax, -0x6c(%%ebp)\n\t"
      "fsts -0x40(%%ebp)\n\t"
      "movswl -0x8(%%ebp), %%eax\n\t"
      "fstps -0x7c(%%ebp)\n\t"
      "movl %%eax, -0x2c(%%ebp)\n\t"
      "flds -0x20(%%ebp)\n\t"
      "addl %%esi, %%eax\n\t"
      "fadds -0x14(%%ebp)\n\t"
      "leal -0x7c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "fsts -0x54(%%ebp)\n\t"
      "fstps -0x68(%%ebp)\n\t"
      "flds -0x24(%%ebp)\n\t"
      "fadds -0x10(%%ebp)\n\t"
      "fsts -0x64(%%ebp)\n\t"
      "fstps -0x78(%%ebp)\n\t"
      "flds -0x28(%%ebp)\n\t"
      "fadds -0x10(%%ebp)\n\t"
      "fsts -0x3c(%%ebp)\n\t"
      "fstps -0x50(%%ebp)\n\t"
      "fildl -0x2c(%%ebp)\n\t"
      "movl %%eax, -0x2c(%%ebp)\n\t"
      "movswl -0xc(%%ebp), %%eax\n\t"
      "fsts -0x38(%%ebp)\n\t"
      "fstps -0x74(%%ebp)\n\t"
      "fildl -0x2c(%%ebp)\n\t"
      "movl %%eax, -0x2c(%%ebp)\n\t"
      "addl %%edi, %%eax\n\t"
      "fsts -0x4c(%%ebp)\n\t"
      "fstps -0x60(%%ebp)\n\t"
      "fildl -0x2c(%%ebp)\n\t"
      "movl %%eax, -0x2c(%%ebp)\n\t"
      "fsts -0x5c(%%ebp)\n\t"
      "fstps -0x70(%%ebp)\n\t"
      "fildl -0x2c(%%ebp)\n\t"
      "fsts -0x34(%%ebp)\n\t"
      "fstps -0x48(%%ebp)\n\t"
      "call *%[c1741d0]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%bl, %%bl\n\t"
      "je .Lrasterizer_text_draw_cached_chars_4\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "movl $0, -0x10(%%ebp)\n\t"
      "movl $0, -0x14(%%ebp)\n\t"
      "jmp .Lrasterizer_text_draw_cached_chars_2\n\t"
      ".Lrasterizer_text_draw_cached_chars_4:\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      ".Lrasterizer_text_draw_cached_chars_5:\n\t"
      "popl %%edi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c183880] "m"(b183cf0_c183880), [c183770] "m"(b183cf0_c183770), [c1741d0] "m"(b183cf0_c1741d0)
      : "memory");
}
#else
#error "rasterizer_text_draw_cached_chars: clang naked draft required"
#endif


/* rasterizer_text_draw: draw ASCII string (0x183e60) */
void rasterizer_text_draw(void *screen_pos, short *bounds, const void *color,
                          int flags, const char *text)
{
  int draw_bounds[4];
  int clip_bounds[4];
  float texel_width;
  float texel_height;
  float widget_params[35];
  void *texture;
  int font_width;
  int font_height;
  int max_width;
  int max_height;
  int clamp_x;
  int clamp_y;

  if (*(char *)0x3256da == 0 || *(short *)0x5a5bc0 != 0) {
    return;
  }

  *(short *)0x325748 += 1;

  if (text == (const char *)0) {
    display_assert("string", "c:\\halo\\SOURCE\\rasterizer\\rasterizer_text.c",
                   0xb4, 1);
    system_exit(-1);
  }

  texture = (void *)(*(int *)0x4d04ac);
  if ((*(char *)0x4d04a0 != 0) && texture != (void *)0 && *text != 0) {
    csstrlen(text);

    if (screen_pos == (void *)0) {
      draw_bounds[0] = *(int *)0x506584;
      draw_bounds[1] = *(int *)0x506588;
      rect2d_offset((short *)draw_bounds, (short)(-*(short *)0x50657e),
                    (short)(-*(short *)0x50657c));
    } else {
      draw_bounds[0] = *(int *)screen_pos;
      draw_bounds[1] = *(int *)((char *)screen_pos + 4);
    }

    if (bounds == (short *)0) {
      clip_bounds[0] = *(int *)0x50657c;
      clip_bounds[1] = *(int *)0x506580;
      rect2d_offset((short *)clip_bounds, (short)(-*(short *)0x50657e),
                    (short)(-*(short *)0x50657c));
    } else {
      max_width = (int)bounds[2];
      if ((int)(*(short *)0x506580 - *(short *)0x50657c) <= (int)bounds[2]) {
        max_width = (int)(*(short *)0x506580 - *(short *)0x50657c);
      }
      max_height = (int)(*(short *)0x506582 - *(short *)0x50657e);
      if ((int)bounds[3] < max_height) {
        max_height = (int)bounds[3];
      }
      clamp_x = (int)bounds[0];
      if (bounds[0] < 0) {
        clamp_x = 0;
      }
      clamp_y = (int)bounds[1];
      if (bounds[1] < 0) {
        clamp_y = 0;
      }
      FUN_001089a0(clip_bounds, clamp_y, clamp_x, max_height, max_width);
      texture = (void *)(*(int *)0x4d04ac);
    }

    csmemset(widget_params, 0, 0x8c);
    font_width = (int)*(short *)((int)texture + 4);
    font_height = (int)*(short *)((int)texture + 6);
    texel_width = *(float *)0x2533c8 / (float)font_width;
    texel_height = *(float *)0x2533c8 / (float)font_height;

    *(unsigned int *)&widget_params[3] = (unsigned int)texture;
    widget_params[10] = 1.0f;
    widget_params[11] = 1.0f;
    widget_params[16] = texel_width;
    widget_params[17] = texel_height;

    FUN_00173b40(widget_params);
    FUN_0019c5d0(rasterizer_text_draw_cached_chars, draw_bounds, color,
                 clip_bounds, flags, (char *)text);
    FUN_00173ae0();
  }
}

/* rasterizer_draw_string: draw wide-character string (0x184060) */
void rasterizer_draw_string(void *screen_pos, short *bounds, const void *color,
                            int flags, unsigned short *text)
{
  int draw_bounds[4];
  int clip_bounds[4];
  float texel_width;
  float texel_height;
  float widget_params[35];
  void *texture;
  int font_width;
  int font_height;
  int max_width;
  int max_height;
  int clamp_x;
  int clamp_y;

  if (*(char *)0x3256da == 0 || *(short *)0x5a5bc0 != 0) {
    return;
  }

  *(short *)0x325748 += 1;

  if (text == (unsigned short *)0) {
    display_assert("string", "c:\\halo\\SOURCE\\rasterizer\\rasterizer_text.c",
                   0x136, 1);
    system_exit(-1);
  }

  texture = (void *)(*(int *)0x4d04ac);
  if ((*(char *)0x4d04a0 != 0) && texture != (void *)0 && *text != 0) {
    ustrlen(text);

    if (screen_pos == (void *)0) {
      draw_bounds[0] = *(int *)0x506584;
      draw_bounds[1] = *(int *)0x506588;
      rect2d_offset((short *)draw_bounds, (short)(-*(short *)0x50657e),
                    (short)(-*(short *)0x50657c));
    } else {
      draw_bounds[0] = *(int *)screen_pos;
      draw_bounds[1] = *(int *)((char *)screen_pos + 4);
    }

    if (bounds == (short *)0) {
      clip_bounds[0] = *(int *)0x50657c;
      clip_bounds[1] = *(int *)0x506580;
      rect2d_offset((short *)clip_bounds, (short)(-*(short *)0x50657e),
                    (short)(-*(short *)0x50657c));
    } else {
      max_width = (int)bounds[2];
      if ((int)(*(short *)0x506580 - *(short *)0x50657c) <= (int)bounds[2]) {
        max_width = (int)(*(short *)0x506580 - *(short *)0x50657c);
      }
      max_height = (int)(*(short *)0x506582 - *(short *)0x50657e);
      if ((int)bounds[3] < max_height) {
        max_height = (int)bounds[3];
      }
      clamp_x = (int)bounds[0];
      if (bounds[0] < 0) {
        clamp_x = 0;
      }
      clamp_y = (int)bounds[1];
      if (bounds[1] < 0) {
        clamp_y = 0;
      }
      FUN_001089a0(clip_bounds, clamp_y, clamp_x, max_height, max_width);
      texture = (void *)(*(int *)0x4d04ac);
    }

    csmemset(widget_params, 0, 0x8c);
    font_width = (int)*(short *)((int)texture + 4);
    font_height = (int)*(short *)((int)texture + 6);
    texel_width = *(float *)0x2533c8 / (float)font_width;
    texel_height = *(float *)0x2533c8 / (float)font_height;

    *(unsigned int *)&widget_params[3] = (unsigned int)texture;
    widget_params[10] = 1.0f;
    widget_params[11] = 1.0f;
    widget_params[16] = texel_width;
    widget_params[17] = texel_height;

    FUN_00173b40(widget_params);
    FUN_0019c960(rasterizer_text_draw_cached_chars, draw_bounds, color,
                 clip_bounds, flags, text);
    FUN_00173ae0();
  }
}

/* rasterizer_transparent_geometry.c */

/* rasterizer_transparent_geometry_new (0x184260) — XBE naked draft (batch 93). */
#if defined(__clang__)
static void * (*const b184260_c8ee60)(uint32_t size, bool zero, const char *file, int line) = debug_malloc;
static void (*const b184260_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;
static int (*const b184260_c174bd0)(void) = FUN_00174bd0;

__attribute__((naked, noinline))
int rasterizer_transparent_geometry_new(void)
{
  __asm__ volatile(
      "pushl $0x29\n\t"
      "pushl $0x2b0ca8\n\t"
      "pushl $0\n\t"
      "pushl $0xf000\n\t"
      "call *%[c8ee60]\n\t"
      "pushl $0x2b\n\t"
      "pushl $0x2b0ca8\n\t"
      "pushl $0\n\t"
      "pushl $0x300\n\t"
      "movl %%eax, 0x4d0cec\n\t"
      "call *%[c8ee60]\n\t"
      "pushl $0x2e\n\t"
      "pushl $0x2b0ca8\n\t"
      "pushl $0\n\t"
      "pushl $0x1400\n\t"
      "movl %%eax, 0x4d0cfc\n\t"
      "call *%[c8ee60]\n\t"
      "movl 0x4d0cec, %%ecx\n\t"
      "addl $0x30, %%esp\n\t"
      "testl %%ecx, %%ecx\n\t"
      "movl %%eax, 0x4d0cf0\n\t"
      "movl $0, 0x4d0cf8\n\t"
      "movl $0, 0x4d0cf4\n\t"
      "je .Lrasterizer_transparent_geometry_new_1\n\t"
      "movl 0x4d0cfc, %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .Lrasterizer_transparent_geometry_new_1\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lrasterizer_transparent_geometry_new_3\n\t"
      ".Lrasterizer_transparent_geometry_new_1:\n\t"
      "pushl $0x2b0c6c\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      ".Lrasterizer_transparent_geometry_new_2:\n\t"
      "xorb %%al, %%al\n\t"
      "ret\n\t"
      ".Lrasterizer_transparent_geometry_new_3:\n\t"
      "call *%[c174bd0]\n\t"
      "testb %%al, %%al\n\t"
      "je .Lrasterizer_transparent_geometry_new_2\n\t"
      "movb $1, %%al\n\t"
      "ret\n\t"
      :
      : [c8ee60] "m"(b184260_c8ee60), [c8f390] "m"(b184260_c8f390), [c174bd0] "m"(b184260_c174bd0)
      : "memory");
}
#else
#error "rasterizer_transparent_geometry_new: clang naked draft required"
#endif


/* rasterizer_transparent_geometry_begin (0x184300) — readable C lift from XBE leaf. */
void rasterizer_transparent_geometry_begin(void)
{
  *(int *)0x4d0cf4 = 0;
  *(short *)0x4d0d00 = 0;
  csmemset((void *)0x4d0cbc, 0, 0x30);
  *(int *)0x4d0cf8 = 0;
}




/* rasterizer_transparent_geometry_group_new (0x184330) — readable C lift. */
void *rasterizer_transparent_geometry_group_new(void)
{
  int index;
  char *base;
  char *group;

  index = *(int *)0x4d0cf4;
  if (index >= 0x180)
    return NULL;
  base = *(char **)0x4d0cec;
  group = base + index * 0xa0;
  *(int *)(group + 0x90) = index;
  *(int *)0x4d0cf4 = index + 1;
  return group;
}

/* rasterizer_secondary_geometry_group_new (0x184360) — readable C lift. */
void *rasterizer_secondary_geometry_group_new(void)
{
  int index;
  char *base;
  char *group;

  index = *(int *)0x4d0cf8;
  if (index >= 0x20)
    return NULL;
  base = *(char **)0x4d0cf0;
  group = base + index * 0xa0;
  *(int *)(group + 0x90) = index;
  *(int *)0x4d0cf8 = index + 1;
  return group;
}

/* rasterizer_secondary_geometry_groups_get (0x184390) — readable C lift. */
void *rasterizer_secondary_geometry_groups_get(uint16_t *out_count)
{
  if (out_count != NULL)
    *out_count = *(uint16_t *)0x4d0cf8;
  return *(void **)0x4d0cf0;
}

/* rasterizer_transparent_geometry_next_group (0x1843b0) — XBE naked draft (batch 91). */
#if defined(__clang__)
static void (*const b1843b0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1843b0_exitfn)(int) = system_exit;

__attribute__((naked, noinline))
void * rasterizer_transparent_geometry_next_group(void *group __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "je .Lrasterizer_transparent_geometry_next_group_5\n\t"
      "movw 0x90(%%eax), %%si\n\t"
      "movl 0x90(%%eax), %%eax\n\t"
      "incw %%si\n\t"
      "testl %%eax, %%eax\n\t"
      "jl .Lrasterizer_transparent_geometry_next_group_1\n\t"
      "cmpl 0x4d0cf4, %%eax\n\t"
      "jl .Lrasterizer_transparent_geometry_next_group_2\n\t"
      ".Lrasterizer_transparent_geometry_next_group_1:\n\t"
      "pushl $1\n\t"
      "pushl $0x89\n\t"
      "pushl $0x2b0ca8\n\t"
      "pushl $0x2b0d00\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrasterizer_transparent_geometry_next_group_2:\n\t"
      "movl 0x4d0cf4, %%eax\n\t"
      "movswl %%si, %%edi\n\t"
      "cmpl %%eax, %%edi\n\t"
      "jge .Lrasterizer_transparent_geometry_next_group_4\n\t"
      "testw %%si, %%si\n\t"
      "jge .Lrasterizer_transparent_geometry_next_group_3\n\t"
      "pushl $1\n\t"
      "pushl $0x8d\n\t"
      "pushl $0x2b0ca8\n\t"
      "pushl $0x2b0ce4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrasterizer_transparent_geometry_next_group_3:\n\t"
      "movl 0x4d0cfc, %%eax\n\t"
      "movswl (%%eax,%%edi,2), %%eax\n\t"
      "movl 0x4d0cec, %%ecx\n\t"
      "leal (%%eax,%%eax,4), %%eax\n\t"
      "shll $5, %%eax\n\t"
      "popl %%edi\n\t"
      "addl %%ecx, %%eax\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lrasterizer_transparent_geometry_next_group_4:\n\t"
      "xorl %%eax, %%eax\n\t"
      ".Lrasterizer_transparent_geometry_next_group_5:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b1843b0_assert), [exitfn] "m"(b1843b0_exitfn)
      : "memory");
}
#else
#error "rasterizer_transparent_geometry_next_group: clang naked draft required"
#endif


/* rasterizer_transparent_geometry_group_get (0x184460) — readable C lift from XBE leaf. */
void *rasterizer_transparent_geometry_group_get(short group_presorted_index)
{
  extern char DAT_002b0d50[];
  extern char DAT_002b0ca8[];

  if (group_presorted_index < 0 ||
      (int)group_presorted_index >= *(int *)0x4d0cf4) {
    display_assert(DAT_002b0d50, DAT_002b0ca8, 0xbc, true);
    system_exit(-1);
  }
  return (void *)(*(int *)0x4d0cec + (int)group_presorted_index * 0xa0);
}




/* rasterizer_transparent_geometry_group_to_presorted_index (0x1844b0) — XBE naked draft (batch 89). */
#if defined(__clang__)
static void (*const b1844b0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1844b0_exitfn)(int) = system_exit;

__attribute__((naked, noinline))
short rasterizer_transparent_geometry_group_to_presorted_index(unsigned int group __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ebx\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x4d0cec, %%edi\n\t"
      "orl $0xffffffff, %%eax\n\t"
      "cmpl %%edi, %%ebx\n\t"
      "jb .Lrasterizer_transparent_geometry_group_to_presorted_index_4\n\t"
      "movl 0x4d0cf4, %%ecx\n\t"
      "leal (%%ecx,%%ecx,4), %%ecx\n\t"
      "shll $5, %%ecx\n\t"
      "addl %%edi, %%ecx\n\t"
      "cmpl %%ecx, %%ebx\n\t"
      "jae .Lrasterizer_transparent_geometry_group_to_presorted_index_4\n\t"
      "movl %%ebx, %%ecx\n\t"
      "subl %%edi, %%ecx\n\t"
      "movl $0x66666667, %%eax\n\t"
      "imull %%ecx\n\t"
      "sarl $6, %%edx\n\t"
      "movl %%edx, %%eax\n\t"
      "shrl $0x1f, %%eax\n\t"
      "addl %%eax, %%edx\n\t"
      "movl %%edx, %%esi\n\t"
      "testw %%si, %%si\n\t"
      "jl .Lrasterizer_transparent_geometry_group_to_presorted_index_1\n\t"
      "movl 0x4d0cf4, %%eax\n\t"
      "movswl %%si, %%ecx\n\t"
      "cmpl %%eax, %%ecx\n\t"
      "jl .Lrasterizer_transparent_geometry_group_to_presorted_index_2\n\t"
      ".Lrasterizer_transparent_geometry_group_to_presorted_index_1:\n\t"
      "pushl $1\n\t"
      "pushl $0xcb\n\t"
      "pushl $0x2b0ca8\n\t"
      "pushl $0x2b0d50\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "movl 0x4d0cec, %%edi\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrasterizer_transparent_geometry_group_to_presorted_index_2:\n\t"
      "movl %%ebx, %%eax\n\t"
      "subl %%edi, %%eax\n\t"
      "xorl %%edx, %%edx\n\t"
      "movl $0xa0, %%ecx\n\t"
      "divl %%ecx\n\t"
      "testl %%edx, %%edx\n\t"
      "je .Lrasterizer_transparent_geometry_group_to_presorted_index_3\n\t"
      "pushl $1\n\t"
      "pushl $0xcc\n\t"
      "pushl $0x2b0ca8\n\t"
      "pushl $0x2b0da8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrasterizer_transparent_geometry_group_to_presorted_index_3:\n\t"
      "movw %%si, %%ax\n\t"
      ".Lrasterizer_transparent_geometry_group_to_presorted_index_4:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b1844b0_assert), [exitfn] "m"(b1844b0_exitfn)
      : "memory");
}
#else
#error "rasterizer_transparent_geometry_group_to_presorted_index: clang naked draft required"
#endif

/* --- rasterizer_text.obj batch drafts (2026-07-26) --- */

/* FUN_00180770 (0x180770) — XBE naked draft (batch 374). */
#if defined(__clang__)
static void (*const b180770_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b180770_exitfn)(int) = system_exit;

__attribute__((naked, noinline))
unsigned char FUN_00180770(float alpha __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "flds 0x8(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_00180770_1\n\t"
      "flds 0x8(%%ebp)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jnp .LFUN_00180770_2\n\t"
      ".LFUN_00180770_1:\n\t"
      "pushl $1\n\t"
      "pushl $0x2a\n\t"
      "pushl $0x2afe38\n\t"
      "pushl $0x2b00a0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00180770_2:\n\t"
      "flds 0x8(%%ebp)\n\t"
      "fmuls 0x2602c8\n\t"
      "fstps 0x8(%%ebp)\n\t"
      "flds 0x8(%%ebp)\n\t"
      "fistps -0x4(%%ebp)\n\t"
      "movb -0x4(%%ebp), %%al\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b180770_assert), [exitfn] "m"(b180770_exitfn)
      : "memory");
}
#else
#error "FUN_00180770: clang naked draft required"
#endif


/* compress_real_to_int16 (0x180820) — XBE naked draft (batch 368). */
#if defined(__clang__)
static void (*const b180820_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b180820_exitfn)(int) = system_exit;
static double (*const b180820_c1d9c2b)(double x) = (void *)floor;

__attribute__((naked, noinline))
void compress_real_to_int16(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "flds 0x8(%%ebp)\n\t"
      "fcomps 0x255e94\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .Lcompress_real_to_int16_1\n\t"
      "flds 0x8(%%ebp)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jnp .Lcompress_real_to_int16_2\n\t"
      ".Lcompress_real_to_int16_1:\n\t"
      "pushl $1\n\t"
      "pushl $0x37\n\t"
      "pushl $0x2afe38\n\t"
      "pushl $0x2b00b8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lcompress_real_to_int16_2:\n\t"
      "flds 0x8(%%ebp)\n\t"
      "subl $8, %%esp\n\t"
      "fmuls 0x2b00b4\n\t"
      "fstpl (%%esp)\n\t"
      "call *%[c1d9c2b]\n\t"
      "fstps 0x8(%%ebp)\n\t"
      "addl $8, %%esp\n\t"
      "flds 0x8(%%ebp)\n\t"
      "fistps -0x4(%%ebp)\n\t"
      "movw -0x4(%%ebp), %%ax\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b180820_assert), [exitfn] "m"(b180820_exitfn), [c1d9c2b] "m"(b180820_c1d9c2b)
      : "memory");
}
#else
#error "compress_real_to_int16: clang naked draft required"
#endif


/* FUN_00180890 (0x180890) — XBE naked draft (batch 365). */
#if defined(__clang__)
static double (*const b180890_c1d9c2b)(double x) = (void *)floor;

__attribute__((naked, noinline))
short FUN_00180890(float f __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "flds 0x8(%%ebp)\n\t"
      "fcomps 0x255e94\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00180890_1\n\t"
      "flds 0x255e94\n\t"
      "jmp .LFUN_00180890_3\n\t"
      ".LFUN_00180890_1:\n\t"
      "flds 0x8(%%ebp)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00180890_2\n\t"
      "flds 0x2533c8\n\t"
      "jmp .LFUN_00180890_3\n\t"
      ".LFUN_00180890_2:\n\t"
      "flds 0x8(%%ebp)\n\t"
      ".LFUN_00180890_3:\n\t"
      "fmuls 0x2b00b4\n\t"
      "subl $8, %%esp\n\t"
      "fstpl (%%esp)\n\t"
      "call *%[c1d9c2b]\n\t"
      "fstps 0x8(%%ebp)\n\t"
      "addl $8, %%esp\n\t"
      "flds 0x8(%%ebp)\n\t"
      "fistps -0x4(%%ebp)\n\t"
      "movw -0x4(%%ebp), %%ax\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c1d9c2b] "m"(b180890_c1d9c2b)
      : "memory");
}
#else
#error "FUN_00180890: clang naked draft required"
#endif


/* 0x181060 */
unsigned char *FUN_00181060(void *lens_flare_params)
{
  int esi = 0;
  int edi = 0;

  /* test edi, edi -> jne 0x181084 */
  display_assert((char *)0x002b02d4, (char *)0x002b01b4, 76, 0);
  system_exit(0);
  /* cmp esi, 4 -> jl 0x1810cf */
  display_assert((char *)0x002a1d18, (char *)0x002b01b4, 87, 0);
  system_exit(0);
  /* test edi, edi -> jl 0x1810db */
  /* cmp edi, 0x10008 -> jl 0x1810f8 */
  display_assert((char *)0x002b0250, (char *)0x002b01b4, 88, 0);
  system_exit(0);
  /* test (int16_t)eax, (int16_t)eax -> jl 0x18110d */
  /* cmp (int16_t)eax, 0x380 -> jl 0x18112a */
  display_assert((char *)0x002b01e8, (char *)0x002b01b4, 94, 0);
  system_exit(0);
  return NULL;

  (void)esi;
  (void)edi;
}

/* FUN_00181180 (0x181180) — XBE naked draft (batch 333). */
#if defined(__clang__)
static void (*const b181180_c16f910)(int16_t profile) = FUN_0016f910;
static void (*const b181180_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b181180_exitfn)(int) = system_exit;
static unsigned char * (*const b181180_c181060)(void *lens_flare_params) = FUN_00181060;
static void (*const b181180_c17d040)(void) = FUN_0017d040;
static void (*const b181180_c16fa40)(int16_t profile) = FUN_0016fa40;

__attribute__((naked, noinline))
void FUN_00181180(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x18\n\t"
      "call *%[c16f910]\n\t"
      "movb 0x3256d7, %%al\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00181180_12\n\t"
      "movw 0x46e008, %%ax\n\t"
      "cmpw $1, %%ax\n\t"
      "jg .LFUN_00181180_12\n\t"
      "jne .LFUN_00181180_1\n\t"
      "cmpw $1, 0x31fa98\n\t"
      "jg .LFUN_00181180_12\n\t"
      ".LFUN_00181180_1:\n\t"
      "movl 0x4d0480, %%eax\n\t"
      "pushl %%esi\n\t"
      "xorl %%esi, %%esi\n\t"
      "cmpl %%esi, %%eax\n\t"
      "movl %%esi, -0x4(%%ebp)\n\t"
      "jle .LFUN_00181180_11\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      ".LFUN_00181180_2:\n\t"
      "cmpw $0, -0x4(%%ebp)\n\t"
      "jl .LFUN_00181180_3\n\t"
      "cmpl %%eax, %%esi\n\t"
      "jl .LFUN_00181180_4\n\t"
      ".LFUN_00181180_3:\n\t"
      "pushl $1\n\t"
      "pushl $0x43\n\t"
      "pushl $0x2b01b4\n\t"
      "pushl $0x2b0174\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00181180_4:\n\t"
      "leal (%%esi,%%esi,4), %%edi\n\t"
      "leal 0x4c6480(,%%edi,8), %%edi\n\t"
      "movl %%edi, %%eax\n\t"
      "call *%[c181060]\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl 0x24(%%edi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jle .LFUN_00181180_5\n\t"
      "pushl %%esi\n\t"
      "call *%[c17d040]\n\t"
      "imull $0xff, %%eax, %%eax\n\t"
      "movl 0x24(%%edi), %%ecx\n\t"
      "movl %%ecx, %%edx\n\t"
      "sarl $1, %%edx\n\t"
      "addl %%edx, %%eax\n\t"
      "cdq\n\t"
      "idivl %%ecx\n\t"
      "addl $4, %%esp\n\t"
      "cmpl $0xff, %%eax\n\t"
      "jge .LFUN_00181180_6\n\t"
      "movb %%al, %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "jne .LFUN_00181180_7\n\t"
      ".LFUN_00181180_5:\n\t"
      "movb $0, (%%ebx)\n\t"
      "jmp .LFUN_00181180_10\n\t"
      ".LFUN_00181180_6:\n\t"
      "orb $0xff, %%cl\n\t"
      ".LFUN_00181180_7:\n\t"
      "movb (%%ebx), %%al\n\t"
      "cmpb %%al, %%cl\n\t"
      "jbe .LFUN_00181180_8\n\t"
      "movzbl %%al, %%eax\n\t"
      "leal (%%eax,%%eax,2), %%eax\n\t"
      "movzbl %%cl, %%ecx\n\t"
      "addl %%ecx, %%eax\n\t"
      "cdq\n\t"
      "andl $3, %%edx\n\t"
      "addl %%edx, %%eax\n\t"
      "sarl $2, %%eax\n\t"
      "jmp .LFUN_00181180_9\n\t"
      ".LFUN_00181180_8:\n\t"
      "jae .LFUN_00181180_10\n\t"
      "movzbl %%al, %%eax\n\t"
      "movzbl %%cl, %%edx\n\t"
      "addl %%edx, %%eax\n\t"
      "cdq\n\t"
      "subl %%edx, %%eax\n\t"
      "sarl $1, %%eax\n\t"
      ".LFUN_00181180_9:\n\t"
      "movb %%al, (%%ebx)\n\t"
      ".LFUN_00181180_10:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "incl %%eax\n\t"
      "movswl %%ax, %%esi\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "movl 0x4d0480, %%eax\n\t"
      "cmpl %%eax, %%esi\n\t"
      "jl .LFUN_00181180_2\n\t"
      "popl %%edi\n\t"
      "popl %%ebx\n\t"
      ".LFUN_00181180_11:\n\t"
      "movl $0, 0x4d0480\n\t"
      "popl %%esi\n\t"
      ".LFUN_00181180_12:\n\t"
      "pushl $0x18\n\t"
      "call *%[c16fa40]\n\t"
      "addl $4, %%esp\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c16f910] "m"(b181180_c16f910), [assert] "m"(b181180_assert), [exitfn] "m"(b181180_exitfn), [c181060] "m"(b181180_c181060), [c17d040] "m"(b181180_c17d040), [c16fa40] "m"(b181180_c16fa40)
      : "memory");
}
#else
#error "FUN_00181180: clang naked draft required"
#endif


/* FUN_001812c0 (0x1812c0) — XBE naked draft (batch 323). */
#if defined(__clang__)
static void (*const b1812c0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1812c0_exitfn)(int) = system_exit;
static void (*const b1812c0_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;

__attribute__((naked, noinline))
void FUN_001812c0(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "pushl %%edi\n\t"
      "orl $0xffffffff, %%edi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LFUN_001812c0_1\n\t"
      "pushl $1\n\t"
      "pushl $0xf0\n\t"
      "pushl $0x2b01b4\n\t"
      "pushl $0x29f510\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001812c0_1:\n\t"
      "flds 0x28(%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_001812c0_2\n\t"
      "flds 0x28(%%esi)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jnp .LFUN_001812c0_3\n\t"
      ".LFUN_001812c0_2:\n\t"
      "pushl $1\n\t"
      "pushl $0xf1\n\t"
      "pushl $0x2b01b4\n\t"
      "pushl $0x2b039c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001812c0_3:\n\t"
      "flds 0x2c(%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_001812c0_4\n\t"
      "flds 0x2c(%%esi)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jnp .LFUN_001812c0_5\n\t"
      ".LFUN_001812c0_4:\n\t"
      "pushl $1\n\t"
      "pushl $0xf2\n\t"
      "pushl $0x2b01b4\n\t"
      "pushl $0x2b035c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001812c0_5:\n\t"
      "flds 0x30(%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_001812c0_6\n\t"
      "flds 0x30(%%esi)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jnp .LFUN_001812c0_7\n\t"
      ".LFUN_001812c0_6:\n\t"
      "pushl $1\n\t"
      "pushl $0xf3\n\t"
      "pushl $0x2b01b4\n\t"
      "pushl $0x2b031c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001812c0_7:\n\t"
      "movl 0x5a37e0, %%ecx\n\t"
      "cmpl $0x80, %%ecx\n\t"
      "jge .LFUN_001812c0_8\n\t"
      "movl %%ecx, %%eax\n\t"
      "movl %%eax, %%edi\n\t"
      "imull $0x38, %%edi, %%edi\n\t"
      "incl %%ecx\n\t"
      "movl %%ecx, 0x5a37e0\n\t"
      "addl $0x5a37e4, %%edi\n\t"
      "cmpw $2, 0x3256ba\n\t"
      "movl $0xe, %%ecx\n\t"
      "rep movsl\n\t"
      "jne .LFUN_001812c0_9\n\t"
      "movl 0x5a5548, %%ecx\n\t"
      "incl %%ecx\n\t"
      "popl %%edi\n\t"
      "movl %%ecx, 0x5a5548\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001812c0_8:\n\t"
      "pushl $0x2b02ec\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "movl %%edi, %%eax\n\t"
      ".LFUN_001812c0_9:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b1812c0_assert), [exitfn] "m"(b1812c0_exitfn), [c8f390] "m"(b1812c0_c8f390)
      : "memory");
}
#else
#error "FUN_001812c0: clang naked draft required"
#endif


/* FUN_00181420 (0x181420) — XBE naked draft (batch 309). */
#if defined(__clang__)
static void (*const b181420_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b181420_exitfn)(int) = system_exit;
static float * (*const b181420_c17ffc0)(float *param_1, unsigned int param_2) = FUN_0017ffc0;
static void (*const b181420_cross)(float *, float *, float *) = cross_product3d;

__attribute__((naked, noinline))
float FUN_00181420(void *lens_flare_params __attribute__((unused)), short rotation_fn __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x30, %%esp\n\t"
      "testl %%esi, %%esi\n\t"
      "movl $0x3f800000, -0x8(%%ebp)\n\t"
      "movl $0, -0x4(%%ebp)\n\t"
      "movl $0, -0xc(%%ebp)\n\t"
      "jne .LFUN_00181420_1\n\t"
      "pushl $1\n\t"
      "pushl $0x76\n\t"
      "pushl $0x2b01b4\n\t"
      "pushl $0x2b02d4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00181420_1:\n\t"
      "movl 0x10(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x30(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c17ffc0]\n\t"
      "movl (%%eax), %%edx\n\t"
      "movl 0x4(%%eax), %%ecx\n\t"
      "movl %%edx, -0x24(%%ebp)\n\t"
      "movl 0x8(%%eax), %%edx\n\t"
      "movswl %%di, %%eax\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $4, %%eax\n\t"
      "movl %%ecx, -0x20(%%ebp)\n\t"
      "movl %%edx, -0x1c(%%ebp)\n\t"
      "ja .LFUN_00181420_7\n\t"
      "jmp *.LFUN_00181420_jt(,%%eax,4)\n\t"
      ".LFUN_00181420_2:\n\t"
      "leal -0x30(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x24(%%ebp), %%ecx\n\t"
      "pushl $0x5a5c64\n\t"
      "pushl %%ecx\n\t"
      "call *%[cross]\n\t"
      "leal -0x30(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x24(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x30(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[cross]\n\t"
      "flds -0x28(%%ebp)\n\t"
      "movl 0x5a5bdc, %%ecx\n\t"
      "movl 0x5a5bd8, %%eax\n\t"
      "movl 0x5a5bd4, %%edx\n\t"
      "movl %%ecx, -0x10(%%ebp)\n\t"
      "fmuls -0x10(%%ebp)\n\t"
      "flds -0x2c(%%ebp)\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "fmuls -0x14(%%ebp)\n\t"
      "movl %%edx, -0x18(%%ebp)\n\t"
      "addl $0x18, %%esp\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds -0x30(%%ebp)\n\t"
      "fmuls -0x18(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fmuls -0x10(%%ebp)\n\t"
      "flds -0x20(%%ebp)\n\t"
      "fmuls -0x14(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds -0x24(%%ebp)\n\t"
      "fmuls -0x18(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fchs\n\t"
      "jmp .LFUN_00181420_9\n\t"
      ".LFUN_00181420_3:\n\t"
      "flds -0x24(%%ebp)\n\t"
      "fchs\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "flds -0x20(%%ebp)\n\t"
      "fchs\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fchs\n\t"
      "jmp .LFUN_00181420_6\n\t"
      ".LFUN_00181420_4:\n\t"
      "leal -0x30(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x24(%%ebp), %%eax\n\t"
      "pushl $0x5a5c64\n\t"
      "pushl %%eax\n\t"
      "call *%[cross]\n\t"
      "leal -0x30(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x24(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x30(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[cross]\n\t"
      "flds 0x4(%%esi)\n\t"
      "fsubs 0x5a5bc8\n\t"
      "addl $0x18, %%esp\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "flds 0x8(%%esi)\n\t"
      "fsubs 0x5a5bcc\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "flds 0xc(%%esi)\n\t"
      "fsubs 0x5a5bd0\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "flds -0x28(%%ebp)\n\t"
      "fmuls -0x10(%%ebp)\n\t"
      "flds -0x2c(%%ebp)\n\t"
      "fmuls -0x14(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds -0x30(%%ebp)\n\t"
      "fmuls -0x18(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fmuls -0x10(%%ebp)\n\t"
      "flds -0x20(%%ebp)\n\t"
      "fmuls -0x14(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds -0x24(%%ebp)\n\t"
      "fmuls -0x18(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fchs\n\t"
      "jmp .LFUN_00181420_9\n\t"
      ".LFUN_00181420_5:\n\t"
      "flds 0x4(%%esi)\n\t"
      "fsubs 0x5a5bc8\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "flds 0x8(%%esi)\n\t"
      "fsubs 0x5a5bcc\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "flds 0xc(%%esi)\n\t"
      "fsubs 0x5a5bd0\n\t"
      ".LFUN_00181420_6:\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "flds 0x5a5c6c\n\t"
      "fmuls -0x10(%%ebp)\n\t"
      "flds 0x5a5c68\n\t"
      "fmuls -0x14(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds 0x5a5c64\n\t"
      "fmuls -0x18(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds 0x5a5c84\n\t"
      "fmuls -0x10(%%ebp)\n\t"
      "flds 0x5a5c80\n\t"
      "fmuls -0x14(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds 0x5a5c7c\n\t"
      "fmuls -0x18(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fchs\n\t"
      "jmp .LFUN_00181420_9\n\t"
      ".LFUN_00181420_7:\n\t"
      "pushl $1\n\t"
      "pushl $0x97\n\t"
      "pushl $0x2b01b4\n\t"
      "pushl $0x2b03dc\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00181420_8:\n\t"
      "flds -0x4(%%ebp)\n\t"
      "flds -0x8(%%ebp)\n\t"
      ".LFUN_00181420_9:\n\t"
      "testw %%di, %%di\n\t"
      "je .LFUN_00181420_10\n\t"
      "fld %%st(1)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .LFUN_00181420_10\n\t"
      "fpatan\n\t"
      "fmuls 0x29c120\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00181420_10:\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "flds -0xc(%%ebp)\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_00181420_jt:\n\t"
      ".long .LFUN_00181420_8\n\t"
      ".long .LFUN_00181420_2\n\t"
      ".long .LFUN_00181420_3\n\t"
      ".long .LFUN_00181420_4\n\t"
      ".long .LFUN_00181420_5\n\t"
      ".text\n\t"
      :
      : [assert] "m"(b181420_assert), [exitfn] "m"(b181420_exitfn), [c17ffc0] "m"(b181420_c17ffc0), [cross] "m"(b181420_cross)
      : "memory");
}
#else
#error "FUN_00181420: clang naked draft required"
#endif


/* FUN_00182610 (0x182610) — XBE naked draft (batch 326). */
#if defined(__clang__)


__attribute__((naked, noinline))
void FUN_00182610(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "xorl %%edi, %%edi\n\t"
      "movl $1, %%edx\n\t"
      "movl %%edx, %%eax\n\t"
      "movl %%edi, 0x4d0490\n\t"
      "movl %%edi, 0x4d0494\n\t"
      "movl %%edi, 0x4d0498\n\t"
      "movswl %%si, %%esi\n\t"
      ".LFUN_00182610_1:\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "cmpl %%esi, %%edx\n\t"
      "jae .LFUN_00182610_2\n\t"
      "movl 0x4d0498, %%ebx\n\t"
      "orl %%eax, %%ebx\n\t"
      "shll $1, %%eax\n\t"
      "movl %%ebx, 0x4d0498\n\t"
      "movl %%eax, %%ecx\n\t"
      ".LFUN_00182610_2:\n\t"
      "movswl 0x8(%%ebp), %%ebx\n\t"
      "cmpl %%ebx, %%edx\n\t"
      "jae .LFUN_00182610_3\n\t"
      "movl 0x4d0494, %%ebx\n\t"
      "orl %%eax, %%ebx\n\t"
      "shll $1, %%eax\n\t"
      "movl %%ebx, 0x4d0494\n\t"
      "movl %%eax, %%ecx\n\t"
      ".LFUN_00182610_3:\n\t"
      "movswl 0xc(%%ebp), %%ebx\n\t"
      "cmpl %%ebx, %%edx\n\t"
      "jae .LFUN_00182610_4\n\t"
      "orl %%eax, %%edi\n\t"
      "shll $1, %%eax\n\t"
      "movl %%eax, %%ecx\n\t"
      ".LFUN_00182610_4:\n\t"
      "shll $1, %%edx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "jne .LFUN_00182610_1\n\t"
      "movl %%edi, 0x4d0490\n\t"
      "popl %%edi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "FUN_00182610: clang naked draft required"
#endif


/* rasterizer_xbox_bitmap_swizzle2d_byte (0x182840) — XBE naked draft (batch 332). */
#if defined(__clang__)
static void (*const b182840_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b182840_exitfn)(int) = system_exit;
static void (*const b182840_c182610)(void) = FUN_00182610;

__attribute__((naked, noinline))
void rasterizer_xbox_bitmap_swizzle2d_byte(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $8, %%esp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "xorl %%edi, %%edi\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "cmpl %%edi, %%eax\n\t"
      "movl %%edi, -0x4(%%ebp)\n\t"
      "jne .Lrasterizer_xbox_bitmap_swizzle2d_byte_1\n\t"
      "pushl $1\n\t"
      "pushl $0x93\n\t"
      "pushl $0x2b087c\n\t"
      "pushl $0x2b08ac\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrasterizer_xbox_bitmap_swizzle2d_byte_1:\n\t"
      "cmpl %%edi, 0xc(%%ebp)\n\t"
      "jne .Lrasterizer_xbox_bitmap_swizzle2d_byte_2\n\t"
      "pushl $1\n\t"
      "pushl $0x94\n\t"
      "pushl $0x2b087c\n\t"
      "pushl $0x2b07dc\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrasterizer_xbox_bitmap_swizzle2d_byte_2:\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "movl 0x10(%%ebp), %%esi\n\t"
      "pushl $1\n\t"
      "pushl %%eax\n\t"
      "call *%[c182610]\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "testw %%ax, %%ax\n\t"
      "jle .Lrasterizer_xbox_bitmap_swizzle2d_byte_6\n\t"
      "movzwl %%ax, %%ecx\n\t"
      "movl 0x4d0498, %%eax\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "movl 0x4d0494, %%ecx\n\t"
      ".Lrasterizer_xbox_bitmap_swizzle2d_byte_3:\n\t"
      "testw %%si, %%si\n\t"
      "jle .Lrasterizer_xbox_bitmap_swizzle2d_byte_5\n\t"
      "movzwl %%si, %%edx\n\t"
      "movl %%edx, 0x14(%%ebp)\n\t"
      ".Lrasterizer_xbox_bitmap_swizzle2d_byte_4:\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "movb (%%ebx,%%edx,1), %%dl\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "orl %%edi, %%ecx\n\t"
      "movb %%dl, (%%ecx,%%esi,1)\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      "subl %%eax, %%edi\n\t"
      "incl %%ebx\n\t"
      "andl %%eax, %%edi\n\t"
      "decl %%ecx\n\t"
      "movl %%ecx, 0x14(%%ebp)\n\t"
      "jne .Lrasterizer_xbox_bitmap_swizzle2d_byte_4\n\t"
      "movl 0x4d0494, %%ecx\n\t"
      "movl 0x10(%%ebp), %%esi\n\t"
      ".Lrasterizer_xbox_bitmap_swizzle2d_byte_5:\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "subl %%ecx, %%edx\n\t"
      "andl %%ecx, %%edx\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      "decl -0x8(%%ebp)\n\t"
      "jne .Lrasterizer_xbox_bitmap_swizzle2d_byte_3\n\t"
      ".Lrasterizer_xbox_bitmap_swizzle2d_byte_6:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b182840_assert), [exitfn] "m"(b182840_exitfn), [c182610] "m"(b182840_c182610)
      : "memory");
}
#else
#error "rasterizer_xbox_bitmap_swizzle2d_byte: clang naked draft required"
#endif


/* rasterizer_xbox_bitmap_swizzle2d_word (0x182910) — XBE naked draft (batch 332). */
#if defined(__clang__)
static void (*const b182910_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b182910_exitfn)(int) = system_exit;
static void (*const b182910_c182610)(void) = FUN_00182610;

__attribute__((naked, noinline))
void rasterizer_xbox_bitmap_swizzle2d_word(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $8, %%esp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "xorl %%edi, %%edi\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "cmpl %%edi, %%eax\n\t"
      "movl %%edi, -0x4(%%ebp)\n\t"
      "jne .Lrasterizer_xbox_bitmap_swizzle2d_word_1\n\t"
      "pushl $1\n\t"
      "pushl $0xb0\n\t"
      "pushl $0x2b087c\n\t"
      "pushl $0x2b08ac\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrasterizer_xbox_bitmap_swizzle2d_word_1:\n\t"
      "cmpl %%edi, 0xc(%%ebp)\n\t"
      "jne .Lrasterizer_xbox_bitmap_swizzle2d_word_2\n\t"
      "pushl $1\n\t"
      "pushl $0xb1\n\t"
      "pushl $0x2b087c\n\t"
      "pushl $0x2b07dc\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrasterizer_xbox_bitmap_swizzle2d_word_2:\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "movl 0x10(%%ebp), %%esi\n\t"
      "pushl $1\n\t"
      "pushl %%eax\n\t"
      "call *%[c182610]\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "testw %%ax, %%ax\n\t"
      "jle .Lrasterizer_xbox_bitmap_swizzle2d_word_6\n\t"
      "movzwl %%ax, %%ecx\n\t"
      "movl 0x4d0498, %%eax\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "movl 0x4d0494, %%ecx\n\t"
      ".Lrasterizer_xbox_bitmap_swizzle2d_word_3:\n\t"
      "testw %%si, %%si\n\t"
      "jle .Lrasterizer_xbox_bitmap_swizzle2d_word_5\n\t"
      "movzwl %%si, %%edx\n\t"
      "movl %%edx, 0x14(%%ebp)\n\t"
      ".Lrasterizer_xbox_bitmap_swizzle2d_word_4:\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "movw (%%edx,%%ebx,2), %%dx\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "orl %%edi, %%ecx\n\t"
      "movw %%dx, (%%esi,%%ecx,2)\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      "subl %%eax, %%edi\n\t"
      "incl %%ebx\n\t"
      "andl %%eax, %%edi\n\t"
      "decl %%ecx\n\t"
      "movl %%ecx, 0x14(%%ebp)\n\t"
      "jne .Lrasterizer_xbox_bitmap_swizzle2d_word_4\n\t"
      "movl 0x4d0494, %%ecx\n\t"
      "movl 0x10(%%ebp), %%esi\n\t"
      ".Lrasterizer_xbox_bitmap_swizzle2d_word_5:\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "subl %%ecx, %%edx\n\t"
      "andl %%ecx, %%edx\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      "decl -0x8(%%ebp)\n\t"
      "jne .Lrasterizer_xbox_bitmap_swizzle2d_word_3\n\t"
      ".Lrasterizer_xbox_bitmap_swizzle2d_word_6:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b182910_assert), [exitfn] "m"(b182910_exitfn), [c182610] "m"(b182910_c182610)
      : "memory");
}
#else
#error "rasterizer_xbox_bitmap_swizzle2d_word: clang naked draft required"
#endif


/* rasterizer_xbox_bitmap_swizzle2d_long (0x1829f0) — XBE naked draft (batch 332). */
#if defined(__clang__)
static void (*const b1829f0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1829f0_exitfn)(int) = system_exit;
static void (*const b1829f0_c182610)(void) = FUN_00182610;

__attribute__((naked, noinline))
void rasterizer_xbox_bitmap_swizzle2d_long(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $8, %%esp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "xorl %%edi, %%edi\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "cmpl %%edi, %%eax\n\t"
      "movl %%edi, -0x4(%%ebp)\n\t"
      "jne .Lrasterizer_xbox_bitmap_swizzle2d_long_1\n\t"
      "pushl $1\n\t"
      "pushl $0xcd\n\t"
      "pushl $0x2b087c\n\t"
      "pushl $0x2b08ac\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrasterizer_xbox_bitmap_swizzle2d_long_1:\n\t"
      "cmpl %%edi, 0xc(%%ebp)\n\t"
      "jne .Lrasterizer_xbox_bitmap_swizzle2d_long_2\n\t"
      "pushl $1\n\t"
      "pushl $0xce\n\t"
      "pushl $0x2b087c\n\t"
      "pushl $0x2b07dc\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrasterizer_xbox_bitmap_swizzle2d_long_2:\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "movl 0x10(%%ebp), %%esi\n\t"
      "pushl $1\n\t"
      "pushl %%eax\n\t"
      "call *%[c182610]\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "testw %%ax, %%ax\n\t"
      "jle .Lrasterizer_xbox_bitmap_swizzle2d_long_6\n\t"
      "movzwl %%ax, %%ecx\n\t"
      "movl 0x4d0498, %%eax\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "movl 0x4d0494, %%ecx\n\t"
      ".Lrasterizer_xbox_bitmap_swizzle2d_long_3:\n\t"
      "testw %%si, %%si\n\t"
      "jle .Lrasterizer_xbox_bitmap_swizzle2d_long_5\n\t"
      "movzwl %%si, %%edx\n\t"
      "movl %%edx, 0x14(%%ebp)\n\t"
      ".Lrasterizer_xbox_bitmap_swizzle2d_long_4:\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "movl (%%edx,%%ebx,4), %%edx\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "orl %%edi, %%ecx\n\t"
      "movl %%edx, (%%esi,%%ecx,4)\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      "subl %%eax, %%edi\n\t"
      "incl %%ebx\n\t"
      "andl %%eax, %%edi\n\t"
      "decl %%ecx\n\t"
      "movl %%ecx, 0x14(%%ebp)\n\t"
      "jne .Lrasterizer_xbox_bitmap_swizzle2d_long_4\n\t"
      "movl 0x4d0494, %%ecx\n\t"
      "movl 0x10(%%ebp), %%esi\n\t"
      ".Lrasterizer_xbox_bitmap_swizzle2d_long_5:\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "subl %%ecx, %%edx\n\t"
      "andl %%ecx, %%edx\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      "decl -0x8(%%ebp)\n\t"
      "jne .Lrasterizer_xbox_bitmap_swizzle2d_long_3\n\t"
      ".Lrasterizer_xbox_bitmap_swizzle2d_long_6:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b1829f0_assert), [exitfn] "m"(b1829f0_exitfn), [c182610] "m"(b1829f0_c182610)
      : "memory");
}
#else
#error "rasterizer_xbox_bitmap_swizzle2d_long: clang naked draft required"
#endif


/* rasterizer_xbox_bitmap_swizzle3d_byte (0x182ac0) — XBE naked draft (batch 324). */
#if defined(__clang__)
static void (*const b182ac0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b182ac0_exitfn)(int) = system_exit;
static void (*const b182ac0_c182610)(void) = FUN_00182610;

__attribute__((naked, noinline))
void rasterizer_xbox_bitmap_swizzle3d_byte(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x10, %%esp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "xorl %%edi, %%edi\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "cmpl %%edi, %%eax\n\t"
      "movl %%edi, -0x4(%%ebp)\n\t"
      "movl %%edi, -0x8(%%ebp)\n\t"
      "jne .Lrasterizer_xbox_bitmap_swizzle3d_byte_1\n\t"
      "pushl $1\n\t"
      "pushl $0xeb\n\t"
      "pushl $0x2b087c\n\t"
      "pushl $0x2b08ac\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrasterizer_xbox_bitmap_swizzle3d_byte_1:\n\t"
      "cmpl %%edi, 0xc(%%ebp)\n\t"
      "jne .Lrasterizer_xbox_bitmap_swizzle3d_byte_2\n\t"
      "pushl $1\n\t"
      "pushl $0xec\n\t"
      "pushl $0x2b087c\n\t"
      "pushl $0x2b07dc\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrasterizer_xbox_bitmap_swizzle3d_byte_2:\n\t"
      "movl 0x18(%%ebp), %%eax\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      "movl 0x10(%%ebp), %%esi\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c182610]\n\t"
      "movl 0x18(%%ebp), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "testw %%ax, %%ax\n\t"
      "jle .Lrasterizer_xbox_bitmap_swizzle3d_byte_8\n\t"
      "movl 0x4d0494, %%ecx\n\t"
      "movzwl %%ax, %%edx\n\t"
      "movl %%edx, -0x10(%%ebp)\n\t"
      "movl 0x4d0490, %%edx\n\t"
      ".Lrasterizer_xbox_bitmap_swizzle3d_byte_3:\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "testw %%ax, %%ax\n\t"
      "jle .Lrasterizer_xbox_bitmap_swizzle3d_byte_7\n\t"
      "movzwl %%ax, %%eax\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "movl %%edi, %%edi\n\t"
      ".Lrasterizer_xbox_bitmap_swizzle3d_byte_4:\n\t"
      "testw %%si, %%si\n\t"
      "jle .Lrasterizer_xbox_bitmap_swizzle3d_byte_6\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "orl %%ecx, %%eax\n\t"
      "movzwl %%si, %%ecx\n\t"
      "movl %%ecx, 0x18(%%ebp)\n\t"
      ".Lrasterizer_xbox_bitmap_swizzle3d_byte_5:\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "movb (%%ebx,%%ecx,1), %%cl\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "movl %%eax, %%edx\n\t"
      "orl %%edi, %%edx\n\t"
      "movb %%cl, (%%edx,%%esi,1)\n\t"
      "movl 0x4d0498, %%ecx\n\t"
      "subl %%ecx, %%edi\n\t"
      "andl %%ecx, %%edi\n\t"
      "movl 0x18(%%ebp), %%ecx\n\t"
      "incl %%ebx\n\t"
      "decl %%ecx\n\t"
      "movl %%ecx, 0x18(%%ebp)\n\t"
      "jne .Lrasterizer_xbox_bitmap_swizzle3d_byte_5\n\t"
      "movl 0x10(%%ebp), %%esi\n\t"
      "movl 0x4d0494, %%ecx\n\t"
      ".Lrasterizer_xbox_bitmap_swizzle3d_byte_6:\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "subl %%ecx, %%edx\n\t"
      "andl %%ecx, %%edx\n\t"
      "decl %%eax\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "jne .Lrasterizer_xbox_bitmap_swizzle3d_byte_4\n\t"
      "movl 0x4d0490, %%edx\n\t"
      ".Lrasterizer_xbox_bitmap_swizzle3d_byte_7:\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "subl %%edx, %%eax\n\t"
      "andl %%edx, %%eax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "decl -0x10(%%ebp)\n\t"
      "jne .Lrasterizer_xbox_bitmap_swizzle3d_byte_3\n\t"
      ".Lrasterizer_xbox_bitmap_swizzle3d_byte_8:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b182ac0_assert), [exitfn] "m"(b182ac0_exitfn), [c182610] "m"(b182ac0_c182610)
      : "memory");
}
#else
#error "rasterizer_xbox_bitmap_swizzle3d_byte: clang naked draft required"
#endif


/* rasterizer_xbox_bitmap_swizzle3d_word (0x182bd0) — XBE naked draft (batch 325). */
#if defined(__clang__)
static void (*const b182bd0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b182bd0_exitfn)(int) = system_exit;
static void (*const b182bd0_c182610)(void) = FUN_00182610;

__attribute__((naked, noinline))
void rasterizer_xbox_bitmap_swizzle3d_word(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x10, %%esp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "xorl %%edi, %%edi\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "cmpl %%edi, %%eax\n\t"
      "movl %%edi, -0x4(%%ebp)\n\t"
      "movl %%edi, -0x8(%%ebp)\n\t"
      "jne .Lrasterizer_xbox_bitmap_swizzle3d_word_1\n\t"
      "pushl $1\n\t"
      "pushl $0x10e\n\t"
      "pushl $0x2b087c\n\t"
      "pushl $0x2b08ac\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrasterizer_xbox_bitmap_swizzle3d_word_1:\n\t"
      "cmpl %%edi, 0xc(%%ebp)\n\t"
      "jne .Lrasterizer_xbox_bitmap_swizzle3d_word_2\n\t"
      "pushl $1\n\t"
      "pushl $0x10f\n\t"
      "pushl $0x2b087c\n\t"
      "pushl $0x2b07dc\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrasterizer_xbox_bitmap_swizzle3d_word_2:\n\t"
      "movl 0x18(%%ebp), %%eax\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      "movl 0x10(%%ebp), %%esi\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c182610]\n\t"
      "movl 0x18(%%ebp), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "testw %%ax, %%ax\n\t"
      "jle .Lrasterizer_xbox_bitmap_swizzle3d_word_8\n\t"
      "movl 0x4d0494, %%ecx\n\t"
      "movzwl %%ax, %%edx\n\t"
      "movl %%edx, -0x10(%%ebp)\n\t"
      "movl 0x4d0490, %%edx\n\t"
      ".Lrasterizer_xbox_bitmap_swizzle3d_word_3:\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "testw %%ax, %%ax\n\t"
      "jle .Lrasterizer_xbox_bitmap_swizzle3d_word_7\n\t"
      "movzwl %%ax, %%eax\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "movl %%edi, %%edi\n\t"
      ".Lrasterizer_xbox_bitmap_swizzle3d_word_4:\n\t"
      "testw %%si, %%si\n\t"
      "jle .Lrasterizer_xbox_bitmap_swizzle3d_word_6\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "orl %%ecx, %%eax\n\t"
      "movzwl %%si, %%ecx\n\t"
      "movl %%ecx, 0x18(%%ebp)\n\t"
      ".Lrasterizer_xbox_bitmap_swizzle3d_word_5:\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "movw (%%ecx,%%ebx,2), %%cx\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "movl %%eax, %%edx\n\t"
      "orl %%edi, %%edx\n\t"
      "movw %%cx, (%%esi,%%edx,2)\n\t"
      "movl 0x4d0498, %%ecx\n\t"
      "subl %%ecx, %%edi\n\t"
      "andl %%ecx, %%edi\n\t"
      "movl 0x18(%%ebp), %%ecx\n\t"
      "incl %%ebx\n\t"
      "decl %%ecx\n\t"
      "movl %%ecx, 0x18(%%ebp)\n\t"
      "jne .Lrasterizer_xbox_bitmap_swizzle3d_word_5\n\t"
      "movl 0x10(%%ebp), %%esi\n\t"
      "movl 0x4d0494, %%ecx\n\t"
      ".Lrasterizer_xbox_bitmap_swizzle3d_word_6:\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "subl %%ecx, %%edx\n\t"
      "andl %%ecx, %%edx\n\t"
      "decl %%eax\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "jne .Lrasterizer_xbox_bitmap_swizzle3d_word_4\n\t"
      "movl 0x4d0490, %%edx\n\t"
      ".Lrasterizer_xbox_bitmap_swizzle3d_word_7:\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "subl %%edx, %%eax\n\t"
      "andl %%edx, %%eax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "decl -0x10(%%ebp)\n\t"
      "jne .Lrasterizer_xbox_bitmap_swizzle3d_word_3\n\t"
      ".Lrasterizer_xbox_bitmap_swizzle3d_word_8:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b182bd0_assert), [exitfn] "m"(b182bd0_exitfn), [c182610] "m"(b182bd0_c182610)
      : "memory");
}
#else
#error "rasterizer_xbox_bitmap_swizzle3d_word: clang naked draft required"
#endif


/* rasterizer_xbox_bitmap_swizzle3d_long (0x182cf0) — XBE naked draft (batch 325). */
#if defined(__clang__)
static void (*const b182cf0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b182cf0_exitfn)(int) = system_exit;
static void (*const b182cf0_c182610)(void) = FUN_00182610;

__attribute__((naked, noinline))
void rasterizer_xbox_bitmap_swizzle3d_long(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x10, %%esp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "xorl %%edi, %%edi\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "cmpl %%edi, %%eax\n\t"
      "movl %%edi, -0x4(%%ebp)\n\t"
      "movl %%edi, -0x8(%%ebp)\n\t"
      "jne .Lrasterizer_xbox_bitmap_swizzle3d_long_1\n\t"
      "pushl $1\n\t"
      "pushl $0x131\n\t"
      "pushl $0x2b087c\n\t"
      "pushl $0x2b08ac\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrasterizer_xbox_bitmap_swizzle3d_long_1:\n\t"
      "cmpl %%edi, 0xc(%%ebp)\n\t"
      "jne .Lrasterizer_xbox_bitmap_swizzle3d_long_2\n\t"
      "pushl $1\n\t"
      "pushl $0x132\n\t"
      "pushl $0x2b087c\n\t"
      "pushl $0x2b07dc\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrasterizer_xbox_bitmap_swizzle3d_long_2:\n\t"
      "movl 0x18(%%ebp), %%eax\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      "movl 0x10(%%ebp), %%esi\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c182610]\n\t"
      "movl 0x18(%%ebp), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "testw %%ax, %%ax\n\t"
      "jle .Lrasterizer_xbox_bitmap_swizzle3d_long_8\n\t"
      "movl 0x4d0494, %%ecx\n\t"
      "movzwl %%ax, %%edx\n\t"
      "movl %%edx, -0x10(%%ebp)\n\t"
      "movl 0x4d0490, %%edx\n\t"
      ".Lrasterizer_xbox_bitmap_swizzle3d_long_3:\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "testw %%ax, %%ax\n\t"
      "jle .Lrasterizer_xbox_bitmap_swizzle3d_long_7\n\t"
      "movzwl %%ax, %%eax\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "movl %%edi, %%edi\n\t"
      ".Lrasterizer_xbox_bitmap_swizzle3d_long_4:\n\t"
      "testw %%si, %%si\n\t"
      "jle .Lrasterizer_xbox_bitmap_swizzle3d_long_6\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "orl %%ecx, %%eax\n\t"
      "movzwl %%si, %%ecx\n\t"
      "movl %%ecx, 0x18(%%ebp)\n\t"
      ".Lrasterizer_xbox_bitmap_swizzle3d_long_5:\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "movl (%%ecx,%%ebx,4), %%ecx\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "movl %%eax, %%edx\n\t"
      "orl %%edi, %%edx\n\t"
      "movl %%ecx, (%%esi,%%edx,4)\n\t"
      "movl 0x4d0498, %%ecx\n\t"
      "subl %%ecx, %%edi\n\t"
      "andl %%ecx, %%edi\n\t"
      "movl 0x18(%%ebp), %%ecx\n\t"
      "incl %%ebx\n\t"
      "decl %%ecx\n\t"
      "movl %%ecx, 0x18(%%ebp)\n\t"
      "jne .Lrasterizer_xbox_bitmap_swizzle3d_long_5\n\t"
      "movl 0x10(%%ebp), %%esi\n\t"
      "movl 0x4d0494, %%ecx\n\t"
      ".Lrasterizer_xbox_bitmap_swizzle3d_long_6:\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "subl %%ecx, %%edx\n\t"
      "andl %%ecx, %%edx\n\t"
      "decl %%eax\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "jne .Lrasterizer_xbox_bitmap_swizzle3d_long_4\n\t"
      "movl 0x4d0490, %%edx\n\t"
      ".Lrasterizer_xbox_bitmap_swizzle3d_long_7:\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "subl %%edx, %%eax\n\t"
      "andl %%edx, %%eax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "decl -0x10(%%ebp)\n\t"
      "jne .Lrasterizer_xbox_bitmap_swizzle3d_long_3\n\t"
      ".Lrasterizer_xbox_bitmap_swizzle3d_long_8:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b182cf0_assert), [exitfn] "m"(b182cf0_exitfn), [c182610] "m"(b182cf0_c182610)
      : "memory");
}
#else
#error "rasterizer_xbox_bitmap_swizzle3d_long: clang naked draft required"
#endif


/* FUN_00182e00 (0x182e00) — XBE naked draft (batch 303). */
#if defined(__clang__)
static void (*const b182e00_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b182e00_exitfn)(int) = system_exit;
static int (*const b182e00_c7d960)(void *bitmap, int mipmap_index) = bitmap_mipmap_get_pixel_data_size;
static void * (*const b182e00_c7d000)(void *bitmap, short mipmap_index) = bitmap_mipmap_address;
static void * (*const b182e00_c8ee60)(uint32_t size, bool zero, const char *file, int line) = debug_malloc;
static short (*const b182e00_c7d6e0)(void *bitmap, int mipmap_index) = bitmap_mipmap_width;
static short (*const b182e00_c7d780)(void *bitmap, short mipmap_index) = bitmap_mipmap_get_height;
static int (*const b182e00_c7d820)(void *bitmap, short mipmap_index) = bitmap_mipmap_get_depth;
static short (*const b182e00_c7c840)(short format) = bitmap_format_bits_per_pixel;
static void (*const b182e00_c182610)(void) = FUN_00182610;
static void (*const b182e00_c1829f0)(void) = rasterizer_xbox_bitmap_swizzle2d_long;
static void (*const b182e00_c182910)(void) = rasterizer_xbox_bitmap_swizzle2d_word;
static void (*const b182e00_c182840)(void) = rasterizer_xbox_bitmap_swizzle2d_byte;
static void (*const b182e00_c182cf0)(void) = rasterizer_xbox_bitmap_swizzle3d_long;
static void (*const b182e00_c182bd0)(void) = rasterizer_xbox_bitmap_swizzle3d_word;
static void (*const b182e00_c182ac0)(void) = rasterizer_xbox_bitmap_swizzle3d_byte;
static void * (*const b182e00_c8e0b0)(void *destination, void *source, size_t size) = csmemcpy;
static void (*const b182e00_c8ef70)(void *ptr, const char *file, int line) = debug_free;
static void (*const b182e00_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;

__attribute__((naked, noinline))
void FUN_00182e00(int param_1 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x20, %%esp\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .LFUN_00182e00_1\n\t"
      "pushl $1\n\t"
      "pushl $0x14e\n\t"
      "pushl $0x2b087c\n\t"
      "pushl $0x263768\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00182e00_1:\n\t"
      "movl 0x2c(%%edi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_00182e00_2\n\t"
      "pushl $1\n\t"
      "pushl $0x14f\n\t"
      "pushl $0x2b087c\n\t"
      "pushl $0x264c30\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00182e00_2:\n\t"
      "movw 0xe(%%edi), %%ax\n\t"
      "testb $0x12, %%al\n\t"
      "jne .LFUN_00182e00_28\n\t"
      "testb $1, %%al\n\t"
      "jne .LFUN_00182e00_3\n\t"
      "pushl $1\n\t"
      "pushl $0x159\n\t"
      "pushl $0x2b087c\n\t"
      "pushl $0x2a2760\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00182e00_3:\n\t"
      "pushl %%ebx\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "cmpw %%bx, 0x14(%%edi)\n\t"
      "movl %%ebx, -0x10(%%ebp)\n\t"
      "jl .LFUN_00182e00_27\n\t"
      "pushl %%esi\n\t"
      "jmp .LFUN_00182e00_5\n\t"
      ".LFUN_00182e00_4:\n\t"
      "movl -0x10(%%ebp), %%ebx\n\t"
      "jmp .LFUN_00182e00_5\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".LFUN_00182e00_5:\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "call *%[c7d960]\n\t"
      "movl %%eax, %%esi\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "movl %%esi, -0x18(%%ebp)\n\t"
      "call *%[c7d000]\n\t"
      "pushl $0x15f\n\t"
      "pushl $0x2b087c\n\t"
      "pushl $0\n\t"
      "pushl %%esi\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "call *%[c8ee60]\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "call *%[c7d6e0]\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "movl %%eax, %%esi\n\t"
      "call *%[c7d780]\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "call *%[c7d820]\n\t"
      "addl $0x38, %%esp\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_00182e00_25\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0xc(%%edi), %%cx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c7c840]\n\t"
      "movswl %%ax, %%eax\n\t"
      "cdq\n\t"
      "andl $7, %%edx\n\t"
      "addl %%edx, %%eax\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "sarl $3, %%eax\n\t"
      "pushl %%ebx\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "call *%[c182610]\n\t"
      "movswl 0xa(%%edi), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "subl $0, %%eax\n\t"
      "je .LFUN_00182e00_19\n\t"
      "decl %%eax\n\t"
      "je .LFUN_00182e00_14\n\t"
      "decl %%eax\n\t"
      "je .LFUN_00182e00_6\n\t"
      "pushl $1\n\t"
      "pushl $0x1b4\n\t"
      "pushl $0x2b087c\n\t"
      "pushl $0x261d30\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "jmp .LFUN_00182e00_24\n\t"
      ".LFUN_00182e00_6:\n\t"
      "movswl -0x14(%%ebp), %%eax\n\t"
      "movl -0x8(%%ebp), %%edi\n\t"
      "movl %%eax, -0x1c(%%ebp)\n\t"
      "movl $0x2aaaaaab, %%eax\n\t"
      "imull -0x18(%%ebp)\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movl %%edx, %%ecx\n\t"
      "shrl $0x1f, %%ecx\n\t"
      "addl %%ecx, %%edx\n\t"
      "movl %%edi, %%ecx\n\t"
      "subl %%ecx, %%eax\n\t"
      "movl %%edx, -0x20(%%ebp)\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "movl $6, -0x14(%%ebp)\n\t"
      "jmp .LFUN_00182e00_8\n\t"
      ".LFUN_00182e00_7:\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "movl %%edi, %%edi\n\t"
      ".LFUN_00182e00_8:\n\t"
      "movl -0x1c(%%ebp), %%ecx\n\t"
      "decl %%ecx\n\t"
      "je .LFUN_00182e00_11\n\t"
      "decl %%ecx\n\t"
      "je .LFUN_00182e00_10\n\t"
      "subl $2, %%ecx\n\t"
      "je .LFUN_00182e00_9\n\t"
      "pushl $1\n\t"
      "pushl $0x1a9\n\t"
      "pushl $0x2b087c\n\t"
      "pushl $0x2b08ec\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "jmp .LFUN_00182e00_13\n\t"
      ".LFUN_00182e00_9:\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "addl %%edi, %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[c1829f0]\n\t"
      "jmp .LFUN_00182e00_12\n\t"
      ".LFUN_00182e00_10:\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "addl %%edi, %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[c182910]\n\t"
      "jmp .LFUN_00182e00_12\n\t"
      ".LFUN_00182e00_11:\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "addl %%edi, %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[c182840]\n\t"
      ".LFUN_00182e00_12:\n\t"
      "addl $0x10, %%esp\n\t"
      ".LFUN_00182e00_13:\n\t"
      "movl -0x20(%%ebp), %%ecx\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "addl %%ecx, %%edi\n\t"
      "decl %%eax\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "jne .LFUN_00182e00_7\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "jmp .LFUN_00182e00_24\n\t"
      ".LFUN_00182e00_14:\n\t"
      "movswl -0x14(%%ebp), %%eax\n\t"
      "decl %%eax\n\t"
      "je .LFUN_00182e00_18\n\t"
      "decl %%eax\n\t"
      "je .LFUN_00182e00_17\n\t"
      "subl $2, %%eax\n\t"
      "je .LFUN_00182e00_16\n\t"
      "pushl $1\n\t"
      "pushl $0x18f\n\t"
      ".LFUN_00182e00_15:\n\t"
      "pushl $0x2b087c\n\t"
      "pushl $0x2b08ec\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "jmp .LFUN_00182e00_24\n\t"
      ".LFUN_00182e00_16:\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c182cf0]\n\t"
      "addl $0x14, %%esp\n\t"
      "jmp .LFUN_00182e00_24\n\t"
      ".LFUN_00182e00_17:\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c182bd0]\n\t"
      "addl $0x14, %%esp\n\t"
      "jmp .LFUN_00182e00_24\n\t"
      ".LFUN_00182e00_18:\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c182ac0]\n\t"
      "addl $0x14, %%esp\n\t"
      "jmp .LFUN_00182e00_24\n\t"
      ".LFUN_00182e00_19:\n\t"
      "movswl -0x14(%%ebp), %%eax\n\t"
      "decl %%eax\n\t"
      "je .LFUN_00182e00_22\n\t"
      "decl %%eax\n\t"
      "je .LFUN_00182e00_21\n\t"
      "subl $2, %%eax\n\t"
      "je .LFUN_00182e00_20\n\t"
      "pushl $1\n\t"
      "pushl $0x17b\n\t"
      "jmp .LFUN_00182e00_15\n\t"
      ".LFUN_00182e00_20:\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c1829f0]\n\t"
      "jmp .LFUN_00182e00_23\n\t"
      ".LFUN_00182e00_21:\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c182910]\n\t"
      "jmp .LFUN_00182e00_23\n\t"
      ".LFUN_00182e00_22:\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c182840]\n\t"
      ".LFUN_00182e00_23:\n\t"
      "addl $0x10, %%esp\n\t"
      ".LFUN_00182e00_24:\n\t"
      "movl -0x18(%%ebp), %%edx\n\t"
      "movl -0x4(%%ebp), %%esi\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "call *%[c8e0b0]\n\t"
      "pushl $0x1b8\n\t"
      "pushl $0x2b087c\n\t"
      "pushl %%esi\n\t"
      "call *%[c8ef70]\n\t"
      "addl $0x18, %%esp\n\t"
      "orb $8, 0xe(%%edi)\n\t"
      "jmp .LFUN_00182e00_26\n\t"
      ".LFUN_00182e00_25:\n\t"
      "pushl $0x2b08b0\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_00182e00_26:\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "incl %%eax\n\t"
      "cmpw 0x14(%%edi), %%ax\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "jle .LFUN_00182e00_4\n\t"
      "popl %%esi\n\t"
      ".LFUN_00182e00_27:\n\t"
      "popl %%ebx\n\t"
      ".LFUN_00182e00_28:\n\t"
      "popl %%edi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b182e00_assert), [exitfn] "m"(b182e00_exitfn), [c7d960] "m"(b182e00_c7d960), [c7d000] "m"(b182e00_c7d000), [c8ee60] "m"(b182e00_c8ee60), [c7d6e0] "m"(b182e00_c7d6e0), [c7d780] "m"(b182e00_c7d780), [c7d820] "m"(b182e00_c7d820), [c7c840] "m"(b182e00_c7c840), [c182610] "m"(b182e00_c182610), [c1829f0] "m"(b182e00_c1829f0), [c182910] "m"(b182e00_c182910), [c182840] "m"(b182e00_c182840), [c182cf0] "m"(b182e00_c182cf0), [c182bd0] "m"(b182e00_c182bd0), [c182ac0] "m"(b182e00_c182ac0), [c8e0b0] "m"(b182e00_c8e0b0), [c8ef70] "m"(b182e00_c8ef70), [c8f390] "m"(b182e00_c8f390)
      : "memory");
}
#else
#error "FUN_00182e00: clang naked draft required"
#endif


/* FUN_00183120 (0x183120) — XBE naked draft (batch 323). */
#if defined(__clang__)
static bool (*const b183120_c7d470)(void *bitmap, int check_hardware) = bitmap_verify;
static void (*const b183120_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b183120_exitfn)(int) = system_exit;
static int16_t (*const b183120_c108db0)(unsigned int value) = FUN_00108db0;

__attribute__((naked, noinline))
int16_t FUN_00183120(void *bitmap __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "pushl %%edi\n\t"
      "xorl %%edi, %%edi\n\t"
      "pushl %%edi\n\t"
      "pushl %%esi\n\t"
      "call *%[c7d470]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00183120_1\n\t"
      "pushl $1\n\t"
      "pushl $0x1cb\n\t"
      "pushl $0x2b087c\n\t"
      "pushl $0x264da0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00183120_1:\n\t"
      "movw 0xe(%%esi), %%ax\n\t"
      "testb $1, %%al\n\t"
      "je .LFUN_00183120_13\n\t"
      "testb $0x10, %%al\n\t"
      "jne .LFUN_00183120_13\n\t"
      "testb $2, %%al\n\t"
      "je .LFUN_00183120_6\n\t"
      "movswl 0x6(%%esi), %%eax\n\t"
      "movswl 0x8(%%esi), %%edi\n\t"
      "cdq\n\t"
      "andl $3, %%edx\n\t"
      "addl %%edx, %%eax\n\t"
      "movl %%eax, %%ecx\n\t"
      "sarl $2, %%ecx\n\t"
      "cmpl %%edi, %%ecx\n\t"
      "movl %%ecx, %%ebx\n\t"
      "jg .LFUN_00183120_2\n\t"
      "movl %%edi, %%ebx\n\t"
      ".LFUN_00183120_2:\n\t"
      "movswl 0x4(%%esi), %%eax\n\t"
      "cdq\n\t"
      "andl $3, %%edx\n\t"
      "addl %%edx, %%eax\n\t"
      "sarl $2, %%eax\n\t"
      "cmpl %%ebx, %%eax\n\t"
      "jg .LFUN_00183120_3\n\t"
      "cmpl %%edi, %%ecx\n\t"
      "movl %%ecx, %%eax\n\t"
      "jg .LFUN_00183120_3\n\t"
      "movl %%edi, %%eax\n\t"
      ".LFUN_00183120_3:\n\t"
      "movw 0x14(%%esi), %%di\n\t"
      "pushl %%eax\n\t"
      "call *%[c108db0]\n\t"
      "addl $4, %%esp\n\t"
      "cmpw %%ax, %%di\n\t"
      "jle .LFUN_00183120_13\n\t"
      "movswl 0x6(%%esi), %%eax\n\t"
      "movswl 0x8(%%esi), %%edi\n\t"
      "cdq\n\t"
      "andl $3, %%edx\n\t"
      "addl %%edx, %%eax\n\t"
      "movl %%eax, %%ecx\n\t"
      "sarl $2, %%ecx\n\t"
      "cmpl %%edi, %%ecx\n\t"
      "movl %%ecx, %%ebx\n\t"
      "jg .LFUN_00183120_4\n\t"
      "movl %%edi, %%ebx\n\t"
      ".LFUN_00183120_4:\n\t"
      "movswl 0x4(%%esi), %%eax\n\t"
      "cdq\n\t"
      "andl $3, %%edx\n\t"
      "addl %%edx, %%eax\n\t"
      "sarl $2, %%eax\n\t"
      "cmpl %%ebx, %%eax\n\t"
      "jg .LFUN_00183120_5\n\t"
      "cmpl %%edi, %%ecx\n\t"
      "movl %%ecx, %%eax\n\t"
      "jg .LFUN_00183120_5\n\t"
      "movl %%edi, %%eax\n\t"
      ".LFUN_00183120_5:\n\t"
      "pushl %%eax\n\t"
      "call *%[c108db0]\n\t"
      "addl $4, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00183120_6:\n\t"
      "movw 0x6(%%esi), %%ax\n\t"
      "movw 0x8(%%esi), %%cx\n\t"
      "cmpw %%cx, %%ax\n\t"
      "movswl %%ax, %%edi\n\t"
      "jg .LFUN_00183120_7\n\t"
      "movswl %%cx, %%edi\n\t"
      ".LFUN_00183120_7:\n\t"
      "movswl 0x4(%%esi), %%edx\n\t"
      "cmpl %%edi, %%edx\n\t"
      "jle .LFUN_00183120_8\n\t"
      "movl %%edx, %%eax\n\t"
      "jmp .LFUN_00183120_9\n\t"
      ".LFUN_00183120_8:\n\t"
      "cmpw %%cx, %%ax\n\t"
      "movswl %%ax, %%eax\n\t"
      "jg .LFUN_00183120_9\n\t"
      "movswl %%cx, %%eax\n\t"
      ".LFUN_00183120_9:\n\t"
      "movw 0x14(%%esi), %%di\n\t"
      "pushl %%eax\n\t"
      "call *%[c108db0]\n\t"
      "addl $4, %%esp\n\t"
      "cmpw %%ax, %%di\n\t"
      "jle .LFUN_00183120_13\n\t"
      "movw 0x6(%%esi), %%ax\n\t"
      "movw 0x8(%%esi), %%cx\n\t"
      "cmpw %%cx, %%ax\n\t"
      "movswl %%ax, %%edi\n\t"
      "jg .LFUN_00183120_10\n\t"
      "movswl %%cx, %%edi\n\t"
      ".LFUN_00183120_10:\n\t"
      "movswl 0x4(%%esi), %%edx\n\t"
      "cmpl %%edi, %%edx\n\t"
      "jle .LFUN_00183120_11\n\t"
      "movl %%edx, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c108db0]\n\t"
      "addl $4, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00183120_11:\n\t"
      "cmpw %%cx, %%ax\n\t"
      "movswl %%ax, %%eax\n\t"
      "jg .LFUN_00183120_12\n\t"
      "movswl %%cx, %%eax\n\t"
      ".LFUN_00183120_12:\n\t"
      "pushl %%eax\n\t"
      "call *%[c108db0]\n\t"
      "addl $4, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00183120_13:\n\t"
      "movw %%di, %%ax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c7d470] "m"(b183120_c7d470), [assert] "m"(b183120_assert), [exitfn] "m"(b183120_exitfn), [c108db0] "m"(b183120_c108db0)
      : "memory");
}
#else
#error "FUN_00183120: clang naked draft required"
#endif

/* --- rasterizer_text.obj orphan shells (2026-07-26) --- */

/* orphan 0x181020 */
int *FUN_00181020(short index)
{
  int eax = 0;
  int ecx = 0;
  int esi = 0;

  /* test (int16_t)esi, (int16_t)esi -> jl 0x181032 */
  /* cmp eax, ecx -> jl 0x18104f */
  display_assert((char *)0x002b0174, (char *)0x002b01b4, 67, 0);
  system_exit(0);
  return NULL;

  (void)eax;
  (void)ecx;
  (void)esi;
}

/* FUN_00181670 (0x181670) — XBE naked draft (batch 309). */
#if defined(__clang__)
static void (*const b181670_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b181670_exitfn)(int) = system_exit;
static int * (*const b181670_c181020)(short index) = FUN_00181020;
static void * (*const b181670_c8e0b0)(void *destination, void *source, size_t size) = csmemcpy;
static void *(*const b181670_memset)(void *, int, unsigned int) = csmemset;
static void (*const b181670_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;

__attribute__((naked, noinline))
void FUN_00181670(int *params __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .LFUN_00181670_1\n\t"
      "pushl $1\n\t"
      "pushl $0x10a\n\t"
      "pushl $0x2b01b4\n\t"
      "pushl $0x29f510\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00181670_1:\n\t"
      "cmpl $0, (%%edi)\n\t"
      "jne .LFUN_00181670_2\n\t"
      "pushl $1\n\t"
      "pushl $0x10b\n\t"
      "pushl $0x2b01b4\n\t"
      "pushl $0x2b05d4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00181670_2:\n\t"
      "movzbl 0x22(%%edi), %%eax\n\t"
      "andl $0xffffff7f, %%eax\n\t"
      "cmpw 0x5a5bc2, %%ax\n\t"
      "je .LFUN_00181670_3\n\t"
      "pushl $1\n\t"
      "pushl $0x10c\n\t"
      "pushl $0x2b01b4\n\t"
      "pushl $0x2b0568\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00181670_3:\n\t"
      "movb 0x3256d7, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00181670_16\n\t"
      "movw 0x46e008, %%ax\n\t"
      "cmpw $1, %%ax\n\t"
      "jg .LFUN_00181670_16\n\t"
      "jne .LFUN_00181670_4\n\t"
      "cmpw $1, 0x31fa98\n\t"
      "jg .LFUN_00181670_16\n\t"
      ".LFUN_00181670_4:\n\t"
      "cmpw $0, 0x5a5bc0\n\t"
      "jne .LFUN_00181670_16\n\t"
      "movl 0x4d0480, %%ecx\n\t"
      "cmpl $0x400, %%ecx\n\t"
      "jge .LFUN_00181670_15\n\t"
      "flds 0x4(%%edi)\n\t"
      "movl (%%edi), %%edx\n\t"
      "fsubs 0x5a5bc8\n\t"
      "flds 0x8(%%edi)\n\t"
      "fsubs 0x5a5bcc\n\t"
      "flds 0xc(%%edi)\n\t"
      "fsubs 0x5a5bd0\n\t"
      "flds 0x1c(%%edx)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .LFUN_00181670_5\n\t"
      "flds 0x5a5bdc\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "flds 0x5a5bd8\n\t"
      "fmul %%st(3), %%st(0)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds 0x5a5bd4\n\t"
      "fmul %%st(4), %%st(0)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fcomps 0x1c(%%edx)\n\t"
      "fstp %%st(0)\n\t"
      "fnstsw %%ax\n\t"
      "fstp %%st(0)\n\t"
      "testb $5, %%ah\n\t"
      "fstp %%st(0)\n\t"
      "jp .LFUN_00181670_16\n\t"
      "jmp .LFUN_00181670_6\n\t"
      ".LFUN_00181670_5:\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      ".LFUN_00181670_6:\n\t"
      "testl $0xff000000, 0x18(%%edi)\n\t"
      "jbe .LFUN_00181670_16\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl %%ecx, %%esi\n\t"
      "incl %%ecx\n\t"
      "movl %%ecx, 0x4d0480\n\t"
      "call *%[c181020]\n\t"
      "pushl $0x28\n\t"
      "movl %%eax, %%ebx\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "call *%[c8e0b0]\n\t"
      "movw 0x1e(%%edi), %%ax\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpw $-1, 0x1c(%%edi)\n\t"
      "jne .LFUN_00181670_11\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "jne .LFUN_00181670_8\n\t"
      "movw $0x8000, 0x1e(%%ebx)\n\t"
      "movw 0x20(%%edi), %%di\n\t"
      "testw %%di, %%di\n\t"
      "jl .LFUN_00181670_7\n\t"
      "cmpw $8, %%di\n\t"
      "jl .LFUN_00181670_14\n\t"
      ".LFUN_00181670_7:\n\t"
      "pushl $1\n\t"
      "pushl $0x136\n\t"
      "pushl $0x2b01b4\n\t"
      "pushl $0x2b0508\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "jmp .LFUN_00181670_14\n\t"
      ".LFUN_00181670_8:\n\t"
      "movswl 0x20(%%edi), %%ecx\n\t"
      "movswl %%ax, %%esi\n\t"
      "shll $0x10, %%esi\n\t"
      "orl %%ecx, %%esi\n\t"
      "jl .LFUN_00181670_9\n\t"
      "cmpl $0x10000, %%esi\n\t"
      "jl .LFUN_00181670_10\n\t"
      ".LFUN_00181670_9:\n\t"
      "pushl $1\n\t"
      "pushl $0x141\n\t"
      "pushl $0x2b01b4\n\t"
      "pushl $0x2b04a0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00181670_10:\n\t"
      "leal 0x8(%%esi), %%edx\n\t"
      "sarl $0x10, %%esi\n\t"
      "orl $0xffff8000, %%esi\n\t"
      "movw %%dx, 0x20(%%ebx)\n\t"
      "movw %%si, 0x1e(%%ebx)\n\t"
      "jmp .LFUN_00181670_14\n\t"
      ".LFUN_00181670_11:\n\t"
      "movswl 0x1e(%%ebx), %%esi\n\t"
      "imull $0x22, %%esi, %%esi\n\t"
      "addl $0x4bed80, %%esi\n\t"
      "testw %%ax, %%ax\n\t"
      "jl .LFUN_00181670_12\n\t"
      "cmpw $0x380, %%ax\n\t"
      "jl .LFUN_00181670_13\n\t"
      ".LFUN_00181670_12:\n\t"
      "pushl $1\n\t"
      "pushl $0x152\n\t"
      "pushl $0x2b01b4\n\t"
      "pushl $0x2b0450\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00181670_13:\n\t"
      "movw 0x1c(%%edi), %%ax\n\t"
      "cmpw (%%esi), %%ax\n\t"
      "je .LFUN_00181670_14\n\t"
      "pushl $0x20\n\t"
      "leal 0x2(%%esi), %%ecx\n\t"
      "pushl $0\n\t"
      "pushl %%ecx\n\t"
      "call *%[memset]\n\t"
      "movw 0x1c(%%ebx), %%dx\n\t"
      "addl $0xc, %%esp\n\t"
      "movw %%dx, (%%esi)\n\t"
      ".LFUN_00181670_14:\n\t"
      "cmpw $2, 0x3256ba\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "jne .LFUN_00181670_16\n\t"
      "incl 0x5a554c\n\t"
      "popl %%edi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00181670_15:\n\t"
      "movb 0x4d0484, %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00181670_16\n\t"
      "pushl $0x2b0418\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "movb $1, 0x4d0484\n\t"
      ".LFUN_00181670_16:\n\t"
      "popl %%edi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b181670_assert), [exitfn] "m"(b181670_exitfn), [c181020] "m"(b181670_c181020), [c8e0b0] "m"(b181670_c8e0b0), [memset] "m"(b181670_memset), [c8f390] "m"(b181670_c8f390)
      : "memory");
}
#else
#error "FUN_00181670: clang naked draft required"
#endif

