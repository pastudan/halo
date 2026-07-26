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

/* 0xf4210 */
void multiplayer_settings_select_list_update_item(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  tag_get(0x44654c61, 0);
  display_assert((char *)0x00289bd0, (char *)0x00288938, 1930, ebx);
  system_exit(0);
  /* relift: cmp dword ptr [esi + 0x3e0], 3 -> je 0xf428c */
  display_assert((char *)0x00289b88, (char *)0x00288938, 1931, ebx);
  system_exit(0);
  FUN_000f3690((void *)0);
  /* cmp ecx, edx -> je 0xf42b4 */
  /* cmp eax, 0xc -> jl 0xf42a0 */
  multiplayer_game_set_text_box_for_game_ruleset((void *)(uintptr_t)edx);
  /* relift: cmp dword ptr [ebp + eax*4 - 0x34], -1 -> je 0xf46cf */
  widget_instance_get_nth_child((void *)(uintptr_t)edi, 0);
  /* test esi, esi -> je 0xf4302 */
  /* relift: cmp word ptr [esi + 0xe], 0 -> je 0xf4321 */
  display_assert((char *)0x00289b54, (char *)0x00288938, 1967, ebx);
  system_exit(0);
  /* test edi, edi -> je 0xf432e */
  /* relift: cmp word ptr [edi + 0xe], (int16_t)ebx -> je 0xf434d */
  display_assert((char *)0x00289b28, (char *)0x00288938, 1970, ebx);
  system_exit(0);
  /* relift: cmp word ptr [esi + 0xe], 0 -> je 0xf437d */
  display_assert((char *)0x00289aec, (char *)0x00288938, 1973, ebx);
  system_exit(0);
  /* test esi, esi -> je 0xf438b */
  /* relift: cmp word ptr [esi + 0xe], 0 -> je 0xf43aa */
  display_assert((char *)0x00289aac, (char *)0x00288938, 1976, ebx);
  system_exit(0);
  /* relift: cmp word ptr [esi + 0xe], (int16_t)ebx -> je 0xf43d9 */
  display_assert((char *)0x00289a70, (char *)0x00288938, 1979, ebx);
  system_exit(0);
  /* relift: cmp word ptr [esi + 0xe], (int16_t)ebx -> je 0xf4408 */
  display_assert((char *)0x00289a38, (char *)0x00288938, 1982, ebx);
  system_exit(0);
  /* relift: cmp word ptr [esi + 0xe], (int16_t)ebx -> je 0xf4437 */
  display_assert((char *)0x002899fc, (char *)0x00288938, 1985, ebx);
  system_exit(0);
  /* relift: cmp word ptr [esi + 0xe], (int16_t)ebx -> je 0xf4466 */
  display_assert((char *)0x002899bc, (char *)0x00288938, 1988, ebx);
  system_exit(0);
  /* relift: cmp word ptr [esi + 0xe], (int16_t)ebx -> je 0xf4495 */
  display_assert((char *)0x00289970, (char *)0x00288938, 1991, ebx);
  system_exit(0);
  /* test esi, esi -> je 0xf44a2 */
  /* relift: cmp word ptr [esi + 0xe], (int16_t)ebx -> je 0xf44c1 */
  display_assert((char *)0x00289938, (char *)0x00288938, 1994, ebx);
  system_exit(0);
  /* relift: cmp word ptr [ebx + 0xe], 1 -> je 0xf44f2 */
  display_assert((char *)0x00289900, (char *)0x00288938, 1997, 0);
  system_exit(0);
  /* cmp edx, -1 -> je 0xf4684 */
  /* relift: cmp dword ptr [eax], edx -> je 0xf4526 */
  /* cmp eax, 0x5aa45c -> jl 0xf4512 */
  ui_widget_realloc(0, 24, (char *)0x00288938, 2023);
  /* test (char)ecx, 1 -> je 0xf45d6 */
  tag_loaded(0, (char *)0);
  /* cmp eax, -1 -> je 0xf45ba */
  FUN_0019d420(0, 0);
  ustrncpy((wchar_t *)(uintptr_t)ecx, (wchar_t *)(uintptr_t)eax, 11);
  ustrncpy((wchar_t *)(uintptr_t)eax, (wchar_t *)(uintptr_t)ebx, 11);
  /* relift: cmp word ptr [ebx + 0x18], 0 -> jge 0xf45f6 */
  FUN_001c0ed0();
  /* cmp esi, ecx -> jle 0xf4612 */
  FUN_001c0ed0();
  /* relift: test byte ptr [ebx + 0x1a], 1 -> je 0xf4634 */
  player_profile_save_last_level_played();
  /* cmp ecx, 9 -> jle 0xf4658 */
  FUN_001c0ed0();

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0xf46e0 */
void FUN_000f46e0(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* test eax, eax -> jne 0xf4717 */
  display_assert((char *)0x00289ea8, (char *)0x00288938, 2142, 0);
  system_exit(0);
  tag_get('aLeD', 0);
  /* relift: cmp word ptr [esi], 2 -> je 0xf474f */
  display_assert((char *)0x00289e64, (char *)0x00288938, 2148, 0);
  system_exit(0);
  /* test eax, eax -> je 0xf4779 */
  display_assert((char *)0x00289e18, (char *)0x00288938, 2149, 0);
  system_exit(0);
  tag_get('aLeD', 0);
  /* cmp ecx, 3 -> je 0xf47b7 */
  display_assert((char *)0x00289da0, (char *)0x00288938, 2151, 0);
  system_exit(0);
  display_assert((char *)0x00289da0, (char *)0x00288938, 2157, 0);
  system_exit(0);
  /* test (int16_t)eax, (int16_t)eax -> jl 0xf47ff */
  /* cmp edx, ecx -> jl 0xf481f */
  display_assert((char *)0x00289d68, (char *)0x00288938, 2159, 0);
  system_exit(0);
  /* test (int16_t)eax, (int16_t)eax -> jl 0xf4833 */
  /* cmp edx, ecx -> jl 0xf4853 */
  display_assert((char *)0x00289d50, (char *)0x00288938, 2162, 0);
  system_exit(0);
  multiplayer_game_set_text_box_for_game_ruleset((void *)(uintptr_t)edx);
  /* cmp esi, -1 -> je 0xf489e */
  /* relift: cmp dword ptr [eax], esi -> je 0xf4891 */
  /* cmp eax, 0x5aa45c -> jl 0xf4880 */
  /* test (int16_t)eax, (int16_t)eax -> jbe 0xf4afe */
  qsort((void *)(uintptr_t)ebx, esi, 0, (void *)0);
  /* test esi, esi -> jle 0xf48d3 */
  /* relift: cmp dword ptr [ebx + eax*4], -1 -> je 0xf48d3 */
  /* cmp eax, esi -> jl 0xf48c8 */
  /* cmp ecx, eax -> jg 0xf48f8 */
  ui_widget_realloc(0, 24, (char *)0x00288938, 2182);
  /* test (char)ecx, 1 -> je 0xf4975 */
  tag_loaded(0, (char *)0);
  FUN_0019d420(0, 0);
  ustrncpy((wchar_t *)(uintptr_t)ecx, (wchar_t *)(uintptr_t)ecx, 11);
  ustrncpy((wchar_t *)(uintptr_t)eax, (wchar_t *)(uintptr_t)esi, 11);
  /* relift: cmp word ptr [esi + 0x18], 0 -> jge 0xf4995 */
  FUN_001c0ed0();
  /* cmp edi, ecx -> jle 0xf49b1 */
  FUN_001c0ed0();
  ui_widget_realloc(0, 512, (char *)0x00288938, 2204);
  /* relift: test byte ptr [esi + 0x1a], 1 -> je 0xf4a7f */
  tag_loaded('rtsu', (char *)0x00289d00);
  tag_loaded('rtsu', (char *)0x00289cb8);
  /* cmp ebx, -1 -> je 0xf4a61 */
  FUN_0019d420(0, 0);
  FUN_0019d420(0, 0);
  unicode_sprintf((wchar_t *)(uintptr_t)eax, 255, (wchar_t *)0x00289ca4);
  tag_loaded('rtsu', (char *)0x00289c58);
  tag_loaded('rtsu', (char *)0x00289c10);
  /* cmp ebx, -1 -> je 0xf4ae8 */
  FUN_0019d420(0, 0);
  FUN_0019d420(0, 0);
  unicode_sprintf((wchar_t *)(uintptr_t)ecx, 255, (wchar_t *)0x00289ca4);
  ui_widget_realloc(0, 0, (char *)0x00288938, 2258);
  ui_widget_realloc(0, 0, (char *)0x00288938, 2263);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0xf4b60 */
void FUN_000f4b60(void)
{
  int eax = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  display_assert((char *)0x0028a058, (char *)0x00288938, 2372, 0);
  system_exit(0);
  tag_get('aLeD', 0);
  /* relift: cmp word ptr [edi], 2 -> je 0xf4bcb */
  display_assert((char *)0x0028a01c, (char *)0x00288938, 2377, 0);
  system_exit(0);
  /* relift: cmp dword ptr [edi + 0x3e0], 3 -> je 0xf4bf4 */
  display_assert((char *)0x00289fd8, (char *)0x00288938, 2378, 0);
  system_exit(0);
  FUN_000f3690((void *)0);
  /* relift: cmp dword ptr [ebp + edi*4 - 0xc], -1 -> je 0xf4ce5 */
  widget_instance_get_nth_child((void *)(uintptr_t)esi, 0);
  tag_get('aLeD', 0);
  /* cmp ecx, 2 -> je 0xf4c58 */
  display_assert((char *)0x00289f90, (char *)0x00288938, 2395, 0);
  system_exit(0);
  tag_get('aLeD', 0);
  /* relift: cmp word ptr [eax], 1 -> je 0xf4c8e */
  display_assert((char *)0x00289f48, (char *)0x00288938, 2397, 0);
  system_exit(0);
  tag_get('aLeD', 0);
  /* relift: cmp word ptr [eax], 0 -> je 0xf4cc4 */
  display_assert((char *)0x00289ef8, (char *)0x00288938, 2399, 0);
  system_exit(0);

  (void)eax;
  (void)ecx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0xf4cf0 */
void FUN_000f4cf0(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  tag_get(0x44654c61, 0);
  /* relift: cmp word ptr [esi], 2 -> je 0xf4d34 */
  display_assert((char *)0x0028974c, (char *)0x00288938, 2495, 0);
  system_exit(0);
  /* relift: cmp dword ptr [esi + 0x3e0], 3 -> je 0xf4d5d */
  display_assert((char *)0x00289710, (char *)0x00288938, 2496, 0);
  system_exit(0);
  FUN_000f3690((void *)0);
  /* relift: cmp dword ptr [ebp + ebx*4 - 0x10], -1 -> je 0xf4e8b */
  widget_instance_get_nth_child((void *)(uintptr_t)edi, 0);
  tag_get('aLeD', 0);
  /* test ecx, ecx -> jne 0xf4dc8 */
  display_assert((char *)0x002896d0, (char *)0x00288938, 2514, 0);
  system_exit(0);
  tag_get('aLeD', 0);
  /* relift: cmp word ptr [eax], 1 -> je 0xf4dfe */
  display_assert((char *)0x00289688, (char *)0x00288938, 2516, 0);
  system_exit(0);
  tag_get('aLeD', 0);
  /* relift: cmp word ptr [eax], 0 -> je 0xf4e34 */
  display_assert((char *)0x00289640, (char *)0x00288938, 2518, 0);
  system_exit(0);
  tag_get('aLeD', 0);
  /* relift: cmp word ptr [eax], 1 -> je 0xf4e6d */
  display_assert((char *)0x002895f0, (char *)0x00288938, 2520, 0);
  system_exit(0);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0xf5640 */
void FUN_000f5640(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0xf5650 */
void FUN_000f5650(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0xf5660 */
char FUN_000f5660(void)
{
  int ecx = 0;
  int edx = 0;
  int esi = 0;

  /* relift: cmp byte ptr [esi + ecx + 0x28a790], dl -> je 0xf5680 */
  ui_play_audio_feedback_sound(0);
  return 0;

  (void)ecx;
  (void)edx;
  (void)esi;
}

/* 0xf56b0 */
char FUN_000f56b0(void)
{
  int ecx = 0;
  int edx = 0;
  int esi = 0;

  /* cmp (int16_t)eax, 0xb -> jne 0xf56db */
  /* relift: cmp byte ptr [esi + ecx + 0x28a790], dl -> je 0xf56d0 */
  ui_play_audio_feedback_sound(0);
  return 0;

  (void)ecx;
  (void)edx;
  (void)esi;
}

/* 0xf5800 */
void FUN_000f5800(void)
{
  int eax = 0;
  int ecx = 0;
  int esi = 0;

  /* test eax, eax -> jne 0xf5829 */
  display_assert((char *)0x0028a97c, (char *)0x0028a854, 986, 0);
  system_exit(0);
  /* cmp (int16_t)esi, 0x24 -> jb 0xf584f */
  display_assert((char *)0x0028a94c, (char *)0x0028a854, 987, 0);
  system_exit(0);
  /* test (char)ecx, (char)ecx -> je 0xf587d */
  /* test (char)ecx, (char)ecx -> je 0xf588d */
  /* test (char)ecx, (char)ecx -> je 0xf58a7 */
  /* test (char)ecx, (char)ecx -> je 0xf58b7 */
  /* test (int16_t)eax, (int16_t)eax -> jne 0xf58c5 */
  /* relift: tail-call FUN_000f5800(); */

  (void)eax;
  (void)ecx;
  (void)esi;
}

/* 0xf5900 */
void FUN_000f5900(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  /* relift: cmp dword ptr [eax + 0xc], edi -> jne 0xf5974 */
  display_assert((char *)0x0028a9d8, (char *)0x0028a854, 1035, 0);
  system_exit(0);
  tag_get('tnof', 0);
  display_assert((char *)0x0028a9c0, (char *)0x0028a854, 1037, 0);
  system_exit(0);
  FUN_00077040(0, 0, 0);
  /* cmp edi, esi -> jne 0xf5a01 */
  display_assert((char *)0x00263768, (char *)0x0028a854, 1045, 0);
  system_exit(0);
  draw_bitmap_in_rect(0, (void *)(uintptr_t)ecx, (void *)(uintptr_t)eax, (void *)(uintptr_t)esi, 0, 0, 0);
  draw_string_set_font(0, 0, 0, 0, (void *)(uintptr_t)edx);
  /* cmp ecx, edi -> je 0xf5a7f */
  FUN_0019d420(0, 0);
  rasterizer_draw_string((void *)(uintptr_t)ecx, (void *)(uintptr_t)eax, (void *)(uintptr_t)esi, 0, (void *)(uintptr_t)eax);
  draw_string_set_font(0, 0, 0, 0, (void *)(uintptr_t)edx);
  FUN_00077040(0, 0, 0);
  /* cmp edi, esi -> je 0xf5b06 */
  FUN_0019cdb0((void *)(uintptr_t)edx, (void *)(uintptr_t)ecx, (void *)(uintptr_t)eax, (void *)(uintptr_t)edx);
  draw_bitmap_in_rect(0, (void *)(uintptr_t)ecx, (void *)(uintptr_t)eax, (void *)(uintptr_t)esi, 0x7f7f7f7f, 0, 0);
  rasterizer_draw_string((void *)(uintptr_t)ecx, (void *)(uintptr_t)eax, (void *)(uintptr_t)esi, 0, (void *)(uintptr_t)edx);
  /* test (char)eax, (char)eax -> jne 0xf5c0d */
  /* relift: cmp dword ptr [0x46cf14], -1 -> je 0xf5c0d */
  system_milliseconds();
  /* test dl, 1 -> je 0xf5c0d */
  FUN_00077040(0, 0, 0);
  /* cmp ebx, esi -> je 0xf5bc4 */
  FUN_0019cff0();
  /* test eax, eax -> je 0xf5bca */
  /* relift: cmp ebx, dword ptr [0x46cf0c] -> jae 0xf5bb9 */
  draw_bitmap_in_rect(0, (void *)0, (void *)0, (void *)0, 0, 0, 0);
  draw_string_set_font(0, 0, 0, 0, (void *)(uintptr_t)eax);
  FUN_000f5800();
  FUN_0019cff0();
  /* test eax, eax -> jne 0xf5c88 */
  FUN_0019cff0();
  /* test eax, eax -> je 0xf5cc3 */
  rasterizer_draw_string((void *)(uintptr_t)ecx, (void *)0, (void *)0, 0, (void *)(uintptr_t)eax);
  /* cmp ecx, esi -> jne 0xf5cf6 */
  /* relift: cmp word ptr [0x46cefe], 4 -> jne 0xf5cf2 */
  /* cmp eax, -1 -> je 0xf5d23 */
  FUN_00077040(0, 0, 0);
  /* test eax, eax -> je 0xf5d23 */
  draw_bitmap_in_rect(0, (void *)(uintptr_t)edi, (void *)0, (void *)0, 0, 0, 0);
  /* relift: cmp dword ptr [edx + 0x2c], -1 -> je 0xf5ede */
  /* cmp esi, 0x2c -> jge 0xf5ede */
  FUN_0019d420(0, 0);
  /* cmp eax, 7 -> ja 0xf5e45 */
  /* relift: cmp ecx, dword ptr [ebp - 4] -> jne 0xf5dcf */
  /* relift: cmp word ptr [0x46cefe], 4 -> jne 0xf5e2c */
  /* relift: cmp ecx, dword ptr [ebp - 4] -> je 0xf5dc1 */
  /* test (char)eax, (char)eax -> je 0xf5dcf */
  /* relift: cmp ecx, dword ptr [ebp - 4] -> je 0xf5dc1 */
  /* test (char)eax, (char)eax -> je 0xf5dcf */
  /* cmp eax, -1 -> je 0xf5e65 */
  FUN_00077040(0, 0, 0);
  display_assert((char *)0x0028a9a8, (char *)0x0028a854, 1407, 0);
  system_exit(0);
  /* test eax, eax -> je 0xf5ea7 */
  rasterizer_draw_string((void *)(uintptr_t)edx, (void *)0, (void *)0, 0, (void *)0);
  /* test edi, edi -> je 0xf5ebe */
  draw_bitmap_in_rect(0, (void *)(uintptr_t)ebx, (void *)(uintptr_t)ebx, (void *)0, 0, 0, 0);
  /* mem[0xd4000f5d] = eax */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0xf5f10 */
void object_get_type(void)
{
  int eax = 0;

  ustrlen((void *)(uintptr_t)eax);

  (void)eax;
}

/* 0xf5f90 */
void items_initialize(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;

  ustrncpy((wchar_t *)(uintptr_t)eax, (wchar_t *)0x0046cf18, ecx);
  /* mem[0x0046cf08] = ebx */
  ui_play_audio_feedback_sound(0);

  (void)eax;
  (void)ebx;
  (void)ecx;
}

/* 0xf5fa0 */
void items_initialize_for_new_map(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0xf5fb0 */
char FUN_000f5fb0(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;

  /* cmp eax, 7 -> ja 0xf621d */
  ustrcmp((wchar_t *)0x0046cf18, (wchar_t *)(uintptr_t)edx);
  /* test eax, eax -> je 0xf603a */
  /* relift: cmp word ptr [eax], (int16_t)ebx -> je 0xf6024 */
  saved_game_file_name_unique();
  /* test (char)eax, (char)eax -> jne 0xf603a */
  ui_widget_display_error(27, 0, 0, ebx);
  FUN_000f57a0();
  ui_widget_display_error(29, 0, 0, ebx);
  FUN_000f57a0();
  ui_play_audio_feedback_sound(0);
  event_manager_flush();
  ui_play_audio_feedback_sound(0);
  ui_play_audio_feedback_sound(0);
  ui_play_audio_feedback_sound(0);
  /* relift: cmp byte ptr [0x46cf07], 1 -> jne 0xf6118 */
  /* relift: cmp word ptr [0x46cefc], (int16_t)ebx -> ja 0xf60e9 */
  display_assert((char *)0x0028aa58, (char *)0x0028a854, 853, 0);
  system_exit(0);
  csmemset((void *)(uintptr_t)ecx, 0, eax);
  /* mem[0x0046cf0c] = edx */
  FUN_000f5f30();
  /* relift: cmp eax, dword ptr [0x46cf08] -> jbe 0xf6137 */
  /* mem[0x0046cf0c] = eax */
  ui_play_audio_feedback_sound(0);
  /* relift: cmp word ptr [ecx], (int16_t)ebx -> je 0xf6137 */
  /* relift: cmp byte ptr [0x46cf07], 1 -> jne 0xf61b9 */
  /* relift: cmp word ptr [0x46cefc], (int16_t)ebx -> ja 0xf6190 */
  display_assert((char *)0x0028aa58, (char *)0x0028a854, 888, 0);
  system_exit(0);
  csmemset((void *)(uintptr_t)eax, 0, edx);
  /* mem[0x0046cf0c] = ecx */
  object_get_type();
  /* cmp eax, 2 -> jl 0xf620e */
  csmemmove((void *)(uintptr_t)eax, (void *)0, 0);
  /* mem[0x0046cf0c] = edx */
  ui_play_audio_feedback_sound(0);
  ui_play_audio_feedback_sound(0);
  /* relift: cmp byte ptr [0x46cf07], 1 -> jne 0xf6277 */
  /* relift: cmp word ptr [0x46cefc], (int16_t)ebx -> ja 0xf624f */
  display_assert((char *)0x0028aa58, (char *)0x0028a854, 913, 0);
  system_exit(0);
  csmemset((void *)(uintptr_t)edx, 0, ecx);
  /* mem[0x0046cf0c] = eax */
  ustrlen((void *)(uintptr_t)ecx);
  /* cmp eax, 2 -> jl 0xf6392 */
  csmemmove((void *)(uintptr_t)eax, (void *)0, 0);
  FUN_000f5800();
  /* mem[0x0046cf0c] = ecx */
  ustrcmp((wchar_t *)(uintptr_t)eax, (wchar_t *)0x0028aa44);
  /* test eax, eax -> jne 0xf638e */
  system_milliseconds();
  /* cmp edx, 9 -> jbe 0xf6325 */
  align_to_character();
  ustrlen((void *)(uintptr_t)eax);
  /* mem[0x0046cf0c] = edx */
  csmemset((void *)(uintptr_t)ecx, 0, eax);
  /* mem[0x0046cf0c] = edx */
  ui_play_audio_feedback_sound(0);
  return 0;

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
}

/* 0xf6a60 */
void item_get_position_even_if_in_inventory(void)
{
  int eax = 0;
  int ecx = 0;

  object_try_and_get_and_verify_type(0, 28);
  /* relift: test byte ptr [eax + 0x1a4], 1 -> je 0xf6acd */
  /* cmp eax, -1 -> je 0xf6ae0 */
  datum_get((void *)(uintptr_t)ecx, 0);
  /* cmp eax, -1 -> je 0xf6ae0 */
  object_get_and_verify_type(0, 0);

  (void)eax;
  (void)ecx;
}

/* 0xf7110 */
void FUN_000f7110(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  object_get_and_verify_type(0, 28);
  display_assert((char *)0x0026b188, (char *)0x0028aaa0, 713, 0);
  system_exit(0);
  object_get_markers_by_string_id(0, (void *)0x0028aa90, (void *)(uintptr_t)eax, 0);
  /* test (int16_t)eax, (int16_t)eax -> je 0xf7331 */
  /* test eax, eax -> jne 0xf717b */
  /* test edi, edi -> jne 0xf7182 */
  /* test (char)eax, 0x41 -> jne 0xf7255 */
  /* test (char)eax, 0x41 -> je 0xf71e5 */
  display_assert((char *)0x0028aaec, (char *)0x0028aaa0, 732, 0);
  system_exit(0);
  quaternion_transform_point((float *)0, (float *)0, (float *)0);
  normalize3d((float *)(uintptr_t)edx);
  matrix4x3_from_forward_up_position((void *)(uintptr_t)edx, (float *)(uintptr_t)ecx, (float *)(uintptr_t)eax, (float *)(uintptr_t)esi);
  valid_real_matrix4x3((float *)(uintptr_t)eax);
  /* test (char)eax, (char)eax -> jne 0xf72f9 */
  display_assert((char *)0x0028aac0, (char *)0x0028aaa0, 755, 0);
  system_exit(0);
  object_get_and_verify_type(0, 0);
  object_compute_child_marker_position((void *)(uintptr_t)eax, (void *)0, (void *)0);

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0xf7340 */
void item_update(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;

  object_get_and_verify_type(0, 28);
  tag_get('meti', 0);
  /* test (char)eax, (char)eax -> je 0xf7390 */
  profile_enter_private((void *)0x0031e710);
  /* relift: cmp word ptr [0x4761d8], 0x20 -> jl 0xf73ba */
  display_assert((char *)0x00253440, (char *)0x0028aaa0, 174, 0);
  system_exit(0);
  /* test (char)eax, 8 -> je 0xf7bc4 */
  /* relift: cmp dword ptr [ebx + 0xcc], -1 -> jne 0xf7bc4 */
  /* relift: test byte ptr [esi + 0x17c], 1 -> je 0xf7471 */
  cross_product3d((float *)(uintptr_t)eax, (float *)(uintptr_t)esi, (float *)(uintptr_t)ecx);
  cross_product3d((float *)(uintptr_t)edx, (float *)(uintptr_t)eax, (float *)(uintptr_t)esi);
  normalize3d((float *)(uintptr_t)esi);
  /* relift: test byte ptr [ebx + 4], 0x20 -> jne 0xf7901 */
  FUN_000130d0(0, (float *)0, (float *)0, 0, (void *)0);
  /* test (char)eax, (char)eax -> je 0xf78d7 */
  FUN_00012fe0((float *)0);
  /* test (char)eax, 0x41 -> jne 0xf7567 */
  /* relift: cmp dword ptr [eax + 0x254], -1 -> je 0xf75b7 */
  FUN_0009f3b0((void *)(uintptr_t)ecx);
  /* test (char)eax, (char)eax -> je 0xf75b7 */
  FUN_0009f430(0, 0, 0, (void *)(uintptr_t)edx, (void *)(uintptr_t)ecx, (void *)(uintptr_t)eax, 0.0f);
  /* cmp eax, -1 -> je 0xf7623 */
  unattached_impulse_sound_new(0, (void *)(uintptr_t)ecx, 0.0f);
  /* cmp (int16_t)eax, 2 -> je 0xf765b */
  /* cmp (int16_t)eax, 3 -> jne 0xf7801 */
  FUN_000f68b0(0);
  /* test edx, 0x3c0 -> je 0xf7801 */
  /* test (char)eax, 0x41 -> jne 0xf7801 */
  FUN_000f7110();
  FUN_00012fb0((float *)(uintptr_t)ecx, 0.0f, (float *)0);
  game_engine_running();
  /* test (char)eax, (char)eax -> jne 0xf7737 */
  /* relift: cmp dword ptr [esi + 0x70], -1 -> jne 0xf7737 */
  object_set_garbage_flag(0, 0);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
}
