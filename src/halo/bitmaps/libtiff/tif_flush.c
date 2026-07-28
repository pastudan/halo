/* kb object: tif_flush.obj -> bitmaps/libtiff/tif_flush.c */

/* --- tif_flush.obj batch drafts (2026-07-26) --- */

/* FUN_00068780 (0x68780) — readable C lift (restored pre-naked). */
void FUN_00068780(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int edi = 0;

  /* cmp eax, ecx -> jle 0x687b1 */
  ((int (*)(void *))TIFFFlushData1)(0);
  /* test eax, eax -> jne 0x687b1 */
  csmemcpy((void *)(uintptr_t)edx, (void *)(uintptr_t)ecx, edi);
  /* test (char)eax, 0x10 -> je 0x68828 */
  /* cmp eax, 0x10 -> je 0x68811 */
  /* cmp eax, 0x20 -> jne 0x68828 */
  ((void(*)(void))FUN_0006f220)();
  ((void(*)(void))FUN_0006f1f0)();
  ((int (*)(void *))TIFFFlushData1)(0);
  /* test eax, eax -> je 0x68879 */
  /* test ebx, ebx -> jg 0x687c0 */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)edi;
}

/* FUN_00068890 (0x68890) — Capstone lift: consume n bytes from TIFF read buffer. */
int FUN_00068890(void *tif, void *buf, int n)
{
  extern char DAT_0025fff0[];
  int avail;
  void *cur;
  unsigned spp;
  int t;

  avail = *(int *)((char *)tif + 0x138);
  if (avail < n) {
    FUN_00068a30(*(void **)tif, DAT_0025fff0, *(void **)((char *)tif + 0xd4));
    return 0;
  }
  cur = *(void **)((char *)tif + 0x134);
  if (cur != buf)
    csmemcpy(buf, cur, (unsigned)n);
  if ((*(unsigned char *)((char *)tif + 0xa) & 0x10) != 0) {
    spp = *(unsigned short *)((char *)tif + 0x36);
    if (spp == 0x10) {
      t = n;
      FUN_0006f1f0((unsigned char *)buf, (t - (t >> 31)) >> 1);
    } else if (spp == 0x20) {
      t = n;
      FUN_0006f220((unsigned char *)buf, (t + ((t >> 31) & 3)) >> 2);
    }
  }
  cur = *(void **)((char *)tif + 0x134);
  avail = *(int *)((char *)tif + 0x138);
  *(void **)((char *)tif + 0x134) = (char *)cur + n;
  *(int *)((char *)tif + 0x138) = avail - n;
  return 1;
}


/* FUN_00068940 (0x68940) — readable C lift. */
int FUN_00068940(void *tif, int count)
{
  int stride;

  stride = *(int *)((char *)tif + 0x124) * count;
  *(int *)((char *)tif + 0x134) += stride;
  *(int *)((char *)tif + 0x138) -= stride;
  return 1;
}

/* FUN_00068970 (0x68970) — readable C lift.
 * DIR32 to handler symbols (oracle uses IMAGE_REL_I386_DIR32). */
int FUN_00068970(void *tif)
{
  *(void **)((char *)tif + 0xfc) = (void *)FUN_00068890;
  *(void **)((char *)tif + 0x104) = (void *)FUN_00068890;
  *(void **)((char *)tif + 0x10c) = (void *)FUN_00068890;
  *(void **)((char *)tif + 0x100) = (void *)FUN_00068780;
  *(void **)((char *)tif + 0x108) = (void *)FUN_00068780;
  *(void **)((char *)tif + 0x110) = (void *)FUN_00068780;
  *(void **)((char *)tif + 0x118) = (void *)FUN_00068940;
  return 1;
}



/* FUN_000689c0 (0x689c0) — readable C lift. */
void FUN_000689c0(const char *msg, void *a1, void *a2)
{
  extern char DAT_00259f68[];
  extern char DAT_00260020[];
  if (msg) {
    crt_fprintf((void *)0x331070, DAT_00259f68, msg);
  }
  ((void (*)(void *, void *, void *))FUN_001d9850)((void *)0x331070, a1, a2);
  crt_fprintf((void *)0x331070, DAT_00260020);
}

/* FUN_00068a10 (0x68a10) — readable C lift: swap global handler. */
void *FUN_00068a10(void *handler)
{
  void *prev;

  prev = *(void **)0x2ca1f4;
  *(void **)0x2ca1f4 = handler;
  return prev;
}

/* FUN_00068a30 (0x68a30) — readable C lift. */
void FUN_00068a30(void *a0, void *a1, ...)
{
  void *cb;
  cb = *(void **)0x2ca1f4;
  if (cb) {
    ((void (*)(void *, void *, void *))cb)(a0, a1, (void *)((char *)&a1 + 4));
  }
}

/* FUN_00068a50 (0x68a50) — readable C lift: set/clear flag bit0 at tif+9. */
void FUN_00068a50(void *tif, int enable)
{
  unsigned char flags;

  flags = *((unsigned char *)tif + 9);
  if (enable) {
    *((unsigned char *)tif + 9) = (unsigned char)(flags | 1);
  } else {
    *((unsigned char *)tif + 9) = (unsigned char)(flags & 0xfe);
  }
}

/* FUN_00068a70 (0x68a70) — XBE naked draft (batch 302). */
#if defined(__clang__)


__attribute__((naked, noinline))
void FUN_00068a70(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "movl 0x120(%%edi), %%ebx\n\t"
      "movswl 0x2(%%ebx), %%ecx\n\t"
      "movswl (%%ebx), %%edx\n\t"
      "pushl %%esi\n\t"
      "movl %%eax, %%esi\n\t"
      "xorl %%eax, %%eax\n\t"
      "testl %%ecx, %%ecx\n\t"
      "movl %%ebx, -0x4(%%ebp)\n\t"
      "jne .LFUN_00068a70_1\n\t"
      "movl $8, %%ecx\n\t"
      ".LFUN_00068a70_1:\n\t"
      "cmpl $7, %%ecx\n\t"
      "ja .LFUN_00068a70_2\n\t"
      "jmp *.LFUN_00068a70_jt(,%%ecx,4)\n\t"
      ".LFUN_00068a70_2:\n\t"
      "movl 0x138(%%edi), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "jle .LFUN_00068a70_29\n\t"
      "decl %%ecx\n\t"
      "movl %%ecx, 0x138(%%edi)\n\t"
      "movl 0x134(%%edi), %%ecx\n\t"
      "movzbl (%%ecx), %%edx\n\t"
      "movl 0x14(%%ebx), %%ebx\n\t"
      "movzbl (%%ebx,%%edx,1), %%edx\n\t"
      "movl -0x4(%%ebp), %%ebx\n\t"
      "incl %%ecx\n\t"
      "movl %%ecx, 0x134(%%edi)\n\t"
      ".LFUN_00068a70_3:\n\t"
      "shll $1, %%eax\n\t"
      "testb %%dl, %%dl\n\t"
      "jns .LFUN_00068a70_4\n\t"
      "orl $1, %%eax\n\t"
      ".LFUN_00068a70_4:\n\t"
      "incl %%esi\n\t"
      "testl %%eax, %%eax\n\t"
      "jg .LFUN_00068a70_21\n\t"
      ".LFUN_00068a70_5:\n\t"
      "shll $1, %%eax\n\t"
      "testb $0x40, %%dl\n\t"
      "je .LFUN_00068a70_6\n\t"
      "orl $1, %%eax\n\t"
      ".LFUN_00068a70_6:\n\t"
      "incl %%esi\n\t"
      "testl %%eax, %%eax\n\t"
      "jg .LFUN_00068a70_22\n\t"
      ".LFUN_00068a70_7:\n\t"
      "shll $1, %%eax\n\t"
      "testb $0x20, %%dl\n\t"
      "je .LFUN_00068a70_8\n\t"
      "orl $1, %%eax\n\t"
      ".LFUN_00068a70_8:\n\t"
      "incl %%esi\n\t"
      "testl %%eax, %%eax\n\t"
      "jg .LFUN_00068a70_23\n\t"
      ".LFUN_00068a70_9:\n\t"
      "shll $1, %%eax\n\t"
      "testb $0x10, %%dl\n\t"
      "je .LFUN_00068a70_10\n\t"
      "orl $1, %%eax\n\t"
      ".LFUN_00068a70_10:\n\t"
      "incl %%esi\n\t"
      "testl %%eax, %%eax\n\t"
      "jg .LFUN_00068a70_24\n\t"
      ".LFUN_00068a70_11:\n\t"
      "shll $1, %%eax\n\t"
      "testb $8, %%dl\n\t"
      "je .LFUN_00068a70_12\n\t"
      "orl $1, %%eax\n\t"
      ".LFUN_00068a70_12:\n\t"
      "incl %%esi\n\t"
      "testl %%eax, %%eax\n\t"
      "jg .LFUN_00068a70_25\n\t"
      ".LFUN_00068a70_13:\n\t"
      "shll $1, %%eax\n\t"
      "testb $4, %%dl\n\t"
      "je .LFUN_00068a70_14\n\t"
      "orl $1, %%eax\n\t"
      ".LFUN_00068a70_14:\n\t"
      "incl %%esi\n\t"
      "testl %%eax, %%eax\n\t"
      "jg .LFUN_00068a70_26\n\t"
      ".LFUN_00068a70_15:\n\t"
      "shll $1, %%eax\n\t"
      "testb $2, %%dl\n\t"
      "je .LFUN_00068a70_16\n\t"
      "orl $1, %%eax\n\t"
      ".LFUN_00068a70_16:\n\t"
      "incl %%esi\n\t"
      "testl %%eax, %%eax\n\t"
      "jg .LFUN_00068a70_27\n\t"
      ".LFUN_00068a70_17:\n\t"
      "shll $1, %%eax\n\t"
      "testb $1, %%dl\n\t"
      "je .LFUN_00068a70_18\n\t"
      "orl $1, %%eax\n\t"
      ".LFUN_00068a70_18:\n\t"
      "incl %%esi\n\t"
      "testl %%eax, %%eax\n\t"
      "jle .LFUN_00068a70_2\n\t"
      "movl $8, %%ecx\n\t"
      ".LFUN_00068a70_19:\n\t"
      "cmpl $0xc, %%esi\n\t"
      "jl .LFUN_00068a70_20\n\t"
      "cmpl $1, %%eax\n\t"
      "je .LFUN_00068a70_28\n\t"
      ".LFUN_00068a70_20:\n\t"
      "xorl %%esi, %%esi\n\t"
      "xorl %%eax, %%eax\n\t"
      "jmp .LFUN_00068a70_1\n\t"
      ".LFUN_00068a70_21:\n\t"
      "movl $1, %%ecx\n\t"
      "jmp .LFUN_00068a70_19\n\t"
      ".LFUN_00068a70_22:\n\t"
      "movl $2, %%ecx\n\t"
      "jmp .LFUN_00068a70_19\n\t"
      ".LFUN_00068a70_23:\n\t"
      "movl $3, %%ecx\n\t"
      "jmp .LFUN_00068a70_19\n\t"
      ".LFUN_00068a70_24:\n\t"
      "movl $4, %%ecx\n\t"
      "jmp .LFUN_00068a70_19\n\t"
      ".LFUN_00068a70_25:\n\t"
      "movl $5, %%ecx\n\t"
      "jmp .LFUN_00068a70_19\n\t"
      ".LFUN_00068a70_26:\n\t"
      "movl $6, %%ecx\n\t"
      "jmp .LFUN_00068a70_19\n\t"
      ".LFUN_00068a70_27:\n\t"
      "movl $7, %%ecx\n\t"
      "jmp .LFUN_00068a70_19\n\t"
      ".LFUN_00068a70_28:\n\t"
      "xorl %%eax, %%eax\n\t"
      "cmpl $7, %%ecx\n\t"
      "setg %%al\n\t"
      "movw %%dx, (%%ebx)\n\t"
      "decl %%eax\n\t"
      "andl %%ecx, %%eax\n\t"
      "movw %%ax, 0x2(%%ebx)\n\t"
      ".LFUN_00068a70_29:\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "movl %%edi, %%edi\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_00068a70_jt:\n\t"
      ".long .LFUN_00068a70_3\n\t"
      ".long .LFUN_00068a70_5\n\t"
      ".long .LFUN_00068a70_7\n\t"
      ".long .LFUN_00068a70_9\n\t"
      ".long .LFUN_00068a70_11\n\t"
      ".long .LFUN_00068a70_13\n\t"
      ".long .LFUN_00068a70_15\n\t"
      ".long .LFUN_00068a70_17\n\t"
      ".text\n\t"
      :
      :
      : "memory");
}
#else
#error "FUN_00068a70: clang naked draft required"
#endif


/* FUN_00068bd0 (0x68bd0) — readable C lift. */
int FUN_00068bd0(unsigned char *tif)
{
  unsigned char *state;
  unsigned int n;
  unsigned short bitpos;
  int mask;
  state = *(unsigned char **)(tif + 0x120);
  if (*(short *)(state + 2) == 0) {
    n = *(unsigned int *)(tif + 0x138);
    if ((int)n > 0) {
      *(unsigned int *)(tif + 0x138) = n - 1;
      {
        unsigned char b;
        unsigned char *table;
        b = **(unsigned char **)(tif + 0x134);
        table = *(unsigned char **)(state + 0x14);
        *(unsigned short *)state = table[b];
        *(unsigned int *)(tif + 0x134) += 1;
      }
    }
  }
  bitpos = *(unsigned short *)(state + 2);
  mask = *(unsigned char *)(0x2ec370 + (short)bitpos);
  mask &= (short)*(unsigned short *)state;
  bitpos = (unsigned short)(bitpos + 1);
  *(unsigned short *)(state + 2) = bitpos;
  if ((short)bitpos > 7)
    *(unsigned short *)(state + 2) = 0;
  return mask;
}

/* FUN_00068c40 (0x68c40) — readable C lift: memset dest@<edx>, count@<ecx>, value stack. */
void FUN_00068c40(unsigned char value, void *dest /*@<edx>*/, int count /*@<ecx>*/)
{
  unsigned char *p;
  int n;

  if (count <= 0)
    return;
  p = (unsigned char *)dest;
  n = count;
  while (n-- > 0)
    *p++ = value;
}

/* FUN_00068c70 (0x68c70) — XBE naked draft (batch 333). */
#if defined(__clang__)
static void (*const b68c70_c68a30)(int param_1, const char *format, ...) = (void (*)(int, const char *, ...))FUN_00068a30;
static void (*const b68c70_c6f890)(void) = (void (*)(void))FUN_0006f890;
static void (*const b68c70_c6d820)(void) = (void *)TIFFScanlineSize;
static void * (*const b68c70_c8ee60)(uint32_t size, bool zero, const char *file, int line) = debug_malloc;

__attribute__((naked, noinline))
void FUN_00068c70(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "cmpw $1, 0x36(%%esi)\n\t"
      "pushl %%ebx\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "je .LFUN_00068c70_1\n\t"
      "movl (%%esi), %%eax\n\t"
      "pushl $0x260084\n\t"
      "pushl %%eax\n\t"
      "call *%[c68a30]\n\t"
      "addl $8, %%esp\n\t"
      "xorl %%eax, %%eax\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00068c70_1:\n\t"
      "movb 0xa(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "pushl %%edi\n\t"
      "pushl %%esi\n\t"
      "jns .LFUN_00068c70_2\n\t"
      "call *%[c6f890]\n\t"
      "movl 0x28(%%esi), %%ecx\n\t"
      "movl %%ecx, -0x4(%%ebp)\n\t"
      "jmp .LFUN_00068c70_3\n\t"
      ".LFUN_00068c70_2:\n\t"
      "call *%[c6d820]\n\t"
      "movl 0x1c(%%esi), %%edx\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      ".LFUN_00068c70_3:\n\t"
      "movl %%eax, %%edi\n\t"
      "movb 0x68(%%esi), %%al\n\t"
      "addl $4, %%esp\n\t"
      "testb $1, %%al\n\t"
      "jne .LFUN_00068c70_4\n\t"
      "cmpw $4, 0x3a(%%esi)\n\t"
      "jne .LFUN_00068c70_5\n\t"
      ".LFUN_00068c70_4:\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "leal 0x1(%%edi,%%eax,1), %%ebx\n\t"
      ".LFUN_00068c70_5:\n\t"
      "pushl $0xfc\n\t"
      "pushl $0x260058\n\t"
      "pushl $0\n\t"
      "pushl %%ebx\n\t"
      "call *%[c8ee60]\n\t"
      "addl $0x10, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%eax, 0x120(%%esi)\n\t"
      "jne .LFUN_00068c70_6\n\t"
      "movl (%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x260034\n\t"
      "pushl $0x260024\n\t"
      "call *%[c68a30]\n\t"
      "addl $0xc, %%esp\n\t"
      "popl %%edi\n\t"
      "xorl %%eax, %%eax\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00068c70_6:\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "movl %%edi, 0x8(%%eax)\n\t"
      "movl %%edx, 0xc(%%eax)\n\t"
      "movzwl 0x40(%%esi), %%ecx\n\t"
      "movsbl 0x8(%%esi), %%edx\n\t"
      "cmpl %%ecx, %%edx\n\t"
      "movl $0x2ecbe0, %%ecx\n\t"
      "jne .LFUN_00068c70_7\n\t"
      "movl $0x2ecce0, %%ecx\n\t"
      ".LFUN_00068c70_7:\n\t"
      "movl %%ecx, 0x14(%%eax)\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "cmpw $1, 0x3c(%%esi)\n\t"
      "sete %%cl\n\t"
      "movw %%cx, 0x4(%%eax)\n\t"
      "testb $1, 0x68(%%esi)\n\t"
      "jne .LFUN_00068c70_8\n\t"
      "cmpw $4, 0x3a(%%esi)\n\t"
      "je .LFUN_00068c70_8\n\t"
      "popl %%edi\n\t"
      "movl $0, 0x18(%%eax)\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00068c70_8:\n\t"
      "movl 0x120(%%esi), %%edx\n\t"
      "cmpw $0, 0x4(%%eax)\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "leal 0x1(%%edx,%%ecx,1), %%ecx\n\t"
      "sete %%dl\n\t"
      "decb %%dl\n\t"
      "popl %%edi\n\t"
      "movl %%ecx, 0x18(%%eax)\n\t"
      "popl %%ebx\n\t"
      "andl $0xff, %%edx\n\t"
      "movb %%dl, -0x1(%%ecx)\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c68a30] "m"(b68c70_c68a30), [c6f890] "m"(b68c70_c6f890), [c6d820] "m"(b68c70_c6d820), [c8ee60] "m"(b68c70_c8ee60)
      : "memory");
}
#else
#error "FUN_00068c70: clang naked draft required"
#endif


/* FUN_00068d80 (0x68d80) — XBE naked draft (batch 339). */
#if defined(__clang__)
static void (*const b68d80_c68c70)(void) = (void (*)(void))FUN_00068c70;
static void (*const b68d80_c68a70)(void) = (void (*)(void))FUN_00068a70;
static void (*const b68d80_c68bd0)(void) = (void (*)(void))FUN_00068bd0;

__attribute__((naked, noinline))
void FUN_00068d80(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "movl 0x120(%%edi), %%esi\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "jne .LFUN_00068d80_1\n\t"
      "pushl $0x1c\n\t"
      "movl %%edi, %%esi\n\t"
      "call *%[c68c70]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $4, %%esp\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "jne .LFUN_00068d80_1\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "xorl %%eax, %%eax\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00068d80_1:\n\t"
      "movl 0x18(%%esi), %%edx\n\t"
      "cmpl %%ebx, %%edx\n\t"
      "movw %%bx, 0x2(%%esi)\n\t"
      "movw %%bx, (%%esi)\n\t"
      "movl %%ebx, 0x10(%%esi)\n\t"
      "je .LFUN_00068d80_2\n\t"
      "movw 0x4(%%esi), %%ax\n\t"
      "movl 0x8(%%esi), %%ecx\n\t"
      "negw %%ax\n\t"
      "sbbl %%eax, %%eax\n\t"
      "andl $0xff, %%eax\n\t"
      "cmpl %%ebx, %%ecx\n\t"
      "jle .LFUN_00068d80_2\n\t"
      "movb %%al, %%bl\n\t"
      "movb %%bl, %%bh\n\t"
      "movl %%edx, %%edi\n\t"
      "movl %%ecx, %%edx\n\t"
      "shrl $2, %%ecx\n\t"
      "movl %%ebx, %%eax\n\t"
      "shll $0x10, %%eax\n\t"
      "movw %%bx, %%ax\n\t"
      "rep stosl\n\t"
      "movl %%edx, %%ecx\n\t"
      "andl $3, %%ecx\n\t"
      "rep stosb\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      ".LFUN_00068d80_2:\n\t"
      "testb $2, 0x9(%%edi)\n\t"
      "jne .LFUN_00068d80_3\n\t"
      "xorl %%eax, %%eax\n\t"
      "call *%[c68a70]\n\t"
      "testb $1, 0x68(%%edi)\n\t"
      "je .LFUN_00068d80_3\n\t"
      "movl %%edi, %%eax\n\t"
      "call *%[c68bd0]\n\t"
      "negl %%eax\n\t"
      "sbbl %%eax, %%eax\n\t"
      "incl %%eax\n\t"
      "movl %%eax, 0x10(%%esi)\n\t"
      ".LFUN_00068d80_3:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl $1, %%eax\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c68c70] "m"(b68d80_c68c70), [c68a70] "m"(b68d80_c68a70), [c68bd0] "m"(b68d80_c68bd0)
      : "memory");
}
#else
#error "FUN_00068d80: clang naked draft required"
#endif


/* FUN_00068e20 (0x68e20) — Capstone lift: set nbits 1-bits into bitstream.
 * ABI: buf@<eax>, bitpos@<ecx>, nbits@<edx>. */
void FUN_00068e20(unsigned char *buf /*@<eax>*/, int bitpos /*@<ecx>*/, int nbits /*@<edx>*/)
{
  extern unsigned char DAT_002ec378[];
  unsigned char *p;
  int n;
  int bp;
  unsigned nbytes;

  if (nbits <= 0)
    return;
  p = buf + (bitpos >> 3);
  bp = bitpos & 7;
  n = nbits;
  if (bp != 0) {
    int room = 8 - bp;
    if (n < room) {
      *p = (unsigned char)(*p | (DAT_002ec378[n] >> bp));
      return;
    }
    *p = (unsigned char)(*p | ((int)0xff >> bp));
    n = n + bp - 8;
    p++;
  }
  if (n >= 8) {
    unsigned i;
    nbytes = (unsigned)n >> 3;
    for (i = 0; i < nbytes; i++)
      p[i] = 0xff;
    n -= (int)(nbytes * 8);
    p += nbytes;
  }
  *p = (unsigned char)(*p | DAT_002ec378[n]);
}


/* FUN_00068eb0 (0x68eb0) — Capstone lift: LZW/Huffman accumulate codes.
 * ABI: tif@<edi>. Returns accumulated length or negative status. */
int FUN_00068eb0(void *tif /*@<edi>*/)
{
  unsigned char *state;
  unsigned short bits;
  unsigned short next_bits;
  unsigned short code;
  unsigned idx;
  int rem;
  unsigned char *buf;
  unsigned char *map;
  int acc = 0;
  short len;

  state = *(unsigned char **)((char *)tif + 0x120);
  bits = *(unsigned short *)(state + 2);
  for (;;) {
    if (*(unsigned short *)(state + 2) == 0)
      goto refill;
  decode:
    idx = ((unsigned)(short)bits << 8) + (unsigned)(*(short *)state);
    next_bits = *(unsigned char *)(0x2cf770u + idx);
    code = *(unsigned char *)(0x2ddd70u + idx);
    if (next_bits == 0) {
  refill:
      rem = *(int *)((char *)tif + 0x138);
      if (rem <= 0)
        return (int)0xfffffffc;
      *(int *)((char *)tif + 0x138) = rem - 1;
      buf = *(unsigned char **)((char *)tif + 0x134);
      map = *(unsigned char **)(state + 0x14);
      *(unsigned short *)state = map[*buf];
      *(int *)((char *)tif + 0x134) = *(int *)((char *)tif + 0x134) + 1;
      bits = *(unsigned short *)(state + 2);
      goto decode;
    }
    if (next_bits == 1)
      return -1;
    if (next_bits == 0xd2)
      return (int)0xfffffffd;
    {
      int k = (int)(short)next_bits - 2;
      k = k + k * 2;
      *(unsigned short *)(state + 2) = code;
      bits = code;
      len = *(short *)(0x2ca254u + (unsigned)k * 2);
      acc += (int)len;
      if (len >= 0x40)
        continue;
      return acc;
    }
  }
}



/* FUN_00068f60 (0x68f60) — Capstone lift: LZW/Huffman accumulate (+8 bit bias).
 * ABI: tif@<edi>. Returns accumulated length or negative status. */
int FUN_00068f60(void *tif /*@<edi>*/)
{
  unsigned char *state;
  unsigned short bits;
  unsigned short next_bits;
  unsigned short code;
  unsigned idx;
  int rem;
  unsigned char *buf;
  unsigned char *map;
  int acc = 0;
  short len;

  state = *(unsigned char **)((char *)tif + 0x120);
  bits = (unsigned short)(*(unsigned short *)(state + 2) + 8);
  for (;;) {
    if (*(unsigned short *)(state + 2) == 0)
      goto refill;
  decode:
    idx = ((unsigned)(short)bits << 8) + (unsigned)(*(short *)state);
    next_bits = *(unsigned char *)(0x2cf770u + idx);
    code = *(unsigned char *)(0x2ddd70u + idx);
    if (next_bits == 0) {
  refill:
      rem = *(int *)((char *)tif + 0x138);
      if (rem <= 0)
        return (int)0xfffffffc;
      *(int *)((char *)tif + 0x138) = rem - 1;
      buf = *(unsigned char **)((char *)tif + 0x134);
      map = *(unsigned char **)(state + 0x14);
      *(unsigned short *)state = map[*buf];
      *(int *)((char *)tif + 0x134) = *(int *)((char *)tif + 0x134) + 1;
      bits = *(unsigned short *)(state + 2);
      goto decode;
    }
    if (next_bits == 1)
      return -1;
    if (next_bits == 0xd2)
      return (int)0xfffffffd;
    {
      int k = (int)(short)next_bits - 0x6a;
      k = k + k * 2;
      *(unsigned short *)(state + 2) = code;
      bits = code;
      len = *(short *)(0x2ca254u + (unsigned)k * 2);
      acc += (int)len;
      if (len >= 0x40) {
        bits = (unsigned short)(bits + 8);
        continue;
      }
      return acc;
    }
  }
}



/* FUN_00069020 (0x69020) — XBE naked draft (batch 300). */
#if defined(__clang__)
static void (*const b69020_c68eb0)(void) = (void (*)(void))FUN_00068eb0;
static void (*const b69020_c68f60)(void) = (void (*)(void))FUN_00068f60;
static void (*const b69020_c68e20)(void) = (void (*)(void))FUN_00068e20;
static void (*const b69020_c68a30)(int param_1, const char *format, ...) = (void (*)(int, const char *, ...))FUN_00068a30;
static void (*const b69020_c68a70)(void) = (void (*)(void))FUN_00068a70;
static void (*const b69020_c6f9d0)(void) = (void (*)(void))FUN_0006f9d0;

__attribute__((naked, noinline))
void FUN_00069020(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $8, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl %%eax, %%edi\n\t"
      "movl 0x120(%%edi), %%eax\n\t"
      "movw 0x4(%%eax), %%cx\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "movw %%cx, -0x4(%%ebp)\n\t"
      "movl %%edi, %%edi\n\t"
      ".LFUN_00069020_1:\n\t"
      "movw -0x4(%%ebp), %%dx\n\t"
      "cmpw 0x4(%%eax), %%dx\n\t"
      "jne .LFUN_00069020_2\n\t"
      "call *%[c68eb0]\n\t"
      "jmp .LFUN_00069020_3\n\t"
      ".LFUN_00069020_2:\n\t"
      "call *%[c68f60]\n\t"
      ".LFUN_00069020_3:\n\t"
      "movl %%eax, %%esi\n\t"
      "cmpl $-4, %%esi\n\t"
      "je .LFUN_00069020_13\n\t"
      "cmpl $-3, %%esi\n\t"
      "je .LFUN_00069020_12\n\t"
      "cmpl $-1, %%esi\n\t"
      "je .LFUN_00069020_7\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "leal (%%esi,%%ebx,1), %%ecx\n\t"
      "cmpl %%eax, %%ecx\n\t"
      "jle .LFUN_00069020_4\n\t"
      "movl %%eax, %%esi\n\t"
      "subl %%ebx, %%esi\n\t"
      ".LFUN_00069020_4:\n\t"
      "testl %%esi, %%esi\n\t"
      "jle .LFUN_00069020_6\n\t"
      "cmpw $0, -0x4(%%ebp)\n\t"
      "je .LFUN_00069020_5\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl %%esi, %%edx\n\t"
      "movl %%ebx, %%ecx\n\t"
      "call *%[c68e20]\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      ".LFUN_00069020_5:\n\t"
      "addl %%esi, %%ebx\n\t"
      "cmpl %%eax, %%ebx\n\t"
      "jge .LFUN_00069020_8\n\t"
      ".LFUN_00069020_6:\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "xorl %%edx, %%edx\n\t"
      "cmpw %%dx, -0x4(%%ebp)\n\t"
      "sete %%dl\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      "jmp .LFUN_00069020_1\n\t"
      ".LFUN_00069020_7:\n\t"
      "movl 0xd4(%%edi), %%eax\n\t"
      "movl (%%edi), %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x26010c\n\t"
      "pushl $0x2ec384\n\t"
      "call *%[c68a30]\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00069020_8:\n\t"
      "testb $2, 0x9(%%edi)\n\t"
      "jne .LFUN_00069020_9\n\t"
      "xorl %%eax, %%eax\n\t"
      "call *%[c68a70]\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      ".LFUN_00069020_9:\n\t"
      "testb $4, 0x9(%%edi)\n\t"
      "je .LFUN_00069020_10\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "movw $0, 0x2(%%edx)\n\t"
      ".LFUN_00069020_10:\n\t"
      "testb $8, 0x9(%%edi)\n\t"
      "je .LFUN_00069020_11\n\t"
      "movl 0x134(%%edi), %%ecx\n\t"
      "testb $1, %%cl\n\t"
      "je .LFUN_00069020_11\n\t"
      "movl 0x138(%%edi), %%edx\n\t"
      "decl %%edx\n\t"
      "incl %%ecx\n\t"
      "movl %%edx, 0x138(%%edi)\n\t"
      "movl %%ecx, 0x134(%%edi)\n\t"
      ".LFUN_00069020_11:\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "cmpl %%eax, %%ebx\n\t"
      "sete %%cl\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ecx, %%eax\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00069020_12:\n\t"
      "movl 0xd4(%%edi), %%edx\n\t"
      "movl (%%edi), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl $0x2600e4\n\t"
      "pushl $0x2ec384\n\t"
      "call *%[c6f9d0]\n\t"
      "addl $0x14, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl $1, %%eax\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00069020_13:\n\t"
      "movl 0xd4(%%edi), %%ecx\n\t"
      "movl (%%edi), %%edx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x2600bc\n\t"
      "pushl $0x2ec384\n\t"
      "call *%[c68a30]\n\t"
      "addl $0x14, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "xorl %%eax, %%eax\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c68eb0] "m"(b69020_c68eb0), [c68f60] "m"(b69020_c68f60), [c68e20] "m"(b69020_c68e20), [c68a30] "m"(b69020_c68a30), [c68a70] "m"(b69020_c68a70), [c6f9d0] "m"(b69020_c6f9d0)
      : "memory");
}
#else
#error "FUN_00069020: clang naked draft required"
#endif


/* FUN_00069180 (0x69180) — Capstone lift: LZW next-code from stream.
 * ABI: tif@<edx>. Returns next code, or 0xd on underrun. */
int FUN_00069180(void *tif /*@<edx>*/)
{
  unsigned char *state;
  unsigned short bits;
  int rem;
  unsigned char *buf;
  unsigned char *map;
  unsigned short code;
  unsigned short next_bits;
  unsigned idx;

  state = *(unsigned char **)((char *)tif + 0x120);
  for (;;) {
    bits = *(unsigned short *)(state + 2);
    if (bits == 0 || (short)bits > 7) {
      rem = *(int *)((char *)tif + 0x138);
      if (rem <= 0)
        return 0xd;
      *(int *)((char *)tif + 0x138) = rem - 1;
      buf = *(unsigned char **)((char *)tif + 0x134);
      map = *(unsigned char **)(state + 0x14);
      *(unsigned short *)state = map[*buf];
      *(int *)((char *)tif + 0x134) = *(int *)((char *)tif + 0x134) + 1;
    }
    idx = ((unsigned)(*(short *)(state + 2)) << 8) + (unsigned)(*(short *)state);
    next_bits = *(unsigned char *)(0x2ccf70u + idx);
    code = *(unsigned char *)(0x2ce370u + idx);
    *(unsigned short *)(state + 2) = code;
    if (next_bits != 0)
      return (int)(short)next_bits;
  }
}



/* FUN_00069200 (0x69200) — XBE naked draft (batch 311). */
#if defined(__clang__)
static void (*const b69200_c6fe10)(void) = (void (*)(void))TIFFFlushData1;

__attribute__((naked, noinline))
void FUN_00069200(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x120(%%edi), %%esi\n\t"
      "movl %%eax, %%ebx\n\t"
      "movswl 0x2(%%esi), %%eax\n\t"
      "cmpl %%eax, %%ebx\n\t"
      "jbe .LFUN_00069200_3\n\t"
      ".LFUN_00069200_1:\n\t"
      "movswl 0x2(%%esi), %%edx\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl %%ebx, %%ecx\n\t"
      "subl %%edx, %%ecx\n\t"
      "shrl %%cl, %%eax\n\t"
      "movl %%ecx, %%ebx\n\t"
      "orw %%ax, (%%esi)\n\t"
      "movl 0x138(%%edi), %%ecx\n\t"
      "cmpl 0x130(%%edi), %%ecx\n\t"
      "jl .LFUN_00069200_2\n\t"
      "pushl %%edi\n\t"
      "call *%[c6fe10]\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_00069200_2:\n\t"
      "movswl (%%esi), %%edx\n\t"
      "movl 0x14(%%esi), %%eax\n\t"
      "movb (%%edx,%%eax,1), %%dl\n\t"
      "movl 0x134(%%edi), %%ecx\n\t"
      "movb %%dl, (%%ecx)\n\t"
      "movl 0x134(%%edi), %%eax\n\t"
      "movl 0x138(%%edi), %%edx\n\t"
      "incl %%eax\n\t"
      "incl %%edx\n\t"
      "movl %%eax, 0x134(%%edi)\n\t"
      "movl %%edx, 0x138(%%edi)\n\t"
      "movw $0, (%%esi)\n\t"
      "movw $8, 0x2(%%esi)\n\t"
      "movswl 0x2(%%esi), %%eax\n\t"
      "cmpl %%eax, %%ebx\n\t"
      "ja .LFUN_00069200_1\n\t"
      ".LFUN_00069200_3:\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x2ec3a4(,%%ebx,4), %%dx\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x2(%%esi), %%ax\n\t"
      "andl %%ecx, %%edx\n\t"
      "movl %%eax, %%ecx\n\t"
      "subl %%ebx, %%ecx\n\t"
      "shll %%cl, %%edx\n\t"
      "subl %%ebx, %%eax\n\t"
      "movw %%ax, 0x2(%%esi)\n\t"
      "orw %%dx, (%%esi)\n\t"
      "testw %%ax, %%ax\n\t"
      "jne .LFUN_00069200_5\n\t"
      "movl 0x138(%%edi), %%eax\n\t"
      "cmpl 0x130(%%edi), %%eax\n\t"
      "jl .LFUN_00069200_4\n\t"
      "pushl %%edi\n\t"
      "call *%[c6fe10]\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_00069200_4:\n\t"
      "movswl (%%esi), %%ecx\n\t"
      "movl 0x14(%%esi), %%edx\n\t"
      "movb (%%ecx,%%edx,1), %%cl\n\t"
      "movl 0x134(%%edi), %%eax\n\t"
      "movb %%cl, (%%eax)\n\t"
      "movl 0x134(%%edi), %%ecx\n\t"
      "movl 0x138(%%edi), %%eax\n\t"
      "incl %%ecx\n\t"
      "incl %%eax\n\t"
      "movl %%ecx, 0x134(%%edi)\n\t"
      "movl %%eax, 0x138(%%edi)\n\t"
      "movw $0, (%%esi)\n\t"
      "movw $8, 0x2(%%esi)\n\t"
      ".LFUN_00069200_5:\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c6fe10] "m"(b69200_c6fe10)
      : "memory");
}
#else
#error "FUN_00069200: clang naked draft required"
#endif


/* FUN_00069310 (0x69310) — XBE naked draft (batch 311). */
#if defined(__clang__)
static void (*const b69310_c69200)(void) = (void (*)(void))FUN_00069200;

__attribute__((naked, noinline))
void FUN_00069310(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "movl %%eax, %%esi\n\t"
      "cmpl $0xa40, %%esi\n\t"
      "pushl %%edi\n\t"
      "movl %%ecx, %%edi\n\t"
      "jl .LFUN_00069310_2\n\t"
      "jmp .LFUN_00069310_1\n\t"
      "leal (%%esp), %%esp\n\t"
      "jmp .LFUN_00069310_1\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".LFUN_00069310_1:\n\t"
      "movzwl 0x26c(%%ebx), %%ecx\n\t"
      "movzwl 0x26a(%%ebx), %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c69200]\n\t"
      "movswl 0x26e(%%ebx), %%edx\n\t"
      "subl %%edx, %%esi\n\t"
      "addl $4, %%esp\n\t"
      "cmpl $0xa40, %%esi\n\t"
      "jge .LFUN_00069310_1\n\t"
      ".LFUN_00069310_2:\n\t"
      "cmpl $0x40, %%esi\n\t"
      "jl .LFUN_00069310_3\n\t"
      "movl %%esi, %%eax\n\t"
      "sarl $6, %%eax\n\t"
      "addl $0x3f, %%eax\n\t"
      "leal (%%eax,%%eax,2), %%eax\n\t"
      "leal (%%ebx,%%eax,2), %%ecx\n\t"
      "movzwl (%%ecx), %%eax\n\t"
      "movl %%ecx, -0x4(%%ebp)\n\t"
      "movzwl 0x2(%%ecx), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c69200]\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "movswl 0x4(%%edx), %%eax\n\t"
      "addl $4, %%esp\n\t"
      "subl %%eax, %%esi\n\t"
      ".LFUN_00069310_3:\n\t"
      "leal (%%esi,%%esi,2), %%ecx\n\t"
      "movzwl 0x2(%%ebx,%%ecx,2), %%edx\n\t"
      "movzwl (%%ebx,%%ecx,2), %%eax\n\t"
      "leal (%%ebx,%%ecx,2), %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c69200]\n\t"
      "addl $4, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c69200] "m"(b69310_c69200)
      : "memory");
}
#else
#error "FUN_00069310: clang naked draft required"
#endif


/* FUN_000693b0 (0x693b0) — Capstone lift: flush/put pending Huffman bits.
 * Calls FUN_00069200(value, nbits@<eax>, tif@<edi>). */
void FUN_000693b0(void *tif)
{
  unsigned char *state;
  int nbits;

  state = *(unsigned char **)((char *)tif + 0x120);
  if (*(unsigned char *)((char *)tif + 0x68) & 4) {
    nbits = *(short *)(state + 2);
    if (nbits != 4) {
      if (nbits < 4)
        nbits += 4;
      else
        nbits -= 4;
      ((void (*)(unsigned int, unsigned int, void *))FUN_00069200)(
          0, (unsigned)nbits, tif);
    }
  }
  ((void (*)(unsigned int, unsigned int, void *))FUN_00069200)(1, 0xc, tif);
  if (*(unsigned char *)((char *)tif + 0x68) & 1) {
    unsigned int is_zero = (*(unsigned int *)(state + 0x10) == 0);
    ((void (*)(unsigned int, unsigned int, void *))FUN_00069200)(
        is_zero, 1, tif);
  }
}



/* FUN_00069420 (0x69420) — XBE naked draft (batch 316). */
#if defined(__clang__)
static void (*const b69420_c68c70)(void) = (void (*)(void))FUN_00068c70;

__attribute__((naked, noinline))
void FUN_00069420(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ebx\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x120(%%ebx), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LFUN_00069420_3\n\t"
      "pushl $0x28\n\t"
      "movl %%ebx, %%esi\n\t"
      "call *%[c68c70]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $4, %%esp\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LFUN_00069420_1\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00069420_1:\n\t"
      "cmpw $0, 0x4(%%esi)\n\t"
      "jne .LFUN_00069420_2\n\t"
      "movl $0x2ec3c8, 0x1c(%%esi)\n\t"
      "movl $0x2ec4c8, 0x20(%%esi)\n\t"
      "jmp .LFUN_00069420_3\n\t"
      ".LFUN_00069420_2:\n\t"
      "movl $0x2ec4c8, 0x1c(%%esi)\n\t"
      "movl $0x2ec3c8, 0x20(%%esi)\n\t"
      ".LFUN_00069420_3:\n\t"
      "pushl %%edi\n\t"
      "movl 0x18(%%esi), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "movw $8, 0x2(%%esi)\n\t"
      "movw $0, (%%esi)\n\t"
      "movl $0, 0x10(%%esi)\n\t"
      "je .LFUN_00069420_4\n\t"
      "movw 0x4(%%esi), %%ax\n\t"
      "movl 0x8(%%esi), %%ecx\n\t"
      "negw %%ax\n\t"
      "sbbl %%eax, %%eax\n\t"
      "andl $0xff, %%eax\n\t"
      "testl %%ecx, %%ecx\n\t"
      "jle .LFUN_00069420_4\n\t"
      "movb %%al, %%bl\n\t"
      "movb %%bl, %%bh\n\t"
      "movl %%ecx, %%edx\n\t"
      "shrl $2, %%ecx\n\t"
      "movl %%ebx, %%eax\n\t"
      "shll $0x10, %%eax\n\t"
      "movw %%bx, %%ax\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "rep stosl\n\t"
      "movl %%edx, %%ecx\n\t"
      "andl $3, %%ecx\n\t"
      "rep stosb\n\t"
      ".LFUN_00069420_4:\n\t"
      "testb $1, 0x68(%%ebx)\n\t"
      "popl %%edi\n\t"
      "je .LFUN_00069420_7\n\t"
      "cmpw $3, 0x5c(%%ebx)\n\t"
      "flds 0x58(%%ebx)\n\t"
      "jne .LFUN_00069420_5\n\t"
      "fmull 0x260140\n\t"
      "fmull 0x260138\n\t"
      ".LFUN_00069420_5:\n\t"
      "fcomps 0x260134\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "movl $4, %%eax\n\t"
      "je .LFUN_00069420_6\n\t"
      "movl $2, %%eax\n\t"
      ".LFUN_00069420_6:\n\t"
      "movw %%ax, 0x26(%%esi)\n\t"
      "decl %%eax\n\t"
      "movw %%ax, 0x24(%%esi)\n\t"
      "popl %%esi\n\t"
      "movl $1, %%eax\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00069420_7:\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw %%ax, 0x26(%%esi)\n\t"
      "movw %%ax, 0x24(%%esi)\n\t"
      "popl %%esi\n\t"
      "movl $1, %%eax\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c68c70] "m"(b69420_c68c70)
      : "memory");
}
#else
#error "FUN_00069420: clang naked draft required"
#endif


/* FUN_00069520 (0x69520) — Capstone lift: emit one LZW code byte to stream. */
int FUN_00069520(void *tif)
{
  unsigned char *state;
  int rem;
  int cap;
  unsigned char *buf;
  unsigned char *map;
  short code;

  state = *(unsigned char **)((char *)tif + 0x120);
  if (*(short *)(state + 2) == 8)
    return 1;

  rem = *(int *)((char *)tif + 0x138);
  cap = *(int *)((char *)tif + 0x130);
  if (rem >= cap)
    TIFFFlushData1(tif);

  code = *(short *)state;
  map = *(unsigned char **)(state + 0x14);
  buf = *(unsigned char **)((char *)tif + 0x134);
  *buf = map[(unsigned short)code];
  *(int *)((char *)tif + 0x134) = *(int *)((char *)tif + 0x134) + 1;
  *(int *)((char *)tif + 0x138) = *(int *)((char *)tif + 0x138) + 1;
  *(short *)state = 0;
  *(short *)(state + 2) = 8;
  return 1;
}


/* FUN_00069590 (0x69590) — readable C lift. */
void FUN_00069590(unsigned char *tif)
{
  int i;
  if (*(unsigned char *)(tif + 9) & 1)
    return;
  for (i = 0; i < 6; i++)
    ((void (*)(void *))FUN_000693b0)(tif);
  ((void (*)(void *))FUN_00069520)(tif);
}

/* FUN_000695c0 (0x695c0) — readable C lift. */
void FUN_000695c0(unsigned char *tif)
{
  extern char DAT_00260058[];
  void *p;
  p = *(void **)(tif + 0x120);
  if (p) {
    debug_free(p, DAT_00260058, 0x435);
    *(void **)(tif + 0x120) = 0;
  }
}

/* FUN_00069600 (0x69600) — Capstone lift: bit-run length via table@<ebx>.
 * ABI: pp stack, bitpos@<ecx>, endbit@<edx>, table@<ebx>.
 * Returns run length; advances *pp past consumed whole bytes. */
int FUN_00069600(unsigned char **pp, int bitpos /*@<ecx>*/, int endbit /*@<edx>*/,
                 const unsigned char *table /*@<ebx>*/)
{
  unsigned char *p;
  int rem;
  int n;
  int span;
  int c;

  p = *pp;
  rem = endbit - bitpos;
  if (rem <= 0) {
    n = 0;
  } else {
    bitpos &= 7;
    if (bitpos == 0) {
      n = 0;
    } else {
      n = (int)table[((unsigned)p[0] << bitpos) & 0xff];
      span = 8 - bitpos;
      if (n > span)
        n = span;
      if (n > rem)
        n = rem;
      bitpos += n;
      if (bitpos < 8) {
        *pp = p;
        return n;
      }
      rem -= n;
      p++;
    }
  }
  while (rem >= 8) {
    c = (int)table[p[0]];
    n += c;
    rem -= c;
    if (c < 8)
      goto done;
    p++;
  }
  if (rem > 0) {
    c = (int)table[p[0]];
    if (c > rem)
      c = rem;
    n += c;
  }
done:
  *pp = p;
  return n;
}

/* FUN_00069690 (0x69690) — Capstone/WT lift.
 * ABI: buf/flag on stack; bit@esi; end@edx. Calls FUN_00069600 (cdecl in C). */
int FUN_00069690(unsigned char *buf, int flag, int bit, int end)
{
  unsigned char *p = buf + (bit >> 3);
  const unsigned char *table =
      flag ? (const unsigned char *)0x2ec4c8u : (const unsigned char *)0x2ec3c8u;
  int got = FUN_00069600(&p, (unsigned)bit, (unsigned)end, table);
  return got + bit;
}



/* FUN_000696d0 (0x696d0) — XBE naked draft (batch 297). */
#if defined(__clang__)
static void (*const b696d0_c69600)(void) = (void (*)(void))FUN_00069600;
static void (*const b696d0_c68e20)(void) = (void (*)(void))FUN_00068e20;
static void (*const b696d0_c68eb0)(void) = (void (*)(void))FUN_00068eb0;
static void (*const b696d0_c68f60)(void) = (void (*)(void))FUN_00068f60;
static void (*const b696d0_c69180)(void) = (void (*)(void))FUN_00069180;
static void (*const b696d0_c68bd0)(void) = (void (*)(void))FUN_00068bd0;
static void (*const b696d0_c6f9d0)(void) = (void (*)(void))FUN_0006f9d0;
static void (*const b696d0_c68a70)(void) = (void (*)(void))FUN_00068a70;
static void (*const b696d0_c68a30)(int param_1, const char *format, ...) = (void (*)(int, const char *, ...))FUN_00068a30;

__attribute__((naked, noinline))
void FUN_000696d0(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x14, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "movl 0x120(%%edi), %%ebx\n\t"
      "orl $0xffffffff, %%esi\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x4(%%ebx), %%dx\n\t"
      "movl %%ebx, -0xc(%%ebp)\n\t"
      "movl %%esi, -0x8(%%ebp)\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      ".LFUN_000696d0_1:\n\t"
      "movw 0x2(%%ebx), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "je .LFUN_000696d0_2\n\t"
      "cmpw $7, %%ax\n\t"
      "jle .LFUN_000696d0_3\n\t"
      ".LFUN_000696d0_2:\n\t"
      "movl 0x138(%%edi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jle .LFUN_000696d0_34\n\t"
      "decl %%eax\n\t"
      "movl %%eax, 0x138(%%edi)\n\t"
      "movl 0x134(%%edi), %%eax\n\t"
      "movzbl (%%eax), %%ecx\n\t"
      "movl 0x14(%%ebx), %%eax\n\t"
      "movzbw (%%eax,%%ecx,1), %%cx\n\t"
      "movw %%cx, (%%ebx)\n\t"
      "incl 0x134(%%edi)\n\t"
      ".LFUN_000696d0_3:\n\t"
      "movswl 0x2(%%ebx), %%eax\n\t"
      "movswl (%%ebx), %%ecx\n\t"
      "shll $8, %%eax\n\t"
      "addl %%ecx, %%eax\n\t"
      "movzbw 0x2ca770(%%eax), %%cx\n\t"
      "movzbw 0x2cbb70(%%eax), %%ax\n\t"
      "movw %%ax, 0x2(%%ebx)\n\t"
      "movswl %%cx, %%eax\n\t"
      "cmpl $0xc, %%eax\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "ja .LFUN_000696d0_42\n\t"
      "jmp *.LFUN_000696d0_jt0(,%%eax,4)\n\t"
      ".LFUN_000696d0_4:\n\t"
      "movl 0x18(%%ebx), %%ebx\n\t"
      "movl %%esi, %%ecx\n\t"
      "sarl $3, %%ecx\n\t"
      "addl %%ebx, %%ecx\n\t"
      "testw %%dx, %%dx\n\t"
      "movl %%ebx, -0x8(%%ebp)\n\t"
      "movl %%ecx, -0x10(%%ebp)\n\t"
      "movl $0x2ec4c8, %%ebx\n\t"
      "je .LFUN_000696d0_5\n\t"
      "movl $0x2ec3c8, %%ebx\n\t"
      ".LFUN_000696d0_5:\n\t"
      "leal -0x10(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "movl %%esi, %%ecx\n\t"
      "call *%[c69600]\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movl %%eax, %%edi\n\t"
      "addl %%esi, %%edi\n\t"
      "movl %%edi, %%eax\n\t"
      "sarl $3, %%eax\n\t"
      "addl %%ecx, %%eax\n\t"
      "addl $4, %%esp\n\t"
      "cmpw $0, -0x4(%%ebp)\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "movl $0x2ec4c8, %%ebx\n\t"
      "jne .LFUN_000696d0_6\n\t"
      "movl $0x2ec3c8, %%ebx\n\t"
      ".LFUN_000696d0_6:\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "leal -0x10(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl %%edi, %%ecx\n\t"
      "call *%[c69600]\n\t"
      "addl %%edi, %%eax\n\t"
      "movl -0x8(%%ebp), %%edi\n\t"
      "movl %%eax, %%edx\n\t"
      "sarl $3, %%edx\n\t"
      "addl %%edi, %%edx\n\t"
      "movl -0x4(%%ebp), %%edi\n\t"
      "addl $4, %%esp\n\t"
      "testw %%di, %%di\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "movl %%edx, -0x10(%%ebp)\n\t"
      "movl $0x2ec4c8, %%ebx\n\t"
      "je .LFUN_000696d0_7\n\t"
      "movl $0x2ec3c8, %%ebx\n\t"
      ".LFUN_000696d0_7:\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "leal -0x10(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl %%eax, %%ecx\n\t"
      "call *%[c69600]\n\t"
      "movl -0x14(%%ebp), %%ecx\n\t"
      "movl %%eax, %%ebx\n\t"
      "addl $4, %%esp\n\t"
      "addl %%ecx, %%ebx\n\t"
      "testw %%di, %%di\n\t"
      "je .LFUN_000696d0_9\n\t"
      "testl %%esi, %%esi\n\t"
      "jge .LFUN_000696d0_8\n\t"
      "xorl %%esi, %%esi\n\t"
      ".LFUN_000696d0_8:\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "movl %%ebx, %%edx\n\t"
      "subl %%esi, %%edx\n\t"
      "movl %%esi, %%ecx\n\t"
      "call *%[c68e20]\n\t"
      ".LFUN_000696d0_9:\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "movl %%ebx, %%esi\n\t"
      "movl -0xc(%%ebp), %%ebx\n\t"
      "movl %%esi, -0x8(%%ebp)\n\t"
      "jmp .LFUN_000696d0_33\n\t"
      ".LFUN_000696d0_10:\n\t"
      "cmpw 0x4(%%ebx), %%dx\n\t"
      "jne .LFUN_000696d0_11\n\t"
      "call *%[c68eb0]\n\t"
      "movl %%eax, %%ebx\n\t"
      "call *%[c68f60]\n\t"
      "jmp .LFUN_000696d0_12\n\t"
      ".LFUN_000696d0_11:\n\t"
      "call *%[c68f60]\n\t"
      "movl %%eax, %%ebx\n\t"
      "call *%[c68eb0]\n\t"
      ".LFUN_000696d0_12:\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "jge .LFUN_000696d0_13\n\t"
      "xorl %%esi, %%esi\n\t"
      ".LFUN_000696d0_13:\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "leal (%%ebx,%%esi,1), %%edx\n\t"
      "cmpl %%eax, %%edx\n\t"
      "jle .LFUN_000696d0_14\n\t"
      "movl %%eax, %%ebx\n\t"
      "subl %%esi, %%ebx\n\t"
      ".LFUN_000696d0_14:\n\t"
      "cmpw $0, -0x4(%%ebp)\n\t"
      "je .LFUN_000696d0_15\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "movl %%ebx, %%edx\n\t"
      "movl %%esi, %%ecx\n\t"
      "call *%[c68e20]\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      ".LFUN_000696d0_15:\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "addl %%ebx, %%esi\n\t"
      "addl %%esi, %%ecx\n\t"
      "cmpl %%eax, %%ecx\n\t"
      "jle .LFUN_000696d0_16\n\t"
      "subl %%esi, %%eax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      ".LFUN_000696d0_16:\n\t"
      "cmpw $0, -0x4(%%ebp)\n\t"
      "jne .LFUN_000696d0_17\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "movl %%esi, %%ecx\n\t"
      "call *%[c68e20]\n\t"
      ".LFUN_000696d0_17:\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movl -0xc(%%ebp), %%ebx\n\t"
      "addl %%eax, %%esi\n\t"
      "movl %%esi, -0x8(%%ebp)\n\t"
      "jmp .LFUN_000696d0_33\n\t"
      ".LFUN_000696d0_18:\n\t"
      "movl 0x18(%%ebx), %%ebx\n\t"
      "movl %%esi, %%eax\n\t"
      "sarl $3, %%eax\n\t"
      "addl %%ebx, %%eax\n\t"
      "testw %%dx, %%dx\n\t"
      "movl %%ebx, -0x8(%%ebp)\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "movl $0x2ec4c8, %%ebx\n\t"
      "je .LFUN_000696d0_19\n\t"
      "movl $0x2ec3c8, %%ebx\n\t"
      ".LFUN_000696d0_19:\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "leal -0x14(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl %%esi, %%ecx\n\t"
      "call *%[c69600]\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movl %%eax, %%edi\n\t"
      "addl %%esi, %%edi\n\t"
      "movl %%edi, %%edx\n\t"
      "sarl $3, %%edx\n\t"
      "addl %%ecx, %%edx\n\t"
      "addl $4, %%esp\n\t"
      "cmpw $0, -0x4(%%ebp)\n\t"
      "movl %%edx, -0x14(%%ebp)\n\t"
      "movl $0x2ec4c8, %%ebx\n\t"
      "jne .LFUN_000696d0_20\n\t"
      "movl $0x2ec3c8, %%ebx\n\t"
      ".LFUN_000696d0_20:\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "leal -0x14(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl %%edi, %%ecx\n\t"
      "call *%[c69600]\n\t"
      "movl -0x10(%%ebp), %%ecx\n\t"
      "movl -0x4(%%ebp), %%ebx\n\t"
      "addl %%edi, %%ecx\n\t"
      "addl $4, %%esp\n\t"
      "testw %%bx, %%bx\n\t"
      "leal -0x6(%%eax,%%ecx,1), %%edi\n\t"
      "je .LFUN_000696d0_22\n\t"
      "testl %%esi, %%esi\n\t"
      "jge .LFUN_000696d0_21\n\t"
      "xorl %%esi, %%esi\n\t"
      ".LFUN_000696d0_21:\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "movl %%edi, %%edx\n\t"
      "subl %%esi, %%edx\n\t"
      "movl %%esi, %%ecx\n\t"
      "call *%[c68e20]\n\t"
      ".LFUN_000696d0_22:\n\t"
      "xorl %%edx, %%edx\n\t"
      "testw %%bx, %%bx\n\t"
      "movl -0xc(%%ebp), %%ebx\n\t"
      "sete %%dl\n\t"
      "movl %%edi, %%esi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "movl %%esi, -0x8(%%ebp)\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      "jmp .LFUN_000696d0_33\n\t"
      ".LFUN_000696d0_23:\n\t"
      "testl %%esi, %%esi\n\t"
      "jge .LFUN_000696d0_24\n\t"
      "xorl %%esi, %%esi\n\t"
      "movl %%esi, -0x8(%%ebp)\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".LFUN_000696d0_24:\n\t"
      "movl %%edi, %%edx\n\t"
      "call *%[c69180]\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "movswl %%ax, %%eax\n\t"
      "leal -0x2(%%eax), %%ecx\n\t"
      "cmpl $0xc, %%ecx\n\t"
      "ja .LFUN_000696d0_32\n\t"
      "movzbl 0x69b78(%%ecx), %%ecx\n\t"
      "jmp *.LFUN_000696d0_jt1(,%%ecx,4)\n\t"
      ".LFUN_000696d0_25:\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "leal -0x2(%%eax,%%esi,1), %%ecx\n\t"
      "movl %%ecx, %%edx\n\t"
      "sarl $3, %%edx\n\t"
      "addl %%edi, %%edx\n\t"
      "andl $7, %%ecx\n\t"
      "movl $1, %%ebx\n\t"
      "je .LFUN_000696d0_27\n\t"
      "movl $8, %%eax\n\t"
      "subl %%ecx, %%eax\n\t"
      "cmpl %%ebx, %%eax\n\t"
      "jle .LFUN_000696d0_26\n\t"
      "movb 0x2ec379, %%al\n\t"
      "shrb %%cl, %%al\n\t"
      "jmp .LFUN_000696d0_28\n\t"
      ".LFUN_000696d0_26:\n\t"
      "movb (%%edx), %%bl\n\t"
      "movl $0xff, %%eax\n\t"
      "sarl %%cl, %%eax\n\t"
      "orb %%al, %%bl\n\t"
      "movb %%bl, (%%edx)\n\t"
      "leal -0x7(%%ecx), %%ebx\n\t"
      "incl %%edx\n\t"
      "cmpl $8, %%ebx\n\t"
      "movl %%ebx, -0x14(%%ebp)\n\t"
      "jl .LFUN_000696d0_27\n\t"
      "shrl $3, %%ebx\n\t"
      "movl %%ebx, %%ecx\n\t"
      "movl %%ecx, %%esi\n\t"
      "shrl $2, %%ecx\n\t"
      "orl $0xffffffff, %%eax\n\t"
      "movl %%edx, %%edi\n\t"
      "rep stosl\n\t"
      "movl %%esi, %%ecx\n\t"
      "movl -0x8(%%ebp), %%esi\n\t"
      "andl $3, %%ecx\n\t"
      "addl %%ebx, %%edx\n\t"
      "rep stosb\n\t"
      "movl -0x14(%%ebp), %%ecx\n\t"
      "negl %%ebx\n\t"
      "leal (%%ecx,%%ebx,8), %%ebx\n\t"
      ".LFUN_000696d0_27:\n\t"
      "movb 0x2ec378(%%ebx), %%al\n\t"
      ".LFUN_000696d0_28:\n\t"
      "movb (%%edx), %%cl\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "movl -0xc(%%ebp), %%ebx\n\t"
      "orb %%al, %%cl\n\t"
      "movswl -0x10(%%ebp), %%eax\n\t"
      "leal -0x1(%%eax,%%esi,1), %%esi\n\t"
      "movb %%cl, (%%edx)\n\t"
      "movl %%esi, -0x8(%%ebp)\n\t"
      "jmp .LFUN_000696d0_32\n\t"
      ".LFUN_000696d0_29:\n\t"
      "addl $5, %%esi\n\t"
      "movl %%esi, -0x8(%%ebp)\n\t"
      "jmp .LFUN_000696d0_32\n\t"
      ".LFUN_000696d0_30:\n\t"
      "leal -0x8(%%esi,%%eax,1), %%esi\n\t"
      "movl %%edi, %%eax\n\t"
      "movl %%esi, -0x8(%%ebp)\n\t"
      "call *%[c68bd0]\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_000696d0_31\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "cmpw %%cx, 0x4(%%ebx)\n\t"
      "sete %%cl\n\t"
      "movl %%ecx, -0x4(%%ebp)\n\t"
      "jmp .LFUN_000696d0_32\n\t"
      ".LFUN_000696d0_31:\n\t"
      "movw 0x4(%%ebx), %%dx\n\t"
      "movw %%dx, -0x4(%%ebp)\n\t"
      ".LFUN_000696d0_32:\n\t"
      "cmpw $8, -0x10(%%ebp)\n\t"
      "jl .LFUN_000696d0_24\n\t"
      ".LFUN_000696d0_33:\n\t"
      "cmpl 0x10(%%ebp), %%esi\n\t"
      "jge .LFUN_000696d0_40\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "jmp .LFUN_000696d0_1\n\t"
      ".LFUN_000696d0_34:\n\t"
      "movl 0xd4(%%edi), %%eax\n\t"
      "movl (%%edi), %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x2601cc\n\t"
      "jmp .LFUN_000696d0_43\n\t"
      ".LFUN_000696d0_35:\n\t"
      "movl 0xd4(%%edi), %%edx\n\t"
      "movl (%%edi), %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl $0x26019c\n\t"
      "jmp .LFUN_000696d0_39\n\t"
      ".LFUN_000696d0_36:\n\t"
      "movl 0xd4(%%edi), %%ecx\n\t"
      "movl (%%edi), %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x2601cc\n\t"
      "jmp .LFUN_000696d0_43\n\t"
      ".LFUN_000696d0_37:\n\t"
      "testb $2, 0x9(%%edi)\n\t"
      "jne .LFUN_000696d0_38\n\t"
      "movl 0xd4(%%edi), %%eax\n\t"
      "movl (%%edi), %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x2600e4\n\t"
      "pushl $0x2ec394\n\t"
      "call *%[c6f9d0]\n\t"
      "addl $0x14, %%esp\n\t"
      "movl $7, %%eax\n\t"
      "call *%[c68a70]\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl $1, %%eax\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000696d0_38:\n\t"
      "movl 0xd4(%%edi), %%edx\n\t"
      "movl (%%edi), %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl $0x260178\n\t"
      ".LFUN_000696d0_39:\n\t"
      "pushl $0x2ec394\n\t"
      "call *%[c68a30]\n\t"
      "addl $0x10, %%esp\n\t"
      ".LFUN_000696d0_40:\n\t"
      "testb $2, 0x9(%%edi)\n\t"
      "jne .LFUN_000696d0_41\n\t"
      "xorl %%eax, %%eax\n\t"
      "call *%[c68a70]\n\t"
      ".LFUN_000696d0_41:\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "xorl %%eax, %%eax\n\t"
      "popl %%edi\n\t"
      "cmpl %%ecx, %%esi\n\t"
      "popl %%esi\n\t"
      "setge %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000696d0_42:\n\t"
      "movl 0xd4(%%edi), %%ecx\n\t"
      "movl (%%edi), %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x260148\n\t"
      ".LFUN_000696d0_43:\n\t"
      "pushl $0x2ec394\n\t"
      "call *%[c68a30]\n\t"
      "addl $0x10, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "xorl %%eax, %%eax\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_000696d0_jt0:\n\t"
      ".long .LFUN_000696d0_33\n\t"
      ".long .LFUN_000696d0_4\n\t"
      ".long .LFUN_000696d0_10\n\t"
      ".long .LFUN_000696d0_18\n\t"
      ".long .LFUN_000696d0_18\n\t"
      ".long .LFUN_000696d0_18\n\t"
      ".long .LFUN_000696d0_18\n\t"
      ".long .LFUN_000696d0_18\n\t"
      ".long .LFUN_000696d0_18\n\t"
      ".long .LFUN_000696d0_18\n\t"
      ".long .LFUN_000696d0_23\n\t"
      ".long .LFUN_000696d0_38\n\t"
      ".long .LFUN_000696d0_37\n\t"
      ".text\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_000696d0_jt1:\n\t"
      ".long .LFUN_000696d0_25\n\t"
      ".long .LFUN_000696d0_29\n\t"
      ".long .LFUN_000696d0_30\n\t"
      ".long .LFUN_000696d0_36\n\t"
      ".long .LFUN_000696d0_35\n\t"
      ".text\n\t"
      :
      : [c69600] "m"(b696d0_c69600), [c68e20] "m"(b696d0_c68e20), [c68eb0] "m"(b696d0_c68eb0), [c68f60] "m"(b696d0_c68f60), [c69180] "m"(b696d0_c69180), [c68bd0] "m"(b696d0_c68bd0), [c6f9d0] "m"(b696d0_c6f9d0), [c68a70] "m"(b696d0_c68a70), [c68a30] "m"(b696d0_c68a30)
      : "memory");
}
#else
#error "FUN_000696d0: clang naked draft required"
#endif


/* FUN_00069b90 (0x69b90) — XBE naked draft (batch 335). */
#if defined(__clang__)
static void (*const b69b90_c69600)(void) = (void (*)(void))FUN_00069600;
static void (*const b69b90_c69310)(void) = (void (*)(void))FUN_00069310;

__attribute__((naked, noinline))
void FUN_00069b90(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $8, %%esp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl 0x120(%%eax), %%eax\n\t"
      "pushl %%ebx\n\t"
      "movl 0x1c(%%eax), %%ebx\n\t"
      "leal 0xc(%%ebp), %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%ecx\n\t"
      "movl %%edi, %%edx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "call *%[c69600]\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "addl $4, %%esp\n\t"
      "movl $0x2ca250, %%ebx\n\t"
      "movl %%eax, %%esi\n\t"
      "call *%[c69310]\n\t"
      "cmpl %%edi, %%esi\n\t"
      "jge .LFUN_00069b90_2\n\t"
      "leal (%%ebx), %%ebx\n\t"
      ".LFUN_00069b90_1:\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movl 0x20(%%eax), %%ebx\n\t"
      "leal 0xc(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl %%edi, %%edx\n\t"
      "movl %%esi, %%ecx\n\t"
      "call *%[c69600]\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "addl $4, %%esp\n\t"
      "movl $0x2ca4e0, %%ebx\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "call *%[c69310]\n\t"
      "addl -0x4(%%ebp), %%esi\n\t"
      "cmpl %%edi, %%esi\n\t"
      "jge .LFUN_00069b90_2\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "movl 0x1c(%%edx), %%ebx\n\t"
      "leal 0xc(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl %%edi, %%edx\n\t"
      "movl %%esi, %%ecx\n\t"
      "call *%[c69600]\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "addl $4, %%esp\n\t"
      "movl $0x2ca250, %%ebx\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "call *%[c69310]\n\t"
      "addl -0x4(%%ebp), %%esi\n\t"
      "cmpl %%edi, %%esi\n\t"
      "jl .LFUN_00069b90_1\n\t"
      ".LFUN_00069b90_2:\n\t"
      "popl %%esi\n\t"
      "movl $1, %%eax\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c69600] "m"(b69b90_c69600), [c69310] "m"(b69b90_c69310)
      : "memory");
}
#else
#error "FUN_00069b90: clang naked draft required"
#endif


/* FUN_00069c40 (0x69c40) — XBE naked draft (batch 299). */
#if defined(__clang__)
static void (*const b69c40_c69600)(void) = (void (*)(void))FUN_00069600;
static void (*const b69c40_c69200)(void) = (void (*)(void))FUN_00069200;
static void (*const b69c40_c69310)(void) = (void (*)(void))FUN_00069310;

__attribute__((naked, noinline))
void FUN_00069c40(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x18, %%esp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl 0x120(%%eax), %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movw 0x4(%%ecx), %%si\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "pushl %%edi\n\t"
      "movzbl (%%ecx), %%edi\n\t"
      "movswl %%si, %%eax\n\t"
      "xorl %%edx, %%edx\n\t"
      "shrl $7, %%edi\n\t"
      "cmpl %%eax, %%edi\n\t"
      "movl %%edx, -0x8(%%ebp)\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "je .LFUN_00069c40_1\n\t"
      "movl %%edx, -0xc(%%ebp)\n\t"
      "jmp .LFUN_00069c40_3\n\t"
      ".LFUN_00069c40_1:\n\t"
      "cmpw %%dx, %%si\n\t"
      "movl %%ecx, -0x10(%%ebp)\n\t"
      "movl $0x2ec4c8, %%ebx\n\t"
      "jne .LFUN_00069c40_2\n\t"
      "movl $0x2ec3c8, %%ebx\n\t"
      ".LFUN_00069c40_2:\n\t"
      "leal -0x10(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl 0x14(%%ebp), %%edx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "call *%[c69600]\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_00069c40_3:\n\t"
      "movl 0x10(%%ebp), %%edi\n\t"
      "movzbl (%%edi), %%ecx\n\t"
      "shrl $7, %%ecx\n\t"
      "cmpl %%eax, %%ecx\n\t"
      "je .LFUN_00069c40_4\n\t"
      "xorl %%eax, %%eax\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "jmp .LFUN_00069c40_7\n\t"
      ".LFUN_00069c40_4:\n\t"
      "testw %%si, %%si\n\t"
      "movl %%edi, -0x10(%%ebp)\n\t"
      "movl $0x2ec4c8, %%ebx\n\t"
      "jne .LFUN_00069c40_5\n\t"
      "movl $0x2ec3c8, %%ebx\n\t"
      ".LFUN_00069c40_5:\n\t"
      "leal -0x10(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl 0x14(%%ebp), %%edx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "call *%[c69600]\n\t"
      "addl $4, %%esp\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      ".LFUN_00069c40_6:\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_00069c40_7:\n\t"
      "movl %%eax, %%ecx\n\t"
      "sarl $3, %%ecx\n\t"
      "leal (%%ecx,%%edi,1), %%edx\n\t"
      "movb %%al, %%bl\n\t"
      "andb $7, %%bl\n\t"
      "movl %%edx, -0x18(%%ebp)\n\t"
      "movb (%%edx), %%dl\n\t"
      "movb $7, %%cl\n\t"
      "subb %%bl, %%cl\n\t"
      "shrb %%cl, %%dl\n\t"
      "movl $0x2ec4c8, %%ebx\n\t"
      "testb $1, %%dl\n\t"
      "jne .LFUN_00069c40_8\n\t"
      "movl $0x2ec3c8, %%ebx\n\t"
      ".LFUN_00069c40_8:\n\t"
      "movl 0x14(%%ebp), %%edx\n\t"
      "leal -0x18(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl %%eax, %%ecx\n\t"
      "call *%[c69600]\n\t"
      "movl -0xc(%%ebp), %%ebx\n\t"
      "movl %%eax, %%esi\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "addl %%eax, %%esi\n\t"
      "addl $4, %%esp\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "jl .LFUN_00069c40_13\n\t"
      "subl %%ebx, %%eax\n\t"
      "cmpl $-3, %%eax\n\t"
      "jl .LFUN_00069c40_9\n\t"
      "cmpl $3, %%eax\n\t"
      "jg .LFUN_00069c40_9\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "leal (%%eax,%%eax,2), %%ecx\n\t"
      "movzwl 0x2ec5ec(,%%ecx,2), %%edx\n\t"
      "movzwl 0x2ec5ea(,%%ecx,2), %%eax\n\t"
      "leal 0x2ec5ea(,%%ecx,2), %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c69200]\n\t"
      "movl %%ebx, %%eax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "jmp .LFUN_00069c40_14\n\t"
      ".LFUN_00069c40_9:\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "movl %%ebx, %%eax\n\t"
      "sarl $3, %%eax\n\t"
      "movb (%%eax,%%ecx,1), %%dl\n\t"
      "addl %%ecx, %%eax\n\t"
      "andb $7, %%bl\n\t"
      "movb $7, %%cl\n\t"
      "subb %%bl, %%cl\n\t"
      "shrb %%cl, %%dl\n\t"
      "movl %%eax, -0x18(%%ebp)\n\t"
      "movl $0x2ec4c8, %%ebx\n\t"
      "testb $1, %%dl\n\t"
      "jne .LFUN_00069c40_10\n\t"
      "movl $0x2ec3c8, %%ebx\n\t"
      ".LFUN_00069c40_10:\n\t"
      "movl 0x14(%%ebp), %%edx\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "leal -0x18(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c69600]\n\t"
      "movzwl 0x2ec5ca, %%ecx\n\t"
      "movl -0xc(%%ebp), %%ebx\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "movl %%eax, %%esi\n\t"
      "movzwl 0x2ec5c8, %%eax\n\t"
      "pushl %%ecx\n\t"
      "addl %%ebx, %%esi\n\t"
      "call *%[c69200]\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "leal (%%ebx,%%edx,1), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_00069c40_11\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movb %%dl, %%al\n\t"
      "andb $7, %%al\n\t"
      "movb $7, %%cl\n\t"
      "subb %%al, %%cl\n\t"
      "movl %%edx, %%eax\n\t"
      "sarl $3, %%eax\n\t"
      "movzbl (%%eax,%%edi,1), %%eax\n\t"
      "shrl %%cl, %%eax\n\t"
      "movl -0x14(%%ebp), %%ecx\n\t"
      "andl $1, %%eax\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "je .LFUN_00069c40_11\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "movl %%ebx, %%eax\n\t"
      "subl %%edx, %%eax\n\t"
      "movl $0x2ca4e0, %%ebx\n\t"
      "movl %%edi, %%ecx\n\t"
      "call *%[c69310]\n\t"
      "movl $0x2ca250, %%ebx\n\t"
      "jmp .LFUN_00069c40_12\n\t"
      ".LFUN_00069c40_11:\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "movl %%ebx, %%eax\n\t"
      "subl %%edx, %%eax\n\t"
      "movl $0x2ca250, %%ebx\n\t"
      "movl %%edi, %%ecx\n\t"
      "call *%[c69310]\n\t"
      "movl $0x2ca4e0, %%ebx\n\t"
      ".LFUN_00069c40_12:\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "movl %%esi, %%eax\n\t"
      "subl %%ecx, %%eax\n\t"
      "movl %%edi, %%ecx\n\t"
      "call *%[c69310]\n\t"
      "movl %%esi, -0x8(%%ebp)\n\t"
      "movl %%esi, %%eax\n\t"
      "jmp .LFUN_00069c40_15\n\t"
      ".LFUN_00069c40_13:\n\t"
      "movzwl 0x2ec5d2, %%ecx\n\t"
      "movzwl 0x2ec5d0, %%eax\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "pushl %%ecx\n\t"
      "call *%[c69200]\n\t"
      "movl %%esi, -0x8(%%ebp)\n\t"
      "movl %%esi, %%eax\n\t"
      ".LFUN_00069c40_14:\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_00069c40_15:\n\t"
      "cmpl 0x14(%%ebp), %%eax\n\t"
      "jge .LFUN_00069c40_19\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "movl %%eax, %%edi\n\t"
      "sarl $3, %%edi\n\t"
      "leal (%%edi,%%edx,1), %%esi\n\t"
      "movb %%al, %%dl\n\t"
      "andb $7, %%dl\n\t"
      "movb $7, %%cl\n\t"
      "subb %%dl, %%cl\n\t"
      "movb (%%esi), %%dl\n\t"
      "movb %%dl, -0x1(%%ebp)\n\t"
      "shrb %%cl, %%dl\n\t"
      "movl %%esi, -0x18(%%ebp)\n\t"
      "movb %%cl, -0x2(%%ebp)\n\t"
      "movl $0x2ec4c8, %%ebx\n\t"
      "andb $1, %%dl\n\t"
      "movb %%dl, -0x3(%%ebp)\n\t"
      "jne .LFUN_00069c40_16\n\t"
      "movl $0x2ec3c8, %%ebx\n\t"
      ".LFUN_00069c40_16:\n\t"
      "movl 0x14(%%ebp), %%esi\n\t"
      "leal -0x18(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl %%esi, %%edx\n\t"
      "movl %%eax, %%ecx\n\t"
      "call *%[c69600]\n\t"
      "movl -0x8(%%ebp), %%ebx\n\t"
      "movb -0x2(%%ebp), %%cl\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "addl %%ebx, %%eax\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "movzbl -0x1(%%ebp), %%eax\n\t"
      "shrl %%cl, %%eax\n\t"
      "addl %%edx, %%edi\n\t"
      "addl $4, %%esp\n\t"
      "movl %%edi, -0x18(%%ebp)\n\t"
      "notl %%eax\n\t"
      "testb $1, %%al\n\t"
      "movl $0x2ec4c8, %%ebx\n\t"
      "jne .LFUN_00069c40_17\n\t"
      "movl $0x2ec3c8, %%ebx\n\t"
      ".LFUN_00069c40_17:\n\t"
      "leal -0x18(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movl %%esi, %%edx\n\t"
      "call *%[c69600]\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movl 0x10(%%ebp), %%edi\n\t"
      "addl %%ecx, %%eax\n\t"
      "movb -0x3(%%ebp), %%cl\n\t"
      "movl %%eax, %%edx\n\t"
      "sarl $3, %%edx\n\t"
      "addl %%edi, %%edx\n\t"
      "addl $4, %%esp\n\t"
      "testb %%cl, %%cl\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "movl %%edx, -0x18(%%ebp)\n\t"
      "movl $0x2ec4c8, %%ebx\n\t"
      "jne .LFUN_00069c40_18\n\t"
      "movl $0x2ec3c8, %%ebx\n\t"
      ".LFUN_00069c40_18:\n\t"
      "leal -0x18(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl %%esi, %%edx\n\t"
      "movl %%eax, %%ecx\n\t"
      "call *%[c69600]\n\t"
      "movl -0x10(%%ebp), %%ecx\n\t"
      "movl 0x10(%%ebp), %%edi\n\t"
      "addl $4, %%esp\n\t"
      "addl %%eax, %%ecx\n\t"
      "movl %%ecx, -0x10(%%ebp)\n\t"
      "jmp .LFUN_00069c40_6\n\t"
      ".LFUN_00069c40_19:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl $1, %%eax\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c69600] "m"(b69c40_c69600), [c69200] "m"(b69c40_c69200), [c69310] "m"(b69c40_c69310)
      : "memory");
}
#else
#error "FUN_00069c40: clang naked draft required"
#endif


/* FUN_00069f30 (0x69f30) — XBE naked draft (batch 326). */
#if defined(__clang__)
static void (*const b69f30_c69200)(void) = (void (*)(void))FUN_00069200;
static void (*const b69f30_c69b90)(void) = (void (*)(void))FUN_00069b90;
static void (*const b69f30_c69c40)(void) = (void (*)(void))FUN_00069c40;
static void * (*const b69f30_c8e0b0)(void *destination, void *source, size_t size) = csmemcpy;

__attribute__((naked, noinline))
void FUN_00069f30(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "pushl %%ebx\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x120(%%ebx), %%esi\n\t"
      "pushl %%edi\n\t"
      "jle .LFUN_00069f30_10\n\t"
      "leal (%%ebx), %%ebx\n\t"
      ".LFUN_00069f30_1:\n\t"
      "testb $4, 0x68(%%ebx)\n\t"
      "movl 0x120(%%ebx), %%eax\n\t"
      "movl %%eax, 0x8(%%ebp)\n\t"
      "je .LFUN_00069f30_4\n\t"
      "movswl 0x2(%%eax), %%eax\n\t"
      "cmpl $4, %%eax\n\t"
      "je .LFUN_00069f30_4\n\t"
      "jge .LFUN_00069f30_2\n\t"
      "addl $4, %%eax\n\t"
      "jmp .LFUN_00069f30_3\n\t"
      ".LFUN_00069f30_2:\n\t"
      "addl $-4, %%eax\n\t"
      ".LFUN_00069f30_3:\n\t"
      "pushl $0\n\t"
      "movl %%ebx, %%edi\n\t"
      "call *%[c69200]\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_00069f30_4:\n\t"
      "pushl $1\n\t"
      "movl $0xc, %%eax\n\t"
      "movl %%ebx, %%edi\n\t"
      "call *%[c69200]\n\t"
      "movb 0x68(%%ebx), %%al\n\t"
      "addl $4, %%esp\n\t"
      "testb $1, %%al\n\t"
      "je .LFUN_00069f30_8\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "movl 0x10(%%ecx), %%edx\n\t"
      "xorl %%eax, %%eax\n\t"
      "testl %%edx, %%edx\n\t"
      "sete %%al\n\t"
      "pushl %%eax\n\t"
      "movl $1, %%eax\n\t"
      "call *%[c69200]\n\t"
      "movb 0x68(%%ebx), %%al\n\t"
      "addl $4, %%esp\n\t"
      "testb $1, %%al\n\t"
      "je .LFUN_00069f30_8\n\t"
      "movl 0x10(%%esi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "jne .LFUN_00069f30_5\n\t"
      "movl 0xc(%%esi), %%edi\n\t"
      "pushl %%edx\n\t"
      "pushl %%ebx\n\t"
      "call *%[c69b90]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_00069f30_11\n\t"
      "movl $1, 0x10(%%esi)\n\t"
      "jmp .LFUN_00069f30_6\n\t"
      ".LFUN_00069f30_5:\n\t"
      "movl 0xc(%%esi), %%eax\n\t"
      "movl 0x18(%%esi), %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ebx\n\t"
      "call *%[c69c40]\n\t"
      "addl $0x10, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_00069f30_11\n\t"
      "decw 0x24(%%esi)\n\t"
      ".LFUN_00069f30_6:\n\t"
      "cmpw $0, 0x24(%%esi)\n\t"
      "jne .LFUN_00069f30_7\n\t"
      "movw 0x26(%%esi), %%ax\n\t"
      "decw %%ax\n\t"
      "movl $0, 0x10(%%esi)\n\t"
      "movw %%ax, 0x24(%%esi)\n\t"
      "jmp .LFUN_00069f30_9\n\t"
      ".LFUN_00069f30_7:\n\t"
      "movl 0x8(%%esi), %%ecx\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "movl 0x18(%%esi), %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c8e0b0]\n\t"
      "addl $0xc, %%esp\n\t"
      "jmp .LFUN_00069f30_9\n\t"
      ".LFUN_00069f30_8:\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "movl 0xc(%%esi), %%edi\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "call *%[c69b90]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_00069f30_11\n\t"
      ".LFUN_00069f30_9:\n\t"
      "movl 0x8(%%esi), %%eax\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "subl %%eax, %%ecx\n\t"
      "addl %%eax, %%edi\n\t"
      "testl %%ecx, %%ecx\n\t"
      "movl %%edi, 0xc(%%ebp)\n\t"
      "movl %%ecx, 0x10(%%ebp)\n\t"
      "jg .LFUN_00069f30_1\n\t"
      ".LFUN_00069f30_10:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl $1, %%eax\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00069f30_11:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "xorl %%eax, %%eax\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c69200] "m"(b69f30_c69200), [c69b90] "m"(b69f30_c69b90), [c69c40] "m"(b69f30_c69c40), [c8e0b0] "m"(b69f30_c8e0b0)
      : "memory");
}
#else
#error "FUN_00069f30: clang naked draft required"
#endif


/* FUN_0006a070 (0x6a070) — XBE naked draft (batch 341). */
#if defined(__clang__)
static void *(*const b6a070_memset)(void *, int, unsigned int) = csmemset;
static void (*const b6a070_c69020)(void) = (void (*)(void))FUN_00069020;
static void (*const b6a070_c696d0)(void) = (void (*)(void))FUN_000696d0;
static void * (*const b6a070_c8e0b0)(void *destination, void *source, size_t size) = csmemcpy;

__attribute__((naked, noinline))
void FUN_0006a070(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "pushl %%ebx\n\t"
      "movl 0xc(%%ebp), %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x120(%%esi), %%edi\n\t"
      "pushl %%eax\n\t"
      "pushl $0\n\t"
      "pushl %%ebx\n\t"
      "call *%[memset]\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jle .LFUN_0006a070_7\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_0006a070_1:\n\t"
      "movl 0x10(%%edi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_0006a070_2\n\t"
      "movl 0xc(%%edi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "movl %%esi, %%eax\n\t"
      "call *%[c69020]\n\t"
      "addl $8, %%esp\n\t"
      "jmp .LFUN_0006a070_3\n\t"
      ".LFUN_0006a070_2:\n\t"
      "movl 0xc(%%edi), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "call *%[c696d0]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_0006a070_3:\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_0006a070_8\n\t"
      "testb $1, 0x68(%%esi)\n\t"
      "je .LFUN_0006a070_6\n\t"
      "movl 0x120(%%esi), %%eax\n\t"
      "cmpw $0, 0x2(%%eax)\n\t"
      "jne .LFUN_0006a070_4\n\t"
      "movl 0x138(%%esi), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "jle .LFUN_0006a070_4\n\t"
      "decl %%ecx\n\t"
      "movl %%ecx, 0x138(%%esi)\n\t"
      "movl 0x134(%%esi), %%ecx\n\t"
      "movzbl (%%ecx), %%edx\n\t"
      "movl 0x14(%%eax), %%ecx\n\t"
      "movzbw (%%ecx,%%edx,1), %%dx\n\t"
      "movw %%dx, (%%eax)\n\t"
      "incl 0x134(%%esi)\n\t"
      ".LFUN_0006a070_4:\n\t"
      "movswl (%%eax), %%ebx\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x2(%%eax), %%dx\n\t"
      "movswl %%dx, %%ecx\n\t"
      "movzbl 0x2ec370(%%ecx), %%ecx\n\t"
      "andl %%ebx, %%ecx\n\t"
      "incl %%edx\n\t"
      "cmpw $7, %%dx\n\t"
      "movw %%dx, 0x2(%%eax)\n\t"
      "jle .LFUN_0006a070_5\n\t"
      "movw $0, 0x2(%%eax)\n\t"
      ".LFUN_0006a070_5:\n\t"
      "movl 0xc(%%ebp), %%ebx\n\t"
      "xorl %%eax, %%eax\n\t"
      "testl %%ecx, %%ecx\n\t"
      "sete %%al\n\t"
      "cmpl $1, %%eax\n\t"
      "movl %%eax, 0x10(%%edi)\n\t"
      "jne .LFUN_0006a070_6\n\t"
      "movl 0x8(%%edi), %%edx\n\t"
      "movl 0x18(%%edi), %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "call *%[c8e0b0]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_0006a070_6:\n\t"
      "movl 0x8(%%edi), %%eax\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "subl %%eax, %%ecx\n\t"
      "addl %%eax, %%ebx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "movl %%ebx, 0xc(%%ebp)\n\t"
      "movl %%ecx, 0x10(%%ebp)\n\t"
      "jg .LFUN_0006a070_1\n\t"
      ".LFUN_0006a070_7:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl $1, %%eax\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0006a070_8:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "xorl %%eax, %%eax\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [memset] "m"(b6a070_memset), [c69020] "m"(b6a070_c69020), [c696d0] "m"(b6a070_c696d0), [c8e0b0] "m"(b6a070_c8e0b0)
      : "memory");
}
#else
#error "FUN_0006a070: clang naked draft required"
#endif


/* FUN_0006a190 (0x6a190) — Capstone lift: install LZW codec vtable on TIFF. */
int FUN_0006a190(void *tif)
{
  unsigned char *t = (unsigned char *)tif;

  *(void **)(t + 0xfc) = (void *)FUN_0006a070;
  *(void **)(t + 0x104) = (void *)FUN_0006a070;
  *(void **)(t + 0x10c) = (void *)FUN_0006a070;
  *(void **)(t + 0x100) = (void *)FUN_00069f30;
  *(void **)(t + 0x108) = (void *)FUN_00069f30;
  *(void **)(t + 0x110) = (void *)FUN_00069f30;
  t[9] = (unsigned char)(t[9] | 1);
  t[0xa] = (unsigned char)(t[0xa] | 0x20);
  *(void **)(t + 0xf0) = (void *)FUN_00068d80;
  *(void **)(t + 0xf4) = (void *)FUN_00069420;
  *(void **)(t + 0xf8) = (void *)FUN_00069520;
  *(void **)(t + 0x114) = (void *)FUN_00069590;
  *(void **)(t + 0x11c) = (void *)FUN_000695c0;
  return 1;
}


/* FUN_0006a210 (0x6a210) — readable C lift. */
int FUN_0006a210(void *tif)
{
  unsigned int flags;
  int (*cb)(void *);
  int (*flush1)(void *) = (int (*)(void *))TIFFFlushData1;

  flags = *(unsigned short *)((char *)tif + 0xa);
  if ((flags & 8) == 0)
    return 0;
  if ((flags & 0x200) != 0) {
    flags &= ~0x200u;
    *(unsigned short *)((char *)tif + 0xa) = (unsigned short)flags;
    cb = *(int (**)(void *))((char *)tif + 0xf8);
    if (cb != NULL && cb(tif) == 0)
      return 0;
  }
  return flush1(tif);
}



/* FUN_0006a260 (0x6a260) — Capstone lift: flush + optional post-write. */
int FUN_0006a260(void *tif)
{
  if (*(short *)((char *)tif + 6) == 0)
    return 1;
  if (((int (*)(void *))FUN_0006a210)(tif) == 0)
    return 0;
  if ((*(unsigned char *)((char *)tif + 0xa) & 2) == 0)
    return 1;
  if (((int (*)(void *))FUN_000680a0)(tif) == 0)
    return 0;
  return 1;
}

/* FUN_0006a2a0 (0x6a2a0) — readable C lift: validate 16-bit sample ranges. */
int FUN_0006a2a0(unsigned short *a, unsigned short *b, unsigned short *c, int n)
{
  extern char DAT_002601f0[];

  if (n > 0) {
    while (n > 0) {
      if (*b >= 0x100 || *a >= 0x100 || *c >= 0x100)
        return 0x10;
      b += 1;
      a += 1;
      c += 1;
      n -= 1;
    }
  }
  FUN_0006f9d0(*(void **)0x3340dc, DAT_002601f0);
  return 8;
}



/* FUN_0006a310 (0x6a310) — XBE naked draft (batch 363). */
#if defined(__clang__)
static int (*const b6a310_c64ec0)(char *prop, int tag, void *out) = (void *)FUN_00064ec0;
static void (*const b6a310_c6f9d0)(void) = (void *)FUN_0006f9d0;

__attribute__((naked, noinline))
void FUN_0006a310(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl $0x3340f0\n\t"
      "pushl $0x112\n\t"
      "pushl %%eax\n\t"
      "call *%[c64ec0]\n\t"
      "movzwl 0x3340f0, %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "decl %%eax\n\t"
      "cmpl $7, %%eax\n\t"
      "ja .LFUN_0006a310_3\n\t"
      "jmp *.LFUN_0006a310_jt(,%%eax,4)\n\t"
      ".LFUN_0006a310_1:\n\t"
      "movl 0x3340dc, %%ecx\n\t"
      "pushl $0x260224\n\t"
      "pushl %%ecx\n\t"
      "call *%[c6f9d0]\n\t"
      "addl $8, %%esp\n\t"
      "movw $4, 0x3340f0\n\t"
      ".LFUN_0006a310_2:\n\t"
      "xorl %%eax, %%eax\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0006a310_3:\n\t"
      "movl 0x3340dc, %%edx\n\t"
      "pushl $0x260208\n\t"
      "pushl %%edx\n\t"
      "call *%[c6f9d0]\n\t"
      "addl $8, %%esp\n\t"
      "movw $1, 0x3340f0\n\t"
      ".LFUN_0006a310_4:\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "decl %%eax\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_0006a310_jt:\n\t"
      ".long .LFUN_0006a310_4\n\t"
      ".long .LFUN_0006a310_3\n\t"
      ".long .LFUN_0006a310_1\n\t"
      ".long .LFUN_0006a310_2\n\t"
      ".long .LFUN_0006a310_3\n\t"
      ".long .LFUN_0006a310_3\n\t"
      ".long .LFUN_0006a310_1\n\t"
      ".long .LFUN_0006a310_1\n\t"
      ".text\n\t"
      :
      : [c64ec0] "m"(b6a310_c64ec0), [c6f9d0] "m"(b6a310_c6f9d0)
      : "memory");
}
#else
#error "FUN_0006a310: clang naked draft required"
#endif


/* FUN_0006a3b0 (0x6a3b0) — XBE naked draft (batch 309). */
#if defined(__clang__)
static void * (*const b6a3b0_c8ee60)(uint32_t size, bool zero, const char *file, int line) = debug_malloc;
static void (*const b6a3b0_c68a30)(int param_1, const char *format, ...) = (void (*)(int, const char *, ...))FUN_00068a30;

__attribute__((naked, noinline))
void FUN_0006a3b0(void)
{
  __asm__ volatile(
      "movzwl 0x3340fc, %%ecx\n\t"
      "movl $8, %%eax\n\t"
      "cdq\n\t"
      "idivl %%ecx\n\t"
      "pushl $0x21a\n\t"
      "pushl $0x260264\n\t"
      "pushl $0\n\t"
      "incl %%eax\n\t"
      "shll $0xa, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c8ee60]\n\t"
      "addl $0x10, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%eax, 0x3340c8\n\t"
      "jne .LFUN_0006a3b0_1\n\t"
      "movl 0x3340dc, %%edx\n\t"
      "pushl $0x260244\n\t"
      "pushl %%edx\n\t"
      "call *%[c68a30]\n\t"
      "addl $8, %%esp\n\t"
      "xorl %%eax, %%eax\n\t"
      "ret\n\t"
      ".LFUN_0006a3b0_1:\n\t"
      "pushl %%ebx\n\t"
      "leal 0x400(%%eax), %%ecx\n\t"
      "xorl %%edx, %%edx\n\t"
      "pushl %%edi\n\t"
      ".LFUN_0006a3b0_2:\n\t"
      "movl %%ecx, (%%eax,%%edx,4)\n\t"
      "movzwl 0x3340fc, %%edi\n\t"
      "decl %%edi\n\t"
      "cmpl $7, %%edi\n\t"
      "ja .LFUN_0006a3b0_8\n\t"
      "jmp *.LFUN_0006a3b0_jt(,%%edi,4)\n\t"
      ".LFUN_0006a3b0_3:\n\t"
      "movl %%edx, %%edi\n\t"
      "sarl $7, %%edi\n\t"
      "movzbl (%%edi,%%esi,1), %%edi\n\t"
      "movl %%edi, %%ebx\n\t"
      "shll $8, %%ebx\n\t"
      "orl %%edi, %%ebx\n\t"
      "shll $8, %%ebx\n\t"
      "orl %%edi, %%ebx\n\t"
      "movl %%ebx, (%%ecx)\n\t"
      "movl %%edx, %%edi\n\t"
      "sarl $6, %%edi\n\t"
      "andl $1, %%edi\n\t"
      "movzbl (%%edi,%%esi,1), %%edi\n\t"
      "movl %%edi, %%ebx\n\t"
      "shll $8, %%ebx\n\t"
      "orl %%edi, %%ebx\n\t"
      "shll $8, %%ebx\n\t"
      "orl %%edi, %%ebx\n\t"
      "movl %%ebx, 0x4(%%ecx)\n\t"
      "addl $4, %%ecx\n\t"
      "movl %%edx, %%edi\n\t"
      "sarl $5, %%edi\n\t"
      "andl $1, %%edi\n\t"
      "movzbl (%%edi,%%esi,1), %%edi\n\t"
      "movl %%edi, %%ebx\n\t"
      "shll $8, %%ebx\n\t"
      "orl %%edi, %%ebx\n\t"
      "shll $8, %%ebx\n\t"
      "orl %%edi, %%ebx\n\t"
      "movl %%ebx, 0x4(%%ecx)\n\t"
      "addl $4, %%ecx\n\t"
      "movl %%edx, %%edi\n\t"
      "sarl $4, %%edi\n\t"
      "andl $1, %%edi\n\t"
      "movzbl (%%edi,%%esi,1), %%edi\n\t"
      "movl %%edi, %%ebx\n\t"
      "shll $8, %%ebx\n\t"
      "orl %%edi, %%ebx\n\t"
      "shll $8, %%ebx\n\t"
      "orl %%edi, %%ebx\n\t"
      "movl %%ebx, 0x4(%%ecx)\n\t"
      "addl $4, %%ecx\n\t"
      "movl %%edx, %%edi\n\t"
      "sarl $3, %%edi\n\t"
      "andl $1, %%edi\n\t"
      "movzbl (%%edi,%%esi,1), %%edi\n\t"
      "movl %%edi, %%ebx\n\t"
      "shll $8, %%ebx\n\t"
      "orl %%edi, %%ebx\n\t"
      "shll $8, %%ebx\n\t"
      "orl %%edi, %%ebx\n\t"
      "movl %%ebx, 0x4(%%ecx)\n\t"
      "addl $4, %%ecx\n\t"
      "movl %%edx, %%edi\n\t"
      "sarl $2, %%edi\n\t"
      "andl $1, %%edi\n\t"
      "movzbl (%%edi,%%esi,1), %%edi\n\t"
      "movl %%edi, %%ebx\n\t"
      "shll $8, %%ebx\n\t"
      "orl %%edi, %%ebx\n\t"
      "shll $8, %%ebx\n\t"
      "orl %%edi, %%ebx\n\t"
      "movl %%ebx, 0x4(%%ecx)\n\t"
      "addl $4, %%ecx\n\t"
      "movl %%edx, %%edi\n\t"
      "sarl $1, %%edi\n\t"
      "andl $1, %%edi\n\t"
      "movzbl (%%edi,%%esi,1), %%edi\n\t"
      "movl %%edi, %%ebx\n\t"
      "shll $8, %%ebx\n\t"
      "orl %%edi, %%ebx\n\t"
      "shll $8, %%ebx\n\t"
      "orl %%edi, %%ebx\n\t"
      "addl $4, %%ecx\n\t"
      "movl %%ebx, (%%ecx)\n\t"
      "movl %%edx, %%edi\n\t"
      "addl $4, %%ecx\n\t"
      "andl $1, %%edi\n\t"
      "movzbl (%%edi,%%esi,1), %%edi\n\t"
      "jmp .LFUN_0006a3b0_7\n\t"
      ".LFUN_0006a3b0_4:\n\t"
      "movl %%edx, %%edi\n\t"
      "sarl $6, %%edi\n\t"
      "movzbl (%%edi,%%esi,1), %%edi\n\t"
      "movl %%edi, %%ebx\n\t"
      "shll $8, %%ebx\n\t"
      "orl %%edi, %%ebx\n\t"
      "shll $8, %%ebx\n\t"
      "orl %%edi, %%ebx\n\t"
      "movl %%ebx, (%%ecx)\n\t"
      "movl %%edx, %%edi\n\t"
      "sarl $4, %%edi\n\t"
      "andl $3, %%edi\n\t"
      "movzbl (%%edi,%%esi,1), %%edi\n\t"
      "movl %%edi, %%ebx\n\t"
      "shll $8, %%ebx\n\t"
      "orl %%edi, %%ebx\n\t"
      "shll $8, %%ebx\n\t"
      "orl %%edi, %%ebx\n\t"
      "movl %%ebx, 0x4(%%ecx)\n\t"
      "addl $4, %%ecx\n\t"
      "movl %%edx, %%edi\n\t"
      "sarl $2, %%edi\n\t"
      "andl $3, %%edi\n\t"
      "movzbl (%%edi,%%esi,1), %%edi\n\t"
      "movl %%edi, %%ebx\n\t"
      "shll $8, %%ebx\n\t"
      "orl %%edi, %%ebx\n\t"
      "shll $8, %%ebx\n\t"
      "orl %%edi, %%ebx\n\t"
      "addl $4, %%ecx\n\t"
      "movl %%ebx, (%%ecx)\n\t"
      "movl %%edx, %%edi\n\t"
      "addl $4, %%ecx\n\t"
      "andl $3, %%edi\n\t"
      "movzbl (%%edi,%%esi,1), %%edi\n\t"
      "jmp .LFUN_0006a3b0_7\n\t"
      ".LFUN_0006a3b0_5:\n\t"
      "movl %%edx, %%edi\n\t"
      "sarl $4, %%edi\n\t"
      "movzbl (%%edi,%%esi,1), %%edi\n\t"
      "movl %%edi, %%ebx\n\t"
      "shll $8, %%ebx\n\t"
      "orl %%edi, %%ebx\n\t"
      "shll $8, %%ebx\n\t"
      "orl %%edi, %%ebx\n\t"
      "movl %%ebx, (%%ecx)\n\t"
      "movl %%edx, %%edi\n\t"
      "addl $4, %%ecx\n\t"
      "andl $0xf, %%edi\n\t"
      "movzbl (%%edi,%%esi,1), %%edi\n\t"
      "jmp .LFUN_0006a3b0_7\n\t"
      ".LFUN_0006a3b0_6:\n\t"
      "movzbl (%%edx,%%esi,1), %%edi\n\t"
      ".LFUN_0006a3b0_7:\n\t"
      "movl %%edi, %%ebx\n\t"
      "shll $8, %%ebx\n\t"
      "orl %%edi, %%ebx\n\t"
      "shll $8, %%ebx\n\t"
      "orl %%edi, %%ebx\n\t"
      "movl %%ebx, (%%ecx)\n\t"
      "addl $4, %%ecx\n\t"
      ".LFUN_0006a3b0_8:\n\t"
      "incl %%edx\n\t"
      "cmpl $0x100, %%edx\n\t"
      "jl .LFUN_0006a3b0_2\n\t"
      "popl %%edi\n\t"
      "movl $1, %%eax\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      "movl %%edi, %%edi\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_0006a3b0_jt:\n\t"
      ".long .LFUN_0006a3b0_3\n\t"
      ".long .LFUN_0006a3b0_4\n\t"
      ".long .LFUN_0006a3b0_8\n\t"
      ".long .LFUN_0006a3b0_5\n\t"
      ".long .LFUN_0006a3b0_8\n\t"
      ".long .LFUN_0006a3b0_8\n\t"
      ".long .LFUN_0006a3b0_8\n\t"
      ".long .LFUN_0006a3b0_6\n\t"
      ".text\n\t"
      :
      : [c8ee60] "m"(b6a3b0_c8ee60), [c68a30] "m"(b6a3b0_c68a30)
      : "memory");
}
#else
#error "FUN_0006a3b0: clang naked draft required"
#endif


/* FUN_0006a5d0 (0x6a5d0) — XBE naked draft (batch 305). */
#if defined(__clang__)
static void * (*const b6a5d0_c8ee60)(uint32_t size, bool zero, const char *file, int line) = debug_malloc;
static void (*const b6a5d0_c68a30)(int param_1, const char *format, ...) = (void (*)(int, const char *, ...))FUN_00068a30;

__attribute__((naked, noinline))
void FUN_0006a5d0(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "movzwl 0x3340fc, %%ecx\n\t"
      "movl $8, %%eax\n\t"
      "cdq\n\t"
      "idivl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "movl 0xc(%%ebp), %%ebx\n\t"
      "pushl $0x251\n\t"
      "pushl $0x260264\n\t"
      "pushl $0\n\t"
      "incl %%eax\n\t"
      "shll $0xa, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c8ee60]\n\t"
      "movl %%eax, %%edx\n\t"
      "addl $0x10, %%esp\n\t"
      "testl %%edx, %%edx\n\t"
      "movl %%edx, 0x3340c4\n\t"
      "jne .LFUN_0006a5d0_1\n\t"
      "movl 0x3340dc, %%edx\n\t"
      "pushl $0x260294\n\t"
      "pushl %%edx\n\t"
      "call *%[c68a30]\n\t"
      "addl $8, %%esp\n\t"
      "xorl %%eax, %%eax\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0006a5d0_1:\n\t"
      "pushl %%edi\n\t"
      "leal 0x400(%%edx), %%ecx\n\t"
      "xorl %%eax, %%eax\n\t"
      "jmp .LFUN_0006a5d0_3\n\t"
      ".LFUN_0006a5d0_2:\n\t"
      "movl 0x3340c4, %%edx\n\t"
      "movl 0xc(%%ebp), %%ebx\n\t"
      "jmp .LFUN_0006a5d0_3\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".LFUN_0006a5d0_3:\n\t"
      "movl %%ecx, (%%edx,%%eax,4)\n\t"
      "movzwl 0x3340fc, %%edx\n\t"
      "decl %%edx\n\t"
      "cmpl $7, %%edx\n\t"
      "ja .LFUN_0006a5d0_10\n\t"
      "jmp *.LFUN_0006a5d0_jt(,%%edx,4)\n\t"
      ".LFUN_0006a5d0_4:\n\t"
      "movl %%eax, %%edx\n\t"
      "sarl $7, %%edx\n\t"
      "movzbl %%dl, %%edi\n\t"
      "xorl %%edx, %%edx\n\t"
      "shll $1, %%edi\n\t"
      "movb (%%edi,%%esi,1), %%dh\n\t"
      "movl %%edi, -0x4(%%ebp)\n\t"
      "addl $4, %%ecx\n\t"
      "addl $4, %%ecx\n\t"
      "addl $4, %%ecx\n\t"
      "addl $4, %%ecx\n\t"
      "movb (%%edi,%%ebx,1), %%dl\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "movzbl (%%edi,%%ebx,1), %%ebx\n\t"
      "andl $0xff, %%ebx\n\t"
      "shll $8, %%edx\n\t"
      "orl %%ebx, %%edx\n\t"
      "movl %%edx, -0x10(%%ecx)\n\t"
      "movl 0xc(%%ebp), %%ebx\n\t"
      "movl %%eax, %%edx\n\t"
      "sarl $6, %%edx\n\t"
      "andb $1, %%dl\n\t"
      "movzbl %%dl, %%edi\n\t"
      "xorl %%edx, %%edx\n\t"
      "shll $1, %%edi\n\t"
      "movb (%%edi,%%esi,1), %%dh\n\t"
      "movl %%edi, -0x4(%%ebp)\n\t"
      "movb (%%edi,%%ebx,1), %%dl\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "movzbl (%%edi,%%ebx,1), %%ebx\n\t"
      "andl $0xff, %%ebx\n\t"
      "shll $8, %%edx\n\t"
      "orl %%ebx, %%edx\n\t"
      "movl %%edx, -0xc(%%ecx)\n\t"
      "movl 0xc(%%ebp), %%ebx\n\t"
      "movl %%eax, %%edx\n\t"
      "sarl $5, %%edx\n\t"
      "andb $1, %%dl\n\t"
      "movzbl %%dl, %%edi\n\t"
      "xorl %%edx, %%edx\n\t"
      "shll $1, %%edi\n\t"
      "movb (%%edi,%%esi,1), %%dh\n\t"
      "movl %%edi, -0x4(%%ebp)\n\t"
      "movb (%%edi,%%ebx,1), %%dl\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "movzbl (%%edi,%%ebx,1), %%ebx\n\t"
      "andl $0xff, %%ebx\n\t"
      "shll $8, %%edx\n\t"
      "orl %%ebx, %%edx\n\t"
      "movl %%edx, -0x8(%%ecx)\n\t"
      "movl 0xc(%%ebp), %%ebx\n\t"
      "movl %%eax, %%edx\n\t"
      "sarl $4, %%edx\n\t"
      "andb $1, %%dl\n\t"
      "movzbl %%dl, %%edi\n\t"
      "xorl %%edx, %%edx\n\t"
      "shll $1, %%edi\n\t"
      "movb (%%edi,%%esi,1), %%dh\n\t"
      "movl %%edi, -0x4(%%ebp)\n\t"
      "movb (%%edi,%%ebx,1), %%dl\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "movzbl (%%edi,%%ebx,1), %%ebx\n\t"
      "andl $0xff, %%ebx\n\t"
      "shll $8, %%edx\n\t"
      "orl %%ebx, %%edx\n\t"
      "movl 0xc(%%ebp), %%ebx\n\t"
      "movl %%edx, -0x4(%%ecx)\n\t"
      "movl %%eax, %%edx\n\t"
      "sarl $3, %%edx\n\t"
      "andb $1, %%dl\n\t"
      "movzbl %%dl, %%edi\n\t"
      "shll $1, %%edi\n\t"
      "xorl %%edx, %%edx\n\t"
      "movb (%%edi,%%esi,1), %%dh\n\t"
      "movl %%edi, -0x4(%%ebp)\n\t"
      "movb (%%edi,%%ebx,1), %%dl\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "movzbl (%%edi,%%ebx,1), %%ebx\n\t"
      "andl $0xff, %%ebx\n\t"
      "shll $8, %%edx\n\t"
      "orl %%ebx, %%edx\n\t"
      "movl %%edx, (%%ecx)\n\t"
      "movl 0xc(%%ebp), %%ebx\n\t"
      "movl %%eax, %%edx\n\t"
      "sarl $2, %%edx\n\t"
      "andb $1, %%dl\n\t"
      "movzbl %%dl, %%edi\n\t"
      "xorl %%edx, %%edx\n\t"
      "shll $1, %%edi\n\t"
      "movb (%%edi,%%esi,1), %%dh\n\t"
      "addl $4, %%ecx\n\t"
      "movl %%edi, -0x4(%%ebp)\n\t"
      "addl $4, %%ecx\n\t"
      "addl $4, %%ecx\n\t"
      "movb (%%edi,%%ebx,1), %%dl\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "movzbl (%%edi,%%ebx,1), %%ebx\n\t"
      "andl $0xff, %%ebx\n\t"
      "shll $8, %%edx\n\t"
      "orl %%ebx, %%edx\n\t"
      "movl 0xc(%%ebp), %%ebx\n\t"
      "movl %%edx, -0x8(%%ecx)\n\t"
      "movl %%eax, %%edx\n\t"
      "sarl $1, %%edx\n\t"
      "andb $1, %%dl\n\t"
      "movzbl %%dl, %%edi\n\t"
      "xorl %%edx, %%edx\n\t"
      "shll $1, %%edi\n\t"
      "movb (%%edi,%%esi,1), %%dh\n\t"
      "movl %%edi, -0x4(%%ebp)\n\t"
      "movb (%%edi,%%ebx,1), %%dl\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "movzbl (%%edi,%%ebx,1), %%ebx\n\t"
      "andl $0xff, %%ebx\n\t"
      "shll $8, %%edx\n\t"
      "orl %%ebx, %%edx\n\t"
      "movl %%edx, -0x4(%%ecx)\n\t"
      "movb %%al, %%dl\n\t"
      "andb $1, %%dl\n\t"
      "jmp .LFUN_0006a5d0_7\n\t"
      ".LFUN_0006a5d0_5:\n\t"
      "movl %%eax, %%edx\n\t"
      "sarl $6, %%edx\n\t"
      "movzbl %%dl, %%edi\n\t"
      "xorl %%edx, %%edx\n\t"
      "shll $1, %%edi\n\t"
      "movb (%%edi,%%esi,1), %%dh\n\t"
      "movl %%edi, -0x4(%%ebp)\n\t"
      "addl $4, %%ecx\n\t"
      "addl $4, %%ecx\n\t"
      "addl $4, %%ecx\n\t"
      "movb (%%edi,%%ebx,1), %%dl\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "movzbl (%%edi,%%ebx,1), %%ebx\n\t"
      "andl $0xff, %%ebx\n\t"
      "shll $8, %%edx\n\t"
      "orl %%ebx, %%edx\n\t"
      "movl %%edx, -0xc(%%ecx)\n\t"
      "movl 0xc(%%ebp), %%ebx\n\t"
      "movl %%eax, %%edx\n\t"
      "sarl $4, %%edx\n\t"
      "andb $3, %%dl\n\t"
      "movzbl %%dl, %%edi\n\t"
      "xorl %%edx, %%edx\n\t"
      "shll $1, %%edi\n\t"
      "movb (%%edi,%%esi,1), %%dh\n\t"
      "movl %%edi, -0x4(%%ebp)\n\t"
      "movb (%%edi,%%ebx,1), %%dl\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "movzbl (%%edi,%%ebx,1), %%ebx\n\t"
      "andl $0xff, %%ebx\n\t"
      "shll $8, %%edx\n\t"
      "orl %%ebx, %%edx\n\t"
      "movl 0xc(%%ebp), %%ebx\n\t"
      "movl %%edx, -0x8(%%ecx)\n\t"
      "movl %%eax, %%edx\n\t"
      "sarl $2, %%edx\n\t"
      "andb $3, %%dl\n\t"
      "movzbl %%dl, %%edi\n\t"
      "xorl %%edx, %%edx\n\t"
      "shll $1, %%edi\n\t"
      "movb (%%edi,%%esi,1), %%dh\n\t"
      "movl %%edi, -0x4(%%ebp)\n\t"
      "movb (%%edi,%%ebx,1), %%dl\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "movzbl (%%edi,%%ebx,1), %%ebx\n\t"
      "andl $0xff, %%ebx\n\t"
      "shll $8, %%edx\n\t"
      "orl %%ebx, %%edx\n\t"
      "movl %%edx, -0x4(%%ecx)\n\t"
      "movb %%al, %%dl\n\t"
      "andb $3, %%dl\n\t"
      "jmp .LFUN_0006a5d0_7\n\t"
      ".LFUN_0006a5d0_6:\n\t"
      "movl %%eax, %%edx\n\t"
      "sarl $4, %%edx\n\t"
      "movzbl %%dl, %%edi\n\t"
      "xorl %%edx, %%edx\n\t"
      "shll $1, %%edi\n\t"
      "movb (%%edi,%%esi,1), %%dh\n\t"
      "addl $4, %%ecx\n\t"
      "movl %%edi, -0x4(%%ebp)\n\t"
      "movb (%%edi,%%ebx,1), %%dl\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "movzbl (%%edi,%%ebx,1), %%ebx\n\t"
      "andl $0xff, %%ebx\n\t"
      "shll $8, %%edx\n\t"
      "orl %%ebx, %%edx\n\t"
      "movl %%edx, -0x4(%%ecx)\n\t"
      "movb %%al, %%dl\n\t"
      "andb $0xf, %%dl\n\t"
      ".LFUN_0006a5d0_7:\n\t"
      "movl 0xc(%%ebp), %%ebx\n\t"
      "movzbl %%dl, %%edi\n\t"
      "shll $1, %%edi\n\t"
      "xorl %%edx, %%edx\n\t"
      "movb (%%edi,%%esi,1), %%dh\n\t"
      "movl %%edi, -0x4(%%ebp)\n\t"
      "movb (%%edi,%%ebx,1), %%dl\n\t"
      "jmp .LFUN_0006a5d0_9\n\t"
      ".LFUN_0006a5d0_8:\n\t"
      "movzbl %%al, %%edi\n\t"
      "shll $1, %%edi\n\t"
      "xorl %%edx, %%edx\n\t"
      "movb (%%edi,%%esi,1), %%dh\n\t"
      "movl %%edi, -0x4(%%ebp)\n\t"
      "movb (%%edi,%%ebx,1), %%dl\n\t"
      ".LFUN_0006a5d0_9:\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "movzbl (%%edi,%%ebx,1), %%ebx\n\t"
      "shll $8, %%edx\n\t"
      "andl $0xff, %%ebx\n\t"
      "orl %%ebx, %%edx\n\t"
      "movl %%edx, (%%ecx)\n\t"
      "addl $4, %%ecx\n\t"
      ".LFUN_0006a5d0_10:\n\t"
      "incl %%eax\n\t"
      "cmpl $0x100, %%eax\n\t"
      "jl .LFUN_0006a5d0_2\n\t"
      "popl %%edi\n\t"
      "movl $1, %%eax\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_0006a5d0_jt:\n\t"
      ".long .LFUN_0006a5d0_4\n\t"
      ".long .LFUN_0006a5d0_5\n\t"
      ".long .LFUN_0006a5d0_10\n\t"
      ".long .LFUN_0006a5d0_6\n\t"
      ".long .LFUN_0006a5d0_10\n\t"
      ".long .LFUN_0006a5d0_10\n\t"
      ".long .LFUN_0006a5d0_10\n\t"
      ".long .LFUN_0006a5d0_8\n\t"
      ".text\n\t"
      :
      : [c8ee60] "m"(b6a5d0_c8ee60), [c68a30] "m"(b6a5d0_c68a30)
      : "memory");
}
#else
#error "FUN_0006a5d0: clang naked draft required"
#endif


/* FUN_0006a910 (0x6a910) — Capstone lift: expand packed samples via LUT @0x3340c4.
 * Args: dest, src, (unused), bits, rows, src_pitch, dest_extra. */
void FUN_0006a910(unsigned int *dest, unsigned char *src, void *unused,
                  unsigned int bit_count, unsigned int row_count, int src_pitch,
                  int dest_extra)
{
  unsigned int **lut;
  unsigned int dest_pitch;
  unsigned int rem;
  unsigned int n;
  unsigned int *out;
  unsigned char *in;

  (void)unused;
  if (row_count == 0)
    return;
  lut = *(unsigned int ***)0x3340c4;
  dest_pitch = (unsigned)dest_extra * 4;
  out = dest;
  in = src;
  do {
    rem = bit_count;
    if (bit_count >= 8) {
      n = bit_count >> 3;
      do {
        *out = *lut[*in];
        out += 1;
        in += 1;
        rem -= 8;
        n -= 1;
      } while (n != 0);
    }
    if (rem != 0) {
      *out = *lut[*in];
      out += 1;
      in += 1;
    }
    out = (unsigned int *)((char *)out + (int)dest_pitch);
    in += src_pitch;
    row_count -= 1;
  } while (row_count != 0);
}



/* FUN_0006a9a0 (0x6a9a0) — readable C lift: 2->32bpp expand via *DAT_003340c4. */
void FUN_0006a9a0(unsigned int *dst, unsigned char *src, void *unused,
                  int count, int num_rows, int skip_src_words, int skip_dst)
{
  extern unsigned int *DAT_003340c4;
  unsigned int *table;
  int pitch;
  int rows;
  int src_skip;
  unsigned int *d;
  unsigned char *s;
  int rem;

  (void)unused;
  src_skip = skip_src_words >> 1; /* cdq/sar on ebp+1c */
  if ((unsigned)num_rows == 0u)
    return;
  table = DAT_003340c4;
  pitch = skip_dst << 2;
  rows = num_rows;
  d = dst;
  s = src;
  do {
    rem = count;
    if ((unsigned)rem >= 2u) {
      unsigned pairs = (unsigned)rem >> 1;
      do {
        unsigned int *p = (unsigned int *)table[*s++];
        *d++ = p[0];
        *d++ = p[1];
        rem -= 2;
      } while (--pairs != 0);
    }
    if (rem != 0) {
      unsigned int *p = (unsigned int *)table[*s++];
      *d++ = p[0];
    }
    d = (unsigned int *)((char *)d + pitch);
    s += src_skip;
  } while (--rows != 0);
}


/* FUN_0006aa40 (0x6aa40) — Capstone lift: 8->32bpp×4 expand via *DAT_003340c4. */
void FUN_0006aa40(unsigned int *dst, unsigned char *src, void *unused,
                  int count, int num_rows, int skip_src_words, int skip_dst)
{
  extern unsigned int *DAT_003340c4;
  unsigned int *table;
  int pitch;
  int rows;
  int src_skip;
  unsigned int *d;
  unsigned char *s;
  int rem;
  int t;

  (void)unused;
  t = skip_src_words;
  src_skip = (t + ((t >> 31) & 3)) >> 2;
  if ((unsigned)num_rows == 0u)
    return;
  table = DAT_003340c4;
  pitch = skip_dst << 2;
  rows = num_rows;
  d = dst;
  s = src;
  do {
    rem = count;
    if ((unsigned)rem >= 4u) {
      unsigned quads = (unsigned)rem >> 2;
      do {
        unsigned int *p = (unsigned int *)table[*s++];
        *d++ = p[0];
        *d++ = p[1];
        *d++ = p[2];
        *d++ = p[3];
        rem -= 4;
      } while (--quads != 0);
    }
    if (rem != 0) {
      unsigned int *p = (unsigned int *)table[*s++];
      if (rem == 3) {
        *d++ = p[0];
        p += 1;
        rem = 2;
      }
      if (rem == 2) {
        *d++ = p[0];
        p += 1;
        rem = 1;
      }
      if (rem == 1)
        *d++ = p[0];
    }
    d = (unsigned int *)((char *)d + pitch);
    s += src_skip;
  } while (--rows != 0);
}


/* FUN_0006ab10 (0x6ab10) — Capstone lift: 8->32bpp×8 expand via *DAT_003340c4. */
void FUN_0006ab10(unsigned int *dst, unsigned char *src, void *unused,
                  int count, int num_rows, int skip_src_words, int skip_dst)
{
  extern unsigned int *DAT_003340c4;
  unsigned int *table;
  int pitch;
  int rows;
  int src_skip;
  unsigned int *d;
  unsigned char *s;
  int rem;
  int t;
  int i;

  (void)unused;
  t = skip_src_words;
  src_skip = (t + ((t >> 31) & 7)) >> 3;
  if ((unsigned)num_rows == 0u)
    return;
  table = DAT_003340c4;
  pitch = skip_dst << 2;
  rows = num_rows;
  d = dst;
  s = src;
  do {
    rem = count;
    if ((unsigned)rem >= 8u) {
      unsigned octs = (unsigned)rem >> 3;
      do {
        unsigned int *p = (unsigned int *)table[*s++];
        for (i = 0; i < 8; i++)
          *d++ = p[i];
        rem -= 8;
      } while (--octs != 0);
    }
    if (rem != 0) {
      unsigned int *p = (unsigned int *)table[*s++];
      /* duff remainder 1..7 via jumptable — copy rem dwords */
      for (i = 0; i < rem; i++)
        *d++ = p[i];
    }
    d = (unsigned int *)((char *)d + pitch);
    s += src_skip;
  } while (--rows != 0);
}


/* FUN_0006ac60 (0x6ac60) — readable C lift from XBE.
 * Expand bytes through LUT @0x3340c8 → dest dwords (same shape as FUN_0006a910). */
void FUN_0006ac60(unsigned int *dest, unsigned char *src, void *unused,
                  unsigned int bit_count, unsigned int row_count, int src_pitch,
                  int dest_extra)
{
  unsigned int **lut;
  unsigned int dest_pitch;
  unsigned int *out;
  unsigned char *in;
  unsigned int x;

  (void)unused;
  if (row_count == 0)
    return;
  lut = *(unsigned int ***)0x3340c8;
  dest_pitch = (unsigned)dest_extra * 4;
  out = dest;
  in = src;
  do {
    x = bit_count;
    if (x > 0) {
      do {
        *out = *lut[*in];
        out += 1;
        in += 1;
        x -= 1;
      } while (x != 0);
    }
    out = (unsigned int *)((char *)out + (int)dest_pitch);
    in += src_pitch;
    row_count -= 1;
  } while (row_count != 0);
}


/* FUN_0006acc0 (0x6acc0) — Capstone lift: 8->32bpp×8 expand via *DAT_003340c8. */
void FUN_0006acc0(unsigned int *dst, unsigned char *src, void *unused,
                  int count, int num_rows, int skip_src_words, int skip_dst)
{
  extern unsigned int *DAT_003340c8;
  unsigned int *table;
  int pitch;
  int rows;
  int src_skip;
  unsigned int *d;
  unsigned char *s;
  int rem;
  int t;
  int i;

  (void)unused;
  t = skip_src_words;
  src_skip = (t + ((t >> 31) & 7)) >> 3;
  if ((unsigned)num_rows == 0u)
    return;
  table = DAT_003340c8;
  pitch = skip_dst << 2;
  rows = num_rows;
  d = dst;
  s = src;
  do {
    rem = count;
    if ((unsigned)rem >= 8u) {
      unsigned octs = (unsigned)rem >> 3;
      do {
        unsigned int *p = (unsigned int *)table[*s++];
        for (i = 0; i < 8; i++)
          *d++ = p[i];
        rem -= 8;
      } while (--octs != 0);
    }
    if (rem != 0) {
      unsigned int *p = (unsigned int *)table[*s++];
      for (i = 0; i < rem; i++)
        *d++ = p[i];
    }
    d = (unsigned int *)((char *)d + pitch);
    s += src_skip;
  } while (--rows != 0);
}


/* FUN_0006ae10 (0x6ae10) — Capstone lift: 8->32bpp×4 expand via *DAT_003340c8. */
void FUN_0006ae10(unsigned int *dst, unsigned char *src, void *unused,
                  int count, int num_rows, int skip_src_words, int skip_dst)
{
  extern unsigned int *DAT_003340c8;
  unsigned int *table;
  int pitch;
  int rows;
  int src_skip;
  unsigned int *d;
  unsigned char *s;
  int rem;
  int t;

  (void)unused;
  t = skip_src_words;
  src_skip = (t + ((t >> 31) & 3)) >> 2;
  if ((unsigned)num_rows == 0u)
    return;
  table = DAT_003340c8;
  pitch = skip_dst << 2;
  rows = num_rows;
  d = dst;
  s = src;
  do {
    rem = count;
    if ((unsigned)rem >= 4u) {
      unsigned quads = (unsigned)rem >> 2;
      do {
        unsigned int *p = (unsigned int *)table[*s++];
        *d++ = p[0];
        *d++ = p[1];
        *d++ = p[2];
        *d++ = p[3];
        rem -= 4;
      } while (--quads != 0);
    }
    if (rem != 0) {
      unsigned int *p = (unsigned int *)table[*s++];
      if (rem == 3) {
        *d++ = p[0];
        p += 1;
        rem = 2;
      }
      if (rem == 2) {
        *d++ = p[0];
        p += 1;
        rem = 1;
      }
      if (rem == 1)
        *d++ = p[0];
    }
    d = (unsigned int *)((char *)d + pitch);
    s += src_skip;
  } while (--rows != 0);
}


/* FUN_0006aee0 (0x6aee0) — readable C lift: 2->32bpp expand via *DAT_003340c8. */
void FUN_0006aee0(unsigned int *dst, unsigned char *src, void *unused,
                  int count, int num_rows, int skip_src_words, int skip_dst)
{
  extern unsigned int *DAT_003340c8;
  unsigned int *table;
  int pitch;
  int rows;
  int src_skip;
  unsigned int *d;
  unsigned char *s;
  int rem;

  (void)unused;
  src_skip = skip_src_words >> 1;
  if ((unsigned)num_rows == 0u)
    return;
  table = DAT_003340c8;
  pitch = skip_dst << 2;
  rows = num_rows;
  d = dst;
  s = src;
  do {
    rem = count;
    if ((unsigned)rem >= 2u) {
      unsigned pairs = (unsigned)rem >> 1;
      do {
        unsigned int *p = (unsigned int *)table[*s++];
        *d++ = p[0];
        *d++ = p[1];
        rem -= 2;
      } while (--pairs != 0);
    }
    if (rem != 0) {
      unsigned int *p = (unsigned int *)table[*s++];
      *d++ = p[0];
    }
    d = (unsigned int *)((char *)d + pitch);
    s += src_skip;
  } while (--rows != 0);
}


/* FUN_0006af80 (0x6af80) — Capstone lift: contig 8-bit RGB→dword (+optional LUT).
 * No-LUT path matches XBE quirk: process count>>3 pixels then at most one more. */
void FUN_0006af80(unsigned int *dst, unsigned char *src, unsigned char *lut,
                  unsigned int count, unsigned int num_rows, int skip_src,
                  int skip_dst)
{
  unsigned short spp = *(unsigned short *)0x3340f8;
  int row_skip = (int)spp * skip_src;
  int pitch = skip_dst << 2;
  unsigned int *d;
  unsigned char *s;
  unsigned int rows;
  unsigned int cols;
  unsigned int n;
  unsigned int rem;
  unsigned int pix;

  if (lut != NULL) {
    if (num_rows == 0)
      return;
    d = dst;
    s = src;
    rows = num_rows;
    do {
      cols = count;
      if (cols != 0) {
        do {
          pix = ((unsigned)lut[s[2]] << 16) | ((unsigned)lut[s[1]] << 8) |
                (unsigned)lut[s[0]];
          *d++ = pix;
          s += spp;
        } while (--cols != 0);
      }
      d = (unsigned int *)((char *)d + pitch);
      s += row_skip;
    } while (--rows != 0);
    return;
  }

  if (num_rows == 0)
    return;
  d = dst;
  s = src;
  rows = num_rows;
  do {
    n = count;
    rem = count;
    if (n >= 8u) {
      n >>= 3;
      do {
        pix = ((unsigned)s[2] << 16) | ((unsigned)s[1] << 8) | (unsigned)s[0];
        *d++ = pix;
        rem -= 8;
        s += spp;
      } while (--n != 0);
    }
    if (rem != 0) {
      pix = ((unsigned)s[2] << 16) | ((unsigned)s[1] << 8) | (unsigned)s[0];
      *d++ = pix;
      s += spp;
    }
    d = (unsigned int *)((char *)d + pitch);
    s += row_skip;
  } while (--rows != 0);
}


/* FUN_0006b0a0 (0x6b0a0) — Capstone lift: contig 16-bit RGB→dword (+optional LUT). */
void FUN_0006b0a0(unsigned int *dst, unsigned short *src, unsigned char *lut,
                  unsigned int count, unsigned int num_rows, int skip_src,
                  int skip_dst)
{
  unsigned short spp = *(unsigned short *)0x3340f8;
  int row_skip = ((int)spp * skip_src) * 2;
  int pitch = skip_dst << 2;
  unsigned int *d;
  unsigned short *s;
  unsigned int rows;
  unsigned int cols;
  unsigned int pix;

  if (lut != NULL) {
    if (num_rows == 0)
      return;
    d = dst;
    s = src;
    rows = num_rows;
    do {
      cols = count;
      if (cols != 0) {
        do {
          pix = ((unsigned)lut[s[2]] << 16) | ((unsigned)lut[s[1]] << 8) |
                (unsigned)lut[s[0]];
          *d++ = pix;
          s += spp;
        } while (--cols != 0);
      }
      d = (unsigned int *)((char *)d + pitch);
      s = (unsigned short *)((char *)s + row_skip);
    } while (--rows != 0);
    return;
  }

  if (num_rows == 0)
    return;
  d = dst;
  s = src;
  rows = num_rows;
  do {
    cols = count;
    if (cols != 0) {
      do {
        pix = ((unsigned)s[2] << 16) | ((unsigned)s[1] << 8) | (unsigned)s[0];
        *d++ = pix;
        s += spp;
      } while (--cols != 0);
    }
    d = (unsigned int *)((char *)d + pitch);
    s = (unsigned short *)((char *)s + row_skip);
  } while (--rows != 0);
}


/* FUN_0006b190 (0x6b190) — Capstone lift: planar R/G/B -> packed RGB dword. */
void FUN_0006b190(unsigned int *dst, unsigned char *src_r, unsigned char *src_g,
                  unsigned char *src_b, unsigned char *lut, int count,
                  int num_rows, int skip_src_count, int skip_dst_count)
{
  int pitch;
  int rows;
  unsigned int *d;
  unsigned char *r;
  unsigned char *g;
  unsigned char *b;
  int rem;
  int n;
  unsigned int pixel;

  if (lut != 0) {
    if ((unsigned)num_rows == 0u)
      return;
    pitch = skip_dst_count << 2;
    rows = num_rows;
    d = dst;
    r = src_r;
    g = src_g;
    b = src_b;
    do {
      rem = count;
      if ((unsigned)rem != 0u) {
        do {
          pixel = (unsigned int)lut[*b];
          pixel = (pixel << 8) | (unsigned int)lut[*g];
          pixel = (pixel << 8) | (unsigned int)lut[*r];
          *d++ = pixel;
          b++;
          g++;
          r++;
        } while (--rem != 0);
      }
      r += skip_src_count;
      g += skip_src_count;
      b += skip_src_count;
      d = (unsigned int *)((char *)d + pitch);
    } while (--rows != 0);
    return;
  }

  /* lut == NULL: pack raw plane bytes; count treated in groups of 8
     (XBE: one pixel per group + one leftover pixel if rem != 0). */
  if ((unsigned)num_rows == 0u)
    return;
  pitch = skip_dst_count << 2;
  rows = num_rows;
  d = dst;
  r = src_r;
  g = src_g;
  b = src_b;
  do {
    rem = count;
    if ((unsigned)rem >= 8u) {
      n = (unsigned)rem >> 3;
      do {
        pixel = (unsigned int)(*b);
        pixel = (pixel << 8) | (unsigned int)(*g);
        pixel = (pixel << 8) | (unsigned int)(*r);
        *d++ = pixel;
        b++;
        g++;
        r++;
        rem -= 8;
      } while (--n != 0);
    }
    if ((unsigned)rem != 0u) {
      pixel = (unsigned int)(*b);
      pixel = (pixel << 8) | (unsigned int)(*g);
      pixel = (pixel << 8) | (unsigned int)(*r);
      *d++ = pixel;
      b++;
      g++;
      r++;
    }
    r += skip_src_count;
    g += skip_src_count;
    b += skip_src_count;
    d = (unsigned int *)((char *)d + pitch);
  } while (--rows != 0);
}


/* FUN_0006b2d0 (0x6b2d0) — Capstone lift: planar 16-bit R/G/B -> packed RGB. */
void FUN_0006b2d0(unsigned int *dst, unsigned short *src_r, unsigned short *src_g,
                  unsigned short *src_b, unsigned char *lut, int count,
                  int num_rows, int skip_src_count, int skip_dst_count)
{
  int pitch = skip_dst_count << 2;
  int src_skip = skip_src_count + skip_src_count; /* bytes; asm add edx,edx */
  int rows;
  unsigned int *d;
  unsigned short *r, *g, *b;
  int rem;
  unsigned int pixel;

  if (lut != 0) {
    if ((unsigned)num_rows == 0u)
      return;
    d = dst;
    r = src_r;
    g = src_g;
    b = src_b;
    rows = num_rows;
    do {
      rem = count;
      if ((unsigned)rem != 0u) {
        do {
          pixel = ((unsigned)lut[*b] << 16) | ((unsigned)lut[*g] << 8) |
                  (unsigned)lut[*r];
          *d++ = pixel;
          b++;
          g++;
          r++;
        } while (--rem != 0);
      }
      r = (unsigned short *)((char *)r + src_skip);
      g = (unsigned short *)((char *)g + src_skip);
      b = (unsigned short *)((char *)b + src_skip);
      d = (unsigned int *)((char *)d + pitch);
    } while (--rows != 0);
    return;
  }

  if ((unsigned)num_rows == 0u)
    return;
  d = dst;
  r = src_r;
  g = src_g;
  b = src_b;
  rows = num_rows;
  do {
    rem = count;
    if ((unsigned)rem != 0u) {
      do {
        pixel = ((unsigned)*b << 16) | ((unsigned)*g << 8) | (unsigned)*r;
        *d++ = pixel;
        b++;
        g++;
        r++;
      } while (--rem != 0);
    }
    r = (unsigned short *)((char *)r + src_skip);
    g = (unsigned short *)((char *)g + src_skip);
    b = (unsigned short *)((char *)b + src_skip);
    d = (unsigned int *)((char *)d + pitch);
  } while (--rows != 0);
}


/* FUN_0006b440 (0x6b440) — Capstone lift: YUV tile → BGRX via *DAT_003340cc.
 * ABI: src@<eax>, uv_offset@<ecx>, num_rows@<edx>; dest/count/pitches cdecl. */
void FUN_0006b440(unsigned char *src /*@<eax>*/, int uv_offset /*@<ecx>*/,
                  int num_rows /*@<edx>*/, unsigned int *dest, int count,
                  int dest_pitch_add, int src_row_skip, int dest_pitch_base)
{
  float *table;
  float su;
  float sv;
  long double c0_sv;
  long double b8_su;
  long double b4_su;
  float bc_sv;
  int row_bytes;
  int rows;
  int col;
  unsigned char *s;
  unsigned int *d;
  long double t;
  float r;
  float g;
  float b;
  double vr;
  double vg;
  double vb;
  unsigned int pixel;

  table = *(float **)0x3340cc;
  su = ((float)(int)src[uv_offset] - table[2]) * *(float *)0x2602cc /
       (table[3] - table[2]);
  sv = ((float)(int)src[uv_offset + 1] - table[4]) * *(float *)0x2602cc /
       (table[5] - table[4]);
  if (num_rows <= 0)
    return;

  row_bytes = (dest_pitch_base + dest_pitch_add) << 2;
  rows = num_rows;
  s = src;
  d = dest;
  do {
    col = 0;
    if (count > 0) {
      c0_sv = (long double)*(float *)0x3340c0 * (long double)sv;
      b8_su = (long double)*(float *)0x3340b8 * (long double)su;
      b4_su = (long double)*(float *)0x3340b4 * (long double)su;
      bc_sv = *(float *)0x3340bc * sv;
      do {
        t = ((long double)(int)*s++ - (long double)table[0]) *
            (long double)*(float *)0x2602c8 /
            ((long double)table[1] - (long double)table[0]);
        r = (float)(t + c0_sv);
        b = (float)(t + b8_su);
        g = (float)(t - b4_su - (long double)bc_sv);

        vr = (double)r + *(double *)0x25fea8;
        if (vr < *(double *)0x2602c0)
          vr = *(double *)0x2602c0;
        else if (vr > *(double *)0x2602b8)
          vr = *(double *)0x2602b8;

        vg = (double)g + *(double *)0x25fea8;
        if (vg < *(double *)0x2602c0)
          vg = *(double *)0x2602c0;
        else if (vg > *(double *)0x2602b8)
          vg = *(double *)0x2602b8;

        vb = (double)b + *(double *)0x25fea8;
        if (vb < *(double *)0x2602c0)
          vb = *(double *)0x2602c0;
        else if (vb > *(double *)0x2602b8)
          vb = *(double *)0x2602b8;

        /* ftol order: B, G, R → pixel = B<<16 | G<<8 | R */
        pixel = ((unsigned int)(int)vb << 16) | ((unsigned int)(int)vg << 8) |
                (unsigned int)(int)vr;
        d[col] = pixel;
        table = *(float **)0x3340cc;
        col++;
      } while (col < count);
    }
    d = (unsigned int *)((char *)d + row_bytes);
    s += src_row_skip;
  } while (--rows != 0);
}


/* FUN_0006b610 (0x6b610) — Capstone lift: tile blit dispatcher via FUN_0006b440.
 * Tile size from DAT_003340d8 (w) × DAT_003340d4 (h). Callee also takes
 * src@<eax>, height@<edx>, area@<ecx>; stubs cover that under Unicorn.
 * Direct cast-call (not a local fn ptr) so clang emits REL32 for sibling resolve. */
void FUN_0006b610(unsigned int *dst, unsigned char *src, void *unused,
                  int count, int num_rows, int skip_src, int param20)
{
  extern unsigned short DAT_003340d4;
  extern unsigned short DAT_003340d8;
  typedef void (*b440_t)(unsigned int *d, int w, int pitch_base, int x_off,
                         int p20);
  unsigned tile_w = DAT_003340d8;
  unsigned tile_h = DAT_003340d4;
  int area = (int)(tile_w * tile_h);
  unsigned char *s = src;
  int rem_w;
  unsigned int *d;
  int pitch_cells;

  (void)unused;

  if ((unsigned)num_rows >= tile_h) {
    pitch_cells = param20 + count;
    do {
      d = dst;
      rem_w = count;
      tile_w = DAT_003340d8;
      if ((unsigned)count >= tile_w) {
        do {
          ((b440_t)(void *)FUN_0006b440)(d, (int)tile_w, count, 0, param20);
          tile_w = DAT_003340d8;
          s += area + 2;
          rem_w -= (int)tile_w;
          d += tile_w;
        } while ((unsigned)rem_w >= tile_w);
      }
      if (rem_w != 0) {
        ((b440_t)(void *)FUN_0006b440)(d, rem_w, count, (int)tile_w - rem_w,
                                       param20);
        tile_w = DAT_003340d8;
        s += area + 2;
      }
      tile_h = DAT_003340d4;
      dst = (unsigned int *)((char *)dst + pitch_cells * (int)tile_h * 4);
      s += skip_src;
      num_rows -= (int)tile_h;
    } while ((unsigned)num_rows >= tile_h);
  }

  if (num_rows != 0) {
    d = dst;
    rem_w = count;
    tile_w = DAT_003340d8;
    if ((unsigned)count >= tile_w) {
      int src_stride = area + 2;
      do {
        ((b440_t)(void *)FUN_0006b440)(d, (int)tile_w, count, 0, param20);
        tile_w = DAT_003340d8;
        s += src_stride;
        rem_w -= (int)tile_w;
        d += tile_w;
      } while ((unsigned)rem_w >= tile_w);
    }
    if (rem_w != 0)
      ((b440_t)(void *)FUN_0006b440)(d, rem_w, count, (int)tile_w - rem_w,
                                     param20);
  }
}


/* FUN_0006b780 (0x6b780) — XBE naked draft (batch 319). */
#if defined(__clang__)
static void (*const b6b780_c68a30)(int param_1, const char *format, ...) = (void (*)(int, const char *, ...))FUN_00068a30;

__attribute__((naked, noinline))
void FUN_0006b780(void)
{
  __asm__ volatile(
      "movzwl 0x3340f4, %%eax\n\t"
      "pushl %%esi\n\t"
      "xorl %%esi, %%esi\n\t"
      "cmpl $6, %%eax\n\t"
      "ja .LFUN_0006b780_15\n\t"
      "jmp *.LFUN_0006b780_jt0(,%%eax,4)\n\t"
      ".LFUN_0006b780_1:\n\t"
      "cmpw $8, 0x3340fc\n\t"
      "jne .LFUN_0006b780_2\n\t"
      "movl $0x6af80, %%esi\n\t"
      "jmp .LFUN_0006b780_14\n\t"
      ".LFUN_0006b780_2:\n\t"
      "movl $0x6b0a0, %%esi\n\t"
      "jmp .LFUN_0006b780_14\n\t"
      ".LFUN_0006b780_3:\n\t"
      "movzwl 0x3340fc, %%eax\n\t"
      "decl %%eax\n\t"
      "cmpl $7, %%eax\n\t"
      "ja .LFUN_0006b780_15\n\t"
      "jmp *.LFUN_0006b780_jt1(,%%eax,4)\n\t"
      ".LFUN_0006b780_4:\n\t"
      "movl $0x6a910, %%esi\n\t"
      "jmp .LFUN_0006b780_14\n\t"
      ".LFUN_0006b780_5:\n\t"
      "movl $0x6a9a0, %%esi\n\t"
      "jmp .LFUN_0006b780_14\n\t"
      ".LFUN_0006b780_6:\n\t"
      "movl $0x6aa40, %%esi\n\t"
      "jmp .LFUN_0006b780_14\n\t"
      ".LFUN_0006b780_7:\n\t"
      "movl $0x6ab10, %%esi\n\t"
      "jmp .LFUN_0006b780_14\n\t"
      ".LFUN_0006b780_8:\n\t"
      "movzwl 0x3340fc, %%eax\n\t"
      "decl %%eax\n\t"
      "cmpl $7, %%eax\n\t"
      "ja .LFUN_0006b780_15\n\t"
      "jmp *.LFUN_0006b780_jt2(,%%eax,4)\n\t"
      ".LFUN_0006b780_9:\n\t"
      "movl $0x6ac60, %%esi\n\t"
      "jmp .LFUN_0006b780_14\n\t"
      ".LFUN_0006b780_10:\n\t"
      "movl $0x6aee0, %%esi\n\t"
      "jmp .LFUN_0006b780_14\n\t"
      ".LFUN_0006b780_11:\n\t"
      "movl $0x6ae10, %%esi\n\t"
      "jmp .LFUN_0006b780_14\n\t"
      ".LFUN_0006b780_12:\n\t"
      "movl $0x6acc0, %%esi\n\t"
      "jmp .LFUN_0006b780_14\n\t"
      ".LFUN_0006b780_13:\n\t"
      "cmpw $8, 0x3340fc\n\t"
      "jne .LFUN_0006b780_15\n\t"
      "movl $0x6b610, %%esi\n\t"
      ".LFUN_0006b780_14:\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LFUN_0006b780_16\n\t"
      ".LFUN_0006b780_15:\n\t"
      "movl 0x3340dc, %%eax\n\t"
      "pushl $0x2602d0\n\t"
      "pushl %%eax\n\t"
      "call *%[c68a30]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_0006b780_16:\n\t"
      "movl %%esi, %%eax\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_0006b780_jt0:\n\t"
      ".long .LFUN_0006b780_8\n\t"
      ".long .LFUN_0006b780_8\n\t"
      ".long .LFUN_0006b780_1\n\t"
      ".long .LFUN_0006b780_3\n\t"
      ".long .LFUN_0006b780_15\n\t"
      ".long .LFUN_0006b780_15\n\t"
      ".long .LFUN_0006b780_13\n\t"
      ".text\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_0006b780_jt1:\n\t"
      ".long .LFUN_0006b780_7\n\t"
      ".long .LFUN_0006b780_6\n\t"
      ".long .LFUN_0006b780_15\n\t"
      ".long .LFUN_0006b780_5\n\t"
      ".long .LFUN_0006b780_15\n\t"
      ".long .LFUN_0006b780_15\n\t"
      ".long .LFUN_0006b780_15\n\t"
      ".long .LFUN_0006b780_4\n\t"
      ".text\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_0006b780_jt2:\n\t"
      ".long .LFUN_0006b780_12\n\t"
      ".long .LFUN_0006b780_11\n\t"
      ".long .LFUN_0006b780_15\n\t"
      ".long .LFUN_0006b780_10\n\t"
      ".long .LFUN_0006b780_15\n\t"
      ".long .LFUN_0006b780_15\n\t"
      ".long .LFUN_0006b780_15\n\t"
      ".long .LFUN_0006b780_9\n\t"
      ".text\n\t"
      :
      : [c68a30] "m"(b6b780_c68a30)
      : "memory");
}
#else
#error "FUN_0006b780: clang naked draft required"
#endif


/* FUN_0006b8e0 (0x6b8e0) — XBE naked draft (batch 341). */
#if defined(__clang__)
static void (*const b6b8e0_c6b780)(void) = (void (*)(void))FUN_0006b780;
static void (*const b6b8e0_c6f910)(void) = (void (*)(void))FUN_0006f910;
static void * (*const b6b8e0_c8ee60)(uint32_t size, bool zero, const char *file, int line) = debug_malloc;
static void (*const b6b8e0_c68a30)(int param_1, const char *format, ...) = (void (*)(int, const char *, ...))FUN_00068a30;
static void (*const b6b8e0_c65e90)(void) = (void (*)(void))TIFFGetField;
static void (*const b6b8e0_c6a310)(void) = (void (*)(void))FUN_0006a310;
static void (*const b6b8e0_c6eea0)(void) = (void (*)(void))FUN_0006eea0;
static void (*const b6b8e0_c8ef70)(void *ptr, const char *file, int line) = debug_free;

__attribute__((naked, noinline))
void FUN_0006b8e0(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x1c, %%esp\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c6b780]\n\t"
      "addl $4, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%eax, -0x18(%%ebp)\n\t"
      "jne .LFUN_0006b8e0_1\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0006b8e0_1:\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "pushl $0x13c\n\t"
      "pushl $0x260264\n\t"
      "pushl $0\n\t"
      "pushl %%esi\n\t"
      "call *%[c6f910]\n\t"
      "addl $4, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[c8ee60]\n\t"
      "addl $0x10, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "jne .LFUN_0006b8e0_2\n\t"
      "movl 0x3340dc, %%ecx\n\t"
      "pushl $0x2602e8\n\t"
      "pushl %%ecx\n\t"
      "call *%[c68a30]\n\t"
      "addl $8, %%esp\n\t"
      "xorl %%eax, %%eax\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0006b8e0_2:\n\t"
      "pushl %%ebx\n\t"
      "leal -0x4(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x142\n\t"
      "pushl %%esi\n\t"
      "call *%[c65e90]\n\t"
      "leal -0x1c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x143\n\t"
      "pushl %%esi\n\t"
      "call *%[c65e90]\n\t"
      "movl 0x14(%%ebp), %%ebx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "call *%[c6a310]\n\t"
      "addl $0x20, %%esp\n\t"
      "cmpw $1, 0x3340f0\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "jne .LFUN_0006b8e0_3\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "leal (%%ecx,%%edi,1), %%eax\n\t"
      "negl %%eax\n\t"
      "jmp .LFUN_0006b8e0_4\n\t"
      ".LFUN_0006b8e0_3:\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movl %%edi, %%eax\n\t"
      "subl %%ecx, %%eax\n\t"
      ".LFUN_0006b8e0_4:\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "xorl %%eax, %%eax\n\t"
      "testl %%ebx, %%ebx\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "jbe .LFUN_0006b8e0_17\n\t"
      "movl -0x1c(%%ebp), %%ecx\n\t"
      "jmp .LFUN_0006b8e0_6\n\t"
      ".LFUN_0006b8e0_5:\n\t"
      "movl 0x14(%%ebp), %%ebx\n\t"
      ".LFUN_0006b8e0_6:\n\t"
      "leal (%%eax,%%ecx,1), %%edx\n\t"
      "cmpl %%ebx, %%edx\n\t"
      "jbe .LFUN_0006b8e0_7\n\t"
      "subl %%eax, %%ebx\n\t"
      "jmp .LFUN_0006b8e0_8\n\t"
      ".LFUN_0006b8e0_7:\n\t"
      "movl %%ecx, %%ebx\n\t"
      ".LFUN_0006b8e0_8:\n\t"
      "xorl %%esi, %%esi\n\t"
      "testl %%edi, %%edi\n\t"
      "jbe .LFUN_0006b8e0_15\n\t"
      "jmp .LFUN_0006b8e0_10\n\t"
      ".LFUN_0006b8e0_9:\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "jmp .LFUN_0006b8e0_10\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".LFUN_0006b8e0_10:\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c6eea0]\n\t"
      "addl $0x18, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jge .LFUN_0006b8e0_11\n\t"
      "movl 0x3340e0, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_0006b8e0_14\n\t"
      ".LFUN_0006b8e0_11:\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "leal (%%esi,%%ecx,1), %%edx\n\t"
      "cmpl %%edi, %%edx\n\t"
      "movl -0x10(%%ebp), %%edx\n\t"
      "jbe .LFUN_0006b8e0_12\n\t"
      "movl %%edi, %%eax\n\t"
      "subl %%esi, %%eax\n\t"
      "subl %%eax, %%ecx\n\t"
      "addl %%ecx, %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "jmp .LFUN_0006b8e0_13\n\t"
      ".LFUN_0006b8e0_12:\n\t"
      "pushl %%edx\n\t"
      "pushl $0\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ecx\n\t"
      ".LFUN_0006b8e0_13:\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "imull %%edi, %%edx\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "pushl %%eax\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "addl %%esi, %%edx\n\t"
      "pushl %%ecx\n\t"
      "leal (%%eax,%%edx,4), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *-0x18(%%ebp)\n\t"
      "addl -0x4(%%ebp), %%esi\n\t"
      "addl $0x1c, %%esp\n\t"
      "cmpl %%edi, %%esi\n\t"
      "jb .LFUN_0006b8e0_9\n\t"
      ".LFUN_0006b8e0_14:\n\t"
      "movl -0x1c(%%ebp), %%ecx\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      ".LFUN_0006b8e0_15:\n\t"
      "cmpw $1, 0x3340f0\n\t"
      "jne .LFUN_0006b8e0_16\n\t"
      "negl %%ebx\n\t"
      ".LFUN_0006b8e0_16:\n\t"
      "addl %%ebx, -0x8(%%ebp)\n\t"
      "movl 0x14(%%ebp), %%edx\n\t"
      "addl %%ecx, %%eax\n\t"
      "cmpl %%edx, %%eax\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "jb .LFUN_0006b8e0_5\n\t"
      ".LFUN_0006b8e0_17:\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "pushl $0x15a\n\t"
      "pushl $0x260264\n\t"
      "pushl %%edx\n\t"
      "call *%[c8ef70]\n\t"
      "addl $0xc, %%esp\n\t"
      "popl %%ebx\n\t"
      "movl $1, %%eax\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c6b780] "m"(b6b8e0_c6b780), [c6f910] "m"(b6b8e0_c6f910), [c8ee60] "m"(b6b8e0_c8ee60), [c68a30] "m"(b6b8e0_c68a30), [c65e90] "m"(b6b8e0_c65e90), [c6a310] "m"(b6b8e0_c6a310), [c6eea0] "m"(b6b8e0_c6eea0), [c8ef70] "m"(b6b8e0_c8ef70)
      : "memory");
}
#else
#error "FUN_0006b8e0: clang naked draft required"
#endif


/* FUN_0006ba70 (0x6ba70) — XBE naked draft (batch 339). */
#if defined(__clang__)
static void (*const b6ba70_c68a30)(int param_1, const char *format, ...) = (void (*)(int, const char *, ...))FUN_00068a30;
static void (*const b6ba70_c6f910)(void) = (void (*)(void))FUN_0006f910;
static void * (*const b6ba70_c8ee60)(uint32_t size, bool zero, const char *file, int line) = debug_malloc;
static void (*const b6ba70_c65e90)(void) = (void (*)(void))TIFFGetField;
static void (*const b6ba70_c6a310)(void) = (void (*)(void))FUN_0006a310;
static void (*const b6ba70_c6eea0)(void) = (void (*)(void))FUN_0006eea0;
static void (*const b6ba70_c8ef70)(void *ptr, const char *file, int line) = debug_free;

__attribute__((naked, noinline))
void FUN_0006ba70(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x24, %%esp\n\t"
      "movzwl 0x3340f4, %%eax\n\t"
      "subl $2, %%eax\n\t"
      "movl $0, -0x4(%%ebp)\n\t"
      "jne .LFUN_0006ba70_2\n\t"
      "cmpw $8, 0x3340fc\n\t"
      "movl $0x6b190, -0x4(%%ebp)\n\t"
      "je .LFUN_0006ba70_1\n\t"
      "movl $0x6b2d0, -0x4(%%ebp)\n\t"
      ".LFUN_0006ba70_1:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_0006ba70_3\n\t"
      ".LFUN_0006ba70_2:\n\t"
      "movl 0x3340dc, %%eax\n\t"
      "pushl $0x2602d0\n\t"
      "pushl %%eax\n\t"
      "call *%[c68a30]\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_0006ba70_3\n\t"
      "xorl %%eax, %%eax\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0006ba70_3:\n\t"
      "pushl %%ebx\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%ebx\n\t"
      "call *%[c6f910]\n\t"
      "pushl $0x178\n\t"
      "movl %%eax, %%esi\n\t"
      "pushl $0x260264\n\t"
      "leal (%%esi,%%esi,2), %%ecx\n\t"
      "pushl $0\n\t"
      "pushl %%ecx\n\t"
      "call *%[c8ee60]\n\t"
      "addl $0x14, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "jne .LFUN_0006ba70_4\n\t"
      "movl 0x3340dc, %%edx\n\t"
      "pushl $0x2602e8\n\t"
      "pushl %%edx\n\t"
      "call *%[c68a30]\n\t"
      "addl $8, %%esp\n\t"
      "popl %%esi\n\t"
      "xorl %%eax, %%eax\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0006ba70_4:\n\t"
      "addl %%esi, %%eax\n\t"
      "movl %%eax, -0x20(%%ebp)\n\t"
      "addl %%esi, %%eax\n\t"
      "movl %%eax, -0x1c(%%ebp)\n\t"
      "leal -0xc(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x142\n\t"
      "pushl %%ebx\n\t"
      "call *%[c65e90]\n\t"
      "leal -0x24(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x143\n\t"
      "pushl %%ebx\n\t"
      "call *%[c65e90]\n\t"
      "movl 0x14(%%ebp), %%esi\n\t"
      "pushl %%esi\n\t"
      "pushl %%ebx\n\t"
      "call *%[c6a310]\n\t"
      "addl $0x20, %%esp\n\t"
      "cmpw $1, 0x3340f0\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "jne .LFUN_0006ba70_5\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "leal (%%edx,%%edi,1), %%eax\n\t"
      "negl %%eax\n\t"
      "jmp .LFUN_0006ba70_6\n\t"
      ".LFUN_0006ba70_5:\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "movl %%edi, %%eax\n\t"
      "subl %%ecx, %%eax\n\t"
      ".LFUN_0006ba70_6:\n\t"
      "movl %%eax, -0x18(%%ebp)\n\t"
      "xorl %%eax, %%eax\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "jbe .LFUN_0006ba70_21\n\t"
      "movl -0x24(%%ebp), %%ecx\n\t"
      "jmp .LFUN_0006ba70_8\n\t"
      ".LFUN_0006ba70_7:\n\t"
      "movl 0x14(%%ebp), %%esi\n\t"
      "jmp .LFUN_0006ba70_8\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".LFUN_0006ba70_8:\n\t"
      "leal (%%eax,%%ecx,1), %%edx\n\t"
      "cmpl %%esi, %%edx\n\t"
      "jbe .LFUN_0006ba70_9\n\t"
      "movl %%esi, %%ebx\n\t"
      "subl %%eax, %%ebx\n\t"
      "jmp .LFUN_0006ba70_10\n\t"
      ".LFUN_0006ba70_9:\n\t"
      "movl %%ecx, %%ebx\n\t"
      ".LFUN_0006ba70_10:\n\t"
      "xorl %%esi, %%esi\n\t"
      "testl %%edi, %%edi\n\t"
      "jbe .LFUN_0006ba70_19\n\t"
      "jmp .LFUN_0006ba70_12\n\t"
      ".LFUN_0006ba70_11:\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movl %%edi, %%edi\n\t"
      ".LFUN_0006ba70_12:\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c6eea0]\n\t"
      "addl $0x18, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jge .LFUN_0006ba70_13\n\t"
      "movl 0x3340e0, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_0006ba70_18\n\t"
      ".LFUN_0006ba70_13:\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "movl -0x20(%%ebp), %%eax\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "pushl $1\n\t"
      "pushl $0\n\t"
      "pushl %%edx\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c6eea0]\n\t"
      "addl $0x18, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jge .LFUN_0006ba70_14\n\t"
      "movl 0x3340e0, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_0006ba70_18\n\t"
      ".LFUN_0006ba70_14:\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "movl -0x1c(%%ebp), %%eax\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "pushl $2\n\t"
      "pushl $0\n\t"
      "pushl %%edx\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c6eea0]\n\t"
      "addl $0x18, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jge .LFUN_0006ba70_15\n\t"
      "movl 0x3340e0, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_0006ba70_18\n\t"
      ".LFUN_0006ba70_15:\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "leal (%%esi,%%ecx,1), %%edx\n\t"
      "cmpl %%edi, %%edx\n\t"
      "movl -0x18(%%ebp), %%edx\n\t"
      "jbe .LFUN_0006ba70_16\n\t"
      "movl %%edi, %%eax\n\t"
      "subl %%esi, %%eax\n\t"
      "subl %%eax, %%ecx\n\t"
      "addl %%ecx, %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "jmp .LFUN_0006ba70_17\n\t"
      ".LFUN_0006ba70_16:\n\t"
      "pushl %%edx\n\t"
      "pushl $0\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ecx\n\t"
      ".LFUN_0006ba70_17:\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "movl -0x1c(%%ebp), %%ecx\n\t"
      "movl -0x20(%%ebp), %%edx\n\t"
      "pushl %%eax\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "pushl %%ecx\n\t"
      "movl -0x10(%%ebp), %%ecx\n\t"
      "imull %%edi, %%ecx\n\t"
      "pushl %%edx\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "addl %%esi, %%ecx\n\t"
      "pushl %%eax\n\t"
      "leal (%%edx,%%ecx,4), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *-0x4(%%ebp)\n\t"
      "addl -0xc(%%ebp), %%esi\n\t"
      "addl $0x24, %%esp\n\t"
      "cmpl %%edi, %%esi\n\t"
      "jb .LFUN_0006ba70_11\n\t"
      ".LFUN_0006ba70_18:\n\t"
      "movl -0x24(%%ebp), %%ecx\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      ".LFUN_0006ba70_19:\n\t"
      "cmpw $1, 0x3340f0\n\t"
      "jne .LFUN_0006ba70_20\n\t"
      "negl %%ebx\n\t"
      ".LFUN_0006ba70_20:\n\t"
      "addl %%ebx, -0x10(%%ebp)\n\t"
      "movl 0x14(%%ebp), %%edx\n\t"
      "addl %%ecx, %%eax\n\t"
      "cmpl %%edx, %%eax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "jb .LFUN_0006ba70_7\n\t"
      ".LFUN_0006ba70_21:\n\t"
      "movl -0x14(%%ebp), %%ecx\n\t"
      "pushl $0x19c\n\t"
      "pushl $0x260264\n\t"
      "pushl %%ecx\n\t"
      "call *%[c8ef70]\n\t"
      "addl $0xc, %%esp\n\t"
      "popl %%esi\n\t"
      "movl $1, %%eax\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c68a30] "m"(b6ba70_c68a30), [c6f910] "m"(b6ba70_c6f910), [c8ee60] "m"(b6ba70_c8ee60), [c65e90] "m"(b6ba70_c65e90), [c6a310] "m"(b6ba70_c6a310), [c6eea0] "m"(b6ba70_c6eea0), [c8ef70] "m"(b6ba70_c8ef70)
      : "memory");
}
#else
#error "FUN_0006ba70: clang naked draft required"
#endif

