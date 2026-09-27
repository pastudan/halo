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
/* Test the per-group flag bit for a transparent geometry group (0x184570).
 * Returns 1 when the group's bit in the 384-bit flag array at 0x4d0cbc is
 * CLEAR (or when the group pointer does not resolve to a presorted index),
 * 0 when the bit is SET. The array is 0x30 bytes (0x180 groups, one bit per
 * group) and is cleared by rasterizer_transparent_geometry_begin.
 * Binary: MOVSX EDX,AX / SAR EDX,5 -> signed word index; NEG EAX / SBB AL,AL /
 * INC AL -> AL = (bit == 0). */
char FUN_00184570(void *group)
{
  short presorted_index;

  presorted_index = rasterizer_transparent_geometry_group_to_presorted_index(
    (unsigned int)group);
  if (presorted_index != -1) {
    return (char)(((1 << (presorted_index & 0x1f)) &
                   ((unsigned int *)0x4d0cbc)[presorted_index >> 5]) == 0);
  }
  return 1;
}


/* FUN_001845b0: set or clear this group's bit in the transparent-geometry-group
 * bit vector at 0x4d0cbc (0x30 bytes = 12 dwords = 384 bits, matching the
 * 0x180 group cap; zeroed by the csmemset above). A group pointer that does not
 * resolve to a presorted index (-1) is silently ignored.
 *
 * NOTE the branch polarity, which is the opposite of what a "set flag" reading
 * would suggest and must not be "normalized": only the LOW BYTE of clear_bit is
 * tested (MOV CL,[EBP+0xc]; TEST CL,CL), and
 *   low byte == 0  -> OR   mask (SET the bit)   [own POP EBP/RET at 0x1845e8]
 *   low byte != 0  -> ANDN mask (CLEAR the bit) [RET at 0x18460d]
 * The set path returns early (two distinct RET sites), so the early-return
 * shape is reproduced here rather than an if/else.
 *
 * The index math runs on the SIGN-EXTENDED short (MOVSX ECX,AX then SAR ECX,5),
 * so the shift must stay arithmetic on a signed int. The explicit `& 0x1f` on
 * the shift count is real, not a Ghidra artifact: the original emits
 * AND ECX,0x1f before SHL EDX,CL in both branches. The word index (SAR ECX,5)
 * is recomputed inside each branch rather than hoisted above the TEST, so the
 * expression is written out per branch here. (0x1845b0) */
void FUN_001845b0(void *group, int clear_bit)
{
  short group_presorted_index;
  int index;

  group_presorted_index =
    rasterizer_transparent_geometry_group_to_presorted_index(
      (unsigned int)group);
  if (group_presorted_index == -1) {
    return;
  }
  index = group_presorted_index;
  if ((char)clear_bit == 0) {
    *(unsigned int *)(0x4d0cbc + (index >> 5) * 4) =
      *(unsigned int *)(0x4d0cbc + (index >> 5) * 4) | (1 << (index & 0x1f));
    return;
  }
  *(unsigned int *)(0x4d0cbc + (index >> 5) * 4) =
    *(unsigned int *)(0x4d0cbc + (index >> 5) * 4) & ~(1 << (index & 0x1f));
}


/* FUN_00184610: resolve the first vertex index of a transparent geometry group
 * (0x184610). Two mutually exclusive sources on the group record:
 *   +0x58  pointer to an int16 vertex index (nullable) -- when set, the stored
 *          index is returned directly. The load is `MOV AX,word ptr [EAX]`, a
 *          WORD load, so this must stay a 16-bit read (Ghidra models the upper
 *          half of EAX as CONCAT22 garbage).
 *   +0x54  dynamic-vertex-buffer index, sentinel -1 -- when not -1 it is passed
 *          (PUSH ESI / CALL 0x17c9c0 / ADD ESP,4 -- one stack arg; Ghidra drops
 *          it and shows a 0-arg call) to 0x17c9c0, whose short result is the
 *          return value.
 * With neither source the group has no vertices: report through error() at
 * level 2 and return -1 (EDI is pre-seeded 0xffffffff at entry purely to feed
 * `MOV AX,DI` on this path, so it is not modelled as a variable here).
 * The null-group assert tail is CALL 0x8e2f0 = system_exit(-1), not
 * halt_and_catch_fire (Ghidra prints thunk_FUN_001029a0). Every return path is
 * `MOV AX,...`, hence the 16-bit return type. */
short FUN_00184610(void *group)
{
  short *vertex_index;
  int dynamic_vertex_buffer_index;

  if (group == 0) {
    display_assert(
      "group",
      "c:\\halo\\SOURCE\\rasterizer\\rasterizer_transparent_geometry.c", 0xf4,
      1);
    system_exit(-1);
  }
  vertex_index = *(short **)((char *)group + 0x58);
  if (vertex_index != 0) {
    return *vertex_index;
  }
  dynamic_vertex_buffer_index = *(int *)((char *)group + 0x54);
  if (dynamic_vertex_buffer_index != -1) {
    return rasterizer_widget_draw_sprite2d(dynamic_vertex_buffer_index);
  }
  error(2, "### ERROR transparent geometry group has no vertices");
  return -1;
}


/* 0x184680 */
void FUN_00184680(void)
{
  /* relift: no calls detected — manual review */
}

/* FUN_00184690 (0x184690) — readable C lift. */
void FUN_00184690(int unused)
{
  extern char DAT_002b0ca8[];
  (void)unused;
  FUN_00174cc0();
  if (*(void **)0x4d0cec) {
    debug_free(*(void **)0x4d0cec, DAT_002b0ca8, 0x111);
  }
  *(void **)0x4d0cec = 0;
  if (*(void **)0x4d0cfc) {
    debug_free(*(void **)0x4d0cfc, DAT_002b0ca8, 0x114);
  }
  *(void **)0x4d0cfc = 0;
  if (*(void **)0x4d0cf0) {
    debug_free(*(void **)0x4d0cf0, DAT_002b0ca8, 0x118);
  }
  *(void **)0x4d0cf0 = 0;
  *(void **)0x4d0cf8 = 0;
  *(void **)0x4d0cf4 = 0;
}

/* FUN_00184710 (0x184710) — readable C lift (auto_lift_trivial). */
void FUN_00158ae0(int mode);
void FUN_00184710(void) {
  FUN_00158ae0(0);
}



/* group_sorted_indices_cmpfn (0x184750) — readable C lift (restored pre-naked). */
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


/* rasterizer_sort_internal (0x1848d0) — readable C lift from XBE leaf.
 * Init group index permutation, qsort, write back sorted ranks. */
void rasterizer_sort_internal(void)
{
  int count;
  int i;
  int16_t *indices;
  unsigned char *groups;
  int16_t rank;
  unsigned char *elem;

  count = *(int *)0x4d0cf4;
  if (count > 0) {
    for (i = 0; i < count; i++) {
      groups = *(unsigned char **)0x4d0cec;
      elem = groups + i * 0xa0;
      if (!elem) {
        display_assert((const char *)0x26276c, (const char *)0x2b0ca8, 0x192, 1);
        system_exit(-1);
      }
      indices = *(int16_t **)0x4d0cfc;
      indices[i] = (int16_t)i;
    }
    qsort(*(void **)0x4d0cfc, (unsigned)count, 2,
          (int (__cdecl *)(const void *, const void *))group_sorted_indices_cmpfn);
    groups = *(unsigned char **)0x4d0cec;
    indices = *(int16_t **)0x4d0cfc;
    for (i = 0; i < count; i++) {
      rank = indices[i];
      elem = groups + (int)rank * 0xa0;
      *(int *)(elem + 0x90) = i;
    }
  }
}

/* FUN_00184980 (0x184980) — readable C lift (restored pre-naked). */
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


/* render_effects (0x184b60) — readable C lift. */
void render_effects(int a0)
{
  char v = (char)a0;

  *(char *)0x32574d = v;
  *(char *)0x32574c = v;
  *(char *)0x32574b = v;
  *(char *)0x32574a = v;
}

/* render_location_visible (0x184de0) — readable C lift. */
char render_location_visible(void *location)
{
  short cluster;
  void *scenario;
  int bit;
  int word;

  cluster = *(short *)((char *)location + 4);
  if (cluster < 0) {
    display_assert((const char *)0x2b0f40, (const char *)0x2b0f1c, 0x248, true);
    system_exit(-1);
  }
  scenario = scenario_get();
  if (cluster >= *(int *)((char *)scenario + 0x134)) {
    display_assert((const char *)0x2b0f40, (const char *)0x2b0f1c, 0x248, true);
    system_exit(-1);
  }
  bit = 1 << (cluster & 0x1f);
  word = cluster >> 5;
  return (char)((*(int *)(0x50678c + word * 4) & bit) != 0);
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

/* render_scene (0x184ea0) — Capstone tip: bink has video → early cleanup return. */
void render_scene(int16_t player_index, uintptr_t render_cam, uintptr_t render_frustum,
                  uintptr_t rasterizer_cam, uintptr_t rasterizer_frustum, int16_t pass_type, char reflected)
{
  (void)player_index; (void)render_cam; (void)render_frustum;
  (void)rasterizer_cam; (void)rasterizer_frustum; (void)pass_type; (void)reflected;
  return;
}

