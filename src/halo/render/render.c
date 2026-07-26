void render_initialize(void)
{
  cached_object_render_states = game_state_data_new(
    "cached object render states", 0x100, 0x100); /* dup-args-ok */
  assert_halt(cached_object_render_states);
}

void render_initialize_for_new_map(void)
{
  data_delete_all(cached_object_render_states);
}

/* Invalidate the cached render states data if it exists and is valid
 * (0x184ba0). Thunk through 0x18afe0. */
void j__render_dispose_from_old_map(void)
{
  int ptr = *(int *)0x50652c;
  if (ptr && *(char *)(ptr + 0x24) != 0) {
    data_make_invalid((data_t *)ptr);
  }
}

void render_dispose(void)
{
  cached_object_render_states = 0;
}

/* Render a window in pregame mode. window_type selects the render path:
 *   0 = full pregame UI (loading screen, menus, bink playback)
 *   1 = inactive window (no player assigned, simpler scene render)
 * Called from render_frame with window_type passed via EBX register. */
void render_window_pregame(int window_type, int16_t *win)
{
  window_parameters_t window_params;

  profile_render_window_start(0);
  csmemset(&window_params, 0, sizeof(window_parameters_t));

  qmemcpy(&unknown_global_camera, (char *)win + 4, sizeof(camera_t));
  render_camera_build_frustum(&unknown_global_camera, 0, global_frustum, 1);

  qmemcpy(&window_params.camera, (char *)win + 0x58, sizeof(camera_t));
  render_camera_build_frustum(&window_params.camera, 0, window_params.frustum,
                              1);

  /* set up scene parameters */
  window_params.unk_0[0] = 0;
  window_params.unk_0[1] = -1;
  *((uint8_t *)&window_params + 5) = (window_type == 0);

  rasterizer_window_begin(&window_params);

  switch (window_type) {
  case 0:
    ((void (*)(void))0x0dff70)();
    ((void (*)(void))0x17e190)();
    break;
  case 1:
    ((void (*)(void))0x0af9a0)();
    break;
  default:
    display_assert("!\"unreachable\"", "c:\\halo\\SOURCE\\render\\render.c",
                   0x11f, 1);
    system_exit(-1);
    break;
  }

  rasterizer_window_end();
  profile_render_window_end();
}

void render_frame_pregame(pregame_render_info_t *pregame_info,
                          void *main_globals_movie)
{
  window_parameters_t window_parameters;
  float elapsed[2];
  float progress;

  ++render;
  rasterizer_frame_begin(elapsed);
  rasterizer_windows_begin();
  profile_render_window_start(0);
  csmemset(&window_parameters, 0, 0x258u);

  qmemcpy(&unknown_global_camera, &pregame_info->cam0,
          sizeof(unknown_global_camera));
  render_camera_build_frustum(&unknown_global_camera, 0, global_frustum, 1);

  qmemcpy(&window_parameters.camera, &pregame_info->cam1,
          sizeof(window_parameters.camera));
  render_camera_build_frustum(&window_parameters.camera, 0,
                              window_parameters.frustum, 1);
  window_parameters.unk_0[0] = 0;
  rasterizer_window_begin(&window_parameters);
  render_ui_widgets(0, &pregame_info->cam1.viewport_bounds);
  bink_playback_render();
  if (game_map_loading_in_progress(&progress)) {
    progress_bar_display(progress);
  }
  rasterizer_window_end();
  profile_render_window_end();
  rasterizer_windows_end();
  rasterizer_frame_end();
}

void render_frame_present(_WORD *a1, void *a2)
{
  ((void (*)(_WORD *, void *))0x17c930)(a2, a1);
}

/* Render a single game window. win is the window struct (passed via ESI in the
 * original binary). offset_or_null points to a packed (x_tile, y_tile) pair
 * for split-screen tile subdivision, or NULL for full-screen rendering.
 * Handles fog distance clamping, camera frustum setup, optional water/sky
 * reflection rendering, and the main scene render pass. */
void render_window(int16_t *win, void *offset_or_null)
{
  char *esi = (char *)win;
  char *render_cam = esi + 4;
  char *rasterizer_cam = esi + 0x58;
  float bounds[4];
  int rendered_reflection = 0;
  char reflection_info[28];
  camera_t reflection_cam;
  float render_frustum[99];
  float rasterizer_frustum[99];
  float reflection_frustum[99];

  /* initialize render pass for this camera */
  ((void (*)(void *))0x1965f0)(render_cam);

  /* update render globals from scene */
  *(int16_t *)0x506732 = 0;
  FUN_0018fbc0(*(int16_t *)esi, (int)(uint16_t) * (int16_t *)0x50678a,
               (const float *)render_cam, (char *)0x506730);
  ((void (*)(int, void *))0x198f10)((int)(uint16_t) * (int16_t *)0x506784,
                                    (void *)0x506730);

  /* track closest fog distance when BSP index is unknown */
  if (*(float *)0x506748 != *(float *)0x2533c0) {
    if (*(int16_t *)0x50678a == -1 && *(float *)0x506770 > *(float *)0x506748) {
      *(float *)0x506770 = *(float *)0x506748;
    }
  }

  /* clamp z_far to fog distance when fog type matches */
  if (*(float *)0x506740 == *(float *)0x2533c8 &&
      *(float *)0x506748 != *(float *)0x2533c0) {
    float fog = *(float *)0x506748;
    if (fog < *(float *)(esi + 0x44))
      *(float *)(esi + 0x44) = fog;
  }

  /* clamp z_far to closest fog in mode 2 */
  if (*(int16_t *)0x50674c == 2 && *(float *)0x506770 != *(float *)0x2533c0) {
    float fog = *(float *)0x506770;
    if (fog < *(float *)(esi + 0x44))
      *(float *)(esi + 0x44) = fog;
  }

  /* fog sanity: z_far must exceed z_near */
  if (*(float *)(esi + 0x44) <= *(float *)(esi + 0x40)) {
    if (!*(uint8_t *)0x4d0d02) {
      error(2, "### ERROR something is wrong with the fog in the "
               "sky tag or the fog tag");
      *(uint8_t *)0x4d0d02 = 1;
    }
    *(float *)(esi + 0x44) = *(float *)(esi + 0x40) + *(float *)0x25bb10;
  }

  /* assert viewport and window bounds match between cameras */
  if (((int (*)(void *, void *, int))0x8da40)(esi + 0x30, esi + 0x84, 8) != 0) {
    display_assert("!memcmp(&window->render_camera.viewport_bounds, "
                   "&window->rasterizer_camera.viewport_bounds, "
                   "sizeof(rectangle2d))",
                   "c:\\halo\\SOURCE\\render\\render.c", 0xbb, 1);
    system_exit(-1);
  }
  if (((int (*)(void *, void *, int))0x8da40)(esi + 0x38, esi + 0x8c, 8) != 0) {
    display_assert("!memcmp(&window->render_camera.window_bounds, "
                   "&window->rasterizer_camera.window_bounds, "
                   "sizeof(rectangle2d))",
                   "c:\\halo\\SOURCE\\render\\render.c", 0xbc, 1);
    system_exit(-1);
  }

  /* compute frustum bounds from the render camera */
  ((void (*)(void *, float *))0x185950)(render_cam, bounds);

  /* split-screen tile adjustment: narrow bounds to this tile */
  if (offset_or_null != NULL) {
    int16_t *tile = (int16_t *)offset_or_null;
    int total = (int)*(int16_t *)0x31fa98 * (int)*(int16_t *)0x46e008;
    if (total > 0) {
      float tw = (bounds[1] - bounds[0]) / (float)total;
      float th = (bounds[3] - bounds[2]) / (float)total;
      int y_idx = total - (int)tile[1] - 1;
      float x0 = (float)(int)tile[0] * tw + bounds[0];
      float y0 = (float)y_idx * th + bounds[2];
      bounds[0] = x0;
      bounds[1] = x0 + tw;
      bounds[2] = y0;
      bounds[3] = y0 + th;
    }
  }

  /* build projection frustums for both cameras */
  render_camera_build_frustum((camera_t *)render_cam, bounds, render_frustum,
                              1);
  render_camera_build_frustum((camera_t *)rasterizer_cam, bounds,
                              rasterizer_frustum, 1);

  /* reflection rendering (single player local only) */
  if (game_connection() == 1) {
    char has_refl = ((char (*)(void *, void *, void *))0x1975e0)(
      render_cam, render_frustum, reflection_info);
    if (has_refl) {
      int saved_bsp = *(int *)0x506784;

      /* reflection requires full-screen viewport */
      if (*(int16_t *)(esi + 0x32) != 0) {
        display_assert("window->render_camera.viewport_bounds.x0==0",
                       "c:\\halo\\SOURCE\\render\\render.c", 0xe1, 1);
        system_exit(-1);
      }
      if (*(int16_t *)(esi + 0x30) != 0) {
        display_assert("window->render_camera.viewport_bounds.y0==0",
                       "c:\\halo\\SOURCE\\render\\render.c", 0xe2, 1);
        system_exit(-1);
      }
      if (*(int16_t *)(esi + 0x36) != 0x280) {
        display_assert("window->render_camera.viewport_bounds.x1=="
                       "RASTERIZER_TARGET_RENDER_PRIMARY_WIDTH",
                       "c:\\halo\\SOURCE\\render\\render.c", 0xe3, 1);
        system_exit(-1);
      }
      if (*(int16_t *)(esi + 0x34) != 0x1e0) {
        display_assert("window->render_camera.viewport_bounds.y1=="
                       "RASTERIZER_TARGET_RENDER_PRIMARY_HEIGHT",
                       "c:\\halo\\SOURCE\\render\\render.c", 0xe4, 1);
        system_exit(-1);
      }

      /* build reflection camera and frustum */
      ((void (*)(void *, void *, void *))0x186ef0)(render_cam, reflection_info,
                                                   &reflection_cam);
      render_camera_build_frustum(&reflection_cam, bounds, reflection_frustum,
                                  1);

      /* render reflection to secondary target */
      ((void (*)(int))0x17c960)(0);
      *(int *)0x506784 = (int)*(int16_t *)(reflection_info + 0x18);

      render_scene(-1, &reflection_cam, reflection_frustum,
                   &reflection_cam, reflection_frustum, 1, 0);

      /* restore BSP and switch back to main render target */
      *(int *)0x506784 = saved_bsp;
      ((void (*)(int))0x17c960)(1);

      rendered_reflection = 1;
    }
  }

  render_scene(*(int16_t *)win, render_cam, render_frustum,
               rasterizer_cam, rasterizer_frustum, 0,
               (char)rendered_reflection);
}

void render_frame(void *a2, __int16 a3, _WORD *a4, _WORD *a5, void *a6,
                  float a7)
{
  int16_t i;
  float elapsed[2];
  int16_t *win;
  int tick;
  int16_t offset[2];

  *(int32_t *)0x506540 += 1;
  *(float *)0x50654c = a7;
  csmemset(elapsed, 0, 8);
  tick = game_time_get();
  elapsed[0] = (float)tick * *(float *)0x2546a4;
  rasterizer_frame_begin(elapsed);
  rasterizer_windows_begin();
  win = (int16_t *)a2;
  for (i = 0; i < a3; i++) {
    *(int16_t *)0x50654a = i;
    if ((char)win[1] != '\0') {
      render_window_pregame(0, win);
    } else if (win[0] == -1) {
      render_window_pregame(1, win);
    } else {
      if (a5 != NULL && a4 != NULL) {
        offset[0] = (int16_t)(*(int16_t *)a4 * *(int16_t *)0x31fa98 +
                              *(int16_t *)a5);
        offset[1] = (int16_t)(((int16_t *)a4)[1] * *(int16_t *)0x31fa98 +
                              ((int16_t *)a5)[1]);
      }
      render_window(win, a5 != NULL ? (void *)offset : NULL);
    }
    win += 0x56;
  }
  ((void (*)(void))0xe28e0)();
  rasterizer_windows_end();
  rasterizer_frame_end();
}
/* --- render.obj batch drafts (2026-07-26) --- */

/* 0x184570 */
char FUN_00184570(void *group)
{
  int eax = 0;

  rasterizer_transparent_geometry_group_to_presorted_index(eax);
  return 1;

  (void)eax;
}

/* 0x1845b0 */
void FUN_001845b0(void *group, int a2)
{
  int eax = 0;

  rasterizer_transparent_geometry_group_to_presorted_index(eax);
  /* cmp (int16_t)eax, 0xffff -> je 0x18460c */

  (void)eax;
}

/* 0x184610 */
int FUN_00184610(void *group)
{
  int eax = 0;
  int esi = 0;

  /* test esi, esi -> jne 0x18463f */
  display_assert((char *)0x0026276c, (char *)0x002b0ca8, 244, 0);
  system_exit(0);
  /* test eax, eax -> je 0x18464d */
  /* cmp esi, -1 -> je 0x184662 */
  rasterizer_widget_draw_sprite2d(0);
  error(0, (char *)0x002b0e18);
  return 0;

  (void)eax;
  (void)esi;
}

/* 0x184680 */
void FUN_00184680(void)
{
  /* relift: no calls detected — manual review */
}

/* 0x184690 */
void FUN_00184690(void)
{
  int eax = 0;
  int esi = 0;

  FUN_00174cc0();
  /* cmp eax, esi -> je 0x1846b4 */
  debug_free((void *)(uintptr_t)eax, (char *)0x002b0ca8, 273);
  /* mem[0x004d0cec] = esi */
  debug_free((void *)(uintptr_t)eax, (char *)0x002b0ca8, 276);
  /* mem[0x004d0cfc] = esi */
  debug_free((void *)(uintptr_t)eax, (char *)0x002b0ca8, 280);
  /* mem[0x004d0cf0] = esi */
  /* mem[0x004d0cf8] = esi */
  /* mem[0x004d0cf4] = esi */

  (void)eax;
  (void)esi;
}

/* 0x184710 */
void FUN_00184710(void)
{
  int eax = 0;

  FUN_00158ae0(0);
  /* test eax, eax -> jne 0x184744 */
  display_assert((char *)0x0026276c, (char *)0x002b0ca8, 402, 0);
  system_exit(0);

  (void)eax;
}

/* 0x184750 */
void group_sorted_indices_cmpfn(void)
{
  int eax = 0;
  int ecx = 0;
  int edi = 0;

  /* test (int16_t)eax, (int16_t)eax -> jl 0x184774 */
  /* cmp eax, ecx -> jl 0x184794 */
  display_assert((char *)0x002b0ea8, (char *)0x002b0ca8, 426, 0);
  system_exit(0);
  /* test edi, edi -> je 0x1847ae */
  /* test (int16_t)eax, (int16_t)eax -> jl 0x1847ae */
  /* relift: cmp ecx, dword ptr [0x4d0cf4] -> jl 0x1847ce */
  display_assert((char *)0x002b0e50, (char *)0x002b0ca8, 427, 0);
  system_exit(0);
  shader_is_water_decal((void *)0);
  /* test (char)eax, (char)eax -> jne 0x18488e */
  shader_is_water_decal((void *)(uintptr_t)eax);
  /* test (char)eax, (char)eax -> je 0x184816 */
  /* relift: cmp word ptr [eax + 0x24], (int16_t)ecx -> je 0x18488e */
  /* test eax, eax -> je 0x18483c */
  /* relift: cmp word ptr [eax + 0x24], (int16_t)ecx -> jne 0x18483c */
  /* test eax, eax -> je 0x18488e */
  /* test (char)eax, 0x41 -> jne 0x18486e */
  /* cmp eax, ecx -> jle 0x18488c */
  /* test (char)ecx, (char)ecx -> jne 0x1848b3 */
  /* test (char)ecx, (char)ecx -> je 0x1848bf */
  /* test (char)eax, (char)eax -> jne 0x1848bf */

  (void)eax;
  (void)ecx;
  (void)edi;
}

/* 0x1848d0 */
void rasterizer_sort_internal(void)
{
  int eax = 0;
  int esi = 0;

  /* test eax, eax -> jle 0x184927 */
  display_assert((char *)0x0026276c, (char *)0x002b0ca8, 402, 0);
  system_exit(0);
  /* cmp esi, eax -> jl 0x1848e0 */
  qsort((void *)(uintptr_t)eax, eax, 0, (void *)0x00184750);
  /* test esi, esi -> jle 0x18497a */
  /* cmp eax, esi -> jl 0x184960 */

  (void)eax;
  (void)esi;
}

/* 0x184980 */
void FUN_00184980(char param_1)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int esi = 0;

  FUN_0016f910(esi);
  /* test eax, eax -> jle 0x184b43 */
  rasterizer_sort_internal();
  FUN_00174ce0();
  /* test (char)ebx, (char)ebx -> je 0x184a3f */
  /* test eax, eax -> je 0x184b0c */
  /* relift: cmp word ptr [eax + 0x24], 7 -> je 0x184a3f */
  shader_is_water_decal((void *)(uintptr_t)eax);
  /* test (char)eax, (char)eax -> je 0x184b0c */
  /* test (char)ebx, (char)ebx -> je 0x184a68 */
  display_assert((char *)0x002b0f14, (char *)0x002b0ca8, 340, 0);
  system_exit(0);
  /* relift: cmp word ptr [0x5a5bc0], 0 -> je 0x184a92 */
  display_assert((char *)0x0029f520, (char *)0x002b0ca8, 341, 0);
  system_exit(0);
  /* test (char)eax, (char)eax -> jne 0x184ae2 */
  FUN_00158ae0(0);
  rasterizer_set_frustum_z(0.0f, 0.0f);
  /* test (char)eax, (char)eax -> je 0x184ae2 */
  display_assert((char *)0x002b0f00, (char *)0x002b0ca8, 355, 0);
  system_exit(0);
  rasterizer_transparent_geometry_group_draw((void *)(uintptr_t)esi, 0);
  /* cmp eax, ecx -> jl 0x184a00 */
  /* test (char)ebx, (char)ebx -> jne 0x184b24 */
  /* relift: cmp word ptr [0x5a5bc2], -1 -> je 0x184b24 */
  FUN_001749b0();
  rasterizer_set_frustum_z(0.0f, 0.0f);
  FUN_0016fa40(esi);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)esi;
}

/* 0x184b60 */
void render_effects(int a0)
{
  /* relift: no calls detected — manual review */
}

/* 0x184de0 */
char render_location_visible(void *location)
{
  int eax = 0;
  int ecx = 0;
  int esi = 0;

  /* relift: cmp word ptr [esi + 4], 0 -> jl 0x184dff */
  scenario_get();
  /* relift: cmp ecx, dword ptr [eax + 0x134] -> jl 0x184e1f */
  display_assert((char *)0x002b0f40, (char *)0x002b0f1c, 584, 0);
  system_exit(0);
  return 1;

  (void)eax;
  (void)ecx;
  (void)esi;
}

/* 0x184e50 */
void *rendered_cluster_get(int rendered_cluster_index)
{
  int esi = 0;

  /* test (int16_t)esi, (int16_t)esi -> jl 0x184e66 */
  /* relift: cmp (int16_t)esi, word ptr [0x5137cc] -> jl 0x184e86 */
  display_assert((char *)0x002b0fa8, (char *)0x002b0f1c, 592, 0);
  system_exit(0);
  return NULL;

  (void)esi;
}

/* 0x184ea0 */
void render_scene(int16_t player_index, void *render_cam, void *render_frustum, void *rasterizer_cam, void *rasterizer_frustum, int16_t pass_type, char reflected)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;

  profile_render_window_start(0);
  /* mem[0x00506544] = edx */
  csmemset((void *)(uintptr_t)eax, 0, 0);
  render_structure_visibility();
  player_effect_get_screen_flash();
  rasterizer_window_begin((void *)(uintptr_t)edx);
  bink_playback_has_video();
  /* test (char)eax, (char)eax -> jne 0x18524b */
  scenario_fog_region_get_fog_index();
  FUN_0018ca40();
  first_person_weapon_render_update();
  FUN_0013b380();
  scenario_test_pvs();
  FUN_001959f0();
  FUN_00195b10();
  FUN_00181a90();
  scenario_test_pas();
  FUN_0013a420();
  FUN_0017cb20(0);
  /* test (int16_t)eax, (int16_t)eax -> jle 0x185011 */
  /* test (int16_t)esi, (int16_t)esi -> jl 0x184fca */
  /* cmp (int16_t)esi, (int16_t)eax -> jl 0x184fea */
  display_assert((char *)0x002b0fa8, (char *)0x002b0f1c, 592, 0);
  system_exit(0);
  FUN_0017cb30(0);
  /* cmp (int16_t)esi, (int16_t)eax -> jl 0x184fc0 */
  FUN_0017cb40();
  FUN_0017cb20(0);
  /* test (int16_t)eax, (int16_t)eax -> jle 0x185081 */
  /* test (int16_t)esi, (int16_t)esi -> jl 0x18503a */
  /* cmp (int16_t)esi, (int16_t)eax -> jl 0x18505a */
  display_assert((char *)0x002b0fa8, (char *)0x002b0f1c, 592, 0);
  system_exit(0);
  FUN_0017cb30(0);
  /* cmp (int16_t)esi, (int16_t)eax -> jl 0x185030 */
  FUN_0017cb40();
  FUN_00195bc0();
  FUN_0017cb20(0);
  /* test (int16_t)eax, (int16_t)eax -> jle 0x1850f3 */
  /* test (int16_t)esi, (int16_t)esi -> jl 0x1850ac */
  /* cmp (int16_t)esi, (int16_t)eax -> jl 0x1850cc */
  display_assert((char *)0x002b0fa8, (char *)0x002b0f1c, 592, 0);
  system_exit(0);
  FUN_0017cb30(0);
  /* cmp (int16_t)esi, (int16_t)eax -> jl 0x1850a2 */
  FUN_0017cb40();
  FUN_0017cb20(0);
  /* test (int16_t)eax, (int16_t)eax -> jle 0x185161 */
  /* test (int16_t)esi, (int16_t)esi -> jl 0x18511a */
  /* cmp (int16_t)esi, (int16_t)eax -> jl 0x18513a */
  display_assert((char *)0x002b0fa8, (char *)0x002b0f1c, 592, 0);
  system_exit(0);
  FUN_0017cb30(0);
  /* cmp (int16_t)esi, (int16_t)eax -> jl 0x185110 */
  FUN_0017cb40();
  FUN_0013a5f0();
  FUN_00195c40();
  FUN_00195cb0();
  FUN_00195d00();
  FUN_00195d40();
  FUN_00195dc0();
  FUN_00195e40();
  get_postgame_hilite_colors();
  FUN_000a54b0();
  FUN_0018c5b0();
  particle_system_update();
  FUN_00188880();
  FUN_00184980(0);
  FUN_0017cb20(0);
  /* test (int16_t)eax, (int16_t)eax -> jle 0x185211 */
  /* test (int16_t)esi, (int16_t)esi -> jl 0x1851ca */
  /* cmp (int16_t)esi, (int16_t)eax -> jl 0x1851ea */
  display_assert((char *)0x002b0fa8, (char *)0x002b0f1c, 592, 0);
  system_exit(0);
  FUN_0017cb30(0);
  /* cmp (int16_t)esi, (int16_t)eax -> jl 0x1851c0 */
  FUN_0017cb40();
  FUN_00193c00();
  FUN_00184980(0);
  FUN_00184710();
  FUN_00195ec0();
  FUN_00181c20();
  interface_draw_screen();
  FUN_0017cba0();
  render_ui_widgets(ebx, (void *)(uintptr_t)ecx);
  bink_playback_render();
  render_camera_debug_frustum();
  FUN_0018ac50();
  FUN_000977e0();
  FUN_0017e190();
  rasterizer_window_end();
  profile_render_window_end();

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
}
