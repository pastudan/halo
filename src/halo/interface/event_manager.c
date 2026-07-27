#include "x87_math.h"
#include <stdint.h>
/* motion_sensor_initialize (0xdb0f0) — readable C lift. */
extern char DAT_00282100[];
extern char DAT_002820e8[];
extern char DAT_00282094[];
extern char DAT_002820d0[];
void motion_sensor_initialize(void)
{
  void *p;

  p = game_state_malloc(DAT_002820e8, DAT_00282100, 0x15a8);
  *(void **)0x46bd2c = p;
  if (p == NULL) {
    display_assert(DAT_002820d0, DAT_00282094, 0x12a, true);
    system_exit(-1);
  }
}

/* (0xdb140) */
void FUN_000db140(void)
{
}

/* Clear the motion sensor state and pre-initialize slot tables (0xdb150). */
void FUN_000db150(void)
{
  unsigned char *p;
  unsigned char *row;
  unsigned char *cell;
  int i;
  int j;
  int k;

  csmemset(*(void **)0x46bd2c, 0, 0x15a8);
  p = (unsigned char *)*(void **)0x46bd2c + 2;
  i = 4;
  do {
    j = 10;
    row = p;
    do {
      k = 0x10;
      cell = row;
      do {
        *cell = 6;
        cell += 4;
        k--;
      } while (k != 0);
      row += 0x84;
      j--;
    } while (j != 0);
    p += 0x568;
    i--;
  } while (i != 0);
}

/* (0xdb1b0) */
void FUN_000db1b0(void)
{
}

/**
 * Check whether it is time to start the attract-mode tab sequence.
 *
 * Returns true when the main menu has been idle long enough (>0x124f8 ms
 * ~= 75 seconds) with no input events.  As a side-effect, starts or stops
 * title music depending on whether the idle threshold (0x11f1c ms ~= 73 s)
 * has been crossed.
 */
bool event_manager_tab_check(void)
{
  unsigned int now;
  unsigned int last_event;
  bool attract_flag;

  if (cache_files_precache_in_progress()) {
    float progress;
    if (cache_files_precache_map_status(&progress) == 1)
      cache_files_precache_map_end();
  }

  if (ui_widget_is_main_menu_loaded() && !cache_files_precache_in_progress() &&
      !network_game_in_progress() && !bink_playback_active()) {
    now = system_milliseconds();
    last_event = event_manager_get_last_event_time();
    if (*(unsigned int *)0x46bd38 > last_event)
      last_event = *(unsigned int *)0x46bd38;
    attract_flag = ui_widget_get_attract_mode_flag();
    if (now - last_event >= 0x11f1c) {
      if (attract_flag)
        ui_widget_stop_attract_mode();
    } else {
      if (!attract_flag)
        ui_widget_start_title_music();
    }
    if (now - last_event >= 0x124f8)
      return true;
  }
  return false;
}

/**
 * Stop attract mode and all sounds, then play the credits Bink video.
 */
void FUN_000dc110(void)
{
  ui_widget_stop_attract_mode();
  sound_stop_all();
  bink_playback_start("d:\\bink\\credits.bik", 0x2e);
}

/**
 * Record the current time as the "mark" timestamp, used by
 * event_manager_tab_check to measure idle duration.
 */
void event_manager_mark_time(void)
{
  *(unsigned int *)0x46bd38 = system_milliseconds();
}

/**
 * Pick and play a random attract-mode Bink video, ensuring it differs
 * from the previously played one.  Resets the mark-time afterward so
 * the idle clock restarts when the video finishes.
 */
void event_manager_tab_process(void)
{
  const char *attract_files[3];
  int16_t idx;

  attract_files[0] = "d:\\bink\\attract1.bik";
  attract_files[1] = "d:\\bink\\attract2.bik";
  attract_files[2] = "d:\\bink\\attract3.bik";

  do {
    idx = random_range(random_math_get_local_seed_address(), 0, 3);
    if (idx < 0)
      idx = 0;
    else if (idx > 2)
      idx = 2;
  } while (idx == *(int16_t *)0x2f670c);

  *(int16_t *)0x2f670c = idx;
  ui_widget_stop_attract_mode();
  bink_playback_start(attract_files[idx], 0x2e);

  if (!bink_playback_active())
    *(unsigned int *)0x46bd38 = system_milliseconds();
}

void event_manager_initialize(void)
{
  csmemset(event_manager_globals, 0, 0x108);
  *(_DWORD *)(event_manager_globals + 4) = system_milliseconds();
  event_manager_globals[0] = 1;
}

void event_manager_dispose(void)
{
  csmemset(event_manager_globals, 0, 0x108);
}

/**
 * Zero out the 0x100-byte event ring buffer, discarding all queued events.
 */
void event_manager_flush(void)
{
  csmemset((void *)0x46bd48, 0, 0x100);
}

/**
 * Set or clear the event suppression flag.  While suppressed,
 * event_manager_dispatch ignores all incoming events.
 */
void event_manager_suppress(int suppress)
{
  *(char *)0x46bd41 = (char)suppress;
}

/**
 * Retrieve the next queued event for the given local player (or any
 * player if player_index == NONE / -1).  Scans the per-player event
 * ring from newest to oldest, copies the first non-empty slot into
 * event_data, clears that slot, and returns true.  Returns false when
 * no events remain.
 */
bool event_manager_get_next_event(void *event_data, int16_t player_index)
{
  int i;
  int16_t pi;
  int16_t *slot;

  assert_halt(event_data &&
              ((player_index >= 0 && player_index < MAXIMUM_GAMEPADS) ||
               player_index == NONE));

  if (!event_manager_globals[0])
    return false;

  if (player_index == NONE) {
    for (pi = 0; pi < 4; pi++) {
      if (event_manager_get_next_event(event_data, pi))
        return true;
    }
    return false;
  }

  /* scan from slot 7 (newest) down to slot 0 (oldest) */
  slot = (int16_t *)(0x46bd80 + (int)player_index * 0x40);
  for (i = 7; i >= 0; i--) {
    if (*slot != 0) {
      int idx = i + (int)player_index * 8;
      *(int *)event_data = *(int *)(0x46bd48 + idx * 8);
      *((int *)event_data + 1) = *(int *)(0x46bd4c + idx * 8);
      *(int16_t *)(0x46bd48 + idx * 8) = 0;
      return true;
    }
    slot -= 4;
  }
  return false;
}

/**
 * Return the timestamp of the last non-empty event dispatched.
 */
unsigned int event_manager_get_last_event_time(void)
{
  return *(unsigned int *)0x46bd44;
}

void event_manager_dispatch(int16_t *event, int16_t player_index)
{
  bool dispatch;
  int now;
  int x, y;
  int ax, ay;
  int pi;

  if (*(char *)0x46bd41)
    return;

  now = system_milliseconds();

  if (event[0] == 1) {
    x = (int)event[2];
    y = (int)event[3];

    ax = x < 0 ? -x : x;
    if (ax < 0x7332) {
      ay = y < 0 ? -y : y;
      if (ay < 0x7332) {
        dispatch = false;
        goto store_stick1;
      }
    }

    ax = x < 0 ? -x : x;
    if (ax >= 0x7332) {
      pi = (int)player_index * 4;
      ay = *(int *)(0x46be68 + pi);
      if (ay < 0)
        ay = -ay;
      if (ay < 0x7332)
        goto record_stick1;
    }

    ay = y < 0 ? -y : y;
    if (ay >= 0x7332) {
      pi = (int)player_index * 4;
      ax = *(int *)(0x46be78 + pi);
      if (ax < 0)
        ax = -ax;
      if (ax < 0x7332)
        goto record_stick1;
    }

    pi = (int)player_index * 4;
    if ((unsigned int)(now - *(int *)(0x46be48 + pi)) < 0xfa) {
      dispatch = false;
      goto store_stick1;
    }

  record_stick1:
    *(int *)(0x46be48 + pi) = now;
    dispatch = true;

    ax = x < 0 ? -x : x;
    if (ax >= 0x7332) {
      if (x >= 0) {
        event[2] = 0x7fff;
        x = 0x7fff;
      } else {
        event[2] = (int16_t)0x8000;
        x = (int)(int16_t)0x8000;
      }
    }

    ay = y < 0 ? -y : y;
    if (ay >= 0x7332) {
      if (y >= 0) {
        event[3] = 0x7fff;
        y = 0x7fff;
      } else {
        event[3] = (int16_t)0x8000;
        y = (int)(int16_t)0x8000;
      }
    }

  store_stick1:
    *(int *)(0x46be68 + (int)player_index * 4) = x;
    *(int *)(0x46be78 + (int)player_index * 4) = y;
  } else if (event[0] == 2) {
    x = (int)event[2];
    y = (int)event[3];

    ax = x < 0 ? -x : x;
    if (ax < 0x7332) {
      ay = y < 0 ? -y : y;
      if (ay < 0x7332) {
        dispatch = false;
        goto store_stick2;
      }
    }

    ax = x < 0 ? -x : x;
    if (ax >= 0x7332) {
      pi = (int)player_index * 4;
      ay = *(int *)(0x46be88 + pi);
      if (ay < 0)
        ay = -ay;
      if (ay < 0x7332)
        goto record_stick2;
    }

    ay = y < 0 ? -y : y;
    if (ay >= 0x7332) {
      pi = (int)player_index * 4;
      ax = *(int *)(0x46be98 + pi);
      if (ax < 0)
        ax = -ax;
      if (ax < 0x7332)
        goto record_stick2;
    }

    pi = (int)player_index * 4;
    if ((unsigned int)(now - *(int *)(0x46be58 + pi)) < 0xfa) {
      dispatch = false;
      goto store_stick2;
    }

  record_stick2:
    *(int *)(0x46be58 + pi) = now;
    dispatch = true;

    ax = x < 0 ? -x : x;
    if (ax >= 0x7332) {
      if (x >= 0) {
        event[2] = 0x7fff;
        x = 0x7fff;
      } else {
        event[2] = (int16_t)0x8000;
        x = (int)(int16_t)0x8000;
      }
    }

    ay = y < 0 ? -y : y;
    if (ay >= 0x7332) {
      if (y >= 0) {
        event[3] = 0x7fff;
        y = 0x7fff;
      } else {
        event[3] = (int16_t)0x8000;
        y = (int)(int16_t)0x8000;
      }
    }

  store_stick2:
    *(int *)(0x46be88 + (int)player_index * 4) = x;
    *(int *)(0x46be98 + (int)player_index * 4) = y;
  } else {
    goto record_event;
  }

  if (!dispatch)
    return;

record_event:
  event[1] = player_index;
  pi = (int)player_index * 0x40;
  csmemmove((void *)(0x46bd48 + pi), (void *)(0x46bd50 + pi), 0x38);
  *(int *)(0x46bd48 + pi) = *(int *)event;
  *(int *)(0x46bd4c + pi) = *(int *)&event[2];
  if (event[0] != 0)
    *(int *)0x46bd44 = now;
}

void event_manager_update(void)
{
  int16_t event[4];
  int16_t empty_event[4];
  char *state;
  int i;
  int16_t j;
  bool had_event;

  if (!event_manager_globals[0])
    return;

  for (i = 0; (int16_t)i < 4; i++) {
    had_event = false;
    if (!input_has_gamepad(i) ||
        (state = (char *)input_get_gamepad_state(i)) == NULL)
      goto send_empty;

    /* left stick */
    if (*(int16_t *)(state + 0x20) != 0 || *(int16_t *)(state + 0x22) != 0) {
      *(int32_t *)&event[2] = *(int32_t *)(state + 0x20);
      event[0] = 1;
      event_manager_dispatch(event, (int16_t)i);
      had_event = true;
    }

    /* right stick */
    if (*(int16_t *)(state + 0x24) != 0 || *(int16_t *)(state + 0x26) != 0) {
      *(int32_t *)&event[2] = *(int32_t *)(state + 0x24);
      event[0] = 2;
      event_manager_dispatch(event, (int16_t)i);
      had_event = true;
    }

    /* buttons (16 digital buttons) */
    for (j = 0; j < 0x10; j++) {
      if (state[0x10 + j] != 0) {
        event[0] = 3;
        ((uint8_t *)&event[2])[0] = (uint8_t)j;
        ((uint8_t *)&event[2])[1] = (uint8_t)state[0x10 + j];
        event_manager_dispatch(event, (int16_t)i);
        had_event = true;
      }
    }

    if (had_event)
      continue;

  send_empty:
    *(int32_t *)&empty_event[1] = 0;
    empty_event[0] = 0;
    empty_event[3] = 0;
    event_manager_dispatch(empty_event, (int16_t)i);
  }
}

/* Wrapper: forward three args to animation_update_internal with update_kind=0
 * (0xdc730). */
void FUN_000dc730(int param_1, short *param_2, int *param_3)
{
  animation_update_internal(0, param_1, param_2, param_3);
}

/* Map a game-event type to a UI-widget event type. */
int16_t FUN_000dc800(int event)
{
  switch ((int16_t)event) {
  case 0:
    return 6;
  case 1:
    return 7;
  case 2:
    return 8;
  case 3:
    return 9;
  case 4:
    return 10;
  case 5:
    return 11;
  case 6:
    return 12;
  case 9:
    return 13;
  case 10:
    return 14;
  case 11:
    return 18;
  case 12:
    return 19;
  case 14:
    return 4;
  case 15:
    return 1;
  case 16:
    return 23;
  case 17:
    return 20;
  default:
    return -1;
  }
}
/* --- event_manager.obj batch drafts (2026-07-26) --- */

/* FUN_000d98c0 (0xd98c0) — readable C lift. */
void FUN_000d98c0(int16_t local_a, int16_t local_b)
{
  void *src;
  void *dst;
  int i;

  if (local_a == (int16_t)-1) {
    display_assert((const char *)0x281eb8, (const char *)0x281eec, 0x89, 1);
    system_exit(-1);
  }
  if (local_b == (int16_t)-1) {
    display_assert((const char *)0x281e98, (const char *)0x281eec, 0x8a, 1);
    system_exit(-1);
  }
  src = FUN_000d8bc0(local_b);
  dst = FUN_000d8bc0(local_a);
  for (i = 0; i < 0xa; i++)
    ((int *)dst)[i] = ((int *)src)[i];
  src = FUN_000d8c30(local_b);
  dst = FUN_000d8c30(local_a);
  for (i = 0; i < 0x14; i++)
    ((int *)dst)[i] = ((int *)src)[i];
}

/* FUN_000d9960 (0xd9960) — XBE naked draft (batch 106). */
#if defined(__clang__)
static int (*const bd9960_cd1540)(void) = FUN_000d1540;
static void *(*const bd9960_memset)(void *, int, unsigned int) = csmemset;
static int (*const bd9960_cba3c0)(int16_t local_player_index) = local_player_get_player_index;
static void *(*const bd9960_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void *(*const bd9960_tryget)(int, int) = object_try_and_get_and_verify_type;
static void * (*const bd9960_cd8c30)(int16_t local_player_index) = FUN_000d8c30;
static void *(*const bd9960_tag)(int, int) = tag_get;
static void *(*const bd9960_get)(int, int) = object_get_and_verify_type;
static void * (*const bd9960_cd8bc0)(int16_t local_player_index) = FUN_000d8bc0;
static void (*const bd9960_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;
static float (*const bd9960_cb6940)(int16_t local_player_index) = player_control_get_autoaim_level;
static int16_t (*const bd9960_cb6a70)(int16_t local_player_index) = player_control_get_zoom_level;
static void (*const bd9960_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const bd9960_exitfn)(int) = system_exit;
static int (*const bd9960_gtime)(void) = game_time_get;
static char * (*const bd9960_c8d9d0)(char *buffer, const char *format, ...) = csprintf;
static void (*const bd9960_cd9ead)(void) = (void (*)(void))render_weapon_hud;

__attribute__((naked, noinline))
void FUN_000d9960(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x2a8, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl %%eax, %%ebx\n\t"
      "call *%[cd1540]\n\t"
      "pushl $0x200\n\t"
      "movl %%eax, -0x28(%%ebp)\n\t"
      "leal -0x2a8(%%ebp), %%eax\n\t"
      "pushl $0x62\n\t"
      "pushl %%eax\n\t"
      "call *%[memset]\n\t"
      "pushl %%ebx\n\t"
      "call *%[cba3c0]\n\t"
      "movl 0x5aa6d4, %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, -0x18(%%ebp)\n\t"
      "movl 0x34(%%eax), %%eax\n\t"
      "pushl $3\n\t"
      "pushl %%eax\n\t"
      "call *%[tryget]\n\t"
      "addl $0x20, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "je .LFUN_000d9960_52\n\t"
      "movl -0x18(%%ebp), %%edx\n\t"
      "movw 0x2(%%edx), %%si\n\t"
      "call *%[cd8c30]\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x77706869\n\t"
      "call *%[tag]\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_000d9960_1\n\t"
      "pushl $4\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl (%%eax), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x77656170\n\t"
      "call *%[tag]\n\t"
      "addl $0x10, %%esp\n\t"
      ".LFUN_000d9960_1:\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "pushl %%edi\n\t"
      "xorl %%eax, %%eax\n\t"
      "movl %%edx, -0x68(%%ebp)\n\t"
      "movl $0xf, %%ecx\n\t"
      "leal -0x64(%%ebp), %%edi\n\t"
      "rep stosl\n\t"
      "movl -0x68(%%ebp), %%eax\n\t"
      "movl 0x9c(%%eax), %%ecx\n\t"
      "movl %%ebx, %%esi\n\t"
      "movl %%ecx, -0x1c(%%ebp)\n\t"
      "movl $0, -0xc(%%ebp)\n\t"
      "movl $1, %%edi\n\t"
      "call *%[cd8bc0]\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "cmpl 0x20(%%eax), %%edx\n\t"
      "je .LFUN_000d9960_2\n\t"
      "movl %%edx, %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "jne .LFUN_000d9960_2\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "pushl $0x50\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "call *%[memset]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_000d9960_2:\n\t"
      "movl -0x1c(%%ebp), %%ebx\n\t"
      "movl %%edi, %%edi\n\t"
      ".LFUN_000d9960_3:\n\t"
      "movswl %%di, %%eax\n\t"
      "shll $2, %%eax\n\t"
      "movl -0x6c(%%ebp,%%eax,1), %%ecx\n\t"
      "movl 0xc(%%ecx), %%ecx\n\t"
      "cmpl $-1, %%ecx\n\t"
      "leal -0x68(%%ebp,%%eax,1), %%esi\n\t"
      "je .LFUN_000d9960_4\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x77706869\n\t"
      "movl %%ecx, -0xa8(%%ebp,%%eax,1)\n\t"
      "call *%[tag]\n\t"
      "movl 0x9c(%%eax), %%edx\n\t"
      "addl $8, %%esp\n\t"
      "orl %%edx, %%ebx\n\t"
      "incl %%edi\n\t"
      "cmpw $0x10, %%di\n\t"
      "movl %%eax, (%%esi)\n\t"
      "jl .LFUN_000d9960_3\n\t"
      ".LFUN_000d9960_4:\n\t"
      "cmpw $0x10, %%di\n\t"
      "movl %%ebx, -0x1c(%%ebp)\n\t"
      "jne .LFUN_000d9960_5\n\t"
      "pushl $0x281f8c\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_000d9960_5:\n\t"
      "movl -0x28(%%ebp), %%esi\n\t"
      "movl 0x10(%%ebp), %%edi\n\t"
      "movl $0, -0x10(%%ebp)\n\t"
      ".LFUN_000d9960_6:\n\t"
      "movswl -0x10(%%ebp), %%ebx\n\t"
      "movl %%ebx, %%ecx\n\t"
      "movl $1, %%eax\n\t"
      "shll %%cl, %%eax\n\t"
      "testl %%eax, -0x1c(%%ebp)\n\t"
      "movl %%eax, -0x24(%%ebp)\n\t"
      "je .LFUN_000d9960_51\n\t"
      "cmpl $0x12, %%ebx\n\t"
      "ja .LFUN_000d9960_43\n\t"
      "jmp *.LFUN_000d9960_jt0(,%%ebx,4)\n\t"
      ".LFUN_000d9960_7:\n\t"
      "movzbw 0xd(%%edi), %%si\n\t"
      "jmp .LFUN_000d9960_44\n\t"
      ".LFUN_000d9960_8:\n\t"
      "movzbw 0x17(%%edi), %%si\n\t"
      "jmp .LFUN_000d9960_44\n\t"
      ".LFUN_000d9960_9:\n\t"
      "cmpl $-1, 0x8(%%ebp)\n\t"
      "je .LFUN_000d9960_38\n\t"
      "movl -0x18(%%ebp), %%edx\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x2(%%edx), %%ax\n\t"
      "pushl %%eax\n\t"
      "call *%[cb6940]\n\t"
      "fcomps 0x2533c8\n\t"
      "addl $4, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .LFUN_000d9960_38\n\t"
      "jmp .LFUN_000d9960_18\n\t"
      ".LFUN_000d9960_10:\n\t"
      "movl -0x18(%%ebp), %%ecx\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x2(%%ecx), %%dx\n\t"
      "pushl %%edx\n\t"
      "call *%[cb6a70]\n\t"
      "addl $4, %%esp\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .LFUN_000d9960_18\n\t"
      "movl -0x18(%%ebp), %%eax\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x2(%%eax), %%cx\n\t"
      "pushl %%ecx\n\t"
      "call *%[cb6a70]\n\t"
      "xorl %%esi, %%esi\n\t"
      "movw %%ax, %%si\n\t"
      "addl $4, %%esp\n\t"
      "addl $2, %%esi\n\t"
      "jmp .LFUN_000d9960_44\n\t"
      ".LFUN_000d9960_11:\n\t"
      "movzbw 0xc(%%edi), %%si\n\t"
      "jmp .LFUN_000d9960_44\n\t"
      ".LFUN_000d9960_12:\n\t"
      "movw 0x12(%%edi), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "jne .LFUN_000d9960_13\n\t"
      "cmpw %%ax, 0xe(%%edi)\n\t"
      "je .LFUN_000d9960_38\n\t"
      "testw %%ax, %%ax\n\t"
      "je .LFUN_000d9960_38\n\t"
      ".LFUN_000d9960_13:\n\t"
      "movw 0xe(%%edi), %%dx\n\t"
      "jmp .LFUN_000d9960_41\n\t"
      ".LFUN_000d9960_14:\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "flds (%%edi)\n\t"
      "movswl 0x18(%%ecx), %%edx\n\t"
      "fmuls 0x253f00\n\t"
      "movl %%edx, -0x20(%%ebp)\n\t"
      "fildl -0x20(%%ebp)\n\t"
      "fcompp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .LFUN_000d9960_38\n\t"
      "jmp .LFUN_000d9960_18\n\t"
      ".LFUN_000d9960_15:\n\t"
      "movw 0x12(%%edi), %%ax\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "cmpw 0x14(%%ecx), %%ax\n\t"
      "jg .LFUN_000d9960_38\n\t"
      "movb 0xc(%%edi), %%al\n\t"
      ".LFUN_000d9960_16:\n\t"
      "testb %%al, %%al\n\t"
      ".LFUN_000d9960_17:\n\t"
      "jne .LFUN_000d9960_38\n\t"
      ".LFUN_000d9960_18:\n\t"
      "movl $1, %%esi\n\t"
      ".LFUN_000d9960_19:\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "movl -0x24(%%ebp), %%ecx\n\t"
      "orl %%ecx, %%eax\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      ".LFUN_000d9960_20:\n\t"
      "cmpl $0x12, %%ebx\n\t"
      "ja .LFUN_000d9960_50\n\t"
      "movzbl 0xd9f0c(%%ebx), %%edx\n\t"
      "jmp *.LFUN_000d9960_jt1(,%%edx,4)\n\t"
      ".LFUN_000d9960_21:\n\t"
      "flds 0x4(%%edi)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_000d9960_38\n\t"
      "flds 0x2533c8\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "fsubs 0x4(%%edi)\n\t"
      "movswl 0x1a(%%edx), %%eax\n\t"
      "movl %%eax, -0x20(%%ebp)\n\t"
      "fmuls 0x253f00\n\t"
      "fildl -0x20(%%ebp)\n\t"
      "fcompp\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jmp .LFUN_000d9960_17\n\t"
      ".LFUN_000d9960_22:\n\t"
      "cmpl $0x3f800000, 0x4(%%edi)\n\t"
      "jne .LFUN_000d9960_23\n\t"
      "movl -0x14(%%ebp), %%ecx\n\t"
      "movl 0x1b8(%%ecx), %%eax\n\t"
      "testb $8, %%ah\n\t"
      "jne .LFUN_000d9960_18\n\t"
      ".LFUN_000d9960_23:\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "movl (%%edx,%%ebx,4), %%eax\n\t"
      "jmp .LFUN_000d9960_37\n\t"
      ".LFUN_000d9960_24:\n\t"
      "cmpw $0, 0xe(%%edi)\n\t"
      "jne .LFUN_000d9960_36\n\t"
      "cmpw $0, 0x12(%%edi)\n\t"
      "jmp .LFUN_000d9960_35\n\t"
      ".LFUN_000d9960_25:\n\t"
      "movl -0x14(%%ebp), %%esi\n\t"
      "movb $1, %%al\n\t"
      "leal 0x2ce(%%esi), %%ecx\n\t"
      "movl $2, %%edx\n\t"
      ".LFUN_000d9960_26:\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000d9960_27\n\t"
      "cmpb $0, (%%ecx)\n\t"
      "jne .LFUN_000d9960_27\n\t"
      "movb $1, %%al\n\t"
      "jmp .LFUN_000d9960_28\n\t"
      ".LFUN_000d9960_27:\n\t"
      "xorb %%al, %%al\n\t"
      ".LFUN_000d9960_28:\n\t"
      "incl %%ecx\n\t"
      "decl %%edx\n\t"
      "jne .LFUN_000d9960_26\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000d9960_29\n\t"
      "movb 0x23d(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_000d9960_29\n\t"
      "movl 0x1b8(%%esi), %%eax\n\t"
      "testb $0x20, %%ah\n\t"
      "jne .LFUN_000d9960_18\n\t"
      ".LFUN_000d9960_29:\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "cmpl $-1, (%%edx,%%ebx,4)\n\t"
      "jne .LFUN_000d9960_18\n\t"
      "xorl %%esi, %%esi\n\t"
      "jmp .LFUN_000d9960_45\n\t"
      ".LFUN_000d9960_30:\n\t"
      "movw 0x12(%%edi), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "jne .LFUN_000d9960_38\n\t"
      "cmpw %%ax, 0xe(%%edi)\n\t"
      "je .LFUN_000d9960_38\n\t"
      "testw %%ax, %%ax\n\t"
      "jne .LFUN_000d9960_38\n\t"
      "movw 0xe(%%edi), %%ax\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "cmpw 0x16(%%ecx), %%ax\n\t"
      "jmp .LFUN_000d9960_42\n\t"
      ".LFUN_000d9960_31:\n\t"
      "movw 0x1c(%%edi), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "jne .LFUN_000d9960_40\n\t"
      "cmpw %%ax, 0x18(%%edi)\n\t"
      "je .LFUN_000d9960_38\n\t"
      "testw %%ax, %%ax\n\t"
      "je .LFUN_000d9960_38\n\t"
      "jmp .LFUN_000d9960_40\n\t"
      ".LFUN_000d9960_32:\n\t"
      "movw 0x1c(%%edi), %%cx\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "cmpw 0x14(%%edx), %%cx\n\t"
      "jg .LFUN_000d9960_38\n\t"
      "movb 0x16(%%edi), %%al\n\t"
      "jmp .LFUN_000d9960_16\n\t"
      ".LFUN_000d9960_33:\n\t"
      "movzbw 0x16(%%edi), %%si\n\t"
      "jmp .LFUN_000d9960_44\n\t"
      ".LFUN_000d9960_34:\n\t"
      "cmpw $0, 0x18(%%edi)\n\t"
      "jne .LFUN_000d9960_36\n\t"
      "cmpw $0, 0x1c(%%edi)\n\t"
      ".LFUN_000d9960_35:\n\t"
      "jne .LFUN_000d9960_36\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "movl 0x1b8(%%eax), %%ecx\n\t"
      "testb $8, %%ch\n\t"
      "jne .LFUN_000d9960_18\n\t"
      ".LFUN_000d9960_36:\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movl (%%ecx,%%ebx,4), %%eax\n\t"
      ".LFUN_000d9960_37:\n\t"
      "cmpl $-1, %%eax\n\t"
      "jne .LFUN_000d9960_18\n\t"
      ".LFUN_000d9960_38:\n\t"
      "xorl %%esi, %%esi\n\t"
      "jmp .LFUN_000d9960_45\n\t"
      ".LFUN_000d9960_39:\n\t"
      "movw 0x1c(%%edi), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "jne .LFUN_000d9960_38\n\t"
      "cmpw %%ax, 0x18(%%edi)\n\t"
      "je .LFUN_000d9960_38\n\t"
      "testw %%ax, %%ax\n\t"
      "jne .LFUN_000d9960_38\n\t"
      ".LFUN_000d9960_40:\n\t"
      "movw 0x18(%%edi), %%dx\n\t"
      ".LFUN_000d9960_41:\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "cmpw 0x16(%%eax), %%dx\n\t"
      ".LFUN_000d9960_42:\n\t"
      "jg .LFUN_000d9960_38\n\t"
      "jmp .LFUN_000d9960_18\n\t"
      ".LFUN_000d9960_43:\n\t"
      "pushl $1\n\t"
      "pushl $0x16e\n\t"
      "pushl $0x281eec\n\t"
      "pushl $0x255ee8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000d9960_44:\n\t"
      "testw %%si, %%si\n\t"
      "jg .LFUN_000d9960_19\n\t"
      ".LFUN_000d9960_45:\n\t"
      "cmpw $0, -0x10(%%ebp)\n\t"
      "je .LFUN_000d9960_19\n\t"
      "movl -0x24(%%ebp), %%eax\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "notl %%eax\n\t"
      "andl %%eax, %%ecx\n\t"
      "movl %%ecx, -0xc(%%ebp)\n\t"
      "jmp .LFUN_000d9960_20\n\t"
      ".LFUN_000d9960_46:\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movswl %%si, %%eax\n\t"
      "movl %%eax, (%%ecx,%%ebx,4)\n\t"
      "jmp .LFUN_000d9960_51\n\t"
      ".LFUN_000d9960_47:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movswl %%si, %%edx\n\t"
      "decl %%edx\n\t"
      "movl %%edx, (%%eax,%%ebx,4)\n\t"
      "jmp .LFUN_000d9960_51\n\t"
      ".LFUN_000d9960_48:\n\t"
      "testw %%si, %%si\n\t"
      "jne .LFUN_000d9960_49\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movl $0xffffffff, (%%ecx,%%ebx,4)\n\t"
      "jmp .LFUN_000d9960_51\n\t"
      ".LFUN_000d9960_49:\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "cmpl $-1, (%%edx,%%ebx,4)\n\t"
      "jne .LFUN_000d9960_51\n\t"
      "call *%[gtime]\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movl %%eax, (%%ecx,%%ebx,4)\n\t"
      "jmp .LFUN_000d9960_51\n\t"
      ".LFUN_000d9960_50:\n\t"
      "pushl $1\n\t"
      "pushl $0x197\n\t"
      "pushl $0x281eec\n\t"
      "pushl $0x255ee8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000d9960_51:\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "incl %%eax\n\t"
      "cmpw $0x13, %%ax\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "jl .LFUN_000d9960_6\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movl %%edx, 0x4c(%%eax)\n\t"
      "popl %%edi\n\t"
      ".LFUN_000d9960_52:\n\t"
      "movl $0x7f, %%eax\n\t"
      "movl $0x62626262, %%ecx\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".LFUN_000d9960_53:\n\t"
      "movswl %%ax, %%edx\n\t"
      "cmpl %%ecx, -0x2a8(%%ebp,%%edx,4)\n\t"
      "jne .LFUN_000d9960_10000\n\t"
      "decl %%eax\n\t"
      "testw %%ax, %%ax\n\t"
      "jge .LFUN_000d9960_53\n\t"
      "orl $0xffffffff, %%esi\n\t"
      "call *%[cd1540]\n\t"
      "cmpl %%eax, -0x28(%%ebp)\n\t"
      "je .LFUN_000d9960_54\n\t"
      "pushl $1\n\t"
      "pushl $0x19e\n\t"
      "pushl $0x281eec\n\t"
      "pushl $0x281960\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000d9960_54:\n\t"
      "cmpw $-1, %%si\n\t"
      "je .LFUN_000d9960_55\n\t"
      "pushl $1\n\t"
      "pushl $0x19e\n\t"
      "movswl %%si, %%eax\n\t"
      "pushl $0x281eec\n\t"
      "pushl %%eax\n\t"
      "pushl $0x281948\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0xc, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000d9960_55:\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000d9960_10000:\n\t"
      "jmp *%[cd9ead]\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_000d9960_jt0:\n\t"
      ".long .LFUN_000d9960_9\n\t"
      ".long .LFUN_000d9960_10\n\t"
      ".long .LFUN_000d9960_38\n\t"
      ".long .LFUN_000d9960_12\n\t"
      ".long .LFUN_000d9960_14\n\t"
      ".long .LFUN_000d9960_15\n\t"
      ".long .LFUN_000d9960_21\n\t"
      ".long .LFUN_000d9960_11\n\t"
      ".long .LFUN_000d9960_24\n\t"
      ".long .LFUN_000d9960_25\n\t"
      ".long .LFUN_000d9960_30\n\t"
      ".long .LFUN_000d9960_31\n\t"
      ".long .LFUN_000d9960_32\n\t"
      ".long .LFUN_000d9960_33\n\t"
      ".long .LFUN_000d9960_34\n\t"
      ".long .LFUN_000d9960_39\n\t"
      ".long .LFUN_000d9960_7\n\t"
      ".long .LFUN_000d9960_8\n\t"
      ".long .LFUN_000d9960_22\n\t"
      ".text\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_000d9960_jt1:\n\t"
      ".long .LFUN_000d9960_46\n\t"
      ".long .LFUN_000d9960_47\n\t"
      ".long .LFUN_000d9960_48\n\t"
      ".text\n\t"
      :
      : [cd1540] "m"(bd9960_cd1540), [memset] "m"(bd9960_memset), [cba3c0] "m"(bd9960_cba3c0), [dget] "m"(bd9960_dget), [tryget] "m"(bd9960_tryget), [cd8c30] "m"(bd9960_cd8c30), [tag] "m"(bd9960_tag), [get] "m"(bd9960_get), [cd8bc0] "m"(bd9960_cd8bc0), [c8f390] "m"(bd9960_c8f390), [cb6940] "m"(bd9960_cb6940), [cb6a70] "m"(bd9960_cb6a70), [assert] "m"(bd9960_assert), [exitfn] "m"(bd9960_exitfn), [gtime] "m"(bd9960_gtime), [c8d9d0] "m"(bd9960_c8d9d0), [cd9ead] "m"(bd9960_cd9ead)
      : "memory");
}
#else
#error "FUN_000d9960: clang naked draft required"
#endif


/* render_weapon_hud (0xd9f20) — XBE naked draft (batch 104). */
#if defined(__clang__)
static int (*const bd9f20_cd1540)(void) = FUN_000d1540;
static void *(*const bd9f20_memset)(void *, int, unsigned int) = csmemset;
static void *(*const bd9f20_tag)(int, int) = tag_get;
static void * (*const bd9f20_cd8bc0)(int16_t local_player_index) = FUN_000d8bc0;
static void * (*const bd9f20_c8e0b0)(void *destination, void *source, size_t size) = csmemcpy;
static __int16 (*const bd9f20_cba4b0)(void) = local_player_count;
static int (*const bd9f20_cd1c50)(float param_1) = FUN_000d1c50;
static int (*const bd9f20_gtime)(void) = game_time_get;
static void (*const bd9f20_ftol)(void) = FUN_001d9068;
static int (*const bd9f20_cb6620)(int16_t local_player_index) = player_control_get_target_object_index;
static float (*const bd9f20_cb6940)(int16_t local_player_index) = player_control_get_autoaim_level;
static int (*const bd9f20_cba3c0)(int16_t local_player_index) = local_player_get_player_index;
static void *(*const bd9f20_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void (*const bd9f20_useat)(int, float *) = unit_set_seat_state;
static vector3_t * (*const bd9f20_c1412f0)(int object_handle, vector3_t *out_position) = object_get_world_position;
static void (*const bd9f20_cd9f20)(void) = render_weapon_hud;
static scenario_t * (*const bd9f20_c18e380)(void) = global_scenario_get;
static void *(*const bd9f20_elem)(void *, int, int) = tag_block_get_element;
static void (*const bd9f20_cd3fe0)(int param_1, short *param_2, int param_3, unsigned int param_4, int param_5) = FUN_000d3fe0;
static void (*const bd9f20_cd3340)(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7, float param_8) = FUN_000d3340;
static float (*const bd9f20_c1d9e70)(float base, float exponent) = FUN_001d9e70;
static void (*const bd9f20_c1daf7e)(void) = FUN_001daf7e;
static void (*const bd9f20_cd3860)(short local_player, void *element, void *position, int value, int param_5, unsigned int flags, int timer_start, float scale) = FUN_000d3860;
static void (*const bd9f20_cd4260)(int param_1, int param_2, int param_3, unsigned int param_4, int param_5, unsigned char param_6, int param_7) = FUN_000d4260;
static void (*const bd9f20_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const bd9f20_exitfn)(int) = system_exit;
static char * (*const bd9f20_c8d9d0)(char *buffer, const char *format, ...) = csprintf;

__attribute__((naked, noinline))
void render_weapon_hud(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x284, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[cd1540]\n\t"
      "pushl $0x200\n\t"
      "movl %%eax, -0x48(%%ebp)\n\t"
      "leal -0x284(%%ebp), %%eax\n\t"
      "pushl $0x62\n\t"
      "pushl %%eax\n\t"
      "call *%[memset]\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x77706869\n\t"
      "call *%[tag]\n\t"
      "movl 0xc(%%ebp), %%esi\n\t"
      "movl %%eax, %%ebx\n\t"
      "addl $0x14, %%esp\n\t"
      "movl %%ebx, -0x1c(%%ebp)\n\t"
      "call *%[cd8bc0]\n\t"
      "movl %%eax, -0x30(%%ebp)\n\t"
      "xorl %%eax, %%eax\n\t"
      "movl %%eax, -0xe(%%ebp)\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movl %%eax, -0xa(%%ebp)\n\t"
      "movl %%eax, -0x6(%%ebp)\n\t"
      "movl %%ecx, -0x2a(%%ebp)\n\t"
      "movw %%ax, -0x2(%%ebp)\n\t"
      "movl %%ecx, -0x26(%%ebp)\n\t"
      "movl %%ecx, -0x22(%%ebp)\n\t"
      "movl %%eax, -0x42(%%ebp)\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw %%cx, -0x1e(%%ebp)\n\t"
      "movl %%eax, -0x3e(%%ebp)\n\t"
      "movl %%eax, -0x3a(%%ebp)\n\t"
      "movl %%ecx, -0x84(%%ebp)\n\t"
      "movl $7, %%ecx\n\t"
      "leal -0x80(%%ebp), %%edi\n\t"
      "movw %%dx, -0x10(%%ebp)\n\t"
      "movw %%dx, -0x2c(%%ebp)\n\t"
      "movw %%dx, -0x44(%%ebp)\n\t"
      "movw %%ax, -0x36(%%ebp)\n\t"
      "rep stosl\n\t"
      "testb $1, 0x10(%%ebx)\n\t"
      "je .Lrender_weapon_hud_1\n\t"
      "movl 0x18(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lrender_weapon_hud_1\n\t"
      "movl 0x1c(%%ebp), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "je .Lrender_weapon_hud_1\n\t"
      "movl 0x20(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .Lrender_weapon_hud_1\n\t"
      "pushl $0x10\n\t"
      "pushl %%eax\n\t"
      "leal -0x10(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c8e0b0]\n\t"
      "pushl $0x10\n\t"
      "leal -0x2c(%%ebp), %%edx\n\t"
      "pushl %%edi\n\t"
      "pushl %%edx\n\t"
      "call *%[c8e0b0]\n\t"
      "pushl $0x10\n\t"
      "leal -0x44(%%ebp), %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "call *%[c8e0b0]\n\t"
      "movl 0x14(%%ebp), %%edi\n\t"
      "movl 0xc(%%ebp), %%ebx\n\t"
      "addl $0x24, %%esp\n\t"
      "jmp .Lrender_weapon_hud_95\n\t"
      ".Lrender_weapon_hud_1:\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      "movw 0x12(%%ecx), %%ax\n\t"
      "cmpw 0x14(%%ebx), %%ax\n\t"
      "jg .Lrender_weapon_hud_2\n\t"
      "orw $1, %%dx\n\t"
      "jmp .Lrender_weapon_hud_3\n\t"
      ".Lrender_weapon_hud_2:\n\t"
      "andw $0xfffe, %%dx\n\t"
      ".Lrender_weapon_hud_3:\n\t"
      "testw %%ax, %%ax\n\t"
      "jne .Lrender_weapon_hud_4\n\t"
      "orw $2, %%dx\n\t"
      "jmp .Lrender_weapon_hud_5\n\t"
      ".Lrender_weapon_hud_4:\n\t"
      "andw $0xfffd, %%dx\n\t"
      ".Lrender_weapon_hud_5:\n\t"
      "movw %%dx, -0x10(%%ebp)\n\t"
      "call *%[cba4b0]\n\t"
      "cmpw $1, %%ax\n\t"
      "jle .Lrender_weapon_hud_6\n\t"
      "orb $4, -0x10(%%ebp)\n\t"
      "jmp .Lrender_weapon_hud_7\n\t"
      ".Lrender_weapon_hud_6:\n\t"
      "andb $0xfb, -0x10(%%ebp)\n\t"
      ".Lrender_weapon_hud_7:\n\t"
      "movl 0x14(%%ebp), %%esi\n\t"
      "movw 0xe(%%esi), %%dx\n\t"
      "cmpw 0x16(%%ebx), %%dx\n\t"
      "jg .Lrender_weapon_hud_8\n\t"
      "movb 0xc(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lrender_weapon_hud_8\n\t"
      "orb $1, -0xe(%%ebp)\n\t"
      "jmp .Lrender_weapon_hud_9\n\t"
      ".Lrender_weapon_hud_8:\n\t"
      "andb $0xfe, -0xe(%%ebp)\n\t"
      ".Lrender_weapon_hud_9:\n\t"
      "movl $0xfffffffd, %%edi\n\t"
      "andw %%di, -0xe(%%ebp)\n\t"
      "call *%[cba4b0]\n\t"
      "cmpw $1, %%ax\n\t"
      "jle .Lrender_weapon_hud_10\n\t"
      "orb $4, -0xe(%%ebp)\n\t"
      "jmp .Lrender_weapon_hud_11\n\t"
      ".Lrender_weapon_hud_10:\n\t"
      "andb $0xfb, -0xe(%%ebp)\n\t"
      ".Lrender_weapon_hud_11:\n\t"
      "movswl 0x18(%%ebx), %%eax\n\t"
      "flds (%%esi)\n\t"
      "fmuls 0x253f00\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "fildl -0x14(%%ebp)\n\t"
      "fcompp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .Lrender_weapon_hud_12\n\t"
      "orb $1, -0xc(%%ebp)\n\t"
      "jmp .Lrender_weapon_hud_13\n\t"
      ".Lrender_weapon_hud_12:\n\t"
      "andb $0xfe, -0xc(%%ebp)\n\t"
      ".Lrender_weapon_hud_13:\n\t"
      "andw %%di, -0xc(%%ebp)\n\t"
      "call *%[cba4b0]\n\t"
      "cmpw $1, %%ax\n\t"
      "jle .Lrender_weapon_hud_14\n\t"
      "orb $4, -0xc(%%ebp)\n\t"
      "jmp .Lrender_weapon_hud_15\n\t"
      ".Lrender_weapon_hud_14:\n\t"
      "andb $0xfb, -0xc(%%ebp)\n\t"
      ".Lrender_weapon_hud_15:\n\t"
      "flds 0x2533c8\n\t"
      "movswl 0x1a(%%ebx), %%ecx\n\t"
      "fsubs 0x4(%%esi)\n\t"
      "movl %%ecx, -0x14(%%ebp)\n\t"
      "fmuls 0x253f00\n\t"
      "fildl -0x14(%%ebp)\n\t"
      "fcompp\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .Lrender_weapon_hud_16\n\t"
      "orb $1, -0xa(%%ebp)\n\t"
      "jmp .Lrender_weapon_hud_17\n\t"
      ".Lrender_weapon_hud_16:\n\t"
      "andb $0xfe, -0xa(%%ebp)\n\t"
      ".Lrender_weapon_hud_17:\n\t"
      "flds 0x4(%%esi)\n\t"
      "pushl %%ecx\n\t"
      "fmuls 0x253f00\n\t"
      "fstps (%%esp)\n\t"
      "call *%[cd1c50]\n\t"
      "addl $4, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jge .Lrender_weapon_hud_18\n\t"
      "xorl %%eax, %%eax\n\t"
      "jmp .Lrender_weapon_hud_20\n\t"
      ".Lrender_weapon_hud_18:\n\t"
      "flds 0x4(%%esi)\n\t"
      "pushl %%ecx\n\t"
      "fmuls 0x253f00\n\t"
      "fstps (%%esp)\n\t"
      "call *%[cd1c50]\n\t"
      "addl $4, %%esp\n\t"
      "cmpl $0x64, %%eax\n\t"
      "jle .Lrender_weapon_hud_19\n\t"
      "movl $0x64, %%eax\n\t"
      "jmp .Lrender_weapon_hud_20\n\t"
      ".Lrender_weapon_hud_19:\n\t"
      "flds 0x4(%%esi)\n\t"
      "pushl %%ecx\n\t"
      "fmuls 0x253f00\n\t"
      "fstps (%%esp)\n\t"
      "call *%[cd1c50]\n\t"
      "addl $4, %%esp\n\t"
      ".Lrender_weapon_hud_20:\n\t"
      "movl $0x64, %%edx\n\t"
      "subl %%eax, %%edx\n\t"
      "jne .Lrender_weapon_hud_21\n\t"
      "orb $2, -0xa(%%ebp)\n\t"
      "jmp .Lrender_weapon_hud_22\n\t"
      ".Lrender_weapon_hud_21:\n\t"
      "andw %%di, -0xa(%%ebp)\n\t"
      ".Lrender_weapon_hud_22:\n\t"
      "call *%[cba4b0]\n\t"
      "cmpw $1, %%ax\n\t"
      "jle .Lrender_weapon_hud_23\n\t"
      "orb $4, -0xa(%%ebp)\n\t"
      "jmp .Lrender_weapon_hud_24\n\t"
      ".Lrender_weapon_hud_23:\n\t"
      "andb $0xfb, -0xa(%%ebp)\n\t"
      ".Lrender_weapon_hud_24:\n\t"
      "movw 0x1c(%%esi), %%ax\n\t"
      "cmpw 0x14(%%ebx), %%ax\n\t"
      "jg .Lrender_weapon_hud_25\n\t"
      "orb $1, -0x8(%%ebp)\n\t"
      "jmp .Lrender_weapon_hud_26\n\t"
      ".Lrender_weapon_hud_25:\n\t"
      "andb $0xfe, -0x8(%%ebp)\n\t"
      ".Lrender_weapon_hud_26:\n\t"
      "testw %%ax, %%ax\n\t"
      "jne .Lrender_weapon_hud_27\n\t"
      "orb $2, -0x8(%%ebp)\n\t"
      "jmp .Lrender_weapon_hud_28\n\t"
      ".Lrender_weapon_hud_27:\n\t"
      "andw %%di, -0x8(%%ebp)\n\t"
      ".Lrender_weapon_hud_28:\n\t"
      "call *%[cba4b0]\n\t"
      "cmpw $1, %%ax\n\t"
      "jle .Lrender_weapon_hud_29\n\t"
      "orb $4, -0x8(%%ebp)\n\t"
      "jmp .Lrender_weapon_hud_30\n\t"
      ".Lrender_weapon_hud_29:\n\t"
      "andb $0xfb, -0x8(%%ebp)\n\t"
      ".Lrender_weapon_hud_30:\n\t"
      "movw 0x18(%%esi), %%ax\n\t"
      "cmpw 0x16(%%ebx), %%ax\n\t"
      "jg .Lrender_weapon_hud_31\n\t"
      "movb 0x16(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lrender_weapon_hud_31\n\t"
      "orb $1, -0x6(%%ebp)\n\t"
      "jmp .Lrender_weapon_hud_32\n\t"
      ".Lrender_weapon_hud_31:\n\t"
      "andb $0xfe, -0x6(%%ebp)\n\t"
      ".Lrender_weapon_hud_32:\n\t"
      "andw %%di, -0x6(%%ebp)\n\t"
      "call *%[cba4b0]\n\t"
      "cmpw $1, %%ax\n\t"
      "jle .Lrender_weapon_hud_33\n\t"
      "orb $4, -0x6(%%ebp)\n\t"
      "jmp .Lrender_weapon_hud_34\n\t"
      ".Lrender_weapon_hud_33:\n\t"
      "andb $0xfb, -0x6(%%ebp)\n\t"
      ".Lrender_weapon_hud_34:\n\t"
      "movl -0x30(%%ebp), %%esi\n\t"
      "leal -0x10(%%ebp), %%edi\n\t"
      "movl $8, %%ebx\n\t"
      ".Lrender_weapon_hud_35:\n\t"
      "testb $1, (%%edi)\n\t"
      "je .Lrender_weapon_hud_36\n\t"
      "cmpl $-1, (%%esi)\n\t"
      "jne .Lrender_weapon_hud_37\n\t"
      "call *%[gtime]\n\t"
      "movl %%eax, (%%esi)\n\t"
      "jmp .Lrender_weapon_hud_37\n\t"
      ".Lrender_weapon_hud_36:\n\t"
      "movl $0xffffffff, (%%esi)\n\t"
      ".Lrender_weapon_hud_37:\n\t"
      "addl $2, %%edi\n\t"
      "addl $4, %%esi\n\t"
      "decl %%ebx\n\t"
      "jne .Lrender_weapon_hud_35\n\t"
      "movl 0x14(%%ebp), %%esi\n\t"
      "movw 0x12(%%esi), %%cx\n\t"
      "movl -0x1c(%%ebp), %%edi\n\t"
      "cmpw 0x14(%%edi), %%cx\n\t"
      "jg .Lrender_weapon_hud_38\n\t"
      "movb 0xc(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lrender_weapon_hud_38\n\t"
      "movw -0x2c(%%ebp), %%ax\n\t"
      "orw $1, %%ax\n\t"
      "jmp .Lrender_weapon_hud_39\n\t"
      ".Lrender_weapon_hud_38:\n\t"
      "movw -0x2c(%%ebp), %%ax\n\t"
      "andw $0xfffe, %%ax\n\t"
      ".Lrender_weapon_hud_39:\n\t"
      "movb 0xc(%%esi), %%dl\n\t"
      "testb %%dl, %%dl\n\t"
      "je .Lrender_weapon_hud_40\n\t"
      "orw $4, %%ax\n\t"
      "jmp .Lrender_weapon_hud_41\n\t"
      ".Lrender_weapon_hud_40:\n\t"
      "andw $0xfffb, %%ax\n\t"
      ".Lrender_weapon_hud_41:\n\t"
      "testw %%cx, %%cx\n\t"
      "jne .Lrender_weapon_hud_42\n\t"
      "orw $2, %%ax\n\t"
      "jmp .Lrender_weapon_hud_43\n\t"
      ".Lrender_weapon_hud_42:\n\t"
      "andw $0xfffd, %%ax\n\t"
      ".Lrender_weapon_hud_43:\n\t"
      "testw %%ax, %%ax\n\t"
      "jne .Lrender_weapon_hud_44\n\t"
      "movw $8, %%ax\n\t"
      "jmp .Lrender_weapon_hud_45\n\t"
      ".Lrender_weapon_hud_44:\n\t"
      "andw $0xfff7, %%ax\n\t"
      ".Lrender_weapon_hud_45:\n\t"
      "movw 0xe(%%esi), %%cx\n\t"
      "orw $0x10, %%ax\n\t"
      "movw %%ax, -0x2c(%%ebp)\n\t"
      "cmpw 0x16(%%edi), %%cx\n\t"
      "movw -0x2a(%%ebp), %%ax\n\t"
      "jg .Lrender_weapon_hud_46\n\t"
      "orw $1, %%ax\n\t"
      "jmp .Lrender_weapon_hud_47\n\t"
      ".Lrender_weapon_hud_46:\n\t"
      "andw $0xfffe, %%ax\n\t"
      ".Lrender_weapon_hud_47:\n\t"
      "testb %%dl, %%dl\n\t"
      "je .Lrender_weapon_hud_48\n\t"
      "orw $4, %%ax\n\t"
      "jmp .Lrender_weapon_hud_49\n\t"
      ".Lrender_weapon_hud_48:\n\t"
      "andw $0xfffb, %%ax\n\t"
      ".Lrender_weapon_hud_49:\n\t"
      "testw %%cx, %%cx\n\t"
      "jne .Lrender_weapon_hud_50\n\t"
      "orw $2, %%ax\n\t"
      "jmp .Lrender_weapon_hud_51\n\t"
      ".Lrender_weapon_hud_50:\n\t"
      "andw $0xfffd, %%ax\n\t"
      ".Lrender_weapon_hud_51:\n\t"
      "testw %%ax, %%ax\n\t"
      "jne .Lrender_weapon_hud_52\n\t"
      "movw $8, %%ax\n\t"
      "jmp .Lrender_weapon_hud_53\n\t"
      ".Lrender_weapon_hud_52:\n\t"
      "andw $0xfff7, %%ax\n\t"
      ".Lrender_weapon_hud_53:\n\t"
      "flds (%%esi)\n\t"
      "orw $0x10, %%ax\n\t"
      "fmuls 0x253f00\n\t"
      "movw %%ax, -0x2a(%%ebp)\n\t"
      "movswl 0x18(%%edi), %%ecx\n\t"
      "movl %%ecx, -0x14(%%ebp)\n\t"
      "fildl -0x14(%%ebp)\n\t"
      "fcompp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .Lrender_weapon_hud_54\n\t"
      "orb $1, -0x28(%%ebp)\n\t"
      "jmp .Lrender_weapon_hud_55\n\t"
      ".Lrender_weapon_hud_54:\n\t"
      "andb $0xfe, -0x28(%%ebp)\n\t"
      ".Lrender_weapon_hud_55:\n\t"
      "movb 0x8(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lrender_weapon_hud_56\n\t"
      "orb $4, -0x28(%%ebp)\n\t"
      "jmp .Lrender_weapon_hud_57\n\t"
      ".Lrender_weapon_hud_56:\n\t"
      "andb $0xfb, -0x28(%%ebp)\n\t"
      ".Lrender_weapon_hud_57:\n\t"
      "movl 0x14(%%ebp), %%edi\n\t"
      "flds 0x4(%%edi)\n\t"
      "pushl %%ecx\n\t"
      "fmuls 0x253f00\n\t"
      "fstps (%%esp)\n\t"
      "call *%[cd1c50]\n\t"
      "addl $4, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jge .Lrender_weapon_hud_58\n\t"
      "xorl %%eax, %%eax\n\t"
      "jmp .Lrender_weapon_hud_60\n\t"
      ".Lrender_weapon_hud_58:\n\t"
      "flds 0x4(%%edi)\n\t"
      "pushl %%ecx\n\t"
      "fmuls 0x253f00\n\t"
      "fstps (%%esp)\n\t"
      "call *%[cd1c50]\n\t"
      "addl $4, %%esp\n\t"
      "cmpl $0x64, %%eax\n\t"
      "jle .Lrender_weapon_hud_59\n\t"
      "movl $0x64, %%eax\n\t"
      "jmp .Lrender_weapon_hud_60\n\t"
      ".Lrender_weapon_hud_59:\n\t"
      "flds 0x4(%%edi)\n\t"
      "pushl %%ecx\n\t"
      "fmuls 0x253f00\n\t"
      "fstps (%%esp)\n\t"
      "call *%[cd1c50]\n\t"
      "addl $4, %%esp\n\t"
      ".Lrender_weapon_hud_60:\n\t"
      "movl $0x64, %%edx\n\t"
      "subl %%eax, %%edx\n\t"
      "movw -0x28(%%ebp), %%ax\n\t"
      "jne .Lrender_weapon_hud_61\n\t"
      "orw $2, %%ax\n\t"
      "jmp .Lrender_weapon_hud_62\n\t"
      ".Lrender_weapon_hud_61:\n\t"
      "andw $0xfffd, %%ax\n\t"
      ".Lrender_weapon_hud_62:\n\t"
      "testw %%ax, %%ax\n\t"
      "jne .Lrender_weapon_hud_63\n\t"
      "movw $8, %%ax\n\t"
      "jmp .Lrender_weapon_hud_64\n\t"
      ".Lrender_weapon_hud_63:\n\t"
      "andw $0xfff7, %%ax\n\t"
      ".Lrender_weapon_hud_64:\n\t"
      "flds 0x2533c8\n\t"
      "movl -0x1c(%%ebp), %%esi\n\t"
      "fsubs 0x4(%%edi)\n\t"
      "orw $0x10, %%ax\n\t"
      "movw %%ax, -0x28(%%ebp)\n\t"
      "movswl 0x1a(%%esi), %%eax\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "fmuls 0x253f00\n\t"
      "fildl -0x14(%%ebp)\n\t"
      "fcompp\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .Lrender_weapon_hud_65\n\t"
      "orb $1, -0x26(%%ebp)\n\t"
      "jmp .Lrender_weapon_hud_66\n\t"
      ".Lrender_weapon_hud_65:\n\t"
      "andb $0xfe, -0x26(%%ebp)\n\t"
      ".Lrender_weapon_hud_66:\n\t"
      "movb 0x8(%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lrender_weapon_hud_67\n\t"
      "orb $4, -0x26(%%ebp)\n\t"
      "jmp .Lrender_weapon_hud_68\n\t"
      ".Lrender_weapon_hud_67:\n\t"
      "andb $0xfb, -0x26(%%ebp)\n\t"
      ".Lrender_weapon_hud_68:\n\t"
      "flds 0x4(%%edi)\n\t"
      "pushl %%ecx\n\t"
      "fmuls 0x253f00\n\t"
      "fstps (%%esp)\n\t"
      "call *%[cd1c50]\n\t"
      "addl $4, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jge .Lrender_weapon_hud_69\n\t"
      "xorl %%eax, %%eax\n\t"
      "jmp .Lrender_weapon_hud_71\n\t"
      ".Lrender_weapon_hud_69:\n\t"
      "flds 0x4(%%edi)\n\t"
      "pushl %%ecx\n\t"
      "fmuls 0x253f00\n\t"
      "fstps (%%esp)\n\t"
      "call *%[cd1c50]\n\t"
      "addl $4, %%esp\n\t"
      "cmpl $0x64, %%eax\n\t"
      "jle .Lrender_weapon_hud_70\n\t"
      "movl $0x64, %%eax\n\t"
      "jmp .Lrender_weapon_hud_71\n\t"
      ".Lrender_weapon_hud_70:\n\t"
      "flds 0x4(%%edi)\n\t"
      "pushl %%ecx\n\t"
      "fmuls 0x253f00\n\t"
      "fstps (%%esp)\n\t"
      "call *%[cd1c50]\n\t"
      "addl $4, %%esp\n\t"
      ".Lrender_weapon_hud_71:\n\t"
      "movl $0x64, %%ecx\n\t"
      "subl %%eax, %%ecx\n\t"
      "movw -0x26(%%ebp), %%ax\n\t"
      "jne .Lrender_weapon_hud_72\n\t"
      "orw $2, %%ax\n\t"
      "jmp .Lrender_weapon_hud_73\n\t"
      ".Lrender_weapon_hud_72:\n\t"
      "andw $0xfffd, %%ax\n\t"
      ".Lrender_weapon_hud_73:\n\t"
      "testw %%ax, %%ax\n\t"
      "jne .Lrender_weapon_hud_74\n\t"
      "movw $8, %%ax\n\t"
      "jmp .Lrender_weapon_hud_75\n\t"
      ".Lrender_weapon_hud_74:\n\t"
      "andw $0xfff7, %%ax\n\t"
      ".Lrender_weapon_hud_75:\n\t"
      "movw 0x1c(%%edi), %%bx\n\t"
      "orw $0x10, %%ax\n\t"
      "movw %%ax, -0x26(%%ebp)\n\t"
      "cmpw 0x14(%%esi), %%bx\n\t"
      "jg .Lrender_weapon_hud_76\n\t"
      "movb 0x16(%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lrender_weapon_hud_76\n\t"
      "movw -0x2c(%%ebp), %%ax\n\t"
      "orw $1, %%ax\n\t"
      "jmp .Lrender_weapon_hud_77\n\t"
      ".Lrender_weapon_hud_76:\n\t"
      "movw -0x2c(%%ebp), %%ax\n\t"
      "andw $0xfffe, %%ax\n\t"
      ".Lrender_weapon_hud_77:\n\t"
      "movb 0x16(%%edi), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "je .Lrender_weapon_hud_78\n\t"
      "orw $4, %%ax\n\t"
      "jmp .Lrender_weapon_hud_79\n\t"
      ".Lrender_weapon_hud_78:\n\t"
      "andw $0xfffb, %%ax\n\t"
      ".Lrender_weapon_hud_79:\n\t"
      "testw %%bx, %%bx\n\t"
      "jne .Lrender_weapon_hud_80\n\t"
      "orw $2, %%ax\n\t"
      "jmp .Lrender_weapon_hud_81\n\t"
      ".Lrender_weapon_hud_80:\n\t"
      "andw $0xfffd, %%ax\n\t"
      ".Lrender_weapon_hud_81:\n\t"
      "testw %%ax, %%ax\n\t"
      "jne .Lrender_weapon_hud_82\n\t"
      "movw $8, %%ax\n\t"
      "jmp .Lrender_weapon_hud_83\n\t"
      ".Lrender_weapon_hud_82:\n\t"
      "andw $0xfff7, %%ax\n\t"
      ".Lrender_weapon_hud_83:\n\t"
      "movw 0x18(%%edi), %%si\n\t"
      "movl -0x1c(%%ebp), %%edx\n\t"
      "orw $0x10, %%ax\n\t"
      "movw %%ax, -0x2c(%%ebp)\n\t"
      "cmpw 0x16(%%edx), %%si\n\t"
      "movw -0x2a(%%ebp), %%ax\n\t"
      "jg .Lrender_weapon_hud_84\n\t"
      "orw $1, %%ax\n\t"
      "jmp .Lrender_weapon_hud_85\n\t"
      ".Lrender_weapon_hud_84:\n\t"
      "andw $0xfffe, %%ax\n\t"
      ".Lrender_weapon_hud_85:\n\t"
      "testb %%cl, %%cl\n\t"
      "je .Lrender_weapon_hud_86\n\t"
      "orw $4, %%ax\n\t"
      "jmp .Lrender_weapon_hud_87\n\t"
      ".Lrender_weapon_hud_86:\n\t"
      "andw $0xfffb, %%ax\n\t"
      ".Lrender_weapon_hud_87:\n\t"
      "testw %%si, %%si\n\t"
      "jne .Lrender_weapon_hud_88\n\t"
      "orw $2, %%ax\n\t"
      "jmp .Lrender_weapon_hud_89\n\t"
      ".Lrender_weapon_hud_88:\n\t"
      "andw $0xfffd, %%ax\n\t"
      ".Lrender_weapon_hud_89:\n\t"
      "testw %%ax, %%ax\n\t"
      "jne .Lrender_weapon_hud_90\n\t"
      "movw $8, %%ax\n\t"
      "jmp .Lrender_weapon_hud_91\n\t"
      ".Lrender_weapon_hud_90:\n\t"
      "andw $0xfff7, %%ax\n\t"
      ".Lrender_weapon_hud_91:\n\t"
      "flds (%%edi)\n\t"
      "movw 0xe(%%edi), %%cx\n\t"
      "fmuls 0x2602c8\n\t"
      "orw $0x10, %%ax\n\t"
      "movw %%ax, -0x2a(%%ebp)\n\t"
      "movw 0x12(%%edi), %%ax\n\t"
      "movw %%ax, -0x44(%%ebp)\n\t"
      "movw %%cx, -0x42(%%ebp)\n\t"
      "call *%[ftol]\n\t"
      "flds 0x2533c8\n\t"
      "fsubs 0x4(%%edi)\n\t"
      "movw %%ax, -0x40(%%ebp)\n\t"
      "fmuls 0x253f00\n\t"
      "call *%[ftol]\n\t"
      "movw %%bx, -0x3c(%%ebp)\n\t"
      "movl 0xc(%%ebp), %%ebx\n\t"
      "pushl %%ebx\n\t"
      "movw %%ax, -0x3e(%%ebp)\n\t"
      "movw %%si, -0x3a(%%ebp)\n\t"
      "call *%[cb6620]\n\t"
      "pushl %%ebx\n\t"
      "movl %%eax, %%esi\n\t"
      "call *%[cb6940]\n\t"
      "fcomps 0x2533c8\n\t"
      "addl $8, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .Lrender_weapon_hud_94\n\t"
      "cmpl $-1, %%esi\n\t"
      "je .Lrender_weapon_hud_94\n\t"
      "pushl %%ebx\n\t"
      "call *%[cba3c0]\n\t"
      "addl $4, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "jne .Lrender_weapon_hud_92\n\t"
      "orl %%eax, %%eax\n\t"
      "jmp .Lrender_weapon_hud_93\n\t"
      ".Lrender_weapon_hud_92:\n\t"
      "pushl %%ebx\n\t"
      "call *%[cba3c0]\n\t"
      "movl 0x5aa6d4, %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%edx\n\t"
      "call *%[dget]\n\t"
      "movl 0x34(%%eax), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      ".Lrender_weapon_hud_93:\n\t"
      "leal -0x58(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "call *%[useat]\n\t"
      "leal -0x64(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%esi\n\t"
      "call *%[c1412f0]\n\t"
      "flds -0x58(%%ebp)\n\t"
      "fsubs -0x64(%%ebp)\n\t"
      "addl $0x10, %%esp\n\t"
      "flds -0x54(%%ebp)\n\t"
      "fsubs -0x60(%%ebp)\n\t"
      "flds -0x50(%%ebp)\n\t"
      "fsubs -0x5c(%%ebp)\n\t"
      "fld %%st(1)\n\t"
      ".byte 0xd8, 0xca\n\t"
      "fld %%st(3)\n\t"
      ".byte 0xd8, 0xcc\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fld %%st(1)\n\t"
      ".byte 0xd8, 0xca\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fsqrt\n\t"
      "fstp %%st(3)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "fmuls 0x281e00\n\t"
      "fstps -0x6c(%%ebp)\n\t"
      "flds -0x5c(%%ebp)\n\t"
      "fsubs -0x50(%%ebp)\n\t"
      "fmuls 0x281e00\n\t"
      "fstps -0x68(%%ebp)\n\t"
      "jmp .Lrender_weapon_hud_95\n\t"
      ".Lrender_weapon_hud_94:\n\t"
      "movl $0xffc00000, %%eax\n\t"
      "movl %%eax, -0x6c(%%ebp)\n\t"
      "movl %%eax, -0x68(%%ebp)\n\t"
      ".Lrender_weapon_hud_95:\n\t"
      "movl -0x1c(%%ebp), %%eax\n\t"
      "movl 0xc(%%eax), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lrender_weapon_hud_96\n\t"
      "leal -0x44(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x2c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "leal -0x10(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edi\n\t"
      "pushl %%edx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "call *%[cd9f20]\n\t"
      "addl $0x1c, %%esp\n\t"
      ".Lrender_weapon_hud_96:\n\t"
      "call *%[c18e380]\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "cmpw $2, 0x3c(%%eax)\n\t"
      "setne %%cl\n\t"
      "movl %%ecx, %%esi\n\t"
      "call *%[cba4b0]\n\t"
      "cmpw $1, %%ax\n\t"
      "jne .Lrender_weapon_hud_97\n\t"
      "orl $2, %%esi\n\t"
      "jmp .Lrender_weapon_hud_98\n\t"
      ".Lrender_weapon_hud_97:\n\t"
      "andl $0xfffffffd, %%esi\n\t"
      ".Lrender_weapon_hud_98:\n\t"
      "call *%[cba4b0]\n\t"
      "cmpw $1, %%ax\n\t"
      "jle .Lrender_weapon_hud_99\n\t"
      "orl $4, %%esi\n\t"
      "jmp .Lrender_weapon_hud_100\n\t"
      ".Lrender_weapon_hud_99:\n\t"
      "andl $0xfffffffb, %%esi\n\t"
      ".Lrender_weapon_hud_100:\n\t"
      "movl -0x1c(%%ebp), %%edi\n\t"
      "movl 0x60(%%edi), %%ecx\n\t"
      "movl %%esi, -0x34(%%ebp)\n\t"
      "leal 0x60(%%edi), %%esi\n\t"
      "xorl %%eax, %%eax\n\t"
      "cmpl %%eax, %%ecx\n\t"
      "movl %%eax, -0x18(%%ebp)\n\t"
      "jle .Lrender_weapon_hud_103\n\t"
      "leal (%%esp), %%esp\n\t"
      ".Lrender_weapon_hud_101:\n\t"
      "pushl $0xb4\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[elem]\n\t"
      "movb 0x2(%%eax), %%cl\n\t"
      "addl $0xc, %%esp\n\t"
      "testb $1, %%cl\n\t"
      "jne .Lrender_weapon_hud_102\n\t"
      "movb 0x4(%%eax), %%cl\n\t"
      "movl $1, %%edx\n\t"
      "shll %%cl, %%edx\n\t"
      "movswl -0x34(%%ebp), %%ecx\n\t"
      "testl %%edx, %%ecx\n\t"
      "je .Lrender_weapon_hud_102\n\t"
      "movswl (%%eax), %%ecx\n\t"
      "movl -0x30(%%ebp), %%edx\n\t"
      "movl (%%edx,%%ecx,4), %%edx\n\t"
      "movswl -0x10(%%ebp,%%ecx,2), %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ecx\n\t"
      "addl $0x24, %%eax\n\t"
      "pushl %%eax\n\t"
      "leal 0x3c(%%edi), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ebx\n\t"
      "call *%[cd3fe0]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrender_weapon_hud_102:\n\t"
      "movl -0x18(%%ebp), %%eax\n\t"
      "movl (%%esi), %%ecx\n\t"
      "incl %%eax\n\t"
      "movl %%eax, -0x18(%%ebp)\n\t"
      "movswl %%ax, %%eax\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jl .Lrender_weapon_hud_101\n\t"
      ".Lrender_weapon_hud_103:\n\t"
      "movl 0x6c(%%edi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "leal 0x6c(%%edi), %%esi\n\t"
      "movl $0, -0x18(%%ebp)\n\t"
      "jle .Lrender_weapon_hud_106\n\t"
      "xorl %%eax, %%eax\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".Lrender_weapon_hud_104:\n\t"
      "pushl $0xb4\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[elem]\n\t"
      "movb 0x2(%%eax), %%cl\n\t"
      "addl $0xc, %%esp\n\t"
      "testb $1, %%cl\n\t"
      "jne .Lrender_weapon_hud_105\n\t"
      "movb 0x4(%%eax), %%cl\n\t"
      "movl $1, %%edx\n\t"
      "shll %%cl, %%edx\n\t"
      "movswl -0x34(%%ebp), %%ecx\n\t"
      "testl %%edx, %%ecx\n\t"
      "je .Lrender_weapon_hud_105\n\t"
      "movswl (%%eax), %%ecx\n\t"
      "movl -0x30(%%ebp), %%edi\n\t"
      "pushl $0\n\t"
      "pushl %%ecx\n\t"
      "fildl (%%edi,%%ecx,4)\n\t"
      "movl -0x1c(%%ebp), %%edi\n\t"
      "xorl %%edx, %%edx\n\t"
      "movb -0x44(%%ebp,%%ecx,2), %%dl\n\t"
      "movswl -0x10(%%ebp,%%ecx,2), %%ecx\n\t"
      "fstps (%%esp)\n\t"
      "pushl %%ecx\n\t"
      "addl $0x24, %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "leal 0x3c(%%edi), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ebx\n\t"
      "call *%[cd3340]\n\t"
      "addl $0x20, %%esp\n\t"
      ".Lrender_weapon_hud_105:\n\t"
      "movl -0x18(%%ebp), %%eax\n\t"
      "movl (%%esi), %%ecx\n\t"
      "incl %%eax\n\t"
      "movl %%eax, -0x18(%%ebp)\n\t"
      "movswl %%ax, %%eax\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jl .Lrender_weapon_hud_104\n\t"
      ".Lrender_weapon_hud_106:\n\t"
      "movl 0x78(%%edi), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "leal 0x78(%%edi), %%eax\n\t"
      "movl $0, -0x18(%%ebp)\n\t"
      "jle .Lrender_weapon_hud_112\n\t"
      "xorl %%ecx, %%ecx\n\t"
      ".Lrender_weapon_hud_107:\n\t"
      "pushl $0xa0\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl %%eax, %%edi\n\t"
      "movb 0x2(%%edi), %%al\n\t"
      "addl $0xc, %%esp\n\t"
      "testb $1, %%al\n\t"
      "jne .Lrender_weapon_hud_111\n\t"
      "movb 0x4(%%edi), %%cl\n\t"
      "movl $1, %%eax\n\t"
      "shll %%cl, %%eax\n\t"
      "movswl -0x34(%%ebp), %%ecx\n\t"
      "testl %%eax, %%ecx\n\t"
      "je .Lrender_weapon_hud_111\n\t"
      "testb $1, 0x78(%%edi)\n\t"
      "movl $1, %%esi\n\t"
      "je .Lrender_weapon_hud_108\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "pushl $0x70\n\t"
      "addl $0x4f0, %%edx\n\t"
      "pushl $0\n\t"
      "pushl %%edx\n\t"
      "call *%[elem]\n\t"
      "movw 0xa(%%eax), %%si\n\t"
      "addl $0xc, %%esp\n\t"
      ".Lrender_weapon_hud_108:\n\t"
      "movb 0x6a(%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lrender_weapon_hud_109\n\t"
      "movswl (%%edi), %%ebx\n\t"
      "movl -0x84(%%ebp,%%ebx,4), %%eax\n\t"
      "cmpl $0xffc00000, %%eax\n\t"
      "leal -0x84(%%ebp,%%ebx,4), %%ebx\n\t"
      "je .Lrender_weapon_hud_111\n\t"
      "fldl 0x281df0\n\t"
      "fldl 0x281de8\n\t"
      "call *%[c1d9e70]\n\t"
      "fsts -0x14(%%ebp)\n\t"
      "fmuls (%%ebx)\n\t"
      "fabs\n\t"
      "flds -0x14(%%ebp)\n\t"
      "call *%[c1daf7e]\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fistps -0x4c(%%ebp)\n\t"
      "movswl (%%edi), %%eax\n\t"
      "movl -0x30(%%ebp), %%ecx\n\t"
      "movl (%%ecx,%%eax,4), %%edx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw -0x10(%%ebp,%%eax,2), %%cx\n\t"
      "pushl $0\n\t"
      "pushl %%edx\n\t"
      "movl -0x4c(%%ebp), %%edx\n\t"
      "pushl %%ecx\n\t"
      "movswl %%si, %%ecx\n\t"
      "movl %%ecx, -0x14(%%ebp)\n\t"
      "pushl %%edx\n\t"
      "fildl -0x14(%%ebp)\n\t"
      "pushl %%ecx\n\t"
      "fdivrs -0x84(%%ebp,%%eax,4)\n\t"
      "fstps (%%esp)\n\t"
      "call *%[cd1c50]\n\t"
      "addl $4, %%esp\n\t"
      "jmp .Lrender_weapon_hud_110\n\t"
      ".Lrender_weapon_hud_109:\n\t"
      "movswl (%%edi), %%eax\n\t"
      "movl -0x30(%%ebp), %%ecx\n\t"
      "movl (%%ecx,%%eax,4), %%edx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw -0x10(%%ebp,%%eax,2), %%cx\n\t"
      "movswl -0x44(%%ebp,%%eax,2), %%eax\n\t"
      "pushl $0\n\t"
      "pushl %%edx\n\t"
      "cdq\n\t"
      "pushl %%ecx\n\t"
      "movswl %%si, %%ecx\n\t"
      "pushl $-1\n\t"
      "idivl %%ecx\n\t"
      ".Lrender_weapon_hud_110:\n\t"
      "movl -0x1c(%%ebp), %%edx\n\t"
      "pushl %%eax\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "addl $0x24, %%edi\n\t"
      "addl $0x3c, %%edx\n\t"
      "pushl %%edi\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[cd3860]\n\t"
      "addl $0x20, %%esp\n\t"
      ".Lrender_weapon_hud_111:\n\t"
      "movl -0x18(%%ebp), %%eax\n\t"
      "incl %%eax\n\t"
      "movswl %%ax, %%ecx\n\t"
      "movl %%eax, -0x18(%%ebp)\n\t"
      "movl -0x1c(%%ebp), %%eax\n\t"
      "movl 0x78(%%eax), %%edx\n\t"
      "addl $0x78, %%eax\n\t"
      "cmpl %%edx, %%ecx\n\t"
      "jl .Lrender_weapon_hud_107\n\t"
      ".Lrender_weapon_hud_112:\n\t"
      "movl -0x1c(%%ebp), %%ebx\n\t"
      "movl 0x90(%%ebx), %%ecx\n\t"
      "addl $0x90, %%ebx\n\t"
      "xorl %%eax, %%eax\n\t"
      "cmpl %%eax, %%ecx\n\t"
      "movl %%eax, -0x18(%%ebp)\n\t"
      "jle .Lrender_weapon_hud_115\n\t"
      ".Lrender_weapon_hud_113:\n\t"
      "pushl $0x68\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "call *%[elem]\n\t"
      "movl %%eax, %%edi\n\t"
      "movb 0x2(%%edi), %%al\n\t"
      "addl $0xc, %%esp\n\t"
      "testb $1, %%al\n\t"
      "jne .Lrender_weapon_hud_114\n\t"
      "movb 0x4(%%edi), %%cl\n\t"
      "movswl -0x34(%%ebp), %%eax\n\t"
      "movl $1, %%edx\n\t"
      "shll %%cl, %%edx\n\t"
      "testl %%edx, %%eax\n\t"
      "je .Lrender_weapon_hud_114\n\t"
      "movswl (%%edi), %%esi\n\t"
      "call *%[cba4b0]\n\t"
      "cmpw $1, %%ax\n\t"
      "movl -0x30(%%ebp), %%eax\n\t"
      "setg %%cl\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw -0x10(%%ebp,%%esi,2), %%dx\n\t"
      "addl $0x24, %%edi\n\t"
      "pushl %%ecx\n\t"
      "movl (%%eax,%%esi,4), %%ecx\n\t"
      "movl -0x1c(%%ebp), %%eax\n\t"
      "pushl %%edx\n\t"
      "movswl -0x2c(%%ebp,%%esi,2), %%edx\n\t"
      "pushl %%ecx\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "addl $0x3c, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[cd4260]\n\t"
      "addl $0x1c, %%esp\n\t"
      ".Lrender_weapon_hud_114:\n\t"
      "movl -0x18(%%ebp), %%eax\n\t"
      "movl (%%ebx), %%ecx\n\t"
      "incl %%eax\n\t"
      "movl %%eax, -0x18(%%ebp)\n\t"
      "movswl %%ax, %%eax\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jl .Lrender_weapon_hud_113\n\t"
      ".Lrender_weapon_hud_115:\n\t"
      "movl $0x7f, %%eax\n\t"
      "movl $0x62626262, %%ecx\n\t"
      ".Lrender_weapon_hud_116:\n\t"
      "movswl %%ax, %%edx\n\t"
      "cmpl %%ecx, -0x284(%%ebp,%%edx,4)\n\t"
      "jne .Lrender_weapon_hud_120\n\t"
      "decl %%eax\n\t"
      "testw %%ax, %%ax\n\t"
      "jge .Lrender_weapon_hud_116\n\t"
      "orl $0xffffffff, %%esi\n\t"
      ".Lrender_weapon_hud_117:\n\t"
      "call *%[cd1540]\n\t"
      "cmpl %%eax, -0x48(%%ebp)\n\t"
      "je .Lrender_weapon_hud_118\n\t"
      "pushl $1\n\t"
      "pushl $0x308\n\t"
      "pushl $0x281eec\n\t"
      "pushl $0x281960\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrender_weapon_hud_118:\n\t"
      "cmpw $-1, %%si\n\t"
      "je .Lrender_weapon_hud_119\n\t"
      "pushl $1\n\t"
      "pushl $0x308\n\t"
      "movswl %%si, %%eax\n\t"
      "pushl $0x281eec\n\t"
      "pushl %%eax\n\t"
      "pushl $0x281948\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0xc, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrender_weapon_hud_119:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lrender_weapon_hud_120:\n\t"
      "movl %%eax, %%esi\n\t"
      "jmp .Lrender_weapon_hud_117\n\t"
      :
      : [cd1540] "m"(bd9f20_cd1540), [memset] "m"(bd9f20_memset), [tag] "m"(bd9f20_tag), [cd8bc0] "m"(bd9f20_cd8bc0), [c8e0b0] "m"(bd9f20_c8e0b0), [cba4b0] "m"(bd9f20_cba4b0), [cd1c50] "m"(bd9f20_cd1c50), [gtime] "m"(bd9f20_gtime), [ftol] "m"(bd9f20_ftol), [cb6620] "m"(bd9f20_cb6620), [cb6940] "m"(bd9f20_cb6940), [cba3c0] "m"(bd9f20_cba3c0), [dget] "m"(bd9f20_dget), [useat] "m"(bd9f20_useat), [c1412f0] "m"(bd9f20_c1412f0), [cd9f20] "m"(bd9f20_cd9f20), [c18e380] "m"(bd9f20_c18e380), [elem] "m"(bd9f20_elem), [cd3fe0] "m"(bd9f20_cd3fe0), [cd3340] "m"(bd9f20_cd3340), [c1d9e70] "m"(bd9f20_c1d9e70), [c1daf7e] "m"(bd9f20_c1daf7e), [cd3860] "m"(bd9f20_cd3860), [cd4260] "m"(bd9f20_cd4260), [assert] "m"(bd9f20_assert), [exitfn] "m"(bd9f20_exitfn), [c8d9d0] "m"(bd9f20_c8d9d0)
      : "memory");
}
#else
#error "render_weapon_hud: clang naked draft required"
#endif


/* hud_update_weapon (0xda980) — XBE naked draft (batch 114). */
#if defined(__clang__)
static int (*const bda980_cd1540)(void) = FUN_000d1540;
static void *(*const bda980_memset)(void *, int, unsigned int) = csmemset;
static __int16 (*const bda980_cba4c0)(__int16 a1) = local_player_get_next;
static int (*const bda980_cba3c0)(int16_t local_player_index) = local_player_get_player_index;
static void *(*const bda980_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void *(*const bda980_get)(int, int) = object_get_and_verify_type;
static int (*const bda980_c1adeb0)(int unit_handle, int16_t weapon_index) = unit_get_weapon;
static void *(*const bda980_tag)(int, int) = tag_get;
static void *(*const bda980_elem)(void *, int, int) = tag_block_get_element;
static void (*const bda980_cfc550)(int weapon_handle, int out_state) = weapon_build_weapon_interface_state;
static int16_t (*const bda980_c1aad90)(int unit_handle) = unit_count_weapons;
static void (*const bda980_cd9960)(void) = FUN_000d9960;
static void * (*const bda980_cd8bc0)(int16_t local_player_index) = FUN_000d8bc0;
static void (*const bda980_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const bda980_exitfn)(int) = system_exit;
static char * (*const bda980_c8d9d0)(char *buffer, const char *format, ...) = csprintf;
static void (*const bda980_cdabdd)(void) = (void (*)(void))FUN_000dabf0;

__attribute__((naked, noinline))
void hud_update_weapon(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x248, %%esp\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[cd1540]\n\t"
      "pushl $0x200\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "leal -0x248(%%ebp), %%eax\n\t"
      "pushl $0x62\n\t"
      "pushl %%eax\n\t"
      "call *%[memset]\n\t"
      "pushl $-1\n\t"
      "call *%[cba4c0]\n\t"
      "addl $0x10, %%esp\n\t"
      "movl %%eax, %%edi\n\t"
      "cmpw $-1, %%di\n\t"
      "movl %%edi, -0x4(%%ebp)\n\t"
      "je .Lhud_update_weapon_8\n\t"
      "pushl %%ebx\n\t"
      "jmp .Lhud_update_weapon_2\n\t"
      ".Lhud_update_weapon_1:\n\t"
      "movl -0x4(%%ebp), %%edi\n\t"
      ".Lhud_update_weapon_2:\n\t"
      "pushl %%edi\n\t"
      "call *%[cba3c0]\n\t"
      "addl $4, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lhud_update_weapon_7\n\t"
      "pushl %%edi\n\t"
      "call *%[cba3c0]\n\t"
      "movl 0x5aa6d4, %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movl 0x34(%%eax), %%esi\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl $-1, %%esi\n\t"
      "je .Lhud_update_weapon_7\n\t"
      "pushl $3\n\t"
      "pushl %%esi\n\t"
      "call *%[get]\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x2a2(%%eax), %%dx\n\t"
      "pushl %%edx\n\t"
      "pushl %%esi\n\t"
      "call *%[c1adeb0]\n\t"
      "movl %%eax, %%ebx\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpl $-1, %%ebx\n\t"
      "jne .Lhud_update_weapon_3\n\t"
      "pushl $3\n\t"
      "pushl %%esi\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%edi\n\t"
      "movl 0xcc(%%edi), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "cmpl %%ebx, %%eax\n\t"
      "je .Lhud_update_weapon_4\n\t"
      "cmpw %%bx, 0x2a0(%%edi)\n\t"
      "je .Lhud_update_weapon_4\n\t"
      "pushl $3\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movswl 0x2a0(%%edi), %%ecx\n\t"
      "movl (%%eax), %%edx\n\t"
      "addl $8, %%esp\n\t"
      "pushl $0x11c\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x756e6974\n\t"
      "call *%[tag]\n\t"
      "addl $0x2e4, %%eax\n\t"
      "addl $8, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movb (%%eax), %%cl\n\t"
      "addl $0xc, %%esp\n\t"
      "testb $8, %%cl\n\t"
      "je .Lhud_update_weapon_6\n\t"
      "movl 0xcc(%%edi), %%eax\n\t"
      "pushl $3\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl 0xcc(%%edi), %%edx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x2a2(%%eax), %%cx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c1adeb0]\n\t"
      "movl %%eax, %%ebx\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpl $-1, %%ebx\n\t"
      "je .Lhud_update_weapon_4\n\t"
      ".Lhud_update_weapon_3:\n\t"
      "pushl $4\n\t"
      "pushl %%ebx\n\t"
      "call *%[get]\n\t"
      "movl (%%eax), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x77656170\n\t"
      "call *%[tag]\n\t"
      "leal -0x48(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "movl %%eax, %%edi\n\t"
      "call *%[cfc550]\n\t"
      "movl 0x48c(%%edi), %%eax\n\t"
      "addl $0x18, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lhud_update_weapon_6\n\t"
      "leal -0x48(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "jmp .Lhud_update_weapon_5\n\t"
      ".Lhud_update_weapon_4:\n\t"
      "pushl %%esi\n\t"
      "call *%[c1aad90]\n\t"
      "addl $4, %%esp\n\t"
      "testw %%ax, %%ax\n\t"
      "jne .Lhud_update_weapon_6\n\t"
      "xorl %%eax, %%eax\n\t"
      "movl $7, %%ecx\n\t"
      "leal -0x24(%%ebp), %%edi\n\t"
      "movl $0, -0x28(%%ebp)\n\t"
      "rep stosl\n\t"
      "movl 0x46bd0c, %%ecx\n\t"
      "movl 0x2cc(%%ecx), %%edx\n\t"
      "leal -0x28(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl $-1\n\t"
      ".Lhud_update_weapon_5:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "call *%[cd9960]\n\t"
      "addl $0xc, %%esp\n\t"
      ".Lhud_update_weapon_6:\n\t"
      "movl -0x4(%%ebp), %%esi\n\t"
      "call *%[cd8bc0]\n\t"
      "movl %%ebx, 0x20(%%eax)\n\t"
      "movl %%esi, %%edi\n\t"
      ".Lhud_update_weapon_7:\n\t"
      "pushl %%edi\n\t"
      "call *%[cba4c0]\n\t"
      "addl $4, %%esp\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "jne .Lhud_update_weapon_1\n\t"
      "popl %%ebx\n\t"
      ".Lhud_update_weapon_8:\n\t"
      "movl $0x7f, %%eax\n\t"
      "movl $0x62626262, %%ecx\n\t"
      "leal (%%ebx), %%ebx\n\t"
      ".Lhud_update_weapon_9:\n\t"
      "movswl %%ax, %%edx\n\t"
      "cmpl %%ecx, -0x248(%%ebp,%%edx,4)\n\t"
      "jne .Lhud_update_weapon_10000\n\t"
      "decl %%eax\n\t"
      "testw %%ax, %%ax\n\t"
      "jge .Lhud_update_weapon_9\n\t"
      "orl $0xffffffff, %%esi\n\t"
      "call *%[cd1540]\n\t"
      "cmpl %%eax, -0x8(%%ebp)\n\t"
      "je .Lhud_update_weapon_10\n\t"
      "pushl $1\n\t"
      "pushl $0xd4\n\t"
      "pushl $0x281eec\n\t"
      "pushl $0x281960\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lhud_update_weapon_10:\n\t"
      "cmpw $-1, %%si\n\t"
      "je .Lhud_update_weapon_11\n\t"
      "pushl $1\n\t"
      "pushl $0xd4\n\t"
      "movswl %%si, %%eax\n\t"
      "pushl $0x281eec\n\t"
      "pushl %%eax\n\t"
      "pushl $0x281948\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0xc, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lhud_update_weapon_11:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lhud_update_weapon_10000:\n\t"
      "jmp *%[cdabdd]\n\t"
      :
      : [cd1540] "m"(bda980_cd1540), [memset] "m"(bda980_memset), [cba4c0] "m"(bda980_cba4c0), [cba3c0] "m"(bda980_cba3c0), [dget] "m"(bda980_dget), [get] "m"(bda980_get), [c1adeb0] "m"(bda980_c1adeb0), [tag] "m"(bda980_tag), [elem] "m"(bda980_elem), [cfc550] "m"(bda980_cfc550), [c1aad90] "m"(bda980_c1aad90), [cd9960] "m"(bda980_cd9960), [cd8bc0] "m"(bda980_cd8bc0), [assert] "m"(bda980_assert), [exitfn] "m"(bda980_exitfn), [c8d9d0] "m"(bda980_c8d9d0), [cdabdd] "m"(bda980_cdabdd)
      : "memory");
}
#else
#error "hud_update_weapon: clang naked draft required"
#endif


/* FUN_000dabf0 (0xdabf0) — XBE naked draft (batch 116). */
#if defined(__clang__)
static void *(*const bdabf0_get)(int, int) = object_get_and_verify_type;
static int (*const bdabf0_c1adeb0)(int unit_handle, int16_t weapon_index) = unit_get_weapon;
static void *(*const bdabf0_tag)(int, int) = tag_get;
static void *(*const bdabf0_elem)(void *, int, int) = tag_block_get_element;
static void (*const bdabf0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const bdabf0_exitfn)(int) = system_exit;
static void (*const bdabf0_cfc550)(int weapon_handle, int out_state) = weapon_build_weapon_interface_state;
static void (*const bdabf0_cd8ff0)(int whud_index, int *player, int weapon_handle, int buf) = FUN_000d8ff0;
static void (*const bdabf0_cd9f20)(void) = render_weapon_hud;
static void (*const bdabf0_cd8ca0)(int object_handle, int16_t local_player_index) = FUN_000d8ca0;
static int16_t (*const bdabf0_c1aad90)(int unit_handle) = unit_count_weapons;
static void (*const bdabf0_cd8cf0)(int param_1, int param_2) = FUN_000d8cf0;
static void * (*const bdabf0_cd8bc0)(int16_t local_player_index) = FUN_000d8bc0;

__attribute__((naked, noinline))
void FUN_000dabf0(int param_1)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x24, %%esp\n\t"
      "pushl %%ebx\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "movl 0x34(%%ebx), %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl $3\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl 0x34(%%ebx), %%edx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x2a2(%%eax), %%cx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c1adeb0]\n\t"
      "movl %%eax, %%edi\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpl $-1, %%edi\n\t"
      "movl %%edi, -0x4(%%ebp)\n\t"
      "movb $0, 0xb(%%ebp)\n\t"
      "jne .LFUN_000dabf0_2\n\t"
      "movl 0x34(%%ebx), %%eax\n\t"
      "pushl $3\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0xcc(%%esi), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "cmpl %%edi, %%eax\n\t"
      "je .LFUN_000dabf0_2\n\t"
      "cmpw %%di, 0x2a0(%%esi)\n\t"
      "je .LFUN_000dabf0_2\n\t"
      "pushl $3\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movswl 0x2a0(%%esi), %%ecx\n\t"
      "movl (%%eax), %%edx\n\t"
      "addl $8, %%esp\n\t"
      "pushl $0x11c\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x756e6974\n\t"
      "call *%[tag]\n\t"
      "addl $0x2e4, %%eax\n\t"
      "addl $8, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movb (%%eax), %%cl\n\t"
      "addl $0xc, %%esp\n\t"
      "testb $8, %%cl\n\t"
      "je .LFUN_000dabf0_1\n\t"
      "movl 0xcc(%%esi), %%eax\n\t"
      "pushl $3\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl 0xcc(%%esi), %%edx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x2a2(%%eax), %%cx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c1adeb0]\n\t"
      "addl $0x10, %%esp\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "movl %%eax, %%edi\n\t"
      "jmp .LFUN_000dabf0_2\n\t"
      ".LFUN_000dabf0_1:\n\t"
      "movb $1, 0xb(%%ebp)\n\t"
      ".LFUN_000dabf0_2:\n\t"
      "movw 0x2(%%ebx), %%ax\n\t"
      "cmpw 0x506548, %%ax\n\t"
      "je .LFUN_000dabf0_3\n\t"
      "pushl $1\n\t"
      "pushl $0x1d8\n\t"
      "pushl $0x281eec\n\t"
      "pushl $0x2819b8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000dabf0_3:\n\t"
      "cmpl $-1, %%edi\n\t"
      "je .LFUN_000dabf0_4\n\t"
      "pushl $4\n\t"
      "pushl %%edi\n\t"
      "call *%[get]\n\t"
      "movl (%%eax), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x77656170\n\t"
      "call *%[tag]\n\t"
      "leal -0x24(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl %%eax, %%esi\n\t"
      "pushl %%edi\n\t"
      "movl %%esi, 0x8(%%ebp)\n\t"
      "call *%[cfc550]\n\t"
      "movl 0x48c(%%esi), %%esi\n\t"
      "addl $0x18, %%esp\n\t"
      "cmpl $-1, %%esi\n\t"
      "je .LFUN_000dabf0_5\n\t"
      "leal -0x24(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "movl %%esi, %%eax\n\t"
      "movl %%ebx, %%ecx\n\t"
      "call *%[cd8ff0]\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x2(%%ebx), %%ax\n\t"
      "pushl $0\n\t"
      "leal -0x24(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[cd9f20]\n\t"
      "leal -0x24(%%ebp), %%ecx\n\t"
      "movl %%esi, %%eax\n\t"
      "movw 0x2(%%ebx), %%si\n\t"
      "pushl %%ecx\n\t"
      "call *%[cd8ca0]\n\t"
      "addl $0x28, %%esp\n\t"
      "jmp .LFUN_000dabf0_5\n\t"
      ".LFUN_000dabf0_4:\n\t"
      "movb 0xb(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_000dabf0_5\n\t"
      "movl 0x34(%%ebx), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c1aad90]\n\t"
      "addl $4, %%esp\n\t"
      "testw %%ax, %%ax\n\t"
      "jne .LFUN_000dabf0_5\n\t"
      "xorl %%eax, %%eax\n\t"
      "movl $0, -0x24(%%ebp)\n\t"
      "movl $7, %%ecx\n\t"
      "leal -0x20(%%ebp), %%edi\n\t"
      "rep stosl\n\t"
      "movl 0x46bd0c, %%ecx\n\t"
      "leal -0x24(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl 0x2cc(%%ecx), %%eax\n\t"
      "pushl $-1\n\t"
      "movl %%ebx, %%ecx\n\t"
      "call *%[cd8ff0]\n\t"
      "movl -0x4(%%ebp), %%edi\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_000dabf0_5:\n\t"
      "movl 0x34(%%ebx), %%edx\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x2(%%ebx), %%ax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[cd8cf0]\n\t"
      "movswl 0x2(%%ebx), %%ebx\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $-1, %%bx\n\t"
      "je .LFUN_000dabf0_6\n\t"
      "movl %%ebx, %%esi\n\t"
      "call *%[cd8bc0]\n\t"
      "movl %%edi, 0x20(%%eax)\n\t"
      ".LFUN_000dabf0_6:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [get] "m"(bdabf0_get), [c1adeb0] "m"(bdabf0_c1adeb0), [tag] "m"(bdabf0_tag), [elem] "m"(bdabf0_elem), [assert] "m"(bdabf0_assert), [exitfn] "m"(bdabf0_exitfn), [cfc550] "m"(bdabf0_cfc550), [cd8ff0] "m"(bdabf0_cd8ff0), [cd9f20] "m"(bdabf0_cd9f20), [cd8ca0] "m"(bdabf0_cd8ca0), [c1aad90] "m"(bdabf0_c1aad90), [cd8cf0] "m"(bdabf0_cd8cf0), [cd8bc0] "m"(bdabf0_cd8bc0)
      : "memory");
}
#else
#error "FUN_000dabf0: clang naked draft required"
#endif


/* tiny_point2d_set (0xdade0) — XBE naked draft (batch 151). */
#if defined(__clang__)
static void (*const bdade0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const bdade0_exitfn)(int) = system_exit;
static void (*const bdade0_ftol)(void) = FUN_001d9068;

__attribute__((naked, noinline))
void tiny_point2d_set(void)
{
  __asm__ volatile(
      "flds (%%esi)\n\t"
      "movl 0x46bd0c, %%eax\n\t"
      "fabs\n\t"
      "flds 0x2d0(%%eax)\n\t"
      "fcompp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .Ltiny_point2d_set_1\n\t"
      "pushl $1\n\t"
      "pushl $0x69\n\t"
      "pushl $0x282094\n\t"
      "pushl $0x282054\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Ltiny_point2d_set_1:\n\t"
      "flds 0x4(%%esi)\n\t"
      "movl 0x46bd0c, %%ecx\n\t"
      "fabs\n\t"
      "flds 0x2d0(%%ecx)\n\t"
      "fcompp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .Ltiny_point2d_set_2\n\t"
      "pushl $1\n\t"
      "pushl $0x6a\n\t"
      "pushl $0x282094\n\t"
      "pushl $0x282014\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Ltiny_point2d_set_2:\n\t"
      "movl 0x46bd0c, %%edx\n\t"
      "flds (%%esi)\n\t"
      "fdivs 0x2d0(%%edx)\n\t"
      "fmuls 0x2602cc\n\t"
      "call *%[ftol]\n\t"
      "movb %%al, (%%edi)\n\t"
      "flds 0x4(%%esi)\n\t"
      "movl 0x46bd0c, %%eax\n\t"
      "fdivs 0x2d0(%%eax)\n\t"
      "fmuls 0x2602cc\n\t"
      "call *%[ftol]\n\t"
      "movb %%al, 0x1(%%edi)\n\t"
      "ret\n\t"
      :
      : [assert] "m"(bdade0_assert), [exitfn] "m"(bdade0_exitfn), [ftol] "m"(bdade0_ftol)
      : "memory");
}
#else
#error "tiny_point2d_set: clang naked draft required"
#endif


/* FUN_000dae90 (0xdae90) — readable C lift. */
void FUN_000dae90(signed char *in_bytes, float *out_xy)
{
  int g = *(int *)0x46bd0c;
  int v;
  v = (int)in_bytes[0];
  out_xy[0] = (float)v * *(float *)(g + 0x2d0) * *(float *)0x2820c0;
  v = (int)in_bytes[1];
  out_xy[1] = (float)v * *(float *)(g + 0x2d0) * *(float *)0x2820c0;
}

/* FUN_000daee0 (0xdaee0) — XBE naked draft (batch 115). */
#if defined(__clang__)
static int (*const bdaee0_cba3c0)(int16_t local_player_index) = local_player_get_player_index;
static void *(*const bdaee0_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static int (*const bdaee0_cba500)(int) = player_index_from_unit_index;
static void *(*const bdaee0_tryget)(int, int) = object_try_and_get_and_verify_type;
static void *(*const bdaee0_get)(int, int) = object_get_and_verify_type;
static bool (*const bdaee0_ca7a30)(int16_t team_a, int16_t team_b) = game_allegiance_get_team_is_friendly;
static void *(*const bdaee0_tag)(int, int) = tag_get;
static void *(*const bdaee0_elem)(void *, int, int) = tag_block_get_element;
static int (*const bdaee0_c8ddd0)(char *s1, char *s2, unsigned int size) = csstrncmp;

__attribute__((naked, noinline))
void FUN_000daee0(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "call *%[cba3c0]\n\t"
      "pushl %%eax\n\t"
      "movl 0x5aa6d4, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl 0x20(%%eax), %%ecx\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl $-1, %%esi\n\t"
      "movl %%ecx, -0x4(%%ebp)\n\t"
      "jne .LFUN_000daee0_1\n\t"
      "movb $5, %%al\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000daee0_1:\n\t"
      "pushl %%esi\n\t"
      "call *%[cba500]\n\t"
      "addl $4, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "jne .LFUN_000daee0_2\n\t"
      "orl %%eax, %%eax\n\t"
      "jmp .LFUN_000daee0_3\n\t"
      ".LFUN_000daee0_2:\n\t"
      "pushl %%esi\n\t"
      "call *%[cba500]\n\t"
      "movl 0x5aa6d4, %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%edx\n\t"
      "call *%[dget]\n\t"
      "movswl 0x2(%%eax), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_000daee0_3:\n\t"
      "cmpl %%ebx, %%eax\n\t"
      "jne .LFUN_000daee0_4\n\t"
      "xorb %%al, %%al\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000daee0_4:\n\t"
      "pushl $3\n\t"
      "pushl %%esi\n\t"
      "call *%[tryget]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_000daee0_5\n\t"
      "movb $2, %%al\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000daee0_5:\n\t"
      "pushl %%edi\n\t"
      "pushl $3\n\t"
      "pushl %%esi\n\t"
      "call *%[get]\n\t"
      "pushl $2\n\t"
      "pushl %%esi\n\t"
      "movl %%eax, %%edi\n\t"
      "call *%[tryget]\n\t"
      "addl $0x10, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_000daee0_9\n\t"
      "pushl $2\n\t"
      "pushl %%esi\n\t"
      "call *%[get]\n\t"
      "movl 0x2d8(%%eax), %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%ecx\n\t"
      "je .LFUN_000daee0_7\n\t"
      ".LFUN_000daee0_6:\n\t"
      "pushl $3\n\t"
      "pushl %%ecx\n\t"
      "call *%[get]\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x68(%%eax), %%dx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[ca7a30]\n\t"
      "addl $0x10, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "setne %%al\n\t"
      "addb $3, %%al\n\t"
      "popl %%edi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000daee0_7:\n\t"
      "movl 0x2d4(%%eax), %%ecx\n\t"
      "cmpl $-1, %%ecx\n\t"
      "jne .LFUN_000daee0_6\n\t"
      "movl (%%eax), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x756e6974\n\t"
      "call *%[tag]\n\t"
      "movl 0x2e4(%%eax), %%ecx\n\t"
      "addl $0x2e4, %%eax\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $1, %%ecx\n\t"
      "jle .LFUN_000daee0_8\n\t"
      "pushl $0x11c\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "pushl $0xa\n\t"
      "addl $4, %%eax\n\t"
      "pushl $0x2820c4\n\t"
      "pushl %%eax\n\t"
      "call *%[c8ddd0]\n\t"
      "addl $0x18, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_000daee0_8\n\t"
      "movb $4, %%al\n\t"
      "popl %%edi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000daee0_8:\n\t"
      "movb $3, %%al\n\t"
      "popl %%edi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000daee0_9:\n\t"
      "pushl %%ebx\n\t"
      "call *%[cba3c0]\n\t"
      "movl 0x5aa6d4, %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movl 0x20(%%eax), %%eax\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x68(%%edi), %%dx\n\t"
      "pushl %%eax\n\t"
      "pushl %%edx\n\t"
      "call *%[ca7a30]\n\t"
      "addl $0x14, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "setne %%al\n\t"
      "incb %%al\n\t"
      "popl %%edi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [cba3c0] "m"(bdaee0_cba3c0), [dget] "m"(bdaee0_dget), [cba500] "m"(bdaee0_cba500), [tryget] "m"(bdaee0_tryget), [get] "m"(bdaee0_get), [ca7a30] "m"(bdaee0_ca7a30), [tag] "m"(bdaee0_tag), [elem] "m"(bdaee0_elem), [c8ddd0] "m"(bdaee0_c8ddd0)
      : "memory");
}
#else
#error "FUN_000daee0: clang naked draft required"
#endif


/* FUN_000db0b0 (0xdb0b0) — readable C lift: motion-sensor slot blob. */
char *FUN_000db0b0(int16_t local_player_index)
{
  if (local_player_index < 0 || local_player_index >= 4) {
    display_assert((char *)0x00266fc0, (char *)0x00282094, 0x11f, 1);
    system_exit(-1);
  }
  return (char *)(*(int *)0x46bd2c) + (int)local_player_index * 0x568;
}

/* FUN_000db1e0 (0xdb1e0) — readable C lift. */
void FUN_000db1e0(float *xy, char flag, int16_t value)
{
  extern char DAT_00282094[];
  extern char DAT_0028210c[];
  if (!xy) {
    display_assert(DAT_0028210c, DAT_00282094, 0x349, 1);
    system_exit(-1);
  }
  *(int16_t *)0x5aa676 = value;
  if (flag)
    *(unsigned *)0x2f66f4 = 0x3f400000;
  else
    *(unsigned *)0x2f66f4 = 0x3f800000;
  *(int *)0x5aa680 = *(int *)xy;
  *(int *)0x5aa684 = *((int *)xy + 1);
  FUN_0017d050();
}

/* FUN_000db250 (0xdb250) — XBE naked draft (batch 132). */
#if defined(__clang__)
static void *(*const bdb250_tryget)(int, int) = object_try_and_get_and_verify_type;
static char (*const bdb250_cab9a0)(void) = FUN_000ab9a0;
static void *(*const bdb250_get)(int, int) = object_get_and_verify_type;
static void (*const bdb250_c140070)(int object_handle, float *position_out, float *direction_out) = object_get_root_location;
static bool (*const bdb250_gerun)(void) = game_engine_running;

__attribute__((naked, noinline))
void FUN_000db250(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xc, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "pushl $3\n\t"
      "pushl %%esi\n\t"
      "xorb %%bl, %%bl\n\t"
      "call *%[tryget]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_000db250_8\n\t"
      "pushl %%esi\n\t"
      "call *%[cab9a0]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000db250_8\n\t"
      "pushl $3\n\t"
      "pushl %%esi\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%edi\n\t"
      "movl 0x1b8(%%edi), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "testb $8, %%ah\n\t"
      "jne .LFUN_000db250_7\n\t"
      "movb 0x23d(%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000db250_1\n\t"
      "cmpb $3, %%al\n\t"
      "jne .LFUN_000db250_7\n\t"
      ".LFUN_000db250_1:\n\t"
      "pushl $0\n\t"
      "leal -0xc(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[c140070]\n\t"
      "addl $0xc, %%esp\n\t"
      "call *%[gerun]\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_000db250_2\n\t"
      "testb $0x10, 0x1b4(%%edi)\n\t"
      "je .LFUN_000db250_2\n\t"
      "xorb %%cl, %%cl\n\t"
      "jmp .LFUN_000db250_3\n\t"
      ".LFUN_000db250_2:\n\t"
      "movb $1, %%cl\n\t"
      ".LFUN_000db250_3:\n\t"
      "flds -0x4(%%ebp)\n\t"
      "movl 0x46bd0c, %%edx\n\t"
      "fmuls -0x4(%%ebp)\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fmuls -0x8(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fmuls -0xc(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fcomps 0x2d4(%%edx)\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "je .LFUN_000db250_4\n\t"
      "movb 0x46bd34, %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_000db250_4\n\t"
      "xorb %%al, %%al\n\t"
      "jmp .LFUN_000db250_5\n\t"
      ".LFUN_000db250_4:\n\t"
      "movb $1, %%al\n\t"
      ".LFUN_000db250_5:\n\t"
      "testb %%cl, %%cl\n\t"
      "je .LFUN_000db250_6\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_000db250_7\n\t"
      ".LFUN_000db250_6:\n\t"
      "popl %%edi\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000db250_7:\n\t"
      "popl %%edi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000db250_8:\n\t"
      "popl %%edi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [tryget] "m"(bdb250_tryget), [cab9a0] "m"(bdb250_cab9a0), [get] "m"(bdb250_get), [c140070] "m"(bdb250_c140070), [gerun] "m"(bdb250_gerun)
      : "memory");
}
#else
#error "FUN_000db250: clang naked draft required"
#endif


/* render_blip (0xdb330) — XBE naked draft (batch 122). */
#if defined(__clang__)
static void (*const bdb330_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const bdb330_exitfn)(int) = system_exit;
static float (*const bdb330_c1d9e70)(float base, float exponent) = FUN_001d9e70;
static int (*const bdb330_gtime)(void) = game_time_get;
static void (*const bdb330_c17d060)(void) = FUN_0017d060;

__attribute__((naked, noinline))
void render_blip(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xc, %%esp\n\t"
      "cmpb $6, %%bl\n\t"
      "movl (%%eax), %%ecx\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl %%ecx, -0xc(%%ebp)\n\t"
      "movl %%edx, -0x8(%%ebp)\n\t"
      "jne .Lrender_blip_1\n\t"
      "pushl $1\n\t"
      "pushl $0x19a\n\t"
      "pushl $0x282094\n\t"
      "pushl $0x282128\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrender_blip_1:\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "flds 0x7c(%%eax)\n\t"
      "pushl %%esi\n\t"
      "fchs\n\t"
      "movl 0x46bd0c, %%esi\n\t"
      "fld %%st(0)\n\t"
      "fsin\n\t"
      "fxch %%st(1)\n\t"
      "fcos\n\t"
      "flds -0x8(%%ebp)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "flds -0xc(%%ebp)\n\t"
      ".byte 0xd8, 0xcb\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fstps 0x8(%%ebp)\n\t"
      "flds -0xc(%%ebp)\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "flds -0x8(%%ebp)\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      ".byte 0xd8, 0xcb\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fmuls -0xc(%%ebp)\n\t"
      "flds 0x8(%%ebp)\n\t"
      "fmuls 0x8(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds 0x2d0(%%esi)\n\t"
      "fld %%st(0)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fld %%st(2)\n\t"
      "fcompp\n\t"
      "fnstsw %%ax\n\t"
      "fstp %%st(0)\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lrender_blip_4\n\t"
      "fsqrt\n\t"
      "fsts -0x4(%%ebp)\n\t"
      "fcomps 0x282124\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lrender_blip_2\n\t"
      "movl $0x3c800000, -0x4(%%ebp)\n\t"
      ".Lrender_blip_2:\n\t"
      "flds 0x2533c8\n\t"
      "fdivs -0x4(%%ebp)\n\t"
      "flds -0xc(%%ebp)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "flds 0x8(%%ebp)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fdivs 0x2d0(%%esi)\n\t"
      "fldl 0x281e18\n\t"
      "call *%[c1d9e70]\n\t"
      "cmpb $5, %%bl\n\t"
      "movsbl 0xc(%%ebp), %%edx\n\t"
      "movsbl %%bl, %%eax\n\t"
      "fmuls 0x2d0(%%esi)\n\t"
      "flds -0xc(%%ebp)\n\t"
      "leal (%%eax,%%eax,2), %%esi\n\t"
      "leal 0x281fc0(,%%esi,4), %%esi\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "flds -0x8(%%ebp)\n\t"
      ".byte 0xd8, 0xca\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "fmuls 0x10(%%ebp)\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fmuls 0x10(%%ebp)\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "flds 0x2533c8\n\t"
      "flds 0x2f66f8(,%%edx,4)\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "jne .Lrender_blip_3\n\t"
      "fstp %%st(0)\n\t"
      "call *%[gtime]\n\t"
      "movl %%eax, 0x8(%%ebp)\n\t"
      "fildl 0x8(%%ebp)\n\t"
      "cmpb %%bl, %%bl\n\t"
      "fmuls 0x282120\n\t"
      "fsin\n\t"
      "faddl 0x2573d8\n\t"
      "fmull 0x282118\n\t"
      "faddl 0x2573d8\n\t"
      ".Lrender_blip_3:\n\t"
      "fmuls 0x18(%%ebp)\n\t"
      "sete %%al\n\t"
      "leal -0xc(%%ebp), %%edx\n\t"
      "fadds -0x4(%%ebp)\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%ecx\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      "fstps (%%esp)\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c17d060]\n\t"
      "addl $0x14, %%esp\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lrender_blip_4:\n\t"
      "fstp %%st(0)\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(bdb330_assert), [exitfn] "m"(bdb330_exitfn), [c1d9e70] "m"(bdb330_c1d9e70), [gtime] "m"(bdb330_gtime), [c17d060] "m"(bdb330_c17d060)
      : "memory");
}
#else
#error "render_blip: clang naked draft required"
#endif


/* motion_sensor_update (0xdb4c0) — XBE naked draft (batch 107). */
#if defined(__clang__)
static int (*const bdb4c0_cd1540)(void) = FUN_000d1540;
static void *(*const bdb4c0_memset)(void *, int, unsigned int) = csmemset;
static bool (*const bdb4c0_gerun)(void) = game_engine_running;
static int (*const bdb4c0_gtime)(void) = game_time_get;
static __int16 (*const bdb4c0_cba4b0)(void) = local_player_count;
static __int16 (*const bdb4c0_cba4c0)(__int16 a1) = local_player_get_next;
static void * (*const bdb4c0_c8e0b0)(void *destination, void *source, size_t size) = csmemcpy;
static int (*const bdb4c0_cba3c0)(int16_t local_player_index) = local_player_get_player_index;
static void *(*const bdb4c0_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void (*const bdb4c0_useat)(int, float *) = unit_set_seat_state;
static void (*const bdb4c0_c13d6f0)(void *iter, int type_mask, int flags) = object_iterator_new;
static void * (*const bdb4c0_c13d730)(void *iter) = object_iterator_next;
static void *(*const bdb4c0_tryget)(int, int) = object_try_and_get_and_verify_type;
static void (*const bdb4c0_cdb250)(void) = FUN_000db250;
static void (*const bdb4c0_c1aae0)(int object_handle, float *center, float *radius) = FUN_0001aae0;
static void (*const bdb4c0_cdaee0)(void) = FUN_000daee0;
static void *(*const bdb4c0_get)(int, int) = object_get_and_verify_type;
static void *(*const bdb4c0_tag)(int, int) = tag_get;
static void (*const bdb4c0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const bdb4c0_exitfn)(int) = system_exit;
static char * (*const bdb4c0_c8d9d0)(char *buffer, const char *format, ...) = csprintf;
static void (*const bdb4c0_cdb93e)(void) = (void (*)(void))update_motion_sensor;

__attribute__((naked, noinline))
void motion_sensor_update(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x284, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[cd1540]\n\t"
      "pushl $0x200\n\t"
      "movl %%eax, -0x40(%%ebp)\n\t"
      "leal -0x284(%%ebp), %%eax\n\t"
      "pushl $0x62\n\t"
      "pushl %%eax\n\t"
      "call *%[memset]\n\t"
      "addl $0xc, %%esp\n\t"
      "call *%[gerun]\n\t"
      "call *%[gtime]\n\t"
      "movl 0x46bd2c, %%ecx\n\t"
      "movl %%eax, %%esi\n\t"
      "movb $1, 0x15a6(%%ecx)\n\t"
      "movw 0x15a4(%%ecx), %%dx\n\t"
      "incw %%dx\n\t"
      "movswl %%dx, %%eax\n\t"
      "cdq\n\t"
      "movl $0xa, %%edi\n\t"
      "idivl %%edi\n\t"
      "movl %%esi, %%eax\n\t"
      "movl $0xf, %%edi\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "movw %%dx, 0x15a4(%%ecx)\n\t"
      "cdq\n\t"
      "idivl %%edi\n\t"
      "movl %%esi, 0x15a0(%%ecx)\n\t"
      "testl %%edx, %%edx\n\t"
      "je .Lmotion_sensor_update_2\n\t"
      "testl %%esi, %%esi\n\t"
      "je .Lmotion_sensor_update_2\n\t"
      "movswl 0x15a4(%%ecx), %%ebx\n\t"
      "leal 0x9(%%ebx), %%eax\n\t"
      "cdq\n\t"
      "movl $0xa, %%ecx\n\t"
      "idivl %%ecx\n\t"
      "movl %%edx, -0x14(%%ebp)\n\t"
      "call *%[cba4b0]\n\t"
      "pushl $-1\n\t"
      "movl %%eax, %%edi\n\t"
      "movl %%edi, -0x10(%%ebp)\n\t"
      "call *%[cba4c0]\n\t"
      "addl $4, %%esp\n\t"
      "testw %%di, %%di\n\t"
      "movl %%eax, %%esi\n\t"
      "jle .Lmotion_sensor_update_19\n\t"
      "movswl -0x14(%%ebp), %%edi\n\t"
      "movzwl -0x10(%%ebp), %%edx\n\t"
      "imull $0x84, %%edi, %%edi\n\t"
      "imull $0x84, %%ebx, %%ebx\n\t"
      "movl %%edx, -0x8(%%ebp)\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".Lmotion_sensor_update_1:\n\t"
      "movl 0x46bd2c, %%ecx\n\t"
      "movswl %%si, %%eax\n\t"
      "imull $0x568, %%eax, %%eax\n\t"
      "leal (%%edi,%%eax,1), %%edx\n\t"
      "pushl $0x84\n\t"
      "addl %%ecx, %%edx\n\t"
      "addl %%ebx, %%eax\n\t"
      "pushl %%edx\n\t"
      "addl %%ecx, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c8e0b0]\n\t"
      "pushl %%esi\n\t"
      "call *%[cba4c0]\n\t"
      "addl $0x10, %%esp\n\t"
      "movl %%eax, %%esi\n\t"
      "decl -0x8(%%ebp)\n\t"
      "jne .Lmotion_sensor_update_1\n\t"
      "jmp .Lmotion_sensor_update_19\n\t"
      ".Lmotion_sensor_update_2:\n\t"
      "call *%[cba4b0]\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movl %%ecx, -0x26(%%ebp)\n\t"
      "pushl $-1\n\t"
      "movw $0, -0x28(%%ebp)\n\t"
      "movw %%cx, -0x22(%%ebp)\n\t"
      "movl %%eax, %%edi\n\t"
      "movl %%edi, -0x10(%%ebp)\n\t"
      "call *%[cba4c0]\n\t"
      "addl $4, %%esp\n\t"
      "testw %%di, %%di\n\t"
      "movl %%eax, %%ebx\n\t"
      "jle .Lmotion_sensor_update_8\n\t"
      "movzwl %%di, %%eax\n\t"
      "leal -0x54(%%ebp), %%edx\n\t"
      "movl %%edx, -0xc(%%ebp)\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "jmp .Lmotion_sensor_update_3\n\t"
      "leal (%%esp), %%esp\n\t"
      "leal (%%esp), %%esp\n\t"
      ".Lmotion_sensor_update_3:\n\t"
      "movl 0x46bd2c, %%eax\n\t"
      "movswl 0x15a4(%%eax), %%ecx\n\t"
      "movswl %%bx, %%edi\n\t"
      "imull $0x84, %%ecx, %%ecx\n\t"
      "movl %%edi, %%esi\n\t"
      "imull $0x568, %%esi, %%esi\n\t"
      "addl %%ecx, %%eax\n\t"
      "pushl %%ebx\n\t"
      "addl %%eax, %%esi\n\t"
      "call *%[cba3c0]\n\t"
      "addl $4, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "jne .Lmotion_sensor_update_4\n\t"
      "orl %%eax, %%eax\n\t"
      "jmp .Lmotion_sensor_update_5\n\t"
      ".Lmotion_sensor_update_4:\n\t"
      "pushl %%ebx\n\t"
      "call *%[cba3c0]\n\t"
      "movl 0x5aa6d4, %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%edx\n\t"
      "call *%[dget]\n\t"
      "movl 0x34(%%eax), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      ".Lmotion_sensor_update_5:\n\t"
      "cmpl $-1, %%eax\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "movw %%bx, (%%ecx)\n\t"
      "je .Lmotion_sensor_update_6\n\t"
      "leal (%%edi,%%edi,2), %%edx\n\t"
      "leal -0x84(%%ebp,%%edx,4), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "call *%[useat]\n\t"
      "addl $8, %%esp\n\t"
      ".Lmotion_sensor_update_6:\n\t"
      "movl $0, 0x78(%%esi)\n\t"
      "leal 0x2(%%esi), %%eax\n\t"
      "movl $0x10, %%ecx\n\t"
      "leal (%%ebx), %%ebx\n\t"
      ".Lmotion_sensor_update_7:\n\t"
      "movb $6, (%%eax)\n\t"
      "addl $4, %%eax\n\t"
      "decl %%ecx\n\t"
      "jne .Lmotion_sensor_update_7\n\t"
      "movl -0xc(%%ebp), %%esi\n\t"
      "addl $2, %%esi\n\t"
      "pushl %%ebx\n\t"
      "movl %%esi, -0xc(%%ebp)\n\t"
      "call *%[cba4c0]\n\t"
      "addl $4, %%esp\n\t"
      "movl %%eax, %%ebx\n\t"
      "decl -0x8(%%ebp)\n\t"
      "jne .Lmotion_sensor_update_3\n\t"
      "movl -0x10(%%ebp), %%edi\n\t"
      ".Lmotion_sensor_update_8:\n\t"
      "pushl $1\n\t"
      "leal -0x38(%%ebp), %%edx\n\t"
      "pushl $3\n\t"
      "pushl %%edx\n\t"
      "call *%[c13d6f0]\n\t"
      "leal -0x38(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c13d730]\n\t"
      "addl $0x10, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lmotion_sensor_update_19\n\t"
      "leal (%%ebx), %%ebx\n\t"
      ".Lmotion_sensor_update_9:\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lmotion_sensor_update_19\n\t"
      "movl -0x30(%%ebp), %%ecx\n\t"
      "pushl $3\n\t"
      "pushl %%ecx\n\t"
      "call *%[tryget]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lmotion_sensor_update_18\n\t"
      "testb $4, 0xb6(%%eax)\n\t"
      "jne .Lmotion_sensor_update_18\n\t"
      "movl -0x30(%%ebp), %%esi\n\t"
      "call *%[cdb250]\n\t"
      "testb %%al, %%al\n\t"
      "je .Lmotion_sensor_update_18\n\t"
      "movl -0x30(%%ebp), %%ecx\n\t"
      "leal -0x1c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x4c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "movl $0, -0x8(%%ebp)\n\t"
      "call *%[c1aae0]\n\t"
      "addl $0xc, %%esp\n\t"
      "testw %%di, %%di\n\t"
      "jle .Lmotion_sensor_update_17\n\t"
      "movzwl %%di, %%eax\n\t"
      "leal -0x54(%%ebp), %%edx\n\t"
      "movl %%edx, -0xc(%%ebp)\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "movl %%edi, %%edi\n\t"
      ".Lmotion_sensor_update_10:\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "movswl (%%ecx), %%ebx\n\t"
      "leal -0x28(%%ebp,%%ebx,2), %%eax\n\t"
      "movl %%eax, -0x18(%%ebp)\n\t"
      "movswl (%%eax), %%eax\n\t"
      "cmpw $0x10, %%ax\n\t"
      "movl %%eax, -0x3c(%%ebp)\n\t"
      "jge .Lmotion_sensor_update_15\n\t"
      "leal (%%ebx,%%ebx,2), %%esi\n\t"
      "shll $2, %%esi\n\t"
      "flds -0x7c(%%ebp,%%esi,1)\n\t"
      "fstps -0x44(%%ebp)\n\t"
      "call *%[gerun]\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lmotion_sensor_update_11\n\t"
      "flds -0x4c(%%ebp)\n\t"
      "movl 0x46bd0c, %%edx\n\t"
      "fsubs -0x84(%%ebp,%%esi,1)\n\t"
      "leal -0x84(%%ebp,%%esi,1), %%eax\n\t"
      "flds -0x48(%%ebp)\n\t"
      "fsubs 0x4(%%eax)\n\t"
      "flds -0x44(%%ebp)\n\t"
      "fsubs 0x8(%%eax)\n\t"
      "flds 0x2d0(%%edx)\n\t"
      "fld %%st(1)\n\t"
      ".byte 0xd8, 0xca\n\t"
      "fld %%st(3)\n\t"
      ".byte 0xd8, 0xcc\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fld %%st(4)\n\t"
      ".byte 0xd8, 0xcd\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fld %%st(1)\n\t"
      ".byte 0xd8, 0xca\n\t"
      "fcompp\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "fnstsw %%ax\n\t"
      "fstp %%st(0)\n\t"
      "testb $1, %%ah\n\t"
      "fstp %%st(0)\n\t"
      "jne .Lmotion_sensor_update_16\n\t"
      ".Lmotion_sensor_update_11:\n\t"
      "movl 0x46bd2c, %%ecx\n\t"
      "movswl 0x15a4(%%ecx), %%edi\n\t"
      "movl -0x30(%%ebp), %%esi\n\t"
      "imull $0x84, %%edi, %%edi\n\t"
      "movl %%ebx, %%eax\n\t"
      "imull $0x568, %%eax, %%eax\n\t"
      "addl %%ecx, %%eax\n\t"
      "movl %%eax, -0x1c(%%ebp)\n\t"
      "addl %%eax, %%edi\n\t"
      "movl %%esi, -0x20(%%ebp)\n\t"
      "call *%[cdaee0]\n\t"
      "movswl -0x3c(%%ebp), %%esi\n\t"
      "movl -0x20(%%ebp), %%ebx\n\t"
      "cmpl $-1, %%ebx\n\t"
      "movb %%al, 0x2(%%edi,%%esi,4)\n\t"
      "je .Lmotion_sensor_update_13\n\t"
      "pushl $3\n\t"
      "pushl %%ebx\n\t"
      "call *%[tryget]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lmotion_sensor_update_13\n\t"
      "pushl $3\n\t"
      "pushl %%ebx\n\t"
      "call *%[get]\n\t"
      "movl (%%eax), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x756e6974\n\t"
      "call *%[tag]\n\t"
      "movw 0x298(%%eax), %%ax\n\t"
      "addl $0x10, %%esp\n\t"
      "testw %%ax, %%ax\n\t"
      "jl .Lmotion_sensor_update_12\n\t"
      "cmpw $3, %%ax\n\t"
      "jl .Lmotion_sensor_update_14\n\t"
      ".Lmotion_sensor_update_12:\n\t"
      "xorl %%eax, %%eax\n\t"
      "jmp .Lmotion_sensor_update_14\n\t"
      ".Lmotion_sensor_update_13:\n\t"
      "xorb %%al, %%al\n\t"
      ".Lmotion_sensor_update_14:\n\t"
      "movl -0x1c(%%ebp), %%edx\n\t"
      "movb %%al, 0x3(%%edi,%%esi,4)\n\t"
      "movl -0x18(%%ebp), %%eax\n\t"
      "movswl (%%eax), %%eax\n\t"
      "movl -0x30(%%ebp), %%ecx\n\t"
      "movl %%ecx, 0x528(%%edx,%%esi,4)\n\t"
      "movl -0x18(%%ebp), %%ecx\n\t"
      "incl %%eax\n\t"
      "movw %%ax, (%%ecx)\n\t"
      "incl 0x78(%%edi)\n\t"
      "movl -0x10(%%ebp), %%edi\n\t"
      "jmp .Lmotion_sensor_update_16\n\t"
      ".Lmotion_sensor_update_15:\n\t"
      "incl -0x8(%%ebp)\n\t"
      ".Lmotion_sensor_update_16:\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "addl $2, %%ecx\n\t"
      "decl %%eax\n\t"
      "movl %%ecx, -0xc(%%ebp)\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "jne .Lmotion_sensor_update_10\n\t"
      ".Lmotion_sensor_update_17:\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movswl %%di, %%edx\n\t"
      "cmpl %%edx, %%eax\n\t"
      "jne .Lmotion_sensor_update_18\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      ".Lmotion_sensor_update_18:\n\t"
      "leal -0x38(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c13d730]\n\t"
      "addl $4, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lmotion_sensor_update_9\n\t"
      ".Lmotion_sensor_update_19:\n\t"
      "movl $0x7f, %%eax\n\t"
      "movl $0x62626262, %%ecx\n\t"
      "leal (%%esp), %%esp\n\t"
      ".Lmotion_sensor_update_20:\n\t"
      "movswl %%ax, %%edx\n\t"
      "cmpl %%ecx, -0x284(%%ebp,%%edx,4)\n\t"
      "jne .Lmotion_sensor_update_10000\n\t"
      "decl %%eax\n\t"
      "testw %%ax, %%ax\n\t"
      "jge .Lmotion_sensor_update_20\n\t"
      "orl $0xffffffff, %%esi\n\t"
      "call *%[cd1540]\n\t"
      "cmpl %%eax, -0x40(%%ebp)\n\t"
      "je .Lmotion_sensor_update_21\n\t"
      "pushl $1\n\t"
      "pushl $0x282\n\t"
      "pushl $0x282094\n\t"
      "pushl $0x281960\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lmotion_sensor_update_21:\n\t"
      "cmpw $-1, %%si\n\t"
      "je .Lmotion_sensor_update_22\n\t"
      "pushl $1\n\t"
      "pushl $0x282\n\t"
      "movswl %%si, %%eax\n\t"
      "pushl $0x282094\n\t"
      "pushl %%eax\n\t"
      "pushl $0x281948\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0xc, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lmotion_sensor_update_22:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lmotion_sensor_update_10000:\n\t"
      "jmp *%[cdb93e]\n\t"
      :
      : [cd1540] "m"(bdb4c0_cd1540), [memset] "m"(bdb4c0_memset), [gerun] "m"(bdb4c0_gerun), [gtime] "m"(bdb4c0_gtime), [cba4b0] "m"(bdb4c0_cba4b0), [cba4c0] "m"(bdb4c0_cba4c0), [c8e0b0] "m"(bdb4c0_c8e0b0), [cba3c0] "m"(bdb4c0_cba3c0), [dget] "m"(bdb4c0_dget), [useat] "m"(bdb4c0_useat), [c13d6f0] "m"(bdb4c0_c13d6f0), [c13d730] "m"(bdb4c0_c13d730), [tryget] "m"(bdb4c0_tryget), [cdb250] "m"(bdb4c0_cdb250), [c1aae0] "m"(bdb4c0_c1aae0), [cdaee0] "m"(bdb4c0_cdaee0), [get] "m"(bdb4c0_get), [tag] "m"(bdb4c0_tag), [assert] "m"(bdb4c0_assert), [exitfn] "m"(bdb4c0_exitfn), [c8d9d0] "m"(bdb4c0_c8d9d0), [cdb93e] "m"(bdb4c0_cdb93e)
      : "memory");
}
#else
#error "motion_sensor_update: clang naked draft required"
#endif


/* update_motion_sensor (0xdb950) — XBE naked draft (batch 109). */
#if defined(__clang__)
static int (*const bdb950_cd1540)(void) = FUN_000d1540;
static void *(*const bdb950_memset)(void *, int, unsigned int) = csmemset;
static void (*const bdb950_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const bdb950_exitfn)(int) = system_exit;
static int (*const bdb950_gtime)(void) = game_time_get;
static int (*const bdb950_cba3c0)(int16_t local_player_index) = local_player_get_player_index;
static void *(*const bdb950_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void (*const bdb950_useat)(int, float *) = unit_set_seat_state;
static void *(*const bdb950_tryget)(int, int) = object_try_and_get_and_verify_type;
static void (*const bdb950_cdb250)(void) = FUN_000db250;
static void (*const bdb950_c1aae0)(int object_handle, float *center, float *radius) = FUN_0001aae0;
static void (*const bdb950_cdade0)(void) = tiny_point2d_set;
static float * (*const bdb950_cb7e30)(int16_t local_player_index) = player_control_get_facing_angles;
static int16_t (*const bdb950_ca9210)(int param_1, int param_2, int param_3, int16_t param_4) = game_engine_player_get_custom_motion_sensor_positions;
static char * (*const bdb950_c8d9d0)(char *buffer, const char *format, ...) = csprintf;
static void (*const bdb950_cdbc9d)(void) = (void (*)(void))FUN_000dbcb0;

__attribute__((naked, noinline))
void update_motion_sensor(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x2c0, %%esp\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[cd1540]\n\t"
      "pushl $0x200\n\t"
      "movl %%eax, -0x24(%%ebp)\n\t"
      "leal -0x2c0(%%ebp), %%eax\n\t"
      "pushl $0x62\n\t"
      "pushl %%eax\n\t"
      "call *%[memset]\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "addl $0xc, %%esp\n\t"
      "testw %%di, %%di\n\t"
      "jl .Lupdate_motion_sensor_1\n\t"
      "cmpw $4, %%di\n\t"
      "jl .Lupdate_motion_sensor_2\n\t"
      ".Lupdate_motion_sensor_1:\n\t"
      "pushl $1\n\t"
      "pushl $0x11f\n\t"
      "pushl $0x282094\n\t"
      "pushl $0x266fc0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lupdate_motion_sensor_2:\n\t"
      "movl 0x46bd2c, %%edx\n\t"
      "movswl %%di, %%esi\n\t"
      "imull $0x568, %%esi, %%esi\n\t"
      "addl %%edx, %%esi\n\t"
      "call *%[gtime]\n\t"
      "movl 0x46bd2c, %%eax\n\t"
      "movb 0x15a6(%%eax), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "je .Lupdate_motion_sensor_14\n\t"
      "pushl %%ebx\n\t"
      "movw 0x15a4(%%eax), %%bx\n\t"
      "pushl %%edi\n\t"
      "call *%[cba3c0]\n\t"
      "addl $4, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "jne .Lupdate_motion_sensor_3\n\t"
      "orl %%eax, %%eax\n\t"
      "movl %%eax, -0x1c(%%ebp)\n\t"
      "jmp .Lupdate_motion_sensor_4\n\t"
      ".Lupdate_motion_sensor_3:\n\t"
      "pushl %%edi\n\t"
      "call *%[cba3c0]\n\t"
      "movl 0x5aa6d4, %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movl 0x34(%%eax), %%edx\n\t"
      "addl $0xc, %%esp\n\t"
      "movl %%edx, -0x1c(%%ebp)\n\t"
      "movl %%edx, %%eax\n\t"
      ".Lupdate_motion_sensor_4:\n\t"
      "movswl %%bx, %%ebx\n\t"
      "imull $0x84, %%ebx, %%ebx\n\t"
      "addl %%esi, %%ebx\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lupdate_motion_sensor_13\n\t"
      "leal -0x18(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "call *%[useat]\n\t"
      "movl -0x18(%%ebp), %%edx\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "leal 0x528(%%esi), %%edi\n\t"
      "addl $8, %%esp\n\t"
      "movl %%edx, 0x70(%%ebx)\n\t"
      "movl %%eax, 0x74(%%ebx)\n\t"
      "movl %%ebx, -0xc(%%ebp)\n\t"
      "movl %%edi, -0x20(%%ebp)\n\t"
      "movl $0x10, -0x8(%%ebp)\n\t"
      "jmp .Lupdate_motion_sensor_5\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".Lupdate_motion_sensor_5:\n\t"
      "movl (%%edi), %%esi\n\t"
      "pushl $3\n\t"
      "pushl %%esi\n\t"
      "call *%[tryget]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lupdate_motion_sensor_8\n\t"
      "call *%[cdb250]\n\t"
      "leal -0x34(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x18(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%esi\n\t"
      "movb %%al, -0x1(%%ebp)\n\t"
      "call *%[c1aae0]\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fsubs 0x70(%%ebx)\n\t"
      "movl 0x74(%%ebx), %%eax\n\t"
      "movl %%eax, -0x3c(%%ebp)\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "fstps -0x2c(%%ebp)\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fsubs 0x74(%%ebx)\n\t"
      "fstps -0x28(%%ebp)\n\t"
      "flds 0x70(%%ebx)\n\t"
      "je .Lupdate_motion_sensor_6\n\t"
      "fsubrs -0x18(%%ebp)\n\t"
      "movl 0x46bd0c, %%ecx\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fsubs -0x3c(%%ebp)\n\t"
      "flds 0x2533c0\n\t"
      "flds 0x2d0(%%ecx)\n\t"
      "fld %%st(2)\n\t"
      ".byte 0xd8, 0xcb\n\t"
      "fld %%st(4)\n\t"
      ".byte 0xd8, 0xcd\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fld %%st(2)\n\t"
      ".byte 0xd8, 0xcb\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fld %%st(1)\n\t"
      ".byte 0xd8, 0xca\n\t"
      "fcompp\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "fnstsw %%ax\n\t"
      "fstp %%st(0)\n\t"
      "testb $1, %%ah\n\t"
      "fstp %%st(0)\n\t"
      "jne .Lupdate_motion_sensor_7\n\t"
      "movl -0xc(%%ebp), %%edi\n\t"
      "leal -0x2c(%%ebp), %%esi\n\t"
      "call *%[cdade0]\n\t"
      "movl -0x20(%%ebp), %%edi\n\t"
      "jmp .Lupdate_motion_sensor_8\n\t"
      ".Lupdate_motion_sensor_6:\n\t"
      "fstp %%st(0)\n\t"
      ".Lupdate_motion_sensor_7:\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "movb $6, 0x2(%%edx)\n\t"
      "movl $0xffffffff, (%%edi)\n\t"
      ".Lupdate_motion_sensor_8:\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "addl $4, %%edx\n\t"
      "addl $4, %%edi\n\t"
      "decl %%eax\n\t"
      "movl %%edx, -0xc(%%ebp)\n\t"
      "movl %%edi, -0x20(%%ebp)\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "jne .Lupdate_motion_sensor_5\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "pushl %%esi\n\t"
      "call *%[cb7e30]\n\t"
      "flds (%%eax)\n\t"
      "fadds 0x2568bc\n\t"
      "addl $4, %%esp\n\t"
      "pushl $0x10\n\t"
      "leal 0x60(%%ebx), %%eax\n\t"
      "pushl %%eax\n\t"
      "fstps 0x7c(%%ebx)\n\t"
      "leal -0xc0(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "movl $0, 0x8(%%ebp)\n\t"
      "call *%[cba3c0]\n\t"
      "addl $4, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[ca9210]\n\t"
      "leal -0x18(%%ebp), %%edx\n\t"
      "movb %%al, 0x80(%%ebx)\n\t"
      "movl -0x1c(%%ebp), %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[useat]\n\t"
      "movb 0x80(%%ebx), %%al\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "addl $0x18, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "jbe .Lupdate_motion_sensor_12\n\t"
      "leal -0xc0(%%ebp), %%esi\n\t"
      ".Lupdate_motion_sensor_9:\n\t"
      "flds (%%esi)\n\t"
      "movl 0x46bd0c, %%edx\n\t"
      "flds 0x4(%%esi)\n\t"
      "flds (%%esi)\n\t"
      "fsubs -0x18(%%ebp)\n\t"
      "fstps (%%esi)\n\t"
      "flds 0x4(%%esi)\n\t"
      "fsubs -0x14(%%ebp)\n\t"
      "fstps 0x4(%%esi)\n\t"
      "fxch %%st(1)\n\t"
      "fsubs -0x18(%%ebp)\n\t"
      "fstps -0x30(%%ebp)\n\t"
      "fsubs -0x14(%%ebp)\n\t"
      "flds 0x2533c0\n\t"
      "flds 0x2d0(%%edx)\n\t"
      "fld %%st(1)\n\t"
      ".byte 0xd8, 0xca\n\t"
      "fld %%st(3)\n\t"
      ".byte 0xd8, 0xcc\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds -0x30(%%ebp)\n\t"
      "fmuls -0x30(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fld %%st(1)\n\t"
      ".byte 0xd8, 0xca\n\t"
      "fcompp\n\t"
      "fstp %%st(0)\n\t"
      "fnstsw %%ax\n\t"
      "fstp %%st(0)\n\t"
      "testb $1, %%ah\n\t"
      "fstp %%st(0)\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "jne .Lupdate_motion_sensor_10\n\t"
      "subl %%eax, %%ecx\n\t"
      "leal 0x40(%%ebx,%%ecx,2), %%edi\n\t"
      "call *%[cdade0]\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "jmp .Lupdate_motion_sensor_11\n\t"
      ".Lupdate_motion_sensor_10:\n\t"
      "incl %%eax\n\t"
      "movl %%eax, 0x8(%%ebp)\n\t"
      ".Lupdate_motion_sensor_11:\n\t"
      "movzbl 0x80(%%ebx), %%eax\n\t"
      "incl %%ecx\n\t"
      "addl $8, %%esi\n\t"
      "cmpl %%eax, %%ecx\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "jl .Lupdate_motion_sensor_9\n\t"
      ".Lupdate_motion_sensor_12:\n\t"
      "movb 0x80(%%ebx), %%al\n\t"
      "movb 0x8(%%ebp), %%cl\n\t"
      "subb %%cl, %%al\n\t"
      "movb %%al, 0x80(%%ebx)\n\t"
      ".Lupdate_motion_sensor_13:\n\t"
      "popl %%ebx\n\t"
      ".Lupdate_motion_sensor_14:\n\t"
      "movl $0x7f, %%eax\n\t"
      "movl $0x62626262, %%ecx\n\t"
      ".Lupdate_motion_sensor_15:\n\t"
      "movswl %%ax, %%edx\n\t"
      "cmpl %%ecx, -0x2c0(%%ebp,%%edx,4)\n\t"
      "jne .Lupdate_motion_sensor_10000\n\t"
      "decl %%eax\n\t"
      "testw %%ax, %%ax\n\t"
      "jge .Lupdate_motion_sensor_15\n\t"
      "orl $0xffffffff, %%esi\n\t"
      "call *%[cd1540]\n\t"
      "cmpl %%eax, -0x24(%%ebp)\n\t"
      "je .Lupdate_motion_sensor_16\n\t"
      "pushl $1\n\t"
      "pushl $0x2f4\n\t"
      "pushl $0x282094\n\t"
      "pushl $0x281960\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lupdate_motion_sensor_16:\n\t"
      "cmpw $-1, %%si\n\t"
      "je .Lupdate_motion_sensor_17\n\t"
      "pushl $1\n\t"
      "pushl $0x2f4\n\t"
      "movswl %%si, %%eax\n\t"
      "pushl $0x282094\n\t"
      "pushl %%eax\n\t"
      "pushl $0x281948\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0xc, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lupdate_motion_sensor_17:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lupdate_motion_sensor_10000:\n\t"
      "jmp *%[cdbc9d]\n\t"
      :
      : [cd1540] "m"(bdb950_cd1540), [memset] "m"(bdb950_memset), [assert] "m"(bdb950_assert), [exitfn] "m"(bdb950_exitfn), [gtime] "m"(bdb950_gtime), [cba3c0] "m"(bdb950_cba3c0), [dget] "m"(bdb950_dget), [useat] "m"(bdb950_useat), [tryget] "m"(bdb950_tryget), [cdb250] "m"(bdb950_cdb250), [c1aae0] "m"(bdb950_c1aae0), [cdade0] "m"(bdb950_cdade0), [cb7e30] "m"(bdb950_cb7e30), [ca9210] "m"(bdb950_ca9210), [c8d9d0] "m"(bdb950_c8d9d0), [cdbc9d] "m"(bdb950_cdbc9d)
      : "memory");
}
#else
#error "update_motion_sensor: clang naked draft required"
#endif


/* FUN_000dbcb0 (0xdbcb0) — XBE naked draft (batch 112). */
#if defined(__clang__)
static int (*const bdbcb0_cd1540)(void) = FUN_000d1540;
static void *(*const bdbcb0_memset)(void *, int, unsigned int) = csmemset;
static int16_t (*const bdbcb0_c86410)(int16_t local_player_index) = director_get_perspective;
static char *(*const bdbcb0_cdb0b0)(int16_t local_player_index) = FUN_000db0b0;
static void (*const bdbcb0_cdb1e0)(void) = FUN_000db1e0;
static float (*const bdbcb0_c1d9e70)(float base, float exponent) = FUN_001d9e70;
static void (*const bdbcb0_cdb330)(void) = render_blip;
static void (*const bdbcb0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const bdbcb0_exitfn)(int) = system_exit;
static char (*const bdbcb0_ca9360)(short param_1) = game_engine_get_goal_in_use;
static void (*const bdbcb0_c17d070)(void) = FUN_0017d070;
static char * (*const bdbcb0_c8d9d0)(char *buffer, const char *format, ...) = csprintf;
static void (*const bdbcb0_cdbf9d)(void) = (void (*)(void))FUN_000dbfb0;

__attribute__((naked, noinline))
void FUN_000dbcb0(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x23c, %%esp\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl %%eax, %%edi\n\t"
      "movl %%ecx, %%esi\n\t"
      "call *%[cd1540]\n\t"
      "pushl $0x200\n\t"
      "movl %%eax, -0x2c(%%ebp)\n\t"
      "leal -0x23c(%%ebp), %%eax\n\t"
      "pushl $0x62\n\t"
      "pushl %%eax\n\t"
      "call *%[memset]\n\t"
      "pushl %%esi\n\t"
      "call *%[c86410]\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpw $3, %%ax\n\t"
      "je .LFUN_000dbcb0_8\n\t"
      "cmpw $2, %%ax\n\t"
      "je .LFUN_000dbcb0_8\n\t"
      "call *%[cdb0b0]\n\t"
      "movl %%eax, -0x28(%%ebp)\n\t"
      "movl 0x46bd0c, %%eax\n\t"
      "flds 0x2d8(%%eax)\n\t"
      "movswl (%%edi), %%ecx\n\t"
      "fdivs 0x2d0(%%eax)\n\t"
      "movswl 0x2(%%edi), %%edx\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl %%ecx, -0x4(%%ebp)\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "pushl $0\n\t"
      "leal -0x10(%%ebp), %%esi\n\t"
      "fstps -0x24(%%ebp)\n\t"
      "fildl -0x4(%%ebp)\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "fildl -0x4(%%ebp)\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "call *%[cdb1e0]\n\t"
      "movl $0xa, %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "movl $0, -0x18(%%ebp)\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "pushl %%ebx\n\t"
      "jmp .LFUN_000dbcb0_1\n\t"
      "leal (%%esp), %%esp\n\t"
      "leal (%%ebx), %%ebx\n\t"
      ".LFUN_000dbcb0_1:\n\t"
      "movl 0x46bd2c, %%ecx\n\t"
      "fildl -0x14(%%ebp)\n\t"
      "movswl 0x15a4(%%ecx), %%eax\n\t"
      "subl -0x18(%%ebp), %%eax\n\t"
      "addl $0xa, %%eax\n\t"
      "cdq\n\t"
      "movl $0xa, %%ecx\n\t"
      "idivl %%ecx\n\t"
      "movl -0x28(%%ebp), %%eax\n\t"
      "fmuls 0x25496c\n\t"
      "fsts -0x8(%%ebp)\n\t"
      "fmuls -0x8(%%ebp)\n\t"
      "fstps -0x1c(%%ebp)\n\t"
      "flds 0x2533c8\n\t"
      "fsubs -0x8(%%ebp)\n\t"
      "fldl 0x282170\n\t"
      "movswl %%dx, %%esi\n\t"
      "imull $0x84, %%esi, %%esi\n\t"
      "addl %%eax, %%esi\n\t"
      "call *%[c1d9e70]\n\t"
      "leal 0x2(%%esi), %%edi\n\t"
      "fmull 0x282168\n\t"
      "movl $0x10, -0x20(%%ebp)\n\t"
      "faddl 0x2573d8\n\t"
      "fstps -0x8(%%ebp)\n\t"
      ".LFUN_000dbcb0_2:\n\t"
      "movb (%%edi), %%bl\n\t"
      "cmpb $6, %%bl\n\t"
      "je .LFUN_000dbcb0_3\n\t"
      "movsbl -0x2(%%edi), %%edx\n\t"
      "movl 0x46bd0c, %%eax\n\t"
      "movsbl -0x1(%%edi), %%ecx\n\t"
      "movl %%edx, -0xc(%%ebp)\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "fildl -0xc(%%ebp)\n\t"
      "pushl %%edx\n\t"
      "movl %%ecx, -0xc(%%ebp)\n\t"
      "movl -0x24(%%ebp), %%ecx\n\t"
      "fmuls 0x2d0(%%eax)\n\t"
      "xorl %%edx, %%edx\n\t"
      "movb 0x1(%%edi), %%dl\n\t"
      "fmuls 0x2820c0\n\t"
      "fstps -0x34(%%ebp)\n\t"
      "fildl -0xc(%%ebp)\n\t"
      "fmuls 0x2d0(%%eax)\n\t"
      "movl -0x1c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "fmuls 0x2820c0\n\t"
      "pushl %%edx\n\t"
      "pushl %%esi\n\t"
      "leal -0x34(%%ebp), %%eax\n\t"
      "fstps -0x30(%%ebp)\n\t"
      "call *%[cdb330]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000dbcb0_3:\n\t"
      "movl -0x20(%%ebp), %%eax\n\t"
      "addl $4, %%edi\n\t"
      "decl %%eax\n\t"
      "movl %%eax, -0x20(%%ebp)\n\t"
      "jne .LFUN_000dbcb0_2\n\t"
      "movb 0x80(%%esi), %%al\n\t"
      "xorl %%edi, %%edi\n\t"
      "testb %%al, %%al\n\t"
      "jbe .LFUN_000dbcb0_7\n\t"
      "xorl %%ebx, %%ebx\n\t"
      ".LFUN_000dbcb0_4:\n\t"
      "cmpw $0x10, %%di\n\t"
      "jl .LFUN_000dbcb0_5\n\t"
      "pushl $1\n\t"
      "pushl $0x32f\n\t"
      "pushl $0x282094\n\t"
      "pushl $0x282148\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000dbcb0_5:\n\t"
      "movsbw 0x60(%%ebx,%%esi,1), %%ax\n\t"
      "pushl %%eax\n\t"
      "call *%[ca9360]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000dbcb0_6\n\t"
      "movsbl 0x40(%%esi,%%ebx,2), %%ecx\n\t"
      "movl 0x46bd0c, %%eax\n\t"
      "movsbl 0x41(%%esi,%%ebx,2), %%edx\n\t"
      "movl %%ecx, -0xc(%%ebp)\n\t"
      "movl -0x1c(%%ebp), %%ecx\n\t"
      "fildl -0xc(%%ebp)\n\t"
      "movl %%edx, -0xc(%%ebp)\n\t"
      "movl -0x24(%%ebp), %%edx\n\t"
      "movb $5, %%bl\n\t"
      "fmuls 0x2d0(%%eax)\n\t"
      "fmuls 0x2820c0\n\t"
      "fstps -0x3c(%%ebp)\n\t"
      "fildl -0xc(%%ebp)\n\t"
      "fmuls 0x2d0(%%eax)\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "fmuls 0x2820c0\n\t"
      "pushl %%edx\n\t"
      "pushl $0\n\t"
      "pushl %%esi\n\t"
      "leal -0x3c(%%ebp), %%eax\n\t"
      "fstps -0x38(%%ebp)\n\t"
      "call *%[cdb330]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000dbcb0_6:\n\t"
      "movzbl 0x80(%%esi), %%eax\n\t"
      "incl %%edi\n\t"
      "movswl %%di, %%ebx\n\t"
      "cmpl %%eax, %%ebx\n\t"
      "jl .LFUN_000dbcb0_4\n\t"
      ".LFUN_000dbcb0_7:\n\t"
      "movl -0x18(%%ebp), %%edx\n\t"
      "movl -0x14(%%ebp), %%ecx\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "incl %%edx\n\t"
      "decl %%ecx\n\t"
      "decl %%eax\n\t"
      "movl %%edx, -0x18(%%ebp)\n\t"
      "movl %%ecx, -0x14(%%ebp)\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "jne .LFUN_000dbcb0_1\n\t"
      "movl 0x46bd30, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x5aa680\n\t"
      "call *%[c17d070]\n\t"
      "addl $8, %%esp\n\t"
      "popl %%ebx\n\t"
      ".LFUN_000dbcb0_8:\n\t"
      "movl $0x7f, %%eax\n\t"
      "movl $0x62626262, %%ecx\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".LFUN_000dbcb0_9:\n\t"
      "movswl %%ax, %%edx\n\t"
      "cmpl %%ecx, -0x23c(%%ebp,%%edx,4)\n\t"
      "jne .LFUN_000dbcb0_10000\n\t"
      "decl %%eax\n\t"
      "testw %%ax, %%ax\n\t"
      "jge .LFUN_000dbcb0_9\n\t"
      "orl $0xffffffff, %%esi\n\t"
      "call *%[cd1540]\n\t"
      "cmpl %%eax, -0x2c(%%ebp)\n\t"
      "je .LFUN_000dbcb0_10\n\t"
      "pushl $1\n\t"
      "pushl $0x33e\n\t"
      "pushl $0x282094\n\t"
      "pushl $0x281960\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000dbcb0_10:\n\t"
      "cmpw $-1, %%si\n\t"
      "je .LFUN_000dbcb0_11\n\t"
      "pushl $1\n\t"
      "pushl $0x33e\n\t"
      "movswl %%si, %%eax\n\t"
      "pushl $0x282094\n\t"
      "pushl %%eax\n\t"
      "pushl $0x281948\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0xc, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000dbcb0_11:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000dbcb0_10000:\n\t"
      "jmp *%[cdbf9d]\n\t"
      :
      : [cd1540] "m"(bdbcb0_cd1540), [memset] "m"(bdbcb0_memset), [c86410] "m"(bdbcb0_c86410), [cdb0b0] "m"(bdbcb0_cdb0b0), [cdb1e0] "m"(bdbcb0_cdb1e0), [c1d9e70] "m"(bdbcb0_c1d9e70), [cdb330] "m"(bdbcb0_cdb330), [assert] "m"(bdbcb0_assert), [exitfn] "m"(bdbcb0_exitfn), [ca9360] "m"(bdbcb0_ca9360), [c17d070] "m"(bdbcb0_c17d070), [c8d9d0] "m"(bdbcb0_c8d9d0), [cdbf9d] "m"(bdbcb0_cdbf9d)
      : "memory");
}
#else
#error "FUN_000dbcb0: clang naked draft required"
#endif


/* FUN_000dbfb0 (0xdbfb0) — readable C lift. */
void FUN_000dbfb0(int16_t local_player_index, int param_2, void *pt)
{
  extern char DAT_00282094[];
  extern char DAT_00282178[];
  if (!pt) {
    display_assert(DAT_00282178, DAT_00282094, 0x1dc, 1);
    system_exit(-1);
  }
  if ((int16_t)local_player_index != (int16_t)-1) {
    ((void (*)(int))update_motion_sensor)(local_player_index);
    ((void (*)(int, int, void *))FUN_000dbcb0)(local_player_index, param_2, pt);
  }
}

/* FUN_000dc000 (0xdc000) — readable C lift from XBE leaf.
 * phase = fmod(game_time * k, period); drive motion-sensor blend factor. */
void FUN_000dc000(void)
{
  float phase;
  int t;

  t = game_time_get();
  phase = x87_fmod((float)t * *(float *)0x2546a4, *(double *)0x282180);
  if (phase < *(float *)0x28217c) {
    *(float *)0x46bd30 =
        *(float *)0x2533c8 / ((phase + *(float *)0x255d90) * *(float *)0x2f6708);
  } else {
    *(unsigned int *)0x46bd30 = 0x3ecccccd;
  }
  motion_sensor_update();
}


