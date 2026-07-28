#include <stdint.h>
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
 * Frameless function: style, font_index.
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
 * state: pointer to { ...; int *buffer (+8); short pos (+0xc);
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

/* FUN_00130b70 (0x130b70) — XBE naked draft (batch 251). */
#if defined(__clang__)
static int (*const b130b70_c1dabd3)(int c) = _isalnum;
static int (*const b130b70_c1dabaa)(int c) = _ispunct;
static void * (*const b130b70_c8de70)(char *destination, const char *source, size_t size) = csstrncpy;
static bool (*const b130b70_cc50c0)(const char *command) = hs_console_evaluate;
static int (*const b130b70_c82f50)(int *ep, const char *buf, int len) = send_endpoint;
static int (*const b130b70_c8df60)(const char *s1) = csstrlen;
static void (*const b130b70_c848c0)(int *ep) = destroy_endpoint;
static const char * (*const b130b70_c81c80)(int error_code) = FUN_00081c80;
static void (*const b130b70_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;

__attribute__((naked, noinline))
char FUN_00130b70(void *client __attribute__((unused)), const char *data __attribute__((unused)), int count __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x88, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "movb $1, %%al\n\t"
      "xorl %%edi, %%edi\n\t"
      "movb %%al, -0x1(%%ebp)\n\t"
      "movl %%edi, -0x8(%%ebp)\n\t"
      ".LFUN_00130b70_1:\n\t"
      "movl 0xc(%%ebp), %%ebx\n\t"
      "cmpl %%ebx, %%edi\n\t"
      "jge .LFUN_00130b70_11\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "addl %%eax, %%edi\n\t"
      "movb (%%edi), %%al\n\t"
      "cmpb $0x7f, %%al\n\t"
      "jg .LFUN_00130b70_8\n\t"
      "movsbl %%al, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1dabd3]\n\t"
      "addl $4, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_00130b70_5\n\t"
      "movsbl (%%edi), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c1dabaa]\n\t"
      "addl $4, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_00130b70_5\n\t"
      "movb (%%edi), %%al\n\t"
      "cmpb $0x20, %%al\n\t"
      "je .LFUN_00130b70_5\n\t"
      "movsbl %%al, %%eax\n\t"
      "addl $-4, %%eax\n\t"
      "cmpl $9, %%eax\n\t"
      "ja .LFUN_00130b70_8\n\t"
      "movzbl 0x130d50(%%eax), %%eax\n\t"
      "jmp *.LFUN_00130b70_jt(,%%eax,4)\n\t"
      ".LFUN_00130b70_2:\n\t"
      "movb 0x4(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "leal 0x4(%%esi), %%edi\n\t"
      "je .LFUN_00130b70_8\n\t"
      "pushl $0x7f\n\t"
      "leal -0x88(%%ebp), %%ecx\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "call *%[c8de70]\n\t"
      "leal -0x88(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movb $0, -0x9(%%ebp)\n\t"
      "movb $0, (%%edi)\n\t"
      "call *%[cc50c0]\n\t"
      "addl $0x10, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00130b70_8\n\t"
      "movl (%%esi), %%eax\n\t"
      "pushl $2\n\t"
      "pushl $0x261f2c\n\t"
      "pushl %%eax\n\t"
      "call *%[c82f50]\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jg .LFUN_00130b70_8\n\t"
      "jmp .LFUN_00130b70_7\n\t"
      ".LFUN_00130b70_3:\n\t"
      "movb 0x4(%%esi), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "leal 0x4(%%esi), %%eax\n\t"
      "je .LFUN_00130b70_6\n\t"
      "pushl %%eax\n\t"
      "call *%[c8df60]\n\t"
      "addl $4, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jle .LFUN_00130b70_6\n\t"
      "movb $0, 0x3(%%eax,%%esi,1)\n\t"
      "jmp .LFUN_00130b70_6\n\t"
      ".LFUN_00130b70_4:\n\t"
      "pushl $0x29a8f8\n\t"
      "call *%[c8df60]\n\t"
      "movl (%%esi), %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl $0x29a8f8\n\t"
      "pushl %%ecx\n\t"
      "call *%[c82f50]\n\t"
      "movl (%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c848c0]\n\t"
      "addl $0x14, %%esp\n\t"
      "movl $0, (%%esi)\n\t"
      "movl %%ebx, -0x8(%%ebp)\n\t"
      "jmp .LFUN_00130b70_8\n\t"
      ".LFUN_00130b70_5:\n\t"
      "leal 0x4(%%esi), %%ebx\n\t"
      "pushl %%ebx\n\t"
      "call *%[c8df60]\n\t"
      "addl $4, %%esp\n\t"
      "incl %%eax\n\t"
      "cmpl $0x80, %%eax\n\t"
      "jge .LFUN_00130b70_9\n\t"
      "movb (%%edi), %%cl\n\t"
      "movb %%cl, 0x3(%%eax,%%esi,1)\n\t"
      "movb $0, (%%ebx,%%eax,1)\n\t"
      ".LFUN_00130b70_6:\n\t"
      "movl (%%esi), %%edx\n\t"
      "pushl $1\n\t"
      "pushl %%edi\n\t"
      "pushl %%edx\n\t"
      "call *%[c82f50]\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jg .LFUN_00130b70_8\n\t"
      "pushl %%eax\n\t"
      "call *%[c81c80]\n\t"
      "pushl %%eax\n\t"
      "pushl $0x29a8d0\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $0x10, %%esp\n\t"
      ".LFUN_00130b70_7:\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      ".LFUN_00130b70_8:\n\t"
      "movl -0x8(%%ebp), %%edi\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "incl %%edi\n\t"
      "testb %%al, %%al\n\t"
      "movl %%edi, -0x8(%%ebp)\n\t"
      "jne .LFUN_00130b70_1\n\t"
      "popl %%edi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00130b70_9:\n\t"
      "pushl $0x29a8a0\n\t"
      "movb $0, 0x4(%%esi)\n\t"
      "call *%[c8df60]\n\t"
      "pushl %%eax\n\t"
      "movl (%%esi), %%eax\n\t"
      "pushl $0x29a8a0\n\t"
      "pushl %%eax\n\t"
      "call *%[c82f50]\n\t"
      "addl $0x10, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jg .LFUN_00130b70_10\n\t"
      "pushl %%eax\n\t"
      "call *%[c81c80]\n\t"
      "pushl %%eax\n\t"
      "pushl $0x29a8d0\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $0x10, %%esp\n\t"
      "popl %%edi\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00130b70_10:\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      ".LFUN_00130b70_11:\n\t"
      "popl %%edi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_00130b70_jt:\n\t"
      ".long .LFUN_00130b70_4\n\t"
      ".long .LFUN_00130b70_3\n\t"
      ".long .LFUN_00130b70_2\n\t"
      ".long .LFUN_00130b70_8\n\t"
      ".text\n\t"
      :
      : [c1dabd3] "m"(b130b70_c1dabd3), [c1dabaa] "m"(b130b70_c1dabaa), [c8de70] "m"(b130b70_c8de70), [cc50c0] "m"(b130b70_cc50c0), [c82f50] "m"(b130b70_c82f50), [c8df60] "m"(b130b70_c8df60), [c848c0] "m"(b130b70_c848c0), [c81c80] "m"(b130b70_c81c80), [c8f390] "m"(b130b70_c8f390)
      : "memory");
}
#else
#error "FUN_00130b70: clang naked draft required"
#endif


/* draw_string_get_string (0x19b510) — readable C lift. */
char *draw_string_get_string(short index)
{
  if (index < 0 || index >= 1) {
    display_assert((const char *)0x2b41e4, (const char *)0x2b4210, 0x155, 1);
    system_exit(-1);
  }
  return FUN_0019d3c0(*(int *)0x4d9b08, (short)(index + 7));
}



/* draw_string_set_indents (0x19b5d0) — readable C lift. */
void draw_string_set_indents(int16_t width, int16_t height)
{
  extern char DAT_002b4278[];
  extern char DAT_002b4210[];
  extern char DAT_002b4264[];
  if (width < 0) {
    display_assert(DAT_002b4278, DAT_002b4210, 0x16e, 1);
    system_exit(-1);
  }
  if (height < 0) {
    display_assert(DAT_002b4264, DAT_002b4210, 0x16f, 1);
    system_exit(-1);
  }
  *(int16_t *)0x4d9b50 = height;
  *(int16_t *)0x4d9b4e = width;
}

/* draw_string_get_color (0x19b790) — readable C lift. */
void draw_string_get_color(float *out)
{
  if (!out) {
    display_assert((const char *)0x269fd8, (const char *)0x2b4210, 0x188, 1);
    system_exit(-1);
  }
  out[0] = *(float *)0x4d9b18;
  out[1] = *(float *)0x4d9b1c;
  out[2] = *(float *)0x4d9b20;
  out[3] = *(float *)0x4d9b24;
}



/* FUN_0019B7E0 (0x19b7e0) — readable C lift. */
void FUN_0019B7E0(int tag_index)
{
  tag_get(0x666f6e74, tag_index);
  *(int *)0x4d9b0c = tag_index;
}

/* draw_string_set_highlight (0x19b8f0) — readable C lift. */
void draw_string_set_highlight(short a, short b)
{
  *(short *)0x4d9b4a = a;
  *(short *)0x4d9b4c = b;
}

/* bitmap_draw_character (0x19b910) — readable C lift (restored pre-naked). */
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


/* FUN_0019bd30 (0x19bd30) — readable C lift (restored pre-naked). */
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


/* parse_string (0x19be30) — readable C lift (restored pre-naked). */
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
  ((void(*)(void))FUN_0019d380)();
  /* test (char)eax, (char)eax -> je 0x19c038 */
  ((void(*)(void))FUN_0019d380)();
  /* test (char)eax, (char)eax -> jne 0x19c038 */
  ((void(*)(void))FUN_0019d380)();
  /* test (char)eax, (char)eax -> jne 0x19c038 */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)esi;
}



/* FUN_0019c1b0 (0x19c1b0) — readable C lift (restored pre-naked). */
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


/* FUN_0019c3c0 (0x19c3c0) — readable C lift (restored pre-naked). */
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

