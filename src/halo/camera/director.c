#include <stdint.h>

/* first_person_camera_new (0x88c40) — readable C lift from XBE leaf. */
void first_person_camera_new(int *camera)
{
  extern char DAT_00266e9c[];
  extern char DAT_0026720c[];

  if (camera == 0) {
    display_assert(DAT_00266e9c, DAT_0026720c, 0x18, true);
    system_exit(-1);
  }
  *camera = 0;
}

/* Camera director — controls camera mode per local player.
 *
 * Per-player director state lives in a 0xf8-byte array of 4 entries.
 * There are two "views" into the array used by different functions:
 *   - base 0x3352b4: float timer [+0], void* camera_fn [+4], camera data [+8]
 *   - base 0x3352fc: unknown dword [+0], unknown byte [+4] (= 0x3352b4 + 0x48)
 *
 * Globals:
 *   0x3352a8  float  delta_time (written by director_update)
 *   0x3352ac  int16  director_mode (0=normal, 1=?, 2=editor/scripted, 4=replay)
 *   0x3352ae  uint8  first-update flag (cleared after first camera dispatch)
 *
 * Camera mode functions (pointers stored at player_struct+4):
 *   0x853c0  debug/free camera (only active for one gamepad player at a time)
 *   0x89270  first-person gameplay camera
 *   0x87f20  scripted/editor camera
 *   0x89cd0  transition camera used when returning from a third-person style
 *            view back to gameplay; binary comparison suggests this is the
 *            vehicle-exit blend path, not a pure dead camera
 *
 * Register-arg callees are reached through shims in camera_internal.h. */
#include "camera_internal.h"

/* Allocate director scripting state. */
void director_initialize(void)
{
  *(char **)0x5ab200 = (char *)game_state_malloc("director scripting", 0, 4);
  **(char **)0x5ab200 = 0;
}

/* Dispose — nothing to clean up. */
void director_dispose(void)
{
}

/* Set active local-player context used by hs/console during cheat dispatch.
 * Writes 1 to the per-player director state byte at struct offset +0x4e. */
void director_set_local_player_context(int16_t player_index)
{
  assert_halt(player_index >= 0 &&
              player_index < MAXIMUM_NUMBER_OF_LOCAL_PLAYERS);
  ((char *)0x335302)[(int)player_index * 0xf8] = 1;
}

/*
 * FUN_000865a0 — set player director mode entry fields.
 * Writes param_1 to [base+0x8], 1.0f to [base+0xc4], clears [base+0xc0],
 * and if param_2 is true writes 1.0f to [base+0x4].
 * Base = 0x3352b0 + local_player_index * 0xf8.
 * local_player_index passed in SI.
 *
 * 0x865a0 / director.obj
 */
void FUN_000865a0(int16_t local_player_index, int param_1, bool param_2)
{
  char *base;

  if (local_player_index < 0 ||
      local_player_index >= MAXIMUM_NUMBER_OF_LOCAL_PLAYERS) {
    display_assert("local_player_index>=0 && "
                   "local_player_index<MAXIMUM_NUMBER_OF_LOCAL_PLAYERS",
                   "c:\\halo\\SOURCE\\camera\\director.c", 0xb3, 1);
    system_exit(-1);
  }
  base = (char *)0x3352b0 + (int)local_player_index * 0xf8;
  *(int *)(base + 0x8) = param_1;
  *(int *)(base + 0xc4) = 0x3f800000;
  *(unsigned char *)(base + 0xc0) = 0;
  if (param_2) {
    *(int *)(base + 0x4) = 0x3f800000;
  }
}

/* Per-player default-state init (0x86600). Fills four 12-byte slots at
 * struct offset 0x194/0x1a0/0x1ac/0x1b8 (relative to 0x3352b4 + player*0xf8).
 * Each slot's first dword is seeded from a const table at 0x2ee604 (0x1c
 * stride); the remaining two dwords are zeroed.
 *
 * Original prototype passes the player index in AX — reached via the
 * reverse-thunk codegen in tools/patch.py when the original binary calls
 * 0x86600. Our C signature is plain cdecl. */
void director_init_player_cameras(int16_t local_player_index)
{
  uint32_t *src;
  char *dst;
  int i;

  assert_halt(local_player_index >= 0 &&
              local_player_index < MAXIMUM_NUMBER_OF_LOCAL_PLAYERS);

  src = (uint32_t *)0x2ee604;
  dst = (char *)0x335380 + (int)local_player_index * 0xf8 + 0xd0;

  for (i = 0; i < 4; i++) {
    *(uint32_t *)(dst - 8) = *src;
    *(uint32_t *)dst = 0;
    *(uint32_t *)(dst - 4) = 0;
    src += 7;
    dst += 0xc;
  }
}

/* Reset director state for all 4 players when disposing old map.
 * Per-player data starts at 0x335374 with stride 0xF8 bytes.
 * Offsets verified against disassembly (ESI-relative). */
void director_dispose_from_old_map(void)
{
  int16_t i;
  char *entry = (char *)0x335374;

  for (i = 0; i < 4; i++) {
    assert_halt(i >= 0 && i < MAXIMUM_NUMBER_OF_LOCAL_PLAYERS);
    *(int *)(entry - 0xbc) = 0;
    *(float *)entry = 1.0f;
    *(uint8_t *)(entry - 4) = 0;
    entry += 0xf8;
  }
  **(char **)0x5ab200 = 0;
}

/* Normal-play camera dispatch for one player (mode-0/1, 0x86de0).
 *
 * Three behaviors selected by reset_flag and the player's death state:
 *
 *   1. reset_flag != 0 (forced reset):
 *      Re-init the camera-data block via 0x88c40, install the first-person
 *      camera fn (0x89270), prime the +0xc0 timer to 1.0f, clear the +0xbc
 *      byte. Returns immediately.
 *
 *   2. reset_flag == 0:
 *      Compute is_dead from player_data: dead iff player_data[+0x34] == -1
 *      AND player_data[+0xaa] (signed short) > 0. Then optionally cycle
 *      camera mode (mode_flags), then if no scripted camera state is active,
 *      re-evaluate the active camera and either:
 *        - is_dead && current != vehicle/death-follow camera: install
 *          third-person follow state via 0x85b60 + set camera 0x85c80 with
 *          timer reset.
 *        - !is_dead && current == 0x85c80: call 0x864b0 to classify whether
 *          gameplay should resume directly in first person (0x89270) or
 *          through the transition camera (0x89cd0). The helper also writes a
 *          small state word stored at base+0x50.
 *
 * Ghidra comparison against the original Xbox binary suggests our earlier
 * comments were too death-camera-centric here: 0x864b0 is vehicle/seat-state
 * sensitive, and 0x89cd0 appears to drive the smooth third-person-to-first-
 * person blend seen when exiting a vehicle.
 *
 * Original receives player index in AX, plus two byte stack args —
 * reverse-thunked to plain cdecl by tools/patch.py. */
void director_set_player_camera_normal(int16_t local_player_index,
                                       char reset_flag, char mode_flags)
{
  char *base;
  uint8_t is_dead;
  void *current_camera;
  int player_handle;
  char *player_data;
  int unit_handle;
  int16_t local_word;
  int16_t result;

  assert_halt(local_player_index >= 0 &&
              local_player_index < MAXIMUM_NUMBER_OF_LOCAL_PLAYERS);

  base = (char *)0x3352b4 + (int)local_player_index * 0xf8;

  if (reset_flag != 0) {
    /* 0x88c40: zero camera-data first dword. */
    ((void (*)(void *))0x88c40)((void *)(base + 8));

    assert_halt(local_player_index >= 0 &&
                local_player_index < MAXIMUM_NUMBER_OF_LOCAL_PLAYERS);

    *(uint8_t *)(base + 0xbc) = 0;
    *(uint32_t *)(base + 4) = 0x89270;
    *(float *)(base + 0xc0) = 1.0f;
    return;
  }

  /* Compute is_dead from the player's data record. */
  player_handle = local_player_get_player_index(local_player_index);
  player_data = (char *)datum_get(*(data_t **)0x5aa6d4, player_handle);
  if (*(int *)(player_data + 0x34) != -1) {
    is_dead = 0;
  } else if (*(int16_t *)(player_data + 0xaa) > 0) {
    is_dead = 1;
  } else {
    is_dead = 0;
  }

  if (mode_flags != 0)
    CAMERA_INTERNAL_CYCLE_MODE(local_player_index, 0x266f68, 3);

  /* If a scripted camera is active (script_state[0] != 0), nothing else. */
  if (**(char **)0x5ab200 != 0)
    return;

  camera_internal_reevaluate(local_player_index, 0);

  current_camera = *(void **)(base + 4);

  if (is_dead != 0) {
    if (current_camera == (void *)0x85c80)
      return; /* already in the third-person follow camera */

    /* 0x85b60: cdecl(camera_data_ptr, player_index, init_flag=-1). */
    ((void (*)(void *, int16_t, int))0x85b60)((void *)(base + 8),
                                              local_player_index, -1);
    camera_internal_set_camera_fn(local_player_index, (void *)0x85c80, 1);
    return;
  }

  /* is_dead == 0: only switch back to gameplay camera if we're still in the
   * third-person follow camera. */
  if (current_camera != (void *)0x85c80)
    return;

  assert_halt(local_player_index >= 0 &&
              local_player_index < MAXIMUM_NUMBER_OF_LOCAL_PLAYERS);

  /* 0xb6870: lookup player's unit handle. */
  unit_handle = ((int (*)(int16_t))0xb6870)(local_player_index);

  /* 0x864b0: classify how gameplay should resume from 0x85c80. Binary
   * evidence says this is not just a dead-camera test: it is sensitive to
   * unit/seat state and selects whether we go through 0x89cd0 (transition
   * camera) or straight to 0x89270. It also writes a small state word that we
   * preserve at base+0x50 for the camera pipeline. */
  result = ((int16_t(*)(int, int16_t *))0x864b0)(unit_handle, &local_word);

  if (result == 1) {
    ((void (*)(void *))0x89850)((void *)(base + 8));
    camera_internal_set_camera_fn(local_player_index, (void *)0x89cd0, 0);
  } else {
    ((void (*)(void *))0x88c40)((void *)(base + 8));
    camera_internal_set_camera_fn(local_player_index, (void *)0x89270, 0);
  }

  *(int16_t *)(base + 0x50) = local_word;
}

/* Switch player to scripted/editor camera (mode 2 dispatch, 0x86fa0).
 * If reset_flag is set, or the current camera fn is not already the scripted
 * one (0x87f20), call the scripted-camera initializer at 0x87800 with the
 * per-player camera-data pointer, then install 0x87f20 as the active camera
 * fn, prime the timer at +0xc0 to 1.0f, and clear the byte flag at +0xbc.
 *
 * Original receives player index in SI and reset_flag as a byte stack arg —
 * reverse-thunked to plain cdecl by tools/patch.py. */
void director_set_player_camera_scripted(int16_t local_player_index,
                                         char reset_flag)
{
  char *base;

  assert_halt(local_player_index >= 0 &&
              local_player_index < MAXIMUM_NUMBER_OF_LOCAL_PLAYERS);

  base = (char *)0x3352b4 + (int)local_player_index * 0xf8;

  if (reset_flag != 0 || *(uint32_t *)(base + 4) != 0x87f20) {
    /* 0x87800: scripted-camera init; cdecl(camera_data_ptr, player_index). */
    ((void (*)(void *, int16_t))0x87800)((void *)(base + 8),
                                         local_player_index);

    assert_halt(local_player_index >= 0 &&
                local_player_index < MAXIMUM_NUMBER_OF_LOCAL_PLAYERS);

    *(uint32_t *)(base + 4) = 0x87f20;
    *(float *)(base + 0xc0) = 1.0f;
    *(uint8_t *)(base + 0xbc) = 0;
  }
}

/* Replay-mode dispatch for one player (0x87050).
 * Two cases:
 *   - reset_flag != 0: forcibly install the first-person camera fn at base+4
 *     (using the camera-data init helper at 0x88c40), prime the timer, clear
 *     the reset byte at +0xbc.
 *   - reset_flag == 0 && mode_flags != 0: cycle through replay camera modes
 *     by calling 0x86a50, which expects @eax=player_index, @ebx=mode-table
 *     pointer, and a stack arg = entry count. The mode table at 0x266f70 has
 *     4 short entries.
 *
 * Original receives reset_flag in AL and player index in SI; reverse-thunked
 * to plain cdecl by tools/patch.py. */
void director_apply_replay_mode_for_player(char reset_flag,
                                           int16_t local_player_index,
                                           char mode_flags)
{
  char *base;

  if (reset_flag != 0) {
    assert_halt(local_player_index >= 0 &&
                local_player_index < MAXIMUM_NUMBER_OF_LOCAL_PLAYERS);

    base = (char *)0x3352b4 + (int)local_player_index * 0xf8;

    /* 0x88c40: camera-data init helper (cdecl: camera_data_ptr). */
    ((void (*)(void *))0x88c40)((void *)(base + 8));

    assert_halt(local_player_index >= 0 &&
                local_player_index < MAXIMUM_NUMBER_OF_LOCAL_PLAYERS);

    *(uint32_t *)(base + 4) = 0x89270;
    *(float *)(base + 0xc0) = 1.0f;
    *(uint8_t *)(base + 0xbc) = 0;
    return;
  }

  if (mode_flags != 0)
    CAMERA_INTERNAL_CYCLE_MODE(local_player_index, 0x266f70, 4);
}

/* Build per-player camera input snapshot for one tick (0x87110).
 *
 * Output buffer layout (32-bit fields unless noted):
 *   +0x00 int16  player_index
 *   +0x02 uint8  valid
 *   +0x04 float  delta_time
 *   +0x08 float  forward
 *   +0x0c float  side
 *   +0x10 float  pitch_accumulator
 *   +0x14 float  yaw_accumulator
 *   +0x18 float  roll_accumulator
 *   +0x1c float  zoom_accumulator
 *   +0x20 float  trigger
 *
 * Branches on whether the player has a controllable unit:
 *   - Has unit: derive look/strafe from unit's control state, scaled by
 *     per-player sensitivity (base+0xc0). Returns "valid" derived from the
 *     unit's cinematic byte (+0x14).
 *   - No unit: fall back to gamepad direct-input. The "no unit" branch
 *     calls 0xcf690 which is stubbed to 0 on Xbox, so the fallback body is
 *     dead code on retail — kept faithful to the binary anyway.
 *
 * Original receives the output-buffer pointer in EAX; reverse-thunked to
 * plain cdecl by tools/patch.py. */
bool director_compute_camera_input(short *out_buf, int local_player_index)
{
  int16_t player16 = (int16_t)local_player_index;
  int player_handle;
  char *player_data;
  int unit_handle;
  void *current_camera;
  char *base;

  assert_halt(player16 >= 0 && player16 < MAXIMUM_NUMBER_OF_LOCAL_PLAYERS);

  csmemset(out_buf, 0, 0x24);
  *out_buf = player16;
  *(float *)(out_buf + 2) = *(float *)0x3352a8;

  base = (char *)0x3352b4 + (int)player16 * 0xf8;

  player_handle = local_player_get_player_index(player16);
  player_data = (char *)datum_get(*(data_t **)0x5aa6d4, player_handle);
  unit_handle = (int)*(int16_t *)(player_data + 2);

  if (unit_handle == -1 || input_has_gamepad((int16_t)unit_handle) == 0) {
    /* No unit / unit not playable: gamepad-direct fallback. On Xbox 0xcf690
     * is stubbed to 0, so the inner body never runs. */
    int *gamepad_state = (int *)((void *(*)(void))0xcf690)();
    if (gamepad_state != NULL) {
      bool back_pressed;

      gamepad_state = (int *)((void *(*)(void))0xcf690)();
      back_pressed = input_key_is_down(0x1d);

      if ((current_camera = *(void **)(base + 4),
           current_camera != (void *)0x89270 &&
             *((char *)gamepad_state + 0xd) != 0) ||
          input_key_is_down(0x1e) != 0) {
        uint8_t mode_flags = (input_key_is_down(0x20) != 0) ? 1 : 0;
        if (input_key_is_down(0x2e))
          mode_flags |= 2;
        if (input_key_is_down(0x2d))
          mode_flags |= 4;
        if (input_key_is_down(0x2f))
          mode_flags |= 8;
        if (input_key_is_down(0x22))
          mode_flags |= 0x10;
        if (input_key_is_down(0x30))
          mode_flags |= 0x20;
        if (input_key_is_down(0x23))
          mode_flags |= 0x40;
        if (input_key_is_down(0x31))
          mode_flags |= 0x80;

        camera_internal_integrate(player16, mode_flags,
                                  (float)gamepad_state[2]);

        *(float *)(out_buf + 4) = (float)gamepad_state[0] * *(float *)0x2670a0;
        *(float *)(out_buf + 6) = (float)gamepad_state[1] * *(float *)0x2670a0;
        *(float *)(out_buf + 8) += *(float *)(base + 0xd8);
        *(float *)(out_buf + 0x10) = (float)gamepad_state[2];
        *(float *)(out_buf + 10) += *(float *)(base + 0xe4);
        *(float *)(out_buf + 0xc) += *(float *)(base + 0xf0);
        *(float *)(out_buf + 0xe) += *(float *)(base + 0xcc);
        *((uint8_t *)out_buf + 2) = 1;

        ((void (*)(int))0x86220)(local_player_index);
        ((void (*)(int))0x861d0)(local_player_index);
      }
      return back_pressed == 1;
    }
    return false;
  }

  /* Has unit: pull look/strafe from the unit's control struct. */
  {
    char *unit_data = (char *)input_get_gamepad_state(unit_handle);
    bool valid_unit;

    if (*(char *)0x335690 != 0) {
      valid_unit = (*(char *)(unit_data + 0x14) == 1);
    } else {
      uint8_t cb = *(uint8_t *)(unit_data + 0x14);
      if (cb == 0) {
        valid_unit = false;
      } else if ((unsigned)cb % 0x1e != 0) {
        valid_unit = false;
      } else {
        valid_unit = true;
      }
    }

    current_camera = *(void **)(base + 4);
    if (current_camera == (void *)0x89270 || current_camera == (void *)0x89cd0)
      return valid_unit;

    if (*(char *)(unit_data + 0x1f) == 1)
      *(char *)(base + 0xbc) = (*(char *)(base + 0xbc) == 0);

    if (*(char *)(base + 0xbc) == 0)
      return valid_unit;

    {
      uint8_t mode_flags = (*(char *)(unit_data + 0x17) != 0) ? 0x10 : 0;
      float trigger;

      if (*(char *)(unit_data + 0x16) != 0)
        mode_flags |= 0x20;

      trigger = (float)((int)((unsigned)(1 < *(uint8_t *)(unit_data + 0x18)) -
                              (unsigned)(1 < *(uint8_t *)(unit_data + 0x19)))) *
                *(float *)0x253524;

      *(float *)(out_buf + 0x10) = trigger;
      camera_internal_integrate(player16, mode_flags, trigger);

      *(float *)(out_buf + 4) = (float)(int)*(int16_t *)(unit_data + 0x24) *
                                *(float *)0x3352a8 * *(float *)0x2670b0;
      *(float *)(out_buf + 6) = (float)(int)*(int16_t *)(unit_data + 0x26) *
                                *(float *)0x3352a8 * *(float *)0x2670ac;
      *(float *)(out_buf + 10) = (float)(int)*(int16_t *)(unit_data + 0x22) *
                                 *(float *)(base + 0xc0) * *(float *)0x3352a8 *
                                 *(float *)0x2670a8;
      *(float *)(out_buf + 0xc) = (float)(int)*(int16_t *)(unit_data + 0x20) *
                                  *(float *)(base + 0xc0) * *(float *)0x3352a8 *
                                  *(float *)0x2670a4;

      *(float *)(out_buf + 0xe) += *(float *)(base + 0xcc);
      *((uint8_t *)out_buf + 2) = 1;

      ((void (*)(int))0x86220)(local_player_index);
      ((void (*)(int))0x861d0)(local_player_index);
    }

    return valid_unit;
  }
}

/*
 * FUN_000874d0 — dispatch per-player camera update based on director mode.
 *
 * Reads the global director mode from 0x3352ac (short) and calls the
 * appropriate per-player camera function:
 *   mode 0, 1 → director_set_player_camera_normal(local_player_index,
 * reset_flag, mode_flags) mode 2    →
 * director_set_player_camera_scripted(local_player_index, reset_flag) mode 4 →
 * director_apply_replay_mode_for_player(reset_flag, local_player_index,
 * mode_flags) other     → no-op
 *
 * local_player_index, reset_flag, mode_flags.
 *
 * 0x874d0 / director.obj
 */
void FUN_000874d0(int16_t local_player_index, char reset_flag, char mode_flags)
{
  switch (*(int16_t *)0x3352ac) {
  case 0:
  case 1:
    director_set_player_camera_normal(local_player_index, reset_flag,
                                      mode_flags);
    return;
  case 2:
    director_set_player_camera_scripted(local_player_index, reset_flag);
    return;
  case 4:
    director_apply_replay_mode_for_player(reset_flag, local_player_index,
                                          mode_flags);
    return;
  default:
    return;
  }
}

/* Set director mode and reset per-player camera state for a new map.
 * Director mode is 2 (scripted) in editor, 0 (normal) otherwise.
 * For each player: zeros timer, two unknown fields, then dispatches to the
 * mode-specific camera initializer and runs the per-player data init. */
void director_initialize_for_new_map(void)
{
  int16_t i;
  char *p;

  /* director mode: 0 = normal gameplay, 2 = editor (scripted camera) */
  *(int16_t *)0x3352ac = game_in_editor() ? 2 : 0;
  *(uint8_t *)0x3352ae = 0;

  /* p points into the per-player array at offset 0x48 from the struct base */
  p = (char *)0x3352fc;
  for (i = 0; i < 4; i++) {
    assert_halt(i >= 0 && i < MAXIMUM_NUMBER_OF_LOCAL_PLAYERS);

    /* zero offset-0x48 field (dword), offset-0x4c field (byte), and the
     * timer at offset-0x00 (= p - 0x48) */
    *(uint32_t *)p = 0;
    *(uint8_t *)(p + 4) = 0;
    *(uint32_t *)(p - 0x48) = 0; /* timer field at struct base */

    switch (*(int16_t *)0x3352ac) {
    case 0:
    case 1:
      camera_internal_set_mode_0_1(i, 1, 0);
      break;
    case 2:
      camera_internal_set_mode_2(i, 1, 0);
      break;
    case 4:
      camera_internal_set_mode_4(1, i, 0);
      break;
    }

    camera_internal_init_player(i);

    p += 0xf8;
  }
}

/* Update all active local players' cameras for this tick.
 * Stores delta_time, polls input via 0x87110, dispatches per-mode camera
 * update, runs the active camera function, then commits the result to the
 * observer.
 *
 * The active camera function is where the transition-camera path starts, but
 * not where it finishes: the camera output block copied to ps+0x54 is later
 * consumed by observer-side code which seeds and integrates several per-axis
 * blend timers. That observer stage is what makes the vehicle-exit return to
 * first person feel smooth in the original binary. */
void director_update(float delta_time)
{
  int i;
  uint8_t mode_flags;
  uint8_t local_98[36]; /* camera input buffer (written by 0x87110) */
  uint8_t local_74[0x68]; /* camera output buffer (written by camera_fn) */
  char *ps; /* per-player struct base (0xf8-byte stride) */

  *(float *)0x3352a8 = delta_time;
  i = 0;
  ps = (char *)0x3352b4;

  do {
    if (local_player_get_player_index((int16_t)i) != -1) {
      assert_halt((int16_t)i >= 0 &&
                  (int16_t)i < MAXIMUM_NUMBER_OF_LOCAL_PLAYERS);

      ps[0x4d] = 0;
      ps[0x4e] = 0;

      mode_flags = camera_internal_poll_input(local_98, i);

      {
        uint8_t rst = *(uint8_t *)0x3352ae;
        switch (*(int16_t *)0x3352ac) {
        case 0:
        case 1:
          camera_internal_set_mode_0_1((int16_t)i, rst, mode_flags);
          break;
        case 2:
          camera_internal_set_mode_2((int16_t)i, rst, mode_flags);
          break;
        case 4:
          camera_internal_set_mode_4(rst, (int16_t)i, mode_flags);
          break;
        }
      }

      /* clear first-update flag after camera mode dispatch */
      *(uint8_t *)0x3352ae = 0;

      csmemset(local_74, 0, 0x68);

      /* call the per-player camera update function if set */
      {
        void (*camera_fn)(void *, void *, void *) =
          *(void (**)(void *, void *, void *))(ps + 4);
        if (camera_fn != NULL) {
          /* the debug camera (0x853c0) only runs for the active gamepad player
           */
          if ((void *)camera_fn != (void *)0x853c0 ||
              (int16_t)i == local_player_get_next(-1)) {
            camera_fn(ps + 8, local_98, local_74);
          }
        }
      }

      if (!(local_74[0] & 1)) {
        /* camera produced no valid output — clear the valid bit */
        *(uint32_t *)(ps + 0x54) &= ~1U;
      } else {
        float *timer = (float *)ps; /* timer at struct offset 0 */
        if (*timer != 0.0f) {
          if (*(float *)0x2549d4 <= *timer ||
              *(void **)(ps + 4) != (void *)0x89270) {
            /* track max timer in local_74[0x48] — this lives inside the
             * camera output buffer so it's passed to the observer via
             * the qmemcpy into ps+0x54. The observer uses it to drive
             * the smooth camera blend. */
            if (*(float *)(local_74 + 0x48) <= *timer)
              *(float *)(local_74 + 0x48) = *timer;
          } else {
            /* reset camera when timer underflows threshold with fp camera.
             * The writes below seed transition flags and timers in the camera
             * output buffer (local_74) at offsets 0x4c/0x4e (flag bytes = 3)
             * and 0x54/0x5c (timer floats = 0). The observer consumes these
             * to drive the smooth third-person-to-first-person blend. */
            *timer = 0.0f;
            *(uint32_t *)(local_74 + 0x54) = 0;
            *(uint8_t *)(local_74 + 0x4c) = 3;
            *(uint32_t *)(local_74 + 0x5c) = 0;
            *(uint8_t *)(local_74 + 0x4e) = 3;
          }
          /* count down timer, clamped to zero */
          {
            float next = *timer - delta_time;
            *timer = next < 0.0f ? 0.0f : next;
          }
        }
        /* copy 0x68 bytes of camera output into the per-player camera slot */
        qmemcpy(ps + 0x54, local_74, 0x68);
      }

      /* commit camera data to the observer subsystem */
      ((void (*)(int16_t, void *))0x8acb0)((int16_t)i, ps + 0x54);
    }

    i++;
    ps += 0xf8;
  } while ((int16_t)i < 4);
}
/* --- director.obj batch drafts (2026-07-26) --- */

/* FUN_00085a40 (0x85a40) — readable C lift from XBE leaf.
 * Returns true if another player datum shares field +0x20 with handle. */
char FUN_00085a40(int handle)
{
  data_iter_t iter;
  void *self;
  void *cur;
  int field20;

  self = datum_get(*(data_t **)0x5aa6d4, handle);
  field20 = *(int *)((char *)self + 0x20);
  data_iterator_new(&iter, *(data_t **)0x5aa6d4);
  for (cur = data_iterator_next(&iter); cur != (void *)0; cur = data_iterator_next(&iter)) {
    if ((int)iter.datum_handle != handle) {
      if (*(int *)((char *)cur + 0x20) == field20) {
        return 1;
      }
    }
  }
  return 0;
}



/* FUN_00085ab0 (0x85ab0) — readable C lift from XBE leaf. */
int FUN_00085ab0(int exclude_handle, int fallback, char require_field_match)
{
  data_iter_t iter;
  void *cur;
  int match_field;
  int best;
  int h;

  if (require_field_match) {
    cur = datum_get(*(data_t **)0x5aa6d4, exclude_handle);
    match_field = *(int *)((char *)cur + 0x20);
  } else {
    match_field = -1;
  }
  data_iterator_new(&iter, *(data_t **)0x5aa6d4);
  best = -1;
  for (cur = data_iterator_next(&iter); cur != (void *)0; cur = data_iterator_next(&iter)) {
    h = (int)iter.datum_handle;
    if (h == exclude_handle) {
      continue;
    }
    if (*(int *)((char *)cur + 0x34) == -1) {
      continue;
    }
    if (require_field_match) {
      if (*(int *)((char *)cur + 0x20) != match_field) {
        continue;
      }
    }
    if (best == -1) {
      best = h;
      continue;
    }
    if ((h & 0xffff) > (fallback & 0xffff)) {
      best = h;
      break;
    }
  }
  if (best != -1) {
    return best;
  }
  return fallback;
}



/* FUN_00085b60 (0x85b60) — XBE naked draft (batch 129). */
#if defined(__clang__)
static void * (*const b85b60_c8a4e0)(unsigned __int16 local_player_index) = observer_get_camera;
static void (*const b85b60_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b85b60_exitfn)(int) = system_exit;
static unsigned int *(*const b85b60_lseed)(void) = random_math_get_local_seed_address;
static float (*const b85b60_rrange)(int *, float, float) = random_real_range;
static bool (*const b85b60_gerun)(void) = game_engine_running;
static int (*const b85b60_cba3c0)(int16_t local_player_index) = local_player_get_player_index;
static void *(*const b85b60_dget)(void *, int) = (void *(*)(void *, int))datum_get;

__attribute__((naked, noinline))
void FUN_00085b60(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ebx\n\t"
      "movl 0xc(%%ebp), %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "call *%[c8a4e0]\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "addl $4, %%esp\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%eax, %%edi\n\t"
      "jne .LFUN_00085b60_1\n\t"
      "pushl $1\n\t"
      "pushl $0x17\n\t"
      "pushl $0x266f44\n\t"
      "pushl $0x266e9c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00085b60_1:\n\t"
      "movl (%%edi), %%ecx\n\t"
      "movl %%esi, %%eax\n\t"
      "movl %%ecx, (%%eax)\n\t"
      "movl 0x4(%%edi), %%edx\n\t"
      "movl %%edx, 0x4(%%eax)\n\t"
      "movl 0x8(%%edi), %%ecx\n\t"
      "pushl $0x40c00000\n\t"
      "pushl $0x40000000\n\t"
      "movl %%ecx, 0x8(%%eax)\n\t"
      "movl $0x3f9c61aa, 0x18(%%esi)\n\t"
      "call *%[lseed]\n\t"
      "pushl %%eax\n\t"
      "call *%[rrange]\n\t"
      "addl $0xc, %%esp\n\t"
      "pushl $0x40c90fdb\n\t"
      "fstps 0x14(%%esi)\n\t"
      "pushl $0\n\t"
      "call *%[lseed]\n\t"
      "pushl %%eax\n\t"
      "call *%[rrange]\n\t"
      "addl $0xc, %%esp\n\t"
      "pushl $0x3f8cbe4c\n\t"
      "fstps 0xc(%%esi)\n\t"
      "pushl $0x3ef1463b\n\t"
      "call *%[lseed]\n\t"
      "pushl %%eax\n\t"
      "call *%[rrange]\n\t"
      "movl 0x10(%%ebp), %%edi\n\t"
      "movl 0x266f38, %%edx\n\t"
      "fchs\n\t"
      "addl $0xc, %%esp\n\t"
      "fstps 0x10(%%esi)\n\t"
      "cmpl $-1, %%edi\n\t"
      "movl %%edx, 0x1c(%%esi)\n\t"
      "je .LFUN_00085b60_2\n\t"
      "flds 0x2548fc\n\t"
      "jmp .LFUN_00085b60_4\n\t"
      ".LFUN_00085b60_2:\n\t"
      "call *%[gerun]\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00085b60_3\n\t"
      "flds 0x266f3c\n\t"
      "jmp .LFUN_00085b60_4\n\t"
      ".LFUN_00085b60_3:\n\t"
      "flds 0x266f40\n\t"
      ".LFUN_00085b60_4:\n\t"
      "pushl %%ebx\n\t"
      "fstps 0x2c(%%esi)\n\t"
      "call *%[cba3c0]\n\t"
      "addl $4, %%esp\n\t"
      "cmpl $-1, %%edi\n\t"
      "movl %%eax, 0x20(%%esi)\n\t"
      "jne .LFUN_00085b60_5\n\t"
      "pushl %%eax\n\t"
      "movl 0x5aa6d4, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl 0x38(%%eax), %%eax\n\t"
      "movl 0x20(%%esi), %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "popl %%edi\n\t"
      "movl %%eax, 0x28(%%esi)\n\t"
      "movl %%ecx, 0x24(%%esi)\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00085b60_5:\n\t"
      "movl 0x20(%%esi), %%ecx\n\t"
      "movl %%edi, %%eax\n\t"
      "popl %%edi\n\t"
      "movl %%eax, 0x28(%%esi)\n\t"
      "movl %%ecx, 0x24(%%esi)\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c8a4e0] "m"(b85b60_c8a4e0), [assert] "m"(b85b60_assert), [exitfn] "m"(b85b60_exitfn), [lseed] "m"(b85b60_lseed), [rrange] "m"(b85b60_rrange), [gerun] "m"(b85b60_gerun), [cba3c0] "m"(b85b60_cba3c0), [dget] "m"(b85b60_dget)
      : "memory");
}
#else
#error "FUN_00085b60: clang naked draft required"
#endif


/* FUN_00085c80 (0x85c80) — XBE naked draft (batch 106). */
#if defined(__clang__)
static void *(*const b85c80_tryget)(int, int) = object_try_and_get_and_verify_type;
static void (*const b85c80_c10cc40)(float *out, float *angles) = angles_to_vector;
static void (*const b85c80_c8aa80)(float *forward, float *up) = observer_up_from_forward;
static bool (*const b85c80_cb5c30)(void) = game_time_get_paused;
static char (*const b85c80_c85a40)(int) = FUN_00085a40;
static void (*const b85c80_c85ab0)(void) = (void (*)(void))FUN_00085ab0;
static void *(*const b85c80_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static bool (*const b85c80_gerun)(void) = game_engine_running;
static bool (*const b85c80_c84a70)(float *a, float *b) = valid_real_normal3d_perpendicular;
static int (*const b85c80_c84a10)(float *vector) = real_vector3d_valid;
static char * (*const b85c80_c8d9d0)(char *buffer, const char *format, ...) = csprintf;
static void (*const b85c80_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b85c80_exitfn)(int) = system_exit;

__attribute__((naked, noinline))
void FUN_00085c80(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ebx\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "movl 0x28(%%ebx), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "je .LFUN_00085c80_1\n\t"
      "pushl $-1\n\t"
      "pushl %%eax\n\t"
      "call *%[tryget]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_00085c80_1\n\t"
      "movl 0x10(%%ebp), %%esi\n\t"
      "addl $0x50, %%eax\n\t"
      "movl (%%eax), %%edx\n\t"
      "leal 0x4(%%esi), %%ecx\n\t"
      "movl %%edx, (%%ecx)\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl %%edx, 0x4(%%ecx)\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl %%eax, 0x8(%%ecx)\n\t"
      "jmp .LFUN_00085c80_2\n\t"
      ".LFUN_00085c80_1:\n\t"
      "movl 0x10(%%ebp), %%esi\n\t"
      "movl %%ebx, %%ecx\n\t"
      "movl (%%ecx), %%edx\n\t"
      "leal 0x4(%%esi), %%eax\n\t"
      "movl %%edx, (%%eax)\n\t"
      "movl 0x4(%%ecx), %%edx\n\t"
      "movl %%edx, 0x4(%%eax)\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "movl %%ecx, 0x8(%%eax)\n\t"
      ".LFUN_00085c80_2:\n\t"
      "movl 0x14(%%ebx), %%edx\n\t"
      "leal 0xc(%%ebx), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal 0x24(%%esi), %%edi\n\t"
      "pushl %%edi\n\t"
      "movl %%edx, 0x1c(%%esi)\n\t"
      "call *%[c10cc40]\n\t"
      "leal 0x30(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "call *%[c8aa80]\n\t"
      "flds 0x2533c0\n\t"
      "movl 0x18(%%ebx), %%ecx\n\t"
      "movl %%ecx, 0x20(%%esi)\n\t"
      "movl 0x31fc38, %%edx\n\t"
      "movl (%%edx), %%ecx\n\t"
      "leal 0x10(%%esi), %%eax\n\t"
      "movl %%ecx, (%%eax)\n\t"
      "movl 0x4(%%edx), %%ecx\n\t"
      "movl %%ecx, 0x4(%%eax)\n\t"
      "movl 0x8(%%edx), %%edx\n\t"
      "movl %%edx, 0x8(%%eax)\n\t"
      "movl 0x31fc38, %%ecx\n\t"
      "movl (%%ecx), %%edx\n\t"
      "leal 0x3c(%%esi), %%eax\n\t"
      "movl %%edx, (%%eax)\n\t"
      "movl 0x4(%%ecx), %%edx\n\t"
      "movl %%edx, 0x4(%%eax)\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "movl %%ecx, 0x8(%%eax)\n\t"
      "movl $1, (%%esi)\n\t"
      "fcomps 0x1c(%%ebx)\n\t"
      "addl $0x10, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00085c80_3\n\t"
      "flds 0x2533c0\n\t"
      "jmp .LFUN_00085c80_4\n\t"
      ".LFUN_00085c80_3:\n\t"
      "flds 0x1c(%%ebx)\n\t"
      ".LFUN_00085c80_4:\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "fstps 0x48(%%esi)\n\t"
      "movb $3, %%dl\n\t"
      "movl %%ecx, 0x54(%%esi)\n\t"
      "movb %%dl, 0x4c(%%esi)\n\t"
      "flds 0x1c(%%ebx)\n\t"
      "fcomps 0x266f38\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .LFUN_00085c80_5\n\t"
      "movl $0x3f000000, 0x1c(%%esi)\n\t"
      "movl %%ecx, 0x5c(%%esi)\n\t"
      "movb %%dl, 0x4e(%%esi)\n\t"
      ".LFUN_00085c80_5:\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "flds 0x1c(%%ebx)\n\t"
      "fsubs 0x4(%%eax)\n\t"
      "fstps 0x1c(%%ebx)\n\t"
      "flds 0x2c(%%ebx)\n\t"
      "fsubs 0x4(%%eax)\n\t"
      "flds 0x2533c0\n\t"
      "fcomp %%st(1)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00085c80_6\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c0\n\t"
      ".LFUN_00085c80_6:\n\t"
      "fsts 0x2c(%%ebx)\n\t"
      "flds 0x2533c0\n\t"
      "fcomp %%st(1)\n\t"
      "fnstsw %%ax\n\t"
      "fstp %%st(0)\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .LFUN_00085c80_12\n\t"
      "call *%[cb5c30]\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00085c80_12\n\t"
      "movl 0x20(%%ebx), %%edi\n\t"
      "call *%[c85a40]\n\t"
      "movl 0x24(%%ebx), %%edx\n\t"
      "movl 0x20(%%ebx), %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ecx\n\t"
      "movb %%al, %%bl\n\t"
      "call *%[c85ab0]\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "movl %%eax, 0x24(%%edi)\n\t"
      "je .LFUN_00085c80_7\n\t"
      "movl 0x5aa6d4, %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%edx\n\t"
      "call *%[dget]\n\t"
      "movl 0x34(%%eax), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "jmp .LFUN_00085c80_8\n\t"
      ".LFUN_00085c80_7:\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      ".LFUN_00085c80_8:\n\t"
      "cmpl 0x28(%%edi), %%eax\n\t"
      "je .LFUN_00085c80_9\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_00085c80_9\n\t"
      "movl 0x266f38, %%ecx\n\t"
      "movl %%ecx, 0x1c(%%edi)\n\t"
      "movl %%eax, 0x28(%%edi)\n\t"
      ".LFUN_00085c80_9:\n\t"
      "call *%[gerun]\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00085c80_10\n\t"
      "flds 0x266f3c\n\t"
      "jmp .LFUN_00085c80_11\n\t"
      ".LFUN_00085c80_10:\n\t"
      "flds 0x266f40\n\t"
      ".LFUN_00085c80_11:\n\t"
      "fstps 0x2c(%%edi)\n\t"
      ".LFUN_00085c80_12:\n\t"
      "movl (%%esi), %%ebx\n\t"
      "testb $1, %%bl\n\t"
      "je .LFUN_00085c80_14\n\t"
      "leal 0x30(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal 0x24(%%esi), %%edi\n\t"
      "pushl %%edi\n\t"
      "call *%[c84a70]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00085c80_13\n\t"
      "movl 0x4(%%esi), %%edx\n\t"
      "movl %%edx, %%eax\n\t"
      "andl $0x7f800000, %%eax\n\t"
      "cmpl $0x7f800000, %%eax\n\t"
      "movl %%edx, 0x10(%%ebp)\n\t"
      "je .LFUN_00085c80_13\n\t"
      "flds 0x4(%%esi)\n\t"
      "fcomps 0x266e98\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_00085c80_13\n\t"
      "flds 0x4(%%esi)\n\t"
      "fcomps 0x266e94\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .LFUN_00085c80_13\n\t"
      "movl 0x8(%%esi), %%ecx\n\t"
      "movl %%ecx, %%edx\n\t"
      "andl $0x7f800000, %%edx\n\t"
      "cmpl $0x7f800000, %%edx\n\t"
      "movl %%ecx, 0x10(%%ebp)\n\t"
      "je .LFUN_00085c80_13\n\t"
      "flds 0x8(%%esi)\n\t"
      "fcomps 0x266e98\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_00085c80_13\n\t"
      "flds 0x8(%%esi)\n\t"
      "fcomps 0x266e94\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .LFUN_00085c80_13\n\t"
      "movl 0xc(%%esi), %%eax\n\t"
      "movl %%eax, %%ecx\n\t"
      "andl $0x7f800000, %%ecx\n\t"
      "cmpl $0x7f800000, %%ecx\n\t"
      "movl %%eax, 0x10(%%ebp)\n\t"
      "je .LFUN_00085c80_13\n\t"
      "flds 0xc(%%esi)\n\t"
      "fcomps 0x266e98\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_00085c80_13\n\t"
      "flds 0xc(%%esi)\n\t"
      "fcomps 0x266e94\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .LFUN_00085c80_13\n\t"
      "movl 0x10(%%esi), %%edx\n\t"
      "movl %%edx, %%eax\n\t"
      "andl $0x7f800000, %%eax\n\t"
      "cmpl $0x7f800000, %%eax\n\t"
      "movl %%edx, 0x10(%%ebp)\n\t"
      "je .LFUN_00085c80_13\n\t"
      "flds 0x10(%%esi)\n\t"
      "fcomps 0x266e98\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_00085c80_13\n\t"
      "flds 0x10(%%esi)\n\t"
      "fcomps 0x266e94\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .LFUN_00085c80_13\n\t"
      "movl 0x14(%%esi), %%ecx\n\t"
      "movl %%ecx, %%edx\n\t"
      "andl $0x7f800000, %%edx\n\t"
      "cmpl $0x7f800000, %%edx\n\t"
      "movl %%ecx, 0x10(%%ebp)\n\t"
      "je .LFUN_00085c80_13\n\t"
      "flds 0x14(%%esi)\n\t"
      "fcomps 0x266e98\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_00085c80_13\n\t"
      "flds 0x14(%%esi)\n\t"
      "fcomps 0x266e94\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .LFUN_00085c80_13\n\t"
      "movl 0x18(%%esi), %%eax\n\t"
      "movl %%eax, %%ecx\n\t"
      "andl $0x7f800000, %%ecx\n\t"
      "cmpl $0x7f800000, %%ecx\n\t"
      "movl %%eax, 0x10(%%ebp)\n\t"
      "je .LFUN_00085c80_13\n\t"
      "flds 0x18(%%esi)\n\t"
      "fcomps 0x266e98\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_00085c80_13\n\t"
      "flds 0x18(%%esi)\n\t"
      "fcomps 0x266e94\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .LFUN_00085c80_13\n\t"
      "leal 0x3c(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c84a10]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00085c80_13\n\t"
      "movl 0x1c(%%esi), %%edx\n\t"
      "movl %%edx, %%eax\n\t"
      "andl $0x7f800000, %%eax\n\t"
      "cmpl $0x7f800000, %%eax\n\t"
      "movl %%edx, 0x10(%%ebp)\n\t"
      "je .LFUN_00085c80_13\n\t"
      "flds 0x1c(%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_00085c80_13\n\t"
      "flds 0x1c(%%esi)\n\t"
      "fcomps 0x266e94\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .LFUN_00085c80_13\n\t"
      "movl 0x20(%%esi), %%ecx\n\t"
      "movl %%ecx, %%edx\n\t"
      "andl $0x7f800000, %%edx\n\t"
      "cmpl $0x7f800000, %%edx\n\t"
      "movl %%ecx, 0x10(%%ebp)\n\t"
      "je .LFUN_00085c80_13\n\t"
      "flds 0x20(%%esi)\n\t"
      "fcomps 0x255ef8\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_00085c80_13\n\t"
      "flds 0x20(%%esi)\n\t"
      "fcomps 0x2568bc\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .LFUN_00085c80_13\n\t"
      "movl 0x48(%%esi), %%eax\n\t"
      "movl %%eax, %%ecx\n\t"
      "andl $0x7f800000, %%ecx\n\t"
      "cmpl $0x7f800000, %%ecx\n\t"
      "movl %%eax, 0x10(%%ebp)\n\t"
      "je .LFUN_00085c80_13\n\t"
      "flds 0x48(%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_00085c80_13\n\t"
      "flds 0x48(%%esi)\n\t"
      "fcomps 0x266e90\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jnp .LFUN_00085c80_14\n\t"
      ".LFUN_00085c80_13:\n\t"
      "flds 0x48(%%esi)\n\t"
      "pushl $1\n\t"
      "pushl $0x9e\n\t"
      "pushl $0x266f44\n\t"
      "pushl %%ebx\n\t"
      "subl $0x90, %%esp\n\t"
      "fstpl 0x88(%%esp)\n\t"
      "flds 0x20(%%esi)\n\t"
      "fstpl 0x80(%%esp)\n\t"
      "flds 0x44(%%esi)\n\t"
      "fstpl 0x78(%%esp)\n\t"
      "flds 0x40(%%esi)\n\t"
      "fstpl 0x70(%%esp)\n\t"
      "flds 0x3c(%%esi)\n\t"
      "fstpl 0x68(%%esp)\n\t"
      "flds 0x1c(%%esi)\n\t"
      "fstpl 0x60(%%esp)\n\t"
      "flds 0x18(%%esi)\n\t"
      "fstpl 0x58(%%esp)\n\t"
      "flds 0x14(%%esi)\n\t"
      "fstpl 0x50(%%esp)\n\t"
      "flds 0x10(%%esi)\n\t"
      "fstpl 0x48(%%esp)\n\t"
      "flds 0xc(%%esi)\n\t"
      "fstpl 0x40(%%esp)\n\t"
      "flds 0x8(%%esi)\n\t"
      "fstpl 0x38(%%esp)\n\t"
      "flds 0x4(%%esi)\n\t"
      "fstpl 0x30(%%esp)\n\t"
      "flds 0x38(%%esi)\n\t"
      "fstpl 0x28(%%esp)\n\t"
      "flds 0x34(%%esi)\n\t"
      "fstpl 0x20(%%esp)\n\t"
      "flds 0x30(%%esi)\n\t"
      "fstpl 0x18(%%esp)\n\t"
      "flds 0x2c(%%esi)\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds 0x28(%%esi)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds (%%edi)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x266e08\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x9c, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00085c80_14:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [tryget] "m"(b85c80_tryget), [c10cc40] "m"(b85c80_c10cc40), [c8aa80] "m"(b85c80_c8aa80), [cb5c30] "m"(b85c80_cb5c30), [c85a40] "m"(b85c80_c85a40), [c85ab0] "m"(b85c80_c85ab0), [dget] "m"(b85c80_dget), [gerun] "m"(b85c80_gerun), [c84a70] "m"(b85c80_c84a70), [c84a10] "m"(b85c80_c84a10), [c8d9d0] "m"(b85c80_c8d9d0), [assert] "m"(b85c80_assert), [exitfn] "m"(b85c80_exitfn)
      : "memory");
}
#else
#error "FUN_00085c80: clang naked draft required"
#endif


/* director_inhibit_facing (0x861d0) — readable C lift from XBE leaf. */
void director_inhibit_facing(short user_index)
{
  extern char DAT_00266fc0[];
  extern char DAT_0026700c[];

  if (user_index < 0 || user_index >= 4) {
    display_assert(DAT_00266fc0, DAT_0026700c, 0xb3, true);
    system_exit(-1);
  }
  *((unsigned char *)0x335301 + (int)user_index * 0xf8) = 1;
}



/* director_inhibited_facing (0x86270) — readable C lift. */
uint8_t director_inhibited_facing(int16_t a0)
{
  if ((int16_t)a0 < 0 || (int16_t)a0 >= 4) {
    display_assert((const char *)0x266fc0, (const char *)0x26700c, 0xb3, 1);
    system_exit(-1);
  }
  return *(uint8_t *)(0x335301 + (int)(int16_t)a0 * 0xf8);
}

/* director_inhibited_input (0x862c0) — readable C lift. */
uint8_t director_inhibited_input(int16_t a0)
{
  if ((int16_t)a0 < 0 || (int16_t)a0 >= 4) {
    display_assert((const char *)0x266fc0, (const char *)0x26700c, 0xb3, 1);
    system_exit(-1);
  }
  return *(uint8_t *)(0x335302 + (int)(int16_t)a0 * 0xf8);
}

/* director_set_mode (0x86310) — readable C lift. */
void director_set_mode(int16_t a0)
{
  if ((int16_t)a0 < 0 || (int16_t)a0 >= 5) {
    display_assert((const char *)0x267044, (const char *)0x26700c, 0x180, 1);
    system_exit(-1);
  }
  if (*(int16_t *)0x3352ac != (int16_t)a0) {
    *(int16_t *)0x3352ac = (int16_t)a0;
    *(uint8_t *)0x3352ae = 1;
  }
}

/* director_save_camera (0x86360) — readable C lift from XBE leaf. */
void director_save_camera(void)
{
  extern char DAT_00265938[];
  extern char DAT_00267084[];
  extern char DAT_00267078[];
  extern char DAT_00267074[];
  void *stream;
  float *cam;

  stream = crt_fopen(DAT_00267084, DAT_00265938);
  if (!stream)
    return;
  cam = (float *)observer_get_camera(0);
  crt_fprintf(stream, DAT_00267078, (double)cam[0], (double)cam[1], (double)cam[2]);
  crt_fprintf(stream, DAT_00267078, (double)cam[8], (double)cam[9], (double)cam[10]);
  crt_fprintf(stream, DAT_00267078, (double)cam[11], (double)cam[12], (double)cam[13]);
  crt_fprintf(stream, DAT_00267074, (double)cam[14]);
  crt_fclose(stream);
}


/* director_get_perspective (0x86410) — readable C lift. */
int16_t director_get_perspective(int16_t local_player_index)
{
  char *slot;
  int fn;

  if (local_player_index < 0 || local_player_index >= 4) {
    display_assert((const char *)0x266fc0, (const char *)0x26700c, 0xb3, true);
    system_exit(-1);
  }
  slot = (char *)0x3352b0 + (int)local_player_index * 0xf8;
  fn = *(int *)(slot + 8);
  if (fn == 0x89270) {
    if (*(float *)(slot + 4) == *(float *)0x2533c0) {
      *(int16_t *)(slot + 0x56) = 0;
      return 0;
    }
    return *(int16_t *)(slot + 0x56);
  }
  if (fn == 0x89cd0) {
    *(int16_t *)(slot + 0x56) = 1;
    return 1;
  }
  *(int16_t *)(slot + 0x56) = (int16_t)(2 + (fn != 0x853c0));
  return *(int16_t *)(slot + 0x56);
}

/* director_desired_perspective (0x864b0) — readable C lift. */
short director_desired_perspective(int unit_handle, short *out_perspective)
{
  char *unit;
  int parent;
  char *parent_obj;
  void *seat;
  unsigned int flags;
  char state;
  short result;

  result = 0;
  *out_perspective = 0;
  if (unit_handle == -1) {
    return result;
  }
  unit = (char *)object_get_and_verify_type(unit_handle, 3);
  parent = *(int *)(unit + 0xcc);
  if (parent == -1) {
    if (*out_perspective == 1 || *out_perspective == 3) {
      return 1;
    }
    return result;
  }
  parent_obj = (char *)object_get_and_verify_type(parent, -1);
  if (((1 << *(unsigned char *)(parent_obj + 0x64)) & 3) == 0) {
    *out_perspective = 2;
    return result;
  }
  seat = tag_block_get_element(
      (char *)tag_get(0x756e6974, *(int *)parent_obj) + 0x2e4,
      (int)*(short *)(unit + 0x2a0),
      0x11c);
  flags = *(unsigned int *)seat;
  if (flags & 0x10) {
    result = 1;
  }
  if (((flags >> 6) & 1) == 0) {
    *out_perspective = 2;
    return result;
  }
  state = *(char *)(unit + 0x253);
  if (state == 0x1a) {
    *out_perspective = 1;
    return 1;
  }
  if (state == 0x1b) {
    *out_perspective = 3;
    return 1;
  }
  *out_perspective = 2;
  return result;
}
void FUN_00086670(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;

  /* cmp (int16_t)esi, 4 -> jl 0x866a7 */
  display_assert((char *)0x00266fc0, (char *)0x0026700c, 179, 0);
  system_exit(0);
  FUN_001d9e70(0.0f, 0.0f);
  /* test (char)eax, 0x41 -> jne 0x866ff */
  /* test (char)eax, (char)eax -> je 0x86731 */
  /* test (char)eax, 0x41 -> jne 0x8676f */
  /* test ebx, eax -> jne 0x86795 */
  /* cmp (int16_t)ecx, -1 -> je 0x867ae */
  /* test ebx, edx -> je 0x867ae */
  /* cmp (int16_t)ecx, -1 -> je 0x867c8 */
  /* test ebx, edx -> je 0x867c8 */
  /* test (char)eax, (char)eax -> jne 0x86818 */
  /* test (char)eax, (char)eax -> je 0x86818 */
  game_in_editor();
  /* test (char)eax, (char)eax -> je 0x8682a */
  /* test (char)eax, 0x41 -> jne 0x8686d */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
}


/* director_load_camera (0x86900) — readable C lift (restored pre-naked). */
void director_load_camera(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;

  crt_fopen((char *)0x00267084, (char *)0x002658a4);
  /* test esi, esi -> je 0x86a40 */
  _fscanf();
  _fscanf();
  _fscanf();
  _fscanf();
  crt_fclose((void *)(uintptr_t)esi);
  ((void(*)(void))FUN_00089350)();
  observer_up_from_forward((float *)(uintptr_t)ecx, (float *)(uintptr_t)eax);
  FUN_0010c510((float *)(uintptr_t)eax, (float *)(uintptr_t)edx);
  /* test (char)eax, 0x41 -> jne 0x86a13 */
  /* mem[0x003352d4] = ecx */
  /* mem[0x003352b8] = 0x893a0 */
  /* mem[0x00335374] = 0x3f800000 */

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
}

/* FUN_00086a50 (0x86a50) — readable C lift (restored pre-naked). */
void FUN_00086a50(void)
{
  int eax = 0;
  int esi = 0;

  /* cmp (int16_t)esi, 4 -> jl 0x86a82 */
  display_assert((char *)0x00266fc0, (char *)0x0026700c, 179, 0);
  system_exit(0);
  /* cmp eax, 4 -> ja 0x86b24 */
  ((void(*)(void))following_camera_new)();
  FUN_000865a0(0x00089cd0, 0, 0);
  ((void(*)(void))FUN_0008cf10)();
  FUN_000865a0(0x0008cf30, 0, 0);
  ((void(*)(void))FUN_00089350)();
  FUN_000865a0(0x000893a0, 0, 0);
  ((void(*)(void))first_person_camera_new)();
  FUN_000865a0(0x00089270, 0, 0);
  display_assert((char *)0, (char *)0x0026700c, 512, 0);
  system_exit(0);
  console_printf(0, (char *)0x00267094);

  (void)eax;
  (void)esi;
}

/* director_camera_deterministic (0x86b80) — readable C lift. */
int director_camera_deterministic(int player_index, void *a, void *b)
{
  int perspective;
  int result;
  int last;

  result = ((int (*)(int, int *))director_desired_perspective)(player_index, &perspective);
  if ((int16_t)result == 0)
    last = ((int (*)(int, void *, void *))FUN_00088c80)(player_index, a, b);
  else
    last = ((int (*)(int, void *, void *))FUN_00089c00)(player_index, a, b);
  /* Original ends with MOV AX, SI — keeps high 16 from the last callee. */
  return (last & ~0xffff) | (result & 0xffff);
}


/* FUN_00086be0 (0x86be0) — readable C lift. */
void FUN_00086be0(short index)
{
  extern char DAT_0026700c[];
  extern char DAT_00266fc0[];
  short idx;
  int *slot;

  idx = index;
  if (idx < 0 || idx >= 4) {
    display_assert(DAT_00266fc0, DAT_0026700c, 0xb3, 1);
    system_exit(-1);
  }
  slot = (int *)(*(int *)0x3f6eb4 + (int)idx * 0x1c);
  (void)slot;
}
void director_script_camera(int value)
{
  int ebx = 0;
  int esi = 0;

  /* test (int16_t)esi, (int16_t)esi -> jl 0x86cd2 */
  /* cmp (int16_t)esi, 4 -> jl 0x86cf2 */
  display_assert((char *)0x00266fc0, (char *)0x0026700c, 179, 0);
  system_exit(0);
  /* test (char)ebx, (char)ebx -> je 0x86d37 */
  /* test (int16_t)esi, (int16_t)esi -> jl 0x86d01 */
  /* cmp (int16_t)esi, 4 -> jl 0x86d21 */
  display_assert((char *)0x00266fc0, (char *)0x0026700c, 179, 0);
  system_exit(0);
  /* test (int16_t)esi, (int16_t)esi -> jl 0x86d42 */
  /* cmp (int16_t)esi, 4 -> jl 0x86d62 */
  display_assert((char *)0x00266fc0, (char *)0x0026700c, 179, 0);
  system_exit(0);
  player_control_get_unit_index(esi);
  ((void(*)(void))director_desired_perspective)();
  /* cmp (int16_t)eax, 1 -> jne 0x86d90 */
  ((void(*)(void))following_camera_new)();
  ((void(*)(void))first_person_camera_new)();
  FUN_000865a0(0x00089270, 0, 0);
  FUN_00084fe0(ebx);
  /* cmp (int16_t)esi, 4 -> jl 0x86cc7 */

  (void)ebx;
  (void)esi;
}


/* FUN_00087800 (0x87800) — XBE naked draft (batch 142). */
#if defined(__clang__)
static scenario_t * (*const b87800_c18e380)(void) = global_scenario_get;
static void *(*const b87800_elem)(void *, int, int) = tag_block_get_element;
static void *(*const b87800_memset)(void *, int, unsigned int) = csmemset;
static void (*const b87800_c10cc40)(float *out, float *angles) = angles_to_vector;
static void (*const b87800_c89350)(void) = (void (*)(void))FUN_00089350;

__attribute__((naked, noinline))
void FUN_00087800(float *target __attribute__((unused)), int16_t flag __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xc, %%esp\n\t"
      "movb 0x33569a, %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00087800_3\n\t"
      "call *%[c18e380]\n\t"
      "movl 0x354(%%eax), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .LFUN_00087800_1\n\t"
      "call *%[c18e380]\n\t"
      "movl 0x358(%%eax), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .LFUN_00087800_1\n\t"
      "pushl $0x34\n\t"
      "pushl $0\n\t"
      "call *%[c18e380]\n\t"
      "addl $0x354, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl %%eax, %%ecx\n\t"
      "movl (%%ecx), %%edx\n\t"
      "movl %%edx, 0x33569c\n\t"
      "movl 0x4(%%ecx), %%edx\n\t"
      "movl %%edx, 0x3356a0\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "movl %%ecx, 0x3356a4\n\t"
      "movl 0xc(%%eax), %%edx\n\t"
      "movl %%edx, 0x3356a8\n\t"
      "jmp .LFUN_00087800_2\n\t"
      ".LFUN_00087800_1:\n\t"
      "pushl $0x14\n\t"
      "pushl $0\n\t"
      "pushl $0x33569c\n\t"
      "call *%[memset]\n\t"
      ".LFUN_00087800_2:\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_00087800_3:\n\t"
      "pushl %%esi\n\t"
      "leal -0xc(%%ebp), %%eax\n\t"
      "pushl $0x3356a8\n\t"
      "pushl %%eax\n\t"
      "movb $1, 0x33569a\n\t"
      "call *%[c10cc40]\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "leal -0xc(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x33569c\n\t"
      "pushl %%esi\n\t"
      "call *%[c89350]\n\t"
      "addl $0x14, %%esp\n\t"
      "cmpw $0, 0xc(%%ebp)\n\t"
      "jne .LFUN_00087800_4\n\t"
      "movl %%esi, 0x3356b0\n\t"
      ".LFUN_00087800_4:\n\t"
      "movw 0x3356c4, %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "je .LFUN_00087800_5\n\t"
      "movswl %%ax, %%edx\n\t"
      "pushl %%esi\n\t"
      "call *0x2ee680(,%%edx,8)\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_00087800_5:\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c18e380] "m"(b87800_c18e380), [elem] "m"(b87800_elem), [memset] "m"(b87800_memset), [c10cc40] "m"(b87800_c10cc40), [c89350] "m"(b87800_c89350)
      : "memory");
}
#else
#error "FUN_00087800: clang naked draft required"
#endif


/* editor_camera_get_focus (0x878d0) — readable C lift. */
void editor_camera_get_focus(float *out_pos, float *out_orient)
{
  if (!out_pos) {
    display_assert((const char *)0x267114, (const char *)0x267120, 0x78, true);
    system_exit(-1);
  }
  if (!out_orient) {
    display_assert((const char *)0x26710c, (const char *)0x267120, 0x79, true);
    system_exit(-1);
  }
  out_pos[0] = *(float *)0x33569c;
  out_pos[1] = *(float *)0x3356a0;
  out_pos[2] = *(float *)0x3356a4;
  out_orient[0] = *(float *)0x3356a8;
  out_orient[1] = *(float *)0x3356ac;
}

/* editor_camera_set_focus (0x87950) — readable C lift. */
void editor_camera_set_focus(float *pos, float *orient)
{
  if (!pos) {
    display_assert((const char *)0x267114, (const char *)0x267120, 0x81, true);
    system_exit(-1);
  }
  if (!orient) {
    display_assert((const char *)0x26710c, (const char *)0x267120, 0x82, true);
    system_exit(-1);
  }
  *(float *)0x33569c = pos[0];
  *(float *)0x3356a0 = pos[1];
  *(float *)0x3356a4 = pos[2];
  *(float *)0x3356a8 = orient[0];
  *(float *)0x3356ac = orient[1];
}

/* editor_camera_set_position (0x879d0) — readable C lift from XBE leaf. */
void editor_camera_set_position(float *pos, float *orient)
{
  extern char DAT_00267120[];
  extern char DAT_0025bb20[];
  extern char DAT_0026710c[];
  float *dst;

  if (!pos) {
    display_assert(DAT_0025bb20, DAT_00267120, 0x94, 1);
    system_exit(-1);
  }
  if (!orient) {
    display_assert(DAT_0026710c, DAT_00267120, 0x95, 1);
    system_exit(-1);
  }
  dst = *(float **)0x3356b0;
  if (!dst) {
    editor_camera_set_focus(pos, orient);
    *(char *)0x33569a = 1;
    return;
  }
  dst[0] = pos[0];
  dst[1] = pos[1];
  dst[2] = pos[2];
  dst[3] = orient[0];
  dst[4] = orient[1];
}


/* FUN_00087ac0 (0x87ac0) — readable C lift. */
char FUN_00087ac0(char enable)
{
  char prev = *(char *)0x335699;
  void *p;
  *(char *)0x335699 = enable;
  if (!enable) {
    p = *(void **)0x3356b0;
    if (p) *(int *)((char *)p + 0x14) = 0;
  }
  return prev;
}

/* editor_camera_set_mode (0x87b00) — readable C lift (restored pre-naked). */
void editor_camera_set_mode(int16_t mode)
{
  int eax = 0;
  int edx = 0;
  int edi = 0;

  /* cmp (int16_t)eax, (int16_t)edi -> je 0x87bb6 */
  /* test (int16_t)eax, (int16_t)eax -> je 0x87b70 */
  /* test edx, edx -> jne 0x87b5d */
  display_assert((char *)0x0026718c, (char *)0x00267120, 302, 0);
  system_exit(0);
  /* test (int16_t)edi, (int16_t)edi -> je 0x87bb6 */
  /* test eax, eax -> jne 0x87ba4 */
  display_assert((char *)0x00267164, (char *)0x00267120, 308, 0);
  system_exit(0);
  console_printf(0, (char *)(uintptr_t)eax);

  (void)eax;
  (void)edx;
  (void)edi;
}


/* FUN_00087c00 (0x87c00) — readable C lift. */
void FUN_00087c00(float *camera)
{
  float *dst;
  float *src;
  int i;

  dst = (float *)0x3356d0;
  for (i = 0; i < 7; i++)
    dst[i] = camera[i];
  if (*(unsigned char *)0x33570c != 0) {
    src = (float *)0x3356f0;
    for (i = 0; i < 7; i++)
      camera[i] = src[i];
  } else {
    camera[0] = 0.0f;
    camera[1] = *(float *)0x2670d8;
    camera[2] = 0.0f;
    vector_to_angles(camera + 3, (float *)(*(char **)0x2ee670 + 0x1c));
  }
}

/* editor_camera_move_to_point (0x87c80) — readable C lift. */
void editor_camera_move_to_point(float *point)
{
  float dir[3];
  float *cam;
  float scale;

  if (!point) {
    display_assert((const char *)0x25bb20, (const char *)0x267120, 0x8b, 1);
    system_exit(-1);
  }
  cam = *(float **)0x3356b0;
  angles_to_vector(dir, cam + 3);
  scale = *(float *)0x254e04;
  cam[0] = point[0] - dir[0] * scale;
  cam[1] = point[1] - dir[1] * scale;
  cam[2] = point[2] - dir[2] * scale;
}


void editor_camera_set_position_and_roll(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;

  display_assert((char *)0x0025bb20, (char *)0x00267120, 169, ebx);
  system_exit(0);
  /* test esi, esi -> jne 0x87d5a */
  display_assert((char *)0x0026710c, (char *)0x00267120, 170, ebx);
  system_exit(0);
  /* test eax, eax -> jne 0x87d80 */
  ((void(*)(void))editor_camera_set_focus)();
  FUN_00109e90((float *)(uintptr_t)edx, 0.0f, 0.0f, 0.0f);
  vector_to_angles((float *)(uintptr_t)ecx, (float *)0);
  angles_to_vector((float *)(uintptr_t)eax, (float *)(uintptr_t)edx);
  angles_to_vector((float *)0, (float *)0);
  normalize3d((float *)(uintptr_t)edx);
  normalize3d((float *)(uintptr_t)eax);
  normalize3d((float *)0);
  FUN_0010c510((float *)(uintptr_t)eax, (float *)(uintptr_t)edx);
  /* cmp eax, -1 -> je 0x87ea2 */
  /* mem[0x003356b8] = edx */
  /* mem[0x003356bc] = eax */
  /* mem[0x003356c0] = ecx */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
}


/* FUN_00087eb0 (0x87eb0) — readable C lift. */
void FUN_00087eb0(int object_handle)
{
  float *anchor = *(float **)0x3356b0;
  *(int *)0x2ee66c = object_handle;
  if (!anchor) {
    return;
  }
  if (object_handle == -1) {
    float *p = *(float **)0x31fc38;
    *(float *)0x3356b8 = p[0];
    *(float *)0x3356bc = p[1];
    *(float *)0x3356c0 = p[2];
    return;
  }
  {
    char *obj = (char *)object_get_and_verify_type(object_handle, -1);
    *(float *)0x3356b8 = anchor[0] - *(float *)(obj + 0x50);
    *(float *)0x3356bc = anchor[1] - *(float *)(obj + 0x54);
    *(float *)0x3356c0 = anchor[2] - *(float *)(obj + 0x58);
  }
}

/* editor_camera_update (0x87f20) — readable C lift (restored pre-naked). */
void editor_camera_update(void)
{
  int eax = 0;
  int ecx = 0;
  int edi = 0;

  /* test ecx, ecx -> jne 0x87f55 */
  display_assert((char *)0x002671bc, (char *)0x00267120, 340, 0);
  system_exit(0);
  /* test (char)eax, (char)eax -> jne 0x87f81 */
  FUN_000853c0(0, (void *)(uintptr_t)edi, (void *)(uintptr_t)ecx);
  vector_to_angles((float *)(uintptr_t)eax, (float *)0);
  ((void(*)(void))FUN_00087eb0)();
  /* test (int16_t)eax, (int16_t)eax -> je 0x88014 */
  /* test ecx, ecx -> jne 0x87ffc */
  display_assert((char *)0x0026718c, (char *)0x00267120, 356, 0);
  system_exit(0);
  /* test (char)eax, (char)eax -> je 0x88045 */

  (void)eax;
  (void)ecx;
  (void)edi;
}

void editor_camera_set_scripted(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;

  /* test (char)ebx, (char)ebx -> je 0x88135 */
  /* test (int16_t)eax, (int16_t)eax -> je 0x880b4 */
  /* test edx, edx -> jne 0x880a1 */
  display_assert((char *)0x0026718c, (char *)0x00267120, 387, 0);
  system_exit(0);
  vector_to_angles((float *)(uintptr_t)edx, (float *)(uintptr_t)ecx);
  ((void(*)(void))editor_camera_set_position)();
  /* cmp eax, -1 -> je 0x8810e */
  FUN_00085280((void *)0x003356b8, (float *)(uintptr_t)eax, (float *)0, 0.0f, 0, 0);
  FUN_00085280((float *)(uintptr_t)eax, (float *)0, (float *)0, 0.0f, 0, 0);
  vector_to_angles((float *)(uintptr_t)eax, (float *)0);
  ((void(*)(void))FUN_00087eb0)();
  /* test edx, edx -> jne 0x881b8 */
  display_assert((char *)0x0026718c, (char *)0x00267120, 414, 0);
  system_exit(0);
  console_printf(0, (char *)0x002671d8);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
}


/* FUN_00088200 (0x88200) — readable C lift. */
void FUN_00088200(float *camera)
{
  float *src;
  int i;
  float *dst = (float *)0x3356f0;
  for (i = 0; i < 7; i++) {
    dst[i] = camera[i];
  }
  *(unsigned char *)0x33570c = 1;
  src = (float *)(*(char **)0x2ee670 + 0x10);
  camera[0] = src[0];
  camera[1] = src[1];
  camera[2] = src[2];
  vector_to_angles(camera + 3, (float *)(*(char **)0x2ee670 + 0x1c));
  FUN_00087eb0(*(int *)0x2ee66c);
}

void editor_camera_flying_update(void)
{
  int eax = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;

  display_assert((char *)0x00266e9c, (char *)0x00267120, 448, 0);
  system_exit(0);
  /* test edi, edi -> jne 0x882b7 */
  display_assert((char *)0x002671f8, (char *)0x00267120, 449, 0);
  system_exit(0);
  /* test esi, esi -> jne 0x882de */
  display_assert((char *)0x0025f120, (char *)0x00267120, 450, 0);
  system_exit(0);
  /* test (char)eax, (char)eax -> je 0x8833e */
  /* test (char)eax, 0x41 -> jne 0x88320 */
  /* test (char)eax, (char)eax -> je 0x88337 */
  angles_to_vector((float *)(uintptr_t)edi, (float *)(uintptr_t)eax);
  normalize3d((float *)(uintptr_t)ecx);
  rotate_vector3d_by_sincos((float *)(uintptr_t)eax, (float *)(uintptr_t)edi, 0.0f, 0.0f);
  object_try_and_get_and_verify_type(0, 0);
  /* test eax, eax -> je 0x884b1 */
  object_get_and_verify_type(0, 0);
  valid_real_normal3d_perpendicular((float *)(uintptr_t)edi, (float *)(uintptr_t)eax);
  /* test (char)eax, (char)eax -> je 0x88723 */
  /* test (char)eax, 1 -> jne 0x88723 */
  /* test (char)eax, 1 -> jne 0x88723 */
  /* test (char)eax, 1 -> jne 0x88723 */
  /* test (char)eax, 1 -> jne 0x88723 */
  /* test (char)eax, 1 -> jne 0x88723 */

  (void)eax;
  (void)ecx;
  (void)esi;
  (void)edi;
}


/* FUN_00088c80 (0x88c80) — copy unit/vehicle camera point + optional marker. */
void FUN_00088c80(int unit_handle, float *out_pos, float *out_forward)
{
  void *unit;
  void *veh;
  void *vehi_tag;
  void *seat;
  int16_t n;
  float markers[0x6c / 4];

  unit = object_get_and_verify_type(unit_handle, 3);
  unit_set_seat_state(unit_handle, out_pos);
  out_forward[0] = *(float *)((char *)unit + 0x1ec);
  out_forward[1] = *(float *)((char *)unit + 0x1f0);
  out_forward[2] = *(float *)((char *)unit + 0x1f4);
  if (*(int *)((char *)unit + 0xcc) == -1)
    return;
  veh = object_try_and_get_and_verify_type(*(int *)((char *)unit + 0xcc), 2);
  if (veh == 0)
    return;
  vehi_tag = tag_get(0x76656869, *(int *)veh);
  seat = tag_block_get_element((char *)vehi_tag + 0x2e4,
                               (int)*(short *)((char *)unit + 0x2a0), 0x11c);
  if ((*(char *)seat & 0x80) == 0)
    return;
  n = object_get_markers_by_string_id(*(int *)((char *)unit + 0xcc),
                                      (void *)0x267238, markers, 1);
  if (n == 0)
    return;
  /* marker layout: position at +0x60.. from marker base ebp-0x6c → +0x60 = ebp-0xc */
  out_pos[0] = markers[0x60 / 4];
  out_pos[1] = markers[0x64 / 4];
  out_pos[2] = markers[0x68 / 4];
  out_forward[0] = markers[0x3c / 4];
  out_forward[1] = markers[0x40 / 4];
  out_forward[2] = markers[0x44 / 4];
}
