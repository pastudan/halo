#include <stdint.h>
/* Return a pointer to the player control data slot for a local player.
 * Each slot is 0x40 bytes, starting at offset 0x10 in the globals struct. */
void *player_control_get_data(int16_t local_player_index)
{
  assert_halt(local_player_index >= 0 &&
              local_player_index < MAXIMUM_NUMBER_OF_LOCAL_PLAYERS);
  return (char *)player_control_globals + local_player_index * 0x40 + 0x10;
}

/* player_control_initialize (0xb63d0) — readable C lift. */
void player_control_initialize(void)
{
  *(void **)0x457090 = game_state_malloc((const char *)0x26e210, 0, 0x110);
}

void player_control_dispose(void)
{
}

/* scripted_player_control_set_camera_control (0xb6430) — readable C lift. */
void scripted_player_control_set_camera_control(char enable)
{
  unsigned int *flags = (unsigned int *)(*(char **)0x457090 + 0xc);
  if (enable) {
    *flags &= ~1u;
  } else {
    *flags |= 1u;
  }
}

/* player_control_get_autoaim_level (0xb6940) — readable C lift. */
float player_control_get_autoaim_level(int16_t local_player_index)
{
  if (local_player_index < 0 || local_player_index >= 4) {
    display_assert((const char *)0x266fc0, (const char *)0x26e1e8, 0xb1, 1);
    system_exit(-1);
  }
  return *(float *)(*(unsigned char **)0x457090 + ((int)local_player_index * 0x40) + 0x3c);
}
/* players_unzoom_all (0xb69d0) — readable C lift. */
void players_unzoom_all(void)
{
  short i;
  for (i = 0; i < 4; i++) {
    if (i < 0 || i >= 4) {
      display_assert((const char *)0x266fc0, (const char *)0x26e1e8, 0xb1, 1);
      system_exit(-1);
    }
    *(short *)(*(unsigned char **)0x457090 + (i * 0x40) + 0x34) = (short)0xffff;
  }
}
/* player_control_get_zoom_level (0xb6a70) — readable C lift. */
short player_control_get_zoom_level(short local_player_index)
{
  if ((short)local_player_index == (short)-1)
    return -1;
  return *(short *)((char *)player_control_get_data(local_player_index) + 0x24);
}

void player_control_action_test_reset(void) {
  uint32_t *base = *(uint32_t **)0x457090;
  base[0] = 0;
  base[1] = 0;
}


/* player_control_action_test_accept (0xb6ab0) — readable C lift from XBE leaf. */
char player_control_action_test_accept(void)
{
  unsigned int *base = *(unsigned int **)0x457090;
  base[1] |= 0x4;
  base[2] |= 0x4;
  return (char)((base[0] >> 2) & 1);
}

/* player_control_action_test_back (0xb6ad0) — readable C lift from XBE leaf. */
char player_control_action_test_back(void)
{
  unsigned int *base = *(unsigned int **)0x457090;
  base[1] |= 0x8;
  base[2] |= 0x8;
  return (char)((base[0] >> 3) & 1);
}

/* player_control_action_test_action (0xb6af0) — readable C lift from XBE leaf. */
char player_control_action_test_action(void)
{
  unsigned int *base = *(unsigned int **)0x457090;
  base[1] |= 0x1;
  base[2] |= 0x1;
  return (char)(base[0] & 1);
}

/* player_control_action_test_look_relative_up (0xb6bb0) — readable C lift from XBE leaf. */
char player_control_action_test_look_relative_up(void)
{
  unsigned int *base = *(unsigned int **)0x457090;
  return (char)((base[0] >> 7) & 1);
}

/* player_control_action_test_look_relative_down (0xb6bc0) — readable C lift from XBE leaf. */
char player_control_action_test_look_relative_down(void)
{
  unsigned int *base = *(unsigned int **)0x457090;
  return (char)((base[0] >> 8) & 1);
}




/* FUN_000b6dd0 (0xb6dd0) — readable C lift: wrap angle delta into (-pi, pi]. */
float FUN_000b6dd0(float a, float b)
{
  float d = b - a;
  /* DAT_00256980=pi, DAT_00255a54=2pi, DAT_0026e280=-pi */
  if (!(d < *(float *)0x256980) && d == d)
    d -= *(float *)0x255a54;
  if (!(d > *(float *)0x26e280) && d == d)
    d += *(float *)0x255a54;
  return d;
}

/* limit2d (0xb6e10) — readable C lift: exact x87 clamp sequence. */
__attribute__((noinline))
char limit2d(float *vec, float max_len)
{
  char ret;
  __asm__ volatile(
      "movl 8(%%ebp), %%ecx\n\t"
      "flds 4(%%ecx)\n\t"
      "flds (%%ecx)\n\t"
      "fld %%st(0)\n\t"
      "fmul %%st(1), %%st\n\t"
      "fld %%st(2)\n\t"
      "fmul %%st(3), %%st\n\t"
      "faddp %%st, %%st(1)\n\t"
      "fstp %%st(2)\n\t"
      "fstp %%st(0)\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fmuls 0xc(%%ebp)\n\t"
      "fld %%st(1)\n\t"
      "fcompp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne 1f\n\t"
      "fsqrt\n\t"
      "movb $1, %%al\n\t"
      "fdivrs 0xc(%%ebp)\n\t"
      "fld %%st(0)\n\t"
      "fmuls (%%ecx)\n\t"
      "fstps (%%ecx)\n\t"
      "fmuls 4(%%ecx)\n\t"
      "fstps 4(%%ecx)\n\t"
      "jmp 2f\n\t"
      "1:\n\t"
      "fstp %%st(0)\n\t"
      "xorb %%al, %%al\n\t"
      "2:\n\t"
      : "=a"(ret)
      :
      : "ecx", "cc", "memory");
  return ret;
}




/* interpolate_scalar (0xb6e60) — readable C lift from XBE leaf. */
void interpolate_scalar(float *value, float target, float max_delta)
{
  float delta;
  delta = target - *value;
  if (delta < -max_delta) {
    *value = *value - max_delta;
  } else if (delta > max_delta) {
    *value = *value + max_delta;
  } else {
    *value = target;
  }
}

/* evaluate_piecewise_linear_function (0xb64c0) — readable C lift. */
float evaluate_piecewise_linear_function(int16_t count, float *table, float t)
{
  char positive;
  int last;
  float x;
  float hi;
  int i0;
  int i1;
  float y;

  if (t != t)
    return t;
  positive = (t >= 0.0f) ? 1 : 0;
  last = (int)count - 1;
  x = __builtin_fabsf(t) * (float)last;
  if (!(x >= *(double *)0x2602c0)) {
    x = (float)(*(double *)0x2602c0);
  } else {
    hi = (float)count - 1.0f;
    if (x > hi)
      x = hi;
  }
  i0 = (int)x;
  if (i0 < 0)
    i0 = 0;
  else if (i0 > last)
    i0 = last;
  i1 = i0 + 1;
  if (i1 > last)
    i1 = last;
  if (table == NULL || i0 < 0 || i0 > i1 || i1 >= (int)count) {
    display_assert((const char *)0x26e228, (const char *)0x26e1e8, 0x14b, 1);
    system_exit(-1);
  }
  y = (table[i1] - table[i0]) * (x - (float)i0) + table[i0];
  if (positive)
    return y;
  return -y;
}

/* player_control_get_unit_index (0xb6870) — readable C lift. */
int player_control_get_unit_index(int16_t local_player_index)
{
  if ((int16_t)local_player_index < 0 || (int16_t)local_player_index >= 4) {
    display_assert((const char *)0x266fc0, (const char *)0x26e1e8, 0xb1, 1);
    system_exit(-1);
  }
  void *base = *(void **)0x457090;
  return *(int *)((char *)base + ((int)(int16_t)local_player_index << 6) + 0x10);
}

/* player_control_get_aiming_unit_index (0xb65c0) — readable C lift. */
int player_control_get_aiming_unit_index(int16_t local_player_index)
{
  unsigned char *base; int *slot;
  if (local_player_index < 0 || local_player_index >= 4) {
    display_assert((const char *)0x266fc0, (const char *)0x26e1e8, 0xb1, 1);
    system_exit(-1);
  }
  base = *(unsigned char **)0x457090;
  slot = (int *)(base + ((int)local_player_index * 0x40) + 0x10);
  return unit_get_aiming_unit_index(*slot);
}
/* player_control_get_target_object_index (0xb6620) — readable C lift. */
int player_control_get_target_object_index(int16_t local_player_index)
{
  unsigned char *base;
  unsigned char *slot;
  void *obj;

  if (local_player_index < 0 || local_player_index >= 4) {
    display_assert((const char *)0x266fc0, (const char *)0x26e1e8, 0xb1, 1);
    system_exit(-1);
  }
  base = *(unsigned char **)0x457090;
  slot = base + ((int)local_player_index * 0x40) + 0x10;
  obj = object_try_and_get_and_verify_type(*(int *)(slot + 0x28), -1);
  if (obj != (void *)0)
    return *(int *)(slot + 0x28);
  return -1;
}

/* player_control_get_field_of_view (0xb6690) — readable C lift. */
float player_control_get_field_of_view(int16_t local_player_index)
{
  unsigned char *slot;
  int unit_handle;
  char *unit;
  char *unit_tag;
  int weapon_handle;
  float base_fov;

  if (local_player_index < 0 || local_player_index >= 4) {
    display_assert((const char *)0x266fc0, (const char *)0x26e1e8, 0xb1, true);
    system_exit(-1);
  }
  slot = *(unsigned char **)0x457090 + (((int)local_player_index) << 6) + 0x10;
  unit_handle = *(int *)slot;
  if (unit_handle == -1)
    return *(float *)0x26e270;
  unit = (char *)object_get_and_verify_type(unit_handle, 3);
  unit_tag = (char *)tag_get(0x756e6974, *(int *)unit);
  weapon_handle = unit_get_weapon(unit_handle, *(int16_t *)(unit + 0x2a2));
  base_fov = *(float *)(unit_tag + 0x1a0);
  if (weapon_handle == -1)
    return base_fov;
  return weapon_get_field_of_view(weapon_handle, base_fov, *(int16_t *)(slot + 0x24));
}

/* player_control_get_unit_camera_info (0xb6740) — XBE naked draft (batch 130). */
#if defined(__clang__)
static void (*const bb6740_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const bb6740_exitfn)(int) = system_exit;
static void *(*const bb6740_get)(int, int) = object_get_and_verify_type;
static void (*const bb6740_useat)(int, float *) = unit_set_seat_state;
static void *(*const bb6740_tryget)(int, int) = object_try_and_get_and_verify_type;
static void *(*const bb6740_tag)(int, int) = tag_get;
static void *(*const bb6740_elem)(void *, int, int) = tag_block_get_element;

__attribute__((naked, noinline))
void player_control_get_unit_camera_info(int16_t local_player_index __attribute__((unused)), void *out_info __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%esi\n\t"
      "movl 0xc(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "pushl %%edi\n\t"
      "jne .Lplayer_control_get_unit_camera_info_1\n\t"
      "pushl $1\n\t"
      "pushl $0x402\n\t"
      "pushl $0x26e1e8\n\t"
      "pushl $0x26e274\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lplayer_control_get_unit_camera_info_1:\n\t"
      "movw 0x8(%%ebp), %%di\n\t"
      "testw %%di, %%di\n\t"
      "movl $0, 0x8(%%esi)\n\t"
      "jl .Lplayer_control_get_unit_camera_info_2\n\t"
      "cmpw $4, %%di\n\t"
      "jl .Lplayer_control_get_unit_camera_info_3\n\t"
      ".Lplayer_control_get_unit_camera_info_2:\n\t"
      "pushl $1\n\t"
      "pushl $0xb1\n\t"
      "pushl $0x26e1e8\n\t"
      "pushl $0x266fc0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lplayer_control_get_unit_camera_info_3:\n\t"
      "movl 0x457090, %%ecx\n\t"
      "movswl %%di, %%eax\n\t"
      "shll $6, %%eax\n\t"
      "movl 0x10(%%eax,%%ecx,1), %%edx\n\t"
      "movl %%edx, %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "movl %%edx, (%%esi)\n\t"
      "movw $0xffff, 0x4(%%esi)\n\t"
      "je .Lplayer_control_get_unit_camera_info_5\n\t"
      "pushl $3\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl (%%esi), %%ecx\n\t"
      "movl %%eax, %%edi\n\t"
      "leal 0xc(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[useat]\n\t"
      "movl 0xcc(%%edi), %%eax\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lplayer_control_get_unit_camera_info_4\n\t"
      "pushl $2\n\t"
      "pushl %%eax\n\t"
      "call *%[tryget]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lplayer_control_get_unit_camera_info_4\n\t"
      "movl (%%eax), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x76656869\n\t"
      "call *%[tag]\n\t"
      "movswl 0x2a0(%%edi), %%ecx\n\t"
      "pushl $0x11c\n\t"
      "pushl %%ecx\n\t"
      "addl $0x2e4, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl 0xcc(%%edi), %%edx\n\t"
      "addl $0x84, %%eax\n\t"
      "movl %%edx, (%%esi)\n\t"
      "movl %%eax, 0x8(%%esi)\n\t"
      "movw 0x2a0(%%edi), %%ax\n\t"
      "movl %%edx, %%ecx\n\t"
      "pushl $3\n\t"
      "pushl %%ecx\n\t"
      "movw %%ax, 0x4(%%esi)\n\t"
      "call *%[get]\n\t"
      "addl $0x1c, %%esp\n\t"
      "movl %%eax, %%edi\n\t"
      ".Lplayer_control_get_unit_camera_info_4:\n\t"
      "cmpw $-1, 0x4(%%esi)\n\t"
      "jne .Lplayer_control_get_unit_camera_info_5\n\t"
      "movl (%%edi), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x756e6974\n\t"
      "call *%[tag]\n\t"
      "addl $8, %%esp\n\t"
      "addl $0x1a8, %%eax\n\t"
      "movl %%eax, 0x8(%%esi)\n\t"
      ".Lplayer_control_get_unit_camera_info_5:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(bb6740_assert), [exitfn] "m"(bb6740_exitfn), [get] "m"(bb6740_get), [useat] "m"(bb6740_useat), [tryget] "m"(bb6740_tryget), [tag] "m"(bb6740_tag), [elem] "m"(bb6740_elem)
      : "memory");
}
#else
#error "player_control_get_unit_camera_info: clang naked draft required"
#endif


/* Apply this frame's look input to a local player's desired aiming angles.
 * yaw_delta/pitch_delta are the raw turn/look deltas (action+0x0c,
 * action+0x10).
 *
 * Yaw advances first, then is constrained to the arc the occupied seat allows:
 * the arc is centred on a marker direction on the unit (the seat definition at
 * +0x24 names the marker) and spans [seat+0xf0, seat+0xf4] about it. A yaw
 * landing outside the arc snaps to whichever end is nearer; the result is then
 * wrapped into [0, 2*pi].
 *
 * The pitch limits are not constants: pc->pitch_minimum/pitch_maximum ease
 * toward targets read from the camera-info limit block at a bounded +-pi/256
 * per call, and those targets are themselves clamped to +-85.5 degrees. Pitch
 * advances last and is clamped to the just-updated limits.
 *
 * c:\halo\SOURCE\game\player_control.c */
void FUN_000b7f90(int16_t local_player_index,
                                          float yaw_delta, float pitch_delta)
{
  player_control_t *pc;
  float *desired_pitch;
  void *globals_tag;
  char camera_info[0xc]; /* {unit handle, seat index, limit block ptr} */
  char marker_buf[0x6c]; /* object_get_markers_by_string_id output */
  float marker_angles[2]; /* yaw, pitch */
  float forward[3];
  float pitch_minimum_target;
  float pitch_maximum_target;
  float pitch_target;
  float delta;
  char *unit_obj;
  char *limits;

  assert_halt_at("c:\\halo\\SOURCE\\game\\player_control.c", 0xb1,
                 local_player_index >= 0 &&
                   local_player_index < MAXIMUM_NUMBER_OF_LOCAL_PLAYERS);

  pc = (player_control_t *)((char *)player_control_globals +
                            (int)local_player_index * 0x40 + 0x10);
  globals_tag =
    tag_block_get_element((char *)game_globals_get() + 0x110, 0, 0x80);

  desired_pitch = &pc->desired_angles_pitch;
  pitch_minimum_target = -1.4922565f; /* -85.5 degrees */
  pitch_maximum_target = 1.4922565f; /* +85.5 degrees */

  /* valid_euler_angles2d(&player->desired_angles): pitch within +-85.5
   * degrees, yaw within [0, 2*pi], neither infinite nor NaN. */
  if ((*(uint32_t *)&pc->desired_angles_pitch & 0x7f800000) == 0x7f800000 ||
      pc->desired_angles_pitch > 1.4922565f ||
      pc->desired_angles_pitch < -1.4922565f ||
      (*(uint32_t *)&pc->desired_angles_yaw & 0x7f800000) == 0x7f800000 ||
      pc->desired_angles_yaw > 6.2831855f || pc->desired_angles_yaw < 0.0f) {
    display_assert("valid_euler_angles2d(&player->desired_angles)",
                   "c:\\halo\\SOURCE\\game\\player_control.c", 0x494, 1);
    system_exit(NONE);
  }

  player_control_get_unit_camera_info(local_player_index, camera_info);
  pc->desired_angles_yaw = yaw_delta + pc->desired_angles_yaw;

  /* constrain yaw to the arc this seat permits */
  if (*(int16_t *)(camera_info + 4) != NONE) {
    char *seat;

    /* one nested expression: the original cleans all three calls with a
     * single ADD ESP,0x1c */
    seat = (char *)tag_block_get_element(
      (char *)tag_get(
        0x756e6974 /* 'unit' */,
        *(int *)object_get_and_verify_type(*(int *)camera_info, 3)) +
        0x2e4,
      *(int16_t *)(camera_info + 4), 0x11c);

    if (*(float *)(seat + 0xf0) != 0.0f || *(float *)(seat + 0xf4) != 0.0f) {
      float yaw_low;
      float yaw_high;
      float arc;
      float delta_high;

      object_get_markers_by_string_id(*(int *)camera_info, seat + 0x24,
                                      marker_buf, 1);
      /* the marker's forward vector sits at +0x3c in the marker record */
      vector_to_angles(marker_angles, (float *)(marker_buf + 0x3c));

      yaw_low = marker_angles[0] + *(float *)(seat + 0xf0);
      yaw_high = marker_angles[0] + *(float *)(seat + 0xf4);

      arc = yaw_high - yaw_low;
      if (arc >= 3.1415927f)
        arc -= 6.2831855f;
      if (arc <= -3.1415927f)
        arc += 6.2831855f;

      delta_high = yaw_high - pc->desired_angles_yaw;
      if (delta_high >= 3.1415927f)
        delta_high -= 6.2831855f;
      if (delta_high <= -3.1415927f)
        delta_high += 6.2831855f;

      delta = pc->desired_angles_yaw - yaw_low;
      if (delta >= 3.1415927f)
        delta -= 6.2831855f;
      if (delta <= -3.1415927f)
        delta += 6.2831855f;

      if (arc < 0.0f)
        arc += 6.2831855f;

      /* outside the arc: snap to the nearer end */
      if (!((delta_high >= 0.0f && delta_high < arc) ||
            (delta >= 0.0f && delta < arc))) {
        if (fabs(delta_high) > fabs(delta))
          pc->desired_angles_yaw = yaw_low;
        else
          pc->desired_angles_yaw = yaw_high;
      }
    }
  }

  while (pc->desired_angles_yaw < 0.0f)
    pc->desired_angles_yaw += 6.2831855f;
  while (pc->desired_angles_yaw > 6.2831855f)
    pc->desired_angles_yaw -= 6.2831855f;

  /* ease the pitch limits toward the camera's targets */
  limits = *(char **)(camera_info + 8);
  if (limits != NULL) {
    unit_obj = (char *)object_get_and_verify_type(*(int *)camera_info, 3);
    pitch_target = *(float *)(limits + 0x40);

    if (*(float *)(limits + 0x48) != 0.0f ||
        *(float *)(limits + 0x44) != 0.0f) {
      pitch_minimum_target = *(float *)(limits + 0x44);
      pitch_maximum_target = *(float *)(limits + 0x48);

      /* shift the targets by how far the player has turned off the unit's
       * own facing, so the limits track the body rather than the world */
      if (*(int16_t *)(camera_info + 4) != NONE &&
          *(float *)(unit_obj + 0x38) > 0.0f) {
        float offset;

        marker_angles[0] = pc->desired_angles_yaw;
        marker_angles[1] = 0.0f;
        angles_to_vector(forward, marker_angles);
        offset = 0.2f - FUN_0010c510(forward, (float *)(unit_obj + 0x30));
        pitch_minimum_target -= offset;
        pitch_maximum_target -= offset;
        pitch_target -= offset;
      }

      if (pitch_minimum_target < -1.4922565f)
        pitch_minimum_target = -1.4922565f;
      else if (pitch_minimum_target > 1.4922565f)
        pitch_minimum_target = 1.4922565f;

      if (pitch_maximum_target < -1.4922565f)
        pitch_maximum_target = -1.4922565f;
      else if (pitch_maximum_target > 1.4922565f)
        pitch_maximum_target = 1.4922565f;
    }

    if (pitch_target != 0.0f || pc->field_0x26 != 0) {
      float scaled;
      float magnitude;

      scaled =
        (float)(fabs(*desired_pitch - pitch_target) * 0.6366197466850281);
      if ((*(uint32_t *)desired_pitch & 0x7f800000) == 0x7f800000) {
        display_assert(
          csprintf((char *)0x5ab100, "%s: assert_valid_real(0x%08X %f)",
                   "player->desired_angles.pitch", *(uint32_t *)desired_pitch,
                   (double)*desired_pitch),
          "c:\\halo\\SOURCE\\game\\player_control.c", 0x4f2, 1);
        system_exit(NONE);
      }

      magnitude =
        sqrtf(*(float *)(unit_obj + 0x18) * *(float *)(unit_obj + 0x18) +
              *(float *)(unit_obj + 0x1c) * *(float *)(unit_obj + 0x1c) +
              *(float *)(unit_obj + 0x20) * *(float *)(unit_obj + 0x20));

      if (pitch_target != 0.0f)
        interpolate_scalar(desired_pitch, pitch_target,
                           magnitude * scaled * 0.08f);
      else
        interpolate_scalar(desired_pitch, pitch_target,
                           magnitude * *(float *)((char *)globals_tag + 0x54) *
                             scaled);

      if ((*(uint32_t *)desired_pitch & 0x7f800000) == 0x7f800000) {
        display_assert(
          csprintf((char *)0x5ab100, "%s: assert_valid_real(0x%08X %f)",
                   "player->desired_angles.pitch", *(uint32_t *)desired_pitch,
                   (double)*desired_pitch),
          "c:\\halo\\SOURCE\\game\\player_control.c", 0x4fd, 1);
        system_exit(NONE);
      }
    }
  }

  /* the limits themselves move no faster than pi/256 per call */
  delta = pitch_minimum_target - pc->pitch_minimum;
  if (delta < -0.0122718466f)
    delta = -0.0122718466f;
  else if (delta > 0.0122718466f)
    delta = 0.0122718466f;
  pc->pitch_minimum += delta;

  delta = pitch_maximum_target - pc->pitch_maximum;
  if (delta < -0.0122718466f)
    delta = -0.0122718466f;
  else if (delta > 0.0122718466f)
    delta = 0.0122718466f;
  pc->pitch_maximum += delta;

  pc->desired_angles_pitch = pitch_delta + pc->desired_angles_pitch;
  if (pc->desired_angles_pitch < pc->pitch_minimum)
    pc->desired_angles_pitch = pc->pitch_minimum;
  else if (pc->desired_angles_pitch > pc->pitch_maximum)
    pc->desired_angles_pitch = pc->pitch_maximum;
}


/* player_control_get_desired_weapon (0xb68c0) — readable C lift. */
int player_control_get_desired_weapon(int16_t local_player_index, int unit_handle)
{
  unsigned char *base;
  unsigned char *slot;
  int weapon;
  short current;

  if (local_player_index < 0 || local_player_index >= 4) {
    display_assert((const char *)0x266fc0, (const char *)0x26e1e8, 0xb1, 1);
    system_exit(-1);
  }
  base = *(unsigned char **)0x457090;
  slot = base + ((int)local_player_index * 0x40) + 0x10;
  if (*(int *)slot == unit_handle) {
    current = *(short *)(slot + 0x20);
    weapon = unit_get_weapon(unit_handle, current);
    if (weapon != -1)
      return weapon;
  }
  {
    char *unit_obj = (char *)object_get_and_verify_type(unit_handle, 3);
    return unit_get_weapon(unit_handle, *(short *)(unit_obj + 0x2a2));
  }
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

/* get_local_player_input_blob (0xb70b0) — XBE naked draft (batch 104). */
#if defined(__clang__)
static int (*const bb70b0_cba3c0)(int16_t local_player_index) = local_player_get_player_index;
static void *(*const bb70b0_memset)(void *, int, unsigned int) = csmemset;
static void * (*const bb70b0_cb6380)(int16_t local_player_index) = player_control_get_data;
static void *(*const bb70b0_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static bool (*const bb70b0_ccf6c0)(int16_t gamepad_index) = input_has_gamepad;
static void * (*const bb70b0_c18e450)(void) = game_globals_get;
static void *(*const bb70b0_elem)(void *, int, int) = tag_block_get_element;
static void * (*const bb70b0_ccf710)(int gamepad_index) = input_get_gamepad_state;
static void * (*const bb70b0_cce7f0)(int gamepad_index) = input_abstraction_get_input_state;
static void *(*const bb70b0_get)(int, int) = object_get_and_verify_type;
static void *(*const bb70b0_tag)(int, int) = tag_get;
static bool (*const bb70b0_cb5c30)(void) = game_time_get_paused;
static void (*const bb70b0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const bb70b0_exitfn)(int) = system_exit;
static float (*const bb70b0_cb64c0)(int16_t count, float *table, float t) = (void *)evaluate_piecewise_linear_function;
static float (*const bb70b0_c1b1350)(int unit_handle, int zoom_level) = unit_get_zoom_magnification;
static int (*const bb70b0_ca6470)(int16_t local_player_index, float *field_2c, float *field_30, float *scratch_a, float *scratch_b) = FUN_000a6470;
static float (*const bb70b0_cb5cc0)(void) = game_time_get_speed;
static bool (*const bb70b0_ca7430)(void) = game_players_are_double_speed;
static void *(*const bb70b0_tryget)(int, int) = object_try_and_get_and_verify_type;
static int (*const bb70b0_ccf690)(void) = FUN_000cf690;
static bool (*const bb70b0_ccf560)(uint16_t) = input_key_is_down;
static void (*const bb70b0_cb6bd0)(char *input) = FUN_000b6bd0;
static char * (*const bb70b0_c8d9d0)(char *buffer, const char *format, ...) = csprintf;

__attribute__((naked, noinline))
void get_local_player_input_blob(int16_t local_player_index __attribute__((unused)), float delta_time __attribute__((unused)), char *out_blob __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x48, %%esp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "call *%[cba3c0]\n\t"
      "pushl $0x20\n\t"
      "pushl $0\n\t"
      "pushl %%ebx\n\t"
      "movl %%eax, %%esi\n\t"
      "call *%[memset]\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpl $-1, %%esi\n\t"
      "je .Lget_local_player_input_blob_120\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "call *%[cb6380]\n\t"
      "movl 0x5aa6d4, %%edx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edx\n\t"
      "movl %%eax, %%edi\n\t"
      "call *%[dget]\n\t"
      "xorl %%esi, %%esi\n\t"
      "movw 0x2(%%eax), %%si\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpw 0x457094, %%si\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "sete -0x1(%%ebp)\n\t"
      "cmpw $-1, %%si\n\t"
      "je .Lget_local_player_input_blob_81\n\t"
      "pushl %%esi\n\t"
      "call *%[ccf6c0]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lget_local_player_input_blob_81\n\t"
      "pushl $0x80\n\t"
      "pushl $0\n\t"
      "call *%[c18e450]\n\t"
      "addl $0x110, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "pushl %%esi\n\t"
      "movl %%eax, -0x20(%%ebp)\n\t"
      "call *%[ccf710]\n\t"
      "pushl %%esi\n\t"
      "movl %%eax, -0x24(%%ebp)\n\t"
      "call *%[cce7f0]\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "movl 0x34(%%eax), %%eax\n\t"
      "addl $0x14, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "movl $0, -0x18(%%ebp)\n\t"
      "movl $0, -0x1c(%%ebp)\n\t"
      "je .Lget_local_player_input_blob_2\n\t"
      "pushl $3\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%esi\n\t"
      "movswl 0x8(%%ebp), %%eax\n\t"
      "shll $2, %%eax\n\t"
      "addl $8, %%esp\n\t"
      "flds 0x457098(%%eax)\n\t"
      "fmuls 0x253d4c\n\t"
      "fmuls 0x2546a4\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "flds 0x4570a8(%%eax)\n\t"
      "movl 0xcc(%%esi), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "fmuls 0x253d4c\n\t"
      "fmuls 0x2546a4\n\t"
      "fstps -0x1c(%%ebp)\n\t"
      "je .Lget_local_player_input_blob_2\n\t"
      "cmpw $-1, 0x2a0(%%esi)\n\t"
      "je .Lget_local_player_input_blob_2\n\t"
      "pushl $3\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl (%%eax), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x756e6974\n\t"
      "call *%[tag]\n\t"
      "movswl 0x2a0(%%esi), %%edx\n\t"
      "pushl $0x11c\n\t"
      "pushl %%edx\n\t"
      "addl $0x2e4, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl %%eax, %%ecx\n\t"
      "addl $0x1c, %%esp\n\t"
      "flds 0x7c(%%ecx)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lget_local_player_input_blob_1\n\t"
      "flds 0x7c(%%ecx)\n\t"
      "fmuls 0x253d4c\n\t"
      "fmuls 0x2546a4\n\t"
      "fstps -0x18(%%ebp)\n\t"
      ".Lget_local_player_input_blob_1:\n\t"
      "flds 0x80(%%ecx)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lget_local_player_input_blob_2\n\t"
      "flds 0x80(%%ecx)\n\t"
      "fmuls 0x253d4c\n\t"
      "fmuls 0x2546a4\n\t"
      "fstps -0x1c(%%ebp)\n\t"
      ".Lget_local_player_input_blob_2:\n\t"
      "movl -0x8(%%ebp), %%esi\n\t"
      "movl 0xc(%%esi), %%eax\n\t"
      "movl %%eax, (%%ebx)\n\t"
      "movl 0x10(%%esi), %%ecx\n\t"
      "movl %%ecx, 0x4(%%ebx)\n\t"
      "flds 0x18(%%esi)\n\t"
      "fabs\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "flds 0x14(%%esi)\n\t"
      "fabs\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "flds 0x2533c8\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fcomps 0x25496c\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lget_local_player_input_blob_5\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fcomps 0x25496c\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lget_local_player_input_blob_5\n\t"
      "fstp %%st(0)\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fcomps -0xc(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lget_local_player_input_blob_3\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fdivs -0x14(%%ebp)\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "flds 0x2533c8\n\t"
      "jmp .Lget_local_player_input_blob_4\n\t"
      ".Lget_local_player_input_blob_3:\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fdivs -0xc(%%ebp)\n\t"
      "movl $0x3f800000, -0xc(%%ebp)\n\t"
      ".Lget_local_player_input_blob_4:\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fmuls -0xc(%%ebp)\n\t"
      "fld %%st(1)\n\t"
      ".byte 0xd8, 0xca\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fsqrt\n\t"
      "fstp %%st(1)\n\t"
      ".Lget_local_player_input_blob_5:\n\t"
      "fld %%st(0)\n\t"
      "fmuls 0x14(%%esi)\n\t"
      "fcoms 0x255e94\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lget_local_player_input_blob_6\n\t"
      "fstp %%st(0)\n\t"
      "movl $0xbf800000, -0x14(%%ebp)\n\t"
      "jmp .Lget_local_player_input_blob_8\n\t"
      ".Lget_local_player_input_blob_6:\n\t"
      "fcoms 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lget_local_player_input_blob_7\n\t"
      "fstp %%st(0)\n\t"
      "movl $0x3f800000, -0x14(%%ebp)\n\t"
      "jmp .Lget_local_player_input_blob_8\n\t"
      ".Lget_local_player_input_blob_7:\n\t"
      "fstps -0x14(%%ebp)\n\t"
      ".Lget_local_player_input_blob_8:\n\t"
      "fmuls 0x18(%%esi)\n\t"
      "fcoms 0x255e94\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lget_local_player_input_blob_9\n\t"
      "fstp %%st(0)\n\t"
      "movl $0xbf800000, -0xc(%%ebp)\n\t"
      "jmp .Lget_local_player_input_blob_11\n\t"
      ".Lget_local_player_input_blob_9:\n\t"
      "fcoms 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lget_local_player_input_blob_10\n\t"
      "fstp %%st(0)\n\t"
      "movl $0x3f800000, -0xc(%%ebp)\n\t"
      "jmp .Lget_local_player_input_blob_11\n\t"
      ".Lget_local_player_input_blob_10:\n\t"
      "fstps -0xc(%%ebp)\n\t"
      ".Lget_local_player_input_blob_11:\n\t"
      "movl 0x457090, %%edx\n\t"
      "testb $1, 0xc(%%edx)\n\t"
      "jne .Lget_local_player_input_blob_38\n\t"
      "call *%[cb5c30]\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lget_local_player_input_blob_38\n\t"
      "movb 0xb(%%esi), %%dl\n\t"
      "testb %%dl, %%dl\n\t"
      "je .Lget_local_player_input_blob_12\n\t"
      "movb 0x4570b9, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lget_local_player_input_blob_12\n\t"
      "movb 0x4570ba, %%cl\n\t"
      "xorl %%eax, %%eax\n\t"
      "testb %%cl, %%cl\n\t"
      "sete %%al\n\t"
      "jmp .Lget_local_player_input_blob_13\n\t"
      ".Lget_local_player_input_blob_12:\n\t"
      "movb 0x4570ba, %%cl\n\t"
      "movzbl %%cl, %%eax\n\t"
      ".Lget_local_player_input_blob_13:\n\t"
      "incl %%eax\n\t"
      "testb %%dl, %%dl\n\t"
      "movl %%eax, -0x28(%%ebp)\n\t"
      "fildl -0x28(%%ebp)\n\t"
      "fstps -0x30(%%ebp)\n\t"
      "je .Lget_local_player_input_blob_14\n\t"
      "movb 0x4570b9, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lget_local_player_input_blob_14\n\t"
      "xorl %%eax, %%eax\n\t"
      "testb %%cl, %%cl\n\t"
      "sete %%al\n\t"
      "jmp .Lget_local_player_input_blob_15\n\t"
      ".Lget_local_player_input_blob_14:\n\t"
      "movzbl %%cl, %%eax\n\t"
      ".Lget_local_player_input_blob_15:\n\t"
      "movl -0x20(%%ebp), %%esi\n\t"
      "incl %%eax\n\t"
      "movl %%eax, -0x28(%%ebp)\n\t"
      "fildl -0x28(%%ebp)\n\t"
      "movl 0x74(%%esi), %%eax\n\t"
      "cmpl $1, %%eax\n\t"
      "fstps -0x28(%%ebp)\n\t"
      "jg .Lget_local_player_input_blob_16\n\t"
      "pushl $1\n\t"
      "pushl $0x1c8\n\t"
      "pushl $0x26e1e8\n\t"
      "pushl $0x26e324\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lget_local_player_input_blob_16:\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "movl 0x78(%%esi), %%ecx\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x74(%%esi), %%dx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[cb64c0]\n\t"
      "fmuls -0x28(%%ebp)\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "movl 0x78(%%esi), %%ecx\n\t"
      "fmuls -0x18(%%ebp)\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x74(%%esi), %%dx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "fstps -0x3c(%%ebp)\n\t"
      "pushl %%edx\n\t"
      "call *%[cb64c0]\n\t"
      "fmuls -0x30(%%ebp)\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "movl 0x34(%%eax), %%eax\n\t"
      "fmuls -0x1c(%%ebp)\n\t"
      "addl $0x18, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "fstps -0x38(%%ebp)\n\t"
      "je .Lget_local_player_input_blob_17\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x24(%%edi), %%cx\n\t"
      "cmpw $-1, %%cx\n\t"
      "je .Lget_local_player_input_blob_17\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "call *%[c1b1350]\n\t"
      "fdivrs 0x2533c8\n\t"
      "addl $8, %%esp\n\t"
      "flds -0x3c(%%ebp)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fstps -0x3c(%%ebp)\n\t"
      "fmuls -0x38(%%ebp)\n\t"
      "fstps -0x38(%%ebp)\n\t"
      ".Lget_local_player_input_blob_17:\n\t"
      "movl -0x10(%%ebp), %%ecx\n\t"
      "cmpl $-1, 0x34(%%ecx)\n\t"
      "je .Lget_local_player_input_blob_18\n\t"
      "pushl $0xf4\n\t"
      "pushl $0\n\t"
      "call *%[c18e450]\n\t"
      "addl $0x170, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl -0x10(%%ebp), %%edx\n\t"
      "movl %%eax, -0x30(%%ebp)\n\t"
      "movl 0x34(%%edx), %%eax\n\t"
      "pushl $3\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "flds 0x3d4(%%eax)\n\t"
      "movl -0x30(%%ebp), %%ecx\n\t"
      "fmuls 0x84(%%ecx)\n\t"
      "addl $0x14, %%esp\n\t"
      "fsubrs 0x2533c8\n\t"
      "flds -0x3c(%%ebp)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fstps -0x3c(%%ebp)\n\t"
      "fmuls -0x38(%%ebp)\n\t"
      "fstps -0x38(%%ebp)\n\t"
      ".Lget_local_player_input_blob_18:\n\t"
      "flds 0x40(%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .Lget_local_player_input_blob_19\n\t"
      "pushl $1\n\t"
      "pushl $0x1e3\n\t"
      "pushl $0x26e1e8\n\t"
      "pushl $0x26e2fc\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lget_local_player_input_blob_19:\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fabs\n\t"
      "fstl -0x2c(%%ebp)\n\t"
      "flds 0x48(%%esi)\n\t"
      "fxch %%st(1)\n\t"
      "fcompp\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .Lget_local_player_input_blob_22\n\t"
      "flds 0x34(%%edi)\n\t"
      "fdivs 0x40(%%esi)\n\t"
      "fcoms 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lget_local_player_input_blob_20\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c0\n\t"
      "jmp .Lget_local_player_input_blob_21\n\t"
      ".Lget_local_player_input_blob_20:\n\t"
      "fcoms 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lget_local_player_input_blob_21\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c8\n\t"
      ".Lget_local_player_input_blob_21:\n\t"
      "flds 0x44(%%esi)\n\t"
      "fsubs 0x2533c8\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fadds 0x2533c8\n\t"
      "fmuls -0x3c(%%ebp)\n\t"
      "fstps -0x3c(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fadds 0x34(%%edi)\n\t"
      "fstps 0x34(%%edi)\n\t"
      "jmp .Lget_local_player_input_blob_23\n\t"
      ".Lget_local_player_input_blob_22:\n\t"
      "movl $0, 0x34(%%edi)\n\t"
      ".Lget_local_player_input_blob_23:\n\t"
      "leal -0x34(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x44(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal 0x30(%%edi), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "leal 0x2c(%%edi), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[ca6470]\n\t"
      "movl %%eax, 0x28(%%edi)\n\t"
      "movb 0x2f0291, %%al\n\t"
      "addl $0x14, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lget_local_player_input_blob_36\n\t"
      "flds 0x30(%%edi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lget_local_player_input_blob_36\n\t"
      "fldl -0x2c(%%ebp)\n\t"
      "fcompl 0x2533d0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .Lget_local_player_input_blob_24\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fabs\n\t"
      "fcompl 0x2533d0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .Lget_local_player_input_blob_24\n\t"
      "flds (%%ebx)\n\t"
      "fabs\n\t"
      "fcompl 0x2533d0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .Lget_local_player_input_blob_24\n\t"
      "flds 0x4(%%ebx)\n\t"
      "fabs\n\t"
      "fcompl 0x2533d0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lget_local_player_input_blob_36\n\t"
      ".Lget_local_player_input_blob_24:\n\t"
      "call *%[cb5cc0]\n\t"
      "fstps -0x1c(%%ebp)\n\t"
      "flds (%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lget_local_player_input_blob_25\n\t"
      "flds 0x2533c0\n\t"
      "jmp .Lget_local_player_input_blob_27\n\t"
      ".Lget_local_player_input_blob_25:\n\t"
      "flds (%%esi)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lget_local_player_input_blob_26\n\t"
      "flds 0x2533c8\n\t"
      "jmp .Lget_local_player_input_blob_27\n\t"
      ".Lget_local_player_input_blob_26:\n\t"
      "flds (%%esi)\n\t"
      ".Lget_local_player_input_blob_27:\n\t"
      "fmuls 0x30(%%edi)\n\t"
      "fsubrs 0x2533c8\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "flds 0x4(%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lget_local_player_input_blob_28\n\t"
      "flds 0x2533c0\n\t"
      "jmp .Lget_local_player_input_blob_30\n\t"
      ".Lget_local_player_input_blob_28:\n\t"
      "flds 0x4(%%esi)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lget_local_player_input_blob_29\n\t"
      "flds 0x2533c8\n\t"
      "jmp .Lget_local_player_input_blob_30\n\t"
      ".Lget_local_player_input_blob_29:\n\t"
      "flds 0x4(%%esi)\n\t"
      ".Lget_local_player_input_blob_30:\n\t"
      "fmuls 0x30(%%edi)\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "call *%[ca7430]\n\t"
      "testb %%al, %%al\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "je .Lget_local_player_input_blob_31\n\t"
      "fmuls 0x253398\n\t"
      ".Lget_local_player_input_blob_31:\n\t"
      "flds -0x34(%%ebp)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fstps -0x34(%%ebp)\n\t"
      "fmuls -0x30(%%ebp)\n\t"
      "flds -0x34(%%ebp)\n\t"
      "fcomps 0x26e2f8\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lget_local_player_input_blob_32\n\t"
      "movl $0xbdd67750, -0x34(%%ebp)\n\t"
      "jmp .Lget_local_player_input_blob_33\n\t"
      ".Lget_local_player_input_blob_32:\n\t"
      "flds -0x34(%%ebp)\n\t"
      "fcomps 0x26e2f4\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lget_local_player_input_blob_33\n\t"
      "movl $0x3dd67750, -0x34(%%ebp)\n\t"
      ".Lget_local_player_input_blob_33:\n\t"
      "fcoms 0x26e2f0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lget_local_player_input_blob_34\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x26e2f0\n\t"
      "jmp .Lget_local_player_input_blob_35\n\t"
      ".Lget_local_player_input_blob_34:\n\t"
      "fcoms 0x26e2ec\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lget_local_player_input_blob_35\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x26e2ec\n\t"
      ".Lget_local_player_input_blob_35:\n\t"
      "flds -0x34(%%ebp)\n\t"
      "fmuls -0x18(%%ebp)\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fmuls -0x3c(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fstps -0x3c(%%ebp)\n\t"
      "fmuls -0x18(%%ebp)\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fmuls -0x38(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "jmp .Lget_local_player_input_blob_37\n\t"
      ".Lget_local_player_input_blob_36:\n\t"
      "flds -0x38(%%ebp)\n\t"
      ".Lget_local_player_input_blob_37:\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fmuls 0x253394\n\t"
      "flds -0x3c(%%ebp)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fstps 0xc(%%ebx)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fstps 0x10(%%ebx)\n\t"
      "fstp %%st(0)\n\t"
      "jmp .Lget_local_player_input_blob_39\n\t"
      ".Lget_local_player_input_blob_38:\n\t"
      "xorl %%eax, %%eax\n\t"
      "movl %%eax, 0xc(%%ebx)\n\t"
      "movl %%eax, 0x10(%%ebx)\n\t"
      ".Lget_local_player_input_blob_39:\n\t"
      "xorl %%eax, %%eax\n\t"
      "movb %%al, -0x3d(%%ebp)\n\t"
      "movl %%eax, -0x47(%%ebp)\n\t"
      "movl %%eax, -0x43(%%ebp)\n\t"
      "movw %%ax, -0x3f(%%ebp)\n\t"
      "movw 0xa(%%edi), %%ax\n\t"
      "andw 0x8(%%edi), %%ax\n\t"
      "movb $0, -0x48(%%ebp)\n\t"
      "testw %%ax, %%ax\n\t"
      "je .Lget_local_player_input_blob_47\n\t"
      "movzwl %%ax, %%esi\n\t"
      "movl %%esi, -0x1c(%%ebp)\n\t"
      "movl $1, %%edx\n\t"
      "jmp .Lget_local_player_input_blob_40\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".Lget_local_player_input_blob_40:\n\t"
      "leal -0x1(%%edx), %%ecx\n\t"
      "movl $1, %%eax\n\t"
      "shll %%cl, %%eax\n\t"
      "testl %%eax, %%esi\n\t"
      "je .Lget_local_player_input_blob_41\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movb -0x1(%%ecx,%%edx,1), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lget_local_player_input_blob_41\n\t"
      "movl $1, %%eax\n\t"
      "leal -0x1(%%edx), %%ecx\n\t"
      "shll %%cl, %%eax\n\t"
      "notl %%eax\n\t"
      "andw %%ax, 0x8(%%edi)\n\t"
      "andw %%ax, 0xa(%%edi)\n\t"
      ".Lget_local_player_input_blob_41:\n\t"
      "movl $1, %%eax\n\t"
      "movl %%edx, %%ecx\n\t"
      "shll %%cl, %%eax\n\t"
      "testl %%eax, %%esi\n\t"
      "je .Lget_local_player_input_blob_42\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "cmpb $0, (%%edx,%%ecx,1)\n\t"
      "jne .Lget_local_player_input_blob_42\n\t"
      "movl $1, %%eax\n\t"
      "movl %%edx, %%ecx\n\t"
      "shll %%cl, %%eax\n\t"
      "notl %%eax\n\t"
      "andw %%ax, 0x8(%%edi)\n\t"
      "andw %%ax, 0xa(%%edi)\n\t"
      ".Lget_local_player_input_blob_42:\n\t"
      "leal 0x1(%%edx), %%ecx\n\t"
      "movl $1, %%eax\n\t"
      "shll %%cl, %%eax\n\t"
      "testl %%eax, %%esi\n\t"
      "je .Lget_local_player_input_blob_43\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movb 0x1(%%edx,%%ecx,1), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lget_local_player_input_blob_43\n\t"
      "movl $1, %%eax\n\t"
      "leal 0x1(%%edx), %%ecx\n\t"
      "shll %%cl, %%eax\n\t"
      "notl %%eax\n\t"
      "andw %%ax, 0x8(%%edi)\n\t"
      "andw %%ax, 0xa(%%edi)\n\t"
      ".Lget_local_player_input_blob_43:\n\t"
      "leal 0x2(%%edx), %%ecx\n\t"
      "movl $1, %%eax\n\t"
      "shll %%cl, %%eax\n\t"
      "testl %%eax, %%esi\n\t"
      "je .Lget_local_player_input_blob_44\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movb 0x2(%%edx,%%ecx,1), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lget_local_player_input_blob_44\n\t"
      "movl $1, %%eax\n\t"
      "leal 0x2(%%edx), %%ecx\n\t"
      "shll %%cl, %%eax\n\t"
      "notl %%eax\n\t"
      "andw %%ax, 0x8(%%edi)\n\t"
      "andw %%ax, 0xa(%%edi)\n\t"
      ".Lget_local_player_input_blob_44:\n\t"
      "leal 0x3(%%edx), %%ecx\n\t"
      "movl $1, %%eax\n\t"
      "shll %%cl, %%eax\n\t"
      "testl %%eax, %%esi\n\t"
      "je .Lget_local_player_input_blob_45\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movb 0x3(%%edx,%%ecx,1), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lget_local_player_input_blob_45\n\t"
      "movl $1, %%eax\n\t"
      "leal 0x3(%%edx), %%ecx\n\t"
      "shll %%cl, %%eax\n\t"
      "notl %%eax\n\t"
      "andw %%ax, 0x8(%%edi)\n\t"
      "andw %%ax, 0xa(%%edi)\n\t"
      ".Lget_local_player_input_blob_45:\n\t"
      "movl -0x1c(%%ebp), %%esi\n\t"
      "leal 0x4(%%edx), %%ecx\n\t"
      "movl $1, %%eax\n\t"
      "shll %%cl, %%eax\n\t"
      "testl %%eax, %%esi\n\t"
      "je .Lget_local_player_input_blob_46\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "cmpb $0, 0x4(%%edx,%%eax,1)\n\t"
      "jne .Lget_local_player_input_blob_46\n\t"
      "movl $1, %%eax\n\t"
      "shll %%cl, %%eax\n\t"
      "notl %%eax\n\t"
      "andw %%ax, 0x8(%%edi)\n\t"
      "andw %%ax, 0xa(%%edi)\n\t"
      ".Lget_local_player_input_blob_46:\n\t"
      "addl $6, %%edx\n\t"
      "leal -0x1(%%edx), %%ecx\n\t"
      "cmpl $0xc, %%ecx\n\t"
      "jl .Lget_local_player_input_blob_40\n\t"
      ".Lget_local_player_input_blob_47:\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "leal -0x48(%%ebp), %%ecx\n\t"
      "subl %%ecx, %%eax\n\t"
      "movl %%eax, -0x1c(%%ebp)\n\t"
      "leal -0x48(%%ebp), %%eax\n\t"
      "movl $1, %%esi\n\t"
      "subl %%eax, %%esi\n\t"
      "leal -0x48(%%ebp), %%ecx\n\t"
      "movl $2, %%eax\n\t"
      "subl %%ecx, %%eax\n\t"
      "movl %%eax, -0x18(%%ebp)\n\t"
      "leal -0x48(%%ebp), %%ecx\n\t"
      "movl $3, %%eax\n\t"
      "subl %%ecx, %%eax\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "leal -0x48(%%ebp), %%ecx\n\t"
      "movl $4, %%eax\n\t"
      "subl %%ecx, %%eax\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "movl $5, %%eax\n\t"
      "leal -0x48(%%ebp), %%ecx\n\t"
      "xorl %%edx, %%edx\n\t"
      "subl %%ecx, %%eax\n\t"
      "movl %%esi, -0x30(%%ebp)\n\t"
      "movl %%eax, -0x38(%%ebp)\n\t"
      "jmp .Lget_local_player_input_blob_49\n\t"
      ".Lget_local_player_input_blob_48:\n\t"
      "movl -0x30(%%ebp), %%esi\n\t"
      "jmp .Lget_local_player_input_blob_49\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".Lget_local_player_input_blob_49:\n\t"
      "movl %%edx, %%ecx\n\t"
      "movl $1, %%eax\n\t"
      "shll %%cl, %%eax\n\t"
      "movl %%eax, %%ecx\n\t"
      "movzwl 0x8(%%edi), %%eax\n\t"
      "testl %%ecx, %%eax\n\t"
      "jne .Lget_local_player_input_blob_50\n\t"
      "movl -0x1c(%%ebp), %%ecx\n\t"
      "leal -0x48(%%ebp,%%edx,1), %%eax\n\t"
      "movb (%%ecx,%%eax,1), %%cl\n\t"
      "movb %%cl, (%%eax)\n\t"
      ".Lget_local_player_input_blob_50:\n\t"
      "leal -0x48(%%ebp,%%edx,1), %%eax\n\t"
      "leal (%%esi,%%eax,1), %%ecx\n\t"
      "movl $1, %%esi\n\t"
      "shll %%cl, %%esi\n\t"
      "movzwl 0x8(%%edi), %%ecx\n\t"
      "testl %%esi, %%ecx\n\t"
      "jne .Lget_local_player_input_blob_51\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movb 0x1(%%edx,%%ecx,1), %%cl\n\t"
      "movb %%cl, 0x1(%%eax)\n\t"
      ".Lget_local_player_input_blob_51:\n\t"
      "movl -0x18(%%ebp), %%ecx\n\t"
      "addl %%eax, %%ecx\n\t"
      "movl $1, %%esi\n\t"
      "shll %%cl, %%esi\n\t"
      "movzwl 0x8(%%edi), %%ecx\n\t"
      "testl %%esi, %%ecx\n\t"
      "jne .Lget_local_player_input_blob_52\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movb 0x2(%%edx,%%ecx,1), %%cl\n\t"
      "movb %%cl, 0x2(%%eax)\n\t"
      ".Lget_local_player_input_blob_52:\n\t"
      "movl -0x14(%%ebp), %%ecx\n\t"
      "addl %%eax, %%ecx\n\t"
      "movl $1, %%esi\n\t"
      "shll %%cl, %%esi\n\t"
      "movzwl 0x8(%%edi), %%ecx\n\t"
      "testl %%esi, %%ecx\n\t"
      "jne .Lget_local_player_input_blob_53\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movb 0x3(%%edx,%%ecx,1), %%cl\n\t"
      "movb %%cl, 0x3(%%eax)\n\t"
      ".Lget_local_player_input_blob_53:\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "addl %%eax, %%ecx\n\t"
      "movl $1, %%esi\n\t"
      "shll %%cl, %%esi\n\t"
      "movzwl 0x8(%%edi), %%ecx\n\t"
      "testl %%esi, %%ecx\n\t"
      "jne .Lget_local_player_input_blob_54\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movb 0x4(%%edx,%%ecx,1), %%cl\n\t"
      "movb %%cl, 0x4(%%eax)\n\t"
      ".Lget_local_player_input_blob_54:\n\t"
      "movl -0x38(%%ebp), %%ecx\n\t"
      "addl %%eax, %%ecx\n\t"
      "movl $1, %%esi\n\t"
      "shll %%cl, %%esi\n\t"
      "movzwl 0x8(%%edi), %%ecx\n\t"
      "testl %%esi, %%ecx\n\t"
      "jne .Lget_local_player_input_blob_55\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movb 0x5(%%edx,%%ecx,1), %%cl\n\t"
      "movb %%cl, 0x5(%%eax)\n\t"
      ".Lget_local_player_input_blob_55:\n\t"
      "addl $6, %%edx\n\t"
      "cmpl $0xc, %%edx\n\t"
      "jl .Lget_local_player_input_blob_48\n\t"
      "movl -0x10(%%ebp), %%edx\n\t"
      "movl 0x34(%%edx), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lget_local_player_input_blob_59\n\t"
      "pushl $1\n\t"
      "pushl %%eax\n\t"
      "call *%[tryget]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lget_local_player_input_blob_59\n\t"
      "movb 0x4570b8, %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "jne .Lget_local_player_input_blob_56\n\t"
      "testb $1, 0x424(%%eax)\n\t"
      "jne .Lget_local_player_input_blob_56\n\t"
      "flds 0x4(%%ebx)\n\t"
      "flds (%%ebx)\n\t"
      "fld %%st(1)\n\t"
      ".byte 0xd8, 0xca\n\t"
      "fld %%st(1)\n\t"
      ".byte 0xd8, 0xca\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fcomps 0x26e2e8\n\t"
      "fnstsw %%ax\n\t"
      "fstp %%st(0)\n\t"
      "testb $5, %%ah\n\t"
      "fstp %%st(0)\n\t"
      "jp .Lget_local_player_input_blob_59\n\t"
      ".Lget_local_player_input_blob_56:\n\t"
      "movb -0x3e(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "movl 0x18(%%ebx), %%eax\n\t"
      "je .Lget_local_player_input_blob_57\n\t"
      "orl $1, %%eax\n\t"
      "jmp .Lget_local_player_input_blob_58\n\t"
      ".Lget_local_player_input_blob_57:\n\t"
      "andl $0xfffffffe, %%eax\n\t"
      ".Lget_local_player_input_blob_58:\n\t"
      "movl %%eax, 0x18(%%ebx)\n\t"
      ".Lget_local_player_input_blob_59:\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movzbl 0x7(%%eax), %%ecx\n\t"
      "movb -0x41(%%ebp), %%al\n\t"
      "movl %%ecx, -0x38(%%ebp)\n\t"
      "testb %%al, %%al\n\t"
      "movl 0x18(%%ebx), %%eax\n\t"
      "fildl -0x38(%%ebp)\n\t"
      "fmuls 0x26e1e4\n\t"
      "fstps 0x8(%%ebx)\n\t"
      "je .Lget_local_player_input_blob_60\n\t"
      "orl $0x800, %%eax\n\t"
      "jmp .Lget_local_player_input_blob_61\n\t"
      ".Lget_local_player_input_blob_60:\n\t"
      "andl $0xfffff7ff, %%eax\n\t"
      ".Lget_local_player_input_blob_61:\n\t"
      "movl %%eax, 0x18(%%ebx)\n\t"
      "movb -0x42(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "movl 0x18(%%ebx), %%eax\n\t"
      "je .Lget_local_player_input_blob_62\n\t"
      "orl $0x2000, %%eax\n\t"
      "movl %%eax, 0x18(%%ebx)\n\t"
      "orl $0x1000, %%eax\n\t"
      "jmp .Lget_local_player_input_blob_63\n\t"
      ".Lget_local_player_input_blob_62:\n\t"
      "andl $0xffffdfff, %%eax\n\t"
      "movl %%eax, 0x18(%%ebx)\n\t"
      "andl $0xffffefff, %%eax\n\t"
      ".Lget_local_player_input_blob_63:\n\t"
      "movl %%eax, 0x18(%%ebx)\n\t"
      "cmpb $1, -0x3d(%%ebp)\n\t"
      "movl 0x1c(%%ebx), %%eax\n\t"
      "jne .Lget_local_player_input_blob_64\n\t"
      "orl $4, %%eax\n\t"
      "jmp .Lget_local_player_input_blob_65\n\t"
      ".Lget_local_player_input_blob_64:\n\t"
      "andl $0xfffffffb, %%eax\n\t"
      ".Lget_local_player_input_blob_65:\n\t"
      "movl 0x18(%%ebx), %%ecx\n\t"
      "movl %%eax, 0x1c(%%ebx)\n\t"
      "movb -0x46(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lget_local_player_input_blob_66\n\t"
      "orl $0x40, %%ecx\n\t"
      "jmp .Lget_local_player_input_blob_67\n\t"
      ".Lget_local_player_input_blob_66:\n\t"
      "andl $0xffffffbf, %%ecx\n\t"
      ".Lget_local_player_input_blob_67:\n\t"
      "movzbl %%al, %%edx\n\t"
      "movl -0x20(%%ebp), %%eax\n\t"
      "movl %%ecx, 0x18(%%ebx)\n\t"
      "cmpw 0x6c(%%eax), %%dx\n\t"
      "movl %%ecx, %%eax\n\t"
      "jl .Lget_local_player_input_blob_68\n\t"
      "orl $0x4000, %%eax\n\t"
      "jmp .Lget_local_player_input_blob_69\n\t"
      ".Lget_local_player_input_blob_68:\n\t"
      "andl $0xffffbfff, %%eax\n\t"
      ".Lget_local_player_input_blob_69:\n\t"
      "movl %%eax, 0x18(%%ebx)\n\t"
      "movb -0x43(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "movl 0x18(%%ebx), %%eax\n\t"
      "je .Lget_local_player_input_blob_70\n\t"
      "orl $0x10, %%eax\n\t"
      "jmp .Lget_local_player_input_blob_71\n\t"
      ".Lget_local_player_input_blob_70:\n\t"
      "andl $0xffffffef, %%eax\n\t"
      ".Lget_local_player_input_blob_71:\n\t"
      "movb -0x48(%%ebp), %%cl\n\t"
      "movl %%eax, 0x18(%%ebx)\n\t"
      "testb %%cl, %%cl\n\t"
      "movl 0x18(%%ebx), %%ecx\n\t"
      "movl $0xfffffffd, %%eax\n\t"
      "je .Lget_local_player_input_blob_72\n\t"
      "orl $2, %%ecx\n\t"
      "jmp .Lget_local_player_input_blob_73\n\t"
      ".Lget_local_player_input_blob_72:\n\t"
      "andl %%eax, %%ecx\n\t"
      ".Lget_local_player_input_blob_73:\n\t"
      "movl %%ecx, 0x18(%%ebx)\n\t"
      "movb -0x44(%%ebp), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "movl 0x18(%%ebx), %%ecx\n\t"
      "je .Lget_local_player_input_blob_74\n\t"
      "orl $0x80, %%ecx\n\t"
      "jmp .Lget_local_player_input_blob_75\n\t"
      ".Lget_local_player_input_blob_74:\n\t"
      "andl $0xffffff7f, %%ecx\n\t"
      ".Lget_local_player_input_blob_75:\n\t"
      "movl %%ecx, 0x18(%%ebx)\n\t"
      "cmpb $1, -0x45(%%ebp)\n\t"
      "movl 0x1c(%%ebx), %%ecx\n\t"
      "jne .Lget_local_player_input_blob_76\n\t"
      "orl $1, %%ecx\n\t"
      "jmp .Lget_local_player_input_blob_77\n\t"
      ".Lget_local_player_input_blob_76:\n\t"
      "andl $0xfffffffe, %%ecx\n\t"
      ".Lget_local_player_input_blob_77:\n\t"
      "movl %%ecx, 0x1c(%%ebx)\n\t"
      "cmpb $1, -0x47(%%ebp)\n\t"
      "jne .Lget_local_player_input_blob_78\n\t"
      "orl $2, 0x1c(%%ebx)\n\t"
      "jmp .Lget_local_player_input_blob_79\n\t"
      ".Lget_local_player_input_blob_78:\n\t"
      "andl %%eax, 0x1c(%%ebx)\n\t"
      ".Lget_local_player_input_blob_79:\n\t"
      "testb $2, 0x9(%%edi)\n\t"
      "jne .Lget_local_player_input_blob_80\n\t"
      "movl -0x24(%%ebp), %%ecx\n\t"
      "movb 0x11(%%ecx), %%dl\n\t"
      "movb %%dl, 0x15(%%ebx)\n\t"
      ".Lget_local_player_input_blob_80:\n\t"
      "testb $4, 0x8(%%edi)\n\t"
      "jne .Lget_local_player_input_blob_108\n\t"
      "movl -0x24(%%ebp), %%eax\n\t"
      "movb 0x10(%%eax), %%cl\n\t"
      "movb %%cl, 0x14(%%ebx)\n\t"
      "jmp .Lget_local_player_input_blob_108\n\t"
      ".Lget_local_player_input_blob_81:\n\t"
      "call *%[ccf690]\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lget_local_player_input_blob_108\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lget_local_player_input_blob_108\n\t"
      "call *%[ccf690]\n\t"
      "pushl $0x2e\n\t"
      "movl %%eax, %%edi\n\t"
      "call *%[ccf560]\n\t"
      "negb %%al\n\t"
      "pushl $0x20\n\t"
      "sbbl %%eax, %%eax\n\t"
      "negl %%eax\n\t"
      "movl %%eax, -0x38(%%ebp)\n\t"
      "call *%[ccf560]\n\t"
      "movl -0x38(%%ebp), %%ecx\n\t"
      "negb %%al\n\t"
      "pushl $0x2f\n\t"
      "sbbl %%eax, %%eax\n\t"
      "negl %%eax\n\t"
      "subl %%ecx, %%eax\n\t"
      "movl %%eax, -0x38(%%ebp)\n\t"
      "fildl -0x38(%%ebp)\n\t"
      "fstps (%%ebx)\n\t"
      "call *%[ccf560]\n\t"
      "negb %%al\n\t"
      "pushl $0x2d\n\t"
      "sbbl %%eax, %%eax\n\t"
      "negl %%eax\n\t"
      "movl %%eax, -0x38(%%ebp)\n\t"
      "call *%[ccf560]\n\t"
      "movl -0x38(%%ebp), %%ecx\n\t"
      "movl 0x457090, %%edx\n\t"
      "addl $0x10, %%esp\n\t"
      "negb %%al\n\t"
      "sbbl %%eax, %%eax\n\t"
      "negl %%eax\n\t"
      "subl %%ecx, %%eax\n\t"
      "movl %%eax, -0x38(%%ebp)\n\t"
      "fildl -0x38(%%ebp)\n\t"
      "fstps 0x4(%%ebx)\n\t"
      "movb 0xc(%%edx), %%al\n\t"
      "testb $1, %%al\n\t"
      "jne .Lget_local_player_input_blob_82\n\t"
      "call *%[cb5c30]\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lget_local_player_input_blob_82\n\t"
      "fildl (%%edi)\n\t"
      "fmuls 0x26e1dc\n\t"
      "fchs\n\t"
      "fstps 0xc(%%ebx)\n\t"
      "fildl 0x4(%%edi)\n\t"
      "fmuls 0x26e1e0\n\t"
      "fchs\n\t"
      "fstps 0x10(%%ebx)\n\t"
      "jmp .Lget_local_player_input_blob_83\n\t"
      ".Lget_local_player_input_blob_82:\n\t"
      "xorl %%eax, %%eax\n\t"
      "movl %%eax, 0xc(%%ebx)\n\t"
      "movl %%eax, 0x10(%%ebx)\n\t"
      ".Lget_local_player_input_blob_83:\n\t"
      "pushl $0x69\n\t"
      "call *%[ccf560]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "movl 0x18(%%ebx), %%eax\n\t"
      "je .Lget_local_player_input_blob_84\n\t"
      "orl $0x100, %%eax\n\t"
      "jmp .Lget_local_player_input_blob_85\n\t"
      ".Lget_local_player_input_blob_84:\n\t"
      "andl $0xfffffeff, %%eax\n\t"
      ".Lget_local_player_input_blob_85:\n\t"
      "pushl $0x6c\n\t"
      "movl %%eax, 0x18(%%ebx)\n\t"
      "call *%[ccf560]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "movl 0x18(%%ebx), %%eax\n\t"
      "je .Lget_local_player_input_blob_86\n\t"
      "orl $0x200, %%eax\n\t"
      "jmp .Lget_local_player_input_blob_87\n\t"
      ".Lget_local_player_input_blob_86:\n\t"
      "andl $0xfffffdff, %%eax\n\t"
      ".Lget_local_player_input_blob_87:\n\t"
      "pushl $0x6a\n\t"
      "movl %%eax, 0x18(%%ebx)\n\t"
      "call *%[ccf560]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "movl 0x18(%%ebx), %%eax\n\t"
      "je .Lget_local_player_input_blob_88\n\t"
      "orl $1, %%eax\n\t"
      "jmp .Lget_local_player_input_blob_89\n\t"
      ".Lget_local_player_input_blob_88:\n\t"
      "andl $0xfffffffe, %%eax\n\t"
      ".Lget_local_player_input_blob_89:\n\t"
      "pushl $0x48\n\t"
      "movl %%eax, 0x18(%%ebx)\n\t"
      "call *%[ccf560]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "movl 0x18(%%ebx), %%eax\n\t"
      "je .Lget_local_player_input_blob_90\n\t"
      "orl $2, %%eax\n\t"
      "jmp .Lget_local_player_input_blob_91\n\t"
      ".Lget_local_player_input_blob_90:\n\t"
      "andl $0xfffffffd, %%eax\n\t"
      ".Lget_local_player_input_blob_91:\n\t"
      "pushl $0x1f\n\t"
      "movl %%eax, 0x18(%%ebx)\n\t"
      "call *%[ccf560]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "movl 0x18(%%ebx), %%eax\n\t"
      "je .Lget_local_player_input_blob_92\n\t"
      "orl $0x40, %%eax\n\t"
      "jmp .Lget_local_player_input_blob_93\n\t"
      ".Lget_local_player_input_blob_92:\n\t"
      "andl $0xffffffbf, %%eax\n\t"
      ".Lget_local_player_input_blob_93:\n\t"
      "pushl $0x3b\n\t"
      "movl %%eax, 0x18(%%ebx)\n\t"
      "call *%[ccf560]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "movl 0x18(%%ebx), %%eax\n\t"
      "je .Lget_local_player_input_blob_94\n\t"
      "orl $0x10, %%eax\n\t"
      "jmp .Lget_local_player_input_blob_95\n\t"
      ".Lget_local_player_input_blob_94:\n\t"
      "andl $0xffffffef, %%eax\n\t"
      ".Lget_local_player_input_blob_95:\n\t"
      "pushl $0x22\n\t"
      "movl %%eax, 0x18(%%ebx)\n\t"
      "call *%[ccf560]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "movl 0x18(%%ebx), %%eax\n\t"
      "je .Lget_local_player_input_blob_96\n\t"
      "orl $0x400, %%eax\n\t"
      "jmp .Lget_local_player_input_blob_97\n\t"
      ".Lget_local_player_input_blob_96:\n\t"
      "andl $0xfffffbff, %%eax\n\t"
      ".Lget_local_player_input_blob_97:\n\t"
      "movl %%eax, 0x18(%%ebx)\n\t"
      "movb 0xc(%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "movl 0x18(%%ebx), %%eax\n\t"
      "movl $0x800, %%esi\n\t"
      "je .Lget_local_player_input_blob_98\n\t"
      "orl %%esi, %%eax\n\t"
      "jmp .Lget_local_player_input_blob_99\n\t"
      ".Lget_local_player_input_blob_98:\n\t"
      "andl $0xfffff7ff, %%eax\n\t"
      ".Lget_local_player_input_blob_99:\n\t"
      "movl %%eax, 0x18(%%ebx)\n\t"
      "movb 0xe(%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "movl 0x18(%%ebx), %%eax\n\t"
      "je .Lget_local_player_input_blob_100\n\t"
      "orl $0x2000, %%eax\n\t"
      "jmp .Lget_local_player_input_blob_101\n\t"
      ".Lget_local_player_input_blob_100:\n\t"
      "andl $0xffffdfff, %%eax\n\t"
      ".Lget_local_player_input_blob_101:\n\t"
      "pushl $0x3a\n\t"
      "movl %%eax, 0x18(%%ebx)\n\t"
      "call *%[ccf560]\n\t"
      "addl $4, %%esp\n\t"
      "cmpb $1, %%al\n\t"
      "movl 0x1c(%%ebx), %%eax\n\t"
      "jne .Lget_local_player_input_blob_102\n\t"
      "orl $4, %%eax\n\t"
      "jmp .Lget_local_player_input_blob_103\n\t"
      ".Lget_local_player_input_blob_102:\n\t"
      "andl $0xfffffffb, %%eax\n\t"
      ".Lget_local_player_input_blob_103:\n\t"
      "pushl $0x21\n\t"
      "movl %%eax, 0x1c(%%ebx)\n\t"
      "call *%[ccf560]\n\t"
      "addl $4, %%esp\n\t"
      "cmpb $1, %%al\n\t"
      "movl 0x1c(%%ebx), %%eax\n\t"
      "jne .Lget_local_player_input_blob_104\n\t"
      "orl $1, %%eax\n\t"
      "jmp .Lget_local_player_input_blob_105\n\t"
      ".Lget_local_player_input_blob_104:\n\t"
      "andl $0xfffffffe, %%eax\n\t"
      ".Lget_local_player_input_blob_105:\n\t"
      "movl %%eax, 0x1c(%%ebx)\n\t"
      "testl %%esi, 0x18(%%ebx)\n\t"
      "je .Lget_local_player_input_blob_106\n\t"
      "flds 0x2533c8\n\t"
      "jmp .Lget_local_player_input_blob_107\n\t"
      ".Lget_local_player_input_blob_106:\n\t"
      "flds 0x2533c0\n\t"
      ".Lget_local_player_input_blob_107:\n\t"
      "fstps 0x8(%%ebx)\n\t"
      ".Lget_local_player_input_blob_108:\n\t"
      "pushl $0x2b\n\t"
      "call *%[ccf560]\n\t"
      "addl $4, %%esp\n\t"
      "cmpb $1, %%al\n\t"
      "movl 0x1c(%%ebx), %%eax\n\t"
      "movl $0xfffffff7, %%esi\n\t"
      "movl $8, %%edi\n\t"
      "jne .Lget_local_player_input_blob_109\n\t"
      "orl %%edi, %%eax\n\t"
      "jmp .Lget_local_player_input_blob_110\n\t"
      ".Lget_local_player_input_blob_109:\n\t"
      "andl %%esi, %%eax\n\t"
      ".Lget_local_player_input_blob_110:\n\t"
      "pushl $0x2a\n\t"
      "movl %%eax, 0x1c(%%ebx)\n\t"
      "call *%[ccf560]\n\t"
      "addl $4, %%esp\n\t"
      "cmpb $1, %%al\n\t"
      "movl 0x1c(%%ebx), %%eax\n\t"
      "jne .Lget_local_player_input_blob_111\n\t"
      "orl $0x10, %%eax\n\t"
      "jmp .Lget_local_player_input_blob_112\n\t"
      ".Lget_local_player_input_blob_111:\n\t"
      "andl $0xffffffef, %%eax\n\t"
      ".Lget_local_player_input_blob_112:\n\t"
      "pushl $0x29\n\t"
      "movl %%eax, 0x1c(%%ebx)\n\t"
      "call *%[ccf560]\n\t"
      "addl $4, %%esp\n\t"
      "cmpb $1, %%al\n\t"
      "movl 0x1c(%%ebx), %%eax\n\t"
      "jne .Lget_local_player_input_blob_113\n\t"
      "orl $0x20, %%eax\n\t"
      "jmp .Lget_local_player_input_blob_114\n\t"
      ".Lget_local_player_input_blob_113:\n\t"
      "andl $0xffffffdf, %%eax\n\t"
      ".Lget_local_player_input_blob_114:\n\t"
      "pushl $0x11\n\t"
      "movl %%eax, 0x1c(%%ebx)\n\t"
      "call *%[ccf560]\n\t"
      "addl $4, %%esp\n\t"
      "cmpb $1, %%al\n\t"
      "movl 0x18(%%ebx), %%eax\n\t"
      "jne .Lget_local_player_input_blob_115\n\t"
      "orl $4, %%eax\n\t"
      "jmp .Lget_local_player_input_blob_116\n\t"
      ".Lget_local_player_input_blob_115:\n\t"
      "andl $0xfffffffb, %%eax\n\t"
      ".Lget_local_player_input_blob_116:\n\t"
      "pushl $0x12\n\t"
      "movl %%eax, 0x18(%%ebx)\n\t"
      "call *%[ccf560]\n\t"
      "addl $4, %%esp\n\t"
      "cmpb $1, %%al\n\t"
      "movl 0x18(%%ebx), %%eax\n\t"
      "jne .Lget_local_player_input_blob_117\n\t"
      "orl %%edi, %%eax\n\t"
      "jmp .Lget_local_player_input_blob_118\n\t"
      ".Lget_local_player_input_blob_117:\n\t"
      "andl %%esi, %%eax\n\t"
      ".Lget_local_player_input_blob_118:\n\t"
      "flds 0x4(%%ebx)\n\t"
      "movl %%eax, 0x18(%%ebx)\n\t"
      "flds (%%ebx)\n\t"
      "popl %%edi\n\t"
      "fld %%st(1)\n\t"
      ".byte 0xde, 0xca\n\t"
      "fld %%st(0)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      ".byte 0xde, 0xc2\n\t"
      "fstp %%st(0)\n\t"
      "fcoms 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lget_local_player_input_blob_119\n\t"
      "fsqrt\n\t"
      "fdivrs 0x2533c8\n\t"
      "fld %%st(0)\n\t"
      "fmuls (%%ebx)\n\t"
      "fstps (%%ebx)\n\t"
      "fmuls 0x4(%%ebx)\n\t"
      "fstps 0x4(%%ebx)\n\t"
      "jmp .Lget_local_player_input_blob_120\n\t"
      ".Lget_local_player_input_blob_119:\n\t"
      "fstp %%st(0)\n\t"
      ".Lget_local_player_input_blob_120:\n\t"
      "movl %%ebx, %%esi\n\t"
      "call *%[cb6bd0]\n\t"
      "movl 0x8(%%ebx), %%eax\n\t"
      "movl %%eax, %%ecx\n\t"
      "andl $0x7f800000, %%ecx\n\t"
      "cmpl $0x7f800000, %%ecx\n\t"
      "movl %%eax, -0x38(%%ebp)\n\t"
      "popl %%esi\n\t"
      "jne .Lget_local_player_input_blob_121\n\t"
      "flds 0x8(%%ebx)\n\t"
      "pushl $1\n\t"
      "pushl $0x2b6\n\t"
      "pushl $0x26e1e8\n\t"
      "subl $8, %%esp\n\t"
      "fstpl (%%esp)\n\t"
      "movl %%eax, %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x26e2d0\n\t"
      "pushl $0x25eb8c\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x18, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lget_local_player_input_blob_121:\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [cba3c0] "m"(bb70b0_cba3c0), [memset] "m"(bb70b0_memset), [cb6380] "m"(bb70b0_cb6380), [dget] "m"(bb70b0_dget), [ccf6c0] "m"(bb70b0_ccf6c0), [c18e450] "m"(bb70b0_c18e450), [elem] "m"(bb70b0_elem), [ccf710] "m"(bb70b0_ccf710), [cce7f0] "m"(bb70b0_cce7f0), [get] "m"(bb70b0_get), [tag] "m"(bb70b0_tag), [cb5c30] "m"(bb70b0_cb5c30), [assert] "m"(bb70b0_assert), [exitfn] "m"(bb70b0_exitfn), [cb64c0] "m"(bb70b0_cb64c0), [c1b1350] "m"(bb70b0_c1b1350), [ca6470] "m"(bb70b0_ca6470), [cb5cc0] "m"(bb70b0_cb5cc0), [ca7430] "m"(bb70b0_ca7430), [tryget] "m"(bb70b0_tryget), [ccf690] "m"(bb70b0_ccf690), [ccf560] "m"(bb70b0_ccf560), [cb6bd0] "m"(bb70b0_cb6bd0), [c8d9d0] "m"(bb70b0_c8d9d0)
      : "memory");
}
#else
#error "get_local_player_input_blob: clang naked draft required"
#endif



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
