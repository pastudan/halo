
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

/* player_effect_apply_damage (0xa3b80) — Apply damage-related effects to a
 * player.
 *
 * Uses the damage effect tag (jpt!) to set screen shake, vibration, and
 * directional damage indicators based on the angle of incoming damage
 * relative to the player's camera orientation.
 *
 * Confirmed: datum_get(*(data_t**)0x5aa6d4, player_handle) for player data.
 * Confirmed: assert_halt on direction != NULL.
 * Confirmed: lock_random_seed / unlock_random_seed bracket the entire function.
 * Confirmed: tag_get('jpt!', *damage_params) for tag lookup.
 * Confirmed: player_effect_set_from_descriptor(sVar1, effect, param_4, 1.0f,
 * jpt+0x24). Confirmed: *(unsigned int*)(player+0x1c8) & 0x100 checks vehicle
 * driver flag. Confirmed: Global floats: 0x2533c0=0.0f, 0x2533c8=1.0f,
 * 0x25fea8=~0.0, 0x254a58=~0.7854 (PI/4), 0x26af48=~2.3562 (3*PI/4),
 * 0x2568bc=~1.5708 (PI/2). Confirmed: local_player_get_player_index called
 * twice (original binary artifact). Confirmed: camera+0x20 is forward vector,
 * +0x2c is up vector. Confirmed: effect flags at +0xe4 (right), +0xe5
 * (forward), +0xe6 (down), +0xe7 (side).
 */
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

/* 0xa27a0 */
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

/* 0xa28e0 */
void scripted_player_effect_set_rotation(int a0, float a1, float a2)
{
  /* relift: no calls detected — manual review */
}

/* 0xa2920 */
void scripted_player_effect_set_rumble(int a0, float a1)
{
  /* relift: no calls detected — manual review */
}

/* 0xa2930 */
void player_telefrag_effect_stop(void)
{
  int ecx = 0;
  int esi = 0;

  datum_get((void *)(uintptr_t)ecx, 0);
  /* cmp esi, -1 -> je 0xa2963 */
  player_effect_get(esi);
  rumble_set_direct_motors(0, 0, 0);

  (void)ecx;
  (void)esi;
}

/* 0xa2970 */
void player_effect_screen_fade_in(int a0, float a1, float a2, int a3)
{
  game_time_get();
}

/* 0xa29c0 */
void player_effect_screen_fade_out(int a0, float a1, float a2, int a3)
{
  game_time_get();
}

/* 0xa2a10 */
void player_effect_get_damage_indicators(int player_index, void *out)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;

  player_effect_get(eax);
  csmemcpy((void *)(uintptr_t)ecx, (void *)(uintptr_t)esi, 0);
  /* relift: cmp byte ptr [esi], 0 -> je 0xa2a68 */
  game_time_get_elapsed();
  /* cmp edx, 0xff -> jge 0xa2a61 */
  game_time_get_elapsed();

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
}

/* 0xa2a70 */
void player_effect_clear_damage_indicators(int player_index)
{
  int eax = 0;

  player_effect_get(eax);
  csmemset((void *)(uintptr_t)eax, 0, 0);

  (void)eax;
}

/* 0xa2a90 */
void FUN_000a2a90(void)
{
  /* relift: no calls detected — manual review */
}

/* 0xa2ab0 */
void FUN_000a2ab0(void)
{
  int eax = 0;

  /* relift: cmp word ptr [eax*2 + 0x2ef7e0], 0 -> je 0xa2b90 */
  FUN_001d9068();
  /* test (char)eax, 0x41 -> jne 0xa2b6f */

  (void)eax;
}

/* 0xa2ba0 */
void FUN_000a2ba0(int unit_index, float damage_amount, float scale, float *effect_data, void *effect)
{
  int eax = 0;

  game_time_get();
  /* test (char)eax, 0x41 -> je 0xa2c14 */
  /* test (char)eax, 1 -> jne 0xa2c60 */
  FUN_001d9068();

  (void)eax;
}

/* 0xa2c70 */
void FUN_000a2c70(void)
{
  transition_function_evaluate(0, 0.0f);
}

/* 0xa2d30 */
void player_effect_continuous_refresh(void)
{
  int eax = 0;
  int ecx = 0;
  int esi = 0;

  local_player_get_player_index(esi);
  /* cmp eax, -1 -> je 0xa2daf */
  local_player_get_player_index(esi);
  datum_get((void *)(uintptr_t)eax, 0);
  /* cmp eax, -1 -> je 0xa2daf */
  object_get_world_position(0, (void *)(uintptr_t)ecx);
  player_effect_add_continuous_effect();
  /* cmp (int16_t)esi, 4 -> jl 0xa2d41 */

  (void)eax;
  (void)ecx;
  (void)esi;
}

/* 0xa2dc0 */
void scripted_player_effect_set_translation(int a0, float a1, float a2)
{
  /* relift: no calls detected — manual review */
}

/* 0xa2df0 */
void scripted_player_effect_start(int a0, float a1)
{
  /* relift: no calls detected — manual review */
}

/* 0xa2e40 */
void scripted_player_effect_stop(int a0)
{
  /* relift: no calls detected — manual review */
}

/* 0xa2ed0 */
void player_telefrag_effect_start(void)
{
  int ecx = 0;
  int esi = 0;

  datum_get((void *)(uintptr_t)ecx, 0);
  /* cmp esi, -1 -> je 0xa2fb7 */
  player_effect_get(esi);
  rumble_set_direct_motors(0, 0, 0);
  FUN_000a2ab0();
  FUN_000a2ba0(0, 0.0f, 0.0f, (float *)0, (void *)0);

  (void)ecx;
  (void)esi;
}

/* 0xa2fc0 */
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

/* 0xa32e0 */
void FUN_000a32e0(void)
{
  int eax = 0;
  int ecx = 0;
  int esi = 0;

  random_math_get_local_seed_address();
  random_seed_get_direction3d((void *)(uintptr_t)eax, (float *)0);
  FUN_001092d0((float *)(uintptr_t)esi, (float *)(uintptr_t)ecx, 0.0f, 0.0f);
  random_math_get_local_seed_address();
  random_seed_get_direction3d((void *)(uintptr_t)eax, (float *)0);

  (void)eax;
  (void)ecx;
  (void)esi;
}

/* 0xa3370 */
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
  FUN_000a32e0();
  rumble_set_direct_motors(0, 0, 0);
  game_time_get_elapsed();
  /* relift: cmp word ptr [ebx + 0xdc], 0 -> jle 0xa3853 */
  csmemset((void *)(uintptr_t)edi, 0, 16);
  FUN_000a32e0();
  game_time_get_elapsed();
  matrix4x3_multiply((float *)(uintptr_t)eax, (float *)(uintptr_t)edx, (float *)(uintptr_t)eax);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0xa3890 */
void FUN_000a3890(int unit_index, float *rumble_def, void *direction, float damage_amount, float scale, float *effect)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;

  game_time_get();
  /* test (char)eax, 0x41 -> je 0xa3912 */
  /* test (char)eax, 0x41 -> je 0xa3912 */
  /* test (char)eax, 1 -> jne 0xa3ad5 */
  /* test (char)eax, 0x41 -> jne 0xa3ad5 */
  normalize3d((float *)(uintptr_t)edx);
  player_control_get_facing_angles(eax);
  angles_to_vector((float *)(uintptr_t)ecx, (float *)(uintptr_t)eax);
  normalize3d((float *)(uintptr_t)edx);
  FUN_0010c3c0();
  FUN_001d9068();
  random_math_get_local_seed_address();
  random_real_range((void *)(uintptr_t)eax, 0.0f, 0.0f);
  random_math_get_local_seed_address();
  random_real_range((void *)(uintptr_t)eax, 0.0f, 0.0f);
  normalize3d((float *)0);
  rotate_vector3d_by_sincos((float *)(uintptr_t)esi, (float *)(uintptr_t)ebx, 0.0f, 0.0f);
  player_control_get_facing_direction(0, (float *)0);
  FUN_000b8cf0(0, (float *)0);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
}
