#include <stdint.h>
/* Return pointer to a cluster's sound bit-vector data (0x193550).
 * Computes BIT_VECTOR_SIZE_IN_LONGS from clusters.count, then indexes
 * into cluster_data.elements by cluster_index * that stride. */
uint32_t *structure_bsp_get_cluster_sound_data(void *bsp, int16_t cluster_index)
{
  char *b = (char *)bsp;
  int count = *(int *)(b + 0x134);
  int bit_vector_longs;

  if (cluster_index < 0 || (int)cluster_index >= count) {
    display_assert(
      "cluster_index>=0 && cluster_index<structure_bsp->clusters.count",
      "c:\\halo\\SOURCE\\structures\\structure_bsp_definitions.c", 0x24, 1);
    system_exit(-1);
  }

  bit_vector_longs = (count + 0x1f) >> 5;

  if ((int16_t)(cluster_index + 1) * bit_vector_longs > *(int *)(b + 0x140)) {
    display_assert("(cluster_index+1)*BIT_VECTOR_SIZE_IN_LONGS(structure_bsp->"
                   "clusters.count)<=structure_bsp->cluster_data.size",
                   "c:\\halo\\SOURCE\\structures\\structure_bsp_definitions.c",
                   0x25, 1);
    system_exit(-1);
  }

  return (uint32_t *)(*(int *)(b + 0x14c) +
                      bit_vector_longs * (int)cluster_index * 4);
}

/* Return a pointer to the sound encoding byte for a cluster pair (0x1937d0).
 * Uses upper-triangular matrix indexing (row < column, no diagonal)
 * into sound_cluster_data. */
uint8_t *structure_bsp_get_cluster_encoded_sound_data(void *bsp,
                                                      int16_t from_cluster,
                                                      int16_t to_cluster)
{
  char *b = (char *)bsp;
  int16_t offset;

  offset = (int16_t)((*(int16_t *)(b + 0x134) - 1) * from_cluster -
                     (from_cluster + 1) * from_cluster / 2 + to_cluster - 1);

  if (to_cluster <= from_cluster) {
    display_assert("row_index<column_index",
                   "c:\\halo\\SOURCE\\structures\\structure_bsp_definitions.c",
                   0x4b2, 1);
    system_exit(-1);
  }

  if (offset < 0 || offset >= *(int *)(b + 0x214)) {
    display_assert("offset>=0 && offset<structure_bsp->sound_cluster_data.size",
                   "c:\\halo\\SOURCE\\structures\\structure_bsp_definitions.c",
                   0x4b3, 1);
    system_exit(-1);
  }

  return (uint8_t *)(*(int *)(b + 0x220) + offset);
}

/* Look up the sound encoding byte between two clusters (0x193870).
 * Ensures from < to by swapping if necessary, then delegates to
 * structure_bsp_get_cluster_encoded_sound_data for the actual lookup. Returns 0
 * for same-cluster. */
uint8_t structure_bsp_cluster_sound_encoding(void *bsp, int16_t from_cluster,
                                             int16_t to_cluster)
{
  char *b = (char *)bsp;

  if (from_cluster < 0 || (int)from_cluster >= *(int *)(b + 0x134)) {
    display_assert("from_cluster_index>=0 && from_cluster_index<structure_bsp->"
                   "clusters.count",
                   "c:\\halo\\SOURCE\\structures\\structure_bsp_definitions.c",
                   0x4bf, 1);
    system_exit(-1);
  }
  if (to_cluster < 0 || (int)to_cluster >= *(int *)(b + 0x134)) {
    display_assert("to_cluster_index>=0 && to_cluster_index<structure_bsp->"
                   "clusters.count",
                   "c:\\halo\\SOURCE\\structures\\structure_bsp_definitions.c",
                   0x4c0, 1);
    system_exit(-1);
  }

  if (from_cluster == to_cluster)
    return 0;

  if (from_cluster > to_cluster) {
    int16_t tmp = from_cluster;
    from_cluster = to_cluster;
    to_cluster = tmp;
  }

  return *structure_bsp_get_cluster_encoded_sound_data(bsp, from_cluster,
                                                       to_cluster);
}
/* --- structure_bsp_definitions.obj batch drafts (2026-07-26) --- */

/* FUN_001929a0 (0x1929a0) — readable C lift from XBE leaf.
 * Project leaf-face vertex (EAX=face, ECX=leaf_map) onto plane basis. */
void FUN_001929a0(void *face /*@<eax>*/, void *leaf_map /*@<ecx>*/,
                  short vertex_index, float *out_point)
{
  float *plane;
  float ax, ay, az;
  int proj;
  uint8_t sign;
  int *node;

  node = (int *)tag_block_get_element(*(void **)leaf_map, *(int *)face, 0xc);
  plane = (float *)tag_block_get_element((char *)*(void **)leaf_map + 0xc,
                                         node[0], 0x10);
  ax = fabsf(plane[0]);
  ay = fabsf(plane[1]);
  az = fabsf(plane[2]);
  if (!(az < ay) && !(az < ax))
    proj = 2;
  else if (!(ay < ax))
    proj = 1;
  else
    proj = 0;
  sign = FUN_00099270(plane, (uint32_t)proj);
  project_point2d(
      (float *)tag_block_get_element((char *)face + 4, vertex_index, 8), plane,
      (int16_t)proj, sign, out_point);
}

/* render_debug_leaf_faces (0x192a50) — XBE naked draft (batch 123). */
#if defined(__clang__)
static void *(*const b192a50_elem)(void *, int, int) = tag_block_get_element;
static void (*const b192a50_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b192a50_exitfn)(int) = system_exit;
static void (*const b192a50_c1929a0)(void) = (void (*)(void))FUN_001929a0;
static void (*const b192a50_c189270)(char flag, float *point_a, float *point_b, void *color) = FUN_00189270;
static void (*const b192a50_c188890)(char flag, float *point0, float *point1, float *point2, void *color) = FUN_00188890;

__attribute__((naked, noinline))
void render_debug_leaf_faces(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x40, %%esp\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "pushl %%ebx\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl $0x18\n\t"
      "andl $0x7fffffff, %%eax\n\t"
      "pushl %%eax\n\t"
      "leal 0x4(%%ebx), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[elem]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl (%%ebx), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%esi, 0x8(%%ebp)\n\t"
      "movl $0x3e4ccccd, -0x40(%%ebp)\n\t"
      "movl $0x3f800000, -0x3c(%%ebp)\n\t"
      "movl $0, -0x38(%%ebp)\n\t"
      "movl $0, -0x34(%%ebp)\n\t"
      "jne .Lrender_debug_leaf_faces_1\n\t"
      "pushl $1\n\t"
      "pushl $0x3ac\n\t"
      "pushl $0x2b28b4\n\t"
      "pushl $0x2b2a04\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrender_debug_leaf_faces_1:\n\t"
      "cmpl $0, (%%esi)\n\t"
      "movl $0, 0xc(%%ebp)\n\t"
      "jle .Lrender_debug_leaf_faces_6\n\t"
      "pushl %%edi\n\t"
      "xorl %%eax, %%eax\n\t"
      "jmp .Lrender_debug_leaf_faces_3\n\t"
      ".Lrender_debug_leaf_faces_2:\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      ".Lrender_debug_leaf_faces_3:\n\t"
      "pushl $0x10\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[elem]\n\t"
      "leal -0x30(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0\n\t"
      "movl %%ebx, %%ecx\n\t"
      "movl %%eax, %%esi\n\t"
      "call *%[c1929a0]\n\t"
      "leal -0x24(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $1\n\t"
      "movl %%esi, %%eax\n\t"
      "movl %%ebx, %%ecx\n\t"
      "call *%[c1929a0]\n\t"
      "movl -0x24(%%ebp), %%ecx\n\t"
      "movl -0x20(%%ebp), %%edx\n\t"
      "movl -0x1c(%%ebp), %%eax\n\t"
      "movl %%ecx, -0xc(%%ebp)\n\t"
      "movl 0x2ee6c4, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl %%edx, -0x8(%%ebp)\n\t"
      "leal -0x24(%%ebp), %%edx\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "pushl %%edx\n\t"
      "leal -0x30(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $1\n\t"
      "call *%[c189270]\n\t"
      "movl 0x4(%%esi), %%eax\n\t"
      "movl $2, %%edi\n\t"
      "addl $0x2c, %%esp\n\t"
      "cmpl %%edi, %%eax\n\t"
      "jle .Lrender_debug_leaf_faces_5\n\t"
      "nop\n\t"
      ".Lrender_debug_leaf_faces_4:\n\t"
      "leal -0x18(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edi\n\t"
      "movl %%esi, %%eax\n\t"
      "movl %%ebx, %%ecx\n\t"
      "call *%[c1929a0]\n\t"
      "leal -0x40(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x18(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0xc(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x30(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $1\n\t"
      "call *%[c188890]\n\t"
      "movl 0x2ee6c4, %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x18(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0xc(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $1\n\t"
      "call *%[c189270]\n\t"
      "movl -0x18(%%ebp), %%eax\n\t"
      "movl -0x14(%%ebp), %%ecx\n\t"
      "movl -0x10(%%ebp), %%edx\n\t"
      "addl $0x2c, %%esp\n\t"
      "incl %%edi\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "movswl %%di, %%eax\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      "cmpl 0x4(%%esi), %%eax\n\t"
      "jl .Lrender_debug_leaf_faces_4\n\t"
      ".Lrender_debug_leaf_faces_5:\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "movl (%%ecx), %%edx\n\t"
      "incl %%eax\n\t"
      "movl %%eax, 0xc(%%ebp)\n\t"
      "movswl %%ax, %%eax\n\t"
      "cmpl %%edx, %%eax\n\t"
      "jl .Lrender_debug_leaf_faces_2\n\t"
      "popl %%edi\n\t"
      ".Lrender_debug_leaf_faces_6:\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [elem] "m"(b192a50_elem), [assert] "m"(b192a50_assert), [exitfn] "m"(b192a50_exitfn), [c1929a0] "m"(b192a50_c1929a0), [c189270] "m"(b192a50_c189270), [c188890] "m"(b192a50_c188890)
      : "memory");
}
#else
#error "render_debug_leaf_faces: clang naked draft required"
#endif


/* FUN_00192bb0 (0x192bb0) — readable C lift from XBE leaf.
 * Normalize vector in place; return original length, or 0 on Inf/invalid. */
float FUN_00192bb0(float *v)
{
  float mag;
  float scale;
  uint32_t scale_bits;

  mag = sqrtf(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
  scale = *(float *)0x2533c8 / mag;
  scale_bits = *(uint32_t *)&scale;
  if ((scale_bits & 0x7f800000u) == 0x7f800000u)
    return *(float *)0x2533c0;
  v[0] *= scale;
  v[1] *= scale;
  v[2] *= scale;
  if (!valid_real_normal3d(v))
    return *(float *)0x2533c0;
  return mag;
}


/* intersect_planes3d (0x192c30) — XBE naked draft (batch 121). */
#if defined(__clang__)
static void (*const b192c30_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b192c30_exitfn)(int) = system_exit;
static float (*const b192c30_c192bb0)(float *) = (void *)FUN_00192bb0;
static uint8_t (*const b192c30_c99270)(float *plane, uint32_t basis) = FUN_00099270;
static void (*const b192c30_c61df0)(void *point, short projection, unsigned char sign, void *out_projected) = FUN_00061df0;

__attribute__((naked, noinline))
void intersect_planes3d(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x10, %%esp\n\t"
      "flds (%%esi)\n\t"
      "pushl %%ebx\n\t"
      "fabs\n\t"
      "pushl %%edi\n\t"
      "flds 0x4(%%esi)\n\t"
      "fabs\n\t"
      "flds 0x8(%%esi)\n\t"
      "fabs\n\t"
      ".byte 0xd8, 0xd1\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .Lintersect_planes3d_1\n\t"
      "fcomp %%st(2)\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .Lintersect_planes3d_2\n\t"
      "fstp %%st(0)\n\t"
      "movl $2, %%ebx\n\t"
      "fstp %%st(0)\n\t"
      "jmp .Lintersect_planes3d_4\n\t"
      ".Lintersect_planes3d_1:\n\t"
      "fstp %%st(0)\n\t"
      ".Lintersect_planes3d_2:\n\t"
      "fcomp %%st(1)\n\t"
      "fnstsw %%ax\n\t"
      "fstp %%st(0)\n\t"
      "testb $1, %%ah\n\t"
      "jne .Lintersect_planes3d_3\n\t"
      "movl $1, %%ebx\n\t"
      "jmp .Lintersect_planes3d_4\n\t"
      ".Lintersect_planes3d_3:\n\t"
      "xorl %%ebx, %%ebx\n\t"
      ".Lintersect_planes3d_4:\n\t"
      "movswl %%bx, %%edi\n\t"
      "shll $2, %%edi\n\t"
      "flds (%%edi,%%esi,1)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .Lintersect_planes3d_5\n\t"
      "pushl $1\n\t"
      "pushl $0x12b\n\t"
      "pushl $0x2b28b4\n\t"
      "pushl $0x2b2a10\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lintersect_planes3d_5:\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lintersect_planes3d_6\n\t"
      "pushl $1\n\t"
      "pushl $0x12c\n\t"
      "pushl $0x2b28b4\n\t"
      "pushl $0x25f120\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lintersect_planes3d_6:\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "flds (%%edi,%%ecx,1)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .Lintersect_planes3d_7\n\t"
      "movl (%%ecx), %%eax\n\t"
      "movl 0x4(%%ecx), %%edx\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "movl 0x8(%%ecx), %%eax\n\t"
      "movl 0xc(%%ecx), %%ecx\n\t"
      "movl %%edx, -0xc(%%ebp)\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "movl %%ecx, -0x4(%%ebp)\n\t"
      "jmp .Lintersect_planes3d_8\n\t"
      ".Lintersect_planes3d_7:\n\t"
      "flds (%%edi,%%ecx,1)\n\t"
      "fdivs (%%edi,%%esi,1)\n\t"
      "fld %%st(0)\n\t"
      "fmuls (%%esi)\n\t"
      "fsubrs (%%ecx)\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "fld %%st(0)\n\t"
      "fmuls 0x4(%%esi)\n\t"
      "fsubrs 0x4(%%ecx)\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "fld %%st(0)\n\t"
      "fmuls 0x8(%%esi)\n\t"
      "fsubrs 0x8(%%ecx)\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "fmuls 0xc(%%esi)\n\t"
      "fsubrs 0xc(%%ecx)\n\t"
      "fstps -0x4(%%ebp)\n\t"
      ".Lintersect_planes3d_8:\n\t"
      "leal -0x10(%%ebp), %%eax\n\t"
      "call *%[c192bb0]\n\t"
      "fsts 0x8(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .Lintersect_planes3d_9\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "call *%[c99270]\n\t"
      "addl $8, %%esp\n\t"
      "leal -0x10(%%ebp), %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edx\n\t"
      "call *%[c61df0]\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fdivs 0x8(%%ebp)\n\t"
      "addl $0x10, %%esp\n\t"
      "movw $1, %%ax\n\t"
      "fstps 0x8(%%edi)\n\t"
      "popl %%edi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lintersect_planes3d_9:\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lintersect_planes3d_10\n\t"
      "popl %%edi\n\t"
      "xorw %%ax, %%ax\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lintersect_planes3d_10:\n\t"
      "popl %%edi\n\t"
      "movw $2, %%ax\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b192c30_assert), [exitfn] "m"(b192c30_exitfn), [c192bb0] "m"(b192c30_c192bb0), [c99270] "m"(b192c30_c99270), [c61df0] "m"(b192c30_c61df0)
      : "memory");
}
#else
#error "intersect_planes3d: clang naked draft required"
#endif


/* leaf_map_build_portals_from_leaf (0x192da0) — XBE naked draft (batch 115). */
#if defined(__clang__)
static void *(*const b192da0_elem)(void *, int, int) = tag_block_get_element;
static void (*const b192da0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b192da0_exitfn)(int) = system_exit;
static char (*const b192da0_c191bd0)(int search_value, void **param_1, char *out) = FUN_00191bd0;
static void (*const b192da0_c192050)(void) = (void (*)(void))leaf_map_build_portal_from_leaves;
static void (*const b192da0_c192da0)(void) = (void (*)(void))leaf_map_build_portals_from_leaf;

__attribute__((naked, noinline))
void leaf_map_build_portals_from_leaf(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x10, %%esp\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "pushl %%ebx\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "movl (%%ebx), %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl $0xc\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[elem]\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl $-1, %%edi\n\t"
      "movl %%eax, %%esi\n\t"
      "movl %%esi, -0x10(%%ebp)\n\t"
      "jne .Lleaf_map_build_portals_from_leaf_3\n\t"
      "movl 0x18(%%ebp), %%eax\n\t"
      "testw %%ax, %%ax\n\t"
      "jl .Lleaf_map_build_portals_from_leaf_1\n\t"
      "cmpw 0x4d8e90, %%ax\n\t"
      "jl .Lleaf_map_build_portals_from_leaf_2\n\t"
      ".Lleaf_map_build_portals_from_leaf_1:\n\t"
      "pushl $1\n\t"
      "pushl $0x3b\n\t"
      "pushl $0x2b28b4\n\t"
      "pushl $0x2b2900\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "movl 0x18(%%ebp), %%eax\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lleaf_map_build_portals_from_leaf_2:\n\t"
      "movswl 0x4d8e90, %%edx\n\t"
      "movswl %%ax, %%eax\n\t"
      "subl %%eax, %%edx\n\t"
      "movl 0x4d8a8c(,%%edx,4), %%ecx\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "jmp .Lleaf_map_build_portals_from_leaf_4\n\t"
      ".Lleaf_map_build_portals_from_leaf_3:\n\t"
      "movl $0xffffffff, -0x8(%%ebp)\n\t"
      ".Lleaf_map_build_portals_from_leaf_4:\n\t"
      "leal -0x3(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ebx\n\t"
      "movl (%%esi), %%ebx\n\t"
      "call *%[c191bd0]\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%edi\n\t"
      "movb %%al, -0x2(%%ebp)\n\t"
      "jne .Lleaf_map_build_portals_from_leaf_5\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      "andl $0x7fffffff, %%eax\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "je .Lleaf_map_build_portals_from_leaf_5\n\t"
      "pushl $1\n\t"
      "pushl $0x19f\n\t"
      "pushl $0x2b28b4\n\t"
      "pushl $0x2b2a38\n\t"
      "call *%[assert]\n\t"
      "pushl %%edi\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lleaf_map_build_portals_from_leaf_5:\n\t"
      "movl 0x10(%%ebp), %%esi\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "movl %%ebx, -0xc(%%ebp)\n\t"
      ".Lleaf_map_build_portals_from_leaf_6:\n\t"
      "cmpl $-1, %%edi\n\t"
      "jne .Lleaf_map_build_portals_from_leaf_7\n\t"
      "testw %%bx, %%bx\n\t"
      "je .Lleaf_map_build_portals_from_leaf_7\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jns .Lleaf_map_build_portals_from_leaf_7\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "jmp .Lleaf_map_build_portals_from_leaf_8\n\t"
      ".Lleaf_map_build_portals_from_leaf_7:\n\t"
      "cmpl $-1, %%edi\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "jne .Lleaf_map_build_portals_from_leaf_15\n\t"
      ".Lleaf_map_build_portals_from_leaf_8:\n\t"
      "testw %%bx, %%bx\n\t"
      "jne .Lleaf_map_build_portals_from_leaf_9\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jns .Lleaf_map_build_portals_from_leaf_13\n\t"
      ".Lleaf_map_build_portals_from_leaf_9:\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lleaf_map_build_portals_from_leaf_16\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "movl %%esi, %%ecx\n\t"
      "pushl $0x18\n\t"
      "andl $0x7fffffff, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "addl $4, %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[elem]\n\t"
      "movl %%eax, %%edi\n\t"
      "movl (%%edi), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "testl %%eax, %%eax\n\t"
      "jle .Lleaf_map_build_portals_from_leaf_11\n\t"
      "xorl %%eax, %%eax\n\t"
      ".Lleaf_map_build_portals_from_leaf_10:\n\t"
      "pushl $0x10\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "call *%[elem]\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      "movl (%%eax), %%edx\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl %%ecx, %%edx\n\t"
      "je .Lleaf_map_build_portals_from_leaf_14\n\t"
      "movl (%%edi), %%ecx\n\t"
      "incl %%ebx\n\t"
      "movswl %%bx, %%eax\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jl .Lleaf_map_build_portals_from_leaf_10\n\t"
      ".Lleaf_map_build_portals_from_leaf_11:\n\t"
      "movl -0xc(%%ebp), %%ebx\n\t"
      ".Lleaf_map_build_portals_from_leaf_12:\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      ".Lleaf_map_build_portals_from_leaf_13:\n\t"
      "incl %%ebx\n\t"
      "cmpw $2, %%bx\n\t"
      "movl %%ebx, -0xc(%%ebp)\n\t"
      "jl .Lleaf_map_build_portals_from_leaf_6\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lleaf_map_build_portals_from_leaf_14:\n\t"
      "cmpw $-1, %%bx\n\t"
      "je .Lleaf_map_build_portals_from_leaf_11\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "movl -0xc(%%ebp), %%ebx\n\t"
      "jmp .Lleaf_map_build_portals_from_leaf_16\n\t"
      ".Lleaf_map_build_portals_from_leaf_15:\n\t"
      "movb -0x2(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lleaf_map_build_portals_from_leaf_16\n\t"
      "movzbl -0x3(%%ebp), %%edx\n\t"
      "cmpw %%bx, %%dx\n\t"
      "je .Lleaf_map_build_portals_from_leaf_13\n\t"
      ".Lleaf_map_build_portals_from_leaf_16:\n\t"
      "movl -0x10(%%ebp), %%ecx\n\t"
      "movswl %%bx, %%eax\n\t"
      "movl 0x4(%%ecx,%%eax,4), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jns .Lleaf_map_build_portals_from_leaf_18\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lleaf_map_build_portals_from_leaf_13\n\t"
      "movl %%eax, %%edx\n\t"
      "andl $0x7fffffff, %%edx\n\t"
      "cmpl %%esi, %%edx\n\t"
      "je .Lleaf_map_build_portals_from_leaf_13\n\t"
      "movb -0x1(%%ebp), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      "jne .Lleaf_map_build_portals_from_leaf_17\n\t"
      "movl %%edi, %%ecx\n\t"
      ".Lleaf_map_build_portals_from_leaf_17:\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%ecx\n\t"
      "call *%[c192050]\n\t"
      "addl $0xc, %%esp\n\t"
      "jmp .Lleaf_map_build_portals_from_leaf_12\n\t"
      ".Lleaf_map_build_portals_from_leaf_18:\n\t"
      "movb -0x1(%%ebp), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      "jne .Lleaf_map_build_portals_from_leaf_19\n\t"
      "movl %%edi, %%ecx\n\t"
      ".Lleaf_map_build_portals_from_leaf_19:\n\t"
      "movl 0x18(%%ebp), %%edx\n\t"
      "decl %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "call *%[c192da0]\n\t"
      "addl $0x14, %%esp\n\t"
      "jmp .Lleaf_map_build_portals_from_leaf_13\n\t"
      :
      : [elem] "m"(b192da0_elem), [assert] "m"(b192da0_assert), [exitfn] "m"(b192da0_exitfn), [c191bd0] "m"(b192da0_c191bd0), [c192050] "m"(b192da0_c192050), [c192da0] "m"(b192da0_c192da0)
      : "memory");
}
#else
#error "leaf_map_build_portals_from_leaf: clang naked draft required"
#endif


/* leaf_map_build_leaf_face_for_leaf_on_node (0x192f80) — XBE naked draft (batch 114). */
#if defined(__clang__)
static void *(*const b192f80_elem)(void *, int, int) = tag_block_get_element;
static void (*const b192f80_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b192f80_exitfn)(int) = system_exit;
static void (*const b192f80_c192c30)(void) = (void (*)(void))intersect_planes3d;
static int16_t (*const b192f80_c106510)(int16_t count, float *points, float *line, int16_t max_count, float *out_points, uint32_t *out_bitmask, uint8_t *changed, float epsilon) = convex_polygon2d_clip_to_plane;
static int16_t (*const b192f80_c1b9ad0)(void *tag_block) = tag_block_add_element;
static bool (*const b192f80_c1b9a90)(void *block, int count) = tag_block_resize;
static void * (*const b192f80_c8e0b0)(void *destination, void *source, size_t size) = csmemcpy;

__attribute__((naked, noinline))
void leaf_map_build_leaf_face_for_leaf_on_node(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x228, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "pushl %%edi\n\t"
      "andl $0x7fffffff, %%eax\n\t"
      "pushl $0xc\n\t"
      "pushl %%eax\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "movl (%%ebx), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl (%%eax), %%ecx\n\t"
      "movl (%%ebx), %%edx\n\t"
      "pushl $0x10\n\t"
      "pushl %%ecx\n\t"
      "addl $0xc, %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[elem]\n\t"
      "movl $0x81, %%ecx\n\t"
      "movl $0x3271e0, %%esi\n\t"
      "leal -0x228(%%ebp), %%edi\n\t"
      "movl %%eax, -0x18(%%ebp)\n\t"
      "movw 0x4d8e90, %%ax\n\t"
      "rep movsl\n\t"
      "addl $0x18, %%esp\n\t"
      "xorl %%edi, %%edi\n\t"
      "testw %%ax, %%ax\n\t"
      "jle .Lleaf_map_build_leaf_face_for_leaf_on_node_7\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".Lleaf_map_build_leaf_face_for_leaf_on_node_1:\n\t"
      "cmpw $0, -0x228(%%ebp)\n\t"
      "je .Lleaf_map_build_leaf_face_for_leaf_on_node_10\n\t"
      "testw %%di, %%di\n\t"
      "jl .Lleaf_map_build_leaf_face_for_leaf_on_node_2\n\t"
      "cmpw %%ax, %%di\n\t"
      "jl .Lleaf_map_build_leaf_face_for_leaf_on_node_3\n\t"
      ".Lleaf_map_build_leaf_face_for_leaf_on_node_2:\n\t"
      "pushl $1\n\t"
      "pushl $0x3b\n\t"
      "pushl $0x2b28b4\n\t"
      "pushl $0x2b2900\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lleaf_map_build_leaf_face_for_leaf_on_node_3:\n\t"
      "movswl 0x4d8e90, %%eax\n\t"
      "movswl %%di, %%ecx\n\t"
      "subl %%ecx, %%eax\n\t"
      "movl 0x4d8a8c(,%%eax,4), %%esi\n\t"
      "cmpl 0xc(%%ebp), %%esi\n\t"
      "je .Lleaf_map_build_leaf_face_for_leaf_on_node_6\n\t"
      "movl (%%ebx), %%eax\n\t"
      "movl %%esi, %%edx\n\t"
      "pushl $0xc\n\t"
      "andl $0x7fffffff, %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl (%%eax), %%ecx\n\t"
      "movl (%%ebx), %%edx\n\t"
      "pushl $0x10\n\t"
      "pushl %%ecx\n\t"
      "addl $0xc, %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[elem]\n\t"
      "movl (%%eax), %%ecx\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl %%ecx, -0x10(%%ebp)\n\t"
      "movl 0x8(%%eax), %%ecx\n\t"
      "movl %%edx, -0xc(%%ebp)\n\t"
      "movl 0xc(%%eax), %%edx\n\t"
      "addl $0x18, %%esp\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      "jns .Lleaf_map_build_leaf_face_for_leaf_on_node_4\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fchs\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fchs\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fchs\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fchs\n\t"
      "fstps -0x4(%%ebp)\n\t"
      ".Lleaf_map_build_leaf_face_for_leaf_on_node_4:\n\t"
      "movl -0x18(%%ebp), %%esi\n\t"
      "leal -0x24(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x10(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c192c30]\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $1, %%ax\n\t"
      "jne .Lleaf_map_build_leaf_face_for_leaf_on_node_5\n\t"
      "pushl $0x39800000\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "leal -0x224(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl -0x228(%%ebp), %%edx\n\t"
      "pushl $0x40\n\t"
      "leal -0x24(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x224(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c106510]\n\t"
      "addl $0x20, %%esp\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "movw %%ax, -0x228(%%ebp)\n\t"
      "jne .Lleaf_map_build_leaf_face_for_leaf_on_node_6\n\t"
      "pushl $1\n\t"
      "pushl $0xe3\n\t"
      "pushl $0x2b28b4\n\t"
      "pushl $0x2b2acc\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "jmp .Lleaf_map_build_leaf_face_for_leaf_on_node_6\n\t"
      ".Lleaf_map_build_leaf_face_for_leaf_on_node_5:\n\t"
      "testw %%ax, %%ax\n\t"
      "jne .Lleaf_map_build_leaf_face_for_leaf_on_node_6\n\t"
      "movw %%ax, -0x228(%%ebp)\n\t"
      ".Lleaf_map_build_leaf_face_for_leaf_on_node_6:\n\t"
      "movw 0x4d8e90, %%ax\n\t"
      "incl %%edi\n\t"
      "cmpw %%ax, %%di\n\t"
      "jl .Lleaf_map_build_leaf_face_for_leaf_on_node_1\n\t"
      ".Lleaf_map_build_leaf_face_for_leaf_on_node_7:\n\t"
      "cmpw $0, -0x228(%%ebp)\n\t"
      "je .Lleaf_map_build_leaf_face_for_leaf_on_node_10\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl $0x18\n\t"
      "andl $0x7fffffff, %%eax\n\t"
      "pushl %%eax\n\t"
      "addl $4, %%ebx\n\t"
      "pushl %%ebx\n\t"
      "call *%[elem]\n\t"
      "movl %%eax, %%esi\n\t"
      "pushl %%esi\n\t"
      "call *%[c1b9ad0]\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .Lleaf_map_build_leaf_face_for_leaf_on_node_9\n\t"
      "movswl %%ax, %%eax\n\t"
      "pushl $0x10\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[elem]\n\t"
      "movl -0x14(%%ebp), %%ecx\n\t"
      "movl %%eax, %%esi\n\t"
      "movl %%ecx, (%%esi)\n\t"
      "movswl -0x228(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal 0x4(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1b9a90]\n\t"
      "addl $0x14, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lleaf_map_build_leaf_face_for_leaf_on_node_8\n\t"
      "movswl -0x228(%%ebp), %%ecx\n\t"
      "movl 0x8(%%esi), %%eax\n\t"
      "shll $3, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x224(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c8e0b0]\n\t"
      "addl $0xc, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lleaf_map_build_leaf_face_for_leaf_on_node_8:\n\t"
      "movl 0x4d8e94, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lleaf_map_build_leaf_face_for_leaf_on_node_10\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl $0x2b2aa8, 0x4d8e94\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lleaf_map_build_leaf_face_for_leaf_on_node_9:\n\t"
      "movl 0x4d8e94, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lleaf_map_build_leaf_face_for_leaf_on_node_10\n\t"
      "movl $0x2b2a88, 0x4d8e94\n\t"
      ".Lleaf_map_build_leaf_face_for_leaf_on_node_10:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [elem] "m"(b192f80_elem), [assert] "m"(b192f80_assert), [exitfn] "m"(b192f80_exitfn), [c192c30] "m"(b192f80_c192c30), [c106510] "m"(b192f80_c106510), [c1b9ad0] "m"(b192f80_c1b9ad0), [c1b9a90] "m"(b192f80_c1b9a90), [c8e0b0] "m"(b192f80_c8e0b0)
      : "memory");
}
#else
#error "leaf_map_build_leaf_face_for_leaf_on_node: clang naked draft required"
#endif


/* FUN_001931e0 (0x1931e0) — XBE naked draft (batch 135). */
#if defined(__clang__)
static void *(*const b1931e0_elem)(void *, int, int) = tag_block_get_element;
static void (*const b1931e0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1931e0_exitfn)(int) = system_exit;
static void (*const b1931e0_c192da0)(void) = (void (*)(void))leaf_map_build_portals_from_leaf;
static void (*const b1931e0_c1931e0)(void) = (void (*)(void))FUN_001931e0;

__attribute__((naked, noinline))
void FUN_001931e0(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "movl (%%ebx), %%eax\n\t"
      "pushl %%esi\n\t"
      "movl 0xc(%%ebp), %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl $0xc\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "addl $0xc, %%esp\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "xorl %%edi, %%edi\n\t"
      "jmp .LFUN_001931e0_2\n\t"
      ".LFUN_001931e0_1:\n\t"
      "movl 0xc(%%ebp), %%esi\n\t"
      ".LFUN_001931e0_2:\n\t"
      "testw %%di, %%di\n\t"
      "jne .LFUN_001931e0_3\n\t"
      "orl $0x80000000, %%esi\n\t"
      ".LFUN_001931e0_3:\n\t"
      "cmpw $0x100, 0x4d8e90\n\t"
      "jl .LFUN_001931e0_4\n\t"
      "pushl $1\n\t"
      "pushl $0x2a\n\t"
      "pushl $0x2b28b4\n\t"
      "pushl $0x2b2878\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001931e0_4:\n\t"
      "movswl 0x4d8e90, %%ecx\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movswl %%di, %%edx\n\t"
      "movl %%esi, 0x4d8a90(,%%ecx,4)\n\t"
      "incw 0x4d8e90\n\t"
      "movl 0x4(%%eax,%%edx,4), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jns .LFUN_001931e0_5\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_001931e0_6\n\t"
      "movl 0x4d8e90, %%ecx\n\t"
      "decl %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0\n\t"
      "andl $0x7fffffff, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $-1\n\t"
      "pushl %%ebx\n\t"
      "call *%[c192da0]\n\t"
      "addl $0x14, %%esp\n\t"
      "jmp .LFUN_001931e0_6\n\t"
      ".LFUN_001931e0_5:\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "call *%[c1931e0]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_001931e0_6:\n\t"
      "cmpw $0, 0x4d8e90\n\t"
      "jg .LFUN_001931e0_7\n\t"
      "pushl $1\n\t"
      "pushl $0x33\n\t"
      "pushl $0x2b28b4\n\t"
      "pushl $0x2b28dc\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001931e0_7:\n\t"
      "decw 0x4d8e90\n\t"
      "incl %%edi\n\t"
      "cmpw $2, %%di\n\t"
      "jl .LFUN_001931e0_1\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [elem] "m"(b1931e0_elem), [assert] "m"(b1931e0_assert), [exitfn] "m"(b1931e0_exitfn), [c192da0] "m"(b1931e0_c192da0), [c1931e0] "m"(b1931e0_c1931e0)
      : "memory");
}
#else
#error "FUN_001931e0: clang naked draft required"
#endif


/* FUN_001932d0 (0x1932d0) — readable C lift. */
void FUN_001932d0(void *node, void *leaf)
{
  short count;
  short i;
  void *face;

  count = *(short *)0x4d8e90;
  if (count <= 0)
    return;
  for (i = 0; i < count; i++) {
    if (i < 0 || i >= count) {
      display_assert((const char *)0x2b2900, (const char *)0x2b28b4, 0x3b, true);
      system_exit(-1);
      count = *(short *)0x4d8e90;
    }
    face = *(void **)(0x4d8a8c + ((int)count - (int)i) * 4);
    ((void (*)(void *, void *, void *))(void *)leaf_map_build_leaf_face_for_leaf_on_node)(
        leaf, node, face);
  }
}

/* FUN_00193340 (0x193340) — XBE naked draft (batch 139). */
#if defined(__clang__)
static void *(*const b193340_elem)(void *, int, int) = tag_block_get_element;
static void (*const b193340_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b193340_exitfn)(int) = system_exit;
static void (*const b193340_c1932d0)(void) = (void (*)(void))FUN_001932d0;
static void (*const b193340_c193340)(void) = (void (*)(void))FUN_00193340;

__attribute__((naked, noinline))
void FUN_00193340(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "pushl %%ebx\n\t"
      "movl 0xc(%%ebp), %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl $0xc\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ecx\n\t"
      "call *%[elem]\n\t"
      "addl $0xc, %%esp\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "xorl %%esi, %%esi\n\t"
      ".LFUN_00193340_1:\n\t"
      "testw %%si, %%si\n\t"
      "movl %%ebx, %%edi\n\t"
      "jne .LFUN_00193340_2\n\t"
      "orl $0x80000000, %%edi\n\t"
      ".LFUN_00193340_2:\n\t"
      "cmpw $0x100, 0x4d8e90\n\t"
      "jl .LFUN_00193340_3\n\t"
      "pushl $1\n\t"
      "pushl $0x2a\n\t"
      "pushl $0x2b28b4\n\t"
      "pushl $0x2b2878\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00193340_3:\n\t"
      "movswl 0x4d8e90, %%edx\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movswl %%si, %%eax\n\t"
      "movl %%edi, 0x4d8a90(,%%edx,4)\n\t"
      "incw 0x4d8e90\n\t"
      "movl 0x4(%%ecx,%%eax,4), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "jns .LFUN_00193340_4\n\t"
      "cmpl $-1, %%edi\n\t"
      "je .LFUN_00193340_5\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "call *%[c1932d0]\n\t"
      "movl 0xc(%%ebp), %%ebx\n\t"
      "jmp .LFUN_00193340_5\n\t"
      ".LFUN_00193340_4:\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "pushl %%edi\n\t"
      "pushl %%edx\n\t"
      "call *%[c193340]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_00193340_5:\n\t"
      "cmpw $0, 0x4d8e90\n\t"
      "jg .LFUN_00193340_6\n\t"
      "pushl $1\n\t"
      "pushl $0x33\n\t"
      "pushl $0x2b28b4\n\t"
      "pushl $0x2b28dc\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00193340_6:\n\t"
      "decw 0x4d8e90\n\t"
      "incl %%esi\n\t"
      "cmpw $2, %%si\n\t"
      "jl .LFUN_00193340_1\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [elem] "m"(b193340_elem), [assert] "m"(b193340_assert), [exitfn] "m"(b193340_exitfn), [c1932d0] "m"(b193340_c1932d0), [c193340] "m"(b193340_c193340)
      : "memory");
}
#else
#error "FUN_00193340: clang naked draft required"
#endif


/* leaf_map_initialize_from_bsp (0x193420) — XBE naked draft (batch 129). */
#if defined(__clang__)
static void (*const b193420_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b193420_exitfn)(int) = system_exit;
static void (*const b193420_penter)(void *) = profile_enter_private;
static bool (*const b193420_c1b9a90)(void *block, int count) = tag_block_resize;
static void (*const b193420_c193340)(void) = (void (*)(void))FUN_00193340;
static void (*const b193420_c1931e0)(void) = (void (*)(void))FUN_001931e0;
static void (*const b193420_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;
static void (*const b193420_pexit)(void *) = profile_exit_private;

__attribute__((naked, noinline))
void leaf_map_initialize_from_bsp(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "pushl %%edi\n\t"
      "jne .Lleaf_map_initialize_from_bsp_1\n\t"
      "pushl $1\n\t"
      "pushl $0x56\n\t"
      "pushl $0x2b28b4\n\t"
      "pushl $0x2b2b38\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lleaf_map_initialize_from_bsp_1:\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .Lleaf_map_initialize_from_bsp_2\n\t"
      "pushl $1\n\t"
      "pushl $0x57\n\t"
      "pushl $0x2b28b4\n\t"
      "pushl $0x2b2b34\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lleaf_map_initialize_from_bsp_2:\n\t"
      "cmpw $0, 0x4d8e90\n\t"
      "je .Lleaf_map_initialize_from_bsp_3\n\t"
      "pushl $1\n\t"
      "pushl $0x58\n\t"
      "pushl $0x2b28b4\n\t"
      "pushl $0x2b2b0c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lleaf_map_initialize_from_bsp_3:\n\t"
      "movb 0x449ef1, %%al\n\t"
      "testb %%al, %%al\n\t"
      "movl $0, 0x4d8e94\n\t"
      "je .Lleaf_map_initialize_from_bsp_4\n\t"
      "movb 0x326bf0, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lleaf_map_initialize_from_bsp_4\n\t"
      "pushl $0x326be8\n\t"
      "call *%[penter]\n\t"
      "addl $4, %%esp\n\t"
      ".Lleaf_map_initialize_from_bsp_4:\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal 0x4(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl %%edi, (%%esi)\n\t"
      "call *%[c1b9a90]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lleaf_map_initialize_from_bsp_9\n\t"
      "cmpl $0, (%%edi)\n\t"
      "jle .Lleaf_map_initialize_from_bsp_5\n\t"
      "pushl $0\n\t"
      "pushl %%esi\n\t"
      "call *%[c193340]\n\t"
      "pushl $0\n\t"
      "pushl %%esi\n\t"
      "call *%[c1931e0]\n\t"
      "addl $0x10, %%esp\n\t"
      ".Lleaf_map_initialize_from_bsp_5:\n\t"
      "movl 0x4d8e94, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lleaf_map_initialize_from_bsp_7\n\t"
      ".Lleaf_map_initialize_from_bsp_6:\n\t"
      "pushl %%eax\n\t"
      "pushl $1\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      ".Lleaf_map_initialize_from_bsp_7:\n\t"
      "movb 0x449ef1, %%al\n\t"
      "testb %%al, %%al\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "je .Lleaf_map_initialize_from_bsp_8\n\t"
      "movb 0x326bf0, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lleaf_map_initialize_from_bsp_8\n\t"
      "pushl $0x326be8\n\t"
      "call *%[pexit]\n\t"
      "addl $4, %%esp\n\t"
      ".Lleaf_map_initialize_from_bsp_8:\n\t"
      "movl 0x4d8e94, %%ecx\n\t"
      "xorl %%eax, %%eax\n\t"
      "testl %%ecx, %%ecx\n\t"
      "sete %%al\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lleaf_map_initialize_from_bsp_9:\n\t"
      "movl 0x4d8e94, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lleaf_map_initialize_from_bsp_6\n\t"
      "movl $0x2b2ae8, %%eax\n\t"
      "movl %%eax, 0x4d8e94\n\t"
      "jmp .Lleaf_map_initialize_from_bsp_6\n\t"
      :
      : [assert] "m"(b193420_assert), [exitfn] "m"(b193420_exitfn), [penter] "m"(b193420_penter), [c1b9a90] "m"(b193420_c1b9a90), [c193340] "m"(b193420_c193340), [c1931e0] "m"(b193420_c1931e0), [c8f390] "m"(b193420_c8f390), [pexit] "m"(b193420_pexit)
      : "memory");
}
#else
#error "leaf_map_initialize_from_bsp: clang naked draft required"
#endif


/* structure_bsp_find_material_for_surface (0x1935f0) — readable C lift. */
void structure_bsp_find_material_for_surface(void *scenario, int surface_index,
                                             int16_t *out_collection_index,
                                             int16_t *out_geometry_index)
{
  void *collections;
  int16_t lo;
  int16_t hi;
  int16_t mid;
  void *coll;
  void *geoms;
  void *elem;
  void *elem_a;
  void *elem_b;
  int start;
  int end;

  *out_collection_index = 0;
  collections = (char *)scenario + 0x104;
  hi = (int16_t)(*(int16_t *)((char *)scenario + 0x104) - 1);
  lo = 0;
  if (hi > 0) {
    for (;;) {
      mid = (int16_t)(lo + ((hi - lo) >> 1));
      *out_collection_index = mid;
      coll = tag_block_get_element(collections, mid, 0x20);
      geoms = (char *)coll + 0x14;
      elem = tag_block_get_element(geoms, 0, 0x100);
      if (surface_index < *(int *)((char *)elem + 0x14)) {
        hi = (int16_t)(*out_collection_index - 1);
        *out_collection_index = hi;
      } else {
        elem_a = tag_block_get_element(geoms, *(int *)geoms - 1, 0x100);
        elem_b = tag_block_get_element(geoms, *(int *)geoms - 1, 0x100);
        end = *(int *)((char *)elem_b + 0x14) +
              *(int *)((char *)elem_a + 0x18);
        if (surface_index < end)
          break;
        lo = (int16_t)(*out_collection_index + 1);
        *out_collection_index = lo;
      }
      if (hi <= lo)
        break;
    }
  }

  coll = tag_block_get_element(collections, *out_collection_index, 0x20);
  geoms = (char *)coll + 0x14;
  *out_geometry_index = 0;
  hi = *(int16_t *)geoms;
  lo = 0;
  if (hi > 0) {
    for (;;) {
      mid = (int16_t)(lo + ((hi - lo) >> 1));
      *out_geometry_index = mid;
      elem = tag_block_get_element(geoms, mid, 0x100);
      start = *(int *)((char *)elem + 0x14);
      if (surface_index < start) {
        hi = (int16_t)(*out_geometry_index - 1);
        *out_geometry_index = hi;
      } else {
        end = start + *(int *)((char *)elem + 0x18);
        if (surface_index < end)
          break;
        lo = (int16_t)(*out_geometry_index + 1);
        *out_geometry_index = lo;
      }
      if (lo >= hi)
        break;
    }
  }

  elem = tag_block_get_element(geoms, *out_geometry_index, 0x100);
  start = *(int *)((char *)elem + 0x14);
  if (surface_index < start) {
    display_assert((const char *)0x2b2c74, (const char *)0x2b2bf8, 0x66, 1);
    system_exit(-1);
  }
  end = start + *(int *)((char *)elem + 0x18);
  if (surface_index >= end) {
    display_assert((const char *)0x2b2c30, (const char *)0x2b2bf8, 0x67, 1);
    system_exit(-1);
  }
}

/* vertex_type_from_shader_tag (0x1937a0) — readable C lift. */
void vertex_type_from_shader_tag(int unused_a, short *type_a, short *type_b, char lit)
{
  (void)unused_a;
  if (lit) {
    *type_a = 1;
    *type_b = 3;
  } else {
    *type_a = 0;
    *type_b = 2;
  }
}

