/* MSVC 7.1 FABS intrinsic: declared+pragma here so fabs() inlines to a single
 * FABS instruction instead of a CRT call. */
extern double __cdecl fabs(double);
#if defined(_MSC_VER) && !defined(__clang__)
#pragma intrinsic(fabs)
#else
/* clang builds with -fno-builtin, which ignores the intrinsic pragma above and
 * emits a real CRT call to fabs. The original inlines a single x87 FABS. Force
 * clang to inline via the always-available builtin so the codegen matches the
 * binary (and so equivalence harnesses don't see an external fabs stub). */
#define fabs __builtin_fabs
#endif

/* plane_negate (0x994d0) — readable C lift from XBE leaf. */
void plane_negate(float *plane_in, float *plane_out)
{
  plane_out[0] = -plane_in[0];
  plane_out[1] = -plane_in[1];
  plane_out[2] = -plane_in[2];
  plane_out[3] = -plane_in[3];
}

/* 0x106390 — Perimeter of a closed 2D polygon.
 * vertices is a flat array of (x,y) pairs; vertex_count is the vertex count.
 * Seeds the accumulator with the closing edge dist(vertex[0], vertex[last]),
 * then walks the vertex[i] -> vertex[i+1] edges (vertex_count-1 of them).
 * Term ordering under each sqrt matches the original codegen: x-term first for
 * the closing edge, y-term first inside the loop. Source:
 * c:\halo\SOURCE\math\geometry.c */
float convex_hull2d_perimeter(int16_t vertex_count, float *vertices)
{
  float perimeter;
  uint16_t remaining;

  perimeter = sqrtf((vertices[0] - vertices[vertex_count * 2 + -2]) *
                      (vertices[0] - vertices[vertex_count * 2 + -2]) +
                    (vertices[1] - vertices[vertex_count * 2 + -1]) *
                      (vertices[1] - vertices[vertex_count * 2 + -1]));

  if (1 < vertex_count) {
    remaining = (uint16_t)(vertex_count - 1);
    do {
      remaining = remaining - 1;
      perimeter =
        sqrtf((vertices[3] - vertices[1]) * (vertices[3] - vertices[1]) +
              (vertices[2] - vertices[0]) * (vertices[2] - vertices[0])) +
        perimeter;
      vertices = vertices + 2;
    } while (remaining != 0);
  }
  return perimeter;
}

/* convex_hull2d_test_vector (0x1063f0) — readable C lift (restored pre-naked).
 * Intermediates use long double to approximate x87 80-bit temps that the
 * original keeps live across the Liang-Barsky select (seed[60] 99/1 miss). */
bool convex_hull2d_test_vector(int16_t num_verts, float *polygon2d,
                               float *ray_origin, float *ray_dir,
                               float *out_tmin, float *out_tmax)
{
  long double tmin;
  long double tmax;
  long double dx;
  long double dy;
  long double denom;
  long double num;
  long double t;
  float *pts_iy;
  int16_t i;
  int cur;
  int next;

  tmin = (long double)(-3.4028235e38f);
  tmax = (long double)(3.4028235e38f);

  if (num_verts > 0) {
    i = 0;
    do {
      cur = (int)i;
      next = (((int)num_verts <= i + 1) - 1) & (i + 1);

      pts_iy = polygon2d + cur * 2 + 1;
      dx = (long double)polygon2d[next * 2] - (long double)polygon2d[cur * 2];
      dy = (long double)polygon2d[next * 2 + 1] - (long double)(*pts_iy);

      denom = dy * (long double)ray_dir[0] - dx * (long double)ray_dir[1];
      num = ((long double)ray_origin[1] - (long double)(*pts_iy)) * dx -
            ((long double)ray_origin[0] - (long double)polygon2d[cur * 2]) * dy;

      if (__builtin_fabsl(denom) < *(double *)0x2533d0) {
        if ((float)num < *(float *)0x253f44) {
          return 0;
        }
      } else {
        t = num / denom;
        if ((float)denom <= *(float *)0x2533c0) {
          if (!(tmax <= t))
            tmax = t;
        } else {
          if (!(t <= tmin))
            tmin = t;
        }
        if ((float)tmax < (float)tmin) {
          return 0;
        }
      }
      i = i + 1;
    } while (i < num_verts);
  }

  if (out_tmin != NULL) {
    *out_tmin = (float)tmin;
  }
  if (out_tmax != NULL) {
    *out_tmax = (float)tmax;
  }
  return 1;
}

/* convex_polygon2d_clip_to_plane (0x106510) — XBE naked draft (batch 259). */
#if defined(__clang__)
static void (*const b106510_chkstk)(void) = FUN_001d90e0;
static void (*const b106510_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b106510_exitfn)(int) = system_exit;
static void * (*const b106510_c8e0b0)(void *destination, void *source, size_t size) = csmemcpy;

__attribute__((naked, noinline))
int16_t convex_polygon2d_clip_to_plane(int16_t count __attribute__((unused)), float *points __attribute__((unused)), float *line __attribute__((unused)), int16_t max_count __attribute__((unused)), float *out_points __attribute__((unused)), uint32_t *out_bitmask __attribute__((unused)), uint8_t *changed __attribute__((unused)), float epsilon __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl $0x1014, %%eax\n\t"
      "call *%[chkstk]\n\t"
      "pushl %%ebx\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "xorl %%edi, %%edi\n\t"
      "cmpw $3, %%bx\n\t"
      "movb $0, -0x2(%%ebp)\n\t"
      "movb $0, -0x3(%%ebp)\n\t"
      "movl %%edi, -0x8(%%ebp)\n\t"
      "jge .Lconvex_polygon2d_clip_to_plane_1\n\t"
      "pushl $1\n\t"
      "pushl $0x546\n\t"
      "pushl $0x28be44\n\t"
      "pushl $0x28c010\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lconvex_polygon2d_clip_to_plane_1:\n\t"
      "movl 0x20(%%ebp), %%eax\n\t"
      "cmpl %%edi, %%eax\n\t"
      "je .Lconvex_polygon2d_clip_to_plane_2\n\t"
      "movb $0, (%%eax)\n\t"
      ".Lconvex_polygon2d_clip_to_plane_2:\n\t"
      "movl 0x18(%%ebp), %%esi\n\t"
      "cmpl %%esi, 0xc(%%ebp)\n\t"
      "jne .Lconvex_polygon2d_clip_to_plane_4\n\t"
      "cmpw $0x200, %%bx\n\t"
      "jle .Lconvex_polygon2d_clip_to_plane_3\n\t"
      "pushl $1\n\t"
      "pushl $0x54d\n\t"
      "pushl $0x28be44\n\t"
      "pushl $0x28bff8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lconvex_polygon2d_clip_to_plane_3:\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "movswl %%bx, %%eax\n\t"
      "shll $3, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "leal -0x1014(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c8e0b0]\n\t"
      "leal -0x1014(%%ebp), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "movl %%eax, 0xc(%%ebp)\n\t"
      ".Lconvex_polygon2d_clip_to_plane_4:\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "movswl %%bx, %%edx\n\t"
      "shll $3, %%edx\n\t"
      "leal -0x8(%%edx,%%ecx,1), %%eax\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "flds 0x4(%%eax)\n\t"
      "movl %%edx, -0xc(%%ebp)\n\t"
      "fmuls 0x4(%%ecx)\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "flds (%%eax)\n\t"
      "fmuls (%%ecx)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fsubs 0x8(%%ecx)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "je .Lconvex_polygon2d_clip_to_plane_5\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      ".Lconvex_polygon2d_clip_to_plane_5:\n\t"
      "testw %%bx, %%bx\n\t"
      "movl $0, -0x10(%%ebp)\n\t"
      "jle .Lconvex_polygon2d_clip_to_plane_23\n\t"
      "leal (%%esp), %%esp\n\t"
      ".Lconvex_polygon2d_clip_to_plane_6:\n\t"
      "movswl -0x10(%%ebp), %%eax\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "leal (%%edx,%%eax,8), %%edx\n\t"
      "movb $1, 0x1b(%%ebp)\n\t"
      "flds 0x4(%%edx)\n\t"
      "fmuls 0x4(%%ecx)\n\t"
      "flds (%%ecx)\n\t"
      "fmuls (%%edx)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fsubs 0x8(%%ecx)\n\t"
      "fcoms 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "je .Lconvex_polygon2d_clip_to_plane_7\n\t"
      "movb $0, 0x1b(%%ebp)\n\t"
      ".Lconvex_polygon2d_clip_to_plane_7:\n\t"
      "fcoms 0x24(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lconvex_polygon2d_clip_to_plane_8\n\t"
      "fstp %%st(0)\n\t"
      "movb $1, -0x2(%%ebp)\n\t"
      "jmp .Lconvex_polygon2d_clip_to_plane_9\n\t"
      ".Lconvex_polygon2d_clip_to_plane_8:\n\t"
      "flds 0x24(%%ebp)\n\t"
      "fchs\n\t"
      "fxch %%st(1)\n\t"
      "fcompp\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lconvex_polygon2d_clip_to_plane_9\n\t"
      "movb $1, -0x3(%%ebp)\n\t"
      ".Lconvex_polygon2d_clip_to_plane_9:\n\t"
      "movb 0x1b(%%ebp), %%al\n\t"
      "cmpb -0x1(%%ebp), %%al\n\t"
      "je .Lconvex_polygon2d_clip_to_plane_16\n\t"
      "cmpw 0x14(%%ebp), %%di\n\t"
      "je .Lconvex_polygon2d_clip_to_plane_25\n\t"
      "movl 0x20(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lconvex_polygon2d_clip_to_plane_10\n\t"
      "movb $1, (%%eax)\n\t"
      ".Lconvex_polygon2d_clip_to_plane_10:\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "flds (%%eax)\n\t"
      "fsubs (%%edx)\n\t"
      "flds 0x4(%%eax)\n\t"
      "fsubs 0x4(%%edx)\n\t"
      "flds 0x4(%%edx)\n\t"
      "fmuls 0x4(%%ecx)\n\t"
      "flds (%%ecx)\n\t"
      "fmuls (%%edx)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fsubs 0x8(%%ecx)\n\t"
      "fld %%st(2)\n\t"
      "fmuls (%%ecx)\n\t"
      "fld %%st(2)\n\t"
      "fmuls 0x4(%%ecx)\n\t"
      ".byte 0xde, 0xc1\n\t"
      ".byte 0xde, 0xf9\n\t"
      "fchs\n\t"
      "fcoms 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lconvex_polygon2d_clip_to_plane_11\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c0\n\t"
      "jmp .Lconvex_polygon2d_clip_to_plane_12\n\t"
      ".Lconvex_polygon2d_clip_to_plane_11:\n\t"
      "fcoms 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lconvex_polygon2d_clip_to_plane_12\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c8\n\t"
      ".Lconvex_polygon2d_clip_to_plane_12:\n\t"
      "movl -0x8(%%ebp), %%ebx\n\t"
      "fld %%st(0)\n\t"
      "fmul %%st(3), %%st(0)\n\t"
      "movswl %%di, %%ecx\n\t"
      "movl $1, %%eax\n\t"
      "shll %%cl, %%eax\n\t"
      "fadds (%%edx)\n\t"
      "fstps (%%esi,%%ecx,8)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "orl %%eax, %%ebx\n\t"
      "incl %%edi\n\t"
      "cmpw $1, %%di\n\t"
      "fadds 0x4(%%edx)\n\t"
      "movl %%ebx, -0x8(%%ebp)\n\t"
      "fstps 0x4(%%esi,%%ecx,8)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "je .Lconvex_polygon2d_clip_to_plane_15\n\t"
      "movswl %%di, %%ecx\n\t"
      "flds -0x8(%%esi,%%ecx,8)\n\t"
      "fsubs (%%esi)\n\t"
      "fabs\n\t"
      "flds 0x24(%%ebp)\n\t"
      "fcompp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lconvex_polygon2d_clip_to_plane_13\n\t"
      "flds -0x4(%%esi,%%ecx,8)\n\t"
      "fsubs 0x4(%%esi)\n\t"
      "fabs\n\t"
      "flds 0x24(%%ebp)\n\t"
      "fcompp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .Lconvex_polygon2d_clip_to_plane_14\n\t"
      ".Lconvex_polygon2d_clip_to_plane_13:\n\t"
      "flds -0x10(%%esi,%%ecx,8)\n\t"
      "fsubrs -0x8(%%esi,%%ecx,8)\n\t"
      "fabs\n\t"
      "flds 0x24(%%ebp)\n\t"
      "fcompp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lconvex_polygon2d_clip_to_plane_15\n\t"
      "flds -0x4(%%esi,%%ecx,8)\n\t"
      "fsubs -0xc(%%esi,%%ecx,8)\n\t"
      "fabs\n\t"
      "flds 0x24(%%ebp)\n\t"
      "fcompp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lconvex_polygon2d_clip_to_plane_15\n\t"
      ".Lconvex_polygon2d_clip_to_plane_14:\n\t"
      "decl %%edi\n\t"
      ".Lconvex_polygon2d_clip_to_plane_15:\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      ".Lconvex_polygon2d_clip_to_plane_16:\n\t"
      "movb 0x1b(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lconvex_polygon2d_clip_to_plane_22\n\t"
      "cmpw 0x14(%%ebp), %%di\n\t"
      "je .Lconvex_polygon2d_clip_to_plane_25\n\t"
      "movl (%%edx), %%ecx\n\t"
      "movswl %%di, %%ebx\n\t"
      "movl %%ecx, (%%esi,%%ebx,8)\n\t"
      "movl 0x4(%%edx), %%eax\n\t"
      "movl %%eax, 0x4(%%esi,%%ebx,8)\n\t"
      "movl 0x1c(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lconvex_polygon2d_clip_to_plane_17\n\t"
      "movswl -0x10(%%ebp), %%ecx\n\t"
      "movl $1, %%eax\n\t"
      "shll %%cl, %%eax\n\t"
      "movl 0x1c(%%ebp), %%ecx\n\t"
      "andl (%%ecx), %%eax\n\t"
      "negl %%eax\n\t"
      "sbbl %%eax, %%eax\n\t"
      "negl %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lconvex_polygon2d_clip_to_plane_17\n\t"
      "movl %%ebx, %%ecx\n\t"
      "movl $1, %%eax\n\t"
      "shll %%cl, %%eax\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "orl %%eax, %%ecx\n\t"
      "jmp .Lconvex_polygon2d_clip_to_plane_18\n\t"
      ".Lconvex_polygon2d_clip_to_plane_17:\n\t"
      "movl %%ebx, %%ecx\n\t"
      "movl $1, %%eax\n\t"
      "shll %%cl, %%eax\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "notl %%eax\n\t"
      "andl %%eax, %%ecx\n\t"
      ".Lconvex_polygon2d_clip_to_plane_18:\n\t"
      "incl %%edi\n\t"
      "cmpw $1, %%di\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "je .Lconvex_polygon2d_clip_to_plane_21\n\t"
      "movswl %%di, %%ecx\n\t"
      "flds -0x8(%%esi,%%ecx,8)\n\t"
      "fsubs (%%esi)\n\t"
      "fabs\n\t"
      "flds 0x24(%%ebp)\n\t"
      "fcompp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lconvex_polygon2d_clip_to_plane_19\n\t"
      "flds -0x4(%%esi,%%ecx,8)\n\t"
      "fsubs 0x4(%%esi)\n\t"
      "fabs\n\t"
      "flds 0x24(%%ebp)\n\t"
      "fcompp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .Lconvex_polygon2d_clip_to_plane_20\n\t"
      ".Lconvex_polygon2d_clip_to_plane_19:\n\t"
      "flds -0x10(%%esi,%%ecx,8)\n\t"
      "fsubrs -0x8(%%esi,%%ecx,8)\n\t"
      "fabs\n\t"
      "flds 0x24(%%ebp)\n\t"
      "fcompp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lconvex_polygon2d_clip_to_plane_21\n\t"
      "flds -0x4(%%esi,%%ecx,8)\n\t"
      "fsubs -0xc(%%esi,%%ecx,8)\n\t"
      "fabs\n\t"
      "flds 0x24(%%ebp)\n\t"
      "fcompp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lconvex_polygon2d_clip_to_plane_21\n\t"
      ".Lconvex_polygon2d_clip_to_plane_20:\n\t"
      "decl %%edi\n\t"
      ".Lconvex_polygon2d_clip_to_plane_21:\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      ".Lconvex_polygon2d_clip_to_plane_22:\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "incl %%eax\n\t"
      "cmpw %%bx, %%ax\n\t"
      "movl %%edx, -0x14(%%ebp)\n\t"
      "movb 0x1b(%%ebp), %%dl\n\t"
      "movb %%dl, -0x1(%%ebp)\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "jl .Lconvex_polygon2d_clip_to_plane_6\n\t"
      "cmpw $-1, %%di\n\t"
      "je .Lconvex_polygon2d_clip_to_plane_26\n\t"
      "cmpw $3, %%di\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "jge .Lconvex_polygon2d_clip_to_plane_24\n\t"
      ".Lconvex_polygon2d_clip_to_plane_23:\n\t"
      "xorl %%edi, %%edi\n\t"
      ".Lconvex_polygon2d_clip_to_plane_24:\n\t"
      "movb -0x2(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lconvex_polygon2d_clip_to_plane_32\n\t"
      "xorl %%edi, %%edi\n\t"
      "jmp .Lconvex_polygon2d_clip_to_plane_30\n\t"
      ".Lconvex_polygon2d_clip_to_plane_25:\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "orl $0xffffffff, %%edi\n\t"
      ".Lconvex_polygon2d_clip_to_plane_26:\n\t"
      "testw %%bx, %%bx\n\t"
      "jl .Lconvex_polygon2d_clip_to_plane_27\n\t"
      "cmpw 0x14(%%ebp), %%bx\n\t"
      "jle .Lconvex_polygon2d_clip_to_plane_28\n\t"
      ".Lconvex_polygon2d_clip_to_plane_27:\n\t"
      "pushl $1\n\t"
      "pushl $0x5a8\n\t"
      "pushl $0x28be44\n\t"
      "pushl $0x28bfd4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lconvex_polygon2d_clip_to_plane_28:\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%esi\n\t"
      "call *%[c8e0b0]\n\t"
      ".Lconvex_polygon2d_clip_to_plane_29:\n\t"
      "addl $0xc, %%esp\n\t"
      ".Lconvex_polygon2d_clip_to_plane_30:\n\t"
      "movl 0x1c(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lconvex_polygon2d_clip_to_plane_31\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movl %%ecx, (%%eax)\n\t"
      ".Lconvex_polygon2d_clip_to_plane_31:\n\t"
      "movw %%di, %%ax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lconvex_polygon2d_clip_to_plane_32:\n\t"
      "movb -0x3(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lconvex_polygon2d_clip_to_plane_30\n\t"
      "testw %%bx, %%bx\n\t"
      "jl .Lconvex_polygon2d_clip_to_plane_33\n\t"
      "cmpw 0x14(%%ebp), %%bx\n\t"
      "jle .Lconvex_polygon2d_clip_to_plane_34\n\t"
      ".Lconvex_polygon2d_clip_to_plane_33:\n\t"
      "pushl $1\n\t"
      "pushl $0x5a1\n\t"
      "pushl $0x28be44\n\t"
      "pushl $0x28bfd4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lconvex_polygon2d_clip_to_plane_34:\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[c8e0b0]\n\t"
      "movl %%ebx, %%edi\n\t"
      "jmp .Lconvex_polygon2d_clip_to_plane_29\n\t"
      :
      : [chkstk] "m"(b106510_chkstk), [assert] "m"(b106510_assert), [exitfn] "m"(b106510_exitfn), [c8e0b0] "m"(b106510_c8e0b0)
      : "memory");
}
#else
#error "convex_polygon2d_clip_to_plane: clang naked draft required"
#endif


/* convex_polygon2d_verify (0x106900) — readable C lift from XBE leaf.
 * Rejects vertices with Inf/NaN float encodings. */
bool convex_polygon2d_verify(int16_t vertex_count, uint32_t *vertices)
{
  int16_t i;
  if (vertex_count <= 0) {
    return true;
  }
  for (i = 0; i < vertex_count; i++) {
    uint32_t *vert = vertices + (i * 2);
    if ((vert[0] & 0x7f800000u) == 0x7f800000u) {
      return false;
    }
    if ((vert[1] & 0x7f800000u) == 0x7f800000u) {
      return false;
    }
  }
  return true;
}

/* 0x106dc0 — Verify that a 3D polygon is convex and (near-)planar.
 * vertices is a flat array of (x,y,z) triples (12 bytes each); vertex_count is
 * the vertex count. A reference plane normal is built from the first three
 * vertices as cross(vert0 - vert1, vert2 - vert1). For every vertex the corner
 * normal cross(prev - cur, next - cur) is dotted against that reference normal;
 * if any dot falls below a small negative epsilon (0xb58637bd = -1e-6) the
 * winding has reversed and the function returns 0. The current vertex is also
 * rejected if any component is IEEE 754 infinity or NaN (all exponent bits
 * set). prev wraps to the last vertex on the first iteration; next wraps to
 * vertex 0 on the last. The reference-normal setup runs unconditionally before
 * the count guard, and the loop counter stays 16-bit, matching the original
 * codegen. Returns a byte (bool). Source: c:\halo\SOURCE\math\geometry.c */
bool convex_polygon3d_verify(int16_t vertex_count, float *vertices)
{
  float edge_a0, edge_a1, edge_a2;
  float edge_b0, edge_b1, edge_b2;
  float ref0, ref1, ref2;
  float a0, a1, a2, b0, b1, b2, c0, c1, c2, dot;
  float cx, cy, cz;
  float *prev, *cur, *next;
  int last;
  int16_t i;

  edge_a0 = vertices[0] - vertices[3];
  edge_a1 = vertices[1] - vertices[4];
  edge_a2 = vertices[2] - vertices[5];
  edge_b0 = vertices[6] - vertices[3];
  edge_b1 = vertices[7] - vertices[4];
  edge_b2 = vertices[8] - vertices[5];
  ref0 = edge_a1 * edge_b2 - edge_a2 * edge_b1;
  ref1 = edge_a2 * edge_b0 - edge_a0 * edge_b2;
  ref2 = edge_a0 * edge_b1 - edge_a1 * edge_b0;

  if (vertex_count <= 0) {
    return 1;
  }

  last = vertex_count - 1;
  for (i = 0; i < vertex_count; i++) {
    if (i == 0) {
      prev = vertices + vertex_count * 3 - 3;
    } else {
      prev = vertices + i * 3 - 3;
    }
    cur = vertices + i * 3;
    if (i == last) {
      next = vertices;
    } else {
      next = cur + 3;
    }

    cx = cur[0];
    if ((*(uint32_t *)&cx & 0x7f800000) == 0x7f800000) {
      return 0;
    }
    cy = cur[1];
    if ((*(uint32_t *)&cy & 0x7f800000) == 0x7f800000) {
      return 0;
    }
    cz = cur[2];
    if ((*(uint32_t *)&cz & 0x7f800000) == 0x7f800000) {
      return 0;
    }

    a0 = prev[0] - cur[0];
    a1 = prev[1] - cur[1];
    a2 = prev[2] - cur[2];
    b0 = next[0] - cur[0];
    b1 = next[1] - cur[1];
    b2 = next[2] - cur[2];
    c0 = a1 * b2 - a2 * b1;
    c1 = a2 * b0 - a0 * b2;
    c2 = a0 * b1 - a1 * b0;
    dot = ref0 * c0 + ref1 * c1 + ref2 * c2;
    if (dot < -9.99999997e-07f) {
      return 0;
    }
  }
  return 1;
}

/* convex_polygon3d_clip_to_plane (0x106960) — XBE naked draft (batch 242). */
#if defined(__clang__)
static void (*const b106960_chkstk)(void) = FUN_001d90e0;
static void (*const b106960_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b106960_exitfn)(int) = system_exit;
static void * (*const b106960_c8e0b0)(void *destination, void *source, size_t size) = csmemcpy;

__attribute__((naked, noinline))
int16_t convex_polygon3d_clip_to_plane(int16_t count __attribute__((unused)), float *verts __attribute__((unused)), float *plane __attribute__((unused)), int16_t max_count __attribute__((unused)), float *out_verts __attribute__((unused)), uint32_t *out_bitmask __attribute__((unused)), float epsilon __attribute__((unused)), void *changed __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl $0x1818, %%eax\n\t"
      "call *%[chkstk]\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "xorl %%esi, %%esi\n\t"
      "cmpw $3, %%di\n\t"
      "movb $0, -0x2(%%ebp)\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "jge .Lconvex_polygon3d_clip_to_plane_1\n\t"
      "pushl $1\n\t"
      "pushl $0x5d5\n\t"
      "pushl $0x28be44\n\t"
      "pushl $0x28c010\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lconvex_polygon3d_clip_to_plane_1:\n\t"
      "movl 0x1c(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lconvex_polygon3d_clip_to_plane_2\n\t"
      "movb $0, (%%eax)\n\t"
      ".Lconvex_polygon3d_clip_to_plane_2:\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "cmpl 0x18(%%ebp), %%eax\n\t"
      "jne .Lconvex_polygon3d_clip_to_plane_4\n\t"
      "cmpw $0x200, %%di\n\t"
      "jle .Lconvex_polygon3d_clip_to_plane_3\n\t"
      "pushl $1\n\t"
      "pushl $0x5dc\n\t"
      "pushl $0x28be44\n\t"
      "pushl $0x28bff8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lconvex_polygon3d_clip_to_plane_3:\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "movswl %%di, %%eax\n\t"
      "leal (%%eax,%%eax,2), %%ecx\n\t"
      "shll $2, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "leal -0x1818(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c8e0b0]\n\t"
      "leal -0x1818(%%ebp), %%ecx\n\t"
      "addl $0xc, %%esp\n\t"
      "movl %%ecx, 0xc(%%ebp)\n\t"
      ".Lconvex_polygon3d_clip_to_plane_4:\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "movswl %%di, %%eax\n\t"
      "movl 0x10(%%ebp), %%edi\n\t"
      "leal (%%eax,%%eax,2), %%ecx\n\t"
      "shll $2, %%ecx\n\t"
      "leal -0xc(%%ecx,%%edx,1), %%edx\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "flds 0x4(%%edx)\n\t"
      "fmuls 0x4(%%edi)\n\t"
      "flds 0x8(%%edx)\n\t"
      "fmuls 0x8(%%edi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds (%%edi)\n\t"
      "fmuls (%%edx)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fsubs 0xc(%%edi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .Lconvex_polygon3d_clip_to_plane_5\n\t"
      "movb $1, %%bl\n\t"
      "jmp .Lconvex_polygon3d_clip_to_plane_6\n\t"
      ".Lconvex_polygon3d_clip_to_plane_5:\n\t"
      "xorb %%bl, %%bl\n\t"
      ".Lconvex_polygon3d_clip_to_plane_6:\n\t"
      "cmpw $0, 0x8(%%ebp)\n\t"
      "movl $0, -0xc(%%ebp)\n\t"
      "jle .Lconvex_polygon3d_clip_to_plane_20\n\t"
      ".Lconvex_polygon3d_clip_to_plane_7:\n\t"
      "movswl -0xc(%%ebp), %%eax\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "leal (%%eax,%%eax,2), %%eax\n\t"
      "leal (%%ecx,%%eax,4), %%ecx\n\t"
      "movb $1, 0x13(%%ebp)\n\t"
      "flds 0x8(%%ecx)\n\t"
      "fmuls 0x8(%%edi)\n\t"
      "flds (%%edi)\n\t"
      "fmuls (%%ecx)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds 0x4(%%ecx)\n\t"
      "fmuls 0x4(%%edi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fsubs 0xc(%%edi)\n\t"
      "fcoms 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "je .Lconvex_polygon3d_clip_to_plane_8\n\t"
      "movb $0, 0x13(%%ebp)\n\t"
      ".Lconvex_polygon3d_clip_to_plane_8:\n\t"
      "fcoms 0x20(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lconvex_polygon3d_clip_to_plane_9\n\t"
      "fstp %%st(0)\n\t"
      "movb $1, -0x2(%%ebp)\n\t"
      "jmp .Lconvex_polygon3d_clip_to_plane_10\n\t"
      ".Lconvex_polygon3d_clip_to_plane_9:\n\t"
      "flds 0x20(%%ebp)\n\t"
      "fchs\n\t"
      "fxch %%st(1)\n\t"
      "fcompp\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lconvex_polygon3d_clip_to_plane_10\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      ".Lconvex_polygon3d_clip_to_plane_10:\n\t"
      "cmpb %%bl, 0x13(%%ebp)\n\t"
      "je .Lconvex_polygon3d_clip_to_plane_16\n\t"
      "cmpw 0x14(%%ebp), %%si\n\t"
      "je .Lconvex_polygon3d_clip_to_plane_23\n\t"
      "movl 0x1c(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lconvex_polygon3d_clip_to_plane_11\n\t"
      "movb $1, (%%eax)\n\t"
      ".Lconvex_polygon3d_clip_to_plane_11:\n\t"
      "flds (%%edx)\n\t"
      "fsubs (%%ecx)\n\t"
      "flds 0x4(%%edx)\n\t"
      "fsubs 0x4(%%ecx)\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "flds 0x8(%%edx)\n\t"
      "fsubs 0x8(%%ecx)\n\t"
      "flds 0x8(%%ecx)\n\t"
      "fmuls 0x8(%%edi)\n\t"
      "flds (%%edi)\n\t"
      "fmuls (%%ecx)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds 0x4(%%ecx)\n\t"
      "fmuls 0x4(%%edi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fsubs 0xc(%%edi)\n\t"
      "fld %%st(2)\n\t"
      "fmuls (%%edi)\n\t"
      "fld %%st(2)\n\t"
      "fmuls 0x8(%%edi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fmuls 0x4(%%edi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      ".byte 0xde, 0xf9\n\t"
      "fchs\n\t"
      "fcoms 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lconvex_polygon3d_clip_to_plane_12\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c0\n\t"
      "jmp .Lconvex_polygon3d_clip_to_plane_13\n\t"
      ".Lconvex_polygon3d_clip_to_plane_12:\n\t"
      "fcoms 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lconvex_polygon3d_clip_to_plane_13\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c8\n\t"
      ".Lconvex_polygon3d_clip_to_plane_13:\n\t"
      "fld %%st(0)\n\t"
      "movswl %%si, %%eax\n\t"
      "fmul %%st(3), %%st(0)\n\t"
      "leal (%%eax,%%eax,2), %%edx\n\t"
      "movl 0x18(%%ebp), %%eax\n\t"
      "leal (%%eax,%%edx,4), %%eax\n\t"
      "fadds (%%ecx)\n\t"
      "incl %%esi\n\t"
      "cmpw $1, %%si\n\t"
      "fstps (%%eax)\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fadds 0x4(%%ecx)\n\t"
      "fstps 0x4(%%eax)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fadds 0x8(%%ecx)\n\t"
      "fstps 0x8(%%eax)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "je .Lconvex_polygon3d_clip_to_plane_16\n\t"
      "movl 0x18(%%ebp), %%eax\n\t"
      "movswl %%si, %%ebx\n\t"
      "leal (%%ebx,%%ebx,2), %%edx\n\t"
      "leal (%%eax,%%edx,4), %%edx\n\t"
      "flds -0xc(%%edx)\n\t"
      "fsubs (%%eax)\n\t"
      "fabs\n\t"
      "flds 0x20(%%ebp)\n\t"
      "fcompp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lconvex_polygon3d_clip_to_plane_14\n\t"
      "flds -0x8(%%edx)\n\t"
      "movl 0x18(%%ebp), %%eax\n\t"
      "fsubs 0x4(%%eax)\n\t"
      "fabs\n\t"
      "flds 0x20(%%ebp)\n\t"
      "fcompp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lconvex_polygon3d_clip_to_plane_14\n\t"
      "flds -0x4(%%edx)\n\t"
      "movl 0x18(%%ebp), %%eax\n\t"
      "fsubs 0x8(%%eax)\n\t"
      "fabs\n\t"
      "flds 0x20(%%ebp)\n\t"
      "fcompp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .Lconvex_polygon3d_clip_to_plane_15\n\t"
      ".Lconvex_polygon3d_clip_to_plane_14:\n\t"
      "leal -0x6(%%ebx,%%ebx,2), %%eax\n\t"
      "movl 0x18(%%ebp), %%ebx\n\t"
      "flds (%%ebx,%%eax,4)\n\t"
      "fsubrs -0xc(%%edx)\n\t"
      "fabs\n\t"
      "flds 0x20(%%ebp)\n\t"
      "fcompp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lconvex_polygon3d_clip_to_plane_16\n\t"
      "flds -0x8(%%edx)\n\t"
      "fsubs -0x14(%%edx)\n\t"
      "fabs\n\t"
      "flds 0x20(%%ebp)\n\t"
      "fcompp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lconvex_polygon3d_clip_to_plane_16\n\t"
      "flds -0x4(%%edx)\n\t"
      "fsubs -0x10(%%edx)\n\t"
      "fabs\n\t"
      "flds 0x20(%%ebp)\n\t"
      "fcompp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lconvex_polygon3d_clip_to_plane_16\n\t"
      ".Lconvex_polygon3d_clip_to_plane_15:\n\t"
      "decl %%esi\n\t"
      ".Lconvex_polygon3d_clip_to_plane_16:\n\t"
      "movb 0x13(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lconvex_polygon3d_clip_to_plane_19\n\t"
      "cmpw 0x14(%%ebp), %%si\n\t"
      "jge .Lconvex_polygon3d_clip_to_plane_23\n\t"
      "movswl %%si, %%eax\n\t"
      "leal (%%eax,%%eax,2), %%edx\n\t"
      "movl 0x18(%%ebp), %%eax\n\t"
      "leal (%%eax,%%edx,4), %%edx\n\t"
      "movl %%ecx, %%eax\n\t"
      "movl (%%eax), %%ebx\n\t"
      "movl %%ebx, (%%edx)\n\t"
      "movl 0x4(%%eax), %%ebx\n\t"
      "movl %%ebx, 0x4(%%edx)\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "incl %%esi\n\t"
      "cmpw $1, %%si\n\t"
      "movl %%eax, 0x8(%%edx)\n\t"
      "je .Lconvex_polygon3d_clip_to_plane_19\n\t"
      "movl 0x18(%%ebp), %%eax\n\t"
      "movswl %%si, %%ebx\n\t"
      "leal (%%ebx,%%ebx,2), %%edx\n\t"
      "leal (%%eax,%%edx,4), %%edx\n\t"
      "flds -0xc(%%edx)\n\t"
      "fsubs (%%eax)\n\t"
      "fabs\n\t"
      "flds 0x20(%%ebp)\n\t"
      "fcompp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lconvex_polygon3d_clip_to_plane_17\n\t"
      "flds -0x8(%%edx)\n\t"
      "movl 0x18(%%ebp), %%eax\n\t"
      "fsubs 0x4(%%eax)\n\t"
      "fabs\n\t"
      "flds 0x20(%%ebp)\n\t"
      "fcompp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lconvex_polygon3d_clip_to_plane_17\n\t"
      "flds -0x4(%%edx)\n\t"
      "movl 0x18(%%ebp), %%eax\n\t"
      "fsubs 0x8(%%eax)\n\t"
      "fabs\n\t"
      "flds 0x20(%%ebp)\n\t"
      "fcompp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .Lconvex_polygon3d_clip_to_plane_18\n\t"
      ".Lconvex_polygon3d_clip_to_plane_17:\n\t"
      "leal -0x6(%%ebx,%%ebx,2), %%eax\n\t"
      "movl 0x18(%%ebp), %%ebx\n\t"
      "flds (%%ebx,%%eax,4)\n\t"
      "fsubrs -0xc(%%edx)\n\t"
      "fabs\n\t"
      "flds 0x20(%%ebp)\n\t"
      "fcompp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lconvex_polygon3d_clip_to_plane_19\n\t"
      "flds -0x8(%%edx)\n\t"
      "fsubs -0x14(%%edx)\n\t"
      "fabs\n\t"
      "flds 0x20(%%ebp)\n\t"
      "fcompp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lconvex_polygon3d_clip_to_plane_19\n\t"
      "flds -0x4(%%edx)\n\t"
      "fsubs -0x10(%%edx)\n\t"
      "fabs\n\t"
      "flds 0x20(%%ebp)\n\t"
      "fcompp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lconvex_polygon3d_clip_to_plane_19\n\t"
      ".Lconvex_polygon3d_clip_to_plane_18:\n\t"
      "decl %%esi\n\t"
      ".Lconvex_polygon3d_clip_to_plane_19:\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "movb 0x13(%%ebp), %%bl\n\t"
      "incl %%eax\n\t"
      "cmpw 0x8(%%ebp), %%ax\n\t"
      "movl %%ecx, %%edx\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "jl .Lconvex_polygon3d_clip_to_plane_7\n\t"
      "cmpw $-1, %%si\n\t"
      "je .Lconvex_polygon3d_clip_to_plane_24\n\t"
      "cmpw $3, %%si\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "jge .Lconvex_polygon3d_clip_to_plane_21\n\t"
      ".Lconvex_polygon3d_clip_to_plane_20:\n\t"
      "xorl %%esi, %%esi\n\t"
      ".Lconvex_polygon3d_clip_to_plane_21:\n\t"
      "movb -0x2(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "jne .Lconvex_polygon3d_clip_to_plane_28\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lconvex_polygon3d_clip_to_plane_22\n\t"
      "movb 0x24(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lconvex_polygon3d_clip_to_plane_29\n\t"
      ".Lconvex_polygon3d_clip_to_plane_22:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "xorl %%eax, %%eax\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lconvex_polygon3d_clip_to_plane_23:\n\t"
      "orl $0xffffffff, %%esi\n\t"
      ".Lconvex_polygon3d_clip_to_plane_24:\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "testw %%ax, %%ax\n\t"
      "jl .Lconvex_polygon3d_clip_to_plane_25\n\t"
      "cmpw 0x14(%%ebp), %%ax\n\t"
      "jle .Lconvex_polygon3d_clip_to_plane_26\n\t"
      ".Lconvex_polygon3d_clip_to_plane_25:\n\t"
      "pushl $1\n\t"
      "pushl $0x637\n\t"
      "pushl $0x28be44\n\t"
      "pushl $0x28bfd4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lconvex_polygon3d_clip_to_plane_26:\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "movl 0x18(%%ebp), %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c8e0b0]\n\t"
      "addl $0xc, %%esp\n\t"
      ".Lconvex_polygon3d_clip_to_plane_27:\n\t"
      "popl %%edi\n\t"
      "movw %%si, %%ax\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lconvex_polygon3d_clip_to_plane_28:\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lconvex_polygon3d_clip_to_plane_27\n\t"
      ".Lconvex_polygon3d_clip_to_plane_29:\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "testw %%ax, %%ax\n\t"
      "jl .Lconvex_polygon3d_clip_to_plane_30\n\t"
      "cmpw 0x14(%%ebp), %%ax\n\t"
      "jle .Lconvex_polygon3d_clip_to_plane_31\n\t"
      ".Lconvex_polygon3d_clip_to_plane_30:\n\t"
      "pushl $1\n\t"
      "pushl $0x630\n\t"
      "pushl $0x28be44\n\t"
      "pushl $0x28bfd4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lconvex_polygon3d_clip_to_plane_31:\n\t"
      "movl 0x18(%%ebp), %%edx\n\t"
      "pushl %%ecx\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c8e0b0]\n\t"
      "movw 0x8(%%ebp), %%ax\n\t"
      "addl $0xc, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [chkstk] "m"(b106960_chkstk), [assert] "m"(b106960_assert), [exitfn] "m"(b106960_exitfn), [c8e0b0] "m"(b106960_c8e0b0)
      : "memory");
}
#else
#error "convex_polygon3d_clip_to_plane: clang naked draft required"
#endif

