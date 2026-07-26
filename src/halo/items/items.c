/*
 * text_search_and_replace_function_table[1]  (0x000f52f0, __cdecl)
 *
 * Resolver that renders a single-digit wide replacement string from a widget
 * field.  Reads a signed 16-bit selector at (widget + 8), then writes the
 * digit + NUL terminator into a static wchar_t[2] result buffer at 0x0046cee8
 * and returns a pointer to it (EAX = 0x0046cee8 in every arm of the original).
 *
 *   selector -1 / 0 -> L"1"
 *   selector  1     -> L"2"
 *   selector  2     -> L"3"
 *   selector  3     -> L"4"
 *   otherwise       -> L"?"
 *
 * The original biases the selector by +1 and dispatches through a 5-entry jump
 * table (indices 0..4 for selector -1..3); the switch below reproduces that
 * dense mapping.  The 0x0046cee8 result buffer lies inside the delinker's
 * over-sized game_data build-version array, but is a distinct static owned by
 * this TU, so it is declared as its own symbol (word_46CEE8).
 *
 * ABI: sole cdecl stack arg 'widget' (no register args); leaf, no callees.
 */
wchar_t *FUN_000f52f0(void *widget)
{
  switch (*(short *)((char *)widget + 8)) {
  case -1:
  case 0:
    word_46CEE8[0] = L'1';
    word_46CEE8[1] = L'\0';
    return word_46CEE8;
  case 1:
    word_46CEE8[0] = L'2';
    word_46CEE8[1] = L'\0';
    return word_46CEE8;
  case 2:
    word_46CEE8[0] = L'3';
    word_46CEE8[1] = L'\0';
    return word_46CEE8;
  case 3:
    word_46CEE8[0] = L'4';
    word_46CEE8[1] = L'\0';
    return word_46CEE8;
  default:
    word_46CEE8[0] = L'?';
    word_46CEE8[1] = L'\0';
    return word_46CEE8;
  }
}

/* Virtual on-screen keyboard initialization (items.obj).
 * TU: c:\halo\SOURCE\interface\virtual_keyboard.c (__FILE__ assert @0x28a854).
 *
 * virtual_keyboard_globals lives at 0x46cef0:
 *   +0x00  byte[4]           four separate byte flags (zeroed individually)
 *   +0x04  void *keyboard    'vcky' tag_get result (asserted non-NULL, l.363)
 *   +0x08  int16[3] = 0      state words (0x46cef8/cefa/cefc)
 *   +0x0e  int16 = -1        sentinel (0x46cefe)
 *   +0x10  int16 = -1        sentinel (0x46cf00)
 *   +0x12  int16 = 0         (0x46cf02)
 *   +0x18  int[3] = 0        dwords 0x46cf08/cf0c/cf10
 *   +0x24  int caret_bitmap  'bitm' tag index (0x46cf14; -1 = load failed)
 *
 * Looks up the 'vcky' virtual keyboard tag for "ui\english"; on success
 * caches the tag definition pointer and resets the keyboard state fields,
 * else logs a priority-2 error.  Independently resolves the caret bitmap
 * 'bitm' tag "ui\shell\bitmaps\white" (also error-logged on failure).
 *
 * Returns whether the keyboard definition pointer is non-NULL (SETNE AL
 * from a reload of 0x46cef4; the sole caller at 0xe8809 does TEST AL,AL
 * and logs an error when it is false).
 */
bool virtual_keyboard_initialize(void)
{
  int keyboard_tag;

  *(unsigned char *)0x46cef0 = 0;
  *(unsigned char *)0x46cef1 = 0;
  *(unsigned char *)0x46cef2 = 0;
  *(unsigned char *)0x46cef3 = 0;

  keyboard_tag = tag_loaded(0x76636b79, "ui\\english"); /* 'vcky' */
  if (keyboard_tag != -1) {
    *(void **)0x46cef4 = tag_get(0x76636b79, keyboard_tag); /* 'vcky' */
    if (*(void **)0x46cef4 == (void *)0) {
      display_assert("virtual_keyboard_globals.keyboard",
                     "c:\\halo\\SOURCE\\interface\\virtual_keyboard.c", 363,
                     true);
      system_exit(-1);
    }
    *(short *)0x46cef8 = 0;
    *(short *)0x46cefa = 0;
    *(short *)0x46cefc = 0;
    *(short *)0x46cefe = -1;
    *(short *)0x46cf00 = -1;
    *(short *)0x46cf02 = 0;
    *(int *)0x46cf08 = 0;
    *(int *)0x46cf0c = 0;
    *(int *)0x46cf10 = 0;
  } else {
    error(2, "failed to load virtual keyboard for '%s' language", "<unknown>");
  }

  *(int *)0x46cf14 =
    tag_loaded(0x6269746d, "ui\\shell\\bitmaps\\white"); /* 'bitm' */
  if (*(int *)0x46cf14 == -1) {
    error(2, "failed to load virtual keyboard caret bitmap '%s'",
          "ui\\shell\\bitmaps\\white");
  }

  return *(void **)0x46cef4 != (void *)0;
}

/* virtual_keyboard.c — on-screen (IME-style) text entry state machine.
 *
 * TU: c:\halo\SOURCE\interface\virtual_keyboard.c  (per __FILE__ assert
 * string). kb.json currently files 0xf5500 under items.obj; the assert __FILE__
 * proves the real translation unit is interface/virtual_keyboard.c.
 *
 * The virtual-keyboard state lives in a packed, mixed-width global block based
 * at 0x46cef0 ("virtual_keyboard_globals"). Field widths are preserved exactly
 * (u8 / u16 / u32 / ptr / wchar[32]); do NOT promote the narrow stores to int.
 * Layout used here (offset from 0x46cef0):
 *   +0x00 u8   active flag
 *   +0x01 u8   (cleared)
 *   +0x02 u8   (cleared)
 *   +0x03 u8   (cleared)
 *   +0x04 u32  readiness gate (read-only here)
 *   +0x06 u8   (cleared)
 *   +0x07 u8   set to 1
 *   +0x08 u16  cursor/selection lo (cleared)
 *   +0x0a u16  cursor/selection hi (cleared)
 *   +0x0c u16  buffer_size, clamped <= 0x40 (unsigned)
 *   +0x0e u16  0xffff sentinel
 *   +0x14 u16  caption_index
 *   +0x16 u8   (cleared)
 *   +0x18 ptr  text_buffer
 *   +0x1c ptr  text_buffer end = base + ustrlen(base) (wchar_t* arithmetic)
 *   +0x20 u32  FUN_001d0581() result
 *   +0x28 wchar[32]  ustrncpy of caller text
 *   +0x66 u16  0
 */

/* virtual_keyboard_set_validation — begin a validated virtual-keyboard entry
 * session over the caller's wchar_t buffer. Asserts the inputs (non-null
 * buffer, non-zero even byte size, no session already active) and that
 * caption_index is a valid virtual-keyboard caption string index. If the
 * subsystem is not ready (or a session is somehow active), returns false
 * without changing state. Otherwise flushes pending UI events, initializes the
 * state block, seeds the edit buffer, plays the forward audio cue and returns
 * true.
 *
 * cdecl, bool return in AL (MOV AL,1 success / XOR AL,AL failure). */
bool virtual_keyboard_set_validation(wchar_t *text_buffer,
                                     unsigned short buffer_size,
                                     short caption_index)
{
  int len;

  assert_halt_msg(text_buffer && buffer_size && !(buffer_size & 1) &&
                    !*(uint8_t *)0x46cef0,
                  "text_buffer && buffer_size && !(buffer_size&1) && "
                  "!virtual_keyboard_globals.active");
  assert_halt_msg((caption_index > 7) && (caption_index < 0xb),
                  "(caption_index>=FIRST_VIRTUAL_KEYBOARD_CAPTION_STRING_INDEX)"
                  " && (caption_index<NUMBER_OF_VIRTUAL_KEYBOARD_STRINGS)");

  if (*(uint8_t *)0x46cef0 != 0 || *(uint32_t *)0x46cef4 == 0)
    return false;

  event_manager_flush();

  *(uint16_t *)0x46cef8 = 0;
  *(uint16_t *)0x46cefa = 0;
  *(uint8_t *)0x46cef0 = 1;
  *(wchar_t **)0x46cf08 = text_buffer;
  len = ustrlen(text_buffer);
  *(wchar_t **)0x46cf0c = text_buffer + len;
  *(uint16_t *)0x46cefc = buffer_size;
  if (buffer_size >= 0x40)
    *(uint16_t *)0x46cefc = 0x40;
  *(uint16_t *)0x46cefe = 0xffff;
  *(uint32_t *)0x46cf10 = (uint32_t)FUN_001d0581();
  *(uint16_t *)0x46cf04 = (uint16_t)caption_index;
  *(uint8_t *)0x46cef1 = 0;
  *(uint8_t *)0x46cef2 = 0;
  *(uint8_t *)0x46cef3 = 0;
  *(uint8_t *)0x46cef7 = 1;
  ustrncpy((wchar_t *)0x46cf18, text_buffer, 0x20);
  *(uint16_t *)0x46cf56 = 0;
  *(uint8_t *)0x46cef6 = 0;
  ui_play_audio_feedback_sound(2);
  return true;
}

/* Virtual keyboard cursor move handler: advance the keymap row cursor
 * upward (0xf5700, virtual_keyboard.obj TU).
 *
 * Decrements the row cursor at 0x46cef8 through 5 keymap rows (wrapping
 * -1 -> 4), skipping rows whose key character (keymap byte at
 * 0x28a790[col + row*0xb]) equals the character under the pre-move cursor,
 * so duplicate/merged keys are stepped over in one press. Stores the new
 * row, plays the UI cursor-move sound (selector 1), and returns 1 (move
 * accepted -> caller latches last_move_dir/last_move_time). Sibling of
 * FUN_000f5660/56b0/5750/5fb0.
 *
 * Disasm notes: row is held in AX for the whole loop (16-bit dec, signed
 * jns wrap to 4) and stored to the global once after the loop; the
 * pre-move key byte is cached in DL before the loop; col (0x46cefa) is
 * MOVSX-loaded once into ECX. MOV AL,1 before RET -> char return; PUSH 1
 * is the audio-selector argument. */
char FUN_000f5700(void)
{
  short row;
  short col;
  char original_key;

  row = *(short *)0x46cef8;
  col = *(short *)0x46cefa;
  original_key = ((char *)0x28a790)[(int)col + row * 0xb];
  do {
    row = (short)(row - 1);
    if (row < 0) {
      row = 4;
    }
  } while (((char *)0x28a790)[(int)col + row * 0xb] == original_key);
  *(short *)0x46cef8 = row;
  ui_play_audio_feedback_sound(1);
  return 1;
}

/* Virtual keyboard cursor move handler: advance the keymap row cursor
 * downward (0xf5750, virtual_keyboard.obj TU).
 *
 * Increments the row cursor at 0x46cef8 modulo 5 (5 keymap rows), skipping
 * rows whose key character (keymap byte at 0x28a790[col + row*0xb]) equals
 * the character under the pre-move cursor, so duplicate/merged keys are
 * stepped over in one press. Stores the new row, plays the UI cursor-move
 * sound (selector 1), and returns 1 (move accepted -> caller latches
 * last_move_dir/last_move_time). Sibling of FUN_000f5660/56b0/5700.
 *
 * Disasm notes: row is held in AX for the whole loop (16-bit inc/cmp/xor)
 * and stored to the global once after the loop; the pre-move key byte is
 * cached in DL before the loop; col (0x46cefa) is MOVSX-loaded once. */
char FUN_000f5750(void)
{
  short row;
  short col;
  char original_key;

  row = *(short *)0x46cef8;
  col = *(short *)0x46cefa;
  original_key = ((char *)0x28a790)[(int)col + row * 0xb];
  do {
    row = (short)(row + 1);
    if (row == 5) {
      row = 0;
    }
  } while (((char *)0x28a790)[(int)col + row * 0xb] == original_key);
  *(short *)0x46cef8 = row;
  ui_play_audio_feedback_sound(1);
  return 1;
}

/* Virtual keyboard edit-buffer commit/flush handler (0xf57a0).
 * Commits the working edit buffer into the caller's target pointer: if a
 * target ptr (0x46cf08) is set, copy the working buffer (0x46cf18) into it
 * as UTF-16 for (capacity>>1) wchars via ustrncpy, then NUL-terminate the
 * final wchar cell at index (capacity>>1)-1. Afterwards clear the edit
 * state (active flag 0x46cef0, target ptr 0x46cf08, working buffer word
 * 0x46cf18, flag byte 0x46cf06) and play the UI "accept" feedback sound
 * (selector 3). Returns 1 (accepted -> caller latches move state).
 * Globals: 0x46cf08 = target/dest ptr, 0x46cf18 = working buffer base,
 * 0x46cefc = capacity in bytes (unsigned 16-bit; loaded via MOVZX), used
 * both as cap>>1 for the copy count and (cap>>1)-1 for the terminator.
 * Sibling move handler of FUN_000f5660/56b0/5700/5750/5fb0.
 * Disasm: MOV AL,1 before RET -> returns char 1; PUSH 3 to the audio call. */
char FUN_000f57a0(void)
{
  wchar_t *dest;

  *(char *)0x46cef0 = 0;
  dest = *(wchar_t **)0x46cf08;
  if (dest != (wchar_t *)0x0) {
    ustrncpy(dest, (wchar_t *)0x46cf18,
             (unsigned int)*(unsigned short *)0x46cefc >> 1);
    ((unsigned short *)
       dest)[((unsigned int)*(unsigned short *)0x46cefc >> 1) - 1] = 0;
  }
  *(wchar_t **)0x46cf08 = (wchar_t *)0x0;
  *(short *)0x46cf18 = 0;
  *(char *)0x46cf06 = 0;
  ui_play_audio_feedback_sound(3);
  return 1;
}

/* Virtual keyboard backspace / delete-char handler (0xf5f30).
 * Deletes the wide-char (UTF-16) immediately before the cursor from the
 * edit buffer. If the cursor (0x46cf0c) is past the buffer base (0x46cf08),
 * shift the tail back by one 2-byte cell via csmemmove, NUL-terminate the
 * final wchar cell, then back the cursor up by one wchar. The cursor
 * feedback sound (selector 1) always plays, whether or not a char was
 * removed.
 * Globals: 0x46cf08 = buffer base ptr, 0x46cf0c = cursor/end ptr,
 * 0x46cefc = buffer capacity in bytes (unsigned 16-bit; loaded via MOVZX).
 * The terminator index uses (capacity >> 1) - 1 to match the original's
 * SHR + scaled-index store [base + (cap>>1)*2 - 2]. */
void FUN_000f5f30(void)
{
  char *cursor;
  int remaining;

  cursor = *(char **)0x46cf0c;
  if (*(char **)0x46cf08 < cursor) {
    remaining = ((int)*(unsigned short *)0x46cefc - (int)cursor) +
                (int)*(char **)0x46cf08;
    if (remaining >= 0) {
      csmemmove(cursor - 2, cursor, (unsigned int)remaining);
      ((unsigned short *)*(
        char **)0x46cf08)[((unsigned int)*(unsigned short *)0x46cefc >> 1) -
                          1] = 0;
      *(char **)0x46cf0c -= 2;
    }
  }
  ui_play_audio_feedback_sound(1);
}

/* Virtual on-screen keyboard input pump (virtual_keyboard.obj).
 * TU: c:\halo\SOURCE\interface\virtual_keyboard.c (__FILE__ assert
 * @0x28a790..).
 *
 * FUN_000f63f0 (0xf63f0): drains the per-frame input event queue for the
 * on-screen keyboard and turns controller events into a single move/action
 * code, then dispatches the matching per-direction handler.
 *
 * virtual_keyboard_globals cluster (see items.c virtual_keyboard_initialize):
 *   0x46cef8  short  cursor row       (keymap row)
 *   0x46cefa  short  cursor col       (keymap col)
 *   0x46cefc  short  buffer_size      (edit buffer capacity, bytes)
 *   0x46cefe  short  last_move_dir    (latched direction for auto-repeat)
 *   0x46cf00  short  current_char     (keymap-resolved character)
 *   0x46cf07  byte   buffer_dirty     (0 = pristine, 1 = user has typed)
 *   0x46cf08  char*  buffer_base      (edit buffer start)
 *   0x46cf0c  char*  cursor           (edit caret within the buffer)
 *   0x46cf10  int    last_move_time   (ms timestamp of last accepted move)
 *   0x46cf58  int    repeat_timer     (ms timestamp gating auto-repeat)
 * Keymap dispatch table at 0x28a790 is a signed byte array indexed
 * [row * 0xb + col] (11 columns) yielding the character stored at 0x46cf00.
 *
 * Move handlers FUN_000f5660/56b0/5700/5750/5fb0/57a0 return a char in AL
 * (0/1); the return latches last_move_dir + last_move_time when it is 1.
 */

/* Controller input event record; event_manager_get_next_event writes 8 bytes
 * (two dwords) here: a 16-bit event type at +0 and a 32-bit payload at +4.
 * The payload is reinterpreted per event type (analog word pair / button
 * id + pressed-flag bytes). */
struct virtual_keyboard_event {
  short type; /* +0 : 1 = analog stick, 3 = button */
  short reserved; /* +2 */
  int data; /* +4 : analog X (low word) / Y (high word), or
                    button id (low byte) + pressed flag (byte +1) */
};

void virtual_keyboard_process_input(void)
{
  struct virtual_keyboard_event event;
  int now_ms;
  int action; /* selected move/action code, -1 = none */
  int timer_tmp; /* value stored back into repeat_timer via the shared tail */
  char moved; /* nonzero once a handler accepted the move */
  char pressed; /* button pressed-flag byte */

  now_ms = system_milliseconds();
  action = -1;
  moved = 0;

  if (!event_manager_get_next_event(&event, -1))
    return;

  do {
    if (event.type == 1) {
      /* analog stick: cardinal only at full deflection */
      if ((short)(event.data >> 16) == 0x7fff) {
        action = 2;
      } else if ((short)(event.data >> 16) == -0x8000) {
        action = 3;
      } else if ((short)event.data == -0x8000) {
        action = 0;
      } else {
        timer_tmp = *(int *)0x46cf58;
        if ((short)event.data == 0x7fff)
          goto set_dir_right;
      }
    } else if (event.type == 3) {
      /* button: high byte = pressed flag, low byte = button id */
      pressed = (char)(event.data >> 8);
      switch (event.data & 0xff) {
      case 0: /* A: select current character */
        if (pressed == 1)
          action = 4;
        break;
      case 1: /* B / start: back */
      case 0xd:
        if (pressed == 1)
          action = 5;
        break;
      case 2: /* X: accept / clear */
        if (pressed == 1) {
          if (*(unsigned char *)0x46cf07 == 1) {
            if (*(short *)0x46cefc == 0)
              display_assert("virtual_keyboard_globals.buffer_size>0",
                             "c:\\halo\\SOURCE\\interface\\virtual_keyboard.c",
                             0x27a, true);
            csmemset(*(char **)0x46cf08, 0, (unsigned int)*(short *)0x46cefc);
            *(char **)0x46cf0c = *(char **)0x46cf08;
            *(unsigned char *)0x46cf07 = 0;
            ui_play_audio_feedback_sound(1);
            moved = 1;
          } else {
            FUN_000f5f30();
            moved = 1;
          }
        }
        break;
      case 6: /* cursor left */
        if (pressed == 1) {
          if (*(char **)0x46cf08 < *(char **)0x46cf0c)
            *(char **)0x46cf0c -= 1;
        cursor_moved:
          *(unsigned char *)0x46cf07 = 0;
          ui_play_audio_feedback_sound(1);
          moved = 1;
        }
        break;
      case 7: /* cursor right */
        if (pressed == 1) {
          if (**(char **)0x46cf0c != 0)
            *(char **)0x46cf0c += 1;
          goto cursor_moved;
        }
        break;
      case 8: /* dpad up (auto-repeat gated) */
        if (*(short *)0x46cefe != 2 ||
            0xf9 < (unsigned int)(now_ms - *(int *)0x46cf58) || pressed == 1) {
          action = 2;
          *(int *)0x46cf58 = now_ms;
        }
        break;
      case 9: /* dpad down */
        if (*(short *)0x46cefe != 3 ||
            0xf9 < (unsigned int)(now_ms - *(int *)0x46cf58) || pressed == 1) {
          action = 3;
          *(int *)0x46cf58 = now_ms;
        }
        break;
      case 10: /* dpad left */
        if (*(short *)0x46cefe != 0 ||
            0xf9 < (unsigned int)(now_ms - *(int *)0x46cf58) || pressed == 1) {
          action = 0;
          *(int *)0x46cf58 = now_ms;
        }
        break;
      case 0xb: /* dpad right */
        timer_tmp = now_ms;
        if (*(short *)0x46cefe != 1 ||
            0xf9 < (unsigned int)(now_ms - *(int *)0x46cf58) || pressed == 1) {
        set_dir_right:
          *(int *)0x46cf58 = timer_tmp;
          action = 1;
        }
        break;
      case 0xc: /* home / reset to origin */
        if (pressed == 1) {
          *(short *)0x46cef8 = 0;
          *(short *)0x46cefa = 0;
          action = 4;
        }
        break;
      }
    }
  } while (event_manager_get_next_event(&event, -1));

  if (action != -1) {
    *(short *)0x46cf00 = (short)(char)((
      char *)0x28a790)[(int)*(short *)0x46cefa + *(short *)0x46cef8 * 0xb];
    switch (action) {
    case 0:
      moved = FUN_000f5660();
      break;
    case 1:
      moved = FUN_000f56b0();
      break;
    case 2:
      moved = FUN_000f5700();
      break;
    case 3:
      moved = FUN_000f5750();
      break;
    case 4:
      moved = FUN_000f5fb0();
      break;
    case 5:
      moved = FUN_000f57a0();
      break;
    }
    if (moved == 1) {
      *(short *)0x46cefe = (short)action;
      *(int *)0x46cf10 = now_ms;
    }
  }
}

/* items_dispose_from_old_map (0xf6740)
 * Guarded per-frame virtual-keyboard input pump. If the
 * virtual_keyboard_globals block at 0x46cef0 is active (byte flag at offset 0
 * != 0), drain its input queue via virtual_keyboard_process_input; otherwise
 * no-op. The kb name is a placeholder and does not describe the observed binary
 * behavior. */
void items_dispose_from_old_map(void)
{
  if (*(uint8_t *)0x46cef0 != 0) {
    virtual_keyboard_process_input();
  }
}

/*
 * FUN_000f6750 (0xf6750, __cdecl): apply an item definition's flag bits to a
 * live object instance.
 *
 * Resolves the object instance from its datum handle via
 * object_get_and_verify_type(object_datum, 8) [type_mask 8], then propagates
 * two flag bits from the definition struct (byte flags at definition+0x22)
 * into the object:
 *
 *   def+0x22 bit0 (0x1): drives the object flags word at obj+0x4 bit5 (0x20) --
 *       set -> OR 0x20, clear -> AND ~0x20.  In BOTH arms obj+0x4 is then also
 *       OR'd with 0x60000.  When the bit is CLEAR the object's float at
 *       obj+0x14 is additionally biased by +0.05f (*(float *)0x2533e8).
 *   def+0x22 bit2 (0x4): drives the secondary flags word at obj+0x1a4 bit5 with
 *       INVERTED sense -- clear -> OR 0x20, set -> AND ~0x20.
 *
 * The two consecutive stores to obj+0x4 (bare value, then value|0x60000) are
 * emitted verbatim by the original and are kept split for byte fidelity.
 *
 * ABI: two cdecl stack args (no register args). Sole callee
 * object_get_and_verify_type is cdecl. void return.
 */
void FUN_000f6750(int object_datum, void *definition)
{
  void *obj;
  unsigned int flags;

  obj = object_get_and_verify_type(object_datum, 8);
  if ((*(unsigned char *)((char *)definition + 0x22) & 1) == 0) {
    flags = *(unsigned int *)((char *)obj + 4) & 0xffffffdf;
  } else {
    flags = *(unsigned int *)((char *)obj + 4) | 0x20;
  }
  *(unsigned int *)((char *)obj + 4) = flags;
  *(unsigned int *)((char *)obj + 4) = flags | 0x60000;
  if ((*(unsigned char *)((char *)definition + 0x22) & 4) == 0) {
    *(unsigned int *)((char *)obj + 0x1a4) =
      *(unsigned int *)((char *)obj + 0x1a4) | 0x20;
  } else {
    *(unsigned int *)((char *)obj + 0x1a4) =
      *(unsigned int *)((char *)obj + 0x1a4) & 0xffffffdf;
  }
  if ((*(unsigned char *)((char *)definition + 0x22) & 1) == 0) {
    *(float *)((char *)obj + 0x14) =
      *(float *)((char *)obj + 0x14) + *(float *)0x2533e8;
  }
}

#include "x87_math.h"

/* Activate the pickup sound effect for an equipment item.
 * Looks up the equipment tag definition ('eqip') and plays the
 * pickup sound (tag field at +0x31c) at full volume (scale=1.0). */
void item_activate_equipment_effect(int equipment_handle)
{
  int *equip_obj;
  char *tag_def;
  int sound_tag;

  equip_obj = (int *)object_get_and_verify_type(equipment_handle, 8);
  tag_def = (char *)tag_get(0x65716970, *equip_obj);
  sound_tag = *(int *)(tag_def + 0x31c);
  if (sound_tag != NONE) {
    sound_impulse_start(sound_tag, 1.0f);
  }
}

/* Play the pickup sound for an equipment tag (0xf67f0).
 * Reads the pickup sound tag index at equipment_tag+0x31c and plays it. */
void FUN_000f67f0(int equipment_tag_index)
{
  int tag_data = (int)tag_get(0x65716970, equipment_tag_index);
  if (*(int *)(tag_data + 0x31c) != -1) {
    sound_impulse_start(*(int *)(tag_data + 0x31c), 1.0f);
  }
}

/* Item garbage-collection countdown tick (0xf6820).
 * Fetches the item object (type mask 0x10), decrements the signed 16-bit
 * despawn timer at item_obj+0x1dc (seeded to a random [300,600] value by
 * item_begin_garbage_collection), and deletes the object once the timer
 * reaches 0. Returns whether the item survived this tick (timer still > 0);
 * the original latches this into BL via SETG and returns it in AL.
 * Despite the kb name "item_new", the binary behavior is a per-tick
 * release/countdown, not allocation. */
char item_new(int object_handle)
{
  char *item_obj;
  char survived;

  item_obj = (char *)object_get_and_verify_type(object_handle, 0x10);
  *(int16_t *)(item_obj + 0x1dc) = *(int16_t *)(item_obj + 0x1dc) - 1;
  survived = *(int16_t *)(item_obj + 0x1dc) > 0;
  if (!survived) {
    object_delete(object_handle);
  }
  return survived;
}

/* Mark an item (type mask 0x10 = garbage item type) for garbage collection.
 * Sets the garbage flag, ORs object flags bits 18 and 19 (0xc0000), and
 * picks a random despawn timer in [300, 600] ticks stored at item_obj+0x1dc.
 * Returns true on success. */
bool item_begin_garbage_collection(int item_handle)
{
  char *item_obj;
  unsigned int *seed;
  unsigned int flags;

  item_obj = (char *)object_get_and_verify_type(item_handle, 0x10);
  object_set_garbage_flag(item_handle, 1);
  flags = *(unsigned int *)(item_obj + 0x4);
  *(unsigned int *)(item_obj + 0x4) = flags | 0xc0000;
  seed = (unsigned int *)get_global_random_seed_address();
  *(int16_t *)(item_obj + 0x1dc) = random_range(seed, 300, 600);
  return 1;
}

/* Read the type byte (offset +3) from an item datum entry (0xf68b0).
 * Returns as short (zero-extended from byte). */
short FUN_000f68b0(int item_handle)
{
  char *datum;
  datum = (char *)datum_get(*(data_t **)0x5a8d50, item_handle);
  return (unsigned char)datum[3];
}

/* Activate an item: set flags 0x6000, record game time, reset timer (0xf6910).
 */
char item_activate(int item_handle)
{
  char *item_obj;
  item_obj = (char *)object_get_and_verify_type(item_handle, 0x1c);
  *(unsigned int *)(item_obj + 4) = *(unsigned int *)(item_obj + 4) | 0x6000;
  *(int *)(item_obj + 0x1b4) = game_time_get();
  *(int *)(item_obj + 0x1b0) = NONE;
  return 1;
}

/* Iterate all item objects (type 0x1c) and return true if any have
 * a positive danger count, indicating a dangerous item is near a player. */
bool dangerous_items_near_player(void)
{
  char iter[16];
  void *item;

  object_iterator_new(iter, 0x1c, 1);
  for (item = object_iterator_next(iter); item != NULL;
       item = object_iterator_next(iter)) {
    if (*(int16_t *)((char *)item + 0x1a8) > 0)
      return true;
  }
  return false;
}

/* Attach or detach an item from a unit.
 * When unit_handle is valid: sets item flags bit 0 (attached), conditionally
 * sets bit 1 (player-controlled) based on unit's player handle at +0x1c8,
 * copies the player handle to item+0x70, removes item from garbage list,
 * clears bits 3 and 5 of item flags, and resets the item's scenario location
 * at +0x48.
 * When unit_handle is NONE: clears bits 0 and 1, detaching the item. */
void item_attach_to_unit(int item_handle, int unit_handle)
{
  char *item_obj;
  char *unit_obj;
  uint32_t flags;

  item_obj = (char *)object_get_and_verify_type(item_handle, 0x1c);
  if (unit_handle != NONE) {
    unit_obj = (char *)object_get_and_verify_type(unit_handle, 3);
    flags = *(uint32_t *)(item_obj + 0x1a4);
    flags |= 1;
    *(uint32_t *)(item_obj + 0x1a4) = flags;
    if (*(int *)(unit_obj + 0x1c8) == NONE) {
      flags = (flags & ~2u) | 1;
    } else {
      flags |= 3;
    }
    *(uint32_t *)(item_obj + 0x1a4) = flags;
    *(int *)(item_obj + 0x70) = *(int *)(unit_obj + 0x1c8);
    object_set_garbage_flag(item_handle, 0);
    *(uint32_t *)(item_obj + 0x1a4) = *(uint32_t *)(item_obj + 0x1a4) & ~0x28u;
    *(int *)(item_obj + 0x48) = NONE;
    *(int16_t *)(item_obj + 0x4c) = (int16_t)NONE;
    scenario_location_reset((int *)(item_obj + 0x48));
  } else {
    *(uint32_t *)(item_obj + 0x1a4) = *(uint32_t *)(item_obj + 0x1a4) & ~3u;
  }
}

/* Initialize the danger countdown for an item (0xf6af0).
 * If the item's danger count at +0x1a8 is zero, spawns an effect using
 * the tag reference at +0x2f4 of the 'item' tag definition (detonation
 * or fuse warning), then sets the countdown to a random value in the
 * range [tag+0x2e0, tag+0x2e4] scaled by 30.0 (ticks per second).
 * Called from item_set_position when the item is flagged for detonation
 * and the game engine is not running (campaign/solo mode). */
void item_detonate(int item_handle)
{
  char *item_obj;
  char *item_tag;
  int *seed;
  float rnd;

  item_obj = (char *)object_get_and_verify_type(item_handle, 0x1c);
  item_tag = (char *)tag_get(0x6974656d, *(int *)item_obj);

  if (*(int16_t *)(item_obj + 0x1a8) == 0) {
    FUN_0009ec30(
      *(int *)(item_tag + 0x2f4), item_handle,
      item_handle, /* dup-args-ok: same handle as source and target */
      NONE, 0, 0, 0, 0);
    seed = get_global_random_seed_address();
    rnd = random_real_range(seed, *(float *)(item_tag + 0x2e0),
                            *(float *)(item_tag + 0x2e4));
    *(int16_t *)(item_obj + 0x1a8) = (int16_t)(int)(rnd * 30.0f);
  }
}

/* Update an item's angular velocity state (0xf6b80).
 * Computes the magnitude of the angular velocity vector at +0x3c..+0x44.
 * If nonzero: sets flag bit 2 (has angular velocity) at +0x1a4, normalizes
 * the angular velocity into the direction vector at +0x1c8..+0x1d0 (unless
 * object flag bit 5 at +0x4 is set, indicating externally driven rotation),
 * then stores sin(magnitude) at +0x1d4 and cos(magnitude) at +0x1d8.
 * If zero: clears flag bit 2 and sets sin=0, cos=1 (identity rotation). */
void FUN_000f6b80(int item_handle)
{
  char *item_obj;
  float x, y, z;
  float mag;
  float inv_mag;

  item_obj = (char *)object_get_and_verify_type(item_handle, 0x1c);
  x = *(float *)(item_obj + 0x3c);
  y = *(float *)(item_obj + 0x40);
  z = *(float *)(item_obj + 0x44);
  mag = sqrtf(x * x + y * y + z * z);

  if (mag != 0.0f) {
    *(uint32_t *)(item_obj + 0x1a4) = *(uint32_t *)(item_obj + 0x1a4) | 4;

    if (!(*(uint8_t *)(item_obj + 0x4) & 0x20)) {
      inv_mag = 1.0f / mag;
      *(float *)(item_obj + 0x1c8) = inv_mag * x;
      *(float *)(item_obj + 0x1cc) = inv_mag * y;
      *(float *)(item_obj + 0x1d0) = inv_mag * z;
    }

    *(float *)(item_obj + 0x1d4) = x87_fsin(mag);
    *(float *)(item_obj + 0x1d8) = x87_fcos(mag);
  } else {
    *(uint32_t *)(item_obj + 0x1a4) = *(uint32_t *)(item_obj + 0x1a4) & ~4u;
    *(float *)(item_obj + 0x1d4) = 0.0f;
    *(float *)(item_obj + 0x1d8) = 1.0f;
  }
}

/* valid_real_vector3d_axes3 (0xf6c40)
 *
 * Validate that three vectors (a, b, c) form a valid orthonormal axis triple:
 * each must be a unit normal (valid_real_normal3d), and each adjacent pair
 * must be mutually perpendicular (dot ~= 0). FUN_00021f70 is the two-float
 * approximate-equality test (dot, 0.0). FUN_00013070(c, a) returns the
 * scalar (dot) that must also be ~0. Returns 1 if all checks pass, else 0.
 *
 * FP term order preserved from disassembly (MSVC scheduling emits the sum
 * components in 0,2,1 order); the sum is commutative so this is harmless
 * mathematically but kept for byte-fidelity. */
char valid_real_vector3d_axes3(float *a, float *b, float *c)
{
  float scalar;

  if (valid_real_normal3d(a)) {
    if (valid_real_normal3d(b)) {
      if (valid_real_normal3d(c)) {
        if ((char)FUN_00021f70(a[0] * b[0] + a[2] * b[2] + a[1] * b[1], 0.0f) !=
            '\0') {
          if ((char)FUN_00021f70(b[0] * c[0] + c[2] * b[2] + c[1] * b[1],
                                 0.0f) != '\0') {
            scalar = FUN_00013070(c, a);
            if ((char)FUN_00021f70(scalar, 0.0f) != '\0') {
              return '\x01';
            }
          }
        }
      }
    }
  }
  return '\0';
}

/* valid_real_matrix4x3 (0xf6d00)
 *
 * Validate a 4x3 affine matrix: 1 scale scalar @ +0x00, three orthonormal
 * axis vectors @ +0x04/+0x10/+0x1C, and a translation point @ +0x28.
 * The scale scalar is finite (not inf/NaN) when its IEEE-754 exponent bits
 * (mask 0x7f800000) are NOT all set. Then the axis triple and the point are
 * validated by their respective helpers. Returns 1 only when every check
 * passes; 0 on any failure or non-finite scale.
 *
 * Ghidra mistyped this void(void); it is a bool-returning cdecl fn taking one
 * float* matrix pointer (proven by the render_cameras.c thunk typedef). Nested
 * -if shape preserved: single success return, fall-through failure. */
char valid_real_matrix4x3(float *mat)
{
  if ((*(uint32_t *)mat & 0x7f800000) != 0x7f800000) {
    if (valid_real_vector3d_axes3(mat + 1, mat + 4, mat + 7) != '\0') {
      if (valid_real_point3d(mat + 10)) {
        return '\x01';
      }
    }
  }
  return '\0';
}

/* item_set_position (0xf6d60) — XBE naked draft (batch 49). */
#if defined(__clang__)
static void *(*const bf6d60_get)(int, int) = object_get_and_verify_type;
static void *(*const bf6d60_tag)(int, int) = tag_get;
static void (*const bf6d60_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const bf6d60_exitfn)(int) = system_exit;
static bool (*const bf6d60_gerun)(void) = game_engine_running;
static void (*const bf6d60_cf6af0)(int item_handle) = item_detonate;
static short (*const bf6d60_markers)(int, void *, void *, int) = object_get_markers_by_string_id;
static void *(*const bf6d60_gbsp)(void) = global_collision_bsp_get;
static void *(*const bf6d60_elem)(void *, int, int) = tag_block_get_element;
static void (*const bf6d60_c99640)(int structure_bsp, uint32_t plane_reference, float *out_plane) = bsp3d_get_plane_from_designator;
static float *(*const bf6d60_vsca)(float *, float *, float, float *) = vector3d_scale_add;
static void (*const bf6d60_otrans)(int, float *, void *) = object_translate;
static float (*const bf6d60_c12170)(float *vector) = FUN_00012170;
static float (*const bf6d60_c121e0)(float min, float max) = FUN_000121e0;
static void (*const bf6d60_c213c0)(float *a, float *b, float *out) = vector3d_add;
static int *(*const bf6d60_gseed)(void) = get_global_random_seed_address;
static float (*const bf6d60_rmreal)(unsigned int *) = random_math_real;
static float (*const bf6d60_norm)(float *) = normalize3d;
static void (*const bf6d60_c10b380)(unsigned int *seed, float *out) = random_seed_get_direction3d;
static void (*const bf6d60_f6b80)(int) = FUN_000f6b80;
static void (*const bf6d60_garb)(int, int) = object_set_garbage_flag;

__attribute__((naked, noinline))
void item_set_position(int item_handle __attribute__((unused)), float *position __attribute__((unused)), int flag __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x8c, %%esp\n\t"
      "pushl %%ebx\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl $0x1c\n\t"
      "pushl %%ebx\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl (%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x6974656d\n\t"
      "call *%[tag]\n\t"
      "movb 0x1a4(%%esi), %%cl\n\t"
      "movl %%eax, %%edi\n\t"
      "movl $0x20, %%eax\n\t"
      "addl $0x10, %%esp\n\t"
      "testb %%cl, %%al\n\t"
      "jne .Litem_set_position_14\n\t"
      "cmpw %%ax, 0x4761d8\n\t"
      "jl .Litem_set_position_1\n\t"
      "pushl $1\n\t"
      "pushl $0x218\n\t"
      "pushl $0x28aaa0\n\t"
      "pushl $0x253440\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Litem_set_position_1:\n\t"
      "movw 0x4761d8, %%ax\n\t"
      "movswl %%ax, %%ecx\n\t"
      "incw %%ax\n\t"
      "movw $0xb, 0x5a8c80(,%%ecx,2)\n\t"
      "movw %%ax, 0x4761d8\n\t"
      "cmpl $-1, 0xcc(%%esi)\n\t"
      "jne .Litem_set_position_12\n\t"
      "movb 0x10(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Litem_set_position_2\n\t"
      "call *%[gerun]\n\t"
      "testb %%al, %%al\n\t"
      "jne .Litem_set_position_2\n\t"
      "testb $2, 0x17c(%%edi)\n\t"
      "je .Litem_set_position_2\n\t"
      "pushl %%ebx\n\t"
      "call *%[cf6af0]\n\t"
      "addl $4, %%esp\n\t"
      ".Litem_set_position_2:\n\t"
      "testb $8, 0x1a4(%%esi)\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "je .Litem_set_position_4\n\t"
      "flds 0x8(%%edi)\n\t"
      "flds 0x4(%%edi)\n\t"
      "flds (%%edi)\n\t"
      "fld %%st(0)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fld %%st(2)\n\t"
      "fmul %%st(3), %%st(0)\n\t"
      "faddp %%st(1)\n\t"
      "fld %%st(3)\n\t"
      "fmul %%st(4), %%st(0)\n\t"
      "faddp %%st(1)\n\t"
      "fcomps 0x253f44\n\t"
      "fstp %%st(0)\n\t"
      "fnstsw %%ax\n\t"
      "fstp %%st(0)\n\t"
      "testb $5, %%ah\n\t"
      "fstp %%st(0)\n\t"
      "jnp .Litem_set_position_5\n\t"
      "pushl $1\n\t"
      "leal -0x8c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x28aa90\n\t"
      "pushl %%ebx\n\t"
      "call *%[markers]\n\t"
      "addl $0x10, %%esp\n\t"
      "testw %%ax, %%ax\n\t"
      "je .Litem_set_position_3\n\t"
      "call *%[gbsp]\n\t"
      "movl %%eax, %%ebx\n\t"
      "movswl 0x1aa(%%esi), %%eax\n\t"
      "pushl $0xc\n\t"
      "pushl %%eax\n\t"
      "leal 0x3c(%%ebx), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[elem]\n\t"
      "movl (%%eax), %%eax\n\t"
      "leal -0x10(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "call *%[c99640]\n\t"
      "flds -0x8(%%ebp)\n\t"
      "addl $0x18, %%esp\n\t"
      "fmuls -0x24(%%ebp)\n\t"
      "leal -0x20(%%ebp), %%ecx\n\t"
      "flds -0xc(%%ebp)\n\t"
      "pushl %%ecx\n\t"
      "fmuls -0x28(%%ebp)\n\t"
      "pushl %%ecx\n\t"
      "leal -0x10(%%ebp), %%edx\n\t"
      "leal -0x2c(%%ebp), %%eax\n\t"
      "faddp %%st(1)\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fmuls -0x2c(%%ebp)\n\t"
      "faddp %%st(1)\n\t"
      "fsubs -0x4(%%ebp)\n\t"
      "fsubrs 0x2533e8\n\t"
      "fstps (%%esp)\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[vsca]\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "pushl $0\n\t"
      "leal -0x20(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[otrans]\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "addl $0x1c, %%esp\n\t"
      ".Litem_set_position_3:\n\t"
      "movl 0x4(%%esi), %%ecx\n\t"
      "movl 0x1a4(%%esi), %%eax\n\t"
      "andl $0xffffffdf, %%ecx\n\t"
      "andl $0xfffffff7, %%eax\n\t"
      "movl %%ecx, 0x4(%%esi)\n\t"
      "movl %%eax, 0x1a4(%%esi)\n\t"
      "jmp .Litem_set_position_5\n\t"
      ".Litem_set_position_4:\n\t"
      "andl $0xffffffdf, 0x4(%%esi)\n\t"
      ".Litem_set_position_5:\n\t"
      "flds (%%edi)\n\t"
      "fadds 0x18(%%esi)\n\t"
      "fstps 0x18(%%esi)\n\t"
      "flds 0x1c(%%esi)\n\t"
      "fadds 0x4(%%edi)\n\t"
      "fstps 0x1c(%%esi)\n\t"
      "flds 0x20(%%esi)\n\t"
      "fadds 0x8(%%edi)\n\t"
      "fstps 0x20(%%esi)\n\t"
      "movl 0x1b0(%%esi), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "jne .Litem_set_position_8\n\t"
      "testb $8, 0x1a4(%%esi)\n\t"
      "je .Litem_set_position_8\n\t"
      "pushl %%edi\n\t"
      "call *%[c12170]\n\t"
      "fcomps 0x253f44\n\t"
      "addl $4, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Litem_set_position_8\n\t"
      "pushl $1\n\t"
      "leal -0x8c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x28aa90\n\t"
      "pushl %%ebx\n\t"
      "call *%[markers]\n\t"
      "addl $0x10, %%esp\n\t"
      "testw %%ax, %%ax\n\t"
      "je .Litem_set_position_6\n\t"
      "movl -0x38(%%ebp), %%ecx\n\t"
      "movl -0x34(%%ebp), %%edx\n\t"
      "movl -0x30(%%ebp), %%eax\n\t"
      "movl %%ecx, -0xc(%%ebp)\n\t"
      "movl %%edx, -0x8(%%ebp)\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "jmp .Litem_set_position_7\n\t"
      ".Litem_set_position_6:\n\t"
      "movl 0x31fc44, %%ecx\n\t"
      "movl (%%ecx), %%edx\n\t"
      "movl 0x4(%%ecx), %%eax\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "movl %%edx, -0xc(%%ebp)\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "movl %%ecx, -0x4(%%ebp)\n\t"
      ".Litem_set_position_7:\n\t"
      "pushl $0x3fc90fdb\n\t"
      "pushl $0xbfc90fdb\n\t"
      "call *%[c121e0]\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "addl $0x3c, %%esi\n\t"
      "pushl %%esi\n\t"
      "leal -0x20(%%ebp), %%edx\n\t"
      "fstps -0x20(%%ebp)\n\t"
      "pushl %%edx\n\t"
      "flds -0x8(%%ebp)\n\t"
      "pushl %%esi\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fstps -0x1c(%%ebp)\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "call *%[c213c0]\n\t"
      "addl $0x14, %%esp\n\t"
      "jmp .Litem_set_position_11\n\t"
      ".Litem_set_position_8:\n\t"
      "flds 0x8(%%edi)\n\t"
      "flds 0x4(%%edi)\n\t"
      "flds (%%edi)\n\t"
      "fld %%st(0)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fld %%st(2)\n\t"
      "fmul %%st(3), %%st(0)\n\t"
      "faddp %%st(1)\n\t"
      "fld %%st(3)\n\t"
      "fmul %%st(4), %%st(0)\n\t"
      "faddp %%st(1)\n\t"
      "fsqrt\n\t"
      "fsts -0x14(%%ebp)\n\t"
      "fstp %%st(3)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "fcomps 0x253f44\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Litem_set_position_9\n\t"
      "call *%[gseed]\n\t"
      "pushl %%eax\n\t"
      "call *%[rmreal]\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "addl $4, %%esp\n\t"
      ".Litem_set_position_9:\n\t"
      "movl 0x31fc44, %%eax\n\t"
      "flds (%%eax)\n\t"
      "fmuls 0x4(%%edi)\n\t"
      "flds 0x4(%%eax)\n\t"
      "fmuls (%%edi)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "flds (%%edi)\n\t"
      "fmuls 0x8(%%eax)\n\t"
      "flds (%%eax)\n\t"
      "fmuls 0x8(%%edi)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "flds 0x4(%%eax)\n\t"
      "fmuls 0x8(%%edi)\n\t"
      "flds 0x4(%%edi)\n\t"
      "fmuls 0x8(%%eax)\n\t"
      "leal -0xc(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "call *%[norm]\n\t"
      "fcomps 0x2533c0\n\t"
      "addl $4, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .Litem_set_position_10\n\t"
      "leal -0xc(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[gseed]\n\t"
      "pushl %%eax\n\t"
      "call *%[c10b380]\n\t"
      "addl $8, %%esp\n\t"
      ".Litem_set_position_10:\n\t"
      "call *%[gseed]\n\t"
      "pushl %%eax\n\t"
      "call *%[rmreal]\n\t"
      "fmuls -0x14(%%ebp)\n\t"
      "addl $4, %%esp\n\t"
      "fmuls 0x2568bc\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fmul %%st(2), %%st(0)\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fmul %%st(2), %%st(0)\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "fadds 0x3c(%%esi)\n\t"
      "fstps 0x3c(%%esi)\n\t"
      "fstp %%st(0)\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fadds 0x40(%%esi)\n\t"
      "fstps 0x40(%%esi)\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fadds 0x44(%%esi)\n\t"
      "fstps 0x44(%%esi)\n\t"
      ".Litem_set_position_11:\n\t"
      "movl %%ebx, %%eax\n\t"
      "call *%[f6b80]\n\t"
      "pushl $0\n\t"
      "pushl %%ebx\n\t"
      "call *%[garb]\n\t"
      "addl $8, %%esp\n\t"
      ".Litem_set_position_12:\n\t"
      "cmpw $1, 0x4761d8\n\t"
      "jg .Litem_set_position_13\n\t"
      "pushl $1\n\t"
      "pushl $0x28b\n\t"
      "pushl $0x28aaa0\n\t"
      "pushl $0x253418\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Litem_set_position_13:\n\t"
      "decw 0x4761d8\n\t"
      ".Litem_set_position_14:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [get] "m"(bf6d60_get), [tag] "m"(bf6d60_tag), [assert] "m"(bf6d60_assert), [exitfn] "m"(bf6d60_exitfn), [gerun] "m"(bf6d60_gerun), [cf6af0] "m"(bf6d60_cf6af0), [markers] "m"(bf6d60_markers), [gbsp] "m"(bf6d60_gbsp), [elem] "m"(bf6d60_elem), [c99640] "m"(bf6d60_c99640), [vsca] "m"(bf6d60_vsca), [otrans] "m"(bf6d60_otrans), [c12170] "m"(bf6d60_c12170), [c121e0] "m"(bf6d60_c121e0), [c213c0] "m"(bf6d60_c213c0), [gseed] "m"(bf6d60_gseed), [rmreal] "m"(bf6d60_rmreal), [norm] "m"(bf6d60_norm), [c10b380] "m"(bf6d60_c10b380), [f6b80] "m"(bf6d60_f6b80), [garb] "m"(bf6d60_garb)
      : "memory");
}
#else
#error "item_set_position: clang naked draft required"
#endif

/*
 * ui_widget_group.c
 *
 * TU: c:\halo\SOURCE\interface\ui_widget_group.c
 *   (recovered from the __FILE__ assert string passed to display_assert at
 *    0x000f4f28: "c:\halo\SOURCE\interface\ui_widget_group.c", line 0x1f5.)
 *
 * Shell UI tag preload for the current scenario.  Given the scenario tag
 * index, resolves the 'scnr' tag, force-loads the shared multiplayer game
 * text and white shell bitmap, then branches on the scenario type field
 * (scnr + 0x3c, signed int16: 0 = solo, 1 = multiplayer, 2 = main_menu) to
 * load the matching ui_widget_collection ('Soul') and, for the main menu, a
 * long list of string-list ('ustr'), sound ('snd!') and music ('lsnd') tags.
 * Every load is checked against -1 (NONE) and any failure is reported via
 * error(2, ...).  An unrecognized scenario type asserts and calls
 * system_exit(-1).
 *
 * cachebeta.xbe v01.10.12.2276, FUN_000f4ea0 @ 0x000f4ea0 (items.obj).
 */

void FUN_000f4ea0(int scenario_tag_index)
{
  void *scenario;
  short scenario_type;

  scenario = tag_get(0x73636e72 /* 'scnr' */, scenario_tag_index);

  if (FUN_001b9b00(0x75737472 /* 'ustr' */, "ui\\multiplayer_game_text", 0) == -1)
    error(2, "failed to load the multiplayer game text string list tag");

  if (FUN_001b9b00(0x6269746d /* 'bitm' */, "ui\\shell\\bitmaps\\white", 0) == -1)
    error(2, "generic white texture bitmap");

  /* scnr + 0x3c is a signed int16 scenario type (MOVSX in the original). */
  scenario_type = *(short *)((char *)scenario + 0x3c);

  switch (scenario_type) {
  case 0: /* solo */
    if (FUN_001b9b00(0x536f756c /* 'Soul' */, "ui\\shell\\solo", 0) == -1)
      error(2, "failed to load the solo scenario ui_widget_collection tag");
    break;

  case 1: /* multiplayer */
    if (FUN_001b9b00(0x536f756c, "ui\\shell\\multiplayer", 0) == -1)
      error(2, "failed to load the multiplayer scenario ui_widget_collection tag");
    break;

  case 2: /* main_menu */
    if (FUN_001b9b00(0x536f756c, "ui\\shell\\main_menu", 0) == -1)
      error(2, "failed to load the main menu scenario ui_widget_collection_tag");
    if (FUN_001b9b00(0x76636b79 /* 'vcky' */, "ui\\english", 0) == -1)
      error(2, "failed to load the browser's virtual keyboard tag");
    if (FUN_001b9b00(0x75737472, "ui\\random_player_names", 0) == -1)
      error(2, "failed to load random player names string list tag");
    if (FUN_001b9b00(0x6d706c79 /* 'mply' */, "ui\\multiplayer_scenarios", 0) == -1)
      error(2, "failed to load the multiplayer scenario description tag");
    if (FUN_001b9b00(0x75737472, "ui\\saved_game_file_strings", 0) == -1)
      error(2, "failed to load the default saved game filename string list tag");
    if (FUN_001b9b00(0x75737472, "ui\\default_multiplayer_game_setting_names", 0) == -1)
      error(2, "failed to load the default playlist profile names string list tag");
    if (FUN_001b9b00(0x75737472, "ui\\shell\\strings\\game_variant_descriptions", 0) == -1)
      error(2, "failed to load the multiplayer variant description string list tag");
    if (FUN_001b9b00(0x75737472, "ui\\shell\\main_menu\\player_profiles_select\\difficulty_names", 0) == -1)
      error(2, "failed to load the game difficulty name string list tag");
    if (FUN_001b9b00(0x75737472, "ui\\shell\\strings\\default_player_profile_names", 0) == -1)
      error(2, "failed to load the default player profile names string list tag");
    if (FUN_001b9b00(0x75737472, "ui\\shell\\main_menu\\player_profiles_select\\button_set_long_descriptions", 0) == -1)
      error(2, "failed to load the button set long descriptions string list tag");
    if (FUN_001b9b00(0x75737472, "ui\\shell\\main_menu\\player_profiles_select\\button_set_short_descriptions", 0) == -1)
      error(2, "failed to load the button set short descriptions string list tag");
    if (FUN_001b9b00(0x75737472, "ui\\shell\\main_menu\\player_profiles_select\\joystick_set_defaults_descriptions", 0) == -1)
      error(2, "failed to load the default joystick set descriptions string list tag");
    if (FUN_001b9b00(0x75737472, "ui\\shell\\main_menu\\player_profiles_select\\joystick_set_short_descriptions", 0) == -1)
      error(2, "failed to load the joystick set short descriptions string list tag");
    if (FUN_001b9b00(0x75737472, "ui\\shell\\main_menu\\player_profiles_select\\profile_description_labels", 0) == -1)
      error(2, "failed to load the profile description labels string list tag");
    if (FUN_001b9b00(0x736e6421 /* 'snd!' */, "sound\\sfx\\ui\\cursor", 0) == -1)
      error(2, "failed to load ui cursor sound tag");
    if (FUN_001b9b00(0x736e6421, "sound\\sfx\\ui\\forward", 0) == -1)
      error(2, "failed to load ui forward sound tag");
    if (FUN_001b9b00(0x736e6421, "sound\\sfx\\ui\\back", 0) == -1)
      error(2, "failed to load ui back sound tag");
    if (FUN_001b9b00(0x736e6421, "sound\\sfx\\ui\\flag_failure", 0) == -1)
      error(2, "failed to load ui failure sound tag");
    if (FUN_001b9b00(0x6c736e64 /* 'lsnd' */, "sound\\music\\title1\\title1", 0) == -1)
      error(2, "failed to load main menu title music");
    break;

  default:
    display_assert("unknown scenario type",
                   "c:\\halo\\SOURCE\\interface\\ui_widget_group.c", 0x1f5, true);
    system_exit(-1);
  }
}
/* --- items.obj batch drafts (2026-07-26) --- */

/* 0xf4210 — refresh multiplayer settings select-list item widgets. */
void multiplayer_settings_select_list_update_item(void *widget)
{
  char *tag;
  int handles[3];
  int resolved[3];
  int index;
  int i;

  tag = (char *)tag_get(0x44654c61, *(int *)widget); /* 'aLeD' */
  if (*(int16_t *)tag != 2) {
    display_assert((char *)0x00289bd0, (char *)0x00288938, 0x78a, 1);
    system_exit(-1);
  }
  if (*(int *)(tag + 0x3e0) != 3) {
    display_assert((char *)0x00289b88, (char *)0x00288938, 0x78b, 1);
    system_exit(-1);
  }

  handles[0] = handles[1] = handles[2] = -1;
  FUN_000f3690(handles, widget);
  for (i = 0; i < 3; i++) {
    if (handles[i] == -1)
      resolved[i] = -1;
    else
      resolved[i] = (*(int **)((char *)widget + 0x40))[handles[i]];
  }
  multiplayer_game_set_text_box_for_game_ruleset(resolved, 3);

  for (index = 0; index < 3; index++) {
    char *child;
    char *def;
    char *n0, *n1, *n2, *n3, *n4, *n5, *n6, *n7;
    int entry_handle;
    char *entry;
    int scan;
    short level_cap;
    short level_out;
    short diff_out;

    if (handles[index] == -1)
      break;

    child = (char *)widget_instance_get_nth_child(widget, index);
    if (child == 0 || *(int16_t *)(child + 0xe) != 0) {
      display_assert((char *)0x00289b54, (char *)0x00288938, 0x7af, 1);
      system_exit(-1);
    }
    def = *(char **)(child + 0x34);
    if (def == 0 || *(int16_t *)(def + 0xe) != 1) {
      display_assert((char *)0x00289b28, (char *)0x00288938, 0x7b2, 1);
      system_exit(-1);
    }
    n0 = *(char **)(def + 0x2c);
    if (n0 == 0 || *(int16_t *)(n0 + 0xe) != 0) {
      display_assert((char *)0x00289aec, (char *)0x00288938, 0x7b5, 1);
      system_exit(-1);
    }
    n1 = *(char **)(n0 + 0x2c);
    if (n1 == 0 || *(int16_t *)(n1 + 0xe) != 0) {
      display_assert((char *)0x00289aac, (char *)0x00288938, 0x7b8, 1);
      system_exit(-1);
    }
    n2 = *(char **)(n1 + 0x34);
    if (n2 == 0 || *(int16_t *)(n2 + 0xe) != 1) {
      display_assert((char *)0x00289a70, (char *)0x00288938, 0x7bb, 1);
      system_exit(-1);
    }
    n3 = *(char **)(n2 + 0x2c);
    if (n3 == 0 || *(int16_t *)(n3 + 0xe) != 1) {
      display_assert((char *)0x00289a38, (char *)0x00288938, 0x7be, 1);
      system_exit(-1);
    }
    n4 = *(char **)(n3 + 0x2c);
    if (n4 == 0 || *(int16_t *)(n4 + 0xe) != 1) {
      display_assert((char *)0x002899fc, (char *)0x00288938, 0x7c1, 1);
      system_exit(-1);
    }
    n5 = *(char **)(n4 + 0x2c);
    if (n5 == 0 || *(int16_t *)(n5 + 0xe) != 1) {
      display_assert((char *)0x002899bc, (char *)0x00288938, 0x7c4, 1);
      system_exit(-1);
    }
    n6 = *(char **)(n5 + 0x2c);
    if (n6 == 0 || *(int16_t *)(n6 + 0xe) != 1) {
      display_assert((char *)0x00289970, (char *)0x00288938, 0x7c7, 1);
      system_exit(-1);
    }
    n7 = *(char **)(n6 + 0x2c);
    if (n7 == 0 || *(int16_t *)(n7 + 0xe) != 1) {
      display_assert((char *)0x00289938, (char *)0x00288938, 0x7ca, 1);
      system_exit(-1);
    }
    {
      char *leaf = *(char **)(n7 + 0x2c);
      if (leaf == 0 || *(int16_t *)(leaf + 0xe) != 1) {
        display_assert((char *)0x00289900, (char *)0x00288938, 0x7cd, 1);
        system_exit(-1);
      }

      entry_handle = (*(int **)((char *)widget + 0x40))[handles[index]];
      if (entry_handle == -1)
        goto hide_row;

      entry = 0;
      for (scan = 0; scan < 3; scan++) {
        if (*(int *)(0x5aa3c0 + scan * 0x34) == entry_handle) {
          entry = (char *)(0x5aa3c4 + scan * 0x34);
          break;
        }
      }
      if (entry == 0)
        goto hide_row;

      def[0x10] = 1;
      n2[0x10] = 0;
      n3[0x10] = 1;
      n4[0x10] = 1;
      n5[0x10] = 1;
      n6[0x10] = 1;
      n7[0x10] = 1;
      leaf[0x10] = 1;

      *(void **)(def + 0x3c) =
          ui_widget_realloc(*(int *)(def + 0x3c), 0x18, (char *)0x00288938, 0x7e7);
      if (*(void **)(def + 0x3c) != 0) {
        if ((*(unsigned short *)(entry + 0x1a) & 1) != 0) {
          int ustr = tag_loaded(0x75737472, (char *)0x002898d0);
          wchar_t *src;
          if (ustr != -1)
            src = (wchar_t *)(uintptr_t)FUN_0019d420(ustr, (*(unsigned short *)(entry + 0x1a)) >> 8);
          else
            src = (wchar_t *)0x00281c38;
          ustrncpy(*(wchar_t **)(def + 0x3c), src, 0xb);
          *(int16_t *)(*(char **)(def + 0x3c) + 0x16) = 0;
        } else {
          ustrncpy(*(wchar_t **)(def + 0x3c), (wchar_t *)entry, 0xb);
          *(int16_t *)(*(char **)(def + 0x3c) + 0x16) = 0;
        }
      }

      if (*(int16_t *)(entry + 0x18) < 0)
        level_cap = 0;
      else {
        level_cap = *(int16_t *)(entry + 0x18);
        if (level_cap > (short)(FUN_001c0ed0() - 1))
          level_cap = (short)(FUN_001c0ed0() - 1);
      }
      *(int16_t *)(n0 + 0x50) = level_cap;

      if ((*(unsigned char *)(entry + 0x1a) & 1) != 0) {
        n4[0x10] = 0;
        n6[0x10] = 0;
      } else {
        player_profile_save_last_level_played(entry, &level_out, &diff_out);
        level_out = (short)(level_out + 1);
        if (level_out > 9)
          level_out = 9;
        *(int16_t *)(n4 + 0x40) = level_out;
        *(int16_t *)(n6 + 0x40) = diff_out;
        *(int16_t *)(leaf + 0x40) =
            (short)(*(unsigned char *)(entry + 0x2b) == 1);
      }
      continue;

    hide_row:
      def[0x10] = 0;
      *(int16_t *)(n0 + 0x50) = (int16_t)FUN_001c0ed0();
      n2[0x10] = 1;
      n3[0x10] = 0;
      n4[0x10] = 0;
      n5[0x10] = 0;
      n6[0x10] = 0;
      n7[0x10] = 0;
      leaf[0x10] = 0;
    }
  }
}

/* 0xf46e0 — update playlist/settings item widget text from selected entry. */
void FUN_000f46e0(void *widget)
{
  char *tag;
  char *parent_tag;
  char *parent_def;
  char *row_def;
  int handle;
  int scan;
  char *entry;
  unsigned short count;
  int valid_count;
  short sel;
  short level_cap;

  for (;;) {
    if (*(void **)((char *)widget + 0x30) == 0) {
      display_assert((char *)0x00289ea8, (char *)0x00288938, 0x85e, 1);
      system_exit(-1);
    }

    tag = (char *)tag_get(0x44654c61, *(int *)widget);
    if (*(int16_t *)tag != 2) {
      display_assert((char *)0x00289e64, (char *)0x00288938, 0x864, 1);
      system_exit(-1);
    }
    if (*(int *)(tag + 0x3e0) != 0) {
      display_assert((char *)0x00289e18, (char *)0x00288938, 0x865, 1);
      system_exit(-1);
    }

    parent_tag = (char *)tag_get(0x44654c61, **(int **)((char *)widget + 0x30));
    if (*(int *)(parent_tag + 0x3e0) != 3) {
      display_assert((char *)0x00289da0, (char *)0x00288938, 0x867, 1);
      system_exit(-1);
    }

    parent_def = *(char **)(*(char **)((char *)widget + 0x30) + 0x34);
    row_def = *(char **)(parent_def + 0x2c);
    if (widget != *(void **)(row_def + 0x2c)) {
      display_assert((char *)0x00289da0, (char *)0x00288938, 0x86d, 1);
      system_exit(-1);
    }

    sel = *(int16_t *)((char *)widget + 0x3c);
    count = *(unsigned short *)((char *)widget + 0x44);
    if (sel < 0 || (int)sel >= (int)count) {
      display_assert((char *)0x00289d68, (char *)0x00288938, 0x86f, 1);
      system_exit(-1);
    }
    if (sel < 0 || (int)sel >= (int)count) {
      display_assert((char *)0x00289d50, (char *)0x00288938, 0x872, 1);
      system_exit(-1);
    }

    handle = (*(int **)((char *)widget + 0x40))[sel];
    {
      int handles[1];
      handles[0] = handle;
      multiplayer_game_set_text_box_for_game_ruleset(handles, 1);
    }

    entry = 0;
    if (handle != -1) {
      for (scan = 0; scan < 3; scan++) {
        if (*(int *)(0x5aa3c0 + scan * 0x34) == handle) {
          entry = (char *)(0x5aa3c4 + scan * 0x34);
          break;
        }
      }
    }

    if (entry != 0) {
      *(void **)((char *)widget + 0x4c) = ui_widget_realloc(
          *(int *)((char *)widget + 0x4c), 0x18, (char *)0x00288938, 0x886);
      if (*(void **)((char *)widget + 0x4c) == 0)
        return;

      if ((*(unsigned short *)(entry + 0x1a) & 1) != 0) {
        int ustr = tag_loaded(0x75737472, (char *)0x002898d0);
        wchar_t *src = (wchar_t *)0x0026cdf0;
        if (ustr != -1)
          src = (wchar_t *)(uintptr_t)FUN_0019d420(
              ustr, (*(unsigned short *)(entry + 0x1a)) >> 8);
        ustrncpy(*(wchar_t **)((char *)widget + 0x4c), src, 0xb);
        *(int16_t *)(*(char **)((char *)widget + 0x4c) + 0x16) = 0;
      } else {
        ustrncpy(*(wchar_t **)((char *)widget + 0x4c), (wchar_t *)entry, 0xb);
        *(int16_t *)(*(char **)((char *)widget + 0x4c) + 0x16) = 0;
      }

      if (*(int16_t *)(entry + 0x18) < 0)
        level_cap = 0;
      else {
        level_cap = *(int16_t *)(entry + 0x18);
        if (level_cap > (short)(FUN_001c0ed0() - 1))
          level_cap = (short)(FUN_001c0ed0() - 1);
      }
      *(int16_t *)(parent_def + 0x50) = level_cap;

      *(void **)(row_def + 0x3c) = ui_widget_realloc(
          *(int *)(row_def + 0x3c), 0x200, (char *)0x00288938, 0x89c);
      if (*(void **)(row_def + 0x3c) == 0)
        return;

      if ((*(unsigned char *)(entry + 0x1a) & 1) != 0) {
        int a = tag_loaded(0x75737472, (char *)0x00289d00);
        int b = tag_loaded(0x75737472, (char *)0x00289cb8);
        if (a != -1 && b != -1) {
          wchar_t *sa = (wchar_t *)(uintptr_t)FUN_0019d420(
              a, *(unsigned char *)(entry + 0x29));
          wchar_t *sb = (wchar_t *)(uintptr_t)FUN_0019d420(
              b, *(unsigned char *)(entry + 0x28));
          unicode_sprintf(*(wchar_t **)(row_def + 0x3c), 0xff,
                          (wchar_t *)0x00289ca4, sa, (wchar_t *)0x00261f2c, sb);
          *(int16_t *)(*(char **)(row_def + 0x3c) + 0x1fe) = 0;
        } else {
          **(int16_t **)(row_def + 0x3c) = 0;
          *(int16_t *)(*(char **)(row_def + 0x3c) + 0x1fe) = 0;
        }
      } else {
        int a = tag_loaded(0x75737472, (char *)0x00289c58);
        int b = tag_loaded(0x75737472, (char *)0x00289c10);
        if (a != -1 && b != -1) {
          wchar_t *sa = (wchar_t *)(uintptr_t)FUN_0019d420(
              a, *(unsigned char *)(entry + 0x29));
          wchar_t *sb = (wchar_t *)(uintptr_t)FUN_0019d420(
              b, *(unsigned char *)(entry + 0x28));
          unicode_sprintf(*(wchar_t **)(row_def + 0x3c), 0xff,
                          (wchar_t *)0x00289ca4, sa, (wchar_t *)0x00261f2c, sb);
        }
        *(int16_t *)(*(char **)(row_def + 0x3c) + 0x1fe) = 0;
      }
      return;
    }

    count = *(unsigned short *)((char *)widget + 0x44);
    if (count == 0) {
      *(void **)((char *)widget + 0x4c) = ui_widget_realloc(
          *(int *)((char *)widget + 0x4c), 4, (char *)0x00288938, 0x8d2);
      if (*(void **)((char *)widget + 0x4c) != 0)
        **(int16_t **)((char *)widget + 0x4c) = 0;
      *(int16_t *)(parent_def + 0x50) = 0;
      *(void **)(row_def + 0x3c) = ui_widget_realloc(
          *(int *)(row_def + 0x3c), 4, (char *)0x00288938, 0x8d7);
      if (*(void **)(row_def + 0x3c) != 0)
        **(int16_t **)(row_def + 0x3c) = 0;
      return;
    }

    qsort(*(void **)((char *)widget + 0x40), count, 4, (void *)FUN_000f3960);
    valid_count = 0;
    while (valid_count < (int)count &&
           (*(int **)((char *)widget + 0x40))[valid_count] != -1)
      valid_count++;
    *(unsigned short *)((char *)widget + 0x44) = (unsigned short)valid_count;
    sel = *(int16_t *)((char *)widget + 0x3c);
    if (sel < 0) {
      *(int16_t *)((char *)widget + 0x3c) = 0;
    } else {
      short max_sel = (short)(valid_count - 1);
      if (sel > max_sel)
        sel = max_sel;
      *(int16_t *)((char *)widget + 0x3c) = sel;
    }
  }
}

/* 0xf4b60 — sync item-profile UI child text indices from parent widget bytes. */
#if defined(__clang__)
static void (*const f4b60_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const f4b60_exitfn)(int) = system_exit;
static void *(*const f4b60_tag)(int, int) = tag_get;
static void (*const f4b60_handles)(int *, void *) = FUN_000f3690;
static void *(*const f4b60_nth)(void *, int) = widget_instance_get_nth_child;

__attribute__((naked, noinline))
void FUN_000f4b60(void *widget __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xc, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 8(%%ebp), %%esi\n\t"
      "movl 64(%%esi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "pushl %%edi\n\t"
      "jne .LFUN_000f4b60_1\n\t"
      "pushl $1\n\t"
      "pushl $0x944\n\t"
      "pushl $0x288938\n\t"
      "pushl $0x28a058\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000f4b60_1:\n\t"
      "movl (%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x44654c61\n\t"
      "call *%[tag]\n\t"
      "movl %%eax, %%edi\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $2, (%%edi)\n\t"
      "je .LFUN_000f4b60_2\n\t"
      "pushl $1\n\t"
      "pushl $0x949\n\t"
      "pushl $0x288938\n\t"
      "pushl $0x28a01c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000f4b60_2:\n\t"
      "cmpl $3, 992(%%edi)\n\t"
      "je .LFUN_000f4b60_3\n\t"
      "pushl $1\n\t"
      "pushl $0x94a\n\t"
      "pushl $0x288938\n\t"
      "pushl $0x289fd8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000f4b60_3:\n\t"
      "leal -12(%%ebp), %%eax\n\t"
      "movl %%esi, %%ecx\n\t"
      "call *%[handles]\n\t"
      "xorl %%edi, %%edi\n\t"
      "jmp .LFUN_000f4b60_5\n\t"
      ".LFUN_000f4b60_4:\n\t"
      "movl 8(%%ebp), %%esi\n\t"
      ".LFUN_000f4b60_5:\n\t"
      "cmpl $-1, -12(%%ebp,%%edi,4)\n\t"
      "je .LFUN_000f4b60_9\n\t"
      "pushl %%edi\n\t"
      "pushl %%esi\n\t"
      "call *%[nth]\n\t"
      "movl (%%eax), %%ecx\n\t"
      "movl 52(%%eax), %%esi\n\t"
      "movl 44(%%esi), %%ebx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x44654c61\n\t"
      "call *%[tag]\n\t"
      "movl 992(%%eax), %%ecx\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpl $2, %%ecx\n\t"
      "je .LFUN_000f4b60_6\n\t"
      "pushl $1\n\t"
      "pushl $0x95b\n\t"
      "pushl $0x288938\n\t"
      "pushl $0x289f90\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000f4b60_6:\n\t"
      "movl (%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x44654c61\n\t"
      "call *%[tag]\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $1, (%%eax)\n\t"
      "je .LFUN_000f4b60_7\n\t"
      "pushl $1\n\t"
      "pushl $0x95d\n\t"
      "pushl $0x288938\n\t"
      "pushl $0x289f48\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000f4b60_7:\n\t"
      "movl (%%ebx), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x44654c61\n\t"
      "call *%[tag]\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $0, (%%eax)\n\t"
      "je .LFUN_000f4b60_8\n\t"
      "pushl $1\n\t"
      "pushl $0x95f\n\t"
      "pushl $0x288938\n\t"
      "pushl $0x289ef8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000f4b60_8:\n\t"
      "movl 8(%%ebp), %%ecx\n\t"
      "movl 64(%%ecx), %%edx\n\t"
      "movl -12(%%ebp,%%edi,4), %%eax\n\t"
      "movzbw (%%eax,%%edx,1), %%ax\n\t"
      "incl %%edi\n\t"
      "cmpl $3, %%edi\n\t"
      "movw %%ax, 64(%%esi)\n\t"
      "movw %%ax, 80(%%ebx)\n\t"
      "jl .LFUN_000f4b60_4\n\t"
      ".LFUN_000f4b60_9:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(f4b60_assert), [exitfn] "m"(f4b60_exitfn), [tag] "m"(f4b60_tag), [handles] "m"(f4b60_handles), [nth] "m"(f4b60_nth)
      : "memory");
}
#else
void FUN_000f4b60(void *widget)
{
  char *tag;
  int handles[3];
  int index;
  unsigned char *byte_table;

  if (*(int *)((char *)widget + 0x40) == 0) {
    display_assert((char *)0x0028a058, (char *)0x00288938, 0x944, 1);
    system_exit(-1);
  }

  tag = (char *)tag_get(0x44654c61, *(int *)widget); /* 'aLeD' */
  if (*(int16_t *)tag != 2) {
    display_assert((char *)0x0028a01c, (char *)0x00288938, 0x949, 1);
    system_exit(-1);
  }
  if (*(int *)(tag + 0x3e0) != 3) {
    display_assert((char *)0x00289fd8, (char *)0x00288938, 0x94a, 1);
    system_exit(-1);
  }

  FUN_000f3690(handles, widget);
  byte_table = *(unsigned char **)((char *)widget + 0x40);

  for (index = 0; index < 3; index++) {
    char *child_inst;
    char *child_def;
    char *nested;
    uint16_t value;

    if (handles[index] == -1)
      break;

    child_inst = (char *)widget_instance_get_nth_child(widget, index);
    child_def = *(char **)(child_inst + 0x34);
    nested = *(char **)(child_def + 0x2c);

    if (*(int *)((char *)tag_get(0x44654c61, *(int *)child_inst) + 0x3e0) !=
        2) {
      display_assert((char *)0x00289f90, (char *)0x00288938, 0x95b, 1);
      system_exit(-1);
    }
    if (*(int16_t *)tag_get(0x44654c61, *(int *)child_def) != 1) {
      display_assert((char *)0x00289f48, (char *)0x00288938, 0x95d, 1);
      system_exit(-1);
    }
    if (*(int16_t *)tag_get(0x44654c61, *(int *)nested) != 0) {
      display_assert((char *)0x00289ef8, (char *)0x00288938, 0x95f, 1);
      system_exit(-1);
    }

    value = (uint16_t)byte_table[handles[index]];
    *(uint16_t *)(child_def + 0x40) = value;
    *(uint16_t *)(nested + 0x50) = value;
  }
}
#endif


/* 0xf4cf0 — sync multiplayer item UI child text-box indices from parent widget. */
#if defined(__clang__)
static void (*const f4cf0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const f4cf0_exitfn)(int) = system_exit;
static void *(*const f4cf0_tag)(int, int) = tag_get;
static void (*const f4cf0_handles)(int *, void *) = FUN_000f3690;
static void *(*const f4cf0_nth)(void *, int) = widget_instance_get_nth_child;

__attribute__((naked, noinline))
void FUN_000f4cf0(void *widget __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x10, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 8(%%ebp), %%edi\n\t"
      "movl (%%edi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x44654c61\n\t"
      "call *%[tag]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $2, (%%esi)\n\t"
      "je .LFUN_000f4cf0_1\n\t"
      "pushl $1\n\t"
      "pushl $0x9bf\n\t"
      "pushl $0x288938\n\t"
      "pushl $0x28974c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000f4cf0_1:\n\t"
      "cmpl $3, 992(%%esi)\n\t"
      "je .LFUN_000f4cf0_2\n\t"
      "pushl $1\n\t"
      "pushl $0x9c0\n\t"
      "pushl $0x288938\n\t"
      "pushl $0x289710\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000f4cf0_2:\n\t"
      "leal -16(%%ebp), %%eax\n\t"
      "movl %%edi, %%ecx\n\t"
      "call *%[handles]\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "jmp .LFUN_000f4cf0_4\n\t"
      ".LFUN_000f4cf0_3:\n\t"
      "movl 8(%%ebp), %%edi\n\t"
      "movl %%edi, %%edi\n\t"
      ".LFUN_000f4cf0_4:\n\t"
      "cmpl $-1, -16(%%ebp,%%ebx,4)\n\t"
      "je .LFUN_000f4cf0_9\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "call *%[nth]\n\t"
      "movl 52(%%eax), %%esi\n\t"
      "movl (%%eax), %%edx\n\t"
      "movl 44(%%esi), %%edi\n\t"
      "movl 44(%%edi), %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x44654c61\n\t"
      "movl %%ecx, -4(%%ebp)\n\t"
      "call *%[tag]\n\t"
      "movl 992(%%eax), %%ecx\n\t"
      "addl $0x10, %%esp\n\t"
      "testl %%ecx, %%ecx\n\t"
      "jne .LFUN_000f4cf0_5\n\t"
      "pushl $1\n\t"
      "pushl $0x9d2\n\t"
      "pushl $0x288938\n\t"
      "pushl $0x2896d0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000f4cf0_5:\n\t"
      "movl (%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x44654c61\n\t"
      "call *%[tag]\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $1, (%%eax)\n\t"
      "je .LFUN_000f4cf0_6\n\t"
      "pushl $1\n\t"
      "pushl $0x9d4\n\t"
      "pushl $0x288938\n\t"
      "pushl $0x289688\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000f4cf0_6:\n\t"
      "movl (%%edi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x44654c61\n\t"
      "call *%[tag]\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $0, (%%eax)\n\t"
      "je .LFUN_000f4cf0_7\n\t"
      "pushl $1\n\t"
      "pushl $0x9d6\n\t"
      "pushl $0x288938\n\t"
      "pushl $0x289640\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000f4cf0_7:\n\t"
      "movl -4(%%ebp), %%edx\n\t"
      "movl (%%edx), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x44654c61\n\t"
      "call *%[tag]\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $1, (%%eax)\n\t"
      "je .LFUN_000f4cf0_8\n\t"
      "pushl $1\n\t"
      "pushl $0x9d8\n\t"
      "pushl $0x288938\n\t"
      "pushl $0x2895f0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000f4cf0_8:\n\t"
      "movw -16(%%ebp,%%ebx,4), %%ax\n\t"
      "movl -4(%%ebp), %%ecx\n\t"
      "movw %%ax, 64(%%esi)\n\t"
      "incl %%ebx\n\t"
      "cmpl $3, %%ebx\n\t"
      "movw %%ax, 80(%%edi)\n\t"
      "movw %%ax, 64(%%ecx)\n\t"
      "jl .LFUN_000f4cf0_3\n\t"
      ".LFUN_000f4cf0_9:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(f4cf0_assert), [exitfn] "m"(f4cf0_exitfn), [tag] "m"(f4cf0_tag), [handles] "m"(f4cf0_handles), [nth] "m"(f4cf0_nth)
      : "memory");
}
#else
void FUN_000f4cf0(void *widget)
{
  char *tag;
  int handles[4];
  int index;

  tag = (char *)tag_get(0x44654c61, *(int *)widget); /* 'aLeD' */
  if (*(int16_t *)tag != 2) {
    display_assert((char *)0x0028974c, (char *)0x00288938, 0x9bf, 1);
    system_exit(-1);
  }
  if (*(int *)(tag + 0x3e0) != 3) {
    display_assert((char *)0x00289710, (char *)0x00288938, 0x9c0, 1);
    system_exit(-1);
  }

  FUN_000f3690(handles, widget);

  for (index = 0; index < 3; index++) {
    char *child_inst;
    char *child_def;
    char *nested;
    char *leaf;
    int16_t value;

    if (handles[index] == -1)
      break;

    child_inst = (char *)widget_instance_get_nth_child(widget, index);
    child_def = *(char **)(child_inst + 0x34);
    nested = *(char **)(child_def + 0x2c);
    leaf = *(char **)(nested + 0x2c);

    if (*(int *)((char *)tag_get(0x44654c61, *(int *)child_inst) + 0x3e0) ==
        0) {
      display_assert((char *)0x002896d0, (char *)0x00288938, 0x9d2, 1);
      system_exit(-1);
    }
    if (*(int16_t *)tag_get(0x44654c61, *(int *)child_def) != 1) {
      display_assert((char *)0x00289688, (char *)0x00288938, 0x9d4, 1);
      system_exit(-1);
    }
    if (*(int16_t *)tag_get(0x44654c61, *(int *)nested) != 0) {
      display_assert((char *)0x00289640, (char *)0x00288938, 0x9d6, 1);
      system_exit(-1);
    }
    if (*(int16_t *)tag_get(0x44654c61, *(int *)leaf) != 1) {
      display_assert((char *)0x002895f0, (char *)0x00288938, 0x9d8, 1);
      system_exit(-1);
    }

    value = (int16_t)handles[index];
    *(int16_t *)(child_def + 0x40) = value;
    *(int16_t *)((char *)widget + 0x50) = value;
    *(int16_t *)(leaf + 0x40) = value;
  }
}
#endif


/* 0xf5640 — virtual-keyboard edit-session active flag. */
char FUN_000f5640(void)
{
  return *(char *)0x46cef0;
}

/* 0xf5650 — virtual-keyboard caps/shift-related UI flag. */
char FUN_000f5650(void)
{
  return *(char *)0x46cf06;
}

/* 0xf5660 — virtual-keyboard cursor left (skip duplicate keymap glyphs). */
#if defined(__clang__)
static void (*const FUN_000f5660_snd)(int16_t) = ui_play_audio_feedback_sound;

__attribute__((naked, noinline))
char FUN_000f5660(void)
{
  __asm__ volatile(
      "movswl 0x46cef8, %%ecx\n\t"
      "movw 0x46cefa, %%ax\n\t"
      "imull $0xb, %%ecx, %%ecx\n\t"
      "movswl %%ax, %%edx\n\t"
      "movb 0x28a790(%%edx,%%ecx), %%dl\n\t"
      "pushl %%esi\n\t"
      "jmp 2f\n\t"
      "leal (%%ecx), %%ecx\n\t"
      "2:\n\t"
      "decw %%ax\n\t"
      "jns 1f\n\t"
      "movw $0xa, %%ax\n\t"
      "1:\n\t"
      "movswl %%ax, %%esi\n\t"
      "cmpb %%dl, 0x28a790(%%esi,%%ecx)\n\t"
      "je 2b\n\t"
      "pushl $1\n\t"
      "movw %%ax, 0x46cefa\n\t"
      "call *%[snd]\n\t"
      "addl $4, %%esp\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "ret\n\t"
      :
      : [snd] "m"(FUN_000f5660_snd)
      : "memory");
}
#else
char FUN_000f5660(void)
{
  int16_t row;
  int16_t col;
  int base;
  char original_key;

  row = *(int16_t *)0x46cef8;
  col = *(int16_t *)0x46cefa;
  base = (int)row * 0xb;
  original_key = ((char *)0x28a790)[base + (int)col];
  for (;;) {
    col = (int16_t)(col - 1);
    if ((int16_t)col < 0)
      col = 10;
    if (((char *)0x28a790)[base + (int)col] != original_key)
      break;
  }
  *(int16_t *)0x46cefa = col;
  ui_play_audio_feedback_sound(1);
  return 1;
}
#endif

/* 0xf56b0 — virtual-keyboard cursor right (skip duplicate keymap glyphs). */
#if defined(__clang__)
static void (*const FUN_000f56b0_snd)(int16_t) = ui_play_audio_feedback_sound;

__attribute__((naked, noinline))
char FUN_000f56b0(void)
{
  __asm__ volatile(
      "movswl 0x46cef8, %%ecx\n\t"
      "movw 0x46cefa, %%ax\n\t"
      "imull $0xb, %%ecx, %%ecx\n\t"
      "movswl %%ax, %%edx\n\t"
      "movb 0x28a790(%%edx,%%ecx), %%dl\n\t"
      "pushl %%esi\n\t"
      "jmp 2f\n\t"
      "leal (%%ecx), %%ecx\n\t"
      "2:\n\t"
      "incw %%ax\n\t"
      "cmpw $0xb, %%ax\n\t"
      "jne 1f\n\t"
      "xorw %%ax, %%ax\n\t"
      "1:\n\t"
      "movswl %%ax, %%esi\n\t"
      "cmpb %%dl, 0x28a790(%%esi,%%ecx)\n\t"
      "je 2b\n\t"
      "pushl $1\n\t"
      "movw %%ax, 0x46cefa\n\t"
      "call *%[snd]\n\t"
      "addl $4, %%esp\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "ret\n\t"
      :
      : [snd] "m"(FUN_000f56b0_snd)
      : "memory");
}
#else
char FUN_000f56b0(void)
{
  int16_t row;
  int16_t col;
  int base;
  char original_key;

  row = *(int16_t *)0x46cef8;
  col = *(int16_t *)0x46cefa;
  base = (int)row * 0xb;
  original_key = ((char *)0x28a790)[base + (int)col];
  for (;;) {
    col = (int16_t)(col + 1);
    if ((int16_t)col == 11)
      col = 0;
    if (((char *)0x28a790)[base + (int)col] != original_key)
      break;
  }
  *(int16_t *)0x46cefa = col;
  ui_play_audio_feedback_sound(1);
  return 1;
}
#endif

/* 0xf5800 — look up a soft-keyboard glyph for slot_index (@<si>). */
#if defined(__clang__)
static void (*const FUN_000f5800_assert)(const char *, const char *, int,
                                         bool) = display_assert;
static void (*const FUN_000f5800_exit)(int) = system_exit;

__attribute__((naked, noinline))
unsigned short FUN_000f5800(int16_t slot_index __attribute__((unused)))
{
  __asm__ volatile(
      "movl 0x46cef4, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne 1f\n\t"
      "pushl $1\n\t"
      "pushl $0x3da\n\t"
      "pushl $0x28a854\n\t"
      "pushl $0x28a97c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exit]\n\t"
      "addl $0x14, %%esp\n\t"
      "1:\n\t"
      "cmpw $0x24, %%si\n\t"
      "jb 2f\n\t"
      "pushl $1\n\t"
      "pushl $0x3db\n\t"
      "pushl $0x28a854\n\t"
      "pushl $0x28a94c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exit]\n\t"
      "addl $0x14, %%esp\n\t"
      "2:\n\t"
      "movl 0x46cef4, %%ecx\n\t"
      "movl 0x34(%%ecx), %%edx\n\t"
      "movb 0x46cef1, %%cl\n\t"
      "movzwl %%si, %%eax\n\t"
      "leal (%%eax,%%eax,4), %%eax\n\t"
      "shll $4, %%eax\n\t"
      "addl %%edx, %%eax\n\t"
      "testb %%cl, %%cl\n\t"
      "movb 0x46cef2, %%cl\n\t"
      "je 5f\n\t"
      "testb %%cl, %%cl\n\t"
      "je 3f\n\t"
      "movw 0xa(%%eax), %%ax\n\t"
      "jmp 8f\n\t"
      "3:\n\t"
      "movb 0x46cef3, %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "je 4f\n\t"
      "movw 0xc(%%eax), %%ax\n\t"
      "jmp 8f\n\t"
      "4:\n\t"
      "movw 4(%%eax), %%ax\n\t"
      "jmp 8f\n\t"
      "5:\n\t"
      "testb %%cl, %%cl\n\t"
      "movb 0x46cef3, %%cl\n\t"
      "je 7f\n\t"
      "testb %%cl, %%cl\n\t"
      "je 6f\n\t"
      "movw 0xe(%%eax), %%ax\n\t"
      "jmp 8f\n\t"
      "6:\n\t"
      "movw 6(%%eax), %%ax\n\t"
      "jmp 8f\n\t"
      "7:\n\t"
      "testb %%cl, %%cl\n\t"
      "je 9f\n\t"
      "movw 8(%%eax), %%ax\n\t"
      "jmp 8f\n\t"
      "9:\n\t"
      "movw 2(%%eax), %%ax\n\t"
      "8:\n\t"
      "testw %%ax, %%ax\n\t"
      "jne 10f\n\t"
      "movl $0x7f, %%eax\n\t"
      "10:\n\t"
      "ret\n\t"
      :
      : [assert] "m"(FUN_000f5800_assert), [exit] "m"(FUN_000f5800_exit)
      : "memory");
}
#else
unsigned short FUN_000f5800(int16_t slot_index /* @<si> */)
{
  char *ui_globals;
  char *entry;
  unsigned short glyph;
  char shift;
  char alt;
  char caps;

  ui_globals = *(char **)0x46cef4;
  if (ui_globals == 0) {
    display_assert((char *)0x0028a97c, (char *)0x0028a854, 0x3da, 1);
    system_exit(-1);
  }
  if ((uint16_t)slot_index >= 0x24) {
    display_assert((char *)0x0028a94c, (char *)0x0028a854, 0x3db, 1);
    system_exit(-1);
  }

  entry = *(char **)(ui_globals + 0x34) +
          (((int)(uint16_t)slot_index + (int)(uint16_t)slot_index * 4) << 4);
  shift = *(char *)0x46cef1;
  alt = *(char *)0x46cef2;
  caps = *(char *)0x46cef3;

  if (shift != 0) {
    if (alt != 0)
      glyph = *(unsigned short *)(entry + 0xa);
    else if (caps != 0)
      glyph = *(unsigned short *)(entry + 0xc);
    else
      glyph = *(unsigned short *)(entry + 4);
  } else if (alt != 0) {
    if (caps != 0)
      glyph = *(unsigned short *)(entry + 0xe);
    else
      glyph = *(unsigned short *)(entry + 6);
  } else if (caps != 0) {
    glyph = *(unsigned short *)(entry + 8);
  } else {
    glyph = *(unsigned short *)(entry + 2);
  }

  if (glyph == 0)
    return 0x7f;
  return glyph;
}
#endif

/* FUN_000f5900 (0xf5900) — draw the item/profile name UI (font, bitmap, editable string). */
#if defined(__clang__)
static void (*const f5900_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const f5900_exitfn)(int) = system_exit;
static void *(*const f5900_tag)(int, int) = tag_get;
static void *(*const f5900_bmap)(int, short, short) = FUN_00077040;
static void (*const f5900_drawbmp)(int, short *, short *, short *, int, int, int) = draw_bitmap_in_rect;
static void (*const f5900_dsfont)(int, int, int, int, const void *) = draw_string_set_font;
static int (*const f5900_u9d420)(int, int) = FUN_0019d420;
static void (*const f5900_rdraw)(void *, short *, const void *, int, unsigned short *) = rasterizer_draw_string;
static void (*const f5900_u9cdb0)(short *, void *, short *, short *) = FUN_0019cdb0;
static unsigned int (*const f5900_msys)(void) = system_milliseconds;
static void *(*const f5900_u9cff0)(void *, unsigned short) = FUN_0019cff0;
static unsigned short (*const f5900_f5800)(short) = FUN_000f5800;

__attribute__((naked, noinline))
void FUN_000f5900(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x74, %%esp\n\t"
      "movl $0x3f800000, -0x34(%%ebp)\n\t"
      "movl -0x34(%%ebp), %%eax\n\t"
      "pushl %%ebx\n\t"
      "movl %%eax, -0x44(%%ebp)\n\t"
      "movl $0x3f666666, -0x28(%%ebp)\n\t"
      "movl -0x28(%%ebp), %%eax\n\t"
      "pushl %%esi\n\t"
      "movl %%eax, -0x38(%%ebp)\n\t"
      "movl 0x46cef4, %%eax\n\t"
      "pushl %%edi\n\t"
      "movl $0x3f666666, -0x30(%%ebp)\n\t"
      "movl -0x30(%%ebp), %%ecx\n\t"
      "movl $0x3f666666, -0x2c(%%ebp)\n\t"
      "movl -0x2c(%%ebp), %%edx\n\t"
      "xorl %%esi, %%esi\n\t"
      "orl $0xffffffff, %%edi\n\t"
      "cmpl %%esi, %%eax\n\t"
      "movl %%ecx, -0x40(%%ebp)\n\t"
      "movl %%edx, -0x3c(%%ebp)\n\t"
      "je .LFUN_000f5900_1\n\t"
      "cmpl %%edi, 0xc(%%eax)\n\t"
      "jne .LFUN_000f5900_2\n\t"
      ".LFUN_000f5900_1:\n\t"
      "pushl $1\n\t"
      "pushl $0x40b\n\t"
      "pushl $0x28a854\n\t"
      "pushl $0x28a9d8\n\t"
      "call *%[assert]\n\t"
      "pushl %%edi\n\t"
      "call *%[exitfn]\n\t"
      "movl 0x46cef4, %%eax\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000f5900_2:\n\t"
      "movl 0xc(%%eax), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x666f6e74\n\t"
      "call *%[tag]\n\t"
      "addl $8, %%esp\n\t"
      "cmpl %%esi, %%eax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "jne .LFUN_000f5900_3\n\t"
      "pushl $1\n\t"
      "pushl $0x40d\n\t"
      "pushl $0x28a854\n\t"
      "pushl $0x28a9c0\n\t"
      "call *%[assert]\n\t"
      "pushl %%edi\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000f5900_3:\n\t"
      "movl 0x46cef4, %%eax\n\t"
      "movl 0x1c(%%eax), %%ecx\n\t"
      "cmpl %%edi, %%ecx\n\t"
      "movl $0x280, %%ebx\n\t"
      "je .LFUN_000f5900_5\n\t"
      "pushl %%esi\n\t"
      "movl %%ecx, %%edx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edx\n\t"
      "movw %%si, -0x1c(%%ebp)\n\t"
      "movw %%si, -0x1a(%%ebp)\n\t"
      "movw $0x1e0, -0x18(%%ebp)\n\t"
      "movw %%bx, -0x16(%%ebp)\n\t"
      "call *%[bmap]\n\t"
      "movl %%eax, %%edi\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl %%esi, %%edi\n\t"
      "jne .LFUN_000f5900_4\n\t"
      "pushl $1\n\t"
      "pushl $0x415\n\t"
      "pushl $0x28a854\n\t"
      "pushl $0x263768\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000f5900_4:\n\t"
      "pushl %%esi\n\t"
      "pushl %%esi\n\t"
      "pushl $-1\n\t"
      "pushl %%esi\n\t"
      "leal -0x1c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x1c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edi\n\t"
      "call *%[drawbmp]\n\t"
      "movl 0x46cef4, %%eax\n\t"
      "addl $0x1c, %%esp\n\t"
      "orl $0xffffffff, %%edi\n\t"
      ".LFUN_000f5900_5:\n\t"
      "movl 0xc(%%eax), %%eax\n\t"
      "leal -0x44(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%esi\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[dsfont]\n\t"
      "movl 0x46cef4, %%eax\n\t"
      "movl 0x2c(%%eax), %%ecx\n\t"
      "addl $0x14, %%esp\n\t"
      "cmpl %%edi, %%ecx\n\t"
      "je .LFUN_000f5900_6\n\t"
      "movl 0x2c(%%eax), %%edx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x46cf04, %%cx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[u9d420]\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%esi\n\t"
      "leal -0x1c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x1c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movw $0x4e, -0x1c(%%ebp)\n\t"
      "movw $0x72, -0x1a(%%ebp)\n\t"
      "movw $0x6e, -0x18(%%ebp)\n\t"
      "movw %%bx, -0x16(%%ebp)\n\t"
      "call *%[rdraw]\n\t"
      "movl 0x46cef4, %%eax\n\t"
      "addl $0x1c, %%esp\n\t"
      ".LFUN_000f5900_6:\n\t"
      "movl 0xc(%%eax), %%eax\n\t"
      "leal -0x34(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%esi\n\t"
      "pushl $2\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[dsfont]\n\t"
      "movb 0x46cf07, %%al\n\t"
      "addl $0x14, %%esp\n\t"
      "cmpb $1, %%al\n\t"
      "movw $0x76, -0x1c(%%ebp)\n\t"
      "movw $0xdc, -0x1a(%%ebp)\n\t"
      "movw $0x8f, -0x18(%%ebp)\n\t"
      "movw $0x1a4, -0x16(%%ebp)\n\t"
      "jne .LFUN_000f5900_7\n\t"
      "movl 0x46cf14, %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%esi\n\t"
      "pushl %%ecx\n\t"
      "call *%[bmap]\n\t"
      "movl %%eax, %%edi\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl %%esi, %%edi\n\t"
      "je .LFUN_000f5900_7\n\t"
      "movl 0x46cf08, %%ecx\n\t"
      "leal -0x24(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x14(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "leal -0x1c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[u9cdb0]\n\t"
      "addw $-2, -0x12(%%ebp)\n\t"
      "addw $2, -0xe(%%ebp)\n\t"
      "pushl %%esi\n\t"
      "pushl %%esi\n\t"
      "pushl $0x7f7f7f7f\n\t"
      "pushl %%esi\n\t"
      "leal -0x1c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x14(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edi\n\t"
      "call *%[drawbmp]\n\t"
      "addl $0x2c, %%esp\n\t"
      ".LFUN_000f5900_7:\n\t"
      "movl 0x46cf08, %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%esi\n\t"
      "pushl %%esi\n\t"
      "leal -0x1c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x1c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[rdraw]\n\t"
      "movb 0x46cf07, %%al\n\t"
      "addl $0x14, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_000f5900_12\n\t"
      "cmpl $-1, 0x46cf14\n\t"
      "je .LFUN_000f5900_12\n\t"
      "call *%[msys]\n\t"
      "movl %%eax, %%edx\n\t"
      "movl $0x10624dd3, %%eax\n\t"
      "mull %%edx\n\t"
      "shrl $6, %%edx\n\t"
      "testb $1, %%dl\n\t"
      "je .LFUN_000f5900_12\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movl 0x46cf08, %%ebx\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x6(%%ecx), %%ax\n\t"
      "addw 0x4(%%ecx), %%ax\n\t"
      "pushl %%esi\n\t"
      "pushl %%esi\n\t"
      "xorl %%edi, %%edi\n\t"
      "movl %%edi, -0x4(%%ebp)\n\t"
      "movl %%esi, -0xc(%%ebp)\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "movl 0x46cf14, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[bmap]\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl %%esi, %%eax\n\t"
      "movl %%eax, -0x18(%%ebp)\n\t"
      "je .LFUN_000f5900_12\n\t"
      "cmpl %%esi, %%ebx\n\t"
      "je .LFUN_000f5900_10\n\t"
      ".LFUN_000f5900_8:\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw (%%ebx), %%cx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[u9cff0]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_000f5900_11\n\t"
      "cmpl 0x46cf0c, %%ebx\n\t"
      "jae .LFUN_000f5900_9\n\t"
      "movw 0x2(%%eax), %%cx\n\t"
      "addw %%cx, -0x4(%%ebp)\n\t"
      "movl -0x4(%%ebp), %%edi\n\t"
      ".LFUN_000f5900_9:\n\t"
      "addw 0x2(%%eax), %%si\n\t"
      "addl $2, %%ebx\n\t"
      "jne .LFUN_000f5900_8\n\t"
      "jmp .LFUN_000f5900_11\n\t"
      ".LFUN_000f5900_10:\n\t"
      "xorl %%esi, %%esi\n\t"
      "movw -0xc(%%ebp), %%si\n\t"
      ".LFUN_000f5900_11:\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "sarw $1, %%si\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl $-1\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "leal -0x24(%%ebp), %%ecx\n\t"
      "subl %%esi, %%edi\n\t"
      "addl $0x140, %%edi\n\t"
      "movw %%di, -0x22(%%ebp)\n\t"
      "movl -0x22(%%ebp), %%edx\n\t"
      "incl %%edx\n\t"
      "movw %%dx, -0x1e(%%ebp)\n\t"
      "movl -0x18(%%ebp), %%edx\n\t"
      "pushl %%ecx\n\t"
      "addl $0x78, %%eax\n\t"
      "pushl %%edx\n\t"
      "movw $0x78, -0x24(%%ebp)\n\t"
      "movw %%ax, -0x20(%%ebp)\n\t"
      "call *%[drawbmp]\n\t"
      "addl $0x1c, %%esp\n\t"
      "xorl %%esi, %%esi\n\t"
      ".LFUN_000f5900_12:\n\t"
      "movl 0x46cef4, %%ecx\n\t"
      "movl 0xc(%%ecx), %%edx\n\t"
      "leal -0x34(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl $2\n\t"
      "pushl $-1\n\t"
      "pushl %%edx\n\t"
      "call *%[dsfont]\n\t"
      "movl 0x46cef4, %%eax\n\t"
      "movl 0x34(%%eax), %%ebx\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw %%si, -0x74(%%ebp)\n\t"
      "movl $0xb, %%ecx\n\t"
      "leal -0x72(%%ebp), %%edi\n\t"
      "rep stosl\n\t"
      "addl $0x14, %%esp\n\t"
      "movl %%ebx, -0x18(%%ebp)\n\t"
      "stosw\n\t"
      "movl %%esi, -0x4(%%ebp)\n\t"
      "movl $0x31e5b0, %%edi\n\t"
      "addl $0x2c, %%ebx\n\t"
      ".LFUN_000f5900_13:\n\t"
      "movl -0x4(%%ebp), %%esi\n\t"
      "call *%[f5800]\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "movw %%ax, -0x74(%%ebp)\n\t"
      "movl -0x74(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[u9cff0]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_000f5900_14\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "pushl $0x7f\n\t"
      "pushl %%eax\n\t"
      "movw $0x7f, -0x74(%%ebp)\n\t"
      "call *%[u9cff0]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_000f5900_15\n\t"
      ".LFUN_000f5900_14:\n\t"
      "movl (%%edi), %%ecx\n\t"
      "movl 0x4(%%edi), %%edx\n\t"
      "movl %%ecx, -0x14(%%ebp)\n\t"
      "movl $2, %%eax\n\t"
      "addw %%ax, -0x12(%%ebp)\n\t"
      "movl %%edx, -0x10(%%ebp)\n\t"
      "addw %%ax, -0xe(%%ebp)\n\t"
      "movl $5, %%eax\n\t"
      "addw %%ax, -0x14(%%ebp)\n\t"
      "addw %%ax, -0x10(%%ebp)\n\t"
      "leal -0x74(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "leal -0x14(%%ebp), %%ecx\n\t"
      "pushl $0\n\t"
      "pushl %%ecx\n\t"
      "call *%[rdraw]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000f5900_15:\n\t"
      "movswl 0x46cef8, %%edx\n\t"
      "movswl 0x46cefa, %%eax\n\t"
      "imull $0xb, %%edx, %%edx\n\t"
      "movsbl 0x28a790(%%edx,%%eax,1), %%ecx\n\t"
      "movl -0x4(%%ebp), %%esi\n\t"
      "cmpl %%esi, %%ecx\n\t"
      "jne .LFUN_000f5900_17\n\t"
      "cmpw $4, 0x46cefe\n\t"
      "jne .LFUN_000f5900_16\n\t"
      "movl 0x10(%%ebx), %%eax\n\t"
      "jmp .LFUN_000f5900_18\n\t"
      ".LFUN_000f5900_16:\n\t"
      "movl (%%ebx), %%eax\n\t"
      "jmp .LFUN_000f5900_18\n\t"
      ".LFUN_000f5900_17:\n\t"
      "movl -0x10(%%ebx), %%eax\n\t"
      ".LFUN_000f5900_18:\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_000f5900_19\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "call *%[bmap]\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_000f5900_19\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl $-1\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[drawbmp]\n\t"
      "addl $0x1c, %%esp\n\t"
      ".LFUN_000f5900_19:\n\t"
      "incl %%esi\n\t"
      "addl $8, %%edi\n\t"
      "addl $0x50, %%ebx\n\t"
      "cmpl $0x31e6d0, %%edi\n\t"
      "movl %%esi, -0x4(%%ebp)\n\t"
      "jl .LFUN_000f5900_13\n\t"
      "movl 0x46cef4, %%edx\n\t"
      "cmpl $-1, 0x2c(%%edx)\n\t"
      "je .LFUN_000f5900_32\n\t"
      "cmpl $0x2c, %%esi\n\t"
      "jge .LFUN_000f5900_32\n\t"
      "movl %%esi, %%eax\n\t"
      "leal (%%eax,%%eax,4), %%edx\n\t"
      "leal -0x24(%%eax), %%ecx\n\t"
      "leal 0x31e5b0(,%%eax,8), %%ebx\n\t"
      "movl -0x18(%%ebp), %%eax\n\t"
      "shll $4, %%edx\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "leal 0x3c(%%edx,%%eax,1), %%esi\n\t"
      "movl %%edi, %%edi\n\t"
      ".LFUN_000f5900_20:\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movl 0x46cef4, %%edx\n\t"
      "movl 0x2c(%%edx), %%eax\n\t"
      "addl $-0x24, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "call *%[u9d420]\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "xorl %%edi, %%edi\n\t"
      "cmpl $7, %%eax\n\t"
      "ja .LFUN_000f5900_28\n\t"
      "movl %%eax, %%ecx\n\t"
      "jmp *.LFUN_000f5900_jt(,%%ecx,4)\n\t"
      ".LFUN_000f5900_21:\n\t"
      "movswl 0x46cef8, %%edx\n\t"
      "movswl 0x46cefa, %%eax\n\t"
      "imull $0xb, %%edx, %%edx\n\t"
      "movsbl 0x28a790(%%edx,%%eax,1), %%ecx\n\t"
      "cmpl -0x4(%%ebp), %%ecx\n\t"
      "jne .LFUN_000f5900_23\n\t"
      ".LFUN_000f5900_22:\n\t"
      "cmpw $4, 0x46cefe\n\t"
      "jne .LFUN_000f5900_26\n\t"
      "movl (%%esi), %%eax\n\t"
      "jmp .LFUN_000f5900_27\n\t"
      ".LFUN_000f5900_23:\n\t"
      "movl -0x20(%%esi), %%eax\n\t"
      "jmp .LFUN_000f5900_27\n\t"
      ".LFUN_000f5900_24:\n\t"
      "movswl 0x46cef8, %%edx\n\t"
      "movswl 0x46cefa, %%eax\n\t"
      "imull $0xb, %%edx, %%edx\n\t"
      "movsbl 0x28a790(%%edx,%%eax,1), %%ecx\n\t"
      "cmpl -0x4(%%ebp), %%ecx\n\t"
      "je .LFUN_000f5900_22\n\t"
      "movb 0x46cef1, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000f5900_23\n\t"
      "movl 0x10(%%esi), %%eax\n\t"
      "jmp .LFUN_000f5900_27\n\t"
      ".LFUN_000f5900_25:\n\t"
      "movswl 0x46cef8, %%edx\n\t"
      "movswl 0x46cefa, %%eax\n\t"
      "imull $0xb, %%edx, %%edx\n\t"
      "movsbl 0x28a790(%%edx,%%eax,1), %%ecx\n\t"
      "cmpl -0x4(%%ebp), %%ecx\n\t"
      "je .LFUN_000f5900_22\n\t"
      "movb 0x46cef2, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000f5900_23\n\t"
      "movl 0x10(%%esi), %%eax\n\t"
      "jmp .LFUN_000f5900_27\n\t"
      ".LFUN_000f5900_26:\n\t"
      "movl -0x10(%%esi), %%eax\n\t"
      ".LFUN_000f5900_27:\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_000f5900_29\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "call *%[bmap]\n\t"
      "addl $0xc, %%esp\n\t"
      "movl %%eax, %%edi\n\t"
      "jmp .LFUN_000f5900_29\n\t"
      ".LFUN_000f5900_28:\n\t"
      "pushl $1\n\t"
      "pushl $0x57f\n\t"
      "pushl $0x28a854\n\t"
      "pushl $0x28a9a8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000f5900_29:\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_000f5900_30\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "movl 0x4(%%ebx), %%eax\n\t"
      "movl (%%ebx), %%edx\n\t"
      "pushl %%ecx\n\t"
      "movl %%eax, -0x18(%%ebp)\n\t"
      "pushl $0\n\t"
      "movl %%edx, -0x1c(%%ebp)\n\t"
      "movl $2, %%eax\n\t"
      "addw %%ax, -0x1a(%%ebp)\n\t"
      "addw %%ax, -0x16(%%ebp)\n\t"
      "pushl $0\n\t"
      "movl $5, %%eax\n\t"
      "addw %%ax, -0x1c(%%ebp)\n\t"
      "addw %%ax, -0x18(%%ebp)\n\t"
      "leal -0x1c(%%ebp), %%edx\n\t"
      "pushl $0\n\t"
      "pushl %%edx\n\t"
      "call *%[rdraw]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000f5900_30:\n\t"
      "testl %%edi, %%edi\n\t"
      "je .LFUN_000f5900_31\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl $-1\n\t"
      "pushl $0\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "call *%[drawbmp]\n\t"
      "addl $0x1c, %%esp\n\t"
      ".LFUN_000f5900_31:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movl -0x8(%%ebp), %%edi\n\t"
      "incl %%eax\n\t"
      "incl %%edi\n\t"
      "addl $8, %%ebx\n\t"
      "addl $0x50, %%esi\n\t"
      "cmpl $0x31e710, %%ebx\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "movl %%edi, -0x8(%%ebp)\n\t"
      "jl .LFUN_000f5900_20\n\t"
      ".LFUN_000f5900_32:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_000f5900_jt:\n\t"
      ".long .LFUN_000f5900_21\n\t"
      ".long .LFUN_000f5900_24\n\t"
      ".long .LFUN_000f5900_25\n\t"
      ".long .LFUN_000f5900_31\n\t"
      ".long .LFUN_000f5900_21\n\t"
      ".long .LFUN_000f5900_21\n\t"
      ".long .LFUN_000f5900_21\n\t"
      ".long .LFUN_000f5900_21\n\t"
      ".text\n\t"
      :
      : [assert] "m"(f5900_assert), [exitfn] "m"(f5900_exitfn), [tag] "m"(f5900_tag), [bmap] "m"(f5900_bmap), [drawbmp] "m"(f5900_drawbmp), [dsfont] "m"(f5900_dsfont), [u9d420] "m"(f5900_u9d420), [rdraw] "m"(f5900_rdraw), [u9cdb0] "m"(f5900_u9cdb0), [msys] "m"(f5900_msys), [u9cff0] "m"(f5900_u9cff0), [f5800] "m"(f5900_f5800)
      : "memory");
}
#else
#error "FUN_000f5900: clang naked draft required"
#endif

/* 0xf5f10 — remaining UTF-16 capacity in the item-name edit buffer. */
#if defined(__clang__)
static int (*const object_get_type_ustrlen)(const unsigned short *) = ustrlen;

__attribute__((naked, noinline))
int object_get_type(void)
{
  __asm__ volatile(
      "movl 0x46cf08, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[f]\n\t"
      "leal 2(%%eax,%%eax), %%ecx\n\t"
      "movzwl 0x46cefc, %%eax\n\t"
      "addl $4, %%esp\n\t"
      "subl %%ecx, %%eax\n\t"
      "ret\n\t"
      :
      : [f] "m"(object_get_type_ustrlen)
      : "memory");
}
#else
int object_get_type(void)
{
  int len = ustrlen(*(const unsigned short **)0x46cf08);
  return (int)*(uint16_t *)0x46cefc - (len + len + 2);
}
#endif

/* 0xf5f90 — items TU init alias (XBE: jmp FUN_000f57a0). */
void items_initialize(void)
{
  FUN_000f57a0();
}

/* 0xf5fa0 — flush the item-name keyboard if an edit session is active. */
void items_initialize_for_new_map(void)
{
  if (*(char *)0x46cef0 != 0)
    FUN_000f5900();
}

/* 0xf5fb0 — handle item-name UI keyboard/controller actions (jump table). */
char FUN_000f5fb0(void)
{
  int action;
  wchar_t *buf;

  action = (int)(signed char)*(
      (char *)0x28a790 +
      (int)*(int16_t *)0x46cef8 * 11 + (int)*(int16_t *)0x46cefa);
  action -= 0x24;
  buf = *(wchar_t **)0x46cf08;

  if ((unsigned)action > 7) {
    if (*(char *)0x46cf07 == 1) {
      if (*(uint16_t *)0x46cefc == 0) {
        display_assert((char *)0x0028aa58, (char *)0x0028a854, 0x391, 1);
        system_exit(-1);
      }
      csmemset(buf, 0, *(uint16_t *)0x46cefc);
      *(wchar_t **)0x46cf0c = buf;
      *(char *)0x46cf07 = 0;
    }
    if ((int)*(uint16_t *)0x46cefc -
            (int)ustrlen((unsigned short *)buf) * 2 - 2 >=
        2) {
      ustrlen((unsigned short *)buf);
      FUN_000f5800(0);
      ustrcmp(buf, (wchar_t *)0x0028aa44);
      align_to_character();
      ustrlen((unsigned short *)buf);
      ui_play_audio_feedback_sound(2);
    } else {
      ui_play_audio_feedback_sound(4);
    }
  } else if (action == 0) {
    if (ustrcmp(buf, (wchar_t *)0x46cf18) != 0) {
      if (buf[0] != 0) {
        if (saved_game_file_name_unique() == 0) {
          ui_widget_display_error(0x1b, -1, 1, 0);
          FUN_000f57a0();
        } else {
          *(char *)0x46cf06 = 1;
        }
      } else {
        ui_widget_display_error(0x1d, -1, 1, 0);
        FUN_000f57a0();
      }
    } else {
      *(char *)0x46cf06 = 1;
    }
    ui_play_audio_feedback_sound(3);
    *(char *)0x46cef0 = 0;
    event_manager_flush();
  } else if (action == 1) {
    ui_play_audio_feedback_sound(1);
    *(char *)0x46cef1 = (char)(*(char *)0x46cef1 == 0);
  } else if (action == 2) {
    ui_play_audio_feedback_sound(1);
    *(char *)0x46cef2 = (char)(*(char *)0x46cef2 == 0);
  } else if (action == 3) {
    ui_play_audio_feedback_sound(1);
    *(char *)0x46cef3 = (char)(*(char *)0x46cef3 == 0);
  } else if (action == 4) {
    if (*(char *)0x46cf07 == 1) {
      if (*(uint16_t *)0x46cefc == 0) {
        display_assert((char *)0x0028aa58, (char *)0x0028a854, 0x355, 1);
        system_exit(-1);
      }
      csmemset(buf, 0, *(uint16_t *)0x46cefc);
      *(wchar_t **)0x46cf0c = buf;
      *(char *)0x46cf07 = 0;
    } else {
      FUN_000f5f30();
    }
  } else if (action == 5) {
    if ((uintptr_t)*(void **)0x46cf0c > (uintptr_t)buf)
      *(wchar_t **)0x46cf0c =
          (wchar_t *)((char *)*(void **)0x46cf0c - 2);
    *(char *)0x46cf07 = 0;
    ui_play_audio_feedback_sound(1);
  } else if (action == 6) {
    if (**(wchar_t **)0x46cf0c != 0)
      *(wchar_t **)0x46cf0c = *(wchar_t **)0x46cf0c + 1;
    *(char *)0x46cf07 = 0;
    ui_play_audio_feedback_sound(1);
  } else {
    if (*(char *)0x46cf07 == 1) {
      if (*(uint16_t *)0x46cefc == 0) {
        display_assert((char *)0x0028aa58, (char *)0x0028a854, 0x378, 1);
        system_exit(-1);
      }
      csmemset(buf, 0, *(uint16_t *)0x46cefc);
      *(wchar_t **)0x46cf0c = buf;
      *(char *)0x46cf07 = 0;
    }
    object_get_type();
    if (ustrlen((unsigned short *)buf) >= 2) {
      wchar_t *cursor = *(wchar_t **)0x46cf0c;
      csmemmove(cursor, cursor + 1,
                (unsigned int)((char *)buf + *(uint16_t *)0x46cefc -
                               (char *)(cursor + 1)));
      ui_play_audio_feedback_sound(2);
    } else {
      ui_play_audio_feedback_sound(4);
    }
  }

  if (*((char *)0x28a790 + (int)*(int16_t *)0x46cef8 * 11 +
        (int)*(int16_t *)0x46cefa) != 0x25)
    *(char *)0x46cef1 = 0;
  return 1;
}

/* 0xf6a60 — world position for an item, or its inventory parent's object. */
void item_get_position_even_if_in_inventory(int item_handle, float *out)
{
  char *item;
  int parent_handle;
  char *parent_datum;
  int object_handle;
  char *obj;
  float *pos;

  item = (char *)object_try_and_get_and_verify_type(item_handle, 0x1c);
  out[0] = 0.0f;
  out[1] = 0.0f;
  out[2] = 0.0f;
  if (item == 0)
    return;

  if ((item[0x1a4] & 1) != 0) {
    parent_handle = *(int *)(item + 0x70);
    if (parent_handle == -1)
      return;
    parent_datum = (char *)datum_get(*(data_t **)0x5aa6d4, parent_handle);
    object_handle = *(int *)(parent_datum + 0x34);
    if (object_handle == -1)
      return;
    obj = (char *)object_get_and_verify_type(object_handle, 3);
    pos = (float *)(obj + 0x50);
    out[0] = pos[0];
    out[1] = pos[1];
    out[2] = pos[2];
    return;
  }

  pos = (float *)(item + 0x50);
  out[0] = pos[0];
  out[1] = pos[1];
  out[2] = pos[2];
}

/* 0xf7110 — snap item orientation to a ground hit normal via marker basis. */
void FUN_000f7110(float *opt_position, int item_handle, float *hit_normal,
                  float *out_position)
{
  char *item;
  char marker[0x6c];
  float matrix[12];
  float local_pos[3];
  float basis[3];
  float quat[4];
  float *right;
  float *forward;
  float *position;
  float dot;
  float len;
  float inv;

  item = (char *)object_get_and_verify_type(item_handle, 0x1c);
  if (hit_normal == 0) {
    display_assert((char *)0x0026b188, (char *)0x0028aaa0, 0x2c9, 1);
    system_exit(-1);
  }

  if (object_get_markers_by_string_id(item_handle, (void *)0x0028aa90, marker,
                                      1) == 0)
    return;

  right = (float *)(marker + 0x54);
  forward = (float *)(marker + 0x3c);
  position = (float *)(marker + 0x60);

  if (opt_position == 0)
    opt_position = position;
  if (out_position == 0)
    out_position = local_pos;

  dot = right[0] * hit_normal[0] + right[1] * hit_normal[1] +
        right[2] * hit_normal[2];
  len = sqrtf((dot + 1.0f) + (dot + 1.0f));
  if (len > *(double *)0x26aed0) {
    if (!(len > 0.0f)) {
      display_assert((char *)0x0028aaec, (char *)0x0028aaa0, 0x2dc, 1);
      system_exit(-1);
    }
    /* Build rotation quaternion taking marker-right toward hit normal. */
    quat[0] = right[1] * hit_normal[2] - right[2] * hit_normal[1];
    quat[1] = right[2] * hit_normal[0] - right[0] * hit_normal[2];
    quat[2] = right[0] * hit_normal[1] - right[1] * hit_normal[0];
    inv = 1.0f / len;
    quat[0] *= inv;
    quat[1] *= inv;
    quat[2] *= inv;
    quat[3] = len * 0.5f;
    quaternion_transform_point(quat, forward, basis);
  } else {
    float cx = forward[1] * hit_normal[2] - forward[2] * hit_normal[1];
    float cy = forward[2] * hit_normal[0] - forward[0] * hit_normal[2];
    float cz = forward[0] * hit_normal[1] - forward[1] * hit_normal[0];
    basis[0] = cy * hit_normal[2] - cz * hit_normal[1];
    basis[1] = cz * hit_normal[0] - cx * hit_normal[2];
    basis[2] = cx * hit_normal[1] - cy * hit_normal[0];
  }

  normalize3d(basis);
  matrix4x3_from_forward_up_position(matrix, opt_position, basis, hit_normal);
  if (!valid_real_matrix4x3(matrix)) {
    display_assert((char *)0x0028aac0, (char *)0x0028aaa0, 0x2f3, 1);
    system_exit(-1);
  }

  object_compute_child_marker_position(
      object_get_and_verify_type(item_handle, -1), marker, matrix);
  out_position[0] = *(float *)(item + 0xc);
  out_position[1] = *(float *)(item + 0x10);
  out_position[2] = *(float *)(item + 0x14);
}

/* 0xf7340 — per-tick update for a free (unheld) item. */
#if defined(__clang__)
static float *(*const iupd_vsca)(float *, float *, float, float *) = vector3d_scale_add;
static void (*const iupd_v2fb0)(float *, float, float *) = FUN_00012fb0;
static float (*const iupd_v2fe0)(float *) = FUN_00012fe0;
static float (*const iupd_norm)(float *) = normalize3d;
static bool (*const iupd_v30d0)(unsigned int, float *, float *, int, short *) = FUN_000130d0;
static void (*const iupd_cross)(float *, float *, float *) = cross_product3d;
static void (*const iupd_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const iupd_exitfn)(int) = system_exit;
static void (*const iupd_penter)(void *) = profile_enter_private;
static void (*const iupd_pexit)(void *) = profile_exit_private;
static int (*const iupd_o9ec30)(int, int, int, short, float, float, int, int) = FUN_0009ec30;
static bool (*const iupd_o9f3b0)(void *) = FUN_0009f3b0;
static void (*const iupd_o9f430)(int, short, short, void *, void *, void *, float) = FUN_0009f430;
static bool (*const iupd_gerun)(void) = game_engine_running;
static int (*const iupd_gtime)(void) = game_time_get;
static short (*const iupd_f68b0)(int) = FUN_000f68b0;
static void (*const iupd_f6b80)(int) = FUN_000f6b80;
static void (*const iupd_isetpos)(int, float *, int) = item_set_position;
static void (*const iupd_f7110)(float *, int, float *, float *) = FUN_000f7110;
static void (*const iupd_xfrmpt)(float *, float *, float *) = matrix_transform_point;
static void (*const iupd_m3x3pt)(void *, float *, float *) = real_matrix3x3_transform_point;
static void (*const iupd_rots)(float *, float *, float, float) = rotate_vector3d_by_sincos;
static void *(*const iupd_tryget)(int, int) = object_try_and_get_and_verify_type;
static void *(*const iupd_get)(int, int) = object_get_and_verify_type;
static void (*const iupd_garb)(int, int) = object_set_garbage_flag;
static void (*const iupd_odel)(int) = object_delete;
static void *(*const iupd_onode)(int, short) = object_get_node_matrix;
static short (*const iupd_markers)(int, void *, void *, int) = object_get_markers_by_string_id;
static void (*const iupd_ochild)(void *, void *, void *) = object_compute_child_marker_position;
static void (*const iupd_otrans)(int, float *, void *) = object_translate;
static char (*const iupd_bsext)(short) = breakable_surface_extant;
static char (*const iupd_c4dc30)(int, float *, int) = FUN_0014dc30;
static void *(*const iupd_gbsp)(void) = global_collision_bsp_get;
static short (*const iupd_gbspi)(void) = global_structure_bsp_index_get;
static void *(*const iupd_elem)(void *, int, int) = tag_block_get_element;
static void *(*const iupd_tag)(int, int) = tag_get;
static void (*const iupd_usnd)(int, void *, float) = unattached_impulse_sound_new;

__attribute__((naked, noinline))
void item_update(int item_handle __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xc8, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "pushl $0x1c\n\t"
      "pushl %%edi\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl (%%ebx), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x6974656d\n\t"
      "movl %%ebx, -0x24(%%ebp)\n\t"
      "call *%[tag]\n\t"
      "movl %%eax, %%esi\n\t"
      "movb 0x449ef1, %%al\n\t"
      "addl $0x10, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "movl %%esi, -0x1c(%%ebp)\n\t"
      "je .Litem_update_1\n\t"
      "movb 0x31e718, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Litem_update_1\n\t"
      "pushl $0x31e710\n\t"
      "call *%[penter]\n\t"
      "addl $4, %%esp\n\t"
      ".Litem_update_1:\n\t"
      "cmpw $0x20, 0x4761d8\n\t"
      "jl .Litem_update_2\n\t"
      "pushl $1\n\t"
      "pushl $0xae\n\t"
      "pushl $0x28aaa0\n\t"
      "pushl $0x253440\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Litem_update_2:\n\t"
      "movw 0x4761d8, %%ax\n\t"
      "movswl %%ax, %%ecx\n\t"
      "incw %%ax\n\t"
      "movw $0xb, 0x5a8c80(,%%ecx,2)\n\t"
      "movw %%ax, 0x4761d8\n\t"
      "movl 0x4(%%ebx), %%eax\n\t"
      "testb $8, %%ah\n\t"
      "je .Litem_update_27\n\t"
      "cmpl $-1, 0xcc(%%ebx)\n\t"
      "jne .Litem_update_27\n\t"
      "testb $1, 0x17c(%%esi)\n\t"
      "je .Litem_update_3\n\t"
      "flds 0x38(%%ebx)\n\t"
      "fsubs 0x2533c8\n\t"
      "fabs\n\t"
      "fcompl 0x2533d0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .Litem_update_3\n\t"
      "movl 0x31fc44, %%edx\n\t"
      "movl (%%edx), %%esi\n\t"
      "leal 0x30(%%ebx), %%eax\n\t"
      "movl %%eax, %%ecx\n\t"
      "movl %%esi, (%%ecx)\n\t"
      "movl 0x4(%%edx), %%esi\n\t"
      "movl %%esi, 0x4(%%ecx)\n\t"
      "movl 0x8(%%edx), %%edx\n\t"
      "movl %%edx, 0x8(%%ecx)\n\t"
      "leal -0xc(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal 0x24(%%ebx), %%esi\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "call *%[cross]\n\t"
      "pushl %%esi\n\t"
      "leal 0x30(%%ebx), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0xc(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[cross]\n\t"
      "pushl %%esi\n\t"
      "call *%[norm]\n\t"
      "fcomps 0x2533c0\n\t"
      "addl $0x1c, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .Litem_update_3\n\t"
      "movl 0x31fc3c, %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "movl %%ecx, (%%esi)\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl %%edx, 0x4(%%esi)\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl %%eax, 0x8(%%esi)\n\t"
      ".Litem_update_3:\n\t"
      "testb $0x20, 0x4(%%ebx)\n\t"
      "jne .Litem_update_18\n\t"
      "leal 0x18(%%ebx), %%esi\n\t"
      "movl %%esi, %%ecx\n\t"
      "movl (%%ecx), %%edx\n\t"
      "movl 0x4(%%ecx), %%eax\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "movl %%edx, -0x18(%%ebp)\n\t"
      "movl -0x1c(%%ebp), %%edx\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "testb $4, 0x17c(%%edx)\n\t"
      "movl %%esi, -0x28(%%ebp)\n\t"
      "movl %%ecx, -0x10(%%ebp)\n\t"
      "jne .Litem_update_4\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fsubs 0x32512c\n\t"
      "fstps -0x10(%%ebp)\n\t"
      ".Litem_update_4:\n\t"
      "flds -0x18(%%ebp)\n\t"
      "movl 0x1b0(%%ebx), %%edx\n\t"
      "fadds 0xc(%%ebx)\n\t"
      "leal 0xc(%%ebx), %%eax\n\t"
      "leal -0xac(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "pushl %%edx\n\t"
      "flds -0x14(%%ebp)\n\t"
      "leal -0xc(%%ebp), %%ecx\n\t"
      "fadds 0x10(%%ebx)\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl $0x1ff3e9\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fadds 0x14(%%ebx)\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "call *%[v30d0]\n\t"
      "addl $0x14, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Litem_update_17\n\t"
      "flds -0x88(%%ebp)\n\t"
      "leal -0x18(%%ebp), %%edx\n\t"
      "fmuls 0x2533e8\n\t"
      "pushl %%edx\n\t"
      "fadds -0xc(%%ebp)\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "flds -0x84(%%ebp)\n\t"
      "fmuls 0x2533e8\n\t"
      "fadds -0x8(%%ebp)\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "flds -0x80(%%ebp)\n\t"
      "fmuls 0x2533e8\n\t"
      "fadds -0x4(%%ebp)\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "call *%[v2fe0]\n\t"
      "fdivs 0x28aa80\n\t"
      "addl $4, %%esp\n\t"
      "fsts -0x20(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Litem_update_5\n\t"
      "movl $0, -0x20(%%ebp)\n\t"
      "jmp .Litem_update_6\n\t"
      ".Litem_update_5:\n\t"
      "flds -0x20(%%ebp)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Litem_update_6\n\t"
      "movl $0x3f800000, -0x20(%%ebp)\n\t"
      ".Litem_update_6:\n\t"
      "movl -0x1c(%%ebp), %%eax\n\t"
      "cmpl $-1, 0x254(%%eax)\n\t"
      "je .Litem_update_7\n\t"
      "leal -0x94(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[o9f3b0]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Litem_update_7\n\t"
      "movl -0x20(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0xa0(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl -0x78(%%ebp), %%eax\n\t"
      "leal -0x88(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl -0x1c(%%ebp), %%ecx\n\t"
      "leal -0x94(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl 0x254(%%ecx), %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl $8\n\t"
      "pushl %%edx\n\t"
      "call *%[o9f430]\n\t"
      "addl $0x1c, %%esp\n\t"
      ".Litem_update_7:\n\t"
      "movl -0x1c(%%ebp), %%eax\n\t"
      "movl 0x264(%%eax), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Litem_update_8\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "movl %%ecx, -0x54(%%ebp)\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movl %%edx, -0x50(%%ebp)\n\t"
      "movl -0x88(%%ebp), %%edx\n\t"
      "movl %%ecx, -0x4c(%%ebp)\n\t"
      "movl -0x84(%%ebp), %%ecx\n\t"
      "movl %%edx, -0x48(%%ebp)\n\t"
      "movl -0x80(%%ebp), %%edx\n\t"
      "movl %%ecx, -0x44(%%ebp)\n\t"
      "movl 0x31fc38, %%ecx\n\t"
      "movl %%edx, -0x40(%%ebp)\n\t"
      "movl (%%ecx), %%edx\n\t"
      "movl %%edx, -0x3c(%%ebp)\n\t"
      "movl 0x4(%%ecx), %%edx\n\t"
      "movl %%edx, -0x38(%%ebp)\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "movl 0x48(%%ebx), %%edx\n\t"
      "movl %%ecx, -0x34(%%ebp)\n\t"
      "movl 0x4c(%%ebx), %%ecx\n\t"
      "movl %%edx, -0x30(%%ebp)\n\t"
      "movl -0x20(%%ebp), %%edx\n\t"
      "movl %%ecx, -0x2c(%%ebp)\n\t"
      "pushl %%edx\n\t"
      "leal -0x54(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "call *%[usnd]\n\t"
      "addl $0xc, %%esp\n\t"
      ".Litem_update_8:\n\t"
      "movw -0xac(%%ebp), %%ax\n\t"
      "cmpw $2, %%ax\n\t"
      "je .Litem_update_9\n\t"
      "cmpw $3, %%ax\n\t"
      "jne .Litem_update_14\n\t"
      "movl -0x74(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[f68b0]\n\t"
      "movl $1, %%edx\n\t"
      "addl $4, %%esp\n\t"
      "movl %%eax, %%ecx\n\t"
      "shll %%cl, %%edx\n\t"
      "testl $0x3c0, %%edx\n\t"
      "je .Litem_update_14\n\t"
      ".Litem_update_9:\n\t"
      "flds -0x80(%%ebp)\n\t"
      "fcomps 0x28aaf4\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Litem_update_14\n\t"
      "flds -0x84(%%ebp)\n\t"
      "fmuls -0x14(%%ebp)\n\t"
      "flds -0x88(%%ebp)\n\t"
      "fmuls -0x18(%%ebp)\n\t"
      "faddp %%st(1)\n\t"
      "flds -0x80(%%ebp)\n\t"
      "fmuls -0x10(%%ebp)\n\t"
      "faddp %%st(1)\n\t"
      "fchs\n\t"
      "fcomps 0x2533e8\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Litem_update_14\n\t"
      "movl -0x94(%%ebp), %%eax\n\t"
      "movl -0x90(%%ebp), %%ecx\n\t"
      "movl -0x8c(%%ebp), %%edx\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "leal -0x94(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0xc(%%ebp), %%eax\n\t"
      "leal -0x88(%%ebp), %%esi\n\t"
      "movl %%edi, %%ebx\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      "call *%[f7110]\n\t"
      "flds -0x84(%%ebp)\n\t"
      "movl -0x24(%%ebp), %%esi\n\t"
      "fmuls 0x40(%%esi)\n\t"
      "leal 0x3c(%%esi), %%eax\n\t"
      "flds -0x80(%%ebp)\n\t"
      "addl $4, %%esp\n\t"
      "fmuls 0x8(%%eax)\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "leal -0x88(%%ebp), %%ecx\n\t"
      "faddp %%st(1)\n\t"
      "movl $0, -0x10(%%ebp)\n\t"
      "flds -0x88(%%ebp)\n\t"
      "movl $0, -0x14(%%ebp)\n\t"
      "fmuls (%%eax)\n\t"
      "movl $0, -0x18(%%ebp)\n\t"
      "faddp %%st(1)\n\t"
      "fstps (%%esp)\n\t"
      "pushl %%ecx\n\t"
      "call *%[v2fb0]\n\t"
      "addl $0xc, %%esp\n\t"
      "call *%[gerun]\n\t"
      "testb %%al, %%al\n\t"
      "jne .Litem_update_10\n\t"
      "cmpl $-1, 0x70(%%esi)\n\t"
      "jne .Litem_update_10\n\t"
      "pushl $1\n\t"
      "pushl %%edi\n\t"
      "call *%[garb]\n\t"
      "addl $8, %%esp\n\t"
      ".Litem_update_10:\n\t"
      "movl 0x4(%%esi), %%edx\n\t"
      "movswl -0xac(%%ebp), %%eax\n\t"
      "orl $0x20, %%edx\n\t"
      "subl $2, %%eax\n\t"
      "movl %%edx, 0x4(%%esi)\n\t"
      "je .Litem_update_12\n\t"
      "decl %%eax\n\t"
      "je .Litem_update_11\n\t"
      "pushl $1\n\t"
      "pushl $0x11b\n\t"
      "pushl $0x28aaa0\n\t"
      "pushl $0x255ee8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "jmp .Litem_update_13\n\t"
      ".Litem_update_11:\n\t"
      "orl $0x10, 0x1a4(%%esi)\n\t"
      "movl -0x74(%%ebp), %%eax\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "movl %%eax, 0x1b8(%%esi)\n\t"
      "call *%[onode]\n\t"
      "leal 0x1bc(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x94(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "call *%[m3x3pt]\n\t"
      "addl $0x14, %%esp\n\t"
      "jmp .Litem_update_13\n\t"
      ".Litem_update_12:\n\t"
      "movl 0x1a4(%%esi), %%eax\n\t"
      "movw -0x68(%%ebp), %%dx\n\t"
      "orl $8, %%eax\n\t"
      "movl %%eax, 0x1a4(%%esi)\n\t"
      "movw %%dx, 0x1aa(%%esi)\n\t"
      "call *%[gbspi]\n\t"
      "movw %%ax, 0x1ac(%%esi)\n\t"
      ".Litem_update_13:\n\t"
      "movl -0x88(%%ebp), %%ecx\n\t"
      "movl -0x84(%%ebp), %%edx\n\t"
      "leal 0x1c8(%%esi), %%eax\n\t"
      "movl %%ecx, (%%eax)\n\t"
      "movl -0x80(%%ebp), %%ecx\n\t"
      "movl %%edx, 0x4(%%eax)\n\t"
      "movl %%ecx, 0x8(%%eax)\n\t"
      "movl %%edi, %%eax\n\t"
      "call *%[f6b80]\n\t"
      "movl -0x24(%%ebp), %%ebx\n\t"
      "movl $0xffffffff, 0x1b0(%%esi)\n\t"
      "movl -0x28(%%ebp), %%esi\n\t"
      "jmp .Litem_update_17\n\t"
      ".Litem_update_14:\n\t"
      "cmpw $2, -0xac(%%ebp)\n\t"
      "flds -0x88(%%ebp)\n\t"
      "fmuls -0x18(%%ebp)\n\t"
      "fmuls 0x25686c\n\t"
      "flds -0x84(%%ebp)\n\t"
      "fmuls -0x14(%%ebp)\n\t"
      "fmuls 0x256870\n\t"
      ".byte 0xde, 0xe9\n\t"
      "flds -0x80(%%ebp)\n\t"
      "fmuls -0x10(%%ebp)\n\t"
      "fmuls 0x256870\n\t"
      ".byte 0xde, 0xe9\n\t"
      "je .Litem_update_15\n\t"
      "flds 0x2533ec\n\t"
      "fcomp %%st(1)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .Litem_update_15\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533ec\n\t"
      ".Litem_update_15:\n\t"
      "flds -0x88(%%ebp)\n\t"
      "movl -0x94(%%ebp), %%edx\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "movl -0x90(%%ebp), %%eax\n\t"
      "movl -0x8c(%%ebp), %%ecx\n\t"
      "movl %%edx, -0xc(%%ebp)\n\t"
      "fadds -0x18(%%ebp)\n\t"
      "pushl %%edi\n\t"
      "leal -0xc(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "pushl $0x1ff3e9\n\t"
      "flds -0x84(%%ebp)\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "movl %%ecx, -0x4(%%ebp)\n\t"
      "fadds -0x14(%%ebp)\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "fmuls -0x80(%%ebp)\n\t"
      "fadds -0x10(%%ebp)\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "call *%[c4dc30]\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Litem_update_16\n\t"
      "leal -0xc(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x3d4ccccd\n\t"
      "leal -0x88(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x94(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[vsca]\n\t"
      "addl $0x10, %%esp\n\t"
      ".Litem_update_16:\n\t"
      "pushl %%edi\n\t"
      "leal -0xc(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x1ff3e9\n\t"
      "call *%[c4dc30]\n\t"
      "addl $0xc, %%esp\n\t"
      ".Litem_update_17:\n\t"
      "movl -0x18(%%ebp), %%ecx\n\t"
      "movl -0x14(%%ebp), %%edx\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "movl %%ecx, (%%esi)\n\t"
      "movl %%edx, 0x4(%%esi)\n\t"
      "leal -0xa0(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0xc(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "movl %%eax, 0x8(%%esi)\n\t"
      "call *%[otrans]\n\t"
      "addl $0xc, %%esp\n\t"
      "jmp .Litem_update_24\n\t"
      ".Litem_update_18:\n\t"
      "movl -0x1c(%%ebp), %%eax\n\t"
      "testb $4, 0x17c(%%eax)\n\t"
      "jne .Litem_update_24\n\t"
      "pushl $1\n\t"
      "leal -0xc8(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x28aa90\n\t"
      "pushl %%edi\n\t"
      "call *%[markers]\n\t"
      "movb 0x1a4(%%ebx), %%al\n\t"
      "addl $0x10, %%esp\n\t"
      "testb $8, %%al\n\t"
      "je .Litem_update_19\n\t"
      "orl $0xffffffff, %%esi\n\t"
      "cmpw %%si, 0x1aa(%%ebx)\n\t"
      "je .Litem_update_19\n\t"
      "call *%[gbspi]\n\t"
      "cmpw %%ax, 0x1ac(%%ebx)\n\t"
      "jne .Litem_update_19\n\t"
      "call *%[gbsp]\n\t"
      "movswl 0x1aa(%%ebx), %%edx\n\t"
      "pushl $0xc\n\t"
      "pushl %%edx\n\t"
      "addl $0x3c, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movb 0x8(%%eax), %%cl\n\t"
      "addl $0xc, %%esp\n\t"
      "testb $8, %%cl\n\t"
      "je .Litem_update_23\n\t"
      "movzbw 0x9(%%eax), %%ax\n\t"
      "pushl %%eax\n\t"
      "call *%[bsext]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Litem_update_23\n\t"
      "movl 0x32512c, %%edx\n\t"
      "movl 0x31fc50, %%eax\n\t"
      "leal -0xc(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[v2fb0]\n\t"
      "movl 0x1a4(%%ebx), %%eax\n\t"
      "andl $0xfffffff7, %%eax\n\t"
      "movw %%si, 0x1aa(%%ebx)\n\t"
      "jmp .Litem_update_21\n\t"
      ".Litem_update_19:\n\t"
      "testb $0x10, 0x1a4(%%ebx)\n\t"
      "je .Litem_update_23\n\t"
      "movl 0x1b8(%%ebx), %%edx\n\t"
      "pushl $-1\n\t"
      "pushl %%edx\n\t"
      "call *%[tryget]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Litem_update_20\n\t"
      "movl 0x1b8(%%ebx), %%eax\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "call *%[onode]\n\t"
      "leal -0xc(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal 0x1bc(%%ebx), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[xfrmpt]\n\t"
      "leal -0xc(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal 0x1c8(%%ebx), %%esi\n\t"
      "xorl %%eax, %%eax\n\t"
      "movl %%edi, %%ebx\n\t"
      "call *%[f7110]\n\t"
      "movl -0x24(%%ebp), %%ebx\n\t"
      "jmp .Litem_update_22\n\t"
      ".Litem_update_20:\n\t"
      "movl 0x32512c, %%edx\n\t"
      "movl 0x31fc50, %%eax\n\t"
      "leal -0xc(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[v2fb0]\n\t"
      "movl 0x1a4(%%ebx), %%eax\n\t"
      "andl $0xffffffef, %%eax\n\t"
      ".Litem_update_21:\n\t"
      "leal -0xc(%%ebp), %%ecx\n\t"
      "pushl $0\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edi\n\t"
      "movl %%eax, 0x1a4(%%ebx)\n\t"
      "call *%[isetpos]\n\t"
      ".Litem_update_22:\n\t"
      "addl $0x18, %%esp\n\t"
      ".Litem_update_23:\n\t"
      "flds 0x3c(%%ebx)\n\t"
      "movl %%edi, %%eax\n\t"
      "fmuls 0x2555d0\n\t"
      "fstps 0x3c(%%ebx)\n\t"
      "flds 0x40(%%ebx)\n\t"
      "fmuls 0x2555d0\n\t"
      "fstps 0x40(%%ebx)\n\t"
      "flds 0x44(%%ebx)\n\t"
      "fmuls 0x2555d0\n\t"
      "fstps 0x44(%%ebx)\n\t"
      "call *%[f6b80]\n\t"
      ".Litem_update_24:\n\t"
      "testb $4, 0x1a4(%%ebx)\n\t"
      "je .Litem_update_27\n\t"
      "testb $0x20, 0x4(%%ebx)\n\t"
      "je .Litem_update_25\n\t"
      "pushl $1\n\t"
      "leal -0xc8(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x28aa90\n\t"
      "pushl %%edi\n\t"
      "call *%[markers]\n\t"
      "addl $0x10, %%esp\n\t"
      "testw %%ax, %%ax\n\t"
      "je .Litem_update_25\n\t"
      "movl 0x1d8(%%ebx), %%eax\n\t"
      "movl $0xd, %%ecx\n\t"
      "leal -0x90(%%ebp), %%esi\n\t"
      "leal -0x5c(%%ebp), %%edi\n\t"
      "rep movsl\n\t"
      "movl 0x1d4(%%ebx), %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "leal 0x1c8(%%ebx), %%esi\n\t"
      "leal -0x58(%%ebp), %%edx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edx\n\t"
      "call *%[rots]\n\t"
      "movl 0x1d8(%%ebx), %%eax\n\t"
      "movl 0x1d4(%%ebx), %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "leal -0x40(%%ebp), %%edx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edx\n\t"
      "call *%[rots]\n\t"
      "leal -0x4c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x58(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x40(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[cross]\n\t"
      "leal -0x58(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x40(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x4c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[cross]\n\t"
      "leal -0x58(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[norm]\n\t"
      "fstp %%st(0)\n\t"
      "leal -0x4c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[norm]\n\t"
      "fstp %%st(0)\n\t"
      "leal -0x40(%%ebp), %%edx\n\t"
      "addl $0x40, %%esp\n\t"
      "pushl %%edx\n\t"
      "call *%[norm]\n\t"
      "fstp %%st(0)\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "addl $4, %%esp\n\t"
      "leal -0x5c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0xc8(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $-1\n\t"
      "pushl %%edx\n\t"
      "call *%[get]\n\t"
      "addl $8, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[ochild]\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "addl $0xc, %%esp\n\t"
      "jmp .Litem_update_26\n\t"
      ".Litem_update_25:\n\t"
      "movl 0x1d8(%%ebx), %%eax\n\t"
      "movl 0x1d4(%%ebx), %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "leal 0x1c8(%%ebx), %%esi\n\t"
      "leal 0x24(%%ebx), %%edx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edx\n\t"
      "call *%[rots]\n\t"
      "movl 0x1d8(%%ebx), %%eax\n\t"
      "movl 0x1d4(%%ebx), %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "leal 0x30(%%ebx), %%edx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edx\n\t"
      "call *%[rots]\n\t"
      "addl $0x20, %%esp\n\t"
      ".Litem_update_26:\n\t"
      "leal 0x30(%%ebx), %%esi\n\t"
      "pushl %%esi\n\t"
      "call *%[norm]\n\t"
      "fstp %%st(0)\n\t"
      "leal -0xc(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal 0x24(%%ebx), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[cross]\n\t"
      "leal 0x24(%%ebx), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0xc(%%ebp), %%edx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edx\n\t"
      "call *%[cross]\n\t"
      "leal 0x24(%%ebx), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[norm]\n\t"
      "fstp %%st(0)\n\t"
      "addl $0x20, %%esp\n\t"
      ".Litem_update_27:\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x1a8(%%ebx), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "jle .Litem_update_28\n\t"
      "decl %%eax\n\t"
      "testw %%ax, %%ax\n\t"
      "movw %%ax, 0x1a8(%%ebx)\n\t"
      "jne .Litem_update_28\n\t"
      "movl -0x1c(%%ebp), %%eax\n\t"
      "movl 0x304(%%eax), %%ecx\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl $-1\n\t"
      "pushl %%edi\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "call *%[o9ec30]\n\t"
      "pushl %%edi\n\t"
      "call *%[odel]\n\t"
      "addl $0x24, %%esp\n\t"
      ".Litem_update_28:\n\t"
      "testb $1, 0x1a4(%%ebx)\n\t"
      "je .Litem_update_29\n\t"
      "call *%[gtime]\n\t"
      "movl %%eax, 0x1b4(%%ebx)\n\t"
      ".Litem_update_29:\n\t"
      "cmpw $1, 0x4761d8\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "jg .Litem_update_30\n\t"
      "pushl $1\n\t"
      "pushl $0x1d4\n\t"
      "pushl $0x28aaa0\n\t"
      "pushl $0x253418\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Litem_update_30:\n\t"
      "movb 0x449ef1, %%al\n\t"
      "decw 0x4761d8\n\t"
      "testb %%al, %%al\n\t"
      "je .Litem_update_31\n\t"
      "movb 0x31e718, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Litem_update_31\n\t"
      "pushl $0x31e710\n\t"
      "call *%[pexit]\n\t"
      "addl $4, %%esp\n\t"
      ".Litem_update_31:\n\t"
      "movb $1, %%al\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "ret\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "ret\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "ret\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "ret\n\t"
      :
      : [vsca] "m"(iupd_vsca), [v2fb0] "m"(iupd_v2fb0), [v2fe0] "m"(iupd_v2fe0), [norm] "m"(iupd_norm), [v30d0] "m"(iupd_v30d0), [cross] "m"(iupd_cross), [assert] "m"(iupd_assert), [exitfn] "m"(iupd_exitfn), [penter] "m"(iupd_penter), [pexit] "m"(iupd_pexit), [o9ec30] "m"(iupd_o9ec30), [o9f3b0] "m"(iupd_o9f3b0), [o9f430] "m"(iupd_o9f430), [gerun] "m"(iupd_gerun), [gtime] "m"(iupd_gtime), [f68b0] "m"(iupd_f68b0), [f6b80] "m"(iupd_f6b80), [isetpos] "m"(iupd_isetpos), [f7110] "m"(iupd_f7110), [xfrmpt] "m"(iupd_xfrmpt), [m3x3pt] "m"(iupd_m3x3pt), [rots] "m"(iupd_rots), [tryget] "m"(iupd_tryget), [get] "m"(iupd_get), [garb] "m"(iupd_garb), [odel] "m"(iupd_odel), [onode] "m"(iupd_onode), [markers] "m"(iupd_markers), [ochild] "m"(iupd_ochild), [otrans] "m"(iupd_otrans), [bsext] "m"(iupd_bsext), [c4dc30] "m"(iupd_c4dc30), [gbsp] "m"(iupd_gbsp), [gbspi] "m"(iupd_gbspi), [elem] "m"(iupd_elem), [tag] "m"(iupd_tag), [usnd] "m"(iupd_usnd)
      : "memory");
}
#else
void item_update(int item_handle)
{
  char *item;
  char *item_tag;
  float *up;
  float *forward;
  float right[3];
  float start[3];
  float end[3];
  float hit_normal[3];
  float ground_t;
  int16_t collision[0x60];
  int16_t depth;
  char in_air;

  item = (char *)object_get_and_verify_type(item_handle, 0x1c);
  item_tag = (char *)tag_get(0x6974656d, *(int *)item); /* 'item' */

  if (*(char *)0x449ef1 != 0 && *(char *)0x31e718 != 0)
    profile_enter_private((void *)0x0031e710);

  if (*(int16_t *)0x4761d8 >= 0x20) {
    display_assert((char *)0x00253440, (char *)0x0028aaa0, 0xae, 1);
    system_exit(-1);
  }
  depth = *(int16_t *)0x4761d8;
  *(int16_t *)0x4761d8 = (int16_t)(depth + 1);
  *(int16_t *)(0x5a8c80 + (int)depth * 2) = 0xb;

  /* Only simulate when on-ground bit clear in flags and no parent. */
  if ((*(unsigned int *)(item + 4) & 0x800) == 0 ||
      *(int *)(item + 0xcc) != -1) {
    *(int16_t *)0x4761d8 = (int16_t)(*(int16_t *)0x4761d8 - 1);
    return;
  }

  /* Optional upright snap when item definition requests it. */
  if ((*(unsigned char *)(item_tag + 0x17c) & 1) != 0) {
    float tilt = fabsf(*(float *)(item + 0x38) - 1.0f);
    if (!(tilt < *(double *)0x2533d0)) {
      up = *(float **)0x31fc44;
      *(float *)(item + 0x30) = up[0];
      *(float *)(item + 0x34) = up[1];
      *(float *)(item + 0x38) = up[2];
      /* right = up × forward; forward = right × up (re-orthonormalize). */
      cross_product3d((float *)(item + 0x30), (float *)(item + 0x24), right);
      cross_product3d(right, (float *)(item + 0x30), (float *)(item + 0x24));
      if (normalize3d((float *)(item + 0x24)) == 0.0f) {
        forward = *(float **)0x31fc3c;
        *(float *)(item + 0x24) = forward[0];
        *(float *)(item + 0x28) = forward[1];
        *(float *)(item + 0x2c) = forward[2];
      }
    }
  }

  in_air = (char)((*(unsigned char *)(item + 4) & 0x20) != 0);
  if (in_air == 0) {
    float vel[3];
    vel[0] = *(float *)(item + 0x18);
    vel[1] = *(float *)(item + 0x1c);
    vel[2] = *(float *)(item + 0x20);
    if ((*(unsigned char *)(item_tag + 0x17c) & 4) == 0)
      vel[2] -= *(float *)0x32512c;

    start[0] = *(float *)(item + 0xc);
    start[1] = *(float *)(item + 0x10);
    start[2] = *(float *)(item + 0x14);
    end[0] = start[0] + vel[0];
    end[1] = start[1] + vel[1];
    end[2] = start[2] + vel[2];

    if (FUN_000130d0(0x1ff3e9, start, end, *(int *)(item + 0x1b0),
                     collision)) {
      hit_normal[0] = *(float *)((char *)collision + 0x24);
      hit_normal[1] = *(float *)((char *)collision + 0x28);
      hit_normal[2] = *(float *)((char *)collision + 0x2c);
      end[0] += hit_normal[0] * *(float *)0x2533e8;
      end[1] += hit_normal[1] * *(float *)0x2533e8;
      end[2] += hit_normal[2] * *(float *)0x2533e8;
      ground_t = FUN_00012fe0(vel) / *(float *)0x28aa80;
      if (ground_t < 0.0f)
        ground_t = 0.0f;
      else if (ground_t > 1.0f)
        ground_t = 1.0f;

      if (*(int *)(item_tag + 0x254) != -1) {
        char material_buf[0x10];
        if (FUN_0009f3b0(material_buf))
          FUN_0009f430(*(int *)(item_tag + 0x254), 8, 0, material_buf,
                       hit_normal, (void *)(item_tag + 0x78), ground_t);
      }
      if (*(int *)(item_tag + 0x264) != -1) {
        float sound_loc[12];
        sound_loc[0] = end[0];
        sound_loc[1] = end[1];
        sound_loc[2] = end[2];
        sound_loc[3] = hit_normal[0];
        sound_loc[4] = hit_normal[1];
        sound_loc[5] = hit_normal[2];
        {
          float *gv = *(float **)0x31fc38;
          sound_loc[6] = gv[0];
          sound_loc[7] = gv[1];
          sound_loc[8] = gv[2];
        }
        sound_loc[9] = *(float *)(item + 0x48);
        sound_loc[10] = *(float *)(item + 0x4c);
        unattached_impulse_sound_new(*(int *)(item_tag + 0x264), sound_loc,
                                     ground_t);
      }

      {
        int16_t surface = collision[0];
        if (surface == 2 ||
            (surface == 3 &&
             ((1 << (int)FUN_000f68b0(item_handle)) & 0x3c0) != 0)) {
          if (hit_normal[2] > *(float *)0x28aaf4) {
            float into = -(hit_normal[0] * vel[0] + hit_normal[1] * vel[1] +
                           hit_normal[2] * vel[2]);
            if (into > *(float *)0x2533e8) {
              FUN_000f7110(0, item_handle, hit_normal, 0);
              FUN_00012fb0(hit_normal, into, vel);
              if (!game_engine_running() && *(int *)(item_tag + 0x70) == -1)
                object_set_garbage_flag(item_handle, 1);
              *(unsigned int *)(item + 4) |= 0x20;
              *(float *)(item + 0x1c8) = hit_normal[0];
              *(float *)(item + 0x1cc) = hit_normal[1];
              *(float *)(item + 0x1d0) = hit_normal[2];
              FUN_000f6b80(item_handle);
              *(int *)(item + 0x1b0) = -1;
            }
          }
        } else {
          float slide = hit_normal[0] * vel[0] * *(float *)0x25686c -
                        hit_normal[1] * vel[1] * *(float *)0x256870 -
                        hit_normal[2] * vel[2] * *(float *)0x256870;
          if (surface != 2 && slide < *(float *)0x2533ec)
            slide = *(float *)0x2533ec;
          vel[0] += hit_normal[0] * slide;
          vel[1] += hit_normal[1] * slide;
          vel[2] += hit_normal[2] * slide;
          FUN_0014dc30(0x1ff3e9, (float *)((char *)collision + 0x18),
                       item_handle);
        }
      }

      *(float *)(item + 0x18) = vel[0];
      *(float *)(item + 0x1c) = vel[1];
      *(float *)(item + 0x20) = vel[2];
      object_translate(item_handle, end, (void *)((char *)collision + 0xc));
    } else {
      *(float *)(item + 0x18) = vel[0];
      *(float *)(item + 0x1c) = vel[1];
      *(float *)(item + 0x20) = vel[2];
      object_translate(item_handle, end, 0);
    }
  } else if ((*(unsigned char *)(item_tag + 0x17c) & 4) == 0) {
    char marker_buf[0xd0];
    object_get_markers_by_string_id(item_handle, (void *)0x0028aa90, marker_buf,
                                    1);
    if ((*(unsigned int *)(item + 0x1a4) & 8) != 0 &&
        *(int16_t *)(item + 0x1aa) != (int16_t)-1) {
      if (*(int16_t *)(item + 0x1ac) == global_structure_bsp_index_get()) {
        float drop[3];
        FUN_00012fb0(*(float **)0x31fc50, *(float *)0x32512c, drop);
        *(unsigned int *)(item + 0x1a4) &= ~8u;
        *(int16_t *)(item + 0x1aa) = -1;
        *(float *)(item + 0x18) += drop[0];
        *(float *)(item + 0x1c) += drop[1];
        *(float *)(item + 0x20) += drop[2];
      }
    }
  }

  *(int16_t *)0x4761d8 = (int16_t)(*(int16_t *)0x4761d8 - 1);
}
#endif

