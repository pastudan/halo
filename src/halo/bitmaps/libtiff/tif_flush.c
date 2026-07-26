/* kb object: tif_flush.obj -> bitmaps/libtiff/tif_flush.c */

/* --- tif_flush.obj batch drafts (2026-07-26) --- */

/* 0x68780 */
void FUN_00068780(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int edi = 0;

  /* cmp eax, ecx -> jle 0x687b1 */
  TIFFFlushData1();
  /* test eax, eax -> jne 0x687b1 */
  csmemcpy((void *)(uintptr_t)edx, (void *)(uintptr_t)ecx, edi);
  /* test (char)eax, 0x10 -> je 0x68828 */
  /* cmp eax, 0x10 -> je 0x68811 */
  /* cmp eax, 0x20 -> jne 0x68828 */
  FUN_0006f220();
  FUN_0006f1f0();
  TIFFFlushData1();
  /* test eax, eax -> je 0x68879 */
  /* test ebx, ebx -> jg 0x687c0 */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)edi;
}

/* 0x68890 */
void FUN_00068890(void)
{
  int eax = 0;
  int ebx = 0;
  int esi = 0;
  int edi = 0;

  /* cmp eax, edi -> jge 0x688c2 */
  FUN_00068a30(0, (char *)0x0025fff0);
  /* cmp eax, ebx -> je 0x688db */
  csmemcpy((void *)(uintptr_t)ebx, (void *)(uintptr_t)eax, edi);
  /* relift: test byte ptr [esi + 0xa], 0x10 -> je 0x68914 */
  /* cmp eax, 0x10 -> je 0x68903 */
  /* cmp eax, 0x20 -> jne 0x68914 */
  FUN_0006f220();
  FUN_0006f1f0();

  (void)eax;
  (void)ebx;
  (void)esi;
  (void)edi;
}

/* 0x68940 */
void FUN_00068940(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x68970 */
void FUN_00068970(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x689c0 */
void FUN_000689c0(void)
{
  int eax = 0;

  /* test eax, eax -> je 0x689dd */
  crt_fprintf((void *)0x00331070, (char *)0x00259f68);
  FUN_001d9850();
  crt_fprintf((void *)0x00331070, (char *)0x00260020);

  (void)eax;
}

/* 0x68a10 */
void FUN_00068a10(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x68a30 */
void FUN_00068a30(int param_1, const char *format, ...)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x68a50 */
void FUN_00068a50(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
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


/* 0x68bd0 */
void FUN_00068bd0(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x68c40 */
void FUN_00068c40(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x68c70 */
void FUN_00068c70(void)
{
  int eax = 0;
  int ebx = 0;
  int esi = 0;

  FUN_00068a30(0, (char *)0x00260084);
  FUN_0006f890();
  TIFFScanlineSize();
  /* test (char)eax, 1 -> jne 0x68cca */
  /* relift: cmp word ptr [esi + 0x3a], 4 -> jne 0x68cd1 */
  debug_malloc(ebx, 0, (char *)0x00260058, 252);
  FUN_00068a30(0x00260024, (char *)0x00260034);
  /* relift: test byte ptr [esi + 0x68], 1 -> jne 0x68d57 */
  /* relift: cmp word ptr [esi + 0x3a], 4 -> je 0x68d57 */

  (void)eax;
  (void)ebx;
  (void)esi;
}

/* 0x68d80 */
void FUN_00068d80(void)
{
  int ebx = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;

  /* cmp esi, ebx -> jne 0x68dae */
  FUN_00068c70();
  /* cmp esi, ebx -> jne 0x68dae */
  /* cmp ecx, ebx -> jle 0x68df3 */
  /* relift: test byte ptr [edi + 9], 2 -> jne 0x68e15 */
  FUN_00068a70();
  /* relift: test byte ptr [edi + 0x68], 1 -> je 0x68e15 */
  FUN_00068bd0();

  (void)ebx;
  (void)ecx;
  (void)esi;
  (void)edi;
}

/* 0x68e20 */
void FUN_00068e20(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x68eb0 */
void FUN_00068eb0(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x68f60 */
void FUN_00068f60(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* FUN_00069020 (0x69020) — XBE naked draft (batch 300). */
#if defined(__clang__)
static void (*const b69020_c68eb0)(void) = FUN_00068eb0;
static void (*const b69020_c68f60)(void) = FUN_00068f60;
static void (*const b69020_c68e20)(void) = FUN_00068e20;
static void (*const b69020_c68a30)(int param_1, const char *format, ...) = FUN_00068a30;
static void (*const b69020_c68a70)(void) = FUN_00068a70;
static void (*const b69020_c6f9d0)(void) = FUN_0006f9d0;

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


/* 0x69180 */
void FUN_00069180(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* FUN_00069200 (0x69200) — XBE naked draft (batch 311). */
#if defined(__clang__)
static void (*const b69200_c6fe10)(void) = TIFFFlushData1;

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
static void (*const b69310_c69200)(void) = FUN_00069200;

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


/* 0x693b0 */
void FUN_000693b0(void)
{
  int eax = 0;

  /* cmp eax, 4 -> je 0x693e1 */
  FUN_00069200();
  FUN_00069200();
  /* test (char)eax, 1 -> je 0x6940f */
  FUN_00069200();

  (void)eax;
}

/* 0x69420 */
void FUN_00069420(void)
{
  int ecx = 0;
  int esi = 0;

  /* test esi, esi -> jne 0x6946d */
  FUN_00068c70();
  /* test esi, esi -> jne 0x69448 */
  /* relift: cmp word ptr [esi + 4], 0 -> jne 0x6945f */
  /* test ecx, ecx -> jle 0x694b9 */
  /* relift: relift: fcomp dword ptr [0x260134] */

  (void)ecx;
  (void)esi;
}

/* 0x69520 */
void FUN_00069520(void)
{
  int eax = 0;
  int esi = 0;
  int edi = 0;

  /* relift: cmp word ptr [edi + 2], 8 -> je 0x69582 */
  /* relift: cmp eax, dword ptr [esi + 0x130] -> jl 0x6954c */
  TIFFFlushData1();

  (void)eax;
  (void)esi;
  (void)edi;
}

/* 0x69590 */
void FUN_00069590(void)
{
  int esi = 0;

  /* relift: test byte ptr [esi + 9], 1 -> jne 0x695b9 */
  FUN_000693b0();
  FUN_00069520();

  (void)esi;
}

/* 0x695c0 */
void FUN_000695c0(void)
{
  int eax = 0;

  /* test eax, eax -> je 0x695ee */
  debug_free((void *)(uintptr_t)eax, (char *)0x00260058, 1077);

  (void)eax;
}

/* 0x69600 */
void FUN_00069600(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x69690 */
void FUN_00069690(void)
{
  FUN_00069600();
}

/* FUN_000696d0 (0x696d0) — XBE naked draft (batch 297). */
#if defined(__clang__)
static void (*const b696d0_c69600)(void) = FUN_00069600;
static void (*const b696d0_c68e20)(void) = FUN_00068e20;
static void (*const b696d0_c68eb0)(void) = FUN_00068eb0;
static void (*const b696d0_c68f60)(void) = FUN_00068f60;
static void (*const b696d0_c69180)(void) = FUN_00069180;
static void (*const b696d0_c68bd0)(void) = FUN_00068bd0;
static void (*const b696d0_c6f9d0)(void) = FUN_0006f9d0;
static void (*const b696d0_c68a70)(void) = FUN_00068a70;
static void (*const b696d0_c68a30)(int param_1, const char *format, ...) = FUN_00068a30;

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


/* 0x69b90 */
void FUN_00069b90(void)
{
  int esi = 0;
  int edi = 0;

  FUN_00069600();
  FUN_00069310();
  /* cmp esi, edi -> jge 0x69c2a */
  FUN_00069600();
  FUN_00069310();
  /* cmp esi, edi -> jge 0x69c2a */
  FUN_00069600();
  FUN_00069310();
  /* cmp esi, edi -> jl 0x69bd0 */

  (void)esi;
  (void)edi;
}

/* FUN_00069c40 (0x69c40) — XBE naked draft (batch 299). */
#if defined(__clang__)
static void (*const b69c40_c69600)(void) = FUN_00069600;
static void (*const b69c40_c69200)(void) = FUN_00069200;
static void (*const b69c40_c69310)(void) = FUN_00069310;

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


/* 0x69f30 */
void FUN_00069f30(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;

  /* cmp eax, 4 -> je 0x69f7e */
  FUN_00069200();
  FUN_00069200();
  /* test (char)eax, 1 -> je 0x6a02e */
  FUN_00069200();
  /* test (char)eax, 1 -> je 0x6a02e */
  FUN_00069b90();
  /* test eax, eax -> je 0x6a067 */
  FUN_00069c40();
  /* test eax, eax -> je 0x6a067 */
  /* relift: cmp word ptr [esi + 0x24], 0 -> jne 0x6a018 */
  csmemcpy((void *)(uintptr_t)eax, (void *)(uintptr_t)edx, ecx);
  FUN_00069b90();
  /* test eax, eax -> je 0x6a067 */

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
}

/* 0x6a070 */
void FUN_0006a070(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;

  csmemset((void *)(uintptr_t)ebx, 0, eax);
  /* test eax, eax -> jle 0x6a171 */
  /* test eax, eax -> jne 0x6a0b8 */
  FUN_00069020();
  FUN_000696d0();
  /* test eax, eax -> je 0x6a17b */
  /* relift: test byte ptr [esi + 0x68], 1 -> je 0x6a159 */
  /* relift: cmp word ptr [eax + 2], 0 -> jne 0x6a110 */
  /* test ecx, ecx -> jle 0x6a110 */
  csmemcpy((void *)(uintptr_t)eax, (void *)(uintptr_t)ebx, edx);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
}

/* 0x6a190 */
void FUN_0006a190(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x6a210 */
void FUN_0006a210(void)
{
  int eax = 0;
  int ecx = 0;

  /* test (char)eax, 8 -> je 0x6a249 */
  /* test (int16_t)ecx, (int16_t)ecx -> je 0x6a24e */
  /* test eax, eax -> je 0x6a24e */
  /* test eax, eax -> jne 0x6a24e */
  TIFFFlushData1();

  (void)eax;
  (void)ecx;
}

/* 0x6a260 */
int FUN_0006a260(int file)
{
  int eax = 0;
  int esi = 0;

  /* relift: cmp word ptr [esi + 6], 0 -> je 0x6a293 */
  FUN_0006a210();
  /* test eax, eax -> je 0x6a28e */
  /* relift: test byte ptr [esi + 0xa], 2 -> je 0x6a293 */
  FUN_000680a0();
  /* test eax, eax -> jne 0x6a293 */
  return 1;

  (void)eax;
  (void)esi;
}

/* 0x6a2a0 */
void FUN_0006a2a0(void)
{
  int eax = 0;
  int edi = 0;

  /* cmp (int16_t)edi, 0x100 -> jae 0x6a2f8 */
  /* cmp (int16_t)edi, 0x100 -> jae 0x6a2f8 */
  /* cmp (int16_t)edi, 0x100 -> jae 0x6a2f8 */
  /* test eax, eax -> jg 0x6a2b0 */
  FUN_0006f9d0();

  (void)eax;
  (void)edi;
}

/* 0x6a310 */
void FUN_0006a310(void)
{
  int eax = 0;

  FUN_00064ec0(0, 0, 0);
  /* cmp eax, 7 -> ja 0x6a35e */
  FUN_0006f9d0();
  /* relift: relift: mov word ptr [0x3340f0], 4 */
  FUN_0006f9d0();
  /* relift: relift: mov word ptr [0x3340f0], 1 */
  /* mem[0xa35e0006] = eax */
  /* mem[0x90900006] = eax */

  (void)eax;
}

/* FUN_0006a3b0 (0x6a3b0) — XBE naked draft (batch 309). */
#if defined(__clang__)
static void * (*const b6a3b0_c8ee60)(uint32_t size, bool zero, const char *file, int line) = debug_malloc;
static void (*const b6a3b0_c68a30)(int param_1, const char *format, ...) = FUN_00068a30;

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
static void (*const b6a5d0_c68a30)(int param_1, const char *format, ...) = FUN_00068a30;

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


/* 0x6a910 */
void FUN_0006a910(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x6a9a0 */
void FUN_0006a9a0(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* FUN_0006aa40 (0x6aa40) — XBE naked draft (batch 307). */
#if defined(__clang__)


__attribute__((naked, noinline))
void FUN_0006aa40(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "movl 0x1c(%%ebp), %%eax\n\t"
      "movl 0x18(%%ebp), %%ecx\n\t"
      "cdq\n\t"
      "andl $3, %%edx\n\t"
      "addl %%edx, %%eax\n\t"
      "sarl $2, %%eax\n\t"
      "testl %%ecx, %%ecx\n\t"
      "movl %%eax, 0x1c(%%ebp)\n\t"
      "jbe .LFUN_0006aa40_7\n\t"
      "movl 0x20(%%ebp), %%edx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0xc(%%ebp), %%esi\n\t"
      "shll $2, %%edx\n\t"
      "movl %%ecx, 0x18(%%ebp)\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "pushl %%edi\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      ".LFUN_0006aa40_1:\n\t"
      "movl 0x14(%%ebp), %%edi\n\t"
      "cmpl $4, %%edi\n\t"
      "jb .LFUN_0006aa40_3\n\t"
      "movl %%edi, %%ebx\n\t"
      "shrl $2, %%ebx\n\t"
      ".LFUN_0006aa40_2:\n\t"
      "movzbl (%%esi), %%eax\n\t"
      "movl 0x3340c4, %%edx\n\t"
      "movl (%%edx,%%eax,4), %%edx\n\t"
      "movl (%%edx), %%eax\n\t"
      "movl %%eax, (%%ecx)\n\t"
      "movl 0x4(%%edx), %%eax\n\t"
      "addl $4, %%edx\n\t"
      "addl $4, %%ecx\n\t"
      "movl %%eax, (%%ecx)\n\t"
      "movl 0x4(%%edx), %%eax\n\t"
      "addl $4, %%edx\n\t"
      "addl $4, %%ecx\n\t"
      "movl %%eax, (%%ecx)\n\t"
      "movl 0x4(%%edx), %%edx\n\t"
      "addl $4, %%ecx\n\t"
      "movl %%edx, (%%ecx)\n\t"
      "incl %%esi\n\t"
      "addl $4, %%ecx\n\t"
      "subl $4, %%edi\n\t"
      "decl %%ebx\n\t"
      "jne .LFUN_0006aa40_2\n\t"
      "movl 0x1c(%%ebp), %%eax\n\t"
      ".LFUN_0006aa40_3:\n\t"
      "testl %%edi, %%edi\n\t"
      "jbe .LFUN_0006aa40_6\n\t"
      "movzbl (%%esi), %%edx\n\t"
      "movl 0x3340c4, %%ebx\n\t"
      "movl (%%ebx,%%edx,4), %%edx\n\t"
      "incl %%esi\n\t"
      "decl %%edi\n\t"
      "je .LFUN_0006aa40_5\n\t"
      "decl %%edi\n\t"
      "je .LFUN_0006aa40_4\n\t"
      "decl %%edi\n\t"
      "jne .LFUN_0006aa40_6\n\t"
      "movl (%%edx), %%edi\n\t"
      "movl %%edi, (%%ecx)\n\t"
      "addl $4, %%ecx\n\t"
      "addl $4, %%edx\n\t"
      ".LFUN_0006aa40_4:\n\t"
      "movl (%%edx), %%edi\n\t"
      "movl %%edi, (%%ecx)\n\t"
      "addl $4, %%ecx\n\t"
      "addl $4, %%edx\n\t"
      ".LFUN_0006aa40_5:\n\t"
      "movl (%%edx), %%edx\n\t"
      "movl %%edx, (%%ecx)\n\t"
      "addl $4, %%ecx\n\t"
      ".LFUN_0006aa40_6:\n\t"
      "movl -0x4(%%ebp), %%ebx\n\t"
      "movl 0x18(%%ebp), %%edx\n\t"
      "addl %%ebx, %%ecx\n\t"
      "addl %%eax, %%esi\n\t"
      "decl %%edx\n\t"
      "movl %%edx, 0x18(%%ebp)\n\t"
      "jne .LFUN_0006aa40_1\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      ".LFUN_0006aa40_7:\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "FUN_0006aa40: clang naked draft required"
#endif


/* FUN_0006ab10 (0x6ab10) — XBE naked draft (batch 303). */
#if defined(__clang__)


__attribute__((naked, noinline))
void FUN_0006ab10(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "movl 0x1c(%%ebp), %%eax\n\t"
      "movl 0x18(%%ebp), %%ecx\n\t"
      "cdq\n\t"
      "andl $7, %%edx\n\t"
      "addl %%edx, %%eax\n\t"
      "sarl $3, %%eax\n\t"
      "testl %%ecx, %%ecx\n\t"
      "movl %%eax, 0x1c(%%ebp)\n\t"
      "jbe .LFUN_0006ab10_12\n\t"
      "movl 0x20(%%ebp), %%edx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0xc(%%ebp), %%esi\n\t"
      "shll $2, %%edx\n\t"
      "movl %%ecx, 0x18(%%ebp)\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "pushl %%edi\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      ".LFUN_0006ab10_1:\n\t"
      "movl 0x14(%%ebp), %%edi\n\t"
      "cmpl $8, %%edi\n\t"
      "jb .LFUN_0006ab10_3\n\t"
      "movl %%edi, %%ebx\n\t"
      "shrl $3, %%ebx\n\t"
      ".LFUN_0006ab10_2:\n\t"
      "movzbl (%%esi), %%eax\n\t"
      "movl 0x3340c4, %%edx\n\t"
      "movl (%%edx,%%eax,4), %%edx\n\t"
      "movl (%%edx), %%eax\n\t"
      "movl %%eax, (%%ecx)\n\t"
      "movl 0x4(%%edx), %%eax\n\t"
      "movl %%eax, 0x4(%%ecx)\n\t"
      "addl $4, %%edx\n\t"
      "movl 0x4(%%edx), %%eax\n\t"
      "addl $4, %%ecx\n\t"
      "movl %%eax, 0x4(%%ecx)\n\t"
      "addl $4, %%edx\n\t"
      "movl 0x4(%%edx), %%eax\n\t"
      "addl $4, %%ecx\n\t"
      "movl %%eax, 0x4(%%ecx)\n\t"
      "addl $4, %%edx\n\t"
      "movl 0x4(%%edx), %%eax\n\t"
      "addl $4, %%ecx\n\t"
      "movl %%eax, 0x4(%%ecx)\n\t"
      "addl $4, %%edx\n\t"
      "movl 0x4(%%edx), %%eax\n\t"
      "addl $4, %%ecx\n\t"
      "addl $4, %%edx\n\t"
      "addl $4, %%ecx\n\t"
      "movl %%eax, (%%ecx)\n\t"
      "movl 0x4(%%edx), %%eax\n\t"
      "addl $4, %%edx\n\t"
      "addl $4, %%ecx\n\t"
      "movl %%eax, (%%ecx)\n\t"
      "movl 0x4(%%edx), %%edx\n\t"
      "addl $4, %%ecx\n\t"
      "movl %%edx, (%%ecx)\n\t"
      "incl %%esi\n\t"
      "addl $4, %%ecx\n\t"
      "subl $8, %%edi\n\t"
      "decl %%ebx\n\t"
      "jne .LFUN_0006ab10_2\n\t"
      "movl 0x1c(%%ebp), %%eax\n\t"
      ".LFUN_0006ab10_3:\n\t"
      "testl %%edi, %%edi\n\t"
      "jbe .LFUN_0006ab10_11\n\t"
      "movzbl (%%esi), %%edx\n\t"
      "movl 0x3340c4, %%ebx\n\t"
      "movl (%%ebx,%%edx,4), %%edx\n\t"
      "incl %%esi\n\t"
      "decl %%edi\n\t"
      "cmpl $6, %%edi\n\t"
      "ja .LFUN_0006ab10_11\n\t"
      "jmp *.LFUN_0006ab10_jt(,%%edi,4)\n\t"
      ".LFUN_0006ab10_4:\n\t"
      "movl (%%edx), %%edi\n\t"
      "movl %%edi, (%%ecx)\n\t"
      "addl $4, %%ecx\n\t"
      "addl $4, %%edx\n\t"
      ".LFUN_0006ab10_5:\n\t"
      "movl (%%edx), %%edi\n\t"
      "movl %%edi, (%%ecx)\n\t"
      "addl $4, %%ecx\n\t"
      "addl $4, %%edx\n\t"
      ".LFUN_0006ab10_6:\n\t"
      "movl (%%edx), %%edi\n\t"
      "movl %%edi, (%%ecx)\n\t"
      "addl $4, %%ecx\n\t"
      "addl $4, %%edx\n\t"
      ".LFUN_0006ab10_7:\n\t"
      "movl (%%edx), %%edi\n\t"
      "movl %%edi, (%%ecx)\n\t"
      "addl $4, %%ecx\n\t"
      "addl $4, %%edx\n\t"
      ".LFUN_0006ab10_8:\n\t"
      "movl (%%edx), %%edi\n\t"
      "movl %%edi, (%%ecx)\n\t"
      "addl $4, %%ecx\n\t"
      "addl $4, %%edx\n\t"
      ".LFUN_0006ab10_9:\n\t"
      "movl (%%edx), %%edi\n\t"
      "movl %%edi, (%%ecx)\n\t"
      "addl $4, %%ecx\n\t"
      "addl $4, %%edx\n\t"
      ".LFUN_0006ab10_10:\n\t"
      "movl (%%edx), %%edx\n\t"
      "movl %%edx, (%%ecx)\n\t"
      "addl $4, %%ecx\n\t"
      ".LFUN_0006ab10_11:\n\t"
      "movl -0x4(%%ebp), %%ebx\n\t"
      "movl 0x18(%%ebp), %%edx\n\t"
      "addl %%ebx, %%ecx\n\t"
      "addl %%eax, %%esi\n\t"
      "decl %%edx\n\t"
      "movl %%edx, 0x18(%%ebp)\n\t"
      "jne .LFUN_0006ab10_1\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      ".LFUN_0006ab10_12:\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "nop\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_0006ab10_jt:\n\t"
      ".long .LFUN_0006ab10_10\n\t"
      ".long .LFUN_0006ab10_9\n\t"
      ".long .LFUN_0006ab10_8\n\t"
      ".long .LFUN_0006ab10_7\n\t"
      ".long .LFUN_0006ab10_6\n\t"
      ".long .LFUN_0006ab10_5\n\t"
      ".long .LFUN_0006ab10_4\n\t"
      ".text\n\t"
      :
      :
      : "memory");
}
#else
#error "FUN_0006ab10: clang naked draft required"
#endif


/* 0x6ac60 */
void FUN_0006ac60(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* FUN_0006acc0 (0x6acc0) — XBE naked draft (batch 303). */
#if defined(__clang__)


__attribute__((naked, noinline))
void FUN_0006acc0(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "movl 0x1c(%%ebp), %%eax\n\t"
      "movl 0x18(%%ebp), %%ecx\n\t"
      "cdq\n\t"
      "andl $7, %%edx\n\t"
      "addl %%edx, %%eax\n\t"
      "sarl $3, %%eax\n\t"
      "testl %%ecx, %%ecx\n\t"
      "movl %%eax, 0x1c(%%ebp)\n\t"
      "jbe .LFUN_0006acc0_12\n\t"
      "movl 0x20(%%ebp), %%edx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0xc(%%ebp), %%esi\n\t"
      "shll $2, %%edx\n\t"
      "movl %%ecx, 0x18(%%ebp)\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "pushl %%edi\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      ".LFUN_0006acc0_1:\n\t"
      "movl 0x14(%%ebp), %%edi\n\t"
      "cmpl $8, %%edi\n\t"
      "jb .LFUN_0006acc0_3\n\t"
      "movl %%edi, %%ebx\n\t"
      "shrl $3, %%ebx\n\t"
      ".LFUN_0006acc0_2:\n\t"
      "movzbl (%%esi), %%eax\n\t"
      "movl 0x3340c8, %%edx\n\t"
      "movl (%%edx,%%eax,4), %%edx\n\t"
      "movl (%%edx), %%eax\n\t"
      "movl %%eax, (%%ecx)\n\t"
      "movl 0x4(%%edx), %%eax\n\t"
      "movl %%eax, 0x4(%%ecx)\n\t"
      "addl $4, %%edx\n\t"
      "movl 0x4(%%edx), %%eax\n\t"
      "addl $4, %%ecx\n\t"
      "movl %%eax, 0x4(%%ecx)\n\t"
      "addl $4, %%edx\n\t"
      "movl 0x4(%%edx), %%eax\n\t"
      "addl $4, %%ecx\n\t"
      "movl %%eax, 0x4(%%ecx)\n\t"
      "addl $4, %%edx\n\t"
      "movl 0x4(%%edx), %%eax\n\t"
      "addl $4, %%ecx\n\t"
      "movl %%eax, 0x4(%%ecx)\n\t"
      "addl $4, %%edx\n\t"
      "movl 0x4(%%edx), %%eax\n\t"
      "addl $4, %%ecx\n\t"
      "addl $4, %%edx\n\t"
      "addl $4, %%ecx\n\t"
      "movl %%eax, (%%ecx)\n\t"
      "movl 0x4(%%edx), %%eax\n\t"
      "addl $4, %%edx\n\t"
      "addl $4, %%ecx\n\t"
      "movl %%eax, (%%ecx)\n\t"
      "movl 0x4(%%edx), %%edx\n\t"
      "addl $4, %%ecx\n\t"
      "movl %%edx, (%%ecx)\n\t"
      "incl %%esi\n\t"
      "addl $4, %%ecx\n\t"
      "subl $8, %%edi\n\t"
      "decl %%ebx\n\t"
      "jne .LFUN_0006acc0_2\n\t"
      "movl 0x1c(%%ebp), %%eax\n\t"
      ".LFUN_0006acc0_3:\n\t"
      "testl %%edi, %%edi\n\t"
      "jbe .LFUN_0006acc0_11\n\t"
      "movzbl (%%esi), %%edx\n\t"
      "movl 0x3340c8, %%ebx\n\t"
      "movl (%%ebx,%%edx,4), %%edx\n\t"
      "incl %%esi\n\t"
      "decl %%edi\n\t"
      "cmpl $6, %%edi\n\t"
      "ja .LFUN_0006acc0_11\n\t"
      "jmp *.LFUN_0006acc0_jt(,%%edi,4)\n\t"
      ".LFUN_0006acc0_4:\n\t"
      "movl (%%edx), %%edi\n\t"
      "movl %%edi, (%%ecx)\n\t"
      "addl $4, %%ecx\n\t"
      "addl $4, %%edx\n\t"
      ".LFUN_0006acc0_5:\n\t"
      "movl (%%edx), %%edi\n\t"
      "movl %%edi, (%%ecx)\n\t"
      "addl $4, %%ecx\n\t"
      "addl $4, %%edx\n\t"
      ".LFUN_0006acc0_6:\n\t"
      "movl (%%edx), %%edi\n\t"
      "movl %%edi, (%%ecx)\n\t"
      "addl $4, %%ecx\n\t"
      "addl $4, %%edx\n\t"
      ".LFUN_0006acc0_7:\n\t"
      "movl (%%edx), %%edi\n\t"
      "movl %%edi, (%%ecx)\n\t"
      "addl $4, %%ecx\n\t"
      "addl $4, %%edx\n\t"
      ".LFUN_0006acc0_8:\n\t"
      "movl (%%edx), %%edi\n\t"
      "movl %%edi, (%%ecx)\n\t"
      "addl $4, %%ecx\n\t"
      "addl $4, %%edx\n\t"
      ".LFUN_0006acc0_9:\n\t"
      "movl (%%edx), %%edi\n\t"
      "movl %%edi, (%%ecx)\n\t"
      "addl $4, %%ecx\n\t"
      "addl $4, %%edx\n\t"
      ".LFUN_0006acc0_10:\n\t"
      "movl (%%edx), %%edx\n\t"
      "movl %%edx, (%%ecx)\n\t"
      "addl $4, %%ecx\n\t"
      ".LFUN_0006acc0_11:\n\t"
      "movl -0x4(%%ebp), %%ebx\n\t"
      "movl 0x18(%%ebp), %%edx\n\t"
      "addl %%ebx, %%ecx\n\t"
      "addl %%eax, %%esi\n\t"
      "decl %%edx\n\t"
      "movl %%edx, 0x18(%%ebp)\n\t"
      "jne .LFUN_0006acc0_1\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      ".LFUN_0006acc0_12:\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "nop\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_0006acc0_jt:\n\t"
      ".long .LFUN_0006acc0_10\n\t"
      ".long .LFUN_0006acc0_9\n\t"
      ".long .LFUN_0006acc0_8\n\t"
      ".long .LFUN_0006acc0_7\n\t"
      ".long .LFUN_0006acc0_6\n\t"
      ".long .LFUN_0006acc0_5\n\t"
      ".long .LFUN_0006acc0_4\n\t"
      ".text\n\t"
      :
      :
      : "memory");
}
#else
#error "FUN_0006acc0: clang naked draft required"
#endif


/* FUN_0006ae10 (0x6ae10) — XBE naked draft (batch 308). */
#if defined(__clang__)


__attribute__((naked, noinline))
void FUN_0006ae10(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "movl 0x1c(%%ebp), %%eax\n\t"
      "movl 0x18(%%ebp), %%ecx\n\t"
      "cdq\n\t"
      "andl $3, %%edx\n\t"
      "addl %%edx, %%eax\n\t"
      "sarl $2, %%eax\n\t"
      "testl %%ecx, %%ecx\n\t"
      "movl %%eax, 0x1c(%%ebp)\n\t"
      "jbe .LFUN_0006ae10_7\n\t"
      "movl 0x20(%%ebp), %%edx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0xc(%%ebp), %%esi\n\t"
      "shll $2, %%edx\n\t"
      "movl %%ecx, 0x18(%%ebp)\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "pushl %%edi\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      ".LFUN_0006ae10_1:\n\t"
      "movl 0x14(%%ebp), %%edi\n\t"
      "cmpl $4, %%edi\n\t"
      "jb .LFUN_0006ae10_3\n\t"
      "movl %%edi, %%ebx\n\t"
      "shrl $2, %%ebx\n\t"
      ".LFUN_0006ae10_2:\n\t"
      "movzbl (%%esi), %%eax\n\t"
      "movl 0x3340c8, %%edx\n\t"
      "movl (%%edx,%%eax,4), %%edx\n\t"
      "movl (%%edx), %%eax\n\t"
      "movl %%eax, (%%ecx)\n\t"
      "movl 0x4(%%edx), %%eax\n\t"
      "addl $4, %%edx\n\t"
      "addl $4, %%ecx\n\t"
      "movl %%eax, (%%ecx)\n\t"
      "movl 0x4(%%edx), %%eax\n\t"
      "addl $4, %%edx\n\t"
      "addl $4, %%ecx\n\t"
      "movl %%eax, (%%ecx)\n\t"
      "movl 0x4(%%edx), %%edx\n\t"
      "addl $4, %%ecx\n\t"
      "movl %%edx, (%%ecx)\n\t"
      "incl %%esi\n\t"
      "addl $4, %%ecx\n\t"
      "subl $4, %%edi\n\t"
      "decl %%ebx\n\t"
      "jne .LFUN_0006ae10_2\n\t"
      "movl 0x1c(%%ebp), %%eax\n\t"
      ".LFUN_0006ae10_3:\n\t"
      "testl %%edi, %%edi\n\t"
      "jbe .LFUN_0006ae10_6\n\t"
      "movzbl (%%esi), %%edx\n\t"
      "movl 0x3340c8, %%ebx\n\t"
      "movl (%%ebx,%%edx,4), %%edx\n\t"
      "incl %%esi\n\t"
      "decl %%edi\n\t"
      "je .LFUN_0006ae10_5\n\t"
      "decl %%edi\n\t"
      "je .LFUN_0006ae10_4\n\t"
      "decl %%edi\n\t"
      "jne .LFUN_0006ae10_6\n\t"
      "movl (%%edx), %%edi\n\t"
      "movl %%edi, (%%ecx)\n\t"
      "addl $4, %%ecx\n\t"
      "addl $4, %%edx\n\t"
      ".LFUN_0006ae10_4:\n\t"
      "movl (%%edx), %%edi\n\t"
      "movl %%edi, (%%ecx)\n\t"
      "addl $4, %%ecx\n\t"
      "addl $4, %%edx\n\t"
      ".LFUN_0006ae10_5:\n\t"
      "movl (%%edx), %%edx\n\t"
      "movl %%edx, (%%ecx)\n\t"
      "addl $4, %%ecx\n\t"
      ".LFUN_0006ae10_6:\n\t"
      "movl -0x4(%%ebp), %%ebx\n\t"
      "movl 0x18(%%ebp), %%edx\n\t"
      "addl %%ebx, %%ecx\n\t"
      "addl %%eax, %%esi\n\t"
      "decl %%edx\n\t"
      "movl %%edx, 0x18(%%ebp)\n\t"
      "jne .LFUN_0006ae10_1\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      ".LFUN_0006ae10_7:\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "FUN_0006ae10: clang naked draft required"
#endif


/* 0x6aee0 */
void FUN_0006aee0(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* FUN_0006af80 (0x6af80) — XBE naked draft (batch 305). */
#if defined(__clang__)


__attribute__((naked, noinline))
void FUN_0006af80(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "movzwl 0x3340f8, %%edx\n\t"
      "imull 0x1c(%%ebp), %%edx\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "movl 0x18(%%ebp), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl %%edx, 0x1c(%%ebp)\n\t"
      "je .LFUN_0006af80_4\n\t"
      "testl %%eax, %%eax\n\t"
      "jbe .LFUN_0006af80_9\n\t"
      "movl 0x20(%%ebp), %%esi\n\t"
      "movl 0x14(%%ebp), %%edi\n\t"
      "shll $2, %%esi\n\t"
      "movl %%esi, 0x10(%%ebp)\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_0006af80_1:\n\t"
      "testl %%edi, %%edi\n\t"
      "jbe .LFUN_0006af80_3\n\t"
      ".LFUN_0006af80_2:\n\t"
      "movzbl 0x2(%%eax), %%edx\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "movb (%%edx,%%ecx,1), %%bh\n\t"
      "movzbl 0x1(%%eax), %%edx\n\t"
      "addl $4, %%esi\n\t"
      "movb (%%edx,%%ecx,1), %%bl\n\t"
      "movzbl (%%eax), %%edx\n\t"
      "movzbl (%%edx,%%ecx,1), %%edx\n\t"
      "shll $8, %%ebx\n\t"
      "orl %%edx, %%ebx\n\t"
      "movl %%ebx, -0x4(%%esi)\n\t"
      "movzwl 0x3340f8, %%edx\n\t"
      "addl %%edx, %%eax\n\t"
      "decl %%edi\n\t"
      "jne .LFUN_0006af80_2\n\t"
      "movl 0x1c(%%ebp), %%edx\n\t"
      "movl 0x14(%%ebp), %%edi\n\t"
      ".LFUN_0006af80_3:\n\t"
      "addl 0x10(%%ebp), %%esi\n\t"
      "movl -0x4(%%ebp), %%ebx\n\t"
      "addl %%edx, %%eax\n\t"
      "decl %%ebx\n\t"
      "movl %%ebx, -0x4(%%ebp)\n\t"
      "jne .LFUN_0006af80_1\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0006af80_4:\n\t"
      "testl %%eax, %%eax\n\t"
      "jbe .LFUN_0006af80_9\n\t"
      "movl 0x20(%%ebp), %%ecx\n\t"
      "movl 0x14(%%ebp), %%esi\n\t"
      "shll $2, %%ecx\n\t"
      "movl %%ecx, 0x10(%%ebp)\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      ".LFUN_0006af80_5:\n\t"
      "cmpl $8, %%esi\n\t"
      "movl %%esi, %%edi\n\t"
      "jb .LFUN_0006af80_7\n\t"
      "shrl $3, %%esi\n\t"
      ".LFUN_0006af80_6:\n\t"
      "movzbl (%%eax), %%ebx\n\t"
      "xorl %%edx, %%edx\n\t"
      "movb 0x2(%%eax), %%dh\n\t"
      "addl $4, %%ecx\n\t"
      "subl $8, %%edi\n\t"
      "movb 0x1(%%eax), %%dl\n\t"
      "shll $8, %%edx\n\t"
      "orl %%ebx, %%edx\n\t"
      "movl %%edx, -0x4(%%ecx)\n\t"
      "movzwl 0x3340f8, %%edx\n\t"
      "addl %%edx, %%eax\n\t"
      "decl %%esi\n\t"
      "jne .LFUN_0006af80_6\n\t"
      "movl 0x1c(%%ebp), %%edx\n\t"
      "movl 0x14(%%ebp), %%esi\n\t"
      ".LFUN_0006af80_7:\n\t"
      "testl %%edi, %%edi\n\t"
      "jbe .LFUN_0006af80_8\n\t"
      "movzbl (%%eax), %%edi\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "movb 0x2(%%eax), %%bh\n\t"
      "addl $4, %%ecx\n\t"
      "movb 0x1(%%eax), %%bl\n\t"
      "shll $8, %%ebx\n\t"
      "orl %%edi, %%ebx\n\t"
      "movl %%ebx, -0x4(%%ecx)\n\t"
      "movzwl 0x3340f8, %%edi\n\t"
      "addl %%edi, %%eax\n\t"
      ".LFUN_0006af80_8:\n\t"
      "addl 0x10(%%ebp), %%ecx\n\t"
      "movl -0x4(%%ebp), %%edi\n\t"
      "addl %%edx, %%eax\n\t"
      "decl %%edi\n\t"
      "movl %%edi, -0x4(%%ebp)\n\t"
      "jne .LFUN_0006af80_5\n\t"
      ".LFUN_0006af80_9:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "FUN_0006af80: clang naked draft required"
#endif


/* FUN_0006b0a0 (0x6b0a0) — XBE naked draft (batch 306). */
#if defined(__clang__)


__attribute__((naked, noinline))
void FUN_0006b0a0(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movzwl 0x3340f8, %%edx\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "imull 0x1c(%%ebp), %%edx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "je .LFUN_0006b0a0_4\n\t"
      "movl 0x18(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jbe .LFUN_0006b0a0_8\n\t"
      "movl 0x20(%%ebp), %%edi\n\t"
      "shll $2, %%edi\n\t"
      "addl %%edx, %%edx\n\t"
      "movl %%edi, 0xc(%%ebp)\n\t"
      "movl 0x14(%%ebp), %%edi\n\t"
      "movl %%esi, 0x10(%%ebp)\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "movl %%edx, 0x1c(%%ebp)\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".LFUN_0006b0a0_1:\n\t"
      "testl %%edi, %%edi\n\t"
      "jbe .LFUN_0006b0a0_3\n\t"
      ".LFUN_0006b0a0_2:\n\t"
      "movzwl 0x4(%%eax), %%edx\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "movb (%%edx,%%ecx,1), %%bh\n\t"
      "movzwl 0x2(%%eax), %%edx\n\t"
      "addl $4, %%esi\n\t"
      "movb (%%edx,%%ecx,1), %%bl\n\t"
      "movzwl (%%eax), %%edx\n\t"
      "movzbl (%%edx,%%ecx,1), %%edx\n\t"
      "shll $8, %%ebx\n\t"
      "orl %%edx, %%ebx\n\t"
      "decl %%edi\n\t"
      "movl %%ebx, -0x4(%%esi)\n\t"
      "movzwl 0x3340f8, %%edx\n\t"
      "leal (%%eax,%%edx,2), %%eax\n\t"
      "jne .LFUN_0006b0a0_2\n\t"
      "movl 0x14(%%ebp), %%edi\n\t"
      ".LFUN_0006b0a0_3:\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "movl 0x1c(%%ebp), %%ebx\n\t"
      "addl %%edx, %%esi\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "addl %%ebx, %%eax\n\t"
      "decl %%edx\n\t"
      "movl %%edx, 0x10(%%ebp)\n\t"
      "jne .LFUN_0006b0a0_1\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0006b0a0_4:\n\t"
      "movl 0x18(%%ebp), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "jbe .LFUN_0006b0a0_8\n\t"
      "movl 0x20(%%ebp), %%esi\n\t"
      "shll $2, %%esi\n\t"
      "addl %%edx, %%edx\n\t"
      "movl %%esi, 0xc(%%ebp)\n\t"
      "movl %%edx, 0x1c(%%ebp)\n\t"
      "movl 0x14(%%ebp), %%edx\n\t"
      "movl %%ecx, %%esi\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "jmp .LFUN_0006b0a0_5\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".LFUN_0006b0a0_5:\n\t"
      "testl %%edx, %%edx\n\t"
      "jbe .LFUN_0006b0a0_7\n\t"
      ".LFUN_0006b0a0_6:\n\t"
      "movzwl 0x4(%%eax), %%edi\n\t"
      "movzwl 0x2(%%eax), %%ebx\n\t"
      "shll $8, %%edi\n\t"
      "orl %%ebx, %%edi\n\t"
      "movzwl (%%eax), %%ebx\n\t"
      "shll $8, %%edi\n\t"
      "orl %%ebx, %%edi\n\t"
      "movl %%edi, (%%ecx)\n\t"
      "movzwl 0x3340f8, %%edi\n\t"
      "addl $4, %%ecx\n\t"
      "decl %%edx\n\t"
      "leal (%%eax,%%edi,2), %%eax\n\t"
      "jne .LFUN_0006b0a0_6\n\t"
      "movl 0x14(%%ebp), %%edx\n\t"
      ".LFUN_0006b0a0_7:\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "movl 0x1c(%%ebp), %%ebx\n\t"
      "addl %%edi, %%ecx\n\t"
      "addl %%ebx, %%eax\n\t"
      "decl %%esi\n\t"
      "jne .LFUN_0006b0a0_5\n\t"
      ".LFUN_0006b0a0_8:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "FUN_0006b0a0: clang naked draft required"
#endif


/* FUN_0006b190 (0x6b190) — XBE naked draft (batch 301). */
#if defined(__clang__)


__attribute__((naked, noinline))
void FUN_0006b190(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xc, %%esp\n\t"
      "movl 0x18(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "je .LFUN_0006b190_4\n\t"
      "movl 0x20(%%ebp), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "jbe .LFUN_0006b190_9\n\t"
      "movl 0x28(%%ebp), %%edx\n\t"
      "movl 0x14(%%ebp), %%edi\n\t"
      "movl 0x10(%%ebp), %%esi\n\t"
      "shll $2, %%edx\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      ".LFUN_0006b190_1:\n\t"
      "movl 0x1c(%%ebp), %%ebx\n\t"
      "testl %%ebx, %%ebx\n\t"
      "movl 0x24(%%ebp), %%edx\n\t"
      "jbe .LFUN_0006b190_3\n\t"
      "movl %%ebx, 0x18(%%ebp)\n\t"
      ".LFUN_0006b190_2:\n\t"
      "movzbl (%%edi), %%edx\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "movb (%%edx,%%eax,1), %%bh\n\t"
      "movzbl (%%esi), %%edx\n\t"
      "movb (%%edx,%%eax,1), %%bl\n\t"
      "movzbl (%%ecx), %%edx\n\t"
      "movzbl (%%edx,%%eax,1), %%edx\n\t"
      "shll $8, %%ebx\n\t"
      "orl %%edx, %%ebx\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "addl $4, %%edx\n\t"
      "movl %%ebx, -0x4(%%edx)\n\t"
      "incl %%edi\n\t"
      "movl %%edx, 0x8(%%ebp)\n\t"
      "movl 0x18(%%ebp), %%edx\n\t"
      "incl %%esi\n\t"
      "incl %%ecx\n\t"
      "decl %%edx\n\t"
      "movl %%edx, 0x18(%%ebp)\n\t"
      "jne .LFUN_0006b190_2\n\t"
      "movl 0x24(%%ebp), %%edx\n\t"
      ".LFUN_0006b190_3:\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "addl %%edx, %%ecx\n\t"
      "addl %%edx, %%esi\n\t"
      "addl %%edx, %%edi\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "addl %%edx, %%ebx\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "decl %%edx\n\t"
      "movl %%ebx, 0x8(%%ebp)\n\t"
      "movl %%edx, -0x8(%%ebp)\n\t"
      "jne .LFUN_0006b190_1\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0006b190_4:\n\t"
      "movl 0x20(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jbe .LFUN_0006b190_9\n\t"
      "movl 0x28(%%ebp), %%ecx\n\t"
      "movl 0x14(%%ebp), %%esi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "leal (,%%ecx,4), %%edx\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      "movl 0x24(%%ebp), %%edx\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      ".LFUN_0006b190_5:\n\t"
      "movl 0x1c(%%ebp), %%ebx\n\t"
      "cmpl $8, %%ebx\n\t"
      "movl %%ebx, 0x18(%%ebp)\n\t"
      "jb .LFUN_0006b190_7\n\t"
      "movl %%ebx, %%edx\n\t"
      "shrl $3, %%edx\n\t"
      "movl %%edx, -0x8(%%ebp)\n\t"
      ".LFUN_0006b190_6:\n\t"
      "movzbl (%%eax), %%ebx\n\t"
      "xorl %%edx, %%edx\n\t"
      "movb (%%esi), %%dh\n\t"
      "addl $4, %%edi\n\t"
      "movb (%%ecx), %%dl\n\t"
      "shll $8, %%edx\n\t"
      "orl %%ebx, %%edx\n\t"
      "movl 0x18(%%ebp), %%ebx\n\t"
      "movl %%edx, -0x4(%%edi)\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "incl %%esi\n\t"
      "incl %%ecx\n\t"
      "subl $8, %%ebx\n\t"
      "incl %%eax\n\t"
      "decl %%edx\n\t"
      "movl %%ebx, 0x18(%%ebp)\n\t"
      "movl %%edx, -0x8(%%ebp)\n\t"
      "jne .LFUN_0006b190_6\n\t"
      "movl 0x24(%%ebp), %%edx\n\t"
      ".LFUN_0006b190_7:\n\t"
      "movl 0x18(%%ebp), %%ebx\n\t"
      "testl %%ebx, %%ebx\n\t"
      "jbe .LFUN_0006b190_8\n\t"
      "movzbl (%%eax), %%ebx\n\t"
      "xorl %%edx, %%edx\n\t"
      "movb (%%esi), %%dh\n\t"
      "addl $4, %%edi\n\t"
      "movb (%%ecx), %%dl\n\t"
      "shll $8, %%edx\n\t"
      "orl %%ebx, %%edx\n\t"
      "movl %%edx, -0x4(%%edi)\n\t"
      "movl 0x24(%%ebp), %%edx\n\t"
      "incl %%esi\n\t"
      "incl %%ecx\n\t"
      "incl %%eax\n\t"
      ".LFUN_0006b190_8:\n\t"
      "addl -0x4(%%ebp), %%edi\n\t"
      "movl -0xc(%%ebp), %%ebx\n\t"
      "addl %%edx, %%eax\n\t"
      "addl %%edx, %%ecx\n\t"
      "addl %%edx, %%esi\n\t"
      "decl %%ebx\n\t"
      "movl %%ebx, -0xc(%%ebp)\n\t"
      "jne .LFUN_0006b190_5\n\t"
      ".LFUN_0006b190_9:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "FUN_0006b190: clang naked draft required"
#endif


/* FUN_0006b2d0 (0x6b2d0) — XBE naked draft (batch 304). */
#if defined(__clang__)


__attribute__((naked, noinline))
void FUN_0006b2d0(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x14(%%ebp), %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x18(%%ebp), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "je .LFUN_0006b2d0_5\n\t"
      "movl 0x20(%%ebp), %%edx\n\t"
      "testl %%edx, %%edx\n\t"
      "jbe .LFUN_0006b2d0_9\n\t"
      "movl 0x24(%%ebp), %%edx\n\t"
      "movl 0x28(%%ebp), %%ebx\n\t"
      "addl %%edx, %%edx\n\t"
      "shll $2, %%ebx\n\t"
      "movl %%ebx, 0x10(%%ebp)\n\t"
      "movl 0x20(%%ebp), %%ebx\n\t"
      "movl %%edx, 0xc(%%ebp)\n\t"
      "movl %%ebx, 0x18(%%ebp)\n\t"
      "jmp .LFUN_0006b2d0_2\n\t"
      ".LFUN_0006b2d0_1:\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      ".LFUN_0006b2d0_2:\n\t"
      "movl 0x1c(%%ebp), %%ebx\n\t"
      "testl %%ebx, %%ebx\n\t"
      "jbe .LFUN_0006b2d0_4\n\t"
      "movl %%ebx, 0x14(%%ebp)\n\t"
      "jmp .LFUN_0006b2d0_3\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".LFUN_0006b2d0_3:\n\t"
      "movzwl (%%esi), %%edx\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "movb (%%edx,%%edi,1), %%bh\n\t"
      "movzwl (%%ecx), %%edx\n\t"
      "addl $2, %%esi\n\t"
      "addl $2, %%ecx\n\t"
      "addl $2, %%eax\n\t"
      "movb (%%edx,%%edi,1), %%bl\n\t"
      "movzwl -0x2(%%eax), %%edx\n\t"
      "movzbl (%%edx,%%edi,1), %%edx\n\t"
      "shll $8, %%ebx\n\t"
      "orl %%edx, %%ebx\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "movl %%ebx, (%%edx)\n\t"
      "addl $4, %%edx\n\t"
      "movl %%edx, 0x8(%%ebp)\n\t"
      "decl 0x14(%%ebp)\n\t"
      "jne .LFUN_0006b2d0_3\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      ".LFUN_0006b2d0_4:\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "addl %%edx, %%eax\n\t"
      "addl %%edx, %%ecx\n\t"
      "addl %%edx, %%esi\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "addl %%edx, %%ebx\n\t"
      "movl 0x18(%%ebp), %%edx\n\t"
      "decl %%edx\n\t"
      "movl %%ebx, 0x8(%%ebp)\n\t"
      "movl %%edx, 0x18(%%ebp)\n\t"
      "jne .LFUN_0006b2d0_1\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0006b2d0_5:\n\t"
      "movl 0x20(%%ebp), %%edx\n\t"
      "testl %%edx, %%edx\n\t"
      "jbe .LFUN_0006b2d0_9\n\t"
      "movl 0x24(%%ebp), %%edi\n\t"
      "movl 0x28(%%ebp), %%ebx\n\t"
      "addl %%edi, %%edi\n\t"
      "shll $2, %%ebx\n\t"
      "movl %%edx, 0x18(%%ebp)\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "movl %%edi, 0xc(%%ebp)\n\t"
      "movl %%ebx, 0x10(%%ebp)\n\t"
      ".LFUN_0006b2d0_6:\n\t"
      "movl 0x1c(%%ebp), %%ebx\n\t"
      "testl %%ebx, %%ebx\n\t"
      "jbe .LFUN_0006b2d0_8\n\t"
      "movl %%ebx, 0x14(%%ebp)\n\t"
      "movl %%edi, %%edi\n\t"
      ".LFUN_0006b2d0_7:\n\t"
      "movzwl (%%esi), %%edi\n\t"
      "movzwl (%%ecx), %%ebx\n\t"
      "shll $8, %%edi\n\t"
      "orl %%ebx, %%edi\n\t"
      "movzwl (%%eax), %%ebx\n\t"
      "shll $8, %%edi\n\t"
      "orl %%ebx, %%edi\n\t"
      "movl %%edi, (%%edx)\n\t"
      "movl 0x14(%%ebp), %%edi\n\t"
      "addl $4, %%edx\n\t"
      "addl $2, %%esi\n\t"
      "addl $2, %%ecx\n\t"
      "addl $2, %%eax\n\t"
      "decl %%edi\n\t"
      "movl %%edi, 0x14(%%ebp)\n\t"
      "jne .LFUN_0006b2d0_7\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      ".LFUN_0006b2d0_8:\n\t"
      "addl 0x10(%%ebp), %%edx\n\t"
      "movl 0x18(%%ebp), %%ebx\n\t"
      "addl %%edi, %%eax\n\t"
      "addl %%edi, %%ecx\n\t"
      "addl %%edi, %%esi\n\t"
      "decl %%ebx\n\t"
      "movl %%ebx, 0x18(%%ebp)\n\t"
      "jne .LFUN_0006b2d0_6\n\t"
      ".LFUN_0006b2d0_9:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "FUN_0006b2d0: clang naked draft required"
#endif


/* 0x6b3f0 */
void TIFFFlushData(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* FUN_0006b440 (0x6b440) — XBE naked draft (batch 299). */
#if defined(__clang__)
static void (*const b6b440_ftol)(void) = FUN_001d9068;

__attribute__((naked, noinline))
void FUN_0006b440(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x20, %%esp\n\t"
      "testl %%edx, %%edx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl %%eax, %%edi\n\t"
      "movzbl (%%edi,%%ecx,1), %%esi\n\t"
      "movl 0x3340cc, %%eax\n\t"
      "movl %%esi, -0xc(%%ebp)\n\t"
      "movzbl 0x1(%%edi,%%ecx,1), %%ecx\n\t"
      "fildl -0xc(%%ebp)\n\t"
      "movl %%ecx, -0xc(%%ebp)\n\t"
      "movl 0xc(%%ebp), %%ebx\n\t"
      "fsubs 0x8(%%eax)\n\t"
      "fmuls 0x2602cc\n\t"
      "flds 0xc(%%eax)\n\t"
      "fsubs 0x8(%%eax)\n\t"
      ".byte 0xde, 0xf9\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "fildl -0xc(%%ebp)\n\t"
      "fsubs 0x10(%%eax)\n\t"
      "fmuls 0x2602cc\n\t"
      "flds 0x14(%%eax)\n\t"
      "fsubs 0x10(%%eax)\n\t"
      ".byte 0xde, 0xf9\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "jle .LFUN_0006b440_10\n\t"
      "movl 0x18(%%ebp), %%ecx\n\t"
      "movl 0x10(%%ebp), %%esi\n\t"
      "addl %%esi, %%ecx\n\t"
      "shll $2, %%ecx\n\t"
      "movl %%ecx, -0x20(%%ebp)\n\t"
      "movl %%edx, -0xc(%%ebp)\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_0006b440_1:\n\t"
      "xorl %%esi, %%esi\n\t"
      "testl %%ebx, %%ebx\n\t"
      "jle .LFUN_0006b440_9\n\t"
      "flds 0x3340c0\n\t"
      "fmuls -0x8(%%ebp)\n\t"
      "flds 0x3340b8\n\t"
      "fmuls -0x4(%%ebp)\n\t"
      "flds 0x3340b4\n\t"
      "fmuls -0x4(%%ebp)\n\t"
      "flds 0x3340bc\n\t"
      "fmuls -0x8(%%ebp)\n\t"
      "fstps -0x14(%%ebp)\n\t"
      ".LFUN_0006b440_2:\n\t"
      "movzbl (%%edi), %%edx\n\t"
      "movl %%edx, -0x10(%%ebp)\n\t"
      "incl %%edi\n\t"
      "fildl -0x10(%%ebp)\n\t"
      "fsubs (%%eax)\n\t"
      "fmuls 0x2602c8\n\t"
      "flds 0x4(%%eax)\n\t"
      "fsubs (%%eax)\n\t"
      ".byte 0xde, 0xf9\n\t"
      "fld %%st(3)\n\t"
      "fadd %%st(1), %%st(0)\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "fld %%st(2)\n\t"
      "fadd %%st(1), %%st(0)\n\t"
      "fstps -0x1c(%%ebp)\n\t"
      "fsub %%st(1), %%st(0)\n\t"
      "fsubs -0x14(%%ebp)\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "flds -0x10(%%ebp)\n\t"
      "faddl 0x25fea8\n\t"
      "fcoml 0x2602c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_0006b440_3\n\t"
      "fstp %%st(0)\n\t"
      "fldl 0x2602c0\n\t"
      "jmp .LFUN_0006b440_4\n\t"
      ".LFUN_0006b440_3:\n\t"
      "fcoml 0x2602b8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_0006b440_4\n\t"
      "fstp %%st(0)\n\t"
      "fldl 0x2602b8\n\t"
      ".LFUN_0006b440_4:\n\t"
      "flds -0x18(%%ebp)\n\t"
      "faddl 0x25fea8\n\t"
      "fcoml 0x2602c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_0006b440_5\n\t"
      "fstp %%st(0)\n\t"
      "fldl 0x2602c0\n\t"
      "jmp .LFUN_0006b440_6\n\t"
      ".LFUN_0006b440_5:\n\t"
      "fcoml 0x2602b8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_0006b440_6\n\t"
      "fstp %%st(0)\n\t"
      "fldl 0x2602b8\n\t"
      ".LFUN_0006b440_6:\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "faddl 0x25fea8\n\t"
      "fcoml 0x2602c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_0006b440_7\n\t"
      "fstp %%st(0)\n\t"
      "fldl 0x2602c0\n\t"
      "jmp .LFUN_0006b440_8\n\t"
      ".LFUN_0006b440_7:\n\t"
      "fcoml 0x2602b8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_0006b440_8\n\t"
      "fstp %%st(0)\n\t"
      "fldl 0x2602b8\n\t"
      ".LFUN_0006b440_8:\n\t"
      "call *%[ftol]\n\t"
      "movl %%eax, %%ebx\n\t"
      "shll $8, %%ebx\n\t"
      "call *%[ftol]\n\t"
      "orl %%eax, %%ebx\n\t"
      "shll $8, %%ebx\n\t"
      "call *%[ftol]\n\t"
      "orl %%eax, %%ebx\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl %%ebx, (%%eax,%%esi,4)\n\t"
      "movl 0xc(%%ebp), %%ebx\n\t"
      "movl 0x3340cc, %%eax\n\t"
      "incl %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "jl .LFUN_0006b440_2\n\t"
      "movl -0x20(%%ebp), %%ecx\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      ".LFUN_0006b440_9:\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "movl 0x14(%%ebp), %%esi\n\t"
      "addl %%ecx, %%edx\n\t"
      "movl %%edx, 0x8(%%ebp)\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "addl %%esi, %%edi\n\t"
      "decl %%edx\n\t"
      "movl %%edx, -0xc(%%ebp)\n\t"
      "jne .LFUN_0006b440_1\n\t"
      ".LFUN_0006b440_10:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [ftol] "m"(b6b440_ftol)
      : "memory");
}
#else
#error "FUN_0006b440: clang naked draft required"
#endif


/* FUN_0006b610 (0x6b610) — XBE naked draft (batch 310). */
#if defined(__clang__)
static void (*const b6b610_c6b440)(void) = FUN_0006b440;

__attribute__((naked, noinline))
void FUN_0006b610(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $8, %%esp\n\t"
      "movw 0x3340d8, %%cx\n\t"
      "movzwl 0x3340d4, %%eax\n\t"
      "movzwl %%cx, %%edx\n\t"
      "imull %%eax, %%edx\n\t"
      "pushl %%ebx\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      "movl 0x18(%%ebp), %%edx\n\t"
      "pushl %%esi\n\t"
      "movl 0xc(%%ebp), %%esi\n\t"
      "cmpl %%eax, %%edx\n\t"
      "movl 0x14(%%ebp), %%edx\n\t"
      "pushl %%edi\n\t"
      "jb .LFUN_0006b610_5\n\t"
      "movl 0x20(%%ebp), %%eax\n\t"
      "addl %%edx, %%eax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_0006b610_1:\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "movzwl %%cx, %%eax\n\t"
      "cmpl %%eax, %%edx\n\t"
      "movl %%edx, %%ebx\n\t"
      "jb .LFUN_0006b610_3\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_0006b610_2:\n\t"
      "pushl 0x20(%%ebp)\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "pushl $0\n\t"
      "pushl %%edx\n\t"
      "movzwl 0x3340d4, %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "movl %%esi, %%eax\n\t"
      "call *%[c6b440]\n\t"
      "movw 0x3340d8, %%cx\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "movzwl %%cx, %%eax\n\t"
      "addl $2, %%edx\n\t"
      "addl %%edx, %%esi\n\t"
      "movl 0x14(%%ebp), %%edx\n\t"
      "subl %%eax, %%ebx\n\t"
      "addl $0x14, %%esp\n\t"
      "cmpl %%eax, %%ebx\n\t"
      "leal (%%edi,%%eax,4), %%edi\n\t"
      "jae .LFUN_0006b610_2\n\t"
      ".LFUN_0006b610_3:\n\t"
      "testl %%ebx, %%ebx\n\t"
      "jbe .LFUN_0006b610_4\n\t"
      "movl 0x20(%%ebp), %%eax\n\t"
      "movzwl %%cx, %%ecx\n\t"
      "pushl %%eax\n\t"
      "subl %%ebx, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "pushl %%edx\n\t"
      "movzwl 0x3340d4, %%edx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "movl %%esi, %%eax\n\t"
      "call *%[c6b440]\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "movw 0x3340d8, %%cx\n\t"
      "leal 0x2(%%esi,%%edx,1), %%esi\n\t"
      "movl 0x14(%%ebp), %%edx\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0006b610_4:\n\t"
      "movzwl 0x3340d4, %%eax\n\t"
      "movl -0x8(%%ebp), %%edi\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "imull %%eax, %%edi\n\t"
      "leal (%%ebx,%%edi,4), %%edi\n\t"
      "movl %%edi, 0x8(%%ebp)\n\t"
      "addl 0x1c(%%ebp), %%esi\n\t"
      "movl 0x18(%%ebp), %%edi\n\t"
      "subl %%eax, %%edi\n\t"
      "cmpl %%eax, %%edi\n\t"
      "movl %%edi, 0x18(%%ebp)\n\t"
      "jae .LFUN_0006b610_1\n\t"
      ".LFUN_0006b610_5:\n\t"
      "movl 0x18(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jbe .LFUN_0006b610_8\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "movzwl %%cx, %%eax\n\t"
      "cmpl %%eax, %%edx\n\t"
      "movl %%edx, %%ebx\n\t"
      "jb .LFUN_0006b610_7\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "addl $2, %%ecx\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      ".LFUN_0006b610_6:\n\t"
      "movl 0x20(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "pushl $0\n\t"
      "pushl %%edx\n\t"
      "movl 0x18(%%ebp), %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "movl %%esi, %%eax\n\t"
      "call *%[c6b440]\n\t"
      "movw 0x3340d8, %%cx\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "movzwl %%cx, %%eax\n\t"
      "addl %%edx, %%esi\n\t"
      "movl 0x14(%%ebp), %%edx\n\t"
      "subl %%eax, %%ebx\n\t"
      "addl $0x14, %%esp\n\t"
      "cmpl %%eax, %%ebx\n\t"
      "leal (%%edi,%%eax,4), %%edi\n\t"
      "jae .LFUN_0006b610_6\n\t"
      ".LFUN_0006b610_7:\n\t"
      "testl %%ebx, %%ebx\n\t"
      "jbe .LFUN_0006b610_8\n\t"
      "movl 0x20(%%ebp), %%eax\n\t"
      "movzwl %%cx, %%ecx\n\t"
      "pushl %%eax\n\t"
      "subl %%ebx, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "pushl %%edx\n\t"
      "movl 0x18(%%ebp), %%edx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "movl %%esi, %%eax\n\t"
      "call *%[c6b440]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0006b610_8:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c6b440] "m"(b6b610_c6b440)
      : "memory");
}
#else
#error "FUN_0006b610: clang naked draft required"
#endif


/* 0x6b780 */
void FUN_0006b780(void)
{
  int eax = 0;
  int esi = 0;

  /* cmp eax, 6 -> ja 0x6b825 */
  /* relift: cmp word ptr [0x3340fc], 8 -> jne 0x6b7ab */
  /* cmp eax, 7 -> ja 0x6b825 */
  /* cmp eax, 7 -> ja 0x6b825 */
  /* relift: cmp word ptr [0x3340fc], 8 -> jne 0x6b825 */
  /* test esi, esi -> jne 0x6b838 */
  FUN_00068a30(0, (char *)0x002602d0);
  /* test esi, esi -> jne 0x6b8da */
  FUN_00068a30(0, (char *)0x002602d0);

  (void)eax;
  (void)esi;
}

/* 0x6b8e0 */
void FUN_0006b8e0(void)
{
  int eax = 0;
  int ebx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  FUN_0006b780();
  FUN_0006f910();
  debug_malloc(eax, 0, (char *)0, 0);
  FUN_00068a30(0, (char *)0x002602e8);
  TIFFGetField();
  TIFFGetField();
  FUN_0006a310();
  /* cmp edx, ebx -> jbe 0x6b9ae */
  /* test edi, edi -> jbe 0x6ba2d */
  FUN_0006eea0();
  /* test eax, eax -> jge 0x6b9e3 */
  /* test eax, eax -> jne 0x6ba27 */
  /* cmp esi, edi -> jb 0x6b9b8 */
  /* relift: cmp word ptr [0x3340f0], 1 -> jne 0x6ba39 */
  debug_free((void *)(uintptr_t)edx, (char *)0x00260264, 346);

  (void)eax;
  (void)ebx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x6ba70 */
void FUN_0006ba70(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* test eax, eax -> jne 0x6bac8 */
  FUN_00068a30(0, (char *)0x002602d0);
  /* test eax, eax -> jne 0x6bac8 */
  FUN_0006f910();
  debug_malloc(ecx, 0, (char *)0x00260264, 376);
  FUN_00068a30(0, (char *)0x002602e8);
  TIFFGetField();
  TIFFGetField();
  FUN_0006a310();
  /* cmp edx, esi -> jbe 0x6bb8d */
  /* test edi, edi -> jbe 0x6bc69 */
  FUN_0006eea0();
  /* test eax, eax -> jge 0x6bbc7 */
  /* test eax, eax -> jne 0x6bc63 */
  FUN_0006eea0();
  /* test eax, eax -> jge 0x6bbed */
  /* test eax, eax -> jne 0x6bc63 */
  FUN_0006eea0();
  /* test eax, eax -> jge 0x6bc13 */
  /* test eax, eax -> jne 0x6bc63 */
  /* cmp esi, edi -> jb 0x6bb9b */
  /* relift: cmp word ptr [0x3340f0], 1 -> jne 0x6bc75 */
  debug_free((void *)(uintptr_t)ecx, (char *)0x00260264, 412);
  FUN_0006b780();
  FUN_0006f180();
  debug_malloc(eax, 0, (char *)0, 0);
  FUN_00068a30(0, (char *)0x00260304);
  FUN_0006a310();
  FUN_00064ec0(0, 0, 0);
  TIFFGetField();
  TIFFScanlineSize();
  /* cmp ebx, eax -> jae 0x6bd79 */
  /* test eax, eax -> jbe 0x6be1e */
  /* cmp edx, eax -> jbe 0x6bd9e */
  FUN_0006f0d0();
  FUN_0006ede0();
  /* test eax, eax -> jge 0x6bdd2 */
  /* test eax, eax -> jne 0x6be1b */
  /* relift: cmp word ptr [0x3340f0], 1 -> jne 0x6be03 */
  debug_free((void *)(uintptr_t)esi, (char *)0x00260264, 459);
  FUN_0006f180();
  debug_malloc(eax, edi, (char *)0x00260264, 487);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}
