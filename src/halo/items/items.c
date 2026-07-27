/* FUN_000f52f0 (0xf52f0) — XBE naked draft (batch 69). */
#if defined(__clang__)


__attribute__((naked, noinline))
wchar_t * FUN_000f52f0(void *widget __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movswl 0x8(%%eax), %%eax\n\t"
      "incl %%eax\n\t"
      "cmpl $4, %%eax\n\t"
      "ja .LFUN_000f52f0_5\n\t"
      "jmp *.LFUN_000f52f0_jt(,%%eax,4)\n\t"
      ".LFUN_000f52f0_1:\n\t"
      "movw $0x31, 0x46cee8\n\t"
      "movw $0, 0x46ceea\n\t"
      "movl $0x46cee8, %%eax\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000f52f0_2:\n\t"
      "movw $0x32, 0x46cee8\n\t"
      "movw $0, 0x46ceea\n\t"
      "movl $0x46cee8, %%eax\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000f52f0_3:\n\t"
      "movw $0x33, 0x46cee8\n\t"
      "movw $0, 0x46ceea\n\t"
      "movl $0x46cee8, %%eax\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000f52f0_4:\n\t"
      "movw $0x34, 0x46cee8\n\t"
      "movw $0, 0x46ceea\n\t"
      "movl $0x46cee8, %%eax\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000f52f0_5:\n\t"
      "movw $0x3f, 0x46cee8\n\t"
      "movw $0, 0x46ceea\n\t"
      "movl $0x46cee8, %%eax\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_000f52f0_jt:\n\t"
      ".long .LFUN_000f52f0_1\n\t"
      ".long .LFUN_000f52f0_1\n\t"
      ".long .LFUN_000f52f0_2\n\t"
      ".long .LFUN_000f52f0_3\n\t"
      ".long .LFUN_000f52f0_4\n\t"
      ".text\n\t"
      :
      :
      : "memory");
}
#else
#error "FUN_000f52f0: clang naked draft required"
#endif


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

/* FUN_000f5750 (0xf5750) — XBE naked draft (batch 54). */
#if defined(__clang__)
static void (*const bf5750_ce5ab0)(int16_t sound_selector) = ui_play_audio_feedback_sound;
static wchar_t * (*const bf5750_c19dc90)(wchar_t *dest, wchar_t *src, size_t count) = ustrncpy;
static void (*const bf5750_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const bf5750_exitfn)(int) = system_exit;
static unsigned short (*const bf5750_cf5800)(int16_t slot_index /* */) = (void *)FUN_000f5800;

__attribute__((naked, noinline))
char FUN_000f5750(void)
{
  __asm__ volatile(
      "movw 0x46cef8, %%ax\n\t"
      "movswl 0x46cefa, %%ecx\n\t"
      "movswl %%ax, %%edx\n\t"
      "imull $0xb, %%edx, %%edx\n\t"
      "movb 0x28a790(%%edx,%%ecx,1), %%dl\n\t"
      "pushl %%esi\n\t"
      "jmp .LFUN_000f5750_1\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".LFUN_000f5750_1:\n\t"
      "incw %%ax\n\t"
      "cmpw $5, %%ax\n\t"
      "jne .LFUN_000f5750_2\n\t"
      "xorw %%ax, %%ax\n\t"
      ".LFUN_000f5750_2:\n\t"
      "movswl %%ax, %%esi\n\t"
      "imull $0xb, %%esi, %%esi\n\t"
      "cmpb %%dl, 0x28a790(%%esi,%%ecx,1)\n\t"
      "je .LFUN_000f5750_1\n\t"
      "pushl $1\n\t"
      "movw %%ax, 0x46cef8\n\t"
      "call *%[ce5ab0]\n\t"
      "addl $4, %%esp\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "ret\n\t"
      "nop\n\t"
      "nop\n\t"
      "movl 0x46cf08, %%eax\n\t"
      "pushl %%ebx\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "cmpl %%ebx, %%eax\n\t"
      "movb %%bl, 0x46cef0\n\t"
      "je .LFUN_000f5750_3\n\t"
      "movzwl 0x46cefc, %%ecx\n\t"
      "shrl $1, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x46cf18\n\t"
      "pushl %%eax\n\t"
      "call *%[c19dc90]\n\t"
      "movzwl 0x46cefc, %%edx\n\t"
      "movl 0x46cf08, %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "shrl $1, %%edx\n\t"
      "movw %%bx, -0x2(%%eax,%%edx,2)\n\t"
      ".LFUN_000f5750_3:\n\t"
      "pushl $3\n\t"
      "movl %%ebx, 0x46cf08\n\t"
      "movw %%bx, 0x46cf18\n\t"
      "movb %%bl, 0x46cf06\n\t"
      "call *%[ce5ab0]\n\t"
      "addl $4, %%esp\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      "nop\n\t"
      "nop\n\t"
      "movl 0x46cef4, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_000f5750_4\n\t"
      "pushl $1\n\t"
      "pushl $0x3da\n\t"
      "pushl $0x28a854\n\t"
      "pushl $0x28a97c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000f5750_4:\n\t"
      "cmpw $0x24, %%si\n\t"
      "jb .LFUN_000f5750_5\n\t"
      "pushl $1\n\t"
      "pushl $0x3db\n\t"
      "pushl $0x28a854\n\t"
      "pushl $0x28a94c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000f5750_5:\n\t"
      "movl 0x46cef4, %%ecx\n\t"
      "movl 0x34(%%ecx), %%edx\n\t"
      "movb 0x46cef1, %%cl\n\t"
      "movzwl %%si, %%eax\n\t"
      "leal (%%eax,%%eax,4), %%eax\n\t"
      "shll $4, %%eax\n\t"
      "addl %%edx, %%eax\n\t"
      "testb %%cl, %%cl\n\t"
      "movb 0x46cef2, %%cl\n\t"
      "je .LFUN_000f5750_8\n\t"
      "testb %%cl, %%cl\n\t"
      "je .LFUN_000f5750_6\n\t"
      "movw 0xa(%%eax), %%ax\n\t"
      "jmp .LFUN_000f5750_12\n\t"
      ".LFUN_000f5750_6:\n\t"
      "movb 0x46cef3, %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "je .LFUN_000f5750_7\n\t"
      "movw 0xc(%%eax), %%ax\n\t"
      "jmp .LFUN_000f5750_12\n\t"
      ".LFUN_000f5750_7:\n\t"
      "movw 0x4(%%eax), %%ax\n\t"
      "jmp .LFUN_000f5750_12\n\t"
      ".LFUN_000f5750_8:\n\t"
      "testb %%cl, %%cl\n\t"
      "movb 0x46cef3, %%cl\n\t"
      "je .LFUN_000f5750_10\n\t"
      "testb %%cl, %%cl\n\t"
      "je .LFUN_000f5750_9\n\t"
      "movw 0xe(%%eax), %%ax\n\t"
      "jmp .LFUN_000f5750_12\n\t"
      ".LFUN_000f5750_9:\n\t"
      "movw 0x6(%%eax), %%ax\n\t"
      "jmp .LFUN_000f5750_12\n\t"
      ".LFUN_000f5750_10:\n\t"
      "testb %%cl, %%cl\n\t"
      "je .LFUN_000f5750_11\n\t"
      "movw 0x8(%%eax), %%ax\n\t"
      "jmp .LFUN_000f5750_12\n\t"
      ".LFUN_000f5750_11:\n\t"
      "movw 0x2(%%eax), %%ax\n\t"
      ".LFUN_000f5750_12:\n\t"
      "testw %%ax, %%ax\n\t"
      "jne .LFUN_000f5750_13\n\t"
      "movl $0x7f, %%eax\n\t"
      ".LFUN_000f5750_13:\n\t"
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
      "movswl 0x46cef8, %%eax\n\t"
      "movswl 0x46cefa, %%ecx\n\t"
      "imull $0xb, %%eax, %%eax\n\t"
      "pushl %%esi\n\t"
      "movsbw 0x28a790(%%eax,%%ecx,1), %%si\n\t"
      "call *%[cf5800]\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      "nop\n\t"
      :
      : [ce5ab0] "m"(bf5750_ce5ab0), [c19dc90] "m"(bf5750_c19dc90), [assert] "m"(bf5750_assert), [exitfn] "m"(bf5750_exitfn), [cf5800] "m"(bf5750_cf5800)
      : "memory");
}
#else
#error "FUN_000f5750: clang naked draft required"
#endif


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

/* virtual_keyboard_process_input (0xf63f0) — XBE naked draft (batch 61). */
#if defined(__clang__)
static unsigned int (*const bf63f0_c8e370)(void) = system_milliseconds;
static bool (*const bf63f0_cdc250)(void *event_data, int16_t player_index) = event_manager_get_next_event;
static void (*const bf63f0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const bf63f0_exitfn)(int) = system_exit;
static void *(*const bf63f0_memset)(void *, int, unsigned int) = csmemset;
static void (*const bf63f0_ce5ab0)(int16_t sound_selector) = ui_play_audio_feedback_sound;
static void (*const bf63f0_cf5f30)(void) = FUN_000f5f30;
static char (*const bf63f0_cf5660)(void) = FUN_000f5660;
static char (*const bf63f0_cf56b0)(void) = FUN_000f56b0;
static char (*const bf63f0_cf5700)(void) = FUN_000f5700;
static char (*const bf63f0_cf5750)(void) = FUN_000f5750;
static char (*const bf63f0_cf5fb0)(void) = FUN_000f5fb0;
static char (*const bf63f0_cf57a0)(void) = FUN_000f57a0;

__attribute__((naked, noinline))
void virtual_keyboard_process_input(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $8, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c8e370]\n\t"
      "movl %%eax, %%edi\n\t"
      "leal -0x8(%%ebp), %%eax\n\t"
      "pushl $-1\n\t"
      "pushl %%eax\n\t"
      "orl $0xffffffff, %%esi\n\t"
      "xorb %%bl, %%bl\n\t"
      "call *%[cdc250]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lvirtual_keyboard_process_input_34\n\t"
      "jmp .Lvirtual_keyboard_process_input_1\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".Lvirtual_keyboard_process_input_1:\n\t"
      "movswl -0x8(%%ebp), %%eax\n\t"
      "decl %%eax\n\t"
      "je .Lvirtual_keyboard_process_input_20\n\t"
      "movl $2, %%edx\n\t"
      "subl %%edx, %%eax\n\t"
      "jne .Lvirtual_keyboard_process_input_25\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movzbl %%al, %%ecx\n\t"
      "cmpl $0xd, %%ecx\n\t"
      "ja .Lvirtual_keyboard_process_input_25\n\t"
      "jmp *.Lvirtual_keyboard_process_input_jt0(,%%ecx,4)\n\t"
      ".Lvirtual_keyboard_process_input_2:\n\t"
      "cmpb $1, %%ah\n\t"
      "jne .Lvirtual_keyboard_process_input_25\n\t"
      "movl $4, %%esi\n\t"
      "jmp .Lvirtual_keyboard_process_input_25\n\t"
      ".Lvirtual_keyboard_process_input_3:\n\t"
      "cmpb $1, %%ah\n\t"
      "jne .Lvirtual_keyboard_process_input_25\n\t"
      "movl $5, %%esi\n\t"
      "jmp .Lvirtual_keyboard_process_input_25\n\t"
      ".Lvirtual_keyboard_process_input_4:\n\t"
      "cmpw %%dx, 0x46cefe\n\t"
      "jne .Lvirtual_keyboard_process_input_5\n\t"
      "movl %%edi, %%ecx\n\t"
      "subl 0x46cf58, %%ecx\n\t"
      "cmpl $0xfa, %%ecx\n\t"
      "jae .Lvirtual_keyboard_process_input_5\n\t"
      "cmpb $1, %%ah\n\t"
      "jne .Lvirtual_keyboard_process_input_25\n\t"
      ".Lvirtual_keyboard_process_input_5:\n\t"
      "movl %%edx, %%esi\n\t"
      "movl %%edi, 0x46cf58\n\t"
      "jmp .Lvirtual_keyboard_process_input_25\n\t"
      ".Lvirtual_keyboard_process_input_6:\n\t"
      "cmpw $0, 0x46cefe\n\t"
      "jne .Lvirtual_keyboard_process_input_7\n\t"
      "movl 0x46cf58, %%ecx\n\t"
      "movl %%edi, %%edx\n\t"
      "subl %%ecx, %%edx\n\t"
      "cmpl $0xfa, %%edx\n\t"
      "jae .Lvirtual_keyboard_process_input_7\n\t"
      "cmpb $1, %%ah\n\t"
      "jne .Lvirtual_keyboard_process_input_25\n\t"
      ".Lvirtual_keyboard_process_input_7:\n\t"
      "xorl %%esi, %%esi\n\t"
      "movl %%edi, 0x46cf58\n\t"
      "jmp .Lvirtual_keyboard_process_input_25\n\t"
      ".Lvirtual_keyboard_process_input_8:\n\t"
      "cmpw $3, 0x46cefe\n\t"
      "jne .Lvirtual_keyboard_process_input_9\n\t"
      "movl 0x46cf58, %%edx\n\t"
      "movl %%edi, %%ecx\n\t"
      "subl %%edx, %%ecx\n\t"
      "cmpl $0xfa, %%ecx\n\t"
      "jae .Lvirtual_keyboard_process_input_9\n\t"
      "cmpb $1, %%ah\n\t"
      "jne .Lvirtual_keyboard_process_input_25\n\t"
      ".Lvirtual_keyboard_process_input_9:\n\t"
      "movl $3, %%esi\n\t"
      "movl %%edi, 0x46cf58\n\t"
      "jmp .Lvirtual_keyboard_process_input_25\n\t"
      ".Lvirtual_keyboard_process_input_10:\n\t"
      "cmpw $1, 0x46cefe\n\t"
      "jne .Lvirtual_keyboard_process_input_11\n\t"
      "movl 0x46cf58, %%ecx\n\t"
      "movl %%edi, %%edx\n\t"
      "subl %%ecx, %%edx\n\t"
      "cmpl $0xfa, %%edx\n\t"
      "jae .Lvirtual_keyboard_process_input_11\n\t"
      "cmpb $1, %%ah\n\t"
      "jne .Lvirtual_keyboard_process_input_25\n\t"
      ".Lvirtual_keyboard_process_input_11:\n\t"
      "movl %%edi, 0x46cf58\n\t"
      "jmp .Lvirtual_keyboard_process_input_24\n\t"
      ".Lvirtual_keyboard_process_input_12:\n\t"
      "cmpb $1, %%ah\n\t"
      "jne .Lvirtual_keyboard_process_input_25\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw %%ax, 0x46cef8\n\t"
      "movw %%ax, 0x46cefa\n\t"
      "movl $4, %%esi\n\t"
      "jmp .Lvirtual_keyboard_process_input_25\n\t"
      ".Lvirtual_keyboard_process_input_13:\n\t"
      "cmpb $1, %%ah\n\t"
      "jne .Lvirtual_keyboard_process_input_25\n\t"
      "movb 0x46cf07, %%al\n\t"
      "cmpb %%ah, %%al\n\t"
      "jne .Lvirtual_keyboard_process_input_15\n\t"
      "cmpw $0, 0x46cefc\n\t"
      "ja .Lvirtual_keyboard_process_input_14\n\t"
      "pushl $1\n\t"
      "pushl $0x27a\n\t"
      "pushl $0x28a854\n\t"
      "pushl $0x28aa58\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lvirtual_keyboard_process_input_14:\n\t"
      "movzwl 0x46cefc, %%eax\n\t"
      "movl 0x46cf08, %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl $0\n\t"
      "pushl %%ecx\n\t"
      "call *%[memset]\n\t"
      "movl 0x46cf08, %%edx\n\t"
      "pushl $1\n\t"
      "movl %%edx, 0x46cf0c\n\t"
      "movb $0, 0x46cf07\n\t"
      "call *%[ce5ab0]\n\t"
      "addl $0x10, %%esp\n\t"
      "movb $1, %%bl\n\t"
      "jmp .Lvirtual_keyboard_process_input_25\n\t"
      ".Lvirtual_keyboard_process_input_15:\n\t"
      "call *%[cf5f30]\n\t"
      "movb $1, %%bl\n\t"
      "jmp .Lvirtual_keyboard_process_input_25\n\t"
      ".Lvirtual_keyboard_process_input_16:\n\t"
      "cmpb $1, %%ah\n\t"
      "jne .Lvirtual_keyboard_process_input_25\n\t"
      "movl 0x46cf0c, %%eax\n\t"
      "cmpl 0x46cf08, %%eax\n\t"
      "movb $0, 0x46cf07\n\t"
      "jbe .Lvirtual_keyboard_process_input_18\n\t"
      "subl %%edx, %%eax\n\t"
      ".Lvirtual_keyboard_process_input_17:\n\t"
      "movl %%eax, 0x46cf0c\n\t"
      ".Lvirtual_keyboard_process_input_18:\n\t"
      "pushl $1\n\t"
      "call *%[ce5ab0]\n\t"
      "addl $4, %%esp\n\t"
      "movb $1, %%bl\n\t"
      "jmp .Lvirtual_keyboard_process_input_25\n\t"
      ".Lvirtual_keyboard_process_input_19:\n\t"
      "cmpb $1, %%ah\n\t"
      "jne .Lvirtual_keyboard_process_input_25\n\t"
      "movl 0x46cf0c, %%ecx\n\t"
      "movb $0, 0x46cf07\n\t"
      "cmpw $0, (%%ecx)\n\t"
      "je .Lvirtual_keyboard_process_input_18\n\t"
      "movl %%ecx, %%eax\n\t"
      "addl %%edx, %%eax\n\t"
      "jmp .Lvirtual_keyboard_process_input_17\n\t"
      ".Lvirtual_keyboard_process_input_20:\n\t"
      "movw -0x2(%%ebp), %%ax\n\t"
      "cmpw $0x7fff, %%ax\n\t"
      "jne .Lvirtual_keyboard_process_input_21\n\t"
      "movl $2, %%esi\n\t"
      "jmp .Lvirtual_keyboard_process_input_25\n\t"
      ".Lvirtual_keyboard_process_input_21:\n\t"
      "cmpw $0x8000, %%ax\n\t"
      "jne .Lvirtual_keyboard_process_input_22\n\t"
      "movl $3, %%esi\n\t"
      "jmp .Lvirtual_keyboard_process_input_25\n\t"
      ".Lvirtual_keyboard_process_input_22:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "cmpw $0x8000, %%ax\n\t"
      "jne .Lvirtual_keyboard_process_input_23\n\t"
      "xorl %%esi, %%esi\n\t"
      "jmp .Lvirtual_keyboard_process_input_25\n\t"
      ".Lvirtual_keyboard_process_input_23:\n\t"
      "cmpw $0x7fff, %%ax\n\t"
      "jne .Lvirtual_keyboard_process_input_25\n\t"
      ".Lvirtual_keyboard_process_input_24:\n\t"
      "movl $1, %%esi\n\t"
      ".Lvirtual_keyboard_process_input_25:\n\t"
      "leal -0x8(%%ebp), %%edx\n\t"
      "pushl $-1\n\t"
      "pushl %%edx\n\t"
      "call *%[cdc250]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lvirtual_keyboard_process_input_1\n\t"
      "cmpl $-1, %%esi\n\t"
      "je .Lvirtual_keyboard_process_input_34\n\t"
      "movswl 0x46cef8, %%eax\n\t"
      "movswl 0x46cefa, %%ecx\n\t"
      "imull $0xb, %%eax, %%eax\n\t"
      "cmpl $5, %%esi\n\t"
      "movsbw 0x28a790(%%eax,%%ecx,1), %%dx\n\t"
      "movw %%dx, 0x46cf00\n\t"
      "ja .Lvirtual_keyboard_process_input_33\n\t"
      "jmp *.Lvirtual_keyboard_process_input_jt1(,%%esi,4)\n\t"
      ".Lvirtual_keyboard_process_input_26:\n\t"
      "call *%[cf5660]\n\t"
      "jmp .Lvirtual_keyboard_process_input_32\n\t"
      ".Lvirtual_keyboard_process_input_27:\n\t"
      "call *%[cf56b0]\n\t"
      "jmp .Lvirtual_keyboard_process_input_32\n\t"
      ".Lvirtual_keyboard_process_input_28:\n\t"
      "call *%[cf5700]\n\t"
      "jmp .Lvirtual_keyboard_process_input_32\n\t"
      ".Lvirtual_keyboard_process_input_29:\n\t"
      "call *%[cf5750]\n\t"
      "jmp .Lvirtual_keyboard_process_input_32\n\t"
      ".Lvirtual_keyboard_process_input_30:\n\t"
      "call *%[cf5fb0]\n\t"
      "jmp .Lvirtual_keyboard_process_input_32\n\t"
      ".Lvirtual_keyboard_process_input_31:\n\t"
      "call *%[cf57a0]\n\t"
      ".Lvirtual_keyboard_process_input_32:\n\t"
      "movb %%al, %%bl\n\t"
      ".Lvirtual_keyboard_process_input_33:\n\t"
      "cmpb $1, %%bl\n\t"
      "jne .Lvirtual_keyboard_process_input_34\n\t"
      "movl %%edi, 0x46cf10\n\t"
      "movw %%si, 0x46cefe\n\t"
      ".Lvirtual_keyboard_process_input_34:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "movl %%edi, %%edi\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".Lvirtual_keyboard_process_input_jt0:\n\t"
      ".long .Lvirtual_keyboard_process_input_2\n\t"
      ".long .Lvirtual_keyboard_process_input_3\n\t"
      ".long .Lvirtual_keyboard_process_input_13\n\t"
      ".long .Lvirtual_keyboard_process_input_25\n\t"
      ".long .Lvirtual_keyboard_process_input_25\n\t"
      ".long .Lvirtual_keyboard_process_input_25\n\t"
      ".long .Lvirtual_keyboard_process_input_16\n\t"
      ".long .Lvirtual_keyboard_process_input_19\n\t"
      ".long .Lvirtual_keyboard_process_input_4\n\t"
      ".long .Lvirtual_keyboard_process_input_8\n\t"
      ".long .Lvirtual_keyboard_process_input_6\n\t"
      ".long .Lvirtual_keyboard_process_input_10\n\t"
      ".long .Lvirtual_keyboard_process_input_12\n\t"
      ".long .Lvirtual_keyboard_process_input_3\n\t"
      ".text\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".Lvirtual_keyboard_process_input_jt1:\n\t"
      ".long .Lvirtual_keyboard_process_input_26\n\t"
      ".long .Lvirtual_keyboard_process_input_27\n\t"
      ".long .Lvirtual_keyboard_process_input_28\n\t"
      ".long .Lvirtual_keyboard_process_input_29\n\t"
      ".long .Lvirtual_keyboard_process_input_30\n\t"
      ".long .Lvirtual_keyboard_process_input_31\n\t"
      ".text\n\t"
      :
      : [c8e370] "m"(bf63f0_c8e370), [cdc250] "m"(bf63f0_cdc250), [assert] "m"(bf63f0_assert), [exitfn] "m"(bf63f0_exitfn), [memset] "m"(bf63f0_memset), [ce5ab0] "m"(bf63f0_ce5ab0), [cf5f30] "m"(bf63f0_cf5f30), [cf5660] "m"(bf63f0_cf5660), [cf56b0] "m"(bf63f0_cf56b0), [cf5700] "m"(bf63f0_cf5700), [cf5750] "m"(bf63f0_cf5750), [cf5fb0] "m"(bf63f0_cf5fb0), [cf57a0] "m"(bf63f0_cf57a0)
      : "memory");
}
#else
#error "virtual_keyboard_process_input: clang naked draft required"
#endif


/* items_dispose_from_old_map (0xf6740) — readable C lift from XBE leaf. */
void items_dispose_from_old_map(void)
{
  if (*(char *)0x46cef0)
    virtual_keyboard_process_input();
}

/* FUN_000f6750 (0xf6750) — readable C lift. */
void FUN_000f6750(int item_handle, void *definition)
{
  char *item;
  uint32_t flags;

  item = (char *)object_get_and_verify_type(item_handle, 8);
  flags = *(uint32_t *)(item + 4);
  if ((*(uint8_t *)((char *)definition + 0x22) & 1) != 0)
    flags |= 0x20u;
  else
    flags &= ~0x20u;
  flags |= 0x60000u;
  *(uint32_t *)(item + 4) = flags;
  if ((*(uint8_t *)((char *)definition + 0x22) & 4) == 0)
    *(uint32_t *)(item + 0x1a4) |= 0x20u;
  else
    *(uint32_t *)(item + 0x1a4) &= ~0x20u;
  if ((*(uint8_t *)((char *)definition + 0x22) & 1) == 0)
    *(float *)(item + 0x14) = *(float *)(item + 0x14) + *(float *)0x2533e8;
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

/* item_new (0xf6820) — XBE naked draft (batch 98). */
#if defined(__clang__)
static void *(*const bf6820_get)(int, int) = object_get_and_verify_type;
static void (*const bf6820_odel)(int) = object_delete;

__attribute__((naked, noinline))
char item_new(int object_handle __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "pushl $0x10\n\t"
      "pushl %%esi\n\t"
      "call *%[get]\n\t"
      "addl $8, %%esp\n\t"
      "decw 0x1dc(%%eax)\n\t"
      "movw 0x1dc(%%eax), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "setg %%bl\n\t"
      "testb %%bl, %%bl\n\t"
      "jne .Litem_new_1\n\t"
      "pushl %%esi\n\t"
      "call *%[odel]\n\t"
      "addl $4, %%esp\n\t"
      ".Litem_new_1:\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [get] "m"(bf6820_get), [odel] "m"(bf6820_odel)
      : "memory");
}
#else
#error "item_new: clang naked draft required"
#endif


/* item_begin_garbage_collection (0xf6860) — XBE naked draft (batch 96). */
#if defined(__clang__)
static void *(*const bf6860_get)(int, int) = object_get_and_verify_type;
static void (*const bf6860_garb)(int, int) = object_set_garbage_flag;
static int *(*const bf6860_gseed)(void) = get_global_random_seed_address;
static int16_t (*const bf6860_c10b2d0)(unsigned int *seed, int16_t min, int16_t max) = random_range;

__attribute__((naked, noinline))
bool item_begin_garbage_collection(int item_handle __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "pushl $0x10\n\t"
      "pushl %%edi\n\t"
      "call *%[get]\n\t"
      "pushl $1\n\t"
      "pushl %%edi\n\t"
      "movl %%eax, %%esi\n\t"
      "call *%[garb]\n\t"
      "movl 0x4(%%esi), %%ecx\n\t"
      "addl $0x10, %%esp\n\t"
      "orl $0xc0000, %%ecx\n\t"
      "pushl $0x258\n\t"
      "pushl $0x12c\n\t"
      "movl %%ecx, 0x4(%%esi)\n\t"
      "call *%[gseed]\n\t"
      "pushl %%eax\n\t"
      "call *%[c10b2d0]\n\t"
      "addl $0xc, %%esp\n\t"
      "movw %%ax, 0x1dc(%%esi)\n\t"
      "popl %%edi\n\t"
      "movb $1, %%al\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [get] "m"(bf6860_get), [garb] "m"(bf6860_garb), [gseed] "m"(bf6860_gseed), [c10b2d0] "m"(bf6860_c10b2d0)
      : "memory");
}
#else
#error "item_begin_garbage_collection: clang naked draft required"
#endif


/* FUN_000f68b0 (0xf68b0) — readable C lift from XBE leaf. */
short FUN_000f68b0(int item_handle)
{
  unsigned char *item;
  item = (unsigned char *)datum_get(*(data_t **)0x5a8d50, item_handle);
  return (short)item[3];
}

/* item_activate (0xf6910) — readable C lift from XBE leaf. */
char item_activate(int item_handle)
{
  int *obj;
  obj = (int *)object_get_and_verify_type(item_handle, 0x1c);
  obj[1] = obj[1] | 0x6000;
  obj[0x1b4/4] = game_time_get();
  obj[0x1b0/4] = -1;
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

/* FUN_000f6b80 (0xf6b80) — XBE naked draft (batch 65). */
#if defined(__clang__)
static void *(*const bf6b80_get)(int, int) = object_get_and_verify_type;

__attribute__((naked, noinline))
void FUN_000f6b80(int item_handle __attribute__((unused)))
{
  __asm__ volatile(
      "pushl $0x1c\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%ecx\n\t"
      "flds 0x44(%%ecx)\n\t"
      "addl $8, %%esp\n\t"
      "flds 0x40(%%ecx)\n\t"
      "flds 0x3c(%%ecx)\n\t"
      "fld %%st(0)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fld %%st(2)\n\t"
      "fmul %%st(3), %%st(0)\n\t"
      "faddp %%st(1)\n\t"
      "fld %%st(3)\n\t"
      "fmul %%st(4), %%st(0)\n\t"
      "faddp %%st(1)\n\t"
      "fsqrt\n\t"
      "fstp %%st(3)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "fcoms 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .LFUN_000f6b80_2\n\t"
      "movl 0x1a4(%%ecx), %%edx\n\t"
      "movb 0x4(%%ecx), %%al\n\t"
      "orl $4, %%edx\n\t"
      "testb $0x20, %%al\n\t"
      "movl %%edx, 0x1a4(%%ecx)\n\t"
      "jne .LFUN_000f6b80_1\n\t"
      "flds 0x2533c8\n\t"
      "fdiv %%st(1), %%st(0)\n\t"
      "fld %%st(0)\n\t"
      "fmuls 0x3c(%%ecx)\n\t"
      "fstps 0x1c8(%%ecx)\n\t"
      "fld %%st(0)\n\t"
      "fmuls 0x40(%%ecx)\n\t"
      "fstps 0x1cc(%%ecx)\n\t"
      "fmuls 0x44(%%ecx)\n\t"
      "fstps 0x1d0(%%ecx)\n\t"
      ".LFUN_000f6b80_1:\n\t"
      "fld %%st(0)\n\t"
      "fsin\n\t"
      "fstps 0x1d4(%%ecx)\n\t"
      "fcos\n\t"
      "fstps 0x1d8(%%ecx)\n\t"
      "ret\n\t"
      ".LFUN_000f6b80_2:\n\t"
      "movl 0x1a4(%%ecx), %%eax\n\t"
      "fstp %%st(0)\n\t"
      "andl $0xfffffffb, %%eax\n\t"
      "movl %%eax, 0x1a4(%%ecx)\n\t"
      "movl $0, 0x1d4(%%ecx)\n\t"
      "movl $0x3f800000, 0x1d8(%%ecx)\n\t"
      "ret\n\t"
      :
      : [get] "m"(bf6b80_get)
      : "memory");
}
#else
#error "FUN_000f6b80: clang naked draft required"
#endif


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

/* valid_real_matrix4x3 (0xf6d00) — XBE naked draft (batch 69). */
#if defined(__clang__)
static char (*const bf6d00_cf6c40)(float *a, float *b, float *c) = valid_real_vector3d_axes3;
static bool (*const bf6d00_ca16b0)(float *point) = valid_real_point3d;

__attribute__((naked, noinline))
char valid_real_matrix4x3(float *mat __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "movl (%%esi), %%eax\n\t"
      "movl %%eax, %%ecx\n\t"
      "andl $0x7f800000, %%ecx\n\t"
      "cmpl $0x7f800000, %%ecx\n\t"
      "movl %%eax, 0x8(%%ebp)\n\t"
      "je .Lvalid_real_matrix4x3_1\n\t"
      "leal 0x1c(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal 0x10(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal 0x4(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[cf6c40]\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lvalid_real_matrix4x3_1\n\t"
      "addl $0x28, %%esi\n\t"
      "pushl %%esi\n\t"
      "call *%[ca16b0]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lvalid_real_matrix4x3_1\n\t"
      "movl $1, %%eax\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lvalid_real_matrix4x3_1:\n\t"
      "xorl %%eax, %%eax\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [cf6c40] "m"(bf6d00_cf6c40), [ca16b0] "m"(bf6d00_ca16b0)
      : "memory");
}
#else
#error "valid_real_matrix4x3: clang naked draft required"
#endif


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

/* FUN_000f4ea0 (0xf4ea0) — XBE naked draft (batch 58). */
#if defined(__clang__)
static void *(*const bf4ea0_tag)(int, int) = tag_get;
static int (*const bf4ea0_c1b9b00)(int tag_class, const char *name, int flags) = FUN_001b9b00;
static void (*const bf4ea0_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;
static void (*const bf4ea0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const bf4ea0_exitfn)(int) = system_exit;

__attribute__((naked, noinline))
void FUN_000f4ea0(int scenario_tag_index __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "pushl $0x73636e72\n\t"
      "call *%[tag]\n\t"
      "pushl $0\n\t"
      "pushl $0x288db8\n\t"
      "pushl $0x75737472\n\t"
      "movl %%eax, %%esi\n\t"
      "call *%[c1b9b00]\n\t"
      "addl $0x14, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "jne .LFUN_000f4ea0_1\n\t"
      "pushl $0x28a6f4\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_000f4ea0_1:\n\t"
      "pushl $0\n\t"
      "pushl $0x28a6dc\n\t"
      "pushl $0x6269746d\n\t"
      "call *%[c1b9b00]\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "jne .LFUN_000f4ea0_2\n\t"
      "pushl $0x28a6bc\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_000f4ea0_2:\n\t"
      "movswl 0x3c(%%esi), %%eax\n\t"
      "subl $0, %%eax\n\t"
      "popl %%esi\n\t"
      "je .LFUN_000f4ea0_23\n\t"
      "decl %%eax\n\t"
      "je .LFUN_000f4ea0_22\n\t"
      "decl %%eax\n\t"
      "je .LFUN_000f4ea0_3\n\t"
      "pushl $1\n\t"
      "pushl $0x1f5\n\t"
      "pushl $0x28a690\n\t"
      "pushl $0x28a678\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000f4ea0_3:\n\t"
      "pushl $0\n\t"
      "pushl $0x28a664\n\t"
      "pushl $0x536f756c\n\t"
      "call *%[c1b9b00]\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "jne .LFUN_000f4ea0_4\n\t"
      "pushl $0x28a624\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_000f4ea0_4:\n\t"
      "pushl $0\n\t"
      "pushl $0x28a618\n\t"
      "pushl $0x76636b79\n\t"
      "call *%[c1b9b00]\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "jne .LFUN_000f4ea0_5\n\t"
      "pushl $0x28a5e4\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_000f4ea0_5:\n\t"
      "pushl $0\n\t"
      "pushl $0x28a5cc\n\t"
      "pushl $0x75737472\n\t"
      "call *%[c1b9b00]\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "jne .LFUN_000f4ea0_6\n\t"
      "pushl $0x28a598\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_000f4ea0_6:\n\t"
      "pushl $0\n\t"
      "pushl $0x28a57c\n\t"
      "pushl $0x6d706c79\n\t"
      "call *%[c1b9b00]\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "jne .LFUN_000f4ea0_7\n\t"
      "pushl $0x28a544\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_000f4ea0_7:\n\t"
      "pushl $0\n\t"
      "pushl $0x28a528\n\t"
      "pushl $0x75737472\n\t"
      "call *%[c1b9b00]\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "jne .LFUN_000f4ea0_8\n\t"
      "pushl $0x28a4e8\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_000f4ea0_8:\n\t"
      "pushl $0\n\t"
      "pushl $0x28a4bc\n\t"
      "pushl $0x75737472\n\t"
      "call *%[c1b9b00]\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "jne .LFUN_000f4ea0_9\n\t"
      "pushl $0x28a478\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_000f4ea0_9:\n\t"
      "pushl $0\n\t"
      "pushl $0x2898a4\n\t"
      "pushl $0x75737472\n\t"
      "call *%[c1b9b00]\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "jne .LFUN_000f4ea0_10\n\t"
      "pushl $0x28a430\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_000f4ea0_10:\n\t"
      "pushl $0\n\t"
      "pushl $0x28a3f0\n\t"
      "pushl $0x75737472\n\t"
      "call *%[c1b9b00]\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "jne .LFUN_000f4ea0_11\n\t"
      "pushl $0x28a3b8\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_000f4ea0_11:\n\t"
      "pushl $0\n\t"
      "pushl $0x2898d0\n\t"
      "pushl $0x75737472\n\t"
      "call *%[c1b9b00]\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "jne .LFUN_000f4ea0_12\n\t"
      "pushl $0x28a378\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_000f4ea0_12:\n\t"
      "pushl $0\n\t"
      "pushl $0x289cb8\n\t"
      "pushl $0x75737472\n\t"
      "call *%[c1b9b00]\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "jne .LFUN_000f4ea0_13\n\t"
      "pushl $0x28a328\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_000f4ea0_13:\n\t"
      "pushl $0\n\t"
      "pushl $0x289c10\n\t"
      "pushl $0x75737472\n\t"
      "call *%[c1b9b00]\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "jne .LFUN_000f4ea0_14\n\t"
      "pushl $0x28a2e0\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_000f4ea0_14:\n\t"
      "pushl $0\n\t"
      "pushl $0x289d00\n\t"
      "pushl $0x75737472\n\t"
      "call *%[c1b9b00]\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "jne .LFUN_000f4ea0_15\n\t"
      "pushl $0x28a288\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_000f4ea0_15:\n\t"
      "pushl $0\n\t"
      "pushl $0x289c58\n\t"
      "pushl $0x75737472\n\t"
      "call *%[c1b9b00]\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "jne .LFUN_000f4ea0_16\n\t"
      "pushl $0x28a230\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_000f4ea0_16:\n\t"
      "pushl $0\n\t"
      "pushl $0x289780\n\t"
      "pushl $0x75737472\n\t"
      "call *%[c1b9b00]\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "jne .LFUN_000f4ea0_17\n\t"
      "pushl $0x28a1e8\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_000f4ea0_17:\n\t"
      "pushl $0\n\t"
      "pushl $0x28380c\n\t"
      "pushl $0x736e6421\n\t"
      "call *%[c1b9b00]\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "jne .LFUN_000f4ea0_18\n\t"
      "pushl $0x28a1c0\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_000f4ea0_18:\n\t"
      "pushl $0\n\t"
      "pushl $0x2837f4\n\t"
      "pushl $0x736e6421\n\t"
      "call *%[c1b9b00]\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "jne .LFUN_000f4ea0_19\n\t"
      "pushl $0x28a19c\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_000f4ea0_19:\n\t"
      "pushl $0\n\t"
      "pushl $0x2837e0\n\t"
      "pushl $0x736e6421\n\t"
      "call *%[c1b9b00]\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "jne .LFUN_000f4ea0_20\n\t"
      "pushl $0x28a178\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_000f4ea0_20:\n\t"
      "pushl $0\n\t"
      "pushl $0x2837c4\n\t"
      "pushl $0x736e6421\n\t"
      "call *%[c1b9b00]\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "jne .LFUN_000f4ea0_21\n\t"
      "pushl $0x28a154\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_000f4ea0_21:\n\t"
      "pushl $0\n\t"
      "pushl $0x2834e0\n\t"
      "pushl $0x6c736e64\n\t"
      "call *%[c1b9b00]\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "jne .LFUN_000f4ea0_24\n\t"
      "pushl $0x28a12c\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000f4ea0_22:\n\t"
      "pushl $0\n\t"
      "pushl $0x28a114\n\t"
      "pushl $0x536f756c\n\t"
      "call *%[c1b9b00]\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "jne .LFUN_000f4ea0_24\n\t"
      "pushl $0x28a0d0\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000f4ea0_23:\n\t"
      "pushl $0\n\t"
      "pushl $0x28a0c0\n\t"
      "pushl $0x536f756c\n\t"
      "call *%[c1b9b00]\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "jne .LFUN_000f4ea0_24\n\t"
      "pushl $0x28a084\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_000f4ea0_24:\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [tag] "m"(bf4ea0_tag), [c1b9b00] "m"(bf4ea0_c1b9b00), [c8f390] "m"(bf4ea0_c8f390), [assert] "m"(bf4ea0_assert), [exitfn] "m"(bf4ea0_exitfn)
      : "memory");
}
#else
#error "FUN_000f4ea0: clang naked draft required"
#endif

/* --- items.obj batch drafts (2026-07-26) --- */

/* multiplayer_settings_select_list_update_item (0xf4210) — XBE naked draft (batch 221). */
#if defined(__clang__)
static void *(*const bf4210_tag)(int, int) = tag_get;
static void (*const bf4210_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const bf4210_exitfn)(int) = system_exit;
static void (*const bf4210_cf3690)(int *out_handles /* */, void *widget /* */) = FUN_000f3690;
static void (*const bf4210_cf3740)(int *handles, int count) = multiplayer_game_set_text_box_for_game_ruleset;
static void * (*const bf4210_ce3cd0)(void *widget, int index) = widget_instance_get_nth_child;
static void * (*const bf4210_ce3d20)(int a1, unsigned short a2, const char *a3, unsigned int a4) = ui_widget_realloc;
static int (*const bf4210_c1b9930)(int group_tag, const char *name, ...) = tag_loaded;
static int (*const bf4210_c19d420)(int param_1, int param_2) = FUN_0019d420;
static wchar_t * (*const bf4210_c19dc90)(wchar_t *dest, wchar_t *src, size_t count) = ustrncpy;
static unsigned short (*const bf4210_c1c0ed0)(void) = FUN_001c0ed0;
static void (*const bf4210_c1c0f70)(void *profile, short *out_level, short *out_difficulty) = player_profile_save_last_level_played;

__attribute__((naked, noinline))
void multiplayer_settings_select_list_update_item(void *widget __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x40, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "orl $0xffffffff, %%eax\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "movl %%eax, -0x34(%%ebp)\n\t"
      "movl %%eax, -0x30(%%ebp)\n\t"
      "movl %%eax, -0x2c(%%ebp)\n\t"
      "movl (%%edi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x44654c61\n\t"
      "call *%[tag]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $2, (%%esi)\n\t"
      "movl $1, %%ebx\n\t"
      "je .Lmultiplayer_settings_select_list_update_item_1\n\t"
      "pushl %%ebx\n\t"
      "pushl $0x78a\n\t"
      "pushl $0x288938\n\t"
      "pushl $0x289bd0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lmultiplayer_settings_select_list_update_item_1:\n\t"
      "cmpl $3, 0x3e0(%%esi)\n\t"
      "je .Lmultiplayer_settings_select_list_update_item_2\n\t"
      "pushl %%ebx\n\t"
      "pushl $0x78b\n\t"
      "pushl $0x288938\n\t"
      "pushl $0x289b88\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lmultiplayer_settings_select_list_update_item_2:\n\t"
      "leal -0x34(%%ebp), %%eax\n\t"
      "movl %%edi, %%ecx\n\t"
      "call *%[cf3690]\n\t"
      "xorl %%eax, %%eax\n\t"
      "orl $0xffffffff, %%edx\n\t"
      "jmp .Lmultiplayer_settings_select_list_update_item_3\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".Lmultiplayer_settings_select_list_update_item_3:\n\t"
      "movl -0x34(%%ebp,%%eax,1), %%ecx\n\t"
      "cmpl %%edx, %%ecx\n\t"
      "je .Lmultiplayer_settings_select_list_update_item_4\n\t"
      "movl 0x40(%%edi), %%esi\n\t"
      "movl (%%esi,%%ecx,4), %%ecx\n\t"
      "movl %%ecx, -0x40(%%ebp,%%eax,1)\n\t"
      "jmp .Lmultiplayer_settings_select_list_update_item_5\n\t"
      ".Lmultiplayer_settings_select_list_update_item_4:\n\t"
      "movl %%edx, -0x40(%%ebp,%%eax,1)\n\t"
      ".Lmultiplayer_settings_select_list_update_item_5:\n\t"
      "addl $4, %%eax\n\t"
      "cmpl $0xc, %%eax\n\t"
      "jl .Lmultiplayer_settings_select_list_update_item_3\n\t"
      "leal -0x40(%%ebp), %%edx\n\t"
      "pushl $3\n\t"
      "pushl %%edx\n\t"
      "call *%[cf3740]\n\t"
      "addl $8, %%esp\n\t"
      "xorl %%eax, %%eax\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "jmp .Lmultiplayer_settings_select_list_update_item_7\n\t"
      ".Lmultiplayer_settings_select_list_update_item_6:\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "movl $1, %%ebx\n\t"
      ".Lmultiplayer_settings_select_list_update_item_7:\n\t"
      "cmpl $-1, -0x34(%%ebp,%%eax,4)\n\t"
      "je .Lmultiplayer_settings_select_list_update_item_46\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "call *%[ce3cd0]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $8, %%esp\n\t"
      "testl %%esi, %%esi\n\t"
      "je .Lmultiplayer_settings_select_list_update_item_8\n\t"
      "cmpw $0, 0xe(%%esi)\n\t"
      "je .Lmultiplayer_settings_select_list_update_item_9\n\t"
      ".Lmultiplayer_settings_select_list_update_item_8:\n\t"
      "pushl %%ebx\n\t"
      "pushl $0x7af\n\t"
      "pushl $0x288938\n\t"
      "pushl $0x289b54\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lmultiplayer_settings_select_list_update_item_9:\n\t"
      "movl 0x34(%%esi), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "je .Lmultiplayer_settings_select_list_update_item_10\n\t"
      "cmpw %%bx, 0xe(%%edi)\n\t"
      "je .Lmultiplayer_settings_select_list_update_item_11\n\t"
      ".Lmultiplayer_settings_select_list_update_item_10:\n\t"
      "pushl %%ebx\n\t"
      "pushl $0x7b2\n\t"
      "pushl $0x288938\n\t"
      "pushl $0x289b28\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lmultiplayer_settings_select_list_update_item_11:\n\t"
      "movl 0x2c(%%edi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%esi, -0x1c(%%ebp)\n\t"
      "je .Lmultiplayer_settings_select_list_update_item_12\n\t"
      "cmpw $0, 0xe(%%esi)\n\t"
      "je .Lmultiplayer_settings_select_list_update_item_13\n\t"
      ".Lmultiplayer_settings_select_list_update_item_12:\n\t"
      "pushl %%ebx\n\t"
      "pushl $0x7b5\n\t"
      "pushl $0x288938\n\t"
      "pushl $0x289aec\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lmultiplayer_settings_select_list_update_item_13:\n\t"
      "movl 0x2c(%%esi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .Lmultiplayer_settings_select_list_update_item_14\n\t"
      "cmpw $0, 0xe(%%esi)\n\t"
      "je .Lmultiplayer_settings_select_list_update_item_15\n\t"
      ".Lmultiplayer_settings_select_list_update_item_14:\n\t"
      "pushl %%ebx\n\t"
      "pushl $0x7b8\n\t"
      "pushl $0x288938\n\t"
      "pushl $0x289aac\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lmultiplayer_settings_select_list_update_item_15:\n\t"
      "movl 0x34(%%esi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%esi, -0x20(%%ebp)\n\t"
      "je .Lmultiplayer_settings_select_list_update_item_16\n\t"
      "cmpw %%bx, 0xe(%%esi)\n\t"
      "je .Lmultiplayer_settings_select_list_update_item_17\n\t"
      ".Lmultiplayer_settings_select_list_update_item_16:\n\t"
      "pushl %%ebx\n\t"
      "pushl $0x7bb\n\t"
      "pushl $0x288938\n\t"
      "pushl $0x289a70\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lmultiplayer_settings_select_list_update_item_17:\n\t"
      "movl 0x2c(%%esi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%esi, -0x24(%%ebp)\n\t"
      "je .Lmultiplayer_settings_select_list_update_item_18\n\t"
      "cmpw %%bx, 0xe(%%esi)\n\t"
      "je .Lmultiplayer_settings_select_list_update_item_19\n\t"
      ".Lmultiplayer_settings_select_list_update_item_18:\n\t"
      "pushl %%ebx\n\t"
      "pushl $0x7be\n\t"
      "pushl $0x288938\n\t"
      "pushl $0x289a38\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lmultiplayer_settings_select_list_update_item_19:\n\t"
      "movl 0x2c(%%esi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%esi, -0x8(%%ebp)\n\t"
      "je .Lmultiplayer_settings_select_list_update_item_20\n\t"
      "cmpw %%bx, 0xe(%%esi)\n\t"
      "je .Lmultiplayer_settings_select_list_update_item_21\n\t"
      ".Lmultiplayer_settings_select_list_update_item_20:\n\t"
      "pushl %%ebx\n\t"
      "pushl $0x7c1\n\t"
      "pushl $0x288938\n\t"
      "pushl $0x2899fc\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lmultiplayer_settings_select_list_update_item_21:\n\t"
      "movl 0x2c(%%esi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%esi, -0x28(%%ebp)\n\t"
      "je .Lmultiplayer_settings_select_list_update_item_22\n\t"
      "cmpw %%bx, 0xe(%%esi)\n\t"
      "je .Lmultiplayer_settings_select_list_update_item_23\n\t"
      ".Lmultiplayer_settings_select_list_update_item_22:\n\t"
      "pushl %%ebx\n\t"
      "pushl $0x7c4\n\t"
      "pushl $0x288938\n\t"
      "pushl $0x2899bc\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lmultiplayer_settings_select_list_update_item_23:\n\t"
      "movl 0x2c(%%esi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%esi, -0xc(%%ebp)\n\t"
      "je .Lmultiplayer_settings_select_list_update_item_24\n\t"
      "cmpw %%bx, 0xe(%%esi)\n\t"
      "je .Lmultiplayer_settings_select_list_update_item_25\n\t"
      ".Lmultiplayer_settings_select_list_update_item_24:\n\t"
      "pushl %%ebx\n\t"
      "pushl $0x7c7\n\t"
      "pushl $0x288938\n\t"
      "pushl $0x289970\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lmultiplayer_settings_select_list_update_item_25:\n\t"
      "movl 0x2c(%%esi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .Lmultiplayer_settings_select_list_update_item_26\n\t"
      "cmpw %%bx, 0xe(%%esi)\n\t"
      "je .Lmultiplayer_settings_select_list_update_item_27\n\t"
      ".Lmultiplayer_settings_select_list_update_item_26:\n\t"
      "pushl %%ebx\n\t"
      "pushl $0x7ca\n\t"
      "pushl $0x288938\n\t"
      "pushl $0x289938\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lmultiplayer_settings_select_list_update_item_27:\n\t"
      "movl 0x2c(%%esi), %%ebx\n\t"
      "testl %%ebx, %%ebx\n\t"
      "movl %%ebx, -0x18(%%ebp)\n\t"
      "je .Lmultiplayer_settings_select_list_update_item_28\n\t"
      "cmpw $1, 0xe(%%ebx)\n\t"
      "je .Lmultiplayer_settings_select_list_update_item_29\n\t"
      ".Lmultiplayer_settings_select_list_update_item_28:\n\t"
      "pushl $1\n\t"
      "pushl $0x7cd\n\t"
      "pushl $0x288938\n\t"
      "pushl $0x289900\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lmultiplayer_settings_select_list_update_item_29:\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl -0x10(%%ebp), %%edx\n\t"
      "movl 0x40(%%eax), %%ecx\n\t"
      "movl -0x34(%%ebp,%%edx,4), %%eax\n\t"
      "movl (%%ecx,%%eax,4), %%edx\n\t"
      "cmpl $-1, %%edx\n\t"
      "je .Lmultiplayer_settings_select_list_update_item_44\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movl $0x5aa3c0, %%eax\n\t"
      ".Lmultiplayer_settings_select_list_update_item_30:\n\t"
      "cmpl %%edx, (%%eax)\n\t"
      "je .Lmultiplayer_settings_select_list_update_item_31\n\t"
      "addl $0x34, %%eax\n\t"
      "incl %%ecx\n\t"
      "cmpl $0x5aa45c, %%eax\n\t"
      "jl .Lmultiplayer_settings_select_list_update_item_30\n\t"
      "jmp .Lmultiplayer_settings_select_list_update_item_44\n\t"
      ".Lmultiplayer_settings_select_list_update_item_31:\n\t"
      "imull $0x34, %%ecx, %%ecx\n\t"
      "addl $0x5aa3c4, %%ecx\n\t"
      "movl %%ecx, %%ebx\n\t"
      "je .Lmultiplayer_settings_select_list_update_item_43\n\t"
      "movl -0x20(%%ebp), %%eax\n\t"
      "movl -0x24(%%ebp), %%ecx\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "movb $1, 0x10(%%edi)\n\t"
      "movb $0, 0x10(%%eax)\n\t"
      "movl -0x28(%%ebp), %%eax\n\t"
      "movb $1, 0x10(%%ecx)\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "movb $1, 0x10(%%edx)\n\t"
      "movl -0x18(%%ebp), %%edx\n\t"
      "movb $1, 0x10(%%eax)\n\t"
      "movb $1, 0x10(%%ecx)\n\t"
      "pushl $0x7e7\n\t"
      "movb $1, 0x10(%%esi)\n\t"
      "pushl $0x288938\n\t"
      "movb $1, 0x10(%%edx)\n\t"
      "movl 0x3c(%%edi), %%eax\n\t"
      "pushl $0x18\n\t"
      "pushl %%eax\n\t"
      "call *%[ce3d20]\n\t"
      "addl $0x10, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%eax, 0x3c(%%edi)\n\t"
      "je .Lmultiplayer_settings_select_list_update_item_36\n\t"
      "movw 0x1a(%%ebx), %%cx\n\t"
      "testb $1, %%cl\n\t"
      "je .Lmultiplayer_settings_select_list_update_item_34\n\t"
      "movzwl %%cx, %%esi\n\t"
      "pushl $0x2898d0\n\t"
      "pushl $0x75737472\n\t"
      "shrl $8, %%esi\n\t"
      "call *%[c1b9930]\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lmultiplayer_settings_select_list_update_item_32\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "call *%[c19d420]\n\t"
      "addl $8, %%esp\n\t"
      "jmp .Lmultiplayer_settings_select_list_update_item_33\n\t"
      ".Lmultiplayer_settings_select_list_update_item_32:\n\t"
      "movl $0x281c38, %%eax\n\t"
      ".Lmultiplayer_settings_select_list_update_item_33:\n\t"
      "movl 0x3c(%%edi), %%ecx\n\t"
      "pushl $0xb\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c19dc90]\n\t"
      "movl 0x3c(%%edi), %%edx\n\t"
      "movw $0, 0x16(%%edx)\n\t"
      "jmp .Lmultiplayer_settings_select_list_update_item_35\n\t"
      ".Lmultiplayer_settings_select_list_update_item_34:\n\t"
      "pushl $0xb\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "call *%[c19dc90]\n\t"
      "movl 0x3c(%%edi), %%eax\n\t"
      "movw $0, 0x16(%%eax)\n\t"
      ".Lmultiplayer_settings_select_list_update_item_35:\n\t"
      "addl $0xc, %%esp\n\t"
      ".Lmultiplayer_settings_select_list_update_item_36:\n\t"
      "cmpw $0, 0x18(%%ebx)\n\t"
      "jge .Lmultiplayer_settings_select_list_update_item_37\n\t"
      "xorl %%eax, %%eax\n\t"
      "jmp .Lmultiplayer_settings_select_list_update_item_39\n\t"
      ".Lmultiplayer_settings_select_list_update_item_37:\n\t"
      "movswl 0x18(%%ebx), %%esi\n\t"
      "call *%[c1c0ed0]\n\t"
      "movzwl %%ax, %%ecx\n\t"
      "decl %%ecx\n\t"
      "cmpl %%ecx, %%esi\n\t"
      "jle .Lmultiplayer_settings_select_list_update_item_38\n\t"
      "call *%[c1c0ed0]\n\t"
      "movzwl %%ax, %%eax\n\t"
      "decl %%eax\n\t"
      "jmp .Lmultiplayer_settings_select_list_update_item_39\n\t"
      ".Lmultiplayer_settings_select_list_update_item_38:\n\t"
      "movl %%esi, %%eax\n\t"
      ".Lmultiplayer_settings_select_list_update_item_39:\n\t"
      "movl -0x1c(%%ebp), %%edx\n\t"
      "movw %%ax, 0x50(%%edx)\n\t"
      "testb $1, 0x1a(%%ebx)\n\t"
      "je .Lmultiplayer_settings_select_list_update_item_40\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "movb $0, 0x10(%%eax)\n\t"
      "movb $0, 0x10(%%ecx)\n\t"
      "jmp .Lmultiplayer_settings_select_list_update_item_45\n\t"
      ".Lmultiplayer_settings_select_list_update_item_40:\n\t"
      "leal -0x4(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x14(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "call *%[c1c0f70]\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "movswl %%ax, %%ecx\n\t"
      "addl $0xc, %%esp\n\t"
      "incl %%ecx\n\t"
      "cmpl $9, %%ecx\n\t"
      "jle .Lmultiplayer_settings_select_list_update_item_41\n\t"
      "movl $9, %%eax\n\t"
      "jmp .Lmultiplayer_settings_select_list_update_item_42\n\t"
      ".Lmultiplayer_settings_select_list_update_item_41:\n\t"
      "incl %%eax\n\t"
      ".Lmultiplayer_settings_select_list_update_item_42:\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "movw %%ax, 0x40(%%edx)\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "movw -0x4(%%ebp), %%ax\n\t"
      "movw %%ax, 0x40(%%ecx)\n\t"
      "movb 0x2b(%%ebx), %%al\n\t"
      "xorl %%edx, %%edx\n\t"
      "cmpb $1, %%al\n\t"
      "movl -0x18(%%ebp), %%eax\n\t"
      "sete %%dl\n\t"
      "movw %%dx, 0x40(%%eax)\n\t"
      "jmp .Lmultiplayer_settings_select_list_update_item_45\n\t"
      ".Lmultiplayer_settings_select_list_update_item_43:\n\t"
      "movl -0x18(%%ebp), %%ebx\n\t"
      ".Lmultiplayer_settings_select_list_update_item_44:\n\t"
      "movb $0, 0x10(%%edi)\n\t"
      "call *%[c1c0ed0]\n\t"
      "movl -0x1c(%%ebp), %%ecx\n\t"
      "movl -0x20(%%ebp), %%edx\n\t"
      "movw %%ax, 0x50(%%ecx)\n\t"
      "movl -0x24(%%ebp), %%eax\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movb $1, 0x10(%%edx)\n\t"
      "movl -0x28(%%ebp), %%edx\n\t"
      "movb $0, 0x10(%%eax)\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "movb $0, 0x10(%%ecx)\n\t"
      "movb $0, 0x10(%%edx)\n\t"
      "movb $0, 0x10(%%eax)\n\t"
      "movb $0, 0x10(%%esi)\n\t"
      "movb $0, 0x10(%%ebx)\n\t"
      ".Lmultiplayer_settings_select_list_update_item_45:\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "incl %%eax\n\t"
      "cmpl $3, %%eax\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "jl .Lmultiplayer_settings_select_list_update_item_6\n\t"
      ".Lmultiplayer_settings_select_list_update_item_46:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
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
      :
      : [tag] "m"(bf4210_tag), [assert] "m"(bf4210_assert), [exitfn] "m"(bf4210_exitfn), [cf3690] "m"(bf4210_cf3690), [cf3740] "m"(bf4210_cf3740), [ce3cd0] "m"(bf4210_ce3cd0), [ce3d20] "m"(bf4210_ce3d20), [c1b9930] "m"(bf4210_c1b9930), [c19d420] "m"(bf4210_c19d420), [c19dc90] "m"(bf4210_c19dc90), [c1c0ed0] "m"(bf4210_c1c0ed0), [c1c0f70] "m"(bf4210_c1c0f70)
      : "memory");
}
#else
#error "multiplayer_settings_select_list_update_item: clang naked draft required"
#endif


/* FUN_000f46e0 (0xf46e0) — XBE naked draft (batch 230). */
#if defined(__clang__)
static void (*const bf46e0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const bf46e0_exitfn)(int) = system_exit;
static void *(*const bf46e0_tag)(int, int) = tag_get;
static void (*const bf46e0_cf3740)(int *handles, int count) = multiplayer_game_set_text_box_for_game_ruleset;
static void __cdecl (*const bf46e0_c1d9260)(void *base, size_t nmemb, size_t size, int (__cdecl *compar)(const void *, const void *)) = qsort;
static void * (*const bf46e0_ce3d20)(int a1, unsigned short a2, const char *a3, unsigned int a4) = ui_widget_realloc;
static int (*const bf46e0_c1b9930)(int group_tag, const char *name, ...) = tag_loaded;
static int (*const bf46e0_c19d420)(int param_1, int param_2) = FUN_0019d420;
static wchar_t * (*const bf46e0_c19dc90)(wchar_t *dest, wchar_t *src, size_t count) = ustrncpy;
static unsigned short (*const bf46e0_c1c0ed0)(void) = FUN_001c0ed0;
static void (*const bf46e0_c19e9f0)(wchar_t *buffer, int buffer_size, const wchar_t *format, ...) = unicode_sprintf;

__attribute__((naked, noinline))
void FUN_000f46e0(void *widget __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $8, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_000f46e0_1:\n\t"
      "movl 0x30(%%edi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_000f46e0_2\n\t"
      "pushl $1\n\t"
      "pushl $0x85e\n\t"
      "pushl $0x288938\n\t"
      "pushl $0x289ea8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000f46e0_2:\n\t"
      "movl (%%edi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x44654c61\n\t"
      "call *%[tag]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $2, (%%esi)\n\t"
      "je .LFUN_000f46e0_3\n\t"
      "pushl $1\n\t"
      "pushl $0x864\n\t"
      "pushl $0x288938\n\t"
      "pushl $0x289e64\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000f46e0_3:\n\t"
      "movl 0x3e0(%%esi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_000f46e0_4\n\t"
      "pushl $1\n\t"
      "pushl $0x865\n\t"
      "pushl $0x288938\n\t"
      "pushl $0x289e18\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000f46e0_4:\n\t"
      "movl 0x30(%%edi), %%ecx\n\t"
      "movl (%%ecx), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x44654c61\n\t"
      "call *%[tag]\n\t"
      "movl 0x3e0(%%eax), %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $3, %%ecx\n\t"
      "je .LFUN_000f46e0_5\n\t"
      "pushl $1\n\t"
      "pushl $0x867\n\t"
      "pushl $0x288938\n\t"
      "pushl $0x289da0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000f46e0_5:\n\t"
      "movl 0x30(%%edi), %%eax\n\t"
      "movl 0x34(%%eax), %%eax\n\t"
      "movl 0x2c(%%eax), %%ebx\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "cmpl 0x2c(%%ebx), %%edi\n\t"
      "movl %%ebx, 0x8(%%ebp)\n\t"
      "je .LFUN_000f46e0_6\n\t"
      "pushl $1\n\t"
      "pushl $0x86d\n\t"
      "pushl $0x288938\n\t"
      "pushl $0x289da0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000f46e0_6:\n\t"
      "movw 0x3c(%%edi), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "jl .LFUN_000f46e0_7\n\t"
      "movzwl 0x44(%%edi), %%ecx\n\t"
      "movswl %%ax, %%edx\n\t"
      "cmpl %%ecx, %%edx\n\t"
      "jl .LFUN_000f46e0_8\n\t"
      ".LFUN_000f46e0_7:\n\t"
      "pushl $1\n\t"
      "pushl $0x86f\n\t"
      "pushl $0x288938\n\t"
      "pushl $0x289d68\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000f46e0_8:\n\t"
      "movw 0x3c(%%edi), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "jl .LFUN_000f46e0_9\n\t"
      "movzwl 0x44(%%edi), %%ecx\n\t"
      "movswl %%ax, %%edx\n\t"
      "cmpl %%ecx, %%edx\n\t"
      "jl .LFUN_000f46e0_10\n\t"
      ".LFUN_000f46e0_9:\n\t"
      "pushl $1\n\t"
      "pushl $0x872\n\t"
      "pushl $0x288938\n\t"
      "pushl $0x289d50\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000f46e0_10:\n\t"
      "movswl 0x3c(%%edi), %%eax\n\t"
      "movl 0x40(%%edi), %%ecx\n\t"
      "movl (%%ecx,%%eax,4), %%esi\n\t"
      "leal -0x8(%%ebp), %%edx\n\t"
      "pushl $1\n\t"
      "pushl %%edx\n\t"
      "movl %%esi, -0x8(%%ebp)\n\t"
      "call *%[cf3740]\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%esi\n\t"
      "je .LFUN_000f46e0_13\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movl $0x5aa3c0, %%eax\n\t"
      "leal (%%ebx), %%ebx\n\t"
      ".LFUN_000f46e0_11:\n\t"
      "cmpl %%esi, (%%eax)\n\t"
      "je .LFUN_000f46e0_12\n\t"
      "addl $0x34, %%eax\n\t"
      "incl %%ecx\n\t"
      "cmpl $0x5aa45c, %%eax\n\t"
      "jl .LFUN_000f46e0_11\n\t"
      "jmp .LFUN_000f46e0_13\n\t"
      ".LFUN_000f46e0_12:\n\t"
      "imull $0x34, %%ecx, %%ecx\n\t"
      "addl $0x5aa3c4, %%ecx\n\t"
      "movl %%ecx, %%esi\n\t"
      "jne .LFUN_000f46e0_18\n\t"
      ".LFUN_000f46e0_13:\n\t"
      "movw 0x44(%%edi), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "jbe .LFUN_000f46e0_29\n\t"
      "movl 0x40(%%edi), %%ebx\n\t"
      "pushl $0xf3960\n\t"
      "movzwl %%ax, %%esi\n\t"
      "pushl $4\n\t"
      "pushl %%esi\n\t"
      "pushl %%ebx\n\t"
      "call *%[c1d9260]\n\t"
      "addl $0x10, %%esp\n\t"
      "xorl %%eax, %%eax\n\t"
      "testl %%esi, %%esi\n\t"
      "jle .LFUN_000f46e0_15\n\t"
      ".LFUN_000f46e0_14:\n\t"
      "cmpl $-1, (%%ebx,%%eax,4)\n\t"
      "je .LFUN_000f46e0_15\n\t"
      "incl %%eax\n\t"
      "cmpl %%esi, %%eax\n\t"
      "jl .LFUN_000f46e0_14\n\t"
      ".LFUN_000f46e0_15:\n\t"
      "movw 0x3c(%%edi), %%cx\n\t"
      "testw %%cx, %%cx\n\t"
      "movw %%ax, 0x44(%%edi)\n\t"
      "jge .LFUN_000f46e0_16\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw %%ax, 0x3c(%%edi)\n\t"
      "jmp .LFUN_000f46e0_1\n\t"
      ".LFUN_000f46e0_16:\n\t"
      "movzwl %%ax, %%eax\n\t"
      "movswl %%cx, %%ecx\n\t"
      "decl %%eax\n\t"
      "cmpl %%eax, %%ecx\n\t"
      "jg .LFUN_000f46e0_17\n\t"
      "movl %%ecx, %%eax\n\t"
      ".LFUN_000f46e0_17:\n\t"
      "movw %%ax, 0x3c(%%edi)\n\t"
      "jmp .LFUN_000f46e0_1\n\t"
      ".LFUN_000f46e0_18:\n\t"
      "movl 0x4c(%%edi), %%eax\n\t"
      "pushl $0x886\n\t"
      "pushl $0x288938\n\t"
      "pushl $0x18\n\t"
      "pushl %%eax\n\t"
      "call *%[ce3d20]\n\t"
      "addl $0x10, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%eax, 0x4c(%%edi)\n\t"
      "je .LFUN_000f46e0_31\n\t"
      "movw 0x1a(%%esi), %%cx\n\t"
      "testb $1, %%cl\n\t"
      "je .LFUN_000f46e0_20\n\t"
      "movzwl %%cx, %%ebx\n\t"
      "pushl $0x2898d0\n\t"
      "pushl $0x75737472\n\t"
      "shrl $8, %%ebx\n\t"
      "call *%[c1b9930]\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "movl $0x26cdf0, %%ecx\n\t"
      "je .LFUN_000f46e0_19\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "call *%[c19d420]\n\t"
      "addl $8, %%esp\n\t"
      "movl %%eax, %%ecx\n\t"
      ".LFUN_000f46e0_19:\n\t"
      "pushl $0xb\n\t"
      "pushl %%ecx\n\t"
      "movl 0x4c(%%edi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c19dc90]\n\t"
      "movl 0x4c(%%edi), %%edx\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "movw $0, 0x16(%%edx)\n\t"
      "jmp .LFUN_000f46e0_21\n\t"
      ".LFUN_000f46e0_20:\n\t"
      "pushl $0xb\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "call *%[c19dc90]\n\t"
      "movl 0x4c(%%edi), %%eax\n\t"
      "movw $0, 0x16(%%eax)\n\t"
      ".LFUN_000f46e0_21:\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpw $0, 0x18(%%esi)\n\t"
      "jge .LFUN_000f46e0_22\n\t"
      "xorl %%eax, %%eax\n\t"
      "jmp .LFUN_000f46e0_24\n\t"
      ".LFUN_000f46e0_22:\n\t"
      "movswl 0x18(%%esi), %%edi\n\t"
      "call *%[c1c0ed0]\n\t"
      "movzwl %%ax, %%ecx\n\t"
      "decl %%ecx\n\t"
      "cmpl %%ecx, %%edi\n\t"
      "jle .LFUN_000f46e0_23\n\t"
      "call *%[c1c0ed0]\n\t"
      "movzwl %%ax, %%eax\n\t"
      "decl %%eax\n\t"
      "jmp .LFUN_000f46e0_24\n\t"
      ".LFUN_000f46e0_23:\n\t"
      "movl %%edi, %%eax\n\t"
      ".LFUN_000f46e0_24:\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "pushl $0x89c\n\t"
      "pushl $0x288938\n\t"
      "movw %%ax, 0x50(%%edx)\n\t"
      "movl 0x3c(%%ebx), %%eax\n\t"
      "pushl $0x200\n\t"
      "pushl %%eax\n\t"
      "call *%[ce3d20]\n\t"
      "addl $0x10, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%eax, 0x3c(%%ebx)\n\t"
      "je .LFUN_000f46e0_31\n\t"
      "testb $1, 0x1a(%%esi)\n\t"
      "je .LFUN_000f46e0_26\n\t"
      "pushl $0x289d00\n\t"
      "pushl $0x75737472\n\t"
      "call *%[c1b9930]\n\t"
      "pushl $0x289cb8\n\t"
      "pushl $0x75737472\n\t"
      "movl %%eax, %%edi\n\t"
      "call *%[c1b9930]\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpl $-1, %%edi\n\t"
      "movl %%eax, %%ebx\n\t"
      "je .LFUN_000f46e0_25\n\t"
      "cmpl $-1, %%ebx\n\t"
      "je .LFUN_000f46e0_25\n\t"
      "movzbw 0x29(%%esi), %%cx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edi\n\t"
      "call *%[c19d420]\n\t"
      "movzbw 0x28(%%esi), %%dx\n\t"
      "movl %%eax, %%edi\n\t"
      "pushl %%edx\n\t"
      "pushl %%ebx\n\t"
      "call *%[c19d420]\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "pushl %%eax\n\t"
      "movl 0x3c(%%esi), %%eax\n\t"
      "pushl $0x261f2c\n\t"
      "pushl %%edi\n\t"
      "pushl $0x289ca4\n\t"
      "pushl $0xff\n\t"
      "pushl %%eax\n\t"
      "call *%[c19e9f0]\n\t"
      "movl 0x3c(%%esi), %%ecx\n\t"
      "movw $0, 0x1fe(%%ecx)\n\t"
      "jmp .LFUN_000f46e0_27\n\t"
      ".LFUN_000f46e0_25:\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "movl 0x3c(%%edx), %%eax\n\t"
      "popl %%edi\n\t"
      "movw $0, (%%eax)\n\t"
      "movl 0x3c(%%edx), %%eax\n\t"
      "popl %%esi\n\t"
      "movw $0, 0x1fe(%%eax)\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000f46e0_26:\n\t"
      "pushl $0x289c58\n\t"
      "pushl $0x75737472\n\t"
      "call *%[c1b9930]\n\t"
      "pushl $0x289c10\n\t"
      "pushl $0x75737472\n\t"
      "movl %%eax, %%edi\n\t"
      "call *%[c1b9930]\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpl $-1, %%edi\n\t"
      "movl %%eax, %%ebx\n\t"
      "je .LFUN_000f46e0_28\n\t"
      "cmpl $-1, %%ebx\n\t"
      "je .LFUN_000f46e0_28\n\t"
      "movzbw 0x29(%%esi), %%cx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edi\n\t"
      "call *%[c19d420]\n\t"
      "movzbw 0x28(%%esi), %%dx\n\t"
      "movl %%eax, %%edi\n\t"
      "pushl %%edx\n\t"
      "pushl %%ebx\n\t"
      "call *%[c19d420]\n\t"
      "pushl %%eax\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl 0x3c(%%eax), %%ecx\n\t"
      "pushl $0x261f2c\n\t"
      "pushl %%edi\n\t"
      "pushl $0x289ca4\n\t"
      "pushl $0xff\n\t"
      "pushl %%ecx\n\t"
      "call *%[c19e9f0]\n\t"
      ".LFUN_000f46e0_27:\n\t"
      "addl $0x28, %%esp\n\t"
      ".LFUN_000f46e0_28:\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "movl 0x3c(%%edx), %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movw $0, 0x1fe(%%eax)\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000f46e0_29:\n\t"
      "movl 0x4c(%%edi), %%ecx\n\t"
      "pushl $0x8d2\n\t"
      "pushl $0x288938\n\t"
      "pushl $4\n\t"
      "pushl %%ecx\n\t"
      "call *%[ce3d20]\n\t"
      "addl $0x10, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%eax, 0x4c(%%edi)\n\t"
      "je .LFUN_000f46e0_30\n\t"
      "movw $0, (%%eax)\n\t"
      ".LFUN_000f46e0_30:\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "pushl $0x8d7\n\t"
      "pushl $0x288938\n\t"
      "movw $0, 0x50(%%edx)\n\t"
      "movl 0x3c(%%ebx), %%eax\n\t"
      "pushl $4\n\t"
      "pushl %%eax\n\t"
      "call *%[ce3d20]\n\t"
      "addl $0x10, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%eax, 0x3c(%%ebx)\n\t"
      "je .LFUN_000f46e0_31\n\t"
      "movw $0, (%%eax)\n\t"
      ".LFUN_000f46e0_31:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(bf46e0_assert), [exitfn] "m"(bf46e0_exitfn), [tag] "m"(bf46e0_tag), [cf3740] "m"(bf46e0_cf3740), [c1d9260] "m"(bf46e0_c1d9260), [ce3d20] "m"(bf46e0_ce3d20), [c1b9930] "m"(bf46e0_c1b9930), [c19d420] "m"(bf46e0_c19d420), [c19dc90] "m"(bf46e0_c19dc90), [c1c0ed0] "m"(bf46e0_c1c0ed0), [c19e9f0] "m"(bf46e0_c19e9f0)
      : "memory");
}
#else
#error "FUN_000f46e0: clang naked draft required"
#endif


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


/* FUN_000f5640 (0xf5640) — readable C lift. */
char FUN_000f5640(void)
{
  return *(char *)0x46cef0;
}

/* FUN_000f5650 (0xf5650) — readable C lift. */
char FUN_000f5650(void)
{
  return *(char *)0x46cf06;
}

/* 0xf5660 — virtual-keyboard cursor left (skip duplicate keymap glyphs). */
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


/* 0xf56b0 — virtual-keyboard cursor right (skip duplicate keymap glyphs). */
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


/* FUN_000f5800 (0xf5800) — readable C lift: soft-keyboard glyph lookup. */
unsigned short FUN_000f5800(int16_t slot_index)
{
  extern char DAT_0028a97c[];
  extern char DAT_0028a854[];
  extern char DAT_0028a94c[];
  char *ui_globals;
  char *entry;
  unsigned short glyph;
  char shift;
  char alt;
  char caps;

  ui_globals = *(char **)0x46cef4;
  if (ui_globals == 0) {
    display_assert(DAT_0028a97c, DAT_0028a854, 0x3da, 1);
    system_exit(-1);
  }
  if ((uint16_t)slot_index >= 0x24) {
    display_assert(DAT_0028a94c, DAT_0028a854, 0x3db, 1);
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
static unsigned short (*const f5900_f5800)(short) = (void *)FUN_000f5800;

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
int object_get_type(void)
{
  int len = ustrlen(*(const unsigned short **)0x46cf08);
  return (int)*(uint16_t *)0x46cefc - (len + len + 2);
}


/* items_initialize (0xf5f90) — readable C lift (jmp alias). */
void items_initialize(void)
{
  FUN_000f57a0();
}

/* items_initialize_for_new_map (0xf5fa0) — readable C lift. */
void items_initialize_for_new_map(void)
{
  if (*(unsigned char *)0x46cef0)
    FUN_000f5900();
}



/* FUN_000f5fb0 (0xf5fb0) — XBE naked draft (batch 222). */
#if defined(__clang__)
static int (*const bf5fb0_c19d810)(const wchar_t *s1, const wchar_t *s2) = ustrcmp;
static char (*const bf5fb0_c1c2bf0)(void) = saved_game_file_name_unique;
static void (*const bf5fb0_ce8910)(int16_t error_handle, int local_player_index, char is_modal, char pause_game) = ui_widget_display_error;
static char (*const bf5fb0_cf57a0)(void) = FUN_000f57a0;
static void (*const bf5fb0_ce5ab0)(int16_t sound_selector) = ui_play_audio_feedback_sound;
static void (*const bf5fb0_cdc220)(void) = event_manager_flush;
static void (*const bf5fb0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const bf5fb0_exitfn)(int) = system_exit;
static void *(*const bf5fb0_memset)(void *, int, unsigned int) = csmemset;
static void (*const bf5fb0_cf5f30)(void) = FUN_000f5f30;
static int (*const bf5fb0_cf5f10)(void) = object_get_type;
static void (*const bf5fb0_c8dae0)(void *dest, const void *src, unsigned int size) = csmemmove;
static int (*const bf5fb0_c19d8c0)(const unsigned short *s) = ustrlen;
static unsigned short (*const bf5fb0_cf5800)(int16_t slot_index /* */) = FUN_000f5800;
static unsigned int (*const bf5fb0_c8e370)(void) = system_milliseconds;
static void (*const bf5fb0_c19d6e0)(void) = align_to_character;

__attribute__((naked, noinline))
char FUN_000f5fb0(void)
{
  __asm__ volatile(
      "movswl 0x46cef8, %%eax\n\t"
      "movswl 0x46cefa, %%ecx\n\t"
      "imull $0xb, %%eax, %%eax\n\t"
      "movsbl 0x28a790(%%eax,%%ecx,1), %%eax\n\t"
      "pushl %%ebx\n\t"
      "addl $-0x24, %%eax\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "cmpl $7, %%eax\n\t"
      "ja .LFUN_000f5fb0_19\n\t"
      "jmp *.LFUN_000f5fb0_jt(,%%eax,4)\n\t"
      ".LFUN_000f5fb0_1:\n\t"
      "movl 0x46cf08, %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x46cf18\n\t"
      "call *%[c19d810]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_000f5fb0_3\n\t"
      "movl 0x46cf08, %%eax\n\t"
      "cmpw %%bx, (%%eax)\n\t"
      "je .LFUN_000f5fb0_2\n\t"
      "pushl %%eax\n\t"
      "call *%[c1c2bf0]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_000f5fb0_3\n\t"
      "pushl %%ebx\n\t"
      "pushl $1\n\t"
      "pushl $-1\n\t"
      "pushl $0x1b\n\t"
      "call *%[ce8910]\n\t"
      "addl $0x10, %%esp\n\t"
      "call *%[cf57a0]\n\t"
      "jmp .LFUN_000f5fb0_4\n\t"
      ".LFUN_000f5fb0_2:\n\t"
      "pushl %%ebx\n\t"
      "pushl $1\n\t"
      "pushl $-1\n\t"
      "pushl $0x1d\n\t"
      "call *%[ce8910]\n\t"
      "addl $0x10, %%esp\n\t"
      "call *%[cf57a0]\n\t"
      "jmp .LFUN_000f5fb0_4\n\t"
      ".LFUN_000f5fb0_3:\n\t"
      "movb $1, 0x46cf06\n\t"
      ".LFUN_000f5fb0_4:\n\t"
      "pushl $3\n\t"
      "call *%[ce5ab0]\n\t"
      "addl $4, %%esp\n\t"
      "movb %%bl, 0x46cef0\n\t"
      "call *%[cdc220]\n\t"
      "jmp .LFUN_000f5fb0_27\n\t"
      ".LFUN_000f5fb0_5:\n\t"
      "pushl $1\n\t"
      "call *%[ce5ab0]\n\t"
      "movb 0x46cef1, %%al\n\t"
      "addl $4, %%esp\n\t"
      "cmpb %%bl, %%al\n\t"
      "sete %%al\n\t"
      "movb %%al, 0x46cef1\n\t"
      "jmp .LFUN_000f5fb0_27\n\t"
      ".LFUN_000f5fb0_6:\n\t"
      "pushl $1\n\t"
      "call *%[ce5ab0]\n\t"
      "movb 0x46cef2, %%al\n\t"
      "addl $4, %%esp\n\t"
      "cmpb %%bl, %%al\n\t"
      "sete %%cl\n\t"
      "movb %%cl, 0x46cef2\n\t"
      "jmp .LFUN_000f5fb0_27\n\t"
      ".LFUN_000f5fb0_7:\n\t"
      "pushl $1\n\t"
      "call *%[ce5ab0]\n\t"
      "movb 0x46cef3, %%al\n\t"
      "addl $4, %%esp\n\t"
      "cmpb %%bl, %%al\n\t"
      "sete %%dl\n\t"
      "movb %%dl, 0x46cef3\n\t"
      "jmp .LFUN_000f5fb0_27\n\t"
      ".LFUN_000f5fb0_8:\n\t"
      "cmpb $1, 0x46cf07\n\t"
      "jne .LFUN_000f5fb0_10\n\t"
      "cmpw %%bx, 0x46cefc\n\t"
      "ja .LFUN_000f5fb0_9\n\t"
      "pushl $1\n\t"
      "pushl $0x355\n\t"
      "pushl $0x28a854\n\t"
      "pushl $0x28aa58\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000f5fb0_9:\n\t"
      "movzwl 0x46cefc, %%eax\n\t"
      "movl 0x46cf08, %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ecx\n\t"
      "call *%[memset]\n\t"
      "movl 0x46cf08, %%edx\n\t"
      "addl $0xc, %%esp\n\t"
      "movl %%edx, 0x46cf0c\n\t"
      "movb %%bl, 0x46cf07\n\t"
      "jmp .LFUN_000f5fb0_27\n\t"
      ".LFUN_000f5fb0_10:\n\t"
      "call *%[cf5f30]\n\t"
      "jmp .LFUN_000f5fb0_27\n\t"
      ".LFUN_000f5fb0_11:\n\t"
      "movl 0x46cf0c, %%eax\n\t"
      "cmpl 0x46cf08, %%eax\n\t"
      "jbe .LFUN_000f5fb0_13\n\t"
      "subl $2, %%eax\n\t"
      ".LFUN_000f5fb0_12:\n\t"
      "movl %%eax, 0x46cf0c\n\t"
      ".LFUN_000f5fb0_13:\n\t"
      "pushl $1\n\t"
      "movb %%bl, 0x46cf07\n\t"
      "call *%[ce5ab0]\n\t"
      "addl $4, %%esp\n\t"
      "jmp .LFUN_000f5fb0_27\n\t"
      ".LFUN_000f5fb0_14:\n\t"
      "movl 0x46cf0c, %%ecx\n\t"
      "cmpw %%bx, (%%ecx)\n\t"
      "je .LFUN_000f5fb0_13\n\t"
      "movl %%ecx, %%eax\n\t"
      "addl $2, %%eax\n\t"
      "jmp .LFUN_000f5fb0_12\n\t"
      ".LFUN_000f5fb0_15:\n\t"
      "cmpb $1, 0x46cf07\n\t"
      "jne .LFUN_000f5fb0_17\n\t"
      "cmpw %%bx, 0x46cefc\n\t"
      "ja .LFUN_000f5fb0_16\n\t"
      "pushl $1\n\t"
      "pushl $0x378\n\t"
      "pushl $0x28a854\n\t"
      "pushl $0x28aa58\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000f5fb0_16:\n\t"
      "movzwl 0x46cefc, %%edx\n\t"
      "movl 0x46cf08, %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "call *%[memset]\n\t"
      "movl 0x46cf08, %%ecx\n\t"
      "addl $0xc, %%esp\n\t"
      "movl %%ecx, 0x46cf0c\n\t"
      "movb %%bl, 0x46cf07\n\t"
      ".LFUN_000f5fb0_17:\n\t"
      "call *%[cf5f10]\n\t"
      "cmpl $2, %%eax\n\t"
      "jl .LFUN_000f5fb0_18\n\t"
      "movzwl 0x46cefc, %%edx\n\t"
      "movl 0x46cf0c, %%eax\n\t"
      "movl 0x46cf08, %%ecx\n\t"
      "subl %%eax, %%edx\n\t"
      "leal -0x2(%%edx,%%ecx,1), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "addl $2, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c8dae0]\n\t"
      "movl 0x46cf0c, %%eax\n\t"
      "movw $0x20, (%%eax)\n\t"
      "movl 0x46cf0c, %%edx\n\t"
      "addl $2, %%edx\n\t"
      "pushl $2\n\t"
      "movl %%edx, 0x46cf0c\n\t"
      "call *%[ce5ab0]\n\t"
      "addl $0x10, %%esp\n\t"
      "jmp .LFUN_000f5fb0_27\n\t"
      ".LFUN_000f5fb0_18:\n\t"
      "pushl $4\n\t"
      "call *%[ce5ab0]\n\t"
      "addl $4, %%esp\n\t"
      "jmp .LFUN_000f5fb0_27\n\t"
      ".LFUN_000f5fb0_19:\n\t"
      "cmpb $1, 0x46cf07\n\t"
      "jne .LFUN_000f5fb0_21\n\t"
      "cmpw %%bx, 0x46cefc\n\t"
      "ja .LFUN_000f5fb0_20\n\t"
      "pushl $1\n\t"
      "pushl $0x391\n\t"
      "pushl $0x28a854\n\t"
      "pushl $0x28aa58\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000f5fb0_20:\n\t"
      "movzwl 0x46cefc, %%ecx\n\t"
      "movl 0x46cf08, %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edx\n\t"
      "call *%[memset]\n\t"
      "movl 0x46cf08, %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "movl %%eax, 0x46cf0c\n\t"
      "movb %%bl, 0x46cf07\n\t"
      ".LFUN_000f5fb0_21:\n\t"
      "movl 0x46cf08, %%ecx\n\t"
      "pushl %%esi\n\t"
      "movzwl 0x46cefc, %%esi\n\t"
      "pushl %%ecx\n\t"
      "call *%[c19d8c0]\n\t"
      "leal 0x2(%%eax,%%eax,1), %%edx\n\t"
      "movl %%esi, %%eax\n\t"
      "subl %%edx, %%eax\n\t"
      "addl $4, %%esp\n\t"
      "cmpl $2, %%eax\n\t"
      "jl .LFUN_000f5fb0_25\n\t"
      "movl 0x46cf0c, %%eax\n\t"
      "movl 0x46cf08, %%ecx\n\t"
      "subl %%eax, %%esi\n\t"
      "leal -0x2(%%esi,%%ecx,1), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "addl $2, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c8dae0]\n\t"
      "movswl 0x46cef8, %%eax\n\t"
      "movswl 0x46cefa, %%ecx\n\t"
      "imull $0xb, %%eax, %%eax\n\t"
      "movsbw 0x28a790(%%eax,%%ecx,1), %%si\n\t"
      "call *%[cf5800]\n\t"
      "movl 0x46cf0c, %%edx\n\t"
      "movw %%ax, (%%edx)\n\t"
      "movl 0x46cf0c, %%ecx\n\t"
      "movl 0x46cf08, %%eax\n\t"
      "addl $2, %%ecx\n\t"
      "pushl $0x28aa44\n\t"
      "pushl %%eax\n\t"
      "movl %%ecx, 0x46cf0c\n\t"
      "call *%[c19d810]\n\t"
      "addl $0x14, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_000f5fb0_24\n\t"
      "call *%[c8e370]\n\t"
      "xorl %%edx, %%edx\n\t"
      "movl $0xa, %%ecx\n\t"
      "divl %%ecx\n\t"
      "cmpl $9, %%edx\n\t"
      "jbe .LFUN_000f5fb0_22\n\t"
      "movl $9, %%edx\n\t"
      ".LFUN_000f5fb0_22:\n\t"
      "addl $0xb, %%edx\n\t"
      "cmpw %%bx, 0x46cf18\n\t"
      "movw %%dx, 0x46cf04\n\t"
      "je .LFUN_000f5fb0_23\n\t"
      "movl 0x46cf08, %%edx\n\t"
      "pushl $0x46cf18\n\t"
      "pushl %%edx\n\t"
      "call *%[c19d6e0]\n\t"
      "movl 0x46cf08, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c19d8c0]\n\t"
      "movl 0x46cf08, %%ecx\n\t"
      "leal (%%ecx,%%eax,2), %%edx\n\t"
      "addl $0xc, %%esp\n\t"
      "movl %%edx, 0x46cf0c\n\t"
      "pushl $2\n\t"
      "jmp .LFUN_000f5fb0_26\n\t"
      ".LFUN_000f5fb0_23:\n\t"
      "movzwl 0x46cefc, %%eax\n\t"
      "movl 0x46cf08, %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ecx\n\t"
      "call *%[memset]\n\t"
      "movl 0x46cf08, %%edx\n\t"
      "addl $0xc, %%esp\n\t"
      "movl %%edx, 0x46cf0c\n\t"
      ".LFUN_000f5fb0_24:\n\t"
      "pushl $2\n\t"
      "jmp .LFUN_000f5fb0_26\n\t"
      ".LFUN_000f5fb0_25:\n\t"
      "pushl $4\n\t"
      ".LFUN_000f5fb0_26:\n\t"
      "call *%[ce5ab0]\n\t"
      "addl $4, %%esp\n\t"
      "popl %%esi\n\t"
      ".LFUN_000f5fb0_27:\n\t"
      "movswl 0x46cef8, %%eax\n\t"
      "movswl 0x46cefa, %%ecx\n\t"
      "imull $0xb, %%eax, %%eax\n\t"
      "cmpb $0x25, 0x28a790(%%eax,%%ecx,1)\n\t"
      "movb $1, %%al\n\t"
      "je .LFUN_000f5fb0_28\n\t"
      "movb %%bl, 0x46cef1\n\t"
      ".LFUN_000f5fb0_28:\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      "movl %%edi, %%edi\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_000f5fb0_jt:\n\t"
      ".long .LFUN_000f5fb0_1\n\t"
      ".long .LFUN_000f5fb0_5\n\t"
      ".long .LFUN_000f5fb0_6\n\t"
      ".long .LFUN_000f5fb0_7\n\t"
      ".long .LFUN_000f5fb0_8\n\t"
      ".long .LFUN_000f5fb0_11\n\t"
      ".long .LFUN_000f5fb0_14\n\t"
      ".long .LFUN_000f5fb0_15\n\t"
      ".text\n\t"
      :
      : [c19d810] "m"(bf5fb0_c19d810), [c1c2bf0] "m"(bf5fb0_c1c2bf0), [ce8910] "m"(bf5fb0_ce8910), [cf57a0] "m"(bf5fb0_cf57a0), [ce5ab0] "m"(bf5fb0_ce5ab0), [cdc220] "m"(bf5fb0_cdc220), [assert] "m"(bf5fb0_assert), [exitfn] "m"(bf5fb0_exitfn), [memset] "m"(bf5fb0_memset), [cf5f30] "m"(bf5fb0_cf5f30), [cf5f10] "m"(bf5fb0_cf5f10), [c8dae0] "m"(bf5fb0_c8dae0), [c19d8c0] "m"(bf5fb0_c19d8c0), [cf5800] "m"(bf5fb0_cf5800), [c8e370] "m"(bf5fb0_c8e370), [c19d6e0] "m"(bf5fb0_c19d6e0)
      : "memory");
}
#else
#error "FUN_000f5fb0: clang naked draft required"
#endif


/* item_get_position_even_if_in_inventory (0xf6a60) — readable C lift. */
void item_get_position_even_if_in_inventory(int item_handle, float *out_pos)
{
  char *item_obj;
  int owner;
  char *unit_obj;

  item_obj = (char *)object_try_and_get_and_verify_type(item_handle, 0x1c);
  out_pos[0] = 0;
  out_pos[1] = 0;
  out_pos[2] = 0;
  if (item_obj == (char *)0)
    return;
  if ((*(unsigned char *)(item_obj + 0x1a4) & 1) != 0) {
    owner = *(int *)(item_obj + 0x70);
    if (owner == -1)
      return;
    owner = *(int *)((char *)datum_get(*(data_t **)0x5aa6d4, owner) + 0x34);
    if (owner == -1)
      return;
    unit_obj = (char *)object_get_and_verify_type(owner, 3);
    out_pos[0] = *(float *)(unit_obj + 0x50);
    out_pos[1] = *(float *)(unit_obj + 0x54);
    out_pos[2] = *(float *)(unit_obj + 0x58);
    return;
  }
  out_pos[0] = *(float *)(item_obj + 0x50);
  out_pos[1] = *(float *)(item_obj + 0x54);
  out_pos[2] = *(float *)(item_obj + 0x58);
}

/* FUN_000f7110 (0xf7110) — XBE naked draft (batch 234). */
#if defined(__clang__)
static void *(*const bf7110_get)(int, int) = object_get_and_verify_type;
static void (*const bf7110_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const bf7110_exitfn)(int) = system_exit;
static short (*const bf7110_markers)(int, void *, void *, int) = object_get_markers_by_string_id;
static void (*const bf7110_c10bb20)(float *q, float *v, float *out) = quaternion_transform_point;
static float (*const bf7110_norm)(float *) = normalize3d;
static void (*const bf7110_m4x3)(void *, float *, float *, float *) = matrix4x3_from_forward_up_position;
static char (*const bf7110_cf6d00)(float *mat) = valid_real_matrix4x3;
static void (*const bf7110_ochild)(void *, void *, void *) = object_compute_child_marker_position;

__attribute__((naked, noinline))
void FUN_000f7110(float *opt_position __attribute__((unused)), int item_handle __attribute__((unused)), float *hit_normal __attribute__((unused)), float *out_position __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xc8, %%esp\n\t"
      "pushl %%edi\n\t"
      "pushl $0x1c\n\t"
      "pushl %%ebx\n\t"
      "movl %%eax, %%edi\n\t"
      "call *%[get]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%eax, -0x18(%%ebp)\n\t"
      "jne .LFUN_000f7110_1\n\t"
      "pushl $1\n\t"
      "pushl $0x2c9\n\t"
      "pushl $0x28aaa0\n\t"
      "pushl $0x26b188\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000f7110_1:\n\t"
      "pushl $1\n\t"
      "leal -0x94(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x28aa90\n\t"
      "pushl %%ebx\n\t"
      "call *%[markers]\n\t"
      "addl $0x10, %%esp\n\t"
      "testw %%ax, %%ax\n\t"
      "je .LFUN_000f7110_8\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_000f7110_2\n\t"
      "leal -0x34(%%ebp), %%ecx\n\t"
      "movl %%ecx, 0x8(%%ebp)\n\t"
      ".LFUN_000f7110_2:\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .LFUN_000f7110_3\n\t"
      "leal -0x34(%%ebp), %%edi\n\t"
      ".LFUN_000f7110_3:\n\t"
      "flds -0x40(%%ebp)\n\t"
      "fmuls (%%esi)\n\t"
      "flds -0x3c(%%ebp)\n\t"
      "fmuls 0x4(%%esi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds -0x38(%%ebp)\n\t"
      "fmuls 0x8(%%esi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fadds 0x2533c8\n\t"
      "fadd %%st(0), %%st(0)\n\t"
      "fsqrt\n\t"
      "fsts -0x4(%%ebp)\n\t"
      "fcompl 0x26aed0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_000f7110_5\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .LFUN_000f7110_4\n\t"
      "pushl $1\n\t"
      "pushl $0x2dc\n\t"
      "pushl $0x28aaa0\n\t"
      "pushl $0x28aaec\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000f7110_4:\n\t"
      "flds -0x3c(%%ebp)\n\t"
      "leal -0x14(%%ebp), %%edx\n\t"
      "fmuls 0x8(%%esi)\n\t"
      "pushl %%edx\n\t"
      "flds -0x38(%%ebp)\n\t"
      "leal -0x58(%%ebp), %%eax\n\t"
      "fmuls 0x4(%%esi)\n\t"
      "pushl %%eax\n\t"
      "leal -0x28(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      ".byte 0xde, 0xe9\n\t"
      "flds -0x38(%%ebp)\n\t"
      "fmuls (%%esi)\n\t"
      "flds -0x40(%%ebp)\n\t"
      "fmuls 0x8(%%esi)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "flds -0x40(%%ebp)\n\t"
      "fmuls 0x4(%%esi)\n\t"
      "flds -0x3c(%%ebp)\n\t"
      "fmuls (%%esi)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0x20(%%ebp)\n\t"
      "flds 0x2533c8\n\t"
      "fdivs -0x4(%%ebp)\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "fxch %%st(1)\n\t"
      "fmuls -0x8(%%ebp)\n\t"
      "fstps -0x28(%%ebp)\n\t"
      "fmuls -0x8(%%ebp)\n\t"
      "fstps -0x24(%%ebp)\n\t"
      "flds -0x20(%%ebp)\n\t"
      "fmuls -0x8(%%ebp)\n\t"
      "fstps -0x20(%%ebp)\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fmuls 0x253398\n\t"
      "fstps -0x1c(%%ebp)\n\t"
      "call *%[c10bb20]\n\t"
      "addl $0xc, %%esp\n\t"
      "jmp .LFUN_000f7110_6\n\t"
      ".LFUN_000f7110_5:\n\t"
      "flds -0x50(%%ebp)\n\t"
      "fmuls 0x4(%%esi)\n\t"
      "flds -0x54(%%ebp)\n\t"
      "fmuls 0x8(%%esi)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "flds -0x58(%%ebp)\n\t"
      "fmuls 0x8(%%esi)\n\t"
      "flds -0x50(%%ebp)\n\t"
      "fmuls (%%esi)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "flds -0x54(%%ebp)\n\t"
      "fmuls (%%esi)\n\t"
      "flds -0x58(%%ebp)\n\t"
      "fmuls 0x4(%%esi)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fld %%st(1)\n\t"
      "fmuls 0x8(%%esi)\n\t"
      "fld %%st(1)\n\t"
      "fmuls 0x4(%%esi)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "fmuls (%%esi)\n\t"
      "fld %%st(2)\n\t"
      "fmuls 0x8(%%esi)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "fxch %%st(1)\n\t"
      "fmuls 0x4(%%esi)\n\t"
      "fxch %%st(1)\n\t"
      "fmuls (%%esi)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0xc(%%ebp)\n\t"
      ".LFUN_000f7110_6:\n\t"
      "leal -0x14(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[norm]\n\t"
      "fstp %%st(0)\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "pushl %%esi\n\t"
      "leal -0x14(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "leal -0xc8(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[m4x3]\n\t"
      "leal -0xc8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[cf6d00]\n\t"
      "addl $0x18, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_000f7110_7\n\t"
      "pushl $1\n\t"
      "pushl $0x2f3\n\t"
      "pushl $0x28aaa0\n\t"
      "pushl $0x28aac0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000f7110_7:\n\t"
      "leal -0xc8(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x94(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $-1\n\t"
      "pushl %%ebx\n\t"
      "call *%[get]\n\t"
      "addl $8, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[ochild]\n\t"
      "movl -0x18(%%ebp), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "addl $0xc, %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "movl %%ecx, (%%edi)\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl %%edx, 0x4(%%edi)\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl %%eax, 0x8(%%edi)\n\t"
      ".LFUN_000f7110_8:\n\t"
      "popl %%edi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [get] "m"(bf7110_get), [assert] "m"(bf7110_assert), [exitfn] "m"(bf7110_exitfn), [markers] "m"(bf7110_markers), [c10bb20] "m"(bf7110_c10bb20), [norm] "m"(bf7110_norm), [m4x3] "m"(bf7110_m4x3), [cf6d00] "m"(bf7110_cf6d00), [ochild] "m"(bf7110_ochild)
      : "memory");
}
#else
#error "FUN_000f7110: clang naked draft required"
#endif


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

