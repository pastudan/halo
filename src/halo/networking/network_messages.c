/* ========================================================================
 * data_encoding.c — Decode-side encoding state helpers
 * Original source: c:\halo\SOURCE\memory\data_encoding.c
 *
 * Encoding state struct (16 bytes, int[4]):
 *   [0] = buffer pointer
 *   [1] = current offset
 *   [2] = buffer_size
 *   [3] = overflow flag (byte at low byte of word [3])
 * ======================================================================== */

#define byte_swap_raw \
  ((void (*)(void *, int, int))0x118620)

#define byte_swap_structures \
  ((void (*)(void *, void *, int))0x118be0)

#define encode_state_new \
  ((void (*)(int *, int, int))0x119c50)

#define encode_raw_data \
  ((int (*)(int *, int, short, int))0x119cc0)

#define encode_packet_fields \
  ((void (*)(int, int *, short, void *, short, int, short *))0x11afa0)

#define csstrcpy \
  ((char *(*)(char *, const char *))0x8dff0)

#define array_get_element \
  ((int (*)(int *, int, int))0x117ee0)

#define array_reset \
  ((void (*)(int *, int))0x117b20)

#define array_dispose \
  ((void (*)(int *))0x117cf0)

/* packet_header byte-swap definition at 0x3220c0 */
#define packet_header_bs_def ((void *)0x3220c0)

/* hash primes table at 0x3220d4 */
#define hashtable_primes ((short *)0x3220d4)

/* last decode error string global at 0x46e804 */
#define s_last_decode_error (*(char **)0x46e804)

/* FUN_0011a230 (0x11a230) — XBE naked draft (batch 89). */
#if defined(__clang__)
static int (*const b11a230_c8d8d0)(const char *s, int n) = strnlen;
static void (*const b11a230_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b11a230_exitfn)(int) = system_exit;
static void * (*const b11a230_c8de70)(char *destination, const char *source, size_t size) = csstrncpy;

__attribute__((naked, noinline))
bool FUN_0011a230(int *state __attribute__((unused)), const char *source __attribute__((unused)), short max_length __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movswl 0x10(%%ebp), %%eax\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c8d8d0]\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "movl 0x4(%%esi), %%ecx\n\t"
      "movl (%%esi), %%ebx\n\t"
      "movswl %%ax, %%edi\n\t"
      "movl 0x8(%%esi), %%eax\n\t"
      "leal 0x1(%%edi,%%ecx,1), %%edx\n\t"
      "addl $8, %%esp\n\t"
      "addl %%ecx, %%ebx\n\t"
      "cmpl %%eax, %%edx\n\t"
      "jle .LFUN_0011a230_1\n\t"
      "pushl $1\n\t"
      "pushl $0xb6\n\t"
      "pushl $0x28eef8\n\t"
      "pushl $0x28f010\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0011a230_1:\n\t"
      "movl 0x4(%%esi), %%eax\n\t"
      "leal 0x1(%%eax,%%edi,1), %%ecx\n\t"
      "cmpl 0x8(%%esi), %%ecx\n\t"
      "jg .LFUN_0011a230_2\n\t"
      "movb 0xc(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_0011a230_2\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "pushl %%edi\n\t"
      "pushl %%edx\n\t"
      "pushl %%ebx\n\t"
      "call *%[c8de70]\n\t"
      "movb $0, (%%edi,%%ebx,1)\n\t"
      "movl 0x4(%%esi), %%eax\n\t"
      "movb 0xc(%%esi), %%cl\n\t"
      "addl $0xc, %%esp\n\t"
      "incl %%edi\n\t"
      "addl %%edi, %%eax\n\t"
      "movl %%eax, 0x4(%%esi)\n\t"
      "popl %%edi\n\t"
      "xorl %%eax, %%eax\n\t"
      "testb %%cl, %%cl\n\t"
      "popl %%esi\n\t"
      "sete %%al\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0011a230_2:\n\t"
      "movb $1, 0xc(%%esi)\n\t"
      "movb 0xc(%%esi), %%cl\n\t"
      "popl %%edi\n\t"
      "xorl %%eax, %%eax\n\t"
      "testb %%cl, %%cl\n\t"
      "popl %%esi\n\t"
      "sete %%al\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c8d8d0] "m"(b11a230_c8d8d0), [assert] "m"(b11a230_assert), [exitfn] "m"(b11a230_exitfn), [c8de70] "m"(b11a230_c8de70)
      : "memory");
}
#else
#error "FUN_0011a230: clang naked draft required"
#endif


/* FUN_0011a2d0 (0x11a2d0) — readable C lift from XBE leaf. */
void FUN_0011a2d0(int *state, void *buffer, int buffer_size)
{
  extern char DAT_00267900[];
  extern char DAT_0028eef8[];
  extern char DAT_0028edb4[];

  if (buffer == 0) {
    display_assert(DAT_00267900, DAT_0028eef8, 0xcc, true);
    system_exit(-1);
  }
  if (buffer_size < 0) {
    display_assert(DAT_0028edb4, DAT_0028eef8, 0xcd, true);
    system_exit(-1);
  }
  csmemset(state, 0, 0x10);
  state[0] = (int)buffer;
  state[2] = buffer_size;
}




/* FUN_0011a340 (0x11a340) — XBE naked draft (batch 86). */
#if defined(__clang__)
static void (*const b11a340_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b11a340_exitfn)(int) = system_exit;
static void (*const b11a340_c118be0)(void *definition, void *data, int count) = FUN_00118be0;

__attribute__((naked, noinline))
int FUN_0011a340(int *state __attribute__((unused)), short count __attribute__((unused)), void *bs_definition __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "pushl %%edi\n\t"
      "je .LFUN_0011a340_1\n\t"
      "cmpl $0, (%%esi)\n\t"
      "je .LFUN_0011a340_1\n\t"
      "movl 0x4(%%esi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jl .LFUN_0011a340_1\n\t"
      "cmpl 0x8(%%esi), %%eax\n\t"
      "jle .LFUN_0011a340_2\n\t"
      ".LFUN_0011a340_1:\n\t"
      "pushl $1\n\t"
      "pushl $0xde\n\t"
      "pushl $0x28eef8\n\t"
      "pushl $0x28f058\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0011a340_2:\n\t"
      "movw 0xc(%%ebp), %%di\n\t"
      "testw %%di, %%di\n\t"
      "jge .LFUN_0011a340_3\n\t"
      "pushl $1\n\t"
      "pushl $0xdf\n\t"
      "pushl $0x28eef8\n\t"
      "pushl $0x28f044\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0011a340_3:\n\t"
      "movl 0x10(%%ebp), %%ebx\n\t"
      "testl %%ebx, %%ebx\n\t"
      "jne .LFUN_0011a340_4\n\t"
      "pushl $1\n\t"
      "pushl $0xe0\n\t"
      "pushl $0x28eef8\n\t"
      "pushl $0x28ef80\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0011a340_4:\n\t"
      "movw 0x4(%%ebx), %%ax\n\t"
      "movl 0x4(%%esi), %%ecx\n\t"
      "imulw %%di, %%ax\n\t"
      "movl 0x8(%%esi), %%edi\n\t"
      "movswl %%ax, %%ebx\n\t"
      "leal (%%ebx,%%ecx,1), %%edx\n\t"
      "cmpl %%edi, %%edx\n\t"
      "jg .LFUN_0011a340_6\n\t"
      "movb 0xc(%%esi), %%dl\n\t"
      "testb %%dl, %%dl\n\t"
      "jne .LFUN_0011a340_6\n\t"
      "movl (%%esi), %%edi\n\t"
      "addl %%ecx, %%edi\n\t"
      "testw %%ax, %%ax\n\t"
      "je .LFUN_0011a340_5\n\t"
      "movswl 0xc(%%ebp), %%eax\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "call *%[c118be0]\n\t"
      "movl 0x4(%%esi), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "addl %%ebx, %%eax\n\t"
      "movl %%eax, 0x4(%%esi)\n\t"
      ".LFUN_0011a340_5:\n\t"
      "movl %%edi, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0011a340_6:\n\t"
      "popl %%edi\n\t"
      "movb $1, 0xc(%%esi)\n\t"
      "popl %%esi\n\t"
      "xorl %%eax, %%eax\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b11a340_assert), [exitfn] "m"(b11a340_exitfn), [c118be0] "m"(b11a340_c118be0)
      : "memory");
}
#else
#error "FUN_0011a340: clang naked draft required"
#endif


/* FUN_0011a430 (0x11a430) — XBE naked draft (batch 86). */
#if defined(__clang__)
static void (*const b11a430_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b11a430_exitfn)(int) = system_exit;
static void (*const b11a430_c118620)(void *data, int count, int element_size) = FUN_00118620;

__attribute__((naked, noinline))
int FUN_0011a430(int *state __attribute__((unused)), short count __attribute__((unused)), int element_size __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "pushl %%edi\n\t"
      "xorl %%edi, %%edi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_0011a430_1\n\t"
      "cmpl $0, (%%esi)\n\t"
      "je .LFUN_0011a430_1\n\t"
      "movl 0x4(%%esi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jl .LFUN_0011a430_1\n\t"
      "cmpl 0x8(%%esi), %%eax\n\t"
      "jle .LFUN_0011a430_2\n\t"
      ".LFUN_0011a430_1:\n\t"
      "pushl $1\n\t"
      "pushl $0x100\n\t"
      "pushl $0x28eef8\n\t"
      "pushl $0x28f058\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0011a430_2:\n\t"
      "movw 0xc(%%ebp), %%bx\n\t"
      "testw %%bx, %%bx\n\t"
      "jge .LFUN_0011a430_3\n\t"
      "pushl $1\n\t"
      "pushl $0x101\n\t"
      "pushl $0x28eef8\n\t"
      "pushl $0x28eb58\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0011a430_3:\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "addl $8, %%eax\n\t"
      "cmpl $9, %%eax\n\t"
      "ja .LFUN_0011a430_8\n\t"
      "movzbl 0x11a548(%%eax), %%eax\n\t"
      "jmp *.LFUN_0011a430_jt(,%%eax,4)\n\t"
      ".LFUN_0011a430_4:\n\t"
      "movswl %%bx, %%ebx\n\t"
      "jmp .LFUN_0011a430_9\n\t"
      ".LFUN_0011a430_5:\n\t"
      "movswl %%bx, %%ebx\n\t"
      "shll $1, %%ebx\n\t"
      "jmp .LFUN_0011a430_9\n\t"
      ".LFUN_0011a430_6:\n\t"
      "movswl %%bx, %%ebx\n\t"
      "shll $2, %%ebx\n\t"
      "jmp .LFUN_0011a430_9\n\t"
      ".LFUN_0011a430_7:\n\t"
      "movswl %%bx, %%ebx\n\t"
      "shll $3, %%ebx\n\t"
      "jmp .LFUN_0011a430_9\n\t"
      ".LFUN_0011a430_8:\n\t"
      "pushl $1\n\t"
      "pushl $0x109\n\t"
      "pushl $0x28eef8\n\t"
      "pushl $0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "movl 0xc(%%ebp), %%ebx\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0011a430_9:\n\t"
      "movl 0x4(%%esi), %%eax\n\t"
      "movl 0x8(%%esi), %%edx\n\t"
      "leal (%%eax,%%ebx,1), %%ecx\n\t"
      "cmpl %%edx, %%ecx\n\t"
      "jg .LFUN_0011a430_11\n\t"
      "movb 0xc(%%esi), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "jne .LFUN_0011a430_11\n\t"
      "movl (%%esi), %%edi\n\t"
      "addl %%eax, %%edi\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "cmpl $1, %%eax\n\t"
      "je .LFUN_0011a430_10\n\t"
      "movswl 0xc(%%ebp), %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "call *%[c118620]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_0011a430_10:\n\t"
      "addl %%ebx, 0x4(%%esi)\n\t"
      "movl %%edi, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0011a430_11:\n\t"
      "movl %%edi, %%eax\n\t"
      "popl %%edi\n\t"
      "movb $1, 0xc(%%esi)\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "movl %%edi, %%edi\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_0011a430_jt:\n\t"
      ".long .LFUN_0011a430_7\n\t"
      ".long .LFUN_0011a430_6\n\t"
      ".long .LFUN_0011a430_5\n\t"
      ".long .LFUN_0011a430_4\n\t"
      ".long .LFUN_0011a430_8\n\t"
      ".text\n\t"
      :
      : [assert] "m"(b11a430_assert), [exitfn] "m"(b11a430_exitfn), [c118620] "m"(b11a430_c118620)
      : "memory");
}
#else
#error "FUN_0011a430: clang naked draft required"
#endif


/* FUN_0011a560 (0x11a560) — readable C lift from XBE leaf.
 * Read next byte from a bounded buffer cursor. */
unsigned char FUN_0011a560(int *state)
{
  extern char DAT_0028f058[];
  extern char DAT_0028eef8[];
  int offset;
  int limit;
  unsigned char *base;
  int next;

  if (state == 0 || state[0] == 0 || state[1] < 0 || state[1] > state[2]) {
    display_assert(DAT_0028f058, DAT_0028eef8, 0x100, true);
    system_exit(-1);
  }
  offset = state[1];
  limit = state[2];
  next = offset + 1;
  if (next > limit || *((unsigned char *)state + 0xc) != 0) {
    *((unsigned char *)state + 0xc) = 1;
    return 0;
  }
  base = (unsigned char *)state[0];
  state[1] = next;
  if (base + offset == 0)
    return 0;
  return base[offset];
}



/* FUN_0011a5d0 (0x11a5d0) — XBE naked draft (batch 90). */
#if defined(__clang__)
static void (*const b11a5d0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b11a5d0_exitfn)(int) = system_exit;
static void (*const b11a5d0_c118620)(void *data, int count, int element_size) = FUN_00118620;

__attribute__((naked, noinline))
short FUN_0011a5d0(int *state __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "pushl %%edi\n\t"
      "je .LFUN_0011a5d0_1\n\t"
      "cmpl $0, (%%esi)\n\t"
      "je .LFUN_0011a5d0_1\n\t"
      "movl 0x4(%%esi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jl .LFUN_0011a5d0_1\n\t"
      "cmpl 0x8(%%esi), %%eax\n\t"
      "jle .LFUN_0011a5d0_2\n\t"
      ".LFUN_0011a5d0_1:\n\t"
      "pushl $1\n\t"
      "pushl $0x100\n\t"
      "pushl $0x28eef8\n\t"
      "pushl $0x28f058\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0011a5d0_2:\n\t"
      "movl 0x4(%%esi), %%eax\n\t"
      "movl 0x8(%%esi), %%edx\n\t"
      "leal 0x2(%%eax), %%ecx\n\t"
      "cmpl %%edx, %%ecx\n\t"
      "jg .LFUN_0011a5d0_3\n\t"
      "movb 0xc(%%esi), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "jne .LFUN_0011a5d0_3\n\t"
      "movl (%%esi), %%edi\n\t"
      "pushl $-2\n\t"
      "addl %%eax, %%edi\n\t"
      "pushl $1\n\t"
      "pushl %%edi\n\t"
      "call *%[c118620]\n\t"
      "movl 0x4(%%esi), %%eax\n\t"
      "addl $2, %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%edi, %%edi\n\t"
      "movl %%eax, 0x4(%%esi)\n\t"
      "je .LFUN_0011a5d0_4\n\t"
      "movswl (%%edi), %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0011a5d0_3:\n\t"
      "movb $1, 0xc(%%esi)\n\t"
      ".LFUN_0011a5d0_4:\n\t"
      "popl %%edi\n\t"
      "xorl %%eax, %%eax\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b11a5d0_assert), [exitfn] "m"(b11a5d0_exitfn), [c118620] "m"(b11a5d0_c118620)
      : "memory");
}
#else
#error "FUN_0011a5d0: clang naked draft required"
#endif


/* FUN_0011a650 (0x11a650) — XBE naked draft (batch 90). */
#if defined(__clang__)
static void (*const b11a650_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b11a650_exitfn)(int) = system_exit;
static void (*const b11a650_c118620)(void *data, int count, int element_size) = FUN_00118620;

__attribute__((naked, noinline))
int FUN_0011a650(int *state __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "pushl %%edi\n\t"
      "je .LFUN_0011a650_1\n\t"
      "cmpl $0, (%%esi)\n\t"
      "je .LFUN_0011a650_1\n\t"
      "movl 0x4(%%esi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jl .LFUN_0011a650_1\n\t"
      "cmpl 0x8(%%esi), %%eax\n\t"
      "jle .LFUN_0011a650_2\n\t"
      ".LFUN_0011a650_1:\n\t"
      "pushl $1\n\t"
      "pushl $0x100\n\t"
      "pushl $0x28eef8\n\t"
      "pushl $0x28f058\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0011a650_2:\n\t"
      "movl 0x4(%%esi), %%eax\n\t"
      "movl 0x8(%%esi), %%edx\n\t"
      "leal 0x4(%%eax), %%ecx\n\t"
      "cmpl %%edx, %%ecx\n\t"
      "jg .LFUN_0011a650_3\n\t"
      "movb 0xc(%%esi), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "jne .LFUN_0011a650_3\n\t"
      "movl (%%esi), %%edi\n\t"
      "pushl $-4\n\t"
      "addl %%eax, %%edi\n\t"
      "pushl $1\n\t"
      "pushl %%edi\n\t"
      "call *%[c118620]\n\t"
      "movl 0x4(%%esi), %%eax\n\t"
      "addl $4, %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%edi, %%edi\n\t"
      "movl %%eax, 0x4(%%esi)\n\t"
      "je .LFUN_0011a650_4\n\t"
      "movl (%%edi), %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0011a650_3:\n\t"
      "movb $1, 0xc(%%esi)\n\t"
      ".LFUN_0011a650_4:\n\t"
      "popl %%edi\n\t"
      "xorl %%eax, %%eax\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b11a650_assert), [exitfn] "m"(b11a650_exitfn), [c118620] "m"(b11a650_c118620)
      : "memory");
}
#else
#error "FUN_0011a650: clang naked draft required"
#endif


/* FUN_0011a6d0 (0x11a6d0) — readable C lift. */
unsigned long long FUN_0011a6d0(int *state)
{
  int *pair;

  pair = (int *)FUN_0011a430(state, 1, -8);
  if (pair == NULL)
    return 0;
  return ((unsigned long long)(unsigned int)pair[1] << 32) | (unsigned int)pair[0];
}

/* FUN_0011a700 (0x11a700) — readable C lift. */
unsigned int FUN_0011a700(int *state, int maximum_value)
{
  if (maximum_value <= 0) {
    display_assert((const char *)0x28ef70, (const char *)0x28eef8, 0x141, 1);
    system_exit(-1);
  }
  if (maximum_value <= 0xff)
    return (unsigned int)FUN_0011a560(state);
  if (maximum_value <= 0xffff)
    return (unsigned int)(int)FUN_0011a5d0(state);
  return (unsigned int)FUN_0011a650(state);
}

/* FUN_0011a770 (0x11a770) — XBE naked draft (batch 84). */
#if defined(__clang__)
static void (*const b11a770_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b11a770_exitfn)(int) = system_exit;
static unsigned char (*const b11a770_c11a560)(int *state) = FUN_0011a560;
static short (*const b11a770_c11a5d0)(int *state) = FUN_0011a5d0;
static int (*const b11a770_c11a650)(int *state) = FUN_0011a650;
static int64_t (*const b11a770_c11a6d0)(int *state) = FUN_0011a6d0;
static int (*const b11a770_c11a340)(int *state, short count, void *bs_definition) = FUN_0011a340;

__attribute__((naked, noinline))
void * FUN_0011a770(int *state __attribute__((unused)), int element_size_type __attribute__((unused)), unsigned int *element_count_ref __attribute__((unused)), int maximum_element_count __attribute__((unused)), void *bs_definition __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "pushl %%edi\n\t"
      "je .LFUN_0011a770_1\n\t"
      "cmpl $0, (%%esi)\n\t"
      "je .LFUN_0011a770_1\n\t"
      "movl 0x4(%%esi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jl .LFUN_0011a770_1\n\t"
      "cmpl 0x8(%%esi), %%eax\n\t"
      "jl .LFUN_0011a770_2\n\t"
      ".LFUN_0011a770_1:\n\t"
      "pushl $1\n\t"
      "pushl $0x15c\n\t"
      "pushl $0x28eef8\n\t"
      "pushl $0x28ef20\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0011a770_2:\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_0011a770_3\n\t"
      "pushl $1\n\t"
      "pushl $0x15d\n\t"
      "pushl $0x28eef8\n\t"
      "pushl $0x28f0c0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0011a770_3:\n\t"
      "movl 0x14(%%ebp), %%ebx\n\t"
      "testl %%ebx, %%ebx\n\t"
      "jg .LFUN_0011a770_4\n\t"
      "pushl $1\n\t"
      "pushl $0x15e\n\t"
      "pushl $0x28eef8\n\t"
      "pushl $0x28f0a8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0011a770_4:\n\t"
      "movl 0x18(%%ebp), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .LFUN_0011a770_5\n\t"
      "pushl $1\n\t"
      "pushl $0x15f\n\t"
      "pushl $0x28eef8\n\t"
      "pushl $0x28ef80\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0011a770_5:\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "addl $8, %%eax\n\t"
      "cmpl $9, %%eax\n\t"
      "ja .LFUN_0011a770_10\n\t"
      "movzbl 0x11a8d0(%%eax), %%eax\n\t"
      "jmp *.LFUN_0011a770_jt(,%%eax,4)\n\t"
      ".LFUN_0011a770_6:\n\t"
      "pushl %%esi\n\t"
      "call *%[c11a560]\n\t"
      "addl $4, %%esp\n\t"
      "movzbl %%al, %%eax\n\t"
      "jmp .LFUN_0011a770_11\n\t"
      ".LFUN_0011a770_7:\n\t"
      "pushl %%esi\n\t"
      "call *%[c11a5d0]\n\t"
      "addl $4, %%esp\n\t"
      "movswl %%ax, %%eax\n\t"
      "jmp .LFUN_0011a770_11\n\t"
      ".LFUN_0011a770_8:\n\t"
      "pushl %%esi\n\t"
      "call *%[c11a650]\n\t"
      "addl $4, %%esp\n\t"
      "jmp .LFUN_0011a770_11\n\t"
      ".LFUN_0011a770_9:\n\t"
      "pushl %%esi\n\t"
      "call *%[c11a6d0]\n\t"
      "addl $4, %%esp\n\t"
      "jmp .LFUN_0011a770_11\n\t"
      ".LFUN_0011a770_10:\n\t"
      "pushl $1\n\t"
      "pushl $0x172\n\t"
      "pushl $0x28eef8\n\t"
      "pushl $0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0011a770_11:\n\t"
      "movb 0xc(%%esi), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "jne .LFUN_0011a770_12\n\t"
      "testl %%eax, %%eax\n\t"
      "jl .LFUN_0011a770_12\n\t"
      "cmpl %%ebx, %%eax\n\t"
      "jg .LFUN_0011a770_12\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "movl %%eax, (%%ecx)\n\t"
      "call *%[c11a340]\n\t"
      "addl $0xc, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0011a770_12:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "xorl %%eax, %%eax\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_0011a770_jt:\n\t"
      ".long .LFUN_0011a770_9\n\t"
      ".long .LFUN_0011a770_8\n\t"
      ".long .LFUN_0011a770_7\n\t"
      ".long .LFUN_0011a770_6\n\t"
      ".long .LFUN_0011a770_10\n\t"
      ".text\n\t"
      :
      : [assert] "m"(b11a770_assert), [exitfn] "m"(b11a770_exitfn), [c11a560] "m"(b11a770_c11a560), [c11a5d0] "m"(b11a770_c11a5d0), [c11a650] "m"(b11a770_c11a650), [c11a6d0] "m"(b11a770_c11a6d0), [c11a340] "m"(b11a770_c11a340)
      : "memory");
}
#else
#error "FUN_0011a770: clang naked draft required"
#endif


/* FUN_0011a8e0 (0x11a8e0) — XBE naked draft (batch 93). */
#if defined(__clang__)


__attribute__((naked, noinline))
char * FUN_0011a8e0(int *state __attribute__((unused)), unsigned short max_length __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "movl (%%ecx), %%eax\n\t"
      "movl 0x8(%%ecx), %%edx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x4(%%ecx), %%edi\n\t"
      "addl %%edi, %%eax\n\t"
      "xorl %%esi, %%esi\n\t"
      "cmpl %%edx, %%edi\n\t"
      "jge .LFUN_0011a8e0_2\n\t"
      "xorl %%edx, %%edx\n\t"
      "jmp .LFUN_0011a8e0_1\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".LFUN_0011a8e0_1:\n\t"
      "cmpb $0, (%%edx,%%eax,1)\n\t"
      "je .LFUN_0011a8e0_3\n\t"
      "movl 0x4(%%ecx), %%ebx\n\t"
      "incl %%esi\n\t"
      "movswl %%si, %%edx\n\t"
      "addl %%edx, %%ebx\n\t"
      "cmpl 0x8(%%ecx), %%ebx\n\t"
      "jl .LFUN_0011a8e0_1\n\t"
      ".LFUN_0011a8e0_2:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb $1, 0xc(%%ecx)\n\t"
      "xorl %%eax, %%eax\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0011a8e0_3:\n\t"
      "movswl %%si, %%edx\n\t"
      "leal 0x1(%%edx,%%edi,1), %%edx\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%edx, 0x4(%%ecx)\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "FUN_0011a8e0: clang naked draft required"
#endif


/* ========================================================================
 * Already-ported: verify_packet_group_definitions (0x11a930)
 * ======================================================================== */

void verify_packet_group_definitions(group_definition *group)
{
  short i;

  for (i = 0; i < group->packet_count; i++) {
    packet_entry *entry = &group->packets[i];

    if (entry->definition != NULL) {
      assert_halt(entry->packet_class >= 0 &&
                  entry->packet_class < group->packet_class_count);
      assert_halt(entry->definition->size <=
                  group->maximum_decoded_packet_size);
      assert_halt((uint32_t)(entry->definition->size + sizeof(packet_header)) <=
                  (uint32_t)group->maximum_encoded_packet_size);
      verify_packet_definition(entry->definition);
    }
  }
}

/* network_messages.c — Network game packet group initialization.
 *
 * Corresponds to network_messages.obj.
 * initialize_network_game_packets at 0x12b640 is a thin wrapper that calls
 * verify_packet_group_definitions (0x11a930) with the global
 * s_network_game_messages_group (0x323510).
 *
 * verify_packet_group_definitions iterates the packet entries in the given
 * group, validates class bounds and size constraints, then calls
 * verify_packet_definition on each non-NULL definition.
 *
 * verify_packet_definition at 0x11b540 validates a single packet_definition:
 * checks non-NULL, size >= 0, version >= 0, name and fields non-NULL, then
 * (if not yet validated) computes total field sizes and confirms they match
 * the declared size. Sets validated = 1 after success.
 *
 * Original source: c:\halo\SOURCE\memory\data_packet_groups.c lines 0x28-0x2a
 * verify_packet_definition source: c:\halo\SOURCE\memory\data_packets.c lines
 * 0x20-0x2b
 */

/* compute_packet_field_sizes at 0x11add0 — not yet ported (data_packets.c) */
#define compute_packet_field_sizes \
  ((void (*)(packet_definition *, short *, short *, short *))0x11add0)

void verify_packet_definition(packet_definition *def)
{
  short computed_size;
  short field_count;

  if (def == NULL) {
    display_assert("packet_definition",
                   "c:\\halo\\SOURCE\\memory\\data_packets.c", 0x20, 1);
    system_exit(-1);
  }
  if (def->size < 0) {
    display_assert("packet_definition->size>=0",
                   "c:\\halo\\SOURCE\\memory\\data_packets.c", 0x21, 1);
    system_exit(-1);
  }
  if (def->version < 0) {
    display_assert("packet_definition->version>=0",
                   "c:\\halo\\SOURCE\\memory\\data_packets.c", 0x22, 1);
    system_exit(-1);
  }
  if (def->name == NULL || def->fields == NULL) {
    display_assert("packet_definition->name && packet_definition->fields",
                   "c:\\halo\\SOURCE\\memory\\data_packets.c", 0x23, 1);
    system_exit(-1);
  }
  if (!def->validated) {
    compute_packet_field_sizes(def, &computed_size, def->fields, &field_count);
    if (computed_size != def->size) {
      display_assert(csprintf(error_string_buffer,
                              "packet '%s' fields added up to #%d bytes but "
                              "should have been #%d bytes.",
                              def->name, (int)computed_size, (int)def->size),
                     "c:\\halo\\SOURCE\\memory\\data_packets.c", 0x2b, 1);
      system_exit(-1);
    }
    def->validated = 1;
  }
}

/* ========================================================================
 * data_packet_groups.c — Packet group decode
 * ======================================================================== */

/* FUN_0011aa40 (0x11aa40) — XBE naked draft (batch 84). */
#if defined(__clang__)
static void (*const b11aa40_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b11aa40_exitfn)(int) = system_exit;
static void (*const b11aa40_c118be0)(void *definition, void *data, int count) = FUN_00118be0;
static bool (*const b11aa40_c11b750)(int definition, int encoded_packet, short encoded_packet_size, int decoded_packet, unsigned short *version_out, short *bytes_consumed_out) = FUN_0011b750;

__attribute__((naked, noinline))
bool FUN_0011aa40(int group __attribute__((unused)), void *decoded_packet __attribute__((unused)), char *encoded_packet __attribute__((unused)), short *encoded_packet_size __attribute__((unused)), short *packet_type __attribute__((unused)), short *packet_version __attribute__((unused)), short expected_packet_class __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "movl $0, -0x4(%%ebp)\n\t"
      "jne .LFUN_0011aa40_1\n\t"
      "pushl $1\n\t"
      "pushl $0x49\n\t"
      "pushl $0x28f1f0\n\t"
      "pushl $0x28f340\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0011aa40_1:\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x10(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x14(%%ebp), %%edi\n\t"
      "je .LFUN_0011aa40_2\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .LFUN_0011aa40_3\n\t"
      ".LFUN_0011aa40_2:\n\t"
      "pushl $1\n\t"
      "pushl $0x4a\n\t"
      "pushl $0x28f1f0\n\t"
      "pushl $0x28f318\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0011aa40_3:\n\t"
      "movl 0x18(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_0011aa40_4\n\t"
      "movl 0x1c(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_0011aa40_5\n\t"
      ".LFUN_0011aa40_4:\n\t"
      "pushl $1\n\t"
      "pushl $0x4b\n\t"
      "pushl $0x28f1f0\n\t"
      "pushl $0x28f2f8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0011aa40_5:\n\t"
      "movw 0x20(%%ebp), %%bx\n\t"
      "testw %%bx, %%bx\n\t"
      "jl .LFUN_0011aa40_6\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "cmpw 0x6(%%eax), %%bx\n\t"
      "jl .LFUN_0011aa40_7\n\t"
      ".LFUN_0011aa40_6:\n\t"
      "pushl $1\n\t"
      "pushl $0x4d\n\t"
      "pushl $0x28f1f0\n\t"
      "pushl $0x28f2a0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0011aa40_7:\n\t"
      "movw (%%edi), %%ax\n\t"
      "cmpw $1, %%ax\n\t"
      "jb .LFUN_0011aa40_11\n\t"
      "movswl %%ax, %%ecx\n\t"
      "leal -0x1(%%ecx,%%esi,1), %%esi\n\t"
      "pushl $1\n\t"
      "pushl %%esi\n\t"
      "pushl $0x3220c0\n\t"
      "call *%[c118be0]\n\t"
      "movb (%%esi), %%al\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jl .LFUN_0011aa40_10\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "movsbw %%al, %%dx\n\t"
      "cmpw 0x4(%%ecx), %%dx\n\t"
      "jge .LFUN_0011aa40_10\n\t"
      "movl 0x10(%%ecx), %%ecx\n\t"
      "movsbl %%al, %%eax\n\t"
      "cmpw %%bx, (%%ecx,%%eax,8)\n\t"
      "leal (%%ecx,%%eax,8), %%eax\n\t"
      "jne .LFUN_0011aa40_9\n\t"
      "decw (%%edi)\n\t"
      "movl 0x4(%%eax), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "movw (%%edi), %%cx\n\t"
      "je .LFUN_0011aa40_8\n\t"
      "movl 0x1c(%%ebp), %%edx\n\t"
      "pushl $0\n\t"
      "pushl %%edx\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ecx\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "call *%[c11b750]\n\t"
      "addl $0x18, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_0011aa40_8\n\t"
      "movl $0x28f278, -0x4(%%ebp)\n\t"
      "jmp .LFUN_0011aa40_12\n\t"
      ".LFUN_0011aa40_8:\n\t"
      "movsbw (%%esi), %%dx\n\t"
      "movl 0x18(%%ebp), %%eax\n\t"
      "movw %%dx, (%%eax)\n\t"
      "jmp .LFUN_0011aa40_12\n\t"
      ".LFUN_0011aa40_9:\n\t"
      "movl $0x28f254, -0x4(%%ebp)\n\t"
      "jmp .LFUN_0011aa40_12\n\t"
      ".LFUN_0011aa40_10:\n\t"
      "movl $0x28f238, -0x4(%%ebp)\n\t"
      "jmp .LFUN_0011aa40_12\n\t"
      ".LFUN_0011aa40_11:\n\t"
      "movl $0x28f21c, -0x4(%%ebp)\n\t"
      ".LFUN_0011aa40_12:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "testl %%eax, %%eax\n\t"
      "popl %%edi\n\t"
      "sete %%cl\n\t"
      "popl %%esi\n\t"
      "movl %%eax, 0x46e804\n\t"
      "movb %%cl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b11aa40_assert), [exitfn] "m"(b11aa40_exitfn), [c118be0] "m"(b11aa40_c118be0), [c11b750] "m"(b11aa40_c11b750)
      : "memory");
}
#else
#error "FUN_0011aa40: clang naked draft required"
#endif


/* ========================================================================
 * data_packets.c — Packet field encode/decode
 * ======================================================================== */

/* FUN_0011b2a0 (0x11b2a0) — XBE naked draft (batch 82). */
#if defined(__clang__)
static int (*const b11b2a0_c11a430)(int *state, short count, int element_size) = FUN_0011a430;
static void * (*const b11b2a0_c8e0b0)(void *destination, void *source, size_t size) = csmemcpy;
static char * (*const b11b2a0_c11a8e0)(int *state, unsigned short max_length) = (void *)FUN_0011a8e0;
static char * (*const b11b2a0_c8dff0)(char *destination, const char *source) = csstrcpy;
static unsigned int (*const b11b2a0_c11a700)(int *state, int maximum_value) = (void *)FUN_0011a700;
static void (*const b11b2a0_c11add0)(packet_definition *def, short *param_2, short *param_3, short *param_4) = compute_packet_field_sizes;
static void (*const b11b2a0_c11b2a0)(int definition, int *decode_state, unsigned short version, unsigned short *output, short *decoded_size_out, short *field_defs, short *field_count_out) = FUN_0011b2a0;
static void *(*const b11b2a0_memset)(void *, int, unsigned int) = csmemset;

__attribute__((naked, noinline))
void FUN_0011b2a0(int definition __attribute__((unused)), int *decode_state __attribute__((unused)), unsigned short version __attribute__((unused)), unsigned short *output __attribute__((unused)), short *decoded_size_out __attribute__((unused)), short *field_defs __attribute__((unused)), short *field_count_out __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x10, %%esp\n\t"
      "movl 0x1c(%%ebp), %%eax\n\t"
      "cmpw $9, (%%eax)\n\t"
      "pushl %%ebx\n\t"
      "movl 0x14(%%ebp), %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl %%eax, %%esi\n\t"
      "movl %%ebx, -0xc(%%ebp)\n\t"
      "je .LFUN_0011b2a0_11\n\t"
      "pushl %%edi\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      ".LFUN_0011b2a0_1:\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "cmpw 0x4(%%esi), %%cx\n\t"
      "jl .LFUN_0011b2a0_20\n\t"
      "movw 0x6(%%esi), %%ax\n\t"
      "cmpw %%ax, %%cx\n\t"
      "jle .LFUN_0011b2a0_2\n\t"
      "testw %%ax, %%ax\n\t"
      "jne .LFUN_0011b2a0_20\n\t"
      ".LFUN_0011b2a0_2:\n\t"
      "movswl (%%esi), %%eax\n\t"
      "decl %%eax\n\t"
      "cmpl $7, %%eax\n\t"
      "ja .LFUN_0011b2a0_10\n\t"
      "jmp *.LFUN_0011b2a0_jt(,%%eax,4)\n\t"
      ".LFUN_0011b2a0_3:\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x2(%%esi), %%ax\n\t"
      "pushl $1\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "call *%[c11a430]\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_0011b2a0_10\n\t"
      "movswl 0x2(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "call *%[c8e0b0]\n\t"
      "addl $0xc, %%esp\n\t"
      "jmp .LFUN_0011b2a0_10\n\t"
      ".LFUN_0011b2a0_4:\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x2(%%esi), %%dx\n\t"
      "pushl $-2\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "call *%[c11a430]\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_0011b2a0_10\n\t"
      "movswl 0x2(%%esi), %%ecx\n\t"
      "shll $1, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "call *%[c8e0b0]\n\t"
      "addl $0xc, %%esp\n\t"
      "jmp .LFUN_0011b2a0_10\n\t"
      ".LFUN_0011b2a0_5:\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x2(%%esi), %%dx\n\t"
      "pushl $-4\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "call *%[c11a430]\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_0011b2a0_10\n\t"
      "movswl 0x2(%%esi), %%ecx\n\t"
      "shll $2, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "call *%[c8e0b0]\n\t"
      "addl $0xc, %%esp\n\t"
      "jmp .LFUN_0011b2a0_10\n\t"
      ".LFUN_0011b2a0_6:\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x2(%%esi), %%dx\n\t"
      "pushl $-8\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "call *%[c11a430]\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_0011b2a0_10\n\t"
      "movswl 0x2(%%esi), %%ecx\n\t"
      "shll $3, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "call *%[c8e0b0]\n\t"
      "addl $0xc, %%esp\n\t"
      "jmp .LFUN_0011b2a0_10\n\t"
      ".LFUN_0011b2a0_7:\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x2(%%esi), %%dx\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "call *%[c11a8e0]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_0011b2a0_10\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "call *%[c8dff0]\n\t"
      "addl $8, %%esp\n\t"
      "jmp .LFUN_0011b2a0_10\n\t"
      ".LFUN_0011b2a0_8:\n\t"
      "movswl 0x2(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "call *%[c11a700]\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "movl %%eax, %%ebx\n\t"
      "pushl $1\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "movw %%bx, (%%ecx)\n\t"
      "call *%[c11a430]\n\t"
      "addl $0x14, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_0011b2a0_9\n\t"
      "movswl %%bx, %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "addl $2, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c8e0b0]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_0011b2a0_9:\n\t"
      "movl -0xc(%%ebp), %%ebx\n\t"
      ".LFUN_0011b2a0_10:\n\t"
      "movswl 0x8(%%esi), %%ecx\n\t"
      "addl %%ecx, %%ebx\n\t"
      "addl $0xa, %%esi\n\t"
      "cmpw $9, (%%esi)\n\t"
      "movl %%ebx, -0xc(%%ebp)\n\t"
      "jne .LFUN_0011b2a0_1\n\t"
      "movl 0x1c(%%ebp), %%eax\n\t"
      "popl %%edi\n\t"
      ".LFUN_0011b2a0_11:\n\t"
      "movl 0x20(%%ebp), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .LFUN_0011b2a0_12\n\t"
      "subl %%eax, %%esi\n\t"
      "movl $0x66666667, %%eax\n\t"
      "imull %%esi\n\t"
      "sarl $2, %%edx\n\t"
      "movl %%edx, %%eax\n\t"
      "shrl $0x1f, %%eax\n\t"
      "leal 0x1(%%edx,%%eax,1), %%edx\n\t"
      "movw %%dx, (%%ecx)\n\t"
      ".LFUN_0011b2a0_12:\n\t"
      "movl 0x18(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_0011b2a0_13\n\t"
      "subl 0x14(%%ebp), %%ebx\n\t"
      "movw %%bx, (%%eax)\n\t"
      ".LFUN_0011b2a0_13:\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0011b2a0_14:\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x2(%%esi), %%cx\n\t"
      "pushl $1\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edi\n\t"
      "call *%[c11a430]\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_0011b2a0_10\n\t"
      "movswl 0x2(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "call *%[c8e0b0]\n\t"
      "addl $0xc, %%esp\n\t"
      "jmp .LFUN_0011b2a0_10\n\t"
      ".LFUN_0011b2a0_15:\n\t"
      "movswl 0x2(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "call *%[c11a700]\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "movl %%eax, %%ebx\n\t"
      "leal -0x8(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal 0xa(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0\n\t"
      "pushl %%edx\n\t"
      "movl %%ebx, -0x10(%%ebp)\n\t"
      "call *%[c11add0]\n\t"
      "addl $0x18, %%esp\n\t"
      "testw %%bx, %%bx\n\t"
      "jl .LFUN_0011b2a0_16\n\t"
      "cmpw 0x2(%%esi), %%bx\n\t"
      "jle .LFUN_0011b2a0_17\n\t"
      ".LFUN_0011b2a0_16:\n\t"
      "movl $0, -0x10(%%ebp)\n\t"
      "movl -0x10(%%ebp), %%ebx\n\t"
      ".LFUN_0011b2a0_17:\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "movw %%bx, (%%eax)\n\t"
      "leal 0x2(%%eax), %%ebx\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "testw %%ax, %%ax\n\t"
      "jle .LFUN_0011b2a0_19\n\t"
      "movzwl %%ax, %%eax\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_0011b2a0_18:\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "pushl $0\n\t"
      "leal 0xa(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "leal -0x4(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[c11b2a0]\n\t"
      "movswl -0x4(%%ebp), %%ecx\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "addl $0x1c, %%esp\n\t"
      "addl %%ecx, %%ebx\n\t"
      "decl %%eax\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "jne .LFUN_0011b2a0_18\n\t"
      ".LFUN_0011b2a0_19:\n\t"
      "movswl -0x8(%%ebp), %%eax\n\t"
      "leal (%%eax,%%eax,4), %%edx\n\t"
      "leal (%%esi,%%edx,2), %%esi\n\t"
      "jmp .LFUN_0011b2a0_9\n\t"
      ".LFUN_0011b2a0_20:\n\t"
      "movswl 0x8(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0\n\t"
      "pushl %%ebx\n\t"
      "call *%[memset]\n\t"
      "addl $0xc, %%esp\n\t"
      "jmp .LFUN_0011b2a0_10\n\t"
      "nop\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_0011b2a0_jt:\n\t"
      ".long .LFUN_0011b2a0_3\n\t"
      ".long .LFUN_0011b2a0_4\n\t"
      ".long .LFUN_0011b2a0_5\n\t"
      ".long .LFUN_0011b2a0_6\n\t"
      ".long .LFUN_0011b2a0_7\n\t"
      ".long .LFUN_0011b2a0_8\n\t"
      ".long .LFUN_0011b2a0_15\n\t"
      ".long .LFUN_0011b2a0_14\n\t"
      ".text\n\t"
      :
      : [c11a430] "m"(b11b2a0_c11a430), [c8e0b0] "m"(b11b2a0_c8e0b0), [c11a8e0] "m"(b11b2a0_c11a8e0), [c8dff0] "m"(b11b2a0_c8dff0), [c11a700] "m"(b11b2a0_c11a700), [c11add0] "m"(b11b2a0_c11add0), [c11b2a0] "m"(b11b2a0_c11b2a0), [memset] "m"(b11b2a0_memset)
      : "memory");
}
#else
#error "FUN_0011b2a0: clang naked draft required"
#endif


/* FUN_0011b650 (0x11b650) — XBE naked draft (batch 85). */
#if defined(__clang__)
static void (*const b11b650_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b11b650_exitfn)(int) = system_exit;
static void (*const b11b650_c11b540)(packet_definition *def) = verify_packet_definition;
static void (*const b11b650_c119c50)(int *state, int buf, int buf_size) = FUN_00119c50;
static int (*const b11b650_c119cc0)(int *param_1, int param_2, short param_3, int param_4) = FUN_00119cc0;
static void (*const b11b650_c11afa0)(int param_1, int *param_2, short param_3, void *param_4, short param_5, int param_6, short *param_7) = _data_packet_encode;

__attribute__((naked, noinline))
bool FUN_0011b650(int definition __attribute__((unused)), short version __attribute__((unused)), void *data __attribute__((unused)), char *buffer __attribute__((unused)), short *buffer_size_out __attribute__((unused)), short maximum_buffer_size __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x10, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "pushl %%edi\n\t"
      "jne .LFUN_0011b650_1\n\t"
      "pushl $1\n\t"
      "pushl $0x3d\n\t"
      "pushl $0x28f498\n\t"
      "pushl $0x28f5d8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0011b650_1:\n\t"
      "movl 0x14(%%ebp), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "je .LFUN_0011b650_2\n\t"
      "movl 0x18(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_0011b650_3\n\t"
      ".LFUN_0011b650_2:\n\t"
      "pushl $1\n\t"
      "pushl $0x3e\n\t"
      "pushl $0x28f498\n\t"
      "pushl $0x28f604\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0011b650_3:\n\t"
      "movw 0x1c(%%ebp), %%bx\n\t"
      "testw %%bx, %%bx\n\t"
      "jge .LFUN_0011b650_4\n\t"
      "pushl $1\n\t"
      "pushl $0x3f\n\t"
      "pushl $0x28f498\n\t"
      "pushl $0x28f5ec\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0011b650_4:\n\t"
      "pushl %%esi\n\t"
      "call *%[c11b540]\n\t"
      "movswl %%bx, %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x10(%%ebp), %%ecx\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "call *%[c119c50]\n\t"
      "movl 0xc(%%ebp), %%ebx\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpw $-1, %%bx\n\t"
      "jne .LFUN_0011b650_5\n\t"
      "movw 0xa(%%esi), %%bx\n\t"
      ".LFUN_0011b650_5:\n\t"
      "cmpw $0, 0xa(%%esi)\n\t"
      "jle .LFUN_0011b650_6\n\t"
      "pushl $1\n\t"
      "pushl $1\n\t"
      "leal 0x1f(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x10(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movb %%bl, 0x1f(%%ebp)\n\t"
      "call *%[c119cc0]\n\t"
      "addl $0x10, %%esp\n\t"
      ".LFUN_0011b650_6:\n\t"
      "movl 0xc(%%esi), %%ecx\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "pushl $0\n\t"
      "pushl %%ecx\n\t"
      "pushl $0\n\t"
      "pushl %%edx\n\t"
      "pushl %%ebx\n\t"
      "leal -0x10(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[c11afa0]\n\t"
      "movw -0xc(%%ebp), %%cx\n\t"
      "movl 0x18(%%ebp), %%edx\n\t"
      "addl $0x1c, %%esp\n\t"
      "movw %%cx, (%%edx)\n\t"
      "movb -0x4(%%ebp), %%cl\n\t"
      "popl %%edi\n\t"
      "xorl %%eax, %%eax\n\t"
      "testb %%cl, %%cl\n\t"
      "popl %%esi\n\t"
      "sete %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b11b650_assert), [exitfn] "m"(b11b650_exitfn), [c11b540] "m"(b11b650_c11b540), [c119c50] "m"(b11b650_c119c50), [c119cc0] "m"(b11b650_c119cc0), [c11afa0] "m"(b11b650_c11afa0)
      : "memory");
}
#else
#error "FUN_0011b650: clang naked draft required"
#endif


/* FUN_0011b750 (0x11b750) — XBE naked draft (batch 85). */
#if defined(__clang__)
static void (*const b11b750_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b11b750_exitfn)(int) = system_exit;
static void (*const b11b750_c11b540)(packet_definition *def) = verify_packet_definition;
static void (*const b11b750_c11a2d0)(int *state, void *buffer, int buffer_size) = FUN_0011a2d0;
static unsigned char (*const b11b750_c11a560)(int *state) = FUN_0011a560;
static void (*const b11b750_c11b2a0)(int definition, int *decode_state, unsigned short version, unsigned short *output, short *decoded_size_out, short *field_defs, short *field_count_out) = FUN_0011b2a0;

__attribute__((naked, noinline))
bool FUN_0011b750(int definition __attribute__((unused)), int encoded_packet __attribute__((unused)), short encoded_packet_size __attribute__((unused)), int decoded_packet __attribute__((unused)), unsigned short *version_out __attribute__((unused)), short *bytes_consumed_out __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x14, %%esp\n\t"
      "pushl %%ebx\n\t"
      "movl 0xc(%%ebp), %%ebx\n\t"
      "testl %%ebx, %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "jne .LFUN_0011b750_1\n\t"
      "pushl $1\n\t"
      "pushl $0x5f\n\t"
      "pushl $0x28f498\n\t"
      "pushl $0x28f634\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0011b750_1:\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_0011b750_2\n\t"
      "pushl $1\n\t"
      "pushl $0x60\n\t"
      "pushl $0x28f498\n\t"
      "pushl $0x28f340\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0011b750_2:\n\t"
      "movw 0x10(%%ebp), %%di\n\t"
      "testw %%di, %%di\n\t"
      "jge .LFUN_0011b750_3\n\t"
      "pushl $1\n\t"
      "pushl $0x61\n\t"
      "pushl $0x28f498\n\t"
      "pushl $0x28f61c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0011b750_3:\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "pushl %%esi\n\t"
      "call *%[c11b540]\n\t"
      "movswl %%di, %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x14(%%ebp), %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c11a2d0]\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpw $0, 0xa(%%esi)\n\t"
      "jne .LFUN_0011b750_4\n\t"
      "xorl %%edi, %%edi\n\t"
      "jmp .LFUN_0011b750_5\n\t"
      ".LFUN_0011b750_4:\n\t"
      "leal -0x14(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c11a560]\n\t"
      "addl $4, %%esp\n\t"
      "movzbw %%al, %%di\n\t"
      ".LFUN_0011b750_5:\n\t"
      "cmpw 0xa(%%esi), %%di\n\t"
      "jg .LFUN_0011b750_6\n\t"
      "movl 0xc(%%esi), %%eax\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "pushl $0\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edi\n\t"
      "leal -0x14(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%esi\n\t"
      "call *%[c11b2a0]\n\t"
      "movb -0x8(%%ebp), %%al\n\t"
      "addl $0x1c, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "movb $1, %%cl\n\t"
      "je .LFUN_0011b750_7\n\t"
      ".LFUN_0011b750_6:\n\t"
      "movb -0x1(%%ebp), %%cl\n\t"
      ".LFUN_0011b750_7:\n\t"
      "movl 0x18(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_0011b750_8\n\t"
      "movw %%di, (%%eax)\n\t"
      ".LFUN_0011b750_8:\n\t"
      "movl 0x1c(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "je .LFUN_0011b750_9\n\t"
      "movw -0x10(%%ebp), %%dx\n\t"
      "movw %%dx, (%%eax)\n\t"
      ".LFUN_0011b750_9:\n\t"
      "movb %%cl, %%al\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b11b750_assert), [exitfn] "m"(b11b750_exitfn), [c11b540] "m"(b11b750_c11b540), [c11a2d0] "m"(b11b750_c11a2d0), [c11a560] "m"(b11b750_c11a560), [c11b2a0] "m"(b11b750_c11b2a0)
      : "memory");
}
#else
#error "FUN_0011b750: clang naked draft required"
#endif


/* ========================================================================
 * hashtable.c — Hash table implementation
 * ======================================================================== */

/* hashtable_new (0x11b850) — XBE naked draft (batch 87). */
#if defined(__clang__)
static void (*const b11b850_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b11b850_exitfn)(int) = system_exit;
static void (*const b11b850_c117b20)(int *table, int element_size) = array_new;

__attribute__((naked, noinline))
void hashtable_new(void *table __attribute__((unused)), short key_size __attribute__((unused)), short element_size __attribute__((unused)), float load_factor __attribute__((unused)), int param_5 __attribute__((unused)), int param_6 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "pushl %%edi\n\t"
      "jne .Lhashtable_new_1\n\t"
      "pushl $1\n\t"
      "pushl $0x29\n\t"
      "pushl $0x28f678\n\t"
      "pushl $0x28f670\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lhashtable_new_1:\n\t"
      "movw 0xc(%%ebp), %%bx\n\t"
      "testw %%bx, %%bx\n\t"
      "jg .Lhashtable_new_2\n\t"
      "pushl $1\n\t"
      "pushl $0x2a\n\t"
      "pushl $0x28f678\n\t"
      "pushl $0x28f664\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lhashtable_new_2:\n\t"
      "movw 0x10(%%ebp), %%di\n\t"
      "testw %%di, %%di\n\t"
      "jg .Lhashtable_new_3\n\t"
      "pushl $1\n\t"
      "pushl $0x2b\n\t"
      "pushl $0x28f678\n\t"
      "pushl $0x28e9ac\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lhashtable_new_3:\n\t"
      "flds 0x14(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lhashtable_new_4\n\t"
      "flds 0x14(%%ebp)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jnp .Lhashtable_new_5\n\t"
      ".Lhashtable_new_4:\n\t"
      "pushl $1\n\t"
      "pushl $0x2c\n\t"
      "pushl $0x28f678\n\t"
      "pushl $0x28f644\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lhashtable_new_5:\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "movl 0x18(%%ebp), %%ecx\n\t"
      "movl 0x1c(%%ebp), %%edx\n\t"
      "movl %%eax, 0x8(%%esi)\n\t"
      "movl %%ecx, 0x10(%%esi)\n\t"
      "movswl %%di, %%ecx\n\t"
      "movswl %%bx, %%eax\n\t"
      "addl %%ecx, %%eax\n\t"
      "movl %%edx, 0x14(%%esi)\n\t"
      "pushl %%eax\n\t"
      "leal 0x1c(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "movw %%bx, (%%esi)\n\t"
      "movw %%di, 0x2(%%esi)\n\t"
      "movw $0, 0x4(%%esi)\n\t"
      "movw $0xffff, 0x6(%%esi)\n\t"
      "call *%[c117b20]\n\t"
      "addl $8, %%esp\n\t"
      "popl %%edi\n\t"
      "movl $0, 0x18(%%esi)\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b11b850_assert), [exitfn] "m"(b11b850_exitfn), [c117b20] "m"(b11b850_c117b20)
      : "memory");
}
#else
#error "hashtable_new: clang naked draft required"
#endif


/* hashtable_set_user_data — store a user-data/callback value at offset 0x0c
 * of the hashtable header (0x11b950).
 *
 * Original source: c:\halo\SOURCE\memory\hashtable.c
 * Offset 0x0c sits between the load_factor float (0x08) and the param_5 field
 * (0x10) established by hashtable_new.  This is a simple field setter with no
 * validation.
 */
void hashtable_set_user_data(void *table, int user_data)
{
  char *t = (char *)table;
  *(int *)(t + 0x0c) = user_data;
}

/* hashtable_dispose (0x11b960) — XBE naked draft (batch 91). */
#if defined(__clang__)
static void (*const b11b960_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b11b960_exitfn)(int) = system_exit;
static void (*const b11b960_c117cf0)(int *table) = FUN_00117cf0;
static void (*const b11b960_c8ef70)(void *ptr, const char *file, int line) = debug_free;

__attribute__((naked, noinline))
void hashtable_dispose(short *table __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .Lhashtable_dispose_1\n\t"
      "cmpw $0, (%%esi)\n\t"
      "jle .Lhashtable_dispose_1\n\t"
      "cmpw $0, 0x2(%%esi)\n\t"
      "jle .Lhashtable_dispose_1\n\t"
      "flds 0x8(%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lhashtable_dispose_1\n\t"
      "flds 0x8(%%esi)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .Lhashtable_dispose_1\n\t"
      "movw 0x6(%%esi), %%cx\n\t"
      "cmpw $-1, %%cx\n\t"
      "je .Lhashtable_dispose_2\n\t"
      "movl $1, %%eax\n\t"
      "shll %%cl, %%eax\n\t"
      "cmpl 0x20(%%esi), %%eax\n\t"
      "je .Lhashtable_dispose_2\n\t"
      ".Lhashtable_dispose_1:\n\t"
      "pushl $1\n\t"
      "pushl $0x6e\n\t"
      "pushl $0x28f678\n\t"
      "pushl $0x28f69c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lhashtable_dispose_2:\n\t"
      "leal 0x1c(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c117cf0]\n\t"
      "movl 0x18(%%esi), %%esi\n\t"
      "addl $4, %%esp\n\t"
      "testl %%esi, %%esi\n\t"
      "je .Lhashtable_dispose_3\n\t"
      "pushl $0x74\n\t"
      "pushl $0x28f678\n\t"
      "pushl %%esi\n\t"
      "call *%[c8ef70]\n\t"
      "addl $0xc, %%esp\n\t"
      ".Lhashtable_dispose_3:\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b11b960_assert), [exitfn] "m"(b11b960_exitfn), [c117cf0] "m"(b11b960_c117cf0), [c8ef70] "m"(b11b960_c8ef70)
      : "memory");
}
#else
#error "hashtable_dispose: clang naked draft required"
#endif


/* FUN_0011ba00 (0x11ba00) — XBE naked draft (batch 95). */
#if defined(__clang__)


__attribute__((naked, noinline))
int FUN_0011ba00(unsigned char *key __attribute__((unused)), unsigned int key_size __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "xorl %%eax, %%eax\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "testl %%edx, %%edx\n\t"
      "jbe .LFUN_0011ba00_3\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "pushl %%edi\n\t"
      ".LFUN_0011ba00_1:\n\t"
      "cmpw $0xf, %%cx\n\t"
      "jne .LFUN_0011ba00_2\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "subl $0xf, %%edx\n\t"
      ".LFUN_0011ba00_2:\n\t"
      "movzbw (%%esi), %%bx\n\t"
      "movswl %%cx, %%edi\n\t"
      "movswl 0x3220d4(,%%edi,2), %%edi\n\t"
      "imulw %%bx, %%di\n\t"
      "addl %%edi, %%eax\n\t"
      "incl %%ecx\n\t"
      "movswl %%cx, %%edi\n\t"
      "incl %%esi\n\t"
      "cmpl %%edx, %%edi\n\t"
      "jb .LFUN_0011ba00_1\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      ".LFUN_0011ba00_3:\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "FUN_0011ba00: clang naked draft required"
#endif


/* FUN_0011ba50 (0x11ba50) — XBE naked draft (batch 84). */
#if defined(__clang__)
static int (*const b11ba50_c11ba00)(unsigned char *key, unsigned int key_size) = (void *)FUN_0011ba00;
static int (*const b11ba50_c117ee0)(int *array, int index, int element_size) = FUN_00117ee0;
static int (*const b11ba50_c8da40)(const void *a, const void *b, int size) = csmemcmp;

__attribute__((naked, noinline))
int FUN_0011ba50(short *table __attribute__((unused)), void *key __attribute__((unused)), unsigned short *slot_index_out __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "movl 0x10(%%esi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "movl $0, -0x4(%%ebp)\n\t"
      "je .LFUN_0011ba50_1\n\t"
      "pushl %%ecx\n\t"
      "movl 0xc(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%%eax\n\t"
      "jmp .LFUN_0011ba50_2\n\t"
      ".LFUN_0011ba50_1:\n\t"
      "movswl (%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c11ba00]\n\t"
      ".LFUN_0011ba50_2:\n\t"
      "addl $8, %%esp\n\t"
      "pushl %%ebx\n\t"
      "movl 0x18(%%esi), %%ebx\n\t"
      "pushl %%edi\n\t"
      "xorl %%edi, %%edi\n\t"
      "movw 0x20(%%esi), %%di\n\t"
      "decw %%di\n\t"
      "movswl %%ax, %%eax\n\t"
      "movl $1, %%edx\n\t"
      "andl %%eax, %%edi\n\t"
      "movswl %%di, %%eax\n\t"
      "movl %%eax, %%ecx\n\t"
      "andl $0x1f, %%ecx\n\t"
      "shll %%cl, %%edx\n\t"
      "movl %%eax, %%ecx\n\t"
      "sarl $5, %%ecx\n\t"
      "testl %%edx, (%%ebx,%%ecx,4)\n\t"
      "je .LFUN_0011ba50_6\n\t"
      "leal (%%ebx), %%ebx\n\t"
      ".LFUN_0011ba50_3:\n\t"
      "movw -0x4(%%ebp), %%dx\n\t"
      "cmpw 0x4(%%esi), %%dx\n\t"
      "jge .LFUN_0011ba50_8\n\t"
      "movl 0x14(%%esi), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "je .LFUN_0011ba50_4\n\t"
      "movswl 0x2(%%esi), %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "leal 0x1c(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c117ee0]\n\t"
      "movl 0xc(%%esi), %%ecx\n\t"
      "addl $0xc, %%esp\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *0x14(%%esi)\n\t"
      "addl $0xc, %%esp\n\t"
      "movzbl %%al, %%eax\n\t"
      "jmp .LFUN_0011ba50_5\n\t"
      ".LFUN_0011ba50_4:\n\t"
      "movswl (%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "movswl 0x2(%%esi), %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "leal 0x1c(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c117ee0]\n\t"
      "addl $0xc, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[c8da40]\n\t"
      "addl $0xc, %%esp\n\t"
      "negl %%eax\n\t"
      "sbbl %%eax, %%eax\n\t"
      "incl %%eax\n\t"
      ".LFUN_0011ba50_5:\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_0011ba50_7\n\t"
      "movl -0x4(%%ebp), %%ebx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x20(%%esi), %%cx\n\t"
      "incl %%edi\n\t"
      "decw %%cx\n\t"
      "movl $1, %%edx\n\t"
      "andl %%ecx, %%edi\n\t"
      "movswl %%di, %%eax\n\t"
      "movl %%eax, %%ecx\n\t"
      "andl $0x1f, %%ecx\n\t"
      "incl %%ebx\n\t"
      "shll %%cl, %%edx\n\t"
      "movl %%eax, %%ecx\n\t"
      "movl %%ebx, -0x4(%%ebp)\n\t"
      "movl 0x18(%%esi), %%ebx\n\t"
      "sarl $5, %%ecx\n\t"
      "testl %%edx, (%%ebx,%%ecx,4)\n\t"
      "jne .LFUN_0011ba50_3\n\t"
      ".LFUN_0011ba50_6:\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "movw %%di, (%%edx)\n\t"
      "popl %%edi\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0011ba50_7:\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "movw %%di, (%%ecx)\n\t"
      "popl %%edi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0011ba50_8:\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "movw %%di, (%%eax)\n\t"
      "popl %%edi\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c11ba00] "m"(b11ba50_c11ba00), [c117ee0] "m"(b11ba50_c117ee0), [c8da40] "m"(b11ba50_c8da40)
      : "memory");
}
#else
#error "FUN_0011ba50: clang naked draft required"
#endif


/* FUN_0011bb70 (0x11bb70) — XBE naked draft (batch 88). */
#if defined(__clang__)
static void (*const b11bb70_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b11bb70_exitfn)(int) = system_exit;
static int (*const b11bb70_c11ba50)(short *table, void *key, unsigned short *slot_index_out) = FUN_0011ba50;
static int (*const b11bb70_c117ee0)(int *array, int index, int element_size) = FUN_00117ee0;

__attribute__((naked, noinline))
int FUN_0011bb70(short *table __attribute__((unused)), void *key __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "pushl %%edi\n\t"
      "xorl %%edi, %%edi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_0011bb70_1\n\t"
      "cmpw %%di, (%%esi)\n\t"
      "jle .LFUN_0011bb70_1\n\t"
      "cmpw %%di, 0x2(%%esi)\n\t"
      "jle .LFUN_0011bb70_1\n\t"
      "flds 0x8(%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_0011bb70_1\n\t"
      "flds 0x8(%%esi)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .LFUN_0011bb70_1\n\t"
      "movw 0x6(%%esi), %%cx\n\t"
      "cmpw $-1, %%cx\n\t"
      "je .LFUN_0011bb70_2\n\t"
      "movl $1, %%eax\n\t"
      "shll %%cl, %%eax\n\t"
      "cmpl 0x20(%%esi), %%eax\n\t"
      "je .LFUN_0011bb70_2\n\t"
      ".LFUN_0011bb70_1:\n\t"
      "pushl $1\n\t"
      "pushl $0x4d\n\t"
      "pushl $0x28f678\n\t"
      "pushl $0x28f69c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0011bb70_2:\n\t"
      "cmpw $0, 0x4(%%esi)\n\t"
      "je .LFUN_0011bb70_3\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "leal 0xa(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c11ba50]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0011bb70_3\n\t"
      "movswl 0x2(%%esi), %%eax\n\t"
      "movswl 0xa(%%ebp), %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "leal 0x1c(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c117ee0]\n\t"
      "movswl (%%esi), %%ecx\n\t"
      "addl $0xc, %%esp\n\t"
      "popl %%edi\n\t"
      "addl %%ecx, %%eax\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0011bb70_3:\n\t"
      "movl %%edi, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b11bb70_assert), [exitfn] "m"(b11bb70_exitfn), [c11ba50] "m"(b11bb70_c11ba50), [c117ee0] "m"(b11bb70_c117ee0)
      : "memory");
}
#else
#error "FUN_0011bb70: clang naked draft required"
#endif


/* FUN_0011bc20 (0x11bc20) — XBE naked draft (batch 82). */
#if defined(__clang__)
static void (*const b11bc20_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b11bc20_exitfn)(int) = system_exit;
static int (*const b11bc20_c11ba50)(short *table, void *key, unsigned short *slot_index_out) = FUN_0011ba50;
static int (*const b11bc20_c117ee0)(int *array, int index, int element_size) = FUN_00117ee0;
static int (*const b11bc20_c11ba00)(unsigned char *key, unsigned int key_size) = (void *)FUN_0011ba00;
static void * (*const b11bc20_c8e0b0)(void *destination, void *source, size_t size) = csmemcpy;

__attribute__((naked, noinline))
void FUN_0011bc20(short *table __attribute__((unused)), void *key __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "pushl %%edi\n\t"
      "je .LFUN_0011bc20_1\n\t"
      "cmpw $0, (%%esi)\n\t"
      "jle .LFUN_0011bc20_1\n\t"
      "cmpw $0, 0x2(%%esi)\n\t"
      "jle .LFUN_0011bc20_1\n\t"
      "flds 0x8(%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_0011bc20_1\n\t"
      "flds 0x8(%%esi)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .LFUN_0011bc20_1\n\t"
      "movw 0x6(%%esi), %%cx\n\t"
      "cmpw $-1, %%cx\n\t"
      "je .LFUN_0011bc20_2\n\t"
      "movl $1, %%eax\n\t"
      "shll %%cl, %%eax\n\t"
      "cmpl 0x20(%%esi), %%eax\n\t"
      "je .LFUN_0011bc20_2\n\t"
      ".LFUN_0011bc20_1:\n\t"
      "pushl $1\n\t"
      "pushl $0xc3\n\t"
      "pushl $0x28f678\n\t"
      "pushl $0x28f69c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0011bc20_2:\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .LFUN_0011bc20_3\n\t"
      "pushl $1\n\t"
      "pushl $0xc4\n\t"
      "pushl $0x28f678\n\t"
      "pushl $0x265ba4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0011bc20_3:\n\t"
      "leal 0x8(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edi\n\t"
      "call *%[c11ba50]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0011bc20_12\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "xorl %%edi, %%edi\n\t"
      "movw 0x20(%%esi), %%di\n\t"
      "decw %%di\n\t"
      "incl %%edx\n\t"
      "pushl %%ebx\n\t"
      "movl $1, %%eax\n\t"
      "andl %%edx, %%edi\n\t"
      "movl 0x18(%%esi), %%edx\n\t"
      "movswl %%di, %%ebx\n\t"
      "movl %%ebx, %%ecx\n\t"
      "andl $0x1f, %%ecx\n\t"
      "shll %%cl, %%eax\n\t"
      "movl %%ebx, %%ecx\n\t"
      "sarl $5, %%ecx\n\t"
      "testl %%eax, (%%edx,%%ecx,4)\n\t"
      "je .LFUN_0011bc20_11\n\t"
      "leal (%%ebx), %%ebx\n\t"
      ".LFUN_0011bc20_4:\n\t"
      "movswl 0x2(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal 0x1c(%%esi), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "call *%[c117ee0]\n\t"
      "movl 0x10(%%esi), %%ecx\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .LFUN_0011bc20_5\n\t"
      "movl 0xc(%%esi), %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%edx\n\t"
      "call *%%ecx\n\t"
      "jmp .LFUN_0011bc20_6\n\t"
      ".LFUN_0011bc20_5:\n\t"
      "movswl (%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "call *%[c11ba00]\n\t"
      ".LFUN_0011bc20_6:\n\t"
      "movswl %%ax, %%ecx\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x20(%%esi), %%ax\n\t"
      "addl $8, %%esp\n\t"
      "decw %%ax\n\t"
      "andl %%ecx, %%eax\n\t"
      "cmpw %%di, %%ax\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "jge .LFUN_0011bc20_8\n\t"
      "cmpw %%ax, %%cx\n\t"
      "jl .LFUN_0011bc20_7\n\t"
      "cmpw %%di, %%cx\n\t"
      "jl .LFUN_0011bc20_9\n\t"
      ".LFUN_0011bc20_7:\n\t"
      "cmpw %%di, %%ax\n\t"
      ".LFUN_0011bc20_8:\n\t"
      "jle .LFUN_0011bc20_10\n\t"
      "cmpw %%ax, %%cx\n\t"
      "jge .LFUN_0011bc20_9\n\t"
      "cmpw %%di, %%cx\n\t"
      "jge .LFUN_0011bc20_10\n\t"
      ".LFUN_0011bc20_9:\n\t"
      "movl 0x1c(%%esi), %%edx\n\t"
      "movswl 0x2(%%esi), %%ecx\n\t"
      "leal 0x1c(%%esi), %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "call *%[c117ee0]\n\t"
      "movswl 0x2(%%esi), %%edx\n\t"
      "addl $0xc, %%esp\n\t"
      "pushl %%eax\n\t"
      "movswl 0x8(%%ebp), %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "leal 0x1c(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c117ee0]\n\t"
      "addl $0xc, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[c8e0b0]\n\t"
      "addl $0xc, %%esp\n\t"
      "movl %%edi, 0x8(%%ebp)\n\t"
      ".LFUN_0011bc20_10:\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x20(%%esi), %%cx\n\t"
      "decw %%cx\n\t"
      "incl %%edi\n\t"
      "movl $1, %%edx\n\t"
      "andl %%ecx, %%edi\n\t"
      "movswl %%di, %%ebx\n\t"
      "movl %%ebx, %%ecx\n\t"
      "andl $0x1f, %%ecx\n\t"
      "shll %%cl, %%edx\n\t"
      "movl 0x18(%%esi), %%ecx\n\t"
      "movl %%ebx, %%eax\n\t"
      "sarl $5, %%eax\n\t"
      "testl %%edx, (%%ecx,%%eax,4)\n\t"
      "jne .LFUN_0011bc20_4\n\t"
      ".LFUN_0011bc20_11:\n\t"
      "movswl 0x8(%%ebp), %%ecx\n\t"
      "movl 0x18(%%esi), %%eax\n\t"
      "movl %%ecx, %%edx\n\t"
      "sarl $5, %%edx\n\t"
      "leal (%%eax,%%edx,4), %%eax\n\t"
      "andl $0x1f, %%ecx\n\t"
      "movl $1, %%edx\n\t"
      "shll %%cl, %%edx\n\t"
      "movl (%%eax), %%ecx\n\t"
      "popl %%ebx\n\t"
      "popl %%edi\n\t"
      "notl %%edx\n\t"
      "andl %%edx, %%ecx\n\t"
      "movl %%ecx, (%%eax)\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0011bc20_12:\n\t"
      "pushl $1\n\t"
      "pushl $0xe1\n\t"
      "pushl $0x28f678\n\t"
      "pushl $0x28f6b4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b11bc20_assert), [exitfn] "m"(b11bc20_exitfn), [c11ba50] "m"(b11bc20_c11ba50), [c117ee0] "m"(b11bc20_c117ee0), [c11ba00] "m"(b11bc20_c11ba00), [c8e0b0] "m"(b11bc20_c8e0b0)
      : "memory");
}
#else
#error "FUN_0011bc20: clang naked draft required"
#endif


/* FUN_0011be10 (0x11be10) — XBE naked draft (batch 89). */
#if defined(__clang__)
static int (*const b11be10_c11ba50)(short *table, void *key, unsigned short *slot_index_out) = FUN_0011ba50;
static void (*const b11be10_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b11be10_exitfn)(int) = system_exit;
static int (*const b11be10_c117ee0)(int *array, int index, int element_size) = FUN_00117ee0;
static void * (*const b11be10_c8e0b0)(void *destination, void *source, size_t size) = csmemcpy;

__attribute__((naked, noinline))
int FUN_0011be10(short *table __attribute__((unused)), void *key __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl %%eax, %%esi\n\t"
      "leal -0x4(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "xorl %%edi, %%edi\n\t"
      "call *%[c11ba50]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0011be10_1\n\t"
      "pushl $1\n\t"
      "pushl $0xf1\n\t"
      "pushl $0x28f678\n\t"
      "pushl $0x28f6d4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "movl %%edi, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0011be10_1:\n\t"
      "movswl 0x2(%%esi), %%edx\n\t"
      "movswl -0x4(%%ebp), %%edi\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edx\n\t"
      "leal 0x1c(%%esi), %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[c117ee0]\n\t"
      "movswl (%%esi), %%ecx\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "pushl %%ecx\n\t"
      "movl %%eax, %%ebx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ebx\n\t"
      "call *%[c8e0b0]\n\t"
      "movl 0x18(%%esi), %%ecx\n\t"
      "movl %%edi, %%eax\n\t"
      "sarl $5, %%eax\n\t"
      "leal (%%ecx,%%eax,4), %%eax\n\t"
      "movl %%edi, %%ecx\n\t"
      "movl (%%eax), %%edi\n\t"
      "andl $0x1f, %%ecx\n\t"
      "movl $1, %%edx\n\t"
      "shll %%cl, %%edx\n\t"
      "addl $0x18, %%esp\n\t"
      "orl %%edx, %%edi\n\t"
      "movl %%edi, (%%eax)\n\t"
      "movswl (%%esi), %%eax\n\t"
      "addl %%ebx, %%eax\n\t"
      "incw 0x4(%%esi)\n\t"
      "popl %%ebx\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c11ba50] "m"(b11be10_c11ba50), [assert] "m"(b11be10_assert), [exitfn] "m"(b11be10_exitfn), [c117ee0] "m"(b11be10_c117ee0), [c8e0b0] "m"(b11be10_c8e0b0)
      : "memory");
}
#else
#error "FUN_0011be10: clang naked draft required"
#endif


/* FUN_0011beb0 (0x11beb0) — XBE naked draft (batch 81). */
#if defined(__clang__)
static void (*const b11beb0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b11beb0_exitfn)(int) = system_exit;
static void * (*const b11beb0_c8ee60)(uint32_t size, bool zero, const char *file, int line) = debug_malloc;
static void (*const b11beb0_c117b20)(int *table, int element_size) = array_new;
static int (*const b11beb0_c117b90)(int *array, int new_count) = array_resize;
static void *(*const b11beb0_memset)(void *, int, unsigned int) = csmemset;
static int (*const b11beb0_c117ee0)(int *array, int index, int element_size) = FUN_00117ee0;
static int (*const b11beb0_c11be10)(short *table, void *key) = FUN_0011be10;
static void * (*const b11beb0_c8e0b0)(void *destination, void *source, size_t size) = csmemcpy;
static void (*const b11beb0_c8ef70)(void *ptr, const char *file, int line) = debug_free;
static void (*const b11beb0_c117cf0)(int *table) = FUN_00117cf0;

__attribute__((naked, noinline))
int FUN_0011beb0(short *table __attribute__((unused)), short growth_bits __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x18, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "movw 0x4(%%esi), %%ax\n\t"
      "movl 0x18(%%esi), %%edx\n\t"
      "movw %%ax, -0xc(%%ebp)\n\t"
      "leal 0x1c(%%esi), %%eax\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "cmpw $0, (%%esi)\n\t"
      "movw 0x6(%%esi), %%cx\n\t"
      "movl %%eax, 0x8(%%ebp)\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      "movl (%%eax), %%edx\n\t"
      "movl %%edx, -0x18(%%ebp)\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "pushl %%edi\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "movl %%edx, -0x14(%%ebp)\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "jle .LFUN_0011beb0_1\n\t"
      "cmpw $0, 0x2(%%esi)\n\t"
      "jle .LFUN_0011beb0_1\n\t"
      "flds 0x8(%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_0011beb0_1\n\t"
      "flds 0x8(%%esi)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .LFUN_0011beb0_1\n\t"
      "cmpw $-1, %%cx\n\t"
      "je .LFUN_0011beb0_2\n\t"
      "movl 0x20(%%esi), %%eax\n\t"
      "movl $1, %%edx\n\t"
      "shll %%cl, %%edx\n\t"
      "cmpl %%eax, %%edx\n\t"
      "je .LFUN_0011beb0_2\n\t"
      ".LFUN_0011beb0_1:\n\t"
      "pushl $1\n\t"
      "pushl $0x86\n\t"
      "pushl $0x28f678\n\t"
      "pushl $0x28f69c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0011beb0_2:\n\t"
      "movw 0xc(%%ebp), %%di\n\t"
      "testw %%di, %%di\n\t"
      "jg .LFUN_0011beb0_3\n\t"
      "pushl $1\n\t"
      "pushl $0x87\n\t"
      "pushl $0x28f678\n\t"
      "pushl $0x28f724\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0011beb0_3:\n\t"
      "movswl 0x6(%%esi), %%ecx\n\t"
      "movswl %%di, %%eax\n\t"
      "addl %%ecx, %%eax\n\t"
      "cmpl $0x10, %%eax\n\t"
      "jl .LFUN_0011beb0_4\n\t"
      "pushl $1\n\t"
      "pushl $0x88\n\t"
      "pushl $0x28f678\n\t"
      "pushl $0x28f6f8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0011beb0_4:\n\t"
      "addw %%di, 0x6(%%esi)\n\t"
      "movw 0x6(%%esi), %%cx\n\t"
      "movl $1, %%eax\n\t"
      "shll %%cl, %%eax\n\t"
      "pushl $0x8f\n\t"
      "pushl $0x28f678\n\t"
      "pushl $0\n\t"
      "movswl %%ax, %%ebx\n\t"
      "leal 0x1f(%%ebx), %%edi\n\t"
      "sarl $5, %%edi\n\t"
      "shll $2, %%edi\n\t"
      "pushl %%edi\n\t"
      "movw $0, 0x4(%%esi)\n\t"
      "call *%[c8ee60]\n\t"
      "addl $0x10, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%eax, 0x18(%%esi)\n\t"
      "je .LFUN_0011beb0_11\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl (%%eax), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c117b20]\n\t"
      "pushl %%ebx\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "pushl %%ebx\n\t"
      "call *%[c117b90]\n\t"
      "addl $0x10, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0011beb0_10\n\t"
      "movl 0x18(%%esi), %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "call *%[memset]\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "xorl %%edi, %%edi\n\t"
      "testl %%eax, %%eax\n\t"
      "jle .LFUN_0011beb0_7\n\t"
      "xorl %%eax, %%eax\n\t"
      "movl %%edi, %%edi\n\t"
      ".LFUN_0011beb0_5:\n\t"
      "movl -0x4(%%ebp), %%ebx\n\t"
      "movl %%eax, %%ecx\n\t"
      "andl $0x1f, %%ecx\n\t"
      "movl $1, %%edx\n\t"
      "shll %%cl, %%edx\n\t"
      "movl %%eax, %%ecx\n\t"
      "sarl $5, %%ecx\n\t"
      "testl %%edx, (%%ebx,%%ecx,4)\n\t"
      "je .LFUN_0011beb0_6\n\t"
      "movl -0x18(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "leal -0x18(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c117ee0]\n\t"
      "movswl 0x2(%%esi), %%ecx\n\t"
      "movswl (%%esi), %%edx\n\t"
      "addl $0xc, %%esp\n\t"
      "pushl %%ecx\n\t"
      "addl %%eax, %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "movl %%esi, %%eax\n\t"
      "call *%[c11be10]\n\t"
      "addl $4, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[c8e0b0]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_0011beb0_6:\n\t"
      "movl -0x14(%%ebp), %%ecx\n\t"
      "incl %%edi\n\t"
      "movswl %%di, %%eax\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jl .LFUN_0011beb0_5\n\t"
      "jmp .LFUN_0011beb0_8\n\t"
      ".LFUN_0011beb0_7:\n\t"
      "movl -0x4(%%ebp), %%ebx\n\t"
      ".LFUN_0011beb0_8:\n\t"
      "testl %%ebx, %%ebx\n\t"
      "je .LFUN_0011beb0_9\n\t"
      "pushl $0xa8\n\t"
      "pushl $0x28f678\n\t"
      "pushl %%ebx\n\t"
      "call *%[c8ef70]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_0011beb0_9:\n\t"
      "leal -0x18(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c117cf0]\n\t"
      "addl $4, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0011beb0_10:\n\t"
      "movl 0x18(%%esi), %%ecx\n\t"
      "pushl $0xb0\n\t"
      "pushl $0x28f678\n\t"
      "pushl %%ecx\n\t"
      "call *%[c8ef70]\n\t"
      "addl $0xc, %%esp\n\t"
      "jmp .LFUN_0011beb0_12\n\t"
      ".LFUN_0011beb0_11:\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      ".LFUN_0011beb0_12:\n\t"
      "movw -0x8(%%ebp), %%dx\n\t"
      "movw -0xc(%%ebp), %%ax\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movw %%dx, 0x6(%%esi)\n\t"
      "movl -0x18(%%ebp), %%edx\n\t"
      "movw %%ax, 0x4(%%esi)\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "movl %%ecx, 0x18(%%esi)\n\t"
      "movl -0x10(%%ebp), %%ecx\n\t"
      "movl %%edx, (%%ebx)\n\t"
      "popl %%edi\n\t"
      "movl %%eax, 0x4(%%ebx)\n\t"
      "popl %%esi\n\t"
      "movl %%ecx, 0x8(%%ebx)\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b11beb0_assert), [exitfn] "m"(b11beb0_exitfn), [c8ee60] "m"(b11beb0_c8ee60), [c117b20] "m"(b11beb0_c117b20), [c117b90] "m"(b11beb0_c117b90), [memset] "m"(b11beb0_memset), [c117ee0] "m"(b11beb0_c117ee0), [c11be10] "m"(b11beb0_c11be10), [c8e0b0] "m"(b11beb0_c8e0b0), [c8ef70] "m"(b11beb0_c8ef70), [c117cf0] "m"(b11beb0_c117cf0)
      : "memory");
}
#else
#error "FUN_0011beb0: clang naked draft required"
#endif


/* FUN_0011c0f0 (0x11c0f0) — XBE naked draft (batch 88). */
#if defined(__clang__)
static void (*const b11c0f0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b11c0f0_exitfn)(int) = system_exit;
static int (*const b11c0f0_c11beb0)(short *table, short growth_bits) = FUN_0011beb0;
static int (*const b11c0f0_c11be10)(short *table, void *key) = FUN_0011be10;

__attribute__((naked, noinline))
int FUN_0011c0f0(short *table __attribute__((unused)), void *key __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_0011c0f0_1\n\t"
      "cmpw $0, (%%esi)\n\t"
      "jle .LFUN_0011c0f0_1\n\t"
      "cmpw $0, 0x2(%%esi)\n\t"
      "jle .LFUN_0011c0f0_1\n\t"
      "flds 0x8(%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_0011c0f0_1\n\t"
      "flds 0x8(%%esi)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .LFUN_0011c0f0_1\n\t"
      "movw 0x6(%%esi), %%cx\n\t"
      "cmpw $-1, %%cx\n\t"
      "je .LFUN_0011c0f0_2\n\t"
      "movl $1, %%eax\n\t"
      "shll %%cl, %%eax\n\t"
      "cmpl 0x20(%%esi), %%eax\n\t"
      "je .LFUN_0011c0f0_2\n\t"
      ".LFUN_0011c0f0_1:\n\t"
      "pushl $1\n\t"
      "pushl $0x5d\n\t"
      "pushl $0x28f678\n\t"
      "pushl $0x28f69c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0011c0f0_2:\n\t"
      "movw 0x6(%%esi), %%cx\n\t"
      "cmpw $-1, %%cx\n\t"
      "je .LFUN_0011c0f0_3\n\t"
      "movswl 0x4(%%esi), %%edx\n\t"
      "movl %%edx, 0x8(%%ebp)\n\t"
      "fildl 0x8(%%ebp)\n\t"
      "fildl 0x20(%%esi)\n\t"
      "fmuls 0x8(%%esi)\n\t"
      "fcompp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .LFUN_0011c0f0_4\n\t"
      ".LFUN_0011c0f0_3:\n\t"
      "xorl %%eax, %%eax\n\t"
      "cmpw $-1, %%cx\n\t"
      "sete %%al\n\t"
      "incl %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[c11beb0]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_0011c0f0_4\n\t"
      "xorl %%eax, %%eax\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0011c0f0_4:\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl %%esi, %%eax\n\t"
      "call *%[c11be10]\n\t"
      "addl $4, %%esp\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b11c0f0_assert), [exitfn] "m"(b11c0f0_exitfn), [c11beb0] "m"(b11c0f0_c11beb0), [c11be10] "m"(b11c0f0_c11be10)
      : "memory");
}
#else
#error "FUN_0011c0f0: clang naked draft required"
#endif


/* ========================================================================
 * lra_cache.c — LRU/LRA cache implementation
 * Original source: c:\halo\SOURCE\memory\lra_cache.c
 *
 * Cache struct (0x3c bytes):
 *   +0x00 char[0x20]  name (null-terminated, max 0x1f chars)
 *   +0x20 int         size (total buffer size)
 *   +0x24 void*       base_address (buffer pointer)
 *   +0x28 byte        owns_buffer
 *   +0x2c void*       head_block
 *   +0x30 void(*)(void*,int)  lock_proc
 *   +0x34 void(*)(void*)      unlock_proc
 *   +0x38 int         magic = 0x6c726163 ("lrac")
 *
 * Block header (0x10 bytes, prepended to user data):
 *   +0x00 int         user_data
 *   +0x04 int         flags (bit 0 = in_use, bit 1 = freed/unlocked)
 *   +0x08 int         size
 *   +0x0c void*       next_block
 * ======================================================================== */

/* FUN_0011c1b0 (0x11c1b0) — readable C lift. */
int FUN_0011c1b0(int cache)
{
  int *inner = *(int **)((char *)cache + 0x2c);
  if (inner == 0) {
    return 0;
  }
  if (inner[3] == 0) {
    return 0;
  }
  return 1;
}

/* lra_cache_default_lock — default lock callback (0x11c1d0). */
void FUN_0011c1d0(int *ptr, int user_data)
{
  *ptr = user_data;
}

/* lra_cache_default_unlock — default unlock callback (0x11c1e0). */
void FUN_0011c1e0(int *ptr)
{
  *ptr = 0;
}

/* FUN_0011c210 (0x11c210) — XBE naked draft (batch 92). */
#if defined(__clang__)
static char * (*const b11c210_c8d9d0)(char *buffer, const char *format, ...) = csprintf;
static void (*const b11c210_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b11c210_exitfn)(int) = system_exit;
static void (*const b11c210_c11c282)(void) = (void (*)(void))FUN_0011c290;

__attribute__((naked, noinline))
void FUN_0011c210(int cache __attribute__((unused)), int block __attribute__((unused)))
{
  __asm__ volatile(
      "movl 0x4(%%esi), %%eax\n\t"
      "andl $0xfffffffc, %%eax\n\t"
      "cmpl $0x41626c68, %%eax\n\t"
      "pushl %%edi\n\t"
      "jne .LFUN_0011c210_1\n\t"
      "movl 0x8(%%esi), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "jl .LFUN_0011c210_1\n\t"
      "movl 0x20(%%ebx), %%edi\n\t"
      "cmpl %%edi, %%ecx\n\t"
      "jge .LFUN_0011c210_1\n\t"
      "movl 0x24(%%ebx), %%edx\n\t"
      "movl %%esi, %%eax\n\t"
      "subl %%edx, %%eax\n\t"
      "js .LFUN_0011c210_1\n\t"
      "addl %%eax, %%ecx\n\t"
      "cmpl %%edi, %%ecx\n\t"
      "jg .LFUN_0011c210_1\n\t"
      "movl 0xc(%%esi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_0011c210_10000\n\t"
      "subl %%edx, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jl .LFUN_0011c210_1\n\t"
      "addl $0x10, %%eax\n\t"
      "cmpl %%edi, %%eax\n\t"
      "jbe .LFUN_0011c210_2\n\t"
      ".LFUN_0011c210_1:\n\t"
      "pushl $1\n\t"
      "pushl $0x18e\n\t"
      "pushl $0x28f768\n\t"
      "pushl %%esi\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ebx\n\t"
      "pushl $0x28f734\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x14, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0011c210_2:\n\t"
      "popl %%edi\n\t"
      "ret\n\t"
      ".LFUN_0011c210_10000:\n\t"
      "jmp *%[c11c282]\n\t"
      :
      : [c8d9d0] "m"(b11c210_c8d9d0), [assert] "m"(b11c210_assert), [exitfn] "m"(b11c210_exitfn), [c11c282] "m"(b11c210_c11c282)
      : "memory");
}
#else
#error "FUN_0011c210: clang naked draft required"
#endif


/* FUN_0011c290 (0x11c290) — XBE naked draft (batch 93). */
#if defined(__clang__)
static void (*const b11c290_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b11c290_exitfn)(int) = system_exit;
static char * (*const b11c290_c8d9d0)(char *buffer, const char *format, ...) = csprintf;
static void (*const b11c290_c11c210)(int cache, int block) = FUN_0011c210;

__attribute__((naked, noinline))
void FUN_0011c290(int cache __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebx\n\t"
      "movl %%eax, %%ebx\n\t"
      "testl %%ebx, %%ebx\n\t"
      "pushl %%esi\n\t"
      "jne .LFUN_0011c290_1\n\t"
      "pushl $1\n\t"
      "pushl $0x198\n\t"
      "pushl $0x28f768\n\t"
      "pushl $0x28f7b4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0011c290_1:\n\t"
      "cmpl $0x6c726163, 0x38(%%ebx)\n\t"
      "jne .LFUN_0011c290_2\n\t"
      "movl 0x24(%%ebx), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_0011c290_2\n\t"
      "movl 0x20(%%ebx), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jge .LFUN_0011c290_3\n\t"
      ".LFUN_0011c290_2:\n\t"
      "pushl $1\n\t"
      "pushl $0x1a2\n\t"
      "pushl $0x28f768\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ebx\n\t"
      "pushl $0x28f78c\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x10, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0011c290_3:\n\t"
      "movl 0x2c(%%ebx), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_0011c290_4\n\t"
      "call *%[c11c210]\n\t"
      ".LFUN_0011c290_4:\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b11c290_assert), [exitfn] "m"(b11c290_exitfn), [c8d9d0] "m"(b11c290_c8d9d0), [c11c210] "m"(b11c290_c11c210)
      : "memory");
}
#else
#error "FUN_0011c290: clang naked draft required"
#endif


/* FUN_0011c310 (0x11c310) — XBE naked draft (batch 85). */
#if defined(__clang__)
static void * (*const b11c310_c8ee60)(uint32_t size, bool zero, const char *file, int line) = debug_malloc;
static void (*const b11c310_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b11c310_exitfn)(int) = system_exit;
static void *(*const b11c310_memset)(void *, int, unsigned int) = csmemset;
static void * (*const b11c310_c8de70)(char *destination, const char *source, size_t size) = csstrncpy;
static void (*const b11c310_c11c290)(int cache) = FUN_0011c290;
static void (*const b11c310_c8ef70)(void *ptr, const char *file, int line) = debug_free;

__attribute__((naked, noinline))
int FUN_0011c310(const char *name __attribute__((unused)), int size __attribute__((unused)), void (*lock_proc)(void * __attribute__((unused)), int), void (*unlock_proc)(void *) __attribute__((unused)), void *base_address __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl $0x56\n\t"
      "pushl $0x28f768\n\t"
      "pushl $0\n\t"
      "pushl $0x3c\n\t"
      "call *%[c8ee60]\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "addl $0x10, %%esp\n\t"
      "testl %%edi, %%edi\n\t"
      "movl %%eax, %%esi\n\t"
      "jge .LFUN_0011c310_1\n\t"
      "pushl $1\n\t"
      "pushl $0x58\n\t"
      "pushl $0x28f768\n\t"
      "pushl $0x267a80\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0011c310_1:\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_0011c310_2\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_0011c310_3\n\t"
      ".LFUN_0011c310_2:\n\t"
      "movl $0x11c1d0, 0x10(%%ebp)\n\t"
      "movl $0x11c1e0, 0x14(%%ebp)\n\t"
      ".LFUN_0011c310_3:\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_0011c310_6\n\t"
      "movl 0x18(%%ebp), %%ebx\n\t"
      "testl %%ebx, %%ebx\n\t"
      "movb $0, 0xf(%%ebp)\n\t"
      "jne .LFUN_0011c310_4\n\t"
      "pushl $0x66\n\t"
      "pushl $0x28f768\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "call *%[c8ee60]\n\t"
      "movl %%eax, %%ebx\n\t"
      "addl $0x10, %%esp\n\t"
      "testl %%ebx, %%ebx\n\t"
      "movb $1, 0xf(%%ebp)\n\t"
      "je .LFUN_0011c310_7\n\t"
      ".LFUN_0011c310_4:\n\t"
      "testb $3, %%bl\n\t"
      "je .LFUN_0011c310_5\n\t"
      "pushl $1\n\t"
      "pushl $0x6b\n\t"
      "pushl $0x28f768\n\t"
      "pushl $0x28f7bc\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0011c310_5:\n\t"
      "pushl $0x3c\n\t"
      "pushl $0\n\t"
      "pushl %%esi\n\t"
      "call *%[memset]\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl $0x1f\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[c8de70]\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "movb 0xf(%%ebp), %%cl\n\t"
      "movl 0x14(%%ebp), %%edx\n\t"
      "movl %%eax, 0x30(%%esi)\n\t"
      "addl $0x18, %%esp\n\t"
      "movl %%esi, %%eax\n\t"
      "movb $0, 0x1f(%%esi)\n\t"
      "movl %%edi, 0x20(%%esi)\n\t"
      "movl %%ebx, 0x24(%%esi)\n\t"
      "movl $0, 0x2c(%%esi)\n\t"
      "movl $0x6c726163, 0x38(%%esi)\n\t"
      "movb %%cl, 0x28(%%esi)\n\t"
      "movl %%edx, 0x34(%%esi)\n\t"
      "call *%[c11c290]\n\t"
      ".LFUN_0011c310_6:\n\t"
      "popl %%edi\n\t"
      "movl %%esi, %%eax\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0011c310_7:\n\t"
      "pushl $0x7e\n\t"
      "pushl $0x28f768\n\t"
      "pushl %%esi\n\t"
      "call *%[c8ef70]\n\t"
      "addl $0xc, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "xorl %%eax, %%eax\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c8ee60] "m"(b11c310_c8ee60), [assert] "m"(b11c310_assert), [exitfn] "m"(b11c310_exitfn), [memset] "m"(b11c310_memset), [c8de70] "m"(b11c310_c8de70), [c11c290] "m"(b11c310_c11c290), [c8ef70] "m"(b11c310_c8ef70)
      : "memory");
}
#else
#error "FUN_0011c310: clang naked draft required"
#endif


/* FUN_0011c430 (0x11c430) — readable C lift. */
extern char DAT_0028f768[];
void FUN_0011c430(void *cache)
{
  FUN_0011c290((int)cache);
  if (*((char *)cache + 0x28) != 0)
    debug_free(*(void **)((char *)cache + 0x24), DAT_0028f768, 0x8c);
  debug_free(cache, DAT_0028f768, 0x8d);
}

/* FUN_0011c480 (0x11c480) — readable C lift from XBE leaf. */
void FUN_0011c480(int cache)
{
  unsigned char *c;
  unsigned char *node;
  void (*cb)(int);

  c = (unsigned char *)cache;
  FUN_0011c290(cache);
  if (*(int *)(c + 0x2c) == 0 || *(int *)(c + 0x24) == 0) {
    *(int *)(c + 0x2c) = 0;
    return;
  }
  for (node = *(unsigned char **)(c + 0x24); node != 0;
       node = *(unsigned char **)(node + 0xc)) {
    if ((node[4] & 2) == 0) {
      cb = *(void (**)(int))(c + 0x34);
      cb(*(int *)node);
      *(int *)(node + 4) = (*(int *)(node + 4) & ~1) | 2;
    }
  }
  *(int *)(c + 0x2c) = 0;
}

/* FUN_0011c4d0 (0x11c4d0) — readable C lift from XBE leaf. */
void FUN_0011c4d0(int cache, void *pointer)
{
  extern char DAT_00267eec[];
  extern char DAT_0028f768[];
  unsigned char *hdr;
  void (*fn)(int);

  if (pointer == 0) {
    display_assert(DAT_00267eec, DAT_0028f768, 0x11a, true);
    system_exit(-1);
  }
  hdr = (unsigned char *)pointer - 0x10;
  FUN_0011c290(cache);
  FUN_0011c210(cache, (int)hdr);
  if ((*(int *)(hdr + 4) & 2) == 0) {
    fn = *(void (**)(int))((char *)cache + 0x34);
    fn(*(int *)hdr);
    *(int *)(hdr + 4) = (*(int *)(hdr + 4) & ~1) | 2;
  }
}




/* ========================================================================
 * Already-ported: initialize_network_game_packets (0x12b640)
 * ======================================================================== */

void initialize_network_game_packets(void)
{
  verify_packet_group_definitions(&s_network_game_messages_group);
}

/* Static 0x604-byte output buffer for encode_network_game_message (0x46e8d0).
 * Passed as the pre-allocated destination to create_message(); only one caller
 * exists so this is safe as a module-level static. */
static char s_network_game_message_buffer[0x604];

/* encode_network_game_message — validate, encode and wrap a typed network
 * game message struct into a transmittable message packet (0x12b700).
 *
 * Validates that message_struct_size matches the expected size for the given
 * type, encodes the struct into a 1536-byte stack buffer using the global
 * packet group definition, then wraps the encoded bytes in a message header
 * and returns a pointer to the resulting message, or NULL on failure.
 */
void *encode_network_game_message(int type, void *data,
                                  int16_t message_struct_size)
{
  char encoded_buf[0x600];
  int32_t encoded_size;
  const char *assertion;
  int assertion_line;

  encoded_size = 0x600;

  switch ((int16_t)type) {
  case 0:
    if (message_struct_size == 0xc)
      goto size_ok;
    assertion =
      "message_struct_size==sizeof(message_client_broadcast_game_search)";
    assertion_line = 0xa0;
    break;
  case 1:
    if (message_struct_size == 8)
      goto size_ok;
    assertion = "message_struct_size==sizeof(message_client_ping)";
    assertion_line = 0xa1;
    break;
  case 2:
    if (message_struct_size == 0x114)
      goto size_ok;
    assertion = "message_struct_size==sizeof(message_server_game_advertise)";
    assertion_line = 0xa4;
    break;
  case 3:
    if (message_struct_size == 4)
      goto size_ok;
    assertion = "message_struct_size==sizeof(message_server_pong)";
    assertion_line = 0xa5;
    break;
  case 4:
    if (message_struct_size == 8)
      goto size_ok;
    assertion = "message_struct_size==sizeof(message_server_machine_accepted)";
    assertion_line = 0xa8;
    break;
  case 5:
    if (message_struct_size == 2)
      goto size_ok;
    assertion = "message_struct_size==sizeof(message_server_machine_rejected)";
    assertion_line = 0xa9;
    break;
  case 6:
    if (message_struct_size == 0x434)
      goto size_ok;
    assertion =
      "message_struct_size==sizeof(message_server_game_settings_update)";
    assertion_line = 0xaa;
    break;
  case 7:
    if (message_struct_size == 2)
      goto size_ok;
    assertion = "message_struct_size==sizeof(message_server_pregame_countdown)";
    assertion_line = 0xab;
    break;
  case 8:
    if (message_struct_size == 4)
      goto size_ok;
    assertion = "message_struct_size==sizeof(message_server_begin_game)";
    assertion_line = 0xad;
    break;
  case 9:
    if (message_struct_size == 4)
      goto size_ok;
    assertion =
      "message_struct_size==sizeof(message_server_graceful_game_exit_pregame)";
    assertion_line = 0xae;
    break;
  case 10:
    if (message_struct_size == 2)
      goto size_ok;
    assertion = "message_struct_size==sizeof(message_server_pregame_keep_alive)";
    assertion_line = 0xac;
    break;
  case 11:
    if (message_struct_size == 2)
      goto size_ok;
    assertion = "message_struct_size==sizeof(message_server_postgame_keep_alive)";
    assertion_line = 0xb1;
    break;
  case 12:
    if (message_struct_size == 0x50)
      goto size_ok;
    assertion = "message_struct_size==sizeof(message_client_join_game_request)";
    assertion_line = 0xb4;
    break;
  case 13:
    if (message_struct_size == 0x20)
      goto size_ok;
    assertion =
      "message_struct_size==sizeof(message_client_add_player_request_pregame)";
    assertion_line = 0xb5;
    break;
  case 14:
    if (message_struct_size == 0x20)
      goto size_ok;
    assertion = "message_struct_size==sizeof(message_client_remove_player_"
                "request_pregame)";
    assertion_line = 0xb6;
    break;
  case 15:
    if (message_struct_size == 0x44)
      goto size_ok;
    assertion = "message_struct_size==sizeof(message_client_settings_request)";
    assertion_line = 0xb7;
    break;
  case 16:
    if (message_struct_size == 0x20)
      goto size_ok;
    assertion =
      "message_struct_size==sizeof(message_client_player_settings_request)";
    assertion_line = 0xb8;
    break;
  case 17:
    if (message_struct_size == 2)
      goto size_ok;
    assertion = "message_struct_size==sizeof(message_client_game_start_request)";
    assertion_line = 0xb9;
    break;
  case 18:
    if (message_struct_size == 4)
      goto size_ok;
    assertion =
      "message_struct_size==sizeof(message_client_graceful_game_exit_pregame)";
    assertion_line = 0xba;
    break;
  case 19:
    if (message_struct_size == 0x100)
      goto size_ok;
    assertion =
      "message_struct_size==sizeof(message_client_map_is_precached_pregame)";
    assertion_line = 0xbb;
    break;
  case 20:
    if (message_struct_size == 0x210)
      goto size_ok;
    assertion = "message_struct_size==sizeof(message_server_game_update)";
    assertion_line = 0xbe;
    break;
  case 21:
    if (message_struct_size == 0x20)
      goto size_ok;
    assertion = "message_struct_size==sizeof(message_server_add_player_ingame)";
    assertion_line = 0xbf;
    break;
  case 22:
    if (message_struct_size == 0x24)
      goto size_ok;
    assertion =
      "message_struct_size==sizeof(message_server_remove_player_ingame)";
    assertion_line = 0xc0;
    break;
  case 23:
    if (message_struct_size == 4)
      goto size_ok;
    assertion = "message_struct_size==sizeof(message_server_game_over)";
    assertion_line = 0xc1;
    break;
  case 24:
    if (message_struct_size == 4)
      goto size_ok;
    assertion = "message_struct_size==sizeof(message_client_loaded)";
    assertion_line = 0xc4;
    break;
  case 25:
    if (message_struct_size == 0x88)
      goto size_ok;
    assertion = "message_struct_size==sizeof(message_client_game_update)";
    assertion_line = 0xc5;
    break;
  case 26:
    if (message_struct_size == 0x20)
      goto size_ok;
    assertion =
      "message_struct_size==sizeof(message_client_add_player_request_ingame)";
    assertion_line = 0xc6;
    break;
  case 27:
    if (message_struct_size == 0x20)
      goto size_ok;
    assertion = "message_struct_size==sizeof(message_client_remove_player_"
                "request_ingame)";
    assertion_line = 0xc7;
    break;
  case 28:
    if (message_struct_size == 0x10)
      goto size_ok;
    assertion =
      "message_struct_size==sizeof(message_client_host_crashed_cry_for_help)";
    assertion_line = 0xc9;
    break;
  case 29:
    if (message_struct_size == 0x10)
      goto size_ok;
    assertion = "message_struct_size==sizeof(message_client_join_new_host)";
    assertion_line = 0xca;
    break;
  case 30:
    if (message_struct_size == 4)
      goto size_ok;
    assertion = "message_struct_size==sizeof(message_server_switch_to_pregame)";
    assertion_line = 0xcd;
    break;
  case 31:
    if (message_struct_size == 4)
      goto size_ok;
    assertion =
      "message_struct_size==sizeof(message_server_graceful_game_exit_postgame)";
    assertion_line = 0xce;
    break;
  case 32:
    if (message_struct_size == 0x20)
      goto size_ok;
    assertion = "message_struct_size==sizeof(message_client_remove_player_"
                "request_postgame)";
    assertion_line = 0xd1;
    break;
  case 33:
    if (message_struct_size == 4)
      goto size_ok;
    assertion = "message_struct_size==sizeof(message_client_switch_to_pregame)";
    assertion_line = 0xd2;
    break;
  case 34:
    if (message_struct_size == 4)
      goto size_ok;
    assertion =
      "message_struct_size==sizeof(message_client_graceful_game_exit_postgame)";
    assertion_line = 0xd3;
    break;
  default:
    assertion = "unknown network game message structure type";
    assertion_line = 0xd5;
    break;
  }

  display_assert(assertion, "c:\\halo\\SOURCE\\networking\\network_messages.c",
                 assertion_line, 1);
  system_exit(-1);

size_ok:
  if (data == NULL || (int16_t)encoded_size < 1) {
    display_assert("message_struct && encoded_message && encoded_message_size "
                   "&& (*encoded_message_size>0)",
                   "c:\\halo\\SOURCE\\networking\\network_messages.c", 0x161,
                   1);
    system_exit(-1);
  }

  if (!encode_packet_group(&s_network_game_messages_group, data, encoded_buf,
                           &encoded_size, type, 1)) {
    network_game_log("encode_network_game_message() failed");
    return NULL;
  }

  {
    void *msg = (void *)create_message(3, (int)encoded_buf, encoded_size,
                                       (int)s_network_game_message_buffer, 0x604);
    if (msg == NULL) {
      network_game_log("create_message() failed");
    }
    return msg;
  }
}
