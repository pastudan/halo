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

/* 0x1929a0 */
void FUN_001929a0(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;

  tag_block_get_element((void *)(uintptr_t)ecx, 0, 12);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  /* test (char)eax, 1 -> jne 0x1929f8 */
  /* test (char)eax, 1 -> jne 0x1929fa */
  /* test (char)eax, 1 -> jne 0x192a0c */
  FUN_00099270((float *)(uintptr_t)esi, edi);
  tag_block_get_element((void *)(uintptr_t)ebx, 0, 0);
  project_point2d((float *)(uintptr_t)eax, (float *)0, 0, 0, (float *)0);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)esi;
  (void)edi;
}

/* 0x192a50 */
void render_debug_leaf_faces(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  tag_block_get_element((void *)(uintptr_t)ecx, 0, 0);
  display_assert((char *)0x002b2a04, (char *)0x002b28b4, 940, 0);
  system_exit(0);
  tag_block_get_element((void *)(uintptr_t)esi, 0, 16);
  FUN_001929a0();
  FUN_001929a0();
  FUN_00189270(0, (float *)(uintptr_t)eax, (float *)(uintptr_t)edx, (void *)(uintptr_t)ecx);
  /* cmp eax, edi -> jle 0x192b88 */
  FUN_001929a0();
  FUN_00188890(0, (float *)(uintptr_t)edx, (float *)(uintptr_t)ecx, (float *)(uintptr_t)eax, (void *)(uintptr_t)edx);
  FUN_00189270(0, (float *)(uintptr_t)edx, (float *)(uintptr_t)ecx, (void *)(uintptr_t)eax);
  /* relift: cmp eax, dword ptr [esi + 4] -> jl 0x192b30 */
  /* cmp eax, edx -> jl 0x192ace */

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x192bb0 */
void FUN_00192bb0(void)
{
  int eax = 0;
  int ecx = 0;

  /* cmp ecx, 0x7f800000 -> je 0x192c1e */
  valid_real_normal3d((float *)0);
  /* test (char)eax, (char)eax -> je 0x192c20 */

  (void)eax;
  (void)ecx;
}

/* intersect_planes3d (0x192c30) — XBE naked draft (batch 121). */
#if defined(__clang__)
static void (*const b192c30_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b192c30_exitfn)(int) = system_exit;
static void (*const b192c30_c192bb0)(void) = FUN_00192bb0;
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
static void (*const b192da0_c192050)(void) = leaf_map_build_portal_from_leaves;
static void (*const b192da0_c192da0)(void) = leaf_map_build_portals_from_leaf;

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
static void (*const b192f80_c192c30)(void) = intersect_planes3d;
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


/* 0x1931e0 */
void FUN_001931e0(void)
{
  int eax = 0;
  int edi = 0;

  tag_block_get_element((void *)(uintptr_t)eax, 0, 12);
  /* test (int16_t)edi, (int16_t)edi -> jne 0x193210 */
  /* relift: cmp word ptr [0x4d8e90], 0x100 -> jl 0x193238 */
  display_assert((char *)0x002b2878, (char *)0x002b28b4, 42, 0);
  system_exit(0);
  /* cmp eax, -1 -> je 0x193287 */
  leaf_map_build_portals_from_leaf();
  /* relift: tail-call FUN_001931e0(); */
  /* relift: cmp word ptr [0x4d8e90], 0 -> jg 0x1932ae */
  display_assert((char *)0x002b28dc, (char *)0x002b28b4, 51, 0);
  system_exit(0);
  /* cmp (int16_t)edi, 2 -> jl 0x193202 */

  (void)eax;
  (void)edi;
}

/* 0x1932d0 */
void FUN_001932d0(void)
{
  int esi = 0;

  /* test (int16_t)eax, (int16_t)eax -> jle 0x193334 */
  /* test (int16_t)esi, (int16_t)esi -> jl 0x1932ea */
  /* cmp (int16_t)esi, (int16_t)eax -> jl 0x19330d */
  display_assert((char *)0x002b2900, (char *)0x002b28b4, 59, 0);
  system_exit(0);
  leaf_map_build_leaf_face_for_leaf_on_node();
  /* cmp (int16_t)esi, (int16_t)eax -> jl 0x1932e0 */

  (void)esi;
}

/* 0x193340 */
void FUN_00193340(void)
{
  int ecx = 0;
  int esi = 0;
  int edi = 0;

  tag_block_get_element((void *)(uintptr_t)ecx, 0, 12);
  /* relift: cmp word ptr [0x4d8e90], 0x100 -> jl 0x193395 */
  display_assert((char *)0x002b2878, (char *)0x002b28b4, 42, 0);
  system_exit(0);
  /* cmp edi, -1 -> je 0x1933d7 */
  FUN_001932d0();
  /* relift: tail-call FUN_00193340(); */
  /* relift: cmp word ptr [0x4d8e90], 0 -> jg 0x1933fe */
  display_assert((char *)0x002b28dc, (char *)0x002b28b4, 51, 0);
  system_exit(0);
  /* cmp (int16_t)esi, 2 -> jl 0x193360 */

  (void)ecx;
  (void)esi;
  (void)edi;
}

/* 0x193420 */
void leaf_map_initialize_from_bsp(void)
{
  int eax = 0;
  int ecx = 0;
  int edi = 0;

  display_assert((char *)0x002b2b38, (char *)0x002b28b4, 86, 0);
  system_exit(0);
  /* test edi, edi -> jne 0x19346d */
  display_assert((char *)0x002b2b34, (char *)0x002b28b4, 87, 0);
  system_exit(0);
  /* relift: cmp word ptr [0x4d8e90], 0 -> je 0x193494 */
  display_assert((char *)0x002b2b0c, (char *)0x002b28b4, 88, 0);
  system_exit(0);
  /* mem[0x004d8e94] = 0 */
  /* test (char)eax, (char)eax -> je 0x1934bd */
  profile_enter_private((void *)0x00326be8);
  tag_block_resize((void *)(uintptr_t)ecx, 0);
  /* test (char)eax, (char)eax -> je 0x19352f */
  /* relift: cmp dword ptr [edi], 0 -> jle 0x1934eb */
  FUN_00193340();
  FUN_001931e0();
  /* test eax, eax -> je 0x1934ff */
  error(0, (char *)(uintptr_t)eax);
  /* test (char)eax, (char)eax -> je 0x193520 */
  profile_exit_private((void *)0x00326be8);
  /* test eax, eax -> jne 0x1934f4 */
  /* mem[0x004d8e94] = eax */

  (void)eax;
  (void)ecx;
  (void)edi;
}

/* structure_bsp_find_material_for_surface (0x1935f0) — XBE naked draft (batch 117). */
#if defined(__clang__)
static void *(*const b1935f0_elem)(void *, int, int) = tag_block_get_element;
static void (*const b1935f0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1935f0_exitfn)(int) = system_exit;

__attribute__((naked, noinline))
void structure_bsp_find_material_for_surface(void *scenario __attribute__((unused)), int surface_index __attribute__((unused)), int16_t *out_collection_index __attribute__((unused)), int16_t *out_geometry_index __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "xorl %%edi, %%edi\n\t"
      "movw %%di, (%%eax)\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movw 0x104(%%eax), %%si\n\t"
      "addl $0x104, %%eax\n\t"
      "decw %%si\n\t"
      "testw %%si, %%si\n\t"
      "movl %%eax, 0x8(%%ebp)\n\t"
      "jle .Lstructure_bsp_find_material_for_surface_4\n\t"
      "jmp .Lstructure_bsp_find_material_for_surface_1\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".Lstructure_bsp_find_material_for_surface_1:\n\t"
      "movswl %%di, %%ecx\n\t"
      "movswl %%si, %%eax\n\t"
      "subl %%ecx, %%eax\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "cdq\n\t"
      "subl %%edx, %%eax\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "sarl $1, %%eax\n\t"
      "addl %%edi, %%eax\n\t"
      "movw %%ax, (%%edx)\n\t"
      "movswl %%ax, %%eax\n\t"
      "pushl $0x20\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[elem]\n\t"
      "pushl $0x100\n\t"
      "leal 0x14(%%eax), %%ebx\n\t"
      "pushl $0\n\t"
      "pushl %%ebx\n\t"
      "call *%[elem]\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "movl 0x14(%%eax), %%ecx\n\t"
      "addl $0x18, %%esp\n\t"
      "cmpl %%ecx, %%edx\n\t"
      "jge .Lstructure_bsp_find_material_for_surface_2\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "movw (%%eax), %%si\n\t"
      "decw %%si\n\t"
      "movw %%si, (%%eax)\n\t"
      "jmp .Lstructure_bsp_find_material_for_surface_3\n\t"
      ".Lstructure_bsp_find_material_for_surface_2:\n\t"
      "movl (%%ebx), %%eax\n\t"
      "pushl $0x100\n\t"
      "decl %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "call *%[elem]\n\t"
      "movl (%%ebx), %%ecx\n\t"
      "pushl $0x100\n\t"
      "decl %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "movl %%eax, %%edi\n\t"
      "call *%[elem]\n\t"
      "movl 0x14(%%eax), %%ecx\n\t"
      "movl 0x18(%%edi), %%edx\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "addl %%ecx, %%edx\n\t"
      "addl $0x18, %%esp\n\t"
      "cmpl %%edx, %%eax\n\t"
      "jl .Lstructure_bsp_find_material_for_surface_4\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "movw (%%eax), %%di\n\t"
      "incw %%di\n\t"
      "movw %%di, (%%eax)\n\t"
      ".Lstructure_bsp_find_material_for_surface_3:\n\t"
      "cmpw %%di, %%si\n\t"
      "jg .Lstructure_bsp_find_material_for_surface_1\n\t"
      ".Lstructure_bsp_find_material_for_surface_4:\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "movswl (%%eax), %%ecx\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "pushl $0x20\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[elem]\n\t"
      "movl 0x14(%%ebp), %%ebx\n\t"
      "xorl %%esi, %%esi\n\t"
      "leal 0x14(%%eax), %%ecx\n\t"
      "movw %%si, (%%ebx)\n\t"
      "movw (%%ecx), %%di\n\t"
      "addl $0xc, %%esp\n\t"
      "testw %%di, %%di\n\t"
      "movl %%ecx, 0x10(%%ebp)\n\t"
      "jle .Lstructure_bsp_find_material_for_surface_10\n\t"
      "jmp .Lstructure_bsp_find_material_for_surface_6\n\t"
      ".Lstructure_bsp_find_material_for_surface_5:\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      ".Lstructure_bsp_find_material_for_surface_6:\n\t"
      "movswl %%si, %%edx\n\t"
      "movswl %%di, %%eax\n\t"
      "subl %%edx, %%eax\n\t"
      "cdq\n\t"
      "subl %%edx, %%eax\n\t"
      "sarl $1, %%eax\n\t"
      "addl %%esi, %%eax\n\t"
      "movw %%ax, (%%ebx)\n\t"
      "movswl %%ax, %%eax\n\t"
      "pushl $0x100\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[elem]\n\t"
      "movl 0x14(%%eax), %%ecx\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl %%ecx, %%edx\n\t"
      "jge .Lstructure_bsp_find_material_for_surface_7\n\t"
      "movw (%%ebx), %%di\n\t"
      "decw %%di\n\t"
      "movw %%di, (%%ebx)\n\t"
      "jmp .Lstructure_bsp_find_material_for_surface_8\n\t"
      ".Lstructure_bsp_find_material_for_surface_7:\n\t"
      "movl 0x18(%%eax), %%eax\n\t"
      "addl %%ecx, %%eax\n\t"
      "cmpl %%eax, %%edx\n\t"
      "jl .Lstructure_bsp_find_material_for_surface_9\n\t"
      "movw (%%ebx), %%si\n\t"
      "incw %%si\n\t"
      "movw %%si, (%%ebx)\n\t"
      ".Lstructure_bsp_find_material_for_surface_8:\n\t"
      "cmpw %%di, %%si\n\t"
      "jl .Lstructure_bsp_find_material_for_surface_5\n\t"
      ".Lstructure_bsp_find_material_for_surface_9:\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      ".Lstructure_bsp_find_material_for_surface_10:\n\t"
      "movswl (%%ebx), %%edx\n\t"
      "pushl $0x100\n\t"
      "pushl %%edx\n\t"
      "pushl %%ecx\n\t"
      "call *%[elem]\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x14(%%esi), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl %%eax, %%edi\n\t"
      "jge .Lstructure_bsp_find_material_for_surface_11\n\t"
      "pushl $1\n\t"
      "pushl $0x66\n\t"
      "pushl $0x2b2bf8\n\t"
      "pushl $0x2b2c74\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lstructure_bsp_find_material_for_surface_11:\n\t"
      "movl 0x18(%%esi), %%eax\n\t"
      "addl 0x14(%%esi), %%eax\n\t"
      "cmpl %%eax, %%edi\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "jl .Lstructure_bsp_find_material_for_surface_12\n\t"
      "pushl $1\n\t"
      "pushl $0x67\n\t"
      "pushl $0x2b2bf8\n\t"
      "pushl $0x2b2c30\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lstructure_bsp_find_material_for_surface_12:\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [elem] "m"(b1935f0_elem), [assert] "m"(b1935f0_assert), [exitfn] "m"(b1935f0_exitfn)
      : "memory");
}
#else
#error "structure_bsp_find_material_for_surface: clang naked draft required"
#endif


/* 0x1937a0 */
void vertex_type_from_shader_tag(void)
{
  /* relift: no calls detected — manual review */
}
