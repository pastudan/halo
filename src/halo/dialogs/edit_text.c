/* Check if the object's "front" marker faces away from the aim direction
 * (0x971a0). Returns false if the marker forward dot aim > 0 (facing towards
 * aim), true otherwise (facing away, or if the object/marker can't be
 * resolved). */
bool FUN_000971a0(int object_handle, float *position, float *aim_position)
{
  char *obj = (char *)object_try_and_get_and_verify_type(object_handle, 0x100);
  if (obj && (*(uint8_t *)(obj + 0x1c4) & 1) == 0) {
    char marker_buf[0x6c];
    int16_t count =
      object_get_markers_by_string_id(object_handle, "front", marker_buf, 1);
    if (count == 1) {
      float *fwd = (float *)(marker_buf + 0x3c);
      float dot = fwd[0] * aim_position[0] + fwd[1] * aim_position[1] +
                  fwd[2] * aim_position[2];
      if (dot > 0.0f) {
        return false;
      }
    }
  }
  return true;
}

/* Clamp cursor and selection to valid range [0, strlen] (0x972b0).
 * If cursor == selection after clamping, cancels the selection.
 * Snaps both to valid character boundaries via unicode_snap_cursor. */
void edit_text_clamp_cursor(void *edit_text)
{
  int *et = (int *)edit_text;
  int16_t len = (int16_t)csstrlen((const char *)et[0]);

  int16_t cursor = *(int16_t *)((int)et + 6);
  int16_t clamped_cursor;
  if (cursor < 0) {
    clamped_cursor = 0;
  } else if (cursor > len) {
    clamped_cursor = len;
  } else {
    clamped_cursor = cursor;
  }

  int16_t sel = *(int16_t *)((int)et + 8);
  *(int16_t *)((int)et + 6) = clamped_cursor;
  int16_t clamped_sel;
  if (sel < -1) {
    clamped_sel = -1;
  } else if (sel > len) {
    clamped_sel = len;
  } else {
    clamped_sel = sel;
  }

  *(int16_t *)((int)et + 8) = clamped_sel;
  if (clamped_cursor == clamped_sel) {
    *(int16_t *)((int)et + 8) = -1;
  }

  unicode_snap_cursor((const char *)et[0], (int16_t *)((int)et + 6));
  if (*(int16_t *)((int)et + 8) != -1) {
    unicode_snap_cursor((const char *)et[0], (int16_t *)((int)et + 8));
  }
}

/* Moves the text cursor to the end of the edit text buffer and
 * clears any active selection. Asserts that the edit_text struct
 * is valid (non-null, has buffer, max_length > 0, strlen <= max). */
void edit_text_set_cursor_to_end(void *edit_text)
{
  int *et = (int *)edit_text;

  if (et == NULL || et[0] == 0 || *(int16_t *)((int)et + 4) <= 0 ||
      (unsigned int)csstrlen((const char *)et[0]) >
        (unsigned int)(int)*(int16_t *)((int)et + 4)) {
    display_assert("valid_edit_text(edit)",
                   "c:\\halo\\SOURCE\\dialogs\\edit_text.c", 0x9f, 1);
    system_exit(-1);
  }

  edit_text_clamp_cursor(edit_text);

  int16_t len = (int16_t)csstrlen((const char *)et[0]);
  *(int16_t *)((int)et + 6) = len;
  *(int16_t *)((int)et + 8) = -1;
}

/* Get the selection range as ordered (min, max) of cursor and anchor (0x973a0).
 * Returns false if no selection is active (selection_start == -1). */
bool edit_text_get_selection_range(void *edit_text, int16_t *out_start,
                                   int16_t *out_end)
{
  int *et = (int *)edit_text;

  if (et == NULL || et[0] == 0 || *(int16_t *)((int)et + 4) <= 0 ||
      (unsigned int)csstrlen((const char *)et[0]) >
        (unsigned int)(int)*(int16_t *)((int)et + 4)) {
    display_assert("valid_edit_text(edit)",
                   "c:\\halo\\SOURCE\\dialogs\\edit_text.c", 0xae, 1);
    system_exit(-1);
  }

  edit_text_clamp_cursor(edit_text);

  int16_t sel = *(int16_t *)((int)et + 8);
  if (sel == -1)
    return false;

  int16_t cursor = *(int16_t *)((int)et + 6);
  *out_start = (sel > cursor) ? cursor : sel;

  sel = *(int16_t *)((int)et + 8);
  cursor = *(int16_t *)((int)et + 6);
  *out_end = (sel > cursor) ? sel : cursor;

  return true;
}

/* Validates the edit_text struct and initializes cursor state by
 * placing the cursor at the end of the current text. */
void edit_text_initialize(void *edit_text)
{
  int *et = (int *)edit_text;

  if (et == NULL || et[0] == 0 || *(int16_t *)((int)et + 4) <= 0 ||
      (unsigned int)csstrlen((const char *)et[0]) >
        (unsigned int)(int)*(int16_t *)((int)et + 4)) {
    display_assert("valid_edit_text(edit)",
                   "c:\\halo\\SOURCE\\dialogs\\edit_text.c", 0x19, 1);
    system_exit(-1);
  }

  edit_text_set_cursor_to_end(edit_text);
}

/* Processes a single key event for the edit_text widget. Handles:
 * - Character insertion (with or without active selection)
 * - Left/Right arrow keys for cursor movement
 * - Shift+arrow for extending selection
 * - Backspace/Delete for character or selection deletion
 * When a selection is active, typing replaces it. Backspace/Delete
 * remove the selection range. Arrow keys collapse the selection to
 * the appropriate end. All cursor changes are snapped to unicode
 * character boundaries via unicode_snap_cursor.
 *
 * key_event layout:
 *   offset 0: uint8_t flags (bit 0 = shift held)
 *   offset 1: uint8_t character code
 *   offset 2: int16_t key code (0x1d=backspace, 0x54=delete, 0x4f=left,
 * 0x50=right)
 *
 * edit_text layout:
 *   offset 0: char* text buffer pointer
 *   offset 4: int16_t max_length
 *   offset 6: int16_t cursor_pos
 *   offset 8: int16_t selection (-1 = no selection)
 */
void edit_text_process_key(void *edit_text, void *keystroke)
{
  int *et = (int *)edit_text;
  unsigned char *key = (unsigned char *)keystroke;
  int16_t sel_start, sel_end;
  int text;
  int len;
  int cursor_pos;

  if (et == NULL || et[0] == 0 || *(int16_t *)((int)et + 4) <= 0 ||
      (unsigned int)csstrlen((const char *)et[0]) >
        (unsigned int)(int)*(int16_t *)((int)et + 4)) {
    display_assert("valid_edit_text(edit)",
                   "c:\\halo\\SOURCE\\dialogs\\edit_text.c", 0x23, 1);
    system_exit(-1);
  }

  edit_text_clamp_cursor(edit_text);

  int16_t key_code = *(int16_t *)(key + 2);

  /* --- Backspace / Delete --- */
  if (key_code == 0x1d || key_code == 0x54) {
    /* If there is an active selection, delete the selected range */
    if (edit_text_get_selection_range(edit_text, &sel_end, &sel_start)) {
      text = et[0];
      len = csstrlen((const char *)(text + (int)sel_start));
      csmemmove((void *)(text + (int)sel_end),
                (const void *)(text + (int)sel_start), (unsigned int)(len + 1));
      *(int16_t *)((int)et + 6) = sel_end;
      *(int16_t *)((int)et + 8) = -1;
      unicode_snap_cursor((const char *)et[0], (int16_t *)((int)et + 6));
      return;
    }

    if (key_code == 0x1d) {
      /* Backspace: delete character before cursor */
      int16_t old_cursor = *(int16_t *)((int)et + 6);
      if (old_cursor > 0) {
        unicode_cursor_backward((const char *)et[0], (int16_t *)((int)et + 6));
        text = et[0];
        len = csstrlen((const char *)(text + (int)old_cursor));
        csmemmove((void *)(text + (int)*(int16_t *)((int)et + 6)),
                  (const void *)(text + (int)old_cursor),
                  (unsigned int)(len + 1));
      }
    } else {
      /* Delete: delete character at cursor */
      int16_t cur = *(int16_t *)((int)et + 6);
      if ((unsigned int)(int)cur >= (unsigned int)csstrlen((const char *)et[0]))
        goto snap_and_return;

      int16_t temp_cursor = cur;
      unicode_cursor_forward((const char *)et[0], &temp_cursor);
      text = et[0];
      len = csstrlen((const char *)(text + (int)temp_cursor));
      csmemmove((void *)(text + (int)*(int16_t *)((int)et + 6)),
                (const void *)(text + (int)temp_cursor),
                (unsigned int)(len + 1));
    }
    goto snap_and_return;
  }

  /* --- Left / Right arrow --- */
  if (key_code == 0x4f || key_code == 0x50) {
    if ((key[0] & 1) == 0) {
      /* No shift: if selection active, collapse to appropriate end */
      if (edit_text_get_selection_range(edit_text, &sel_start, &sel_end)) {
        *(int16_t *)((int)et + 8) = -1;
        if (key_code == 0x4f) {
          /* Left: move cursor to selection start */
          *(int16_t *)((int)et + 6) = sel_start;
          unicode_snap_cursor((const char *)et[0], (int16_t *)((int)et + 6));
          return;
        }
        /* Right: move cursor to selection end */
        *(int16_t *)((int)et + 6) = sel_end;
        unicode_snap_cursor((const char *)et[0], (int16_t *)((int)et + 6));
        return;
      }
      if ((key[0] & 1) == 0)
        goto move_cursor;
    }

    /* Shift held (or shift re-check fell through): begin/extend selection */
    if (*(int16_t *)((int)et + 8) == -1) {
      *(int16_t *)((int)et + 8) = *(int16_t *)((int)et + 6);
    }

  move_cursor:
    if (key_code == 0x4f && *(int16_t *)((int)et + 6) > 0) {
      unicode_cursor_backward((const char *)et[0], (int16_t *)((int)et + 6));
    } else if (key_code == 0x50) {
      if ((unsigned int)(int)*(int16_t *)((int)et + 6) <
          (unsigned int)csstrlen((const char *)et[0])) {
        unicode_cursor_forward((const char *)et[0], (int16_t *)((int)et + 6));
      }
    }

    /* If selection collapsed (cursor == selection anchor), clear it */
    if (*(int16_t *)((int)et + 8) == *(int16_t *)((int)et + 6)) {
      *(int16_t *)((int)et + 8) = -1;
      unicode_snap_cursor((const char *)et[0], (int16_t *)((int)et + 6));
      return;
    }
    goto snap_and_return;
  }

  /* --- Character insertion --- */
  if (key[1] == 0 || key[1] == 0xff)
    goto snap_and_return;

  if (edit_text_get_selection_range(edit_text, &sel_start, &sel_end)) {
    /* Replace selection with typed character */
    text = et[0];
    len = csstrlen((const char *)(text + (int)sel_end));
    csmemmove((void *)(text + (int)sel_start + 1),
              (const void *)(text + (int)sel_end), (unsigned int)(len + 1));
    *(int16_t *)((int)et + 6) = sel_start;
    *(int16_t *)((int)et + 8) = -1;
    *(unsigned char *)((int)sel_start + et[0]) = key[1];
    *(int16_t *)((int)et + 6) = *(int16_t *)((int)et + 6) + 1;
    unicode_snap_cursor((const char *)et[0], (int16_t *)((int)et + 6));
    return;
  }

  /* No selection: insert at cursor if room */
  if ((unsigned int)csstrlen((const char *)et[0]) >=
      (unsigned int)(int)*(int16_t *)((int)et + 4))
    goto snap_and_return;

  cursor_pos = (int)*(int16_t *)((int)et + 6) + et[0];
  len = csstrlen((const char *)cursor_pos);
  csmemmove((void *)(cursor_pos + 1), (const void *)cursor_pos,
            (unsigned int)(len + 1));
  *(unsigned char *)((int)*(int16_t *)((int)et + 6) + et[0]) = key[1];
  *(int16_t *)((int)et + 6) = *(int16_t *)((int)et + 6) + 1;
  unicode_snap_cursor((const char *)et[0], (int16_t *)((int)et + 6));
  return;

snap_and_return:
  unicode_snap_cursor((const char *)et[0], (int16_t *)((int)et + 6));
  return;
}
/* --- edit_text.obj batch drafts (2026-07-26) --- */

/* FUN_00096d70 (0x96d70) — XBE naked draft (batch 356). */
#if defined(__clang__)
static void *(*const b96d70_get)(int, int) = object_get_and_verify_type;
static char * (*const b96d70_c8dff0)(char *destination, const char *source) = (void *)csstrcpy;
static int (*const b96d70_c8df60)(const char *s1) = (void *)csstrlen;
static int (*const b96d70_c1d90f0)(char *buffer, const char *format, ...) = (void *)crt_sprintf;
static void *(*const b96d70_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static vector3_t * (*const b96d70_c1412f0)(int object_handle, vector3_t *out_position) = (void *)object_get_world_position;
static void (*const b96d70_c189cb0)(char flag, void *position, void *string, int color) = (void *)FUN_00189cb0;

__attribute__((naked, noinline))
void FUN_00096d70(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x20c, %%esp\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "pushl $0x380\n\t"
      "pushl %%edi\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%esi\n\t"
      "movb 0x5aa8c4, %%al\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00096d70_3\n\t"
      "leal -0x20c(%%ebp), %%eax\n\t"
      "pushl $0x25386f\n\t"
      "pushl %%eax\n\t"
      "call *%[c8dff0]\n\t"
      "flds 0x1b0(%%esi)\n\t"
      "fstpl (%%esp)\n\t"
      "subl $8, %%esp\n\t"
      "flds 0x1ac(%%esi)\n\t"
      "leal -0x20c(%%ebp), %%ecx\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x269b6c\n\t"
      "pushl %%ecx\n\t"
      "call *%[c8df60]\n\t"
      "leal -0x20c(%%ebp,%%eax,1), %%edx\n\t"
      "addl $4, %%esp\n\t"
      "pushl %%edx\n\t"
      "call *%[c1d90f0]\n\t"
      "movw 0x1a8(%%esi), %%ax\n\t"
      "addl $0x18, %%esp\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .LFUN_00096d70_1\n\t"
      "movl 0x5aa8c8, %%ecx\n\t"
      "movswl %%ax, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movzwl 0x1a8(%%esi), %%edx\n\t"
      "flds 0x4(%%eax)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl %%edx\n\t"
      "leal -0x20c(%%ebp), %%eax\n\t"
      "pushl $0x269b50\n\t"
      "pushl %%eax\n\t"
      "call *%[c8df60]\n\t"
      "leal -0x20c(%%ebp,%%eax,1), %%ecx\n\t"
      "addl $4, %%esp\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1d90f0]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00096d70_1:\n\t"
      "flds 0x1bc(%%esi)\n\t"
      "subl $0x10, %%esp\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "leal -0x20c(%%ebp), %%edx\n\t"
      "flds 0x1b8(%%esi)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x269b34\n\t"
      "pushl %%edx\n\t"
      "call *%[c8df60]\n\t"
      "leal -0x20c(%%ebp,%%eax,1), %%eax\n\t"
      "addl $4, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d90f0]\n\t"
      "movw 0x1b4(%%esi), %%ax\n\t"
      "addl $0x18, %%esp\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .LFUN_00096d70_2\n\t"
      "movl 0x5aa8c8, %%edx\n\t"
      "movswl %%ax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[dget]\n\t"
      "leal -0x20c(%%ebp), %%ecx\n\t"
      "flds 0x4(%%eax)\n\t"
      "movzwl 0x1b4(%%esi), %%eax\n\t"
      "fstpl (%%esp)\n\t"
      "pushl %%eax\n\t"
      "pushl $0x269b50\n\t"
      "pushl %%ecx\n\t"
      "call *%[c8df60]\n\t"
      "leal -0x20c(%%ebp,%%eax,1), %%edx\n\t"
      "addl $4, %%esp\n\t"
      "pushl %%edx\n\t"
      "call *%[c1d90f0]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00096d70_2:\n\t"
      "leal -0xc(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "call *%[c1412f0]\n\t"
      "movl 0x31fc44, %%eax\n\t"
      "flds (%%eax)\n\t"
      "movl 0x2ee6c4, %%ecx\n\t"
      "fmuls 0x253524\n\t"
      "pushl %%ecx\n\t"
      "leal -0x20c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "fadds -0xc(%%ebp)\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "flds 0x4(%%eax)\n\t"
      "fmuls 0x253524\n\t"
      "fadds -0x8(%%ebp)\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "flds 0x8(%%eax)\n\t"
      "leal -0xc(%%ebp), %%eax\n\t"
      "fmuls 0x253524\n\t"
      "pushl %%eax\n\t"
      "pushl $0\n\t"
      "fadds -0x4(%%ebp)\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "call *%[c189cb0]\n\t"
      "addl $0x18, %%esp\n\t"
      ".LFUN_00096d70_3:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [get] "m"(b96d70_get), [c8dff0] "m"(b96d70_c8dff0), [c8df60] "m"(b96d70_c8df60), [c1d90f0] "m"(b96d70_c1d90f0), [dget] "m"(b96d70_dget), [c1412f0] "m"(b96d70_c1412f0), [c189cb0] "m"(b96d70_c189cb0)
      : "memory");
}
#else
#error "FUN_00096d70: clang naked draft required"
#endif


/* FUN_00096f20 (0x96f20) — XBE naked draft (batch 337). */
#if defined(__clang__)
static void *(*const b96f20_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void (*const b96f20_c13d6f0)(void *iter, int type_mask, int flags) = object_iterator_new;
static void * (*const b96f20_c13d730)(void *iter) = object_iterator_next;
static void *(*const b96f20_tag)(int, int) = tag_get;
static void (*const b96f20_c967a0)(void *rec, int object) = FUN_000967a0;

__attribute__((naked, noinline))
int FUN_00096f20(int a0 __attribute__((unused)), float a1 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x10, %%esp\n\t"
      "flds 0xc(%%ebp)\n\t"
      "pushl %%ebx\n\t"
      "fcomps 0x2533c0\n\t"
      "pushl %%esi\n\t"
      "xorb %%bl, %%bl\n\t"
      "pushl %%edi\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00096f20_1\n\t"
      "movl $0, 0xc(%%ebp)\n\t"
      "jmp .LFUN_00096f20_2\n\t"
      ".LFUN_00096f20_1:\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00096f20_2\n\t"
      "movl $0x3f800000, 0xc(%%ebp)\n\t"
      ".LFUN_00096f20_2:\n\t"
      "movw 0x8(%%ebp), %%di\n\t"
      "cmpw $-1, %%di\n\t"
      "je .LFUN_00096f20_8\n\t"
      "movl 0x5aa8c8, %%ecx\n\t"
      "movswl %%di, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "flds 0x4(%%ecx)\n\t"
      "fcomps 0xc(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .LFUN_00096f20_8\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x2(%%ecx), %%ax\n\t"
      "testb $1, %%al\n\t"
      "je .LFUN_00096f20_3\n\t"
      "testb $2, %%al\n\t"
      "jne .LFUN_00096f20_8\n\t"
      ".LFUN_00096f20_3:\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "orl $2, %%eax\n\t"
      "pushl $0\n\t"
      "movw %%ax, 0x2(%%ecx)\n\t"
      "leal -0x10(%%ebp), %%eax\n\t"
      "pushl $0x380\n\t"
      "pushl %%eax\n\t"
      "movl %%edx, 0x4(%%ecx)\n\t"
      "movb $1, %%bl\n\t"
      "call *%[c13d6f0]\n\t"
      "leal -0x10(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c13d730]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $0x10, %%esp\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_00096f20_8\n\t"
      ".LFUN_00096f20_4:\n\t"
      "movl (%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x64657669\n\t"
      "call *%[tag]\n\t"
      "addl $8, %%esp\n\t"
      "cmpw %%di, 0x1a8(%%esi)\n\t"
      "movl %%eax, %%ecx\n\t"
      "jne .LFUN_00096f20_7\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00096f20_5\n\t"
      "movl 0x1fc(%%ecx), %%ecx\n\t"
      "jmp .LFUN_00096f20_6\n\t"
      ".LFUN_00096f20_5:\n\t"
      "movl 0x1ec(%%ecx), %%ecx\n\t"
      ".LFUN_00096f20_6:\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "call *%[c967a0]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_00096f20_7:\n\t"
      "leal -0x10(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c13d730]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $4, %%esp\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LFUN_00096f20_4\n\t"
      ".LFUN_00096f20_8:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [dget] "m"(b96f20_dget), [c13d6f0] "m"(b96f20_c13d6f0), [c13d730] "m"(b96f20_c13d730), [tag] "m"(b96f20_tag), [c967a0] "m"(b96f20_c967a0)
      : "memory");
}
#else
#error "FUN_00096f20: clang naked draft required"
#endif


/* 0x97040 */
void FUN_00097040(int a0, float a1)
{
  int eax = 0;

  /* cmp eax, -1 -> je 0x97073 */
  object_get_and_verify_type(0, 896);
  /* cmp (int16_t)eax, 0xffff -> je 0x97073 */
  device_group_set_actual_value(0, 0.0f);

  (void)eax;
}

/* 0x97080 */
void FUN_00097080(int object, void *ctrl_block)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int edi = 0;

  object_get_and_verify_type(0, 896);
  tag_get('ived', 0);
  /* cmp (int16_t)eax, 0xffff -> jne 0x970d3 */
  device_effect_new();
  /* cmp (int16_t)eax, 0xffff -> jne 0x97112 */
  device_effect_new();
  datum_get((void *)(uintptr_t)edx, 0);
  datum_get((void *)(uintptr_t)edx, 0);
  datum_get((void *)(uintptr_t)edx, 0);
  datum_get((void *)(uintptr_t)ecx, 0);
  /* test (char)eax, 8 -> je 0x9718f */
  /* relift: test byte ptr [edi + 4], 0x10 -> je 0x9719c */

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)edi;
}

/* FUN_00097220 (0x97220) — XBE naked draft (batch 354). */
#if defined(__clang__)
static void *(*const b97220_get)(int, int) = object_get_and_verify_type;
static int (*const b97220_c96f20)(int a0, float a1) = (void *)FUN_00096f20;

__attribute__((naked, noinline))
int FUN_00097220(int a0 __attribute__((unused)), float a1 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_00097220_1\n\t"
      "pushl $0x380\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movswl 0x1b4(%%eax), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .LFUN_00097220_1\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "call *%[c96f20]\n\t"
      "addl $8, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00097220_1:\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [get] "m"(b97220_get), [c96f20] "m"(b97220_c96f20)
      : "memory");
}
#else
#error "FUN_00097220: clang naked draft required"
#endif


/* FUN_00097260 (0x97260) — XBE naked draft (batch 349). */
#if defined(__clang__)
static void *(*const b97260_get)(int, int) = object_get_and_verify_type;
static int (*const b97260_c96f20)(int a0, float a1) = FUN_00096f20;

__attribute__((naked, noinline))
void FUN_00097260(int a0 __attribute__((unused)), float a1 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_00097260_1\n\t"
      "pushl $0x380\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl 0x1a4(%%eax), %%edx\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "orl $4, %%edx\n\t"
      "movl %%edx, 0x1a4(%%eax)\n\t"
      "movl %%ecx, 0x1ac(%%eax)\n\t"
      "movswl 0x1a8(%%eax), %%eax\n\t"
      "movl %%ecx, %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c96f20]\n\t"
      "addl $0x10, %%esp\n\t"
      ".LFUN_00097260_1:\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [get] "m"(b97260_get), [c96f20] "m"(b97260_c96f20)
      : "memory");
}
#else
#error "FUN_00097260: clang naked draft required"
#endif

