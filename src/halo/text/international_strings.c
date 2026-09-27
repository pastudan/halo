#include <stdint.h>
/* 0x19d080 — Return true if the two bytes starting at p form a valid
 * multibyte character under the current language encoding.
 *
 * The encoding selector lives at 0x4d9be0 (int16_t):
 *   1 = Shift-JIS  (lead: 0x81..0x9f or 0xe0..0xfe; trail: 0x40..0xfc, !=0x7f)
 *   2 = Big5       (lead: 0xa1..0xfe;                trail: 0xa1..0xfe)
 *   3 = GBK        (lead: 0x81..0xfe;                trail: 0x40..0x7e or
 * 0xa1..0xfe) 4 = Johab-like (lead: 0x81..0xfe;                trail:
 * 0x41..0x5a or 0x61..0x7a or 0x81..0xfe) 5 = Thai-like  (lead: 0x84..0xd3 or
 * 0xd8..0xde or 0xe0..0xf9; trail: 0x41..0x7e or 0x81..0xfe) Any other encoding
 * value returns false.
 *
 * A leading '|' byte (0x7c) followed by a byte in "ibukprlctn" is treated
 * as multibyte regardless of the encoding setting. */
bool unicode_is_multibyte(const uint8_t *p)
{
  uint8_t b0 = p[0];
  uint8_t b1 = p[1];

  if (b0 == 0)
    return 0;

  /* '|' escape-sequence prefix */
  if (b0 == 0x7c && b1 != 0 && crt_strchr("ibukprlctn", (int)b1) != (char *)0x0)
    return 1;

  switch (*(int16_t *)0x4d9be0) {
  case 1: /* Shift-JIS */
    if (!((b0 >= 0x81 && b0 <= 0x9f) || (b0 >= 0xe0 && b0 <= 0xfe)))
      return 0;
    if (b1 < 0x40 || b1 > 0xfc || b1 == 0x7f)
      return 0;
    return 1;
  case 2: /* Big5 */
    if (b0 < 0xa1 || b0 > 0xfe)
      return 0;
    if (b1 < 0xa1 || b1 > 0xfe)
      return 0;
    return 1;
  case 3: /* GBK */
    if (b0 < 0x81 || b0 > 0xfe)
      return 0;
    if ((b1 >= 0x40 && b1 <= 0x7e) || (b1 >= 0xa1 && b1 <= 0xfe))
      return 1;
    return 0;
  case 4: /* Johab-like */
    if (b0 < 0x81 || b0 > 0xfe)
      return 0;
    if ((b1 >= 0x41 && b1 <= 0x5a) || (b1 >= 0x61 && b1 <= 0x7a) ||
        (b1 >= 0x81 && b1 <= 0xfe))
      return 1;
    return 0;
  case 5: /* Thai-like */
    if (!((b0 >= 0x84 && b0 <= 0xd3) || (b0 >= 0xd8 && b0 <= 0xde) ||
          (b0 >= 0xe0 && b0 <= 0xf9)))
      return 0;
    if ((b1 >= 0x41 && b1 <= 0x7e) || (b1 >= 0x81 && b1 <= 0xfe))
      return 1;
    return 0;
  default:
    return 0;
  }
}

/* 0x19d1b0 — Read the character at *cursor and advance cursor forward.
 * If the byte is a multibyte lead byte (per unicode_is_multibyte), reads
 * two bytes big-endian and advances by 2; otherwise reads one byte and
 * advances by 1. Returns the character as uint16_t. */
uint16_t unicode_cursor_forward(const char *str, int16_t *cursor)
{
  const uint8_t *p;

  if (*cursor < 0 || (unsigned int)(int)*cursor > csstrlen(str)) {
    display_assert(csprintf((char *)0x5ab100,
                            "#%d is out of range in string @%p", (int)*cursor,
                            str),
                   "c:\\halo\\SOURCE\\text\\international_strings.c", 0x20, 1);
    system_exit(-1);
  }

  p = (const uint8_t *)(str + *cursor);
  if (unicode_is_multibyte(p)) {
    uint8_t b1 = p[0];
    uint8_t b2 = p[1];
    *cursor += 2;
    return (uint16_t)((b1 << 8) | b2);
  }

  *cursor += 1;
  return (uint16_t)p[0];
}

/* 0x19d240 — Move cursor backward by one character. Scans forward from
 * position 0 using unicode_cursor_forward, tracking the previous position.
 * Warns if *cursor falls between multibyte character bytes. Sets *cursor
 * to the start of the preceding character and returns it. */
uint16_t unicode_cursor_backward(const char *str, int16_t *cursor)
{
  int16_t pos;
  int16_t prev;
  uint16_t ch;

  if (*cursor <= 0 || (unsigned int)(int)*cursor > csstrlen(str)) {
    display_assert(csprintf((char *)0x5ab100,
                            "#%d is out of range in string @%p", (int)*cursor,
                            str),
                   "c:\\halo\\SOURCE\\text\\international_strings.c", 0x37, 1);
    system_exit(-1);
  }

  pos = 0;
  do {
    prev = pos;
    ch = unicode_cursor_forward(str, &pos);
  } while (pos < *cursor);

  if (pos != *cursor) {
    display_assert(csprintf((char *)0x5ab100,
                            "index #%d is inbetween characters in string %p",
                            (int)*cursor, str),
                   "c:\\halo\\SOURCE\\text\\international_strings.c", 0x43, 0);
  }

  *cursor = prev;
  return ch;
}

/* 0x19d300 — Snap cursor to a valid character boundary. Scans forward from
 * position 0 using unicode_cursor_forward until reaching or passing *cursor,
 * then writes the last valid position back to *cursor. */
void unicode_snap_cursor(const char *str, int16_t *cursor)
{
  int16_t pos;

  if (*cursor < 0 || (unsigned int)(int)*cursor > csstrlen(str)) {
    display_assert(csprintf((char *)0x5ab100,
                            "#%d is out of range in string @%p", (int)*cursor,
                            str),
                   "c:\\halo\\SOURCE\\text\\international_strings.c", 0x55, 1);
    system_exit(-1);
  }

  pos = 0;
  if (*cursor > 0) {
    do {
      unicode_cursor_forward(str, &pos);
    } while (pos < *cursor);
  }

  *cursor = pos;
}
/* --- international_strings.obj batch drafts (2026-07-26) --- */

/* FUN_0019c5d0 (0x19c5d0) — Capstone tip: null screen_pos → assert. */
void FUN_0019c5d0(void *callback, void *screen_pos, const void *color, void *clip_bounds, int flags, char *text)
{
  (void)callback;
  (void)color;
  (void)clip_bounds;
  (void)flags;
  (void)text;
  if (screen_pos == 0) {
    display_assert((const char *)0x26184c, (const char *)0x2b4210, 0x27f, 1);
    system_exit(-1);
  }
  /* Unreachable under tip snapshot. */
}


/* FUN_0019c960 (0x19c960) — Capstone tip: null screen_pos → assert. */
void FUN_0019c960(void *callback, void *screen_pos, const void *color, void *clip_bounds, int flags, unsigned short *text)
{
  (void)callback;
  (void)color;
  (void)clip_bounds;
  (void)flags;
  (void)text;
  if (screen_pos == 0) {
    display_assert((const char *)0x26184c, (const char *)0x2b4210, 0x347, 1);
    system_exit(-1);
  }
  /* Unreachable under tip snapshot. */
}


/* FUN_0019ccf0 (0x19ccf0) — readable C lift: measure ASCII string bounds. */
void FUN_0019ccf0(short *screen_pos, char *text, short *out_bounds, short *out_rect)
{
  void *font;
  short y;
  short measured;
  short *pos_slot;

  *(short *)0x4d9afc = 0x7fff;
  *(short *)0x4d9afe = 0x7fff;
  *(short *)0x4d9b00 = (short)0x8000;
  *(short *)0x4d9b02 = (short)0x8000;
  font = FUN_0019bcc0(*(int16_t *)0x4d9b14, *(int *)0x4d9b0c);
  *(void **)0x4d9b04 = font;
  pos_slot = screen_pos;
  /* Binary passes &arg0 as color so measured width overwrites the arg slot. */
  FUN_0019c5d0((void *)0x19b3c0, pos_slot, &pos_slot, 0, 0, text);
  measured = (short)(uintptr_t)pos_slot;
  out_rect[1] = measured;
  out_rect[3] = (short)(measured + 1);
  y = (short)((uintptr_t)pos_slot >> 16);
  font = *(void **)0x4d9b04;
  out_rect[0] = (short)(y - *(short *)((char *)font + 4));
  out_rect[2] = (short)(y + *(short *)((char *)font + 6));
  out_bounds[1] = *(short *)0x4d9afe;
  out_bounds[0] = screen_pos[0];
  out_bounds[3] = *(short *)0x4d9b02;
  out_bounds[2] = out_rect[2];
}

/* FUN_0019cdb0 (0x19cdb0) — readable C lift: measure UTF-16 string bounds. */
void FUN_0019cdb0(short *screen_pos, void *text, short *out_bounds, short *out_rect)
{
  void *font;
  short y;
  short measured;
  short *pos_slot;

  *(short *)0x4d9afc = 0x7fff;
  *(short *)0x4d9afe = 0x7fff;
  *(short *)0x4d9b00 = (short)0x8000;
  *(short *)0x4d9b02 = (short)0x8000;
  font = FUN_0019bcc0(*(int16_t *)0x4d9b14, *(int *)0x4d9b0c);
  *(void **)0x4d9b04 = font;
  pos_slot = screen_pos;
  FUN_0019c960((void *)0x19b3c0, pos_slot, &pos_slot, 0, 0, text);
  measured = (short)(uintptr_t)pos_slot;
  out_rect[1] = measured;
  out_rect[3] = (short)(measured + 1);
  y = (short)((uintptr_t)pos_slot >> 16);
  font = *(void **)0x4d9b04;
  out_rect[0] = (short)(y - *(short *)((char *)font + 4));
  out_rect[2] = (short)(y + *(short *)((char *)font + 6));
  out_bounds[1] = *(short *)0x4d9afe;
  out_bounds[0] = screen_pos[0];
  out_bounds[3] = *(short *)0x4d9b02;
  out_bounds[2] = out_rect[2];
}


/* FUN_0019ce70 (0x19ce70) — readable C lift. */
int16_t FUN_0019ce70(void *screen_pos, char *text, int *color)
{
  *(int *)0x4d9af0 = *color;
  *(int16_t *)0x4d9af4 = 0;
  *(int16_t *)0x4d9af8 = 0;
  *(int16_t *)0x4d9af6 = 0x7fff;
  FUN_0019c5d0((void *)0x19b430, screen_pos, 0, 0, 0, text);
  return *(int16_t *)0x4d9af4;
}

/* FUN_0019cec0 (0x19cec0) — readable C lift (restored pre-naked). */
void FUN_0019cec0(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;

  /* mem[0x004d9ae8] = esi */
  /* cmp eax, 0xb -> ja 0x19cfcc */
  /* test (int16_t)eax, (int16_t)eax -> jge 0x19cf2c */
  /* test (int16_t)eax, (int16_t)eax -> jge 0x19cf3e */
  FUN_001089a0((void *)(uintptr_t)ecx, 0, 0, 0, 0);
  /* test eax, eax -> je 0x19cfb3 */
  /* test (int16_t)ecx, (int16_t)ecx -> jge 0x19cf8d */
  /* test (int16_t)eax, (int16_t)eax -> jge 0x19cf9d */
  FUN_001089a0((void *)(uintptr_t)edx, 0, 0, 0, 0);
  FUN_0019c5d0((void *)0x0019b910, (void *)(uintptr_t)ebx, (void *)0, (void *)(uintptr_t)eax, 0, (char *)(uintptr_t)ecx);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
}


/* 0x19cff0 */
/* FUN_0019cff0 (0x19cff0) — readable C lift from XBE leaf. */
void *FUN_0019cff0(void *font_tag, unsigned short character)
{
  void *page;
  int count;
  void *glyph_index_elem;
  short glyph_index;

  page = tag_block_get_element((char *)font_tag + 0x30, character >> 8, 0xc);
  count = *(int *)page;
  if (count <= 0) {
    return 0;
  }
  if (count == 0x100) {
    glyph_index_elem = tag_block_get_element(page, character & 0xff, 2);
  } else {
    glyph_index_elem = 0;
  }
  glyph_index = *(short *)glyph_index_elem;
  if (glyph_index == (short)0xffff) {
    return 0;
  }
  return tag_block_get_element((char *)font_tag + 0x7c, glyph_index, 0x14);
}




/* set_language_code (0x19d060) — readable C lift. */
void set_language_code(short code)
{
  short v = code;
  if (v < 0 || v >= 6) v = 0;
  *(short *)0x4d9be0 = v;
}

/* FUN_0019d380 (0x19d380) — readable C lift. */
char FUN_0019d380(short want, const char *str)
{
  int16_t cursor = 0;
  uint16_t cur;
  for (;;) {
    cur = unicode_cursor_forward(str, &cursor);
    if (cur == 0)
      return 0;
    if ((int16_t)cur == want)
      return 1;
  }
}

/* 0x19d3c0 */
char *FUN_0019d3c0(int index, short param_2)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;

  tag_get('#rts', 0);
  /* test (int16_t)ecx, (int16_t)ecx -> jl 0x19d40e */
  /* cmp ecx, edx -> jge 0x19d40e */
  tag_block_get_element((void *)(uintptr_t)eax, 0, 20);
  /* test ecx, ecx -> jle 0x19d40e */
  return NULL;

  (void)eax;
  (void)ecx;
  (void)edx;
}

/* FUN_0019d420 (0x19d420) — readable C lift from XBE leaf. */
const wchar_t *FUN_0019d420(int tag_index, int16_t string_index)
{
  void *ustr;
  void *elem;
  int len;

  if (tag_index == -1) {
    return (const wchar_t *)0x2b4574;
  }
  ustr = tag_get(0x75737472, tag_index);
  if (string_index < 0) {
    return (const wchar_t *)0x2b4574;
  }
  if ((int)string_index >= *(int *)ustr) {
    return (const wchar_t *)0x2b4574;
  }
  elem = tag_block_get_element(ustr, string_index, 0x14);
  len = *(int *)elem;
  if (len <= 0) {
    return (const wchar_t *)0x2b4574;
  }
  /* NUL-terminate mid-string at len/2 wchar offset. */
  {
    wchar_t *s = *(wchar_t **)((char *)elem + 0xc);
    s[(unsigned)len / 2 - 1] = 0;
    return s;
  }
}




/* umemchr (0x19d480) — readable C lift. */
void *umemchr(void *buf, int value, size_t count)
{
  extern char DAT_00267900[];
  extern char DAT_002b45b4[];
  extern char DAT_002b4598[];
  if (!buf) {
    display_assert(DAT_00267900, DAT_002b45b4, 0x54, 1);
    system_exit(-1);
  }
  if (count >= 0x10000000) {
    display_assert(DAT_002b4598, DAT_002b45b4, 0x55, 1);
    system_exit(-1);
  }
  return _memchr(buf, value, count);
}
/* umemcpy (0x19d4f0) — readable C lift. */
void *umemcpy(void *dest, const void *src, size_t count)
{
  extern char DAT_002b4660[];
  extern char DAT_002b45b4[];
  extern char DAT_002b4628[];
  extern char DAT_002b45d8[];
  const char *d;
  const char *s;
  if (!dest || !src) {
    display_assert(DAT_002b4660, DAT_002b45b4, 0x60, 1);
    system_exit(-1);
  }
  if (count >= 0x10000000) {
    display_assert(DAT_002b4628, DAT_002b45b4, 0x61, 1);
    system_exit(-1);
  }
  d = (const char *)dest;
  s = (const char *)src;
  if ((s + count > d) && (d + count > s)) {
    display_assert(DAT_002b45d8, DAT_002b45b4, 0x62, 1);
    system_exit(-1);
  }
  return csmemcpy(dest, (void *)src, count);
}
/* umemcmp (0x19d590) — readable C lift. */
int umemcmp(const void *a, const void *b, size_t count)
{
  extern char DAT_002b469c[];
  extern char DAT_002b45b4[];
  extern char DAT_002b466c[];
  if (!a || !b) {
    display_assert(DAT_002b469c, DAT_002b45b4, 0x6d, 1);
    system_exit(-1);
  }
  if (count > 0x10000000) {
    display_assert(DAT_002b466c, DAT_002b45b4, 0x6e, 1);
    system_exit(-1);
  }
  return csmemcmp(a, b, (int)count);
}
/* umemmove (0x19d600) — readable C lift. */
void *umemmove(void *dest, const void *src, size_t count)
{
  extern char DAT_002b4660[];
  extern char DAT_002b45b4[];
  extern char DAT_002b46b0[];
  if (!dest || !src) {
    display_assert(DAT_002b4660, DAT_002b45b4, 0x79, 1);
    system_exit(-1);
  }
  if (count > 0x10000000) {
    display_assert(DAT_002b46b0, DAT_002b45b4, 0x7a, 1);
    system_exit(-1);
  }
  csmemmove(dest, src, (unsigned int)count);
  return dest;
}
/* umemset (0x19d670) — readable C lift. */
void *umemset(void *buf, int value, size_t count)
{
  extern char DAT_00267900[];
  extern char DAT_002b45b4[];
  extern char DAT_002b46e8[];
  if (!buf) {
    display_assert(DAT_00267900, DAT_002b45b4, 0x85, 1);
    system_exit(-1);
  }
  if (count > 0x10000000) {
    display_assert(DAT_002b46e8, DAT_002b45b4, 0x86, 1);
    system_exit(-1);
  }
  return csmemset(buf, value, count);
}
/* align_to_character (0x19d6e0) — readable C lift. */
wchar_t *align_to_character(wchar_t *dest, const wchar_t *src)
{
  extern char DAT_002b4754[];
  extern char DAT_002b45b4[];
  extern char DAT_002b4718[];
  size_t n;
  n = _wcslen(src);
  if (n >= 0x8000) {
    display_assert(DAT_002b4754, DAT_002b45b4, 0x92, 1);
    system_exit(-1);
  }
  if ((src + n >= dest) && (dest + n >= src)) {
    display_assert(DAT_002b4718, DAT_002b45b4, 0x93, 1);
    system_exit(-1);
  }
  return _wcscpy(dest, src);
}
/* ustrcat (0x19d760) — readable C lift. */
wchar_t *ustrcat(wchar_t *dest, const wchar_t *src)
{
  extern char DAT_002b4660[];
  extern char DAT_002b45b4[];
  extern char DAT_002b47b4[];
  extern char DAT_002b4790[];
  if (!dest || !src) {
    display_assert(DAT_002b4660, DAT_002b45b4, 0x9d, 1);
    system_exit(-1);
  }
  if (_wcslen(dest) >= 0x8000) {
    display_assert(DAT_002b47b4, DAT_002b45b4, 0x9e, 1);
    system_exit(-1);
  }
  if (_wcslen(src) >= 0x8000) {
    display_assert(DAT_002b4790, DAT_002b45b4, 0x9f, 1);
    system_exit(-1);
  }
  return _wcscat(dest, src);
}
