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

/* 0x6c680 */
void FUN_0006c680(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x6c6f0 */
void FUN_0006c6f0(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

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


/* 0x6c860 */
void FUN_0006c860(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x6c8d0 */
void FUN_0006c8d0(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

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

/* 0x6d180 */
void FUN_0006d180(void)
{
  int edi = 0;

  /* test edi, edi -> jle 0x6d1bc */
  /* test edi, edi -> jg 0x6d1a0 */
  FUN_0006cfa0();

  (void)edi;
}

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

/* 0x6d340 */
void FUN_0006d340(void)
{
  int eax = 0;
  int ebx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  /* test eax, eax -> je 0x6d47f */
  /* cmp eax, 0x40 -> je 0x6d409 */
  /* cmp eax, 3 -> ja 0x6d3f0 */
  /* relift: cmp esi, dword ptr [ebp - 0xc] -> jge 0x6d449 */
  /* test ebx, ebx -> je 0x6d497 */
  /* cmp ebx, edx -> jl 0x6d497 */
  csmemcpy((void *)(uintptr_t)edx, (void *)0, 0);
  /* cmp ebx, esi -> jl 0x6d49a */
  csmemcpy((void *)(uintptr_t)edx, (void *)(uintptr_t)edi, esi);
  FUN_00068a30(0, (char *)0x002605a4);

  (void)eax;
  (void)ebx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x6d4d0 */
void FUN_0006d4d0(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x6d500 */
void FUN_0006d500(void)
{
  int ecx = 0;

  /* cmp (char)ecx, 0x61 -> je 0x6d579 */
  /* cmp (char)ecx, 0x72 -> je 0x6d568 */
  /* cmp (char)ecx, 0x77 -> je 0x6d579 */
  FUN_00068a30(0, (char *)0x002605d0);
  /* cmp (char)ecx, 0x2b -> jne 0x6d588 */

  (void)ecx;
}

/* 0x6d590 */
void TIFFFdOpen(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;

  /* cmp (char)eax, 0x72 -> je 0x6d5af */
  /* cmp (char)eax, 0x77 -> je 0x6d5bf */
  /* cmp (char)eax, 0x2b -> jne 0x6d5cd */
  csstrlen((char *)(uintptr_t)ebx);
  debug_malloc(eax, 0, (char *)0, 0);
  /* test esi, esi -> jne 0x6d61f */
  FUN_00068a30(0x002ec96c, (char *)0x0026068c);
  __close(0);
  csmemset((void *)(uintptr_t)esi, 0, 316);
  csstrcpy((char *)(uintptr_t)eax, (char *)(uintptr_t)ebx);
  __read();
  /* cmp eax, 8 -> je 0x6d70d */
  /* relift: cmp word ptr [esi + 6], 0 -> jne 0x6d6a3 */
  FUN_00068a30(0, (char *)0x00260674);
  __write();
  /* cmp eax, 8 -> je 0x6d6e2 */
  FUN_00068a30(0, (char *)0x0025fe8c);
  FUN_0006d500();
  FUN_00066190();
  /* test eax, eax -> je 0x6d808 */
  /* cmp (int16_t)edi, 0x4d4d -> je 0x6d739 */
  /* cmp (int16_t)edi, 0x4949 -> je 0x6d739 */
  FUN_00068a30(0, (char *)0x00260648);
  FUN_0006d500();
  /* relift: test byte ptr [esi + 0xa], 0x10 -> je 0x6d766 */
  FUN_0006f1b0();
  FUN_0006f1d0();
  /* cmp (int16_t)eax, 0x2a -> je 0x6d78b */
  FUN_00068a30(0, (char *)0x00260618);
  /* cmp (char)eax, 0x61 -> je 0x6d7df */
  /* cmp (char)eax, 0x72 -> jne 0x6d808 */
  FUN_00066e70();
  /* test eax, eax -> je 0x6d808 */
  /* test (char)ecx, 0x10 -> je 0x6d7f7 */
  FUN_00068a30(0, (char *)0x002605e0);
  FUN_00066190();
  /* test eax, eax -> jne 0x6d706 */
  FUN_00064ee0(0);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)esi;
  (void)edi;
}

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

/* 0x6d980 */
void FUN_0006d980(void)
{
  FUN_0006f890();
  TIFFScanlineSize();
}

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


/* 0x6dbf0 */
void FUN_0006dbf0(void)
{
  int eax = 0;
  int ebx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* test edx, edx -> jle 0x6dcbb */
  /* cmp esi, 0x80 -> jl 0x6dc3d */
  /* test esi, esi -> jge 0x6dc8a */
  csmemcpy((void *)(uintptr_t)edi, (void *)(uintptr_t)ebx, esi);
  /* test eax, eax -> jg 0x6dc20 */
  FUN_00068a30(0, (char *)0x002606ec);

  (void)eax;
  (void)ebx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x6dd00 */
void FUN_0006dd00(void)
{
  int eax = 0;
  int ebx = 0;

  FUN_0006d9c0();
  /* test eax, eax -> jl 0x6dd48 */
  /* test ebx, ebx -> jg 0x6dd20 */

  (void)eax;
  (void)ebx;
}

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
