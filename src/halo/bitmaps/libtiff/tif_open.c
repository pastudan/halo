/* kb object: tif_open.obj -> bitmaps/libtiff/tif_open.c */

/* --- tif_open.obj batch drafts (2026-07-26) --- */

/* 0x6c400 */
void FUN_0006c400(void)
{
  int eax = 0;
  int ecx = 0;

  FUN_00064ec0(0, 0, 0);
  /* cmp ecx, 0xf -> ja 0x6c58b */
  FUN_00064ec0(0, 0, 0);
  /* cmp eax, 1 -> je 0x6c472 */
  /* cmp eax, 2 -> jle 0x6c467 */
  /* cmp eax, 4 -> jle 0x6c472 */
  TIFFGetField();
  /* test eax, eax -> jne 0x6c4f3 */
  /* cmp eax, 1 -> je 0x6c4cd */
  /* cmp eax, 2 -> jle 0x6c4af */
  /* cmp eax, 4 -> jg 0x6c4af */
  /* relift: relift: mov word ptr [0x3340f4], 2 */
  TIFFFileName();
  FUN_00068a30(0, (char *)0);
  /* relift: relift: mov word ptr [0x3340f4], 1 */
  TIFFFileName();
  FUN_00068a30(0, (char *)0);
  TIFFGetField();
  TIFFGetField();
  /* mem[0x003340e0] = ecx */
  /* mem[0x003340c8] = 0 */
  /* mem[0x003340c4] = 0 */
  FUN_0006c080();
  debug_free((void *)(uintptr_t)eax, (char *)0x00260264, 125);
  /* test eax, eax -> je 0x6c584 */
  debug_free((void *)(uintptr_t)eax, (char *)0x00260264, 127);
  TIFFFileName();
  FUN_00068a30(0, (char *)0);

  (void)eax;
  (void)ecx;
}

/* 0x6c5e0 */
void FUN_0006c5e0(void)
{
  int eax = 0;
  int ecx = 0;

  FUN_00068a30(0, (char *)0x00260480);
  /* relift: cmp word ptr [eax + 0x5e], 1 -> jne 0x6c611 */
  /* cmp ecx, 8 -> je 0x6c645 */
  /* cmp ecx, 0x10 -> je 0x6c63d */
  FUN_00068a30(0, (char *)0x00260438);
  /* test ecx, ecx -> je 0x6c679 */
  FUN_0006f890();
  TIFFScanlineSize();

  (void)eax;
  (void)ecx;
}

/* FUN_0006c680 (0x6c680) — XBE naked draft (batch 326). */
#if defined(__clang__)


__attribute__((naked, noinline))
void FUN_0006c680(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "pushl %%edi\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "cmpl %%ecx, %%edi\n\t"
      "jle .LFUN_0006c680_9\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "subl %%ecx, %%edi\n\t"
      "pushl %%esi\n\t"
      ".LFUN_0006c680_1:\n\t"
      "cmpl $4, %%ecx\n\t"
      "ja .LFUN_0006c680_2\n\t"
      "jmp *.LFUN_0006c680_jt(,%%ecx,4)\n\t"
      ".LFUN_0006c680_2:\n\t"
      "leal -0x4(%%ecx), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jle .LFUN_0006c680_4\n\t"
      ".LFUN_0006c680_3:\n\t"
      "movb (%%eax), %%dl\n\t"
      "addb %%dl, (%%eax,%%ecx,1)\n\t"
      "incl %%eax\n\t"
      "decl %%esi\n\t"
      "jne .LFUN_0006c680_3\n\t"
      ".LFUN_0006c680_4:\n\t"
      "movb (%%eax), %%dl\n\t"
      "addb %%dl, (%%eax,%%ecx,1)\n\t"
      "incl %%eax\n\t"
      ".LFUN_0006c680_5:\n\t"
      "movb (%%eax), %%dl\n\t"
      "addb %%dl, (%%eax,%%ecx,1)\n\t"
      "incl %%eax\n\t"
      ".LFUN_0006c680_6:\n\t"
      "movb (%%eax), %%dl\n\t"
      "addb %%dl, (%%eax,%%ecx,1)\n\t"
      "incl %%eax\n\t"
      ".LFUN_0006c680_7:\n\t"
      "movb (%%eax), %%dl\n\t"
      "addb %%dl, (%%eax,%%ecx,1)\n\t"
      "incl %%eax\n\t"
      ".LFUN_0006c680_8:\n\t"
      "subl %%ecx, %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "jg .LFUN_0006c680_1\n\t"
      "popl %%esi\n\t"
      ".LFUN_0006c680_9:\n\t"
      "popl %%edi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "movl %%edi, %%edi\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_0006c680_jt:\n\t"
      ".long .LFUN_0006c680_8\n\t"
      ".long .LFUN_0006c680_7\n\t"
      ".long .LFUN_0006c680_6\n\t"
      ".long .LFUN_0006c680_5\n\t"
      ".long .LFUN_0006c680_4\n\t"
      ".text\n\t"
      :
      :
      : "memory");
}
#else
#error "FUN_0006c680: clang naked draft required"
#endif


/* FUN_0006c6f0 (0x6c6f0) — XBE naked draft (batch 324). */
#if defined(__clang__)


__attribute__((naked, noinline))
void FUN_0006c6f0(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "cdq\n\t"
      "subl %%edx, %%eax\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "sarl $1, %%eax\n\t"
      "cmpl %%edx, %%eax\n\t"
      "jle .LFUN_0006c6f0_9\n\t"
      "pushl %%esi\n\t"
      "subl %%edx, %%eax\n\t"
      "pushl %%edi\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_0006c6f0_1:\n\t"
      "cmpl $4, %%edx\n\t"
      "ja .LFUN_0006c6f0_2\n\t"
      "jmp *.LFUN_0006c6f0_jt(,%%edx,4)\n\t"
      ".LFUN_0006c6f0_2:\n\t"
      "leal -0x4(%%edx), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jle .LFUN_0006c6f0_4\n\t"
      ".LFUN_0006c6f0_3:\n\t"
      "movw (%%ecx), %%di\n\t"
      "addw %%di, (%%ecx,%%edx,2)\n\t"
      "addl $2, %%ecx\n\t"
      "decl %%esi\n\t"
      "jne .LFUN_0006c6f0_3\n\t"
      ".LFUN_0006c6f0_4:\n\t"
      "movw (%%ecx), %%si\n\t"
      "addw %%si, (%%ecx,%%edx,2)\n\t"
      "addl $2, %%ecx\n\t"
      ".LFUN_0006c6f0_5:\n\t"
      "movw (%%ecx), %%si\n\t"
      "addw %%si, (%%ecx,%%edx,2)\n\t"
      "addl $2, %%ecx\n\t"
      ".LFUN_0006c6f0_6:\n\t"
      "movw (%%ecx), %%si\n\t"
      "addw %%si, (%%ecx,%%edx,2)\n\t"
      "addl $2, %%ecx\n\t"
      ".LFUN_0006c6f0_7:\n\t"
      "movw (%%ecx), %%si\n\t"
      "addw %%si, (%%ecx,%%edx,2)\n\t"
      "addl $2, %%ecx\n\t"
      ".LFUN_0006c6f0_8:\n\t"
      "subl %%edx, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jg .LFUN_0006c6f0_1\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      ".LFUN_0006c6f0_9:\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "movl %%edi, %%edi\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_0006c6f0_jt:\n\t"
      ".long .LFUN_0006c6f0_8\n\t"
      ".long .LFUN_0006c6f0_7\n\t"
      ".long .LFUN_0006c6f0_6\n\t"
      ".long .LFUN_0006c6f0_5\n\t"
      ".long .LFUN_0006c6f0_4\n\t"
      ".text\n\t"
      :
      :
      : "memory");
}
#else
#error "FUN_0006c6f0: clang naked draft required"
#endif


/* FUN_0006c780 (0x6c780) — XBE naked draft (batch 307). */
#if defined(__clang__)
static void (*const b6c780_c6f9d0)(void) = FUN_0006f9d0;

__attribute__((naked, noinline))
void FUN_0006c780(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edi\n\t"
      "movl 0x120(%%ecx), %%edi\n\t"
      "movl 0x14(%%edi), %%eax\n\t"
      "cmpl 0x18(%%edi), %%eax\n\t"
      "movl %%edi, -0x4(%%ebp)\n\t"
      "jle .LFUN_0006c780_1\n\t"
      "movl 0xdc(%%ecx), %%eax\n\t"
      "movl (%%ecx), %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl $0x2604a4\n\t"
      "pushl %%ecx\n\t"
      "call *%[c6f9d0]\n\t"
      "addl $0xc, %%esp\n\t"
      "movl $0x101, %%eax\n\t"
      "popl %%edi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0006c780_1:\n\t"
      "pushl %%ebx\n\t"
      "movzwl 0x6(%%edi), %%ebx\n\t"
      "movl %%eax, %%edx\n\t"
      "pushl %%esi\n\t"
      "movl 0x12c(%%ecx), %%esi\n\t"
      "movb 0x4(%%edi), %%cl\n\t"
      "sarl $3, %%edx\n\t"
      "addl %%esi, %%edx\n\t"
      "movzbl (%%edx), %%esi\n\t"
      "andl $7, %%eax\n\t"
      "testb $2, %%cl\n\t"
      "je .LFUN_0006c780_3\n\t"
      "movb %%al, %%cl\n\t"
      "shrl %%cl, %%esi\n\t"
      "movl $8, %%ecx\n\t"
      "subl %%eax, %%ecx\n\t"
      "subl %%ecx, %%ebx\n\t"
      "incl %%edx\n\t"
      "cmpl $8, %%ebx\n\t"
      "jl .LFUN_0006c780_2\n\t"
      "movzbl (%%edx), %%eax\n\t"
      "movl -0x4(%%ebp), %%edi\n\t"
      "shll %%cl, %%eax\n\t"
      "addl $8, %%ecx\n\t"
      "orl %%eax, %%esi\n\t"
      "incl %%edx\n\t"
      "subl $8, %%ebx\n\t"
      ".LFUN_0006c780_2:\n\t"
      "movzbl 0x2ec7d0(%%ebx), %%eax\n\t"
      "movzbl (%%edx), %%edx\n\t"
      "andl %%edx, %%eax\n\t"
      "jmp .LFUN_0006c780_5\n\t"
      ".LFUN_0006c780_3:\n\t"
      "movl $8, %%ecx\n\t"
      "subl %%eax, %%ecx\n\t"
      "movzbl 0x2ec7d0(%%ecx), %%eax\n\t"
      "andl %%esi, %%eax\n\t"
      "subl %%ecx, %%ebx\n\t"
      "incl %%edx\n\t"
      "cmpl $8, %%ebx\n\t"
      "jl .LFUN_0006c780_4\n\t"
      "movzbl (%%edx), %%ecx\n\t"
      "shll $8, %%eax\n\t"
      "orl %%ecx, %%eax\n\t"
      "incl %%edx\n\t"
      "subl $8, %%ebx\n\t"
      ".LFUN_0006c780_4:\n\t"
      "movzbl 0x2ec7dc(%%ebx), %%esi\n\t"
      "movzbl (%%edx), %%edx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movb $8, %%cl\n\t"
      "subb %%bl, %%cl\n\t"
      "andl %%edx, %%esi\n\t"
      "shrl %%cl, %%esi\n\t"
      "movl %%ebx, %%ecx\n\t"
      ".LFUN_0006c780_5:\n\t"
      "shll %%cl, %%eax\n\t"
      "movl 0x14(%%edi), %%ecx\n\t"
      "orl %%eax, %%esi\n\t"
      "movzwl 0x6(%%edi), %%eax\n\t"
      "addl %%ecx, %%eax\n\t"
      "movl %%eax, 0x14(%%edi)\n\t"
      "movl %%esi, %%eax\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%edi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c6f9d0] "m"(b6c780_c6f9d0)
      : "memory");
}
#else
#error "FUN_0006c780: clang naked draft required"
#endif


/* FUN_0006c860 (0x6c860) — XBE naked draft (batch 324). */
#if defined(__clang__)


__attribute__((naked, noinline))
void FUN_0006c860(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "pushl %%edi\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "cmpl %%ecx, %%edi\n\t"
      "jle .LFUN_0006c860_9\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "subl %%ecx, %%edi\n\t"
      "leal -0x1(%%eax,%%edi,1), %%eax\n\t"
      "pushl %%esi\n\t"
      ".LFUN_0006c860_1:\n\t"
      "cmpl $4, %%ecx\n\t"
      "ja .LFUN_0006c860_2\n\t"
      "jmp *.LFUN_0006c860_jt(,%%ecx,4)\n\t"
      ".LFUN_0006c860_2:\n\t"
      "leal -0x4(%%ecx), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jle .LFUN_0006c860_4\n\t"
      "jmp .LFUN_0006c860_3\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".LFUN_0006c860_3:\n\t"
      "movb (%%eax), %%dl\n\t"
      "subb %%dl, (%%eax,%%ecx,1)\n\t"
      "decl %%eax\n\t"
      "decl %%esi\n\t"
      "jne .LFUN_0006c860_3\n\t"
      ".LFUN_0006c860_4:\n\t"
      "movb (%%eax), %%dl\n\t"
      "subb %%dl, (%%eax,%%ecx,1)\n\t"
      "decl %%eax\n\t"
      ".LFUN_0006c860_5:\n\t"
      "movb (%%eax), %%dl\n\t"
      "subb %%dl, (%%eax,%%ecx,1)\n\t"
      "decl %%eax\n\t"
      ".LFUN_0006c860_6:\n\t"
      "movb (%%eax), %%dl\n\t"
      "subb %%dl, (%%eax,%%ecx,1)\n\t"
      "decl %%eax\n\t"
      ".LFUN_0006c860_7:\n\t"
      "movb (%%eax), %%dl\n\t"
      "subb %%dl, (%%eax,%%ecx,1)\n\t"
      "decl %%eax\n\t"
      ".LFUN_0006c860_8:\n\t"
      "subl %%ecx, %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "jg .LFUN_0006c860_1\n\t"
      "popl %%esi\n\t"
      ".LFUN_0006c860_9:\n\t"
      "popl %%edi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "nop\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_0006c860_jt:\n\t"
      ".long .LFUN_0006c860_8\n\t"
      ".long .LFUN_0006c860_7\n\t"
      ".long .LFUN_0006c860_6\n\t"
      ".long .LFUN_0006c860_5\n\t"
      ".long .LFUN_0006c860_4\n\t"
      ".text\n\t"
      :
      :
      : "memory");
}
#else
#error "FUN_0006c860: clang naked draft required"
#endif


/* FUN_0006c8d0 (0x6c8d0) — XBE naked draft (batch 323). */
#if defined(__clang__)


__attribute__((naked, noinline))
void FUN_0006c8d0(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "cdq\n\t"
      "subl %%edx, %%eax\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "sarl $1, %%eax\n\t"
      "cmpl %%edx, %%eax\n\t"
      "jle .LFUN_0006c8d0_9\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "subl %%edx, %%eax\n\t"
      "pushl %%esi\n\t"
      "leal -0x2(%%ecx,%%eax,2), %%ecx\n\t"
      "pushl %%edi\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".LFUN_0006c8d0_1:\n\t"
      "cmpl $4, %%edx\n\t"
      "ja .LFUN_0006c8d0_2\n\t"
      "jmp *.LFUN_0006c8d0_jt(,%%edx,4)\n\t"
      ".LFUN_0006c8d0_2:\n\t"
      "leal -0x4(%%edx), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jle .LFUN_0006c8d0_4\n\t"
      ".LFUN_0006c8d0_3:\n\t"
      "movw (%%ecx), %%di\n\t"
      "subw %%di, (%%ecx,%%edx,2)\n\t"
      "subl $2, %%ecx\n\t"
      "decl %%esi\n\t"
      "jne .LFUN_0006c8d0_3\n\t"
      ".LFUN_0006c8d0_4:\n\t"
      "movw (%%ecx), %%si\n\t"
      "subw %%si, (%%ecx,%%edx,2)\n\t"
      "subl $2, %%ecx\n\t"
      ".LFUN_0006c8d0_5:\n\t"
      "movw (%%ecx), %%si\n\t"
      "subw %%si, (%%ecx,%%edx,2)\n\t"
      "subl $2, %%ecx\n\t"
      ".LFUN_0006c8d0_6:\n\t"
      "movw (%%ecx), %%si\n\t"
      "subw %%si, (%%ecx,%%edx,2)\n\t"
      "subl $2, %%ecx\n\t"
      ".LFUN_0006c8d0_7:\n\t"
      "movw (%%ecx), %%si\n\t"
      "subw %%si, (%%ecx,%%edx,2)\n\t"
      "subl $2, %%ecx\n\t"
      ".LFUN_0006c8d0_8:\n\t"
      "subl %%edx, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jg .LFUN_0006c8d0_1\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      ".LFUN_0006c8d0_9:\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "movl %%edi, %%edi\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_0006c8d0_jt:\n\t"
      ".long .LFUN_0006c8d0_8\n\t"
      ".long .LFUN_0006c8d0_7\n\t"
      ".long .LFUN_0006c8d0_6\n\t"
      ".long .LFUN_0006c8d0_5\n\t"
      ".long .LFUN_0006c8d0_4\n\t"
      ".text\n\t"
      :
      :
      : "memory");
}
#else
#error "FUN_0006c8d0: clang naked draft required"
#endif


/* FUN_0006c960 (0x6c960) — XBE naked draft (batch 307). */
#if defined(__clang__)
static void (*const b6c960_c6fe10)(void) = TIFFFlushData1;

__attribute__((naked, noinline))
void FUN_0006c960(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $8, %%esp\n\t"
      "pushl %%ebx\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x120(%%ebx), %%edi\n\t"
      "movzwl 0x6(%%edi), %%edx\n\t"
      "movl 0x14(%%edi), %%eax\n\t"
      "movl 0x18(%%edi), %%esi\n\t"
      "leal (%%edx,%%eax,1), %%ecx\n\t"
      "cmpl %%esi, %%ecx\n\t"
      "movl %%edx, -0x8(%%ebp)\n\t"
      "jle .LFUN_0006c960_3\n\t"
      "movl %%eax, %%ecx\n\t"
      "andl $7, %%ecx\n\t"
      "movl %%ecx, -0x4(%%ebp)\n\t"
      "pushl %%ebx\n\t"
      "je .LFUN_0006c960_1\n\t"
      "movl 0x12c(%%ebx), %%esi\n\t"
      "sarl $3, %%eax\n\t"
      "movl %%eax, 0x138(%%ebx)\n\t"
      "addl %%eax, %%esi\n\t"
      "call *%[c6fe10]\n\t"
      "movl 0x12c(%%ebx), %%edx\n\t"
      "movb (%%esi), %%al\n\t"
      "movb %%al, (%%edx)\n\t"
      "jmp .LFUN_0006c960_2\n\t"
      ".LFUN_0006c960_1:\n\t"
      "call *%[c6fe10]\n\t"
      ".LFUN_0006c960_2:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movl 0x12c(%%ebx), %%esi\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "addl $4, %%esp\n\t"
      "movl %%eax, 0x14(%%edi)\n\t"
      "jmp .LFUN_0006c960_4\n\t"
      ".LFUN_0006c960_3:\n\t"
      "movl 0x12c(%%ebx), %%ecx\n\t"
      "movl %%eax, %%esi\n\t"
      "sarl $3, %%esi\n\t"
      "addl %%ecx, %%esi\n\t"
      "andl $7, %%eax\n\t"
      ".LFUN_0006c960_4:\n\t"
      "movb (%%esi), %%bl\n\t"
      "leal -0x8(%%edx,%%eax,1), %%edx\n\t"
      "movb 0x2ec7dc(%%eax), %%al\n\t"
      "andb %%bl, %%al\n\t"
      "movl 0xc(%%ebp), %%ebx\n\t"
      "movl %%edx, %%ecx\n\t"
      "sarl %%cl, %%ebx\n\t"
      "orb %%bl, %%al\n\t"
      "movb %%al, (%%esi)\n\t"
      "incl %%esi\n\t"
      "cmpl $8, %%edx\n\t"
      "jl .LFUN_0006c960_5\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "subl $8, %%edx\n\t"
      "movl %%edx, %%ecx\n\t"
      "sarl %%cl, %%eax\n\t"
      "incl %%esi\n\t"
      "movb %%al, -0x1(%%esi)\n\t"
      ".LFUN_0006c960_5:\n\t"
      "testl %%edx, %%edx\n\t"
      "je .LFUN_0006c960_6\n\t"
      "movb 0x2ec7d0(%%edx), %%al\n\t"
      "andb 0xc(%%ebp), %%al\n\t"
      "movl $8, %%ecx\n\t"
      "subl %%edx, %%ecx\n\t"
      "shlb %%cl, %%al\n\t"
      "movb %%al, (%%esi)\n\t"
      ".LFUN_0006c960_6:\n\t"
      "movzwl 0x6(%%edi), %%eax\n\t"
      "movl 0x2c(%%edi), %%edx\n\t"
      "movl 0x14(%%edi), %%ecx\n\t"
      "addl %%eax, %%ecx\n\t"
      "movl %%ecx, 0x14(%%edi)\n\t"
      "addl %%eax, %%edx\n\t"
      "movl %%edx, 0x2c(%%edi)\n\t"
      "movl %%ecx, %%edi\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "addl $7, %%edi\n\t"
      "sarl $3, %%edi\n\t"
      "movl %%edi, 0x138(%%ecx)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c6fe10] "m"(b6c960_c6fe10)
      : "memory");
}
#else
#error "FUN_0006c960: clang naked draft required"
#endif


/* FUN_0006ca50 (0x6ca50) — XBE naked draft (batch 311). */
#if defined(__clang__)


__attribute__((naked, noinline))
void FUN_0006ca50(void)
{
  __asm__ volatile(
      "leal 0x4e5c(%%esi), %%eax\n\t"
      "movl $0x138, %%edx\n\t"
      "orl $0xffffffff, %%ecx\n\t"
      "movl %%edi, %%edi\n\t"
      ".LFUN_0006ca50_1:\n\t"
      "movl %%ecx, -0x40(%%eax)\n\t"
      "movl %%ecx, -0x3c(%%eax)\n\t"
      "movl %%ecx, -0x38(%%eax)\n\t"
      "movl %%ecx, -0x34(%%eax)\n\t"
      "movl %%ecx, -0x30(%%eax)\n\t"
      "movl %%ecx, -0x2c(%%eax)\n\t"
      "movl %%ecx, -0x28(%%eax)\n\t"
      "movl %%ecx, -0x24(%%eax)\n\t"
      "movl %%ecx, -0x20(%%eax)\n\t"
      "movl %%ecx, -0x1c(%%eax)\n\t"
      "movl %%ecx, -0x18(%%eax)\n\t"
      "movl %%ecx, -0x14(%%eax)\n\t"
      "movl %%ecx, -0x10(%%eax)\n\t"
      "movl %%ecx, -0xc(%%eax)\n\t"
      "movl %%ecx, -0x8(%%eax)\n\t"
      "movl %%ecx, -0x4(%%eax)\n\t"
      "addl $-0x40, %%eax\n\t"
      "decl %%edx\n\t"
      "jne .LFUN_0006ca50_1\n\t"
      "movl $0xb, %%edx\n\t"
      "jmp .LFUN_0006ca50_2\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".LFUN_0006ca50_2:\n\t"
      "subl $4, %%eax\n\t"
      "decl %%edx\n\t"
      "movl %%ecx, (%%eax)\n\t"
      "jne .LFUN_0006ca50_2\n\t"
      "xorl %%eax, %%eax\n\t"
      "movl %%eax, 0x24(%%esi)\n\t"
      "movl %%eax, 0x28(%%esi)\n\t"
      "movl %%eax, 0x2c(%%esi)\n\t"
      "movl $0x102, 0x1c(%%esi)\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "FUN_0006ca50: clang naked draft required"
#endif


/* 0x6cac0 */
void FUN_0006cac0(void)
{
  int eax = 0;

  /* test eax, eax -> je 0x6caee */
  debug_free((void *)(uintptr_t)eax, (char *)0x002604d8, 925);

  (void)eax;
}

/* FUN_0006cb00 (0x6cb00) — XBE naked draft (batch 314). */
#if defined(__clang__)
static void (*const b6cb00_c6c780)(void) = FUN_0006c780;
static void *(*const b6cb00_memset)(void *, int, unsigned int) = csmemset;
static void (*const b6cb00_c68a30)(int param_1, const char *format, ...) = FUN_00068a30;

__attribute__((naked, noinline))
void FUN_0006cb00(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x120(%%ecx), %%esi\n\t"
      "testb $1, 0x4(%%esi)\n\t"
      "pushl %%edi\n\t"
      "movl 0x3ac4(%%esi), %%edi\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      "movl %%eax, 0xc(%%ebp)\n\t"
      "je .LFUN_0006cb00_2\n\t"
      ".LFUN_0006cb00_1:\n\t"
      "decl %%eax\n\t"
      "js .LFUN_0006cb00_3\n\t"
      "movb -0x1(%%edi), %%bl\n\t"
      "decl %%edi\n\t"
      "movb %%bl, (%%edx)\n\t"
      "leal 0x3736(%%esi), %%ebx\n\t"
      "incl %%edx\n\t"
      "cmpl %%ebx, %%edi\n\t"
      "ja .LFUN_0006cb00_1\n\t"
      "andb $0xfe, 0x4(%%esi)\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      "movl %%eax, 0xc(%%ebp)\n\t"
      ".LFUN_0006cb00_2:\n\t"
      "testl %%eax, %%eax\n\t"
      "movl (%%esi), %%edx\n\t"
      "movl 0x3ac8(%%esi), %%ebx\n\t"
      "movl %%edx, 0x10(%%ebp)\n\t"
      "jle .LFUN_0006cb00_19\n\t"
      "jmp .LFUN_0006cb00_6\n\t"
      ".LFUN_0006cb00_3:\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      "movl %%eax, 0xc(%%ebp)\n\t"
      "movl %%edi, 0x3ac4(%%esi)\n\t"
      ".LFUN_0006cb00_4:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl $1, %%eax\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0006cb00_5:\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      ".LFUN_0006cb00_6:\n\t"
      "call *%[c6c780]\n\t"
      "cmpl $0x101, %%eax\n\t"
      "je .LFUN_0006cb00_18\n\t"
      "cmpl $0x100, %%eax\n\t"
      "jne .LFUN_0006cb00_8\n\t"
      "pushl $0x2716\n\t"
      "leal 0x20(%%esi), %%eax\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "call *%[memset]\n\t"
      "movb 0x4(%%esi), %%al\n\t"
      "addl $0xc, %%esp\n\t"
      "testb $2, %%al\n\t"
      "movl $0x102, 0x1c(%%esi)\n\t"
      "movw $9, 0x6(%%esi)\n\t"
      "movl $0x1fe, 0x10(%%esi)\n\t"
      "je .LFUN_0006cb00_7\n\t"
      "movl $0x1ff, 0x10(%%esi)\n\t"
      ".LFUN_0006cb00_7:\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "call *%[c6c780]\n\t"
      "cmpl $0x101, %%eax\n\t"
      "je .LFUN_0006cb00_18\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movb %%al, (%%ecx)\n\t"
      "incl %%ecx\n\t"
      "movl %%ecx, -0x4(%%ebp)\n\t"
      "decl 0xc(%%ebp)\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl %%eax, 0x10(%%ebp)\n\t"
      "jmp .LFUN_0006cb00_17\n\t"
      ".LFUN_0006cb00_8:\n\t"
      "cmpl 0x1c(%%esi), %%eax\n\t"
      "movl %%eax, %%edx\n\t"
      "jl .LFUN_0006cb00_9\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "movb %%bl, (%%edi)\n\t"
      "incl %%edi\n\t"
      ".LFUN_0006cb00_9:\n\t"
      "cmpl $0x100, %%eax\n\t"
      "jl .LFUN_0006cb00_11\n\t"
      "nop\n\t"
      ".LFUN_0006cb00_10:\n\t"
      "movb 0x2736(%%esi,%%eax,1), %%cl\n\t"
      "movb %%cl, (%%edi)\n\t"
      "movswl 0x20(%%esi,%%eax,2), %%eax\n\t"
      "incl %%edi\n\t"
      "cmpl $0x100, %%eax\n\t"
      "jge .LFUN_0006cb00_10\n\t"
      ".LFUN_0006cb00_11:\n\t"
      "movzbl 0x2736(%%esi,%%eax,1), %%ebx\n\t"
      "movb %%bl, (%%edi)\n\t"
      "incl %%edi\n\t"
      ".LFUN_0006cb00_12:\n\t"
      "decl 0xc(%%ebp)\n\t"
      "js .LFUN_0006cb00_13\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movb -0x1(%%edi), %%cl\n\t"
      "decl %%edi\n\t"
      "movb %%cl, (%%eax)\n\t"
      "incl %%eax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "leal 0x3736(%%esi), %%eax\n\t"
      "cmpl %%eax, %%edi\n\t"
      "ja .LFUN_0006cb00_12\n\t"
      "jmp .LFUN_0006cb00_14\n\t"
      ".LFUN_0006cb00_13:\n\t"
      "orb $1, 0x4(%%esi)\n\t"
      ".LFUN_0006cb00_14:\n\t"
      "movl 0x1c(%%esi), %%eax\n\t"
      "cmpl $0xfff, %%eax\n\t"
      "jge .LFUN_0006cb00_16\n\t"
      "movw 0x10(%%ebp), %%cx\n\t"
      "movw %%cx, 0x20(%%esi,%%eax,2)\n\t"
      "movb %%bl, 0x2736(%%esi,%%eax,1)\n\t"
      "movl 0x1c(%%esi), %%eax\n\t"
      "movl 0x10(%%esi), %%ecx\n\t"
      "incl %%eax\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "movl %%eax, 0x1c(%%esi)\n\t"
      "jle .LFUN_0006cb00_16\n\t"
      "incw 0x6(%%esi)\n\t"
      "movl $0xc, %%eax\n\t"
      "cmpw %%ax, 0x6(%%esi)\n\t"
      "jbe .LFUN_0006cb00_15\n\t"
      "movw %%ax, 0x6(%%esi)\n\t"
      ".LFUN_0006cb00_15:\n\t"
      "movb 0x6(%%esi), %%cl\n\t"
      "movl $1, %%eax\n\t"
      "shll %%cl, %%eax\n\t"
      "movb 0x4(%%esi), %%cl\n\t"
      "addl $-2, %%eax\n\t"
      "testb $2, %%cl\n\t"
      "movl %%eax, 0x10(%%esi)\n\t"
      "je .LFUN_0006cb00_16\n\t"
      "incl %%eax\n\t"
      "movl %%eax, 0x10(%%esi)\n\t"
      ".LFUN_0006cb00_16:\n\t"
      "movl %%edx, 0x10(%%ebp)\n\t"
      ".LFUN_0006cb00_17:\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jg .LFUN_0006cb00_5\n\t"
      ".LFUN_0006cb00_18:\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      ".LFUN_0006cb00_19:\n\t"
      "testl %%eax, %%eax\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "movl %%edi, 0x3ac4(%%esi)\n\t"
      "movl %%edx, (%%esi)\n\t"
      "movl %%ebx, 0x3ac8(%%esi)\n\t"
      "jle .LFUN_0006cb00_4\n\t"
      "pushl %%eax\n\t"
      "movl 0xd4(%%ecx), %%eax\n\t"
      "movl (%%ecx), %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl $0x260504\n\t"
      "pushl %%ecx\n\t"
      "call *%[c68a30]\n\t"
      "addl $0x10, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "xorl %%eax, %%eax\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c6c780] "m"(b6cb00_c6c780), [memset] "m"(b6cb00_memset), [c68a30] "m"(b6cb00_c68a30)
      : "memory");
}
#else
#error "FUN_0006cb00: clang naked draft required"
#endif


/* 0x6ccf0 */
void FUN_0006ccf0(void)
{
  int eax = 0;

  FUN_0006cb00();
  /* test eax, eax -> je 0x6cd2f */

  (void)eax;
}

/* 0x6cd40 */
void FUN_0006cd40(void)
{
  int eax = 0;
  int edi = 0;

  FUN_0006cb00();
  /* test eax, eax -> jne 0x6cd6d */
  /* test edi, edi -> jle 0x6cd8e */
  /* test edi, edi -> jg 0x6cd75 */

  (void)eax;
  (void)edi;
}

/* 0x6cda0 */
void FUN_0006cda0(void)
{
  int eax = 0;

  /* cmp eax, -1 -> je 0x6cdc5 */
  FUN_0006c960();
  FUN_0006c960();

  (void)eax;
}

/* FUN_0006cde0 (0x6cde0) — XBE naked draft (batch 319). */
#if defined(__clang__)
static void (*const b6cde0_c6ca50)(void) = FUN_0006ca50;
static void (*const b6cde0_c6c960)(void) = FUN_0006c960;

__attribute__((naked, noinline))
void FUN_0006cde0(void)
{
  __asm__ volatile(
      "pushl %%esi\n\t"
      "movl 0x120(%%edi), %%esi\n\t"
      "movl 0x28(%%esi), %%eax\n\t"
      "cmpl $0x7fffff, %%eax\n\t"
      "leal 0x2710(%%eax), %%ecx\n\t"
      "movl %%ecx, 0x20(%%esi)\n\t"
      "jle .LFUN_0006cde0_2\n\t"
      "movl 0x2c(%%esi), %%ecx\n\t"
      "sarl $8, %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "jne .LFUN_0006cde0_1\n\t"
      "movl $0x7fffffff, %%eax\n\t"
      "jmp .LFUN_0006cde0_3\n\t"
      ".LFUN_0006cde0_1:\n\t"
      "cdq\n\t"
      "idivl %%ecx\n\t"
      "jmp .LFUN_0006cde0_3\n\t"
      ".LFUN_0006cde0_2:\n\t"
      "shll $8, %%eax\n\t"
      "cdq\n\t"
      "idivl 0x2c(%%esi)\n\t"
      ".LFUN_0006cde0_3:\n\t"
      "cmpl 0x24(%%esi), %%eax\n\t"
      "jg .LFUN_0006cde0_4\n\t"
      "call *%[c6ca50]\n\t"
      "pushl $0x100\n\t"
      "pushl %%edi\n\t"
      "call *%[c6c960]\n\t"
      "movb 0x4(%%esi), %%al\n\t"
      "addl $8, %%esp\n\t"
      "testb $2, %%al\n\t"
      "movw $9, 0x6(%%esi)\n\t"
      "movl $0x1ff, 0x10(%%esi)\n\t"
      "je .LFUN_0006cde0_5\n\t"
      "movl $0x200, 0x10(%%esi)\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      ".LFUN_0006cde0_4:\n\t"
      "movl %%eax, 0x24(%%esi)\n\t"
      ".LFUN_0006cde0_5:\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      :
      : [c6ca50] "m"(b6cde0_c6ca50), [c6c960] "m"(b6cde0_c6c960)
      : "memory");
}
#else
#error "FUN_0006cde0: clang naked draft required"
#endif


/* 0x6ce60 */
void FUN_0006ce60(void)
{
  int eax = 0;
  int ebx = 0;
  int esi = 0;

  /* cmp esi, ebx -> jne 0x6cefb */
  debug_malloc(30068, ebx, (char *)0x002604d8, 308);
  FUN_00068a30(0x00260564, (char *)0x00260574);
  FUN_0006c5e0();
  /* test eax, eax -> je 0x6cead */
  /* relift: cmp dword ptr [esi + 0xc], ebx -> je 0x6ceff */
  /* relift: cmp byte ptr [eax], (char)ebx -> jne 0x6cf7c */
  /* relift: test byte ptr [eax + 1], 1 -> je 0x6cf7c */
  /* relift: test byte ptr [esi + 4], 2 -> jne 0x6cf76 */
  FUN_0006f9d0();

  (void)eax;
  (void)ebx;
  (void)esi;
}

/* FUN_0006cfa0 (0x6cfa0) — XBE naked draft (batch 301). */
#if defined(__clang__)
static void (*const b6cfa0_c6c960)(void) = FUN_0006c960;
static void (*const b6cfa0_c6ca50)(void) = FUN_0006ca50;
static void (*const b6cfa0_c6cde0)(void) = FUN_0006cde0;

__attribute__((naked, noinline))
void FUN_0006cfa0(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xc, %%esp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%esi\n\t"
      "movl 0x120(%%eax), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LFUN_0006cfa0_1\n\t"
      "xorl %%eax, %%eax\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0006cfa0_1:\n\t"
      "movl (%%esi), %%ecx\n\t"
      "cmpl $-1, %%ecx\n\t"
      "pushl %%edi\n\t"
      "movl 0x10(%%ebp), %%edi\n\t"
      "movl %%ecx, -0x4(%%ebp)\n\t"
      "jne .LFUN_0006cfa0_2\n\t"
      "testl %%edi, %%edi\n\t"
      "jle .LFUN_0006cfa0_12\n\t"
      "pushl $0x100\n\t"
      "pushl %%eax\n\t"
      "call *%[c6c960]\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "movzbl (%%eax), %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "incl %%eax\n\t"
      "movl %%eax, 0xc(%%ebp)\n\t"
      "movl 0x28(%%esi), %%eax\n\t"
      "decl %%edi\n\t"
      "incl %%eax\n\t"
      "movl %%ecx, -0x4(%%ebp)\n\t"
      "movl %%eax, 0x28(%%esi)\n\t"
      ".LFUN_0006cfa0_2:\n\t"
      "testl %%edi, %%edi\n\t"
      "jle .LFUN_0006cfa0_12\n\t"
      "pushl %%ebx\n\t"
      "movl %%edi, -0x8(%%ebp)\n\t"
      ".LFUN_0006cfa0_3:\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "movzbl (%%eax), %%edi\n\t"
      "movl 0x28(%%esi), %%ebx\n\t"
      "incl %%eax\n\t"
      "incl %%ebx\n\t"
      "movl %%ebx, 0x28(%%esi)\n\t"
      "movl %%edi, %%ebx\n\t"
      "movl %%edi, -0xc(%%ebp)\n\t"
      "shll $4, %%edi\n\t"
      "xorl %%ecx, %%edi\n\t"
      "movl 0x30(%%esi,%%edi,4), %%edx\n\t"
      "movl %%eax, 0xc(%%ebp)\n\t"
      "shll $0xc, %%ebx\n\t"
      "leal 0x30(%%esi,%%edi,4), %%eax\n\t"
      "addl %%ecx, %%ebx\n\t"
      "cmpl %%ebx, %%edx\n\t"
      "jne .LFUN_0006cfa0_4\n\t"
      "movswl 0x4e5c(%%esi,%%edi,2), %%edx\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      "jmp .LFUN_0006cfa0_11\n\t"
      ".LFUN_0006cfa0_4:\n\t"
      "testl %%edx, %%edx\n\t"
      "jl .LFUN_0006cfa0_7\n\t"
      "movl $0x138b, %%ecx\n\t"
      "subl %%edi, %%ecx\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .LFUN_0006cfa0_5\n\t"
      "movl $1, %%ecx\n\t"
      ".LFUN_0006cfa0_5:\n\t"
      "leal (,%%ecx,4), %%edx\n\t"
      "subl %%ecx, %%edi\n\t"
      "subl %%edx, %%eax\n\t"
      "testl %%edi, %%edi\n\t"
      "jge .LFUN_0006cfa0_6\n\t"
      "addl $0x138b, %%edi\n\t"
      "addl $0x4e2c, %%eax\n\t"
      ".LFUN_0006cfa0_6:\n\t"
      "movl (%%eax), %%edx\n\t"
      "cmpl %%ebx, %%edx\n\t"
      "je .LFUN_0006cfa0_8\n\t"
      "testl %%edx, %%edx\n\t"
      "jge .LFUN_0006cfa0_5\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      ".LFUN_0006cfa0_7:\n\t"
      "pushl %%ecx\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c6c960]\n\t"
      "movw 0x1c(%%esi), %%ax\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "movw %%ax, 0x4e5c(%%esi,%%edi,2)\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      "movl 0x1c(%%esi), %%edx\n\t"
      "addl $8, %%esp\n\t"
      "incl %%edx\n\t"
      "movl %%edx, 0x1c(%%esi)\n\t"
      "movl %%ebx, 0x30(%%esi,%%edi,4)\n\t"
      "movl 0x1c(%%esi), %%eax\n\t"
      "cmpl $0xffe, %%eax\n\t"
      "jne .LFUN_0006cfa0_9\n\t"
      "call *%[c6ca50]\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "pushl $0x100\n\t"
      "pushl %%ecx\n\t"
      "call *%[c6c960]\n\t"
      "movb 0x4(%%esi), %%al\n\t"
      "addl $8, %%esp\n\t"
      "testb $2, %%al\n\t"
      "movw $9, 0x6(%%esi)\n\t"
      "movl $0x1ff, 0x10(%%esi)\n\t"
      "je .LFUN_0006cfa0_11\n\t"
      "movl $0x200, 0x10(%%esi)\n\t"
      "jmp .LFUN_0006cfa0_11\n\t"
      ".LFUN_0006cfa0_8:\n\t"
      "movswl 0x4e5c(%%esi,%%edi,2), %%eax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "jmp .LFUN_0006cfa0_11\n\t"
      ".LFUN_0006cfa0_9:\n\t"
      "cmpl 0x10(%%esi), %%eax\n\t"
      "jle .LFUN_0006cfa0_10\n\t"
      "incw 0x6(%%esi)\n\t"
      "movw 0x6(%%esi), %%cx\n\t"
      "movl $1, %%eax\n\t"
      "shll %%cl, %%eax\n\t"
      "movb 0x4(%%esi), %%cl\n\t"
      "decl %%eax\n\t"
      "testb $2, %%cl\n\t"
      "movl %%eax, 0x10(%%esi)\n\t"
      "je .LFUN_0006cfa0_11\n\t"
      "incl %%eax\n\t"
      "movl %%eax, 0x10(%%esi)\n\t"
      "jmp .LFUN_0006cfa0_11\n\t"
      ".LFUN_0006cfa0_10:\n\t"
      "movl 0x28(%%esi), %%edx\n\t"
      "cmpl 0x20(%%esi), %%edx\n\t"
      "jl .LFUN_0006cfa0_11\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "call *%[c6cde0]\n\t"
      ".LFUN_0006cfa0_11:\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "decl %%eax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "jne .LFUN_0006cfa0_3\n\t"
      "popl %%ebx\n\t"
      ".LFUN_0006cfa0_12:\n\t"
      "popl %%edi\n\t"
      "movl %%ecx, (%%esi)\n\t"
      "movl $1, %%eax\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c6c960] "m"(b6cfa0_c6c960), [c6ca50] "m"(b6cfa0_c6ca50), [c6cde0] "m"(b6cfa0_c6cde0)
      : "memory");
}
#else
#error "FUN_0006cfa0: clang naked draft required"
#endif


/* 0x6d140 */
void FUN_0006d140(void)
{
  FUN_0006cfa0();
}

/* FUN_0006d180 (0x6d180) — XBE naked draft (batch 330). */
#if defined(__clang__)
static void (*const b6d180_c6cfa0)(void) = FUN_0006cfa0;

__attribute__((naked, noinline))
void FUN_0006d180(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%ebx\n\t"
      "movl 0xc(%%ebp), %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x120(%%eax), %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x10(%%ebp), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "jle .LFUN_0006d180_2\n\t"
      "movzwl 0xa(%%esi), %%eax\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".LFUN_0006d180_1:\n\t"
      "movzwl 0x8(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "call *0xc(%%esi)\n\t"
      "movzwl 0xa(%%esi), %%eax\n\t"
      "subl %%eax, %%edi\n\t"
      "addl $0xc, %%esp\n\t"
      "addl %%eax, %%ebx\n\t"
      "testl %%edi, %%edi\n\t"
      "jg .LFUN_0006d180_1\n\t"
      "movl 0x10(%%ebp), %%edi\n\t"
      ".LFUN_0006d180_2:\n\t"
      "movl 0x14(%%ebp), %%edx\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c6cfa0]\n\t"
      "addl $0x10, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c6cfa0] "m"(b6d180_c6cfa0)
      : "memory");
}
#else
#error "FUN_0006d180: clang naked draft required"
#endif


/* 0x6d1e0 */
void FUN_0006d1e0(void)
{
  int eax = 0;
  int esi = 0;

  /* test esi, esi -> jne 0x6d279 */
  debug_malloc(30068, esi, (char *)0x002604d8, 619);
  FUN_00068a30(0x00260594, (char *)0x00260574);
  FUN_0006c5e0();
  /* test eax, eax -> je 0x6d22a */
  /* test eax, eax -> je 0x6d279 */
  FUN_0006ca50();

  (void)eax;
  (void)esi;
}

/* 0x6d2d0 */
void FUN_0006d2d0(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* FUN_0006d340 (0x6d340) — XBE naked draft (batch 325). */
#if defined(__clang__)
static void * (*const b6d340_c8e0b0)(void *destination, void *source, size_t size) = csmemcpy;
static void (*const b6d340_c68a30)(int param_1, const char *format, ...) = FUN_00068a30;

__attribute__((naked, noinline))
void FUN_0006d340(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xc, %%esp\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "jle .LFUN_0006d340_1\n\t"
      "movl %%ecx, %%esi\n\t"
      "shrl $2, %%ecx\n\t"
      "orl $0xffffffff, %%eax\n\t"
      "movl %%edx, %%edi\n\t"
      "rep stosl\n\t"
      "movl %%esi, %%ecx\n\t"
      "andl $3, %%ecx\n\t"
      "rep stosb\n\t"
      ".LFUN_0006d340_1:\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "movl 0x124(%%ecx), %%esi\n\t"
      "movl 0x134(%%ecx), %%edi\n\t"
      "movl 0x138(%%ecx), %%ebx\n\t"
      "movl %%esi, -0x8(%%ebp)\n\t"
      "movl %%edx, 0xc(%%ebp)\n\t"
      "jle .LFUN_0006d340_14\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_0006d340_2:\n\t"
      "movzbl (%%edi), %%eax\n\t"
      "incl %%edi\n\t"
      "decl %%ebx\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_0006d340_15\n\t"
      "cmpl $0x40, %%eax\n\t"
      "je .LFUN_0006d340_11\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "movl 0x1c(%%ecx), %%edx\n\t"
      "movl %%edx, -0xc(%%ebp)\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "xorl %%esi, %%esi\n\t"
      ".LFUN_0006d340_3:\n\t"
      "movl %%eax, %%ecx\n\t"
      "sarl $6, %%ecx\n\t"
      "andl $3, %%ecx\n\t"
      "andl $0x3f, %%eax\n\t"
      "jle .LFUN_0006d340_10\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      ".LFUN_0006d340_4:\n\t"
      "movl %%esi, %%eax\n\t"
      "andl $3, %%eax\n\t"
      "incl %%esi\n\t"
      "cmpl $3, %%eax\n\t"
      "ja .LFUN_0006d340_9\n\t"
      "jmp *.LFUN_0006d340_jt(,%%eax,4)\n\t"
      ".LFUN_0006d340_5:\n\t"
      "movb %%cl, %%al\n\t"
      "shlb $6, %%al\n\t"
      "movb %%al, (%%edx)\n\t"
      "jmp .LFUN_0006d340_9\n\t"
      ".LFUN_0006d340_6:\n\t"
      "movb %%cl, %%al\n\t"
      "shlb $4, %%al\n\t"
      "orb %%al, (%%edx)\n\t"
      "jmp .LFUN_0006d340_9\n\t"
      ".LFUN_0006d340_7:\n\t"
      "movb %%cl, %%al\n\t"
      "shlb $2, %%al\n\t"
      "orb %%al, (%%edx)\n\t"
      "jmp .LFUN_0006d340_9\n\t"
      ".LFUN_0006d340_8:\n\t"
      "orb %%cl, (%%edx)\n\t"
      "incl %%edx\n\t"
      ".LFUN_0006d340_9:\n\t"
      "decl -0x4(%%ebp)\n\t"
      "jne .LFUN_0006d340_4\n\t"
      ".LFUN_0006d340_10:\n\t"
      "cmpl -0xc(%%ebp), %%esi\n\t"
      "jge .LFUN_0006d340_12\n\t"
      "testl %%ebx, %%ebx\n\t"
      "je .LFUN_0006d340_16\n\t"
      "movzbl (%%edi), %%eax\n\t"
      "incl %%edi\n\t"
      "decl %%ebx\n\t"
      "jmp .LFUN_0006d340_3\n\t"
      ".LFUN_0006d340_11:\n\t"
      "movzbl 0x2(%%edi), %%esi\n\t"
      "movzbl 0x3(%%edi), %%ecx\n\t"
      "shll $8, %%esi\n\t"
      "addl %%ecx, %%esi\n\t"
      "leal 0x4(%%esi), %%edx\n\t"
      "cmpl %%edx, %%ebx\n\t"
      "jl .LFUN_0006d340_16\n\t"
      "movzbl (%%edi), %%ecx\n\t"
      "movzbl 0x1(%%edi), %%edx\n\t"
      "pushl %%esi\n\t"
      "leal 0x4(%%edi), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "shll $8, %%ecx\n\t"
      "addl %%ecx, %%eax\n\t"
      "addl %%eax, %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c8e0b0]\n\t"
      "movl $0xfffffffc, %%ecx\n\t"
      "subl %%esi, %%ecx\n\t"
      "addl $0xc, %%esp\n\t"
      "leal 0x4(%%edi,%%esi,1), %%edi\n\t"
      "addl %%ecx, %%ebx\n\t"
      ".LFUN_0006d340_12:\n\t"
      "movl -0x8(%%ebp), %%esi\n\t"
      ".LFUN_0006d340_13:\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "subl %%esi, %%eax\n\t"
      "addl %%esi, %%edx\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%eax, 0x10(%%ebp)\n\t"
      "movl %%edx, 0xc(%%ebp)\n\t"
      "jg .LFUN_0006d340_2\n\t"
      ".LFUN_0006d340_14:\n\t"
      "movl %%edi, 0x134(%%ecx)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebx, 0x138(%%ecx)\n\t"
      "movl $1, %%eax\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0006d340_15:\n\t"
      "cmpl %%esi, %%ebx\n\t"
      "jl .LFUN_0006d340_17\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%edx\n\t"
      "call *%[c8e0b0]\n\t"
      "addl $0xc, %%esp\n\t"
      "addl %%esi, %%edi\n\t"
      "subl %%esi, %%ebx\n\t"
      "jmp .LFUN_0006d340_13\n\t"
      ".LFUN_0006d340_16:\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      ".LFUN_0006d340_17:\n\t"
      "movl 0xd4(%%ecx), %%eax\n\t"
      "movl (%%ecx), %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl $0x2605a4\n\t"
      "pushl %%ecx\n\t"
      "call *%[c68a30]\n\t"
      "addl $0xc, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "xorl %%eax, %%eax\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "movl %%edi, %%edi\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_0006d340_jt:\n\t"
      ".long .LFUN_0006d340_5\n\t"
      ".long .LFUN_0006d340_6\n\t"
      ".long .LFUN_0006d340_7\n\t"
      ".long .LFUN_0006d340_8\n\t"
      ".text\n\t"
      :
      : [c8e0b0] "m"(b6d340_c8e0b0), [c68a30] "m"(b6d340_c68a30)
      : "memory");
}
#else
#error "FUN_0006d340: clang naked draft required"
#endif


/* 0x6d4d0 */
void FUN_0006d4d0(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* FUN_0006d500 (0x6d500) — XBE naked draft (batch 327). */
#if defined(__clang__)


__attribute__((naked, noinline))
void FUN_0006d500(void)
{
  __asm__ volatile(
      "cmpl $0x4d4d, %%edx\n\t"
      "movb $1, 0x8(%%eax)\n\t"
      "movl $0x2ec8f8, 0xd0(%%eax)\n\t"
      "jne .LFUN_0006d500_1\n\t"
      "testl %%ecx, %%ecx\n\t"
      "movl $0x2ec92c, 0xcc(%%eax)\n\t"
      "jne .LFUN_0006d500_2\n\t"
      "orb $0x10, 0xa(%%eax)\n\t"
      "ret\n\t"
      ".LFUN_0006d500_1:\n\t"
      "testl %%ecx, %%ecx\n\t"
      "movl $0x334100, 0xcc(%%eax)\n\t"
      "je .LFUN_0006d500_2\n\t"
      "orb $0x10, 0xa(%%eax)\n\t"
      ".LFUN_0006d500_2:\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "FUN_0006d500: clang naked draft required"
#endif


/* TIFFFdOpen (0x6d590) — XBE naked draft (batch 323). */
#if defined(__clang__)
static int (*const b6d590_c8df60)(const char *s1) = csstrlen;
static void * (*const b6d590_c8ee60)(uint32_t size, bool zero, const char *file, int line) = debug_malloc;
static void (*const b6d590_c68a30)(int param_1, const char *format, ...) = FUN_00068a30;
static int (*const b6d590_c1e0218)(int fd) = __close;
static void *(*const b6d590_memset)(void *, int, unsigned int) = csmemset;
static char * (*const b6d590_c8dff0)(char *destination, const char *source) = csstrcpy;
static void (*const b6d590_c1e209e)(void) = __read;
static void (*const b6d590_c1df419)(void) = __write;
static void (*const b6d590_c6d500)(void) = FUN_0006d500;
static void (*const b6d590_c66190)(void) = FUN_00066190;
static void (*const b6d590_c6f1b0)(void) = FUN_0006f1b0;
static void (*const b6d590_c6f1d0)(void) = FUN_0006f1d0;
static void (*const b6d590_c66e70)(void) = FUN_00066e70;
static void (*const b6d590_c64ee0)(int file) = FUN_00064ee0;

__attribute__((naked, noinline))
void TIFFFdOpen(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "movb (%%ecx), %%al\n\t"
      "cmpb $0x61, %%al\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "je .LTIFFFdOpen_2\n\t"
      "cmpb $0x72, %%al\n\t"
      "je .LTIFFFdOpen_1\n\t"
      "cmpb $0x77, %%al\n\t"
      "je .LTIFFFdOpen_2\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x2605d0\n\t"
      "jmp .LTIFFFdOpen_4\n\t"
      ".LTIFFFdOpen_1:\n\t"
      "movb 0x1(%%ecx), %%al\n\t"
      "xorl %%edi, %%edi\n\t"
      "cmpb $0x2b, %%al\n\t"
      "jne .LTIFFFdOpen_3\n\t"
      "movl $2, %%edi\n\t"
      "jmp .LTIFFFdOpen_3\n\t"
      ".LTIFFFdOpen_2:\n\t"
      "cmpb $0x77, %%al\n\t"
      "movl $0x102, %%edi\n\t"
      "jne .LTIFFFdOpen_3\n\t"
      "movl $0x302, %%edi\n\t"
      ".LTIFFFdOpen_3:\n\t"
      "movl 0xc(%%ebp), %%ebx\n\t"
      "pushl $0xab\n\t"
      "pushl $0x2606b0\n\t"
      "pushl $0\n\t"
      "pushl %%ebx\n\t"
      "call *%[c8df60]\n\t"
      "addl $0x13d, %%eax\n\t"
      "addl $4, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[c8ee60]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $0x10, %%esp\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LTIFFFdOpen_5\n\t"
      "pushl %%ebx\n\t"
      "pushl $0x26068c\n\t"
      ".LTIFFFdOpen_4:\n\t"
      "pushl $0x2ec96c\n\t"
      "call *%[c68a30]\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[c1e0218]\n\t"
      "addl $4, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "xorl %%eax, %%eax\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LTIFFFdOpen_5:\n\t"
      "pushl $0x13c\n\t"
      "pushl $0\n\t"
      "pushl %%esi\n\t"
      "call *%[memset]\n\t"
      "leal 0x13c(%%esi), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "movl %%eax, (%%esi)\n\t"
      "call *%[c8dff0]\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "andl $0xfffffcff, %%edi\n\t"
      "movw %%di, 0x6(%%esi)\n\t"
      "pushl $8\n\t"
      "orl $0xffffffff, %%eax\n\t"
      "leal 0xc4(%%esi), %%edi\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "movw %%bx, 0x4(%%esi)\n\t"
      "movl %%eax, 0xd8(%%esi)\n\t"
      "movl $0, 0xe0(%%esi)\n\t"
      "movl %%eax, 0xdc(%%esi)\n\t"
      "movl %%eax, 0xd4(%%esi)\n\t"
      "call *%[c1e209e]\n\t"
      "addl $0x20, %%esp\n\t"
      "cmpl $8, %%eax\n\t"
      "je .LTIFFFdOpen_9\n\t"
      "cmpw $0, 0x6(%%esi)\n\t"
      "jne .LTIFFFdOpen_6\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "pushl $0x260674\n\t"
      "pushl %%ecx\n\t"
      "call *%[c68a30]\n\t"
      "addl $8, %%esp\n\t"
      "jmp .LTIFFFdOpen_15\n\t"
      ".LTIFFFdOpen_6:\n\t"
      "pushl $8\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "movw $0x4949, (%%edi)\n\t"
      "movw $0x2a, 0xc6(%%esi)\n\t"
      "movl $0, 0xc8(%%esi)\n\t"
      "call *%[c1df419]\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl $8, %%eax\n\t"
      "je .LTIFFFdOpen_7\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "pushl $0x25fe8c\n\t"
      "pushl %%edx\n\t"
      "call *%[c68a30]\n\t"
      "addl $8, %%esp\n\t"
      "jmp .LTIFFFdOpen_15\n\t"
      ".LTIFFFdOpen_7:\n\t"
      "movzwl (%%edi), %%edx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movl %%esi, %%eax\n\t"
      "call *%[c6d500]\n\t"
      "pushl %%esi\n\t"
      "call *%[c66190]\n\t"
      "addl $4, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LTIFFFdOpen_15\n\t"
      "movl $0, 0xc(%%esi)\n\t"
      ".LTIFFFdOpen_8:\n\t"
      "popl %%edi\n\t"
      "movl %%esi, %%eax\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LTIFFFdOpen_9:\n\t"
      "movw (%%edi), %%di\n\t"
      "cmpw $0x4d4d, %%di\n\t"
      "je .LTIFFFdOpen_10\n\t"
      "cmpw $0x4949, %%di\n\t"
      "je .LTIFFFdOpen_10\n\t"
      "movzwl %%di, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%eax\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "pushl $0x260648\n\t"
      "pushl %%eax\n\t"
      "call *%[c68a30]\n\t"
      "addl $0x10, %%esp\n\t"
      "jmp .LTIFFFdOpen_15\n\t"
      ".LTIFFFdOpen_10:\n\t"
      "movzwl %%di, %%edx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movl %%esi, %%eax\n\t"
      "call *%[c6d500]\n\t"
      "testb $0x10, 0xa(%%esi)\n\t"
      "je .LTIFFFdOpen_11\n\t"
      "leal 0xc6(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c6f1b0]\n\t"
      "leal 0xc8(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c6f1d0]\n\t"
      "addl $8, %%esp\n\t"
      ".LTIFFFdOpen_11:\n\t"
      "movw 0xc6(%%esi), %%ax\n\t"
      "cmpw $0x2a, %%ax\n\t"
      "je .LTIFFFdOpen_12\n\t"
      "movzwl %%ax, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%eax\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "pushl $0x260618\n\t"
      "pushl %%eax\n\t"
      "call *%[c68a30]\n\t"
      "addl $0x10, %%esp\n\t"
      "jmp .LTIFFFdOpen_15\n\t"
      ".LTIFFFdOpen_12:\n\t"
      "orb $0x40, 0xa(%%esi)\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "movw 0xa(%%esi), %%cx\n\t"
      "xorl %%eax, %%eax\n\t"
      "movl %%eax, 0x12c(%%esi)\n\t"
      "movl %%eax, 0x134(%%esi)\n\t"
      "movl %%eax, 0x130(%%esi)\n\t"
      "movb (%%edx), %%al\n\t"
      "cmpb $0x61, %%al\n\t"
      "je .LTIFFFdOpen_13\n\t"
      "cmpb $0x72, %%al\n\t"
      "jne .LTIFFFdOpen_15\n\t"
      "movl 0xc8(%%esi), %%eax\n\t"
      "pushl %%esi\n\t"
      "movl %%eax, 0x10(%%esi)\n\t"
      "call *%[c66e70]\n\t"
      "addl $4, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LTIFFFdOpen_15\n\t"
      "orb $4, 0xa(%%esi)\n\t"
      "popl %%edi\n\t"
      "movl $0xffffffff, 0x138(%%esi)\n\t"
      "movl %%esi, %%eax\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LTIFFFdOpen_13:\n\t"
      "testb $0x10, %%cl\n\t"
      "je .LTIFFFdOpen_14\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "pushl $0x2605e0\n\t"
      "pushl %%ecx\n\t"
      "call *%[c68a30]\n\t"
      "addl $8, %%esp\n\t"
      "jmp .LTIFFFdOpen_15\n\t"
      ".LTIFFFdOpen_14:\n\t"
      "pushl %%esi\n\t"
      "call *%[c66190]\n\t"
      "addl $4, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LTIFFFdOpen_8\n\t"
      ".LTIFFFdOpen_15:\n\t"
      "pushl %%esi\n\t"
      "movw $0, 0x6(%%esi)\n\t"
      "call *%[c64ee0]\n\t"
      "addl $4, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "xorl %%eax, %%eax\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c8df60] "m"(b6d590_c8df60), [c8ee60] "m"(b6d590_c8ee60), [c68a30] "m"(b6d590_c68a30), [c1e0218] "m"(b6d590_c1e0218), [memset] "m"(b6d590_memset), [c8dff0] "m"(b6d590_c8dff0), [c1e209e] "m"(b6d590_c1e209e), [c1df419] "m"(b6d590_c1df419), [c6d500] "m"(b6d590_c6d500), [c66190] "m"(b6d590_c66190), [c6f1b0] "m"(b6d590_c6f1b0), [c6f1d0] "m"(b6d590_c6f1d0), [c66e70] "m"(b6d590_c66e70), [c64ee0] "m"(b6d590_c64ee0)
      : "memory");
}
#else
#error "TIFFFdOpen: clang naked draft required"
#endif


/* 0x6d820 */
void TIFFScanlineSize(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x6d850 */
void TIFFFileName(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x6d860 */
void TIFFFileno(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x6d870 */
void TIFFGetMode(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x6d880 */
void TIFFIsTiled(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x6d8a0 */
void TIFFCurrentRow(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x6d8b0 */
void TIFFCurrentDirectory(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x6d8c0 */
void TIFFCurrentStrip(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x6d8d0 */
void TIFFCurrentTile(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x6d8e0 */
int FUN_0006d8e0(const char *path, const char *mode)
{
  int eax = 0;
  int ecx = 0;

  /* cmp (char)ecx, 0x61 -> je 0x6d954 */
  /* cmp (char)ecx, 0x72 -> je 0x6d910 */
  /* cmp (char)ecx, 0x77 -> je 0x6d954 */
  FUN_00068a30(0x002ec960, (char *)0x002605d0);
  /* cmp (char)ecx, 0x2b -> jne 0x6d91f */
  __open();
  /* test eax, eax -> jge 0x6d965 */
  FUN_00068a30(0x002ec960, (char *)0x002606dc);
  TIFFFdOpen();
  return 0;

  (void)eax;
  (void)ecx;
}

/* FUN_0006d980 (0x6d980) — XBE naked draft (batch 336). */
#if defined(__clang__)
static void (*const b6d980_c6f890)(void) = FUN_0006f890;
static void (*const b6d980_c6d820)(void) = TIFFScanlineSize;

__attribute__((naked, noinline))
void FUN_0006d980(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "movb 0xa(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "pushl %%esi\n\t"
      "jns .LFUN_0006d980_1\n\t"
      "call *%[c6f890]\n\t"
      "movl %%eax, 0x120(%%esi)\n\t"
      "addl $4, %%esp\n\t"
      "movl $1, %%eax\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0006d980_1:\n\t"
      "call *%[c6d820]\n\t"
      "movl %%eax, 0x120(%%esi)\n\t"
      "addl $4, %%esp\n\t"
      "movl $1, %%eax\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c6f890] "m"(b6d980_c6f890), [c6d820] "m"(b6d980_c6d820)
      : "memory");
}
#else
#error "FUN_0006d980: clang naked draft required"
#endif


/* FUN_0006d9c0 (0x6d9c0) — XBE naked draft (batch 299). */
#if defined(__clang__)
static void (*const b6d9c0_c6fe10)(void) = TIFFFlushData1;

__attribute__((naked, noinline))
void FUN_0006d9c0(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xc, %%esp\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "movl 0x130(%%edx), %%ecx\n\t"
      "movl 0x134(%%edx), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "addl 0x12c(%%edx), %%ecx\n\t"
      "movl %%ecx, -0xc(%%ebp)\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "xorl %%edi, %%edi\n\t"
      "cmpl %%edi, %%ecx\n\t"
      "movl %%edi, -0x4(%%ebp)\n\t"
      "jg .LFUN_0006d9c0_3\n\t"
      ".LFUN_0006d9c0_1:\n\t"
      "movl 0x134(%%edx), %%edi\n\t"
      "movl 0x138(%%edx), %%esi\n\t"
      "movl %%eax, %%ecx\n\t"
      "subl %%edi, %%ecx\n\t"
      "addl %%ecx, %%esi\n\t"
      "popl %%edi\n\t"
      "movl %%esi, 0x138(%%edx)\n\t"
      "popl %%esi\n\t"
      "movl %%eax, 0x134(%%edx)\n\t"
      "movl $1, %%eax\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0006d9c0_2:\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "leal (%%ebx), %%ebx\n\t"
      ".LFUN_0006d9c0_3:\n\t"
      "movl 0xc(%%ebp), %%esi\n\t"
      "movzbl (%%esi), %%edx\n\t"
      "incl %%esi\n\t"
      "decl %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "movl %%edx, -0x8(%%ebp)\n\t"
      "movl %%esi, 0xc(%%ebp)\n\t"
      "movl %%ecx, 0x10(%%ebp)\n\t"
      "movl $1, %%ebx\n\t"
      "jle .LFUN_0006d9c0_6\n\t"
      "leal (%%ebx), %%ebx\n\t"
      ".LFUN_0006d9c0_4:\n\t"
      "movl 0xc(%%ebp), %%esi\n\t"
      "movzbl (%%esi), %%esi\n\t"
      "cmpl %%esi, %%edx\n\t"
      "jne .LFUN_0006d9c0_5\n\t"
      "movl 0xc(%%ebp), %%esi\n\t"
      "incl %%ebx\n\t"
      "decl %%ecx\n\t"
      "incl %%esi\n\t"
      "testl %%ecx, %%ecx\n\t"
      "movl %%esi, 0xc(%%ebp)\n\t"
      "jg .LFUN_0006d9c0_4\n\t"
      ".LFUN_0006d9c0_5:\n\t"
      "movl %%ecx, 0x10(%%ebp)\n\t"
      "leal (%%ebx), %%ebx\n\t"
      ".LFUN_0006d9c0_6:\n\t"
      "movl -0xc(%%ebp), %%esi\n\t"
      "leal 0x2(%%eax), %%ecx\n\t"
      "cmpl %%esi, %%ecx\n\t"
      "jb .LFUN_0006d9c0_11\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "cmpl $1, %%ecx\n\t"
      "je .LFUN_0006d9c0_7\n\t"
      "cmpl $3, %%ecx\n\t"
      "je .LFUN_0006d9c0_7\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "movl 0x134(%%esi), %%edx\n\t"
      "movl 0x138(%%esi), %%ecx\n\t"
      "subl %%edx, %%eax\n\t"
      "addl %%eax, %%ecx\n\t"
      "pushl %%esi\n\t"
      "movl %%ecx, 0x138(%%esi)\n\t"
      "call *%[c6fe10]\n\t"
      "addl $4, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_0006d9c0_24\n\t"
      "movl 0x134(%%esi), %%eax\n\t"
      "jmp .LFUN_0006d9c0_10\n\t"
      ".LFUN_0006d9c0_7:\n\t"
      "subl %%edi, %%eax\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl 0x134(%%eax), %%ecx\n\t"
      "movl %%edi, %%edx\n\t"
      "subl %%ecx, %%edx\n\t"
      "movl 0x138(%%eax), %%ecx\n\t"
      "addl %%edx, %%ecx\n\t"
      "pushl %%eax\n\t"
      "movl %%ecx, 0x138(%%eax)\n\t"
      "call *%[c6fe10]\n\t"
      "addl $4, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_0006d9c0_24\n\t"
      "testl %%esi, %%esi\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "movl 0x134(%%ecx), %%eax\n\t"
      "jle .LFUN_0006d9c0_9\n\t"
      "leal (%%ebx), %%ebx\n\t"
      ".LFUN_0006d9c0_8:\n\t"
      "movb (%%edi), %%dl\n\t"
      "movb %%dl, (%%eax)\n\t"
      "incl %%eax\n\t"
      "incl %%edi\n\t"
      "decl %%esi\n\t"
      "jne .LFUN_0006d9c0_8\n\t"
      ".LFUN_0006d9c0_9:\n\t"
      "movl 0x134(%%ecx), %%edi\n\t"
      ".LFUN_0006d9c0_10:\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      ".LFUN_0006d9c0_11:\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "cmpl $3, %%ecx\n\t"
      "ja .LFUN_0006d9c0_19\n\t"
      "jmp *.LFUN_0006d9c0_jt(,%%ecx,4)\n\t"
      ".LFUN_0006d9c0_12:\n\t"
      "cmpl $1, %%ebx\n\t"
      "jle .LFUN_0006d9c0_16\n\t"
      "movl $2, -0x4(%%ebp)\n\t"
      "jmp .LFUN_0006d9c0_14\n\t"
      ".LFUN_0006d9c0_13:\n\t"
      "cmpl $1, %%ebx\n\t"
      "jle .LFUN_0006d9c0_22\n\t"
      "movl $3, -0x4(%%ebp)\n\t"
      ".LFUN_0006d9c0_14:\n\t"
      "cmpl $0x80, %%ebx\n\t"
      "jle .LFUN_0006d9c0_23\n\t"
      "movb $0x81, (%%eax)\n\t"
      "incl %%eax\n\t"
      "movb %%dl, (%%eax)\n\t"
      "incl %%eax\n\t"
      "subl $0x80, %%ebx\n\t"
      "jmp .LFUN_0006d9c0_6\n\t"
      ".LFUN_0006d9c0_15:\n\t"
      "cmpl $1, %%ebx\n\t"
      "jg .LFUN_0006d9c0_14\n\t"
      ".LFUN_0006d9c0_16:\n\t"
      "movl %%eax, %%edi\n\t"
      "movb $0, (%%eax)\n\t"
      "movl $1, -0x4(%%ebp)\n\t"
      ".LFUN_0006d9c0_17:\n\t"
      "incl %%eax\n\t"
      ".LFUN_0006d9c0_18:\n\t"
      "movb %%dl, (%%eax)\n\t"
      "incl %%eax\n\t"
      ".LFUN_0006d9c0_19:\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "jg .LFUN_0006d9c0_2\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "jmp .LFUN_0006d9c0_1\n\t"
      ".LFUN_0006d9c0_20:\n\t"
      "cmpl $1, %%ebx\n\t"
      "jne .LFUN_0006d9c0_21\n\t"
      "cmpb $0xff, -0x2(%%eax)\n\t"
      "jne .LFUN_0006d9c0_21\n\t"
      "movb (%%edi), %%cl\n\t"
      "cmpb $0x7e, %%cl\n\t"
      "jge .LFUN_0006d9c0_21\n\t"
      "addb $2, %%cl\n\t"
      "xorl %%edx, %%edx\n\t"
      "cmpb $0x7f, %%cl\n\t"
      "setne %%dl\n\t"
      "movb %%cl, (%%edi)\n\t"
      "movb -0x1(%%eax), %%cl\n\t"
      "movb %%cl, -0x2(%%eax)\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "jmp .LFUN_0006d9c0_6\n\t"
      ".LFUN_0006d9c0_21:\n\t"
      "movl $2, -0x4(%%ebp)\n\t"
      "jmp .LFUN_0006d9c0_6\n\t"
      ".LFUN_0006d9c0_22:\n\t"
      "movb (%%edi), %%bl\n\t"
      "incb %%bl\n\t"
      "movb %%bl, %%cl\n\t"
      "cmpb $0x7f, %%cl\n\t"
      "movb %%bl, (%%edi)\n\t"
      "jne .LFUN_0006d9c0_18\n\t"
      "movl $0, -0x4(%%ebp)\n\t"
      "jmp .LFUN_0006d9c0_18\n\t"
      ".LFUN_0006d9c0_23:\n\t"
      "movb $1, %%cl\n\t"
      "subb %%bl, %%cl\n\t"
      "movb %%cl, (%%eax)\n\t"
      "jmp .LFUN_0006d9c0_17\n\t"
      ".LFUN_0006d9c0_24:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "orl $0xffffffff, %%eax\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_0006d9c0_jt:\n\t"
      ".long .LFUN_0006d9c0_12\n\t"
      ".long .LFUN_0006d9c0_13\n\t"
      ".long .LFUN_0006d9c0_15\n\t"
      ".long .LFUN_0006d9c0_20\n\t"
      ".text\n\t"
      :
      : [c6fe10] "m"(b6d9c0_c6fe10)
      : "memory");
}
#else
#error "FUN_0006d9c0: clang naked draft required"
#endif


/* FUN_0006dbf0 (0x6dbf0) — XBE naked draft (batch 323). */
#if defined(__clang__)
static void * (*const b6dbf0_c8e0b0)(void *destination, void *source, size_t size) = csmemcpy;
static void (*const b6dbf0_c68a30)(int param_1, const char *format, ...) = FUN_00068a30;

__attribute__((naked, noinline))
void FUN_0006dbf0(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $8, %%esp\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "movl 0x138(%%ecx), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "pushl %%ebx\n\t"
      "movl 0x134(%%ecx), %%ebx\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "jle .LFUN_0006dbf0_7\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "jmp .LFUN_0006dbf0_1\n\t"
      "leal (%%esp), %%esp\n\t"
      "nop\n\t"
      ".LFUN_0006dbf0_1:\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "testl %%edx, %%edx\n\t"
      "jle .LFUN_0006dbf0_6\n\t"
      "movsbl (%%ebx), %%esi\n\t"
      "incl %%ebx\n\t"
      "cmpl $0x80, %%esi\n\t"
      "jl .LFUN_0006dbf0_2\n\t"
      "subl $0x100, %%esi\n\t"
      ".LFUN_0006dbf0_2:\n\t"
      "testl %%esi, %%esi\n\t"
      "jge .LFUN_0006dbf0_3\n\t"
      "decl %%eax\n\t"
      "cmpl $-0x80, %%esi\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "je .LFUN_0006dbf0_5\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "movl $1, %%edx\n\t"
      "subl %%esi, %%edx\n\t"
      "subl %%edx, %%eax\n\t"
      "movl %%eax, 0x10(%%ebp)\n\t"
      "movsbl (%%ebx), %%eax\n\t"
      "incl %%ebx\n\t"
      "testl %%edx, %%edx\n\t"
      "movl %%ebx, -0x8(%%ebp)\n\t"
      "jle .LFUN_0006dbf0_5\n\t"
      "movb %%al, %%bl\n\t"
      "movb %%bl, %%bh\n\t"
      "movl %%edx, %%ecx\n\t"
      "movl %%ecx, %%esi\n\t"
      "shrl $2, %%ecx\n\t"
      "movl %%ebx, %%eax\n\t"
      "shll $0x10, %%eax\n\t"
      "movw %%bx, %%ax\n\t"
      "movl -0x8(%%ebp), %%ebx\n\t"
      "rep stosl\n\t"
      "movl %%esi, %%ecx\n\t"
      "andl $3, %%ecx\n\t"
      "rep stosb\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "addl %%edx, %%edi\n\t"
      "jmp .LFUN_0006dbf0_4\n\t"
      ".LFUN_0006dbf0_3:\n\t"
      "incl %%esi\n\t"
      "pushl %%esi\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "call *%[c8e0b0]\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "subl %%esi, %%edx\n\t"
      "addl $0xc, %%esp\n\t"
      "addl %%esi, %%edi\n\t"
      "addl %%esi, %%ebx\n\t"
      "subl %%esi, %%eax\n\t"
      "movl %%edx, 0x10(%%ebp)\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      ".LFUN_0006dbf0_4:\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "movl %%edi, 0xc(%%ebp)\n\t"
      ".LFUN_0006dbf0_5:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jg .LFUN_0006dbf0_1\n\t"
      ".LFUN_0006dbf0_6:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      ".LFUN_0006dbf0_7:\n\t"
      "movl %%eax, 0x138(%%ecx)\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%ebx, 0x134(%%ecx)\n\t"
      "popl %%ebx\n\t"
      "jle .LFUN_0006dbf0_8\n\t"
      "movl 0xd4(%%ecx), %%eax\n\t"
      "movl (%%ecx), %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl $0x2606ec\n\t"
      "pushl %%ecx\n\t"
      "call *%[c68a30]\n\t"
      "addl $0xc, %%esp\n\t"
      "xorl %%eax, %%eax\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0006dbf0_8:\n\t"
      "movl $1, %%eax\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c8e0b0] "m"(b6dbf0_c8e0b0), [c68a30] "m"(b6dbf0_c68a30)
      : "memory");
}
#else
#error "FUN_0006dbf0: clang naked draft required"
#endif


/* FUN_0006dd00 (0x6dd00) — XBE naked draft (batch 328). */
#if defined(__clang__)
static void (*const b6dd00_c6d9c0)(void) = FUN_0006d9c0;

__attribute__((naked, noinline))
void FUN_0006dd00(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%ebx\n\t"
      "movl 0x10(%%ebp), %%ebx\n\t"
      "testl %%ebx, %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x120(%%eax), %%esi\n\t"
      "pushl %%edi\n\t"
      "jle .LFUN_0006dd00_2\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_0006dd00_1:\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%edx\n\t"
      "call *%[c6d9c0]\n\t"
      "addl $0x10, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jl .LFUN_0006dd00_3\n\t"
      "subl %%esi, %%ebx\n\t"
      "addl %%esi, %%edi\n\t"
      "testl %%ebx, %%ebx\n\t"
      "jg .LFUN_0006dd00_1\n\t"
      ".LFUN_0006dd00_2:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl $1, %%eax\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0006dd00_3:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "orl $0xffffffff, %%eax\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c6d9c0] "m"(b6dd00_c6d9c0)
      : "memory");
}
#else
#error "FUN_0006dd00: clang naked draft required"
#endif


/* 0x6dd50 */
void FUN_0006dd50(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x6dda0 */
void FUN_0006dda0(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;

  crt_fprintf((void *)(uintptr_t)edi, (char *)0x00260f8c);
  /* test (char)eax, 0x20 -> je 0x6de37 */
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x00260f7c);
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x00260f60);
  /* relift: test byte ptr [esi + 0x34], 2 -> je 0x6de0e */
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x00260f48);
  /* relift: test byte ptr [esi + 0x34], 4 -> je 0x6de23 */
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x00260f34);
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x00260f24);
  /* relift: test byte ptr [esi + 0x14], 1 -> je 0x6de7b */
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x00260efc);
  /* test (char)eax, 2 -> je 0x6de6d */
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x00260ee8);
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x00260ee4);
  /* relift: test byte ptr [esi + 0x14], 2 -> je 0x6debf */
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x00260ec0);
  /* test (char)eax, 4 -> je 0x6deb1 */
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x00260eac);
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x00260ee4);
  /* relift: test byte ptr [esi + 0x14], 8 -> je 0x6df38 */
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x00260e94);
  /* test eax, 0x1000000 -> je 0x6df2a */
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x00260e80);
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x00260e58);
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x00260ee4);
  /* relift: test byte ptr [esi + 0x14], 0x10 -> je 0x6df5c */
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x00260e44);
  /* test (char)ebx, (char)eax -> je 0x6df78 */
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x00260e30);
  /* relift: test byte ptr [esi + 0x18], (char)ebx -> je 0x6dfee */
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x00260e1c);
  /* cmp ecx, 3 -> ja 0x6dfde */
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x00260e14);
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x00260e04);
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x00260df0);
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x00260dd8);
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x00260dcc);
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x00260db4);
  /* cmp eax, 0x7ffe -> jg 0x6e0a7 */
  /* cmp eax, 5 -> ja 0x6e0b8 */
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x00260dac);
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x00260d88);
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x00260d64);
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x00260d40);
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x00260d20);
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x00260d10);
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x00260cf8);
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x00260dcc);
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x00260cdc);
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x00260cbc);
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x00260c84);
  /* test (char)eax, 1 -> je 0x6e14b */
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x00260c64);
  /* cmp (int16_t)eax, 9 -> jae 0x6e138 */
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x00260c60);
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x00260dcc);
  /* relift: test byte ptr [esi + 0x18], 4 -> je 0x6e171 */
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x00260c2c);
  /* test (char)eax, 2 -> je 0x6e1c4 */
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x00260c18);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)esi;
  (void)edi;
}
