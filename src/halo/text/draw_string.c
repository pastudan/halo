/*
 * text/draw_string.c — string rendering state setup and telnet tab output
 * XBE source: c:\halo\SOURCE\text\draw_string.c
 *
 * Manages a small block of draw-string globals at 0x4d9b0c:
 *   [+0x00] int    font tag index      (0x4d9b0c)
 *   [+0x04] int    flags               (0x4d9b10)
 *   [+0x08] short  style               (0x4d9b14)
 *   [+0x0a] short  justify             (0x4d9b16)
 *   [+0x0c] float  color.alpha         (0x4d9b18)
 *   [+0x10] float  color.red           (0x4d9b1c)
 *   [+0x14] float  color.green         (0x4d9b20)
 *   [+0x18] float  color.blue          (0x4d9b24)
 *   [+0x1c] short  tab_stop_count      (0x4d9b28)
 *   [+0x1e] short  tab_stops[16]       (0x4d9b2a)
 *
 * terminal_string_process_tabs (0x130ab0) lives here even though it
 * touches telnet globals — it forwards the rendered text out over the
 * telnet debug console.  The telnet console globals base is 0x46eee0:
 *   [+0x04] int*  client endpoint      (0x46eee4)
 *   [+0x08] char  client input buffer  (0x46eee8)
 *   [+0x88] char  initialized flag     (0x46ef68)
 *
 * Re-implemented functions (by XBE address, ascending):
 *   0x130ab0  terminal_string_process_tabs
 *   0x19b560  draw_string_set_tab_stops
 *   0x19b640  draw_string_set_color
 *   0x19b800  draw_string_set_style_justify_flags
 *   0x19b8b0  draw_string_set_font
 */

/* Telnet console globals accessed here (base 0x46eee0). */
#define tc_initialized (*(char *)0x46ef68)
#define tc_client0_ep (*(int **)0x46eee4)
#define tc_client0_buf ((char *)0x46eee8)

/* Maximum tab stops allowed (asserted in draw_string_set_tab_stops). */
#define MAXIMUM_NUMBER_OF_TAB_STOPS 16

/*
 * terminal_string_process_tabs — forward rendered text to telnet console.
 *
 * If the telnet subsystem is initialized, a client is connected, and the
 * text is non-empty, sends "\r\n" followed by the text over the TCP
 * connection.  If the client's trailing input buffer (tc_client0_buf) is
 * also non-empty it appends that too.  On any send failure the connection
 * is logged as lost and the endpoint is closed and cleared.
 *
 * Confirmed: checks 0x46ef68 (tc_initialized), 0x46eee4 (client ep),
 *            param_1 non-null and non-empty.
 * Confirmed: csstrlen (0x8df60), send_endpoint (0x82f50),
 *            error (0x8f390), destroy_endpoint (0x848c0).
 * Confirmed: CRLF prefix string at 0x261f2c = "\r\n".
 * Confirmed: error string at 0x29a87c = "connection lost to telnet client".
 */
void terminal_string_process_tabs(const char *text)
{
  int len;
  int sent;

  if (!tc_initialized)
    return;
  if (text == NULL)
    return;
  if (*text == '\0')
    return;
  if (tc_client0_ep == NULL)
    return;

  /* Send CRLF prefix. */
  sent = send_endpoint(tc_client0_ep, (const char *)0x261f2c, 2);
  if (sent <= 0)
    goto lost;

  /* Send the text itself. */
  len = csstrlen(text);
  sent = send_endpoint(tc_client0_ep, text, len);
  if (sent <= 0)
    goto lost;

  /* If the client input buffer has a pending line, echo it back. */
  if (tc_client0_buf[0] != '\0') {
    len = csstrlen(tc_client0_buf);
    sent = send_endpoint(tc_client0_ep, tc_client0_buf, len);
  }
  if (sent > 0)
    return;

lost:
  error(2, "connection lost to telnet client");
  destroy_endpoint(tc_client0_ep);
  tc_client0_ep = NULL;
}

/*
 * FUN_0019b3c0 — update text-bounds tracking globals.
 *
 * Records the min/max extents of a rendered text element for layout tracking.
 * param_5/param_6 = left/top corner (shorts); param_9/param_10 = width/height.
 * param_2 (int) is stored as an associated handle at 0x4d9b04.
 *
 * Globals (in a tightly packed block at 0x4d9af8):
 *   0x4d9afc (short) min_y   0x4d9afe (short) min_x
 *   0x4d9b00 (short) max_y   0x4d9b02 (short) max_x
 *   0x4d9b04 (int)   tag/handle
 *
 * 0x19b3c0 / draw_string.obj
 */
void FUN_0019b3c0(int param_1, int param_2, int param_3, int param_4,
                  short param_5, short param_6, int param_7, int param_8,
                  short param_9, short param_10)
{
  if (param_5 < *(short *)0x4d9afe)
    *(short *)0x4d9afe = param_5;
  if (param_6 < *(short *)0x4d9afc)
    *(short *)0x4d9afc = param_6;
  if (*(short *)0x4d9b02 < (short)(param_5 + param_9))
    *(short *)0x4d9b02 = (short)(param_5 + param_9);
  if (*(short *)0x4d9b00 < (short)(param_10 + param_6)) {
    *(short *)0x4d9b00 = (short)(param_10 + param_6);
    *(int *)0x4d9b04 = param_2;
    return;
  }
  *(int *)0x4d9b04 = param_2;
}

/*
 * FUN_0019b430 — cursor hit-test callback for text layout.
 *
 * Computes the Chebyshev (L∞) distance from the reference point at globals
 * 0x4d9af0 (ref_x, short) / 0x4d9af2 (ref_y, short) to the four edges of
 * the text element bounding box [param_5..param_5+param_9] ×
 * [param_6..param_6+param_10]. If this distance beats the current best
 * (0x4d9af6), updates it and sets the cursor position markers at 0x4d9af4 and
 * 0x4d9af8 based on which half of the element the reference point falls in.
 * Always updates 0x4d9af8.
 *
 * param_1 = pointer to text element; *(short*)(param_1+0xc) = cursor position
 * value.
 *
 * 0x19b430 / draw_string.obj
 */
void FUN_0019b430(int param_1, int param_2, int param_3, int param_4,
                  short param_5, short param_6, int param_7, int param_8,
                  short param_9, short param_10)
{
  short ref_x = *(short *)0x4d9af0;
  short dx_left = (short)param_5 - ref_x;
  short dx_right = (short)(param_5 + param_9) - ref_x;
  short dy_top = (short)param_6 - *(short *)0x4d9af2;
  short dy_bottom = (short)param_10 + dy_top;
  short max_dist;
  int edx;
  int ecx;

  if (dx_left < 0)
    dx_left = -dx_left;
  if (dx_right < 0)
    dx_right = -dx_right;
  if (dy_top < 0)
    dy_top = -dy_top;
  if (dy_bottom < 0)
    dy_bottom = -dy_bottom;

  max_dist = dx_left;
  if (max_dist <= dx_right)
    max_dist = dx_right;
  if (max_dist <= dy_top)
    max_dist = dy_top;
  if (max_dist <= dy_bottom)
    max_dist = dy_bottom;

  if (max_dist < *(short *)0x4d9af6) {
    *(short *)0x4d9af6 = max_dist;
    edx = (int)ref_x - (int)(short)param_5;
    ecx = ((int)(short)(param_5 + param_9) - (int)(short)param_5) >> 1;
    if (edx < ecx) {
      *(short *)0x4d9af4 = *(short *)0x4d9af8;
      *(short *)0x4d9af8 = *(short *)(param_1 + 0xc);
      return;
    }
    *(short *)0x4d9af4 = *(short *)(param_1 + 0xc);
    *(short *)0x4d9af8 = *(short *)(param_1 + 0xc);
    return;
  }
  *(short *)0x4d9af8 = *(short *)(param_1 + 0xc);
}

/*
 * draw_string_set_tab_stops — set the tab stop array for subsequent draws.
 *
 * Validates count is in [0, MAXIMUM_NUMBER_OF_TAB_STOPS).  Stores the
 * count at 0x4d9b28 and copies count shorts from stops to 0x4d9b2a.
 *
 * Confirmed: assert string "count>=0 && count<MAXIMUM_NUMBER_OF_TAB_STOPS"
 *            in draw_string.c line 0x15e.
 * Confirmed: cap at 0x10 (16) after assert path.
 * Confirmed: SHL EAX,1 before csmemcpy — copies count*2 bytes (shorts).
 * Confirmed: tab count stored as word at 0x4d9b28; array at 0x4d9b2a.
 */
void draw_string_set_tab_stops(void *stops, short count)
{
  if (count < 0 || count >= MAXIMUM_NUMBER_OF_TAB_STOPS) {
    display_assert("count>=0 && count<MAXIMUM_NUMBER_OF_TAB_STOPS",
                   "c:\\halo\\SOURCE\\text\\draw_string.c", 0x15e, 1);
    system_exit(-1);
    /* After assert: cap at 16 and continue. */
    if (count > 0x10) {
      *(short *)0x4d9b28 = 0x10;
      goto copy;
    }
  }
  *(short *)0x4d9b28 = count;
  if (count < 1)
    return;
copy:
  csmemcpy((void *)0x4d9b2a, stops, (int)*(short *)0x4d9b28 << 1);
}

/*
 * draw_string_set_color — set the draw-string ARGB color state.
 *
 * Validates that color is non-NULL and each of the four float components
 * (alpha, red, green, blue) is in [0.0, 1.0].  Stores the four floats
 * at 0x4d9b18..0x4d9b24 via raw dword moves (preserving bit pattern).
 *
 * Confirmed: assert "color" line 0x17a; assert per-channel lines 0x17b-0x17e.
 * Confirmed: float comparisons use x87 FCOMP against [0x2533c0]=0.0f and
 *            [0x2533c8]=1.0f.
 * Confirmed: final stores via MOV EAX,[ESI]; MOV [0x4d9b18],EAX etc.
 * Confirmed: field order in ESI: [+0]=alpha, [+4]=red, [+8]=green, [+c]=blue.
 */
void draw_string_set_color(const void *color)
{
  const float *c = (const float *)color;

  if (c == NULL) {
    display_assert("color", "c:\\halo\\SOURCE\\text\\draw_string.c", 0x17a, 1);
    system_exit(-1);
  }
  if (!(c[0] >= 0.0f && c[0] <= 1.0f)) {
    display_assert("(color->alpha >= 0.f) && (color->alpha <= 1.f)",
                   "c:\\halo\\SOURCE\\text\\draw_string.c", 0x17b, 1);
    system_exit(-1);
  }
  if (!(c[1] >= 0.0f && c[1] <= 1.0f)) {
    display_assert("(color->red >= 0.f) && (color->red <= 1.f)",
                   "c:\\halo\\SOURCE\\text\\draw_string.c", 0x17c, 1);
    system_exit(-1);
  }
  if (!(c[2] >= 0.0f && c[2] <= 1.0f)) {
    display_assert("(color->green >= 0.f) && (color->green <= 1.f)",
                   "c:\\halo\\SOURCE\\text\\draw_string.c", 0x17d, 1);
    system_exit(-1);
  }
  if (!(c[3] >= 0.0f && c[3] <= 1.0f)) {
    display_assert("(color->blue >= 0.f) && (color->blue <= 1.f)",
                   "c:\\halo\\SOURCE\\text\\draw_string.c", 0x17e, 1);
    system_exit(-1);
  }
  /* Store via raw dword copies to preserve bit-exact float representation. */
  *(int *)0x4d9b18 = *(const int *)&c[0]; /* alpha */
  *(int *)0x4d9b1c = *(const int *)&c[1]; /* red   */
  *(int *)0x4d9b20 = *(const int *)&c[2]; /* green */
  *(int *)0x4d9b24 = *(const int *)&c[3]; /* blue  */
}

/*
 * draw_string_set_style_justify_flags — set text style, justification, flags.
 *
 * Validates:
 *   flags  — bits above 3 must be clear (VALID_FLAGS, NUMBER_OF_TEXT_FLAGS=4)
 *   style  — must be -1 (plain) or in [0, NUMBER_OF_TEXT_STYLES) i.e. [0,3)
 *   justify — must be in [0, NUMBER_OF_TEXT_JUSTIFICATIONS) i.e. [0,2]
 *
 * Confirmed: TEST EBX,0xfffffff0 for flags check (line 0x19a).
 * Confirmed: style compared as word: CMP DI,-0x1; JZ ok; TEST DI,DI;
 *            JL bad; CMP DI,0x4; JL ok (line 0x19b).
 * Confirmed: justify compared as word: TEST SI,SI; JL bad; CMP SI,0x3;
 *            JL ok (line 0x19c).
 * Confirmed: stores — MOV word[0x4d9b14],DI; MOV word[0x4d9b16],SI;
 *            MOV dword[0x4d9b10],EBX.
 */
void draw_string_set_style_justify_flags(short style, short justify, int flags)
{
  if (flags & 0xfffffff0) {
    display_assert("VALID_FLAGS(flags, NUMBER_OF_TEXT_FLAGS)",
                   "c:\\halo\\SOURCE\\text\\draw_string.c", 0x19a, 1);
    system_exit(-1);
  }
  if (style != -1 && (style < 0 || style >= 4)) {
    display_assert(
      "style==_text_style_plain || (style>=0 && style<NUMBER_OF_TEXT_STYLES)",
      "c:\\halo\\SOURCE\\text\\draw_string.c", 0x19b, 1);
    system_exit(-1);
  }
  if (justify < 0 || justify >= 3) {
    display_assert(
      "justification>=0 && justification<NUMBER_OF_TEXT_JUSTIFICATIONS",
      "c:\\halo\\SOURCE\\text\\draw_string.c", 0x19c, 1);
    system_exit(-1);
  }
  /* Note: stores happen after all assertions, matching original order. */
  *(short *)0x4d9b14 = style;
  *(short *)0x4d9b16 = justify;
  *(int *)0x4d9b10 = flags;
}

/*
 * draw_string_set_font — configure the draw-string font state.
 *
 * Verifies the tag_index names a valid 'font' tag via tag_get, stores the
 * tag index, then delegates color and style/justify/flags setup.
 *
 * Confirmed: PUSH ESI (tag_index); PUSH 0x666f6e74 ('font'); CALL tag_get.
 * Confirmed: MOV [0x4d9b0c],ESI after tag_get (stores tag_index, not result).
 * Confirmed: param_5 (color) pushed first to draw_string_set_color (EBP+0x18).
 * Confirmed: style=EBP+0xc, justify=EBP+0x10, flags=EBP+0x14 →
 *            PUSH ECX(flags); PUSH EDX(justify); PUSH EAX(style);
 *            CALL draw_string_set_style_justify_flags.
 * Confirmed: single ADD ESP,0x18 cleans both preceding calls (4+12 args).
 */
void draw_string_set_font(int tag_index, int style, int justify, int flags,
                          const void *color)
{
  tag_get(0x666f6e74, tag_index); /* validate 'font' tag; result unused */
  *(int *)0x4d9b0c = tag_index;
  draw_string_set_color(color);
  draw_string_set_style_justify_flags((short)style, (short)justify, flags);
}

/*
 * FUN_0019bcc0 — resolve the effective font tag for a given style.
 *
 * If style == -1 (plain): returns tag_get("font", font_index) directly.
 * Otherwise asserts style in [0, 3], gets the font tag for font_index,
 * looks up the per-style font override at [font_tag+0x48 + style*0x10],
 * and falls back to font_index if the style entry is -1.
 * Returns the final tag_get("font", resolved_index) pointer.
 *
 * Frameless function: style@<si>, font_index@<edi>.
 *
 * 0x19bcc0 / draw_string.obj
 */
void *FUN_0019bcc0(int16_t style, int font_index)
{
  int tag_handle;
  void *font_tag;

  if (style != (int16_t)-1) {
    if (style < 0 || style >= 4) {
      display_assert(
        "style==_text_style_plain || (style>=0 && style<NUMBER_OF_TEXT_STYLES)",
        "c:\\halo\\SOURCE\\text\\draw_string.c", 0x406, 1);
      system_exit(-1);
    }
    font_tag = tag_get(0x666f6e74, font_index);
    tag_handle = *(int *)((char *)font_tag + 0x48 + (int)style * 0x10);
    if (tag_handle == -1)
      tag_handle = font_index;
  } else {
    tag_handle = font_index;
  }
  return tag_get(0x666f6e74, tag_handle);
}

/*
 * FUN_0019c0a0 — advance a wide-char string tokenizer by one character.
 *
 * Reads the next wide character (int16_t) from state->buffer[pos], stores it
 * in state->current_char (+0x12), increments state->pos (+0xc), then
 * classifies and stores the token type at state->token_type (+0x14):
 *   '\0' (0)    → type 0 (end of string)
 *   '\t' (9)    → type 3 (tab)
 *   '\r' (13)   → type 1 (newline)
 *   '|n' (7c 6e) → type 1, char = '\r' (escape sequence for newline)
 *   other        → type 6 (printable/other)
 * Returns the token type.
 *
 * state@<eax>: pointer to { ...; int *buffer (+8); short pos (+0xc);
 *              short current_char (+0x12); short token_type (+0x14); ... }
 *
 * 0x19c0a0 / draw_string.obj
 */
int16_t FUN_0019c0a0(void *state)
{
  char *s = (char *)state;
  short pos;
  int16_t c;
  int16_t c2;

  pos = *(short *)(s + 0xc);
  c = *(int16_t *)(*(int *)(s + 0x8) + (int)pos * 2);
  *(int16_t *)(s + 0x12) = c;
  *(short *)(s + 0xc) = (short)(pos + 1);

  switch ((unsigned short)c) {
  case 0:
    *(int16_t *)(s + 0x14) = 0;
    return *(int16_t *)(s + 0x14);
  case 9:
    *(int16_t *)(s + 0x14) = 3;
    return *(int16_t *)(s + 0x14);
  case 0xd:
    *(int16_t *)(s + 0x14) = 1;
    return *(int16_t *)(s + 0x14);
  case 0x7c:
    c2 = *(int16_t *)(*(int *)(s + 0x8) + (int)(short)(pos + 1) * 2);
    *(short *)(s + 0xc) = (short)(pos + 2);
    if (c2 == 0x6e) {
      *(int16_t *)(s + 0x12) = 0xd;
      *(int16_t *)(s + 0x14) = 1;
      return *(int16_t *)(s + 0x14);
    }
    /* fall through */
  default:
    *(int16_t *)(s + 0x14) = 6;
    break;
  }
  return *(int16_t *)(s + 0x14);
}
/* --- draw_string.obj batch drafts (2026-07-26) --- */

/* 0x130b70 */
char FUN_00130b70(void *client, const char *data, int count)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  /* cmp edi, ebx -> jge 0x130d3a */
  /* cmp (char)eax, 0x7f -> jg 0x130cde */
  _isalnum(0);
  /* test eax, eax -> jne 0x130c94 */
  _ispunct(0);
  /* test eax, eax -> jne 0x130c94 */
  /* cmp (char)eax, 0x20 -> je 0x130c94 */
  /* cmp eax, 9 -> ja 0x130cde */
  csstrncpy((char *)(uintptr_t)ecx, (char *)(uintptr_t)edi, 127);
  hs_console_evaluate((char *)(uintptr_t)edx);
  /* test (char)eax, (char)eax -> je 0x130cde */
  send_endpoint((void *)(uintptr_t)eax, (char *)0x00261f2c, 0);
  /* test eax, eax -> jg 0x130cde */
  csstrlen((char *)(uintptr_t)eax);
  /* test eax, eax -> jle 0x130cb2 */
  csstrlen((char *)0x0029a8f8);
  send_endpoint((void *)(uintptr_t)ecx, (char *)0x0029a8f8, 0);
  destroy_endpoint((void *)(uintptr_t)edx);
  csstrlen((char *)(uintptr_t)ebx);
  /* cmp eax, 0x80 -> jge 0x130cf6 */
  send_endpoint((void *)(uintptr_t)edx, (char *)(uintptr_t)edi, 0);
  /* test eax, eax -> jg 0x130cde */
  FUN_00081c80(0);
  error(0, (char *)0x0029a8d0);
  csstrlen((char *)0x0029a8a0);
  send_endpoint((void *)(uintptr_t)eax, (char *)0x0029a8a0, 0);
  /* test eax, eax -> jg 0x130d37 */
  FUN_00081c80(0);
  error(0, (char *)0x0029a8d0);
  /* test (char)eax, (char)eax -> je 0x130eb3 */
  FUN_00083040(0, 0);
  /* test (char)eax, (char)eax -> je 0x130e26 */
  FUN_00084450(0);
  /* test edi, edi -> je 0x130e25 */
  /* relift: cmp dword ptr [eax], 0 -> je 0x130dc4 */
  /* cmp eax, 0x46ef68 -> jl 0x130db0 */
  csstrlen((char *)0x0029a998);
  send_endpoint((void *)(uintptr_t)edi, (char *)0x0029a998, 0);
  /* test eax, eax -> jg 0x130dec */
  destroy_endpoint((void *)(uintptr_t)edi);
  /* cmp esi, 1 -> jne 0x130e25 */
  csstrlen((char *)0x0029a950);
  send_endpoint((void *)(uintptr_t)edi, (char *)0x0029a950, 0);
  destroy_endpoint((void *)(uintptr_t)edi);
  /* test eax, eax -> je 0x130eb2 */
  FUN_00083040(0, 0);
  /* test (char)eax, (char)eax -> je 0x130eb2 */
  recv_endpoint((void *)(uintptr_t)eax, (void *)(uintptr_t)edx, 32);
  /* relift: tail-call FUN_00130b70(); */
  /* test (char)eax, (char)eax -> jne 0x130eb2 */
  error(0, (char *)0x0029a930);
  FUN_00081c80(0);
  error(0, (char *)0x0029a908);
  /* test eax, eax -> je 0x130eb2 */
  destroy_endpoint((void *)(uintptr_t)eax);
  /* mem[0x0046eee4] = 0 */
  game_state_data_new((char *)0x0029a9e0, 12, 700);
  /* mem[0x005a90d4] = eax */
  error(eax, (char *)0x0029a9bc);
  data_delete_all((void *)(uintptr_t)eax);
  data_make_invalid((void *)(uintptr_t)eax);
  /* test eax, eax -> je 0x130f23 */
  /* mem[0x005a90d4] = 0 */
  tag_get('!tna', 0);
  data_new_at_index((void *)(uintptr_t)eax);
  datum_get((void *)(uintptr_t)ecx, 0);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  tag_get('mtib', 0);
  /* cmp ecx, edx -> jge 0x1310bd */
  tag_block_get_element((void *)(uintptr_t)eax, 0, 64);
  /* cmp ecx, ebx -> je 0x1310bd */
  tag_block_get_element((void *)(uintptr_t)eax, 0, 32);
  FUN_00076ff0(0, 0);
  /* cmp eax, ebx -> je 0x1310bd */
  /* cmp eax, edx -> jl 0x130fd0 */
  datum_delete((void *)(uintptr_t)ecx, 0);
  object_get_markers_by_string_id(0, (void *)(uintptr_t)ecx, (void *)(uintptr_t)eax, 0);
  scenario_location_from_point((void *)(uintptr_t)eax, (void *)(uintptr_t)edx);
  FUN_001d9068();
  /* test (char)eax, 0x41 -> je 0x131223 */
  FUN_001d9068();
  /* test (char)eax, 0x41 -> je 0x131223 */
  FUN_001d9068();
  /* test (char)eax, 0x41 -> jne 0x131269 */
  /* test eax, eax -> jle 0x131269 */
  /* cmp eax, ebx -> jl 0x131235 */
  /* test (char)eax, 0x41 -> jne 0x1312e8 */
  FUN_0018d2c0((void *)(uintptr_t)edx, ecx, eax, 0x00326b30, 0);
  tag_block_get_element((void *)(uintptr_t)ebx, 0, 0);
  /* test (char)eax, 0x41 -> jne 0x1313c0 */
  FUN_0018d6e0((void *)(uintptr_t)edx, 0, ecx, 0, (float *)(uintptr_t)esi, (float *)(uintptr_t)eax, 0.0f, 0.0f, (float *)0, 0.0f, 0);
  /* cmp eax, ecx -> jl 0x131320 */
  FUN_0018d360((void *)(uintptr_t)eax);
  FUN_00131150();
  /* test (char)eax, (char)eax -> jne 0x1316eb */
  /* test (char)eax, 0x41 -> jne 0x1316eb */
  /* test edx, edx -> jle 0x1316ea */
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  tag_get(0x70706879, 0);
  FUN_00154a50(0, 0, (void *)0, 0, (float *)0, (float *)0, (float *)0, (float *)0, (void *)0, 0.0f, 0.0f);
  normalize3d((float *)0);
  FUN_0010c510((float *)(uintptr_t)eax, (float *)(uintptr_t)edx);
  rotate_vector3d_by_sincos((float *)(uintptr_t)edx, (float *)(uintptr_t)ecx, 0.0f, 0.0f);
  /* cmp eax, edx -> jl 0x131463 */
  object_get_and_verify_type(0, 0);
  datum_get((void *)(uintptr_t)ecx, 0);
  tag_get('!tna', 0);
  /* test (char)eax, (char)eax -> jne 0x13177f */
  FUN_001313f0();
  FUN_001313f0();
  FUN_001313f0();
  FUN_00131280();
  data_next_index((void *)(uintptr_t)eax, 0);
  /* cmp edi, -1 -> je 0x131832 */
  datum_get((void *)(uintptr_t)ecx, 0);
  tag_get('!tna', 0);
  /* test (char)eax, (char)eax -> jne 0x13181b */
  /* cmp (int16_t)eax, 5 -> jge 0x13181b */
  /* test (char)eax, 0x41 -> jne 0x131807 */
  FUN_001313f0();
  data_next_index((void *)(uintptr_t)eax, 0);
  /* cmp edi, -1 -> jne 0x1317b1 */
  /* test edi, edi -> jne 0x131871 */
  display_assert((char *)0x0029aa24, (char *)0x0029aa38, 96, 0);
  system_exit(0);
  /* test (int16_t)ebx, (int16_t)ebx -> jl 0x131880 */
  /* relift: cmp (int16_t)ebx, word ptr [edi + 0xc] -> jl 0x13189d */
  display_assert((char *)0x0029aa08, (char *)0x0029aa38, 97, 0);
  system_exit(0);
  /* test (int16_t)esi, (int16_t)esi -> jl 0x1318ac */
  /* relift: cmp (int16_t)esi, word ptr [edi + 0xe] -> jl 0x1318c9 */
  display_assert((char *)0x0029a9e8, (char *)0x0029aa38, 98, 0);
  system_exit(0);
  /* test edi, edi -> jne 0x131921 */
  display_assert((char *)0x0029aa24, (char *)0x0029aa38, 109, 0);
  system_exit(0);
  /* test (int16_t)ebx, (int16_t)ebx -> jl 0x131936 */
  /* cmp ecx, eax -> jl 0x131953 */
  display_assert((char *)0x0029aa80, (char *)0x0029aa38, 110, 0);
  system_exit(0);
  /* test (int16_t)esi, (int16_t)esi -> jl 0x131968 */
  /* cmp eax, edx -> jl 0x131985 */
  display_assert((char *)0x0029aa60, (char *)0x0029aa38, 111, 0);
  system_exit(0);
  game_state_data_new((char *)0x0029aac0, 0, 5820);
  /* mem[0x005a90d0] = eax */
  error(eax, (char *)0x0029aaa0);
  data_delete_all((void *)(uintptr_t)eax);
  data_make_invalid((void *)(uintptr_t)eax);
  /* test eax, eax -> je 0x131a13 */
  /* mem[0x005a90d0] = 0 */
  /* cmp edi, ecx -> jge 0x131b1e */
  /* relift: cmp word ptr [ebp + 0x10], 0 -> jl 0x131b0f */
  /* test (int16_t)ebx, (int16_t)ebx -> jl 0x131b0f */
  /* cmp esi, ecx -> jge 0x131b0f */
  /* cmp edi, eax -> jge 0x131b0f */
  /* cmp (int16_t)ecx, 4 -> je 0x131ab5 */
  /* cmp (int16_t)ecx, 5 -> je 0x131ab5 */
  /* cmp (int16_t)ecx, 4 -> je 0x131ad5 */
  /* cmp (int16_t)ecx, 2 -> je 0x131ad5 */
  telnet_console_print();
  /* cmp (int16_t)esi, (int16_t)edi -> jne 0x131afe */
  /* cmp edi, ecx -> jl 0x131a70 */
  datum_delete((void *)(uintptr_t)ecx, 0);
  tag_block_get_element((void *)(uintptr_t)edi, 0, 52);
  object_get_markers_by_string_id(0, (void *)(uintptr_t)eax, (void *)0, 0);
  /* relift: cmp esi, dword ptr [edi] -> jl 0x131b80 */
  scenario_location_from_point((void *)(uintptr_t)edx, (void *)(uintptr_t)edi);
  /* test (char)ecx, (char)ecx -> jne 0x131df6 */
  /* relift: cmp word ptr [ebx + 0xe], (int16_t)esi -> jle 0x131c08 */
  /* relift: cmp (int16_t)eax, word ptr [ebx + 0xe] -> jl 0x131bf5 */
  /* relift: cmp (int16_t)esi, word ptr [ebx + 0xe] -> jge 0x131d0b */
  tag_block_get_element((void *)(uintptr_t)eax, 0, 52);
  /* test (int16_t)eax, (int16_t)eax -> jge 0x131c46 */
  /* cmp eax, ecx -> jg 0x131c58 */
  FUN_001d9068();
  /* test (char)eax, 0x41 -> je 0x131d8e */
  FUN_001d9068();
  /* test (char)eax, 0x41 -> je 0x131d8e */
  FUN_001d9068();
  /* test (char)eax, 0x41 -> jne 0x131de6 */
  /* relift: cmp word ptr [ebx + 0xc], (int16_t)edi -> jle 0x131de3 */
  /* test (int16_t)eax, (int16_t)eax -> jle 0x131dd9 */
  FUN_00131840();
  /* cmp (int16_t)esi, (int16_t)eax -> jl 0x131da7 */
  /* relift: cmp (int16_t)edi, word ptr [ebx + 0xc] -> jl 0x131da0 */
  /* relift: cmp word ptr [esi + 8], (int16_t)edi -> je 0x131ebe */
  /* relift: cmp (int16_t)edi, word ptr [esi + 0xe] -> jge 0x131ebd */
  tag_block_get_element((void *)(uintptr_t)eax, 0, 52);
  /* test (int16_t)ecx, (int16_t)ecx -> jge 0x131e59 */
  /* cmp ecx, eax -> jg 0x131e6b */
  FUN_00131a20();
  FUN_00131a20();
  /* test (int16_t)ecx, (int16_t)ecx -> je 0x131fae */
  /* cmp (int16_t)ecx, 4 -> je 0x131efb */
  /* cmp (int16_t)ecx, 3 -> jne 0x131f39 */
  FUN_00131a20();
  /* cmp (int16_t)ecx, 4 -> jne 0x131f57 */
  FUN_00131a20();
  /* cmp (int16_t)ecx, 1 -> jne 0x131f84 */
  FUN_00131a20();
  FUN_00131a20();
  /* cmp (int16_t)ecx, 2 -> jne 0x131fac */
  FUN_00131a20();
  FUN_00131a20();
  object_get_and_verify_type(0, 0);
  FUN_00131b60();
  FUN_0018f3e0((void *)(uintptr_t)ecx, (void *)(uintptr_t)eax, (void *)(uintptr_t)ecx);
  /* test (char)eax, (char)eax -> jne 0x13244b */
  /* test (int16_t)ebx, (int16_t)ebx -> je 0x1320c3 */
  /* test (int16_t)ebx, (int16_t)ebx -> je 0x1320e0 */
  /* test ecx, ecx -> je 0x13243d */
  FUN_00131840();
  tag_get('yhpp', 0);
  tag_get('yhpp', 0);
  random_math_get_local_seed_address();
  random_seed_get_direction3d((void *)(uintptr_t)eax, (float *)0);
  tag_get(0x70706879, 0);
  FUN_00154a50(0, 0, (void *)0, 0, (float *)0, (float *)0, (float *)0, (float *)0, (void *)0, 0.0f, 0.0f);
  /* relift: cmp word ptr [ebp - 0x10], 0 -> jne 0x132214 */
  /* cmp (int16_t)eax, 0xffff -> je 0x132214 */
  /* test (int16_t)eax, (int16_t)eax -> jl 0x1322f5 */
  /* relift: cmp (int16_t)eax, word ptr [edi + 0xc] -> jge 0x1322f5 */
  /* test (int16_t)ecx, (int16_t)ecx -> jl 0x1322f5 */
  /* relift: cmp (int16_t)ecx, word ptr [edi + 0xe] -> jge 0x1322f5 */
  FUN_00131840();
  /* relift: cmp word ptr [ebp - 0x10], 0 -> je 0x132344 */
  /* test (int16_t)ecx, (int16_t)ecx -> jne 0x132344 */
  /* relift: cmp word ptr [ebp - 0x10], 0 -> jne 0x1323c0 */
  object_get_and_verify_type(0, 0);
  /* relift: cmp word ptr [eax + 0x68], 0 -> je 0x13248f */
  /* relift: cmp dword ptr [ebp - 0x18], -1 -> jne 0x1324a1 */
  rasterizer_widget_submit(0);
  rasterizer_widget_set_zbuffer_enable(0, 0);
  /* cmp eax, -1 -> je 0x132c5e */
  object_get_and_verify_type(0, 0);
  tag_get('ejbo', 0);
  rasterizer_widget_draw_sprite3d(0);
  rasterizer_widget_begin(0);
  csmemset((void *)0, 0, 0);
  FUN_00131840();
  /* cmp ebx, eax -> jl 0x1325c2 */
  FUN_00131840();
  FUN_00131840();
  FUN_00131840();
  FUN_00180d10(0, 0, 0, 0, (void *)0, 0);
  /* test ecx, ecx -> jle 0x132a54 */
  telnet_console_print();
  /* cmp eax, 5 -> ja 0x132a26 */
  /* relift: cmp (int16_t)eax, word ptr [ebp - 8] -> jl 0x1327be */
  display_assert((char *)0x0029aad0, (char *)0x0029aa38, 742, 0);
  system_exit(0);
  display_assert((char *)0x0029aad0, (char *)0x0029aa38, 747, 0);
  system_exit(0);
  /* relift: cmp (int16_t)eax, word ptr [ebp - 8] -> jl 0x1328b2 */
  display_assert((char *)0x0029aad0, (char *)0x0029aa38, 754, 0);
  system_exit(0);
  /* relift: cmp (int16_t)eax, word ptr [ebp - 8] -> jl 0x132923 */
  display_assert((char *)0x0029aad0, (char *)0x0029aa38, 761, 0);
  system_exit(0);
  /* relift: cmp (int16_t)eax, word ptr [ebp - 8] -> jl 0x132996 */
  display_assert((char *)0x0029aad0, (char *)0x0029aa38, 768, 0);
  system_exit(0);
  /* relift: cmp (int16_t)eax, word ptr [ebp - 8] -> jl 0x1329de */
  display_assert((char *)0x0029aad0, (char *)0x0029aa38, 775, 0);
  system_exit(0);
  display_assert((char *)0, (char *)0x0029aa38, 784, 0);
  system_exit(0);
  /* cmp ecx, eax -> jl 0x132770 */
  /* cmp eax, edx -> jl 0x132760 */
  rasterizer_widget_set_texture(0);
  rasterizer_widget_end(0);
  tag_get('rdhs', 0);
  display_assert((char *)0x0029aa08, (char *)0x0029aa38, 97, 0);
  system_exit(0);
  /* relift: cmp word ptr [esi + 0xe], 0 -> jg 0x132ad6 */
  display_assert((char *)0x0029a9e8, (char *)0x0029aa38, 98, 0);
  system_exit(0);
  FUN_00131840();
  FUN_00131840();
  FUN_00131840();
  csmemset((void *)0, 0, 0);
  rasterizer_psuedo_dynamic_screen_quad_draw(0);
  FUN_0017d1a0(0);
  FUN_0017cbb0((void *)(uintptr_t)eax, 0);
  shader_type_is_transparent(ecx);
  FUN_0017cbd0(0, 0, 0, 0, 0, 0, 0, (float *)(uintptr_t)edx, 0);
  FUN_0017cbc0(0, 0, 0, 0, 0, 0, 0);
  FUN_0017cbe0();
  FUN_0017cbf0();
  rasterizer_psuedo_dynamic_screen_quad_draw(0);
  rasterizer_widget_set_tint_factor(0);
  rasterizer_widget_submit_occlusion_test(0);
  global_scenario_get();
  /* cmp ecx, -1 -> je 0x132e0c */
  tag_get('galf', 0);
  data_new_at_index((void *)(uintptr_t)eax);
  datum_get((void *)(uintptr_t)ecx, 0);
  /* cmp edx, 0xe1 -> jge 0x132e06 */
  /* cmp (int16_t)eax, 0x28 -> jge 0x132e06 */
  /* cmp ecx, eax -> je 0x132e06 */
  /* relift: cmp word ptr [esi + 0xe], (int16_t)ecx -> jle 0x132dd8 */
  FUN_00131840();
  /* cmp eax, ecx -> jge 0x132dcf */
  /* cmp eax, edx -> jge 0x132dcf */
  telnet_console_print();
  /* relift: cmp (int16_t)ebx, word ptr [esi + 0xe] -> jl 0x132d60 */
  FUN_00131e00();
  FUN_00131ed0();
  object_get_and_verify_type(0, 0);
  datum_get((void *)(uintptr_t)ecx, 0);
  tag_get('galf', 0);
  /* test (char)eax, (char)eax -> jne 0x132e7a */
  FUN_00131fc0();
  flag_render_proper();
  data_next_index((void *)(uintptr_t)eax, 0);
  /* cmp edi, -1 -> je 0x132f2e */
  datum_get((void *)(uintptr_t)ecx, 0);
  tag_get('galf', 0);
  /* cmp (int16_t)eax, 5 -> jge 0x132f16 */
  FUN_00131fc0();
  data_next_index((void *)(uintptr_t)ecx, 0);
  /* cmp edi, -1 -> jne 0x132ec0 */
  /* test eax, eax -> je 0x132f62 */
  data_delete_all((void *)(uintptr_t)eax);
  /* test eax, eax -> je 0x132f72 */
  data_delete_all((void *)(uintptr_t)eax);
  /* test eax, eax -> je 0x132f92 */
  data_make_invalid((void *)(uintptr_t)eax);
  /* test eax, eax -> je 0x132fa2 */
  data_make_invalid((void *)(uintptr_t)eax);
  data_new_at_index((void *)(uintptr_t)eax);
  datum_get((void *)(uintptr_t)ecx, 0);
  tag_get('!wlg', 0);
  tag_get('mtib', 0);
  /* relift: cmp word ptr [eax], 3 -> jne 0x133088 */
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  FUN_00077040(0, 0, 0);
  FUN_001d9068();
  datum_get((void *)(uintptr_t)eax, 0);
  /* test eax, eax -> je 0x1330de */
  datum_delete((void *)(uintptr_t)edx, 0);
  datum_delete((void *)(uintptr_t)eax, 0);
  tag_get(0x676c7721, 0);
  /* test (char)ecx, 8 -> je 0x133165 */
  /* test (char)eax, 0x41 -> jne 0x13315e */
  tag_get(0x676c7721, 0);
  /* test (char)ecx, 0x10 -> je 0x1331c7 */
  /* test (char)eax, 0x41 -> jne 0x1331c1 */
  tag_get(0x676c7721, 0);
  /* test (char)ecx, 0x20 -> je 0x13323f */
  /* test (char)eax, 0x41 -> jne 0x133224 */
  tag_get(0x676c7721, 0);
  tag_get('!wlg', 0);
  /* relift: cmp (int16_t)ecx, word ptr [esi + 0x52] -> jle 0x1332fb */
  /* test ecx, ecx -> je 0x1332dc */
  datum_delete((void *)(uintptr_t)eax, 0);
  tag_get(0x676c7721, 0);
  /* cmp (int16_t)eax, 0xffff -> je 0x13339b */
  object_get_function_value(0, 0, (void *)(uintptr_t)ecx);
  /* test (char)eax, (char)eax -> jne 0x133347 */
  /* relift: test byte ptr [esi + 0x28], 1 -> je 0x133403 */
  /* test (char)eax, 0x41 -> jne 0x13344f */
  /* test (char)eax, 0x41 -> jne 0x13348c */
  data_new_at_index((void *)(uintptr_t)eax);
  /* cmp esi, -1 -> je 0x1334df */
  datum_get((void *)(uintptr_t)ecx, 0);
  datum_get((void *)(uintptr_t)ecx, 0);
  tag_get('!wlg', 0);
  FUN_0018d2c0((void *)(uintptr_t)edx, ecx, eax, 0x00326a78, 0);
  /* test esi, esi -> je 0x1335bc */
  FUN_0018d6e0((void *)(uintptr_t)eax, 0, 0, 0, (float *)(uintptr_t)edx, (float *)(uintptr_t)ecx, 0.0f, 0.0f, (float *)0, 0.0f, 0);
  /* test esi, esi -> jne 0x133580 */
  FUN_0018d360((void *)(uintptr_t)ecx);
  /* test (char)eax, 1 -> jne 0x1335fd */
  display_assert((char *)0x0029aae4, (char *)0x0025ed80, 1530, 0);
  system_exit(0);
  FUN_001335e0(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
  FUN_001335e0(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
  FUN_001335e0(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
  /* test eax, eax -> jne 0x1337bb */
  game_state_data_new((char *)0x0029ab58, 0, 604);
  /* mem[0x005a90c8] = eax */
  /* test eax, eax -> jne 0x1337bb */
  game_state_data_new((char *)0x0029ab48, 512, 100);
  /* mem[0x005a90cc] = eax */
  error(0, (char *)0x0029ab1c);
  error(0, (char *)0x0029aaf8);
  tag_get(0x676c7721, 0);
  data_new_at_index((void *)(uintptr_t)edx);
  /* cmp ebx, -1 -> je 0x13398a */
  datum_get((void *)(uintptr_t)eax, 0);
  /* relift: cmp word ptr [esi + 0x80], (int16_t)ebx -> jne 0x133844 */
  random_math_get_local_seed_address();
  random_real_range((void *)(uintptr_t)eax, 0.0f, 0.0f);
  /* relift: cmp word ptr [esi + 0x9c], (int16_t)ebx -> jne 0x13388f */
  random_math_get_local_seed_address();
  random_real_range((void *)(uintptr_t)eax, 0.0f, 0.0f);
  /* relift: cmp word ptr [esi + 0xb0], -1 -> jne 0x133905 */
  /* relift: test byte ptr [esi + 0x28], 1 -> jne 0x133905 */
  random_math_get_local_seed_address();
  random_real_range((void *)(uintptr_t)eax, 0.0f, 0.0f);
  display_assert((char *)0, (char *)0x0029ab60, 945, 0);
  system_exit(0);
  random_math_get_local_seed_address();
  random_real_range((void *)(uintptr_t)eax, 0.0f, 0.0f);
  random_math_get_local_seed_address();
  random_real_range((void *)(uintptr_t)eax, 0.0f, 0.0f);
  /* test (char)eax, 0x41 -> je 0x1339ea */
  /* cmp ecx, edx -> jl 0x1339c0 */
  display_assert((char *)0x0029aba4, (char *)0x0029ab60, 1079, 0);
  system_exit(0);
  /* test (int16_t)ebx, (int16_t)ebx -> jge 0x133a20 */
  /* cmp eax, ecx -> jle 0x133a2b */
  /* relift: cmp word ptr [esi + 4], 1 -> jg 0x133a56 */
  display_assert((char *)0x0029ab88, (char *)0x0029ab60, 1083, 0);
  system_exit(0);
  /* test edx, edx -> jle 0x133aaa */
  /* cmp ecx, edx -> jl 0x133a80 */
  /* cmp edi, edx -> jl 0x133ad1 */
  display_assert((char *)0x0029aba4, (char *)0x0029ab60, 1180, 0);
  system_exit(0);
  /* test (int16_t)ebx, (int16_t)ebx -> jge 0x133ada */
  /* cmp edi, eax -> jg 0x133ae5 */
  /* cmp ebx, 4 -> jge 0x133b1c */
  /* test (int16_t)eax, (int16_t)eax -> jle 0x133b06 */
  /* relift: cmp ecx, dword ptr [ebp - 0x14] -> jge 0x133b0c */
  /* cmp ebx, 4 -> jl 0x133b00 */
  FUN_001336a0((float *)0, (float *)0, (float *)0, (float *)0, (float *)0, 0.0f,
               0.0f, 0.0f, 0.0f, 0.0f);
  FUN_001336a0((float *)0, (float *)0, (float *)0, (float *)0, (float *)0, 0.0f,
               0.0f, 0.0f, 0.0f, 0.0f);
  FUN_001336a0((float *)0, (float *)0, (float *)0, (float *)0, (float *)0, 0.0f,
               0.0f, 0.0f, 0.0f, 0.0f);
  tag_get(0x676c7721, 0);
  /* cmp (int16_t)eax, 0xffff -> je 0x1340e2 */
  object_get_function_value(0, 0, (void *)(uintptr_t)ecx);
  /* test (char)eax, (char)eax -> jne 0x1340b6 */
  /* test (char)ecx, 1 -> je 0x1341d4 */
  display_assert((char *)0x0029abcc, (char *)0, 0, 0);
  system_exit(0);
  get_particle_world_position(0, 0, 0.0f);
  get_particle_world_position(0, 0, 0.0f);
  get_particle_world_position(0, 0, 0.0f);
  /* test (char)eax, 0x41 -> jne 0x1341c0 */
  /* test (char)eax, 0x41 -> je 0x134202 */
  get_particle_world_position(0, 0, 0.0f);
  /* test (char)eax, 0x41 -> jne 0x1341be */
  /* test (char)eax, 0x41 -> jne 0x13426c */
  /* test (char)eax, 0x41 -> je 0x134250 */
  get_particle_world_position(0, 0, 0.0f);
  tag_get(0x676c7721, 0);
  glow_normal_particle_new(0, 0, 0);
  /* test eax, eax -> je 0x134344 */
  /* relift: test byte ptr [ecx + 0x28], 2 -> je 0x1342f5 */
  /* relift: test byte ptr [ecx + 0x28], 4 -> je 0x134318 */
  /* test ecx, ecx -> jne 0x134328 */
  /* test edi, edi -> je 0x13432f */
  tag_get(0x676c7721, 0);
  data_new_at_index((void *)(uintptr_t)ecx);
  datum_get((void *)(uintptr_t)edx, 0);
  /* relift: cmp word ptr [ebx + 4], 1 -> jle 0x1343ea */
  random_math_get_local_seed_address();
  random_real_range((void *)(uintptr_t)eax, 0.0f, 0.0f);
  get_particle_world_position(0, 0, 0.0f);
  display_assert((char *)0x0029abfc, (char *)0x0029ab60, 996, 0);
  system_exit(0);
  random_math_get_local_seed_address();
  random_real_range((void *)(uintptr_t)eax, 0.0f, 0.0f);
  random_math_get_local_seed_address();
  random_real_range((void *)(uintptr_t)eax, 0.0f, 0.0f);
  random_math_get_local_seed_address();
  random_real_range((void *)(uintptr_t)eax, 0.0f, 0.0f);
  normalize3d((float *)(uintptr_t)eax);
  random_math_get_local_seed_address();
  random_real_range((void *)(uintptr_t)eax, 0.0f, 0.0f);
  FUN_001d9068();
  random_math_get_local_seed_address();
  random_real_range((void *)(uintptr_t)eax, 0.0f, 0.0f);
  tag_get(0x676c7721, 0);
  object_get_markers_by_string_id(0, (void *)(uintptr_t)esi, (void *)(uintptr_t)ecx, 0);
  /* cmp (int16_t)eax, 1 -> jle 0x134876 */
  /* relift: cmp word ptr [ebp - 8], (int16_t)esi -> je 0x13469a */
  normalize3d((float *)0);
  /* test (int16_t)eax, (int16_t)eax -> jl 0x134711 */
  /* test (int16_t)eax, (int16_t)eax -> jl 0x134709 */
  /* relift: cmp word ptr [ebp + edi*2 - 0x24], (int16_t)ecx -> je 0x134706 */
  /* test (int16_t)eax, (int16_t)eax -> jge 0x1346f4 */
  /* cmp eax, edx -> jl 0x134730 */
  FUN_001342a0(0);
  /* cmp (int16_t)eax, 1 -> jle 0x134876 */
  /* cmp (int16_t)eax, 0xffff -> je 0x13482b */
  object_get_function_value(0, 0, (void *)(uintptr_t)ecx);
  /* test (char)eax, (char)eax -> jne 0x134815 */
  object_get_function_value(0, 0, (void *)(uintptr_t)ecx);
  /* test (char)eax, (char)eax -> jne 0x134857 */
  game_time_get();
  /* relift: cmp word ptr [ebx + 4], 1 -> jle 0x1348d0 */
  /* test esi, esi -> je 0x1348d0 */
  /* relift: test byte ptr [esi + 0x54], 2 -> jne 0x1348c9 */
  FUN_00134070(0, 0, 0, 0.0f, 0.0f);
  FUN_00133300(0, 0, 0);
  /* test esi, esi -> jne 0x134893 */
  /* test esi, esi -> je 0x1349fb */
  /* relift: test byte ptr [esi + 0x54], 2 -> je 0x1349f0 */
  game_time_get();
  FUN_001330f0(0, 0);
  tag_get('!wlg', 0);
  /* test (char)ecx, 0x10 -> je 0x13494d */
  /* test (char)eax, 0x41 -> jne 0x134947 */
  FUN_001331d0(0, 0);
  tag_get('!wlg', 0);
  tag_get('!wlg', 0);
  /* relift: cmp (int16_t)edx, word ptr [esi + 0x52] -> jle 0x1349f0 */
  /* test ecx, ecx -> je 0x1349d0 */
  datum_delete((void *)(uintptr_t)ecx, 0);
  /* test esi, esi -> jne 0x1348e0 */
  /* test (char)eax, 0x41 -> jne 0x134ad4 */
  /* test (char)eax, 0x41 -> jne 0x134ad4 */
  glow_trailing_particle_new(0);
  /* test eax, eax -> je 0x134ab4 */
  /* test ecx, ecx -> je 0x134a7b */
  FUN_001d9068();
  /* test (char)eax, 0x41 -> je 0x134a53 */
  display_assert((char *)0x0029ac28, (char *)0x0029ab60, 521, 0);
  system_exit(0);
  /* cmp edi, -1 -> je 0x134b4a */
  /* cmp esi, -1 -> je 0x134b49 */
  datum_get((void *)(uintptr_t)eax, 0);
  tag_get('!wlg', 0);
  datum_get((void *)(uintptr_t)edx, 0);
  FUN_001345b0(0, 0);
  object_get_markers_by_string_id(0, (void *)(uintptr_t)ebx, (void *)(uintptr_t)eax, 0);
  FUN_00133520(0, 0);
  game_state_data_new((char *)0x0029acc8, 256, 0);
  /* mem[0x0046f020] = eax */
  return 0;

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x19b510 */
void draw_string_get_string(void)
{
  int esi = 0;

  /* test (int16_t)esi, (int16_t)esi -> jl 0x19b522 */
  /* cmp (int16_t)esi, 1 -> jl 0x19b542 */
  display_assert((char *)0x002b41e4, (char *)0x002b4210, 341, 0);
  system_exit(0);
  FUN_0019d3c0(0, 0);

  (void)esi;
}

/* 0x19b5d0 */
void draw_string_set_indents(int width, int height)
{
  int edi = 0;

  display_assert((char *)0x002b4278, (char *)0x002b4210, 366, 0);
  system_exit(0);
  /* test (int16_t)edi, (int16_t)edi -> jge 0x19b627 */
  display_assert((char *)0x002b4264, (char *)0x002b4210, 367, 0);
  system_exit(0);

  (void)edi;
}

/* 0x19b790 */
void draw_string_get_color(void)
{
  int esi = 0;

  /* test esi, esi -> jne 0x19b7bb */
  display_assert((char *)0x00269fd8, (char *)0x002b4210, 392, 0);
  system_exit(0);

  (void)esi;
}

/* 0x19b7e0 */
void FUN_0019B7E0(void)
{
  int esi = 0;

  tag_get(0x666f6e74, 0);
  /* mem[0x004d9b0c] = esi */

  (void)esi;
}

/* 0x19b8f0 */
void draw_string_set_highlight(void)
{
  /* relift: no calls detected — manual review */
}

/* 0x19b910 */
void bitmap_draw_character(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;

  /* test (int16_t)ecx, (int16_t)ecx -> jle 0x19bc9c */
  bitmap_format_bits_per_pixel(0);
  /* relift: cmp (int16_t)eax, word ptr [ecx + 6] -> jle 0x19ba2d */
  display_assert((char *)0x002b443c, (char *)0x002b4210, 486, 0);
  system_exit(0);
  /* test (int16_t)edx, (int16_t)edx -> jl 0x19ba52 */
  /* cmp edx, ecx -> jle 0x19ba76 */
  display_assert((char *)0x002b43fc, (char *)0x002b4210, 487, 0);
  system_exit(0);
  /* cmp ecx, 0xb -> ja 0x19bc5f */
  /* test (int16_t)eax, (int16_t)eax -> jle 0x19bc7f */
  /* test (int16_t)eax, (int16_t)eax -> je 0x19bac6 */
  /* cmp eax, ecx -> jle 0x19bac4 */
  /* test (int16_t)eax, (int16_t)eax -> jle 0x19bc7f */
  /* test (char)eax, (char)eax -> je 0x19bb71 */
  /* test (int16_t)eax, (int16_t)eax -> jle 0x19bc7f */
  /* test (int16_t)ecx, (int16_t)ecx -> je 0x19bc49 */
  display_assert((char *)0x00261888, (char *)0x002b4210, 556, 0);
  system_exit(0);

  (void)eax;
  (void)ecx;
  (void)edx;
}

/* 0x19bd30 */
void FUN_0019bd30(void)
{
  int esi = 0;

  /* test (int16_t)esi, (int16_t)esi -> jl 0x19bd4b */
  /* cmp (int16_t)esi, 4 -> jl 0x19bd6b */
  display_assert((char *)0x002b4388, (char *)0x002b4210, 1045, 0);
  system_exit(0);
  /* test (int16_t)eax, (int16_t)eax -> jl 0x19bd7a */
  /* cmp (int16_t)eax, 3 -> jl 0x19bd9e */
  display_assert((char *)0x002b4348, (char *)0x002b4210, 1046, 0);
  system_exit(0);
  FUN_001d9068();
  FUN_001d9068();
  FUN_001d9068();
  FUN_001d9068();
  FUN_0019bcc0(0, 0);

  (void)esi;
}

/* 0x19be30 */
void parse_string(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int esi = 0;

  unicode_cursor_forward((char *)(uintptr_t)eax, (void *)(uintptr_t)esi);
  crt_tolower(0);
  /* cmp eax, 0x13 -> ja 0x19bf06 */
  /* cmp eax, -1 -> je 0x19bf76 */
  /* cmp eax, 7 -> jne 0x19bf26 */
  FUN_0019bcc0(0, 0);
  /* cmp (int16_t)ebx, 7 -> je 0x19be40 */
  /* cmp (int16_t)ebx, 5 -> je 0x19be40 */
  /* cmp (int16_t)ebx, -1 -> jne 0x19bf60 */
  display_assert((char *)0x002b4478, (char *)0x002b4210, 1194, 0);
  system_exit(0);
  /* test eax, eax -> je 0x19c056 */
  /* cmp eax, 9 -> je 0x19c04c */
  /* cmp eax, 0xd -> je 0x19c042 */
  unicode_cursor_forward((char *)(uintptr_t)ecx, (void *)(uintptr_t)eax);
  FUN_0019d3c0(0, 0);
  FUN_0019d3c0(0, 0);
  FUN_0019d3c0(0, 0);
  /* test (int16_t)ebx, (int16_t)ebx -> jne 0x19c009 */
  FUN_0019d380();
  /* test (char)eax, (char)eax -> je 0x19c038 */
  FUN_0019d380();
  /* test (char)eax, (char)eax -> jne 0x19c038 */
  FUN_0019d380();
  /* test (char)eax, (char)eax -> jne 0x19c038 */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)esi;
}

/* 0x19c1b0 */
void FUN_0019c1b0(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  /* cmp (int16_t)ecx, (int16_t)esi -> jle 0x19c1e7 */
  /* cmp (int16_t)ecx, 0x7fff -> jge 0x19c1f9 */
  /* cmp (int16_t)ecx, 0x8000 -> jle 0x19c20a */
  /* cmp (int16_t)eax, 0x7fff -> jge 0x19c219 */
  /* test ecx, ecx -> je 0x19c25f */
  /* cmp (int16_t)eax, (int16_t)esi -> jle 0x19c230 */
  /* cmp (int16_t)eax, (int16_t)edx -> jge 0x19c240 */
  /* cmp (int16_t)eax, (int16_t)edi -> jle 0x19c24f */
  /* cmp (int16_t)eax, (int16_t)ebx -> jge 0x19c25f */
  /* cmp (int16_t)esi, (int16_t)edx -> jge 0x19c3b4 */
  /* cmp (int16_t)edi, (int16_t)ebx -> jge 0x19c3b4 */
  FUN_0019bd30();
  /* relift: cmp (int16_t)eax, word ptr [0x4d9b4a] -> jl 0x19c2cc */
  /* relift: cmp (int16_t)eax, word ptr [0x4d9b4c] -> jge 0x19c2cc */
  parse_string();
  FUN_0019cff0(0, 0);
  /* cmp eax, edi -> je 0x19c3a6 */
  /* cmp edi, ebx -> jle 0x19c33e */
  /* cmp (int16_t)ecx, (int16_t)ebx -> jge 0x19c351 */
  /* cmp edi, ebx -> jle 0x19c369 */
  /* cmp (int16_t)edx, (int16_t)ebx -> jge 0x19c37d */
  /* test (int16_t)esi, (int16_t)esi -> jle 0x19c3a6 */
  /* test (int16_t)edi, (int16_t)edi -> jle 0x19c3a6 */
  /* relift: cmp (int16_t)eax, word ptr [ebp + 0x20] -> jl 0x19c2b0 */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x19c3c0 */
void FUN_0019c3c0(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  /* cmp (int16_t)ecx, (int16_t)esi -> jle 0x19c3f7 */
  /* cmp (int16_t)ecx, 0x7fff -> jge 0x19c409 */
  /* cmp (int16_t)ecx, 0x8000 -> jle 0x19c41a */
  /* cmp (int16_t)eax, 0x7fff -> jge 0x19c429 */
  /* test ecx, ecx -> je 0x19c46f */
  /* cmp (int16_t)eax, (int16_t)esi -> jle 0x19c440 */
  /* cmp (int16_t)eax, (int16_t)edx -> jge 0x19c450 */
  /* cmp (int16_t)eax, (int16_t)edi -> jle 0x19c45f */
  /* cmp (int16_t)eax, (int16_t)ebx -> jge 0x19c46f */
  /* cmp (int16_t)esi, (int16_t)edx -> jge 0x19c5c3 */
  /* cmp (int16_t)edi, (int16_t)ebx -> jge 0x19c5c3 */
  FUN_0019bd30();
  /* relift: cmp (int16_t)eax, word ptr [0x4d9b4a] -> jl 0x19c4dc */
  /* relift: cmp (int16_t)eax, word ptr [0x4d9b4c] -> jge 0x19c4dc */
  FUN_0019c0a0((void *)0);
  FUN_0019cff0(0, 0);
  /* cmp eax, edi -> je 0x19c5b5 */
  /* cmp edi, ebx -> jle 0x19c54d */
  /* cmp (int16_t)ecx, (int16_t)ebx -> jge 0x19c560 */
  /* cmp edi, ebx -> jle 0x19c578 */
  /* cmp (int16_t)edx, (int16_t)ebx -> jge 0x19c58c */
  /* test (int16_t)esi, (int16_t)esi -> jle 0x19c5b5 */
  /* test (int16_t)edi, (int16_t)edi -> jle 0x19c5b5 */
  /* relift: cmp (int16_t)eax, word ptr [ebp + 0x20] -> jl 0x19c4c0 */
  display_assert((char *)0x0026184c, (char *)0x002b4210, 639, 0);
  system_exit(0);
  /* cmp edi, ebx -> jne 0x19c635 */
  display_assert((char *)0x0027b838, (char *)0x002b4210, 640, 0);
  system_exit(0);
  FUN_0019bd30();
  /* cmp (int16_t)esi, (int16_t)ebx -> jl 0x19c69d */
  /* cmp (int16_t)esi, (int16_t)eax -> jle 0x19c6bd */
  display_assert((char *)0x002b4488, (char *)0x002b4210, 672, 0);
  system_exit(0);
  /* cmp (int16_t)esi, (int16_t)ebx -> je 0x19c6cf */
  parse_string();
  /* cmp (int16_t)eax, 2 -> je 0x19c784 */
  /* cmp (int16_t)eax, 6 -> je 0x19c784 */
  FUN_0019cff0(0, 0);
  /* test eax, eax -> je 0x19c7fa */
  /* relift: cmp word ptr [ebp - 0x40], 2 -> je 0x19c7b1 */
  /* cmp (int16_t)edi, 2 -> jne 0x19c7b1 */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}
