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

/* render_debug_leaf_faces (0x192a50) — readable C lift (restored pre-naked). */
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
  ((void(*)(void))FUN_001929a0)();
  ((void(*)(void))FUN_001929a0)();
  FUN_00189270(0, (float *)(uintptr_t)eax, (float *)(uintptr_t)edx, (void *)(uintptr_t)ecx);
  /* cmp eax, edi -> jle 0x192b88 */
  ((void(*)(void))FUN_001929a0)();
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


/* intersect_planes3d (0x192c30) — readable C lift (restored pre-naked). */
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
  ((void(*)(void))FUN_00192bb0)();
  FUN_00099270((float *)(uintptr_t)esi, ebx);
  FUN_00061df0((void *)(uintptr_t)edx, 0, eax, (void *)0);
  /* test (char)eax, 0x41 -> jne 0x192d90 */

  (void)eax;
  (void)ebx;
  (void)edx;
  (void)esi;
}



/* leaf_map_build_portals_from_leaf (0x192da0) — readable C lift (restored pre-naked). */
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


/* leaf_map_build_leaf_face_for_leaf_on_node (0x192f80) — readable C lift (restored pre-naked). */
void leaf_map_build_leaf_face_for_leaf_on_node(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  tag_block_get_element((void *)(uintptr_t)eax, 0, 12);
  tag_block_get_element((void *)(uintptr_t)edx, 0, 0);
  /* test (int16_t)eax, (int16_t)eax -> jle 0x193122 */
  /* relift: cmp word ptr [ebp - 0x228], 0 -> je 0x1931d2 */
  /* test (int16_t)edi, (int16_t)edi -> jl 0x192ff8 */
  /* cmp (int16_t)edi, (int16_t)eax -> jl 0x193015 */
  display_assert((char *)0x002b2900, (char *)0x002b28b4, 59, 0);
  system_exit(0);
  /* relift: cmp esi, dword ptr [ebp + 0xc] -> je 0x193112 */
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  tag_block_get_element((void *)(uintptr_t)edx, 0, 0);
  intersect_planes3d();
  /* cmp (int16_t)eax, 1 -> jne 0x193106 */
  convex_polygon2d_clip_to_plane(edx, (float *)(uintptr_t)ecx, (float *)(uintptr_t)eax, 64, (float *)(uintptr_t)edx, (void *)0, (void *)0, 0.0f);
  display_assert((char *)0x002b2acc, (char *)0x002b28b4, 227, 0);
  system_exit(0);
  /* test (int16_t)eax, (int16_t)eax -> jne 0x193112 */
  /* cmp (int16_t)edi, (int16_t)eax -> jl 0x192fe0 */
  /* relift: cmp word ptr [ebp - 0x228], 0 -> je 0x1931d2 */
  tag_block_get_element((void *)(uintptr_t)ebx, 0, 0);
  tag_block_add_element((void *)(uintptr_t)esi);
  /* cmp (int16_t)eax, 0xffff -> je 0x1931bf */
  tag_block_get_element((void *)(uintptr_t)esi, 0, 16);
  tag_block_resize((void *)(uintptr_t)eax, 0);
  /* test (char)eax, (char)eax -> je 0x1931a5 */
  csmemcpy((void *)(uintptr_t)eax, (void *)(uintptr_t)edx, ecx);
  /* test eax, eax -> jne 0x1931d2 */
  /* mem[0x004d8e94] = 0x2b2aa8 */
  /* test eax, eax -> jne 0x1931d2 */
  /* mem[0x004d8e94] = 0x2b2a88 */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}


/* FUN_001931e0 (0x1931e0) — readable C lift from XBE leaf.
 * Sibling of FUN_00193340: walk 2 children; leaf path builds portals. */
void FUN_001931e0(void *block, int index)
{
  void *node;
  int i;
  int path_index;
  int child;

  node = tag_block_get_element(*(void **)block, index, 0xc);
  for (i = 0; i < 2; i++) {
    path_index = index;
    if (i == 0)
      path_index |= (int)0x80000000;
    if (*(short *)0x4d8e90 >= 0x100) {
      display_assert((const char *)0x2b2878, (const char *)0x2b28b4, 0x2a, 1);
      system_exit(-1);
    }
    *(int *)(0x4d8a90 + (*(short *)0x4d8e90) * 4) = path_index;
    (*(short *)0x4d8e90)++;
    child = ((int *)((char *)node + 4))[i];
    if (child < 0) {
      if (child != -1) {
        ((void (*)(void *, int, int, int, int))(void *)leaf_map_build_portals_from_leaf)(
            block, -1, child & 0x7fffffff, 0, (*(short *)0x4d8e90) - 1);
      }
    } else {
      FUN_001931e0(block, child);
    }
    if (*(short *)0x4d8e90 <= 0) {
      display_assert((const char *)0x2b28dc, (const char *)0x2b28b4, 0x33, 1);
      system_exit(-1);
    }
    (*(short *)0x4d8e90)--;
  }
}




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

/* FUN_00193340 (0x193340) — readable C lift from XBE leaf.
 * Walk 2 child slots; push path bits onto 0x4d8a90 stack; recurse or leaf. */
void FUN_00193340(void *block, int index)
{
  void *node;
  int i;
  int path_index;
  int child;

  node = tag_block_get_element(*(void **)block, index, 0xc);
  for (i = 0; i < 2; i++) {
    path_index = index;
    if (i == 0)
      path_index |= (int)0x80000000;
    if (*(short *)0x4d8e90 >= 0x100) {
      display_assert((const char *)0x2b2878, (const char *)0x2b28b4, 0x2a, 1);
      system_exit(-1);
    }
    *(int *)(0x4d8a90 + (*(short *)0x4d8e90) * 4) = path_index;
    (*(short *)0x4d8e90)++;
    child = ((int *)((char *)node + 4))[i];
    if (child < 0) {
      if (child != -1)
        FUN_001932d0((void *)child, block);
    } else {
      FUN_00193340(block, child);
    }
    if (*(short *)0x4d8e90 <= 0) {
      display_assert((const char *)0x2b28dc, (const char *)0x2b28b4, 0x33, 1);
      system_exit(-1);
    }
    (*(short *)0x4d8e90)--;
  }
}




/* leaf_map_initialize_from_bsp (0x193420) — readable C lift (restored pre-naked). */
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
  ((void(*)(void))FUN_00193340)();
  ((void(*)(void))FUN_001931e0)();
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

