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

/* FUN_000a54b0 (0xa54b0) — XBE naked draft (batch 139). */
#if defined(__clang__)
static void (*const ba54b0_ca3e60)(void) = FUN_000a3e60;
static bool (*const ba54b0_c18f3e0)(void *location, void *position, int16_t *out_sky_index) = FUN_0018f3e0;
static void * (*const ba54b0_c18e3c0)(void) = scenario_get;
static void *(*const ba54b0_elem)(void *, int, int) = tag_block_get_element;
static void (*const ba54b0_ca4200)(void) = weather_particle_system_delete;
static void (*const ba54b0_ca40a0)(void) = weather_particle_system_new;
static void (*const ba54b0_ca4e20)(int16_t weather_index) = weather_particle_system_render;

__attribute__((naked, noinline))
void FUN_000a54b0(void)
{
  __asm__ volatile(
      "movb 0x32574c, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000a54b0_5\n\t"
      "movb 0x2ef7ee, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000a54b0_5\n\t"
      "pushl %%esi\n\t"
      "movl 0x506548, %%esi\n\t"
      "cmpw $-1, %%si\n\t"
      "je .LFUN_000a54b0_4\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "call *%[ca3e60]\n\t"
      "movl %%eax, %%esi\n\t"
      "movw 0x506784, %%ax\n\t"
      "leal 0x18(%%esi), %%edi\n\t"
      "movw %%ax, 0x14(%%esi)\n\t"
      "movl 0x506780, %%ecx\n\t"
      "pushl %%edi\n\t"
      "leal 0x10(%%esi), %%eax\n\t"
      "pushl $0x506550\n\t"
      "pushl %%eax\n\t"
      "orl $0xffffffff, %%ebx\n\t"
      "movl %%ecx, (%%eax)\n\t"
      "call *%[c18f3e0]\n\t"
      "movw (%%edi), %%di\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpw $-1, %%di\n\t"
      "movb %%al, 0x1a(%%esi)\n\t"
      "je .LFUN_000a54b0_1\n\t"
      "movswl %%di, %%edx\n\t"
      "pushl $0xf0\n\t"
      "pushl %%edx\n\t"
      "call *%[c18e3c0]\n\t"
      "addl $0x1b4, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl 0x2c(%%eax), %%ebx\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_000a54b0_1:\n\t"
      "movl (%%esi), %%eax\n\t"
      "cmpl %%ebx, %%eax\n\t"
      "je .LFUN_000a54b0_3\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_000a54b0_2\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x506548, %%ax\n\t"
      "pushl %%eax\n\t"
      "call *%[ca4200]\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_000a54b0_2:\n\t"
      "cmpl $-1, %%ebx\n\t"
      "je .LFUN_000a54b0_3\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x506548, %%cx\n\t"
      "pushl $0x3f800000\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ecx\n\t"
      "call *%[ca40a0]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_000a54b0_3:\n\t"
      "cmpl $-1, (%%esi)\n\t"
      "popl %%edi\n\t"
      "popl %%ebx\n\t"
      "je .LFUN_000a54b0_4\n\t"
      "movl 0x506548, %%eax\n\t"
      "popl %%esi\n\t"
      "jmp .LFUN_000a54b0_10000\n\t"
      ".LFUN_000a54b0_4:\n\t"
      "popl %%esi\n\t"
      ".LFUN_000a54b0_5:\n\t"
      "ret\n\t"
      ".LFUN_000a54b0_10000:\n\t"
      "jmp *%[ca4e20]\n\t"
      :
      : [ca3e60] "m"(ba54b0_ca3e60), [c18f3e0] "m"(ba54b0_c18f3e0), [c18e3c0] "m"(ba54b0_c18e3c0), [elem] "m"(ba54b0_elem), [ca4200] "m"(ba54b0_ca4200), [ca40a0] "m"(ba54b0_ca40a0), [ca4e20] "m"(ba54b0_ca4e20)
      : "memory");
}
#else
#error "FUN_000a54b0: clang naked draft required"
#endif


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

/* FUN_000a5610 (0xa5610) — XBE naked draft (batch 134). */
#if defined(__clang__)
static void *(*const ba5610_get)(int, int) = object_get_and_verify_type;
static int (*const ba5610_c1adeb0)(int unit_handle, int16_t weapon_index) = unit_get_weapon;
static void *(*const ba5610_tag)(int, int) = tag_get;
static float (*const ba5610_cfc780)(int weapon_handle, int16_t zoom_level) = weapon_get_zoom_magnification;

__attribute__((naked, noinline))
void FUN_000a5610(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "movl %%eax, %%esi\n\t"
      "cmpl $-1, %%esi\n\t"
      "pushl %%edi\n\t"
      "je .LFUN_000a5610_3\n\t"
      "pushl $3\n\t"
      "pushl %%esi\n\t"
      "call *%[get]\n\t"
      "movswl 0x2a2(%%eax), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[c1adeb0]\n\t"
      "movl %%eax, %%edi\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpl $-1, %%edi\n\t"
      "je .LFUN_000a5610_3\n\t"
      "pushl $4\n\t"
      "pushl %%edi\n\t"
      "call *%[get]\n\t"
      "movl (%%eax), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x77656170\n\t"
      "call *%[tag]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "jne .LFUN_000a5610_1\n\t"
      "testb $0x20, 0x308(%%esi)\n\t"
      "jne .LFUN_000a5610_3\n\t"
      ".LFUN_000a5610_1:\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "call *%[cfc780]\n\t"
      "flds 0x2533c8\n\t"
      ".byte 0xd8, 0xf1\n\t"
      "addl $8, %%esp\n\t"
      "fsts -0x4(%%ebp)\n\t"
      "fmuls 0x3e4(%%esi)\n\t"
      "fstps (%%ebx)\n\t"
      "fld %%st(0)\n\t"
      "fmuls 0x3e8(%%esi)\n\t"
      "fstps 0x4(%%ebx)\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fmuls 0x3ec(%%esi)\n\t"
      "fstps 0x8(%%ebx)\n\t"
      "fmuls 0x3f0(%%esi)\n\t"
      "fstps 0xc(%%ebx)\n\t"
      "flds 0x3f4(%%esi)\n\t"
      "fcomps 0x3e4(%%esi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_000a5610_2\n\t"
      "flds 0x3f4(%%esi)\n\t"
      "popl %%edi\n\t"
      "fmuls -0x4(%%ebp)\n\t"
      "movb $1, %%al\n\t"
      "popl %%esi\n\t"
      "fstps 0x10(%%ebx)\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000a5610_2:\n\t"
      "flds 0x3e4(%%esi)\n\t"
      "popl %%edi\n\t"
      "fmuls -0x4(%%ebp)\n\t"
      "movb $1, %%al\n\t"
      "popl %%esi\n\t"
      "fstps 0x10(%%ebx)\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000a5610_3:\n\t"
      "popl %%edi\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [get] "m"(ba5610_get), [c1adeb0] "m"(ba5610_c1adeb0), [tag] "m"(ba5610_tag), [cfc780] "m"(ba5610_cfc780)
      : "memory");
}
#else
#error "FUN_000a5610: clang naked draft required"
#endif


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

/* FUN_000a57b0 (0xa57b0) — XBE naked draft (batch 153). */
#if defined(__clang__)


__attribute__((naked, noinline))
short FUN_000a57b0(float *vec __attribute__((unused)), float max_length __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "flds 0x8(%%ecx)\n\t"
      "flds 0x4(%%ecx)\n\t"
      "flds (%%ecx)\n\t"
      "fld %%st(0)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fld %%st(2)\n\t"
      ".byte 0xd8, 0xcb\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fld %%st(3)\n\t"
      ".byte 0xd8, 0xcc\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fstp %%st(3)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fmuls 0xc(%%ebp)\n\t"
      "fld %%st(1)\n\t"
      "fcompp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_000a57b0_1\n\t"
      "fsqrt\n\t"
      "movb $1, %%al\n\t"
      "fdivrs 0xc(%%ebp)\n\t"
      "fld %%st(0)\n\t"
      "fmuls (%%ecx)\n\t"
      "fstps (%%ecx)\n\t"
      "fld %%st(0)\n\t"
      "fmuls 0x4(%%ecx)\n\t"
      "fstps 0x4(%%ecx)\n\t"
      "fmuls 0x8(%%ecx)\n\t"
      "fstps 0x8(%%ecx)\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000a57b0_1:\n\t"
      "fstp %%st(0)\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "FUN_000a57b0: clang naked draft required"
#endif


/* FUN_000a5810 (0xa5810) — readable C lift. */
void FUN_000a5810(float *out, float value, int field0)
{
  out[1] = value;
  *(int *)out = field0;
}

/* FUN_000a5830 (0xa5830) — XBE naked draft (batch 135). */
#if defined(__clang__)
static void (*const ba5830_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const ba5830_exitfn)(int) = system_exit;
static int (*const ba5830_c13d7f0)(int object_handle) = object_get_root_parent;
static bool (*const ba5830_ray)(unsigned int, float *, float *, int, short *) = FUN_0014df70;

__attribute__((naked, noinline))
void FUN_000a5830(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x5c, %%esp\n\t"
      "pushl %%ebx\n\t"
      "xorb %%bl, %%bl\n\t"
      "cmpw $0x20, 0x4761d8\n\t"
      "jl .LFUN_000a5830_1\n\t"
      "pushl $1\n\t"
      "pushl $0x15e\n\t"
      "pushl $0x26b08c\n\t"
      "pushl $0x253440\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000a5830_1:\n\t"
      "movw 0x4761d8, %%ax\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "movswl %%ax, %%ecx\n\t"
      "incw %%ax\n\t"
      "pushl %%edx\n\t"
      "movw $6, 0x5a8c80(,%%ecx,2)\n\t"
      "movw %%ax, 0x4761d8\n\t"
      "call *%[c13d7f0]\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "flds (%%edx)\n\t"
      "fsubs (%%ecx)\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "flds 0x4(%%edx)\n\t"
      "fsubs 0x4(%%ecx)\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "flds 0x8(%%edx)\n\t"
      "leal -0x5c(%%ebp), %%edx\n\t"
      "fsubs 0x8(%%ecx)\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "leal -0xc(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "pushl %%ecx\n\t"
      "pushl $0xc2ad\n\t"
      "call *%[ray]\n\t"
      "addl $0x18, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000a5830_2\n\t"
      "cmpw $3, -0x5c(%%ebp)\n\t"
      "jne .LFUN_000a5830_3\n\t"
      "movl -0x24(%%ebp), %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%ecx\n\t"
      "call *%[c13d7f0]\n\t"
      "movl 0x14(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl %%eax, %%esi\n\t"
      "call *%[c13d7f0]\n\t"
      "addl $8, %%esp\n\t"
      "cmpl %%eax, %%esi\n\t"
      "popl %%esi\n\t"
      "jne .LFUN_000a5830_3\n\t"
      ".LFUN_000a5830_2:\n\t"
      "movb $1, %%bl\n\t"
      ".LFUN_000a5830_3:\n\t"
      "cmpw $1, 0x4761d8\n\t"
      "jg .LFUN_000a5830_4\n\t"
      "pushl $1\n\t"
      "pushl $0x16f\n\t"
      "pushl $0x26b08c\n\t"
      "pushl $0x253418\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000a5830_4:\n\t"
      "decw 0x4761d8\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(ba5830_assert), [exitfn] "m"(ba5830_exitfn), [c13d7f0] "m"(ba5830_c13d7f0), [ray] "m"(ba5830_ray)
      : "memory");
}
#else
#error "FUN_000a5830: clang naked draft required"
#endif


/* FUN_000a5920 (0xa5920) — XBE naked draft (batch 117). */
#if defined(__clang__)
static void (*const ba5920_c1a12e0)(int unit_handle, float *out_pos, float *out_axis, int *out_value) = biped_get_autoaim_pill;
static short (*const ba5920_a57b0)(float *, float) = (void *)FUN_000a57b0;

__attribute__((naked, noinline))
void FUN_000a5920(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x2c, %%esp\n\t"
      "leal -0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "leal -0x14(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x20(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c1a12e0]\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fmuls 0x8(%%esi)\n\t"
      "addl $0x10, %%esp\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fmuls 0x4(%%esi)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fmuls (%%esi)\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fmuls 0x8(%%esi)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fmuls 0x4(%%esi)\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fmuls (%%esi)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fld %%st(0)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fld %%st(2)\n\t"
      ".byte 0xd8, 0xcb\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fld %%st(3)\n\t"
      ".byte 0xd8, 0xcc\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fsts -0x4(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_000a5920_3\n\t"
      "flds (%%ebx)\n\t"
      "fsubs -0x20(%%ebp)\n\t"
      "flds 0x4(%%ebx)\n\t"
      "fsubs -0x1c(%%ebp)\n\t"
      "flds 0x8(%%ebx)\n\t"
      "fsubs -0x18(%%ebp)\n\t"
      "fld %%st(1)\n\t"
      "fmuls 0x8(%%esi)\n\t"
      "fld %%st(1)\n\t"
      "fmuls 0x4(%%esi)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0x2c(%%ebp)\n\t"
      "fmuls (%%esi)\n\t"
      "fld %%st(2)\n\t"
      "fmuls 0x8(%%esi)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0x28(%%ebp)\n\t"
      "fxch %%st(1)\n\t"
      "fmuls 0x4(%%esi)\n\t"
      "fld %%st(1)\n\t"
      "fmuls (%%esi)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fxch %%st(1)\n\t"
      "fstp %%st(0)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "flds -0x28(%%ebp)\n\t"
      ".byte 0xd8, 0xcb\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds -0x2c(%%ebp)\n\t"
      ".byte 0xd8, 0xcc\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fdivs -0x4(%%ebp)\n\t"
      "fstp %%st(3)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "fcoms 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_000a5920_1\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c0\n\t"
      "jmp .LFUN_000a5920_2\n\t"
      ".LFUN_000a5920_1:\n\t"
      "fcoms 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_000a5920_2\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c8\n\t"
      ".LFUN_000a5920_2:\n\t"
      "flds -0x14(%%ebp)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fadds -0x20(%%ebp)\n\t"
      "fstps (%%edi)\n\t"
      "flds -0x10(%%ebp)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fadds -0x1c(%%ebp)\n\t"
      "fstps 0x4(%%edi)\n\t"
      "fmuls -0xc(%%ebp)\n\t"
      "fadds -0x18(%%ebp)\n\t"
      "fstps 0x8(%%edi)\n\t"
      "jmp .LFUN_000a5920_4\n\t"
      ".LFUN_000a5920_3:\n\t"
      "movl -0x20(%%ebp), %%edx\n\t"
      "fstp %%st(0)\n\t"
      "movl -0x1c(%%ebp), %%eax\n\t"
      "fstp %%st(0)\n\t"
      "movl %%edi, %%ecx\n\t"
      "fstp %%st(0)\n\t"
      "movl %%edx, (%%ecx)\n\t"
      "movl -0x18(%%ebp), %%edx\n\t"
      "movl %%eax, 0x4(%%ecx)\n\t"
      "movl %%edx, 0x8(%%ecx)\n\t"
      ".LFUN_000a5920_4:\n\t"
      "flds (%%edi)\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "fsubs (%%ebx)\n\t"
      "pushl %%eax\n\t"
      "flds 0x4(%%edi)\n\t"
      "leal -0x20(%%ebp), %%ecx\n\t"
      "fsubs 0x4(%%ebx)\n\t"
      "pushl %%ecx\n\t"
      "flds 0x8(%%edi)\n\t"
      "fsubs 0x8(%%ebx)\n\t"
      "fstps -0x24(%%ebp)\n\t"
      "fld %%st(1)\n\t"
      "fmuls (%%esi)\n\t"
      "flds -0x24(%%ebp)\n\t"
      "fmuls 0x8(%%esi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fld %%st(1)\n\t"
      "fmuls 0x4(%%esi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fchs\n\t"
      "fsts -0x4(%%ebp)\n\t"
      "fmuls (%%esi)\n\t"
      ".byte 0xd8, 0xc2\n\t"
      "fstps -0x20(%%ebp)\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fmuls 0x4(%%esi)\n\t"
      ".byte 0xd8, 0xc1\n\t"
      "fstps -0x1c(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fmuls 0x8(%%esi)\n\t"
      "fadds -0x24(%%ebp)\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "call *%[a57b0]\n\t"
      "flds (%%edi)\n\t"
      "addl $8, %%esp\n\t"
      "fsubs -0x20(%%ebp)\n\t"
      "fstps (%%edi)\n\t"
      "flds 0x4(%%edi)\n\t"
      "fsubs -0x1c(%%ebp)\n\t"
      "fstps 0x4(%%edi)\n\t"
      "flds 0x8(%%edi)\n\t"
      "fsubs -0x18(%%ebp)\n\t"
      "fstps 0x8(%%edi)\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c1a12e0] "m"(ba5920_c1a12e0), [a57b0] "m"(ba5920_a57b0)
      : "memory");
}
#else
#error "FUN_000a5920: clang naked draft required"
#endif


/* FUN_000a5ac0 (0xa5ac0) — XBE naked draft (batch 119). */
#if defined(__clang__)
static void (*const ba5ac0_ca5920)(void) = FUN_000a5920;
static float (*const ba5ac0_norm)(float *) = normalize3d;
static void (*const ba5ac0_c1d94f0)(void) = FUN_001d94f0;
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
static void (*const ba5c60_ca5920)(void) = FUN_000a5920;
static void (*const ba5c60_ca5830)(void) = FUN_000a5830;
static float (*const ba5c60_norm)(float *) = normalize3d;
static void (*const ba5c60_c1d94f0)(void) = FUN_001d94f0;

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


/* FUN_000a5d70 (0xa5d70) — XBE naked draft (batch 119). */
#if defined(__clang__)
static void *(*const ba5d70_get)(int, int) = object_get_and_verify_type;
static char (*const ba5d70_c110210)(float *p1, float p2, float *p3, float *p4, float p5, float sine, float cosine) = FUN_00110210;
static bool (*const ba5d70_ca7a30)(int16_t team_a, int16_t team_b) = game_allegiance_get_team_is_friendly;
static void *(*const ba5d70_tag)(int, int) = tag_get;
static void (*const ba5d70_ca5ac0)(void) = FUN_000a5ac0;
static void (*const ba5d70_ca5d70)(void) = FUN_000a5d70;

__attribute__((naked, noinline))
void FUN_000a5d70(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x38, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "movl %%edi, %%edi\n\t"
      ".LFUN_000a5d70_1:\n\t"
      "pushl $-1\n\t"
      "pushl %%edi\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%esi\n\t"
      "movb 0x64(%%esi), %%cl\n\t"
      "movl $1, %%eax\n\t"
      "shll %%cl, %%eax\n\t"
      "addl $8, %%esp\n\t"
      "movl %%esi, 0xc(%%ebp)\n\t"
      "testb $3, %%al\n\t"
      "je .LFUN_000a5d70_3\n\t"
      "testb $1, 0x4(%%esi)\n\t"
      "jne .LFUN_000a5d70_3\n\t"
      "pushl $3\n\t"
      "pushl %%edi\n\t"
      "call *%[get]\n\t"
      "flds 0x32c(%%eax)\n\t"
      "fcomps 0x2533c8\n\t"
      "addl $8, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_000a5d70_3\n\t"
      "movl 0x20(%%ebp), %%ecx\n\t"
      "movl 0x1c(%%ebp), %%edx\n\t"
      "movl 0x18(%%ebp), %%eax\n\t"
      "pushl %%ecx\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      "pushl %%edx\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "pushl %%eax\n\t"
      "movl 0x5c(%%esi), %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "leal 0x50(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c110210]\n\t"
      "addl $0x1c, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000a5d70_3\n\t"
      "movb 0x64(%%esi), %%cl\n\t"
      "movl $1, %%edx\n\t"
      "shll %%cl, %%edx\n\t"
      "testb $1, %%dl\n\t"
      "je .LFUN_000a5d70_2\n\t"
      "testb $4, 0xb6(%%esi)\n\t"
      "jne .LFUN_000a5d70_2\n\t"
      "cmpl 0x24(%%ebp), %%edi\n\t"
      "je .LFUN_000a5d70_2\n\t"
      "movl 0x28(%%ebp), %%ecx\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x68(%%esi), %%ax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[ca7a30]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000a5d70_2\n\t"
      "movl (%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x62697064\n\t"
      "call *%[tag]\n\t"
      "movl 0x17c(%%eax), %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "testl $0x200000, %%ecx\n\t"
      "jne .LFUN_000a5d70_2\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "leal -0x38(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[ca5ac0]\n\t"
      "addl $0x14, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000a5d70_2\n\t"
      "cmpw 0x2c(%%ebp), %%bx\n\t"
      "jge .LFUN_000a5d70_2\n\t"
      "movl 0x30(%%ebp), %%ecx\n\t"
      "movswl %%bx, %%edi\n\t"
      "imull $0x38, %%edi, %%edi\n\t"
      "addl %%ecx, %%edi\n\t"
      "movl $0xe, %%ecx\n\t"
      "leal -0x38(%%ebp), %%esi\n\t"
      "rep movsl\n\t"
      "movl 0xc(%%ebp), %%esi\n\t"
      "incl %%ebx\n\t"
      ".LFUN_000a5d70_2:\n\t"
      "movl 0xc8(%%esi), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_000a5d70_3\n\t"
      "movl 0x2c(%%ebp), %%ecx\n\t"
      "cmpw %%cx, %%bx\n\t"
      "jge .LFUN_000a5d70_3\n\t"
      "movl 0x30(%%ebp), %%edi\n\t"
      "movswl %%bx, %%edx\n\t"
      "imull $0x38, %%edx, %%edx\n\t"
      "addl %%edi, %%edx\n\t"
      "pushl %%edx\n\t"
      "movl 0x24(%%ebp), %%edx\n\t"
      "subl %%ebx, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl 0x28(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl 0x20(%%ebp), %%ecx\n\t"
      "pushl %%edx\n\t"
      "movl 0x1c(%%ebp), %%edx\n\t"
      "pushl %%ecx\n\t"
      "movl 0x18(%%ebp), %%ecx\n\t"
      "pushl %%edx\n\t"
      "movl 0x14(%%ebp), %%edx\n\t"
      "pushl %%ecx\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "pushl %%edx\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%edx\n\t"
      "call *%[ca5d70]\n\t"
      "addl $0x2c, %%esp\n\t"
      "addl %%eax, %%ebx\n\t"
      ".LFUN_000a5d70_3:\n\t"
      "movl 0xc4(%%esi), %%edi\n\t"
      "cmpl $-1, %%edi\n\t"
      "je .LFUN_000a5d70_4\n\t"
      "cmpw 0x2c(%%ebp), %%bx\n\t"
      "jl .LFUN_000a5d70_1\n\t"
      ".LFUN_000a5d70_4:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movw %%bx, %%ax\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [get] "m"(ba5d70_get), [c110210] "m"(ba5d70_c110210), [ca7a30] "m"(ba5d70_ca7a30), [tag] "m"(ba5d70_tag), [ca5ac0] "m"(ba5d70_ca5ac0), [ca5d70] "m"(ba5d70_ca5d70)
      : "memory");
}
#else
#error "FUN_000a5d70: clang naked draft required"
#endif


/* FUN_000a5f00 (0xa5f00) — XBE naked draft (batch 124). */
#if defined(__clang__)
static void (*const ba5f00_chkstk)(void) = FUN_001d90e0;
static int16_t (*const ba5f00_c198ad0)(int16_t starting_cluster, float *point, float *direction, float length, float sine, float cosine, int16_t max_count, int16_t *out_indices) = structure_clusters_in_cone;
static int16_t (*const ba5f00_c140420)(int flags, int16_t cluster_count, int16_t *cluster_indices, int16_t max_count, int *out_handles) = object_find_in_cluster;
static void (*const ba5f00_ca5d70)(void) = FUN_000a5d70;

__attribute__((naked, noinline))
void FUN_000a5f00(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl $0x2410, %%eax\n\t"
      "call *%[chkstk]\n\t"
      "flds 0x4(%%edi)\n\t"
      "fcomps 0xc(%%edi)\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "xorl %%esi, %%esi\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_000a5f00_1\n\t"
      "movl 0x4(%%edi), %%eax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "jmp .LFUN_000a5f00_2\n\t"
      ".LFUN_000a5f00_1:\n\t"
      "movl 0xc(%%edi), %%ecx\n\t"
      "movl %%ecx, -0x4(%%ebp)\n\t"
      ".LFUN_000a5f00_2:\n\t"
      "flds (%%edi)\n\t"
      "fcomps 0x8(%%edi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_000a5f00_3\n\t"
      "flds (%%edi)\n\t"
      "jmp .LFUN_000a5f00_4\n\t"
      ".LFUN_000a5f00_3:\n\t"
      "flds 0x8(%%edi)\n\t"
      ".LFUN_000a5f00_4:\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_000a5f00_6\n\t"
      "fcoms 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_000a5f00_6\n\t"
      "fld %%st(0)\n\t"
      "leal -0x410(%%ebp), %%edx\n\t"
      "fsin\n\t"
      "pushl %%edx\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "pushl $0x200\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "fcos\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "pushl %%ecx\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "pushl %%edx\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c198ad0]\n\t"
      "leal -0x2410(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x800\n\t"
      "leal -0x410(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl $1\n\t"
      "call *%[c140420]\n\t"
      "addl $0x34, %%esp\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "testw %%ax, %%ax\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "jle .LFUN_000a5f00_7\n\t"
      ".LFUN_000a5f00_5:\n\t"
      "movl 0x20(%%ebp), %%edx\n\t"
      "movswl %%si, %%ecx\n\t"
      "imull $0x38, %%ecx, %%ecx\n\t"
      "addl %%edx, %%ecx\n\t"
      "movl 0x1c(%%ebp), %%edx\n\t"
      "pushl %%ecx\n\t"
      "movl 0x18(%%ebp), %%ecx\n\t"
      "subl %%esi, %%edx\n\t"
      "pushl %%edx\n\t"
      "movl 0x14(%%ebp), %%edx\n\t"
      "pushl %%ecx\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "pushl %%edx\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "pushl %%ecx\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "pushl %%edx\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "pushl %%ecx\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "pushl %%edx\n\t"
      "movswl %%bx, %%eax\n\t"
      "movl -0x2410(%%ebp,%%eax,4), %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "call *%[ca5d70]\n\t"
      "addl $0x2c, %%esp\n\t"
      "addl %%eax, %%esi\n\t"
      "cmpw 0x1c(%%ebp), %%si\n\t"
      "jge .LFUN_000a5f00_7\n\t"
      "incl %%ebx\n\t"
      "cmpw -0x10(%%ebp), %%bx\n\t"
      "jl .LFUN_000a5f00_5\n\t"
      "movw %%si, %%ax\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000a5f00_6:\n\t"
      "fstp %%st(0)\n\t"
      ".LFUN_000a5f00_7:\n\t"
      "movw %%si, %%ax\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [chkstk] "m"(ba5f00_chkstk), [c198ad0] "m"(ba5f00_c198ad0), [c140420] "m"(ba5f00_c140420), [ca5d70] "m"(ba5f00_ca5d70)
      : "memory");
}
#else
#error "FUN_000a5f00: clang naked draft required"
#endif


/* FUN_000a6030 (0xa6030) — XBE naked draft (batch 130). */
#if defined(__clang__)
static int (*const ba6030_c18e720)(int point) = FUN_0018e720;
static void * (*const ba6030_c18e3c0)(void) = scenario_get;
static void *(*const ba6030_elem)(void *, int, int) = tag_block_get_element;
static void (*const ba6030_ca5f00)(void) = FUN_000a5f00;
static void __cdecl (*const ba6030_c1d9260)(void *base, size_t nmemb, size_t size, int (__cdecl *compar)(const void *, const void *)) = qsort;
static void (*const ba6030_ca5830)(void) = FUN_000a5830;

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
static void (*const ba6130_ca5610)(void) = FUN_000a5610;
static void (*const ba6130_c86b80)(void) = (void *)director_camera_deterministic;
static void (*const ba6130_ca6030)(void) = FUN_000a6030;
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
static void (*const ba6470_ca5610)(void) = FUN_000a5610;
static void * (*const ba6470_c8a4e0)(unsigned __int16 local_player_index) = observer_get_camera;
static void (*const ba6470_ca6030)(void) = FUN_000a6030;
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

