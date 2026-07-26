/* Offset a 2D rectangle by (dx, dy) (0x108a70).
 * rect layout: {top, left, bottom, right} as int16_t[4]. */
void rect2d_offset(int16_t *rect, int16_t dx, int16_t dy)
{
  rect[1] += dx;
  rect[3] += dx;
  rect[0] += dy;
  rect[2] += dy;
}

/* Compute floor(log2(value)) (0x108db0).
 * Returns 0 for value <= 1. */
int16_t FUN_00108db0(unsigned int value)
{
  int result = 0;
  if (value != 0) {
    while (value != 1) {
      value >>= 1;
      result++;
    }
  }
  return (int16_t)result;
}
/* --- rectangles.obj batch drafts (2026-07-26) --- */

/* 0x107c30 */
void FUN_00107c30(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* test eax, eax -> jne 0x107c5a */
  display_assert((char *)0x0028ba70, (char *)0x0028be44, 2284, 0);
  system_exit(0);
  /* test edi, edi -> jne 0x107c84 */
  display_assert((char *)0x0028c050, (char *)0x0028be44, 2285, 0);
  system_exit(0);
  /* test esi, esi -> jne 0x107cab */
  display_assert((char *)0x0028c048, (char *)0x0028be44, 2286, 0);
  system_exit(0);
  /* test ebx, ebx -> jne 0x107cd2 */
  display_assert((char *)0x0028c03c, (char *)0x0028be44, 2287, 0);
  system_exit(0);
  FUN_00106f50(esi, (float *)(uintptr_t)eax, edx, (char *)(uintptr_t)edi, ecx, (char *)(uintptr_t)esi, eax, (char *)(uintptr_t)ebx);
  /* test (char)eax, (char)eax -> je 0x107d34 */
  /* test (int16_t)esi, (int16_t)esi -> jle 0x107d2d */
  FUN_00107520();
  /* test (char)eax, (char)eax -> je 0x107d34 */
  /* cmp (int16_t)edi, (int16_t)esi -> jl 0x107d00 */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x107d40 */
void FUN_00107d40(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* FUN_00107db0 (0x107db0) — XBE naked draft (batch 243). */
#if defined(__clang__)


__attribute__((naked, noinline))
void FUN_00107db0(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $8, %%esp\n\t"
      "pushl %%ebx\n\t"
      "movw 0x20(%%ebp), %%bx\n\t"
      "pushl %%esi\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "testw %%bx, %%bx\n\t"
      "pushl %%edi\n\t"
      "movl $0xff7fffff, -0x4(%%ebp)\n\t"
      "movl $0x7f7fffff, -0x8(%%ebp)\n\t"
      "jle .LFUN_00107db0_7\n\t"
      "movl 0x2c(%%ebp), %%edx\n\t"
      "movl 0x28(%%ebp), %%esi\n\t"
      "movl 0x24(%%ebp), %%edi\n\t"
      "nop\n\t"
      ".LFUN_00107db0_1:\n\t"
      "movswl %%cx, %%eax\n\t"
      "imull $0x1c, %%eax, %%eax\n\t"
      "addl %%edi, %%eax\n\t"
      "cmpb $0, (%%eax)\n\t"
      "je .LFUN_00107db0_6\n\t"
      "flds 0xc(%%eax)\n\t"
      "fmuls 0x8(%%esi)\n\t"
      "flds 0x8(%%eax)\n\t"
      "fmuls 0x4(%%esi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds 0x4(%%eax)\n\t"
      "fmuls (%%esi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fsubs 0x10(%%eax)\n\t"
      "flds 0xc(%%eax)\n\t"
      "fmuls 0x8(%%edx)\n\t"
      "flds 0x8(%%eax)\n\t"
      "fmuls 0x4(%%edx)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds 0x4(%%eax)\n\t"
      "fmuls (%%edx)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fsts 0x20(%%ebp)\n\t"
      "fabs\n\t"
      "fcompl 0x2533d0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .LFUN_00107db0_4\n\t"
      "fdivs 0x20(%%ebp)\n\t"
      "fchs\n\t"
      "flds 0x20(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00107db0_2\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fcomp %%st(1)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00107db0_3\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fcomps -0x8(%%ebp)\n\t"
      "jmp .LFUN_00107db0_5\n\t"
      ".LFUN_00107db0_2:\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fcomp %%st(1)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00107db0_3\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fcomps -0x8(%%ebp)\n\t"
      "jmp .LFUN_00107db0_5\n\t"
      ".LFUN_00107db0_3:\n\t"
      "fstp %%st(0)\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fcomps -0x8(%%ebp)\n\t"
      "jmp .LFUN_00107db0_5\n\t"
      ".LFUN_00107db0_4:\n\t"
      "fcomps 0x31fb40\n\t"
      ".LFUN_00107db0_5:\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .LFUN_00107db0_10\n\t"
      ".LFUN_00107db0_6:\n\t"
      "incl %%ecx\n\t"
      "cmpw %%bx, %%cx\n\t"
      "jl .LFUN_00107db0_1\n\t"
      ".LFUN_00107db0_7:\n\t"
      "movl 0x30(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_00107db0_8\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movl %%ecx, (%%eax)\n\t"
      ".LFUN_00107db0_8:\n\t"
      "movl 0x34(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_00107db0_9\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "movl %%edx, (%%eax)\n\t"
      ".LFUN_00107db0_9:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00107db0_10:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "FUN_00107db0: clang naked draft required"
#endif


/* 0x107ec0 */
void get_edge_vertex(void)
{
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  /* test edi, edi -> jne 0x107f13 */
  display_assert((char *)0x0028be3c, (char *)0x0028be44, 269, 0);
  system_exit(0);
  /* test (int16_t)ecx, (int16_t)ecx -> jl 0x107f21 */
  /* relift: cmp (int16_t)ecx, word ptr [edi + 0xc] -> jl 0x107f44 */
  display_assert((char *)0x0028c2ac, (char *)0x0028be44, 270, 0);
  system_exit(0);
  /* test (int16_t)ebx, (int16_t)ebx -> jl 0x107f4f */
  /* relift: cmp (int16_t)ebx, word ptr [edi + 0xc] -> jl 0x107f72 */
  display_assert((char *)0x0028c284, (char *)0x0028be44, 271, 0);
  system_exit(0);
  /* relift: cmp (int16_t)ebx, word ptr [ebp - 8] -> jne 0x107f9b */
  display_assert((char *)0x0028c278, (char *)0x0028be44, 272, 0);
  system_exit(0);
  /* test (int16_t)edx, (int16_t)edx -> jne 0x107fb8 */
  /* relift: cmp (int16_t)edx, word ptr [edi] -> je 0x10804b */
  /* relift: cmp word ptr [edi], (int16_t)esi -> jle 0x108024 */
  calculate_vertex(0, 0, 0, 0, (void *)0, 0);
  /* relift: cmp (int16_t)esi, word ptr [edi] -> jl 0x107ff0 */
  /* test (char)ecx, (char)ecx -> je 0x108041 */

  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x108060 */
short FUN_00108060(int16_t count, void *records, int a3, uint16_t *scratch, int max_count, uint16_t *out_list, uint32_t seed)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  FUN_001d90e0();
  display_assert((char *)0x0028c330, (char *)0x0028be44, 1016, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x1080c8 */
  display_assert((char *)0x0026856c, (char *)0x0028be44, 1017, 0);
  system_exit(0);
  /* test (int16_t)esi, (int16_t)esi -> jne 0x1080f0 */
  display_assert((char *)0x0028c328, (char *)0x0028be44, 1018, 0);
  system_exit(0);
  /* test ebx, ebx -> jne 0x108114 */
  display_assert((char *)0x0028c324, (char *)0x0028be44, 1019, 0);
  system_exit(0);
  /* test (int16_t)edi, (int16_t)edi -> jne 0x108139 */
  display_assert((char *)0x0028c31c, (char *)0x0028be44, 1020, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x108160 */
  display_assert((char *)0x0025f120, (char *)0x0028be44, 1021, 0);
  system_exit(0);
  /* relift: cmp dword ptr [ebp + 0xc], eax -> je 0x10816c */
  /* cmp ebx, eax -> jne 0x10818c */
  display_assert((char *)0x0028c304, (char *)0x0028be44, 1022, 0);
  system_exit(0);
  /* test (int16_t)esi, (int16_t)esi -> jg 0x1081a0 */
  /* test (int16_t)edi, (int16_t)edi -> jle 0x108193 */
  /* cmp eax, edx -> jne 0x1081c0 */
  plane2d_from_points((float *)(uintptr_t)ecx, (float *)(uintptr_t)eax, (float *)(uintptr_t)edx);
  /* test eax, eax -> je 0x10821d */
  convex_polygon2d_clip_to_plane(edi, (float *)(uintptr_t)edx, (float *)(uintptr_t)ecx, eax, (float *)(uintptr_t)esi, (void *)0, (void *)0, 0.0f);
  /* cmp (int16_t)edi, -1 -> jne 0x108257 */
  /* relift: cmp (int16_t)edi, word ptr [ebp + 0x18] -> jle 0x108243 */
  display_assert((char *)0x0028c2d4, (char *)0x0028be44, 1037, 0);
  system_exit(0);
  csmemcpy((void *)(uintptr_t)esi, (void *)(uintptr_t)ecx, eax);
  return 0;

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x108270 */
void get_face_vertex(void)
{
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int edi = 0;

  /* test (int16_t)eax, (int16_t)eax -> jl 0x108297 */
  /* relift: cmp (int16_t)eax, word ptr [edi + 0xc] -> jle 0x1082b7 */
  display_assert((char *)0x0028c3a0, (char *)0x0028be44, 222, 0);
  system_exit(0);
  /* test (int16_t)eax, (int16_t)eax -> jl 0x1082c5 */
  /* relift: cmp (int16_t)eax, word ptr [edi + 0xc] -> jle 0x1082e8 */
  display_assert((char *)0x0028c378, (char *)0x0028be44, 223, 0);
  system_exit(0);
  /* test (int16_t)edx, (int16_t)edx -> jl 0x1082f6 */
  /* relift: cmp (int16_t)edx, word ptr [edi + 0xc] -> jle 0x10831c */
  display_assert((char *)0x0028c350, (char *)0x0028be44, 224, 0);
  system_exit(0);
  /* test (int16_t)ecx, (int16_t)ecx -> jne 0x108356 */
  get_edge_vertex();
  /* relift: cmp (int16_t)ebx, word ptr [edi] -> jne 0x108378 */
  get_edge_vertex();
  get_edge_vertex();
  get_edge_vertex();
  get_edge_vertex();
  calculate_vertex(0, 0, 0, 0, (void *)0, 0);

  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)edi;
}

/* subdivide_triangle (0x108400) — XBE naked draft (batch 242). */
#if defined(__clang__)
static void (*const b108400_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b108400_exitfn)(int) = system_exit;
static void * (*const b108400_c8ee60)(uint32_t size, bool zero, const char *file, int line) = debug_malloc;
static void (*const b108400_c108270)(void) = get_face_vertex;
static void (*const b108400_c8ef70)(void *ptr, const char *file, int line) = debug_free;

__attribute__((naked, noinline))
void subdivide_triangle(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x18, %%esp\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw (%%esi), %%ax\n\t"
      "incw %%ax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "movl %%eax, %%edi\n\t"
      "imull %%eax, %%edi\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lsubdivide_triangle_1\n\t"
      "pushl $1\n\t"
      "pushl $0x92\n\t"
      "pushl $0x28be44\n\t"
      "pushl $0x28c5d8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lsubdivide_triangle_1:\n\t"
      "movl 0x18(%%ebp), %%ebx\n\t"
      "testl %%ebx, %%ebx\n\t"
      "jne .Lsubdivide_triangle_2\n\t"
      "pushl $1\n\t"
      "pushl $0x93\n\t"
      "pushl $0x28be44\n\t"
      "pushl $0x28c5b4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lsubdivide_triangle_2:\n\t"
      "movl 0x1c(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lsubdivide_triangle_3\n\t"
      "pushl $1\n\t"
      "pushl $0x94\n\t"
      "pushl $0x28be44\n\t"
      "pushl $0x28c598\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lsubdivide_triangle_3:\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "testw %%ax, %%ax\n\t"
      "jl .Lsubdivide_triangle_4\n\t"
      "cmpw 0xc(%%esi), %%ax\n\t"
      "jl .Lsubdivide_triangle_5\n\t"
      ".Lsubdivide_triangle_4:\n\t"
      "pushl $1\n\t"
      "pushl $0x95\n\t"
      "pushl $0x28be44\n\t"
      "pushl $0x28c570\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lsubdivide_triangle_5:\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "testw %%ax, %%ax\n\t"
      "jl .Lsubdivide_triangle_6\n\t"
      "cmpw 0xc(%%esi), %%ax\n\t"
      "jl .Lsubdivide_triangle_7\n\t"
      ".Lsubdivide_triangle_6:\n\t"
      "pushl $1\n\t"
      "pushl $0x96\n\t"
      "pushl $0x28be44\n\t"
      "pushl $0x28c548\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lsubdivide_triangle_7:\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "testw %%ax, %%ax\n\t"
      "jl .Lsubdivide_triangle_8\n\t"
      "cmpw 0xc(%%esi), %%ax\n\t"
      "jl .Lsubdivide_triangle_9\n\t"
      ".Lsubdivide_triangle_8:\n\t"
      "pushl $1\n\t"
      "pushl $0x97\n\t"
      "pushl $0x28be44\n\t"
      "pushl $0x28c520\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lsubdivide_triangle_9:\n\t"
      "movswl 0xe(%%esi), %%eax\n\t"
      "movswl (%%ebx), %%ecx\n\t"
      "shll $2, %%eax\n\t"
      "cmpl %%eax, %%ecx\n\t"
      "jl .Lsubdivide_triangle_10\n\t"
      "pushl $1\n\t"
      "pushl $0x98\n\t"
      "pushl $0x28be44\n\t"
      "pushl $0x28c4b8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lsubdivide_triangle_10:\n\t"
      "pushl $0x9a\n\t"
      "movswl %%di, %%edx\n\t"
      "pushl $0x28be44\n\t"
      "shll $1, %%edx\n\t"
      "pushl $0\n\t"
      "pushl %%edx\n\t"
      "call *%[c8ee60]\n\t"
      "movl %%eax, %%edx\n\t"
      "addl $0x10, %%esp\n\t"
      "testl %%edx, %%edx\n\t"
      "movl %%edx, -0x8(%%ebp)\n\t"
      "je .Lsubdivide_triangle_27\n\t"
      "testw %%di, %%di\n\t"
      "jle .Lsubdivide_triangle_11\n\t"
      "movzwl %%di, %%ecx\n\t"
      "orl $0xffffffff, %%eax\n\t"
      "shrl $1, %%ecx\n\t"
      "movl %%edx, %%edi\n\t"
      "rep stosl\n\t"
      "adcl %%ecx, %%ecx\n\t"
      "rep stosw\n\t"
      ".Lsubdivide_triangle_11:\n\t"
      "cmpw $1, (%%esi)\n\t"
      "movl $1, -0x4(%%ebp)\n\t"
      "jl .Lsubdivide_triangle_26\n\t"
      "movl $3, %%eax\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "jmp .Lsubdivide_triangle_13\n\t"
      ".Lsubdivide_triangle_12:\n\t"
      "movl 0x18(%%ebp), %%ebx\n\t"
      "leal (%%esp), %%esp\n\t"
      ".Lsubdivide_triangle_13:\n\t"
      "movswl (%%ebx), %%ecx\n\t"
      "movl 0x8(%%esi), %%edx\n\t"
      "movw %%ax, (%%edx,%%ecx,2)\n\t"
      "incw (%%ebx)\n\t"
      "incw 0x10(%%esi)\n\t"
      "cmpw $3, %%ax\n\t"
      "movl $1, %%ebx\n\t"
      "jl .Lsubdivide_triangle_25\n\t"
      ".Lsubdivide_triangle_14:\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movl 0x1c(%%ebp), %%ecx\n\t"
      "movl 0x14(%%ebp), %%edx\n\t"
      "pushl %%eax\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "pushl %%ecx\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "pushl %%edx\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "leal -0x1(%%ebx), %%edi\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "decl %%eax\n\t"
      "movl %%esi, %%ecx\n\t"
      "call *%[c108270]\n\t"
      "movl 0x1c(%%ebp), %%ecx\n\t"
      "movl 0x14(%%ebp), %%edx\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "pushl %%ecx\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "pushl %%edx\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "pushl %%edi\n\t"
      "movl -0x4(%%ebp), %%edi\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "movl %%edi, %%eax\n\t"
      "movl %%esi, %%ecx\n\t"
      "call *%[c108270]\n\t"
      "movl 0x1c(%%ebp), %%ecx\n\t"
      "movl 0x14(%%ebp), %%edx\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "pushl %%ecx\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "pushl %%edx\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "movl %%edi, %%eax\n\t"
      "movl %%esi, %%ecx\n\t"
      "call *%[c108270]\n\t"
      "addl $0x54, %%esp\n\t"
      "movl %%eax, %%edi\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "testw %%ax, %%ax\n\t"
      "movl %%edi, -0x18(%%ebp)\n\t"
      "jl .Lsubdivide_triangle_15\n\t"
      "cmpw 0xc(%%esi), %%ax\n\t"
      "jle .Lsubdivide_triangle_16\n\t"
      ".Lsubdivide_triangle_15:\n\t"
      "pushl $1\n\t"
      "pushl $0xb0\n\t"
      "pushl $0x28be44\n\t"
      "pushl $0x28c47c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lsubdivide_triangle_16:\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "testw %%ax, %%ax\n\t"
      "jl .Lsubdivide_triangle_17\n\t"
      "cmpw 0xc(%%esi), %%ax\n\t"
      "jle .Lsubdivide_triangle_18\n\t"
      ".Lsubdivide_triangle_17:\n\t"
      "pushl $1\n\t"
      "pushl $0xb1\n\t"
      "pushl $0x28be44\n\t"
      "pushl $0x28c444\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lsubdivide_triangle_18:\n\t"
      "testw %%di, %%di\n\t"
      "jl .Lsubdivide_triangle_19\n\t"
      "cmpw 0xc(%%esi), %%di\n\t"
      "jle .Lsubdivide_triangle_20\n\t"
      ".Lsubdivide_triangle_19:\n\t"
      "pushl $1\n\t"
      "pushl $0xb2\n\t"
      "pushl $0x28be44\n\t"
      "pushl $0x28c408\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lsubdivide_triangle_20:\n\t"
      "cmpw $1, %%bx\n\t"
      "movl 0x18(%%ebp), %%edi\n\t"
      "jne .Lsubdivide_triangle_21\n\t"
      "movswl (%%edi), %%eax\n\t"
      "movl 0x8(%%esi), %%ecx\n\t"
      "movw -0xc(%%ebp), %%dx\n\t"
      "movw %%dx, (%%ecx,%%eax,2)\n\t"
      "incw (%%edi)\n\t"
      "movswl (%%edi), %%eax\n\t"
      "movl 0x8(%%esi), %%ecx\n\t"
      "movw -0x10(%%ebp), %%dx\n\t"
      "movw %%dx, (%%ecx,%%eax,2)\n\t"
      "incw (%%edi)\n\t"
      ".Lsubdivide_triangle_21:\n\t"
      "movswl (%%edi), %%eax\n\t"
      "movl 0x8(%%esi), %%ecx\n\t"
      "movw -0x18(%%ebp), %%dx\n\t"
      "movw %%dx, (%%ecx,%%eax,2)\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "incw (%%edi)\n\t"
      "cmpw %%ax, %%bx\n\t"
      "jge .Lsubdivide_triangle_24\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movl 0x1c(%%ebp), %%edx\n\t"
      "pushl %%ecx\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      "pushl %%edx\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "pushl %%ecx\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edx\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "decl %%eax\n\t"
      "movl %%esi, %%ecx\n\t"
      "call *%[c108270]\n\t"
      "addl $0x1c, %%esp\n\t"
      "testw %%ax, %%ax\n\t"
      "movl %%eax, -0x18(%%ebp)\n\t"
      "jl .Lsubdivide_triangle_22\n\t"
      "cmpw 0xc(%%esi), %%ax\n\t"
      "jle .Lsubdivide_triangle_23\n\t"
      ".Lsubdivide_triangle_22:\n\t"
      "pushl $1\n\t"
      "pushl $0xc2\n\t"
      "pushl $0x28be44\n\t"
      "pushl $0x28c3c8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "movl -0x18(%%ebp), %%eax\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lsubdivide_triangle_23:\n\t"
      "movswl (%%edi), %%ecx\n\t"
      "movl 0x8(%%esi), %%edx\n\t"
      "movw %%ax, (%%edx,%%ecx,2)\n\t"
      "incw (%%edi)\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      ".Lsubdivide_triangle_24:\n\t"
      "incl %%ebx\n\t"
      "cmpw %%ax, %%bx\n\t"
      "jle .Lsubdivide_triangle_14\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      ".Lsubdivide_triangle_25:\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "incl %%ecx\n\t"
      "addl $2, %%eax\n\t"
      "cmpw (%%esi), %%cx\n\t"
      "movl %%ecx, -0x4(%%ebp)\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "jle .Lsubdivide_triangle_12\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      ".Lsubdivide_triangle_26:\n\t"
      "pushl $0xc8\n\t"
      "pushl $0x28be44\n\t"
      "pushl %%edx\n\t"
      "call *%[c8ef70]\n\t"
      "addl $0xc, %%esp\n\t"
      ".Lsubdivide_triangle_27:\n\t"
      "popl %%edi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b108400_assert), [exitfn] "m"(b108400_exitfn), [c8ee60] "m"(b108400_c8ee60), [c108270] "m"(b108400_c108270), [c8ef70] "m"(b108400_c8ef70)
      : "memory");
}
#else
#error "subdivide_triangle: clang naked draft required"
#endif


/* 0x1087b0 */
void *FUN_001087b0(int type)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  debug_malloc(20, edi, (char *)0x0028be44, 58);
  /* cmp esi, edi -> je 0x108995 */
  debug_malloc(edx, edi, (char *)0, 0);
  debug_malloc(eax, edi, (char *)0, 0);
  debug_malloc(128, edi, (char *)0x0028be44, 69);
  /* relift: cmp dword ptr [esi + 8], edi -> je 0x108956 */
  /* cmp ebx, edi -> je 0x108956 */
  subdivide_triangle();
  /* cmp ecx, eax -> jl 0x10892d */
  display_assert((char *)0x0028c610, (char *)0x0028be44, 98, 0);
  system_exit(0);
  /* relift: cmp (int16_t)edx, word ptr [esi + 0xc] -> je 0x108981 */
  display_assert((char *)0x0028c5e8, (char *)0x0028be44, 99, 0);
  system_exit(0);
  /* cmp eax, edi -> je 0x10896a */
  debug_free((void *)(uintptr_t)eax, (char *)0x0028be44, 103);
  /* cmp eax, edi -> je 0x108981 */
  debug_free((void *)(uintptr_t)eax, (char *)0x0028be44, 104);
  /* test ebx, ebx -> je 0x108995 */
  debug_free((void *)(uintptr_t)ebx, (char *)0x0028be44, 107);
  return NULL;

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x1089a0 */
void FUN_001089a0(int *bounds, int y0, int x0, int h, int w)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x1089d0 */
void FUN_001089d0(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x1089f0 */
void FUN_001089f0(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x108a10 */
void FUN_00108a10(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x108a30 */
void FUN_00108a30(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x108a50 */
void FUN_00108a50(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x108a90 */
void FUN_00108a90(void)
{
  int eax = 0;

  csprintf((char *)0x005ab100, (char *)0x0028c678);
  display_assert((char *)(uintptr_t)eax, (char *)0, 0, 0);

  (void)eax;
}

/* 0x108bc0 */
void FUN_00108bc0(void)
{
  int eax = 0;
  int edx = 0;

  /* cmp (int16_t)eax, (int16_t)edx -> jge 0x108c44 */
  csmemset((void *)(uintptr_t)eax, 0, 0);

  (void)eax;
  (void)edx;
}

/* 0x108c60 */
void FUN_00108c60(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x108cd0 */
void FUN_00108cd0(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x108d00 */
void FUN_00108d00(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x108d40 */
void FUN_00108d40(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x108d80 */
void FUN_00108d80(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x108dd0 */
void FUN_00108dd0(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x108df0 */
void FUN_00108df0(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x108e20 */
void FUN_00108e20(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x108e40 */
void FUN_00108e40(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* cmp ecx, esi -> ja 0x108e5c */
  /* test edx, edx -> jne 0x108e50 */
  /* test esi, esi -> jne 0x108eaa */
  display_assert((char *)0x0028c6c8, (char *)0x0028c6a4, 348, 0);
  system_exit(0);
  /* test (int16_t)eax, (int16_t)eax -> jl 0x108ef4 */
  /* test ebx, ebx -> je 0x108edc */
  /* test eax, eax -> je 0x108ee4 */
  /* test edi, edi -> jne 0x108f34 */
  display_assert((char *)0x0028c6c8, (char *)0x0028c6a4, 369, 0);
  system_exit(0);
  /* test esi, esi -> jne 0x108f5b */
  display_assert((char *)0x0025f120, (char *)0x0028c6a4, 370, 0);
  system_exit(0);
  /* test (int16_t)ecx, (int16_t)ecx -> jl 0x108f8e */
  /* test edi, edi -> je 0x108fb3 */
  /* test esi, esi -> jne 0x108fd3 */
  display_assert((char *)0x0028c6d4, (char *)0x0028c6a4, 387, 0);
  system_exit(0);
  /* test (int16_t)ecx, (int16_t)ecx -> jl 0x108ffe */
  /* cmp eax, esi -> jle 0x109071 */
  csmemset((void *)(uintptr_t)edx, 0, 52);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}
