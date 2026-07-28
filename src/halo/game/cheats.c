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


/* FUN_000a5ac0 (0xa5ac0) — readable C lift (restored pre-naked). */
void FUN_000a5ac0(void)
{
  int eax = 0;
  int ecx = 0;
  int edi = 0;

  FUN_000a5920();
  normalize3d((float *)0);
  /* test (char)eax, 0x41 -> jne 0xa5b65 */
  ((void(*)(void))FUN_001d94f0)();
  /* cmp edi, eax -> je 0xa5c22 */
  ((void(*)(void))FUN_000a5590)();
  ((void(*)(void))FUN_000a5590)();
  ((void(*)(void))FUN_000a5590)();
  ((void(*)(void))FUN_000a5590)();
  /* test (char)eax, 0x41 -> jne 0xa5c28 */
  object_get_and_verify_type(0, 0);
  tag_get('tinu', 0);
  /* test ecx, 0x80000 -> je 0xa5c28 */
  game_globals_get();
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  /* test (char)eax, 0x41 -> je 0xa5c4f */
  /* test (char)eax, 0x41 -> je 0xa5c4f */

  (void)eax;
  (void)ecx;
  (void)edi;
}


/* FUN_000a5c60 (0xa5c60) — readable C lift (restored pre-naked). */
void FUN_000a5c60(void)
{
  int eax = 0;

  FUN_000a5920();
  ((void(*)(void))FUN_000a5830)();
  /* test (char)eax, (char)eax -> je 0xa5d5d */
  normalize3d((float *)0);
  ((void(*)(void))FUN_001d94f0)();
  /* test (char)eax, 0x41 -> jne 0xa5d44 */
  ((void(*)(void))FUN_001d94f0)();
  ((void(*)(void))FUN_001d94f0)();

  (void)eax;
}


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


/* FUN_000a6030 (0xa6030) — readable C lift (restored pre-naked). */
void FUN_000a6030(void)
{
  int eax = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;

  FUN_0018e720(0);
  /* cmp eax, -1 -> je 0xa60fd */
  FUN_0018e720(0);
  scenario_get();
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  /* cmp (int16_t)eax, 0xffff -> je 0xa60fd */
  FUN_000a5f00();
  /* test (int16_t)edi, (int16_t)edi -> jle 0xa60fd */
  qsort((void *)(uintptr_t)ecx, eax, 56, (void *)0);
  /* test (int16_t)edi, (int16_t)edi -> jle 0xa60fd */
  ((void(*)(void))FUN_000a5830)();
  /* test (char)eax, (char)eax -> jne 0xa6106 */
  /* cmp (int16_t)esi, (int16_t)edi -> jl 0xa60d0 */

  (void)eax;
  (void)ecx;
  (void)esi;
  (void)edi;
}


/* player_aim_projectile (0xa6130) — readable C lift (restored pre-naked). */
int player_aim_projectile(int player_handle, float *out_position,
                          float *aim_direction)
{
  char *player;
  int aiming_unit;
  int16_t zoom;
  char aim_buf[0x6c];
  float cam_pos[3];
  float cam_fwd[3];
  float aim_copy[3];
  float delta[3];
  float scaled_fwd[3];
  float cone_axis[3];
  float pinned[3];
  float dist;
  int object_handle = -1;
  int16_t stack_depth;
  char ok;

  player = (char *)datum_get(*(data_t **)0x5aa6d4, player_handle);
  aiming_unit = unit_get_aiming_unit_index(*(int *)(player + 0x34));
  if (!valid_real_normal3d(aim_direction)) {
    csprintf((char *)0x5ab100, (char *)0x254a24, (char *)0x255554,
             (double)aim_direction[0], (double)aim_direction[1],
             (double)aim_direction[2]);
    display_assert((char *)0x5ab100, (char *)0x26b08c, 0x4d, 1);
    system_exit(-1);
  }

  stack_depth = *(int16_t *)0x4761d8;
  if (stack_depth >= 0x20) {
    display_assert((char *)0x253440, (char *)0x26b08c, 0x4f, 1);
    system_exit(-1);
  }
  *(int16_t *)(0x5a8c80 + (int)stack_depth * 2) = 6;
  *(int16_t *)0x4761d8 = (int16_t)(stack_depth + 1);

  zoom = unit_get_zoom_level(aiming_unit);
  /* FUN_000a5610 fills aim_buf from the aiming unit / zoom level. */
  ok = ((char (*)(int, void *, int16_t))FUN_000a5610)(aiming_unit, aim_buf, zoom);
  if (ok) {
    ((void(*)(void))director_camera_deterministic)();
    aim_copy[0] = aim_direction[0];
    aim_copy[1] = aim_direction[1];
    aim_copy[2] = aim_direction[2];
    ok = ((char (*)(void *, void *, void *, int, uint16_t, void *))FUN_000a6030)(
        aim_buf, cam_pos, cam_fwd, *(int *)(player + 0x34),
        *(uint16_t *)(player + 0x20), (void *)0);
    if (ok) {
      delta[0] = cam_fwd[0] - out_position[0];
      delta[1] = cam_fwd[1] - out_position[1];
      delta[2] = cam_fwd[2] - out_position[2];
      if (normalize3d(delta) == 0.0f) {
        delta[0] = aim_copy[0];
        delta[1] = aim_copy[1];
        delta[2] = aim_copy[2];
      }
      object_handle = *(int *)(aim_buf + 0); /* filled by aim helpers when present */
    }

    {
      char *unit = (char *)object_get_and_verify_type(aiming_unit, 3);
      float origin[3];
      float dir[3];
      float dummy[3];
      int16_t hit;

      origin[0] = cam_pos[0];
      origin[1] = cam_pos[1];
      origin[2] = cam_pos[2];
      dir[0] = cam_fwd[0] - *(float *)(unit + 0xc);
      dir[1] = cam_fwd[1] - *(float *)(unit + 0x10);
      dir[2] = cam_fwd[2] - *(float *)(unit + 0x14);
      dist = sqrtf(dir[0] * dir[0] + dir[1] * dir[1] + dir[2] * dir[2]);
      normalize3d(cam_fwd);
      origin[0] += cam_fwd[0] * dist;
      origin[1] += cam_fwd[1] * dist;
      origin[2] += cam_fwd[2] * dist;
      scaled_fwd[0] = cam_fwd[0] * *(float *)0x26b0b0;
      scaled_fwd[1] = cam_fwd[1] * *(float *)0x26b0b0;
      scaled_fwd[2] = cam_fwd[2] * *(float *)0x26b0b0;
      FUN_0014df70(0x1000e9, origin, scaled_fwd, *(int *)(player + 0x34), &hit);
      (void)dummy;
      (void)unit;
    }

    cone_axis[0] = cam_fwd[0] - out_position[0];
    cone_axis[1] = cam_fwd[1] - out_position[1];
    cone_axis[2] = cam_fwd[2] - out_position[2];
    if (normalize3d(cone_axis) == 0.0f) {
      cone_axis[0] = aim_direction[0];
      cone_axis[1] = aim_direction[1];
      cone_axis[2] = aim_direction[2];
    }
    FUN_0010c780(delta, cone_axis, *(float *)(aim_buf + 0x18), pinned);
    pin_normal_to_cone3d(pinned, aim_direction, sinf(*(float *)(aim_buf + 0x10)),
                         cosf(*(float *)(aim_buf + 0x10)), aim_direction);
  }

  if (*(int16_t *)0x4761d8 <= 1) {
    display_assert((char *)0x253418, (char *)0x26b08c, 0x8c, 1);
    system_exit(-1);
  }
  *(int16_t *)0x4761d8 = (int16_t)(*(int16_t *)0x4761d8 - 1);
  *(int *)(player + 0x40) = object_handle;
  *(int *)(player + 0x44) = game_time_get();
  return object_handle;
}


void FUN_000a6930(int, unsigned short)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;

  FUN_000a67c0();
  /* cmp eax, -1 -> je 0xa6a7c */
  datum_get((void *)(uintptr_t)eax, 0);
  object_get_and_verify_type(0, 0);
  object_get_world_position(0, (void *)(uintptr_t)edx);
  object_get_orientation(0, (float *)(uintptr_t)edx, (float *)(uintptr_t)ecx);
  /* test (int16_t)eax, (int16_t)eax -> jle 0xa6a7b */
  /* cmp ecx, -1 -> je 0xa6a6e */
  /* test (char)eax, 0x41 -> jne 0xa69cf */
  object_placement_data_new((void *)0, 0, 0);
  object_new((void *)0);
  game_globals_get();
  /* relift: cmp dword ptr [esi], 0 -> je 0xa6ae7 */
  tag_block_get_element((void *)(uintptr_t)esi, 0, 16);
  /* test eax, eax -> je 0xa6ae7 */
  /* relift: cmp dword ptr [esi], 0 -> je 0xa6ad1 */
  tag_block_get_element((void *)(uintptr_t)esi, 0, 16);
  /* relift: tail-call ((void(*)(void))FUN_000a6930)(); */
  /* relift: tail-call ((void(*)(void))FUN_000a6930)(); */
  FUN_001b9b60(0, 0x77656170);
  FUN_001b9b80(0);
  /* cmp eax, -1 -> je 0xa6b2d */
  /* cmp (int16_t)esi, 0x10 -> jae 0xa6b2d */
  FUN_001b9b80(0);
  /* cmp eax, -1 -> jne 0xa6b08 */
  /* relift: tail-call ((void(*)(void))FUN_000a6930)(); */
  game_globals_get();
  /* relift: cmp dword ptr [esi], 0 -> je 0xa6b7f */
  tag_block_get_element((void *)(uintptr_t)esi, 0, 16);
  /* relift: tail-call ((void(*)(void))FUN_000a6930)(); */
  /* relift: tail-call ((void(*)(void))FUN_000a6930)(); */
  game_globals_get();
  /* relift: cmp dword ptr [esi], 0 -> je 0xa6be2 */
  tag_block_get_element((void *)(uintptr_t)esi, 0, 160);
  tag_block_get_element((void *)(uintptr_t)esi, 0, 160);
  /* relift: tail-call ((void(*)(void))FUN_000a6930)(); */
  game_state_malloc((char *)0x0026b198, (char *)0, 276);
  /* mem[0x004566ec] = eax */
  csmemset((void *)(uintptr_t)eax, 0, 276);
  csmemset((void *)0x005aa820, 0, 104);
  real_math_reset_precision();
  game_time_initialize();
  game_engine_initialize((void *)0x005aa820);
  game_allegiance_initialize();
  interface_initialize();
  scenario_initialize();
  director_initialize();
  observer_initialize();
  render_initialize();
  objects_initialize();
  structures_initialize();
  breakable_surfaces_initialize();
  decals_initialize();
  collision_log_initialize();
  players_initialize();
  contrails_initialize();
  particles_initialize();
  effects_initialize();
  weather_particle_systems_initialize();
  particle_systems_initialize();
  sound_classes_initialize();
  game_sound_initialize();
  rumble_initialize();
  player_effect_initialize();
  ai_initialize();
  editor_initialize();
  ui_widgets_initialize();
  hs_initialize();
  recorded_animations_initialize();
  cheats_initialize();
  transport_initialize();
  telnet_console_initialize();
  initialize_network_game_packets();
  cinematic_initialize();
  saved_game_files_initialize();
  event_manager_initialize();
  input_abstraction_initialize();
  player_ui_initialize();
  bink_playback_initialize();
  recorded_animations_dispose();
  cinematic_dispose();
  hs_dispose();
  cheats_dispose();
  ui_widgets_dispose();
  editor_dispose();
  ai_dispose();
  player_effect_dispose();
  rumble_dispose();

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
}

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

