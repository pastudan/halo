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

void ui_widget_pending_load_apply(int pending_a6, int widget, int16_t a7);

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

void ui_widget_handle_event_handler(void *widget, void *definition,
                                    void *event_data, void *event_handler,
                                    char *widget_deleted);

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
            ui_widget_pending_load_apply(pending_load.a6, (int)loaded_widget,
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




/* FUN_000e76b0 (0xe76b0) — XBE naked draft (batch 139). */
#if defined(__clang__)
static void (*const be76b0_ce73c0)(void *widget, int16_t *bounds, float opacity_scale, char param_4, char visible) = (void *)FUN_000e73c0;

__attribute__((naked, noinline))
void FUN_000e76b0(void *widget, void *tag, void *a, float d, int e, int f)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "movl 0x48(%%edi), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .LFUN_000e76b0_3\n\t"
      "movl 0x30(%%edi), %%eax\n\t"
      "flds 0x24(%%edi)\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_000e76b0_2\n\t"
      "leal (%%ebx), %%ebx\n\t"
      ".LFUN_000e76b0_1:\n\t"
      "fmuls 0x24(%%eax)\n\t"
      "movl 0x30(%%eax), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_000e76b0_1\n\t"
      ".LFUN_000e76b0_2:\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "fstps 0x24(%%ecx)\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "movl 0x48(%%edi), %%edx\n\t"
      "pushl $1\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[ce73c0]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000e76b0_3:\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "testb $1, 0x150(%%eax)\n\t"
      "je .LFUN_000e76b0_5\n\t"
      "movl 0x34(%%edi), %%esi\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "je .LFUN_000e76b0_6\n\t"
      "leal (%%ebx), %%ebx\n\t"
      ".LFUN_000e76b0_4:\n\t"
      "movzwl 0x44(%%edi), %%ecx\n\t"
      "cmpl %%ecx, %%ebx\n\t"
      "jge .LFUN_000e76b0_5\n\t"
      "movswl 0x3c(%%edi), %%edx\n\t"
      "movl 0x18(%%ebp), %%ecx\n\t"
      "cmpl %%edx, %%ebx\n\t"
      "movl 0x14(%%ebp), %%edx\n\t"
      "sete %%al\n\t"
      "pushl %%eax\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[ce73c0]\n\t"
      "movl 0x2c(%%esi), %%esi\n\t"
      "addl $0x14, %%esp\n\t"
      "incl %%ebx\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LFUN_000e76b0_4\n\t"
      ".LFUN_000e76b0_5:\n\t"
      "movw $0, 0x3e(%%edi)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000e76b0_6:\n\t"
      "movw %%bx, 0x3e(%%edi)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [ce73c0] "m"(be76b0_ce73c0)
      : "memory");
}
#else
#error "FUN_000e76b0: clang naked draft required"
#endif


/* network_game_reset_to_pregame_ui (0xe8830) — XBE naked draft (batch 137). */
#if defined(__clang__)
static void (*const be8830_ce58c0)(void) = (void *)ui_widgets_close_all;
static bool (*const be8830_c12a170)(void) = (void *)network_game_is_splitscreen_local;
static unsigned int (*const be8830_c12a1a0)(void) = (void *)FUN_0012a1a0;
static void * (*const be8830_ce84e0)(const char *name, int tag_index, int is_child, int widget_stack, int parent_tag_index, int a6, int a7) = (void *)ui_widget_load_by_name_or_tag;
static void (*const be8830_c8f390)(unsigned __int16 a1, const char *a2, ...) = (void *)error;
static void * (*const be8830_c12a1d0)(void) = (void *)network_game_server_get;
static void (*const be8830_c12d690)(void *server, char flag) = (void *)network_game_server_pause_countdown;

__attribute__((naked, noinline))
void network_game_reset_to_pregame_ui(void)
{
  __asm__ volatile(
      "call *%[ce58c0]\n\t"
      "call *%[c12a170]\n\t"
      "testb %%al, %%al\n\t"
      "je .Lnetwork_game_reset_to_pregame_ui_2\n\t"
      "call *%[c12a1a0]\n\t"
      "testb %%al, %%al\n\t"
      "pushl $-1\n\t"
      "pushl $-1\n\t"
      "pushl $-1\n\t"
      "pushl $-1\n\t"
      "pushl $0\n\t"
      "pushl $-1\n\t"
      "je .Lnetwork_game_reset_to_pregame_ui_1\n\t"
      "pushl $0x284370\n\t"
      "call *%[ce84e0]\n\t"
      "addl $0x1c, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lnetwork_game_reset_to_pregame_ui_4\n\t"
      "pushl $0x284338\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "ret\n\t"
      ".Lnetwork_game_reset_to_pregame_ui_1:\n\t"
      "pushl $0x2842d8\n\t"
      "call *%[ce84e0]\n\t"
      "addl $0x1c, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lnetwork_game_reset_to_pregame_ui_4\n\t"
      "pushl $0x2842ac\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "ret\n\t"
      ".Lnetwork_game_reset_to_pregame_ui_2:\n\t"
      "call *%[c12a1d0]\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lnetwork_game_reset_to_pregame_ui_3\n\t"
      "pushl $1\n\t"
      "call *%[c12a1d0]\n\t"
      "pushl %%eax\n\t"
      "call *%[c12d690]\n\t"
      "pushl $-1\n\t"
      "pushl $-1\n\t"
      "pushl $-1\n\t"
      "pushl $-1\n\t"
      "pushl $0\n\t"
      "pushl $-1\n\t"
      "pushl $0x284250\n\t"
      "call *%[ce84e0]\n\t"
      "addl $0x24, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lnetwork_game_reset_to_pregame_ui_4\n\t"
      "pushl $0x2842ac\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "ret\n\t"
      ".Lnetwork_game_reset_to_pregame_ui_3:\n\t"
      "pushl $-1\n\t"
      "pushl $-1\n\t"
      "pushl $-1\n\t"
      "pushl $-1\n\t"
      "pushl $0\n\t"
      "pushl $-1\n\t"
      "pushl $0x2828e0\n\t"
      "call *%[ce84e0]\n\t"
      "addl $0x1c, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lnetwork_game_reset_to_pregame_ui_4\n\t"
      "pushl $0x284220\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      ".Lnetwork_game_reset_to_pregame_ui_4:\n\t"
      "ret\n\t"
      :
      : [ce58c0] "m"(be8830_ce58c0), [c12a170] "m"(be8830_c12a170), [c12a1a0] "m"(be8830_c12a1a0), [ce84e0] "m"(be8830_ce84e0), [c8f390] "m"(be8830_c8f390), [c12a1d0] "m"(be8830_c12a1d0), [c12d690] "m"(be8830_c12d690)
      : "memory");
}
#else
#error "network_game_reset_to_pregame_ui: clang naked draft required"
#endif


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

/* split_screen_game_initialize (0xea810) — XBE naked draft (batch 134). */
#if defined(__clang__)
static void (*const bea810_assert)(const char *, const char *, int, bool) = (void *)display_assert;
static void (*const bea810_exitfn)(int) = (void *)system_exit;
static int (*const bea810_c12a0a0)(void) = (void *)FUN_0012a0a0;
static short (*const bea810_c12a690)(void) = (void *)network_game_client_get_local_machine_index;
static bool (*const bea810_c12ac80)(void *client) = (void *)network_player_is_valid;
static void * (*const bea810_c12a240)(void) = (void *)network_game_client_get;
static char (*const bea810_c125a90)(void *client, void *player) = (void *)network_game_client_update_local_player_data;
static void (*const bea810_c8f390)(unsigned __int16 a1, const char *a2, ...) = (void *)error;

__attribute__((naked, noinline))
char split_screen_game_initialize(void *widget, void *player_data)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x24, %%esp\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lsplit_screen_game_initialize_1\n\t"
      "pushl $1\n\t"
      "pushl $0x624\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x286184\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lsplit_screen_game_initialize_1:\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c12a0a0]\n\t"
      "movl %%eax, %%ebx\n\t"
      "testl %%ebx, %%ebx\n\t"
      "je .Lsplit_screen_game_initialize_5\n\t"
      "cmpb $1, 0xc0(%%ebx)\n\t"
      "jne .Lsplit_screen_game_initialize_5\n\t"
      "call *%[c12a690]\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "je .Lsplit_screen_game_initialize_5\n\t"
      "xorl %%esi, %%esi\n\t"
      "leal 0x242(%%ebx), %%edi\n\t"
      ".Lsplit_screen_game_initialize_2:\n\t"
      "leal -0x1c(%%edi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c12ac80]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lsplit_screen_game_initialize_3\n\t"
      "movsbw (%%edi), %%cx\n\t"
      "cmpw -0x4(%%ebp), %%cx\n\t"
      "jne .Lsplit_screen_game_initialize_3\n\t"
      "movsbw 0x1(%%edi), %%dx\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "cmpw 0x2(%%eax), %%dx\n\t"
      "je .Lsplit_screen_game_initialize_4\n\t"
      ".Lsplit_screen_game_initialize_3:\n\t"
      "incl %%esi\n\t"
      "addl $0x20, %%edi\n\t"
      "cmpl $0x10, %%esi\n\t"
      "jl .Lsplit_screen_game_initialize_2\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lsplit_screen_game_initialize_4:\n\t"
      "shll $5, %%esi\n\t"
      "leal 0x226(%%esi,%%ebx,1), %%esi\n\t"
      "movl $8, %%ecx\n\t"
      "leal -0x24(%%ebp), %%edi\n\t"
      "rep movsl\n\t"
      "movb -0x6(%%ebp), %%bl\n\t"
      "testb %%bl, %%bl\n\t"
      "leal -0x24(%%ebp), %%edx\n\t"
      "sete %%cl\n\t"
      "pushl %%edx\n\t"
      "movb %%cl, -0x6(%%ebp)\n\t"
      "call *%[c12a240]\n\t"
      "pushl %%eax\n\t"
      "call *%[c125a90]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lsplit_screen_game_initialize_5\n\t"
      "pushl $0x286150\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      ".Lsplit_screen_game_initialize_5:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(bea810_assert), [exitfn] "m"(bea810_exitfn), [c12a0a0] "m"(bea810_c12a0a0), [c12a690] "m"(bea810_c12a690), [c12ac80] "m"(bea810_c12ac80), [c12a240] "m"(bea810_c12a240), [c125a90] "m"(bea810_c125a90), [c8f390] "m"(bea810_c8f390)
      : "memory");
}
#else
#error "split_screen_game_initialize: clang naked draft required"
#endif


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

/* FUN_000ecd50 (0xecd50) — XBE naked draft (batch 143). */
#if defined(__clang__)
static void *(*const becd50_ce0ec0)(void) = (void *)player_ui_get_edit_playlist_profile;
static void (*const becd50_assert)(const char *, const char *, int, bool) = (void *)display_assert;
static void (*const becd50_exitfn)(int) = (void *)system_exit;
static void * (*const becd50_ce3cd0)(void *widget, int index) = (void *)widget_instance_get_nth_child;
static void (*const becd50_c8f390)(unsigned __int16 a1, const char *a2, ...) = (void *)error;

__attribute__((naked, noinline))
char FUN_000ecd50(void *widget)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[ce0ec0]\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "cmpw $3, 0xe(%%esi)\n\t"
      "movl %%eax, %%edi\n\t"
      "je .LFUN_000ecd50_1\n\t"
      "pushl $1\n\t"
      "pushl $0xab2\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x287ab0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000ecd50_1:\n\t"
      "testl %%edi, %%edi\n\t"
      "je .LFUN_000ecd50_8\n\t"
      "movl 0x18(%%edi), %%edi\n\t"
      "leal -0x1(%%edi), %%eax\n\t"
      "cmpl $4, %%eax\n\t"
      "ja .LFUN_000ecd50_6\n\t"
      "jmp *.LFUN_000ecd50_jt(,%%eax,4)\n\t"
      ".LFUN_000ecd50_2:\n\t"
      "movw $1, 0x3c(%%esi)\n\t"
      "jmp .LFUN_000ecd50_7\n\t"
      ".LFUN_000ecd50_3:\n\t"
      "movw $2, 0x3c(%%esi)\n\t"
      "jmp .LFUN_000ecd50_7\n\t"
      ".LFUN_000ecd50_4:\n\t"
      "movw $3, 0x3c(%%esi)\n\t"
      "jmp .LFUN_000ecd50_7\n\t"
      ".LFUN_000ecd50_5:\n\t"
      "movw $4, 0x3c(%%esi)\n\t"
      "jmp .LFUN_000ecd50_7\n\t"
      ".LFUN_000ecd50_6:\n\t"
      "movw $0, 0x3c(%%esi)\n\t"
      ".LFUN_000ecd50_7:\n\t"
      "movswl 0x3c(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[ce3cd0]\n\t"
      "addl $8, %%esp\n\t"
      "movl %%eax, 0x38(%%esi)\n\t"
      "popl %%edi\n\t"
      "movb $1, %%al\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000ecd50_8:\n\t"
      "pushl $0x286550\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "popl %%edi\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_000ecd50_jt:\n\t"
      ".long .LFUN_000ecd50_6\n\t"
      ".long .LFUN_000ecd50_3\n\t"
      ".long .LFUN_000ecd50_4\n\t"
      ".long .LFUN_000ecd50_2\n\t"
      ".long .LFUN_000ecd50_5\n\t"
      ".text\n\t"
      :
      : [ce0ec0] "m"(becd50_ce0ec0), [assert] "m"(becd50_assert), [exitfn] "m"(becd50_exitfn), [ce3cd0] "m"(becd50_ce3cd0), [c8f390] "m"(becd50_c8f390)
      : "memory");
}
#else
#error "FUN_000ecd50: clang naked draft required"
#endif


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

/* FUN_000ea010 (0xea010) — XBE naked draft (batch 135). */
#if defined(__clang__)
static void (*const bea010_c12a150)(char accept) = (void *)network_game_set_accept_remote_connections;
static void * (*const bea010_c12a1d0)(void) = (void *)network_game_server_get;
static void (*const bea010_cae750)(void) = (void *)game_engine_playlist_initialize;
static bool (*const bea010_c12a890)(void) = (void *)FUN_0012a890;
static void (*const bea010_ca8a70)(void) = (void *)game_engine_playlist_begin;
static void (*const bea010_cfff70)(short param) = (void *)set_game_connection;
static void * (*const bea010_c12a240)(void) = (void *)network_game_client_get;
static bool (*const bea010_c12a250)(void) = (void *)FUN_0012a250;
static void (*const bea010_c12a1e0)(void) = (void *)dispose_global_network_game_client;
static void (*const bea010_c12a2a0)(void) = (void *)dispose_global_network_game_server;
static void (*const bea010_ce0960)(void) = (void *)player_ui_clear_multiplayer_variant;
static void (*const bea010_c8f390)(unsigned __int16 a1, const char *a2, ...) = (void *)error;

__attribute__((naked, noinline))
char FUN_000ea010(void)
{
  __asm__ volatile(
      "pushl %%ebx\n\t"
      "pushl $0\n\t"
      "movb $1, %%bl\n\t"
      "call *%[c12a150]\n\t"
      "addl $4, %%esp\n\t"
      "call *%[c12a1d0]\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_000ea010_2\n\t"
      "call *%[cae750]\n\t"
      "call *%[c12a890]\n\t"
      "movb %%al, %%bl\n\t"
      "cmpb $1, %%bl\n\t"
      "jne .LFUN_000ea010_1\n\t"
      "call *%[ca8a70]\n\t"
      "pushl $2\n\t"
      "call *%[cfff70]\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_000ea010_1:\n\t"
      "testb %%bl, %%bl\n\t"
      "je .LFUN_000ea010_4\n\t"
      ".LFUN_000ea010_2:\n\t"
      "call *%[c12a240]\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_000ea010_3\n\t"
      "call *%[c12a250]\n\t"
      "movb %%al, %%bl\n\t"
      ".LFUN_000ea010_3:\n\t"
      "testb %%bl, %%bl\n\t"
      "jne .LFUN_000ea010_5\n\t"
      ".LFUN_000ea010_4:\n\t"
      "call *%[c12a1e0]\n\t"
      "call *%[c12a2a0]\n\t"
      "call *%[ce0960]\n\t"
      "pushl $0x285d48\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_000ea010_5:\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      :
      : [c12a150] "m"(bea010_c12a150), [c12a1d0] "m"(bea010_c12a1d0), [cae750] "m"(bea010_cae750), [c12a890] "m"(bea010_c12a890), [ca8a70] "m"(bea010_ca8a70), [cfff70] "m"(bea010_cfff70), [c12a240] "m"(bea010_c12a240), [c12a250] "m"(bea010_c12a250), [c12a1e0] "m"(bea010_c12a1e0), [c12a2a0] "m"(bea010_c12a2a0), [ce0960] "m"(bea010_ce0960), [c8f390] "m"(bea010_c8f390)
      : "memory");
}
#else
#error "FUN_000ea010: clang naked draft required"
#endif


/* FUN_000ea100 (0xea100) — XBE naked draft (batch 137). */
#if defined(__clang__)
static void *(*const bea100_tag)(int, int) = (void *)tag_get;
static void (*const bea100_assert)(const char *, const char *, int, bool) = (void *)display_assert;
static void (*const bea100_exitfn)(int) = (void *)system_exit;
static void (*const bea100_c1c3080)(void) = (void *)saved_game_file_retrieve_last_used_multiplayer_map;
static int (*const bea100_c1dd801)(const char *a, const char *b) = (void *)crt_stricmp;

__attribute__((naked, noinline))
char FUN_000ea100(void *widget)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x100, %%esp\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "movl (%%esi), %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "pushl $0x44654c61\n\t"
      "call *%[tag]\n\t"
      "movl %%eax, %%edi\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $2, (%%edi)\n\t"
      "je .LFUN_000ea100_1\n\t"
      "pushl $1\n\t"
      "pushl $0x4cc\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x285db8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000ea100_1:\n\t"
      "cmpl $3, 0x3e0(%%edi)\n\t"
      "je .LFUN_000ea100_2\n\t"
      "pushl $1\n\t"
      "pushl $0x4cd\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x285d78\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000ea100_2:\n\t"
      "leal -0x100(%%ebp), %%ecx\n\t"
      "movl $0xd, %%edi\n\t"
      "pushl %%ecx\n\t"
      "movl $0x31e4c8, 0x40(%%esi)\n\t"
      "movw %%di, 0x44(%%esi)\n\t"
      "call *%[c1c3080]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000ea100_5\n\t"
      "movw $0, 0x3c(%%esi)\n\t"
      "jmp .LFUN_000ea100_3\n\t"
      "leal (%%ebx), %%ebx\n\t"
      ".LFUN_000ea100_3:\n\t"
      "movswl 0x3c(%%esi), %%edx\n\t"
      "movl 0x31e4c8(,%%edx,4), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x100(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1dd801]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_000ea100_4\n\t"
      "incw 0x3c(%%esi)\n\t"
      "cmpw %%di, 0x3c(%%esi)\n\t"
      "jl .LFUN_000ea100_3\n\t"
      ".LFUN_000ea100_4:\n\t"
      "cmpw %%di, 0x3c(%%esi)\n\t"
      "movb $1, %%al\n\t"
      "jne .LFUN_000ea100_6\n\t"
      "popl %%edi\n\t"
      "movw $0, 0x3c(%%esi)\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000ea100_5:\n\t"
      "movb $1, %%al\n\t"
      ".LFUN_000ea100_6:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [tag] "m"(bea100_tag), [assert] "m"(bea100_assert), [exitfn] "m"(bea100_exitfn), [c1c3080] "m"(bea100_c1c3080), [c1dd801] "m"(bea100_c1dd801)
      : "memory");
}
#else
#error "FUN_000ea100: clang naked draft required"
#endif


/* FUN_000eceb0 (0xeceb0) — XBE naked draft (batch 108). */
#if defined(__clang__)
static void *(*const beceb0_ce0ec0)(void) = (void *)player_ui_get_edit_playlist_profile;
static void (*const beceb0_assert)(const char *, const char *, int, bool) = (void *)display_assert;
static void (*const beceb0_exitfn)(int) = (void *)system_exit;
static void (*const beceb0_c8f390)(unsigned __int16 a1, const char *a2, ...) = (void *)error;

__attribute__((naked, noinline))
char FUN_000eceb0(void *widget)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[ce0ec0]\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "cmpw $3, 0xe(%%esi)\n\t"
      "movl %%eax, %%edi\n\t"
      "movl %%edi, -0x4(%%ebp)\n\t"
      "je .LFUN_000eceb0_1\n\t"
      "pushl $1\n\t"
      "pushl $0xaed\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x287b1c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000eceb0_1:\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "cmpl %%ebx, %%edi\n\t"
      "je .LFUN_000eceb0_40\n\t"
      "movl 0x34(%%esi), %%edi\n\t"
      "cmpl %%ebx, %%edi\n\t"
      "jne .LFUN_000eceb0_2\n\t"
      "pushl $1\n\t"
      "pushl $0xaf5\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x2868d0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000eceb0_2:\n\t"
      "movl 0x34(%%edi), %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "je .LFUN_000eceb0_4\n\t"
      ".LFUN_000eceb0_3:\n\t"
      "movl $2, %%ecx\n\t"
      "cmpw %%cx, 0xe(%%esi)\n\t"
      "je .LFUN_000eceb0_5\n\t"
      "movl 0x2c(%%esi), %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "jne .LFUN_000eceb0_3\n\t"
      ".LFUN_000eceb0_4:\n\t"
      "pushl $1\n\t"
      "pushl $0xaf7\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x2868a8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "movl $2, %%ecx\n\t"
      ".LFUN_000eceb0_5:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movzbl 0x4c(%%eax), %%eax\n\t"
      "subl %%ebx, %%eax\n\t"
      "je .LFUN_000eceb0_6\n\t"
      "movw %%bx, 0x3c(%%esi)\n\t"
      "jmp .LFUN_000eceb0_7\n\t"
      ".LFUN_000eceb0_6:\n\t"
      "movw $1, 0x3c(%%esi)\n\t"
      ".LFUN_000eceb0_7:\n\t"
      "movl 0x2c(%%edi), %%edi\n\t"
      "cmpl %%ebx, %%edi\n\t"
      "jne .LFUN_000eceb0_8\n\t"
      "pushl $1\n\t"
      "pushl $0xb00\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x286848\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "movl $2, %%ecx\n\t"
      ".LFUN_000eceb0_8:\n\t"
      "movl 0x34(%%edi), %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "je .LFUN_000eceb0_10\n\t"
      ".LFUN_000eceb0_9:\n\t"
      "cmpw %%cx, 0xe(%%esi)\n\t"
      "je .LFUN_000eceb0_11\n\t"
      "movl 0x2c(%%esi), %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "jne .LFUN_000eceb0_9\n\t"
      ".LFUN_000eceb0_10:\n\t"
      "pushl $1\n\t"
      "pushl $0xb02\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x28681c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "movl $2, %%ecx\n\t"
      ".LFUN_000eceb0_11:\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "movl 0x50(%%edx), %%eax\n\t"
      "cmpl $0x1518, %%eax\n\t"
      "jg .LFUN_000eceb0_14\n\t"
      "je .LFUN_000eceb0_13\n\t"
      "cmpl %%ebx, %%eax\n\t"
      "je .LFUN_000eceb0_15\n\t"
      "cmpl $0x708, %%eax\n\t"
      "je .LFUN_000eceb0_12\n\t"
      "cmpl $0xe10, %%eax\n\t"
      "jne .LFUN_000eceb0_15\n\t"
      "movw %%cx, 0x3c(%%esi)\n\t"
      "jmp .LFUN_000eceb0_18\n\t"
      ".LFUN_000eceb0_12:\n\t"
      "movw $1, 0x3c(%%esi)\n\t"
      "jmp .LFUN_000eceb0_18\n\t"
      ".LFUN_000eceb0_13:\n\t"
      "movw $3, 0x3c(%%esi)\n\t"
      "jmp .LFUN_000eceb0_18\n\t"
      ".LFUN_000eceb0_14:\n\t"
      "cmpl $0x2328, %%eax\n\t"
      "je .LFUN_000eceb0_17\n\t"
      "cmpl $0x4650, %%eax\n\t"
      "je .LFUN_000eceb0_16\n\t"
      ".LFUN_000eceb0_15:\n\t"
      "movw %%bx, 0x3c(%%esi)\n\t"
      "jmp .LFUN_000eceb0_18\n\t"
      ".LFUN_000eceb0_16:\n\t"
      "movw $5, 0x3c(%%esi)\n\t"
      "jmp .LFUN_000eceb0_18\n\t"
      ".LFUN_000eceb0_17:\n\t"
      "movw $4, 0x3c(%%esi)\n\t"
      ".LFUN_000eceb0_18:\n\t"
      "movl 0x2c(%%edi), %%edi\n\t"
      "cmpl %%ebx, %%edi\n\t"
      "jne .LFUN_000eceb0_19\n\t"
      "pushl $1\n\t"
      "pushl $0xb0f\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x2867bc\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "movl $2, %%ecx\n\t"
      ".LFUN_000eceb0_19:\n\t"
      "movl 0x34(%%edi), %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "je .LFUN_000eceb0_21\n\t"
      ".LFUN_000eceb0_20:\n\t"
      "cmpw %%cx, 0xe(%%esi)\n\t"
      "je .LFUN_000eceb0_22\n\t"
      "movl 0x2c(%%esi), %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "jne .LFUN_000eceb0_20\n\t"
      ".LFUN_000eceb0_21:\n\t"
      "pushl $1\n\t"
      "pushl $0xb11\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x28678c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "movl $2, %%ecx\n\t"
      ".LFUN_000eceb0_22:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movzbl 0x4e(%%eax), %%eax\n\t"
      "subl %%ebx, %%eax\n\t"
      "je .LFUN_000eceb0_23\n\t"
      "movw %%bx, 0x3c(%%esi)\n\t"
      "jmp .LFUN_000eceb0_24\n\t"
      ".LFUN_000eceb0_23:\n\t"
      "movw $1, 0x3c(%%esi)\n\t"
      ".LFUN_000eceb0_24:\n\t"
      "movl 0x2c(%%edi), %%edi\n\t"
      "cmpl %%ebx, %%edi\n\t"
      "jne .LFUN_000eceb0_25\n\t"
      "pushl $1\n\t"
      "pushl $0xb1a\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x286720\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "movl $2, %%ecx\n\t"
      ".LFUN_000eceb0_25:\n\t"
      "movl 0x34(%%edi), %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "je .LFUN_000eceb0_27\n\t"
      "movl %%edi, %%edi\n\t"
      ".LFUN_000eceb0_26:\n\t"
      "cmpw %%cx, 0xe(%%esi)\n\t"
      "je .LFUN_000eceb0_28\n\t"
      "movl 0x2c(%%esi), %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "jne .LFUN_000eceb0_26\n\t"
      ".LFUN_000eceb0_27:\n\t"
      "pushl $1\n\t"
      "pushl $0xb1c\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x2866e8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "movl $2, %%ecx\n\t"
      ".LFUN_000eceb0_28:\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "movzbl 0x4f(%%edx), %%eax\n\t"
      "subl %%ebx, %%eax\n\t"
      "je .LFUN_000eceb0_29\n\t"
      "movw %%bx, 0x3c(%%esi)\n\t"
      "jmp .LFUN_000eceb0_30\n\t"
      ".LFUN_000eceb0_29:\n\t"
      "movw $1, 0x3c(%%esi)\n\t"
      ".LFUN_000eceb0_30:\n\t"
      "movl 0x2c(%%edi), %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "jne .LFUN_000eceb0_31\n\t"
      "pushl $1\n\t"
      "pushl $0xb25\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x28667c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "movl $2, %%ecx\n\t"
      ".LFUN_000eceb0_31:\n\t"
      "movl 0x34(%%esi), %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "je .LFUN_000eceb0_33\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_000eceb0_32:\n\t"
      "cmpw %%cx, 0xe(%%esi)\n\t"
      "je .LFUN_000eceb0_34\n\t"
      "movl 0x2c(%%esi), %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "jne .LFUN_000eceb0_32\n\t"
      ".LFUN_000eceb0_33:\n\t"
      "pushl $1\n\t"
      "pushl $0xb27\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x28664c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "movl $2, %%ecx\n\t"
      ".LFUN_000eceb0_34:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movl 0x40(%%eax), %%eax\n\t"
      "decl %%eax\n\t"
      "cmpl $0xe, %%eax\n\t"
      "ja .LFUN_000eceb0_35\n\t"
      "movzbl 0xed224(%%eax), %%edx\n\t"
      "jmp *.LFUN_000eceb0_jt(,%%edx,4)\n\t"
      ".LFUN_000eceb0_35:\n\t"
      "popl %%edi\n\t"
      "movw %%bx, 0x3c(%%esi)\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000eceb0_36:\n\t"
      "popl %%edi\n\t"
      "movw $1, 0x3c(%%esi)\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000eceb0_37:\n\t"
      "popl %%edi\n\t"
      "movw %%cx, 0x3c(%%esi)\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000eceb0_38:\n\t"
      "popl %%edi\n\t"
      "movw $3, 0x3c(%%esi)\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000eceb0_39:\n\t"
      "popl %%edi\n\t"
      "movw $4, 0x3c(%%esi)\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000eceb0_40:\n\t"
      "pushl $0x286550\n\t"
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
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_000eceb0_jt:\n\t"
      ".long .LFUN_000eceb0_35\n\t"
      ".long .LFUN_000eceb0_36\n\t"
      ".long .LFUN_000eceb0_37\n\t"
      ".long .LFUN_000eceb0_38\n\t"
      ".long .LFUN_000eceb0_39\n\t"
      ".long .LFUN_000eceb0_35\n\t"
      ".text\n\t"
      :
      : [ce0ec0] "m"(beceb0_ce0ec0), [assert] "m"(beceb0_assert), [exitfn] "m"(beceb0_exitfn), [c8f390] "m"(beceb0_c8f390)
      : "memory");
}
#else
#error "FUN_000eceb0: clang naked draft required"
#endif


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

/* draw_bitmap_in_rect (0xe3e80) — XBE naked draft (batch 108). */
#if defined(__clang__)
static void *(*const be3e80_memset)(void *, int, unsigned int) = (void *)csmemset;
static int (*const be3e80_cdeca0)(int interface_tag_index) = (void *)interface_get_tag_index;
static void *(*const be3e80_tag)(int, int) = (void *)tag_get;
static void *(*const be3e80_elem)(void *, int, int) = (void *)tag_block_get_element;
static unsigned int (*const be3e80_c8e370)(void) = (void *)system_milliseconds;
static void (*const be3e80_c1daf7e)(void) = (void *)FUN_001daf7e;
static void (*const be3e80_c17cfa0)(void *render_data, void *vertices) = (void *)rasterizer_sprites_render;

__attribute__((naked, noinline))
void draw_bitmap_in_rect(int bitmap, int16_t *src_rect, int16_t *dst_rect, int16_t *clip_rect, int flags, int param_6, int param_7)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x13c, %%esp\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "pushl %%esi\n\t"
      "xorl %%esi, %%esi\n\t"
      "cmpl %%esi, %%ecx\n\t"
      "je .Ldraw_bitmap_in_rect_17\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "cmpl %%esi, %%edx\n\t"
      "je .Ldraw_bitmap_in_rect_17\n\t"
      "movl 0x5aa460, %%eax\n\t"
      "movl %%eax, -0x54(%%ebp)\n\t"
      "movl 0x5aa464, %%eax\n\t"
      "movl %%eax, -0x50(%%ebp)\n\t"
      "movl 0x5aa468, %%eax\n\t"
      "movl %%eax, -0x4c(%%ebp)\n\t"
      "movl 0x5aa46c, %%eax\n\t"
      "movl %%eax, -0x48(%%ebp)\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "cmpl %%esi, %%eax\n\t"
      "movl $0x3f666666, -0x60(%%ebp)\n\t"
      "movl $0x3f666666, -0x5c(%%ebp)\n\t"
      "movl $0x3f666666, -0x58(%%ebp)\n\t"
      "movl $0x3f666666, -0x24(%%ebp)\n\t"
      "jne .Ldraw_bitmap_in_rect_1\n\t"
      "movw 0x4(%%ecx), %%ax\n\t"
      "movw 0x6(%%ecx), %%cx\n\t"
      "movw %%ax, -0xa(%%ebp)\n\t"
      "movw %%si, -0xe(%%ebp)\n\t"
      "movw %%si, -0x10(%%ebp)\n\t"
      "movw %%cx, -0xc(%%ebp)\n\t"
      "leal -0x10(%%ebp), %%eax\n\t"
      ".Ldraw_bitmap_in_rect_1:\n\t"
      "pushl %%ebx\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "movw 0x4(%%edx), %%bx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x6(%%edx), %%cx\n\t"
      "pushl %%edi\n\t"
      "xorl %%esi, %%esi\n\t"
      "movw 0x2(%%edx), %%si\n\t"
      "xorl %%edi, %%edi\n\t"
      "movw (%%edx), %%di\n\t"
      "movl %%ebx, %%edx\n\t"
      "movl %%ebx, -0x14(%%ebp)\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "movw 0x6(%%eax), %%bx\n\t"
      "subw 0x2(%%eax), %%bx\n\t"
      "movl %%ecx, -0x1c(%%ebp)\n\t"
      "subl %%esi, %%ecx\n\t"
      "movswl %%cx, %%ecx\n\t"
      "subl %%edi, %%edx\n\t"
      "movswl %%dx, %%edx\n\t"
      "movl %%ebx, -0x4(%%ebp)\n\t"
      "movw 0x4(%%eax), %%bx\n\t"
      "subw (%%eax), %%bx\n\t"
      "movswl %%si, %%eax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "movswl %%di, %%eax\n\t"
      "fildl -0x8(%%ebp)\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "fsts -0x44(%%ebp)\n\t"
      "addl %%eax, %%ecx\n\t"
      "fildl -0xc(%%ebp)\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "addl %%eax, %%edx\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "fsts -0x40(%%ebp)\n\t"
      "testl %%eax, %%eax\n\t"
      "fildl -0x8(%%ebp)\n\t"
      "movl %%edx, -0xc(%%ebp)\n\t"
      "fsts -0x3c(%%ebp)\n\t"
      "fxch %%st(1)\n\t"
      "fstps -0x38(%%ebp)\n\t"
      "fstps -0x34(%%ebp)\n\t"
      "fildl -0xc(%%ebp)\n\t"
      "fsts -0x30(%%ebp)\n\t"
      "fxch %%st(1)\n\t"
      "fstps -0x2c(%%ebp)\n\t"
      "fstps -0x28(%%ebp)\n\t"
      "je .Ldraw_bitmap_in_rect_5\n\t"
      "movw 0x2(%%eax), %%cx\n\t"
      "cmpw %%si, %%cx\n\t"
      "jle .Ldraw_bitmap_in_rect_2\n\t"
      "movswl %%cx, %%ecx\n\t"
      "movl %%ecx, -0xc(%%ebp)\n\t"
      "fildl -0xc(%%ebp)\n\t"
      "fsts -0x2c(%%ebp)\n\t"
      "fstps -0x44(%%ebp)\n\t"
      ".Ldraw_bitmap_in_rect_2:\n\t"
      "movw 0x6(%%eax), %%cx\n\t"
      "cmpw -0x1c(%%ebp), %%cx\n\t"
      "jge .Ldraw_bitmap_in_rect_3\n\t"
      "movswl %%cx, %%edx\n\t"
      "movl %%edx, -0x1c(%%ebp)\n\t"
      "fildl -0x1c(%%ebp)\n\t"
      "fsts -0x34(%%ebp)\n\t"
      "fstps -0x3c(%%ebp)\n\t"
      ".Ldraw_bitmap_in_rect_3:\n\t"
      "movw (%%eax), %%cx\n\t"
      "cmpw %%di, %%cx\n\t"
      "jle .Ldraw_bitmap_in_rect_4\n\t"
      "movswl %%cx, %%ecx\n\t"
      "movl %%ecx, -0x1c(%%ebp)\n\t"
      "fildl -0x1c(%%ebp)\n\t"
      "fsts -0x38(%%ebp)\n\t"
      "fstps -0x40(%%ebp)\n\t"
      ".Ldraw_bitmap_in_rect_4:\n\t"
      "movw 0x4(%%eax), %%ax\n\t"
      "cmpw -0x14(%%ebp), %%ax\n\t"
      "jge .Ldraw_bitmap_in_rect_5\n\t"
      "movswl %%ax, %%edx\n\t"
      "movl %%edx, -0x14(%%ebp)\n\t"
      "fildl -0x14(%%ebp)\n\t"
      "fsts -0x28(%%ebp)\n\t"
      "fstps -0x30(%%ebp)\n\t"
      ".Ldraw_bitmap_in_rect_5:\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "movswl 0x4(%%ecx), %%eax\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "fildl -0x14(%%ebp)\n\t"
      "flds 0x2533c8\n\t"
      "fcomp %%st(1)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Ldraw_bitmap_in_rect_6\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c8\n\t"
      ".Ldraw_bitmap_in_rect_6:\n\t"
      "movswl -0x4(%%ebp), %%edx\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      "fidivrs -0x4(%%ebp)\n\t"
      "fcoms 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Ldraw_bitmap_in_rect_7\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c8\n\t"
      ".Ldraw_bitmap_in_rect_7:\n\t"
      "movswl 0x6(%%ecx), %%eax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "fildl -0x4(%%ebp)\n\t"
      "flds 0x2533c8\n\t"
      "fcomp %%st(1)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Ldraw_bitmap_in_rect_8\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c8\n\t"
      ".Ldraw_bitmap_in_rect_8:\n\t"
      "movswl %%bx, %%ecx\n\t"
      "movl %%ecx, -0x4(%%ebp)\n\t"
      "fidivrs -0x4(%%ebp)\n\t"
      "fcoms 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Ldraw_bitmap_in_rect_9\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c8\n\t"
      ".Ldraw_bitmap_in_rect_9:\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "xorl %%eax, %%eax\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "leal -0x44(%%ebp), %%esi\n\t"
      "leal -0x134(%%ebp), %%ecx\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".Ldraw_bitmap_in_rect_10:\n\t"
      "movl 0x18(%%ebp), %%edx\n\t"
      "movl %%edx, 0x8(%%ecx)\n\t"
      "cdq\n\t"
      "movl $3, %%edi\n\t"
      "idivl %%edi\n\t"
      "testl %%edx, %%edx\n\t"
      "je .Ldraw_bitmap_in_rect_11\n\t"
      "fld %%st(1)\n\t"
      "jmp .Ldraw_bitmap_in_rect_12\n\t"
      ".Ldraw_bitmap_in_rect_11:\n\t"
      "flds 0x2533c0\n\t"
      ".Ldraw_bitmap_in_rect_12:\n\t"
      "cmpw $1, %%bx\n\t"
      "fstps (%%ecx)\n\t"
      "jle .Ldraw_bitmap_in_rect_13\n\t"
      "fld %%st(0)\n\t"
      "jmp .Ldraw_bitmap_in_rect_14\n\t"
      ".Ldraw_bitmap_in_rect_13:\n\t"
      "flds 0x2533c0\n\t"
      ".Ldraw_bitmap_in_rect_14:\n\t"
      "movl (%%esi), %%eax\n\t"
      "fstps 0x4(%%ecx)\n\t"
      "movl 0x4(%%esi), %%edx\n\t"
      "movl %%eax, -0x8(%%ecx)\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "incl %%ebx\n\t"
      "movl %%edx, -0x4(%%ecx)\n\t"
      "incl %%eax\n\t"
      "addl $8, %%esi\n\t"
      "addl $0x14, %%ecx\n\t"
      "cmpw $4, %%bx\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "jl .Ldraw_bitmap_in_rect_10\n\t"
      "pushl $0x8c\n\t"
      "fstp %%st(0)\n\t"
      "xorl %%edi, %%edi\n\t"
      "fstp %%st(0)\n\t"
      "leal -0xec(%%ebp), %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[memset]\n\t"
      "movb 0x20(%%ebp), %%al\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Ldraw_bitmap_in_rect_15\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "movl $0x3f800000, -0xa8(%%ebp)\n\t"
      "movl $0x3f800000, -0xac(%%ebp)\n\t"
      "movl $0x3f800000, -0xc0(%%ebp)\n\t"
      "movl $0x3f800000, -0xc4(%%ebp)\n\t"
      "movl %%ecx, -0xe0(%%ebp)\n\t"
      "jmp .Ldraw_bitmap_in_rect_16\n\t"
      ".Ldraw_bitmap_in_rect_15:\n\t"
      "pushl $0x30\n\t"
      "pushl %%edi\n\t"
      "pushl $0xf\n\t"
      "call *%[cdeca0]\n\t"
      "pushl %%eax\n\t"
      "pushl $0x6269746d\n\t"
      "call *%[tag]\n\t"
      "addl $0x60, %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "addl $0xc, %%esp\n\t"
      "movl %%eax, %%esi\n\t"
      "call *%[c8e370]\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "fildl -0x4(%%ebp)\n\t"
      "fsts -0x8(%%ebp)\n\t"
      "fmuls 0x283304\n\t"
      "fldl 0x2573d8\n\t"
      "call *%[c1daf7e]\n\t"
      "fmuls 0x283300\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fmuls 0x2832fc\n\t"
      "fldl 0x2573d8\n\t"
      "call *%[c1daf7e]\n\t"
      "fmuls 0x283300\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fmuls 0x2832f8\n\t"
      "fldl 0x2573d8\n\t"
      "call *%[c1daf7e]\n\t"
      "fchs\n\t"
      "fmuls 0x2832f4\n\t"
      "fstps -0x20(%%ebp)\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fmuls 0x2832f0\n\t"
      "fldl 0x2573d8\n\t"
      "call *%[c1daf7e]\n\t"
      "fchs\n\t"
      "leal -0x60(%%ebp), %%edx\n\t"
      "movl %%edx, -0x94(%%ebp)\n\t"
      "leal -0x24(%%ebp), %%eax\n\t"
      "leal -0x18(%%ebp), %%ecx\n\t"
      "leal -0x60(%%ebp), %%edx\n\t"
      "fmuls 0x2832f4\n\t"
      "movl %%eax, -0x74(%%ebp)\n\t"
      "leal -0x24(%%ebp), %%eax\n\t"
      "movl %%ecx, -0xd0(%%ebp)\n\t"
      "fstps -0x1c(%%ebp)\n\t"
      "movl %%edx, -0x90(%%ebp)\n\t"
      "movl -0x54(%%ebp), %%edx\n\t"
      "leal -0x20(%%ebp), %%ecx\n\t"
      "movl %%eax, -0x70(%%ebp)\n\t"
      "movl -0x50(%%ebp), %%eax\n\t"
      "movl %%esi, -0xe0(%%ebp)\n\t"
      "movw $5, -0x68(%%ebp)\n\t"
      "movl $0x3f800000, -0xc4(%%ebp)\n\t"
      "movl $0x3f800000, -0xc0(%%ebp)\n\t"
      "movb $1, -0xd4(%%ebp)\n\t"
      "movb $1, -0xe4(%%ebp)\n\t"
      "movl $0x3b52ba08, -0xac(%%ebp)\n\t"
      "movl $0x3b52ba08, -0xa8(%%ebp)\n\t"
      "movl %%esi, -0xdc(%%ebp)\n\t"
      "movl %%ecx, -0xcc(%%ebp)\n\t"
      "movw %%di, -0x66(%%ebp)\n\t"
      "movl $0x3f800000, -0xbc(%%ebp)\n\t"
      "movl $0x3f800000, -0xb8(%%ebp)\n\t"
      "movb $1, -0xd3(%%ebp)\n\t"
      "movb $1, -0xe3(%%ebp)\n\t"
      "movl $0x3ba3065e, -0xa4(%%ebp)\n\t"
      "movl $0x3ba3065e, -0xa0(%%ebp)\n\t"
      "movl %%edx, -0x88(%%ebp)\n\t"
      "movl -0x4c(%%ebp), %%ecx\n\t"
      "movl -0x48(%%ebp), %%edx\n\t"
      "movl %%eax, -0x84(%%ebp)\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl %%ecx, -0x80(%%ebp)\n\t"
      "movl %%edx, -0x7c(%%ebp)\n\t"
      "movl %%edi, -0x6c(%%ebp)\n\t"
      "movl $0x3f800000, -0x98(%%ebp)\n\t"
      "movl $0x3f800000, -0x9c(%%ebp)\n\t"
      "movl $0x3f800000, -0xb0(%%ebp)\n\t"
      "movl $0x3f800000, -0xb4(%%ebp)\n\t"
      "movl %%eax, -0xd8(%%ebp)\n\t"
      "movb $1, -0x78(%%ebp)\n\t"
      ".Ldraw_bitmap_in_rect_16:\n\t"
      "leal -0x13c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0xec(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl %%edi, -0xec(%%ebp)\n\t"
      "movb $0, -0x62(%%ebp)\n\t"
      "movw %%di, -0x64(%%ebp)\n\t"
      "call *%[c17cfa0]\n\t"
      "addl $8, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%ebx\n\t"
      ".Ldraw_bitmap_in_rect_17:\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [memset] "m"(be3e80_memset), [cdeca0] "m"(be3e80_cdeca0), [tag] "m"(be3e80_tag), [elem] "m"(be3e80_elem), [c8e370] "m"(be3e80_c8e370), [c1daf7e] "m"(be3e80_c1daf7e), [c17cfa0] "m"(be3e80_c17cfa0)
      : "memory");
}
#else
#error "draw_bitmap_in_rect: clang naked draft required"
#endif


/* FUN_000e4ad0 (0xe4ad0) — XBE naked draft (batch 120). */
#if defined(__clang__)
static scenario_t * (*const be4ad0_c18e380)(void) = (void *)global_scenario_get;
static void * (*const be4ad0_c18e450)(void) = (void *)game_globals_get;
static void *(*const be4ad0_elem)(void *, int, int) = (void *)tag_block_get_element;
static unsigned int (*const be4ad0_c8e370)(void) = (void *)system_milliseconds;
static void (*const be4ad0_cd16a0)(int bitmap_tag, short sequence_index, unsigned int frame_index, int *out_bitmap, int *out_sprite) = (void *)FUN_000d16a0;
static void *(*const be4ad0_xtex)(void *, bool, bool) = (void *)xbox_texture_cache_get_hardware_format;
static __int16 (*const be4ad0_cba4b0)(void) = (void *)local_player_count;
static float (*const be4ad0_cd1690)(int split_screen) = (void *)FUN_000d1690;
static void (*const be4ad0_ftol)(void) = (void *)FUN_001d9068;
static void (*const be4ad0_cd3200)(int bitmap_data, short screen_index, short *screen_pos, int uv_rect, float scale_value, float rotation, int color, char use_bitmap_size) = (void *)FUN_000d3200;

__attribute__((naked, noinline))
void FUN_000e4ad0(void *icon_state /*  */, int16_t *cursor /*  */, int string_index)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x14, %%esp\n\t"
      "call *%[c18e380]\n\t"
      "call *%[c18e450]\n\t"
      "movl 0x140(%%eax), %%ecx\n\t"
      "addl $0x140, %%eax\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .LFUN_000e4ad0_1\n\t"
      "pushl $0x130\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "addl $0xc, %%esp\n\t"
      "jmp .LFUN_000e4ad0_2\n\t"
      ".LFUN_000e4ad0_1:\n\t"
      "xorl %%eax, %%eax\n\t"
      ".LFUN_000e4ad0_2:\n\t"
      "movb 0xc(%%esi), %%cl\n\t"
      "pushl %%edi\n\t"
      "movl 0xec(%%eax), %%edi\n\t"
      "xorl %%eax, %%eax\n\t"
      "testb %%cl, %%cl\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "je .LFUN_000e4ad0_3\n\t"
      "call *%[c8e370]\n\t"
      "movl %%eax, %%ecx\n\t"
      "imull $0x1e, %%ecx, %%ecx\n\t"
      "movl $0x10624dd3, %%eax\n\t"
      "mull %%ecx\n\t"
      "movsbl 0xc(%%esi), %%ecx\n\t"
      "movl %%edx, %%eax\n\t"
      "shrl $6, %%eax\n\t"
      "xorl %%edx, %%edx\n\t"
      "divl %%ecx\n\t"
      ".LFUN_000e4ad0_3:\n\t"
      "leal -0x10(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw (%%esi), %%dx\n\t"
      "leal -0x4(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "call *%[cd16a0]\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "addl $0x14, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "popl %%edi\n\t"
      "je .LFUN_000e4ad0_8\n\t"
      "pushl $1\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "call *%[xtex]\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_000e4ad0_8\n\t"
      "call *%[cba4b0]\n\t"
      "cmpw $1, %%ax\n\t"
      "setg %%al\n\t"
      "pushl %%eax\n\t"
      "call *%[cd1690]\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "movswl 0x4(%%esi), %%ecx\n\t"
      "movswl 0x2(%%ebx), %%edx\n\t"
      "movl %%ecx, -0x14(%%ebp)\n\t"
      "addl $4, %%esp\n\t"
      "fildl -0x14(%%ebp)\n\t"
      "movl %%edx, -0x14(%%ebp)\n\t"
      "fmuls -0xc(%%ebp)\n\t"
      "fiaddl -0x14(%%ebp)\n\t"
      "fadds 0x2533c8\n\t"
      "call *%[ftol]\n\t"
      "movswl 0x6(%%esi), %%ecx\n\t"
      "movw %%ax, -0x8(%%ebp)\n\t"
      "movswl 0x4(%%ebx), %%eax\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "fildl -0x14(%%ebp)\n\t"
      "movl %%ecx, -0x14(%%ebp)\n\t"
      "fildl -0x14(%%ebp)\n\t"
      "fmuls -0xc(%%ebp)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fsubs 0x253f40\n\t"
      "call *%[ftol]\n\t"
      "movw %%ax, -0x6(%%ebp)\n\t"
      "testb $2, 0xd(%%esi)\n\t"
      "je .LFUN_000e4ad0_4\n\t"
      "movl 0x8(%%esi), %%eax\n\t"
      "jmp .LFUN_000e4ad0_5\n\t"
      ".LFUN_000e4ad0_4:\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      ".LFUN_000e4ad0_5:\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "pushl $0\n\t"
      "pushl %%edx\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "pushl %%eax\n\t"
      "leal -0x8(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $2\n\t"
      "pushl %%edx\n\t"
      "call *%[cd3200]\n\t"
      "movb 0xd(%%esi), %%al\n\t"
      "addl $0x20, %%esp\n\t"
      "testb $4, %%al\n\t"
      "je .LFUN_000e4ad0_6\n\t"
      "movw 0x2(%%esi), %%ax\n\t"
      "addw -0x8(%%ebp), %%ax\n\t"
      "movw %%ax, 0x2(%%ebx)\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000e4ad0_6:\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_000e4ad0_7\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "flds 0x4(%%eax)\n\t"
      "movswl 0x4(%%ecx), %%edx\n\t"
      "fsubs (%%eax)\n\t"
      "movswl 0x2(%%esi), %%eax\n\t"
      "movswl -0x8(%%ebp), %%ecx\n\t"
      "movl %%edx, -0x14(%%ebp)\n\t"
      "fimull -0x14(%%ebp)\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "fiaddl -0x14(%%ebp)\n\t"
      "movl %%ecx, -0x14(%%ebp)\n\t"
      "fiaddl -0x14(%%ebp)\n\t"
      "call *%[ftol]\n\t"
      "movw %%ax, 0x2(%%ebx)\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000e4ad0_7:\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x4(%%edx), %%ax\n\t"
      "addw 0x2(%%esi), %%ax\n\t"
      "addl %%ecx, %%eax\n\t"
      "movw %%ax, 0x2(%%ebx)\n\t"
      ".LFUN_000e4ad0_8:\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c18e380] "m"(be4ad0_c18e380), [c18e450] "m"(be4ad0_c18e450), [elem] "m"(be4ad0_elem), [c8e370] "m"(be4ad0_c8e370), [cd16a0] "m"(be4ad0_cd16a0), [xtex] "m"(be4ad0_xtex), [cba4b0] "m"(be4ad0_cba4b0), [cd1690] "m"(be4ad0_cd1690), [ftol] "m"(be4ad0_ftol), [cd3200] "m"(be4ad0_cd3200)
      : "memory");
}
#else
#error "FUN_000e4ad0: clang naked draft required"
#endif


/* remap_sticks_for_local_player (0xe4da0) — XBE naked draft (batch 122). */
#if defined(__clang__)
static int16_t (*const be4da0_ce4a80)(wchar_t *needle) = (void *)ui_widget_find_localized_string_index;
static void (*const be4da0_assert)(const char *, const char *, int, bool) = (void *)display_assert;
static void (*const be4da0_exitfn)(int) = (void *)system_exit;
static char (*const be4da0_ce4d40)(int16_t player_index) = (void *)ui_widget_player_prefers_metric_units;

__attribute__((naked, noinline))
int16_t remap_sticks_for_local_player(int16_t icon_type, int local_player_index)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movswl %%ax, %%ecx\n\t"
      "addl $-0x10, %%ecx\n\t"
      "cmpl $0xf, %%ecx\n\t"
      "ja .Lremap_sticks_for_local_player_8\n\t"
      "movzbl 0xe4eb8(%%ecx), %%ecx\n\t"
      "pushl %%ebx\n\t"
      "jmp *.Lremap_sticks_for_local_player_jt(,%%ecx,4)\n\t"
      ".Lremap_sticks_for_local_player_1:\n\t"
      "movl $0x283038, %%ebx\n\t"
      "call *%[ce4a80]\n\t"
      "cmpw $0x10, %%ax\n\t"
      "je .Lremap_sticks_for_local_player_2\n\t"
      "pushl $1\n\t"
      "pushl $0x1093\n\t"
      "pushl $0x283280\n\t"
      "pushl $0x283698\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lremap_sticks_for_local_player_2:\n\t"
      "movl $0x282f04, %%ebx\n\t"
      "call *%[ce4a80]\n\t"
      "cmpw $0x1e, %%ax\n\t"
      "je .Lremap_sticks_for_local_player_3\n\t"
      "pushl $1\n\t"
      "pushl $0x1094\n\t"
      "pushl $0x283280\n\t"
      "pushl $0x283678\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lremap_sticks_for_local_player_3:\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "call *%[ce4d40]\n\t"
      "negb %%al\n\t"
      "popl %%ebx\n\t"
      "sbbl %%eax, %%eax\n\t"
      "negl %%eax\n\t"
      "addl $0x10, %%eax\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lremap_sticks_for_local_player_4:\n\t"
      "movl $0x283020, %%ebx\n\t"
      "call *%[ce4a80]\n\t"
      "cmpw $0x11, %%ax\n\t"
      "je .Lremap_sticks_for_local_player_5\n\t"
      "pushl $1\n\t"
      "pushl $0x109a\n\t"
      "pushl $0x283280\n\t"
      "pushl $0x283654\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lremap_sticks_for_local_player_5:\n\t"
      "movl $0x282ef8, %%ebx\n\t"
      "call *%[ce4a80]\n\t"
      "cmpw $0x1f, %%ax\n\t"
      "je .Lremap_sticks_for_local_player_6\n\t"
      "pushl $1\n\t"
      "pushl $0x109b\n\t"
      "pushl $0x283280\n\t"
      "pushl $0x283634\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lremap_sticks_for_local_player_6:\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "call *%[ce4d40]\n\t"
      "negb %%al\n\t"
      "sbbl %%eax, %%eax\n\t"
      "addl $0x11, %%eax\n\t"
      ".Lremap_sticks_for_local_player_7:\n\t"
      "popl %%ebx\n\t"
      ".Lremap_sticks_for_local_player_8:\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".Lremap_sticks_for_local_player_jt:\n\t"
      ".long .Lremap_sticks_for_local_player_1\n\t"
      ".long .Lremap_sticks_for_local_player_4\n\t"
      ".long .Lremap_sticks_for_local_player_7\n\t"
      ".text\n\t"
      :
      : [ce4a80] "m"(be4da0_ce4a80), [assert] "m"(be4da0_assert), [exitfn] "m"(be4da0_exitfn), [ce4d40] "m"(be4da0_ce4d40)
      : "memory");
}
#else
#error "remap_sticks_for_local_player: clang naked draft required"
#endif


/* FUN_000e5180 (0xe5180) — XBE naked draft (batch 113). */
#if defined(__clang__)
static int (*const be5180_c19d8c0)(const unsigned short *s) = (void *)ustrlen;
static wchar_t * (*const be5180_c19ded0)(const wchar_t *haystack, const wchar_t *needle) = (void *)ustrstr;
static void * (*const be5180_c8e0b0)(void *destination, void *source, size_t size) = (void *)csmemcpy;
static void (*const be5180_c8dae0)(void *dest, const void *src, unsigned int size) = (void *)csmemmove;
static void * (*const be5180_c11fbe0)(void *pool, int block, unsigned short new_size, const char *file, unsigned int line) = (void *)stack_memory_pool_realloc;

__attribute__((naked, noinline))
int FUN_000e5180(wchar_t *text, wchar_t *replacement, void **pool_block)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x10, %%esp\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "xorl %%eax, %%eax\n\t"
      "testl %%ecx, %%ecx\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "je .LFUN_000e5180_10\n\t"
      "pushl %%ebx\n\t"
      "movl (%%ecx), %%ebx\n\t"
      "testl %%ebx, %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl %%ebx, -0x8(%%ebp)\n\t"
      "je .LFUN_000e5180_9\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "pushl %%esi\n\t"
      "call *%[c19d8c0]\n\t"
      "movl %%eax, %%edi\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c19d8c0]\n\t"
      "pushl %%ebx\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "call *%[c19d8c0]\n\t"
      "movl -0x10(%%ebp), %%ecx\n\t"
      "addl $0xc, %%esp\n\t"
      "movl %%eax, %%ebx\n\t"
      "incl %%ebx\n\t"
      "cmpl %%edi, %%ecx\n\t"
      "pushl %%esi\n\t"
      "jg .LFUN_000e5180_3\n\t"
      "movl %%edi, %%eax\n\t"
      "subl %%ecx, %%eax\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "call *%[c19ded0]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $8, %%esp\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_000e5180_8\n\t"
      ".LFUN_000e5180_1:\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "incl %%edx\n\t"
      "addl %%eax, %%eax\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%esi\n\t"
      "call *%[c8e0b0]\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jle .LFUN_000e5180_2\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "movl %%esi, %%ecx\n\t"
      "subl %%edx, %%ecx\n\t"
      "sarl $1, %%ecx\n\t"
      "addl %%eax, %%ecx\n\t"
      "movl %%ebx, %%edx\n\t"
      "subl %%ecx, %%edx\n\t"
      "shll $1, %%edx\n\t"
      "pushl %%edx\n\t"
      "leal (%%esi,%%edi,2), %%ecx\n\t"
      "addl %%eax, %%eax\n\t"
      "pushl %%ecx\n\t"
      "addl %%esi, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c8dae0]\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "subl %%eax, %%ebx\n\t"
      ".LFUN_000e5180_2:\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c19ded0]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $8, %%esp\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LFUN_000e5180_1\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000e5180_3:\n\t"
      "subl %%edi, %%ecx\n\t"
      "movl %%ecx, -0xc(%%ebp)\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c19ded0]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_000e5180_8\n\t"
      ".LFUN_000e5180_4:\n\t"
      "incl -0x4(%%ebp)\n\t"
      "leal (%%eax,%%edi,2), %%edx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edx\n\t"
      "call *%[c19ded0]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_000e5180_4\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jle .LFUN_000e5180_9\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "imull %%eax, %%ecx\n\t"
      "movl 0x31e04c, %%eax\n\t"
      "pushl $0x1382\n\t"
      "addl %%ebx, %%ecx\n\t"
      "pushl $0x283280\n\t"
      "shll $1, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c11fbe0]\n\t"
      "addl $0x14, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "jne .LFUN_000e5180_5\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "orl $0xffffffff, %%eax\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000e5180_5:\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "call *%[c19ded0]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $8, %%esp\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_000e5180_7\n\t"
      "movl -0x10(%%ebp), %%ecx\n\t"
      "leal (%%ecx,%%ecx,1), %%edx\n\t"
      "movl %%edx, -0x10(%%ebp)\n\t"
      ".LFUN_000e5180_6:\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movl %%esi, %%eax\n\t"
      "subl %%ecx, %%eax\n\t"
      "sarl $1, %%eax\n\t"
      "addl %%edi, %%eax\n\t"
      "movl %%ebx, %%ecx\n\t"
      "subl %%eax, %%ecx\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "shll $1, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal (%%esi,%%edi,2), %%edx\n\t"
      "pushl %%edx\n\t"
      "addl %%esi, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c8dae0]\n\t"
      "movl -0x10(%%ebp), %%ecx\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%esi\n\t"
      "call *%[c8e0b0]\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "addl %%eax, %%ebx\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c19ded0]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $0x20, %%esp\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LFUN_000e5180_6\n\t"
      ".LFUN_000e5180_7:\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "movl %%edx, (%%eax)\n\t"
      ".LFUN_000e5180_8:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      ".LFUN_000e5180_9:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      ".LFUN_000e5180_10:\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c19d8c0] "m"(be5180_c19d8c0), [c19ded0] "m"(be5180_c19ded0), [c8e0b0] "m"(be5180_c8e0b0), [c8dae0] "m"(be5180_c8dae0), [c11fbe0] "m"(be5180_c11fbe0)
      : "memory");
}
#else
#error "FUN_000e5180: clang naked draft required"
#endif


/* FUN_000e5b10 (0xe5b10) — XBE naked draft (batch 111). */
#if defined(__clang__)
static void (*const be5b10_assert)(const char *, const char *, int, bool) = (void *)display_assert;
static void (*const be5b10_exitfn)(int) = (void *)system_exit;
static void *(*const be5b10_tag)(int, int) = (void *)tag_get;
static void * (*const be5b10_ce84e0)(const char *name, int tag_index, int is_child, int widget_stack, int parent_tag_index, int a6, int a7) = (void *)ui_widget_load_by_name_or_tag;
static void (*const be5b10_ce4800)(void *parent, void *child) = (void *)ui_widget_link_child;
static void (*const be5b10_c8f390)(unsigned __int16 a1, const char *a2, ...) = (void *)error;

__attribute__((naked, noinline))
void FUN_000e5b10(void *widget /*  */, void *draw_state /*  */)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xc, %%esp\n\t"
      "pushl %%ebx\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "testb $2, 0x150(%%ebx)\n\t"
      "pushl %%edi\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "je .LFUN_000e5b10_7\n\t"
      "cmpw $2, 0xe(%%esi)\n\t"
      "je .LFUN_000e5b10_1\n\t"
      "pushl $1\n\t"
      "pushl $0xa20\n\t"
      "pushl $0x283280\n\t"
      "pushl $0x283930\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000e5b10_1:\n\t"
      "movl 0x3e0(%%ebx), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_000e5b10_2\n\t"
      "pushl $1\n\t"
      "pushl $0xa22\n\t"
      "pushl $0x283280\n\t"
      "pushl $0x2838c0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000e5b10_2:\n\t"
      "cmpl $-1, 0xf8(%%ebx)\n\t"
      "jne .LFUN_000e5b10_3\n\t"
      "pushl $1\n\t"
      "pushl $0xa24\n\t"
      "pushl $0x283280\n\t"
      "pushl $0x283860\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000e5b10_3:\n\t"
      "movl 0xf8(%%ebx), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x75737472\n\t"
      "call *%[tag]\n\t"
      "movb $1, 0x46cc83\n\t"
      "movl (%%eax), %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "xorl %%edi, %%edi\n\t"
      "testl %%ecx, %%ecx\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "jle .LFUN_000e5b10_6\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_000e5b10_4:\n\t"
      "movl (%%esi), %%edx\n\t"
      "pushl $-1\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x8(%%esi), %%cx\n\t"
      "pushl $-1\n\t"
      "pushl $-1\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edx\n\t"
      "pushl $0\n\t"
      "call *%[ce84e0]\n\t"
      "addl $0x1c, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_000e5b10_5\n\t"
      "pushl %%esi\n\t"
      "movl %%eax, %%ebx\n\t"
      "call *%[ce4800]\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "addl $4, %%esp\n\t"
      "incw 0x44(%%esi)\n\t"
      "movl (%%eax), %%ecx\n\t"
      "incl %%edi\n\t"
      "cmpl %%ecx, %%edi\n\t"
      "jl .LFUN_000e5b10_4\n\t"
      "jmp .LFUN_000e5b10_6\n\t"
      ".LFUN_000e5b10_5:\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      ".LFUN_000e5b10_6:\n\t"
      "movb $0, 0x46cc83\n\t"
      ".LFUN_000e5b10_7:\n\t"
      "movl 0x3e0(%%ebx), %%ecx\n\t"
      "xorl %%eax, %%eax\n\t"
      "cmpl %%eax, %%ecx\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "jle .LFUN_000e5b10_13\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "movl %%edi, %%edi\n\t"
      ".LFUN_000e5b10_8:\n\t"
      "movl 0x3e4(%%ebx), %%ebx\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movb 0x30(%%ebx,%%ecx,1), %%al\n\t"
      "movw 0x8(%%esi), %%di\n\t"
      "addl %%ecx, %%ebx\n\t"
      "testb $1, %%al\n\t"
      "je .LFUN_000e5b10_10\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x34(%%ebx), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "jl .LFUN_000e5b10_9\n\t"
      "cmpw $4, %%ax\n\t"
      "jge .LFUN_000e5b10_9\n\t"
      "movl %%eax, %%edi\n\t"
      "jmp .LFUN_000e5b10_10\n\t"
      ".LFUN_000e5b10_9:\n\t"
      "movswl %%ax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x283820\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_000e5b10_10:\n\t"
      "movl 0xc(%%ebx), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_000e5b10_11\n\t"
      "pushl $-1\n\t"
      "pushl $-1\n\t"
      "pushl $-1\n\t"
      "pushl %%edi\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "pushl $0\n\t"
      "call *%[ce84e0]\n\t"
      "addl $0x1c, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_000e5b10_12\n\t"
      "movw 0x38(%%ebx), %%dx\n\t"
      "addw 0xa(%%esi), %%dx\n\t"
      "pushl %%esi\n\t"
      "movw %%dx, 0xa(%%eax)\n\t"
      "movw 0x36(%%ebx), %%cx\n\t"
      "addw 0xc(%%esi), %%cx\n\t"
      "movl %%eax, %%ebx\n\t"
      "movw %%cx, 0xc(%%eax)\n\t"
      "call *%[ce4800]\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_000e5b10_11:\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "addl $0x50, %%edx\n\t"
      "movl %%edx, -0x8(%%ebp)\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "movl 0x3e0(%%edx), %%ecx\n\t"
      "incl %%eax\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "movl %%edx, %%ebx\n\t"
      "jl .LFUN_000e5b10_8\n\t"
      "jmp .LFUN_000e5b10_13\n\t"
      ".LFUN_000e5b10_12:\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      ".LFUN_000e5b10_13:\n\t"
      "cmpw $3, 0xe(%%esi)\n\t"
      "jne .LFUN_000e5b10_15\n\t"
      "movl 0x1b0(%%ebx), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_000e5b10_15\n\t"
      "pushl $-1\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x8(%%esi), %%cx\n\t"
      "pushl $-1\n\t"
      "pushl $-1\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "pushl $0\n\t"
      "call *%[ce84e0]\n\t"
      "addl $0x1c, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%eax, 0x48(%%esi)\n\t"
      "je .LFUN_000e5b10_15\n\t"
      "movl 0x28(%%eax), %%eax\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "je .LFUN_000e5b10_14\n\t"
      "movl %%ecx, 0x2c(%%eax)\n\t"
      ".LFUN_000e5b10_14:\n\t"
      "movl 0x48(%%esi), %%edx\n\t"
      "movl %%ecx, 0x28(%%edx)\n\t"
      "movl 0x48(%%esi), %%eax\n\t"
      "movl %%ecx, 0x30(%%eax)\n\t"
      ".LFUN_000e5b10_15:\n\t"
      "movl 0x2c(%%ebx), %%ebx\n\t"
      "testb %%bl, %%bl\n\t"
      "js .LFUN_000e5b10_21\n\t"
      "movw 0xe(%%esi), %%ax\n\t"
      "cmpw $2, %%ax\n\t"
      "je .LFUN_000e5b10_16\n\t"
      "cmpw $3, %%ax\n\t"
      "je .LFUN_000e5b10_16\n\t"
      "testb $1, %%bl\n\t"
      "je .LFUN_000e5b10_21\n\t"
      "jmp .LFUN_000e5b10_17\n\t"
      ".LFUN_000e5b10_16:\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw %%ax, 0x3c(%%esi)\n\t"
      "movw %%ax, 0x3e(%%esi)\n\t"
      ".LFUN_000e5b10_17:\n\t"
      "movl 0x34(%%esi), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "je .LFUN_000e5b10_21\n\t"
      ".LFUN_000e5b10_18:\n\t"
      "movw 0xe(%%esi), %%ax\n\t"
      "cmpw $2, %%ax\n\t"
      "je .LFUN_000e5b10_20\n\t"
      "cmpw $3, %%ax\n\t"
      "je .LFUN_000e5b10_20\n\t"
      "movl (%%edi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x44654c61\n\t"
      "call *%[tag]\n\t"
      "movb 0x12(%%edi), %%cl\n\t"
      "addl $8, %%esp\n\t"
      "testb %%cl, %%cl\n\t"
      "jne .LFUN_000e5b10_19\n\t"
      "movl 0x54(%%eax), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "jg .LFUN_000e5b10_20\n\t"
      "movw 0xe(%%edi), %%ax\n\t"
      "cmpw $2, %%ax\n\t"
      "je .LFUN_000e5b10_20\n\t"
      "cmpw $3, %%ax\n\t"
      "je .LFUN_000e5b10_20\n\t"
      ".LFUN_000e5b10_19:\n\t"
      "movl 0x2c(%%edi), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .LFUN_000e5b10_18\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "popl %%edi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000e5b10_20:\n\t"
      "movl %%edi, 0x38(%%esi)\n\t"
      ".LFUN_000e5b10_21:\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "popl %%edi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(be5b10_assert), [exitfn] "m"(be5b10_exitfn), [tag] "m"(be5b10_tag), [ce84e0] "m"(be5b10_ce84e0), [ce4800] "m"(be5b10_ce4800), [c8f390] "m"(be5b10_c8f390)
      : "memory");
}
#else
#error "FUN_000e5b10: clang naked draft required"
#endif


/* draw_string_and_hack_in_icons (0xe5de0) — XBE naked draft (batch 109). */
#if defined(__clang__)
static void (*const be5de0_c1db180)(void) = (void *)_wcscpy;
static wchar_t * (*const be5de0_c1db134)(const wchar_t *s, wchar_t c) = (void *)_wcschr;
static void (*const be5de0_c8f390)(unsigned __int16 a1, const char *a2, ...) = (void *)error;
static void (*const be5de0_c19b5d0)(int width, int height) = (void *)draw_string_set_indents;
static void (*const be5de0_c19cdb0)(short *out_rect, void *text, short *out_bounds, short *in_rect) = (void *)FUN_0019cdb0;
static void (*const be5de0_c184060)(void *screen_pos, short *bounds, const void *color, int flags, unsigned short *text) = (void *)rasterizer_draw_string;
static int16_t (*const be5de0_ce4a80)(wchar_t *needle) = (void *)ui_widget_find_localized_string_index;
static size_t (*const be5de0_c1db11e)(const wchar_t *str) = (void *)_wcslen;
static int16_t (*const be5de0_ce4da0)(int16_t icon_type, int local_player_index) = (void *)remap_sticks_for_local_player;
static void (*const be5de0_cce6c0)(short local_player_index, void *preferences_out) = (void *)input_abstraction_get_local_player_preferences;
static void (*const be5de0_assert)(const char *, const char *, int, bool) = (void *)display_assert;
static void (*const be5de0_exitfn)(int) = (void *)system_exit;
static void *(*const be5de0_elem)(void *, int, int) = (void *)tag_block_get_element;
static void (*const be5de0_c7af20)(unsigned int color, float *dst) = (void *)pixel32_to_real_argb_color;
static void (*const be5de0_c19b790)(void) = (void *)draw_string_get_color;
static void (*const be5de0_ftol)(void) = (void *)FUN_001d9068;
static unsigned int (*const be5de0_d1c90)(float *) = (void *)FUN_000d1c90;
static void (*const be5de0_ce4ad0)(void *icon_state /* */, int16_t *cursor /* */, int string_index) = (void *)FUN_000e4ad0;
static void (*const be5de0_ce4c70)(void *draw_state, void *cursor, int string_index) = (void *)FUN_000e4c70;

__attribute__((naked, noinline))
void draw_string_and_hack_in_icons(int16_t *rect, int param_2, int param_3, int param_4, wchar_t *text, int local_player_index)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x5c, %%esp\n\t"
      "movl 0x18(%%ebp), %%edx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "movl (%%esi), %%eax\n\t"
      "movl 0x4(%%esi), %%ecx\n\t"
      "pushl %%edi\n\t"
      "movl $0x46c420, %%edi\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "movl %%edi, -0x8(%%ebp)\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "movl %%ecx, -0x10(%%ebp)\n\t"
      "call *%[c1db180]\n\t"
      "addl $8, %%esp\n\t"
      "jmp .Ldraw_string_and_hack_in_icons_2\n\t"
      ".Ldraw_string_and_hack_in_icons_1:\n\t"
      "movl -0x8(%%ebp), %%edi\n\t"
      ".Ldraw_string_and_hack_in_icons_2:\n\t"
      "pushl $0x25\n\t"
      "pushl %%edi\n\t"
      "call *%[c1db134]\n\t"
      "movl %%eax, %%ebx\n\t"
      "addl $8, %%esp\n\t"
      "testl %%ebx, %%ebx\n\t"
      "je .Ldraw_string_and_hack_in_icons_20\n\t"
      "movw $0, (%%ebx)\n\t"
      "movw -0x12(%%ebp), %%di\n\t"
      "subw 0x2(%%esi), %%di\n\t"
      "addl $2, %%ebx\n\t"
      "testw %%di, %%di\n\t"
      "jge .Ldraw_string_and_hack_in_icons_3\n\t"
      "pushl $0x2835f0\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "testw %%di, %%di\n\t"
      "jge .Ldraw_string_and_hack_in_icons_3\n\t"
      "xorl %%edi, %%edi\n\t"
      ".Ldraw_string_and_hack_in_icons_3:\n\t"
      "pushl $0\n\t"
      "pushl %%edi\n\t"
      "call *%[c19b5d0]\n\t"
      "movl -0x8(%%ebp), %%edi\n\t"
      "leal -0x14(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x1c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edi\n\t"
      "pushl %%esi\n\t"
      "call *%[c19cdb0]\n\t"
      "movw 0x2(%%esi), %%dx\n\t"
      "addw $-3, -0x12(%%ebp)\n\t"
      "pushl %%edi\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "leal -0x1c(%%ebp), %%eax\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "movw %%dx, -0x1a(%%ebp)\n\t"
      "call *%[c184060]\n\t"
      "movw -0x14(%%ebp), %%cx\n\t"
      "addl $0x2c, %%esp\n\t"
      "movw %%cx, (%%esi)\n\t"
      "movl %%ebx, -0x8(%%ebp)\n\t"
      "call *%[ce4a80]\n\t"
      "movl %%eax, %%edi\n\t"
      "cmpw $-1, %%di\n\t"
      "jne .Ldraw_string_and_hack_in_icons_5\n\t"
      "movw -0x12(%%ebp), %%di\n\t"
      "subw 0x2(%%esi), %%di\n\t"
      "testw %%di, %%di\n\t"
      "jge .Ldraw_string_and_hack_in_icons_4\n\t"
      "pushl $0x2835f0\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "testw %%di, %%di\n\t"
      "jge .Ldraw_string_and_hack_in_icons_4\n\t"
      "xorl %%edi, %%edi\n\t"
      ".Ldraw_string_and_hack_in_icons_4:\n\t"
      "pushl $0\n\t"
      "pushl %%edi\n\t"
      "call *%[c19b5d0]\n\t"
      "leal -0x14(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x24(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x2839c4\n\t"
      "pushl %%esi\n\t"
      "call *%[c19cdb0]\n\t"
      "movw 0x2(%%esi), %%cx\n\t"
      "addw $-3, -0x12(%%ebp)\n\t"
      "pushl $0x2839c4\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "leal -0x24(%%ebp), %%edx\n\t"
      "pushl $0\n\t"
      "pushl %%edx\n\t"
      "movw %%cx, -0x22(%%ebp)\n\t"
      "call *%[c184060]\n\t"
      "movw -0x14(%%ebp), %%ax\n\t"
      "addl $0x2c, %%esp\n\t"
      "movw %%ax, (%%esi)\n\t"
      "jmp .Ldraw_string_and_hack_in_icons_19\n\t"
      ".Ldraw_string_and_hack_in_icons_5:\n\t"
      "movswl %%di, %%ecx\n\t"
      "movl 0x31e098(,%%ecx,4), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c1db11e]\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x5aa45c, %%cx\n\t"
      "leal (%%ebx,%%eax,2), %%eax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edi\n\t"
      "call *%[ce4da0]\n\t"
      "addl $0xc, %%esp\n\t"
      "orl $0xffffffff, %%ebx\n\t"
      "movl %%eax, %%esi\n\t"
      "cmpw $0x11, %%si\n\t"
      "jle .Ldraw_string_and_hack_in_icons_12\n\t"
      "cmpw $0x1f, %%si\n\t"
      "jg .Ldraw_string_and_hack_in_icons_11\n\t"
      "cmpw $0x1c, %%si\n\t"
      "jg .Ldraw_string_and_hack_in_icons_6\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x5aa45c, %%ax\n\t"
      "leal -0x5c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[cce6c0]\n\t"
      "movswl %%si, %%ecx\n\t"
      "movsbl 0x31e126(%%ecx), %%edx\n\t"
      "movzbw -0x54(%%ebp,%%edx,1), %%bx\n\t"
      "addl $8, %%esp\n\t"
      "jmp .Ldraw_string_and_hack_in_icons_13\n\t"
      ".Ldraw_string_and_hack_in_icons_6:\n\t"
      "movswl %%si, %%eax\n\t"
      "movsbw 0x31e126(%%eax), %%bx\n\t"
      "addl $-0x1c, %%eax\n\t"
      "cmpl $3, %%eax\n\t"
      "ja .Ldraw_string_and_hack_in_icons_13\n\t"
      "jmp *.Ldraw_string_and_hack_in_icons_jt(,%%eax,4)\n\t"
      ".Ldraw_string_and_hack_in_icons_7:\n\t"
      "movl $0xc, %%ebx\n\t"
      "jmp .Ldraw_string_and_hack_in_icons_13\n\t"
      ".Ldraw_string_and_hack_in_icons_8:\n\t"
      "movl $0xd, %%ebx\n\t"
      "jmp .Ldraw_string_and_hack_in_icons_13\n\t"
      ".Ldraw_string_and_hack_in_icons_9:\n\t"
      "movl $0x10, %%ebx\n\t"
      "jmp .Ldraw_string_and_hack_in_icons_13\n\t"
      ".Ldraw_string_and_hack_in_icons_10:\n\t"
      "movl $0x11, %%ebx\n\t"
      "jmp .Ldraw_string_and_hack_in_icons_13\n\t"
      ".Ldraw_string_and_hack_in_icons_11:\n\t"
      "pushl $1\n\t"
      "pushl $0x10f5\n\t"
      "pushl $0x283280\n\t"
      "pushl $0x2839bc\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "jmp .Ldraw_string_and_hack_in_icons_13\n\t"
      ".Ldraw_string_and_hack_in_icons_12:\n\t"
      "movl %%esi, %%ebx\n\t"
      ".Ldraw_string_and_hack_in_icons_13:\n\t"
      "movl 0x46bd0c, %%eax\n\t"
      "movswl %%bx, %%edi\n\t"
      "pushl $0x10\n\t"
      "addl $0xc4, %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl %%eax, %%esi\n\t"
      "movb 0xd(%%esi), %%cl\n\t"
      "movw 0x2(%%esi), %%dx\n\t"
      "leal -0x34(%%ebp), %%eax\n\t"
      "movb %%cl, -0x1(%%ebp)\n\t"
      "movl 0x8(%%esi), %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "movw %%dx, -0xc(%%ebp)\n\t"
      "call *%[c7af20]\n\t"
      "movb 0xd(%%esi), %%cl\n\t"
      "andb $0xfd, %%cl\n\t"
      "addl $0x14, %%esp\n\t"
      "testw %%bx, %%bx\n\t"
      "movb %%cl, 0xd(%%esi)\n\t"
      "jl .Ldraw_string_and_hack_in_icons_14\n\t"
      "cmpw $0x12, %%bx\n\t"
      "jl .Ldraw_string_and_hack_in_icons_15\n\t"
      ".Ldraw_string_and_hack_in_icons_14:\n\t"
      "pushl $1\n\t"
      "pushl $0x110a\n\t"
      "pushl $0x283280\n\t"
      "pushl $0x283994\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Ldraw_string_and_hack_in_icons_15:\n\t"
      "movb 0x31e080(%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Ldraw_string_and_hack_in_icons_16\n\t"
      "andb $0xfb, 0xd(%%esi)\n\t"
      "movw $0xfffb, 0x2(%%esi)\n\t"
      ".Ldraw_string_and_hack_in_icons_16:\n\t"
      "leal -0x44(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c19b790]\n\t"
      "flds -0x44(%%ebp)\n\t"
      "fmuls 0x2602c8\n\t"
      "addl $4, %%esp\n\t"
      "call *%[ftol]\n\t"
      "movl %%eax, %%edi\n\t"
      "movl 0x8(%%esi), %%eax\n\t"
      "shll $0x18, %%edi\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Ldraw_string_and_hack_in_icons_17\n\t"
      "movb 0x1c(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Ldraw_string_and_hack_in_icons_18\n\t"
      ".Ldraw_string_and_hack_in_icons_17:\n\t"
      "movl -0x44(%%ebp), %%eax\n\t"
      "movl -0x40(%%ebp), %%ecx\n\t"
      "movl -0x3c(%%ebp), %%edx\n\t"
      "movl %%eax, -0x34(%%ebp)\n\t"
      "movl -0x38(%%ebp), %%eax\n\t"
      "movl %%ecx, -0x30(%%ebp)\n\t"
      "movl %%edx, -0x2c(%%ebp)\n\t"
      "movl %%eax, -0x28(%%ebp)\n\t"
      ".Ldraw_string_and_hack_in_icons_18:\n\t"
      "flds -0x30(%%ebp)\n\t"
      "leal -0x34(%%ebp), %%ecx\n\t"
      "fmuls -0x44(%%ebp)\n\t"
      "pushl %%ecx\n\t"
      "fstps -0x30(%%ebp)\n\t"
      "flds -0x2c(%%ebp)\n\t"
      "fmuls -0x44(%%ebp)\n\t"
      "fstps -0x2c(%%ebp)\n\t"
      "flds -0x28(%%ebp)\n\t"
      "fmuls -0x44(%%ebp)\n\t"
      "fstps -0x28(%%ebp)\n\t"
      "call *%[d1c90]\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "andl $0xffffff, %%eax\n\t"
      "orl %%edi, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%edx\n\t"
      "leal -0x14(%%ebp), %%ebx\n\t"
      "call *%[ce4ad0]\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movw -0xc(%%ebp), %%cx\n\t"
      "addl $0xc, %%esp\n\t"
      "incw 0x2(%%eax)\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "movb %%al, 0xd(%%esi)\n\t"
      "movw %%cx, 0x2(%%esi)\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      ".Ldraw_string_and_hack_in_icons_19:\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Ldraw_string_and_hack_in_icons_1\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "call *%[c19b5d0]\n\t"
      "addl $8, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Ldraw_string_and_hack_in_icons_20:\n\t"
      "testl %%edi, %%edi\n\t"
      "je .Ldraw_string_and_hack_in_icons_21\n\t"
      "pushl %%edi\n\t"
      "leal -0x14(%%ebp), %%edi\n\t"
      "movl %%esi, %%ebx\n\t"
      "call *%[ce4c70]\n\t"
      "addl $4, %%esp\n\t"
      ".Ldraw_string_and_hack_in_icons_21:\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "call *%[c19b5d0]\n\t"
      "addl $8, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".Ldraw_string_and_hack_in_icons_jt:\n\t"
      ".long .Ldraw_string_and_hack_in_icons_7\n\t"
      ".long .Ldraw_string_and_hack_in_icons_8\n\t"
      ".long .Ldraw_string_and_hack_in_icons_9\n\t"
      ".long .Ldraw_string_and_hack_in_icons_10\n\t"
      ".text\n\t"
      :
      : [c1db180] "m"(be5de0_c1db180), [c1db134] "m"(be5de0_c1db134), [c8f390] "m"(be5de0_c8f390), [c19b5d0] "m"(be5de0_c19b5d0), [c19cdb0] "m"(be5de0_c19cdb0), [c184060] "m"(be5de0_c184060), [ce4a80] "m"(be5de0_ce4a80), [c1db11e] "m"(be5de0_c1db11e), [ce4da0] "m"(be5de0_ce4da0), [cce6c0] "m"(be5de0_cce6c0), [assert] "m"(be5de0_assert), [exitfn] "m"(be5de0_exitfn), [elem] "m"(be5de0_elem), [c7af20] "m"(be5de0_c7af20), [c19b790] "m"(be5de0_c19b790), [ftol] "m"(be5de0_ftol), [d1c90] "m"(be5de0_d1c90), [ce4ad0] "m"(be5de0_ce4ad0), [ce4c70] "m"(be5de0_ce4c70)
      : "memory");
}
#else
#error "draw_string_and_hack_in_icons: clang naked draft required"
#endif


/* FUN_000e6140 (0xe6140) — XBE naked draft (batch 109). */
#if defined(__clang__)
static int (*const be6140_c19d420)(int param_1, int param_2) = (void *)FUN_0019d420;
static int (*const be6140_c19d8c0)(const unsigned short *s) = (void *)ustrlen;
static void * (*const be6140_c11fbe0)(void *pool, int block, unsigned short new_size, const char *file, unsigned int line) = (void *)stack_memory_pool_realloc;
static void * (*const be6140_c8e0b0)(void *destination, void *source, size_t size) = (void *)csmemcpy;
static wchar_t * (*const be6140_cf5290)(void *widget, unsigned short function_index) = (void *)ui_widget_text_search_and_replace_function_invoke;
static wchar_t * (*const be6140_c19f450)(const char *ascii, wchar_t *unicode, size_t length) = (void *)ascii_to_wide;
static int (*const be6140_ce5180)(wchar_t *text, wchar_t *replacement, void **pool_block) = (void *)FUN_000e5180;
static void (*const be6140_c8f390)(unsigned __int16 a1, const char *a2, ...) = (void *)error;
static float (*const be6140_ce4960)(void *widget) = (void *)widget_instance_get_opacity_product;
static void (*const be6140_ce5530)(float *out) = (void *)get_ui_argb_white;
static void (*const be6140_c19b8b0)(int tag_index, int style, int justify, int flags, const void *color) = (void *)draw_string_set_font;
static char (*const be6140_ce4ce0)(wchar_t *text) = (void *)ui_widget_match_localized_substring;
static void (*const be6140_ce5de0)(int16_t *rect, int param_2, int param_3, int param_4, wchar_t *text, int local_player_index) = (void *)draw_string_and_hack_in_icons;
static void (*const be6140_c184060)(void *screen_pos, short *bounds, const void *color, int flags, unsigned short *text) = (void *)rasterizer_draw_string;

__attribute__((naked, noinline))
void FUN_000e6140(void *widget /*  */, void *draw_state /*  */)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x7c, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0xf8(%%esi), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "pushl %%edi\n\t"
      "movl %%ecx, %%ebx\n\t"
      "je .LFUN_000e6140_3\n\t"
      "movw 0x40(%%ebx), %%cx\n\t"
      "cmpw $-1, %%cx\n\t"
      "jne .LFUN_000e6140_1\n\t"
      "movw 0x12e(%%esi), %%cx\n\t"
      ".LFUN_000e6140_1:\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "call *%[c19d420]\n\t"
      "pushl %%eax\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "call *%[c19d8c0]\n\t"
      "movl 0x3c(%%ebx), %%ecx\n\t"
      "movl 0x31e04c, %%edx\n\t"
      "pushl $0x1145\n\t"
      "leal (%%eax,%%eax,1), %%edi\n\t"
      "pushl $0x283280\n\t"
      "leal 0x2(%%edi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c11fbe0]\n\t"
      "addl $0x20, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%eax, 0x3c(%%ebx)\n\t"
      "je .LFUN_000e6140_2\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "call *%[c8e0b0]\n\t"
      "movl 0x3c(%%ebx), %%edx\n\t"
      "addl $0xc, %%esp\n\t"
      "movw $0, (%%edi,%%edx,1)\n\t"
      "jmp .LFUN_000e6140_3\n\t"
      ".LFUN_000e6140_2:\n\t"
      "movl $0x283a54, 0x3c(%%ebx)\n\t"
      ".LFUN_000e6140_3:\n\t"
      "leal 0x3c(%%ebx), %%eax\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "movl (%%eax), %%eax\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "je .LFUN_000e6140_17\n\t"
      "cmpw %%cx, (%%eax)\n\t"
      "je .LFUN_000e6140_17\n\t"
      "cmpl %%ecx, 0x60(%%esi)\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "jle .LFUN_000e6140_6\n\t"
      "movl %%ecx, -0x4(%%ebp)\n\t"
      "leal (%%ebx), %%ebx\n\t"
      ".LFUN_000e6140_4:\n\t"
      "movl 0x64(%%esi), %%edi\n\t"
      "addl -0x4(%%ebp), %%edi\n\t"
      "je .LFUN_000e6140_5\n\t"
      "cmpb $0, (%%edi)\n\t"
      "je .LFUN_000e6140_5\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x20(%%edi), %%ax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "call *%[cf5290]\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl $0x40\n\t"
      "leal -0x7c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "call *%[c19f450]\n\t"
      "addl $0xc, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[ce5180]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_000e6140_5:\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "movl 0x60(%%esi), %%ecx\n\t"
      "incl %%eax\n\t"
      "addl $0x22, %%edx\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      "jl .LFUN_000e6140_4\n\t"
      ".LFUN_000e6140_6:\n\t"
      "movl 0x108(%%esi), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "jne .LFUN_000e6140_7\n\t"
      "pushl $0x283a10\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000e6140_7:\n\t"
      "movw 0x11c(%%esi), %%di\n\t"
      "testw %%di, %%di\n\t"
      "jl .LFUN_000e6140_16\n\t"
      "cmpw $3, %%di\n\t"
      "jge .LFUN_000e6140_16\n\t"
      "movb 0x10(%%ebx), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000e6140_17\n\t"
      "movl %%ebx, %%eax\n\t"
      "call *%[ce4960]\n\t"
      "movl 0x28(%%esi), %%ecx\n\t"
      "movl 0x24(%%esi), %%eax\n\t"
      "movl %%ecx, -0x10(%%ebp)\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "je .LFUN_000e6140_8\n\t"
      "movl (%%ecx), %%eax\n\t"
      "movl 0x4(%%ecx), %%ecx\n\t"
      "jmp .LFUN_000e6140_9\n\t"
      ".LFUN_000e6140_8:\n\t"
      "movl 0x24(%%esi), %%eax\n\t"
      "movl 0x28(%%esi), %%ecx\n\t"
      ".LFUN_000e6140_9:\n\t"
      "movw 0xe(%%ebp), %%dx\n\t"
      "addw %%dx, -0x10(%%ebp)\n\t"
      "movl %%eax, -0x1c(%%ebp)\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "movl %%ecx, -0x18(%%ebp)\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "addw %%cx, -0xe(%%ebp)\n\t"
      "shrl $0x10, %%eax\n\t"
      "addw %%cx, %%ax\n\t"
      "addw 0x130(%%esi), %%ax\n\t"
      "movw -0x14(%%ebp), %%cx\n\t"
      "addw %%dx, %%cx\n\t"
      "addw 0x132(%%esi), %%cx\n\t"
      "movw %%ax, -0x12(%%ebp)\n\t"
      "movb 0x10(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "movw %%cx, -0x14(%%ebp)\n\t"
      "je .LFUN_000e6140_10\n\t"
      "leal -0x3c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[ce5530]\n\t"
      "flds 0x10c(%%esi)\n\t"
      "movl (%%eax), %%ecx\n\t"
      "movl %%ecx, -0x2c(%%ebp)\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl %%edx, -0x28(%%ebp)\n\t"
      "movl 0x8(%%eax), %%ecx\n\t"
      "movl %%ecx, -0x24(%%ebp)\n\t"
      "movl 0xc(%%eax), %%edx\n\t"
      "addl $4, %%esp\n\t"
      "movl %%edx, -0x20(%%ebp)\n\t"
      "jmp .LFUN_000e6140_12\n\t"
      ".LFUN_000e6140_10:\n\t"
      "flds 0x2533c8\n\t"
      "leal 0x10c(%%esi), %%ebx\n\t"
      "movl %%ebx, %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl %%edx, -0x28(%%ebp)\n\t"
      "fcomps -0x28(%%ebp)\n\t"
      "movl %%ecx, -0x2c(%%ebp)\n\t"
      "movl 0x8(%%eax), %%ecx\n\t"
      "movl 0xc(%%eax), %%edx\n\t"
      "fnstsw %%ax\n\t"
      "movl %%ecx, -0x24(%%ebp)\n\t"
      "movl %%edx, -0x20(%%ebp)\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .LFUN_000e6140_11\n\t"
      "flds 0x2533c8\n\t"
      "fcomps -0x24(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .LFUN_000e6140_11\n\t"
      "flds 0x2533c8\n\t"
      "fcomps -0x20(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .LFUN_000e6140_11\n\t"
      "leal -0x3c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[ce5530]\n\t"
      "flds (%%ebx)\n\t"
      "movl (%%eax), %%ecx\n\t"
      "movl %%ecx, -0x2c(%%ebp)\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl %%edx, -0x28(%%ebp)\n\t"
      "movl 0x8(%%eax), %%ecx\n\t"
      "movl %%ecx, -0x24(%%ebp)\n\t"
      "movl 0xc(%%eax), %%edx\n\t"
      "addl $4, %%esp\n\t"
      "movl %%edx, -0x20(%%ebp)\n\t"
      "jmp .LFUN_000e6140_12\n\t"
      ".LFUN_000e6140_11:\n\t"
      "flds -0x2c(%%ebp)\n\t"
      ".LFUN_000e6140_12:\n\t"
      "movb 0x11e(%%esi), %%al\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "testb $4, %%al\n\t"
      "fstps -0x2c(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "je .LFUN_000e6140_14\n\t"
      "movl 0x46cc40, %%eax\n\t"
      "fildl 0x46cc40\n\t"
      "testl %%eax, %%eax\n\t"
      "jge .LFUN_000e6140_13\n\t"
      "fadds 0x25fb8c\n\t"
      ".LFUN_000e6140_13:\n\t"
      "fmuls 0x28327c\n\t"
      "fmuls 0x254644\n\t"
      "fcos\n\t"
      "fadds 0x2533ec\n\t"
      "fmuls 0x253524\n\t"
      "fmuls -0x2c(%%ebp)\n\t"
      "fstps -0x2c(%%ebp)\n\t"
      ".LFUN_000e6140_14:\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "leal -0x2c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0\n\t"
      "pushl %%edi\n\t"
      "pushl $-1\n\t"
      "pushl %%edx\n\t"
      "call *%[c19b8b0]\n\t"
      "movl -0xc(%%ebp), %%esi\n\t"
      "movl (%%esi), %%eax\n\t"
      "addl $0x14, %%esp\n\t"
      "call *%[ce4ce0]\n\t"
      "testb %%al, %%al\n\t"
      "movl (%%esi), %%eax\n\t"
      "leal -0x14(%%ebp), %%edx\n\t"
      "leal -0x1c(%%ebp), %%ecx\n\t"
      "je .LFUN_000e6140_15\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[ce5de0]\n\t"
      "addl $0x18, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000e6140_15:\n\t"
      "pushl %%eax\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c184060]\n\t"
      "addl $0x14, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000e6140_16:\n\t"
      "pushl $0x2839c8\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_000e6140_17:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c19d420] "m"(be6140_c19d420), [c19d8c0] "m"(be6140_c19d8c0), [c11fbe0] "m"(be6140_c11fbe0), [c8e0b0] "m"(be6140_c8e0b0), [cf5290] "m"(be6140_cf5290), [c19f450] "m"(be6140_c19f450), [ce5180] "m"(be6140_ce5180), [c8f390] "m"(be6140_c8f390), [ce4960] "m"(be6140_ce4960), [ce5530] "m"(be6140_ce5530), [c19b8b0] "m"(be6140_c19b8b0), [ce4ce0] "m"(be6140_ce4ce0), [ce5de0] "m"(be6140_ce5de0), [c184060] "m"(be6140_c184060)
      : "memory");
}
#else
#error "FUN_000e6140: clang naked draft required"
#endif


/* FUN_000e6450 (0xe6450) — XBE naked draft (batch 107). */
#if defined(__clang__)
static void * (*const be6450_c77040)(int tag_index, short sequence_index, short frame_index) = (void *)FUN_00077040;
static void *(*const be6450_memset)(void *, int, unsigned int) = (void *)csmemset;
static void (*const be6450_ce3e80)(int bitmap, int16_t *src_rect, int16_t *dst_rect, int16_t *clip_rect, int flags, int param_6, int param_7) = (void *)draw_bitmap_in_rect;
static int (*const be6450_c19d420)(int param_1, int param_2) = (void *)FUN_0019d420;
static int (*const be6450_c19d8c0)(const unsigned short *s) = (void *)ustrlen;
static void * (*const be6450_c11fa40)(void *pool, int size, const char *file, unsigned int line) = (void *)stack_memory_pool_allocate;
static void * (*const be6450_c8e0b0)(void *destination, void *source, size_t size) = (void *)csmemcpy;
static wchar_t * (*const be6450_cf5290)(void *widget, unsigned short function_index) = (void *)ui_widget_text_search_and_replace_function_invoke;
static wchar_t * (*const be6450_c19f450)(const char *ascii, wchar_t *unicode, size_t length) = (void *)ascii_to_wide;
static int (*const be6450_ce5180)(wchar_t *text, wchar_t *replacement, void **pool_block) = (void *)FUN_000e5180;
static float (*const be6450_ce4960)(void *widget) = (void *)widget_instance_get_opacity_product;
static void (*const be6450_ce54e0)(float *out) = (void *)get_ui_rgb_white;
static void (*const be6450_c19b8b0)(int tag_index, int style, int justify, int flags, const void *color) = (void *)draw_string_set_font;
static void (*const be6450_c184060)(void *screen_pos, short *bounds, const void *color, int flags, unsigned short *text) = (void *)rasterizer_draw_string;
static void (*const be6450_c8f390)(unsigned __int16 a1, const char *a2, ...) = (void *)error;
static void (*const be6450_c11f620)(void *pool, void *block) = (void *)stack_memory_pool_deallocate;

__attribute__((naked, noinline))
void FUN_000e6450(void *draw_state, void *widget /*  */, int param_3, int param_4)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x108, %%esp\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "movl 0x30(%%ecx), %%eax\n\t"
      "flds 0x24(%%ecx)\n\t"
      "pushl %%edi\n\t"
      "fsts -0xc(%%ebp)\n\t"
      "xorl %%edi, %%edi\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%edi, -0x10(%%ebp)\n\t"
      "je .LFUN_000e6450_2\n\t"
      "nop\n\t"
      ".LFUN_000e6450_1:\n\t"
      "fmuls 0x24(%%eax)\n\t"
      "movl 0x30(%%eax), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_000e6450_1\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "jmp .LFUN_000e6450_3\n\t"
      ".LFUN_000e6450_2:\n\t"
      "fstp %%st(0)\n\t"
      ".LFUN_000e6450_3:\n\t"
      "movb 0x10(%%ecx), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000e6450_26\n\t"
      "movw 0x3e(%%ecx), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "je .LFUN_000e6450_6\n\t"
      "xorl %%edx, %%edx\n\t"
      "testw %%ax, %%ax\n\t"
      "setge %%dl\n\t"
      "leal -0x1(%%edx,%%edx,1), %%edx\n\t"
      "cmpl $-1, %%edx\n\t"
      "je .LFUN_000e6450_4\n\t"
      "cmpl $1, %%edx\n\t"
      "jne .LFUN_000e6450_6\n\t"
      "decl %%eax\n\t"
      "movl %%edx, -0x10(%%ebp)\n\t"
      "jmp .LFUN_000e6450_5\n\t"
      ".LFUN_000e6450_4:\n\t"
      "incl %%eax\n\t"
      "movl $1, %%edi\n\t"
      ".LFUN_000e6450_5:\n\t"
      "movw %%ax, 0x3e(%%ecx)\n\t"
      ".LFUN_000e6450_6:\n\t"
      "movl 0x160(%%esi), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "call *%[c77040]\n\t"
      "movl 0x10(%%ebp), %%ebx\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "je .LFUN_000e6450_7\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fmuls 0x2602c8\n\t"
      "fstps -0x30(%%ebp)\n\t"
      "flds -0x30(%%ebp)\n\t"
      "fistps -0x18(%%ebp)\n\t"
      "pushl $0x8c\n\t"
      "leal -0xc8(%%ebp), %%ecx\n\t"
      "pushl $0\n\t"
      "pushl %%ecx\n\t"
      "call *%[memset]\n\t"
      "movl 0x174(%%esi), %%edx\n\t"
      "movl 0x178(%%esi), %%eax\n\t"
      "movw 0x12(%%ebp), %%di\n\t"
      "movl %%edx, -0x8(%%ebp)\n\t"
      "movl -0x18(%%ebp), %%edx\n\t"
      "addw %%bx, -0x6(%%ebp)\n\t"
      "addw %%di, -0x8(%%ebp)\n\t"
      "pushl $0\n\t"
      "shll $0x18, %%edx\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "addw %%bx, -0x2(%%ebp)\n\t"
      "addw %%di, -0x4(%%ebp)\n\t"
      "leal -0xc8(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "orl $0xffffff, %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "leal -0x8(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x8(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[ce3e80]\n\t"
      "addl $0x28, %%esp\n\t"
      "jmp .LFUN_000e6450_8\n\t"
      ".LFUN_000e6450_7:\n\t"
      "movw 0x12(%%ebp), %%di\n\t"
      ".LFUN_000e6450_8:\n\t"
      "movl -0x10(%%ebp), %%ecx\n\t"
      "movl 0x170(%%esi), %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0\n\t"
      "pushl %%edx\n\t"
      "call *%[c77040]\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "je .LFUN_000e6450_9\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fmuls 0x2602c8\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fistps -0x30(%%ebp)\n\t"
      "pushl $0x8c\n\t"
      "leal -0xc8(%%ebp), %%eax\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "call *%[memset]\n\t"
      "movl 0x17c(%%esi), %%ecx\n\t"
      "movl 0x180(%%esi), %%edx\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "movl -0x30(%%ebp), %%ecx\n\t"
      "addw %%bx, -0x6(%%ebp)\n\t"
      "addw %%di, -0x8(%%ebp)\n\t"
      "pushl $0\n\t"
      "shll $0x18, %%ecx\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "addw %%bx, -0x2(%%ebp)\n\t"
      "addw %%di, -0x4(%%ebp)\n\t"
      "leal -0xc8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "orl $0xffffff, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "movl -0x14(%%ebp), %%edx\n\t"
      "leal -0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x8(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[ce3e80]\n\t"
      "addl $0x28, %%esp\n\t"
      ".LFUN_000e6450_9:\n\t"
      "movl 0x3e0(%%esi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_000e6450_25\n\t"
      "movl 0xf8(%%esi), %%ecx\n\t"
      "cmpl $-1, %%ecx\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "je .LFUN_000e6450_12\n\t"
      "movswl 0x3c(%%eax), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c19d420]\n\t"
      "pushl %%eax\n\t"
      "movl %%eax, -0x18(%%ebp)\n\t"
      "call *%[c19d8c0]\n\t"
      "movl 0x31e04c, %%ecx\n\t"
      "addl %%eax, %%eax\n\t"
      "pushl $0x1202\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "pushl $0x283280\n\t"
      "addl $2, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c11fa40]\n\t"
      "addl $0x1c, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "je .LFUN_000e6450_24\n\t"
      "movl -0x10(%%ebp), %%edx\n\t"
      "movl -0x18(%%ebp), %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "call *%[c8e0b0]\n\t"
      "movl -0x10(%%ebp), %%edx\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "movw $0, (%%edx,%%eax,1)\n\t"
      "movl 0x60(%%esi), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "movl $0, -0x10(%%ebp)\n\t"
      "jle .LFUN_000e6450_13\n\t"
      "movl $0, -0x14(%%ebp)\n\t"
      "jmp .LFUN_000e6450_10\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".LFUN_000e6450_10:\n\t"
      "movl 0x64(%%esi), %%edi\n\t"
      "addl -0x14(%%ebp), %%edi\n\t"
      "je .LFUN_000e6450_11\n\t"
      "cmpb $0, (%%edi)\n\t"
      "je .LFUN_000e6450_11\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x20(%%edi), %%cx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[cf5290]\n\t"
      "addl $8, %%esp\n\t"
      "leal -0xc(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl $0x40\n\t"
      "leal -0x108(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "call *%[c19f450]\n\t"
      "addl $0xc, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[ce5180]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_000e6450_11:\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "movl -0x14(%%ebp), %%edx\n\t"
      "movl 0x60(%%esi), %%ecx\n\t"
      "incl %%eax\n\t"
      "addl $0x22, %%edx\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "movl %%edx, -0x14(%%ebp)\n\t"
      "jl .LFUN_000e6450_10\n\t"
      "movw 0x12(%%ebp), %%di\n\t"
      "jmp .LFUN_000e6450_13\n\t"
      ".LFUN_000e6450_12:\n\t"
      "movl 0x4c(%%eax), %%ecx\n\t"
      "movl %%ecx, -0xc(%%ebp)\n\t"
      ".LFUN_000e6450_13:\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_000e6450_24\n\t"
      "cmpl $-1, 0x108(%%esi)\n\t"
      "jne .LFUN_000e6450_14\n\t"
      "pushl $0x283ac8\n\t"
      "jmp .LFUN_000e6450_23\n\t"
      ".LFUN_000e6450_14:\n\t"
      "movw 0x11c(%%esi), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "jl .LFUN_000e6450_22\n\t"
      "cmpw $3, %%ax\n\t"
      "jge .LFUN_000e6450_22\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "call *%[ce4960]\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .LFUN_000e6450_15\n\t"
      "movl (%%ecx), %%eax\n\t"
      "movl 0x4(%%ecx), %%ecx\n\t"
      "jmp .LFUN_000e6450_16\n\t"
      ".LFUN_000e6450_15:\n\t"
      "movl 0x24(%%esi), %%eax\n\t"
      "movl 0x28(%%esi), %%ecx\n\t"
      ".LFUN_000e6450_16:\n\t"
      "movl 0x24(%%esi), %%edx\n\t"
      "movl %%eax, -0x1c(%%ebp)\n\t"
      "movl 0x28(%%esi), %%eax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "movb 0x14(%%ebp), %%al\n\t"
      "addw %%bx, -0x2(%%ebp)\n\t"
      "addw %%di, -0x4(%%ebp)\n\t"
      "movl %%edx, -0x8(%%ebp)\n\t"
      "addw %%bx, -0x6(%%ebp)\n\t"
      "addw %%di, -0x8(%%ebp)\n\t"
      "testb %%al, %%al\n\t"
      "movl %%ecx, -0x18(%%ebp)\n\t"
      "je .LFUN_000e6450_17\n\t"
      "flds 0x10c(%%esi)\n\t"
      "leal -0x3c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "fsts -0x2c(%%ebp)\n\t"
      "call *%[ce54e0]\n\t"
      "movl (%%eax), %%edx\n\t"
      "movl %%edx, -0x28(%%ebp)\n\t"
      "movl 0x4(%%eax), %%ecx\n\t"
      "movl %%ecx, -0x24(%%ebp)\n\t"
      "movl 0x8(%%eax), %%edx\n\t"
      "addl $4, %%esp\n\t"
      "movl %%edx, -0x20(%%ebp)\n\t"
      "jmp .LFUN_000e6450_19\n\t"
      ".LFUN_000e6450_17:\n\t"
      "flds 0x2533c8\n\t"
      "leal 0x10c(%%esi), %%ecx\n\t"
      "movl %%ecx, %%eax\n\t"
      "movl (%%eax), %%edx\n\t"
      "movl %%edx, -0x2c(%%ebp)\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl %%edx, -0x28(%%ebp)\n\t"
      "fcomps -0x28(%%ebp)\n\t"
      "movl 0x8(%%eax), %%edx\n\t"
      "movl 0xc(%%eax), %%eax\n\t"
      "movl %%eax, -0x20(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "movl %%edx, -0x24(%%ebp)\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .LFUN_000e6450_18\n\t"
      "flds 0x2533c8\n\t"
      "fcomps -0x24(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .LFUN_000e6450_18\n\t"
      "flds 0x2533c8\n\t"
      "fcomps -0x20(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .LFUN_000e6450_18\n\t"
      "flds (%%ecx)\n\t"
      "jmp .LFUN_000e6450_19\n\t"
      ".LFUN_000e6450_18:\n\t"
      "flds -0x2c(%%ebp)\n\t"
      ".LFUN_000e6450_19:\n\t"
      "movb 0x11e(%%esi), %%al\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "testb $4, %%al\n\t"
      "fstps -0x2c(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "je .LFUN_000e6450_21\n\t"
      "movl 0x46cc40, %%ecx\n\t"
      "fildl 0x46cc40\n\t"
      "testl %%ecx, %%ecx\n\t"
      "jge .LFUN_000e6450_20\n\t"
      "fadds 0x25fb8c\n\t"
      ".LFUN_000e6450_20:\n\t"
      "fmuls 0x28327c\n\t"
      "fmuls 0x254644\n\t"
      "fsin\n\t"
      "fadds 0x2533c8\n\t"
      "fmuls 0x253398\n\t"
      "fmuls -0x2c(%%ebp)\n\t"
      "fstps -0x2c(%%ebp)\n\t"
      ".LFUN_000e6450_21:\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x11c(%%esi), %%ax\n\t"
      "leal -0x2c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "movl 0x108(%%esi), %%eax\n\t"
      "pushl $-1\n\t"
      "pushl %%eax\n\t"
      "call *%[c19b8b0]\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "leal -0x1c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x8(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c184060]\n\t"
      "addl $0x28, %%esp\n\t"
      "jmp .LFUN_000e6450_24\n\t"
      ".LFUN_000e6450_22:\n\t"
      "pushl $0x283a78\n\t"
      ".LFUN_000e6450_23:\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_000e6450_24:\n\t"
      "cmpl $-1, 0xf8(%%esi)\n\t"
      "je .LFUN_000e6450_25\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "movl 0x31e04c, %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c11f620]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_000e6450_25:\n\t"
      "popl %%ebx\n\t"
      ".LFUN_000e6450_26:\n\t"
      "popl %%edi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c77040] "m"(be6450_c77040), [memset] "m"(be6450_memset), [ce3e80] "m"(be6450_ce3e80), [c19d420] "m"(be6450_c19d420), [c19d8c0] "m"(be6450_c19d8c0), [c11fa40] "m"(be6450_c11fa40), [c8e0b0] "m"(be6450_c8e0b0), [cf5290] "m"(be6450_cf5290), [c19f450] "m"(be6450_c19f450), [ce5180] "m"(be6450_ce5180), [ce4960] "m"(be6450_ce4960), [ce54e0] "m"(be6450_ce54e0), [c19b8b0] "m"(be6450_c19b8b0), [c184060] "m"(be6450_c184060), [c8f390] "m"(be6450_c8f390), [c11f620] "m"(be6450_c11f620)
      : "memory");
}
#else
#error "FUN_000e6450: clang naked draft required"
#endif


/* FUN_000e73c0 (0xe73c0) — XBE naked draft (batch 111). */
#if defined(__clang__)
static void *(*const be73c0_tag)(int, int) = (void *)tag_get;
static void (*const be73c0_cf0a30)(void *widget, unsigned short game_data_input_reference_function) = (void *)ui_widget_game_data_function_invoke;
static void * (*const be73c0_c77040)(int tag_index, short sequence_index, short frame_index) = (void *)FUN_00077040;
static void *(*const be73c0_elem)(void *, int, int) = (void *)tag_block_get_element;
static void (*const be73c0_ce3e80)(int bitmap, int16_t *src_rect, int16_t *dst_rect, int16_t *clip_rect, int flags, int param_6, int param_7) = (void *)draw_bitmap_in_rect;
static void (*const be73c0_ce76b0)(void *widget, void *tag, void *a, float d, int e, int f) = (void *)FUN_000e76b0;
static void (*const be73c0_ce6450)(void *draw_state, void *widget /* */, int param_3, int param_4) = (void *)FUN_000e6450;
static char (*const be73c0_ce4a40)(void *widget) = (void *)widget_instance_parent_allows_focus;
static void (*const be73c0_ce6140)(void *widget /* */, void *draw_state /* */) = (void *)FUN_000e6140;
static void (*const be73c0_ce73c0)(void *widget, int16_t *bounds, float opacity_scale, char param_4, char visible) = (void *)FUN_000e73c0;

__attribute__((naked, noinline))
void FUN_000e73c0(void *widget, int16_t *bounds, float opacity_scale, char param_4, char visible)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xa8, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "movl (%%edi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x44654c61\n\t"
      "call *%[tag]\n\t"
      "flds 0x24(%%edi)\n\t"
      "movl %%eax, %%esi\n\t"
      "fsts -0x4(%%ebp)\n\t"
      "movl 0x30(%%edi), %%eax\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "addl $8, %%esp\n\t"
      "cmpl %%ebx, %%eax\n\t"
      "je .LFUN_000e73c0_2\n\t"
      ".LFUN_000e73c0_1:\n\t"
      "fmuls 0x24(%%eax)\n\t"
      "movl 0x30(%%eax), %%eax\n\t"
      "cmpl %%ebx, %%eax\n\t"
      "jne .LFUN_000e73c0_1\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "jmp .LFUN_000e73c0_3\n\t"
      ".LFUN_000e73c0_2:\n\t"
      "fstp %%st(0)\n\t"
      ".LFUN_000e73c0_3:\n\t"
      "movb 0x18(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_000e73c0_4\n\t"
      "movl 0x2c(%%esi), %%eax\n\t"
      "testb $0x20, %%ah\n\t"
      "je .LFUN_000e73c0_4\n\t"
      "movb $1, 0x18(%%ebp)\n\t"
      ".LFUN_000e73c0_4:\n\t"
      "movw 0xa(%%edi), %%cx\n\t"
      "movw 0xc(%%edi), %%dx\n\t"
      "movl 0x48(%%esi), %%eax\n\t"
      "addw %%cx, 0x10(%%ebp)\n\t"
      "addw %%dx, 0x12(%%ebp)\n\t"
      "cmpl %%ebx, %%eax\n\t"
      "jle .LFUN_000e73c0_6\n\t"
      "movl %%ebx, 0x8(%%ebp)\n\t"
      "movl %%edi, %%edi\n\t"
      ".LFUN_000e73c0_5:\n\t"
      "movl 0x4c(%%esi), %%eax\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw (%%ecx,%%eax,1), %%dx\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "call *%[cf0a30]\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "movl 0x48(%%esi), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "incl %%ebx\n\t"
      "addl $0x24, %%ecx\n\t"
      "cmpl %%eax, %%ebx\n\t"
      "movl %%ecx, 0x8(%%ebp)\n\t"
      "jl .LFUN_000e73c0_5\n\t"
      ".LFUN_000e73c0_6:\n\t"
      "movb 0x10(%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000e73c0_20\n\t"
      "movl 0x44(%%esi), %%ecx\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x50(%%edi), %%ax\n\t"
      "pushl %%eax\n\t"
      "pushl $0\n\t"
      "pushl %%ecx\n\t"
      "call *%[c77040]\n\t"
      "movl 0xc(%%ebp), %%ebx\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%eax, -0x1c(%%ebp)\n\t"
      "je .LFUN_000e73c0_12\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "movl 0x24(%%esi), %%eax\n\t"
      "movl 0x28(%%esi), %%ecx\n\t"
      "movl %%edx, -0x18(%%ebp)\n\t"
      "movl 0x44(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x6269746d\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "movl %%ebx, 0x8(%%ebp)\n\t"
      "call *%[tag]\n\t"
      "pushl $0x40\n\t"
      "addl $0x54, %%eax\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movb 0x18(%%ebp), %%al\n\t"
      "addl $0x14, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000e73c0_7\n\t"
      "movl $0, 0x5aa460\n\t"
      "movl $0x3d4ccccd, 0x5aa464\n\t"
      "movl $0x3d4ccccd, 0x5aa468\n\t"
      "movl $0x3d4ccccd, 0x5aa46c\n\t"
      ".LFUN_000e73c0_7:\n\t"
      "movw 0x10(%%ebp), %%ax\n\t"
      "movw 0x12(%%ebp), %%cx\n\t"
      "addw %%ax, -0xa(%%ebp)\n\t"
      "addw %%ax, -0x6(%%ebp)\n\t"
      "addw %%cx, -0xc(%%ebp)\n\t"
      "addw %%cx, -0x8(%%ebp)\n\t"
      "testl %%ebx, %%ebx\n\t"
      "je .LFUN_000e73c0_8\n\t"
      "movl (%%ebx), %%edx\n\t"
      "movl %%edx, -0x14(%%ebp)\n\t"
      "movl 0x4(%%ebx), %%edx\n\t"
      "addw %%ax, -0x12(%%ebp)\n\t"
      "addw %%cx, -0x14(%%ebp)\n\t"
      "movl %%edx, -0x10(%%ebp)\n\t"
      "addw %%ax, -0xe(%%ebp)\n\t"
      "addw %%cx, -0x10(%%ebp)\n\t"
      "leal -0x14(%%ebp), %%edx\n\t"
      "movl %%edx, 0x8(%%ebp)\n\t"
      ".LFUN_000e73c0_8:\n\t"
      "testb $4, 0x2c(%%esi)\n\t"
      "je .LFUN_000e73c0_10\n\t"
      "movl 0x46cc40, %%eax\n\t"
      "fildl 0x46cc40\n\t"
      "testl %%eax, %%eax\n\t"
      "jge .LFUN_000e73c0_9\n\t"
      "fadds 0x25fb8c\n\t"
      ".LFUN_000e73c0_9:\n\t"
      "fmuls 0x28327c\n\t"
      "fmuls 0x254644\n\t"
      "fcos\n\t"
      "fadds 0x2533c8\n\t"
      "fmuls 0x253398\n\t"
      "fmuls -0x4(%%ebp)\n\t"
      "jmp .LFUN_000e73c0_11\n\t"
      ".LFUN_000e73c0_10:\n\t"
      "flds -0x18(%%ebp)\n\t"
      ".LFUN_000e73c0_11:\n\t"
      "fmuls 0x2602c8\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fistps -0x4(%%ebp)\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl $0\n\t"
      "shll $0x18, %%edx\n\t"
      "leal -0xa8(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "orl $0xffffff, %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "movl -0x1c(%%ebp), %%eax\n\t"
      "leal -0xc(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0xc(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[ce3e80]\n\t"
      "movb 0x18(%%ebp), %%al\n\t"
      "addl $0x1c, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000e73c0_12\n\t"
      "movl $0, 0x5aa460\n\t"
      "movl $0, 0x5aa464\n\t"
      "movl $0, 0x5aa468\n\t"
      "movl $0, 0x5aa46c\n\t"
      ".LFUN_000e73c0_12:\n\t"
      "movswl 0xe(%%edi), %%eax\n\t"
      "decl %%eax\n\t"
      "je .LFUN_000e73c0_17\n\t"
      "decl %%eax\n\t"
      "je .LFUN_000e73c0_16\n\t"
      "decl %%eax\n\t"
      "jne .LFUN_000e73c0_13\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[ce76b0]\n\t"
      "movb 0x150(%%esi), %%al\n\t"
      "notb %%al\n\t"
      "andb $1, %%al\n\t"
      "addl $0x14, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000e73c0_20\n\t"
      ".LFUN_000e73c0_13:\n\t"
      "movl 0x34(%%edi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_000e73c0_20\n\t"
      "movl %%edi, %%edi\n\t"
      ".LFUN_000e73c0_14:\n\t"
      "cmpl 0x38(%%edi), %%esi\n\t"
      "sete %%al\n\t"
      "testb %%al, %%al\n\t"
      "movb %%al, 0x14(%%ebp)\n\t"
      "je .LFUN_000e73c0_18\n\t"
      "movw 0xe(%%edi), %%ax\n\t"
      "cmpw $2, %%ax\n\t"
      "je .LFUN_000e73c0_15\n\t"
      "cmpw $3, %%ax\n\t"
      "jne .LFUN_000e73c0_18\n\t"
      ".LFUN_000e73c0_15:\n\t"
      "movb $1, 0x18(%%ebp)\n\t"
      "jmp .LFUN_000e73c0_19\n\t"
      ".LFUN_000e73c0_16:\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "call *%[ce6450]\n\t"
      "movb 0x150(%%esi), %%al\n\t"
      "addl $0x10, %%esp\n\t"
      "testb $2, %%al\n\t"
      "je .LFUN_000e73c0_13\n\t"
      "movl 0x3e0(%%esi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_000e73c0_13\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000e73c0_17:\n\t"
      "movl %%edi, %%eax\n\t"
      "call *%[ce4a40]\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "movl %%edi, %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%ebx\n\t"
      "movl %%esi, %%eax\n\t"
      "call *%[ce6140]\n\t"
      "addl $0xc, %%esp\n\t"
      "jmp .LFUN_000e73c0_13\n\t"
      ".LFUN_000e73c0_18:\n\t"
      "movb $0, 0x18(%%ebp)\n\t"
      ".LFUN_000e73c0_19:\n\t"
      "movl 0x18(%%ebp), %%eax\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "call *%[ce73c0]\n\t"
      "movl 0x2c(%%esi), %%esi\n\t"
      "addl $0x14, %%esp\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LFUN_000e73c0_14\n\t"
      ".LFUN_000e73c0_20:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [tag] "m"(be73c0_tag), [cf0a30] "m"(be73c0_cf0a30), [c77040] "m"(be73c0_c77040), [elem] "m"(be73c0_elem), [ce3e80] "m"(be73c0_ce3e80), [ce76b0] "m"(be73c0_ce76b0), [ce6450] "m"(be73c0_ce6450), [ce4a40] "m"(be73c0_ce4a40), [ce6140] "m"(be73c0_ce6140), [ce73c0] "m"(be73c0_ce73c0)
      : "memory");
}
#else
#error "FUN_000e73c0: clang naked draft required"
#endif


/* render_ui_widgets_postgame (0xe7760) — XBE naked draft (batch 124). */
#if defined(__clang__)
static char (*const be7760_cf5640)(void) = (void *)FUN_000f5640;
static __int16 (*const be7760_cba4b0)(void) = (void *)local_player_count;
static void (*const be7760_ce73c0)(void *widget, int16_t *bounds, float opacity_scale, char param_4, char visible) = (void *)FUN_000e73c0;

__attribute__((naked, noinline))
void render_ui_widgets_postgame(int16_t local_player_index, int16_t *bounds)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x48, %%esp\n\t"
      "movl $0xf0, %%eax\n\t"
      "movl $0x140, %%ecx\n\t"
      "pushl %%ebx\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "movw %%bx, -0x48(%%ebp)\n\t"
      "movw %%bx, -0x46(%%ebp)\n\t"
      "movw %%bx, -0x44(%%ebp)\n\t"
      "movw %%bx, -0x42(%%ebp)\n\t"
      "movw %%bx, -0x40(%%ebp)\n\t"
      "movw %%bx, -0x3e(%%ebp)\n\t"
      "movw %%bx, -0x3c(%%ebp)\n\t"
      "movw %%bx, -0x3a(%%ebp)\n\t"
      "movw %%bx, -0x38(%%ebp)\n\t"
      "movw %%bx, -0x36(%%ebp)\n\t"
      "movw %%bx, -0x34(%%ebp)\n\t"
      "movw %%ax, -0x32(%%ebp)\n\t"
      "movw %%bx, -0x30(%%ebp)\n\t"
      "movw %%bx, -0x2e(%%ebp)\n\t"
      "movw %%bx, -0x2c(%%ebp)\n\t"
      "movw %%bx, -0x2a(%%ebp)\n\t"
      "movw %%bx, -0x28(%%ebp)\n\t"
      "movw %%bx, -0x26(%%ebp)\n\t"
      "movw %%bx, -0x24(%%ebp)\n\t"
      "movw %%ax, -0x22(%%ebp)\n\t"
      "movw %%cx, -0x20(%%ebp)\n\t"
      "movw %%ax, -0x1e(%%ebp)\n\t"
      "movw %%bx, -0x1c(%%ebp)\n\t"
      "movw %%bx, -0x1a(%%ebp)\n\t"
      "movw %%bx, -0x18(%%ebp)\n\t"
      "movw %%bx, -0x16(%%ebp)\n\t"
      "movw %%cx, -0x14(%%ebp)\n\t"
      "movw %%bx, -0x12(%%ebp)\n\t"
      "movw %%bx, -0x10(%%ebp)\n\t"
      "movw %%ax, -0xe(%%ebp)\n\t"
      "movw %%cx, -0xc(%%ebp)\n\t"
      "movw %%ax, -0xa(%%ebp)\n\t"
      "call *%[cf5640]\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lrender_ui_widgets_postgame_9\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "cmpw %%bx, %%ax\n\t"
      "jge .Lrender_ui_widgets_postgame_1\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movl %%ecx, 0x8(%%ebp)\n\t"
      "jmp .Lrender_ui_widgets_postgame_3\n\t"
      ".Lrender_ui_widgets_postgame_1:\n\t"
      "cmpw $3, %%ax\n\t"
      "movl $3, 0x8(%%ebp)\n\t"
      "jg .Lrender_ui_widgets_postgame_2\n\t"
      "movl %%eax, 0x8(%%ebp)\n\t"
      ".Lrender_ui_widgets_postgame_2:\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      ".Lrender_ui_widgets_postgame_3:\n\t"
      "pushl %%esi\n\t"
      "movl 0xc(%%ebp), %%esi\n\t"
      "pushl %%edi\n\t"
      "xorl %%edi, %%edi\n\t"
      "leal (%%esp), %%esp\n\t"
      ".Lrender_ui_widgets_postgame_4:\n\t"
      "movl 0x46cc20(,%%edi,4), %%eax\n\t"
      "cmpl %%ebx, %%eax\n\t"
      "je .Lrender_ui_widgets_postgame_8\n\t"
      "cmpb $1, 0x11(%%eax)\n\t"
      "je .Lrender_ui_widgets_postgame_7\n\t"
      "cmpb $1, 0x15(%%eax)\n\t"
      "movw 0x8(%%eax), %%ax\n\t"
      "jne .Lrender_ui_widgets_postgame_5\n\t"
      "cmpw %%cx, %%ax\n\t"
      "je .Lrender_ui_widgets_postgame_7\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .Lrender_ui_widgets_postgame_7\n\t"
      "cmpw $-1, %%cx\n\t"
      "je .Lrender_ui_widgets_postgame_7\n\t"
      "cmpb %%bl, 0x46cc88\n\t"
      "je .Lrender_ui_widgets_postgame_8\n\t"
      "jmp .Lrender_ui_widgets_postgame_7\n\t"
      ".Lrender_ui_widgets_postgame_5:\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "jne .Lrender_ui_widgets_postgame_6\n\t"
      "cmpl %%ebx, %%edi\n\t"
      "je .Lrender_ui_widgets_postgame_7\n\t"
      ".Lrender_ui_widgets_postgame_6:\n\t"
      "cmpw %%cx, %%ax\n\t"
      "jne .Lrender_ui_widgets_postgame_8\n\t"
      ".Lrender_ui_widgets_postgame_7:\n\t"
      "movw 0x6(%%esi), %%ax\n\t"
      "movw 0x4(%%esi), %%cx\n\t"
      "subw 0x2(%%esi), %%ax\n\t"
      "subw (%%esi), %%cx\n\t"
      "pushl %%ebx\n\t"
      "pushl $1\n\t"
      "movw %%bx, -0x6(%%ebp)\n\t"
      "movw %%bx, -0x8(%%ebp)\n\t"
      "movw %%ax, -0x2(%%ebp)\n\t"
      "movw %%cx, -0x4(%%ebp)\n\t"
      "call *%[cba4b0]\n\t"
      "movswl %%ax, %%edx\n\t"
      "movswl 0x8(%%ebp), %%eax\n\t"
      "leal (%%eax,%%edx,4), %%ecx\n\t"
      "movl -0x58(%%ebp,%%ecx,4), %%edx\n\t"
      "movl 0x46cc20(,%%edi,4), %%ecx\n\t"
      "pushl %%edx\n\t"
      "leal -0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[ce73c0]\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrender_ui_widgets_postgame_8:\n\t"
      "incl %%edi\n\t"
      "cmpl $4, %%edi\n\t"
      "jl .Lrender_ui_widgets_postgame_4\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      ".Lrender_ui_widgets_postgame_9:\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [cf5640] "m"(be7760_cf5640), [cba4b0] "m"(be7760_cba4b0), [ce73c0] "m"(be7760_ce73c0)
      : "memory");
}
#else
#error "render_ui_widgets_postgame: clang naked draft required"
#endif


/* FUN_000e98c0 (0xe98c0) — XBE naked draft (batch 120). */
#if defined(__clang__)
static void *(*const be98c0_memset)(void *, int, unsigned int) = (void *)csmemset;
static void (*const be98c0_ce0980)(void) = (void *)player_ui_get_active_player_profile;
static void (*const be98c0_c1c0f70)(void *profile, short *out_level, short *out_difficulty) = (void *)player_profile_save_last_level_played;
static void *(*const be98c0_tag)(int, int) = (void *)tag_get;
static void (*const be98c0_assert)(const char *, const char *, int, bool) = (void *)display_assert;
static void (*const be98c0_exitfn)(int) = (void *)system_exit;
static int16_t (*const be98c0_ce0a10)(int16_t) = (void *)player_ui_get_last_single_player_level_played;

__attribute__((naked, noinline))
char FUN_000e98c0(void *widget)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x68, %%esp\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl $0x50\n\t"
      "pushl $0\n\t"
      "pushl $0x46cce8\n\t"
      "call *%[memset]\n\t"
      "leal -0x68(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0\n\t"
      "call *%[ce0980]\n\t"
      "leal -0x8(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x4(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x68(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1c0f70]\n\t"
      "leal -0x38(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $1\n\t"
      "call *%[ce0980]\n\t"
      "leal -0x6(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x2(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x38(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1c0f70]\n\t"
      "movl -0x4(%%ebp), %%esi\n\t"
      "movw -0x2(%%ebp), %%di\n\t"
      "addl $0x34, %%esp\n\t"
      "xorl %%eax, %%eax\n\t"
      "leal (%%ebx), %%ebx\n\t"
      ".LFUN_000e98c0_1:\n\t"
      "movl 0x31e498(,%%eax,4), %%edx\n\t"
      "movl %%edx, 0x46cce8(,%%eax,8)\n\t"
      "movb -0x4c(%%ebp,%%eax,1), %%dl\n\t"
      "testb %%dl, %%dl\n\t"
      "jne .LFUN_000e98c0_2\n\t"
      "movswl %%si, %%ecx\n\t"
      "incl %%ecx\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "je .LFUN_000e98c0_2\n\t"
      "movb -0x1c(%%ebp,%%eax,1), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "jne .LFUN_000e98c0_2\n\t"
      "movswl %%di, %%ecx\n\t"
      "incl %%ecx\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "je .LFUN_000e98c0_2\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_000e98c0_3\n\t"
      ".LFUN_000e98c0_2:\n\t"
      "movsbl -0x1c(%%ebp,%%eax,1), %%ecx\n\t"
      "movsbl %%dl, %%edx\n\t"
      "orl %%edx, %%ecx\n\t"
      "movl %%ecx, %%edx\n\t"
      "shrl $1, %%edx\n\t"
      "andb $1, %%dl\n\t"
      "movb %%dl, 0x46cced(,%%eax,8)\n\t"
      "movl %%ecx, %%edx\n\t"
      "shrl $2, %%edx\n\t"
      "andb $1, %%dl\n\t"
      "shrl $3, %%ecx\n\t"
      "andb $1, %%cl\n\t"
      "movb $1, 0x46ccec(,%%eax,8)\n\t"
      "movb %%dl, 0x46ccee(,%%eax,8)\n\t"
      "movb %%cl, 0x46ccef(,%%eax,8)\n\t"
      ".LFUN_000e98c0_3:\n\t"
      "incl %%eax\n\t"
      "cmpl $0xa, %%eax\n\t"
      "jl .LFUN_000e98c0_1\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "movl (%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x44654c61\n\t"
      "call *%[tag]\n\t"
      "movl %%eax, %%edi\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $2, (%%edi)\n\t"
      "je .LFUN_000e98c0_4\n\t"
      "pushl $1\n\t"
      "pushl $0x2b1\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x285a18\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000e98c0_4:\n\t"
      "cmpl $3, 0x3e0(%%edi)\n\t"
      "je .LFUN_000e98c0_5\n\t"
      "pushl $1\n\t"
      "pushl $0x2b2\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x2859e4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000e98c0_5:\n\t"
      "pushl $0\n\t"
      "movl $0x46cce8, 0x40(%%esi)\n\t"
      "movw $0xa, 0x44(%%esi)\n\t"
      "call *%[ce0a10]\n\t"
      "addl $4, %%esp\n\t"
      "testw %%ax, %%ax\n\t"
      "jge .LFUN_000e98c0_6\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw %%ax, 0x3c(%%esi)\n\t"
      "popl %%edi\n\t"
      "movb $1, %%al\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000e98c0_6:\n\t"
      "pushl $0\n\t"
      "call *%[ce0a10]\n\t"
      "addl $4, %%esp\n\t"
      "cmpw $9, %%ax\n\t"
      "jle .LFUN_000e98c0_7\n\t"
      "movl $9, %%eax\n\t"
      "movw %%ax, 0x3c(%%esi)\n\t"
      "popl %%edi\n\t"
      "movb $1, %%al\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000e98c0_7:\n\t"
      "pushl $0\n\t"
      "call *%[ce0a10]\n\t"
      "movswl %%ax, %%eax\n\t"
      "addl $4, %%esp\n\t"
      "movw %%ax, 0x3c(%%esi)\n\t"
      "popl %%edi\n\t"
      "movb $1, %%al\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [memset] "m"(be98c0_memset), [ce0980] "m"(be98c0_ce0980), [c1c0f70] "m"(be98c0_c1c0f70), [tag] "m"(be98c0_tag), [assert] "m"(be98c0_assert), [exitfn] "m"(be98c0_exitfn), [ce0a10] "m"(be98c0_ce0a10)
      : "memory");
}
#else
#error "FUN_000e98c0: clang naked draft required"
#endif


/* FUN_000e9a90 (0xe9a90) — XBE naked draft (batch 124). */
#if defined(__clang__)
static void (*const be9a90_assert)(const char *, const char *, int, bool) = (void *)display_assert;
static void (*const be9a90_exitfn)(int) = (void *)system_exit;
static void (*const be9a90_c8f390)(unsigned __int16 a1, const char *a2, ...) = (void *)error;
static void (*const be9a90_ce5ab0)(int16_t sound_selector) = (void *)ui_play_audio_feedback_sound;
static void (*const be9a90_ce0980)(void) = (void *)player_ui_get_active_player_profile;
static void (*const be9a90_c1c0f70)(void *profile, short *out_level, short *out_difficulty) = (void *)player_profile_save_last_level_played;
static void (*const be9a90_ce0c30)(bool) = (void *)player_ui_remember_player1_profile;
static void (*const be9a90_cfffa0)(const char *name) = (void *)main_set_map_name;
static void (*const be9a90_c100000)(void) = (void *)main_defer_map_map_change;
static void (*const be9a90_ce9bbf)(void) = (void (*)(void))ui_widget_event_handler_set_difficulty;

__attribute__((naked, noinline))
char FUN_000e9a90(void *widget)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x34, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "movw 0x3c(%%edi), %%ax\n\t"
      "xorb %%bl, %%bl\n\t"
      "testw %%ax, %%ax\n\t"
      "jl .LFUN_000e9a90_1\n\t"
      "cmpw $0xa, %%ax\n\t"
      "jl .LFUN_000e9a90_2\n\t"
      ".LFUN_000e9a90_1:\n\t"
      "pushl $1\n\t"
      "pushl $0x2d4\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x285aa4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000e9a90_2:\n\t"
      "movswl 0x31fa94, %%eax\n\t"
      "decl %%eax\n\t"
      "je .LFUN_000e9a90_4\n\t"
      "decl %%eax\n\t"
      "je .LFUN_000e9a90_7\n\t"
      "pushl $0x285a78\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_000e9a90_3:\n\t"
      "pushl $0x285a54\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "pushl $4\n\t"
      "call *%[ce5ab0]\n\t"
      "addl $0xc, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000e9a90_4:\n\t"
      "leal -0x34(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0\n\t"
      "call *%[ce0980]\n\t"
      "leal -0x4(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal 0xa(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x34(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1c0f70]\n\t"
      "movw 0x3c(%%edi), %%ax\n\t"
      "movswl %%ax, %%ecx\n\t"
      "movb -0x18(%%ebp,%%ecx,1), %%dl\n\t"
      "addl $0x14, %%esp\n\t"
      "testb %%dl, %%dl\n\t"
      "jne .LFUN_000e9a90_5\n\t"
      "movswl 0xa(%%ebp), %%edx\n\t"
      "incl %%edx\n\t"
      "cmpl %%edx, %%ecx\n\t"
      "je .LFUN_000e9a90_5\n\t"
      "testw %%ax, %%ax\n\t"
      "jne .LFUN_000e9a90_6\n\t"
      ".LFUN_000e9a90_5:\n\t"
      "movb $1, %%bl\n\t"
      ".LFUN_000e9a90_6:\n\t"
      "pushl $0\n\t"
      "call *%[ce0c30]\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_000e9a90_7:\n\t"
      "xorl %%esi, %%esi\n\t"
      ".LFUN_000e9a90_8:\n\t"
      "leal -0x34(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[ce0980]\n\t"
      "leal -0x4(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal 0xa(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x34(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1c0f70]\n\t"
      "movw 0x3c(%%edi), %%ax\n\t"
      "movswl %%ax, %%ecx\n\t"
      "movb -0x18(%%ebp,%%ecx,1), %%dl\n\t"
      "addl $0x14, %%esp\n\t"
      "testb %%dl, %%dl\n\t"
      "jne .LFUN_000e9a90_10000\n\t"
      "movswl 0xa(%%ebp), %%edx\n\t"
      "incl %%edx\n\t"
      "cmpl %%edx, %%ecx\n\t"
      "je .LFUN_000e9a90_10000\n\t"
      "testw %%ax, %%ax\n\t"
      "je .LFUN_000e9a90_10000\n\t"
      "incl %%esi\n\t"
      "cmpw $1, %%si\n\t"
      "jle .LFUN_000e9a90_8\n\t"
      "cmpb $1, %%bl\n\t"
      "jne .LFUN_000e9a90_3\n\t"
      "movswl 0x3c(%%edi), %%eax\n\t"
      "movl 0x31e498(,%%eax,4), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[cfffa0]\n\t"
      "addl $4, %%esp\n\t"
      "call *%[c100000]\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000e9a90_10000:\n\t"
      "jmp *%[ce9bbf]\n\t"
      :
      : [assert] "m"(be9a90_assert), [exitfn] "m"(be9a90_exitfn), [c8f390] "m"(be9a90_c8f390), [ce5ab0] "m"(be9a90_ce5ab0), [ce0980] "m"(be9a90_ce0980), [c1c0f70] "m"(be9a90_c1c0f70), [ce0c30] "m"(be9a90_ce0c30), [cfffa0] "m"(be9a90_cfffa0), [c100000] "m"(be9a90_c100000), [ce9bbf] "m"(be9a90_ce9bbf)
      : "memory");
}
#else
#error "FUN_000e9a90: clang naked draft required"
#endif


/* FUN_000e9dd0 (0xe9dd0) — XBE naked draft (batch 114). */
#if defined(__clang__)
static void (*const be9dd0_c82bd0)(void) = (void *)FUN_00082bd0;
static void (*const be9dd0_c12d250)(void *join_token) = (void *)network_game_generate_join_game_token;
static void * (*const be9dd0_c12a240)(void) = (void *)network_game_client_get;
static char (*const be9dd0_c124aa0)(void *client, void *game, void *join_token, void *address) = (void *)network_game_client_initiate_join_game;
static void * (*const be9dd0_ce4310)(void *widget) = (void *)ui_widget_get_last_child;
static int (*const be9dd0_ce4330)(void *widget) = (void *)widget_instance_get_child_index_from_parent;
static void * (*const be9dd0_ce84e0)(const char *name, int tag_index, int is_child, int widget_stack, int parent_tag_index, int a6, int a7) = (void *)ui_widget_load_by_name_or_tag;
static void (*const be9dd0_c8f390)(unsigned __int16 a1, const char *a2, ...) = (void *)error;
static void (*const be9dd0_cfff70)(short param) = (void *)set_game_connection;
static void (*const be9dd0_c12a780)(void) = (void *)network_game_abort;
static void (*const be9dd0_ce5ab0)(int16_t sound_selector) = (void *)ui_play_audio_feedback_sound;

__attribute__((naked, noinline))
char FUN_000e9dd0(void *widget)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x40, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "movl 0x38(%%esi), %%eax\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "cmpl %%ebx, %%eax\n\t"
      "pushl %%edi\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "je .LFUN_000e9dd0_10\n\t"
      "movw 0x3c(%%esi), %%ax\n\t"
      "cmpw %%bx, %%ax\n\t"
      "jl .LFUN_000e9dd0_10\n\t"
      "movw 0x44(%%esi), %%dx\n\t"
      "movswl %%ax, %%eax\n\t"
      "movzwl %%dx, %%ecx\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jge .LFUN_000e9dd0_9\n\t"
      "movl 0x40(%%esi), %%ecx\n\t"
      "cmpl %%ebx, %%ecx\n\t"
      "je .LFUN_000e9dd0_9\n\t"
      "cmpw %%bx, %%dx\n\t"
      "jbe .LFUN_000e9dd0_8\n\t"
      "movl (%%ecx,%%eax,4), %%edi\n\t"
      "cmpb $1, 0xe0(%%edi)\n\t"
      "jne .LFUN_000e9dd0_7\n\t"
      "cmpw %%bx, 0xde(%%edi)\n\t"
      "jne .LFUN_000e9dd0_6\n\t"
      "xorl %%edx, %%edx\n\t"
      "movl %%edx, -0x18(%%ebp)\n\t"
      "leal -0x1c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl %%edx, -0x14(%%ebp)\n\t"
      "xorl %%eax, %%eax\n\t"
      "pushl $0x141e\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "movl %%edx, -0x10(%%ebp)\n\t"
      "pushl %%edi\n\t"
      "leal 0x8(%%edi), %%edx\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "pushl %%edx\n\t"
      "leal 0x18(%%edi), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl %%ebx, -0x1c(%%ebp)\n\t"
      "call *%[c82bd0]\n\t"
      "movl -0x1c(%%ebp), %%eax\n\t"
      "addl $0x14, %%esp\n\t"
      "cmpl %%ebx, %%eax\n\t"
      "je .LFUN_000e9dd0_5\n\t"
      "cmpw %%bx, -0xa(%%ebp)\n\t"
      "je .LFUN_000e9dd0_5\n\t"
      "leal -0x2e(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movw %%bx, -0x3e(%%ebp)\n\t"
      "call *%[c12d250]\n\t"
      "addl $4, %%esp\n\t"
      "leal -0x1c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x40(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "call *%[c12a240]\n\t"
      "pushl %%eax\n\t"
      "call *%[c124aa0]\n\t"
      "addl $0x10, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000e9dd0_4\n\t"
      "pushl %%esi\n\t"
      "call *%[ce4310]\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl 0x30(%%esi), %%eax\n\t"
      "addl $4, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_000e9dd0_1\n\t"
      "movl (%%eax), %%edi\n\t"
      "jmp .LFUN_000e9dd0_2\n\t"
      ".LFUN_000e9dd0_1:\n\t"
      "orl $0xffffffff, %%edi\n\t"
      ".LFUN_000e9dd0_2:\n\t"
      "pushl %%esi\n\t"
      "call *%[ce4330]\n\t"
      "movl (%%ebx), %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "pushl $-1\n\t"
      "pushl $0\n\t"
      "pushl $-1\n\t"
      "pushl $0x2828e0\n\t"
      "call *%[ce84e0]\n\t"
      "addl $0x20, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_000e9dd0_3\n\t"
      "pushl $0x283728\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "addl $8, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb $1, (%%edx)\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000e9dd0_3:\n\t"
      "pushl $1\n\t"
      "call *%[cfff70]\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "addl $4, %%esp\n\t"
      "popl %%edi\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "popl %%esi\n\t"
      "movb $1, (%%edx)\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000e9dd0_4:\n\t"
      "call *%[c12a780]\n\t"
      "pushl $0x285d20\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "addl $8, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000e9dd0_5:\n\t"
      "pushl $0x285ce8\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "addl $8, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000e9dd0_6:\n\t"
      "pushl $0x285c90\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "addl $8, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000e9dd0_7:\n\t"
      "pushl $0x285c70\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "pushl $4\n\t"
      "call *%[ce5ab0]\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "addl $0xc, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000e9dd0_8:\n\t"
      "pushl $0x285c08\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "addl $8, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000e9dd0_9:\n\t"
      "pushl $0x285b90\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_000e9dd0_10:\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c82bd0] "m"(be9dd0_c82bd0), [c12d250] "m"(be9dd0_c12d250), [c12a240] "m"(be9dd0_c12a240), [c124aa0] "m"(be9dd0_c124aa0), [ce4310] "m"(be9dd0_ce4310), [ce4330] "m"(be9dd0_ce4330), [ce84e0] "m"(be9dd0_ce84e0), [c8f390] "m"(be9dd0_c8f390), [cfff70] "m"(be9dd0_cfff70), [c12a780] "m"(be9dd0_c12a780), [ce5ab0] "m"(be9dd0_ce5ab0)
      : "memory");
}
#else
#error "FUN_000e9dd0: clang naked draft required"
#endif


/* display_scenario_help (0xea210) — XBE naked draft (batch 119). */
#if defined(__clang__)
static void *(*const bea210_tag)(int, int) = (void *)tag_get;
static void (*const bea210_assert)(const char *, const char *, int, bool) = (void *)display_assert;
static void (*const bea210_exitfn)(int) = (void *)system_exit;
static void * (*const bea210_c1d9e59)(const char *filename, const char *mode) = (void *)crt_fopen;
static char * (*const bea210_c1daeec)(char *buffer, int max_count, void *stream) = (void *)crt_fgets;
static char * (*const bea210_c8df10)(char *string, const char *delimiters) = (void *)csstrtok;
static int (*const bea210_c1d9dac)(void *stream) = (void *)crt_fclose;
static void (*const bea210_c100010)(const char *name) = (void *)main_set_multiplayer_map_name;
static void (*const bea210_cab040)(char *param_1) = (void *)FUN_000ab040;
static void * (*const bea210_c12a1d0)(void) = (void *)network_game_server_get;
static void (*const bea210_c12d6f0)(int server, char *map_name) = (void *)network_game_server_change_map_name;
static int (*const bea210_c1dd801)(const char *a, const char *b) = (void *)crt_stricmp;
static void (*const bea210_c1c2fb0)(void) = (void *)saved_game_file_remember_last_used_multiplayer_map;

__attribute__((naked, noinline))
char display_scenario_help(void *widget)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x40, %%esp\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "movl (%%edi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x44654c61\n\t"
      "call *%[tag]\n\t"
      "movl 0x3e0(%%eax), %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $1, %%ecx\n\t"
      "je .Ldisplay_scenario_help_1\n\t"
      "pushl $1\n\t"
      "pushl $0x500\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x285ec0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Ldisplay_scenario_help_1:\n\t"
      "movl 0x34(%%edi), %%esi\n\t"
      "movl (%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x44654c61\n\t"
      "call *%[tag]\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $0, (%%eax)\n\t"
      "jne .Ldisplay_scenario_help_2\n\t"
      "cmpl $3, 0x3e0(%%eax)\n\t"
      "je .Ldisplay_scenario_help_3\n\t"
      ".Ldisplay_scenario_help_2:\n\t"
      "pushl $1\n\t"
      "pushl $0x505\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x285e70\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Ldisplay_scenario_help_3:\n\t"
      "movl 0x34(%%esi), %%esi\n\t"
      "movl (%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x44654c61\n\t"
      "call *%[tag]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $2, (%%esi)\n\t"
      "je .Ldisplay_scenario_help_4\n\t"
      "pushl $1\n\t"
      "pushl $0x508\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x285db8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Ldisplay_scenario_help_4:\n\t"
      "cmpl $3, 0x3e0(%%esi)\n\t"
      "je .Ldisplay_scenario_help_5\n\t"
      "pushl $1\n\t"
      "pushl $0x509\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x285d78\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Ldisplay_scenario_help_5:\n\t"
      "movl 0x34(%%edi), %%eax\n\t"
      "movl 0x34(%%eax), %%esi\n\t"
      "movw 0x3c(%%esi), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "jl .Ldisplay_scenario_help_6\n\t"
      "cmpw $0xd, %%ax\n\t"
      "jl .Ldisplay_scenario_help_7\n\t"
      ".Ldisplay_scenario_help_6:\n\t"
      "pushl $1\n\t"
      "pushl $0x512\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x285e20\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Ldisplay_scenario_help_7:\n\t"
      "movswl 0x3c(%%esi), %%ecx\n\t"
      "movl 0x31e4c8(,%%ecx,4), %%edi\n\t"
      "pushl $0x2658a4\n\t"
      "pushl $0x285e04\n\t"
      "call *%[c1d9e59]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $8, %%esp\n\t"
      "testl %%esi, %%esi\n\t"
      "je .Ldisplay_scenario_help_8\n\t"
      "pushl %%esi\n\t"
      "leal -0x40(%%ebp), %%edx\n\t"
      "pushl $0x40\n\t"
      "pushl %%edx\n\t"
      "call *%[c1daeec]\n\t"
      "leal -0x40(%%ebp), %%eax\n\t"
      "pushl $0x285dfc\n\t"
      "pushl %%eax\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "call *%[c8df10]\n\t"
      "pushl %%esi\n\t"
      "leal -0x40(%%ebp), %%edi\n\t"
      "call *%[c1d9dac]\n\t"
      "addl $0x18, %%esp\n\t"
      ".Ldisplay_scenario_help_8:\n\t"
      "pushl %%edi\n\t"
      "call *%[c100010]\n\t"
      "pushl %%edi\n\t"
      "call *%[cab040]\n\t"
      "addl $8, %%esp\n\t"
      "call *%[c12a1d0]\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Ldisplay_scenario_help_9\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[c12d6f0]\n\t"
      "addl $8, %%esp\n\t"
      ".Ldisplay_scenario_help_9:\n\t"
      "xorl %%esi, %%esi\n\t"
      ".Ldisplay_scenario_help_10:\n\t"
      "movl 0x31e4c8(,%%esi,4), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edi\n\t"
      "call *%[c1dd801]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Ldisplay_scenario_help_11\n\t"
      "incl %%esi\n\t"
      "cmpl $0xd, %%esi\n\t"
      "jl .Ldisplay_scenario_help_10\n\t"
      "popl %%edi\n\t"
      "movb $1, %%al\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Ldisplay_scenario_help_11:\n\t"
      "movl 0x31e4c8(,%%esi,4), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c1c2fb0]\n\t"
      "addl $4, %%esp\n\t"
      "popl %%edi\n\t"
      "movb $1, %%al\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [tag] "m"(bea210_tag), [assert] "m"(bea210_assert), [exitfn] "m"(bea210_exitfn), [c1d9e59] "m"(bea210_c1d9e59), [c1daeec] "m"(bea210_c1daeec), [c8df10] "m"(bea210_c8df10), [c1d9dac] "m"(bea210_c1d9dac), [c100010] "m"(bea210_c100010), [cab040] "m"(bea210_cab040), [c12a1d0] "m"(bea210_c12a1d0), [c12d6f0] "m"(bea210_c12d6f0), [c1dd801] "m"(bea210_c1dd801), [c1c2fb0] "m"(bea210_c1c2fb0)
      : "memory");
}
#else
#error "display_scenario_help: clang naked draft required"
#endif


/* network_game_server_list_initialize (0xea3e0) — XBE naked draft (batch 125). */
#if defined(__clang__)
static void *(*const bea3e0_memset)(void *, int, unsigned int) = (void *)csmemset;
static void *(*const bea3e0_tag)(int, int) = (void *)tag_get;
static void (*const bea3e0_assert)(const char *, const char *, int, bool) = (void *)display_assert;
static void (*const bea3e0_exitfn)(int) = (void *)system_exit;
static void * (*const bea3e0_ce3d20)(int a1, unsigned short a2, const char *a3, unsigned int a4) = (void *)ui_widget_realloc;
static void (*const bea3e0_c1c26b0)(void) = (void *)FUN_001c26b0;
static void (*const bea3e0_c1c2ed0)(void) = (void *)saved_game_file_retrieve_last_used_multiplayer_variant_directory;
static void (*const bea3e0_c1c38d0)(void) = (void *)saved_game_file_find_profile_index_for_directory_path;

__attribute__((naked, noinline))
char network_game_server_list_initialize(void *widget)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x100, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl $0x144\n\t"
      "pushl $-1\n\t"
      "pushl $0x5aa260\n\t"
      "movl $0xffffffff, 0x31e494\n\t"
      "call *%[memset]\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "movl (%%edi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x44654c61\n\t"
      "call *%[tag]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $0x14, %%esp\n\t"
      "cmpw $2, (%%esi)\n\t"
      "je .Lnetwork_game_server_list_initialize_1\n\t"
      "pushl $1\n\t"
      "pushl $0x568\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x285f48\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lnetwork_game_server_list_initialize_1:\n\t"
      "cmpl $3, 0x3e0(%%esi)\n\t"
      "je .Lnetwork_game_server_list_initialize_2\n\t"
      "pushl $1\n\t"
      "pushl $0x569\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x285f08\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lnetwork_game_server_list_initialize_2:\n\t"
      "movl 0x40(%%edi), %%ecx\n\t"
      "pushl $0x56e\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x190\n\t"
      "pushl %%ecx\n\t"
      "call *%[ce3d20]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $0x10, %%esp\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%esi, 0x40(%%edi)\n\t"
      "je .Lnetwork_game_server_list_initialize_7\n\t"
      "pushl %%esi\n\t"
      "leal 0x8(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0\n\t"
      "movl $0x64, 0x8(%%ebp)\n\t"
      "call *%[c1c26b0]\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpw $3, %%ax\n\t"
      "jae .Lnetwork_game_server_list_initialize_4\n\t"
      "movzwl %%ax, %%ecx\n\t"
      "movl $3, %%edx\n\t"
      "subl %%eax, %%edx\n\t"
      "leal (%%esi,%%ecx,4), %%ecx\n\t"
      "movzwl %%dx, %%edx\n\t"
      ".Lnetwork_game_server_list_initialize_3:\n\t"
      "movl $0xffffffff, (%%ecx)\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "incl %%eax\n\t"
      "addl $4, %%ecx\n\t"
      "decl %%edx\n\t"
      "movl %%eax, 0x8(%%ebp)\n\t"
      "jne .Lnetwork_game_server_list_initialize_3\n\t"
      ".Lnetwork_game_server_list_initialize_4:\n\t"
      "movw %%ax, 0x44(%%edi)\n\t"
      "leal -0x100(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1c2ed0]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lnetwork_game_server_list_initialize_7\n\t"
      "leal -0x100(%%ebp), %%ecx\n\t"
      "pushl $1\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1c38d0]\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lnetwork_game_server_list_initialize_7\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "testw %%dx, %%dx\n\t"
      "jbe .Lnetwork_game_server_list_initialize_7\n\t"
      "leal (%%esp), %%esp\n\t"
      ".Lnetwork_game_server_list_initialize_5:\n\t"
      "movzwl %%cx, %%ebx\n\t"
      "cmpl %%eax, (%%esi,%%ebx,4)\n\t"
      "je .Lnetwork_game_server_list_initialize_6\n\t"
      "incl %%ecx\n\t"
      "cmpw %%dx, %%cx\n\t"
      "jb .Lnetwork_game_server_list_initialize_5\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lnetwork_game_server_list_initialize_6:\n\t"
      "movw %%cx, 0x3c(%%edi)\n\t"
      ".Lnetwork_game_server_list_initialize_7:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [memset] "m"(bea3e0_memset), [tag] "m"(bea3e0_tag), [assert] "m"(bea3e0_assert), [exitfn] "m"(bea3e0_exitfn), [ce3d20] "m"(bea3e0_ce3d20), [c1c26b0] "m"(bea3e0_c1c26b0), [c1c2ed0] "m"(bea3e0_c1c2ed0), [c1c38d0] "m"(bea3e0_c1c38d0)
      : "memory");
}
#else
#error "network_game_server_list_initialize: clang naked draft required"
#endif


/* network_game_join_game_from_server_list (0xea570) — XBE naked draft (batch 113). */
#if defined(__clang__)
static void *(*const bea570_tag)(int, int) = (void *)tag_get;
static void (*const bea570_assert)(const char *, const char *, int, bool) = (void *)display_assert;
static void (*const bea570_exitfn)(int) = (void *)system_exit;
static void (*const bea570_ce5ab0)(int16_t sound_selector) = (void *)ui_play_audio_feedback_sound;
static void (*const bea570_ce4500)(int16_t error_handle, int16_t local_player_index, char a3, char a4) = (void *)display_error_deferred;
static void (*const bea570_c1c26f0)(void) = (void *)playlist_profile_delete;
static void * (*const bea570_c12a1d0)(void) = (void *)network_game_server_get;
static void (*const bea570_c1c4da0)(void) = (void *)FUN_001c4da0;
static void (*const bea570_c1c2e00)(void) = (void *)saved_game_file_remember_last_used_multiplayer_variant_directory;
static void * (*const bea570_c1d9e59)(const char *filename, const char *mode) = (void *)crt_fopen;
static char * (*const bea570_c1daeec)(char *buffer, int max_count, void *stream) = (void *)crt_fgets;
static char * (*const bea570_c8df10)(char *string, const char *delimiters) = (void *)csstrtok;
static void *(*const bea570_memset)(void *, int, unsigned int) = (void *)csmemset;
static game_variant_t * (*const bea570_cadd50)(game_variant_t *variant, const char *name) = (void *)game_engine_get_variant_by_name;
static int (*const bea570_c8da40)(const void *a, const void *b, int size) = (void *)csmemcmp;
static int (*const bea570_c1d9dac)(void *stream) = (void *)crt_fclose;
static void (*const bea570_ce0a60)(void *) = (void *)player_ui_set_game_variant;
static void (*const bea570_c12d7f0)(void *server, void *variant) = (void *)network_game_server_change_game_variant;
static void (*const bea570_c8f390)(unsigned __int16 a1, const char *a2, ...) = (void *)error;

__attribute__((naked, noinline))
char network_game_join_game_from_server_list(void *widget)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x320, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "movl (%%edi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x44654c61\n\t"
      "call *%[tag]\n\t"
      "movl 0x3e0(%%eax), %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $1, %%ecx\n\t"
      "je .Lnetwork_game_join_game_from_server_list_1\n\t"
      "pushl $1\n\t"
      "pushl $0x5b9\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x286108\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lnetwork_game_join_game_from_server_list_1:\n\t"
      "movl 0x34(%%edi), %%esi\n\t"
      "movl (%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x44654c61\n\t"
      "call *%[tag]\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $0, (%%eax)\n\t"
      "movl $3, %%ebx\n\t"
      "jne .Lnetwork_game_join_game_from_server_list_2\n\t"
      "cmpl %%ebx, 0x3e0(%%eax)\n\t"
      "je .Lnetwork_game_join_game_from_server_list_3\n\t"
      ".Lnetwork_game_join_game_from_server_list_2:\n\t"
      "pushl $1\n\t"
      "pushl $0x5be\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x2860b8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lnetwork_game_join_game_from_server_list_3:\n\t"
      "movl 0x34(%%esi), %%esi\n\t"
      "movl (%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x44654c61\n\t"
      "call *%[tag]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $2, (%%esi)\n\t"
      "je .Lnetwork_game_join_game_from_server_list_4\n\t"
      "pushl $1\n\t"
      "pushl $0x5c1\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x286070\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lnetwork_game_join_game_from_server_list_4:\n\t"
      "cmpl %%ebx, 0x3e0(%%esi)\n\t"
      "je .Lnetwork_game_join_game_from_server_list_5\n\t"
      "pushl $1\n\t"
      "pushl $0x5c2\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x286034\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lnetwork_game_join_game_from_server_list_5:\n\t"
      "movl 0x34(%%edi), %%eax\n\t"
      "movl 0x34(%%eax), %%esi\n\t"
      "movw 0x3c(%%esi), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "jl .Lnetwork_game_join_game_from_server_list_6\n\t"
      "movzwl 0x44(%%esi), %%ecx\n\t"
      "movswl %%ax, %%edx\n\t"
      "cmpl %%ecx, %%edx\n\t"
      "jl .Lnetwork_game_join_game_from_server_list_7\n\t"
      ".Lnetwork_game_join_game_from_server_list_6:\n\t"
      "pushl $1\n\t"
      "pushl $0x5cb\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x285fe0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lnetwork_game_join_game_from_server_list_7:\n\t"
      "movswl 0x3c(%%esi), %%eax\n\t"
      "movl 0x40(%%esi), %%ecx\n\t"
      "movl (%%ecx,%%eax,4), %%esi\n\t"
      "cmpl $-1, %%esi\n\t"
      "jne .Lnetwork_game_join_game_from_server_list_8\n\t"
      "pushl $4\n\t"
      "call *%[ce5ab0]\n\t"
      "addl $4, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lnetwork_game_join_game_from_server_list_8:\n\t"
      "testl %%esi, %%esi\n\t"
      "js .Lnetwork_game_join_game_from_server_list_9\n\t"
      "pushl $0\n\t"
      "pushl $1\n\t"
      "pushl $-1\n\t"
      "pushl $0x1f\n\t"
      "call *%[ce4500]\n\t"
      "pushl $4\n\t"
      "call *%[ce5ab0]\n\t"
      "addl $0x14, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lnetwork_game_join_game_from_server_list_9:\n\t"
      "leal -0x68(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%esi\n\t"
      "call *%[c1c26f0]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lnetwork_game_join_game_from_server_list_14\n\t"
      "call *%[c12a1d0]\n\t"
      "movl %%eax, %%edi\n\t"
      "leal -0x320(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "movl %%edi, 0x8(%%ebp)\n\t"
      "call *%[c1c4da0]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lnetwork_game_join_game_from_server_list_10\n\t"
      "leal -0x320(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1c2e00]\n\t"
      "addl $4, %%esp\n\t"
      ".Lnetwork_game_join_game_from_server_list_10:\n\t"
      "pushl $0x2658a4\n\t"
      "pushl $0x285fc0\n\t"
      "call *%[c1d9e59]\n\t"
      "movl %%eax, %%ebx\n\t"
      "addl $8, %%esp\n\t"
      "testl %%ebx, %%ebx\n\t"
      "je .Lnetwork_game_join_game_from_server_list_12\n\t"
      "pushl %%ebx\n\t"
      "leal -0xe8(%%ebp), %%edx\n\t"
      "pushl $0x80\n\t"
      "pushl %%edx\n\t"
      "call *%[c1daeec]\n\t"
      "leal -0xe8(%%ebp), %%eax\n\t"
      "pushl $0x285dfc\n\t"
      "pushl %%eax\n\t"
      "movb $0, -0x69(%%ebp)\n\t"
      "call *%[c8df10]\n\t"
      "pushl $0x68\n\t"
      "leal -0x1b8(%%ebp), %%ecx\n\t"
      "pushl $0\n\t"
      "pushl %%ecx\n\t"
      "call *%[memset]\n\t"
      "leal -0xe8(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x220(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[cadd50]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl $0x1a, %%ecx\n\t"
      "leal -0x150(%%ebp), %%edi\n\t"
      "rep movsl\n\t"
      "pushl $0x68\n\t"
      "leal -0x1b8(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x150(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c8da40]\n\t"
      "addl $0x34, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lnetwork_game_join_game_from_server_list_11\n\t"
      "movl $0x1a, %%ecx\n\t"
      "leal -0x150(%%ebp), %%esi\n\t"
      "leal -0x68(%%ebp), %%edi\n\t"
      "rep movsl\n\t"
      ".Lnetwork_game_join_game_from_server_list_11:\n\t"
      "pushl %%ebx\n\t"
      "call *%[c1d9dac]\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "addl $4, %%esp\n\t"
      ".Lnetwork_game_join_game_from_server_list_12:\n\t"
      "leal -0x68(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[ce0a60]\n\t"
      "addl $4, %%esp\n\t"
      "testl %%edi, %%edi\n\t"
      "je .Lnetwork_game_join_game_from_server_list_13\n\t"
      "leal -0x68(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edi\n\t"
      "call *%[c12d7f0]\n\t"
      "addl $8, %%esp\n\t"
      ".Lnetwork_game_join_game_from_server_list_13:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lnetwork_game_join_game_from_server_list_14:\n\t"
      "pushl $0x285f90\n\t"
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
      :
      : [tag] "m"(bea570_tag), [assert] "m"(bea570_assert), [exitfn] "m"(bea570_exitfn), [ce5ab0] "m"(bea570_ce5ab0), [ce4500] "m"(bea570_ce4500), [c1c26f0] "m"(bea570_c1c26f0), [c12a1d0] "m"(bea570_c12a1d0), [c1c4da0] "m"(bea570_c1c4da0), [c1c2e00] "m"(bea570_c1c2e00), [c1d9e59] "m"(bea570_c1d9e59), [c1daeec] "m"(bea570_c1daeec), [c8df10] "m"(bea570_c8df10), [memset] "m"(bea570_memset), [cadd50] "m"(bea570_cadd50), [c8da40] "m"(bea570_c8da40), [c1d9dac] "m"(bea570_c1d9dac), [ce0a60] "m"(bea570_ce0a60), [c12d7f0] "m"(bea570_c12d7f0), [c8f390] "m"(bea570_c8f390)
      : "memory");
}
#else
#error "network_game_join_game_from_server_list: clang naked draft required"
#endif


/* FUN_000ea900 (0xea900) — XBE naked draft (batch 131). */
#if defined(__clang__)
static void (*const bea900_assert)(const char *, const char *, int, bool) = (void *)display_assert;
static void (*const bea900_exitfn)(int) = (void *)system_exit;
static void * (*const bea900_c12a240)(void) = (void *)network_game_client_get;
static int16_t (*const bea900_c124a30)(void *server, void *out_param) = (void *)network_game_client_get_state;
static int (*const bea900_c12a0a0)(void) = (void *)FUN_0012a0a0;
static short (*const bea900_c12a690)(void) = (void *)network_game_client_get_local_machine_index;
static bool (*const bea900_c12ac80)(void *client) = (void *)network_player_is_valid;
static char (*const bea900_c1258a0)(void *client, int16_t local_player_index) = (void *)network_game_client_add_player;
static void (*const bea900_c12b650)(const char *fmt, ...) = (void *)network_game_log;

__attribute__((naked, noinline))
char FUN_000ea900(void *widget, void *event_data)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "movl 0xc(%%ebp), %%ebx\n\t"
      "testl %%ebx, %%ebx\n\t"
      "jne .LFUN_000ea900_1\n\t"
      "pushl $1\n\t"
      "pushl $0x652\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x286184\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000ea900_1:\n\t"
      "call *%[c12a240]\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "je .LFUN_000ea900_7\n\t"
      "leal 0xc(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "call *%[c124a30]\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $2, %%ax\n\t"
      "jne .LFUN_000ea900_7\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c12a0a0]\n\t"
      "movl %%eax, %%esi\n\t"
      "call *%[c12a690]\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%eax, %%edi\n\t"
      "jne .LFUN_000ea900_2\n\t"
      "pushl $1\n\t"
      "pushl $0x65b\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x2861a8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000ea900_2:\n\t"
      "cmpw $-1, %%di\n\t"
      "je .LFUN_000ea900_5\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movl %%ecx, 0xc(%%ebp)\n\t"
      ".LFUN_000ea900_3:\n\t"
      "movswl %%cx, %%edx\n\t"
      "shll $5, %%edx\n\t"
      "leal 0x226(%%edx,%%esi,1), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c12ac80]\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000ea900_4\n\t"
      "movswl %%cx, %%edx\n\t"
      "shll $5, %%edx\n\t"
      "leal (%%edx,%%esi,1), %%eax\n\t"
      "movsbw 0x242(%%eax), %%dx\n\t"
      "cmpw %%di, %%dx\n\t"
      "jne .LFUN_000ea900_4\n\t"
      "movsbw 0x243(%%eax), %%ax\n\t"
      "cmpw 0x2(%%ebx), %%ax\n\t"
      "je .LFUN_000ea900_6\n\t"
      ".LFUN_000ea900_4:\n\t"
      "incl %%ecx\n\t"
      "cmpw $0x10, %%cx\n\t"
      "movl %%ecx, 0xc(%%ebp)\n\t"
      "jl .LFUN_000ea900_3\n\t"
      ".LFUN_000ea900_5:\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x2(%%ebx), %%cx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c1258a0]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_000ea900_6\n\t"
      "pushl $0x28618c\n\t"
      "call *%[c12b650]\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_000ea900_6:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      ".LFUN_000ea900_7:\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(bea900_assert), [exitfn] "m"(bea900_exitfn), [c12a240] "m"(bea900_c12a240), [c124a30] "m"(bea900_c124a30), [c12a0a0] "m"(bea900_c12a0a0), [c12a690] "m"(bea900_c12a690), [c12ac80] "m"(bea900_c12ac80), [c1258a0] "m"(bea900_c1258a0), [c12b650] "m"(bea900_c12b650)
      : "memory");
}
#else
#error "FUN_000ea900: clang naked draft required"
#endif


/* FUN_000eaa10 (0xeaa10) — XBE naked draft (batch 124). */
#if defined(__clang__)
static void *(*const beaa10_tag)(int, int) = (void *)tag_get;
static void *(*const beaa10_memset)(void *, int, unsigned int) = (void *)csmemset;
static void (*const beaa10_assert)(const char *, const char *, int, bool) = (void *)display_assert;
static void (*const beaa10_exitfn)(int) = (void *)system_exit;
static void * (*const beaa10_ce3d20)(int a1, unsigned short a2, const char *a3, unsigned int a4) = (void *)ui_widget_realloc;
static void (*const beaa10_c1c0d50)(int, int, int, int) = (void *)FUN_001c0d50;
static int (*const beaa10_ce0c90)(void) = (void *)player_ui_get_player1_last_used_profile_index;

__attribute__((naked, noinline))
char FUN_000eaa10(void *widget)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "movl (%%esi), %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "pushl $0x44654c61\n\t"
      "call *%[tag]\n\t"
      "pushl $0x9c\n\t"
      "pushl $-1\n\t"
      "pushl $0x5aa3c0\n\t"
      "movl %%eax, %%edi\n\t"
      "movl $0xffffffff, 0x31e494\n\t"
      "call *%[memset]\n\t"
      "addl $0x14, %%esp\n\t"
      "cmpw $2, (%%edi)\n\t"
      "je .LFUN_000eaa10_1\n\t"
      "pushl $1\n\t"
      "pushl $0x696\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x2861f8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000eaa10_1:\n\t"
      "movl 0x3e0(%%edi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "movl $3, %%ebx\n\t"
      "je .LFUN_000eaa10_2\n\t"
      "cmpl %%ebx, %%eax\n\t"
      "je .LFUN_000eaa10_2\n\t"
      "pushl $1\n\t"
      "pushl $0x698\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x2861b0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000eaa10_2:\n\t"
      "movl 0x40(%%esi), %%ecx\n\t"
      "pushl $0x69d\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x190\n\t"
      "pushl %%ecx\n\t"
      "call *%[ce3d20]\n\t"
      "addl $0x10, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%eax, 0x40(%%esi)\n\t"
      "je .LFUN_000eaa10_8\n\t"
      "cmpl %%ebx, 0x3e0(%%edi)\n\t"
      "movl $0x64, 0x8(%%ebp)\n\t"
      "movb $1, -0x4(%%ebp)\n\t"
      "jne .LFUN_000eaa10_3\n\t"
      "movb $0, -0x4(%%ebp)\n\t"
      ".LFUN_000eaa10_3:\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x8(%%esi), %%cx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "leal 0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1c0d50]\n\t"
      "movl 0x3e0(%%edi), %%eax\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpl %%ebx, %%eax\n\t"
      "jne .LFUN_000eaa10_5\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "cmpw %%bx, %%cx\n\t"
      "jae .LFUN_000eaa10_5\n\t"
      "movzwl %%cx, %%eax\n\t"
      "shll $2, %%eax\n\t"
      "subl %%ecx, %%ebx\n\t"
      "movzwl %%bx, %%ecx\n\t"
      ".LFUN_000eaa10_4:\n\t"
      "movl 0x40(%%esi), %%edx\n\t"
      "movl $0xffffffff, (%%eax,%%edx,1)\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "incl %%ebx\n\t"
      "addl $4, %%eax\n\t"
      "decl %%ecx\n\t"
      "movl %%ebx, 0x8(%%ebp)\n\t"
      "jne .LFUN_000eaa10_4\n\t"
      ".LFUN_000eaa10_5:\n\t"
      "movw 0x8(%%ebp), %%ax\n\t"
      "movw %%ax, 0x44(%%esi)\n\t"
      "call *%[ce0c90]\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_000eaa10_8\n\t"
      "movl 0x40(%%esi), %%edx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "cmpw %%cx, 0x44(%%esi)\n\t"
      "jbe .LFUN_000eaa10_8\n\t"
      ".LFUN_000eaa10_6:\n\t"
      "cmpl %%eax, (%%edx,%%ecx,4)\n\t"
      "je .LFUN_000eaa10_7\n\t"
      "movzwl 0x44(%%esi), %%edi\n\t"
      "incl %%ecx\n\t"
      "cmpl %%edi, %%ecx\n\t"
      "jl .LFUN_000eaa10_6\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000eaa10_7:\n\t"
      "movw %%cx, 0x3c(%%esi)\n\t"
      ".LFUN_000eaa10_8:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [tag] "m"(beaa10_tag), [memset] "m"(beaa10_memset), [assert] "m"(beaa10_assert), [exitfn] "m"(beaa10_exitfn), [ce3d20] "m"(beaa10_ce3d20), [c1c0d50] "m"(beaa10_c1c0d50), [ce0c90] "m"(beaa10_ce0c90)
      : "memory");
}
#else
#error "FUN_000eaa10: clang naked draft required"
#endif


/* FUN_000eaba0 (0xeaba0) — XBE naked draft (batch 118). */
#if defined(__clang__)
static void (*const beaba0_assert)(const char *, const char *, int, bool) = (void *)display_assert;
static void (*const beaba0_exitfn)(int) = (void *)system_exit;
static void *(*const beaba0_tag)(int, int) = (void *)tag_get;
static void (*const beaba0_ce4500)(int16_t error_handle, int16_t local_player_index, char a3, char a4) = (void *)display_error_deferred;
static void (*const beaba0_ce5ab0)(int16_t sound_selector) = (void *)ui_play_audio_feedback_sound;
static void (*const beaba0_c1c18f0)(void) = (void *)player_profile_new;
static int (*const beaba0_ce0810)(short local_player_index) = (void *)player_ui_get_single_player_local_player_from_controller;
static void (*const beaba0_ce1490)(void) = (void *)player_ui_set_active_player_profile;
static void (*const beaba0_c8f390)(unsigned __int16 a1, const char *a2, ...) = (void *)error;

__attribute__((naked, noinline))
char FUN_000eaba0(void *widget, void *event_data)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x30, %%esp\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_000eaba0_1\n\t"
      "cmpw $-1, 0x2(%%eax)\n\t"
      "jne .LFUN_000eaba0_2\n\t"
      ".LFUN_000eaba0_1:\n\t"
      "pushl $1\n\t"
      "pushl $0x6e3\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x2863b4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000eaba0_2:\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "movl (%%edi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x44654c61\n\t"
      "call *%[tag]\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $0, (%%eax)\n\t"
      "jne .LFUN_000eaba0_3\n\t"
      "cmpl $3, 0x3e0(%%eax)\n\t"
      "jge .LFUN_000eaba0_4\n\t"
      ".LFUN_000eaba0_3:\n\t"
      "pushl $1\n\t"
      "pushl $0x6ec\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x286360\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000eaba0_4:\n\t"
      "movl 0x34(%%edi), %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x44654c61\n\t"
      "call *%[tag]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $2, (%%esi)\n\t"
      "je .LFUN_000eaba0_5\n\t"
      "pushl $1\n\t"
      "pushl $0x6ef\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x286320\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000eaba0_5:\n\t"
      "cmpl $3, 0x3e0(%%esi)\n\t"
      "je .LFUN_000eaba0_6\n\t"
      "pushl $1\n\t"
      "pushl $0x6f0\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x2862e8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000eaba0_6:\n\t"
      "movl 0x34(%%edi), %%esi\n\t"
      "movw 0x3c(%%esi), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "jl .LFUN_000eaba0_7\n\t"
      "movzwl 0x44(%%esi), %%edx\n\t"
      "movswl %%ax, %%eax\n\t"
      "cmpl %%edx, %%eax\n\t"
      "jl .LFUN_000eaba0_8\n\t"
      ".LFUN_000eaba0_7:\n\t"
      "pushl $1\n\t"
      "pushl $0x6f8\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x286298\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000eaba0_8:\n\t"
      "movswl 0x3c(%%esi), %%ecx\n\t"
      "movl 0x40(%%esi), %%edi\n\t"
      "movl (%%edi,%%ecx,4), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_000eaba0_11\n\t"
      "testl %%eax, %%eax\n\t"
      "js .LFUN_000eaba0_9\n\t"
      "pushl $0\n\t"
      "pushl $1\n\t"
      "pushl $-1\n\t"
      "pushl $0x1f\n\t"
      "call *%[ce4500]\n\t"
      "pushl $4\n\t"
      "call *%[ce5ab0]\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "addl $0x14, %%esp\n\t"
      "popl %%edi\n\t"
      "movb $1, (%%edx)\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000eaba0_9:\n\t"
      "leal -0x30(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "call *%[c1c18f0]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000eaba0_10\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x2(%%edx), %%ax\n\t"
      "pushl %%eax\n\t"
      "call *%[ce0810]\n\t"
      "movswl 0x3c(%%esi), %%edx\n\t"
      "leal -0x30(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl (%%edi,%%edx,4), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "call *%[ce1490]\n\t"
      "addl $0x10, %%esp\n\t"
      "popl %%edi\n\t"
      "movb $1, %%al\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000eaba0_10:\n\t"
      "pushl $0x286264\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "popl %%edi\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000eaba0_11:\n\t"
      "pushl $0x28623c\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "pushl $4\n\t"
      "call *%[ce5ab0]\n\t"
      "addl $0xc, %%esp\n\t"
      "popl %%edi\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(beaba0_assert), [exitfn] "m"(beaba0_exitfn), [tag] "m"(beaba0_tag), [ce4500] "m"(beaba0_ce4500), [ce5ab0] "m"(beaba0_ce5ab0), [c1c18f0] "m"(beaba0_c1c18f0), [ce0810] "m"(beaba0_ce0810), [ce1490] "m"(beaba0_ce1490), [c8f390] "m"(beaba0_c8f390)
      : "memory");
}
#else
#error "FUN_000eaba0: clang naked draft required"
#endif


/* multiplayer_level_select (0xead60) — XBE naked draft (batch 123). */
#if defined(__clang__)
static void (*const bead60_assert)(const char *, const char *, int, bool) = (void *)display_assert;
static void (*const bead60_exitfn)(int) = (void *)system_exit;
static void *(*const bead60_tag)(int, int) = (void *)tag_get;
static void (*const bead60_ce4500)(int16_t error_handle, int16_t local_player_index, char a3, char a4) = (void *)display_error_deferred;
static void (*const bead60_ce5ab0)(int16_t sound_selector) = (void *)ui_play_audio_feedback_sound;
static void (*const bead60_c1c18f0)(void) = (void *)player_profile_new;
static void (*const bead60_ce1490)(void) = (void *)player_ui_set_active_player_profile;
static void (*const bead60_c8f390)(unsigned __int16 a1, const char *a2, ...) = (void *)error;

__attribute__((naked, noinline))
char multiplayer_level_select(void *widget, void *event_data)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x30, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0xc(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "pushl %%edi\n\t"
      "je .Lmultiplayer_level_select_1\n\t"
      "cmpw $-1, 0x2(%%esi)\n\t"
      "jne .Lmultiplayer_level_select_2\n\t"
      ".Lmultiplayer_level_select_1:\n\t"
      "pushl $1\n\t"
      "pushl $0x72a\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x2863b4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lmultiplayer_level_select_2:\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movw 0x2(%%esi), %%bx\n\t"
      "movl 0x34(%%eax), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .Lmultiplayer_level_select_4\n\t"
      ".Lmultiplayer_level_select_3:\n\t"
      "cmpw $2, 0xe(%%esi)\n\t"
      "je .Lmultiplayer_level_select_5\n\t"
      "movl 0x2c(%%esi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .Lmultiplayer_level_select_3\n\t"
      ".Lmultiplayer_level_select_4:\n\t"
      "pushl $1\n\t"
      "pushl $0x72e\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x286498\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lmultiplayer_level_select_5:\n\t"
      "movl (%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x44654c61\n\t"
      "call *%[tag]\n\t"
      "movl 0x3e0(%%eax), %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .Lmultiplayer_level_select_6\n\t"
      "pushl $1\n\t"
      "pushl $0x735\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x286440\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lmultiplayer_level_select_6:\n\t"
      "movw 0x3c(%%esi), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "jl .Lmultiplayer_level_select_7\n\t"
      "movzwl 0x44(%%esi), %%edx\n\t"
      "movswl %%ax, %%eax\n\t"
      "cmpl %%edx, %%eax\n\t"
      "jl .Lmultiplayer_level_select_8\n\t"
      ".Lmultiplayer_level_select_7:\n\t"
      "pushl $1\n\t"
      "pushl $0x73b\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x2863f0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lmultiplayer_level_select_8:\n\t"
      "movswl 0x3c(%%esi), %%ecx\n\t"
      "movl 0x40(%%esi), %%edi\n\t"
      "movl (%%edi,%%ecx,4), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "js .Lmultiplayer_level_select_9\n\t"
      "pushl $0\n\t"
      "pushl $1\n\t"
      "pushl %%ebx\n\t"
      "pushl $0x1f\n\t"
      "call *%[ce4500]\n\t"
      "pushl $4\n\t"
      "call *%[ce5ab0]\n\t"
      "addl $0x14, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lmultiplayer_level_select_9:\n\t"
      "leal -0x30(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c1c18f0]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lmultiplayer_level_select_10\n\t"
      "movswl 0x3c(%%esi), %%ecx\n\t"
      "movl (%%edi,%%ecx,4), %%edx\n\t"
      "leal -0x30(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%ebx\n\t"
      "call *%[ce1490]\n\t"
      "addl $0xc, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lmultiplayer_level_select_10:\n\t"
      "pushl $0x286264\n\t"
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
      :
      : [assert] "m"(bead60_assert), [exitfn] "m"(bead60_exitfn), [tag] "m"(bead60_tag), [ce4500] "m"(bead60_ce4500), [ce5ab0] "m"(bead60_ce5ab0), [c1c18f0] "m"(bead60_c1c18f0), [ce1490] "m"(bead60_ce1490), [c8f390] "m"(bead60_c8f390)
      : "memory");
}
#else
#error "multiplayer_level_select: clang naked draft required"
#endif


/* FUN_000eaec0 (0xeaec0) — XBE naked draft (batch 125). */
#if defined(__clang__)
static void *(*const beaec0_tag)(int, int) = (void *)tag_get;
static void (*const beaec0_assert)(const char *, const char *, int, bool) = (void *)display_assert;
static void (*const beaec0_exitfn)(int) = (void *)system_exit;
static void (*const beaec0_ce1500)(void) = (void *)player_ui_begin_editing_profile;
static void (*const beaec0_ce4500)(int16_t error_handle, int16_t local_player_index, char a3, char a4) = (void *)display_error_deferred;
static void (*const beaec0_ce5ab0)(int16_t sound_selector) = (void *)ui_play_audio_feedback_sound;

__attribute__((naked, noinline))
char FUN_000eaec0(void *widget)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "movl (%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x44654c61\n\t"
      "xorb %%bl, %%bl\n\t"
      "movl $0xffffffff, 0x31e494\n\t"
      "call *%[tag]\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $0, (%%eax)\n\t"
      "jne .LFUN_000eaec0_1\n\t"
      "cmpl $3, 0x3e0(%%eax)\n\t"
      "jge .LFUN_000eaec0_2\n\t"
      ".LFUN_000eaec0_1:\n\t"
      "pushl $1\n\t"
      "pushl $0x768\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x286500\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000eaec0_2:\n\t"
      "movl 0x34(%%esi), %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x44654c61\n\t"
      "call *%[tag]\n\t"
      "movl %%eax, %%edi\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $2, (%%edi)\n\t"
      "je .LFUN_000eaec0_3\n\t"
      "pushl $1\n\t"
      "pushl $0x76b\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x286070\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000eaec0_3:\n\t"
      "cmpl $3, 0x3e0(%%edi)\n\t"
      "popl %%edi\n\t"
      "je .LFUN_000eaec0_4\n\t"
      "pushl $1\n\t"
      "pushl $0x76c\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x286034\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000eaec0_4:\n\t"
      "movl 0x34(%%esi), %%esi\n\t"
      "movw 0x3c(%%esi), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "jl .LFUN_000eaec0_5\n\t"
      "movzwl 0x44(%%esi), %%edx\n\t"
      "movswl %%ax, %%eax\n\t"
      "cmpl %%edx, %%eax\n\t"
      "jl .LFUN_000eaec0_6\n\t"
      ".LFUN_000eaec0_5:\n\t"
      "pushl $1\n\t"
      "pushl $0x775\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x285fe0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000eaec0_6:\n\t"
      "movswl 0x3c(%%esi), %%ecx\n\t"
      "movl 0x40(%%esi), %%edx\n\t"
      "movl (%%edx,%%ecx,4), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_000eaec0_8\n\t"
      "testl %%eax, %%eax\n\t"
      "jns .LFUN_000eaec0_7\n\t"
      "pushl %%eax\n\t"
      "call *%[ce1500]\n\t"
      "addl $4, %%esp\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000eaec0_7:\n\t"
      "pushl $0\n\t"
      "pushl $1\n\t"
      "pushl $-1\n\t"
      "pushl $0x1f\n\t"
      "call *%[ce4500]\n\t"
      "pushl $4\n\t"
      "call *%[ce5ab0]\n\t"
      "addl $0x14, %%esp\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000eaec0_8:\n\t"
      "pushl $4\n\t"
      "call *%[ce5ab0]\n\t"
      "addl $4, %%esp\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [tag] "m"(beaec0_tag), [assert] "m"(beaec0_assert), [exitfn] "m"(beaec0_exitfn), [ce1500] "m"(beaec0_ce1500), [ce4500] "m"(beaec0_ce4500), [ce5ab0] "m"(beaec0_ce5ab0)
      : "memory");
}
#else
#error "FUN_000eaec0: clang naked draft required"
#endif


/* FUN_000eb020 (0xeb020) — XBE naked draft (batch 124). */
#if defined(__clang__)
static void *(*const beb020_ce0ec0)(void) = (void *)player_ui_get_edit_playlist_profile;
static void (*const beb020_assert)(const char *, const char *, int, bool) = (void *)display_assert;
static void (*const beb020_exitfn)(int) = (void *)system_exit;
static void (*const beb020_c8f390)(unsigned __int16 a1, const char *a2, ...) = (void *)error;
static void *(*const beb020_memset)(void *, int, unsigned int) = (void *)csmemset;

__attribute__((naked, noinline))
char FUN_000eb020(void *widget)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[ce0ec0]\n\t"
      "movl %%eax, %%edi\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl 0x30(%%eax), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "movb $1, %%bl\n\t"
      "je .LFUN_000eb020_1\n\t"
      "cmpw $3, 0xe(%%esi)\n\t"
      "je .LFUN_000eb020_2\n\t"
      ".LFUN_000eb020_1:\n\t"
      "pushl $1\n\t"
      "pushl $0x7a6\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x2865a0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000eb020_2:\n\t"
      "testl %%edi, %%edi\n\t"
      "je .LFUN_000eb020_11\n\t"
      "movswl 0x3c(%%esi), %%eax\n\t"
      "cmpl $4, %%eax\n\t"
      "ja .LFUN_000eb020_8\n\t"
      "jmp *.LFUN_000eb020_jt(,%%eax,4)\n\t"
      ".LFUN_000eb020_3:\n\t"
      "movl $1, %%esi\n\t"
      "jmp .LFUN_000eb020_9\n\t"
      ".LFUN_000eb020_4:\n\t"
      "movl $4, %%esi\n\t"
      "jmp .LFUN_000eb020_9\n\t"
      ".LFUN_000eb020_5:\n\t"
      "movl $2, %%esi\n\t"
      "jmp .LFUN_000eb020_9\n\t"
      ".LFUN_000eb020_6:\n\t"
      "movl $3, %%esi\n\t"
      "jmp .LFUN_000eb020_9\n\t"
      ".LFUN_000eb020_7:\n\t"
      "movl $5, %%esi\n\t"
      "jmp .LFUN_000eb020_9\n\t"
      ".LFUN_000eb020_8:\n\t"
      "pushl $0x28657c\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "movl 0x18(%%edi), %%esi\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_000eb020_9:\n\t"
      "cmpl 0x18(%%edi), %%esi\n\t"
      "je .LFUN_000eb020_10\n\t"
      "pushl $0x18\n\t"
      "leal 0x4c(%%edi), %%ecx\n\t"
      "pushl $0\n\t"
      "pushl %%ecx\n\t"
      "call *%[memset]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_000eb020_10:\n\t"
      "movl %%esi, 0x18(%%edi)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000eb020_11:\n\t"
      "pushl $0x286550\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_000eb020_jt:\n\t"
      ".long .LFUN_000eb020_3\n\t"
      ".long .LFUN_000eb020_4\n\t"
      ".long .LFUN_000eb020_5\n\t"
      ".long .LFUN_000eb020_6\n\t"
      ".long .LFUN_000eb020_7\n\t"
      ".text\n\t"
      :
      : [ce0ec0] "m"(beb020_ce0ec0), [assert] "m"(beb020_assert), [exitfn] "m"(beb020_exitfn), [c8f390] "m"(beb020_c8f390), [memset] "m"(beb020_memset)
      : "memory");
}
#else
#error "FUN_000eb020: clang naked draft required"
#endif


/* FUN_000eb150 (0xeb150) — XBE naked draft (batch 109). */
#if defined(__clang__)
static void *(*const beb150_ce0ec0)(void) = (void *)player_ui_get_edit_playlist_profile;
static void (*const beb150_assert)(const char *, const char *, int, bool) = (void *)display_assert;
static void (*const beb150_exitfn)(int) = (void *)system_exit;
static void (*const beb150_c8f390)(unsigned __int16 a1, const char *a2, ...) = (void *)error;
static void (*const beb150_ce59e0)(int16_t player_index) = (void *)ui_widgets_pop_stack;

__attribute__((naked, noinline))
char FUN_000eb150(void *widget)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "call *%[ce0ec0]\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "cmpl %%ebx, %%eax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "je .LFUN_000eb150_46\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x34(%%eax), %%edi\n\t"
      "cmpl %%ebx, %%edi\n\t"
      "jne .LFUN_000eb150_1\n\t"
      "pushl $1\n\t"
      "pushl $0x7f8\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x2868d0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000eb150_1:\n\t"
      "movl 0x34(%%edi), %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "je .LFUN_000eb150_3\n\t"
      "leal (%%ebx), %%ebx\n\t"
      ".LFUN_000eb150_2:\n\t"
      "cmpw $2, 0xe(%%esi)\n\t"
      "je .LFUN_000eb150_4\n\t"
      "movl 0x2c(%%esi), %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "jne .LFUN_000eb150_2\n\t"
      ".LFUN_000eb150_3:\n\t"
      "pushl $1\n\t"
      "pushl $0x7fa\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x2868a8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000eb150_4:\n\t"
      "movswl 0x3c(%%esi), %%eax\n\t"
      "subl %%ebx, %%eax\n\t"
      "je .LFUN_000eb150_6\n\t"
      "decl %%eax\n\t"
      "je .LFUN_000eb150_5\n\t"
      "pushl $0x28686c\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "jmp .LFUN_000eb150_7\n\t"
      ".LFUN_000eb150_5:\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movb %%bl, 0x4c(%%ecx)\n\t"
      "jmp .LFUN_000eb150_7\n\t"
      ".LFUN_000eb150_6:\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "movb $1, 0x4c(%%edx)\n\t"
      ".LFUN_000eb150_7:\n\t"
      "movl 0x2c(%%edi), %%edi\n\t"
      "cmpl %%ebx, %%edi\n\t"
      "jne .LFUN_000eb150_8\n\t"
      "pushl $1\n\t"
      "pushl $0x803\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x286848\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000eb150_8:\n\t"
      "movl 0x34(%%edi), %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "je .LFUN_000eb150_10\n\t"
      "movl $2, %%eax\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_000eb150_9:\n\t"
      "cmpw %%ax, 0xe(%%esi)\n\t"
      "je .LFUN_000eb150_11\n\t"
      "movl 0x2c(%%esi), %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "jne .LFUN_000eb150_9\n\t"
      ".LFUN_000eb150_10:\n\t"
      "pushl $1\n\t"
      "pushl $0x805\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x28681c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000eb150_11:\n\t"
      "movswl 0x3c(%%esi), %%eax\n\t"
      "cmpl $5, %%eax\n\t"
      "ja .LFUN_000eb150_18\n\t"
      "jmp *.LFUN_000eb150_jt0(,%%eax,4)\n\t"
      ".LFUN_000eb150_12:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movl %%ebx, 0x50(%%eax)\n\t"
      "jmp .LFUN_000eb150_19\n\t"
      ".LFUN_000eb150_13:\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movl $0x708, 0x50(%%ecx)\n\t"
      "jmp .LFUN_000eb150_19\n\t"
      ".LFUN_000eb150_14:\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "movl $0xe10, 0x50(%%edx)\n\t"
      "jmp .LFUN_000eb150_19\n\t"
      ".LFUN_000eb150_15:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movl $0x1518, 0x50(%%eax)\n\t"
      "jmp .LFUN_000eb150_19\n\t"
      ".LFUN_000eb150_16:\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movl $0x2328, 0x50(%%ecx)\n\t"
      "jmp .LFUN_000eb150_19\n\t"
      ".LFUN_000eb150_17:\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "movl $0x4650, 0x50(%%edx)\n\t"
      "jmp .LFUN_000eb150_19\n\t"
      ".LFUN_000eb150_18:\n\t"
      "pushl $0x2867dc\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_000eb150_19:\n\t"
      "movl 0x2c(%%edi), %%edi\n\t"
      "cmpl %%ebx, %%edi\n\t"
      "jne .LFUN_000eb150_20\n\t"
      "pushl $1\n\t"
      "pushl $0x812\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x2867bc\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000eb150_20:\n\t"
      "movl 0x34(%%edi), %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "je .LFUN_000eb150_22\n\t"
      "movl $2, %%eax\n\t"
      ".LFUN_000eb150_21:\n\t"
      "cmpw %%ax, 0xe(%%esi)\n\t"
      "je .LFUN_000eb150_23\n\t"
      "movl 0x2c(%%esi), %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "jne .LFUN_000eb150_21\n\t"
      ".LFUN_000eb150_22:\n\t"
      "pushl $1\n\t"
      "pushl $0x814\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x28678c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000eb150_23:\n\t"
      "movswl 0x3c(%%esi), %%eax\n\t"
      "subl %%ebx, %%eax\n\t"
      "je .LFUN_000eb150_25\n\t"
      "decl %%eax\n\t"
      "je .LFUN_000eb150_24\n\t"
      "pushl $0x286748\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "jmp .LFUN_000eb150_26\n\t"
      ".LFUN_000eb150_24:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movb %%bl, 0x4e(%%eax)\n\t"
      "jmp .LFUN_000eb150_26\n\t"
      ".LFUN_000eb150_25:\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movb $1, 0x4e(%%ecx)\n\t"
      ".LFUN_000eb150_26:\n\t"
      "movl 0x2c(%%edi), %%edi\n\t"
      "cmpl %%ebx, %%edi\n\t"
      "jne .LFUN_000eb150_27\n\t"
      "pushl $1\n\t"
      "pushl $0x81d\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x286720\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000eb150_27:\n\t"
      "movl 0x34(%%edi), %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "je .LFUN_000eb150_29\n\t"
      "movl $2, %%eax\n\t"
      "movl %%edi, %%edi\n\t"
      ".LFUN_000eb150_28:\n\t"
      "cmpw %%ax, 0xe(%%esi)\n\t"
      "je .LFUN_000eb150_30\n\t"
      "movl 0x2c(%%esi), %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "jne .LFUN_000eb150_28\n\t"
      ".LFUN_000eb150_29:\n\t"
      "pushl $1\n\t"
      "pushl $0x81f\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x2866e8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000eb150_30:\n\t"
      "movswl 0x3c(%%esi), %%eax\n\t"
      "subl %%ebx, %%eax\n\t"
      "je .LFUN_000eb150_32\n\t"
      "decl %%eax\n\t"
      "je .LFUN_000eb150_31\n\t"
      "pushl $0x2866a0\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "jmp .LFUN_000eb150_33\n\t"
      ".LFUN_000eb150_31:\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movb %%bl, 0x4f(%%ecx)\n\t"
      "jmp .LFUN_000eb150_34\n\t"
      ".LFUN_000eb150_32:\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "movb $1, 0x4f(%%edx)\n\t"
      ".LFUN_000eb150_33:\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      ".LFUN_000eb150_34:\n\t"
      "movl 0x2c(%%edi), %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "jne .LFUN_000eb150_35\n\t"
      "pushl $1\n\t"
      "pushl $0x828\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x28667c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000eb150_35:\n\t"
      "movl 0x34(%%esi), %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "je .LFUN_000eb150_37\n\t"
      "movl $2, %%eax\n\t"
      ".LFUN_000eb150_36:\n\t"
      "cmpw %%ax, 0xe(%%esi)\n\t"
      "je .LFUN_000eb150_38\n\t"
      "movl 0x2c(%%esi), %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "jne .LFUN_000eb150_36\n\t"
      ".LFUN_000eb150_37:\n\t"
      "pushl $1\n\t"
      "pushl $0x82a\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x28664c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000eb150_38:\n\t"
      "movswl 0x3c(%%esi), %%eax\n\t"
      "cmpl $4, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "ja .LFUN_000eb150_44\n\t"
      "jmp *.LFUN_000eb150_jt1(,%%eax,4)\n\t"
      ".LFUN_000eb150_39:\n\t"
      "movl $1, 0x40(%%ecx)\n\t"
      "jmp .LFUN_000eb150_45\n\t"
      ".LFUN_000eb150_40:\n\t"
      "movl $3, 0x40(%%ecx)\n\t"
      "jmp .LFUN_000eb150_45\n\t"
      ".LFUN_000eb150_41:\n\t"
      "movl $5, 0x40(%%ecx)\n\t"
      "jmp .LFUN_000eb150_45\n\t"
      ".LFUN_000eb150_42:\n\t"
      "movl $0xa, 0x40(%%ecx)\n\t"
      "jmp .LFUN_000eb150_45\n\t"
      ".LFUN_000eb150_43:\n\t"
      "movl $0xf, 0x40(%%ecx)\n\t"
      "jmp .LFUN_000eb150_45\n\t"
      ".LFUN_000eb150_44:\n\t"
      "pushl $0x286608\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_000eb150_45:\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x8(%%eax), %%cx\n\t"
      "pushl %%ecx\n\t"
      "call *%[ce59e0]\n\t"
      "addl $4, %%esp\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000eb150_46:\n\t"
      "pushl $0x286550\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_000eb150_jt0:\n\t"
      ".long .LFUN_000eb150_12\n\t"
      ".long .LFUN_000eb150_13\n\t"
      ".long .LFUN_000eb150_14\n\t"
      ".long .LFUN_000eb150_15\n\t"
      ".long .LFUN_000eb150_16\n\t"
      ".long .LFUN_000eb150_17\n\t"
      ".text\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_000eb150_jt1:\n\t"
      ".long .LFUN_000eb150_39\n\t"
      ".long .LFUN_000eb150_40\n\t"
      ".long .LFUN_000eb150_41\n\t"
      ".long .LFUN_000eb150_42\n\t"
      ".long .LFUN_000eb150_43\n\t"
      ".text\n\t"
      :
      : [ce0ec0] "m"(beb150_ce0ec0), [assert] "m"(beb150_assert), [exitfn] "m"(beb150_exitfn), [c8f390] "m"(beb150_c8f390), [ce59e0] "m"(beb150_ce59e0)
      : "memory");
}
#else
#error "FUN_000eb150: clang naked draft required"
#endif


/* FUN_000eb4f0 (0xeb4f0) — XBE naked draft (batch 116). */
#if defined(__clang__)
static void *(*const beb4f0_ce0ec0)(void) = (void *)player_ui_get_edit_playlist_profile;
static void (*const beb4f0_assert)(const char *, const char *, int, bool) = (void *)display_assert;
static void (*const beb4f0_exitfn)(int) = (void *)system_exit;
static void (*const beb4f0_c8f390)(unsigned __int16 a1, const char *a2, ...) = (void *)error;
static void (*const beb4f0_ce59e0)(int16_t player_index) = (void *)ui_widgets_pop_stack;

__attribute__((naked, noinline))
char FUN_000eb4f0(void *widget)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ebx\n\t"
      "call *%[ce0ec0]\n\t"
      "movl %%eax, %%ebx\n\t"
      "testl %%ebx, %%ebx\n\t"
      "je .LFUN_000eb4f0_26\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x34(%%eax), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .LFUN_000eb4f0_1\n\t"
      "pushl $1\n\t"
      "pushl $0x84e\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x286a64\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000eb4f0_1:\n\t"
      "movl 0x34(%%edi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_000eb4f0_3\n\t"
      ".LFUN_000eb4f0_2:\n\t"
      "cmpw $2, 0xe(%%esi)\n\t"
      "je .LFUN_000eb4f0_4\n\t"
      "movl 0x2c(%%esi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LFUN_000eb4f0_2\n\t"
      ".LFUN_000eb4f0_3:\n\t"
      "pushl $1\n\t"
      "pushl $0x850\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x286a38\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000eb4f0_4:\n\t"
      "movswl 0x3c(%%esi), %%eax\n\t"
      "subl $0, %%eax\n\t"
      "je .LFUN_000eb4f0_6\n\t"
      "decl %%eax\n\t"
      "je .LFUN_000eb4f0_5\n\t"
      "pushl $0x2869f8\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "jmp .LFUN_000eb4f0_7\n\t"
      ".LFUN_000eb4f0_5:\n\t"
      "movb $0, 0x4c(%%ebx)\n\t"
      "jmp .LFUN_000eb4f0_7\n\t"
      ".LFUN_000eb4f0_6:\n\t"
      "movb $1, 0x4c(%%ebx)\n\t"
      ".LFUN_000eb4f0_7:\n\t"
      "movl 0x2c(%%edi), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .LFUN_000eb4f0_8\n\t"
      "pushl $1\n\t"
      "pushl $0x859\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x2869d4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000eb4f0_8:\n\t"
      "movl 0x34(%%edi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_000eb4f0_10\n\t"
      "movl $2, %%eax\n\t"
      "movl %%edi, %%edi\n\t"
      ".LFUN_000eb4f0_9:\n\t"
      "cmpw %%ax, 0xe(%%esi)\n\t"
      "je .LFUN_000eb4f0_11\n\t"
      "movl 0x2c(%%esi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LFUN_000eb4f0_9\n\t"
      ".LFUN_000eb4f0_10:\n\t"
      "pushl $1\n\t"
      "pushl $0x85b\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x2869a8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000eb4f0_11:\n\t"
      "movswl 0x3c(%%esi), %%eax\n\t"
      "cmpl $4, %%eax\n\t"
      "ja .LFUN_000eb4f0_17\n\t"
      "jmp *.LFUN_000eb4f0_jt(,%%eax,4)\n\t"
      ".LFUN_000eb4f0_12:\n\t"
      "movl $1, 0x40(%%ebx)\n\t"
      "jmp .LFUN_000eb4f0_18\n\t"
      ".LFUN_000eb4f0_13:\n\t"
      "movl $2, 0x40(%%ebx)\n\t"
      "jmp .LFUN_000eb4f0_18\n\t"
      ".LFUN_000eb4f0_14:\n\t"
      "movl $5, 0x40(%%ebx)\n\t"
      "jmp .LFUN_000eb4f0_18\n\t"
      ".LFUN_000eb4f0_15:\n\t"
      "movl $0xa, 0x40(%%ebx)\n\t"
      "jmp .LFUN_000eb4f0_18\n\t"
      ".LFUN_000eb4f0_16:\n\t"
      "movl $0xf, 0x40(%%ebx)\n\t"
      "jmp .LFUN_000eb4f0_18\n\t"
      ".LFUN_000eb4f0_17:\n\t"
      "pushl $0x286968\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_000eb4f0_18:\n\t"
      "movl 0x2c(%%edi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LFUN_000eb4f0_19\n\t"
      "pushl $1\n\t"
      "pushl $0x867\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x286950\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000eb4f0_19:\n\t"
      "movl 0x34(%%esi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_000eb4f0_21\n\t"
      "movl $2, %%eax\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_000eb4f0_20:\n\t"
      "cmpw %%ax, 0xe(%%esi)\n\t"
      "je .LFUN_000eb4f0_22\n\t"
      "movl 0x2c(%%esi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LFUN_000eb4f0_20\n\t"
      ".LFUN_000eb4f0_21:\n\t"
      "pushl $1\n\t"
      "pushl $0x869\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x286928\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000eb4f0_22:\n\t"
      "movswl 0x3c(%%esi), %%eax\n\t"
      "subl $0, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "je .LFUN_000eb4f0_24\n\t"
      "decl %%eax\n\t"
      "je .LFUN_000eb4f0_23\n\t"
      "pushl $0x2868f0\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "jmp .LFUN_000eb4f0_25\n\t"
      ".LFUN_000eb4f0_23:\n\t"
      "movb $0, 0x1c(%%ebx)\n\t"
      "jmp .LFUN_000eb4f0_25\n\t"
      ".LFUN_000eb4f0_24:\n\t"
      "movb $1, 0x1c(%%ebx)\n\t"
      ".LFUN_000eb4f0_25:\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x8(%%ecx), %%dx\n\t"
      "pushl %%edx\n\t"
      "call *%[ce59e0]\n\t"
      "addl $4, %%esp\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000eb4f0_26:\n\t"
      "pushl $0x286550\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_000eb4f0_jt:\n\t"
      ".long .LFUN_000eb4f0_12\n\t"
      ".long .LFUN_000eb4f0_13\n\t"
      ".long .LFUN_000eb4f0_14\n\t"
      ".long .LFUN_000eb4f0_15\n\t"
      ".long .LFUN_000eb4f0_16\n\t"
      ".text\n\t"
      :
      : [ce0ec0] "m"(beb4f0_ce0ec0), [assert] "m"(beb4f0_assert), [exitfn] "m"(beb4f0_exitfn), [c8f390] "m"(beb4f0_c8f390), [ce59e0] "m"(beb4f0_ce59e0)
      : "memory");
}
#else
#error "FUN_000eb4f0: clang naked draft required"
#endif


/* FUN_000eb710 (0xeb710) — XBE naked draft (batch 109). */
#if defined(__clang__)
static void *(*const beb710_ce0ec0)(void) = (void *)player_ui_get_edit_playlist_profile;
static void (*const beb710_assert)(const char *, const char *, int, bool) = (void *)display_assert;
static void (*const beb710_exitfn)(int) = (void *)system_exit;
static void (*const beb710_c8f390)(unsigned __int16 a1, const char *a2, ...) = (void *)error;
static void (*const beb710_ce59e0)(int16_t player_index) = (void *)ui_widgets_pop_stack;

__attribute__((naked, noinline))
char FUN_000eb710(void *widget)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "call *%[ce0ec0]\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "cmpl %%ebx, %%eax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "je .LFUN_000eb710_40\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x34(%%eax), %%edi\n\t"
      "cmpl %%ebx, %%edi\n\t"
      "jne .LFUN_000eb710_1\n\t"
      "pushl $1\n\t"
      "pushl $0x88b\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x286c9c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000eb710_1:\n\t"
      "movl 0x34(%%edi), %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "je .LFUN_000eb710_3\n\t"
      "leal (%%ebx), %%ebx\n\t"
      ".LFUN_000eb710_2:\n\t"
      "cmpw $2, 0xe(%%esi)\n\t"
      "je .LFUN_000eb710_4\n\t"
      "movl 0x2c(%%esi), %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "jne .LFUN_000eb710_2\n\t"
      ".LFUN_000eb710_3:\n\t"
      "pushl $1\n\t"
      "pushl $0x88d\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x286c70\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000eb710_4:\n\t"
      "movswl 0x3c(%%esi), %%eax\n\t"
      "subl %%ebx, %%eax\n\t"
      "je .LFUN_000eb710_6\n\t"
      "decl %%eax\n\t"
      "je .LFUN_000eb710_5\n\t"
      "pushl $0x286c30\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "jmp .LFUN_000eb710_7\n\t"
      ".LFUN_000eb710_5:\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movb $1, 0x4c(%%ecx)\n\t"
      "jmp .LFUN_000eb710_7\n\t"
      ".LFUN_000eb710_6:\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "movb %%bl, 0x4c(%%edx)\n\t"
      ".LFUN_000eb710_7:\n\t"
      "movl 0x2c(%%edi), %%edi\n\t"
      "cmpl %%ebx, %%edi\n\t"
      "jne .LFUN_000eb710_8\n\t"
      "pushl $1\n\t"
      "pushl $0x896\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x286c10\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000eb710_8:\n\t"
      "movl 0x34(%%edi), %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "je .LFUN_000eb710_10\n\t"
      "movl $2, %%eax\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_000eb710_9:\n\t"
      "cmpw %%ax, 0xe(%%esi)\n\t"
      "je .LFUN_000eb710_11\n\t"
      "movl 0x2c(%%esi), %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "jne .LFUN_000eb710_9\n\t"
      ".LFUN_000eb710_10:\n\t"
      "pushl $1\n\t"
      "pushl $0x898\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x286be0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000eb710_11:\n\t"
      "movswl 0x3c(%%esi), %%eax\n\t"
      "subl %%ebx, %%eax\n\t"
      "je .LFUN_000eb710_13\n\t"
      "decl %%eax\n\t"
      "je .LFUN_000eb710_12\n\t"
      "pushl $0x286ba0\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "jmp .LFUN_000eb710_14\n\t"
      ".LFUN_000eb710_12:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movb %%bl, 0x4e(%%eax)\n\t"
      "jmp .LFUN_000eb710_14\n\t"
      ".LFUN_000eb710_13:\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movb $1, 0x4e(%%ecx)\n\t"
      ".LFUN_000eb710_14:\n\t"
      "movl 0x2c(%%edi), %%edi\n\t"
      "cmpl %%ebx, %%edi\n\t"
      "jne .LFUN_000eb710_15\n\t"
      "pushl $1\n\t"
      "pushl $0x8a1\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x286b80\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000eb710_15:\n\t"
      "movl 0x34(%%edi), %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "je .LFUN_000eb710_17\n\t"
      "movl $2, %%eax\n\t"
      "jmp .LFUN_000eb710_16\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".LFUN_000eb710_16:\n\t"
      "cmpw %%ax, 0xe(%%esi)\n\t"
      "je .LFUN_000eb710_18\n\t"
      "movl 0x2c(%%esi), %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "jne .LFUN_000eb710_16\n\t"
      ".LFUN_000eb710_17:\n\t"
      "pushl $1\n\t"
      "pushl $0x8a3\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x286b54\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000eb710_18:\n\t"
      "movswl 0x3c(%%esi), %%eax\n\t"
      "subl %%ebx, %%eax\n\t"
      "je .LFUN_000eb710_20\n\t"
      "decl %%eax\n\t"
      "je .LFUN_000eb710_19\n\t"
      "pushl $0x286b14\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "jmp .LFUN_000eb710_21\n\t"
      ".LFUN_000eb710_19:\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "movb $1, 0x4d(%%edx)\n\t"
      "jmp .LFUN_000eb710_21\n\t"
      ".LFUN_000eb710_20:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movb %%bl, 0x4d(%%eax)\n\t"
      ".LFUN_000eb710_21:\n\t"
      "movl 0x2c(%%edi), %%edi\n\t"
      "cmpl %%ebx, %%edi\n\t"
      "jne .LFUN_000eb710_22\n\t"
      "pushl $1\n\t"
      "pushl $0x8ac\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x286af4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000eb710_22:\n\t"
      "movl 0x34(%%edi), %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "je .LFUN_000eb710_24\n\t"
      "movl $2, %%eax\n\t"
      "jmp .LFUN_000eb710_23\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".LFUN_000eb710_23:\n\t"
      "cmpw %%ax, 0xe(%%esi)\n\t"
      "je .LFUN_000eb710_25\n\t"
      "movl 0x2c(%%esi), %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "jne .LFUN_000eb710_23\n\t"
      ".LFUN_000eb710_24:\n\t"
      "pushl $1\n\t"
      "pushl $0x8ae\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x286ac8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000eb710_25:\n\t"
      "movswl 0x3c(%%esi), %%eax\n\t"
      "cmpl $4, %%eax\n\t"
      "ja .LFUN_000eb710_31\n\t"
      "jmp *.LFUN_000eb710_jt(,%%eax,4)\n\t"
      ".LFUN_000eb710_26:\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movl $5, 0x40(%%ecx)\n\t"
      "jmp .LFUN_000eb710_32\n\t"
      ".LFUN_000eb710_27:\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "movl $0xa, 0x40(%%edx)\n\t"
      "jmp .LFUN_000eb710_32\n\t"
      ".LFUN_000eb710_28:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movl $0xf, 0x40(%%eax)\n\t"
      "jmp .LFUN_000eb710_32\n\t"
      ".LFUN_000eb710_29:\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movl $0x19, 0x40(%%ecx)\n\t"
      "jmp .LFUN_000eb710_32\n\t"
      ".LFUN_000eb710_30:\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "movl $0x32, 0x40(%%edx)\n\t"
      "jmp .LFUN_000eb710_32\n\t"
      ".LFUN_000eb710_31:\n\t"
      "pushl $0x286a88\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_000eb710_32:\n\t"
      "movl 0x2c(%%edi), %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "jne .LFUN_000eb710_33\n\t"
      "pushl $1\n\t"
      "pushl $0x8ba\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x286950\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000eb710_33:\n\t"
      "movl 0x34(%%esi), %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "je .LFUN_000eb710_35\n\t"
      "movl $2, %%eax\n\t"
      "jmp .LFUN_000eb710_34\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".LFUN_000eb710_34:\n\t"
      "cmpw %%ax, 0xe(%%esi)\n\t"
      "je .LFUN_000eb710_36\n\t"
      "movl 0x2c(%%esi), %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "jne .LFUN_000eb710_34\n\t"
      ".LFUN_000eb710_35:\n\t"
      "pushl $1\n\t"
      "pushl $0x8bc\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x286928\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000eb710_36:\n\t"
      "movswl 0x3c(%%esi), %%eax\n\t"
      "subl %%ebx, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "je .LFUN_000eb710_38\n\t"
      "decl %%eax\n\t"
      "je .LFUN_000eb710_37\n\t"
      "pushl $0x2868f0\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "jmp .LFUN_000eb710_39\n\t"
      ".LFUN_000eb710_37:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movb %%bl, 0x1c(%%eax)\n\t"
      "jmp .LFUN_000eb710_39\n\t"
      ".LFUN_000eb710_38:\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movb $1, 0x1c(%%ecx)\n\t"
      ".LFUN_000eb710_39:\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x8(%%edx), %%ax\n\t"
      "pushl %%eax\n\t"
      "call *%[ce59e0]\n\t"
      "addl $4, %%esp\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000eb710_40:\n\t"
      "pushl $0x286550\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_000eb710_jt:\n\t"
      ".long .LFUN_000eb710_26\n\t"
      ".long .LFUN_000eb710_27\n\t"
      ".long .LFUN_000eb710_28\n\t"
      ".long .LFUN_000eb710_29\n\t"
      ".long .LFUN_000eb710_30\n\t"
      ".text\n\t"
      :
      : [ce0ec0] "m"(beb710_ce0ec0), [assert] "m"(beb710_assert), [exitfn] "m"(beb710_exitfn), [c8f390] "m"(beb710_c8f390), [ce59e0] "m"(beb710_ce59e0)
      : "memory");
}
#else
#error "FUN_000eb710: clang naked draft required"
#endif


/* FUN_000eba70 (0xeba70) — XBE naked draft (batch 106). */
#if defined(__clang__)
static void *(*const beba70_ce0ec0)(void) = (void *)player_ui_get_edit_playlist_profile;
static void (*const beba70_assert)(const char *, const char *, int, bool) = (void *)display_assert;
static void (*const beba70_exitfn)(int) = (void *)system_exit;
static void (*const beba70_c8f390)(unsigned __int16 a1, const char *a2, ...) = (void *)error;
static void (*const beba70_ce59e0)(int16_t player_index) = (void *)ui_widgets_pop_stack;

__attribute__((naked, noinline))
char FUN_000eba70(void *widget)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "call *%[ce0ec0]\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "je .LFUN_000eba70_68\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x34(%%eax), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .LFUN_000eba70_1\n\t"
      "pushl $1\n\t"
      "pushl $0x8de\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x287034\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000eba70_1:\n\t"
      "movl 0x34(%%edi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "movl $2, %%eax\n\t"
      "je .LFUN_000eba70_3\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_000eba70_2:\n\t"
      "cmpw %%ax, 0xe(%%esi)\n\t"
      "je .LFUN_000eba70_4\n\t"
      "movl 0x2c(%%esi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LFUN_000eba70_2\n\t"
      ".LFUN_000eba70_3:\n\t"
      "pushl $1\n\t"
      "pushl $0x8e0\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x287004\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000eba70_4:\n\t"
      "movswl 0x3c(%%esi), %%eax\n\t"
      "cmpl $3, %%eax\n\t"
      "ja .LFUN_000eba70_9\n\t"
      "jmp *.LFUN_000eba70_jt0(,%%eax,4)\n\t"
      ".LFUN_000eba70_5:\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movl $0, 0x54(%%ecx)\n\t"
      "jmp .LFUN_000eba70_10\n\t"
      ".LFUN_000eba70_6:\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "movl $1, 0x54(%%edx)\n\t"
      "jmp .LFUN_000eba70_10\n\t"
      ".LFUN_000eba70_7:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movl $2, 0x54(%%eax)\n\t"
      "jmp .LFUN_000eba70_10\n\t"
      ".LFUN_000eba70_8:\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movl $3, 0x54(%%ecx)\n\t"
      "jmp .LFUN_000eba70_10\n\t"
      ".LFUN_000eba70_9:\n\t"
      "pushl $0x286fc0\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_000eba70_10:\n\t"
      "movl 0x2c(%%edi), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .LFUN_000eba70_11\n\t"
      "pushl $1\n\t"
      "pushl $0x8eb\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x286f98\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000eba70_11:\n\t"
      "movl 0x34(%%edi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_000eba70_13\n\t"
      "movl $2, %%eax\n\t"
      "nop\n\t"
      ".LFUN_000eba70_12:\n\t"
      "cmpw %%ax, 0xe(%%esi)\n\t"
      "je .LFUN_000eba70_14\n\t"
      "movl 0x2c(%%esi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LFUN_000eba70_12\n\t"
      ".LFUN_000eba70_13:\n\t"
      "pushl $1\n\t"
      "pushl $0x8ed\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x286f64\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000eba70_14:\n\t"
      "movswl 0x3c(%%esi), %%eax\n\t"
      "cmpl $3, %%eax\n\t"
      "ja .LFUN_000eba70_19\n\t"
      "jmp *.LFUN_000eba70_jt1(,%%eax,4)\n\t"
      ".LFUN_000eba70_15:\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "movl $0, 0x58(%%edx)\n\t"
      "jmp .LFUN_000eba70_20\n\t"
      ".LFUN_000eba70_16:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movl $1, 0x58(%%eax)\n\t"
      "jmp .LFUN_000eba70_20\n\t"
      ".LFUN_000eba70_17:\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movl $2, 0x58(%%ecx)\n\t"
      "jmp .LFUN_000eba70_20\n\t"
      ".LFUN_000eba70_18:\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "movl $3, 0x58(%%edx)\n\t"
      "jmp .LFUN_000eba70_20\n\t"
      ".LFUN_000eba70_19:\n\t"
      "pushl $0x286f20\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_000eba70_20:\n\t"
      "movl 0x2c(%%edi), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .LFUN_000eba70_21\n\t"
      "pushl $1\n\t"
      "pushl $0x8f8\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x286efc\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000eba70_21:\n\t"
      "movl 0x34(%%edi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_000eba70_23\n\t"
      "movl $2, %%eax\n\t"
      "nop\n\t"
      ".LFUN_000eba70_22:\n\t"
      "cmpw %%ax, 0xe(%%esi)\n\t"
      "je .LFUN_000eba70_24\n\t"
      "movl 0x2c(%%esi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LFUN_000eba70_22\n\t"
      ".LFUN_000eba70_23:\n\t"
      "pushl $1\n\t"
      "pushl $0x8fa\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x286ecc\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000eba70_24:\n\t"
      "movswl 0x3c(%%esi), %%eax\n\t"
      "subl $0, %%eax\n\t"
      "je .LFUN_000eba70_27\n\t"
      "decl %%eax\n\t"
      "je .LFUN_000eba70_26\n\t"
      "decl %%eax\n\t"
      "je .LFUN_000eba70_25\n\t"
      "pushl $0x286e88\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "jmp .LFUN_000eba70_28\n\t"
      ".LFUN_000eba70_25:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movl $2, 0x50(%%eax)\n\t"
      "jmp .LFUN_000eba70_28\n\t"
      ".LFUN_000eba70_26:\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movl $0, 0x50(%%ecx)\n\t"
      "jmp .LFUN_000eba70_28\n\t"
      ".LFUN_000eba70_27:\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "movl $1, 0x50(%%edx)\n\t"
      ".LFUN_000eba70_28:\n\t"
      "movl 0x2c(%%edi), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .LFUN_000eba70_29\n\t"
      "pushl $1\n\t"
      "pushl $0x904\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x286e6c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000eba70_29:\n\t"
      "movl 0x34(%%edi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_000eba70_31\n\t"
      "movl $2, %%eax\n\t"
      ".LFUN_000eba70_30:\n\t"
      "cmpw %%ax, 0xe(%%esi)\n\t"
      "je .LFUN_000eba70_32\n\t"
      "movl 0x2c(%%esi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LFUN_000eba70_30\n\t"
      ".LFUN_000eba70_31:\n\t"
      "pushl $1\n\t"
      "pushl $0x906\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x286e40\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000eba70_32:\n\t"
      "movswl 0x3c(%%esi), %%eax\n\t"
      "subl $0, %%eax\n\t"
      "je .LFUN_000eba70_35\n\t"
      "decl %%eax\n\t"
      "je .LFUN_000eba70_34\n\t"
      "decl %%eax\n\t"
      "je .LFUN_000eba70_33\n\t"
      "pushl $0x286e04\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "jmp .LFUN_000eba70_36\n\t"
      ".LFUN_000eba70_33:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movl $2, 0x5c(%%eax)\n\t"
      "jmp .LFUN_000eba70_36\n\t"
      ".LFUN_000eba70_34:\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movl $1, 0x5c(%%ecx)\n\t"
      "jmp .LFUN_000eba70_36\n\t"
      ".LFUN_000eba70_35:\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "movl $0, 0x5c(%%edx)\n\t"
      ".LFUN_000eba70_36:\n\t"
      "movl 0x2c(%%edi), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .LFUN_000eba70_37\n\t"
      "pushl $1\n\t"
      "pushl $0x910\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x286de4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000eba70_37:\n\t"
      "movl 0x34(%%edi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_000eba70_39\n\t"
      "movl $2, %%eax\n\t"
      ".LFUN_000eba70_38:\n\t"
      "cmpw %%ax, 0xe(%%esi)\n\t"
      "je .LFUN_000eba70_40\n\t"
      "movl 0x2c(%%esi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LFUN_000eba70_38\n\t"
      ".LFUN_000eba70_39:\n\t"
      "pushl $1\n\t"
      "pushl $0x912\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x286db8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000eba70_40:\n\t"
      "movswl 0x3c(%%esi), %%eax\n\t"
      "subl $0, %%eax\n\t"
      "je .LFUN_000eba70_42\n\t"
      "decl %%eax\n\t"
      "je .LFUN_000eba70_41\n\t"
      "pushl $0x286d78\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "jmp .LFUN_000eba70_43\n\t"
      ".LFUN_000eba70_41:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movb $0, 0x4c(%%eax)\n\t"
      "jmp .LFUN_000eba70_43\n\t"
      ".LFUN_000eba70_42:\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movb $1, 0x4c(%%ecx)\n\t"
      ".LFUN_000eba70_43:\n\t"
      "movl 0x2c(%%edi), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .LFUN_000eba70_44\n\t"
      "pushl $1\n\t"
      "pushl $0x91b\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x286d54\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000eba70_44:\n\t"
      "movl 0x34(%%edi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_000eba70_46\n\t"
      "movl $2, %%eax\n\t"
      ".LFUN_000eba70_45:\n\t"
      "cmpw %%ax, 0xe(%%esi)\n\t"
      "je .LFUN_000eba70_47\n\t"
      "movl 0x2c(%%esi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LFUN_000eba70_45\n\t"
      ".LFUN_000eba70_46:\n\t"
      "pushl $1\n\t"
      "pushl $0x91d\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x286d24\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000eba70_47:\n\t"
      "movswl 0x3c(%%esi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jl .LFUN_000eba70_48\n\t"
      "cmpl $0xf, %%eax\n\t"
      "jg .LFUN_000eba70_48\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "incl %%eax\n\t"
      "movl %%eax, 0x60(%%edx)\n\t"
      "jmp .LFUN_000eba70_49\n\t"
      ".LFUN_000eba70_48:\n\t"
      "pushl $0x286ce0\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_000eba70_49:\n\t"
      "movl 0x2c(%%edi), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .LFUN_000eba70_50\n\t"
      "pushl $1\n\t"
      "pushl $0x936\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x286cc0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000eba70_50:\n\t"
      "movl 0x34(%%edi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_000eba70_52\n\t"
      "movl $2, %%eax\n\t"
      ".LFUN_000eba70_51:\n\t"
      "cmpw %%ax, 0xe(%%esi)\n\t"
      "je .LFUN_000eba70_53\n\t"
      "movl 0x2c(%%esi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LFUN_000eba70_51\n\t"
      ".LFUN_000eba70_52:\n\t"
      "pushl $1\n\t"
      "pushl $0x938\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x2869a8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000eba70_53:\n\t"
      "movswl 0x3c(%%esi), %%eax\n\t"
      "cmpl $4, %%eax\n\t"
      "ja .LFUN_000eba70_59\n\t"
      "jmp *.LFUN_000eba70_jt2(,%%eax,4)\n\t"
      ".LFUN_000eba70_54:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movl $1, 0x40(%%eax)\n\t"
      "jmp .LFUN_000eba70_60\n\t"
      ".LFUN_000eba70_55:\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movl $2, 0x40(%%ecx)\n\t"
      "jmp .LFUN_000eba70_60\n\t"
      ".LFUN_000eba70_56:\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "movl $5, 0x40(%%edx)\n\t"
      "jmp .LFUN_000eba70_60\n\t"
      ".LFUN_000eba70_57:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movl $0xa, 0x40(%%eax)\n\t"
      "jmp .LFUN_000eba70_60\n\t"
      ".LFUN_000eba70_58:\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movl $0xf, 0x40(%%ecx)\n\t"
      "jmp .LFUN_000eba70_60\n\t"
      ".LFUN_000eba70_59:\n\t"
      "pushl $0x286968\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_000eba70_60:\n\t"
      "movl 0x2c(%%edi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LFUN_000eba70_61\n\t"
      "pushl $1\n\t"
      "pushl $0x944\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x286950\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000eba70_61:\n\t"
      "movl 0x34(%%esi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_000eba70_63\n\t"
      "movl $2, %%eax\n\t"
      ".LFUN_000eba70_62:\n\t"
      "cmpw %%ax, 0xe(%%esi)\n\t"
      "je .LFUN_000eba70_64\n\t"
      "movl 0x2c(%%esi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LFUN_000eba70_62\n\t"
      ".LFUN_000eba70_63:\n\t"
      "pushl $1\n\t"
      "pushl $0x946\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x286928\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000eba70_64:\n\t"
      "movswl 0x3c(%%esi), %%eax\n\t"
      "subl $0, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "je .LFUN_000eba70_66\n\t"
      "decl %%eax\n\t"
      "je .LFUN_000eba70_65\n\t"
      "pushl $0x2868f0\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "jmp .LFUN_000eba70_67\n\t"
      ".LFUN_000eba70_65:\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "movb $0, 0x1c(%%edx)\n\t"
      "jmp .LFUN_000eba70_67\n\t"
      ".LFUN_000eba70_66:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movb $1, 0x1c(%%eax)\n\t"
      ".LFUN_000eba70_67:\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x8(%%ecx), %%dx\n\t"
      "pushl %%edx\n\t"
      "call *%[ce59e0]\n\t"
      "addl $4, %%esp\n\t"
      "movb $1, %%al\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000eba70_68:\n\t"
      "pushl $0x286550\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "xorb %%al, %%al\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_000eba70_jt0:\n\t"
      ".long .LFUN_000eba70_5\n\t"
      ".long .LFUN_000eba70_6\n\t"
      ".long .LFUN_000eba70_7\n\t"
      ".long .LFUN_000eba70_8\n\t"
      ".text\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_000eba70_jt1:\n\t"
      ".long .LFUN_000eba70_15\n\t"
      ".long .LFUN_000eba70_16\n\t"
      ".long .LFUN_000eba70_17\n\t"
      ".long .LFUN_000eba70_18\n\t"
      ".text\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_000eba70_jt2:\n\t"
      ".long .LFUN_000eba70_54\n\t"
      ".long .LFUN_000eba70_55\n\t"
      ".long .LFUN_000eba70_56\n\t"
      ".long .LFUN_000eba70_57\n\t"
      ".long .LFUN_000eba70_58\n\t"
      ".text\n\t"
      :
      : [ce0ec0] "m"(beba70_ce0ec0), [assert] "m"(beba70_assert), [exitfn] "m"(beba70_exitfn), [c8f390] "m"(beba70_c8f390), [ce59e0] "m"(beba70_ce59e0)
      : "memory");
}
#else
#error "FUN_000eba70: clang naked draft required"
#endif


/* FUN_000ebff0 (0xebff0) — XBE naked draft (batch 112). */
#if defined(__clang__)
static void *(*const bebff0_ce0ec0)(void) = (void *)player_ui_get_edit_playlist_profile;
static void (*const bebff0_assert)(const char *, const char *, int, bool) = (void *)display_assert;
static void (*const bebff0_exitfn)(int) = (void *)system_exit;
static void (*const bebff0_c8f390)(unsigned __int16 a1, const char *a2, ...) = (void *)error;
static void (*const bebff0_ce59e0)(int16_t player_index) = (void *)ui_widgets_pop_stack;

__attribute__((naked, noinline))
char FUN_000ebff0(void *widget)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ebx\n\t"
      "call *%[ce0ec0]\n\t"
      "movl %%eax, %%ebx\n\t"
      "testl %%ebx, %%ebx\n\t"
      "je .LFUN_000ebff0_36\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x34(%%eax), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .LFUN_000ebff0_1\n\t"
      "pushl $1\n\t"
      "pushl $0x968\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x2871d8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000ebff0_1:\n\t"
      "movl 0x34(%%edi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_000ebff0_3\n\t"
      ".LFUN_000ebff0_2:\n\t"
      "cmpw $2, 0xe(%%esi)\n\t"
      "je .LFUN_000ebff0_4\n\t"
      "movl 0x2c(%%esi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LFUN_000ebff0_2\n\t"
      ".LFUN_000ebff0_3:\n\t"
      "pushl $1\n\t"
      "pushl $0x96a\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x2871ac\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000ebff0_4:\n\t"
      "movswl 0x3c(%%esi), %%eax\n\t"
      "subl $0, %%eax\n\t"
      "je .LFUN_000ebff0_7\n\t"
      "decl %%eax\n\t"
      "je .LFUN_000ebff0_6\n\t"
      "decl %%eax\n\t"
      "je .LFUN_000ebff0_5\n\t"
      "pushl $0x28716c\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "jmp .LFUN_000ebff0_8\n\t"
      ".LFUN_000ebff0_5:\n\t"
      "movl $2, 0x50(%%ebx)\n\t"
      "jmp .LFUN_000ebff0_8\n\t"
      ".LFUN_000ebff0_6:\n\t"
      "movl $1, 0x50(%%ebx)\n\t"
      "jmp .LFUN_000ebff0_8\n\t"
      ".LFUN_000ebff0_7:\n\t"
      "movl $0, 0x50(%%ebx)\n\t"
      ".LFUN_000ebff0_8:\n\t"
      "movl 0x2c(%%edi), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .LFUN_000ebff0_9\n\t"
      "pushl $1\n\t"
      "pushl $0x974\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x28714c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000ebff0_9:\n\t"
      "movl 0x34(%%edi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_000ebff0_11\n\t"
      "movl $2, %%eax\n\t"
      ".LFUN_000ebff0_10:\n\t"
      "cmpw %%ax, 0xe(%%esi)\n\t"
      "je .LFUN_000ebff0_12\n\t"
      "movl 0x2c(%%esi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LFUN_000ebff0_10\n\t"
      ".LFUN_000ebff0_11:\n\t"
      "pushl $1\n\t"
      "pushl $0x976\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x287120\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000ebff0_12:\n\t"
      "movswl 0x3c(%%esi), %%eax\n\t"
      "subl $0, %%eax\n\t"
      "je .LFUN_000ebff0_15\n\t"
      "decl %%eax\n\t"
      "je .LFUN_000ebff0_14\n\t"
      "decl %%eax\n\t"
      "je .LFUN_000ebff0_13\n\t"
      "pushl $0x2870e4\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "jmp .LFUN_000ebff0_16\n\t"
      ".LFUN_000ebff0_13:\n\t"
      "movl $2, 0x4c(%%ebx)\n\t"
      "jmp .LFUN_000ebff0_16\n\t"
      ".LFUN_000ebff0_14:\n\t"
      "movl $1, 0x4c(%%ebx)\n\t"
      "jmp .LFUN_000ebff0_16\n\t"
      ".LFUN_000ebff0_15:\n\t"
      "movl $0, 0x4c(%%ebx)\n\t"
      ".LFUN_000ebff0_16:\n\t"
      "movl 0x2c(%%edi), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .LFUN_000ebff0_17\n\t"
      "pushl $1\n\t"
      "pushl $0x980\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x2870c8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000ebff0_17:\n\t"
      "movl 0x34(%%edi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_000ebff0_19\n\t"
      "movl $2, %%eax\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_000ebff0_18:\n\t"
      "cmpw %%ax, 0xe(%%esi)\n\t"
      "je .LFUN_000ebff0_20\n\t"
      "movl 0x2c(%%esi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LFUN_000ebff0_18\n\t"
      ".LFUN_000ebff0_19:\n\t"
      "pushl $1\n\t"
      "pushl $0x982\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x28709c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000ebff0_20:\n\t"
      "movswl 0x3c(%%esi), %%eax\n\t"
      "cmpl $5, %%eax\n\t"
      "ja .LFUN_000ebff0_27\n\t"
      "jmp *.LFUN_000ebff0_jt(,%%eax,4)\n\t"
      ".LFUN_000ebff0_21:\n\t"
      "movl $1, 0x40(%%ebx)\n\t"
      "jmp .LFUN_000ebff0_28\n\t"
      ".LFUN_000ebff0_22:\n\t"
      "movl $3, 0x40(%%ebx)\n\t"
      "jmp .LFUN_000ebff0_28\n\t"
      ".LFUN_000ebff0_23:\n\t"
      "movl $5, 0x40(%%ebx)\n\t"
      "jmp .LFUN_000ebff0_28\n\t"
      ".LFUN_000ebff0_24:\n\t"
      "movl $0xa, 0x40(%%ebx)\n\t"
      "jmp .LFUN_000ebff0_28\n\t"
      ".LFUN_000ebff0_25:\n\t"
      "movl $0xf, 0x40(%%ebx)\n\t"
      "jmp .LFUN_000ebff0_28\n\t"
      ".LFUN_000ebff0_26:\n\t"
      "movl $0x19, 0x40(%%ebx)\n\t"
      "jmp .LFUN_000ebff0_28\n\t"
      ".LFUN_000ebff0_27:\n\t"
      "pushl $0x28705c\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_000ebff0_28:\n\t"
      "movl 0x2c(%%edi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LFUN_000ebff0_29\n\t"
      "pushl $1\n\t"
      "pushl $0x98f\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x286950\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000ebff0_29:\n\t"
      "movl 0x34(%%esi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_000ebff0_31\n\t"
      "movl $2, %%eax\n\t"
      ".LFUN_000ebff0_30:\n\t"
      "cmpw %%ax, 0xe(%%esi)\n\t"
      "je .LFUN_000ebff0_32\n\t"
      "movl 0x2c(%%esi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LFUN_000ebff0_30\n\t"
      ".LFUN_000ebff0_31:\n\t"
      "pushl $1\n\t"
      "pushl $0x991\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x286928\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000ebff0_32:\n\t"
      "movswl 0x3c(%%esi), %%eax\n\t"
      "subl $0, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "je .LFUN_000ebff0_34\n\t"
      "decl %%eax\n\t"
      "je .LFUN_000ebff0_33\n\t"
      "pushl $0x2868f0\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "jmp .LFUN_000ebff0_35\n\t"
      ".LFUN_000ebff0_33:\n\t"
      "movb $0, 0x1c(%%ebx)\n\t"
      "jmp .LFUN_000ebff0_35\n\t"
      ".LFUN_000ebff0_34:\n\t"
      "movb $1, 0x1c(%%ebx)\n\t"
      ".LFUN_000ebff0_35:\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x8(%%ecx), %%dx\n\t"
      "pushl %%edx\n\t"
      "call *%[ce59e0]\n\t"
      "addl $4, %%esp\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000ebff0_36:\n\t"
      "pushl $0x286550\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_000ebff0_jt:\n\t"
      ".long .LFUN_000ebff0_21\n\t"
      ".long .LFUN_000ebff0_22\n\t"
      ".long .LFUN_000ebff0_23\n\t"
      ".long .LFUN_000ebff0_24\n\t"
      ".long .LFUN_000ebff0_25\n\t"
      ".long .LFUN_000ebff0_26\n\t"
      ".text\n\t"
      :
      : [ce0ec0] "m"(bebff0_ce0ec0), [assert] "m"(bebff0_assert), [exitfn] "m"(bebff0_exitfn), [c8f390] "m"(bebff0_c8f390), [ce59e0] "m"(bebff0_ce59e0)
      : "memory");
}
#else
#error "FUN_000ebff0: clang naked draft required"
#endif


/* FUN_000ec2c0 (0xec2c0) — XBE naked draft (batch 106). */
#if defined(__clang__)
static void *(*const bec2c0_ce0ec0)(void) = (void *)player_ui_get_edit_playlist_profile;
static void (*const bec2c0_assert)(const char *, const char *, int, bool) = (void *)display_assert;
static void (*const bec2c0_exitfn)(int) = (void *)system_exit;
static void (*const bec2c0_c8f390)(unsigned __int16 a1, const char *a2, ...) = (void *)error;

__attribute__((naked, noinline))
char FUN_000ec2c0(void *widget)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ebx\n\t"
      "call *%[ce0ec0]\n\t"
      "movl %%eax, %%ebx\n\t"
      "testl %%ebx, %%ebx\n\t"
      "je .LFUN_000ec2c0_75\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x34(%%eax), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .LFUN_000ec2c0_1\n\t"
      "pushl $1\n\t"
      "pushl $0x9b3\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x287654\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000ec2c0_1:\n\t"
      "movl 0x34(%%edi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "movl $2, %%eax\n\t"
      "je .LFUN_000ec2c0_3\n\t"
      "jmp .LFUN_000ec2c0_2\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".LFUN_000ec2c0_2:\n\t"
      "cmpw %%ax, 0xe(%%esi)\n\t"
      "je .LFUN_000ec2c0_4\n\t"
      "movl 0x2c(%%esi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LFUN_000ec2c0_2\n\t"
      ".LFUN_000ec2c0_3:\n\t"
      "pushl $1\n\t"
      "pushl $0x9b5\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x287624\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000ec2c0_4:\n\t"
      "movswl 0x3c(%%esi), %%eax\n\t"
      "cmpl $3, %%eax\n\t"
      "ja .LFUN_000ec2c0_9\n\t"
      "jmp *.LFUN_000ec2c0_jt0(,%%eax,4)\n\t"
      ".LFUN_000ec2c0_5:\n\t"
      "movl $0, 0x38(%%ebx)\n\t"
      "jmp .LFUN_000ec2c0_10\n\t"
      ".LFUN_000ec2c0_6:\n\t"
      "movl $1, 0x38(%%ebx)\n\t"
      "jmp .LFUN_000ec2c0_10\n\t"
      ".LFUN_000ec2c0_7:\n\t"
      "movl $3, 0x38(%%ebx)\n\t"
      "jmp .LFUN_000ec2c0_10\n\t"
      ".LFUN_000ec2c0_8:\n\t"
      "movl $5, 0x38(%%ebx)\n\t"
      "jmp .LFUN_000ec2c0_10\n\t"
      ".LFUN_000ec2c0_9:\n\t"
      "pushl $0x2875e0\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_000ec2c0_10:\n\t"
      "movl 0x2c(%%edi), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .LFUN_000ec2c0_11\n\t"
      "pushl $1\n\t"
      "pushl $0x9c0\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x2875b8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000ec2c0_11:\n\t"
      "movl 0x34(%%edi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_000ec2c0_13\n\t"
      "movl $2, %%eax\n\t"
      ".LFUN_000ec2c0_12:\n\t"
      "cmpw %%ax, 0xe(%%esi)\n\t"
      "je .LFUN_000ec2c0_14\n\t"
      "movl 0x2c(%%esi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LFUN_000ec2c0_12\n\t"
      ".LFUN_000ec2c0_13:\n\t"
      "pushl $1\n\t"
      "pushl $0x9c2\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x287588\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000ec2c0_14:\n\t"
      "movswl 0x3c(%%esi), %%eax\n\t"
      "cmpl $5, %%eax\n\t"
      "ja .LFUN_000ec2c0_21\n\t"
      "jmp *.LFUN_000ec2c0_jt1(,%%eax,4)\n\t"
      ".LFUN_000ec2c0_15:\n\t"
      "movl $0x3f000000, 0x3c(%%ebx)\n\t"
      "jmp .LFUN_000ec2c0_22\n\t"
      ".LFUN_000ec2c0_16:\n\t"
      "movl $0x3f800000, 0x3c(%%ebx)\n\t"
      "jmp .LFUN_000ec2c0_22\n\t"
      ".LFUN_000ec2c0_17:\n\t"
      "movl $0x3fc00000, 0x3c(%%ebx)\n\t"
      "jmp .LFUN_000ec2c0_22\n\t"
      ".LFUN_000ec2c0_18:\n\t"
      "movl $0x40000000, 0x3c(%%ebx)\n\t"
      "jmp .LFUN_000ec2c0_22\n\t"
      ".LFUN_000ec2c0_19:\n\t"
      "movl $0x40400000, 0x3c(%%ebx)\n\t"
      "jmp .LFUN_000ec2c0_22\n\t"
      ".LFUN_000ec2c0_20:\n\t"
      "movl $0x40800000, 0x3c(%%ebx)\n\t"
      "jmp .LFUN_000ec2c0_22\n\t"
      ".LFUN_000ec2c0_21:\n\t"
      "pushl $0x287548\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_000ec2c0_22:\n\t"
      "movl 0x2c(%%edi), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .LFUN_000ec2c0_23\n\t"
      "pushl $1\n\t"
      "pushl $0x9cf\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x287530\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000ec2c0_23:\n\t"
      "movl 0x34(%%edi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_000ec2c0_25\n\t"
      "movl $2, %%eax\n\t"
      ".LFUN_000ec2c0_24:\n\t"
      "cmpw %%ax, 0xe(%%esi)\n\t"
      "je .LFUN_000ec2c0_26\n\t"
      "movl 0x2c(%%esi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LFUN_000ec2c0_24\n\t"
      ".LFUN_000ec2c0_25:\n\t"
      "pushl $1\n\t"
      "pushl $0x9d1\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x287508\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000ec2c0_26:\n\t"
      "movswl 0x3c(%%esi), %%eax\n\t"
      "subl $0, %%eax\n\t"
      "je .LFUN_000ec2c0_28\n\t"
      "decl %%eax\n\t"
      "je .LFUN_000ec2c0_27\n\t"
      "pushl $0x2874cc\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "jmp .LFUN_000ec2c0_30\n\t"
      ".LFUN_000ec2c0_27:\n\t"
      "movl 0x20(%%ebx), %%eax\n\t"
      "orl $8, %%eax\n\t"
      "jmp .LFUN_000ec2c0_29\n\t"
      ".LFUN_000ec2c0_28:\n\t"
      "movl 0x20(%%ebx), %%eax\n\t"
      "andl $0xfffffff7, %%eax\n\t"
      ".LFUN_000ec2c0_29:\n\t"
      "movl %%eax, 0x20(%%ebx)\n\t"
      ".LFUN_000ec2c0_30:\n\t"
      "movl 0x2c(%%edi), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .LFUN_000ec2c0_31\n\t"
      "pushl $1\n\t"
      "pushl $0x9da\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x2874ac\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000ec2c0_31:\n\t"
      "movl 0x34(%%edi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_000ec2c0_33\n\t"
      "movl $2, %%eax\n\t"
      ".LFUN_000ec2c0_32:\n\t"
      "cmpw %%ax, 0xe(%%esi)\n\t"
      "je .LFUN_000ec2c0_34\n\t"
      "movl 0x2c(%%esi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LFUN_000ec2c0_32\n\t"
      ".LFUN_000ec2c0_33:\n\t"
      "pushl $1\n\t"
      "pushl $0x9dc\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x287480\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000ec2c0_34:\n\t"
      "movswl 0x3c(%%esi), %%eax\n\t"
      "cmpl $3, %%eax\n\t"
      "ja .LFUN_000ec2c0_39\n\t"
      "jmp *.LFUN_000ec2c0_jt2(,%%eax,4)\n\t"
      ".LFUN_000ec2c0_35:\n\t"
      "movl $0, 0x30(%%ebx)\n\t"
      "jmp .LFUN_000ec2c0_40\n\t"
      ".LFUN_000ec2c0_36:\n\t"
      "movl $0x96, 0x30(%%ebx)\n\t"
      "jmp .LFUN_000ec2c0_40\n\t"
      ".LFUN_000ec2c0_37:\n\t"
      "movl $0x12c, 0x30(%%ebx)\n\t"
      "jmp .LFUN_000ec2c0_40\n\t"
      ".LFUN_000ec2c0_38:\n\t"
      "movl $0x1c2, 0x30(%%ebx)\n\t"
      "jmp .LFUN_000ec2c0_40\n\t"
      ".LFUN_000ec2c0_39:\n\t"
      "pushl $0x287440\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_000ec2c0_40:\n\t"
      "movl 0x2c(%%edi), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .LFUN_000ec2c0_41\n\t"
      "pushl $1\n\t"
      "pushl $0x9e7\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x28741c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000ec2c0_41:\n\t"
      "movl 0x34(%%edi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_000ec2c0_43\n\t"
      "movl $2, %%eax\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_000ec2c0_42:\n\t"
      "cmpw %%ax, 0xe(%%esi)\n\t"
      "je .LFUN_000ec2c0_44\n\t"
      "movl 0x2c(%%esi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LFUN_000ec2c0_42\n\t"
      ".LFUN_000ec2c0_43:\n\t"
      "pushl $1\n\t"
      "pushl $0x9e9\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x2873e8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000ec2c0_44:\n\t"
      "movswl 0x3c(%%esi), %%eax\n\t"
      "cmpl $3, %%eax\n\t"
      "ja .LFUN_000ec2c0_49\n\t"
      "jmp *.LFUN_000ec2c0_jt3(,%%eax,4)\n\t"
      ".LFUN_000ec2c0_45:\n\t"
      "movl $0, 0x2c(%%ebx)\n\t"
      "jmp .LFUN_000ec2c0_50\n\t"
      ".LFUN_000ec2c0_46:\n\t"
      "movl $0x96, 0x2c(%%ebx)\n\t"
      "jmp .LFUN_000ec2c0_50\n\t"
      ".LFUN_000ec2c0_47:\n\t"
      "movl $0x12c, 0x2c(%%ebx)\n\t"
      "jmp .LFUN_000ec2c0_50\n\t"
      ".LFUN_000ec2c0_48:\n\t"
      "movl $0x1c2, 0x2c(%%ebx)\n\t"
      "jmp .LFUN_000ec2c0_50\n\t"
      ".LFUN_000ec2c0_49:\n\t"
      "pushl $0x2873a0\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_000ec2c0_50:\n\t"
      "movl 0x2c(%%edi), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .LFUN_000ec2c0_51\n\t"
      "pushl $1\n\t"
      "pushl $0x9f4\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x287380\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000ec2c0_51:\n\t"
      "movl 0x34(%%edi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_000ec2c0_53\n\t"
      "movl $2, %%eax\n\t"
      ".LFUN_000ec2c0_52:\n\t"
      "cmpw %%ax, 0xe(%%esi)\n\t"
      "je .LFUN_000ec2c0_54\n\t"
      "movl 0x2c(%%esi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LFUN_000ec2c0_52\n\t"
      ".LFUN_000ec2c0_53:\n\t"
      "pushl $1\n\t"
      "pushl $0x9f6\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x287354\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000ec2c0_54:\n\t"
      "movswl 0x3c(%%esi), %%eax\n\t"
      "subl $0, %%eax\n\t"
      "je .LFUN_000ec2c0_56\n\t"
      "decl %%eax\n\t"
      "je .LFUN_000ec2c0_55\n\t"
      "pushl $0x287314\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "jmp .LFUN_000ec2c0_57\n\t"
      ".LFUN_000ec2c0_55:\n\t"
      "movb $0, 0x28(%%ebx)\n\t"
      "jmp .LFUN_000ec2c0_57\n\t"
      ".LFUN_000ec2c0_56:\n\t"
      "movb $1, 0x28(%%ebx)\n\t"
      ".LFUN_000ec2c0_57:\n\t"
      "movl 0x2c(%%edi), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .LFUN_000ec2c0_58\n\t"
      "pushl $1\n\t"
      "pushl $0x9ff\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x2872f0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000ec2c0_58:\n\t"
      "movl 0x34(%%edi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_000ec2c0_60\n\t"
      "movl $2, %%eax\n\t"
      "leal (%%ebx), %%ebx\n\t"
      ".LFUN_000ec2c0_59:\n\t"
      "cmpw %%ax, 0xe(%%esi)\n\t"
      "je .LFUN_000ec2c0_61\n\t"
      "movl 0x2c(%%esi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LFUN_000ec2c0_59\n\t"
      ".LFUN_000ec2c0_60:\n\t"
      "pushl $1\n\t"
      "pushl $0xa01\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x2872bc\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000ec2c0_61:\n\t"
      "movswl 0x3c(%%esi), %%eax\n\t"
      "subl $0, %%eax\n\t"
      "je .LFUN_000ec2c0_63\n\t"
      "decl %%eax\n\t"
      "je .LFUN_000ec2c0_62\n\t"
      "pushl $0x287278\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "jmp .LFUN_000ec2c0_65\n\t"
      ".LFUN_000ec2c0_62:\n\t"
      "movl 0x20(%%ebx), %%eax\n\t"
      "andl $0xffffffef, %%eax\n\t"
      "jmp .LFUN_000ec2c0_64\n\t"
      ".LFUN_000ec2c0_63:\n\t"
      "movl 0x20(%%ebx), %%eax\n\t"
      "orl $0x10, %%eax\n\t"
      ".LFUN_000ec2c0_64:\n\t"
      "movl %%eax, 0x20(%%ebx)\n\t"
      ".LFUN_000ec2c0_65:\n\t"
      "movl 0x2c(%%edi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_000ec2c0_70\n\t"
      "movl 0x34(%%eax), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_000ec2c0_67\n\t"
      "movl $2, %%eax\n\t"
      "movl %%edi, %%edi\n\t"
      ".LFUN_000ec2c0_66:\n\t"
      "cmpw %%ax, 0xe(%%esi)\n\t"
      "je .LFUN_000ec2c0_68\n\t"
      "movl 0x2c(%%esi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LFUN_000ec2c0_66\n\t"
      ".LFUN_000ec2c0_67:\n\t"
      "pushl $1\n\t"
      "pushl $0xa0e\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x287244\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000ec2c0_68:\n\t"
      "movswl 0x3c(%%esi), %%eax\n\t"
      "cmpl $3, %%eax\n\t"
      "ja .LFUN_000ec2c0_74\n\t"
      "jmp *.LFUN_000ec2c0_jt4(,%%eax,4)\n\t"
      ".LFUN_000ec2c0_69:\n\t"
      "movl $0, 0x34(%%ebx)\n\t"
      ".LFUN_000ec2c0_70:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000ec2c0_71:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl $0x96, 0x34(%%ebx)\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000ec2c0_72:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl $0x12c, 0x34(%%ebx)\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000ec2c0_73:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl $0x1c2, 0x34(%%ebx)\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000ec2c0_74:\n\t"
      "pushl $0x287200\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000ec2c0_75:\n\t"
      "pushl $0x286550\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_000ec2c0_jt0:\n\t"
      ".long .LFUN_000ec2c0_5\n\t"
      ".long .LFUN_000ec2c0_6\n\t"
      ".long .LFUN_000ec2c0_7\n\t"
      ".long .LFUN_000ec2c0_8\n\t"
      ".text\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_000ec2c0_jt1:\n\t"
      ".long .LFUN_000ec2c0_15\n\t"
      ".long .LFUN_000ec2c0_16\n\t"
      ".long .LFUN_000ec2c0_17\n\t"
      ".long .LFUN_000ec2c0_18\n\t"
      ".long .LFUN_000ec2c0_19\n\t"
      ".long .LFUN_000ec2c0_20\n\t"
      ".text\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_000ec2c0_jt2:\n\t"
      ".long .LFUN_000ec2c0_35\n\t"
      ".long .LFUN_000ec2c0_36\n\t"
      ".long .LFUN_000ec2c0_37\n\t"
      ".long .LFUN_000ec2c0_38\n\t"
      ".text\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_000ec2c0_jt3:\n\t"
      ".long .LFUN_000ec2c0_45\n\t"
      ".long .LFUN_000ec2c0_46\n\t"
      ".long .LFUN_000ec2c0_47\n\t"
      ".long .LFUN_000ec2c0_48\n\t"
      ".text\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_000ec2c0_jt4:\n\t"
      ".long .LFUN_000ec2c0_69\n\t"
      ".long .LFUN_000ec2c0_71\n\t"
      ".long .LFUN_000ec2c0_72\n\t"
      ".long .LFUN_000ec2c0_73\n\t"
      ".text\n\t"
      :
      : [ce0ec0] "m"(bec2c0_ce0ec0), [assert] "m"(bec2c0_assert), [exitfn] "m"(bec2c0_exitfn), [c8f390] "m"(bec2c0_c8f390)
      : "memory");
}
#else
#error "FUN_000ec2c0: clang naked draft required"
#endif


/* FUN_000ec840 (0xec840) — XBE naked draft (batch 110). */
#if defined(__clang__)
static void *(*const bec840_ce0ec0)(void) = (void *)player_ui_get_edit_playlist_profile;
static void (*const bec840_assert)(const char *, const char *, int, bool) = (void *)display_assert;
static void (*const bec840_exitfn)(int) = (void *)system_exit;
static void (*const bec840_c8f390)(unsigned __int16 a1, const char *a2, ...) = (void *)error;

__attribute__((naked, noinline))
char FUN_000ec840(void *widget)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ebx\n\t"
      "call *%[ce0ec0]\n\t"
      "movl %%eax, %%ebx\n\t"
      "testl %%ebx, %%ebx\n\t"
      "je .LFUN_000ec840_43\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x34(%%eax), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .LFUN_000ec840_1\n\t"
      "pushl $1\n\t"
      "pushl $0xa30\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x2878a8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000ec840_1:\n\t"
      "movl 0x34(%%edi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_000ec840_3\n\t"
      ".LFUN_000ec840_2:\n\t"
      "cmpw $2, 0xe(%%esi)\n\t"
      "je .LFUN_000ec840_4\n\t"
      "movl 0x2c(%%esi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LFUN_000ec840_2\n\t"
      ".LFUN_000ec840_3:\n\t"
      "pushl $1\n\t"
      "pushl $0xa32\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x287874\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000ec840_4:\n\t"
      "movswl 0x3c(%%esi), %%eax\n\t"
      "subl $0, %%eax\n\t"
      "je .LFUN_000ec840_6\n\t"
      "decl %%eax\n\t"
      "je .LFUN_000ec840_5\n\t"
      "pushl $0x287830\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "jmp .LFUN_000ec840_8\n\t"
      ".LFUN_000ec840_5:\n\t"
      "movl 0x20(%%ebx), %%eax\n\t"
      "andl $0xfffffffb, %%eax\n\t"
      "jmp .LFUN_000ec840_7\n\t"
      ".LFUN_000ec840_6:\n\t"
      "movl 0x20(%%ebx), %%eax\n\t"
      "orl $4, %%eax\n\t"
      ".LFUN_000ec840_7:\n\t"
      "movl %%eax, 0x20(%%ebx)\n\t"
      ".LFUN_000ec840_8:\n\t"
      "movl 0x2c(%%edi), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .LFUN_000ec840_9\n\t"
      "pushl $1\n\t"
      "pushl $0xa3b\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x28780c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000ec840_9:\n\t"
      "movl 0x34(%%edi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_000ec840_11\n\t"
      "movl $2, %%eax\n\t"
      ".LFUN_000ec840_10:\n\t"
      "cmpw %%ax, 0xe(%%esi)\n\t"
      "je .LFUN_000ec840_12\n\t"
      "movl 0x2c(%%esi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LFUN_000ec840_10\n\t"
      ".LFUN_000ec840_11:\n\t"
      "pushl $1\n\t"
      "pushl $0xa3d\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x2877e0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000ec840_12:\n\t"
      "movswl 0x3c(%%esi), %%eax\n\t"
      "cmpl $4, %%eax\n\t"
      "ja .LFUN_000ec840_18\n\t"
      "jmp *.LFUN_000ec840_jt0(,%%eax,4)\n\t"
      ".LFUN_000ec840_13:\n\t"
      "movl $0, 0x48(%%ebx)\n\t"
      "jmp .LFUN_000ec840_19\n\t"
      ".LFUN_000ec840_14:\n\t"
      "movl $1, 0x48(%%ebx)\n\t"
      "jmp .LFUN_000ec840_19\n\t"
      ".LFUN_000ec840_15:\n\t"
      "movl $2, 0x48(%%ebx)\n\t"
      "jmp .LFUN_000ec840_19\n\t"
      ".LFUN_000ec840_16:\n\t"
      "movl $3, 0x48(%%ebx)\n\t"
      "jmp .LFUN_000ec840_19\n\t"
      ".LFUN_000ec840_17:\n\t"
      "movl $4, 0x48(%%ebx)\n\t"
      "jmp .LFUN_000ec840_19\n\t"
      ".LFUN_000ec840_18:\n\t"
      "pushl $0x2877a0\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_000ec840_19:\n\t"
      "movl 0x2c(%%edi), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .LFUN_000ec840_20\n\t"
      "pushl $1\n\t"
      "pushl $0xa49\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x287784\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000ec840_20:\n\t"
      "movl 0x34(%%edi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_000ec840_22\n\t"
      "movl $2, %%eax\n\t"
      ".LFUN_000ec840_21:\n\t"
      "cmpw %%ax, 0xe(%%esi)\n\t"
      "je .LFUN_000ec840_23\n\t"
      "movl 0x2c(%%esi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LFUN_000ec840_21\n\t"
      ".LFUN_000ec840_22:\n\t"
      "pushl $1\n\t"
      "pushl $0xa4b\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x287758\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000ec840_23:\n\t"
      "movswl 0x3c(%%esi), %%eax\n\t"
      "cmpl $0xa, %%eax\n\t"
      "ja .LFUN_000ec840_35\n\t"
      "jmp *.LFUN_000ec840_jt1(,%%eax,4)\n\t"
      ".LFUN_000ec840_24:\n\t"
      "movl $0, 0x44(%%ebx)\n\t"
      "jmp .LFUN_000ec840_36\n\t"
      ".LFUN_000ec840_25:\n\t"
      "movl $1, 0x44(%%ebx)\n\t"
      "jmp .LFUN_000ec840_36\n\t"
      ".LFUN_000ec840_26:\n\t"
      "movl $2, 0x44(%%ebx)\n\t"
      "jmp .LFUN_000ec840_36\n\t"
      ".LFUN_000ec840_27:\n\t"
      "movl $3, 0x44(%%ebx)\n\t"
      "jmp .LFUN_000ec840_36\n\t"
      ".LFUN_000ec840_28:\n\t"
      "movl $4, 0x44(%%ebx)\n\t"
      "jmp .LFUN_000ec840_36\n\t"
      ".LFUN_000ec840_29:\n\t"
      "movl $5, 0x44(%%ebx)\n\t"
      "jmp .LFUN_000ec840_36\n\t"
      ".LFUN_000ec840_30:\n\t"
      "movl $6, 0x44(%%ebx)\n\t"
      "jmp .LFUN_000ec840_36\n\t"
      ".LFUN_000ec840_31:\n\t"
      "movl $7, 0x44(%%ebx)\n\t"
      "jmp .LFUN_000ec840_36\n\t"
      ".LFUN_000ec840_32:\n\t"
      "movl $8, 0x44(%%ebx)\n\t"
      "jmp .LFUN_000ec840_36\n\t"
      ".LFUN_000ec840_33:\n\t"
      "movl $9, 0x44(%%ebx)\n\t"
      "jmp .LFUN_000ec840_36\n\t"
      ".LFUN_000ec840_34:\n\t"
      "movl $0xa, 0x44(%%ebx)\n\t"
      "jmp .LFUN_000ec840_36\n\t"
      ".LFUN_000ec840_35:\n\t"
      "pushl $0x28771c\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_000ec840_36:\n\t"
      "movl 0x2c(%%edi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LFUN_000ec840_37\n\t"
      "pushl $1\n\t"
      "pushl $0xa5e\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x2876f8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000ec840_37:\n\t"
      "movl 0x34(%%esi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_000ec840_39\n\t"
      "movl $2, %%eax\n\t"
      ".LFUN_000ec840_38:\n\t"
      "cmpw %%ax, 0xe(%%esi)\n\t"
      "je .LFUN_000ec840_40\n\t"
      "movl 0x2c(%%esi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LFUN_000ec840_38\n\t"
      ".LFUN_000ec840_39:\n\t"
      "pushl $1\n\t"
      "pushl $0xa60\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x2876c4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000ec840_40:\n\t"
      "movswl 0x3c(%%esi), %%eax\n\t"
      "subl $0, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "je .LFUN_000ec840_42\n\t"
      "decl %%eax\n\t"
      "je .LFUN_000ec840_41\n\t"
      "pushl $0x287680\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000ec840_41:\n\t"
      "orl $0x20, 0x20(%%ebx)\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000ec840_42:\n\t"
      "andl $0xffffffdf, 0x20(%%ebx)\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000ec840_43:\n\t"
      "pushl $0x286550\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_000ec840_jt0:\n\t"
      ".long .LFUN_000ec840_13\n\t"
      ".long .LFUN_000ec840_14\n\t"
      ".long .LFUN_000ec840_15\n\t"
      ".long .LFUN_000ec840_16\n\t"
      ".long .LFUN_000ec840_17\n\t"
      ".text\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_000ec840_jt1:\n\t"
      ".long .LFUN_000ec840_24\n\t"
      ".long .LFUN_000ec840_25\n\t"
      ".long .LFUN_000ec840_26\n\t"
      ".long .LFUN_000ec840_27\n\t"
      ".long .LFUN_000ec840_28\n\t"
      ".long .LFUN_000ec840_29\n\t"
      ".long .LFUN_000ec840_30\n\t"
      ".long .LFUN_000ec840_31\n\t"
      ".long .LFUN_000ec840_32\n\t"
      ".long .LFUN_000ec840_33\n\t"
      ".long .LFUN_000ec840_34\n\t"
      ".text\n\t"
      :
      : [ce0ec0] "m"(bec840_ce0ec0), [assert] "m"(bec840_assert), [exitfn] "m"(bec840_exitfn), [c8f390] "m"(bec840_c8f390)
      : "memory");
}
#else
#error "FUN_000ec840: clang naked draft required"
#endif


/* FUN_000ecb60 (0xecb60) — XBE naked draft (batch 117). */
#if defined(__clang__)
static void *(*const becb60_ce0ec0)(void) = (void *)player_ui_get_edit_playlist_profile;
static void (*const becb60_assert)(const char *, const char *, int, bool) = (void *)display_assert;
static void (*const becb60_exitfn)(int) = (void *)system_exit;
static void (*const becb60_c8f390)(unsigned __int16 a1, const char *a2, ...) = (void *)error;

__attribute__((naked, noinline))
char FUN_000ecb60(void *widget)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ebx\n\t"
      "call *%[ce0ec0]\n\t"
      "movl %%eax, %%ebx\n\t"
      "testl %%ebx, %%ebx\n\t"
      "je .LFUN_000ecb60_23\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x34(%%eax), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .LFUN_000ecb60_1\n\t"
      "pushl $1\n\t"
      "pushl $0xa80\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x287a8c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000ecb60_1:\n\t"
      "movl 0x34(%%edi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_000ecb60_3\n\t"
      ".LFUN_000ecb60_2:\n\t"
      "cmpw $2, 0xe(%%esi)\n\t"
      "je .LFUN_000ecb60_4\n\t"
      "movl 0x2c(%%esi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LFUN_000ecb60_2\n\t"
      ".LFUN_000ecb60_3:\n\t"
      "pushl $1\n\t"
      "pushl $0xa82\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x287a5c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000ecb60_4:\n\t"
      "movswl 0x3c(%%esi), %%eax\n\t"
      "subl $0, %%eax\n\t"
      "je .LFUN_000ecb60_7\n\t"
      "decl %%eax\n\t"
      "je .LFUN_000ecb60_6\n\t"
      "decl %%eax\n\t"
      "je .LFUN_000ecb60_5\n\t"
      "pushl $0x287a1c\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "jmp .LFUN_000ecb60_8\n\t"
      ".LFUN_000ecb60_5:\n\t"
      "movl $2, 0x24(%%ebx)\n\t"
      "jmp .LFUN_000ecb60_8\n\t"
      ".LFUN_000ecb60_6:\n\t"
      "movl $1, 0x24(%%ebx)\n\t"
      "jmp .LFUN_000ecb60_8\n\t"
      ".LFUN_000ecb60_7:\n\t"
      "movl $0, 0x24(%%ebx)\n\t"
      ".LFUN_000ecb60_8:\n\t"
      "movl 0x2c(%%edi), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .LFUN_000ecb60_9\n\t"
      "pushl $1\n\t"
      "pushl $0xa8c\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x2879f0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000ecb60_9:\n\t"
      "movl 0x34(%%edi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_000ecb60_11\n\t"
      "movl $2, %%eax\n\t"
      ".LFUN_000ecb60_10:\n\t"
      "cmpw %%ax, 0xe(%%esi)\n\t"
      "je .LFUN_000ecb60_12\n\t"
      "movl 0x2c(%%esi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LFUN_000ecb60_10\n\t"
      ".LFUN_000ecb60_11:\n\t"
      "pushl $1\n\t"
      "pushl $0xa8e\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x2879b8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000ecb60_12:\n\t"
      "movswl 0x3c(%%esi), %%eax\n\t"
      "subl $0, %%eax\n\t"
      "je .LFUN_000ecb60_14\n\t"
      "decl %%eax\n\t"
      "je .LFUN_000ecb60_13\n\t"
      "pushl $0x287970\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "jmp .LFUN_000ecb60_16\n\t"
      ".LFUN_000ecb60_13:\n\t"
      "movl 0x20(%%ebx), %%eax\n\t"
      "andl $0xfffffffe, %%eax\n\t"
      "jmp .LFUN_000ecb60_15\n\t"
      ".LFUN_000ecb60_14:\n\t"
      "movl 0x20(%%ebx), %%eax\n\t"
      "orl $1, %%eax\n\t"
      ".LFUN_000ecb60_15:\n\t"
      "movl %%eax, 0x20(%%ebx)\n\t"
      ".LFUN_000ecb60_16:\n\t"
      "movl 0x2c(%%edi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LFUN_000ecb60_17\n\t"
      "pushl $1\n\t"
      "pushl $0xa97\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x287948\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000ecb60_17:\n\t"
      "movl 0x34(%%esi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_000ecb60_19\n\t"
      "movl $2, %%eax\n\t"
      "movl %%edi, %%edi\n\t"
      ".LFUN_000ecb60_18:\n\t"
      "cmpw %%ax, 0xe(%%esi)\n\t"
      "je .LFUN_000ecb60_20\n\t"
      "movl 0x2c(%%esi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LFUN_000ecb60_18\n\t"
      ".LFUN_000ecb60_19:\n\t"
      "pushl $1\n\t"
      "pushl $0xa99\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x287914\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000ecb60_20:\n\t"
      "movswl 0x3c(%%esi), %%eax\n\t"
      "subl $0, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "je .LFUN_000ecb60_22\n\t"
      "decl %%eax\n\t"
      "je .LFUN_000ecb60_21\n\t"
      "pushl $0x2878d0\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000ecb60_21:\n\t"
      "andl $0xfffffffd, 0x20(%%ebx)\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000ecb60_22:\n\t"
      "orl $2, 0x20(%%ebx)\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000ecb60_23:\n\t"
      "pushl $0x286550\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [ce0ec0] "m"(becb60_ce0ec0), [assert] "m"(becb60_assert), [exitfn] "m"(becb60_exitfn), [c8f390] "m"(becb60_c8f390)
      : "memory");
}
#else
#error "FUN_000ecb60: clang naked draft required"
#endif

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



/* ui_widget_pending_load_apply (0xe5090) — XBE naked draft (batch 239). */
#if defined(__clang__)
static int * (*const be5090_ce4910)(int *widget, int tag_handle) = (void *)ui_widget_find_by_tag;
static void *(*const be5090_tag)(int, int) = (void *)tag_get;
static void (*const be5090_ce4f20)(void *root_widget, void *target_widget) = (void *)ui_widget_apply_focus;
static char (*const be5090_ce4980)(void *widget) = (void *)widget_instance_is_visible_in_parent_chain;

__attribute__((naked, noinline))
void ui_widget_pending_load_apply(int a6, int widget, int16_t a7)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lui_widget_pending_load_apply_4\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "call *%[ce4910]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $8, %%esp\n\t"
      "testl %%esi, %%esi\n\t"
      "je .Lui_widget_pending_load_apply_3\n\t"
      "cmpw $0, 0xc(%%ebp)\n\t"
      "jl .Lui_widget_pending_load_apply_7\n\t"
      "movl 0x34(%%esi), %%esi\n\t"
      "xorl %%edi, %%edi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .Lui_widget_pending_load_apply_3\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".Lui_widget_pending_load_apply_1:\n\t"
      "cmpw $2, 0xe(%%esi)\n\t"
      "jne .Lui_widget_pending_load_apply_2\n\t"
      "movl (%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x44654c61\n\t"
      "call *%[tag]\n\t"
      "movl 0x3e0(%%eax), %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $1, %%ecx\n\t"
      "jg .Lui_widget_pending_load_apply_3\n\t"
      ".Lui_widget_pending_load_apply_2:\n\t"
      "movswl 0xc(%%ebp), %%ecx\n\t"
      "cmpl %%ecx, %%edi\n\t"
      "je .Lui_widget_pending_load_apply_5\n\t"
      "movl 0x2c(%%esi), %%esi\n\t"
      "incl %%edi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .Lui_widget_pending_load_apply_1\n\t"
      ".Lui_widget_pending_load_apply_3:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      ".Lui_widget_pending_load_apply_4:\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lui_widget_pending_load_apply_5:\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl %%esi, %%ecx\n\t"
      "call *%[ce4f20]\n\t"
      "movl 0x30(%%esi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .Lui_widget_pending_load_apply_3\n\t"
      "movw 0xe(%%esi), %%ax\n\t"
      "cmpw $2, %%ax\n\t"
      "je .Lui_widget_pending_load_apply_6\n\t"
      "cmpw $3, %%ax\n\t"
      "jne .Lui_widget_pending_load_apply_3\n\t"
      ".Lui_widget_pending_load_apply_6:\n\t"
      "movw %%di, 0x3c(%%esi)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lui_widget_pending_load_apply_7:\n\t"
      "movl %%esi, %%eax\n\t"
      "call *%[ce4980]\n\t"
      "testb %%al, %%al\n\t"
      "je .Lui_widget_pending_load_apply_3\n\t"
      "cmpw $2, 0xe(%%esi)\n\t"
      "jne .Lui_widget_pending_load_apply_8\n\t"
      "movl (%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x44654c61\n\t"
      "call *%[tag]\n\t"
      "movl 0x3e0(%%eax), %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $1, %%ecx\n\t"
      "jg .Lui_widget_pending_load_apply_3\n\t"
      ".Lui_widget_pending_load_apply_8:\n\t"
      "movl %%edi, %%eax\n\t"
      "popl %%edi\n\t"
      "movl %%esi, %%ecx\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      ".byte 0xe9, 0xc8, 0xfd, 0xff, 0xff\n\t"
      :
      : [ce4910] "m"(be5090_ce4910), [tag] "m"(be5090_tag), [ce4f20] "m"(be5090_ce4f20), [ce4980] "m"(be5090_ce4980)
      : "memory");
}
#else
#error "ui_widget_pending_load_apply: clang naked draft required"
#endif


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
void ui_widget_list_prev(void *widget)
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




/* ui_widget_list_next (0xe5440) — XBE naked draft (batch 141). */
#if defined(__clang__)
static void *(*const be5440_tag)(int, int) = (void *)tag_get;

__attribute__((naked, noinline))
void ui_widget_list_next(void *widget)
{
  __asm__ volatile(
      "movl 0x38(%%edi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "pushl %%esi\n\t"
      "je .Lui_widget_list_next_2\n\t"
      "movl 0x28(%%eax), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lui_widget_list_next_3\n\t"
      "movl 0x34(%%edi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .Lui_widget_list_next_9\n\t"
      "movl 0x2c(%%esi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lui_widget_list_next_4\n\t"
      ".Lui_widget_list_next_1:\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x2c(%%esi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lui_widget_list_next_1\n\t"
      "jmp .Lui_widget_list_next_4\n\t"
      ".Lui_widget_list_next_2:\n\t"
      "movl 0x34(%%edi), %%eax\n\t"
      "movl 0x28(%%eax), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .Lui_widget_list_next_5\n\t"
      ".Lui_widget_list_next_3:\n\t"
      "movl %%eax, %%esi\n\t"
      ".Lui_widget_list_next_4:\n\t"
      "testl %%esi, %%esi\n\t"
      "je .Lui_widget_list_next_9\n\t"
      "leal (%%esp), %%esp\n\t"
      ".Lui_widget_list_next_5:\n\t"
      "cmpl 0x38(%%edi), %%esi\n\t"
      "je .Lui_widget_list_next_9\n\t"
      "movl (%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x44654c61\n\t"
      "call *%[tag]\n\t"
      "movl 0x54(%%eax), %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "testl %%ecx, %%ecx\n\t"
      "jg .Lui_widget_list_next_8\n\t"
      "testb $1, 0x2c(%%eax)\n\t"
      "jne .Lui_widget_list_next_8\n\t"
      "movw 0xe(%%edi), %%ax\n\t"
      "cmpw $2, %%ax\n\t"
      "je .Lui_widget_list_next_8\n\t"
      "cmpw $3, %%ax\n\t"
      "je .Lui_widget_list_next_8\n\t"
      "movl 0x28(%%esi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .Lui_widget_list_next_5\n\t"
      "movl 0x34(%%edi), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .Lui_widget_list_next_7\n\t"
      "movl 0x2c(%%ecx), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lui_widget_list_next_7\n\t"
      ".Lui_widget_list_next_6:\n\t"
      "movl %%eax, %%ecx\n\t"
      "movl 0x2c(%%ecx), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lui_widget_list_next_6\n\t"
      ".Lui_widget_list_next_7:\n\t"
      "movl %%ecx, %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .Lui_widget_list_next_5\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      ".Lui_widget_list_next_8:\n\t"
      "movl %%esi, 0x38(%%edi)\n\t"
      ".Lui_widget_list_next_9:\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      :
      : [tag] "m"(be5440_tag)
      : "memory");
}
#else
#error "ui_widget_list_next: clang naked draft required"
#endif


/* ui_widget_close_and_reload (0xe68e0) — XBE naked draft (batch 142). */
#if defined(__clang__)
static void (*const be68e0_ce4770)(int *head, void *record) = (void *)ui_widget_pending_load_pop;
static void (*const be68e0_ce5620)(void *widget) = (void *)ui_widget_close;
static void * (*const be68e0_ce84e0)(const char *name, int tag_index, int is_child, int widget_stack, int parent_tag_index, int a6, int a7) = (void *)ui_widget_load_by_name_or_tag;
static void (*const be68e0_ce5090)(int a6, int widget, int16_t a7) = (void *)ui_widget_pending_load_apply;

__attribute__((naked, noinline))
void ui_widget_close_and_reload(void *widget)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x10, %%esp\n\t"
      "pushl %%ebx\n\t"
      "movl %%eax, %%ebx\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x8(%%ebx), %%ax\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "sete %%cl\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "orl $0xffffffff, %%esi\n\t"
      "decl %%ecx\n\t"
      "andl %%ecx, %%eax\n\t"
      "movswl %%ax, %%eax\n\t"
      "leal 0x46cc30(,%%eax,4), %%edi\n\t"
      "cmpl $0, (%%edi)\n\t"
      "je .Lui_widget_close_and_reload_1\n\t"
      "leal -0x10(%%ebp), %%esi\n\t"
      "call *%[ce4770]\n\t"
      "movl -0x6(%%ebp), %%esi\n\t"
      "movl -0x10(%%ebp), %%edi\n\t"
      "jmp .Lui_widget_close_and_reload_2\n\t"
      ".Lui_widget_close_and_reload_1:\n\t"
      "orl $0xffffffff, %%edi\n\t"
      ".Lui_widget_close_and_reload_2:\n\t"
      "movl %%ebx, %%ecx\n\t"
      "movl 0x30(%%ebx), %%ebx\n\t"
      "testl %%ebx, %%ebx\n\t"
      "je .Lui_widget_close_and_reload_4\n\t"
      "movl %%ebx, %%eax\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".Lui_widget_close_and_reload_3:\n\t"
      "movl %%eax, %%ecx\n\t"
      "movl 0x30(%%ecx), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lui_widget_close_and_reload_3\n\t"
      ".Lui_widget_close_and_reload_4:\n\t"
      "pushl %%ecx\n\t"
      "call *%[ce5620]\n\t"
      "addl $4, %%esp\n\t"
      "cmpl $-1, %%edi\n\t"
      "je .Lui_widget_close_and_reload_5\n\t"
      "pushl $-1\n\t"
      "pushl $-1\n\t"
      "pushl $-1\n\t"
      "pushl %%esi\n\t"
      "pushl $0\n\t"
      "pushl %%edi\n\t"
      "pushl $0\n\t"
      "call *%[ce84e0]\n\t"
      "addl $0x1c, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lui_widget_close_and_reload_5\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "call *%[ce5090]\n\t"
      "addl $8, %%esp\n\t"
      ".Lui_widget_close_and_reload_5:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [ce4770] "m"(be68e0_ce4770), [ce5620] "m"(be68e0_ce5620), [ce84e0] "m"(be68e0_ce84e0), [ce5090] "m"(be68e0_ce5090)
      : "memory");
}
#else
#error "ui_widget_close_and_reload: clang naked draft required"
#endif


/* ui_widget_list_next_item (0xe6ab0) — XBE naked draft (batch 115). */
#if defined(__clang__)
static void (*const be6ab0_assert)(const char *, const char *, int, bool) = (void *)display_assert;
static void (*const be6ab0_exitfn)(int) = (void *)system_exit;
static void *(*const be6ab0_tag)(int, int) = (void *)tag_get;
static void * (*const be6ab0_ce3cd0)(void *widget, int index) = (void *)widget_instance_get_nth_child;
static void (*const be6ab0_c8f390)(unsigned __int16 a1, const char *a2, ...) = (void *)error;
static void (*const be6ab0_ce4f20)(void *root_widget, void *target_widget) = (void *)ui_widget_apply_focus;
static void (*const be6ab0_ce6890)(void *widget, int tag_handle, int16_t player_index) = (void *)ui_widget_set_focus;

__attribute__((naked, noinline))
int ui_widget_list_next_item(void *widget, void *event_data, char *widget_deleted)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "pushl %%edi\n\t"
      "jne .Lui_widget_list_next_item_1\n\t"
      "pushl $1\n\t"
      "pushl $0x4ce\n\t"
      "pushl $0x283280\n\t"
      "pushl $0x2832a8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lui_widget_list_next_item_1:\n\t"
      "movl (%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x44654c61\n\t"
      "call *%[tag]\n\t"
      "movl %%eax, %%ebx\n\t"
      "movw 0xe(%%esi), %%ax\n\t"
      "movl $2, %%edi\n\t"
      "addl $8, %%esp\n\t"
      "cmpw %%di, %%ax\n\t"
      "je .Lui_widget_list_next_item_2\n\t"
      "cmpw $3, %%ax\n\t"
      "je .Lui_widget_list_next_item_2\n\t"
      "pushl $1\n\t"
      "pushl $0x4d1\n\t"
      "pushl $0x283280\n\t"
      "pushl $0x283d14\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lui_widget_list_next_item_2:\n\t"
      "movl 0x40(%%esi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lui_widget_list_next_item_9\n\t"
      "movw 0x44(%%esi), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "jbe .Lui_widget_list_next_item_9\n\t"
      "movswl 0x3c(%%esi), %%edi\n\t"
      "movzwl %%ax, %%ecx\n\t"
      "incl %%edi\n\t"
      "cmpl %%ecx, %%edi\n\t"
      "jl .Lui_widget_list_next_item_3\n\t"
      "xorl %%edi, %%edi\n\t"
      ".Lui_widget_list_next_item_3:\n\t"
      "movw 0xe(%%esi), %%ax\n\t"
      "cmpw $3, %%ax\n\t"
      "jne .Lui_widget_list_next_item_4\n\t"
      "pushl %%edi\n\t"
      "pushl %%esi\n\t"
      "call *%[ce3cd0]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lui_widget_list_next_item_13\n\t"
      "pushl %%edi\n\t"
      "pushl $0x283cd0\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $0xc, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lui_widget_list_next_item_4:\n\t"
      "cmpw $2, %%ax\n\t"
      "jne .Lui_widget_list_next_item_8\n\t"
      "movl 0x3e0(%%ebx), %%eax\n\t"
      "cmpl $1, %%eax\n\t"
      "jle .Lui_widget_list_next_item_7\n\t"
      "cmpl $3, %%eax\n\t"
      "je .Lui_widget_list_next_item_5\n\t"
      "pushl $1\n\t"
      "pushl $0x4f4\n\t"
      "pushl $0x283280\n\t"
      "pushl $0x283c98\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lui_widget_list_next_item_5:\n\t"
      "movl 0x38(%%esi), %%eax\n\t"
      "movl 0x34(%%esi), %%ecx\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "je .Lui_widget_list_next_item_6\n\t"
      "cmpl 0x2c(%%ecx), %%eax\n\t"
      "jne .Lui_widget_list_next_item_7\n\t"
      ".Lui_widget_list_next_item_6:\n\t"
      "movl 0x2c(%%eax), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lui_widget_list_next_item_7\n\t"
      "movl %%eax, %%ecx\n\t"
      "movl %%esi, %%eax\n\t"
      "call *%[ce4f20]\n\t"
      ".Lui_widget_list_next_item_7:\n\t"
      "movw %%di, 0x3c(%%esi)\n\t"
      ".Lui_widget_list_next_item_8:\n\t"
      "popl %%edi\n\t"
      "movw $0xf, 0x3e(%%esi)\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lui_widget_list_next_item_9:\n\t"
      "cmpw %%di, 0xe(%%esi)\n\t"
      "jne .Lui_widget_list_next_item_11\n\t"
      "cmpl $1, 0x3e0(%%ebx)\n\t"
      "jle .Lui_widget_list_next_item_10\n\t"
      "pushl $1\n\t"
      "pushl $0x508\n\t"
      "pushl $0x283280\n\t"
      "pushl $0x283c28\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lui_widget_list_next_item_10:\n\t"
      "cmpw %%di, 0xe(%%esi)\n\t"
      "jne .Lui_widget_list_next_item_11\n\t"
      "testb $2, 0x150(%%ebx)\n\t"
      "je .Lui_widget_list_next_item_11\n\t"
      "movl 0x3e0(%%ebx), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lui_widget_list_next_item_11\n\t"
      "incw 0x3c(%%esi)\n\t"
      "movw 0x3c(%%esi), %%ax\n\t"
      "movzwl 0x44(%%esi), %%ecx\n\t"
      "movswl %%ax, %%edx\n\t"
      "cmpl %%ecx, %%edx\n\t"
      "jne .Lui_widget_list_next_item_8\n\t"
      "popl %%edi\n\t"
      "movw $0, 0x3c(%%esi)\n\t"
      "movw $0xf, 0x3e(%%esi)\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lui_widget_list_next_item_11:\n\t"
      "movl 0x38(%%esi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lui_widget_list_next_item_12\n\t"
      "movswl 0x3c(%%esi), %%edi\n\t"
      "movzwl 0x44(%%esi), %%ecx\n\t"
      "movl 0x2c(%%eax), %%eax\n\t"
      "incl %%edi\n\t"
      "cmpl %%ecx, %%edi\n\t"
      "je .Lui_widget_list_next_item_12\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lui_widget_list_next_item_13\n\t"
      ".Lui_widget_list_next_item_12:\n\t"
      "movl 0x34(%%esi), %%eax\n\t"
      "xorl %%edi, %%edi\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lui_widget_list_next_item_14\n\t"
      ".Lui_widget_list_next_item_13:\n\t"
      "movl (%%eax), %%eax\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x8(%%esi), %%dx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "movl %%esi, %%eax\n\t"
      "call *%[ce6890]\n\t"
      "addl $8, %%esp\n\t"
      "movw %%di, 0x3c(%%esi)\n\t"
      "popl %%edi\n\t"
      "movw $0xf, 0x3e(%%esi)\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lui_widget_list_next_item_14:\n\t"
      "pushl $0x283be8\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(be6ab0_assert), [exitfn] "m"(be6ab0_exitfn), [tag] "m"(be6ab0_tag), [ce3cd0] "m"(be6ab0_ce3cd0), [c8f390] "m"(be6ab0_c8f390), [ce4f20] "m"(be6ab0_ce4f20), [ce6890] "m"(be6ab0_ce6890)
      : "memory");
}
#else
#error "ui_widget_list_next_item: clang naked draft required"
#endif


/* ui_widget_list_prev_item (0xe6cb0) — XBE naked draft (batch 115). */
#if defined(__clang__)
static void (*const be6cb0_assert)(const char *, const char *, int, bool) = (void *)display_assert;
static void (*const be6cb0_exitfn)(int) = (void *)system_exit;
static void *(*const be6cb0_tag)(int, int) = (void *)tag_get;
static void * (*const be6cb0_ce3cd0)(void *widget, int index) = (void *)widget_instance_get_nth_child;
static void (*const be6cb0_c8f390)(unsigned __int16 a1, const char *a2, ...) = (void *)error;
static void (*const be6cb0_ce4f20)(void *root_widget, void *target_widget) = (void *)ui_widget_apply_focus;
static void (*const be6cb0_ce6890)(void *widget, int tag_handle, int16_t player_index) = (void *)ui_widget_set_focus;

__attribute__((naked, noinline))
int ui_widget_list_prev_item(void *widget, void *event_data, char *widget_deleted)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "pushl %%edi\n\t"
      "jne .Lui_widget_list_prev_item_1\n\t"
      "pushl $1\n\t"
      "pushl $0x54f\n\t"
      "pushl $0x283280\n\t"
      "pushl $0x2832a8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lui_widget_list_prev_item_1:\n\t"
      "movl (%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x44654c61\n\t"
      "call *%[tag]\n\t"
      "movl %%eax, %%ebx\n\t"
      "movw 0xe(%%esi), %%ax\n\t"
      "movl $2, %%edi\n\t"
      "addl $8, %%esp\n\t"
      "cmpw %%di, %%ax\n\t"
      "je .Lui_widget_list_prev_item_2\n\t"
      "cmpw $3, %%ax\n\t"
      "je .Lui_widget_list_prev_item_2\n\t"
      "pushl $1\n\t"
      "pushl $0x552\n\t"
      "pushl $0x283280\n\t"
      "pushl $0x283d14\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lui_widget_list_prev_item_2:\n\t"
      "movl 0x40(%%esi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lui_widget_list_prev_item_8\n\t"
      "movw 0x44(%%esi), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "jbe .Lui_widget_list_prev_item_8\n\t"
      "movswl 0x3c(%%esi), %%edi\n\t"
      "decl %%edi\n\t"
      "jns .Lui_widget_list_prev_item_3\n\t"
      "movzwl %%ax, %%edi\n\t"
      "decl %%edi\n\t"
      ".Lui_widget_list_prev_item_3:\n\t"
      "movw 0xe(%%esi), %%ax\n\t"
      "cmpw $3, %%ax\n\t"
      "jne .Lui_widget_list_prev_item_5\n\t"
      "pushl %%edi\n\t"
      "pushl %%esi\n\t"
      "call *%[ce3cd0]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lui_widget_list_prev_item_4\n\t"
      "movl (%%eax), %%edx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x8(%%esi), %%cx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "jmp .Lui_widget_list_prev_item_14\n\t"
      ".Lui_widget_list_prev_item_4:\n\t"
      "pushl %%edi\n\t"
      "pushl $0x283cd0\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $0xc, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lui_widget_list_prev_item_5:\n\t"
      "cmpw $2, %%ax\n\t"
      "jne .Lui_widget_list_prev_item_16\n\t"
      "movl 0x3e0(%%ebx), %%eax\n\t"
      "cmpl $1, %%eax\n\t"
      "jle .Lui_widget_list_prev_item_15\n\t"
      "cmpl $3, %%eax\n\t"
      "je .Lui_widget_list_prev_item_6\n\t"
      "pushl $1\n\t"
      "pushl $0x574\n\t"
      "pushl $0x283280\n\t"
      "pushl $0x283c98\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lui_widget_list_prev_item_6:\n\t"
      "movl 0x38(%%esi), %%eax\n\t"
      "cmpl 0x34(%%esi), %%eax\n\t"
      "je .Lui_widget_list_prev_item_15\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lui_widget_list_prev_item_7\n\t"
      "pushl $1\n\t"
      "pushl $0x57d\n\t"
      "pushl $0x283280\n\t"
      "pushl $0x283d48\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lui_widget_list_prev_item_7:\n\t"
      "movl 0x38(%%esi), %%eax\n\t"
      "movl 0x28(%%eax), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .Lui_widget_list_prev_item_15\n\t"
      "movl %%esi, %%eax\n\t"
      "call *%[ce4f20]\n\t"
      "movw %%di, 0x3c(%%esi)\n\t"
      "popl %%edi\n\t"
      "movw $0xfff1, 0x3e(%%esi)\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lui_widget_list_prev_item_8:\n\t"
      "cmpw %%di, 0xe(%%esi)\n\t"
      "jne .Lui_widget_list_prev_item_10\n\t"
      "cmpl $1, 0x3e0(%%ebx)\n\t"
      "jle .Lui_widget_list_prev_item_9\n\t"
      "pushl $1\n\t"
      "pushl $0x58c\n\t"
      "pushl $0x283280\n\t"
      "pushl $0x283c28\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lui_widget_list_prev_item_9:\n\t"
      "cmpw %%di, 0xe(%%esi)\n\t"
      "jne .Lui_widget_list_prev_item_10\n\t"
      "testb $2, 0x150(%%ebx)\n\t"
      "je .Lui_widget_list_prev_item_10\n\t"
      "movl 0x3e0(%%ebx), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lui_widget_list_prev_item_10\n\t"
      "decw 0x3c(%%esi)\n\t"
      "cmpw $0, 0x3c(%%esi)\n\t"
      "jge .Lui_widget_list_prev_item_16\n\t"
      "movw 0x44(%%esi), %%cx\n\t"
      "decw %%cx\n\t"
      "popl %%edi\n\t"
      "movw %%cx, 0x3c(%%esi)\n\t"
      "movw $0xfff1, 0x3e(%%esi)\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lui_widget_list_prev_item_10:\n\t"
      "movl 0x38(%%esi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lui_widget_list_prev_item_11\n\t"
      "movswl 0x3c(%%esi), %%edi\n\t"
      "movl 0x28(%%eax), %%eax\n\t"
      "decl %%edi\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lui_widget_list_prev_item_13\n\t"
      ".Lui_widget_list_prev_item_11:\n\t"
      "movl 0x34(%%esi), %%eax\n\t"
      "movl 0x2c(%%eax), %%ecx\n\t"
      "xorl %%edi, %%edi\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .Lui_widget_list_prev_item_13\n\t"
      ".Lui_widget_list_prev_item_12:\n\t"
      "movl %%ecx, %%eax\n\t"
      "movl 0x2c(%%eax), %%ecx\n\t"
      "incl %%edi\n\t"
      "testl %%ecx, %%ecx\n\t"
      "jne .Lui_widget_list_prev_item_12\n\t"
      ".Lui_widget_list_prev_item_13:\n\t"
      "movl (%%eax), %%eax\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x8(%%esi), %%dx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      ".Lui_widget_list_prev_item_14:\n\t"
      "movl %%esi, %%eax\n\t"
      "call *%[ce6890]\n\t"
      "addl $8, %%esp\n\t"
      ".Lui_widget_list_prev_item_15:\n\t"
      "movw %%di, 0x3c(%%esi)\n\t"
      ".Lui_widget_list_prev_item_16:\n\t"
      "popl %%edi\n\t"
      "movw $0xfff1, 0x3e(%%esi)\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(be6cb0_assert), [exitfn] "m"(be6cb0_exitfn), [tag] "m"(be6cb0_tag), [ce3cd0] "m"(be6cb0_ce3cd0), [c8f390] "m"(be6cb0_c8f390), [ce4f20] "m"(be6cb0_ce4f20), [ce6890] "m"(be6cb0_ce6890)
      : "memory");
}
#else
#error "ui_widget_list_prev_item: clang naked draft required"
#endif


/* ui_widget_handle_event_handler (0xe6ed0) — XBE naked draft (batch 106). */
#if defined(__clang__)
static char (*const be6ed0_cc4b00)(const char *name) = (void *)hs_evaluate_by_name;
static void (*const be6ed0_c8f390)(unsigned __int16 a1, const char *a2, ...) = (void *)error;
static bool (*const be6ed0_ce9810)(void *widget, int unknown, uint16_t handler_func_index, bool *widget_deleted) = (void *)ui_widget_event_handler_dispatch;
static void (*const be6ed0_ce6890)(void *widget, int tag_handle, int16_t player_index) = (void *)ui_widget_set_focus;
static int * (*const be6ed0_ce4910)(int *widget, int tag_handle) = (void *)ui_widget_find_by_tag;
static void (*const be6ed0_ce5620)(void *widget) = (void *)ui_widget_close;
static void * (*const be6ed0_ce9320)(void *widget, int tag_index) = (void *)ui_widget_spawn_from_event_handler;
static void * (*const be6ed0_ce84e0)(const char *name, int tag_index, int is_child, int widget_stack, int parent_tag_index, int a6, int a7) = (void *)ui_widget_load_by_name_or_tag;
static void (*const be6ed0_assert)(const char *, const char *, int, bool) = (void *)display_assert;
static void (*const be6ed0_exitfn)(int) = (void *)system_exit;
static void (*const be6ed0_ce68e0)(void *widget) = (void *)ui_widget_close_and_reload;
static int (*const be6ed0_c1c7480)(int sound_tag_index, float scale) = (void *)sound_impulse_start;
static void (*const be6ed0_c11f620)(void *pool, void *block) = (void *)stack_memory_pool_deallocate;
static int (*const be6ed0_c1b9930)(int group_tag, const char *name, ...) = (void *)tag_loaded;

__attribute__((naked, noinline))
void ui_widget_handle_event_handler(void *widget, void *definition, void *event_data, void *event_handler, char *widget_deleted)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xc, %%esp\n\t"
      "pushl %%ebx\n\t"
      "movl 0x14(%%ebp), %%ebx\n\t"
      "movl (%%ebx), %%eax\n\t"
      "testb $4, %%ah\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "movb $1, -0x2(%%ebp)\n\t"
      "movb $0, -0x6(%%ebp)\n\t"
      "movl $0, -0xc(%%ebp)\n\t"
      "movb $0, -0x5(%%ebp)\n\t"
      "movb $0, -0x3(%%ebp)\n\t"
      "movb $0, -0x4(%%ebp)\n\t"
      "je .Lui_widget_handle_event_handler_1\n\t"
      "movb 0x28(%%ebx), %%al\n\t"
      "testb %%al, %%al\n\t"
      "leal 0x28(%%ebx), %%esi\n\t"
      "je .Lui_widget_handle_event_handler_1\n\t"
      "pushl %%esi\n\t"
      "call *%[cc4b00]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lui_widget_handle_event_handler_1\n\t"
      "pushl %%esi\n\t"
      "pushl $0x283f58\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $0xc, %%esp\n\t"
      ".Lui_widget_handle_event_handler_1:\n\t"
      "cmpb $0, (%%ebx)\n\t"
      "jns .Lui_widget_handle_event_handler_2\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lui_widget_handle_event_handler_2\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x6(%%ebx), %%cx\n\t"
      "leal -0x1(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "call *%[ce9810]\n\t"
      "addl $0x10, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lui_widget_handle_event_handler_2\n\t"
      "pushl $0x283f38\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "movb $1, -0x6(%%ebp)\n\t"
      "jmp .Lui_widget_handle_event_handler_46\n\t"
      ".Lui_widget_handle_event_handler_2:\n\t"
      "testb $0x40, (%%ebx)\n\t"
      "je .Lui_widget_handle_event_handler_5\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lui_widget_handle_event_handler_5\n\t"
      "movl 0x14(%%ebx), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lui_widget_handle_event_handler_3\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x8(%%edi), %%cx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "movl %%edi, %%eax\n\t"
      "call *%[ce6890]\n\t"
      "movl $1, -0xc(%%ebp)\n\t"
      "jmp .Lui_widget_handle_event_handler_4\n\t"
      ".Lui_widget_handle_event_handler_3:\n\t"
      "pushl $0x283ee8\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "movb $0, -0x2(%%ebp)\n\t"
      ".Lui_widget_handle_event_handler_4:\n\t"
      "addl $8, %%esp\n\t"
      ".Lui_widget_handle_event_handler_5:\n\t"
      "testb $0x20, (%%ebx)\n\t"
      "je .Lui_widget_handle_event_handler_6\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lui_widget_handle_event_handler_6\n\t"
      "cmpl $-1, 0x14(%%ebx)\n\t"
      "jne .Lui_widget_handle_event_handler_6\n\t"
      "pushl $0x283ea0\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "movb $0, -0x2(%%ebp)\n\t"
      ".Lui_widget_handle_event_handler_6:\n\t"
      "movl (%%ebx), %%eax\n\t"
      "testb $1, %%al\n\t"
      "je .Lui_widget_handle_event_handler_7\n\t"
      "movb -0x1(%%ebp), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "jne .Lui_widget_handle_event_handler_7\n\t"
      "movb $1, -0x5(%%ebp)\n\t"
      ".Lui_widget_handle_event_handler_7:\n\t"
      "testb $2, %%al\n\t"
      "je .Lui_widget_handle_event_handler_13\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lui_widget_handle_event_handler_13\n\t"
      "movl 0x14(%%ebx), %%edi\n\t"
      "cmpl $-1, %%edi\n\t"
      "je .Lui_widget_handle_event_handler_13\n\t"
      "xorl %%eax, %%eax\n\t"
      "movl $0x46cc20, %%esi\n\t"
      "jmp .Lui_widget_handle_event_handler_8\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".Lui_widget_handle_event_handler_8:\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lui_widget_handle_event_handler_10\n\t"
      "movl (%%esi), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .Lui_widget_handle_event_handler_9\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "call *%[ce4910]\n\t"
      "addl $8, %%esp\n\t"
      ".Lui_widget_handle_event_handler_9:\n\t"
      "addl $4, %%esi\n\t"
      "cmpl $0x46cc30, %%esi\n\t"
      "jl .Lui_widget_handle_event_handler_8\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lui_widget_handle_event_handler_12\n\t"
      ".Lui_widget_handle_event_handler_10:\n\t"
      "cmpl 0x8(%%ebp), %%eax\n\t"
      "jne .Lui_widget_handle_event_handler_11\n\t"
      "movb $1, -0x3(%%ebp)\n\t"
      "jmp .Lui_widget_handle_event_handler_13\n\t"
      ".Lui_widget_handle_event_handler_11:\n\t"
      "pushl %%eax\n\t"
      "call *%[ce5620]\n\t"
      "addl $4, %%esp\n\t"
      "jmp .Lui_widget_handle_event_handler_13\n\t"
      ".Lui_widget_handle_event_handler_12:\n\t"
      "pushl $0x283e58\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "movb $0, -0x2(%%ebp)\n\t"
      ".Lui_widget_handle_event_handler_13:\n\t"
      "movl (%%ebx), %%eax\n\t"
      "testb $4, %%al\n\t"
      "je .Lui_widget_handle_event_handler_14\n\t"
      "movb -0x1(%%ebp), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "jne .Lui_widget_handle_event_handler_14\n\t"
      "movb $1, -0x4(%%ebp)\n\t"
      ".Lui_widget_handle_event_handler_14:\n\t"
      "testb $8, %%al\n\t"
      "je .Lui_widget_handle_event_handler_17\n\t"
      "movl 0x14(%%ebx), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lui_widget_handle_event_handler_17\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%edx\n\t"
      "call *%[ce9320]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lui_widget_handle_event_handler_15\n\t"
      "pushl $0x283728\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "movb $0, -0x2(%%ebp)\n\t"
      "jmp .Lui_widget_handle_event_handler_17\n\t"
      ".Lui_widget_handle_event_handler_15:\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lui_widget_handle_event_handler_16\n\t"
      "movl $2, -0xc(%%ebp)\n\t"
      ".Lui_widget_handle_event_handler_16:\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      ".Lui_widget_handle_event_handler_17:\n\t"
      "movl (%%ebx), %%eax\n\t"
      "testb $1, %%ah\n\t"
      "je .Lui_widget_handle_event_handler_30\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lui_widget_handle_event_handler_30\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "movl 0x14(%%eax), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lui_widget_handle_event_handler_30\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "pushl $-1\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x8(%%ecx), %%dx\n\t"
      "pushl $-1\n\t"
      "pushl $-1\n\t"
      "pushl %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl $0\n\t"
      "call *%[ce84e0]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $0x1c, %%esp\n\t"
      "testl %%esi, %%esi\n\t"
      "je .Lui_widget_handle_event_handler_29\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "movl 0x28(%%esi), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "movl 0x30(%%edx), %%eax\n\t"
      "movl 0x2c(%%edx), %%edi\n\t"
      "movl 0x28(%%edx), %%ebx\n\t"
      "je .Lui_widget_handle_event_handler_18\n\t"
      "movl $0, 0x2c(%%ecx)\n\t"
      ".Lui_widget_handle_event_handler_18:\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movl %%ecx, 0x28(%%esi)\n\t"
      "movl %%ecx, 0x30(%%esi)\n\t"
      "movw 0xa(%%edx), %%cx\n\t"
      "addw %%cx, 0xa(%%esi)\n\t"
      "movw 0xc(%%edx), %%cx\n\t"
      "addw %%cx, 0xc(%%esi)\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "je .Lui_widget_handle_event_handler_20\n\t"
      "movl %%eax, 0x30(%%esi)\n\t"
      "cmpl %%edx, 0x34(%%eax)\n\t"
      "jne .Lui_widget_handle_event_handler_19\n\t"
      "movl %%esi, 0x34(%%eax)\n\t"
      ".Lui_widget_handle_event_handler_19:\n\t"
      "cmpl %%edx, 0x38(%%eax)\n\t"
      "jne .Lui_widget_handle_event_handler_20\n\t"
      "movl %%esi, 0x38(%%eax)\n\t"
      ".Lui_widget_handle_event_handler_20:\n\t"
      "cmpl %%ecx, %%edi\n\t"
      "je .Lui_widget_handle_event_handler_22\n\t"
      "cmpl %%edx, 0x28(%%edi)\n\t"
      "je .Lui_widget_handle_event_handler_21\n\t"
      "pushl $1\n\t"
      "pushl $0xe89\n\t"
      "pushl $0x283280\n\t"
      "pushl $0x283e3c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "addl $0x14, %%esp\n\t"
      "xorl %%ecx, %%ecx\n\t"
      ".Lui_widget_handle_event_handler_21:\n\t"
      "movl %%esi, 0x28(%%edi)\n\t"
      ".Lui_widget_handle_event_handler_22:\n\t"
      "cmpl %%ecx, %%ebx\n\t"
      "movl %%edi, 0x2c(%%esi)\n\t"
      "je .Lui_widget_handle_event_handler_24\n\t"
      "cmpl %%edx, 0x2c(%%ebx)\n\t"
      "je .Lui_widget_handle_event_handler_23\n\t"
      "pushl $1\n\t"
      "pushl $0xe90\n\t"
      "pushl $0x283280\n\t"
      "pushl $0x283e20\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "addl $0x14, %%esp\n\t"
      "xorl %%ecx, %%ecx\n\t"
      ".Lui_widget_handle_event_handler_23:\n\t"
      "movl %%esi, 0x2c(%%ebx)\n\t"
      ".Lui_widget_handle_event_handler_24:\n\t"
      "movl %%ebx, 0x28(%%esi)\n\t"
      "xorl %%eax, %%eax\n\t"
      ".Lui_widget_handle_event_handler_25:\n\t"
      "cmpl %%esi, 0x46cc20(,%%eax,4)\n\t"
      "je .Lui_widget_handle_event_handler_26\n\t"
      "incl %%eax\n\t"
      "cmpl $4, %%eax\n\t"
      "jl .Lui_widget_handle_event_handler_25\n\t"
      "jmp .Lui_widget_handle_event_handler_27\n\t"
      ".Lui_widget_handle_event_handler_26:\n\t"
      "movl %%ecx, 0x46cc20(,%%eax,4)\n\t"
      ".Lui_widget_handle_event_handler_27:\n\t"
      "cmpl %%ecx, -0xc(%%ebp)\n\t"
      "jne .Lui_widget_handle_event_handler_28\n\t"
      "movl $2, -0xc(%%ebp)\n\t"
      ".Lui_widget_handle_event_handler_28:\n\t"
      "movl %%ecx, 0x28(%%edx)\n\t"
      "movl %%ecx, 0x2c(%%edx)\n\t"
      "movl %%ecx, 0x30(%%edx)\n\t"
      "movb $1, -0x3(%%ebp)\n\t"
      "jmp .Lui_widget_handle_event_handler_30\n\t"
      ".Lui_widget_handle_event_handler_29:\n\t"
      "pushl $0x283dd8\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "movb $0, -0x2(%%ebp)\n\t"
      ".Lui_widget_handle_event_handler_30:\n\t"
      "movl 0x14(%%ebp), %%edx\n\t"
      "movl (%%edx), %%eax\n\t"
      "testb $2, %%ah\n\t"
      "je .Lui_widget_handle_event_handler_32\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "call *%[ce68e0]\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lui_widget_handle_event_handler_31\n\t"
      "movl $3, -0xc(%%ebp)\n\t"
      ".Lui_widget_handle_event_handler_31:\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      ".Lui_widget_handle_event_handler_32:\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "movl 0x24(%%eax), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lui_widget_handle_event_handler_33\n\t"
      "pushl $0x3f800000\n\t"
      "pushl %%eax\n\t"
      "call *%[c1c7480]\n\t"
      "addl $8, %%esp\n\t"
      ".Lui_widget_handle_event_handler_33:\n\t"
      "movb -0x4(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lui_widget_handle_event_handler_39\n\t"
      "movl $0x46cc30, %%esi\n\t"
      ".Lui_widget_handle_event_handler_34:\n\t"
      "movl -0x10(%%esi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lui_widget_handle_event_handler_35\n\t"
      "pushl %%eax\n\t"
      "call *%[ce5620]\n\t"
      "addl $4, %%esp\n\t"
      ".Lui_widget_handle_event_handler_35:\n\t"
      "cmpl $0, (%%esi)\n\t"
      "je .Lui_widget_handle_event_handler_38\n\t"
      ".Lui_widget_handle_event_handler_36:\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .Lui_widget_handle_event_handler_37\n\t"
      "pushl $1\n\t"
      "pushl $0x9fc\n\t"
      "pushl $0x283280\n\t"
      "pushl $0x283560\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lui_widget_handle_event_handler_37:\n\t"
      "movl (%%esi), %%eax\n\t"
      "movl 0x31e04c, %%edx\n\t"
      "movl 0xc(%%eax), %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%edx\n\t"
      "movl %%ecx, (%%esi)\n\t"
      "call *%[c11f620]\n\t"
      "movl (%%esi), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lui_widget_handle_event_handler_36\n\t"
      ".Lui_widget_handle_event_handler_38:\n\t"
      "addl $4, %%esi\n\t"
      "cmpl $0x46cc40, %%esi\n\t"
      "jl .Lui_widget_handle_event_handler_34\n\t"
      "jmp .Lui_widget_handle_event_handler_44\n\t"
      ".Lui_widget_handle_event_handler_39:\n\t"
      "movb -0x5(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lui_widget_handle_event_handler_42\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "movl 0x30(%%ecx), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lui_widget_handle_event_handler_41\n\t"
      ".Lui_widget_handle_event_handler_40:\n\t"
      "movl %%eax, %%ecx\n\t"
      "movl 0x30(%%ecx), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lui_widget_handle_event_handler_40\n\t"
      ".Lui_widget_handle_event_handler_41:\n\t"
      "pushl %%ecx\n\t"
      "jmp .Lui_widget_handle_event_handler_43\n\t"
      ".Lui_widget_handle_event_handler_42:\n\t"
      "movb -0x3(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lui_widget_handle_event_handler_45\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      ".Lui_widget_handle_event_handler_43:\n\t"
      "call *%[ce5620]\n\t"
      "addl $4, %%esp\n\t"
      ".Lui_widget_handle_event_handler_44:\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      ".Lui_widget_handle_event_handler_45:\n\t"
      "movb -0x2(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lui_widget_handle_event_handler_52\n\t"
      "movl 0x14(%%ebp), %%ebx\n\t"
      ".Lui_widget_handle_event_handler_46:\n\t"
      "movl (%%ebx), %%eax\n\t"
      "testb $8, %%ah\n\t"
      "je .Lui_widget_handle_event_handler_52\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "movl 0x2d4(%%ecx), %%eax\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "testl %%eax, %%eax\n\t"
      "jle .Lui_widget_handle_event_handler_52\n\t"
      "xorl %%esi, %%esi\n\t"
      "movl %%ecx, %%edi\n\t"
      "nop\n\t"
      ".Lui_widget_handle_event_handler_47:\n\t"
      "movl 0x2d8(%%edi), %%eax\n\t"
      "movb -0x6(%%ebp), %%cl\n\t"
      "addl %%esi, %%eax\n\t"
      "cmpb $1, %%cl\n\t"
      "jne .Lui_widget_handle_event_handler_51\n\t"
      "testb $1, 0x30(%%eax)\n\t"
      "je .Lui_widget_handle_event_handler_51\n\t"
      "movb -0x1(%%ebp), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "jne .Lui_widget_handle_event_handler_49\n\t"
      "movl 0xc(%%eax), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lui_widget_handle_event_handler_51\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%edx\n\t"
      "call *%[ce9320]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lui_widget_handle_event_handler_48\n\t"
      "pushl $0x283da8\n\t"
      "jmp .Lui_widget_handle_event_handler_50\n\t"
      ".Lui_widget_handle_event_handler_48:\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "jmp .Lui_widget_handle_event_handler_51\n\t"
      ".Lui_widget_handle_event_handler_49:\n\t"
      "pushl $0x283d60\n\t"
      ".Lui_widget_handle_event_handler_50:\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      ".Lui_widget_handle_event_handler_51:\n\t"
      "movl 0x2d4(%%edi), %%eax\n\t"
      "incl %%ebx\n\t"
      "addl $0x50, %%esi\n\t"
      "cmpl %%eax, %%ebx\n\t"
      "jl .Lui_widget_handle_event_handler_47\n\t"
      ".Lui_widget_handle_event_handler_52:\n\t"
      "movswl -0xc(%%ebp), %%eax\n\t"
      "popl %%edi\n\t"
      "decl %%eax\n\t"
      "cmpl $3, %%eax\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "ja .Lui_widget_handle_event_handler_58\n\t"
      "jmp *.Lui_widget_handle_event_handler_jt(,%%eax,4)\n\t"
      ".Lui_widget_handle_event_handler_53:\n\t"
      "pushl $0x28380c\n\t"
      "jmp .Lui_widget_handle_event_handler_57\n\t"
      ".Lui_widget_handle_event_handler_54:\n\t"
      "pushl $0x2837f4\n\t"
      "jmp .Lui_widget_handle_event_handler_57\n\t"
      ".Lui_widget_handle_event_handler_55:\n\t"
      "pushl $0x2837e0\n\t"
      "jmp .Lui_widget_handle_event_handler_57\n\t"
      ".Lui_widget_handle_event_handler_56:\n\t"
      "pushl $0x2837c4\n\t"
      ".Lui_widget_handle_event_handler_57:\n\t"
      "pushl $0x736e6421\n\t"
      "call *%[c1b9930]\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lui_widget_handle_event_handler_58\n\t"
      "pushl $0x3f800000\n\t"
      "pushl %%eax\n\t"
      "call *%[c1c7480]\n\t"
      "addl $8, %%esp\n\t"
      ".Lui_widget_handle_event_handler_58:\n\t"
      "movl 0x18(%%ebp), %%eax\n\t"
      "movb -0x1(%%ebp), %%cl\n\t"
      "movb %%cl, (%%eax)\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".Lui_widget_handle_event_handler_jt:\n\t"
      ".long .Lui_widget_handle_event_handler_53\n\t"
      ".long .Lui_widget_handle_event_handler_54\n\t"
      ".long .Lui_widget_handle_event_handler_55\n\t"
      ".long .Lui_widget_handle_event_handler_56\n\t"
      ".text\n\t"
      :
      : [cc4b00] "m"(be6ed0_cc4b00), [c8f390] "m"(be6ed0_c8f390), [ce9810] "m"(be6ed0_ce9810), [ce6890] "m"(be6ed0_ce6890), [ce4910] "m"(be6ed0_ce4910), [ce5620] "m"(be6ed0_ce5620), [ce9320] "m"(be6ed0_ce9320), [ce84e0] "m"(be6ed0_ce84e0), [assert] "m"(be6ed0_assert), [exitfn] "m"(be6ed0_exitfn), [ce68e0] "m"(be6ed0_ce68e0), [c1c7480] "m"(be6ed0_c1c7480), [c11f620] "m"(be6ed0_c11f620), [c1b9930] "m"(be6ed0_c1b9930)
      : "memory");
}
#else
#error "ui_widget_handle_event_handler: clang naked draft required"
#endif


/* ui_widget_load_from_tag_internal (0xe7b10) — XBE naked draft (batch 115). */
#if defined(__clang__)
static void *(*const be7b10_memset)(void *, int, unsigned int) = (void *)csmemset;
static void *(*const be7b10_tag)(int, int) = (void *)tag_get;
static void *(*const be7b10_elem)(void *, int, int) = (void *)tag_block_get_element;
static void (*const be7b10_ce5b10)(void *widget /* */, void *draw_state /* */) = (void *)FUN_000e5b10;
static void (*const be7b10_c8f390)(unsigned __int16 a1, const char *a2, ...) = (void *)error;
static void (*const be7b10_ce6ed0)(void *widget, void *definition, void *event_data, void *event_handler, char *widget_deleted) = (void *)ui_widget_handle_event_handler;
static void (*const be7b10_ce4f20)(void *root_widget, void *target_widget) = (void *)ui_widget_apply_focus;
static bool (*const be7b10_cb5c30)(void) = (void *)game_time_get_paused;
static void (*const be7b10_cb5c70)(bool) = (void *)game_time_set_paused;
static void (*const be7b10_c1cb8a0)(int enabled) = (void *)sound_set_music_enabled;

__attribute__((naked, noinline))
void ui_widget_load_from_tag_internal(void *tag_data, void *widget, void *parent, int tag_index, int widget_stack, int widget_stack_base)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $8, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl $0x58\n\t"
      "movl %%edx, %%esi\n\t"
      "pushl $0\n\t"
      "pushl %%esi\n\t"
      "movl %%eax, %%edi\n\t"
      "movl %%ecx, %%ebx\n\t"
      "call *%[memset]\n\t"
      "movb 0x150(%%edi), %%al\n\t"
      "addl $0xc, %%esp\n\t"
      "testb $2, %%al\n\t"
      "je .Lui_widget_load_from_tag_internal_1\n\t"
      "testl %%ebx, %%ebx\n\t"
      "je .Lui_widget_load_from_tag_internal_1\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "cmpl (%%ebx), %%eax\n\t"
      "jne .Lui_widget_load_from_tag_internal_1\n\t"
      "movw $1, 0xe(%%esi)\n\t"
      ".Lui_widget_load_from_tag_internal_1:\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "movw 0xc(%%ebp), %%ax\n\t"
      "movw %%ax, 0x8(%%esi)\n\t"
      "movl %%ecx, (%%esi)\n\t"
      "leal 0x4(%%edi), %%edx\n\t"
      "movl %%edx, 0x4(%%esi)\n\t"
      "movw (%%edi), %%cx\n\t"
      "movw %%cx, 0xe(%%esi)\n\t"
      "movb $1, 0x10(%%esi)\n\t"
      "movl 0x2c(%%edi), %%edx\n\t"
      "shrl $9, %%edx\n\t"
      "andb $1, %%dl\n\t"
      "movb %%dl, 0x11(%%esi)\n\t"
      "movl 0x2c(%%edi), %%eax\n\t"
      "shrl $1, %%eax\n\t"
      "andb $1, %%al\n\t"
      "movb %%al, 0x13(%%esi)\n\t"
      "movl 0x46cc40, %%ecx\n\t"
      "movl %%ecx, 0x18(%%esi)\n\t"
      "movl 0x30(%%edi), %%eax\n\t"
      "xorl %%edx, %%edx\n\t"
      "testl %%eax, %%eax\n\t"
      "setle %%dl\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "decl %%edx\n\t"
      "andl %%edx, %%eax\n\t"
      "movl %%eax, 0x1c(%%esi)\n\t"
      "movl 0x34(%%edi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "setle %%cl\n\t"
      "movl $0x3f800000, 0x24(%%esi)\n\t"
      "movl %%ebx, 0x30(%%esi)\n\t"
      "decl %%ecx\n\t"
      "andl %%ecx, %%eax\n\t"
      "movl %%eax, 0x20(%%esi)\n\t"
      "movswl 0xe(%%esi), %%eax\n\t"
      "decl %%eax\n\t"
      "jne .Lui_widget_load_from_tag_internal_2\n\t"
      "movw $0xffff, 0x40(%%esi)\n\t"
      ".Lui_widget_load_from_tag_internal_2:\n\t"
      "movl 0x44(%%edi), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lui_widget_load_from_tag_internal_3\n\t"
      "pushl $0x40\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "pushl $0x6269746d\n\t"
      "call *%[tag]\n\t"
      "addl $0x54, %%eax\n\t"
      "addl $8, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movw 0x22(%%eax), %%dx\n\t"
      "addl $0xc, %%esp\n\t"
      "movw %%dx, 0x56(%%esi)\n\t"
      ".Lui_widget_load_from_tag_internal_3:\n\t"
      "movb 0x46cc83, %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lui_widget_load_from_tag_internal_4\n\t"
      "pushl %%edi\n\t"
      "call *%[ce5b10]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lui_widget_load_from_tag_internal_4\n\t"
      "pushl $0x283fa8\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      ".Lui_widget_load_from_tag_internal_4:\n\t"
      "movl 0x54(%%edi), %%eax\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "cmpl %%ebx, %%eax\n\t"
      "movl %%ebx, 0x8(%%ebp)\n\t"
      "jle .Lui_widget_load_from_tag_internal_7\n\t"
      "leal (%%ebx), %%ebx\n\t"
      ".Lui_widget_load_from_tag_internal_5:\n\t"
      "movl 0x58(%%edi), %%eax\n\t"
      "addl %%ebx, %%eax\n\t"
      "cmpw $0x18, 0x4(%%eax)\n\t"
      "jne .Lui_widget_load_from_tag_internal_6\n\t"
      "movw 0x8(%%esi), %%dx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movl %%ecx, -0x6(%%ebp)\n\t"
      "movw %%cx, -0x2(%%ebp)\n\t"
      "leal 0xf(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "movw %%dx, -0x6(%%ebp)\n\t"
      "leal -0x8(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "pushl %%esi\n\t"
      "movw $0, -0x8(%%ebp)\n\t"
      "call *%[ce6ed0]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lui_widget_load_from_tag_internal_6:\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl 0x54(%%edi), %%ecx\n\t"
      "incl %%eax\n\t"
      "addl $0x48, %%ebx\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "movl %%eax, 0x8(%%ebp)\n\t"
      "jl .Lui_widget_load_from_tag_internal_5\n\t"
      ".Lui_widget_load_from_tag_internal_7:\n\t"
      "movl 0x38(%%esi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lui_widget_load_from_tag_internal_11\n\t"
      "movl 0x34(%%esi), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "je .Lui_widget_load_from_tag_internal_11\n\t"
      ".Lui_widget_load_from_tag_internal_8:\n\t"
      "movl (%%edi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x44654c61\n\t"
      "call *%[tag]\n\t"
      "movb 0x12(%%edi), %%cl\n\t"
      "addl $8, %%esp\n\t"
      "testb %%cl, %%cl\n\t"
      "jne .Lui_widget_load_from_tag_internal_10\n\t"
      "movl 0x54(%%eax), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "jg .Lui_widget_load_from_tag_internal_9\n\t"
      "movw 0xe(%%edi), %%ax\n\t"
      "cmpw $2, %%ax\n\t"
      "je .Lui_widget_load_from_tag_internal_9\n\t"
      "cmpw $3, %%ax\n\t"
      "jne .Lui_widget_load_from_tag_internal_10\n\t"
      ".Lui_widget_load_from_tag_internal_9:\n\t"
      "movl %%edi, %%ecx\n\t"
      "movl %%esi, %%eax\n\t"
      "call *%[ce4f20]\n\t"
      ".Lui_widget_load_from_tag_internal_10:\n\t"
      "movl 0x2c(%%edi), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .Lui_widget_load_from_tag_internal_8\n\t"
      ".Lui_widget_load_from_tag_internal_11:\n\t"
      "cmpb $1, 0x13(%%esi)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "jne .Lui_widget_load_from_tag_internal_13\n\t"
      "incw 0x46cc4a\n\t"
      "call *%[cb5c30]\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lui_widget_load_from_tag_internal_12\n\t"
      "pushl $1\n\t"
      "call *%[cb5c70]\n\t"
      "addl $4, %%esp\n\t"
      ".Lui_widget_load_from_tag_internal_12:\n\t"
      "movb 0x46cc87, %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lui_widget_load_from_tag_internal_13\n\t"
      "movb 0x46cc88, %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lui_widget_load_from_tag_internal_13\n\t"
      "pushl $1\n\t"
      "call *%[c1cb8a0]\n\t"
      "addl $4, %%esp\n\t"
      "movb $1, 0x46cc87\n\t"
      ".Lui_widget_load_from_tag_internal_13:\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [memset] "m"(be7b10_memset), [tag] "m"(be7b10_tag), [elem] "m"(be7b10_elem), [ce5b10] "m"(be7b10_ce5b10), [c8f390] "m"(be7b10_c8f390), [ce6ed0] "m"(be7b10_ce6ed0), [ce4f20] "m"(be7b10_ce4f20), [cb5c30] "m"(be7b10_cb5c30), [cb5c70] "m"(be7b10_cb5c70), [c1cb8a0] "m"(be7b10_c1cb8a0)
      : "memory");
}
#else
#error "ui_widget_load_from_tag_internal: clang naked draft required"
#endif


/* 0xe9320 */
void *ui_widget_spawn_from_event_handler(void *widget, int tag_index)
{
  int eax = 0;
  int ecx = 0;
  int ebp = 0;

  tag_get(0x44654c61, 0);
  /* test (char)ecx, 0x10 -> je 0xe9371 */
  /* cmp eax, 4 -> ja 0xe9368 */
  /* cmp eax, 4 -> ja 0xe938a */
  display_assert((char *)0x00284cb8, (char *)0x00283280, 5392, 0);
  system_exit(0);
  /* test eax, eax -> jne 0xe93b8 */
  /* test ecx, ecx -> je 0xe93f1 */
  /* test eax, eax -> je 0xe93f1 */
  /* relift: cmp eax, dword ptr [ebp + 8] -> je 0xe93ef */
  /* test eax, eax -> jne 0xe93e0 */
  ui_widget_load_by_name_or_tag((char *)0, 0, 0, 0, 0, 0, 0);
  error(0, (char *)0x00283728);
  return NULL;

  (void)eax;
  (void)ecx;
  (void)ebp;
}
