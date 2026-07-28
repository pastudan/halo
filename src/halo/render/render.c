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

/* FUN_00184980 (0x184980) — XBE naked draft (batch 121). */
#if defined(__clang__)
static void (*const b184980_c16f910)(int16_t profile) = FUN_0016f910;
static void (*const b184980_c1848d0)(void) = rasterizer_sort_internal;
static void (*const b184980_c174ce0)(void) = FUN_00174ce0;
static char (*const b184980_c190930)(void *shader) = shader_is_water_decal;
static void (*const b184980_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b184980_exitfn)(int) = system_exit;
static void (*const b184980_c158ae0)(int mode) = FUN_00158ae0;
static void (*const b184980_c156c30)(float near_z, float far_z) = rasterizer_set_frustum_z;
static void (*const b184980_c174d10)(void *group, int dirty) = rasterizer_transparent_geometry_group_draw;
static void (*const b184980_c1749b0)(void) = FUN_001749b0;
static void (*const b184980_c16fa40)(int16_t profile) = FUN_0016fa40;

__attribute__((naked, noinline))
void FUN_00184980(char param_1 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "movb 0x8(%%ebp), %%bl\n\t"
      "movb %%bl, %%al\n\t"
      "negb %%al\n\t"
      "pushl %%esi\n\t"
      "sbbl %%eax, %%eax\n\t"
      "andl $0xfffffffd, %%eax\n\t"
      "addl $0x16, %%eax\n\t"
      "movl %%eax, %%esi\n\t"
      "pushl %%esi\n\t"
      "movl %%esi, -0x4(%%ebp)\n\t"
      "call *%[c16f910]\n\t"
      "movl 0x4d0cf4, %%eax\n\t"
      "addl $4, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jle .LFUN_00184980_11\n\t"
      "testb %%bl, %%bl\n\t"
      "movb $0, 0xb(%%ebp)\n\t"
      "je .LFUN_00184980_1\n\t"
      "call *%[c1848d0]\n\t"
      "cmpw $-1, 0x5a5bc2\n\t"
      "movw $0, 0x4d0cb8\n\t"
      "je .LFUN_00184980_1\n\t"
      "movb $1, 0x325740\n\t"
      ".LFUN_00184980_1:\n\t"
      "call *%[c174ce0]\n\t"
      "movswl 0x4d0cb8, %%eax\n\t"
      "cmpl 0x4d0cf4, %%eax\n\t"
      "movb $0, 0x325740\n\t"
      "jge .LFUN_00184980_9\n\t"
      "jmp .LFUN_00184980_2\n\t"
      "leal (%%esp), %%esp\n\t"
      "nop\n\t"
      ".LFUN_00184980_2:\n\t"
      "movl 0x4d0cfc, %%ecx\n\t"
      "movswl (%%ecx,%%eax,2), %%eax\n\t"
      "movl 0x4d0cec, %%ecx\n\t"
      "leal (%%eax,%%eax,4), %%esi\n\t"
      "shll $5, %%esi\n\t"
      "addl %%ecx, %%esi\n\t"
      "testb %%bl, %%bl\n\t"
      "je .LFUN_00184980_3\n\t"
      "movl 0xc(%%esi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_00184980_8\n\t"
      "cmpw $7, 0x24(%%eax)\n\t"
      "je .LFUN_00184980_3\n\t"
      "pushl %%eax\n\t"
      "call *%[c190930]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00184980_8\n\t"
      ".LFUN_00184980_3:\n\t"
      "cmpb $0, (%%esi)\n\t"
      "jns .LFUN_00184980_6\n\t"
      "testb %%bl, %%bl\n\t"
      "je .LFUN_00184980_4\n\t"
      "pushl $1\n\t"
      "pushl $0x154\n\t"
      "pushl $0x2b0ca8\n\t"
      "pushl $0x2b0f14\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00184980_4:\n\t"
      "cmpw $0, 0x5a5bc0\n\t"
      "je .LFUN_00184980_5\n\t"
      "pushl $1\n\t"
      "pushl $0x155\n\t"
      "pushl $0x2b0ca8\n\t"
      "pushl $0x29f520\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00184980_5:\n\t"
      "movb 0xb(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00184980_7\n\t"
      "pushl $0\n\t"
      "call *%[c158ae0]\n\t"
      "movl 0x3256a0, %%edx\n\t"
      "movl 0x32569c, %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c156c30]\n\t"
      "addl $0xc, %%esp\n\t"
      "movb $1, 0xb(%%ebp)\n\t"
      "jmp .LFUN_00184980_7\n\t"
      ".LFUN_00184980_6:\n\t"
      "movb 0xb(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00184980_7\n\t"
      "pushl $1\n\t"
      "pushl $0x163\n\t"
      "pushl $0x2b0ca8\n\t"
      "pushl $0x2b0f00\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00184980_7:\n\t"
      "pushl $0\n\t"
      "pushl %%esi\n\t"
      "call *%[c174d10]\n\t"
      "movw 0x4d0cb8, %%ax\n\t"
      "movl 0x4d0cf4, %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "incw %%ax\n\t"
      "movw %%ax, 0x4d0cb8\n\t"
      "movswl %%ax, %%eax\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jl .LFUN_00184980_2\n\t"
      ".LFUN_00184980_8:\n\t"
      "movl -0x4(%%ebp), %%esi\n\t"
      ".LFUN_00184980_9:\n\t"
      "testb %%bl, %%bl\n\t"
      "jne .LFUN_00184980_10\n\t"
      "cmpw $-1, 0x5a5bc2\n\t"
      "je .LFUN_00184980_10\n\t"
      "movb $1, 0x325740\n\t"
      ".LFUN_00184980_10:\n\t"
      "call *%[c1749b0]\n\t"
      "movb 0xb(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "movb $0, 0x325740\n\t"
      "je .LFUN_00184980_11\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "call *%[c156c30]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_00184980_11:\n\t"
      "pushl %%esi\n\t"
      "call *%[c16fa40]\n\t"
      "addl $4, %%esp\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c16f910] "m"(b184980_c16f910), [c1848d0] "m"(b184980_c1848d0), [c174ce0] "m"(b184980_c174ce0), [c190930] "m"(b184980_c190930), [assert] "m"(b184980_assert), [exitfn] "m"(b184980_exitfn), [c158ae0] "m"(b184980_c158ae0), [c156c30] "m"(b184980_c156c30), [c174d10] "m"(b184980_c174d10), [c1749b0] "m"(b184980_c1749b0), [c16fa40] "m"(b184980_c16fa40)
      : "memory");
}
#else
#error "FUN_00184980: clang naked draft required"
#endif


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

/* render_scene (0x184ea0) — XBE naked draft (batch 80). */
#if defined(__clang__)
static void (*const b184ea0_c915b0)(char a1) = profile_render_window_start;
static void *(*const b184ea0_memset)(void *, int, unsigned int) = csmemset;
static void (*const b184ea0_c198180)(void) = render_structure_visibility;
static void (*const b184ea0_ca2fc0)(void) = player_effect_get_screen_flash;
static int (*const b184ea0_c17c8d0)(window_parameters_t *a1) = rasterizer_window_begin;
static bool (*const b184ea0_c1c5980)(void) = bink_playback_has_video;
static void (*const b184ea0_c18d0b0)(void) = scenario_fog_region_get_fog_index;
static void (*const b184ea0_c18ca40)(void) = FUN_0018ca40;
static void (*const b184ea0_cddae0)(void) = first_person_weapon_render_update;
static void (*const b184ea0_c13b380)(void) = FUN_0013b380;
static void (*const b184ea0_c18c3a0)(void) = scenario_test_pvs;
static void (*const b184ea0_c1959f0)(void) = FUN_001959f0;
static void (*const b184ea0_c195b10)(void) = FUN_00195b10;
static void (*const b184ea0_c181a90)(void) = FUN_00181a90;
static void (*const b184ea0_c18c460)(void) = scenario_test_pas;
static void (*const b184ea0_c13a420)(void) = FUN_0013a420;
static void (*const b184ea0_c17cb20)(short pass_index) = FUN_0017cb20;
static void (*const b184ea0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b184ea0_exitfn)(int) = system_exit;
static void (*const b184ea0_c17cb30)(int rendered_cluster_data) = FUN_0017cb30;
static void (*const b184ea0_c17cb40)(void) = FUN_0017cb40;
static void (*const b184ea0_c195bc0)(void) = FUN_00195bc0;
static void (*const b184ea0_c13a5f0)(void) = FUN_0013a5f0;
static void (*const b184ea0_c195c40)(void) = FUN_00195c40;
static void (*const b184ea0_c195cb0)(void) = FUN_00195cb0;
static void (*const b184ea0_c195d00)(void) = FUN_00195d00;
static void (*const b184ea0_c195d40)(void) = FUN_00195d40;
static void (*const b184ea0_c195dc0)(void) = FUN_00195dc0;
static void (*const b184ea0_c195e40)(void) = FUN_00195e40;
static void (*const b184ea0_ca8630)(void) = get_postgame_hilite_colors;
static void (*const b184ea0_ca54b0)(void) = FUN_000a54b0;
static void (*const b184ea0_c18c5b0)(void) = FUN_0018c5b0;
static void (*const b184ea0_ca1170)(void) = particle_system_update;
static void (*const b184ea0_c188880)(void) = FUN_00188880;
static void (*const b184ea0_c184980)(char param_1) = FUN_00184980;
static void (*const b184ea0_c193c00)(void) = FUN_00193c00;
static void (*const b184ea0_c184710)(void) = FUN_00184710;
static void (*const b184ea0_c195ec0)(void) = FUN_00195ec0;
static void (*const b184ea0_c181c20)(void) = FUN_00181c20;
static void (*const b184ea0_cdefb0)(void) = interface_draw_screen;
static void (*const b184ea0_c17cba0)(void) = FUN_0017cba0;
static void (*const b184ea0_ce78e0)(__int16 a1, viewport_bounds_t *window_bounds) = render_ui_widgets;
static void (*const b184ea0_c1c63e0)(void) = bink_playback_render;
static void (*const b184ea0_c186d40)(void) = render_camera_debug_frustum;
static void (*const b184ea0_c18ac50)(void) = FUN_0018ac50;
static void (*const b184ea0_c977e0)(void) = FUN_000977e0;
static void (*const b184ea0_c17e190)(void) = FUN_0017e190;
static void (*const b184ea0_c17c900)(void) = rasterizer_window_end;
static void (*const b184ea0_c91640)(void) = profile_render_window_end;

__attribute__((naked, noinline))
void render_scene(int16_t player_index __attribute__((unused)), void *render_cam __attribute__((unused)), void *render_frustum __attribute__((unused)), void *rasterizer_cam __attribute__((unused)), void *rasterizer_frustum __attribute__((unused)), int16_t pass_type __attribute__((unused)), char reflected __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x258, %%esp\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl $1\n\t"
      "call *%[c915b0]\n\t"
      "movl 0x506544, %%edx\n\t"
      "pushl $0x258\n\t"
      "leal -0x258(%%ebp), %%eax\n\t"
      "incl %%edx\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "movl %%edx, 0x506544\n\t"
      "call *%[memset]\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "movb 0x1c(%%ebp), %%dl\n\t"
      "movw %%bx, 0x506548\n\t"
      "movl $0x15, %%ecx\n\t"
      "movl $0x506550, %%edi\n\t"
      "rep movsl\n\t"
      "movl 0xc(%%ebp), %%esi\n\t"
      "movl $0x63, %%ecx\n\t"
      "movl $0x5065a4, %%edi\n\t"
      "rep movsl\n\t"
      "movl 0x10(%%ebp), %%esi\n\t"
      "movw 0x50654a, %%ax\n\t"
      "movl $0x15, %%ecx\n\t"
      "leal -0x250(%%ebp), %%edi\n\t"
      "rep movsl\n\t"
      "movl 0x14(%%ebp), %%esi\n\t"
      "movl $0x63, %%ecx\n\t"
      "leal -0x1fc(%%ebp), %%edi\n\t"
      "rep movsl\n\t"
      "movw 0x18(%%ebp), %%cx\n\t"
      "movw %%cx, -0x258(%%ebp)\n\t"
      "movb %%dl, -0x254(%%ebp)\n\t"
      "movw %%ax, -0x256(%%ebp)\n\t"
      "movl $0x14, %%ecx\n\t"
      "movl $0x506730, %%esi\n\t"
      "leal -0x70(%%ebp), %%edi\n\t"
      "rep movsl\n\t"
      "call *%[c198180]\n\t"
      "leal -0x20(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "call *%[ca2fc0]\n\t"
      "leal -0x258(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c17c8d0]\n\t"
      "addl $0x1c, %%esp\n\t"
      "call *%[c1c5980]\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lrender_scene_21\n\t"
      "call *%[c18d0b0]\n\t"
      "call *%[c18ca40]\n\t"
      "call *%[cddae0]\n\t"
      "call *%[c13b380]\n\t"
      "call *%[c18c3a0]\n\t"
      "call *%[c1959f0]\n\t"
      "call *%[c195b10]\n\t"
      "call *%[c181a90]\n\t"
      "call *%[c18c460]\n\t"
      "call *%[c13a420]\n\t"
      "pushl $2\n\t"
      "call *%[c17cb20]\n\t"
      "movw 0x5137cc, %%ax\n\t"
      "addl $4, %%esp\n\t"
      "xorl %%esi, %%esi\n\t"
      "testw %%ax, %%ax\n\t"
      "jle .Lrender_scene_4\n\t"
      "jmp .Lrender_scene_1\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".Lrender_scene_1:\n\t"
      "testw %%si, %%si\n\t"
      "jl .Lrender_scene_2\n\t"
      "cmpw %%ax, %%si\n\t"
      "jl .Lrender_scene_3\n\t"
      ".Lrender_scene_2:\n\t"
      "pushl $1\n\t"
      "pushl $0x250\n\t"
      "pushl $0x2b0f1c\n\t"
      "pushl $0x2b0fa8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrender_scene_3:\n\t"
      "movswl %%si, %%eax\n\t"
      "imull $0x1a0, %%eax, %%eax\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x5067cc(%%eax), %%cx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c17cb30]\n\t"
      "movw 0x5137cc, %%ax\n\t"
      "addl $4, %%esp\n\t"
      "incl %%esi\n\t"
      "cmpw %%ax, %%si\n\t"
      "jl .Lrender_scene_1\n\t"
      ".Lrender_scene_4:\n\t"
      "call *%[c17cb40]\n\t"
      "pushl $3\n\t"
      "call *%[c17cb20]\n\t"
      "movw 0x5137cc, %%ax\n\t"
      "addl $4, %%esp\n\t"
      "xorl %%esi, %%esi\n\t"
      "testw %%ax, %%ax\n\t"
      "jle .Lrender_scene_8\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".Lrender_scene_5:\n\t"
      "testw %%si, %%si\n\t"
      "jl .Lrender_scene_6\n\t"
      "cmpw %%ax, %%si\n\t"
      "jl .Lrender_scene_7\n\t"
      ".Lrender_scene_6:\n\t"
      "pushl $1\n\t"
      "pushl $0x250\n\t"
      "pushl $0x2b0f1c\n\t"
      "pushl $0x2b0fa8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrender_scene_7:\n\t"
      "movswl %%si, %%edx\n\t"
      "imull $0x1a0, %%edx, %%edx\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x5067cc(%%edx), %%ax\n\t"
      "pushl %%eax\n\t"
      "call *%[c17cb30]\n\t"
      "movw 0x5137cc, %%ax\n\t"
      "addl $4, %%esp\n\t"
      "incl %%esi\n\t"
      "cmpw %%ax, %%si\n\t"
      "jl .Lrender_scene_5\n\t"
      ".Lrender_scene_8:\n\t"
      "call *%[c17cb40]\n\t"
      "call *%[c195bc0]\n\t"
      "pushl $0\n\t"
      "call *%[c17cb20]\n\t"
      "movw 0x5137cc, %%ax\n\t"
      "addl $4, %%esp\n\t"
      "xorl %%esi, %%esi\n\t"
      "testw %%ax, %%ax\n\t"
      "jle .Lrender_scene_12\n\t"
      ".Lrender_scene_9:\n\t"
      "testw %%si, %%si\n\t"
      "jl .Lrender_scene_10\n\t"
      "cmpw %%ax, %%si\n\t"
      "jl .Lrender_scene_11\n\t"
      ".Lrender_scene_10:\n\t"
      "pushl $1\n\t"
      "pushl $0x250\n\t"
      "pushl $0x2b0f1c\n\t"
      "pushl $0x2b0fa8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrender_scene_11:\n\t"
      "movswl %%si, %%ecx\n\t"
      "imull $0x1a0, %%ecx, %%ecx\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x5067cc(%%ecx), %%dx\n\t"
      "pushl %%edx\n\t"
      "call *%[c17cb30]\n\t"
      "movw 0x5137cc, %%ax\n\t"
      "addl $4, %%esp\n\t"
      "incl %%esi\n\t"
      "cmpw %%ax, %%si\n\t"
      "jl .Lrender_scene_9\n\t"
      ".Lrender_scene_12:\n\t"
      "call *%[c17cb40]\n\t"
      "pushl $1\n\t"
      "call *%[c17cb20]\n\t"
      "movw 0x5137cc, %%ax\n\t"
      "addl $4, %%esp\n\t"
      "xorl %%esi, %%esi\n\t"
      "testw %%ax, %%ax\n\t"
      "jle .Lrender_scene_16\n\t"
      "nop\n\t"
      ".Lrender_scene_13:\n\t"
      "testw %%si, %%si\n\t"
      "jl .Lrender_scene_14\n\t"
      "cmpw %%ax, %%si\n\t"
      "jl .Lrender_scene_15\n\t"
      ".Lrender_scene_14:\n\t"
      "pushl $1\n\t"
      "pushl $0x250\n\t"
      "pushl $0x2b0f1c\n\t"
      "pushl $0x2b0fa8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrender_scene_15:\n\t"
      "movswl %%si, %%eax\n\t"
      "imull $0x1a0, %%eax, %%eax\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x5067cc(%%eax), %%cx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c17cb30]\n\t"
      "movw 0x5137cc, %%ax\n\t"
      "addl $4, %%esp\n\t"
      "incl %%esi\n\t"
      "cmpw %%ax, %%si\n\t"
      "jl .Lrender_scene_13\n\t"
      ".Lrender_scene_16:\n\t"
      "call *%[c17cb40]\n\t"
      "call *%[c13a5f0]\n\t"
      "call *%[c195c40]\n\t"
      "call *%[c195cb0]\n\t"
      "call *%[c195d00]\n\t"
      "call *%[c195d40]\n\t"
      "call *%[c195dc0]\n\t"
      "call *%[c195e40]\n\t"
      "call *%[ca8630]\n\t"
      "call *%[ca54b0]\n\t"
      "call *%[c18c5b0]\n\t"
      "call *%[ca1170]\n\t"
      "call *%[c188880]\n\t"
      "pushl $1\n\t"
      "call *%[c184980]\n\t"
      "pushl $4\n\t"
      "call *%[c17cb20]\n\t"
      "movw 0x5137cc, %%ax\n\t"
      "addl $8, %%esp\n\t"
      "xorl %%esi, %%esi\n\t"
      "testw %%ax, %%ax\n\t"
      "jle .Lrender_scene_20\n\t"
      ".Lrender_scene_17:\n\t"
      "testw %%si, %%si\n\t"
      "jl .Lrender_scene_18\n\t"
      "cmpw %%ax, %%si\n\t"
      "jl .Lrender_scene_19\n\t"
      ".Lrender_scene_18:\n\t"
      "pushl $1\n\t"
      "pushl $0x250\n\t"
      "pushl $0x2b0f1c\n\t"
      "pushl $0x2b0fa8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrender_scene_19:\n\t"
      "movswl %%si, %%edx\n\t"
      "imull $0x1a0, %%edx, %%edx\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x5067cc(%%edx), %%ax\n\t"
      "pushl %%eax\n\t"
      "call *%[c17cb30]\n\t"
      "movw 0x5137cc, %%ax\n\t"
      "addl $4, %%esp\n\t"
      "incl %%esi\n\t"
      "cmpw %%ax, %%si\n\t"
      "jl .Lrender_scene_17\n\t"
      ".Lrender_scene_20:\n\t"
      "call *%[c17cb40]\n\t"
      "call *%[c193c00]\n\t"
      "pushl $0\n\t"
      "call *%[c184980]\n\t"
      "call *%[c184710]\n\t"
      "call *%[c195ec0]\n\t"
      "call *%[c181c20]\n\t"
      "call *%[cdefb0]\n\t"
      "call *%[c17cba0]\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "addl $0x2c, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "call *%[ce78e0]\n\t"
      "addl $0xc, %%esp\n\t"
      ".Lrender_scene_21:\n\t"
      "call *%[c1c63e0]\n\t"
      "pushl $0x5065a4\n\t"
      "pushl $0x506550\n\t"
      "call *%[c186d40]\n\t"
      "addl $8, %%esp\n\t"
      "call *%[c18ac50]\n\t"
      "call *%[c977e0]\n\t"
      "call *%[c17e190]\n\t"
      "call *%[c17c900]\n\t"
      "call *%[c91640]\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c915b0] "m"(b184ea0_c915b0), [memset] "m"(b184ea0_memset), [c198180] "m"(b184ea0_c198180), [ca2fc0] "m"(b184ea0_ca2fc0), [c17c8d0] "m"(b184ea0_c17c8d0), [c1c5980] "m"(b184ea0_c1c5980), [c18d0b0] "m"(b184ea0_c18d0b0), [c18ca40] "m"(b184ea0_c18ca40), [cddae0] "m"(b184ea0_cddae0), [c13b380] "m"(b184ea0_c13b380), [c18c3a0] "m"(b184ea0_c18c3a0), [c1959f0] "m"(b184ea0_c1959f0), [c195b10] "m"(b184ea0_c195b10), [c181a90] "m"(b184ea0_c181a90), [c18c460] "m"(b184ea0_c18c460), [c13a420] "m"(b184ea0_c13a420), [c17cb20] "m"(b184ea0_c17cb20), [assert] "m"(b184ea0_assert), [exitfn] "m"(b184ea0_exitfn), [c17cb30] "m"(b184ea0_c17cb30), [c17cb40] "m"(b184ea0_c17cb40), [c195bc0] "m"(b184ea0_c195bc0), [c13a5f0] "m"(b184ea0_c13a5f0), [c195c40] "m"(b184ea0_c195c40), [c195cb0] "m"(b184ea0_c195cb0), [c195d00] "m"(b184ea0_c195d00), [c195d40] "m"(b184ea0_c195d40), [c195dc0] "m"(b184ea0_c195dc0), [c195e40] "m"(b184ea0_c195e40), [ca8630] "m"(b184ea0_ca8630), [ca54b0] "m"(b184ea0_ca54b0), [c18c5b0] "m"(b184ea0_c18c5b0), [ca1170] "m"(b184ea0_ca1170), [c188880] "m"(b184ea0_c188880), [c184980] "m"(b184ea0_c184980), [c193c00] "m"(b184ea0_c193c00), [c184710] "m"(b184ea0_c184710), [c195ec0] "m"(b184ea0_c195ec0), [c181c20] "m"(b184ea0_c181c20), [cdefb0] "m"(b184ea0_cdefb0), [c17cba0] "m"(b184ea0_c17cba0), [ce78e0] "m"(b184ea0_ce78e0), [c1c63e0] "m"(b184ea0_c1c63e0), [c186d40] "m"(b184ea0_c186d40), [c18ac50] "m"(b184ea0_c18ac50), [c977e0] "m"(b184ea0_c977e0), [c17e190] "m"(b184ea0_c17e190), [c17c900] "m"(b184ea0_c17c900), [c91640] "m"(b184ea0_c91640)
      : "memory");
}
#else
#error "render_scene: clang naked draft required"
#endif

