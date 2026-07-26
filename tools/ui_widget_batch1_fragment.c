/* --- ui_widget.obj batch1 drafts (2026-07-26) --- */

bool event_controller_index_compatible_with_widget(void *widget,
                                                   void *event_data)
{
  int16_t event_player;
  int16_t widget_player;

  event_player = *(int16_t *)((char *)event_data + 8);
  if (event_player == -1)
    return true;
  widget_player = *(int16_t *)((char *)widget + 2);
  if (event_player == widget_player)
    return true;
  return false;
}

void set_ui_plasma_effect_color(float r, float g, float b, float a)
{
  *(float *)0x5aa460 = r;
  *(float *)0x5aa464 = g;
  *(float *)0x5aa468 = b;
  *(float *)0x5aa46c = a;
}

void ui_widgets_set_fade_value(float fade)
{
  *(float *)0x46cc4c = fade;
}

void ui_widget_debug_show_path(char show)
{
  *(char *)0x46cc84 = show;
}

int widget_instance_count_children(void *widget)
{
  void *child;
  int count;

  count = 0;
  if (widget == NULL)
    return 0;
  child = *(void **)((char *)widget + 0x34);
  while (child != NULL) {
    count++;
    child = *(void **)((char *)child + 0x2c);
  }
  return count;
}

void *widget_instance_get_nth_child(void *widget, int index)
{
  void *child;
  int i;

  if (widget == NULL) {
    display_assert((char *)0x2832a8, (char *)0x283280, 0x41a, 1);
    system_exit(-1);
  }
  child = *(void **)((char *)widget + 0x34);
  if (index <= 0)
    return child;
  for (i = 0; i < index; i++) {
    if (child == NULL)
      return NULL;
    child = *(void **)((char *)child + 0x2c);
  }
  return child;
}

void widget_free(void *block)
{
  stack_memory_pool_deallocate(*(void **)0x31e04c, block);
}

char ui_widgets_active(void)
{
  int *slot;

  if (*(char *)0x46cc82 == 0)
    return 0;
  slot = (int *)0x46cc20;
  while ((int)slot < 0x46cc30) {
    if (*slot != 0)
      return 1;
    slot++;
  }
  return 0;
}

char ui_widgets_active_for_local_player(int16_t local_player_index)
{
  int *slot;
  void *widget;

  if (local_player_index < 0 || local_player_index >= 4) {
    display_assert((char *)0x2832b0, (char *)0x283280, 0x456, 1);
    system_exit(-1);
  }
  if (*(char *)0x46cc82 == 0)
    return 0;
  slot = (int *)0x46cc20;
  while ((int)slot < 0x46cc30) {
    widget = (void *)*slot;
    if (widget != NULL &&
        *(int16_t *)((char *)widget + 8) == local_player_index)
      return 1;
    slot++;
  }
  return 0;
}

float FUN_000e3e60(int a, float b)
{
  float product;
  product = (float)a * *(float *)0x255ef8 * b;
  return product * *(double *)0x2573d8;
}

int widget_instance_get_child_index_from_parent(void *widget)
{
  void *parent;
  void *sibling;
  int index;

  parent = *(void **)((char *)widget + 0x30);
  if (parent == NULL)
    return -1;
  sibling = *(void **)((char *)parent + 0x34);
  if (sibling == NULL)
    return -1;
  index = 0;
  while (sibling != NULL) {
    if (sibling == widget)
      return index;
    sibling = *(void **)((char *)sibling + 0x2c);
    index++;
  }
  return -1;
}

void widget_instance_set_visibility_recursive(void *widget, char visible)
{
  void *child;

  if (widget == NULL) {
    display_assert((char *)0x2832a8, (char *)0x283280, 0x743, 1);
    system_exit(-1);
  }
  *(char *)((char *)widget + 0x10) = visible;
  child = *(void **)((char *)widget + 0x34);
  while (child != NULL) {
    widget_instance_set_visibility_recursive(child, visible);
    child = *(void **)((char *)child + 0x2c);
  }
}

void main_menu_active(char active)
{
  *(char *)0x46cc88 = active;
}

char main_menu_is_active(void)
{
  return *(char *)0x46cc88;
}

void ui_set_next_level(int16_t level_index)
{
  const char *map_name;

  if (level_index == -1) {
    main_goto_main_menu();
    return;
  }
  if (level_index < 0 || level_index > 9) {
    error(2, (char *)0x283318);
    main_goto_main_menu();
    return;
  }
  map_name = main_get_solo_level_name(level_index);
  main_set_map_name(map_name);
  main_menu_switch_to_single_player();
}

void display_error_deferred(int16_t error_handle, int16_t local_player_index,
                            char a3, char a4)
{
  ui_widget_deferred_error_t *slots;
  ui_widget_deferred_error_t *slot;
  int index;

  if (local_player_index != -1) {
    if (local_player_index < 0 || local_player_index >= 4) {
      display_assert((char *)0x283424, (char *)0x283280, 0x8f0, 1);
      system_exit(-1);
    }
  }
  index = (int)local_player_index;
  if (local_player_index == -1)
    index = 0;
  slots = (ui_widget_deferred_error_t *)0x46cc50;
  slot = &slots[index];
  if (slot->error_handle != -1) {
    error(2, (char *)0x2833d0, index);
    return;
  }
  slot->error_handle = error_handle;
  slot->local_player_index = local_player_index;
  slot->a3 = a3;
  slot->a4 = a4;
}

void display_error_abort_to_dashboard_deferred(int16_t error_handle, char flag)
{
  if (*(int16_t *)0x46cc68 != -1) {
    error(2, (char *)0x283460);
    return;
  }
  *(int16_t *)0x46cc68 = error_handle;
  *(char *)0x46cc6a = flag;
}

void ui_widget_link_child(void *parent, void *child)
{
  void *first;
  void *last;

  first = *(void **)((char *)parent + 0x34);
  if (*(void **)((char *)parent + 0x28) != NULL ||
      *(void **)((char *)parent + 0x2c) != NULL) {
    display_assert((char *)0x283588, (char *)0x283280, 0xa9f, 1);
    system_exit(-1);
  }
  if (first != NULL) {
    last = first;
    while (*(void **)((char *)last + 0x2c) != NULL)
      last = *(void **)((char *)last + 0x2c);
    if (*(void **)((char *)last + 0x2c) != NULL) {
      display_assert((char *)0x28356c, (char *)0x283280, 0xaa9, 1);
      system_exit(-1);
    }
    *(void **)((char *)last + 0x2c) = child;
    *(void **)((char *)child + 0x28) = last;
  } else {
    *(void **)((char *)parent + 0x34) = child;
  }
}

float widget_instance_get_opacity_product(void *widget)
{
  float opacity;
  void *node;

  opacity = *(float *)((char *)widget + 0x24);
  node = *(void **)((char *)widget + 0x30);
  while (node != NULL) {
    opacity = opacity * *(float *)((char *)node + 0x24);
    node = *(void **)((char *)node + 0x30);
  }
  return opacity;
}

char widget_instance_is_visible_in_parent_chain(void *widget)
{
  void *node;
  void *tag;
  char list_visible;

  if (*((char *)widget + 0x12) != 0)
    return 0;
  node = *(void **)((char *)widget + 0x30);
  if (node == NULL)
    return 1;
  tag = tag_get(0x44654c61, *(int *)node);
  list_visible = 1;
  while (node != NULL && list_visible) {
    tag = tag_get(0x44654c61, *(int *)node);
    if ((*(char *)((char *)tag + 0x2c) & 1) == 0) {
      if (*(int16_t *)((char *)node + 0xe) != 2 &&
          *(int16_t *)((char *)node + 0xe) != 3)
        list_visible = 0;
    }
    node = *(void **)((char *)node + 0x30);
  }
  return list_visible;
}

char widget_instance_parent_allows_focus(void *widget)
{
  void *parent;
  void *tag;

  parent = *(void **)((char *)widget + 0x30);
  if (parent == NULL)
    return 1;
  if (*(void **)((char *)parent + 0x38) == widget)
    return 1;
  parent = *(void **)((char *)parent + 0x30);
  if (parent == NULL)
    return 1;
  if (*(void **)((char *)parent + 0x38) != parent)
    return 0;
  if (*(int16_t *)((char *)parent + 0xe) == 2 ||
      *(int16_t *)((char *)parent + 0xe) == 3)
    return 1;
  while (parent != NULL) {
    tag = tag_get(0x44654c61, *(int *)parent);
    if (*(int *)((char *)tag + 0x54) <= 0) {
      if (*(int16_t *)((char *)parent + 0xe) != 2 &&
          *(int16_t *)((char *)parent + 0xe) != 3)
        return 0;
    }
    parent = *(void **)((char *)parent + 0x30);
  }
  return 1;
}

int16_t ui_widget_find_localized_string_index(wchar_t *needle)
{
  int index;
  wchar_t *candidate;
  int len;

  index = 0;
  while (index < 0x28) {
    candidate = *(wchar_t **)(0x31e098 + index * 4);
    len = _wcslen(candidate);
    if (_wcsnicmp(needle, candidate, len) == 0)
      return (int16_t)index;
    index++;
  }
  return (int16_t)-1;
}

void FUN_000e4c70(void *draw_state, void *cursor, int string_index)
{
  int16_t indent_delta;
  int bounds[2];

  indent_delta = *(int16_t *)((char *)draw_state + 2) -
                 *(int16_t *)((char *)cursor + 2);
  if (indent_delta < 0) {
    error(2, (char *)0x2835f0);
    if (indent_delta < 0)
      indent_delta = 0;
  }
  draw_string_set_indents(0, indent_delta);
  FUN_0019cdb0((short *)bounds, cursor, (short *)draw_state,
               (short *)draw_state);
  *(int16_t *)((char *)draw_state + 2) -= 3;
  bounds[1] = *(int16_t *)((char *)cursor + 2);
  rasterizer_draw_string(0, bounds, 0, 0, string_index);
  *(int16_t *)cursor = *(int16_t *)draw_state;
}

char ui_widget_match_localized_substring(wchar_t *text)
{
  wchar_t *cursor;
  int16_t index;

  if (text == NULL) {
    display_assert((char *)0x27b838, (char *)0x283280, 0x1055, 1);
    system_exit(-1);
    return 0;
  }
  cursor = _wcschr(text, 0x25);
  if (cursor == NULL)
    return 0;
  cursor++;
  for (;;) {
    index = ui_widget_find_localized_string_index(cursor);
    if (index != -1)
      return 1;
    cursor = _wcschr(cursor, 0x25);
    if (cursor == NULL)
      return 0;
    cursor++;
  }
}

char ui_widget_player_prefers_metric_units(int16_t player_index)
{
  int16_t resolved;
  char prefs[0x18];

  resolved = player_index;
  if (resolved == -1)
    resolved = local_player_get_next(-1);
  csmemset(prefs, 0, 0x18);
  if (resolved != -1)
    input_abstraction_get_local_player_preferences(resolved, prefs);
  if (*(int16_t *)(prefs + 0x14) == 1)
    return 1;
  if (*(int16_t *)(prefs + 0x14) == 3)
    return 1;
  return 0;
}

void get_ui_rgb_white(float *out)
{
  (void)*(float **)0x2ee708;
  out[0] = *(float *)0x31e148;
  out[1] = *(float *)0x31e14c;
  out[2] = *(float *)0x31e150;
}

void get_ui_argb_white(float *out)
{
  float *src;

  src = *(float **)0x2ee6c4;
  out[0] = src[0];
  out[1] = *(float *)0x31e148;
  out[2] = *(float *)0x31e14c;
  out[3] = *(float *)0x31e150;
}

void __stdcall ui_widget_filesystem_check_thread_proc(int unused)
{
  int16_t result;
  int profile_index;
  int device_id;

  (void)unused;
  result = saved_game_perform_file_system_checks();
  *(int16_t *)0x46cc80 = result;
  if (result == 0) {
    device_id = -1;
    profile_index = 1;
    FUN_001c26b0(device_id, &profile_index, &device_id);
    FUN_001c0d50(device_id, &profile_index, &device_id, 1);
    player_ui_get_player1_last_used_profile_index();
  }
}

unsigned int modulate_pixel32_by_real_alpha(unsigned int pixel, float alpha)
{
  int alpha_int;
  unsigned int rgb;
  float scaled;

  alpha_int = (int)(pixel >> 24);
  if (alpha_int < 0)
    scaled = (float)alpha_int + *(float *)0x25fb8c;
  else
    scaled = (float)alpha_int;
  scaled = scaled * alpha;
  alpha_int = (int)scaled;
  rgb = pixel & 0xffffff;
  return rgb | ((unsigned int)alpha_int << 24);
}

void ui_widgets_close_stack_for_player(int16_t player_index)
{
  int *stack_head;
  void *widget;
  void *pool;

  if (player_index < 0 || player_index >= 4) {
    display_assert((char *)0x2832b0, (char *)0x283280, 0x482, 1);
    system_exit(-1);
  }
  stack_head = (int *)0x46cc30;
  while ((int)stack_head < 0x46cc40) {
    widget = *(void **)(stack_head - 4);
    if (widget != NULL && *(int16_t *)((char *)widget + 8) == player_index)
      ui_widget_close(widget);
    while (*stack_head != 0) {
      pool = *(void **)0x31e04c;
      widget = (void *)*stack_head;
      *stack_head = *(int *)(widget + 0xc);
      stack_memory_pool_deallocate(pool, widget);
    }
    stack_head++;
  }
}

void ui_widgets_pop_stack(int16_t player_index)
{
  int *head;
  ui_widget_pending_load_t pending;

  if (player_index == -1)
    player_index = 0;
  else if (player_index < 0 || player_index >= 4) {
    display_assert((char *)0x282750, (char *)0x283280, 0x4b4, 1);
    system_exit(-1);
  }
  head = (int *)(0x46cc30 + (int)player_index * 4);
  if (*head != 0)
    ui_widget_pending_load_pop(head, &pending);
}

void main_screen_shell_begin_fade(int fade_duration)
{
  int *slot;
  void *widget;
  void *pool;
  int tick_now;

  ui_widget_stop_attract_mode();
  slot = (int *)0x46cc20;
  tick_now = *(int *)0x46cc40;
  while ((int)slot < 0x46cc30) {
    widget = (void *)*slot;
    if (widget != NULL && *((char *)widget + 0x15) == 0) {
      *(int *)((char *)widget + 0x20) = fade_duration;
      *(int *)((char *)widget + 0x1c) =
        tick_now - *(int *)((char *)widget + 0x18) + 0x64;
      while (slot[4] != 0) {
        pool = *(void **)0x31e04c;
        widget = (void *)slot[4];
        slot[4] = *(int *)(widget + 0xc);
        stack_memory_pool_deallocate(pool, widget);
      }
    }
    slot++;
  }
}

void ui_play_audio_feedback_sound(int16_t sound_selector)
{
  int tag_index;

  switch (sound_selector) {
  case 1:
    tag_index = tag_loaded((char *)0x28380c, 0x736e6421);
    break;
  case 2:
    tag_index = tag_loaded((char *)0x2837f4, 0x736e6421);
    break;
  case 3:
    tag_index = tag_loaded((char *)0x2837e0, 0x736e6421);
    break;
  case 4:
    tag_index = tag_loaded((char *)0x2837c4, 0x736e6421);
    break;
  default:
    return;
  }
  if (tag_index == -1)
    return;
  sound_impulse_start(tag_index, 1.0f);
}

void FUN_000e76b0(void *widget, void *tag, void *a, float d, int e, int f)
{
  void *overlay;
  void *child;
  int child_index;
  char selected;

  overlay = *(void **)((char *)widget + 0x48);
  if (overlay != NULL) {
    float opacity;
    opacity = widget_instance_get_opacity_product(widget);
    *(float *)((char *)overlay + 0x24) = opacity;
    FUN_000e73c0(overlay, a, d, 0, 1);
  }
  if ((*(char *)((char *)tag + 0x150) & 1) == 0) {
    *(int16_t *)((char *)widget + 0x3e) = 0;
    return;
  }
  child = *(void **)((char *)widget + 0x34);
  child_index = 0;
  while (child != NULL) {
    if (child_index >= *(int16_t *)((char *)widget + 0x44))
      break;
    selected = (char)(child_index == *(int16_t *)((char *)widget + 0x3c));
    FUN_000e73c0(child, a, d, f, selected);
    child = *(void **)((char *)child + 0x2c);
    child_index++;
  }
  *(int16_t *)((char *)widget + 0x3e) = 0;
}

void network_game_reset_to_pregame_ui(void)
{
  void *loaded;
  char splitscreen;

  ui_widgets_close_all();
  splitscreen = network_game_is_splitscreen_local();
  if (splitscreen) {
    if (FUN_0012a1a0()) {
      loaded = ui_widget_load_by_name_or_tag((char *)0x284370, -1, 0, -1, -1,
                                             -1, -1);
      if (loaded == NULL) {
        error(2, (char *)0x284338);
        return;
      }
    } else {
      loaded = ui_widget_load_by_name_or_tag((char *)0x2842d8, -1, 0, -1, -1,
                                             -1, -1);
      if (loaded == NULL) {
        error(2, (char *)0x2842ac);
        return;
      }
    }
    return;
  }
  if (network_game_server_get() != NULL) {
    network_game_server_pause_countdown(network_game_server_get(), 1);
    loaded = ui_widget_load_by_name_or_tag((char *)0x284250, -1, 0, -1, -1,
                                           -1, -1);
    if (loaded == NULL)
      error(2, (char *)0x2842ac);
    return;
  }
  loaded = ui_widget_load_by_name_or_tag((char *)0x2828e0, -1, 0, -1, -1, -1,
                                         -1);
  if (loaded == NULL)
    error(2, (char *)0x284220);
}

char FUN_000e9a60(void *widget)
{
  csmemset((void *)0x46cce8, 0, 0x50);
  *(int *)((char *)widget + 0x40) = 0;
  *(int16_t *)((char *)widget + 0x44) = 0;
  return 1;
}

char ui_widget_event_handler_set_difficulty(void *widget, void *event_data,
                                            bool *widget_deleted)
{
  int16_t player_index;

  (void)event_data;
  (void)widget_deleted;
  player_index = *(int16_t *)((char *)widget + 0x3c);
  if (player_index < 0 || player_index >= 4) {
    display_assert((char *)0x285ad8, (char *)0x2859a4, 0x313, 1);
    system_exit(-1);
  }
  main_set_difficulty(player_index);
  ui_play_audio_feedback_sound(2);
  return 1;
}

char display_error_abort_to_dashboard(void *widget, void *event_data,
                                      bool *widget_deleted)
{
  int16_t player_index;

  (void)event_data;
  (void)widget_deleted;
  player_index = *(int16_t *)((char *)widget + 8);
  if (player_index == -1) {
    display_assert((char *)0x285b10, (char *)0x2859a4, 0x369, 1);
    system_exit(-1);
  }
  player_ui_local_player_joined_multiplayer_game(player_index);
  return 1;
}

char FUN_000E9D40(void)
{
  char ok;

  ok = 1;
  dispose_global_network_game_server();
  player_ui_clear_multiplayer_variant();
  network_game_set_accept_remote_connections(1);
  if (network_game_server_get() == NULL) {
    game_engine_playlist_initialize();
    ok = FUN_0012a890();
    if (ok == 1) {
      network_game_server_pause_countdown(network_game_server_get(), 1);
      game_engine_playlist_begin();
      set_game_connection(2);
    }
  }
  if (ok != 0) {
    if (network_game_client_get() == NULL)
      ok = FUN_0012a250();
  }
  if (ok == 0) {
    dispose_global_network_game_client();
    dispose_global_network_game_server();
    network_game_set_accept_remote_connections(0);
    player_ui_clear_multiplayer_variant();
    error(2, (char *)0x2828ac);
  }
  return ok;
}

char FUN_000e9fd0(void *widget)
{
  *(int *)((char *)widget + 0x40) = 0;
  *(int16_t *)((char *)widget + 0x44) = 0;
  return 1;
}

char FUN_000ea1f0(void *widget)
{
  *(int *)((char *)widget + 0x40) = 0;
  *(int16_t *)((char *)widget + 0x44) = 0;
  return 1;
}

char FUN_000ea540(void *widget)
{
  if (*(int *)((char *)widget + 0x40) != 0) {
    widget_free((void *)*(int *)((char *)widget + 0x40));
    *(int *)((char *)widget + 0x40) = 0;
  }
  *(int16_t *)((char *)widget + 0x44) = 0;
  return 1;
}

char split_screen_game_initialize(void *widget, void *player_data)
{
  void *client;
  int machine_index;
  int i;
  void *network_player;
  char local_prefs[0x24];
  char updated;

  if (player_data == NULL) {
    display_assert((char *)0x286184, (char *)0x2859a4, 0x624, 1);
    system_exit(-1);
  }
  client = FUN_0012a0a0();
  if (client == NULL || *((char *)client + 0xc0) != 1)
    return 1;
  machine_index = network_game_client_get_local_machine_index();
  if (machine_index == -1)
    return 1;
  for (i = 0; i < 0x10; i++) {
    network_player = (void *)((char *)client + 0x242 + i * 0x20);
    if (network_player_is_valid((char *)network_player - 0x1c) &&
        *(int16_t *)network_player == machine_index &&
        *(int16_t *)((char *)network_player + 1) ==
            *(int16_t *)((char *)player_data + 2))
      goto found;
  }
  return 1;
found:
  csmemcpy(local_prefs, (char *)client + 0x226 + i * 0x20, 0x20);
  if (local_prefs[6] == 0)
    local_prefs[6] = 1;
  updated = network_game_client_update_local_player_data(
    network_game_client_get(), local_prefs);
  if (updated == 0)
    error(2, (char *)0x286150);
  return 1;
}

char FUN_000eab70(void *widget)
{
  if (*(int *)((char *)widget + 0x40) != 0) {
    widget_free((void *)*(int *)((char *)widget + 0x40));
    *(int *)((char *)widget + 0x40) = 0;
  }
  *(int16_t *)((char *)widget + 0x44) = 0;
  return 1;
}

char FUN_000ecd50(void *widget)
{
  void *profile;
  int game_type;

  profile = player_ui_get_edit_playlist_profile();
  if (*(int16_t *)((char *)widget + 0xe) != 3) {
    display_assert((char *)0x287ab0, (char *)0x2859a4, 0xab2, 1);
    system_exit(-1);
  }
  if (profile == NULL) {
    error(2, (char *)0x286550);
    return 0;
  }
  game_type = *(int *)((char *)profile + 0x18) - 1;
  if (game_type == 0)
    *(int16_t *)((char *)widget + 0x3c) = 1;
  else if (game_type == 1)
    *(int16_t *)((char *)widget + 0x3c) = 2;
  else if (game_type == 2)
    *(int16_t *)((char *)widget + 0x3c) = 3;
  else if (game_type == 3)
    *(int16_t *)((char *)widget + 0x3c) = 4;
  else
    *(int16_t *)((char *)widget + 0x3c) = 0;
  *(void **)((char *)widget + 0x38) =
    widget_instance_get_nth_child(widget, *(int16_t *)((char *)widget + 0x3c));
  return 1;
}

char playlist_profile_change_koth_rules(void *widget)
{
  void *profile;
  void *buffer;

  profile = player_ui_get_edit_playlist_profile();
  if (*(int16_t *)((char *)widget + 0xe) != 1) {
    display_assert((char *)0x287af0, (char *)0x2859a4, 0xad2, 1);
    system_exit(-1);
  }
  if (profile == NULL) {
    error(2, (char *)0x286550);
    return 0;
  }
  buffer = ui_widget_realloc(*(int *)((char *)widget + 0x3c), 0x100,
                             (char *)0x2859a4, 0xad6);
  *(void **)((char *)widget + 0x3c) = buffer;
  if (buffer == NULL)
    return 1;
  ustrncpy((char *)buffer, (char *)profile, 0x7f);
  *(int16_t *)((char *)buffer + 0xfe) = 0;
  return 1;
}

char FUN_000ea010(void)
{
  char ok;

  ok = 1;
  network_game_set_accept_remote_connections(0);
  if (network_game_server_get() == NULL) {
    game_engine_playlist_initialize();
    ok = FUN_0012a890();
    if (ok == 1) {
      game_engine_playlist_begin();
      set_game_connection(2);
    }
  }
  if (ok != 0) {
    if (network_game_client_get() == NULL)
      ok = FUN_0012a250();
  }
  if (ok == 0) {
    dispose_global_network_game_client();
    dispose_global_network_game_server();
    player_ui_clear_multiplayer_variant();
    error(2, (char *)0x285d48);
  }
  return ok;
}

char FUN_000ea100(void *widget)
{
  void *tag;
  char map_name[0x100];
  int16_t map_count;
  int16_t map_index;

  tag = tag_get(0x44654c61, *(int *)widget);
  if (*(int16_t *)tag != 2) {
    display_assert((char *)0x285db8, (char *)0x2859a4, 0x4cc, 1);
    system_exit(-1);
  }
  if (*(int *)((char *)tag + 0x3e0) != 3) {
    display_assert((char *)0x285d78, (char *)0x2859a4, 0x4cd, 1);
    system_exit(-1);
  }
  *(int *)((char *)widget + 0x40) = 0x31e4c8;
  map_count = 0xd;
  *(int16_t *)((char *)widget + 0x44) = map_count;
  if (!saved_game_file_retrieve_last_used_multiplayer_map(map_name))
    return 1;
  *(int16_t *)((char *)widget + 0x3c) = 0;
  while (*(int16_t *)((char *)widget + 0x3c) < map_count) {
    map_index = *(int16_t *)((char *)widget + 0x3c);
    if (crt_stricmp(*(char **)(0x31e4c8 + map_index * 4), map_name) == 0)
      break;
    (*(int16_t *)((char *)widget + 0x3c))++;
  }
  if (*(int16_t *)((char *)widget + 0x3c) == map_count)
    *(int16_t *)((char *)widget + 0x3c) = 0;
  return 1;
}

char FUN_000eceb0(void *widget)
{
  void *profile;
  void *list_widget;
  void *item_widget;
  void *sibling;
  int16_t team_index;

  profile = player_ui_get_edit_playlist_profile();
  if (*(int16_t *)((char *)widget + 0xe) != 3) {
    display_assert((char *)0x287b1c, (char *)0x2859a4, 0xaed, 1);
    system_exit(-1);
  }
  if (profile == NULL) {
    error(2, (char *)0x286550);
    return 0;
  }
  list_widget = *(void **)((char *)widget + 0x34);
  if (list_widget == NULL) {
    display_assert((char *)0x2868d0, (char *)0x2859a4, 0xaf5, 1);
    system_exit(-1);
  }
  item_widget = *(void **)((char *)list_widget + 0x34);
  while (item_widget != NULL) {
    if (*(int16_t *)((char *)item_widget + 0xe) == 2)
      break;
    item_widget = *(void **)((char *)item_widget + 0x2c);
  }
  if (item_widget == NULL) {
    display_assert((char *)0x2868a8, (char *)0x2859a4, 0xaf7, 1);
    system_exit(-1);
  }
  team_index = 0;
  if (*(char *)((char *)profile + 0x4c) == 0)
    team_index = 1;
  *(int16_t *)((char *)item_widget + 0x3c) = team_index;
  sibling = *(void **)((char *)list_widget + 0x2c);
  if (sibling == NULL) {
    display_assert((char *)0x286848, (char *)0x2859a4, 0xb00, 1);
    system_exit(-1);
  }
  item_widget = *(void **)((char *)sibling + 0x34);
  while (item_widget != NULL) {
    if (*(int16_t *)((char *)item_widget + 0xe) == 2)
      break;
    item_widget = *(void **)((char *)item_widget + 0x2c);
  }
  *(int16_t *)((char *)item_widget + 0x3c) = 0;
  return 1;
}

