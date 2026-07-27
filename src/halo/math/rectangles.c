#include <stdint.h>
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

/* FUN_00107c30 (0x107c30) — readable C lift from XBE leaf.
 * Build convex polyhedron from point cloud, then validate each point. */
char FUN_00107c30(int16_t point_count, float *points, int16_t vertices_capacity,
                  char *vertices, int16_t edges_capacity, char *edges,
                  int16_t surfaces_capacity, char *surfaces)
{
  int16_t i;
  char (*validate_point)(int16_t, float *, int16_t, char *, int16_t, char *,
                         int16_t, char *, int);

  if (!points) {
    display_assert((const char *)0x28ba70, (const char *)0x28be44, 0x8ec, 1);
    system_exit(-1);
  }
  if (!vertices) {
    display_assert((const char *)0x28c050, (const char *)0x28be44, 0x8ed, 1);
    system_exit(-1);
  }
  if (!edges) {
    display_assert((const char *)0x28c048, (const char *)0x28be44, 0x8ee, 1);
    system_exit(-1);
  }
  if (!surfaces) {
    display_assert((const char *)0x28c03c, (const char *)0x28be44, 0x8ef, 1);
    system_exit(-1);
  }
  if (!FUN_00106f50(point_count, points, vertices_capacity, vertices,
                    edges_capacity, edges, surfaces_capacity, surfaces))
    return 0;
  validate_point = (char (*)(int16_t, float *, int16_t, char *, int16_t, char *,
                             int16_t, char *, int))FUN_00107520;
  if (point_count <= 0)
    return 1;
  for (i = 0; i < point_count; i++) {
    if (!validate_point(point_count, points, vertices_capacity, vertices,
                        edges_capacity, edges, surfaces_capacity, surfaces,
                        (int)i))
      return 0;
  }
  return 1;
}



/* FUN_00107d40 (0x107d40) — readable C lift from XBE leaf. */
char FUN_00107d40(int a0, int a1, int a2, int a3, int a4, int a5, int16_t count, float *dir, float *planes)
{
  int16_t i;
  char ok;
  float *plane;
  float d;

  (void)a0; (void)a1; (void)a2; (void)a3; (void)a4; (void)a5;
  ok = 1;
  if (count <= 0) {
    return ok;
  }
  for (i = 0; i < count; i++) {
    plane = (float *)((char *)planes + (int)i * 0x1c);
    if (*(unsigned char *)plane == 0) {
      continue;
    }
    d = plane[3] * dir[2] + plane[2] * dir[1] + plane[1] * dir[0] - plane[4];
    if (d > *(float *)0x31fb40) {
      return 0;
    }
  }
  return ok;
}



/* FUN_00107db0 (0x107db0) — readable C lift from XBE leaf.
 * Clip ray t-interval against a list of planes (stride 0x1c). */
char FUN_00107db0(int a0, int a1, int a2, int a3, int a4, int a5,
                  int16_t count, float *planes, float *origin, float *direction,
                  float *out_t_neg, float *out_t_pos)
{
  int16_t i;
  float t_neg;
  float t_pos;
  float *plane;
  float numer;
  float denom;
  float abs_denom;
  float t;
  unsigned int bits;

  (void)a0;
  (void)a1;
  (void)a2;
  (void)a3;
  (void)a4;
  (void)a5;

  bits = 0xff7fffffu;
  t_neg = *(float *)&bits;
  bits = 0x7f7fffffu;
  t_pos = *(float *)&bits;

  for (i = 0; i < count; i++) {
    plane = (float *)((char *)planes + (int)i * 0x1c);
    if (*(unsigned char *)plane == 0)
      continue;
    numer = plane[3] * origin[2] + plane[2] * origin[1] + plane[1] * origin[0] -
            plane[4];
    denom = plane[3] * direction[2] + plane[2] * direction[1] +
            plane[1] * direction[0];
    abs_denom = denom;
    if (abs_denom < *(float *)0x2533c0)
      abs_denom = -abs_denom;
    if ((double)abs_denom < *(double *)0x2533d0) {
      if (numer > *(float *)0x31fb40)
        return 0;
    } else {
      t = -numer / denom;
      if (denom > *(float *)0x2533c0) {
        if (t_neg < t)
          t_neg = t;
      } else {
        if (t_pos > t)
          t_pos = t;
      }
      if (t_neg > t_pos)
        return 0;
    }
  }
  if (out_t_neg)
    *out_t_neg = t_neg;
  if (out_t_pos)
    *out_t_pos = t_pos;
  return 1;
}



/* get_edge_vertex (0x107ec0) — readable C lift (restored pre-naked). */
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


/* FUN_00108060 (0x108060) — XBE naked draft (batch 245). */
#if defined(__clang__)
static void (*const b108060_chkstk)(void) = FUN_001d90e0;
static void (*const b108060_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b108060_exitfn)(int) = system_exit;
static float * (*const b108060_c99400)(float *out_line, float *point_a, float *point_b) = plane2d_from_points;
static int16_t (*const b108060_c106510)(int16_t count, float *points, float *line, int16_t max_count, float *out_points, uint32_t *out_bitmask, uint8_t *changed, float epsilon) = convex_polygon2d_clip_to_plane;
static void * (*const b108060_c8e0b0)(void *destination, void *source, size_t size) = csmemcpy;

__attribute__((naked, noinline))
short FUN_00108060(int16_t count __attribute__((unused)), void *records __attribute__((unused)), int a3 __attribute__((unused)), uint16_t *scratch __attribute__((unused)), int max_count __attribute__((unused)), uint16_t *out_list __attribute__((unused)), uint32_t seed __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl $0x200c, %%eax\n\t"
      "call *%[chkstk]\n\t"
      "cmpw $0x200, 0x18(%%ebp)\n\t"
      "pushl %%ebx\n\t"
      "movl 0x14(%%ebp), %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x10(%%ebp), %%edi\n\t"
      "movl %%ebx, 0x10(%%ebp)\n\t"
      "jle .LFUN_00108060_1\n\t"
      "pushl $1\n\t"
      "pushl $0x3f8\n\t"
      "pushl $0x28be44\n\t"
      "pushl $0x28c330\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00108060_1:\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_00108060_2\n\t"
      "pushl $1\n\t"
      "pushl $0x3f9\n\t"
      "pushl $0x28be44\n\t"
      "pushl $0x26856c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00108060_2:\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "testw %%si, %%si\n\t"
      "jne .LFUN_00108060_3\n\t"
      "pushl $1\n\t"
      "pushl $0x3fa\n\t"
      "pushl $0x28be44\n\t"
      "pushl $0x28c328\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00108060_3:\n\t"
      "testl %%ebx, %%ebx\n\t"
      "jne .LFUN_00108060_4\n\t"
      "pushl $1\n\t"
      "pushl $0x3fb\n\t"
      "pushl $0x28be44\n\t"
      "pushl $0x28c324\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00108060_4:\n\t"
      "testw %%di, %%di\n\t"
      "jne .LFUN_00108060_5\n\t"
      "pushl $1\n\t"
      "pushl $0x3fc\n\t"
      "pushl $0x28be44\n\t"
      "pushl $0x28c31c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00108060_5:\n\t"
      "movl 0x1c(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_00108060_6\n\t"
      "pushl $1\n\t"
      "pushl $0x3fd\n\t"
      "pushl $0x28be44\n\t"
      "pushl $0x25f120\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00108060_6:\n\t"
      "movl 0x1c(%%ebp), %%eax\n\t"
      "cmpl %%eax, 0xc(%%ebp)\n\t"
      "je .LFUN_00108060_7\n\t"
      "cmpl %%eax, %%ebx\n\t"
      "jne .LFUN_00108060_8\n\t"
      ".LFUN_00108060_7:\n\t"
      "pushl $1\n\t"
      "pushl $0x3fe\n\t"
      "pushl $0x28be44\n\t"
      "pushl $0x28c304\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00108060_8:\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "testw %%si, %%si\n\t"
      "jg .LFUN_00108060_11\n\t"
      ".LFUN_00108060_9:\n\t"
      "movw %%di, %%ax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00108060_10:\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      ".LFUN_00108060_11:\n\t"
      "testw %%di, %%di\n\t"
      "jle .LFUN_00108060_9\n\t"
      "testw %%bx, %%bx\n\t"
      "leal -0x1(%%ebx), %%ecx\n\t"
      "jne .LFUN_00108060_12\n\t"
      "leal -0x1(%%esi), %%ecx\n\t"
      ".LFUN_00108060_12:\n\t"
      "movswl %%si, %%edx\n\t"
      "movswl %%bx, %%eax\n\t"
      "decl %%edx\n\t"
      "cmpl %%edx, %%eax\n\t"
      "jne .LFUN_00108060_13\n\t"
      "movl 0x1c(%%ebp), %%esi\n\t"
      "jmp .LFUN_00108060_14\n\t"
      ".LFUN_00108060_13:\n\t"
      "movl %%eax, %%edx\n\t"
      "andl $1, %%edx\n\t"
      "shll $0xc, %%edx\n\t"
      "leal -0x200c(%%ebp,%%edx,1), %%esi\n\t"
      ".LFUN_00108060_14:\n\t"
      "movswl %%cx, %%edx\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "leal (%%ecx,%%edx,8), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal (%%ecx,%%eax,8), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0xc(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c99400]\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_00108060_15\n\t"
      "movl 0x20(%%ebp), %%edx\n\t"
      "movl 0x18(%%ebp), %%eax\n\t"
      "pushl %%edx\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "leal -0xc(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "call *%[c106510]\n\t"
      "addl $0x20, %%esp\n\t"
      "movl %%eax, %%edi\n\t"
      "cmpw $-1, %%di\n\t"
      "jne .LFUN_00108060_17\n\t"
      "orw %%di, %%ax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00108060_15:\n\t"
      "cmpw 0x18(%%ebp), %%di\n\t"
      "jle .LFUN_00108060_16\n\t"
      "pushl $1\n\t"
      "pushl $0x40d\n\t"
      "pushl $0x28be44\n\t"
      "pushl $0x28c2d4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00108060_16:\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "movswl %%di, %%eax\n\t"
      "shll $3, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "call *%[c8e0b0]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_00108060_17:\n\t"
      "incl %%ebx\n\t"
      "cmpw 0x8(%%ebp), %%bx\n\t"
      "movl %%esi, 0x10(%%ebp)\n\t"
      "jl .LFUN_00108060_10\n\t"
      "movw %%di, %%ax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [chkstk] "m"(b108060_chkstk), [assert] "m"(b108060_assert), [exitfn] "m"(b108060_exitfn), [c99400] "m"(b108060_c99400), [c106510] "m"(b108060_c106510), [c8e0b0] "m"(b108060_c8e0b0)
      : "memory");
}
#else
#error "FUN_00108060: clang naked draft required"
#endif


/* get_face_vertex (0x108270) — readable C lift (restored pre-naked). */
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


/* subdivide_triangle (0x108400) — readable C lift (restored pre-naked). */
void subdivide_triangle(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* test eax, eax -> jne 0x10843b */
  display_assert((char *)0x0028c5d8, (char *)0x0028be44, 146, 0);
  system_exit(0);
  /* test ebx, ebx -> jne 0x108462 */
  display_assert((char *)0x0028c5b4, (char *)0x0028be44, 147, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x108489 */
  display_assert((char *)0x0028c598, (char *)0x0028be44, 148, 0);
  system_exit(0);
  /* test (int16_t)eax, (int16_t)eax -> jl 0x108497 */
  /* relift: cmp (int16_t)eax, word ptr [esi + 0xc] -> jl 0x1084b7 */
  display_assert((char *)0x0028c570, (char *)0x0028be44, 149, 0);
  system_exit(0);
  /* test (int16_t)eax, (int16_t)eax -> jl 0x1084c5 */
  /* relift: cmp (int16_t)eax, word ptr [esi + 0xc] -> jl 0x1084e5 */
  display_assert((char *)0x0028c548, (char *)0x0028be44, 150, 0);
  system_exit(0);
  /* test (int16_t)eax, (int16_t)eax -> jl 0x1084f3 */
  /* relift: cmp (int16_t)eax, word ptr [esi + 0xc] -> jl 0x108513 */
  display_assert((char *)0x0028c520, (char *)0x0028be44, 151, 0);
  system_exit(0);
  /* cmp ecx, eax -> jl 0x108541 */
  display_assert((char *)0x0028c4b8, (char *)0x0028be44, 152, 0);
  system_exit(0);
  debug_malloc(edx, 0, (char *)0, 0);
  /* test (int16_t)edi, (int16_t)edi -> jle 0x10857e */
  get_face_vertex();
  get_face_vertex();
  get_face_vertex();
  /* relift: cmp (int16_t)eax, word ptr [esi + 0xc] -> jle 0x10866a */
  display_assert((char *)0x0028c47c, (char *)0x0028be44, 176, 0);
  system_exit(0);
  /* test (int16_t)eax, (int16_t)eax -> jl 0x108678 */
  /* relift: cmp (int16_t)eax, word ptr [esi + 0xc] -> jle 0x108698 */
  display_assert((char *)0x0028c444, (char *)0x0028be44, 177, 0);
  system_exit(0);
  /* test (int16_t)edi, (int16_t)edi -> jl 0x1086a3 */
  /* relift: cmp (int16_t)edi, word ptr [esi + 0xc] -> jle 0x1086c3 */
  display_assert((char *)0x0028c408, (char *)0x0028be44, 178, 0);
  system_exit(0);
  /* cmp (int16_t)ebx, (int16_t)eax -> jge 0x10876c */
  get_face_vertex();
  /* relift: cmp (int16_t)eax, word ptr [esi + 0xc] -> jle 0x10875c */
  display_assert((char *)0x0028c3c8, (char *)0x0028be44, 194, 0);
  system_exit(0);
  /* cmp (int16_t)ebx, (int16_t)eax -> jle 0x1085c0 */
  debug_free((void *)(uintptr_t)edx, (char *)0x0028be44, 200);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}


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

/* FUN_001089a0 (0x1089a0) — readable C lift from XBE leaf.
 * Sets rectangle2d as (x0,y0,x1,y1) from (y0,x0,y1,x1) args. */
void FUN_001089a0(int *bounds, int y0, int x0, int y1, int x1)
{
  int16_t *r = (int16_t *)bounds;
  r[1] = (int16_t)y0;
  r[0] = (int16_t)x0;
  r[3] = (int16_t)y1;
  r[2] = (int16_t)x1;
}

/* FUN_001089d0 (0x1089d0) — readable C lift. */
void FUN_001089d0(int *point, int x, int y)
{
  *(short *)point = (short)x;
  *((short *)point + 1) = (short)y;
}


/* FUN_001089f0 (0x1089f0) — readable C lift. */
void FUN_001089f0(int *point, int dx, int dy)
{
  *(short *)point = (short)(*(short *)point + (short)dx);
  *((short *)point + 1) = (short)(*((short *)point + 1) + (short)dy);
}


/* FUN_00108a10 (0x108a10) — readable C lift. */
int FUN_00108a10(int *rect)
{
  short *r = (short *)rect;
  return (int)(unsigned short)r[3] - (int)r[1];
}


/* FUN_00108a30 (0x108a30) — readable C lift. */
int FUN_00108a30(int *rect)
{
  short *r = (short *)rect;
  return (int)(unsigned short)r[2] - (int)r[0];
}


/* FUN_00108a50 (0x108a50) — readable C lift. */
void FUN_00108a50(int *rect, int dy, int dx)
{
  short *r = (short *)rect;
  r[1] = (short)(r[1] + (short)dy);
  r[3] = (short)(r[3] - (short)dy);
  r[0] = (short)(r[0] + (short)dx);
  r[2] = (short)(r[2] - (short)dx);
}


/* FUN_00108a90 (0x108a90) — XBE naked draft (batch 253). */
#if defined(__clang__)
static char * (*const b108a90_c8d9d0)(char *buffer, const char *format, ...) = csprintf;
static void (*const b108a90_assert)(const char *, const char *, int, bool) = display_assert;

__attribute__((naked, noinline))
void FUN_00108a90(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x10, %%esp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x2(%%eax), %%cx\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw (%%eax), %%dx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movw 0x6(%%eax), %%si\n\t"
      "subw %%cx, %%si\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "movw 0x4(%%eax), %%cx\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "subw %%dx, %%cx\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x2(%%eax), %%dx\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "movw (%%eax), %%bx\n\t"
      "pushl %%edi\n\t"
      "movw 0x6(%%eax), %%di\n\t"
      "subw %%dx, %%di\n\t"
      "movl %%edx, 0xc(%%ebp)\n\t"
      "movw 0x4(%%eax), %%dx\n\t"
      "subw %%bx, %%dx\n\t"
      "movl %%ebx, 0x8(%%ebp)\n\t"
      "movl (%%eax), %%ebx\n\t"
      "movl 0x4(%%eax), %%eax\n\t"
      "movl %%ebx, -0x10(%%ebp)\n\t"
      "movswl 0x14(%%ebp), %%ebx\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "movl %%ebx, %%eax\n\t"
      "subl $0, %%eax\n\t"
      "je .LFUN_00108a90_2\n\t"
      "decl %%eax\n\t"
      "je .LFUN_00108a90_1\n\t"
      "pushl $0\n\t"
      "pushl $0xad\n\t"
      "pushl $0x28c6a4\n\t"
      "pushl %%ebx\n\t"
      "pushl $0x28c678\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0xc, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "addl $0x10, %%esp\n\t"
      "jmp .LFUN_00108a90_4\n\t"
      ".LFUN_00108a90_1:\n\t"
      "movswl %%dx, %%edx\n\t"
      "movswl %%cx, %%ecx\n\t"
      "subl %%edx, %%ecx\n\t"
      "movl $0x55555556, %%eax\n\t"
      "imull %%ecx\n\t"
      "movl %%edx, %%ecx\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "movl %%ecx, %%eax\n\t"
      "shrl $0x1f, %%eax\n\t"
      "addl %%eax, %%ecx\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "subl %%edx, %%ecx\n\t"
      "addl %%eax, %%ecx\n\t"
      "movswl %%di, %%edx\n\t"
      "movswl %%si, %%eax\n\t"
      "subl %%edx, %%eax\n\t"
      "cdq\n\t"
      "subl %%edx, %%eax\n\t"
      "sarl $1, %%eax\n\t"
      "jmp .LFUN_00108a90_3\n\t"
      ".LFUN_00108a90_2:\n\t"
      "movswl %%dx, %%eax\n\t"
      "cdq\n\t"
      "subl %%edx, %%eax\n\t"
      "movl %%eax, %%ebx\n\t"
      "movswl %%cx, %%eax\n\t"
      "cdq\n\t"
      "subl %%edx, %%eax\n\t"
      "movl %%eax, %%ecx\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "sarl $1, %%ecx\n\t"
      "sarl $1, %%ebx\n\t"
      "subl %%ebx, %%ecx\n\t"
      "movl -0x4(%%ebp), %%ebx\n\t"
      "subl %%eax, %%ecx\n\t"
      "movswl %%di, %%eax\n\t"
      "cdq\n\t"
      "subl %%edx, %%eax\n\t"
      "movl %%eax, %%edi\n\t"
      "movswl %%si, %%eax\n\t"
      "cdq\n\t"
      "subl %%edx, %%eax\n\t"
      "sarl $1, %%edi\n\t"
      "sarl $1, %%eax\n\t"
      "addl %%ebx, %%ecx\n\t"
      "subl %%edi, %%eax\n\t"
      ".LFUN_00108a90_3:\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "movl -0x8(%%ebp), %%ebx\n\t"
      "addw %%cx, -0x10(%%ebp)\n\t"
      "subl %%edx, %%eax\n\t"
      "addl %%ebx, %%eax\n\t"
      "addw %%ax, -0xa(%%ebp)\n\t"
      "addw %%ax, -0xe(%%ebp)\n\t"
      "addw %%cx, -0xc(%%ebp)\n\t"
      ".LFUN_00108a90_4:\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "movl -0x10(%%ebp), %%ecx\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ecx, (%%eax)\n\t"
      "movl %%edx, 0x4(%%eax)\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c8d9d0] "m"(b108a90_c8d9d0), [assert] "m"(b108a90_assert)
      : "memory");
}
#else
#error "FUN_00108a90: clang naked draft required"
#endif


/* FUN_00108bc0 (0x108bc0) — readable C lift from XBE leaf.
 * Intersect two rectangle2d {top,left,bottom,right}; write result or zero. */
char FUN_00108bc0(int16_t *a, int16_t *b, int16_t *out)
{
  int16_t left;
  int16_t right;
  int16_t top;
  int16_t bottom;

  left = a[1];
  if (left <= b[1])
    left = b[1];
  right = b[3];
  if (a[3] <= b[3])
    right = a[3];
  top = b[0];
  if (a[0] > b[0])
    top = a[0];
  bottom = a[2];
  if (a[2] > b[2])
    bottom = b[2];

  if (left < right && top < bottom) {
    out[0] = top;
    out[1] = left;
    out[2] = bottom;
    out[3] = right;
    return 1;
  }
  csmemset(out, 0, 8);
  return 0;
}

/* FUN_00108c60 (0x108c60) — readable C lift. */
void FUN_00108c60(int16_t *a, int16_t *b, int16_t *out)
{
  out[1] = (a[1] > b[1]) ? a[1] : b[1];
  out[3] = (a[3] < b[3]) ? a[3] : b[3];
  out[0] = (a[0] > b[0]) ? a[0] : b[0];
  out[2] = (a[2] < b[2]) ? a[2] : b[2];
}

/* FUN_00108cd0 (0x108cd0) — readable C lift. */
char FUN_00108cd0(int *rect, int *point)
{
  short *r = (short *)rect;
  short *p = (short *)point;
  return p[0] >= r[1] && p[0] < r[3] && p[1] >= r[0] && p[1] < r[2];
}

/* FUN_00108d00 (0x108d00) — readable C lift: rectangle2d containment. */
int FUN_00108d00(int16_t *outer, int16_t *inner)
{
  if (inner[1] < outer[1])
    return 0;
  if (inner[3] > outer[3])
    return 0;
  if (inner[0] < outer[0])
    return 0;
  if (inner[2] > outer[2])
    return 0;
  return 1;
}

/* FUN_00108d40 (0x108d40) — readable C lift: rectangle2d equal. */
int FUN_00108d40(int16_t *a, int16_t *b)
{
  if (a[1] != b[1])
    return 0;
  if (a[3] != b[3])
    return 0;
  if (a[0] != b[0])
    return 0;
  if (a[2] != b[2])
    return 0;
  return 1;
}

/* FUN_00108d80 (0x108d80) — readable C lift: point2d equal. */
int FUN_00108d80(int16_t *a, int16_t *b)
{
  if (a[0] != b[0])
    return 0;
  if (a[1] != b[1])
    return 0;
  return 1;
}

/* FUN_00108e20 (0x108e20) — readable C lift: next power-of-two (u16). */
int FUN_00108e20(unsigned int value)
{
  unsigned int v;
  int pow2;

  v = (unsigned int)(unsigned short)value;
  pow2 = 1;
  if ((int)v <= pow2)
    return pow2;
  do {
    pow2 <<= 1;
  } while (pow2 < (int)v);
  return pow2;
}

/* FUN_00108e40 (0x108e40) — readable C lift: integer square root. */
unsigned int FUN_00108e40(unsigned int n)
{
  unsigned int rem;
  unsigned int root;
  unsigned int bit;
  unsigned int trial;

  rem = n;
  root = 0;
  bit = 0x40000000u;
  while (bit != 0) {
    trial = bit + root;
    if (trial <= rem) {
      rem -= trial;
      root = trial + bit;
    }
    bit >>= 2;
    root >>= 1;
  }
  if (rem > root)
    root++;
  return root;
}

