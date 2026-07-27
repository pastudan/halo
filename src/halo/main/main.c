#include <stdint.h>
/* Close all UI widgets and display the "damaged media" fatal error screen.
 *
 * Loads the "error_abort_to_dashboard_you_have_no_choice" widget by name,
 * asserts that it is a text box widget (type 1), sets its string_list_index
 * and the global error_string_index to 0x23, marks the widget as needing
 * a text update, then flushes input and enters the halt loop forever.
 * If the widget fails to load, logs an error and enters the halt loop
 * anyway. This function never returns. */
void display_error_damaged_media(void)
{
  void *widget;

  ui_widgets_close_all();
  widget = ui_widget_load_by_name_or_tag(
    "ui\\shell\\error\\error_abort_to_dashboard_you_have_no_choice", -1, 0, -1,
    -1, -1, -1);
  if (widget != NULL) {
    if (*(int16_t *)((char *)widget + 0xe) != 1) {
      display_assert("expected a text box widget",
                     "c:\\halo\\SOURCE\\interface\\ui_widget.c", 0x90f, 1);
      system_exit(-1);
    }
    *(int16_t *)((char *)widget + 0x40) = 0x23;
    *(uint8_t *)((char *)widget + 0x15) = 1;
    *(int16_t *)0x31e054 = 0x23;
    input_frame_end();
    main_halt_entry();
  }
  error(2, "failed to load '%s' widget",
        "ui\\shell\\error\\error_abort_to_dashboard_you_have_no_choice");
  input_frame_end();
  main_halt_entry();
}

/* Guard wrapper: if param_1 is nonzero, change the selected AI encounter
 * by calling ai_debug_change_selected_encounter with direction 0. */
void FUN_000ffe10(char param_1)
{
  if (param_1 != '\0') {
    ai_debug_change_selected_encounter(0);
  }
}

/* Guard wrapper: if param_1 is nonzero, change the selected AI actor
 * by calling ai_debug_change_selected_actor with direction 1 (next). */
void FUN_000ffe30(char param_1)
{
  if (param_1 != '\0') {
    ai_debug_change_selected_actor(1);
  }
}

/* Guard wrapper: if param_1 is nonzero, change the selected AI actor
 * by calling ai_debug_change_selected_actor with direction 0 (prev). */
void FUN_000ffe50(char param_1)
{
  if (param_1 != '\0') {
    ai_debug_change_selected_actor(0);
  }
}

/* Guard wrapper: if param_1 is nonzero, call FUN_00053890. */
void FUN_000ffe70(char param_1)
{
  if (param_1 != '\0') {
    FUN_00053890();
    return;
  }
}

/* Guard wrapper: if param_1 is nonzero, call FUN_0008f630. */
void FUN_000ffe90(char param_1)
{
  if (param_1 != '\0') {
    FUN_0008f630();
    return;
  }
}

/* set_game_connection (0xfff70) — readable C lift. */
void set_game_connection(short param)
{
  *(short *)0x46da0c = param;
}



short game_connection(void)
{
  return word_46DA0C;
}

void main_defer_map_map_change(void)
{
  main_change_map_name_pending = 0;
}

/* Return a pointer to the global multiplayer map name buffer (0x100050). */
char *main_get_multiplayer_map_name(void)
{
  return (char *)0x46db55;
}

/* Return the game variant index from the static table at 0x31fa90. */
int16_t main_get_difficulty(void)
{
  return *(int16_t *)0x31fa90;
}

static const short _game_connection_local = 0;

int __cdecl sort_desired_local_player_controllers(const void *a1,
                                                  const void *a2)
{
  short v1;
  short v2;

  v1 = *(short *)a1;
  v2 = *(short *)a2;
  if (v1 == -1) {
    if (v2 != -1)
      return 1;
  } else if (v2 == -1) {
    return -1;
  }
  if (v2 < v1)
    return 1;
  return (v2 <= v1) - 1;
}

void create_local_players(void)
{
  int i;
  int j;
  int player;
  int16_t gamepad_index;
  int16_t assigned_controllers[4];
  int16_t desired_controllers[4];
  int16_t default_controllers[4];

  if (main_globals.main_menu_scenario_loaded) {
    local_player_set_player_index(0, player_new(0, -1, 0, 0));
    return;
  }

  csmemset(assigned_controllers, -1, sizeof(assigned_controllers));
  csmemset(desired_controllers, -1, sizeof(desired_controllers));
  default_controllers[0] = 0;
  default_controllers[1] = 1;
  default_controllers[2] = 2;
  default_controllers[3] = 3;

  assert_halt(game_connection() == _game_connection_local);

  for (i = 0; i < player_spawn_count; i++) {
    gamepad_index = player_ui_get_single_player_local_player_controller(i);
    desired_controllers[i] = gamepad_index;
    if (gamepad_index == -1) {
      desired_controllers[i] = default_controllers[i];
    }

    assert_halt((desired_controllers[i] >= 0) &&
                (desired_controllers[i] < MAXIMUM_GAMEPADS));

    gamepad_index = desired_controllers[i];
    if (assigned_controllers[gamepad_index] != -1) {
      for (j = 0; j < MAXIMUM_GAMEPADS; j++) {
        if (assigned_controllers[j] == -1) {
          desired_controllers[i] = j;
          assigned_controllers[(int16_t)j] = j;
          break;
        }
      }
      assert_halt(j < MAXIMUM_GAMEPADS);
    } else {
      assigned_controllers[gamepad_index] = gamepad_index;
    }
  }

  qsort(desired_controllers, 4, 2, sort_desired_local_player_controllers);

  for (i = 0; i < player_spawn_count; i++) {
    gamepad_index = desired_controllers[i];
    assert_halt((gamepad_index >= 0) && (gamepad_index < MAXIMUM_GAMEPADS));
    player = player_new(0, -1, gamepad_index, 0);
    local_player_set_player_index(gamepad_index, player);
  }
}

void main_queue_map_name(char *map_name)
{
  if (map_name != 0) {
    csstrncpy(&byte_46DC55, map_name, 0xff);
    byte_46DA50 = 1;
  } else {
    byte_46DC55 = 0;
    byte_46DA50 = 0;
  }
}

/*
 * main_precache_map_tick - 0x1005d0
 *
 * Advances the map precaching state machine. Called periodically to poll
 * precache progress. If a precache is in progress and its status is 1
 * (complete), ends the precache. Then, if no precache is active, begins
 * precaching the queued map name and clears the queue flag.
 */
void main_precache_map_tick(void)
{
  float status;
  if (cache_files_precache_in_progress()) {
    if (cache_files_precache_map_status(&status) == 1) {
      cache_files_precache_map_end();
    }
  }
  if (!cache_files_precache_in_progress()) {
    cache_files_precache_map_begin(&byte_46DC55, false);
    byte_46DA50 = 0;
  }
}

void main_goto_main_menu(void)
{
  word_46DA40 = -1;
  byte_46DA28 = 0;
  main_menu_load_pending = 1;
}

void main_menu_precache_resources(void)
{
  scenario_t *scenario = global_scenario_get();
  if (scenario) {
    assert_halt(scenario->type == _scenario_type_main_menu);
    predicted_resources_precache(&scenario->unk_236);
  }
}

/*
 * main_reset_player_actions - 0x1006b0
 *
 * Resets the player action queue state by deleting all pending updates,
 * re-initializing the queue, and restarting the server update pipeline.
 * Called when closing a UI widget (ui_widget_close) and at the end of
 * each network client frame (network_game_client_end_frame).
 */
void main_reset_player_actions(void)
{
  update_server_delete();
  update_server_new();
  update_server_start();
}

/*
 * main_change_map_name_in_progress - 0x1006c0
 *
 * Returns true while the
 * map-change deadline tick at 0x46da34 is non-zero.
 */
bool main_change_map_name_in_progress(void)
{
  return *(uint32_t *)0x46da34 != 0;
}

/*
 * compute_window_bounds - 0x100910
 *
 * Computes viewport split bounds for a given player in a multi-player split
 * screen layout. Divides the screen area (from globals at 0x32565c/0x325660
 * for x and 0x32565e/0x325662 for y) into a grid, and assigns a sub-rectangle
 * to the player at player_index. Also computes a "full" bounds (a3) that
 * extends to the screen edges for border players.
 *
 * Calls an inlined grid dimension helper (originally at 0x1008a0) that takes
 * EBX as a register arg: finds the smallest (horiz, vert) grid such that
 * horiz * vert >= num_players.
 *
 * When num_players > horizontal_count * vertical_count, player 0 is given a
 * double-wide column (bVar5 flag set), and all other indices are shifted by 1.
 *
 * The "gap" value is 4 pixels when num_players >= 2, else 0.
 *
 * Confirmed:
 *  - Assert strings match: "player_index<num_players",
 *    "vertical_index>=0 && vertical_index<vertical_count",
 *    "horizontal_index>=0 && horizontal_index<horizontal_count".
 *  - Source path: "c:\\halo\\SOURCE\\main\\main.c" with lines 0x54f, 0x56e,
 * 0x56f.
 *  - All screen bounds are int16_t accessed via MOVSX.
 *  - Gap padding applied to inner edges; outer edges replaced by full viewport.
 */
void compute_window_bounds(int player_index, int num_players,
                           viewport_bounds_t *full_bounds,
                           viewport_bounds_t *split_bounds)
{
  int horizontal_count;
  int vertical_count;
  int total_slots;
  int vertical_index;
  int horizontal_index;
  int cell_height;
  int cell_width;
  int wide_cell_width;
  bool has_extra_wide_slot;
  uint16_t gap;

  /* --- assert: player_index < num_players --- */
  assert_halt(player_index < num_players);

  /* gap between sub-windows when more than 1 player */
  gap = (num_players < 2) ? 0 : 4;
  has_extra_wide_slot = false;

  /* --- inlined grid dimension helper (originally at 0x1008a0) ---
   * Finds the smallest (h, v) such that h * v >= num_players, with h <= v.
   * EBX = num_players (register arg in original). */
  {
    int h = 1, v = 1;
    assert_halt(num_players > 0);
    if (num_players > 1) {
      while (v * h < num_players) {
        if (h < v)
          h++;
        else {
          h = 1;
          v++;
        }
      }
    }
    horizontal_count = h;
    vertical_count = v;
  }

  total_slots = horizontal_count * vertical_count;

  /* When grid has spare slots, player 0 gets a double-wide column.
   * Other players shift by +1 so they skip player 0's extra slot. */
  if (total_slots - num_players != 0 && num_players <= total_slots) {
    if (player_index == 0) {
      has_extra_wide_slot = true;
    } else {
      player_index = player_index + 1;
    }
  }

  vertical_index = player_index / horizontal_count;
  horizontal_index = player_index - vertical_index * horizontal_count;

  assert_halt(vertical_index >= 0 && vertical_index < vertical_count);
  assert_halt(horizontal_index >= 0 && horizontal_index < horizontal_count);

  /* screen area globals (not in kb.json) */
  {
    int16_t scr_y0 = *(int16_t *)0x32565c;
    int16_t scr_y1 = *(int16_t *)0x325660;
    int16_t scr_x0 = *(int16_t *)0x32565e;
    int16_t scr_x1 = *(int16_t *)0x325662;

    cell_height = (int16_t)((scr_y1 - scr_y0) / vertical_count);
    cell_width = (int16_t)((scr_x1 - scr_x0) / horizontal_count);
    wide_cell_width = cell_width * (has_extra_wide_slot ? 2 : 1);

    /* compute per-player split bounds */
    split_bounds->x0 = (int16_t)(horizontal_index * wide_cell_width + scr_x0);
    split_bounds->x1 =
      (int16_t)((horizontal_index + 1) * wide_cell_width + scr_x0);
    split_bounds->y0 = (int16_t)(vertical_index * cell_height + scr_y0);
    split_bounds->y1 = (int16_t)((vertical_index + 1) * cell_height + scr_y0);

    /* copy to full bounds before gap adjustments */
    *full_bounds = *split_bounds;

    /* apply gap padding to inner edges of split bounds */
    split_bounds->x0 = split_bounds->x0 + (int16_t)(horizontal_index * gap);
    split_bounds->x1 =
      split_bounds->x1 - (int16_t)((horizontal_index == 0) * gap);
    split_bounds->y0 = split_bounds->y0 + (int16_t)(vertical_index * gap);
    split_bounds->y1 =
      split_bounds->y1 - (int16_t)((vertical_index == 0) * gap);

    /* replace outer edges of full bounds with full viewport bounds */
    if (horizontal_index == 0) {
      full_bounds->x0 = *(int16_t *)0x325656;
    }
    if ((has_extra_wide_slot ? 1 : 0) + horizontal_index + 1 ==
        horizontal_count) {
      full_bounds->x1 = *(int16_t *)0x32565a;
    }
    if (vertical_index == 0) {
      full_bounds->y0 = *(int16_t *)0x325654;
    }
    if (vertical_index + 1 == vertical_count) {
      full_bounds->y1 = *(int16_t *)0x325658;
    }
  }
}

/*
 * main_new_map - 0x100b40
 *
 * Loads a new map from the given game_options. Flushes input, attempts a
 * game_load, initializes the map if successful, creates local players and
 * starts game time, then fires the initial game pulse.
 *
 * Confirmed:
 *  - Calls input_flush (0xcf500), game_load (0xa76b0),
 * game_initialize_for_new_map (0xa7780), error_occurred (0x8f600),
 * create_local_players (0x1000d0), game_time_start (0xb5f40),
 * game_initial_pulse (0xa73c0).
 *  - On game_load failure: error(0, "game_load() failed.").
 *  - On error_occurred: error(0, "main_new_map() failed.").
 *  - Clears many main_globals flags after game_initial_pulse.
 *  - Copies 0x46da3f to 0x46da3e before clearing 0x46da3f.
 *  - Sets word at 0x46da40 to 0xffff (-1).
 *  - If byte at 0x46da54 is set, calls 0x1bfee0 (cache file precache).
 *  - Calls ui_widgets_disable_pause_game(0x1e) at exit.
 */
void main_new_map(game_options_t *game_options)
{
  input_flush();
  if (game_load(game_options)) {
    game_initialize_for_new_map();
  } else {
    error(0, "game_load() failed.");
  }

  if (error_occurred()) {
    error(0, "main_new_map() failed.");
  } else {
    create_local_players();
    game_time_start();
  }

  game_initial_pulse();

  /* Copy game_state_load_core_pending (0x46da3f) to 0x46da3e, then clear
   * many main_globals flags. Order matches original disassembly. */
  {
    uint8_t saved = *(uint8_t *)0x46da3f;
    uint8_t da54 = *(uint8_t *)0x46da54;

    *(uint8_t *)0x46da24 = 0;
    main_change_map_name_pending = 0;
    *(uint8_t *)0x46da26 = 0;
    *(uint8_t *)0x46da27 = 0;
    byte_46DA28 = 0;
    main_won_map_private_pending = 0;
    byte_46DA3B = 0;
    byte_46DA3C = 0;
    *(uint8_t *)0x46da3d = 0;
    *(uint8_t *)0x46da3f = 0;
    word_46DA40 = -1;
    game_state_load_core_pending = saved;

    if (da54 != 0) {
      cache_files_precache();
    }
  }

  ui_widgets_disable_pause_game(0x1e);
}

/*
 * main_change_map_name - 0x100c10
 *
 * Called from the main game loop when main_change_map_name_pending (0x46da25)
 * is set. Fades out the main menu music and UI over 1000 ms, then starts a
 * new game with the map name queued in the global map_name[255] buffer
 * (0x46da55).
 *
 * Confirmed:
 *  - Pending guard: main_globals.main_menu_scenario_loaded (0x46da42) == 1.
 *    If not pending, the function clears the timer deadline (0x46da34) and
 *    falls through to the timer-expired path.
 *  - Timer deadline stored as raw uint32 milliseconds at 0x46da34 (not in
 *    kb.json; used only by this function). Compared against
 *    unk_time_globals.unk_0 (uint32 ms ticker at 0x46d9e0).
 *  - Timer not-yet-started path (deadline == 0):
 *      - FUN_e46a0 returns DAT_0046cc86 (main-menu music-active flag).
 *      - If music is playing (== 1):
 *          deadline = current_ms + 1000
 *          FUN_e5a40(1000) — begin music fade-out over 1000 ms
 *          FUN_e3e10(1)    — enable UI widget
 *          FUN_e3c90(0.0f) — set rasterizer fade to 0 (transparent)
 *        MSVC interleaves: PUSH 0x3e8 (e5a40 arg), then PUSH 0x1 (e3e10 arg),
 *        then PUSH 0x0 (e3c90 arg), cleaned with a single ADD ESP,0xc.
 *      - Early-return if deadline not yet reached (current_ms < deadline).
 *  - Timer-running path (deadline != 0, deadline not yet reached):
 *      delta = deadline - current_ms (int32; add 4294967296.0f if negative to
 *      handle uint32 wrap).
 *      fade = 1.0f - (delta * 0.001f) [constants at 0x2533c8 and 0x255ef8].
 *      FUN_e3c90(fade) — update rasterizer blend.
 *  - Timer-expired (or not-pending) path:
 *      FUN_e3c90(-1.0f)     — set fade to -1.0f (0xbf800000)
 *      FUN_e4640()          — stop main-menu music
 *      FUN_e43d0(0)         — clear UI widget flag2
 *      main_globals.main_menu_scenario_loaded = 0  [cleared mid push-sequence]
 *      FUN_e3e10(0)         — disable UI widget
 *        MSVC interleaves: PUSH 0xbf800000 (e3c90), PUSH 0x0 (e43d0), PUSH 0x0
 *        (e3e10), cleaned with ADD ESP,0xc.
 *      If game_in_progress() and word_46DA0C == 0:
 *        - build game_options_t on the stack (0x10c bytes at [EBP-0x110]):
 *            game_options_new(&game_options)
 *            csstrncpy(game_options.map_name, map_name, 0xff)
 *            game_options.map_name[255] = 0   (explicit null-term)
 *            game_options.difficulty = global_difficulty_level
 *        - game_dispose_from_old_map()
 *        - game_precache_new_map(game_options.map_name, 1)
 *        - game_unload()
 *        - main_new_map(&game_options)
 *        - loop i=0 .. player_spawn_count-1: FUN_1c1c00(i) (save player
 * profile) Loop counter compared as signed int16 against player_spawn_count.
 *  - Deadline cleared to 0 unconditionally at function exit (0x46da34 = 0).
 *  - Float constants:
 *      0x4f800000 = 4294967296.0f (2^32, uint32 wrap correction)
 *      0x3a83126f = ~0.001f       (1/1000 ms-to-fraction scale, at 0x255ef8)
 *      0x3f800000 = 1.0f          (at 0x2533c8)
 *      0xbf800000 = -1.0f
 *
 * Inferred:
 *  - FUN_e46a0 = "main menu music is playing" — reads DAT_0046cc86.
 *  - FUN_e5a40 = begin UI fade / music fade-out (takes fade duration ms).
 *  - FUN_e3c90 = rasterizer_set_fade (takes float; stores raw bits to
 * DAT_0046cc4c).
 *  - FUN_e3e10 = ui_widget_set_flag (bool enable).
 *  - FUN_e4640 = stop_main_menu_music.
 *  - FUN_e43d0 = ui_widget_set_flag2 (bool).
 *  - FUN_1c1c00 = player_profile_save_level (local_player_index).
 *
 * Uncertain:
 *  - Exact semantics of FUN_e5a40, e3c90, e3e10, e43d0 — names are inferred
 *    from callee bodies and context; not confirmed by source strings.
 *  - Whether the note "// FIXME: Merge adjacent globals" on main_globals_t
 *    means 0x46da42 has dual use here vs. in main_menu_load.
 */
void main_change_map_name(void)
{
  game_options_t game_options;
  int delta;
  int i;

  typedef void(__cdecl * fn_ui_fade_start_t)(int duration_ms);
  typedef void(__cdecl * fn_set_fade_t)(float fade);
  typedef void(__cdecl * fn_set_widget_flag2_t)(bool enable);
  typedef void(__cdecl * fn_save_player_level_t)(int local_player_index);

  if (main_globals.main_menu_scenario_loaded) {
    if (*(int *)0x46da34 == 0) {
      /* music not yet fading: check if music is still playing */
      if (ui_widget_get_attract_mode_flag()) {
        /* set deadline and kick off the 1000 ms fade sequence */
        *(uint32_t *)0x46da34 = (uint32_t)unk_time_globals.unk_0 + 1000;
        /* MSVC interleaved pre-push: PUSH 0x3e8, PUSH 0x1, PUSH 0x0 */
        ((fn_ui_fade_start_t)0xe5a40)(1000);
        ui_widget_set_events_suppressed(1);
        ((fn_set_fade_t)0xe3c90)(0.0f);
      }
    } else {
      /* compute remaining time and update the rasterizer blend */
      delta = (int)(*(uint32_t *)0x46da34 - (uint32_t)unk_time_globals.unk_0);
      {
        float flt_delta = (float)delta;
        if (delta < 0) {
          flt_delta = flt_delta + 4294967296.0f; /* uint32 wrap correction */
        }
        /* fade = 1.0f - remaining_ms * (1/1000) */
        ((fn_set_fade_t)0xe3c90)(1.0f - flt_delta * *(float *)0x255ef8);
      }
    }
    /* bail out if deadline has not been reached */
    if ((uint32_t)unk_time_globals.unk_0 < *(uint32_t *)0x46da34) {
      return;
    }
  } else {
    /* not pending: clear deadline and fall through to clean-up path */
    *(int *)0x46da34 = 0;
  }

  /* timer expired (or was never pending): finalize fade and start new map */
  /* MSVC interleaved pre-push: PUSH 0xbf800000, PUSH 0x0, PUSH 0x0 */
  ((fn_set_fade_t)0xe3c90)(-1.0f); /* 0xbf800000 */
  ui_widget_stop_attract_mode();
  ((fn_set_widget_flag2_t)0xe43d0)(0);
  main_globals.main_menu_scenario_loaded = 0;
  ui_widget_set_events_suppressed(0);

  if (game_in_progress() && word_46DA0C == 0) {
    /* initialize game_options from queued map name and difficulty */
    game_options_new(&game_options);
    csstrncpy(game_options.map_name, map_name, 0xff);
    game_options.map_name[255] = 0; /* explicit null-terminator */
    game_options.difficulty = global_difficulty_level;

    game_dispose_from_old_map();
    game_precache_new_map(game_options.map_name, 1);
    game_unload();
    main_new_map(&game_options);

    /* save level progress for each local player (signed int16 compare) */
    for (i = 0; (int16_t)i < player_spawn_count; i++) {
      ((fn_save_player_level_t)0x1c1c00)(i);
    }
  }

  *(int *)0x46da34 = 0;
}

/*
 * main_skip_private - 0x100de0
 *
 * Confirmed:
 *  - Reads/clears two adjacent globals:
 *      0x46da4a = int16_t skip counter (how many ticks to fast-forward)
 *      0x46da49 = bool main_skip_private_pending (cleared on both paths)
 *  - Guard: counter must be > 0 AND cinematic_in_progress() must be true.
 *    If not, emits error(2, "manual skipping doesn't work outside of
 *    cinemtatic start/stop...") [sic — original typo preserved in binary].
 *  - On success: saves current game speed via game_time_get_speed(), sets
 *    speed to 1.0f, then loops calling game_time_update(1/30.0f) once per
 *    tick while the counter is > 0 (counter decremented inside loop).
 *  - After the loop, decrements the counter once more (goes to -1), restores
 *    the saved speed via game_time_set_speed(saved_speed), then zeroes both
 *    globals.
 *  - Float constant 0x3d088889 = ~0.0333f (1/30 sec, one game tick at 30 Hz).
 *  - Float constant 0x3f800000 = 1.0f.
 *  - FSTP/PUSH round-trip: saved speed is stored as float (4 bytes) on the
 *    stack [EBP-4] and reloaded into EAX before being pushed as a raw dword.
 */
void main_skip_private(void)
{
  float saved_speed;
  int16_t *skip_count = (int16_t *)0x46da4a;

  if (*skip_count > 0 && cinematic_in_progress()) {
    saved_speed = game_time_get_speed();
    game_time_set_speed(1.0f);
    while (*skip_count > 0) {
      (*skip_count)--;
      game_time_update(0.03333333507180214f);
    }
    (*skip_count)--;
    game_time_set_speed(saved_speed);
    *skip_count = 0;
    main_skip_private_pending = 0;
    return;
  }
  error(2, "manual skipping doesn't work outside of cinemtatic start/stop...");
  *skip_count = 0;
  main_skip_private_pending = 0;
}

/*
 * main_save_map_private - 0x100eb0
 *
 * Confirmed:
 *  - Returns immediately if game_time_get_paused() (CALL 0xb5c30; JNZ out).
 *  - 0x46da29 (byte): save-in-progress flag. When zero the game is NOT
 *    actively trying to save; when non-zero a save attempt is underway.
 *  - 0x46da2a (byte): secondary flag checked only when the retry counter
 *    (0x46da30) has exceeded 0xef ticks.
 *  - 0x46da2c (dword): cooldown counter. Decremented each tick; save is only
 *    attempted when it falls to <= 0. Reset to 10 after each attempt.
 *  - 0x46da30 (dword): total-ticks counter. Incremented on every call while
 *    the save-pending flag (0x46da29) is set. Used to detect a hung save.
 *  - 0x46da38 (int16_t): consecutive-success counter for game_safe_to_save().
 *    Cleared to 0 on failure, incremented on success. When the original value
 *    reaches >= 3 (i.e. three or more consecutive successes), the save is
 *    triggered (BL set; hud_autosave + game_state_save_pending armed).
 *  - 0x46da28 (byte): cleared to 0 whenever the save attempt is resolved
 *    (success, abort, or overflow). Already in kb.json as byte_46DA28.
 *  - 0x46da2b = game_state_save_pending: set to 1 to arm the save, then the
 *    main loop (0x100eb0 caller) handles the actual game_state_save call.
 *  - CALL 0xd0db0 = hud_autosave(int16_t): notifies HUD; arg is 1.
 *  - CALL 0xff4d0 = local logging helper (int, const char *, ...): same cast
 *    pattern used in game_state.c and cheats.c.
 *  - debug_game_save (0x46e002): when set, enables the "unsafe save" path
 *    (triggers autosave even when 0x46da29==0) and logs the "gave up" message
 *    on overflow instead of silently aborting.
 *  - Overflow path (0x46da30 >= 0xf0 AND 0x46da2a != 0): clears byte_46DA28
 *    and returns without triggering a save regardless of debug_game_save.
 *    With debug_game_save set, logs "gave up trying to save" first.
 *
 * Inferred:
 *  - 0x46da29 is probably "main_save_map_private_pending" or similar — the
 *    name is not confirmed from strings.
 *  - 0x46da2a is probably a secondary "abort on overflow" sub-flag.
 *  - 0x46da2c is a retry-cooldown tick counter; 10-tick interval inferred.
 *  - 0x46da30 is a total-attempt tick counter; 0xf0 = 240 ticks ceiling.
 *  - 0x46da38 is a run-of-good-frames counter gating the actual save trigger.
 *
 * Uncertain:
 *  - Exact semantic names for 0x46da29, 0x46da2a, 0x46da2c, 0x46da30,
 *    0x46da38 — all accessed as hardcoded addresses since not in kb.json.
 */
void main_save_map_private(void)
{
  int orig_ticks;
  int orig_cooldown;
  int16_t orig_safe_count;
  bool trigger;

  if (game_time_get_paused()) {
    return;
  }

  trigger = false;

  if (*(uint8_t *)0x46da29 == 0) {
    /* Not in a pending-save state: only fire if debug_game_save forces it. */
    if (debug_game_save) {
      ((void (*)(int, const char *, ...))0xff4d0)(0, "unsafe save");
    }
    /* Fall through to shared trigger tail. */
  } else {
    /* Increment total-ticks counter and check for overflow. */
    orig_ticks = *(int *)0x46da30;
    *(int *)0x46da30 = orig_ticks + 1;

    if (orig_ticks >= 0xf0 && *(uint8_t *)0x46da2a != 0) {
      /* Hung for too long — abort the save. */
      if (debug_game_save) {
        ((void (*)(int, const char *, ...))0xff4d0)(0,
                                                    "gave up trying to save");
      }
      byte_46DA28 = 0;
      return;
    }

    /* Decrement cooldown counter; only attempt save when it reaches <= 0. */
    orig_cooldown = *(int *)0x46da2c;
    *(int *)0x46da2c = orig_cooldown - 1;
    if (orig_cooldown > 0) {
      return;
    }

    /* Poll game_safe_to_save(); track consecutive successes. */
    if (game_safe_to_save()) {
      orig_safe_count = *(int16_t *)0x46da38;
      *(int16_t *)0x46da38 = orig_safe_count + 1;
      if (orig_safe_count >= 3) {
        trigger = true;
      }
    } else {
      *(int16_t *)0x46da38 = 0;
    }

    /* Reset cooldown regardless of whether the save fires. */
    *(int *)0x46da2c = 10;

    if (!trigger) {
      return;
    }
  }

  /* Shared trigger tail: arm save and clear pending flag. */
  hud_autosave(1);
  game_state_save_pending = 1;
  byte_46DA28 = 0;
}

/*
 * main_won_map_private - 0x101040
 *
 * Confirmed:
 *  - Sets main_menu_load_pending (0x46da43) = 1.
 *  - Clears main_won_map_private_pending (0x46da3a) = 0.
 *  - Calls 0x1006f0(&map_name) → returns a short level index (0-8) for
 *    recognized map names, or -1 for unrecognized. Source path visible in
 *    the callee: "c:\\halo\\SOURCE\\saved games\\player_profile.c". The
 *    callee strips the path prefix (FUN_8de70 = csstrncpy-like), lowercases
 *    (FUN_8d9a0), then does up to 10 strstr comparisons for the 10 SP
 *    level names. Returns 0-8 for a known level; the 10th path returns 9
 *    but the expression `(-(uint)(pcVar1 != 0) & 10) - 1` maps it to 9.
 *  - Zero-extends the 16-bit result (XOR EDI,EDI; MOV DI,AX), then
 *    increments: level_index = (uint16_t)(result) + 1. If (short)level_index
 *    >= 10, level_index is set to -1 (OR EDI,0xffffffff).
 *  - Loops i = 0 .. player_spawn_count-1, calling 0x1c1cc0(i) each
 *    iteration. Callee source: "player_profile.c" — saves level completion
 *    for each local player's profile.
 *  - Calls 0xe4420(level_index) to trigger the inter-level transition:
 *    level_index == -1 → main menu; -1 < level_index < 10 → load next
 *    level; else → "unknown level" error + FUN_100620 (main_menu fallback).
 *  - Loop counter compared as signed 16-bit (CMP SI, word[0x31fa94]).
 */
void main_won_map_private(void)
{
  uint16_t map_level;
  int level_index;
  int i;

  typedef uint16_t(__cdecl * fn_map_to_level_t)(char *map_name);
  typedef void(__cdecl * fn_save_player_level_t)(int local_player_index);
  typedef void(__cdecl * fn_level_transition_t)(int level_index);

  main_menu_load_pending = 1;
  main_won_map_private_pending = 0;

  /* map the current map name to a 0-based level index; unrecognized = -1 */
  map_level = ((fn_map_to_level_t)0x1006f0)(map_name);
  level_index = (int)(map_level + 1);
  if ((int16_t)level_index >= 10) {
    level_index = -1;
  }

  /* record level completion in each local player's saved profile */
  for (i = 0; (int16_t)i < player_spawn_count; i++) {
    ((fn_save_player_level_t)0x1c1cc0)(i);
  }

  /* trigger level transition or return to main menu */
  ((fn_level_transition_t)0xe4420)(level_index);
}

/*
 * main_frame_rate_debug - 0x101130
 *
 * Confirmed:
 *  - No arguments; void return. cdecl frame, saves EBX/ESI/EDI.
 *  - Enable flag at 0x46e003 (bool, unnamed): when zero the function is a
 *    no-op (returns immediately). Not in kb.json.
 *  - State initialized/reset via flag at 0x46e391 (bool active). On first
 *    call with active==0 and enable==0, exits early. On first call with
 *    active==1 but enable==0, clears the entire state block and exits.
 *  - Frame-time history ring-buffer: float[8] at 0x46e36c (32 bytes).
 *    Current slot index at 0x46e38e (byte, wraps mod 8). Slow-frame bitmask
 *    at 0x46e38c (uint16_t, one bit per slot). Initialized with csmemset.
 *  - Slow-frame threshold: flt_46DA08 (current frame seconds) compared
 *    against double constant 0.036 at 0x28b430 (= ~1/27.78s ≈ 27.8 fps
 *    threshold) via FCOMP double ptr — decompiler shows float cast but
 *    disasm confirms double operand.
 *  - Mask bit set when frame is SLOW (> threshold), cleared when fast.
 *  - Trigger condition: all 8 slots slow (bitmask == 0xff), has-triggered
 *    flag (0x46e38f) == 0. Writes a save-core file and an init .txt log.
 *  - After trigger, sets 0x46e38f=1. Cleared back to 0 once 60 consecutive
 *    fast-frame passes accumulate (counter at 0x46e390, threshold 0x3c=60).
 *  - File helpers called directly by address; not in kb.json:
 *      0x1ba1f0: returns scenario/map name pointer (field+0x10 of globals)
 *      0x19b0d0: strips path prefix (strrchr basename)
 *      0x1d051d: fills TIME_FIELDS-like struct (KeQuerySystemTime +
 *                RtlTimeToTimeFields)
 *      0x1d90f0: internal sprintf variant (not csprintf)
 *      0x1d9e59: __fsopen wrapper (fopen with share mode 0x40)
 *      0x1d98ad: _fwprintf
 *      0x1d9bd2: _fflush
 *      0x1d9dac: _fclose
 *  - String "d:\%s_init.txt" and file modes "r"/"wt"/"a+t" confirm
 *    log-file append behavior.
 *
 * Inferred:
 *  - 0x46e003 = "debug_frame_rate_enable" or similar console/debug flag.
 *  - The 8-slot bitmask going all-1s (0xff) triggers "we're running slow"
 *    recording; 60 consecutive fast frames clears the trigger latch.
 *  - game_state_save_core writes a binary game-state snapshot whose name
 *    encodes the timestamp.
 *
 * Uncertain:
 *  - Exact semantic name of 0x46e003. Could be "profile_frame_rate" or a
 *    different per-build debug flag.
 *  - TIME_FIELDS field ordering relied on (Year/Month/Day/Hour/Min/Sec/Ms).
 *    The sprintf arg order in disasm: Month, Hour, Year, Minute, Second, Ms.
 */
void main_frame_rate_debug(void)
{
  /* frame-time history and state live at fixed addresses, not in kb.json */
  float *frame_times = (float *)0x46e36c; /* float[8] ring buffer */
  uint16_t *slow_mask = (uint16_t *)0x46e38c; /* bitmask: 1=slow slot */
  uint8_t *slot_idx = (uint8_t *)0x46e38e; /* current ring slot 0-7 */
  uint8_t *triggered = (uint8_t *)0x46e38f; /* has-triggered latch */
  uint8_t *fast_count = (uint8_t *)0x46e390; /* consecutive fast frames */
  uint8_t *active = (uint8_t *)0x46e391; /* state initialized flag */
  bool *enable = (bool *)0x46e003; /* debug enable flag */

  /* slow-frame threshold: ~27.8 fps (double, NOT float — disasm confirms) */
  static const double slow_threshold = 0.036; /* 0x28b430 */

  /* sizeof TIME_FIELDS fields (8x int16_t) */
  int16_t tf[8]; /* [0]=Year [1]=Month [2]=Day [3]=Hour [4]=Min [5]=Sec
                    [6]=Ms [7]=Weekday — layout per RtlTimeToTimeFields */

  char core_name[256]; /* [EBP-0x214..-0x115] */
  char init_path[256]; /* [EBP-0x114..-0x15] */

  uint32_t idx;
  uint32_t bit;
  char *map_name;
  void *fp;

  typedef char *(__cdecl * fn_get_scenario_name_t)(int scenario_idx);
  typedef char *(__cdecl * fn_basename_t)(char *path);
  typedef void(__cdecl * fn_get_time_t)(int16_t * tf_out);
  typedef int(__cdecl * fn_sprintf_t)(char *buf, const char *fmt, ...);
  typedef void *(__cdecl * fn_fopen_t)(const char *path, const char *mode);
  typedef int(__cdecl * fn_fwprintf_t)(void *fp, const wchar_t *fmt, ...);
  typedef int(__cdecl * fn_fflush_t)(void *fp);
  typedef int(__cdecl * fn_fclose_t)(void *fp);

  if (*active != 0) {
    if (*enable != 0)
      goto do_update;
    /* active but no longer enabled — reset state */
    *active = 0;
    csmemset(frame_times, 0, 0x20);
    *slow_mask = 0;
    *slot_idx = 0;
    *triggered = 0;
    *fast_count = 0;
    *active = 0;
  }

  if (*enable == 0)
    return;

do_update:
  /* store current frame time in ring slot */
  frame_times[*slot_idx] = flt_46DA08;

  /* update slow-frame bitmask for this slot */
  bit = (uint32_t)(1 << (*slot_idx & 0x1f));
  if (flt_46DA08 <= (float)slow_threshold) {
    *slow_mask = (uint16_t)(*slow_mask & ~(uint16_t)bit);
  } else {
    *slow_mask = (uint16_t)(*slow_mask | (uint16_t)bit);
  }

  /* advance ring index mod 8 */
  idx = (uint32_t)(int8_t)(*slot_idx + 1) & 0x80000007u;
  if ((int32_t)idx < 0)
    idx = (idx - 1 | 0xfffffff8u) + 1;
  *slot_idx = (uint8_t)idx;

  *active = 1;

  if (*triggered == 0) {
    /* first trigger: all 8 slots must be slow (bitmask 0xff) */
    if (*slow_mask == 0xff) {
      /* get scenario/map name, strip path prefix */
      map_name = ((fn_basename_t)0x19b0d0)(
        ((fn_get_scenario_name_t)0x1ba1f0)(global_scenario_index));

      /* get current time fields */
      ((fn_get_time_t)0x1d051d)(tf);

      /* build core snapshot filename:
       * <map>_slow_<mo>_<hr>_<yr>_<min>_<sec>_<ms>.bin */
      ((fn_sprintf_t)0x1d90f0)(core_name, "%s_slow_%d_%d_%d_%d_%d_%d.bin",
                               map_name, (int)(uint16_t)tf[1], /* Month */
                               (int)(uint16_t)tf[3], /* Hour */
                               (int)(uint16_t)tf[0], /* Year */
                               (int)(uint16_t)tf[4], /* Minute */
                               (int)(uint16_t)tf[5], /* Second */
                               (int)(uint16_t)tf[6]); /* Milliseconds */

      /* save binary game-state core */
      game_state_save_core(core_name);

      /* build init.txt path: d:\<map>_init.txt */
      ((fn_sprintf_t)0x1d90f0)(init_path, "d:\\%s_init.txt", map_name);

      /* open file: try "r" first to detect if it exists */
      fp = ((fn_fopen_t)0x1d9e59)(init_path, "r");
      if (fp == (void *)0) {
        /* new file: create with "wt" and write map_name line */
        fp = ((fn_fopen_t)0x1d9e59)(init_path, "wt");
        ((fn_fwprintf_t)0x1d98ad)(fp, L"map_name %s\n", map_name);
      } else {
        /* existing file: close "r" handle, reopen in append mode */
        ((fn_fclose_t)0x1d9dac)(fp);
        fp = ((fn_fopen_t)0x1d9e59)(init_path, "a+t");
      }

      /* append core snapshot filename */
      ((fn_fwprintf_t)0x1d98ad)(fp, L";core_load_name_at_startup %s\n",
                                core_name);
      ((fn_fflush_t)0x1d9bd2)(fp);
      ((fn_fclose_t)0x1d9dac)(fp);

      *triggered = 1;
    }
  } else if (*slot_idx == 0) {
    /* latch active: check if ring just completed a full pass */
    if (*slow_mask != 0) {
      /* still slow frames in window — reset fast counter */
      *fast_count = 0;
      return;
    }
    /* all frames fast this pass */
    *fast_count = *fast_count + 1;
    if (';' < *fast_count) { /* 0x3b=59 threshold: >59 = 60th pass */
      *fast_count = 0;
      *triggered = 0;
      return;
    }
  }
}

/*
 * main_update_time - 0x1013d0
 *
 * Confirmed:
 *  - Reads system_milliseconds() at entry and exit, and tracks both the raw
 *    millisecond delta (unk_time_globals.unk_0) and the hardware flip count
 *    timeline (unk_time_globals.unk_8 / unk_16 / unk_24 / unk_32).
 *  - Selects the larger of the previous target time (unk_8) and the most
 *    recent presented time (unk_32) before adjusting the next frame target.
 *  - When 0x32568d is clear, uses a 33 ms software frame cap:
 *      - clears 0x46dd9a
 *      - if ms_delta < 33, brackets an optional Sleep(33 - ms_delta) with
 *        0x91b70 / 0x91ba0 markers
 *      - else reports the overshoot to 0x8f8c0(ms_delta - 33)
 *  - When 0x32568d is set, optional pacing debug/control is driven by:
 *      - 0x325690 (requested rate; zero treated as 30)
 *      - 0x46dd96 (current divisor), 0x46dd98 (requested divisor)
 *      - failure counters at 0x46dd9e..0x46dda6 (5 x int16)
 *      - target-history slots at 0x46ddb0..0x46ddd0 (5 x int64)
 *      - debug buffer at 0x46ddfc
 *    The control loop evaluates divisors 5..1 (12/15/20/30/60 fps), updates
 *    the failure history, may keep/restore/fail-down the divisor, then adds
 *    the chosen divisor to the selected target time.
 *  - Frame seconds written to flt_46DA08 come from:
 *      - ms delta * 0.001f when 0x32568d is clear (with uint32 wrap fix), or
 *      - (target - previous_target) * (1/60) when 0x32568d is set.
 *  - If main_globals_movie is non-NULL (overlaps smaller timing globals at
 *    0x46da10 / 0x46da20), the computed frame step is overridden by the float
 *    at 0x46da20.
 *  - Non-movie frame seconds are clamped to [0, 1]. In local games
 *    (word_46DA0C == 0), extra caps apply:
 *      - normal path: max 1/15 sec (0x3d888889)
 *      - debug_game_save path: max 1/30 sec (0x3d088889)
 *  - Exit writes:
 *      unk_time_globals.unk_0  = end_ms
 *      unk_time_globals.unk_8  = chosen_target
 *      flt_46DA08              = frame_seconds
 *      0x8f870(frame_seconds)
 *      unk_time_globals.unk_16 = qword_325678
 *
 * Inferred:
 *  - 0x32568d is the per-frame pacing/throttle enable.
 *  - 0x32568e gates the adaptive divisor debugging/control path.
 *  - 0x325690 is a requested presentation rate value that maps to divisors
 *    1..5 via 60 / requested_rate (with 0 meaning 30 fps -> divisor 2).
 *  - The pooled strings "wt" and "dn" used in the debug trace likely mean
 *    "wait" and "down", but the exact abbreviations are left as raw string
 *    references rather than renamed semantics.
 *
 * Uncertain:
 *  - Exact symbolic names for 0x32568d/0x32568e/0x325690, 0x46dd96/0x46dd98,
 *    0x46dd9e..0x46ddd0, and 0x46dd9a.
 *  - Exact semantics of 0x8f870 and 0x8f8c0 beyond the observed global writes.
 *  - No register-argument (``) ABI edges were found in this function or
 *    its caller path; the reverse-thunk audit for this lift found only cdecl /
 *    stdcall calls.
 */
void main_update_time(void)
{
  int end_ms;
  int ms_delta;
  int buffer_length;
  int16_t requested_rate;
  int16_t desired_divisor;
  int16_t chosen_divisor;
  int16_t elapsed_game_ticks;
  int slot;
  int64_t chosen_target;
  int64_t short_target;
  int64_t present_target;
  int64_t previous_target;
  float frame_seconds;
  char *debug_buffer;
  int16_t *failure_counts;
  int64_t *target_history;

  typedef char *(__cdecl * fn_csstrcpy_t)(char *destination,
                                          const char *source);
  typedef void(__cdecl * fn_store_frame_seconds_t)(float frame_seconds);
  typedef void(__cdecl * fn_store_frame_overshoot_t)(int overshoot_ms);
  typedef void(__cdecl * fn_rdtsc_marker_t)(void);
  typedef void(__stdcall * fn_sleep_t)(int milliseconds);

  end_ms = system_milliseconds();
  previous_target = unk_time_globals.unk_8;
  present_target = unk_time_globals.unk_32;
  chosen_target = present_target;
  if (present_target < previous_target) {
    chosen_target = previous_target;
  }

  if (*(char *)0x32568d == '\0') {
    ms_delta = end_ms - (int)unk_time_globals.unk_0;
    *(char *)0x46dd9a = 0;
    if (ms_delta < 0x21) {
      ((fn_rdtsc_marker_t)0x91b70)();
      if (*(char *)0x31fa96 != '\0') {
        ((fn_sleep_t)0x1d0362)(0x21 - ms_delta);
      }
      ((fn_rdtsc_marker_t)0x91ba0)();
    } else {
      ((fn_store_frame_overshoot_t)0x8f8c0)(ms_delta - 0x21);
    }
  } else {
    debug_buffer = (char *)0x46ddfc;
    failure_counts = (int16_t *)0x46dd9e;
    target_history = (int64_t *)0x46ddb0;

    ((fn_csstrcpy_t)0x8dff0)(debug_buffer, "");
    if (*(char *)0x31fa96 != '\0' && *(int16_t *)0x325690 >= 0) {
      requested_rate = *(int16_t *)0x325690;
      if (requested_rate == 0) {
        requested_rate = 0x1e;
      }

      desired_divisor = (int16_t)(0x3c / requested_rate);
      chosen_divisor = desired_divisor;
      *(int16_t *)0x46dd98 = desired_divisor;

      if (*(char *)0x32568e != '\0') {
        int16_t best_divisor;
        int16_t current_divisor;

        elapsed_game_ticks = game_time_get_elapsed();
        current_divisor = *(int16_t *)0x46dd96;
        short_target = (int64_t)(int16_t)(uint16_t)chosen_target;
        best_divisor = 5;

        snprintf(debug_buffer, 0x200,
                 "last%6I64d init%6I64d achv%6I64d pres%6I64d g%d cur%d... ",
                 unk_time_globals.unk_8, unk_time_globals.unk_16,
                 unk_time_globals.unk_24, unk_time_globals.unk_32,
                 (int)elapsed_game_ticks, (int)current_divisor);

        for (slot = 5; slot > 0; slot--) {
          int index;
          int16_t failure_count;
          int16_t clamped_failure_count;
          int16_t target_age;
          int16_t slot_bucket;
          bool ignore_failure;
          const char *label;
          int64_t target_age_raw;

          index = slot - 1;
          failure_count = failure_counts[index];
          clamped_failure_count = failure_count;
          if (clamped_failure_count > 99) {
            clamped_failure_count = 99;
          }

          target_age_raw = short_target - target_history[index];
          if (target_age_raw > 99) {
            target_age = 99;
          } else {
            target_age = (int16_t)target_age_raw;
          }

          slot_bucket = (int16_t)((slot + 1) / 2);
          ignore_failure = false;
          if ((int16_t)((current_divisor + 1) / 2) > slot_bucket &&
              slot_bucket >= (int16_t)(current_divisor / 2) &&
              elapsed_game_ticks > slot_bucket) {
            ignore_failure = true;
          }

          if (unk_time_globals.unk_24 >= unk_time_globals.unk_16 + slot) {
            if (chosen_target >= target_history[index] + 0xf) {
              label = (const char *)0x28b48c;
              if (failure_counts[index] < 4) {
                label = (const char *)0x28b3fc;
              }

              buffer_length = csstrlen(debug_buffer);
              snprintf(debug_buffer + buffer_length, 0x200 - buffer_length,
                       "(%s%2d/%2d) ", label, (int)clamped_failure_count,
                       (int)target_age);
            } else {
              failure_counts[index] = 0;

              buffer_length = csstrlen(debug_buffer);
              snprintf(debug_buffer + buffer_length, 0x200 - buffer_length,
                       "(ok   %2d) ", (int)target_age);
            }
          } else {
            if (ignore_failure) {
              label = "ignor";
            } else {
              failure_counts[index] = failure_count + 1;
              target_history[index] = chosen_target;
              label = "fail ";
            }

            buffer_length = csstrlen(debug_buffer);
            snprintf(debug_buffer + buffer_length, 0x200 - buffer_length,
                     "(%s%2d) ", label, (int)clamped_failure_count);
          }

          if (desired_divisor <= slot && failure_counts[index] < 4) {
            best_divisor = (int16_t)slot;
          }
        }

        if (best_divisor == 0) {
          requested_rate = 999;
        } else {
          requested_rate = (int16_t)(0x3c / best_divisor);
        }

        if (*(int16_t *)0x46dd96 < best_divisor) {
          buffer_length = csstrlen(debug_buffer);
          snprintf(debug_buffer + buffer_length, 0x200 - buffer_length,
                   " FAILDOWN %d", (int)requested_rate);
        } else if (best_divisor < *(int16_t *)0x46dd96) {
          buffer_length = csstrlen(debug_buffer);
          snprintf(debug_buffer + buffer_length, 0x200 - buffer_length,
                   " RESTORE  %d", (int)requested_rate);
        } else {
          buffer_length = csstrlen(debug_buffer);
          snprintf(debug_buffer + buffer_length, 0x200 - buffer_length,
                   " MAINTAIN %d", (int)requested_rate);
        }

        buffer_length = csstrlen(debug_buffer);
        snprintf(debug_buffer + buffer_length, 0x200 - buffer_length,
                 " des %d targ%6I64d", (int)requested_rate,
                 chosen_target + best_divisor);

        chosen_divisor = best_divisor;
      }

      chosen_target += chosen_divisor;
      *(int16_t *)0x46dd96 = chosen_divisor;
    }
  }

  end_ms = system_milliseconds();
  if (chosen_target < qword_325678) {
    chosen_target = qword_325678;
  }

  if (*(char *)0x32568d == '\0') {
    frame_seconds = (float)(end_ms - (int)unk_time_globals.unk_0);
    if (end_ms - (int)unk_time_globals.unk_0 < 0) {
      frame_seconds = frame_seconds + 4294967296.0f;
    }
    frame_seconds = frame_seconds * 0.001000000047497451f;
  } else {
    frame_seconds =
      (float)(chosen_target - unk_time_globals.unk_8) * 0.01666666753590107f;
  }

  if (main_globals_movie == NULL) {
    if (frame_seconds < 0.0f) {
      frame_seconds = 0.0f;
    } else if (frame_seconds > 1.0f) {
      frame_seconds = 1.0f;
    }

    if (word_46DA0C == 0) {
      if (!debug_game_save) {
        if (frame_seconds > 0.06666667014360428f) {
          frame_seconds = 0.06666667014360428f;
        }
      } else if (frame_seconds > 0.03333333507180214f) {
        frame_seconds = 0.03333333507180214f;
      }
    }
  } else {
    frame_seconds = *(float *)0x46da20;
  }

  unk_time_globals.unk_0 = end_ms;
  unk_time_globals.unk_8 = chosen_target;
  flt_46DA08 = frame_seconds;
  ((fn_store_frame_seconds_t)0x8f870)(frame_seconds);
  unk_time_globals.unk_16 = qword_325678;
}

/*
 * main_rasterizer_throttle - 0x101970
 *
 * Confirmed:
 *  - Reads the hardware vblank/flip counter pair (qword_325678 at
 *    0x325678/0x32567c) and writes a "frame start" snapshot
 *    (qword_325678 + 1) into unk_time_globals.unk_24 (0x46d9f8/0x46d9fc).
 *  - Two enable flags gate framerate control:
 *      0x31fa96 = master rasterizer vblank enable
 *      0x32568d = per-frame enable (cleared to 0 on 1000 ms timeout)
 *  - When enabled, waits in a spin loop for the flip counter to reach
 *    unk_time_globals.unk_8 - 1 (0x46d9e8/0x46d9ec). Bracketed by
 *    RDTSC calls at 0x91b70 (start) and 0x91ba0 (end). During the wait,
 *    if cache_files_precache_in_progress (0x1bc6b0) returns true, the
 *    loop calls 0x1d0362(1) (stdcall sleep/yield) each iteration.
 *  - After the wait (or if throttle was skipped), stores a "frame end"
 *    snapshot (qword_325678 + 1) into unk_time_globals.unk_32
 *    (0x46da00/0x46da04).
 *  - Computes frames elapsed since last vblank target as a signed int64
 *    (frame_end - unk_8), clamped to [0, 0x7fff] → int16_t frames_delta.
 *    Captures synced = (0x46dd96 == 0x46dd98) at frame-end snapshot time.
 *  - Appends a debug timing string to the buffer at 0x46ddfc using
 *    csstrlen (0x8df60, called twice due to MSVC pre-push interleaving)
 *    and snprintf (0x1d9179). Format: "%6I64d(targ%6I64d %s%2d)" with
 *    entry flip count, target (unk_8), label, and elapsed ticks.
 *    Label is "THROTTLE" if we waited, "SYNCED  " if on-time, else
 *    "LAPSED  ".
 *  - Writes 0x46dd9a (frame-pacing active flag): 1 iff 0x46dd96 > 0 &&
 *    frames_delta == 0, else 0.
 *  - Calls 0x8f880(frames_delta, synced, debug_buf) to store per-frame
 *    profile counters.
 */
void main_rasterizer_throttle(void)
{
  /* snapshot of hardware flip counter pair at function entry */
  unsigned int entry_flip_lo;
  int entry_flip_hi;
  /* target: unk_time_globals.unk_8 - 1 (64-bit) */
  unsigned int target_lo;
  int target_hi;
  /* system_milliseconds() at start of wait loop (timeout reference) */
  unsigned int ms_start;
  /* true if we actually entered the vblank wait */
  bool did_throttle;
  /* return of cache_files_precache_in_progress */
  bool precache_in_progress;
  /* frames elapsed since vblank target, clamped to [0, 0x7fff] */
  int16_t frames_delta;
  /* whether 0x46dd96 == 0x46dd98 at frame-end snapshot time */
  bool synced;
  /* elapsed flip ticks (throttle path) or sign-extended frames_delta */
  unsigned int elapsed_lo;
  int elapsed_hi;
  /* frame-end flip counter snapshot (qword_325678 + 1) */
  unsigned int end_flip_lo;
  int end_flip_hi;
  /* raw 64-bit delta: frame_end - unk_8 */
  unsigned int udelta_lo;
  int udelta_hi;
  /* debug label: "THROTTLE", "SYNCED  ", or "LAPSED  " */
  const char *label;
  /* csstrlen return values for debug buffer append (called twice per MSVC
   * pre-push interleaving: first to compute remaining space, second to
   * compute end-of-string pointer) */
  int str_len1;
  int str_len2;

  typedef unsigned int(__cdecl * fn_system_ms_t)(void);
  typedef bool(__cdecl * fn_precache_t)(void);
  typedef void(__stdcall * fn_yield_t)(int);
  typedef void(__cdecl * fn_warn_t)(const char *);
  typedef void(__cdecl * fn_rdtsc_t)(void);
  typedef int(__cdecl * fn_csstrlen_t)(const char *);
  typedef void(__cdecl * fn_profile_store_t)(int16_t, bool, const char *);
  typedef int(__cdecl * fn_snprintf_t)(char *, int, const char *, ...);

  /* snapshot hardware flip counter on entry */
  entry_flip_lo = *(unsigned int *)0x325678;
  entry_flip_hi = *(int *)0x32567c;

  /* frame-start snapshot = qword_325678 + 1 (64-bit) */
  *(unsigned int *)0x46d9f8 = entry_flip_lo + 1;
  *(int *)0x46d9fc = entry_flip_hi + (unsigned int)(0xfffffffe < entry_flip_lo);

  did_throttle = false;

  /* framerate control: master enable (0x31fa96) and per-frame enable
   * (0x32568d, cleared on timeout) must both be non-zero */
  if ((*(char *)0x31fa96 != '\0') && (*(char *)0x32568d != '\0')) {
    /* target = unk_time_globals.unk_8 - 1 (64-bit decrement) */
    target_lo = *(unsigned int *)0x46d9e8 - 1;
    target_hi =
      *(int *)0x46d9ec - (unsigned int)(*(unsigned int *)0x46d9e8 == 0);

    /* enter throttle only if current flip count < target (signed 64-bit) */
    if (!(*(int *)0x32567c > target_hi) &&
        !((*(int *)0x32567c == target_hi) &&
          (*(unsigned int *)0x325678 >= target_lo))) {
      ms_start = ((fn_system_ms_t)0x8e370)();
      precache_in_progress = ((fn_precache_t)0x1bc6b0)();
      did_throttle = true;
      ((fn_rdtsc_t)0x91b70)(); /* RDTSC timestamp: throttle start */

      /* re-check: still behind? spin-wait for vblank */
      if (!(*(int *)0x32567c > target_hi) &&
          !((*(int *)0x32567c == target_hi) &&
            (*(unsigned int *)0x325678 >= target_lo))) {
        while (1) {
          if (precache_in_progress) {
            ((fn_yield_t)0x1d0362)(1); /* yield during precache */
          }
          /* timeout guard: give up after 1000 ms */
          if (((fn_system_ms_t)0x8e370)() > ms_start + 1000U) {
            ((fn_warn_t)0xff550)(
              "stuck waiting for VBLANK callback! disabling rasterizer "
              "framerate control");
            *(char *)0x32568d = '\0'; /* disable per-frame throttle */
            break;
          }
          /* exit if flip counter reached target */
          if ((*(int *)0x32567c > target_hi) ||
              ((*(int *)0x32567c == target_hi) &&
               (*(unsigned int *)0x325678 >= target_lo))) {
            break;
          }
        }
      }
      ((fn_rdtsc_t)0x91ba0)(); /* RDTSC timestamp: throttle end */
    }
  }

  /* frame-end snapshot = qword_325678 + 1 (64-bit) */
  end_flip_lo = *(unsigned int *)0x325678 + 1;
  end_flip_hi =
    *(int *)0x32567c + (unsigned int)(*(unsigned int *)0x325678 > 0xfffffffe);

  /* capture synced flag before clobbering registers */
  synced = (*(int16_t *)0x46dd96 == *(int16_t *)0x46dd98);
  *(unsigned int *)0x46da00 = end_flip_lo;
  *(int *)0x46da04 = end_flip_hi;

  /* frames elapsed = frame_end - unk_time_globals.unk_8 (signed 64-bit),
   * clamped to int16 range [0, 0x7fff] */
  udelta_lo = end_flip_lo - *(unsigned int *)0x46d9e8;
  udelta_hi = end_flip_hi - *(int *)0x46d9ec -
              (unsigned int)(end_flip_lo < *(unsigned int *)0x46d9e8);

  if (udelta_hi > 0 || (udelta_hi == 0 && udelta_lo > 0x7fff)) {
    frames_delta = 0x7fff; /* saturate high */
  } else if (udelta_hi < 0) {
    frames_delta = 0; /* underflow: treat as 0 */
  } else {
    frames_delta = (int16_t)udelta_lo;
  }

  /* build debug label and elapsed value for the timing string */
  if (did_throttle) {
    /* elapsed = current flip count - entry flip count (64-bit sub) */
    elapsed_lo = *(unsigned int *)0x325678 - entry_flip_lo;
    elapsed_hi = *(int *)0x32567c - entry_flip_hi -
                 (unsigned int)(*(unsigned int *)0x325678 < entry_flip_lo);
    label = "THROTTLE";
  } else {
    /* use sign-extended frames_delta as elapsed (matches MOVSX/CDQ) */
    elapsed_lo = (unsigned int)(int)frames_delta;
    elapsed_hi = (int)frames_delta >> 0x1f;
    label = "SYNCED  ";
    if (frames_delta != 0) {
      label = "LAPSED  ";
    }
  }

  /* append timing info to the debug ring buffer at 0x46ddfc.
   * csstrlen is called twice due to MSVC pre-push interleaving: the first
   * call measures the current length to compute remaining space; the
   * second call (with the same arg) computes the end-of-string pointer.
   * Both calls produce the same result since the buffer is not modified
   * between them. */
  str_len1 = ((fn_csstrlen_t)0x8df60)((const char *)0x46ddfc);
  str_len2 = ((fn_csstrlen_t)0x8df60)((const char *)0x46ddfc);
  ((fn_snprintf_t)0x1d9179)((char *)(0x46ddfc + str_len2), 0x200 - str_len1,
                            "%6I64d(targ%6I64d %s%2d)", entry_flip_lo,
                            entry_flip_hi, *(unsigned int *)0x46d9e8,
                            *(int *)0x46d9ec, label, elapsed_lo, elapsed_hi);

  /* frame-pacing active flag: set iff dd96 counter > 0 and no frames
   * elapsed this tick (i.e., we're running ahead of schedule) */
  if (*(int16_t *)0x46dd96 > 0 && frames_delta == 0) {
    *(char *)0x46dd9a = 1;
  } else {
    *(char *)0x46dd9a = 0;
  }

  /* store per-frame profile: delta count, synced flag, debug string */
  ((fn_profile_store_t)0x8f880)(frames_delta, synced, (const char *)0x46ddfc);
}

/* Clear both rasterizer timing flags. */
void main_lost_map(void)
{
  *(char *)0x46da46 = 0;
  *(char *)0x46da47 = 0;
}

/* Set the rasterizer frame-skip flag. */
void main_start_time(void)
{
  *(char *)0x46da47 = 1;
}

/*
 * main_vertical_blank_interrupt_handler - 0x101cd0
 *
 * Interrupt-context callback invoked by the D3D vblank interrupt. Increments
 * the 64-bit hardware flip counter at 0x325678/0x32567c, then optionally
 * records timing history when a flip-count pointer is available.
 *
 * Confirmed:
 *  - Increments qword at 0x325678 (lo) / 0x32567c (hi) by 1 with carry.
 *  - If flip_count_ptr (0x46ddd8) is NULL: copies the current flip counter
 *    to the "presented" snapshot at 0x325680/0x325684, then tail-calls
 *    input_tick (0xcf7e0).
 *  - If flip_count_ptr is non-NULL and *flip_count_ptr != DAT_325670:
 *      - Stores (uint16_t)(flip_lo - presented_lo) into the ring buffer
 *        at 0x46ddde + word_46DDDC * 2.
 *      - Advances word_46DDDC = (word_46DDDC + 1) % 15.
 *      - Copies current flip counter to presented snapshot.
 *      - Updates DAT_325670 = *flip_count_ptr.
 *  - Always tail-calls input_tick (0xcf7e0) at exit.
 *  - No stack frame (no PUSH EBP / MOV EBP,ESP in original — but we emit
 *    one from C; the function is simple enough that the overhead is fine).
 */
void main_vertical_blank_interrupt_handler(void)
{
  uint32_t flip_lo;
  uint32_t presented_lo;
  int16_t ring_index;

  /* increment 64-bit flip counter with carry */
  flip_lo = *(uint32_t *)0x325678 +
            1; /* hazard-ok: value-arithmetic (counter+1 for carry) */
  *(uint32_t *)0x325678 = flip_lo;
  *(uint32_t *)0x32567c = *(uint32_t *)0x32567c + (uint32_t)(flip_lo == 0);

  if (flip_count_ptr == NULL) {
    /* no flip-count source: just snapshot the counter */
    *(uint32_t *)0x325680 = *(uint32_t *)0x325678;
    *(uint32_t *)0x325684 = *(uint32_t *)0x32567c;
    input_tick();
    return;
  }

  if (*flip_count_ptr != *(int *)0x325670) {
    /* flip count changed: record timing delta in ring buffer */
    presented_lo = *(uint16_t *)0x325680;
    ring_index = word_46DDDC;
    *(int16_t *)(0x46ddde + ring_index * 2) =
      (int16_t)((uint16_t) * (uint32_t *)0x325678 - (uint16_t)presented_lo);

    word_46DDDC = (int16_t)((ring_index + 1) % 15);

    *(uint32_t *)0x325680 = *(uint32_t *)0x325678;
    *(uint32_t *)0x325684 = *(uint32_t *)0x32567c;
    *(int *)0x325670 = *flip_count_ptr;
  }

  input_tick();
}

/*
 * main_save_current_solo_map - 0x101d90
 *
 * Writes the current solo-map name to "z:\\last_solo.txt" so it can be
 * reloaded later by main_load_last_solo_map. Called from 0xa6dc0 (the
 * "queue_map" helper) on a successful solo campaign map change.
 *
 * Confirmed:
 *  - Guard: 0x1006f0 maps the map-name string to a campaign level index
 *    (0..9) or 0xffff when the name is not a known solo level. When the
 *    guard returns 0xffff the function returns without opening the file.
 *    Same helper used by main_won_map_private and main_load_last_solo_map.
 *  - File I/O helpers (addresses reused from main_load_last_solo_map /
 *    main_frame_rate_debug; not in kb.json):
 *      fopen  = 0x1d9e59 with mode "w" (DAT_00265938)
 *      fwrite = 0x1db2b3 (signature fwrite(buf, size, count, fp) — the
 *               Ghidra symbol "FID_conflict:_fread" at 0x1db2b3 is
 *               actually fwrite; its body calls the write-buffer helper
 *               at 0x1db19c which performs MOVSD/MOVSB REP from the
 *               caller buffer into the FILE's buffer).
 *      fclose = 0x1d9dac
 *  - File contents: fwrite(map_name, 1, csstrlen(map_name) + 1, fp) —
 *    includes the terminating NUL so the reader can read the full path
 *    as a NUL-terminated C string.
 *  - On fopen failure: error(2, "Couldn't create a file to write the "
 *    "current solo map to") — no ABORT, no fallback. The solo progress
 *    simply isn't persisted.
 *  - The fopen PUSH ESI just before reserves the fclose fp arg slot,
 *    and ADD ESP,0x14 at the tail cleans fwrite's 4 args + fclose's
 *    1 arg together (MSVC pre-push interleaving).
 *
 * Uncertain:
 *  - csstrlen is the size-1 strlen at 0x8df60 (confirmed in kb.json).
 *    Ghidra's "csstrlen" stub in the decomp was the same helper.
 */
void main_save_current_solo_map(char *map_name)
{
  uint16_t level_index;
  void *fp;

  typedef uint16_t(__cdecl * fn_map_to_level_t)(char *map_name);
  typedef void *(__cdecl * fn_fopen_t)(const char *path, const char *mode);
  typedef size_t(__cdecl * fn_fwrite_t)(const void *buf, size_t size,
                                        size_t count, void *fp);
  typedef int(__cdecl * fn_fclose_t)(void *fp);

  level_index = ((fn_map_to_level_t)0x1006f0)(map_name);
  if (level_index == 0xffff) {
    return;
  }

  fp = ((fn_fopen_t)0x1d9e59)("z:\\last_solo.txt", "w");
  if (fp == NULL) {
    error(2, "Couldn't create a file to write the current solo map to");
    return;
  }

  ((fn_fwrite_t)0x1db2b3)(map_name, 1, csstrlen(map_name) + 1, fp);
  ((fn_fclose_t)0x1d9dac)(fp);
}

/*
 * main_load_last_solo_map - 0x101e00
 *
 * Called from the main loop when main_load_last_solo_map_pending (0x46da48)
 * is set. Reads the last-solo-map name from "z:\\last_solo.txt" and queues
 * that map (or the default "levels\\a10\\a10") for the next change-map pass.
 *
 * Confirmed:
 *  - Pending guard: main_load_last_solo_map_pending must be non-zero.
 *    A second guard at 0x1c5940 returns non-zero while a saved-film / demo
 *    playback is active (it reads DAT_0046cc86-adjacent globals 0x4ead58 /
 *    0x4ead60); when that guard fires, the function bails out without
 *    clearing either pending flag.
 *  - File I/O (addresses match the LIBCMT thunks already used by
 *    main_frame_rate_debug):
 *      fopen  = 0x1d9e59 with mode "r" (DAT_002658a4)
 *      fread  = 0x1db3f7 (size_t fread(buf, 1, 0xff, fp))
 *      fclose = 0x1d9dac
 *  - 256-byte stack buffer (local_104 at [EBP-0x100]). fread is clamped to
 *    0xff via a signed compare (JLE) and buf[n] is explicitly nulled.
 *  - 0x1006f0 maps a map-name string to a level index (0-9) or -1 (0xffff).
 *    Same helper already used by main_won_map_private. A 0xffff return means
 *    the loaded path is not a known level; fall back to the default.
 *  - Default map pointer lives at *(char **)0x31fa9c (points at the string
 *    "levels\\a10\\a10" — not in kb.json, accessed by hardcoded address).
 *  - 0xfffa0 is the shared "queue change-map-name" helper: copies the
 *    argument into map_name[] (0x46da55), clears main_menu_load_pending
 *    (0x46da43), sets byte_46DA54, and — if the game is in progress with
 *    word_46DA0C == 0 — arms main_change_map_name_pending.
 *  - On exit: clears main_change_map_name_pending (0x46da25) and
 *    main_load_last_solo_map_pending (0x46da48). The 0xfffa0 helper had
 *    just armed main_change_map_name_pending; this trailing clear undoes
 *    that, which is intentional — the original binary forgoes the
 *    change-map path when loading the last-solo map directly.
 *
 * Inferred:
 *  - 0x1c5940 is a "saved-film / demo is being played back" predicate. Its
 *    body reads DAT_0046ead58 (byte) and DAT_0046ead60 (dword); returns 1
 *    only when both are set. Exact name not confirmed from strings.
 *
 * Uncertain:
 *  - The paired globals gating 0x1c5940 have no strong semantic label yet.
 */
void main_load_last_solo_map(void)
{
  char buf[256];
  void *fp;
  int n;
  char *map_path;
  uint16_t level_index;

  typedef bool(__cdecl * fn_film_active_t)(void);
  typedef void *(__cdecl * fn_fopen_t)(const char *path, const char *mode);
  typedef size_t(__cdecl * fn_fread_t)(void *buf, size_t size, size_t count,
                                       void *fp);
  typedef int(__cdecl * fn_fclose_t)(void *fp);
  typedef uint16_t(__cdecl * fn_map_to_level_t)(char *map_name);
  typedef void(__cdecl * fn_queue_map_t)(char *map_path);

  if (!main_load_last_solo_map_pending) {
    return;
  }
  if (((fn_film_active_t)0x1c5940)()) {
    return;
  }

  /* default: *(char **)0x31fa9c → "levels\\a10\\a10" */
  map_path = *(char **)0x31fa9c;

  fp = ((fn_fopen_t)0x1d9e59)("z:\\last_solo.txt", "r");
  if (fp != NULL) {
    n = (int)((fn_fread_t)0x1db3f7)(buf, 1, 0xff, fp);
    ((fn_fclose_t)0x1d9dac)(fp);
    if (n > 0xff) {
      n = 0xff;
    }
    buf[n] = 0;
    level_index = ((fn_map_to_level_t)0x1006f0)(buf);
    if (level_index != 0xffff) {
      map_path = buf;
    }
  }

  ((fn_queue_map_t)0xfffa0)(map_path);
  main_change_map_name_pending = 0;
  main_load_last_solo_map_pending = 0;
}

/*
 * main_load_ui_scenario - 0x101f00
 *
 * Loads the main-menu UI scenario "levels\\ui\\ui" and initializes the
 * game-engine / director state for the menu. Called from main_menu_load
 * (0x101fe0) when main_globals.main_menu_scenario_loaded is clear, and from
 * the game-startup path with param_1 = 1 to also precache menu resources.
 *
 * Confirmed:
 *  - Precaches the UI level twice. The first call is with the string
 *    literal "levels\\ui\\ui"; the second call passes the same string
 *    after it has been copied into the local game_options.map_name[].
 *    The original binary emits both calls and we preserve that.
 *  - Asserts !main_globals.main_menu_scenario_loaded (the function may
 *    not be re-entered while the menu scenario is already resident).
 *    Original message / path / line are preserved verbatim.
 *  - game_options_t is built entirely on the stack (0x10c bytes at
 *    [EBP-0x10c]); csstrncpy(map_name, "levels\\ui\\ui", 0xff) with an
 *    explicit map_name[255] = 0 terminator. This matches the layout in
 *    types.h (map_name at offset 0xC).
 *  - Tear-down / setup order is: game_dispose_from_old_map, game_unload,
 *    game_engine_dispose, game_set_game_variant(0),
 *    main_menu_scenario_loaded = 1, main_new_map(&game_options).
 *  - Post main_new_map the function calls three director/UI helpers
 *    (0x86cb0, 0x85180, 0xe43d0) and arms main_load_last_solo_map_pending.
 *    The trailing `if (a1)` branch calls main_menu_precache_resources.
 *
 * Inferred:
 *  - 0x86cb0 lives in camera/director.c (its asserts reference that file)
 *    and appears to reset/enable directors for each local player;
 *    called here with 1.
 *  - 0x85180 appears to be a cinematic/cutscene state initializer;
 *    called here with (0, 0, -1).
 *  - 0xe43d0 is the UI widget-flag-2 setter already used by
 *    main_change_map_name; called here with 1.
 *
 * Uncertain:
 *  - Exact semantics of 0x86cb0 / 0x85180 arguments beyond the observed
 *    constant values. Names are withheld pending stronger evidence.
 */
void main_load_ui_scenario(bool a1)
{
  game_options_t game_options;

  typedef void(__cdecl * fn_director_init_t)(int arg);
  typedef void(__cdecl * fn_cinematic_reset_t)(int16_t a, int16_t b, int c);
  typedef void(__cdecl * fn_set_widget_flag2_t)(bool enable);

  game_precache_new_map("levels\\ui\\ui", 1);

  if (main_globals.main_menu_scenario_loaded) {
    display_assert("!main_globals.main_menu_scenario_loaded",
                   "c:\\halo\\SOURCE\\main\\main.c", 0x444, 1);
    system_exit(-1);
  }

  game_options_new(&game_options);
  csstrncpy(game_options.map_name, "levels\\ui\\ui", 0xff);
  game_options.map_name[255] = 0;

  game_precache_new_map(game_options.map_name, 1);
  game_dispose_from_old_map();
  game_unload();
  game_engine_dispose();
  game_set_game_variant(0);

  main_globals.main_menu_scenario_loaded = 1;
  main_new_map(&game_options);

  ((fn_director_init_t)0x86cb0)(1);
  ((fn_cinematic_reset_t)0x85180)(0, 0, -1);
  ((fn_set_widget_flag2_t)0xe43d0)(1);

  main_load_last_solo_map_pending = 1;

  if (a1) {
    main_menu_precache_resources();
  }
}

void main_menu_load(void)
{
  if (!main_globals.main_menu_scenario_loaded) {
    main_load_ui_scenario(0);
  }
  main_screen_shell_load();
  main_menu_precache_resources();
  update_server_delete();
  update_server_new();
  update_server_start();
  game_time_dispose_from_old_map();
  game_time_initialize_for_new_map();
  game_time_start();
  hs_runtime_dispose_from_old_map();
  hs_runtime_initialize_for_new_map();
  main_menu_load_pending = false;
}

void main_pregame_render(void)
{
  vector3_t unk[3];

  collision_log_continue_period(1);
  sound_render();

  unk[2].x = 0;
  unk[2].y = 0;
  unk[2].z = 0;
  pregame_render_info.cam1.unk_0 = unk[2];

  unk[1].x = 0;
  unk[1].y = 0;
  unk[1].z = 1.0;
  pregame_render_info.cam1.unk_12 = unk[1];

  pregame_render_info.unk_0 = -1;
  pregame_render_info.unk_2 = 1;

  unk[0].x = 0;
  unk[0].y = 1.0;
  unk[0].z = 0;
  pregame_render_info.cam1.unk_24 = unk[0];

  pregame_render_info.cam1.unk_36 = 0;
  pregame_render_info.cam1.vertical_field_of_view =
    2 *
    atan2(render_camera_get_adjusted_field_of_view_tangent(1.3962634) * 0.75,
          1.0);
  compute_window_bounds(0, 1, &pregame_render_info.cam1.viewport_bounds,
                        &pregame_render_info.cam1.unk_52);
  pregame_render_info.cam1.z_near = 0.0099999998;
  pregame_render_info.cam1.z_far = 1.0;
  qmemcpy(&pregame_render_info.cam0, &pregame_render_info.cam1,
          sizeof(pregame_render_info.cam0));
  render_frame_pregame(&pregame_render_info, main_globals_movie);
  collision_log_end_period();
}

/*
 * set_window_camera_values - 0x1021c0
 *
 * Populates the camera fields of a window_t struct (starting at offset 0x58)
 * from either an observer camera (a3 != NULL) or default global camera
 * pointers when a3 is NULL.
 *
 * Confirmed:
 *  - window param in EDI (stack arg [EBP+8]), camera param in EBX ([EBP+0xc]).
 *  - Copies three 12-byte vectors (position, forward, up) into window+0x58,
 *    window+0x64, window+0x70 respectively.
 *  - Computes vertical_field_of_view = 2 * atan2(tan(fov_half) * scale, 1.0)
 *    and stores at window+0x80.
 *  - When a3 != NULL and window->player != -1, and neither ff4c0 nor
 *    game_time_get_paused returns true, and object type != 3: applies a
 *    matrix transform from the player's object matrix to the camera vectors.
 *  - Sets window+0x7c (unk byte) to 0.
 *  - Copies globals at 0x325694/0x325698 to window+0x94/0x98.
 *  - If *(byte*)0x5aa255 == 0: copies 0x54 bytes (21 dwords) from the
 *    camera area (window+0x58) back to window+0x04 (the previous-frame
 *    camera snapshot), using REP MOVSD.
 *
 * Inferred:
 *  - 0x31fc1c, 0x31fc3c, 0x31fc44 are global pointers to default camera
 *    position, forward, and up vectors (used when no observer is active).
 *  - 0x25afcc is a float scale factor (0.75) for FOV tangent.
 *  - 0x2573d8 is double 1.0 (used as atan2 denominator).
 *  - 0x186460 is render_camera_get_adjusted_field_of_view_tangent (tan of
 *    half FOV).
 *  - 0xff4c0 is likely "game_in_editor" or similar predicate.
 *  - 0xa3370 is object_get_world_matrix (extracts a 4x3 matrix for a datum).
 *  - 0x10a110 builds a 4x3 matrix from position/forward/up vectors.
 *  - 0x109850 is matrix4x3_multiply.
 *  - 0x109540 decomposes a 4x3 matrix back into position/forward/up.
 *  - 0x5aa255 is a "first frame" or "camera not yet initialized" flag.
 */
void set_window_camera_values(void *window, float *a3)
{
  char *win = (char *)window;
  float *dest_pos = (float *)(win + 0x58);
  float *dest_fwd = (float *)(win + 0x64);
  float *dest_up = (float *)(win + 0x70);

  typedef double(__cdecl * fn_tan_fov_t)(float half_fov);
  typedef bool(__cdecl * fn_in_editor_t)(void);
  typedef int16_t(__cdecl * fn_object_type_t)(uint16_t datum);
  typedef void(__cdecl * fn_get_matrix_t)(uint16_t datum, float *out);
  typedef void(__cdecl * fn_build_matrix_t)(float *out, float *pos, float *fwd,
                                            float *up);
  typedef void(__cdecl * fn_mul_matrix_t)(float *a, float *b, float *out);
  typedef void(__cdecl * fn_decompose_t)(float *mat, float *pos, float *fwd,
                                         float *up);

  if (a3 != NULL) {
    /* copy position (a3+0x00), forward (a3+0x20), up (a3+0x2c) */
    dest_pos[0] = a3[0];
    dest_pos[1] = a3[1];
    dest_pos[2] = a3[2];
    dest_fwd[0] = a3[8]; /* offset 0x20 / 4 = 8 */
    dest_fwd[1] = a3[9];
    dest_fwd[2] = a3[10];
    dest_up[0] = a3[11]; /* offset 0x2c / 4 = 11 */
    dest_up[1] = a3[12];
    dest_up[2] = a3[13];

    /* vertical_field_of_view = 2 * atan2(tan(a3[0xe]) * scale, 1.0) */
    {
      double t = ((fn_tan_fov_t)0x186460)(a3[14]);
      double scaled = t * (double)*(float *)0x25afcc;
      double angle = atan2(scaled, *(double *)0x2573d8);
      *(float *)(win + 0x80) = (float)(angle + angle);
    }

    /* apply object matrix transform if player is valid and not in editor
     * or paused, and object type != 3 */
    if (*(int16_t *)win != -1) {
      if (!((fn_in_editor_t)0xff4c0)()) {
        if (!game_time_get_paused()) {
          uint16_t player_datum = *(uint16_t *)win;
          int16_t obj_type = ((fn_object_type_t)0x86410)(player_datum);
          if (obj_type != 3) {
            float obj_matrix[13]; /* 4x3 matrix = 52 bytes */
            float cam_matrix[13];
            ((fn_get_matrix_t)0xa3370)(player_datum, obj_matrix);
            ((fn_build_matrix_t)0x10a110)(cam_matrix, a3, a3 + 8, a3 + 11);
            ((fn_mul_matrix_t)0x109850)(cam_matrix, obj_matrix, cam_matrix);
            ((fn_decompose_t)0x109540)(cam_matrix, dest_pos, dest_fwd, dest_up);
          }
        }
      }
    }
  } else {
    /* no observer camera: use global default camera pointers */
    {
      float *src = *(float **)0x31fc1c;
      dest_pos[0] = src[0];
      dest_pos[1] = src[1];
      dest_pos[2] = src[2];
    }
    {
      float *src = *(float **)0x31fc3c;
      dest_fwd[0] = src[0];
      dest_fwd[1] = src[1];
      dest_fwd[2] = src[2];
    }
    {
      float *src = *(float **)0x31fc44;
      dest_up[0] = src[0];
      dest_up[1] = src[1];
      dest_up[2] = src[2];
    }

    /* default FOV: tan(1.3962634) * scale, doubled atan2 */
    {
      double t = ((fn_tan_fov_t)0x186460)(1.3962634f);
      double scaled = t * (double)*(float *)0x25afcc;
      double angle = atan2(scaled, *(double *)0x2573d8);
      *(float *)(win + 0x80) = (float)(angle + angle);
    }
  }

  /* clear unk byte at offset 0x7c */
  *(uint8_t *)(win + 0x7c) = 0;

  /* copy timing globals */
  *(uint32_t *)(win + 0x94) = *(uint32_t *)0x325694;
  *(uint32_t *)(win + 0x98) = *(uint32_t *)0x325698;

  /* if 0x5aa255 is clear, snapshot camera to previous-frame area */
  if (*(uint8_t *)0x5aa255 == 0) {
    qmemcpy(win + 0x04, win + 0x58, 0x54);
  }
}

void main_present_frame(void)
{
  const char *err_msg;
  char path[512];
  file_ref_t file_ref;

  render_frame_present(0, main_globals_movie);

  if (global_screenshot_count <= 0 && main_globals_movie) {
    snprintf(path, sizeof(path), "movie\\frame%06d.tga", movie_frame_count++);
    file_reference_create_from_path(&file_ref, path, 0);
    err_msg = tiff_export(&file_ref, main_globals_movie);
    if (err_msg) {
      error(2, err_msg);
    }
  }
}

void main_setup_connection(void)
{
  game_options_t game_options;

  if (byte_46DA45) {
    main_menu_load_pending = 0;
    word_46DA0C = 3;
    error(2, "error opening saved film");
    main_menu_load_pending = 1;
  }

  if (main_menu_load_pending) {
    main_menu_load();
    return;
  }

  word_46DA0C = 0;
  game_options_new(&game_options);
  csstrncpy(game_options.map_name, map_name, sizeof(game_options.map_name) - 1);
  game_options.map_name[sizeof(game_options.map_name) - 1] = 0;
  game_options.difficulty = global_difficulty_level;
  game_precache_new_map(game_options.map_name, 1);
  game_dispose_from_old_map();
  main_new_map(&game_options);
}

void main_initialize_time(void)
{
  /* d3d_find_flipcount compares the stored callback pointer against the
   * original XBE address.  The forward thunk for our ported C function
   * lives at a different address, so we must pass the raw original
   * address here.  The reverse thunk at 0x101cd0 redirects into our
   * ported main_vertical_blank_interrupt_handler. */
#define VBLANK_HANDLER_ADDR (void *)0x101CD0

  unk_time_globals.unk_0 = system_milliseconds();
  unk_time_globals.unk_8 = 0L;
  rasterizer_set_vblank_callback(VBLANK_HANDLER_ADDR);
  word_46DDDC = 0;
  csmemset(word_46DDDE, 0, 0x1Eu);
  flip_count_ptr = d3d_find_flipcount();
#undef VBLANK_HANDLER_ADDR
}

/*
 * screenshot_render - 0x102510
 *
 * Renders and saves multi-resolution screenshots. Takes the window array via
 * EDI (register arg). Clamps the screenshot multiplier (int16 at 0x31fa98)
 * to [1, 3], creates a scaled bitmap via bitmap_2d_new (0x7e0b0), renders
 * each tile of each screenshot frame, saves each as a numbered TIF file,
 * then deletes the bitmap.
 *
 * Confirmed:
 *  - Register arg: EDI = window pointer (void *a1).
 *  - Clamp logic: if multiplier < 1, set 1; if > 3, set 3; else keep.
 *  - Bitmap created with scaled screen dimensions * multiplier.
 *  - Nested loop: for each of global_screenshot_count x global_screenshot_count
 *    outer frames, for each multiplier x multiplier inner tiles.
 *  - When global_screenshot_count < 2 AND multiplier < 2: single-shot mode
 *    (render_frame gets NULL tile coords, render_frame_present gets NULL).
 *  - Otherwise: render_frame and render_frame_present get tile coordinate
 *    pointers.
 *  - File format: "%dscreenshot%d%d.tif" with (screenshot_index, row, col).
 *  - After all frames: increments screenshot_index (0x46da0e), calls
 *    bitmap_delete (0x7c8f0).
 *  - Clears global_screenshot_count to 0 at exit.
 */
void screenshot_render(void *a1)
{
  int16_t multiplier;
  void *bitmap;
  int16_t outer_row, outer_col;
  int16_t inner_row, inner_col;
  char path[512];
  file_ref_t file_ref;
  int16_t tile_coords[4]; /* local_8, local_6, local_4, local_2 */
  const char *err_msg;

  typedef void *(__cdecl * fn_bitmap_new_t)(int width, int height, int unk,
                                            int depth);
  typedef void(__cdecl * fn_render_frame_t)(
    void *win, int16_t count, int16_t *a4, int16_t *a5, void *bitmap, float a7);
  typedef void(__cdecl * fn_render_present_t)(int16_t * a1, void *bitmap);
  typedef const char *(__cdecl * fn_tiff_export_t)(file_ref_t * info,
                                                   void *bitmap);

  /* clamp multiplier to [1, 3] */
  multiplier = *(int16_t *)0x31fa98;
  if (multiplier < 1) {
    *(int16_t *)0x31fa98 = 1;
  } else if (multiplier > 3) {
    *(int16_t *)0x31fa98 = 3;
  }

  /* create scaled bitmap */
  {
    int16_t scr_x0 = *(int16_t *)0x325654;
    int16_t scr_x1 = *(int16_t *)0x325658;
    int16_t scr_y0 = *(int16_t *)0x325656;
    int16_t scr_y1 = *(int16_t *)0x32565a;
    int w = *(int16_t *)0x31fa98 * (scr_x1 - scr_x0);
    int h = *(int16_t *)0x31fa98 * (scr_y1 - scr_y0);
    bitmap = ((fn_bitmap_new_t)0x7e0b0)(w, h, 0, 10);
  }

  if (bitmap == NULL || *(int *)((char *)bitmap + 0x2c) == 0) {
    goto done;
  }

  console_printf(1, "");
  console_flush();

  for (outer_row = 0; outer_row < global_screenshot_count; outer_row++) {
    for (outer_col = 0; outer_col < global_screenshot_count; outer_col++) {
      for (inner_row = 0; inner_row < *(int16_t *)0x31fa98; inner_row++) {
        for (inner_col = 0; inner_col < *(int16_t *)0x31fa98; inner_col++) {
          tile_coords[0] = inner_col; /* local_8: x tile */
          tile_coords[1] = inner_row; /* local_6: y tile */
          tile_coords[2] = outer_col; /* local_4: outer x */
          tile_coords[3] = outer_row; /* local_2: outer y */

          if (global_screenshot_count < 2 && *(int16_t *)0x31fa98 < 2) {
            /* single-shot: no tile coordinates */
            ((fn_render_frame_t)0x185680)(a1, 1, NULL, NULL, bitmap, 0.0f);
            ((fn_render_present_t)0x184dc0)(NULL, bitmap);
          } else {
            ((fn_render_frame_t)0x185680)(a1, 1, &tile_coords[2],
                                          &tile_coords[0], bitmap, 0.0f);
            ((fn_render_present_t)0x184dc0)(&tile_coords[0], bitmap);
          }
        }
      }

      /* save TIF file */
      crt_sprintf(path, "%dscreenshot%d%d.tif", (int)*(uint16_t *)0x46da0e,
                  (int)outer_row, (int)outer_col);
      file_reference_create_from_path(&file_ref, path, 0);
      err_msg = ((fn_tiff_export_t)0x7f5e0)(&file_ref, bitmap);
      if (err_msg != NULL) {
        error(2, err_msg);
      }
    }
  }

  *(int16_t *)0x46da0e = *(int16_t *)0x46da0e + 1;
  bitmap_delete(bitmap);

done:
  global_screenshot_count = 0;
}

/*
 * halt_and_catch_fire (0x1029a0) — fatal-error "bluescreen" renderer.
 * Entered after an unrecoverable engine fault. Guards against re-entrant
 * invocation with an INT3 breakpoint, then silences rumble on every
 * connected gamepad and resolves the interface (or fallback system) font.
 * Loops forever: rebuilds a throwaway camera/frustum from the default
 * camera globals, mirrors it into the shared render camera, begins the
 * rasterizer window, draws the build version string and the last
 * recorded error message, then presents the frame. Never returns.
 */
void halt_and_catch_fire(void)
{
  void *had_interface;
  int16_t gamepad_index;
  char has_gamepad;
  int tag_index;
  window_parameters_t window_params;
  float frame_begin_buf[2];
  int32_t screen_pos[2];
  uint8_t text_color[6];
  float *default_pos;
  float *default_fwd;
  float *default_up;
  float *frustum_extra;
  double t;
  double scaled;
  double angle;
  const void *default_color;
  void *error_msg;

  if (*(char *)0x46e392 != 0) {
    FUN_001d980b(0);
#if defined(_MSC_VER) && !defined(__clang__)
    __asm { int 3 }
#else
    __asm__ volatile("int3");
#endif
    return;
  }

  had_interface = FUN_0018e3b0();
  *(char *)0x46e392 = 1;

  for (gamepad_index = 0; gamepad_index < 4; gamepad_index++) {
    has_gamepad = input_has_gamepad(gamepad_index);
    if (has_gamepad != 0) {
      input_set_rumble(gamepad_index, 0, 0);
    }
  }

  tag_index = -1;
  if (had_interface != NULL) {
    tag_index = interface_get_tag_index(1);
  }
  if (tag_index == -1) {
    tag_index = tag_loaded(0x666f6e74, "old tags\\internal system plain");
  }

  for (;;) {
    _rasterizer_reset_state();
    csmemset(frame_begin_buf, 0, sizeof(frame_begin_buf));
    rasterizer_frame_begin(frame_begin_buf);
    _rasterizer_windows_begin();

    csmemset(&window_params, 0, sizeof(window_params));

    /* Default camera position/forward/up: bare PTR_DAT globals hold the
     * pointer VALUE to a live 3-float vector each (same idiom already
     * established above for 0x31fc1c/0x31fc3c/0x31fc44). */
    default_pos = *(float **)0x31fc1c;
    window_params.camera.unk_0.x = default_pos[0];
    window_params.camera.unk_0.y = default_pos[1];
    window_params.camera.unk_0.z = default_pos[2];

    default_fwd = *(float **)0x31fc3c;
    window_params.camera.unk_12.x = default_fwd[0];
    window_params.camera.unk_12.y = default_fwd[1];
    window_params.camera.unk_12.z = default_fwd[2];

    default_up = *(float **)0x31fc44;
    window_params.camera.unk_24.x = default_up[0];
    window_params.camera.unk_24.y = default_up[1];
    window_params.camera.unk_24.z = default_up[2];

    window_params.camera.unk_36 = 0;

    window_params.camera.viewport_bounds.y0 = 0;
    window_params.camera.viewport_bounds.x0 = 0;
    window_params.camera.viewport_bounds.y1 = 0x1e0;
    window_params.camera.viewport_bounds.x1 = 0x280;

    /* Bit-exact dword copy, not an int->float conversion: the original
     * stores a raw undefined4 into these float fields. */
    window_params.camera.z_near = *(float *)0x325694;
    window_params.camera.z_far = *(float *)0x325698;

    t = render_camera_get_adjusted_field_of_view_tangent(1.3962634f);
    scaled = t * (double)*(float *)0x25afcc;
    angle = atan2(scaled, *(double *)0x2573d8);
    window_params.camera.vertical_field_of_view = (float)(angle + angle);

    render_camera_build_frustum(&window_params.camera, 0, window_params.frustum,
                                1);

    window_params.unk_0[0] = 0;

    frustum_extra = *(float **)0x2ee71c;
    window_params.frustum[100] = frustum_extra[0];
    window_params.frustum[101] = frustum_extra[1];
    window_params.frustum[102] = frustum_extra[2];
    window_params.frustum[104] = 0.0f;
    window_params.frustum[105] = 0.0f;
    *(int16_t *)&window_params.frustum[106] = 0;

    /* Mirror into the shared render camera used elsewhere in the renderer. */
    qmemcpy(&unknown_global_camera, &window_params.camera, sizeof(camera_t));

    rasterizer_window_begin(&window_params);

    if (tag_index != -1) {
      screen_pos[0] = *(int32_t *)0x32565c;
      screen_pos[1] = *(int32_t *)0x325660;

      /* text_color is not a color: rasterizer_text_draw's 3rd parameter is
       * an OUT cursor -- draw_string (0x19c5d0) ends with `*param_3 =
       * CONCAT22(line_y, x_end)`, writing the end-of-text position into
       * bytes 0..3. The original zeroes only bytes 0..3 (two word stores
       * of BX at [EBP-0x8]/[EBP-0x6]); bytes 4..5 stay uninitialized and
       * are only ever read into the discarded high word of a dword load. */
      *(int16_t *)&text_color[0] = 0;
      *(int16_t *)&text_color[2] = 0;

      default_color = *(const void **)0x2ee6c4;
      draw_string_set_font(tag_index, -1, 0, 0, default_color);
      draw_string_set_tab_stops(0, 0);
      draw_string_set_color(default_color);
      rasterizer_text_draw(
        screen_pos, 0, text_color, -4,
        "halobeta xbox 01.10.12.2276 built at: Oct 12 2001 16:07:48");

      /* Original (0x102bd5): MOV EDX,[EBP-0x6]; DEC EDX; MOV [EBP-0x14],DX.
       * [EBP-0x6] bytes 0..1 are the HIGH word of the cursor dword the
       * first draw wrote at [EBP-0x8] -- the final line Y. The error
       * message is drawn starting from that line; only the low word of
       * screen_pos[0] is stored (high word untouched, matching the
       * original word store). */
      *(int16_t *)&screen_pos[0] = (int16_t)(*(int32_t *)(text_color + 2) - 1);

      error_msg = error_get();
      rasterizer_text_draw(screen_pos, 0, text_color, -4,
                           (const char *)error_msg);
    }

    FUN_00184980(1);
    FUN_00184980(0);
    FUN_0017e190();
    FUN_00158f90();
    _rasterizer_windows_end();
    _rasterizer_frame_end();
    /* Original calls the thunk at 0x17c930 (jmps to 0x157e40) with two null
     * args -- rasterizer_dynamic_lit_geometry_draw, NOT render_frame_present
     * (0x184dc0). Both args are used by the callee (edi=[ebp+8], esi=[ebp+c]);
     * (0,0) selects its null/no-geometry path. */
    rasterizer_dynamic_lit_geometry_draw(0, 0);
    input_update();
  }
}

/*
 * main_halt_entry — infinite render loop entered after a fatal halt.
 * Continuously processes input, shell idle, event manager, telnet console,
 * UI widgets, pregame rendering, rasterizer throttle, and frame presentation.
 * This keeps the screen alive (e.g. showing an error overlay) even though the
 * game simulation has stopped.  Never returns.
 */
void __noreturn main_halt_entry(void)
{
  for (;;) {
    input_frame_begin();
    input_update();
    shell_idle();
    event_manager_update();
    telnet_console_process();
    process_ui_widgets();
    main_pregame_render();
    main_rasterizer_throttle();
    main_present_frame();
    input_frame_end();
  }
}

void main_game_render(double a2)
{
  bool force_single_screen;
  int player_index;
  window_t *current_window;
  void *camera;
  int num_players;
  int num_screens;
  __int16 next_player;

  lock_global_random_seed();
  collision_log_continue_period(1);
  sound_render();

  force_single_screen = game_engine_force_single_screen();
  next_player = -1;
  num_screens = CLAMP(local_player_count(), 1, 4);
  num_players = num_screens;

  if (force_single_screen || cinematic_in_progress()) {
    num_screens = 1;
    num_players = 1;
  }

  for (player_index = 0; player_index < num_players; player_index++) {
    current_window = &window[player_index];
    camera = NULL;

    compute_window_bounds(player_index, num_players, &current_window->unk_132,
                          &current_window->unk_140);

    if (!force_single_screen && player_index < num_screens) {
      if (!byte_325714 || next_player == -1) {
        if (word_46DA0C == 3) {
          next_player = 0;
        } else {
          next_player = local_player_get_next(next_player);
        }
      }
      current_window->player = next_player;
      camera = observer_get_camera(next_player);
    } else {
      current_window->player = -1;
    }

    set_window_camera_values(current_window, camera);
    current_window->unk_2 = 0;
  }

  current_window = &window[num_players];
  compute_window_bounds(0, 1, &current_window->unk_132,
                        &current_window->unk_140);
  current_window->player = -1;
  current_window->unk_2 = 1;
  set_window_camera_values(current_window, 0);

  if (global_screenshot_count <= 0) {
    render_frame(window, num_players + 1, 0, 0, main_globals_movie, a2);
  } else {
    screenshot_render(window);
  }
  collision_log_end_period();
  unlock_global_random_seed();
}

#ifdef DECOMP_CUSTOM
static void print_startup_banner(void)
{
  error(2, "DECOMP BUILD %s (%s)", build_rev, build_date);
  error(2, "--------------------------------------------------------------");
}
#endif

static __inline void abort_with_error_message(int16_t message_id)
{
  display_error_when_main_menu_loaded(message_id);
  error(2, "the game host went down");
  network_game_abort();
}

void main_loop(void)
{
  bool v0; // cc
  bool v1; // bl
  float a2; // [esp+4h] [ebp-14h]
  float a2a; // [esp+4h] [ebp-14h]
  float a2b; // [esp+4h] [ebp-14h]
  float a2_4; // [esp+8h] [ebp-10h]
  float a2_4a; // [esp+8h] [ebp-10h]
  char v9[4]; // [esp+10h] [ebp-8h] BYREF
  int x;
#ifdef DECOMP_CUSTOM
  /* die-to-core debug hook enable flag; armed from the d:\die_to_core.xts
   * sentinel at startup below (mirrors the recorder *.xts sentinel checks). */
  int die_to_core_enabled = 0;
#endif

  if (!game_in_editor()) {
    csstrncpy(map_name, "levels\\b30\\b30", 0xFFu);
    byte_46DB54 = 0;
  }
  main_menu_load_pending = game_in_editor() == 0;
  word_46DA40 = -1;
  byte_46DA46 = 1;
  console_initialize();
  debug_keys_initialize();
  game_initialize();
  console_startup();

#ifdef DECOMP_CUSTOM
  print_startup_banner();
  /* Arm the die-to-core debug hook if the sentinel exists (same file-attribute
   * probe the input recorder uses for write/read/loop.xts). */
  die_to_core_enabled = (file_get_full_attributes("d:\\die_to_core.xts") != -1);
#endif

  main_setup_connection();
  main_initialize_time();
  while (1) {
    if (!game_in_editor()) {
      if (word_46DA40 != -1) {
        scenario_switch_structure_bsp(word_46DA40);
        word_46DA40 = -1;
        hud_load(0);
      }
      if (byte_46DA3B) {
        if (!(unsigned __int8)game_time_get_paused()) {
          v0 = word_46DA4C++ <= 90;
          if (!v0) {
            byte_46DA3B = 0;
            word_46DA4C = 0;
#ifdef DECOMP_CUSTOM
            /* die-to-core debug hook (d:\die_to_core.xts): reload the fixture
             * core instead of the campaign checkpoint, so death-loops don't
             * need a reboot. Reuses the existing load-core dispatch at the
             * bottom of this same loop iteration (game_state_load_core_pending,
             * checked below). Falls through to the faithful revert when the
             * sentinel is absent or no core name is loaded. */
            if (die_to_core_enabled && core_name[0]) {
              game_state_load_core_pending = 1;
            } else
#endif
              game_state_revert();
          }
        }
      }
      if (main_won_map_private_pending) {
        main_won_map_private();
      }
      if (byte_46DA3C) {
        if (!(unsigned __int8)game_time_get_paused() &&
            !cinematic_in_progress()) {
          v0 = word_46DA4E++ <= 90;
          if (!v0) {
            if (players_respawn_coop()) {
              byte_46DA3C = 0;
              word_46DA4E = 0;
            }
          }
        }
      }
      if (game_state_save_pending) {
        game_state_save();
        hud_autosave(0);
        game_state_save_pending = 0;
      }
      if (main_change_map_name_pending) {
        main_change_map_name();
      }
      if (game_state_revert_pending) {
        game_state_revert();
        ui_widgets_disable_pause_game(30);
        game_state_revert_pending = 0;
      }
      if (should_skip_cinematic) {
        if (cinematic_can_be_skipped()) {
          game_state_revert();
          ui_widgets_disable_pause_game(30);
          game_state_revert_pending = 0;
        }
        should_skip_cinematic = 0;
      }
      if (game_reset_pending && !(unsigned __int8)game_time_get_paused()) {
        scenario_switch_structure_bsp(0);
        game_dispose_from_old_map();
        input_flush();
        game_initialize_for_new_map();
        create_local_players();
        game_time_start();
        game_initial_pulse();
        ui_widgets_disable_pause_game(30);
        game_reset_pending = 0;
      }
      if (game_state_save_core_pending) {
        game_state_save_core(core_name);
        game_state_save_core_pending = 0;
      }
      if (game_state_load_core_pending) {
        game_state_load_core(core_name);
        game_state_load_core_pending = 0;
#ifdef DECOMP_CUSTOM
        /* core-loop / die-to-core: re-sync recorded input to the freshly
         * (re)loaded core — rewind playback to packet 0 so the stored input
         * re-executes from the same state. Active only when input playback is
         * on (read.xts / core_loop.xts = mode 4, loop.xts = mode 5). The mode
         * and handle globals live in input_xbox.c (0x46b818 / 0x46b814). */
        if (*(int *)0x46b818 == 4 || *(int *)0x46b818 == 5) {
          SetFilePointer(*(int *)0x46b814, 0, (int *)0, 0);
        }
#endif
      }
      if (main_menu_load_pending) {
        main_menu_load();
      }
      if (main_load_last_solo_map_pending) {
        main_load_last_solo_map();
      }
      if (xbox_demos_launch_pending) {
        xbox_demos_launch_pending = 0;
        xbox_demos_launch();
      }
      if (main_skip_private_pending) {
        main_skip_private();
      }
      if (byte_46DA50) {
        if (cache_files_precache_in_progress() &&
            (unsigned __int16)cache_files_precache_map_status((float *)v9) ==
              1) {
          cache_files_precache_map_end();
        }
        if (!cache_files_precache_in_progress()) {
          cache_files_precache_map_begin(&byte_46DC55, 0);
          byte_46DA50 = 0;
        }
      }
    } else {
      if (game_reset_pending && !(unsigned __int8)game_time_get_paused()) {
        scenario_switch_structure_bsp(0);
        game_dispose_from_old_map();
        input_flush();
        game_initialize_for_new_map();
        create_local_players();
        game_time_start();
        game_initial_pulse();
        ui_widgets_disable_pause_game(30);
        game_reset_pending = 0;
      }
    }
    profile_frame_start();
    input_frame_begin();
    input_update();
    input_abstraction_update();
    shell_idle();
    event_manager_update();
    telnet_console_process();
    if (!shell_application_is_paused()) {
      v1 = 1;
      x = word_46DA0C;
      if (x == 1) {
        if (!network_game_client_start_frame()) {
          abort_with_error_message(6);
        }
      } else if (x == 2) {
        if (!network_game_client_start_frame()) {
          abort_with_error_message(1);
        } else if (!network_game_server_start_frame()) {
          abort_with_error_message(1);
        }
      } else if (x == 3) {
        break;
      }
      main_update_time();
      process_ui_widgets();
      bink_playback_update();
      if ((!game_in_editor() &&
           (input_key_is_down(0x55u) || input_key_is_down(0))) ||
          editor_should_exit()) {
        if (main_globals_movie) {
          bitmap_delete(main_globals_movie);
          main_globals_movie = 0;
        }
        if (!game_engine_running()) {
          word_46DA40 = -1;
          byte_46DA28 = 0;
          game_reset_pending = 1;
          byte_46DA3B = 0;
        }
      }
      if (game_in_progress()) {
        terminal_update();
        if (!console_update() || word_46DA0C) {
          debug_keys_update();
          cheats_update();
          a2 = (double)(unsigned __int8)byte_46DA46;
          a2 *= flt_46DA08;
          player_control_update(a2);
          x = word_46DA0C;
          if (x > 0 && x <= 2 && !network_game_client_end_frame()) {
            display_error_when_main_menu_loaded(1);
            network_game_abort();
          }
          a2a = (double)(unsigned __int8)byte_46DA46;
          a2a *= flt_46DA08;
          game_time_update(a2a);
          v1 = main_globals.main_menu_scenario_loaded ||
               (byte_46DA46 &&
                ((unsigned __int8)game_time_get_paused() ||
                 game_time_get_elapsed() > 0 || game_time_get_speed() < 1.0));

          v1 &= !game_engine_running() || game_time_get() >= 3;

          collision_log_continue_period(1);
          a2b = (double)(unsigned __int8)byte_46DA46;
          a2b *= flt_46DA08;
          director_update(a2b);
          a2_4 = (double)(unsigned __int8)byte_46DA46;
          a2_4 *= flt_46DA08;
          observer_update(a2_4);
          collision_log_end_period();
          a2_4a = (double)(unsigned __int8)byte_46DA46;
          a2_4a *= flt_46DA08;
          game_engine_update_non_deterministic(a2_4a);
        }
        if (byte_46DA28) {
          main_save_map_private();
        }
        if (v1 && !debug_no_drawing) {
          profile_render_start();
          main_game_render(flt_46DA08);
          profile_render_end();
        }
      } else {
        profile_render_start();
        main_pregame_render();
        profile_render_end();
      }
      main_rasterizer_throttle();
      if (v1 && !debug_no_drawing) {
        main_present_frame();
      }
    }
    input_frame_end();
    profile_frame_end();
    main_frame_rate_debug();
    if (byte_46DA47) {
      byte_46DA47 = 0;
      unk_time_globals.unk_0 = system_milliseconds();
      unk_time_globals.unk_8 = qword_325678;
      byte_46DA46 = 1;
    }
  }
  error(2, "end of saved film");
  x = word_46DA0C;
  switch (x) {
  case 2:
    dispose_global_network_game_server();
    dispose_global_network_game_client();
    break;
  case 1:
    dispose_global_network_game_server();
    break;
  }
  game_dispose_from_old_map();
  game_dispose();
  debug_keys_dispose();
  console_dispose();
}

/*
 * FUN_001034e0 - 0x1034e0
 * Dispose helper for an object carrying three sub-allocations plus an
 * element table. Walks the element table (base at word offset +3 / byte
 * 0xC, signed count at word offset +4 / byte 0x10) and, for each index,
 * resolves the element pointer via the indexer FUN_00117ee0(base, index,
 * stride=0x1c) and frees it with FUN_00117cf0. After the loop it frees
 * three tables: the object itself (+0x0), the element table (+0xC), and a
 * third table (+0x18). Element stride is 28 bytes.
 *
 * Ghidra mis-detected the prototype as void(void); the sole parameter is a
 * normal cdecl stack argument (in_stack_00000004). Pointer arithmetic is in
 * int-word (4-byte) units.
 */
void FUN_001034e0(int *param_1)
{
  int *elem;
  int index;

  index = 0;
  if (0 < param_1[4]) {
    do {
      elem = (int *)FUN_00117ee0(param_1 + 3, index, 0x1c);
      FUN_00117cf0(elem);
      index = index + 1;
    } while (index < param_1[4]);
  }
  FUN_00117cf0(param_1);
  FUN_00117cf0(param_1 + 3);
  FUN_00117cf0(param_1 + 6);
  return;
}
/*
 * main/main_recursive_tree_walk.c — recursive tree/graph DFS marking helper
 * XBE source: c:\halo\SOURCE\main\main.c
 *   (grouped into its own TU for the recursive walk helper)
 *
 * Re-implemented functions (by XBE address, ascending):
 *   0x103530  FUN_00103530  — depth-first marking walk over a node graph
 */

#include "common.h"

/*
 * FUN_00103530 — depth-first walk of a node graph.
 *
 * Looks up node = base+0x18[node_index] (stride 0x18, 6 dwords). Each node
 * holds three child-list references at node[0..2] and a visited/mark flag at
 * node[3] (0xffffffff == unvisited). If the node is unvisited and the optional
 * caller callback (may be NULL) approves it, the node is stamped with `mark`
 * and the walk recurses into every child referenced by node[0..2] via the
 * child-list array at base+0xc (stride 0x1c).
 *
 * ABI: cdecl, 5 stack params. Ghidra mis-typed this as void(void); the true
 * 5-param prototype, the callback's 4-arg char-returning signature (call site
 * @0x103566), and the recursion's 5th argument (@0x1035c9) are reconstructed
 * from the disassembly push sequences, not the decompiler.
 *
 * FUN_00117ee0(array_base, index, elem_size) returns &array[index].
 *
 * The inner child counter is a 16-bit short widened via MOVSX per iteration;
 * preserved here as `short i` / `(int)i` for codegen fidelity.
 */
void FUN_00103530(int base, char (*visit)(uint32_t, int, uint32_t *, uint32_t),
                  uint32_t visit_arg, uint32_t mark, int node_index)
{
  uint32_t *node;
  int *child_list;
  int elem;
  short i;
  int slot;

  node = (uint32_t *)FUN_00117ee0((int *)(base + 0x18), node_index, 0x18);
  if ((node[3] == 0xffffffff) &&
      ((visit == NULL) || ((*visit)(mark, base, node, visit_arg) != 0))) {
    node[3] = mark;
    slot = 3;
    do {
      if (*node != 0xffffffff) {
        child_list =
          (int *)FUN_00117ee0((int *)(base + 0xc), *node & 0x7fffffff, 0x1c);
        i = 0;
        if (0 < child_list[1]) {
          elem = 0;
          do {
            FUN_00103530(base, visit, visit_arg, mark,
                         *(int *)FUN_00117ee0(child_list, elem, 4));
            i = i + 1;
            elem = (int)i;
          } while (elem < child_list[1]);
        }
      }
      node = node + 1;
      slot = slot + -1;
    } while (slot != 0);
  }
}

/*
 * FUN_00103b80 — resolve a triangle's three vertices and forward them.
 *
 * Looks up element `tri` in table A (obj+0x134, stride 0x34) at `index`.
 * That element holds three vertex indices at word offsets +2/+3/+4
 * (byte 0x8/0xc/0x10). Each index is resolved against vertex table B
 * (obj+0x140, stride 0x50); the +8 offset into each 0x50-byte vertex
 * element is the payload passed downstream (a float* — a position/vertex
 * pointer). The three resolved pointers plus `base` and `flag` are handed
 * to FUN_00103860.
 *
 * ABI: cdecl, 4 stack params. Ghidra mis-typed this as void(void) and
 * aliased EDI=[EBP+0xc]/ESI, losing [EBP+0x8]. The true prototype and the
 * 5-arg call to FUN_00103860 are reconstructed from the disassembly push
 * sequences, not the decompiler. FUN_00103860 itself is a 5-param cdecl
 * (verified from its own disasm/decompile): (base, a, b, c, flag).
 *
 * The three inner FUN_00117ee0 calls are written as arguments to
 * FUN_00103860 so MSVC right-to-left evaluation reproduces the original
 * interleaved push order: flag first, then vertex[tri[4]], vertex[tri[3]],
 * vertex[tri[2]], then base last.
 *
 * FUN_00117ee0(array_base, index, elem_size) returns &array[index].
 */
void FUN_00103b80(int base, int obj, int index, int flag)
{
  int *tri;

  tri = (int *)FUN_00117ee0((int *)(obj + 0x134), index, 0x34);
  FUN_00103860(
    base, (float *)(FUN_00117ee0((int *)(obj + 0x140), tri[2], 0x50) + 8),
    (float *)(FUN_00117ee0((int *)(obj + 0x140), tri[3], 0x50) + 8),
    (float *)(FUN_00117ee0((int *)(obj + 0x140), tri[4], 0x50) + 8), flag);
}
/* Lazily opens the debug VRML output file ("debug.wrl") on the first call,
 * writes the VRML header, flushes it, and caches the FILE* in the global at
 * 0x46e394. Returns whether the handle is non-NULL (open succeeded). The
 * open is idempotent: once the handle is cached, subsequent calls skip the
 * open/write and just report handle-valid status. */
bool FUN_00103d30(void)
{
  if (*(void **)0x46e394 == NULL) {
    *(void **)0x46e394 = crt_fopen("debug.wrl", "w");
    if (*(void **)0x46e394 != NULL) {
      crt_fprintf(*(void **)0x46e394, "#VRML V1.0 ascii\n\n");
      crt_fflush(*(void **)0x46e394);
    }
  }
  return *(void **)0x46e394 != NULL;
}
/* error_geometry.c — debug VRML ("error geometry") output subsystem.
 *
 * Source TU proven by the __FILE__ assert xref
 * "c:\halo\SOURCE\tool\error_geometry.c". Grouped under main.obj alongside its
 * sibling FUN_00103d30 (debug .wrl lazy-open) at 0x103d30.
 */
#include "../../common.h"

/* FUN_00103de0 (0x103de0)  error_geometry.c:0x44
 *
 * Retarget the debug error-geometry output file. If 'source' differs from the
 * currently-cached path (module-global buffer @0x31fac8, compared with
 * csstrncmp over 0x3b bytes), then:
 *   - close and clear any open error_geometry_file (FILE* @0x46e394),
 *   - copy 'source' into the path buffer (csstrncpy, 0x3b),
 *   - clear the byte flag @0x31fb03,
 *   - append the ".wrl" extension (FUN_0008dc30 = strcat-like),
 *   - assert the file handle is now NULL, and
 *   - run the CRT-region helper FUN_001db4a9.
 * If 'source' matches the cached path, the call is a no-op.
 *
 * cdecl, verified from disassembly at 0x103de0: the sole stack arg
 * [EBP+0x8]='source' (Ghidra surfaces it as in_stack_00000004 because the
 * kb.json decl was void(void)). The assert tail's decompiler thunk_FUN_001029a0
 * resolves in this TU to system_exit(-1) (CALL 0x8e2f0), matching every other
 * error_geometry.c assert; verified by check_assert_targets.py.
 */
void FUN_00103de0(char *source)
{
  if (csstrncmp((char *)0x31fac8, source, 0x3b) != 0) {
    if (*(void **)0x46e394 != NULL) {
      crt_fclose(*(void **)0x46e394);
      *(void **)0x46e394 = NULL;
    }
    csstrncpy((char *)0x31fac8, source, 0x3b);
    *(char *)0x31fb03 = 0;
    FUN_0008dc30((char *)0x31fac8, ".wrl");
    if (*(void **)0x46e394 != NULL) {
      display_assert("error_geometry_file==NULL",
                     "c:\\halo\\SOURCE\\tool\\error_geometry.c", 0x44, true);
      system_exit(-1);
    }
    FUN_001db4a9();
  }
}

/* ui_widget_display_deferred_errors (0xe8db0) — readable C lift from XBE leaf. */
void ui_widget_display_deferred_errors(void)
{
  extern char DAT_00284750[];
  extern char DAT_00283280[];
  short *slot;
  int i;
  short err;

  if (cinematic_in_progress()) {
    display_assert(DAT_00284750, DAT_00283280, 0x93f, true);
    system_exit(-1);
  }
  slot = (short *)0x46cc6c;
  for (i = 0; i < 4; i++) {
    err = slot[0];
    if (err >= 0 && err < 0x28) {
      ui_widget_display_error(err, (int16_t)i, (char)((unsigned char *)slot)[2],
                              (char)((unsigned char *)slot)[3]);
    }
    slot[0] = (short)0xffff;
    slot = (short *)((char *)slot + 4);
  }
}


/* --- main.obj batch1 drafts (2026-07-26) --- */

bool cache_files_give_time_to_precache(const char *name);
void main_menu_active(char active);

/* gamepad_button_is_down (0xffef0) — readable C lift from XBE leaf. */
char gamepad_button_is_down(int16_t button)
{
  extern char DAT_0028b078[];
  extern char DAT_0028b0b4[];
  int i;
  void *state;
  unsigned char v;

  if (button < 0 || button >= 0x10) {
    display_assert(DAT_0028b078, DAT_0028b0b4, 0xf5, true);
    system_exit(-1);
  }
  for (i = 0; i < 4; i++) {
    if (input_has_gamepad((int16_t)i))
      break;
  }
  if (i >= 4)
    return 0;
  state = input_get_gamepad_state(i);
  v = *((unsigned char *)state + 0x10 + (int)button);
  return v > 0;
}


void main_disallow_persistent_storage(void)
{
  *(char *)0x46da54 = 0;
}

/* main_set_map_name (0xfffa0) — readable C lift. */
void main_set_map_name(const char *name)
{
  *(unsigned char *)0x46da43 = 0;
  csstrncpy((char *)0x46da55, name, 0xff);
  *(unsigned char *)0x46db54 = 0;
  *(unsigned char *)0x46da54 = 1;
  if (game_in_editor() || game_in_progress()) {
    if (*(short *)0x46da0c == 0)
      *(unsigned char *)0x46da25 = 1;
  }
}



/* main_set_multiplayer_map_name (0x100010) — readable C lift. */
void main_set_multiplayer_map_name(const char *name)
{
  csstrncpy((char *)0x46db55, name, 0xff);
  *(unsigned char *)0x46dc54 = 0;
  cache_files_give_time_to_precache((const char *)0x46db55);
}



const char *main_get_map_name(void)
{
  return (const char *)0x46da55;
}

/* main_set_difficulty (0x100060) — readable C lift. */
void main_set_difficulty(int16_t difficulty)
{
  if (difficulty >= 0 && difficulty < 4) {
    *(int16_t *)0x31fa90 = difficulty;
  }
}

/* main_reset_map (0x1002a0) — readable C lift. */
void main_reset_map(void)
{
  *(int16_t *)0x46da40 = (int16_t)0xffff;
  *(char *)0x46da28 = 0;
  *(char *)0x46da24 = 1;
  *(char *)0x46da3b = 0;
}

/* main_revert_map (0x1002c0) — readable C lift. */
void main_revert_map(void)
{
  *(int16_t *)0x46da40 = (int16_t)0xffff;
  *(char *)0x46da28 = 0;
  *(char *)0x46da26 = 1;
  *(char *)0x46da3b = 0;
}

/* main_skip_cinematic (0x1002e0) — readable C lift. */
void main_skip_cinematic(void)
{
  *(int16_t *)0x46da40 = (int16_t)0xffff;
  *(char *)0x46da28 = 0;
  *(char *)0x46da27 = 1;
}

/* main_save_map_nonsafe (0x100300) — readable C lift. */
void main_save_map_nonsafe(void)
{
  *(char *)0x46da28 = 1;
  *(char *)0x46da29 = 0;
}

char main_saving_map(void)
{
  return *(char *)0x46da28;
}

void main_save_cancel(void)
{
  *(char *)0x46da28 = 0;
}

/* main_save_map_safe (0x100330) — readable C lift. */
void main_save_map_safe(void)
{
  if (*(unsigned char *)0x46da28 == 0 || *(unsigned char *)0x46da2a == 0) {
    *(unsigned char *)0x46da28 = 1;
    *(unsigned char *)0x46da29 = 1;
    *(unsigned char *)0x46da2a = 1;
    *(unsigned int *)0x46da2c = 0;
    *(unsigned int *)0x46da30 = 0;
    *(unsigned short *)0x46da38 = 0;
  }
}

/* main_won_map (0x100370) — readable C lift. */
void main_won_map(void)
{
  *(char *)0x46da28 = 0;
  *(char *)0x46da3a = 1;
}

/* FUN_00100380 (0x100380) — readable C lift. */
void FUN_00100380(void)
{
  *(char *)0x46da28 = 0;
  *(char *)0x46da3b = 1;
}

/* main_respawn (0x100390) — readable C lift. */
void main_respawn(char flag)
{
  *(char *)0x46da3c = 1;
  if (flag) {
    *(int16_t *)0x46da4e = 0x5b;
  }
}

/* main_save_core (0x1003b0) — readable C lift. */
void main_save_core(void)
{
  *(char *)0x46da3d = 1;
  csstrcpy((char *)0x46dd55, (const char *)0x28b198);
}

/* main_save_core_name (0x1003d0) — readable C lift. */
void main_save_core_name(const char *name)
{
  if ((unsigned)csstrlen(name) >= 0x40) {
    display_assert((const char *)0x28b1a4, (const char *)0x28b0b4, 0x3a5, 0);
  }
  csstrncpy(0x46dd55, name, 0x3f);
  *(uint8_t *)0x46da3d = 1;
}

/* main_load_core (0x100420) — readable C lift. */
void main_load_core(void)
{
  *(char *)0x46da3e = 1;
  csstrcpy((char *)0x46dd55, (const char *)0x28b198);
}

/* main_load_core_at_startup (0x100440) — readable C lift. */
void main_load_core_at_startup(void)
{
  *(char *)0x46da3f = 1;
  csstrcpy((char *)0x46dd55, (const char *)0x28b198);
}

/* main_load_core_name (0x100460) — readable C lift. */
void main_load_core_name(const char *name)
{
  if ((unsigned)csstrlen(name) >= 0x40) {
    display_assert((const char *)0x28b1a4, (const char *)0x28b0b4, 0x3c9, 0);
  }
  csstrncpy(0x46dd55, name, 0x3f);
  *(uint8_t *)0x46da3e = 1;
}

/* main_load_core_name_at_startup (0x1004b0) — readable C lift. */
void main_load_core_name_at_startup(const char *name)
{
  if ((unsigned)csstrlen(name) >= 0x40) {
    display_assert((const char *)0x28b1a4, (const char *)0x28b0b4, 0x3d7, 0);
  }
  csstrncpy(0x46dd55, name, 0x3f);
  *(uint8_t *)0x46da3f = 1;
}

/* main_switch_structure_bsp (0x100500) — readable C lift. */
void main_switch_structure_bsp(int16_t bsp_index)
{
  scenario_t *scenario = global_scenario_get();

  if (bsp_index < 0 || (int)bsp_index >= *(int *)((char *)scenario + 0x5a4)) {
    console_warning((const char *)0x28b1e0, (int)bsp_index);
    return;
  }
  if (bsp_index == *(int16_t *)0x326a0c) {
    console_warning((const char *)0x28b20c, (int)bsp_index);
    return;
  }
  *(int16_t *)0x46da40 = bsp_index;
  hud_load(true);
}

/* main_skip (0x100560) — readable C lift. */
void main_skip(short level)
{
  if (level > 0xf) {
    error(2, (const char *)0x28b238);
    return;
  }
  *(short *)0x46da4a = level;
  *(char *)0x46da49 = 1;
}

/* main_menu_unload (0x100690) — readable C lift. */
void main_menu_unload(void)
{
  ui_widget_stop_attract_mode();
  main_menu_active(0);
  *(char *)0x46da42 = 0;
}

void main_menu_switch_to_single_player(void)
{
  *(char *)0x46da25 = 1;
}

void main_set_game_connection_to_film_playback(void)
{
  *(char *)0x46da45 = 1;
}

/* main_get_solo_level_from_name (0x1006f0) — XBE naked draft (batch 121). */
#if defined(__clang__)
static void * (*const b1006f0_c8de70)(char *destination, const char *source, size_t size) = csstrncpy;
static char * (*const b1006f0_c8d9a0)(char *s) = csstr_tolower;
static char * (*const b1006f0_c1d9690)(const char *haystack, const char *needle) = crt_strstr;

__attribute__((naked, noinline))
int main_get_solo_level_from_name(const char *map_name __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x80, %%esp\n\t"
      "pushl %%edi\n\t"
      "xorl %%eax, %%eax\n\t"
      "movb $0, -0x80(%%ebp)\n\t"
      "movl $0x1f, %%ecx\n\t"
      "leal -0x7f(%%ebp), %%edi\n\t"
      "rep stosl\n\t"
      "stosw\n\t"
      "stosb\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl $0x7f\n\t"
      "pushl %%eax\n\t"
      "leal -0x80(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c8de70]\n\t"
      "leal -0x80(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "call *%[c8d9a0]\n\t"
      "leal -0x80(%%ebp), %%eax\n\t"
      "pushl $0x284a8c\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d9690]\n\t"
      "addl $0x18, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "popl %%edi\n\t"
      "je .Lmain_get_solo_level_from_name_1\n\t"
      "xorl %%eax, %%eax\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lmain_get_solo_level_from_name_1:\n\t"
      "leal -0x80(%%ebp), %%ecx\n\t"
      "pushl $0x284a50\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1d9690]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lmain_get_solo_level_from_name_2\n\t"
      "movl $1, %%eax\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lmain_get_solo_level_from_name_2:\n\t"
      "leal -0x80(%%ebp), %%edx\n\t"
      "pushl $0x284a14\n\t"
      "pushl %%edx\n\t"
      "call *%[c1d9690]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lmain_get_solo_level_from_name_3\n\t"
      "movl $2, %%eax\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lmain_get_solo_level_from_name_3:\n\t"
      "leal -0x80(%%ebp), %%eax\n\t"
      "pushl $0x2849d8\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d9690]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lmain_get_solo_level_from_name_4\n\t"
      "movl $3, %%eax\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lmain_get_solo_level_from_name_4:\n\t"
      "leal -0x80(%%ebp), %%ecx\n\t"
      "pushl $0x28499c\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1d9690]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lmain_get_solo_level_from_name_5\n\t"
      "movl $4, %%eax\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lmain_get_solo_level_from_name_5:\n\t"
      "leal -0x80(%%ebp), %%edx\n\t"
      "pushl $0x284960\n\t"
      "pushl %%edx\n\t"
      "call *%[c1d9690]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lmain_get_solo_level_from_name_6\n\t"
      "movl $5, %%eax\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lmain_get_solo_level_from_name_6:\n\t"
      "leal -0x80(%%ebp), %%eax\n\t"
      "pushl $0x284924\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d9690]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lmain_get_solo_level_from_name_7\n\t"
      "movl $6, %%eax\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lmain_get_solo_level_from_name_7:\n\t"
      "leal -0x80(%%ebp), %%ecx\n\t"
      "pushl $0x2848e8\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1d9690]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lmain_get_solo_level_from_name_8\n\t"
      "movl $7, %%eax\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lmain_get_solo_level_from_name_8:\n\t"
      "leal -0x80(%%ebp), %%edx\n\t"
      "pushl $0x2848ac\n\t"
      "pushl %%edx\n\t"
      "call *%[c1d9690]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lmain_get_solo_level_from_name_9\n\t"
      "movl $8, %%eax\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lmain_get_solo_level_from_name_9:\n\t"
      "leal -0x80(%%ebp), %%eax\n\t"
      "pushl $0x284870\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d9690]\n\t"
      "addl $8, %%esp\n\t"
      "negl %%eax\n\t"
      "sbbl %%eax, %%eax\n\t"
      "andl $0xa, %%eax\n\t"
      "decl %%eax\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c8de70] "m"(b1006f0_c8de70), [c8d9a0] "m"(b1006f0_c8d9a0), [c1d9690] "m"(b1006f0_c1d9690)
      : "memory");
}
#else
#error "main_get_solo_level_from_name: clang naked draft required"
#endif


/* main_get_current_solo_level (0x100860) — readable C lift (thin wrapper). */
int main_get_current_solo_level(void)
{
  return main_get_solo_level_from_name((const char *)0x46da55);
}

const char *main_get_solo_level_name(int16_t index)
{
  if (index < 0 || index >= 0xa)
    return 0;
  return *(const char **)(0x31fa9c + (int)index * 4);
}

void main_run_demos(void)
{
  *(char *)0x46da44 = 1;
}

/* main_get_window_count (0x100b00) — readable C lift. */
short main_get_window_count(void)
{
  short n;
  if (game_engine_force_single_screen() || cinematic_in_progress())
    return 1;
  n = local_player_count();
  if (n < 1)
    return 1;
  if (n > 4)
    return 4;
  return n;
}

void main_crash(int unused)
{
  *(volatile int *)0 = (int)0x28b5a8;
}

/* main_print_version (0x101cc0) — readable C lift. */
void main_print_version(void)
{
  console_printf(0, (const char *)0x28b5d4);
}

/* main_save_map_no_timeout (0x101ec0) — readable C lift. */
void main_save_map_no_timeout(void)
{
  if (*(char *)0x46da28 == 0 || *(char *)0x46da2a != 0) {
    *(char *)0x46da28 = 1;
    *(char *)0x46da29 = 1;
    *(int *)0x46da2c = 0;
    *(int *)0x46da30 = 0;
    *(short *)0x46da38 = 0;
  }
  *(char *)0x46da2a = 0;
}

/* main_roll_credits (0x102070) — readable C lift. */
void main_roll_credits(void)
{
  extern char DAT_0028b68c[];
  error(2, DAT_0028b68c);
  main_menu_load();
  FUN_000dc110();
}

/* FUN_001008a0 (0x1008a0) — readable C lift from XBE leaf.
 * Smallest (h, v) grid with h*v >= num_players (num_players in EBX). */
void FUN_001008a0(int num_players /* @<ebx> */, int *horizontal_out, int *vertical_out)
{
  extern char DAT_0028b294[];
  extern char DAT_0028b0b4[];
  int h = 1;
  int v = 1;

  if (num_players <= 0) {
    display_assert(DAT_0028b294, DAT_0028b0b4, 0x51c, true);
    system_exit(-1);
  }
  if (num_players > 1) {
    while (v * h < num_players) {
      if (h < v)
        h++;
      else {
        h = 1;
        v++;
      }
    }
  }
  *horizontal_out = h;
  *vertical_out = v;
}


/* main_movie_start (0x101bc0) — readable C lift. */
void main_movie_start(float frame_rate)
{
  void *bmp;

  if (*(int *)0x46da10 != 0) {
    display_assert((const char *)0x28b58c, (const char *)0x28b0b4, 0xa6b, true);
    system_exit(-1);
  }
  bmp = bitmap_2d_new(0x280, 0x1e0, 0, 0xa);
  *(void **)0x46da10 = bmp;
  if (!bmp)
    return;
  directory_create_or_delete_contents((const char *)0x28b584);
  *(int *)0x46da1c = 0;
  if (!(frame_rate <= *(float *)0x253f44)) {
    *(float *)0x46da20 = *(float *)0x2533c8 / frame_rate;
    game_time_set_speed(1.0f);
    return;
  }
  *(unsigned int *)0x46da20 = 0x3d088889u;
  game_time_set_speed(1.0f);
}

/* --- main.obj batch2 drafts (2026-07-26) --- */

void FUN_00054df0(void);

/* FUN_000e8e20 (0xe8e20) — XBE naked draft (batch 115). */
#if defined(__clang__)
static void (*const be8e20_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const be8e20_exitfn)(int) = system_exit;
static const char * (*const be8e20_c1ba1f0)(int tag_index) = tag_get_name;
static void * (*const be8e20_c8de70)(char *destination, const char *source, size_t size) = csstrncpy;
static char * (*const be8e20_c8d9a0)(char *s) = csstr_tolower;
static char * (*const be8e20_c1d9690)(const char *haystack, const char *needle) = crt_strstr;
static __int16 (*const be8e20_ce07c0)(__int16 a1) = player_ui_get_single_player_local_player_controller;
static void * (*const be8e20_ce84e0)(const char *name, int tag_index, int is_child, int widget_stack, int parent_tag_index, int a6, int a7) = ui_widget_load_by_name_or_tag;
static void (*const be8e20_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;

__attribute__((naked, noinline))
void FUN_000e8e20(int a0 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x100, %%esp\n\t"
      "pushl %%ebx\n\t"
      "movw 0x8(%%ebp), %%bx\n\t"
      "testw %%bx, %%bx\n\t"
      "pushl %%esi\n\t"
      "jge .LFUN_000e8e20_1\n\t"
      "pushl $1\n\t"
      "pushl $0x967\n\t"
      "pushl $0x283280\n\t"
      "pushl $0x284a90\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000e8e20_1:\n\t"
      "movl 0x326a08, %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_000e8e20_17\n\t"
      "pushl $0xff\n\t"
      "pushl %%eax\n\t"
      "call *%[c1ba1f0]\n\t"
      "addl $4, %%esp\n\t"
      "pushl %%eax\n\t"
      "leal -0x100(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c8de70]\n\t"
      "leal -0x100(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "call *%[c8d9a0]\n\t"
      "leal -0x100(%%ebp), %%edx\n\t"
      "pushl $0x284a8c\n\t"
      "pushl %%edx\n\t"
      "call *%[c1d9690]\n\t"
      "addl $0x18, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_000e8e20_2\n\t"
      "movl $0x284a54, %%esi\n\t"
      "jmp .LFUN_000e8e20_11\n\t"
      ".LFUN_000e8e20_2:\n\t"
      "leal -0x100(%%ebp), %%eax\n\t"
      "pushl $0x284a50\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d9690]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_000e8e20_3\n\t"
      "movl $0x284a18, %%esi\n\t"
      "jmp .LFUN_000e8e20_11\n\t"
      ".LFUN_000e8e20_3:\n\t"
      "leal -0x100(%%ebp), %%ecx\n\t"
      "pushl $0x284a14\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1d9690]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_000e8e20_4\n\t"
      "movl $0x2849dc, %%esi\n\t"
      "jmp .LFUN_000e8e20_11\n\t"
      ".LFUN_000e8e20_4:\n\t"
      "leal -0x100(%%ebp), %%edx\n\t"
      "pushl $0x2849d8\n\t"
      "pushl %%edx\n\t"
      "call *%[c1d9690]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_000e8e20_5\n\t"
      "movl $0x2849a0, %%esi\n\t"
      "jmp .LFUN_000e8e20_11\n\t"
      ".LFUN_000e8e20_5:\n\t"
      "leal -0x100(%%ebp), %%eax\n\t"
      "pushl $0x28499c\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d9690]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_000e8e20_6\n\t"
      "movl $0x284964, %%esi\n\t"
      "jmp .LFUN_000e8e20_11\n\t"
      ".LFUN_000e8e20_6:\n\t"
      "leal -0x100(%%ebp), %%ecx\n\t"
      "pushl $0x284960\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1d9690]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_000e8e20_7\n\t"
      "movl $0x284928, %%esi\n\t"
      "jmp .LFUN_000e8e20_11\n\t"
      ".LFUN_000e8e20_7:\n\t"
      "leal -0x100(%%ebp), %%edx\n\t"
      "pushl $0x284924\n\t"
      "pushl %%edx\n\t"
      "call *%[c1d9690]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_000e8e20_8\n\t"
      "movl $0x2848ec, %%esi\n\t"
      "jmp .LFUN_000e8e20_11\n\t"
      ".LFUN_000e8e20_8:\n\t"
      "leal -0x100(%%ebp), %%eax\n\t"
      "pushl $0x2848e8\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d9690]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_000e8e20_9\n\t"
      "movl $0x2848b0, %%esi\n\t"
      "jmp .LFUN_000e8e20_11\n\t"
      ".LFUN_000e8e20_9:\n\t"
      "leal -0x100(%%ebp), %%ecx\n\t"
      "pushl $0x2848ac\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1d9690]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_000e8e20_10\n\t"
      "movl $0x284874, %%esi\n\t"
      "jmp .LFUN_000e8e20_11\n\t"
      ".LFUN_000e8e20_10:\n\t"
      "leal -0x100(%%ebp), %%edx\n\t"
      "pushl $0x284870\n\t"
      "pushl %%edx\n\t"
      "call *%[c1d9690]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_000e8e20_16\n\t"
      "movl $0x284838, %%esi\n\t"
      ".LFUN_000e8e20_11:\n\t"
      "pushl $0\n\t"
      "call *%[ce07c0]\n\t"
      "pushl $-1\n\t"
      "pushl $-1\n\t"
      "pushl $-1\n\t"
      "pushl %%eax\n\t"
      "pushl $0\n\t"
      "pushl $-1\n\t"
      "pushl %%esi\n\t"
      "call *%[ce84e0]\n\t"
      "addl $0x20, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_000e8e20_15\n\t"
      "movl 0x34(%%eax), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_000e8e20_13\n\t"
      ".LFUN_000e8e20_12:\n\t"
      "cmpw $1, 0xe(%%esi)\n\t"
      "je .LFUN_000e8e20_14\n\t"
      "movl 0x2c(%%esi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LFUN_000e8e20_12\n\t"
      ".LFUN_000e8e20_13:\n\t"
      "pushl $1\n\t"
      "pushl $0x986\n\t"
      "pushl $0x283280\n\t"
      "pushl $0x284808\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000e8e20_14:\n\t"
      "movw %%bx, 0x40(%%esi)\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000e8e20_15:\n\t"
      "pushl $0x2847e4\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000e8e20_16:\n\t"
      "leal -0x100(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x2847a4\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $0xc, %%esp\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000e8e20_17:\n\t"
      "pushl $0x284768\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(be8e20_assert), [exitfn] "m"(be8e20_exitfn), [c1ba1f0] "m"(be8e20_c1ba1f0), [c8de70] "m"(be8e20_c8de70), [c8d9a0] "m"(be8e20_c8d9a0), [c1d9690] "m"(be8e20_c1d9690), [ce07c0] "m"(be8e20_ce07c0), [ce84e0] "m"(be8e20_ce84e0), [c8f390] "m"(be8e20_c8f390)
      : "memory");
}
#else
#error "FUN_000e8e20: clang naked draft required"
#endif


/* FUN_000ffeb0 (0xffeb0) — readable C lift. */
void FUN_000ffeb0(char param_1)
{
  if (param_1) {
    FUN_00054df0();
  }
}

/* main_framerate_render (0x102700) — XBE naked draft (batch 114). */
#if defined(__clang__)
static int (*const b102700_c1d9179)(char *str, size_t size, const char *format, ...) = snprintf;
static void (*const b102700_c19b800)(short style, short justify, int flags) = draw_string_set_style_justify_flags;
static void (*const b102700_c19b640)(const void *color) = draw_string_set_color;
static void (*const b102700_c19b7e0)(void) = (void (*)(void))FUN_0019B7E0;
static void (*const b102700_c183e60)(void *screen_pos, short *bounds, const void *color, int flags, const char *text) = rasterizer_text_draw;
static bool (*const b102700_c1bc6b0)(void) = cache_files_precache_in_progress;
static __int16 (*const b102700_c1bcf00)(float *) = cache_files_precache_map_status;

__attribute__((naked, noinline))
void main_framerate_render(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x1c, %%esp\n\t"
      "movb 0x46e004, %%al\n\t"
      "pushl %%ebx\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "cmpb %%bl, %%al\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "je .Lmain_framerate_render_5\n\t"
      "movl 0x46bd0c, %%eax\n\t"
      "movl 0x54(%%eax), %%edi\n\t"
      "cmpl $-1, %%edi\n\t"
      "je .Lmain_framerate_render_5\n\t"
      "flds 0x46da08\n\t"
      "movl 0x506584, %%ecx\n\t"
      "fcomps 0x25bb10\n\t"
      "movl 0x506588, %%edx\n\t"
      "movl %%ecx, -0x1c(%%ebp)\n\t"
      "movl %%edx, -0x18(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lmain_framerate_render_1\n\t"
      "flds 0x46da08\n\t"
      "jmp .Lmain_framerate_render_2\n\t"
      ".Lmain_framerate_render_1:\n\t"
      "flds 0x25bb10\n\t"
      ".Lmain_framerate_render_2:\n\t"
      "flds 0x2533c8\n\t"
      ".byte 0xd8, 0xf1\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fistps -0xc(%%ebp)\n\t"
      "cmpb %%bl, 0x46dd9a\n\t"
      "movl -0xc(%%ebp), %%esi\n\t"
      "je .Lmain_framerate_render_3\n\t"
      "movswl 0x46dd96, %%ecx\n\t"
      "movl $0x3c, %%eax\n\t"
      "cdq\n\t"
      "idivl %%ecx\n\t"
      "movl %%eax, %%esi\n\t"
      ".Lmain_framerate_render_3:\n\t"
      "movswl %%si, %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x25acb8\n\t"
      "leal -0x4(%%ebp), %%eax\n\t"
      "pushl $3\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d9179]\n\t"
      "movl -0x16(%%ebp), %%ecx\n\t"
      "movl -0x18(%%ebp), %%edx\n\t"
      "pushl %%ebx\n\t"
      "addl $-0x32, %%ecx\n\t"
      "addl $-0x32, %%edx\n\t"
      "pushl %%ebx\n\t"
      "pushl $-1\n\t"
      "movb %%bl, -0x1(%%ebp)\n\t"
      "movw %%cx, -0x1a(%%ebp)\n\t"
      "movw %%dx, -0x1c(%%ebp)\n\t"
      "call *%[c19b800]\n\t"
      "movl 0x2ee6d4, %%eax\n\t"
      "addl $0x1c, %%esp\n\t"
      "cmpw $0x1e, %%si\n\t"
      "jge .Lmain_framerate_render_4\n\t"
      "movl 0x2ee6d0, %%eax\n\t"
      ".Lmain_framerate_render_4:\n\t"
      "pushl %%eax\n\t"
      "call *%[c19b640]\n\t"
      "pushl %%edi\n\t"
      "call *%[c19b7e0]\n\t"
      "leal -0x4(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ebx\n\t"
      "leal -0x1c(%%ebp), %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c183e60]\n\t"
      "addl $0x1c, %%esp\n\t"
      ".Lmain_framerate_render_5:\n\t"
      "cmpb %%bl, 0x46e005\n\t"
      "je .Lmain_framerate_render_8\n\t"
      "movl 0x46bd0c, %%edx\n\t"
      "movl 0x54(%%edx), %%edi\n\t"
      "cmpl $-1, %%edi\n\t"
      "je .Lmain_framerate_render_8\n\t"
      "movl 0x506584, %%eax\n\t"
      "movl %%eax, -0x1c(%%ebp)\n\t"
      "movl 0x506588, %%eax\n\t"
      "movl %%eax, -0x18(%%ebp)\n\t"
      "movl -0x16(%%ebp), %%ecx\n\t"
      "addl $-0x32, %%eax\n\t"
      "addl $-0x32, %%ecx\n\t"
      "movw %%ax, -0x1c(%%ebp)\n\t"
      "movw %%cx, -0x1a(%%ebp)\n\t"
      "movw 0x46dddc, %%cx\n\t"
      "movswl %%cx, %%eax\n\t"
      "addl $0xe, %%eax\n\t"
      "cdq\n\t"
      "movl $0xf, %%esi\n\t"
      "idivl %%esi\n\t"
      "cmpw %%cx, %%dx\n\t"
      "je .Lmain_framerate_render_8\n\t"
      "movl %%edi, %%edi\n\t"
      ".Lmain_framerate_render_6:\n\t"
      "movswl %%dx, %%esi\n\t"
      "movswl 0x46ddde(,%%esi,2), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl $0xffffffec, %%eax\n\t"
      "addw %%ax, -0x1c(%%ebp)\n\t"
      "addw %%ax, -0x18(%%ebp)\n\t"
      "pushl $0x25acb8\n\t"
      "leal -0x8(%%ebp), %%eax\n\t"
      "pushl $3\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d9179]\n\t"
      "pushl %%ebx\n\t"
      "pushl $1\n\t"
      "pushl $-1\n\t"
      "movb %%bl, -0x5(%%ebp)\n\t"
      "call *%[c19b800]\n\t"
      "pushl %%edi\n\t"
      "call *%[c19b7e0]\n\t"
      "movl 0x2ee6c4, %%eax\n\t"
      "addl $0x20, %%esp\n\t"
      "cmpw $2, 0x46ddde(,%%esi,2)\n\t"
      "je .Lmain_framerate_render_7\n\t"
      "movl 0x2ee6d0, %%eax\n\t"
      ".Lmain_framerate_render_7:\n\t"
      "pushl %%eax\n\t"
      "call *%[c19b640]\n\t"
      "leal -0x8(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ebx\n\t"
      "leal -0x1c(%%ebp), %%edx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edx\n\t"
      "call *%[c183e60]\n\t"
      "leal 0xe(%%esi), %%eax\n\t"
      "cdq\n\t"
      "movl $0xf, %%ecx\n\t"
      "idivl %%ecx\n\t"
      "addl $0x18, %%esp\n\t"
      "cmpw 0x46dddc, %%dx\n\t"
      "jne .Lmain_framerate_render_6\n\t"
      ".Lmain_framerate_render_8:\n\t"
      "cmpb %%bl, 0x46e006\n\t"
      "je .Lmain_framerate_render_9\n\t"
      "call *%[c1bc6b0]\n\t"
      "testb %%al, %%al\n\t"
      "je .Lmain_framerate_render_9\n\t"
      "movl 0x46bd0c, %%edx\n\t"
      "movl 0x54(%%edx), %%esi\n\t"
      "cmpl $-1, %%esi\n\t"
      "je .Lmain_framerate_render_9\n\t"
      "leal -0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1bcf00]\n\t"
      "addl $4, %%esp\n\t"
      "testw %%ax, %%ax\n\t"
      "jne .Lmain_framerate_render_9\n\t"
      "flds -0x8(%%ebp)\n\t"
      "movl 0x506584, %%ecx\n\t"
      "fmuls 0x253f00\n\t"
      "movl 0x506588, %%edx\n\t"
      "movl %%ecx, -0x1c(%%ebp)\n\t"
      "movl %%edx, -0x18(%%ebp)\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fistps -0x10(%%ebp)\n\t"
      "movswl -0x10(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x25acb8\n\t"
      "leal -0x4(%%ebp), %%ecx\n\t"
      "pushl $3\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1d9179]\n\t"
      "movl -0x16(%%ebp), %%edx\n\t"
      "movl -0x18(%%ebp), %%eax\n\t"
      "pushl %%ebx\n\t"
      "addl $-0x32, %%edx\n\t"
      "addl $-0x64, %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl $-1\n\t"
      "movb %%bl, -0x1(%%ebp)\n\t"
      "movw %%dx, -0x1a(%%ebp)\n\t"
      "movw %%ax, -0x1c(%%ebp)\n\t"
      "call *%[c19b800]\n\t"
      "movl 0x2ee6f4, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c19b640]\n\t"
      "pushl %%esi\n\t"
      "call *%[c19b7e0]\n\t"
      "leal -0x4(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ebx\n\t"
      "leal -0x1c(%%ebp), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "call *%[c183e60]\n\t"
      "addl $0x38, %%esp\n\t"
      ".Lmain_framerate_render_9:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c1d9179] "m"(b102700_c1d9179), [c19b800] "m"(b102700_c19b800), [c19b640] "m"(b102700_c19b640), [c19b7e0] "m"(b102700_c19b7e0), [c183e60] "m"(b102700_c183e60), [c1bc6b0] "m"(b102700_c1bc6b0), [c1bcf00] "m"(b102700_c1bcf00)
      : "memory");
}
#else
#error "main_framerate_render: clang naked draft required"
#endif


/* FUN_001034b0 (0x1034b0) — readable C lift. */
void FUN_001034b0(int *obj)
{
  array_new(obj, 0xc);
  array_new((int *)((char *)obj + 0xc), 0x1c);
  array_new((int *)((char *)obj + 0x18), 0x18);
}

/* FUN_00103600 (0x103600) — XBE naked draft (batch 135). */
#if defined(__clang__)
static int (*const b103600_c117ee0)(int *array, int index, int element_size) = FUN_00117ee0;
static int (*const b103600_c117da0)(int *array) = FUN_00117da0;

__attribute__((naked, noinline))
int FUN_00103600(int *array __attribute__((unused)), float *vec __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "movl 0x4(%%esi), %%eax\n\t"
      "pushl %%edi\n\t"
      "xorl %%edi, %%edi\n\t"
      "testl %%eax, %%eax\n\t"
      "jle .LFUN_00103600_3\n\t"
      "movl %%edi, %%edi\n\t"
      ".LFUN_00103600_1:\n\t"
      "pushl $0xc\n\t"
      "pushl %%edi\n\t"
      "pushl %%esi\n\t"
      "call *%[c117ee0]\n\t"
      "flds (%%ebx)\n\t"
      "fsubs (%%eax)\n\t"
      "addl $0xc, %%esp\n\t"
      "fabs\n\t"
      "fcompl 0x2549d8\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00103600_2\n\t"
      "flds 0x4(%%ebx)\n\t"
      "pushl $0xc\n\t"
      "pushl %%edi\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "pushl %%esi\n\t"
      "call *%[c117ee0]\n\t"
      "flds 0x4(%%eax)\n\t"
      "fsubrs -0x4(%%ebp)\n\t"
      "addl $0xc, %%esp\n\t"
      "fabs\n\t"
      "fcompl 0x2549d8\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00103600_2\n\t"
      "flds 0x8(%%ebx)\n\t"
      "pushl $0xc\n\t"
      "pushl %%edi\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "pushl %%esi\n\t"
      "call *%[c117ee0]\n\t"
      "flds 0x8(%%eax)\n\t"
      "fsubrs -0x4(%%ebp)\n\t"
      "addl $0xc, %%esp\n\t"
      "fabs\n\t"
      "fcompl 0x2549d8\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .LFUN_00103600_3\n\t"
      ".LFUN_00103600_2:\n\t"
      "movl 0x4(%%esi), %%eax\n\t"
      "incl %%edi\n\t"
      "cmpl %%eax, %%edi\n\t"
      "jl .LFUN_00103600_1\n\t"
      ".LFUN_00103600_3:\n\t"
      "cmpl 0x4(%%esi), %%edi\n\t"
      "jne .LFUN_00103600_4\n\t"
      "pushl %%esi\n\t"
      "call *%[c117da0]\n\t"
      "movl %%eax, %%edi\n\t"
      "addl $4, %%esp\n\t"
      "cmpl $-1, %%edi\n\t"
      "je .LFUN_00103600_4\n\t"
      "pushl $0xc\n\t"
      "pushl %%edi\n\t"
      "pushl %%esi\n\t"
      "call *%[c117ee0]\n\t"
      "movl (%%ebx), %%ecx\n\t"
      "movl %%ecx, (%%eax)\n\t"
      "movl 0x4(%%ebx), %%edx\n\t"
      "movl %%edx, 0x4(%%eax)\n\t"
      "movl 0x8(%%ebx), %%ecx\n\t"
      "addl $0xc, %%esp\n\t"
      "movl %%ecx, 0x8(%%eax)\n\t"
      ".LFUN_00103600_4:\n\t"
      "movl %%edi, %%eax\n\t"
      "popl %%edi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c117ee0] "m"(b103600_c117ee0), [c117da0] "m"(b103600_c117da0)
      : "memory");
}
#else
#error "FUN_00103600: clang naked draft required"
#endif


/* FUN_001036c0 (0x1036c0) — XBE naked draft (batch 126). */
#if defined(__clang__)
static int (*const b1036c0_c117ee0)(int *array, int index, int element_size) = FUN_00117ee0;
static int (*const b1036c0_c117da0)(int *array) = FUN_00117da0;
static void (*const b1036c0_c117b20)(int *table, int element_size) = array_new;

__attribute__((naked, noinline))
int FUN_001036c0(int *base __attribute__((unused)), int a __attribute__((unused)), int b __attribute__((unused)), int flag __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl 0x10(%%ebx), %%eax\n\t"
      "pushl %%esi\n\t"
      "xorl %%esi, %%esi\n\t"
      "testl %%eax, %%eax\n\t"
      "pushl %%edi\n\t"
      "jle .LFUN_001036c0_6\n\t"
      ".LFUN_001036c0_1:\n\t"
      "pushl $0x1c\n\t"
      "leal 0xc(%%ebx), %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "call *%[c117ee0]\n\t"
      "movl 0xc(%%eax), %%ecx\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl %%edx, %%ecx\n\t"
      "jne .LFUN_001036c0_2\n\t"
      "movl 0x10(%%eax), %%edi\n\t"
      "cmpl 0x10(%%ebp), %%edi\n\t"
      "je .LFUN_001036c0_4\n\t"
      ".LFUN_001036c0_2:\n\t"
      "cmpl 0x10(%%ebp), %%ecx\n\t"
      "jne .LFUN_001036c0_3\n\t"
      "cmpl %%edx, 0x10(%%eax)\n\t"
      "je .LFUN_001036c0_5\n\t"
      ".LFUN_001036c0_3:\n\t"
      "movl 0x10(%%ebx), %%eax\n\t"
      "incl %%esi\n\t"
      "cmpl %%eax, %%esi\n\t"
      "jl .LFUN_001036c0_1\n\t"
      "jmp .LFUN_001036c0_6\n\t"
      ".LFUN_001036c0_4:\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "jmp .LFUN_001036c0_6\n\t"
      ".LFUN_001036c0_5:\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      ".LFUN_001036c0_6:\n\t"
      "cmpl 0x10(%%ebx), %%esi\n\t"
      "jne .LFUN_001036c0_7\n\t"
      "leal 0xc(%%ebx), %%edi\n\t"
      "pushl %%edi\n\t"
      "call *%[c117da0]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $4, %%esp\n\t"
      "cmpl $-1, %%esi\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "je .LFUN_001036c0_8\n\t"
      "pushl $0x1c\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c117ee0]\n\t"
      "movl %%eax, %%edi\n\t"
      "pushl $4\n\t"
      "pushl %%edi\n\t"
      "call *%[c117b20]\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "addl $0x14, %%esp\n\t"
      "movl %%eax, 0xc(%%edi)\n\t"
      "movl %%ecx, 0x10(%%edi)\n\t"
      ".LFUN_001036c0_7:\n\t"
      "cmpl $-1, %%esi\n\t"
      "je .LFUN_001036c0_8\n\t"
      "pushl $0x1c\n\t"
      "pushl %%esi\n\t"
      "addl $0xc, %%ebx\n\t"
      "pushl %%ebx\n\t"
      "call *%[c117ee0]\n\t"
      "movl %%eax, %%edi\n\t"
      "pushl %%edi\n\t"
      "call *%[c117da0]\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_001036c0_8\n\t"
      "pushl $4\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "call *%[c117ee0]\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "movl %%edx, (%%eax)\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001036c0_9\n\t"
      "orl $0x80000000, %%esi\n\t"
      "popl %%edi\n\t"
      "movl %%esi, %%eax\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001036c0_8:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "orl $0xffffffff, %%eax\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001036c0_9:\n\t"
      "andl $0x7fffffff, %%esi\n\t"
      "popl %%edi\n\t"
      "movl %%esi, %%eax\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c117ee0] "m"(b1036c0_c117ee0), [c117da0] "m"(b1036c0_c117da0), [c117b20] "m"(b1036c0_c117b20)
      : "memory");
}
#else
#error "FUN_001036c0: clang naked draft required"
#endif


float *FUN_001037b0(float *out, float *p0, float *p1, float *p2)
{
  float e1[3];
  float e2[3];

  e1[0] = p1[0] - p0[0];
  e1[1] = p1[1] - p0[1];
  e1[2] = p1[2] - p0[2];
  e2[0] = p2[0] - p0[0];
  e2[1] = p2[1] - p0[1];
  e2[2] = p2[2] - p0[2];
  out[0] = e1[1] * e2[2] - e1[2] * e2[1];
  out[1] = e1[2] * e2[0] - e1[0] * e2[2];
  out[2] = e1[0] * e2[1] - e1[1] * e2[0];
  normalize3d(out);
  if (out[0] * out[0] + out[1] * out[1] + out[2] * out[2] <= *(float *)0x2533c0) {
    out[3] = 0.0f;
    return 0;
  }
  out[3] = out[0] * p0[0] + out[1] * p0[1] + out[2] * p0[2];
  return out;
}

/* FUN_00103860 (0x103860) — XBE naked draft (batch 118). */
#if defined(__clang__)
static int (*const b103860_c117da0)(int *array) = FUN_00117da0;
static int (*const b103860_c117ee0)(int *array, int index, int element_size) = FUN_00117ee0;
static int (*const b103860_c103600)(int *array, float *vec) = FUN_00103600;
static int (*const b103860_c1036c0)(int *base, int a, int b, int flag) = FUN_001036c0;
static void *(*const b103860_memset)(void *, int, unsigned int) = csmemset;
static void (*const b103860_c104040)(float *p0, float *p1, float *p2, float *color) = FUN_00104040;
static void (*const b103860_c1db443)(void) = (void (*)(void))_wprintf;

__attribute__((naked, noinline))
int FUN_00103860(int base __attribute__((unused)), float *a __attribute__((unused)), float *b __attribute__((unused)), float *c __attribute__((unused)), char flag __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x18, %%esp\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "pushl %%edi\n\t"
      "leal 0x18(%%esi), %%edi\n\t"
      "pushl %%edi\n\t"
      "call *%[c117da0]\n\t"
      "addl $4, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "je .LFUN_00103860_12\n\t"
      "pushl %%ebx\n\t"
      "pushl $0x18\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "call *%[c117ee0]\n\t"
      "movl 0xc(%%ebp), %%ebx\n\t"
      "addl $0xc, %%esp\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "call *%[c103600]\n\t"
      "movl 0x10(%%ebp), %%ebx\n\t"
      "movl %%eax, %%edi\n\t"
      "movl %%edi, -0x18(%%ebp)\n\t"
      "call *%[c103600]\n\t"
      "movl 0x14(%%ebp), %%ebx\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "call *%[c103600]\n\t"
      "orl $0xffffffff, %%ecx\n\t"
      "cmpl %%ecx, %%edi\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "je .LFUN_00103860_1\n\t"
      "cmpl %%ecx, -0x14(%%ebp)\n\t"
      "je .LFUN_00103860_1\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jne .LFUN_00103860_2\n\t"
      ".LFUN_00103860_1:\n\t"
      "movl %%ecx, -0x4(%%ebp)\n\t"
      ".LFUN_00103860_2:\n\t"
      "movl -0xc(%%ebp), %%ebx\n\t"
      "leal -0x18(%%ebp), %%edi\n\t"
      "movl $1, %%esi\n\t"
      "subl %%ebx, %%edi\n\t"
      "movl $3, -0x8(%%ebp)\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".LFUN_00103860_3:\n\t"
      "movl %%esi, %%eax\n\t"
      "cdq\n\t"
      "movl $3, %%ecx\n\t"
      "idivl %%ecx\n\t"
      "movl (%%edi,%%ebx,1), %%eax\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movl -0x18(%%ebp,%%edx,4), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1036c0]\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "movl %%eax, (%%ebx)\n\t"
      "jne .LFUN_00103860_4\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      ".LFUN_00103860_4:\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "incl %%esi\n\t"
      "addl $4, %%ebx\n\t"
      "decl %%eax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "jne .LFUN_00103860_3\n\t"
      "movl -0xc(%%ebp), %%edi\n\t"
      "pushl $8\n\t"
      "leal 0x10(%%edi), %%edx\n\t"
      "pushl $0\n\t"
      "pushl %%edx\n\t"
      "movl $0xffffffff, 0xc(%%edi)\n\t"
      "call *%[memset]\n\t"
      "movb 0x18(%%ebp), %%al\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00103860_11\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl 0x1c(%%eax), %%edx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "decl %%edx\n\t"
      "testl %%edx, %%edx\n\t"
      "movl %%ecx, -0xc(%%ebp)\n\t"
      "jle .LFUN_00103860_11\n\t"
      ".LFUN_00103860_5:\n\t"
      "pushl $0x18\n\t"
      "pushl %%ecx\n\t"
      "addl $0x18, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c117ee0]\n\t"
      "addl $0xc, %%esp\n\t"
      "xorl %%esi, %%esi\n\t"
      ".LFUN_00103860_6:\n\t"
      "movswl %%si, %%edx\n\t"
      "movl (%%edi,%%edx,4), %%edx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "andl $0x7fffffff, %%edx\n\t"
      ".LFUN_00103860_7:\n\t"
      "movswl %%cx, %%ebx\n\t"
      "movl (%%eax,%%ebx,4), %%ebx\n\t"
      "andl $0x7fffffff, %%ebx\n\t"
      "cmpl %%edx, %%ebx\n\t"
      "je .LFUN_00103860_8\n\t"
      "incl %%ecx\n\t"
      "cmpw $3, %%cx\n\t"
      "jl .LFUN_00103860_7\n\t"
      ".LFUN_00103860_8:\n\t"
      "cmpw $3, %%cx\n\t"
      "je .LFUN_00103860_10\n\t"
      "incl %%esi\n\t"
      "cmpw $3, %%si\n\t"
      "jl .LFUN_00103860_6\n\t"
      "movl 0x2ee6f0, %%eax\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "pushl %%eax\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c104040]\n\t"
      "movb 0x46e393, %%al\n\t"
      "addl $0x10, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00103860_9\n\t"
      "pushl $0x28b780\n\t"
      "call *%[c1db443]\n\t"
      "addl $4, %%esp\n\t"
      "movb $1, 0x46e393\n\t"
      ".LFUN_00103860_9:\n\t"
      "popl %%ebx\n\t"
      "popl %%edi\n\t"
      "orl $0xffffffff, %%eax\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00103860_10:\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl 0x1c(%%eax), %%edx\n\t"
      "incl %%ecx\n\t"
      "decl %%edx\n\t"
      "cmpl %%edx, %%ecx\n\t"
      "movl %%ecx, -0xc(%%ebp)\n\t"
      "jl .LFUN_00103860_5\n\t"
      ".LFUN_00103860_11:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "popl %%ebx\n\t"
      ".LFUN_00103860_12:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c117da0] "m"(b103860_c117da0), [c117ee0] "m"(b103860_c117ee0), [c103600] "m"(b103860_c103600), [c1036c0] "m"(b103860_c1036c0), [memset] "m"(b103860_memset), [c104040] "m"(b103860_c104040), [c1db443] "m"(b103860_c1db443)
      : "memory");
}
#else
#error "FUN_00103860: clang naked draft required"
#endif


/* FUN_00103a00 (0x103a00) — XBE naked draft (batch 119). */
#if defined(__clang__)
static int (*const b103a00_c117ee0)(int *array, int index, int element_size) = FUN_00117ee0;
static float * (*const b103a00_c1037b0)(float *out, float *p0, float *p1, float *p2) = FUN_001037b0;

__attribute__((naked, noinline))
char FUN_00103a00(uint32_t mark __attribute__((unused)), int base __attribute__((unused)), uint32_t *node __attribute__((unused)), uint32_t plane_arg __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x10, %%esp\n\t"
      "pushl %%ebx\n\t"
      "movl 0xc(%%ebp), %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x10(%%ebp), %%esi\n\t"
      "movl (%%esi), %%ecx\n\t"
      "pushl %%edi\n\t"
      "pushl $0xc\n\t"
      "pushl $0x1c\n\t"
      "andl $0x7fffffff, %%ecx\n\t"
      "leal 0xc(%%ebx), %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "call *%[c117ee0]\n\t"
      "movl (%%esi), %%edx\n\t"
      "andl $0x80000000, %%edx\n\t"
      "addl $0xc, %%esp\n\t"
      "negl %%edx\n\t"
      "sbbl %%edx, %%edx\n\t"
      "negl %%edx\n\t"
      "movl 0xc(%%eax,%%edx,4), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "call *%[c117ee0]\n\t"
      "movl 0x4(%%esi), %%ecx\n\t"
      "addl $0xc, %%esp\n\t"
      "pushl $0xc\n\t"
      "pushl $0x1c\n\t"
      "andl $0x7fffffff, %%ecx\n\t"
      "movl %%eax, %%edi\n\t"
      "pushl %%ecx\n\t"
      "leal 0xc(%%ebx), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c117ee0]\n\t"
      "movl 0x4(%%esi), %%edx\n\t"
      "andl $0x80000000, %%edx\n\t"
      "addl $0xc, %%esp\n\t"
      "negl %%edx\n\t"
      "sbbl %%edx, %%edx\n\t"
      "negl %%edx\n\t"
      "movl 0xc(%%eax,%%edx,4), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "call *%[c117ee0]\n\t"
      "movl 0x8(%%esi), %%ecx\n\t"
      "addl $0xc, %%esp\n\t"
      "pushl $0xc\n\t"
      "pushl $0x1c\n\t"
      "andl $0x7fffffff, %%ecx\n\t"
      "movl %%eax, 0xc(%%ebp)\n\t"
      "pushl %%ecx\n\t"
      "leal 0xc(%%ebx), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c117ee0]\n\t"
      "movl 0x8(%%esi), %%edx\n\t"
      "andl $0x80000000, %%edx\n\t"
      "addl $0xc, %%esp\n\t"
      "negl %%edx\n\t"
      "sbbl %%edx, %%edx\n\t"
      "negl %%edx\n\t"
      "movl 0xc(%%eax,%%edx,4), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "call *%[c117ee0]\n\t"
      "flds 0x4(%%edi)\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "fmuls 0x4(%%esi)\n\t"
      "movl %%eax, %%ecx\n\t"
      "flds 0x8(%%edi)\n\t"
      "addl $0xc, %%esp\n\t"
      "fmuls 0x8(%%esi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds (%%edi)\n\t"
      "fmuls (%%esi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fsubs 0xc(%%esi)\n\t"
      "fabs\n\t"
      "fcompl 0x28b800\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00103a00_1\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "flds 0x4(%%edx)\n\t"
      "fmuls 0x4(%%esi)\n\t"
      "flds 0x8(%%edx)\n\t"
      "fmuls 0x8(%%esi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds (%%edx)\n\t"
      "fmuls (%%esi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fsubs 0xc(%%esi)\n\t"
      "fabs\n\t"
      "fcompl 0x28b800\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00103a00_1\n\t"
      "flds 0x4(%%ecx)\n\t"
      "fmuls 0x4(%%esi)\n\t"
      "flds 0x8(%%ecx)\n\t"
      "fmuls 0x8(%%esi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds (%%ecx)\n\t"
      "fmuls (%%esi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fsubs 0xc(%%esi)\n\t"
      "fabs\n\t"
      "fcompl 0x28b800\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00103a00_1\n\t"
      "pushl %%edx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x10(%%ebp), %%ecx\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1037b0]\n\t"
      "addl $0x10, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_00103a00_1\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fmuls (%%esi)\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fmuls 0x8(%%esi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fmuls 0x4(%%esi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00103a00_1\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00103a00_1:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c117ee0] "m"(b103a00_c117ee0), [c1037b0] "m"(b103a00_c1037b0)
      : "memory");
}
#else
#error "FUN_00103a00: clang naked draft required"
#endif


/* FUN_00103c00 (0x103c00) — XBE naked draft (batch 125). */
#if defined(__clang__)
static int (*const b103c00_c117ee0)(int *array, int index, int element_size) = FUN_00117ee0;
static float * (*const b103c00_c1037b0)(float *out, float *p0, float *p1, float *p2) = FUN_001037b0;
static void (*const b103c00_c103530)(int base, char (*visit)(uint32_t, int, uint32_t *, uint32_t), uint32_t visit_arg, uint32_t mark, int node_index) = FUN_00103530;

__attribute__((naked, noinline))
int FUN_00103c00(int *obj __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x18, %%esp\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "movl 0x1c(%%edi), %%ecx\n\t"
      "xorl %%eax, %%eax\n\t"
      "cmpl %%eax, %%ecx\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "jle .LFUN_00103c00_3\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "leal 0xc(%%edi), %%ebx\n\t"
      ".LFUN_00103c00_1:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "pushl $0x18\n\t"
      "pushl %%eax\n\t"
      "leal 0x18(%%edi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c117ee0]\n\t"
      "addl $0xc, %%esp\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x4(%%esi), %%ecx\n\t"
      "pushl $0xc\n\t"
      "pushl $0x1c\n\t"
      "andl $0x7fffffff, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "call *%[c117ee0]\n\t"
      "movl 0x4(%%esi), %%edx\n\t"
      "andl $0x80000000, %%edx\n\t"
      "addl $0xc, %%esp\n\t"
      "negl %%edx\n\t"
      "sbbl %%edx, %%edx\n\t"
      "negl %%edx\n\t"
      "movl 0xc(%%eax,%%edx,4), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "call *%[c117ee0]\n\t"
      "movl 0x8(%%esi), %%ecx\n\t"
      "addl $0xc, %%esp\n\t"
      "pushl %%eax\n\t"
      "pushl $0xc\n\t"
      "pushl $0x1c\n\t"
      "andl $0x7fffffff, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "call *%[c117ee0]\n\t"
      "movl 0x8(%%esi), %%edx\n\t"
      "andl $0x80000000, %%edx\n\t"
      "addl $0xc, %%esp\n\t"
      "negl %%edx\n\t"
      "sbbl %%edx, %%edx\n\t"
      "negl %%edx\n\t"
      "movl 0xc(%%eax,%%edx,4), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "call *%[c117ee0]\n\t"
      "movl (%%esi), %%ecx\n\t"
      "addl $0xc, %%esp\n\t"
      "pushl %%eax\n\t"
      "pushl $0xc\n\t"
      "pushl $0x1c\n\t"
      "andl $0x7fffffff, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "call *%[c117ee0]\n\t"
      "movl (%%esi), %%edx\n\t"
      "andl $0x80000000, %%edx\n\t"
      "addl $0xc, %%esp\n\t"
      "negl %%edx\n\t"
      "sbbl %%edx, %%edx\n\t"
      "negl %%edx\n\t"
      "movl 0xc(%%eax,%%edx,4), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "call *%[c117ee0]\n\t"
      "addl $0xc, %%esp\n\t"
      "pushl %%eax\n\t"
      "leal -0x18(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1037b0]\n\t"
      "movl 0xc(%%esi), %%eax\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "jne .LFUN_00103c00_2\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "movl -0x8(%%ebp), %%esi\n\t"
      "pushl %%edx\n\t"
      "pushl %%esi\n\t"
      "leal -0x18(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x103a00\n\t"
      "pushl %%edi\n\t"
      "call *%[c103530]\n\t"
      "addl $0x14, %%esp\n\t"
      "incl %%esi\n\t"
      "movl %%esi, -0x8(%%ebp)\n\t"
      ".LFUN_00103c00_2:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movl 0x1c(%%edi), %%ecx\n\t"
      "incl %%eax\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "jl .LFUN_00103c00_1\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      ".LFUN_00103c00_3:\n\t"
      "popl %%edi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c117ee0] "m"(b103c00_c117ee0), [c1037b0] "m"(b103c00_c1037b0), [c103530] "m"(b103c00_c103530)
      : "memory");
}
#else
#error "FUN_00103c00: clang naked draft required"
#endif


/* FUN_00103d80 (0x103d80) — readable C lift from XBE leaf.
 * Assert error_geometry_file is null, then CRT helper with arg 0x31fac8.
 * Must be a direct CALL (not call [mem]) so Unicorn can stub FUN_001db4a9. */
void FUN_00103d80(void)
{
  extern char DAT_0028b81c[];
  extern char DAT_0028b838[];

  if (*(int *)0x46e394 != 0) {
    display_assert(DAT_0028b81c, DAT_0028b838, 0x44, true);
    system_exit(-1);
  }
#if defined(__clang__)
  __asm__ __volatile__(
      "pushl $0x31fac8\n\t"
      "call _FUN_001db4a9\n\t"
      "addl $4, %%esp\n\t"
      :
      :
      : "memory");
#else
  ((void (*)(void *))FUN_001db4a9)((void *)0x31fac8);
#endif
}




static __attribute__((unused)) void error_geometry_assert_null(const char *name, int line)
{
  display_assert((char *)name, (char *)0x28b838, line, 1);
  system_exit(-1);
}

/* FUN_00103e80 (0x103e80) — XBE naked draft (batch 123). */
#if defined(__clang__)
static void (*const b103e80_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b103e80_exitfn)(int) = system_exit;
static bool (*const b103e80_c103d30)(void) = FUN_00103d30;
static void (*const b103e80_xfrmpt)(float *, float *, float *) = matrix_transform_point;
static int (*const b103e80_c1d98ad)(void *stream, const char *format, ...) = crt_fprintf;
static int (*const b103e80_c1d9bd2)(void *stream) = crt_fflush;

__attribute__((naked, noinline))
void FUN_00103e80(float *p0 __attribute__((unused)), float *p1 __attribute__((unused)), float *color __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x18, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .LFUN_00103e80_1\n\t"
      "pushl $1\n\t"
      "pushl $0x8f\n\t"
      "pushl $0x28b838\n\t"
      "pushl $0x28b948\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00103e80_1:\n\t"
      "movl 0xc(%%ebp), %%ebx\n\t"
      "testl %%ebx, %%ebx\n\t"
      "jne .LFUN_00103e80_2\n\t"
      "pushl $1\n\t"
      "pushl $0x90\n\t"
      "pushl $0x28b838\n\t"
      "pushl $0x28b944\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00103e80_2:\n\t"
      "movl 0x10(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LFUN_00103e80_3\n\t"
      "pushl $1\n\t"
      "pushl $0x91\n\t"
      "pushl $0x28b838\n\t"
      "pushl $0x269fd8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00103e80_3:\n\t"
      "call *%[c103d30]\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00103e80_4\n\t"
      "leal -0x18(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl $0x31fb08\n\t"
      "call *%[xfrmpt]\n\t"
      "leal -0xc(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl $0x31fb08\n\t"
      "call *%[xfrmpt]\n\t"
      "movl 0x46e394, %%edx\n\t"
      "pushl $0x28b934\n\t"
      "pushl %%edx\n\t"
      "call *%[c1d98ad]\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fmuls 0x253f00\n\t"
      "movl 0x46e394, %%eax\n\t"
      "subl $0x10, %%esp\n\t"
      "fstpl 0x28(%%esp)\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fmuls 0x253f00\n\t"
      "fstpl 0x20(%%esp)\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fmuls 0x253f00\n\t"
      "fstpl 0x18(%%esp)\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fmuls 0x253f00\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fmuls 0x253f00\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fmuls 0x253f00\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x28b908\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d98ad]\n\t"
      "movl 0x46e394, %%ecx\n\t"
      "pushl $0x28b8e0\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1d98ad]\n\t"
      "flds 0x2533c8\n\t"
      "fsubs (%%esi)\n\t"
      "movl 0x46e394, %%edx\n\t"
      "addl $0x40, %%esp\n\t"
      "subl $0x40, %%esp\n\t"
      "fstl 0x38(%%esp)\n\t"
      "fstpl 0x30(%%esp)\n\t"
      "flds 0xc(%%esi)\n\t"
      "fstpl 0x28(%%esp)\n\t"
      "flds 0x8(%%esi)\n\t"
      "fstpl 0x20(%%esp)\n\t"
      "flds 0x4(%%esi)\n\t"
      "fstpl 0x18(%%esp)\n\t"
      "flds 0xc(%%esi)\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds 0x8(%%esi)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds 0x4(%%esi)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x28b898\n\t"
      "pushl %%edx\n\t"
      "call *%[c1d98ad]\n\t"
      "movl 0x46e394, %%eax\n\t"
      "pushl $0x28b86c\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d98ad]\n\t"
      "movl 0x46e394, %%ecx\n\t"
      "addl $0x50, %%esp\n\t"
      "pushl $0x28b868\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1d98ad]\n\t"
      "movl 0x46e394, %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c1d9bd2]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_00103e80_4:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b103e80_assert), [exitfn] "m"(b103e80_exitfn), [c103d30] "m"(b103e80_c103d30), [xfrmpt] "m"(b103e80_xfrmpt), [c1d98ad] "m"(b103e80_c1d98ad), [c1d9bd2] "m"(b103e80_c1d9bd2)
      : "memory");
}
#else
#error "FUN_00103e80: clang naked draft required"
#endif


/* FUN_00104040 (0x104040) — XBE naked draft (batch 120). */
#if defined(__clang__)
static void (*const b104040_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b104040_exitfn)(int) = system_exit;
static bool (*const b104040_c103d30)(void) = FUN_00103d30;
static void (*const b104040_xfrmpt)(float *, float *, float *) = matrix_transform_point;
static int (*const b104040_c1d98ad)(void *stream, const char *format, ...) = crt_fprintf;
static int (*const b104040_c1d9bd2)(void *stream) = crt_fflush;

__attribute__((naked, noinline))
void FUN_00104040(float *p0 __attribute__((unused)), float *p1 __attribute__((unused)), float *p2 __attribute__((unused)), float *color __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x24, %%esp\n\t"
      "pushl %%ebx\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "testl %%ebx, %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "jne .LFUN_00104040_1\n\t"
      "pushl $1\n\t"
      "pushl $0xb1\n\t"
      "pushl $0x28b838\n\t"
      "pushl $0x28b948\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00104040_1:\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_00104040_2\n\t"
      "pushl $1\n\t"
      "pushl $0xb2\n\t"
      "pushl $0x28b838\n\t"
      "pushl $0x28b944\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00104040_2:\n\t"
      "movl 0x10(%%ebp), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .LFUN_00104040_3\n\t"
      "pushl $1\n\t"
      "pushl $0xb3\n\t"
      "pushl $0x28b838\n\t"
      "pushl $0x28ba10\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00104040_3:\n\t"
      "movl 0x14(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LFUN_00104040_4\n\t"
      "pushl $1\n\t"
      "pushl $0xb4\n\t"
      "pushl $0x28b838\n\t"
      "pushl $0x269fd8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00104040_4:\n\t"
      "call *%[c103d30]\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00104040_5\n\t"
      "leal -0x24(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl $0x31fb08\n\t"
      "call *%[xfrmpt]\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "leal -0x18(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x31fb08\n\t"
      "call *%[xfrmpt]\n\t"
      "leal -0xc(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl $0x31fb08\n\t"
      "call *%[xfrmpt]\n\t"
      "movl 0x46e394, %%ecx\n\t"
      "pushl $0x28b934\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1d98ad]\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fmuls 0x253f00\n\t"
      "subl $0x1c, %%esp\n\t"
      "movl 0x46e394, %%edx\n\t"
      "fstpl 0x40(%%esp)\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fmuls 0x253f00\n\t"
      "fstpl 0x38(%%esp)\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fmuls 0x253f00\n\t"
      "fstpl 0x30(%%esp)\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fmuls 0x253f00\n\t"
      "fstpl 0x28(%%esp)\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fmuls 0x253f00\n\t"
      "fstpl 0x20(%%esp)\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fmuls 0x253f00\n\t"
      "fstpl 0x18(%%esp)\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fmuls 0x253f00\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds -0x20(%%ebp)\n\t"
      "fmuls 0x253f00\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds -0x24(%%ebp)\n\t"
      "fmuls 0x253f00\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x28b9d8\n\t"
      "pushl %%edx\n\t"
      "call *%[c1d98ad]\n\t"
      "movl 0x46e394, %%eax\n\t"
      "pushl $0x28b9b0\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d98ad]\n\t"
      "flds 0x2533c8\n\t"
      "fsubs (%%esi)\n\t"
      "movl 0x46e394, %%ecx\n\t"
      "addl $0x58, %%esp\n\t"
      "subl $0x20, %%esp\n\t"
      "fstpl 0x18(%%esp)\n\t"
      "flds 0xc(%%esi)\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds 0x8(%%esi)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds 0x4(%%esi)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x28b978\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1d98ad]\n\t"
      "movl 0x46e394, %%edx\n\t"
      "pushl $0x28b94c\n\t"
      "pushl %%edx\n\t"
      "call *%[c1d98ad]\n\t"
      "movl 0x46e394, %%eax\n\t"
      "pushl $0x28b868\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d98ad]\n\t"
      "movl 0x46e394, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1d9bd2]\n\t"
      "addl $0x3c, %%esp\n\t"
      ".LFUN_00104040_5:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b104040_assert), [exitfn] "m"(b104040_exitfn), [c103d30] "m"(b104040_c103d30), [xfrmpt] "m"(b104040_xfrmpt), [c1d98ad] "m"(b104040_c1d98ad), [c1d9bd2] "m"(b104040_c1d9bd2)
      : "memory");
}
#else
#error "FUN_00104040: clang naked draft required"
#endif


/* FUN_00104240 (0x104240) — XBE naked draft (batch 118). */
#if defined(__clang__)
static void (*const b104240_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b104240_exitfn)(int) = system_exit;
static bool (*const b104240_c103d30)(void) = FUN_00103d30;
static int (*const b104240_c1d98ad)(void *stream, const char *format, ...) = crt_fprintf;
static void (*const b104240_xfrmpt)(float *, float *, float *) = matrix_transform_point;
static int (*const b104240_c1d9bd2)(void *stream) = crt_fflush;

__attribute__((naked, noinline))
void FUN_00104240(int point_count __attribute__((unused)), float *points __attribute__((unused)), float *color __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xc, %%esp\n\t"
      "pushl %%ebx\n\t"
      "movw 0x8(%%ebp), %%bx\n\t"
      "testw %%bx, %%bx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "jge .LFUN_00104240_1\n\t"
      "pushl $1\n\t"
      "pushl $0xd3\n\t"
      "pushl $0x28b838\n\t"
      "pushl $0x28ba78\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00104240_1:\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .LFUN_00104240_2\n\t"
      "pushl $1\n\t"
      "pushl $0xd4\n\t"
      "pushl $0x28b838\n\t"
      "pushl $0x28ba70\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00104240_2:\n\t"
      "movl 0x10(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LFUN_00104240_3\n\t"
      "pushl $1\n\t"
      "pushl $0xd5\n\t"
      "pushl $0x28b838\n\t"
      "pushl $0x269fd8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00104240_3:\n\t"
      "cmpw $3, %%bx\n\t"
      "jl .LFUN_00104240_9\n\t"
      "call *%[c103d30]\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00104240_9\n\t"
      "movl 0x46e394, %%eax\n\t"
      "pushl $0x28b934\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d98ad]\n\t"
      "movl 0x46e394, %%ecx\n\t"
      "pushl $0x28ba58\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1d98ad]\n\t"
      "addl $0x10, %%esp\n\t"
      "testw %%bx, %%bx\n\t"
      "jle .LFUN_00104240_6\n\t"
      "movswl %%bx, %%eax\n\t"
      "decl %%eax\n\t"
      "movl %%eax, 0xc(%%ebp)\n\t"
      "xorl %%esi, %%esi\n\t"
      "movzwl %%bx, %%ebx\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_00104240_4:\n\t"
      "leal -0xc(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "pushl $0x31fb08\n\t"
      "call *%[xfrmpt]\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl %%eax, %%esi\n\t"
      "movl $0x28ba54, %%eax\n\t"
      "jl .LFUN_00104240_5\n\t"
      "movl $0x28ba4c, %%eax\n\t"
      ".LFUN_00104240_5:\n\t"
      "flds -0x4(%%ebp)\n\t"
      "pushl %%eax\n\t"
      "fmuls 0x253f00\n\t"
      "movl 0x46e394, %%eax\n\t"
      "subl $0x18, %%esp\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fmuls 0x253f00\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fmuls 0x253f00\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x28ba40\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d98ad]\n\t"
      "addl $0x24, %%esp\n\t"
      "incl %%esi\n\t"
      "addl $0xc, %%edi\n\t"
      "decl %%ebx\n\t"
      "jne .LFUN_00104240_4\n\t"
      "movl 0x10(%%ebp), %%esi\n\t"
      "movw 0x8(%%ebp), %%bx\n\t"
      ".LFUN_00104240_6:\n\t"
      "movl 0x46e394, %%ecx\n\t"
      "pushl $0x28b9b0\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1d98ad]\n\t"
      "flds 0x2533c8\n\t"
      "fsubs (%%esi)\n\t"
      "movl 0x46e394, %%edx\n\t"
      "subl $0x18, %%esp\n\t"
      "fstpl 0x18(%%esp)\n\t"
      "flds 0xc(%%esi)\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds 0x8(%%esi)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds 0x4(%%esi)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x28b978\n\t"
      "pushl %%edx\n\t"
      "call *%[c1d98ad]\n\t"
      "movl 0x46e394, %%eax\n\t"
      "pushl $0x28ba20\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d98ad]\n\t"
      "addl $0x30, %%esp\n\t"
      "testw %%bx, %%bx\n\t"
      "jle .LFUN_00104240_8\n\t"
      "xorl %%esi, %%esi\n\t"
      "movzwl %%bx, %%edi\n\t"
      ".LFUN_00104240_7:\n\t"
      "movl 0x46e394, %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl $0x28ba1c\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1d98ad]\n\t"
      "addl $0xc, %%esp\n\t"
      "incl %%esi\n\t"
      "decl %%edi\n\t"
      "jne .LFUN_00104240_7\n\t"
      ".LFUN_00104240_8:\n\t"
      "movl 0x46e394, %%edx\n\t"
      "pushl $0x28ba14\n\t"
      "pushl %%edx\n\t"
      "call *%[c1d98ad]\n\t"
      "movl 0x46e394, %%eax\n\t"
      "pushl $0x28b868\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d98ad]\n\t"
      "movl 0x46e394, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1d9bd2]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00104240_9:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b104240_assert), [exitfn] "m"(b104240_exitfn), [c103d30] "m"(b104240_c103d30), [c1d98ad] "m"(b104240_c1d98ad), [xfrmpt] "m"(b104240_xfrmpt), [c1d9bd2] "m"(b104240_c1d9bd2)
      : "memory");
}
#else
#error "FUN_00104240: clang naked draft required"
#endif


/* FUN_00104430 (0x104430) — XBE naked draft (batch 112). */
#if defined(__clang__)
static void (*const b104430_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b104430_exitfn)(int) = system_exit;
static bool (*const b104430_c103d30)(void) = FUN_00103d30;
static int (*const b104430_c1d98ad)(void *stream, const char *format, ...) = crt_fprintf;
static void (*const b104430_xfrmpt)(float *, float *, float *) = matrix_transform_point;
static int (*const b104430_c1d9bd2)(void *stream) = crt_fflush;

__attribute__((naked, noinline))
void FUN_00104430(int count __attribute__((unused)), int16_t *sections __attribute__((unused)), float *points __attribute__((unused)), float *color __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x14, %%esp\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "pushl %%edi\n\t"
      "jge .LFUN_00104430_1\n\t"
      "pushl $1\n\t"
      "pushl $0x14c\n\t"
      "pushl $0x28b838\n\t"
      "pushl $0x28bb94\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00104430_1:\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .LFUN_00104430_2\n\t"
      "pushl $1\n\t"
      "pushl $0x14d\n\t"
      "pushl $0x28b838\n\t"
      "pushl $0x28bb84\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00104430_2:\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_00104430_3\n\t"
      "pushl $1\n\t"
      "pushl $0x14e\n\t"
      "pushl $0x28b838\n\t"
      "pushl $0x28ba70\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00104430_3:\n\t"
      "testl %%esi, %%esi\n\t"
      "jle .LFUN_00104430_17\n\t"
      "call *%[c103d30]\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00104430_17\n\t"
      "movl 0x46e394, %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl $0x28b934\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d98ad]\n\t"
      "movl 0x46e394, %%ecx\n\t"
      "pushl $0x28bb64\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1d98ad]\n\t"
      "xorl %%eax, %%eax\n\t"
      "addl $0x10, %%esp\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "jle .LFUN_00104430_7\n\t"
      "movl %%edi, %%ebx\n\t"
      "movl %%esi, -0x8(%%ebp)\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_00104430_4:\n\t"
      "xorl %%edi, %%edi\n\t"
      "cmpw %%di, (%%ebx)\n\t"
      "jle .LFUN_00104430_6\n\t"
      "leal (%%eax,%%eax,2), %%edx\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "leal (%%eax,%%edx,4), %%esi\n\t"
      ".LFUN_00104430_5:\n\t"
      "leal -0x14(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl $0x31fb08\n\t"
      "call *%[xfrmpt]\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fmuls 0x253f00\n\t"
      "movl 0x46e394, %%edx\n\t"
      "subl $0xc, %%esp\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fmuls 0x253f00\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fmuls 0x253f00\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x28bb54\n\t"
      "pushl %%edx\n\t"
      "call *%[c1d98ad]\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "addl $0x20, %%esp\n\t"
      "incl %%edi\n\t"
      "incl %%edx\n\t"
      "addl $0xc, %%esi\n\t"
      "cmpw (%%ebx), %%di\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      "jl .LFUN_00104430_5\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "movl %%edx, %%eax\n\t"
      ".LFUN_00104430_6:\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "addl $2, %%ebx\n\t"
      "decl %%ecx\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "jne .LFUN_00104430_4\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      ".LFUN_00104430_7:\n\t"
      "movl 0x46e394, %%eax\n\t"
      "pushl $0x28bb4c\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d98ad]\n\t"
      "movl 0x46e394, %%ecx\n\t"
      "pushl $0x28bb20\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1d98ad]\n\t"
      "movl 0x14(%%ebp), %%ebx\n\t"
      "addl $0x10, %%esp\n\t"
      "testl %%ebx, %%ebx\n\t"
      "je .LFUN_00104430_12\n\t"
      "movl 0x46e394, %%edx\n\t"
      "pushl $0x28bafc\n\t"
      "pushl %%edx\n\t"
      "call *%[c1d98ad]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%esi, %%esi\n\t"
      "jle .LFUN_00104430_11\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "leal 0x8(%%ebx), %%esi\n\t"
      "movl %%eax, 0x10(%%ebp)\n\t"
      ".LFUN_00104430_8:\n\t"
      "movl $2, %%ebx\n\t"
      "cmpw %%bx, (%%edi)\n\t"
      "jle .LFUN_00104430_10\n\t"
      "leal (%%ebx), %%ebx\n\t"
      ".LFUN_00104430_9:\n\t"
      "flds 0x4(%%esi)\n\t"
      "movl 0x46e394, %%ecx\n\t"
      "subl $0x18, %%esp\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds (%%esi)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds -0x4(%%esi)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x28baec\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1d98ad]\n\t"
      "addl $0x20, %%esp\n\t"
      "incl %%ebx\n\t"
      "cmpw (%%edi), %%bx\n\t"
      "jl .LFUN_00104430_9\n\t"
      ".LFUN_00104430_10:\n\t"
      "movl 0x46e394, %%edx\n\t"
      "pushl $0x260ee4\n\t"
      "pushl %%edx\n\t"
      "call *%[c1d98ad]\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "addl $0x10, %%esi\n\t"
      "addl $2, %%edi\n\t"
      "decl %%eax\n\t"
      "movl %%eax, 0x10(%%ebp)\n\t"
      "jne .LFUN_00104430_8\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "movl 0x14(%%ebp), %%ebx\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      ".LFUN_00104430_11:\n\t"
      "flds 0x2533c8\n\t"
      "movl 0x46e394, %%eax\n\t"
      "fsubs (%%ebx)\n\t"
      "subl $8, %%esp\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x28bad0\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d98ad]\n\t"
      "addl $0x10, %%esp\n\t"
      ".LFUN_00104430_12:\n\t"
      "movl 0x46e394, %%ecx\n\t"
      "pushl $0x28baa8\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1d98ad]\n\t"
      "addl $8, %%esp\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "testl %%esi, %%esi\n\t"
      "jle .LFUN_00104430_16\n\t"
      "movl %%esi, 0x8(%%ebp)\n\t"
      "leal (%%ebx), %%ebx\n\t"
      ".LFUN_00104430_13:\n\t"
      "movl 0x46e394, %%edx\n\t"
      "pushl $0x28baa4\n\t"
      "pushl %%edx\n\t"
      "call *%[c1d98ad]\n\t"
      "movl $2, %%esi\n\t"
      "addl $8, %%esp\n\t"
      "cmpw %%si, (%%edi)\n\t"
      "jle .LFUN_00104430_15\n\t"
      "movl %%edi, %%edi\n\t"
      ".LFUN_00104430_14:\n\t"
      "movl 0x46e394, %%ecx\n\t"
      "movswl %%si, %%eax\n\t"
      "addl %%ebx, %%eax\n\t"
      "pushl %%eax\n\t"
      "decl %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl $0x28ba94\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1d98ad]\n\t"
      "addl $0x14, %%esp\n\t"
      "incl %%esi\n\t"
      "cmpw (%%edi), %%si\n\t"
      "jl .LFUN_00104430_14\n\t"
      ".LFUN_00104430_15:\n\t"
      "movl 0x46e394, %%edx\n\t"
      "pushl $0x260ee4\n\t"
      "pushl %%edx\n\t"
      "call *%[c1d98ad]\n\t"
      "movswl (%%edi), %%eax\n\t"
      "addl %%eax, %%ebx\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "addl $2, %%edi\n\t"
      "decl %%eax\n\t"
      "movl %%eax, 0x8(%%ebp)\n\t"
      "jne .LFUN_00104430_13\n\t"
      ".LFUN_00104430_16:\n\t"
      "movl 0x46e394, %%ecx\n\t"
      "pushl $0x28ba88\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1d98ad]\n\t"
      "movl 0x46e394, %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c1d9bd2]\n\t"
      "addl $0xc, %%esp\n\t"
      "popl %%ebx\n\t"
      ".LFUN_00104430_17:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b104430_assert), [exitfn] "m"(b104430_exitfn), [c103d30] "m"(b104430_c103d30), [c1d98ad] "m"(b104430_c1d98ad), [xfrmpt] "m"(b104430_xfrmpt), [c1d9bd2] "m"(b104430_c1d9bd2)
      : "memory");
}
#else
#error "FUN_00104430: clang naked draft required"
#endif


