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

/* 0x192c30 */
void intersect_planes3d(void)
{
  int eax = 0;
  int ebx = 0;
  int edx = 0;
  int esi = 0;

  /* test (char)eax, 1 -> jne 0x192c63 */
  /* test (char)eax, 1 -> jne 0x192c65 */
  /* test (char)eax, 1 -> jne 0x192c77 */
  display_assert((char *)0x002b2a10, (char *)0x002b28b4, 299, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x192cd6 */
  display_assert((char *)0x0025f120, (char *)0x002b28b4, 300, 0);
  system_exit(0);
  FUN_00192bb0();
  FUN_00099270((float *)(uintptr_t)esi, ebx);
  FUN_00061df0((void *)(uintptr_t)edx, 0, eax, (void *)0);
  /* test (char)eax, 0x41 -> jne 0x192d90 */

  (void)eax;
  (void)ebx;
  (void)edx;
  (void)esi;
}

/* 0x192da0 */
void leaf_map_build_portals_from_leaf(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  tag_block_get_element((void *)(uintptr_t)ecx, 0, 12);
  /* test (int16_t)eax, (int16_t)eax -> jl 0x192ddb */
  /* relift: cmp (int16_t)eax, word ptr [0x4d8e90] -> jl 0x192dfb */
  display_assert((char *)0x002b2900, (char *)0x002b28b4, 59, 0);
  system_exit(0);
  FUN_00191bd0(0, (void *)(uintptr_t)edx, (char *)0);
  /* cmp eax, ecx -> je 0x192e5f */
  display_assert((char *)0x002b2a38, (char *)0x002b28b4, 415, 0);
  system_exit(0);
  /* cmp edi, -1 -> jne 0x192e7e */
  /* test (int16_t)ebx, (int16_t)ebx -> je 0x192e7e */
  /* test (int16_t)ebx, (int16_t)ebx -> jne 0x192e97 */
  /* test (char)eax, (char)eax -> je 0x192f1c */
  tag_block_get_element((void *)(uintptr_t)edx, 0, 0);
  /* test eax, eax -> jle 0x192ee3 */
  tag_block_get_element((void *)(uintptr_t)edi, 0, 16);
  /* cmp edx, ecx -> je 0x192efe */
  /* cmp eax, ecx -> jl 0x192ec4 */
  /* cmp (int16_t)ebx, -1 -> je 0x192ee3 */
  /* test (char)eax, (char)eax -> je 0x192f1c */
  /* cmp (int16_t)edx, (int16_t)ebx -> je 0x192ee9 */
  /* cmp eax, -1 -> je 0x192ee9 */
  /* cmp edx, esi -> je 0x192ee9 */
  leaf_map_build_portal_from_leaves();
  /* relift: tail-call leaf_map_build_portals_from_leaf(); */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

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

/* 0x1935f0 */
void structure_bsp_find_material_for_surface(void *scenario, int surface_index, int16_t *out_collection_index, int16_t *out_geometry_index)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  tag_block_get_element((void *)(uintptr_t)ecx, 0, 32);
  tag_block_get_element((void *)(uintptr_t)ebx, 0, 256);
  /* cmp edx, ecx -> jge 0x19366e */
  tag_block_get_element((void *)(uintptr_t)ebx, 0, 0);
  tag_block_get_element((void *)(uintptr_t)ebx, 0, 0);
  /* cmp eax, edx -> jl 0x1936b4 */
  /* cmp (int16_t)esi, (int16_t)edi -> jg 0x193620 */
  tag_block_get_element((void *)(uintptr_t)edx, 0, 32);
  tag_block_get_element((void *)(uintptr_t)ecx, 0, 256);
  /* cmp edx, ecx -> jge 0x19371c */
  /* cmp edx, eax -> jl 0x193732 */
  /* cmp (int16_t)esi, (int16_t)edi -> jl 0x1936e1 */
  tag_block_get_element((void *)(uintptr_t)ecx, 0, 256);
  /* cmp edi, eax -> jge 0x193770 */
  display_assert((char *)0x002b2c74, (char *)0x002b2bf8, 102, 0);
  system_exit(0);
  display_assert((char *)0x002b2c30, (char *)0x002b2bf8, 103, 0);
  system_exit(0);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x1937a0 */
void vertex_type_from_shader_tag(void)
{
  /* relift: no calls detected — manual review */
}
