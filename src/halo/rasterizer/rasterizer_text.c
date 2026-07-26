/* FUN_0017ff50: stub (0x17ff50) */
void FUN_0017ff50(void)
{
}

/* rasterizer_frame_statistics.c */

/* rasterizer_frame_statistics_dispose: free frame statistics buffer if
 * allocated (0x17ff60) */
void FUN_0017ff60(void)
{
  void *ptr;
  ptr = *(void **)0x47ec40;
  if (ptr != 0) {
    debug_free(ptr,
               "c:\\halo\\SOURCE\\rasterizer\\rasterizer_frame_statistics.c",
               0x345);
  }
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

/* rasterizer_geometry_vertex_type_to_stride: return vertex stride for type,
 * assert valid range (0x180050) */
int FUN_00180050(short param_1)
{
  if ((param_1 < 0) || (0xb < param_1)) {
    display_assert("type>=0 && type<NUMBER_OF_RASTERIZER_VERTEX_TYPES",
                   "c:\\halo\\SOURCE\\rasterizer\\rasterizer_geometry.c", 0xaa,
                   1);
    system_exit(-1);
  }
  return (int)*(short *)(0x2afe14 + param_1 * 2);
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


/* rasterizer_geometry_vertex_get_position: copy 3-float position from vertex
 * to output (0x180500) */
void FUN_00180500(float *param_1, float *param_2)
{
  if (param_1 == 0) {
    display_assert("vertex",
                   "c:\\halo\\SOURCE\\rasterizer\\rasterizer_geometry.c", 0x1b6,
                   1);
    system_exit(-1);
  }
  if (param_2 == 0) {
    display_assert(
      "point", "c:\\halo\\SOURCE\\rasterizer\\rasterizer_geometry.c", 0x1b7, 1);
    system_exit(-1);
  }
  param_2[0] = param_1[0];
  param_2[1] = param_1[1];
  param_2[2] = param_1[2];
}

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

/* rasterizer_geometry_vertex_get_texcoord: copy 2-float texcoord from
 * compressed vertex to output (0x1805f0) */
void FUN_001805f0(int param_1, float *param_2)
{
  if (param_1 == 0) {
    display_assert("vertex",
                   "c:\\halo\\SOURCE\\rasterizer\\rasterizer_geometry.c", 0x1ce,
                   1);
    system_exit(-1);
  }
  if (param_2 == 0) {
    display_assert("texcoord",
                   "c:\\halo\\SOURCE\\rasterizer\\rasterizer_geometry.c", 0x1cf,
                   1);
    system_exit(-1);
  }
  param_2[0] = *(float *)(param_1 + 0x18);
  param_2[1] = *(float *)(param_1 + 0x1c);
}

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

/* rasterizer_geometry_float_to_uint8: clamp float [0,1] to byte via scale
 * 255.0. FISTP round-to-nearest in original; C cast truncates — structural
 * rounding delta at midpoints. (0x1807d0) */
unsigned char FUN_001807d0(float param_1)
{
  float clamped;
  if (param_1 < 0.0f) {
    clamped = 0.0f;
  } else if (param_1 > 1.0f) {
    clamped = 1.0f;
  } else {
    clamped = param_1;
  }
  return (unsigned char)(int)(clamped * *(float *)0x2602c8);
}

/* rasterizer_geometry_pack_normal_11_11_10_validated: pack float[3] normal
 * into 11-11-10 uint, asserting components in [-1.0, 1.0]. Encodes via
 * floor(component * scale) + FISTP. Verifies round-trip via FUN_0017ffc0.
 * Structural cap: FUCOMPP-based range asserts cannot be matched exactly.
 * layout: bits[10:0]=i, bits[21:11]=j, bits[31:22]=k (10-bit). (0x1808f0) */
unsigned int FUN_001808f0(float *param_1)
{
  float decoded_i;
  float decoded_j;
  float decoded_k;
  float *decoded;
  unsigned int i_11;
  unsigned int j_11;
  unsigned int packed;
  int tmp;
  float local_buf[3];

  if (param_1 == 0) {
    display_assert("parameters",
                   "c:\\halo\\SOURCE\\rasterizer\\rasterizer_geometry.c", 0x45,
                   1);
    system_exit(-1);
  }
  if (*param_1 < -1.0f || *param_1 > 1.0f || param_1[1] < -1.0f ||
      param_1[1] > 1.0f || param_1[2] < -1.0f || param_1[2] > 1.0f) {
    display_assert("invalid vector",
                   "c:\\halo\\SOURCE\\rasterizer\\rasterizer_geometry.c", 0x4e,
                   1);
    system_exit(-1);
  }
  tmp = (int)floor((double)(*param_1 * *(float *)0x2b0118));
  i_11 = (unsigned int)tmp & 0x7ff;
  tmp = (int)floor((double)(param_1[1] * *(float *)0x2b0118));
  j_11 = (unsigned int)tmp & 0x7ff;
  tmp = (int)floor((double)(param_1[2] * *(float *)0x2b0114));
  packed = (((unsigned int)tmp & 0x3ff) << 11 | j_11) << 11 | i_11;

  decoded = FUN_0017ffc0(local_buf, packed);
  decoded_i = decoded[0];
  decoded_j = decoded[1];
  decoded_k = decoded[2];

  if ((float)*(double *)0x28b800 <= fabsf(decoded_i - *param_1)) {
    display_assert("fabs(v2.i - v->i)<0.01f",
                   "c:\\halo\\SOURCE\\rasterizer\\rasterizer_geometry.c", 0x5c,
                   1);
    system_exit(-1);
  }
  if ((float)*(double *)0x28b800 <= fabsf(decoded_j - param_1[1])) {
    display_assert("fabs(v2.j - v->j)<0.01f",
                   "c:\\halo\\SOURCE\\rasterizer\\rasterizer_geometry.c", 0x5d,
                   1);
    system_exit(-1);
  }
  if ((float)*(double *)0x28b800 <= fabsf(decoded_k - param_1[2])) {
    display_assert("fabs(v2.k - v->k)<0.01f",
                   "c:\\halo\\SOURCE\\rasterizer\\rasterizer_geometry.c", 0x5e,
                   1);
    system_exit(-1);
  }
  return packed;
}

/* rasterizer_geometry_pack_normal_11_11_10_clamped: clamp float[3] normal to
 * [-1.0, 1.0] then pack to 11-11-10 uint. Same encoding as FUN_001808f0 but
 * silently clamps out-of-range values. Verifies round-trip via FUN_0017ffc0.
 * layout: bits[10:0]=i, bits[21:11]=j, bits[31:22]=k (10-bit). (0x180b10) */
unsigned int FUN_00180b10(float *param_1)
{
  float ci;
  float cj;
  float ck;
  float *decoded;
  float decoded_i;
  float decoded_j;
  float decoded_k;
  unsigned int i_11;
  unsigned int j_11;
  unsigned int packed;
  int tmp;
  float local_buf[3];

  if (param_1 == 0) {
    display_assert("parameters",
                   "c:\\halo\\SOURCE\\rasterizer\\rasterizer_geometry.c", 0x68,
                   1);
    system_exit(-1);
  }
  if (*param_1 < -1.0f) {
    ci = -1.0f;
  } else if (*param_1 > 1.0f) {
    ci = 1.0f;
  } else {
    ci = *param_1;
  }
  tmp = (int)floor((double)(ci * *(float *)0x2b0118));
  i_11 = (unsigned int)tmp & 0x7ff;

  if (param_1[1] < -1.0f) {
    cj = -1.0f;
  } else if (param_1[1] > 1.0f) {
    cj = 1.0f;
  } else {
    cj = param_1[1];
  }
  tmp = (int)floor((double)(cj * *(float *)0x2b0118));
  j_11 = (unsigned int)tmp & 0x7ff;

  if (param_1[2] < -1.0f) {
    ck = -1.0f;
  } else if (param_1[2] > 1.0f) {
    ck = 1.0f;
  } else {
    ck = param_1[2];
  }
  tmp = (int)floor((double)(ck * *(float *)0x2b0114));
  packed = (((unsigned int)tmp & 0x3ff) << 11 | j_11) << 11 | i_11;

  decoded = FUN_0017ffc0(local_buf, packed);
  decoded_i = decoded[0];
  decoded_j = decoded[1];
  decoded_k = decoded[2];

  if ((float)*(double *)0x28b800 <= fabsf(decoded_i - *param_1)) {
    display_assert("fabs(v2.i - v->i)<0.01f",
                   "c:\\halo\\SOURCE\\rasterizer\\rasterizer_geometry.c", 0x76,
                   1);
    system_exit(-1);
  }
  if ((float)*(double *)0x28b800 <= fabsf(decoded_j - param_1[1])) {
    display_assert("fabs(v2.j - v->j)<0.01f",
                   "c:\\halo\\SOURCE\\rasterizer\\rasterizer_geometry.c", 0x77,
                   1);
    system_exit(-1);
  }
  if ((float)*(double *)0x28b800 <= fabsf(decoded_k - param_1[2])) {
    display_assert("fabs(v2.k - v->k)<0.01f",
                   "c:\\halo\\SOURCE\\rasterizer\\rasterizer_geometry.c", 0x78,
                   1);
    system_exit(-1);
  }
  return packed;
}

/* rasterizer_geometry_vertex_compress: compress vertex buffer (0x180d10)
 * ported=false: structural cap, too complex for reliable VC71 match */
void FUN_00180d10(short param_1, int param_2, int param_3, int param_4,
                  void *param_5, int param_6)
{

  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  display_assert((char *)0x002b0084, (char *)0x002afe38, 194, 0);
  system_exit(0);
  /* test edi, edi -> jne 0x180d64 */
  display_assert((char *)0x00263b58, (char *)0x002afe38, 195, 0);
  system_exit(0);
  error(0, (char *)0x002b0140);
  /* cmp eax, ecx -> je 0x180dc2 */
  display_assert((char *)0x002b0008, (char *)0x002afe38, 239, 0);
  system_exit(0);
  /* cmp ecx, eax -> je 0x180dee */
  display_assert((char *)0x002affc4, (char *)0x002afe38, 240, 0);
  system_exit(0);
  /* test ebx, ebx -> jle 0x180fde */
  FUN_00180b10((float *)(uintptr_t)eax);
  FUN_00180b10((float *)(uintptr_t)esi);
  FUN_00180b10((float *)(uintptr_t)ecx);
  FUN_00180890(0.0f);
  FUN_00180890(0.0f);
  FUN_00180890(0.0f);
  /* cmp ecx, eax -> je 0x180eb2 */
  display_assert((char *)0x002aff48, (char *)0x002afe38, 221, 0);
  system_exit(0);
  /* cmp edx, eax -> je 0x180ee0 */
  display_assert((char *)0x002afef8, (char *)0x002afe38, 222, 0);
  system_exit(0);
  /* test ebx, ebx -> jle 0x180fde */
  FUN_00180b10((float *)(uintptr_t)eax);
  FUN_00180890(0.0f);
  FUN_00180890(0.0f);
  /* cmp eax, ecx -> je 0x180f54 */
  display_assert((char *)0x002afeb0, (char *)0x002afe38, 201, 0);
  system_exit(0);
  /* cmp ecx, eax -> je 0x180f80 */
  display_assert((char *)0x002afe68, (char *)0x002afe38, 202, 0);
  system_exit(0);
  /* test ebx, ebx -> jle 0x180fde */
  FUN_00180b10((float *)(uintptr_t)eax);
  FUN_00180b10((float *)(uintptr_t)esi);
  FUN_00180b10((float *)(uintptr_t)ecx);
  /* relift: relift: mov (int16_t)eax, word ptr [0x46e008] */
  /* cmp (int16_t)eax, 1 -> jg 0x18100b */
  /* relift: cmp word ptr [0x31fa98], 1 -> jg 0x18100b */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* rasterizer_lights.c */

/* rasterizer_lights_initialize: clear lights buffers and counter (0x181150) */
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

/* lens_flare_scenery_queue: queue lens flares from scenario scenery lights for
 * rendering. Iterates light-marker block entries for param_1 scenery_light
 * index. Builds a 0x28-byte params struct and calls FUN_00181670 (the lens
 * flare queue submission function) for each entry. (0x181900) */
void FUN_00181900(short param_1)
{
  int scenario; /* scenario base ptr */
  int light_block; /* scenario->scenery_lights[param_1] element ptr */
  int lf_block_base; /* scenario->lens_flare_block ptr */
  int lf_mark_base; /* scenario->lens_flare_marker_block ptr */
  int entry; /* current light_marker_block entry ptr */
  int lf_instance; /* lens_flare_instance element ptr */
  int loop_end; /* count of light_marker entries */
  int i; /* loop counter */
  /* params struct for FUN_00181670: 0x28-byte contiguous buffer.
   * Layout (confirmed from disassembly at 0x181a2c..0x181a67):
   *   +0x00: tag_get('lens', def->tag_index) result
   *   +0x04: entry->xyz[0] (float, from puVar2[0..2])
   *   +0x08: entry->xyz[1]
   *   +0x0c: entry->xyz[2]
   *   +0x10: FUN_00180b10(&dir_vec) = compressed normal of direction
   *   +0x14: FUN_00180b10(&perp_vec) = compressed normal of perpendicular
   *   +0x18: 0xffffffff (color/alpha = -1)
   *   +0x1c: 0xffff word (light_index = -1 -> scenery path)
   *   +0x1e: entry_index >> 16 (hi word of scenery marker index)
   *   +0x20: entry_index & 0xffff (lo word)
   *   +0x22: DAT_0050654a (compressed window index byte)
   *   +0x23: 0
   */
  int params[10]; /* 0x28 = 40 bytes = 10 ints; accessed as byte/short/int */
  float dir[3]; /* direction vector (from entry bytes 0xc/0xd/0xe * scale) */
  float perp[3]; /* perpendicular vector (from perpendicular3d of dir) */
  int entry_idx; /* combined scenery marker index (hi<<16 | lo) */

  if (*(char *)0x3256d7 == 0) {
    return;
  }
  if (*(short *)0x46e008 > 1) {
    return;
  }
  if (*(short *)0x46e008 == 1 && *(short *)0x31fa98 > 1) {
    return;
  }

  scenario = (int)scenario_get();
  /* tag_block_get_element(scenario+0x134, param_1, 0x68) */
  light_block =
    (int)tag_block_get_element((void *)(scenario + 0x134), (int)param_1, 0x68);
  loop_end = (int)*(short *)(light_block + 0x42);
  if (loop_end <= 0) {
    return;
  }

  lf_mark_base = scenario + 0x128;
  lf_block_base = scenario + 0x11c;

  i = 0;
  do {
    /* light_marker_block entry */
    entry_idx = (int)*(unsigned short *)(light_block + 0x40) + i;
    entry = (int)tag_block_get_element((void *)lf_mark_base, entry_idx, 0x10);

    /* lens_flare_instance element */
    lf_instance = (int)tag_block_get_element(
      (void *)lf_block_base, (int)*(unsigned char *)(entry + 0xf), 0x10);

    /* Extract signed bytes from entry for direction vector */
    dir[0] = (float)(int)*(signed char *)(entry + 0xc) * *(float *)0x2820c0;
    dir[1] = (float)(int)*(signed char *)(entry + 0xd) * *(float *)0x2820c0;
    dir[2] = (float)(int)*(signed char *)(entry + 0xe) * *(float *)0x2820c0;

    /* Compute perpendicular and normalize both */
    perpendicular3d(dir, perp);
    normalize3d(dir);
    normalize3d(perp);

    /* Build params buffer (byte-level stores into int array). */
    *(int *)((char *)params + 0x00) =
      (int)tag_get(0x6c656e73, *(int *)(lf_instance + 0xc));
    *(int *)((char *)params + 0x04) = *(int *)(entry + 0x00);
    *(int *)((char *)params + 0x08) = *(int *)(entry + 0x04);
    *(int *)((char *)params + 0x0c) = *(int *)(entry + 0x08);
    *(unsigned int *)((char *)params + 0x10) = (unsigned int)FUN_00180b10(dir);
    *(unsigned int *)((char *)params + 0x14) = (unsigned int)FUN_00180b10(perp);
    *(int *)((char *)params + 0x18) = -1;
    *(short *)((char *)params + 0x1c) = -1;
    *(short *)((char *)params + 0x1e) = (short)(entry_idx >> 16);
    *(short *)((char *)params + 0x20) = (short)entry_idx;
    *(unsigned char *)((char *)params + 0x22) = *(unsigned char *)0x50654a;
    *(unsigned char *)((char *)params + 0x23) = 0;

    FUN_00181670(params);

    i++;
  } while (i < loop_end);
}

/* lens_flare_occlusion_submit: for each queued lens flare entry, compute the
 * occlusion test position and submit via FUN_0017d030. Wrapped by
 * FUN_0016f910/FUN_0016fa40 rasterizer widget begin/end. (0x181a90) */
void FUN_00181a90(void)
{
  int *entry; /* pointer to queued lens flare slot (from FUN_00181020) */
  int definition; /* *entry = definition tag ptr */
  float *dir_result; /* return of FUN_0017ffc0 (3-float direction vec) */
  short occlusion_dir; /* *(short *)(definition + 0x14) */
  int vis_param; /* *(int *)(definition + 0x10) as int (passes to thunk) */
  int lf_count; /* DAT_004d0480 */
  int i; /* loop index */
  float perp[3]; /* perpendicular output (12 bytes, EBP-0x2c) */
  float dir[3]; /* direction vec copied from FUN_0017ffc0 result */
  float pos[3]; /* output position vec for occlusion test (EBP-0x14) */

  FUN_0016f910(0x17);

  if (*(char *)0x3256d7 == 0) {
    FUN_0016fa40(0x17);
    return;
  }
  if (*(short *)0x46e008 > 1) {
    FUN_0016fa40(0x17);
    return;
  }
  if (*(short *)0x46e008 == 1 && *(short *)0x31fa98 > 1) {
    FUN_0016fa40(0x17);
    return;
  }

  if (*(short *)0x5a5bc0 != 0) {
    FUN_0016fa40(0x17);
    return;
  }

  lf_count = *(int *)0x4d0480;
  if (lf_count <= 0) {
    FUN_0016fa40(0x17);
    return;
  }

  FUN_0017cfc0(6, 1);

  lf_count = *(int *)0x4d0480;
  if (lf_count > 0) {
    i = 0;
    do {
      /* FUN_00181020 takes index via SI register; build system provides
       * a thunk that loads the arg into SI before the call. */
      entry = FUN_00181020((short)i);
      definition = *entry;

      /* FUN_0017ffc0(&perp, entry[4]) fills perp[] and returns a
       * pointer to a 3-float direction vec; copy it into dir[]. */
      dir_result = FUN_0017ffc0(perp, (unsigned int)entry[4]);
      dir[0] = dir_result[0];
      dir[1] = dir_result[1];
      dir[2] = dir_result[2];

      /* MOVZX byte [entry+0x22]; AND 0xffffff7f (clear bit 7) → compare
       * with window index */
      if ((*(unsigned char *)((char *)entry + 0x22) & 0x7f) ==
          *(unsigned short *)0x5a5bc2) {
        occlusion_dir = *(short *)(definition + 0x14);
        vis_param = *(int *)(definition + 0x10);

        if (occlusion_dir == 0) {
          /* Negate scale; use global forward direction (0x5a5bd4) */
          vector3d_scale_add((float *)(entry + 1), (float *)0x5a5bd4,
                             -*(float *)(definition + 0x10), pos);
        } else if (occlusion_dir == 1) {
          /* Scale along dir[] by definition field * constant */
          vector3d_scale_add((float *)(entry + 1), dir,
                             *(float *)(definition + 0x10) * *(float *)0x254e68,
                             pos);
        } else if (occlusion_dir == 2) {
          /* Use object/light position directly */
          pos[0] = *(float *)(entry + 1);
          pos[1] = *(float *)(entry + 2);
          pos[2] = *(float *)(entry + 3);
        } else {
          display_assert(
            "### ERROR unsupported lens flare occlusion offset direction",
            "c:\\halo\\SOURCE\\rasterizer\\rasterizer_lights.c", 0x1e2, 1);
          system_exit(-1);
        }

        entry[9] = FUN_0017d030(pos, vis_param, i);
      }

      i++;
    } while (i < *(int *)0x4d0480);
  }

  /* FUN_0017d020 (thunk → FUN_0017ad90) is called after the loop whenever
   * the first lf_count check passed (i.e. when lf_count > 0), matching
   * the original control-flow shape (0x181bfd falls through to 0x181c02
   * regardless of the inner lf_count re-check). */
  FUN_0017d020();

  FUN_0016fa40(0x17);
}

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

/* rasterizer_memory_pool_new: allocate global rasterizer memory pool (0x1824e0)
 */
int rasterizer_memory_pool_new(void)
{
  void *pool;
  char result;
  result = 1;
  pool = (void *)debug_malloc(
    0x18000, 0, "c:\\halo\\SOURCE\\rasterizer\\rasterizer_memory_pool.c", 0x13);
  *(void **)0x4d0488 = pool;
  if (pool == 0) {
    error(2, "### ERROR rasterizer failed to allocate global memory pool");
    return 0;
  }
  return result;
}

/* rasterizer_memory_pool_reset: reset pool allocation cursor to zero (0x182520)
 */
void rasterizer_memory_pool_reset(void)
{
  *(int *)0x4d048c = 0;
}

/* rasterizer_memory_pool_alloc: allocate from memory pool, optionally copying
 * data (0x182530) */
int rasterizer_memory_pool_alloc(int data, int size)
{
  unsigned int new_offset;
  int result;

  new_offset = *(unsigned int *)0x4d048c + size;
  result = 0;
  if (new_offset < 0x18001) {
    result = *(int *)0x4d0488 + *(int *)0x4d048c;
    *(unsigned int *)0x4d048c = new_offset;
    if (data != 0) {
      csmemcpy((void *)result, (void *)data, size);
      return result;
    }
  } else {
    error(2, "### ERROR rasterizer memory pool exceeded");
  }
  return result;
}

/* rasterizer_memory_pool_copy: assert data non-null then copy into pool
 * (0x182590) */
void rasterizer_memory_pool_copy(int data, int size)
{
  if (data == 0) {
    display_assert("data",
                   "c:\\halo\\SOURCE\\rasterizer\\rasterizer_memory_pool.c",
                   0x42, 1);
    system_exit(-1);
  }
  rasterizer_memory_pool_alloc(data, size);
}

/* FUN_001825d0: stub (0x1825d0) */
void FUN_001825d0(void)
{
}

/* rasterizer_memory_pool_delete: free the global rasterizer memory pool
 * (0x1825e0) */
void rasterizer_memory_pool_delete(void)
{
  if (*(void **)0x4d0488 != 0) {
    debug_free(*(void **)0x4d0488,
               "c:\\halo\\SOURCE\\rasterizer\\rasterizer_memory_pool.c", 0x50);
  }
  *(void **)0x4d0488 = 0;
  *(int *)0x4d048c = 0;
}

/* rasterizer_swizzle.c */

/* rasterizer_swizzle_compute_masks: compute swizzle bit-interleave masks for a
 * texture surface (0x182690).
 * param_1/param_2: log2 of width/height; param_3/param_4: u/v tile indices;
 * param_5[0] = u mask, param_5[1] = v mask. */
void rasterizer_swizzle_compute_masks(short param_1, short param_2,
                                      unsigned short param_3,
                                      unsigned short param_4,
                                      unsigned int *param_5)
{
  int16_t sVar1;
  int16_t sVar2;
  int16_t param_1_min;
  unsigned char bVar5;
  unsigned short uVar3;
  unsigned int uVar6;
  unsigned int uVar4;
  int upper;

  sVar1 = FUN_00108db0((unsigned int)(int)param_1);
  sVar2 = FUN_00108db0((unsigned int)(int)param_2);

  /* param_1_min = min(sVar1, sVar2) */
  param_1_min = sVar2;
  if (sVar1 <= sVar2) {
    param_1_min = sVar1;
  }
  bVar5 = (unsigned char)param_1_min;
  uVar3 = (unsigned short)((1 << (bVar5 & 0x1f)) - 1);

  if ((short)uVar3 < 0x40) {
    uVar6 = (unsigned int)*(
      unsigned short *)((int)0x2b07e0 + (int)(short)(param_3 & uVar3) * 2);
    uVar4 = (unsigned int)*(
      unsigned short *)((int)0x2b07e0 + (int)(short)(param_4 & uVar3) * 2);
  } else {
    upper = (int)(short)uVar3 >> 6;
    if (upper > 0x3f) {
      display_assert("upper_mask<=63",
                     "c:\\halo\\SOURCE\\rasterizer\\rasterizer_swizzle.c", 0x56,
                     1);
      system_exit(-1);
    }
    uVar6 = (unsigned int)*(
              unsigned short *)((int)0x2b07e0 +
                                (((int)(short)param_3 >> 6) & upper) * 2)
              << 0xc |
            (unsigned int)*(unsigned short *)((int)0x2b07e0 +
                                              ((int)(short)param_3 & 0x3f) * 2);
    uVar4 = (unsigned int)*(
              unsigned short *)((int)0x2b07e0 +
                                (((int)(short)param_4 >> 6) & upper) * 2)
              << 0xc |
            (unsigned int)*(unsigned short *)((int)0x2b07e0 +
                                              ((int)(short)param_4 & 0x3f) * 2);
  }
  uVar4 = uVar4 << 1;
  if (param_1_min < sVar1) {
    param_5[1] = uVar4;
    *param_5 = uVar6 | ((int)(short)param_3 >> (bVar5 & 0x1f))
                         << (bVar5 * 2 & 0x1f);
    return;
  }
  if (param_1_min < sVar2) {
    uVar4 = uVar4 | ((int)(short)param_4 >> (bVar5 & 0x1f))
                      << (bVar5 * 2 & 0x1f);
  }
  *param_5 = uVar6;
  param_5[1] = uVar4;
}

/* rasterizer_swizzle_interleave_bits: interleave bits from up to 3 channels
 * into a Morton (Z-order) swizzle address (0x1827c0).
 * param_1/param_2/param_3: bit counts for each channel;
 * param_4/param_5/param_6: channel values (x/y/z);
 * param_7[0]=x bits, param_7[1]=y bits, param_7[2]=z bits. */
void rasterizer_swizzle_interleave_bits(short param_1, short param_2,
                                        short param_3, unsigned int param_4,
                                        unsigned int param_5,
                                        unsigned int param_6,
                                        unsigned int *param_7)
{
  unsigned int local_c;
  unsigned int local_8;
  unsigned int uVar7;
  short sVar6;
  short sVar4;
  short sVar5;
  short bVar8;
  unsigned int uVar1;
  unsigned int uVar2;
  unsigned int uVar3;

  local_c = 0;
  local_8 = 0;
  uVar7 = 0;
  sVar6 = 1;
  sVar4 = 0;
  do {
    uVar3 = param_6;
    uVar2 = param_5;
    uVar1 = param_4;
    sVar5 = sVar4;
    if (sVar6 < param_1) {
      param_4 = (unsigned int)(unsigned short)((short)param_4 >> 1);
      local_8 = local_8 | (uVar1 & 1) << ((unsigned char)sVar4 & 0x1f);
      sVar5 = sVar4 + 1;
    }
    if (sVar6 < param_2) {
      param_5 = (unsigned int)(unsigned short)((short)param_5 >> 1);
      local_c = local_c | (uVar2 & 1) << ((unsigned char)sVar5 & 0x1f);
      sVar5 = sVar5 + 1;
    }
    if (sVar6 < param_3) {
      param_6 = (unsigned int)(unsigned short)((short)param_6 >> 1);
      uVar7 = uVar7 | (uVar3 & 1) << ((unsigned char)sVar5 & 0x1f);
      sVar5 = sVar5 + 1;
    }
    sVar6 = sVar6 << 1;
    bVar8 = (short)(sVar4 != sVar5);
    sVar4 = sVar5;
  } while (bVar8);
  param_7[2] = uVar7;
  *param_7 = local_8;
  param_7[1] = local_c;
}

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

/* rasterizer_swizzle_bitmap_all: rebuild hardware format for a bitmap by
 * allocating a swizzle buffer and copying/padding all face mipmaps
 * (0x183390). Returns 1 on success, 0 on out-of-memory. */
int FUN_00183390(int param_1)
{
  int total_size;
  int iVar8;
  unsigned short face_count;
  short sVar2;
  short sVar3;
  int local_c;
  short face_index;
  int swizzle_buf;
  int mip_src;
  int mip_size;
  int row_pitch;
  short adjusted_face_index;
  short local_1c;
  int local_20;

  total_size = FUN_00183290((void *)param_1);
  iVar8 = 0;
  /* face_count: 1 for 2D textures, 6 for cubemaps */
  face_count = (unsigned short)(*(short *)(param_1 + 10) != 2) - 1 & 5;
  local_1c = (short)(face_count + 1);
  if (*(int *)(param_1 + 0x2c) == 0) {
    display_assert("bitmap->base_address",
                   "c:\\halo\\SOURCE\\rasterizer\\rasterizer_swizzle.c", 0x225,
                   1);
    system_exit(-1);
  }
  swizzle_buf = (int)debug_malloc(
    total_size, 0, "c:\\halo\\SOURCE\\rasterizer\\rasterizer_swizzle.c", 0x228);
  if (swizzle_buf == 0) {
    error(2, "### ERROR rasterizer_xbox_bitmap_rebuild_hardware_format "
             "failed (out of memory)");
    return 0;
  }
  FUN_00182e00(param_1);
  face_index = 0;
  if (local_1c > 0) {
    do {
      sVar2 = FUN_00183120((void *)param_1);
      if (-1 < (int)sVar2) {
        local_c = 0;
        local_20 = (int)sVar2;
        do {
          mip_src = (int)bitmap_mipmap_address((void *)param_1, local_c);
          mip_size =
            bitmap_mipmap_get_pixel_data_size((void *)param_1, local_c);
          if (*(short *)(param_1 + 10) == 2) {
            mip_size = mip_size / 6;
          }
          adjusted_face_index = *(short *)((int)0x2b0860 + (int)face_index * 2);
          if ((*(unsigned char *)(param_1 + 0xe) & 0x10) == 0) {
            /* non-swizzled: copy face mipmap data */
            csmemcpy((void *)(swizzle_buf + iVar8),
                     (void *)((int)adjusted_face_index * mip_size + mip_src),
                     (unsigned int)mip_size);
            iVar8 = iVar8 + mip_size;
          } else {
            /* swizzled/tiled: must be face 0, mip 0 */
            if ((face_index != 0) || (adjusted_face_index != 0)) {
              display_assert(
                "face_index==0 && adjusted_face_index==0",
                "c:\\halo\\SOURCE\\rasterizer\\rasterizer_swizzle.c", 0x24c, 1);
              system_exit(-1);
            }
            if ((short)local_c != 0) {
              display_assert(
                "mipmap_index==0",
                "c:\\halo\\SOURCE\\rasterizer\\rasterizer_swizzle.c", 0x24d, 1);
              system_exit(-1);
            }
            if ((*(unsigned char *)(param_1 + 0xe) & 2) != 0) {
              display_assert(
                "!TEST_FLAG(bitmap->flags, _bitmap_compressed_bit)",
                "c:\\halo\\SOURCE\\rasterizer\\rasterizer_swizzle.c", 0x24e, 1);
              system_exit(-1);
            }
            row_pitch = bitmap_mipmap_get_row_pitch((void *)param_1, local_c);
            sVar3 = 0;
            if (0 < *(short *)(param_1 + 6)) {
              do {
                csmemcpy((void *)(swizzle_buf + iVar8), (void *)mip_src,
                         (unsigned int)row_pitch);
                csmemset((void *)(swizzle_buf + iVar8 + row_pitch), 0,
                         (unsigned int)(-row_pitch & 0x3f));
                mip_src = mip_src + row_pitch;
                iVar8 = iVar8 + row_pitch + (-row_pitch & 0x3f);
                sVar3 = sVar3 + 1;
              } while (sVar3 < *(short *)(param_1 + 6));
            }
          }
          local_c = local_c + 1;
        } while ((short)local_c <= (short)local_20);
      }
      /* align offset to 128 bytes at end of each face */
      csmemset((void *)(swizzle_buf + iVar8), 0, (unsigned int)(-iVar8 & 0x7f));
      iVar8 = iVar8 + (-iVar8 & 0x7f);
      face_index = face_index + 1;
    } while (face_index < local_1c);
  }
  if (iVar8 != total_size) {
    display_assert("offset==size",
                   "c:\\halo\\SOURCE\\rasterizer\\rasterizer_swizzle.c", 0x271,
                   1);
    system_exit(-1);
  }
  csmemcpy(*(void **)(param_1 + 0x2c), (void *)swizzle_buf,
           (unsigned int)total_size);
  debug_free((void *)swizzle_buf,
             "c:\\halo\\SOURCE\\rasterizer\\rasterizer_swizzle.c", 0x275);
  return 1;
}

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

/* rasterizer_text_cache_dispose: dispose hardware character cache (0x183720) */
void rasterizer_text_cache_dispose(void)
{
  if (*(char *)0x4d04a0 != 0) {
    rasterizer_text_cache_flush();
    bitmap_delete(*(void **)0x4d04ac);
    *(char *)0x4d04a0 = 0;
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

/* rasterizer_text_get_character_position: get hardware character screen position.
 * Original ABI: AX=index, EBX=*out_y, stack=*out_x
 */
void rasterizer_text_get_character_position(short index, short *out_y,
                                            short *out_x)
{
  if (*(char *)0x4d04a0 == 0) {
    display_assert("hardware_character_cache.initialized",
                   "c:\\halo\\SOURCE\\rasterizer\\rasterizer_text.c", 0x255, 1);
    system_exit(-1);
  }
  if (index < 0 || index >= 256) {
    display_assert("hardware_character_index>=0 && "
                   "hardware_character_index<MAXIMUM_HARDWARE_CHARACTERS",
                   "c:\\halo\\SOURCE\\rasterizer\\rasterizer_text.c", 0x256, 1);
    system_exit(-1);
  }
  if (out_x == (short *)0 || out_y == (short *)0) {
    display_assert("x0 && y0",
                   "c:\\halo\\SOURCE\\rasterizer\\rasterizer_text.c", 599, 1);
    system_exit(-1);
  }
  *out_x = *(short *)(0x4d04b4 + index * 8);
  *out_y = *(short *)(0x4d04b6 + index * 8);
}

/* rasterizer_text_evict_character: evict a hardware character from the cache.
 * Original ABI: ESI=slot (pointer to character pointer in cache)
 */
void rasterizer_text_evict_character(int **slot)
{
  int *character;

  if (slot == (int **)0) {
    display_assert("hardware_character",
                   "c:\\halo\\SOURCE\\rasterizer\\rasterizer_text.c", 0x262, 1);
    system_exit(-1);
  }

  character = *slot;
  if (character != (int *)0) {
    *(short *)((char *)character + 0xc) = -1;
    if (*(short *)((char *)character + 0xe) == *(short *)0x325748) {
      error(3, "font cache overwrote character in use");
    }
    *slot = (int *)0;
  }
}

/* rasterizer_text_cache_character: cache a hardware character into the texture cache.
 * Original ABI: EDI=character pointer, stack=font pointer
 */
void rasterizer_text_cache_character(void *font_character, void *font)
{
  int character = (int)font_character;
  short char_width;
  short char_height;
  int **character_slot;
  short hw_index;
  short y;
  short x;
  short *pixel_out;
  unsigned char *pixel_data;
  int i;
  int cache_top;
  int cache_bottom;
  unsigned short read_index;
  unsigned short write_index;

  if (*(char *)0x4d04a0 == 0) {
    display_assert("hardware_character_cache.initialized",
                   "c:\\halo\\SOURCE\\rasterizer\\rasterizer_text.c", 0x279, 1);
    system_exit(-1);
  }

  hw_index = *(short *)(character + 0xc);

  if (hw_index == -1) {
    char_width = *(short *)(character + 4);
    char_height = *(short *)(character + 6);

    if (char_width > 128) {
      display_assert(
        "font_character->bitmap_width<=HARDWARE_CHARACTER_CACHE_BITMAP_WIDTH",
        "c:\\halo\\SOURCE\\rasterizer\\rasterizer_text.c", 0x285, 1);
      system_exit(-1);
    }
    if (char_height > 128) {
      display_assert(
        "font_character->bitmap_height<=HARDWARE_CHARACTER_CACHE_BITMAP_HEIGHT",
        "c:\\halo\\SOURCE\\rasterizer\\rasterizer_text.c", 0x286, 1);
      system_exit(-1);
    }

    *(short *)(character + 0xe) = *(short *)0x325748;

    /* Advance to next row if needed. Original writes _DAT_004d04a8 =
       (uint)cursor_y as a single 32-bit store, which zero-extends cursor_y
       into the high half — i.e. max_char_height (0x4d04aa) is reset to 0. */
    if (128 < (int)*(short *)0x4d04a6 + (int)char_width) {
      *(short *)0x4d04a8 += *(short *)0x4d04aa;
      *(short *)0x4d04a6 = 0;
      *(short *)0x4d04aa = 0;
    }

    /* Wrap back to top if needed, evicting characters. Original writes
       _DAT_004d04a8 = 0 as a single 32-bit store, clearing both cursor_y
       (0x4d04a8) and max_char_height (0x4d04aa). */
    if (128 < (int)*(short *)0x4d04a8 + (int)char_height) {
      *(short *)0x4d04a6 = 0;
      *(short *)0x4d04a8 = 0;
      *(short *)0x4d04aa = 0;

      read_index = *(unsigned short *)0x4d04a2;
      write_index = *(unsigned short *)0x4d04a4;

      if (read_index != write_index) {
        i = read_index & 0xFF;
        while (i != (write_index & 0xFF)) {
          if (*(short *)(0x4d04b6 + i * 8) <= 0) {
            break;
          }
          rasterizer_text_evict_character((int **)(0x4d04b0 + i * 8));
          i = (i + 1) & 0xFF;
        }
        *(unsigned short *)0x4d04a2 = (unsigned short)i;
      }
    }

    /* Evict characters that overlap */
    if (*(short *)0x4d04aa < char_height) {
      cache_top = *(short *)0x4d04a8 + *(short *)0x4d04aa;
      cache_bottom = char_height + (int)*(short *)0x4d04a8;

      read_index = *(unsigned short *)0x4d04a2;
      write_index = *(unsigned short *)0x4d04a4;

      if (read_index != write_index) {
        i = read_index & 0xFF;
        /* Original is a FIFO drain: break at the first slot whose y is
           outside [cache_top, cache_bottom); only the contiguous front
           entries are evicted and read_index advances past them. cache_bottom
           is exclusive. The prior lift instead scanned the whole queue and
           then set read_index = write_index, draining the entire character
           cache whenever a taller glyph arrived, which dropped already-cached
           menu text. */
        do {
          if (*(short *)(0x4d04b6 + i * 8) < (short)cache_top ||
              (short)cache_bottom <= *(short *)(0x4d04b6 + i * 8)) {
            break;
          }
          rasterizer_text_evict_character((int **)(0x4d04b0 + i * 8));
          i = (i + 1) & 0xFF;
        } while (i != (write_index & 0xFF));
        *(unsigned short *)0x4d04a2 = (unsigned short)i;
      }
      /* Original writes _DAT_004d04a8 = CONCAT22(char_height, cursor_y):
         a 32-bit store that sets max_char_height (0x4d04aa, high half) to
         char_height while leaving cursor_y (0x4d04a8, low half) UNCHANGED.
         The prior lift mistranslated this as `cursor_y += char_height`,
         which advanced the pen down a full row each character until a
         glyph was placed at cursor_y=128, overflowing the 128-tall cache
         texture (bitmaps.c:421 "y>=0 && y<bitmap->height"). */
      *(short *)0x4d04aa = char_height;
    }

    /* Handle full cache: evict oldest character. Original compares
       (byte)(write_index + 1) against read_index, so the +1 wraps at 256;
       truncate to unsigned char before comparing or the 255->0 wrap is
       missed and the cache-full case is never detected. */
    if ((unsigned char)(*(unsigned char *)0x4d04a4 + 1) ==
        *(unsigned char *)0x4d04a2) {
      character_slot = (int **)(0x4d04b0 + *(short *)0x4d04a2 * 8);
      rasterizer_text_evict_character(character_slot);
      *(unsigned short *)0x4d04a2 =
        (unsigned short)(unsigned char)(*(unsigned char *)0x4d04a2 + 1);
    }

    /* Allocate slot and copy bitmap to texture */
    i = *(short *)0x4d04a4;
    *(short *)(character + 0xc) = (short)i;
    *(int *)(0x4d04b0 + i * 8) = character;
    *(short *)(0x4d04b4 + i * 8) = *(short *)0x4d04a6;
    *(short *)(0x4d04b6 + i * 8) = *(short *)0x4d04a8;

    pixel_data =
      (unsigned char *)(*(int *)((int)font + 0x94) + *(int *)(character + 0x10));

    for (y = 0; y < char_height; y++) {
      pixel_out = (short *)bitmap_2d_address(
        *(void **)0x4d04ac, *(short *)(0x4d04b4 + i * 8),
        *(short *)(0x4d04b6 + i * 8) + y, 0);
      for (x = 0; x < char_width; x++) {
        *pixel_out = (short)((*pixel_data << 8) | 0xfff);
        pixel_data++;
        pixel_out++;
      }
    }

    FUN_00168b10(*(void **)0x4d04ac);

    *(short *)0x4d04a6 += char_width;
    *(unsigned short *)0x4d04a4 =
      (unsigned short)(unsigned char)(*(unsigned char *)0x4d04a4 + 1);
  } else {
    if (hw_index < 0 || hw_index >= 256) {
      display_assert(
        "font_character->hardware_character_index>=0 && "
        "font_character->hardware_character_index<MAXIMUM_HARDWARE_CHARACTERS",
        "c:\\halo\\SOURCE\\rasterizer\\rasterizer_text.c", 0x27d, 1);
      system_exit(-1);
    }
    if (character != *(int *)(0x4d04b0 + hw_index * 8)) {
      display_assert("font_character==hardware_character_cache.characters[font_"
                     "character->hardware_character_index].character",
                     "c:\\halo\\SOURCE\\rasterizer\\rasterizer_text.c", 0x27e,
                     1);
      system_exit(-1);
    }
  }
}

/* rasterizer_text_draw_cached_char: draw a single cached character quad.
 * Vertex format is 5 floats each (screen x, screen y, texel u, texel v,
 * packed color) — 4 verts = 20 floats — in winding order TL, TR, BR, BL.
 * cache_offset_x/y (param 7/8) are added to the TEXEL coords (the atlas
 * position), not the screen position. */
void rasterizer_text_draw_cached_char(void *arg0, void *font,
                                      void *font_character, unsigned int color,
                                      short x, short y, int cache_offset_x,
                                      int cache_offset_y, short width,
                                      short height)
{
  float quad_verts[20];
  short cache_x;
  short cache_y;
  short tx;
  short ty;

  rasterizer_text_cache_character(font_character, font);

  if (*(short *)((int)font_character + 0xc) != -1) {
    rasterizer_text_get_character_position(
      *(short *)((int)font_character + 0xc), &cache_y, &cache_x);
    tx = (short)(cache_x + (short)cache_offset_x);
    ty = (short)(cache_y + (short)cache_offset_y);

    /* vert0 TL */
    quad_verts[0] = (float)x;
    quad_verts[1] = (float)y;
    quad_verts[2] = (float)tx;
    quad_verts[3] = (float)ty;
    *(unsigned int *)&quad_verts[4] = color;
    /* vert1 TR */
    quad_verts[5] = (float)(x + width);
    quad_verts[6] = (float)y;
    quad_verts[7] = (float)(tx + width);
    quad_verts[8] = (float)ty;
    *(unsigned int *)&quad_verts[9] = color;
    /* vert2 BR */
    quad_verts[10] = (float)(x + width);
    quad_verts[11] = (float)(y + height);
    quad_verts[12] = (float)(tx + width);
    quad_verts[13] = (float)(ty + height);
    *(unsigned int *)&quad_verts[14] = color;
    /* vert3 BL */
    quad_verts[15] = (float)x;
    quad_verts[16] = (float)(y + height);
    quad_verts[17] = (float)tx;
    quad_verts[18] = (float)(ty + height);
    *(unsigned int *)&quad_verts[19] = color;

    FUN_001741d0(quad_verts);
  }
}

/* rasterizer_text_draw_cached_chars: draw character string via hardware cache.
 * This is the callback used by the text drawing system. It draws the glyph
 * twice: pass 1 is the drop shadow (offset +1.0 in x/y, shadow color), pass 2
 * is the glyph itself (no offset, actual color). Vertex format is 5 floats
 * (screen x, screen y, texel u, texel v, packed color) — 4 verts = 20 floats —
 * in winding order TL, TR, BR, BL. cache_offset_x/y (param 7/8) are added to
 * the TEXEL coords, not the screen position; the shadow offset is what moves
 * the screen position. */
void rasterizer_text_draw_cached_chars(void *arg0, void *font,
                                       void *font_character, unsigned int color,
                                       short x, short y, int cache_offset_x,
                                       int cache_offset_y, short width,
                                       short height)
{
  float quad_verts[20];
  short cache_x;
  short cache_y;
  short tx;
  short ty;
  unsigned int draw_color;
  unsigned int shadow_color;
  float x_base;
  float x_right;
  float y_base;
  float y_bottom;
  float shadow_off_x;
  float shadow_off_y;
  int first_pass;
  int was_first;

  rasterizer_text_cache_character(font_character, font);

  if (*(short *)((int)font_character + 0xc) != -1) {
    shadow_off_x = 1.0f;
    shadow_off_y = 1.0f;
    shadow_color = *(unsigned int *)0x4d0cb0;
    if (*(unsigned int *)0x4d0cb0 == 0) {
      shadow_color = color & 0xff000000;
    }
    x_base = (float)x;
    x_right = (float)(width + x);
    y_base = (float)y;
    y_bottom = (float)(height + y);
    first_pass = 1;

    while (1) {
      rasterizer_text_get_character_position(
        *(short *)((int)font_character + 0xc), &cache_y, &cache_x);
      was_first = first_pass;
      tx = (short)(cache_x + (short)cache_offset_x);
      ty = (short)(cache_y + (short)cache_offset_y);
      draw_color = shadow_color;
      if (first_pass == 0) {
        draw_color = color;
      }

      /* vert0 TL */
      quad_verts[0] = x_base + shadow_off_x;
      quad_verts[1] = y_base + shadow_off_y;
      quad_verts[2] = (float)tx;
      quad_verts[3] = (float)ty;
      *(unsigned int *)&quad_verts[4] = draw_color;
      /* vert1 TR */
      quad_verts[5] = x_right + shadow_off_x;
      quad_verts[6] = y_base + shadow_off_y;
      quad_verts[7] = (float)(tx + width);
      quad_verts[8] = (float)ty;
      *(unsigned int *)&quad_verts[9] = draw_color;
      /* vert2 BR */
      quad_verts[10] = x_right + shadow_off_x;
      quad_verts[11] = y_bottom + shadow_off_y;
      quad_verts[12] = (float)(tx + width);
      quad_verts[13] = (float)(ty + height);
      *(unsigned int *)&quad_verts[14] = draw_color;
      /* vert3 BL */
      quad_verts[15] = x_base + shadow_off_x;
      quad_verts[16] = y_bottom + shadow_off_y;
      quad_verts[17] = (float)tx;
      quad_verts[18] = (float)(ty + height);
      *(unsigned int *)&quad_verts[19] = draw_color;

      FUN_001741d0(quad_verts);

      if (was_first == 0) {
        break;
      }
      first_pass = 0;
      shadow_off_x = 0.0f;
      shadow_off_y = 0.0f;
    }
  }
}

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

/* rasterizer_transparent_geometry_new: allocate transparent geometry buffers
 * and init vertex cache (0x184260) */
int rasterizer_transparent_geometry_new(void)
{
  int success;

  *(void **)0x4d0cec = debug_malloc(
    0xf000, 0,
    "c:\\halo\\SOURCE\\rasterizer\\rasterizer_transparent_geometry.c", 0x29);
  *(void **)0x4d0cfc = debug_malloc(
    0x300, 0, "c:\\halo\\SOURCE\\rasterizer\\rasterizer_transparent_geometry.c",
    0x2b);
  *(void **)0x4d0cf0 = debug_malloc(
    0x1400, 0,
    "c:\\halo\\SOURCE\\rasterizer\\rasterizer_transparent_geometry.c", 0x2e);
  *(int *)0x4d0cf8 = 0;
  *(int *)0x4d0cf4 = 0;
  if (*(int *)0x4d0cec == 0 || *(int *)0x4d0cfc == 0 || *(int *)0x4d0cf0 == 0) {
    error(2, "### ERROR failed to allocate transparent geometry buffer");
  } else {
    success = FUN_00174bd0();
    if (success != 0) {
      return 1;
    }
  }
  return 0;
}

/* rasterizer_transparent_geometry_begin: reset group counts and stats for new
 * frame (0x184300) */
void rasterizer_transparent_geometry_begin(void)
{
  *(int *)0x4d0cf4 = 0;
  *(short *)0x4d0d00 = 0;
  csmemset((void *)0x4d0cbc, 0, 0x30);
  *(int *)0x4d0cf8 = 0;
}

/* rasterizer_transparent_geometry_group_new: allocate next transparent geometry
 * group slot (0x184330) */
void *rasterizer_transparent_geometry_group_new(void)
{
  void *group;

  group = (void *)0;
  if (*(int *)0x4d0cf4 < 0x180) {
    group = (void *)(*(int *)0x4d0cf4 * 0xa0 + *(int *)0x4d0cec);
    *(int *)((char *)group + 0x90) = *(int *)0x4d0cf4;
    *(int *)0x4d0cf4 = *(int *)0x4d0cf4 + 1;
  }
  return group;
}

/* rasterizer_secondary_geometry_group_new: allocate next secondary geometry
 * group slot (0x184360) */
void *rasterizer_secondary_geometry_group_new(void)
{
  void *group;

  group = (void *)0;
  if (*(int *)0x4d0cf8 < 0x20) {
    group = (void *)(*(int *)0x4d0cf8 * 0xa0 + *(int *)0x4d0cf0);
    *(int *)((char *)group + 0x90) = *(int *)0x4d0cf8;
    *(int *)0x4d0cf8 = *(int *)0x4d0cf8 + 1;
  }
  return group;
}

/* rasterizer_secondary_geometry_groups_get: return secondary groups buffer;
 * optionally write count (0x184390) */
void *rasterizer_secondary_geometry_groups_get(short *out_count)
{
  if (out_count != (short *)0) {
    *out_count = (short)*(int *)0x4d0cf8;
  }
  return *(void **)0x4d0cf0;
}

/* rasterizer_transparent_geometry_next_group: return next sorted group after
 * given group (0x1843b0) */
void *rasterizer_transparent_geometry_next_group(void *group)
{
  short next_index;
  short sorted_index;

  if (group != (void *)0) {
    sorted_index = *(short *)((char *)group + 0x90);
    next_index = (short)(sorted_index + 1);
    if (*(int *)((char *)group + 0x90) < 0 ||
        *(int *)0x4d0cf4 <= *(int *)((char *)group + 0x90)) {
      display_assert(
        "group->sorted_index>=0 && "
        "group->sorted_index<transparent_geometry_group_count",
        "c:\\halo\\SOURCE\\rasterizer\\rasterizer_transparent_geometry.c", 0x89,
        1);
      system_exit(-1);
    }
    if (next_index < *(int *)0x4d0cf4) {
      if (next_index < 0) {
        display_assert(
          "next_group_sorted_index>=0",
          "c:\\halo\\SOURCE\\rasterizer\\rasterizer_transparent_geometry.c",
          0x8d, 1);
        system_exit(-1);
      }
      return (void *)(*(short *)(*(int *)0x4d0cfc + next_index * 2) * 0xa0 +
                      *(int *)0x4d0cec);
    }
  }
  return (void *)0;
}

/* rasterizer_transparent_geometry_group_get: return group by presorted index
 * (0x184460) */
void *rasterizer_transparent_geometry_group_get(short group_presorted_index)
{
  if (group_presorted_index < 0 || *(int *)0x4d0cf4 <= group_presorted_index) {
    display_assert(
      "group_presorted_index>=0 && "
      "group_presorted_index<transparent_geometry_group_count",
      "c:\\halo\\SOURCE\\rasterizer\\rasterizer_transparent_geometry.c", 0xbc,
      1);
    system_exit(-1);
  }
  return (void *)(group_presorted_index * 0xa0 + *(int *)0x4d0cec);
}

/* rasterizer_transparent_geometry_group_to_presorted_index: convert group
 * pointer to presorted index (0x1844b0) */
short rasterizer_transparent_geometry_group_to_presorted_index(
  unsigned int group)
{
  unsigned int base;
  int count;
  short index;
  unsigned int offset;
  unsigned int remainder;

  base = *(unsigned int *)0x4d0cec;
  count = *(int *)0x4d0cf4;
  index = -1;
  if (group >= base && group < base + (unsigned int)(count * 0xa0)) {
    index = (short)((int)(group - base) / 0xa0);
    if (index < 0 || count <= index) {
      display_assert(
        "group_presorted_index>=0 && "
        "group_presorted_index<transparent_geometry_group_count",
        "c:\\halo\\SOURCE\\rasterizer\\rasterizer_transparent_geometry.c", 0xcb,
        1);
      system_exit(-1);
    }
    offset = group - base;
    remainder = offset % 0xa0;
    if (remainder != 0) {
      display_assert(
        "((unsigned long)group-(unsigned "
        "long)transparent_geometry_groups)%sizeof(struct "
        "transparent_geometry_group)==0",
        "c:\\halo\\SOURCE\\rasterizer\\rasterizer_transparent_geometry.c", 0xcc,
        1);
      system_exit(-1);
    }
  }
  return index;
}
/* --- rasterizer_text.obj batch drafts (2026-07-26) --- */

/* 0x180770 */
unsigned char FUN_00180770(float alpha)
{
  int eax = 0;

  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 1 -> jne 0x180794 */
  /* relift: relift: fcomp dword ptr [0x2533c8] */
  display_assert((char *)0x002b00a0, (char *)0x002afe38, 42, 0);
  system_exit(0);
  return 0;

  (void)eax;
}

/* 0x180820 */
void compress_real_to_int16(void)
{
  int eax = 0;

  /* relift: relift: fcomp dword ptr [0x255e94] */
  /* test (char)eax, 1 -> jne 0x180844 */
  /* relift: relift: fcomp dword ptr [0x2533c8] */
  display_assert((char *)0x002b00b8, (char *)0x002afe38, 55, 0);
  system_exit(0);
  floor(0.0f);

  (void)eax;
}

/* 0x180890 */
short FUN_00180890(float f)
{
  int eax = 0;

  /* relift: relift: fcomp dword ptr [0x255e94] */
  /* relift: relift: fld dword ptr [0x255e94] */
  /* relift: relift: fcomp dword ptr [0x2533c8] */
  /* test (char)eax, 0x41 -> jne 0x1808c4 */
  /* relift: relift: fld dword ptr [0x2533c8] */
  floor(0.0f);
  return 0;

  (void)eax;
}

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

/* 0x181180 */
void FUN_00181180(void)
{
  int eax = 0;
  int ecx = 0;
  int esi = 0;
  int ebp = 0;

  FUN_0016f910(24);
  /* relift: relift: mov (char)eax, byte ptr [0x3256d7] */
  /* test (char)eax, (char)eax -> je 0x181293 */
  /* relift: relift: mov (int16_t)eax, word ptr [0x46e008] */
  /* cmp (int16_t)eax, 1 -> jg 0x181293 */
  /* relift: cmp word ptr [0x31fa98], 1 -> jg 0x181293 */
  /* relift: cmp word ptr [ebp - 4], 0 -> jl 0x1811db */
  /* cmp esi, eax -> jl 0x1811f8 */
  display_assert((char *)0x002b0174, (char *)0x002b01b4, 67, 0);
  system_exit(0);
  FUN_00181060((void *)0);
  /* test eax, eax -> jle 0x18123a */
  FUN_0017d040();
  /* cmp eax, 0xff -> jge 0x18123f */
  /* test (char)ecx, (char)ecx -> jne 0x181242 */
  /* cmp (char)ecx, (char)eax -> jbe 0x18125e */
  /* cmp esi, eax -> jl 0x1811d0 */
  /* mem[0x004d0480] = 0 */
  FUN_0016fa40(24);

  (void)eax;
  (void)ecx;
  (void)esi;
  (void)ebp;
}

/* 0x1812c0 */
void FUN_001812c0(void)
{
  int eax = 0;
  int ecx = 0;
  int esi = 0;

  /* test esi, esi -> jne 0x1812ef */
  display_assert((char *)0x0029f510, (char *)0x002b01b4, 240, 0);
  system_exit(0);
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 1 -> jne 0x18130f */
  /* relift: relift: fcomp dword ptr [0x2533c8] */
  display_assert((char *)0x002b039c, (char *)0x002b01b4, 241, 0);
  system_exit(0);
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 1 -> jne 0x18134f */
  /* relift: relift: fcomp dword ptr [0x2533c8] */
  display_assert((char *)0x002b035c, (char *)0x002b01b4, 242, 0);
  system_exit(0);
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 1 -> jne 0x18138f */
  /* relift: relift: fcomp dword ptr [0x2533c8] */
  display_assert((char *)0x002b031c, (char *)0x002b01b4, 243, 0);
  system_exit(0);
  /* cmp ecx, 0x80 -> jge 0x1813f3 */
  /* mem[0x005a37e0] = ecx */
  /* mem[0x005a5548] = ecx */
  error(0, (char *)0x002b02ec);

  (void)eax;
  (void)ecx;
  (void)esi;
}

/* 0x181420 */
float FUN_00181420(void *lens_flare_params, short rotation_fn)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int edi = 0;

  display_assert((char *)0x002b02d4, (char *)0x002b01b4, 118, 0);
  system_exit(0);
  FUN_0017ffc0((float *)(uintptr_t)ecx, eax);
  cross_product3d((float *)(uintptr_t)ecx, (void *)0x005a5c64, (float *)(uintptr_t)eax);
  cross_product3d((float *)(uintptr_t)ecx, (float *)(uintptr_t)eax, (float *)(uintptr_t)edx);
  cross_product3d((float *)(uintptr_t)eax, (void *)0x005a5c64, (float *)(uintptr_t)edx);
  cross_product3d((float *)(uintptr_t)eax, (float *)(uintptr_t)edx, (float *)(uintptr_t)ecx);
  /* relift: relift: fld dword ptr [0x5a5c6c] */
  /* relift: relift: fld dword ptr [0x5a5c68] */
  /* relift: relift: fld dword ptr [0x5a5c64] */
  /* relift: relift: fld dword ptr [0x5a5c84] */
  /* relift: relift: fld dword ptr [0x5a5c80] */
  /* relift: relift: fld dword ptr [0x5a5c7c] */
  display_assert((char *)0x002b03dc, (char *)0x002b01b4, 151, 0);
  system_exit(0);
  /* test (int16_t)edi, (int16_t)edi -> je 0x181646 */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  return 0;

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)edi;
}

/* 0x182610 */
void FUN_00182610(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x182840 */
void rasterizer_xbox_bitmap_swizzle2d_byte(void)
{
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  display_assert((char *)0x002b08ac, (char *)0x002b087c, 147, 0);
  system_exit(0);
  /* relift: cmp dword ptr [ebp + 0xc], edi -> jne 0x18289c */
  display_assert((char *)0x002b07dc, (char *)0x002b087c, 148, 0);
  system_exit(0);
  FUN_00182610();
  /* test (int16_t)eax, (int16_t)eax -> jle 0x182908 */
  /* test (int16_t)esi, (int16_t)esi -> jle 0x1828f9 */

  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x182910 */
void rasterizer_xbox_bitmap_swizzle2d_word(void)
{
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  display_assert((char *)0x002b08ac, (char *)0x002b087c, 176, 0);
  system_exit(0);
  /* relift: cmp dword ptr [ebp + 0xc], edi -> jne 0x18296c */
  display_assert((char *)0x002b07dc, (char *)0x002b087c, 177, 0);
  system_exit(0);
  FUN_00182610();
  /* test (int16_t)eax, (int16_t)eax -> jle 0x1829da */
  /* test (int16_t)esi, (int16_t)esi -> jle 0x1829cb */

  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x1829f0 */
void rasterizer_xbox_bitmap_swizzle2d_long(void)
{
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  display_assert((char *)0x002b08ac, (char *)0x002b087c, 205, 0);
  system_exit(0);
  /* relift: cmp dword ptr [ebp + 0xc], edi -> jne 0x182a4c */
  display_assert((char *)0x002b07dc, (char *)0x002b087c, 206, 0);
  system_exit(0);
  FUN_00182610();
  /* test (int16_t)eax, (int16_t)eax -> jle 0x182ab8 */
  /* test (int16_t)esi, (int16_t)esi -> jle 0x182aa9 */

  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x182ac0 */
void rasterizer_xbox_bitmap_swizzle3d_byte(void)
{
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  display_assert((char *)0x002b08ac, (char *)0x002b087c, 235, 0);
  system_exit(0);
  /* relift: cmp dword ptr [ebp + 0xc], edi -> jne 0x182b1f */
  display_assert((char *)0x002b07dc, (char *)0x002b087c, 236, 0);
  system_exit(0);
  FUN_00182610();
  /* test (int16_t)eax, (int16_t)eax -> jle 0x182bc8 */
  /* test (int16_t)eax, (int16_t)eax -> jle 0x182bb9 */
  /* test (int16_t)esi, (int16_t)esi -> jle 0x182ba0 */

  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x182bd0 */
void rasterizer_xbox_bitmap_swizzle3d_word(void)
{
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  display_assert((char *)0x002b08ac, (char *)0x002b087c, 270, 0);
  system_exit(0);
  /* relift: cmp dword ptr [ebp + 0xc], edi -> jne 0x182c2f */
  display_assert((char *)0x002b07dc, (char *)0x002b087c, 271, 0);
  system_exit(0);
  FUN_00182610();
  /* test (int16_t)eax, (int16_t)eax -> jle 0x182cda */
  /* test (int16_t)eax, (int16_t)eax -> jle 0x182ccb */
  /* test (int16_t)esi, (int16_t)esi -> jle 0x182cb2 */

  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x182cf0 */
void rasterizer_xbox_bitmap_swizzle3d_long(void)
{
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  display_assert((char *)0x002b08ac, (char *)0x002b087c, 305, 0);
  system_exit(0);
  /* relift: cmp dword ptr [ebp + 0xc], edi -> jne 0x182d4f */
  display_assert((char *)0x002b07dc, (char *)0x002b087c, 306, 0);
  system_exit(0);
  FUN_00182610();
  /* test (int16_t)eax, (int16_t)eax -> jle 0x182df8 */
  /* test (int16_t)eax, (int16_t)eax -> jle 0x182de9 */
  /* test (int16_t)esi, (int16_t)esi -> jle 0x182dd0 */

  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x182e00 */
void FUN_00182e00(int param_1)
{
  int eax = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* test edi, edi -> jne 0x182e2e */
  display_assert((char *)0x00263768, (char *)0x002b087c, 334, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x182e55 */
  display_assert((char *)0x00264c30, (char *)0x002b087c, 335, 0);
  system_exit(0);
  /* test (char)eax, 0x12 -> jne 0x183112 */
  /* test (char)eax, 1 -> jne 0x182e85 */
  display_assert((char *)0x002a2760, (char *)0x002b087c, 345, 0);
  system_exit(0);
  bitmap_mipmap_get_pixel_data_size((void *)(uintptr_t)edi, 0);
  bitmap_mipmap_address((void *)(uintptr_t)edi, 0);
  debug_malloc(esi, 0, (char *)0x002b087c, 351);
  bitmap_mipmap_width((void *)(uintptr_t)edi, 0);
  bitmap_mipmap_get_height((void *)(uintptr_t)edi, 0);
  bitmap_mipmap_get_depth((void *)(uintptr_t)edi, 0);
  /* test eax, eax -> je 0x1830f0 */
  bitmap_format_bits_per_pixel(0);
  FUN_00182610();
  display_assert((char *)0x00261d30, (char *)0x002b087c, 436, 0);
  system_exit(0);
  display_assert((char *)0x002b08ec, (char *)0x002b087c, 425, 0);
  system_exit(0);
  rasterizer_xbox_bitmap_swizzle2d_long();
  rasterizer_xbox_bitmap_swizzle2d_word();
  rasterizer_xbox_bitmap_swizzle2d_byte();
  display_assert((char *)0x002b08ec, (char *)0x002b087c, 399, 0);
  system_exit(0);
  rasterizer_xbox_bitmap_swizzle3d_long();
  rasterizer_xbox_bitmap_swizzle3d_word();
  rasterizer_xbox_bitmap_swizzle3d_byte();
  rasterizer_xbox_bitmap_swizzle2d_long();
  rasterizer_xbox_bitmap_swizzle2d_word();
  rasterizer_xbox_bitmap_swizzle2d_byte();
  csmemcpy((void *)(uintptr_t)eax, (void *)(uintptr_t)esi, edx);
  debug_free((void *)(uintptr_t)esi, (char *)0x002b087c, 440);
  error(0, (char *)0x002b08b0);

  (void)eax;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x183120 */
int16_t FUN_00183120(void *bitmap)
{
  int eax = 0;
  int ebx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  bitmap_verify((void *)(uintptr_t)esi, 0);
  /* test (char)eax, (char)eax -> jne 0x183159 */
  display_assert((char *)0x00264da0, (char *)0x002b087c, 459, 0);
  system_exit(0);
  /* test (char)eax, 1 -> je 0x183281 */
  /* test (char)eax, 0x10 -> jne 0x183281 */
  /* test (char)eax, 2 -> je 0x183201 */
  /* cmp eax, ebx -> jg 0x1831a9 */
  FUN_00108db0(eax);
  /* cmp (int16_t)edi, (int16_t)eax -> jle 0x183281 */
  /* cmp eax, ebx -> jg 0x1831f3 */
  FUN_00108db0(eax);
  /* cmp edx, edi -> jle 0x183220 */
  FUN_00108db0(eax);
  /* cmp (int16_t)edi, (int16_t)eax -> jle 0x183281 */
  /* cmp edx, edi -> jle 0x183268 */
  FUN_00108db0(eax);
  FUN_00108db0(eax);
  return 0;

  (void)eax;
  (void)ebx;
  (void)edx;
  (void)esi;
  (void)edi;
}
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

/* orphan 0x181670 */
void FUN_00181670(int *params)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;

  /* test edi, edi -> jne 0x18169b */
  display_assert((char *)0x0029f510, (char *)0x002b01b4, 266, 0);
  system_exit(0);
  /* relift: cmp dword ptr [edi], 0 -> jne 0x1816c0 */
  display_assert((char *)0x002b05d4, (char *)0x002b01b4, 267, 0);
  system_exit(0);
  /* relift: cmp (int16_t)eax, word ptr [0x5a5bc2] -> je 0x1816f2 */
  display_assert((char *)0x002b0568, (char *)0x002b01b4, 268, 0);
  system_exit(0);
  /* relift: relift: mov (char)eax, byte ptr [0x3256d7] */
  /* test (char)eax, (char)eax -> je 0x1818fa */
  /* relift: relift: mov (int16_t)eax, word ptr [0x46e008] */
  /* cmp (int16_t)eax, 1 -> jg 0x1818fa */
  /* relift: cmp word ptr [0x31fa98], 1 -> jg 0x1818fa */
  /* relift: cmp word ptr [0x5a5bc0], 0 -> jne 0x1818fa */
  /* cmp ecx, 0x400 -> jge 0x1818db */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* relift: relift: fld dword ptr [0x5a5bdc] */
  /* relift: relift: fld dword ptr [0x5a5bd8] */
  /* relift: relift: fld dword ptr [0x5a5bd4] */
  /* relift: test dword ptr [edi + 0x18], 0xff000000 -> jbe 0x1818fa */
  /* mem[0x004d0480] = ecx */
  FUN_00181020(0);
  csmemcpy((void *)(uintptr_t)ebx, (void *)(uintptr_t)edi, 40);
  /* relift: cmp word ptr [edi + 0x1c], -1 -> jne 0x18186e */
  /* cmp (int16_t)eax, 0xffff -> jne 0x181822 */
  /* test (int16_t)edi, (int16_t)edi -> jl 0x1817fd */
  /* cmp (int16_t)edi, 8 -> jl 0x1818c6 */
  display_assert((char *)0x002b0508, (char *)0x002b01b4, 310, 0);
  system_exit(0);
  /* cmp esi, 0x10000 -> jl 0x181858 */
  display_assert((char *)0x002b04a0, (char *)0x002b01b4, 321, 0);
  system_exit(0);
  /* test (int16_t)eax, (int16_t)eax -> jl 0x181886 */
  /* cmp (int16_t)eax, 0x380 -> jl 0x1818a6 */
  display_assert((char *)0x002b0450, (char *)0x002b01b4, 338, 0);
  system_exit(0);
  /* relift: cmp (int16_t)eax, word ptr [esi] -> je 0x1818c6 */
  csmemset((void *)(uintptr_t)ecx, 0, 32);
  /* relift: relift: mov (char)eax, byte ptr [0x4d0484] */
  /* test (char)eax, (char)eax -> jne 0x1818fa */
  error(0, (char *)0x002b0418);
  /* relift: relift: mov byte ptr [0x4d0484], 1 */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)esi;
  (void)edi;
}
