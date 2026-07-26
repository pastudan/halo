/* --- object_lights.obj batch drafts (2026-07-26) --- */

/* lights_initialize (0x1391e0) — XBE naked draft (batch 230). */
#if defined(__clang__)
static data_t * (*const b1391e0_c1bfe10)(char *name, __int16 maximum_count, __int16 size) = game_state_data_new;
static void * (*const b1391e0_c1bfbf0)(const char *name, const char *a2, int size) = game_state_malloc;
static void (*const b1391e0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1391e0_exitfn)(int) = system_exit;
static void (*const b1391e0_c191500)(void **out, const char *name) = cluster_partition_globals_new;
static void (*const b1391e0_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;

__attribute__((naked, noinline))
void lights_initialize(void)
{
  __asm__ volatile(
      "pushl $0x7c\n\t"
      "pushl $0x380\n\t"
      "pushl $0x29b444\n\t"
      "call *%[c1bfe10]\n\t"
      "pushl $4\n\t"
      "pushl $0\n\t"
      "pushl $0x29b434\n\t"
      "movl %%eax, 0x5a90bc\n\t"
      "call *%[c1bfbf0]\n\t"
      "movl %%eax, 0x46f074\n\t"
      "movl 0x5a90bc, %%eax\n\t"
      "addl $0x18, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Llights_initialize_1\n\t"
      "pushl $1\n\t"
      "pushl $0xc2\n\t"
      "pushl $0x29b324\n\t"
      "pushl $0x29b428\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Llights_initialize_1:\n\t"
      "movl 0x46f074, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Llights_initialize_2\n\t"
      "pushl $1\n\t"
      "pushl $0xc3\n\t"
      "pushl $0x29b324\n\t"
      "pushl $0x29b414\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Llights_initialize_2:\n\t"
      "movl 0x46f074, %%eax\n\t"
      "movb $1, (%%eax)\n\t"
      "movl 0x5a90bc, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Llights_initialize_3\n\t"
      "pushl $0x25b590\n\t"
      "pushl $0x5a90b0\n\t"
      "call *%[c191500]\n\t"
      "addl $8, %%esp\n\t"
      "ret\n\t"
      ".Llights_initialize_3:\n\t"
      "pushl $0x29b3e8\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "ret\n\t"
      :
      : [c1bfe10] "m"(b1391e0_c1bfe10), [c1bfbf0] "m"(b1391e0_c1bfbf0), [assert] "m"(b1391e0_assert), [exitfn] "m"(b1391e0_exitfn), [c191500] "m"(b1391e0_c191500), [c8f390] "m"(b1391e0_c8f390)
      : "memory");
}
#else
#error "lights_initialize: clang naked draft required"
#endif


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

/* 0x139300 — set the global lights-active flag (returns the stored value). */
char lights_enable(char active)
{
  **(char **)0x46f074 = active;
  return active;
}

/* 0x139310 — remove a light from the cluster partition and delete its datum. */
void light_delete(int light_handle)
{
  char *light;

  light = (char *)datum_get(*(void **)0x5a90bc, light_handle);
  cluster_partition_remove_object((void *)0x005a90b0, light_handle,
                                  (void *)(light + 0x10));
  datum_delete(*(void **)0x5a90bc, light_handle);
}

/* 0x139350 — collect gel/cluster indices overlapping a light's partition. */
int16_t FUN_00139350(int light_handle, int16_t *out_buffer, int16_t max_count)
{
  char *light;
  int16_t cluster;
  int16_t count;
  int iter_state;

  light = (char *)datum_get(*(void **)0x5a90bc, light_handle);
  cluster = (int16_t)FUN_00191690((void *)0x005a90b0, &iter_state,
                                  *(int *)(light + 0x10));
  count = 0;
  if (max_count > 0) {
    while (cluster != (int16_t)0xffff) {
      out_buffer[count] = cluster;
      count++;
      cluster = (int16_t)FUN_001916d0((int)0x005a90b0, &iter_state);
      if (count >= max_count)
        break;
    }
  }
  return count;
}

/* object_get_self_illumination (0x1393b0) — XBE naked draft (batch 232). */
#if defined(__clang__)
static void *(*const b1393b0_get)(int, int) = object_get_and_verify_type;
static void *(*const b1393b0_tag)(int, int) = tag_get;
static void *(*const b1393b0_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static float (*const b1393b0_c7a750)(float *color) = real_rgb_color_brightness;
static float (*const b1393b0_c1393b0)(int object_handle) = object_get_self_illumination;

__attribute__((naked, noinline))
float object_get_self_illumination(int object_handle __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl $-1\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl (%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x6f626a65\n\t"
      "call *%[tag]\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl 0x140(%%ebx), %%eax\n\t"
      "addl $0x10, %%esp\n\t"
      "xorl %%edi, %%edi\n\t"
      "testl %%eax, %%eax\n\t"
      "movl $0, -0x4(%%ebp)\n\t"
      "jle .Lobject_get_self_illumination_3\n\t"
      "xorl %%eax, %%eax\n\t"
      "jmp .Lobject_get_self_illumination_1\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".Lobject_get_self_illumination_1:\n\t"
      "movb 0xf4(%%eax,%%esi,1), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "jne .Lobject_get_self_illumination_2\n\t"
      "movl 0xfc(%%esi,%%eax,4), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lobject_get_self_illumination_2\n\t"
      "movl 0x5a90bc, %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%edx\n\t"
      "call *%[dget]\n\t"
      "addl $0x14, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c7a750]\n\t"
      "fadds -0x4(%%ebp)\n\t"
      "addl $0xc, %%esp\n\t"
      "fstps -0x4(%%ebp)\n\t"
      ".Lobject_get_self_illumination_2:\n\t"
      "movl 0x140(%%ebx), %%ecx\n\t"
      "incl %%edi\n\t"
      "movswl %%di, %%eax\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jl .Lobject_get_self_illumination_1\n\t"
      ".Lobject_get_self_illumination_3:\n\t"
      "movl 0xc8(%%esi), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lobject_get_self_illumination_4\n\t"
      "pushl %%eax\n\t"
      "call *%[c1393b0]\n\t"
      "fadds -0x4(%%ebp)\n\t"
      "addl $4, %%esp\n\t"
      "fstps -0x4(%%ebp)\n\t"
      ".Lobject_get_self_illumination_4:\n\t"
      "movl 0xc4(%%esi), %%esi\n\t"
      "cmpl $-1, %%esi\n\t"
      "je .Lobject_get_self_illumination_5\n\t"
      "pushl %%esi\n\t"
      "call *%[c1393b0]\n\t"
      "fadds -0x4(%%ebp)\n\t"
      "addl $4, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lobject_get_self_illumination_5:\n\t"
      "flds -0x4(%%ebp)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [get] "m"(b1393b0_get), [tag] "m"(b1393b0_tag), [dget] "m"(b1393b0_dget), [c7a750] "m"(b1393b0_c7a750), [c1393b0] "m"(b1393b0_c1393b0)
      : "memory");
}
#else
#error "object_get_self_illumination: clang naked draft required"
#endif


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
