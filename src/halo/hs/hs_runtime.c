#include <stdint.h>

/* Validate the syntax tree after loading a scenario. Iterates all syntax
 * nodes and checks for consistency: valid types, valid source offsets,
 * valid script indices, and correct function references. If any node fails
 * validation, sets the compile error message and returns false.
 *
 * This is the last step before scripts can run — it catches stale compiled
 * data that no longer matches the current function table or scenario layout.
 *
 * Callees (all via hardcoded addresses, not in kb.json):
 *   0xc3d00 = hs_function_table_get (short function_index) -> void*
 *   0xc3e60 = hs_script_get_type (uint16 script_ref) -> short
 *   0xc3fc0 = hs_function_find_by_name (char *name) -> short
 *   0xc57a0 = hs_source_offset_valid (int offset) -> bool
 *   0xc73a0 = hs_type_check_expression (@EDI=datum_index) -> bool
 *   0xcb070 = hs_types_compatible (short actual, short desired) -> bool
 * [ported]
 *
 * Globals:
 *   0x5aa6c8 = hs_syntax_data (data_t*)
 *   0x46b6e4 = hs_compile_globals.source_size
 *   0x46b6e8 = hs_compile_globals.compiled_source
 *   0x46b6fc = hs_compile_globals.error_message
 *   0x46b700 = hs_compile_globals.error_offset
 *   0x46b808 = hs_compile_globals.validating (uint8_t)
 */
bool hs_validate_syntax(char **error_info, char **error_text)
{
  bool ok;
  int datum_index;
  char *node;
  short node_type;
  short result_type;
  char *scenario;
  char *script_element;

  ok = true;

  /* Set up compile globals for validation pass. */
  scenario = (char *)global_scenario_get();
  *(int *)0x46b6e8 = *(int *)(scenario + 0x494);
  scenario = (char *)global_scenario_get();
  *(int *)0x46b6e4 = *(int *)(scenario + 0x488) - 0x400;
  *(int *)0x46b6fc = 0;
  *(uint8_t *)0x46b808 = 1;
  *(int *)error_info = 0;
  *(int *)error_text = 0;

  /* Iterate all syntax nodes. */
  datum_index = data_next_index(*(data_t **)0x5aa6c8, -1);
  while (datum_index != -1) {
    if (!ok)
      break;

    node = (char *)datum_get(*(data_t **)0x5aa6c8, datum_index);
    node_type = *(int16_t *)(node + 0x4);

    /* Check if the node type is valid (4..0x30 inclusive) or type 2. */
    if (node_type < 4 || node_type > 0x30) {
      if (node_type != 2) {
        *(int *)0x46b6fc = (int)"missing type (you need to recompile scripts.)";
        goto error;
      }
      /* Type 2 (function call) — skip to next node. */
      goto next;
    }

    /* Check the constant flag (bit 0 of byte at +6). */
    {
      char *node2 = (char *)datum_get(*(data_t **)0x5aa6c8, datum_index);
      if (*(uint8_t *)(node2 + 0x6) & 1) {
        /* Constant node — check source offset range and type-check. */
        if (*(int16_t *)(node + 0x4) >= 9 || (*(uint8_t *)(node + 0x6) & 4)) {
          /* Source offset validation. */
          bool offset_ok = true;
          if (*(int *)(node + 0xc) < 0 ||
              *(int *)(node + 0xc) >= *(int *)0x46b6e4) {
            *(int *)0x46b6fc =
              (int)"bad source offset (you need to recompile.)";
            offset_ok = false;
          }
          ok = offset_ok;
          if (ok) {
            ok = FUN_000c73a0(datum_index);
          }
        }

        if (!ok)
          goto use_node_type;

        /* If the reparse flag (bit 2) is set, get the script type. */
        if (*(uint8_t *)(node + 0x6) & 4) {
          result_type =
            hs_global_get_type((uint16_t) * (int16_t *)(node + 0x10));
          goto check_type;
        }

        goto use_node_type;
      }
    }

    /* Non-constant node: check the script-reference flag (bit 1). */
    if (*(uint8_t *)(node + 0x6) & 2) {
      /* Script reference node. */
      if (*(int16_t *)(node + 0x2) < 0) {
        goto check_script_index;
      }

      {
        int16_t script_idx = *(int16_t *)(node + 0x2);
        scenario = (char *)global_scenario_get();
        if ((int)script_idx >= *(int *)(scenario + 0x49c)) {
          goto check_script_index;
        }

        /* tag_block_get_element (0x19b210): 3 stack args. */
        {
          char *scenario2 = (char *)global_scenario_get();
          script_element = (char *)tag_block_get_element(scenario2 + 0x49c,
                                                         (int)script_idx, 0x5c);
        }

        if (*(int16_t *)(script_element + 0x20) == 3) {
          goto script_ok;
        }
      }

    check_script_index:
      if (*(int16_t *)(script_element + 0x20) != 4) {
        *(int *)0x46b6fc = (int)"bad script index (you need to recompile.)";
        goto error;
      }

    script_ok:
      result_type = *(int16_t *)(script_element + 0x22);
      goto check_type;
    }

    /* Non-constant, non-script-reference: function call node. */
    {
      char *fn_node = (char *)datum_get(*(data_t **)0x5aa6c8, datum_index);
      int next_expr = *(int *)(fn_node + 0x10);

      if (next_expr == -1) {
        *(int *)0x46b6fc =
          (int)"corrupt syntax tree (you need to recompile scripts.)";
        goto error;
      }

      {
        char *inner_node = (char *)datum_get(*(data_t **)0x5aa6c8, next_expr);
        if (*(int16_t *)(inner_node + 0x4) != 2) {
          *(int *)0x46b6fc =
            (int)"corrupt syntax tree (you need to recompile scripts.)";
          goto error;
        }

        /* Validate the source offset of the inner node. */
        {
          bool src_ok;
          int src_offset = *(int *)(inner_node + 0xc);
          src_ok = hs_source_offset_valid(src_offset);
          if (!src_ok)
            goto error;

          /* Look up the function by name in the compiled source. */
          {
            int name_addr = *(int *)(inner_node + 0xc) + *(int *)0x46b6e8;
            int16_t func_idx =
              hs_find_function_by_name((const char *)name_addr);
            if (func_idx == -1) {
              *(int *)0x46b6fc =
                (int)"missing function (you need to recompile scripts.)";
              goto error;
            }

            /* Update the node's function index and look up the return
             * type. */
            *(int16_t *)(node + 0x2) = func_idx;

            hs_function_table_get(func_idx);
            result_type =
              *(int16_t *)hs_function_table_get(*(int16_t *)(node + 0x2));
            goto check_type;
          }
        }
      }
    }

  use_node_type:
    result_type = *(int16_t *)(node + 0x2);

  check_type:
    if (ok) {
      /* Validate that result_type is valid (4..0x30) or passthrough
       * (3). */
      if ((result_type < 4 || result_type > 0x30) && result_type != 3) {
        *(int *)0x46b6fc = (int)"type is inconsistent with usage "
                                "(you need to recompile scripts.)";
        goto error;
      }

      if (!hs_types_compatible(result_type, *(int16_t *)(node + 0x4))) {
        *(int *)0x46b6fc = (int)"type is inconsistent with usage "
                                "(you need to recompile scripts.)";
        goto error;
      }
      ok = true;
    }
    goto next;

  error:
    ok = false;

  next:
    datum_index = data_next_index(*(data_t **)0x5aa6c8, datum_index);
  }

  /* If validation failed, report the error. */
  if (!ok) {
    *(int *)error_info = *(int *)0x46b6fc;
    if (*(int *)0x46b700 != -1) {
      *(int *)error_text = *(int *)0x46b700 + *(int *)0x46b6e8;
    }
  }

  /* Clean up compile globals. */
  *(int *)0x46b6e8 = 0;
  *(int *)0x46b6fc = 0;
  *(uint8_t *)0x46b808 = 0;

  return ok;
}

/* Compile a HaloScript expression from source text. Allocates syntax nodes,
 * copies source into the compiled source buffer, parses one expression,
 * and wraps it in a begin/void node pair for execution. Returns the root
 * syntax datum index on success, or -1 on failure.
 *
 * If no scenario is loaded, allocates a temporary buffer for the source
 * (freed later by hs_compile_cleanup). Otherwise uses the scenario's
 * string constants area offset by 0x400 bytes.
 *
 * Globals:
 *   0x326a08 = global_scenario_index
 *   0x5aa6c8 = hs_syntax_data (data_t*)
 *   0x46b6e4 = hs_compile_globals.source_size
 *   0x46b6e8 = hs_compile_globals.compiled_source
 *   0x46b6fc = hs_compile_globals.error_message
 *   0x46b700 = hs_compile_globals.error_offset
 *   0x46b804 = hs_compile_globals.source_allocated
 */
int hs_compile(int source_length, const char *source, int *error_info,
               char **error_text)
{
  int base_offset;
  int expr_datum;
  char *src_cursor;

  if (source_length >= 0x400)
    return -1;

  if (*(int *)0x326a08 == -1) {
    /* No scenario loaded — allocate temporary buffer. */
    base_offset = 0;
    *(int *)0x46b6e8 = (int)debug_malloc(
      source_length + 1, 0, "c:\\halo\\SOURCE\\hs\\hs_compile.c", 0xaf);
    *(uint8_t *)0x46b804 = 1;
    if (*(int *)0x46b6e8 == 0) {
      display_assert("hs_compile_globals.compiled_source",
                     "c:\\halo\\SOURCE\\hs\\hs_compile.c", 0xb2, true);
      system_exit(-1);
    }
  } else {
    /* Scenario loaded — use string constants area. */
    char *scenario = (char *)global_scenario_get();
    if (*(int *)(scenario + 0x488) < 0x400) {
      display_assert("global_scenario_get()->hs_string_constants.size>="
                     "HS_MAXIMUM_DYNAMIC_SOURCE_DATA_BYTES",
                     "c:\\halo\\SOURCE\\hs\\hs_compile.c", 0xa6, true);
      system_exit(-1);
    }
    scenario = (char *)global_scenario_get();
    base_offset = *(int *)(scenario + 0x488) - 0x400;
    scenario = (char *)global_scenario_get();
    *(int *)0x46b6e8 = *(int *)(scenario + 0x494);
  }

  /* Copy source into compiled source buffer at the base offset. */
  csmemcpy((void *)(*(int *)0x46b6e8 + base_offset), (void *)source,
           source_length);
  *(int *)0x46b6e4 = base_offset + source_length;
  *(uint8_t *)(*(int *)0x46b6e4 + *(int *)0x46b6e8) = 0;

  /* Initialize parse state. */
  src_cursor = (char *)(*(int *)0x46b6e8 + base_offset);
  *(int *)0x46b6fc = 0;
  *(int *)error_info = 0;
  *(int *)error_text = 0;
  *(int *)0x46b700 = -1;

  FUN_000c72b0(&src_cursor);

  if (*src_cursor == '\0')
    return -1;

  expr_datum = FUN_000c7be0(&src_cursor);

  if (*(int *)0x46b6fc != 0)
    goto compile_error;

  /* Allocate two new syntax nodes to wrap the expression. */
  {
    int node1 = data_new_at_index(*(data_t **)0x5aa6c8);
    int node2 = data_new_at_index(*(data_t **)0x5aa6c8);

    if (node1 != -1 && node2 != -1) {
      char *n1 = (char *)datum_get(*(data_t **)0x5aa6c8, node1);
      char *n2 = (char *)datum_get(*(data_t **)0x5aa6c8, node2);

      *(int *)(n1 + 0x10) = node2;
      *(int *)(n1 + 0x8) = -1;

      /* Copy source offset from the parsed expression node. */
      {
        char *expr_node = (char *)datum_get(*(data_t **)0x5aa6c8, expr_datum);
        *(int *)(n1 + 0xc) = *(int *)(expr_node + 0xc);
      }

      *(int16_t *)(n1 + 0x6) = 0;
      *(int *)(n2 + 0x8) = expr_datum;
      *(int *)(n2 + 0xc) = -1;
      *(int16_t *)(n2 + 0x2) = 0x16; /* hs_type_void */
      *(int16_t *)(n2 + 0x6) = 1;
      *(int16_t *)(n2 + 0x4) = 2; /* hs_node_type_function_call */

      /* hs_type_check: 2 stack args (datum_index, check_type). */
      {
        bool ok = hs_type_check(node1, 4);
        if (ok)
          return node1;
      }
    }
  }

compile_error:
  *(int *)error_info = *(int *)0x46b6fc;
  if (*(int *)0x46b700 != -1) {
    *(int *)0x46b700 = *(int *)0x46b700 - base_offset;
    if (*(int *)0x46b700 < 0 || *(int *)0x46b700 >= source_length) {
      display_assert("hs_compile_globals.error_offset>=0 && "
                     "hs_compile_globals.error_offset<source_size",
                     "c:\\halo\\SOURCE\\hs\\hs_compile.c", 0xeb, true);
      system_exit(-1);
    }
    *error_text = (char *)(*(int *)0x46b700 + (int)source);
  }

  return -1;
}

/* Compile a source file into the syntax tree. Parses multiple top-level
 * expressions from the source, checking each with hs_type_check. On
 * failure, reports error info and adjusts error offset relative to the
 * source file.
 *
 * 0xc5730 = hs_compile_source_setup (@EDI=source_file_size, stack: source_ptr)
 * 0xc72b0 = skip_whitespace (@ESI=&cursor)
 * 0xc7be0 = hs_parse_expression (@EAX=&cursor, returns datum index)
 */
bool hs_compile_source(int source_file_size, void *source_ptr,
                       char **error_info, char **error_text)
{
  char *cursor;
  bool ok;
  int expr_datum;

  cursor = hs_compile_initialize(source_file_size, source_ptr);

  if (cursor == NULL) {
    *(int *)error_info = (int)"couldn't allocate memory for compiled source.";
    return false;
  }

  *(int *)0x46b6fc = 0;
  *(int *)error_info = 0;
  *(int *)error_text = 0;
  ok = true;
  *(int *)0x46b700 = -1;

  FUN_000c72b0(&cursor);

  while (*cursor != '\0') {
    expr_datum = FUN_000c7be0(&cursor);
    FUN_000c72b0(&cursor);

    if (*(int *)0x46b6fc != 0)
      goto parse_error;

    ok = hs_type_check(expr_datum, 1);
    if (!ok)
      goto parse_error;
  }

  if (ok)
    return true;

parse_error:
  if (*(int *)0x46b6fc == 0) {
    display_assert("tell matt that somebody failed to correctly report a "
                   "parsing error.",
                   "c:\\halo\\SOURCE\\hs\\hs_compile.c", 0x131, true);
    system_exit(-1);
  }

  *error_info = (char *)*(int *)0x46b6fc;
  *(uint8_t *)0x46b6f8 = 1;

  if (*(int *)0x46b700 != -1) {
    *(int *)0x46b700 = *(int *)0x46b700 + (source_file_size - *(int *)0x46b6e4);
    if (*(int *)0x46b700 < 0 || *(int *)0x46b700 >= source_file_size) {
      display_assert("hs_compile_globals.error_offset>=0 && "
                     "hs_compile_globals.error_offset<source_file_size",
                     "c:\\halo\\SOURCE\\hs\\hs_compile.c", 0x13b, true);
      system_exit(-1);
    }
    *error_text = (char *)(*(int *)0x46b700 + (int)source_ptr);
  }

  return false;
}

/* Clean up compile state after hs_compile or hs_compile_source.
 * If scripts were successfully compiled (hs_compile_globals.dirty),
 * either recompiles scripts from scratch or resizes the scenario's
 * tag blocks. Frees any temporarily allocated source buffer.
 *
 * Globals:
 *   0x46b6e0 = hs_compile_globals.initialized
 *   0x46b6e8 = hs_compile_globals.compiled_source (allocation ptr)
 *   0x46b6f8 = hs_compile_globals.error_occurred
 *   0x46b804 = hs_compile_globals.source_allocated
 *   0x46b805 = hs_compile_globals.dirty
 *   0x5aa6c8 = hs_syntax_data (data_t*)
 */
void hs_compile_cleanup(void)
{
  if (*(uint8_t *)0x46b6e0 == 0) {
    display_assert("hs_compile_globals.initialized",
                   "c:\\halo\\SOURCE\\hs\\hs_compile.c", 0x75, true);
    system_exit(-1);
  }

  if (*(uint8_t *)0x46b805 != 0) {
    if (*(uint8_t *)0x46b6f8 == 0) {
      /* No error — recompile scripts from scratch. */
      hs_compile_recompile_scripts();
    } else {
      /* Error occurred — resize tag blocks to zero and re-validate
       * syntax data. */
      char *scenario = (char *)global_scenario_get();
      tag_block_resize(scenario + 0x49c, 0);
      tag_block_resize(scenario + 0x4a8, 0);
      tag_data_resize(scenario + 0x488, 0);
      data_make_valid(*(data_t **)0x5aa6c8);
    }

    /* Free the compiled source allocation if it exists. */
    if (*(int *)0x46b6e8 != 0) {
      debug_free(*(void **)0x46b6e8, "c:\\halo\\SOURCE\\hs\\hs_compile.c",
                 0x87);
    }
  }

  if (*(uint8_t *)0x46b804 != 0) {
    debug_free(*(void **)0x46b6e8, "c:\\halo\\SOURCE\\hs\\hs_compile.c", 0x8c);
    *(int *)0x46b6e8 = 0;
    *(uint8_t *)0x46b804 = 0;
  }

  *(uint8_t *)0x46b6e0 = 0;
}

/* HaloScript runtime — thread management and script execution. */

/* Dispose runtime state from old map: invalidate thread data and
 * clean up any allocated script globals. */
void hs_runtime_dispose_from_old_map(void)
{
  int16_t idx;
  char *data;

  data_make_invalid(*(data_t **)0x5aa6c4);

  idx = *(int16_t *)0x27d504;
  data = *(char **)0x5aa6c0;
  while (idx < *(int16_t *)(data + 0x2e)) {
    if (datum_absolute_index_to_index((data_t *)data, (int)idx) != 0)
      datum_delete((data_t *)data, (int)idx);
    idx++;
    data = *(char **)0x5aa6c0;
  }

  *(uint8_t *)0x46b810 = 0;
}

/* 0xca940 */
static int hs_thread_new(int script_index, int type)
{
  int thread_index;
  char *thread;
  char *stack;
  char *script;

  if (type < 0 || type >= 3) {
    display_assert("type>=0 && type<NUMBER_OF_HS_THREAD_TYPES",
                   "c:\\halo\\SOURCE\\hs\\hs_runtime.c", 0x26f, true);
    system_exit(-1);
  }

  if (type == 0 && script_index == -1) {
    display_assert("type!=_hs_thread_type_script || script_index!=NONE",
                   "c:\\halo\\SOURCE\\hs\\hs_runtime.c", 0x270, true);
    system_exit(-1);
  }

  thread_index = data_new_at_index(*(data_t **)0x5aa6c4);
  if (thread_index != -1) {
    thread = (char *)datum_get(*(data_t **)0x5aa6c4, thread_index);
    stack = thread + 0x18;
    *(char **)(thread + 0x10) = stack;
    *(int32_t *)stack = 0;
    *(int16_t *)(*(char **)(thread + 0x10) + 0xc) = 0;
    *(int32_t *)(*(char **)(thread + 0x10) + 0x4) = -1;
    *(uint8_t *)(thread + 0x2) = (uint8_t)type;
    *(int32_t *)(thread + 0x4) = script_index;
    *(uint8_t *)(thread + 0x3) = 0;

    if (script_index != -1) {
      script = (char *)tag_block_get_element(
        (char *)global_scenario_get() + 0x49c, script_index, 0x5c);
      if (*(int16_t *)(script + 0x20) == 1) {
        *(int32_t *)(thread + 0x8) = -2;
        return thread_index;
      }
    }
    *(int32_t *)(thread + 0x8) = 0;
  }
  return thread_index;
}

/* 0xcaa30 — Delete an HS thread by handle. Asserts that the thread's type is
 * not _hs_thread_type_script (type==0) before deleting. Called when a
 * console-command thread (type==2) finishes execution in FUN_000cd840.
 */
static void FUN_000caa30(int thread_handle)
{
  char *thread;

  thread = (char *)datum_get(*(data_t **)0x5aa6c4, thread_handle);
  if (*(uint8_t *)(thread + 0x2) == 0) {
    display_assert("hs_thread_get(thread_index)->type!=_hs_thread_type_script",
                   "c:\\halo\\SOURCE\\hs\\hs_runtime.c", 0x290, true);
    system_exit(-1);
  }
  datum_delete(*(data_t **)0x5aa6c4, thread_handle);
}

/* 0xcaa80 */
static char *hs_get_thread_script_name(int thread_index)
{
  char *thread;
  uint8_t type;
  int script_index;
  char *scenario;
  char *script_entry;

  thread = (char *)datum_get(*(data_t **)0x5aa6c4, thread_index);
  type = *(uint8_t *)(thread + 0x2);

  if (type == 0) {
    thread = (char *)datum_get(*(data_t **)0x5aa6c4, thread_index);
    script_index = *(int32_t *)(thread + 0x4);
    scenario = (char *)global_scenario_get();
    script_entry = (char *)tag_block_get_element((char *)scenario + 0x49c,
                                                 script_index, 0x5c);
    return script_entry;
  }

  if (type == 1) {
    return "[global initialize]";
  }

  if (type == 2) {
    return "[console command]";
  }

  display_assert(NULL, "c:\\halo\\SOURCE\\hs\\hs_runtime.c", 0x2a9, true);
  system_exit(-1);
  return NULL;
}

/* 0xcab00 — Push a new frame onto the HaloScript thread's stack.
 * Allocates the next frame by advancing thread->stack_ptr past the current
 * frame, sets the new frame's back-link to the previous frame pointer, and
 * zeroes the new frame's size field.
 *
 * Frame layout (each frame is at thread+0x18..thread+0x218):
 *   +0x00 (void*) : back-link to previous frame
 *   +0x04 (int)   : expression index (set by caller after push)
 *   +0x08 (void*) : destination value pointer (set by caller)
 *   +0x0c (int16_t): frame size in bytes (this function zeroes it)
 *
 * Stack overflow is fatal: formats a message and halts via display_assert.
 */
static void hs_thread_push_frame(int thread_handle)
{
  char *thread;
  char *cur_frame;
  char *new_frame;

  thread = (char *)datum_get(*(data_t **)0x5aa6c4, thread_handle);
  cur_frame = *(char **)(thread + 0x10);

  /* new_frame = cur_frame + cur_frame->size + 0x10 */
  new_frame = cur_frame + (int)*(int16_t *)(cur_frame + 0xc) + 0x10;

  /* Overflow check: (new_frame + 0x10) must be below thread+0x218 */
  if ((unsigned int)(new_frame + 0x10) >= (unsigned int)(thread + 0x218)) {
    const char *script_name = hs_get_thread_script_name(thread_handle);
    const char *msg = csprintf(
      (char *)0x5ab100,
      "a problem occurred while executing the script %s: %s (%s)", script_name,
      "stack overflow.",
      "(byte *) (new_frame+1)<thread->stack_data+HS_THREAD_STACK_SIZE");
    display_assert(msg, "c:\\halo\\SOURCE\\hs\\hs_runtime.c", 0x35e, true);
    system_exit(-1);
  }

  /* Link new frame and advance stack pointer */
  *(char **)(new_frame + 0x0) = cur_frame;
  *(char **)(thread + 0x10) = new_frame;
  *(int16_t *)(new_frame + 0xc) = 0;
}

/* 0xcaba0 — Allocate `size` bytes from the current HaloScript thread stack
 * frame's data area. Returns a pointer to the newly allocated region.
 *
 * The HS thread stack is a fixed-size region [thread+0x18 .. thread+0x218).
 * Each frame begins with a 0xe-byte header:
 *   +0x00 (void*)   : back-link to previous frame
 *   +0x04 (int)     : expression index
 *   +0x08 (void*)   : destination value pointer
 *   +0x0c (int16_t) : current data size in bytes
 * Data starts at frame+0xe; this function returns (frame + old_size + 0xe)
 * and increments frame->size by `size`.
 *
 * Three fatal assertions (line 0x37d–0x37f):
 *   1. valid_thread: thread pointer is within the data array, and the frame
 *      pointer lies in [thread+0x18, thread+0x218).
 *   2. size != 0
 *   3. frame->data + frame->size + size <= thread + HS_THREAD_STACK_SIZE
 *
 * ABI: thread_handle@<eax>, size on stack; returns void* in EAX.
 */
static void *hs_thread_stack_alloc(int thread_handle, int size)
{
  data_t *hs_threads;
  char *thread;
  char *frame;
  int16_t old_size;
  const char *script_name;
  const char *msg;

  hs_threads = *(data_t **)0x5aa6c4;
  thread = (char *)datum_get(hs_threads, thread_handle);
  frame = *(char **)(thread + 0x10);

  /* valid_thread(thread): thread in array bounds, frame in stack area,
   * and current data end within stack.
   * data_t offsets: +0x34=data (base), +0x2e=current_count, +0x22=size (elem).
   */
  if ((unsigned int)thread < (unsigned int)(hs_threads->data) ||
      (unsigned int)thread >= (unsigned int)((char *)hs_threads->data +
                                             (int)hs_threads->current_count *
                                               (int)hs_threads->size) ||
      (unsigned int)frame < (unsigned int)(thread + 0x18) ||
      (unsigned int)frame >= (unsigned int)(thread + 0x218) ||
      (unsigned int)(frame + (int)*(int16_t *)(frame + 0xc) + 0xe) >
        (unsigned int)(thread + 0x218)) {
    script_name = hs_get_thread_script_name(thread_handle);
    msg = csprintf((char *)0x5ab100,
                   "a problem occurred while executing the script %s: %s (%s)",
                   script_name, "valid_thread(thread)", "corrupted stack.");
    display_assert(msg, "c:\\halo\\SOURCE\\hs\\hs_runtime.c", 0x37d, true);
    system_exit(-1);
  }

  if (size == 0) {
    script_name = hs_get_thread_script_name(thread_handle);
    msg = csprintf((char *)0x5ab100,
                   "a problem occurred while executing the script %s: %s (%s)",
                   script_name,
                   "attempt to allocate zero space from the stack.", "size");
    display_assert(msg, "c:\\halo\\SOURCE\\hs\\hs_runtime.c", 0x37e, true);
    system_exit(-1);
  }

  /* frame->data + frame->size + size <= thread + HS_THREAD_STACK_SIZE */
  if ((unsigned int)(frame + (int)*(int16_t *)(frame + 0xc) + 0xe + size) >
      (unsigned int)(thread + 0x218)) {
    script_name = hs_get_thread_script_name(thread_handle);
    msg = csprintf(
      (char *)0x5ab100,
      "a problem occurred while executing the script %s: %s (%s)", script_name,
      "stack overflow.",
      "frame->data+frame->size+size<=thread->stack_data+HS_THREAD_STACK_SIZE");
    display_assert(msg, "c:\\halo\\SOURCE\\hs\\hs_runtime.c", 0x37f, true);
    system_exit(-1);
  }

  old_size = *(int16_t *)(frame + 0xc);
  *(int16_t *)(frame + 0xc) = old_size + (int16_t)size;
  return (void *)(frame + (int)old_size + 0xe);
}

/* 0xcada0 — Find an HS thread whose script index (at +4) matches the given
 * index. Iterates hs_thread_data; returns the matching datum handle or -1. */
int FUN_000cada0(int16_t script_index)
{
  int datum_index;

  datum_index = data_next_index(*(data_t **)0x5aa6c4, -1);
  while (datum_index != -1) {
    char *thread = (char *)datum_get(*(data_t **)0x5aa6c4, datum_index);
    if (*(int *)(thread + 0x4) == (int)script_index)
      return datum_index;
    datum_index = data_next_index(*(data_t **)0x5aa6c4, datum_index);
  }
  return -1;
}

/* 0xcaff0 */
static bool hs_object_types_compatible(int16_t actual_offset,
                                       int16_t desired_offset)
{
  uint16_t *masks = (uint16_t *)0x26f320;
  uint16_t actual_mask;
  uint16_t desired_mask;

  if (actual_offset < 0 || actual_offset >= 6) {
    display_assert("actual_type>=0 && actual_type<NUMBER_OF_HS_OBJECT_TYPES",
                   "c:\\halo\\SOURCE\\hs\\hs_runtime.c", 0x599, true);
    system_exit(-1);
  }

  if (desired_offset < 0 || desired_offset >= 6) {
    display_assert("desired_type>=0 && desired_type<NUMBER_OF_HS_OBJECT_TYPES",
                   "c:\\halo\\SOURCE\\hs\\hs_runtime.c", 0x59a, true);
    system_exit(-1);
  }

  actual_mask = masks[actual_offset];
  desired_mask = masks[desired_offset];
  return (desired_mask & actual_mask) == actual_mask;
}

/* 0xcb070 */
bool hs_types_compatible(int16_t actual_type, int16_t desired_type)
{
  if (actual_type != 3 && (actual_type < 4 || actual_type >= 0x31)) {
    display_assert("actual_type==_hs_passthrough || hs_type_valid(actual_type)",
                   "c:\\halo\\SOURCE\\hs\\hs_runtime.c", 0x5a4, true);
    system_exit(-1);
  }

  if (desired_type < 4 || desired_type >= 0x31) {
    display_assert("hs_type_valid(desired_type)",
                   "c:\\halo\\SOURCE\\hs\\hs_runtime.c", 0x5a5, true);
    system_exit(-1);
  }

  if (actual_type == 3 || actual_type == desired_type)
    return true;

  if (desired_type >= 0x25 && desired_type <= 0x2a) {
    int16_t d_off = desired_type - 0x25;
    if (actual_type >= 0x25 && actual_type <= 0x2a)
      return hs_object_types_compatible((int16_t)(actual_type - 0x25), d_off);
    if (actual_type >= 0x2b && actual_type <= 0x30)
      return hs_object_types_compatible((int16_t)(actual_type - 0x2b), d_off);
    return false;
  }

  if (desired_type >= 0x2b && desired_type <= 0x30) {
    if (actual_type < 0x2b || actual_type > 0x30)
      return false;
    return hs_object_types_compatible((int16_t)(actual_type - 0x2b),
                                      (int16_t)(desired_type - 0x2b));
  }

  return *(int *)((char *)0x2f3ec0 +
                  ((int)desired_type * 0x31 + (int)actual_type) * 4) != 0;
}

/* 0xcb170 — Cast an HS value from actual_type to desired_type, returning the
 * converted value. Uses a function dispatch table at 0x2f3ec0 indexed as
 * [desired_type * 0x31 + actual_type] for most type pairs. Object handle
 * types (0x2b..0x30) to object reference types (0x25..0x2a) are handled by
 * object_name_list_get_handle which converts a handle index to a datum-based
 * reference. Passthrough (actual==3) and identity casts return value unchanged.
 *
 * Assert string confirms name: "hs_can_cast(actual_type, desired_type)"
 * at source line 0x5d8 (c:\halo\SOURCE\hs\hs_runtime.c).
 */
static int hs_can_cast(int thread_handle, int16_t actual_type,
                       int16_t desired_type, int value)
{
  char *script_name;
  char *msg;
  int (*cast_fn)(int);

  if (!hs_types_compatible(actual_type, desired_type)) {
    script_name = hs_get_thread_script_name(thread_handle);
    msg = csprintf((char *)0x5ab100,
                   "a problem occurred while executing the script %s: %s (%s)",
                   script_name, "bad typecast.",
                   "hs_can_cast(actual_type, desired_type)");
    display_assert(msg, "c:\\halo\\SOURCE\\hs\\hs_runtime.c", 0x5d8, true);
    system_exit(-1);
  }

  if (actual_type == desired_type || actual_type == 3)
    return value;

  if (desired_type >= 0x2b && desired_type <= 0x30)
    return value;

  if (desired_type >= 0x25 && desired_type <= 0x2a) {
    if (actual_type >= 0x2b && actual_type <= 0x30)
      return object_name_list_get_handle((int16_t)value);
    return value;
  }

  cast_fn = *(int (**)(int))((char *)0x2f3ec0 +
                             ((int)desired_type * 0x31 + (int)actual_type) * 4);
  return cast_fn(value);
}

/* FUN_000cb230 (0xcb230) — XBE naked draft (batch 69). */
#if defined(__clang__)
static void *(*const bcb230_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void * (*const bcb230_cc3e10)(int16_t global_index) = hs_external_global_get;
static int16_t (*const bcb230_cc3e60)(uint16_t script_ref) = hs_global_get_type;
static void (*const bcb230_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const bcb230_exitfn)(int) = system_exit;

__attribute__((naked, noinline))
void FUN_000cb230(int loop_var __attribute__((unused)))
{
  __asm__ volatile(
      "testl $0x8000, %%edi\n\t"
      "je .LFUN_000cb230_80\n\t"
      "pushl %%ebx\n\t"
      "movl %%edi, %%eax\n\t"
      "andl $0x7fff, %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "movl 0x5aa6c0, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl %%edi, %%ecx\n\t"
      "andl $0x7fff, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl %%eax, %%ebx\n\t"
      "call *%[cc3e10]\n\t"
      "pushl %%edi\n\t"
      "movl %%eax, %%esi\n\t"
      "call *%[cc3e60]\n\t"
      "movswl %%ax, %%eax\n\t"
      "addl $-5, %%eax\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpl $0x26, %%eax\n\t"
      "ja .LFUN_000cb230_79\n\t"
      "jmp *.LFUN_000cb230_jt(,%%eax,4)\n\t"
      ".LFUN_000cb230_1:\n\t"
      "movl 0x8(%%esi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_000cb230_2\n\t"
      "movzbl (%%esi), %%eax\n\t"
      "popl %%esi\n\t"
      "movb %%al, 0x4(%%ebx)\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      ".LFUN_000cb230_2:\n\t"
      "movzbl 0x26f3b2, %%eax\n\t"
      "popl %%esi\n\t"
      "movb %%al, 0x4(%%ebx)\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      ".LFUN_000cb230_3:\n\t"
      "movl 0x8(%%esi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_000cb230_4\n\t"
      "flds (%%esi)\n\t"
      "popl %%esi\n\t"
      "fstps 0x4(%%ebx)\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      ".LFUN_000cb230_4:\n\t"
      "flds 0x26f3b4\n\t"
      "popl %%esi\n\t"
      "fstps 0x4(%%ebx)\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      ".LFUN_000cb230_5:\n\t"
      "movl 0x8(%%esi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_000cb230_6\n\t"
      "movswl (%%esi), %%eax\n\t"
      "popl %%esi\n\t"
      "movw %%ax, 0x4(%%ebx)\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      ".LFUN_000cb230_6:\n\t"
      "movswl 0x26f3b8, %%eax\n\t"
      "popl %%esi\n\t"
      "movw %%ax, 0x4(%%ebx)\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      ".LFUN_000cb230_7:\n\t"
      "movl 0x8(%%esi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_000cb230_8\n\t"
      "movl (%%esi), %%esi\n\t"
      "movl %%esi, 0x4(%%ebx)\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      ".LFUN_000cb230_8:\n\t"
      "movl 0x26f3bc, %%esi\n\t"
      "movl %%esi, 0x4(%%ebx)\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      ".LFUN_000cb230_9:\n\t"
      "movl 0x8(%%esi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_000cb230_10\n\t"
      "movl (%%esi), %%esi\n\t"
      "movl %%esi, 0x4(%%ebx)\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      ".LFUN_000cb230_10:\n\t"
      "movl 0x2f1580, %%esi\n\t"
      "movl %%esi, 0x4(%%ebx)\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      ".LFUN_000cb230_11:\n\t"
      "movl 0x8(%%esi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_000cb230_12\n\t"
      "movswl (%%esi), %%eax\n\t"
      "popl %%esi\n\t"
      "movw %%ax, 0x4(%%ebx)\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      ".LFUN_000cb230_12:\n\t"
      "movswl 0x26f3c0, %%eax\n\t"
      "popl %%esi\n\t"
      "movw %%ax, 0x4(%%ebx)\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      ".LFUN_000cb230_13:\n\t"
      "movl 0x8(%%esi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_000cb230_14\n\t"
      "movswl (%%esi), %%eax\n\t"
      "popl %%esi\n\t"
      "movw %%ax, 0x4(%%ebx)\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      ".LFUN_000cb230_14:\n\t"
      "movswl 0x26f3c4, %%eax\n\t"
      "popl %%esi\n\t"
      "movw %%ax, 0x4(%%ebx)\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      ".LFUN_000cb230_15:\n\t"
      "movl 0x8(%%esi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_000cb230_16\n\t"
      "movswl (%%esi), %%eax\n\t"
      "popl %%esi\n\t"
      "movw %%ax, 0x4(%%ebx)\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      ".LFUN_000cb230_16:\n\t"
      "movswl 0x26f3c8, %%eax\n\t"
      "popl %%esi\n\t"
      "movw %%ax, 0x4(%%ebx)\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      ".LFUN_000cb230_17:\n\t"
      "movl 0x8(%%esi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_000cb230_18\n\t"
      "movswl (%%esi), %%eax\n\t"
      "popl %%esi\n\t"
      "movw %%ax, 0x4(%%ebx)\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      ".LFUN_000cb230_18:\n\t"
      "movswl 0x26f3cc, %%eax\n\t"
      "popl %%esi\n\t"
      "movw %%ax, 0x4(%%ebx)\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      ".LFUN_000cb230_19:\n\t"
      "movl 0x8(%%esi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_000cb230_20\n\t"
      "movswl (%%esi), %%eax\n\t"
      "popl %%esi\n\t"
      "movw %%ax, 0x4(%%ebx)\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      ".LFUN_000cb230_20:\n\t"
      "movswl 0x26f3d0, %%eax\n\t"
      "popl %%esi\n\t"
      "movw %%ax, 0x4(%%ebx)\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      ".LFUN_000cb230_21:\n\t"
      "movl 0x8(%%esi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_000cb230_22\n\t"
      "movswl (%%esi), %%eax\n\t"
      "popl %%esi\n\t"
      "movw %%ax, 0x4(%%ebx)\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      ".LFUN_000cb230_22:\n\t"
      "movswl 0x26f3d4, %%eax\n\t"
      "popl %%esi\n\t"
      "movw %%ax, 0x4(%%ebx)\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      ".LFUN_000cb230_23:\n\t"
      "movl 0x8(%%esi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_000cb230_24\n\t"
      "movswl (%%esi), %%eax\n\t"
      "popl %%esi\n\t"
      "movw %%ax, 0x4(%%ebx)\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      ".LFUN_000cb230_24:\n\t"
      "movswl 0x26f3d8, %%eax\n\t"
      "popl %%esi\n\t"
      "movw %%ax, 0x4(%%ebx)\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      ".LFUN_000cb230_25:\n\t"
      "movl 0x8(%%esi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_000cb230_26\n\t"
      "movl (%%esi), %%esi\n\t"
      "movl %%esi, 0x4(%%ebx)\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      ".LFUN_000cb230_26:\n\t"
      "movl 0x26f3dc, %%esi\n\t"
      "movl %%esi, 0x4(%%ebx)\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      ".LFUN_000cb230_27:\n\t"
      "movl 0x8(%%esi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_000cb230_28\n\t"
      "movswl (%%esi), %%eax\n\t"
      "popl %%esi\n\t"
      "movw %%ax, 0x4(%%ebx)\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      ".LFUN_000cb230_28:\n\t"
      "movswl 0x26f3e0, %%eax\n\t"
      "popl %%esi\n\t"
      "movw %%ax, 0x4(%%ebx)\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      ".LFUN_000cb230_29:\n\t"
      "movl 0x8(%%esi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_000cb230_30\n\t"
      "movswl (%%esi), %%eax\n\t"
      "popl %%esi\n\t"
      "movw %%ax, 0x4(%%ebx)\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      ".LFUN_000cb230_30:\n\t"
      "movswl 0x26f3e4, %%eax\n\t"
      "popl %%esi\n\t"
      "movw %%ax, 0x4(%%ebx)\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      ".LFUN_000cb230_31:\n\t"
      "movl 0x8(%%esi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_000cb230_32\n\t"
      "movswl (%%esi), %%eax\n\t"
      "popl %%esi\n\t"
      "movw %%ax, 0x4(%%ebx)\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      ".LFUN_000cb230_32:\n\t"
      "movswl 0x26f3e8, %%eax\n\t"
      "popl %%esi\n\t"
      "movw %%ax, 0x4(%%ebx)\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      ".LFUN_000cb230_33:\n\t"
      "movl 0x8(%%esi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_000cb230_34\n\t"
      "movswl (%%esi), %%eax\n\t"
      "popl %%esi\n\t"
      "movw %%ax, 0x4(%%ebx)\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      ".LFUN_000cb230_34:\n\t"
      "movswl 0x26f3ec, %%eax\n\t"
      "popl %%esi\n\t"
      "movw %%ax, 0x4(%%ebx)\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      ".LFUN_000cb230_35:\n\t"
      "movl 0x8(%%esi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_000cb230_36\n\t"
      "movswl (%%esi), %%eax\n\t"
      "popl %%esi\n\t"
      "movw %%ax, 0x4(%%ebx)\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      ".LFUN_000cb230_36:\n\t"
      "movswl 0x26f3f0, %%eax\n\t"
      "popl %%esi\n\t"
      "movw %%ax, 0x4(%%ebx)\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      ".LFUN_000cb230_37:\n\t"
      "movl 0x8(%%esi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_000cb230_38\n\t"
      "movl (%%esi), %%esi\n\t"
      "movl %%esi, 0x4(%%ebx)\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      ".LFUN_000cb230_38:\n\t"
      "movl 0x26f3f4, %%esi\n\t"
      "movl %%esi, 0x4(%%ebx)\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      ".LFUN_000cb230_39:\n\t"
      "movl 0x8(%%esi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_000cb230_40\n\t"
      "movl (%%esi), %%esi\n\t"
      "movl %%esi, 0x4(%%ebx)\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      ".LFUN_000cb230_40:\n\t"
      "movl 0x26f3f8, %%esi\n\t"
      "movl %%esi, 0x4(%%ebx)\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      ".LFUN_000cb230_41:\n\t"
      "movl 0x8(%%esi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_000cb230_42\n\t"
      "movl (%%esi), %%esi\n\t"
      "movl %%esi, 0x4(%%ebx)\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      ".LFUN_000cb230_42:\n\t"
      "movl 0x26f400, %%esi\n\t"
      "movl %%esi, 0x4(%%ebx)\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      ".LFUN_000cb230_43:\n\t"
      "movl 0x8(%%esi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_000cb230_44\n\t"
      "movl (%%esi), %%esi\n\t"
      "movl %%esi, 0x4(%%ebx)\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      ".LFUN_000cb230_44:\n\t"
      "movl 0x26f404, %%esi\n\t"
      "movl %%esi, 0x4(%%ebx)\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      ".LFUN_000cb230_45:\n\t"
      "movl 0x8(%%esi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_000cb230_46\n\t"
      "movl (%%esi), %%esi\n\t"
      "movl %%esi, 0x4(%%ebx)\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      ".LFUN_000cb230_46:\n\t"
      "movl 0x26f3fc, %%esi\n\t"
      "movl %%esi, 0x4(%%ebx)\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      ".LFUN_000cb230_47:\n\t"
      "movl 0x8(%%esi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_000cb230_48\n\t"
      "movl (%%esi), %%esi\n\t"
      "movl %%esi, 0x4(%%ebx)\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      ".LFUN_000cb230_48:\n\t"
      "movl 0x26f408, %%esi\n\t"
      "movl %%esi, 0x4(%%ebx)\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      ".LFUN_000cb230_49:\n\t"
      "movl 0x8(%%esi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_000cb230_50\n\t"
      "movl (%%esi), %%esi\n\t"
      "movl %%esi, 0x4(%%ebx)\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      ".LFUN_000cb230_50:\n\t"
      "movl 0x26f40c, %%esi\n\t"
      "movl %%esi, 0x4(%%ebx)\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      ".LFUN_000cb230_51:\n\t"
      "movl 0x8(%%esi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_000cb230_52\n\t"
      "movl (%%esi), %%esi\n\t"
      "movl %%esi, 0x4(%%ebx)\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      ".LFUN_000cb230_52:\n\t"
      "movl 0x26f410, %%esi\n\t"
      "movl %%esi, 0x4(%%ebx)\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      ".LFUN_000cb230_53:\n\t"
      "movl 0x8(%%esi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_000cb230_54\n\t"
      "movl (%%esi), %%esi\n\t"
      "movl %%esi, 0x4(%%ebx)\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      ".LFUN_000cb230_54:\n\t"
      "movl 0x26f414, %%esi\n\t"
      "movl %%esi, 0x4(%%ebx)\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      ".LFUN_000cb230_55:\n\t"
      "movl 0x8(%%esi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_000cb230_56\n\t"
      "movswl (%%esi), %%eax\n\t"
      "popl %%esi\n\t"
      "movw %%ax, 0x4(%%ebx)\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      ".LFUN_000cb230_56:\n\t"
      "movswl 0x26f418, %%eax\n\t"
      "popl %%esi\n\t"
      "movw %%ax, 0x4(%%ebx)\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      ".LFUN_000cb230_57:\n\t"
      "movl 0x8(%%esi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_000cb230_58\n\t"
      "movswl (%%esi), %%eax\n\t"
      "popl %%esi\n\t"
      "movw %%ax, 0x4(%%ebx)\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      ".LFUN_000cb230_58:\n\t"
      "movswl 0x26f41c, %%eax\n\t"
      "popl %%esi\n\t"
      "movw %%ax, 0x4(%%ebx)\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      ".LFUN_000cb230_59:\n\t"
      "movl 0x8(%%esi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_000cb230_60\n\t"
      "movswl (%%esi), %%eax\n\t"
      "popl %%esi\n\t"
      "movw %%ax, 0x4(%%ebx)\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      ".LFUN_000cb230_60:\n\t"
      "movswl 0x26f420, %%eax\n\t"
      "popl %%esi\n\t"
      "movw %%ax, 0x4(%%ebx)\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      ".LFUN_000cb230_61:\n\t"
      "movl 0x8(%%esi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_000cb230_62\n\t"
      "movswl (%%esi), %%eax\n\t"
      "popl %%esi\n\t"
      "movw %%ax, 0x4(%%ebx)\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      ".LFUN_000cb230_62:\n\t"
      "movswl 0x26f424, %%eax\n\t"
      "popl %%esi\n\t"
      "movw %%ax, 0x4(%%ebx)\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      ".LFUN_000cb230_63:\n\t"
      "movl 0x8(%%esi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_000cb230_64\n\t"
      "movswl (%%esi), %%eax\n\t"
      "popl %%esi\n\t"
      "movw %%ax, 0x4(%%ebx)\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      ".LFUN_000cb230_64:\n\t"
      "movswl 0x26f428, %%eax\n\t"
      "popl %%esi\n\t"
      "movw %%ax, 0x4(%%ebx)\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      ".LFUN_000cb230_65:\n\t"
      "movl 0x8(%%esi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_000cb230_66\n\t"
      "movl (%%esi), %%esi\n\t"
      "movl %%esi, 0x4(%%ebx)\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      ".LFUN_000cb230_66:\n\t"
      "movl 0x26f430, %%esi\n\t"
      "movl %%esi, 0x4(%%ebx)\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      ".LFUN_000cb230_67:\n\t"
      "movl 0x8(%%esi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_000cb230_68\n\t"
      "movl (%%esi), %%esi\n\t"
      "movl %%esi, 0x4(%%ebx)\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      ".LFUN_000cb230_68:\n\t"
      "movl 0x26f434, %%esi\n\t"
      "movl %%esi, 0x4(%%ebx)\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      ".LFUN_000cb230_69:\n\t"
      "movl 0x8(%%esi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_000cb230_70\n\t"
      "movl (%%esi), %%esi\n\t"
      "movl %%esi, 0x4(%%ebx)\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      ".LFUN_000cb230_70:\n\t"
      "movl 0x26f438, %%esi\n\t"
      "movl %%esi, 0x4(%%ebx)\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      ".LFUN_000cb230_71:\n\t"
      "movl 0x8(%%esi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_000cb230_72\n\t"
      "movl (%%esi), %%esi\n\t"
      "movl %%esi, 0x4(%%ebx)\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      ".LFUN_000cb230_72:\n\t"
      "movl 0x26f43c, %%esi\n\t"
      "movl %%esi, 0x4(%%ebx)\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      ".LFUN_000cb230_73:\n\t"
      "movl 0x8(%%esi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_000cb230_74\n\t"
      "movl (%%esi), %%esi\n\t"
      "movl %%esi, 0x4(%%ebx)\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      ".LFUN_000cb230_74:\n\t"
      "movl 0x26f440, %%esi\n\t"
      "movl %%esi, 0x4(%%ebx)\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      ".LFUN_000cb230_75:\n\t"
      "movl 0x8(%%esi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_000cb230_76\n\t"
      "movl (%%esi), %%esi\n\t"
      "movl %%esi, 0x4(%%ebx)\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      ".LFUN_000cb230_76:\n\t"
      "movl 0x26f444, %%esi\n\t"
      "movl %%esi, 0x4(%%ebx)\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      ".LFUN_000cb230_77:\n\t"
      "movl 0x8(%%esi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_000cb230_78\n\t"
      "movswl (%%esi), %%eax\n\t"
      "popl %%esi\n\t"
      "movw %%ax, 0x4(%%ebx)\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      ".LFUN_000cb230_78:\n\t"
      "movswl 0x26f42c, %%eax\n\t"
      "popl %%esi\n\t"
      "movw %%ax, 0x4(%%ebx)\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      ".LFUN_000cb230_79:\n\t"
      "pushl $1\n\t"
      "pushl $0x638\n\t"
      "pushl $0x2805bc\n\t"
      "pushl $0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      ".LFUN_000cb230_80:\n\t"
      "ret\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_000cb230_jt:\n\t"
      ".long .LFUN_000cb230_1\n\t"
      ".long .LFUN_000cb230_3\n\t"
      ".long .LFUN_000cb230_5\n\t"
      ".long .LFUN_000cb230_7\n\t"
      ".long .LFUN_000cb230_9\n\t"
      ".long .LFUN_000cb230_11\n\t"
      ".long .LFUN_000cb230_13\n\t"
      ".long .LFUN_000cb230_15\n\t"
      ".long .LFUN_000cb230_17\n\t"
      ".long .LFUN_000cb230_19\n\t"
      ".long .LFUN_000cb230_21\n\t"
      ".long .LFUN_000cb230_23\n\t"
      ".long .LFUN_000cb230_25\n\t"
      ".long .LFUN_000cb230_27\n\t"
      ".long .LFUN_000cb230_29\n\t"
      ".long .LFUN_000cb230_31\n\t"
      ".long .LFUN_000cb230_33\n\t"
      ".long .LFUN_000cb230_35\n\t"
      ".long .LFUN_000cb230_37\n\t"
      ".long .LFUN_000cb230_39\n\t"
      ".long .LFUN_000cb230_41\n\t"
      ".long .LFUN_000cb230_43\n\t"
      ".long .LFUN_000cb230_45\n\t"
      ".long .LFUN_000cb230_47\n\t"
      ".long .LFUN_000cb230_49\n\t"
      ".long .LFUN_000cb230_51\n\t"
      ".long .LFUN_000cb230_53\n\t"
      ".long .LFUN_000cb230_55\n\t"
      ".long .LFUN_000cb230_57\n\t"
      ".long .LFUN_000cb230_59\n\t"
      ".long .LFUN_000cb230_61\n\t"
      ".long .LFUN_000cb230_63\n\t"
      ".long .LFUN_000cb230_65\n\t"
      ".long .LFUN_000cb230_67\n\t"
      ".long .LFUN_000cb230_69\n\t"
      ".long .LFUN_000cb230_71\n\t"
      ".long .LFUN_000cb230_73\n\t"
      ".long .LFUN_000cb230_75\n\t"
      ".long .LFUN_000cb230_77\n\t"
      ".text\n\t"
      :
      : [dget] "m"(bcb230_dget), [cc3e10] "m"(bcb230_cc3e10), [cc3e60] "m"(bcb230_cc3e60), [assert] "m"(bcb230_assert), [exitfn] "m"(bcb230_exitfn)
      : "memory");
}
#else
#error "FUN_000cb230: clang naked draft required"
#endif


/* 0xcb7b0 — Write HS datum values back to external C globals, type-dispatched.
 * Reverse of FUN_000cb230: datum_ptr+4 → *ext_ptr+8. Only writes if the
 * backing pointer (ext_ptr+8) is non-NULL.
 */
static void FUN_000cb7b0(int loop_var)
{
  char *datum_ptr;
  char *ext_ptr;
  int16_t type;

  if ((loop_var & 0x8000) == 0)
    return;

  datum_ptr = (char *)datum_get(*(data_t **)0x5aa6c0, loop_var & 0x7fff);
  ext_ptr = (char *)hs_external_global_get((int16_t)(loop_var & 0x7fff));
  type = hs_global_get_type((uint16_t)loop_var);

  switch (type) {
  case 5:
    if (*(uint8_t **)(ext_ptr + 8) != NULL) {
      **(uint8_t **)(ext_ptr + 8) = *(uint8_t *)(datum_ptr + 4);
    }
    return;
  case 6:
    if (*(float **)(ext_ptr + 8) != NULL) {
      **(float **)(ext_ptr + 8) = *(float *)(datum_ptr + 4);
    }
    return;
  case 7:
  case 10:
  case 0xd:
  case 0x10:
  case 0x13:
  case 0x16:
  case 0x22:
  case 0x2b:
    if (*(int16_t **)(ext_ptr + 8) != NULL) {
      **(int16_t **)(ext_ptr + 8) = *(int16_t *)(datum_ptr + 4);
    }
    return;
  case 8:
  case 0x11:
  case 0x17:
  case 0x1a:
  case 0x1d:
  case 0x26:
  case 0x29:
    if (*(int32_t **)(ext_ptr + 8) != NULL) {
      **(int32_t **)(ext_ptr + 8) = *(int32_t *)(datum_ptr + 4);
    }
    return;
  case 9:
  case 0x18:
  case 0x1b:
  case 0x1e:
  case 0x27:
  case 0x2a:
    if (*(int32_t **)(ext_ptr + 8) != NULL) {
      **(int32_t **)(ext_ptr + 8) = *(int32_t *)(datum_ptr + 4);
    }
    return;
  case 0xb:
  case 0xe:
  case 0x14:
  case 0x20:
  case 0x23:
    if (*(int16_t **)(ext_ptr + 8) != NULL) {
      **(int16_t **)(ext_ptr + 8) = *(int16_t *)(datum_ptr + 4);
    }
    return;
  case 0xc:
  case 0xf:
  case 0x12:
  case 0x15:
  case 0x21:
  case 0x24:
    if (*(int16_t **)(ext_ptr + 8) != NULL) {
      **(int16_t **)(ext_ptr + 8) = *(int16_t *)(datum_ptr + 4);
    }
    return;
  case 0x19:
  case 0x1c:
  case 0x1f:
  case 0x25:
  case 0x28:
    if (*(int32_t **)(ext_ptr + 8) != NULL) {
      **(int32_t **)(ext_ptr + 8) = *(int32_t *)(datum_ptr + 4);
    }
    return;
  default:
    display_assert(NULL, "c:\\halo\\SOURCE\\hs\\hs_runtime.c", 0x671, true);
    system_exit(-1);
    return;
  }
}

/* 0xcb980 — Return the script name of the currently executing HS thread,
 * or "[unknown]" if no thread is currently running.
 *
 * Reads hs_runtime_globals.current_thread (int16_t at 0x46b812).  If -1, no
 * thread is executing and the fallback string is returned.  Otherwise passes
 * the index (sign-extended) to hs_get_thread_script_name and returns that
 * result, or "[unknown]" if it returns NULL.
 *
 * Key globals:
 *   0x46b812 = hs_runtime_globals.current_thread (int16_t, -1 = none)
 */
const char *hs_runtime_get_executing_thread_name(void)
{
  int16_t current_thread;
  const char *name;

  current_thread = *(int16_t *)0x46b812;
  if (current_thread == -1) {
    return "[unknown]";
  }
  name = (const char *)hs_get_thread_script_name((int)current_thread);
  if (name == NULL) {
    return "[unknown]";
  }
  return name;
}

/* 0xcbf80 — Execute a pending script-call expression on an HS thread.
 * Resolves the return type of the callee (either a built-in function or a
 * scenario script), casts the supplied value to that type via hs_can_cast,
 * writes the result into the current stack frame's dest slot, then pops the
 * top stack frame (advances thread->stack_ptr to the previous frame).
 *
 * Asserts valid_thread(thread) — checks that the thread pointer lies within
 * the thread-data array bounds and that its stack pointer is within the
 * per-thread stack window [thread+0x18, thread+0x218).
 *
 * Node layout (hs_syntax datum, EBX):
 *   +0x2 (int16_t) : function/script index (or global index when reparse set)
 *   +0x4 (int16_t) : desired return type (cast target)
 *   +0x6 (uint8_t) : flags; bit 1 (0x2) = script-reference (vs. built-in)
 *
 * Stack frame layout (top frame ptr, *(*(thread+0x10))):
 *   +0x8 (int32_t*): pointer to the destination value slot
 *
 * Scenario script element (offset 0x49c into scenario, stride 0x5c):
 *   +0x22 (int16_t): script return type
 *
 * Key globals:
 *   0x5aa6c4 = hs_thread_data  (data_t*)
 *   0x5aa6c8 = hs_syntax_data  (data_t*)
 *   0x5ab100 = scratch string buffer (for assert message)
 */
static void hs_return(int thread_handle, int value)
{
  char *thread = (char *)datum_get(*(data_t **)0x5aa6c4, thread_handle);
  char *stack_ptr = *(char **)(thread + 0x10);
  int node_handle = *(int *)(stack_ptr + 0x4);
  char *node = (char *)datum_get(*(data_t **)0x5aa6c8, node_handle);
  int16_t actual_type;
  int16_t desired_type;
  int result;
  char *top_frame;
  char *cur_sp;

  /* valid_thread(thread) — assert the thread and its stack are sane. */
  {
    data_t *td = *(data_t **)0x5aa6c4;
    char *data_base = *(char **)(((char *)td) + 0x34);
    int16_t stride = *(int16_t *)(((char *)td) + 0x2e);
    int16_t count = *(int16_t *)(((char *)td) + 0x22);
    char *data_end = data_base + (int)stride * (int)count;
    char *sp = *(char **)(thread + 0x10);
    char *frame_end = sp + 0xe + (int)*(int16_t *)(sp + 0xc);
    if (thread < data_base || thread >= data_end || sp < thread + 0x18 ||
        sp >= thread + 0x218 || frame_end > thread + 0x218) {
      const char *script_name = hs_get_thread_script_name(thread_handle);
      const char *msg =
        csprintf((char *)0x5ab100,
                 "a problem occurred while executing the script %s: %s (%s)",
                 script_name, "valid_thread(thread)", "corrupted stack.");
      display_assert(msg, "c:\\halo\\SOURCE\\hs\\hs_runtime.c", 0x325, true);
      system_exit(-1);
    }
  }

  /* Resolve the actual return type of the callee. */
  if (*(uint8_t *)(node + 0x6) & 0x2) {
    /* Script reference: look up the scenario script element. */
    int script_index = (int)*(int16_t *)(node + 0x2);
    char *scenario = (char *)global_scenario_get();
    char *script_elem =
      (char *)tag_block_get_element(scenario + 0x49c, script_index, 0x5c);
    actual_type = *(int16_t *)(script_elem + 0x22);
  } else {
    /* Built-in function: look up its return type from the function table. */
    int16_t func_index = (int16_t) * (uint16_t *)(node + 0x2);
    char *func_entry = (char *)hs_function_table_get(func_index);
    actual_type = *(int16_t *)func_entry;
  }

  /* Cast value to the desired type and store into the current frame's dest. */
  desired_type = (int16_t) * (uint16_t *)(node + 0x4);
  result = hs_can_cast(thread_handle, actual_type, desired_type, value);
  top_frame = *(char **)(*(char **)(thread + 0x10));
  *(int32_t *)(*(int32_t **)(top_frame + 0x8)) = result;

  /* Pop the top stack frame: advance thread->stack_ptr to previous frame. */
  thread = (char *)datum_get(*(data_t **)0x5aa6c4, thread_handle);
  cur_sp = *(char **)(thread + 0x10);
  *(char **)(thread + 0x10) = *(char **)cur_sp;
}

/* 0xcc0a0 — Resolve an HS global reference to its current value. Syncs
 * external globals via FUN_000cb230, then indexes into hs_globals_data.
 * External globals (bit 0x8000 set) index directly; scenario globals
 * add hs_globals_start_index (0x27d504) as a base offset.
 */
int FUN_000cc0a0(int16_t global_ref)
{
  int index;
  char *datum_ptr;

  FUN_000cb230((int)global_ref);
  if (global_ref & 0x8000) {
    index = global_ref & 0x7fff;
  } else {
    index = (global_ref & 0x7fff) + (int)*(int16_t *)0x27d504;
  }
  datum_ptr = (char *)datum_get(*(data_t **)0x5aa6c0, index);
  return *(int *)(datum_ptr + 4);
}

/* 0xcc1d0 — Evaluate an HS expression and store the result at dest_ptr.
 * If the expression is a constant, evaluates immediately via hs_can_cast.
 * If the expression is a global reference (reparse bit), resolves the global
 * first via FUN_000cc0a0 and hs_global_get_type before evaluating.
 * If the expression is non-constant, sets up the thread stack frame for
 * deferred evaluation: stores dest_ptr and expression_index in the stack
 * frame, pushes a new frame via hs_thread_push_frame, and sets the evaluation
 * flag.
 *
 * Validates thread integrity (stack bounds) and asserts dest_ptr != NULL.
 */
static void FUN_000cc1d0(int thread_handle, int expression_index,
                         void *dest_ptr)
{
  char *thread;
  char *expr;
  char *expr2;
  char *stack_ptr;
  data_t *thread_data;

  thread_data = *(data_t **)0x5aa6c4;
  thread = (char *)datum_get(thread_data, thread_handle);
  expr = (char *)datum_get(*(data_t **)0x5aa6c8, expression_index);

  /* valid_thread(thread) check — verify stack pointer is within bounds */
  {
    uint32_t pool_base = *(uint32_t *)((char *)thread_data + 0x34);
    int16_t datum_count = *(int16_t *)((char *)thread_data + 0x2e);
    int16_t datum_size = *(int16_t *)((char *)thread_data + 0x22);
    uint32_t pool_end = pool_base + (int)datum_count * (int)datum_size;
    uint32_t thr = (uint32_t)thread;
    uint32_t sp = *(uint32_t *)(thread + 0x10);
    uint32_t stack_base = thr + 0x18;
    uint32_t stack_end = thr + 0x218;

    if (thr < pool_base || thr >= pool_end || sp < stack_base ||
        sp >= stack_end || sp + (int)*(int16_t *)(sp + 0xc) + 0xe > stack_end) {
      char *script_name = hs_get_thread_script_name(thread_handle);
      char *msg =
        csprintf((char *)0x5ab100,
                 "a problem occurred while executing the script %s: %s (%s)",
                 script_name, "corrupted stack.", "valid_thread(thread)");
      display_assert(msg, "c:\\halo\\SOURCE\\hs\\hs_runtime.c", 0x2ff, true);
      system_exit(-1);
    }
  }

  if (dest_ptr == NULL) {
    display_assert("destination", "c:\\halo\\SOURCE\\hs\\hs_runtime.c", 0x300,
                   true);
    system_exit(-1);
  }

  expr2 = (char *)datum_get(*(data_t **)0x5aa6c8, expression_index);

  /* Constant expression — evaluate immediately */
  if (*(uint8_t *)(expr2 + 0x6) & 1) {
    if (*(uint8_t *)(expr + 0x6) & 4) {
      /* Global reference (reparse bit): resolve via external global */
      int resolved = FUN_000cc0a0(*(int16_t *)(expr + 0x10));
      int16_t type = hs_global_get_type((uint16_t) * (int16_t *)(expr + 0x10));
      *(int *)dest_ptr =
        hs_can_cast(thread_handle, (int)type,
                    (int)(uint16_t) * (int16_t *)(expr + 0x4), resolved);
    } else {
      *(int *)dest_ptr = hs_can_cast(
        thread_handle, (int)(uint16_t) * (int16_t *)(expr + 0x2),
        (int)(uint16_t) * (int16_t *)(expr + 0x4), *(int *)(expr + 0x10));
    }
    return;
  }

  /* Non-constant expression — set up stack frame for deferred evaluation */
  stack_ptr = *(char **)(thread + 0x10);
  *(void **)(stack_ptr + 0x8) = dest_ptr;
  hs_thread_push_frame(thread_handle);
  *(uint8_t *)(thread + 0x3) |= 1;
  *(int *)(*(char **)(thread + 0x10) + 0x4) = expression_index;
}

/* 0xcc340 — Evaluate a script-reference call. Gets the script element from
 * the scenario scripts block (scenario+0x49c), allocates 4 bytes on the
 * thread stack, then either evaluates the script's expression tree (init)
 * or pops the frame with the stored result. */
void FUN_000cc340(int16_t script_index, int thread_handle, char init)
{
  char *script;
  void *result;

  script = (char *)tag_block_get_element((char *)global_scenario_get() + 0x49c,
                                         (int)script_index, 0x5c);
  datum_get(*(data_t **)0x5aa6c4, thread_handle);
  result = hs_thread_stack_alloc(thread_handle, 4);

  if (init) {
    FUN_000cc1d0(thread_handle, *(int *)(script + 0x24), result);
  } else {
    hs_return(thread_handle, *(int *)result);
  }
}

/* 0xcc3a0 — Evaluate function arguments. Allocates a values array on the
 * thread stack, then evaluates each argument expression one-per-call into
 * the array, type-checking against the formal parameter list. Returns the
 * values array pointer when all arguments are evaluated, or 0 if still
 * processing. */
int FUN_000cc3a0(int thread_datum, int16_t param_count, int formal_params,
                 char init)
{
  char *thread;
  int *values;
  int16_t *arg_index;
  int *expr_ptr;

  thread = (char *)datum_get(*(data_t **)0x5aa6c4, thread_datum);
  values = (int *)hs_thread_stack_alloc(thread_datum, (int)param_count * 4);
  arg_index = (int16_t *)hs_thread_stack_alloc(thread_datum, 2);
  expr_ptr = (int *)hs_thread_stack_alloc(thread_datum, 4);

  if (init) {
    char *node;
    char *child;
    *arg_index = 0;
    node = (char *)datum_get(*(data_t **)0x5aa6c8,
                             *(int *)(*(char **)(thread + 0x10) + 0x4));
    child = (char *)datum_get(*(data_t **)0x5aa6c8, *(int *)(node + 0x10));
    *expr_ptr = *(int *)(child + 0x8);
  }

  if (*arg_index >= param_count) {
    if (*expr_ptr != -1) {
      char *name = hs_get_thread_script_name(thread_datum);
      char *msg =
        csprintf((char *)0x5ab100,
                 "a problem occurred while executing the script %s: %s (%s)",
                 name, "corrupted syntax tree.", "*expression_index==NONE");
      display_assert(msg, "c:\\halo\\SOURCE\\hs\\hs_runtime.c", 0x3d1, 1);
      system_exit(-1);
    }
    return (int)values;
  }

  if (*expr_ptr == -1) {
    char *name = hs_get_thread_script_name(thread_datum);
    char *msg =
      csprintf((char *)0x5ab100,
               "a problem occurred while executing the script %s: %s (%s)",
               name, "corrupted syntax tree.", "*expression_index!=NONE");
    display_assert(msg, "c:\\halo\\SOURCE\\hs\\hs_runtime.c", 0x3c4, 1);
    system_exit(-1);
  }

  {
    char *expr = (char *)datum_get(*(data_t **)0x5aa6c8, *expr_ptr);
    char *name;
    if (*(int16_t *)(expr + 0x4) !=
        *(int16_t *)(formal_params + (int)*arg_index * 2)) {
      datum_get(*(data_t **)0x5aa6c4, thread_datum);
      name = hs_get_thread_script_name(thread_datum);
      error(2, "script %s needs to be recompiled. (%s: %s)", name,
            "unexpected actual parameters.",
            "hs_syntax_get(*expression_index)->type=="
            "formal_parameters[*argument_index]");
      return (int)values;
    }
  }

  FUN_000cc1d0(thread_datum, *expr_ptr, &values[(int)*arg_index]);
  {
    char *expr = (char *)datum_get(*(data_t **)0x5aa6c8, *expr_ptr);
    *expr_ptr = *(int *)(expr + 0x8);
  }
  (*arg_index)++;
  return 0;
}

/* 0xcc560 — Evaluate an HS built-in function call by dispatching to
 * FUN_000cc3a0 with the function's formal parameter count and types
 * from the function descriptor table.
 * Returns FUN_000cc3a0's result — callers (e.g. ai_allegiance at 0xc06b0)
 * read EAX after this call to get the evaluated script value. */
int hs_macro_function_evaluate(int16_t function_index, int thread_datum,
                               char init)
{
  char *desc = (char *)hs_function_table_get(function_index);
  return FUN_000cc3a0(thread_datum, *(int16_t *)(desc + 0x18),
                      (int)(desc + 0x1a), init);
}

/* 0xcc590 — HS 'begin' evaluator. Evaluates a sequence of expressions in
 * order, returning the value of the last one. On init, sets up the expression
 * list pointer (skipping the function-name child). Each call evaluates one
 * expression and advances to the next sibling. */
void hs_evaluate_begin(int16_t function_index, int thread_datum, char init)
{
  char *thread;
  int *expr_ptr;
  int *result_ptr;

  thread = (char *)datum_get(*(data_t **)0x5aa6c4, thread_datum);
  expr_ptr = (int *)hs_thread_stack_alloc(thread_datum, 4);
  result_ptr = (int *)hs_thread_stack_alloc(thread_datum, 4);

  if (function_index != 0) {
    display_assert("function_index==_hs_function_begin",
                   "c:\\halo\\source\\hs\\hs_library_internal_runtime.h", 0x15,
                   1);
    system_exit(-1);
  }

  if (init) {
    char *node = (char *)datum_get(*(data_t **)0x5aa6c8,
                                   *(int *)(*(char **)(thread + 0x10) + 0x4));
    char *child =
      (char *)datum_get(*(data_t **)0x5aa6c8, *(int *)(node + 0x10));
    *expr_ptr = *(int *)(child + 0x8);
    *result_ptr = 0;
  }

  if (*expr_ptr != -1) {
    char *expr;
    FUN_000cc1d0(thread_datum, *expr_ptr, result_ptr);
    expr = (char *)datum_get(*(data_t **)0x5aa6c8, *expr_ptr);
    *expr_ptr = *(int *)(expr + 0x8);
    return;
  }

  hs_return(thread_datum, *result_ptr);
}

/* 0xcc660 — HS 'begin_random' evaluator.
 * Implements (begin_random <arg0> <arg1> ... <argN-1>): on each call selects
 * one not-yet-evaluated argument at random and evaluates it.  When all
 * arguments have been evaluated it pops the frame with the last result.
 *
 * Multi-phase protocol:
 *   init==true  : count the argument list, memset the used-bit array.
 *   init==false : pick the next unused slot and evaluate it; when all slots
 *                 are used call hs_return to commit the result.
 *
 * Stack allocations (via hs_thread_stack_alloc):
 *   2 bytes  — int16_t argument_count
 *   4 bytes  — uint32_t used_bits[]  (one bit per argument, up to 32)
 *   4 bytes  — int       result_value
 *
 * Random selection: random_range(get_global_random_seed_address(), 0,
 *   argument_count) gives a starting offset sVar2; then we try
 *   (i + sVar2) % argument_count for i = 0, 1, ... until we find an
 *   unset bit.
 *
 * Assert: function_index must equal 1 (_hs_function_begin_random).
 * Assert: argument_count must be < 32 (LONG_BITS).
 *
 * Globals:
 *   0x5aa6c4 = hs_thread_data  (data_t*)
 *   0x5aa6c8 = hs_syntax_data  (data_t*)
 */
void hs_evaluate_begin_random(int16_t function_index, int thread_datum,
                              char init)
{
  char *thread;
  int16_t *argument_count;
  int *used_bits;
  int *result_value;
  int16_t sVar2;
  int16_t sVar10;

  thread = (char *)datum_get(*(data_t **)0x5aa6c4, thread_datum);
  argument_count = (int16_t *)hs_thread_stack_alloc(thread_datum, 2);
  used_bits = (int *)hs_thread_stack_alloc(thread_datum, 4);
  result_value = (int *)hs_thread_stack_alloc(thread_datum, 4);

  if (function_index != 1) {
    display_assert("function_index==_hs_function_begin_random",
                   "c:\\halo\\source\\hs\\hs_library_internal_runtime.h", 0x45,
                   1);
    system_exit(-1);
  }

  if (init) {
    /* Walk the argument list to count arguments. */
    char *frame = *(char **)(thread + 0x10);
    char *fn_node =
      (char *)datum_get(*(data_t **)0x5aa6c8, *(int *)(frame + 0x4));
    char *first_child =
      (char *)datum_get(*(data_t **)0x5aa6c8, *(int *)(fn_node + 0x10));
    int arg_datum = *(int *)(first_child + 0x8);

    *argument_count = 0;
    if (arg_datum != -1) {
      do {
        char *arg = (char *)datum_get(*(data_t **)0x5aa6c8, arg_datum);
        arg_datum = *(int *)(arg + 0x8);
        *argument_count = *argument_count + 1;
      } while (arg_datum != -1);

      if (*argument_count >= 0x20) {
        display_assert("*argument_count<LONG_BITS",
                       "c:\\halo\\source\\hs\\hs_library_internal_runtime.h",
                       0x50, 1);
        system_exit(-1);
      }
    }

    csmemset(used_bits, 0, (int)((*argument_count + 0x1f) >> 5) << 2);
  }

  /* Pick a random starting offset in [0, argument_count). */
  sVar2 = random_range((unsigned int *)get_global_random_seed_address(), 0,
                       *argument_count);

  sVar10 = 0;
  if (sVar10 < *argument_count) {
    do {
      /* Compute candidate slot: (sVar10 + sVar2) % argument_count. */
      int16_t sVar11 =
        (int16_t)(((int)sVar10 + (int)sVar2) % (int)*argument_count);

      if ((used_bits[(int)sVar11 >> 5] & (1 << ((int)sVar11 & 0x1f))) == 0) {
        /* Slot not yet used: walk to the sVar11-th argument. */
        char *frame2 = *(char **)(thread + 0x10);
        char *fn_node2 =
          (char *)datum_get(*(data_t **)0x5aa6c8, *(int *)(frame2 + 0x4));
        char *first_child2 =
          (char *)datum_get(*(data_t **)0x5aa6c8, *(int *)(fn_node2 + 0x10));
        int cur_datum = *(int *)(first_child2 + 0x8);

        if (sVar11 > 0) {
          int walk = (int)(uint16_t)sVar11;
          do {
            char *node = (char *)datum_get(*(data_t **)0x5aa6c8, cur_datum);
            cur_datum = *(int *)(node + 0x8);
            walk--;
          } while (walk != 0);
        }

        /* Evaluate the chosen argument. */
        FUN_000cc1d0(thread_datum, cur_datum, result_value);

        /* Mark the slot as used. */
        used_bits[(int)sVar11 >> 5] |= 1 << ((int)sVar11 & 0x1f);
        break;
      }

      sVar10++;
    } while (sVar10 < *argument_count);
  }

  /* If all slots have been tried (counter wrapped to argument_count), pop
   * the frame and commit the result. */
  if (sVar10 == *argument_count) {
    hs_return(thread_datum, *result_value);
  }
}

/* 0xcc870 — HS 'if' evaluator. Three-phase: init evaluates the condition,
 * second call selects then/else branch, third call pops frame with result.
 * (if <condition> <then> [else]) */
void hs_evaluate_if(int16_t function_index, int thread_datum, char init)
{
  char *thread;
  char *cond_result;
  int *branch_ptr;
  int *value_ptr;

  thread = (char *)datum_get(*(data_t **)0x5aa6c4, thread_datum);
  cond_result = (char *)hs_thread_stack_alloc(thread_datum, 4);
  branch_ptr = (int *)hs_thread_stack_alloc(thread_datum, 4);
  value_ptr = (int *)hs_thread_stack_alloc(thread_datum, 4);

  if (function_index != 2) {
    display_assert("function_index==_hs_function_if",
                   "c:\\halo\\source\\hs\\hs_library_internal_runtime.h", 0x77,
                   1);
    system_exit(-1);
  }

  if (init) {
    char *node;
    char *child;
    *(int *)cond_result = 0;
    *branch_ptr = -1;
    node = (char *)datum_get(*(data_t **)0x5aa6c8,
                             *(int *)(*(char **)(thread + 0x10) + 0x4));
    child = (char *)datum_get(*(data_t **)0x5aa6c8, *(int *)(node + 0x10));
    FUN_000cc1d0(thread_datum, *(int *)(child + 0x8), cond_result);
    return;
  }

  if (*branch_ptr != -1) {
    hs_return(thread_datum, *value_ptr);
    return;
  }

  {
    int frame_expr = *(int *)(*(char **)(thread + 0x10) + 0x4);
    char *fn_name = (char *)datum_get(
      *(data_t **)0x5aa6c8,
      *(int *)((char *)datum_get(*(data_t **)0x5aa6c8, frame_expr) + 0x10));

    if (*cond_result) {
      char *cond =
        (char *)datum_get(*(data_t **)0x5aa6c8, *(int *)(fn_name + 0x8));
      *branch_ptr = *(int *)(cond + 0x8);
    } else {
      char *cond =
        (char *)datum_get(*(data_t **)0x5aa6c8, *(int *)(fn_name + 0x8));
      char *then_node =
        (char *)datum_get(*(data_t **)0x5aa6c8, *(int *)(cond + 0x8));
      *branch_ptr = *(int *)(then_node + 0x8);
      if (*branch_ptr == -1) {
        hs_return(thread_datum, 0);
        return;
      }
    }

    FUN_000cc1d0(thread_datum, *branch_ptr, value_ptr);
  }
}

/* 0xcca00 — HS 'set' evaluator. Assigns a value to a global variable.
 * Init: evaluates the value expression, storing result at the global's address.
 * Not init: syncs globals, optionally handles object-list type (0x17), pops
 * frame with the global's current value. */
void hs_evaluate_set(int16_t function_index, int thread_datum, char init)
{
  char *thread;
  char *var_node;
  int var_node_idx;
  int16_t global_type;
  int global_index;

  thread = (char *)datum_get(*(data_t **)0x5aa6c4, thread_datum);
  {
    char *frame_expr = (char *)datum_get(
      *(data_t **)0x5aa6c8, *(int *)(*(char **)(thread + 0x10) + 0x4));
    char *fn_child =
      (char *)datum_get(*(data_t **)0x5aa6c8, *(int *)(frame_expr + 0x10));
    var_node_idx = *(int *)(fn_child + 0x8);
  }
  var_node = (char *)datum_get(*(data_t **)0x5aa6c8, var_node_idx);
  hs_thread_stack_alloc(thread_datum, 4);
  global_type = hs_global_get_type((uint16_t) * (int16_t *)(var_node + 0x10));

  if (init) {
    if (global_type == 0x17)
      FUN_000ce370(FUN_000cc0a0(*(int16_t *)(var_node + 0x10)));

    global_index = (int)*(int16_t *)(var_node + 0x10) & 0x7fff;
    if (!((uint8_t)(*((uint8_t *)(var_node + 0x10) + 1)) & 0x80))
      global_index += (int)*(int16_t *)0x27d504;

    {
      char *global_datum =
        (char *)datum_get(*(data_t **)0x5aa6c0, global_index);
      char *value_expr = (char *)datum_get(*(data_t **)0x5aa6c8, var_node_idx);
      FUN_000cc1d0(thread_datum, *(int *)(value_expr + 0x8), global_datum + 4);
    }
    return;
  }

  FUN_000cb7b0(*(int16_t *)(var_node + 0x10));
  if (global_type == 0x17)
    FUN_000ce350(FUN_000cc0a0(*(int16_t *)(var_node + 0x10)));

  FUN_000cb230(*(int16_t *)(var_node + 0x10));
  {
    int ref = (int)*(int16_t *)(var_node + 0x10);
    if (ref & 0x8000)
      global_index = ref & 0x7fff;
    else
      global_index = (ref & 0x7fff) + (int)*(int16_t *)0x27d504;
  }

  {
    char *global_datum = (char *)datum_get(*(data_t **)0x5aa6c0, global_index);
    hs_return(thread_datum, *(int *)(global_datum + 4));
  }
}

/* 0xccb40 — HS 'and'/'or' evaluator. Short-circuits: AND stops on first
 * false, OR stops on first true. function_index 5 = and, 6 = or. */
void hs_evaluate_logical(int16_t function_index, int thread_datum, char init)
{
  char *thread;
  int *expr_ptr;
  char *result_ptr;
  char *running;
  char is_and;
  char new_val;

  thread = (char *)datum_get(*(data_t **)0x5aa6c4, thread_datum);
  expr_ptr = (int *)hs_thread_stack_alloc(thread_datum, 4);
  result_ptr = (char *)hs_thread_stack_alloc(thread_datum, 4);
  running = (char *)hs_thread_stack_alloc(thread_datum, 1);

  is_and = (char)(function_index == 5);

  if (function_index != 5 && function_index != 6) {
    display_assert(
      "function_index==_hs_function_and || function_index==_hs_function_or",
      "c:\\halo\\source\\hs\\hs_library_internal_runtime.h", 0xcf, 1);
    system_exit(-1);
  }

  if (init) {
    char *node = (char *)datum_get(*(data_t **)0x5aa6c8,
                                   *(int *)(*(char **)(thread + 0x10) + 0x4));
    char *child =
      (char *)datum_get(*(data_t **)0x5aa6c8, *(int *)(node + 0x10));
    *expr_ptr = *(int *)(child + 0x8);
    *running = is_and;
  } else {
    if (is_and)
      new_val = (*running && *result_ptr) ? 1 : 0;
    else
      new_val = (*running || *result_ptr) ? 1 : 0;
    *running = new_val;
  }

  if (*expr_ptr != -1 && *running == is_and) {
    FUN_000cc1d0(thread_datum, *expr_ptr, result_ptr);
    {
      char *expr = (char *)datum_get(*(data_t **)0x5aa6c8, *expr_ptr);
      *expr_ptr = *(int *)(expr + 0x8);
    }
    return;
  }

  hs_return(thread_datum, (int)(uint8_t)*running);
}

/* 0xccc70 — HS arithmetic evaluator (+, -, *, /, min, max). Accumulates
 * results across multiple operand expressions. Function indices 7-12. */
void hs_evaluate_arithmetic(int16_t function_index, int thread_datum, char init)
{
  char *thread;
  int16_t *counter;
  int *expr_ptr;
  float *operand;
  float *accum;

  thread = (char *)datum_get(*(data_t **)0x5aa6c4, thread_datum);
  counter = (int16_t *)hs_thread_stack_alloc(thread_datum, 2);
  expr_ptr = (int *)hs_thread_stack_alloc(thread_datum, 4);
  operand = (float *)hs_thread_stack_alloc(thread_datum, 4);
  accum = (float *)hs_thread_stack_alloc(thread_datum, 4);

  if (init) {
    char *node;
    char *child;
    *counter = 0;
    node = (char *)datum_get(*(data_t **)0x5aa6c8,
                             *(int *)(*(char **)(thread + 0x10) + 0x4));
    child = (char *)datum_get(*(data_t **)0x5aa6c8, *(int *)(node + 0x10));
    *expr_ptr = *(int *)(child + 0x8);
  } else {
    if (*counter == 0) {
      *accum = *operand;
    } else {
      switch (function_index) {
      case 7:
        *accum = *operand + *accum;
        break;
      case 8:
        *accum = *accum - *operand;
        break;
      case 9:
        *accum = *operand * *accum;
        break;
      case 10:
        *accum = *accum / *operand;
        break;
      case 0xb:
        if (*operand < *accum)
          *accum = *operand;
        break;
      case 0xc:
        if (*operand > *accum)
          *accum = *operand;
        break;
      default:
        display_assert(0, "c:\\halo\\source\\hs\\hs_library_internal_runtime.h",
                       0x111, 1);
        system_exit(-1);
        break;
      }
    }
    (*counter)++;
  }

  if (*expr_ptr != -1) {
    FUN_000cc1d0(thread_datum, *expr_ptr, operand);
    {
      char *expr = (char *)datum_get(*(data_t **)0x5aa6c8, *expr_ptr);
      *expr_ptr = *(int *)(expr + 0x8);
    }
    return;
  }

  hs_return(thread_datum, *(int *)accum);
}

/* 0xccdf0 — HS equal/not-equal evaluator. Evaluates two arguments of the
 * same type via FUN_000cc3a0, then compares with csmemcmp using the type's
 * size from the table at 0x26f350. function_index 0xd = equal, 0xe = not_equal.
 */
void hs_evaluate_equality(int16_t function_index, int thread_datum, char init)
{
  int16_t type;
  int16_t param_types[2];
  int *values;

  if (function_index != 0xd && function_index != 0xe) {
    display_assert("function_index==_hs_function_equal || "
                   "function_index==_hs_function_not_equal",
                   "c:\\halo\\source\\hs\\hs_library_internal_runtime.h", 0x131,
                   1);
    system_exit(-1);
  }

  {
    char *thread = (char *)datum_get(*(data_t **)0x5aa6c4, thread_datum);
    char *node = (char *)datum_get(*(data_t **)0x5aa6c8,
                                   *(int *)(*(char **)(thread + 0x10) + 0x4));
    char *child =
      (char *)datum_get(*(data_t **)0x5aa6c8, *(int *)(node + 0x10));
    char *arg1 = (char *)datum_get(*(data_t **)0x5aa6c8, *(int *)(child + 0x8));
    type = *(int16_t *)(arg1 + 0x4);
  }

  param_types[0] = type;
  param_types[1] = type;
  values = (int *)FUN_000cc3a0(thread_datum, 2, (int)param_types, init);
  if (values != 0) {
    int size = (int)*(int16_t *)(0x26f350 + (int)type * 2);
    char result = (csmemcmp(values, values + 1, size) == 0) ? 1 : 0;
    if (function_index == 0xe)
      result = (result == 0) ? 1 : 0;
    hs_return(thread_datum, (int)(uint8_t)result);
  }
}

/* 0xcced0 — HS comparison evaluator (gt/lt/ge/lte). Evaluates two arguments
 * of matching numeric type via FUN_000cc3a0 using the static param_types pair
 * at 0x46b80c/0x46b80e, then performs FPU comparison. Handles three type
 * classes: real (type==6, FLD float), long_integer (type==8, FILD dword),
 * and short_integer/enum (type==7 or 0x20..0x24, MOVSX word then FILD).
 * function_index 0xf=gt, 0x10=lt, 0x11=ge, 0x12=lte.
 *
 * The formal_params passed to FUN_000cc3a0 is a static int16_t[2] at
 * 0x0046b80c; both slots are filled with the argument's inferred type.
 * Result is committed via hs_return(thread_datum, (int)(uint8_t)result).
 */
void hs_evaluate_inequality(int16_t function_index, int thread_datum, char init)
{
  int16_t type;
  /* static param_types pair: [0x0046b80c] = type, [0x0046b80e] = type */
  int16_t *param_types = (int16_t *)0x0046b80c;
  int *values;
  char result;

  if (function_index < 0xf || function_index > 0x12) {
    display_assert(
      "function_index>=_hs_function_gt && function_index<=_hs_function_lte",
      "c:\\halo\\source\\hs\\hs_library_internal_runtime.h", 0x15d, 1);
    system_exit(-1);
  }

  {
    char *thread = (char *)datum_get(*(data_t **)0x5aa6c4, thread_datum);
    char *node = (char *)datum_get(*(data_t **)0x5aa6c8,
                                   *(int *)(*(char **)(thread + 0x10) + 0x4));
    char *child =
      (char *)datum_get(*(data_t **)0x5aa6c8, *(int *)(node + 0x10));
    char *arg1 = (char *)datum_get(*(data_t **)0x5aa6c8, *(int *)(child + 0x8));
    type = *(int16_t *)(arg1 + 0x4);
  }

  param_types[0] = type;
  param_types[1] = type;
  values = (int *)FUN_000cc3a0(thread_datum, 2, (int)param_types, init);
  if (values == NULL)
    return;

  if (type == 6) {
    /* real: load as float directly */
    float a = *(float *)values;
    float b = ((float *)values)[1];
    switch (function_index) {
    case 0xf:
      result = (a > b) ? 1 : 0;
      break; /* gt */
    case 0x10:
      result = (a < b) ? 1 : 0;
      break; /* lt */
    case 0x11:
      result = (a >= b) ? 1 : 0;
      break; /* ge */
    case 0x12:
      result = (a <= b) ? 1 : 0;
      break; /* lte */
    default:
      display_assert(0, "c:\\halo\\source\\hs\\hs_library_internal_runtime.h",
                     0x16b, 1);
      system_exit(-1);
      result = 0;
      break;
    }
  } else if (type == 8) {
    /* long_integer: load as int32 → float for comparison */
    float a = (float)*(int32_t *)values;
    float b = (float)*((int32_t *)values + 1);
    switch (function_index) {
    case 0xf:
      result = (a > b) ? 1 : 0;
      break; /* gt */
    case 0x10:
      result = (a < b) ? 1 : 0;
      break; /* lt */
    case 0x11:
      result = (a >= b) ? 1 : 0;
      break; /* ge */
    case 0x12:
      result = (a <= b) ? 1 : 0;
      break; /* lte */
    default:
      display_assert(0, "c:\\halo\\source\\hs\\hs_library_internal_runtime.h",
                     0x16e, 1);
      system_exit(-1);
      result = 0;
      break;
    }
  } else {
    /* short_integer or enum (type==7 or 0x20..0x24): load as int16 → float */
    float a;
    float b;
    if (type != 7 && (type < 0x20 || type > 0x24)) {
      display_assert("parameter_types[0]==_hs_type_short_integer || "
                     "HS_TYPE_IS_ENUM(parameter_types[0])",
                     "c:\\halo\\source\\hs\\hs_library_internal_runtime.h",
                     0x171, 1);
      system_exit(-1);
    }
    a = (float)(int)*(int16_t *)&values[0];
    b = (float)(int)*(int16_t *)&values[1];
    switch (function_index) {
    case 0xf:
      result = (a > b) ? 1 : 0;
      break; /* gt */
    case 0x10:
      result = (a < b) ? 1 : 0;
      break; /* lt */
    case 0x11:
      result = (a >= b) ? 1 : 0;
      break; /* ge */
    case 0x12:
      result = (a <= b) ? 1 : 0;
      break; /* lte */
    default:
      display_assert(0, "c:\\halo\\source\\hs\\hs_library_internal_runtime.h",
                     0x172, 1);
      system_exit(-1);
      result = 0;
      break;
    }
  }

  hs_return(thread_datum, (int)(uint8_t)result);
}

/* 0xcd0e0 — HS 'sleep' evaluator. Puts a thread (or another thread by script
 * index) to sleep for a given number of ticks. Three-phase protocol:
 *   init: evaluate the sleep-ticks expression, set phase=0.
 *   phase 0: resolve optional target-thread expression; increment phase.
 *   phase 1: apply the sleep. If target != -1, look up thread by script index
 *            via FUN_000cada0(@EDI). Negative ticks → sleep_until = -2
 * (forever). Positive ticks → sleep_until = game_time + ticks. Backs up the
 *            target's old sleep_until if sleeping a different thread.
 *
 * Stack allocations:
 *   4 bytes — sleep_ticks (int16_t value from evaluation)
 *   4 bytes — target_ref (int16_t script index of target thread, or -1)
 *   2 bytes — phase counter
 *
 * Assert: function_index == 0x13 (_hs_function_sleep).
 *
 * Globals:
 *   0x5aa6c4 = hs_thread_data (data_t*)
 *   0x5aa6c8 = hs_syntax_data (data_t*)
 */
void hs_evaluate_sleep(int16_t function_index, int thread_datum, char init)
{
  char *thread;
  int16_t *sleep_ticks;
  int16_t *target_ref;
  int16_t *phase;
  int local_thread;

  thread = (char *)datum_get(*(data_t **)0x5aa6c4, thread_datum);
  sleep_ticks = (int16_t *)hs_thread_stack_alloc(thread_datum, 4);
  target_ref = (int16_t *)hs_thread_stack_alloc(thread_datum, 4);
  phase = (int16_t *)hs_thread_stack_alloc(thread_datum, 2);
  local_thread = thread_datum;

  if (function_index != 0x13) {
    display_assert("function_index==_hs_function_sleep",
                   "c:\\halo\\source\\hs\\hs_library_internal_runtime.h", 0x189,
                   1);
    system_exit(-1);
  }

  if (init) {
    char *node = (char *)datum_get(*(data_t **)0x5aa6c8,
                                   *(int *)(*(int *)(thread + 0x10) + 4));
    char *child =
      (char *)datum_get(*(data_t **)0x5aa6c8, *(int *)(node + 0x10));
    FUN_000cc1d0(thread_datum, *(int *)(child + 0x8), sleep_ticks);
    *phase = 0;
    return;
  }

  if (*phase == 0) {
    char *node = (char *)datum_get(*(data_t **)0x5aa6c8,
                                   *(int *)(*(int *)(thread + 0x10) + 4));
    char *child =
      (char *)datum_get(*(data_t **)0x5aa6c8, *(int *)(node + 0x10));
    char *ticks_node =
      (char *)datum_get(*(data_t **)0x5aa6c8, *(int *)(child + 0x8));
    int next_expr = *(int *)(ticks_node + 0x8);
    *phase = *phase + 1;
    if (next_expr != -1) {
      FUN_000cc1d0(thread_datum, next_expr, target_ref);
      return;
    }
    *(int *)target_ref = -1;
    if (*phase == 0)
      return;
  }

  {
    int16_t ticks = *sleep_ticks;
    if (ticks != 0) {
      if (*target_ref != -1) {
        local_thread = FUN_000cada0(*target_ref);
      }
      if (local_thread != -1) {
        char *target = (char *)datum_get(*(data_t **)0x5aa6c4, local_thread);
        int new_sleep;
        if (ticks < 0) {
          new_sleep = -2;
        } else {
          new_sleep = game_time_get() + (int)ticks;
        }
        if (*(int *)(target + 0x8) != -1) {
          if (local_thread != thread_datum &&
              (*(uint8_t *)(target + 0x3) & 2) == 0) {
            *(uint8_t *)(target + 0x3) |= 2;
            *(int *)(target + 0xc) = *(int *)(target + 0x8);
          }
          target = (char *)datum_get(*(data_t **)0x5aa6c4, local_thread);
          *(int *)(target + 0x8) = new_sleep;
        }
      }
    }
    hs_return(thread_datum, 0);
  }
}

/* 0xcd2a0 — HS 'sleep_until' evaluator. Repeatedly evaluates a condition
 * expression until it becomes true or a timeout expires. Sleeps between
 * evaluations for a configurable number of ticks (default 30).
 *
 * Stack allocations:
 *   4 bytes — evaluated (char flag: 0=pending, nonzero=condition true)
 *   4 bytes — ticks_per_eval (int16_t, default 30)
 *   4 bytes — timeout_ticks (int, -1 = no timeout)
 *   4 bytes — start_time (int, game_time at init)
 *   2 bytes — phase counter
 *
 * Multi-phase:
 *   init: set defaults, evaluate optional ticks_per_eval expression.
 *   phase 0: evaluate optional timeout expression.
 *   phase 1+: re-evaluate condition; if true or timed out, wake thread.
 *             Otherwise set sleep_until = game_time + ticks, clamped to
 * deadline.
 *
 * Assert: function_index == 0x14 (_hs_function_sleep_until).
 */
void hs_evaluate_sleep_until(int16_t function_index, int thread_datum,
                             char init)
{
  char *thread;
  char *evaluated;
  int16_t *ticks_per_eval;
  int *timeout_ticks;
  int *start_time;
  int16_t *phase;
  int ticks_expr;

  thread = (char *)datum_get(*(data_t **)0x5aa6c4, thread_datum);
  evaluated = (char *)hs_thread_stack_alloc(thread_datum, 4);
  ticks_per_eval = (int16_t *)hs_thread_stack_alloc(thread_datum, 4);
  timeout_ticks = (int *)hs_thread_stack_alloc(thread_datum, 4);
  start_time = (int *)hs_thread_stack_alloc(thread_datum, 4);
  phase = (int16_t *)hs_thread_stack_alloc(thread_datum, 2);

  {
    char *node = (char *)datum_get(*(data_t **)0x5aa6c8,
                                   *(int *)(*(int *)(thread + 0x10) + 4));
    char *child =
      (char *)datum_get(*(data_t **)0x5aa6c8, *(int *)(node + 0x10));
    char *cond = (char *)datum_get(*(data_t **)0x5aa6c8, *(int *)(child + 0x8));
    ticks_expr = *(int *)(cond + 0x8);
  }

  if (function_index != 0x14) {
    display_assert("function_index==_hs_function_sleep_until",
                   "c:\\halo\\source\\hs\\hs_library_internal_runtime.h", 0x1e5,
                   1);
    system_exit(-1);
  }

  if (init) {
    *evaluated = 0;
    *start_time = game_time_get();
    *phase = 0;
    *ticks_per_eval = 0x1e;
    *timeout_ticks = -1;
    if (ticks_expr != -1) {
      FUN_000cc1d0(thread_datum, ticks_expr, ticks_per_eval);
      return;
    }
  }

  if (*phase == 0) {
    *phase = 1;
    if (ticks_expr != -1) {
      char *ticks_node = (char *)datum_get(*(data_t **)0x5aa6c8, ticks_expr);
      if (*(int *)(ticks_node + 0x8) != -1) {
        FUN_000cc1d0(thread_datum, *(int *)(ticks_node + 0x8), timeout_ticks);
        return;
      }
    }
  }

  if (*phase != 1)
    return;

  if (*evaluated == 0 && (*timeout_ticks == -1 ||
                          game_time_get() < *timeout_ticks + *start_time)) {
    char *node = (char *)datum_get(*(data_t **)0x5aa6c8,
                                   *(int *)(*(int *)(thread + 0x10) + 4));
    char *child =
      (char *)datum_get(*(data_t **)0x5aa6c8, *(int *)(node + 0x10));
    FUN_000cc1d0(thread_datum, *(int *)(child + 0x8), evaluated);
    {
      int ticks;
      int new_sleep;
      ticks = 1;
      if (*ticks_per_eval >= 1)
        ticks = (int)*ticks_per_eval;
      new_sleep = game_time_get() + ticks;
      *(int *)(thread + 0x8) = new_sleep;
      if (*timeout_ticks != -1) {
        int deadline = *timeout_ticks + *start_time;
        if (deadline <= new_sleep)
          new_sleep = deadline;
        *(int *)(thread + 0x8) = new_sleep;
      }
    }
  } else {
    hs_return(thread_datum, 0);
  }
}

/* 0xcd4a0 — HS 'inspect' evaluator. Evaluates one argument and prints its
 * value using the type-specific inspect function from the table at 0x2f3df8.
 * function_index must be 0x16 (_hs_function_inspect).
 *
 * Stack allocation: 4 bytes — result value.
 *
 * Globals:
 *   0x5aa6c4 = hs_thread_data (data_t*)
 *   0x5aa6c8 = hs_syntax_data (data_t*)
 *   0x2f3df8 = hs_type_inspect_table (code*[])
 */
void hs_evaluate_inspect(int16_t function_index, int thread_datum, char init)
{
  char *thread;
  int *result_ptr;
  char local_404[1024];

  thread = (char *)datum_get(*(data_t **)0x5aa6c4, thread_datum);
  result_ptr = (int *)hs_thread_stack_alloc(thread_datum, 4);

  if (function_index != 0x16) {
    display_assert("function_index==_hs_function_inspect",
                   "c:\\halo\\source\\hs\\hs_library_internal_runtime.h", 700,
                   1);
    system_exit(-1);
  }

  {
    int first_arg = *(int *)(*(int *)(thread + 0x10) + 4);
    if (init) {
      char *node = (char *)datum_get(*(data_t **)0x5aa6c8, first_arg);
      char *child =
        (char *)datum_get(*(data_t **)0x5aa6c8, *(int *)(node + 0x10));
      FUN_000cc1d0(thread_datum, *(int *)(child + 0x8), result_ptr);
      return;
    }

    {
      char *node = (char *)datum_get(*(data_t **)0x5aa6c8, first_arg);
      char *child =
        (char *)datum_get(*(data_t **)0x5aa6c8, *(int *)(node + 0x10));
      char *value_node =
        (char *)datum_get(*(data_t **)0x5aa6c8, *(int *)(child + 0x8));
      int16_t type = *(int16_t *)(value_node + 0x4);
      typedef void (*inspect_fn)(int16_t, int, char *);
      inspect_fn fn = ((inspect_fn *)0x2f3df8)[(int)type];
      if (fn != NULL) {
        fn(type, *result_ptr, local_404);
        console_printf(0, local_404);
      }
    }
    hs_return(thread_datum, 0);
  }
}

/* 0xcd5a0 — HS object-to-unit type converter. Evaluates one argument,
 * checks if the object's type matches the target conversion mask from
 * the table at 0x26f320. Returns the object if compatible, NONE if not.
 * function_index 0x17 = object_to_unit. */
void hs_evaluate_object_cast_up(int16_t function_index, int thread_datum,
                                char init)
{
  char *thread;
  int *result_ptr;

  thread = (char *)datum_get(*(data_t **)0x5aa6c4, thread_datum);
  result_ptr = (int *)hs_thread_stack_alloc(thread_datum, 4);

  if (function_index < 0x17 || function_index > 0x17) {
    display_assert("function_index>=_hs_function_object_to_unit && "
                   "function_index<=_hs_function_object_to_unit",
                   "c:\\halo\\source\\hs\\hs_library_internal_runtime.h", 0x2dc,
                   1);
    system_exit(-1);
  }

  if (init) {
    char *node = (char *)datum_get(*(data_t **)0x5aa6c8,
                                   *(int *)(*(char **)(thread + 0x10) + 0x4));
    char *child =
      (char *)datum_get(*(data_t **)0x5aa6c8, *(int *)(node + 0x10));
    FUN_000cc1d0(thread_datum, *(int *)(child + 0x8), result_ptr);
    return;
  }

  if (*result_ptr == -1) {
    hs_return(thread_datum, -1);
    return;
  }

  {
    char *obj = (char *)object_get_and_verify_type(*result_ptr, -1);
    int type_idx = (int)(int16_t)(function_index - 0x16);
    int type_bit = 1 << (*(uint8_t *)(obj + 0x64) & 0x1f);
    int type_mask = (int)*(int16_t *)(0x26f320 + type_idx * 2);

    const char *tag_name;
    if (type_mask & type_bit) {
      hs_return(thread_datum, *result_ptr);
      return;
    }

    tag_name = tag_get_name(*(int *)obj);
    error(2, "attempt to convert object %s to type %s", tag_name,
          *(const char **)(0x2f153c + type_idx * 4));
    hs_return(thread_datum, -1);
  }
}

/* 0xcd6c0 — HS debug_string evaluator. Collects up to 32 evaluated arguments
 * into a buffer, then dispatches to one of three output functions based on
 * function_index: 0x18 → ai_debug_communication_suppress, 0x19 →
 * ai_debug_communication_ignore, 0x1a → ai_debug_communication_focus.
 *
 * Stack allocations:
 *   4 bytes — current expression datum (int*)
 *   4 bytes — argument count (int*)
 *   128 bytes — argument values array (int[32])
 *
 * Assert: function_index in [0x18..0x1a] (_hs_function_debug_string range).
 */
void hs_evaluate_debug_string(int16_t function_index, int thread_datum,
                              char init)
{
  char *thread;
  int *cur_expr;
  int *arg_count;
  int arg_buf;

  thread = (char *)datum_get(*(data_t **)0x5aa6c4, thread_datum);
  cur_expr = (int *)hs_thread_stack_alloc(thread_datum, 4);
  arg_count = (int *)hs_thread_stack_alloc(thread_datum, 4);
  arg_buf = (int)hs_thread_stack_alloc(thread_datum, 0x80);

  if (function_index < 0x18 || function_index > 0x1a) {
    display_assert("(function_index>=_hs_function_debug_string__first) && "
                   "(function_index<=_hs_function_debug_string__last)",
                   "c:\\halo\\source\\hs\\hs_library_internal_runtime.h", 0x304,
                   1);
    system_exit(-1);
  }

  if (init) {
    char *node = (char *)datum_get(*(data_t **)0x5aa6c8,
                                   *(int *)(*(int *)(thread + 0x10) + 4));
    char *child =
      (char *)datum_get(*(data_t **)0x5aa6c8, *(int *)(node + 0x10));
    *cur_expr = *(int *)(child + 0x8);
    *arg_count = 0;
    csmemset((void *)arg_buf, 0, 0x80);
  }

  if (*cur_expr != -1 && *arg_count < 0x20) {
    int result;
    FUN_000cc1d0(thread_datum, *cur_expr, &result);
    {
      char *expr_node = (char *)datum_get(*(data_t **)0x5aa6c8, *cur_expr);
      *cur_expr = *(int *)(expr_node + 0x8);
    }
    *(int *)(arg_buf + *arg_count * 4) = result;
    *arg_count = *arg_count + 1;
    return;
  }

  {
    typedef void (*debug_string_fn)(int, int);
    debug_string_fn fn;
    if (function_index == 0x18) {
      fn = (debug_string_fn)0x4a650;
    } else if (function_index == 0x19) {
      fn = (debug_string_fn)0x4a680;
    } else if (function_index == 0x1a) {
      fn = (debug_string_fn)0x4a6b0;
    } else {
      display_assert(0, "c:\\halo\\source\\hs\\hs_library_internal_runtime.h",
                     0x330, 1);
      system_exit(-1);
      hs_return(thread_datum, -1);
      return;
    }
    if (fn != NULL)
      fn(*arg_count, arg_buf);
  }
  hs_return(thread_datum, -1);
}

/* FUN_000cd840 (0xcd840) — XBE naked draft (batch 69). */
#if defined(__clang__)
static void *(*const bcd840_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static scenario_t * (*const bcd840_c18e380)(void) = global_scenario_get;
static void *(*const bcd840_elem)(void *, int, int) = tag_block_get_element;
static char * (*const bcd840_ccaa80)(int thread_index) = hs_get_thread_script_name;
static char * (*const bcd840_c8d9d0)(char *buffer, const char *format, ...) = csprintf;
static void (*const bcd840_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const bcd840_exitfn)(int) = system_exit;
static void * (*const bcd840_ccaba0)(int thread_handle, int size) = hs_thread_stack_alloc;
static void (*const bcd840_ccc1d0)(int thread_handle, int expression_index, void *dest_ptr) = FUN_000cc1d0;
static bool (*const bcd840_cb5be0)(void) = game_in_progress;
static int (*const bcd840_gtime)(void) = game_time_get;
static void * (*const bcd840_cc3d00)(int16_t function_index) = hs_function_table_get;
static void (*const bcd840_ccbf80)(int thread_handle, int value) = hs_return;
static void (*const bcd840_ccaa30)(int thread_handle) = FUN_000caa30;

__attribute__((naked, noinline))
void FUN_000cd840(int thread_handle __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xc, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x5aa6c4, %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%edi\n\t"
      "movw %%si, 0x46b812\n\t"
      "movb 0x2(%%edi), %%al\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "movl %%ebx, -0x4(%%ebp)\n\t"
      "jne .LFUN_000cd840_2\n\t"
      "movl 0x4(%%edi), %%ecx\n\t"
      "pushl $0x5c\n\t"
      "pushl %%ecx\n\t"
      "call *%[c18e380]\n\t"
      "addl $0x49c, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "movw 0x20(%%eax), %%ax\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpw $3, %%ax\n\t"
      "je .LFUN_000cd840_1\n\t"
      "cmpw $4, %%ax\n\t"
      "jne .LFUN_000cd840_2\n\t"
      ".LFUN_000cd840_1:\n\t"
      "pushl $1\n\t"
      "pushl $0x2ba\n\t"
      "pushl $0x2805bc\n\t"
      "pushl $0x280bc0\n\t"
      "pushl $0x280b98\n\t"
      "call *%[ccaa80]\n\t"
      "pushl %%eax\n\t"
      "pushl $0x2806c8\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x14, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000cd840_2:\n\t"
      "movl 0x5aa6c4, %%eax\n\t"
      "movl 0x34(%%eax), %%ecx\n\t"
      "cmpl %%ecx, %%edi\n\t"
      "jb .LFUN_000cd840_3\n\t"
      "movswl 0x2e(%%eax), %%edx\n\t"
      "movswl 0x22(%%eax), %%eax\n\t"
      "imull %%eax, %%edx\n\t"
      "addl %%ecx, %%edx\n\t"
      "cmpl %%edx, %%edi\n\t"
      "jae .LFUN_000cd840_3\n\t"
      "movl 0x10(%%edi), %%eax\n\t"
      "leal 0x18(%%edi), %%ecx\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jb .LFUN_000cd840_3\n\t"
      "leal 0x218(%%edi), %%ecx\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jae .LFUN_000cd840_3\n\t"
      "movswl 0xc(%%eax), %%edx\n\t"
      "leal 0xe(%%edx,%%eax,1), %%eax\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jbe .LFUN_000cd840_4\n\t"
      ".LFUN_000cd840_3:\n\t"
      "pushl $1\n\t"
      "pushl $0x2bd\n\t"
      "pushl $0x2805bc\n\t"
      "pushl $0x2807e4\n\t"
      "pushl $0x2807d0\n\t"
      "call *%[ccaa80]\n\t"
      "pushl %%eax\n\t"
      "pushl $0x2806c8\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x14, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000cd840_4:\n\t"
      "movl 0x10(%%edi), %%eax\n\t"
      "movl %%ebx, 0x8(%%edi)\n\t"
      "leal 0x18(%%edi), %%ebx\n\t"
      "cmpl %%ebx, %%eax\n\t"
      "jne .LFUN_000cd840_6\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_000cd840_5\n\t"
      "pushl $1\n\t"
      "pushl $0x2c3\n\t"
      "pushl $0x2805bc\n\t"
      "pushl $0x25bb40\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000cd840_5:\n\t"
      "movl 0x10(%%edi), %%ecx\n\t"
      "pushl $4\n\t"
      "movl %%esi, %%eax\n\t"
      "movw $0, 0xc(%%ecx)\n\t"
      "call *%[ccaba0]\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "pushl %%eax\n\t"
      "movl 0x24(%%edx), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl %%esi, %%eax\n\t"
      "call *%[ccc1d0]\n\t"
      "movl 0x10(%%edi), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl %%ebx, %%eax\n\t"
      "je .LFUN_000cd840_13\n\t"
      "jmp .LFUN_000cd840_6\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_000cd840_6:\n\t"
      "movl 0x8(%%edi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jl .LFUN_000cd840_13\n\t"
      "call *%[cb5be0]\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000cd840_7\n\t"
      "call *%[gtime]\n\t"
      "cmpl %%eax, 0x8(%%edi)\n\t"
      "jg .LFUN_000cd840_13\n\t"
      ".LFUN_000cd840_7:\n\t"
      "movb 0x46b810, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000cd840_13\n\t"
      "movl 0x10(%%edi), %%ecx\n\t"
      "movl 0x4(%%ecx), %%edx\n\t"
      "movl 0x5aa6c8, %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movb 0x3(%%edi), %%bl\n\t"
      "movl 0x10(%%edi), %%ecx\n\t"
      "movw $0, 0xc(%%ecx)\n\t"
      "andb $0xfe, 0x3(%%edi)\n\t"
      "movb 0x6(%%eax), %%cl\n\t"
      "andb $1, %%bl\n\t"
      "addl $8, %%esp\n\t"
      "testb $2, %%cl\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "movb %%bl, -0x8(%%ebp)\n\t"
      "jne .LFUN_000cd840_9\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x2(%%eax), %%dx\n\t"
      "pushl %%edx\n\t"
      "call *%[cc3d00]\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl 0xc(%%ebx), %%eax\n\t"
      "addl $4, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_000cd840_8\n\t"
      "pushl $1\n\t"
      "pushl $0x2d8\n\t"
      "pushl $0x2805bc\n\t"
      "pushl $0x280b84\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000cd840_8:\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x2(%%ecx), %%dx\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%edx\n\t"
      "call *0xc(%%ebx)\n\t"
      "addl $0xc, %%esp\n\t"
      "jmp .LFUN_000cd840_12\n\t"
      ".LFUN_000cd840_9:\n\t"
      "movw 0x2(%%eax), %%ax\n\t"
      "movswl %%ax, %%eax\n\t"
      "pushl $0x5c\n\t"
      "pushl %%eax\n\t"
      "call *%[c18e380]\n\t"
      "addl $0x49c, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl 0x5aa6c4, %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%ecx\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "call *%[dget]\n\t"
      "pushl $4\n\t"
      "movl %%esi, %%eax\n\t"
      "call *%[ccaba0]\n\t"
      "addl $0x18, %%esp\n\t"
      "testb %%bl, %%bl\n\t"
      "je .LFUN_000cd840_10\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "pushl %%eax\n\t"
      "movl 0x24(%%edx), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl %%esi, %%eax\n\t"
      "call *%[ccc1d0]\n\t"
      "jmp .LFUN_000cd840_11\n\t"
      ".LFUN_000cd840_10:\n\t"
      "movl (%%eax), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "call *%[ccbf80]\n\t"
      ".LFUN_000cd840_11:\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_000cd840_12:\n\t"
      "movl 0x10(%%edi), %%ecx\n\t"
      "leal 0x18(%%edi), %%eax\n\t"
      "cmpl %%eax, %%ecx\n\t"
      "jne .LFUN_000cd840_6\n\t"
      ".LFUN_000cd840_13:\n\t"
      "movl 0x10(%%edi), %%ecx\n\t"
      "leal 0x18(%%edi), %%eax\n\t"
      "cmpl %%eax, %%ecx\n\t"
      "jne .LFUN_000cd840_16\n\t"
      "movb 0x2(%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_000cd840_15\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "movw 0x20(%%edx), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "je .LFUN_000cd840_14\n\t"
      "cmpw $1, %%ax\n\t"
      "jne .LFUN_000cd840_16\n\t"
      ".LFUN_000cd840_14:\n\t"
      "movl $0xffffffff, %%eax\n\t"
      "movl %%eax, 0x8(%%edi)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movw %%ax, 0x46b812\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000cd840_15:\n\t"
      "cmpb $2, %%al\n\t"
      "jne .LFUN_000cd840_16\n\t"
      "call *%[ccaa30]\n\t"
      ".LFUN_000cd840_16:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movw $0xffff, 0x46b812\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [dget] "m"(bcd840_dget), [c18e380] "m"(bcd840_c18e380), [elem] "m"(bcd840_elem), [ccaa80] "m"(bcd840_ccaa80), [c8d9d0] "m"(bcd840_c8d9d0), [assert] "m"(bcd840_assert), [exitfn] "m"(bcd840_exitfn), [ccaba0] "m"(bcd840_ccaba0), [ccc1d0] "m"(bcd840_ccc1d0), [cb5be0] "m"(bcd840_cb5be0), [gtime] "m"(bcd840_gtime), [cc3d00] "m"(bcd840_cc3d00), [ccbf80] "m"(bcd840_ccbf80), [ccaa30] "m"(bcd840_ccaa30)
      : "memory");
}
#else
#error "FUN_000cd840: clang naked draft required"
#endif


/* Initialize HaloScript runtime for a new map. Deletes all existing thread
 * data, creates an internal initialization thread, runs all global
 * initialization scripts (type 0x17), then starts continuous/dormant script
 * threads. Asserts if a global init script attempts to sleep.
 *
 * Scenario globals block is at scenario+0x49c (element size 0x5c).
 * Scenario scripts block is at scenario+0x4a8 (element size 0x5c).
 *
 * Key globals:
 *   0x5aa6c4 = hs_thread_data (data_t*)
 *   0x5aa6c0 = hs_globals_data (data_t*)
 *   0x5aa6c8 = hs_syntax_data (data_t*)
 *   0x46b810 = hs_runtime_globals.executing (uint8_t)
 *   0x46b812 = hs_runtime_globals.current_thread (int16_t)
 *   0x27d504 = hs_globals_start_index (int16_t)
 *   0x326a08 = global_scenario_index (int)
 *   0x5aa6a0 = hs_runtime return values buffer (0x20 bytes)
 */
void hs_runtime_initialize_for_new_map(void)
{
  int thread_index;
  char *internal_thread;
  char *scenario;
  char *script_element;
  char *datum_ptr;
  char *stack_frame;
  short loop_var;
  int loop_idx;

  /* Phase 1: wipe all thread data, mark runtime as executing. */
  data_delete_all(*(data_t **)0x5aa6c4);
  *(uint8_t *)0x46b810 = 1;
  *(int16_t *)0x46b812 = -1;

  /* Phase 2: allocate the internal initialization thread. */
  thread_index = data_new_at_index(*(data_t **)0x5aa6c4);
  if (thread_index != -1) {
    internal_thread = (char *)datum_get(*(data_t **)0x5aa6c4, thread_index);
    *(int *)(internal_thread + 0x10) = (int)(internal_thread + 0x18);
    *(int *)(internal_thread + 0x18) = 0;
    stack_frame = *(char **)(internal_thread + 0x10);
    *(int16_t *)(stack_frame + 0xc) = 0;
    *(int *)(stack_frame + 0x4) = -1;
    *(uint8_t *)(internal_thread + 0x2) = 1;
    *(int *)(internal_thread + 0x4) = -1;
    *(uint8_t *)(internal_thread + 0x3) = 0;
    *(int *)(internal_thread + 0x8) = 0;
  }

  /* Phase 3: run global initialization scripts if a scenario is loaded. */
  if (*(int *)0x326a08 != -1) {
    scenario = (char *)global_scenario_get();
    internal_thread = (char *)datum_get(*(data_t **)0x5aa6c4, thread_index);

    loop_var = 0;
    if (*(int *)(scenario + 0x4a8) > 0) {
      loop_idx = 0;
      do {
        /* Get the current script element from the scripts block. */
        {
          char *block_base = (char *)global_scenario_get();
          block_base += 0x4a8;
          script_element =
            (char *)tag_block_get_element(block_base, loop_idx, 0x5c);
        }

        /* Compute the global datum index: if bit 15 set on loop_var, use
         * raw index; otherwise add hs_globals_start_index. */
        {
          int raw_idx = loop_idx & 0x7fff;
          int datum_idx;
          if (loop_var & (int16_t)0x8000)
            datum_idx = raw_idx;
          else
            datum_idx = (int)*(int16_t *)0x27d504 + raw_idx;

          data_new_datum(*(data_t **)0x5aa6c0, (int)(datum_idx | 0xaced0000));

          /* Re-derive datum_idx (same logic, needed after the call). */
          if (loop_var & (int16_t)0x8000)
            datum_idx = raw_idx;
          else
            datum_idx = (int)*(int16_t *)0x27d504 + raw_idx;

          datum_ptr = (char *)datum_get(*(data_t **)0x5aa6c0, datum_idx);
        }

        /* Reset internal thread state and call hs_default_value.
         * hs_default_value (0xcc1d0) takes EAX=thread_index,
         * stack args: (hs_type, dest_ptr). */
        *(int *)(internal_thread + 0x4) = -1;
        {
          char *sf = *(char **)(internal_thread + 0x10);
          *(int16_t *)(sf + 0xc) = 0;
        }
        FUN_000cc1d0(thread_index, *(int *)(script_element + 0x28),
                     (void *)(datum_ptr + 4));

        /* If the script was successfully parsed (bit 0 of byte +3),
         * execute it. */
        if (*(uint8_t *)(internal_thread + 0x3) & 1) {
          FUN_000cd840(thread_index);

          /* If this is a global initialization script (type == 0x17),
           * store the result back into the globals. */
          if (*(int16_t *)(script_element + 0x20) == 0x17) {
            FUN_000cb230((int)loop_var);

            /* Re-derive datum pointer and evaluate the expression.
             * The original code re-calls datum_get here because EDI
             * (internal_thread) was clobbered by cb230. */
            {
              int raw_idx = loop_idx & 0x7fff;
              int datum_idx;
              if (loop_var & (int16_t)0x8000)
                datum_idx = raw_idx;
              else
                datum_idx = (int)*(int16_t *)0x27d504 + raw_idx;

              datum_ptr = (char *)datum_get(*(data_t **)0x5aa6c0, datum_idx);
              FUN_000ce350(*(int *)(datum_ptr + 0x4));
            }
            /* Restore internal_thread (original saved in [EBP-0x10],
             * we re-derive via datum_get). */
            internal_thread =
              (char *)datum_get(*(data_t **)0x5aa6c4, thread_index);
          }

          /* Assert: global init scripts must not sleep.
           * hs_get_thread_script_name (0xcaa80) takes ESI=thread_index
           * as register arg and returns the script name string. */
          if (*(int *)(internal_thread + 0x8) != 0) {
            char *script_name = hs_get_thread_script_name(thread_index);
            display_assert(
              csprintf(error_string_buffer,
                       "a problem occurred while executing the script "
                       "%s: %s (%s)",
                       script_name,
                       "a global initialization attempted to sleep.",
                       "internal_thread->sleep_until==0"),
              "c:\\halo\\SOURCE\\hs\\hs_runtime.c", 0xe7, true);
            system_exit(-1);
          }
        }

        FUN_000cb7b0((int)loop_var);

        loop_var++;
        loop_idx = (int)(int16_t)loop_var;
        scenario = (char *)global_scenario_get();
      } while (loop_idx < *(int *)(scenario + 0x4a8));
    }

    /* Verify internal thread type and delete it. */
    internal_thread = (char *)datum_get(*(data_t **)0x5aa6c4, thread_index);
    if (*(uint8_t *)(internal_thread + 0x2) == 0) {
      display_assert(
        "hs_thread_get(thread_index)->type!=_hs_thread_type_script",
        "c:\\halo\\SOURCE\\hs\\hs_runtime.c", 0x290, true);
      system_exit(-1);
    }
    datum_delete(*(data_t **)0x5aa6c4, thread_index);

    /* Phase 4: start script threads for non-static/startup scripts.
     * Iterates the scenario globals block (offset 0x49c). Scripts with
     * type 3 (static) or 4 (startup) are skipped; others get a new
     * hs thread via ca940 which takes EBX=script_index as register arg
     * and one stack arg (type=0). */
    {
      short script_loop = 0;
      int script_idx = 0;
      char *scripts_block = scenario + 0x49c;
      if (*(int *)scripts_block > 0) {
        do {
          char *script =
            (char *)tag_block_get_element(scripts_block, script_idx, 0x5c);
          int16_t script_type = *(int16_t *)(script + 0x20);
          if (script_type != 3 && script_type != 4) {
            int result = hs_thread_new(script_idx, 0);
            if (result == -1) {
              error(0, "ran out of script threads.");
            }
          }
          script_loop++;
          script_idx = (int)(int16_t)script_loop;
        } while (script_idx < *(int *)scripts_block);
      }
    }
  }

  /* Phase 5: clear the return values buffer. */
  csmemset((void *)0x5aa6a0, 0, 0x20);
}

/* Execute a HaloScript expression at runtime. Allocates a new thread,
 * initializes it as a runtime thread (type 2), sets up the default value
 * for the expression type, and either executes it immediately or returns
 * the result value. Returns -1 if the runtime is not active, the
 * thread_index is invalid, or no threads are available.
 *
 * 0xcc1d0 = hs_default_value (@EAX=thread_handle, stack: expression_index,
 *           dest_ptr)
 * 0xcd840 = hs_execute_thread (@EAX=thread_handle)
 *
 * Globals:
 *   0x46b810 = hs_runtime_globals.executing (uint8_t)
 *   0x5aa6c4 = hs_thread_data (data_t*)
 */
int hs_runtime_execute(int thread_index)
{
  int thread_handle;
  char *thread_ptr;

  if (*(uint8_t *)0x46b810 == 0 || thread_index == -1)
    return -1;

  thread_handle = data_new_at_index(*(data_t *volatile *)0x5aa6c4);

  if (thread_handle == -1) {
    error(2, "there are not enough threads to execute that command.");
    return -1;
  }

  thread_ptr = (char *)datum_get(*(data_t *volatile *)0x5aa6c4, thread_handle);

  /* Initialize thread structure. */
  *(int *)(thread_ptr + 0x10) = (int)(thread_ptr + 0x18);
  *(int *)(thread_ptr + 0x18) = 0;
  {
    char *sf = *(char **)(thread_ptr + 0x10);
    *(int16_t *)(sf + 0xc) = 0;
    *(int *)(sf + 0x4) = -1;
  }
  *(uint8_t *)(thread_ptr + 0x2) = 2; /* runtime thread */
  *(int *)(thread_ptr + 0x4) = -1;
  *(uint8_t *)(thread_ptr + 0x3) = 0;
  *(int *)(thread_ptr + 0x8) = 0;

  /* Re-derive thread pointer (original does a second datum_get). */
  thread_ptr = (char *)datum_get(*(data_t *volatile *)0x5aa6c4, thread_handle);

  FUN_000cc1d0(thread_handle, thread_index, (void *)(thread_ptr + 0x14));

  if (*(uint8_t *)(thread_ptr + 0x3) & 1) {
    /* Thread needs execution — run it. */
    FUN_000cd840(thread_handle);
    return -1;
  }

  /* Return the result value stored at thread+0x14. */
  return *(int *)(thread_ptr + 0x14);
}

/* Initialize HaloScript runtime data structures. Calls data_delete_all
 * on both hs object list data pools.
 *
 * 0x5aa698 = hs_object_list_header_data (data_t*)
 * 0x5aa694 = hs_object_list_reference_data (data_t*)
 */
void hs_runtime_initialize(void)
{
  data_delete_all(*(data_t **)0x5aa698);
  data_delete_all(*(data_t **)0x5aa694);
}

/* Dispose HaloScript runtime data structures. Calls data_make_invalid
 * on both hs object list data pools.
 *
 * 0x5aa698 = hs_object_list_header_data (data_t*)
 * 0x5aa694 = hs_object_list_reference_data (data_t*)
 */
void hs_runtime_dispose(void)
{
  data_make_invalid(*(data_t **)0x5aa698);
  data_make_invalid(*(data_t **)0x5aa694);
}

/* 0x000ce320 — object_list_iterator_next
 * Advances an object-list iterator to the next entry.
 * Returns the object datum handle, or -1 if the list is exhausted.
 * Updates *iter_state to point to the next node's link.
 *
 * Confirmed: datum_get(0x5aa694, *iter_state) at 0xce335.
 * Confirmed: node+0x8 = next link, node+0x4 = object handle.
 */
int FUN_000ce320(int param_1, int *param_2)
{
  char *node;

  if (*param_2 != -1) {
    node = (char *)datum_get(*(data_t **)0x5aa694, *param_2);
    *param_2 = *(int *)(node + 8);
    return *(int *)(node + 4);
  }
  return -1;
}

/* 0xce350 */
void FUN_000ce350(int expression_datum)
{
  if (expression_datum != -1) {
    char *node = (char *)datum_get(*(data_t **)0x5aa698, expression_datum);
    *(int16_t *)(node + 0x4) += 1;
  }
}

/* 0xce370 — Decrement the reference count of an object list entry.
 * Asserts that the count is > 0 before decrementing.
 * Source: object_lists.c line 0xa5.
 *
 * Globals:
 *   0x5aa698 = hs_object_list_data (data_t*)
 */
void FUN_000ce370(int expression_datum)
{
  if (expression_datum != -1) {
    char *node = (char *)datum_get(*(data_t **)0x5aa698, expression_datum);
    if (*(int16_t *)(node + 0x4) < 1) {
      display_assert("list->reference_count>0",
                     "c:\\halo\\SOURCE\\hs\\object_lists.c", 0xa5, 1);
      system_exit(-1);
    }
    *(int16_t *)(node + 0x4) -= 1;
  }
}

/* 0x000ce450 — object_list_iterator_first
 * Initializes an object-list iterator and returns the first object handle.
 * Returns -1 if the list is empty or param_1 is -1.
 *
 * Confirmed: datum_get(0x5aa698, param_1) at 0xce466.
 * Confirmed: datum_get(0x5aa694, first_link) at 0xce483.
 * Confirmed: node+0x8 = head link (list entry), then node+0x8 = next, node+0x4
 * = handle.
 */
int FUN_000ce450(int param_1, int *param_2)
{
  char *node;
  int first_link;

  if (param_1 != -1) {
    node = (char *)datum_get(*(data_t **)0x5aa698, param_1);
    first_link = *(int *)(node + 8);
    *param_2 = first_link;
    if (first_link != -1) {
      node = (char *)datum_get(*(data_t **)0x5aa694, first_link);
      *param_2 = *(int *)(node + 8);
      return *(int *)(node + 4);
    }
  }
  return -1;
}

/* FUN_000c95c0 (0xc95c0) — readable C lift from XBE leaf (!value as bool). */
char FUN_000c95c0(char value)
{
  return value == 0;
}

/* FUN_000c95d0 (0xc95d0) — readable C lift: terminal_output with global color. */
void FUN_000c95d0(const char *text)
{
  void (*out)(void *color, const char *msg) =
      (void (*)(void *, const char *))terminal_output;
  out(*(void **)0x2ee6d4, text);
}

/* FUN_000c9990 (0xc9990) — readable C lift. */
void FUN_000c9990(int16_t name_index)
{
  int handle;
  void *elem;
  if (name_index == (int16_t)-1)
    return;
  handle = object_name_list_get_handle(name_index);
  if (handle == -1) {
    object_new_by_name(name_index);
    return;
  }
  elem = tag_block_get_element(
      (char *)global_scenario_get() + 0x204, (int)name_index, 0x24);
  error(2, (const char *)0x280378, elem);
}
/* hs_object_iterate_names_containing (0xc9b10) — readable C lift. */
void hs_object_iterate_names_containing(void *callback, const char *substr)
{
  char *scenario;
  char *block;
  int i;
  int count;
  char *elem;
  void (*cb)(int);
  scenario = (char *)global_scenario_get();
  if (callback == 0)
  {
    display_assert((const char *)0x25c3b4, (const char *)0x280408, 0x197, 1);
    system_exit(-1);
  }
  cb = (void (*)(int))callback;
  block = scenario + 0x204;
  count = *(int *)block;
  for (i = 0; i < count; i++)
  {
    elem = (char *)tag_block_get_element(block, i, 0x24);
    if (crt_strstr(elem, substr) != 0)
      cb(i);
  }
}
/* FUN_000c9b90 (0xc9b90) — readable C lift. */
void FUN_000c9b90(const char *substr)
{
  hs_object_iterate_names_containing(FUN_000c9990, substr);
}

/* FUN_000cae80 (0xcae80) — readable C lift from XBE leaf (int == 0). */
char FUN_000cae80(int value)
{
  return value == 0;
}

/* FUN_000caea0 (0xcaea0) — readable C lift from XBE leaf (int16 == 0). */
char FUN_000caea0(int16_t value)
{
  return value == 0;
}

/* FUN_000caec0 (0xcaec0) — readable C lift. */
char FUN_000caec0(const char *s)
{
  return (char)(csstrlen(s) == 0);
}

/* FUN_000caef0 (0xcaef0) — readable C lift: int16→float bits in EAX. */
int FUN_000caef0(int16_t value)
{
  float f = (float)(int)value;
  int bits;

  __builtin_memcpy(&bits, &f, sizeof(bits));
  return bits;
}

/* FUN_000caf10 (0xcaf10) — readable C lift: int→float bits in EAX. */
int FUN_000caf10(int value)
{
  float f = (float)value;
  int bits;

  __builtin_memcpy(&bits, &f, sizeof(bits));
  return bits;
}

/* FUN_000caf20 (0xcaf20) — readable C lift: (int16+1)→float bits in EAX. */
int FUN_000caf20(int16_t value)
{
  float f = (float)((int)value + 1);
  int bits;

  __builtin_memcpy(&bits, &f, sizeof(bits));
  return bits;
}

/* FUN_000caf40 (0xcaf40) — readable C lift. */
int16_t FUN_000caf40(float x)
{
  return (int16_t)(int)x;
}

/* FUN_000caf60 (0xcaf60) — readable C lift (tail-call _ftol2). */
int FUN_000caf60(float value)
{
  int result;
  __asm__ volatile(
      "flds %1\n\t"
      "call %P2\n\t"
      "movl %%eax, %0"
      : "=m"(result)
      : "m"(value), "X"(FUN_001d9068)
      : "eax", "edx", "ecx", "st", "cc", "memory");
  return result;
}

/* FUN_000caf70 (0xcaf70) — readable C lift from XBE leaf (int16 identity). */
int16_t FUN_000caf70(int16_t value)
{
  return value;
}

/* FUN_000ce200 (0xce200) — readable C lift. */
int FUN_000ce200(void)
{
  int handle = data_new_at_index(*(data_t **)0x5aa698);
  void *node;
  if (handle == -1)
    return handle;
  node = datum_get(*(data_t **)0x5aa698, handle);
  *(unsigned short *)((char *)node + 6) = 0;
  *(int *)((char *)node + 8) = -1;
  return handle;
}

/* FUN_000ce2b0 (0xce2b0) — readable C lift: append object to list. */
void FUN_000ce2b0(int list_handle, int object_handle)
{
  char *list;
  char *node;
  int neu;
  list = (char *)datum_get(*(data_t **)0x5aa698, list_handle);
  neu = data_new_at_index(*(data_t **)0x5aa694);
  if (neu == -1)
    return;
  node = (char *)datum_get(*(data_t **)0x5aa694, neu);
  *(int *)(node + 4) = object_handle;
  *(int *)(node + 8) = *(int *)(list + 8);
  *(int *)(list + 8) = neu;
  *(unsigned short *)(list + 6) += 1;
}
/* FUN_000cafc0 (0xcafc0) — readable C lift. */
int FUN_000cafc0(int object_handle)
{
  int list;
  if (object_handle == -1)
    return -1;
  list = FUN_000ce200();
  FUN_000ce2b0(list, object_handle);
  return list;
}

/* FUN_000ce090 (0xce090) — readable C lift: advance linked datum cursor. */
int FUN_000ce090(data_t *data, int *cursor)
{
  int handle = *cursor;
  char *node;
  if (handle == -1)
    return -1;
  node = (char *)datum_get(data, handle);
  *cursor = *(int *)(node + 8);
  return *(int *)(node + 4);
}

/* FUN_000ce420 (0xce420) — readable C lift. */
int16_t FUN_000ce420(int list_handle)
{
  void *node;
  if (list_handle == -1)
    return 0;
  node = datum_get(*(data_t **)0x5aa698, list_handle);
  return *(int16_t *)((char *)node + 6);
}

/* FUN_000cab80 (0xcab80) — readable C lift: pop HS thread stack. */
void FUN_000cab80(int handle)
{
  char *node;
  int *stack;

  node = (char *)datum_get(*(data_t **)0x5aa6c4, handle);
  stack = *(int **)(node + 0x10);
  *(int *)(node + 0x10) = *stack;
}



/* FUN_000ca4e0 (0xca4e0) — readable C lift: boolean tostring. */
void FUN_000ca4e0(int16_t type, char flag, char *buffer)
{
  const char *word;
  if (type != 5) {
    display_assert((const char *)0x280460, (const char *)0x280478, 0x241, 1);
    system_exit(-1);
  }
  word = (const char *)(flag ? 0x25cb44 : 0x25cb3c);
  crt_sprintf(buffer, (const char *)0x257984, word);
}
/* FUN_000ca530 (0xca530) — readable C lift: real tostring. */
void FUN_000ca530(int16_t type, float value, char *buffer)
{
  if (type != 6) {
    display_assert((const char *)0x2804ac, (const char *)0x280478, 0x24c, 1);
    system_exit(-1);
  }
  crt_sprintf(buffer, (const char *)0x2804a8, (double)value);
}
/* FUN_000ca580 (0xca580) — readable C lift: short tostring. */
void FUN_000ca580(int16_t type, int16_t value, char *buffer)
{
  if (type != 7) {
    display_assert((const char *)0x2804c0, (const char *)0x280478, 0x257, 1);
    system_exit(-1);
  }
  crt_sprintf(buffer, (const char *)0x25acb8, (int)value);
}
/* FUN_000ca5d0 (0xca5d0) — readable C lift: long tostring. */
void FUN_000ca5d0(int16_t type, int value, char *buffer)
{
  if (type != 8) {
    display_assert((const char *)0x2804e4, (const char *)0x280478, 0x262, 1);
    system_exit(-1);
  }
  crt_sprintf(buffer, (const char *)0x2804e0, value);
}
/* FUN_000ca620 (0xca620) — readable C lift: string-ish tostring. */
void FUN_000ca620(int16_t type, int value, char *buffer)
{
  if (type != 9) {
    display_assert((const char *)0x280500, (const char *)0x280478, 0x26d, 1);
    system_exit(-1);
  }
  crt_sprintf(buffer, (const char *)0x257984, (const char *)value);
}
/* FUN_000c98e0 (0xc98e0) — readable C lift: object/player ownership walk. */
char FUN_000c98e0(int object_handle)
{
  char *obj;
  int player;
  char result;
  int child;
  char *child_obj;
  unsigned int bit;

  obj = (char *)object_get_and_verify_type(object_handle, -1);
  player = player_index_from_unit_index(object_handle);
  result = (char)(player != -1);
  if (result)
    return result;

  child = *(int *)(obj + 0xc8);
  while (child != -1) {
    child_obj = (char *)object_get_and_verify_type(child, -1);
    if (FUN_000c98e0(child))
      return 1;
    child = *(int *)(child_obj + 0xc4);
  }

  child = *(int *)(obj + 0xcc);
  while (child != -1) {
    child_obj = (char *)object_get_and_verify_type(child, -1);
    if (player_index_from_unit_index(child) != -1)
      return 1;
    child = *(int *)(child_obj + 0xcc);
  }

  bit = 1u << (unsigned char)obj[0x64];
  if ((bit & 0x1cu) == 0)
    return result;
  if ((obj[0x1a4] & 2) == 0)
    return result;
  return 1;
}

/* FUN_000c99e0 (0xc99e0) — readable C lift. */
void FUN_000c99e0(int object_handle)
{
  if (object_handle == -1)
    return;
  if (!FUN_000c98e0(object_handle)) {
    object_delete(object_handle);
    return;
  }
  error(2, (const char *)0x2803a8);
}

/* FUN_000c9a20 (0xc9a20) — readable C lift. */
void FUN_000c9a20(int16_t name_index)
{
  int handle;
  if (name_index == (int16_t)0xffff)
    return;
  handle = object_name_list_get_handle(name_index);
  if (handle == -1)
    return;
  FUN_000c99e0(handle);
}

/* FUN_000ca110 (0xca110) — readable C lift. */
void FUN_000ca110(int16_t name_index)
{
  int handle;
  if (name_index == (int16_t)-1)
    return;
  handle = object_name_list_get_handle(name_index);
  if (handle != -1)
    FUN_000c99e0(handle);
  FUN_000c9990(name_index);
}

/* FUN_000c9bb0 (0xc9bb0) — readable C lift. */
void FUN_000c9bb0(const char *substr)
{
  hs_object_iterate_names_containing(FUN_000c9a20, substr);
}

/* FUN_000ca140 (0xca140) — readable C lift. */
void FUN_000ca140(const char *substr)
{
  hs_object_iterate_names_containing(FUN_000ca110, substr);
}

static __attribute__((unused)) void hs_runtime_set_game_flag(int16_t game_flag, char set_flag)
{
  int word_index;
  int bit_index;
  uint32_t mask;
  uint32_t *flags;

  word_index = (int)game_flag >> 5;
  bit_index = (int)game_flag & 0x1f;
  mask = (uint32_t)(1U << bit_index);
  flags = (uint32_t *)(0x5aa6a0 + word_index * 4);
  if (set_flag)
    *flags |= mask;
  else
    *flags &= ~mask;
}

/* FUN_000c8b90 (0xc8b90) — readable C lift. */
char FUN_000c8b90(int16_t node_type, int datum_index)
{
  char *node;
  char *parent;
  int child;
  int next;
  char result;

  result = 0;
  node = (char *)datum_get(*(data_t **)0x5aa6c8, datum_index);
  parent = (char *)datum_get(*(data_t **)0x5aa6c8, *(int *)(node + 0x10));
  child = *(int *)(parent + 8);
  if (node_type != 0x13) {
    display_assert((const char *)0x27d0fc, (const char *)0x27cdc0, 0x20e, 1);
    system_exit(-1);
  }
  if (child == -1) {
    *(int *)0x46b6fc = 0x27d0bc;
    node = (char *)datum_get(*(data_t **)0x5aa6c8, datum_index);
    *(int *)0x46b700 = *(int *)(node + 0xc);
    return result;
  }
  if (!hs_type_check(child, 7))
    return result;
  next = *(int *)((char *)datum_get(*(data_t **)0x5aa6c8, child) + 8);
  if (next == -1)
    return 1;
  if (!hs_type_check(next, 0xa))
    return result;
  return 1;
}

/* FUN_000c8e00 (0xc8e00) — readable C lift. */
char FUN_000c8e00(int16_t function_index, int root_datum)
{
  char result;
  void *entry;
  const char *name;
  char *node;

  datum_get(*(data_t **)0x5aa6c8, root_datum);
  result = 0;
  if (function_index != 0x16) {
    display_assert((const char *)0x27d228, (const char *)0x27cdc0, 0x27f, 1);
    system_exit(-1);
  }
  entry = hs_function_table_get(function_index);
  name = *(const char **)((char *)entry + 4);
  if (!FUN_000c55d0(name, (int *)&function_index, 1, root_datum))
    return result;
  node = (char *)datum_get(*(data_t **)0x5aa6c8, function_index);
  if (hs_type_check(function_index, 0))
    return 1;
  if (*(int *)0x46b6fc)
    return result;
  *(int *)0x46b6fc = 0x27d1e0;
  *(int *)0x46b700 = *(int *)(node + 0xc);
  return result;
}

/* FUN_000c8ec0 (0xc8ec0) — readable C lift. */
char FUN_000c8ec0(int16_t function_index, int root_datum)
{
  char result;
  void *entry;
  const char *name;

  result = 0;
  if (function_index != 0x17) {
    display_assert((const char *)0x27d250, (const char *)0x27cdc0, 0x29a, 1);
    system_exit(-1);
  }
  entry = hs_function_table_get(function_index);
  name = *(const char **)((char *)entry + 4);
  if (!FUN_000c55d0(name, (int *)&function_index, 1, root_datum))
    return result;
  return (char)hs_type_check(function_index, 0x25);
}


/* FUN_000c95f0 (0xc95f0) — readable C lift: collect object list from players. */
int FUN_000c95f0(void)
{
  int list_handle;
  int player;
  char *node;
  int obj;

  list_handle = FUN_000ce200();
  player = data_next_index(*(data_t **)0x5aa6d4, -1);
  while (player != -1) {
    node = (char *)datum_get(*(data_t **)0x5aa6d4, player);
    obj = *(int *)(node + 0x34);
    if (obj != -1)
      FUN_000ce2b0(list_handle, obj);
    player = data_next_index(*(data_t **)0x5aa6d4, player);
  }
  return list_handle;
}

/* FUN_000c9650 (0xc9650) — XBE naked draft (batch 138). */
#if defined(__clang__)
static int (*const bc9650_cce450)(int parent_handle, int *iter_state) = FUN_000ce450;
static char (*const bc9650_c18ef00)(int cluster_index, int object_handle) = FUN_0018ef00;
static int (*const bc9650_cce320)(int parent_handle, int *iter_state) = FUN_000ce320;

__attribute__((naked, noinline))
char FUN_000c9650(int16_t game_flag __attribute__((unused)), int list_handle __attribute__((unused)), char set_flag __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ebx\n\t"
      "movb 0x10(%%ebp), %%bl\n\t"
      "pushl %%esi\n\t"
      "movl 0xc(%%ebp), %%esi\n\t"
      "pushl %%edi\n\t"
      "leal 0x10(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[cce450]\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_000c9650_4\n\t"
      ".LFUN_000c9650_1:\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "call *%[c18ef00]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000c9650_2\n\t"
      "testb %%bl, %%bl\n\t"
      "jne .LFUN_000c9650_3\n\t"
      "movb $1, %%bl\n\t"
      "jmp .LFUN_000c9650_5\n\t"
      ".LFUN_000c9650_2:\n\t"
      "testb %%bl, %%bl\n\t"
      "jne .LFUN_000c9650_6\n\t"
      ".LFUN_000c9650_3:\n\t"
      "leal 0x10(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "call *%[cce320]\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "jne .LFUN_000c9650_1\n\t"
      ".LFUN_000c9650_4:\n\t"
      "testb %%bl, %%bl\n\t"
      "je .LFUN_000c9650_7\n\t"
      ".LFUN_000c9650_5:\n\t"
      "movswl %%di, %%ecx\n\t"
      "movl %%ecx, %%edx\n\t"
      "sarl $5, %%edx\n\t"
      "leal 0x5aa6a0(,%%edx,4), %%eax\n\t"
      "andl $0x1f, %%ecx\n\t"
      "movl $1, %%edx\n\t"
      "shll %%cl, %%edx\n\t"
      "movl (%%eax), %%ecx\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "orl %%edx, %%ecx\n\t"
      "movl %%ecx, (%%eax)\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000c9650_6:\n\t"
      "xorb %%bl, %%bl\n\t"
      ".LFUN_000c9650_7:\n\t"
      "movswl %%di, %%ecx\n\t"
      "movl %%ecx, %%eax\n\t"
      "andl $0x1f, %%ecx\n\t"
      "movl $1, %%edx\n\t"
      "shll %%cl, %%edx\n\t"
      "sarl $5, %%eax\n\t"
      "movl 0x5aa6a0(,%%eax,4), %%ecx\n\t"
      "leal 0x5aa6a0(,%%eax,4), %%eax\n\t"
      "notl %%edx\n\t"
      "popl %%edi\n\t"
      "andl %%edx, %%ecx\n\t"
      "movl %%ecx, (%%eax)\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [cce450] "m"(bc9650_cce450), [c18ef00] "m"(bc9650_c18ef00), [cce320] "m"(bc9650_cce320)
      : "memory");
}
#else
#error "FUN_000c9650: clang naked draft required"
#endif


/* FUN_000c9700 (0xc9700) — readable C lift: unit facing point within angle. */
char FUN_000c9700(int object_handle, int unused, float distance)
{
  float pos[3];
  char *obj;

  if (unused == -1)
    return 0;
  if (object_try_and_get_and_verify_type(unused, 3)) {
    unit_get_head_position(unused, pos);
  } else {
    obj = (char *)object_get_and_verify_type(unused, -1);
    pos[0] = *(float *)(obj + 0x50);
    pos[1] = *(float *)(obj + 0x54);
    pos[2] = *(float *)(obj + 0x58);
  }
  return FUN_001aa430(object_handle, pos, distance * *(float *)0x253d4c);
}


/* FUN_000c9770 (0xc9770) — readable C lift: any list unit facing param. */
char FUN_000c9770(int list_handle, int param, float distance)
{
  int iter;
  int obj;

  obj = FUN_000ce450(list_handle, &iter);
  while (obj != -1) {
    if (object_try_and_get_and_verify_type(obj, 3) &&
        FUN_000c9700(obj, param, distance))
      return 1;
    obj = FUN_000ce320(list_handle, &iter);
  }
  return 0;
}

/* FUN_000c97f0 (0xc97f0) — readable C lift. */
void FUN_000c97f0(int object_handle, int16_t scenario_index, float distance)
{
  void *elem;
  if (scenario_index == 0)
    return;
  elem = tag_block_get_element(
      (char *)global_scenario_get() + 0x4e4, (int)scenario_index, 0x5c);
  FUN_001aa430(object_handle, (float *)((char *)elem + 0x24),
               distance * *(float *)0x253d4c);
}
/* FUN_000c9840 (0xc9840) — XBE naked draft (batch 140). */
#if defined(__clang__)
static int (*const bc9840_cce450)(int parent_handle, int *iter_state) = FUN_000ce450;
static void *(*const bc9840_tryget)(int, int) = object_try_and_get_and_verify_type;
static scenario_t * (*const bc9840_c18e380)(void) = global_scenario_get;
static void *(*const bc9840_elem)(void *, int, int) = tag_block_get_element;
static char (*const bc9840_c1aa430)(int unit_handle, float *point, float half_angle) = FUN_001aa430;
static int (*const bc9840_cce320)(int parent_handle, int *iter_state) = FUN_000ce320;

__attribute__((naked, noinline))
char FUN_000c9840(int list_handle __attribute__((unused)), int16_t scenario_index __attribute__((unused)), float distance __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "leal -0x4(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "call *%[cce450]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%esi\n\t"
      "je .LFUN_000c9840_3\n\t"
      "movw 0xc(%%ebp), %%di\n\t"
      ".LFUN_000c9840_1:\n\t"
      "pushl $3\n\t"
      "pushl %%esi\n\t"
      "call *%[tryget]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_000c9840_2\n\t"
      "testw %%di, %%di\n\t"
      "je .LFUN_000c9840_2\n\t"
      "flds 0x10(%%ebp)\n\t"
      "pushl %%ecx\n\t"
      "fmuls 0x253d4c\n\t"
      "movswl %%di, %%ecx\n\t"
      "fstps (%%esp)\n\t"
      "pushl $0x5c\n\t"
      "pushl %%ecx\n\t"
      "call *%[c18e380]\n\t"
      "addl $0x4e4, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "addl $0xc, %%esp\n\t"
      "addl $0x24, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[c1aa430]\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_000c9840_4\n\t"
      ".LFUN_000c9840_2:\n\t"
      "leal -0x4(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ebx\n\t"
      "call *%[cce320]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%esi\n\t"
      "jne .LFUN_000c9840_1\n\t"
      ".LFUN_000c9840_3:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000c9840_4:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [cce450] "m"(bc9840_cce450), [tryget] "m"(bc9840_tryget), [c18e380] "m"(bc9840_c18e380), [elem] "m"(bc9840_elem), [c1aa430] "m"(bc9840_c1aa430), [cce320] "m"(bc9840_cce320)
      : "memory");
}
#else
#error "FUN_000c9840: clang naked draft required"
#endif


/* FUN_000c9a50 (0xc9a50) — XBE naked draft (batch 137). */
#if defined(__clang__)
static void (*const bc9a50_c1197b0)(data_iter_t *iter, data_t *data) = data_iterator_new;
static void * (*const bc9a50_c119810)(data_iter_t *iterator) = data_iterator_next;
static int (*const bc9a50_c13d7f0)(int object_handle) = object_get_root_parent;
static void (*const bc9a50_c1b2dd0)(int unit_handle) = unit_exit_seat_end;
static void (*const bc9a50_c13d6f0)(void *iter, int type_mask, int flags) = object_iterator_new;
static void * (*const bc9a50_c13d730)(void *iter) = object_iterator_next;
static char (*const bc9a50_cc98e0)(int object_handle) = (void *)FUN_000c98e0;
static void (*const bc9a50_odel)(int) = object_delete;

__attribute__((naked, noinline))
void FUN_000c9a50(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x10, %%esp\n\t"
      "movl 0x5aa6d4, %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "leal -0x10(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1197b0]\n\t"
      "leal -0x10(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c119810]\n\t"
      "addl $0xc, %%esp\n\t"
      "orl $0xffffffff, %%edi\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_000c9a50_3\n\t"
      "pushl %%esi\n\t"
      "leal (%%ebx), %%ebx\n\t"
      ".LFUN_000c9a50_1:\n\t"
      "movl 0x34(%%eax), %%ecx\n\t"
      "cmpl %%edi, %%ecx\n\t"
      "je .LFUN_000c9a50_2\n\t"
      "movl %%ecx, %%esi\n\t"
      "pushl %%esi\n\t"
      "call *%[c13d7f0]\n\t"
      "addl $4, %%esp\n\t"
      "cmpl %%esi, %%eax\n\t"
      "je .LFUN_000c9a50_2\n\t"
      "pushl %%esi\n\t"
      "call *%[c1b2dd0]\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_000c9a50_2:\n\t"
      "leal -0x10(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c119810]\n\t"
      "addl $4, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_000c9a50_1\n\t"
      "popl %%esi\n\t"
      ".LFUN_000c9a50_3:\n\t"
      "pushl $0\n\t"
      "leal -0x10(%%ebp), %%ecx\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "call *%[c13d6f0]\n\t"
      "leal -0x10(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c13d730]\n\t"
      "addl $0x10, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_000c9a50_6\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_000c9a50_4:\n\t"
      "cmpl %%edi, 0xcc(%%eax)\n\t"
      "jne .LFUN_000c9a50_5\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[cc98e0]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_000c9a50_5\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[odel]\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_000c9a50_5:\n\t"
      "leal -0x10(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c13d730]\n\t"
      "addl $4, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_000c9a50_4\n\t"
      ".LFUN_000c9a50_6:\n\t"
      "popl %%edi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c1197b0] "m"(bc9a50_c1197b0), [c119810] "m"(bc9a50_c119810), [c13d7f0] "m"(bc9a50_c13d7f0), [c1b2dd0] "m"(bc9a50_c1b2dd0), [c13d6f0] "m"(bc9a50_c13d6f0), [c13d730] "m"(bc9a50_c13d730), [cc98e0] "m"(bc9a50_cc98e0), [odel] "m"(bc9a50_odel)
      : "memory");
}
#else
#error "FUN_000c9a50: clang naked draft required"
#endif


/* FUN_000c9bd0 (0xc9bd0) — readable C lift. */
int FUN_000c9bd0(int list_handle, int16_t skip_count)
{
  int iter;
  int cur;
  cur = FUN_000ce450(list_handle, &iter);
  while (skip_count > 0) {
    if (cur == -1)
      break;
    cur = FUN_000ce320(list_handle, &iter);
    skip_count -= 1;
  }
  return cur;
}

/* FUN_000c9c10 (0xc9c10) — readable C lift. */
void FUN_000c9c10(int object_handle, float value)
{
  char *obj;
  if (object_handle == -1)
    return;
  obj = (char *)object_get_and_verify_type(object_handle, -1);
  if (value < 0.0f)
    value = 0.0f;
  else if (value > 1.0f)
    value = 1.0f;
  *(float *)(obj + 0x94) = value * *(float *)(obj + 0x8c);
}

/* FUN_000c9c80 (0xc9c80) — readable C lift: permute object region by name. */
void FUN_000c9c80(int object_handle, int region_name, int variant)
{
  void *obj;
  void *tag;
  int model_index;
  void *model_tag;
  void *regions;
  int count;
  int i;
  short found;
  void *elem;

  if (object_handle == -1)
    return;
  obj = object_get_and_verify_type(object_handle, -1);
  tag = tag_get(0x6f626a65, *(int *)obj);
  found = -1;
  if (csstrcmp((const char *)region_name, (const char *)0x25386f) != 0) {
    model_index = *(int *)((char *)tag + 0x34);
    if (model_index != -1) {
      model_tag = tag_get(0x6d6f6465, model_index);
      regions = (char *)model_tag + 0xc4;
      count = *(int *)regions;
      for (i = 0; i < count; i++) {
        elem = tag_block_get_element(regions, i, 0x4c);
        if (crt_stricmp((const char *)elem, (const char *)region_name) == 0) {
          found = (short)i;
          break;
        }
      }
    }
  }
  object_permute_region(object_handle, (const char *)variant, found, 1);
}

/* FUN_000c9d40 (0xc9d40) — readable C lift: delete each object in list. */
void FUN_000c9d40(int list_handle)
{
  int iter;
  int obj;

  obj = FUN_000ce450(list_handle, &iter);
  while (obj != -1) {
    FUN_0013ddd0(obj);
    obj = FUN_000ce320(list_handle, &iter);
  }
}

/* FUN_000c9d80 (0xc9d80) — readable C lift: delete objects of type. */
void FUN_000c9d80(int object_type)
{
  char iter[0x10];
  void *obj;
  object_iterator_new(iter, -1, 0);
  obj = object_iterator_next(iter);
  while (obj != 0) {
    if (*(int *)obj == object_type)
      object_delete(*(int *)(iter + 8));
    obj = object_iterator_next(iter);
  }
  FUN_00145490();
}
/* FUN_000c9de0 (0xc9de0) — readable C lift: unattached effect at cutscene flag. */
void FUN_000c9de0(int effect_tag, int16_t scenario_index)
{
  char *flag;
  float angles[3];
  scenario_t *scen;

  scen = global_scenario_get();
  flag = (char *)tag_block_get_element((char *)scen + 0x4e4, (int)scenario_index, 0x5c);
  angles_to_vector(angles, (float *)(flag + 0x30));
  effect_new_unattached_from_markers(
      effect_tag,
      -1,
      *(float **)0x31fc38,
      1,
      0,
      (float *)(flag + 0x24),
      angles,
      1.0f,
      1.0f,
      0.0f,
      0.0f,
      1.0f);
}

/* FUN_000c9e50 (0xc9e50) — readable C lift: attach effect at marker. */
void FUN_000c9e50(int object_handle, int attach_object, int marker_id)
{
  char markers[0x6c];
  int16_t n;

  if (object_handle == -1 || attach_object == -1)
    return;
  n = object_get_markers_by_string_id(attach_object, (void *)marker_id, markers, 1);
  if (n == 0)
    return;
  effect_new_attached_from_markers(
      -1,
      object_handle,
      attach_object,
      (uint16_t)*(int *)markers,
      1,
      &marker_id,
      (float *)(markers + 0x60),
      (float *)(markers + 0x3c),
      1.0f,
      1.0f,
      0.0f,
      0.0f);
}

/* FUN_000c9ec0 (0xc9ec0) — readable C lift: damage at cutscene flag. */
void FUN_000c9ec0(int damage_type, int16_t scenario_index)
{
  char damage[0x54];
  char *flag;
  float world[3];
  scenario_t *scen;

  scen = global_scenario_get();
  flag = (char *)tag_block_get_element((char *)scen + 0x4e4, (int)scenario_index, 0x5c);
  damage_data_new(damage, damage_type);
  world[0] = *(float *)(flag + 0x24);
  world[1] = *(float *)(flag + 0x28);
  world[2] = *(float *)(flag + 0x2c);
  *(float *)(damage + 0x28) = world[0];
  *(float *)(damage + 0x2c) = world[1];
  *(float *)(damage + 0x30) = world[2];
  *(float *)(damage + 0x1c) = world[0];
  *(float *)(damage + 0x20) = world[1];
  *(float *)(damage + 0x24) = world[2];
  scenario_location_from_point(damage + 0x14, flag + 0x24);
  FUN_00138e30(damage, -1);
}

/* FUN_000c9f30 (0xc9f30) — readable C lift: apply damage at object world pos. */
void FUN_000c9f30(int damage_type, int object_handle)
{
  char damage[0x54];
  float world[3];

  if (object_handle == -1)
    return;
  damage_data_new(damage, damage_type);
  object_get_world_position(object_handle, (vector3_t *)world);
  *(float *)(damage + 0x28) = world[0];
  *(float *)(damage + 0x2c) = world[1];
  *(float *)(damage + 0x30) = world[2];
  scenario_location_from_point(damage + 0x14, world);
  object_cause_damage(damage, object_handle, -1, -1, -1, 0);
}

/* FUN_000ca010 (0xca010) — readable C lift. */
float FUN_000ca010(int object_handle)
{
  float *p = FUN_000c9f90(object_handle);
  if (p == 0)
    return *(float *)0x2533c0;
  return *p;
}

/* FUN_000ca030 (0xca030) — readable C lift. */
void FUN_000ca030(int object_handle, float value)
{
  float *p = FUN_000c9f90(object_handle);
  if (p != 0)
    *p = value;
}

/* FUN_000ca050 (0xca050) — readable C lift: set/clear game flag from object list. */
char FUN_000ca050(int16_t game_flag, int list_handle)
{
  int iter_state;
  int object_handle;
  int bit;
  int *word;
  object_handle = FUN_000ce450(list_handle, &iter_state);
  while (object_handle != -1)
  {
    if (!FUN_0018ef00((int)game_flag, object_handle))
    {
      bit = 1 << ((int)game_flag & 0x1f);
      word = (int *)(0x5aa6a0 + (((int)game_flag >> 5) * 4));
      *word &= ~bit;
      return 0;
    }
    object_handle = FUN_000ce320(list_handle, &iter_state);
  }
  bit = 1 << ((int)game_flag & 0x1f);
  word = (int *)(0x5aa6a0 + (((int)game_flag >> 5) * 4));
  *word |= bit;
  return 1;
}
/* FUN_000ca0f0 (0xca0f0) — readable C lift. */
char FUN_000ca0f0(int16_t game_flag, int list_handle)
{
  return FUN_000c9650(game_flag, list_handle, 0);
}

/* FUN_000ca160 (0xca160) — XBE naked draft (batch 112). */
#if defined(__clang__)
static void *(*const bca160_get)(int, int) = object_get_and_verify_type;
static scenario_t * (*const bca160_c18e380)(void) = global_scenario_get;
static void *(*const bca160_elem)(void *, int, int) = tag_block_get_element;
static bool (*const bca160_ca16b0)(float *point) = valid_real_point3d;
static char * (*const bca160_c8d9d0)(char *buffer, const char *format, ...) = csprintf;
static void (*const bca160_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const bca160_exitfn)(int) = system_exit;
static void *(*const bca160_tryget)(int, int) = object_try_and_get_and_verify_type;
static void (*const bca160_c1b2dd0)(int unit_handle) = unit_exit_seat_end;
static void (*const bca160_c1411c0)(int object_handle) = object_detach_from_parent;
static void (*const bca160_c10cc40)(float *out, float *angles) = angles_to_vector;
static bool (*const bca160_c21fb0)(float *v) = valid_real_normal3d;
static void (*const bca160_c13fbc0)(int object_handle) = object_reset;
static int (*const bca160_cba500)(int) = player_index_from_unit_index;
static void *(*const bca160_onode)(int, short) = object_get_node_matrix;
static void (*const bca160_c109150)(float *src, float *dst) = matrix_inverse;
static void (*const bca160_c109680)(float *matrix, float *in, float *out) = matrix_transform_vector;
static void *(*const bca160_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static char (*const bca160_cbbb80)(int player_handle, void *a, void *b) = player_teleport;
static void (*const bca160_cb6ea0)(uint16_t local_player_index, float *direction) = player_control_set_facing;
static void (*const bca160_c143ae0)(int object_handle, float *position, float *forward, float *up) = object_set_position;

__attribute__((naked, noinline))
void FUN_000ca160(int16_t scenario_index __attribute__((unused)), char teleport_flag __attribute__((unused)), char facing_flag __attribute__((unused)), int object_handle __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x54, %%esp\n\t"
      "cmpl $-1, %%ebx\n\t"
      "je .LFUN_000ca160_14\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl $-1\n\t"
      "pushl %%ebx\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%edi\n\t"
      "movswl 0x8(%%ebp), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "pushl $0x5c\n\t"
      "pushl %%eax\n\t"
      "call *%[c18e380]\n\t"
      "addl $0x4e4, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl %%eax, %%esi\n\t"
      "leal 0x24(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl $0, -0x4(%%ebp)\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "call *%[ca16b0]\n\t"
      "addl $0x10, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_000ca160_1\n\t"
      "flds 0x2c(%%esi)\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "pushl $1\n\t"
      "pushl $0x1cc\n\t"
      "pushl $0x280408\n\t"
      "subl $0x18, %%esp\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds 0x28(%%esi)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds (%%ecx)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x280450\n\t"
      "pushl $0x26ae04\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x24, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000ca160_1:\n\t"
      "movb 0xc(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000ca160_4\n\t"
      "cmpl $-1, 0xcc(%%edi)\n\t"
      "je .LFUN_000ca160_4\n\t"
      "pushl $3\n\t"
      "pushl %%ebx\n\t"
      "call *%[tryget]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "pushl %%ebx\n\t"
      "je .LFUN_000ca160_2\n\t"
      "call *%[c1b2dd0]\n\t"
      "jmp .LFUN_000ca160_3\n\t"
      ".LFUN_000ca160_2:\n\t"
      "call *%[c1411c0]\n\t"
      ".LFUN_000ca160_3:\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_000ca160_4:\n\t"
      "addl $0x30, %%esi\n\t"
      "leal -0x14(%%ebp), %%edx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edx\n\t"
      "call *%[c10cc40]\n\t"
      "leal -0x14(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c21fb0]\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_000ca160_5\n\t"
      "flds -0xc(%%ebp)\n\t"
      "pushl $1\n\t"
      "pushl $0x1df\n\t"
      "pushl $0x280408\n\t"
      "subl $0x18, %%esp\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x26a9c0\n\t"
      "pushl $0x254a24\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x24, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000ca160_5:\n\t"
      "pushl %%ebx\n\t"
      "call *%[c13fbc0]\n\t"
      "pushl $3\n\t"
      "pushl %%ebx\n\t"
      "call *%[tryget]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_000ca160_10\n\t"
      "pushl %%ebx\n\t"
      "call *%[cba500]\n\t"
      "movl %%eax, %%edi\n\t"
      "movl 0xcc(%%esi), %%eax\n\t"
      "addl $4, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_000ca160_6\n\t"
      "movsbw 0xd0(%%esi), %%dx\n\t"
      "leal -0x54(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[onode]\n\t"
      "addl $8, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[c109150]\n\t"
      "leal -0x20(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x14(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x54(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c109680]\n\t"
      "addl $0x14, %%esp\n\t"
      "jmp .LFUN_000ca160_7\n\t"
      ".LFUN_000ca160_6:\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "movl -0x10(%%ebp), %%ecx\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "movl %%eax, -0x20(%%ebp)\n\t"
      "movl %%ecx, -0x1c(%%ebp)\n\t"
      "movl %%edx, -0x18(%%ebp)\n\t"
      ".LFUN_000ca160_7:\n\t"
      "movb 0x10(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000ca160_8\n\t"
      "movl -0x14(%%ebp), %%ecx\n\t"
      "leal 0x1d4(%%esi), %%eax\n\t"
      "movl %%ecx, (%%eax)\n\t"
      "movl -0x10(%%ebp), %%edx\n\t"
      "movl %%edx, 0x4(%%eax)\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "movl %%ecx, 0x8(%%eax)\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "leal 0x1e0(%%esi), %%edx\n\t"
      "movl %%eax, (%%edx)\n\t"
      "movl -0x10(%%ebp), %%ecx\n\t"
      "movl %%ecx, 0x4(%%edx)\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "movl %%eax, 0x8(%%edx)\n\t"
      "movl -0x14(%%ebp), %%ecx\n\t"
      "addl $0x204, %%esi\n\t"
      "movl %%ecx, (%%esi)\n\t"
      "movl -0x10(%%ebp), %%edx\n\t"
      "movl %%edx, 0x4(%%esi)\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "movl %%eax, 0x8(%%esi)\n\t"
      ".LFUN_000ca160_8:\n\t"
      "cmpl $-1, %%edi\n\t"
      "je .LFUN_000ca160_10\n\t"
      "movl 0x5aa6d4, %%ecx\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "movb 0xc(%%ebp), %%al\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000ca160_9\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $-1\n\t"
      "pushl %%edi\n\t"
      "call *%[cbbb80]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_000ca160_9:\n\t"
      "movb 0x10(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000ca160_11\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movswl 0x2(%%eax), %%eax\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .LFUN_000ca160_10\n\t"
      "leal -0x20(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "call *%[cb6ea0]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_000ca160_10:\n\t"
      "movb 0x10(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000ca160_11\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_000ca160_11\n\t"
      "leal -0x14(%%ebp), %%ecx\n\t"
      "jmp .LFUN_000ca160_12\n\t"
      ".LFUN_000ca160_11:\n\t"
      "xorl %%ecx, %%ecx\n\t"
      ".LFUN_000ca160_12:\n\t"
      "movb 0xc(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "je .LFUN_000ca160_13\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_000ca160_13\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "pushl $0\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "call *%[c143ae0]\n\t"
      "addl $0x10, %%esp\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000ca160_13:\n\t"
      "xorl %%eax, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "call *%[c143ae0]\n\t"
      "addl $0x10, %%esp\n\t"
      ".LFUN_000ca160_14:\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [get] "m"(bca160_get), [c18e380] "m"(bca160_c18e380), [elem] "m"(bca160_elem), [ca16b0] "m"(bca160_ca16b0), [c8d9d0] "m"(bca160_c8d9d0), [assert] "m"(bca160_assert), [exitfn] "m"(bca160_exitfn), [tryget] "m"(bca160_tryget), [c1b2dd0] "m"(bca160_c1b2dd0), [c1411c0] "m"(bca160_c1411c0), [c10cc40] "m"(bca160_c10cc40), [c21fb0] "m"(bca160_c21fb0), [c13fbc0] "m"(bca160_c13fbc0), [cba500] "m"(bca160_cba500), [onode] "m"(bca160_onode), [c109150] "m"(bca160_c109150), [c109680] "m"(bca160_c109680), [dget] "m"(bca160_dget), [cbbb80] "m"(bca160_cbbb80), [cb6ea0] "m"(bca160_cb6ea0), [c143ae0] "m"(bca160_c143ae0)
      : "memory");
}
#else
#error "FUN_000ca160: clang naked draft required"
#endif


/* FUN_000ca3f0 (0xca3f0) — readable C lift. */
void FUN_000ca3f0(int object_handle, int scenario_index)
{
  FUN_000ca160(scenario_index, 1, 1, object_handle);
}

/* FUN_000ca410 (0xca410) — readable C lift. */
void FUN_000ca410(int object_handle, int scenario_index)
{
  FUN_000ca160(scenario_index, 0, 1, object_handle);
}

/* FUN_000ca430 (0xca430) — XBE naked draft (batch 137). */
#if defined(__clang__)
static int (*const bca430_c1198f0)(data_t *data, int prev_index) = data_next_index;
static void *(*const bca430_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static char (*const bca430_c18ef00)(int cluster_index, int object_handle) = FUN_0018ef00;
static void (*const bca430_cca160)(int16_t scenario_index, char teleport_flag, char facing_flag, int object_handle) = FUN_000ca160;

__attribute__((naked, noinline))
void FUN_000ca430(int16_t game_flag __attribute__((unused)), int16_t scenario_index __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl 0x5aa6d4, %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl $-1\n\t"
      "pushl %%eax\n\t"
      "call *%[c1198f0]\n\t"
      "movl %%eax, %%edi\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%edi\n\t"
      "je .LFUN_000ca430_3\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".LFUN_000ca430_1:\n\t"
      "movl 0x5aa6d4, %%ecx\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x34(%%esi), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_000ca430_2\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%edx\n\t"
      "call *%[c18ef00]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_000ca430_2\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "movl 0x34(%%esi), %%ebx\n\t"
      "pushl $1\n\t"
      "pushl $1\n\t"
      "pushl %%eax\n\t"
      "call *%[cca160]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_000ca430_2:\n\t"
      "movl 0x5aa6d4, %%ecx\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1198f0]\n\t"
      "movl %%eax, %%edi\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%edi\n\t"
      "jne .LFUN_000ca430_1\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      ".LFUN_000ca430_3:\n\t"
      "popl %%edi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c1198f0] "m"(bca430_c1198f0), [dget] "m"(bca430_dget), [c18ef00] "m"(bca430_c18ef00), [cca160] "m"(bca430_cca160)
      : "memory");
}
#else
#error "FUN_000ca430: clang naked draft required"
#endif


/* FUN_000ca670 (0xca670) — readable C lift: enum tostring. */
void FUN_000ca670(int16_t type, int16_t enum_index, char *buffer)
{
  int16_t *table;
  if (type < 0x20 || type > 0x24) {
    display_assert((const char *)0x28054c, (const char *)0x280478, 0x27b, 1);
    system_exit(-1);
  }
  table = (int16_t *)(0x2726b4 + ((int)type) * 8);
  if (enum_index < 0 || enum_index >= table[0]) {
    display_assert((const char *)0x280518, (const char *)0x280478, 0x27c, 1);
    system_exit(-1);
  }
  crt_sprintf(buffer, (const char *)0x257984,
              *(const char **)(*(int *)((char *)table + 4) + (int)enum_index * 4));
}
/* FUN_000ca700 (0xca700) — readable C lift: allocate HS thread/stack data. */
void FUN_000ca700(void)
{
  data_t *threads;
  data_t *stack;
  int need;
  short i;
  int handle;

  threads = game_state_data_new((char *)0x2805e8, 0x100, 0x218);
  stack = game_state_data_new((char *)0x2805dc, 0x400, 8);
  *(data_t **)0x5aa6c4 = threads;
  *(data_t **)0x5aa6c0 = stack;
  if (!threads || !stack) {
    error(0, (const char *)0x280564);
    return;
  }
  need = (int)*(short *)0x27d504 * 2;
  if (need >= 0x400) {
    display_assert((const char *)0x280598, (const char *)0x2805bc, 0xa9, 1);
    system_exit(-1);
    stack = *(data_t **)0x5aa6c0;
  }
  data_delete_all(stack);
  for (i = 0; i < *(short *)0x27d504; i++) {
    handle = data_new_datum(*(data_t **)0x5aa6c0, (int)i | 0xaced0000);
    if (handle == -1) {
      display_assert((const char *)0x28058c, (const char *)0x2805bc, 0xb1, 1);
      system_exit(-1);
    }
  }
}

const char *FUN_000ca890(int datum_index)
{
  char *node;
  char *thread;
  int16_t script_index;
  void *entry;

  node = (char *)datum_get(*(data_t **)0x5aa6c8, datum_index);
  thread = (char *)datum_get(*(data_t **)0x5aa6c4, *(int *)(node + 8));
  if ((*(uint8_t *)(thread + 6) & 2) == 0) {
    while (*(int16_t *)(node + 2) == 0) {
      if (*(int *)(thread + 0x10) != datum_index)
        break;
      if (*(int *)(node + 0xe) == -1)
        return (const char *)0x2805f4;
      node = (char *)datum_get(*(data_t **)0x5aa6c8, *(int *)(node + 0xe));
      thread = (char *)datum_get(*(data_t **)0x5aa6c4, *(int *)(node + 8));
      if ((*(uint8_t *)(thread + 6) & 2) != 0)
        break;
    }
  }

  script_index = *(int16_t *)(node + 2);
  if ((*(uint8_t *)(thread + 6) & 2) != 0) {
    return (const char *)tag_block_get_element(
      (char *)global_scenario_get() + 0x49c, script_index, 0x5c);
  }

  entry = hs_function_table_get(script_index);
  return *(const char **)((char *)entry + 4);
}

/* FUN_000cacf0 (0xcacf0) — readable C lift: HS thread stack/control cleanup. */
void FUN_000cacf0(int thread_index)
{
  char *thread;
  int expr;
  unsigned char flags;
  int *stack;
  int handle;
  char *node;
  int *link;

  thread = (char *)datum_get(*(data_t **)0x5aa6c4, thread_index);
  expr = *(int *)(thread + 8);
  if (expr == -1)
    return;
  flags = (unsigned char)thread[3];
  *(int *)(thread + 8) = 0;
  if (flags & 2) {
    *(int *)(thread + 8) = *(int *)(thread + 0xc);
    thread[3] = (char)(flags & (unsigned char)~2);
    return;
  }
  stack = *(int **)(thread + 0x10);
  handle = stack[1];
  if (handle != -1) {
    node = (char *)datum_get(*(data_t **)0x5aa6c8, handle);
    if (*(int16_t *)(node + 2) == 0x14) {
      thread = (char *)datum_get(*(data_t **)0x5aa6c4, thread_index);
      stack = *(int **)(thread + 0x10);
      *(int *)(thread + 0x10) = *stack;
      return;
    }
  }
  stack = *(int **)(thread + 0x10);
  link = (int *)*stack;
  if (!link)
    return;
  handle = link[1];
  if (handle == -1)
    return;
  node = (char *)datum_get(*(data_t **)0x5aa6c8, handle);
  if (*(int16_t *)(node + 2) != 0x14)
    return;
  FUN_000cab80(thread_index);
  FUN_000cab80(thread_index);
  thread[3] = (char)(thread[3] & (unsigned char)~1);
}



/* FUN_000cae00 (0xcae00) — readable C lift: find script index by name. */
int FUN_000cae00(const char *script_name)
{
  int handle;
  char *node;
  int script_index;
  void *elem;

  handle = data_next_index(*(data_t **)0x5aa6c4, -1);
  while (handle != -1) {
    node = (char *)datum_get(*(data_t **)0x5aa6c4, handle);
    script_index = *(int *)(node + 4);
    if (script_index != -1) {
      elem = tag_block_get_element(
          (char *)global_scenario_get() + 0x49c, script_index, 0x5c);
      if (crt_stricmp(elem, script_name) == 0)
        return handle;
    }
    handle = data_next_index(*(data_t **)0x5aa6c4, handle);
  }
  return -1;
}



/* FUN_000caf80 (0xcaf80) — readable C lift. */
int FUN_000caf80(int16_t name_index)
{
  int handle;
  int list;
  list = -1;
  handle = object_name_list_get_handle(name_index);
  if (handle == -1)
    return -1;
  list = FUN_000ce200();
  FUN_000ce2b0(list, handle);
  return list;
}

/* FUN_000cb940 (0xcb940) — readable C lift: report script recompile error. */
char FUN_000cb940(int16_t param, int thread_index /*@<eax>*/, const char *detail /*@<edi>*/)
{
  extern char DAT_00280900[];
  extern char DAT_0028092c[];
  const char *msg;
  char *name;

  (void)datum_get(*(data_t **)0x5aa6c4, thread_index);
  msg = detail;
  if (msg == 0)
    msg = DAT_0028092c;
  name = hs_get_thread_script_name(thread_index);
  error(2, DAT_00280900, name, msg, (int)param);
  return 0;
}

/* hs_runtime_update (0xcde00) — XBE naked draft (batch 143). */
#if defined(__clang__)
static int (*const bcde00_gtime)(void) = game_time_get;
static int (*const bcde00_c1198f0)(data_t *data, int prev_index) = data_next_index;
static void *(*const bcde00_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void (*const bcde00_ccd840)(int thread_handle) = FUN_000cd840;
static void (*const bcde00_cce3c0)(void) = FUN_000ce3c0;
static void (*const bcde00_cc3ca0)(void) = hs_scripts_dispose;

__attribute__((naked, noinline))
void hs_runtime_update(void)
{
  __asm__ volatile(
      "movb 0x46b810, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lhs_runtime_update_6\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[gtime]\n\t"
      "movl %%eax, %%edi\n\t"
      "movl 0x5aa6c4, %%eax\n\t"
      "pushl $-1\n\t"
      "pushl %%eax\n\t"
      "xorb %%bl, %%bl\n\t"
      "call *%[c1198f0]\n\t"
      "movl %%eax, %%esi\n\t"
      "movb 0x46b810, %%al\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lhs_runtime_update_4\n\t"
      ".Lhs_runtime_update_1:\n\t"
      "cmpl $-1, %%esi\n\t"
      "je .Lhs_runtime_update_4\n\t"
      "movl 0x5aa6c4, %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movb 0x2(%%eax), %%cl\n\t"
      "addl $8, %%esp\n\t"
      "cmpb $2, %%cl\n\t"
      "jne .Lhs_runtime_update_2\n\t"
      "movb $1, %%bl\n\t"
      ".Lhs_runtime_update_2:\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jl .Lhs_runtime_update_3\n\t"
      "cmpl %%edi, %%eax\n\t"
      "jg .Lhs_runtime_update_3\n\t"
      "movl %%esi, %%eax\n\t"
      "call *%[ccd840]\n\t"
      ".Lhs_runtime_update_3:\n\t"
      "movl 0x5aa6c4, %%edx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edx\n\t"
      "call *%[c1198f0]\n\t"
      "movl %%eax, %%esi\n\t"
      "movb 0x46b810, %%al\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lhs_runtime_update_1\n\t"
      ".Lhs_runtime_update_4:\n\t"
      "call *%[cce3c0]\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "testb %%bl, %%bl\n\t"
      "popl %%ebx\n\t"
      "jne .Lhs_runtime_update_6\n\t"
      "call *%[gtime]\n\t"
      "andl $0x8000000f, %%eax\n\t"
      "jns .Lhs_runtime_update_5\n\t"
      "decl %%eax\n\t"
      "orl $0xfffffff0, %%eax\n\t"
      "incl %%eax\n\t"
      ".Lhs_runtime_update_5:\n\t"
      "jne .Lhs_runtime_update_6\n\t"
      "jmp .Lhs_runtime_update_10000\n\t"
      ".Lhs_runtime_update_6:\n\t"
      "ret\n\t"
      ".Lhs_runtime_update_10000:\n\t"
      "jmp *%[cc3ca0]\n\t"
      :
      : [gtime] "m"(bcde00_gtime), [c1198f0] "m"(bcde00_c1198f0), [dget] "m"(bcde00_dget), [ccd840] "m"(bcde00_ccd840), [cce3c0] "m"(bcde00_cce3c0), [cc3ca0] "m"(bcde00_cc3ca0)
      : "memory");
}
#else
#error "hs_runtime_update: clang naked draft required"
#endif


/* FUN_000ce050 (0xce050) — readable C lift. */
void FUN_000ce050(int save_type, int slot)
{
  char buf[0x100];
  crt_sprintf(buf, (const char *)0x280e94, save_type);
  game_state_data_new(buf, (int16_t)slot, 0xc);
}
/* FUN_000ce0c0 (0xce0c0) — readable C lift: prepend object-list node. */
void FUN_000ce0c0(data_t *data, int *head, int object_handle)
{
  extern char DAT_00280ea4[];
  int neu;
  char *node;

  neu = data_new_at_index(data);
  if (neu == -1) {
    error(2, DAT_00280ea4, data, (int)*(int16_t *)((char *)data + 0x20));
    return;
  }
  node = (char *)datum_get(data, neu);
  *(int *)(node + 4) = object_handle;
  *(int *)(node + 8) = *head;
  *head = neu;
}

/* FUN_000ce110 (0xce110) — readable C lift: delete linked datum chain. */
void FUN_000ce110(data_t *data, int link)
{
  char *node;

  while (link != -1) {
    node = (char *)datum_get(data, link);
    datum_delete(data, link);
    link = *(int *)(node + 8);
  }
}

/* FUN_000ce150 (0xce150) — readable C lift: init object list data arrays. */
void FUN_000ce150(void)
{
  extern char DAT_00280edc[];
  extern char DAT_00280ed0[];
  extern char DAT_00280e94[];
  char buf[0x100];

  *(data_t **)0x5aa698 = game_state_data_new(DAT_00280edc, 0x30, 0xc);
  crt_sprintf(buf, DAT_00280e94, DAT_00280ed0);
  *(data_t **)0x5aa694 = game_state_data_new(buf, 0x80, 0xc);
}

/* object_list_delete (0xce240) — readable C lift. */
void object_list_delete(int list_handle)
{
  extern char DAT_00280ef0[];
  extern char DAT_00280f0c[];
  char *node;

  if (list_handle == -1)
    return;
  node = (char *)datum_get(*(data_t **)0x5aa698, list_handle);
  if (*(int16_t *)(node + 4) != 0) {
    display_assert(DAT_00280ef0, DAT_00280f0c, 0x64, 1);
    system_exit(-1);
  }
  FUN_000ce110(*(data_t **)0x5aa694, *(int *)(node + 8));
  datum_delete(*(data_t **)0x5aa698, list_handle);
}

/* FUN_000ce3c0 (0xce3c0) — readable C lift. */
void FUN_000ce3c0(void)
{
  int index;
  short *datum;

  for (index = data_next_index(*(data_t **)0x5aa698, -1); index != -1;
       index = data_next_index(*(data_t **)0x5aa698, index)) {
    datum = (short *)datum_get(*(void **)0x5aa698, index);
    if (datum[2] == 0)
      object_list_delete(index);
  }
}



/* FUN_000c8720 (0xc8720) — XBE naked draft (batch 122). */
#if defined(__clang__)
static void *(*const bc8720_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void (*const bc8720_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const bc8720_exitfn)(int) = system_exit;
static bool (*const bc8720_cc73a0)(int datum_index) = FUN_000c73a0;
static bool (*const bc8720_cc74c0)(int datum_index) = FUN_000c74c0;
static void * (*const bc8720_cc3d00)(int16_t function_index) = hs_function_table_get;
static int (*const bc8720_c1d90f0)(char *buffer, const char *format, ...) = crt_sprintf;

__attribute__((naked, noinline))
char FUN_000c8720(int16_t function_index __attribute__((unused)), int root_datum __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "movl 0x5aa6c8, %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "movb $1, %%bl\n\t"
      "call *%[dget]\n\t"
      "movl 0x10(%%eax), %%edx\n\t"
      "movl 0x5aa6c8, %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "movl 0x8(%%eax), %%edi\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpw $7, %%si\n\t"
      "jl .LFUN_000c8720_1\n\t"
      "cmpw $0xc, %%si\n\t"
      "jle .LFUN_000c8720_2\n\t"
      ".LFUN_000c8720_1:\n\t"
      "pushl $1\n\t"
      "pushl $0x17d\n\t"
      "pushl $0x27cdc0\n\t"
      "pushl $0x27cfe0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000c8720_2:\n\t"
      "movl $0, -0x4(%%ebp)\n\t"
      ".LFUN_000c8720_3:\n\t"
      "cmpl $-1, %%edi\n\t"
      "je .LFUN_000c8720_8\n\t"
      "movl 0x5aa6c8, %%ecx\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "movb $1, %%bl\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x46b6fc, %%eax\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_000c8720_4\n\t"
      "pushl $1\n\t"
      "pushl $0x48e\n\t"
      "pushl $0x27bd0c\n\t"
      "pushl $0x27cbd4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000c8720_4:\n\t"
      "cmpw $0, 0x4(%%esi)\n\t"
      "jne .LFUN_000c8720_7\n\t"
      "movl $6, %%ebx\n\t"
      "movw %%bx, 0x4(%%esi)\n\t"
      "movl 0x5aa6c8, %%edx\n\t"
      "pushl %%edi\n\t"
      "pushl %%edx\n\t"
      "call *%[dget]\n\t"
      "movb 0x6(%%eax), %%cl\n\t"
      "addl $8, %%esp\n\t"
      "testb $1, %%cl\n\t"
      "je .LFUN_000c8720_5\n\t"
      "movw %%bx, 0x2(%%esi)\n\t"
      "call *%[cc73a0]\n\t"
      "jmp .LFUN_000c8720_6\n\t"
      ".LFUN_000c8720_5:\n\t"
      "movl %%edi, %%ebx\n\t"
      "call *%[cc74c0]\n\t"
      ".LFUN_000c8720_6:\n\t"
      "movb %%al, %%bl\n\t"
      ".LFUN_000c8720_7:\n\t"
      "movl 0x5aa6c8, %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movl 0x8(%%eax), %%edi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "addl $8, %%esp\n\t"
      "incl %%ecx\n\t"
      "testb %%bl, %%bl\n\t"
      "movl %%ecx, -0x4(%%ebp)\n\t"
      "jne .LFUN_000c8720_3\n\t"
      "jmp .LFUN_000c8720_9\n\t"
      ".LFUN_000c8720_8:\n\t"
      "testb %%bl, %%bl\n\t"
      "je .LFUN_000c8720_9\n\t"
      "cmpw $2, -0x4(%%ebp)\n\t"
      "jl .LFUN_000c8720_11\n\t"
      ".LFUN_000c8720_9:\n\t"
      "cmpw $0xa, %%si\n\t"
      "jne .LFUN_000c8720_10\n\t"
      "cmpw $2, -0x4(%%ebp)\n\t"
      "jg .LFUN_000c8720_12\n\t"
      ".LFUN_000c8720_10:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000c8720_11:\n\t"
      "cmpw $0xa, %%si\n\t"
      "jne .LFUN_000c8720_13\n\t"
      ".LFUN_000c8720_12:\n\t"
      "movl $0x25386f, %%eax\n\t"
      "jmp .LFUN_000c8720_14\n\t"
      ".LFUN_000c8720_13:\n\t"
      "movl $0x27cfd0, %%eax\n\t"
      ".LFUN_000c8720_14:\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[cc3d00]\n\t"
      "movl 0x4(%%eax), %%ecx\n\t"
      "addl $4, %%esp\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x27cfac\n\t"
      "pushl $0x46b704\n\t"
      "call *%[c1d90f0]\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "movl 0x5aa6c8, %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "movl $0x46b704, 0x46b6fc\n\t"
      "call *%[dget]\n\t"
      "movl 0xc(%%eax), %%ecx\n\t"
      "addl $0x18, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ecx, 0x46b700\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [dget] "m"(bc8720_dget), [assert] "m"(bc8720_assert), [exitfn] "m"(bc8720_exitfn), [cc73a0] "m"(bc8720_cc73a0), [cc74c0] "m"(bc8720_cc74c0), [cc3d00] "m"(bc8720_cc3d00), [c1d90f0] "m"(bc8720_c1d90f0)
      : "memory");
}
#else
#error "FUN_000c8720: clang naked draft required"
#endif


/* FUN_000c88b0 (0xc88b0) — readable C lift: hs type-check binary op args. */
char FUN_000c88b0(int16_t function_index, int root_datum)
{
  char ok;
  int out_handles[2];
  void *entry;
  const char *name;
  int left;
  int right;

  ok = 0;
  if (function_index != 0xd && function_index != 0xe) {
    display_assert((const char *)0x27d028, (const char *)0x27cdc0, 0x1bc, 1);
    system_exit(-1);
  }
  entry = hs_function_table_get(function_index);
  name = *(const char **)((char *)entry + 4);
  if (!FUN_000c55d0(name, out_handles, 2, root_datum))
    return 0;
  left = out_handles[0];
  right = out_handles[1];
  if (hs_type_check(left, 0)) {
    if (hs_type_check(
            right,
            *(short *)((char *)datum_get(*(data_t **)0x5aa6c8, left) + 4)))
      ok = 1;
  } else if (!*(int *)0x46b6fc) {
    if (hs_type_check(right, 0)) {
      if (hs_type_check(
              left,
              *(short *)((char *)datum_get(*(data_t **)0x5aa6c8, right) + 4)))
        ok = 1;
    } else if (!*(int *)0x46b6fc) {
      if (hs_type_check(left, 6) && hs_type_check(right, 6))
        ok = 1;
    }
  }
  return ok;
}

/* FUN_000c89c0 (0xc89c0) — XBE naked draft (batch 118). */
#if defined(__clang__)
static void (*const bc89c0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const bc89c0_exitfn)(int) = system_exit;
static void * (*const bc89c0_cc3d00)(int16_t function_index) = hs_function_table_get;
static char (*const bc89c0_cc55d0)(const char *name, int *out_handles, int16_t max_count, int root_handle) = FUN_000c55d0;
static bool (*const bc89c0_cc7d80)(int datum_index, int16_t check_type) = hs_type_check;
static void *(*const bc89c0_dget)(void *, int) = (void *(*)(void *, int))datum_get;

__attribute__((naked, noinline))
char FUN_000c89c0(int16_t function_index __attribute__((unused)), int root_datum __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xc, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "cmpw $0xf, %%si\n\t"
      "pushl %%edi\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "jl .LFUN_000c89c0_1\n\t"
      "cmpw $0x12, %%si\n\t"
      "jle .LFUN_000c89c0_2\n\t"
      ".LFUN_000c89c0_1:\n\t"
      "pushl $1\n\t"
      "pushl $0x1e3\n\t"
      "pushl $0x27cdc0\n\t"
      "pushl $0x27d078\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000c89c0_2:\n\t"
      "leal -0xc(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[cc3d00]\n\t"
      "movl 0x4(%%eax), %%ecx\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "addl $4, %%esp\n\t"
      "pushl %%ecx\n\t"
      "movl $2, %%ebx\n\t"
      "call *%[cc55d0]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000c89c0_10\n\t"
      "movl -0xc(%%ebp), %%esi\n\t"
      "pushl $0\n\t"
      "pushl %%esi\n\t"
      "call *%[cc7d80]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "movl $0x20, %%ebx\n\t"
      "je .LFUN_000c89c0_5\n\t"
      "movl 0x5aa6c8, %%edx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edx\n\t"
      "call *%[dget]\n\t"
      "addl $8, %%esp\n\t"
      "cmpw %%bx, 0x4(%%eax)\n\t"
      "jl .LFUN_000c89c0_3\n\t"
      "movl 0x5aa6c8, %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $0x24, 0x4(%%eax)\n\t"
      "jle .LFUN_000c89c0_4\n\t"
      ".LFUN_000c89c0_3:\n\t"
      "movl 0x5aa6c8, %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $6, 0x4(%%eax)\n\t"
      "jl .LFUN_000c89c0_5\n\t"
      "movl 0x5aa6c8, %%edx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edx\n\t"
      "call *%[dget]\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $8, 0x4(%%eax)\n\t"
      "jg .LFUN_000c89c0_5\n\t"
      ".LFUN_000c89c0_4:\n\t"
      "movl 0x5aa6c8, %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x4(%%eax), %%cx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[cc7d80]\n\t"
      "addl $0x10, %%esp\n\t"
      "jmp .LFUN_000c89c0_9\n\t"
      ".LFUN_000c89c0_5:\n\t"
      "movl 0x46b6fc, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_000c89c0_10\n\t"
      "movl -0x8(%%ebp), %%edi\n\t"
      "pushl $0\n\t"
      "pushl %%edi\n\t"
      "call *%[cc7d80]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000c89c0_8\n\t"
      "movl 0x5aa6c8, %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "addl $8, %%esp\n\t"
      "cmpw %%bx, 0x4(%%eax)\n\t"
      "jl .LFUN_000c89c0_6\n\t"
      "movl 0x5aa6c8, %%ecx\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $0x24, 0x4(%%eax)\n\t"
      "jle .LFUN_000c89c0_7\n\t"
      ".LFUN_000c89c0_6:\n\t"
      "movl 0x5aa6c8, %%edx\n\t"
      "pushl %%edi\n\t"
      "pushl %%edx\n\t"
      "call *%[dget]\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $6, 0x4(%%eax)\n\t"
      "jl .LFUN_000c89c0_8\n\t"
      "movl 0x5aa6c8, %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $8, 0x4(%%eax)\n\t"
      "jg .LFUN_000c89c0_8\n\t"
      ".LFUN_000c89c0_7:\n\t"
      "movl 0x5aa6c8, %%ecx\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x4(%%eax), %%dx\n\t"
      "pushl %%edx\n\t"
      "pushl %%esi\n\t"
      "call *%[cc7d80]\n\t"
      "addl $0x10, %%esp\n\t"
      "jmp .LFUN_000c89c0_9\n\t"
      ".LFUN_000c89c0_8:\n\t"
      "movl 0x46b6fc, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_000c89c0_10\n\t"
      "pushl $6\n\t"
      "pushl %%esi\n\t"
      "call *%[cc7d80]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000c89c0_10\n\t"
      "pushl $6\n\t"
      "pushl %%edi\n\t"
      "call *%[cc7d80]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_000c89c0_9:\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000c89c0_10\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      ".LFUN_000c89c0_10:\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(bc89c0_assert), [exitfn] "m"(bc89c0_exitfn), [cc3d00] "m"(bc89c0_cc3d00), [cc55d0] "m"(bc89c0_cc55d0), [cc7d80] "m"(bc89c0_cc7d80), [dget] "m"(bc89c0_dget)
      : "memory");
}
#else
#error "FUN_000c89c0: clang naked draft required"
#endif


/* FUN_000c8c50 (0xc8c50) — readable C lift. */
char FUN_000c8c50(int16_t function_index, int root_datum)
{
  char *node;
  char *parent;
  int a;
  int b;
  int c;
  char result;

  result = 0;
  if (function_index != 0x14) {
    display_assert((const char *)0x27d168, (const char *)0x27cdc0, 0x235, 1);
    system_exit(-1);
  }
  node = (char *)datum_get(*(data_t **)0x5aa6c8, root_datum);
  parent = (char *)datum_get(*(data_t **)0x5aa6c8, *(int *)(node + 0x10));
  a = *(int *)(parent + 8);
  if (a == -1) {
    *(int *)0x46b6fc = 0x27d120;
    node = (char *)datum_get(*(data_t **)0x5aa6c8, root_datum);
    *(int *)0x46b700 = *(int *)(node + 0xc);
    return result;
  }
  b = *(int *)((char *)datum_get(*(data_t **)0x5aa6c8, a) + 8);
  if (!hs_type_check(a, 5))
    return result;
  if (b == -1)
    return result;
  c = *(int *)((char *)datum_get(*(data_t **)0x5aa6c8, b) + 8);
  if (!hs_type_check(b, 7))
    return result;
  if (c == -1)
    return result;
  return (char)hs_type_check(c, 8);
}

/* FUN_000c8d30 (0xc8d30) — readable C lift. */
char FUN_000c8d30(int16_t function_index, int root_datum)
{
  char result;
  void *entry;
  const char *name;
  char *node;
  void *elem;
  short t;

  result = 0;
  if (function_index != 0x15) {
    display_assert((const char *)0x27d1bc, (const char *)0x27cdc0, 0x25d, 1);
    system_exit(-1);
  }
  entry = hs_function_table_get(function_index);
  name = *(const char **)((char *)entry + 4);
  if (!FUN_000c55d0(name, (int *)&function_index, 1, root_datum))
    return result;
  node = (char *)datum_get(*(data_t **)0x5aa6c8, function_index);
  if (!hs_type_check(function_index, 0xa))
    return result;
  elem = tag_block_get_element(
      (char *)global_scenario_get() + 0x49c,
      (int)*(short *)(node + 0x10),
      0x5c);
  t = *(short *)((char *)elem + 0x20);
  if (t == 3 || t == 4) {
    *(int *)0x46b6fc = 0x27d194;
    *(int *)0x46b700 = *(int *)(node + 0xc);
    return result;
  }
  return 1;
}

/* FUN_000c8f40 (0xc8f40) — readable C lift: coerce script expr list types. */
char FUN_000c8f40(int16_t function_index, int root_datum)
{
  char *root;
  char *node;
  int child;
  char ok;

  root = (char *)datum_get(*(data_t **)0x5aa6c8, root_datum);
  node = (char *)datum_get(*(data_t **)0x5aa6c8, *(int *)(root + 0x10));
  child = *(int *)(node + 8);
  ok = 1;
  if (function_index < 0x18 || function_index > 0x1a) {
    display_assert((const char *)0x27d2b0, (const char *)0x27cdc0, 0x2ae, 1);
    system_exit(-1);
  }
  while (child != -1) {
    node = (char *)datum_get(*(data_t **)0x5aa6c8, child);
    ok = 1;
    if (*(int *)0x46b6fc) {
      display_assert((const char *)0x27cbd4, (const char *)0x27bd0c, 0x48e, 1);
      system_exit(-1);
    }
    if (*(short *)(node + 4) == 0) {
      *(short *)(node + 4) = 9;
      node = (char *)datum_get(*(data_t **)0x5aa6c8, child);
      if ((*(unsigned char *)(node + 6) & 1) != 0) {
        *(short *)(node + 2) = 9;
        ok = (char)FUN_000c73a0(child);
      } else {
        ok = (char)FUN_000c74c0(child);
      }
    }
    node = (char *)datum_get(*(data_t **)0x5aa6c8, child);
    child = *(int *)(node + 8);
    if (!ok)
      break;
  }
  return ok;
}

/* render_debug_scripting (0xcb9c0) — XBE naked draft (batch 125). */
#if defined(__clang__)
static void (*const bcb9c0_chkstk)(void) = FUN_001d90e0;
static int (*const bcb9c0_c1d90f0)(char *buffer, const char *format, ...) = crt_sprintf;
static int (*const bcb9c0_c1198f0)(data_t *data, int prev_index) = data_next_index;
static void *(*const bcb9c0_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static char * (*const bcb9c0_ccaa80)(int thread_index) = hs_get_thread_script_name;
static int (*const bcb9c0_c8df60)(const char *s1) = csstrlen;
static int (*const bcb9c0_gtime)(void) = game_time_get;
static char * (*const bcb9c0_c8dc30)(char *destination, const char *source) = FUN_0008dc30;
static const char * (*const bcb9c0_cca890)(int datum_index) = FUN_000ca890;
static void (*const bcb9c0_c19b560)(void *stops, short count) = draw_string_set_tab_stops;
static void (*const bcb9c0_c189c40)(char flag, const char *string) = FUN_00189c40;

__attribute__((naked, noinline))
void render_debug_scripting(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl $0x2804, %%eax\n\t"
      "call *%[chkstk]\n\t"
      "movb 0x5aa69d, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lrender_debug_scripting_7\n\t"
      "pushl %%esi\n\t"
      "leal -0x2804(%%ebp), %%eax\n\t"
      "pushl $0x280950\n\t"
      "pushl %%eax\n\t"
      "movw $0xc8, -0x4(%%ebp)\n\t"
      "movw $0x12c, -0x2(%%ebp)\n\t"
      "call *%[c1d90f0]\n\t"
      "movl 0x5aa6c4, %%ecx\n\t"
      "pushl $-1\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1198f0]\n\t"
      "movl %%eax, %%esi\n\t"
      "movb 0x46b810, %%al\n\t"
      "addl $0x10, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lrender_debug_scripting_6\n\t"
      "pushl %%ebx\n\t"
      "leal (%%esp), %%esp\n\t"
      ".Lrender_debug_scripting_1:\n\t"
      "cmpl $-1, %%esi\n\t"
      "je .Lrender_debug_scripting_5\n\t"
      "movl 0x5aa6c4, %%edx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edx\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl 0x8(%%ebx), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jl .Lrender_debug_scripting_4\n\t"
      "call *%[ccaa80]\n\t"
      "pushl %%eax\n\t"
      "leal -0x2804(%%ebp), %%eax\n\t"
      "pushl $0x26990c\n\t"
      "pushl %%eax\n\t"
      "call *%[c8df60]\n\t"
      "leal -0x2804(%%ebp,%%eax,1), %%ecx\n\t"
      "addl $4, %%esp\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1d90f0]\n\t"
      "movl 0x8(%%ebx), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lrender_debug_scripting_2\n\t"
      "call *%[gtime]\n\t"
      "movl 0x8(%%ebx), %%ecx\n\t"
      "subl %%eax, %%ecx\n\t"
      "jmp .Lrender_debug_scripting_3\n\t"
      ".Lrender_debug_scripting_2:\n\t"
      "xorl %%ecx, %%ecx\n\t"
      ".Lrender_debug_scripting_3:\n\t"
      "pushl %%ecx\n\t"
      "leal -0x2804(%%ebp), %%edx\n\t"
      "pushl $0x25acb8\n\t"
      "pushl %%edx\n\t"
      "call *%[c8df60]\n\t"
      "leal -0x2804(%%ebp,%%eax,1), %%eax\n\t"
      "addl $4, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d90f0]\n\t"
      "leal -0x2804(%%ebp), %%ecx\n\t"
      "pushl $0x28094c\n\t"
      "pushl %%ecx\n\t"
      "call *%[c8dc30]\n\t"
      "movl 0x10(%%ebx), %%eax\n\t"
      "leal 0x18(%%ebx), %%edx\n\t"
      "addl $0x14, %%esp\n\t"
      "cmpl %%edx, %%eax\n\t"
      "je .Lrender_debug_scripting_4\n\t"
      "cmpl $-2, 0x8(%%ebx)\n\t"
      "je .Lrender_debug_scripting_4\n\t"
      "movl 0x4(%%eax), %%eax\n\t"
      "movl %%esi, %%ebx\n\t"
      "call *%[cca890]\n\t"
      "pushl %%eax\n\t"
      "leal -0x2804(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c8dc30]\n\t"
      "addl $8, %%esp\n\t"
      ".Lrender_debug_scripting_4:\n\t"
      "movl 0x5aa6c4, %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1198f0]\n\t"
      "movl %%eax, %%esi\n\t"
      "movb 0x46b810, %%al\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lrender_debug_scripting_1\n\t"
      ".Lrender_debug_scripting_5:\n\t"
      "popl %%ebx\n\t"
      ".Lrender_debug_scripting_6:\n\t"
      "leal -0x4(%%ebp), %%edx\n\t"
      "pushl $2\n\t"
      "pushl %%edx\n\t"
      "movb $0, -0x2404(%%ebp)\n\t"
      "call *%[c19b560]\n\t"
      "leal -0x2804(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $1\n\t"
      "call *%[c189c40]\n\t"
      "leal -0x4(%%ebp), %%ecx\n\t"
      "pushl $0\n\t"
      "pushl %%ecx\n\t"
      "call *%[c19b560]\n\t"
      "addl $0x18, %%esp\n\t"
      "popl %%esi\n\t"
      ".Lrender_debug_scripting_7:\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [chkstk] "m"(bcb9c0_chkstk), [c1d90f0] "m"(bcb9c0_c1d90f0), [c1198f0] "m"(bcb9c0_c1198f0), [dget] "m"(bcb9c0_dget), [ccaa80] "m"(bcb9c0_ccaa80), [c8df60] "m"(bcb9c0_c8df60), [gtime] "m"(bcb9c0_gtime), [c8dc30] "m"(bcb9c0_c8dc30), [cca890] "m"(bcb9c0_cca890), [c19b560] "m"(bcb9c0_c19b560), [c189c40] "m"(bcb9c0_c189c40)
      : "memory");
}
#else
#error "render_debug_scripting: clang naked draft required"
#endif


/* render_debug_trigger_volumes (0xcbb40) — XBE naked draft (batch 107). */
#if defined(__clang__)
static scenario_t * (*const bcbb40_c18e380)(void) = global_scenario_get;
static void *(*const bcbb40_elem)(void *, int, int) = tag_block_get_element;
static void (*const bcbb40_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const bcbb40_exitfn)(int) = system_exit;
static void (*const bcbb40_m4x3)(void *, float *, float *, float *) = matrix4x3_from_forward_up_position;
static void (*const bcbb40_mscale)(float *, float *, float *) = matrix_scale_transform_vector;
static void (*const bcbb40_c189ba0)(float *points, short count, void *color) = FUN_00189ba0;
static void (*const bcbb40_c188a90)(float *points, short count, void *color) = FUN_00188a90;
static bool (*const bcbb40_ray)(unsigned int, float *, float *, int, short *) = FUN_0014df70;
static void (*const bcbb40_c189cb0)(char flag, void *position, void *string, int color) = FUN_00189cb0;

__attribute__((naked, noinline))
void render_debug_trigger_volumes(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x120, %%esp\n\t"
      "movb 0x5aa69c, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lrender_debug_trigger_volumes_15\n\t"
      "pushl %%ebx\n\t"
      "call *%[c18e380]\n\t"
      "movl 0x360(%%eax), %%ecx\n\t"
      "addl $0x360, %%eax\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "cmpl %%ebx, %%ecx\n\t"
      "movl %%ebx, -0x6c(%%ebp)\n\t"
      "movl %%eax, -0x70(%%ebp)\n\t"
      "jle .Lrender_debug_trigger_volumes_14\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "jmp .Lrender_debug_trigger_volumes_2\n\t"
      ".Lrender_debug_trigger_volumes_1:\n\t"
      "movl -0x70(%%ebp), %%eax\n\t"
      "movl %%edi, %%edi\n\t"
      ".Lrender_debug_trigger_volumes_2:\n\t"
      "pushl $0x60\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movswl (%%eax), %%ecx\n\t"
      "addl $0xc, %%esp\n\t"
      "subl $0, %%ecx\n\t"
      "movl %%eax, -0x68(%%ebp)\n\t"
      "je .Lrender_debug_trigger_volumes_4\n\t"
      "decl %%ecx\n\t"
      "je .Lrender_debug_trigger_volumes_3\n\t"
      "pushl $1\n\t"
      "pushl $0x213\n\t"
      "pushl $0x2805bc\n\t"
      "pushl $0x255ee8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "jmp .Lrender_debug_trigger_volumes_5\n\t"
      ".Lrender_debug_trigger_volumes_3:\n\t"
      "leal 0x54(%%eax), %%ecx\n\t"
      "movl %%ecx, %%edx\n\t"
      "movl (%%edx), %%esi\n\t"
      "movl %%esi, -0x24(%%ebp)\n\t"
      "movl 0x4(%%edx), %%esi\n\t"
      "movl %%esi, -0x20(%%ebp)\n\t"
      "movl 0x8(%%edx), %%edx\n\t"
      "movl %%edx, -0x1c(%%ebp)\n\t"
      "movl (%%ecx), %%edx\n\t"
      "movl %%edx, -0x30(%%ebp)\n\t"
      "movl 0x4(%%ecx), %%edx\n\t"
      "movl %%edx, -0x2c(%%ebp)\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "leal 0x3c(%%eax), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl %%ecx, -0x28(%%ebp)\n\t"
      "leal 0x30(%%eax), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "addl $0x48, %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0xd0(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[m4x3]\n\t"
      "leal -0x30(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x24(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0xd0(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[mscale]\n\t"
      "addl $0x1c, %%esp\n\t"
      "jmp .Lrender_debug_trigger_volumes_5\n\t"
      ".Lrender_debug_trigger_volumes_4:\n\t"
      "movl 0x31fc60, %%esi\n\t"
      "movl $0xd, %%ecx\n\t"
      "leal -0xd0(%%ebp), %%edi\n\t"
      "rep movsl\n\t"
      "flds 0x58(%%eax)\n\t"
      "flds 0x50(%%eax)\n\t"
      "movl 0x48(%%eax), %%ecx\n\t"
      "movl %%ecx, -0xa8(%%ebp)\n\t"
      "fstps -0xa4(%%ebp)\n\t"
      "fstps -0xa0(%%ebp)\n\t"
      "flds 0x5c(%%eax)\n\t"
      "fsubs 0x58(%%eax)\n\t"
      "flds 0x54(%%eax)\n\t"
      "fsubs 0x50(%%eax)\n\t"
      "flds 0x4c(%%eax)\n\t"
      "fsubs 0x48(%%eax)\n\t"
      "fstps -0x24(%%ebp)\n\t"
      "movl -0x24(%%ebp), %%edx\n\t"
      "movl %%edx, -0x30(%%ebp)\n\t"
      "fstps -0x20(%%ebp)\n\t"
      "movl -0x20(%%ebp), %%eax\n\t"
      "movl %%eax, -0x2c(%%ebp)\n\t"
      "fstps -0x1c(%%ebp)\n\t"
      "movl -0x1c(%%ebp), %%ecx\n\t"
      "movl %%ecx, -0x28(%%ebp)\n\t"
      ".Lrender_debug_trigger_volumes_5:\n\t"
      "movl %%ebx, %%ecx\n\t"
      "sarl $5, %%ebx\n\t"
      "andl $0x1f, %%ecx\n\t"
      "movl $1, %%edi\n\t"
      "leal 0x5aa6a0(,%%ebx,4), %%edx\n\t"
      "shll %%cl, %%edi\n\t"
      "movl %%edx, -0x8c(%%ebp)\n\t"
      "xorl %%esi, %%esi\n\t"
      "movl $6, -0x64(%%ebp)\n\t"
      "jmp .Lrender_debug_trigger_volumes_6\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".Lrender_debug_trigger_volumes_6:\n\t"
      "xorl %%eax, %%eax\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "movl %%esi, %%eax\n\t"
      "cdq\n\t"
      "subl %%edx, %%eax\n\t"
      "movl %%esi, %%ecx\n\t"
      "sarl $1, %%eax\n\t"
      "andl $0x80000001, %%ecx\n\t"
      "movl $0, -0x18(%%ebp)\n\t"
      "jns .Lrender_debug_trigger_volumes_7\n\t"
      "decl %%ecx\n\t"
      "orl $0xfffffffe, %%ecx\n\t"
      "incl %%ecx\n\t"
      ".Lrender_debug_trigger_volumes_7:\n\t"
      "testw %%cx, %%cx\n\t"
      "movl $3, %%ebx\n\t"
      "je .Lrender_debug_trigger_volumes_8\n\t"
      "movswl %%ax, %%ecx\n\t"
      "flds -0x30(%%ebp)\n\t"
      "fadds -0xa8(%%ebp)\n\t"
      "leal 0x1(%%ecx), %%eax\n\t"
      "cdq\n\t"
      "idivl %%ebx\n\t"
      "fstps -0x60(%%ebp)\n\t"
      "flds -0x2c(%%ebp)\n\t"
      "fadds -0xa4(%%ebp)\n\t"
      "fstps -0x5c(%%ebp)\n\t"
      "flds -0x28(%%ebp)\n\t"
      "fadds -0xa0(%%ebp)\n\t"
      "fstps -0x58(%%ebp)\n\t"
      "leal 0x2(%%ecx), %%eax\n\t"
      "movl %%ebx, %%ecx\n\t"
      "shll $2, %%edx\n\t"
      "flds -0x24(%%ebp,%%edx,1)\n\t"
      "fchs\n\t"
      "fstps -0x18(%%ebp,%%edx,1)\n\t"
      "cdq\n\t"
      "idivl %%ecx\n\t"
      "leal -0x18(%%ebp), %%eax\n\t"
      "leal -0xd0(%%ebp), %%ecx\n\t"
      "shll $2, %%edx\n\t"
      "flds -0x24(%%ebp,%%edx,1)\n\t"
      "fchs\n\t"
      "fstps -0xc(%%ebp,%%edx,1)\n\t"
      "leal -0x18(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[mscale]\n\t"
      "leal -0xc(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0xc(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0xd0(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "jmp .Lrender_debug_trigger_volumes_9\n\t"
      ".Lrender_debug_trigger_volumes_8:\n\t"
      "movl -0xa4(%%ebp), %%ecx\n\t"
      "movl -0xa8(%%ebp), %%edx\n\t"
      "movl %%edx, -0x60(%%ebp)\n\t"
      "movl -0xa0(%%ebp), %%edx\n\t"
      "movl %%ecx, -0x5c(%%ebp)\n\t"
      "movswl %%ax, %%ecx\n\t"
      "movl %%edx, -0x58(%%ebp)\n\t"
      "leal 0x1(%%ecx), %%eax\n\t"
      "cdq\n\t"
      "idivl %%ebx\n\t"
      "shll $2, %%edx\n\t"
      "movl -0x24(%%ebp,%%edx,1), %%eax\n\t"
      "movl %%eax, -0x18(%%ebp,%%edx,1)\n\t"
      "leal 0x2(%%ecx), %%eax\n\t"
      "cdq\n\t"
      "movl $3, %%ecx\n\t"
      "idivl %%ecx\n\t"
      "leal -0x18(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "shll $2, %%edx\n\t"
      "movl -0x24(%%ebp,%%edx,1), %%eax\n\t"
      "movl %%eax, -0xc(%%ebp,%%edx,1)\n\t"
      "leal -0x18(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0xd0(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[mscale]\n\t"
      "leal -0xc(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0xc(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0xd0(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      ".Lrender_debug_trigger_volumes_9:\n\t"
      "call *%[mscale]\n\t"
      "flds -0x60(%%ebp)\n\t"
      "fadds -0x18(%%ebp)\n\t"
      "movl -0x8c(%%ebp), %%ebx\n\t"
      "movl (%%ebx), %%eax\n\t"
      "addl $0x18, %%esp\n\t"
      "testl %%edi, %%eax\n\t"
      "fstps -0x54(%%ebp)\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fadds -0x5c(%%ebp)\n\t"
      "fstps -0x50(%%ebp)\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fadds -0x58(%%ebp)\n\t"
      "fstps -0x4c(%%ebp)\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fadds -0x54(%%ebp)\n\t"
      "fstps -0x48(%%ebp)\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fadds -0x50(%%ebp)\n\t"
      "fstps -0x44(%%ebp)\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fadds -0x4c(%%ebp)\n\t"
      "fstps -0x40(%%ebp)\n\t"
      "flds -0x48(%%ebp)\n\t"
      "fsubs -0x18(%%ebp)\n\t"
      "fstps -0x3c(%%ebp)\n\t"
      "flds -0x44(%%ebp)\n\t"
      "fsubs -0x14(%%ebp)\n\t"
      "fstps -0x38(%%ebp)\n\t"
      "flds -0x40(%%ebp)\n\t"
      "fsubs -0x10(%%ebp)\n\t"
      "fstps -0x34(%%ebp)\n\t"
      "je .Lrender_debug_trigger_volumes_10\n\t"
      "movl 0x2ee6d8, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x60(%%ebp), %%edx\n\t"
      "pushl $4\n\t"
      "pushl %%edx\n\t"
      "call *%[c189ba0]\n\t"
      "addl $0xc, %%esp\n\t"
      "jmp .Lrender_debug_trigger_volumes_11\n\t"
      ".Lrender_debug_trigger_volumes_10:\n\t"
      "movl 0x2ee6d8, %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "movl %%ecx, -0x9c(%%ebp)\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl %%edx, -0x98(%%ebp)\n\t"
      "movl 0x8(%%eax), %%ecx\n\t"
      "movl %%ecx, -0x94(%%ebp)\n\t"
      "movl 0xc(%%eax), %%edx\n\t"
      "movl 0x2ee6d0, %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x60(%%ebp), %%ecx\n\t"
      "pushl $4\n\t"
      "pushl %%ecx\n\t"
      "movl %%edx, -0x90(%%ebp)\n\t"
      "movl $0x3e19999a, -0x9c(%%ebp)\n\t"
      "call *%[c189ba0]\n\t"
      "leal -0x9c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x60(%%ebp), %%eax\n\t"
      "pushl $4\n\t"
      "pushl %%eax\n\t"
      "call *%[c188a90]\n\t"
      "addl $0x18, %%esp\n\t"
      ".Lrender_debug_trigger_volumes_11:\n\t"
      "movl -0x64(%%ebp), %%eax\n\t"
      "incl %%esi\n\t"
      "decl %%eax\n\t"
      "movl %%eax, -0x64(%%ebp)\n\t"
      "jne .Lrender_debug_trigger_volumes_6\n\t"
      "flds -0x30(%%ebp)\n\t"
      "leal -0x120(%%ebp), %%ecx\n\t"
      "fmuls 0x253398\n\t"
      "pushl %%ecx\n\t"
      "pushl $-1\n\t"
      "leal -0x88(%%ebp), %%edx\n\t"
      "fadds -0xa8(%%ebp)\n\t"
      "pushl %%edx\n\t"
      "pushl $0x506550\n\t"
      "pushl $0xc2ad\n\t"
      "fstps -0x7c(%%ebp)\n\t"
      "flds -0x2c(%%ebp)\n\t"
      "fmuls 0x253398\n\t"
      "fadds -0xa4(%%ebp)\n\t"
      "fstps -0x78(%%ebp)\n\t"
      "flds -0x28(%%ebp)\n\t"
      "fmuls 0x253398\n\t"
      "fadds -0xa0(%%ebp)\n\t"
      "fstps -0x74(%%ebp)\n\t"
      "flds -0x7c(%%ebp)\n\t"
      "fsubs 0x506550\n\t"
      "flds -0x78(%%ebp)\n\t"
      "fsubs 0x506554\n\t"
      "flds -0x74(%%ebp)\n\t"
      "fsubs 0x506558\n\t"
      "fstps -0x80(%%ebp)\n\t"
      "fxch %%st(1)\n\t"
      "fmuls 0x255ed4\n\t"
      "fstps -0x88(%%ebp)\n\t"
      "fmuls 0x255ed4\n\t"
      "fstps -0x84(%%ebp)\n\t"
      "flds -0x80(%%ebp)\n\t"
      "fmuls 0x255ed4\n\t"
      "fstps -0x80(%%ebp)\n\t"
      "call *%[ray]\n\t"
      "addl $0x14, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lrender_debug_trigger_volumes_13\n\t"
      "movl (%%ebx), %%eax\n\t"
      "movl -0x68(%%ebp), %%ecx\n\t"
      "addl $4, %%ecx\n\t"
      "testl %%edi, %%eax\n\t"
      "movl 0x2ee6e0, %%eax\n\t"
      "leal -0x7c(%%ebp), %%edx\n\t"
      "jne .Lrender_debug_trigger_volumes_12\n\t"
      "movl 0x2ee6c4, %%eax\n\t"
      ".Lrender_debug_trigger_volumes_12:\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl $1\n\t"
      "call *%[c189cb0]\n\t"
      "addl $0x10, %%esp\n\t"
      ".Lrender_debug_trigger_volumes_13:\n\t"
      "movl -0x6c(%%ebp), %%eax\n\t"
      "incl %%eax\n\t"
      "movswl %%ax, %%ebx\n\t"
      "movl %%eax, -0x6c(%%ebp)\n\t"
      "movl -0x70(%%ebp), %%eax\n\t"
      "cmpl (%%eax), %%ebx\n\t"
      "jl .Lrender_debug_trigger_volumes_1\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      ".Lrender_debug_trigger_volumes_14:\n\t"
      "popl %%ebx\n\t"
      ".Lrender_debug_trigger_volumes_15:\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c18e380] "m"(bcbb40_c18e380), [elem] "m"(bcbb40_elem), [assert] "m"(bcbb40_assert), [exitfn] "m"(bcbb40_exitfn), [m4x3] "m"(bcbb40_m4x3), [mscale] "m"(bcbb40_mscale), [c189ba0] "m"(bcbb40_c189ba0), [c188a90] "m"(bcbb40_c188a90), [ray] "m"(bcbb40_ray), [c189cb0] "m"(bcbb40_c189cb0)
      : "memory");
}
#else
#error "render_debug_trigger_volumes: clang naked draft required"
#endif


/* hs_evaluate_wake (0xcc0e0) — XBE naked draft (batch 136). */
#if defined(__clang__)
static void *(*const bcc0e0_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void (*const bcc0e0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const bcc0e0_exitfn)(int) = system_exit;
static int (*const bcc0e0_ccada0)(int16_t script_index) = FUN_000cada0;
static void (*const bcc0e0_ccacf0)(int thread_index) = FUN_000cacf0;
static void (*const bcc0e0_ccbf80)(int thread_handle, int value) = hs_return;

__attribute__((naked, noinline))
void hs_evaluate_wake(int16_t function_index __attribute__((unused)), int thread_datum __attribute__((unused)), char init __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl 0x5aa6c4, %%eax\n\t"
      "pushl %%ebx\n\t"
      "movl 0xc(%%ebp), %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl 0x10(%%eax), %%ecx\n\t"
      "movl 0x4(%%ecx), %%edx\n\t"
      "movl 0x5aa6c8, %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl 0x10(%%eax), %%ecx\n\t"
      "movl 0x5aa6c8, %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[dget]\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl 0x5aa6c8, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "addl $0x20, %%esp\n\t"
      "cmpw $0x15, 0x8(%%ebp)\n\t"
      "movl %%eax, %%esi\n\t"
      "je .Lhs_evaluate_wake_1\n\t"
      "pushl $1\n\t"
      "pushl $0x22c\n\t"
      "pushl $0x280478\n\t"
      "pushl $0x27d1bc\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lhs_evaluate_wake_1:\n\t"
      "testb $1, 0x6(%%esi)\n\t"
      "jne .Lhs_evaluate_wake_2\n\t"
      "pushl $1\n\t"
      "pushl $0x22d\n\t"
      "pushl $0x280478\n\t"
      "pushl $0x2809a0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lhs_evaluate_wake_2:\n\t"
      "cmpw $0xa, 0x4(%%esi)\n\t"
      "je .Lhs_evaluate_wake_3\n\t"
      "pushl $1\n\t"
      "pushl $0x22e\n\t"
      "pushl $0x280478\n\t"
      "pushl $0x280978\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lhs_evaluate_wake_3:\n\t"
      "movw 0x10(%%esi), %%di\n\t"
      "call *%[ccada0]\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lhs_evaluate_wake_4\n\t"
      "movl %%eax, %%edi\n\t"
      "call *%[ccacf0]\n\t"
      ".Lhs_evaluate_wake_4:\n\t"
      "pushl $0\n\t"
      "pushl %%ebx\n\t"
      "call *%[ccbf80]\n\t"
      "addl $8, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [dget] "m"(bcc0e0_dget), [assert] "m"(bcc0e0_assert), [exitfn] "m"(bcc0e0_exitfn), [ccada0] "m"(bcc0e0_ccada0), [ccacf0] "m"(bcc0e0_ccacf0), [ccbf80] "m"(bcc0e0_ccbf80)
      : "memory");
}
#else
#error "hs_evaluate_wake: clang naked draft required"
#endif


/* FUN_000cdf70 (0xcdf70) — readable C lift. */
void FUN_000cdf70(void *header, void *src, int size)
{
  int rem;
  int n;

  (void)header;
  if (size == 0)
    return;
  if ((unsigned int)size < 0x38u) {
    display_assert((const char *)0x280e48, (const char *)0x280e68, 0x6d, 1);
    system_exit(-1);
  }
  if (csmemcmp(src, (void *)0x280e38, 0xc) == 0) {
    FUN_00118be0((void *)0x2f664c, src, 1);
    FUN_00118be0((void *)0x2f6688, src, 0x4000);
    return;
  }
  rem = size - 0x38;
  if (rem < 0 || (rem % 0x14) != 0) {
    display_assert((const char *)0x280df8, (const char *)0x280e68, 0x79, 1);
    system_exit(-1);
  }
  if (rem < 0 || (rem % 0x14) != 0)
    return;
  n = rem / 0x14;
  FUN_00118be0((void *)0x2f664c, src, 1);
  FUN_00118be0((void *)0x2f6688, (char *)src + 0x38, n);
}

/* FUN_000ce4a0 (0xce4a0) — readable C lift. */
void FUN_000ce4a0(void)
{
  int handle = *(int *)0x46b814;
  if (handle)
    CloseHandle(handle);
}

/* --- hs_runtime.obj orphan shells (2026-07-26) --- */

/* FUN_000c9f90 (0xc9f90) — readable C lift: sound/looping-sound tag float ptr. */
float *FUN_000c9f90(int object_handle)
{
  int idx;
  void *tag;
  int *count_ptr;
  void *elem;

  idx = tag_loaded(0x736e6421, (const char *)object_handle);
  if (idx != -1) {
    tag = tag_get(0x736e6421, idx);
    return (float *)((char *)tag + 0x28);
  }
  idx = tag_loaded(0x6c736e64, (const char *)object_handle);
  if (idx != -1) {
    tag = tag_get(0x6c736e64, idx);
    count_ptr = (int *)((char *)tag + 0x3c);
    if (*count_ptr > 0) {
      elem = tag_block_get_element(count_ptr, 0, 0xa0);
      return (float *)((char *)elem + 4);
    }
  }
  console_printf(0, (const char *)0x280430, object_handle);
  return 0;
}

/* hs_wake_by_name (0xcb9a0) — readable C lift. */
char hs_wake_by_name(const char *script_name)
{
  int idx = FUN_000cae00(script_name);
  if (idx == -1)
    return 0;
  FUN_000cacf0(idx);
  return 1;
}

