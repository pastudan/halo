/* Internal timing/memory checkpoint. Queries memory stats and stores
 * available kilobytes to a global. The string parameter is a debug
 * label unused in retail. */
void bink_playback_trace(const char *msg)
{
  uint32_t mem_status[8];
  csmemset(mem_status, 0, 0x20);
  mem_status[0] = 0x20;
  xbox_query_global_memory_status(mem_status);
  *(uint32_t *)0x32eb9c = mem_status[3] >> 10;
}

/* Bink video playback system for cinematics and loading screens. */

/* Returns true if a bink video is currently open and the subsystem
 * is initialized. Used by callers to gate rendering and input. */
bool bink_playback_active(void)
{
  if (*(int *)0x4ead60 != 0 && *(uint8_t *)0x4ead58 != 0)
    return true;
  return false;
}

/* Returns true if bink is initialized and was started with flag 0x8
 * (suppress-UI mode). Callers use this to skip rendering UI widgets
 * during attract-mode or other fullscreen bink playback. */
bool bink_playback_suppress_ui(void)
{
  if (*(uint8_t *)0x4ead58 != 0 && (*(uint8_t *)0x4ead5c & 8) != 0)
    return true;
  return false;
}

/* Returns true if a bink video handle is open (regardless of whether
 * the subsystem is initialized). */
bool bink_playback_has_video(void)
{
  return *(int *)0x4ead60 != 0;
}

/* Bump-allocate from the top of the bink memory pool with alignment.
 * Computes a candidate pointer at (pool_base + pool_remaining - size),
 * aligns it down if needed, then decrements the remaining pool size.
 * alignment is passed in EAX, alloc_size in ECX (register args). */
void *bink_memory_pool_alloc(int alignment /* @<eax> */,
                             int alloc_size /* @<ecx> */)
{
  unsigned int ptr;
  unsigned int align = (unsigned int)alignment;
  unsigned int size = (unsigned int)alloc_size;

  ptr = (*(unsigned int *)0x4eae2c - size) + *(unsigned int *)0x4eae24;

  if (align != 0 && (ptr & (align - 1)) != 0) {
    if (align == 0 || (align & (align - 1)) != 0) {
      display_assert("alignment_in_bytes>0 && "
                     "(alignment_in_bytes&(alignment_in_bytes-1))==0",
                     "c:\\halo\\SOURCE\\bink\\bink_playback.c", 0x2b3, 1);
      system_exit(-1);
    }
    {
      unsigned int diff = align - ptr;
      unsigned int padding = diff & (align - 1);
      size += padding;
      ptr -= (align - 1) & diff;
    }
  }

  if (size == 0) {
    display_assert("size_in_bytes>0", "c:\\halo\\SOURCE\\bink\\bink_playback.c",
                   0x2b9, 1);
    system_exit(-1);
  }
  if (*(unsigned int *)0x4eae2c < size) {
    display_assert("bink_globals.memory_pool_size>=size_in_bytes",
                   "c:\\halo\\SOURCE\\bink\\bink_playback.c", 0x2ba, 1);
    system_exit(-1);
  }
  if (*(unsigned int *)0x4eae24 == 0) {
    display_assert("bink_globals.memory_pool_base",
                   "c:\\halo\\SOURCE\\bink\\bink_playback.c", 699, 1);
    system_exit(-1);
  }

  *(unsigned int *)0x4eae2c = *(unsigned int *)0x4eae2c - size;
  return (void *)ptr;
}

/* Returns true if all entries in the bink memory pool allocation table
 * are zero (i.e. no outstanding allocations). The pool is an array of
 * dwords at 0x4eacd0 with a count at 0x4eae30. Used by the texture
 * cache release path to assert that all bink allocations were freed. */
bool bink_memory_pool_is_empty(void)
{
  short i;
  bool empty;

  i = 0;
  empty = true;
  if (0 < *(int *)0x4eae30) {
    int idx = 0;
    do {
      if (*(int *)(idx * 4 + 0x4eacd0) != 0) {
        empty = false;
      }
      i = i + 1;
      idx = (int)i;
    } while (idx < *(int *)0x4eae30);
  }
  return empty;
}

/* Release a bink memory pool allocation. Searches the allocation table at
 * 0x4eacd0 (up to 0x4eae30 entries) for a pointer matching ptr, and zeroes
 * that slot when found. If the pointer is not found (or the pool is empty),
 * calls display_assert and exits — "bink just confused the hell out of me (2)".
 * Bracketed by bink_playback_trace calls (memory checkpoint) before the
 * search and after the successful free. Calling convention: __stdcall (RET 4).
 */
void __stdcall bink_memory_pool_free(int ptr)
{
  uint32_t mem_status[8];
  int count;
  int i;

  csmemset(mem_status, 0, 0x20);
  mem_status[0] = 0x20;
  xbox_query_global_memory_status(mem_status);
  *(uint32_t *)0x32eb9c = mem_status[3] >> 10;

  count = *(int *)0x4eae30;
  i = 0;
  if (0 < count) {
    do {
      if (*(int *)(i * 4 + 0x4eacd0) == ptr) {
        *(int *)(i * 4 + 0x4eacd0) = 0;
        if (i < count) {
          goto found;
        }
        break;
      }
      i = i + 1;
    } while (i < count);
  }
  display_assert("### FATAL_ERROR bink just confused the hell out of me (2)",
                 "c:\\halo\\SOURCE\\bink\\bink_playback.c", 0x339, 1);
  system_exit(-1);

found:
  csmemset(mem_status, 0, 0x20);
  mem_status[0] = 0x20;
  xbox_query_global_memory_status(mem_status);
  *(uint32_t *)0x32eb9c = mem_status[3] >> 10;
}

/* Render the bink frame quad on screen with optional debug overlay.
 *
 * Builds a 4-vertex textured quad from the current display bounds and
 * video dimensions, centered on screen unless flag bit 0x10 is set
 * (fullscreen stretch). Calls the sprite renderer to draw the quad.
 *
 * If the debug flag at 0x4ead54 is set (never in retail), draws
 * a text overlay with Bink frame timing statistics. */
void bink_playback_render_frame(void)
{
  char text_buf[1024];
  char summary_buf[256];
  short screen_pos[4];
  float vertices[20]; /* 4 verts x 5 floats (x, y, u, v, color) */
  short top_y, left_x, right_x, bottom_y;
  short sVar9;
  int counter;
  int i;
  short display_top, display_left, display_bottom, display_right;
  int horiz_span, vert_span;
  short video_w, video_h;

  display_top = *(int16_t *)0x325654;
  display_left = *(int16_t *)0x325656;
  display_bottom = *(int16_t *)0x325658;
  display_right = *(int16_t *)0x32565a;

  if ((*(uint32_t *)0x4ead5c & 0x10) != 0) {
    /* Fullscreen stretch: use display bounds directly. */
    top_y = display_top;
    left_x = display_left;
    bottom_y = display_bottom;
    right_x = display_right;
  } else {
    /* Center the video in the display area. */
    horiz_span = (int)(display_right - display_left);
    vert_span = (int)(display_bottom - display_top);
    video_w = *(int16_t *)0x4ead64;
    video_h = *(int16_t *)0x4ead66;
    left_x = (short)((horiz_span - (int)video_w) / 2);
    right_x = (short)((horiz_span + (int)video_w) / 2);
    top_y = (short)((vert_span - (int)video_h) / 2);
    bottom_y = (short)((vert_span + (int)video_h) / 2);
  }

  sVar9 = 0;
  counter = 1;
  i = 0;
  do {
    float u_val, v_val, x_val, y_val;

    /* u coordinate: 0 for left side, video_width for right side. */
    if ((counter & 2) != 0) {
      u_val = (float)(int)*(int16_t *)0x4ead64;
    } else {
      u_val = 0.0f;
    }

    /* v coordinate: 0 for top, video_height for bottom. */
    if (sVar9 > 1) {
      v_val = (float)(int)*(int16_t *)0x4ead66;
    } else {
      v_val = 0.0f;
    }

    /* x position. */
    if ((counter & 2) != 0) {
      x_val = (float)(int)right_x;
    } else {
      x_val = (float)(int)left_x;
    }

    /* y position. */
    if (sVar9 < 2) {
      y_val = (float)(int)top_y;
    } else {
      y_val = (float)(int)bottom_y;
    }

    vertices[i * 5 + 0] = x_val;
    vertices[i * 5 + 1] = y_val;
    vertices[i * 5 + 2] = u_val;
    vertices[i * 5 + 3] = v_val;
    *(uint32_t *)&vertices[i * 5 + 4] = 0xffffffff; /* white, full alpha */

    sVar9 = sVar9 + 1;
    counter = counter + 1;
    i++;
  } while (sVar9 < 4);

  rasterizer_sprites_render((void *)0x4ead98, vertices);

  if (*(uint8_t *)0x4ead54 != 0) {
    /* Debug overlay: gather Bink timing stats and draw on screen. */
    int bink_handle = *(int *)0x4ead60;
    int16_t frame_info[14];
    float scale;

    frame_info[0] = 0xfa; /* max frame count for averaging */
    frame_info[1] = 0;
    frame_info[2] = 0;
    frame_info[3] = 0;
    frame_info[4] = 0;
    frame_info[5] = 0;
    frame_info[9] = 0;
    frame_info[10] = 0;

    BinkGetFrameBuffersInfo((void *)bink_handle, frame_info, 0);

    /* Compute scale factor: 1.0 / total_time. The decompiler shows
     * complex unsigned-to-float conversions for each timing field,
     * then multiplication by scale. Faithfully reproduce this. */
    {
      float total_f = (float)(int)frame_info[8]; /* FIXME: uint32 at offset */
      /* The original reads dword-sized fields from the frame_info struct
       * at offsets that alias over the short array. These are actually
       * dword timing fields from BinkGetFrameBuffersInfo. Use hardcoded
       * pointer arithmetic to match the original exactly. */
      int *fi = (int *)frame_info;
      int total_time = fi[8]; /* offset 0x10 from frame_info base */

      if (total_time < 0)
        total_f = total_f + *(float *)0x25fb8c;
      scale = 1.0f / total_f;

      /* Format timing stats into text buffer. */
      crt_sprintf(
        text_buf,
        "FramesTime=|t%.02f|nFrameVideoDecompTime=|t%.02f|n"
        "FrameAudioDecompTime=|t%.02f|nFrameReadTime=|t%.02f|n"
        "FrameIdleReadTime=|t%.02f|nFrameThreadReadTime=|t%.02f|n"
        "FramesBlitTime=|t%.02f|n|nFrames=|t%d",
        (double)((float)fi[7] < 0 ? (float)fi[7] + *(float *)0x25fb8c :
                                    (float)fi[7]) *
          scale,
        (double)((float)fi[6] < 0 ? (float)fi[6] + *(float *)0x25fb8c :
                                    (float)fi[6]) *
          scale,
        (double)((float)fi[5] < 0 ? (float)fi[5] + *(float *)0x25fb8c :
                                    (float)fi[5]) *
          scale,
        (double)((float)fi[4] < 0 ? (float)fi[4] + *(float *)0x25fb8c :
                                    (float)fi[4]) *
          scale,
        (double)((float)fi[3] < 0 ? (float)fi[3] + *(float *)0x25fb8c :
                                    (float)fi[3]) *
          scale,
        (double)((float)fi[2] < 0 ? (float)fi[2] + *(float *)0x25fb8c :
                                    (float)fi[2]) *
          scale,
        (double)((float)fi[1] < 0 ? (float)fi[1] + *(float *)0x25fb8c :
                                    (float)fi[1]) *
          scale,
        total_time);
    }

    /* Offset screen position by display origin. */
    {
      short dx = *(int16_t *)0x32565c;
      short dy = *(int16_t *)0x325660;
      screen_pos[0] = dx;
      screen_pos[1] = dy;
      screen_pos[2] = dx;
      screen_pos[3] = dy;
    }
    rect2d_offset(screen_pos, 0, 0x20);

    /* Set up text rendering. */
    interface_draw_text(1, 5, 0, 0, -1, 1);
    draw_string_set_color(*(const void **)0x2ee6d4);
    draw_string_set_tab_stops(&frame_info[0], 1);
    rasterizer_text_draw(screen_pos, NULL, (void *)&frame_info[8], -4,
                         text_buf);

    /* Check if enough frames have passed to update stats. */
    if (*(int *)0x4ead88 - *(int *)0x4ead84 > 0x1c) {
      BinkGetSummary((void *)*(int *)0x4ead60, summary_buf);

      *(int *)0x4ead8c = *(int *)(summary_buf + 0x2c) - *(int *)0x4ead7c;
      *(int *)0x4ead90 = *(int *)(summary_buf + 0x30) - *(int *)0x4ead80;
      *(int *)0x4ead94 = *(int *)0x4ead88 - *(int *)0x4ead84;
      *(int *)0x4ead7c = *(int *)(summary_buf + 0x2c);
      *(int *)0x4ead80 = *(int *)(summary_buf + 0x30);
      *(int *)0x4ead84 = *(int *)0x4ead88;
    }

    /* Draw skipped frames / blits stats. */
    {
      int skipped_frames = *(int *)0x4ead8c;
      int skipped_blits = *(int *)0x4ead90;
      int frame_count = *(int *)0x4ead94;

      /* Advance screen position using the cursor y-offset written by the
       * previous draw (high word of the dword stored at frame_info[8]). */
      screen_pos[0] = (int16_t)(frame_info[9] + 0x1f);

      crt_sprintf(text_buf, "SkippedFrames=|t%d (%d)|nSkippedBlits=|t%d|n",
                  skipped_frames, frame_count, skipped_blits);
      draw_string_set_color(*(const void **)0x2ee6d0);
      rasterizer_text_draw(screen_pos, NULL, (void *)&frame_info[8], -4,
                           text_buf);
    }
  }
}

/* Poll all 4 gamepad slots and return true if any digital button or
 * either analog trigger is in the "just pressed" state (value == 1).
 * Used to detect a skip request during bink video playback.
 * Checks trigger bytes at offsets 0x1c and 0x1d, and 8 digital
 * button bytes starting at offset 0x10 in the gamepad state struct. */
bool bink_playback_check_any_button(void)
{
  short pad;
  bool pressed;

  pressed = false;
  pad = 0;
  do {
    if (pressed) {
      return pressed;
    }
    {
      void *state = input_get_gamepad_state((int)pad);
      if (state != NULL) {
        if (*(char *)((int)state + 0x1c) == 1 ||
            *(char *)((int)state + 0x1d) == 1) {
          pressed = true;
        } else {
          short btn = 0;
          do {
            if (*(char *)((int)btn + 0x10 + (int)state) == 1) {
              pressed = true;
              break;
            }
            btn = btn + 1;
          } while (btn < 8);
        }
      }
    }
    pad = pad + 1;
  } while (pad < 4);
  return pressed;
}

/* Bink texture lock adapter. Reorders arguments from the original
 * __fastcall register layout (flags@EAX, rect@ECX, locked_rect@EDX,
 * texture+level on stack) into the standard D3DTexture_LockRect
 * cdecl call. Returns 0. Used as a Bink SDK callback. */
int FUN_001c6170(unsigned int flags, void *rect, void *locked_rect,
                 void *texture, unsigned int level)
{
  D3DTexture_LockRect(texture, level, locked_rect, rect, flags);
  return 0;
}

/* Initialize the bink playback globals and register callbacks. */
void bink_playback_initialize(void)
{
  csmemset((void *)0x4ead58, 0, 0xd8);
  BinkSetSoundSystem((void *)0x1c5ab0, (void *)0x1c5ca0);
  *(uint8_t *)0x4ead58 = 1;
}

/* Release texture cache memory stolen for bink playback. Asserts that
 * all bink pool allocations have been freed before returning memory
 * back to the texture cache. Clears pool base, texture pointer, and
 * pool size globals. */
void bink_playback_release_texture_cache(void)
{
  if (*(uint8_t *)0x4ead58 == 0)
    return;
  if (*(int *)0x4eae24 == 0)
    return;

  if (!bink_memory_pool_is_empty()) {
    display_assert(
      "we released the texture cache but we still had memory allocated",
      "c:\\halo\\SOURCE\\bink\\bink_playback.c", 0x299, 1);
    system_exit(-1);
  }
  xbox_texture_cache_return_memory();
  *(uint32_t *)0x4eae24 = 0;
  *(uint32_t *)0x4ead78 = 0;
  *(uint32_t *)0x4eae2c = 0;
}

/* Decode the current bink frame and blit it to the D3D texture.
 * Calls BinkDoFrame + BinkNextFrame to advance decoding, then locks
 * the texture surface and copies the decoded frame data into it
 * via BinkCopyToBuffer. Temporarily sets the D3D status word to 6
 * during the lock/copy to signal the GPU. */
void bink_playback_decode_frame(void)
{
  int locked_rect[2]; /* [0]=Pitch, [1]=pBits */

  BinkDoFrame((void *)*(int *)0x4ead60);
  BinkNextFrame((void *)*(int *)0x4ead60);
  *(uint16_t *)0x325652 = 6;
  D3DTexture_LockRect((void *)*(int *)0x4ead78, 0, locked_rect, 0, 0);
  BinkCopyToBuffer((void *)*(int *)0x4ead60, (void *)locked_rect[1],
                   locked_rect[0], *(int *)(*(int *)0x4ead60 + 4), 0, 0,
                   *(uint32_t *)0x4ead70 | 0x80000000);
  *(uint16_t *)0x325652 = 0;
}

/* Stop the currently playing bink video. Closes the bink handle,
 * releases texture cache memory, restores the pregame loading flag,
 * reloads the main menu if the flag was set, and marks event time. */
void bink_playback_stop(void)
{
  if (*(uint8_t *)0x4ead58 == 0)
    return;

  /* If events were suppressed during playback, re-enable them. */
  if ((*(uint32_t *)0x4ead5c & 4) != 0) {
    event_manager_suppress(0);
  }

  /* Close the bink handle if one is open. */
  if (*(int *)0x4ead60 != 0) {
    BinkClose((void *)*(int *)0x4ead60);
    *(int *)0x4ead60 = 0;
  }

  /* Release bink texture cache memory. */
  bink_playback_release_texture_cache();

  /* If the main menu flag was set, reload the main menu. */
  if ((*(uint32_t *)0x4ead5c & 0x20) != 0) {
    main_menu_load();
  }

  /* Restore the pregame loading flag from saved value and clear flags.
   * The original loads the saved byte, clears the flags dword, then
   * stores - preserving the load across the clear. */
  {
    uint8_t saved = *(uint8_t *)0x32eba0;
    *(uint32_t *)0x4ead5c = 0;
    *(uint8_t *)0x31fa96 = saved;
  }

  event_manager_mark_time();
}

/* Dispose: stop any playing video and clear globals. */
void bink_playback_dispose(void)
{
  if (*(uint8_t *)0x4ead58 != 0) {
    bink_playback_stop();
    csmemset((void *)0x4ead58, 0, 0xd8);
  }
}

/* Check whether the video should stop (end of file, user skip, etc.)
 * and call bink_playback_stop if so.
 *
 * When the pregame loading flag is set, BinkWait is called once and
 * needs_decode is set based on the result. When loading is not active,
 * BinkWait is called in a busy loop until the frame is ready.
 *
 * The video stops if:
 *  - The user pressed a button (flag bit 2 = skippable), unless
 *    flag bit 0x40 is set and ui widget initialization is still running.
 *  - The video reached the last frame and flag bit 1 (loop) is not set. */
void bink_playback_check_stop(void)
{
  int wait_result;
  uint8_t flags;

  if (*(uint8_t *)0x4ead58 == 0)
    return;
  if (*(int *)0x4ead60 == 0)
    return;

  if (*(uint8_t *)0x31fa96 != 0) {
    /* Pregame loading active: single BinkWait call. */
    wait_result = BinkWait((void *)*(int *)0x4ead60);
    *(uint8_t *)0x4ead59 = (uint8_t)(wait_result == 0);
  } else {
    /* Not loading: busy-wait until frame is ready. */
    do {
      wait_result = BinkWait((void *)*(int *)0x4ead60);
    } while (wait_result != 0);
    *(uint8_t *)0x4ead59 = 1;
  }

  flags = *(uint8_t *)0x4ead5c;

  /* Check if user wants to skip the video. */
  if ((flags & 2) != 0) {
    if ((flags & 0x40) == 0 || !ui_widget_initialization_in_progress()) {
      if (bink_playback_check_any_button()) {
        bink_playback_stop();
        return;
      }
    }
    flags = *(uint8_t *)0x4ead5c;
  }

  /* Check if video has ended. */
  if (*(int *)0x4ead60 == 0 || *(int *)(*(int *)0x4ead60 + 0xc) ==
                                 *(int *)(*(int *)0x4ead60 + 0x8) - 1) {
    if ((flags & 1) == 0) {
      bink_playback_stop();
      return;
    }
  }
}

/* Render the current bink frame if a video is playing. Handles
 * the pregame/loading flag to decide when to flush. */
void bink_playback_render(void)
{
  if (*(uint8_t *)0x4ead58 == 0)
    return;
  if (*(int *)0x4ead60 == 0)
    return;

  if (*(uint8_t *)0x31fa96 != 0) {
    *(uint8_t *)0x4ead59 = 1;
  } else if (*(uint8_t *)0x4ead59 == 0) {
    goto skip_flush;
  }

  bink_playback_decode_frame();
  *(uint8_t *)0x4ead59 = 0;

skip_flush:
  bink_playback_render_frame();
  *(int *)0x4ead88 += 1;

  if (*(uint8_t *)0x31fa96 != 0)
    return;

  bink_playback_check_stop();
}

/* Open and begin playing a bink video file. Allocates memory from the
 * texture cache, opens the bink file, sets up the D3D texture, and
 * configures the render state for fullscreen video playback.
 *
 * flags bit 0x80: high-res mode (16MB pool instead of 4MB)
 * flags bit 0x04: suppress event manager during playback
 * flags bit 0x20: reload main menu when video stops
 * Other flag bits are stored and checked by bink_playback_check_stop. */
void bink_playback_start(const char *filename, unsigned int flags)
{
  uint32_t mem_status[8];
  int *bink;
  unsigned int pool_size;
  unsigned int frame_buf_size;
  int ds_handle;
  int ds_ok;
  void *pool_base;
  void *frame_buf;
  unsigned int hi_res;
  unsigned int bink_flags;
  short bpp;
  int bits_total;

  /* Query memory stats and update global available-KB counter. */
  csmemset(mem_status, 0, 0x20);
  mem_status[0] = 0x20;
  xbox_query_global_memory_status(mem_status);
  *(uint32_t *)0x32eb9c = mem_status[3] >> 10;

  /* Early out if subsystem not initialized or precache in progress. */
  if (*(uint8_t *)0x4ead58 == 0)
    return;
  if (cache_files_precache_in_progress())
    return;

  /* Assert if a video is already playing. */
  if (*(int *)0x4ead60 != 0) {
    display_assert("there is already a bink movie being played",
                   "c:\\halo\\SOURCE\\bink\\bink_playback.c", 0x19e, 1);
    system_exit(-1);
  }

  /* Determine memory pool size based on high-res flag.
   * hi_res (bit 0x80): 0x1000000 (16MB), normal: 0x400000 (4MB). */
  hi_res = flags & 0x80;
  pool_size = (-(unsigned int)(hi_res != 0) & 0xc00000) + 0x400000;
  *(uint32_t *)0x4eae2c = pool_size;
  *(uint32_t *)0x4eae28 = 0;

  /* Steal physical memory from the texture cache for bink. */
  pool_base = xbox_texture_cache_steal_memory(pool_size);
  *(uint32_t *)0x4eae24 = (uint32_t)pool_base;

  /* Assert pool size is page-aligned (4KB). */
  {
    unsigned int remainder = pool_size & 0x80000fff;
    int aligned = 0;
    if ((int)remainder < 0)
      aligned = (remainder - 1 | 0xfffff000) == 0xffffffff;
    else
      aligned = remainder == 0;
    if (!aligned) {
      display_assert("0 == (bink_globals.memory_pool_size % CPU_PAGE_SIZE)",
                     "c:\\halo\\SOURCE\\bink\\bink_playback.c", 0x1a8, 1);
      system_exit(-1);
    }
  }

  /* Set memory protection on the pool (read/write). */
  physical_memory_protect(pool_base, pool_size, 2);

  /* If pool allocation failed, log error and bail. */
  if (*(uint32_t *)0x4eae24 == 0) {
    error(0, "### ERROR bink failed to fucking steal some fucking "
             "memory from the fucking texture cache");
    bink_playback_release_texture_cache();
    return;
  }

  /* Set up DirectSound for bink audio. */
  bink_playback_trace("begin BinkOpen");
  ds_handle = bink_get_dsound_handle();
  ds_ok = 0;
  if (ds_handle != 0) {
    bink_playback_trace("begin BinkSoundUseDirectSound");
    if (BinkSoundUseDirectSound((void *)0x231e80, (void *)ds_handle) != 0) {
      ds_ok = 1;
    }
    bink_playback_trace("end BinkSoundUseDirectSound");
    if (ds_ok)
      goto sound_ok;
  }
  error(2, "### ERROR no DirectSound for bink");

sound_ok:
  /* Configure bink memory limit for high-res mode. */
  if (hi_res != 0) {
    BinkSetMemory(0xc00000);
    bink_flags = 0x1000000;
  } else {
    bink_flags = 0;
  }

  /* Open the bink file. */
  bink = (int *)BinkOpen(filename, bink_flags);
  *(int **)0x4ead60 = bink;
  bink_playback_trace("end BinkOpen");

  if (bink != NULL) {
    /* Calculate page-aligned frame buffer size:
     * width * height * 4 bytes per pixel, rounded up to 4KB page. */
    frame_buf_size = (unsigned int)(bink[1] * bink[0] * 4 + 0xfff) & 0xfffff000;

    /* Allocate frame buffer from the bink memory pool. */
    frame_buf = bink_memory_pool_alloc(0x80, (int)frame_buf_size);

    /* Set memory protection on the frame buffer (read/write/nocache). */
    bink_playback_trace("begin XPhysicalProtect");
    physical_memory_protect(frame_buf, frame_buf_size, 0x404);
    bink_playback_trace("end XPhysicalProtect");

    /* Fill the frame buffer with random data (noise pattern). */
    {
      int i = 0;
      if (0 < (int)frame_buf_size) {
        do {
          int rval = rand();
          *((uint8_t *)frame_buf + i) = (uint8_t)(rval >> 8);
          i++;
        } while (i < (int)frame_buf_size);
      }
    }

    /* Store video dimensions as shorts. */
    *(int16_t *)0x4ead64 = (int16_t)bink[0]; /* width */
    *(int16_t *)0x4ead66 = (int16_t)bink[1]; /* height */

    /* Build the D3D texture header format dword.
     * Encodes width, height in the NV2A texture format. */
    {
      int w = (int)*(int16_t *)0x4ead64;
      int h = (int)*(int16_t *)0x4ead66;
      unsigned int fmt =
        ((((unsigned int)(w * 4) >> 6) - 1) << 12 | (unsigned int)(h - 1))
          << 12 |
        (unsigned int)(w - 1);
      *(uint32_t *)0x4ead50 = fmt;
    }

    /* Set up D3D texture resource descriptor at 0x4ead40. */
    *(uint32_t *)0x4ead6c = 0;
    *(uint32_t *)0x4ead70 = 3; /* D3DFMT_LIN_X8R8G8B8 */
    *(uint32_t *)0x4ead74 = 4; /* bytes per pixel */
    *(uint8_t *)0x4ead68 = 0;
    *(uint32_t *)0x4ead78 = 0x4ead40; /* texture pointer */
    *(uint32_t *)0x4ead40 = 0x40001; /* D3D resource common */
    *(uint32_t *)0x4ead44 = 0;
    *(uint32_t *)0x4ead48 = 0;
    *(uint32_t *)0x4ead4c = 0x11e29; /* texture format */

    /* Register the D3D resource with the GPU. */
    D3DResource_Register((void *)0x4ead40, frame_buf);

    /* Initialize the render quad vertex data. */
    csmemset((void *)0x4ead98, 0, 0x8c);

    /* Set render scale factors to 1.0f. */
    *(uint32_t *)0x4eadd8 = 0x3f800000; /* 1.0f */
    *(uint32_t *)0x4eaddc = 0x3f800000; /* 1.0f */
    *(uint32_t *)0x4eadc0 = 0x3f800000; /* 1.0f */
    *(uint32_t *)0x4eadc4 = 0x3f800000; /* 1.0f */
    *(uint32_t *)0x4ead98 = 0;
    *(uint8_t *)0x4eae22 = 0;
    *(uint16_t *)0x4eae20 = 7;

    /* Set up a bitmap header for the bink frame texture. */
    *(uint32_t *)0x4ead10 = 0x6269746d; /* "bitm" tag */
    *(int16_t *)0x4ead14 = *(int16_t *)0x4ead64; /* width */
    *(int16_t *)0x4ead16 = *(int16_t *)0x4ead66; /* height */
    *(int16_t *)0x4ead18 = 1;
    *(int16_t *)0x4ead1a = 0;
    *(int16_t *)0x4ead1c = 10; /* bitmap format (a8r8g8b8) */
    *(int16_t *)0x4ead1e = 0x10;

    /* Calculate bitmap data size from bits-per-pixel. */
    bpp = bitmap_format_bits_per_pixel(10);
    bits_total =
      (int)bpp * (int)*(int16_t *)0x4ead16 * (int)*(int16_t *)0x4ead14;
    *(int *)0x4ead2c = (int)(bits_total + (bits_total >> 31 & 7)) >> 3;

    /* Set bitmap registration and hardware pointers. */
    *(int *)0x4ead30 = -1;
    *(int *)0x4ead34 = -1;
    *(int *)0x4ead3c = -1;
    *(uint32_t *)0x4ead38 = *(uint32_t *)0x4ead78;
    *(uint32_t *)0x4eada4 = 0x4ead10;

    /* Store flags and optionally suppress event manager. */
    *(uint32_t *)0x4ead5c = flags;
    if ((flags & 4) != 0) {
      bink_playback_trace("begin event_manager");
      event_manager_flush();
      event_manager_suppress(1);
      bink_playback_trace("end event_manager");
    }

    /* Decode and blit the first frame. */
    bink_playback_decode_frame();

    /* Save the pregame loading flag, then clear it and all counters. */
    *(uint8_t *)0x32eba0 = *(uint8_t *)0x31fa96;
    *(uint32_t *)0x4ead7c = 0;
    *(uint32_t *)0x4ead80 = 0;
    *(uint32_t *)0x4ead84 = 0;
    *(uint32_t *)0x4ead88 = 0;
    *(uint32_t *)0x4ead8c = 0;
    *(uint32_t *)0x4ead90 = 0;
    *(uint32_t *)0x4ead94 = 0;
    *(uint8_t *)0x31fa96 = 0;
    return;
  }

  /* BinkOpen failed - log error and release texture cache memory. */
  error(2, "### ERROR failed to open bink file '%s'", filename);
  bink_playback_release_texture_cache();
}

/* Update bink playback state (called once per frame outside rendering). */
void bink_playback_update(void)
{
  if (*(uint8_t *)0x31fa96 != 0)
    bink_playback_check_stop();
}

/* Check if a file is an AIFF or AIFC audio container.
 * Opens the file, reads the first 12-byte AIFF header chunk (FORM + size +
 * type), byte-swaps it via the aiff_container_chunk definition, then checks
 * that the chunk ID is 0x464f524d ('FORM') and the file type is either
 * 0x41494646 ('AIFF') or 0x41494643 ('AIFC'). Closes the file before
 * returning. Returns true if the file is a valid AIFF/AIFC container. */
bool FUN_001c6880(file_ref_t *info)
{
  int header[3];
  char result;
  char ok;

  result = 0;
  ok = file_open(info, 1);
  if (ok != '\0') {
    ok = file_read_from_position(info, 0, 0xc, header);
    if (ok != '\0') {
      FUN_00118be0((void *)0x32ebbc, header, 1);
      if ((header[0] == 0x464f524d) &&
          ((header[2] == 0x41494646) || (header[2] == 0x41494643))) {
        result = 1;
      }
    }
    file_close(info);
  }
  return result;
}
/* --- bink_playback.obj batch drafts (2026-07-26) --- */

/* FUN_001c4da0 (0x1c4da0) — XBE naked draft (batch 316). */
#if defined(__clang__)
static void (*const b1c4da0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1c4da0_exitfn)(int) = system_exit;
static void (*const b1c4da0_c1c3e40)(void) = FUN_001c3e40;
static void * (*const b1c4da0_c8de70)(char *destination, const char *source, size_t size) = csstrncpy;
static char * (*const b1c4da0_c1d9690)(const char *haystack, const char *needle) = crt_strstr;
static void (*const b1c4da0_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;

__attribute__((naked, noinline))
void FUN_001c4da0(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x208, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0xc(%%ebp), %%esi\n\t"
      "xorb %%bl, %%bl\n\t"
      "testl %%esi, %%esi\n\t"
      "pushl %%edi\n\t"
      "jne .LFUN_001c4da0_1\n\t"
      "pushl $1\n\t"
      "pushl $0x38d\n\t"
      "pushl $0x2ba8e8\n\t"
      "pushl $0x2bb8a0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001c4da0_1:\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "movb $0, (%%esi)\n\t"
      "je .LFUN_001c4da0_9\n\t"
      "movzbl %%ah, %%ebx\n\t"
      "sarl $0x10, %%eax\n\t"
      "andl $0xfff, %%eax\n\t"
      "testl %%ebx, %%ebx\n\t"
      "movl %%eax, %%edi\n\t"
      "je .LFUN_001c4da0_2\n\t"
      "pushl $1\n\t"
      "pushl $0x397\n\t"
      "pushl $0x2ba8e8\n\t"
      "pushl $0x2ba8c0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "testl %%ebx, %%ebx\n\t"
      "jl .LFUN_001c4da0_8\n\t"
      ".LFUN_001c4da0_2:\n\t"
      "cmpl $9, %%ebx\n\t"
      "jge .LFUN_001c4da0_8\n\t"
      "testl %%edi, %%edi\n\t"
      "jl .LFUN_001c4da0_8\n\t"
      "cmpl $0x64, %%edi\n\t"
      "jge .LFUN_001c4da0_8\n\t"
      "leal -0x208(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl %%ebx, %%eax\n\t"
      "call *%[c1c3e40]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001c4da0_7\n\t"
      "movw -0x8(%%ebp), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "jne .LFUN_001c4da0_4\n\t"
      "movl $0x2bb788, %%edi\n\t"
      ".LFUN_001c4da0_3:\n\t"
      "pushl $0xff\n\t"
      "leal -0x208(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "call *%[c8de70]\n\t"
      "pushl %%edi\n\t"
      "pushl %%esi\n\t"
      "movb $0, 0xff(%%esi)\n\t"
      "call *%[c1d9690]\n\t"
      "addl $0x14, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_001c4da0_6\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb $0, (%%eax)\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001c4da0_4:\n\t"
      "cmpw $1, %%ax\n\t"
      "jne .LFUN_001c4da0_5\n\t"
      "movl $0x2bb794, %%edi\n\t"
      "jmp .LFUN_001c4da0_3\n\t"
      ".LFUN_001c4da0_5:\n\t"
      "pushl $0x2bb880\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001c4da0_6:\n\t"
      "pushl $0x2bb84c\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "popl %%edi\n\t"
      "movb $0, (%%esi)\n\t"
      "popl %%esi\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001c4da0_7:\n\t"
      "pushl $0x2bb800\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001c4da0_8:\n\t"
      "pushl $0x2bb430\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001c4da0_9:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b1c4da0_assert), [exitfn] "m"(b1c4da0_exitfn), [c1c3e40] "m"(b1c4da0_c1c3e40), [c8de70] "m"(b1c4da0_c8de70), [c1d9690] "m"(b1c4da0_c1d9690), [c8f390] "m"(b1c4da0_c8f390)
      : "memory");
}
#else
#error "FUN_001c4da0: clang naked draft required"
#endif


/* FUN_001c4f30 (0x1c4f30) — XBE naked draft (batch 344). */
#if defined(__clang__)
static void (*const b1c4f30_c1c3250)(void) = FUN_001c3250;
static char * (*const b1c4f30_c19f3a0)(const wchar_t *unicode, char *ascii, int size) = wide_to_ascii;
static void (*const b1c4f30_c1d3254)(void) = FUN_001d3254;
static void (*const b1c4f30_c1d3185)(void) = FUN_001d3185;
static void (*const b1c4f30_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;
static void (*const b1c4f30_c1d335b)(void) = FUN_001d335b;
static void __stdcall (*const b1c4f30_c1d33a2)(int param_1) = (void *)FUN_001d33a2;
static void (*const b1c4f30_c1c3a30)(void) = FUN_001c3a30;
static void (*const b1c4f30_c1c3c40)(void) = FUN_001c3c40;
static void (*const b1c4f30_c1c3320)(void) = FUN_001c3320;

__attribute__((naked, noinline))
void FUN_001c4f30(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x34c, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "pushl %%edi\n\t"
      "xorl %%esi, %%esi\n\t"
      ".LFUN_001c4f30_1:\n\t"
      "movl %%esi, %%eax\n\t"
      "call *%[c1c3250]\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001c4f30_7\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LFUN_001c4f30_6\n\t"
      "xorl %%eax, %%eax\n\t"
      "movl %%eax, -0x7(%%ebp)\n\t"
      "leal -0x34c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movw %%ax, -0x3(%%ebp)\n\t"
      "pushl $8\n\t"
      "leal -0x8(%%ebp), %%edx\n\t"
      "movb %%al, -0x1(%%ebp)\n\t"
      "movl 0x32eb94, %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "movb $0, -0x8(%%ebp)\n\t"
      "call *%[c19f3a0]\n\t"
      "addl $0xc, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d3254]\n\t"
      "movl %%eax, %%edi\n\t"
      "cmpl $-1, %%edi\n\t"
      "je .LFUN_001c4f30_5\n\t"
      "nop\n\t"
      ".LFUN_001c4f30_2:\n\t"
      "cmpl $0x64, %%ebx\n\t"
      "jge .LFUN_001c4f30_4\n\t"
      "leal -0x108(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x8(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c1d3185]\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_001c4f30_3\n\t"
      "pushl $0x2bb8ac\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_001c4f30_3:\n\t"
      "leal -0x34c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d335b]\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_001c4f30_2\n\t"
      ".LFUN_001c4f30_4:\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d33a2]\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_001c4f30_5\n\t"
      "pushl $0x2ba984\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_001c4f30_5:\n\t"
      "call *%[c1c3a30]\n\t"
      "movl %%eax, %%edi\n\t"
      "call *%[c1c3c40]\n\t"
      "addl %%edi, %%eax\n\t"
      "movswl %%ax, %%ecx\n\t"
      "addl %%ecx, %%ebx\n\t"
      ".LFUN_001c4f30_6:\n\t"
      "call *%[c1c3320]\n\t"
      ".LFUN_001c4f30_7:\n\t"
      "incl %%esi\n\t"
      "je .LFUN_001c4f30_1\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c1c3250] "m"(b1c4f30_c1c3250), [c19f3a0] "m"(b1c4f30_c19f3a0), [c1d3254] "m"(b1c4f30_c1d3254), [c1d3185] "m"(b1c4f30_c1d3185), [c8f390] "m"(b1c4f30_c8f390), [c1d335b] "m"(b1c4f30_c1d335b), [c1d33a2] "m"(b1c4f30_c1d33a2), [c1c3a30] "m"(b1c4f30_c1c3a30), [c1c3c40] "m"(b1c4f30_c1c3c40), [c1c3320] "m"(b1c4f30_c1c3320)
      : "memory");
}
#else
#error "FUN_001c4f30: clang naked draft required"
#endif


/* FUN_001c5010 (0x1c5010) — XBE naked draft (batch 356). */
#if defined(__clang__)
static bool (*const b1c5010_c81870)(int *mutex_reference, int timeout_ms) = (void *)take_mutex;
static void (*const b1c5010_c1c3250)(void) = (void *)FUN_001c3250;
static char * (*const b1c5010_c19f3a0)(const wchar_t *unicode, char *ascii, int size) = (void *)wide_to_ascii;
static void (*const b1c5010_c1d3254)(void) = (void *)FUN_001d3254;
static int (*const b1c5010_c1d9179)(char *str, size_t size, const char *format, ...) = (void *)snprintf;
static file_ref_t * (*const b1c5010_c1999f0)(file_ref_t *info, const char *directory, bool a4) = (void *)file_reference_create_from_path;
static bool (*const b1c5010_c19a640)(file_ref_t *info) = (void *)file_exists;
static wchar_t * (*const b1c5010_c19dc90)(wchar_t *dest, wchar_t *src, size_t count) = (void *)ustrncpy;
static bool (*const b1c5010_c19a7a0)(file_ref_t *info, int flags) = (void *)file_open;
static bool (*const b1c5010_c19ab50)(file_ref_t *info, int size, void *buffer) = (void *)file_read;
static void (*const b1c5010_c1c3160)(void) = (void *)saved_game_file_generate_checksum;
static int (*const b1c5010_c8da40)(const void *a, const void *b, int size) = (void *)csmemcmp;
static void (*const b1c5010_c19e9f0)(wchar_t *buffer, int buffer_size, const wchar_t *format, ...) = (void *)unicode_sprintf;
static void (*const b1c5010_c8f390)(unsigned __int16 a1, const char *a2, ...) = (void *)error;
static void (*const b1c5010_c1190b0)(uint32_t *checksum) = (void *)crc_new;
static void (*const b1c5010_c119100)(uint32_t *checksum, void *data, int size) = (void *)crc_checksum_buffer;
static void * (*const b1c5010_c8e0b0)(void *destination, void *source, size_t size) = (void *)csmemcpy;
static bool (*const b1c5010_c19aa00)(file_ref_t *info, int offset) = (void *)file_set_position;
static void (*const b1c5010_c19ac00)(void) = (void *)file_write;
static bool (*const b1c5010_c19a930)(file_ref_t *info) = (void *)file_close;
static void (*const b1c5010_c1c33b0)(void) = (void *)FUN_001c33b0;
static void (*const b1c5010_c1d335b)(void) = (void *)FUN_001d335b;
static void __stdcall (*const b1c5010_c1d33a2)(int param_1) = (void *)FUN_001d33a2;
static void (*const b1c5010_c1c3a30)(void) = (void *)FUN_001c3a30;
static void (*const b1c5010_c1c3c40)(void) = (void *)FUN_001c3c40;
static void (*const b1c5010_c1c3320)(void) = (void *)FUN_001c3320;
static void (*const b1c5010_c818d0)(int *mutex_reference) = (void *)release_mutex;

__attribute__((naked, noinline))
void FUN_001c5010(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xa84, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "pushl %%edi\n\t"
      "xorl %%edi, %%edi\n\t"
      "movl %%edi, -0x8(%%ebp)\n\t"
      "movl %%ebx, -0x4(%%ebp)\n\t"
      "jmp .LFUN_001c5010_1\n\t"
      "leal (%%esp), %%esp\n\t"
      "nop\n\t"
      ".LFUN_001c5010_1:\n\t"
      "movl 0x4eacbc, %%eax\n\t"
      "pushl $0x36ee80\n\t"
      "pushl %%eax\n\t"
      "call *%[c81870]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001c5010_18\n\t"
      "movl %%edi, %%eax\n\t"
      "call *%[c1c3250]\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001c5010_17\n\t"
      "cmpl %%ebx, %%edi\n\t"
      "jne .LFUN_001c5010_16\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movl %%ecx, -0x17(%%ebp)\n\t"
      "leal -0x884(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movw %%cx, -0x13(%%ebp)\n\t"
      "pushl $8\n\t"
      "leal -0x18(%%ebp), %%eax\n\t"
      "movb %%cl, -0x11(%%ebp)\n\t"
      "movl 0x32eb94, %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "movb %%bl, -0x18(%%ebp)\n\t"
      "call *%[c19f3a0]\n\t"
      "addl $0xc, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d3254]\n\t"
      "movl %%eax, %%esi\n\t"
      "cmpl $-1, %%esi\n\t"
      "movl %%esi, -0x10(%%ebp)\n\t"
      "je .LFUN_001c5010_15\n\t"
      ".LFUN_001c5010_2:\n\t"
      "cmpl $0x64, -0x4(%%ebp)\n\t"
      "jge .LFUN_001c5010_13\n\t"
      "xorl %%eax, %%eax\n\t"
      "movb %%bl, -0x340(%%ebp)\n\t"
      "movl $0x81, %%ecx\n\t"
      "leal -0x33f(%%ebp), %%edi\n\t"
      "rep stosl\n\t"
      "pushl $0x2bb788\n\t"
      "leal -0x744(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x25bf84\n\t"
      ".byte 0xaa\n\t"
      "leal -0x340(%%ebp), %%eax\n\t"
      "pushl $0xff\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d9179]\n\t"
      "addl $0x14, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jle .LFUN_001c5010_4\n\t"
      "pushl %%ebx\n\t"
      "leal -0x340(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x138(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c1999f0]\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_001c5010_4\n\t"
      "leal -0x138(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c19a640]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001c5010_4\n\t"
      "movw %%bx, -0x140(%%ebp)\n\t"
      "movl $0x30, %%esi\n\t"
      ".LFUN_001c5010_3:\n\t"
      "pushl $0x7f\n\t"
      "leal -0x640(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x240(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c19dc90]\n\t"
      "leal -0x138(%%ebp), %%ecx\n\t"
      "pushl $3\n\t"
      "pushl %%ecx\n\t"
      "movw %%bx, -0x142(%%ebp)\n\t"
      "call *%[c19a7a0]\n\t"
      "addl $0x14, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001c5010_9\n\t"
      "leal -0x540(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x138(%%ebp), %%eax\n\t"
      "pushl $0x200\n\t"
      "pushl %%eax\n\t"
      "call *%[c19ab50]\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001c5010_7\n\t"
      "leal -0x2c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x540(%%ebp), %%edx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edx\n\t"
      "call *%[c1c3160]\n\t"
      "movzwl %%si, %%edi\n\t"
      "pushl $0x14\n\t"
      "leal -0x540(%%ebp,%%edi,1), %%esi\n\t"
      "leal -0x2c(%%ebp), %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "call *%[c8da40]\n\t"
      "addl $0x18, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_001c5010_6\n\t"
      "movb $1, -0x13b(%%ebp)\n\t"
      "jmp .LFUN_001c5010_8\n\t"
      ".LFUN_001c5010_4:\n\t"
      "pushl $0x2bb794\n\t"
      "leal -0x744(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x25bf84\n\t"
      "leal -0x340(%%ebp), %%edx\n\t"
      "pushl $0xff\n\t"
      "pushl %%edx\n\t"
      "call *%[c1d9179]\n\t"
      "addl $0x14, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jle .LFUN_001c5010_5\n\t"
      "pushl %%ebx\n\t"
      "leal -0x340(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x138(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1999f0]\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_001c5010_5\n\t"
      "leal -0x138(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c19a640]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001c5010_5\n\t"
      "movw $1, -0x140(%%ebp)\n\t"
      "movl $0x68, %%esi\n\t"
      "jmp .LFUN_001c5010_3\n\t"
      ".LFUN_001c5010_5:\n\t"
      "leal -0x858(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x640(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x2bb9d0\n\t"
      "leal -0xa84(%%ebp), %%edx\n\t"
      "pushl $0xff\n\t"
      "pushl %%edx\n\t"
      "call *%[c19e9f0]\n\t"
      "pushl $0x200\n\t"
      "leal -0xa84(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0xa84(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movw %%bx, -0x886(%%ebp)\n\t"
      "call *%[c19f3a0]\n\t"
      "pushl %%eax\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $0x28, %%esp\n\t"
      "movw $0xffff, -0x140(%%ebp)\n\t"
      "jmp .LFUN_001c5010_12\n\t"
      ".LFUN_001c5010_6:\n\t"
      "leal -0x340(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x2bb000\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "leal -0xc(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c1190b0]\n\t"
      "pushl %%edi\n\t"
      "leal -0x540(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0xc(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c119100]\n\t"
      "pushl $4\n\t"
      "leal -0xc(%%ebp), %%edx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edx\n\t"
      "call *%[c8da40]\n\t"
      "addl $0x28, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_001c5010_8\n\t"
      "leal -0x340(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x2bb980\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "pushl $0x14\n\t"
      "leal -0x2c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "call *%[c8e0b0]\n\t"
      "leal -0x138(%%ebp), %%edx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edx\n\t"
      "call *%[c19aa00]\n\t"
      "addl $0x20, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001c5010_8\n\t"
      "leal -0x540(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x138(%%ebp), %%ecx\n\t"
      "pushl $0x200\n\t"
      "pushl %%ecx\n\t"
      "call *%[c19ac00]\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001c5010_8\n\t"
      "movb $1, -0x13b(%%ebp)\n\t"
      "jmp .LFUN_001c5010_8\n\t"
      ".LFUN_001c5010_7:\n\t"
      "pushl $0x2bb948\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_001c5010_8:\n\t"
      "leal -0x138(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c19a930]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_001c5010_11\n\t"
      "pushl $0x2bb90c\n\t"
      "jmp .LFUN_001c5010_10\n\t"
      ".LFUN_001c5010_9:\n\t"
      "pushl $0x2bb8d8\n\t"
      ".LFUN_001c5010_10:\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_001c5010_11:\n\t"
      "leal -0x340(%%ebp), %%esi\n\t"
      "call *%[c1c33b0]\n\t"
      "testb %%al, %%al\n\t"
      "movl -0x10(%%ebp), %%esi\n\t"
      "je .LFUN_001c5010_13\n\t"
      "incl -0x4(%%ebp)\n\t"
      ".LFUN_001c5010_12:\n\t"
      "leal -0x884(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[c1d335b]\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_001c5010_2\n\t"
      ".LFUN_001c5010_13:\n\t"
      "pushl %%esi\n\t"
      "call *%[c1d33a2]\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_001c5010_14\n\t"
      "pushl $0x2ba984\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_001c5010_14:\n\t"
      "movl -0x8(%%ebp), %%edi\n\t"
      ".LFUN_001c5010_15:\n\t"
      "call *%[c1c3a30]\n\t"
      "movl %%eax, %%esi\n\t"
      "call *%[c1c3c40]\n\t"
      "addl %%esi, %%eax\n\t"
      "movswl %%ax, %%ecx\n\t"
      "addl %%ecx, -0x4(%%ebp)\n\t"
      ".LFUN_001c5010_16:\n\t"
      "movl %%edi, %%esi\n\t"
      "call *%[c1c3320]\n\t"
      ".LFUN_001c5010_17:\n\t"
      "movl 0x4eacbc, %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c818d0]\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_001c5010_18:\n\t"
      "incl %%edi\n\t"
      "movl %%edi, -0x8(%%ebp)\n\t"
      "je .LFUN_001c5010_1\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb %%bl, 0x4eacc7\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c81870] "m"(b1c5010_c81870), [c1c3250] "m"(b1c5010_c1c3250), [c19f3a0] "m"(b1c5010_c19f3a0), [c1d3254] "m"(b1c5010_c1d3254), [c1d9179] "m"(b1c5010_c1d9179), [c1999f0] "m"(b1c5010_c1999f0), [c19a640] "m"(b1c5010_c19a640), [c19dc90] "m"(b1c5010_c19dc90), [c19a7a0] "m"(b1c5010_c19a7a0), [c19ab50] "m"(b1c5010_c19ab50), [c1c3160] "m"(b1c5010_c1c3160), [c8da40] "m"(b1c5010_c8da40), [c19e9f0] "m"(b1c5010_c19e9f0), [c8f390] "m"(b1c5010_c8f390), [c1190b0] "m"(b1c5010_c1190b0), [c119100] "m"(b1c5010_c119100), [c8e0b0] "m"(b1c5010_c8e0b0), [c19aa00] "m"(b1c5010_c19aa00), [c19ac00] "m"(b1c5010_c19ac00), [c19a930] "m"(b1c5010_c19a930), [c1c33b0] "m"(b1c5010_c1c33b0), [c1d335b] "m"(b1c5010_c1d335b), [c1d33a2] "m"(b1c5010_c1d33a2), [c1c3a30] "m"(b1c5010_c1c3a30), [c1c3c40] "m"(b1c5010_c1c3c40), [c1c3320] "m"(b1c5010_c1c3320), [c818d0] "m"(b1c5010_c818d0)
      : "memory");
}
#else
#error "FUN_001c5010: clang naked draft required"
#endif


/* FUN_001c53f0 (0x1c53f0) — XBE naked draft (batch 318). */
#if defined(__clang__)
static void (*const b1c53f0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1c53f0_exitfn)(int) = system_exit;
static bool (*const b1c53f0_c81870)(int *mutex_reference, int timeout_ms) = take_mutex;
static void (*const b1c53f0_c1c5010)(void) = FUN_001c5010;
static void (*const b1c53f0_c1c3610)(void) = FUN_001c3610;
static void (*const b1c53f0_c1c3430)(void) = FUN_001c3430;
static void (*const b1c53f0_c1c35a0)(void) = FUN_001c35a0;
static void (*const b1c53f0_c1c3710)(void) = FUN_001c3710;
static void (*const b1c53f0_c1c3500)(void) = FUN_001c3500;
static void (*const b1c53f0_c818d0)(int *mutex_reference) = release_mutex;
static void (*const b1c53f0_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;

__attribute__((naked, noinline))
void FUN_001c53f0(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x20c, %%esp\n\t"
      "movw 0x8(%%ebp), %%ax\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .LFUN_001c53f0_1\n\t"
      "testw %%ax, %%ax\n\t"
      "jl .LFUN_001c53f0_2\n\t"
      "cmpw $4, %%ax\n\t"
      "jge .LFUN_001c53f0_2\n\t"
      ".LFUN_001c53f0_1:\n\t"
      "cmpw $2, 0xc(%%ebp)\n\t"
      "jae .LFUN_001c53f0_2\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_001c53f0_2\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_001c53f0_3\n\t"
      ".LFUN_001c53f0_2:\n\t"
      "pushl $1\n\t"
      "pushl $0xec\n\t"
      "pushl $0x2ba8e8\n\t"
      "pushl $0x2bba90\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001c53f0_3:\n\t"
      "movl 0x4eacbc, %%eax\n\t"
      "pushl $0x36ee80\n\t"
      "pushl %%eax\n\t"
      "call *%[c81870]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001c53f0_12\n\t"
      "movb 0x4eacc7, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001c53f0_4\n\t"
      "call *%[c1c5010]\n\t"
      ".LFUN_001c53f0_4:\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "xorl %%esi, %%esi\n\t"
      "call *%[c1c3610]\n\t"
      "movl 0x4eacc0, %%ecx\n\t"
      "pushl $0x36ee80\n\t"
      "pushl %%ecx\n\t"
      "movl %%eax, 0x8(%%ebp)\n\t"
      "xorl %%edi, %%edi\n\t"
      "call *%[c81870]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001c53f0_10\n\t"
      "xorl %%eax, %%eax\n\t"
      "call *%[c1c3430]\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001c53f0_9\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "pushl %%ebx\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "cmpw %%bx, (%%edx)\n\t"
      "jbe .LFUN_001c53f0_8\n\t"
      ".LFUN_001c53f0_5:\n\t"
      "cmpl 0x8(%%ebp), %%ebx\n\t"
      "jge .LFUN_001c53f0_8\n\t"
      "leal -0x20c(%%ebp), %%esi\n\t"
      "call *%[c1c35a0]\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001c53f0_8\n\t"
      "movzwl 0xc(%%ebp), %%edx\n\t"
      "movswl -0xc(%%ebp), %%eax\n\t"
      "cmpl %%edx, %%eax\n\t"
      "jne .LFUN_001c53f0_7\n\t"
      "cmpb $1, 0x18(%%ebp)\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "je .LFUN_001c53f0_6\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_001c53f0_7\n\t"
      ".LFUN_001c53f0_6:\n\t"
      "movl -0x7(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "movl %%ebx, %%eax\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "call *%[c1c3710]\n\t"
      "movl 0x14(%%ebp), %%edx\n\t"
      "addl $8, %%esp\n\t"
      "movl %%eax, (%%edx,%%edi,4)\n\t"
      "incl %%edi\n\t"
      ".LFUN_001c53f0_7:\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "movzwl (%%eax), %%ecx\n\t"
      "incl %%ebx\n\t"
      "cmpl %%ecx, %%edi\n\t"
      "jl .LFUN_001c53f0_5\n\t"
      ".LFUN_001c53f0_8:\n\t"
      "xorl %%esi, %%esi\n\t"
      "call *%[c1c3500]\n\t"
      "popl %%ebx\n\t"
      ".LFUN_001c53f0_9:\n\t"
      "movl 0x4eacc0, %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c818d0]\n\t"
      "addl $4, %%esp\n\t"
      "jmp .LFUN_001c53f0_11\n\t"
      ".LFUN_001c53f0_10:\n\t"
      "pushl $0x2bae8c\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_001c53f0_11:\n\t"
      "movl 0x4eacbc, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c818d0]\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "addl $4, %%esp\n\t"
      "movw %%di, (%%ecx)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001c53f0_12:\n\t"
      "pushl $0x2bba64\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "movw 0x8(%%ebp), %%dx\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "movw %%dx, (%%eax)\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b1c53f0_assert), [exitfn] "m"(b1c53f0_exitfn), [c81870] "m"(b1c53f0_c81870), [c1c5010] "m"(b1c53f0_c1c5010), [c1c3610] "m"(b1c53f0_c1c3610), [c1c3430] "m"(b1c53f0_c1c3430), [c1c35a0] "m"(b1c53f0_c1c35a0), [c1c3710] "m"(b1c53f0_c1c3710), [c1c3500] "m"(b1c53f0_c1c3500), [c818d0] "m"(b1c53f0_c818d0), [c8f390] "m"(b1c53f0_c8f390)
      : "memory");
}
#else
#error "FUN_001c53f0: clang naked draft required"
#endif


/* FUN_001c5560 (0x1c5560) — XBE naked draft (batch 303). */
#if defined(__clang__)
static void (*const b1c5560_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1c5560_exitfn)(int) = system_exit;
static void (*const b1c5560_c1c5010)(void) = FUN_001c5010;
static void (*const b1c5560_c1c2b20)(void) = saved_game_perform_file_system_checks;
static void (*const b1c5560_ce4590)(int16_t error_handle, char flag) = display_error_abort_to_dashboard_deferred;
static void (*const b1c5560_c1c3610)(void) = FUN_001c3610;
static char * (*const b1c5560_c19f3a0)(const wchar_t *unicode, char *ascii, int size) = wide_to_ascii;
static void (*const b1c5560_c1d2f22)(void) = FUN_001d2f22;
static wchar_t * (*const b1c5560_c19dc90)(wchar_t *dest, wchar_t *src, size_t count) = ustrncpy;
static int (*const b1c5560_c1d9179)(char *str, size_t size, const char *format, ...) = snprintf;
static void (*const b1c5560_c1c0cd0)(int param_1) = FUN_001c0cd0;
static file_ref_t * (*const b1c5560_c1999f0)(file_ref_t *info, const char *directory, bool a4) = file_reference_create_from_path;
static bool (*const b1c5560_c19a490)(file_ref_t *info) = FUN_0019a490;
static bool (*const b1c5560_c19a7a0)(file_ref_t *info, int flags) = file_open;
static void *(*const b1c5560_memset)(void *, int, unsigned int) = csmemset;
static void (*const b1c5560_c1c3160)(void) = saved_game_file_generate_checksum;
static void (*const b1c5560_c19ac00)(void) = file_write;
static bool (*const b1c5560_c19a930)(file_ref_t *info) = file_close;
static void (*const b1c5560_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;
static void (*const b1c5560_c1c4210)(void) = FUN_001c4210;
static void (*const b1c5560_c1c3710)(void) = FUN_001c3710;
static void (*const b1c5560_c1d3185)(void) = FUN_001d3185;
static void (*const b1c5560_ce4500)(int16_t error_handle, int16_t local_player_index, char a3, char a4) = display_error_deferred;

__attribute__((naked, noinline))
void FUN_001c5560(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x620, %%esp\n\t"
      "pushl %%ebx\n\t"
      "movw 0x8(%%ebp), %%bx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "orl $0xffffffff, %%edi\n\t"
      "cmpw $2, %%bx\n\t"
      "jae .LFUN_001c5560_2\n\t"
      "movw 0xc(%%ebp), %%ax\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .LFUN_001c5560_1\n\t"
      "cmpw $4, %%ax\n\t"
      "jge .LFUN_001c5560_2\n\t"
      ".LFUN_001c5560_1:\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_001c5560_3\n\t"
      ".LFUN_001c5560_2:\n\t"
      "pushl $1\n\t"
      "pushl $0x14c\n\t"
      "pushl $0x2ba8e8\n\t"
      "pushl $0x2bbd20\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001c5560_3:\n\t"
      "movb 0x4eacc7, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001c5560_4\n\t"
      "call *%[c1c5010]\n\t"
      ".LFUN_001c5560_4:\n\t"
      "call *%[c1c2b20]\n\t"
      "movl %%eax, %%esi\n\t"
      "movswl %%si, %%eax\n\t"
      "decl %%eax\n\t"
      "je .LFUN_001c5560_5\n\t"
      "decl %%eax\n\t"
      "jne .LFUN_001c5560_7\n\t"
      "pushl $1\n\t"
      "pushl $0x22\n\t"
      "jmp .LFUN_001c5560_6\n\t"
      ".LFUN_001c5560_5:\n\t"
      "pushl $1\n\t"
      "pushl $0x21\n\t"
      ".LFUN_001c5560_6:\n\t"
      "call *%[ce4590]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_001c5560_7:\n\t"
      "testw %%si, %%si\n\t"
      "jne .LFUN_001c5560_22\n\t"
      "xorl %%esi, %%esi\n\t"
      "call *%[c1c3610]\n\t"
      "movl %%eax, %%esi\n\t"
      "cmpl $0x64, %%esi\n\t"
      "jge .LFUN_001c5560_21\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "xorl %%eax, %%eax\n\t"
      "movl %%eax, -0x7(%%ebp)\n\t"
      "movw %%ax, -0x3(%%ebp)\n\t"
      "movb %%al, -0x314(%%ebp)\n\t"
      "movb %%al, -0x1(%%ebp)\n\t"
      "pushl $0x100\n\t"
      "movl $0x3f, %%ecx\n\t"
      "leal -0x313(%%ebp), %%edi\n\t"
      "movb $0, -0x8(%%ebp)\n\t"
      "rep stosl\n\t"
      "leal -0x314(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl 0x32eb94, %%ecx\n\t"
      "pushl $0\n\t"
      "stosw\n\t"
      "pushl $1\n\t"
      "pushl %%edx\n\t"
      ".byte 0xaa\n\t"
      "pushl $8\n\t"
      "leal -0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c19f3a0]\n\t"
      "addl $0xc, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d2f22]\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_001c5560_20\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "movb %%al, -0x214(%%ebp)\n\t"
      "movl $0x81, %%ecx\n\t"
      "leal -0x213(%%ebp), %%edi\n\t"
      "rep stosl\n\t"
      "pushl $0x7f\n\t"
      ".byte 0xaa\n\t"
      "pushl %%edx\n\t"
      "leal -0x114(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c19dc90]\n\t"
      "movw %%bx, -0x14(%%ebp)\n\t"
      "movzwl %%bx, %%ebx\n\t"
      "movl %%ebx, %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "subl $0, %%eax\n\t"
      "movw $0, -0x16(%%ebp)\n\t"
      "movw %%si, -0x12(%%ebp)\n\t"
      "movb $0, -0x10(%%ebp)\n\t"
      "movb $0, -0xf(%%ebp)\n\t"
      "je .LFUN_001c5560_9\n\t"
      "decl %%eax\n\t"
      "je .LFUN_001c5560_8\n\t"
      "movw $0xffff, -0x14(%%ebp)\n\t"
      "jmp .LFUN_001c5560_18\n\t"
      ".LFUN_001c5560_8:\n\t"
      "pushl $0x2bb794\n\t"
      "leal -0x314(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x25bf84\n\t"
      "leal -0x214(%%ebp), %%edx\n\t"
      "pushl $0xff\n\t"
      "pushl %%edx\n\t"
      "call *%[c1d9179]\n\t"
      "addl $0x14, %%esp\n\t"
      "movl $0x68, %%edi\n\t"
      "jmp .LFUN_001c5560_10\n\t"
      ".LFUN_001c5560_9:\n\t"
      "pushl $0x2bb788\n\t"
      "leal -0x314(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x25bf84\n\t"
      "leal -0x214(%%ebp), %%ecx\n\t"
      "pushl $0xff\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1d9179]\n\t"
      "leal -0x314(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl $0x30, %%edi\n\t"
      "call *%[c1c0cd0]\n\t"
      "addl $0x18, %%esp\n\t"
      ".LFUN_001c5560_10:\n\t"
      "cmpw $-1, -0x14(%%ebp)\n\t"
      "je .LFUN_001c5560_18\n\t"
      "pushl $0\n\t"
      "leal -0x214(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x420(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1999f0]\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_001c5560_17\n\t"
      "leal -0x420(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c19a490]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001c5560_17\n\t"
      "leal -0x420(%%ebp), %%eax\n\t"
      "pushl $2\n\t"
      "pushl %%eax\n\t"
      "call *%[c19a7a0]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001c5560_12\n\t"
      "pushl $0x200\n\t"
      "leal -0x620(%%ebp), %%ecx\n\t"
      "pushl $0\n\t"
      "pushl %%ecx\n\t"
      "call *%[memset]\n\t"
      "movzwl %%di, %%edx\n\t"
      "leal -0x620(%%ebp,%%edx,1), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x620(%%ebp), %%ecx\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1c3160]\n\t"
      "leal -0x620(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x420(%%ebp), %%eax\n\t"
      "pushl $0x200\n\t"
      "pushl %%eax\n\t"
      "call *%[c19ac00]\n\t"
      "addl $0x24, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001c5560_11\n\t"
      "movb $1, -0xf(%%ebp)\n\t"
      ".LFUN_001c5560_11:\n\t"
      "leal -0x420(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c19a930]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_001c5560_14\n\t"
      "pushl $0x2bbce4\n\t"
      "jmp .LFUN_001c5560_13\n\t"
      ".LFUN_001c5560_12:\n\t"
      "pushl $0x2bbcb0\n\t"
      ".LFUN_001c5560_13:\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_001c5560_14:\n\t"
      "leal 0x8(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x214(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "xorl %%eax, %%eax\n\t"
      "call *%[c1c4210]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001c5560_16\n\t"
      "movswl -0x12(%%ebp), %%ecx\n\t"
      "cmpl %%ecx, 0x8(%%ebp)\n\t"
      "je .LFUN_001c5560_15\n\t"
      "pushl $1\n\t"
      "pushl $0x1b2\n\t"
      "pushl $0x2ba8e8\n\t"
      "pushl $0x2bbc94\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001c5560_15:\n\t"
      "movl -0xf(%%ebp), %%edx\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "movswl -0x12(%%ebp), %%eax\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movl %%ebx, %%edx\n\t"
      "call *%[c1c3710]\n\t"
      "addl $8, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001c5560_16:\n\t"
      "pushl $0x2bbc50\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "jmp .LFUN_001c5560_18\n\t"
      ".LFUN_001c5560_17:\n\t"
      "leal -0x214(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x2bbc20\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_001c5560_18:\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "movl 0x32eb94, %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl $8\n\t"
      "leal -0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c19f3a0]\n\t"
      "addl $0xc, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d3185]\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_001c5560_19\n\t"
      "pushl $0x2bb55c\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_001c5560_19:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "orl $0xffffffff, %%eax\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001c5560_20:\n\t"
      "pushl $0x2bbbd8\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "orl $0xffffffff, %%eax\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001c5560_21:\n\t"
      "pushl $0x2bbb60\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "pushl $0\n\t"
      "pushl $1\n\t"
      "pushl $-1\n\t"
      "pushl $0x24\n\t"
      "call *%[ce4500]\n\t"
      "addl $0x18, %%esp\n\t"
      ".LFUN_001c5560_22:\n\t"
      "movl %%edi, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b1c5560_assert), [exitfn] "m"(b1c5560_exitfn), [c1c5010] "m"(b1c5560_c1c5010), [c1c2b20] "m"(b1c5560_c1c2b20), [ce4590] "m"(b1c5560_ce4590), [c1c3610] "m"(b1c5560_c1c3610), [c19f3a0] "m"(b1c5560_c19f3a0), [c1d2f22] "m"(b1c5560_c1d2f22), [c19dc90] "m"(b1c5560_c19dc90), [c1d9179] "m"(b1c5560_c1d9179), [c1c0cd0] "m"(b1c5560_c1c0cd0), [c1999f0] "m"(b1c5560_c1999f0), [c19a490] "m"(b1c5560_c19a490), [c19a7a0] "m"(b1c5560_c19a7a0), [memset] "m"(b1c5560_memset), [c1c3160] "m"(b1c5560_c1c3160), [c19ac00] "m"(b1c5560_c19ac00), [c19a930] "m"(b1c5560_c19a930), [c8f390] "m"(b1c5560_c8f390), [c1c4210] "m"(b1c5560_c1c4210), [c1c3710] "m"(b1c5560_c1c3710), [c1d3185] "m"(b1c5560_c1d3185), [ce4500] "m"(b1c5560_ce4500)
      : "memory");
}
#else
#error "FUN_001c5560: clang naked draft required"
#endif


/* 0x1c58f0 */
void FUN_001c58f0(void)
{
  int eax = 0;
  int ebx = 0;
  int edi = 0;

  take_mutex((void *)(uintptr_t)eax, 0x0036ee80);
  /* test (char)eax, (char)eax -> je 0x1c53cf */
  FUN_001c3250();
  /* test (char)eax, (char)eax -> je 0x1c53c0 */
  /* cmp edi, ebx -> jne 0x1c53b9 */

  (void)eax;
  (void)ebx;
  (void)edi;
}

/* FUN_001c5ab0 (0x1c5ab0) — XBE naked draft (batch 331). */
#if defined(__clang__)
static void *(*const b1c5ab0_memset)(void *, int, unsigned int) = csmemset;
static void __stdcall (*const b1c5ab0_c1d0da1)(void *status) = (void *)xbox_query_global_memory_status;
static bool (*const b1c5ab0_c1c5a80)(void) = bink_memory_pool_is_empty;
static void (*const b1c5ab0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1c5ab0_exitfn)(int) = system_exit;
static void __stdcall (*const b1c5ab0_c1d371d)(void *addr, unsigned int size, unsigned int protect) = (void *)physical_memory_protect;
static char * (*const b1c5ab0_c8d9d0)(char *buffer, const char *format, ...) = csprintf;

__attribute__((naked, noinline))
void FUN_001c5ab0(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x20, %%esp\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl $0x20\n\t"
      "xorl %%esi, %%esi\n\t"
      "leal -0x20(%%ebp), %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "call *%[memset]\n\t"
      "addl $0xc, %%esp\n\t"
      "leal -0x20(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl $0x20, -0x20(%%ebp)\n\t"
      "call *%[c1d0da1]\n\t"
      "movl -0x14(%%ebp), %%edx\n\t"
      "movl 0x4eae30, %%eax\n\t"
      "shrl $0xa, %%edx\n\t"
      "cmpl %%esi, %%eax\n\t"
      "movl %%edx, 0x32eb9c\n\t"
      "jle .LFUN_001c5ab0_2\n\t"
      "cmpl %%esi, 0x4eacd0\n\t"
      "jne .LFUN_001c5ab0_2\n\t"
      "call *%[c1c5a80]\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_001c5ab0_1\n\t"
      "pushl $1\n\t"
      "pushl $0x2df\n\t"
      "pushl $0x2bbe68\n\t"
      "pushl $0x2bbf80\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001c5ab0_1:\n\t"
      "call *%[c1c5a80]\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001c5ab0_2\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movl %%esi, 0x4eae30\n\t"
      "movl %%ecx, 0x4eae28\n\t"
      "jmp .LFUN_001c5ab0_3\n\t"
      ".LFUN_001c5ab0_2:\n\t"
      "movl 0x4eae28, %%ecx\n\t"
      ".LFUN_001c5ab0_3:\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "movl 0x4eae2c, %%edx\n\t"
      "leal (%%ecx,%%edi,1), %%eax\n\t"
      "cmpl %%edx, %%eax\n\t"
      "ja .LFUN_001c5ab0_4\n\t"
      "cmpl $0x10, 0x4eae30\n\t"
      "jge .LFUN_001c5ab0_4\n\t"
      "movl 0x4eae24, %%edx\n\t"
      "testl %%edx, %%edx\n\t"
      "jne .LFUN_001c5ab0_5\n\t"
      ".LFUN_001c5ab0_4:\n\t"
      "pushl $1\n\t"
      "pushl $0x2f7\n\t"
      "pushl $0x2bbe68\n\t"
      "pushl $0x2bbf54\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".byte 0xcc\n\t"
      "popl %%edi\n\t"
      "movl %%esi, %%eax\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001c5ab0_5:\n\t"
      "pushl $4\n\t"
      "leal (%%edx,%%ecx,1), %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%esi\n\t"
      "movl %%eax, 0x4eae28\n\t"
      "call *%[c1d371d]\n\t"
      "movl 0x4eae28, %%eax\n\t"
      "movl 0x4eae2c, %%ecx\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jle .LFUN_001c5ab0_6\n\t"
      "pushl $1\n\t"
      "pushl $0x312\n\t"
      "pushl $0x2bbe68\n\t"
      "pushl %%ecx\n\t"
      "subl %%ecx, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x2bbf00\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x10, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001c5ab0_6:\n\t"
      "cmpl $0x10, 0x4eae30\n\t"
      "jl .LFUN_001c5ab0_7\n\t"
      "pushl $1\n\t"
      "pushl $0x313\n\t"
      "pushl $0x2bbe68\n\t"
      "pushl $0x2bbed0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001c5ab0_7:\n\t"
      "movl 0x4eae30, %%eax\n\t"
      "movl %%esi, 0x4eacd0(,%%eax,4)\n\t"
      "incl %%eax\n\t"
      "pushl $0x20\n\t"
      "movl %%eax, 0x4eae30\n\t"
      "leal -0x20(%%ebp), %%eax\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "call *%[memset]\n\t"
      "addl $0xc, %%esp\n\t"
      "leal -0x20(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl $0x20, -0x20(%%ebp)\n\t"
      "call *%[c1d0da1]\n\t"
      "movl -0x14(%%ebp), %%edx\n\t"
      "movl 0x4eae2c, %%eax\n\t"
      "movl 0x4eae28, %%ecx\n\t"
      "shrl $0xa, %%edx\n\t"
      "cmpl %%eax, %%ecx\n\t"
      "movl %%edx, 0x32eb9c\n\t"
      "jl .LFUN_001c5ab0_8\n\t"
      "pushl $1\n\t"
      "pushl $0x31f\n\t"
      "pushl $0x2bbe68\n\t"
      "pushl $0x2bbe90\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "movl 0x4eae2c, %%eax\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001c5ab0_8:\n\t"
      "movl 0x4eae28, %%ecx\n\t"
      "addl $0x3000, %%ecx\n\t"
      "cmpl %%eax, %%ecx\n\t"
      "movl %%ecx, 0x4eae28\n\t"
      "jle .LFUN_001c5ab0_9\n\t"
      "movl %%eax, 0x4eae28\n\t"
      ".LFUN_001c5ab0_9:\n\t"
      "popl %%edi\n\t"
      "movl %%esi, %%eax\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [memset] "m"(b1c5ab0_memset), [c1d0da1] "m"(b1c5ab0_c1d0da1), [c1c5a80] "m"(b1c5ab0_c1c5a80), [assert] "m"(b1c5ab0_assert), [exitfn] "m"(b1c5ab0_exitfn), [c1d371d] "m"(b1c5ab0_c1d371d), [c8d9d0] "m"(b1c5ab0_c8d9d0)
      : "memory");
}
#else
#error "FUN_001c5ab0: clang naked draft required"
#endif


/* FUN_001c6900 (0x1c6900) — XBE naked draft (batch 324). */
#if defined(__clang__)
static bool (*const b1c6900_c19a7a0)(file_ref_t *info, int flags) = file_open;
static bool (*const b1c6900_c19acb0)(file_ref_t *info, int offset, int size, void *buffer) = file_read_from_position;
static void (*const b1c6900_c118be0)(void *definition, void *data, int count) = FUN_00118be0;
static bool (*const b1c6900_c19a930)(file_ref_t *info) = file_close;
static int (*const b1c6900_c8da40)(const void *a, const void *b, int size) = csmemcmp;

__attribute__((naked, noinline))
void FUN_001c6900(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x48, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "pushl $1\n\t"
      "xorb %%bl, %%bl\n\t"
      "pushl %%edi\n\t"
      "movb %%bl, -0x1(%%ebp)\n\t"
      "movl $0xc, %%esi\n\t"
      "call *%[c19a7a0]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001c6900_10\n\t"
      "leal -0xc(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $8\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c19acb0]\n\t"
      "addl $0x10, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001c6900_9\n\t"
      ".LFUN_001c6900_1:\n\t"
      "pushl $1\n\t"
      "leal -0xc(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x32ebe4\n\t"
      "call *%[c118be0]\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl $0x434f4d4d, %%eax\n\t"
      "je .LFUN_001c6900_3\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "testb $1, %%al\n\t"
      "je .LFUN_001c6900_2\n\t"
      "incl %%eax\n\t"
      ".LFUN_001c6900_2:\n\t"
      "leal -0xc(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal 0x8(%%esi,%%eax,1), %%esi\n\t"
      "pushl $8\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c19acb0]\n\t"
      "addl $0x10, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_001c6900_1\n\t"
      "movb -0x1(%%ebp), %%bl\n\t"
      "pushl %%edi\n\t"
      "call *%[c19a930]\n\t"
      "addl $4, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001c6900_3:\n\t"
      "leal -0x48(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x16\n\t"
      "addl $8, %%esi\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c19acb0]\n\t"
      "addl $0x10, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001c6900_9\n\t"
      "movb $0xac, %%cl\n\t"
      "movb %%cl, -0x16(%%ebp)\n\t"
      "movb %%cl, -0x22(%%ebp)\n\t"
      "movb %%cl, -0x2e(%%ebp)\n\t"
      "pushl $1\n\t"
      "leal -0x48(%%ebp), %%ecx\n\t"
      "movb $0x40, %%dl\n\t"
      "movb $0x44, %%al\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x32ec18\n\t"
      "movb %%dl, -0x18(%%ebp)\n\t"
      "movb $0xc, -0x17(%%ebp)\n\t"
      "movb %%al, -0x15(%%ebp)\n\t"
      "movb %%bl, -0x14(%%ebp)\n\t"
      "movb %%bl, -0x13(%%ebp)\n\t"
      "movb %%bl, -0x12(%%ebp)\n\t"
      "movb %%bl, -0x11(%%ebp)\n\t"
      "movb %%bl, -0x10(%%ebp)\n\t"
      "movb %%bl, -0xf(%%ebp)\n\t"
      "movb %%dl, -0x24(%%ebp)\n\t"
      "movb $0xd, -0x23(%%ebp)\n\t"
      "movb %%al, -0x21(%%ebp)\n\t"
      "movb %%bl, -0x20(%%ebp)\n\t"
      "movb %%bl, -0x1f(%%ebp)\n\t"
      "movb %%bl, -0x1e(%%ebp)\n\t"
      "movb %%bl, -0x1d(%%ebp)\n\t"
      "movb %%bl, -0x1c(%%ebp)\n\t"
      "movb %%bl, -0x1b(%%ebp)\n\t"
      "movb %%dl, -0x30(%%ebp)\n\t"
      "movb $0xe, -0x2f(%%ebp)\n\t"
      "movb %%al, -0x2d(%%ebp)\n\t"
      "movb %%bl, -0x2c(%%ebp)\n\t"
      "movb %%bl, -0x2b(%%ebp)\n\t"
      "movb %%bl, -0x2a(%%ebp)\n\t"
      "movb %%bl, -0x29(%%ebp)\n\t"
      "movb %%bl, -0x28(%%ebp)\n\t"
      "movb %%bl, -0x27(%%ebp)\n\t"
      "call *%[c118be0]\n\t"
      "pushl $0xa\n\t"
      "leal -0x40(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x18(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c8da40]\n\t"
      "addl $0x18, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_001c6900_6\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "movl $0x2b11, (%%eax)\n\t"
      ".LFUN_001c6900_4:\n\t"
      "movw -0x42(%%ebp), %%cx\n\t"
      "movw -0x48(%%ebp), %%dx\n\t"
      "movw %%cx, 0x8(%%eax)\n\t"
      "movw %%dx, 0x4(%%eax)\n\t"
      "cmpl $0x12, -0x8(%%ebp)\n\t"
      "je .LFUN_001c6900_5\n\t"
      "cmpl $0x4e4f4e45, -0x36(%%ebp)\n\t"
      "jne .LFUN_001c6900_9\n\t"
      ".LFUN_001c6900_5:\n\t"
      "pushl %%edi\n\t"
      "movb $1, %%bl\n\t"
      "call *%[c19a930]\n\t"
      "addl $4, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001c6900_6:\n\t"
      "pushl $0xa\n\t"
      "leal -0x40(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x24(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c8da40]\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_001c6900_7\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "movw -0x42(%%ebp), %%dx\n\t"
      "movw -0x48(%%ebp), %%cx\n\t"
      "movl $0x5622, (%%eax)\n\t"
      "movw %%dx, 0x8(%%eax)\n\t"
      "movw %%cx, 0x4(%%eax)\n\t"
      "cmpl $0x12, -0x8(%%ebp)\n\t"
      "je .LFUN_001c6900_5\n\t"
      "cmpl $0x4e4f4e45, -0x36(%%ebp)\n\t"
      "jne .LFUN_001c6900_9\n\t"
      "pushl %%edi\n\t"
      "movb $1, %%bl\n\t"
      "call *%[c19a930]\n\t"
      "addl $4, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001c6900_7:\n\t"
      "pushl $0xa\n\t"
      "leal -0x40(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x30(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c8da40]\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "jne .LFUN_001c6900_8\n\t"
      "movl $0xac44, (%%eax)\n\t"
      "jmp .LFUN_001c6900_4\n\t"
      ".LFUN_001c6900_8:\n\t"
      "movl $0xffffffff, (%%eax)\n\t"
      ".LFUN_001c6900_9:\n\t"
      "movb -0x1(%%ebp), %%bl\n\t"
      "pushl %%edi\n\t"
      "call *%[c19a930]\n\t"
      "addl $4, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001c6900_10:\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c19a7a0] "m"(b1c6900_c19a7a0), [c19acb0] "m"(b1c6900_c19acb0), [c118be0] "m"(b1c6900_c118be0), [c19a930] "m"(b1c6900_c19a930), [c8da40] "m"(b1c6900_c8da40)
      : "memory");
}
#else
#error "FUN_001c6900: clang naked draft required"
#endif


/* 0x1c6b20 */
void FUN_001c6b20(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int edi = 0;

  file_open((void *)(uintptr_t)edi, 0);
  /* test (char)eax, (char)eax -> je 0x1c6be2 */
  file_read_from_position((void *)(uintptr_t)edi, 0, 0, (void *)(uintptr_t)eax);
  /* test (char)eax, (char)eax -> je 0x1c6bbf */
  FUN_00118be0((void *)0x0032ebe4, (void *)(uintptr_t)ecx, 0);
  /* test (char)eax, 1 -> je 0x1c6b85 */
  file_read_from_position((void *)(uintptr_t)edi, 0, 0, (void *)(uintptr_t)edx);
  /* test (char)eax, (char)eax -> jne 0x1c6b60 */
  file_read_from_position((void *)(uintptr_t)edi, 0, 0, (void *)0);
  /* test (char)eax, (char)eax -> je 0x1c6bbf */
  file_close((void *)(uintptr_t)edi);
  /* test (char)ebx, (char)ebx -> je 0x1c6be2 */
  FUN_00118620((void *)(uintptr_t)edx, 0, 0);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)edi;
}

/* 0x1c6bf0 */
void FUN_001c6bf0(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* FUN_001c6c00 (0x1c6c00) — XBE naked draft (batch 339). */
#if defined(__clang__)
static void (*const b1c6c00_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1c6c00_exitfn)(int) = system_exit;
static bool (*const b1c6c00_c1c6880)(file_ref_t *info) = FUN_001c6880;
static void (*const b1c6c00_c1c6900)(void) = FUN_001c6900;
static void (*const b1c6c00_c1c6d20)(void) = FUN_001c6d20;
static void (*const b1c6c00_c1c6d90)(void) = FUN_001c6d90;

__attribute__((naked, noinline))
void FUN_001c6c00(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "movb $1, %%bl\n\t"
      "jne .LFUN_001c6c00_1\n\t"
      "pushl $1\n\t"
      "pushl $0x12\n\t"
      "pushl $0x2bc328\n\t"
      "pushl $0x2b3b10\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001c6c00_1:\n\t"
      "movl 0xc(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LFUN_001c6c00_2\n\t"
      "pushl $1\n\t"
      "pushl $0x13\n\t"
      "pushl $0x2bc328\n\t"
      "pushl $0x265878\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001c6c00_2:\n\t"
      "pushl %%esi\n\t"
      "call *%[c1c6880]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001c6c00_3\n\t"
      "pushl %%edi\n\t"
      "pushl %%esi\n\t"
      "call *%[c1c6900]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_001c6c00_5\n\t"
      ".LFUN_001c6c00_3:\n\t"
      "pushl %%esi\n\t"
      "call *%[c1c6d20]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001c6c00_4\n\t"
      "pushl %%edi\n\t"
      "pushl %%esi\n\t"
      "call *%[c1c6d90]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_001c6c00_5\n\t"
      ".LFUN_001c6c00_4:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001c6c00_5:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b1c6c00_assert), [exitfn] "m"(b1c6c00_exitfn), [c1c6880] "m"(b1c6c00_c1c6880), [c1c6900] "m"(b1c6c00_c1c6900), [c1c6d20] "m"(b1c6c00_c1c6d20), [c1c6d90] "m"(b1c6c00_c1c6d90)
      : "memory");
}
#else
#error "FUN_001c6c00: clang naked draft required"
#endif

