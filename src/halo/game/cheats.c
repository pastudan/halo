#include "x87_math.h"
void cheats_initialize(void)
{
  csmemset(cheats_globals, 0, sizeof(cheats_globals));
}

void cheats_dispose(void)
{
}

void cheats_dispose_from_old_map(void)
{
}

void cheats_update(void)
{
  int16_t player_index;
  void *gamepad;
  char *cheat;
  char *btn;
  int cnt;

  if (!cheat_controller)
    return;

  player_index = (int16_t)local_player_get_next(-1);
  while (player_index != -1) {
    gamepad = input_get_gamepad_state(player_index);
    if (gamepad != NULL && *(char *)((char *)gamepad + 0x1d)) {
      cheat = cheats_globals;
      btn = (char *)gamepad + 0x10;
      cnt = 0x10;
      do {
        if (*cheat != '\0' && *btn != '\0') {
          director_set_local_player_context(player_index);
          if (*btn == '\x01') {
            console_printf(0, cheat);
            if (!hs_console_evaluate(cheat))
              *cheat = '\0';
          }
        }
        btn++;
        cheat += 0xc8;
        cnt--;
      } while (cnt != 0);
    }
    player_index = (int16_t)local_player_get_next(player_index);
  }
}

void cheats_load_from_file(void)
{
  void *stream;
  int16_t slot;
  char *entry;

  stream = crt_fopen("d:\\cheats.txt", "r");
  if (stream == NULL)
    return;

  for (slot = 0; slot < 16; slot++) {
    entry = cheats_globals + (int)slot * 200;
    if (crt_fgets(entry, 199, stream) == NULL)
      break;
    csstrtok(entry, "\r\n\t;");
    if ((slot == 12 || slot == 13) && *entry != '\0') {
      *entry = '\0';
      error(2, "Cannot execute cheats attached to the back or start button");
    }
  }
  crt_fclose(stream);
}

/* cheat_active_camouflage_local_player — give weapon infinite ammo cheat for
 * one local player. Finds the player's primary weapon, sets its vitality
 * to 1.0f (full), and sets bit 4 (+optionally bit 5) in the weapon's flags at
 * +0x1b4. Source: cheats.c, local_player_index in [0,3].
 */
void cheat_active_camouflage_local_player(int local_player_index)
{
  int player_handle;
  char *player;
  char *weapon;
  unsigned int flags;

  if ((short)local_player_index < 0 || (short)local_player_index >= 4)
    return;
  player_handle = local_player_get_player_index((int16_t)local_player_index);
  if (player_handle == -1)
    return;
  player = (char *)datum_get(player_data, player_handle);
  weapon = (char *)object_get_and_verify_type(*(int *)(player + 0x34), 3);
  *(unsigned int *)(weapon + 0x32c) = 0x3f800000;
  flags = *(unsigned int *)(weapon + 0x1b4);
  if (flags & 0x10)
    *(unsigned int *)(weapon + 0x1b4) = flags | 0x20;
  *(unsigned int *)(weapon + 0x1b4) |= 0x10;
}

/* FUN_000a67c0 — find the first player datum that has a weapon equipped.
 * Returns the datum handle of the player, or -1 if none found.
 * The datum handle is stored in the iterator at offset 8 (data_iter_t.datum).
 */
int FUN_000a67c0(void)
{
  data_iter_t iter;
  char *player;

  data_iterator_new(&iter, player_data);
  player = (char *)data_iterator_next(&iter);
  while (player != NULL) {
    if (*(int *)(player + 0x34) != -1)
      return *(int *)((char *)&iter + 8);
    player = (char *)data_iterator_next(&iter);
  }
  return -1;
}

void cheats_initialize_for_new_map(void)
{
  cheats_load_from_file();
}

/* cheat_teleport_to_camera — teleport cheat: move a player's vehicle/weapon to
 * the camera. Finds a player with a weapon (via FUN_000a67c0), then teleports
 * the vehicle (or weapon if not in a vehicle) to the camera position using
 * object_set_position. Frameless in the original binary.
 */
typedef void (*terminal_output_2_t)(void *, const char *);

void cheat_teleport_to_camera(void)
{
  int player_handle;
  char *player;
  short local_player_idx;
  char *camera;
  char *weapon_obj;
  int object_handle;

  player_handle = FUN_000a67c0();
  if (player_handle == -1)
    return;
  player = (char *)datum_get(player_data, player_handle);
  local_player_idx = *(short *)(player + 2);
  if (local_player_idx == (short)-1)
    return;
  camera = (char *)observer_get_camera((unsigned short)local_player_idx);
  if (!camera) {
    display_assert("result", "c:\\halo\\SOURCE\\game\\cheats.c", 0x100, 1);
    system_exit(-1);
  }
  if (*(short *)(camera + 0x10) != (short)-1) {
    weapon_obj = (char *)object_get_and_verify_type(*(int *)(player + 0x34), 3);
    object_handle = *(int *)(weapon_obj + 0xcc);
    if (object_handle == -1)
      object_handle = *(int *)(player + 0x34);
    object_set_position(object_handle, (float *)camera, NULL, NULL);
    return;
  }
  ((terminal_output_2_t)terminal_output)(
    *(void **)0x2ee6f0,
    "Camera is outside BSP... cannot initiate teleportation...");
}

/* cheat_all_powerups — give weapon infinite ammo for the first armed player.
 * Same weapon modification logic as cheat_active_camouflage_local_player but
 * targets the first player that has a weapon equipped (via FUN_000a67c0) rather
 * than a specific local index. Frameless in the original binary.
 */
void cheat_all_powerups(void)
{
  int player_handle;
  char *player;
  char *weapon;
  unsigned int flags;

  player_handle = FUN_000a67c0();
  if (player_handle == -1)
    return;
  player = (char *)datum_get(player_data, player_handle);
  weapon = (char *)object_get_and_verify_type(*(int *)(player + 0x34), 3);
  *(unsigned int *)(weapon + 0x32c) = 0x3f800000;
  flags = *(unsigned int *)(weapon + 0x1b4);
  if (flags & 0x10)
    *(unsigned int *)(weapon + 0x1b4) = flags | 0x20;
  *(unsigned int *)(weapon + 0x1b4) |= 0x10;
}
/* --- cheats.obj batch drafts (2026-07-26) --- */

/* FUN_000a54b0 (0xa54b0) — readable C lift from XBE leaf.
 * Cheat weather update: if cheat flags set and a weather slot is active,
 * refresh particle system for the current sky weather tag. */
void FUN_000a54b0(void)
{
  short slot;
  char *state;
  short sky_index;
  int weather_tag;
  int cur;
  char ok;

  if (!*(unsigned char *)0x32574c)
    return;
  if (!*(unsigned char *)0x2ef7ee)
    return;
  slot = *(short *)0x506548;
  if (slot == -1)
    return;

  state = (char *)FUN_000a3e60(slot);
  *(short *)(state + 0x14) = *(short *)0x506784;
  *(int *)(state + 0x10) = *(int *)0x506780;
  sky_index = -1;
  weather_tag = -1;
  ok = FUN_0018f3e0((void *)(state + 0x10), (void *)0x506550, (int16_t *)(state + 0x18));
  *(unsigned char *)(state + 0x1a) = ok;
  sky_index = *(short *)(state + 0x18);
  if (sky_index != -1) {
    void *scen = global_scenario_get();
    void *elem = tag_block_get_element((char *)scen + 0x1b4, sky_index, 0xf0);
    weather_tag = *(int *)((char *)elem + 0x2c);
  }
  cur = *(int *)state;
  if (cur != weather_tag) {
    if (cur != -1)
      ((void (*)(int))(void *)weather_particle_system_delete)((unsigned short)slot);
    if (weather_tag != -1)
      ((void (*)(int, int, float))(void *)weather_particle_system_new)(
          (unsigned short)slot, weather_tag, 1.0f);
  }
  if (*(int *)state != -1)
    weather_particle_system_render(slot);
}




/* FUN_000a5590 (0xa5590) — readable C lift. */
float FUN_000a5590(float x, float y)
{
  float half = y * *(float *)0x253398;
  if (!(x < y) && x == x && y == y) {
    return *(float *)0x2533c0;
  }
  if (x > half || x != x || half != half) {
    return (y - x) / (y - half);
  }
  return *(float *)0x2533c8;
}

/* FUN_000a55e0 (0xa55e0) — readable C lift. */
float FUN_000a55e0(float a, float b, float c, float d)
{
  return FUN_000a5590(a, b) * FUN_000a5590(c, d);
}

/* FUN_000a5610 (0xa5610) — readable C lift from XBE leaf.
 * unit@eax, out@ebx, zoom@stack. Note: XBE FPU stack leaves mag in ST for
 * out[1]/out[3] while out[0]/out[2]/out[4] use inv=const/mag. */
char FUN_000a5610(int unit_handle /*@<eax>*/, float *out /*@<ebx>*/, int16_t zoom_level)
{
  void *unit;
  int16_t weapon_index;
  int weapon_handle;
  void *weapon_obj;
  void *weap_tag;
  float mag;
  float inv;
  float a, b;

  if (unit_handle == -1)
    return 0;
  unit = object_get_and_verify_type(unit_handle, 3);
  weapon_index = *(int16_t *)((char *)unit + 0x2a2);
  weapon_handle = unit_get_weapon(unit_handle, weapon_index);
  if (weapon_handle == -1)
    return 0;
  weapon_obj = object_get_and_verify_type(weapon_handle, 4);
  weap_tag = tag_get(0x77656170, *(int *)weapon_obj);
  if (zoom_level == (int16_t)0xffff &&
      (*(unsigned char *)((char *)weap_tag + 0x308) & 0x20))
    return 0;
  mag = weapon_get_zoom_magnification(weapon_handle, zoom_level);
  inv = *(float *)0x2533c8 / mag;
  out[0] = inv * *(float *)((char *)weap_tag + 0x3e4);
  out[1] = mag * *(float *)((char *)weap_tag + 0x3e8);
  out[2] = inv * *(float *)((char *)weap_tag + 0x3ec);
  out[3] = mag * *(float *)((char *)weap_tag + 0x3f0);
  a = *(float *)((char *)weap_tag + 0x3f4);
  b = *(float *)((char *)weap_tag + 0x3e4);
  /* fcom 3f4 vs 3e4; test 0x41 → <= uses 3e4, else 3f4 */
  out[4] = inv * ((a <= b) ? b : a);
  return 1;
}





/* FUN_000a5700 (0xa5700) — readable C lift from XBE leaf. */
int FUN_000a5700(float *a, float *b)
{
  if (a[12] > b[12])
    return -1;
  if (a[12] < b[12])
    return 1;
  if (a[13] > b[13])
    return -1;
  if (a[13] < b[13])
    return 1;
  if (a[10] < b[10])
    return -1;
  if (a[10] > b[10])
    return 1;
  if (a[11] < b[11])
    return -1;
  if (a[11] > b[11])
    return 1;
  return (int)(*(unsigned int *)a & 0xffff) - (int)(*(unsigned int *)b & 0xffff);
}

/* FUN_000a57a0 (0xa57a0) — readable C lift: 1/sqrt(x). */
float FUN_000a57a0(float x)
{
  return *(float *)0x2533c8 / __builtin_sqrtf(x);
}

/* FUN_000a57b0 (0xa57b0) — readable C lift from XBE leaf. */
char FUN_000a57b0(float *vec, float max_length)
{
  float x = vec[0];
  float y = vec[1];
  float z = vec[2];
  float len2 = x * x + y * y + z * z;
  float max2 = max_length * max_length;

  if (len2 <= max2) {
    return 0;
  }
  {
    float scale = max_length / __builtin_sqrtf(len2);
    vec[0] = x * scale;
    vec[1] = y * scale;
    vec[2] = z * scale;
  }
  return 1;
}




/* FUN_000a5810 (0xa5810) — readable C lift. */
void FUN_000a5810(float *out, float value, int field0)
{
  out[1] = value;
  *(int *)out = field0;
}

/* FUN_000a5830 (0xa5830) — readable C lift. */
char FUN_000a5830(float *from, float *to, int object_handle, int other_handle)
{
  char ok;
  int root;
  float delta[3];
  short hit[0x2e]; /* 0x5c bytes */
  int hit_obj;
  int root_a;
  int root_b;

  ok = 0;
  if (*(short *)0x4761d8 >= 0x20) {
    display_assert((const char *)0x253440, (const char *)0x26b08c, 0x15e, 1);
    system_exit(-1);
  }
  {
    short idx = *(short *)0x4761d8;
    *(short *)(0x5a8c80 + idx * 2) = 6;
    *(short *)0x4761d8 = (short)(idx + 1);
  }
  root = object_get_root_parent(object_handle);
  delta[0] = to[0] - from[0];
  delta[1] = to[1] - from[1];
  delta[2] = to[2] - from[2];
  if (!FUN_0014df70(0xc2ad, from, delta, root, hit)) {
    ok = 1;
  } else if (hit[0] == 3) {
    hit_obj = *(int *)((char *)hit + 0x38); /* -0x24 - (-0x5c) = 0x38 */
    root_a = object_get_root_parent(hit_obj);
    root_b = object_get_root_parent(other_handle);
    if (root_a == root_b)
      ok = 1;
  }
  if (*(short *)0x4761d8 <= 1) {
    display_assert((const char *)0x253418, (const char *)0x26b08c, 0x16f, 1);
    system_exit(-1);
  }
  *(short *)0x4761d8 = (short)(*(short *)0x4761d8 - 1);
  return ok;
}

/* FUN_000a5920 (0xa5920) — readable C lift (restored pre-naked). */
void FUN_000a5920(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;

  biped_get_autoaim_pill(0, (float *)(uintptr_t)edx, (float *)(uintptr_t)ecx, (void *)(uintptr_t)eax);
  /* test (char)eax, 0x41 -> jne 0xa5a2a */
  /* test (char)eax, 0x41 -> jne 0xa5a0a */
  FUN_000a57b0((float *)0, 0.0f);

  (void)eax;
  (void)ecx;
  (void)edx;
}


/* FUN_000a5ac0 (0xa5ac0) — XBE naked draft (batch 119). */
#if defined(__clang__)
static void (*const ba5ac0_ca5920)(void) = (void *)FUN_000a5920;
static float (*const ba5ac0_norm)(float *) = normalize3d;
static void (*const ba5ac0_c1d94f0)(void) = (void *)FUN_001d94f0;
static void (*const ba5ac0_ca5590)(void) = (void (*)(void))(void *)&FUN_000a5590;
static void *(*const ba5ac0_get)(int, int) = object_get_and_verify_type;
static void *(*const ba5ac0_tag)(int, int) = tag_get;
static void * (*const ba5ac0_c18e450)(void) = game_globals_get;
static void *(*const ba5ac0_elem)(void *, int, int) = tag_block_get_element;

__attribute__((naked, noinline))
void FUN_000a5ac0(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "movl 0x18(%%ebp), %%eax\n\t"
      "pushl %%ebx\n\t"
      "movl 0x10(%%ebp), %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x14(%%ebp), %%esi\n\t"
      "pushl %%edi\n\t"
      "leal 0x4(%%eax), %%edi\n\t"
      "pushl %%ecx\n\t"
      "movl %%ecx, (%%eax)\n\t"
      "call *%[ca5920]\n\t"
      "flds (%%edi)\n\t"
      "fsubs (%%ebx)\n\t"
      "movl 0x18(%%ebp), %%esi\n\t"
      "fstps 0x10(%%esi)\n\t"
      "flds 0x4(%%edi)\n\t"
      "fsubs 0x4(%%ebx)\n\t"
      "fstps 0x14(%%esi)\n\t"
      "flds 0x8(%%edi)\n\t"
      "leal 0x1c(%%esi), %%edi\n\t"
      "fsubs 0x8(%%ebx)\n\t"
      "movl %%edi, %%eax\n\t"
      "pushl %%edi\n\t"
      "fstps 0x18(%%esi)\n\t"
      "movl 0x10(%%esi), %%ecx\n\t"
      "movl 0x14(%%esi), %%edx\n\t"
      "movl %%ecx, (%%eax)\n\t"
      "movl 0x18(%%esi), %%ecx\n\t"
      "movl %%edx, 0x4(%%eax)\n\t"
      "movl %%ecx, 0x8(%%eax)\n\t"
      "call *%[norm]\n\t"
      "fsts 0xc(%%ebp)\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "fstps 0x28(%%esi)\n\t"
      "flds 0x8(%%edi)\n\t"
      "addl $8, %%esp\n\t"
      "fmuls 0x8(%%eax)\n\t"
      "flds 0x4(%%edi)\n\t"
      "fmuls 0x4(%%eax)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds (%%edi)\n\t"
      "fmuls (%%eax)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fcoms 0x255e94\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_000a5ac0_1\n\t"
      "fstp %%st(0)\n\t"
      "movl $0xbf800000, 0x18(%%ebp)\n\t"
      "jmp .LFUN_000a5ac0_3\n\t"
      ".LFUN_000a5ac0_1:\n\t"
      "fcoms 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_000a5ac0_2\n\t"
      "fstp %%st(0)\n\t"
      "movl $0x3f800000, 0x18(%%ebp)\n\t"
      "jmp .LFUN_000a5ac0_3\n\t"
      ".LFUN_000a5ac0_2:\n\t"
      "fstps 0x18(%%ebp)\n\t"
      ".LFUN_000a5ac0_3:\n\t"
      "flds 0x18(%%ebp)\n\t"
      "call *%[c1d94f0]\n\t"
      "fsts 0x18(%%ebp)\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "fstps 0x2c(%%esi)\n\t"
      "xorl %%eax, %%eax\n\t"
      "cmpl %%eax, %%edi\n\t"
      "je .LFUN_000a5ac0_4\n\t"
      "movl 0x4(%%edi), %%edx\n\t"
      "movl 0xc(%%ebp), %%ebx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ebx\n\t"
      "call *%[ca5590]\n\t"
      "fstps 0x14(%%ebp)\n\t"
      "movl (%%edi), %%eax\n\t"
      "movl 0x18(%%ebp), %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[ca5590]\n\t"
      "fmuls 0x14(%%ebp)\n\t"
      "fstps 0x30(%%esi)\n\t"
      "movl 0xc(%%edi), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ebx\n\t"
      "call *%[ca5590]\n\t"
      "fstps 0x14(%%ebp)\n\t"
      "movl 0x8(%%edi), %%eax\n\t"
      "movl 0x18(%%ebp), %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[ca5590]\n\t"
      "fmuls 0x14(%%ebp)\n\t"
      "addl $0x20, %%esp\n\t"
      "fsts 0x34(%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_000a5ac0_5\n\t"
      "movl (%%esi), %%edx\n\t"
      "pushl $3\n\t"
      "pushl %%edx\n\t"
      "call *%[get]\n\t"
      "movl (%%eax), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x756e6974\n\t"
      "call *%[tag]\n\t"
      "movl 0x17c(%%eax), %%ecx\n\t"
      "addl $0x10, %%esp\n\t"
      "testl $0x80000, %%ecx\n\t"
      "je .LFUN_000a5ac0_5\n\t"
      "pushl $0x80\n\t"
      "pushl $0\n\t"
      "call *%[c18e450]\n\t"
      "addl $0x110, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "flds 0x8(%%eax)\n\t"
      "fmuls 0x34(%%esi)\n\t"
      "addl $0xc, %%esp\n\t"
      "fstps 0x34(%%esi)\n\t"
      "jmp .LFUN_000a5ac0_5\n\t"
      ".LFUN_000a5ac0_4:\n\t"
      "movl %%eax, 0x30(%%esi)\n\t"
      "movl %%eax, 0x34(%%esi)\n\t"
      ".LFUN_000a5ac0_5:\n\t"
      "flds 0x30(%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .LFUN_000a5ac0_6\n\t"
      "flds 0x34(%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .LFUN_000a5ac0_6\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "xorl %%eax, %%eax\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000a5ac0_6:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl $1, %%eax\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [ca5920] "m"(ba5ac0_ca5920), [norm] "m"(ba5ac0_norm), [c1d94f0] "m"(ba5ac0_c1d94f0), [ca5590] "m"(ba5ac0_ca5590), [get] "m"(ba5ac0_get), [tag] "m"(ba5ac0_tag), [c18e450] "m"(ba5ac0_c18e450), [elem] "m"(ba5ac0_elem)
      : "memory");
}
#else
#error "FUN_000a5ac0: clang naked draft required"
#endif


/* FUN_000a5c60 (0xa5c60) — XBE naked draft (batch 126). */
#if defined(__clang__)
static void (*const ba5c60_ca5920)(void) = (void *)FUN_000a5920;
static void (*const ba5c60_ca5830)(void) = (void *)FUN_000a5830;
static float (*const ba5c60_norm)(float *) = normalize3d;
static void (*const ba5c60_c1d94f0)(void) = (void *)FUN_001d94f0;

__attribute__((naked, noinline))
void FUN_000a5c60(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $8, %%esp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%ebx\n\t"
      "movl 0xc(%%ebp), %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x10(%%ebp), %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x18(%%ebp), %%edi\n\t"
      "pushl %%eax\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "call *%[ca5920]\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "movl 0x14(%%ebp), %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "call *%[ca5830]\n\t"
      "addl $0x14, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000a5c60_3\n\t"
      "flds (%%edi)\n\t"
      "movl 0x1c(%%ebp), %%esi\n\t"
      "fsubs (%%ebx)\n\t"
      "pushl %%esi\n\t"
      "fstps (%%esi)\n\t"
      "flds 0x4(%%edi)\n\t"
      "fsubs 0x4(%%ebx)\n\t"
      "fstps 0x4(%%esi)\n\t"
      "flds 0x8(%%edi)\n\t"
      "fsubs 0x8(%%ebx)\n\t"
      "fstps 0x8(%%esi)\n\t"
      "call *%[norm]\n\t"
      "movl 0x20(%%ebp), %%eax\n\t"
      "fld %%st(0)\n\t"
      "fstps (%%eax)\n\t"
      "addl $4, %%esp\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .LFUN_000a5c60_3\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "flds 0x8(%%eax)\n\t"
      "fmuls 0x8(%%esi)\n\t"
      "flds 0x4(%%eax)\n\t"
      "fmuls 0x4(%%esi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds (%%eax)\n\t"
      "fmuls (%%esi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fcoms 0x255e94\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_000a5c60_1\n\t"
      "fstp %%st(0)\n\t"
      "movl $0xbf800000, -0x8(%%ebp)\n\t"
      "flds -0x8(%%ebp)\n\t"
      "call *%[c1d94f0]\n\t"
      "movl 0x24(%%ebp), %%ecx\n\t"
      "popl %%edi\n\t"
      "fstps (%%ecx)\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000a5c60_1:\n\t"
      "fcoms 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_000a5c60_2\n\t"
      "fstp %%st(0)\n\t"
      "movl $0x3f800000, -0x8(%%ebp)\n\t"
      "flds -0x8(%%ebp)\n\t"
      "call *%[c1d94f0]\n\t"
      "movl 0x24(%%ebp), %%ecx\n\t"
      "popl %%edi\n\t"
      "fstps (%%ecx)\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000a5c60_2:\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "flds -0x8(%%ebp)\n\t"
      "call *%[c1d94f0]\n\t"
      "movl 0x24(%%ebp), %%ecx\n\t"
      "popl %%edi\n\t"
      "fstps (%%ecx)\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000a5c60_3:\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [ca5920] "m"(ba5c60_ca5920), [ca5830] "m"(ba5c60_ca5830), [norm] "m"(ba5c60_norm), [c1d94f0] "m"(ba5c60_c1d94f0)
      : "memory");
}
#else
#error "FUN_000a5c60: clang naked draft required"
#endif


/* FUN_000a5d70 (0xa5d70) — readable C lift (restored pre-naked). */
void FUN_000a5d70(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  object_get_and_verify_type(0, 0);
  /* test (char)eax, 3 -> je 0xa5ed5 */
  /* relift: test byte ptr [esi + 4], 1 -> jne 0xa5ed5 */
  object_get_and_verify_type(0, 0);
  FUN_00110210((float *)(uintptr_t)ecx, 0.0f, (float *)(uintptr_t)edx, (float *)(uintptr_t)ecx, 0.0f, 0.0f, 0.0f);
  /* test (char)eax, (char)eax -> je 0xa5ed5 */
  /* test dl, 1 -> je 0xa5e88 */
  /* relift: test byte ptr [esi + 0xb6], 4 -> jne 0xa5e88 */
  /* relift: cmp edi, dword ptr [ebp + 0x24] -> je 0xa5e88 */
  game_allegiance_get_team_is_friendly(ecx, eax);
  /* test (char)eax, (char)eax -> je 0xa5e88 */
  tag_get('dpib', 0);
  /* test ecx, 0x200000 -> jne 0xa5e88 */
  FUN_000a5ac0();
  /* test (char)eax, (char)eax -> je 0xa5e88 */
  /* relift: cmp (int16_t)ebx, word ptr [ebp + 0x2c] -> jge 0xa5e88 */
  /* cmp eax, -1 -> je 0xa5ed5 */
  /* cmp (int16_t)ebx, (int16_t)ecx -> jge 0xa5ed5 */
  /* relift: tail-call FUN_000a5d70(); */
  /* cmp edi, -1 -> je 0xa5eea */
  /* relift: cmp (int16_t)ebx, word ptr [ebp + 0x2c] -> jl 0xa5d80 */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}


/* FUN_000a5f00 (0xa5f00) — readable C lift (restored pre-naked). */
void FUN_000a5f00(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int ebp = 0;

  FUN_001d90e0();
  /* test (char)eax, 0x41 -> jne 0xa5f26 */
  /* test (char)eax, 0x41 -> jne 0xa5f3c */
  /* test (char)eax, 0x41 -> jne 0xa601b */
  /* test (char)eax, 0x41 -> jne 0xa601b */
  structure_clusters_in_cone(edx, (float *)(uintptr_t)ecx, (float *)(uintptr_t)eax, 0.0f, 0.0f, 0.0f, 0, (void *)0);
  object_find_in_cluster(0, eax, (void *)(uintptr_t)edx, 2048, (void *)(uintptr_t)ecx);
  FUN_000a5d70();
  /* relift: cmp (int16_t)esi, word ptr [ebp + 0x1c] -> jge 0xa601d */
  /* relift: cmp (int16_t)ebx, word ptr [ebp - 0x10] -> jl 0xa5fc1 */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)ebp;
}


/* FUN_000a6030 (0xa6030) — XBE naked draft (batch 130). */
#if defined(__clang__)
static int (*const ba6030_c18e720)(int point) = FUN_0018e720;
static void * (*const ba6030_c18e3c0)(void) = global_scenario_get;
static void *(*const ba6030_elem)(void *, int, int) = tag_block_get_element;
static void (*const ba6030_ca5f00)(void) = (void *)FUN_000a5f00;
static void __cdecl (*const ba6030_c1d9260)(void *base, size_t nmemb, size_t size, int (__cdecl *compar)(const void *, const void *)) = qsort;
static void (*const ba6030_ca5830)(void) = (void *)FUN_000a5830;

__attribute__((naked, noinline))
void FUN_000a6030(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xe00, %%esp\n\t"
      "pushl %%ebx\n\t"
      "movl 0xc(%%ebp), %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "call *%[c18e720]\n\t"
      "addl $4, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_000a6030_2\n\t"
      "pushl $0x10\n\t"
      "pushl %%ebx\n\t"
      "call *%[c18e720]\n\t"
      "andl $0x7fffffff, %%eax\n\t"
      "addl $4, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[c18e3c0]\n\t"
      "addl $0xe0, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movw 0x8(%%eax), %%ax\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .LFUN_000a6030_2\n\t"
      "movl 0x18(%%ebp), %%edx\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "leal -0xe00(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      "pushl $0x40\n\t"
      "pushl %%edx\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "call *%[ca5f00]\n\t"
      "addl $0x1c, %%esp\n\t"
      "movl %%eax, %%edi\n\t"
      "testw %%di, %%di\n\t"
      "jle .LFUN_000a6030_2\n\t"
      "pushl $0xa5700\n\t"
      "movswl %%di, %%eax\n\t"
      "pushl $0x38\n\t"
      "pushl %%eax\n\t"
      "leal -0xe00(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1d9260]\n\t"
      "addl $0x10, %%esp\n\t"
      "xorl %%esi, %%esi\n\t"
      "testw %%di, %%di\n\t"
      "jle .LFUN_000a6030_2\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_000a6030_1:\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      "movswl %%si, %%eax\n\t"
      "imull $0x38, %%eax, %%eax\n\t"
      "movl -0xe00(%%ebp,%%eax,1), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ecx\n\t"
      "leal -0xdfc(%%ebp,%%eax,1), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ebx\n\t"
      "call *%[ca5830]\n\t"
      "addl $0x10, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_000a6030_3\n\t"
      "incl %%esi\n\t"
      "cmpw %%di, %%si\n\t"
      "jl .LFUN_000a6030_1\n\t"
      ".LFUN_000a6030_2:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000a6030_3:\n\t"
      "movl 0x1c(%%ebp), %%edi\n\t"
      "movswl %%si, %%esi\n\t"
      "imull $0x38, %%esi, %%esi\n\t"
      "leal -0xe00(%%ebp,%%esi,1), %%esi\n\t"
      "movl $0xe, %%ecx\n\t"
      "rep movsl\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c18e720] "m"(ba6030_c18e720), [c18e3c0] "m"(ba6030_c18e3c0), [elem] "m"(ba6030_elem), [ca5f00] "m"(ba6030_ca5f00), [c1d9260] "m"(ba6030_c1d9260), [ca5830] "m"(ba6030_ca5830)
      : "memory");
}
#else
#error "FUN_000a6030: clang naked draft required"
#endif


/* player_aim_projectile (0xa6130) — XBE naked draft (batch 225). */
#if defined(__clang__)
static void *(*const ba6130_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static int (*const ba6130_c1a9880)(int unit_index) = unit_get_aiming_unit_index;
static bool (*const ba6130_c21fb0)(float *v) = valid_real_normal3d;
static char * (*const ba6130_c8d9d0)(char *buffer, const char *format, ...) = csprintf;
static void (*const ba6130_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const ba6130_exitfn)(int) = system_exit;
static int16_t (*const ba6130_c1a8690)(int unit_handle) = unit_get_zoom_level;
static void (*const ba6130_ca5610)(void) = (void *)FUN_000a5610;
static void (*const ba6130_c86b80)(void) = (void *)director_camera_deterministic;
static void (*const ba6130_ca6030)(void) = (void *)FUN_000a6030;
static float (*const ba6130_norm)(float *) = normalize3d;
static void *(*const ba6130_get)(int, int) = object_get_and_verify_type;
static bool (*const ba6130_ray)(unsigned int, float *, float *, int, short *) = FUN_0014df70;
static void (*const ba6130_c10c780)(float *v1, float *v2, float t, float *out) = FUN_0010c780;
static char (*const ba6130_c10fed0)(float *normal, float *direction, float sin_half_angle, float cos_half_angle, float *result) = pin_normal_to_cone3d;
static int (*const ba6130_gtime)(void) = game_time_get;

__attribute__((naked, noinline))
int player_aim_projectile(int player_handle __attribute__((unused)), float *out_position __attribute__((unused)), float *aim_direction __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xbc, %%esp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl 0x5aa6d4, %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "movl $0xffffffff, -0x2c(%%ebp)\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x34(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c1a9880]\n\t"
      "movl 0x10(%%ebp), %%edi\n\t"
      "movl %%eax, %%ebx\n\t"
      "pushl %%edi\n\t"
      "movl %%ebx, -0x4(%%ebp)\n\t"
      "call *%[c21fb0]\n\t"
      "addl $0x10, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lplayer_aim_projectile_1\n\t"
      "flds 0x8(%%edi)\n\t"
      "pushl $1\n\t"
      "pushl $0x4d\n\t"
      "pushl $0x26b08c\n\t"
      "subl $0x18, %%esp\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds 0x4(%%edi)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds (%%edi)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x255554\n\t"
      "pushl $0x254a24\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x24, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lplayer_aim_projectile_1:\n\t"
      "cmpw $0x20, 0x4761d8\n\t"
      "jl .Lplayer_aim_projectile_2\n\t"
      "pushl $1\n\t"
      "pushl $0x4f\n\t"
      "pushl $0x26b08c\n\t"
      "pushl $0x253440\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lplayer_aim_projectile_2:\n\t"
      "movw 0x4761d8, %%ax\n\t"
      "movswl %%ax, %%ecx\n\t"
      "incw %%ax\n\t"
      "pushl %%ebx\n\t"
      "movw $6, 0x5a8c80(,%%ecx,2)\n\t"
      "movw %%ax, 0x4761d8\n\t"
      "call *%[c1a8690]\n\t"
      "leal -0x6c(%%ebp), %%ebx\n\t"
      "pushl %%eax\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "call *%[ca5610]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lplayer_aim_projectile_6\n\t"
      "movl 0x34(%%esi), %%ecx\n\t"
      "leal -0x48(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x10(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c86b80]\n\t"
      "movl %%edi, %%edx\n\t"
      "movl (%%edx), %%eax\n\t"
      "movl 0x4(%%edx), %%ecx\n\t"
      "movl 0x8(%%edx), %%edx\n\t"
      "movl %%ecx, -0x18(%%ebp)\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x20(%%esi), %%cx\n\t"
      "movl %%eax, -0x1c(%%ebp)\n\t"
      "leal -0xa4(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl %%edx, -0x14(%%ebp)\n\t"
      "movl 0x34(%%esi), %%edx\n\t"
      "leal -0x48(%%ebp), %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "leal -0x10(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x6c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl $0, -0x30(%%ebp)\n\t"
      "call *%[ca6030]\n\t"
      "movl 0xc(%%ebp), %%ebx\n\t"
      "addl $0x24, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lplayer_aim_projectile_4\n\t"
      "flds -0xa0(%%ebp)\n\t"
      "leal -0x1c(%%ebp), %%eax\n\t"
      "fsubs (%%ebx)\n\t"
      "pushl %%eax\n\t"
      "fstps -0x1c(%%ebp)\n\t"
      "flds -0x9c(%%ebp)\n\t"
      "fsubs 0x4(%%ebx)\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "flds -0x98(%%ebp)\n\t"
      "fsubs 0x8(%%ebx)\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "call *%[norm]\n\t"
      "fcomps 0x2533c0\n\t"
      "addl $4, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .Lplayer_aim_projectile_3\n\t"
      "movl %%edi, %%ecx\n\t"
      "movl (%%ecx), %%edx\n\t"
      "movl 0x4(%%ecx), %%eax\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "movl %%edx, -0x1c(%%ebp)\n\t"
      "movl %%eax, -0x18(%%ebp)\n\t"
      "movl %%ecx, -0x14(%%ebp)\n\t"
      ".Lplayer_aim_projectile_3:\n\t"
      "movl -0x74(%%ebp), %%edx\n\t"
      "movl -0xa4(%%ebp), %%eax\n\t"
      "movl %%edx, -0x30(%%ebp)\n\t"
      "movl %%eax, -0x2c(%%ebp)\n\t"
      ".Lplayer_aim_projectile_4:\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "pushl $3\n\t"
      "pushl %%ecx\n\t"
      "call *%[get]\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fsubs 0xc(%%eax)\n\t"
      "addl $0xc, %%eax\n\t"
      "flds -0xc(%%ebp)\n\t"
      "movl -0x48(%%ebp), %%edx\n\t"
      "fsubs 0x4(%%eax)\n\t"
      "movl -0x40(%%ebp), %%ecx\n\t"
      "flds -0x8(%%ebp)\n\t"
      "movl %%edx, -0x28(%%ebp)\n\t"
      "fsubs 0x8(%%eax)\n\t"
      "movl -0x44(%%ebp), %%eax\n\t"
      "leal -0x28(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "fld %%st(0)\n\t"
      "movl %%eax, -0x24(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "movl %%ecx, -0x20(%%ebp)\n\t"
      "fld %%st(2)\n\t"
      "fmul %%st(3), %%st(0)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fld %%st(3)\n\t"
      "fmul %%st(4), %%st(0)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fsqrt\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "call *%[norm]\n\t"
      "fstp %%st(0)\n\t"
      "movl 0x34(%%esi), %%ecx\n\t"
      "flds -0x28(%%ebp)\n\t"
      "leal -0xbc(%%ebp), %%eax\n\t"
      "fmuls -0x4(%%ebp)\n\t"
      "pushl %%eax\n\t"
      "flds -0x24(%%ebp)\n\t"
      "pushl %%ecx\n\t"
      "fmuls -0x4(%%ebp)\n\t"
      "leal -0x54(%%ebp), %%edx\n\t"
      "flds -0x20(%%ebp)\n\t"
      "pushl %%edx\n\t"
      "fmuls -0x4(%%ebp)\n\t"
      "leal -0x10(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x1000e9\n\t"
      "fstps -0x20(%%ebp)\n\t"
      "fxch %%st(1)\n\t"
      "fadds -0x10(%%ebp)\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "fadds -0xc(%%ebp)\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "flds -0x20(%%ebp)\n\t"
      "fadds -0x8(%%ebp)\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "flds -0x48(%%ebp)\n\t"
      "fmuls 0x26b0b0\n\t"
      "fstps -0x54(%%ebp)\n\t"
      "flds -0x44(%%ebp)\n\t"
      "fmuls 0x26b0b0\n\t"
      "fstps -0x50(%%ebp)\n\t"
      "flds -0x40(%%ebp)\n\t"
      "fmuls 0x26b0b0\n\t"
      "fstps -0x4c(%%ebp)\n\t"
      "call *%[ray]\n\t"
      "flds -0xa4(%%ebp)\n\t"
      "leal -0x3c(%%ebp), %%ecx\n\t"
      "fsubs (%%ebx)\n\t"
      "fstps -0x3c(%%ebp)\n\t"
      "flds -0xa0(%%ebp)\n\t"
      "fsubs 0x4(%%ebx)\n\t"
      "fstps -0x38(%%ebp)\n\t"
      "flds -0x9c(%%ebp)\n\t"
      "fsubs 0x8(%%ebx)\n\t"
      "fstps -0x34(%%ebp)\n\t"
      "pushl %%ecx\n\t"
      "call *%[norm]\n\t"
      "fcomps 0x2533c0\n\t"
      "addl $0x24, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .Lplayer_aim_projectile_5\n\t"
      "movl %%edi, %%edx\n\t"
      "movl (%%edx), %%eax\n\t"
      "movl 0x4(%%edx), %%ecx\n\t"
      "movl 0x8(%%edx), %%edx\n\t"
      "movl %%eax, -0x3c(%%ebp)\n\t"
      "movl %%ecx, -0x38(%%ebp)\n\t"
      "movl %%edx, -0x34(%%ebp)\n\t"
      ".Lplayer_aim_projectile_5:\n\t"
      "movl -0x30(%%ebp), %%ecx\n\t"
      "leal -0x54(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "leal -0x1c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x3c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c10c780]\n\t"
      "flds -0x5c(%%ebp)\n\t"
      "fcos\n\t"
      "addl $0x10, %%esp\n\t"
      "pushl %%edi\n\t"
      "subl $8, %%esp\n\t"
      "leal -0x54(%%ebp), %%ecx\n\t"
      "fstps 0x4(%%esp)\n\t"
      "flds -0x5c(%%ebp)\n\t"
      "fsin\n\t"
      "fstps (%%esp)\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "call *%[c10fed0]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lplayer_aim_projectile_6:\n\t"
      "cmpw $1, 0x4761d8\n\t"
      "jg .Lplayer_aim_projectile_7\n\t"
      "pushl $1\n\t"
      "pushl $0x8c\n\t"
      "pushl $0x26b08c\n\t"
      "pushl $0x253418\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lplayer_aim_projectile_7:\n\t"
      "decw 0x4761d8\n\t"
      "movl -0x2c(%%ebp), %%edi\n\t"
      "movl %%edi, 0x40(%%esi)\n\t"
      "call *%[gtime]\n\t"
      "movl %%eax, 0x44(%%esi)\n\t"
      "movl %%edi, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      :
      : [dget] "m"(ba6130_dget), [c1a9880] "m"(ba6130_c1a9880), [c21fb0] "m"(ba6130_c21fb0), [c8d9d0] "m"(ba6130_c8d9d0), [assert] "m"(ba6130_assert), [exitfn] "m"(ba6130_exitfn), [c1a8690] "m"(ba6130_c1a8690), [ca5610] "m"(ba6130_ca5610), [c86b80] "m"(ba6130_c86b80), [ca6030] "m"(ba6130_ca6030), [norm] "m"(ba6130_norm), [get] "m"(ba6130_get), [ray] "m"(ba6130_ray), [c10c780] "m"(ba6130_c10c780), [c10fed0] "m"(ba6130_c10fed0), [gtime] "m"(ba6130_gtime)
      : "memory");
}
#else
#error "player_aim_projectile: clang naked draft required"
#endif


/* FUN_000a6930 (0xa6930) — XBE naked draft (batch 124). */
#if defined(__clang__)
static int (*const ba6930_ca67c0)(void) = FUN_000a67c0;
static void *(*const ba6930_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void *(*const ba6930_get)(int, int) = object_get_and_verify_type;
static vector3_t * (*const ba6930_c1412f0)(int object_handle, vector3_t *out_position) = object_get_world_position;
static void (*const ba6930_c141360)(int object_handle, float *out_forward, float *out_up) = object_get_orientation;
static void (*const ba6930_opnew)(void *, int, int) = object_placement_data_new;
static int (*const ba6930_onew)(void *) = object_new;

__attribute__((naked, noinline))
void FUN_000a6930(int param_0, unsigned short param_1 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xb0, %%esp\n\t"
      "call *%[ca67c0]\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_000a6930_5\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "movl 0x5aa6d4, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x34(%%esi), %%ecx\n\t"
      "pushl $3\n\t"
      "pushl %%ecx\n\t"
      "call *%[get]\n\t"
      "movl 0x34(%%esi), %%eax\n\t"
      "leal -0x1c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c1412f0]\n\t"
      "movl 0x34(%%esi), %%eax\n\t"
      "leal -0x28(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x10(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c141360]\n\t"
      "movw 0xc(%%ebp), %%ax\n\t"
      "addl $0x24, %%esp\n\t"
      "testw %%ax, %%ax\n\t"
      "jle .LFUN_000a6930_4\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "xorl %%esi, %%esi\n\t"
      "addl $0xc, %%edi\n\t"
      "movzwl %%ax, %%ebx\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_000a6930_1:\n\t"
      "movl (%%edi), %%ecx\n\t"
      "cmpl $-1, %%ecx\n\t"
      "je .LFUN_000a6930_3\n\t"
      "movswl %%ax, %%edx\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      "fildl -0x4(%%ebp)\n\t"
      "fdivrs 0x255a54\n\t"
      "fcoms 0x26b164\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_000a6930_2\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x26b164\n\t"
      ".LFUN_000a6930_2:\n\t"
      "flds -0x10(%%ebp)\n\t"
      "movl %%edx, %%eax\n\t"
      "flds -0xc(%%ebp)\n\t"
      "cdq\n\t"
      "fpatan\n\t"
      "subl %%edx, %%eax\n\t"
      "sarl $1, %%eax\n\t"
      "movl %%esi, %%edx\n\t"
      "subl %%eax, %%edx\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      "pushl $-1\n\t"
      "pushl %%ecx\n\t"
      "leal -0xb0(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "fildl -0x4(%%ebp)\n\t"
      ".byte 0xd8, 0xca\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "call *%[opnew]\n\t"
      "flds -0x4(%%ebp)\n\t"
      "movl -0x10(%%ebp), %%ecx\n\t"
      "fcos\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movl %%ecx, -0x7c(%%ebp)\n\t"
      "movl -0x28(%%ebp), %%ecx\n\t"
      "movl %%ecx, -0x70(%%ebp)\n\t"
      "movl %%edx, -0x78(%%ebp)\n\t"
      "movl -0x24(%%ebp), %%edx\n\t"
      "movl %%eax, -0x74(%%ebp)\n\t"
      "movl -0x20(%%ebp), %%eax\n\t"
      "leal -0xb0(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl %%edx, -0x6c(%%ebp)\n\t"
      "movl %%eax, -0x68(%%ebp)\n\t"
      "fmuls 0x2533ec\n\t"
      "fadds -0x1c(%%ebp)\n\t"
      "fstps -0x98(%%ebp)\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fsin\n\t"
      "fmuls 0x2533ec\n\t"
      "fadds -0x18(%%ebp)\n\t"
      "fstps -0x94(%%ebp)\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fadds 0x2533f0\n\t"
      "fstps -0x90(%%ebp)\n\t"
      "call *%[onew]\n\t"
      "movw 0xc(%%ebp), %%ax\n\t"
      "addl $0x10, %%esp\n\t"
      ".LFUN_000a6930_3:\n\t"
      "incl %%esi\n\t"
      "addl $0x10, %%edi\n\t"
      "decl %%ebx\n\t"
      "jne .LFUN_000a6930_1\n\t"
      "popl %%edi\n\t"
      "popl %%ebx\n\t"
      ".LFUN_000a6930_4:\n\t"
      "popl %%esi\n\t"
      ".LFUN_000a6930_5:\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [ca67c0] "m"(ba6930_ca67c0), [dget] "m"(ba6930_dget), [get] "m"(ba6930_get), [c1412f0] "m"(ba6930_c1412f0), [c141360] "m"(ba6930_c141360), [opnew] "m"(ba6930_opnew), [onew] "m"(ba6930_onew)
      : "memory");
}
#else
#error "FUN_000a6930: clang naked draft required"
#endif

/* --- cheats.obj orphan shells (2026-07-26) --- */

/* FUN_000a6470 (0xa6470) — XBE naked draft (batch 120). */
#if defined(__clang__)
static int16_t (*const ba6470_c86410)(int16_t local_player_index) = director_get_perspective;
static int (*const ba6470_cba3c0)(int16_t local_player_index) = local_player_get_player_index;
static void *(*const ba6470_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static int (*const ba6470_c1a9880)(int unit_index) = unit_get_aiming_unit_index;
static int16_t (*const ba6470_cb6a70)(int16_t local_player_index) = player_control_get_zoom_level;
static void (*const ba6470_ca5610)(void) = (void *)FUN_000a5610;
static void * (*const ba6470_c8a4e0)(unsigned __int16 local_player_index) = observer_get_camera;
static void (*const ba6470_ca6030)(void) = (void *)FUN_000a6030;
static void (*const ba6470_c10cc00)(float *out_angles, float *in_vector) = vector_to_angles;
static void (*const ba6470_c140070)(int object_handle, float *position_out, float *direction_out) = object_get_root_location;

__attribute__((naked, noinline))
int FUN_000a6470(int16_t local_player_index __attribute__((unused)), float *field_2c __attribute__((unused)), float *field_30 __attribute__((unused)), float *scratch_a __attribute__((unused)), float *scratch_b __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x68, %%esp\n\t"
      "pushl %%ebx\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "call *%[c86410]\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "movl 0x14(%%ebp), %%edi\n\t"
      "movl 0x18(%%ebp), %%esi\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movl %%ecx, (%%edx)\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "movl %%ecx, (%%edx)\n\t"
      "addl $4, %%esp\n\t"
      "cmpw %%cx, %%ax\n\t"
      "movl %%ecx, 0x4(%%edi)\n\t"
      "movl %%ecx, (%%edi)\n\t"
      "movl %%ecx, 0x4(%%esi)\n\t"
      "movl %%ecx, (%%esi)\n\t"
      "je .LFUN_000a6470_1\n\t"
      "cmpw $1, %%ax\n\t"
      "jne .LFUN_000a6470_2\n\t"
      ".LFUN_000a6470_1:\n\t"
      "pushl %%ebx\n\t"
      "call *%[cba3c0]\n\t"
      "pushl %%eax\n\t"
      "movl 0x5aa6d4, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl 0x34(%%eax), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl %%eax, 0x18(%%ebp)\n\t"
      "call *%[c1a9880]\n\t"
      "pushl %%ebx\n\t"
      "movl %%eax, 0x14(%%ebp)\n\t"
      "call *%[cb6a70]\n\t"
      "leal -0x30(%%ebp), %%ebx\n\t"
      "pushl %%eax\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "call *%[ca5610]\n\t"
      "addl $0x18, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000a6470_2\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c8a4e0]\n\t"
      "movl 0x18(%%ebp), %%ebx\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x20(%%ebx), %%dx\n\t"
      "leal -0x68(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ecx\n\t"
      "leal 0x20(%%eax), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "leal -0x30(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[ca6030]\n\t"
      "addl $0x1c, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000a6470_2\n\t"
      "movl -0x38(%%ebp), %%ecx\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "movl -0x34(%%ebp), %%eax\n\t"
      "movl %%ecx, (%%edx)\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "leal -0x58(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "movl %%eax, (%%ecx)\n\t"
      "call *%[c10cc00]\n\t"
      "movl 0x34(%%ebx), %%ecx\n\t"
      "pushl $0\n\t"
      "leal -0x18(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c140070]\n\t"
      "movl -0x68(%%ebp), %%eax\n\t"
      "pushl $0\n\t"
      "leal -0xc(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c140070]\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fsubs -0x18(%%ebp)\n\t"
      "movl -0x68(%%ebp), %%eax\n\t"
      "flds -0x8(%%ebp)\n\t"
      "addl $0x20, %%esp\n\t"
      "fsubs -0x14(%%ebp)\n\t"
      "popl %%edi\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fsubs -0x10(%%ebp)\n\t"
      "flds -0x58(%%ebp)\n\t"
      "fmuls -0x58(%%ebp)\n\t"
      "flds -0x54(%%ebp)\n\t"
      "fmuls -0x54(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fld %%st(0)\n\t"
      "fsqrt\n\t"
      "flds -0x58(%%ebp)\n\t"
      ".byte 0xd8, 0xcc\n\t"
      "flds -0x54(%%ebp)\n\t"
      ".byte 0xd8, 0xce\n\t"
      ".byte 0xde, 0xe9\n\t"
      ".byte 0xd8, 0xf2\n\t"
      "fstps (%%esi)\n\t"
      "fxch %%st(2)\n\t"
      ".byte 0xd8, 0xca\n\t"
      "flds -0x54(%%ebp)\n\t"
      ".byte 0xd8, 0xcc\n\t"
      "flds -0x58(%%ebp)\n\t"
      ".byte 0xd8, 0xce\n\t"
      ".byte 0xde, 0xc1\n\t"
      ".byte 0xd8, 0xf3\n\t"
      "fmuls -0x50(%%ebp)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "flds -0x50(%%ebp)\n\t"
      "fmuls -0x50(%%ebp)\n\t"
      ".byte 0xd8, 0xc2\n\t"
      ".byte 0xde, 0xf9\n\t"
      "fstps 0x4(%%esi)\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "fstp %%st(1)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000a6470_2:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "orl $0xffffffff, %%eax\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c86410] "m"(ba6470_c86410), [cba3c0] "m"(ba6470_cba3c0), [dget] "m"(ba6470_dget), [c1a9880] "m"(ba6470_c1a9880), [cb6a70] "m"(ba6470_cb6a70), [ca5610] "m"(ba6470_ca5610), [c8a4e0] "m"(ba6470_c8a4e0), [ca6030] "m"(ba6470_ca6030), [c10cc00] "m"(ba6470_c10cc00), [c140070] "m"(ba6470_c140070)
      : "memory");
}
#else
#error "FUN_000a6470: clang naked draft required"
#endif

