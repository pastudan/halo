void FUN_000a6a80(void)
{
  char local_118[12];
  int aiStack_10c[61];
  char local_18[20];
  int *piVar1;
  int iVar2;
  void *uVar3;
  int iVar4;

  piVar1 = (int *)((char *)game_globals_get() + 0x14c);
  if (*piVar1 != 0) {
    iVar2 = (int)tag_block_get_element(piVar1, 0, 0x10);
    if (iVar2 != 0) {
      if (*piVar1 == 0) {
        FUN_000a6930(0, *(unsigned short *)piVar1);
        return;
      }
      uVar3 = tag_block_get_element(piVar1, 0, 0x10);
      FUN_000a6930((int)uVar3, *(unsigned short *)piVar1);
      return;
    }
  }
  iVar2 = 0;
  FUN_001b9b60((int)local_18, 0x77656170);
  iVar4 = FUN_001b9b80((int)local_18);
  while (iVar4 != -1 && (unsigned short)iVar2 < 0x10) {
    aiStack_10c[(short)(unsigned short)iVar2 * 4] = iVar4;
    iVar2 = iVar2 + 1;
    iVar4 = FUN_001b9b80((int)local_18);
  }
  FUN_000a6930((int)local_118, iVar2);
  return;
}

void FUN_000a6b50(void)
{
  int *block;
  void *element;

  block = (int *)((char *)game_globals_get() + 0x158);
  if (*block != 0) {
    element = tag_block_get_element(block, 0, 0x10);
    FUN_000a6930((int)element, *(unsigned short *)block);
    return;
  }
  FUN_000a6930(0, *(unsigned short *)block);
}

void FUN_000a6ba0(void)
{
  int *block;
  int index;

  block = (int *)((char *)game_globals_get() + 0x164);
  if (*block != 0) {
    index = (int)*(short *)((char *)tag_block_get_element(block, 0, 0xa0) + 0x20);
    FUN_000a6930(*(int *)((char *)tag_block_get_element(block, 0, 0xa0) + 0x24),
                 (unsigned short)index);
  }
}

void game_initialize(void)
{
  game_globals = (game_globals_t *)game_state_malloc("game globals", 0,
                                                     sizeof(game_globals_t));
  csmemset(game_globals, 0, sizeof(game_globals_t));
  csmemset(&game_variant_global, 0, sizeof(game_variant_global));
  real_math_reset_precision();
  game_time_initialize();
  game_engine_initialize(&game_variant_global);
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
  progress_bar_initialize();
}

void game_dispose(void)
{
  recorded_animations_dispose();
  cinematic_dispose();
  hs_dispose();
  cheats_dispose();
  ui_widgets_dispose();
  editor_dispose();
  ai_dispose();
  player_effect_dispose();
  rumble_dispose();
  game_sound_dispose();
  sound_classes_dispose();
  game_engine_dispose();
  particle_systems_dispose();
  weather_particle_systems_dispose();
  effects_dispose();
  particles_dispose();
  contrails_dispose();
  players_dispose();
  decals_dispose();
  breakable_surfaces_dispose();
  structures_dispose();
  render_dispose();
  objects_dispose();
  director_dispose();
  interface_dispose();
  game_allegiance_dispose();
  game_time_dispose();
  saved_game_files_dispose();
  event_manager_dispose();
  input_abstraction_dispose();
  player_ui_dispose();
  game_state_dispose();
  telnet_console_dispose();
  transport_dispose();
  bink_playback_dispose();
  progress_bar_dispose();
}

void game_precache_new_map(char *map_name, bool a2)
{
  __int16 map_status;

  if (cache_files_precache_map_loaded(map_name)) {
  LABEL_22:
    if (a2) {
      assert_halt(cache_files_precache_map_loaded(map_name));
      main_save_current_solo_map(map_name);
      main_queue_map_name(NULL);

      if (cache_files_precache_in_progress())
        cache_files_precache_map_end();

      if (player_spawn_count == 1)
        player_ui_remember_player1_profile(true);
    }
    return;
  }

  if (cache_files_precache_in_progress() &&
      !cache_files_precache_is_copying_map(map_name)) {
    if (a2) {
      cache_files_precache_map_end();
    } else {
      cache_files_precache_map_queue_end();
      main_queue_map_name(map_name);
    }
  }

  if (!cache_files_precache_in_progress() &&
      !cache_files_precache_map_begin(map_name, a2)) {
    error(2, "shouldn't be here... map '%s' doesn't exist", map_name);
    if (a2) {
      display_assert("read the last error message for which map failed to load",
                     __FILE__, __LINE__, true);
      system_exit(-1);
    }
  }

  cache_files_precache_set_priority(a2);

  if (a2) {
    game_globals->map_loading = true;
    game_globals->map_load_progress = 0.0f;
    assert_halt(cache_files_precache_in_progress() &&
                cache_files_precache_is_copying_map(map_name));
    ui_widget_load_progress_widget();
    progress_bar_begin(global_scenario_index != -1);

    do {
      map_status =
        cache_files_precache_map_status(&game_globals->map_load_progress);
      main_pregame_render();
      main_rasterizer_throttle();
      main_present_frame();
    } while (!map_status);

    progress_bar_end();
    ui_widgets_close_all();

    if (map_status == 2)
      display_error_damaged_media();

    cache_files_precache_map_end();
    assert_halt(cache_files_precache_map_loaded(map_name));

    game_globals->map_loading = false;
    game_globals->map_load_progress = 1.0f;

    goto LABEL_22;
  }
}

bool game_map_loading_in_progress(float *progress)
{
  if (progress) {
    *progress = game_globals->map_load_progress;
  }
  return game_globals->map_loading;
}

void game_unload(void)
{
  __int16 map_status;

  if (cache_files_precache_in_progress()) {
    game_globals->map_loading = true;
    ui_widget_load_progress_widget();

    do {
      map_status =
        cache_files_precache_map_status(&game_globals->map_load_progress);
      main_pregame_render();
      main_rasterizer_throttle();
      main_present_frame();
    } while (!map_status);

    ui_widgets_close_all();
    if (map_status == 2)
      display_error_damaged_media();
    cache_files_precache_map_end();
  }
  if (game_globals->map_loaded) {
    scenario_unload();
    random_seed_debug_log(0);
    game_globals->map_loaded = false;
  }
}

void game_dispose_from_old_map()
{
  rasterizer_dispose_from_old_map();
  game_state_dispose_from_old_map();
  cheats_dispose_from_old_map();
  recorded_animations_dispose_from_old_map();
  hs_dispose_from_old_map();
  cinematic_dispose_from_old_map();
  editor_dispose_from_old_map();
  ai_dispose_from_old_map();
  player_effect_dispose_from_old_map();
  rumble_dispose_from_old_map();
  point_physics_dispose_from_old_map();
  particle_systems_dispose_from_old_map();
  weather_particle_systems_dispose_from_old_map();
  decals_dispose_from_old_map();
  breakable_surfaces_dispose_from_old_map();
  structures_dispose_from_old_map();
  j__render_dispose_from_old_map();
  objects_dispose_from_old_map();
  director_dispose_from_old_map();
  observer_dispose_from_old_map();
  interface_dispose_from_old_map();
  players_dispose_from_old_map();
  contrails_dispose_from_old_map();
  particles_dispose_from_old_map();
  effects_dispose_from_old_map();
  game_sound_dispose_from_old_map();
  sound_classes_dispose_from_old_map();
  sound_dispose_from_old_map();
  game_allegiance_dispose_from_old_map();
  update_server_delete();
  game_engine_dispose_from_old_map();
  scenario_dispose_from_old_map();
  game_time_dispose_from_old_map();
  ui_widgets_close_all();
  ui_widgets_safe_to_load(0);
  game_globals->active = 0;
}

void game_frame(float elapsed)
{
  if (game_globals->players_double_speed)
    elapsed *= 0.5f;

  assert_halt(game_globals->active);

  collision_log_begin_period(1);
  particles_update(elapsed);
  contrails_update(elapsed);
  particle_systems_update(elapsed);
  widgets_update(elapsed);
  game_sound_update(elapsed);
  scenario_frame_update(elapsed);
  rasterizer_frame_update(elapsed);
  numeric_countdown_timer_update();
  collision_log_end_period();
}

void remove_quitting_players_from_game(void)
{
  data_iter_t iter;
  char *player;
  int quit_tick;
  int quit_at;

  if (!game_engine_running())
    return;

  quit_tick = game_time_get();
  data_iterator_new(&iter, player_data);
  while ((player = (char *)data_iterator_next(&iter)) != NULL) {
    quit_at = *(int *)(player + 0xCC);
    if (quit_at != -1 && *(char *)(player + 0xD1) == 0) {
      if (quit_tick == quit_at) {
        *(char *)(player + 0xD1) = 1;
        if (*(int *)(player + 0x34) != -1) {
          object_get_and_verify_type(*(int *)(player + 0x34), 3);
          unit_delete(*(int *)(player + 0x34));
        }
      } else if (quit_at < quit_tick) {
        error(2, "player %x failed to quit, wanted %d is %d", iter.datum_handle,
              quit_at, quit_tick);
      }
    }
  }
}

void game_tick(void)
{
  float seconds_per_tick;

  profile_tick_start();
  collision_log_begin_period(0);
  real_math_reset_precision();
  if (profile_global_enable && byte_2EF808)
    profile_enter_private(&off_2EF800);

  assert_halt(game_globals->active);

  remove_quitting_players_from_game();
  game_allegiance_update();
  units_update();
  ai_update();
  players_update_before_game();

  seconds_per_tick = 1 / 30.0f;
  if (game_globals->players_double_speed)
    seconds_per_tick = 1 / 60.0f;

  effects_update(seconds_per_tick);
  lock_global_random_seed();
  rumble_update();
  first_person_weapons_update();
  unlock_global_random_seed();
  game_engine_update();
  editor_update();
  hs_update();
  recorded_animations_update();
  objects_update();
  players_update_after_game();
  hud_update();
  player_effect_update();
  if (profile_global_enable && byte_2EF808)
    profile_exit_private(&off_2EF800);
  collision_log_end_period();
  profile_tick_end();
}

void game_options_new(game_options_t *options)
{
  csmemset(options, 0, sizeof(*options));
  options->unk_4 = 0;
  options->difficulty = 1;
  options->random_seed = 0xDEADBEEF;
}

static bool game_options_verify(game_options_t *options)
{
  return options->difficulty >= 0 && options->difficulty < 4;
}

void game_initial_pulse()
{
  data_iter_t iter; // [esp+0h] [ebp-10h] BYREF

  data_iterator_new(&iter, player_data);
  while (data_iterator_next(&iter))
    game_engine_player_added(iter.datum_handle);
  game_engine_game_starting();
}

void game_set_players_are_double_speed(bool is_double_speed)
{
  game_globals->players_double_speed = is_double_speed;
}

bool game_players_are_double_speed(void)
{
  return game_globals->players_double_speed;
}

void game_difficulty_level_set(int16_t difficulty)
{
  game_globals->game_options.difficulty = difficulty;
}

int16_t game_difficulty_level_get(void)
{
  return game_globals->game_options.difficulty;
}

int game_difficulty_level_get_ignore_easy(void)
{
  int16_t difficulty = game_globals->game_options.difficulty;

  if (difficulty <= 1)
    return 1;

  return difficulty;
}

void game_set_game_variant(game_variant_t *variant)
{
  if (!variant)
    csmemset(&game_variant_global, 0, sizeof(game_variant_t));
  else
    qmemcpy(&game_variant_global, variant, sizeof(game_variant_t));
}

void game_set_game_engine_index(void)
{
  display_assert(
    "this is broken and should get updated for the variants, ask michael",
    __FILE__, __LINE__, true);
  system_exit(-1);
}

bool game_all_quiet(void)
{
  return !dangerous_projectiles_near_player() &&
         !dangerous_items_near_player() && !dangerous_effects_near_player() &&
         !any_unit_is_dangerous() && !ai_enemies_can_see_player();
}

bool game_safe_to_save(void)
{
  if (ai_enemies_can_see_player()) {
    if (debug_game_save) {
      console_warning("not safe to save: ai_enemies_can_see_player");
    }
    return false;
  }

  if (dangerous_projectiles_near_player()) {
    if (debug_game_save) {
      console_warning("not safe to save: dangerous_projectiles_near_player");
    }
    return false;
  }

  if (dangerous_items_near_player()) {
    if (debug_game_save) {
      console_warning("not safe to save: dangerous_items_near_player");
    }
    return false;
  }

  if (dangerous_effects_near_player()) {
    if (debug_game_save) {
      console_warning("not safe to save: dangerous_effects_near_player");
    }
    return false;
  }

  if (any_unit_is_dangerous()) {
    if (debug_game_save) {
      console_warning("not safe to save: any_unit_is_dangerous");
    }
    return false;
  }

  if (any_player_is_in_the_air()) {
    if (debug_game_save) {
      console_warning("not safe to save: any_player_is_in_the_air");
    }
    return false;
  }

  if (any_player_is_dead()) {
    if (debug_game_save) {
      console_warning("not safe to save: any_player_is_dead");
    }
    return false;
  }

  if (vehicle_moving_near_any_player()) {
    if (debug_game_save) {
      console_warning("not safe to save: vehicle_moving_near_any_player");
    }
    return false;
  }

  return true;
}

bool game_safe_to_speak(void)
{
  return !dangerous_projectiles_near_player() && !any_player_is_dead();
}

bool game_is_cooperative(void)
{
  return player_spawn_count > 1;
}
void set_random_seed(int seed)
{
  *get_global_random_seed_address() = seed;
}
bool game_load(game_options_t *options)
{
  game_globals_t *globals;
  bool loaded;

  assert_halt(!game_globals->active);
  assert_halt(!game_globals->map_loaded);
  assert_halt(game_options_verify(options));

  random_seed_debug_log(1);
  csmemcpy(&game_globals->game_options, options, sizeof(*options));

  loaded = scenario_load(options->map_name);
  globals = game_globals;

  if (loaded) {
    globals->map_loaded = true;
  }

  return globals->map_loaded;
}

void game_initialize_for_new_map(void)
{
  int random_seed;

  assert_halt(game_globals->map_loaded);
  assert_halt(!game_globals->active);

  random_seed = game_globals->game_options.random_seed;
  *get_global_random_seed_address() = random_seed;
  game_engine_dispose();
  game_engine_initialize(&game_variant_global);
  real_math_reset_precision();
  rasterizer_initialize_for_new_map();
  game_state_initialize_for_new_map();
  game_time_initialize_for_new_map();
  interface_initialize_for_new_map();
  game_allegiance_initialize_for_new_map();
  players_initialize_for_new_map();
  scenario_initialize_for_new_map();
  objects_initialize_for_new_map();
  render_initialize_for_new_map();
  structures_initialize_for_new_map();
  breakable_surfaces_initialize_for_new_map();
  decals_initialize_for_new_map();
  director_initialize_for_new_map();
  observer_initialize_for_new_map();
  contrails_initialize_for_new_map();
  particles_initialize_for_new_map();
  effects_initialize_for_new_map();
  particle_systems_initialize_for_new_map();
  sound_initialize_for_new_map();
  sound_classes_initialize_for_new_map();
  game_sound_initialize_for_new_map();
  weather_particle_systems_initialize_for_new_map();
  point_physics_initialize_for_new_map();
  game_engine_initialize_for_new_map();
  game_statistics_start();
  update_server_new();
  player_control_initialize_for_new_map();
  rumble_initialize_for_new_map();
  player_effect_initialize_for_new_map();
  ai_initialize_for_new_map();
  console_initialize_for_new_map();
  editor_initialize_for_new_map();
  cinematic_initialize_for_new_map();
  hs_initialize_for_new_map();
  recorded_animations_initialize_for_new_map();
  cheats_initialize_for_new_map();
  game_globals->active = 1;
  objects_place();
  if (!game_in_editor()) {
    ai_place();
  }
  ui_widgets_safe_to_load(1);
}

void game_set_game_variant_from_name(const char *name)
{
  game_variant_t variant;
  game_variant_t variant_copy;

  // The original at 0xa78e0 has a dead `if (!&variant_copy)` branch from a
  // LEA+TEST+JNZ pattern on a stack address — unreachable in practice, and
  // inexpressible in C. We preserve the two-step copy via variant_copy but
  // skip the dead zero-out branch.
  qmemcpy(&variant_copy, game_engine_get_variant_by_name(&variant, name),
          sizeof(game_variant_t));
  qmemcpy(&game_variant_global, &variant_copy, sizeof(game_variant_t));
}

/* FUN_000b4170 (0xb4170) — race/team score computation.
 * Given a player handle and a mode flag, computes a score:
 *   mode 1: returns a per-team value from the table at 0x456f98.
 *   otherwise: counts set bits in the per-team bitmask at 0x456f54
 *              (8 bits per loop iteration, 4 iterations for all 32 bits),
 *              then returns player->c2 * 0x21 + bit_count. */
int FUN_000b4170(int player_handle, int param_2)
{
  int iVar1;
  unsigned int uVar2;
  unsigned char bVar3;
  int iVar5;
  int iVar6;
  char *player;
  int team_index;

  player = (char *)datum_get(player_data, player_handle);
  team_index = *(int *)(player + 0x20);
  if (param_2 == 1) {
    return ((int *)0x456f98)[team_index];
  }
  uVar2 = ((unsigned int *)0x456f54)[team_index];
  iVar6 = 0;
  iVar5 = 2;
  do {
    bVar3 = (unsigned char)iVar5;
    if ((uVar2 & (1 << (bVar3 - 2))) != 0)
      iVar6 = iVar6 + 1;
    if ((uVar2 & (1 << (bVar3 - 1))) != 0)
      iVar6 = iVar6 + 1;
    if ((uVar2 & (1 << bVar3)) != 0)
      iVar6 = iVar6 + 1;
    if ((uVar2 & (1 << (bVar3 + 1))) != 0)
      iVar6 = iVar6 + 1;
    if ((uVar2 & (1 << (bVar3 + 2))) != 0)
      iVar6 = iVar6 + 1;
    if ((uVar2 & (1 << (bVar3 + 3))) != 0)
      iVar6 = iVar6 + 1;
    if ((uVar2 & (1 << (bVar3 + 4))) != 0)
      iVar6 = iVar6 + 1;
    if ((uVar2 & (1 << (bVar3 + 5))) != 0)
      iVar6 = iVar6 + 1;
    iVar1 = iVar5 + 6;
    iVar5 = iVar5 + 8;
  } while (iVar1 < 0x20);
  return (int)*(int16_t *)(player + 0xc2) * 0x21 + iVar6;
}

/* FUN_000b4250 (0xb4250) — race score string
 *
 * Formats the player's race score (lap/flag count) into a wide string buffer.
 * Looks up the player datum by handle, reads the int16 score at offset 0xc2,
 * and formats it via usprintf with the format string at 0x26c118 (likely
 * L"%d"). */
wchar_t *FUN_000b4250(int player_handle, wchar_t *dst)
{
  char *player;

  player = (char *)datum_get(player_data, player_handle);
  usprintf(dst, (const wchar_t *)0x26c118, (int)*(int16_t *)(player + 0xc2));
  return dst;
}

/* FUN_000b4290 (0xb4290) — race score header string
 *
 * Returns the header label for the race score column.
 * If the game variant modifier (offset 0x4c) is 2 (flags mode), returns
 * L"Flags". Otherwise returns L"Laps". */
wchar_t *FUN_000b4290(wchar_t *dst)
{
  void *variant;

  variant = game_engine_get_variant();
  if (*(int *)((char *)variant + 0x4c) == 2) {
    usprintf(dst, L"Flags");
    return dst;
  }
  usprintf(dst, L"Laps");
  return dst;
}

/* FUN_000b42d0 (0xb42d0) — race score format by position index
 *
 * Formats the race score at 0x456f98[param_1] into dst using the
 * format string pointer at 0x26c118. Returns dst. */
wchar_t *FUN_000b42d0(int param_1, wchar_t *dst)
{
  usprintf(dst, (const wchar_t *)0x26c118, ((int *)0x456f98)[param_1]);
  return dst;
}

/* FUN_000b45c0 (0xb45c0) — XBE naked draft (batch 132). */
#if defined(__clang__)
static scenario_t * (*const bb45c0_c18e380)(void) = global_scenario_get;
static void (*const bb45c0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const bb45c0_exitfn)(int) = system_exit;
static int *(*const bb45c0_gseed)(void) = get_global_random_seed_address;
static int16_t (*const bb45c0_c10b2d0)(unsigned int *seed, int16_t min, int16_t max) = random_range;
static void *(*const bb45c0_elem)(void *, int, int) = tag_block_get_element;

__attribute__((naked, noinline))
int FUN_000b45c0(int param_1 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $8, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "orl $0xffffffff, %%edi\n\t"
      "movl %%edi, -0x4(%%ebp)\n\t"
      "call *%[c18e380]\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "movl 0x456f10, %%eax\n\t"
      "xorl %%esi, %%esi\n\t"
      "xorl %%ecx, %%ecx\n\t"
      ".LFUN_000b45c0_1:\n\t"
      "movl $1, %%edx\n\t"
      "shll %%cl, %%edx\n\t"
      "testl %%edx, %%eax\n\t"
      "je .LFUN_000b45c0_2\n\t"
      "incl %%esi\n\t"
      ".LFUN_000b45c0_2:\n\t"
      "incl %%ecx\n\t"
      "cmpl $0x20, %%ecx\n\t"
      "jl .LFUN_000b45c0_1\n\t"
      "cmpl %%edi, 0x8(%%ebp)\n\t"
      "je .LFUN_000b45c0_3\n\t"
      "decl %%esi\n\t"
      ".LFUN_000b45c0_3:\n\t"
      "testl %%esi, %%esi\n\t"
      "jg .LFUN_000b45c0_4\n\t"
      "pushl $1\n\t"
      "pushl $0x2a7\n\t"
      "pushl $0x26d8f4\n\t"
      "pushl $0x26db9c\n\t"
      "call *%[assert]\n\t"
      "pushl %%edi\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000b45c0_4:\n\t"
      "pushl %%esi\n\t"
      "pushl $0\n\t"
      "call *%[gseed]\n\t"
      "pushl %%eax\n\t"
      "call *%[c10b2d0]\n\t"
      "movl -0x8(%%ebp), %%esi\n\t"
      "addl $0x378, %%esi\n\t"
      "movswl %%ax, %%ebx\n\t"
      "movl (%%esi), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "xorl %%edi, %%edi\n\t"
      "testl %%eax, %%eax\n\t"
      "jle .LFUN_000b45c0_7\n\t"
      ".LFUN_000b45c0_5:\n\t"
      "pushl $0x94\n\t"
      "pushl %%edi\n\t"
      "pushl %%esi\n\t"
      "call *%[elem]\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpw $3, 0x10(%%eax)\n\t"
      "jne .LFUN_000b45c0_6\n\t"
      "movswl 0x12(%%eax), %%ecx\n\t"
      "cmpl 0x8(%%ebp), %%ecx\n\t"
      "je .LFUN_000b45c0_6\n\t"
      "testl %%ebx, %%ebx\n\t"
      "je .LFUN_000b45c0_10\n\t"
      "decl %%ebx\n\t"
      ".LFUN_000b45c0_6:\n\t"
      "movl (%%esi), %%eax\n\t"
      "incl %%edi\n\t"
      "cmpl %%eax, %%edi\n\t"
      "jl .LFUN_000b45c0_5\n\t"
      ".LFUN_000b45c0_7:\n\t"
      "movl -0x4(%%ebp), %%esi\n\t"
      ".LFUN_000b45c0_8:\n\t"
      "pushl $1\n\t"
      "pushl $0x2bc\n\t"
      "pushl $0x26d8f4\n\t"
      "pushl $0x26db88\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000b45c0_9:\n\t"
      "popl %%edi\n\t"
      "movl %%esi, %%eax\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000b45c0_10:\n\t"
      "movswl 0x12(%%eax), %%esi\n\t"
      "cmpl $-1, %%esi\n\t"
      "jne .LFUN_000b45c0_9\n\t"
      "jmp .LFUN_000b45c0_8\n\t"
      :
      : [c18e380] "m"(bb45c0_c18e380), [assert] "m"(bb45c0_assert), [exitfn] "m"(bb45c0_exitfn), [gseed] "m"(bb45c0_gseed), [c10b2d0] "m"(bb45c0_c10b2d0), [elem] "m"(bb45c0_elem)
      : "memory");
}
#else
#error "FUN_000b45c0: clang naked draft required"
#endif


/* FUN_000b4960 (0xb4960) — XBE naked draft (batch 130). */
#if defined(__clang__)
static scenario_t * (*const bb4960_c18e380)(void) = global_scenario_get;
static void (*const bb4960_cb3860)(void) = (void *)FUN_000b3860;
static void *(*const bb4960_memset)(void *, int, unsigned int) = csmemset;
static void *(*const bb4960_elem)(void *, int, int) = tag_block_get_element;
static void (*const bb4960_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;
static void (*const bb4960_ca93e0)(int flag_index, int *position, float height, char *name, int target, int16_t team, int player) = game_engine_set_goal_position;
static void * (*const bb4960_ca9350)(void) = game_engine_get_variant;
static int (*const bb4960_cb45c0)(int param_1) = FUN_000b45c0;

__attribute__((naked, noinline))
int FUN_000b4960(void)
{
  __asm__ volatile(
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl $0x20, %%ebx\n\t"
      "call *%[c18e380]\n\t"
      "movl %%eax, %%esi\n\t"
      "call *%[cb3860]\n\t"
      "pushl $0xd0\n\t"
      "pushl $0\n\t"
      "pushl $0x456f10\n\t"
      "movb $0, 0x456fdc\n\t"
      "call *%[memset]\n\t"
      "addl $0x378, %%esi\n\t"
      "movl $0x1e, 0x5aa744\n\t"
      "movl (%%esi), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "xorl %%edi, %%edi\n\t"
      "testl %%eax, %%eax\n\t"
      "jle .LFUN_000b4960_5\n\t"
      ".LFUN_000b4960_1:\n\t"
      "pushl $0x94\n\t"
      "pushl %%edi\n\t"
      "pushl %%esi\n\t"
      "call *%[elem]\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpw $3, 0x10(%%eax)\n\t"
      "jne .LFUN_000b4960_4\n\t"
      "movw 0x12(%%eax), %%cx\n\t"
      "cmpw $0x20, %%cx\n\t"
      "jl .LFUN_000b4960_2\n\t"
      "pushl $0x20\n\t"
      "pushl $0x26dc60\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $0xc, %%esp\n\t"
      "jmp .LFUN_000b4960_4\n\t"
      ".LFUN_000b4960_2:\n\t"
      "movswl %%cx, %%ecx\n\t"
      "cmpl %%ecx, %%ebx\n\t"
      "jle .LFUN_000b4960_3\n\t"
      "movl %%ecx, %%ebx\n\t"
      ".LFUN_000b4960_3:\n\t"
      "pushl $-1\n\t"
      "pushl $-1\n\t"
      "movl $1, %%edx\n\t"
      "shll %%cl, %%edx\n\t"
      "movl 0x456f10, %%ecx\n\t"
      "pushl $-1\n\t"
      "pushl $0x26d4c0\n\t"
      "orl %%edx, %%ecx\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "movl %%ecx, 0x456f10\n\t"
      "movswl 0x12(%%eax), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[ca93e0]\n\t"
      "addl $0x1c, %%esp\n\t"
      ".LFUN_000b4960_4:\n\t"
      "movl (%%esi), %%eax\n\t"
      "incl %%edi\n\t"
      "cmpl %%eax, %%edi\n\t"
      "jl .LFUN_000b4960_1\n\t"
      ".LFUN_000b4960_5:\n\t"
      "call *%[ca9350]\n\t"
      "cmpl $2, 0x4c(%%eax)\n\t"
      "jne .LFUN_000b4960_6\n\t"
      "pushl $-1\n\t"
      "call *%[cb45c0]\n\t"
      "addl $4, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%eax, 0x456f94\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      ".LFUN_000b4960_6:\n\t"
      "call *%[ca9350]\n\t"
      "movl 0x4c(%%eax), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "movl $0x456f14, %%edi\n\t"
      "movl $0x10, %%ecx\n\t"
      "jne .LFUN_000b4960_7\n\t"
      "movl %%ebx, %%eax\n\t"
      "rep stosl\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      ".LFUN_000b4960_7:\n\t"
      "orl $0xffffffff, %%eax\n\t"
      "rep stosl\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      :
      : [c18e380] "m"(bb4960_c18e380), [cb3860] "m"(bb4960_cb3860), [memset] "m"(bb4960_memset), [elem] "m"(bb4960_elem), [c8f390] "m"(bb4960_c8f390), [ca93e0] "m"(bb4960_ca93e0), [ca9350] "m"(bb4960_ca9350), [cb45c0] "m"(bb4960_cb45c0)
      : "memory");
}
#else
#error "FUN_000b4960: clang naked draft required"
#endif


/* FUN_000b4d50 (0xb4d50) — race score lookup
 *
 * Looks up a player's race score value. If param_2 == 1, reads score from
 * the 0x456fe0 table indexed by the player's int at offset 0x20. Otherwise
 * reads from the 0x457020 table indexed by the player handle's low 16 bits. */
int FUN_000b4d50(unsigned int player_handle, int param_2)
{
  char *player;

  player = (char *)datum_get(player_data, player_handle);
  if (param_2 == 1) {
    return *(int *)(0x456fe0 + *(int *)(player + 0x20) * 4);
  }
  return *(int *)(0x457020 + (player_handle & 0xffff) * 4);
}

/* FUN_000b4d90 (0xb4d90) — check race state == 1 */
bool FUN_000b4d90(int param_1)
{
  bool result;
  result = 0;
  if (--param_1 == 0) {
    result = 1;
  }
  return result;
}

/* FUN_000b4da0 (0xb4da0) — race score format by handle
 *
 * Formats a race score string from the 0x457020 table, indexed by the
 * low 16 bits of the player handle. Uses the format string at 0x26c118. */
wchar_t *FUN_000b4da0(unsigned int player_handle, wchar_t *dst)
{
  usprintf(dst, (const wchar_t *)0x26c118,
           *(int *)(0x457020 + (player_handle & 0xffff) * 4));
  return dst;
}

/* FUN_000b4dd0 (0xb4dd0) — race score header "Score"
 *
 * Formats the static header string L"Score" into the destination buffer. */
wchar_t *FUN_000b4dd0(wchar_t *dst)
{
  usprintf(dst, L"Score");
  return dst;
}

/* FUN_000b4df0 (0xb4df0) — race score format by index
 *
 * Formats a race score string from the 0x456fe0 table, indexed directly
 * by param_1. Uses the format string at 0x26c118. */
wchar_t *FUN_000b4df0(int index, wchar_t *dst)
{
  usprintf(dst, (const wchar_t *)0x26c118, *(int *)(0x456fe0 + index * 4));
  return dst;
}

/* 0xb5490 — FUN_000b5490
 *
 * Returns the name string for a given material type index.
 * If material_type == -1, returns "NONE" (at 0x253a04).
 * Otherwise asserts material_type is in [0, NUMBER_OF_MATERIAL_TYPES) where
 * NUMBER_OF_MATERIAL_TYPES == 0x21 (33), then indexes into the static pointer
 * table at 0x2f0208 (const char *[33]).
 *
 * Confirmed: PUSH 0x1 / PUSH 0x389 / PUSH 0x26dfc4 / PUSH 0x26df88 /
 *   CALL display_assert / PUSH -0x1 / CALL system_exit / ADD ESP,0x14 at
 *   0xb54a9-0xb54c6 (lazy cdecl stack cleanup covers both calls).
 * Confirmed: MOVSX EAX,SI / MOV EAX,[EAX*4+0x2f0208] table lookup at 0xb54c9.
 * Confirmed: CMP SI,-0x1 / JZ → MOV EAX,0x253a04 / RET at 0xb54d6.
 * Source file: c:\halo\SOURCE\game\game_globals.c, assert line 0x389 (905).
 */
const char *FUN_000b5490(short material_type)
{
  if (material_type == -1)
    return (const char *)0x253a04;
  if (material_type < 0 || material_type >= 0x21) {
    display_assert("material_type>=0 && material_type<NUMBER_OF_MATERIAL_TYPES",
                   "c:\\halo\\SOURCE\\game\\game_globals.c", 0x389, 1);
    system_exit(-1);
  }
  return ((const char **)0x2f0208)[material_type];
}

/* 0xb54e0 — game_globals_difficulty_scale
 *
 * Looks up a difficulty scaling factor from the game globals matg tag's
 * difficulty block.  The block stores an array of floats arranged as
 * value_type rows of 4 difficulty columns (Easy/Normal/Heroic/Legendary).
 *
 * Register args: @BX = value_type (0..0x22), @DI = difficulty (-1 = raw
 * per-value_type default, 0..3 = clamped to [0, 3]).
 *
 * If difficulty < 0 the function indexes the table as value_type*16 bytes
 * from the element base (i.e. column 0, raw float[value_type][0]).
 * If difficulty >= 0 it clamps to min(difficulty, 3) and indexes as
 * (difficulty + value_type*4)*4 bytes, i.e. float[value_type][difficulty].
 *
 * Falls back to 1.0f if game_globals_get() returns NULL, the difficulty
 * block count is zero, or tag_block_get_element returns NULL.
 *
 * Confirmed: CALL 0x18e450 (game_globals_get) at 0xb54ec.
 * Confirmed: TEST BX,BX / CMP BX,0x23 range assert at 0xb54f1/0xb54f8.
 * Confirmed: MOV ECX,[ESI+0x11c] / LEA EAX,[ESI+0x11c] at 0xb5522/0xb552a.
 * Confirmed: PUSH 0x284 / PUSH 0x0 / PUSH EAX to tag_block_get_element at
 *   0xb5532. Confirmed: TEST DI,DI / JGE 0xb555e selects raw vs clamped path.
 * Confirmed: XOR ECX,ECX / MOVSX EDX,BX / MOVSX ECX,CX / LEA EDX,[ECX+EDX*4]
 *   then FLD [EAX+EDX*4] for the raw (DI<0) path at 0xb554b.
 * Confirmed: CMP DI,3 / MOV ECX,3 / JG / MOV ECX,EDI clamping at 0xb555e.
 */
float game_globals_difficulty_scale(int16_t value_type, int16_t difficulty)
{
  float default_val = 1.0f;
  void *globals;
  void *element;
  int16_t clamped;
  int idx;

  assert_halt(value_type >= 0 && value_type < 0x23);

  globals = game_globals_get();
  if (!globals)
    return default_val;

  if (*(int *)((char *)globals + 0x11c) == 0)
    return default_val;

  element = tag_block_get_element((char *)globals + 0x11c, 0, 0x284);
  if (!element)
    return default_val;

  if (difficulty < 0) {
    idx = (int)value_type * 4;
    return *(float *)((char *)element + idx * 4);
  }

  clamped = difficulty > 3 ? 3 : difficulty;
  idx = (int)clamped + (int)value_type * 4;
  return *(float *)((char *)element + idx * 4);
}

/* 0xb5590 — FUN_000b5590
 *
 * Convenience wrapper: fetches the current game difficulty level and
 * returns game_globals_difficulty_scale(value_type, difficulty).
 *
 * Confirmed: CALL 0xa7460 (game_difficulty_level_get) at 0xb5595.
 * Confirmed: MOV EBX,[EBP+0x8] (value_type cdecl arg) at 0xb559a.
 * Confirmed: MOV EDI,EAX (difficulty ← return AX of game_difficulty_level_get)
 *   at 0xb559d. Confirmed: CALL 0xb54e0 (game_globals_difficulty_scale,
 *   @bx=value_type, @di=difficulty) at 0xb559f.
 */
float FUN_000b5590(int16_t value_type)
{
  int16_t difficulty = game_difficulty_level_get();
  return game_globals_difficulty_scale(value_type, difficulty);
}

/* FUN_000b55b0 (0xb55b0) — game_globals_difficulty_scale_get
 *
 * Returns the difficulty scaling factor for a given game-globals value type
 * and team. The lookup strategy depends on game mode:
 *   - If the game engine is running (multiplayer/co-op): force difficulty=1
 *     (Normal) regardless of the current level setting.
 *   - Else if team is friendly (allegiance_get_team_is_friendly(1, team)):
 *     use the actual difficulty level from game_difficulty_level_get.
 *   - Else: look up value_type in an override table at 0x26ddc8
 *     (int16_t[0x23]). If the override is NONE (-1, meaning no override),
 *     force difficulty=1. Otherwise substitute the override value_type and
 *     use the actual difficulty level.
 *
 * The underlying scale is fetched by game_globals_difficulty_scale (@BX=value_type,
 * @DI=difficulty) from the game globals tag (matg) difficulty block.
 *
 * Confirmed: CALL 0xa7460 (game_difficulty_level_get) → EDI at 0xb55ba.
 * Confirmed: CALL 0xa8e30 (game_engine_running) → AL at 0xb55bc.
 * Confirmed: MOV EDI,1 when running at 0xb55c5 (force Normal).
 * Confirmed: CALL 0xa7a30 (game_allegiance_get_team_is_friendly(1, team)) at
 * 0xb55dc. Confirmed: assert value_type in [0, 0x22] at line 0x3bd (957),
 *   __FILE__ "c:\halo\SOURCE\game\game_globals.c".
 * Confirmed: override table word lookup at [ECX*2 + 0x26ddc8] at 0xb5619.
 * Confirmed: CMP AX,0xffff selects between override=NONE (EDI=1) and
 *   override != NONE (EBX=override, EDI=actual difficulty) at 0xb5621.
 * Confirmed: CALL 0xb54e0 with BX=value_type and DI=difficulty in all paths.
 */
float FUN_000b55b0(short value_type, int team)
{
  int16_t difficulty = game_difficulty_level_get();
  if (game_engine_running()) {
    return game_globals_difficulty_scale(value_type, 1);
  }
  if (game_allegiance_get_team_is_friendly(1, team)) {
    return game_globals_difficulty_scale(value_type, difficulty);
  }
  assert_halt(value_type >= 0 && value_type < 0x23);
  {
    int16_t override = *(int16_t *)(0x26ddc8 + (int)value_type * 2);
    if (override == (int16_t)0xffff) {
      return game_globals_difficulty_scale(value_type, 1);
    }
    return game_globals_difficulty_scale(override, difficulty);
  }
}
/* --- game.obj batch drafts (2026-07-26) --- */

/* race_team_can_win_game (0xb40f0) — readable C lift. */
char race_team_can_win_game(int team_handle, unsigned int bit_index)
{
  datum_get(*(data_t **)0x5aa6d4, team_handle);
  if ((*(unsigned int *)0x456f10 & (1u << bit_index)) == 0) {
    display_assert((const char *)0x26db24, (const char *)0x26d8f4, 0x426, 1);
    system_exit(-1);
    return 0;
  }
  return FUN_000b3b30(team_handle, (int)bit_index);
}
/* race_engine_update (0xb4300) — readable C lift. */
int race_engine_update(int player_handle)
{
  char *player;
  char present[2];
  int team;

  if (!FUN_000a95a0()) {
    return FUN_000ae250(player_handle);
  }
  player = (char *)datum_get(*(data_t **)0x5aa6d4, player_handle);
  present[0] = FUN_000b3c60(0);
  present[1] = FUN_000b3c60(1);
  if (present[0] != present[1]) {
    team = *(int *)(player + 0x20);
    return present[team] != 0;
  }
  if (present[0]) {
    return FUN_000ae250(player_handle);
  }
  display_assert((const char *)0x26db74, (const char *)0x26d8f4, 0x48d, 1);
  system_exit(-1);
  return -1;
}
/* FUN_000b43b0 (0xb43b0) — readable C lift. */
int FUN_000b43b0(float *point, int *exclude, int exclude_count)
{
  float best_d2;
  int best;
  char *scenario;
  char *globals;
  char *block;
  int i, j;
  char *elem;
  float dx, dy, dz, d2;

  best_d2 = 1000000.0f;
  best = -1;
  scenario = (char *)global_scenario_get();
  globals = (char *)game_globals_get();
  tag_block_get_element(globals + 0x164, 0, 0xa0);
  block = scenario + 0x378;
  for (i = 0; i < *(int *)block; i++) {
    elem = (char *)tag_block_get_element(block, i, 0x94);
    if (*(int16_t *)(elem + 0x10) != 4)
      continue;
    for (j = 0; j < exclude_count; j++) {
      if (i == exclude[j])
        goto next;
    }
    if (point == NULL)
      return i;
    dx = *(float *)elem - point[0];
    dy = *(float *)(elem + 4) - point[1];
    dz = *(float *)(elem + 8) - point[2];
    d2 = dx * dx + dy * dy + dz * dz;
    if (!(d2 >= best_d2)) {
      best_d2 = d2;
      best = i;
    }
  next:
    ;
  }
  return best;
}

/* FUN_000b4490 (0xb4490) — XBE naked draft (batch 126). */
#if defined(__clang__)
static scenario_t * (*const bb4490_c18e380)(void) = global_scenario_get;
static void (*const bb4490_c1197b0)(data_iter_t *iter, data_t *data) = data_iterator_new;
static void * (*const bb4490_c119810)(data_iter_t *iterator) = data_iterator_next;
static void *(*const bb4490_get)(int, int) = object_get_and_verify_type;
static void (*const bb4490_cb43b0)(void) = (void *)FUN_000b43b0;
static void *(*const bb4490_elem)(void *, int, int) = tag_block_get_element;
static int (*const bb4490_cb3770)(int param_1) = FUN_000b3770;
static void (*const bb4490_opnew)(void *, int, int) = object_placement_data_new;
static void (*const bb4490_c10cc70)(float *output, float angle) = vector3d_from_angle;
static int (*const bb4490_onew)(void *) = object_new;

__attribute__((naked, noinline))
void FUN_000b4490(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xbc, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c18e380]\n\t"
      "movl %%eax, %%esi\n\t"
      "xorl %%eax, %%eax\n\t"
      "movl $7, %%ecx\n\t"
      "leal -0x30(%%ebp), %%edi\n\t"
      "movl $0xffffffff, -0x34(%%ebp)\n\t"
      "rep stosl\n\t"
      "movl 0x5aa6d4, %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x14(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "call *%[c1197b0]\n\t"
      "leal -0x14(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c119810]\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_000b4490_6\n\t"
      ".LFUN_000b4490_1:\n\t"
      "movl 0x34(%%eax), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_000b4490_2\n\t"
      "pushl $3\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "addl $8, %%esp\n\t"
      "jmp .LFUN_000b4490_3\n\t"
      ".LFUN_000b4490_2:\n\t"
      "xorl %%eax, %%eax\n\t"
      ".LFUN_000b4490_3:\n\t"
      "cmpl $8, %%ebx\n\t"
      "je .LFUN_000b4490_6\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_000b4490_4\n\t"
      "leal -0x34(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "addl $0xc, %%eax\n\t"
      "pushl %%eax\n\t"
      "jmp .LFUN_000b4490_5\n\t"
      ".LFUN_000b4490_4:\n\t"
      "leal -0x34(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0\n\t"
      ".LFUN_000b4490_5:\n\t"
      "call *%[cb43b0]\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_000b4490_6\n\t"
      "movl %%eax, -0x34(%%ebp,%%ebx,4)\n\t"
      "leal -0x14(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "incl %%ebx\n\t"
      "call *%[c119810]\n\t"
      "addl $4, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_000b4490_1\n\t"
      ".LFUN_000b4490_6:\n\t"
      "xorl %%edi, %%edi\n\t"
      "testl %%ebx, %%ebx\n\t"
      "jle .LFUN_000b4490_9\n\t"
      "addl $0x378, %%esi\n\t"
      "movl %%esi, -0x4(%%ebp)\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_000b4490_7:\n\t"
      "movl -0x34(%%ebp,%%edi,4), %%ecx\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "pushl $0x94\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[elem]\n\t"
      "pushl %%edi\n\t"
      "movl %%eax, %%esi\n\t"
      "call *%[cb3770]\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_000b4490_8\n\t"
      "pushl $-1\n\t"
      "pushl %%eax\n\t"
      "leal -0xbc(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[opnew]\n\t"
      "movl %%esi, %%ecx\n\t"
      "movl (%%ecx), %%edx\n\t"
      "movl %%edx, -0xa4(%%ebp)\n\t"
      "movl 0x4(%%ecx), %%eax\n\t"
      "movl %%eax, -0xa0(%%ebp)\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "movl %%ecx, -0x9c(%%ebp)\n\t"
      "movl 0xc(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x88(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c10cc70]\n\t"
      "leal -0xbc(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[onew]\n\t"
      "addl $0x18, %%esp\n\t"
      "movb $1, 0x456fdc\n\t"
      ".LFUN_000b4490_8:\n\t"
      "incl %%edi\n\t"
      "cmpl %%ebx, %%edi\n\t"
      "jl .LFUN_000b4490_7\n\t"
      ".LFUN_000b4490_9:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c18e380] "m"(bb4490_c18e380), [c1197b0] "m"(bb4490_c1197b0), [c119810] "m"(bb4490_c119810), [get] "m"(bb4490_get), [cb43b0] "m"(bb4490_cb43b0), [elem] "m"(bb4490_elem), [cb3770] "m"(bb4490_cb3770), [opnew] "m"(bb4490_opnew), [c10cc70] "m"(bb4490_c10cc70), [onew] "m"(bb4490_onew)
      : "memory");
}
#else
#error "FUN_000b4490: clang naked draft required"
#endif


/* race_update_team_score (0xb46b0) — XBE naked draft (batch 126). */
#if defined(__clang__)
static scenario_t * (*const bb46b0_c18e380)(void) = global_scenario_get;
static void *(*const bb46b0_elem)(void *, int, int) = tag_block_get_element;
static char (*const bb46b0_cb3b30)(int flag_index, int param_1) = FUN_000b3b30;
static void (*const bb46b0_cb2610)(int event_type) = game_engine_post_event;
static void * (*const bb46b0_ca9350)(void) = game_engine_get_variant;
static void (*const bb46b0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const bb46b0_exitfn)(int) = system_exit;
static void (*const bb46b0_cb39a0)(int player_handle) = FUN_000b39a0;
static int (*const bb46b0_cb45c0)(int param_1) = FUN_000b45c0;

__attribute__((naked, noinline))
void race_update_team_score(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "movl %%eax, %%ebx\n\t"
      "call *%[c18e380]\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "pushl $0x94\n\t"
      "pushl %%ecx\n\t"
      "addl $0x378, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl %%eax, %%edi\n\t"
      "movswl 0x12(%%edi), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "movl %%ebx, %%ecx\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "call *%[cb3b30]\n\t"
      "testb %%al, %%al\n\t"
      "je .Lrace_update_team_score_7\n\t"
      "pushl %%esi\n\t"
      "movl %%ebx, %%esi\n\t"
      "pushl $0x1a\n\t"
      "andl $0xffff, %%esi\n\t"
      "call *%[cb2610]\n\t"
      "movl 0x456f14(,%%esi,4), %%eax\n\t"
      "addl $4, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "jne .Lrace_update_team_score_2\n\t"
      "call *%[ca9350]\n\t"
      "movl 0x4c(%%eax), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "jne .Lrace_update_team_score_1\n\t"
      "pushl $1\n\t"
      "pushl $0x2d3\n\t"
      "pushl $0x26d8f4\n\t"
      "pushl $0x26dc08\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrace_update_team_score_1:\n\t"
      "movswl 0x12(%%edi), %%edx\n\t"
      "movl %%edx, 0x456f14(,%%esi,4)\n\t"
      ".Lrace_update_team_score_2:\n\t"
      "call *%[ca9350]\n\t"
      "cmpl $2, 0x4c(%%eax)\n\t"
      "jne .Lrace_update_team_score_3\n\t"
      "movl %%ebx, %%eax\n\t"
      "call *%[cb39a0]\n\t"
      "movl 0x456f94, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[cb45c0]\n\t"
      "addl $4, %%esp\n\t"
      "popl %%esi\n\t"
      "popl %%edi\n\t"
      "movl %%eax, 0x456f94\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lrace_update_team_score_3:\n\t"
      "movl 0x456f54(,%%esi,4), %%eax\n\t"
      "cmpl 0x456f10, %%eax\n\t"
      "leal 0x456f54(,%%esi,4), %%edi\n\t"
      "jne .Lrace_update_team_score_4\n\t"
      "movl %%ebx, %%eax\n\t"
      "call *%[cb39a0]\n\t"
      "popl %%esi\n\t"
      "popl %%edi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lrace_update_team_score_4:\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movl $1, %%esi\n\t"
      "shll %%cl, %%esi\n\t"
      "testl %%esi, %%eax\n\t"
      "je .Lrace_update_team_score_5\n\t"
      "pushl $1\n\t"
      "pushl $0x2e9\n\t"
      "pushl $0x26d8f4\n\t"
      "pushl $0x26dbe0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrace_update_team_score_5:\n\t"
      "movl (%%edi), %%ebx\n\t"
      "orl %%esi, %%ebx\n\t"
      "movl %%ebx, (%%edi)\n\t"
      "movl 0x456f10, %%ecx\n\t"
      "movl %%ebx, %%edi\n\t"
      "notl %%ecx\n\t"
      "testl %%ecx, %%edi\n\t"
      "je .Lrace_update_team_score_6\n\t"
      "pushl $1\n\t"
      "pushl $0x2ed\n\t"
      "pushl $0x26d8f4\n\t"
      "pushl $0x26dba8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrace_update_team_score_6:\n\t"
      "popl %%esi\n\t"
      ".Lrace_update_team_score_7:\n\t"
      "popl %%edi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c18e380] "m"(bb46b0_c18e380), [elem] "m"(bb46b0_elem), [cb3b30] "m"(bb46b0_cb3b30), [cb2610] "m"(bb46b0_cb2610), [ca9350] "m"(bb46b0_ca9350), [assert] "m"(bb46b0_assert), [exitfn] "m"(bb46b0_exitfn), [cb39a0] "m"(bb46b0_cb39a0), [cb45c0] "m"(bb46b0_cb45c0)
      : "memory");
}
#else
#error "race_update_team_score: clang naked draft required"
#endif


/* FUN_000B4800 (0xb4800) — XBE naked draft (batch 123). */
#if defined(__clang__)
static void *(*const bb4800_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void (*const bb4800_ca9970)(int param_1, int param_2, int param_3) = game_engine_state_message;
static bool (*const bb4800_ca8e40)(void) = game_engine_can_score;
static void *(*const bb4800_get)(int, int) = object_get_and_verify_type;
static int (*const bb4800_cad270)(float *position, float radius, float height, int16_t type, int16_t index) = find_netgame_flag;
static void (*const bb4800_cb46b0)(void) = (void *)race_update_team_score;

__attribute__((naked, noinline))
void FUN_000B4800(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl 0x5aa6d4, %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "pushl %%edi\n\t"
      "pushl $0x16\n\t"
      "pushl %%edi\n\t"
      "movl %%eax, %%esi\n\t"
      "call *%[ca9970]\n\t"
      "movl 0x34(%%esi), %%eax\n\t"
      "addl $0x14, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_000B4800_3\n\t"
      "call *%[ca8e40]\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000B4800_3\n\t"
      "movl 0x34(%%esi), %%ecx\n\t"
      "pushl $3\n\t"
      "pushl %%ecx\n\t"
      "call *%[get]\n\t"
      "movl 0xcc(%%eax), %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%ecx\n\t"
      "je .LFUN_000B4800_1\n\t"
      "pushl $3\n\t"
      "pushl %%ecx\n\t"
      "call *%[get]\n\t"
      "pushl $-1\n\t"
      "pushl $3\n\t"
      "pushl $0\n\t"
      "addl $0x50, %%eax\n\t"
      "pushl $0x40200000\n\t"
      "pushl %%eax\n\t"
      "call *%[cad270]\n\t"
      "addl $0x1c, %%esp\n\t"
      "jmp .LFUN_000B4800_2\n\t"
      ".LFUN_000B4800_1:\n\t"
      "pushl $-1\n\t"
      "pushl $3\n\t"
      "pushl $0x3f19999a\n\t"
      "addl $0x50, %%eax\n\t"
      "pushl $0x3fc00000\n\t"
      "pushl %%eax\n\t"
      "call *%[cad270]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000B4800_2:\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_000B4800_3\n\t"
      "pushl %%eax\n\t"
      "movl %%edi, %%eax\n\t"
      "call *%[cb46b0]\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_000B4800_3:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [dget] "m"(bb4800_dget), [ca9970] "m"(bb4800_ca9970), [ca8e40] "m"(bb4800_ca8e40), [get] "m"(bb4800_get), [cad270] "m"(bb4800_cad270), [cb46b0] "m"(bb4800_cb46b0)
      : "memory");
}
#else
#error "FUN_000B4800: clang naked draft required"
#endif


/* FUN_000b4a70 (0xb4a70) — readable C lift. */
char FUN_000b4a70(int handle_b, int handle_a, int handle_c)
{
  void *pa = datum_get(*(data_t **)0x5aa6d4, handle_a);
  void *pb = datum_get(*(data_t **)0x5aa6d4, handle_b);
  if (handle_b == handle_a || handle_b == handle_c) {
    return 0;
  }
  if (*(int *)((char *)pb + 0x20) == *(int *)((char *)pa + 0x20)) {
    return 0;
  }
  if (*(int *)((char *)pb + 0x34) == -1) {
    return 0;
  }
  return 1;
}

/* FUN_000b4b10 (0xb4b10) — readable C lift. */
void FUN_000b4b10(int datum_handle)
{
  void *d = datum_get(*(data_t **)0x5aa6d4, datum_handle);
  *(unsigned int *)((char *)d + 0x88) = 0xffffffffu;
}
/* FUN_000b4bf0 (0xb4bf0) — XBE naked draft (batch 131). */
#if defined(__clang__)
static void *(*const bb4bf0_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void * (*const bb4bf0_ca9350)(void) = game_engine_get_variant;

__attribute__((naked, noinline))
void FUN_000b4bf0(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "movl 0x5aa6d4, %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x5aa6d4, %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "addl $0x10, %%esp\n\t"
      "movl %%eax, %%edi\n\t"
      "call *%[ca9350]\n\t"
      "movb 0x4d(%%eax), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "jne .LFUN_000b4bf0_6\n\t"
      "flds 0x6c(%%esi)\n\t"
      "fsubs 0x255ca0\n\t"
      "fcoms 0x2533c8\n\t"
      "fsts 0x6c(%%esi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_000b4bf0_2\n\t"
      "fsubs 0x256140\n\t"
      "fcoms 0x2533c8\n\t"
      "fsts 0x6c(%%esi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .LFUN_000b4bf0_1\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c8\n\t"
      ".LFUN_000b4bf0_1:\n\t"
      "fstps 0x6c(%%esi)\n\t"
      "jmp .LFUN_000b4bf0_3\n\t"
      ".LFUN_000b4bf0_2:\n\t"
      "fstp %%st(0)\n\t"
      ".LFUN_000b4bf0_3:\n\t"
      "flds 0x6c(%%esi)\n\t"
      "fcomps 0x2555d0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_000b4bf0_4\n\t"
      "flds 0x6c(%%esi)\n\t"
      "jmp .LFUN_000b4bf0_5\n\t"
      ".LFUN_000b4bf0_4:\n\t"
      "flds 0x2555d0\n\t"
      ".LFUN_000b4bf0_5:\n\t"
      "fstps 0x6c(%%esi)\n\t"
      ".LFUN_000b4bf0_6:\n\t"
      "call *%[ca9350]\n\t"
      "movb 0x4c(%%eax), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "jne .LFUN_000b4bf0_11\n\t"
      "flds 0x6c(%%edi)\n\t"
      "fadds 0x25496c\n\t"
      "fcoms 0x2533c8\n\t"
      "fsts 0x6c(%%edi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .LFUN_000b4bf0_8\n\t"
      "fadds 0x25496c\n\t"
      "fcoms 0x2533c8\n\t"
      "fsts 0x6c(%%edi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_000b4bf0_7\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c8\n\t"
      ".LFUN_000b4bf0_7:\n\t"
      "fstps 0x6c(%%edi)\n\t"
      "jmp .LFUN_000b4bf0_9\n\t"
      ".LFUN_000b4bf0_8:\n\t"
      "fstp %%st(0)\n\t"
      ".LFUN_000b4bf0_9:\n\t"
      "flds 0x6c(%%edi)\n\t"
      "fcomps 0x2533ec\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_000b4bf0_10\n\t"
      "flds 0x2533ec\n\t"
      "fstps 0x6c(%%edi)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000b4bf0_10:\n\t"
      "flds 0x6c(%%edi)\n\t"
      "fstps 0x6c(%%edi)\n\t"
      ".LFUN_000b4bf0_11:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [dget] "m"(bb4bf0_dget), [ca9350] "m"(bb4bf0_ca9350)
      : "memory");
}
#else
#error "FUN_000b4bf0: clang naked draft required"
#endif


/* FUN_000b4d00 (0xb4d00) — readable C lift: add to team/player score buckets. */
void FUN_000b4d00(int player_handle /*@<eax>*/, int delta /*@<edi>*/)
{
  char *player;
  int team;

  player = (char *)datum_get(*(data_t **)0x5aa6d4, player_handle);
  team = *(int *)(player + 0x20);
  *(int *)(0x456fe0 + team * 4) += delta;
  *(int *)(0x457020 + (player_handle & 0xffff) * 4) += delta;
}

/* find_next_target (0xb4e20) — XBE naked draft (batch 121). */
#if defined(__clang__)
static void *(*const bb4e20_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void (*const bb4e20_c1197b0)(data_iter_t *iter, data_t *data) = data_iterator_new;
static void * (*const bb4e20_c119810)(data_iter_t *iterator) = data_iterator_next;
static int *(*const bb4e20_gseed)(void) = get_global_random_seed_address;
static int16_t (*const bb4e20_c10b2d0)(unsigned int *seed, int16_t min, int16_t max) = random_range;
static void (*const bb4e20_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const bb4e20_exitfn)(int) = system_exit;
static void (*const bb4e20_cad0c0)(int param_1, int param_2, int param_3) = game_engine_player_event;

__attribute__((naked, noinline))
void find_next_target(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x20, %%esp\n\t"
      "movl 0x5aa6d4, %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl 0x88(%%eax), %%ecx\n\t"
      "movl 0x5aa6d4, %%edx\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "pushl %%edx\n\t"
      "leal -0x20(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "movl $0xffffffff, -0xc(%%ebp)\n\t"
      "movl $0, -0x4(%%ebp)\n\t"
      "call *%[c1197b0]\n\t"
      "leal -0x20(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c119810]\n\t"
      "addl $0x14, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lfind_next_target_8\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      ".Lfind_next_target_1:\n\t"
      "movl 0x5aa6d4, %%edx\n\t"
      "movl -0x18(%%ebp), %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%edx\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl 0x5aa6d4, %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpl %%edi, %%esi\n\t"
      "je .Lfind_next_target_2\n\t"
      "cmpl -0x8(%%ebp), %%esi\n\t"
      "je .Lfind_next_target_2\n\t"
      "movl 0x20(%%eax), %%ecx\n\t"
      "cmpl 0x20(%%ebx), %%ecx\n\t"
      "je .Lfind_next_target_2\n\t"
      "cmpl $-1, 0x34(%%eax)\n\t"
      "je .Lfind_next_target_2\n\t"
      "incl -0x4(%%ebp)\n\t"
      ".Lfind_next_target_2:\n\t"
      "leal -0x20(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c119810]\n\t"
      "addl $4, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lfind_next_target_1\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jle .Lfind_next_target_7\n\t"
      "pushl %%eax\n\t"
      "pushl $0\n\t"
      "call *%[gseed]\n\t"
      "pushl %%eax\n\t"
      "call *%[c10b2d0]\n\t"
      "movl 0x5aa6d4, %%ecx\n\t"
      "movswl %%ax, %%eax\n\t"
      "pushl %%ecx\n\t"
      "leal -0x20(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "call *%[c1197b0]\n\t"
      "leal -0x20(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c119810]\n\t"
      "addl $0x18, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lfind_next_target_6\n\t"
      "leal (%%esp), %%esp\n\t"
      ".Lfind_next_target_3:\n\t"
      "movl 0x5aa6d4, %%ecx\n\t"
      "movl -0x18(%%ebp), %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movl 0x5aa6d4, %%edx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edx\n\t"
      "movl %%eax, %%ebx\n\t"
      "call *%[dget]\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpl %%edi, %%esi\n\t"
      "je .Lfind_next_target_4\n\t"
      "cmpl -0x8(%%ebp), %%esi\n\t"
      "je .Lfind_next_target_4\n\t"
      "movl 0x20(%%eax), %%ecx\n\t"
      "cmpl 0x20(%%ebx), %%ecx\n\t"
      "je .Lfind_next_target_4\n\t"
      "cmpl $-1, 0x34(%%eax)\n\t"
      "je .Lfind_next_target_4\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lfind_next_target_5\n\t"
      "decl %%eax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      ".Lfind_next_target_4:\n\t"
      "leal -0x20(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c119810]\n\t"
      "addl $4, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lfind_next_target_3\n\t"
      "jmp .Lfind_next_target_6\n\t"
      ".Lfind_next_target_5:\n\t"
      "movl -0x18(%%ebp), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "jne .Lfind_next_target_7\n\t"
      ".Lfind_next_target_6:\n\t"
      "pushl $1\n\t"
      "pushl $0xc2\n\t"
      "pushl $0x26dcc4\n\t"
      "pushl $0x26dcb0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lfind_next_target_7:\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      ".Lfind_next_target_8:\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "movl -0x10(%%ebp), %%ecx\n\t"
      "movl %%eax, 0x88(%%ecx)\n\t"
      "je .Lfind_next_target_9\n\t"
      "pushl %%eax\n\t"
      "pushl $0x1e\n\t"
      "pushl %%edi\n\t"
      "call *%[cad0c0]\n\t"
      "addl $0xc, %%esp\n\t"
      ".Lfind_next_target_9:\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [dget] "m"(bb4e20_dget), [c1197b0] "m"(bb4e20_c1197b0), [c119810] "m"(bb4e20_c119810), [gseed] "m"(bb4e20_gseed), [c10b2d0] "m"(bb4e20_c10b2d0), [assert] "m"(bb4e20_assert), [exitfn] "m"(bb4e20_exitfn), [cad0c0] "m"(bb4e20_cad0c0)
      : "memory");
}
#else
#error "find_next_target: clang naked draft required"
#endif


/* FUN_000b4fb0 (0xb4fb0) — XBE naked draft (batch 146). */
#if defined(__clang__)
static void *(*const bb4fb0_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void (*const bb4fb0_cb4bf0)(void) = (void *)FUN_000b4bf0;
static void * (*const bb4fb0_ca9350)(void) = game_engine_get_variant;
static void (*const bb4fb0_cb4e20)(void) = (void *)find_next_target;
static void (*const bb4fb0_cb4d00)(void) = (void *)FUN_000b4d00;

__attribute__((naked, noinline))
void FUN_000b4fb0(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl 0x5aa6d4, %%eax\n\t"
      "pushl %%edi\n\t"
      "movl 0x10(%%ebp), %%edi\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movb 0xd1(%%eax), %%cl\n\t"
      "addl $8, %%esp\n\t"
      "testb %%cl, %%cl\n\t"
      "jne .LFUN_000b4fb0_4\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "cmpl $-1, %%esi\n\t"
      "je .LFUN_000b4fb0_3\n\t"
      "movl 0x5aa6d4, %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%ebx\n\t"
      "movb 0x14(%%ebp), %%al\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_000b4fb0_2\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[cb4bf0]\n\t"
      "addl $8, %%esp\n\t"
      "call *%[ca9350]\n\t"
      "movb 0x4e(%%eax), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "je .LFUN_000b4fb0_1\n\t"
      "cmpl %%edi, 0x88(%%ebx)\n\t"
      "jne .LFUN_000b4fb0_3\n\t"
      "movl %%esi, %%edi\n\t"
      "call *%[cb4e20]\n\t"
      ".LFUN_000b4fb0_1:\n\t"
      "movl $1, %%edi\n\t"
      "movl %%esi, %%eax\n\t"
      "call *%[cb4d00]\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%edi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000b4fb0_2:\n\t"
      "orl $0xffffffff, %%edi\n\t"
      "movl %%esi, %%eax\n\t"
      "call *%[cb4d00]\n\t"
      ".LFUN_000b4fb0_3:\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      ".LFUN_000b4fb0_4:\n\t"
      "popl %%edi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [dget] "m"(bb4fb0_dget), [cb4bf0] "m"(bb4fb0_cb4bf0), [ca9350] "m"(bb4fb0_ca9350), [cb4e20] "m"(bb4fb0_cb4e20), [cb4d00] "m"(bb4fb0_cb4d00)
      : "memory");
}
#else
#error "FUN_000b4fb0: clang naked draft required"
#endif


/* FUN_000b5040 (0xb5040) — XBE naked draft (batch 117). */
#if defined(__clang__)
static void *(*const bb5040_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void * (*const bb5040_ca9350)(void) = game_engine_get_variant;
static void (*const bb5040_c19e9f0)(wchar_t *buffer, int buffer_size, const wchar_t *format, ...) = unicode_sprintf;
static int (*const bb5040_ca9e20)(int param_1, int param_2) = game_engine_get_place;
static wchar_t * (*const bb5040_ca9af0)(int param_1) = game_engine_place_to_string;

__attribute__((naked, noinline))
void FUN_000b5040(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x100, %%esp\n\t"
      "movl 0x5aa6d4, %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "movb $1, %%bl\n\t"
      "call *%[dget]\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "xorl %%eax, %%eax\n\t"
      "cmpl $0x1e, %%ecx\n\t"
      "jne .LFUN_000b5040_4\n\t"
      "call *%[ca9350]\n\t"
      "movb 0x1c(%%eax), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "pushl %%esi\n\t"
      "je .LFUN_000b5040_1\n\t"
      "movl 0x5aa6d4, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movl 0x20(%%eax), %%edx\n\t"
      "movl 0x5aa6d4, %%eax\n\t"
      "movl 0x456fe0(,%%edx,4), %%edi\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "pushl %%edi\n\t"
      "andl $0xffff, %%esi\n\t"
      "movl 0x457020(,%%esi,4), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x26dd64\n\t"
      "leal -0x100(%%ebp), %%edx\n\t"
      "pushl $0x80\n\t"
      "pushl %%edx\n\t"
      "call *%[c19e9f0]\n\t"
      "addl $0x24, %%esp\n\t"
      "jmp .LFUN_000b5040_2\n\t"
      ".LFUN_000b5040_1:\n\t"
      "movl 0x5aa6d4, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "andl $0xffff, %%esi\n\t"
      "movl 0x457020(,%%esi,4), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x26c118\n\t"
      "leal -0x100(%%ebp), %%edx\n\t"
      "pushl $0x80\n\t"
      "pushl %%edx\n\t"
      "call *%[c19e9f0]\n\t"
      "addl $0x18, %%esp\n\t"
      ".LFUN_000b5040_2:\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "movl 0x5aa6d4, %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_000b5040_3:\n\t"
      "movl 0x18(%%ebp), %%edx\n\t"
      "addl $4, %%eax\n\t"
      "pushl %%eax\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "pushl $0x26dd48\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c19e9f0]\n\t"
      "addl $0x10, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000b5040_4:\n\t"
      "cmpl $0x16, %%ecx\n\t"
      "je .LFUN_000b5040_5\n\t"
      "cmpl $0x1e, %%ecx\n\t"
      "je .LFUN_000b5040_3\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000b5040_5:\n\t"
      "call *%[ca9350]\n\t"
      "movb 0x1c(%%eax), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "pushl $1\n\t"
      "pushl %%esi\n\t"
      "je .LFUN_000b5040_6\n\t"
      "call *%[ca9e20]\n\t"
      "pushl %%eax\n\t"
      "call *%[ca9af0]\n\t"
      "movl 0x5aa6d4, %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%ecx\n\t"
      "movl %%eax, %%edi\n\t"
      "call *%[dget]\n\t"
      "movl 0x20(%%eax), %%edx\n\t"
      "movl 0x5aa6d4, %%ecx\n\t"
      "movl 0x456fe0(,%%edx,4), %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%ecx\n\t"
      "movl %%eax, 0xc(%%ebp)\n\t"
      "call *%[dget]\n\t"
      "andl $0xffff, %%esi\n\t"
      "movl 0x457020(,%%esi,4), %%esi\n\t"
      "call *%[ca9350]\n\t"
      "movl 0x40(%%eax), %%edx\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "movl 0x18(%%ebp), %%ecx\n\t"
      "pushl %%edx\n\t"
      "movl 0x14(%%ebp), %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl $0x26dd14\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c19e9f0]\n\t"
      "addl $0x38, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000b5040_6:\n\t"
      "call *%[ca9e20]\n\t"
      "pushl %%eax\n\t"
      "call *%[ca9af0]\n\t"
      "movl %%eax, %%edi\n\t"
      "movl 0x5aa6d4, %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl 0x20(%%eax), %%ecx\n\t"
      "movl 0x456fe0(,%%ecx,4), %%esi\n\t"
      "call *%[ca9350]\n\t"
      "movl 0x40(%%eax), %%edx\n\t"
      "movl 0x18(%%ebp), %%eax\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl $0x26dcf0\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c19e9f0]\n\t"
      "addl $0x2c, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [dget] "m"(bb5040_dget), [ca9350] "m"(bb5040_ca9350), [c19e9f0] "m"(bb5040_c19e9f0), [ca9e20] "m"(bb5040_ca9e20), [ca9af0] "m"(bb5040_ca9af0)
      : "memory");
}
#else
#error "FUN_000b5040: clang naked draft required"
#endif


/* slayer_engine_display_score (0xb5210) — XBE naked draft (batch 107). */
#if defined(__clang__)
static void *(*const bb5210_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void * (*const bb5210_ca9350)(void) = game_engine_get_variant;
static void (*const bb5210_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const bb5210_exitfn)(int) = system_exit;
static void (*const bb5210_ca9460)(short param_1) = game_engine_clear_goal_position;
static void *(*const bb5210_get)(int, int) = object_get_and_verify_type;
static void (*const bb5210_ca93e0)(int flag_index, int *position, float height, char *name, int target, int16_t team, int player) = game_engine_set_goal_position;
static void (*const bb5210_cb4e20)(void) = (void *)find_next_target;
static char (*const bb5210_ca9900)(int param_1) = game_engine_man_out;
static void (*const bb5210_ca8b00)(void) = (void *)game_engine_start_over;

__attribute__((naked, noinline))
void slayer_engine_display_score(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl 0x5aa6d4, %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "addl $8, %%esp\n\t"
      "movl %%eax, %%esi\n\t"
      "call *%[ca9350]\n\t"
      "movb 0x4d(%%eax), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "je .Lslayer_engine_display_score_2\n\t"
      "flds 0x6c(%%esi)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lslayer_engine_display_score_2\n\t"
      "flds 0x6c(%%esi)\n\t"
      "fsubs 0x26ddb8\n\t"
      "fcoms 0x2533c8\n\t"
      "fsts 0x6c(%%esi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .Lslayer_engine_display_score_1\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c8\n\t"
      ".Lslayer_engine_display_score_1:\n\t"
      "fstps 0x6c(%%esi)\n\t"
      ".Lslayer_engine_display_score_2:\n\t"
      "call *%[ca9350]\n\t"
      "movb 0x4c(%%eax), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "je .Lslayer_engine_display_score_4\n\t"
      "flds 0x6c(%%esi)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lslayer_engine_display_score_4\n\t"
      "flds 0x6c(%%esi)\n\t"
      "fadds 0x26ddb4\n\t"
      "fcoms 0x2533c8\n\t"
      "fsts 0x6c(%%esi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lslayer_engine_display_score_3\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c8\n\t"
      ".Lslayer_engine_display_score_3:\n\t"
      "fstps 0x6c(%%esi)\n\t"
      ".Lslayer_engine_display_score_4:\n\t"
      "call *%[ca9350]\n\t"
      "movb 0x4e(%%eax), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "je .Lslayer_engine_display_score_9\n\t"
      "testw %%di, %%di\n\t"
      "jl .Lslayer_engine_display_score_5\n\t"
      "cmpw $0x10, %%di\n\t"
      "jl .Lslayer_engine_display_score_6\n\t"
      ".Lslayer_engine_display_score_5:\n\t"
      "pushl $1\n\t"
      "pushl $0x1f5\n\t"
      "pushl $0x26dcc4\n\t"
      "pushl $0x26dd7c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lslayer_engine_display_score_6:\n\t"
      "pushl %%edi\n\t"
      "call *%[ca9460]\n\t"
      "movl 0x88(%%esi), %%eax\n\t"
      "addl $4, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lslayer_engine_display_score_7\n\t"
      "movl 0x5aa6d4, %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movl 0x34(%%eax), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lslayer_engine_display_score_7\n\t"
      "pushl $3\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "pushl $-1\n\t"
      "pushl $-1\n\t"
      "pushl %%edi\n\t"
      "pushl $0x26d8b8\n\t"
      "pushl $0\n\t"
      "addl $0x50, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "call *%[ca93e0]\n\t"
      "addl $0x24, %%esp\n\t"
      ".Lslayer_engine_display_score_7:\n\t"
      "cmpl $-1, 0x34(%%esi)\n\t"
      "je .Lslayer_engine_display_score_8\n\t"
      "cmpl $-1, 0x88(%%esi)\n\t"
      "jne .Lslayer_engine_display_score_8\n\t"
      "call *%[cb4e20]\n\t"
      ".Lslayer_engine_display_score_8:\n\t"
      "movl 0x88(%%esi), %%esi\n\t"
      "cmpl $-1, %%esi\n\t"
      "je .Lslayer_engine_display_score_9\n\t"
      "pushl %%esi\n\t"
      "call *%[ca9900]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lslayer_engine_display_score_9\n\t"
      "call *%[cb4e20]\n\t"
      ".Lslayer_engine_display_score_9:\n\t"
      "movl 0x5aa6d4, %%edx\n\t"
      "pushl %%edi\n\t"
      "pushl %%edx\n\t"
      "call *%[dget]\n\t"
      "movl 0x20(%%eax), %%eax\n\t"
      "movl 0x456fe0(,%%eax,4), %%esi\n\t"
      "addl $8, %%esp\n\t"
      "call *%[ca9350]\n\t"
      "movl 0x40(%%eax), %%ecx\n\t"
      "popl %%edi\n\t"
      "cmpl %%ecx, %%esi\n\t"
      "popl %%esi\n\t"
      "jl .Lslayer_engine_display_score_10\n\t"
      "popl %%ebp\n\t"
      "jmp .Lslayer_engine_display_score_10000\n\t"
      ".Lslayer_engine_display_score_10:\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lslayer_engine_display_score_10000:\n\t"
      "jmp *%[ca8b00]\n\t"
      :
      : [dget] "m"(bb5210_dget), [ca9350] "m"(bb5210_ca9350), [assert] "m"(bb5210_assert), [exitfn] "m"(bb5210_exitfn), [ca9460] "m"(bb5210_ca9460), [get] "m"(bb5210_get), [ca93e0] "m"(bb5210_ca93e0), [cb4e20] "m"(bb5210_cb4e20), [ca9900] "m"(bb5210_ca9900), [ca8b00] "m"(bb5210_ca8b00)
      : "memory");
}
#else
#error "slayer_engine_display_score: clang naked draft required"
#endif

/* --- game.obj orphan shells (2026-07-26) --- */

/* FUN_000A7470 (0xa7470) — readable C lift. */
int FUN_000A7470(void)
{
  int16_t v = *(int16_t *)(*(char **)0x4566ec + 0xe);

  if (v > 1) {
    return (int)v;
  }
  return 1;
}

