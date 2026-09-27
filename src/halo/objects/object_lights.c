#include <stdint.h>
/* --- object_lights.obj batch drafts (2026-07-26) --- */

/* lights_initialize (0x1391e0) — readable C lift. */
void lights_initialize(void)
{
  extern char DAT_0029b444[];
  extern char DAT_0029b434[];
  extern char DAT_0029b428[];
  extern char DAT_0029b414[];
  extern char DAT_0029b324[];
  extern char DAT_0029b3e8[];
  extern char DAT_0025b590[];

  *(data_t **)0x5a90bc = game_state_data_new(DAT_0029b444, 0x380, 0x7c);
  *(void **)0x46f074 = game_state_malloc(DAT_0029b434, (const char *)0, 4);
  if (!*(void **)0x5a90bc) {
    display_assert(DAT_0029b428, DAT_0029b324, 0xc2, true);
    system_exit(-1);
  }
  if (!*(void **)0x46f074) {
    display_assert(DAT_0029b414, DAT_0029b324, 0xc3, true);
    system_exit(-1);
  }
  **(unsigned char **)0x46f074 = 1;
  if (*(void **)0x5a90bc)
    cluster_partition_globals_new((void **)0x5a90b0, DAT_0025b590);
  else
    error(2, DAT_0029b3e8);
}


/* lights_dispose (0x1392a0) — readable C lift. */
void lights_dispose(void)
{
  cluster_partition_null_references((int *)0x5a90b0);
}

/* lights_initialize_for_new_map (0x1392b0) — readable C lift. */
void lights_initialize_for_new_map(void)
{
  data_delete_all(*(void **)0x5a90bc);
  **(unsigned char **)0x46f074 = 1;
  cluster_partition_clear((void *)0x5a90b0);
}



/* lights_dispose_from_old_map (0x1392e0) — readable C lift. */
void lights_dispose_from_old_map(void)
{
  data_make_invalid(*(void **)0x5a90bc);
  cluster_partition_dispose((void *)0x5a90b0);
}



/* 0x139300 — set the global lights-active flag (returns the stored value). */
char lights_enable(char active)
{
  **(char **)0x46f074 = active;
  return active;
}

/* light_delete (0x139310) — readable C lift. */
void light_delete(int light_handle)
{
  void *light;

  light = datum_get(*(data_t **)0x5a90bc, light_handle);
  cluster_partition_remove_object((void *)0x5a90b0, light_handle,
                                  (char *)light + 0x10);
  datum_delete(*(data_t **)0x5a90bc, light_handle);
}
/* FUN_00139350 (0x139350) — readable C lift: collect light clusters. */
int16_t FUN_00139350(int light_handle, int16_t *out_buffer, int16_t max_count)
{
  void *light;
  int state;
  int16_t count;
  int16_t cluster;

  light = datum_get(*(data_t **)0x5a90bc, light_handle);
  cluster = (int16_t)FUN_00191690((void *)0x5a90b0, &state,
                                  *(int *)((char *)light + 0x10));
  count = 0;
  if (max_count > 0) {
    while (cluster != (int16_t)0xffff && count < max_count) {
      out_buffer[count] = cluster;
      count = (int16_t)(count + 1);
      cluster = (int16_t)FUN_001916d0(0x5a90b0, &state);
    }
  }
  return count;
}


/* object_get_self_illumination (0x1393b0) — readable C lift. */
float object_get_self_illumination(int object_handle)
{
  char *obj;
  char *obj_tag;
  int count;
  int i;
  float sum;
  int light_handle;
  void *light_datum;

  obj = (char *)object_get_and_verify_type(object_handle, -1);
  obj_tag = (char *)tag_get(0x6f626a65, *(int *)obj); /* 'obje' */
  count = *(int *)(obj_tag + 0x140);
  sum = 0.0f;
  for (i = 0; i < count; i++) {
    if (obj[0xf4 + i] != 0)
      continue;
    light_handle = *(int *)(obj + 0xfc + i * 4);
    if (light_handle == -1)
      continue;
    light_datum = datum_get(*(void **)0x5a90bc, light_handle);
    sum += real_rgb_color_brightness((float *)((char *)light_datum + 0x14));
  }
  if (*(int *)(obj + 0xc8) != -1)
    sum += object_get_self_illumination(*(int *)(obj + 0xc8));
  if (*(int *)(obj + 0xc4) != -1)
    sum += object_get_self_illumination(*(int *)(obj + 0xc4));
  return sum;
}


__attribute__((unused)) __attribute__((unused))
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

/* FUN_00139480 (0x139480) — Capstone tip: structure_test_vector fail → return. */
void FUN_00139480(void *position, void *tint_color, void *out_color, char use_lightmap)
{
  float *src = *(float **)0x2ee70c;
  float *tint = (float *)tint_color;
  float *outc = (float *)out_color;
  float out_point[3];
  float out_u, out_v;
  int16_t out_collection;
  int16_t out_material;
  int32_t out_surface;

  (void)use_lightmap;
  tint[0] = src[0];
  tint[1] = src[1];
  tint[2] = src[2];
  outc[0] = src[0];
  outc[1] = src[1];
  outc[2] = src[2];
  if (!structure_test_vector((float *)position, (float *)0x29b204, out_point,
                             &out_collection, &out_material, &out_surface,
                             &out_u, &out_v))
    return;
}

