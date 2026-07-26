/* --- main.obj batch1 drafts (2026-07-26) --- */

bool cache_files_give_time_to_precache(const char *name);
void main_menu_active(int flag);

char gamepad_button_is_down(int16_t button)
{
  if (button < 0 || button >= 0x10) {
    display_assert((char *)0x28b078, "c:\\halo\\SOURCE\\main\\main.c", 0xf5, 1);
    system_exit(-1);
  }
  {
    int i;
    for (i = 0; i < 4; i++) {
      if (input_has_gamepad((int16_t)i)) {
        void *state = input_get_gamepad_state(i);
        if ((char)*((char *)state + 0x10 + button) > 0)
          return 1;
      }
    }
  }
  return 0;
}

void main_disallow_persistent_storage(void)
{
  *(char *)0x46da54 = 0;
}

void main_set_map_name(const char *name)
{
  csstrncpy((char *)0x46da55, name, 0xff);
  *(char *)0x46da43 = 0;
  *(char *)0x46db54 = 0;
  *(char *)0x46da54 = 1;
  if (game_in_editor() || game_in_progress()) {
    if (*(int16_t *)0x46da0c == 0)
      *(char *)0x46da25 = 1;
  }
}

void main_set_multiplayer_map_name(const char *name)
{
  csstrncpy((char *)0x46db55, name, 0xff);
  *(char *)0x46dc54 = 0;
  cache_files_give_time_to_precache((char *)0x46db55);
}

const char *main_get_map_name(void)
{
  return (const char *)0x46da55;
}

void main_set_difficulty(int16_t difficulty)
{
  if (difficulty >= 0 && difficulty < 4)
    *(int16_t *)0x31fa90 = difficulty;
}

void main_reset_map(void)
{
  *(int16_t *)0x46da40 = -1;
  *(char *)0x46da28 = 0;
  *(char *)0x46da24 = 1;
  *(char *)0x46da3b = 0;
}

void main_revert_map(void)
{
  *(int16_t *)0x46da40 = -1;
  *(char *)0x46da28 = 0;
  *(char *)0x46da26 = 1;
  *(char *)0x46da3b = 0;
}

void main_skip_cinematic(void)
{
  *(int16_t *)0x46da40 = -1;
  *(char *)0x46da28 = 0;
  *(char *)0x46da27 = 1;
}

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

void main_save_map_safe(void)
{
  if (*(char *)0x46da28 != 0 && *(char *)0x46da2a != 0)
    return;
  *(char *)0x46da28 = 1;
  *(char *)0x46da29 = 1;
  *(char *)0x46da2a = 1;
  *(int *)0x46da2c = 0;
  *(int *)0x46da30 = 0;
  *(int16_t *)0x46da38 = 0;
}

void main_won_map(void)
{
  *(char *)0x46da28 = 0;
  *(char *)0x46da3a = 1;
}

void FUN_00100380(void)
{
  *(char *)0x46da28 = 0;
  *(char *)0x46da3b = 1;
}

void main_respawn(char flag)
{
  *(char *)0x46da3c = 1;
  if (flag)
    *(int16_t *)0x46da4e = 0x5b;
}

void main_save_core(void)
{
  *(char *)0x46da3d = 1;
  csstrcpy((char *)0x46dd55, (char *)0x28b198);
}

void main_save_core_name(const char *name)
{
  if (csstrlen(name) >= 0x40) {
    display_assert((char *)0x28b1a4, "c:\\halo\\SOURCE\\main\\main.c", 0x3a5, 0);
  }
  csstrncpy((char *)0x46dd55, name, 0x3f);
  *(char *)0x46da3d = 1;
}

void main_load_core(void)
{
  *(char *)0x46da3e = 1;
  csstrcpy((char *)0x46dd55, (char *)0x28b198);
}

void main_load_core_at_startup(void)
{
  *(char *)0x46da3f = 1;
  csstrcpy((char *)0x46dd55, (char *)0x28b198);
}

void main_load_core_name(const char *name)
{
  if (csstrlen(name) >= 0x40) {
    display_assert((char *)0x28b1a4, "c:\\halo\\SOURCE\\main\\main.c", 0x3c9, 0);
  }
  csstrncpy((char *)0x46dd55, name, 0x3f);
  *(char *)0x46da3e = 1;
}

void main_load_core_name_at_startup(const char *name)
{
  if (csstrlen(name) >= 0x40) {
    display_assert((char *)0x28b1a4, "c:\\halo\\SOURCE\\main\\main.c", 0x3d7, 0);
  }
  csstrncpy((char *)0x46dd55, name, 0x3f);
  *(char *)0x46da3f = 1;
}

void main_switch_structure_bsp(int16_t bsp_index)
{
  void *scenario = global_scenario_get();
  if (bsp_index < 0 || bsp_index >= *(int *)((char *)scenario + 0x5a4)) {
    console_warning((char *)0x28b1e0, (int)bsp_index);
    return;
  }
  if (bsp_index == *(int16_t *)0x326a0c) {
    console_warning((char *)0x28b20c, (int)bsp_index);
    return;
  }
  *(int16_t *)0x46da40 = bsp_index;
  hud_load(1);
}

void main_skip(int16_t level)
{
  if (level > 0xf) {
    error(2, (char *)0x28b238);
    return;
  }
  *(int16_t *)0x46da4a = level;
  *(char *)0x46da49 = 1;
}

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

int main_get_solo_level_from_name(const char *map_name)
{
  char buf[0x80];
  static const struct {
    const char *needle;
    int index;
  } levels[] = {
      {(char *)0x284a8c, 0}, {(char *)0x284a50, 1}, {(char *)0x284a14, 2},
      {(char *)0x2849d8, 3}, {(char *)0x28499c, 4}, {(char *)0x284960, 5},
      {(char *)0x284924, 6}, {(char *)0x2848e8, 7}, {(char *)0x2848ac, 8},
      {(char *)0x284870, 9},
  };
  int i;

  csstrncpy(buf, map_name, 0x7f);
  buf[0x7f] = 0;
  csstr_tolower(buf);
  for (i = 0; i < 10; i++) {
    if (crt_strstr(buf, levels[i].needle) != 0)
      return levels[i].index;
  }
  return -1;
}

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

int16_t main_get_window_count(void)
{
  if (game_engine_force_single_screen() || cinematic_in_progress())
    return 1;
  if (local_player_count() < 1)
    return 1;
  if (local_player_count() > 4)
    return 4;
  return local_player_count();
}

void main_crash(int unused)
{
  *(int *)0 = (int)0x28b5a8;
}

void main_print_version(void)
{
  console_printf(0, (char *)0x28b5d4);
}

void main_save_map_no_timeout(void)
{
  if (*(char *)0x46da28 != 0 && *(char *)0x46da2a == 0)
    return;
  *(char *)0x46da28 = 1;
  *(char *)0x46da29 = 1;
  *(int *)0x46da2c = 0;
  *(int *)0x46da30 = 0;
  *(int16_t *)0x46da38 = 0;
  *(char *)0x46da2a = 0;
}

void main_roll_credits(void)
{
  error(2, (char *)0x28b68c);
  main_menu_load();
  FUN_000dc110();
}

