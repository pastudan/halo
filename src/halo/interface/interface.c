#include <stdint.h>
/* UI/HUD interface subsystem init/dispose. */

void interface_initialize(void)
{
  ((void (*)(void))0xe33a0)();
  hud_new();
  ((void (*)(void))0x19b320)();
  ((void (*)(void))0xdc750)();
}

void interface_dispose_from_old_map(void)
{
  ((void (*)(void))0x19b3a0)();
  hud_dispose_from_old_map();
}

void interface_dispose(void)
{
  ((void (*)(void))0x19b3b0)();
  ((void (*)(void))0xe33e0)();
  hud_dispose();
}

#define NUMBER_OF_INTERFACE_TAGS 16

/* Look up a tag_index from the interface globals tag block.
 * The interface globals element (size 0x130) contains an array of 16
 * tag_reference entries (each 0x10 bytes) starting at offset 0x0.
 * The tag_index field is at offset 0xc within each tag_reference.
 * Returns the tag_index for the given interface_tag_index slot. */
int interface_get_tag_index(int interface_tag_index)
{
  char *globals;
  char *element;

  assert_halt(interface_tag_index >= 0 &&
              interface_tag_index < NUMBER_OF_INTERFACE_TAGS);

  globals = (char *)game_globals_get();
  if (*(int *)(globals + 0x140) != 0) {
    globals = (char *)game_globals_get();
    element = (char *)tag_block_get_element(globals + 0x140, 0, 0x130);
    return *(int *)(element + interface_tag_index * 0x10 + 0xc);
  }

  return *(int *)((char *)0 + interface_tag_index * 0x10 + 0xc);
}

/* Look up an ARGB float color from a color_table ('colo') tag.
 * Uses interface_get_tag_index to resolve the color tag, then
 * indexes into the color table block (element size 0x30).
 * Color data is 4 floats (ARGB) at offset 0x20 within each entry.
 * The color_index is taken modulo the block count (as a short).
 * Returns out_color. */
void *interface_get_color(int interface_tag_index, short color_index,
                          void *out_color)
{
  int tag_idx;
  int *color_tag;
  int count;
  char *entry;
  float *out = (float *)out_color;

  tag_idx = interface_get_tag_index(interface_tag_index);

  out[3] = 1.0f;
  out[2] = 1.0f;
  out[1] = 1.0f;
  out[0] = 1.0f;

  if (tag_idx != -1) {
    color_tag = (int *)tag_get(0x636f6c6f, tag_idx);
    count = *color_tag;
    if (count != 0) {
      entry = (char *)tag_block_get_element(color_tag,
                                            (short)(color_index % count), 0x30);
      out[0] = *(float *)(entry + 0x20);
      out[1] = *(float *)(entry + 0x24);
      out[2] = *(float *)(entry + 0x28);
      out[3] = *(float *)(entry + 0x2c);
    }
  }

  return out_color;
}

/* Set up font, color, and style for drawing interface text.
 * Resolves font_index to a tag_index, looks up an ARGB color from the
 * interface color table (indexed by color_tag_index / color_index), then
 * configures the draw_string subsystem with those parameters. */
void interface_draw_text(int font_index, int style, int justify, int flags,
                         int color_tag_index, short color_index)
{
  float color[4];
  int tag_index;

  tag_index = interface_get_tag_index(font_index);
  interface_get_color(color_tag_index, color_index, color);
  draw_string_set_font(tag_index, style, justify, flags, color);
}

/* interface_draw_splitscreen_dividers (0xdfdc0) — readable C lift. */
void interface_draw_splitscreen_dividers(void)
{
  int16_t rect[4];
  int16_t nplayers;

  if (game_engine_force_single_screen())
    return;
  if (cinematic_in_progress())
    return;

  nplayers = local_player_count();
  if (nplayers <= 1)
    return;

  /* Vertical center divider (2+ players). */
  rect[0] = 0xef;
  rect[1] = 0;
  rect[2] = 0xf1;
  rect[3] = 0x280;
  draw_quad(rect, (int)0xff000000);

  if (nplayers <= 2)
    return;

  /* Horizontal divider for 3–4 players. */
  rect[2] = 0x1e0;
  rect[3] = 0x141;
  rect[1] = 0x13f;
  if (nplayers == 3) {
    rect[0] = 0xf0;
    draw_quad(rect, (int)0xff000000);
    return;
  }

  rect[0] = 0;
  if (nplayers != 4) {
    display_assert((const char *)0x2825d0, (const char *)0x2824e0, 0x374, 1);
    system_exit(-1);
  }
  draw_quad(rect, (int)0xff000000);
}


/* Initialize interface for a new map: set up HUD elements and load the
 * first interface globals tag block entry for widget rendering. */
void interface_initialize_for_new_map(void)
{
  char *globals;
  char *element;

  ((void (*)(void))0xd0360)();
  ((void (*)(void))0x19b330)();
  ((void (*)(void))0xdc7a0)();

  globals = (char *)game_globals_get();
  if (*(int *)(globals + 0x140) == 0) {
    element = 0;
  } else {
    globals = (char *)game_globals_get();
    element = (char *)tag_block_get_element(globals + 0x140, 0, 0x130);
  }

  ((void (*)(int, int, int, int, void *))0x19b8b0)(*(int *)(element + 0x1c), -1,
                                                   0, 0, *(void **)0x2ee6c4);
}
/* --- interface.obj batch drafts (2026-07-26) --- */

/* FUN_000dedf0 (0xdedf0) — readable C lift (restored pre-naked). */
void FUN_000dedf0(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;

  local_player_get_player_index(eax);
  datum_get((void *)(uintptr_t)ecx, 0);
  director_get_perspective(edx);
  /* test ecx, ecx -> je 0xdef9b */
  /* relift: cmp byte ptr [ecx], 0 -> je 0xdef9b */
  /* cmp (int16_t)eax, 3 -> je 0xdef9b */
  /* cmp (int16_t)eax, 2 -> je 0xdef9b */
  /* cmp eax, ebx -> je 0xdef9b */
  object_get_and_verify_type(0, 0);
  unit_get_weapon(0, eax);
  object_get_and_verify_type(0, 0);
  /* cmp eax, ebx -> je 0xdef9b */
  /* relift: cmp word ptr [esi + 0x2a0], (int16_t)ebx -> je 0xdef9b */
  object_get_and_verify_type(0, 0);
  tag_get(0x756e6974, 0);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  /* test (char)ecx, 8 -> je 0xdef9b */
  object_get_and_verify_type(0, 0);
  unit_get_weapon(0, ecx);
  object_get_and_verify_type(0, 0);
  /* cmp esi, -1 -> je 0xdef9b */
  object_get_and_verify_type(0, 0);
  tag_get('paew', 0);
  /* cmp eax, -1 -> je 0xdef7e */
  unit_count_weapons(0);
  /* test (int16_t)eax, (int16_t)eax -> jne 0xdef9b */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
}


/* interface_draw_screen (0xdefb0) — readable C lift (restored pre-naked). */
void interface_draw_screen(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;

  /* relift: cmp word ptr [0x506548], -1 -> je 0xdf341 */
  FUN_000dedf0();
  /* cmp eax, -1 -> je 0xdf32d */
  tag_get('ihpw', 0);
  /* test ecx, ecx -> jle 0xdf32d */
  tag_block_get_element((void *)(uintptr_t)eax, 0, 184);
  player_control_get_zoom_level(ecx);
  csmemset((void *)0, 0, 0);
  /* test (char)ebx, (char)ebx -> jne 0xdf03b */
  /* relift: test byte ptr [esi + 4], 1 -> jne 0xdf08e */
  main_get_window_count();
  /* cmp (int16_t)eax, 1 -> jg 0xdf04b */
  /* cmp eax, -1 -> je 0xdf08e */
  tag_get(0x6269746d, 0);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  main_get_window_count();
  /* cmp (int16_t)eax, 1 -> jg 0xdf13d */
  /* test (char)ebx, (char)ebx -> jne 0xdf0ab */
  /* relift: test byte ptr [esi + 0x40], 1 -> jne 0xdf141 */
  /* test (char)eax, 0x41 -> jne 0xdf100 */
  scalars_interpolate(0.0f, 0.0f, 0.0f, (float *)(uintptr_t)edx);
  /* test (char)eax, 0x41 -> jne 0xdf13b */
  /* test (char)ebx, (char)ebx -> jne 0xdf14b */
  /* relift: test byte ptr [esi + 0x6c], 1 -> jne 0xdf202 */
  /* relift: test byte ptr [esi + 0x6c], 2 -> je 0xdf190 */
  /* test (char)eax, 0x41 -> jne 0xdf187 */
  ((void(*)(void))FUN_0017d9d0)();
  ((void(*)(void))FUN_0017d9d0)();
  /* test (char)eax, 0x41 -> jne 0xdf1d8 */
  ((void(*)(void))FUN_0017d9d0)();
  /* test (char)eax, 0x41 -> jne 0xdf1fc */
  /* test (char)ebx, (char)ebx -> jne 0xdf20f */
  /* relift: test byte ptr [esi + 0x8c], 1 -> jne 0xdf311 */
  /* test (char)eax, 0x41 -> jne 0xdf251 */
  ((void(*)(void))FUN_0017d9d0)();
  ((void(*)(void))FUN_0017d9d0)();
  /* test (char)eax, 0x41 -> jne 0xdf2a8 */
  ((void(*)(void))FUN_0017d9d0)();
  /* test (char)eax, 0x41 -> jne 0xdf30f */
  FUN_0017cb90((void *)(uintptr_t)eax);
  FUN_000d1400();
  FUN_000afdf0();
  FUN_0017cb90((void *)(uintptr_t)eax);
  FUN_000d1400();
  FUN_000afdf0();
  FUN_0017cb90((void *)0);
  FUN_000d1400();
  FUN_000afdf0();

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
}



/* profile_graph_toggle (0xdf350) — readable C lift. */
void profile_graph_toggle(const char *name)
{
  int16_t count = *(int16_t *)0x306d20;
  for (int16_t i = 0; i < count; i++) {
    char *entry = (char *)0x306d28 + (int)i * 0x20c;
    if (crt_stricmp(name, entry) == 0 || crt_stricmp(name, entry + 0x100) == 0) {
      entry[0x209] = !entry[0x209];
    }
  }
}

/* FUN_000df3d0 (0xdf3d0) — readable C lift (restored pre-naked). */
void FUN_000df3d0(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;

  matrix_transform_point((void *)0x005065e8, (float *)(uintptr_t)ecx, (float *)0);
  matrix_transform_point((void *)0x005065e8, (float *)(uintptr_t)eax, (float *)(uintptr_t)edx);
  rasterizer_hud_motion_sensor_blip_begin();

  (void)eax;
  (void)ecx;
  (void)edx;
}


/* FUN_000df4e0 (0xdf4e0) — readable C lift (restored pre-naked). */
void FUN_000df4e0(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  FUN_001d90e0();
  game_globals_get();
  /* test ecx, ecx -> je 0xdf526 */
  game_globals_get();
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  interface_get_color(0, 0, (void *)(uintptr_t)eax);
  draw_string_set_font(0, 0, 0, 0, (void *)(uintptr_t)ecx);
  FUN_0013db60((void *)(uintptr_t)edx);
  FUN_0008e480((void *)(uintptr_t)eax);
  FUN_0009c910((void *)(uintptr_t)ecx);
  csstrcpy((char *)(uintptr_t)edx, (char *)0x0025386f);
  csstrlen((char *)(uintptr_t)eax);
  crt_sprintf((char *)(uintptr_t)ecx, (char *)0);
  csstrlen((char *)(uintptr_t)ecx);
  crt_sprintf((char *)(uintptr_t)edx, (char *)0);
  csstrlen((char *)(uintptr_t)eax);
  crt_sprintf((char *)(uintptr_t)ecx, (char *)0);
  csstrlen((char *)(uintptr_t)ecx);
  crt_sprintf((char *)(uintptr_t)edx, (char *)0);
  ((void(*)(void))FUN_00053790)();
  FUN_0014da20((char *)(uintptr_t)ecx);
  rasterizer_text_draw((void *)0, (void *)0, (void *)0, 0, (char *)(uintptr_t)edx);
  crt_sprintf((char *)(uintptr_t)eax, (char *)0x00282528);
  csstrlen((char *)(uintptr_t)ecx);
  profile_dump();
  draw_string_set_tab_stops((void *)(uintptr_t)eax, 0);
  rasterizer_text_draw((void *)0, (void *)0, (void *)0, 0, (char *)(uintptr_t)ecx);
  draw_string_set_tab_stops((void *)(uintptr_t)edx, 0);
  /* test (char)eax, (char)eax -> je 0xdfdb5 */
  render_frustum_get_projection_bounds((void *)0x005065a4, (void *)(uintptr_t)eax);
  /* relift: cmp word ptr [0x306d20], (int16_t)edi -> jle 0xdf800 */
  profile_find_frame_value();
  /* test (char)eax, (char)eax -> je 0xdfdb4 */
  rasterizer_hud_motion_sensor_blip_begin();
  csmemset((void *)(uintptr_t)ecx, 0, 128);
  FUN_0017ca40();
  ((void(*)(void))profile_frame_iterator_new)();
  ((void(*)(void))profile_frame_iterator_next)();
  /* test (char)eax, (char)eax -> je 0xdfbde */
  /* cmp (int16_t)eax, 0xffff -> je 0xdfb65 */
  profile_frame_get_value();
  /* test (char)eax, 0x41 -> jne 0xdf98a */
  /* test (char)eax, (char)eax -> je 0xdf9ee */
  /* relift: cmp word ptr [ebp - 0xc], 0 -> jle 0xdf9ee */
  /* test (char)eax, (char)eax -> je 0xdf9ee */
  /* relift: cmp word ptr [edi + 0x306d20], -1 -> je 0xdf9ee */
  /* test (char)eax, (char)eax -> jne 0xdf9ee */
  FUN_001d9068();
  FUN_001d9068();
  matrix_transform_point((float *)0, (float *)0, (float *)0);
  /* test (char)eax, (char)eax -> je 0xdfaf8 */
  /* test (char)eax, (char)eax -> jne 0xdfaf8 */
  /* test (char)ebx, (char)ebx -> jne 0xdfaf8 */
  /* relift: cmp word ptr [ebp + esi*2 - 0x108], 0 -> jne 0xdfaa3 */
  /* relift: cmp word ptr [ebp + esi*2 - 0x108], 0x200 -> jl 0xdfacf */
  display_assert((char *)0x00282508, (char *)0x002824e0, 704, 0);
  system_exit(0);
  /* test (int16_t)eax, (int16_t)eax -> jle 0xdfb33 */
  FUN_0017ca60((void *)(uintptr_t)ecx, 0, (float *)0);
  csmemcpy((void *)(uintptr_t)ecx, (void *)(uintptr_t)eax, 256);
  csmemcpy((void *)(uintptr_t)eax, (void *)(uintptr_t)edx, 256);
  csmemcpy((void *)(uintptr_t)edx, (void *)(uintptr_t)ecx, 768);
  ((void(*)(void))profile_frame_iterator_next)();
  /* test (char)eax, (char)eax -> jne 0xdf8b0 */
  /* relift: cmp word ptr [0x306d20], (int16_t)edi -> jle 0xdfc3e */
  FUN_0017ca60((void *)(uintptr_t)eax, ecx, (float *)0);
  /* relift: cmp (int16_t)edi, word ptr [0x306d20] -> jl 0xdfbf0 */
  FUN_0017ca70();
  rasterizer_widget_get_occlusion_test_result();
  ((void(*)(void))profile_frame_iterator_new)();
  ((void(*)(void))profile_frame_iterator_next)();
  /* test (char)eax, (char)eax -> je 0xdfdae */
  ((void(*)(void))profile_frame_get_messages)();
  ((void(*)(void))profile_frame_get_stalls)();
  /* cmp edi, esi -> je 0xdfd96 */
  /* test edi, eax -> je 0xdfd62 */
  FUN_000df3d0();
  /* test edi, eax -> je 0xdfd8a */
  FUN_000df3d0();
  /* cmp (int16_t)esi, 0x1b -> jl 0xdfd64 */
  ((void(*)(void))profile_frame_iterator_next)();
  /* test (char)eax, (char)eax -> jne 0xdfc70 */
  rasterizer_hud_motion_sensor_blip_end();

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}



/* interface_get_rgb_color (0xdff00) — readable C lift. */
int16_t *interface_get_rgb_color(int interface_tag_index, int16_t color_index, int16_t *out_rgb)
{
  float tmp[4];
  float scale;
  interface_get_color(interface_tag_index, color_index, tmp);
  scale = *(float *)0x2647cc;
  out_rgb[0] = (int16_t)(int)(tmp[0] * scale);
  out_rgb[1] = (int16_t)(int)(tmp[1] * scale);
  out_rgb[2] = (int16_t)(int)(tmp[2] * scale);
  out_rgb[3] = (int16_t)(int)(tmp[3] * scale);
  return out_rgb;
}

/* interface_draw_fullscreen_overlays (0xdff70) — readable C lift. */
void interface_draw_fullscreen_overlays(void)
{
  cinematic_render();
  interface_draw_splitscreen_dividers();
  hud_render_timer();
  terminal_draw();
  main_framerate_render();
  FUN_000df4e0();
}

/* interface_draw_bitmap (0xdff90) — readable C lift (restored pre-naked). */
void interface_draw_bitmap(int sprite_handle, short *offset_xy, void *color, float scale_a, int flag, float scale_b)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;

  FUN_001d9068();
  /* test dl, 2 -> je 0xe004c */
  /* cmp (int16_t)esi, 1 -> jle 0xe0059 */
  csmemset((void *)(uintptr_t)edx, 0, 0);
  rasterizer_sprites_render((void *)(uintptr_t)ecx, (void *)(uintptr_t)eax);

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
}


/* FUN_000e0110 (0xe0110) — readable C lift (restored pre-naked). */
void FUN_000e0110(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;

  FUN_001d9068();
  FUN_001d9068();
  FUN_001d9068();
  FUN_001d9068();
  /* cmp (int16_t)ecx, 1 -> jle 0xe020d */
  csmemset((void *)(uintptr_t)ecx, 0, 0);
  rasterizer_sprites_render((void *)(uintptr_t)ecx, (void *)(uintptr_t)eax);
  /* test dl, 2 -> je 0xe036b */
  /* cmp (int16_t)ecx, 1 -> jle 0xe0378 */
  csmemset((void *)(uintptr_t)ecx, 0, 0);
  rasterizer_sprites_render((void *)(uintptr_t)ecx, (void *)(uintptr_t)eax);
  /* relift: cmp byte ptr [0x30f028], 1 -> jne 0xe047d */
  file_reference_create_from_path((void *)(uintptr_t)eax, (char *)0x002825e0, 0);
  /* test eax, eax -> je 0xe0476 */
  file_exists((void *)(uintptr_t)ecx);
  /* test (char)eax, (char)eax -> je 0xe0476 */
  D3DDevice_PersistDisplay();
  error(0, (char *)0x002826a8);
  saved_game_files_take_mutex();
  cache_files_precache_in_progress();
  /* test (char)eax, (char)eax -> je 0xe04d1 */
  error(0, (char *)0x00282688);
  cache_files_precache_map_end();
  D3DDevice_PersistDisplay();
  /* test eax, eax -> jge 0xe04f7 */
  display_assert((char *)0x002825f8, (char *)0x00282640, 64, 0);
  system_exit(0);
  xbox_demos_available();

  (void)eax;
  (void)ecx;
  (void)edx;
}

