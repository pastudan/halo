/* --- ui_widget.obj batch2 drafts (2026-07-26) --- */

static void *ui_widget_find_child_type(void *list_widget, int16_t type)
{
  void *child;

  if (list_widget == NULL)
    return NULL;
  child = *(void **)((char *)list_widget + 0x34);
  while (child != NULL) {
    if (*(int16_t *)((char *)child + 0xe) == type)
      return child;
    child = *(void **)((char *)child + 0x2c);
  }
  return NULL;
}

static void *ui_widget_get_playlist_profile(void)
{
  return *(void **)0x31e494;
}

static void ui_widget_assert_fail(const char *msg, unsigned line)
{
  display_assert(msg, (char *)0x2859a4, line, 1);
  system_exit(-1);
}

static wchar_t *ui_widget_wcsstr(const wchar_t *haystack, const wchar_t *needle)
{
  const wchar_t *h;
  const wchar_t *n;

  if (needle == NULL || *needle == 0)
    return (wchar_t *)haystack;
  if (haystack == NULL)
    return NULL;
  while (*haystack != 0) {
    h = haystack;
    n = needle;
    while (*h != 0 && *n != 0 && *h == *n) {
      h++;
      n++;
    }
    if (*n == 0)
      return (wchar_t *)haystack;
    haystack++;
  }
  return NULL;
}

static wchar_t *ui_widget_wcschr(wchar_t *s, wchar_t c)
{
  while (*s != 0) {
    if (*s == c)
      return s;
    s++;
  }
  return NULL;
}

static void ui_widget_wcscpy(wchar_t *dest, const wchar_t *src)
{
  while (*src != 0) {
    *dest = *src;
    dest++;
    src++;
  }
  *dest = 0;
}

static void ui_widget_read_draw_color(float color[4])
{
  color[0] = *(float *)0x4d9b18;
  color[1] = *(float *)0x4d9b1c;
  color[2] = *(float *)0x4d9b20;
  color[3] = *(float *)0x4d9b24;
}

void draw_bitmap_in_rect(int bitmap, int16_t *src_rect, int16_t *dst_rect,
                         int16_t *clip_rect, int flags, int param_6, int param_7)
{
  void *bitmap_ptr;
  float color[4];
  float uv[4];
  float xy[4];
  char sprite_buf[0x8c];
  char render_state[0x50];
  void *tag_data;
  void *elem;
  int tag_index;
  int i;
  float scale_x;
  float scale_y;
  int16_t local_src[4];
  int16_t local_dst[4];

  (void)param_6;
  (void)param_7;
  bitmap_ptr = (void *)(size_t)bitmap;
  if (bitmap == 0 || dst_rect == NULL)
    return;

  color[0] = *(float *)0x5aa460;
  color[1] = *(float *)0x5aa464;
  color[2] = *(float *)0x5aa468;
  color[3] = *(float *)0x5aa46c;

  if (src_rect == NULL) {
    local_src[0] = 0;
    local_src[1] = 0;
    local_src[2] = *(int16_t *)((char *)bitmap_ptr + 4);
    local_src[3] = *(int16_t *)((char *)bitmap_ptr + 6);
    src_rect = local_src;
  }

  local_dst[0] = dst_rect[0];
  local_dst[1] = dst_rect[1];
  local_dst[2] = dst_rect[2];
  local_dst[3] = dst_rect[3];

  if (clip_rect != NULL) {
    if (clip_rect[1] > local_dst[1])
      xy[1] = (float)clip_rect[1];
    if (clip_rect[3] < local_dst[3])
      xy[3] = (float)clip_rect[3];
    if (clip_rect[0] > local_dst[0])
      xy[0] = (float)clip_rect[0];
    if (clip_rect[2] < local_dst[2])
      xy[2] = (float)clip_rect[2];
  }

  scale_x = (float)(src_rect[2] - src_rect[0]);
  if (scale_x < *(float *)0x2533c8)
    scale_x = *(float *)0x2533c8;
  scale_x = (float)(local_dst[2] - local_dst[0]) / scale_x;

  scale_y = (float)(src_rect[3] - src_rect[1]);
  if (scale_y < *(float *)0x2533c8)
    scale_y = *(float *)0x2533c8;
  scale_y = (float)(local_dst[3] - local_dst[1]) / scale_y;

  csmemset(sprite_buf, 0, 0x8c);
  if (flags != 0) {
    csmemset(render_state, 0, 0x50);
    *(void **)(render_state + 0x54) = bitmap_ptr;
    *(float *)(render_state + 0x28) = 1.0f;
    *(float *)(render_state + 0x2c) = 1.0f;
    *(float *)(render_state + 0x30) = 1.0f;
    *(float *)(render_state + 0x34) = 1.0f;
    rasterizer_sprites_render(render_state, sprite_buf);
    return;
  }

  tag_index = interface_get_tag_index(0xf);
  tag_data = tag_get(0x6269746d, tag_index);
  elem = tag_block_get_element((char *)tag_data + 0x60, 0, 0);

  for (i = 0; i < 4; i++) {
    uv[i * 2] = ((float *)&color)[i];
    uv[i * 2 + 1] = ((float *)&color)[i];
  }

  csmemset(render_state, 0, 0x50);
  *(void **)(render_state + 0x54) = elem;
  *(void **)(render_state + 0x58) = elem;
  *(void **)(render_state + 0x7c) = bitmap_ptr;
  *(float *)(render_state + 0x28) = color[0];
  *(float *)(render_state + 0x2c) = color[1];
  *(float *)(render_state + 0x30) = color[2];
  *(float *)(render_state + 0x34) = color[3];
  *(char *)(render_state + 0x62) = 0;
  rasterizer_sprites_render(render_state, sprite_buf);
}

void FUN_000e4ad0(void *icon_state, int16_t *cursor, int string_index)
{
  void *globals;
  void *scenario;
  void *elem;
  int out_bitmap;
  int out_sprite;
  int frame;
  int sequence;
  float scale;
  int16_t pos[2];
  float split_scale;

  scenario = global_scenario_get();
  globals = game_globals_get();
  elem = NULL;
  if (*(int *)((char *)globals + 0x140) != 0)
    elem = tag_block_get_element((char *)globals + 0x140, 0, 0x130);

  frame = 0;
  if (*(char *)((char *)icon_state + 0xc) != 0) {
    frame = (int)(system_milliseconds() * 0x1e / 0x41c21e83);
    frame /= (int)(char)*(char *)((char *)icon_state + 0xc);
  }

  sequence = *(int16_t *)icon_state;
  out_bitmap = 0;
  out_sprite = 0;
  FUN_000d16a0(*(int *)((char *)elem + 0xec), sequence, (unsigned int)frame,
               &out_bitmap, &out_sprite);
  if (out_bitmap == 0)
    return;
  if (xbox_texture_cache_get_hardware_format((void *)(size_t)out_bitmap, 0, 1) == 0)
    return;

  split_scale = FUN_000d1690(local_player_count() > 1);
  pos[0] = (int16_t)(int)(split_scale * (float)*(int16_t *)((char *)icon_state + 4) +
                         *(float *)0x2533c8 + (float)cursor[1]);
  pos[1] = (int16_t)(int)((float)*(int16_t *)((char *)icon_state + 6) * split_scale -
                          *(float *)0x253f40 + (float)cursor[2]);

  if ((*(char *)((char *)icon_state + 0xd) & 4) != 0) {
    cursor[1] = (int16_t)(pos[0] + *(int16_t *)((char *)icon_state + 2));
    return;
  }

  if (out_sprite != 0) {
    scale = (*(float *)((char *)(size_t)out_sprite + 4) -
             *(float *)(size_t)out_sprite) *
            (float)*(int16_t *)((char *)(size_t)out_bitmap + 4);
    cursor[1] = (int16_t)(int)(scale + (float)*(int16_t *)((char *)icon_state + 2) +
                               (float)pos[0]);
    return;
  }

  cursor[1] = (int16_t)(*(int16_t *)((char *)(size_t)out_bitmap + 4) +
                        *(int16_t *)((char *)icon_state + 2) + pos[0]);
  (void)scenario;
  (void)string_index;
}

int16_t remap_sticks_for_local_player(int16_t icon_type, int local_player_index)
{
  int16_t index;

  switch (icon_type) {
  case 0x10:
    index = ui_widget_find_localized_string_index((wchar_t *)0x283038);
    if (index != 0x10)
      ui_widget_assert_fail((char *)0x283698, 0x1093);
    index = ui_widget_find_localized_string_index((wchar_t *)0x282f04);
    if (index != 0x1e)
      ui_widget_assert_fail((char *)0x283678, 0x1094);
    if (ui_widget_player_prefers_metric_units((int16_t)local_player_index))
      return 0x10;
    return 0x11;
  case 0x11:
    index = ui_widget_find_localized_string_index((wchar_t *)0x283020);
    if (index != 0x11)
      ui_widget_assert_fail((char *)0x283654, 0x109a);
    index = ui_widget_find_localized_string_index((wchar_t *)0x282ef8);
    if (index != 0x1f)
      ui_widget_assert_fail((char *)0x283634, 0x109b);
    if (ui_widget_player_prefers_metric_units((int16_t)local_player_index))
      return 0x11;
    return 0x12;
  default:
    if (icon_type >= 0x10 && icon_type <= 0x1f)
      return icon_type;
    return icon_type;
  }
}

int FUN_000e5180(wchar_t *text, wchar_t *replacement, void **pool_block)
{
  void *block;
  int match_count;
  int text_len;
  int repl_len;
  int pat_len;
  wchar_t *found;
  int tail_len;
  int new_size;

  match_count = 0;
  if (pool_block == NULL)
    return 0;
  block = *pool_block;
  if (block == NULL)
    return 0;

  text_len = ustrlen(text);
  repl_len = ustrlen(replacement);
  pat_len = ustrlen(block);
  if (repl_len > text_len) {
    found = ui_widget_wcsstr(block, text);
    while (found != NULL) {
      match_count++;
      tail_len = text_len - repl_len;
      csmemcpy(found, replacement, repl_len * 2);
      if (tail_len > 0)
        csmemmove(found + repl_len * 2, found + text_len * 2, tail_len * 2);
      pat_len -= tail_len;
      found = ui_widget_wcsstr(block, text);
    }
    return match_count;
  }

  found = ui_widget_wcsstr(block, text);
  if (found == NULL)
    return 0;
  match_count = 1;
  while (ui_widget_wcsstr(found + text_len, text) != NULL)
    match_count++;

  new_size = (pat_len + (repl_len - text_len) * match_count + 1) * 2;
  block = stack_memory_pool_realloc(*(void **)0x31e04c, (int)(size_t)block,
                                    (unsigned short)new_size, (char *)0x283280,
                                    0x1382);
  if (block == NULL)
    return -1;
  *pool_block = block;

  found = ui_widget_wcsstr(block, text);
  while (found != NULL) {
    csmemmove(found + repl_len * 2, found + text_len * 2,
              (pat_len - (int)(found - (wchar_t *)block) - text_len) * 2);
    csmemcpy(found, replacement, repl_len * 2);
    pat_len += repl_len - text_len;
    found = ui_widget_wcsstr(block, text);
  }
  return match_count;
}

void FUN_000e5b10(void *widget, void *draw_state)
{
  void *tag;
  void *loaded;
  int index;

  if ((*(char *)((char *)widget + 0x150) & 2) == 0)
    return;
  if (*(int16_t *)((char *)draw_state + 0xe) != 2)
    ui_widget_assert_fail((char *)0x283930, 0xa20);
  if (*(int *)((char *)widget + 0x3e0) != 0)
    ui_widget_assert_fail((char *)0x2838c0, 0xa22);
  if (*(int *)((char *)widget + 0xf8) == -1)
    ui_widget_assert_fail((char *)0x283860, 0xa24);

  tag = tag_get(0x75737472, *(int *)((char *)widget + 0xf8));
  *(char *)0x46cc83 = 1;
  index = 0;
  while (index < *(int *)tag) {
    loaded = ui_widget_load_by_name_or_tag(
        0, *(int *)draw_state, (int)(size_t)draw_state,
        *(int16_t *)((char *)draw_state + 8), -1, -1, -1);
    ui_widget_link_child(widget, loaded);
    index++;
  }
  if (*(int *)((char *)tag + 0x54) <= 0)
    error(2, (char *)0x283818);
}

void draw_string_and_hack_in_icons(int16_t *rect, int param_2, int param_3, int param_4,
                                   wchar_t *text, int local_player_index)
{
  wchar_t buf[0x25];
  wchar_t *pct;
  int16_t icon_type;
  void *icon_tag;
  float color[4];
  uint32_t pixel;
  int16_t out_rect[4];
  int16_t bounds[4];

  (void)param_2;
  (void)param_3;
  (void)param_4;
  ui_widget_wcscpy(buf, text);
  pct = ui_widget_wcschr(buf, 0x25);
  if (pct == NULL)
    return;

  *pct = 0;
  pct++;
  draw_string_set_indents(0, (int16_t)(rect[1] - rect[0]));
  bounds[0] = rect[0];
  bounds[1] = rect[1];
  bounds[2] = rect[2];
  bounds[3] = rect[3];
  FUN_0019cdb0(out_rect, pct, bounds, (short *)rect);
  rasterizer_draw_string(bounds, 0, 0, 0, (unsigned short *)pct);

  icon_type = ui_widget_find_localized_string_index(pct);
  if (icon_type < 0) {
    error(2, (char *)0x2835f0);
    return;
  }
  if (icon_type < 0 || icon_type >= 0x12)
    ui_widget_assert_fail((char *)0x2839bc, 0x10f5);

  icon_tag = tag_block_get_element((void *)(*(int *)0x46bd0c + 0xc4), icon_type, 0x10);
  if (*(char *)(0x31e080 + icon_type) != 0) {
    *(char *)((char *)icon_tag + 0xd) &= ~4;
    *(int16_t *)((char *)icon_tag + 2) = -5;
  }

  ui_widget_read_draw_color(color);
  pixel = FUN_000d1c90(color) & 0xffffff;
  pixel |= (uint32_t)(int)(color[0] * *(float *)0x2602c8) << 24;
  (void)pixel;

  out_rect[0] = rect[0];
  out_rect[1] = rect[1];
  FUN_000e4ad0(icon_tag, out_rect, icon_type);
  rect[1]++;
  draw_string_set_indents(0, 0);
  (void)local_player_index;
}

void FUN_000e6140(void *widget, void *draw_state)
{
  void *text_src;
  wchar_t *text;
  int index;
  int entry_offset;

  if (*(int *)((char *)widget + 0xf8) != -1) {
    int16_t font = *(int16_t *)((char *)draw_state + 0x40);
    if (font == -1)
      font = *(int16_t *)((char *)widget + 0x12e);
    text_src = (void *)FUN_0019d420(*(int *)((char *)widget + 0xf8), font);
    text = (wchar_t *)stack_memory_pool_realloc(
      *(void **)0x31e04c, (int)(size_t) * (void **)((char *)draw_state + 0x3c),
      (unsigned short)(ustrlen(text_src) * 2 + 2), (char *)0x283280, 0x1145);
    if (text == NULL)
      *(void **)((char *)draw_state + 0x3c) = (void *)0x283a54;
    else {
      csmemcpy(text, text_src, ustrlen(text_src) * 2 + 2);
      *(void **)((char *)draw_state + 0x3c) = text;
    }
  }

  text = *(wchar_t **)((char *)draw_state + 0x3c);
  if (text == NULL || *text == 0)
    return;

  index = 0;
  entry_offset = 0;
  while (index < *(int *)((char *)widget + 0x60)) {
    void *entry = (char *)widget + 0x64 + entry_offset;
    if (*(char *)entry != 0) {
      text = ui_widget_text_search_and_replace_function_invoke(
        draw_state, *(unsigned short *)((char *)entry + 0x20));
      *(wchar_t **)((char *)draw_state + 0x3c) = text;
      FUN_000e5180(text, (wchar_t *)0x283a54, (void **)((char *)draw_state + 0x3c));
    }
    index++;
    entry_offset += 0x22;
  }

  if (widget_instance_get_opacity_product(widget) <= *(float *)0x2533c8)
    return;

  get_ui_argb_white((float *)draw_state);
  draw_string_set_font(*(int16_t *)((char *)draw_state + 0x40), -1, 0, 0,
                       (float *)draw_state);
  if (ui_widget_match_localized_substring(text))
    draw_string_and_hack_in_icons((int16_t *)draw_state, 0, 0, 0, text, 0);
  else
    rasterizer_draw_string((void *)((char *)draw_state + 0x14), (short *)draw_state,
                           0, 0, (unsigned short *)text);
}

void FUN_000e6450(void *draw_state, void *widget, int param_3, int param_4)
{
  float opacity;
  void *bitmap;
  wchar_t *text;
  void *text_src;
  int16_t rect[4];
  char sprite[0x8c];

  (void)param_3;
  (void)param_4;
  opacity = widget_instance_get_opacity_product(widget);
  if (*(char *)((char *)widget + 0x10) == 0)
    return;

  if (*(int16_t *)((char *)widget + 0x3e) != 0) {
    if (*(int16_t *)((char *)widget + 0x3e) > 0)
      (*(int16_t *)((char *)widget + 0x3e))--;
    else
      (*(int16_t *)((char *)widget + 0x3e))++;
  }

  bitmap = FUN_00077040(*(int *)((char *)draw_state + 0x160), 0, 0);
  if (bitmap != NULL) {
    csmemset(sprite, 0, 0x8c);
    rect[0] = 0;
    rect[1] = 0;
    rect[2] = *(int16_t *)((char *)draw_state + 4);
    rect[3] = *(int16_t *)((char *)draw_state + 6);
    draw_bitmap_in_rect((int)(size_t)bitmap, NULL, rect, NULL, 0, 0, 0);
  }

  if (*(int *)((char *)widget + 0xf8) != -1) {
    text_src = (void *)FUN_0019d420(*(int *)((char *)widget + 0xf8),
                                    *(int16_t *)((char *)widget + 0x12e));
    text = (wchar_t *)stack_memory_pool_allocate(
      *(void **)0x31e04c, (unsigned short)(ustrlen(text_src) * 2 + 2),
      (char *)0x283280, 0x1158);
    if (text != NULL) {
      csmemcpy(text, text_src, ustrlen(text_src) * 2 + 2);
      text = ui_widget_text_search_and_replace_function_invoke(
        draw_state, 0);
      *(wchar_t **)((char *)draw_state + 0x3c) = text;
      FUN_000e5180(text, (wchar_t *)0x283a54, (void **)((char *)draw_state + 0x3c));
      if (opacity > *(float *)0x2533c8) {
        get_ui_rgb_white((float *)draw_state);
        draw_string_set_font(*(int16_t *)((char *)widget + 0x12e), -1, 0, 0,
                             (float *)draw_state);
        rasterizer_draw_string((void *)((char *)draw_state + 0x14),
                               (short *)draw_state, 0, 0, (unsigned short *)text);
      }
      stack_memory_pool_deallocate(*(void **)0x31e04c, text);
    }
  }
}

void FUN_000e73c0(void *widget, int16_t *bounds, float opacity_scale, char param_4,
                  char visible)
{
  void *tag;
  float opacity;
  int index;
  void *bitmap;

  tag = tag_get(0x44654c61, *(int *)widget);
  opacity = *(float *)((char *)widget + 0x24);
  {
    void *parent = *(void **)((char *)widget + 0x30);
    while (parent != NULL) {
      opacity *= *(float *)((char *)parent + 0x24);
      parent = *(void **)((char *)parent + 0x30);
    }
  }

  if (param_4 == 0 && ((*(int *)((char *)tag + 0x2c) >> 8) & 0x20) != 0)
    visible = 1;

  bounds[0] += *(int16_t *)((char *)widget + 0xa);
  bounds[1] += *(int16_t *)((char *)widget + 0xc);

  index = 0;
  while (index < *(int *)((char *)tag + 0x48)) {
    ui_widget_game_data_function_invoke(
      widget, *(int16_t *)(*(int *)((char *)tag + 0x4c) + index * 2));
    index++;
  }

  if (*(char *)((char *)widget + 0x10) == 0)
    return;

  bitmap = FUN_00077040(*(int *)((char *)tag + 0x160), 0, 0);
  if (bitmap != NULL) {
    int16_t rect[4];
    rect[0] = bounds[0];
    rect[1] = bounds[1];
    rect[2] = bounds[0] + *(int16_t *)((char *)widget + 0xa);
    rect[3] = bounds[1] + *(int16_t *)((char *)widget + 0xc);
    draw_bitmap_in_rect((int)(size_t)bitmap, NULL, rect, NULL, 0, 0, 0);
  }

  FUN_000e76b0(widget, tag, bounds, opacity * opacity_scale, param_4, visible);
  if (widget_instance_parent_allows_focus(widget))
    FUN_000e6140(widget, bounds);
  if (*(char *)((char *)widget + 0x11) != 0)
    FUN_000e73c0(widget, bounds, opacity_scale, param_4, visible);
}

void render_ui_widgets_postgame(int16_t local_player_index, int16_t *bounds)
{
  int16_t clip[0x26];
  int stack_index;
  void *widget;
  int16_t inner[2];
  int player_count;

  clip[0] = 0;
  clip[1] = 0;
  clip[2] = 0;
  clip[3] = 0;
  clip[4] = 0;
  clip[5] = 0;
  clip[6] = 0;
  clip[7] = 0;
  clip[8] = 0;
  clip[9] = 0;
  clip[10] = 0;
  clip[11] = 0;
  clip[12] = 0;
  clip[13] = 0;
  clip[14] = 0;
  clip[15] = 0;
  clip[16] = 0;
  clip[17] = 0x00f0;
  clip[18] = 0;
  clip[19] = 0;
  clip[20] = 0;
  clip[21] = 0;
  clip[22] = 0;
  clip[23] = 0;
  clip[24] = 0;
  clip[25] = 0x00f0;
  clip[26] = 0x0140;
  clip[27] = 0x00f0;
  clip[28] = 0;
  clip[29] = 0;
  clip[30] = 0;
  clip[31] = 0;
  clip[32] = 0x0140;
  clip[33] = 0;
  clip[34] = 0;
  clip[35] = 0x00f0;
  clip[36] = 0x0140;
  clip[37] = 0x00f0;

  if (((char (*)(void))FUN_000f5640)())
    return;

  if (local_player_index < 0)
    local_player_index = 0;
  else if (local_player_index > 3)
    local_player_index = 3;

  player_count = local_player_count();
  for (stack_index = 0; stack_index < 4; stack_index++) {
    widget = *(void **)(0x46cc20 + stack_index * 4);
    if (widget == NULL)
      continue;
    if (*(char *)((char *)widget + 0x11) == 1)
      goto render;
    if (*(char *)((char *)widget + 0x15) == 1) {
      if (*(int16_t *)((char *)widget + 8) == local_player_index ||
          *(int16_t *)((char *)widget + 8) == -1 || local_player_index == -1 ||
          *(char *)0x46cc88 == 0)
        goto render;
      continue;
    }
    if (*(int16_t *)((char *)widget + 8) == -1 && stack_index != 0)
      continue;
    if (*(int16_t *)((char *)widget + 8) != local_player_index)
      continue;
  render:
    inner[0] = 0;
    inner[1] = 0;
    inner[0] = (int16_t)(bounds[2] - bounds[0]);
    inner[1] = (int16_t)(bounds[3] - bounds[1]);
    FUN_000e73c0(widget, clip + 18 + (local_player_index + player_count) * 4, 1.0f, 0,
                 1);
  }
}

char FUN_000e98c0(void *widget)
{
  char profile_buf[0x50];
  char profile2[0x38];
  int16_t level_index;
  int16_t difficulty;
  int index;
  void *tag;

  csmemset((void *)0x46cce8, 0, 0x50);
  ((void (*)(void *, int))player_ui_get_active_player_profile)(profile_buf, 0);
  ((void (*)(void *, int16_t *, int16_t *))player_profile_save_last_level_played)(
      profile_buf, &level_index, &difficulty);
  ((void (*)(void *, int))player_ui_get_active_player_profile)(profile2, 1);
  ((void (*)(void *, int16_t *, int16_t *))player_profile_save_last_level_played)(
      profile2, &level_index, &difficulty);

  for (index = 0; index < 0xa; index++) {
    *(int *)(0x46cce8 + index * 8) = *(int *)(0x31e498 + index * 4);
    if (profile_buf[index + 0x14] != 0 || index == level_index + 1 ||
        profile2[index + 0x14] != 0 || index == difficulty + 1) {
      if (index == 0)
        continue;
      *(char *)(0x46cced + index * 8) = (char)((profile_buf[index + 0x14] |
                                                profile2[index + 0x14]) >> 1) &
                                        1;
      *(char *)(0x46ccec + index * 8) = 1;
      *(char *)(0x46ccee + index * 8) =
          (char)((profile_buf[index + 0x14] | profile2[index + 0x14]) >> 2) & 1;
      *(char *)(0x46ccef + index * 8) =
          (char)((profile_buf[index + 0x14] | profile2[index + 0x14]) >> 3) & 1;
    }
  }

  tag = tag_get(0x44654c61, *(int *)widget);
  if (*(int16_t *)tag != 2)
    ui_widget_assert_fail((char *)0x285db8, 0x4cc);
  if (*(int *)((char *)tag + 0x3e0) != 3)
    ui_widget_assert_fail((char *)0x285d78, 0x4cd);

  *(void **)((char *)widget + 0x40) = (void *)0x46cce8;
  *(int16_t *)((char *)widget + 0x44) = 0xa;
  level_index =
      ((int16_t (*)(void))player_ui_get_last_single_player_level_played)();
  if (level_index < 0) {
    *(int16_t *)((char *)widget + 0x3c) = 0;
    return 1;
  }
  if (level_index > 9)
    level_index = 9;
  *(int16_t *)((char *)widget + 0x3c) = level_index;
  difficulty =
      ((int16_t (*)(void))player_ui_get_last_single_player_level_played)();
  *(int16_t *)((char *)widget + 0x44) = difficulty;
  ((int16_t (*)(void))player_ui_get_last_single_player_level_played)();
  return 1;
}

char FUN_000e9a90(void *widget)
{
  char profile[0x34];
  int16_t level;
  int16_t difficulty;
  char changed;
  int pass;

  if (*(int16_t *)((char *)widget + 0x3c) < 0 ||
      *(int16_t *)((char *)widget + 0x3c) >= 0xa)
    ui_widget_assert_fail((char *)0x285aa4, 0x2d4);

  if (*(int16_t *)0x31fa94 == 1) {
    ((void (*)(void *, int))player_ui_get_active_player_profile)(profile, 0);
    ((void (*)(void *, int16_t *, int16_t *))player_profile_save_last_level_played)(
        profile, &level, &difficulty);
    changed = 0;
    if (profile[*(int16_t *)((char *)widget + 0x3c) + 0x14] == 0 &&
        *(int16_t *)((char *)widget + 0x3c) != level + 1 &&
        *(int16_t *)((char *)widget + 0x3c) != 0)
      changed = 1;
    ((void (*)(bool))player_ui_remember_player1_profile)(0);
    pass = 0;
    while (pass <= 1) {
      ((void (*)(void *, int))player_ui_get_active_player_profile)(profile, pass);
      ((void (*)(void *, int16_t *, int16_t *))player_profile_save_last_level_played)(
          profile, &level, &difficulty);
      if (profile[*(int16_t *)((char *)widget + 0x3c) + 0x14] == 0 &&
          *(int16_t *)((char *)widget + 0x3c) != level + 1 &&
          *(int16_t *)((char *)widget + 0x3c) != 0)
        changed = 1;
      pass++;
    }
    if (changed) {
      main_set_map_name(*(char **)(0x31e498 +
                                   *(int16_t *)((char *)widget + 0x3c) * 4));
      main_defer_map_map_change();
    }
    return changed;
  }

  if (*(int16_t *)0x31fa94 == 2) {
    error(2, (char *)0x285a78);
    error(2, (char *)0x285a54);
    ui_play_audio_feedback_sound(4);
    return 0;
  }
  return 0;
}

char FUN_000e9dd0(void *widget)
{
  void *list_item;
  void *game;
  int16_t index;
  int16_t count;
  char join_token[0x2e];
  char ok;

  list_item = *(void **)((char *)widget + 0x38);
  if (list_item == NULL)
    return 0;
  index = *(int16_t *)((char *)widget + 0x3c);
  count = *(int16_t *)((char *)widget + 0x44);
  if (index < 0 || index >= count)
    return 0;
  if (*(int *)((char *)widget + 0x40) == 0)
    return 0;
  if (count == 0)
    return 0;

  game = *(void **)(*(int *)((char *)widget + 0x40) + index * 4);
  if (*(char *)((char *)game + 0xe0) != 1 || *(int16_t *)((char *)game + 0xde) != 0)
    return 0;

  ((void (*)(void *, char *, char *, char *, int))FUN_00082bd0)(
      game, join_token, (char *)game + 8, (char *)game + 0x18, 0x141e);
  if (*(int *)join_token == 0 || *(int16_t *)((char *)join_token + 0xa) == 0)
    return 0;

  network_game_generate_join_game_token(join_token);
  ok = network_game_client_initiate_join_game(
      network_game_client_get(), game, join_token, (void *)((char *)game + 8));
  if (ok == 0) {
    ui_widget_get_last_child(widget);
    widget_instance_get_child_index_from_parent(widget);
    ui_widget_load_by_name_or_tag(NULL, -1, -1, *(int16_t *)((char *)widget + 8), -1,
                                  -1, -1);
    error(2, (char *)0x285d48);
    set_game_connection(0);
    network_game_abort();
    error(2, (char *)0x285d48);
  }
  return ok;
}

char display_scenario_help(void *widget)
{
  void *tag;
  void *list;
  void *item;
  int16_t index;
  char path[0x40];
  void *file;
  char *map_name;
  int map_index;

  tag = tag_get(0x44654c61, *(int *)widget);
  if (*(int *)((char *)tag + 0x3e0) != 1)
    ui_widget_assert_fail((char *)0x285ec0, 0x500);

  list = *(void **)((char *)widget + 0x34);
  tag = tag_get(0x44654c61, *(int *)list);
  if (*(int16_t *)tag != 0 && *(int *)((char *)tag + 0x3e0) != 3)
    ui_widget_assert_fail((char *)0x285e70, 0x505);

  item = *(void **)((char *)list + 0x34);
  tag = tag_get(0x44654c61, *(int *)item);
  if (*(int16_t *)tag != 2)
    ui_widget_assert_fail((char *)0x285db8, 0x508);
  if (*(int *)((char *)tag + 0x3e0) != 3)
    ui_widget_assert_fail((char *)0x285d78, 0x509);

  list = *(void **)((char *)item + 0x34);
  index = *(int16_t *)((char *)list + 0x3c);
  if (index < 0 || index >= 0xd)
    ui_widget_assert_fail((char *)0x285e20, 0x512);

  map_name = *(char **)(0x31e4c8 + index * 4);
  file = crt_fopen((char *)0x285e04, (char *)0x2658a4);
  if (file != NULL) {
    crt_fgets(path, 0x40, file);
    csstrtok(path, (char *)0x285dfc);
    crt_fclose(file);
  } else {
    path[0] = 0;
  }

  main_set_multiplayer_map_name(map_name);
  FUN_000ab040(map_name);
  if (network_game_server_get() != NULL)
    ((void (*)(int, char *))network_game_server_change_map_name)(
        (int)(size_t)network_game_server_get(), map_name);

  for (map_index = 0; map_index < 0xd; map_index++) {
    if (crt_stricmp(*(char **)(0x31e4c8 + map_index * 4), map_name) == 0) {
      ((void (*)(char *))saved_game_file_remember_last_used_multiplayer_map)(
          *(char **)(0x31e4c8 + map_index * 4));
      break;
    }
  }
  return 1;
}

char network_game_server_list_initialize(void *widget)
{
  void *tag;
  void *buffer;
  int16_t count;
  int16_t index;
  char dir[0x100];
  int profile_index;

  csmemset((void *)0x5aa260, 0xff, 0x144);
  *(int *)0x31e494 = -1;

  tag = tag_get(0x44654c61, *(int *)widget);
  if (*(int16_t *)tag != 2)
    ui_widget_assert_fail((char *)0x285f48, 0x568);
  if (*(int *)((char *)tag + 0x3e0) != 3)
    ui_widget_assert_fail((char *)0x285f08, 0x569);

  buffer = ui_widget_realloc(*(int *)((char *)widget + 0x40), 0x190, (char *)0x2859a4,
                             0x56e);
  *(void **)((char *)widget + 0x40) = buffer;
  if (buffer == NULL)
    return 1;

  count = 0x64;
  ((void (*)(void *, int16_t *, int))FUN_001c26b0)(buffer, &count, 0);
  for (index = 0; index < 3 - count; index++)
    *(int *)((char *)buffer + (count + index) * 4) = -1;
  *(int16_t *)((char *)widget + 0x44) = count;

  if (((char (*)(char *))saved_game_file_retrieve_last_used_multiplayer_variant_directory)(
          dir)) {
    profile_index =
        ((int (*)(char *, int))saved_game_file_find_profile_index_for_directory_path)(
            dir, 1);
    if (profile_index != -1) {
      for (index = 0; index < count; index++) {
        if (*(int *)((char *)buffer + index * 4) == profile_index) {
          *(int16_t *)((char *)widget + 0x3c) = index;
          break;
        }
      }
    }
  }
  return 1;
}

char network_game_join_game_from_server_list(void *widget)
{
  void *tag;
  void *list;
  void *item;
  void *file;
  char line[0x320];
  char dir[0x100];
  char variant[0x100];
  int game_variant;

  tag = tag_get(0x44654c61, *(int *)widget);
  if (*(int *)((char *)tag + 0x3e0) != 1)
    ui_widget_assert_fail((char *)0x286108, 0x5b9);

  list = *(void **)((char *)widget + 0x34);
  tag = tag_get(0x44654c61, *(int *)list);
  if (*(int16_t *)tag != 0 && *(int *)((char *)tag + 0x3e0) != 3)
    ui_widget_assert_fail((char *)0x2860b8, 0x5be);

  item = *(void **)((char *)list + 0x34);
  tag = tag_get(0x44654c61, *(int *)item);
  if (*(int16_t *)tag != 2)
    ui_widget_assert_fail((char *)0x286070, 0x5c1);
  if (*(int *)((char *)tag + 0x3e0) != 3)
    ui_widget_assert_fail((char *)0x286030, 0x5c2);

  ui_play_audio_feedback_sound(4);
  display_error_deferred(0x1a, *(int16_t *)((char *)widget + 8), 0, 0);
  ui_play_audio_feedback_sound(4);
  playlist_profile_delete();

  if (network_game_server_get() != NULL)
    FUN_001c4da0();

  if (!((char (*)(char *))saved_game_file_retrieve_last_used_multiplayer_variant_directory)(
          dir))
    return 1;

  file = crt_fopen(dir, (char *)0x2658a4);
  if (file == NULL)
    return 1;
  crt_fgets(line, 0x320, file);
  csstrtok(line, (char *)0x285dfc);
  csmemset(variant, 0, 0x100);
  game_variant =
      (int)(size_t)game_engine_get_variant_by_name((void *)variant, line);
  if (csmemcmp(variant, line, 0x100) == 0) {
    crt_fclose(file);
    return 1;
  }
  crt_fclose(file);
  ((void (*)(char *))saved_game_file_remember_last_used_multiplayer_variant_directory)(
      dir);
  ((void (*)(int))player_ui_set_game_variant)(game_variant);
  if (network_game_server_get() != NULL)
    ((void (*)(void *, void *))network_game_server_change_game_variant)(
        network_game_server_get(), (void *)(size_t)game_variant);
  error(2, (char *)0x2860f0);
  return 1;
}

char FUN_000ea900(void *widget, void *event_data)
{
  void *client;
  void *session;
  int16_t machine;
  int index;
  int16_t player_index;

  if (event_data == NULL)
    ui_widget_assert_fail((char *)0x286184, 0x652);

  client = network_game_client_get();
  if (client == NULL)
    return 1;
  if (network_game_client_get_state(client, (void *)&event_data) != 2)
    return 1;

  session = (void *)FUN_0012a0a0();
  machine = network_game_client_get_local_machine_index();
  if (session == NULL)
    ui_widget_assert_fail((char *)0x2861a8, 0x65b);

  if (machine != -1) {
    for (index = 0; index < 0x10; index++) {
      if (network_player_is_valid((char *)session + index * 0x20 + 0x226)) {
        if (*(char *)((char *)session + index * 0x20 + 0x242) == (char)machine &&
            *(int16_t *)((char *)session + index * 0x20 + 0x243) ==
                *(int16_t *)((char *)event_data + 2))
          return 1;
      }
    }
  }

  player_index = *(int16_t *)((char *)event_data + 2);
  if (!network_game_client_add_player(client, player_index))
    network_game_log((char *)0x28618c);
  return 1;
}

char FUN_000eaa10(void *widget)
{
  void *tag;
  void *buffer;
  char solo;

  csmemset((void *)0x5aa3c0, 0xff, 0x9c);
  *(int *)0x31e494 = -1;

  tag = tag_get(0x44654c61, *(int *)widget);
  if (*(int16_t *)tag != 2)
    ui_widget_assert_fail((char *)0x2861f8, 0x696);
  if (*(int *)((char *)tag + 0x3e0) != 0 && *(int *)((char *)tag + 0x3e0) != 3)
    ui_widget_assert_fail((char *)0x2861b0, 0x698);

  buffer = ui_widget_realloc(*(int *)((char *)widget + 0x40), 0x190, (char *)0x2859a4,
                             0x69d);
  *(void **)((char *)widget + 0x40) = buffer;
  if (buffer == NULL)
    return 1;

  solo = (char)(*(int *)((char *)tag + 0x3e0) != 3);
  ((void (*)(void *, char *, int16_t))FUN_001c0d50)(
      buffer, &solo, *(int16_t *)((char *)widget + 8));
  player_ui_get_player1_last_used_profile_index();
  return 1;
}

char FUN_000eaba0(void *widget, void *event_data)
{
  void *tag;
  void *list;
  int16_t profile_index;
  char profile_buf[0x30];

  if (event_data == NULL || *(int16_t *)((char *)event_data + 2) == -1)
    ui_widget_assert_fail((char *)0x2863b4, 0x6e3);

  tag = tag_get(0x44654c61, *(int *)widget);
  if (*(int16_t *)tag != 0 && *(int *)((char *)tag + 0x3e0) < 3)
    ui_widget_assert_fail((char *)0x286360, 0x6ec);

  list = *(void **)((char *)widget + 0x34);
  tag = tag_get(0x44654c61, *(int *)list);
  if (*(int16_t *)tag != 2)
    ui_widget_assert_fail((char *)0x286320, 0x6ef);
  if (*(int *)((char *)tag + 0x3e0) != 3)
    ui_widget_assert_fail((char *)0x2862e8, 0x6f0);

  list = ui_widget_find_child_type(list, 2);
  if (*(int16_t *)((char *)list + 0x3c) < 0 ||
      *(int16_t *)((char *)list + 0x3c) >= *(int16_t *)((char *)widget + 0x44))
    ui_widget_assert_fail((char *)0x2862b0, 0x6f4);

  profile_index = *(int16_t *)((char *)event_data + 2);
  display_error_deferred(0x19, *(int16_t *)((char *)widget + 8), 0, 0);
  ui_play_audio_feedback_sound(4);
  ((void (*)(void *, int16_t))player_profile_new)(profile_buf, profile_index);
  ((void (*)(int, int))player_ui_set_active_player_profile)(
      ((int (*)(short))player_ui_get_single_player_local_player_from_controller)(0),
      profile_index);
  error(2, (char *)0x286280);
  return 1;
}

char multiplayer_level_select(void *widget, void *event_data)
{
  void *tag;
  void *list;
  void *item;
  int16_t profile_index;
  char profile_buf[0x30];

  if (event_data == NULL || *(int16_t *)((char *)event_data + 2) == -1)
    ui_widget_assert_fail((char *)0x2863b4, 0x72a);

  list = ui_widget_find_child_type(*(void **)((char *)widget + 0x34), 2);
  if (list == NULL)
    ui_widget_assert_fail((char *)0x286498, 0x72e);

  tag = tag_get(0x44654c61, *(int *)list);
  if (*(int *)((char *)tag + 0x3e0) != 0)
    ui_widget_assert_fail((char *)0x286440, 0x735);

  if (*(int16_t *)((char *)list + 0x3c) < 0 ||
      *(int16_t *)((char *)list + 0x3c) >= *(int16_t *)((char *)list + 0x44))
    ui_widget_assert_fail((char *)0x286410, 0x738);

  profile_index = *(int16_t *)((char *)event_data + 2);
  display_error_deferred(0x19, *(int16_t *)((char *)widget + 8), 0, 0);
  ui_play_audio_feedback_sound(4);
  ((void (*)(void *, int16_t))player_profile_new)(profile_buf, profile_index);
  ((void (*)(int, int))player_ui_set_active_player_profile)(
      ((int (*)(short))player_ui_get_single_player_local_player_from_controller)(0),
      profile_index);
  item = *(void **)((char *)list + 0x38);
  *(int *)((char *)widget + 0x40) = *(int *)((char *)list + 0x40);
  *(int16_t *)((char *)widget + 0x3c) = *(int16_t *)((char *)item + 0x3c);
  error(2, (char *)0x2863d0);
  return 1;
}

char FUN_000eaec0(void *widget)
{
  void *tag;

  *(int *)0x31e494 = -1;
  tag = tag_get(0x44654c61, *(int *)widget);
  if (*(int16_t *)tag != 0 && *(int *)((char *)tag + 0x3e0) < 3)
    ui_widget_assert_fail((char *)0x286510, 0x748);
  return 1;
}

char FUN_000eb020(void *widget)
{
  void *profile;
  void *parent;
  void *list;
  int game_type;

  profile = ui_widget_get_playlist_profile();
  parent = *(void **)((char *)widget + 0x30);
  if (parent == NULL || *(int16_t *)((char *)parent + 0xe) != 3)
    ui_widget_assert_fail((char *)0x2865a0, 0x7a6);
  if (profile == NULL) {
    error(2, (char *)0x286550);
    return 0;
  }

  list = *(void **)((char *)widget + 0x34);
  switch (*(int16_t *)((char *)list + 0x3c)) {
  case 0:
    game_type = 1;
    break;
  case 1:
    game_type = 4;
    break;
  case 2:
    game_type = 2;
    break;
  case 3:
    game_type = 3;
    break;
  case 4:
    game_type = 5;
    break;
  default:
    error(2, (char *)0x28657c);
    game_type = *(int *)((char *)profile + 0x18);
    break;
  }

  if (game_type != *(int *)((char *)profile + 0x18)) {
    csmemset((char *)profile + 0x4c, 0, 0x18);
    *(int *)((char *)profile + 0x18) = game_type;
  }
  return 1;
}

char FUN_000eb150(void *widget)
{
  void *profile;
  void *list;
  void *item;
  void *sibling;
  int16_t team_index;

  profile = ui_widget_get_playlist_profile();
  list = *(void **)((char *)widget + 0x34);
  if (list == NULL)
    ui_widget_assert_fail((char *)0x2868d0, 0x7f8);
  item = ui_widget_find_child_type(list, 2);
  if (item == NULL)
    ui_widget_assert_fail((char *)0x2868a8, 0x7fa);
  if (profile == NULL) {
    error(2, (char *)0x286550);
    return 0;
  }

  switch (*(int16_t *)((char *)item + 0x3c)) {
  case 0:
    *(char *)((char *)profile + 0x4c) = 1;
    break;
  case 1:
    *(char *)((char *)profile + 0x4c) = 0;
    break;
  default:
    error(2, (char *)0x28686c);
    break;
  }

  sibling = *(void **)((char *)list + 0x2c);
  if (sibling == NULL)
    ui_widget_assert_fail((char *)0x286848, 0x803);
  item = ui_widget_find_child_type(sibling, 2);
  if (item == NULL)
    ui_widget_assert_fail((char *)0x286820, 0x805);

  switch (*(int16_t *)((char *)item + 0x3c)) {
  case 0:
    team_index = 0;
    break;
  case 1:
    team_index = 1;
    break;
  default:
    error(2, (char *)0x2867ec);
    team_index = 0;
    break;
  }
  *(int16_t *)((char *)item + 0x3c) = team_index;

  sibling = *(void **)((char *)sibling + 0x2c);
  if (sibling == NULL)
    ui_widget_assert_fail((char *)0x2867c8, 0x80b);
  item = ui_widget_find_child_type(sibling, 2);
  if (item == NULL)
    ui_widget_assert_fail((char *)0x2867a0, 0x80d);
  switch (*(int16_t *)((char *)item + 0x3c)) {
  case 0:
    *(int16_t *)((char *)item + 0x3c) = 0;
    break;
  case 1:
    *(int16_t *)((char *)item + 0x3c) = 1;
    break;
  default:
    error(2, (char *)0x286774);
    break;
  }

  sibling = *(void **)((char *)sibling + 0x2c);
  if (sibling == NULL)
    ui_widget_assert_fail((char *)0x286750, 0x813);
  item = ui_widget_find_child_type(sibling, 2);
  if (item == NULL)
    ui_widget_assert_fail((char *)0x286728, 0x815);
  if (*(int16_t *)((char *)item + 0x3c) != 0)
    error(2, (char *)0x286700);

  ui_widgets_pop_stack(*(int16_t *)((char *)widget + 8));
  error(2, (char *)0x2866d8);
  return 1;
}

char FUN_000eb4f0(void *widget)
{
  void *profile;
  void *list;
  void *item;

  profile = ui_widget_get_playlist_profile();
  if (profile == NULL) {
    error(2, (char *)0x286550);
    return 0;
  }
  list = *(void **)((char *)widget + 0x34);
  if (list == NULL)
    ui_widget_assert_fail((char *)0x286a64, 0x84e);
  item = ui_widget_find_child_type(list, 2);
  if (item == NULL)
    ui_widget_assert_fail((char *)0x286a38, 0x850);

  switch (*(int16_t *)((char *)item + 0x3c)) {
  case 0:
    *(char *)((char *)profile + 0x4c) = 1;
    break;
  case 1:
    *(char *)((char *)profile + 0x4c) = 0;
    break;
  default:
    error(2, (char *)0x2869f8);
    break;
  }

  list = *(void **)((char *)list + 0x2c);
  if (list == NULL)
    ui_widget_assert_fail((char *)0x2869d4, 0x859);
  item = ui_widget_find_child_type(list, 2);
  if (item == NULL)
    ui_widget_assert_fail((char *)0x2869ac, 0x85b);
  switch (*(int16_t *)((char *)item + 0x3c)) {
  case 0:
    *(int *)((char *)profile + 0x50) = 0;
    break;
  case 1:
    *(int *)((char *)profile + 0x50) = 1;
    break;
  default:
    error(2, (char *)0x286978);
    break;
  }

  ui_widgets_pop_stack(*(int16_t *)((char *)widget + 8));
  error(2, (char *)0x286958);
  return 1;
}

char FUN_000eb710(void *widget)
{
  void *profile;
  void *list;
  void *item;

  profile = ui_widget_get_playlist_profile();
  if (profile == NULL) {
    error(2, (char *)0x286550);
    return 0;
  }
  list = *(void **)((char *)widget + 0x34);
  if (list == NULL)
    ui_widget_assert_fail((char *)0x286c9c, 0x88b);
  item = ui_widget_find_child_type(list, 2);
  if (item == NULL)
    ui_widget_assert_fail((char *)0x286c70, 0x88d);

  switch (*(int16_t *)((char *)item + 0x3c)) {
  case 0:
    *(char *)((char *)profile + 0x4c) = 0;
    break;
  case 1:
    *(char *)((char *)profile + 0x4c) = 1;
    break;
  default:
    error(2, (char *)0x286c30);
    break;
  }

  list = *(void **)((char *)list + 0x2c);
  if (list == NULL)
    ui_widget_assert_fail((char *)0x286c08, 0x896);
  item = ui_widget_find_child_type(list, 2);
  if (item == NULL)
    ui_widget_assert_fail((char *)0x286be0, 0x898);
  switch (*(int16_t *)((char *)item + 0x3c)) {
  case 0:
    *(int *)((char *)profile + 0x54) = 0;
    break;
  case 1:
    *(int *)((char *)profile + 0x54) = 1;
    break;
  case 2:
    *(int *)((char *)profile + 0x54) = 2;
    break;
  case 3:
    *(int *)((char *)profile + 0x54) = 3;
    break;
  default:
    error(2, (char *)0x286ba0);
    break;
  }

  ui_widgets_pop_stack(*(int16_t *)((char *)widget + 8));
  error(2, (char *)0x286b78);
  return 1;
}

char FUN_000eba70(void *widget)
{
  void *profile;
  void *list;
  void *item;

  profile = ui_widget_get_playlist_profile();
  if (profile == NULL) {
    error(2, (char *)0x286550);
    return 0;
  }
  list = *(void **)((char *)widget + 0x34);
  if (list == NULL)
    ui_widget_assert_fail((char *)0x287034, 0x8de);
  item = ui_widget_find_child_type(list, 2);
  if (item == NULL)
    ui_widget_assert_fail((char *)0x287004, 0x8e0);

  switch (*(int16_t *)((char *)item + 0x3c)) {
  case 0:
    *(int *)((char *)profile + 0x54) = 0;
    break;
  case 1:
    *(int *)((char *)profile + 0x54) = 1;
    break;
  case 2:
    *(int *)((char *)profile + 0x54) = 2;
    break;
  case 3:
    *(int *)((char *)profile + 0x54) = 3;
    break;
  default:
    error(2, (char *)0x286fc0);
    break;
  }

  list = *(void **)((char *)list + 0x2c);
  if (list == NULL)
    ui_widget_assert_fail((char *)0x286f98, 0x8eb);
  item = ui_widget_find_child_type(list, 2);
  if (item == NULL)
    ui_widget_assert_fail((char *)0x286f70, 0x8ed);
  switch (*(int16_t *)((char *)item + 0x3c)) {
  case 0:
    *(int *)((char *)profile + 0x58) = 0;
    break;
  case 1:
    *(int *)((char *)profile + 0x58) = 1;
    break;
  case 2:
    *(int *)((char *)profile + 0x58) = 2;
    break;
  case 3:
    *(int *)((char *)profile + 0x58) = 3;
    break;
  default:
    error(2, (char *)0x286f40);
    break;
  }

  ui_widgets_pop_stack(*(int16_t *)((char *)widget + 8));
  error(2, (char *)0x286f18);
  return 1;
}

char FUN_000ebff0(void *widget)
{
  void *profile;
  void *list;
  void *item;

  profile = ui_widget_get_playlist_profile();
  if (profile == NULL) {
    error(2, (char *)0x286550);
    return 0;
  }
  list = *(void **)((char *)widget + 0x34);
  if (list == NULL)
    ui_widget_assert_fail((char *)0x2871d8, 0x968);
  item = ui_widget_find_child_type(list, 2);
  if (item == NULL)
    ui_widget_assert_fail((char *)0x2871ac, 0x96a);

  switch (*(int16_t *)((char *)item + 0x3c)) {
  case 0:
    *(int *)((char *)profile + 0x50) = 0;
    break;
  case 1:
    *(int *)((char *)profile + 0x50) = 1;
    break;
  case 2:
    *(int *)((char *)profile + 0x50) = 2;
    break;
  default:
    error(2, (char *)0x28716c);
    break;
  }

  list = *(void **)((char *)list + 0x2c);
  if (list == NULL)
    ui_widget_assert_fail((char *)0x287144, 0x974);
  item = ui_widget_find_child_type(list, 2);
  if (item == NULL)
    ui_widget_assert_fail((char *)0x28711c, 0x976);
  switch (*(int16_t *)((char *)item + 0x3c)) {
  case 0:
    *(char *)((char *)profile + 0x4c) = 1;
    break;
  case 1:
    *(char *)((char *)profile + 0x4c) = 0;
    break;
  default:
    error(2, (char *)0x2870e4);
    break;
  }

  ui_widgets_pop_stack(*(int16_t *)((char *)widget + 8));
  error(2, (char *)0x2870bc);
  return 1;
}

char FUN_000ec2c0(void *widget)
{
  void *profile;
  void *list;
  void *item;

  profile = ui_widget_get_playlist_profile();
  if (profile == NULL) {
    error(2, (char *)0x286550);
    return 0;
  }
  list = *(void **)((char *)widget + 0x34);
  if (list == NULL)
    ui_widget_assert_fail((char *)0x287654, 0x9b3);
  item = ui_widget_find_child_type(list, 2);
  if (item == NULL)
    ui_widget_assert_fail((char *)0x287624, 0x9b5);

  switch (*(int16_t *)((char *)item + 0x3c)) {
  case 0:
    *(int *)((char *)profile + 0x38) = 0;
    break;
  case 1:
    *(int *)((char *)profile + 0x38) = 1;
    break;
  case 2:
    *(int *)((char *)profile + 0x38) = 3;
    break;
  case 3:
    *(int *)((char *)profile + 0x38) = 5;
    break;
  default:
    error(2, (char *)0x2875e0);
    break;
  }

  list = *(void **)((char *)list + 0x2c);
  if (list == NULL)
    ui_widget_assert_fail((char *)0x2875b8, 0x9bf);
  item = ui_widget_find_child_type(list, 2);
  if (item == NULL)
    ui_widget_assert_fail((char *)0x287590, 0x9c1);
  switch (*(int16_t *)((char *)item + 0x3c)) {
  case 0:
    *(int *)((char *)profile + 0x3c) = 0;
    break;
  case 1:
    *(int *)((char *)profile + 0x3c) = 1;
    break;
  default:
    error(2, (char *)0x287560);
    break;
  }

  ui_widgets_pop_stack(*(int16_t *)((char *)widget + 8));
  error(2, (char *)0x287538);
  return 1;
}

char FUN_000ec840(void *widget)
{
  void *profile;
  void *list;
  void *item;
  void *buffer;

  profile = ui_widget_get_playlist_profile();
  if (profile == NULL) {
    error(2, (char *)0x286550);
    return 0;
  }
  list = *(void **)((char *)widget + 0x34);
  if (list == NULL)
    ui_widget_assert_fail((char *)0x2878d8, 0xa0a);
  item = ui_widget_find_child_type(list, 2);
  if (item == NULL)
    ui_widget_assert_fail((char *)0x2878b0, 0xa0c);

  buffer = ui_widget_realloc(*(int *)((char *)item + 0x3c), 0x100, (char *)0x2859a4,
                             0xa10);
  *(void **)((char *)item + 0x3c) = buffer;
  if (buffer != NULL) {
    ustrncpy((wchar_t *)buffer, (wchar_t *)profile, 0x7f);
    *(int16_t *)((char *)buffer + 0xfe) = 0;
  }

  ui_widgets_pop_stack(*(int16_t *)((char *)widget + 8));
  error(2, (char *)0x287888);
  return 1;
}

char FUN_000ecb60(void *widget)
{
  void *profile;
  void *list;
  void *item;

  profile = ui_widget_get_playlist_profile();
  if (profile == NULL) {
    error(2, (char *)0x286550);
    return 0;
  }
  list = *(void **)((char *)widget + 0x34);
  if (list == NULL)
    ui_widget_assert_fail((char *)0x287ab0, 0xab2);
  item = ui_widget_find_child_type(list, 3);
  if (item == NULL)
    ui_widget_assert_fail((char *)0x287a80, 0xab4);

  switch (*(int *)((char *)profile + 0x18) - 1) {
  case 0:
    *(int16_t *)((char *)item + 0x3c) = 1;
    break;
  case 1:
    *(int16_t *)((char *)item + 0x3c) = 2;
    break;
  case 2:
    *(int16_t *)((char *)item + 0x3c) = 3;
    break;
  case 3:
    *(int16_t *)((char *)item + 0x3c) = 4;
    break;
  default:
    *(int16_t *)((char *)item + 0x3c) = 0;
    break;
  }
  *(void **)((char *)item + 0x38) =
      widget_instance_get_nth_child(item, *(int16_t *)((char *)item + 0x3c));
  return 1;
}
