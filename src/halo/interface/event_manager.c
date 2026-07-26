/* motion_sensor_initialize (0xdb0f0) — XBE naked draft (batch 99). */
#if defined(__clang__)
static void * (*const bdb0f0_c1bfbf0)(const char *name, const char *a2, int size) = game_state_malloc;
static void (*const bdb0f0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const bdb0f0_exitfn)(int) = system_exit;

__attribute__((naked, noinline))
void motion_sensor_initialize(void)
{
  __asm__ volatile(
      "pushl $0x15a8\n\t"
      "pushl $0x282100\n\t"
      "pushl $0x2820e8\n\t"
      "call *%[c1bfbf0]\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%eax, 0x46bd2c\n\t"
      "jne .Lmotion_sensor_initialize_1\n\t"
      "pushl $1\n\t"
      "pushl $0x12a\n\t"
      "pushl $0x282094\n\t"
      "pushl $0x2820d0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lmotion_sensor_initialize_1:\n\t"
      "ret\n\t"
      :
      : [c1bfbf0] "m"(bdb0f0_c1bfbf0), [assert] "m"(bdb0f0_assert), [exitfn] "m"(bdb0f0_exitfn)
      : "memory");
}
#else
#error "motion_sensor_initialize: clang naked draft required"
#endif


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

/* 0xd98c0 */
void FUN_000d98c0(void)
{
  int ebx = 0;

  display_assert((char *)0x00281eb8, (char *)0x00281eec, 137, 0);
  system_exit(0);
  /* cmp (int16_t)ebx, -1 -> jne 0xd9918 */
  display_assert((char *)0x00281e98, (char *)0x00281eec, 138, 0);
  system_exit(0);
  FUN_000d8bc0(0);
  FUN_000d8bc0(0);
  FUN_000d8c30(0);
  FUN_000d8c30(0);

  (void)ebx;
}

/* 0xd9960 */
void FUN_000d9960(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  FUN_000d1540();
  csmemset((void *)(uintptr_t)eax, 98, 512);
  local_player_get_player_index(ebx);
  datum_get((void *)(uintptr_t)ecx, 0);
  object_try_and_get_and_verify_type(0, 0);
  FUN_000d8c30(0);
  tag_get('ihpw', 0);
  /* cmp eax, -1 -> je 0xd99fa */
  object_get_and_verify_type(0, 0);
  tag_get('paew', 0);
  FUN_000d8bc0(0);
  /* relift: cmp edx, dword ptr [eax + 0x20] -> je 0xd9a4b */
  /* cmp eax, -1 -> jne 0xd9a4b */
  csmemset((void *)(uintptr_t)eax, 0, 80);
  tag_get('ihpw', 0);
  error(0, (char *)0x00281f8c);
  /* cmp ebx, 0x12 -> ja 0xd9d64 */
  /* relift: cmp dword ptr [ebp + 8], -1 -> je 0xd9d3a */
  player_control_get_autoaim_level(eax);
  player_control_get_zoom_level(edx);
  /* cmp (int16_t)eax, 0xffff -> je 0xd9bca */
  player_control_get_zoom_level(ecx);
  /* test (int16_t)eax, (int16_t)eax -> jne 0xd9b81 */
  /* relift: cmp word ptr [edi + 0xe], (int16_t)eax -> je 0xd9d3a */
  /* test (int16_t)eax, (int16_t)eax -> je 0xd9d3a */
  /* relift: cmp (int16_t)eax, word ptr [ecx + 0x14] -> jg 0xd9d3a */
  /* test (char)eax, (char)eax -> jne 0xd9d3a */
  /* cmp ebx, 0x12 -> ja 0xd9de8 */
  /* relift: cmp dword ptr [edi + 4], 0x3f800000 -> jne 0xd9c41 */
  /* test (char)eax, 8 -> jne 0xd9bca */
  /* relift: cmp word ptr [edi + 0xe], 0 -> jne 0xd9d2b */
  /* test (char)eax, (char)eax -> je 0xd9c7e */
  /* relift: cmp byte ptr [ecx], 0 -> jne 0xd9c7e */
  /* test (char)eax, (char)eax -> je 0xd9ca1 */
  /* test (char)eax, (char)eax -> jne 0xd9ca1 */
  /* test (char)eax, 0x20 -> jne 0xd9bca */
  /* relift: cmp dword ptr [edx + ebx*4], -1 -> jne 0xd9bca */
  /* test (int16_t)eax, (int16_t)eax -> jne 0xd9d3a */
  /* relift: cmp word ptr [edi + 0xe], (int16_t)eax -> je 0xd9d3a */
  /* test (int16_t)eax, (int16_t)eax -> jne 0xd9d3a */
  /* test (int16_t)eax, (int16_t)eax -> jne 0xd9d52 */
  /* relift: cmp word ptr [edi + 0x18], (int16_t)eax -> je 0xd9d3a */
  /* test (int16_t)eax, (int16_t)eax -> je 0xd9d3a */
  /* relift: cmp (int16_t)ecx, word ptr [edx + 0x14] -> jg 0xd9d3a */
  /* relift: cmp word ptr [edi + 0x18], 0 -> jne 0xd9d2b */
  /* relift: cmp word ptr [edi + 0x1c], 0 -> jne 0xd9d2b */
  /* test (char)ecx, 8 -> jne 0xd9bca */
  /* cmp eax, -1 -> jne 0xd9bca */
  /* test (int16_t)eax, (int16_t)eax -> jne 0xd9d3a */
  /* relift: cmp word ptr [edi + 0x18], (int16_t)eax -> je 0xd9d3a */
  /* test (int16_t)eax, (int16_t)eax -> jne 0xd9d3a */
  /* relift: cmp (int16_t)edx, word ptr [eax + 0x16] -> jg 0xd9d3a */
  display_assert((char *)0x00255ee8, (char *)0x00281eec, 366, 0);
  system_exit(0);
  /* test (int16_t)esi, (int16_t)esi -> jg 0xd9bcf */
  /* relift: cmp word ptr [ebp - 0x10], 0 -> je 0xd9bcf */
  /* test (int16_t)esi, (int16_t)esi -> jne 0xd9dd2 */
  /* relift: cmp dword ptr [edx + ebx*4], -1 -> jne 0xd9e08 */
  game_time_get();
  display_assert((char *)0x00255ee8, (char *)0x00281eec, 407, 0);
  system_exit(0);
  /* relift: cmp dword ptr [ebp + edx*4 - 0x2a8], ecx -> jne 0xd9ead */
  /* test (int16_t)eax, (int16_t)eax -> jge 0xd9e30 */
  FUN_000d1540();
  /* relift: cmp dword ptr [ebp - 0x28], eax -> je 0xd9e6f */
  display_assert((char *)0x00281960, (char *)0x00281eec, 414, 0);
  system_exit(0);
  /* cmp (int16_t)esi, -1 -> je 0xd9ea7 */
  csprintf((char *)0x005ab100, (char *)0x00281948);
  display_assert((char *)(uintptr_t)eax, (char *)0, 0, 0);
  system_exit(0);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

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


/* 0xda980 */
void hud_update_weapon(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  FUN_000d1540();
  csmemset((void *)(uintptr_t)eax, 98, 512);
  local_player_get_next(0);
  local_player_get_player_index(edi);
  /* cmp eax, -1 -> je 0xdab39 */
  local_player_get_player_index(edi);
  datum_get((void *)(uintptr_t)ecx, 0);
  /* cmp esi, -1 -> je 0xdab39 */
  object_get_and_verify_type(0, 0);
  unit_get_weapon(0, edx);
  /* cmp ebx, -1 -> jne 0xdaab6 */
  object_get_and_verify_type(0, 0);
  /* cmp eax, ebx -> je 0xdaaed */
  /* relift: cmp word ptr [edi + 0x2a0], (int16_t)ebx -> je 0xdaaed */
  object_get_and_verify_type(0, 0);
  tag_get(0x756e6974, 0);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  /* test (char)ecx, 8 -> je 0xdab2c */
  object_get_and_verify_type(0, 0);
  unit_get_weapon(0, ecx);
  /* cmp ebx, -1 -> je 0xdaaed */
  object_get_and_verify_type(0, 0);
  tag_get('paew', 0);
  weapon_build_weapon_interface_state(0, 0);
  /* cmp eax, -1 -> je 0xdab2c */
  unit_count_weapons(0);
  /* test (int16_t)eax, (int16_t)eax -> jne 0xdab2c */
  FUN_000d9960();
  FUN_000d8bc0(0);
  local_player_get_next(edi);
  /* relift: cmp dword ptr [ebp + edx*4 - 0x248], ecx -> jne 0xdabdd */
  /* test (int16_t)eax, (int16_t)eax -> jge 0xdab60 */
  FUN_000d1540();
  /* relift: cmp dword ptr [ebp - 8], eax -> je 0xdab9f */
  display_assert((char *)0x00281960, (char *)0x00281eec, 212, 0);
  system_exit(0);
  /* cmp (int16_t)esi, -1 -> je 0xdabd7 */
  csprintf((char *)0x005ab100, (char *)0x00281948);
  display_assert((char *)(uintptr_t)eax, (char *)0, 0, 0);
  system_exit(0);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0xdabf0 */
void FUN_000dabf0(int param_1)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;

  object_get_and_verify_type(0, 0);
  unit_get_weapon(0, ecx);
  object_get_and_verify_type(0, 0);
  /* cmp eax, edi -> je 0xdacc1 */
  /* relift: cmp word ptr [esi + 0x2a0], (int16_t)edi -> je 0xdacc1 */
  object_get_and_verify_type(0, 0);
  tag_get(0x756e6974, 0);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  /* test (char)ecx, 8 -> je 0xdacbd */
  object_get_and_verify_type(0, 0);
  unit_get_weapon(0, ecx);
  /* relift: cmp (int16_t)eax, word ptr [0x506548] -> je 0xdacee */
  display_assert((char *)0x002819b8, (char *)0x00281eec, 472, 0);
  system_exit(0);
  /* cmp edi, -1 -> je 0xdad66 */
  object_get_and_verify_type(0, 0);
  tag_get('paew', 0);
  weapon_build_weapon_interface_state(0, 0);
  /* cmp esi, -1 -> je 0xdadb0 */
  FUN_000d8ff0(0, (void *)(uintptr_t)eax, 0, 0);
  render_weapon_hud();
  FUN_000d8ca0(0, 0);
  /* test (char)eax, (char)eax -> jne 0xdadb0 */
  unit_count_weapons(0);
  /* test (int16_t)eax, (int16_t)eax -> jne 0xdadb0 */
  FUN_000d8ff0(0, (void *)(uintptr_t)eax, 0, 0);
  FUN_000d8cf0(0, 0);
  /* cmp (int16_t)ebx, -1 -> je 0xdadd7 */
  FUN_000d8bc0(0);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)esi;
  (void)edi;
}

/* 0xdade0 */
void tiny_point2d_set(void)
{
  int eax = 0;

  /* test (char)eax, 0x41 -> je 0xdae15 */
  display_assert((char *)0x00282054, (char *)0x00282094, 105, 0);
  system_exit(0);
  /* test (char)eax, 0x41 -> je 0xdae4c */
  display_assert((char *)0x00282014, (char *)0x00282094, 106, 0);
  system_exit(0);
  FUN_001d9068();
  FUN_001d9068();

  (void)eax;
}

/* 0xdae90 */
void FUN_000dae90(void)
{
  /* relift: no calls detected — manual review */
}

/* 0xdaee0 */
void FUN_000daee0(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;

  local_player_get_player_index(ebx);
  datum_get((void *)(uintptr_t)eax, 0);
  player_index_from_unit_index(0);
  /* cmp eax, -1 -> jne 0xdaf1c */
  player_index_from_unit_index(0);
  datum_get((void *)(uintptr_t)edx, 0);
  /* cmp eax, ebx -> jne 0xdaf40 */
  object_try_and_get_and_verify_type(0, 0);
  /* test eax, eax -> jne 0xdaf55 */
  object_get_and_verify_type(0, 0);
  object_try_and_get_and_verify_type(0, 0);
  /* test eax, eax -> je 0xdb00d */
  object_get_and_verify_type(0, 0);
  /* cmp ecx, -1 -> je 0xdafb0 */
  object_get_and_verify_type(0, 0);
  game_allegiance_get_team_is_friendly(edx, ecx);
  /* cmp ecx, -1 -> jne 0xdaf89 */
  tag_get('tinu', 0);
  /* cmp ecx, 1 -> jle 0xdb006 */
  tag_block_get_element((void *)(uintptr_t)eax, 0, 284);
  csstrncmp((char *)(uintptr_t)eax, (char *)0x002820c4, 0);
  /* test eax, eax -> jne 0xdb006 */
  local_player_get_player_index(ebx);
  datum_get((void *)(uintptr_t)ecx, 0);
  game_allegiance_get_team_is_friendly(edx, eax);
  /* relift: tail-call FUN_000daee0(); */
  object_try_and_get_and_verify_type(0, 0);
  /* test eax, eax -> je 0xdb090 */
  object_get_and_verify_type(0, 0);
  tag_get('tinu', 0);
  /* test (int16_t)eax, (int16_t)eax -> jl 0xdb089 */
  /* cmp (int16_t)eax, 3 -> jl 0xdb092 */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
}

/* 0xdb0b0 */
void FUN_000db0b0(void)
{
  int esi = 0;

  /* test (int16_t)esi, (int16_t)esi -> jl 0xdb0bb */
  /* cmp (int16_t)esi, 4 -> jl 0xdb0db */
  display_assert((char *)0x00266fc0, (char *)0x00282094, 287, 0);
  system_exit(0);

  (void)esi;
}

/* 0xdb1e0 */
void FUN_000db1e0(void)
{
  int ecx = 0;
  int edx = 0;
  int esi = 0;

  /* test esi, esi -> jne 0xdb207 */
  display_assert((char *)0x0028210c, (char *)0x00282094, 841, 0);
  system_exit(0);
  /* mem[0x002f66f4] = 0x3f400000 */
  /* mem[0x002f66f4] = 0x3f800000 */
  /* mem[0x005aa680] = ecx */
  /* mem[0x005aa684] = edx */

  (void)ecx;
  (void)edx;
  (void)esi;
}

/* 0xdb250 */
void FUN_000db250(void)
{
  int eax = 0;
  int ecx = 0;
  int edi = 0;

  object_try_and_get_and_verify_type(0, 0);
  /* test eax, eax -> je 0xdb31b */
  FUN_000ab9a0();
  /* test (char)eax, (char)eax -> je 0xdb31b */
  object_get_and_verify_type(0, 0);
  /* test (char)eax, 8 -> jne 0xdb313 */
  /* test (char)eax, (char)eax -> je 0xdb2a4 */
  /* cmp (char)eax, 3 -> jne 0xdb313 */
  object_get_root_location(0, (float *)(uintptr_t)eax, (float *)0);
  game_engine_running();
  /* test (char)eax, (char)eax -> jne 0xdb2c9 */
  /* relift: test byte ptr [edi + 0x1b4], 0x10 -> je 0xdb2c9 */
  /* test (char)eax, 1 -> je 0xdb301 */
  /* test (char)eax, (char)eax -> jne 0xdb301 */
  /* test (char)ecx, (char)ecx -> je 0xdb30b */
  /* test (char)eax, (char)eax -> jne 0xdb313 */

  (void)eax;
  (void)ecx;
  (void)edi;
}

/* 0xdb330 */
void render_blip(void)
{
  display_assert((char *)0x00282128, (char *)0x00282094, 410, 0);
  system_exit(0);
  FUN_001d9e70(0.0f, 0.0f);
  game_time_get();
  FUN_0017d060();
}

/* 0xdb4c0 */
void motion_sensor_update(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  FUN_000d1540();
  csmemset((void *)(uintptr_t)eax, 98, 512);
  game_engine_running();
  game_time_get();
  /* test edx, edx -> je 0xdb5c9 */
  /* test esi, esi -> je 0xdb5c9 */
  local_player_count();
  local_player_get_next(0);
  csmemcpy((void *)(uintptr_t)eax, (void *)0, 0);
  local_player_get_next(esi);
  local_player_count();
  local_player_get_next(0);
  local_player_get_player_index(0);
  /* cmp eax, -1 -> jne 0xdb643 */
  local_player_get_player_index(ebx);
  datum_get((void *)(uintptr_t)edx, 0);
  unit_set_seat_state(0, (float *)(uintptr_t)ecx);
  local_player_get_next(ebx);
  object_iterator_new((void *)(uintptr_t)edx, 0, 0);
  object_iterator_next((void *)(uintptr_t)eax);
  /* test eax, eax -> je 0xdb8b2 */
  /* test (char)eax, (char)eax -> jne 0xdb8b2 */
  object_try_and_get_and_verify_type(0, 0);
  /* test eax, eax -> je 0xdb89e */
  /* relift: test byte ptr [eax + 0xb6], 4 -> jne 0xdb89e */
  FUN_000db250();
  /* test (char)eax, (char)eax -> je 0xdb89e */
  FUN_0001aae0(0, (float *)(uintptr_t)eax, (float *)(uintptr_t)edx);
  /* test (int16_t)edi, (int16_t)edi -> jle 0xdb890 */
  game_engine_running();
  /* test (char)eax, (char)eax -> jne 0xdb7d5 */
  FUN_000daee0();
  object_try_and_get_and_verify_type(0, 0);
  /* test eax, eax -> je 0xdb84f */
  object_get_and_verify_type(0, 0);
  tag_get('tinu', 0);
  /* test (int16_t)eax, (int16_t)eax -> jl 0xdb84b */
  /* cmp (int16_t)eax, 3 -> jl 0xdb851 */
  /* cmp eax, edx -> jne 0xdb89e */
  object_iterator_next((void *)(uintptr_t)eax);
  /* test eax, eax -> jne 0xdb6e0 */
  /* relift: cmp dword ptr [ebp + edx*4 - 0x284], ecx -> jne 0xdb93e */
  /* test (int16_t)eax, (int16_t)eax -> jge 0xdb8c0 */
  FUN_000d1540();
  /* relift: cmp dword ptr [ebp - 0x40], eax -> je 0xdb8ff */
  display_assert((char *)0x00281960, (char *)0x00282094, 642, 0);
  system_exit(0);
  /* cmp (int16_t)esi, -1 -> je 0xdb937 */
  csprintf((char *)0x005ab100, (char *)0x00281948);
  display_assert((char *)(uintptr_t)eax, (char *)0, 0, 0);
  system_exit(0);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0xdb950 */
void update_motion_sensor(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  FUN_000d1540();
  csmemset((void *)(uintptr_t)eax, 98, 512);
  /* test (int16_t)edi, (int16_t)edi -> jl 0xdb987 */
  /* cmp (int16_t)edi, 4 -> jl 0xdb9a7 */
  display_assert((char *)0x00266fc0, (char *)0x00282094, 287, 0);
  system_exit(0);
  game_time_get();
  /* test (char)ecx, (char)ecx -> je 0xdbc16 */
  local_player_get_player_index(edi);
  /* cmp eax, -1 -> jne 0xdb9ed */
  local_player_get_player_index(edi);
  datum_get((void *)(uintptr_t)ecx, 0);
  /* cmp eax, -1 -> je 0xdbc15 */
  unit_set_seat_state(0, (float *)(uintptr_t)ecx);
  object_try_and_get_and_verify_type(0, 0);
  /* test eax, eax -> je 0xdbaff */
  FUN_000db250();
  FUN_0001aae0(0, (float *)(uintptr_t)edx, (float *)(uintptr_t)ecx);
  tiny_point2d_set();
  player_control_get_facing_angles(esi);
  local_player_get_player_index(esi);
  game_engine_player_get_custom_motion_sensor_positions(0, 0, 0, 0);
  unit_set_seat_state(0, (float *)(uintptr_t)edx);
  tiny_point2d_set();
  /* relift: cmp dword ptr [ebp + edx*4 - 0x2c0], ecx -> jne 0xdbc9d */
  /* test (int16_t)eax, (int16_t)eax -> jge 0xdbc20 */
  FUN_000d1540();
  /* relift: cmp dword ptr [ebp - 0x24], eax -> je 0xdbc5f */
  display_assert((char *)0x00281960, (char *)0x00282094, 756, 0);
  system_exit(0);
  /* cmp (int16_t)esi, -1 -> je 0xdbc97 */
  csprintf((char *)0x005ab100, (char *)0x00281948);
  display_assert((char *)(uintptr_t)eax, (char *)0, 0, 0);
  system_exit(0);

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0xdbcb0 */
void FUN_000dbcb0(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  FUN_000d1540();
  csmemset((void *)(uintptr_t)eax, 98, 512);
  director_get_perspective(esi);
  /* cmp (int16_t)eax, 3 -> je 0xdbf13 */
  /* cmp (int16_t)eax, 2 -> je 0xdbf13 */
  FUN_000db0b0();
  FUN_000db1e0();
  FUN_001d9e70(0.0f, 0.0f);
  /* cmp (char)ebx, 6 -> je 0xdbe24 */
  render_blip();
  /* test (char)eax, (char)eax -> jbe 0xdbee3 */
  /* cmp (int16_t)edi, 0x10 -> jl 0xdbe68 */
  display_assert((char *)0x00282148, (char *)0x00282094, 815, 0);
  system_exit(0);
  game_engine_get_goal_in_use(0);
  /* test (char)eax, (char)eax -> je 0xdbed0 */
  render_blip();
  /* cmp ebx, eax -> jl 0xdbe42 */
  FUN_0017d070();
  /* relift: cmp dword ptr [ebp + edx*4 - 0x23c], ecx -> jne 0xdbf9d */
  /* test (int16_t)eax, (int16_t)eax -> jge 0xdbf20 */
  FUN_000d1540();
  /* relift: cmp dword ptr [ebp - 0x2c], eax -> je 0xdbf5f */
  display_assert((char *)0x00281960, (char *)0x00282094, 830, 0);
  system_exit(0);
  /* cmp (int16_t)esi, -1 -> je 0xdbf97 */
  csprintf((char *)0x005ab100, (char *)0x00281948);
  display_assert((char *)(uintptr_t)eax, (char *)0, 0, 0);
  system_exit(0);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0xdbfb0 */
void FUN_000dbfb0(int param_1, int param_2, int param_3)
{
  int esi = 0;
  int edi = 0;

  /* test edi, edi -> jne 0xdbfdc */
  display_assert((char *)0x00282178, (char *)0x00282094, 476, 0);
  system_exit(0);
  /* cmp (int16_t)esi, -1 -> je 0xdbffb */
  update_motion_sensor();
  FUN_000dbcb0();

  (void)esi;
  (void)edi;
}

/* 0xdc000 */
void FUN_000dc000(void)
{
  game_time_get();
  FUN_001daf7e();
  motion_sensor_update();
  /* mem[0x0046bd30] = 0x3ecccccd */
  motion_sensor_update();
}
