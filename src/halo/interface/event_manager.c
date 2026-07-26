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

/* 0xd9f20 */
void render_weapon_hud(void)
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
  tag_get('ihpw', 0);
  FUN_000d8bc0(0);
  /* relift: test byte ptr [ebx + 0x10], 1 -> je 0xd9ffe */
  /* test eax, eax -> je 0xd9ffe */
  /* test edi, edi -> je 0xd9ffe */
  /* test esi, esi -> je 0xd9ffe */
  csmemcpy((void *)(uintptr_t)ecx, (void *)(uintptr_t)eax, 16);
  csmemcpy((void *)(uintptr_t)edx, (void *)(uintptr_t)edi, 16);
  csmemcpy((void *)(uintptr_t)eax, (void *)(uintptr_t)esi, 16);
  /* relift: cmp (int16_t)eax, word ptr [ebx + 0x14] -> jg 0xda011 */
  /* test (int16_t)eax, (int16_t)eax -> jne 0xda020 */
  local_player_count();
  /* cmp (int16_t)eax, 1 -> jle 0xda039 */
  /* relift: cmp (int16_t)edx, word ptr [ebx + 0x16] -> jg 0xda057 */
  /* test (char)eax, (char)eax -> jne 0xda057 */
  local_player_count();
  /* cmp (int16_t)eax, 1 -> jle 0xda075 */
  local_player_count();
  /* cmp (int16_t)eax, 1 -> jle 0xda0b3 */
  /* test (char)eax, 1 -> jne 0xda0df */
  FUN_000d1c50(0.0f);
  /* test eax, eax -> jge 0xda100 */
  FUN_000d1c50(0.0f);
  /* cmp eax, 0x64 -> jle 0xda121 */
  FUN_000d1c50(0.0f);
  local_player_count();
  /* cmp (int16_t)eax, 1 -> jle 0xda15a */
  /* relift: cmp (int16_t)eax, word ptr [ebx + 0x14] -> jg 0xda16e */
  /* test (int16_t)eax, (int16_t)eax -> jne 0xda17d */
  local_player_count();
  /* cmp (int16_t)eax, 1 -> jle 0xda192 */
  /* relift: cmp (int16_t)eax, word ptr [ebx + 0x16] -> jg 0xda1ad */
  /* test (char)eax, (char)eax -> jne 0xda1ad */
  local_player_count();
  /* cmp (int16_t)eax, 1 -> jle 0xda1c6 */
  /* relift: test byte ptr [edi], 1 -> je 0xda1e8 */
  /* relift: cmp dword ptr [esi], -1 -> jne 0xda1ee */
  game_time_get();
  /* relift: cmp (int16_t)ecx, word ptr [edi + 0x14] -> jg 0xda218 */
  /* test (char)eax, (char)eax -> jne 0xda218 */
  /* test dl, dl -> je 0xda22d */
  /* test (int16_t)ecx, (int16_t)ecx -> jne 0xda23c */
  /* test (int16_t)eax, (int16_t)eax -> jne 0xda24b */
  /* test dl, dl -> je 0xda279 */
  /* test (int16_t)ecx, (int16_t)ecx -> jne 0xda288 */
  /* test (int16_t)eax, (int16_t)eax -> jne 0xda297 */
  /* test (char)eax, (char)eax -> je 0xda2d5 */
  FUN_000d1c50(0.0f);
  /* test eax, eax -> jge 0xda2f9 */
  FUN_000d1c50(0.0f);
  /* cmp eax, 0x64 -> jle 0xda31a */
  FUN_000d1c50(0.0f);
  /* test (int16_t)eax, (int16_t)eax -> jne 0xda351 */
  /* test (char)eax, 1 -> jne 0xda388 */
  /* test (char)eax, (char)eax -> je 0xda399 */
  FUN_000d1c50(0.0f);
  /* test eax, eax -> jge 0xda3ba */
  FUN_000d1c50(0.0f);
  /* cmp eax, 0x64 -> jle 0xda3db */
  FUN_000d1c50(0.0f);
  /* test (int16_t)eax, (int16_t)eax -> jne 0xda412 */
  /* relift: cmp (int16_t)ebx, word ptr [esi + 0x14] -> jg 0xda439 */
  /* test (char)eax, (char)eax -> jne 0xda439 */
  /* test (char)ecx, (char)ecx -> je 0xda44e */
  /* test (int16_t)ebx, (int16_t)ebx -> jne 0xda45d */
  /* test (int16_t)eax, (int16_t)eax -> jne 0xda46c */
  /* test (char)ecx, (char)ecx -> je 0xda49d */
  /* test (int16_t)esi, (int16_t)esi -> jne 0xda4ac */
  /* test (int16_t)eax, (int16_t)eax -> jne 0xda4bb */
  FUN_001d9068();
  FUN_001d9068();
  player_control_get_target_object_index(ebx);
  player_control_get_autoaim_level(ebx);
  /* cmp esi, -1 -> je 0xda5bc */
  local_player_get_player_index(ebx);
  /* cmp eax, -1 -> jne 0xda548 */
  local_player_get_player_index(ebx);
  datum_get((void *)(uintptr_t)edx, 0);
  unit_set_seat_state(0, (float *)(uintptr_t)ecx);
  object_get_world_position(0, (void *)(uintptr_t)edx);
  /* cmp eax, -1 -> je 0xda5ed */
  /* relift: tail-call render_weapon_hud(); */
  global_scenario_get();
  local_player_count();
  /* cmp (int16_t)eax, 1 -> jne 0xda60e */
  local_player_count();
  /* cmp (int16_t)eax, 1 -> jle 0xda621 */
  tag_block_get_element((void *)(uintptr_t)esi, 0, 180);
  /* test (char)ecx, 1 -> jne 0xda68a */
  /* test ecx, edx -> je 0xda68a */
  FUN_000d3fe0(0, (void *)(uintptr_t)edx, 0, 0, 0);
  /* cmp eax, ecx -> jl 0xda640 */
  tag_block_get_element((void *)(uintptr_t)esi, 0, 180);
  /* test (char)ecx, 1 -> jne 0xda70a */
  /* test ecx, edx -> je 0xda70a */
  FUN_000d3340(0, 0, 0, 0, 0, 0, 0, 0.0f);
  /* cmp eax, ecx -> jl 0xda6b0 */
  tag_block_get_element((void *)(uintptr_t)eax, 0, 160);
  /* test (char)eax, 1 -> jne 0xda843 */
  /* test ecx, eax -> je 0xda843 */
  tag_block_get_element((void *)(uintptr_t)edx, 0, 0);
  /* test (char)eax, (char)eax -> je 0xda80a */
  FUN_001d9e70(0.0f, 0.0f);
  FUN_001daf7e();
  FUN_000d1c50(0.0f);
  FUN_000d3860(0, (void *)(uintptr_t)edx, (void *)(uintptr_t)edi, 0, 0, 0, 0, 0.0f);
  /* cmp ecx, edx -> jl 0xda731 */
  tag_block_get_element((void *)(uintptr_t)ebx, 0, 104);
  /* test (char)eax, 1 -> jne 0xda8d9 */
  /* test eax, edx -> je 0xda8d9 */
  local_player_count();
  FUN_000d4260(0, 0, 0, 0, 0, 0, 0);
  /* cmp eax, ecx -> jl 0xda876 */
  /* relift: cmp dword ptr [ebp + edx*4 - 0x284], ecx -> jne 0xda971 */
  /* test (int16_t)eax, (int16_t)eax -> jge 0xda8f3 */
  FUN_000d1540();
  /* relift: cmp dword ptr [ebp - 0x48], eax -> je 0xda932 */
  display_assert((char *)0x00281960, (char *)0x00281eec, 776, 0);
  system_exit(0);
  /* cmp (int16_t)esi, -1 -> je 0xda96a */
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
