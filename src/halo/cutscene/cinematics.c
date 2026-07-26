void cinematic_initialize(void)
{
  cinematic_globals = (cinematic_globals_t *)game_state_malloc(
    "cinematic globals", 0, sizeof(cinematic_globals_t));
  assert_halt(cinematic_globals);
}

void cinematic_dispose(void)
{
}

void cinematic_initialize_for_new_map(void)
{
  csmemset(cinematic_globals, 0, sizeof(cinematic_globals_t));
  csmemset(cinematic_globals->unk_12, 0xFF, sizeof(cinematic_globals->unk_12));
}

void cinematic_dispose_from_old_map(void)
{
  cinematic_globals->unk_8 = false;
  cinematic_globals->in_progress = false;
}

bool cinematic_can_be_skipped(void)
{
  return cinematic_globals->can_be_skipped;
}

bool cinematic_in_progress(void)
{
  return cinematic_globals->in_progress;
}
/* --- cinematics.obj batch drafts (2026-07-26) --- */

/* 0x92e20 */
void cinematic_start(void)
{
  player_input_enable(0);
  ai_globals_dialogue_triggers_enabled(0);
  game_time_get();
}

/* 0x92e70 */
void cinematic_skip_start(void)
{
  /* relift: no calls detected — manual review */
}

/* 0x92e80 */
void cinematic_skip_stop(void)
{
  /* relift: no calls detected — manual review */
}

/* 0x92e90 */
void cinematic_show_letterbox(int a0)
{
  game_time_get();
}

/* 0x92ec0 */
void draw_quad(int16_t *rect, int color)
{
  int ebx = 0;
  int ecx = 0;

  global_scenario_get();
  game_globals_get();
  /* cmp ecx, ebx -> je 0x92ef8 */
  tag_block_get_element((void *)0, 0, 428);
  tag_get(0x6269746d, 0);
  tag_block_get_element((void *)0, 0, 0);
  csmemset((void *)0, 0, 140);
  rasterizer_sprites_render((void *)0, (void *)0);

  (void)ebx;
  (void)ecx;
}

/* 0x93010 */
void cinematic_force_title(void)
{
  /* relift: no calls detected — manual review */
}

/* 0x93030 */
void cinematic_suppress_bsp_object_creation(int a0)
{
  /* relift: no calls detected — manual review */
}

/* 0x93050 */
void cinematic_stop(void)
{
  int eax = 0;

  player_input_enable(0);
  ai_globals_dialogue_triggers_enabled(0);
  FUN_0017d950();
  /* test eax, eax -> je 0x9308f */
  csmemset((void *)0, 0, 16);
  FUN_0017dec0(0);

  (void)eax;
}

/* 0x930b0 */
void cinematic_set_title_delayed(int a0, float a1)
{
  int ecx = 0;
  int edx = 0;
  int esi = 0;

  /* relift: cmp word ptr [ecx + esi*4 + 0xc], (int16_t)edx -> je 0x93102 */
  /* cmp (int16_t)eax, 4 -> jl 0x930c2 */
  global_scenario_get();
  tag_block_get_element((void *)0, 0, 0);
  error(0, (void *)0x00268e9c);
  /* cmp (int16_t)eax, 4 -> jge 0x930d3 */

  (void)ecx;
  (void)edx;
  (void)esi;
}

/* 0x93140 */
void cinematic_render(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int edi = 0;

  /* test (char)eax, 0x41 -> jne 0x93346 */
  ui_widgets_active();
  /* test (char)eax, (char)eax -> jne 0x93346 */
  game_time_get();
  /* test (char)eax, 0x41 -> jne 0x931dc */
  /* test (char)eax, 0x41 -> jne 0x931e0 */
  /* test (char)eax, 0x41 -> jne 0x93346 */
  draw_quad((void *)0, 0xff000000);
  draw_quad((void *)0, 0xff000000);
  /* cmp (int16_t)eax, 0xffff -> je 0x9361b */
  global_scenario_get();
  tag_block_get_element((void *)0, 0, 0);
  global_scenario_get();
  /* cmp edi, -1 -> je 0x9361b */
  tag_get('rtsu', 0);
  /* test (int16_t)ecx, (int16_t)ecx -> jl 0x9361b */
  /* cmp ecx, edx -> jge 0x9361b */
  /* relift: cmp (int16_t)eax, word ptr [ebx] -> jne 0x93402 */
  game_in_editor();
  /* test (char)eax, (char)eax -> jne 0x93474 */
  /* test (char)eax, 0x41 -> jne 0x93472 */
  /* test (char)eax, 0x41 -> jne 0x93474 */
  pixel32_to_real_argb_color(0, (void *)0);
  /* test (char)eax, 0x41 -> jne 0x934ec */
  /* test (char)eax, 0x41 -> jne 0x93503 */
  /* test (char)eax, 0x41 -> jne 0x9351a */
  draw_string_set_font(0, 0, 0, 0, (void *)0);
  /* test eax, eax -> jge 0x9355f */
  /* cmp ecx, eax -> jg 0x9359a */
  rasterizer_text_set_shadow_color((void *)0);
  FUN_0019d420(0, 0);
  rasterizer_draw_string((void *)0, (void *)0, (void *)0, 0, (void *)0);
  rasterizer_text_set_shadow_color((void *)0);
  game_time_get_paused();
  /* test (char)eax, (char)eax -> je 0x935df */
  game_time_get_elapsed();
  game_in_editor();
  /* test (char)eax, (char)eax -> jne 0x9361b */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)edi;
}

/* 0x93640 */
void FUN_00093640(int a0)
{
  cinematic_set_title_delayed(0, 0.0f);
}

/* 0x93660 */
void FUN_00093660(void)
{
  int eax = 0;

  /* test (char)eax, (char)eax -> jbe 0x936a3 */
  /* cmp (char)eax, 3 -> jbe 0x9368d */
  /* cmp (char)eax, 4 -> jne 0x936a3 */
  FUN_00094290();
  FUN_00094ba0();

  (void)eax;
}

/* 0x93710 */
void FUN_00093710(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int esi = 0;

  /* cmp eax, ecx -> jge 0x9376f */
  /* relift: cmp dword ptr [esi + 4], ebx -> je 0x9376a */
  FUN_00118be0((void *)0, (void *)0, 0);
  /* cmp eax, ebx -> jne 0x93747 */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)esi;
}

/* 0x93780 */
void FUN_00093780(int a, int *cursor, int c)
{
  int eax = 0;
  int ecx = 0;
  int esi = 0;

  csmemset((void *)0, 0, 64);
  /* cmp eax, ecx -> jge 0x937fe */
  /* relift: cmp dword ptr [esi], -1 -> je 0x937f9 */
  /* cmp eax, -1 -> je 0x937e9 */
  csmemcpy((void *)0, (void *)0, 0);
  /* relift: cmp dword ptr [esi], -1 -> jne 0x937d0 */

  (void)eax;
  (void)ecx;
  (void)esi;
}

/* 0x93810 */
void FUN_00093810(void)
{
  int eax = 0;
  int ecx = 0;

  /* cmp eax, ecx -> jge 0x93879 */
  /* cmp eax, -1 -> je 0x93874 */
  csmemcpy((void *)0, (void *)0, 0);
  /* cmp eax, -1 -> jne 0x93850 */

  (void)eax;
  (void)ecx;
}

/* 0x93880 */
void FUN_00093880(void)
{
  int eax = 0;
  int ecx = 0;

  display_assert((void *)0x002690a0, (void *)0x002690a8, 25, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x938d3 */
  display_assert((void *)0x00265d1c, (void *)0x002690a8, 25, 0);
  system_exit(0);
  /* cmp (char)ecx, 8 -> je 0x938fd */
  display_assert((void *)0x0026906c, (void *)0x002690a8, 25, 0);
  system_exit(0);

  (void)eax;
  (void)ecx;
}

/* 0x93910 */
void FUN_00093910(void)
{
  int eax = 0;
  int ecx = 0;

  display_assert((void *)0x002690a0, (void *)0x002690a8, 26, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x93963 */
  display_assert((void *)0x00265d1c, (void *)0x002690a8, 26, 0);
  system_exit(0);
  /* cmp (char)ecx, 0xc -> je 0x9398d */
  display_assert((void *)0x002690e0, (void *)0x002690a8, 26, 0);
  system_exit(0);

  (void)eax;
  (void)ecx;
}

/* 0x939a0 */
void FUN_000939a0(void)
{
  int eax = 0;
  int ecx = 0;

  display_assert((void *)0x002690a0, (void *)0x002690a8, 27, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x939f3 */
  display_assert((void *)0x00265d1c, (void *)0x002690a8, 27, 0);
  system_exit(0);
  /* cmp (char)ecx, 0x10 -> je 0x93a1d */
  display_assert((void *)0x00269110, (void *)0x002690a8, 27, 0);
  system_exit(0);

  (void)eax;
  (void)ecx;
}

/* 0x93a30 */
void FUN_00093a30(void)
{
  int eax = 0;
  int ecx = 0;

  display_assert((void *)0x002690a0, (void *)0x002690a8, 28, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x93a83 */
  display_assert((void *)0x00265d1c, (void *)0x002690a8, 28, 0);
  system_exit(0);
  /* cmp (char)ecx, 0x14 -> je 0x93aad */
  display_assert((void *)0x00269140, (void *)0x002690a8, 28, 0);
  system_exit(0);

  (void)eax;
  (void)ecx;
}

/* 0x93ac0 */
void FUN_00093ac0(void)
{
  int eax = 0;
  int ecx = 0;

  display_assert((void *)0x002690a0, (void *)0x002690a8, 33, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x93b13 */
  display_assert((void *)0x00265d1c, (void *)0x002690a8, 35, 0);
  system_exit(0);
  /* cmp (char)ecx, 0x18 -> je 0x93b3d */
  display_assert((void *)0x00269170, (void *)0x002690a8, 36, 0);
  system_exit(0);

  (void)eax;
  (void)ecx;
}

/* 0x93b60 */
void FUN_00093b60(void)
{
  /* relift: no calls detected — manual review */
}

/* 0x93ba0 */
void FUN_00093ba0(void)
{
  /* relift: no calls detected — manual review */
}

/* 0x93be0 */
void FUN_00093be0(void)
{
  angles_to_vector((void *)0, (void *)0);
}

/* 0x93c20 */
void FUN_00093c20(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;

  display_assert((void *)0x002690a0, (void *)0x002690a8, 100, 0);
  system_exit(0);
  /* test esi, esi -> jne 0x93c78 */
  display_assert((void *)0x00265d1c, (void *)0x002690a8, 102, 0);
  system_exit(0);
  /* cmp dl, 0x1c -> jb 0x93c92 */
  /* cmp eax, 8 -> jl 0x93caf */
  display_assert((void *)0x002691a0, (void *)0x002690a8, 103, 0);
  system_exit(0);
  /* cmp (int16_t)eax, 0x3e8 -> jle 0x93ce8 */
  /* cmp (int16_t)eax, 0xfc18 -> jge 0x93cf6 */
  angles_to_vector((void *)0, (void *)0);
  /* test (int16_t)eax, (int16_t)eax -> je 0x93d69 */
  FUN_00093b60();
  FUN_00093be0();
  /* test (int16_t)eax, (int16_t)eax -> je 0x93dbc */
  /* test (int16_t)ecx, (int16_t)ecx -> je 0x93ded */
  FUN_00093b60();
  FUN_00093be0();

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
}

/* 0x93e20 */
void FUN_00093e20(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;

  display_assert((void *)0x002690a0, (void *)0x002690a8, 160, 0);
  system_exit(0);
  /* test esi, esi -> jne 0x93e7e */
  display_assert((void *)0x00265d1c, (void *)0x002690a8, 162, 0);
  system_exit(0);
  /* cmp dl, 0x3c -> jb 0x93e98 */
  /* cmp eax, 8 -> jl 0x93eb8 */
  display_assert((void *)0x00269238, (void *)0x002690a8, 163, 0);
  system_exit(0);
  /* cmp (int16_t)eax, 0x3e8 -> jle 0x93ef0 */
  /* cmp (int16_t)eax, 0xfc18 -> jge 0x93efe */
  angles_to_vector((void *)0, (void *)0);
  /* test (int16_t)eax, (int16_t)eax -> je 0x93f70 */
  FUN_00093ba0();
  FUN_00093be0();
  /* test (int16_t)eax, (int16_t)eax -> je 0x93fc3 */
  /* test (int16_t)ecx, (int16_t)ecx -> je 0x93ff4 */
  FUN_00093ba0();
  FUN_00093be0();
  FUN_00093780(0, (void *)0, 0);
  /* test eax, eax -> jne 0x940ca */
  display_assert((void *)0x002690a0, (void *)0x002690a8, 275, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x940f1 */
  display_assert((void *)0x00269368, (void *)0x002690a8, 276, 0);
  system_exit(0);
  /* test esi, esi -> jne 0x9411a */
  display_assert((void *)0x00269358, (void *)0x002690a8, 277, 0);
  system_exit(0);
  /* relift: cmp dword ptr [esi], 0 -> jne 0x9413f */
  display_assert((void *)0x00269344, (void *)0x002690a8, 278, 0);
  system_exit(0);
  /* cmp eax, 3 -> ja 0x941b9 */
  /* cmp (int16_t)ebx, 0xff -> jbe 0x941d9 */
  display_assert((void *)0x00255ee8, (void *)0x002690a8, 309, 0);
  system_exit(0);
  /* cmp edx, eax -> jl 0x94254 */
  /* cmp (char)eax, 4 -> je 0x94254 */
  /* cmp (char)eax, 0x5c -> jb 0x94220 */
  display_assert((void *)0x002692cc, (void *)0x002690a8, 315, 0);
  system_exit(0);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
}
