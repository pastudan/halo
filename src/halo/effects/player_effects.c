#include <stdint.h>

char *player_effect_get(int16_t local_player_index)
{
  assert_halt(local_player_index >= 0 &&
              local_player_index < MAXIMUM_NUMBER_OF_LOCAL_PLAYERS);
  assert_halt(player_effect_globals);
  return player_effect_globals + local_player_index * 0xec;
}

void player_effect_initialize(void)
{
  player_effect_globals = (char *)game_state_malloc("player effects", 0, 0x3ec);
  assert_halt(player_effect_globals);
}

void player_effect_dispose(void)
{
}

void player_effect_initialize_for_new_map(void)
{
  csmemset(player_effect_globals, 0, 0x3ec);
  *(_WORD *)(player_effect_globals + 0x3c0) = 0xFFFF;
  *(_DWORD *)(player_effect_globals + 0x3e8) = game_time_get();
}

void player_effect_dispose_from_old_map(void)
{
}

void player_effect_update(void)
{
  int16_t local_player_index;
  int player_index;
  void *player;
  char *effect;

  local_player_index = (int16_t)local_player_get_next(-1);
  while (local_player_index != -1) {
    player_index = local_player_get_player_index(local_player_index);
    if (player_index != -1) {
      player = datum_get(player_data,
                         local_player_get_player_index(local_player_index));
      if (*(int *)((char *)player + 0x34) != -1) {
        local_player_index = (int16_t)local_player_get_next(local_player_index);
        continue;
      }
    }
    effect = player_effect_get(local_player_index);
    csmemset(effect + 0xe4, 0, 4);
    csmemset(player_effect_get(local_player_index), 0, 0xec);
    rumble_clear_for_local_player(local_player_index);
    local_player_index = (int16_t)local_player_get_next(local_player_index);
  }
}

/* player_effect_set_from_descriptor -- apply an effect descriptor to a player's
 * effect state. Internal helper at 0xa2ab0.
 *
 * The original binary passes the descriptor in EBX as a register arg;
 * we pass it explicitly since all callers are in this TU.
 *
 * Confirmed: copies 56 bytes (14 dwords) from descriptor to effect+0x18.
 * Confirmed: scales effect+0x28 by intensity_scale.
 * Confirmed: sets effect+0xde to (short)(intensity_scale * effect->field_28).
 * Confirmed: clamps effect+0x3c to [0.0f, max] where max comes from descriptor.
 * Confirmed: sets bit 0 at effect+0xe8.
 */
static void player_effect_set_from_descriptor(int player_index, char *effect,
                                              float intensity,
                                              float intensity_scale,
                                              void *descriptor)
{
  int16_t desc_type = *(int16_t *)descriptor;
  int16_t desc_priority = *((int16_t *)descriptor + 1);
  float desc_duration = *(float *)((char *)descriptor + 0x10);
  float desc_max = *(float *)((char *)descriptor + 0x20);
  float desc_min = *(float *)((char *)descriptor + 0x24);
  int16_t effect_priority = *(int16_t *)(effect + 0x1a);
  int16_t effect_timer = *(int16_t *)(effect + 0xde);
  int16_t *enabled_array = (int16_t *)0x2ef7e0;
  float scaled_duration;
  float clamped_value;

  (void)
    player_index; /* original binary receives this in ESI but never uses it */

  scaled_duration = intensity_scale * desc_duration;

  if (((effect_priority <= desc_priority) ||
       ((float)effect_timer <= scaled_duration)) &&
      (enabled_array[desc_type] != 0)) {
    csmemcpy(effect + 0x18, descriptor, 0x38);

    *(float *)(effect + 0x28) = intensity_scale * *(float *)(effect + 0x28);

    *(int16_t *)(effect + 0xde) = (int16_t)(*(float *)(effect + 0x28));

    clamped_value = 0.0f;
    if (0.0f <= ((1.0f - desc_min) * intensity + desc_min)) {
      if (((1.0f - desc_min) * intensity + desc_min) <= desc_max) {
        clamped_value = (1.0f - desc_min) * intensity + desc_min;
      } else {
        clamped_value = desc_max;
      }
    }
    *(float *)(effect + 0x3c) = clamped_value;
    *(uint8_t *)(effect + 0xe8) |= 1;
  }
}

void player_effect_apply(int player_handle, void *effect_descriptor,
                         float intensity)
{
  int16_t unit_index;
  void *player;
  char *effect;

  if (player_handle == -1)
    return;

  player = datum_get(player_data, player_handle);
  unit_index = *(int16_t *)((char *)player + 2);

  if (unit_index == -1)
    return;

  effect = player_effect_get(unit_index);
  player_effect_set_from_descriptor(unit_index, effect, intensity,
                                    intensity * 30.0f, effect_descriptor);
}

/* FUN_000a3b80 (0xa3b80) — readable C lift (restored pre-naked). */
void FUN_000a3b80(int player_handle, void *damage_params, void *direction,
                  float damage_amount, float scale)
{
  char *player;
  int16_t unit_index;
  char *jpt_tag;
  char *effect;
  int driver_handle;
  int driver_type_valid;
  int damage_type_valid;
  void *camera;
  float attacker_pos[3];
  vector3_t victim_pos;
  float delta[3];
  float rotated_delta[3];
  float length;
  float angle;

  player = (char *)datum_get(*(data_t **)0x5aa6d4, player_handle);
  unit_index = *(int16_t *)(player + 2);

  if ((int)direction == 0) {
    assert_halt(0);
  }

  lock_global_random_seed();

  if (unit_index != -1) {
    jpt_tag = (char *)tag_get(0x6a707421, *(int *)damage_params);
    effect = player_effect_get(unit_index);

    player_effect_set_from_descriptor(unit_index, effect, damage_amount, 1.0f,
                                      (void *)(jpt_tag + 0x24));
    FUN_000a3890(unit_index, (float *)(jpt_tag + 0x98), direction,
                 damage_amount, 1.0f, (float *)effect /* @<eax> */);
    FUN_000a2ba0(unit_index, damage_amount, 1.0f,
                 (float *)(jpt_tag + 0xcc) /* @<eax> */,
                 (void *)effect /* @<ebx> */);
    rumble_player_impulse((short)unit_index, (float *)(jpt_tag + 0x5c),
                          damage_amount, 1.0f);

    if (*(int *)(jpt_tag + 0x120) != -1) {
      sound_impulse_start(*(int *)(jpt_tag + 0x120), 1.0f);
    }

    if ((*(float *)0x2533c0 < scale) &&
        (*(int *)((char *)damage_params + 0xc) != -1)) {
      if ((*(unsigned int *)(jpt_tag + 0x1c8) & 0x100) != 0) {
        *(unsigned char *)(effect + 0xe6) = 1;
        unlock_global_random_seed();
        return;
      }

      driver_handle = local_player_get_player_index(unit_index);
      if (driver_handle == -1) {
        driver_handle = -1;
      } else {
        driver_handle = local_player_get_player_index(unit_index);
        player = (char *)datum_get(*(data_t **)0x5aa6d4, driver_handle);
        driver_handle = *(int *)(player + 0x34);
      }

      driver_type_valid =
        (int)object_try_and_get_and_verify_type(driver_handle, 3) != 0;
      damage_type_valid = (int)object_try_and_get_and_verify_type(
                            *(int *)((char *)damage_params + 0xc), -1) != 0;

      if (driver_type_valid && damage_type_valid) {
        camera = observer_get_camera(unit_index);
        if (camera != (void *)0) {
          unit_get_head_position(driver_handle, attacker_pos);
          object_get_world_position(*(int *)((char *)damage_params + 0xc),
                                    &victim_pos);

          delta[0] = victim_pos.x - attacker_pos[0];
          delta[1] = victim_pos.y - attacker_pos[1];
          delta[2] = victim_pos.z - attacker_pos[2];

          cross_product3d((float *)((char *)camera + 0x20),
                          (float *)((char *)camera + 0x2c), attacker_pos);

          rotated_delta[0] = attacker_pos[0] * delta[0] +
                             attacker_pos[1] * delta[1] +
                             attacker_pos[2] * delta[2];
          rotated_delta[1] = delta[0] * *(float *)((char *)camera + 0x20) +
                             delta[1] * *(float *)((char *)camera + 0x24) +
                             delta[2] * *(float *)((char *)camera + 0x28);
          rotated_delta[2] = delta[0] * *(float *)((char *)camera + 0x2c) +
                             delta[1] * *(float *)((char *)camera + 0x30) +
                             delta[2] * *(float *)((char *)camera + 0x34);

          length = normalize3d(rotated_delta);
          if (length != 0.0f) {
            if ((0.0f < fabsf(rotated_delta[2]))) {
              if (rotated_delta[2] <= 0.0f) {
                *(unsigned char *)(effect + 0xe6) = 1;
              } else {
                *(unsigned char *)(effect + 0xe4) = 1;
              }
            }

            angle = (float)atan2(rotated_delta[1], rotated_delta[0]);
            if ((angle < *(float *)0x254a58) || (*(float *)0x26af48 < angle)) {
              if ((*(float *)0x2568bc < fabsf(angle))) {
                *(unsigned char *)(effect + 0xe5) = 1;
                unlock_global_random_seed();
                return;
              }
              *(unsigned char *)(effect + 0xe7) = 1;
            }
          }
        }
      }
    }
  }

  unlock_global_random_seed();
}

/* --- player_effects.obj batch drafts (2026-07-26) --- */

/* player_effect_add_continuous_effect (0xa27a0) — readable C lift (restored pre-naked). */
void player_effect_add_continuous_effect(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int edi = 0;

  tag_get(0x63646d67, 0);
  player_effect_get(ecx);
  /* test (char)eax, 0x41 -> jne 0xa2821 */
  game_time_get();
  FUN_0010a5e0(edx, 0.0f);
  csmemset((void *)(uintptr_t)edi, 0, 16);
  /* test (char)eax, 0x41 -> je 0xa2896 */
  /* test (char)eax, 0x41 -> je 0xa28b7 */

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)edi;
}


/* scripted_player_effect_set_rotation (0xa28e0) — readable C lift (deg→rad scale). */
void scripted_player_effect_set_rotation(float yaw, float pitch, float roll)
{
  char *fx;
  float scale;

  fx = *(char **)0x4557ec;
  scale = *(float *)0x253d4c;
  *(float *)(fx + 0x3d0) = yaw * scale;
  *(float *)(fx + 0x3d4) = pitch * scale;
  *(float *)(fx + 0x3d8) = roll * scale;
}

/* scripted_player_effect_set_rumble (0xa2920) — readable C lift. */
void scripted_player_effect_set_rumble(int a0, float a1)
{
  rumble_player_set_scripted_values(a0, a1);
}

/* player_telefrag_effect_stop (0xa2930) — readable C lift. */
void player_telefrag_effect_stop(int player_handle)
{
  void *d = datum_get(*(data_t **)0x5aa6d4, player_handle);
  short idx = *(short *)((char *)d + 2);
  if (idx != -1) {
    player_effect_get(idx);
    rumble_set_direct_motors(idx, 0, 0);
  }
}
/* player_effect_screen_fade_in (0xa2970) — readable C lift. */
void player_effect_screen_fade_in(float a0, int a1, int a2, short a3)
{
  char *p = *(char **)0x4557ec;
  *(float *)(p + 0x3b0) = a0;
  *(int *)(p + 0x3b4) = a1;
  *(int *)(p + 0x3b8) = a2;
  *(short *)(p + 0x3c0) = a3;
  p[0x3c2] = (char)0;
  *(int *)(p + 0x3bc) = game_time_get();
}

/* player_effect_screen_fade_out (0xa29c0) — readable C lift. */
void player_effect_screen_fade_out(float a0, int a1, int a2, short a3)
{
  char *p = *(char **)0x4557ec;
  *(float *)(p + 0x3b0) = a0;
  *(int *)(p + 0x3b4) = a1;
  *(int *)(p + 0x3b8) = a2;
  *(short *)(p + 0x3c0) = a3;
  p[0x3c2] = (char)1;
  *(int *)(p + 0x3bc) = game_time_get();
}

/* player_effect_get_damage_indicators (0xa2a10) — readable C lift. */
void player_effect_get_damage_indicators(int player_index, void *out)
{
  char *p = player_effect_get((int16_t)player_index);
  char *src = p + 0xe4;
  int i;
  csmemcpy(out, src, 4);
  for (i = 0; i < 4; i++) {
    if (src[i] != 0) {
      int v = (int)game_time_get_elapsed() + (unsigned char)src[i];
      if (v >= 0xff)
        src[i] = (char)0xff;
      else
        src[i] = (char)((int)game_time_get_elapsed() + (unsigned char)src[i]);
    }
    src++;
  }
}
/* player_effect_clear_damage_indicators (0xa2a70) — readable C lift. */
void player_effect_clear_damage_indicators(int player_index)
{
  char *p = player_effect_get((int16_t)player_index);
  csmemset(p + 0xe4, 0, 4);
}
/* FUN_000a2a90 (0xa2a90) — readable C lift: lerp(a, 1, t) = a+(1-a)*t. */
float FUN_000a2a90(float a, float t)
{
  return (*(float *)0x2533c8 - a) * t + a;
}

/* FUN_000a2ab0 (0xa2ab0) — readable C lift from XBE leaf.
 * descriptor@ebx; stack: unused, effect*, intensity, scale (pre-*30). */
void FUN_000a2ab0(int unused_player, char *effect, float intensity, float scale,
                  void *descriptor)
{
  float scale30;
  int16_t effect_pri;
  int16_t desc_pri;
  int16_t desc_type;
  float timer_f;
  float scaled_dur;
  float desc_min;
  float desc_max;
  float value;

  (void)unused_player;

  scale30 = scale * *(float *)0x253394;
  effect_pri = *(int16_t *)(effect + 0x1a);
  desc_pri = *(int16_t *)((char *)descriptor + 2);

  if (effect_pri > desc_pri) {
    timer_f = (float)(int)*(int16_t *)(effect + 0xde);
    scaled_dur = scale30 * *(float *)((char *)descriptor + 0x10);
    if (!(scaled_dur < timer_f))
      return;
  }

  desc_type = *(int16_t *)descriptor;
  if (((int16_t *)0x2ef7e0)[desc_type] == 0)
    return;

  {
    int i;
    int *dst = (int *)(effect + 0x18);
    int *src = (int *)descriptor;
    for (i = 0; i < 14; i++)
      dst[i] = src[i];
  }
  *(float *)(effect + 0x28) = scale30 * *(float *)(effect + 0x28);
  {
    float ftmp = *(float *)(effect + 0x28);
    int ftol_result;
    __asm__ volatile(
        "flds %1\n\t"
        "call %P2\n\t"
        "movl %%eax, %0"
        : "=m"(ftol_result)
        : "m"(ftmp), "X"(FUN_001d9068)
        : "eax", "edx", "ecx", "st", "cc", "memory");
    *(int16_t *)(effect + 0xde) = (int16_t)ftol_result;
  }

  desc_min = *(float *)((char *)descriptor + 0x24);
  desc_max = *(float *)((char *)descriptor + 0x20);
  value = (*(float *)0x2533c8 - desc_min) * intensity + desc_min;
  if (value < *(float *)0x2533c0)
    value = *(float *)0x2533c0;
  else if (!(value <= desc_max))
    value = desc_max;

  *(float *)(effect + 0x3c) = value;
  *(uint8_t *)(effect + 0xe8) |= 1;
}


/* FUN_000a2ba0 (0xa2ba0) — readable C lift from XBE leaf.
 * effect_data@eax, effect@ebx; stack: unit_index, damage, scale. */
void FUN_000a2ba0(int unit_index, float damage_amount, float scale,
                  float *effect_data, void *effect)
{
  float scale30;
  float lerp_val;
  float thresh;
  float timer_f;
  float cur;
  char *eff;
  int i;
  int *dst;
  int *src;

  (void)unit_index;
  game_time_get();

  eff = (char *)effect;
  scale30 = scale * *(float *)0x253394;
  lerp_val = (*(float *)0x2533c8 - effect_data[10]) * damage_amount + effect_data[10];
  timer_f = (float)(int)*(int16_t *)(eff + 0xe2);
  thresh = scale30 * effect_data[0];
  cur = *(float *)(eff + 0xac);

  if (!(timer_f < thresh || lerp_val > cur))
    return;

  dst = (int *)(eff + 0x84);
  src = (int *)effect_data;
  for (i = 0; i < 18; i++)
    dst[i] = src[i];
  *(float *)(eff + 0xac) = lerp_val;

  /* fmul/fst/ftol in one asm block so ST0 keeps 80-bit product for _ftol2. */
  __asm__ volatile(
      "flds %0\n\t"
      "fmuls %1\n\t"
      "fsts %1\n\t"
      "call %P2\n\t"
      "movw %%ax, %3\n\t"
      "flds %0\n\t"
      "fmuls %4\n\t"
      "fstps %4\n\t"
      :
      : "m"(scale30), "m"(*(float *)(eff + 0x84)), "X"(FUN_001d9068),
        "m"(*(int16_t *)(eff + 0xe2)), "m"(*(float *)(eff + 0xa4))
      : "eax", "edx", "ecx", "st", "cc", "memory");
  *(uint8_t *)(eff + 0xe8) |= 4;
}


/* FUN_000a2c70 (0xa2c70) — readable C lift. function_type@eax */
float FUN_000a2c70(float scale, float numer, float denom, short function_type)
{
  float t = *(float *)0x2533c8 - (numer / denom);
  return transition_function_evaluate(function_type, t) * scale;
}
/* player_effect_continuous_refresh (0xa2d30) — readable C lift. */
void player_effect_continuous_refresh(void *effect, float *center)
{
  int16_t i;
  int player;
  char *pdata;
  int unit;
  float wpos[3];
  float dx, dy, dz, dist;

  for (i = 0; i < 4; i++) {
    player = local_player_get_player_index(i);
    if (player == -1)
      continue;
    pdata = (char *)datum_get(*(data_t **)0x5aa6d4, player);
    unit = *(int *)(pdata + 0x34);
    if (unit == -1)
      continue;
    object_get_world_position(unit, (vector3_t *)wpos);
    dx = center[0] - wpos[0];
    dy = center[1] - wpos[1];
    dz = center[2] - wpos[2];
    dist = __builtin_sqrtf(dx * dx + dy * dy + dz * dz);
    ((void (*)(int16_t, void *, float))player_effect_add_continuous_effect)(i, effect, dist);
  }
}

/* scripted_player_effect_set_translation (0xa2dc0) — readable C lift. */
void scripted_player_effect_set_translation(int a0, int a1, int a2)
{
  char *g = *(char **)0x4557ec;
  *(int *)(g + 0x3c4) = a0;
  *(int *)(g + 0x3c8) = a1;
  *(int *)(g + 0x3cc) = a2;
}

/* scripted_player_effect_start (0xa2df0) — readable C lift. */
void scripted_player_effect_start(float intensity, float seconds)
{
  char *fx;
  int ticks;
  int flags;

  fx = *(char **)0x4557ec;
  *(float *)(fx + 0x3dc) = intensity;
  ticks = (int)(seconds * *(float *)0x253394);
  *(short *)(fx + 0x3e0) = (short)ticks;
  *(short *)(fx + 0x3e2) = (short)ticks;
  flags = *(int *)(fx + 0x3e4);
  flags = (flags & ~2) | 1;
  *(int *)(fx + 0x3e4) = flags;
}


/* scripted_player_effect_stop (0xa2e40) — readable C lift. */
void scripted_player_effect_stop(float seconds)
{
  char *fx;
  int ticks;

  ticks = (int)(seconds * *(float *)0x253394);
  fx = *(char **)0x4557ec;
  *(short *)(fx + 0x3e0) = (short)ticks;
  *(short *)(fx + 0x3e2) = (short)ticks;
  *(int *)(fx + 0x3e4) |= 2;
}

/* player_telefrag_effect_start (0xa2ed0) — readable C lift (restored pre-naked). */
void player_telefrag_effect_start(void)
{
  int ecx = 0;
  int esi = 0;

  datum_get((void *)(uintptr_t)ecx, 0);
  /* cmp esi, -1 -> je 0xa2fb7 */
  player_effect_get(esi);
  rumble_set_direct_motors(0, 0, 0);
  ((void(*)(void))FUN_000a2ab0)();
  FUN_000a2ba0(0, 0.0f, 0.0f, (float *)0, (void *)0);

  (void)ecx;
  (void)esi;
}



/* player_effect_get_screen_flash (0xa2fc0) — readable C lift (restored pre-naked). */
void player_effect_get_screen_flash(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* test esi, esi -> jne 0xa2feb */
  display_assert((char *)0x0026af30, (char *)0x0026ae94, 484, 0);
  system_exit(0);
  console_is_active();
  /* test (char)eax, (char)eax -> jne 0xa328a */
  /* test (char)ecx, (char)ecx -> jne 0xa303f */
  game_time_get();
  /* cmp ecx, edx -> jg 0xa318c */
  game_time_get();
  game_time_get();
  /* test (char)eax, 0x41 -> jne 0xa30e8 */
  game_time_get();
  transition_function_evaluate(0, 0.0f);
  /* test (char)ecx, (char)ecx -> jne 0xa3143 */
  /* test (char)eax, 0x41 -> jne 0xa3181 */
  /* cmp (int16_t)eax, 0xffff -> je 0xa3289 */
  player_effect_get(eax);
  /* relift: cmp word ptr [edi + 0xde], 0 -> jg 0xa31ca */
  /* relift: test byte ptr [edi + 0xe8], 1 -> je 0xa3289 */
  /* test (char)eax, 0x41 -> jne 0xa3237 */
  transition_function_evaluate(0, 0.0f);
  game_time_get_elapsed();
  /* test (char)eax, 1 -> jne 0xa3269 */
  display_assert((char *)0x0026aef0, (char *)0x0026ae94, 530, 0);
  system_exit(0);
  csprintf((char *)0x005ab100, (char *)0x0025eb8c);
  display_assert((char *)(uintptr_t)eax, (char *)0, 0, 0);
  system_exit(0);

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}


/* FUN_000a32e0 (0xa32e0) — readable C lift. */
void FUN_000a32e0(float *obj, float pitch, float yaw)
{
  float dir[3];
  unsigned int *seed;
  char *base;

  base = (char *)obj;
  if (yaw != 0.0f) {
    seed = random_math_get_local_seed_address();
    random_seed_get_direction3d(seed, dir);
    FUN_001092d0(obj, dir, __builtin_sinf(yaw), __builtin_cosf(yaw));
  }
  if (pitch != 0.0f) {
    seed = random_math_get_local_seed_address();
    random_seed_get_direction3d(seed, dir);
    *(float *)(base + 0x28) = dir[0] * pitch;
    *(float *)(base + 0x2c) = dir[1] * pitch;
    *(float *)(base + 0x30) = dir[2] * pitch;
  }
}

/* player_effect_get_camera_effect_matrix (0xa3370) — readable C lift (restored pre-naked). */
void player_effect_get_camera_effect_matrix(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* test edi, edi -> jne 0xa339f */
  display_assert((char *)0x0026af40, (char *)0x0026ae94, 601, 0);
  system_exit(0);
  /* cmp (int16_t)esi, -1 -> je 0xa3881 */
  game_time_get();
  /* relift: test byte ptr [eax + 0x3e4], 1 -> je 0xa35a1 */
  /* test (int16_t)ecx, (int16_t)ecx -> jle 0xa3440 */
  /* relift: test byte ptr [eax + 0x3e4], 2 -> je 0xa3416 */
  game_time_get_elapsed();
  game_time_get_elapsed();
  /* test (char)ecx, 2 -> je 0xa3463 */
  rumble_player_set_scale(0.0f);
  /* relift: test byte ptr [eax + 0x3e4], 1 -> je 0xa3880 */
  /* test (char)eax, 0x41 -> jne 0xa34a0 */
  rumble_player_set_scale(0.0f);
  random_math_get_local_seed_address();
  random_real_range((void *)(uintptr_t)eax, 0.0f, 0.0f);
  random_math_get_local_seed_address();
  random_real_range((void *)(uintptr_t)eax, 0.0f, 0.0f);
  random_math_get_local_seed_address();
  random_real_range((void *)(uintptr_t)eax, 0.0f, 0.0f);
  FUN_00109e90((float *)(uintptr_t)esi, 0.0f, 0.0f, 0.0f);
  random_math_get_local_seed_address();
  random_real_range((void *)(uintptr_t)eax, 0.0f, 0.0f);
  random_math_get_local_seed_address();
  random_real_range((void *)(uintptr_t)eax, 0.0f, 0.0f);
  random_math_get_local_seed_address();
  random_real_range((void *)(uintptr_t)eax, 0.0f, 0.0f);
  player_effect_get(esi);
  /* test (char)ecx, dl -> jne 0xa35d3 */
  /* test (char)ecx, dl -> je 0xa35dc */
  transition_function_evaluate(0, 0.0f);
  FUN_001092d0((float *)(uintptr_t)ecx, (float *)(uintptr_t)eax, 0.0f, 0.0f);
  game_time_get_elapsed();
  /* relift: test byte ptr [ebx + 0xe8], dl -> je 0xa3880 */
  /* relift: test byte ptr [ebx + 0xe8], dl -> je 0xa3710 */
  transition_function_evaluate(0, 0.0f);
  FUN_0010a5e0(edx, 0.0f);
  /* test (char)eax, 0x41 -> jne 0xa37b4 */
  /* test (char)eax, 0x41 -> jne 0xa37d5 */
  ((void(*)(void))FUN_000a32e0)();
  rumble_set_direct_motors(0, 0, 0);
  game_time_get_elapsed();
  /* relift: cmp word ptr [ebx + 0xdc], 0 -> jle 0xa3853 */
  csmemset((void *)(uintptr_t)edi, 0, 16);
  ((void(*)(void))FUN_000a32e0)();
  game_time_get_elapsed();
  matrix4x3_multiply((float *)(uintptr_t)eax, (float *)(uintptr_t)edx, (float *)(uintptr_t)eax);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}



/* FUN_000a3890 (0xa3890) — XBE naked draft (batch 110). */
#if defined(__clang__)
static int (*const ba3890_gtime)(void) = game_time_get;
static float (*const ba3890_norm)(float *) = normalize3d;
static float * (*const ba3890_cb7e30)(int16_t local_player_index) = (void *)player_control_get_facing_angles;
static void (*const ba3890_c10cc40)(float *out, float *angles) = (void *)angles_to_vector;
static void (*const ba3890_c10c3c0)(void) = (void *)FUN_0010c3c0;
static void (*const ba3890_ftol)(void) = FUN_001d9068;
static unsigned int *(*const ba3890_lseed)(void) = random_math_get_local_seed_address;
static float (*const ba3890_rrange)(int *, float, float) = random_real_range;
static void (*const ba3890_rots)(float *, float *, float, float) = rotate_vector3d_by_sincos;
static float * (*const ba3890_cb7f10)(int16_t local_player_index, float *out_direction) = (void *)player_control_get_facing_direction;
static void (*const ba3890_cb8cf0)(int16_t a, float *delta) = (void *)FUN_000b8cf0;

__attribute__((naked, noinline))
void FUN_000a3890(int unit_index __attribute__((unused)), float *rumble_def __attribute__((unused)), void *direction __attribute__((unused)), float damage_amount __attribute__((unused)), float scale __attribute__((unused)), float *effect __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x28, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl %%eax, %%ebx\n\t"
      "call *%[gtime]\n\t"
      "flds 0x18(%%ebp)\n\t"
      "fmuls 0x253394\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "movswl 0xe0(%%ebx), %%eax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "flds 0x18(%%edi)\n\t"
      "flds 0x2533c8\n\t"
      ".byte 0xd8, 0xe1\n\t"
      "fmuls 0x14(%%ebp)\n\t"
      ".byte 0xd8, 0xc1\n\t"
      "fstps 0x18(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "fildl -0x4(%%ebp)\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "flds 0x50(%%ebx)\n\t"
      "fcomps -0x4(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .LFUN_000a3890_1\n\t"
      "flds 0x18(%%ebp)\n\t"
      "fcomps 0x68(%%ebx)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .LFUN_000a3890_1\n\t"
      "flds 0x18(%%ebp)\n\t"
      "fcomps 0x68(%%ebx)\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_000a3890_2\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fmuls (%%edi)\n\t"
      "fcomps -0x4(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_000a3890_2\n\t"
      ".LFUN_000a3890_1:\n\t"
      "movl 0x10(%%ebp), %%esi\n\t"
      "movl %%esi, %%ecx\n\t"
      "movl (%%ecx), %%edx\n\t"
      "movl 0x4(%%ecx), %%eax\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "movl %%edx, -0x1c(%%ebp)\n\t"
      "leal -0x1c(%%ebp), %%edx\n\t"
      "movl %%ecx, -0x14(%%ebp)\n\t"
      "pushl %%edx\n\t"
      "movl %%eax, -0x18(%%ebp)\n\t"
      "movl $0, -0x14(%%ebp)\n\t"
      "call *%[norm]\n\t"
      "fstp %%st(0)\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[cb7e30]\n\t"
      "movl (%%eax), %%ecx\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "leal -0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x28(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      "call *%[c10cc40]\n\t"
      "leal -0x28(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl $0, -0x20(%%ebp)\n\t"
      "call *%[norm]\n\t"
      "fstp %%st(0)\n\t"
      "flds -0x18(%%ebp)\n\t"
      "addl $0x14, %%esp\n\t"
      "fmuls -0x18(%%ebp)\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fmuls -0x1c(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fmuls -0x14(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fsubs 0x2533c8\n\t"
      "fabs\n\t"
      "fcompl 0x2533d0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_000a3890_3\n\t"
      "flds -0x24(%%ebp)\n\t"
      "fmuls -0x24(%%ebp)\n\t"
      "flds -0x28(%%ebp)\n\t"
      "fmuls -0x28(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds -0x20(%%ebp)\n\t"
      "fmuls -0x20(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fsubs 0x2533c8\n\t"
      "fabs\n\t"
      "fcompl 0x2533d0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_000a3890_3\n\t"
      "leal -0x1c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x28(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c10c3c0]\n\t"
      "flds -0xc(%%ebp)\n\t"
      "movl 0x18(%%ebp), %%edx\n\t"
      "movl %%edi, %%esi\n\t"
      "movl $0xd, %%ecx\n\t"
      "leal 0x50(%%ebx), %%edi\n\t"
      "rep movsl\n\t"
      "fmuls 0x50(%%ebx)\n\t"
      "fsts 0x50(%%ebx)\n\t"
      "addl $8, %%esp\n\t"
      "movl %%edx, 0x68(%%ebx)\n\t"
      "call *%[ftol]\n\t"
      "movl 0x60(%%ebx), %%ecx\n\t"
      "fld %%st(0)\n\t"
      "movw %%ax, 0xe0(%%ebx)\n\t"
      "fcos\n\t"
      "movl 0x64(%%ebx), %%eax\n\t"
      "movl %%eax, %%edx\n\t"
      "movl %%eax, 0x18(%%ebp)\n\t"
      "pushl %%edx\n\t"
      "movl %%ecx, %%eax\n\t"
      "pushl %%eax\n\t"
      "movl $0, 0x8(%%ebx)\n\t"
      "movl %%ecx, -0xc(%%ebp)\n\t"
      "fstps (%%ebx)\n\t"
      "fsin\n\t"
      "fstps 0x4(%%ebx)\n\t"
      "call *%[lseed]\n\t"
      "pushl %%eax\n\t"
      "call *%[rrange]\n\t"
      "fstps 0x18(%%ebp)\n\t"
      "addl $0xc, %%esp\n\t"
      "pushl $0x40c90fdb\n\t"
      "pushl $0\n\t"
      "call *%[lseed]\n\t"
      "pushl %%eax\n\t"
      "call *%[rrange]\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "movl 0x31fc44, %%eax\n\t"
      "flds 0x4(%%eax)\n\t"
      "leal 0xc(%%ebx), %%esi\n\t"
      "fmuls (%%ebx)\n\t"
      "pushl %%esi\n\t"
      "flds 0x4(%%ebx)\n\t"
      "fmuls (%%eax)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "flds 0x8(%%ebx)\n\t"
      "fmuls (%%eax)\n\t"
      "flds (%%ebx)\n\t"
      "fmuls 0x8(%%eax)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "flds 0x8(%%eax)\n\t"
      "fmuls 0x4(%%ebx)\n\t"
      "flds 0x4(%%eax)\n\t"
      "fmuls 0x8(%%ebx)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps (%%esi)\n\t"
      "fstps 0x4(%%esi)\n\t"
      "fstps 0x8(%%esi)\n\t"
      "call *%[norm]\n\t"
      "fstp %%st(0)\n\t"
      "addl $8, %%esp\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fcos\n\t"
      "fstps 0x4(%%esp)\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fsin\n\t"
      "fstps (%%esp)\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "call *%[rots]\n\t"
      "flds 0x18(%%ebp)\n\t"
      "fmuls (%%esi)\n\t"
      "addl $0x10, %%esp\n\t"
      "fstps (%%esi)\n\t"
      "flds 0x18(%%ebp)\n\t"
      "fmuls 0x4(%%esi)\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "fstps 0x4(%%esi)\n\t"
      "flds 0x18(%%ebp)\n\t"
      "fmuls 0x8(%%esi)\n\t"
      "fstps 0x8(%%esi)\n\t"
      "movb 0xe8(%%ebx), %%al\n\t"
      "orb $2, %%al\n\t"
      "movb %%al, 0xe8(%%ebx)\n\t"
      ".LFUN_000a3890_2:\n\t"
      "movl 0x10(%%ebp), %%esi\n\t"
      ".LFUN_000a3890_3:\n\t"
      "flds 0x24(%%edi)\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "flds 0x2533c8\n\t"
      "leal -0x28(%%ebp), %%ecx\n\t"
      ".byte 0xd8, 0xe1\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "fmuls 0x14(%%ebp)\n\t"
      ".byte 0xd8, 0xc1\n\t"
      "fstps 0x10(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "call *%[cb7f10]\n\t"
      "movl 0x31fc44, %%eax\n\t"
      "flds -0x20(%%ebp)\n\t"
      "fmuls 0x4(%%eax)\n\t"
      "leal -0x10(%%ebp), %%edx\n\t"
      "flds -0x24(%%ebp)\n\t"
      "pushl %%edx\n\t"
      "fmuls 0x8(%%eax)\n\t"
      "pushl %%ebx\n\t"
      ".byte 0xde, 0xe9\n\t"
      "flds -0x28(%%ebp)\n\t"
      "fmuls 0x8(%%eax)\n\t"
      "flds -0x20(%%ebp)\n\t"
      "fmuls (%%eax)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "flds -0x24(%%ebp)\n\t"
      "fmuls (%%eax)\n\t"
      "flds -0x28(%%ebp)\n\t"
      "fmuls 0x4(%%eax)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fxch %%st(2)\n\t"
      "fmuls (%%esi)\n\t"
      "fxch %%st(2)\n\t"
      "fmuls 0x8(%%esi)\n\t"
      ".byte 0xde, 0xc2\n\t"
      "fmuls 0x4(%%esi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fmuls 0x20(%%edi)\n\t"
      "fmuls 0x10(%%ebp)\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "flds -0x28(%%ebp)\n\t"
      "fmuls (%%esi)\n\t"
      "flds -0x20(%%ebp)\n\t"
      "fmuls 0x8(%%esi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds -0x24(%%ebp)\n\t"
      "fmuls 0x4(%%esi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fmuls 0x20(%%edi)\n\t"
      "fmuls 0x10(%%ebp)\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "call *%[cb8cf0]\n\t"
      "addl $0x10, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [gtime] "m"(ba3890_gtime), [norm] "m"(ba3890_norm), [cb7e30] "m"(ba3890_cb7e30), [c10cc40] "m"(ba3890_c10cc40), [c10c3c0] "m"(ba3890_c10c3c0), [ftol] "m"(ba3890_ftol), [lseed] "m"(ba3890_lseed), [rrange] "m"(ba3890_rrange), [rots] "m"(ba3890_rots), [cb7f10] "m"(ba3890_cb7f10), [cb8cf0] "m"(ba3890_cb8cf0)
      : "memory");
}
#else
#error "FUN_000a3890: clang naked draft required"
#endif

