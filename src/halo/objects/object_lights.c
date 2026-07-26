/* --- object_lights.obj batch drafts (2026-07-26) --- */

/* 0x1391e0 — allocate light datums and cluster-partition globals. */
void lights_initialize(void)
{
  void *lights_data;
  void *active_flag;

  lights_data = game_state_data_new((char *)0x0029b444, 0x380, 0x7c);
  *(void **)0x5a90bc = lights_data;
  active_flag = game_state_malloc((char *)0x0029b434, 0, 4);
  *(void **)0x46f074 = active_flag;

  if (lights_data == 0) {
    display_assert((char *)0x0029b428, (char *)0x0029b324, 0xc2, 1);
    system_exit(-1);
  }
  if (active_flag == 0) {
    display_assert((char *)0x0029b414, (char *)0x0029b324, 0xc3, 1);
    system_exit(-1);
  }

  *(char *)active_flag = 1;
  if (*(void **)0x5a90bc != 0)
    cluster_partition_globals_new((void **)0x005a90b0, (char *)0x0025b590);
}

/* 0x1392a0 */
void lights_dispose(void)
{
  cluster_partition_null_references((void *)0x005a90b0);
}

/* 0x1392b0 */
void lights_initialize_for_new_map(void)
{
  data_delete_all(*(void **)0x5a90bc);
  **(char **)0x46f074 = 1;
  cluster_partition_clear((void *)0x005a90b0);
}

/* 0x1392e0 */
void lights_dispose_from_old_map(void)
{
  data_make_invalid(*(void **)0x5a90bc);
  cluster_partition_dispose((void *)0x005a90b0);
}

/* 0x139300 */
int lights_enable(int a0)
{
  /* relift: no calls detected — manual review */
  (void)0;
  return 0;
}

/* 0x139310 */
void light_delete(int light_handle)
{
  int eax = 0;
  int ecx = 0;

  datum_get((void *)(uintptr_t)eax, 0);
  cluster_partition_remove_object((void *)0x005a90b0, 0, (void *)(uintptr_t)eax);
  datum_delete((void *)(uintptr_t)ecx, 0);

  (void)eax;
  (void)ecx;
}

/* 0x139350 */
int16_t FUN_00139350(int light_handle, int16_t *out_buffer, int16_t max_count)
{
  int eax = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;

  datum_get((void *)(uintptr_t)ecx, 0);
  FUN_00191690((void *)0x005a90b0, (void *)(uintptr_t)eax, 0);
  /* test (int16_t)edi, (int16_t)edi -> jle 0x1393a4 */
  /* cmp (int16_t)eax, 0xffff -> je 0x1393a4 */
  FUN_001916d0(0, (void *)0);
  /* cmp (int16_t)esi, (int16_t)edi -> jl 0x139380 */
  return 0;

  (void)eax;
  (void)ecx;
  (void)esi;
  (void)edi;
}

/* 0x1393b0 — sum self-illumination from attached lights (+ parent/child). */
float object_get_self_illumination(int object_handle)
{
  char *obj;
  char *obj_tag;
  float total = 0.0f;
  int16_t i;
  int light_count;
  int parent;
  int child;

  obj = (char *)object_get_and_verify_type(object_handle, -1);
  obj_tag = (char *)tag_get(0x6f626a65, *(int *)obj); /* 'obje' */
  light_count = *(int *)(obj_tag + 0x140);
  for (i = 0; i < light_count; i++) {
    int light_handle;
    if (obj[0xf4 + (int)i] != 0)
      continue;
    light_handle = *(int *)(obj + 0xfc + (int)i * 4);
    if (light_handle == -1)
      continue;
    total += real_rgb_color_brightness(
        (float *)((char *)datum_get(*(void **)0x5a90bc, light_handle) + 0x14));
  }

  parent = *(int *)(obj + 0xc8);
  if (parent != -1)
    total += object_get_self_illumination(parent);
  child = *(int *)(obj + 0xc4);
  if (child != -1)
    return total + object_get_self_illumination(child);
  return total;
}

static void light_sample_clamp_rgb(float *rgb)
{
  int i;

  for (i = 0; i < 3; i++) {
    float v = rgb[i] + *(float *)0x25496c;
    if (v > 1.0f)
      v = 1.0f;
    rgb[i] = v;
  }
}

/* 0x139480 — Sample structure lightmap/tint colors at a world-space point. */
void FUN_00139480(void *position, void *tint_color, void *out_color, char use_lightmap)
{
  float *pos;
  float *tint;
  float *out;
  float hit_point[3];
  int16_t collection_index;
  int16_t material_index;
  int32_t surface_index;
  float hit_u;
  float hit_v;
  char *scenario;
  char *collection_elem;
  char *material_elem;
  char *shader;
  char *shader_ext;
  char *bitmap_tag;
  void *lightmap_bitmap;
  void *detail_bitmap;
  char *lightmap_elem;
  int sampled_tint;

  pos = (float *)position;
  tint = (float *)tint_color;
  out = (float *)out_color;

  tint[0] = out[0] = ((float *)0x2ee70c)[0];
  tint[1] = out[1] = ((float *)0x2ee70c)[1];
  tint[2] = out[2] = ((float *)0x2ee70c)[2];

  if (!structure_test_vector(pos, (float *)0x0029b204, hit_point,
                             &collection_index, &material_index,
                             &surface_index, &hit_u, &hit_v))
    return;

  scenario = (char *)scenario_get();
  collection_elem =
      (char *)tag_block_get_element(scenario + 0x104, collection_index, 0x20);
  material_elem =
      (char *)tag_block_get_element(collection_elem + 0x14, material_index, 0x100);
  shader = (char *)tag_get('rdhs', *(int *)(material_elem + 0xc));
  if (*(int16_t *)(shader + 0x24) != 3)
    return;

  shader_ext = (char *)FUN_001906b0(shader, 3);
  if (*(int *)(scenario + 0xc) == -1)
    return;
  if (*(int *)(shader_ext + 0x94) == -1)
    return;
  if (*(int16_t *)material_elem == -1)
    return;

  lightmap_bitmap =
      FUN_00076ff0(*(int *)(scenario + 0xc), *(short *)(shader_ext + 0x94));
  bitmap_tag = (char *)tag_get('mtib', *(int *)(shader_ext + 0x94));
  detail_bitmap = FUN_00076ff0(*(int *)(shader_ext + 0x94),
                               (short)(*(int16_t *)(material_elem + 0x10) /
                                       *(int *)(bitmap_tag + 0x60)));

  lightmap_elem = 0;
  sampled_tint = 0;
  if (lightmap_bitmap != 0) {
    if ((use_lightmap && FUN_00138ee0((int)(uintptr_t)lightmap_bitmap) != 0) ||
        xbox_texture_cache_get_hardware_format(lightmap_bitmap, 0, 0) != 0) {
      lightmap_elem =
          (char *)tag_block_get_element(scenario + 0xf8, surface_index, 6);
      FUN_00138fd0((int)(uintptr_t)material_elem, (int)(uintptr_t)lightmap_elem,
                   (unsigned short *)lightmap_elem, hit_u, hit_v, tint);
      light_sample_clamp_rgb(tint);
      sampled_tint = 1;
    }
  }

  if (detail_bitmap == 0)
    return;

  if ((use_lightmap && FUN_00138ee0((int)(uintptr_t)detail_bitmap) != 0) ||
      xbox_texture_cache_get_hardware_format(detail_bitmap, 0, 0) != 0) {
    if (!sampled_tint)
      lightmap_elem =
          (char *)tag_block_get_element(scenario + 0xf8, surface_index, 6);
    FUN_001390d0((int)(uintptr_t)material_elem, (int)(uintptr_t)detail_bitmap,
                 (uint16_t *)lightmap_elem, hit_u, hit_v, out);
    light_sample_clamp_rgb(out);
  }
}
