
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
  (void)0;
}

/* 0xa2920 */
void scripted_player_effect_set_rumble(int a0, float a1)
{
  /* relift: no calls detected — manual review */
  (void)0;
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
  (void)0;
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
  (void)0;
}

/* 0xa2df0 */
void scripted_player_effect_start(int a0, float a1)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0xa2e40 */
void scripted_player_effect_stop(int a0)
{
  /* relift: no calls detected — manual review */
  (void)0;
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

/* player_effect_get_camera_effect_matrix (0xa3370) — XBE naked draft (batch 106). */
#if defined(__clang__)
static void (*const ba3370_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const ba3370_exitfn)(int) = system_exit;
static int (*const ba3370_gtime)(void) = game_time_get;
static int16_t (*const ba3370_cb5ae0)(void) = game_time_get_elapsed;
static void (*const ba3370_cb9ba0)(float scale) = rumble_player_set_scale;
static unsigned int *(*const ba3370_lseed)(void) = random_math_get_local_seed_address;
static float (*const ba3370_rrange)(int *, float, float) = random_real_range;
static void (*const ba3370_c109e90)(float *out, float yaw, float pitch, float roll) = FUN_00109e90;
static char * (*const ba3370_ca2690)(int16_t local_player_index) = player_effect_get;
static float (*const ba3370_c10a710)(short function_type, float t) = transition_function_evaluate;
static void (*const ba3370_c1092d0)(float *out_matrix, float *axis, float sine, float cosine) = FUN_001092d0;
static float (*const ba3370_c10a5e0)(int16_t function_type, float input) = FUN_0010a5e0;
static void (*const ba3370_ca32e0)(void) = FUN_000a32e0;
static void (*const ba3370_cb9da0)(short local_player_index, int left_motor, int right_motor) = rumble_set_direct_motors;
static void *(*const ba3370_memset)(void *, int, unsigned int) = csmemset;
static void (*const ba3370_c109850)(float *a, float *b, float *out) = matrix4x3_multiply;

__attribute__((naked, noinline))
void player_effect_get_camera_effect_matrix(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x48, %%esp\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .Lplayer_effect_get_camera_effect_matrix_1\n\t"
      "pushl $1\n\t"
      "pushl $0x259\n\t"
      "pushl $0x26ae94\n\t"
      "pushl $0x26af40\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lplayer_effect_get_camera_effect_matrix_1:\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "cmpw $-1, %%si\n\t"
      "je .Lplayer_effect_get_camera_effect_matrix_23\n\t"
      "pushl %%ebx\n\t"
      "call *%[gtime]\n\t"
      "movl 0x4557ec, %%eax\n\t"
      "testb $1, 0x3e4(%%eax)\n\t"
      "je .Lplayer_effect_get_camera_effect_matrix_8\n\t"
      "movl 0x3dc(%%eax), %%ecx\n\t"
      "movl 0x31fc60, %%esi\n\t"
      "leal 0x3c4(%%eax), %%ebx\n\t"
      "movl %%ecx, 0x8(%%ebp)\n\t"
      "movl $0xd, %%ecx\n\t"
      "rep movsl\n\t"
      "movw 0x1c(%%ebx), %%cx\n\t"
      "testw %%cx, %%cx\n\t"
      "jle .Lplayer_effect_get_camera_effect_matrix_3\n\t"
      "testb $2, 0x3e4(%%eax)\n\t"
      "je .Lplayer_effect_get_camera_effect_matrix_2\n\t"
      "movswl 0x1e(%%ebx), %%eax\n\t"
      "movswl %%cx, %%edx\n\t"
      "movl %%edx, -0x8(%%ebp)\n\t"
      "fildl -0x8(%%ebp)\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "fidivl -0x8(%%ebp)\n\t"
      "fmuls 0x8(%%ebp)\n\t"
      "fstps 0x8(%%ebp)\n\t"
      "call *%[cb5ae0]\n\t"
      "subw %%ax, 0x1c(%%ebx)\n\t"
      "jmp .Lplayer_effect_get_camera_effect_matrix_4\n\t"
      ".Lplayer_effect_get_camera_effect_matrix_2:\n\t"
      "movswl 0x1e(%%ebx), %%edx\n\t"
      "movswl %%cx, %%ecx\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "fildl -0x8(%%ebp)\n\t"
      "movl %%edx, -0x8(%%ebp)\n\t"
      "fidivl -0x8(%%ebp)\n\t"
      "fsubrs 0x2533c8\n\t"
      "fmuls 0x8(%%ebp)\n\t"
      "fstps 0x8(%%ebp)\n\t"
      "call *%[cb5ae0]\n\t"
      "subw %%ax, 0x1c(%%ebx)\n\t"
      "jmp .Lplayer_effect_get_camera_effect_matrix_4\n\t"
      ".Lplayer_effect_get_camera_effect_matrix_3:\n\t"
      "movl 0x3e4(%%eax), %%ecx\n\t"
      "testb $2, %%cl\n\t"
      "je .Lplayer_effect_get_camera_effect_matrix_5\n\t"
      "andl $0xfffffffe, %%ecx\n\t"
      "pushl $0\n\t"
      "movl %%ecx, 0x3e4(%%eax)\n\t"
      "call *%[cb9ba0]\n\t"
      "addl $4, %%esp\n\t"
      ".Lplayer_effect_get_camera_effect_matrix_4:\n\t"
      "movl 0x4557ec, %%eax\n\t"
      ".Lplayer_effect_get_camera_effect_matrix_5:\n\t"
      "testb $1, 0x3e4(%%eax)\n\t"
      "je .Lplayer_effect_get_camera_effect_matrix_22\n\t"
      "flds 0x8(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lplayer_effect_get_camera_effect_matrix_6\n\t"
      "movl $0, 0x8(%%ebp)\n\t"
      "jmp .Lplayer_effect_get_camera_effect_matrix_7\n\t"
      ".Lplayer_effect_get_camera_effect_matrix_6:\n\t"
      "flds 0x8(%%ebp)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lplayer_effect_get_camera_effect_matrix_7\n\t"
      "movl $0x3f800000, 0x8(%%ebp)\n\t"
      ".Lplayer_effect_get_camera_effect_matrix_7:\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[cb9ba0]\n\t"
      "addl $4, %%esp\n\t"
      "pushl $0x3f800000\n\t"
      "pushl $0xbf800000\n\t"
      "call *%[lseed]\n\t"
      "pushl %%eax\n\t"
      "call *%[rrange]\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "addl $0xc, %%esp\n\t"
      "pushl $0x3f800000\n\t"
      "pushl $0xbf800000\n\t"
      "call *%[lseed]\n\t"
      "pushl %%eax\n\t"
      "call *%[rrange]\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "addl $0xc, %%esp\n\t"
      "pushl $0x3f800000\n\t"
      "pushl $0xbf800000\n\t"
      "call *%[lseed]\n\t"
      "pushl %%eax\n\t"
      "call *%[rrange]\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fmuls 0x14(%%ebx)\n\t"
      "movl 0xc(%%ebp), %%esi\n\t"
      "fmuls 0x8(%%ebp)\n\t"
      "fstps 0x8(%%esp)\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fmuls 0x10(%%ebx)\n\t"
      "fmuls 0x8(%%ebp)\n\t"
      "fstps 0x4(%%esp)\n\t"
      "fmuls 0xc(%%ebx)\n\t"
      "fmuls 0x8(%%ebp)\n\t"
      "fstps (%%esp)\n\t"
      "pushl %%esi\n\t"
      "call *%[c109e90]\n\t"
      "addl $0x10, %%esp\n\t"
      "pushl $0x3f800000\n\t"
      "pushl $0xbf800000\n\t"
      "call *%[lseed]\n\t"
      "pushl %%eax\n\t"
      "call *%[rrange]\n\t"
      "fstps 0xc(%%ebp)\n\t"
      "addl $0xc, %%esp\n\t"
      "pushl $0x3f800000\n\t"
      "pushl $0xbf800000\n\t"
      "call *%[lseed]\n\t"
      "pushl %%eax\n\t"
      "call *%[rrange]\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "addl $0xc, %%esp\n\t"
      "pushl $0x3f800000\n\t"
      "pushl $0xbf800000\n\t"
      "call *%[lseed]\n\t"
      "pushl %%eax\n\t"
      "call *%[rrange]\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "flds 0xc(%%ebp)\n\t"
      "addl $0xc, %%esp\n\t"
      "fmuls 0x8(%%ebx)\n\t"
      "fmuls 0x8(%%ebp)\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fmuls (%%ebx)\n\t"
      "fmuls 0x8(%%ebp)\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fmuls 0x4(%%ebx)\n\t"
      "popl %%ebx\n\t"
      "popl %%edi\n\t"
      "fmuls 0x8(%%ebp)\n\t"
      "fstps 0x28(%%esi)\n\t"
      "fstps 0x2c(%%esi)\n\t"
      "fstps 0x30(%%esi)\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lplayer_effect_get_camera_effect_matrix_8:\n\t"
      "pushl %%esi\n\t"
      "call *%[ca2690]\n\t"
      "movl %%eax, %%ebx\n\t"
      "movw 0xe0(%%ebx), %%ax\n\t"
      "movb 0xe8(%%ebx), %%dl\n\t"
      "addl $4, %%esp\n\t"
      "testw %%ax, %%ax\n\t"
      "movb $2, %%cl\n\t"
      "jg .Lplayer_effect_get_camera_effect_matrix_9\n\t"
      "testb %%dl, %%cl\n\t"
      "jne .Lplayer_effect_get_camera_effect_matrix_10\n\t"
      "movl 0x31fc60, %%esi\n\t"
      "jmp .Lplayer_effect_get_camera_effect_matrix_13\n\t"
      ".Lplayer_effect_get_camera_effect_matrix_9:\n\t"
      "testb %%dl, %%cl\n\t"
      "je .Lplayer_effect_get_camera_effect_matrix_11\n\t"
      ".Lplayer_effect_get_camera_effect_matrix_10:\n\t"
      "movl $0x3f800000, -0x4(%%ebp)\n\t"
      "jmp .Lplayer_effect_get_camera_effect_matrix_12\n\t"
      ".Lplayer_effect_get_camera_effect_matrix_11:\n\t"
      "flds 0x50(%%ebx)\n\t"
      "movswl %%ax, %%ecx\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "movl 0x68(%%ebx), %%edx\n\t"
      "xorl %%eax, %%eax\n\t"
      "fildl -0x8(%%ebp)\n\t"
      "movw 0x54(%%ebx), %%ax\n\t"
      "pushl %%ecx\n\t"
      "movl %%edx, -0x8(%%ebp)\n\t"
      "fsubrs 0x50(%%ebx)\n\t"
      ".byte 0xd8, 0xf1\n\t"
      "fsubrs 0x2533c8\n\t"
      "fstps (%%esp)\n\t"
      "pushl %%eax\n\t"
      "fstp %%st(0)\n\t"
      "call *%[c10a710]\n\t"
      "fmuls -0x8(%%ebp)\n\t"
      "addl $8, %%esp\n\t"
      "fstps -0x4(%%ebp)\n\t"
      ".Lplayer_effect_get_camera_effect_matrix_12:\n\t"
      "movb 0xe8(%%ebx), %%dl\n\t"
      "flds 0x4(%%ebx)\n\t"
      "andb $0xfd, %%dl\n\t"
      "movb %%dl, 0xe8(%%ebx)\n\t"
      "movl 0x31fc44, %%eax\n\t"
      "fmuls (%%eax)\n\t"
      "subl $8, %%esp\n\t"
      "flds (%%ebx)\n\t"
      "leal -0x48(%%ebp), %%ecx\n\t"
      "fmuls 0x4(%%eax)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "flds 0x8(%%eax)\n\t"
      "fmuls (%%ebx)\n\t"
      "flds 0x8(%%ebx)\n\t"
      "fmuls (%%eax)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "flds 0x8(%%ebx)\n\t"
      "fmuls 0x4(%%eax)\n\t"
      "flds 0x8(%%eax)\n\t"
      "leal -0x14(%%ebp), %%eax\n\t"
      "fmuls 0x4(%%ebx)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fmuls 0x58(%%ebx)\n\t"
      "fld %%st(0)\n\t"
      "fcos\n\t"
      "fstps 0x4(%%esp)\n\t"
      "fsin\n\t"
      "fstps (%%esp)\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1092d0]\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fmuls 0x5c(%%ebx)\n\t"
      "addl $0x10, %%esp\n\t"
      "fld %%st(0)\n\t"
      "fmuls (%%ebx)\n\t"
      "fld %%st(1)\n\t"
      "fmuls 0x4(%%ebx)\n\t"
      "fstps -0x1c(%%ebp)\n\t"
      "fxch %%st(1)\n\t"
      "fmuls 0x8(%%ebx)\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fmuls 0xc(%%ebx)\n\t"
      ".byte 0xd8, 0xc1\n\t"
      "fstps -0x20(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fmuls 0x10(%%ebx)\n\t"
      "fadds -0x1c(%%ebp)\n\t"
      "fstps -0x1c(%%ebp)\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fmuls 0x14(%%ebx)\n\t"
      "fadds -0x18(%%ebp)\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "call *%[cb5ae0]\n\t"
      "subw %%ax, 0xe0(%%ebx)\n\t"
      "leal -0x48(%%ebp), %%esi\n\t"
      ".Lplayer_effect_get_camera_effect_matrix_13:\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "movl $0xd, %%ecx\n\t"
      "rep movsl\n\t"
      "movw 0xe2(%%ebx), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "movb $4, %%dl\n\t"
      "jg .Lplayer_effect_get_camera_effect_matrix_14\n\t"
      "testb %%dl, 0xe8(%%ebx)\n\t"
      "je .Lplayer_effect_get_camera_effect_matrix_22\n\t"
      ".Lplayer_effect_get_camera_effect_matrix_14:\n\t"
      "movl 0x31fc60, %%esi\n\t"
      "movl $0xd, %%ecx\n\t"
      "leal -0x48(%%ebp), %%edi\n\t"
      "rep movsl\n\t"
      "testb %%dl, 0xe8(%%ebx)\n\t"
      "je .Lplayer_effect_get_camera_effect_matrix_15\n\t"
      "movl $0x3f800000, -0x8(%%ebp)\n\t"
      "jmp .Lplayer_effect_get_camera_effect_matrix_16\n\t"
      ".Lplayer_effect_get_camera_effect_matrix_15:\n\t"
      "flds 0x84(%%ebx)\n\t"
      "movswl %%ax, %%edx\n\t"
      "movl %%edx, -0x8(%%ebp)\n\t"
      "movl 0xac(%%ebx), %%eax\n\t"
      "pushl %%ecx\n\t"
      "fildl -0x8(%%ebp)\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x88(%%ebx), %%ax\n\t"
      "fsubrs 0x84(%%ebx)\n\t"
      ".byte 0xd8, 0xf1\n\t"
      "fsubrs 0x2533c8\n\t"
      "fstps (%%esp)\n\t"
      "pushl %%eax\n\t"
      "fstp %%st(0)\n\t"
      "call *%[c10a710]\n\t"
      "fmuls -0x8(%%ebp)\n\t"
      "addl $8, %%esp\n\t"
      "fstps -0x8(%%ebp)\n\t"
      ".Lplayer_effect_get_camera_effect_matrix_16:\n\t"
      "movswl 0xe2(%%ebx), %%ecx\n\t"
      "movl %%ecx, -0x4(%%ebp)\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0xa0(%%ebx), %%dx\n\t"
      "fildl -0x4(%%ebp)\n\t"
      "pushl %%ecx\n\t"
      "fsubrs 0x84(%%ebx)\n\t"
      "fdivs 0xa4(%%ebx)\n\t"
      "fstps (%%esp)\n\t"
      "pushl %%edx\n\t"
      "call *%[c10a5e0]\n\t"
      "fmuls 0xa8(%%ebx)\n\t"
      "flds 0x2533c8\n\t"
      "addl $8, %%esp\n\t"
      "fsubs 0xa8(%%ebx)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fmuls -0x8(%%ebp)\n\t"
      "fld %%st(0)\n\t"
      "fmuls 0x8c(%%ebx)\n\t"
      "fcoms 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lplayer_effect_get_camera_effect_matrix_17\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "jmp .Lplayer_effect_get_camera_effect_matrix_18\n\t"
      ".Lplayer_effect_get_camera_effect_matrix_17:\n\t"
      "fstp %%st(0)\n\t"
      "movl $0, -0x8(%%ebp)\n\t"
      ".Lplayer_effect_get_camera_effect_matrix_18:\n\t"
      "fmuls 0x90(%%ebx)\n\t"
      "fcoms 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lplayer_effect_get_camera_effect_matrix_19\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "jmp .Lplayer_effect_get_camera_effect_matrix_20\n\t"
      ".Lplayer_effect_get_camera_effect_matrix_19:\n\t"
      "fstp %%st(0)\n\t"
      "movl $0, -0x4(%%ebp)\n\t"
      ".Lplayer_effect_get_camera_effect_matrix_20:\n\t"
      "movb 0xe8(%%ebx), %%cl\n\t"
      "flds -0x4(%%ebp)\n\t"
      "andb $0xfb, %%cl\n\t"
      "movb %%cl, 0xe8(%%ebx)\n\t"
      "fadds 0xd8(%%ebx)\n\t"
      "leal 0xcc(%%ebx), %%edi\n\t"
      "subl $8, %%esp\n\t"
      "fstps 0x4(%%esp)\n\t"
      "leal -0x48(%%ebp), %%esi\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fadds 0x8(%%edi)\n\t"
      "fstps (%%esp)\n\t"
      "call *%[ca32e0]\n\t"
      "movl 0x4(%%edi), %%eax\n\t"
      "movl (%%edi), %%ecx\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[cb9da0]\n\t"
      "addl $0x14, %%esp\n\t"
      "call *%[cb5ae0]\n\t"
      "addw %%ax, 0xdc(%%ebx)\n\t"
      "cmpw $0, 0xdc(%%ebx)\n\t"
      "jle .Lplayer_effect_get_camera_effect_matrix_21\n\t"
      "pushl $0x10\n\t"
      "pushl $0\n\t"
      "pushl %%edi\n\t"
      "movw $0, 0xdc(%%ebx)\n\t"
      "call *%[memset]\n\t"
      "addl $0xc, %%esp\n\t"
      ".Lplayer_effect_get_camera_effect_matrix_21:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "leal -0x48(%%ebp), %%esi\n\t"
      "call *%[ca32e0]\n\t"
      "call *%[cb5ae0]\n\t"
      "subw %%ax, 0xe2(%%ebx)\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x48(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c109850]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lplayer_effect_get_camera_effect_matrix_22:\n\t"
      "popl %%ebx\n\t"
      ".Lplayer_effect_get_camera_effect_matrix_23:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(ba3370_assert), [exitfn] "m"(ba3370_exitfn), [gtime] "m"(ba3370_gtime), [cb5ae0] "m"(ba3370_cb5ae0), [cb9ba0] "m"(ba3370_cb9ba0), [lseed] "m"(ba3370_lseed), [rrange] "m"(ba3370_rrange), [c109e90] "m"(ba3370_c109e90), [ca2690] "m"(ba3370_ca2690), [c10a710] "m"(ba3370_c10a710), [c1092d0] "m"(ba3370_c1092d0), [c10a5e0] "m"(ba3370_c10a5e0), [ca32e0] "m"(ba3370_ca32e0), [cb9da0] "m"(ba3370_cb9da0), [memset] "m"(ba3370_memset), [c109850] "m"(ba3370_c109850)
      : "memory");
}
#else
#error "player_effect_get_camera_effect_matrix: clang naked draft required"
#endif


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
