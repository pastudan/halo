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

/* FUN_0019c5d0 (0x19c5d0) — XBE naked draft (batch 242). */
#if defined(__clang__)
static void (*const b19c5d0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b19c5d0_exitfn)(int) = system_exit;
static void (*const b19c5d0_c19bd30)(void) = FUN_0019bd30;
static void (*const b19c5d0_c19be30)(void) = parse_string;
static void * (*const b19c5d0_c19cff0)(void *font_tag, unsigned short character) = FUN_0019cff0;
static void (*const b19c5d0_c108a10)(void) = FUN_00108a10;
static void (*const b19c5d0_c19c1b0)(void) = FUN_0019c1b0;

__attribute__((naked, noinline))
void FUN_0019c5d0(void *callback __attribute__((unused)), void *screen_pos __attribute__((unused)), const void *color __attribute__((unused)), void *clip_bounds __attribute__((unused)), int flags __attribute__((unused)), char *text __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x54, %%esp\n\t"
      "pushl %%ebx\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0xc(%%ebp), %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "pushl %%edi\n\t"
      "movl %%ebx, -0x14(%%ebp)\n\t"
      "movl %%ebx, -0x18(%%ebp)\n\t"
      "movl %%ebx, -0xc(%%ebp)\n\t"
      "movl %%ebx, -0x20(%%ebp)\n\t"
      "jne .LFUN_0019c5d0_1\n\t"
      "pushl $1\n\t"
      "pushl $0x27f\n\t"
      "pushl $0x2b4210\n\t"
      "pushl $0x26184c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0019c5d0_1:\n\t"
      "movl 0x1c(%%ebp), %%edi\n\t"
      "cmpl %%ebx, %%edi\n\t"
      "jne .LFUN_0019c5d0_2\n\t"
      "pushl $1\n\t"
      "pushl $0x280\n\t"
      "pushl $0x2b4210\n\t"
      "pushl $0x27b838\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0019c5d0_2:\n\t"
      "movl 0x4d9b0c, %%ecx\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x4d9b16, %%ax\n\t"
      "pushl $0x4d9b18\n\t"
      "leal -0x54(%%ebp), %%ebx\n\t"
      "pushl %%eax\n\t"
      "movl 0x4d9b14, %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edi\n\t"
      "call *%[c19bd30]\n\t"
      "addl $0x10, %%esp\n\t"
      "jmp .LFUN_0019c5d0_4\n\t"
      ".LFUN_0019c5d0_3:\n\t"
      "movl 0xc(%%ebp), %%esi\n\t"
      ".LFUN_0019c5d0_4:\n\t"
      "movl -0x48(%%ebp), %%eax\n\t"
      "movl -0x44(%%ebp), %%edx\n\t"
      "movl (%%esi), %%ecx\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "movl %%eax, -0x30(%%ebp)\n\t"
      "movw 0x4d9b28, %%ax\n\t"
      "movl %%edx, -0x2c(%%ebp)\n\t"
      "movl 0x4(%%esi), %%edx\n\t"
      "orl $0xffffffff, %%edi\n\t"
      "cmpw %%bx, %%ax\n\t"
      "movl %%ebx, -0x8(%%ebp)\n\t"
      "movl %%ebx, -0x24(%%ebp)\n\t"
      "movb %%bl, -0x1(%%ebp)\n\t"
      "movl %%ecx, -0x38(%%ebp)\n\t"
      "movl %%edx, -0x34(%%ebp)\n\t"
      "jle .LFUN_0019c5d0_10\n\t"
      "movl -0x14(%%ebp), %%esi\n\t"
      "cmpw %%bx, %%si\n\t"
      "jl .LFUN_0019c5d0_5\n\t"
      "cmpw %%ax, %%si\n\t"
      "jle .LFUN_0019c5d0_6\n\t"
      ".LFUN_0019c5d0_5:\n\t"
      "pushl $1\n\t"
      "pushl $0x2a0\n\t"
      "pushl $0x2b4210\n\t"
      "pushl $0x2b4488\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0019c5d0_6:\n\t"
      "cmpw %%bx, %%si\n\t"
      "je .LFUN_0019c5d0_7\n\t"
      "movswl %%si, %%eax\n\t"
      "movw 0x4d9b28(,%%eax,2), %%ax\n\t"
      "jmp .LFUN_0019c5d0_9\n\t"
      ".LFUN_0019c5d0_7:\n\t"
      "cmpw %%bx, -0x18(%%ebp)\n\t"
      "movw -0x36(%%ebp), %%ax\n\t"
      "je .LFUN_0019c5d0_8\n\t"
      "addw 0x4d9b50, %%ax\n\t"
      "jmp .LFUN_0019c5d0_9\n\t"
      ".LFUN_0019c5d0_8:\n\t"
      "addw 0x4d9b4e, %%ax\n\t"
      ".LFUN_0019c5d0_9:\n\t"
      "cmpw 0x4d9b28, %%si\n\t"
      "movw %%ax, -0x36(%%ebp)\n\t"
      "jge .LFUN_0019c5d0_13\n\t"
      "movswl %%si, %%ecx\n\t"
      "movw 0x4d9b2a(,%%ecx,2), %%dx\n\t"
      "movw %%dx, -0x32(%%ebp)\n\t"
      "jmp .LFUN_0019c5d0_13\n\t"
      ".LFUN_0019c5d0_10:\n\t"
      "cmpw %%bx, -0x18(%%ebp)\n\t"
      "movw -0x36(%%ebp), %%ax\n\t"
      "je .LFUN_0019c5d0_11\n\t"
      "addw 0x4d9b50, %%ax\n\t"
      "jmp .LFUN_0019c5d0_12\n\t"
      ".LFUN_0019c5d0_11:\n\t"
      "addw 0x4d9b4e, %%ax\n\t"
      ".LFUN_0019c5d0_12:\n\t"
      "movw %%ax, -0x36(%%ebp)\n\t"
      ".LFUN_0019c5d0_13:\n\t"
      "movl -0x50(%%ebp), %%edx\n\t"
      "movw 0xa(%%edx), %%cx\n\t"
      "xorl %%esi, %%esi\n\t"
      "movw 0x8(%%edx), %%si\n\t"
      "addw 0x6(%%edx), %%si\n\t"
      "addw %%ax, %%cx\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x4(%%edx), %%ax\n\t"
      "movl 0x18(%%ebp), %%edx\n\t"
      "movw %%cx, -0x10(%%ebp)\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "addl %%eax, %%esi\n\t"
      "addl %%edx, %%esi\n\t"
      "movl -0x18(%%ebp), %%edx\n\t"
      "addl %%edx, %%ecx\n\t"
      "imull %%ecx, %%esi\n\t"
      "addl %%eax, %%esi\n\t"
      "addl -0x38(%%ebp), %%esi\n\t"
      "movw %%si, -0xe(%%ebp)\n\t"
      "movl %%edi, %%edi\n\t"
      ".LFUN_0019c5d0_14:\n\t"
      "leal -0x54(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "xorb %%bl, %%bl\n\t"
      "call *%[c19be30]\n\t"
      "movw -0x40(%%ebp), %%ax\n\t"
      "addl $4, %%esp\n\t"
      "cmpw $2, %%ax\n\t"
      "je .LFUN_0019c5d0_15\n\t"
      "cmpw $6, %%ax\n\t"
      "je .LFUN_0019c5d0_15\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "jmp .LFUN_0019c5d0_19\n\t"
      ".LFUN_0019c5d0_15:\n\t"
      "movl -0x42(%%ebp), %%ecx\n\t"
      "movl -0x50(%%ebp), %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c19cff0]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_0019c5d0_19\n\t"
      "cmpw $2, -0x40(%%ebp)\n\t"
      "je .LFUN_0019c5d0_16\n\t"
      "cmpw $2, %%di\n\t"
      "jne .LFUN_0019c5d0_16\n\t"
      "movl -0x1c(%%ebp), %%ecx\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "movl %%ecx, -0x24(%%ebp)\n\t"
      "movl %%edx, -0x28(%%ebp)\n\t"
      ".LFUN_0019c5d0_16:\n\t"
      "movswl -0x10(%%ebp), %%ecx\n\t"
      "movswl 0x4(%%eax), %%edx\n\t"
      "addl %%ecx, %%edx\n\t"
      "movw -0x8(%%ebp), %%cx\n\t"
      "movswl %%cx, %%edi\n\t"
      "addl %%edi, %%edx\n\t"
      "movswl -0x32(%%ebp), %%edi\n\t"
      "cmpl %%edi, %%edx\n\t"
      "jge .LFUN_0019c5d0_17\n\t"
      "addw 0x2(%%eax), %%cx\n\t"
      "movw %%cx, -0x8(%%ebp)\n\t"
      "jmp .LFUN_0019c5d0_19\n\t"
      ".LFUN_0019c5d0_17:\n\t"
      "testb $1, 0x4d9b10\n\t"
      "je .LFUN_0019c5d0_19\n\t"
      "movl -0x24(%%ebp), %%eax\n\t"
      "testw %%ax, %%ax\n\t"
      "jle .LFUN_0019c5d0_18\n\t"
      "movl -0x28(%%ebp), %%edx\n\t"
      "movl %%eax, -0x1c(%%ebp)\n\t"
      "movl %%edx, -0x8(%%ebp)\n\t"
      "movb $1, %%bl\n\t"
      ".LFUN_0019c5d0_18:\n\t"
      "testb %%bl, %%bl\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "jne .LFUN_0019c5d0_20\n\t"
      ".LFUN_0019c5d0_19:\n\t"
      "movl -0x48(%%ebp), %%eax\n\t"
      "movl %%eax, -0x1c(%%ebp)\n\t"
      ".LFUN_0019c5d0_20:\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "movl -0x40(%%ebp), %%edi\n\t"
      "je .LFUN_0019c5d0_14\n\t"
      "movswl -0x2c(%%ebp), %%eax\n\t"
      "decl %%eax\n\t"
      "je .LFUN_0019c5d0_21\n\t"
      "decl %%eax\n\t"
      "jne .LFUN_0019c5d0_22\n\t"
      "leal -0x38(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c108a10]\n\t"
      "movswl %%ax, %%edx\n\t"
      "movswl -0x8(%%ebp), %%eax\n\t"
      "subl %%eax, %%edx\n\t"
      "movl -0x36(%%ebp), %%eax\n\t"
      "sarl $1, %%edx\n\t"
      "addl $4, %%esp\n\t"
      "addl %%eax, %%edx\n\t"
      "movw %%dx, -0x10(%%ebp)\n\t"
      "jmp .LFUN_0019c5d0_22\n\t"
      ".LFUN_0019c5d0_21:\n\t"
      "leal -0x38(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c108a10]\n\t"
      "movl -0x50(%%ebp), %%ecx\n\t"
      "movl -0x8(%%ebp), %%edi\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw -0x36(%%ebp), %%dx\n\t"
      "subw 0xa(%%ecx), %%dx\n\t"
      "addl $4, %%esp\n\t"
      "subl %%edi, %%edx\n\t"
      "addl %%edx, %%eax\n\t"
      "movw %%ax, -0x10(%%ebp)\n\t"
      ".LFUN_0019c5d0_22:\n\t"
      "testb $2, 0x4d9b10\n\t"
      "jne .LFUN_0019c5d0_23\n\t"
      "cmpw -0x34(%%ebp), %%si\n\t"
      "jge .LFUN_0019c5d0_24\n\t"
      ".LFUN_0019c5d0_23:\n\t"
      "movl -0x1c(%%ebp), %%edx\n\t"
      "movl -0x30(%%ebp), %%eax\n\t"
      "movl 0x1c(%%ebp), %%ecx\n\t"
      "pushl %%edx\n\t"
      "movl -0x3c(%%ebp), %%edx\n\t"
      "pushl %%eax\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "pushl %%eax\n\t"
      "leal -0x10(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "leal -0x38(%%ebp), %%eax\n\t"
      "call *%[c19c1b0]\n\t"
      "addl $0x1c, %%esp\n\t"
      ".LFUN_0019c5d0_24:\n\t"
      "movw -0x1c(%%ebp), %%ax\n\t"
      "movw %%ax, -0x48(%%ebp)\n\t"
      "movswl -0x40(%%ebp), %%eax\n\t"
      "cmpl $6, %%eax\n\t"
      "ja .LFUN_0019c5d0_29\n\t"
      "jmp *.LFUN_0019c5d0_jt(,%%eax,4)\n\t"
      ".LFUN_0019c5d0_25:\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "incl %%eax\n\t"
      "cmpw -0x20(%%ebp), %%ax\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "jle .LFUN_0019c5d0_30\n\t"
      "movl %%eax, -0x20(%%ebp)\n\t"
      "jmp .LFUN_0019c5d0_30\n\t"
      ".LFUN_0019c5d0_26:\n\t"
      "movw -0x14(%%ebp), %%cx\n\t"
      "cmpw 0x4d9b28, %%cx\n\t"
      "jge .LFUN_0019c5d0_30\n\t"
      "incl -0x14(%%ebp)\n\t"
      ".LFUN_0019c5d0_27:\n\t"
      "movl $0, -0xc(%%ebp)\n\t"
      "jmp .LFUN_0019c5d0_30\n\t"
      ".LFUN_0019c5d0_28:\n\t"
      "movl -0x18(%%ebp), %%edx\n\t"
      "xorl %%eax, %%eax\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "movl -0x20(%%ebp), %%eax\n\t"
      "leal 0x1(%%edx,%%eax,1), %%ecx\n\t"
      "movl %%ecx, -0x18(%%ebp)\n\t"
      "jmp .LFUN_0019c5d0_30\n\t"
      ".LFUN_0019c5d0_29:\n\t"
      "pushl $1\n\t"
      "pushl $0x328\n\t"
      "pushl $0x2b4210\n\t"
      "pushl $0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0019c5d0_30:\n\t"
      "cmpw $0, -0x40(%%ebp)\n\t"
      "jne .LFUN_0019c5d0_3\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movw %%cx, 0x4d9b4c\n\t"
      "movw %%cx, 0x4d9b4a\n\t"
      "popl %%ebx\n\t"
      "je .LFUN_0019c5d0_31\n\t"
      "movl -0x10(%%ebp), %%edx\n\t"
      "movl %%edx, (%%eax)\n\t"
      ".LFUN_0019c5d0_31:\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_0019c5d0_jt:\n\t"
      ".long .LFUN_0019c5d0_30\n\t"
      ".long .LFUN_0019c5d0_28\n\t"
      ".long .LFUN_0019c5d0_25\n\t"
      ".long .LFUN_0019c5d0_26\n\t"
      ".long .LFUN_0019c5d0_27\n\t"
      ".long .LFUN_0019c5d0_30\n\t"
      ".long .LFUN_0019c5d0_25\n\t"
      ".text\n\t"
      :
      : [assert] "m"(b19c5d0_assert), [exitfn] "m"(b19c5d0_exitfn), [c19bd30] "m"(b19c5d0_c19bd30), [c19be30] "m"(b19c5d0_c19be30), [c19cff0] "m"(b19c5d0_c19cff0), [c108a10] "m"(b19c5d0_c108a10), [c19c1b0] "m"(b19c5d0_c19c1b0)
      : "memory");
}
#else
#error "FUN_0019c5d0: clang naked draft required"
#endif


/* FUN_0019c960 (0x19c960) — XBE naked draft (batch 242). */
#if defined(__clang__)
static void (*const b19c960_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b19c960_exitfn)(int) = system_exit;
static void (*const b19c960_c19bd30)(void) = FUN_0019bd30;
static int16_t (*const b19c960_c19c0a0)(void *state) = FUN_0019c0a0;
static void * (*const b19c960_c19cff0)(void *font_tag, unsigned short character) = FUN_0019cff0;
static void (*const b19c960_c108a10)(void) = FUN_00108a10;
static void (*const b19c960_c19c3c0)(void) = FUN_0019c3c0;

__attribute__((naked, noinline))
void FUN_0019c960(void *callback __attribute__((unused)), void *screen_pos __attribute__((unused)), const void *color __attribute__((unused)), void *clip_bounds __attribute__((unused)), int flags __attribute__((unused)), unsigned short *text __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x58, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0xc(%%ebp), %%esi\n\t"
      "pushl %%edi\n\t"
      "xorl %%edi, %%edi\n\t"
      "cmpl %%edi, %%esi\n\t"
      "movl %%edi, -0x14(%%ebp)\n\t"
      "movl %%edi, -0x18(%%ebp)\n\t"
      "movl %%edi, -0xc(%%ebp)\n\t"
      "movl %%edi, -0x20(%%ebp)\n\t"
      "jne .LFUN_0019c960_1\n\t"
      "pushl $1\n\t"
      "pushl $0x347\n\t"
      "pushl $0x2b4210\n\t"
      "pushl $0x26184c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0019c960_1:\n\t"
      "movl 0x1c(%%ebp), %%ebx\n\t"
      "cmpl %%edi, %%ebx\n\t"
      "jne .LFUN_0019c960_2\n\t"
      "pushl $1\n\t"
      "pushl $0x348\n\t"
      "pushl $0x2b4210\n\t"
      "pushl $0x27b838\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0019c960_2:\n\t"
      "movl 0x4d9b0c, %%ecx\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x4d9b16, %%ax\n\t"
      "pushl $0x4d9b18\n\t"
      "pushl %%eax\n\t"
      "movl 0x4d9b14, %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "leal -0x58(%%ebp), %%ebx\n\t"
      "call *%[c19bd30]\n\t"
      "addl $0x10, %%esp\n\t"
      "jmp .LFUN_0019c960_4\n\t"
      ".LFUN_0019c960_3:\n\t"
      "movl 0xc(%%ebp), %%esi\n\t"
      "movl -0x14(%%ebp), %%edi\n\t"
      ".LFUN_0019c960_4:\n\t"
      "movl -0x4c(%%ebp), %%eax\n\t"
      "movl -0x48(%%ebp), %%edx\n\t"
      "movl (%%esi), %%ecx\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "movl %%eax, -0x34(%%ebp)\n\t"
      "movw 0x4d9b28, %%ax\n\t"
      "cmpw %%bx, %%ax\n\t"
      "movl %%edx, -0x30(%%ebp)\n\t"
      "movl 0x4(%%esi), %%edx\n\t"
      "movl %%ebx, -0x8(%%ebp)\n\t"
      "movl %%ebx, -0x24(%%ebp)\n\t"
      "movl $0xffffffff, -0x28(%%ebp)\n\t"
      "movb %%bl, -0x1(%%ebp)\n\t"
      "movl %%ecx, -0x3c(%%ebp)\n\t"
      "movl %%edx, -0x38(%%ebp)\n\t"
      "jle .LFUN_0019c960_10\n\t"
      "cmpw %%bx, %%di\n\t"
      "jl .LFUN_0019c960_5\n\t"
      "cmpw %%ax, %%di\n\t"
      "jle .LFUN_0019c960_6\n\t"
      ".LFUN_0019c960_5:\n\t"
      "pushl $1\n\t"
      "pushl $0x368\n\t"
      "pushl $0x2b4210\n\t"
      "pushl $0x2b4488\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "movw 0x4d9b28, %%ax\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0019c960_6:\n\t"
      "cmpw %%bx, %%di\n\t"
      "je .LFUN_0019c960_7\n\t"
      "movswl %%di, %%ecx\n\t"
      "movw 0x4d9b28(,%%ecx,2), %%dx\n\t"
      "movw %%dx, -0x3a(%%ebp)\n\t"
      "jmp .LFUN_0019c960_9\n\t"
      ".LFUN_0019c960_7:\n\t"
      "cmpw %%bx, -0x18(%%ebp)\n\t"
      "je .LFUN_0019c960_8\n\t"
      "movw 0x4d9b50, %%cx\n\t"
      "addw %%cx, -0x3a(%%ebp)\n\t"
      "jmp .LFUN_0019c960_9\n\t"
      ".LFUN_0019c960_8:\n\t"
      "movw 0x4d9b4e, %%dx\n\t"
      "addw %%dx, -0x3a(%%ebp)\n\t"
      ".LFUN_0019c960_9:\n\t"
      "cmpw %%ax, %%di\n\t"
      "jge .LFUN_0019c960_12\n\t"
      "movswl %%di, %%eax\n\t"
      "movw 0x4d9b2a(,%%eax,2), %%cx\n\t"
      "movw %%cx, -0x36(%%ebp)\n\t"
      "jmp .LFUN_0019c960_12\n\t"
      ".LFUN_0019c960_10:\n\t"
      "cmpw %%bx, -0x18(%%ebp)\n\t"
      "je .LFUN_0019c960_11\n\t"
      "movw 0x4d9b50, %%dx\n\t"
      "addw %%dx, -0x3a(%%ebp)\n\t"
      "jmp .LFUN_0019c960_12\n\t"
      ".LFUN_0019c960_11:\n\t"
      "movw 0x4d9b4e, %%ax\n\t"
      "addw %%ax, -0x3a(%%ebp)\n\t"
      ".LFUN_0019c960_12:\n\t"
      "movl -0x54(%%ebp), %%ecx\n\t"
      "movw 0xa(%%ecx), %%ax\n\t"
      "addw -0x3a(%%ebp), %%ax\n\t"
      "movl 0x18(%%ebp), %%edx\n\t"
      "xorl %%esi, %%esi\n\t"
      "movw 0x8(%%ecx), %%si\n\t"
      "addw 0x6(%%ecx), %%si\n\t"
      "movw %%ax, -0x10(%%ebp)\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x4(%%ecx), %%ax\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "movw -0x8(%%ebp), %%di\n\t"
      "addl %%eax, %%esi\n\t"
      "addl %%edx, %%esi\n\t"
      "movl -0x18(%%ebp), %%edx\n\t"
      "addl %%edx, %%ecx\n\t"
      "imull %%ecx, %%esi\n\t"
      "addl %%eax, %%esi\n\t"
      "addl -0x3c(%%ebp), %%esi\n\t"
      "movw %%si, -0xe(%%ebp)\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_0019c960_13:\n\t"
      "leal -0x58(%%ebp), %%eax\n\t"
      "xorb %%bl, %%bl\n\t"
      "call *%[c19c0a0]\n\t"
      "movw -0x44(%%ebp), %%ax\n\t"
      "cmpw $2, %%ax\n\t"
      "je .LFUN_0019c960_14\n\t"
      "cmpw $6, %%ax\n\t"
      "je .LFUN_0019c960_14\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "jmp .LFUN_0019c960_18\n\t"
      ".LFUN_0019c960_14:\n\t"
      "movl -0x46(%%ebp), %%eax\n\t"
      "movl -0x54(%%ebp), %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c19cff0]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_0019c960_18\n\t"
      "movl $2, %%ecx\n\t"
      "cmpw %%cx, -0x44(%%ebp)\n\t"
      "je .LFUN_0019c960_15\n\t"
      "cmpw %%cx, -0x28(%%ebp)\n\t"
      "jne .LFUN_0019c960_15\n\t"
      "movl -0x1c(%%ebp), %%edx\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movl %%edx, -0x24(%%ebp)\n\t"
      "movl %%ecx, -0x2c(%%ebp)\n\t"
      ".LFUN_0019c960_15:\n\t"
      "movswl -0x10(%%ebp), %%ecx\n\t"
      "movswl 0x4(%%eax), %%edx\n\t"
      "addl %%ecx, %%edx\n\t"
      "movswl %%di, %%ecx\n\t"
      "addl %%ecx, %%edx\n\t"
      "movswl -0x36(%%ebp), %%ecx\n\t"
      "cmpl %%ecx, %%edx\n\t"
      "jge .LFUN_0019c960_16\n\t"
      "addw 0x2(%%eax), %%di\n\t"
      "movw %%di, -0x8(%%ebp)\n\t"
      "jmp .LFUN_0019c960_18\n\t"
      ".LFUN_0019c960_16:\n\t"
      "testb $1, 0x4d9b10\n\t"
      "je .LFUN_0019c960_18\n\t"
      "movl -0x24(%%ebp), %%eax\n\t"
      "testw %%ax, %%ax\n\t"
      "jle .LFUN_0019c960_17\n\t"
      "movl -0x2c(%%ebp), %%edx\n\t"
      "movl %%eax, -0x1c(%%ebp)\n\t"
      "movl %%edx, -0x8(%%ebp)\n\t"
      "movb $1, %%bl\n\t"
      "movw %%dx, %%di\n\t"
      ".LFUN_0019c960_17:\n\t"
      "testb %%bl, %%bl\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "jne .LFUN_0019c960_19\n\t"
      ".LFUN_0019c960_18:\n\t"
      "movl -0x4c(%%ebp), %%eax\n\t"
      "movl %%eax, -0x1c(%%ebp)\n\t"
      ".LFUN_0019c960_19:\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "movl -0x44(%%ebp), %%ecx\n\t"
      "movl %%ecx, -0x28(%%ebp)\n\t"
      "je .LFUN_0019c960_13\n\t"
      "movswl -0x30(%%ebp), %%eax\n\t"
      "decl %%eax\n\t"
      "je .LFUN_0019c960_20\n\t"
      "decl %%eax\n\t"
      "jne .LFUN_0019c960_22\n\t"
      "leal -0x3c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c108a10]\n\t"
      "movswl %%ax, %%eax\n\t"
      "movswl %%di, %%ecx\n\t"
      "subl %%ecx, %%eax\n\t"
      "movl -0x3a(%%ebp), %%ecx\n\t"
      "sarl $1, %%eax\n\t"
      "jmp .LFUN_0019c960_21\n\t"
      ".LFUN_0019c960_20:\n\t"
      "leal -0x3c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c108a10]\n\t"
      "movl -0x54(%%ebp), %%edx\n\t"
      "movl -0x8(%%ebp), %%edi\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw -0x3a(%%ebp), %%cx\n\t"
      "subw 0xa(%%edx), %%cx\n\t"
      "subl %%edi, %%ecx\n\t"
      ".LFUN_0019c960_21:\n\t"
      "addl $4, %%esp\n\t"
      "addl %%ecx, %%eax\n\t"
      "movw %%ax, -0x10(%%ebp)\n\t"
      ".LFUN_0019c960_22:\n\t"
      "testb $2, 0x4d9b10\n\t"
      "jne .LFUN_0019c960_23\n\t"
      "cmpw -0x38(%%ebp), %%si\n\t"
      "jge .LFUN_0019c960_24\n\t"
      ".LFUN_0019c960_23:\n\t"
      "movl -0x1c(%%ebp), %%eax\n\t"
      "movl -0x34(%%ebp), %%ecx\n\t"
      "movl 0x1c(%%ebp), %%edx\n\t"
      "pushl %%eax\n\t"
      "movl -0x40(%%ebp), %%eax\n\t"
      "pushl %%ecx\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%ecx\n\t"
      "leal -0x10(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "leal -0x3c(%%ebp), %%eax\n\t"
      "call *%[c19c3c0]\n\t"
      "addl $0x1c, %%esp\n\t"
      ".LFUN_0019c960_24:\n\t"
      "movswl -0x44(%%ebp), %%eax\n\t"
      "cmpl $6, %%eax\n\t"
      "movw -0x1c(%%ebp), %%cx\n\t"
      "movw %%cx, -0x4c(%%ebp)\n\t"
      "ja .LFUN_0019c960_29\n\t"
      "jmp *.LFUN_0019c960_jt(,%%eax,4)\n\t"
      ".LFUN_0019c960_25:\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "incl %%eax\n\t"
      "cmpw -0x20(%%ebp), %%ax\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "jle .LFUN_0019c960_30\n\t"
      "movl %%eax, -0x20(%%ebp)\n\t"
      "jmp .LFUN_0019c960_30\n\t"
      ".LFUN_0019c960_26:\n\t"
      "movw -0x14(%%ebp), %%dx\n\t"
      "cmpw 0x4d9b28, %%dx\n\t"
      "jge .LFUN_0019c960_30\n\t"
      "incl -0x14(%%ebp)\n\t"
      ".LFUN_0019c960_27:\n\t"
      "movl $0, -0xc(%%ebp)\n\t"
      "jmp .LFUN_0019c960_30\n\t"
      ".LFUN_0019c960_28:\n\t"
      "movl -0x20(%%ebp), %%ecx\n\t"
      "xorl %%eax, %%eax\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "movl -0x18(%%ebp), %%eax\n\t"
      "leal 0x1(%%eax,%%ecx,1), %%edx\n\t"
      "movl %%edx, -0x18(%%ebp)\n\t"
      "jmp .LFUN_0019c960_30\n\t"
      ".LFUN_0019c960_29:\n\t"
      "pushl $1\n\t"
      "pushl $0x3f0\n\t"
      "pushl $0x2b4210\n\t"
      "pushl $0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0019c960_30:\n\t"
      "cmpw $0, -0x44(%%ebp)\n\t"
      "jne .LFUN_0019c960_3\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movw %%cx, 0x4d9b4c\n\t"
      "movw %%cx, 0x4d9b4a\n\t"
      "popl %%ebx\n\t"
      "je .LFUN_0019c960_31\n\t"
      "movl -0x10(%%ebp), %%ecx\n\t"
      "movl %%ecx, (%%eax)\n\t"
      ".LFUN_0019c960_31:\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_0019c960_jt:\n\t"
      ".long .LFUN_0019c960_30\n\t"
      ".long .LFUN_0019c960_28\n\t"
      ".long .LFUN_0019c960_25\n\t"
      ".long .LFUN_0019c960_26\n\t"
      ".long .LFUN_0019c960_27\n\t"
      ".long .LFUN_0019c960_30\n\t"
      ".long .LFUN_0019c960_25\n\t"
      ".text\n\t"
      :
      : [assert] "m"(b19c960_assert), [exitfn] "m"(b19c960_exitfn), [c19bd30] "m"(b19c960_c19bd30), [c19c0a0] "m"(b19c960_c19c0a0), [c19cff0] "m"(b19c960_c19cff0), [c108a10] "m"(b19c960_c108a10), [c19c3c0] "m"(b19c960_c19c3c0)
      : "memory");
}
#else
#error "FUN_0019c960: clang naked draft required"
#endif


/* 0x19ccf0 */
void FUN_0019ccf0(void)
{
  int eax = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;

  FUN_0019bcc0(edi, 0);
  /* mem[0x004d9b04] = eax */
  FUN_0019c5d0((void *)0x0019b3c0, (void *)(uintptr_t)esi, (void *)(uintptr_t)ecx, (void *)0, 0, (char *)(uintptr_t)eax);

  (void)eax;
  (void)ecx;
  (void)esi;
  (void)edi;
}

/* 0x19cdb0 */
void FUN_0019cdb0(short *out_rect, void *text, short *out_bounds, short *in_rect)
{
  int eax = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;

  FUN_0019bcc0(edi, 0);
  /* mem[0x004d9b04] = eax */
  FUN_0019c960((void *)0x0019b3c0, (void *)(uintptr_t)esi, (void *)(uintptr_t)ecx, (void *)0, 0, (void *)(uintptr_t)eax);

  (void)eax;
  (void)ecx;
  (void)esi;
  (void)edi;
}

/* 0x19ce70 */
void FUN_0019ce70(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;

  /* mem[0x004d9af0] = ecx */
  FUN_0019c5d0((void *)0x0019b430, (void *)(uintptr_t)eax, (void *)(uintptr_t)eax, (void *)(uintptr_t)eax, 0, (char *)(uintptr_t)edx);

  (void)eax;
  (void)ecx;
  (void)edx;
}

/* 0x19cec0 */
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
/* FUN_0019cff0 (0x19cff0) — XBE naked draft (batch 235). */
#if defined(__clang__)
static void *(*const b19cff0_elem)(void *, int, int) = tag_block_get_element;

__attribute__((naked, noinline))
void * FUN_0019cff0(void *font_tag __attribute__((unused)), unsigned short character __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movzwl 0xc(%%ebp), %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "movl %%esi, %%eax\n\t"
      "pushl $0xc\n\t"
      "shrl $8, %%eax\n\t"
      "pushl %%eax\n\t"
      "leal 0x30(%%edi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[elem]\n\t"
      "movl (%%eax), %%ecx\n\t"
      "addl $0xc, %%esp\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "jle .LFUN_0019cff0_3\n\t"
      "cmpl $0x100, %%ecx\n\t"
      "jne .LFUN_0019cff0_1\n\t"
      "pushl $2\n\t"
      "andl $0xff, %%esi\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "addl $0xc, %%esp\n\t"
      "jmp .LFUN_0019cff0_2\n\t"
      ".LFUN_0019cff0_1:\n\t"
      "xorl %%eax, %%eax\n\t"
      ".LFUN_0019cff0_2:\n\t"
      "movw (%%eax), %%ax\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .LFUN_0019cff0_3\n\t"
      "movswl %%ax, %%edx\n\t"
      "pushl $0x14\n\t"
      "pushl %%edx\n\t"
      "addl $0x7c, %%edi\n\t"
      "pushl %%edi\n\t"
      "call *%[elem]\n\t"
      "addl $0xc, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0019cff0_3:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebx, %%eax\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [elem] "m"(b19cff0_elem)
      : "memory");
}
#else
#error "FUN_0019cff0: clang naked draft required"
#endif


/* 0x19d060 */
void set_language_code(short code)
{
  /* relift: no calls detected — manual review */
}

/* 0x19d380 */
void FUN_0019d380(void)
{
  int eax = 0;
  int esi = 0;
  int edi = 0;

  unicode_cursor_forward((char *)(uintptr_t)esi, (void *)(uintptr_t)eax);
  /* test (int16_t)eax, (int16_t)eax -> je 0x19d3b3 */
  /* cmp (int16_t)eax, (int16_t)edi -> jne 0x19d393 */

  (void)eax;
  (void)esi;
  (void)edi;
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

/* 0x19d420 */
int FUN_0019d420(int param_1, int param_2)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;

  tag_get('rtsu', 0);
  /* test (int16_t)ecx, (int16_t)ecx -> jl 0x19d472 */
  /* cmp ecx, edx -> jge 0x19d472 */
  tag_block_get_element((void *)(uintptr_t)eax, 0, 20);
  /* test ecx, ecx -> jle 0x19d472 */
  return 0;

  (void)eax;
  (void)ecx;
  (void)edx;
}

/* 0x19d480 */
void umemchr(void)
{
  int edi = 0;

  display_assert((char *)0x00267900, (char *)0x002b45b4, 84, 0);
  system_exit(0);
  /* cmp edi, 0x10000000 -> jb 0x19d4d1 */
  display_assert((char *)0x002b4598, (char *)0x002b45b4, 85, 0);
  system_exit(0);
  _memchr();

  (void)edi;
}

/* 0x19d4f0 */
void umemcpy(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;

  /* test ebx, ebx -> jne 0x19d521 */
  display_assert((char *)0x002b4660, (char *)0x002b45b4, 96, 0);
  system_exit(0);
  /* cmp edi, 0x10000000 -> jb 0x19d549 */
  display_assert((char *)0x002b4628, (char *)0x002b45b4, 97, 0);
  system_exit(0);
  /* cmp eax, esi -> jbe 0x19d574 */
  /* cmp ecx, ebx -> jbe 0x19d574 */
  display_assert((char *)0x002b45d8, (char *)0x002b45b4, 98, 0);
  system_exit(0);
  csmemcpy((void *)(uintptr_t)esi, (void *)(uintptr_t)ebx, edi);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)esi;
  (void)edi;
}

/* 0x19d590 */
void umemcmp(void)
{
  int ebx = 0;
  int esi = 0;
  int edi = 0;

  /* test ebx, ebx -> jne 0x19d5c1 */
  display_assert((char *)0x002b469c, (char *)0x002b45b4, 109, 0);
  system_exit(0);
  /* cmp edi, 0x10000000 -> jbe 0x19d5e9 */
  display_assert((char *)0x002b466c, (char *)0x002b45b4, 110, 0);
  system_exit(0);
  csmemcmp((void *)(uintptr_t)esi, (void *)(uintptr_t)ebx, 0);

  (void)ebx;
  (void)esi;
  (void)edi;
}

/* 0x19d600 */
void umemmove(void)
{
  int ebx = 0;
  int esi = 0;
  int edi = 0;

  /* test ebx, ebx -> jne 0x19d631 */
  display_assert((char *)0x002b4660, (char *)0x002b45b4, 121, 0);
  system_exit(0);
  /* cmp edi, 0x10000000 -> jbe 0x19d659 */
  display_assert((char *)0x002b46b0, (char *)0x002b45b4, 122, 0);
  system_exit(0);
  csmemmove((void *)(uintptr_t)esi, (void *)(uintptr_t)ebx, edi);

  (void)ebx;
  (void)esi;
  (void)edi;
}

/* 0x19d670 */
void umemset(void)
{
  int esi = 0;
  int edi = 0;

  display_assert((char *)0x00267900, (char *)0x002b45b4, 133, 0);
  system_exit(0);
  /* cmp edi, 0x10000000 -> jbe 0x19d6c7 */
  display_assert((char *)0x002b46e8, (char *)0x002b45b4, 134, 0);
  system_exit(0);
  csmemset((void *)(uintptr_t)esi, 0, edi);

  (void)esi;
  (void)edi;
}

/* 0x19d6e0 */
void align_to_character(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;

  _wcslen((wchar_t *)(uintptr_t)edi);
  /* cmp esi, 0x8000 -> jb 0x19d71c */
  display_assert((char *)0x002b4754, (char *)0x002b45b4, 146, 0);
  system_exit(0);
  /* cmp eax, ebx -> jb 0x19d74d */
  /* cmp ecx, edi -> jb 0x19d74d */
  display_assert((char *)0x002b4718, (char *)0x002b45b4, 147, 0);
  system_exit(0);
  _wcscpy();

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)esi;
  (void)edi;
}

/* 0x19d760 */
void ustrcat(void)
{
  int eax = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;

  /* test edi, edi -> jne 0x19d793 */
  display_assert((char *)0x002b4660, (char *)0x002b45b4, 157, 0);
  system_exit(0);
  _wcslen((wchar_t *)(uintptr_t)esi);
  /* cmp eax, 0x8000 -> jb 0x19d7c3 */
  display_assert((char *)0x002b47b4, (char *)0x002b45b4, 158, 0);
  system_exit(0);
  _wcslen((wchar_t *)(uintptr_t)edi);
  /* cmp eax, 0x8000 -> jb 0x19d7f3 */
  display_assert((char *)0x002b4790, (char *)0x002b45b4, 159, 0);
  system_exit(0);
  _wcscat();
  /* test edi, edi -> jne 0x19d843 */
  display_assert((char *)0x002b4828, (char *)0x002b45b4, 181, 0);
  system_exit(0);
  _wcslen((wchar_t *)(uintptr_t)esi);
  /* cmp eax, 0x8000 -> jb 0x19d873 */
  display_assert((char *)0x002b4800, (char *)0x002b45b4, 182, 0);
  system_exit(0);
  _wcslen((wchar_t *)(uintptr_t)edi);
  /* cmp eax, 0x8000 -> jb 0x19d8a3 */
  display_assert((char *)0x002b47d8, (char *)0x002b45b4, 183, 0);
  system_exit(0);
  _wcscmp((wchar_t *)(uintptr_t)esi, (wchar_t *)(uintptr_t)edi);
  /* test esi, esi -> jne 0x19d8eb */
  display_assert((char *)0x0027b838, (char *)0x002b45b4, 194, 0);
  system_exit(0);
  _wcslen((wchar_t *)(uintptr_t)esi);
  /* cmp esi, 0x8000 -> jb 0x19d91e */
  display_assert((char *)0x002b483c, (char *)0x002b45b4, 196, 0);
  system_exit(0);
  /* test edi, edi -> jne 0x19d95e */
  display_assert((char *)0x0027b838, (char *)0x002b45b4, 208, 0);
  system_exit(0);
  /* test eax, eax -> jbe 0x19d99d */
  /* test (int16_t)ecx, (int16_t)ecx -> je 0x19d975 */
  /* cmp esi, eax -> jb 0x19d965 */
  /* cmp esi, 0x8000 -> jb 0x19d99d */
  display_assert((char *)0x002b483c, (char *)0x002b45b4, 214, 0);
  system_exit(0);
  /* test esi, esi -> jne 0x19d9db */
  display_assert((char *)0x0027b838, (char *)0x002b45b4, 224, 0);
  system_exit(0);
  _wcslen((wchar_t *)(uintptr_t)esi);
  /* cmp eax, 0x8000 -> jb 0x19da0b */
  display_assert((char *)0x002b4858, (char *)0x002b45b4, 225, 0);
  system_exit(0);
  _wcschr((wchar_t *)(uintptr_t)esi, eax);
  /* test edi, edi -> jne 0x19da53 */
  display_assert((char *)0x002b4828, (char *)0x002b45b4, 235, 0);
  system_exit(0);
  _wcslen((wchar_t *)(uintptr_t)esi);
  /* cmp eax, 0x8000 -> jb 0x19da83 */
  display_assert((char *)0x002b4800, (char *)0x002b45b4, 236, 0);
  system_exit(0);
  _wcslen((wchar_t *)(uintptr_t)edi);
  /* cmp eax, 0x8000 -> jb 0x19dab3 */
  display_assert((char *)0x002b47d8, (char *)0x002b45b4, 237, 0);
  system_exit(0);
  FUN_001dbfa7((wchar_t *)(uintptr_t)esi, (wchar_t *)(uintptr_t)edi);
  /* test edi, edi -> jne 0x19db03 */
  display_assert((char *)0x002b48ac, (char *)0x002b45b4, 247, 0);
  system_exit(0);
  _wcslen((wchar_t *)(uintptr_t)esi);
  /* cmp eax, 0x8000 -> jb 0x19db33 */
  display_assert((char *)0x002b4858, (char *)0x002b45b4, 248, 0);
  system_exit(0);
  _wcslen((wchar_t *)(uintptr_t)edi);
  /* cmp eax, 0x8000 -> jb 0x19db63 */
  display_assert((char *)0x002b4880, (char *)0x002b45b4, 249, 0);
  system_exit(0);

  (void)eax;
  (void)ecx;
  (void)esi;
  (void)edi;
}
