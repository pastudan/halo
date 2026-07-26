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

/* evaluate_piecewise_linear_function (0xb64c0) — XBE naked draft (batch 129). */
#if defined(__clang__)
static void (*const bb64c0_ftol)(void) = FUN_001d9068;
static void (*const bb64c0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const bb64c0_exitfn)(int) = system_exit;

__attribute__((naked, noinline))
float evaluate_piecewise_linear_function(int16_t count __attribute__((unused)), float *table __attribute__((unused)), float t __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xc, %%esp\n\t"
      "flds 0x10(%%ebp)\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .Levaluate_piecewise_linear_function_1\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      ".Levaluate_piecewise_linear_function_1:\n\t"
      "movswl 0x8(%%ebp), %%eax\n\t"
      "flds 0x10(%%ebp)\n\t"
      "pushl %%ebx\n\t"
      "fabs\n\t"
      "pushl %%esi\n\t"
      "leal -0x1(%%eax), %%esi\n\t"
      "movl %%esi, -0x8(%%ebp)\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "pushl %%edi\n\t"
      "fimull -0x8(%%ebp)\n\t"
      "fcoml 0x2602c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Levaluate_piecewise_linear_function_2\n\t"
      "fstp %%st(0)\n\t"
      "fldl 0x2602c0\n\t"
      "jmp .Levaluate_piecewise_linear_function_3\n\t"
      ".Levaluate_piecewise_linear_function_2:\n\t"
      "fildl -0xc(%%ebp)\n\t"
      "fsubs 0x2533c8\n\t"
      "fsts 0x10(%%ebp)\n\t"
      "fld %%st(1)\n\t"
      "fcompp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Levaluate_piecewise_linear_function_3\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x10(%%ebp)\n\t"
      ".Levaluate_piecewise_linear_function_3:\n\t"
      "fsts 0x10(%%ebp)\n\t"
      "call *%[ftol]\n\t"
      "testw %%ax, %%ax\n\t"
      "jge .Levaluate_piecewise_linear_function_4\n\t"
      "xorl %%eax, %%eax\n\t"
      "jmp .Levaluate_piecewise_linear_function_5\n\t"
      ".Levaluate_piecewise_linear_function_4:\n\t"
      "movswl %%ax, %%eax\n\t"
      "cmpl %%esi, %%eax\n\t"
      "jle .Levaluate_piecewise_linear_function_5\n\t"
      "movl %%esi, %%eax\n\t"
      ".Levaluate_piecewise_linear_function_5:\n\t"
      "movswl %%ax, %%edi\n\t"
      "leal 0x1(%%edi), %%ebx\n\t"
      "cmpl %%esi, %%ebx\n\t"
      "movl %%edi, -0xc(%%ebp)\n\t"
      "jle .Levaluate_piecewise_linear_function_6\n\t"
      "movl %%esi, %%ebx\n\t"
      ".Levaluate_piecewise_linear_function_6:\n\t"
      "movl 0xc(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .Levaluate_piecewise_linear_function_7\n\t"
      "testw %%ax, %%ax\n\t"
      "jl .Levaluate_piecewise_linear_function_7\n\t"
      "cmpw %%bx, %%ax\n\t"
      "jg .Levaluate_piecewise_linear_function_7\n\t"
      "cmpw 0x8(%%ebp), %%bx\n\t"
      "jl .Levaluate_piecewise_linear_function_8\n\t"
      ".Levaluate_piecewise_linear_function_7:\n\t"
      "pushl $1\n\t"
      "pushl $0x14b\n\t"
      "pushl $0x26e1e8\n\t"
      "pushl $0x26e228\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Levaluate_piecewise_linear_function_8:\n\t"
      "movswl %%bx, %%eax\n\t"
      "flds (%%esi,%%eax,4)\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "fsubs (%%esi,%%edi,4)\n\t"
      "fildl -0xc(%%ebp)\n\t"
      "fsubrs 0x10(%%ebp)\n\t"
      ".byte 0xde, 0xc9\n\t"
      "fadds (%%esi,%%edi,4)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "je .Levaluate_piecewise_linear_function_9\n\t"
      "fchs\n\t"
      ".Levaluate_piecewise_linear_function_9:\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [ftol] "m"(bb64c0_ftol), [assert] "m"(bb64c0_assert), [exitfn] "m"(bb64c0_exitfn)
      : "memory");
}
#else
#error "evaluate_piecewise_linear_function: clang naked draft required"
#endif


/* player_control_get_unit_index (0xb6870) — XBE naked draft (batch 97). */
#if defined(__clang__)
static void (*const bb6870_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const bb6870_exitfn)(int) = system_exit;

__attribute__((naked, noinline))
int player_control_get_unit_index(int16_t local_player_index __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%esi\n\t"
      "movw 0x8(%%ebp), %%si\n\t"
      "testw %%si, %%si\n\t"
      "jl .Lplayer_control_get_unit_index_1\n\t"
      "cmpw $4, %%si\n\t"
      "jl .Lplayer_control_get_unit_index_2\n\t"
      ".Lplayer_control_get_unit_index_1:\n\t"
      "pushl $1\n\t"
      "pushl $0xb1\n\t"
      "pushl $0x26e1e8\n\t"
      "pushl $0x266fc0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lplayer_control_get_unit_index_2:\n\t"
      "movl 0x457090, %%ecx\n\t"
      "movswl %%si, %%eax\n\t"
      "shll $6, %%eax\n\t"
      "movl 0x10(%%eax,%%ecx,1), %%eax\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(bb6870_assert), [exitfn] "m"(bb6870_exitfn)
      : "memory");
}
#else
#error "player_control_get_unit_index: clang naked draft required"
#endif


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

/* FUN_000b7f90 (0xb7f90) — XBE naked draft (batch 105). */
#if defined(__clang__)
static void (*const bb7f90_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const bb7f90_exitfn)(int) = system_exit;
static void * (*const bb7f90_c18e450)(void) = game_globals_get;
static void *(*const bb7f90_elem)(void *, int, int) = tag_block_get_element;
static void (*const bb7f90_cb6740)(int16_t local_player_index, void *out_info) = player_control_get_unit_camera_info;
static void *(*const bb7f90_get)(int, int) = object_get_and_verify_type;
static void *(*const bb7f90_tag)(int, int) = tag_get;
static short (*const bb7f90_markers)(int, void *, void *, int) = object_get_markers_by_string_id;
static void (*const bb7f90_c10cc00)(float *out_angles, float *in_vector) = vector_to_angles;
static void (*const bb7f90_c10cc40)(float *out, float *angles) = angles_to_vector;
static float (*const bb7f90_c10c510)(float *v1, float *v2) = FUN_0010c510;
static char * (*const bb7f90_c8d9d0)(char *buffer, const char *format, ...) = csprintf;
static void (*const bb7f90_cb6e60)(float *value, float target, float max_delta) = interpolate_scalar;

__attribute__((naked, noinline))
void FUN_000b7f90(int16_t local_player_index __attribute__((unused)), float dx __attribute__((unused)), float dy __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xb0, %%esp\n\t"
      "pushl %%ebx\n\t"
      "movl %%eax, %%ebx\n\t"
      "testw %%bx, %%bx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "jl .LFUN_000b7f90_1\n\t"
      "cmpw $4, %%bx\n\t"
      "jl .LFUN_000b7f90_2\n\t"
      ".LFUN_000b7f90_1:\n\t"
      "pushl $1\n\t"
      "pushl $0xb1\n\t"
      "pushl $0x26e1e8\n\t"
      "pushl $0x266fc0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000b7f90_2:\n\t"
      "movl 0x457090, %%ecx\n\t"
      "movswl %%bx, %%eax\n\t"
      "shll $6, %%eax\n\t"
      "pushl $0x80\n\t"
      "pushl $0\n\t"
      "leal 0x10(%%eax,%%ecx,1), %%edi\n\t"
      "call *%[c18e450]\n\t"
      "addl $0x110, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl 0x10(%%edi), %%edx\n\t"
      "leal 0x10(%%edi), %%esi\n\t"
      "movl %%eax, -0x20(%%ebp)\n\t"
      "movl %%edx, %%eax\n\t"
      "andl $0x7f800000, %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl $0x7f800000, %%eax\n\t"
      "movl $0xbfbf0243, -0x8(%%ebp)\n\t"
      "movl $0x3fbf0243, -0xc(%%ebp)\n\t"
      "movl %%edx, -0x10(%%ebp)\n\t"
      "je .LFUN_000b7f90_3\n\t"
      "flds (%%esi)\n\t"
      "fcomps 0x26e37c\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .LFUN_000b7f90_3\n\t"
      "flds (%%esi)\n\t"
      "fcomps 0x26e378\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_000b7f90_3\n\t"
      "movl 0xc(%%edi), %%ecx\n\t"
      "movl %%ecx, %%edx\n\t"
      "andl $0x7f800000, %%edx\n\t"
      "cmpl $0x7f800000, %%edx\n\t"
      "movl %%ecx, -0x10(%%ebp)\n\t"
      "je .LFUN_000b7f90_3\n\t"
      "flds 0xc(%%edi)\n\t"
      "fcomps 0x255a54\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .LFUN_000b7f90_3\n\t"
      "flds 0xc(%%edi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "je .LFUN_000b7f90_4\n\t"
      ".LFUN_000b7f90_3:\n\t"
      "pushl $1\n\t"
      "pushl $0x494\n\t"
      "pushl $0x26e1e8\n\t"
      "pushl $0x26e348\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000b7f90_4:\n\t"
      "leal -0x38(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "call *%[cb6740]\n\t"
      "flds 0x8(%%ebp)\n\t"
      "fadds 0xc(%%edi)\n\t"
      "addl $8, %%esp\n\t"
      "fstps 0xc(%%edi)\n\t"
      "cmpw $-1, -0x34(%%ebp)\n\t"
      "je .LFUN_000b7f90_17\n\t"
      "movl -0x38(%%ebp), %%ecx\n\t"
      "pushl $3\n\t"
      "pushl %%ecx\n\t"
      "call *%[get]\n\t"
      "movl (%%eax), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x756e6974\n\t"
      "call *%[tag]\n\t"
      "movswl -0x34(%%ebp), %%ecx\n\t"
      "pushl $0x11c\n\t"
      "pushl %%ecx\n\t"
      "addl $0x2e4, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl %%eax, %%ebx\n\t"
      "addl $0x1c, %%esp\n\t"
      "flds 0xf0(%%ebx)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .LFUN_000b7f90_5\n\t"
      "flds 0xf4(%%ebx)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .LFUN_000b7f90_17\n\t"
      ".LFUN_000b7f90_5:\n\t"
      "movl -0x38(%%ebp), %%ecx\n\t"
      "pushl $1\n\t"
      "leal -0xb0(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal 0x24(%%ebx), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[markers]\n\t"
      "leal -0x74(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x14(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c10cc00]\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fadds 0xf0(%%ebx)\n\t"
      "addl $0x18, %%esp\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fadds 0xf4(%%ebx)\n\t"
      "fsts -0x10(%%ebp)\n\t"
      "fsubs -0x18(%%ebp)\n\t"
      "fcoms 0x256980\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_000b7f90_6\n\t"
      "fsubs 0x255a54\n\t"
      ".LFUN_000b7f90_6:\n\t"
      "fcoms 0x26e280\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .LFUN_000b7f90_7\n\t"
      "fadds 0x255a54\n\t"
      ".LFUN_000b7f90_7:\n\t"
      "fsts -0x1c(%%ebp)\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fsubs 0xc(%%edi)\n\t"
      "fsts -0x4(%%ebp)\n\t"
      "fcomps 0x256980\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_000b7f90_8\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fsubs 0x255a54\n\t"
      "fstps -0x4(%%ebp)\n\t"
      ".LFUN_000b7f90_8:\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fcomps 0x26e280\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .LFUN_000b7f90_9\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fadds 0x255a54\n\t"
      "fstps -0x4(%%ebp)\n\t"
      ".LFUN_000b7f90_9:\n\t"
      "flds 0xc(%%edi)\n\t"
      "fsubs -0x18(%%ebp)\n\t"
      "fsts 0x8(%%ebp)\n\t"
      "fcomps 0x256980\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_000b7f90_10\n\t"
      "flds 0x8(%%ebp)\n\t"
      "fsubs 0x255a54\n\t"
      "fstps 0x8(%%ebp)\n\t"
      ".LFUN_000b7f90_10:\n\t"
      "flds 0x8(%%ebp)\n\t"
      "fcomps 0x26e280\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .LFUN_000b7f90_11\n\t"
      "flds 0x8(%%ebp)\n\t"
      "fadds 0x255a54\n\t"
      "fstps 0x8(%%ebp)\n\t"
      ".LFUN_000b7f90_11:\n\t"
      "fcoms 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_000b7f90_12\n\t"
      "fadds 0x255a54\n\t"
      "fstps -0x1c(%%ebp)\n\t"
      "jmp .LFUN_000b7f90_13\n\t"
      ".LFUN_000b7f90_12:\n\t"
      "fstp %%st(0)\n\t"
      ".LFUN_000b7f90_13:\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_000b7f90_14\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fcomps -0x1c(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .LFUN_000b7f90_17\n\t"
      ".LFUN_000b7f90_14:\n\t"
      "flds 0x8(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_000b7f90_15\n\t"
      "flds 0x8(%%ebp)\n\t"
      "fcomps -0x1c(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .LFUN_000b7f90_17\n\t"
      ".LFUN_000b7f90_15:\n\t"
      "flds 0x8(%%ebp)\n\t"
      "fabs\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fabs\n\t"
      "fcompp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_000b7f90_16\n\t"
      "movl -0x18(%%ebp), %%ecx\n\t"
      "movl %%ecx, 0xc(%%edi)\n\t"
      "jmp .LFUN_000b7f90_17\n\t"
      ".LFUN_000b7f90_16:\n\t"
      "movl -0x10(%%ebp), %%edx\n\t"
      "movl %%edx, 0xc(%%edi)\n\t"
      ".LFUN_000b7f90_17:\n\t"
      "flds 0xc(%%edi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_000b7f90_19\n\t"
      "flds 0xc(%%edi)\n\t"
      "leal (%%ebx), %%ebx\n\t"
      ".LFUN_000b7f90_18:\n\t"
      "fadds 0x255a54\n\t"
      "fcoms 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .LFUN_000b7f90_18\n\t"
      "fstps 0xc(%%edi)\n\t"
      ".LFUN_000b7f90_19:\n\t"
      "flds 0xc(%%edi)\n\t"
      "fcomps 0x255a54\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_000b7f90_21\n\t"
      "flds 0xc(%%edi)\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_000b7f90_20:\n\t"
      "fsubs 0x255a54\n\t"
      "fcoms 0x255a54\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .LFUN_000b7f90_20\n\t"
      "fstps 0xc(%%edi)\n\t"
      ".LFUN_000b7f90_21:\n\t"
      "movl -0x30(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_000b7f90_32\n\t"
      "movl -0x38(%%ebp), %%eax\n\t"
      "pushl $3\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl -0x30(%%ebp), %%ecx\n\t"
      "flds 0x48(%%ecx)\n\t"
      "movl 0x40(%%ecx), %%edx\n\t"
      "fcomps 0x2533c0\n\t"
      "movl %%eax, %%ebx\n\t"
      "addl $8, %%esp\n\t"
      "movl %%edx, 0x8(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .LFUN_000b7f90_22\n\t"
      "flds 0x44(%%ecx)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .LFUN_000b7f90_27\n\t"
      ".LFUN_000b7f90_22:\n\t"
      "cmpw $-1, -0x34(%%ebp)\n\t"
      "movl 0x44(%%ecx), %%eax\n\t"
      "movl 0x48(%%ecx), %%ecx\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "movl %%ecx, -0xc(%%ebp)\n\t"
      "je .LFUN_000b7f90_23\n\t"
      "flds 0x38(%%ebx)\n\t"
      "fcomps 0x2549d4\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_000b7f90_23\n\t"
      "movl 0xc(%%edi), %%edx\n\t"
      "leal -0x14(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x44(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl %%edx, -0x14(%%ebp)\n\t"
      "movl $0, -0x10(%%ebp)\n\t"
      "call *%[c10cc40]\n\t"
      "leal 0x30(%%ebx), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x44(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c10c510]\n\t"
      "fsubrs 0x2568bc\n\t"
      "flds -0x8(%%ebp)\n\t"
      "addl $0x10, %%esp\n\t"
      ".byte 0xd8, 0xe1\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "flds -0xc(%%ebp)\n\t"
      ".byte 0xd8, 0xe1\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "flds 0x8(%%ebp)\n\t"
      ".byte 0xd8, 0xe1\n\t"
      "fstps 0x8(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      ".LFUN_000b7f90_23:\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fcomps 0x26e378\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_000b7f90_24\n\t"
      "movl $0xbfbf0243, -0x8(%%ebp)\n\t"
      "jmp .LFUN_000b7f90_25\n\t"
      ".LFUN_000b7f90_24:\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fcomps 0x26e37c\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_000b7f90_25\n\t"
      "movl $0x3fbf0243, -0x8(%%ebp)\n\t"
      ".LFUN_000b7f90_25:\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fcomps 0x26e378\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_000b7f90_26\n\t"
      "movl $0xbfbf0243, -0xc(%%ebp)\n\t"
      "jmp .LFUN_000b7f90_27\n\t"
      ".LFUN_000b7f90_26:\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fcomps 0x26e37c\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_000b7f90_27\n\t"
      "movl $0x3fbf0243, -0xc(%%ebp)\n\t"
      ".LFUN_000b7f90_27:\n\t"
      "flds 0x8(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .LFUN_000b7f90_28\n\t"
      "movb 0x26(%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000b7f90_32\n\t"
      ".LFUN_000b7f90_28:\n\t"
      "flds (%%esi)\n\t"
      "movl (%%esi), %%ecx\n\t"
      "fsubs 0x8(%%ebp)\n\t"
      "movl %%ecx, %%edx\n\t"
      "andl $0x7f800000, %%edx\n\t"
      "cmpl $0x7f800000, %%edx\n\t"
      "fabs\n\t"
      "movl %%ecx, -0x18(%%ebp)\n\t"
      "fmull 0x26e3b0\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "jne .LFUN_000b7f90_29\n\t"
      "flds (%%esi)\n\t"
      "pushl $1\n\t"
      "pushl $0x4f2\n\t"
      "pushl $0x26e1e8\n\t"
      "subl $8, %%esp\n\t"
      "fstpl (%%esp)\n\t"
      "movl %%ecx, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x26e38c\n\t"
      "pushl $0x25eb8c\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x18, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000b7f90_29:\n\t"
      "flds 0x8(%%ebp)\n\t"
      "pushl %%ecx\n\t"
      "fcomps 0x2533c0\n\t"
      "flds 0x20(%%ebx)\n\t"
      "flds 0x1c(%%ebx)\n\t"
      "flds 0x18(%%ebx)\n\t"
      "fld %%st(0)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fld %%st(2)\n\t"
      ".byte 0xd8, 0xcb\n\t"
      "fnstsw %%ax\n\t"
      ".byte 0xde, 0xc1\n\t"
      "testb $0x44, %%ah\n\t"
      "fld %%st(3)\n\t"
      ".byte 0xd8, 0xcc\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fsqrt\n\t"
      "fstp %%st(3)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "jnp .LFUN_000b7f90_30\n\t"
      "fmuls -0x10(%%ebp)\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "fmuls 0x26e388\n\t"
      "fstps (%%esp)\n\t"
      "pushl %%ecx\n\t"
      "jmp .LFUN_000b7f90_31\n\t"
      ".LFUN_000b7f90_30:\n\t"
      "movl -0x20(%%ebp), %%edx\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "fmuls 0x54(%%edx)\n\t"
      "fmuls -0x10(%%ebp)\n\t"
      "fstps (%%esp)\n\t"
      "pushl %%eax\n\t"
      ".LFUN_000b7f90_31:\n\t"
      "pushl %%esi\n\t"
      "call *%[cb6e60]\n\t"
      "movl (%%esi), %%ecx\n\t"
      "movl %%ecx, %%edx\n\t"
      "andl $0x7f800000, %%edx\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl $0x7f800000, %%edx\n\t"
      "movl %%ecx, 0x8(%%ebp)\n\t"
      "jne .LFUN_000b7f90_32\n\t"
      "flds (%%esi)\n\t"
      "pushl $1\n\t"
      "pushl $0x4fd\n\t"
      "pushl $0x26e1e8\n\t"
      "subl $8, %%esp\n\t"
      "fstpl (%%esp)\n\t"
      "movl %%ecx, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x26e38c\n\t"
      "pushl $0x25eb8c\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x18, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000b7f90_32:\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fsubs 0x38(%%edi)\n\t"
      "fcoms 0x26e384\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_000b7f90_33\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x26e384\n\t"
      "jmp .LFUN_000b7f90_34\n\t"
      ".LFUN_000b7f90_33:\n\t"
      "fcoms 0x26e380\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_000b7f90_34\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x26e380\n\t"
      ".LFUN_000b7f90_34:\n\t"
      "fadds 0x38(%%edi)\n\t"
      "fstps 0x38(%%edi)\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fsubs 0x3c(%%edi)\n\t"
      "fcoms 0x26e384\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_000b7f90_35\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x26e384\n\t"
      "jmp .LFUN_000b7f90_36\n\t"
      ".LFUN_000b7f90_35:\n\t"
      "fcoms 0x26e380\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_000b7f90_36\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x26e380\n\t"
      ".LFUN_000b7f90_36:\n\t"
      "fadds 0x3c(%%edi)\n\t"
      "fstps 0x3c(%%edi)\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fadds (%%esi)\n\t"
      "fcoms 0x38(%%edi)\n\t"
      "fsts (%%esi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_000b7f90_37\n\t"
      "movl 0x38(%%edi), %%ecx\n\t"
      "fstp %%st(0)\n\t"
      "popl %%edi\n\t"
      "movl %%ecx, (%%esi)\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000b7f90_37:\n\t"
      "fcoms 0x3c(%%edi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_000b7f90_38\n\t"
      "movl 0x3c(%%edi), %%edx\n\t"
      "fstp %%st(0)\n\t"
      "popl %%edi\n\t"
      "movl %%edx, (%%esi)\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000b7f90_38:\n\t"
      "popl %%edi\n\t"
      "fstps (%%esi)\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(bb7f90_assert), [exitfn] "m"(bb7f90_exitfn), [c18e450] "m"(bb7f90_c18e450), [elem] "m"(bb7f90_elem), [cb6740] "m"(bb7f90_cb6740), [get] "m"(bb7f90_get), [tag] "m"(bb7f90_tag), [markers] "m"(bb7f90_markers), [c10cc00] "m"(bb7f90_c10cc00), [c10cc40] "m"(bb7f90_c10cc40), [c10c510] "m"(bb7f90_c10c510), [c8d9d0] "m"(bb7f90_c8d9d0), [cb6e60] "m"(bb7f90_cb6e60)
      : "memory");
}
#else
#error "FUN_000b7f90: clang naked draft required"
#endif


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

/* FUN_000b6bd0 (0xb6bd0) — XBE naked draft (batch 116). */
#if defined(__clang__)
static bool (*const bb6bd0_c92e60)(void) = cinematic_can_be_skipped;
static void (*const bb6bd0_c1002e0)(void) = main_skip_cinematic;

__attribute__((naked, noinline))
void FUN_000b6bd0(char *input __attribute__((unused)))
{
  __asm__ volatile(
      "movb 0x14(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000b6bd0_1\n\t"
      "call *%[c92e60]\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000b6bd0_1\n\t"
      "call *%[c1002e0]\n\t"
      ".LFUN_000b6bd0_1:\n\t"
      "testb $0x40, 0x18(%%esi)\n\t"
      "movl 0x457090, %%ecx\n\t"
      "je .LFUN_000b6bd0_2\n\t"
      "orl $1, (%%ecx)\n\t"
      ".LFUN_000b6bd0_2:\n\t"
      "testb $2, 0x18(%%esi)\n\t"
      "je .LFUN_000b6bd0_3\n\t"
      "orl $2, (%%ecx)\n\t"
      ".LFUN_000b6bd0_3:\n\t"
      "movb 0x14(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000b6bd0_4\n\t"
      "orl $4, (%%ecx)\n\t"
      ".LFUN_000b6bd0_4:\n\t"
      "movb 0x15(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000b6bd0_5\n\t"
      "orl $8, (%%ecx)\n\t"
      ".LFUN_000b6bd0_5:\n\t"
      "flds 0x8(%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_000b6bd0_6\n\t"
      "orl $0x10, (%%ecx)\n\t"
      ".LFUN_000b6bd0_6:\n\t"
      "movl 0x18(%%esi), %%eax\n\t"
      "testb $0x20, %%ah\n\t"
      "je .LFUN_000b6bd0_7\n\t"
      "orl $0x20, (%%ecx)\n\t"
      ".LFUN_000b6bd0_7:\n\t"
      "testb $4, 0x1c(%%esi)\n\t"
      "je .LFUN_000b6bd0_8\n\t"
      "orl $0x40, (%%ecx)\n\t"
      ".LFUN_000b6bd0_8:\n\t"
      "flds 0x10(%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_000b6bd0_9\n\t"
      "movl (%%ecx), %%eax\n\t"
      "orl $0x80, %%eax\n\t"
      "jmp .LFUN_000b6bd0_10\n\t"
      ".LFUN_000b6bd0_9:\n\t"
      "flds 0x10(%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_000b6bd0_11\n\t"
      "movl (%%ecx), %%eax\n\t"
      "orl $0x100, %%eax\n\t"
      ".LFUN_000b6bd0_10:\n\t"
      "movl %%eax, (%%ecx)\n\t"
      ".LFUN_000b6bd0_11:\n\t"
      "flds 0xc(%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_000b6bd0_12\n\t"
      "movl (%%ecx), %%eax\n\t"
      "orl $0x200, %%eax\n\t"
      "jmp .LFUN_000b6bd0_13\n\t"
      ".LFUN_000b6bd0_12:\n\t"
      "flds 0xc(%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_000b6bd0_14\n\t"
      "movl (%%ecx), %%eax\n\t"
      "orl $0x400, %%eax\n\t"
      ".LFUN_000b6bd0_13:\n\t"
      "movl %%eax, (%%ecx)\n\t"
      ".LFUN_000b6bd0_14:\n\t"
      "flds (%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_000b6bd0_15\n\t"
      "movl (%%ecx), %%eax\n\t"
      "orl $0x800, %%eax\n\t"
      "jmp .LFUN_000b6bd0_16\n\t"
      ".LFUN_000b6bd0_15:\n\t"
      "flds (%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_000b6bd0_17\n\t"
      "movl (%%ecx), %%eax\n\t"
      "orl $0x1000, %%eax\n\t"
      ".LFUN_000b6bd0_16:\n\t"
      "movl %%eax, (%%ecx)\n\t"
      ".LFUN_000b6bd0_17:\n\t"
      "flds 0x4(%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_000b6bd0_18\n\t"
      "movl (%%ecx), %%eax\n\t"
      "orl $0x2000, %%eax\n\t"
      "jmp .LFUN_000b6bd0_19\n\t"
      ".LFUN_000b6bd0_18:\n\t"
      "flds 0x4(%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_000b6bd0_20\n\t"
      "movl (%%ecx), %%eax\n\t"
      "orl $0x4000, %%eax\n\t"
      ".LFUN_000b6bd0_19:\n\t"
      "movl %%eax, (%%ecx)\n\t"
      ".LFUN_000b6bd0_20:\n\t"
      "testb $1, 0x4(%%ecx)\n\t"
      "movl $0xffffffbf, %%edx\n\t"
      "jne .LFUN_000b6bd0_23\n\t"
      "movl 0x8(%%ecx), %%eax\n\t"
      "testb $1, %%al\n\t"
      "je .LFUN_000b6bd0_24\n\t"
      "testb $0x40, 0x18(%%esi)\n\t"
      "je .LFUN_000b6bd0_21\n\t"
      "orl $1, %%eax\n\t"
      "jmp .LFUN_000b6bd0_22\n\t"
      ".LFUN_000b6bd0_21:\n\t"
      "andl $0xfffffffe, %%eax\n\t"
      ".LFUN_000b6bd0_22:\n\t"
      "movl %%eax, 0x8(%%ecx)\n\t"
      ".LFUN_000b6bd0_23:\n\t"
      "andl %%edx, 0x18(%%esi)\n\t"
      ".LFUN_000b6bd0_24:\n\t"
      "movb 0x2f0292, %%al\n\t"
      "testb %%al, %%al\n\t"
      "movb 0x4(%%ecx), %%al\n\t"
      "jne .LFUN_000b6bd0_31\n\t"
      "testb $4, %%al\n\t"
      "jne .LFUN_000b6bd0_27\n\t"
      "movl 0x8(%%ecx), %%eax\n\t"
      "testb $4, %%al\n\t"
      "je .LFUN_000b6bd0_28\n\t"
      "testb $0x40, 0x18(%%esi)\n\t"
      "je .LFUN_000b6bd0_25\n\t"
      "orl $4, %%eax\n\t"
      "jmp .LFUN_000b6bd0_26\n\t"
      ".LFUN_000b6bd0_25:\n\t"
      "andl $0xfffffffb, %%eax\n\t"
      ".LFUN_000b6bd0_26:\n\t"
      "movl %%eax, 0x8(%%ecx)\n\t"
      ".LFUN_000b6bd0_27:\n\t"
      "andl %%edx, 0x18(%%esi)\n\t"
      ".LFUN_000b6bd0_28:\n\t"
      "testb $8, 0x4(%%ecx)\n\t"
      "jne .LFUN_000b6bd0_30\n\t"
      "movl 0x8(%%ecx), %%eax\n\t"
      "testb $8, %%al\n\t"
      "je .LFUN_000b6bd0_38\n\t"
      "testb $1, 0x1c(%%esi)\n\t"
      "je .LFUN_000b6bd0_29\n\t"
      "orl $8, %%eax\n\t"
      "movl %%eax, 0x8(%%ecx)\n\t"
      "andl $0xfffffffe, 0x1c(%%esi)\n\t"
      "ret\n\t"
      ".LFUN_000b6bd0_29:\n\t"
      "andl $0xfffffff7, %%eax\n\t"
      "movl %%eax, 0x8(%%ecx)\n\t"
      ".LFUN_000b6bd0_30:\n\t"
      "andl $0xfffffffe, 0x1c(%%esi)\n\t"
      "ret\n\t"
      ".LFUN_000b6bd0_31:\n\t"
      "testb $4, %%al\n\t"
      "movl $0xfffffffd, %%edx\n\t"
      "jne .LFUN_000b6bd0_34\n\t"
      "movl 0x8(%%ecx), %%eax\n\t"
      "testb $4, %%al\n\t"
      "je .LFUN_000b6bd0_35\n\t"
      "testb $2, 0x18(%%esi)\n\t"
      "je .LFUN_000b6bd0_32\n\t"
      "orl $4, %%eax\n\t"
      "jmp .LFUN_000b6bd0_33\n\t"
      ".LFUN_000b6bd0_32:\n\t"
      "andl $0xfffffffb, %%eax\n\t"
      ".LFUN_000b6bd0_33:\n\t"
      "movl %%eax, 0x8(%%ecx)\n\t"
      ".LFUN_000b6bd0_34:\n\t"
      "andl %%edx, 0x18(%%esi)\n\t"
      ".LFUN_000b6bd0_35:\n\t"
      "testb $8, 0x4(%%ecx)\n\t"
      "jne .LFUN_000b6bd0_37\n\t"
      "movl 0x8(%%ecx), %%eax\n\t"
      "testb $4, %%al\n\t"
      "je .LFUN_000b6bd0_38\n\t"
      "testb $2, 0x1c(%%esi)\n\t"
      "je .LFUN_000b6bd0_36\n\t"
      "orl $4, %%eax\n\t"
      "movl %%eax, 0x8(%%ecx)\n\t"
      "andl %%edx, 0x1c(%%esi)\n\t"
      "ret\n\t"
      ".LFUN_000b6bd0_36:\n\t"
      "andl $0xfffffffb, %%eax\n\t"
      "movl %%eax, 0x8(%%ecx)\n\t"
      ".LFUN_000b6bd0_37:\n\t"
      "andl %%edx, 0x1c(%%esi)\n\t"
      ".LFUN_000b6bd0_38:\n\t"
      "ret\n\t"
      :
      : [c92e60] "m"(bb6bd0_c92e60), [c1002e0] "m"(bb6bd0_c1002e0)
      : "memory");
}
#else
#error "FUN_000b6bd0: clang naked draft required"
#endif


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
static float (*const bb70b0_cb64c0)(int16_t count, float *table, float t) = evaluate_piecewise_linear_function;
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
