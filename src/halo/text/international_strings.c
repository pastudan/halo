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

/* 0x19c5d0 */
void FUN_0019c5d0(void *callback, void *screen_pos, const void *color, void *clip_bounds, int flags, char *text)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

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
  /* cmp edx, edi -> jge 0x19c7d6 */
  /* relift: test byte ptr [0x4d9b10], 1 -> je 0x19c7fa */
  /* test (int16_t)eax, (int16_t)eax -> jle 0x19c7f2 */
  FUN_00108a10();
  FUN_00108a10();
  /* relift: test byte ptr [0x4d9b10], 2 -> jne 0x19c86d */
  /* relift: cmp (int16_t)esi, word ptr [ebp - 0x34] -> jge 0x19c894 */
  FUN_0019c1b0();
  /* cmp eax, 6 -> ja 0x19c8ee */
  /* relift: cmp (int16_t)ecx, word ptr [0x4d9b28] -> jge 0x19c90b */
  display_assert((char *)0, (char *)0x002b4210, 808, 0);
  system_exit(0);
  /* relift: cmp word ptr [ebp - 0x40], 0 -> jne 0x19c65d */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x19c960 */
void FUN_0019c960(void *callback, void *screen_pos, const void *color, void *clip_bounds, int flags, unsigned short *text)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  display_assert((char *)0x0026184c, (char *)0x002b4210, 839, 0);
  system_exit(0);
  /* cmp ebx, edi -> jne 0x19c9c5 */
  display_assert((char *)0x0027b838, (char *)0x002b4210, 840, 0);
  system_exit(0);
  FUN_0019bd30();
  /* cmp (int16_t)edi, (int16_t)ebx -> jl 0x19ca31 */
  /* cmp (int16_t)edi, (int16_t)eax -> jle 0x19ca57 */
  display_assert((char *)0x002b4488, (char *)0x002b4210, 872, 0);
  system_exit(0);
  /* cmp (int16_t)edi, (int16_t)ebx -> je 0x19ca6d */
  /* relift: cmp word ptr [ebp - 0x18], (int16_t)ebx -> je 0x19ca80 */
  /* cmp (int16_t)edi, (int16_t)eax -> jge 0x19cabe */
  /* relift: cmp word ptr [ebp - 0x18], (int16_t)ebx -> je 0x19cab4 */
  FUN_0019c0a0((void *)0);
  /* cmp (int16_t)eax, 2 -> je 0x19cb20 */
  /* cmp (int16_t)eax, 6 -> je 0x19cb20 */
  FUN_0019cff0(0, 0);
  /* test eax, eax -> je 0x19cb99 */
  /* relift: cmp word ptr [ebp - 0x44], (int16_t)ecx -> je 0x19cb51 */
  /* relift: cmp word ptr [ebp - 0x28], (int16_t)ecx -> jne 0x19cb51 */
  /* cmp edx, ecx -> jge 0x19cb72 */
  /* relift: test byte ptr [0x4d9b10], 1 -> je 0x19cb99 */
  /* test (int16_t)eax, (int16_t)eax -> jle 0x19cb91 */
  FUN_00108a10();
  FUN_00108a10();
  /* relift: test byte ptr [0x4d9b10], 2 -> jne 0x19cc05 */
  /* relift: cmp (int16_t)esi, word ptr [ebp - 0x38] -> jge 0x19cc2c */
  FUN_0019c3c0();
  /* relift: cmp (int16_t)edx, word ptr [0x4d9b28] -> jge 0x19cca3 */
  display_assert((char *)0, (char *)0x002b4210, 1008, 0);
  system_exit(0);
  /* relift: cmp word ptr [ebp - 0x44], 0 -> jne 0x19c9ed */
  /* mem[0x6f0019cc] = eax */
  /* mem[0x440019cc] = eax */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

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
