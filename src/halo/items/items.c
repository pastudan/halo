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

/* item_set_position (0xf6d60)
 *
 * Apply a velocity/position delta to an item and update its angular velocity.
 * Manages collision user depth, ground clamping, angular tumble, and garbage
 * flag state. Called each tick to move free-floating items (grenades, weapons,
 * equipment on the ground).
 *
 * If the item is grounded (flag bit 3 at +0x1a4) and the delta magnitude is
 * above a small epsilon, the item is repositioned to just above the ground
 * plane via a "ground point" marker lookup and plane projection. Otherwise
 * position is simply accumulated. Angular velocity gets a tumble impulse from
 * cross(global_up, delta) scaled by a random factor and pi/2, or a random
 * angular jolt from the ground normal when velocity is near zero.
 *
 * Confirmed: 3 cdecl args (item_handle, position, flag).
 * Confirmed: CALL 0x13d680 (object_get_and_verify_type) with type_mask 0x1c.
 * Confirmed: CALL 0x1ba140 (tag_get) with 'item' (0x6974656d).
 * Confirmed: CALL 0x8d9f0 (display_assert) for collision depth checks.
 * Confirmed: CALL 0xa8e30 (game_engine_running) for flag-dependent branch.
 * Confirmed: CALL 0xf6af0 (item_detonate) if flag set and engine not running.
 * Confirmed: CALL 0x140f10 (object_get_markers_by_string_id) for "ground
 * point". Confirmed: CALL 0x18e3f0 (global_collision_bsp_get) to get collision
 * BSP. Confirmed: CALL 0x19b210 (tag_block_get_element) at bsp+0x3c. Confirmed:
 * CALL 0x99640 (bsp3d_get_plane_from_designator) for plane extraction.
 * Confirmed: CALL 0x12f80 (vector3d_scale_add) for ground projection.
 * Confirmed: CALL 0x143be0 (object_translate) for repositioning item.
 * Confirmed: CALL 0x12170 (FUN_00012170) for vector magnitude. Confirmed: CALL
 * 0x10b0d0 (get_global_random_seed_address). Confirmed: CALL 0x10b240
 * (random_math_real) for random scale. Confirmed: CALL 0x13010 (normalize3d)
 * for cross product normalization. Confirmed: CALL 0x10b380
 * (random_seed_get_direction3d) for degenerate case. Confirmed: CALL 0x121e0
 * (FUN_000121e0) for random angle
 * [-pi/4, pi/4]. Confirmed: CALL 0x213c0 (vector3d_add) for angular velocity
 * accumulation. Confirmed: CALL 0xf6b80 (FUN_000f6b80) with item_handle in EAX.
 * Confirmed: CALL 0x13d920 (object_set_garbage_flag) with (handle, 0).
 * Confirmed: global collision depth at 0x4761d8 (int16_t).
 * Confirmed: collision user stack at 0x5a8c80.
 * Confirmed: global up vector pointer at 0x31fc44 → {0, 0, 1}.
 * Confirmed: epsilon constant at 0x253f44 = ~0.0001f.
 * Confirmed: offset constant at 0x2533e8 = 0.05f.
 * Confirmed: zero constant at 0x2533c0 = 0.0f.
 * Confirmed: pi/2 constant at 0x2568bc = ~1.5708f.
 */
void item_set_position(int item_handle, float *position, int flag)
{
  char *item_obj;
  char *item_tag;
  int16_t marker_count;
  char marker_buf[0x6c];
  float plane[4];
  float cross[3];
  float vel_mag;
  float new_pos[3];
  float scaled_dir[3];
  float *up;
  float scale;
  int bsp;
  int *plane_ref;
  float dot;

  item_obj = (char *)object_get_and_verify_type(item_handle, 0x1c);
  item_tag = (char *)tag_get(0x6974656d, *(int *)item_obj);

  /* Early out if item has flag bit 5 set at +0x1a4 */
  if (*(uint8_t *)(item_obj + 0x1a4) & 0x20)
    return;

  /* Collision depth guard */
  if (*(int16_t *)0x4761d8 >= 0x20) {
    display_assert("global_current_collision_user_depth < "
                   "MAXIMUM_COLLISION_USER_STACK_DEPTH",
                   "c:\\halo\\SOURCE\\items\\items.c", 0x218, 1);
    system_exit(-1);
  }

  {
    int16_t depth = *(int16_t *)0x4761d8;
    *(int16_t *)(0x5a8c80 + (int)depth * 2) = 0xb;
    *(int16_t *)0x4761d8 = depth + 1;
  }

  /* Only process if parent object handle (obj+0xCC) is NONE */
  if (*(int *)(item_obj + 0xcc) == NONE) {
    /* If flag param is set, game engine not running, and tag flag bit 1 set,
     * call item_detonate (possibly spawns pickup effect or similar) */
    if ((char)flag != 0) {
      if (!game_engine_running()) {
        if (*(uint8_t *)(item_tag + 0x17c) & 2) {
          item_detonate(item_handle);
        }
      }
    }

    /* Check ground flag (bit 3 of item_flags at +0x1a4) */
    if (!(*(uint8_t *)(item_obj + 0x1a4) & 0x8)) {
      /* Not grounded: just clear the "needs update" flag bit 5 at +0x04 */
      *(uint32_t *)(item_obj + 0x04) =
        *(uint32_t *)(item_obj + 0x04) & 0xffffffdf;
    } else if (*(float *)0x253f44 <= position[0] * position[0] +
                                       position[1] * position[1] +
                                       position[2] * position[2]) {
      /* Grounded and velocity magnitude squared >= epsilon:
       * Try to reposition item to ground plane */
      marker_count = object_get_markers_by_string_id(
        item_handle, (void *)0x28aa90, marker_buf, 1);
      if (marker_count != 0) {
        /* Ground point marker found: project position onto ground plane */
        bsp = (int)global_collision_bsp_get();
        plane_ref = (int *)tag_block_get_element(
          (void *)(bsp + 0x3c), (int)*(int16_t *)(item_obj + 0x1aa), 0xc);
        bsp3d_get_plane_from_designator(bsp, *plane_ref, plane);

        /* Compute offset from plane: 0.05 - (dot(normal, ground_pos) -
         * distance) */
        dot = plane[0] * *(float *)(marker_buf + 0x60) +
              plane[1] * *(float *)(marker_buf + 0x64) +
              plane[2] * *(float *)(marker_buf + 0x68);
        scale = *(float *)0x2533e8 - (dot - plane[3]);

        vector3d_scale_add((float *)(marker_buf + 0x60), plane, scale, new_pos);
        object_translate(item_handle, new_pos, 0);
      }
      /* Clear "needs update" bit 5 at +0x04 and ground bit 3 at +0x1a4 */
      *(uint32_t *)(item_obj + 0x04) =
        *(uint32_t *)(item_obj + 0x04) & 0xffffffdf;
      *(uint32_t *)(item_obj + 0x1a4) =
        *(uint32_t *)(item_obj + 0x1a4) & 0xfffffff7;
    }

    /* Accumulate position delta onto object position at +0x18 */
    *(float *)(item_obj + 0x18) += position[0];
    *(float *)(item_obj + 0x1c) += position[1];
    *(float *)(item_obj + 0x20) += position[2];

    /* Determine angular velocity update path */
    if (*(int *)(item_obj + 0x1b0) != NONE ||
        !(*(uint8_t *)(item_obj + 0x1a4) & 0x8) ||
        *(float *)0x253f44 <= FUN_00012170(position)) {
      /* Normal tumble: compute angular velocity from cross product */
      vel_mag = sqrtf(position[0] * position[0] + position[1] * position[1] +
                      position[2] * position[2]);
      if (vel_mag < *(float *)0x253f44) {
        unsigned int *seed = (unsigned int *)get_global_random_seed_address();
        vel_mag = random_math_real(seed);
      }

      /* cross = cross(global_up, position_delta) */
      up = *(float **)0x31fc44;
      cross[2] = up[0] * position[1] - up[1] * position[0];
      cross[1] = position[0] * up[2] - up[0] * position[2];
      cross[0] = up[1] * position[2] - position[1] * up[2];

      if (normalize3d(cross) <= *(float *)0x2533c0) {
        /* Degenerate cross product: use random direction */
        unsigned int *seed = (unsigned int *)get_global_random_seed_address();
        random_seed_get_direction3d(seed, cross);
      }

      {
        unsigned int *seed = (unsigned int *)get_global_random_seed_address();
        float factor = random_math_real(seed) * vel_mag * *(float *)0x2568bc;
        *(float *)(item_obj + 0x3c) += cross[0] * factor;
        *(float *)(item_obj + 0x40) += cross[1] * factor;
        *(float *)(item_obj + 0x44) += cross[2] * factor;
      }
    } else {
      /* Slow/grounded path: apply random angular jolt from ground normal */
      marker_count = object_get_markers_by_string_id(
        item_handle, (void *)0x28aa90, marker_buf, 1);
      if (marker_count == 0) {
        /* No marker: use global up vector as normal */
        up = *(float **)0x31fc44;
        cross[0] = up[0];
        cross[1] = up[1];
        cross[2] = up[2];
      } else {
        /* Use ground point marker normal (at marker+0x54) */
        cross[0] = *(float *)(marker_buf + 0x54);
        cross[1] = *(float *)(marker_buf + 0x58);
        cross[2] = *(float *)(marker_buf + 0x5c);
      }

      /* Random angle in [-pi/4, pi/4] */
      scale = FUN_000121e0(-1.5707963f, 1.5707963f);
      scaled_dir[0] = cross[0] * scale;
      scaled_dir[1] = cross[1] * scale;
      scaled_dir[2] = cross[2] * scale;

      /* angular_velocity += scaled_dir */
      vector3d_add(
        (float *)(item_obj + 0x3c), scaled_dir,
        (float *)(item_obj + 0x3c)); /* dup-args-ok: in-place accumulation */
    }

    /* Update item velocity/angular state and clear garbage flag */
    FUN_000f6b80(item_handle);
    object_set_garbage_flag(item_handle, 0);
  }

  /* Collision depth unguard */
  if (*(int16_t *)0x4761d8 < 2) {
    display_assert("global_current_collision_user_depth > 1",
                   "c:\\halo\\SOURCE\\items\\items.c", 0x28b, 1);
    system_exit(-1);
  }
  *(int16_t *)0x4761d8 = *(int16_t *)0x4761d8 - 1;
}
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

/* 0xf4cf0 — sync multiplayer item UI child text-box indices from parent widget. */
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

/* 0xf5900 — draw the item/profile name UI (font, bitmap, editable string). */
void FUN_000f5900(void)
{
  char *ui_globals;
  char *font_tag;
  float color_white[4];
  float color_grey[4];
  int16_t rect[4];
  int16_t tmp_rect[4];
  void *bitmap;
  wchar_t *text;
  wchar_t *cursor;
  int slot;
  char *bitm_base;
  int16_t *screen_slot;
  unsigned short glyph;
  void *glyph_info;
  unsigned int millis;

  color_white[0] = color_white[1] = color_white[2] = color_white[3] = 1.0f;
  color_grey[0] = color_grey[1] = color_grey[2] = color_grey[3] = 0.9f;

  ui_globals = *(char **)0x46cef4;
  if (ui_globals == 0 || *(int *)(ui_globals + 0xc) == -1) {
    display_assert((char *)0x0028a9d8, (char *)0x0028a854, 0x40b, 1);
    system_exit(-1);
    ui_globals = *(char **)0x46cef4;
  }

  font_tag = (char *)tag_get(0x666f6e74, *(int *)(ui_globals + 0xc));
  if (font_tag == 0) {
    display_assert((char *)0x0028a9c0, (char *)0x0028a854, 0x40d, 1);
    system_exit(-1);
  }

  if (*(int *)(ui_globals + 0x1c) != -1) {
    rect[0] = 0;
    rect[1] = 0;
    rect[2] = 0x1e0;
    rect[3] = 0x280;
    bitmap = FUN_00077040(*(int *)(ui_globals + 0x1c), 0, 0);
    if (bitmap == 0) {
      display_assert((char *)0x00263768, (char *)0x0028a854, 0x415, 1);
      system_exit(-1);
    }
    draw_bitmap_in_rect((int)(uintptr_t)bitmap, rect, rect, 0, 0, 0, -1);
  }

  draw_string_set_font(*(int *)(ui_globals + 0xc), -1, 0, 0, color_grey);

  if (*(int *)(ui_globals + 0x2c) != -1) {
    rect[0] = 0x4e;
    rect[1] = 0x72;
    rect[2] = 0x6e;
    rect[3] = 0x280;
    rasterizer_draw_string(
        (void *)rect, rect, 0, 0,
        (unsigned short *)FUN_0019d420(*(int *)(ui_globals + 0x2c),
                                       (int)*(uint16_t *)0x46cf04));
  }

  draw_string_set_font(*(int *)(ui_globals + 0xc), -1, 2, 0, color_white);

  rect[0] = 0x76;
  rect[1] = 0xdc;
  rect[2] = 0x8f;
  rect[3] = 0x1a4;

  if (*(char *)0x46cf07 == 1) {
    bitmap = FUN_00077040(*(int *)0x46cf14, 0, 0);
    if (bitmap != 0) {
      FUN_0019cdb0(rect, *(void **)0x46cf08, tmp_rect, rect);
      tmp_rect[1] = (int16_t)(tmp_rect[1] - 2);
      tmp_rect[3] = (int16_t)(tmp_rect[3] + 2);
      draw_bitmap_in_rect((int)(uintptr_t)bitmap, tmp_rect, rect, 0, 0, 0,
                          0x7f7f7f7f);
    }
  }

  rasterizer_draw_string((void *)rect, rect, 0, 0, *(unsigned short **)0x46cf08);

  if (*(char *)0x46cf07 == 0 && *(int *)0x46cf14 != -1) {
    millis = system_milliseconds();
    if ((((millis * (unsigned)0x10624dd3) >> 6) & 1) != 0) {
      int width = 0;
      int half = 0;
      int line_h =
          (int)*(uint16_t *)(font_tag + 4) + (int)*(uint16_t *)(font_tag + 6);
      text = *(wchar_t **)0x46cf08;
      cursor = *(wchar_t **)0x46cf0c;
      bitmap = FUN_00077040(*(int *)0x46cf14, 0, 0);
      if (bitmap != 0) {
        if (text != 0) {
          wchar_t *p = text;
          while (*p != 0) {
            glyph_info = FUN_0019cff0(font_tag, (unsigned short)*p);
            if (glyph_info == 0)
              break;
            if ((uintptr_t)p < (uintptr_t)cursor)
              width += (int)*(int16_t *)((char *)glyph_info + 2);
            half += (int)*(int16_t *)((char *)glyph_info + 2);
            p++;
          }
        }
        half >>= 1;
        rect[0] = 0x78;
        rect[1] = (int16_t)(width - half + 0x140);
        rect[2] = (int16_t)(line_h + 0x78);
        rect[3] = (int16_t)(rect[1] + 1);
        draw_bitmap_in_rect((int)(uintptr_t)bitmap, 0, rect, 0, 0, 0, -1);
      }
    }
  }

  draw_string_set_font(*(int *)(ui_globals + 0xc), -1, 2, 0, color_white);

  bitm_base = *(char **)(ui_globals + 0x34) + 0x2c;
  screen_slot = (int16_t *)0x31e5b0;
  for (slot = 0; (uintptr_t)screen_slot < 0x31e6d0u; slot++) {
    int key_action;
    int bitm_index;
    int16_t bounds[4];

    glyph = FUN_000f5800((int16_t)slot);
    glyph_info = FUN_0019cff0(font_tag, glyph);
    if (glyph_info == 0) {
      glyph = 0x7f;
      glyph_info = FUN_0019cff0(font_tag, glyph);
    }
    if (glyph_info != 0) {
      bounds[0] = screen_slot[0];
      bounds[1] = (int16_t)(screen_slot[1] + 2);
      bounds[2] = screen_slot[2];
      bounds[3] = (int16_t)(screen_slot[3] + 2);
      bounds[0] = (int16_t)(bounds[0] + 5);
      bounds[2] = (int16_t)(bounds[2] + 5);
      rasterizer_draw_string((void *)bounds, 0, 0, 0, &glyph);
    }

    key_action =
        (int)(signed char)*((char *)0x28a790 + (int)*(int16_t *)0x46cef8 * 11 +
                            (int)*(int16_t *)0x46cefa);
    if (key_action == slot) {
      if (*(int16_t *)0x46cefe == 4)
        bitm_index = *(int *)(bitm_base + 0x10);
      else
        bitm_index = *(int *)bitm_base;
    } else {
      bitm_index = *(int *)(bitm_base - 0x10);
    }
    if (bitm_index != -1) {
      bitmap = FUN_00077040(bitm_index, 0, 0);
      if (bitmap != 0)
        draw_bitmap_in_rect((int)(uintptr_t)bitmap, screen_slot, screen_slot, 0,
                            0, 0, -1);
    }

    screen_slot += 4;
    bitm_base += 0x50;
  }
}

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
