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

/* FUN_0019c5d0 (0x19c5d0) — XBE naked draft (batch 242). */
#if defined(__clang__)
static void (*const b19c5d0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b19c5d0_exitfn)(int) = system_exit;
static void (*const b19c5d0_c19bd30)(void) = FUN_0019bd30;
static void (*const b19c5d0_c19be30)(void) = parse_string;
static void * (*const b19c5d0_c19cff0)(void *font_tag, unsigned short character) = FUN_0019cff0;
static void (*const b19c5d0_c108a10)(void) = (void *)FUN_00108a10;
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
static void (*const b19c960_c108a10)(void) = (void *)FUN_00108a10;
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

/* FUN_0019cec0 (0x19cec0) — XBE naked draft (batch 272). */
#if defined(__clang__)
static void (*const b19cec0_c1089a0)(int *bounds, int y0, int x0, int h, int w) = (void *)FUN_001089a0;
static void (*const b19cec0_c19c5d0)(void *callback, void *screen_pos, const void *color, void *clip_bounds, int flags, char *text) = FUN_0019c5d0;

__attribute__((naked, noinline))
void FUN_0019cec0(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x10, %%esp\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "movl %%esi, 0x4d9ae8\n\t"
      "movswl 0xc(%%esi), %%eax\n\t"
      "cmpl $0xb, %%eax\n\t"
      "ja .LFUN_0019cec0_16\n\t"
      "movzbl 0x19cfdc(%%eax), %%eax\n\t"
      "jmp *.LFUN_0019cec0_jt(,%%eax,4)\n\t"
      ".LFUN_0019cec0_1:\n\t"
      "pushl %%ebx\n\t"
      "movl 0xc(%%ebp), %%ebx\n\t"
      "testl %%ebx, %%ebx\n\t"
      "pushl %%edi\n\t"
      "jne .LFUN_0019cec0_8\n\t"
      "movw 4, %%cx\n\t"
      "movw 0x6(%%esi), %%ax\n\t"
      "cmpw %%cx, %%ax\n\t"
      "movswl %%cx, %%edi\n\t"
      "jg .LFUN_0019cec0_2\n\t"
      "movswl %%ax, %%edi\n\t"
      ".LFUN_0019cec0_2:\n\t"
      "movw 6, %%cx\n\t"
      "movw 0x4(%%esi), %%ax\n\t"
      "cmpw %%cx, %%ax\n\t"
      "movswl %%cx, %%edx\n\t"
      "jg .LFUN_0019cec0_3\n\t"
      "movswl %%ax, %%edx\n\t"
      ".LFUN_0019cec0_3:\n\t"
      "movw (%%ebx), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "jge .LFUN_0019cec0_4\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "jmp .LFUN_0019cec0_5\n\t"
      ".LFUN_0019cec0_4:\n\t"
      "movswl %%ax, %%ecx\n\t"
      ".LFUN_0019cec0_5:\n\t"
      "movw 2, %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "jge .LFUN_0019cec0_6\n\t"
      "xorl %%eax, %%eax\n\t"
      "jmp .LFUN_0019cec0_7\n\t"
      ".LFUN_0019cec0_6:\n\t"
      "movswl %%ax, %%eax\n\t"
      ".LFUN_0019cec0_7:\n\t"
      "pushl %%edi\n\t"
      "pushl %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "leal -0x8(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1089a0]\n\t"
      "addl $0x14, %%esp\n\t"
      "leal -0x8(%%ebp), %%ebx\n\t"
      ".LFUN_0019cec0_8:\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_0019cec0_15\n\t"
      "movw 0x4(%%eax), %%dx\n\t"
      "movw 0x6(%%esi), %%cx\n\t"
      "cmpw %%dx, %%cx\n\t"
      "movswl %%dx, %%edi\n\t"
      "jg .LFUN_0019cec0_9\n\t"
      "movswl %%cx, %%edi\n\t"
      ".LFUN_0019cec0_9:\n\t"
      "movw 0x6(%%eax), %%dx\n\t"
      "movw 0x4(%%esi), %%cx\n\t"
      "cmpw %%dx, %%cx\n\t"
      "movswl %%dx, %%edx\n\t"
      "jg .LFUN_0019cec0_10\n\t"
      "movswl %%cx, %%edx\n\t"
      ".LFUN_0019cec0_10:\n\t"
      "movw (%%eax), %%cx\n\t"
      "testw %%cx, %%cx\n\t"
      "jge .LFUN_0019cec0_11\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "jmp .LFUN_0019cec0_12\n\t"
      ".LFUN_0019cec0_11:\n\t"
      "movswl %%cx, %%ecx\n\t"
      ".LFUN_0019cec0_12:\n\t"
      "movw 0x2(%%eax), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "jge .LFUN_0019cec0_13\n\t"
      "xorl %%eax, %%eax\n\t"
      "jmp .LFUN_0019cec0_14\n\t"
      ".LFUN_0019cec0_13:\n\t"
      "movswl %%ax, %%eax\n\t"
      ".LFUN_0019cec0_14:\n\t"
      "pushl %%edi\n\t"
      "pushl %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "leal -0x10(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c1089a0]\n\t"
      "addl $0x14, %%esp\n\t"
      "leal -0x10(%%ebp), %%eax\n\t"
      ".LFUN_0019cec0_15:\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "pushl $0\n\t"
      "pushl %%ebx\n\t"
      "pushl $0x19b910\n\t"
      "call *%[c19c5d0]\n\t"
      "addl $0x18, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%ebx\n\t"
      ".LFUN_0019cec0_16:\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_0019cec0_jt:\n\t"
      ".long .LFUN_0019cec0_1\n\t"
      ".long .LFUN_0019cec0_16\n\t"
      ".text\n\t"
      :
      : [c1089a0] "m"(b19cec0_c1089a0), [c19c5d0] "m"(b19cec0_c19c5d0)
      : "memory");
}
#else
#error "FUN_0019cec0: clang naked draft required"
#endif


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
