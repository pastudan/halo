/* Return a pointer to the player control data slot for a local player.
 * Each slot is 0x40 bytes, starting at offset 0x10 in the globals struct. */
void *player_control_get_data(int16_t local_player_index)
{
  assert_halt(local_player_index >= 0 &&
              local_player_index < MAXIMUM_NUMBER_OF_LOCAL_PLAYERS);
  return (char *)player_control_globals + local_player_index * 0x40 + 0x10;
}

void player_control_initialize(void)
{
  player_control_globals = (player_control_globals_t *)game_state_malloc(
      "player control globals", 0, sizeof(player_control_globals_t));
}

void player_control_dispose(void)
{
}

/* Scripted camera takeover: clear bit0 of globals+0xc when enable!=0 (player
 * camera allowed); set bit0 when enable==0 (scripted camera lock). */
void scripted_player_control_set_camera_control(char enable)
{
  int *flags;

  flags = (int *)((char *)player_control_globals + 0xc);
  if (enable)
    *flags &= ~1;
  else
    *flags |= 1;
}

float player_control_get_autoaim_level(int16_t local_player_index)
{
  assert_halt(local_player_index >= 0 &&
              local_player_index < MAXIMUM_NUMBER_OF_LOCAL_PLAYERS);
  return *(float *)((char *)player_control_globals +
                    (int)local_player_index * 0x40 + 0x3c);
}

void players_unzoom_all(void)
{
  int16_t i;

  for (i = 0; i < MAXIMUM_NUMBER_OF_LOCAL_PLAYERS; i++) {
    assert_halt(i >= 0 && i < MAXIMUM_NUMBER_OF_LOCAL_PLAYERS);
    *(int16_t *)((char *)player_control_globals + (int)i * 0x40 + 0x34) =
        (int16_t)NONE;
  }
}

int16_t player_control_get_zoom_level(int16_t local_player_index)
{
  char *slot;

  if (local_player_index == (int16_t)NONE)
    return (int16_t)NONE;
  slot = (char *)player_control_get_data(local_player_index);
  return *(int16_t *)(slot + 0x24);
}

void player_control_action_test_reset(void)
{
  *(int *)player_control_globals = 0;
  *((int *)player_control_globals + 1) = 0;
}

char player_control_action_test_accept(void)
{
  int *g;

  g = (int *)player_control_globals;
  g[1] |= 4;
  g[2] |= 4;
  return (char)((g[0] >> 2) & 1);
}

char player_control_action_test_back(void)
{
  int *g;

  g = (int *)player_control_globals;
  g[1] |= 8;
  g[2] |= 8;
  return (char)((g[0] >> 3) & 1);
}

char player_control_action_test_action(void)
{
  int *g;

  g = (int *)player_control_globals;
  g[1] |= 1;
  g[2] |= 1;
  return (char)(g[0] & 1);
}

char player_control_action_test_jump(void)
{
  return (char)((*(int *)player_control_globals >> 1) & 1);
}

char player_control_action_test_primary_trigger(void)
{
  return (char)((*(int *)player_control_globals >> 4) & 1);
}

char player_control_action_test_grenade_trigger(void)
{
  return (char)((*(int *)player_control_globals >> 5) & 1);
}

char player_control_action_test_zoom(void)
{
  return (char)((*(int *)player_control_globals >> 6) & 1);
}

/* True when all relative-move bits (0x7800) are set. */
char player_control_action_test_move_relative_all_directions(void)
{
  return (char)((~*(int *)player_control_globals & 0x7800) == 0);
}

/* True when all relative-look bits (0x780) are set. */
char player_control_action_test_look_relative_all_directions(void)
{
  return (char)((~*(int *)player_control_globals & 0x780) == 0);
}

char player_control_action_test_look_relative_left(void)
{
  return (char)((*(int *)player_control_globals >> 9) & 1);
}

char player_control_action_test_look_relative_right(void)
{
  return (char)((*(int *)player_control_globals >> 10) & 1);
}

char player_control_action_test_look_relative_up(void)
{
  return (char)((*(int *)player_control_globals >> 7) & 1);
}

char player_control_action_test_look_relative_down(void)
{
  return (char)((*(int *)player_control_globals >> 8) & 1);
}

/* Smallest signed angle delta b-a, wrapped into [-pi, pi). */
float FUN_000b6dd0(float a, float b)
{
  float diff;

  diff = b - a;
  if (diff >= *(float *)0x256980)
    diff -= *(float *)0x255a54;
  if (diff <= *(float *)0x26e280)
    diff += *(float *)0x255a54;
  return diff;
}

/* If |vec| > max_len, scale vec onto the circle of radius max_len and return 1;
 * otherwise leave vec unchanged and return 0. */
char limit2d(float *vec, float max_len)
{
  float len_sq;
  float scale;

  len_sq = vec[0] * vec[0] + vec[1] * vec[1];
  if (len_sq > max_len * max_len) {
    scale = max_len / sqrtf(len_sq);
    vec[0] *= scale;
    vec[1] *= scale;
    return 1;
  }
  return 0;
}

/* Move *value toward target by at most max_delta per call. */
void interpolate_scalar(float *value, float target, float max_delta)
{
  float delta;

  delta = target - *value;
  if (delta < -max_delta)
    *value += -max_delta;
  else if (delta > max_delta)
    *value += max_delta;
  else
    *value += delta;
}

/* Piecewise-linear sample of table[0..count) at |t| in [0,1], with sign of t
 * applied by negating the result when t >= 0 (matches XBE polarity). */
float evaluate_piecewise_linear_function(int16_t count, float *table, float t)
{
  char positive;
  int n;
  float idx_f;
  int16_t i;
  int16_t j;
  float result;

  positive = 1;
  if (t < *(float *)0x2533c0)
    positive = 0;
  n = (int)count - 1;
  idx_f = fabsf(t) * (float)n;
  if (idx_f < 0.0)
    idx_f = 0.0f;
  else if (idx_f > (float)count - *(float *)0x2533c8)
    idx_f = (float)count - *(float *)0x2533c8;
  i = (int16_t)(int)idx_f;
  if (i < 0)
    i = 0;
  else if ((int)i > n)
    i = (int16_t)n;
  j = (int16_t)(i + 1);
  if ((int)j > n)
    j = (int16_t)n;
  assert_halt(table && i >= 0 && i <= j && j < count);
  result = table[i] + (idx_f - (float)i) * (table[j] - table[i]);
  if (positive)
    result = -result;
  return result;
}

int player_control_get_unit_index(int16_t local_player_index)
{
  assert_halt(local_player_index >= 0 &&
              local_player_index < MAXIMUM_NUMBER_OF_LOCAL_PLAYERS);
  return *(int *)((char *)player_control_globals +
                  (int)local_player_index * 0x40 + 0x10);
}

int player_control_get_aiming_unit_index(int16_t local_player_index)
{
  int unit_handle;

  assert_halt(local_player_index >= 0 &&
              local_player_index < MAXIMUM_NUMBER_OF_LOCAL_PLAYERS);
  unit_handle = *(int *)((char *)player_control_globals +
                         (int)local_player_index * 0x40 + 0x10);
  return unit_get_aiming_unit_index(unit_handle);
}

int player_control_get_target_object_index(int16_t local_player_index)
{
  char *slot;
  int target_handle;

  assert_halt(local_player_index >= 0 &&
              local_player_index < MAXIMUM_NUMBER_OF_LOCAL_PLAYERS);
  slot = (char *)player_control_globals + (int)local_player_index * 0x40 + 0x10;
  target_handle = *(int *)(slot + 0x28);
  if (object_try_and_get_and_verify_type(target_handle, NONE))
    return *(int *)(slot + 0x28);
  return NONE;
}

float player_control_get_field_of_view(int16_t local_player_index)
{
  char *slot;
  int unit_handle;
  void *unit_obj;
  void *unit_tag;
  int weapon_handle;
  int16_t zoom;

  assert_halt(local_player_index >= 0 &&
              local_player_index < MAXIMUM_NUMBER_OF_LOCAL_PLAYERS);
  slot = (char *)player_control_globals + (int)local_player_index * 0x40 + 0x10;
  unit_handle = *(int *)slot;
  if (unit_handle == NONE)
    return *(float *)0x26e270;
  unit_obj = object_get_and_verify_type(unit_handle, 3);
  unit_tag = tag_get(0x756e6974 /* 'unit' */, *(int *)unit_obj);
  zoom = *(int16_t *)(slot + 0x24);
  weapon_handle = unit_get_weapon(unit_handle, *(int16_t *)((char *)unit_obj + 0x2a2));
  if (weapon_handle != NONE)
    return weapon_get_field_of_view(
        weapon_handle, *(float *)((char *)unit_tag + 0x1a0), zoom);
  return *(float *)((char *)unit_tag + 0x1a0);
}

/* Fill out_info with the unit/vehicle camera used for this local player:
 * +0 object handle, +4 seat index, +8 camera tag ptr, +0xc seat position. */
void player_control_get_unit_camera_info(int16_t local_player_index,
                                         void *out_info)
{
  char *out;
  int unit_handle;
  void *unit_obj;
  int parent_handle;
  void *parent_obj;
  void *vehi_tag;
  void *seat_elem;
  void *unit_tag;

  assert_halt(out_info != NULL);
  out = (char *)out_info;
  assert_halt(local_player_index >= 0 &&
              local_player_index < MAXIMUM_NUMBER_OF_LOCAL_PLAYERS);
  *(int *)(out + 8) = 0;
  unit_handle = *(int *)((char *)player_control_globals +
                         (int)local_player_index * 0x40 + 0x10);
  *(int *)out = unit_handle;
  *(int16_t *)(out + 4) = (int16_t)NONE;
  if (unit_handle == NONE)
    return;
  unit_obj = object_get_and_verify_type(unit_handle, 3);
  unit_set_seat_state(unit_handle, (float *)(out + 0xc));
  parent_handle = *(int *)((char *)unit_obj + 0xcc);
  if (parent_handle != NONE) {
    parent_obj = object_try_and_get_and_verify_type(parent_handle, 2);
    if (parent_obj) {
      vehi_tag = tag_get(0x76656869 /* 'vehi' */, *(int *)parent_obj);
      seat_elem = tag_block_get_element((char *)vehi_tag + 0x2e4,
                                        *(int16_t *)((char *)unit_obj + 0x2a0),
                                        0x11c);
      *(int *)out = parent_handle;
      *(void **)(out + 8) = (char *)seat_elem + 0x84;
      *(int16_t *)(out + 4) = *(int16_t *)((char *)unit_obj + 0x2a0);
      unit_obj = object_get_and_verify_type(parent_handle, 3);
    }
  }
  if (*(int16_t *)(out + 4) == (int16_t)NONE) {
    unit_tag = tag_get(0x756e6974 /* 'unit' */, *(int *)unit_obj);
    *(void **)(out + 8) = (char *)unit_tag + 0x1a8;
  }
}

/* Apply look deltas (dx=yaw, dy=pitch) to a local player's desired facing,
 * including vehicle-seat yaw limits, camera pitch clamps, and autoaim smoothing. */
void FUN_000b7f90(int16_t local_player_index, float dx, float dy)
{
  char *slot;
  float *desired_pitch;
  float *desired_yaw;
  void *game_tag_elem;
  char camera_info[0x10];
  int16_t seat_index;
  int unit_handle;
  void *camera_tag;
  float pitch_min;
  float pitch_max;
  float camera_yaw_offset;
  uint32_t bits;

  assert_halt(local_player_index >= 0 &&
              local_player_index < MAXIMUM_NUMBER_OF_LOCAL_PLAYERS);

  slot = (char *)player_control_globals + (int)local_player_index * 0x40 + 0x10;
  desired_yaw = (float *)(slot + 0xc);
  desired_pitch = (float *)(slot + 0x10);

  {
    void *globals = game_globals_get();
    game_tag_elem = tag_block_get_element((char *)globals + 0x110, 0, 0x80);
  }

  pitch_min = *(float *)0xbfbf0243;
  pitch_max = *(float *)0x3fbf0243;
  camera_yaw_offset = *(float *)0x2533c0;

  bits = *(uint32_t *)desired_pitch;
  if ((bits & 0x7f800000u) == 0x7f800000u ||
      *desired_pitch > *(float *)0x26e37c ||
      *desired_pitch < *(float *)0x26e378) {
    display_assert("valid_euler_angles2d(&player->desired_angles)",
                   "c:\\halo\\SOURCE\\game\\player_control.c", 0x494, 1);
    system_exit(NONE);
  }
  bits = *(uint32_t *)desired_yaw;
  if ((bits & 0x7f800000u) == 0x7f800000u ||
      *desired_yaw > *(float *)0x255a54 ||
      *desired_yaw < *(float *)0x2533c0) {
    display_assert("valid_euler_angles2d(&player->desired_angles)",
                   "c:\\halo\\SOURCE\\game\\player_control.c", 0x494, 1);
    system_exit(NONE);
  }

  player_control_get_unit_camera_info(local_player_index, camera_info);
  unit_handle = *(int *)camera_info;
  seat_index = *(int16_t *)(camera_info + 4);
  camera_tag = *(void **)(camera_info + 8);

  *desired_yaw += dx;

  if (seat_index != (int16_t)NONE) {
    void *unit_obj;
    void *unit_tag;
    void *seat_elem;
    float marker_angles[2];
    char marker_buf[0x6c];
    float min_yaw;
    float max_yaw;
    float yaw_range;
    float delta_to_max;
    float delta_from_min;

    unit_obj = object_get_and_verify_type(unit_handle, 3);
    unit_tag = tag_get(0x756e6974 /* 'unit' */, *(int *)unit_obj);
    seat_elem = tag_block_get_element((char *)unit_tag + 0x2e4, seat_index, 0x11c);

    if (*(float *)((char *)seat_elem + 0xf0) != *(float *)0x2533c0 ||
        *(float *)((char *)seat_elem + 0xf4) != *(float *)0x2533c0) {
      object_get_markers_by_string_id(unit_handle, (char *)seat_elem + 0x24,
                                      marker_buf, 1);
      vector_to_angles(marker_angles,
                       (float *)((char *)marker_buf + 0x3c));
      min_yaw = marker_angles[0] + *(float *)((char *)seat_elem + 0xf0);
      max_yaw = marker_angles[0] + *(float *)((char *)seat_elem + 0xf4);
      yaw_range = FUN_000b6dd0(min_yaw, max_yaw);
      delta_to_max = FUN_000b6dd0(*desired_yaw, max_yaw);
      delta_from_min = FUN_000b6dd0(min_yaw, *desired_yaw);

      if (yaw_range < *(float *)0x2533c0)
        yaw_range += *(float *)0x255a54;

      if (!((delta_to_max >= *(float *)0x2533c0 &&
             delta_to_max <= yaw_range) ||
            (delta_from_min >= *(float *)0x2533c0 &&
             delta_from_min <= yaw_range))) {
        if (fabsf(delta_from_min) < fabsf(delta_to_max))
          *desired_yaw = min_yaw;
        else
          *desired_yaw = max_yaw;
      }
    }
  }

  while (*desired_yaw < *(float *)0x2533c0)
    *desired_yaw += *(float *)0x255a54;
  while (*desired_yaw >= *(float *)0x255a54)
    *desired_yaw -= *(float *)0x255a54;

  if (camera_tag != NULL) {
    void *unit_obj;
    float tag_pitch_min;
    float tag_pitch_max;

    unit_obj = object_get_and_verify_type(unit_handle, 3);
    tag_get(0x756e6974 /* 'unit' */, *(int *)unit_obj);
    tag_pitch_min = *(float *)((char *)camera_tag + 0x44);
    tag_pitch_max = *(float *)((char *)camera_tag + 0x48);
    camera_yaw_offset = *(float *)((char *)camera_tag + 0x40);

    if (tag_pitch_max != *(float *)0x2533c0 ||
        tag_pitch_min != *(float *)0x2533c0) {
      pitch_min = tag_pitch_min;
      pitch_max = tag_pitch_max;

      if (seat_index != (int16_t)NONE &&
          *(float *)((char *)unit_obj + 0x38) > *(float *)0x2549d4) {
        float facing_vec[3];
        float angles[2];
        float adjust;

        angles[0] = *desired_yaw;
        angles[1] = *(float *)0x2533c0;
        angles_to_vector(facing_vec, angles);
        adjust = FUN_0010c510((float *)((char *)unit_obj + 0x30), facing_vec) -
                 *(float *)0x2568bc;
        pitch_min -= adjust;
        pitch_max -= adjust;
        camera_yaw_offset -= adjust;
      }

      if (pitch_min <= *(float *)0x26e378)
        pitch_min = *(float *)0xbfbf0243;
      else if (pitch_min <= *(float *)0x26e37c)
        pitch_min = *(float *)0x3fbf0243;

      if (pitch_max <= *(float *)0x26e378)
        pitch_max = *(float *)0xbfbf0243;
      else if (pitch_max <= *(float *)0x26e37c)
        pitch_max = *(float *)0x3fbf0243;
    }

    if (camera_yaw_offset != *(float *)0x2533c0 ||
        *(char *)(slot + 0x26) != 0) {
      float pitch_delta;
      float scaled;
      float max_delta;
      uint32_t pitch_bits;

      pitch_delta = *desired_pitch - camera_yaw_offset;
      scaled = (float)((double)fabsf(pitch_delta) * *(double *)0x26e3b0);
      pitch_bits = *(uint32_t *)desired_pitch;
      if ((pitch_bits & 0x7f800000u) == 0x7f800000u) {
        char *msg =
          csprintf((char *)0x5ab100, "%s: assert_valid_real(0x%08X %f)",
                   "player_control->desired_angles.pitch", pitch_bits,
                   (double)*desired_pitch);
        display_assert(msg, "c:\\halo\\SOURCE\\game\\player_control.c", 0x4f2,
                       1);
        system_exit(NONE);
      }

      if (camera_yaw_offset != *(float *)0x2533c0) {
        max_delta =
          sqrtf(*(float *)(slot + 0x18) * *(float *)(slot + 0x18) +
                *(float *)(slot + 0x1c) * *(float *)(slot + 0x1c) +
                *(float *)(slot + 0x20) * *(float *)(slot + 0x20)) *
          scaled * *(float *)0x26e388;
      } else {
        max_delta = *(float *)((char *)game_tag_elem + 0x54) * scaled;
      }

      interpolate_scalar(desired_pitch, camera_yaw_offset, max_delta);

      pitch_bits = *(uint32_t *)desired_pitch;
      if ((pitch_bits & 0x7f800000u) == 0x7f800000u) {
        char *msg =
          csprintf((char *)0x5ab100, "%s: assert_valid_real(0x%08X %f)",
                   "player_control->desired_angles.pitch", pitch_bits,
                   (double)*desired_pitch);
        display_assert(msg, "c:\\halo\\SOURCE\\game\\player_control.c", 0x4fd,
                       1);
        system_exit(NONE);
      }
    }
  }

  {
    float delta;

    delta = pitch_min - *(float *)(slot + 0x38);
    if (delta <= *(float *)0x26e384)
      *(float *)(slot + 0x38) += *(float *)0x26e384;
    else if (delta >= *(float *)0x26e380)
      *(float *)(slot + 0x38) += *(float *)0x26e380;
    else
      *(float *)(slot + 0x38) = pitch_min;

    delta = pitch_max - *(float *)(slot + 0x3c);
    if (delta <= *(float *)0x26e384)
      *(float *)(slot + 0x3c) += *(float *)0x26e384;
    else if (delta >= *(float *)0x26e380)
      *(float *)(slot + 0x3c) += *(float *)0x26e380;
    else
      *(float *)(slot + 0x3c) = pitch_max;
  }

  *desired_pitch += dy;
  if (*desired_pitch < *(float *)(slot + 0x38))
    *desired_pitch = *(float *)(slot + 0x38);
  else if (*desired_pitch > *(float *)(slot + 0x3c))
    *desired_pitch = *(float *)(slot + 0x3c);
}

int player_control_get_desired_weapon(int16_t local_player_index, int unit_handle)
{
  char *slot;
  int weapon_handle;

  assert_halt(local_player_index >= 0 &&
              local_player_index < MAXIMUM_NUMBER_OF_LOCAL_PLAYERS);
  slot = (char *)player_control_globals + (int)local_player_index * 0x40 + 0x10;
  if (*(int *)slot == unit_handle) {
    weapon_handle = unit_get_weapon(unit_handle, *(int16_t *)(slot + 0x20));
    if (weapon_handle != NONE)
      return weapon_handle;
  }
  return unit_get_weapon(
      unit_handle,
      *(int16_t *)((char *)object_get_and_verify_type(unit_handle, 3) + 0x2a2));
}

float *player_control_get_facing_angles(int16_t local_player_index)
{
  char *slot;
  uint32_t bits;

  assert_halt(local_player_index >= 0 &&
              local_player_index < MAXIMUM_NUMBER_OF_LOCAL_PLAYERS);
  slot = (char *)player_control_globals + (int)local_player_index * 0x40 + 0x10;
  bits = *(uint32_t *)(slot + 0x10);
  if ((bits & 0x7f800000) == 0x7f800000 ||
      *(float *)(slot + 0x10) > *(float *)0x26e37c ||
      *(float *)(slot + 0x10) < *(float *)0x26e378) {
    display_assert("valid_euler_angles2d(&player->desired_angles)",
                   "c:\\halo\\SOURCE\\game\\player_control.c", 0x3c0, 1);
    system_exit(NONE);
  }
  bits = *(uint32_t *)(slot + 0xc);
  if ((bits & 0x7f800000) == 0x7f800000 ||
      *(float *)(slot + 0xc) > *(float *)0x255a54 ||
      *(float *)(slot + 0xc) < *(float *)0x2533c0) {
    display_assert("valid_euler_angles2d(&player->desired_angles)",
                   "c:\\halo\\SOURCE\\game\\player_control.c", 0x3c0, 1);
    system_exit(NONE);
  }
  return (float *)(slot + 0xc);
}

float *player_control_get_facing_direction(int16_t local_player_index,
                                           float *out_direction)
{
  float *angles;
  int player_index;

  angles = player_control_get_facing_angles(local_player_index);
  player_index = local_player_get_player_index(local_player_index);
  player_build_action_update(player_index, out_direction, angles);
  return out_direction;
}

/* Map a local input blob (ESI) into player_control_globals action-test flags. */
void FUN_000b6bd0(char *input)
{
  int *g;
  int flags8;
  int input_flags;

  if (input[0x14] && cinematic_can_be_skipped())
    main_skip_cinematic();

  g = (int *)player_control_globals;
  input_flags = *(int *)(input + 0x18);
  if (input_flags & 0x40)
    g[0] |= 1;
  if (input_flags & 2)
    g[0] |= 2;
  if (input[0x14])
    g[0] |= 4;
  if (input[0x15])
    g[0] |= 8;
  if (*(float *)(input + 8) > *(float *)0x2533c0)
    g[0] |= 0x10;
  if (input_flags & 0x2000)
    g[0] |= 0x20;
  if (input[0x1c] & 4)
    g[0] |= 0x40;
  if (*(float *)(input + 0x10) > *(float *)0x2533c0)
    g[0] |= 0x80;
  else if (*(float *)(input + 0x10) < *(float *)0x2533c0)
    g[0] |= 0x100;
  if (*(float *)(input + 0xc) > *(float *)0x2533c0)
    g[0] |= 0x200;
  else if (*(float *)(input + 0xc) < *(float *)0x2533c0)
    g[0] |= 0x400;
  if (*(float *)input > *(float *)0x2533c0)
    g[0] |= 0x800;
  else if (*(float *)input < *(float *)0x2533c0)
    g[0] |= 0x1000;
  if (*(float *)(input + 4) > *(float *)0x2533c0)
    g[0] |= 0x2000;
  else if (*(float *)(input + 4) < *(float *)0x2533c0)
    g[0] |= 0x4000;

  /* Sticky bit0 on globals+8 / clear input 0x40. */
  if (g[1] & 1) {
    *(int *)(input + 0x18) &= ~0x40;
  } else if (g[2] & 1) {
    flags8 = g[2];
    if (*(int *)(input + 0x18) & 0x40)
      flags8 |= 1;
    else
      flags8 &= ~1;
    g[2] = flags8;
    *(int *)(input + 0x18) &= ~0x40;
  }

  if (!*(uint8_t *)0x2f0292) {
    if (g[1] & 4) {
      *(int *)(input + 0x18) &= ~0x40;
    } else if (g[2] & 4) {
      flags8 = g[2];
      if (*(int *)(input + 0x18) & 0x40)
        flags8 |= 4;
      else
        flags8 &= ~4;
      g[2] = flags8;
      *(int *)(input + 0x18) &= ~0x40;
    }
    if (g[1] & 8) {
      *(int *)(input + 0x1c) &= ~1;
      return;
    }
    if (!(g[2] & 8))
      return;
    flags8 = g[2];
    if (input[0x1c] & 1) {
      g[2] = flags8 | 8;
      *(int *)(input + 0x1c) &= ~1;
      return;
    }
    g[2] = flags8 & ~8;
    *(int *)(input + 0x1c) &= ~1;
    return;
  }

  /* Alternate sticky path when 0x2f0292 is set. */
  if (g[1] & 4) {
    *(int *)(input + 0x18) &= ~2;
  } else if (g[2] & 4) {
    flags8 = g[2];
    if (*(int *)(input + 0x18) & 2)
      flags8 |= 4;
    else
      flags8 &= ~4;
    g[2] = flags8;
    *(int *)(input + 0x18) &= ~2;
  }
  if (g[1] & 8) {
    *(int *)(input + 0x1c) &= ~2;
    return;
  }
  if (!(g[2] & 4))
    return;
  flags8 = g[2];
  if (input[0x1c] & 2) {
    g[2] = flags8 | 4;
    *(int *)(input + 0x1c) &= ~2;
    return;
  }
  g[2] = flags8 & ~4;
  *(int *)(input + 0x1c) &= ~2;
}

/* Forward input delta into FUN_000b7f90 (local player index in EAX). */
void FUN_000b8cf0(int a, float *delta)
{
  assert_halt(delta != NULL);
  FUN_000b7f90((int16_t)a, delta[0], delta[1]);
}

void FUN_000b8d30(int handle)
{
  int queue_index;

  queue_index = data_new_datum(*(data_t **)0x4570c8, handle);
  if (queue_index == NONE) {
    display_assert("queue_index!=NONE", "c:\\halo\\SOURCE\\game\\player_control.c",
                   0xeb, 1);
    system_exit(NONE);
  }
}

/* Set action flags on a local player's control slot.
 * ORs the given flags into the player's action_flags field, and
 * optionally into the persistent_action_flags field as well. */
void player_control_set_action_flags(int16_t local_player_index, uint16_t flags,
                                     bool persistent)
{
  uint16_t *slot;

  assert_halt(local_player_index >= 0 &&
              local_player_index < MAXIMUM_NUMBER_OF_LOCAL_PLAYERS);
  slot = (uint16_t *)((char *)player_control_globals +
                      local_player_index * 0x40 + 0x10);
  *(uint16_t *)((char *)slot + 8) |= flags;
  if (persistent)
    *(uint16_t *)((char *)slot + 0xa) |= flags;
}

/* Get the local player index for the player controlling a unit.
 * Looks up the unit's player handle (unit+0x1c8), then reads the local
 * player index (player+0x2) from the player datum. Returns NONE (0xffff)
 * if the unit has no controlling player. */
int16_t unit_get_local_player_index(int unit_handle)
{
  char *unit_obj;
  int player_handle;
  char *player;

  unit_obj = (char *)object_get_and_verify_type(unit_handle, 3);
  player_handle = *(int *)(unit_obj + 0x1c8);
  if (player_handle != NONE) {
    player = (char *)datum_get(player_data, player_handle);
    return *(int16_t *)(player + 0x2);
  }
  return (int16_t)NONE;
}

/* Clear the aim-assist weapon interaction slot for a unit's controlling player.
 * Looks up the player datum via the unit's player handle (unit+0x1c8), then
 * finds the local player index (player+0x2), retrieves the player control slot,
 * and resets the weapon interaction field (slot+0x24) to NONE. */
void player_clear_aim_assist(int unit_handle)
{
  char *unit_obj;
  int player_handle;
  char *player;
  int16_t local_player_index;
  char *slot;

  unit_obj = (char *)object_get_and_verify_type(unit_handle, 3);
  player_handle = *(int *)(unit_obj + 0x1c8);
  if (player_handle != NONE) {
    player = (char *)datum_get(player_data, player_handle);
    local_player_index = *(int16_t *)(player + 0x2);
    if (local_player_index != NONE) {
      slot = (char *)player_control_get_data((int16_t)local_player_index);
      *(int16_t *)(slot + 0x24) = NONE;
    }
  }
}

/* Set a player control slot's desired facing angles from a 3D direction vector.
 * Converts the direction vector to yaw+pitch via vector_to_angles (atan2-based
 * vector_to_angles), validates both angles for NaN/Inf, and normalizes yaw
 * to [0, 2*pi) by adding 2*pi if negative. */
void player_control_set_facing(uint16_t local_player_index, float *direction)
{
  char *player_slot;
  float *desired_yaw;

  assert_halt(local_player_index >= 0 &&
              local_player_index < MAXIMUM_NUMBER_OF_LOCAL_PLAYERS);

  player_slot = (char *)player_control_globals +
                (int)(int16_t)local_player_index * 0x40 + 0x10;
  desired_yaw = (float *)(player_slot + 0xc);

  /* Convert direction vector to yaw/pitch angles */
  vector_to_angles(desired_yaw, direction);

  /* assert_valid_real on desired_angles.pitch (slot+0x10) */
  if ((*(uint32_t *)(player_slot + 0x10) & 0x7f800000u) == 0x7f800000u) {
    char *msg = csprintf((char *)0x5ab100, "%s: assert_valid_real(0x%08X %f)",
                         "player_control->desired_angles.pitch",
                         *(uint32_t *)(player_slot + 0x10),
                         (double)*(float *)(player_slot + 0x10));
    display_assert(msg, "c:\\halo\\SOURCE\\game\\player_control.c", 0xbb, 1);
    system_exit(NONE);
  }

  /* assert_valid_real on desired_angles.yaw (slot+0xc) */
  if ((*(uint32_t *)desired_yaw & 0x7f800000u) == 0x7f800000u) {
    char *msg = csprintf((char *)0x5ab100, "%s: assert_valid_real(0x%08X %f)",
                         "player_control->desired_angles.yaw",
                         *(uint32_t *)desired_yaw, (double)*desired_yaw);
    display_assert(msg, "c:\\halo\\SOURCE\\game\\player_control.c", 0xbc, 1);
    system_exit(NONE);
  }

  /* Normalize yaw to [0, 2*pi) */
  if (*desired_yaw < *(float *)0x2533c0)
    *desired_yaw += *(float *)0x255a54;
}

void player_control_new_unit(uint16_t local_player_index, int player_index)
{
  int *slot;
  float *facing;
  int unit;

  assert_halt(local_player_index >= 0 &&
              local_player_index < MAXIMUM_NUMBER_OF_LOCAL_PLAYERS);
  slot =
    (int *)((char *)player_control_globals + local_player_index * 0x40 + 0x10);
  csmemset(slot, 0, 0x40);
  *slot = player_index;
  *(int16_t *)(slot + 8) = -1;
  *(int16_t *)((char *)slot + 0x22) = -1;
  *(int16_t *)(slot + 9) = -1;
  *(char *)((char *)slot + 0x26) = 0;
  slot[10] = -1;
  *(float *)(slot + 0xf) = 1.49f;
  *(float *)(slot + 0xe) = -1.49f;
  *(int16_t *)(slot + 2) = 0;
  *(int16_t *)((char *)slot + 10) = 0;
  if (player_index != -1) {
    unit = (int)object_get_and_verify_type(player_index, 3);
    facing = (float *)(slot + 3);
    vector_to_angles(facing, (float *)(unit + 0x1d4));
    if (*facing < *(float *)0x2533c0)
      *facing += *(float *)0x255a54;
    *(int16_t *)(slot + 8) = *(int16_t *)(unit + 0x2a4);
    *(int16_t *)((char *)slot + 0x22) = (int16_t) * (char *)(unit + 0x2cd);
    *(int16_t *)(slot + 9) = (int16_t) * (char *)(unit + 0x2d1);
  }
}

/* Set the desired weapon index on a unit's controlling player.
 * Resolves the unit's player handle (unit+0x1c8), looks up the local player
 * index (player+0x2), retrieves the player control slot, and writes
 * seat_index into the desired weapon field (slot+0x20). */
void player_control_set_unit_seat(int unit_handle, int seat_index)
{
  char *unit_obj;
  int player_handle;
  char *player;
  int16_t local_player_index;
  char *slot;

  unit_obj = (char *)object_get_and_verify_type(unit_handle, 3);
  player_handle = *(int *)(unit_obj + 0x1c8);
  if (player_handle != NONE) {
    player = (char *)datum_get(player_data, player_handle);
    local_player_index = *(int16_t *)(player + 0x2);
    if (local_player_index != NONE) {
      slot = (char *)player_control_get_data(local_player_index);
      *(int16_t *)(slot + 0x20) = (int16_t)seat_index;
    }
  }
}

void player_control_initialize_for_new_map(void)
{
  int i;
  int iVar;
  int scenario;

  *(int *)player_control_globals = 0;
  *((int *)player_control_globals + 1) = 0;
  *((int *)player_control_globals + 2) = 0;
  *((int *)player_control_globals + 3) = 0;
  for (i = 0; (int16_t)i < 4; i++) {
    scenario = ((int (*)(void))0x18e450)();
    iVar = (int)tag_block_get_element((void *)(scenario + 0x110), 0, 0x80);
    player_control_new_unit(i, -1);
    if (*(float *)((char *)0x4570a8 + i * 4) == *(float *)0x2533c0)
      *(int *)((char *)0x4570a8 + i * 4) = *(int *)(iVar + 0x4c);
    if (*(float *)((char *)0x457098 + i * 4) == *(float *)0x2533c0)
      *(int *)((char *)0x457098 + i * 4) = *(int *)(iVar + 0x50);
  }
}

/* Read controller/keyboard state into a 0x20-byte local input blob.
 * Original Xbox ABI passes out_blob in EBX with cdecl stack args for index
 * and delta_time. */
void get_local_player_input_blob(int16_t local_player_index, float delta_time,
                                 char *out_blob)
{
  int player_index;
  char *slot;
  char *player;
  int16_t gamepad_index;
  char is_primary_player;
  void *game_tag_elem;
  void *abstract_input;
  int unit_handle;
  char *unit_obj;
  float look_scale_x;
  float look_scale_y;
  float abs_look_x;
  float abs_look_y;
  float deadzone_scale;
  float look_x;
  float look_y;
  float move_x;
  float move_y;
  float aim_speed;
  float scratch_a;
  float scratch_b;
  float scratch_c;
  float scratch_d;
  uint32_t flags18;
  uint32_t flags1c;
  char action_bytes[0xc];
  int i;
  int bit;
  uint16_t blocked;
  uint16_t mask;
  int edx;

  player_index = local_player_get_player_index(local_player_index);
  csmemset(out_blob, 0, 0x20);
  if (player_index == NONE)
    goto validate_trigger;

  slot = (char *)player_control_get_data(local_player_index);
  player = (char *)datum_get(*(data_t **)0x5aa6d4, player_index);
  gamepad_index = *(int16_t *)(player + 0x2);
  is_primary_player = (char)(gamepad_index == *(int16_t *)0x457094);

  {
    void *globals = game_globals_get();
    game_tag_elem = tag_block_get_element((char *)globals + 0x110, 0, 0x80);
  }

  if (gamepad_index != (int16_t)NONE && input_has_gamepad(gamepad_index)) {
    (void)input_get_gamepad_state((int)gamepad_index);
    abstract_input = input_abstraction_get_input_state((int)gamepad_index);

    look_scale_x = 0.0f;
    look_scale_y = 0.0f;
    /* XBE: unit comes from player datum +0x34 (not control-slot +0x24). */
    unit_handle = *(int *)(player + 0x34);
    if (unit_handle != NONE) {
      unit_obj = (char *)object_get_and_verify_type(unit_handle, 3);
      look_scale_x =
        *(float *)((char *)0x457098 + (int)local_player_index * 4) *
        *(float *)0x253d4c * *(float *)0x2546a4;
      look_scale_y =
        *(float *)((char *)0x4570a8 + (int)local_player_index * 4) *
        *(float *)0x253d4c * *(float *)0x2546a4;
      if (*(int *)(unit_obj + 0xcc) != NONE &&
          *(int16_t *)(unit_obj + 0x2a0) != (int16_t)NONE) {
        void *parent_obj;
        void *unit_tag;
        void *seat_elem;
        parent_obj =
          (char *)object_get_and_verify_type(*(int *)(unit_obj + 0xcc), 3);
        unit_tag = tag_get(0x756e6974, *(int *)parent_obj);
        seat_elem = tag_block_get_element((char *)unit_tag + 0x2e4,
                                          *(int16_t *)(unit_obj + 0x2a0),
                                          0x11c);
        if (*(float *)((char *)seat_elem + 0x7c) != *(float *)0x2533c0)
          look_scale_x = *(float *)((char *)seat_elem + 0x7c) *
                         *(float *)0x253d4c * *(float *)0x2546a4;
        if (*(float *)((char *)seat_elem + 0x80) != *(float *)0x2533c0)
          look_scale_y = *(float *)((char *)seat_elem + 0x80) *
                         *(float *)0x253d4c * *(float *)0x2546a4;
      }
    }

    move_x = *(float *)((char *)abstract_input + 0xc);
    move_y = *(float *)((char *)abstract_input + 0x10);
    *(float *)out_blob = move_x;
    *(float *)(out_blob + 4) = move_y;

    abs_look_x = *(float *)((char *)abstract_input + 0x14);
    if (abs_look_x < 0.0f)
      abs_look_x = -abs_look_x;
    abs_look_y = *(float *)((char *)abstract_input + 0x18);
    if (abs_look_y < 0.0f)
      abs_look_y = -abs_look_y;

    deadzone_scale = *(float *)0x2533c8;
    if (abs_look_x <= *(float *)0x25496c && abs_look_y <= *(float *)0x25496c) {
      if (abs_look_y <= abs_look_x) {
        if (abs_look_x > *(float *)0x2533c0)
          abs_look_y = abs_look_y / abs_look_x;
        else
          abs_look_y = 1.0f;
      } else {
        if (abs_look_y > *(float *)0x2533c0)
          abs_look_x = abs_look_x / abs_look_y;
        abs_look_y = 1.0f;
      }
      deadzone_scale = sqrtf(abs_look_y * abs_look_y +
                             *(float *)0x2533c8 * *(float *)0x2533c8);
    }

    look_x = deadzone_scale * *(float *)((char *)abstract_input + 0x14);
    if (look_x <= *(float *)0x255e94)
      look_x = -1.0f;
    else if (look_x >= *(float *)0x2533c8)
      look_x = 1.0f;

    look_y = deadzone_scale * *(float *)((char *)abstract_input + 0x18);
    if (look_y <= *(float *)0x255e94)
      look_y = -1.0f;
    else if (look_y >= *(float *)0x2533c8)
      look_y = 1.0f;

    if ((*(uint8_t *)((char *)player_control_globals + 0xc) & 1) ||
        game_time_get_paused()) {
      look_x = 0.0f;
      look_y = 0.0f;
    } else {
      int southpaw_y;
      int southpaw_x;
      int16_t curve_count;
      float *curve_table;
      float y_curve_scale;
      float x_curve_scale;

      southpaw_y = (int)*(char *)0x4570ba + 1;
      if (*(char *)((char *)abstract_input + 0xb) && *(char *)0x4570b9)
        southpaw_y = (*(char *)0x4570ba == 0) + 1;
      y_curve_scale = (float)southpaw_y;

      southpaw_x = (int)*(char *)0x4570ba + 1;
      if (*(char *)((char *)abstract_input + 0xb) && *(char *)0x4570b9)
        southpaw_x = (*(char *)0x4570ba == 0) + 1;
      x_curve_scale = (float)southpaw_x;

      curve_count = *(int16_t *)((char *)game_tag_elem + 0x74);
      curve_table = *(float **)((char *)game_tag_elem + 0x78);
      if ((int)curve_count <= 1) {
        display_assert("player_control->look_curve_node_count>1",
                       "c:\\halo\\SOURCE\\game\\player_control.c", 0x1c8, 1);
        system_exit(NONE);
      }

      look_x = evaluate_piecewise_linear_function(curve_count, curve_table,
                                                 look_x);
      look_x *= y_curve_scale;
      look_x *= look_scale_x;

      look_y = evaluate_piecewise_linear_function(curve_count, curve_table,
                                                  look_y);
      look_y *= x_curve_scale;
      look_y *= look_scale_y;

      if (unit_handle != NONE) {
        int16_t zoom_weapon = *(int16_t *)(slot + 0x24);
        if (zoom_weapon != (int16_t)NONE) {
          float zoom = unit_get_zoom_magnification(unit_handle, zoom_weapon);
          look_x = look_x * (zoom / *(float *)0x2533c8);
          look_y = look_y * zoom;
        }
      }

      if (unit_handle != NONE) {
        void *player_settings;
        void *unit_obj2;
        player_settings =
          tag_block_get_element((void *)((char *)game_globals_get() + 0x170), 0,
                                0xf4);
        unit_obj2 = object_get_and_verify_type(unit_handle, 3);
        look_x = look_x * (*(float *)((char *)unit_obj2 + 0x3d4) *
                           *(float *)((char *)player_settings + 0x84) -
                           *(float *)0x2533c8);
        look_y = look_y * look_scale_y;
      }

      if (*(float *)((char *)abstract_input + 0x40) != *(float *)0x2533c0) {
        if (fabsf(look_x) <= (double)*(float *)((char *)abstract_input + 0x48)) {
          float v =
            *(float *)(slot + 0x34) / *(float *)((char *)abstract_input + 0x40);
          if (v <= *(float *)0x2533c0)
            v = *(float *)0x2533c0;
          else if (v >= *(float *)0x2533c8)
            v = *(float *)0x2533c8;
          look_x = (*(float *)((char *)abstract_input + 0x44) -
                    *(float *)0x2533c8) *
                     v +
                   *(float *)0x2533c8;
          look_x *= look_scale_x;
          *(float *)(slot + 0x34) += delta_time * *(float *)0x253394;
        } else {
          *(float *)(slot + 0x34) = 0.0f;
        }
      }

      scratch_c = look_x;
      scratch_d = look_y;
      *(int *)(slot + 0x28) =
        FUN_000a6470(local_player_index, (float *)(slot + 0x2c),
                      (float *)(slot + 0x30), &scratch_a, &scratch_b);

      if (*(char *)0x2f0291 && *(float *)(slot + 0x30) == *(float *)0x2533c0 &&
          fabsf(look_x) > *(double *)0x2533d0 &&
          fabsf(look_y) > *(double *)0x2533d0 &&
          fabsf(move_x) > *(double *)0x2533d0 &&
          fabsf(move_y) > *(double *)0x2533d0) {
        look_x = scratch_d * delta_time * *(float *)0x253394;
        look_y = scratch_c * delta_time * *(float *)0x253394;
        look_x = scratch_c * look_x;
        look_y = scratch_d * look_y;
      } else {
        aim_speed = game_time_get_speed();
        if (*(float *)abstract_input != *(float *)0x2533c0) {
          if (*(float *)abstract_input >= *(float *)0x2533c8)
            look_x = *(float *)0x2533c8;
          else
            look_x = *(float *)abstract_input;
        } else
          look_x = *(float *)0x2533c0;
        look_x = look_x * *(float *)(slot + 0x30) - *(float *)0x2533c8;

        if (*(float *)((char *)abstract_input + 4) != *(float *)0x2533c0) {
          if (*(float *)((char *)abstract_input + 4) >= *(float *)0x2533c8)
            move_y = *(float *)0x2533c8;
          else
            move_y = *(float *)((char *)abstract_input + 4);
        } else
          move_y = *(float *)0x2533c0;
        move_y *= *(float *)(slot + 0x30);

        if (game_players_are_double_speed())
          aim_speed *= *(float *)0x253398;

        scratch_a *= aim_speed;
        if (scratch_a <= *(float *)0x26e2f8)
          scratch_a = *(float *)0xbdd67750;
        else if (scratch_a >= *(float *)0x26e2f4)
          scratch_a = *(float *)0x3dd67750;

        if (aim_speed <= *(float *)0x26e2f0)
          aim_speed = *(float *)0x26e2f0;
        else if (aim_speed >= *(float *)0x26e2ec)
          aim_speed = *(float *)0x26e2ec;

        look_x = scratch_a * move_y + look_x * scratch_c;
        look_y = aim_speed * move_y + look_y * scratch_d;
      }

      *(float *)(out_blob + 0xc) = look_x;
      *(float *)(out_blob + 0x10) = look_y;
    }

    csmemset(action_bytes, 0, sizeof(action_bytes));
    blocked = *(uint16_t *)(slot + 8) & *(uint16_t *)(slot + 0xa);
    if (blocked) {
      for (edx = 1; edx <= 0xc; edx++) {
        mask = (uint16_t)(1 << (edx - 1));
        if ((blocked & mask) && !((char *)abstract_input)[edx - 1]) {
          blocked &= ~mask;
          *(uint16_t *)(slot + 8) = blocked;
          *(uint16_t *)(slot + 0xa) &= ~mask;
        }
      }
    }

    for (i = 0; i < 0xc; i += 6) {
      for (bit = 0; bit < 6; bit++) {
        mask = (uint16_t)(1 << (i + bit));
        if ((*(uint16_t *)(slot + 8) & mask) == 0)
          action_bytes[i + bit] = ((char *)abstract_input)[i + bit];
      }
    }

    flags18 = 0;
    flags1c = 0;

    unit_handle = *(int *)(player + 0x34);
    if (unit_handle != NONE &&
        object_try_and_get_and_verify_type(unit_handle, 1)) {
      char *checked = (char *)object_try_and_get_and_verify_type(unit_handle, 1);
      if (!*(char *)0x4570b8 && !(*(char *)(checked + 0x424) & 1)) {
        float mag_sq = move_y * move_y + move_x * move_x;
        if (!(mag_sq > *(float *)0x26e2e8))
          goto skip_fire_flag;
      }
      if (action_bytes[7])
        flags18 |= 1;
      else
        flags18 &= ~1u;
    }
  skip_fire_flag:;

    *(float *)(out_blob + 8) =
      (float)(int)(*(char *)((char *)abstract_input + 7)) *
      *(float *)0x26e1e4;

    if (action_bytes[7])
      flags18 |= 0x800;
    else
      flags18 &= ~0x800u;

    if (action_bytes[6]) {
      flags18 |= 0x2000;
      flags18 |= 0x1000;
    } else {
      flags18 &= ~0x2000u;
      flags18 &= ~0x1000u;
    }

    if (action_bytes[11] == 1)
      flags1c |= 4;
    else
      flags1c &= ~4u;

    if (action_bytes[2])
      flags18 |= 0x40;
    else
      flags18 &= ~0x40u;

    if ((int)(int16_t)action_bytes[2] >= *(int16_t *)((char *)game_tag_elem + 0x6c))
      flags18 |= 0x4000;
    else
      flags18 &= ~0x4000u;

    if (action_bytes[5])
      flags18 |= 0x10;
    else
      flags18 &= ~0x10u;

    if (action_bytes[0])
      flags18 |= 2;
    else
      flags18 &= ~2u;

    if (action_bytes[4])
      flags18 |= 0x80;
    else
      flags18 &= ~0x80u;

    if (action_bytes[3] == 1)
      flags1c |= 1;
    else
      flags1c &= ~1u;

    if (action_bytes[1] == 1)
      flags1c |= 2;
    else
      flags1c &= ~2u;

    *(int *)(out_blob + 0x18) = (int)flags18;
    *(int *)(out_blob + 0x1c) = (int)flags1c;
    if ((*(uint16_t *)(slot + 9) & 2) == 0) {
      void *gp = input_get_gamepad_state((int)gamepad_index);
      out_blob[0x15] = ((char *)gp)[0x11];
    }
    if ((*(uint16_t *)(slot + 8) & 4) == 0) {
      void *gp = input_get_gamepad_state((int)gamepad_index);
      out_blob[0x14] = ((char *)gp)[0x10];
    }
    goto normalize_move;

  } else {
    int kb_state;
    kb_state = FUN_000cf690();
    if (!kb_state || !is_primary_player)
      goto finalize_flags;

    kb_state = FUN_000cf690();
    *(float *)out_blob =
      (float)((int)input_key_is_down(0x2e) - (int)input_key_is_down(0x20));
    *(float *)(out_blob + 4) =
      (float)((int)input_key_is_down(0x2f) - (int)input_key_is_down(0x2d));

    if (!((*(uint8_t *)((char *)player_control_globals + 0xc) & 1)) &&
        !game_time_get_paused()) {
      *(float *)(out_blob + 0xc) =
        (float)(int)(*(float *)(slot + 0x2c) * *(float *)0x26e1dc * -1.0f);
      *(float *)(out_blob + 0x10) =
        (float)(int)(*(float *)(slot + 0x30) * *(float *)0x26e1e0 * -1.0f);
    } else {
      *(int *)(out_blob + 0xc) = 0;
      *(int *)(out_blob + 0x10) = 0;
    }

    flags18 = 0;
    flags1c = 0;
    if (input_key_is_down(0x69))
      flags18 |= 0x100;
    else
      flags18 &= ~0x100u;
    if (input_key_is_down(0x6c))
      flags18 |= 0x200;
    else
      flags18 &= ~0x200u;
    if (input_key_is_down(0x48))
      flags18 |= 1;
    else
      flags18 &= ~1u;
    if (input_key_is_down(0x1f))
      flags18 |= 2;
    else
      flags18 &= ~2u;
    if (input_key_is_down(0x3b))
      flags18 |= 0x40;
    else
      flags18 &= ~0x40u;
    if (input_key_is_down(0x22))
      flags18 |= 0x10;
    else
      flags18 &= ~0x10u;
    if (input_key_is_down(0x6a))
      flags18 |= 0x400;
    else
      flags18 &= ~0x400u;
    if (*(char *)(slot + 0xc))
      flags18 |= 0x800;
    else
      flags18 &= ~0x800u;
    if (*(char *)(slot + 0xe))
      flags18 |= 0x2000;
    else
      flags18 &= ~0x2000u;
    if (input_key_is_down(0x3a) == 1)
      flags1c |= 4;
    else
      flags1c &= ~4u;
    if (input_key_is_down(0x21) == 1)
      flags1c |= 1;
    else
      flags1c &= ~1u;

    *(int *)(out_blob + 0x18) = (int)flags18;
    *(int *)(out_blob + 0x1c) = (int)flags1c;
  }

finalize_flags:
  flags18 = *(uint32_t *)(out_blob + 0x18);
  flags1c = *(uint32_t *)(out_blob + 0x1c);

  if (flags18 & 0x800)
    *(float *)(out_blob + 8) = *(float *)0x2533c8;
  else
    *(float *)(out_blob + 8) = *(float *)0x2533c0;

  if (input_key_is_down(0x2b) == 1)
    flags1c |= 8;
  else
    flags1c &= ~8u;
  if (input_key_is_down(0x2a) == 1)
    flags1c |= 0x10;
  else
    flags1c &= ~0x10u;
  if (input_key_is_down(0x29) == 1)
    flags1c |= 0x20;
  else
    flags1c &= ~0x20u;
  if (input_key_is_down(0x11) == 1)
    flags18 |= 4;
  else
    flags18 &= ~4u;
  if (input_key_is_down(0x12) == 1)
    flags18 |= 8;
  else
    flags18 &= ~8u;

  *(int *)(out_blob + 0x18) = (int)flags18;
  *(int *)(out_blob + 0x1c) = (int)flags1c;

normalize_move:
  if (*(float *)(out_blob + 4) != 0.0f || *(float *)out_blob != 0.0f) {
    float mag_sq = *(float *)(out_blob + 4) * *(float *)(out_blob + 4) +
                   *(float *)out_blob * *(float *)out_blob;
    if (mag_sq <= *(float *)0x2533c8) {
      float scale = sqrtf(mag_sq) / *(float *)0x2533c8;
      *(float *)out_blob *= scale;
      *(float *)(out_blob + 4) *= scale;
    }
  }

validate_trigger:
  FUN_000b6bd0(out_blob);
  {
    uint32_t bits = *(uint32_t *)(out_blob + 8);
    if ((bits & 0x7f800000u) == 0x7f800000u) {
      char *msg =
        csprintf((char *)0x5ab100, "%s: assert_valid_real(0x%08X %f)",
                 "input->primary_trigger", bits,
                 (double)*(float *)(out_blob + 8));
      display_assert(msg, "c:\\halo\\SOURCE\\game\\player_control.c", 0x2b6,
                     1);
      system_exit(NONE);
    }
  }
}


/* Process input for a local player: read controller/keyboard state, handle
 * weapon switching and grenade throwing, detect autoaim idle, validate
 * facing angles, and submit the resulting action to the game engine.
 * Called once per local player per frame from player_control_update. */
void player_control_get_facing(int16_t local_player_index, float delta_time)
{
  char *player; /* player control struct (ESI) */
  void *game_tag_elem;
  char action[0x20]; /* input action struct, filled by get_input */
  int player_index;

  assert_halt(local_player_index >= 0 &&
              local_player_index < MAXIMUM_NUMBER_OF_LOCAL_PLAYERS);

  player =
    (char *)player_control_globals + (int)local_player_index * 0x40 + 0x10;

  /* get game globals tag element (input sensitivity thresholds etc.) */
  {
    void *globals = game_globals_get();
    game_tag_elem = tag_block_get_element((char *)globals + 0x110, 0, 0x80);
  }

  csmemset(action, 0xfa, 0x20);
  get_local_player_input_blob(local_player_index, delta_time, action);

  player_index = local_player_get_player_index(local_player_index);

  /* validate desired facing angles if player exists */
  if (player_index != NONE) {
    uint32_t bits;
    bits = *(uint32_t *)(player + 0x10);
    if ((bits & 0x7f800000) == 0x7f800000) {
      display_assert("player->desired_angles.pitch",
                     "c:\\halo\\SOURCE\\game\\player_control.c", 0x2ce, 1);
      system_exit(NONE);
    }
    bits = *(uint32_t *)(player + 0x0c);
    if ((bits & 0x7f800000) == 0x7f800000) {
      display_assert("player->desired_angles.yaw",
                     "c:\\halo\\SOURCE\\game\\player_control.c", 0x2cf, 1);
      system_exit(NONE);
    }
  }

  /* if director is controlling the camera, clear input */
  if (((bool (*)(int16_t))0x862c0)(local_player_index))
    csmemset(action, 0, 0x20);

  /* handle weapon/vehicle switching when playing locally */
  if (game_connection() == 0) {
    uint8_t flags = *(uint8_t *)(action + 0x1c);

    /* weapon switch (action bits 3-4) */
    if (flags & 0x18) {
      int new_weapon;
      if (flags & 0x10)
        new_weapon = ((int (*)(int))0x1aa080)(*(int *)player);
      else
        new_weapon = ((int (*)(int))0x1aa170)(*(int *)player);
      if (new_weapon != NONE)
        ((void (*)(int16_t, int))0xba5f0)(local_player_index, new_weapon);
    }

    /* grenade throw (action bit 5) */
    if (flags & 0x20) {
      if (*(int *)player == NONE)
        goto final_copy;
      ((void (*)(int))0x1aa240)(*(int *)player);
    }
  }

  /* unit-specific handling */
  if (*(int *)player != NONE) {
    char *unit_obj;
    int weapon_datum;

    unit_obj = (char *)object_get_and_verify_type(*(int *)player, 3);

    /* look up unit definition tag and current weapon */
    tag_get(0x756e6974, *(int *)unit_obj);
    weapon_datum = ((int (*)(int, uint16_t))0x1adeb0)(
      *(int *)player, *(uint16_t *)(unit_obj + 0x2a2));

    /* validate player weapon index */
    if (*(int16_t *)(player + 0x20) == NONE ||
        ((int (*)(int, int16_t))0x1adeb0)(
          *(int *)player, *(int16_t *)(player + 0x20)) == NONE) {
      *(int16_t *)(player + 0x20) = *(int16_t *)(unit_obj + 0x2a4);
    }

    /* weapon interaction (action bit 0) */
    if ((*(uint8_t *)(action + 0x1c) & 1) ||
        ((int (*)(int, int16_t))0x1adeb0)(
          *(int *)player, *(int16_t *)(player + 0x20)) == NONE ||
        *(int16_t *)(player + 0x20) == NONE) {
      int16_t new_wp = ((int16_t(*)(int, int16_t, int))0x1b1b40)(
        *(int *)player, *(int16_t *)(player + 0x20),
        *(uint8_t *)(action + 0x1c) & 1);
      *(int16_t *)(player + 0x20) = new_wp;
      *(int16_t *)(player + 0x24) = NONE;
    }

    /* check for forced weapon from AI/script */
    {
      int16_t forced = ((int16_t(*)(int))0x1ac350)(*(int *)player);
      if (forced != NONE && *(int16_t *)(player + 0x20) != forced) {
        *(int16_t *)(player + 0x20) = forced;
        *(int16_t *)(player + 0x24) = NONE;
      }
    }

    /* validate grenade type */
    if (*(int16_t *)(player + 0x22) == NONE ||
        ((int16_t(*)(int, int16_t))0x1aae70)(
          *(int *)player, *(int16_t *)(player + 0x22)) == 0) {
      *(int16_t *)(player + 0x22) = (int16_t) * (int8_t *)(unit_obj + 0x2cd);
    }

    /* grenade switch (action bit 1) */
    if ((*(uint8_t *)(action + 0x1c) & 2) ||
        ((int16_t(*)(int, int16_t))0x1aae70)(
          *(int *)player, *(int16_t *)(player + 0x22)) == 0 ||
        *(int16_t *)(player + 0x22) == NONE) {
      *(int16_t *)(player + 0x22) = ((int16_t(*)(int, int16_t, int))0x1a9980)(
        *(int *)player, *(int16_t *)(player + 0x22), 1);
    }

    /* melee/throw request (action bit 2) */
    if ((*(uint8_t *)(action + 0x1c) & 4) &&
        (*(uint8_t *)((char *)player_control_globals + 0xc) & 1) == 0 &&
        !game_time_get_paused() && weapon_datum != NONE &&
        !cinematic_in_progress()) {
      *(int16_t *)(player + 0x24) = ((int16_t(*)(int, int16_t))0xfc710)(
        weapon_datum, *(int16_t *)(player + 0x24));
    }

    /* apply turning/look input (unless scripted camera) */
    if (!((bool (*)(int16_t))0x86270)(local_player_index)) {
      FUN_000b7f90(local_player_index, *(float *)(action + 0x0c),
                   *(float *)(action + 0x10));
    }

    /* autoaim idle detection: if the player is looking at an enemy
     * (crosshair showing), actively turning (yaw above threshold),
     * and NOT firing, increment the idle counter. When the counter
     * exceeds a tag-defined threshold, enable autoaim assist. */
    if (*(int *)(unit_obj + 0xcc) == NONE) {
      float abs_facing;
      if (!((bool (*)(int16_t))0xe0b50)(local_player_index))
        goto reset_autoaim;
      /* FABS + FCOMP double: check if facing yaw exceeds threshold */
      abs_facing = *(float *)(player + 0x14);
      if (abs_facing < 0.0f)
        abs_facing = -abs_facing;
      if (!(abs_facing > *(double *)0x25fea8))
        goto reset_autoaim;
      /* check trigger and throttle below firing threshold */
      if (*(float *)(action + 0x10) >= *(float *)0x253f44)
        goto reset_autoaim;
      if (*(float *)(player + 0x30) >= *(float *)0x253f44)
        goto reset_autoaim;
      /* all conditions met — increment idle counter */
      {
        int count = (int)*(int8_t *)(player + 0x27) + 1;
        if (count < 0)
          count = 0;
        else if (count > 0x7f)
          count = 0x7f;
        *(int8_t *)(player + 0x27) = (int8_t)count;
        *(uint8_t *)(player + 0x26) =
          (int16_t)(int8_t)count > *(int16_t *)((char *)game_tag_elem + 0x6e);
      }
      goto final_copy;
    reset_autoaim:
      *(uint8_t *)(player + 0x27) = 0;
    }
    *(uint8_t *)(player + 0x26) = 0;
  }

final_copy:
  /* copy action results to player control struct */
  *(int *)(player + 0x04) = *(int *)(action + 0x18);
  *(int *)(player + 0x14) = *(int *)(action + 0x00);
  *(int *)(player + 0x18) = *(int *)(action + 0x04);
  *(int *)(player + 0x1c) = *(int *)(action + 0x08);

  /* validate primary_trigger */
  {
    uint32_t bits = *(uint32_t *)(player + 0x1c);
    if ((bits & 0x7f800000) == 0x7f800000) {
      display_assert("player->primary_trigger",
                     "c:\\halo\\SOURCE\\game\\player_control.c", 0x351, 1);
      system_exit(NONE);
    }
  }

  /* submit action to the game engine */
  player_index = local_player_get_player_index(local_player_index);
  if (player_index != NONE) {
    uint32_t bits;
    /* validate final desired angles and trigger */
    bits = *(uint32_t *)(player + 0x10);
    if ((bits & 0x7f800000) == 0x7f800000) {
      display_assert("player->desired_angles.pitch",
                     "c:\\halo\\SOURCE\\game\\player_control.c", 0x35d, 1);
      system_exit(NONE);
    }
    bits = *(uint32_t *)(player + 0x0c);
    if ((bits & 0x7f800000) == 0x7f800000) {
      display_assert("player->desired_angles.yaw",
                     "c:\\halo\\SOURCE\\game\\player_control.c", 0x35e, 1);
      system_exit(NONE);
    }
    bits = *(uint32_t *)(player + 0x1c);
    if ((bits & 0x7f800000) == 0x7f800000) {
      display_assert("player->primary_trigger",
                     "c:\\halo\\SOURCE\\game\\player_control.c", 0x35f, 1);
      system_exit(NONE);
    }

    /* build and submit player action struct */
    {
      char player_action[0x20];
      *(int *)(player_action + 0x00) = *(int *)(player + 0x04);
      *(int *)(player_action + 0x04) = *(int *)(player + 0x0c);
      *(int *)(player_action + 0x08) = *(int *)(player + 0x10);
      *(int16_t *)(player_action + 0x18) = *(int16_t *)(player + 0x20);
      *(int16_t *)(player_action + 0x1a) = *(int16_t *)(player + 0x22);
      *(int *)(player_action + 0x0c) = *(int *)(player + 0x14);
      *(int16_t *)(player_action + 0x1c) = *(int16_t *)(player + 0x24);
      *(int *)(player_action + 0x14) = *(int *)(player + 0x1c);
      *(int *)(player_action + 0x10) = *(int *)(player + 0x18);

      /* validate action facing angles */
      bits = *(uint32_t *)(player_action + 0x08);
      if ((bits & 0x7f800000) == 0x7f800000) {
        display_assert("action.desired_facing.pitch",
                       "c:\\halo\\SOURCE\\game\\player_control.c", 0x369, 1);
        system_exit(NONE);
      }
      bits = *(uint32_t *)(player_action + 0x04);
      if ((bits & 0x7f800000) == 0x7f800000) {
        display_assert("action.desired_facing.yaw",
                       "c:\\halo\\SOURCE\\game\\player_control.c", 0x36a, 1);
        system_exit(NONE);
      }

      ((void (*)(void *))0xb8f40)(player_action);
    }
  }
}

void player_control_update(float delta_time)
{
  int16_t i;

  if (profile_global_enable && *(char *)0x2f02a0)
    profile_enter_private((void *)0x2f0298);
  collision_log_begin_period(2);
  ((void (*)(void))0xb8f70)();
  for (i = 0; i < 4; i++)
    player_control_get_facing(i, delta_time);
  collision_log_end_period();
  if (profile_global_enable && *(char *)0x2f02a0)
    profile_exit_private((void *)0x2f0298);
}
