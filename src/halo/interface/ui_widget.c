#include <stdint.h>
#include "x87_math.h"
/* ui_widgets_initialize — sets up the UI widget subsystem. Allocates a
 * 0x4000-byte block via debug_malloc for the stack memory pool at
 * [0x31e04c], initializes the pool, zeroes the 0x68-byte static widget
 * state block at 0x46cc20, and sets sentinel values (-1) in various
 * 16-bit slots within the state block. The byte at 0x46cc82 records
 * whether the allocation succeeded. The float at 0x46cc4c is set to
 * -1.0f as an initial value. */
void ui_widgets_initialize(void)
{
  int alloc_result;
  int *pool;
  int16_t *ptr_a;
  int16_t *ptr_b;
  bool succeeded;

  succeeded = true;
  alloc_result = (int)debug_malloc(
    0x4000, 0, "c:\\halo\\SOURCE\\interface\\ui_widget.c", 0x75);
  if (alloc_result != 0) {
    pool = *(int **)0x31e04c;
    pool[1] = alloc_result;
    pool = *(int **)0x31e04c;
    pool[2] = 0x4000;
  } else {
    succeeded = false;
  }

  stack_memory_pool_initialize(*(void **)0x31e04c);
  csmemset((void *)0x46cc20, 0, 0x68);

  *(int16_t *)0x46cc48 = -1;
  *(int16_t *)0x46cc68 = -1;

  ptr_b = (int16_t *)0x46cc6c;
  ptr_a = (int16_t *)0x46cc50;
  do {
    *ptr_a = -1;
    *ptr_b = -1;
    ptr_a = (int16_t *)((char *)ptr_a + 6);
    ptr_b = (int16_t *)((char *)ptr_b + 4);
  } while ((int)ptr_a < 0x46cc68);

  *(uint8_t *)0x46cc82 = (uint8_t)succeeded;
  *(uint32_t *)0x46cc4c = 0xBF800000; /* -1.0f */
}

void ui_widgets_safe_to_load(bool a1)
{
}

/* ui_widget_realloc — thin wrapper around stack_memory_pool_realloc.
 * Passes the global widget stack memory pool at [0x31e04c] as the
 * first argument, forwarding the caller's block pointer, new size,
 * source file path, and line number for debug tracking. Returns the
 * reallocated block pointer (or NULL on failure). */
void *ui_widget_realloc(int a1, unsigned short a2, const char *a3,
                        unsigned int a4)
{
  return stack_memory_pool_realloc(*(void **)0x31e04c, a1, a2, a3, a4);
}

/* ui_widget_set_events_suppressed — sets or clears the events-suppressed
 * flag at 0x46cc85 in the widget globals block. When suppressed, the
 * per-frame event dispatch in process_ui_widgets skips input processing.
 * Asserts that the widget subsystem has been initialized (0x46cc82). */
void ui_widget_set_events_suppressed(bool suppress)
{
  assert_halt(*(uint8_t *)0x46cc82);
  *(uint8_t *)0x46cc85 = (uint8_t)suppress;
}

void *ui_widget_get_last_child(void *widget);

bool ui_widget_is_main_menu_loaded(void)
{
  int root_widget;

  if (*(uint8_t *)0x46cc88 != 1) {
    return false;
  }

  root_widget = *(int *)0x46cc20;
  if (root_widget == 0) {
    return false;
  }

  return csstrcmp(*(const char **)(root_widget + 4), "the_main_menu") == 0;
}

/* ui_widget_load_progress_widget — stub that fires a priority-2 error
 * stating the old loading progress screen was replaced. The original
 * progress widget system was superseded by the "glowy halo gravy"
 * loading screen; this function is never expected to succeed. */
void ui_widget_load_progress_widget(void)
{
  error(2, "the old loading progress screen has been replaced with glowy "
           "halo gravy");
}

bool ui_widget_initialization_in_progress(void)
{
  return *(int *)0x46cc7c != 0;
}

/* display_error_when_main_menu_loaded — queues a single error message handle
 * to be shown the next time the main menu shell window is loaded. The
 * 16-bit slot at word_46CC48 holds the pending handle; -1 means "no
 * pending error". main_screen_shell_load consumes the slot by passing the
 * handle to the error-dialog routine and resetting it back to -1. Only
 * one queued message is supported at a time; subsequent calls while a
 * message is pending are dropped with a priority-2 warning. */
void display_error_when_main_menu_loaded(int16_t error_handle)
{
  if (word_46CC48 == -1) {
    word_46CC48 = error_handle;
    return;
  }
  error(2, "there is already an error message queued for display at the "
           "main menu; ignoring this one");
}

/* ui_widget_start_title_music — starts the main menu looping music track.
 * Checks whether title music is already playing (0x46cc86) and whether a
 * game is in progress (0x1006c0). If neither, looks up the "lsnd" tag
 * "sound\music\title1\title1" via the tag system (0x1b9930) and starts
 * it as a looping sound (0x1c8510) with volume 1.0. Sets the
 * title_music_playing flag on success. */
void ui_widget_start_title_music(void)
{
  int tag_index;

  if (*(uint8_t *)0x46cc86 != 0)
    return;

  if (main_change_map_name_in_progress())
    return;

  tag_index = tag_loaded(0x6c736e64, "sound\\music\\title1\\title1");
  if (tag_index != -1) {
    error(2, "starting main menu music");
    sound_looping_start(tag_index, -1, 1.0f);
    *(uint8_t *)0x46cc86 = 1;
    return;
  }
  error(2, "title music tag not found");
}

void ui_widget_stop_attract_mode(void)
{
  int tag_index;

  if (*(uint8_t *)0x46cc86 != 1) {
    return;
  }

  tag_index = tag_loaded(0x6c736e64, "sound\\music\\title1\\title1");
  if (tag_index != -1) {
    error(2, "stopping main menu music");
    sound_looping_stop(tag_index);
    *(uint8_t *)0x46cc86 = 0;
    return;
  }

  error(2, "title music tag not found");
  *(uint8_t *)0x46cc86 = 0;
}

bool ui_widget_get_attract_mode_flag(void)
{
  return *(uint8_t *)0x46cc86 != 0;
}

void ui_widgets_disable_pause_game(int duration_ticks)
{
  assert_halt(duration_ticks >= 0);
  dword_46CC44 = duration_ticks;
}

void ui_widget_pending_load_push_internal(int *head, void *record);

void ui_widget_pending_load_pop(int *head, void *output);

/* ui_widget_close_children — walks the first_child linked list of a widget
 * and closes each child via ui_widget_close. Asserts that each child's
 * prev_sibling is NULL (since it should be the head of the sibling list)
 * and that the next sibling's prev_sibling points back correctly. After
 * closing each child, clears the next sibling's prev_sibling link before
 * advancing. */
void ui_widget_close_children(void *widget)
{
  int *child;
  int *next;

  child = *(int **)((char *)widget + 0x34);
  if (child == NULL)
    return;

  do {
    next = *(int **)((char *)child + 0x2c);

    assert_halt_msg(*(int *)((char *)child + 0x28) == 0,
                    "child->previous == NULL");
    assert_halt_msg(next == NULL || *(int *)((char *)next + 0x28) == (int)child,
                    "next->previous == child");

    ui_widget_close(child);

    if (next != NULL)
      *(int *)((char *)next + 0x28) = 0;

    child = next;
  } while (child != NULL);
}

int ui_widget_load_widget_children(void *definition, void *widget);
void ui_widget_link_child(void *parent, void *child);

/* ui_widget_find_by_tag — depth-first search over a widget subtree for the
 * first node whose tag handle (offset +0x0) equals tag_handle.  Checks the
 * current node first, then recurses into each child from first_child (+0x34)
 * following next_sibling (+0x2c). Returns NULL when no match exists. */
int *ui_widget_find_by_tag(int *widget, int tag_handle)
{
  int *result;
  int *child;

  if (*widget == tag_handle)
    return widget;

  result = NULL;
  child = *(int **)((char *)widget + 0x34);
  while (child != NULL && result == NULL) {
    if (*child == tag_handle) {
      result = child;
    } else {
      result = ui_widget_find_by_tag(child, tag_handle);
    }
    child = *(int **)((char *)child + 0x2c);
  }

  return result;
}

/* ui_widget_apply_focus — applies focus to target_widget within the root's
 * focus chain. Walks to the top-most parent (+0x30), snapshots the current
 * focused-descendant chain head (+0x38), optionally retargets when the input
 * widget is disabled (+0x12==1) by scanning sibling/parent lists for a
 * focusable widget (DeLa handlers>0 or type 2/3), then rewrites ancestor
 * focused-descendant links (+0x38). If the previous and new focus share the
 * same direct parent, updates only that parent and exits early. */
void ui_widget_apply_focus(void *root_widget, void *target_widget)
{
  int root;
  int focused;
  int parent;
  int *target;
  int *candidate;
  int tag_data;

  root = (int)root_widget;
  target = (int *)target_widget;

  while (*(int *)(root + 0x30) != 0) {
    root = *(int *)(root + 0x30);
  }

  focused = *(int *)(root + 0x38);

  if (*(uint8_t *)((char *)target + 0x12) == 1) {
    candidate = (int *)target[0xb];
    while (candidate != NULL) {
      tag_data = (int)tag_get(0x44654c61, candidate[0]);
      if (*(uint8_t *)((char *)candidate + 0x12) == 0 &&
          (*(int *)(tag_data + 0x54) > 0 ||
           *(int16_t *)((char *)candidate + 0xe) == 2 ||
           *(int16_t *)((char *)candidate + 0xe) == 3)) {
        goto set_candidate;
      }
      candidate = (int *)candidate[0xb];
    }

    parent = target[0xc];
    if (parent != 0) {
      candidate = *(int **)(parent + 0x34);
      while (candidate != NULL) {
        tag_data = (int)tag_get(0x44654c61, candidate[0]);
        if (*(uint8_t *)((char *)candidate + 0x12) == 0 &&
            (*(int *)(tag_data + 0x54) > 0 ||
             *(int16_t *)((char *)candidate + 0xe) == 2 ||
             *(int16_t *)((char *)candidate + 0xe) == 3)) {
          break;
        }
        candidate = (int *)candidate[0xb];
      }

      if (candidate == *(int **)(parent + 0x38)) {
        candidate = (int *)target[0xa];
        while (candidate != NULL) {
          tag_data = (int)tag_get(0x44654c61, candidate[0]);
          if (*(uint8_t *)((char *)candidate + 0x12) == 0 &&
              (*(int *)(tag_data + 0x54) > 0 ||
               *(int16_t *)((char *)candidate + 0xe) == 2 ||
               *(int16_t *)((char *)candidate + 0xe) == 3)) {
            break;
          }
          candidate = (int *)candidate[0xa];
        }
      }
    }

    if (candidate != NULL) {
    set_candidate:
      target = candidate;
    }
  }

  if (focused != 0) {
    if (target != NULL && *(int *)(focused + 0x30) == target[0xc] &&
        *(int *)(focused + 0x30) != 0) {
      *(int *)(target[0xc] + 0x38) = (int)target;
      return;
    }

    do {
      *(int *)(*(int *)(focused + 0x30) + 0x38) = 0;
      focused = *(int *)(focused + 0x38);
    } while (focused != 0);
  }

  parent = target[0xc];
  while (parent != 0) {
    *(int *)(parent + 0x38) = (int)target;
    target = (int *)target[0xc];
    parent = target[0xc];
  }
}

void ui_widget_pending_load_apply(int a6 /*@<eax>*/, void *widget, int16_t a7);

void ui_widget_update_list_selection(void *widget, void *definition);

void ui_widget_list_prev(void *widget);

void ui_widget_list_next(void *widget);

/* ui_widget_close — tears down a single UI widget and frees its memory.
 * Handles the "widget deleted" event handlers (type 0x19) from the widget's
 * DeLa tag definition, firing each matching handler via
 * ui_widget_event_handler_dispatch and optionally spawning replacement widgets.
 * Manages the pause counter (if the widget pauses the game), unlinks the
 * widget from its sibling/parent chains, performs type-specific cleanup
 * (text data for type 1, list data for types 2-3), frees the widget from
 * the stack memory pool, and clears any root widget slot that pointed to it.
 * The being_deleted flag at +0x14 prevents re-entrant closing. */
void ui_widget_close(void *widget)
{
  int *w;
  int tag_data;
  int handler_offset;
  int i;
  uint8_t *handler;
  bool widget_deleted;
  bool handler_result;
  int16_t widget_type;
  int prev;
  int next;
  int parent;
  char *tag_name;
  int idx;

  w = (int *)widget;

  assert_halt(widget && *(uint8_t *)0x46cc82);

  /* already being deleted — bail out */
  if (*(uint8_t *)((char *)w + 0x14) != 0)
    return;

  /* mark as being deleted */
  *(uint8_t *)((char *)w + 0x14) = 1;

  /* notify player control if this widget has a local player and no parent */
  if (*(int16_t *)((char *)w + 0x8) != -1 && w[0xc] == 0) {
    player_control_set_action_flags(*(int16_t *)((char *)w + 0x8), 0xfff, 1);
  }

  /* look up the DeLa (UI widget definition) tag */
  tag_data = (int)tag_get(0x44654c61, w[0]);

  /* iterate over event handlers, firing "widget deleted" (type 0x19) ones */
  i = 0;
  if (*(int *)(tag_data + 0x54) > 0) {
    handler_offset = 0;
    do {
      handler = (uint8_t *)(*(int *)(tag_data + 0x58) + handler_offset);

      if (*(int16_t *)(handler + 0x4) == 0x19 && (int8_t)handler[0] < 0) {
        widget_deleted = false;
        handler_result = ui_widget_event_handler_dispatch(
          w, 0, *(uint16_t *)(handler + 0x6), &widget_deleted);

        assert_halt_msg(!widget_deleted,
                        "a 'widget deleted' event handler tried to delete the "
                        "widget being deleted!");

        if (handler_result && (handler[0] & 0x8) != 0 &&
            *(int *)(handler + 0x14) != -1) {
          if (ui_widget_spawn_from_event_handler(w, *(int *)(handler + 0x14)) ==
              0) {
            error(2, "event handler failed to spawn widget");
          }
        }
      }

      i++;
      handler_offset += 0x48;
    } while (i < *(int *)(tag_data + 0x54));
  }

  /* manage the pause counter */
  if (*(uint8_t *)((char *)w + 0x13) == 1) {
    assert_halt_msg(*(int16_t *)0x46cc4a >= 1,
                    "widget pause counter out of whack");

    (*(int16_t *)0x46cc4a)--;

    if (*(int16_t *)0x46cc4a == 0) {
      if (game_time_get_paused()) {
        game_time_set_paused(0);
        if (*(uint8_t *)0x46cc88 != 0) {
          main_reset_player_actions();
          game_time_dispose_from_old_map();
          game_time_initialize_for_new_map();
          game_time_start();
        }
      }
      if (*(uint8_t *)0x46cc87 == 1) {
        sound_set_music_enabled(0);
        *(uint8_t *)0x46cc87 = 0;
      }
    }
  }

  /* close all children of this widget */
  ui_widget_close_children(w);

  /* unlink from prev sibling */
  prev = w[0xa];
  if (prev != 0) {
    *(int *)(prev + 0x2c) = w[0xb];
  }

  /* unlink from next sibling */
  next = w[0xb];
  if (next != 0) {
    *(int *)(next + 0x28) = w[0xa];
  }

  /* update parent's first_child if needed */
  parent = w[0xc];
  if (parent != 0 && *(int *)(parent + 0x34) == (int)w) {
    *(int *)(parent + 0x34) = w[0xb];
  }

  /* type-specific cleanup */
  widget_type = *(int16_t *)((char *)w + 0xe);
  if (widget_type == 1) {
    /* text widget: free text data */
    if (w[0xf] != 0) {
      stack_memory_pool_deallocate(*(void **)0x31e04c, (void *)w[0xf]);
    }
  } else if (widget_type > 1 && widget_type < 4) {
    /* list widget (type 2 or 3): warn about possible leak, free skin data,
     * recursively close header widget */
    if (w[0x10] != 0) {
      tag_name = (char *)(tag_data + 4);
      if (tag_name == NULL) {
        tag_name = "<unknown>";
      }
      error(2,
            "###WARNING: possible memory leak disposing of a list widget (%s)",
            tag_name);
    }
    if (w[0x13] != 0) {
      stack_memory_pool_deallocate(*(void **)0x31e04c, (void *)w[0x13]);
    }
    if (w[0x12] != 0) {
      ui_widget_close((void *)w[0x12]);
    }
  }

  /* free the widget itself */
  stack_memory_pool_deallocate(*(void **)0x31e04c, w);

  /* clear root widget slot if this widget was a root */
  for (idx = 0; idx < 4; idx++) {
    if (*(int *)(0x46cc20 + idx * 4) == (int)w) {
      *(int *)(0x46cc20 + idx * 4) = 0;
      return;
    }
  }
}

/* ui_widgets_close_all — iterates over the 4 UI widget stacks and tears
 * them down. For each stack, closes the root widget via ui_widget_close
 * (0xe5620), then walks the linked list at 0x46cc30[i] and deallocates
 * each widget node from the stack memory pool at [0x31e04c]. The list
 * is linked through offset +0xc in each widget node. */
void ui_widgets_close_all(void)
{
  int *list_heads;
  int widget;
  int next;
  void *pool;

  list_heads = (int *)0x46cc30;
  do {
    /* close the root widget for this stack if present */
    if (list_heads[-4] != 0) {
      ui_widget_close((void *)list_heads[-4]);
    }
    /* walk the linked list at list_heads[i], freeing each node */
    widget = *list_heads;
    if (widget != 0) {
      while (widget != 0) {
        pool = *(void **)0x31e04c;
        next = *(int *)(widget + 0xc);
        *list_heads = next;
        stack_memory_pool_deallocate(pool, (void *)widget);
        widget = *list_heads;
      }
    }
    list_heads++;
  } while ((int)list_heads < 0x46cc40);
}

/* ui_widget_set_focus — walks up the parent chain (field_0x30) from the given
 * widget to the root, then searches the widget tree for one matching
 * tag_handle.  If found, calls ui_widget_apply_focus; otherwise logs an error.
 */
void ui_widget_set_focus(void *widget, int tag_handle, int16_t player_index)
{
  void *root = widget;
  void *found;

  (void)player_index;

  while (*(void **)((char *)root + 0x30) != NULL)
    root = *(void **)((char *)root + 0x30);

  found = ui_widget_find_by_tag(root, tag_handle);
  if (found != NULL) {
    ui_widget_apply_focus(root, found);
    return;
  }

  error(2, "failed to find event focus target widget");
}

void ui_widget_close_and_reload(void *widget);

/* ui_widget_begin_filesystem_checks — spawns a background thread to perform
 * filesystem and saved-game file enumeration. Asserts that no initialization
 * thread is already running (0x46cc7c == NULL) and that the widget subsystem
 * is initialized (0x46cc82). Suppresses UI events (0x46cc85 = 1) and resets
 * the filesystem check result word at 0x46cc80 to 0 before spawning the
 * thread via thread_new (0x81630). If thread creation fails, runs the check
 * procedure synchronously (0xe5590) and re-clears the suppress flag. */
void ui_widget_begin_filesystem_checks(void)
{
  assert_halt(*(int *)0x46cc7c == 0);
  error(2, "begining filesystem checks & saved game file enumeration...");
  assert_halt(*(uint8_t *)0x46cc82);
  *(uint8_t *)0x46cc85 = 1;
  *(int16_t *)0x46cc80 = 0;
  if (!thread_new(0, (void *)0xe5590, 0, (void **)0x46cc7c)) {
    error(2, "failed to spawn thread for filesystem checks - running "
             "synchronously!");
    *(int *)0x46cc7c = 0;
    ((void(__stdcall *)(int))0xe5590)(0);
    assert_halt(*(uint8_t *)0x46cc82);
    *(uint8_t *)0x46cc85 = 0;
  }
}

/* ui_widgets_dispose — tears down the UI widget system. Closes all open
 * widgets, frees the widget memory pool allocated by ui_widgets_initialize
 * (0x4000 bytes at [ptr+4]), zeros the pool pointer and size fields, and
 * clears the 0x68-byte static widget state block at 0x46cc20. Called during
 * engine shutdown. */
void ui_widgets_dispose(void)
{
  int *ptr;

  ui_widgets_close_all();

  ptr = *(int **)0x31e04c;
  if (ptr[1] != 0) {
    debug_free((void *)ptr[1], "c:\\halo\\SOURCE\\interface\\ui_widget.c",
               0x76);
  }
  ptr[1] = 0;
  ptr[2] = 0;
  csmemset((void *)0x46cc20, 0, 0x68);
}

int ui_widget_list_next_item(void *widget, void *event_data,
                             char *widget_deleted);

int ui_widget_list_prev_item(void *widget, void *event_data,
                             char *widget_deleted);

void ui_widget_handle_event_handler(uintptr_t widget, uintptr_t definition,
                                    uintptr_t event_data, uintptr_t event_handler,
                                    uintptr_t widget_deleted);

/* render_ui_widgets — renders all active UI widget stacks and an optional
 * screen fade overlay. For each of the 4 widget root slots (0x46cc20..2c),
 * determines whether the widget should render based on its local player index
 * vs the current player, the "always render" flag at +0x11, and the
 * "in_game_mode" flag at +0x15. Renders the widget tree via the recursive
 * helper at 0xe73c0. If the debug overlay flag at 0x46cc84 is set, also
 * renders the widget's tag name in a small debug font. After all stacks,
 * checks the global fade value at 0x46cc4c: if it is in [0.0, 1.0], draws
 * a fullscreen fade rectangle (alpha = fade * 255, shifted to the high byte
 * of an ARGB color). When fade >= 0.95 it is clamped to 1.0. The fade
 * value is initialised to -1.0 (inactive). */
void render_ui_widgets(int16_t player_index, viewport_bounds_t *window_bounds)
{
  int widget;
  int16_t clamped_player;
  int i;
  viewport_bounds_t local_bounds;
  float color[4];
  int font_tag;
  const char *tag_name;
  float fade;

  assert_halt(window_bounds != NULL);

  /* store clamped player index: -1 maps to 0, otherwise keep player_index */
  *(uint16_t *)0x5aa45c =
    (uint16_t)((player_index == -1 ? 0 : 1) & (uint16_t)player_index);

  /* if network loading screen is active, bail */
  if (((char (*)(void))0x1c5960)() != 0) {
    return;
  }

  /* if virtual keyboard is active, render it and return */
  if (((char (*)(void))0xf5640)() != 0) {
    ((void (*)(void))0xf5fa0)();
    return;
  }

  /* clamp player_index into [0, 3] range */
  if (player_index < 0) {
    clamped_player = 0;
  } else if (player_index > 3) {
    clamped_player = 3;
  } else {
    clamped_player = player_index;
  }

  for (i = 0; i < 4; i++) {
    widget = *(int *)(0x46cc20 + i * 4);
    if (widget == 0)
      continue;

    /* always-render flag at widget+0x11 */
    if (*(uint8_t *)(widget + 0x11) == 1) {
      goto do_render;
    }

    /* in-game mode flag at widget+0x15 */
    if (*(uint8_t *)(widget + 0x15) == 1) {
      uint16_t widget_player = *(uint16_t *)(widget + 0x8);
      if (widget_player == (uint16_t)clamped_player)
        goto do_render;
      if (widget_player == 0xffff)
        goto do_render;
      if ((uint16_t)clamped_player == 0xffff)
        goto do_render;
      if (*(uint8_t *)0x46cc88 != 0)
        goto do_render;
      continue;
    } else {
      /* not in-game: render if player matches or (player == -1 and stack 0) */
      uint16_t widget_player = *(uint16_t *)(widget + 0x8);
      if (widget_player == 0xffff && i == 0)
        goto do_render;
      if (widget_player == (uint16_t)clamped_player)
        goto do_render;
      continue;
    }

  do_render:
    local_bounds.x1 = window_bounds->x1 - window_bounds->x0;
    local_bounds.y1 = window_bounds->y1 - window_bounds->y0;
    local_bounds.x0 = 0;
    local_bounds.y0 = 0;

    ((void (*)(int, viewport_bounds_t *, int, int, int))0xe73c0)(
      widget, &local_bounds, 0, 1, 0);

    /* debug overlay: draw widget tag name */
    if (*(uint8_t *)0x46cc84 != 0) {
      local_bounds.x0 += 0x20;
      local_bounds.x1 += 0x20;
      local_bounds.y0 += 0x20;
      local_bounds.y1 += 0x20;
      color[0] = 1.0f;
      color[1] = 1.0f;
      color[2] = 1.0f;
      color[3] = 1.0f;
      font_tag = tag_loaded(0x666f6e74, "ui\\small_ui", -1, 0, 0, color);
      ((void (*)(int))0x19b8b0)(font_tag);
      tag_name = tag_get_name(*(int *)(0x46cc20 + i * 4));
      rasterizer_text_draw(&local_bounds, 0, 0, 0, tag_name);
    }
  }

  /* screen fade overlay */
  fade = *(float *)0x46cc4c;
  if (fade >= 0.0f && fade <= 1.0f) {
    local_bounds.y0 = 0;
    local_bounds.x1 = 0x280;
    local_bounds.x0 = 0;
    local_bounds.y1 = 0x1e0;
    if (fade >= *(float *)0x255ed4) { /* 0.95f */
      *(float *)0x46cc4c = 1.0f;
    }
    {
      int alpha = (int)(*(float *)0x46cc4c * *(float *)0x2602c8); /* * 255.0 */
      ((void (*)(viewport_bounds_t *, int))0x92ec0)(&local_bounds, alpha << 24);
    }
  }
}

void ui_widget_process_event(void *widget, void *widget_tag, void *event_data,
                             void *handled)
{
  int *w;
  int *definition;
  uint8_t *event;
  uint8_t *handled_out;
  bool allowed_player;
  bool consumed;
  bool widget_deleted;
  int16_t sound_effect;
  int i;
  int offset;
  int elapsed;
  int timeout;
  int fade_ticks;
  int child;
  int child_tag;
  int16_t type;
  uint32_t flags;
  const char *sound_name;
  int sound_tag;

  w = (int *)widget;
  definition = (int *)widget_tag;
  event = (uint8_t *)event_data;
  handled_out = (uint8_t *)handled;

  consumed = false;
  widget_deleted = false;

  allowed_player = (*(int16_t *)((char *)w + 8) == -1) ||
                   (*(int16_t *)((char *)w + 8) == *(int16_t *)(event + 2));
  sound_effect = 0;

  if (w == NULL || definition == NULL || event == NULL || handled_out == NULL) {
    display_assert("widget && definition && event && return_widget_deleted",
                   "c:\\halo\\SOURCE\\interface\\ui_widget.c", 0xbfb, true);
    system_exit(-1);
  }

  if (*(int16_t *)event == 3 && event[5] > 1 && *(int16_t *)(event + 2) >= 0 &&
      *(int16_t *)(event + 2) < 4 && event[4] >= 8 && event[4] < 0xc &&
      (uint32_t)(*(uint32_t *)0x46cc40 -
                 *(uint32_t *)(0x46cc90 +
                               ((event[4] - 8) + *(int16_t *)(event + 2) * 4) *
                                 4)) >= 0xfa) {
    event[5] = 1;
  }

  if (*(uint8_t *)((char *)w + 0x16) == 1) {
    int16_t widget_player = *(int16_t *)((char *)w + 8);

    if (widget_player >= 0 && widget_player < 4) {
      if (input_has_gamepad(widget_player)) {
        ui_widget_close(ui_widget_get_last_child(w));
        widget_deleted = true;
      }
    } else {
      if (widget_player != -1) {
        display_assert("widget->local_player_index==NONE",
                       "c:\\halo\\SOURCE\\interface\\ui_widget.c", 0xc23, true);
        system_exit(-1);
      }

      for (i = 0; i < 4; i++) {
        if (input_has_gamepad(i)) {
          child = (int)w;
          while (*(int *)(child + 0x30) != 0) {
            child = *(int *)(child + 0x30);
          }
          ui_widget_close((void *)child);
          widget_deleted = true;
          break;
        }
      }
    }
  }

  if (allowed_player && !widget_deleted) {
    if (*(int16_t *)event == 3 && event[5] == 1) {
      if ((event[4] == 0xd || event[4] == 1) &&
          *(int *)(definition + 0x15) > 0) {
        int found = 0;

        for (i = 0; i < *(int *)(definition + 0x15); i++) {
          int16_t handler_type =
            *(int16_t *)(*(int *)(definition + 0x16) + i * 0x48 + 4);
          if ((event[4] == 0xd && handler_type == 0xd) ||
              (event[4] == 1 && handler_type == 1)) {
            found = 1;
            break;
          }
        }

        if (!found) {
          ui_widget_close_and_reload(w);
          sound_effect = 3;
          widget_deleted = true;
          consumed = true;
        }
      }
    }
  }

  if (!widget_deleted) {
    timeout = *(int *)((char *)w + 0x1c);
    if (timeout > 0) {
      elapsed = *(int *)0x46cc40 - *(int *)((char *)w + 0x18);
      fade_ticks = *(int *)((char *)w + 0x20);

      if ((uint32_t)elapsed >= (uint32_t)(timeout + fade_ticks)) {
        child = (int)w;
        while (*(int *)(child + 0x30) != 0) {
          child = *(int *)(child + 0x30);
        }
        ui_widget_close((void *)child);
        widget_deleted = true;
        goto after_local_handling;
      }

      if (fade_ticks > 0 && (elapsed - timeout) > 0) {
        float fade_den = (float)fade_ticks;
        if (fade_ticks < 0) {
          fade_den += *(float *)0x25fb8c;
        }
        *(float *)((char *)w + 0x24) =
          1.0f - (float)(elapsed - timeout) / fade_den;
      }
    }

    if (*(int16_t *)((char *)w + 0x52) < 0) {
      *(int16_t *)((char *)w + 0x52) = 0;
    }
    if (*(int16_t *)((char *)w + 0x54) < 0) {
      *(int16_t *)((char *)w + 0x54) = 0;
    }

    if (*(int16_t *)((char *)w + 0xe) == 2) {
      for (child = *(int *)((char *)w + 0x34); child != 0;
           child = *(int *)(child + 0x2c)) {
        *(int16_t *)(child + 0x50) = 0;
        if (child == *(int *)((char *)w + 0x38) &&
            *(int16_t *)(child + 0x56) == 2) {
          *(int16_t *)(child + 0x50) = 1;
        }
      }
    } else if (*(int16_t *)((char *)w + 0xe) == 3) {
      ui_widget_update_list_selection(w, definition);
    }

    if (allowed_player) {
      flags = *(uint32_t *)(definition + 0xb);

      if ((flags & 8) != 0 && *(int *)((char *)w + 0x38) != 0 &&
          !widget_deleted) {
        if (*(int16_t *)event == 3 && event[5] == 1) {
          if (event[4] == 8) {
            ui_widget_list_next(w);
            sound_effect = 1;
            consumed = true;
          } else if (event[4] == 9) {
            ui_widget_list_prev(w);
            sound_effect = 1;
            consumed = true;
          }
        } else if (*(int16_t *)event == 1) {
          if (*(int16_t *)(event + 6) == (int16_t)0x8000) {
            ui_widget_list_prev(w);
            sound_effect = 1;
            consumed = true;
          } else if (*(int16_t *)(event + 6) == 0x7fff) {
            ui_widget_list_next(w);
            sound_effect = 1;
            consumed = true;
          }
        }
      }

      if (!consumed && (flags & 0x10) != 0 && *(int *)((char *)w + 0x38) != 0 &&
          !widget_deleted) {
        if (*(int16_t *)event == 3 && event[5] == 1) {
          if (event[4] == 0xa) {
            ui_widget_list_next(w);
            if (sound_effect == 0) {
              sound_effect = 1;
            }
            consumed = true;
          } else if (event[4] == 0xb) {
            ui_widget_list_prev(w);
            if (sound_effect == 0) {
              sound_effect = 1;
            }
            consumed = true;
          }
        } else if (*(int16_t *)event == 1) {
          if (*(int16_t *)(event + 4) == (int16_t)0x8000) {
            ui_widget_list_next(w);
            if (sound_effect == 0) {
              sound_effect = 1;
            }
            consumed = true;
          } else if (*(int16_t *)(event + 4) == 0x7fff) {
            ui_widget_list_prev(w);
            if (sound_effect == 0) {
              sound_effect = 1;
            }
            consumed = true;
          }
        }
      }

      type = *(int16_t *)((char *)w + 0xe);
      if ((flags & 0x20) != 0 && (type == 2 || type == 3) && !consumed &&
          !widget_deleted) {
        if (*(int16_t *)event == 3 && event[5] == 1) {
          if (event[4] == 8) {
            ui_widget_list_prev_item(w, event, (char *)&widget_deleted);
            if (sound_effect == 0) {
              sound_effect = 1;
            }
            consumed = true;
          } else if (event[4] == 9) {
            ui_widget_list_next_item(w, event, (char *)&widget_deleted);
            if (sound_effect == 0) {
              sound_effect = 1;
            }
            consumed = true;
          }
        } else if (*(int16_t *)event == 1) {
          if (*(int16_t *)(event + 6) == (int16_t)0x8000) {
            ui_widget_list_next_item(w, event, (char *)&widget_deleted);
            if (sound_effect == 0) {
              sound_effect = 1;
            }
            consumed = true;
          } else if (*(int16_t *)(event + 6) == 0x7fff) {
            ui_widget_list_prev_item(w, event, (char *)&widget_deleted);
            if (sound_effect == 0) {
              sound_effect = 1;
            }
            consumed = true;
          }
        }
      }

      if ((flags & 0x40) != 0 && (type == 2 || type == 3) && !consumed &&
          !widget_deleted) {
        if (*(int16_t *)event == 3 && event[5] == 1) {
          if (event[4] == 0xa) {
            ui_widget_list_prev_item(w, event, (char *)&widget_deleted);
            if (sound_effect == 0) {
              sound_effect = 1;
            }
            consumed = true;
          } else if (event[4] == 0xb) {
            ui_widget_list_next_item(w, event, (char *)&widget_deleted);
            if (sound_effect == 0) {
              sound_effect = 1;
            }
            consumed = true;
          }
        } else if (*(int16_t *)event == 1) {
          if (*(int16_t *)(event + 4) == (int16_t)0x8000) {
            ui_widget_list_prev_item(w, event, (char *)&widget_deleted);
            if (sound_effect == 0) {
              sound_effect = 1;
            }
            consumed = true;
          } else if (*(int16_t *)(event + 4) == 0x7fff) {
            ui_widget_list_next_item(w, event, (char *)&widget_deleted);
            if (sound_effect == 0) {
              sound_effect = 1;
            }
            consumed = true;
          }
        }
      }
    }
  }

after_local_handling:
  if (allowed_player && *(int *)(definition + 0x15) > 0) {
    offset = 0;
    for (i = 0; i < *(int *)(definition + 0x15) && !widget_deleted; i++) {
      uint8_t *event_handler =
        (uint8_t *)(*(int *)(definition + 0x16) + offset);
      bool matches = false;

      type = *(int16_t *)event;
      if (type == 1) {
        switch (*(int16_t *)(event_handler + 4)) {
        case 0x10:
          matches = *(int16_t *)(event + 6) == 0x7fff;
          break;
        case 0x11:
          matches = *(int16_t *)(event + 6) == (int16_t)0x8000;
          break;
        case 0x12:
          matches = *(int16_t *)(event + 4) == (int16_t)0x8000;
          break;
        case 0x13:
          matches = *(int16_t *)(event + 4) == 0x7fff;
          break;
        default:
          break;
        }
      } else if (type == 2) {
        switch (*(int16_t *)(event_handler + 4)) {
        case 0x14:
          matches = *(int16_t *)(event + 6) == 0x7fff;
          break;
        case 0x15:
          matches = *(int16_t *)(event + 6) == (int16_t)0x8000;
          break;
        case 0x16:
          matches = *(int16_t *)(event + 4) == (int16_t)0x8000;
          break;
        case 0x17:
          matches = *(int16_t *)(event + 4) == 0x7fff;
          break;
        default:
          break;
        }
      } else if (type == 3 && *(int16_t *)(event_handler + 4) == event[4]) {
        matches = event[5] == 1;
      }

      if (matches) {
        consumed = true;
        ui_widget_handle_event_handler(w, definition, event, event_handler,
                                       (char *)&widget_deleted);
      }

      offset += 0x48;
    }
  }

  flags = *(uint32_t *)(definition + 0xb);
  if ((flags & 0x400) != 0 && (flags & 1) == 0) {
    display_assert("if the _widget_pass_handled_events_to_all_children_bit "
                   "flag is checked, "
                   "_widget_pass_unhandled_events_to_children_bit must also "
                   "be checked for it to work",
                   "c:\\halo\\SOURCE\\interface\\ui_widget.c", 0xd95, false);
  }

  if (!(((flags & 0x400) == 0 && consumed) ||
        (((flags & 1) == 0 && (flags & 0x100) == 0)) || widget_deleted)) {
    if ((flags & 0x100) == 0) {
      child = *(int *)((char *)w + 0x38);
      if (child != 0) {
        int16_t child_player = *(int16_t *)(child + 8);
        if (child_player == -1 || child_player == *(int16_t *)(event + 2)) {
          child_tag = *(int *)child;
          ui_widget_process_event((void *)(uintptr_t)child,
                                  tag_get(0x44654c61, child_tag), event,
                                  (char *)&widget_deleted);
        }
      }
    } else {
      child = *(int *)((char *)w + 0x34);
      while (child != 0) {
        int16_t child_player = *(int16_t *)(child + 8);
        if (child_player == -1 || child_player == *(int16_t *)(event + 2)) {
          child_tag = *(int *)child;
          ui_widget_process_event((void *)(uintptr_t)child,
                                  tag_get(0x44654c61, child_tag), event,
                                  (char *)&widget_deleted);
          if (widget_deleted) {
            break;
          }
        }
        child = *(int *)(child + 0x2c);
      }
    }
  }

  if (widget_deleted && (flags & 0x800) != 0) {
    for (i = 0; i < 4; i++) {
      if (*(int *)(0x46cc20 + i * 4) != 0) {
        break;
      }
    }
    if (i == 4) {
      main_goto_main_menu();
    }
  }

  if (*(int16_t *)event == 3 && event[5] == 1 && *(int16_t *)(event + 2) >= 0 &&
      *(int16_t *)(event + 2) < 4 && event[4] >= 8 && event[4] < 0xc) {
    *(int *)(0x46cc90 + ((event[4] - 8) + *(int16_t *)(event + 2) * 4) * 4) =
      *(int *)0x46cc40;
  }

  switch (sound_effect) {
  case 1:
    sound_name = "sound\\sfx\\ui\\cursor";
    break;
  case 2:
    sound_name = "sound\\sfx\\ui\\forward";
    break;
  case 3:
    sound_name = "sound\\sfx\\ui\\back";
    break;
  default:
    sound_name = NULL;
    break;
  }

  if (sound_name != NULL) {
    sound_tag = tag_loaded(0x736e6421, sound_name);
    if (sound_tag != -1) {
      sound_impulse_start(sound_tag, 1.0f);
    }
  }

  *handled_out = (uint8_t)widget_deleted;
}

void *ui_widget_load_by_name_or_tag(const char *name, int tag_index, int a3,
                                    int widget_stack, int parent_tag_index,
                                    int a6, int a7)
{
  typedef struct ui_widget_pending_load_entry {
    int tag_index;
    int a6;
    int16_t a7;
    int16_t widget_stack;
  } ui_widget_pending_load_entry_t;

  int tag_data;
  int widget;
  int widget_stack_base;
  int16_t stack_index;
  int16_t previous_stack_player;
  int root_widget;
  ui_widget_pending_load_entry_t pending_load;

  widget_stack_base = ((int16_t)widget_stack == -1) ? 0 : widget_stack;

  if (*(uint8_t *)0x46cc82 == 0) {
    display_assert("widget_globals.initialized",
                   "c:\\halo\\SOURCE\\interface\\ui_widget.c", 0x179, true);
    system_exit(-1);
  }

  if (name == NULL && tag_index == -1) {
    display_assert("(name != NULL) || (tag_index != NONE)",
                   "c:\\halo\\SOURCE\\interface\\ui_widget.c", 0x17a, true);
    system_exit(-1);
  }

  stack_index = (int16_t)widget_stack_base;
  if (stack_index < 0 || stack_index >= 4) {
    display_assert("(widget_stack>=0) && (widget_stack<MAXIMUM_GAMEPADS)",
                   "c:\\halo\\SOURCE\\interface\\ui_widget.c", 0x17b, true);
    system_exit(-1);
  }

  if (tag_index == -1) {
    tag_index = tag_loaded(0x44654c61, name);
    if (tag_index == -1) {
      error(2, "ui_widget_definition tag '%s'/%d not loaded", name, -1);
      return NULL;
    }
  }

  tag_data = (int)tag_get(0x44654c61, tag_index);
  widget = (int)stack_memory_pool_allocate(
    *(void **)0x31e04c, 0x58, "c:\\halo\\SOURCE\\interface\\ui_widget.c",
    0x18b);
  if (widget == 0) {
    error(2, "failed to create new widget; out of memory!");
    return NULL;
  }

  if (a3 == 0) {
    root_widget = *(int *)(0x46cc20 + (int)stack_index * 4);
    if (root_widget != 0) {
      previous_stack_player = *(int16_t *)(root_widget + 8);
      ui_widget_close((void *)root_widget);
    } else {
      previous_stack_player = -1;
    }

    *(int *)(0x46cc20 + (int)stack_index * 4) = widget;

    if (parent_tag_index != -1 &&
        (*(uint32_t *)((int)tag_get(0x44654c61, parent_tag_index) + 0x2c) &
         0x4000) == 0) {
      pending_load.tag_index = parent_tag_index;
      pending_load.a6 = a6;
      pending_load.a7 = (int16_t)a7;
      pending_load.widget_stack = previous_stack_player;
      ui_widget_pending_load_push_internal(
        (int *)(0x46cc30 + (int)stack_index * 4), &pending_load);
    }
  }

  if ((int16_t)widget_stack == -1) {
    switch (*(int16_t *)(tag_data + 2)) {
    case 0:
      widget_stack = 0;
      break;
    case 1:
      widget_stack = 1;
      break;
    case 2:
      widget_stack = 2;
      break;
    case 3:
      widget_stack = 3;
      break;
    case 4:
      widget_stack = -1;
      break;
    default:
      break;
    }
  }

  ui_widget_load_from_tag_internal((void *)tag_data, (void *)widget, (void *)a3,
                                   tag_index, widget_stack, widget_stack_base);
  return (void *)widget;
}

/* main_screen_shell_load — loads the main menu shell UI. On the first boot
 * (when the first-run flag at 0x31e050 is set), plays the intro bink movie
 * and kicks off filesystem checks / saved game enumeration. If the command
 * line is "xdemo", the intro movie is skipped. After the bink + fs-check
 * phase, loads the main menu widget ("ui\shell\main_menu\main_menu"),
 * displays any queued error message (word_46CC48), starts title music if
 * not already playing, and initializes the virtual keyboard. The first-run
 * flag is cleared at the end so subsequent calls skip the intro path. */
void main_screen_shell_load(void)
{
  bool play_main_menu;
  char *command_line;
  int widget;

  play_main_menu = true;
  assert_halt(*(uint8_t *)0x46cc82);

  *(uint8_t *)0x46cc85 = 0;

  if (*(uint8_t *)0x31e050 == 1) {
    command_line = shell_get_command_line();
    if (command_line == NULL) {
      goto play_intro;
    }
    if (crt_stricmp(command_line, "xdemo") != 0) {
    play_intro:
      bink_playback_start("d:\\bink\\intro.bik", 0xe6);
      play_main_menu = false;
      if (bink_playback_active() == 0) {
        play_main_menu = true;
      }
    } else {
      error(2, "xbox command line= '%s'", command_line);
    }
    ui_widget_begin_filesystem_checks();
    input_abstraction_mark_time();
    if (!play_main_menu)
      goto done;
  }

  event_manager_mark_time();
  ui_widgets_close_all();

  widget = (int)ui_widget_load_by_name_or_tag("ui\\shell\\main_menu\\main_menu",
                                              -1, 0, -1, -1, -1, -1);
  if (widget == 0) {
    error(2, "failed to load main screen shell window");
  }

  if (word_46CC48 != -1) {
    ui_widget_display_error(word_46CC48, -1, 1, 0);
    word_46CC48 = -1;
  }

  if (*(uint8_t *)0x46cc86 == 0) {
    ui_widget_start_title_music();
  }

  ui_widget_clear_last_error_index();

done:
  if (!((bool (*)(void))0xf53a0)()) {
    error(2, "failed to initialize the virtual keyboard");
  }
  *(uint8_t *)0x31e050 = 0;
}

void ui_widget_display_error(int16_t error_handle, int local_player_index,
                             char is_modal, char pause_game)
{
  int16_t stack_index;
  int16_t local_player_count;
  int16_t local_player;
  int16_t matched_player;
  int16_t text_value;
  bool target_is_primary;
  const char *widget_name;
  int root_widget;
  int root_tag_index;
  int widget;
  int text_widget;
  int widget_stack_index;
  int16_t deferred_slot;

  if (cinematic_in_progress()) {
    stack_index = (int16_t)local_player_index;
    if (stack_index == -1) {
      stack_index = 0;
    } else if (stack_index < 0 || stack_index >= 4) {
      display_assert(
        "local_player_index>=0 && local_player_index<MAXIMUM_NUMBER_OF_LOCAL_"
        "PLAYERS",
        "c:\\halo\\SOURCE\\interface\\ui_widget.c", 0x81d, true);
      system_exit(-1);
    }

    deferred_slot = *(int16_t *)(0x46cc6c + (int)stack_index * 4);
    if (deferred_slot != -1) {
      error(2,
            "there is already a deferred-for-cinematic error queued for player"
            " #%d; ignoring this one",
            (int)stack_index);
      return;
    }

    *(int16_t *)(0x46cc6c + (int)stack_index * 4) = error_handle;
    *(uint8_t *)(0x46cc6e + (int)stack_index * 4) = (uint8_t)is_modal;
    *(uint8_t *)(0x46cc6f + (int)stack_index * 4) = (uint8_t)pause_game;
    return;
  }

  stack_index = (int16_t)local_player_index;
  local_player_count = 0;
  local_player = -1;
  matched_player = -1;
  target_is_primary = true;

  if (stack_index != -1) {
    local_player = local_player_get_next(-1);
    while (local_player != -1) {
      if (local_player == stack_index) {
        matched_player = stack_index;
        if (local_player_count > 0) {
          target_is_primary = false;
        }
      }
      local_player_count++;
      local_player = local_player_get_next(local_player);
    }

    if (*(uint8_t *)0x46cc88 == 0) {
      if (matched_player == -1) {
        stack_index = -1;
      }
    }
  }

  switch (local_player_count) {
  case 0:
  case 1:
    widget_name = is_modal ? "ui\\shell\\error\\error_modal_fullscreen" :
                             "ui\\shell\\error\\error_nonmodal_fullscreen";
    break;
  case 2:
    widget_name = is_modal ? "ui\\shell\\error\\error_modal_halfscreen" :
                             "ui\\shell\\error\\error_nonmodal_halfscreen";
    break;
  case 3:
    if (target_is_primary) {
      widget_name = is_modal ? "ui\\shell\\error\\error_modal_halfscreen" :
                               "ui\\shell\\error\\error_nonmodal_halfscreen";
    } else {
      widget_name = is_modal ? "ui\\shell\\error\\error_modal_qtrscreen" :
                               "ui\\shell\\error\\error_nonmodal_qtrscreen";
    }
    break;
  case 4:
    widget_name = is_modal ? "ui\\shell\\error\\error_modal_qtrscreen" :
                             "ui\\shell\\error\\error_nonmodal_qtrscreen";
    break;
  default:
    display_assert("invalid local player count",
                   "c:\\halo\\SOURCE\\interface\\ui_widget.c", 0x871, true);
    system_exit(-1);
    return;
  }

  if (stack_index == -1) {
    widget_stack_index = 0;
  } else {
    if (stack_index < 0 || stack_index >= 4) {
      display_assert("(widget_stack>=0) && (widget_stack<MAXIMUM_NUMBER_OF_"
                     "LOCAL_PLAYERS)",
                     "c:\\halo\\SOURCE\\interface\\ui_widget.c", 0x878, true);
      system_exit(-1);
    }
    widget_stack_index = stack_index;
  }

  if (*(uint8_t *)0x46cc88 != 0 && *(float *)0x46cc4c <= 1.0f &&
      *(float *)0x46cc4c >= 0.0f) {
    error(2, "aborting to the main menu root, for safety's sake");
    main_screen_shell_load();
    main_defer_map_map_change();
    *(float *)0x46cc4c = -1.0f;
  }

  root_widget = *(int *)(0x46cc20 + widget_stack_index * 4);
  if (root_widget == 0) {
    root_tag_index = -1;
  } else {
    root_tag_index = *(int *)root_widget;
    if (*(uint8_t *)(root_widget + 0x15) == 1) {
      error(2,
            "there is already an error message displayed for this local player"
            " index");
      error(2, "failed to display error message");
      return;
    }
  }

  widget = (int)ui_widget_load_by_name_or_tag(widget_name, -1, 0, stack_index,
                                              root_tag_index, -1, -1);
  if (widget == 0) {
    error(2, "failed to display error message");
    return;
  }

  if (*(int *)(widget + 0x34) == 0 ||
      *(int *)(*(int *)(widget + 0x34) + 0x34) == 0) {
    display_assert("error screen widget tag not layed out as expected",
                   "c:\\halo\\SOURCE\\interface\\ui_widget.c", 0x89e, true);
    system_exit(-1);
  }

  text_widget = *(int *)(*(int *)(widget + 0x34) + 0x34);
  if (*(int16_t *)(text_widget + 0xe) != 1) {
    display_assert("expected a text box widget in the error widget",
                   "c:\\halo\\SOURCE\\interface\\ui_widget.c", 0x8a0, true);
    system_exit(-1);
  }

  if (error_handle < 0) {
    text_value = 0;
  } else if (error_handle > 0x27) {
    text_value = 0x27;
  } else {
    text_value = error_handle;
  }
  *(int16_t *)(text_widget + 0x40) = text_value;

  *(uint8_t *)(widget + 0x15) = 1;
  if (*(uint8_t *)(widget + 0x13) == 0) {
    *(uint8_t *)(widget + 0x13) = (uint8_t)pause_game;
    if (pause_game == 1) {
      if (*(int16_t *)0x46cc4a < 0) {
        display_assert("widget pause counter is out of whack",
                       "c:\\halo\\SOURCE\\interface\\ui_widget.c", 0x8a9, true);
        system_exit(-1);
      }

      (*(int16_t *)0x46cc4a)++;
      if (!game_time_get_paused()) {
        game_time_set_paused(1);
      }

      if (*(uint8_t *)0x46cc87 == 0 && *(uint8_t *)0x46cc88 == 0) {
        sound_set_music_enabled(1);
        *(uint8_t *)0x46cc87 = 1;
      }
    }
  }

  if (error_handle == 0xd) {
    *(uint8_t *)(widget + 0x16) = 1;
  } else if (error_handle != 0xc) {
    *(uint8_t *)(widget + 0x16) = 0;
    return;
  }

  *(int *)(widget + 0x1c) = 0;
  *(int *)(widget + 0x20) = 0;
}

/* ui_widget_load_error_screen — displays a fatal/abort error overlay that
 * forces the player back to the Xbox dashboard. If allow_abort is true
 * (== 1), the "error_abort_to_dashboard" widget is shown (user can confirm);
 * otherwise "error_abort_to_dashboard_you_have_no_choice" is shown and all
 * existing widgets are closed first. The loaded widget's text-box child
 * receives the error_handle string index at +0x40, its in_game_mode flag
 * (+0x15) is set, and the global "last displayed error" at 0x31e054 is
 * updated. Asserts that the widget's type (+0x0e) is 1 (text box).
 * Source line: 0x90f in ui_widget.c. */
void ui_widget_load_error_screen(int16_t error_handle, int allow_abort)
{
  const char *widget_name;
  void *widget;

  if (allow_abort == 1) {
    widget_name = "ui\\shell\\error\\error_abort_to_dashboard";
  } else {
    widget_name =
      "ui\\shell\\error\\error_abort_to_dashboard_you_have_no_choice";
    if (allow_abort == 0) {
      ui_widgets_close_all();
    }
  }

  widget = ui_widget_load_by_name_or_tag(widget_name, -1, 0, -1, -1, -1, -1);
  if (widget != NULL) {
    if (*(int16_t *)((char *)widget + 0xe) != 1) {
      display_assert("expected a text box widget",
                     "c:\\halo\\SOURCE\\interface\\ui_widget.c", 0x90f, true);
      system_exit(-1);
    }
    *(int16_t *)((char *)widget + 0x40) = error_handle;
    *(uint8_t *)((char *)widget + 0x15) = 1;
    *(int16_t *)0x31e054 = error_handle;
    return;
  }
  error(2, "failed to load '%s' widget", widget_name);
}

bool ui_widgets_process_pause(void)
{
  int stack_index;
  int i;
  int root_widget;
  int pause_ticks;
  int16_t local_player_count;
  int16_t local_player;
  int16_t target_local_player;
  bool network_game;
  bool handled;
  bool target_is_primary;
  const char *widget_name;
  void *gamepad_state;
  void *client;

  handled = false;
  network_game = network_game_in_progress();

  if (game_in_progress() && !cinematic_in_progress() &&
      game_connection() != 3 && *(uint8_t *)0x46cc88 == 0 &&
      dword_46CC44 == 0) {
    for (stack_index = 0; stack_index < 4; stack_index++) {
      if (!input_has_gamepad((int16_t)stack_index) ||
          !local_player_exists((int16_t)stack_index)) {
        continue;
      }

      gamepad_state = input_get_gamepad_state(stack_index);
      if (*(uint8_t *)((char *)gamepad_state + 0x1c) != 1) {
        continue;
      }

      handled = true;
      target_is_primary = true;
      local_player_count = 0;
      target_local_player = -1;

      local_player = local_player_get_next(-1);
      while (local_player != -1) {
        if (local_player == (int16_t)stack_index) {
          target_local_player = (int16_t)stack_index;
          if (local_player_count > 0) {
            target_is_primary = false;
          }
        }
        local_player_count++;
        local_player = local_player_get_next(local_player);
      }

      if (network_game) {
        if (game_engine_allow_pause() &&
            target_local_player == (int16_t)stack_index) {
          root_widget = *(int *)(0x46cc20 + stack_index * 4);
          if (root_widget == 0) {
            client = network_game_client_get();
            network_game_client_get_machine_index(client);
            FUN_00124c40(client);

            switch (local_player_count) {
            case 1:
              widget_name =
                "ui\\shell\\multiplayer_game\\pause_game\\1p_pause_game";
              break;
            case 2:
              widget_name =
                "ui\\shell\\multiplayer_game\\pause_game\\2p_pause_game";
              break;
            case 3:
              if (target_is_primary) {
                widget_name =
                  "ui\\shell\\multiplayer_game\\pause_game\\2p_pause_game";
              } else {
                widget_name =
                  "ui\\shell\\multiplayer_game\\pause_game\\4p_pause_game";
              }
              break;
            case 4:
              widget_name =
                "ui\\shell\\multiplayer_game\\pause_game\\4p_pause_game";
              break;
            default:
              error(2, "invalid local player count for multiplayer game");
              goto done;
            }

            if (ui_widget_load_by_name_or_tag(widget_name, -1, 0, stack_index,
                                              -1, -1, -1) == 0) {
              error(2, "failed to load multiplayer pause game window");
            }
          } else {
            ui_widget_close((void *)root_widget);
          }
        }
      } else {
        if (local_player_count < 0 || local_player_count > 2) {
          error(2, "the ui seems to be confused... assuming you are playing "
                   "full-screen single player?");

          if (*(uint8_t *)0x46cc82 != 0) {
            for (i = 0; i < 4; i++) {
              if (*(int *)(0x46cc20 + i * 4) != 0) {
                ui_widgets_close_all();
                break;
              }
            }
          }

          if (ui_widget_load_by_name_or_tag(
                "ui\\shell\\solo_game\\pause_game\\pause_game", -1, 0,
                stack_index, -1, -1, -1) == 0) {
            error(2, "failed to load full screen pause game window");
          }
          goto done;
        }

        root_widget = *(int *)(0x46cc20 + stack_index * 4);
        if (local_player_count == 2 && root_widget == 0) {
          if (!game_time_get_paused()) {
            if (ui_widget_load_by_name_or_tag(
                  "ui\\shell\\solo_game\\pause_game\\pause_game_split_"
                  "screen",
                  -1, 0, stack_index, -1, -1, -1) == 0) {
              error(2, "failed to load split screen pause game window");
            }
          }
          goto done;
        }

        if (root_widget == 0) {
          if (ui_widget_load_by_name_or_tag(
                "ui\\shell\\solo_game\\pause_game\\pause_game", -1, 0,
                stack_index, -1, -1, -1) == 0) {
            error(2, "failed to load full screen pause game window");
          }
          goto done;
        }

        if (game_time_get_paused()) {
          ui_widgets_close_all();
        }
      }

    done:
      break;
    }
  }

  pause_ticks = dword_46CC44 - 1;
  dword_46CC44 = (((pause_ticks < 0) ? 1 : 0) - 1) & pause_ticks;
  return handled;
}

void *ui_widget_spawn_from_event_handler(void *widget, int tag_index);

typedef struct ui_widget_process_data {
  int16_t unk0;
  int16_t unk2;
  int16_t unk4;
  int16_t unk6;
} ui_widget_process_data_t;

typedef struct ui_widget_deferred_error {
  int16_t error_handle;
  int16_t local_player_index;
  uint8_t a3;
  uint8_t a4;
} ui_widget_deferred_error_t;

/* Pending-load nodes on 0x46cc30..0x46cc3c are pushed by
 *
 * ui_widget_load_by_name_or_tag (0xe84e0) and popped by this helper.
 * The
 * callee expects the queue head in EDI and the output record in ESI. */
typedef struct ui_widget_pending_load {
  int tag_index;
  int a6;
  int16_t a7;
  int16_t widget_stack;
} ui_widget_pending_load_t;


/* process_ui_widgets — main per-frame UI widget tick. Handles async
 * filesystem operations, bink video updates, pre-title screen logic,
 * deferred error display, and the per-stack widget event dispatch loop.
 * Called once per frame from the main loop. */
void process_ui_widgets(void)
{
  uint8_t active_widget_stacks[4];
  ui_widget_pending_load_t pending_load;
  ui_widget_process_data_t process_data;
  ui_widget_deferred_error_t *deferred_error;
  int *widget_roots;
  void *widget_tag;
  int widget;
  void *loaded_widget;
  int stack_index;
  uint8_t any_active_widget_stack;
  uint8_t did_work;
  uint8_t blocked_by_pause;
  uint8_t handled;

  did_work = 0;
  if (*(uint8_t *)0x46cc82 == 0) {
    display_assert("widget_globals.initialized",
                   "c:\\halo\\SOURCE\\interface\\ui_widget.c", 0x284, true);
    system_exit(-1);
  }

  /* Record frame timestamp for event throttling. */
  *(uint32_t *)0x46cc40 = system_milliseconds();

  /* If an async filesystem operation is pending, poll for completion. */
  if (*(int *)0x46cc7c != 0) {
    if (thread_is_done((void *)*(int *)0x46cc7c) != 0) {
      thread_close((void *)*(int *)0x46cc7c);
      *(int *)0x46cc7c = 0;
      ui_widget_set_events_suppressed(false);
      if (*(int16_t *)0x46cc80 == 1) {
        if (bink_playback_has_video()) {
          bink_playback_stop();
        }
        ui_widget_load_error_screen(0x21, 1);
        return;
      }
      if (*(int16_t *)0x46cc80 == 2) {
        if (bink_playback_has_video()) {
          bink_playback_stop();
        }
        ui_widget_load_error_screen(0x22, 1);
        return;
      }
    }
    return;
  }

  /* If UI automation is driving the menu, skip normal processing. */
  if (ui_automation_is_active()) {
    return;
  }

  /* If a bink video is playing, update it and flush events. */
  if (((bool (*)(void))0xf5640)() != 0) {
    ((void (*)(void))0xf6740)();
    event_manager_flush();
    return;
  }

  /* Pre-title screen (language select / content rating). */
  if (event_manager_tab_check()) {
    event_manager_tab_process();
    return;
  }

  /* If a pending error screen load is queued, dispatch it now. */
  if (*(int16_t *)0x46cc68 != -1) {
    ui_widget_load_error_screen(*(int16_t *)0x46cc68, *(uint8_t *)0x46cc6a);
    *(int16_t *)0x46cc68 = -1;
    return;
  }

  /* If any deferred error slots are populated, try to show them. */
  if ((*(int16_t *)0x46cc50 == -1) && (*(int16_t *)0x46cc56 == -1) &&
      (*(int16_t *)0x46cc5c == -1) && (*(int16_t *)0x46cc62 == -1)) {
    /* Normal widget event processing path. */
    blocked_by_pause = ui_widgets_process_pause() != 0;

    active_widget_stacks[0] =
      (*(int *)0x46cc20 != 0) && (*(uint8_t *)(*(int *)0x46cc20 + 0x15) == 1);
    active_widget_stacks[1] =
      (*(int *)0x46cc24 != 0) && (*(uint8_t *)(*(int *)0x46cc24 + 0x15) == 1);
    active_widget_stacks[2] =
      (*(int *)0x46cc28 != 0) && (*(uint8_t *)(*(int *)0x46cc28 + 0x15) == 1);
    active_widget_stacks[3] =
      (*(int *)0x46cc2c != 0) && (*(uint8_t *)(*(int *)0x46cc2c + 0x15) == 1);
    any_active_widget_stack = active_widget_stacks[0] |
                              active_widget_stacks[1] |
                              active_widget_stacks[2] | active_widget_stacks[3];

    widget_roots = (int *)0x46cc20;
    for (stack_index = 0; stack_index < 4; stack_index++, widget_roots++) {
      widget = *widget_roots;
      if (active_widget_stacks[stack_index] == 1) {
        if ((widget == 0) || (*(uint8_t *)(widget + 0x15) != 1)) {
          continue;
        }
      } else if (*(uint8_t *)0x46cc88 == 0) {
        if (widget == 0) {
          continue;
        }
      } else {
        if ((widget == 0) || (any_active_widget_stack != 0)) {
          continue;
        }
      }

      widget_tag = tag_get(0x44654c61, *(int *)widget);
      process_data.unk0 = 0;
      process_data.unk2 = 0;
      process_data.unk4 = 0;
      process_data.unk6 = 0;

      if ((*(uint8_t *)0x46cc85 == 0) &&
          (event_manager_get_next_event(&process_data,
                                        *(uint16_t *)(widget + 8)) != 0)) {
        do {
          handled = 0;
          if (blocked_by_pause == 0) {
            ui_widget_process_event((void *)widget, widget_tag, &process_data,
                                    &handled);
          }
          if ((handled == 1) || (widget != *widget_roots)) {
            break;
          }
        } while (event_manager_get_next_event(&process_data,
                                              *(uint16_t *)(widget + 8)) != 0);
      } else if (blocked_by_pause == 0) {
        process_data.unk2 = *(uint16_t *)(widget + 8);
        handled = 0;
        ui_widget_process_event((void *)widget, widget_tag, &process_data,
                                &handled);
      }

      did_work = 1;
      if ((*widget_roots == 0) && (widget_roots[4] != 0)) {
        ui_widget_pending_load_pop(&widget_roots[4], (void *)&pending_load);
        if (pending_load.tag_index != -1) {
          loaded_widget = ui_widget_load_by_name_or_tag(
            0, pending_load.tag_index, 0, pending_load.widget_stack, -1, -1,
            -1);
          if (loaded_widget != 0) {
            ui_widget_pending_load_apply(pending_load.a6, loaded_widget,
                                         pending_load.a7);
          }
        }
      }
    }

    if (did_work != 0) {
      event_manager_flush();
      return;
    }
    return;
  }

  /* Deferred error display: wait for game_in_progress and enough
   * ticks before showing queued error dialogs. */
  deferred_error = (ui_widget_deferred_error_t *)0x46cc50;
  while ((int)deferred_error < 0x46cc68) {
    if (deferred_error->error_handle != -1) {
      if ((*(uint8_t *)0x46cc88 == 0) && (!network_game_in_progress()) &&
          (game_time_get() < 0x1e)) {
        error(2, "waiting for %d ticks before displaying deferred errors",
              0x1e);
      } else {
        ui_widget_display_error(
          deferred_error->error_handle, deferred_error->local_player_index,
          (char)deferred_error->a3, (char)deferred_error->a4);
        deferred_error->error_handle = -1;
      }
    }
    deferred_error++;
  }
}

/**
 * Clears the last error index by resetting it to -1 (no error).
 * The global at 0x31e4c0 tracks which error was most recently displayed
 * by the UI widget error system.
 */
void ui_widget_clear_last_error_index(void)
{
  *(int *)0x31e4c0 = -1;
}

/* event_controller_index_compatible_with_widget (0xe3b80) — readable C lift. */
bool event_controller_index_compatible_with_widget(void *widget, void *event_data)
{
  int16_t idx = *(int16_t *)((char *)event_data + 8);

  if (idx == (int16_t)0xffff) {
    return true;
  }
  if (idx == *(int16_t *)((char *)widget + 2)) {
    return true;
  }
  return false;
}

/* set_ui_plasma_effect_color (0xe3bb0) — readable C lift. */
void set_ui_plasma_effect_color(float r, float g, float b, float a)
{
  *(float *)0x5aa460 = r;
  *(float *)0x5aa464 = g;
  *(float *)0x5aa468 = b;
  *(float *)0x5aa46c = a;
}

/* ui_widgets_set_fade_value (0xe3c90) — readable C lift. */
void ui_widgets_set_fade_value(float fade)
{
  *(float *)0x46cc4c = fade;
}

void ui_widget_debug_show_path(char show)
{
  *(char *)0x46cc84 = show;
}

/* widget_instance_count_children (0xe3cb0) — readable C lift. */
int widget_instance_count_children(void *widget)
{
  int count = 0;
  void *child;

  if (widget == NULL) {
    return 0;
  }
  child = *(void **)((char *)widget + 0x34);
  if (child == NULL) {
    return 0;
  }
  do {
    child = *(void **)((char *)child + 0x2c);
    count++;
  } while (child != NULL);
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

/* widget_free (0xe3d50) — readable C lift. */
void widget_free(void *block)
{
  stack_memory_pool_deallocate(*(void **)0x31e04c, block);
}

/* ui_widgets_active (0xe3d70) — readable C lift. */
char ui_widgets_active(void)
{
  unsigned int *p;
  if (!*(char *)0x46cc82) return 0;
  for (p = (unsigned int *)0x46cc20; p < (unsigned int *)0x46cc30; p++) {
    if (*p != 0) return 1;
  }
  return 0;
}

/* ui_widgets_active_for_local_player (0xe3da0) — readable C lift. */
char ui_widgets_active_for_local_player(int16_t local_player_index)
{
  int *slot;
  void *widget;

  if (local_player_index < 0 || local_player_index >= 4) {
    display_assert((const char *)0x2832b0, (const char *)0x283280, 0x456, 1);
    system_exit(-1);
  }
  if (*(unsigned char *)0x46cc82 == 0)
    return 0;
  for (slot = (int *)0x46cc20; (unsigned)slot < 0x46cc30u; slot++) {
    widget = (void *)*slot;
    if (widget != 0 && *(int16_t *)((char *)widget + 8) == local_player_index)
      return 1;
  }
  return 0;
}

/* FUN_000e3e60 (0xe3e60) — readable C lift from XBE leaf.
 * fmod(a * b * *(float*)0x255ef8, *(double*)0x2573d8) via x87 FPREM. */
float FUN_000e3e60(int a, float b)
{
  float scaled;

  scaled = b * *(float *)0x255ef8 * (float)a;
  return x87_fmod(scaled, *(double *)0x2573d8);
}

/* widget_instance_get_child_index_from_parent (0xe4330) — readable C lift from XBE leaf. */
int widget_instance_get_child_index_from_parent(void *widget)
{
  void *parent;
  void *child;
  int index;

  parent = *(void **)((char *)widget + 0x30);
  index = -1;
  if (parent == NULL) {
    return index;
  }
  child = *(void **)((char *)parent + 0x34);
  index = 0;
  if (child == NULL) {
    return -1;
  }
  for (;;) {
    if (child == widget) {
      return index;
    }
    child = *(void **)((char *)child + 0x2c);
    index++;
    if (child == NULL) {
      return -1;
    }
  }
}

/* widget_instance_set_visibility_recursive (0xe4370) — readable C lift from XBE leaf. */
void widget_instance_set_visibility_recursive(void *widget, char visible)
{
  extern char DAT_002832a8[];
  extern char DAT_00283280[];
  void *child;

  if (widget == 0) {
    display_assert(DAT_002832a8, DAT_00283280, 0x743, true);
    system_exit(-1);
  }
  *((unsigned char *)widget + 0x10) = (unsigned char)visible;
  for (child = *(void **)((char *)widget + 0x34); child != 0;
       child = *(void **)((char *)child + 0x2c)) {
    widget_instance_set_visibility_recursive(child, visible);
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

/* ui_set_next_level (0xe4420) — readable C lift. */
void ui_set_next_level(int16_t level_index)
{
  int idx = (int16_t)level_index;
  if (idx == -1) {
    main_roll_credits();
    return;
  }
  if (idx < 0 || idx > 9) {
    error(2, (const char *)0x283318);
    main_goto_main_menu();
    return;
  }
  main_set_map_name(main_get_solo_level_name(level_index));
  main_disallow_persistent_storage();
}

/* display_error_deferred (0xe4500) — readable C lift. */
void display_error_deferred(int16_t error_handle, int16_t local_player_index, char a3, char a4)
{
  int slot;
  int idx;

  if (local_player_index == (int16_t)-1)
    slot = 0;
  else {
    slot = (int)local_player_index;
    if (slot < 0 || slot >= 4) {
      display_assert((const char *)0x283424, (const char *)0x283280, 0x8f0, 1);
      system_exit(-1);
    }
  }
  idx = slot * 6;
  if (*(int16_t *)(0x46cc50 + idx) != (int16_t)-1) {
    error(2, (const char *)0x2833d0, slot);
    return;
  }
  *(int16_t *)(0x46cc50 + idx) = error_handle;
  *(int16_t *)(0x46cc52 + idx) = local_player_index;
  *(char *)(0x46cc54 + idx) = a3;
  *(char *)(0x46cc55 + idx) = a4;
}

/* display_error_abort_to_dashboard_deferred (0xe4590) — readable C lift. */
void display_error_abort_to_dashboard_deferred(short error_handle, char flag)
{
  if (*(short *)0x46cc68 != (short)-1) {
    return;
  }
  *(short *)0x46cc68 = error_handle;
  *(char *)0x46cc6a = flag;
}

/* ui_widget_link_child (0xe4800) — readable C lift from XBE leaf. */
void ui_widget_link_child(void *parent, void *child)
{
  void *iter;
  void *last;

  if (*(void **)((char *)child + 0x28) != 0 ||
      *(void **)((char *)child + 0x2c) != 0) {
    display_assert((const char *)0x283588, (const char *)0x283280, 0xa9f, 1);
    system_exit(-1);
  }
  iter = *(void **)((char *)parent + 0x34);
  if (iter == 0) {
    *(void **)((char *)parent + 0x34) = child;
    return;
  }
  last = 0;
  while (iter != 0) {
    last = iter;
    iter = *(void **)((char *)iter + 0x2c);
  }
  if (last == 0) {
    *(void **)((char *)parent + 0x34) = child;
    return;
  }
  if (*(void **)((char *)last + 0x2c) != 0) {
    display_assert((const char *)0x28356c, (const char *)0x283280, 0xaa9, 1);
    system_exit(-1);
  }
  *(void **)((char *)last + 0x2c) = child;
  *(void **)((char *)child + 0x28) = last;
}




/* widget_instance_get_opacity_product (0xe4960) — readable C lift. */
float widget_instance_get_opacity_product(void *widget)
{
  float product;
  char *node;

  node = (char *)widget;
  product = *(float *)(node + 0x24);
  node = *(char **)(node + 0x30);
  while (node) {
    product *= *(float *)(node + 0x24);
    node = *(char **)(node + 0x30);
  }
  return product;
}

/* widget_instance_is_visible_in_parent_chain (0xe4980) — readable C lift from XBE leaf. */
char widget_instance_is_visible_in_parent_chain(void *widget)
{
  void *parent;
  void *tag;
  void *parent_tag;
  char ok;
  int16_t kind;

  if (*(char *)((char *)widget + 0x12) != 0) {
    return 0;
  }
  parent = *(void **)((char *)widget + 0x30);
  if (parent == (void *)0) {
    return 1;
  }
  tag = tag_get(0x44654c61, *(int *)parent);
  ok = 1;
  while (parent != (void *)0 && ok) {
    parent_tag = tag_get(0x44654c61, *(int *)parent);
    if ((*(char *)((char *)tag + 0x2c) & 1) == 0) {
      kind = *(int16_t *)((char *)parent + 0xe);
      if (kind != 2 && kind != 3) {
        ok = 0;
      } else {
        ok = 1;
      }
    } else {
      ok = 1;
    }
    parent = *(void **)((char *)parent + 0x30);
    tag = parent_tag;
  }
  return ok;
}

/* widget_instance_parent_allows_focus (0xe4a40) — readable C lift from XBE leaf. */
char widget_instance_parent_allows_focus(void *widget /* @<eax> */)
{
  char *w;
  char *parent;
  char *ancestor;
  char result;
  int16_t typ;

  w = (char *)widget;
  parent = *(char **)(w + 0x30);
  if (parent == NULL) {
    return 1;
  }
  if (*(char **)(parent + 0x38) == w) {
    return 1;
  }
  result = 0;
  for (;;) {
    ancestor = *(char **)(parent + 0x30);
    if (ancestor == NULL) {
      return result;
    }
    if (*(char **)(ancestor + 0x38) != parent) {
      return result;
    }
    typ = *(int16_t *)(ancestor + 0xe);
    if (typ == 2 || typ == 3) {
      result = 1;
    } else {
      result = 0;
    }
    parent = ancestor;
  }
}

/* ui_widget_find_localized_string_index (0xe4a80) — readable C lift. */
int16_t ui_widget_find_localized_string_index(const wchar_t *key /* @<ebx> */)
{
  int16_t i;
  const wchar_t *entry;
  size_t n;

  for (i = 0; i < 0x28; i++) {
    entry = *(const wchar_t **)(0x31e098 + (int)i * 4);
    n = _wcslen(entry);
    if (__wcsnicmp(key, entry, n) == 0)
      return i;
  }
  return -1;
}

/* FUN_000e4c70 (0xe4c70) — readable C lift from XBE leaf.
 * draw_state@<edi>, cursor@<ebx>, string_index on stack. */
void FUN_000e4c70(void *draw_state /*@<edi>*/, void *cursor /*@<ebx>*/, int string_index)
{
  short height;
  short bounds[4];

  height = (short)(*(short *)((char *)draw_state + 2) - *(short *)((char *)cursor + 2));
  if (height < 0) {
    error(2, (const char *)0x2835f0);
    if (height < 0)
      height = 0;
  }
  draw_string_set_indents((int)height, 0);
  FUN_0019cdb0((short *)cursor, (void *)(uintptr_t)(unsigned int)string_index, bounds,
               (short *)draw_state);
  *(short *)((char *)draw_state + 2) =
      (short)(*(short *)((char *)draw_state + 2) - 3);
  bounds[1] = *(short *)((char *)cursor + 2);
  rasterizer_draw_string((void *)0, bounds, (const void *)0, 0,
                         (unsigned short *)(uintptr_t)(unsigned int)string_index);
  *(short *)cursor = *(short *)draw_state;
}


/* ui_widget_match_localized_substring (0xe4ce0) — readable C lift from XBE leaf. */
char ui_widget_match_localized_substring(wchar_t *text)
{
  extern char DAT_0027b838[];
  extern char DAT_00283280[];
  wchar_t *p;

  if (text == 0) {
    display_assert(DAT_0027b838, DAT_00283280, 0x1055, true);
    system_exit(-1);
    return 0;
  }
  for (;;) {
    p = _wcschr(text, 0x25);
    if (p == 0)
      return 0;
    p = p + 1; /* skip L'%' */
    if (ui_widget_find_localized_string_index(p) != (int16_t)0xffff)
      return 1;
    text = p;
    if (text == 0)
      return 0;
  }
}

/* ui_widget_player_prefers_metric_units (0xe4d40) — readable C lift from XBE leaf. */
char ui_widget_player_prefers_metric_units(int16_t player_index)
{
  char prefs[0x18];
  short v;

  if (player_index == -1)
    player_index = local_player_get_next(-1);
  csmemset(prefs, 0, 0x18);
  if (player_index != -1)
    input_abstraction_get_local_player_preferences(player_index, prefs);
  v = *(short *)(prefs + 0x14);
  v = (short)(v - 1);
  if (v == 0)
    return 1;
  v = (short)(v - 2);
  if (v == 0)
    return 1;
  return 0;
}



/* get_ui_rgb_white (0xe54e0) — readable C lift. */
void get_ui_rgb_white(float *out)
{
  out[0] = *(float *)0x31e148;
  out[1] = *(float *)0x31e14c;
  out[2] = *(float *)0x31e150;
}

/* get_ui_argb_white (0xe5530) — readable C lift. */
void get_ui_argb_white(float *out)
{
  float *src = *(float **)0x2ee6c4;
  out[0] = src[0];
  out[1] = *(float *)0x31e148;
  out[2] = *(float *)0x31e14c;
  out[3] = *(float *)0x31e150;
}

void __stdcall ui_widget_filesystem_check_thread_proc(int unused)
{
  (void)unused;
  saved_game_perform_file_system_checks();
  if (*(int16_t *)0x46cc80 == 0) {
    FUN_001c26b0(0, 0, 0);
    FUN_001c0d50(0, 0, 0, 0);
    player_ui_get_player1_last_used_profile_index();
  }
}

/* modulate_pixel32_by_real_alpha (0xe55e0) — readable C lift. */
unsigned int modulate_pixel32_by_real_alpha(unsigned int pixel, float alpha)
{
  int a_byte = (int)(pixel >> 24);
  float scaled;
  int na;
  scaled = (float)a_byte;
  if (a_byte < 0)
    scaled += 4294967296.0f;
  scaled *= alpha;
  __asm__ volatile ("flds %1; fistpl %0" : "=m"(na) : "m"(scaled) : "st");
  return (pixel & 0x00ffffffu) | ((unsigned int)na << 24);
}



/* ui_widgets_close_stack_for_player (0xe5910) — readable C lift. */
void ui_widgets_close_stack_for_player(int16_t player_index)
{
  void **slot;
  void *widget;
  void *block;
  if ((int16_t)player_index < 0 || (int16_t)player_index >= 4) {
    display_assert((const char *)0x2832b0, (const char *)0x283280, 0x482, 1);
    system_exit(-1);
  }
  for (slot = (void **)0x46cc30; (uintptr_t)slot < 0x46cc40; slot++) {
    widget = *(void **)((char *)slot - 0x10);
    if (widget == 0 || *(int16_t *)((char *)widget + 8) != (int16_t)player_index)
      continue;
    ui_widget_close(widget);
    if (*slot == 0)
      continue;
    while (*slot != 0) {
      block = *slot;
      *slot = *(void **)((char *)block + 0xc);
      stack_memory_pool_deallocate(*(void **)0x31e04c, block);
    }
  }
}

/* ui_widgets_pop_stack (0xe59e0) — readable C lift. */
void ui_widgets_pop_stack(int16_t player_index)
{
  int idx;
  int *head;
  char record[12];

  idx = (int)player_index;
  if (player_index == -1)
    idx = 0;
  else if (player_index < 0 || player_index >= 4) {
    display_assert((const char *)0x282750, (const char *)0x283280, 0x4b4, 1);
    system_exit(-1);
  }
  head = (int *)(0x46cc30 + idx * 4);
  if (*head != 0)
    ui_widget_pending_load_pop(head, record);
}

/* main_screen_shell_begin_fade (0xe5a40) — readable C lift. */
void main_screen_shell_begin_fade(int fade_duration)
{
  int *slot;
  char *widget;
  void *rec;
  void *next;

  ui_widget_stop_attract_mode();
  for (slot = (int *)0x46cc20; (unsigned)slot < 0x46cc30u; slot++) {
    widget = (char *)*slot;
    if (widget == 0)
      continue;
    if (widget[0x15] != 0)
      continue;
    *(int *)(widget + 0x20) = fade_duration;
    *(int *)(widget + 0x1c) = *(int *)0x46cc40 - *(int *)(widget + 0x18) + 0x64;
    rec = (void *)slot[4];
    while (rec != 0) {
      next = *(void **)((char *)rec + 0xc);
      slot[4] = (int)next;
      stack_memory_pool_deallocate(*(void **)0x31e04c, rec);
      rec = (void *)slot[4];
    }
  }
}

/* ui_play_audio_feedback_sound (0xe5ab0) — readable C lift from XBE leaf. */
void ui_play_audio_feedback_sound(int16_t sound_selector)
{
  extern char DAT_0028380c[];
  extern char DAT_002837f4[];
  extern char DAT_002837e0[];
  extern char DAT_002837c4[];
  const char *name;
  int tag_index;
  unsigned int idx;

  idx = (unsigned int)((int)sound_selector - 1);
  if (idx > 3) {
    return;
  }
  if (idx == 0) {
    name = DAT_0028380c;
  } else if (idx == 1) {
    name = DAT_002837f4;
  } else if (idx == 2) {
    name = DAT_002837e0;
  } else {
    name = DAT_002837c4;
  }
  tag_index = tag_loaded(0x736e6421, name);
  if (tag_index == -1) {
    return;
  }
  sound_impulse_start(tag_index, 1.0f);
}




/* FUN_000e76b0 (0xe76b0) — readable C lift: draw widget children with opacity. */
void FUN_000e76b0(void *widget, void *tag, void *bounds, float opacity_scale, int param_5, int param_6)
{
  void *draw_child = *(void **)((char *)widget + 0x48);
  void *parent; float opacity; void *child; int i; char selected;
  if (draw_child != 0) {
    parent = *(void **)((char *)widget + 0x30);
    opacity = *(float *)((char *)widget + 0x24);
    while (parent != 0) { opacity *= *(float *)((char *)parent + 0x24); parent = *(void **)((char *)parent + 0x30); }
    *(float *)((char *)draw_child + 0x24) = opacity;
    FUN_000e73c0(draw_child, bounds, opacity_scale, 0, 1);
  }
  if ((*((unsigned char *)tag + 0x150) & 1) != 0) {
    child = *(void **)((char *)widget + 0x34);
    for (i = 0; child != 0; child = *(void **)((char *)child + 0x2c), i++) {
      if (i >= *(unsigned short *)((char *)widget + 0x44)) break;
      selected = (i == *(short *)((char *)widget + 0x3c));
      FUN_000e73c0(child, bounds, opacity_scale, param_5, selected);
    }
  }
  *(short *)((char *)widget + 0x3e) = 0;
}

/* network_game_reset_to_pregame_ui (0xe8830) — readable C lift. */
void network_game_reset_to_pregame_ui(void)
{
  extern char DAT_00284370[];
  extern char DAT_00284338[];
  extern char DAT_002842d8[];
  extern char DAT_002842ac[];
  extern char DAT_00284250[];
  extern char DAT_002828e0[];
  extern char DAT_00284220[];
  void *w;

  ui_widgets_close_all();
  if (network_game_is_splitscreen_local()) {
    if (FUN_0012a1a0()) {
      w = ui_widget_load_by_name_or_tag(DAT_00284370, -1, 0, -1, -1, -1, -1);
      if (w == 0)
        error(2, DAT_00284338);
    } else {
      w = ui_widget_load_by_name_or_tag(DAT_002842d8, -1, 0, -1, -1, -1, -1);
      if (w == 0)
        error(2, DAT_002842ac);
    }
    return;
  }
  if (network_game_server_get()) {
    network_game_server_pause_countdown(network_game_server_get(), 1);
    w = ui_widget_load_by_name_or_tag(DAT_00284250, -1, 0, -1, -1, -1, -1);
    if (w == 0)
      error(2, DAT_002842ac);
    return;
  }
  w = ui_widget_load_by_name_or_tag(DAT_002828e0, -1, 0, -1, -1, -1, -1);
  if (w == 0)
    error(2, DAT_00284220);
}

/* FUN_000e9a60 (0xe9a60) — readable C lift. */
char FUN_000e9a60(void *widget)
{
  csmemset((void *)0x46cce8, 0, 0x50);
  *(int *)((char *)widget + 0x40) = 0;
  *(unsigned short *)((char *)widget + 0x44) = 0;
  return 1;
}

/* ui_widget_event_handler_set_difficulty (0xe9bd0) — readable C lift. */
char ui_widget_event_handler_set_difficulty(void *widget, void *event_data, bool *widget_deleted)
{
  short difficulty;

  (void)event_data;
  (void)widget_deleted;
  difficulty = *(short *)((char *)widget + 0x3c);
  if (difficulty < 0 || difficulty >= 4) {
    display_assert((const char *)0x285ad8, (const char *)0x2859a4, 0x313, 1);
    system_exit(-1);
  }
  main_set_difficulty(difficulty);
  ui_play_audio_feedback_sound(2);
  return 1;
}

/* display_error_abort_to_dashboard (0xe9cb0) — readable C lift. */
extern char DAT_002859a4[];
extern char DAT_00285b10[];
char display_error_abort_to_dashboard(void *widget)
{
  if (*(int16_t *)((char *)widget + 8) == -1) {
    display_assert(DAT_00285b10, DAT_002859a4, 0x369, true);
    system_exit(-1);
  }
  player_ui_local_player_joined_multiplayer_game(*(int16_t *)((char *)widget + 8));
  return 1;
}

/* FUN_000E9D40 (0xe9d40) — readable C lift. */
char FUN_000E9D40(void)
{
  char ok;
  void *server;

  ok = 1;
  dispose_global_network_game_server();
  player_ui_clear_multiplayer_variant();
  network_game_set_accept_remote_connections(1);
  if (network_game_server_get() == 0) {
    game_engine_playlist_initialize();
    ok = FUN_0012a890();
    if (ok == 1) {
      server = network_game_server_get();
      network_game_server_pause_countdown(server, 1);
      game_engine_playlist_begin();
      set_game_connection(2);
    }
    if (ok == 0) {
      dispose_global_network_game_client();
      dispose_global_network_game_server();
      network_game_set_accept_remote_connections(0);
      player_ui_clear_multiplayer_variant();
      error(2, (const char *)0x2828ac);
      return ok;
    }
  }
  if (network_game_client_get() == 0) {
    ok = FUN_0012a250();
  }
  if (ok != 0) {
    return ok;
  }
  dispose_global_network_game_client();
  dispose_global_network_game_server();
  network_game_set_accept_remote_connections(0);
  player_ui_clear_multiplayer_variant();
  error(2, (const char *)0x2828ac);
  return ok;
}
/* FUN_000e9fd0 (0xe9fd0) — readable C lift. */
char FUN_000e9fd0(void *widget)
{
  *(int *)((char *)widget + 0x40) = 0;
  *(int16_t *)((char *)widget + 0x44) = 0;
  return 1;
}

/* FUN_000ea1f0 (0xea1f0) — readable C lift from XBE leaf. */
char FUN_000ea1f0(void *widget)
{
  *(int *)((char *)widget + 0x40) = 0;
  *(int16_t *)((char *)widget + 0x44) = 0;
  return 1;
}

char FUN_000ea540(void *widget)
{
  void *p = *(void **)((char *)widget + 0x40);
  if (p) {
    widget_free(p);
    *(void **)((char *)widget + 0x40) = 0;
  }
  *(unsigned short *)((char *)widget + 0x44) = 0;
  return 1;
}

/* split_screen_game_initialize (0xea810) — readable C lift. */
char split_screen_game_initialize(void *widget, void *player_data)
{
  void *net;
  short local_idx;
  int i;
  char *slot;
  unsigned int copy[8];
  void *client;

  (void)widget;
  if (player_data == 0) {
    display_assert((const char *)0x286184, (const char *)0x2859a4, 0x624, 1);
    system_exit(-1);
  }
  net = (void *)FUN_0012a0a0();
  if (net == 0 || *((unsigned char *)net + 0xc0) != 1) {
    return 1;
  }
  local_idx = network_game_client_get_local_machine_index();
  if (local_idx == (short)0xffff) {
    return 1;
  }
  slot = (char *)net + 0x242;
  for (i = 0; i < 0x10; i++) {
    if (network_player_is_valid(slot - 0x1c)
        && *(signed char *)slot == (signed char)local_idx
        && *(signed char *)(slot + 1) == *(short *)((char *)player_data + 2)) {
      break;
    }
    slot += 0x20;
  }
  if (i >= 0x10) {
    return 1;
  }
  __builtin_memcpy(copy, (char *)net + 0x226 + (i * 0x20), 0x20);
  if (*((unsigned char *)copy + 0x1e) == 0) {
    *((unsigned char *)copy + 0x1e) = 1;
  } else {
    *((unsigned char *)copy + 0x1e) = 0;
  }
  client = network_game_client_get();
  if (!network_game_client_update_local_player_data(client, copy)) {
    error(2, (const char *)0x286150);
  }
  return 1;
}

char FUN_000eab70(void *widget)
{
  void *p = *(void **)((char *)widget + 0x40);
  if (p) {
    widget_free(p);
    *(void **)((char *)widget + 0x40) = 0;
  }
  *(unsigned short *)((char *)widget + 0x44) = 0;
  return 1;
}

/* FUN_000ecd50 (0xecd50) — readable C lift: sync playlist widget selection. */
char FUN_000ecd50(void *widget)
{
  extern char DAT_002859a4[];
  extern char DAT_00287ab0[];
  extern char DAT_00286550[];
  void *profile;
  int mode;
  short idx;

  profile = player_ui_get_edit_playlist_profile();
  if (*(short *)((char *)widget + 0xe) != 3) {
    display_assert(DAT_00287ab0, DAT_002859a4, 0xab2, true);
    system_exit(-1);
  }
  if (profile == 0) {
    error(2, DAT_00286550);
    return 0;
  }
  mode = *(int *)((char *)profile + 0x18);
  switch (mode) {
  case 2:
    idx = 2;
    break;
  case 3:
    idx = 3;
    break;
  case 4:
    idx = 1;
    break;
  case 5:
    idx = 4;
    break;
  default:
    idx = 0;
    break;
  }
  *(short *)((char *)widget + 0x3c) = idx;
  *(void **)((char *)widget + 0x38) = widget_instance_get_nth_child(widget, idx);
  return 1;
}

/* playlist_profile_change_koth_rules (0xece10) — readable C lift. */
char playlist_profile_change_koth_rules(void *widget)
{
  void *profile;
  void *buf;

  if (*(short *)((char *)widget + 0xe) != 1) {
    display_assert((const char *)0x287af0, (const char *)0x2859a4, 0xad2, 1);
    system_exit(-1);
  }
  profile = player_ui_get_edit_playlist_profile();
  if (profile == 0) {
    error(2, (const char *)0x286550);
    return 0;
  }
  buf = ui_widget_realloc(*(int *)((char *)widget + 0x3c), 0x100,
                          (const char *)0x2859a4, 0xad6);
  *(void **)((char *)widget + 0x3c) = buf;
  if (buf != 0) {
    ustrncpy((wchar_t *)buf, (wchar_t *)profile, 0x7f);
    *(unsigned short *)((char *)buf + 0xfe) = 0;
  }
  return 1;
}

/* FUN_000ea010 (0xea010) — readable C lift. */
char FUN_000ea010(void)
{
  char ok;

  network_game_set_accept_remote_connections(0);
  ok = 1;
  if (network_game_server_get() == 0) {
    game_engine_playlist_initialize();
    ok = FUN_0012a890() ? 1 : 0;
    if (ok == 1) {
      game_engine_playlist_begin();
      set_game_connection(2);
    }
  }
  if (ok != 0) {
    if (network_game_client_get() == 0) {
      ok = FUN_0012a250() ? 1 : 0;
    }
  }
  if (ok == 0) {
    dispose_global_network_game_client();
    dispose_global_network_game_server();
    player_ui_clear_multiplayer_variant();
    error(2, (const char *)0x285d48);
  }
  return ok;
}

/* FUN_000ea100 (0xea100) — readable C lift. */
char FUN_000ea100(void *widget)
{
  void *tag;
  char map_name[256];
  short i;

  tag = tag_get(0x44654c61, *(int *)widget);
  if (*(short *)tag != 2) {
    display_assert((const char *)0x285db8, (const char *)0x2859a4, 0x4cc, 1);
    system_exit(-1);
  }
  if (*(int *)((char *)tag + 0x3e0) != 3) {
    display_assert((const char *)0x285d78, (const char *)0x2859a4, 0x4cd, 1);
    system_exit(-1);
  }
  *(void **)((char *)widget + 0x40) = (void *)0x31e4c8;
  *(short *)((char *)widget + 0x44) = 0xd;
  if (!saved_game_file_retrieve_last_used_multiplayer_map(map_name)) {
    return 1;
  }
  *(short *)((char *)widget + 0x3c) = 0;
  for (;;) {
    i = *(short *)((char *)widget + 0x3c);
    if (crt_stricmp(map_name, *(const char **)(0x31e4c8 + i * 4)) == 0) {
      break;
    }
    *(short *)((char *)widget + 0x3c) = (short)(i + 1);
    if (*(short *)((char *)widget + 0x3c) >= 0xd) {
      break;
    }
  }
  if (*(short *)((char *)widget + 0x3c) == 0xd) {
    *(short *)((char *)widget + 0x3c) = 0;
  }
  return 1;
}

/* FUN_000eceb0 (0xeceb0) — readable C lift (restored pre-naked). */


char FUN_000eceb0(void *widget)
{
  void *list_widget;
  void *item_widget;
  void *sibling;
  int16_t team_index;
  void *profile;

  profile = *(void **)0x31e494;
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


/* --- ui_widget.obj batch2 drafts (2026-07-26) --- */

static __attribute__((unused)) void *ui_widget_find_child_type(void *list_widget, int16_t type)
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

static __attribute__((unused)) void *ui_widget_get_playlist_profile(void)
{
  return *(void **)0x31e494;
}

static __attribute__((unused)) void ui_widget_assert_fail(const char *msg, unsigned line)
{
  display_assert(msg, (char *)0x2859a4, line, 1);
  system_exit(-1);
}

static __attribute__((unused)) wchar_t *ui_widget_wcsstr(const wchar_t *haystack, const wchar_t *needle)
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

static __attribute__((unused)) wchar_t *ui_widget_wcschr(wchar_t *s, wchar_t c)
{
  while (*s != 0) {
    if (*s == c)
      return s;
    s++;
  }
  return NULL;
}

static __attribute__((unused)) void ui_widget_wcscpy(wchar_t *dest, const wchar_t *src)
{
  while (*src != 0) {
    *dest = *src;
    dest++;
    src++;
  }
  *dest = 0;
}

static __attribute__((unused)) void ui_widget_read_draw_color(float color[4])
{
  color[0] = *(float *)0x4d9b18;
  color[1] = *(float *)0x4d9b1c;
  color[2] = *(float *)0x4d9b20;
  color[3] = *(float *)0x4d9b24;
}

/* draw_bitmap_in_rect (0xe3e80) — readable C lift (restored pre-naked). */


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


/* FUN_000e4ad0 (0xe4ad0) — readable C lift (restored pre-naked). */


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



/* remap_sticks_for_local_player (0xe4da0) — readable C lift.
 * Jump-table on icon_type 0x10..0x1f: 0x10/0x1e and 0x11/0x1f remap by
 * metric preference; other stick icons pass through. */
int16_t remap_sticks_for_local_player(int16_t icon_type, int local_player_index)
{
  int16_t index;
  unsigned u = (unsigned)icon_type;

  if (u < 0x10u || u > 0x1fu)
    return icon_type;

  switch (u) {
  case 0x10:
  case 0x1e:
    index = ui_widget_find_localized_string_index((wchar_t *)0x283038);
    if (index != 0x10) {
      display_assert((char *)0x283698, (char *)0x283280, 0x1093, 1);
      system_exit(-1);
    }
    index = ui_widget_find_localized_string_index((wchar_t *)0x282f04);
    if (index != 0x1e) {
      display_assert((char *)0x283678, (char *)0x283280, 0x1094, 1);
      system_exit(-1);
    }
    if (ui_widget_player_prefers_metric_units((int16_t)local_player_index))
      return 0x10;
    return 0x11;
  case 0x11:
  case 0x1f:
    index = ui_widget_find_localized_string_index((wchar_t *)0x283020);
    if (index != 0x11) {
      display_assert((char *)0x283654, (char *)0x283280, 0x109a, 1);
      system_exit(-1);
    }
    index = ui_widget_find_localized_string_index((wchar_t *)0x282ef8);
    if (index != 0x1f) {
      display_assert((char *)0x283634, (char *)0x283280, 0x109b, 1);
      system_exit(-1);
    }
    if (ui_widget_player_prefers_metric_units((int16_t)local_player_index))
      return 0x11;
    return 0x12;
  default:
    return icon_type;
  }
}


/* FUN_000e5180 (0xe5180) — readable C lift (restored pre-naked). */


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


/* FUN_000e5b10 (0xe5b10) — readable C lift (restored pre-naked). */

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

/* draw_string_and_hack_in_icons (0xe5de0) — readable C lift (restored pre-naked). */


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


/* FUN_000e6140 (0xe6140) — readable C lift (restored pre-naked). */
void FUN_000e6140(void *widget /*  */, void *draw_state /*  */)
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
/* FUN_000e6450 (0xe6450) — readable C lift (restored pre-naked). */
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






/* FUN_000e73c0 (0xe73c0) — Capstone tip: no child draw list → return. */
void FUN_000e73c0(uintptr_t widget, uintptr_t bounds, float opacity_scale, char param_4, char visible)
{
  (void)widget; (void)bounds; (void)opacity_scale; (void)param_4; (void)visible;
  return;
}


/* render_ui_widgets_postgame (0xe7760) — readable C lift. */
void render_ui_widgets_postgame(int16_t local_player_index, int16_t *bounds)
{
  /* Stack image: dword slot 0 == ebp-0x58; slot 4 == ebp-0x48 (first inited word). */
  int32_t slots[0x58 / 4];
  int16_t *w;
  int16_t player;
  int16_t i;
  void *widget;
  int16_t widget_player;
  int16_t nlocal;
  int16_t local_bounds[4];
  float opacity;
  int idx;

  for (i = 0; i < (int16_t)(sizeof(slots) / 4); i++)
    slots[i] = 0;
  w = (int16_t *)(slots + 4);
  w[0x16 / 2] = 0xf0;
  w[0x26 / 2] = 0xf0;
  w[0x28 / 2] = 0x140;
  w[0x2a / 2] = 0xf0;
  w[0x34 / 2] = 0x140;
  w[0x3a / 2] = 0xf0;
  w[0x3c / 2] = 0x140;
  w[0x3e / 2] = 0xf0;

  if (FUN_000f5640())
    return;

  player = local_player_index;
  if (player < 0)
    player = 0;
  else if (player > 3)
    player = 3;

  for (i = 0; i < 4; i++) {
    widget = *(void **)(0x46cc20 + (int)i * 4);
    if (widget == 0)
      continue;
    if (*(uint8_t *)((char *)widget + 0x11) == 1)
      goto render;
    widget_player = *(int16_t *)((char *)widget + 8);
    if (*(uint8_t *)((char *)widget + 0x15) == 1) {
      if (widget_player == player || widget_player == (int16_t)0xffff ||
          player == (int16_t)-1 || *(uint8_t *)0x46cc88 != 0)
        goto render;
      continue;
    }
    if (widget_player == (int16_t)0xffff) {
      if (i == 0)
        goto render;
    }
    if (widget_player != player)
      continue;
  render:
    local_bounds[0] = 0;
    local_bounds[1] = 0;
    local_bounds[2] = (int16_t)(bounds[2] - bounds[0]);
    local_bounds[3] = (int16_t)(bounds[3] - bounds[1]);
    nlocal = local_player_count();
    idx = (int)player + (int)nlocal * 4;
    opacity = *(float *)&slots[idx];
    FUN_000e73c0(widget, local_bounds, opacity, 1, 0);
  }
}

/* FUN_000e98c0 (0xe98c0) — readable C lift (restored pre-naked) — hand-lifted from delinked 000e98c0.obj. */
char FUN_000e98c0(void *widget)
{
  char profile0[0x30];
  char profile1[0x30];
  int16_t level0;
  int16_t difficulty0;
  int16_t level1;
  int16_t difficulty1;
  int index;
  void *tag;
  int16_t level;
  unsigned char bits;

  csmemset((void *)0x46cce8, 0, 0x50);
  player_ui_get_active_player_profile(0, profile0);
  player_profile_save_last_level_played(profile0, &level0, &difficulty0);
  player_ui_get_active_player_profile(1, profile1);
  player_profile_save_last_level_played(profile1, &level1, &difficulty1);

  for (index = 0; index < 0xa; index++) {
    *(int *)(0x46cce8 + index * 8) = *(int *)(0x31e498 + index * 4);
    if (profile0[index + 0x1c] != 0 || index == (int)level0 + 1 ||
        profile1[index + 0x1c] != 0 || index == (int)level1 + 1 || index == 0) {
      bits = (unsigned char)profile0[index + 0x1c] |
             (unsigned char)profile1[index + 0x1c];
      *(char *)(0x46cced + index * 8) = (char)((bits >> 1) & 1);
      *(char *)(0x46ccec + index * 8) = 1;
      *(char *)(0x46ccee + index * 8) = (char)((bits >> 2) & 1);
      *(char *)(0x46ccef + index * 8) = (char)((bits >> 3) & 1);
    }
  }

  tag = tag_get(0x44654c61, *(int *)widget);
  if (*(int16_t *)tag != 2) {
    display_assert((const char *)0x285a18, (const char *)0x2859a4, 0x2b1, true);
    system_exit(-1);
  }
  if (*(int *)((char *)tag + 0x3e0) != 3) {
    display_assert((const char *)0x2859e4, (const char *)0x2859a4, 0x2b2, true);
    system_exit(-1);
  }

  *(void **)((char *)widget + 0x40) = (void *)0x46cce8;
  *(int16_t *)((char *)widget + 0x44) = 0xa;

  level = player_ui_get_last_single_player_level_played(0);
  if (level < 0) {
    *(int16_t *)((char *)widget + 0x3c) = 0;
    return 1;
  }
  level = player_ui_get_last_single_player_level_played(0);
  if (level > 9) {
    *(int16_t *)((char *)widget + 0x3c) = 9;
    return 1;
  }
  level = player_ui_get_last_single_player_level_played(0);
  *(int16_t *)((char *)widget + 0x3c) = level;
  return 1;
}





/* FUN_000e9a90 (0xe9a90) — Capstone tip: unknown game_mode → debug + return 0. */
char FUN_000e9a90(void *widget)
{
  short kind;
  short mode;
  kind = *(short *)((char *)widget + 0x3c);
  if (kind < 0 || kind >= 10) {
    display_assert((char *)0x285aa4, (char *)0x2859a4, 0x2d4, 1);
    system_exit(-1);
  }
  mode = *(short *)0x31fa94;
  if (mode == 1 || mode == 2) {
    return 0;
  }
  error(2, (const char *)0x285a78);
  error(2, (const char *)0x285a54);
  ui_play_audio_feedback_sound(4);
  return 0;
}


/* FUN_000e9dd0 (0xe9dd0) — readable C lift (restored pre-naked). */


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


/* display_scenario_help (0xea210) — Capstone tip: widget type != 1 → assert. */
char display_scenario_help(void *widget)
{
  void *tag;
  tag = tag_get(0x44654c61, *(int *)widget);
  if (*(int *)((char *)tag + 0x3e0) != 1) {
    display_assert((char *)0x285ec0, (char *)0x2859a4, 0x500, 1);
    system_exit(-1);
  }
  return 0;
}


/* network_game_server_list_initialize (0xea3e0) — readable C lift (Capstone hand-lift).
 * Reset server-list widget state, realloc slot array, seed from last-used
 * multiplayer variant profile. Capstone on XBE 0xea3e0..0xea533. */
char network_game_server_list_initialize(void *widget)
{
  char *w;
  void *tag;
  void *slots;
  char pathbuf[0x100];
  int count;
  int profile;
  uint16_t i;
  uint16_t n;

  w = (char *)widget;
  *(int *)0x31e494 = -1;
  csmemset((void *)0x5aa260, -1, 0x144);

  tag = tag_get(0x44654c61, *(int *)w);
  if (*(int16_t *)tag != 2) {
    display_assert((const char *)0x285f48, (const char *)0x2859a4, 0x568, 1);
    system_exit(-1);
  }
  if (*(int *)((char *)tag + 0x3e0) != 3) {
    display_assert((const char *)0x285f08, (const char *)0x2859a4, 0x569, 1);
    system_exit(-1);
  }

  slots = ui_widget_realloc(*(int *)(w + 0x40), 0x190, (const char *)0x2859a4, 0x56e);
  *(void **)(w + 0x40) = slots;
  if (slots != 0) {
    count = 0x64;
    FUN_001c26b0(0, (int)&count, (int)slots);
    n = (uint16_t)count;
    if (n < 3) {
      for (i = n; i < 3; i++)
        *((int *)slots + i) = -1;
      n = 3;
      count = 3;
    }
    *(uint16_t *)(w + 0x44) = n;

    if (saved_game_file_retrieve_last_used_multiplayer_variant_directory(pathbuf)) {
      profile = saved_game_file_find_profile_index_for_directory_path(pathbuf, 1);
      if (profile != -1) {
        n = (uint16_t)count;
        for (i = 0; i < n; i++) {
          if (*((int *)slots + i) == profile) {
            *(uint16_t *)(w + 0x3c) = i;
            break;
          }
        }
      }
    }
  }
  return 1;
}

/* network_game_join_game_from_server_list (0xea570) — Capstone tip: type != 1 → assert. */
char network_game_join_game_from_server_list(void *widget)
{
  void *tag;
  tag = tag_get(0x44654c61, *(int *)widget);
  if (*(int *)((char *)tag + 0x3e0) != 1) {
    display_assert((char *)0x286108, (char *)0x2859a4, 0x5b9, 1);
    system_exit(-1);
  }
  return 0;
}


/* FUN_000ea900 (0xea900) — readable C lift: join network game from event. */
char FUN_000ea900(void *widget, void *event_data)
{
  void *client;
  void *ev;
  void *state_out;
  int16_t state;
  void *players;
  short local_idx;
  int i;
  char *base;

  (void)widget;
  ev = event_data;
  if (!ev) {
    display_assert((const char *)0x286184, (const char *)0x2859a4, 0x652, 1);
    system_exit(-1);
  }
  client = network_game_client_get();
  if (!client)
    return 1;
  state_out = ev;
  state = network_game_client_get_state(client, &state_out);
  if (state != 2)
    return 1;
  players = (void *)FUN_0012a0a0();
  local_idx = network_game_client_get_local_machine_index();
  if (!players) {
    display_assert((const char *)0x2861a8, (const char *)0x2859a4, 0x65b, 1);
    system_exit(-1);
  }
  if (local_idx != -1) {
    for (i = 0; i < 0x10; i++) {
      base = (char *)players + i * 0x20;
      if (network_player_is_valid(base + 0x226) &&
          (short)*(signed char *)(base + 0x242) == local_idx &&
          (short)*(signed char *)(base + 0x243) ==
              *(short *)((char *)ev + 2))
        return 1;
    }
  }
  if (!network_game_client_add_player(client, *(int16_t *)((char *)ev + 2)))
    network_game_log((const char *)0x28618c);
  return 1;
}

/* FUN_000eaa10 (0xeaa10) — readable C lift from XBE leaf. */
char FUN_000eaa10(void *widget)
{
  void *tag;
  int mode;
  void *buf;
  unsigned short count;
  char flag;
  unsigned short n;
  int last;
  unsigned i;
  int left;
  int *slots;

  tag = tag_get(0x44654c61, *(int *)widget);
  *(int *)0x31e494 = -1;
  csmemset((void *)0x5aa3c0, -1, 0x9c);
  if (*(short *)tag != 2) {
    display_assert((const char *)0x2861f8, (const char *)0x2859a4, 0x696, 1);
    system_exit(-1);
  }
  mode = *(int *)((char *)tag + 0x3e0);
  if (mode != 0 && mode != 3) {
    display_assert((const char *)0x2861b0, (const char *)0x2859a4, 0x698, 1);
    system_exit(-1);
  }
  buf = ui_widget_realloc(*(int *)((char *)widget + 0x40), 0x190,
                          (const char *)0x2859a4, 0x69d);
  *(void **)((char *)widget + 0x40) = buf;
  if (buf == 0)
    return 1;

  count = 0x64;
  flag = (*(int *)((char *)tag + 0x3e0) == 3) ? 0 : 1;
  FUN_001c0d50((int)*(unsigned short *)((char *)widget + 8), (int)&count,
               (int)buf, (int)flag);
  if (*(int *)((char *)tag + 0x3e0) == 3 && count < 3) {
    slots = (int *)buf;
    left = 3 - (int)count;
    for (i = (unsigned)count; left > 0; i++, left--)
      slots[i] = -1;
    count = 3;
  }
  *(unsigned short *)((char *)widget + 0x44) = count;
  last = player_ui_get_player1_last_used_profile_index();
  if (last != -1) {
    n = *(unsigned short *)((char *)widget + 0x44);
    slots = *(int **)((char *)widget + 0x40);
    for (i = 0; i < (unsigned)n; i++) {
      if (slots[i] == last) {
        *(short *)((char *)widget + 0x3c) = (short)i;
        break;
      }
    }
  }
  return 1;
}


/* FUN_000eaba0 (0xeaba0) — readable C lift from XBE leaf. */
char FUN_000eaba0(void *widget, void *event_data, char *out_flag)
{
  void *tag;
  void *child;
  void *child_tag;
  short sel;
  int handle;
  char profile[0x30];
  int local_player;

  if (event_data == 0 || *(short *)((char *)event_data + 2) == -1) {
    display_assert((const char *)0x2863b4, (const char *)0x2859a4, 0x6e3, 1);
    system_exit(-1);
  }
  tag = tag_get(0x44654c61, *(int *)widget);
  if (*(short *)tag != 0 || *(int *)((char *)tag + 0x3e0) < 3) {
    display_assert((const char *)0x286360, (const char *)0x2859a4, 0x6ec, 1);
    system_exit(-1);
  }
  child = *(void **)((char *)widget + 0x34);
  child_tag = tag_get(0x44654c61, *(int *)child);
  if (*(short *)child_tag != 2) {
    display_assert((const char *)0x286320, (const char *)0x2859a4, 0x6ef, 1);
    system_exit(-1);
  }
  if (*(int *)((char *)child_tag + 0x3e0) != 3) {
    display_assert((const char *)0x2862e8, (const char *)0x2859a4, 0x6f0, 1);
    system_exit(-1);
  }
  child = *(void **)((char *)widget + 0x34);
  sel = *(short *)((char *)child + 0x3c);
  if (sel < 0 || (int)sel >= (int)*(unsigned short *)((char *)child + 0x44)) {
    display_assert((const char *)0x286298, (const char *)0x2859a4, 0x6f8, 1);
    system_exit(-1);
  }
  handle = ((int *)*(void **)((char *)child + 0x40))[sel];
  if (handle == -1) {
    error(2, (const char *)0x28623c);
    ui_play_audio_feedback_sound(4);
    return 0;
  }
  if (handle >= 0) {
    display_error_deferred(0x1f, -1, 1, 0);
    ui_play_audio_feedback_sound(4);
    *out_flag = 1;
    return 0;
  }
  if (!player_profile_new(handle, profile)) {
    error(2, (const char *)0x286264);
    return 0;
  }
  local_player = player_ui_get_single_player_local_player_from_controller(
      *(short *)((char *)event_data + 2));
  player_ui_set_active_player_profile((int16_t)local_player, handle, profile);
  return 1;
}


/* multiplayer_level_select (0xead60) — readable C lift from XBE leaf. */
char multiplayer_level_select(void *widget, void *event_data)
{
  short controller;
  void *child;
  void *tag;
  short sel;
  int handle;
  char profile[0x30];

  if (event_data == 0 || *(short *)((char *)event_data + 2) == -1) {
    display_assert((const char *)0x2863b4, (const char *)0x2859a4, 0x72a, 1);
    system_exit(-1);
  }
  controller = *(short *)((char *)event_data + 2);
  child = *(void **)((char *)widget + 0x34);
  while (child != 0) {
    if (*(short *)((char *)child + 0xe) == 2)
      break;
    child = *(void **)((char *)child + 0x2c);
  }
  if (child == 0) {
    display_assert((const char *)0x286498, (const char *)0x2859a4, 0x72e, 1);
    system_exit(-1);
  }
  tag = tag_get(0x44654c61, *(int *)child);
  if (*(int *)((char *)tag + 0x3e0) != 0) {
    display_assert((const char *)0x286440, (const char *)0x2859a4, 0x735, 1);
    system_exit(-1);
  }
  sel = *(short *)((char *)child + 0x3c);
  if (sel < 0 || (int)sel >= (int)*(unsigned short *)((char *)child + 0x44)) {
    display_assert((const char *)0x2863f0, (const char *)0x2859a4, 0x73b, 1);
    system_exit(-1);
  }
  handle = ((int *)*(void **)((char *)child + 0x40))[sel];
  if (handle >= 0) {
    display_error_deferred(0x1f, controller, 1, 0);
    ui_play_audio_feedback_sound(4);
    return 0;
  }
  if (!player_profile_new(handle, profile)) {
    error(2, (const char *)0x286264);
    return 0;
  }
  player_ui_set_active_player_profile(controller, handle, profile);
  return 1;
}


/* FUN_000eaec0 (0xeaec0) — readable C lift from XBE leaf. */
char FUN_000eaec0(void *widget)
{
  void *tag;
  void *child;
  void *child_tag;
  short sel;
  int handle;
  char result;

  result = 0;
  *(int *)0x31e494 = -1;
  tag = tag_get(0x44654c61, *(int *)widget);
  if (*(short *)tag != 0 || *(int *)((char *)tag + 0x3e0) < 3) {
    display_assert((const char *)0x286500, (const char *)0x2859a4, 0x768, 1);
    system_exit(-1);
  }
  child = *(void **)((char *)widget + 0x34);
  child_tag = tag_get(0x44654c61, *(int *)child);
  if (*(short *)child_tag != 2) {
    display_assert((const char *)0x286070, (const char *)0x2859a4, 0x76b, 1);
    system_exit(-1);
  }
  if (*(int *)((char *)child_tag + 0x3e0) != 3) {
    display_assert((const char *)0x286034, (const char *)0x2859a4, 0x76c, 1);
    system_exit(-1);
  }
  child = *(void **)((char *)widget + 0x34);
  sel = *(short *)((char *)child + 0x3c);
  if (sel < 0 || (int)sel >= (int)*(unsigned short *)((char *)child + 0x44)) {
    display_assert((const char *)0x285fe0, (const char *)0x2859a4, 0x775, 1);
    system_exit(-1);
  }
  handle = ((int *)*(void **)((char *)child + 0x40))[sel];
  if (handle == -1) {
    ui_play_audio_feedback_sound(4);
    return result;
  }
  if (handle < 0) {
    player_ui_begin_editing_profile(handle);
    return 1;
  }
  display_error_deferred(0x1f, -1, 1, 0);
  ui_play_audio_feedback_sound(4);
  return result;
}


/* FUN_000eb020 (0xeb020) — readable C lift: write playlist game mode from widget. */
char FUN_000eb020(void *widget)
{
  extern char DAT_002859a4[];
  extern char DAT_002865a0[];
  extern char DAT_0028657c[];
  extern char DAT_00286550[];
  void *profile; void *parent; int mode; char ok = 1;
  profile = player_ui_get_edit_playlist_profile();
  parent = *(void **)((char *)widget + 0x30);
  if (parent == 0 || *(short *)((char *)parent + 0xe) != 3) {
    display_assert(DAT_002865a0, DAT_002859a4, 0x7a6, true); system_exit(-1);
  }
  if (profile == 0) { error(2, DAT_00286550); return 0; }
  switch (*(short *)((char *)parent + 0x3c)) {
  case 0: mode = 1; break; case 1: mode = 4; break; case 2: mode = 2; break;
  case 3: mode = 3; break; case 4: mode = 5; break;
  default: error(2, DAT_0028657c); mode = *(int *)((char *)profile + 0x18); break;
  }
  if (mode != *(int *)((char *)profile + 0x18)) csmemset((char *)profile + 0x4c, 0, 0x18u);
  *(int *)((char *)profile + 0x18) = mode;
  return ok;
}

/* FUN_000eb150 (0xeb150) — Capstone tip: no edit playlist profile → error + return 1. */
char FUN_000eb150(void *widget)
{
  (void)widget;
  if (!player_ui_get_edit_playlist_profile()) {
    error(2, (const char *)0x286550);
    return 1;
  }
  return 0;
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


/* FUN_000eb710 (0xeb710) — readable C lift (restored pre-naked). */


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


/* FUN_000eba70 (0xeba70) — readable C lift (restored pre-naked). */


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


/* FUN_000ec2c0 (0xec2c0) — readable C lift (restored pre-naked). */


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

/* --- ui_widget.obj orphan shells (2026-07-26) --- */

/* ui_widget_get_last_child (0xe4310) — readable C lift from XBE leaf.
 * Walks the +0x30 link chain; returns the last non-NULL node (or widget). */
void *ui_widget_get_last_child(void *widget)
{
  void *next;

  next = *(void **)((char *)widget + 0x30);
  if (next == NULL) {
    return widget;
  }
  do {
    widget = next;
    next = *(void **)((char *)widget + 0x30);
  } while (next != NULL);
  return widget;
}

/* ui_widget_pending_load_push_internal (0xe46f0) — readable C lift. */
void ui_widget_pending_load_push_internal(int *head, void *record)
{
  int *node;
  node = (int *)stack_memory_pool_allocate(*(void **)0x31e04c, 0x10, (const char *)0x283280, 0x9e4);
  if (head == 0 || record == 0) {
    display_assert((const char *)0x283560, (const char *)0x283280, 0x9e6, 1);
    system_exit(-1);
  }
  if (node == 0)
    return;
  node[0] = ((int *)record)[0];
  node[1] = ((int *)record)[1];
  node[2] = ((int *)record)[2];
  node[3] = *head;
  *head = (int)node;
}

/* ui_widget_pending_load_pop (0xe4770) — readable C lift from XBE leaf. */
void ui_widget_pending_load_pop(int *head, void *record)
{
  extern char DAT_00283560[];
  extern char DAT_00283280[];
  int *node;

  if (head == 0 || record == 0) {
    display_assert(DAT_00283560, DAT_00283280, 0x9fc, true);
    system_exit(-1);
  }
  node = (int *)*head;
  ((int *)record)[0] = node[0];
  ((int *)record)[1] = node[1];
  ((int *)record)[2] = node[2];
  *head = node[3];
  stack_memory_pool_deallocate(*(void **)0x31e04c, node);
}



/* ui_widget_pending_load_apply (0xe5090) — readable C lift from XBE leaf. */
void ui_widget_pending_load_apply(int a6 /*@<eax>*/, void *widget, int16_t a7)
{
  void *found;
  void *child;
  void *parent;
  void *tag;
  int i;
  short kind;

  if (a6 == -1)
    return;

  found = ui_widget_find_by_tag((int *)widget, a6);
  if (found == 0)
    return;

  if (a7 < 0) {
    if (!widget_instance_is_visible_in_parent_chain(found))
      return;
    if (*(short *)((char *)found + 0xe) == 2) {
      tag = tag_get(0x44654c61, *(int *)found);
      if (*(int *)((char *)tag + 0x3e0) > 1)
        return;
    }
    ui_widget_apply_focus(widget, found);
    return;
  }

  child = *(void **)((char *)found + 0x34);
  i = 0;
  if (child == 0)
    return;

  for (;;) {
    if (*(short *)((char *)child + 0xe) == 2) {
      tag = tag_get(0x44654c61, *(int *)child);
      if (*(int *)((char *)tag + 0x3e0) > 1)
        return;
    }
    if (i == (int)a7)
      break;
    child = *(void **)((char *)child + 0x2c);
    i++;
    if (child == 0)
      return;
  }

  ui_widget_apply_focus(widget, child);
  parent = *(void **)((char *)child + 0x30);
  if (parent == 0)
    return;
  kind = *(short *)((char *)parent + 0xe);
  if (kind == 2 || kind == 3)
    *(short *)((char *)parent + 0x3c) = (short)i;
}


/* ui_widget_update_list_selection (0xe5380) — readable C lift from XBE leaf. */
void ui_widget_update_list_selection(void *widget /* @<ecx> */, void *definition)
{
  void *child;
  (void)definition;

  child = *(void **)((char *)widget + 0x34);
  if (child == NULL) {
    return;
  }
  do {
    if (child == *(void **)((char *)widget + 0x38)) {
      if (*(int16_t *)((char *)child + 0x56) == 2) {
        *(int16_t *)((char *)child + 0x50) = 1;
      }
    } else {
      if (*(int16_t *)((char *)child + 0x56) == 2) {
        *(int16_t *)((char *)child + 0x50) = 0;
      }
    }
    child = *(void **)((char *)child + 0x2c);
  } while (child != NULL);
}

/* ui_widget_list_prev (0xe53e0) — readable C lift from XBE leaf. */
void ui_widget_list_prev(void *widget /*@<edi>*/)
{
  void *cur;
  void *tag;
  short kind;

  cur = *(void **)((char *)widget + 0x38);
  if (cur != 0) {
    cur = *(void **)((char *)cur + 0x2c);
  }
  if (cur == 0) {
    cur = *(void **)((char *)widget + 0x34);
  }
  if (cur == 0) {
    return;
  }
  for (;;) {
    if (cur == *(void **)((char *)widget + 0x38)) {
      return;
    }
    tag = tag_get(0x44654c61, *(int *)cur);
    if (*(int *)((char *)tag + 0x54) > 0 ||
        (*(unsigned char *)((char *)tag + 0x2c) & 1) != 0) {
      *(void **)((char *)widget + 0x38) = cur;
      return;
    }
    kind = *(short *)((char *)widget + 0xe);
    if (kind == 2 || kind == 3) {
      *(void **)((char *)widget + 0x38) = cur;
      return;
    }
    cur = *(void **)((char *)cur + 0x2c);
    if (cur == 0) {
      cur = *(void **)((char *)widget + 0x34);
      if (cur == 0) {
        return;
      }
    }
  }
}




/* ui_widget_list_next (0xe5440) — readable C lift from XBE leaf. */
void ui_widget_list_next(void *widget /*@<edi>*/)
{
  void *cur;
  void *tag;
  void *child;
  short kind;

  cur = *(void **)((char *)widget + 0x38);
  if (cur != 0) {
    cur = *(void **)((char *)cur + 0x28);
    if (cur == 0) {
      child = *(void **)((char *)widget + 0x34);
      if (child == 0)
        return;
      cur = *(void **)((char *)child + 0x2c);
      if (cur != 0) {
        for (;;) {
          child = cur;
          cur = *(void **)((char *)child + 0x2c);
          if (cur == 0) {
            cur = child;
            break;
          }
        }
      } else {
        cur = child;
      }
    }
  } else {
    child = *(void **)((char *)widget + 0x34);
    cur = *(void **)((char *)child + 0x28);
    if (cur == 0)
      cur = child;
  }
  if (cur == 0)
    return;
  for (;;) {
    if (cur == *(void **)((char *)widget + 0x38))
      return;
    tag = tag_get(0x44654c61, *(int *)cur);
    if (*(int *)((char *)tag + 0x54) > 0 ||
        (*(unsigned char *)((char *)tag + 0x2c) & 1) != 0) {
      *(void **)((char *)widget + 0x38) = cur;
      return;
    }
    kind = *(short *)((char *)widget + 0xe);
    if (kind == 2 || kind == 3) {
      *(void **)((char *)widget + 0x38) = cur;
      return;
    }
    cur = *(void **)((char *)cur + 0x28);
    if (cur == 0) {
      child = *(void **)((char *)widget + 0x34);
      if (child == 0)
        return;
      {
        void *p = *(void **)((char *)child + 0x2c);
        if (p != 0) {
          for (;;) {
            child = p;
            p = *(void **)((char *)child + 0x2c);
            if (p == 0)
              break;
          }
        }
        cur = child;
      }
      if (cur == 0)
        return;
    }
  }
}

/* ui_widget_close_and_reload (0xe68e0) — readable C lift. */
void ui_widget_close_and_reload(void *widget)
{
  unsigned short controller;
  int root_index;
  int *head;
  int pending[3];
  int tag_index;
  int widget_stack;
  int a6;
  short a7;
  void *root;
  void *loaded;

  controller = *(unsigned short *)((char *)widget + 8);
  if (controller == 0xffffu)
    root_index = 0;
  else
    root_index = (int)(short)controller;
  head = (int *)(0x46cc30 + root_index * 4);
  widget_stack = -1;
  if (*head != 0) {
    ui_widget_pending_load_pop(head, pending);
    tag_index = pending[0];
    a6 = pending[1];
    a7 = (short)(pending[2] & 0xffff);
    widget_stack = (int)(short)((unsigned)pending[2] >> 16);
  } else {
    tag_index = -1;
    a6 = 0;
    a7 = 0;
  }

  root = widget;
  while (*(void **)((char *)root + 0x30) != 0)
    root = *(void **)((char *)root + 0x30);
  ui_widget_close(root);

  if (tag_index != -1) {
    loaded = ui_widget_load_by_name_or_tag(
        0, tag_index, 0, widget_stack, -1, -1, -1);
    if (loaded != 0)
      ui_widget_pending_load_apply(a6, loaded, a7);
  }
}

/* ui_widget_list_next_item (0xe6ab0) — Capstone tip: list type not 2/3 → assert. */
int ui_widget_list_next_item(void *widget, void *event_data, char *widget_deleted)
{
  short kind;
  (void)event_data;
  (void)widget_deleted;
  if (!widget) {
    display_assert((char *)0x2832a8, (char *)0x283280, 0x4ce, 1);
    system_exit(-1);
  }
  tag_get(0x44654c61, *(int *)widget);
  kind = *(short *)((char *)widget + 0xe);
  if (kind != 2 && kind != 3) {
    display_assert((char *)0x283d14, (char *)0x283280, 0x4d1, 1);
    system_exit(-1);
  }
  return 0;
}


/* ui_widget_list_prev_item (0xe6cb0) — Capstone tip: list type not 2/3 → assert. */
int ui_widget_list_prev_item(void *widget, void *event_data, char *widget_deleted)
{
  short kind;
  (void)event_data;
  (void)widget_deleted;
  if (!widget) {
    display_assert((char *)0x2832a8, (char *)0x283280, 0x54f, 1);
    system_exit(-1);
  }
  tag_get(0x44654c61, *(int *)widget);
  kind = *(short *)((char *)widget + 0xe);
  if (kind != 2 && kind != 3) {
    display_assert((char *)0x283d14, (char *)0x283280, 0x552, 1);
    system_exit(-1);
  }
  return 0;
}


/* ui_widget_handle_event_handler (0xe6ed0) — Capstone tip: empty event flags → deleted=0. */
void ui_widget_handle_event_handler(uintptr_t widget, uintptr_t definition, uintptr_t event_data,
                                    uintptr_t event_handler, uintptr_t widget_deleted)
{
  (void)widget; (void)definition; (void)event_data; (void)event_handler;
  if (widget_deleted)
    *(char *)widget_deleted = 0;
}


/* ui_widget_load_from_tag_internal (0xe7b10) — Capstone tip: parent==NULL init path. */
void ui_widget_load_from_tag_internal(uintptr_t tag_data /*@<eax>*/, uintptr_t widget /*@<edx>*/,
                                      uintptr_t parent /*@<ecx>*/, int tag_index, int widget_stack,
                                      int widget_stack_base)
{
  (void)tag_data; (void)widget; (void)parent;
  (void)tag_index; (void)widget_stack; (void)widget_stack_base;
  return;
}


/* ui_widget_spawn_from_event_handler (0xe9320) — readable C lift from XBE leaf. */
void *ui_widget_spawn_from_event_handler(void *widget, int tag_index)
{
  void *tag;
  unsigned int flags;
  int type;
  int widget_stack;
  void *parent;
  void *root;
  int parent_tag;
  int child_index;
  void *iter;
  int i;
  void *loaded;
  int root_tag;

  tag = tag_get(0x44654c61, tag_index);
  flags = *(unsigned int *)((char *)tag + 0x2c);
  type = (int)*(short *)((char *)tag + 2);

  if ((flags & 0x1000u) != 0) {
    if (type > 4) {
      display_assert((const char *)0x284cb8, (const char *)0x283280, 0x1504, 1);
      system_exit(-1);
      widget_stack = (int)widget;
    } else if (type == 0) {
      widget_stack = 0;
    } else if (type == 1) {
      widget_stack = 1;
    } else if (type == 2) {
      widget_stack = 2;
    } else if (type == 3) {
      widget_stack = 3;
    } else {
      widget_stack = -1;
    }
  } else if (type > 4) {
    display_assert((const char *)0x284cb8, (const char *)0x283280, 0x1510, 1);
    system_exit(-1);
    widget_stack = (int)widget;
  } else if (type == 0) {
    widget_stack = 0;
  } else if (type == 1) {
    widget_stack = 1;
  } else if (type == 2) {
    widget_stack = 2;
  } else if (type == 3) {
    widget_stack = 3;
  } else {
    widget_stack = (int)*(unsigned short *)((char *)widget + 8);
  }

  parent = *(void **)((char *)widget + 0x30);
  root = widget;
  if (parent != 0) {
    root = parent;
    while (*(void **)((char *)root + 0x30) != 0)
      root = *(void **)((char *)root + 0x30);
  }

  if (parent != 0)
    parent_tag = *(int *)parent;
  else
    parent_tag = -1;

  child_index = -1;
  if (parent != 0) {
    iter = *(void **)((char *)parent + 0x34);
    i = 0;
    while (iter != 0) {
      if (iter == widget) {
        child_index = i;
        break;
      }
      iter = *(void **)((char *)iter + 0x2c);
      i++;
    }
  }

  root_tag = *(int *)root;
  loaded = ui_widget_load_by_name_or_tag(
      0, tag_index, 0, widget_stack, root_tag, parent_tag, child_index);
  if (loaded == 0)
    error(2, (const char *)0x283728);
  return loaded;
}
