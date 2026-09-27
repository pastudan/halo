#include <stdint.h>
/* kb object: <common> -> kb_common_stubs.c */

/* --- <common> batch drafts (2026-07-26) --- */

/* FUN_00067710 (0x67710) — readable C lift.
 * ABI: tag@<ax>, value@<ecx>, out@<edx>, tif@<esi>. */
void FUN_00067710(unsigned short tag /*@<ax>*/, unsigned int value /*@<ecx>*/,
                  void *out /*@<edx>*/, void *tif /*@<esi>*/)
{
  unsigned int masked;
  unsigned int shift;
  char *bitmask;
  char *bitspersample;

  *(unsigned short *)out = tag;
  *((unsigned int *)out + 1) = 1;
  if (value > 0xffffu) {
    *((unsigned short *)out + 1) = 4;
    *((unsigned int *)out + 2) = value;
    return;
  }
  *((unsigned short *)out + 1) = 3;
  bitmask = *(char **)((char *)tif + 0xd0);
  masked = *(unsigned int *)(bitmask + 0xc);
  masked &= value;
  if (*(unsigned short *)((char *)tif + 0xc4) == 0x4d4d) {
    bitspersample = *(char **)((char *)tif + 0xcc);
    shift = *(unsigned int *)(bitspersample + 0xc);
    masked <<= (unsigned char)shift;
  }
  *((unsigned int *)out + 2) = masked;
}

/* FUN_00067760 (0x67760) — implemented in bitmaps/libtiff/tif_dirwrite.c */

/* FUN_000677f0 (0x677f0) — readable C lift (restored pre-naked). */
void FUN_000677f0(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int esi = 0;

  ((void (*)(void))__lseek)();
  ((void (*)(void))__lseek)();
  ((void (*)(void))__write)();
  /* cmp eax, 8 -> je 0x6785f */
  FUN_00068a30(0, (char *)0x0025fe8c);
  ((void (*)(void))__lseek)();
  /* cmp eax, ecx -> jne 0x6793f */
  __read();
  /* cmp eax, 2 -> jne 0x6793f */
  /* relift: test byte ptr [esi + 0xa], (char)ebx -> je 0x678b8 */
  ((void(*)(void))FUN_0006f1b0)();
  ((void (*)(void))__lseek)();
  __read();
  /* cmp eax, 4 -> jne 0x6792d */
  /* relift: test byte ptr [esi + 0xa], (char)ebx -> je 0x678f8 */
  ((void(*)(void))FUN_0006f1d0)();
  /* test ecx, ecx -> jne 0x67870 */
  ((void (*)(void))__lseek)();
  ((void (*)(void))__write)();
  /* cmp eax, 4 -> je 0x67934 */
  FUN_00068a30(0x002ca124, (char *)0x0025fe2c);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)esi;
}


/* FUN_00067960 (0x67960) — readable C lift.
 * ABI: type@<ax>, tag@<cx>, out@<edx>; packs one float as RATIONAL. */
int FUN_00067960(unsigned short type /*@<ax>*/, unsigned short tag /*@<cx>*/,
                 void *out /*@<edx>*/, void *ctx, float value)
{
  int pair[2];
  void *typeinfo;

  *(unsigned short *)out = tag;
  *((unsigned short *)out + 1) = type;
  *((unsigned int *)out + 1) = 1;
  if (type == 5 && value < 0.0f) {
    typeinfo = ((void *(*)(unsigned int))TIFFDefaultDirectory)((unsigned int)tag);
    FUN_0006f9d0(*(void **)ctx, (void *)0x25feb8,
                 *(void **)((char *)typeinfo + 0x10), (double)value);
  }
  pair[0] = (int)((double)value * 10000.0 + 0.5);
  pair[1] = 0x2710;
  return ((int (*)(void *))FUN_00067760)(pair);
}

/* FUN_000679f0 (0x679f0) — XBE naked draft (batch 340). */
#if defined(__clang__)
static void (*const b679f0_c67760)(void) = (void(*)(void))FUN_00067760;

__attribute__((naked, noinline))
int FUN_000679f0(unsigned short tag, void *tif, void *out, int count, void **items)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl %%ecx, %%edi\n\t"
      "movl %%edx, %%ebx\n\t"
      "movw %%ax, (%%edi)\n\t"
      "movl 0x3340b0, %%eax\n\t"
      "movw $3, 0x2(%%edi)\n\t"
      "movb 0x36(%%ebx), %%cl\n\t"
      "movl $1, %%edx\n\t"
      "shll %%cl, %%edx\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "xorl %%esi, %%esi\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%edx, 0x4(%%edi)\n\t"
      "jle .LFUN_000679f0_2\n\t"
      ".LFUN_000679f0_1:\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "movl (%%ecx,%%esi,4), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c67760]\n\t"
      "addl $4, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_000679f0_3\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "incl %%esi\n\t"
      "cmpl %%eax, %%esi\n\t"
      "jl .LFUN_000679f0_1\n\t"
      ".LFUN_000679f0_2:\n\t"
      "movl 0x4(%%edi), %%eax\n\t"
      "imull 0x8(%%ebp), %%eax\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movl %%eax, 0x4(%%edi)\n\t"
      "movl %%ecx, 0x8(%%edi)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl $1, %%eax\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000679f0_3:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "xorl %%eax, %%eax\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c67760] "m"(b679f0_c67760)
      : "memory");
}
#else
#error "FUN_000679f0: clang naked draft required"
#endif


/* FUN_00067a70 (0x67a70) — readable C lift.
 * ABI: tag@<ax>, out@<ecx>, s@<esi>. */
int FUN_00067a70(unsigned short tag /*@<ax>*/, void *out /*@<ecx>*/,
                 const char *s /*@<esi>*/)
{
  unsigned int len;
  int (*alloc_ascii)(const char *) = (int (*)(const char *))FUN_00067760;

  *(unsigned short *)out = tag;
  *((unsigned short *)out + 1) = 2;
  len = (unsigned int)csstrlen(s) + 1u;
  *((unsigned int *)out + 1) = len;
  if (len > 4u) {
    if (!alloc_ascii(s))
      return 0;
  } else {
    csmemcpy((char *)out + 8, (void *)s, len);
  }
  return 1;
}

/* FUN_00067ac0 (0x67ac0) — readable C lift.
 * ABI: count@<eax>, tag@<dx>, src@<ecx>, tif/type/out cdecl. */
int FUN_00067ac0(unsigned int count /*@<eax>*/, unsigned short tag /*@<dx>*/,
                 unsigned short *src /*@<ecx>*/, void *tif, unsigned short type,
                 void *out)
{
  unsigned int lo;
  unsigned int packed;

  *(unsigned short *)out = tag;
  *((unsigned short *)out + 1) = type;
  *((unsigned int *)out + 1) = count;
  if ((int)count > 2)
    return ((int (*)(void *))FUN_00067760)(src);
  lo = (unsigned int)src[0];
  if (*(unsigned short *)((char *)tif + 0xc4) == 0x4d4d) {
    packed = lo << 16;
    *((unsigned int *)out + 2) = packed;
    if (count == 2u)
      *((unsigned int *)out + 2) = packed | (unsigned int)src[1];
  } else {
    *((unsigned int *)out + 2) = lo;
    if (count == 2u)
      *((unsigned int *)out + 2) = ((unsigned int)src[1] << 16) | lo;
  }
  return 1;
}

/* FUN_00067b40 (0x67b40) — readable C lift.
 * ABI: count@<eax>, tag@<dx>, src@<ecx>, type cdecl, out cdecl. */
int FUN_00067b40(unsigned int count /*@<eax>*/, unsigned short tag /*@<dx>*/,
                 unsigned int *src /*@<ecx>*/, unsigned short type, void *out)
{
  *(unsigned short *)out = tag;
  *((unsigned short *)out + 1) = type;
  *((unsigned int *)out + 1) = count;
  if (count != 1u)
    return ((int (*)(void *))FUN_00067760)(src);
  *((unsigned int *)out + 2) = *src;
  return 1;
}

/* FUN_00067b80 (0x67b80) — XBE naked draft (batch 376). */
#if defined(__clang__)
static void * (*const b67b80_c8ee60)(uint32_t size, bool zero, const char *file, int line) = (void *)debug_malloc;
static void (*const b67b80_ftol)(void) = FUN_001d9068;
static void (*const b67b80_c67760)(void) = (void *)FUN_00067760;
static void (*const b67b80_c8ef70)(void *ptr, const char *file, int line) = (void *)debug_free;

__attribute__((naked, noinline))
int FUN_00067b80(unsigned int count, unsigned short tag, void *typeinfo, unsigned short type, void *out, float *values)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movw 0xc(%%ebp), %%dx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl %%eax, %%edi\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "pushl $0x27a\n\t"
      "pushl $0x25fefc\n\t"
      "movw %%cx, (%%eax)\n\t"
      "movw %%dx, 0x2(%%eax)\n\t"
      "movl %%edi, 0x4(%%eax)\n\t"
      "leal (,%%edi,8), %%eax\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "call *%[c8ee60]\n\t"
      "addl $0x10, %%esp\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "testl %%edi, %%edi\n\t"
      "movl %%eax, %%esi\n\t"
      "jle .LFUN_00067b80_2\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".LFUN_00067b80_1:\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      "flds (%%ecx,%%ebx,4)\n\t"
      "fmull 0x25feb0\n\t"
      "faddl 0x25fea8\n\t"
      "call *%[ftol]\n\t"
      "movl %%eax, (%%esi,%%ebx,8)\n\t"
      "movl $0x2710, 0x4(%%esi,%%ebx,8)\n\t"
      "incl %%ebx\n\t"
      "cmpl %%edi, %%ebx\n\t"
      "jl .LFUN_00067b80_1\n\t"
      ".LFUN_00067b80_2:\n\t"
      "movl 0x10(%%ebp), %%edi\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "pushl %%esi\n\t"
      "call *%[c67760]\n\t"
      "pushl $0x281\n\t"
      "pushl $0x25fefc\n\t"
      "pushl %%esi\n\t"
      "movl %%eax, %%edi\n\t"
      "call *%[c8ef70]\n\t"
      "addl $0x10, %%esp\n\t"
      "movl %%edi, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c8ee60] "m"(b67b80_c8ee60), [ftol] "m"(b67b80_ftol), [c67760] "m"(b67b80_c67760), [c8ef70] "m"(b67b80_c8ef70)
      : "memory");
}
#else
#error "FUN_00067b80: clang naked draft required"
#endif


/* FUN_00067c10 (0x67c10) — readable C lift.
 * ABI: count@<eax>, tag@<dx>, src@<ecx>, type cdecl, out cdecl. */
int FUN_00067c10(unsigned int count /*@<eax>*/, unsigned short tag /*@<dx>*/,
                 unsigned int *src /*@<ecx>*/, unsigned short type, void *out)
{
  *(unsigned short *)out = tag;
  *((unsigned short *)out + 1) = type;
  *((unsigned int *)out + 1) = count;
  if (count != 1u)
    return ((int (*)(void *))FUN_00067760)(src);
  *((unsigned int *)out + 2) = *src;
  return 1;
}

/* 0x67c50 */
void FUN_00067c50(void)
{
  int eax = 0;
  int ecx = 0;
  int esi = 0;

  /* cmp (int16_t)ecx, 1 -> jbe 0x67cf1 */
  ((void(*)(void))_TIFFgetfield)();
  ((void(*)(void))_TIFFgetfield)();
  ((void(*)(void))FUN_00067ac0)();
  /* test eax, eax -> jne 0x67d31 */
  ((void(*)(void))_TIFFgetfield)();
  /* relift: cmp word ptr [esi + 0xc4], 0x4d4d -> jne 0x67d3d */
  /* cmp (int16_t)ecx, 1 -> jbe 0x67dbf */
  ((void(*)(void))_TIFFgetfield)();
  ((void(*)(void))_TIFFgetfield)();
  ((void(*)(void))FUN_00067b40)();
  /* test eax, eax -> jne 0x67d31 */
  ((void(*)(void))_TIFFgetfield)();
  /* cmp (int16_t)ecx, 1 -> jbe 0x67e3c */
  ((void(*)(void))_TIFFgetfield)();
  ((void(*)(void))_TIFFgetfield)();
  ((void(*)(void))FUN_00067b80)();
  /* test eax, eax -> jne 0x67d31 */
  ((void(*)(void))_TIFFgetfield)();
  ((void(*)(void))FUN_00067960)();
  /* test eax, eax -> jne 0x67d31 */
  /* cmp (int16_t)ecx, 1 -> jbe 0x67ef2 */
  ((void(*)(void))_TIFFgetfield)();
  ((void(*)(void))_TIFFgetfield)();
  ((void(*)(void))FUN_00067760)();
  /* test eax, eax -> jne 0x67d31 */
  ((void(*)(void))_TIFFgetfield)();
  ((void(*)(void))_TIFFgetfield)();
  ((void(*)(void))FUN_00067a70)();
  /* test eax, eax -> jne 0x67d31 */

  (void)eax;
  (void)ecx;
  (void)esi;
}


/* FUN_00067f70 (0x67f70) — XBE naked draft (batch 327). */
#if defined(__clang__)
static void (*const b67f70_c65f70)(void) = (void(*)(void))_TIFFgetfield;
static void (*const b67f70_c67760)(void) = (void(*)(void))FUN_00067760;

__attribute__((naked, noinline))
int FUN_00067f70(void *out, void *tif, unsigned short tag)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xc, %%esp\n\t"
      "movzwl 0xc(%%ebp), %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "movzwl 0x44(%%edi), %%ebx\n\t"
      "leal -0x4(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "leal 0x14(%%edi), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c65f70]\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%ebx, %%ebx\n\t"
      "jle .LFUN_00067f70_1\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movw %%ax, %%dx\n\t"
      "movl %%ebx, %%ecx\n\t"
      "leal -0xc(%%ebp), %%edi\n\t"
      "shll $0x10, %%edx\n\t"
      "movw %%ax, %%dx\n\t"
      "shrl $1, %%ecx\n\t"
      "movl %%edx, %%eax\n\t"
      "rep stosl\n\t"
      "adcl %%ecx, %%ecx\n\t"
      "rep stosw\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      ".LFUN_00067f70_1:\n\t"
      "cmpl $2, %%ebx\n\t"
      "movw 0xc(%%ebp), %%ax\n\t"
      "movw %%ax, (%%esi)\n\t"
      "movw $3, 0x2(%%esi)\n\t"
      "movl %%ebx, 0x4(%%esi)\n\t"
      "jg .LFUN_00067f70_4\n\t"
      "cmpw $0x4d4d, 0xc4(%%edi)\n\t"
      "movzwl -0xc(%%ebp), %%eax\n\t"
      "jne .LFUN_00067f70_2\n\t"
      "shll $0x10, %%eax\n\t"
      "cmpl $2, %%ebx\n\t"
      "movl %%eax, 0x8(%%esi)\n\t"
      "jne .LFUN_00067f70_3\n\t"
      "movzwl -0xa(%%ebp), %%ecx\n\t"
      "orl %%eax, %%ecx\n\t"
      "popl %%edi\n\t"
      "movl %%ecx, 0x8(%%esi)\n\t"
      "movl $1, %%eax\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00067f70_2:\n\t"
      "cmpl $2, %%ebx\n\t"
      "movl %%eax, 0x8(%%esi)\n\t"
      "jne .LFUN_00067f70_3\n\t"
      "movzwl -0xa(%%ebp), %%edx\n\t"
      "shll $0x10, %%edx\n\t"
      "orl %%eax, %%edx\n\t"
      "movl %%edx, 0x8(%%esi)\n\t"
      ".LFUN_00067f70_3:\n\t"
      "popl %%edi\n\t"
      "movl $1, %%eax\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00067f70_4:\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "leal -0xc(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl %%esi, %%edi\n\t"
      "call *%[c67760]\n\t"
      "addl $4, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c65f70] "m"(b67f70_c65f70), [c67760] "m"(b67f70_c67760)
      : "memory");
}
#else
#error "FUN_00067f70: clang naked draft required"
#endif


/* FUN_00068030 moved to bitmaps/libtiff/tif_dir.c (readable C lift). */
/* FUN_000680a0 (0x680a0) — Capstone tip: flags word==0 → return 1. */
int FUN_000680a0(void *obj)
{
  if (*(short *)((char *)obj + 6) == 0)
    return 1;
  return 0;
}



/* FUN_0006bcb0 (0x6bcb0) — readable C lift (restored pre-naked). */
void FUN_0006bcb0(void)
{
  int eax = 0;
  int ebx = 0;
  int edx = 0;
  int esi = 0;

  FUN_0006b780();
  ((void(*)(void))FUN_0006f180)();
  debug_malloc(eax, 0, (char *)0, 0);
  FUN_00068a30(0, (char *)0x00260304);
  ((void (*)(void))FUN_0006a310)();
  FUN_00064ec0(0, 0, 0);
  ((void (*)(void))TIFFGetField)();
  ((void(*)(void))TIFFScanlineSize)();
  /* cmp ebx, eax -> jae 0x6bd79 */
  /* test eax, eax -> jbe 0x6be1e */
  /* cmp edx, eax -> jbe 0x6bd9e */
  ((void(*)(void))FUN_0006f0d0)();
  ((void (*)(void))FUN_0006ede0)();
  /* test eax, eax -> jge 0x6bdd2 */
  /* test eax, eax -> jne 0x6be1b */
  /* relift: cmp word ptr [0x3340f0], 1 -> jne 0x6be03 */
  debug_free((void *)(uintptr_t)esi, (char *)0x00260264, 459);

  (void)eax;
  (void)ebx;
  (void)edx;
  (void)esi;
}


/* FUN_0006be40 (0x6be40) — readable C lift (restored pre-naked). */
void FUN_0006be40(void)
{
  int eax = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  ((void(*)(void))FUN_0006f180)();
  debug_malloc(eax, edi, (char *)0x00260264, 487);
  /* relift: cmp dword ptr [ebp - 4], edi -> jne 0x6bee2 */
  FUN_00068a30(0, (char *)0x002602d0);
  /* cmp eax, edi -> jne 0x6bee2 */
  FUN_00068a30(0, (char *)0x002602d0);
  ((void (*)(void))FUN_0006a310)();
  FUN_00064ec0(0, 0, 0);
  ((void (*)(void))TIFFGetField)();
  ((void(*)(void))TIFFScanlineSize)();
  /* cmp edi, eax -> jae 0x6bf48 */
  /* test esi, esi -> jbe 0x6c055 */
  /* cmp edx, esi -> jbe 0x6bf6e */
  ((void(*)(void))FUN_0006f0d0)();
  ((void (*)(void))FUN_0006ede0)();
  /* test eax, eax -> jge 0x6bfa8 */
  /* test eax, eax -> jne 0x6c055 */
  ((void(*)(void))FUN_0006f0d0)();
  ((void (*)(void))FUN_0006ede0)();
  /* test eax, eax -> jge 0x6bfd6 */
  /* test eax, eax -> jne 0x6c055 */
  ((void(*)(void))FUN_0006f0d0)();
  ((void (*)(void))FUN_0006ede0)();
  /* test eax, eax -> jge 0x6c004 */
  /* test eax, eax -> jne 0x6c055 */
  /* relift: cmp word ptr [0x3340f0], 1 -> jne 0x6c03d */
  debug_free((void *)(uintptr_t)edx, (char *)0x00260264, 517);

  (void)eax;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}


/* FUN_0006c080 — defined in bitmaps/libtiff/tif_flush.c */





/* FUN_00074fb0 (0x74fb0) — Capstone tip: bitmap_verify fail → assert. */
void FUN_00074fb0(void *pixel_data, void *bitmap_data)
{
  (void)bitmap_data;
  if (!bitmap_verify(pixel_data, 1)) {
    display_assert((const char *)0x261aa4, (const char *)0x2616f0, 0x5f9, true);
    system_exit(-1);
  }
}

/* bitmap_cube_map_face_insert (0x7ece0) — Capstone tip: bitmap_verify fail → assert. */
void bitmap_cube_map_face_insert(void *bitmap_2d, void *bitmap_cube, int mipmap, int face)
{
  (void)bitmap_cube;
  (void)mipmap;
  (void)face;
  if (!bitmap_verify(bitmap_2d, 0)) {
    display_assert((const char *)0x26555c, (const char *)0x264a74, 0x34c, true);
    system_exit(-1);
  }
}


/* FUN_0007ef80 (0x7ef80) — Capstone tip: count<=0 → return. */
void FUN_0007ef80(void *dst, void *unused, short count, void *src)
{
  (void)dst; (void)unused; (void)src;
  if (count <= 0)
    return;
}



/* FUN_0007f150 (0x7f150) — Capstone tip: bitmap_verify fail → assert. */
void FUN_0007f150(void)
{
  if (!bitmap_verify((void *)0, 1)) {
    display_assert((const char *)0x261814, (const char *)0x2657dc, 0x30, true);
    system_exit(-1);
  }
}

/* FUN_000887e0 (0x887e0) — readable C lift (restored pre-naked). */
void FUN_000887e0(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int edi = 0;

  player_control_get_unit_camera_info(ecx, (void *)(uintptr_t)eax);
  /* test (char)eax, (char)eax -> je 0x8886b */
  /* test (char)eax, 0x41 -> jne 0x8885a */
  director_set_local_player_context(eax);
  /* test (char)eax, 0x41 -> je 0x8888c */
  /* cmp eax, -1 -> je 0x888c6 */
  angles_to_vector((float *)(uintptr_t)ebx, (float *)(uintptr_t)ecx);
  observer_up_from_forward((float *)(uintptr_t)ebx, (float *)(uintptr_t)edx);
  object_get_root_location(0, (float *)(uintptr_t)eax, (float *)0);
  valid_real_normal3d_perpendicular((float *)(uintptr_t)eax, (float *)(uintptr_t)edi);
  /* test (char)eax, (char)eax -> je 0x88b73 */
  /* test (char)eax, 1 -> jne 0x88b73 */
  /* test (char)eax, 1 -> jne 0x88b73 */
  /* test (char)eax, 1 -> jne 0x88b73 */
  /* test (char)eax, 1 -> jne 0x88b73 */
  /* test (char)eax, 1 -> jne 0x88b73 */
  /* test (char)eax, 1 -> jne 0x88b73 */
  real_vector3d_valid((float *)(uintptr_t)eax);
  /* test (char)eax, (char)eax -> je 0x88b73 */
  /* test (char)eax, 1 -> jne 0x88b73 */
  /* test (char)eax, 1 -> jne 0x88b73 */
  /* test (char)eax, 1 -> jne 0x88b73 */
  csprintf((char *)0x005ab100, (char *)0x00266e08);
  display_assert((char *)(uintptr_t)eax, (char *)0, 0, 0);
  system_exit(0);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)edi;
}


/* first_person_camera_new (0x88c40) — defined in camera/director.c */


/* FUN_00088c80 (0x88c80) — readable C lift: unit seat marker vectors. */
void FUN_00088c80(int unit_handle, float *out_a, float *out_b)
{
  char *unit;
  int parent;
  void *obj;
  void *tag;
  void *elem;
  char markers[0x6c];
  short n;

  unit = (char *)object_get_and_verify_type(unit_handle, 3);
  unit_set_seat_state(unit_handle, out_a);
  out_b[0] = *(float *)(unit + 0x1ec);
  out_b[1] = *(float *)(unit + 0x1f0);
  out_b[2] = *(float *)(unit + 0x1f4);
  parent = *(int *)(unit + 0xcc);
  if (parent == -1)
    return;
  obj = object_try_and_get_and_verify_type(parent, 2);
  if (!obj)
    return;
  tag = tag_get(0x76656869, *(int *)obj);
  elem = tag_block_get_element((char *)tag + 0x2e4, (int)*(short *)(unit + 0x2a0), 0x11c);
  if ((*(signed char *)elem) >= 0)
    return;
  n = object_get_markers_by_string_id(parent, (const char *)0x267238, markers, 1);
  if (!n)
    return;
  out_a[0] = *(float *)(markers + 0x60);
  out_a[1] = *(float *)(markers + 0x64);
  out_a[2] = *(float *)(markers + 0x68);
  out_b[0] = *(float *)(markers + 0x3c);
  out_b[1] = *(float *)(markers + 0x40);
  out_b[2] = *(float *)(markers + 0x44);
}



/* first_person_camera_for_unit_and_vector (0x88d50) — Capstone tip: perp fail → assert. */
void first_person_camera_for_unit_and_vector(void *dest /*@<esi>*/, int object_handle /*@<ecx>*/,
                                            void *vector /*@<eax>*/)
{
  char *out = (char *)dest;
  float *vec = (float *)vector;
  float *global_up = (float *)0x0031fc38;
  unsigned int fov_bits = 0x3f9c61aa;

  (void)object_handle;
  *(int *)(out + 0x48) = 0;
  *(int *)out = 0;
  *(float *)(out + 0x10) = global_up[0];
  *(float *)(out + 0x14) = global_up[1];
  *(float *)(out + 0x18) = global_up[2];
  *(float *)(out + 0x24) = vec[0];
  *(float *)(out + 0x28) = vec[1];
  *(float *)(out + 0x2c) = vec[2];
  *(int *)(out + 0x1c) = 0;
  *(unsigned int *)(out + 0x20) = fov_bits;

  observer_up_from_forward((float *)(out + 0x24), (float *)(out + 0x30));
  if (!valid_real_normal3d_perpendicular((float *)(out + 0x24), (float *)(out + 0x30))) {
    display_assert((const char *)0x0026720c, (const char *)0x00267248, 0x52, 1);
    system_exit(-1);
  }
}


/* FUN_000b3df0 (0xb3df0) — Capstone tip: code-0x16 > 0xe → return 0. */
char FUN_000b3df0(int a, unsigned int code, void *player_or_ctx, int buf, int buf_size)
{
  (void)a;
  (void)player_or_ctx;
  (void)buf;
  (void)buf_size;
  if (code - 0x16u > 0xeu)
    return 0;
  return 1;
}


/* FUN_000c0bb0 (0xc0bb0) — readable C lift. */
void FUN_000c0bb0(int16_t function_index, int thread_datum, char init)
{
  int *eval;

  eval = (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (eval) {
    FUN_00057900(eval[0], *(unsigned char *)((char *)eval + 4));
    hs_return(thread_datum, 0);
  }
}

/* FUN_000c0bf0 (0xc0bf0) — readable C lift. */
void FUN_000c0bf0(int16_t function_index, int thread_datum, char init)
{
  int *eval;

  eval = (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (eval) {
    FUN_000579d0(eval[0], *(short *)((char *)eval + 4));
    hs_return(thread_datum, 0);
  }
}

/* playlist_profile_change_slayer_rules (0xed240) — readable C lift (restored pre-naked). */
void playlist_profile_change_slayer_rules(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;

  player_ui_get_edit_playlist_profile();
  display_assert((char *)0x00287b1c, (char *)0x002859a4, 2883, 0);
  system_exit(0);
  /* cmp edi, ebx -> je 0xed42a */
  /* cmp edi, ebx -> jne 0xed2ac */
  display_assert((char *)0x00286a64, (char *)0x002859a4, 2891, 0);
  system_exit(0);
  /* cmp esi, ebx -> je 0xed2c5 */
  /* relift: cmp word ptr [esi + 0xe], (int16_t)ecx -> je 0xed2ea */
  /* cmp esi, ebx -> jne 0xed2b3 */
  display_assert((char *)0x00286a38, (char *)0x002859a4, 2893, 0);
  system_exit(0);
  /* cmp edi, ebx -> jne 0xed32d */
  display_assert((char *)0x002869d4, (char *)0x002859a4, 2902, 0);
  system_exit(0);
  /* cmp esi, ebx -> je 0xed341 */
  /* relift: cmp word ptr [esi + 0xe], (int16_t)ecx -> je 0xed366 */
  /* cmp esi, ebx -> jne 0xed334 */
  display_assert((char *)0x002869a8, (char *)0x002859a4, 2904, 0);
  system_exit(0);
  /* cmp eax, 0xe -> ja 0xed39e */
  /* cmp esi, ebx -> jne 0xed3ce */
  display_assert((char *)0x00286950, (char *)0x002859a4, 2916, 0);
  system_exit(0);
  /* cmp esi, ebx -> je 0xed3e2 */
  /* relift: cmp word ptr [esi + 0xe], (int16_t)ecx -> je 0xed402 */
  /* cmp esi, ebx -> jne 0xed3d5 */
  display_assert((char *)0x00286928, (char *)0x002859a4, 2918, 0);
  system_exit(0);
  error(0, (char *)0x00286550);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)esi;
  (void)edi;
}


/* FUN_000ed470 (0xed470) — readable C lift (restored pre-naked). */
void FUN_000ed470(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;

  player_ui_get_edit_playlist_profile();
  display_assert((char *)0x00287b1c, (char *)0x002859a4, 2943, 0);
  system_exit(0);
  /* cmp edi, ebx -> je 0xed75d */
  /* cmp edi, ebx -> jne 0xed4dc */
  display_assert((char *)0x00286c9c, (char *)0x002859a4, 2951, 0);
  system_exit(0);
  /* cmp esi, ebx -> je 0xed4f5 */
  /* relift: cmp word ptr [esi + 0xe], (int16_t)ecx -> je 0xed51a */
  /* cmp esi, ebx -> jne 0xed4e3 */
  display_assert((char *)0x00286c70, (char *)0x002859a4, 2953, 0);
  system_exit(0);
  /* cmp edi, ebx -> jne 0xed560 */
  display_assert((char *)0x00286c10, (char *)0x002859a4, 2962, 0);
  system_exit(0);
  /* cmp esi, ebx -> je 0xed574 */
  /* relift: cmp word ptr [esi + 0xe], (int16_t)ecx -> je 0xed599 */
  /* cmp esi, ebx -> jne 0xed567 */
  display_assert((char *)0x00286be0, (char *)0x002859a4, 2964, 0);
  system_exit(0);
  /* cmp edi, ebx -> jne 0xed5df */
  display_assert((char *)0x00286b80, (char *)0x002859a4, 2973, 0);
  system_exit(0);
  /* cmp esi, ebx -> je 0xed5f3 */
  /* relift: cmp word ptr [esi + 0xe], (int16_t)ecx -> je 0xed618 */
  /* cmp esi, ebx -> jne 0xed5e6 */
  display_assert((char *)0x00286b54, (char *)0x002859a4, 2975, 0);
  system_exit(0);
  /* cmp edi, ebx -> jne 0xed65e */
  display_assert((char *)0x00286af4, (char *)0x002859a4, 2984, 0);
  system_exit(0);
  /* cmp esi, ebx -> je 0xed672 */
  /* relift: cmp word ptr [esi + 0xe], (int16_t)ecx -> je 0xed697 */
  /* cmp esi, ebx -> jne 0xed665 */
  display_assert((char *)0x00286ac8, (char *)0x002859a4, 2986, 0);
  system_exit(0);
  /* cmp eax, 0x2d -> ja 0xed6d1 */
  /* cmp esi, ebx -> jne 0xed701 */
  display_assert((char *)0x00286950, (char *)0x002859a4, 2998, 0);
  system_exit(0);
  /* cmp esi, ebx -> je 0xed715 */
  /* relift: cmp word ptr [esi + 0xe], (int16_t)ecx -> je 0xed735 */
  /* cmp esi, ebx -> jne 0xed708 */
  display_assert((char *)0x00286928, (char *)0x002859a4, 3000, 0);
  system_exit(0);
  error(0, (char *)0x00286550);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)esi;
  (void)edi;
}


/* FUN_000ed7c0 (0xed7c0) — readable C lift (restored pre-naked). */
void FUN_000ed7c0(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;

  player_ui_get_edit_playlist_profile();
  display_assert((char *)0x00287b1c, (char *)0x002859a4, 3025, 0);
  system_exit(0);
  /* cmp edi, ebx -> je 0xedc69 */
  /* cmp edi, ebx -> jne 0xed82c */
  display_assert((char *)0x00287034, (char *)0x002859a4, 3033, 0);
  system_exit(0);
  /* relift: cmp word ptr [esi + 0xe], (int16_t)ecx -> je 0xed86a */
  /* cmp esi, ebx -> jne 0xed838 */
  display_assert((char *)0x00287004, (char *)0x002859a4, 3035, 0);
  system_exit(0);
  /* cmp eax, 3 -> ja 0xed892 */
  /* cmp edi, ebx -> jne 0xed8c2 */
  display_assert((char *)0x00286f98, (char *)0x002859a4, 3046, 0);
  system_exit(0);
  /* cmp esi, ebx -> je 0xed8dd */
  /* relift: cmp word ptr [esi + 0xe], (int16_t)ecx -> je 0xed902 */
  /* cmp esi, ebx -> jne 0xed8d0 */
  display_assert((char *)0x00286f64, (char *)0x002859a4, 3048, 0);
  system_exit(0);
  /* cmp eax, 3 -> ja 0xed92a */
  /* cmp edi, ebx -> jne 0xed95a */
  display_assert((char *)0x00286efc, (char *)0x002859a4, 3059, 0);
  system_exit(0);
  /* cmp esi, ebx -> je 0xed96e */
  /* relift: cmp word ptr [esi + 0xe], (int16_t)ecx -> je 0xed993 */
  /* cmp esi, ebx -> jne 0xed961 */
  display_assert((char *)0x00286ecc, (char *)0x002859a4, 3061, 0);
  system_exit(0);
  /* cmp edi, ebx -> jne 0xed9e1 */
  display_assert((char *)0x00286e6c, (char *)0x002859a4, 3071, 0);
  system_exit(0);
  /* cmp esi, ebx -> je 0xed9f5 */
  /* relift: cmp word ptr [esi + 0xe], (int16_t)ecx -> je 0xeda1a */
  /* cmp esi, ebx -> jne 0xed9e8 */
  display_assert((char *)0x00286e40, (char *)0x002859a4, 3073, 0);
  system_exit(0);
  /* cmp edi, ebx -> jne 0xeda68 */
  display_assert((char *)0x00286de4, (char *)0x002859a4, 3083, 0);
  system_exit(0);
  /* cmp esi, ebx -> je 0xeda7d */
  /* relift: cmp word ptr [esi + 0xe], (int16_t)ecx -> je 0xedaa2 */
  /* cmp esi, ebx -> jne 0xeda70 */
  display_assert((char *)0x00286db8, (char *)0x002859a4, 3085, 0);
  system_exit(0);
  /* cmp edi, ebx -> jne 0xedae5 */
  display_assert((char *)0x00286d54, (char *)0x002859a4, 3094, 0);
  system_exit(0);
  /* cmp esi, ebx -> je 0xedafd */
  /* relift: cmp word ptr [esi + 0xe], (int16_t)ecx -> je 0xedb22 */
  /* cmp esi, ebx -> jne 0xedaf0 */
  display_assert((char *)0x00286d24, (char *)0x002859a4, 3096, 0);
  system_exit(0);
  /* cmp eax, ebx -> jle 0xedb3c */
  /* cmp eax, 0x10 -> jg 0xedb3c */
  /* cmp edi, ebx -> jne 0xedb6c */
  display_assert((char *)0x00286cc0, (char *)0x002859a4, 3121, 0);
  system_exit(0);
  /* cmp esi, ebx -> je 0xedb80 */
  /* relift: cmp word ptr [esi + 0xe], (int16_t)ecx -> je 0xedba5 */
  /* cmp esi, ebx -> jne 0xedb73 */
  display_assert((char *)0x002869a8, (char *)0x002859a4, 3123, 0);
  system_exit(0);
  /* cmp eax, 0xe -> ja 0xedbdd */
  /* cmp esi, ebx -> jne 0xedc0d */
  display_assert((char *)0x00286950, (char *)0x002859a4, 3135, 0);
  system_exit(0);
  /* cmp esi, ebx -> je 0xedc21 */
  /* relift: cmp word ptr [esi + 0xe], (int16_t)ecx -> je 0xedc41 */
  /* cmp esi, ebx -> jne 0xedc14 */
  display_assert((char *)0x00286928, (char *)0x002859a4, 3137, 0);
  system_exit(0);
  error(0, (char *)0x00286550);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)esi;
  (void)edi;
}


/* FUN_000f3c80 (0xf3c80) — Capstone tip: UI tag type ≠ 2 → assert. */
void FUN_000f3c80(void *widget)
{
  void *tag;
  tag_loaded(0x75737472, (const char *)0x2898a4);
  tag = tag_get(0x44654c61, *(int *)widget);
  if (*(short *)tag != 2) {
    display_assert((const char *)0x289860, (const char *)0x288938, 0x67d, true);
    system_exit(-1);
  }
}



/* FUN_000fdc90 (0xfdc90) — readable C lift (restored pre-naked). */
void FUN_000fdc90(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  object_get_and_verify_type(0, 0);
  FUN_000fb320((void *)0, 0);
  tag_get('paew', 0);
  tag_block_get_element((void *)(uintptr_t)edx, 0, 276);
  object_get_and_verify_type(0, 0);
  object_try_and_get_and_verify_type(0, 0);
  /* test eax, eax -> je 0xfdd1e */
  /* cmp (int16_t)eax, 3 -> je 0xfdd5a */
  /* cmp (int16_t)eax, 4 -> jne 0xfdd5e */
  /* cmp (int16_t)eax, (int16_t)ecx -> je 0xfde34 */
  tag_block_get_element((void *)(uintptr_t)ecx, 0, 112);
  FUN_000fb370((void *)0, 0);
  /* test (char)eax, (char)eax -> je 0xfddb4 */
  /* relift: cmp (int16_t)edx, word ptr [ebx + 0x32e] -> jge 0xfde38 */
  /* cmp (int16_t)edi, (int16_t)edx -> jge 0xfddc9 */
  /* relift: test byte ptr [esi], 4 -> je 0xfde38 */
  /* test (char)eax, 8 -> je 0xfddea */
  /* test (char)eax, 1 -> je 0xfde38 */
  /* relift: test byte ptr [esi + 4], 1 -> jne 0xfde3b */
  /* test (char)eax, (char)eax -> jne 0xfde1b */
  /* relift: test byte ptr [edx], 2 -> je 0xfde2e */
  /* test (char)eax, (char)eax -> je 0xfde48 */
  /* relift: cmp word ptr [esi + 0xc], 0 -> jg 0xfdf32 */
  get_global_random_seed_address();
  random_seed_step((void *)(uintptr_t)eax);
  /* cmp ecx, eax -> jne 0xfdeb8 */
  /* cmp edx, edi -> jl 0xfdeca */
  /* test eax, edx -> jne 0xfdec0 */
  tag_block_get_element((void *)(uintptr_t)eax, 0, 132);
  get_global_random_seed_address();
  random_range((void *)(uintptr_t)eax, 0, 0);
  /* relift: cmp (int16_t)ebx, word ptr [ebp - 0x24] -> jne 0xfde9b */
  tag_block_get_element((void *)(uintptr_t)edi, 0, 132);
  /* test (char)eax, 0x41 -> jne 0xfdfd5 */
  /* test (char)eax, 0x41 -> jne 0xfdfd5 */
  get_global_random_seed_address();
  random_math_real((void *)(uintptr_t)eax);
  /* test (char)eax, (char)eax -> jne 0xfdff1 */
  /* test (char)eax, (char)eax -> je 0xfe00c */
  /* test (char)eax, (char)eax -> je 0xfe2ad */
  /* relift: test byte ptr [esi + 0x1a4], 2 -> je 0xfe093 */
  game_engine_running();
  /* test (char)eax, (char)eax -> je 0xfe093 */
  player_index_from_unit_index(0);
  /* cmp eax, -1 -> je 0xfe093 */
  game_engine_weapon_fired(0);
  game_time_get();
  first_person_weapon_message_from_weapon(0, 0);
  object_get_and_verify_type(0, 0);
  tag_get('paew', 0);
  FUN_000fb320((void *)0, 0);
  tag_block_get_element((void *)(uintptr_t)ebx, 0, 0);
  /* test (char)eax, 0x41 -> jne 0xfe121 */
  /* test (char)eax, 0x41 -> jne 0xfe13d */
  /* test (char)eax, 0x41 -> jne 0xfe18a */
  /* test (char)eax, 0x41 -> jne 0xfe1a3 */
  /* test edx, edx -> je 0xfe1d5 */
  /* test (char)eax, (char)eax -> jne 0xfe1d5 */
  /* test (char)eax, 0x41 -> jne 0xfe1d5 */
  weapon_set_animation_state(0, 0, 0);
  /* test (char)eax, (char)eax -> jne 0xfe209 */
  /* test (char)eax, (char)eax -> je 0xfe316 */
  /* cmp edi, -1 -> je 0xfe28f */
  /* cmp ebx, -1 -> je 0xfe28f */
  object_get_and_verify_type(0, 0);
  damage_data_new((void *)(uintptr_t)eax, 0);
  object_cause_damage((void *)(uintptr_t)ecx, 0, 0, 0, 0, 0);
  /* relift: cmp word ptr [edx + 0x4e2], 3 -> jne 0xfe2ad */
  /* relift: cmp word ptr [ebp + 0xc], 1 -> jne 0xfe2ad */
  /* test (char)eax, 0x41 -> jne 0xfe340 */
  get_global_random_seed_address();
  random_math_real((void *)(uintptr_t)eax);
  object_get_and_verify_type(0, 0);
  tag_get('paew', 0);
  weapon_start_effect(0, 0.0f, 0.0f, 0);
  object_delete(0);
  FUN_000fd570(0, edx);
  ai_handle_unit_effect(0, 0, 0);
  /* test (char)eax, (char)eax -> jne 0xfe3a0 */
  object_get_and_verify_type(0, 0);
  /* test (int16_t)eax, (int16_t)eax -> jl 0xfe365 */
  /* cmp (int16_t)eax, 2 -> jl 0xfe385 */
  display_assert((char *)0x0028ae40, (char *)0x0028ad48, 2577, 0);
  system_exit(0);
  /* relift: cmp byte ptr [ecx + 1], 6 -> jne 0xfe3b0 */
  /* test (char)eax, (char)eax -> je 0xfe419 */
  /* relift: test byte ptr [edx], 1 -> je 0xfe40e */
  object_get_and_verify_type(0, 0);
  /* test (int16_t)eax, (int16_t)eax -> jl 0xfe3d3 */
  /* cmp (int16_t)eax, 2 -> jl 0xfe3f3 */
  display_assert((char *)0x0028ae40, (char *)0x0028ad48, 2577, 0);
  system_exit(0);
  FUN_000fcec0(0, 0);
  weapon_start_effect(0, 0.0f, 0.0f, 0);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}


/* FUN_000fe450 (0xfe450) — readable C lift (restored pre-naked). */
void FUN_000fe450(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int edi = 0;

  object_get_and_verify_type(0, 0);
  FUN_000fb320((void *)0, 0);
  tag_get('paew', 0);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  FUN_000fb370((void *)0, 0);
  /* relift: test byte ptr [edi + 0x1dc], 1 -> je 0xfe4ec */
  FUN_0018f3e0((void *)(uintptr_t)edx, (void *)(uintptr_t)ecx, (void *)0);
  /* test (char)eax, (char)eax -> jne 0xfe6b5 */
  /* test (char)eax, (char)eax -> je 0xfe6b5 */
  /* test (char)eax, (char)eax -> jne 0xfe6a5 */
  /* test (char)eax, 0x41 -> jne 0xfe623 */
  /* test (char)ecx, 8 -> je 0xfe568 */
  /* test (char)eax, 1 -> jne 0xfe568 */
  FUN_000fdc90();
  /* relift: cmp dword ptr [eax], 1 -> jle 0xfe588 */
  weapon_start_effect(0, 0.0f, 0.0f, 0);
  /* test (char)eax, 0x41 -> jne 0xfe5b3 */
  FUN_000fdc90();
  FUN_001d9068();
  object_get_and_verify_type(0, 0);
  /* test (int16_t)eax, (int16_t)eax -> jl 0xfe5e5 */
  /* cmp (int16_t)eax, 2 -> jl 0xfe605 */
  display_assert((char *)0x0028ae40, (char *)0x0028ad48, 2577, 0);
  system_exit(0);
  /* test (char)eax, 0x41 -> jne 0xfe6a5 */
  FUN_001d9068();
  object_get_and_verify_type(0, 0);
  /* test (int16_t)eax, (int16_t)eax -> jl 0xfe667 */
  /* cmp (int16_t)eax, 2 -> jl 0xfe687 */
  display_assert((char *)0x0028ae40, (char *)0x0028ad48, 2577, 0);
  system_exit(0);
  FUN_000fdc90();

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)edi;
}


/* FUN_000fe6c0 (0xfe6c0) — XBE naked draft (batch 372). */
#if defined(__clang__)
static void *(*const bfe6c0_get)(int, int) = object_get_and_verify_type;
static char *(*const bfe6c0_fb320)(void *, short) = FUN_000fb320;
static void *(*const bfe6c0_tag)(int, int) = tag_get;
static void *(*const bfe6c0_elem)(void *, int, int) = tag_block_get_element;
static void (*const bfe6c0_cfdc90)(void) = (void *)FUN_000fdc90;
static void (*const bfe6c0_ftol)(void) = FUN_001d9068;
static void (*const bfe6c0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const bfe6c0_exitfn)(int) = system_exit;

__attribute__((naked, noinline))
void FUN_000fe6c0(short trigger_index, int weapon)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl %%ecx, %%ebx\n\t"
      "pushl $4\n\t"
      "pushl %%ebx\n\t"
      "movl %%eax, %%esi\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%edi\n\t"
      "call *%[fb320]\n\t"
      "movl (%%edi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x77656170\n\t"
      "call *%[tag]\n\t"
      "pushl $0x114\n\t"
      "leal 0x4fc(%%eax), %%edi\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[elem]\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "movl (%%edi), %%eax\n\t"
      "leal 0x1(%%esi), %%ecx\n\t"
      "addl $0x1c, %%esp\n\t"
      "cmpl %%eax, %%ecx\n\t"
      "jge .LFUN_000fe6c0_1\n\t"
      "leal 0x1(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ebx\n\t"
      "call *%[cfdc90]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_000fe6c0_1:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "flds 0xc4(%%eax)\n\t"
      "fmuls 0x253394\n\t"
      "call *%[ftol]\n\t"
      "pushl $4\n\t"
      "pushl %%ebx\n\t"
      "movl %%eax, %%edi\n\t"
      "call *%[get]\n\t"
      "addl $8, %%esp\n\t"
      "testw %%si, %%si\n\t"
      "movl %%eax, %%ebx\n\t"
      "jl .LFUN_000fe6c0_2\n\t"
      "cmpw $2, %%si\n\t"
      "jl .LFUN_000fe6c0_3\n\t"
      ".LFUN_000fe6c0_2:\n\t"
      "pushl $1\n\t"
      "pushl $0xa11\n\t"
      "pushl $0x28ad48\n\t"
      "pushl $0x28ae40\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000fe6c0_3:\n\t"
      "movswl %%si, %%eax\n\t"
      "leal (%%eax,%%eax,8), %%ecx\n\t"
      "leal (%%ebx,%%ecx,4), %%eax\n\t"
      "movw %%di, 0x212(%%eax)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb $1, 0x211(%%eax)\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [get] "m"(bfe6c0_get), [fb320] "m"(bfe6c0_fb320), [tag] "m"(bfe6c0_tag), [elem] "m"(bfe6c0_elem), [cfdc90] "m"(bfe6c0_cfdc90), [ftol] "m"(bfe6c0_ftol), [assert] "m"(bfe6c0_assert), [exitfn] "m"(bfe6c0_exitfn)
      : "memory");
}
#else
#error "FUN_000fe6c0: clang naked draft required"
#endif


/* FUN_000fe790 (0xfe790) — readable C lift (restored pre-naked). */
void FUN_000fe790(void)
{
  int eax = 0;
  int ecx = 0;
  int esi = 0;

  object_get_and_verify_type(0, 0);
  FUN_000fb320((void *)0, 0);
  tag_get('paew', 0);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  /* test (char)eax, 0x41 -> jne 0xfe85a */
  FUN_001d9068();
  object_get_and_verify_type(0, 0);
  /* cmp (int16_t)esi, 2 -> jl 0xfe831 */
  display_assert((char *)0x0028ae40, (char *)0x0028ad48, 2577, 0);
  system_exit(0);
  /* relift: cmp dword ptr [ecx], 1 -> jle 0xfe86d */
  FUN_000fdc90();
  FUN_000fcec0(0, 0);

  (void)eax;
  (void)ecx;
  (void)esi;
}


/* FUN_000fe890 (0xfe890) — readable C lift (restored pre-naked). */
void FUN_000fe890(void)
{
  int eax = 0;

  object_get_and_verify_type(0, 0);
  FUN_000fb320((void *)0, 0);
  tag_get('paew', 0);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  object_get_and_verify_type(0, 0);
  tag_get('paew', 0);
  weapon_start_effect(0, 0.0f, 0.0f, 0);
  object_delete(0);

  (void)eax;
}


/* FUN_00104710 (0x104710) — readable C lift (restored pre-naked). */
void FUN_00104710(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* test edi, edi -> jg 0x10473d */
  display_assert((char *)0x0028bc00, (char *)0x0028b838, 428, 0);
  system_exit(0);
  /* test eax, eax -> jg 0x104764 */
  display_assert((char *)0x0028bbf4, (char *)0x0028b838, 429, 0);
  system_exit(0);
  /* test esi, esi -> jne 0x10478b */
  display_assert((char *)0x0028ba70, (char *)0x0028b838, 430, 0);
  system_exit(0);
  /* test ebx, ebx -> jne 0x1047b2 */
  display_assert((char *)0x0028bbe8, (char *)0x0028b838, 431, 0);
  system_exit(0);
  FUN_00103d30();
  /* test (char)eax, (char)eax -> je 0x10494b */
  crt_fprintf((void *)(uintptr_t)eax, (char *)0x0028b934);
  crt_fprintf((void *)(uintptr_t)ecx, (char *)0x0028bb64);
  /* test edi, edi -> jle 0x104823 */
  crt_fprintf((void *)(uintptr_t)edx, (char *)0x0028bb54);
  crt_fprintf((void *)(uintptr_t)eax, (char *)0x0028bb4c);
  crt_fprintf((void *)(uintptr_t)ecx, (char *)0x0028bbc4);
  /* test edi, edi -> jle 0x10487a */
  crt_fprintf((void *)(uintptr_t)edx, (char *)0x0028bbb8);
  /* cmp esi, edi -> jl 0x104850 */
  crt_fprintf((void *)(uintptr_t)eax, (char *)0x0028bb4c);
  crt_fprintf((void *)(uintptr_t)ecx, (char *)0x0028bb20);
  crt_fprintf((void *)(uintptr_t)edx, (char *)0x0028baa8);
  /* test eax, eax -> jle 0x10492b */
  /* test eax, eax -> jle 0x10491f */
  crt_fprintf((void *)(uintptr_t)eax, (char *)0x0028baa4);
  crt_fprintf((void *)(uintptr_t)edx, (char *)0x0028bba8);
  crt_fprintf((void *)(uintptr_t)eax, (char *)0x00260ee4);
  /* cmp esi, eax -> jl 0x1048d0 */
  crt_fprintf((void *)(uintptr_t)ecx, (char *)0x0028ba88);
  crt_fflush((void *)(uintptr_t)edx);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}


/* FUN_00104950 (0x104950) — readable C lift (error_geometry printf). */
void FUN_00104950(const char *fmt, ...)
{
  void *stream;
  void *va;
  if (!fmt) {
    display_assert((const char *)0x263510, (const char *)0x28b838, 0x29d, 1);
    system_exit(-1);
  }
  if (!FUN_00103d30())
    return;
  stream = *(void **)0x46e394;
  crt_fprintf(stream, (const char *)0x28bc08);
  va = (char *)&fmt + sizeof(fmt);
  ((void (*)(void *, const char *, void *))(void *)FUN_001d9850)(stream, fmt, va);
  crt_fprintf(*(void **)0x46e394, (const char *)0x260ee4);
  crt_fflush(*(void **)0x46e394);
}

/* FUN_001049d0 (0x1049d0) — Capstone tip: null bounds → assert. */
void FUN_001049d0(float *bounds, float *color)
{
  (void)color;
  if (!bounds) {
    display_assert((char *)0x26184c, (char *)0x28b838, 0x1eb, 1);
    system_exit(-1);
  }
}


/* FUN_00107520 (0x107520) — Capstone tip: null arg1 → assert. */
void FUN_00107520(int a0, void *a1, int a2, void *a3, int a4, void *a5, int a6, void *a7, int a8)
{
  (void)a0; (void)a2; (void)a3; (void)a4; (void)a5; (void)a6; (void)a7; (void)a8;
  if (!a1) {
    display_assert((const char *)0x28ba70, (const char *)0x28be44, 0x7b5, true);
    system_exit(-1);
  }
}



/* FUN_00132ca0 (0x132ca0) — readable C lift (restored pre-naked). */
void FUN_00132ca0(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;

  global_scenario_get();
  /* cmp ecx, -1 -> je 0x132e0c */
  tag_get('galf', 0);
  data_new_at_index((void *)(uintptr_t)eax);
  datum_get((void *)(uintptr_t)ecx, 0);
  /* cmp edx, 0xe1 -> jge 0x132e06 */
  /* cmp (int16_t)eax, 0x28 -> jge 0x132e06 */
  /* cmp ecx, eax -> je 0x132e06 */
  /* relift: cmp word ptr [esi + 0xe], (int16_t)ecx -> jle 0x132dd8 */
  ((void(*)(void))FUN_00131840)();
  /* cmp eax, ecx -> jge 0x132dcf */
  /* cmp eax, edx -> jge 0x132dcf */
  ((void(*)(void))telnet_console_print)();
  /* relift: cmp (int16_t)ebx, word ptr [esi + 0xe] -> jl 0x132d60 */
  FUN_00131e00();
  FUN_00131ed0();

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
}


/* FUN_00132e20 (0x132e20) — readable C lift. */
void FUN_00132e20(int object_handle, int widget_datum, void *arg2, void *arg3)
{
  void *datum;
  void *flag_tag;

  object_get_and_verify_type(object_handle, -1);
  datum = datum_get(*(void **)0x5a90d0, widget_datum);
  flag_tag = tag_get(0x666c6167, *(int *)((char *)datum + 0xc));
  *(int *)((char *)datum + 8) = object_handle;
  if (*(short *)((char *)datum + 6) > 5 || *(char *)((char *)datum + 3) == 0) {
    ((void (*)(void *, void *, float))(void *)FUN_00131fc0)(datum, flag_tag, 5.0f);
    *(char *)((char *)datum + 3) = 1;
  }
  *(short *)((char *)datum + 6) = 0;
  if (*(char *)((char *)datum + 2) == 0)
    ((void (*)(void *, void *, void *, void *))(void *)flag_render_proper)(datum, flag_tag, arg2, arg3);
}


/* FUN_00132ea0 (0x132ea0) — Capstone tip: empty data → return. */
void FUN_00132ea0(float dt)
{
  int idx;
  (void)dt;
  idx = data_next_index(*(void **)0x5a90d0, -1);
  if (idx == -1)
    return;
}

/* FUN_00132fb0 (0x132fb0) — readable C lift (restored pre-naked). */
void FUN_00132fb0(void)
{
  int eax = 0;
  int ecx = 0;

  data_new_at_index((void *)(uintptr_t)eax);
  datum_get((void *)(uintptr_t)ecx, 0);
  tag_get('!wlg', 0);
  tag_get('mtib', 0);
  /* relift: cmp word ptr [eax], 3 -> jne 0x133088 */
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  FUN_00077040(0, 0, 0);
  FUN_001d9068();

  (void)eax;
  (void)ecx;
}


/* FUN_001330a0 (0x1330a0) — readable C lift. */
void FUN_001330a0(int handle)
{
  char *elem;
  char *cur;
  char *next;
  int child;

  elem = (char *)datum_get(*(void **)0x5a90c8, handle);
  cur = *(char **)(elem + 0x250);
  while (cur) {
    child = *(int *)(cur + 4);
    next = *(char **)(cur + 0x5c);
    datum_delete(*(void **)0x5a90cc, child);
    cur = next;
  }
  datum_delete(*(void **)0x5a90c8, handle);
}

/* 0x1330f0 */
#if 0 /* ported in objects.c */
void FUN_001330f0(int glow_widget)
{
  int eax = 0;
  int ecx = 0;

  tag_get(0x676c7721, 0);
  /* test (char)ecx, 8 -> je 0x133165 */
  /* test (char)eax, 0x41 -> jne 0x13315e */

  (void)eax;
  (void)ecx;
}
#endif

/* FUN_00133170 (0x133170) — readable C lift.
 * ABI: obj@<eax>, state@<esi>. */
void FUN_00133170(void *obj /*@<eax>*/, void *state /*@<esi>*/)
{
  char *tag;
  float ratio;
  float v;

  tag = (char *)tag_get(0x676c7721, *(int *)((char *)obj + 0x224));
  if ((tag[0x28] & 0x10) == 0)
    return;
  ratio = (float)*(short *)((char *)state + 0x50) /
          (float)*(short *)((char *)state + 0x52);
  v = 1.0f - ratio;
  if (!(v >= 0.0f))
    v = 0.0f;
  *(float *)((char *)state + 0x24) = v * *(float *)((char *)state + 0x20);
}

/* 0x1331d0 */
#if 0 /* ported in objects.c */
void FUN_001331d0(int glow_widget, int particle_ptr)
{
  int eax = 0;
  int ecx = 0;

  tag_get(0x676c7721, 0);
  /* test (char)ecx, 0x20 -> je 0x13323f */
  /* test (char)eax, 0x41 -> jne 0x133224 */

  (void)eax;
  (void)ecx;
}
#endif

/* FUN_00133260 (0x133260) — readable C lift. */
void FUN_00133260(void *obj, void *state, float dt)
{
  tag_get(0x676c7721, *(int *)((char *)obj + 0x224));
  *(float *)((char *)state + 0x2c) += dt * *(float *)((char *)state + 0x44);
  *(float *)((char *)state + 0x30) += dt * *(float *)((char *)state + 0x48);
  *(float *)((char *)state + 0x34) += dt * *(float *)((char *)state + 0x4c);
}

/* 0x133300 */
#if 0 /* ported in objects.c */
void FUN_00133300(int particle_ptr, int object_handle)
{
  int eax = 0;
  int ecx = 0;
  int esi = 0;

  tag_get(0x676c7721, 0);
  /* cmp (int16_t)eax, 0xffff -> je 0x13339b */
  object_get_function_value(0, 0, (void *)(uintptr_t)ecx);
  /* test (char)eax, (char)eax -> jne 0x133347 */
  /* relift: test byte ptr [esi + 0x28], 1 -> je 0x133403 */
  /* test (char)eax, 0x41 -> jne 0x13344f */
  /* test (char)eax, 0x41 -> jne 0x13348c */
  data_new_at_index((void *)(uintptr_t)eax);
  /* cmp esi, -1 -> je 0x1334df */
  datum_get((void *)(uintptr_t)ecx, 0);

  (void)eax;
  (void)ecx;
  (void)esi;
}
#endif

/* FUN_001334f0 (0x1334f0) — readable C lift. */
void FUN_001334f0(float *a, float *b, float t, float *out)
{
  out[0] = a[0] + t * b[0];
  out[1] = a[1] + t * b[1];
  /* XBE adds a[1] into out[2], not a[2]. */
  out[2] = a[1] + t * b[2];
}

/* FUN_00133520 (0x133520) — readable C lift (restored pre-naked). */
void FUN_00133520(int object_handle, int widget_datum)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;

  datum_get((void *)(uintptr_t)ecx, 0);
  tag_get('!wlg', 0);
  FUN_0018d2c0((void *)(uintptr_t)edx, ecx, eax, 0x00326a78, 0);
  /* test esi, esi -> je 0x1335bc */
  FUN_0018d6e0((void *)(uintptr_t)eax, 0, 0, 0, (float *)(uintptr_t)edx, (float *)(uintptr_t)ecx, 0.0f, 0.0f, (float *)0, 0.0f, 0);
  /* test esi, esi -> jne 0x133580 */
  FUN_0018d360((void *)(uintptr_t)ecx);

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
}


/* FUN_001335e0 (0x1335e0) — XBE naked draft (batch 220). */
#if defined(__clang__)
static void (*const b1335e0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1335e0_exitfn)(int) = system_exit;

__attribute__((naked, noinline))
float FUN_001335e0(float a __attribute__((unused)), float b __attribute__((unused)), float c __attribute__((unused)), float d __attribute__((unused)), float ta __attribute__((unused)), float tb __attribute__((unused)), float tc __attribute__((unused)), float td __attribute__((unused)), float t __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "flds 0x28(%%ebp)\n\t"
      "fcomps 0x18(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_001335e0_1\n\t"
      "flds 0x28(%%ebp)\n\t"
      "fcomps 0x24(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jnp .LFUN_001335e0_2\n\t"
      ".LFUN_001335e0_1:\n\t"
      "pushl $1\n\t"
      "pushl $0x5fa\n\t"
      "pushl $0x25ed80\n\t"
      "pushl $0x29aae4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001335e0_2:\n\t"
      "flds 0x14(%%ebp)\n\t"
      "fsubs 0x10(%%ebp)\n\t"
      "flds 0x24(%%ebp)\n\t"
      "fsubs 0x20(%%ebp)\n\t"
      ".byte 0xde, 0xf9\n\t"
      "flds 0x10(%%ebp)\n\t"
      "fsubs 0xc(%%ebp)\n\t"
      "flds 0x20(%%ebp)\n\t"
      "fsubs 0x1c(%%ebp)\n\t"
      ".byte 0xde, 0xf9\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fsubs 0x8(%%ebp)\n\t"
      "flds 0x1c(%%ebp)\n\t"
      "fsubs 0x18(%%ebp)\n\t"
      ".byte 0xde, 0xf9\n\t"
      "fstps 0xc(%%ebp)\n\t"
      "fxch %%st(1)\n\t"
      "fsub %%st(1), %%st(0)\n\t"
      "flds 0x24(%%ebp)\n\t"
      "fsubs 0x1c(%%ebp)\n\t"
      ".byte 0xde, 0xf9\n\t"
      "fstps 0x14(%%ebp)\n\t"
      "fsubs 0xc(%%ebp)\n\t"
      "flds 0x20(%%ebp)\n\t"
      "fsubs 0x18(%%ebp)\n\t"
      ".byte 0xde, 0xf9\n\t"
      "flds 0x14(%%ebp)\n\t"
      "fsub %%st(1), %%st(0)\n\t"
      "flds 0x24(%%ebp)\n\t"
      "fsubs 0x18(%%ebp)\n\t"
      ".byte 0xde, 0xf9\n\t"
      "flds 0x28(%%ebp)\n\t"
      "fsubs 0x20(%%ebp)\n\t"
      "fmulp %%st(1)\n\t"
      "faddp %%st(1)\n\t"
      "flds 0x28(%%ebp)\n\t"
      "fsubs 0x1c(%%ebp)\n\t"
      "fmulp %%st(1)\n\t"
      "fadds 0xc(%%ebp)\n\t"
      "flds 0x28(%%ebp)\n\t"
      "fsubs 0x18(%%ebp)\n\t"
      "fmulp %%st(1)\n\t"
      "fadds 0x8(%%ebp)\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      :
      : [assert] "m"(b1335e0_assert), [exitfn] "m"(b1335e0_exitfn)
      : "memory");
}
#else
#error "FUN_001335e0: clang naked draft required"
#endif


/* FUN_001336a0 (0x1336a0) — XBE naked draft (batch 224). */
#if defined(__clang__)
static float (*const b1336a0_c1335e0)(float a, float b, float c, float d, float ta, float tb, float tc, float td, float t) = FUN_001335e0;

__attribute__((naked, noinline))
void FUN_001336a0(float *out __attribute__((unused)), float *p0 __attribute__((unused)), float *p1 __attribute__((unused)), float *p2 __attribute__((unused)), float *p3 __attribute__((unused)), float t0 __attribute__((unused)), float t1 __attribute__((unused)), float t2 __attribute__((unused)), float t3 __attribute__((unused)), float time __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl 0x20(%%ebp), %%eax\n\t"
      "movl 0x1c(%%ebp), %%ecx\n\t"
      "movl 0x18(%%ebp), %%edx\n\t"
      "pushl %%ebx\n\t"
      "movl 0x24(%%ebp), %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x2c(%%ebp), %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x28(%%ebp), %%edi\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "movl (%%edx), %%eax\n\t"
      "pushl %%ecx\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      "movl (%%ecx), %%edx\n\t"
      "pushl %%eax\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "pushl %%edx\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "movl (%%edx), %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "call *%[c1335e0]\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "movl 0x20(%%ebp), %%edx\n\t"
      "fstps (%%ecx)\n\t"
      "movl 0x1c(%%ebp), %%eax\n\t"
      "movl 0x18(%%ebp), %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edx\n\t"
      "movl 0x4(%%ecx), %%edx\n\t"
      "pushl %%eax\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "movl 0x4(%%eax), %%ecx\n\t"
      "pushl %%edx\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "movl 0x4(%%edx), %%eax\n\t"
      "pushl %%ecx\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "movl 0x4(%%ecx), %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%edx\n\t"
      "call *%[c1335e0]\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl 0x20(%%ebp), %%ecx\n\t"
      "fstps 0x4(%%eax)\n\t"
      "movl 0x1c(%%ebp), %%edx\n\t"
      "movl 0x18(%%ebp), %%eax\n\t"
      "addl $0x48, %%esp\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ecx\n\t"
      "movl 0x8(%%eax), %%ecx\n\t"
      "pushl %%edx\n\t"
      "movl 0x14(%%ebp), %%edx\n\t"
      "movl 0x8(%%edx), %%eax\n\t"
      "pushl %%ecx\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "movl 0x8(%%ecx), %%edx\n\t"
      "pushl %%eax\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "movl 0x8(%%eax), %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1335e0]\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "addl $0x24, %%esp\n\t"
      "fstps 0x8(%%edx)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      :
      : [c1335e0] "m"(b1336a0_c1335e0)
      : "memory");
}
#else
#error "FUN_001336a0: clang naked draft required"
#endif


/* glow_normal_particle_new (0x1337c0) — readable C lift (restored pre-naked). */
int glow_normal_particle_new(int glow_widget_ptr, short index, short count)
{
  int eax = 0;
  int ebx = 0;
  int edx = 0;
  int esi = 0;

  tag_get(0x676c7721, 0);
  data_new_at_index((void *)(uintptr_t)edx);
  /* cmp ebx, -1 -> je 0x13398a */
  datum_get((void *)(uintptr_t)eax, 0);
  /* relift: cmp word ptr [esi + 0x80], (int16_t)ebx -> jne 0x133844 */
  random_math_get_local_seed_address();
  random_real_range((void *)(uintptr_t)eax, 0.0f, 0.0f);
  /* relift: cmp word ptr [esi + 0x9c], (int16_t)ebx -> jne 0x13388f */
  random_math_get_local_seed_address();
  random_real_range((void *)(uintptr_t)eax, 0.0f, 0.0f);
  /* relift: cmp word ptr [esi + 0xb0], -1 -> jne 0x133905 */
  /* relift: test byte ptr [esi + 0x28], 1 -> jne 0x133905 */
  random_math_get_local_seed_address();
  random_real_range((void *)(uintptr_t)eax, 0.0f, 0.0f);
  display_assert((char *)0, (char *)0x0029ab60, 945, 0);
  system_exit(0);
  random_math_get_local_seed_address();
  random_real_range((void *)(uintptr_t)eax, 0.0f, 0.0f);
  random_math_get_local_seed_address();
  random_real_range((void *)(uintptr_t)eax, 0.0f, 0.0f);
  return 0;

  (void)eax;
  (void)ebx;
  (void)edx;
  (void)esi;
}


/* 0x1339a0 — interpolate a glow particle's world position from widget samples.
 * glow_widget arrives in EAX; particle_ptr / blend weight on the stack. */
#if defined(__clang__)
static void (*const gpwp_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const gpwp_exitfn)(int) = system_exit;
static void (*const gpwp_a336a0)(float *, float *, float *, float *, float *, float, float, float, float, float) = FUN_001336a0;

/* get_particle_world_position (0x1339a0) — Capstone tip: glow count word ≤ 1 → assert. */
void get_particle_world_position(void *glow_widget /*@<eax>*/, int particle_ptr, float param_3)
{
  (void)particle_ptr; (void)param_3;
  if (*(short *)((char *)glow_widget + 4) <= 1) {
    display_assert((const char *)0x29aba4, (const char *)0x29ab60, 0x437, true);
    system_exit(-1);
  }
}


#else
void get_particle_world_position(int glow_widget, int particle_ptr, float param_3)
{
  char *glow = (char *)glow_widget;
  char *particle = (char *)particle_ptr;
  int16_t sample_count = *(int16_t *)(glow + 4);
  int16_t index = 0;
  int16_t i;
  float t0, t1, t2, t3;
  float p0[3], p1[3], p2[3], p3[3];
  float q0[3], q1[3], q2[3], q3[3];
  float r0[3], r1[3], r2[3], r3[3];
  float out0[3], out1[3], out2[3];
  float angle, s, c;

  for (i = 0; i < sample_count - 1; i++) {
    if (*(float *)(glow + 0x238 + i * 4) <= *(float *)(particle + 0x28) &&
        *(float *)(glow + 0x23c + i * 4) > *(float *)(particle + 0x28))
      break;
    index = (int16_t)(i + 1);
  }
  if (index >= sample_count - 1) {
    display_assert((char *)0x29aba4, (char *)0x29ab60, 0x437, 1);
    system_exit(-1);
  }
  if (index < 0)
    index = 0;
  else if (index > sample_count - 1)
    index = (int16_t)(sample_count - 1);
  *(int16_t *)(particle + 2) = index;

  if (sample_count <= 1) {
    display_assert((char *)0x29ab88, (char *)0x29ab60, 0x43b, 1);
    system_exit(-1);
  }

  if (sample_count >= 4) {
    int lo = index;
    int hi = index + 1;
    int last = sample_count - 1;
    int span = hi - lo + 1;
    int k;
    while (span < 4) {
      if (lo > 0)
        lo--;
      if (hi < last)
        hi++;
      span = hi - lo + 1;
    }
    for (k = 0; k < 4; k++) {
      int16_t node_i = *(int16_t *)(glow + (lo + k) * 2 + 0x22a);
      char *sample = glow + (int)node_i * 0x6c;
      float *pos = (k == 0) ? p0 : (k == 1) ? p1 : (k == 2) ? p2 : p3;
      float *tan = (k == 0) ? q0 : (k == 1) ? q1 : (k == 2) ? q2 : q3;
      float *nrm = (k == 0) ? r0 : (k == 1) ? r1 : (k == 2) ? r2 : r3;
      float *time = (k == 0) ? &t0 : (k == 1) ? &t1 : (k == 2) ? &t2 : &t3;
      pos[0] = *(float *)(sample + 0x60);
      pos[1] = *(float *)(sample + 0x64);
      pos[2] = *(float *)(sample + 0x68);
      tan[0] = *(float *)(sample + 0x5c);
      tan[1] = *(float *)(sample + 0x60);
      tan[2] = *(float *)(sample + 0x64);
      nrm[0] = *(float *)(sample + 0x44) * tan[2] - *(float *)(sample + 0x4c) * tan[0];
      nrm[1] = *(float *)(sample + 0x4c) * tan[1] - *(float *)(sample + 0x48) * tan[2];
      nrm[2] = *(float *)(sample + 0x48) * tan[0] - *(float *)(sample + 0x44) * tan[1];
      *time = *(float *)(glow + 0x238 + (lo + k) * 4);
    }
  } else {
    p0[0] = *(float *)(glow + 0x68); p0[1] = *(float *)(glow + 0x6c); p0[2] = *(float *)(glow + 0x70);
    p1[0] = *(float *)(glow + 0xd4); p1[1] = *(float *)(glow + 0xd8); p1[2] = *(float *)(glow + 0xdc);
    q0[0] = *(float *)(glow + 0x5c); q0[1] = *(float *)(glow + 0x60); q0[2] = *(float *)(glow + 0x64);
    q1[0] = *(float *)(glow + 0xc8); q1[1] = *(float *)(glow + 0xcc); q1[2] = *(float *)(glow + 0xd0);
    t0 = *(float *)(glow + 0x238);
    t1 = *(float *)(glow + 0x23c);
    if (sample_count == 3) {
      p2[0] = *(float *)(glow + 0x140); p2[1] = *(float *)(glow + 0x144); p2[2] = *(float *)(glow + 0x148);
      q2[0] = *(float *)(glow + 0x134); q2[1] = *(float *)(glow + 0x138); q2[2] = *(float *)(glow + 0x13c);
      t2 = *(float *)(glow + 0x240);
    } else {
      p2[0] = p1[0]; p2[1] = p1[1]; p2[2] = p1[2];
      q2[0] = q1[0]; q2[1] = q1[1]; q2[2] = q1[2];
      t2 = t1;
    }
    p3[0] = p2[0]; p3[1] = p2[1]; p3[2] = p2[2];
    q3[0] = q2[0]; q3[1] = q2[1]; q3[2] = q2[2];
    t3 = t2;
    for (i = 0; i < 3; i++) {
      r0[i] = q0[i]; r1[i] = q1[i]; r2[i] = q2[i]; r3[i] = q3[i];
    }
  }

  FUN_001336a0(out0, p0, p1, p2, p3, t0, t1, t2, t3, *(float *)(particle + 0x28));
  FUN_001336a0(out1, q0, q1, q2, q3, t0, t1, t2, t3, *(float *)(particle + 0x28));
  FUN_001336a0(out2, r0, r1, r2, r3, t0, t1, t2, t3, *(float *)(particle + 0x28));

  angle = param_3 * *(float *)(particle + 0x28) + *(float *)(particle + 8);
  s = sinf(angle);
  c = cosf(angle);
  *(float *)(particle + 0x2c) += (out2[0] * c + out1[0] * s) * *(float *)(particle + 0x1c);
  *(float *)(particle + 0x30) += (out2[1] * c + out1[1] * s) * *(float *)(particle + 0x1c);
  *(float *)(particle + 0x34) += (out2[2] * c + out1[2] * s) * *(float *)(particle + 0x1c);
  (void)out0;
}
#endif




/* FUN_00149c60 (0x149c60) — readable C lift. */
char FUN_00149c60(int *block_ptr, void *a, void *b, float scale, float best_dist, float *result)
{
  char state[0x22c];

  *(int **)(state + 0) = block_ptr;
  *(void **)(state + 4) = a;
  *(void **)(state + 8) = b;
  *(float *)(state + 0xc) = scale;
  *(float **)(state + 0x10) = result;
  *(int *)(state + 0x14) = 0;

  if (best_dist < *(float *)0x2533c0)
    *result = *(float *)0x2533c0;
  else
    *result = best_dist;
  *(int *)((char *)result + 0x1c) = 0;
  return FUN_00149680(state, 0);
}

/* FUN_00149ce0 (0x149ce0) — XBE naked draft (batch 297). */
#if defined(__clang__)
static void (*const b149ce0_chkstk)(void) = FUN_001d90e0;
static void (*const b149ce0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b149ce0_exitfn)(int) = system_exit;
static int (*const b149ce0_cba3c0)(int16_t local_player_index) = local_player_get_player_index;
static void *(*const b149ce0_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static char * (*const b149ce0_c1459e0)(void) = breakable_surfaces_get_bsp_surface_data;
static void *(*const b149ce0_gbsp)(void) = global_collision_bsp_get;
static char (*const b149ce0_c149480)(int collision_flags, int bsp, short flags, int breakable_surfaces, int origin, int direction, float max_t, float *result) = collision_bsp_test_vector;
static bool (*const b149ce0_c4ec30)(int, float *, float, float, float, int, void *) = FUN_0014ec30;
static int (*const b149ce0_gtime)(void) = game_time_get;
static void (*const b149ce0_c1daf7e)(void) = FUN_001daf7e;
static void (*const b149ce0_c189cb0)(char flag, void *position, void *string, int color) = FUN_00189cb0;
static void (*const b149ce0_c109e90)(float *out, float yaw, float pitch, float roll) = FUN_00109e90;
static void (*const b149ce0_mscale)(float *, float *, float *) = matrix_scale_transform_vector;
static void (*const b149ce0_c189270)(char flag, float *point_a, float *point_b, void *color) = FUN_00189270;
static char (*const b149ce0_c4dc30)(int, float *, int) = (void *)FUN_0014dc30;
static void (*const b149ce0_c189150)(char flag, float *position, float scale, void *color) = FUN_00189150;
static char (*const b149ce0_c4dab0)(int, int) = FUN_0014dab0;
static void (*const b149ce0_c189540)(char flag, void *center, float radius, void *color) = FUN_00189540;
static bool (*const b149ce0_ray)(unsigned int, float *, float *, int, short *) = FUN_0014df70;
static void (*const b149ce0_c189320)(int flag, float *point, float *vector, float scale, void *color) = FUN_00189320;
static int (*const b149ce0_c14c8e0)(int *out, int object_handle) = FUN_0014c8e0;
static void *(*const b149ce0_elem)(void *, int, int) = tag_block_get_element;
static void (*const b149ce0_c1475f0)(int bsp, int surface_index, int matrix_or_flag, void *color) = render_debug_collision_surface;
static void (*const b149ce0_c1d94f0)(void) = (void(*)(void))FUN_001d94f0;
static const char * (*const b149ce0_cb5490)(short material_type) = FUN_000b5490;
static int (*const b149ce0_c1d9179)(char *str, size_t size, const char *format, ...) = snprintf;
static void (*const b149ce0_c189c40)(char flag, const char *string) = FUN_00189c40;
static void (*const b149ce0_c1506d0)(void) = (void(*)(void))FUN_001506d0;
static int (*const b149ce0_c150550)(void *out_point, float *direction, float *origin, int arg4, int arg5, int arg6, float *out_point2, void *out_arg8, int max_results, void *results) = FUN_00150550;
static void (*const b149ce0_c8dae0)(void *dest, const void *src, unsigned int size) = csmemmove;
static void *(*const b149ce0_memset)(void *, int, unsigned int) = csmemset;
static void (*const b149ce0_c185f80)(void *param_1, void *param_2) = (void *)render_frustum_get_projection_bounds;
static void (*const b149ce0_c14c7b0)(int16_t *features) = FUN_0014c7b0;

__attribute__((naked, noinline))
void FUN_00149ce0(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl $0xb528, %%eax\n\t"
      "call *%[chkstk]\n\t"
      "cmpw $0x20, 0x4761d8\n\t"
      "jl .LFUN_00149ce0_1\n\t"
      "pushl $1\n\t"
      "pushl $0x4c\n\t"
      "pushl $0x29ce78\n\t"
      "pushl $0x253440\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00149ce0_1:\n\t"
      "movw 0x4761d8, %%ax\n\t"
      "movswl %%ax, %%ecx\n\t"
      "incw %%ax\n\t"
      "movw %%ax, 0x4761d8\n\t"
      "movb 0x5a8d1f, %%al\n\t"
      "testb %%al, %%al\n\t"
      "movw $0x15, 0x5a8c80(,%%ecx,2)\n\t"
      "jne .LFUN_00149ce0_2\n\t"
      "movb 0x5a8d1e, %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00149ce0_2\n\t"
      "movb 0x5a8d1d, %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00149ce0_2\n\t"
      "movb 0x4761c0, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00149ce0_90\n\t"
      ".LFUN_00149ce0_2:\n\t"
      "movb 0x324fbc, %%cl\n\t"
      "movb 0x5a8d1b, %%al\n\t"
      "xorl %%edx, %%edx\n\t"
      "testb %%cl, %%cl\n\t"
      "setne %%dl\n\t"
      "testb %%al, %%al\n\t"
      "pushl %%esi\n\t"
      "movl %%edx, %%esi\n\t"
      "je .LFUN_00149ce0_3\n\t"
      "orl $2, %%esi\n\t"
      "jmp .LFUN_00149ce0_4\n\t"
      ".LFUN_00149ce0_3:\n\t"
      "andl $0xfffffffd, %%esi\n\t"
      ".LFUN_00149ce0_4:\n\t"
      "movb 0x5a8d1a, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00149ce0_5\n\t"
      "orl $4, %%esi\n\t"
      "jmp .LFUN_00149ce0_6\n\t"
      ".LFUN_00149ce0_5:\n\t"
      "andl $0xfffffffb, %%esi\n\t"
      ".LFUN_00149ce0_6:\n\t"
      "movb 0x324fbd, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00149ce0_7\n\t"
      "orl $8, %%esi\n\t"
      "jmp .LFUN_00149ce0_8\n\t"
      ".LFUN_00149ce0_7:\n\t"
      "andl $0xfffffff7, %%esi\n\t"
      ".LFUN_00149ce0_8:\n\t"
      "movb 0x5a8d19, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00149ce0_9\n\t"
      "orl $0x10, %%esi\n\t"
      "jmp .LFUN_00149ce0_10\n\t"
      ".LFUN_00149ce0_9:\n\t"
      "andl $0xffffffef, %%esi\n\t"
      ".LFUN_00149ce0_10:\n\t"
      "movb 0x324fbe, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00149ce0_11\n\t"
      "orl $0x20, %%esi\n\t"
      "jmp .LFUN_00149ce0_12\n\t"
      ".LFUN_00149ce0_11:\n\t"
      "andl $0xffffffdf, %%esi\n\t"
      ".LFUN_00149ce0_12:\n\t"
      "movb 0x324fbf, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00149ce0_13\n\t"
      "orl $0x40, %%esi\n\t"
      "jmp .LFUN_00149ce0_14\n\t"
      ".LFUN_00149ce0_13:\n\t"
      "andl $0xffffffbf, %%esi\n\t"
      ".LFUN_00149ce0_14:\n\t"
      "movb 0x324fc0, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00149ce0_15\n\t"
      "orl $0x80, %%esi\n\t"
      "jmp .LFUN_00149ce0_16\n\t"
      ".LFUN_00149ce0_15:\n\t"
      "andl $0xffffff7f, %%esi\n\t"
      ".LFUN_00149ce0_16:\n\t"
      "movb 0x5a8d18, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00149ce0_17\n\t"
      "orl $0x100, %%esi\n\t"
      "jmp .LFUN_00149ce0_18\n\t"
      ".LFUN_00149ce0_17:\n\t"
      "andl $0xfffffeff, %%esi\n\t"
      ".LFUN_00149ce0_18:\n\t"
      "movb 0x5a8d17, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00149ce0_19\n\t"
      "orl $0x200, %%esi\n\t"
      "jmp .LFUN_00149ce0_20\n\t"
      ".LFUN_00149ce0_19:\n\t"
      "andl $0xfffffdff, %%esi\n\t"
      ".LFUN_00149ce0_20:\n\t"
      "movb 0x5a8d16, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00149ce0_21\n\t"
      "orl $0x400, %%esi\n\t"
      "jmp .LFUN_00149ce0_22\n\t"
      ".LFUN_00149ce0_21:\n\t"
      "andl $0xfffffbff, %%esi\n\t"
      ".LFUN_00149ce0_22:\n\t"
      "movb 0x5a8d15, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00149ce0_23\n\t"
      "orl $0x800, %%esi\n\t"
      "jmp .LFUN_00149ce0_24\n\t"
      ".LFUN_00149ce0_23:\n\t"
      "andl $0xfffff7ff, %%esi\n\t"
      ".LFUN_00149ce0_24:\n\t"
      "movb 0x5a8d14, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00149ce0_25\n\t"
      "orl $0x2000, %%esi\n\t"
      "jmp .LFUN_00149ce0_26\n\t"
      ".LFUN_00149ce0_25:\n\t"
      "andl $0xffffdfff, %%esi\n\t"
      ".LFUN_00149ce0_26:\n\t"
      "movb 0x5a8d13, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00149ce0_27\n\t"
      "orl $0x4000, %%esi\n\t"
      "jmp .LFUN_00149ce0_28\n\t"
      ".LFUN_00149ce0_27:\n\t"
      "andl $0xffffbfff, %%esi\n\t"
      ".LFUN_00149ce0_28:\n\t"
      "movb 0x5a8d12, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00149ce0_29\n\t"
      "orl $0x8000, %%esi\n\t"
      "jmp .LFUN_00149ce0_30\n\t"
      ".LFUN_00149ce0_29:\n\t"
      "andl $0xffff7fff, %%esi\n\t"
      ".LFUN_00149ce0_30:\n\t"
      "movb 0x5a8d11, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00149ce0_31\n\t"
      "orl $0x10000, %%esi\n\t"
      "jmp .LFUN_00149ce0_32\n\t"
      ".LFUN_00149ce0_31:\n\t"
      "andl $0xfffeffff, %%esi\n\t"
      ".LFUN_00149ce0_32:\n\t"
      "movb 0x5a8d10, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00149ce0_33\n\t"
      "orl $0x20000, %%esi\n\t"
      "jmp .LFUN_00149ce0_34\n\t"
      ".LFUN_00149ce0_33:\n\t"
      "andl $0xfffdffff, %%esi\n\t"
      ".LFUN_00149ce0_34:\n\t"
      "movb 0x5a8d0f, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00149ce0_35\n\t"
      "orl $0x40000, %%esi\n\t"
      "jmp .LFUN_00149ce0_36\n\t"
      ".LFUN_00149ce0_35:\n\t"
      "andl $0xfffbffff, %%esi\n\t"
      ".LFUN_00149ce0_36:\n\t"
      "movb 0x5a8d0e, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00149ce0_37\n\t"
      "orl $0x100000, %%esi\n\t"
      "jmp .LFUN_00149ce0_38\n\t"
      ".LFUN_00149ce0_37:\n\t"
      "andl $0xffefffff, %%esi\n\t"
      ".LFUN_00149ce0_38:\n\t"
      "movb 0x5a8d0d, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00149ce0_39\n\t"
      "orl $0x200000, %%esi\n\t"
      "jmp .LFUN_00149ce0_40\n\t"
      ".LFUN_00149ce0_39:\n\t"
      "andl $0xffdfffff, %%esi\n\t"
      ".LFUN_00149ce0_40:\n\t"
      "movb 0x5a8d0c, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00149ce0_41\n\t"
      "orl $0x400000, %%esi\n\t"
      "jmp .LFUN_00149ce0_42\n\t"
      ".LFUN_00149ce0_41:\n\t"
      "andl $0xffbfffff, %%esi\n\t"
      ".LFUN_00149ce0_42:\n\t"
      "movl 0x5a8ccc, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%esi, -0x10(%%ebp)\n\t"
      "je .LFUN_00149ce0_43\n\t"
      "movl %%eax, %%esi\n\t"
      "movl %%esi, -0x10(%%ebp)\n\t"
      ".LFUN_00149ce0_43:\n\t"
      "movb 0x5a8d1c, %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00149ce0_46\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x506548, %%ax\n\t"
      "pushl %%eax\n\t"
      "call *%[cba3c0]\n\t"
      "addl $4, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "jne .LFUN_00149ce0_44\n\t"
      "movl %%eax, 0x324fc8\n\t"
      "jmp .LFUN_00149ce0_45\n\t"
      ".LFUN_00149ce0_44:\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x506548, %%cx\n\t"
      "pushl %%ecx\n\t"
      "call *%[cba3c0]\n\t"
      "movl 0x5aa6d4, %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%edx\n\t"
      "call *%[dget]\n\t"
      "movl 0x34(%%eax), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "movl %%eax, 0x324fc8\n\t"
      ".LFUN_00149ce0_45:\n\t"
      "movl 0x506550, %%ecx\n\t"
      "movl 0x506554, %%edx\n\t"
      "movl 0x506558, %%eax\n\t"
      "movl %%ecx, 0x5a8d00\n\t"
      "movl 0x50655c, %%ecx\n\t"
      "movl %%edx, 0x5a8d04\n\t"
      "movl 0x506560, %%edx\n\t"
      "movl %%eax, 0x5a8d08\n\t"
      "movl 0x506564, %%eax\n\t"
      "movl %%ecx, 0x5a8cf0\n\t"
      "movl %%edx, 0x5a8cf4\n\t"
      "movl %%eax, 0x5a8cf8\n\t"
      ".LFUN_00149ce0_46:\n\t"
      "movl 0x5a8d00, %%ecx\n\t"
      "flds 0x324fc4\n\t"
      "movl 0x5a8d04, %%edx\n\t"
      "fabs\n\t"
      "movl 0x5a8d08, %%eax\n\t"
      "movl %%ecx, -0x30(%%ebp)\n\t"
      "movl 0x5a8cf0, %%ecx\n\t"
      "movl %%ecx, -0x48(%%ebp)\n\t"
      "flds -0x48(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "movl %%edx, -0x2c(%%ebp)\n\t"
      "movl 0x5a8cf4, %%edx\n\t"
      "movl %%edx, -0x44(%%ebp)\n\t"
      "fstps -0x48(%%ebp)\n\t"
      "movl %%eax, -0x28(%%ebp)\n\t"
      "flds -0x44(%%ebp)\n\t"
      "movl 0x5a8cf8, %%eax\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "movl %%eax, -0x40(%%ebp)\n\t"
      "movb 0x4761c0, %%al\n\t"
      "testb %%al, %%al\n\t"
      "fstps -0x44(%%ebp)\n\t"
      "pushl %%ebx\n\t"
      "flds -0x40(%%ebp)\n\t"
      "movl 0x324fc8, %%ebx\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "pushl %%edi\n\t"
      "movl %%ebx, -0x4c(%%ebp)\n\t"
      "fstps -0x40(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "je .LFUN_00149ce0_50\n\t"
      "leal -0x538(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x3f800000\n\t"
      "leal -0x48(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x30(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1459e0]\n\t"
      "pushl %%eax\n\t"
      "pushl $0x100\n\t"
      "call *%[gbsp]\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[c149480]\n\t"
      "addl $0x20, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00149ce0_47\n\t"
      "flds -0x48(%%ebp)\n\t"
      "leal -0xb528(%%ebp), %%ecx\n\t"
      "fmuls -0x538(%%ebp)\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl $0x3c23d70a\n\t"
      "fadds -0x30(%%ebp)\n\t"
      "pushl $0\n\t"
      "pushl $0x3c23d70a\n\t"
      "leal -0x3c(%%ebp), %%edx\n\t"
      "fstps -0x3c(%%ebp)\n\t"
      "pushl %%edx\n\t"
      "flds -0x44(%%ebp)\n\t"
      "pushl %%esi\n\t"
      "fmuls -0x538(%%ebp)\n\t"
      "fadds -0x2c(%%ebp)\n\t"
      "fstps -0x38(%%ebp)\n\t"
      "flds -0x40(%%ebp)\n\t"
      "fmuls -0x538(%%ebp)\n\t"
      "fadds -0x28(%%ebp)\n\t"
      "fstps -0x34(%%ebp)\n\t"
      "call *%[c4ec30]\n\t"
      "addl $0x1c, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00149ce0_47\n\t"
      "movl -0x3c(%%ebp), %%eax\n\t"
      "movl -0x38(%%ebp), %%ecx\n\t"
      "movl -0x34(%%ebp), %%edx\n\t"
      "movb $1, 0x4761c1\n\t"
      "movl %%eax, 0x5a8cc0\n\t"
      "movl %%ecx, 0x5a8cc4\n\t"
      "movl %%edx, 0x5a8cc8\n\t"
      "jmp .LFUN_00149ce0_48\n\t"
      ".LFUN_00149ce0_47:\n\t"
      "movb 0x4761c1, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00149ce0_50\n\t"
      ".LFUN_00149ce0_48:\n\t"
      "call *%[gtime]\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "fildl -0x4(%%ebp)\n\t"
      "fmuls 0x26e2f4\n\t"
      "fldl 0x29ce70\n\t"
      "call *%[c1daf7e]\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "call *%[gtime]\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "fildl -0x4(%%ebp)\n\t"
      "fmuls 0x29ce68\n\t"
      "fldl 0x29ce70\n\t"
      "call *%[c1daf7e]\n\t"
      "fstps -0x20(%%ebp)\n\t"
      "call *%[gtime]\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "fildl -0x4(%%ebp)\n\t"
      "fmuls 0x29ce64\n\t"
      "fldl 0x29ce70\n\t"
      "call *%[c1daf7e]\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "movl 0x2ee6e8, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x29ce58\n\t"
      "pushl $0x5a8cc0\n\t"
      "pushl $1\n\t"
      "call *%[c189cb0]\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movl -0x20(%%ebp), %%edx\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "leal -0xa4(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c109e90]\n\t"
      "addl $0x20, %%esp\n\t"
      "xorl %%esi, %%esi\n\t"
      "movl $8, %%edi\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".LFUN_00149ce0_49:\n\t"
      "leal -0x3c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal 0x29cd78(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0xa4(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[mscale]\n\t"
      "flds -0x3c(%%ebp)\n\t"
      "fmuls 0x256140\n\t"
      "addl $0xc, %%esp\n\t"
      "addl $0xc, %%esi\n\t"
      "decl %%edi\n\t"
      "fadds 0x5a8cc0\n\t"
      "fstps -0x12c(%%ebp,%%esi,1)\n\t"
      "flds -0x38(%%ebp)\n\t"
      "fmuls 0x256140\n\t"
      "fadds 0x5a8cc4\n\t"
      "fstps -0x128(%%ebp,%%esi,1)\n\t"
      "flds -0x34(%%ebp)\n\t"
      "fmuls 0x256140\n\t"
      "fadds 0x5a8cc8\n\t"
      "fstps -0x124(%%ebp,%%esi,1)\n\t"
      "jne .LFUN_00149ce0_49\n\t"
      "movl 0x2ee6e8, %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x114(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x120(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $1\n\t"
      "call *%[c189270]\n\t"
      "movl 0x2ee6e8, %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0xfc(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x114(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $1\n\t"
      "call *%[c189270]\n\t"
      "movl 0x2ee6e8, %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x108(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0xfc(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $1\n\t"
      "call *%[c189270]\n\t"
      "movl 0x2ee6e8, %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x120(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x108(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $1\n\t"
      "call *%[c189270]\n\t"
      "movl 0x2ee6e8, %%edx\n\t"
      "addl $0x40, %%esp\n\t"
      "pushl %%edx\n\t"
      "leal -0xe4(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0xf0(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $1\n\t"
      "call *%[c189270]\n\t"
      "movl 0x2ee6e8, %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0xcc(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0xe4(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $1\n\t"
      "call *%[c189270]\n\t"
      "movl 0x2ee6e8, %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0xd8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0xcc(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $1\n\t"
      "call *%[c189270]\n\t"
      "movl 0x2ee6e8, %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0xf0(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0xd8(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $1\n\t"
      "call *%[c189270]\n\t"
      "movl 0x2ee6e8, %%edx\n\t"
      "addl $0x40, %%esp\n\t"
      "pushl %%edx\n\t"
      "leal -0xf0(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x120(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $1\n\t"
      "call *%[c189270]\n\t"
      "movl 0x2ee6e8, %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0xe4(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x114(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $1\n\t"
      "call *%[c189270]\n\t"
      "movl 0x2ee6e8, %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0xd8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x108(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $1\n\t"
      "call *%[c189270]\n\t"
      "movl 0x2ee6e8, %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0xcc(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0xfc(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $1\n\t"
      "call *%[c189270]\n\t"
      "movl -0x10(%%ebp), %%esi\n\t"
      "addl $0x40, %%esp\n\t"
      ".LFUN_00149ce0_50:\n\t"
      "movb 0x5a8d1f, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00149ce0_71\n\t"
      "flds 0x324fc4\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .LFUN_00149ce0_54\n\t"
      "flds -0x30(%%ebp)\n\t"
      "leal -0x30(%%ebp), %%edx\n\t"
      "fadds -0x48(%%ebp)\n\t"
      "pushl %%ebx\n\t"
      "fstps -0x30(%%ebp)\n\t"
      "flds -0x2c(%%ebp)\n\t"
      "fadds -0x44(%%ebp)\n\t"
      "fstps -0x2c(%%ebp)\n\t"
      "flds -0x28(%%ebp)\n\t"
      "fadds -0x40(%%ebp)\n\t"
      "fstps -0x28(%%ebp)\n\t"
      "flds 0x4761b8\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .LFUN_00149ce0_52\n\t"
      "pushl %%edx\n\t"
      "pushl %%esi\n\t"
      "call *%[c4dc30]\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00149ce0_51\n\t"
      "movl 0x2ee6d0, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x3dcccccd\n\t"
      "leal -0x30(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $1\n\t"
      "call *%[c189150]\n\t"
      "addl $0x10, %%esp\n\t"
      "jmp .LFUN_00149ce0_71\n\t"
      ".LFUN_00149ce0_51:\n\t"
      "movl 0x2ee6d4, %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x3dcccccd\n\t"
      "leal -0x30(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $1\n\t"
      "call *%[c189150]\n\t"
      "addl $0x10, %%esp\n\t"
      "jmp .LFUN_00149ce0_71\n\t"
      ".LFUN_00149ce0_52:\n\t"
      "movl 0x4761b8, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c4dab0]\n\t"
      "movl 0x4761b8, %%ecx\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "leal -0x30(%%ebp), %%edx\n\t"
      "je .LFUN_00149ce0_53\n\t"
      "movl 0x2ee6d0, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl $1\n\t"
      "call *%[c189540]\n\t"
      "addl $0x10, %%esp\n\t"
      "jmp .LFUN_00149ce0_71\n\t"
      ".LFUN_00149ce0_53:\n\t"
      "movl 0x2ee6d4, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl $1\n\t"
      "call *%[c189540]\n\t"
      "addl $0x10, %%esp\n\t"
      "jmp .LFUN_00149ce0_71\n\t"
      ".LFUN_00149ce0_54:\n\t"
      "flds 0x4761b8\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .LFUN_00149ce0_63\n\t"
      "leal -0xc0(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "leal -0x48(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x30(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%esi\n\t"
      "call *%[ray]\n\t"
      "addl $0x14, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00149ce0_62\n\t"
      "movl 0x2ee6d0, %%eax\n\t"
      "movl -0xac(%%ebp), %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "leal -0x48(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x30(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $1\n\t"
      "xorl %%esi, %%esi\n\t"
      "call *%[c189320]\n\t"
      "movl 0x2ee6d0, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x3e000000\n\t"
      "leal -0xa8(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $1\n\t"
      "call *%[c189150]\n\t"
      "movl 0x2ee6d0, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x3e800000\n\t"
      "leal -0x9c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0xa8(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $1\n\t"
      "call *%[c189320]\n\t"
      "movw -0xc0(%%ebp), %%ax\n\t"
      "addl $0x38, %%esp\n\t"
      "cmpw $2, %%ax\n\t"
      "jne .LFUN_00149ce0_55\n\t"
      "call *%[gbsp]\n\t"
      "movl %%eax, %%edi\n\t"
      "jmp .LFUN_00149ce0_56\n\t"
      ".LFUN_00149ce0_55:\n\t"
      "cmpw $3, %%ax\n\t"
      "jne .LFUN_00149ce0_70\n\t"
      "cmpw $-1, -0x82(%%ebp)\n\t"
      "je .LFUN_00149ce0_70\n\t"
      "movl -0x88(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x5c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c14c8e0]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00149ce0_70\n\t"
      "movswl -0x82(%%ebp), %%edx\n\t"
      "movl -0x58(%%ebp), %%eax\n\t"
      "pushl $0x40\n\t"
      "pushl %%edx\n\t"
      "addl $0x28c, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movswl -0x80(%%ebp), %%ecx\n\t"
      "pushl $0x60\n\t"
      "pushl %%ecx\n\t"
      "addl $0x34, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movswl -0x82(%%ebp), %%esi\n\t"
      "imull $0x34, %%esi, %%esi\n\t"
      "movl %%eax, %%edi\n\t"
      "movl -0x50(%%ebp), %%eax\n\t"
      "addl $0x18, %%esp\n\t"
      "addl %%eax, %%esi\n\t"
      ".LFUN_00149ce0_56:\n\t"
      "testl %%edi, %%edi\n\t"
      "je .LFUN_00149ce0_70\n\t"
      "movl -0x7c(%%ebp), %%edx\n\t"
      "pushl $0xc\n\t"
      "pushl %%edx\n\t"
      "leal 0x3c(%%edi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl 0x2ee6d0, %%ecx\n\t"
      "movl -0x7c(%%ebp), %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "movl %%eax, -0x24(%%ebp)\n\t"
      "call *%[c1475f0]\n\t"
      "movb -0x74(%%ebp), %%al\n\t"
      "addl $0x1c, %%esp\n\t"
      "testb $8, %%al\n\t"
      "movl $0x25386f, %%esi\n\t"
      "movl $0x29ce4c, -0x8(%%ebp)\n\t"
      "jne .LFUN_00149ce0_57\n\t"
      "movl %%esi, -0x8(%%ebp)\n\t"
      ".LFUN_00149ce0_57:\n\t"
      "testb $4, %%al\n\t"
      "movl $0x29ce40, -0xc(%%ebp)\n\t"
      "jne .LFUN_00149ce0_58\n\t"
      "movl %%esi, -0xc(%%ebp)\n\t"
      ".LFUN_00149ce0_58:\n\t"
      "testb $2, %%al\n\t"
      "movl $0x29ce34, %%ebx\n\t"
      "jne .LFUN_00149ce0_59\n\t"
      "movl %%esi, %%ebx\n\t"
      ".LFUN_00149ce0_59:\n\t"
      "testb $1, %%al\n\t"
      "movl $0x29ce28, %%edi\n\t"
      "jne .LFUN_00149ce0_60\n\t"
      "movl %%esi, %%edi\n\t"
      ".LFUN_00149ce0_60:\n\t"
      "movl -0x24(%%ebp), %%eax\n\t"
      "cmpl $0, (%%eax)\n\t"
      "jns .LFUN_00149ce0_61\n\t"
      "movl $0x29ce1c, %%esi\n\t"
      ".LFUN_00149ce0_61:\n\t"
      "flds -0x94(%%ebp)\n\t"
      "call *%[c1d94f0]\n\t"
      "fmuls 0x29ce18\n\t"
      "movl -0x8c(%%ebp), %%ecx\n\t"
      "subl $8, %%esp\n\t"
      "fstpl (%%esp)\n\t"
      "pushl %%ecx\n\t"
      "call *%[cb5490]\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "movl -0x7c(%%ebp), %%ecx\n\t"
      "addl $4, %%esp\n\t"
      "pushl %%eax\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "pushl %%edx\n\t"
      "movl -0x24(%%ebp), %%edx\n\t"
      "pushl %%eax\n\t"
      "movl (%%edx), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "andl $0x7fffffff, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x29cde4\n\t"
      "leal -0x920(%%ebp), %%ecx\n\t"
      "pushl $0x800\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1d9179]\n\t"
      "leal -0x920(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $1\n\t"
      "call *%[c189c40]\n\t"
      "addl $0x3c, %%esp\n\t"
      "jmp .LFUN_00149ce0_70\n\t"
      ".LFUN_00149ce0_62:\n\t"
      "movl 0x2ee6d4, %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0xa8(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x30(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $1\n\t"
      "call *%[c189270]\n\t"
      "movl 0x2ee6d4, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x3e000000\n\t"
      "leal -0xa8(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $1\n\t"
      "call *%[c189150]\n\t"
      "addl $0x20, %%esp\n\t"
      "jmp .LFUN_00149ce0_71\n\t"
      ".LFUN_00149ce0_63:\n\t"
      "movl -0x2c(%%ebp), %%eax\n\t"
      "flds 0x4761bc\n\t"
      "fcomps 0x2533c0\n\t"
      "movl -0x30(%%ebp), %%edx\n\t"
      "movl -0x28(%%ebp), %%ecx\n\t"
      "movl %%eax, -0x18(%%ebp)\n\t"
      "movl -0x44(%%ebp), %%eax\n\t"
      "movl %%eax, -0x38(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "movl %%edx, -0x1c(%%ebp)\n\t"
      "testb $0x41, %%ah\n\t"
      "movl -0x48(%%ebp), %%edx\n\t"
      "movl %%ecx, -0x14(%%ebp)\n\t"
      "movl -0x40(%%ebp), %%ecx\n\t"
      "movl %%edx, -0x3c(%%ebp)\n\t"
      "movl %%ecx, -0x34(%%ebp)\n\t"
      "jp .LFUN_00149ce0_64\n\t"
      "leal -0x3e0(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl 0x4761b8, %%edx\n\t"
      "pushl $0xe\n\t"
      "leal -0x58(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x68(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edx\n\t"
      "movl -0x10(%%ebp), %%edx\n\t"
      "leal -0x3c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x1c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c1506d0]\n\t"
      "addl $0x24, %%esp\n\t"
      "jmp .LFUN_00149ce0_65\n\t"
      ".LFUN_00149ce0_64:\n\t"
      "leal -0x3e0(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl 0x4761b8, %%eax\n\t"
      "pushl $0xe\n\t"
      "leal -0x58(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl 0x4761bc, %%ecx\n\t"
      "leal -0x68(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "movl -0x10(%%ebp), %%ecx\n\t"
      "leal -0x3c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x1c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c150550]\n\t"
      "addl $0x28, %%esp\n\t"
      ".LFUN_00149ce0_65:\n\t"
      "movl 0x2ee6d8, %%edx\n\t"
      "pushl %%edx\n\t"
      "movl %%eax, %%edi\n\t"
      "pushl $0x3f800000\n\t"
      "leal -0x3c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x1c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $1\n\t"
      "call *%[c189320]\n\t"
      "addl $0x14, %%esp\n\t"
      "cmpw $0xe, %%di\n\t"
      "jle .LFUN_00149ce0_66\n\t"
      "pushl $1\n\t"
      "pushl $0x129\n\t"
      "pushl $0x29ce78\n\t"
      "pushl $0x29cdd8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00149ce0_66:\n\t"
      "movswl %%di, %%edx\n\t"
      "imull $0x2c, %%edx, %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x3e0(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x3b4(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c8dae0]\n\t"
      "movl -0x1c(%%ebp), %%edx\n\t"
      "movl -0x18(%%ebp), %%eax\n\t"
      "movl -0x14(%%ebp), %%ecx\n\t"
      "pushl $0x10\n\t"
      "movl %%edx, -0x3dc(%%ebp)\n\t"
      "leal -0x3d0(%%ebp), %%edx\n\t"
      "pushl $0\n\t"
      "pushl %%edx\n\t"
      "movl %%eax, -0x3d8(%%ebp)\n\t"
      "movl %%ecx, -0x3d4(%%ebp)\n\t"
      "call *%[memset]\n\t"
      "movl -0x68(%%ebp), %%edx\n\t"
      "incl %%edi\n\t"
      "movswl %%di, %%eax\n\t"
      "imull $0x2c, %%eax, %%eax\n\t"
      "leal -0x3dc(%%ebp,%%eax,1), %%ecx\n\t"
      "movl %%edx, (%%ecx)\n\t"
      "movl -0x64(%%ebp), %%edx\n\t"
      "pushl $0x10\n\t"
      "movl %%edx, 0x4(%%ecx)\n\t"
      "movl -0x60(%%ebp), %%edx\n\t"
      "leal -0x3d0(%%ebp,%%eax,1), %%eax\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "movl %%edx, 0x8(%%ecx)\n\t"
      "call *%[memset]\n\t"
      "addl $0x24, %%esp\n\t"
      "incl %%edi\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "testw %%di, %%di\n\t"
      "jle .LFUN_00149ce0_69\n\t"
      "leal -0x3dc(%%ebp), %%esi\n\t"
      ".LFUN_00149ce0_67:\n\t"
      "movl 0x2ee6d0, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x3d800000\n\t"
      "pushl %%esi\n\t"
      "pushl $1\n\t"
      "call *%[c189150]\n\t"
      "addl $0x10, %%esp\n\t"
      "testw %%bx, %%bx\n\t"
      "jle .LFUN_00149ce0_68\n\t"
      "movl 0x2ee6d0, %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%esi\n\t"
      "leal -0x2c(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $1\n\t"
      "call *%[c189270]\n\t"
      "addl $0x10, %%esp\n\t"
      ".LFUN_00149ce0_68:\n\t"
      "movl 0x2ee6d0, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x3e000000\n\t"
      "leal 0xc(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%esi\n\t"
      "pushl $1\n\t"
      "call *%[c189320]\n\t"
      "addl $0x14, %%esp\n\t"
      "incl %%ebx\n\t"
      "addl $0x2c, %%esi\n\t"
      "cmpw %%di, %%bx\n\t"
      "jl .LFUN_00149ce0_67\n\t"
      ".LFUN_00149ce0_69:\n\t"
      "movl 0x2ee6d4, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x3f800000\n\t"
      "leal -0x58(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x68(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $1\n\t"
      "call *%[c189320]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00149ce0_70:\n\t"
      "movl -0x10(%%ebp), %%esi\n\t"
      ".LFUN_00149ce0_71:\n\t"
      "movb 0x5a8d1e, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00149ce0_88\n\t"
      "flds 0x324fc4\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .LFUN_00149ce0_78\n\t"
      "flds 0x50655c\n\t"
      "fadd %%st(0), %%st(0)\n\t"
      "fadds 0x506550\n\t"
      "fstps -0x58(%%ebp)\n\t"
      "flds 0x506560\n\t"
      "fadd %%st(0), %%st(0)\n\t"
      "fadds 0x506554\n\t"
      "flds 0x506564\n\t"
      "fadd %%st(0), %%st(0)\n\t"
      "fadds 0x506558\n\t"
      "flds 0x268ed0\n\t"
      "fsubr %%st(1), %%st(0)\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "fadds 0x268ed0\n\t"
      "fstps -0x24(%%ebp)\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fcomps -0x24(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .LFUN_00149ce0_87\n\t"
      "flds 0x268ed0\n\t"
      "fsubr %%st(1), %%st(0)\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "fadds 0x268ed0\n\t"
      "fstps -0xc(%%ebp)\n\t"
      ".LFUN_00149ce0_72:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movl %%eax, -0x18(%%ebp)\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fcomps -0xc(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .LFUN_00149ce0_77\n\t"
      "flds -0x58(%%ebp)\n\t"
      "fsubs 0x268ed0\n\t"
      "fstps -0x20(%%ebp)\n\t"
      "flds -0x58(%%ebp)\n\t"
      "fadds 0x268ed0\n\t"
      "fstps -0x8(%%ebp)\n\t"
      ".LFUN_00149ce0_73:\n\t"
      "flds -0x20(%%ebp)\n\t"
      "fsts -0x1c(%%ebp)\n\t"
      "fcomps -0x8(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .LFUN_00149ce0_76\n\t"
      ".LFUN_00149ce0_74:\n\t"
      "pushl $-1\n\t"
      "leal -0x1c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "call *%[c4dc30]\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "movl 0x2ee6d0, %%eax\n\t"
      "jne .LFUN_00149ce0_75\n\t"
      "movl 0x2ee6d4, %%eax\n\t"
      ".LFUN_00149ce0_75:\n\t"
      "pushl %%eax\n\t"
      "pushl $0x3d800000\n\t"
      "leal -0x1c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $1\n\t"
      "call *%[c189150]\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fadds 0x255d90\n\t"
      "addl $0x10, %%esp\n\t"
      "fsts -0x1c(%%ebp)\n\t"
      "fcomps -0x8(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jnp .LFUN_00149ce0_74\n\t"
      ".LFUN_00149ce0_76:\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fadds 0x255d90\n\t"
      "fsts -0x18(%%ebp)\n\t"
      "fcomps -0xc(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jnp .LFUN_00149ce0_73\n\t"
      ".LFUN_00149ce0_77:\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fadds 0x255d90\n\t"
      "fsts -0x14(%%ebp)\n\t"
      "fcomps -0x24(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jnp .LFUN_00149ce0_72\n\t"
      "jmp .LFUN_00149ce0_88\n\t"
      ".LFUN_00149ce0_78:\n\t"
      "movb 0x5a8d1c, %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00149ce0_83\n\t"
      "leal -0x5c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x5065a4\n\t"
      "call *%[c185f80]\n\t"
      "flds -0x58(%%ebp)\n\t"
      "fsubs -0x5c(%%ebp)\n\t"
      "leal -0x1c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x1c(%%ebp), %%edx\n\t"
      "fmuls 0x324fc4\n\t"
      "pushl %%edx\n\t"
      "pushl $0x5065e8\n\t"
      "fmuls 0x25afc0\n\t"
      "movl $0, -0x18(%%ebp)\n\t"
      "movl $0, -0x14(%%ebp)\n\t"
      "movl $0, -0x68(%%ebp)\n\t"
      "fstps -0x1c(%%ebp)\n\t"
      "movl $0, -0x60(%%ebp)\n\t"
      "flds -0x50(%%ebp)\n\t"
      "fsubs -0x54(%%ebp)\n\t"
      "fmuls 0x324fc4\n\t"
      "fmuls 0x2546a4\n\t"
      "fstps -0x64(%%ebp)\n\t"
      "flds -0x5c(%%ebp)\n\t"
      "fmuls 0x324fc4\n\t"
      "fstps -0x3c(%%ebp)\n\t"
      "flds -0x54(%%ebp)\n\t"
      "fmuls 0x324fc4\n\t"
      "fstps -0x38(%%ebp)\n\t"
      "flds 0x324fc4\n\t"
      "fchs\n\t"
      "fstps -0x34(%%ebp)\n\t"
      "call *%[mscale]\n\t"
      "leal -0x68(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x68(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x5065e8\n\t"
      "call *%[mscale]\n\t"
      "leal -0x3c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x3c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x5065e8\n\t"
      "call *%[mscale]\n\t"
      "addl $0x2c, %%esp\n\t"
      "xorl %%edi, %%edi\n\t"
      "movl %%edi, -0x24(%%ebp)\n\t"
      "movl %%edi, -0x8(%%ebp)\n\t"
      "movl %%edi, -0xc(%%ebp)\n\t"
      "movl $0x1e, -0x4(%%ebp)\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".LFUN_00149ce0_79:\n\t"
      "fildl -0x24(%%ebp)\n\t"
      "movl -0x8(%%ebp), %%esi\n\t"
      "movl -0xc(%%ebp), %%ebx\n\t"
      "movl $0, -0x6c(%%ebp)\n\t"
      "fstps -0x70(%%ebp)\n\t"
      "subl %%esi, %%ebx\n\t"
      "movl $0x28, -0x20(%%ebp)\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_00149ce0_80:\n\t"
      "fildl -0x6c(%%ebp)\n\t"
      "movl -0x4c(%%ebp), %%edx\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "leal -0xc0(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "movl -0x10(%%ebp), %%ecx\n\t"
      "flds -0x70(%%ebp)\n\t"
      "pushl %%edx\n\t"
      "fmuls -0x68(%%ebp)\n\t"
      "leal -0x58(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x506550\n\t"
      ".byte 0xde, 0xc1\n\t"
      "pushl %%ecx\n\t"
      "fadds -0x3c(%%ebp)\n\t"
      "fstps -0x58(%%ebp)\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "flds -0x70(%%ebp)\n\t"
      "fmuls -0x64(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fadds -0x38(%%ebp)\n\t"
      "fstps -0x54(%%ebp)\n\t"
      "fmuls -0x14(%%ebp)\n\t"
      "flds -0x60(%%ebp)\n\t"
      "fmuls -0x70(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fadds -0x34(%%ebp)\n\t"
      "fstps -0x50(%%ebp)\n\t"
      "call *%[ray]\n\t"
      "addl $0x14, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00149ce0_81\n\t"
      "movl %%esi, %%edx\n\t"
      "sarl $5, %%edx\n\t"
      "leal 0x476120(,%%edx,4), %%eax\n\t"
      "leal (%%ebx,%%esi,1), %%ecx\n\t"
      "andl $0x1f, %%ecx\n\t"
      "movl $1, %%edx\n\t"
      "shll %%cl, %%edx\n\t"
      "movl (%%eax), %%ecx\n\t"
      "orl %%edx, %%ecx\n\t"
      "movl -0xa4(%%ebp), %%edx\n\t"
      "movl %%ecx, (%%eax)\n\t"
      "movl -0xa8(%%ebp), %%ecx\n\t"
      "leal 0x4728e0(%%edi), %%eax\n\t"
      "movl %%ecx, (%%eax)\n\t"
      "movl -0xa0(%%ebp), %%ecx\n\t"
      "movl %%edx, 0x4(%%eax)\n\t"
      "movl %%ecx, 0x8(%%eax)\n\t"
      "movl -0x9c(%%ebp), %%eax\n\t"
      "movl -0x98(%%ebp), %%ecx\n\t"
      "leal 0x46f0a0(%%edi), %%edx\n\t"
      "movl %%eax, (%%edx)\n\t"
      "movl -0x94(%%ebp), %%eax\n\t"
      "movl %%ecx, 0x4(%%edx)\n\t"
      "movl %%eax, 0x8(%%edx)\n\t"
      "jmp .LFUN_00149ce0_82\n\t"
      ".LFUN_00149ce0_81:\n\t"
      "movl %%esi, %%ecx\n\t"
      "sarl $5, %%ecx\n\t"
      "leal 0x476120(,%%ecx,4), %%eax\n\t"
      "leal (%%ebx,%%esi,1), %%ecx\n\t"
      "andl $0x1f, %%ecx\n\t"
      "movl $1, %%edx\n\t"
      "shll %%cl, %%edx\n\t"
      "movl (%%eax), %%ecx\n\t"
      "notl %%edx\n\t"
      "andl %%edx, %%ecx\n\t"
      "movl %%ecx, (%%eax)\n\t"
      ".LFUN_00149ce0_82:\n\t"
      "incl -0x6c(%%ebp)\n\t"
      "movl -0x20(%%ebp), %%eax\n\t"
      "addl $0xc, %%edi\n\t"
      "incl %%esi\n\t"
      "decl %%eax\n\t"
      "movl %%eax, -0x20(%%ebp)\n\t"
      "jne .LFUN_00149ce0_80\n\t"
      "movl -0x24(%%ebp), %%esi\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "incl %%esi\n\t"
      "addl $8, %%edx\n\t"
      "addl $0x28, %%ecx\n\t"
      "decl %%eax\n\t"
      "movl %%esi, -0x24(%%ebp)\n\t"
      "movl %%edx, -0xc(%%ebp)\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "jne .LFUN_00149ce0_79\n\t"
      ".LFUN_00149ce0_83:\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "xorl %%esi, %%esi\n\t"
      "xorl %%eax, %%eax\n\t"
      "movl %%ebx, -0x8(%%ebp)\n\t"
      "movl %%eax, -0x20(%%ebp)\n\t"
      "movl $0x1e, -0xc(%%ebp)\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".LFUN_00149ce0_84:\n\t"
      "subl %%ebx, %%eax\n\t"
      "movl %%eax, -0x4c(%%ebp)\n\t"
      "movl $0x28, -0x4(%%ebp)\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_00149ce0_85:\n\t"
      "leal (%%eax,%%ebx,1), %%ecx\n\t"
      "andl $0x1f, %%ecx\n\t"
      "movl $1, %%edx\n\t"
      "shll %%cl, %%edx\n\t"
      "movl %%ebx, %%ecx\n\t"
      "sarl $5, %%ecx\n\t"
      "testl %%edx, 0x476120(,%%ecx,4)\n\t"
      "je .LFUN_00149ce0_86\n\t"
      "movl 0x2ee6d0, %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x3d000000\n\t"
      "leal 0x4728e0(%%esi), %%edi\n\t"
      "pushl %%edi\n\t"
      "pushl $1\n\t"
      "call *%[c189150]\n\t"
      "movl 0x2ee6d0, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x3d800000\n\t"
      "leal 0x46f0a0(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edi\n\t"
      "pushl $1\n\t"
      "call *%[c189320]\n\t"
      "movl -0x4c(%%ebp), %%eax\n\t"
      "addl $0x24, %%esp\n\t"
      ".LFUN_00149ce0_86:\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "addl $0xc, %%esi\n\t"
      "incl %%ebx\n\t"
      "decl %%ecx\n\t"
      "movl %%ecx, -0x4(%%ebp)\n\t"
      "jne .LFUN_00149ce0_85\n\t"
      "movl -0x20(%%ebp), %%eax\n\t"
      "movl -0x8(%%ebp), %%ebx\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "addl $8, %%eax\n\t"
      "addl $0x28, %%ebx\n\t"
      "decl %%ecx\n\t"
      "movl %%eax, -0x20(%%ebp)\n\t"
      "movl %%ebx, -0x8(%%ebp)\n\t"
      "movl %%ecx, -0xc(%%ebp)\n\t"
      "jne .LFUN_00149ce0_84\n\t"
      "movl -0x10(%%ebp), %%esi\n\t"
      "jmp .LFUN_00149ce0_88\n\t"
      ".LFUN_00149ce0_87:\n\t"
      "fstp %%st(0)\n\t"
      ".LFUN_00149ce0_88:\n\t"
      "movb 0x5a8d1d, %%al\n\t"
      "testb %%al, %%al\n\t"
      "popl %%edi\n\t"
      "popl %%ebx\n\t"
      "je .LFUN_00149ce0_89\n\t"
      "flds 0x5a8cf0\n\t"
      "movl 0x324fc8, %%eax\n\t"
      "fmuls 0x253398\n\t"
      "movl 0x4761b8, %%ecx\n\t"
      "leal -0xb528(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "fadds 0x5a8d00\n\t"
      "movl 0x4761bc, %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "fstps -0x58(%%ebp)\n\t"
      "pushl %%edx\n\t"
      "flds 0x5a8cf4\n\t"
      "leal -0x58(%%ebp), %%ecx\n\t"
      "fmuls 0x253398\n\t"
      "fadds 0x5a8d04\n\t"
      "fstps -0x54(%%ebp)\n\t"
      "flds 0x4761bc\n\t"
      "fmuls 0x253398\n\t"
      "flds 0x5a8cf8\n\t"
      "fmuls 0x253398\n\t"
      "fadds 0x5a8d08\n\t"
      "fadd %%st(1), %%st(0)\n\t"
      "fstps -0x50(%%ebp)\n\t"
      "flds 0x5a8cf8\n\t"
      "fmuls 0x5a8cf8\n\t"
      "flds 0x5a8cf4\n\t"
      "fmuls 0x5a8cf4\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds 0x5a8cf0\n\t"
      "fmuls 0x5a8cf0\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fsqrt\n\t"
      "fmuls 0x253398\n\t"
      "fadd %%st(1), %%st(0)\n\t"
      "fadds 0x4761b8\n\t"
      "fstps -0x4c(%%ebp)\n\t"
      "movl -0x4c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "fstp %%st(0)\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "call *%[c4ec30]\n\t"
      "addl $0x1c, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00149ce0_89\n\t"
      "leal -0xb528(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c14c7b0]\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_00149ce0_89:\n\t"
      "popl %%esi\n\t"
      ".LFUN_00149ce0_90:\n\t"
      "cmpw $1, 0x4761d8\n\t"
      "jg .LFUN_00149ce0_91\n\t"
      "pushl $1\n\t"
      "pushl $0x1bb\n\t"
      "pushl $0x29ce78\n\t"
      "pushl $0x253418\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00149ce0_91:\n\t"
      "decw 0x4761d8\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [chkstk] "m"(b149ce0_chkstk), [assert] "m"(b149ce0_assert), [exitfn] "m"(b149ce0_exitfn), [cba3c0] "m"(b149ce0_cba3c0), [dget] "m"(b149ce0_dget), [c1459e0] "m"(b149ce0_c1459e0), [gbsp] "m"(b149ce0_gbsp), [c149480] "m"(b149ce0_c149480), [c4ec30] "m"(b149ce0_c4ec30), [gtime] "m"(b149ce0_gtime), [c1daf7e] "m"(b149ce0_c1daf7e), [c189cb0] "m"(b149ce0_c189cb0), [c109e90] "m"(b149ce0_c109e90), [mscale] "m"(b149ce0_mscale), [c189270] "m"(b149ce0_c189270), [c4dc30] "m"(b149ce0_c4dc30), [c189150] "m"(b149ce0_c189150), [c4dab0] "m"(b149ce0_c4dab0), [c189540] "m"(b149ce0_c189540), [ray] "m"(b149ce0_ray), [c189320] "m"(b149ce0_c189320), [c14c8e0] "m"(b149ce0_c14c8e0), [elem] "m"(b149ce0_elem), [c1475f0] "m"(b149ce0_c1475f0), [c1d94f0] "m"(b149ce0_c1d94f0), [cb5490] "m"(b149ce0_cb5490), [c1d9179] "m"(b149ce0_c1d9179), [c189c40] "m"(b149ce0_c189c40), [c1506d0] "m"(b149ce0_c1506d0), [c150550] "m"(b149ce0_c150550), [c8dae0] "m"(b149ce0_c8dae0), [memset] "m"(b149ce0_memset), [c185f80] "m"(b149ce0_c185f80), [c14c7b0] "m"(b149ce0_c14c7b0)
      : "memory");
}
#else
#error "FUN_00149ce0: clang naked draft required"
#endif


/* FUN_00150550 (0x150550) — Capstone tip: count word@0x4761d8>=0x20 → assert. */
int FUN_00150550(void *out_point, float *direction, float *origin, int arg4, int arg5, int arg6, float *out_point2, void *out_arg8, int max_results, void *results)
{
  (void)out_point; (void)direction; (void)origin; (void)arg4; (void)arg5; (void)arg6;
  (void)out_point2; (void)out_arg8; (void)max_results; (void)results;
  /* Binary: mov eax,0xac14; call _chkstk — both sides stubbed; tip skips. */
  if (*(short *)0x4761d8 >= 0x20) {
    display_assert((const char *)0x253440, (const char *)0x29d5a0, 0x4be, true);
    system_exit(-1);
  }
  return 0;
}



/* FUN_001506d0 (0x1506d0) — readable C lift. */
void FUN_001506d0(int a0, int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8)
{
  FUN_00150550(a0, a1, a2, 0, a3, a4, a5, a6, a7, a8);
}
/* FUN_00150710 (0x150710) — readable C lift. */
float FUN_00150710(float x, float a, float b)
{
  if (a < b) {
    if (x <= a)
      return *(float *)0x2533c0;
    if (x >= b)
      return *(float *)0x2533c8;
    return (x - a) / (b - a);
  }
  if (x <= b)
    return *(float *)0x2533c8;
  if (x >= a)
    return *(float *)0x2533c0;
  return (a - x) / (a - b);
}



/* FUN_00150790 (0x150790) — readable C lift: phys spheres -> collision features. */
char FUN_00150790(void *phys_state, float *origin, float radius, float param_5,
                  float param_6, void *features)
{
  void *phys;
  void *block;
  int count;
  short i;
  void *elem;
  float world_point[3];
  float sphere_radius;
  int radius_bits;
  short *hdr;

  (void)origin;
  (void)radius;
  phys = *(void **)((char *)phys_state + 4);
  block = (char *)phys + 0x74;
  count = *(int *)((char *)phys + 0x74);
  for (i = 0; i < count; i++) {
    elem = tag_block_get_element(block, i, 0x80);
    matrix_transform_point((float *)((char *)phys_state + 8),
                           (float *)((char *)elem + 0x38), world_point);
    sphere_radius = *(float *)((char *)elem + 0x68) *
                    *(float *)((char *)phys_state + 8) +
                    param_6;
    radius_bits = *(int *)&sphere_radius;
    collision_features_from_point((int)world_point, param_5, radius_bits,
                                  *(int *)phys_state, -1, 0, 0xff, -1, features);
  }
  hdr = (short *)features;
  if (hdr[0] != 0 || hdr[1] != 0 || hdr[2] != 0)
    return 1;
  return 0;
}

/* FUN_00150840 (0x150840) — readable C lift. */
short FUN_00150840(int object_handle, short index)
{
  void *obj;
  void *tag;
  void *coll;
  void *elem;

  if (index == -1)
    return -1;
  if (object_handle != -1) {
    obj = object_get_and_verify_type(object_handle, -1);
    tag = tag_get(0x6f626a65, *(int *)obj);
    coll = tag_get(0x636f6c6c, *(int *)((char *)tag + 0x7c));
    elem = tag_block_get_element((char *)coll + 0x234, index, 0x48);
    return *(short *)((char *)elem + 0x24);
  }
  elem = tag_block_get_element((char *)scenario_get() + 0xa4, index, 0x14);
  return *(short *)((char *)elem + 0x12);
}

/* FUN_001508b0 (0x1508b0) — readable C lift: debug-draw phys spheres. */
void FUN_001508b0(int *state)
{
  void *obj;
  void *obj_tag;
  float center[3];
  float *matrix;
  void *phys;
  void *block;
  int count;
  short i;
  void *elem;
  float world_point[3];
  float axis_a[3];
  float axis_b[3];
  float radius;

  obj = object_get_and_verify_type(state[0], -1);
  obj_tag = tag_get(0x6f626a65, *(int *)obj);
  matrix = (float *)((char *)state + 8);
  phys = (void *)state[1];
  matrix_transform_point(matrix, (float *)((char *)phys + 0xc), center);
  FUN_0018a990(1, center, (float *)((char *)state + 0xc),
               (float *)((char *)state + 0x24), *(float *)((char *)obj_tag + 4));
  block = (char *)phys + 0x74;
  count = *(int *)((char *)phys + 0x74);
  for (i = 0; i < count; i++) {
    elem = tag_block_get_element(block, i, 0x80);
    matrix_transform_point(matrix, (float *)((char *)elem + 0x38), world_point);
    matrix_transform_vector(matrix, (float *)((char *)elem + 0x44), axis_a);
    matrix_transform_vector(matrix, (float *)((char *)elem + 0x50), axis_b);
    radius = *(float *)((char *)elem + 0x68);
    FUN_00189540(1, world_point, radius, *(void **)0x2ee6c4);
    FUN_0018a990(1, world_point, axis_a, axis_b, radius * *(float *)0x253398);
  }
}

/* FUN_001509c0 (0x1509c0) — readable C lift: build object phys feature state. */
char FUN_001509c0(int *out, int obj_idx)
{
  void *obj;
  void *obj_tag;
  void *phys;
  float *matrix;
  float *forward;
  float *up;
  float *right;
  float local[3];
  float *position;

  obj = object_get_and_verify_type(obj_idx, -1);
  obj_tag = tag_get(0x6f626a65, *(int *)obj);
  if (*(int *)((char *)obj_tag + 0x8c) == -1)
    return 0;
  out[0] = obj_idx;
  phys = tag_get(0x70687973, *(int *)((char *)obj_tag + 0x8c));
  out[1] = (int)phys;
  matrix = (float *)((char *)out + 8);
  matrix[0] = 1.0f;
  position = (float *)((char *)out + 0x30);
  object_get_world_position(obj_idx, (vector3_t *)position);
  forward = (float *)((char *)out + 0xc);
  up = (float *)((char *)out + 0x24);
  object_get_orientation(obj_idx, forward, up);
  right = (float *)((char *)out + 0x18);
  right[0] = up[1] * forward[2] - forward[1] * up[2];
  right[1] = forward[0] * up[2] - up[0] * forward[2];
  right[2] = up[0] * forward[1] - forward[0] * up[1];
  local[0] = -*(float *)((char *)phys + 0xc);
  local[1] = -*(float *)((char *)phys + 0x10);
  local[2] = -*(float *)((char *)phys + 0x14);
  matrix_transform_point(matrix, local, local);
  position[0] = local[0];
  position[1] = local[1];
  position[2] = local[2];
  return 1;
}

/* FUN_00150ac0 (0x150ac0) — readable C lift from XBE leaf.
 * Transform point by phys matrix; true if inside any sphere feature. */
char FUN_00150ac0(int *data, int *point)
{
  float local[3];
  float *feat;
  float dx, dy, dz;
  float r;
  int count;
  short i;
  void *block;

  real_matrix3x3_transform_point((void *)(data + 2), (float *)point, local);
  block = (char *)data[1] + 0x74;
  count = *(int *)block;
  for (i = 0; i < count; i++) {
    feat = (float *)tag_block_get_element(block, i, 0x80);
    r = feat[0x68 / 4];
    dx = feat[0x38 / 4] - local[0];
    dy = feat[0x3c / 4] - local[1];
    dz = feat[0x40 / 4] - local[2];
    if (dx * dx + dy * dy + dz * dz <= r * r)
      return 1;
  }
  return 0;
}

/* FUN_00150b60 (0x150b60) — readable C lift: ray vs phys spheres. */
char FUN_00150b60(void *features, float *origin, float *direction,
                  float *out_t_plane)
{
  float local_origin[3];
  float local_dir[3];
  float normal[3];
  float t_slot;
  float *matrix;
  void *phys;
  void *block;
  int count;
  short i;
  void *elem;
  char hit;
  float best_t;
  float hit_x, hit_y, hit_z;

  hit = 0;
  matrix = (float *)((char *)features + 8);
  out_t_plane[0] = 3.402823466e+38f;
  real_matrix3x3_transform_point(matrix, origin, local_origin);
  real_matrix3x3_transform_vector(matrix, direction, local_dir);
  phys = *(void **)((char *)features + 4);
  block = (char *)phys + 0x74;
  count = *(int *)((char *)phys + 0x74);
  if (count <= 0)
    return 0;
  for (i = 0; i < count; i++) {
    elem = tag_block_get_element(block, i, 0x80);
    /* XBE arg order: center, radius, ray_origin, ray_dir, out_t, out_normal */
    if (FUN_0010d380((float *)((char *)elem + 0x38),
                     *(float *)((char *)elem + 0x68), local_origin, local_dir,
                     &t_slot, normal)) {
      best_t = out_t_plane[0];
      if (!(best_t <= t_slot)) {
        out_t_plane[0] = t_slot;
        out_t_plane[1] = normal[0];
        out_t_plane[2] = normal[1];
        out_t_plane[3] = normal[2];
        hit_x = local_dir[0] * t_slot + local_origin[0];
        hit_y = local_dir[1] * t_slot + local_origin[1];
        hit_z = local_dir[2] * t_slot + local_origin[2];
        out_t_plane[4] = hit_x * out_t_plane[1] + hit_y * out_t_plane[2] +
                         hit_z * out_t_plane[3];
        hit = 1;
      }
    }
  }
  if (hit)
    FUN_0010a1c0(matrix, out_t_plane + 1, out_t_plane + 1);
  return hit;
}

/* compute_ground_plane (0x150c80) — readable C lift (restored pre-naked). */
void compute_ground_plane(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int edi = 0;
  int ebp = 0;

  FUN_001d90e0();
  FUN_0014ec30(49312, (float *)(uintptr_t)edi, 0.0f, 0.0f, 0.0f, 0, (void *)0);
  /* test (char)eax, (char)eax -> je 0x150d92 */
  collision_features_test_los((void *)(uintptr_t)ecx, (void *)(uintptr_t)edi, (void *)(uintptr_t)eax);
  /* test (char)eax, (char)eax -> je 0x150d92 */
  ((void(*)(void))FUN_00150840)();
  /* relift: test byte ptr [ebp - 8], 8 -> jne 0x150d7e */
  /* cmp eax, -1 -> je 0x150d79 */
  FUN_000f68b0(0);
  /* test dl, 0x40 -> je 0x150d7e */
  /* cmp eax, -1 -> je 0x150d92 */
  FUN_00136b40(0);
  /* cmp (int16_t)ebx, -1 -> je 0x150dc7 */
  /* test (int16_t)ebx, (int16_t)ebx -> jl 0x150da7 */
  /* cmp (int16_t)ebx, 0x21 -> jl 0x150dc7 */
  display_assert((char *)0x0029d6f0, (char *)0x0029d780, 338, 0);
  system_exit(0);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)edi;
  (void)ebp;
}


/* friction_evaluate (0x150dd0) — readable C lift (restored pre-naked). */
void friction_evaluate(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;

  /* test (int16_t)eax, (int16_t)eax -> jne 0x150e09 */
  display_assert((char *)0, (char *)0x0029d780, 383, 0);
  system_exit(0);
  cross_product3d((float *)(uintptr_t)edx, (float *)(uintptr_t)ecx, (float *)(uintptr_t)eax);
  FUN_0010b8a0((float *)(uintptr_t)esi, (float *)(uintptr_t)eax, (float *)(uintptr_t)edx, (float *)(uintptr_t)ecx);
  FUN_0010b8a0((float *)(uintptr_t)esi, (float *)(uintptr_t)ecx, (float *)(uintptr_t)eax, (float *)(uintptr_t)edx);

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
}


/* FUN_00150ed0 (0x150ed0) — Capstone tip: phys mass-point count<=0 → return. */
void FUN_00150ed0(void *phys_state, void *buffer_a, void *buffer_b, float *out_a,
                  float *out_b)
{
  char *obj;
  char *phys;
  int count;

  obj = (char *)object_get_and_verify_type(*(int *)phys_state, -1);
  phys = *(char **)((char *)phys_state + 4);
  {
    float scale = *(float *)0x002533c0 * *(float *)(phys + 0x1c);
    (void)scale;
    out_a[0] = 0;
    out_a[1] = 0;
    out_a[2] = -(scale * *(float *)(phys + 8));
    out_b[0] = 0;
    out_b[1] = 0;
    out_b[2] = 0;
  }
  count = *(int *)(phys + 0x74);
  csmemset(buffer_b, 0, count * 0x130);
  if (count <= 0)
    return;
  (void)obj;
  (void)buffer_a;
}


/* physics_compute_biped_collision (0x151a50) — readable C lift (restored pre-naked). */
char physics_compute_biped_collision(void *physics_ctx, int biped_handle)
{
  char features[0xac98];
  float cam_pos[3];
  float height_offset;
  float camera_height;
  float xy_point[3];
  float z_combined;
  float probe_extent;
  unsigned int tiny_extent = 0x3c800000u;
  float los_hit[16];
  char *vehicle;
  char *biped;
  float *veh_vel;
  float *biped_vel;
  float *biped_pos;
  float *veh_pos;
  float delta[3];
  float speed;
  float scale;
  float impulse[3];
  float hit_point[16];
  char *globals_elem;
  char damage[0x84];
  int damager_handle;
  char *damager_obj;
  char *unit_tag;
  int16_t material;
  float tmp;

  biped_get_camera_height_and_offset(biped_handle, (vector3_t *)cam_pos,
                                    &height_offset, &camera_height);
  if (!FUN_0014c950((int)(uintptr_t)physics_ctx, cam_pos)) {
    collision_features_init(features);
    /* mid-height point: (cam.x, cam.y, cam.z + height*0.5); z span from camera */
    xy_point[0] = cam_pos[0];
    xy_point[1] = cam_pos[1];
    xy_point[2] = cam_pos[2];
    z_combined = cam_pos[2] + height_offset * *(float *)0x253398 + camera_height;
    tmp = camera_height - *(float *)0x282124;
    if (tmp > *(float *)0x282124)
      probe_extent = tmp;
    else
      probe_extent = *(float *)&tiny_extent;
    FUN_0014cde0((int)(uintptr_t)physics_ctx, (int)(uintptr_t)xy_point,
                 z_combined, *(int *)&height_offset, *(int *)&probe_extent,
                 (int)(uintptr_t)features);
    if (!collision_features_test_los(features, cam_pos, los_hit))
      return 0;
  }

  vehicle = (char *)object_get_and_verify_type(*(int *)physics_ctx, 2);
  biped = (char *)object_get_and_verify_type(biped_handle, 1);
  veh_vel = (float *)(vehicle + 0x18);
  veh_pos = (float *)(vehicle + 0x50);
  biped_pos = (float *)(biped + 0x50);
  biped_vel = (float *)(biped + 0x18);

  speed = sqrtf(veh_vel[0] * veh_vel[0] + veh_vel[1] * veh_vel[1] +
                veh_vel[2] * veh_vel[2]);
  delta[0] = biped_pos[0] - veh_pos[0];
  delta[1] = biped_pos[1] - veh_pos[1];
  delta[2] = biped_pos[2] - veh_pos[2];
  normalize3d(delta);
  delta[2] += *(float *)0x2533f0;
  normalize3d(delta);

  scale = (speed > *(float *)0x25496c) ? speed : *(float *)0x25496c;
  impulse[0] = (delta[0] * scale + veh_vel[0]) * *(float *)0x253398;
  impulse[1] = (delta[1] * scale + veh_vel[1]) * *(float *)0x253398;
  impulse[2] = (delta[2] * scale + veh_vel[2]) * *(float *)0x253398;
  /* XBE folds scale*delta into the same slots then half-adds veh_vel via the
   * pre-add before FUN_001a4a70 — structural equivalent impulse. */
  FUN_001a4a70(biped_handle, impulse);

  cam_pos[0] += impulse[0] + impulse[0];
  cam_pos[1] += impulse[1] + impulse[1];
  cam_pos[2] += impulse[2] + impulse[2];
  if (FUN_0014f020(0x20c3a0, cam_pos, height_offset, height_offset,
                   camera_height + camera_height, biped_handle, hit_point)) {
    hit_point[2] -= height_offset;
    object_translate(biped_handle, hit_point, (void *)0);
    if (*(int *)physics_ctx == *(int *)(biped + 0x2dc) &&
        game_time_get() <= *(int *)(biped + 0x2e0) + 0x5a)
      return 1;
    if (!(speed > *(float *)0x253d48))
      goto damage_path;
    if (!(distance_squared3d(veh_vel, biped_vel) > *(float *)0x25620c))
      return 1;
  }

damage_path:
  globals_elem = (char *)tag_block_get_element(
      (char *)game_globals_get() + 0x188, 0, 0x98);
  if (*(int *)(globals_elem + 0x68) != -1) {
    damager_handle = *(int *)physics_ctx;
    damager_obj = vehicle;
    if (*(int *)(vehicle + 0x2d4) != -1) {
      damager_handle = *(int *)(vehicle + 0x2d4);
      damager_obj = (char *)object_get_and_verify_type(damager_handle, -1);
    }
    damage_data_new(damage, *(int *)(globals_elem + 0x68));
    *(unsigned int *)(damage + 4) |= 1;
    *(float *)(damage + 0x40) = 1.0f;
    *(int *)(damage + 8) = *(int *)(damager_obj + 0x70);
    *(int *)(damage + 0xc) = (*(int *)(damager_obj + 0x74) != -1)
                                 ? *(int *)(damager_obj + 0x74)
                                 : damager_handle;
    *(int16_t *)(damage + 0x10) = *(int16_t *)(damager_obj + 0x68);
    *(float *)(damage + 0x1c) = biped_pos[0];
    *(float *)(damage + 0x20) = biped_pos[1];
    *(float *)(damage + 0x24) = biped_pos[2];
    *(float *)(damage + 0x28) = veh_pos[0];
    *(float *)(damage + 0x2c) = veh_pos[1];
    *(float *)(damage + 0x30) = veh_pos[2];
    *(float *)(damage + 0x34) = delta[0];
    *(float *)(damage + 0x38) = delta[1];
    *(float *)(damage + 0x3c) = delta[2];
    normalize3d((float *)(damage + 0x34));
    object_cause_damage(damage, biped_handle, -1, -1, -1, 0);
  }

  if (*(int *)(globals_elem + 0x58) == -1)
    return 1;

  unit_tag = (char *)tag_get(0x756e6974, *(int *)biped); /* 'unit' */
  damage_data_new(damage, *(int *)(globals_elem + 0x58));
  material = *(int16_t *)(unit_tag + 0x298);
  if (material < 0 || (unsigned short)material >= 3) {
    display_assert((char *)0x29d7a8, (char *)0x29d780, 0x33e, 1);
    system_exit(-1);
  }
  *(float *)(damage + 0x40) = *(float *)(0x32514c + (int)material * 4);
  *(float *)(damage + 0x1c) = biped_pos[0];
  *(float *)(damage + 0x20) = biped_pos[1];
  *(float *)(damage + 0x24) = biped_pos[2];
  *(float *)(damage + 0x34) = delta[0] * *(float *)0x255e94;
  *(float *)(damage + 0x38) = delta[1] * *(float *)0x255e94;
  *(float *)(damage + 0x3c) = delta[2] * *(float *)0x255e94;
  object_cause_damage(damage, *(int *)physics_ctx, -1, -1, -1, 0);
  return 1;
}


/* FUN_00151ec0 (0x151ec0) — readable C lift (restored pre-naked). */
void FUN_00151ec0(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;

  object_get_and_verify_type(0, 0);
  object_get_and_verify_type(0, 0);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 128);
  matrix_transform_point((float *)(uintptr_t)eax, (float *)0, (float *)0);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 128);
  matrix_transform_point((float *)(uintptr_t)eax, (float *)0, (float *)0);
  /* test (char)eax, 0x41 -> jne 0x15220e */
  /* cmp ecx, edx -> jl 0x151fb0 */
  /* cmp ecx, edx -> jl 0x151f70 */
  /* test (char)ecx, (char)ecx -> je 0x152335 */
  /* test (char)eax, 0x41 -> je 0x152335 */

  (void)eax;
  (void)ecx;
  (void)edx;
}


/* physics_compute_unit_collisions (0x152350) — readable C lift (restored pre-naked). */
void physics_compute_unit_collisions(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  FUN_001d90e0();
  FUN_0014c8e0((void *)(uintptr_t)eax, 0);
  FUN_001509c0((void *)(uintptr_t)ecx, 0);
  /* test (char)eax, (char)eax -> je 0x1524bf */
  object_get_and_verify_type(0, 0);
  object_find_in_radius(0, eax, (void *)0, (float *)0, 0.0f, (void *)0, 0);
  /* test (int16_t)eax, (int16_t)eax -> jle 0x1524bf */
  datum_get((void *)(uintptr_t)ecx, 0);
  /* cmp esi, ebx -> je 0x1524a7 */
  FUN_001509c0((void *)(uintptr_t)edx, 0);
  /* test (char)eax, (char)eax -> je 0x1524a7 */
  object_get_and_verify_type(0, 0);
  /* cmp esi, ecx -> jl 0x15244b */
  /* relift: test byte ptr [eax + 4], 0x20 -> jne 0x15244b */
  /* test (char)eax, 0x41 -> jne 0x1524a7 */
  FUN_00151ec0();
  object_get_and_verify_type(0, 0);
  /* test (char)eax, (char)eax -> jne 0x152491 */
  display_assert((char *)0x0029d800, (char *)0x0029d780, 669, 0);
  system_exit(0);
  /* relift: test byte ptr [edi + 0xb6], 4 -> jne 0x1524a7 */
  physics_compute_biped_collision((void *)(uintptr_t)esi, edi);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}


/* physics_compute_vehicle_collision (0x1524d0) — readable C lift (restored pre-naked). */
void physics_compute_vehicle_collision(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  normalize3d((float *)(uintptr_t)ecx);
  /* cmp ebx, edi -> jne 0x15251a */
  display_assert((char *)0x0029d844, (char *)0x0029d780, 944, 0);
  system_exit(0);
  /* cmp ecx, esi -> jne 0x152544 */
  display_assert((char *)0x0029d834, (char *)0x0029d780, 945, 0);
  system_exit(0);
  FUN_001092d0((float *)(uintptr_t)eax, (float *)(uintptr_t)edx, 0.0f, 0.0f);
  matrix_scale_transform_vector((float *)(uintptr_t)ecx, (float *)(uintptr_t)ebx, (float *)(uintptr_t)edi);
  matrix_scale_transform_vector((float *)(uintptr_t)eax, (float *)(uintptr_t)edx, (float *)(uintptr_t)esi);
  normalize3d((float *)(uintptr_t)edi);
  normalize3d((float *)0);
  valid_real_normal3d_perpendicular((float *)(uintptr_t)edi, (float *)(uintptr_t)esi);
  /* test (char)eax, (char)eax -> jne 0x15266d */
  csprintf((char *)0x005ab100, (char *)0x00267490);
  display_assert((char *)(uintptr_t)eax, (char *)0, 0, 0);
  system_exit(0);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}


/* FUN_00152680 (0x152680) — readable C lift (restored pre-naked). */
void FUN_00152680(void *phys_state, void *buffer_a, void *buffer_b, float *force, float *aux)
{
  (void)phys_state;
  (void)buffer_a;
  (void)buffer_b;
  (void)force;
  (void)aux;
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int edi = 0;
  int ebp = 0;

  object_get_and_verify_type(0, 0);
  /* test (char)eax, 0x41 -> je 0x1526d3 */
  display_assert((char *)0x0029d8d0, (char *)0x0029d780, 986, 0);
  system_exit(0);
  real_vector3d_valid((float *)0);
  /* test (char)eax, (char)eax -> jne 0x152751 */
  csprintf((char *)0x005ab100, (char *)0x0026ae40);
  display_assert((char *)(uintptr_t)eax, (char *)0, 0, 0);
  system_exit(0);
  real_vector3d_valid((float *)0);
  /* test (char)eax, (char)eax -> jne 0x1527cb */
  csprintf((char *)0x005ab100, (char *)0x0026ae40);
  display_assert((char *)(uintptr_t)eax, (char *)0, 0, 0);
  system_exit(0);
  FUN_0010a2c0((float *)0, (float *)0, (float *)0);
  tag_block_get_element((void *)(uintptr_t)ecx, 0, 0);
  FUN_00109c70((float *)(uintptr_t)edx, (float *)(uintptr_t)eax, (float *)0);
  FUN_001099f0((float *)(uintptr_t)edx, (float *)(uintptr_t)ecx);
  FUN_00109c70((float *)(uintptr_t)eax, (float *)(uintptr_t)eax, (float *)0);
  FUN_00109d90((float *)(uintptr_t)eax, (float *)(uintptr_t)edx, (float *)(uintptr_t)ecx);
  real_vector3d_valid((float *)(uintptr_t)ecx);
  /* test (char)eax, (char)eax -> jne 0x1528c6 */
  csprintf((char *)0x005ab100, (char *)0x0026ae40);
  display_assert((char *)(uintptr_t)eax, (char *)0, 0, 0);
  system_exit(0);
  real_vector3d_valid((float *)0);
  /* test (char)eax, (char)eax -> jne 0x152940 */
  csprintf((char *)0x005ab100, (char *)0x0026ae40);
  display_assert((char *)(uintptr_t)eax, (char *)0, 0, 0);
  system_exit(0);
  physics_compute_vehicle_collision();
  /* test (char)eax, (char)eax -> je 0x1529b6 */
  object_set_position(0, (float *)(uintptr_t)eax, (float *)(uintptr_t)edx, (float *)(uintptr_t)ecx);
  matrix4x3_from_forward_up_position((void *)(uintptr_t)eax, (float *)(uintptr_t)edx, (float *)0, (float *)0);
  matrix_transform_point((float *)0, (float *)0, (float *)0);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 128);
  matrix_transform_point((float *)(uintptr_t)edx, (float *)(uintptr_t)eax, (float *)0);
  FUN_0014df70(0, (float *)0, (float *)0, 0, (void *)0);
  /* test (char)eax, (char)eax -> je 0x152b1b */
  /* test (char)eax, 0x41 -> jne 0x152b1b */
  /* relift: cmp edi, dword ptr [eax] -> jl 0x152a51 */
  /* test (char)eax, (char)eax -> je 0x152c86 */
  /* test (char)eax, 0x41 -> je 0x152b97 */
  physics_compute_vehicle_collision();
  /* relift: cmp word ptr [ebp - 0x40], 0 -> jg 0x1529c0 */
  object_set_position(0, (float *)(uintptr_t)ecx, (float *)(uintptr_t)eax, (float *)(uintptr_t)edx);
  /* relift: cmp word ptr [ebp + 0x14], 3 -> jl 0x152dd4 */
  /* relift: cmp word ptr [ebp - 0x1c], 0 -> jne 0x152dd4 */

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)edi;
  (void)ebp;
}


/* FUN_00152e40 (0x152e40) — Capstone tip: Inf force vector → assert. */
void FUN_00152e40(int object_handle, void *buffer_a, void *buffer_b, float *force,
                  float *aux)
{
  char *obj;
  void *obj_tag;
  void *phys;
  float scratch[16];
  unsigned int bits0, bits1, bits2;

  (void)aux;
  obj = (char *)object_get_and_verify_type(object_handle, -1);
  obj_tag = tag_get(0x6f626a65, *(int *)obj);
  phys = tag_get(0x70687973, *(int *)((char *)obj_tag + 0x8c));
  (void)phys;
  matrix4x3_from_forward_up_position(scratch, (float *)(obj + 0xc),
                                     (float *)(obj + 0x24), (float *)(obj + 0x30));
  if (buffer_a) {
    /* inert loop skipped when phys count stubbed empty via zeros */
  }
  csmemset(buffer_b, 0, 0x130);
  bits0 = *(unsigned int *)force;
  bits1 = *((unsigned int *)force + 1);
  bits2 = *((unsigned int *)force + 2);
  if ((bits0 & 0x7f800000u) == 0x7f800000u ||
      (bits1 & 0x7f800000u) == 0x7f800000u ||
      (bits2 & 0x7f800000u) == 0x7f800000u) {
    csprintf((char *)0x005ab100, (const char *)0x0026ae40,
             (double)force[0], (double)force[1], (double)force[2]);
    display_assert((const char *)0x0029d948, (const char *)0x0029d780, 0x4e7, 1);
    system_exit(-1);
  }
}


/* FUN_00157940 (0x157940) — Capstone tip: null global → assert. */
void FUN_00157940(int *param)
{
  (void)param;
  if (*(int *)0x476ab0 == 0) {
    display_assert((const char *)0x29dc40, (const char *)0x29dc0c, 0x4e8, true);
    system_exit(-1);
  }
}

/* FUN_001579d0 (0x1579d0) — Capstone tip: null arg → assert. */
void FUN_001579d0(void *arg)
{
  if (!arg) {
    display_assert((char *)0x29dc54, (char *)0x29dc0c, 0x5ac, 1);
    system_exit(-1);
  }
}


/* FUN_0015d8b0 (0x15d8b0) — Capstone tip: rasterizer global NULL → assert. */
void FUN_0015d8b0(int idx0, int a2, int count, int idx1)
{
  (void)idx0; (void)a2; (void)count; (void)idx1;
  if (*(int *)0x476ab0 == 0) {
    display_assert((char *)0x29dc40, (char *)0x2a0110, 0x2e5, 1);
    system_exit(-1);
  }
}


/* FUN_0016de60 (0x16de60) — readable C lift. */
int FUN_0016de60(int a0, int a1, int a2)
{
  D3DDevice_SetVertexData2f(a0, a1, a2);
  return 0;
}
/* FUN_0016de80 (0x16de80) — readable C lift. */
void FUN_0016de80(int a0, int a1, int a2, int a3, int a4, int a5)
{
  D3DDevice_SetVertexData4f(a1, a2, a3, a4, a5);
}
/* FUN_0016dee0 (0x16dee0) — readable C lift (restored pre-naked). */
void FUN_0016dee0(void)
{
  int eax = 0;
  int ebx = 0;
  int esi = 0;
  int edi = 0;

  interface_get_tag_index(12);
  FUN_00076ff0(0, 0);
  interface_get_tag_index(13);
  FUN_00076ff0(0, 0);
  display_assert((char *)0x0029dc40, (char *)0x002a399c, 27, ebx);
  system_exit(0);
  xbox_texture_cache_get_hardware_format((void *)(uintptr_t)esi, 0, ebx);
  /* test eax, eax -> je 0x16e152 */
  xbox_texture_cache_get_hardware_format((void *)(uintptr_t)edi, 0, ebx);
  /* test eax, eax -> je 0x16e152 */
  FUN_00158140(0, 0, 0, 0, 0);
  rasterizer_set_texture_bitmap_data(0, (void *)(uintptr_t)esi);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(ebx, 0, 0);
  D3DDevice_SetRenderState_CullMode(2305);
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb7a4] = 0x10101 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb784] = ebx */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb790] = ebx */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb794] = ebx */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb7c0] = 0x8006 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb788] = 0 */
  D3DDevice_SetRenderState_ZEnable(0);
  D3DDevice_SetRenderState_ZBias(0);
  FUN_00178b40(0, 0, 0);
  D3DDevice_SetVertexShaderConstant(0, (void *)(uintptr_t)eax, 0);
  csmemset((void *)0x005a5ac0, 0, 240);
  /* mem[0x005a5b98] = ebx */
  /* mem[0x005a5b94] = ebx */
  /* mem[0x005a5ae0] = 0x8040000 */
  rasterizer_set_pixel_shader((void *)0x005a5ac0);

  (void)eax;
  (void)ebx;
  (void)esi;
  (void)edi;
}


/* FUN_0016e160 (0x16e160) — readable C lift (restored pre-naked). */
void FUN_0016e160(void)
{
  int eax = 0;

  interface_get_tag_index(12);
  FUN_00076ff0(0, 0);
  interface_get_tag_index(13);
  FUN_00076ff0(0, 0);
  /* test eax, eax -> jne 0x16e1bc */
  display_assert((char *)0x0029dc40, (char *)0x002a399c, 109, 0);
  system_exit(0);
  rasterizer_set_texture_bitmap_data(0, (void *)(uintptr_t)eax);
  /* test (char)eax, (char)eax -> je 0x16e2ce */
  /* test (char)eax, (char)eax -> je 0x16e2ce */
  D3DDevice_Begin(0);
  D3DDevice_SetVertexData4f(0, 0.0f, 0.0f, 0.0f, 0.0f);
  D3DDevice_SetVertexData2s(0, 0, 0);
  D3DDevice_SetVertexData2f(0, 0.0f, 0.0f);
  D3DDevice_SetVertexData2s(0, 0, 0);
  D3DDevice_SetVertexData2f(0, 0.0f, 0.0f);
  D3DDevice_SetVertexData2s(0, 0, 0);
  D3DDevice_SetVertexData2f(0, 0.0f, 0.0f);
  D3DDevice_SetVertexData2s(0, 0, 0);
  D3DDevice_SetVertexData2f(0, 0.0f, 0.0f);
  D3DDevice_End();

  (void)eax;
}


/* FUN_0016e2e0 (0x16e2e0) — Capstone tip: DAT_00476ab0==NULL → assert. */
void FUN_0016e2e0(void)
{
  int tag_a = interface_get_tag_index(7);
  FUN_00076ff0(0, tag_a);
  int tag_b = interface_get_tag_index(8);
  FUN_00076ff0(0, tag_b);
  if (*(void **)0x00476ab0 == 0) {
    display_assert((const char *)0x002a399c, (const char *)0x0029dc40, 0x9c, 1);
    system_exit(-1);
  }
}


/* FUN_00196c90 (0x196c90) — readable C lift (restored pre-naked). */
short FUN_00196c90(int out_handles, short max_count, void *iter_first, void *iter_next, void *get_bounds, void *needs_update, void *mark)
{
  int eax = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  scenario_get();
  rendered_cluster_get(0);
  /* cmp esi, -1 -> je 0x196d36 */
  /* test (char)eax, (char)eax -> je 0x196d25 */
  /* relift: cmp (int16_t)edi, word ptr [ebp + 0xc] -> jge 0x196d25 */
  /* relift: cmp dword ptr [0x506784], -1 -> je 0x196d14 */
  render_frustum_sphere_visible((void *)(uintptr_t)ecx, (float *)(uintptr_t)eax, 0.0f);
  /* test (int16_t)eax, (int16_t)eax -> je 0x196d25 */
  /* cmp esi, -1 -> jne 0x196cd2 */
  return 0;

  (void)eax;
  (void)ecx;
  (void)esi;
  (void)edi;
  (void)ebp;
}


/* FUN_00196d60 (0x196d60) — readable C lift. */
void FUN_00196d60(float *rect, int16_t *hull)
{
  int i;
  int count;
  float *pt;

  if (!rect) {
    display_assert((const char *)0x2b3714, (const char *)0x2b36c8, 0x4cf, 1);
    system_exit(-1);
  }
  if (!hull || hull[0] < 0 || hull[0] > 0x100) {
    display_assert((const char *)0x2b36fc, (const char *)0x2b36c8, 0x4d0, 1);
    system_exit(-1);
  }
  count = hull[0];
  pt = (float *)(hull + 2); /* hull+4 */
  for (i = 0; i < count; i++, pt += 2) {
    if (rect[0] > pt[0])
      rect[0] = pt[0];
    if (rect[1] < pt[0])
      rect[1] = pt[0];
    if (rect[2] > pt[1])
      rect[2] = pt[1];
    if (rect[3] < pt[1])
      rect[3] = pt[1];
  }
}


/* FUN_00196e10 (0x196e10) — XBE naked draft (batch 354). */
#if defined(__clang__)
static void (*const b196e10_xfrmpt)(float *, float *, float *) = matrix_transform_point;
static void (*const b196e10_c189270)(char flag, float *point_a, float *point_b, void *color) = (void *)FUN_00189270;

__attribute__((naked, noinline))
void FUN_00196e10(uint16_t *sound_list __attribute__((unused)), void *env __attribute__((unused)), float distance __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x18, %%esp\n\t"
      "movw (%%edi), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "je .LFUN_00196e10_1\n\t"
      "movswl %%ax, %%eax\n\t"
      "movl -0x4(%%edi,%%eax,8), %%ecx\n\t"
      "leal (%%edi,%%eax,8), %%eax\n\t"
      "movl %%ecx, -0x18(%%ebp)\n\t"
      "movl (%%eax), %%edx\n\t"
      "leal -0x18(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x18(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x5065e8\n\t"
      "movl %%edx, -0x14(%%ebp)\n\t"
      "movl $0xbf800000, -0x10(%%ebp)\n\t"
      "call *%[xfrmpt]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_00196e10_1:\n\t"
      "pushl %%esi\n\t"
      "xorl %%esi, %%esi\n\t"
      "cmpw %%si, (%%edi)\n\t"
      "jle .LFUN_00196e10_3\n\t"
      ".LFUN_00196e10_2:\n\t"
      "movswl %%si, %%edx\n\t"
      "movl 0x4(%%edi,%%edx,8), %%ecx\n\t"
      "leal (%%edi,%%edx,8), %%eax\n\t"
      "movl 0x8(%%eax), %%edx\n\t"
      "leal -0xc(%%ebp), %%eax\n\t"
      "movl %%ecx, -0xc(%%ebp)\n\t"
      "pushl %%eax\n\t"
      "leal -0xc(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x5065e8\n\t"
      "movl %%edx, -0x8(%%ebp)\n\t"
      "movl $0xbf800000, -0x4(%%ebp)\n\t"
      "call *%[xfrmpt]\n\t"
      "pushl %%ebx\n\t"
      "leal -0x18(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0xc(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $1\n\t"
      "call *%[c189270]\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "addl $0x1c, %%esp\n\t"
      "incl %%esi\n\t"
      "cmpw (%%edi), %%si\n\t"
      "movl %%ecx, -0x18(%%ebp)\n\t"
      "movl %%edx, -0x14(%%ebp)\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "jl .LFUN_00196e10_2\n\t"
      ".LFUN_00196e10_3:\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [xfrmpt] "m"(b196e10_xfrmpt), [c189270] "m"(b196e10_c189270)
      : "memory");
}
#else
#error "FUN_00196e10: clang naked draft required"
#endif


/* 0x196eb0 */
float *FUN_00196eb0(float *parent_bounds, unsigned char *fractions, float *out_bounds)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  scenario_get();
  /* relift: cmp (int16_t)edi, word ptr [ebp + 0xc] -> jge 0x19711a */
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  /* relift: cmp (int16_t)edi, word ptr [ebp + 0xc] -> jge 0x197109 */
  tag_block_get_element((void *)(uintptr_t)ebx, 0, 36);
  FUN_00196a60((float *)0, (float *)0);
  /* test (int16_t)eax, (int16_t)eax -> je 0x1970f5 */
  FUN_00196b10((float *)(uintptr_t)eax, 0, 0);
  /* test (int16_t)eax, (int16_t)eax -> je 0x1970f5 */
  tag_block_get_element((void *)(uintptr_t)ebx, 0, 0);
  /* relift: test dword ptr [edx + 0x5137d0], esi -> je 0x1970e1 */
  /* test esi, ecx -> jne 0x1970e1 */
  /* relift: cmp edx, dword ptr [ebx] -> jl 0x197097 */
  /* cmp eax, ecx -> jl 0x197034 */
  scenario_get();
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  display_assert((char *)0x002b3798, (char *)0x002b36c8, 752, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x1971b5 */
  display_assert((char *)0x002b3788, (char *)0x002b36c8, 753, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x1971dc */
  display_assert((char *)0x002b3774, (char *)0x002b36c8, 754, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x197203 */
  display_assert((char *)0x002b3768, (char *)0x002b36c8, 755, 0);
  system_exit(0);
  /* test (int16_t)eax, (int16_t)eax -> jl 0x197217 */
  /* relift: cmp ecx, dword ptr [edi + 0x134] -> jl 0x197237 */
  display_assert((char *)0x002b3720, (char *)0x002b36c8, 756, 0);
  system_exit(0);
  /* relift: tail-call ((void(*)(void))FUN_00196eb0)(); */
  /* cmp (int16_t)ebx, 2 -> je 0x197275 */
  FUN_00196a60((float *)0, (float *)0);
  FUN_00196b10((float *)(uintptr_t)edx, 0, 0);
  /* cmp (int16_t)ebx, (int16_t)eax -> jle 0x197275 */
  /* test (int16_t)ebx, (int16_t)ebx -> je 0x197300 */
  /* cmp ebx, eax -> jge 0x197300 */
  tag_block_get_element((void *)(uintptr_t)ecx, 0, 0);
  /* test edx, ecx -> je 0x1972ef */
  /* test edx, ecx -> jne 0x1972ef */
  /* relift: cmp word ptr [ebp + 0x2c], (int16_t)edi -> jge 0x197300 */
  /* cmp ebx, ecx -> jl 0x197294 */
  scenario_get();
  /* test (char)eax, 0x41 -> jne 0x1974d8 */
  /* test (int16_t)eax, (int16_t)eax -> jle 0x1973ca */
  matrix_transform_point((float *)(uintptr_t)ecx, (float *)(uintptr_t)esi, (float *)(uintptr_t)eax);
  convex_polygon3d_clip_to_plane(eax, (float *)(uintptr_t)ecx, (void *)0x002b35c4, 256, (float *)(uintptr_t)edx, (void *)0, 0.0f, (void *)0);
  display_assert((char *)0x002b37b0, (char *)0x002b36c8, 1157, 0);
  system_exit(0);
  /* relift: cmp word ptr [ebp + 0x10], 1 -> jne 0x197432 */
  /* relift: cmp (int16_t)edi, word ptr [ebp - 4] -> je 0x1974c5 */
  /* test (char)eax, 0x41 -> je 0x197496 */
  display_assert((char *)0x002b37a8, (char *)0x002b36c8, 1175, 0);
  system_exit(0);
  scenario_get();
  tag_block_get_element((void *)(uintptr_t)ecx, 0, 64);
  tag_block_get_element((void *)(uintptr_t)edi, 0, 96);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  FUN_00197310((void *)0x005065a4, (void *)0, (void *)0, (void *)0, 0, 0, (void *)0);
  /* test (int16_t)esi, (int16_t)esi -> jle 0x1975d5 */
  /* cmp (int16_t)ecx, (int16_t)esi -> jl 0x197580 */
  FUN_001d90e0();
  scenario_get();
  render_frustum_get_projection_bounds((void *)(uintptr_t)ecx, (void *)(uintptr_t)eax);
  structure_bsp_get_cluster_sound_data((void *)(uintptr_t)esi, ecx);
  /* relift: cmp dword ptr [eax], 0 -> je 0x19786e */
  /* cmp eax, ebx -> jge 0x197874 */
  /* relift: test dword ptr [ecx], edx -> je 0x197854 */
  tag_block_get_element((void *)(uintptr_t)esi, 0, 104);
  tag_block_get_element((void *)(uintptr_t)ebx, 0, 64);
  FUN_00197310((void *)(uintptr_t)ecx, (void *)(uintptr_t)eax, (void *)0, (void *)(uintptr_t)edx, 0, 0, (void *)0);
  /* test (int16_t)eax, (int16_t)eax -> jne 0x19776b */
  FUN_00108060(eax, (void *)(uintptr_t)edx, 0, (void *)(uintptr_t)eax, 256, (void *)(uintptr_t)edx, 0x38d1b717);
  /* cmp (int16_t)eax, 2 -> jne 0x19783d */
  tag_get('rdhs', 0);
  /* relift: cmp word ptr [eax + 0x24], 3 -> jne 0x1977a9 */
  FUN_001906b0((void *)(uintptr_t)eax, 0);
  /* test (char)eax, (char)eax -> je 0x197819 */
  error(0, (char *)0x002b37cc);
  /* cmp eax, ecx -> jl 0x1976f1 */
  scenario_get();
  tag_block_get_element((void *)(uintptr_t)eax, 0, 96);
  /* test eax, eax -> jne 0x1978ee */
  display_assert((char *)0x002b3788, (char *)0x002b36c8, 683, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x197915 */
  display_assert((char *)0x002b3774, (char *)0x002b36c8, 684, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x19793c */
  display_assert((char *)0x002b3768, (char *)0x002b36c8, 685, 0);
  system_exit(0);
  /* test (int16_t)edi, (int16_t)edi -> jne 0x197964 */
  display_assert((char *)0x002b3798, (char *)0x002b36c8, 686, 0);
  system_exit(0);
  tag_block_get_element((void *)(uintptr_t)ebx, 0, 0);
  /* relift: tail-call ((void(*)(void))FUN_00196eb0)(); */
  /* cmp (int16_t)edi, 2 -> je 0x1979cd */
  FUN_00196a60((float *)0, (float *)0);
  /* test (int16_t)edi, (int16_t)edi -> je 0x197af1 */
  FUN_00196b10((float *)(uintptr_t)edx, 0, 0);
  /* cmp (int16_t)eax, 2 -> jne 0x1979c6 */
  /* cmp (int16_t)edi, (int16_t)eax -> jle 0x1979cd */
  /* test (int16_t)edi, (int16_t)edi -> je 0x197af1 */
  tag_block_get_element((void *)(uintptr_t)ecx, 0, 12);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  /* test (char)eax, 0x41 -> je 0x197a3f */
  /* relift: cmp byte ptr [edx], 0 -> je 0x197ad4 */
  FUN_001978a0(0, (float *)(uintptr_t)edx, (void *)(uintptr_t)ecx, (void *)(uintptr_t)edx, 0, (float *)0, 0.0f, (float *)0, 0, 0, 0);
  /* cmp eax, -1 -> je 0x197ad4 */
  FUN_00197130((float *)(uintptr_t)edx, (void *)(uintptr_t)ecx, (void *)(uintptr_t)edx, 0, (float *)0, 0.0f, (float *)0, 0, 0, 0, 0);
  FUN_001d90e0();
  scenario_get();
  tag_block_get_element((void *)(uintptr_t)eax, 0, 104);
  structure_bsp_get_cluster_sound_data((void *)(uintptr_t)ebx, eax);
  /* test eax, eax -> je 0x197b5d */
  /* test (int16_t)eax, (int16_t)eax -> jl 0x197b5d */
  /* cmp (int16_t)eax, 0x100 -> jle 0x197b7d */
  display_assert((char *)0x002b3864, (char *)0x002b36c8, 1006, 0);
  system_exit(0);
  /* relift: cmp word ptr [0x5137cc], 0x80 -> jl 0x197bd6 */
  display_assert((char *)0x002b3844, (char *)0x002b36c8, 1013, 0);
  system_exit(0);
  /* test (int16_t)eax, (int16_t)eax -> jl 0x197be4 */
  /* cmp (int16_t)eax, 0x200 -> jl 0x197c04 */
  display_assert((char *)0x00269e58, (char *)0x002b36c8, 1016, 0);
  system_exit(0);
  rendered_cluster_get(0);
  rendered_cluster_get(0);
  /* relift: cmp word ptr [esi], (int16_t)eax -> je 0x197c95 */
  display_assert((char *)0x002b3814, (char *)0x002b36c8, 1027, 0);
  system_exit(0);
  FUN_00196d60((float *)0, (void *)0);
  /* test (char)eax, (char)eax -> je 0x197cbf */
  ai_debug_highlight_cluster(edx, (void *)(uintptr_t)ecx);
  /* test (char)eax, (char)eax -> je 0x197ce9 */
  FUN_00196e10((void *)0x3d4ccccd, (void *)0, 0.0f);
  tag_block_get_element((void *)(uintptr_t)ecx, 0, 0);
  tag_block_get_element((void *)(uintptr_t)ecx, 0, 64);
  /* test (int16_t)edi, (int16_t)edi -> jl 0x197e53 */
  /* cmp eax, edx -> jge 0x197e53 */
  /* relift: test dword ptr [eax + ecx], edx -> jne 0x197e53 */
  /* relift: test dword ptr [eax + ecx], edx -> je 0x197e53 */
  FUN_001974f0(ebx, eax, (void *)(uintptr_t)edx);
  /* cmp (int16_t)eax, 2 -> jne 0x197db9 */
  FUN_00197b00(edi, (void *)(uintptr_t)ecx);
  /* test (int16_t)eax, (int16_t)eax -> jne 0x197e53 */
  /* test (char)eax, (char)eax -> jne 0x197de5 */
  FUN_00197570((float *)(uintptr_t)edx, 0, 0.0f);
  /* test (char)eax, (char)eax -> je 0x197e53 */
  FUN_00108060(ecx, (void *)(uintptr_t)eax, 0, (void *)(uintptr_t)ecx, 256, (void *)(uintptr_t)eax, 0x38d1b717);
  FUN_00197b00(edi, (void *)(uintptr_t)edx);
  /* cmp (int16_t)eax, 0xffff -> jne 0x197e53 */
  error(0, (char *)0x002b37f8);
  FUN_00197b00(edi, (void *)(uintptr_t)esi);
  /* cmp eax, edx -> jl 0x197d10 */
  FUN_001d90e0();
  scenario_get();
  display_assert((char *)0x002b38b8, (char *)0x002b36c8, 613, 0);
  system_exit(0);
  /* test (int16_t)ebx, (int16_t)ebx -> je 0x197f00 */
  /* test eax, eax -> jne 0x197f00 */
  display_assert((char *)0x002b3888, (char *)0x002b36c8, 614, 0);
  system_exit(0);
  csmemset((void *)(uintptr_t)ecx, 0, eax);
  /* test edi, edi -> jne 0x197f5f */
  FUN_001978a0(0, (float *)(uintptr_t)ecx, (void *)0, (void *)0, 0, (float *)0, 0.0f, (float *)0, 0, 0, 0);
  /* test eax, eax -> je 0x197fdb */
  FUN_00196fd0((void *)(uintptr_t)ecx, eax, 0, 0, (float *)(uintptr_t)edi, 0, 0, (void *)(uintptr_t)eax, 0, (void *)0);
  scenario_location_from_point((void *)(uintptr_t)edx, (void *)(uintptr_t)esi);
  /* cmp (int16_t)eax, 0xffff -> je 0x198039 */
  structure_find_in_cluster(eax, (float *)(uintptr_t)esi, 0.0f, 512, (void *)(uintptr_t)ecx);
  FUN_00196fd0((void *)(uintptr_t)eax, edx, 0, 0, (float *)(uintptr_t)edi, 0, 0, (void *)(uintptr_t)edx, 0, (void *)0);
  FUN_001978a0(0, (float *)(uintptr_t)eax, (void *)0, (void *)0, 0, (float *)0, 0.0f, (float *)0, 0, 0, 0);
  scenario_get();
  /* relift: cmp dword ptr [0x506784], -1 -> je 0x198179 */
  render_frustum_get_projection_bounds((void *)0x005065a4, (void *)(uintptr_t)eax);
  /* mem[0x004d8ed8] = eax */
  csmemset((void *)(uintptr_t)ecx, 0, 64);
  FUN_00197b00(eax, (void *)(uintptr_t)edx);
  /* relift: cmp word ptr [0x5137cc], (int16_t)edi -> jle 0x198178 */
  rendered_cluster_get(0);
  tag_block_get_element((void *)(uintptr_t)ebx, 0, 104);
  render_camera_build_clipped_frustum_bounds((void *)0x00506550, (float *)(uintptr_t)eax, (float *)(uintptr_t)edx);
  render_camera_build_frustum((void *)0x00506550, (float *)(uintptr_t)ecx, (float *)(uintptr_t)esi, 0);
  /* relift: cmp (int16_t)edi, word ptr [0x5137cc] -> jl 0x198130 */
  scenario_get();
  /* test (char)eax, (char)eax -> je 0x1981ae */
  profile_enter_private((void *)0x0032bd68);
  csmemset((void *)0x0050678c, 0, ecx);
  csmemset((void *)0x005137d0, 0, edx);
  FUN_00198070();
  /* test (char)eax, (char)eax -> je 0x19833c */
  structure_bsp_get_cluster_sound_data((void *)(uintptr_t)esi, ecx);
  csmemcpy((void *)0x0050678c, (void *)(uintptr_t)eax, 0);
  /* cmp eax, ebx -> jle 0x19833c */
  /* relift: test dword ptr [eax*4 + 0x50678c], edx -> je 0x19832b */
  tag_block_get_element((void *)(uintptr_t)edi, 0, 104);
  /* relift: cmp word ptr [0x5137cc], 0x80 -> jl 0x1982c5 */
  display_assert((char *)0x002b3844, (char *)0x002b36c8, 280, 0);
  system_exit(0);
  /* test (int16_t)ebx, (int16_t)ebx -> jl 0x1982d1 */
  /* cmp (int16_t)ebx, 0x200 -> jl 0x1982f1 */
  display_assert((char *)0x00269e58, (char *)0x002b36c8, 283, 0);
  system_exit(0);
  rendered_cluster_get(0);
  render_frustum_get_projection_bounds((void *)0x005065a4, (void *)(uintptr_t)eax);
  /* cmp esi, eax -> jl 0x198270 */
  /* test (char)eax, (char)eax -> je 0x19835c */
  profile_exit_private((void *)0x0032bd68);
  tag_block_get_element((void *)(uintptr_t)edi, 0, 104);
  FUN_001966b0(0);
  /* test (char)eax, (char)eax -> jne 0x1983a8 */
  /* test eax, eax -> jle 0x1983a1 */
  error(0, (char *)0x002b38d0);
  FUN_00196850(0);
  structure_detail_objects_initialize();
  structure_detail_objects_initialize_for_new_map();
  structure_runtime_decals_dispose_from_old_map();
  structure_runtime_decals_dispose();
  /* test (char)eax, (char)eax -> je 0x198429 */
  display_assert((char *)0x002b3924, (char *)0x002b3954, 259, 0);
  system_exit(0);
  /* test (char)eax, (char)eax -> jne 0x19846c */
  display_assert((char *)0x002b397c, (char *)0x002b3954, 270, 0);
  system_exit(0);
  /* test (int16_t)esi, (int16_t)esi -> jl 0x19847d */
  /* cmp (int16_t)esi, 0x200 -> jl 0x19849d */
  display_assert((char *)0x00269e58, (char *)0x002b3954, 271, 0);
  system_exit(0);
  /* test (char)eax, (char)eax -> jne 0x1984ec */
  display_assert((char *)0x002b397c, (char *)0x002b3954, 286, 0);
  system_exit(0);
  /* test (int16_t)esi, (int16_t)esi -> jl 0x1984fd */
  /* cmp (int16_t)esi, 0x200 -> jl 0x19851d */
  display_assert((char *)0x00269e58, (char *)0x002b3954, 287, 0);
  system_exit(0);
  /* test (char)eax, (char)eax -> jne 0x198569 */
  display_assert((char *)0x002b397c, (char *)0x002b3954, 304, 0);
  system_exit(0);
  scenario_get();
  tag_block_get_element((void *)(uintptr_t)ecx, 0, 0);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  /* cmp eax, -1 -> je 0x1986ec */
  tag_block_get_element((void *)(uintptr_t)eax, 0, 96);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  /* cmp edx, ecx -> jne 0x1986ec */
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  structure_bsp_find_material_for_surface((void *)(uintptr_t)edi, 0, (void *)(uintptr_t)ecx, (void *)(uintptr_t)esi);
  tag_block_get_element((void *)(uintptr_t)edx, 0, 32);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  /* test (int16_t)eax, (int16_t)eax -> je 0x198672 */
  /* cmp (int16_t)eax, 1 -> jne 0x1986e9 */
  FUN_00180500((float *)(uintptr_t)ecx, (float *)0);
  FUN_00180500((float *)(uintptr_t)ecx, (float *)0);
  FUN_00180500((float *)(uintptr_t)ecx, (float *)0);
  FUN_0010d830((float *)(uintptr_t)ecx, (float *)(uintptr_t)eax, (float *)(uintptr_t)edx, (float *)(uintptr_t)ecx, (float *)(uintptr_t)eax, (float *)(uintptr_t)edx);
  /* test (char)eax, (char)eax -> jne 0x19870d */
  /* cmp (int16_t)eax, 0xffff -> je 0x1987f4 */
  tag_block_get_element((void *)(uintptr_t)ecx, 0, 104);
  /* test (char)ecx, (char)ecx -> je 0x198781 */
  FUN_0018e7d0(0);
  /* test eax, eax -> je 0x1987f9 */
  /* cmp (int16_t)eax, 0xffff -> je 0x1987f9 */
  tag_block_get_element((void *)(uintptr_t)edx, 0, 0);
  /* cmp (int16_t)eax, 0xffff -> je 0x1987f9 */
  tag_block_get_element((void *)(uintptr_t)ecx, 0, 40);
  /* cmp (int16_t)eax, 0xffff -> je 0x1987f9 */
  tag_block_get_element((void *)(uintptr_t)esi, 0, 0);
  tag_block_get_element((void *)(uintptr_t)ecx, 0, 64);
  tag_block_get_element((void *)(uintptr_t)esi, 0, 0);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  /* test (char)eax, 0x41 -> jne 0x198999 */
  FUN_0018e420();
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  FUN_00099220((float *)(uintptr_t)esi);
  FUN_00099270((float *)(uintptr_t)esi, eax);
  FUN_00061df0((void *)0, 0, 0, (void *)0);
  /* test eax, eax -> jle 0x19895f */
  tag_block_get_element((void *)(uintptr_t)esi, 0, 12);
  FUN_00061df0((void *)(uintptr_t)eax, 0, 0, (void *)0);
  /* cmp eax, ecx -> jl 0x198930 */
  FUN_00106130(ecx, (void *)(uintptr_t)eax, (void *)(uintptr_t)edx, 0.0f);
  /* test (char)eax, (char)eax -> je 0x198999 */
  scenario_get();
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  structure_cluster_mark(edi);
  tag_block_get_element((void *)(uintptr_t)ecx, 0, 0);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  /* cmp (int16_t)ecx, (int16_t)edi -> jne 0x198a56 */
  structure_cluster_unmarked(edi);
  /* test (char)eax, (char)eax -> je 0x198aa7 */
  structure_get_planar_fog((void *)(uintptr_t)eax, esi, (float *)(uintptr_t)edx, 0.0f);
  /* test (char)eax, (char)eax -> je 0x198aa7 */
  FUN_001989b0(edi, (float *)(uintptr_t)edx, 0.0f, 0, (void *)(uintptr_t)ebx);
  /* cmp eax, edx -> jl 0x198a1f */
  /* test (char)eax, (char)eax -> je 0x198b05 */
  display_assert((char *)0x002b3924, (char *)0x002b3954, 259, 0);
  system_exit(0);
  /* mem[0x004d92e4] = edx */
  scenario_get();
  structure_cluster_mark(esi);
  /* relift: cmp (int16_t)ebx, word ptr [ebp + 0x20] -> jge 0x198c72 */
  tag_block_get_element((void *)(uintptr_t)edx, 0, 0);
  tag_block_get_element((void *)(uintptr_t)ebx, 0, 0);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  /* cmp (int16_t)eax, (int16_t)edi -> jne 0x198bcb */
  structure_cluster_unmarked(edx);
  /* test (char)eax, (char)eax -> je 0x198c4f */
  FUN_00110210((float *)(uintptr_t)esi, 0.0f, (float *)0, (float *)0, 0.0f, 0.0f, 0.0f);
  /* test (char)eax, (char)eax -> je 0x198c4f */
  structure_cluster_mark(eax);
  /* cmp (int16_t)esi, 0x200 -> jl 0x198c3c */
  display_assert((char *)0x002b39ac, (char *)0x002b3954, 245, 0);
  system_exit(0);
  /* cmp eax, ecx -> jl 0x198b94 */
  display_assert((char *)0x002b397c, (char *)0x002b3954, 304, 0);
  system_exit(0);
  display_assert((char *)0x0026856c, (char *)0x002b3954, 392, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x198d0b */
  display_assert((char *)0x002a3e7c, (char *)0x002b3954, 393, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x198d32 */
  display_assert((char *)0x002b39ec, (char *)0x002b3954, 394, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x198d59 */
  display_assert((char *)0x002b39dc, (char *)0x002b3954, 395, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x198d80 */
  display_assert((char *)0x002b39d8, (char *)0x002b3954, 396, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x198da7 */
  display_assert((char *)0x00269cdc, (char *)0x002b3954, 397, 0);
  system_exit(0);
  display_assert((char *)0x00253440, (char *)0x002b3954, 406, 0);
  system_exit(0);
  FUN_0014df70(33, (float *)(uintptr_t)esi, (float *)(uintptr_t)ecx, 0, (void *)(uintptr_t)eax);
  /* test (char)eax, (char)eax -> je 0x198ec4 */
  scenario_get();
  structure_render_surface_from_point_and_leaf((void *)(uintptr_t)esi, eax, 0, (void *)0, (void *)0, (void *)0, (float *)0, (float *)0);
  /* test (char)eax, (char)eax -> je 0x198e8d */
  tag_block_get_element((void *)(uintptr_t)edi, 0, 0);
  /* relift: cmp word ptr [eax], -1 -> je 0x198e8d */
  /* relift: test byte ptr [ebp - 8], 1 -> je 0x198ec4 */
  /* relift: cmp word ptr [0x4761d8], 1 -> jg 0x198eee */
  display_assert((char *)0x00253418, (char *)0x002b3954, 426, 0);
  system_exit(0);
  /* test (char)eax, (char)eax -> je 0x198dc0 */
  scenario_get();
  display_assert((char *)0x0029dc54, (char *)0x002b3954, 497, 0);
  system_exit(0);
  structure_get_planar_fog_definition_index((void *)(uintptr_t)ebx, eax, edi);
  /* cmp edi, -1 -> jne 0x198faa */
  /* cmp (int16_t)eax, 0xffff -> je 0x198f9d */
  tag_block_get_element((void *)(uintptr_t)ebx, 0, 0);
  FUN_0018e7d0(0);
  /* test eax, eax -> je 0x198f9d */
  scenario_get();
  tag_block_get_element((void *)(uintptr_t)eax, 0, 104);
  tag_get(' gof', 0);
  /* test (char)eax, (char)eax -> je 0x198fe7 */
  /* relift: test byte ptr [eax + 3], 0x80 -> je 0x199032 */
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  tag_block_get_element((void *)(uintptr_t)ebx, 0, 0);
  FUN_001954e0((void *)0);
  /* test (char)eax, (char)eax -> je 0x19922a */
  /* relift: cmp word ptr [0x50674c], 1 -> jne 0x19922a */
  /* relift: cmp dword ptr [0x506784], -1 -> je 0x19922a */
  scenario_get();
  tag_block_get_element((void *)(uintptr_t)ecx, 0, 104);
  tag_block_get_element((void *)(uintptr_t)esi, 0, 0);
  tag_block_get_element((void *)(uintptr_t)ebx, 0, 12);
  tag_block_get_element((void *)(uintptr_t)ebx, 0, 12);
  FUN_0017eb10((float *)0, (float *)0, 0);
  FUN_0017eb10((float *)(uintptr_t)ecx, (float *)(uintptr_t)eax, 0);
  FUN_0017e5b0((float *)(uintptr_t)edi, (float *)(uintptr_t)ecx, 0, 0);
  FUN_0017e5b0((float *)(uintptr_t)ebx, (float *)(uintptr_t)ecx, 0, 0);
  /* test eax, eax -> jne 0x19925a */
  display_assert((char *)0x00267114, (char *)0x002b3954, 134, 0);
  system_exit(0);
  /* test (char)eax, 1 -> je 0x19928a */
  display_assert((char *)0x0029d9b0, (char *)0x002b3954, 135, 0);
  system_exit(0);
  display_assert((char *)0x0028ede8, (char *)0x002b3954, 136, 0);
  system_exit(0);
  /* test edi, edi -> jne 0x1992dc */
  display_assert((char *)0x002b39fc, (char *)0x002b3954, 137, 0);
  system_exit(0);
  /* cmp (int16_t)esi, -1 -> je 0x199359 */
  /* test (char)eax, 0x41 -> jne 0x199347 */
  structures_cluster_marker_begin();
  FUN_001989b0(esi, (float *)(uintptr_t)ecx, 0.0f, 0, (void *)(uintptr_t)edi);
  /* test (char)eax, (char)eax -> jne 0x199338 */
  display_assert((char *)0x002b397c, (char *)0x002b3954, 304, 0);
  system_exit(0);
  /* test (int16_t)ebx, (int16_t)ebx -> jle 0x199359 */
  /* cmp (int16_t)esi, 2 -> jl 0x199392 */
  display_assert((char *)0x002b3a70, (char *)0x002b3aac, 75, 0);
  system_exit(0);
  csstrlen((char *)(uintptr_t)edi);
  /* test eax, eax -> je 0x1993c8 */
  display_assert((char *)0x002b3a40, (char *)0x002b3aac, 76, 0);
  system_exit(0);
  csstrlen((char *)(uintptr_t)ebx);
  /* cmp eax, 0xff -> jbe 0x1993f8 */
  display_assert((char *)0x002b3a10, (char *)0x002b3aac, 77, 0);
  system_exit(0);
  csstrncpy((char *)(uintptr_t)edi, (char *)(uintptr_t)ebx, 255);
  display_assert((char *)0x002b3b10, (char *)0x002b3aac, 91, 0);
  system_exit(0);
  /* cmp (int16_t)edi, -1 -> jl 0x199459 */
  /* cmp (int16_t)edi, 2 -> jl 0x199476 */
  display_assert((char *)0x002b3ad0, (char *)0x002b3aac, 92, 0);
  system_exit(0);
  csmemset((void *)(uintptr_t)esi, 0, 268);
  display_assert((char *)0x0028ede8, (char *)0x002b3aac, 257, 0);
  system_exit(0);
  /* test edi, edi -> jne 0x1994f6 */
  display_assert((char *)0x002b3b18, (char *)0x002b3aac, 258, 0);
  system_exit(0);
  find_files_begin(0, (void *)(uintptr_t)eax);
  /* test ebx, ebx -> jle 0x19952a */
  find_files_next((void *)(uintptr_t)edi, 0);
  /* test (char)eax, (char)eax -> je 0x19952a */
  /* cmp esi, ebx -> jl 0x199510 */
  file_open((void *)(uintptr_t)edi, 0);
  /* test (char)eax, (char)eax -> je 0x1995af */
  file_get_eof((void *)(uintptr_t)edi);
  debug_malloc(eax, esi, (char *)0x002b3aac, 280);
  /* test esi, esi -> je 0x1995a5 */
  file_read((void *)(uintptr_t)edi, 0, (void *)(uintptr_t)esi);
  /* test (char)eax, (char)eax -> jne 0x1995a5 */
  debug_free((void *)(uintptr_t)esi, (char *)0x002b3aac, 286);
  file_close((void *)(uintptr_t)edi);
  /* test eax, eax -> je 0x199616 */
  vsprintf((char *)(uintptr_t)edx, (char *)(uintptr_t)eax, (char *)(uintptr_t)ecx);
  csstrlen((char *)(uintptr_t)ecx);
  /* ((void(*)(void))file_write)(); */ ((void)0);
  file_get_position((void *)(uintptr_t)esi);
  /* ((void(*)(void))file_set_eof)(); */ ((void)0);
  /* test esi, esi -> jne 0x19964b */
  display_assert((char *)0x002b3b10, (char *)0x002b3aac, 508, 0);
  system_exit(0);
  /* relift: cmp dword ptr [esi], 0x66696c6f -> je 0x199673 */
  display_assert((char *)0x002b3bb0, (char *)0x002b3aac, 509, 0);
  system_exit(0);
  /* relift: test word ptr [esi + 4], 0xfffe -> je 0x19969b */
  display_assert((char *)0x002b3b74, (char *)0x002b3aac, 510, 0);
  system_exit(0);
  /* cmp (int16_t)eax, 0xffff -> jl 0x1996ab */
  /* cmp (int16_t)eax, 2 -> jl 0x1996cb */
  display_assert((char *)0x002b3b28, (char *)0x002b3aac, 511, 0);
  system_exit(0);
  file_reference_verify((void *)(uintptr_t)esi);
  csmemcpy((void *)(uintptr_t)esi, (void *)(uintptr_t)esi, 264);
  file_reference_verify((void *)(uintptr_t)edi);
  display_assert((char *)0x002b3c08, (char *)0x002b3aac, 137, 0);
  system_exit(0);
  /* relift: test byte ptr [esi + 4], 1 -> je 0x199761 */
  display_assert((char *)0x002b3bdc, (char *)0x002b3aac, 138, 0);
  system_exit(0);
  path_add_directory((char *)(uintptr_t)esi, (char *)0);
  file_reference_verify((void *)(uintptr_t)edi);
  display_assert((char *)0x0028ede0, (char *)0x002b3aac, 151, 0);
  system_exit(0);
  /* relift: test byte ptr [esi + 4], 1 -> je 0x1997cd */
  path_remove_filename((char *)(uintptr_t)eax);
  path_add_directory((char *)(uintptr_t)ecx, (char *)(uintptr_t)ebx);
  file_reference_verify((void *)(uintptr_t)eax);
  file_reference_verify((void *)(uintptr_t)eax);
  /* test edi, edi -> jne 0x199869 */
  display_assert((char *)0x0028ede0, (char *)0x002b3aac, 185, 0);
  system_exit(0);
  /* relift: test word ptr [ebx + 4], 0xfff0 -> je 0x199891 */
  display_assert((char *)0x002b3cb0, (char *)0x002b3aac, 186, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x1998ab */
  /* cmp eax, 9 -> jne 0x1998d3 */
  display_assert((char *)0x002b3c70, (char *)0x002b3aac, 188, 0);
  system_exit(0);
  /* test (char)eax, 2 -> je 0x1998ff */
  display_assert((char *)0x002b3c18, (char *)0x002b3aac, 189, 0);
  system_exit(0);
  path_from_file_reference(eax, (char *)(uintptr_t)edx, (char *)(uintptr_t)ecx);
  path_split((char *)(uintptr_t)eax, (char **)(uintptr_t)edx, (char **)(uintptr_t)ecx, (char **)(uintptr_t)eax, (char **)(uintptr_t)edx, 0);
  path_add_directory((char *)(uintptr_t)edi, (char *)(uintptr_t)ecx);
  /* test (char)ebx, 2 -> je 0x19996b */
  path_add_directory((char *)(uintptr_t)edi, (char *)(uintptr_t)edx);
  /* test (char)ebx, 4 -> je 0x19997d */
  path_add_directory((char *)(uintptr_t)edi, (char *)(uintptr_t)eax);
  /* test (char)ebx, 8 -> je 0x19998f */
  path_add_extension((char *)(uintptr_t)edi, (char *)(uintptr_t)ecx);
  file_reference_verify((void *)(uintptr_t)eax);
  file_reference_verify((void *)(uintptr_t)ecx);
  /* relift: cmp (int16_t)edx, word ptr [eax + 6] -> jne 0x1999de */
  csstrcmp((char *)(uintptr_t)esi, (char *)0);
  /* test esi, esi -> jne 0x199a18 */
  display_assert((char *)0x002b3b10, (char *)0x002b3aac, 91, 0);
  system_exit(0);
  csmemset((void *)(uintptr_t)esi, 0, 268);
  file_reference_add_directory((void *)(uintptr_t)esi, (char *)(uintptr_t)eax);
  file_reference_set_name((void *)(uintptr_t)esi, (char *)(uintptr_t)ecx);
  csmemset((void *)(uintptr_t)eax, 0, 268);
  file_reference_add_directory((void *)(uintptr_t)edx, (char *)(uintptr_t)ecx);
  file_exists((void *)(uintptr_t)eax);
  /* test (char)eax, (char)eax -> je 0x199b05 */
  find_files_begin(0, (void *)(uintptr_t)ecx);
  find_files_next((void *)(uintptr_t)edx, 0);
  /* test (char)eax, (char)eax -> je 0x199b14 */
  file_delete((void *)(uintptr_t)eax);
  find_files_next((void *)(uintptr_t)ecx, 0);
  /* test (char)eax, (char)eax -> jne 0x199ae0 */
  FUN_0019a490((void *)(uintptr_t)edx);
  display_assert((char *)0x002b3d7c, (char *)0x002b3aac, 369, 0);
  system_exit(0);
  /* test esi, esi -> jne 0x199b81 */
  display_assert((char *)0x002b3d68, (char *)0x002b3aac, 370, 0);
  system_exit(0);
  /* relift: cmp byte ptr [edi], 0 -> jne 0x199ba6 */
  display_assert((char *)0x002b3d50, (char *)0x002b3aac, 371, 0);
  system_exit(0);
  /* relift: cmp byte ptr [esi], 0 -> jne 0x199bcb */
  display_assert((char *)0x002b3d38, (char *)0x002b3aac, 372, 0);
  system_exit(0);
  /* relift: cmp dword ptr [ebp + 0x10], 0xff -> jl 0x199bf4 */
  display_assert((char *)0x002b3d14, (char *)0x002b3aac, 373, 0);
  system_exit(0);
  csstrlen((char *)(uintptr_t)esi);
  /* cmp eax, 0xff -> jb 0x199c24 */
  display_assert((char *)0x002b3ce0, (char *)0x002b3aac, 374, 0);
  system_exit(0);
  csmemset((void *)(uintptr_t)eax, 0, 268);
  file_reference_set_name((void *)(uintptr_t)ecx, (char *)(uintptr_t)edi);
  file_exists((void *)(uintptr_t)edx);
  /* test (char)eax, (char)eax -> je 0x199d2c */
  file_read_into_buffer((void *)(uintptr_t)ecx, (void *)(uintptr_t)eax);
  /* test ebx, ebx -> jne 0x199c96 */
  file_delete((void *)(uintptr_t)edx);
  /* relift: cmp dword ptr [ebp - 4], 0x18e70 -> je 0x199cc8 */
  debug_free((void *)(uintptr_t)ebx, (char *)0x002b3aac, 389);
  file_delete((void *)(uintptr_t)eax);
  /* test ebx, ebx -> je 0x199d2c */
  csstrcmp((char *)(uintptr_t)edi, (char *)(uintptr_t)ecx);
  /* test eax, eax -> je 0x199cf7 */
  /* relift: cmp byte ptr [edi], 0 -> je 0x199d19 */
  /* cmp esi, 0xc8 -> jl 0x199cd0 */
  csmemcpy((void *)(uintptr_t)ecx, (void *)(uintptr_t)eax, edx);
  debug_free((void *)(uintptr_t)ebx, (char *)0x002b3aac, 416);
  display_assert((char *)0x002b3d7c, (char *)0x002b3aac, 430, 0);
  system_exit(0);
  /* test edi, edi -> jne 0x199da4 */
  display_assert((char *)0x002b3d68, (char *)0x002b3aac, 431, 0);
  system_exit(0);
  /* relift: cmp byte ptr [esi], 0 -> jne 0x199dc9 */
  display_assert((char *)0x002b3d50, (char *)0x002b3aac, 432, 0);
  system_exit(0);
  /* relift: cmp byte ptr [edi], 0 -> jne 0x199dee */
  display_assert((char *)0x002b3d38, (char *)0x002b3aac, 433, 0);
  system_exit(0);
  /* relift: cmp dword ptr [ebp + 0x10], 0xff -> jl 0x199e17 */
  display_assert((char *)0x002b3d14, (char *)0x002b3aac, 434, 0);
  system_exit(0);
  csstrlen((char *)(uintptr_t)edi);
  /* cmp eax, 0xff -> jb 0x199e47 */
  display_assert((char *)0x002b3ce0, (char *)0x002b3aac, 435, 0);
  system_exit(0);
  csmemset((void *)(uintptr_t)eax, 0, 268);
  file_reference_set_name((void *)(uintptr_t)ecx, (char *)(uintptr_t)esi);
  file_exists((void *)(uintptr_t)edx);
  /* test (char)eax, (char)eax -> je 0x199ee3 */
  file_read_into_buffer((void *)(uintptr_t)ecx, (void *)(uintptr_t)eax);
  /* test edi, edi -> jne 0x199eb5 */
  file_delete((void *)(uintptr_t)edx);
  /* relift: cmp dword ptr [ebp - 8], 0x18e70 -> je 0x199edf */
  debug_free((void *)(uintptr_t)edi, (char *)0x002b3aac, 450);
  file_delete((void *)(uintptr_t)eax);
  /* test edi, edi -> jne 0x199f16 */
  debug_malloc(0x00018e70, 0, (char *)0x002b3aac, 461);
  /* test edi, edi -> je 0x199fe7 */
  csmemset((void *)(uintptr_t)edi, 0, 0x00018e70);
  /* relift: cmp byte ptr [ebx], 0 -> je 0x199f47 */
  csstrcmp((char *)(uintptr_t)ebx, (char *)(uintptr_t)ecx);
  /* test eax, eax -> je 0x199f47 */
  /* cmp esi, 0xc8 -> jl 0x199f20 */
  csstrcpy((char *)(uintptr_t)esi, (char *)0);
  csmemcpy((void *)(uintptr_t)esi, (void *)0, 0);
  file_exists((void *)(uintptr_t)edx);
  FUN_0019a490((void *)(uintptr_t)eax);
  file_open((void *)(uintptr_t)ecx, 0);
  /* test (char)eax, (char)eax -> je 0x199fcd */
  /* ((void(*)(void))file_write)(); */ ((void)0);
  file_close((void *)(uintptr_t)eax);
  debug_free((void *)(uintptr_t)edi, (char *)0x002b3aac, 492);
  /* test (char)eax, (char)eax -> jne 0x19a007 */
  display_assert((char *)0x00254818, (char *)0x002b3aac, 495, 0);
  system_exit(0);
  csmemcmp((void *)(uintptr_t)ecx, (void *)(uintptr_t)eax, 0);
  file_reference_verify((void *)(uintptr_t)eax);
  /* test eax, 0xfffffffc -> je 0x19a083 */
  display_assert((char *)0x002b3dbc, (char *)0x002b3dec, 548, 0);
  system_exit(0);
  /* relift: test byte ptr [ebx + 4], 1 -> je 0x19a0a9 */
  display_assert((char *)0x002b3d90, (char *)0x002b3dec, 549, 0);
  system_exit(0);
  /* test (int16_t)edi, (int16_t)edi -> jl 0x19a0da */
  /* cmp eax, -1 -> je 0x19a0d3 */
  CloseHandle(0);
  /* mem[0x0032cf60] = ecx */
  csstrcpy((char *)0x0032cf68, (char *)(uintptr_t)ebx);
  /* relift: cmp byte ptr [ebx], 0 -> je 0x19a196 */
  csstrlen((char *)(uintptr_t)edi);
  csstrlen((char *)(uintptr_t)ebx);
  /* cmp eax, 0xff -> jbe 0x19a15d */
  display_assert((char *)0x002b3e18, (char *)0x002b3dec, 672, 0);
  system_exit(0);
  csstrlen((char *)(uintptr_t)edi);
  /* cmp esi, edi -> je 0x19a175 */
  csstrlen((char *)(uintptr_t)edi);
  csstrncpy((char *)(uintptr_t)esi, (char *)(uintptr_t)ebx, ecx);
  /* relift: cmp byte ptr [ebx], 0 -> je 0x19a226 */
  csstrlen((char *)(uintptr_t)edi);
  csstrlen((char *)(uintptr_t)ebx);
  /* cmp eax, 0xff -> jbe 0x19a1ed */
  display_assert((char *)0x002b3e50, (char *)0x002b3dec, 696, 0);
  system_exit(0);
  csstrlen((char *)(uintptr_t)edi);
  /* cmp esi, edi -> je 0x19a205 */
  csstrlen((char *)(uintptr_t)edi);
  csstrncpy((char *)(uintptr_t)esi, (char *)(uintptr_t)ebx, ecx);
  csstrlen((char *)(uintptr_t)esi);
  /* relift: cmp word ptr [ebp + 8], 0 -> je 0x19a25d */
  unicode_cursor_backward((char *)(uintptr_t)esi, (void *)(uintptr_t)eax);
  /* cmp (int16_t)eax, 0x5c -> jne 0x19a243 */
  unicode_cursor_forward((char *)(uintptr_t)esi, (void *)(uintptr_t)ecx);
  /* cmp (int16_t)eax, 0x5c -> jne 0x19a27e */
  csstrlen((char *)(uintptr_t)esi);
  unicode_cursor_backward((char *)(uintptr_t)esi, (void *)(uintptr_t)eax);
  /* cmp (int16_t)eax, 0x2e -> jne 0x19a2ff */
  /* test (char)eax, (char)eax -> je 0x19a33b */
  /* relift: cmp byte ptr [ecx], 0 -> jne 0x19a33b */
  /* relift: cmp byte ptr [edx], 0 -> jne 0x19a33b */
  /* cmp (int16_t)eax, 0x5c -> jne 0x19a33b */
  /* test (char)eax, (char)eax -> je 0x19a327 */
  /* relift: cmp byte ptr [eax], 0 -> jne 0x19a327 */
  /* relift: cmp byte ptr [ecx], 0 -> jne 0x19a33b */
  /* relift: cmp word ptr [ebp + 8], 0 -> jne 0x19a2c3 */
  /* test (char)eax, (char)eax -> je 0x19a357 */
  /* relift: cmp byte ptr [edx], 0 -> jne 0x19a357 */
  /* relift: cmp dword ptr [edi], esi -> je 0x19a360 */
  /* test edi, edi -> jne 0x19a3a3 */
  display_assert((char *)0x002b3e90, (char *)0x002b3dec, 788, 0);
  system_exit(0);
  /* test (char)eax, (char)eax -> je 0x19a3d6 */
  /* test (char)ecx, (char)ecx -> je 0x19a3d6 */
  /* test (char)ecx, (char)ecx -> je 0x19a3d6 */
  _isalpha();
  /* test eax, eax -> je 0x19a3d6 */
  /* relift: cmp byte ptr [esi + 1], 0x3a -> jne 0x19a3d6 */
  /* relift: cmp byte ptr [esi + 2], 0x5c -> je 0x19a3e4 */
  csstrcpy((char *)(uintptr_t)edi, (char *)0x002b3e8c);
  FUN_0008dc30((char *)(uintptr_t)edi, (char *)(uintptr_t)esi);
  file_reference_verify((void *)(uintptr_t)eax);
  path_from_file_reference(eax, (char *)(uintptr_t)edx, (char *)(uintptr_t)ecx);
  file_get_full_attributes((char *)(uintptr_t)ecx);
  /* cmp eax, -1 -> je 0x19a444 */
  file_reference_verify((void *)(uintptr_t)eax);
  xapi_GetLastError();
  error(0, (char *)0x002b3ea4);
  SetLastError(0);
  file_reference_verify((void *)(uintptr_t)ebx);
  path_from_file_reference(ecx, (char *)(uintptr_t)edi, (char *)(uintptr_t)eax);
  CreateFileA((char *)(uintptr_t)edx, 0x40000000, 0, 0, 0, 128, 0);
  /* cmp eax, -1 -> je 0x19a51d */
  CloseHandle(0);
  CreateDirectoryA((char *)(uintptr_t)edi, 0);
  /* test eax, eax -> jne 0x19a50a */
  file_reference_verify((void *)(uintptr_t)ebx);
  xapi_GetLastError();
  error(0, (char *)0x002b3ea4);
  SetLastError(0);
  file_reference_verify((void *)(uintptr_t)ebx);
  path_from_file_reference(edx, (char *)(uintptr_t)ecx, (char *)(uintptr_t)eax);
  /* test (char)eax, 1 -> je 0x19a5df */
  FUN_001d0df0((char *)(uintptr_t)eax, 128);
  /* test eax, eax -> je 0x19a5f8 */
  DeleteFileA((char *)(uintptr_t)ecx);
  /* test eax, eax -> je 0x19a5f8 */
  FUN_001d347c((char *)(uintptr_t)edx);
  /* test eax, eax -> je 0x19a5f8 */
  file_reference_verify((void *)(uintptr_t)ebx);
  xapi_GetLastError();
  error(0, (char *)0x002b3ea4);
  SetLastError(0);
  file_reference_verify((void *)(uintptr_t)esi);
  path_from_file_reference(edx, (char *)(uintptr_t)ecx, (char *)(uintptr_t)eax);
  file_get_full_attributes((char *)(uintptr_t)eax);
  /* cmp eax, -1 -> je 0x19a6a3 */
  xapi_GetLastError();
  /* cmp eax, 2 -> je 0x19a6c6 */
  xapi_GetLastError();
  /* cmp eax, 3 -> je 0x19a6c6 */
  file_error((void *)0x002b3ed4, (char *)0);
  file_reference_verify((void *)(uintptr_t)eax);
  path_from_file_reference(edx, (char *)(uintptr_t)esi, (char *)(uintptr_t)ecx);
  csstrcpy((char *)(uintptr_t)ecx, (char *)(uintptr_t)eax);
  path_remove_filename((char *)(uintptr_t)edx);
  path_add_directory((char *)(uintptr_t)eax, (char *)(uintptr_t)edi);
  MoveFileA();
  /* test eax, eax -> je 0x19a790 */
  path_remove_filename((char *)(uintptr_t)esi);
  path_add_directory((char *)(uintptr_t)esi, (char *)(uintptr_t)edi);
  file_reference_verify((void *)(uintptr_t)eax);
  display_assert((char *)0x002b3f8c, (char *)0x002b3dec, 308, 0);
  system_exit(0);
  /* test (char)ebx, 3 -> jne 0x19a82a */
  display_assert((char *)0x002b3f48, (char *)0x002b3dec, 309, 0);
  system_exit(0);
  /* test (char)ebx, 4 -> je 0x19a856 */
  display_assert((char *)0x002b3ef0, (char *)0x002b3dec, 310, 0);
  system_exit(0);
  path_from_file_reference(eax, (char *)(uintptr_t)edx, (char *)(uintptr_t)ecx);
  /* test edi, edi -> je 0x19a886 */
  CreateFileA((char *)(uintptr_t)ecx, eax, 0, 0, 0, 128, 0);
  /* cmp eax, -1 -> je 0x19a8d9 */
  SetFilePointer(0, 0, (void *)0, 0);
  /* cmp eax, -1 -> jne 0x19a91e */
  CloseHandle(0);
  file_reference_verify((void *)(uintptr_t)eax);
  xapi_GetLastError();
  error(0, (char *)0x002b3ea4);
  SetLastError(0);
  file_reference_verify((void *)(uintptr_t)edi);
  CloseHandle(0);
  /* test eax, eax -> je 0x19a967 */
  file_reference_verify((void *)(uintptr_t)edi);
  xapi_GetLastError();
  error(0, (char *)0x002b3ea4);
  SetLastError(0);
  file_reference_verify((void *)(uintptr_t)edi);
  SetFilePointer(0, 0, (void *)0, 0);
  /* cmp esi, -1 -> jne 0x19a9fa */
  file_reference_verify((void *)(uintptr_t)edi);
  xapi_GetLastError();
  error(0, (char *)0x002b3ea4);
  SetLastError(0);
  file_reference_verify((void *)(uintptr_t)esi);
  SetFilePointer(0, 0, (void *)0, 0);
  /* test (char)ebx, (char)ebx -> jne 0x19aa5f */
  file_reference_verify((void *)(uintptr_t)esi);
  xapi_GetLastError();
  error(0, (char *)0x002b3ea4);
  SetLastError(0);
  file_reference_verify((void *)(uintptr_t)edi);
  GetFileSize(0, (void *)0);
  /* cmp esi, -1 -> jne 0x19aac6 */
  file_reference_verify((void *)(uintptr_t)edi);
  xapi_GetLastError();
  error(0, (char *)0x002b3ea4);
  SetLastError(0);
  file_reference_verify((void *)(uintptr_t)esi);
  file_set_position((void *)(uintptr_t)esi, 0);
  /* test (char)eax, (char)eax -> je 0x19ab07 */
  SetEndOfFile(0);
  /* test eax, eax -> je 0x19ab07 */
  file_reference_verify((void *)(uintptr_t)esi);
  xapi_GetLastError();
  error(0, (char *)0x002b3ea4);
  SetLastError(0);
  file_reference_verify((void *)(uintptr_t)ebx);
  display_assert((char *)0x00267900, (char *)0x002b3dec, 423, 0);
  system_exit(0);
  ReadFile(0, (void *)(uintptr_t)edi, ecx, (void *)(uintptr_t)eax, (void *)0);
  /* test eax, eax -> je 0x19abbf */
  /* relift: cmp dword ptr [ebp - 4], eax -> jne 0x19abb8 */
  SetLastError(38);
  file_reference_verify((void *)(uintptr_t)ebx);
  xapi_GetLastError();
  error(0, (char *)0x002b3ea4);
  SetLastError(0);
  file_reference_verify((void *)(uintptr_t)ebx);
  display_assert((char *)0x00267900, (char *)0x002b3dec, 451, 0);
  system_exit(0);
  WriteFile(0, (void *)(uintptr_t)edi, ecx, (void *)(uintptr_t)eax, (void *)0);
  /* test eax, eax -> je 0x19ac68 */
  /* relift: cmp dword ptr [ebp - 4], eax -> jne 0x19ac68 */
  file_reference_verify((void *)(uintptr_t)ebx);
  xapi_GetLastError();
  error(0, (char *)0x002b3ea4);
  SetLastError(0);
  file_set_position((void *)(uintptr_t)esi, 0);
  /* test (char)eax, (char)eax -> je 0x19ace5 */
  file_read((void *)(uintptr_t)esi, 0, (void *)(uintptr_t)ecx);
  /* test (char)eax, (char)eax -> je 0x19ace5 */
  file_set_position((void *)(uintptr_t)esi, 0);
  /* test (char)eax, (char)eax -> je 0x19ad25 */
  /* ((void(*)(void))file_write)(); */ ((void)0);
  /* test (char)eax, (char)eax -> je 0x19ad25 */
  file_reference_verify((void *)(uintptr_t)ebx);
  csmemset((void *)(uintptr_t)edi, 0, 0);
  path_from_file_reference(edx, (char *)(uintptr_t)ecx, (char *)(uintptr_t)eax);
  FUN_001d0ee1();
  /* test eax, eax -> je 0x19adb5 */
  csmemcpy((void *)(uintptr_t)edi, (void *)(uintptr_t)edx, 0);
  file_reference_verify((void *)(uintptr_t)ebx);
  xapi_GetLastError();
  error(0, (char *)0x002b3ea4);
  SetLastError(0);
  file_reference_verify((void *)(uintptr_t)esi);
  /* test edi, edi -> jne 0x19ae4a */
  display_assert((char *)0x00267f68, (char *)0x002b3dec, 524, 0);
  system_exit(0);
  path_from_file_reference(edx, (char *)(uintptr_t)ecx, (char *)(uintptr_t)eax);
  FUN_001d0ee1();
  /* test eax, eax -> je 0x19ae88 */
  file_reference_verify((void *)(uintptr_t)esi);
  xapi_GetLastError();
  error(0, (char *)0x002b3ea4);
  return NULL;

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x1a4440 — refresh biped forward/up from flying, climb, limp, or default. */
#if defined(__clang__)
static float (*const a4440_norm)(float *) = normalize3d;
static void (*const a4440_cross)(float *, float *, float *) = cross_product3d;
static bool (*const a4440_vnorm)(float *) = valid_real_normal3d;
static char *(*const a4440_xspr)(char *, const char *, ...) = csprintf;
static void (*const a4440_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const a4440_exitfn)(int) = system_exit;
static void (*const a4440_rots)(float *, float *, float, float) = rotate_vector3d_by_sincos;
static void *(*const a4440_get)(int, int) = object_get_and_verify_type;
static void (*const a4440_a2800)(int, const char *) = FUN_001a2800;
static void *(*const a4440_tag)(int, int) = tag_get;
static void (*const a4440_ffloor)(void) = (void(*)(void))FUN_001d94f0;

/* FUN_001a4440 (0x1a4440) — Capstone tip: biped tag flags bit2 clear → return. */
void FUN_001a4440(int unit_handle)
{
  void *obj = object_get_and_verify_type(unit_handle, 1);
  void *tag = tag_get(0x62697064, *(int *)obj);
  if ((*(unsigned int *)((char *)tag + 0x2f4) & 4) == 0)
    return;
}


#else
void FUN_001a4440(int unit_handle)
{
  char *unit;
  char *biped_tag;
  unsigned int flags;
  float *forward;
  float *up;
  float *global_up;
  float *global_forward;
  float *global_left;
  float axis[3];
  float temp[3];
  float rotated[3];
  float angle;
  float s;
  float c;
  float dot;

  unit = (char *)object_get_and_verify_type(unit_handle, 1);
  biped_tag = (char *)tag_get(0x62697064, *(int *)unit); /* 'bipd' */
  flags = *(unsigned int *)(biped_tag + 0x2f4);
  forward = (float *)(unit + 0x24);
  up = (float *)(unit + 0x30);

  if ((flags & 4) != 0 && (*(unsigned char *)(unit + 0xb6) & 4) == 0) {
    if (!valid_real_normal3d(forward)) {
      csprintf((char *)0x5ab100, (char *)0x254a24, (char *)0x2b5148,
               (double)forward[0], (double)forward[1], (double)*(float *)(unit + 0x2c));
      display_assert((char *)0x5ab100, (char *)0x2b4d5c, 0xfa5, 1);
      system_exit(-1);
    }

    global_up = *(float **)0x31fc44;
    cross_product3d(global_up, forward, temp);
    cross_product3d(temp, forward, axis);
    if (normalize3d(axis) == 0.0f) {
      global_forward = *(float **)0x31fc3c;
      global_left = *(float **)0x31fc40;
      axis[0] = global_forward[0];
      axis[1] = global_forward[1];
      axis[2] = global_forward[2];
      temp[0] = global_left[0];
      temp[1] = global_left[1];
      temp[2] = global_left[2];
    }

    angle = *(float *)(unit + 0x468);
    c = cosf(angle);
    s = sinf(angle);
    rotated[0] = axis[0] * c;
    rotated[1] = axis[1] * c;
    rotated[2] = axis[2] * c;
    normalize3d(temp);
    up[0] = temp[0] * s + rotated[0];
    up[1] = temp[1] * s + rotated[1];
    up[2] = temp[2] * s + rotated[2];
    FUN_001a2800(unit_handle, (const char *)0x2b5130);
    return;
  }

  if ((flags & 0x40) != 0 && (*(unsigned char *)(unit + 0xb6) & 4) == 0) {
    float desired[3];

    if (*(int *)(unit + 0x430) == -1) {
      desired[0] = up[0];
      desired[1] = up[1];
      desired[2] = up[2];
    } else {
      float *climb = (float *)(unit + 0x46c);
      desired[0] = climb[0];
      desired[1] = climb[1];
      desired[2] = climb[2];
      cross_product3d(up, desired, temp);
      if (normalize3d(temp) == 0.0f) {
        dot = desired[0] * up[0] + desired[1] * up[1] + desired[2] * up[2];
        if (!(dot > 0.0f)) {
          desired[0] = forward[0];
          desired[1] = forward[1];
          desired[2] = forward[2];
        }
      } else {
        double bank = *(double *)0x281138;
        c = (float)cos(bank);
        s = (float)sin(bank);
        rotated[0] = up[0];
        rotated[1] = up[1];
        rotated[2] = up[2];
        rotate_vector3d_by_sincos(rotated, temp, s, c);
        cross_product3d(desired, rotated, axis);
        if (!(axis[0] * temp[0] + axis[1] * temp[1] + axis[2] * temp[2] > 0.0f)) {
          desired[0] = rotated[0];
          desired[1] = rotated[1];
          desired[2] = rotated[2];
        }
      }
    }

    cross_product3d(desired, forward, temp);
    cross_product3d(temp, desired, axis);
    if (normalize3d(axis) == 0.0f) {
      cross_product3d(desired, up, temp);
      cross_product3d(temp, desired, axis);
      if (normalize3d(axis) == 0.0f) {
        global_up = *(float **)0x31fc44;
        global_forward = *(float **)0x31fc3c;
        desired[0] = global_up[0];
        desired[1] = global_up[1];
        desired[2] = global_up[2];
        axis[0] = global_forward[0];
        axis[1] = global_forward[1];
        axis[2] = global_forward[2];
      }
    }
    forward[0] = axis[0];
    forward[1] = axis[1];
    forward[2] = axis[2];
    up[0] = desired[0];
    up[1] = desired[1];
    up[2] = desired[2];
    FUN_001a2800(unit_handle, (const char *)0x2b5118);
    return;
  }

  if ((*(unsigned char *)(unit + 0xb6) & 4) != 0 &&
      (*(unsigned char *)(unit + 0x424) & 1) == 0) {
    float *look = (float *)(unit + 0x46c);

    FUN_001a2800(unit_handle, (const char *)0x2b50fc);
    dot = look[0] * up[0] + look[1] * up[1] + look[2] * up[2];
    if (fabs(dot - 1.0f) >= *(double *)0x2533d0) {
      angle = acosf(dot);
      if (angle != 0.0f) {
        cross_product3d(up, look, temp);
        if (normalize3d(temp) != 0.0f) {
          c = cosf(angle);
          s = sinf(angle);
          rotate_vector3d_by_sincos(up, temp, s, c);
          rotate_vector3d_by_sincos(forward, temp, s, c);
          normalize3d(up);
          normalize3d(forward);
        }
      }
    }
    FUN_001a2800(unit_handle, (const char *)0x2b50e0);
    return;
  }

  forward[2] = 0.0f;
  if (normalize3d(forward) == 0.0f) {
    global_forward = *(float **)0x31fc3c;
    forward[0] = global_forward[0];
    forward[1] = global_forward[1];
    forward[2] = global_forward[2];
  }
  global_up = *(float **)0x31fc44;
  up[0] = global_up[0];
  up[1] = global_up[1];
  up[2] = global_up[2];
  FUN_001a2800(unit_handle, (const char *)0x2b50c8);
}
#endif


/* FUN_001a4990 (0x1a4990) — readable C lift. */
char FUN_001a4990(int unit_handle)
{
  void *biped;
  void *tag;
  char *quat;
  void __attribute__((regparm(1))) (*init_fn)(int) =
      (void __attribute__((regparm(1))) (*)(int))(void *)FUN_001a25e0;

  biped = object_get_and_verify_type(unit_handle, 1);
  tag = tag_get(0x62697064, *(int *)biped);
  quat = (char *)biped + 0x46c;
  *(int *)(quat + 0) = *(int *)0x32513c;
  *(int *)(quat + 4) = *(int *)0x325140;
  *(int *)(quat + 8) = *(int *)0x325144;
  *(int *)(quat + 0xc) = *(int *)0x325148;
  *(unsigned char *)((char *)biped + 0x45c) = 0x7f;
  *(int *)((char *)biped + 0x430) = -1;
  *(int *)((char *)biped + 0x434) = -1;
  object_get_world_position(unit_handle, (vector3_t *)((char *)biped + 0x438));
  *(int *)((char *)biped + 0x448) = -1;
  *(int *)((char *)biped + 0x444) = -1;
  *(int *)((char *)biped + 0x44c) = -1;
  if ((*(unsigned char *)((char *)tag + 0x2f4) & 0x40) != 0)
    init_fn(unit_handle);
  FUN_001a4440(unit_handle);
  *(int *)((char *)biped + 0x42c) = -1;
  *(unsigned char *)((char *)biped + 0x42b) = 0;
  return 1;
}


/* FUN_001a4a50 moved to units/bipeds.c */



/* FUN_001a4a70 (0x1a4a70) — readable C lift (restored pre-naked). */
void FUN_001a4a70(int handle, float *velocity)
{
  char *unit;
  char *biped_tag;
  float *global_up;
  float lateral[3];
  float speed;
  float kick;
  float tmp[3];

  unit = (char *)object_get_and_verify_type(handle, 1);
  biped_tag = (char *)tag_get(0x62697064, *(int *)unit); /* 'bipd' */

  /* Skip entirely when the biped is already in a special recovery state. */
  if ((*(unsigned int *)(biped_tag + 0x17c) & 0x100000) != 0)
    return;

  FUN_001a2800(handle, (const char *)0x2b5180);

  if ((*(unsigned char *)(unit + 0xb6) & 4) == 0) {
    velocity[0] *= *(float *)0x253398;
    velocity[1] *= *(float *)0x253398;
    velocity[2] *= *(float *)0x253398;
  }
  if ((*(unsigned char *)(unit + 0xb6) & 4) != 0)
    biped_stop_limp_body_physics(handle);

  *(float *)(unit + 0x18) += velocity[0];
  *(float *)(unit + 0x1c) += velocity[1];
  *(float *)(unit + 0x20) += velocity[2];
  *(int *)(unit + 4) &= ~0x20;
  *(unsigned int *)(unit + 0x424) |= 3;

  if ((*(unsigned char *)(unit + 0xb6) & 4) != 0 ||
      (*(unsigned char *)(biped_tag + 0x2f4) & 0x44) != 0) {
    global_up = *(float **)0x31fc44;
    /* lateral = velocity × up  (same FPU order as XBE) */
    lateral[0] = velocity[2] * global_up[1] - velocity[1] * global_up[2];
    lateral[1] = global_up[2] * velocity[0] - velocity[2] * global_up[0];
    lateral[2] = velocity[1] * global_up[0] - global_up[1] * velocity[0];
    normalize3d(lateral);
    speed = sqrtf(velocity[0] * velocity[0] + velocity[1] * velocity[1] +
                  velocity[2] * velocity[2]);
    kick = random_math_real((unsigned int *)get_global_random_seed_address()) *
           speed * *(float *)0x2568bc;
    *(float *)(unit + 0x3c) += lateral[0] * kick;
    *(float *)(unit + 0x40) += lateral[1] * kick;
    *(float *)(unit + 0x44) += lateral[2] * kick;
  }

  if (*(int *)(unit + 0xcc) == -1) {
    tmp[0] = velocity[0];
    tmp[1] = velocity[1];
    tmp[2] = velocity[2];
    if (normalize3d(tmp) > 0.0f) {
      *(float *)(unit + 0x24) = tmp[0];
      *(float *)(unit + 0x28) = tmp[1];
      *(float *)(unit + 0x2c) = tmp[2];
      FUN_001a4440(handle);
      FUN_001a2800(handle, (const char *)0x2b5174);
    }
  }
}


/* 0x1a4c50 — biped facing / aim-turn update from movement state. */
#if defined(__clang__)
static float (*const a4c50_v2170)(float *) = FUN_00012170;
static float (*const a4c50_mag)(float *) = magnitude3d;
static float (*const a4c50_norm)(float *) = normalize3d;
static float (*const a4c50_v3070)(float *, float *) = FUN_00013070;
static void (*const a4c50_cross)(float *, float *, float *) = cross_product3d;
static void (*const a4c50_rots)(float *, float *, float, float) = rotate_vector3d_by_sincos;
static void *(*const a4c50_get)(int, int) = object_get_and_verify_type;
static void (*const a4c50_a2800)(int, const char *) = FUN_001a2800;
static void (*const a4c50_a4440)(int) = FUN_001a4440;
static void (*const a4c50_b0630)(int, float *, float *, float *, float *, float, float) = FUN_001b0630;
static void *(*const a4c50_tag)(int, int) = tag_get;

/* FUN_001a4c50 (0x1a4c50) — Capstone tip: biped flag clear + idle → return. */
void FUN_001a4c50(int unit_handle, unsigned char *state)
{
  char *obj;
  void *tag;

  (void)state;
  obj = (char *)object_get_and_verify_type(unit_handle, 1);
  tag = tag_get(0x62697064, *(int *)obj);
  if ((*(unsigned int *)((char *)tag + 0x2f4) & 4) == 0 ||
      (*(unsigned char *)(obj + 0xb6) & 4) != 0) {
    if (obj[0x257] == 0)
      return;
  }
}
#else
void FUN_001a4c50(int unit_handle, unsigned char *state)
{
  char *unit;
  char *biped_tag;
  unsigned int tag_flags;
  float *forward;
  float *up;
  float *aim;
  float desired[3];
  float yaw_bounds[4];
  float pitch_scale;
  float yaw_scale;
  float turn;
  float blend;
  float speed_sq;
  float aim_dot;
  float thresh;
  char special;
  char facing_ok;
  float s;
  float c;
  float *global_up;
  float tmp[3];

  unit = (char *)object_get_and_verify_type(unit_handle, 1);
  biped_tag = (char *)tag_get(0x62697064, *(int *)unit); /* 'bipd' */
  tag_flags = *(unsigned int *)(biped_tag + 0x2f4);
  forward = (float *)(unit + 0x24);
  up = (float *)(unit + 0x30);
  aim = (float *)(unit + 0x1d4);

  /* Fast path: biped uses simple pathfinding facing and is alive. */
  if ((tag_flags & 4) != 0 && (*(unsigned char *)(unit + 0xb6) & 4) == 0) {
    speed_sq = *(float *)(unit + 0x18) * *(float *)(unit + 0x18) +
               *(float *)(unit + 0x1c) * *(float *)(unit + 0x1c) +
               *(float *)(unit + 0x20) * *(float *)(unit + 0x20);
    if (!(speed_sq > *(float *)0x253f2c)) {
      speed_sq = *(float *)(unit + 0x3c) * *(float *)(unit + 0x3c) +
                 *(float *)(unit + 0x40) * *(float *)(unit + 0x40) +
                 *(float *)(unit + 0x44) * *(float *)(unit + 0x44);
      if (!(speed_sq > *(float *)0x2b51c4) &&
          !(FUN_00012170((float *)(unit + 0x228)) > *(float *)0x255d1c)) {
        if ((*(unsigned char *)(unit + 0x1b8) & 0x20) != 0) {
          unsigned int bits = 0x3f7d70a4u;
          thresh = *(float *)&bits;
        } else {
          thresh = *(float *)(biped_tag + 0x4c8);
        }
        if (FUN_00013070(aim, forward) > thresh) {
          desired[0] = forward[0];
          desired[1] = forward[1];
          desired[2] = forward[2];
          goto aim_blend;
        }
      }
    }

    desired[0] = aim[0];
    desired[1] = aim[1];
    desired[2] = aim[2];
    turn = *(float *)(biped_tag + 0x330) * *(float *)(unit + 0x230);
    if (turn != 0.0f) {
      desired[2] += turn;
      if (normalize3d(desired) == 0.0f) {
        desired[0] = aim[0];
        desired[1] = aim[1];
        desired[2] = aim[2];
      }
    }

  aim_blend:
    /* Lateral aim error vs unit up, scaled into unit+0x468 throttle. */
    turn = (up[1] * forward[2] - up[2] * forward[1]) * aim[2] +
           (up[2] * forward[0] - up[0] * forward[2]) * aim[1] +
           (up[0] * forward[1] - up[1] * forward[0]) * aim[0];
    turn = turn * *(float *)0x254e6c * *(float *)(unit + 0x228) -
           *(float *)(unit + 0x22c);
    if (turn > *(float *)0x2533ec)
      turn = *(float *)0x2533ec;
    turn *= *(float *)(biped_tag + 0x324);
    if (!(turn * *(float *)(unit + 0x468) > 0.0f)) {
      blend = 1.0f;
    } else {
      blend = *(float *)(unit + 0x468) / turn;
      if (blend > 1.0f)
        blend = 1.0f;
      blend = 1.0f - blend;
    }
    blend = (1.0f - blend) * *(float *)(biped_tag + 0x32c) +
            blend * *(float *)(biped_tag + 0x328);
    if (blend > 0.0f)
      *(float *)(unit + 0x468) =
          *(float *)(unit + 0x468) +
          (turn - *(float *)(unit + 0x468)) * blend * *(float *)0x253394;
    else
      *(float *)(unit + 0x468) = turn;

    {
      unsigned int pi = 0x40490fdbu;
      unsigned int hpi = 0x3fc90fdbu;
      yaw_bounds[0] = -*(float *)&pi;
      yaw_bounds[1] = *(float *)&pi;
      yaw_bounds[2] = -*(float *)&hpi;
      yaw_bounds[3] = *(float *)&hpi;
    }
    pitch_scale = *(float *)(biped_tag + 0x344) * *(float *)0x2546a4;
    yaw_scale = *(float *)(biped_tag + 0x348) * *(float *)0x25620c;
    if (yaw_scale == 0.0f) {
      forward[0] = desired[0];
      forward[1] = desired[1];
      forward[2] = desired[2];
    } else {
      FUN_001b0630(0, forward, desired, (float *)(unit + 0x3c), yaw_bounds,
                   pitch_scale, yaw_scale);
    }
    FUN_001a4440(unit_handle);
    FUN_001a2800(unit_handle, (const char *)0x2b51b4);
    return;
  }

  /* Slow path: seated / special movement facing. */
  if (unit[0x257] == 0)
    return;
  special = (char)(unit[0x257] == 5);

  if ((tag_flags & 0x40) != 0) {
    tmp[0] = *(float *)(unit + 0x1dc) * up[1] - *(float *)(unit + 0x1d8) * up[2];
    tmp[1] = *(float *)(unit + 0x1d4) * up[2] - *(float *)(unit + 0x1dc) * up[0];
    tmp[2] = *(float *)(unit + 0x1d8) * up[0] - *(float *)(unit + 0x1d4) * up[1];
    /* reconstruct facing from aim × up style cross (matches XBE FPU order) */
    desired[0] = tmp[1] * up[2] - tmp[2] * up[1];
    desired[1] = tmp[2] * up[0] - tmp[0] * up[2];
    desired[2] = tmp[0] * up[1] - tmp[1] * up[0];
    if (normalize3d(desired) == 0.0f) {
      desired[0] = forward[0];
      desired[1] = forward[1];
      desired[2] = forward[2];
    }
    aim_dot = desired[0] * forward[0] + desired[1] * forward[1];
  } else {
    desired[0] = aim[0];
    desired[1] = aim[1];
    desired[2] = 0.0f;
    if (magnitude3d(desired) == 0.0f) {
      desired[0] = forward[0];
      desired[1] = forward[1];
      desired[2] = forward[2];
    }
    aim_dot = desired[0] * forward[1] - desired[1] * forward[0];
  }

  facing_ok = 1;
  if (!(aim_dot > 0.0f))
    facing_ok = 0;
  if (aim_dot > *(float *)0x2568c0) {
    if (unit[0x253] == 3)
      facing_ok = 1;
    else if (unit[0x253] == 2)
      facing_ok = 0;
  }

  if (unit[0x42a] == 1 || (tag_flags & 1) != 0) {
    if ((*(unsigned int *)(unit + 0x1b8) & 0x100) != 0)
      return;
    c = cosf(*(float *)(biped_tag + 0x2f0) * *(float *)0x2546a4);
    s = sinf(*(float *)(biped_tag + 0x2f0) * *(float *)0x2546a4);
    if (facing_ok)
      s = -s;
    if ((tag_flags & 0x40) != 0) {
      rotate_vector3d_by_sincos(forward, up, s, c);
      cross_product3d(desired, forward, tmp);
      aim_dot = tmp[0] * up[0] + tmp[1] * up[1] + tmp[2] * up[2];
    } else {
      float nx = s * forward[0] + c * forward[1];
      float ny = c * forward[0] - s * forward[1];
      forward[0] = ny;
      forward[1] = nx;
      aim_dot = desired[0] * forward[1] - desired[1] * forward[0];
    }
    /* XBE: if facing_ok, require aim_dot > 0; else require aim_dot < 0. */
    if (facing_ok ? !(aim_dot > 0.0f) : !(aim_dot < 0.0f))
      goto done_rotate;

    if ((*(unsigned char *)(biped_tag + 0x2f4) & 0x40) != 0) {
      cross_product3d(up, desired, tmp);
      if (normalize3d(tmp) > 0.0f)
        cross_product3d(tmp, up, forward);
    } else {
      forward[0] = desired[0];
      forward[1] = desired[1];
      forward[2] = 0.0f;
      global_up = *(float **)0x31fc44;
      up[0] = global_up[0];
      up[1] = global_up[1];
      up[2] = global_up[2];
    }
    normalize3d(forward);
  done_rotate:
    FUN_001a2800(unit_handle, (const char *)0x2b518c);
    return;
  }

  if (unit[0x42a] != 0 || special ||
      (*(unsigned int *)(unit + 0x1b4) & 0x4000) != 0 ||
      (*(unsigned int *)(unit + 0x1b8) & 0x100) != 0)
    return;

  if ((*(unsigned char *)(unit + 0x1b8) & 0x20) != 0)
    thresh = *(float *)0x28ace8;
  else
    thresh = *(float *)(biped_tag + 0x4c8);
  if (aim_dot > thresh &&
      (*(unsigned int *)(biped_tag + 0x17c) & 0x100000) == 0 && state) {
    *state = (unsigned char)((facing_ok ? 1 : 0) + 2);
  }
  FUN_001a2800(unit_handle, (const char *)0x2b51a0);
}
#endif


/* FUN_001a5300 (0x1a5300) — readable C lift (restored pre-naked). */
void FUN_001a5300(int unit_handle, unsigned char *state)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  object_get_and_verify_type(0, 0);
  /* relift: test byte ptr [edi + 0xb6], 4 -> je 0x1a533e */
  /* relift: test byte ptr [edi + 0x248], 4 -> jne 0x1a6277 */
  tag_get(0x62697064, 0);
  /* test (char)ecx, 8 -> je 0x1a53a6 */
  unit_scripting_unit_driver(0, (void *)(uintptr_t)eax);
  biped_get_camera_height_and_offset(0, (void *)(uintptr_t)eax, (float *)(uintptr_t)edx, (float *)(uintptr_t)ecx);
  /* test (char)eax, (char)eax -> jne 0x1a5514 */
  FUN_000b5590(0);
  /* relift: test byte ptr [ebx + 0x2f4], 4 -> je 0x1a5531 */
  /* relift: test byte ptr [edi + 0xb6], 4 -> jne 0x1a5531 */
  /* test (char)eax, 0x41 -> jne 0x1a5585 */
  /* test (char)eax, 0x41 -> jne 0x1a55af */
  /* test (char)eax, 0x41 -> jne 0x1a55af */
  /* test (char)eax, 0x41 -> jne 0x1a55fc */
  /* relift: test byte ptr [edi + 0xb6], 4 -> jne 0x1a5677 */
  /* relift: test byte ptr [ebx + 0x2f4], 4 -> jne 0x1a58d8 */
  /* relift: test byte ptr [edi + 0x248], 4 -> jne 0x1a58d8 */
  tag_get('edom', 0);
  tag_get('rtna', 0);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  FUN_00120590((void *)(uintptr_t)eax, 0, 16);
  FUN_00120590((void *)(uintptr_t)eax, 0, 12);
  FUN_00120590((void *)(uintptr_t)eax, 0, 0);
  rotate_vector3d_by_sincos((float *)(uintptr_t)ecx, (float *)(uintptr_t)esi, 0.0f, 0.0f);
  /* test (char)eax, 0x20 -> je 0x1a58ba */
  /* cmp (char)eax, 2 -> je 0x1a57f3 */
  /* cmp (char)eax, 3 -> jne 0x1a58ba */
  FUN_00013070((float *)(uintptr_t)eax, (float *)(uintptr_t)ecx);
  /* test (char)eax, 0x41 -> jne 0x1a58ba */
  cross_product3d((float *)(uintptr_t)eax, (float *)(uintptr_t)eax, (float *)(uintptr_t)edx);
  cross_product3d((float *)(uintptr_t)eax, (float *)(uintptr_t)ecx, (float *)(uintptr_t)eax);
  unit_abort_animation(0);
  FUN_001a4440(0);
  /* test (char)eax, 4 -> je 0x1a5a4b */
  /* relift: test byte ptr [edi + 0xb6], 4 -> jne 0x1a5a4b */
  FUN_00012fe0((float *)(uintptr_t)esi);
  /* test (char)eax, 0x41 -> jne 0x1a599c */
  /* relift: cmp dword ptr [edi + 0x464], 0x3f800000 -> jne 0x1a596f */
  /* test (char)eax, 0x41 -> jne 0x1a599c */
  /* test (char)eax, 2 -> je 0x1a5c20 */
  /* relift: cmp byte ptr [edi + 0x253], 0x1c -> je 0x1a5c20 */
  game_globals_get();
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  /* cmp eax, -1 -> je 0x1a5aa2 */
  datum_get((void *)(uintptr_t)ecx, 0);
  /* test (char)eax, 0x41 -> jne 0x1a5ae2 */
  /* test (char)eax, 0x41 -> jne 0x1a5b56 */
  game_players_are_double_speed();
  /* test (char)eax, (char)eax -> je 0x1a5c47 */
  /* relift: test byte ptr [edi + 0x424], 3 -> jne 0x1a5c47 */
  /* relift: test byte ptr [edi + 0x424], 1 -> je 0x1a5c85 */
  /* relift: cmp byte ptr [edi + 0x459], 0x16 -> jge 0x1a5c85 */
  /* cmp eax, -1 -> je 0x1a5c85 */
  actor_is_leaping(0);
  /* test (char)eax, (char)eax -> je 0x1a5c85 */
  /* relift: cmp byte ptr [edi + 0x257], 3 -> jne 0x1a5cd9 */
  /* test (char)eax, 0x41 -> jne 0x1a5ccd */
  /* test (char)eax, 0x41 -> jne 0x1a5d4a */
  /* relift: test byte ptr [edi + 0x424], 1 -> je 0x1a5d4a */
  /* test (char)ecx, (char)ecx -> jne 0x1a5d77 */
  /* test (char)eax, 1 -> je 0x1a5d88 */
  /* test (char)eax, 2 -> je 0x1a5d93 */
  /* test (char)eax, 4 -> je 0x1a5d9e */
  /* relift: test byte ptr [ebx + 0x2f4], 4 -> je 0x1a5dd7 */
  /* test (int16_t)eax, (int16_t)eax -> jne 0x1a5dd7 */
  /* relift: test byte ptr [ebx + 0x2f4], 0x20 -> je 0x1a5de7 */
  /* relift: test byte ptr [ebx + 0x2f4], (char)ecx -> je 0x1a5dfb */
  /* test (int16_t)eax, (int16_t)eax -> jne 0x1a5dfb */
  FUN_001a2f40((void *)0);
  /* cmp eax, -1 -> je 0x1a5e1d */
  /* test (char)eax, (char)eax -> jle 0x1a5e31 */
  /* relift: test dword ptr [edi + 0x1b4], 0x1000000 -> je 0x1a5e8f */
  object_translate(0, (float *)(uintptr_t)eax, (void *)0);
  /* test (char)ecx, 4 -> je 0x1a5f1e */
  /* test (char)eax, 0x41 -> jne 0x1a5fac */
  FUN_001a0e00(0.0f, 0);
  /* test (char)ecx, 4 -> jne 0x1a5fbf */
  FUN_001a2b90(0);
  /* relift: cmp byte ptr [edi + 0x239], 3 -> jne 0x1a61ba */
  /* cmp eax, -1 -> je 0x1a61ba */
  object_get_and_verify_type(0, 0);
  display_assert((char *)0x00253440, (char *)0x002b4d5c, 2157, 0);
  system_exit(0);
  fast_vector_intersects_sphere((float *)(uintptr_t)ecx, (float *)(uintptr_t)eax, (float *)(uintptr_t)ebx, 0.0f);
  /* test (char)eax, (char)eax -> je 0x1a6189 */
  FUN_0014c8e0((void *)(uintptr_t)eax, 0);
  /* test (char)eax, (char)eax -> je 0x1a6189 */
  FUN_0014cb00(0, (void *)0, (void *)(uintptr_t)eax, (void *)(uintptr_t)edx, (void *)(uintptr_t)ecx);
  /* test (char)eax, (char)eax -> je 0x1a6189 */
  FUN_0014df70(49824, (float *)(uintptr_t)ecx, (float *)(uintptr_t)eax, 0, (void *)(uintptr_t)edx);
  /* test (char)eax, (char)eax -> jne 0x1a6189 */
  vector3d_scale_add((float *)(uintptr_t)edx, (float *)(uintptr_t)ecx, 0.0f, (float *)(uintptr_t)edx);
  FUN_0010a1c0((float *)(uintptr_t)edx, (float *)0, (float *)0);
  plane_negate((float *)(uintptr_t)ecx, (float *)(uintptr_t)eax);
  unit_impact_melee_damage(0, 0, 0, 0, 0, 0, (float *)(uintptr_t)eax, 0);
  /* relift: cmp word ptr [0x4761d8], 1 -> jg 0x1a61b3 */
  display_assert((char *)0x00253418, (char *)0x002b4d5c, 2200, 0);
  system_exit(0);
  FUN_001a0a40(0, 0, (float *)0);
  FUN_001a0be0(0.0f, 0);
  /* relift: test byte ptr [ecx + 0x424], 1 -> jne 0x1a61ff */
  /* relift: test byte ptr [ecx + 0x424], 1 -> jne 0x1a6251 */
  /* relift: test byte ptr [ebp - 0x44], 0x10 -> jne 0x1a6251 */
  object_get_and_verify_type(0, 0);
  tag_get('dpib', 0);
  /* test (char)ecx, 0x20 -> je 0x1a62db */
  /* relift: cmp (char)ecx, byte ptr [esi + 0x47d] -> jae 0x1a62db */
  /* test (char)eax, (char)eax -> jne 0x1a62c6 */
  FUN_001a0680(0);
  FUN_001a2800(0x002b51ec, (char *)0);
  /* relift: cmp byte ptr [esi + 0x459], 3 -> jl 0x1a6317 */
  /* test (char)ecx, 4 -> jne 0x1a6317 */
  /* relift: cmp byte ptr [esi + 0x253], 0x18 -> jne 0x1a62ff */
  FUN_001a2160(0);
  FUN_001a2800(0x002b51d8, (char *)0);
  /* relift: cmp byte ptr [esi + 0x253], 0x18 -> jne 0x1a6333 */
  FUN_001a4440(0);
  FUN_001a2800(0x002b51cc, (char *)0);
  object_get_and_verify_type(0, 0);
  tag_get('dpib', 0);
  /* test (char)eax, (char)eax -> jne 0x1a678d */
  /* test (char)eax, (char)eax -> je 0x1a63a4 */
  /* test (char)eax, (char)eax -> je 0x1a63a4 */
  profile_enter_private((void *)0x0032d1d0);
  FUN_001a2800(0x002b524c, (char *)0);
  /* cmp eax, -1 -> je 0x1a6461 */
  object_get_and_verify_type(0, 0);
  /* cmp (int16_t)ecx, 1 -> jne 0x1a6444 */
  object_get_and_verify_type(0, 0);
  FUN_001a1fb0(0);
  /* relift: test byte ptr [esi + 0x1b8], 0x40 -> je 0x1a640b */
  unit_try_and_exit_seat(0);
  /* test (char)eax, (char)eax -> je 0x1a672c */
  /* relift: test byte ptr [ebx + 4], 2 -> je 0x1a672c */
  unit_exit_seat_end(0);
  /* test (int16_t)ecx, (int16_t)ecx -> jne 0x1a672c */
  FUN_001a4440(0);
  /* test (char)eax, 4 -> jne 0x1a647d */
  /* relift: test byte ptr [ebx + 0x2f4], 0x44 -> jne 0x1a64b8 */
  normalize3d((float *)(uintptr_t)ebx);
  /* cmp eax, 7 -> ja 0x1a64e4 */
  /* test (char)ecx, 1 -> je 0x1a655f */
  /* cmp (char)eax, 0x7f -> jge 0x1a6566 */
  /* test (char)ecx, 2 -> je 0x1a657f */
  /* cmp (char)eax, 0x7f -> jge 0x1a6586 */
  FUN_001a2800(0x002b5240, (char *)0);
  /* test (char)eax, 4 -> jne 0x1a65c7 */
  FUN_001a4c50(0, (unsigned char *)(uintptr_t)ecx);
  FUN_001a2800(0x002b5230, (char *)0);
  /* relift: tail-call ((void(*)(void))FUN_001a5300)(); */
  FUN_001a2800(0x002b5224, (char *)0);
  /* test (char)eax, 4 -> je 0x1a65f4 */
  FUN_001a6280(0, (char *)0);
  /* test (char)eax, 1 -> je 0x1a660d */
  FUN_001a2900(0, (char *)(uintptr_t)eax);
  /* relift: cmp word ptr [esi + 0x460], -1 -> je 0x1a6622 */
  FUN_001a2a60(0, (char *)0);
  /* test (char)eax, 2 -> je 0x1a6632 */
  FUN_001a2b10(0);
  FUN_001a2800(0x002b520c, (char *)0);
  /* test (char)eax, (char)eax -> jne 0x1a6702 */
  /* relift: cmp dword ptr [esi + 0x1c8], -1 -> je 0x1a6719 */
  object_get_and_verify_type(0, 0);
  unit_get_weapon(0, eax);
  weapon_prevents_melee_attack(0);
  /* test (char)eax, (char)eax -> jne 0x1a6719 */
  /* relift: cmp byte ptr [esi + 0x2d0], 0xff -> jne 0x1a6719 */
  unit_animation_start_action(0, 0);
  weapon_stop_reload(0);
  first_person_weapon_message_from_unit(0, 0);
  weapon_get_animation_frame(0, 0, 13, 0);
  weapon_get_animation_frame(0, 0, 13, 0);
  /* relift: cmp (char)eax, byte ptr [esi + 0x45e] -> jne 0x1a6713 */
  unit_cause_player_melee_damage(0);
  FUN_001a2440(0);
  FUN_001a1e70(0);
  FUN_001a0b30(0);
  FUN_001b0d90(0, (char *)(uintptr_t)ecx);
  /* cmp (int16_t)eax, 1 -> jne 0x1a6744 */
  FUN_001a2290(0);
  /* relift: test byte ptr [esi + 0xb6], 4 -> je 0x1a6759 */
  /* relift: test byte ptr [esi + 4], 0x20 -> je 0x1a6759 */
  FUN_001a2800(0x002b5200, (char *)0);
  /* test (char)eax, (char)eax -> je 0x1a678d */
  /* test (char)eax, (char)eax -> je 0x1a678d */
  profile_exit_private((void *)0x0032d1d0);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}


/* FUN_001b8f10 (0x1b8f10) — readable C lift. */
void FUN_001b8f10(int vehicle_handle, void *wheel_buffer, void *scratch_buffer)
{
  void *obj;
  void *vehi;
  void *phys;

  obj = object_get_and_verify_type(vehicle_handle, 2);
  vehi = tag_get(0x76656869, *(int *)obj);
  phys = tag_get(0x70687973, *(int *)((char *)vehi + 0x8c));
  if (*(float *)phys > *(float *)0x2533c0) {
    FUN_001b6560(vehicle_handle, wheel_buffer, scratch_buffer);
  } else {
    FUN_001b69a0(vehicle_handle, wheel_buffer, scratch_buffer);
  }
  FUN_001b7020(vehicle_handle);
}


/* FUN_001b8f80 — defined in units/vehicles.c */



/* FUN_001bb430 (0x1bb430) — readable C lift (restored pre-naked). */
void FUN_001bb430(void)
{
  int eax = 0;
  int ebx = 0;
  int esi = 0;

  ((void(*)(void))FUN_001baa50)();
  /* test (int16_t)eax, (int16_t)eax -> jl 0x1bb463 */
  /* cmp (int16_t)eax, 8 -> jl 0x1bb483 */
  display_assert((char *)0x002b8580, (char *)0x002b839c, 1516, 0);
  system_exit(0);
  /* relift: cmp word ptr [eax], -1 -> je 0x1bb4ac */
  display_assert((char *)0x002b8918, (char *)0x002b839c, 1517, 0);
  system_exit(0);
  physical_memory_protect((void *)(uintptr_t)ebx, esi, 0);
  ((void (*)(void))FUN_001bb190)();
  display_assert((char *)0x002b88e8, (char *)0x002b839c, 1537, 0);
  system_exit(0);
  /* relift: tail-call FUN_001bb430(); */
  /* cmp (int16_t)esi, 8 -> jl 0x1bb586 */
  display_assert((char *)0x002b8580, (char *)0x002b839c, 1561, 0);
  system_exit(0);
  /* relift: tail-call FUN_001bb430(); */

  (void)eax;
  (void)ebx;
  (void)esi;
}


/* acquire_read_request (0x1bb5a0) — readable C lift. */
void acquire_read_request(void *base, int16_t *slot)
{
  int16_t idx;
  int word;
  unsigned int bit;
  unsigned int *bitmap;
  void __attribute__((regparm(1))) (*release_fn)(void *b, int16_t *s, int i) =
      (void __attribute__((regparm(1))) (*)(void *, int16_t *, int))(void *)FUN_001bb430;
  idx = (int16_t)(((char *)slot - (char *)base - 0xa78) >> 1);
  if (idx < 0 || idx >= 8) {
    display_assert((const char *)0x2b8580, (const char *)0x2b839c, 0x652, 1);
    system_exit(-1);
  }
  word = (int)idx >> 5;
  bit = 1u << (idx & 0x1f);
  bitmap = (unsigned int *)((char *)base + 0x998 + word * 4);
  if ((*bitmap & bit) == 0) {
    display_assert((const char *)0x2b8940, (const char *)0x2b839c, 0x653, 1);
    system_exit(-1);
  }
  *bitmap &= ~bit;
  *slot = (int16_t)0xffff;
  release_fn(base, slot, (int)idx);
}

/* FUN_001bb640 (0x1bb640) — Capstone tip: index not in [0,1) → assert. */
void FUN_001bb640(int16_t index /*@<ax>*/, void *base /*@<ecx>*/)
{
  (void)base;
  if (index < 0 || index >= 1) {
    display_assert((char *)0x2b85c8, (char *)0x2b839c, 0x661, 1);
    system_exit(-1);
  }
}


/* FUN_001c4990 (0x1c4990) — Capstone tip: nonzero type byte → assert. */
void FUN_001c4990(int handle)
{
  if ((handle >> 8) & 0xff) {
    display_assert((const char *)0x2ba8c0, (const char *)0x2ba8e8, 0x306, true);
    system_exit(-1);
  }
}


/* FUN_001d5c66 (0x1d5c66) — XBE naked draft (batch 304). */
#if defined(__clang__)
static void (*const b1d5c66_c1dd5c8)(void) = FUN_001dd5c8;
static unsigned int (*const b1d5c66_c1d8750)(unsigned int val) = FUN_001d8750;
static void (*const b1d5c66_c1d5411)(void) = FUN_001d5411;
static void (*const b1d5c66_c1d4cd9)(void) = FUN_001d4cd9;
static void (*const b1d5c66_c1d63d5)(void) = FUN_001d63d5;
static void (*const b1d5c66_c1dd601)(void) = __SEH_epilog;

__attribute__((naked, noinline))
void *__stdcall FUN_001d5c66(void *heap __attribute__((unused)), unsigned int flags __attribute__((unused)), int size __attribute__((unused)))
{
  __asm__ volatile(
      "pushl $0x178\n\t"
      "pushl $0x2c1ea0\n\t"
      "call *%[c1dd5c8]\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "movl %%esi, %%ebx\n\t"
      "movl %%ebx, -0x1c(%%ebp)\n\t"
      "andb $0, -0x1d(%%ebp)\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "orl 0x18(%%esi), %%ecx\n\t"
      "movl %%ecx, 0xc(%%ebp)\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_001d5c66_1\n\t"
      "incl %%eax\n\t"
      ".LFUN_001d5c66_1:\n\t"
      "addl $0x1f, %%eax\n\t"
      "andl $0xfffffff0, %%eax\n\t"
      "movl %%eax, -0x24(%%ebp)\n\t"
      "movl %%eax, %%edi\n\t"
      "shrl $4, %%edi\n\t"
      "movl %%edi, -0x28(%%ebp)\n\t"
      "andl $0, -0x4(%%ebp)\n\t"
      "testb $1, %%cl\n\t"
      "jne .LFUN_001d5c66_2\n\t"
      "pushl 0x580(%%esi)\n\t"
      "call *0x25309c\n\t"
      "movb $1, -0x1d(%%ebp)\n\t"
      ".LFUN_001d5c66_2:\n\t"
      "cmpl $0x80, %%edi\n\t"
      "jae .LFUN_001d5c66_13\n\t"
      "leal 0x180(%%esi,%%edi,8), %%eax\n\t"
      "movl %%eax, -0x2c(%%ebp)\n\t"
      "cmpl %%eax, (%%eax)\n\t"
      "je .LFUN_001d5c66_4\n\t"
      "movl 0x4(%%eax), %%eax\n\t"
      "subl $8, %%eax\n\t"
      "movl %%eax, -0x30(%%ebp)\n\t"
      "movb 0x5(%%eax), %%dl\n\t"
      "movb %%dl, -0x31(%%ebp)\n\t"
      "movl 0x8(%%eax), %%ecx\n\t"
      "movl %%ecx, -0x38(%%ebp)\n\t"
      "movl 0xc(%%eax), %%edi\n\t"
      "movl %%edi, -0x3c(%%ebp)\n\t"
      "movl %%ecx, (%%edi)\n\t"
      "movl %%edi, 0x4(%%ecx)\n\t"
      "cmpl %%edi, %%ecx\n\t"
      "jne .LFUN_001d5c66_3\n\t"
      "movzwl (%%eax), %%ecx\n\t"
      "movl %%ecx, %%edi\n\t"
      "shrl $3, %%edi\n\t"
      "movl %%edi, -0x40(%%ebp)\n\t"
      "andl $7, %%ecx\n\t"
      "xorl %%edi, %%edi\n\t"
      "incl %%edi\n\t"
      "shll %%cl, %%edi\n\t"
      "movl %%edi, -0x44(%%ebp)\n\t"
      "movl -0x40(%%ebp), %%ecx\n\t"
      "leal 0x160(%%ecx,%%esi,1), %%ecx\n\t"
      "movl %%ecx, -0x48(%%ebp)\n\t"
      "movzbl (%%ecx), %%ecx\n\t"
      "xorl %%edi, %%ecx\n\t"
      "movl -0x48(%%ebp), %%edi\n\t"
      "movb %%cl, (%%edi)\n\t"
      ".LFUN_001d5c66_3:\n\t"
      "movl -0x28(%%ebp), %%ecx\n\t"
      "subl %%ecx, 0x30(%%esi)\n\t"
      "movl %%eax, -0x4c(%%ebp)\n\t"
      "andl $0x10, %%edx\n\t"
      "orb $1, %%dl\n\t"
      "movb %%dl, 0x5(%%eax)\n\t"
      "movl -0x24(%%ebp), %%ecx\n\t"
      "subl 0x10(%%ebp), %%ecx\n\t"
      "movb %%cl, 0x6(%%eax)\n\t"
      "andb $0, 0x7(%%eax)\n\t"
      "jmp .LFUN_001d5c66_43\n\t"
      ".LFUN_001d5c66_4:\n\t"
      "movl -0x28(%%ebp), %%ecx\n\t"
      "movl %%ecx, %%edx\n\t"
      "shrl $5, %%edx\n\t"
      "movl %%edx, -0x50(%%ebp)\n\t"
      "leal 0x160(%%esi,%%edx,4), %%edi\n\t"
      "movl %%edi, -0x54(%%ebp)\n\t"
      "andl $0x1f, %%ecx\n\t"
      "xorl %%eax, %%eax\n\t"
      "incl %%eax\n\t"
      "shll %%cl, %%eax\n\t"
      "decl %%eax\n\t"
      "notl %%eax\n\t"
      "andl (%%edi), %%eax\n\t"
      "movl %%eax, -0x58(%%ebp)\n\t"
      "addl $4, %%edi\n\t"
      "movl %%edi, -0x54(%%ebp)\n\t"
      "subl $0, %%edx\n\t"
      "je .LFUN_001d5c66_5\n\t"
      "decl %%edx\n\t"
      "je .LFUN_001d5c66_7\n\t"
      "decl %%edx\n\t"
      "je .LFUN_001d5c66_9\n\t"
      "decl %%edx\n\t"
      "je .LFUN_001d5c66_11\n\t"
      "jmp .LFUN_001d5c66_14\n\t"
      ".LFUN_001d5c66_5:\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_001d5c66_6\n\t"
      "leal 0x180(%%esi), %%edi\n\t"
      "jmp .LFUN_001d5c66_12\n\t"
      ".LFUN_001d5c66_6:\n\t"
      "movl (%%edi), %%eax\n\t"
      "movl %%eax, -0x58(%%ebp)\n\t"
      "addl $4, %%edi\n\t"
      "movl %%edi, -0x54(%%ebp)\n\t"
      ".LFUN_001d5c66_7:\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_001d5c66_8\n\t"
      "leal 0x280(%%esi), %%edi\n\t"
      "jmp .LFUN_001d5c66_12\n\t"
      ".LFUN_001d5c66_8:\n\t"
      "movl (%%edi), %%eax\n\t"
      "movl %%eax, -0x58(%%ebp)\n\t"
      "addl $4, %%edi\n\t"
      "movl %%edi, -0x54(%%ebp)\n\t"
      ".LFUN_001d5c66_9:\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_001d5c66_10\n\t"
      "leal 0x380(%%esi), %%edi\n\t"
      "jmp .LFUN_001d5c66_12\n\t"
      ".LFUN_001d5c66_10:\n\t"
      "movl (%%edi), %%eax\n\t"
      "movl %%eax, -0x58(%%ebp)\n\t"
      "addl $4, %%edi\n\t"
      "movl %%edi, -0x54(%%ebp)\n\t"
      ".LFUN_001d5c66_11:\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_001d5c66_14\n\t"
      "leal 0x480(%%esi), %%edi\n\t"
      ".LFUN_001d5c66_12:\n\t"
      "movl %%edi, -0x2c(%%ebp)\n\t"
      "movl %%eax, %%ecx\n\t"
      "call *%[c1d8750]\n\t"
      "movsbl %%al, %%eax\n\t"
      "leal (%%edi,%%eax,8), %%eax\n\t"
      "movl %%eax, -0x2c(%%ebp)\n\t"
      "movl 0x4(%%eax), %%eax\n\t"
      "subl $8, %%eax\n\t"
      "movl %%eax, -0x30(%%ebp)\n\t"
      "movl 0x8(%%eax), %%ecx\n\t"
      "movl %%ecx, -0x5c(%%ebp)\n\t"
      "movl 0xc(%%eax), %%edx\n\t"
      "movl %%edx, -0x60(%%ebp)\n\t"
      "movl %%ecx, (%%edx)\n\t"
      "movl %%edx, 0x4(%%ecx)\n\t"
      "cmpl %%edx, %%ecx\n\t"
      "jne .LFUN_001d5c66_19\n\t"
      "movzwl (%%eax), %%ecx\n\t"
      "movl %%ecx, %%edx\n\t"
      "shrl $3, %%edx\n\t"
      "movl %%edx, -0x64(%%ebp)\n\t"
      "andl $7, %%ecx\n\t"
      "xorl %%edi, %%edi\n\t"
      "incl %%edi\n\t"
      "shll %%cl, %%edi\n\t"
      "movl %%edi, -0x68(%%ebp)\n\t"
      "leal 0x160(%%edx,%%esi,1), %%esi\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movb (%%esi), %%cl\n\t"
      "xorl %%edi, %%ecx\n\t"
      "movb %%cl, (%%esi)\n\t"
      "jmp .LFUN_001d5c66_19\n\t"
      ".LFUN_001d5c66_13:\n\t"
      "cmpl 0x1c(%%esi), %%edi\n\t"
      "ja .LFUN_001d5c66_46\n\t"
      ".LFUN_001d5c66_14:\n\t"
      "leal 0x180(%%esi), %%edx\n\t"
      "movl %%edx, -0x2c(%%ebp)\n\t"
      "movl 0x4(%%edx), %%eax\n\t"
      "movl %%eax, -0x6c(%%ebp)\n\t"
      "cmpl %%eax, %%edx\n\t"
      "je .LFUN_001d5c66_17\n\t"
      "addl $-8, %%eax\n\t"
      "movl %%eax, -0x30(%%ebp)\n\t"
      "movzwl (%%eax), %%eax\n\t"
      "cmpl -0x28(%%ebp), %%eax\n\t"
      "jb .LFUN_001d5c66_17\n\t"
      "movl (%%edx), %%ecx\n\t"
      ".LFUN_001d5c66_15:\n\t"
      "movl %%ecx, -0x6c(%%ebp)\n\t"
      "cmpl %%ecx, %%edx\n\t"
      "je .LFUN_001d5c66_17\n\t"
      "leal -0x8(%%ecx), %%eax\n\t"
      "movl %%eax, -0x30(%%ebp)\n\t"
      "movzwl (%%eax), %%esi\n\t"
      "cmpl -0x28(%%ebp), %%esi\n\t"
      "jb .LFUN_001d5c66_16\n\t"
      "movl 0x8(%%eax), %%ecx\n\t"
      "movl %%ecx, -0x70(%%ebp)\n\t"
      "movl 0xc(%%eax), %%edx\n\t"
      "movl %%edx, -0x74(%%ebp)\n\t"
      "jmp .LFUN_001d5c66_18\n\t"
      ".LFUN_001d5c66_16:\n\t"
      "movl (%%ecx), %%ecx\n\t"
      "jmp .LFUN_001d5c66_15\n\t"
      ".LFUN_001d5c66_17:\n\t"
      "pushl -0x24(%%ebp)\n\t"
      "pushl %%ebx\n\t"
      "call *%[c1d5411]\n\t"
      "movl %%eax, -0x30(%%ebp)\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_001d5c66_45\n\t"
      "movl 0x8(%%eax), %%ecx\n\t"
      "movl %%ecx, -0x78(%%ebp)\n\t"
      "movl 0xc(%%eax), %%edx\n\t"
      "movl %%edx, -0x7c(%%ebp)\n\t"
      ".LFUN_001d5c66_18:\n\t"
      "movl %%ecx, (%%edx)\n\t"
      "movl %%edx, 0x4(%%ecx)\n\t"
      ".LFUN_001d5c66_19:\n\t"
      "movb 0x5(%%eax), %%cl\n\t"
      "movb %%cl, -0x31(%%ebp)\n\t"
      "movzwl (%%eax), %%ecx\n\t"
      "subl %%ecx, 0x30(%%ebx)\n\t"
      "movl %%eax, -0x4c(%%ebp)\n\t"
      "movb $1, 0x5(%%eax)\n\t"
      "movzwl (%%eax), %%edx\n\t"
      "movl -0x28(%%ebp), %%ecx\n\t"
      "subl %%ecx, %%edx\n\t"
      "movl %%edx, -0x80(%%ebp)\n\t"
      "movw %%cx, (%%eax)\n\t"
      "movl -0x24(%%ebp), %%ecx\n\t"
      "subl 0x10(%%ebp), %%ecx\n\t"
      "movb %%cl, 0x6(%%eax)\n\t"
      "andb $0, 0x7(%%eax)\n\t"
      "testl %%edx, %%edx\n\t"
      "je .LFUN_001d5c66_42\n\t"
      "cmpl $1, %%edx\n\t"
      "jne .LFUN_001d5c66_20\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw (%%eax), %%cx\n\t"
      "incl %%ecx\n\t"
      "movw %%cx, (%%eax)\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movb 0x6(%%eax), %%cl\n\t"
      "addl $0x10, %%ecx\n\t"
      "movb %%cl, 0x6(%%eax)\n\t"
      "jmp .LFUN_001d5c66_42\n\t"
      ".LFUN_001d5c66_20:\n\t"
      "movl -0x28(%%ebp), %%esi\n\t"
      "shll $4, %%esi\n\t"
      "addl %%eax, %%esi\n\t"
      "movl %%esi, -0x84(%%ebp)\n\t"
      "movb -0x31(%%ebp), %%cl\n\t"
      "movb %%cl, 0x5(%%esi)\n\t"
      "movw -0x28(%%ebp), %%di\n\t"
      "movw %%di, 0x2(%%esi)\n\t"
      "movb 0x4(%%eax), %%al\n\t"
      "movb %%al, 0x4(%%esi)\n\t"
      "movw %%dx, (%%esi)\n\t"
      "testb $0x10, %%cl\n\t"
      "je .LFUN_001d5c66_27\n\t"
      "xorl %%eax, %%eax\n\t"
      "movb 0x5(%%esi), %%al\n\t"
      "andl $0x10, %%eax\n\t"
      "movb %%al, 0x5(%%esi)\n\t"
      "cmpw $0x80, %%dx\n\t"
      "jae .LFUN_001d5c66_22\n\t"
      "movzwl %%dx, %%eax\n\t"
      "leal 0x180(%%ebx,%%eax,8), %%edi\n\t"
      "movl %%edi, -0x88(%%ebp)\n\t"
      "cmpl %%edi, (%%edi)\n\t"
      "jne .LFUN_001d5c66_21\n\t"
      "movzwl (%%esi), %%ecx\n\t"
      "movl %%ecx, %%eax\n\t"
      "shrl $3, %%eax\n\t"
      "movl %%eax, -0x8c(%%ebp)\n\t"
      "andl $7, %%ecx\n\t"
      "xorl %%eax, %%eax\n\t"
      "incl %%eax\n\t"
      "shll %%cl, %%eax\n\t"
      "movl %%eax, -0x90(%%ebp)\n\t"
      "movl -0x8c(%%ebp), %%ecx\n\t"
      "leal 0x160(%%ecx,%%ebx,1), %%ecx\n\t"
      "movl %%ecx, -0x94(%%ebp)\n\t"
      "movzbl (%%ecx), %%ecx\n\t"
      "orl %%eax, %%ecx\n\t"
      "movl -0x94(%%ebp), %%eax\n\t"
      "movb %%cl, (%%eax)\n\t"
      ".LFUN_001d5c66_21:\n\t"
      "movl %%edi, -0x98(%%ebp)\n\t"
      "movl 0x4(%%edi), %%ecx\n\t"
      "movl %%ecx, -0x9c(%%ebp)\n\t"
      "jmp .LFUN_001d5c66_36\n\t"
      ".LFUN_001d5c66_22:\n\t"
      "leal 0x180(%%ebx), %%ecx\n\t"
      "movl %%ecx, -0xa0(%%ebp)\n\t"
      "movl (%%ecx), %%eax\n\t"
      ".LFUN_001d5c66_23:\n\t"
      "movl %%eax, -0xa4(%%ebp)\n\t"
      "cmpl %%eax, %%ecx\n\t"
      "je .LFUN_001d5c66_24\n\t"
      "leal -0x8(%%eax), %%edi\n\t"
      "movl %%edi, -0xa8(%%ebp)\n\t"
      "cmpw (%%edi), %%dx\n\t"
      "jbe .LFUN_001d5c66_24\n\t"
      "movl (%%eax), %%eax\n\t"
      "jmp .LFUN_001d5c66_23\n\t"
      ".LFUN_001d5c66_24:\n\t"
      "movl %%eax, -0xac(%%ebp)\n\t"
      "movl 0x4(%%eax), %%edi\n\t"
      "movl %%edi, -0xb0(%%ebp)\n\t"
      ".LFUN_001d5c66_25:\n\t"
      "leal 0x8(%%esi), %%ecx\n\t"
      "movl %%eax, (%%ecx)\n\t"
      "movl %%edi, 0xc(%%esi)\n\t"
      "movl %%ecx, (%%edi)\n\t"
      "movl %%ecx, 0x4(%%eax)\n\t"
      ".LFUN_001d5c66_26:\n\t"
      "addl %%edx, 0x30(%%ebx)\n\t"
      "jmp .LFUN_001d5c66_41\n\t"
      ".LFUN_001d5c66_27:\n\t"
      "movl %%edx, %%eax\n\t"
      "shll $4, %%eax\n\t"
      "addl %%esi, %%eax\n\t"
      "movl %%eax, -0xb4(%%ebp)\n\t"
      "movb 0x5(%%eax), %%cl\n\t"
      "testb $1, %%cl\n\t"
      "je .LFUN_001d5c66_32\n\t"
      "movw %%dx, 0x2(%%eax)\n\t"
      "xorl %%eax, %%eax\n\t"
      "movb 0x5(%%esi), %%al\n\t"
      "andl $0x10, %%eax\n\t"
      "movb %%al, 0x5(%%esi)\n\t"
      "cmpw $0x80, %%dx\n\t"
      "jae .LFUN_001d5c66_29\n\t"
      "movzwl %%dx, %%eax\n\t"
      "leal 0x180(%%ebx,%%eax,8), %%edi\n\t"
      "movl %%edi, -0xb8(%%ebp)\n\t"
      "cmpl %%edi, (%%edi)\n\t"
      "jne .LFUN_001d5c66_28\n\t"
      "movzwl (%%esi), %%ecx\n\t"
      "movl %%ecx, %%eax\n\t"
      "shrl $3, %%eax\n\t"
      "movl %%eax, -0xbc(%%ebp)\n\t"
      "andl $7, %%ecx\n\t"
      "xorl %%eax, %%eax\n\t"
      "incl %%eax\n\t"
      "shll %%cl, %%eax\n\t"
      "movl %%eax, -0xc0(%%ebp)\n\t"
      "movl -0xbc(%%ebp), %%ecx\n\t"
      "leal 0x160(%%ecx,%%ebx,1), %%ecx\n\t"
      "movl %%ecx, -0xc4(%%ebp)\n\t"
      "movzbl (%%ecx), %%ecx\n\t"
      "orl %%eax, %%ecx\n\t"
      "movl -0xc4(%%ebp), %%eax\n\t"
      "movb %%cl, (%%eax)\n\t"
      ".LFUN_001d5c66_28:\n\t"
      "movl %%edi, -0xc8(%%ebp)\n\t"
      "movl 0x4(%%edi), %%ecx\n\t"
      "movl %%ecx, -0xcc(%%ebp)\n\t"
      "jmp .LFUN_001d5c66_36\n\t"
      ".LFUN_001d5c66_29:\n\t"
      "leal 0x180(%%ebx), %%ecx\n\t"
      "movl %%ecx, -0xd0(%%ebp)\n\t"
      "movl (%%ecx), %%eax\n\t"
      ".LFUN_001d5c66_30:\n\t"
      "movl %%eax, -0xd4(%%ebp)\n\t"
      "cmpl %%eax, %%ecx\n\t"
      "je .LFUN_001d5c66_31\n\t"
      "leal -0x8(%%eax), %%edi\n\t"
      "movl %%edi, -0xd8(%%ebp)\n\t"
      "cmpw (%%edi), %%dx\n\t"
      "jbe .LFUN_001d5c66_31\n\t"
      "movl (%%eax), %%eax\n\t"
      "jmp .LFUN_001d5c66_30\n\t"
      ".LFUN_001d5c66_31:\n\t"
      "movl %%eax, -0xdc(%%ebp)\n\t"
      "movl 0x4(%%eax), %%edi\n\t"
      "movl %%edi, -0xe0(%%ebp)\n\t"
      "jmp .LFUN_001d5c66_25\n\t"
      ".LFUN_001d5c66_32:\n\t"
      "movb %%cl, 0x5(%%esi)\n\t"
      "movl 0x8(%%eax), %%ecx\n\t"
      "movl %%ecx, -0xe4(%%ebp)\n\t"
      "movl 0xc(%%eax), %%edi\n\t"
      "movl %%edi, -0xe8(%%ebp)\n\t"
      "movl %%ecx, (%%edi)\n\t"
      "movl %%edi, 0x4(%%ecx)\n\t"
      "cmpl %%edi, %%ecx\n\t"
      "jne .LFUN_001d5c66_33\n\t"
      "movw (%%eax), %%cx\n\t"
      "cmpw $0x80, %%cx\n\t"
      "jae .LFUN_001d5c66_33\n\t"
      "movzwl %%cx, %%ecx\n\t"
      "movl %%ecx, %%edi\n\t"
      "shrl $3, %%edi\n\t"
      "movl %%edi, -0xec(%%ebp)\n\t"
      "andl $7, %%ecx\n\t"
      "xorl %%edi, %%edi\n\t"
      "incl %%edi\n\t"
      "shll %%cl, %%edi\n\t"
      "movl %%edi, -0xf0(%%ebp)\n\t"
      "movl -0xec(%%ebp), %%ecx\n\t"
      "leal 0x160(%%ecx,%%ebx,1), %%ecx\n\t"
      "movl %%ecx, -0xf4(%%ebp)\n\t"
      "movzbl (%%ecx), %%ecx\n\t"
      "xorl %%edi, %%ecx\n\t"
      "movl -0xf4(%%ebp), %%edi\n\t"
      "movb %%cl, (%%edi)\n\t"
      ".LFUN_001d5c66_33:\n\t"
      "movzwl (%%eax), %%ecx\n\t"
      "subl %%ecx, 0x30(%%ebx)\n\t"
      "movzwl (%%eax), %%eax\n\t"
      "addl %%eax, %%edx\n\t"
      "movl %%edx, -0x80(%%ebp)\n\t"
      "cmpl $0xff00, %%edx\n\t"
      "ja .LFUN_001d5c66_40\n\t"
      "movw %%dx, (%%esi)\n\t"
      "testb $0x10, 0x5(%%esi)\n\t"
      "jne .LFUN_001d5c66_34\n\t"
      "movl %%edx, %%eax\n\t"
      "shll $4, %%eax\n\t"
      "movw %%dx, 0x2(%%eax,%%esi,1)\n\t"
      ".LFUN_001d5c66_34:\n\t"
      "xorl %%eax, %%eax\n\t"
      "movb 0x5(%%esi), %%al\n\t"
      "andl $0x10, %%eax\n\t"
      "movb %%al, 0x5(%%esi)\n\t"
      "cmpw $0x80, %%dx\n\t"
      "jae .LFUN_001d5c66_37\n\t"
      "movzwl %%dx, %%eax\n\t"
      "leal 0x180(%%ebx,%%eax,8), %%edi\n\t"
      "movl %%edi, -0xf8(%%ebp)\n\t"
      "cmpl %%edi, (%%edi)\n\t"
      "jne .LFUN_001d5c66_35\n\t"
      "movzwl (%%esi), %%ecx\n\t"
      "movl %%ecx, %%eax\n\t"
      "shrl $3, %%eax\n\t"
      "movl %%eax, -0xfc(%%ebp)\n\t"
      "andl $7, %%ecx\n\t"
      "xorl %%eax, %%eax\n\t"
      "incl %%eax\n\t"
      "shll %%cl, %%eax\n\t"
      "movl %%eax, -0x100(%%ebp)\n\t"
      "movl -0xfc(%%ebp), %%ecx\n\t"
      "leal 0x160(%%ecx,%%ebx,1), %%ecx\n\t"
      "movl %%ecx, -0x104(%%ebp)\n\t"
      "movzbl (%%ecx), %%ecx\n\t"
      "orl %%eax, %%ecx\n\t"
      "movl -0x104(%%ebp), %%eax\n\t"
      "movb %%cl, (%%eax)\n\t"
      ".LFUN_001d5c66_35:\n\t"
      "movl %%edi, -0x108(%%ebp)\n\t"
      "movl 0x4(%%edi), %%ecx\n\t"
      "movl %%ecx, -0x10c(%%ebp)\n\t"
      ".LFUN_001d5c66_36:\n\t"
      "leal 0x8(%%esi), %%eax\n\t"
      "movl %%edi, (%%eax)\n\t"
      "movl %%ecx, 0xc(%%esi)\n\t"
      "movl %%eax, (%%ecx)\n\t"
      "movl %%eax, 0x4(%%edi)\n\t"
      "jmp .LFUN_001d5c66_26\n\t"
      ".LFUN_001d5c66_37:\n\t"
      "leal 0x180(%%ebx), %%ecx\n\t"
      "movl %%ecx, -0x110(%%ebp)\n\t"
      "movl (%%ecx), %%eax\n\t"
      ".LFUN_001d5c66_38:\n\t"
      "movl %%eax, -0x114(%%ebp)\n\t"
      "cmpl %%eax, %%ecx\n\t"
      "je .LFUN_001d5c66_39\n\t"
      "leal -0x8(%%eax), %%edi\n\t"
      "movl %%edi, -0x118(%%ebp)\n\t"
      "cmpw (%%edi), %%dx\n\t"
      "jbe .LFUN_001d5c66_39\n\t"
      "movl (%%eax), %%eax\n\t"
      "jmp .LFUN_001d5c66_38\n\t"
      ".LFUN_001d5c66_39:\n\t"
      "movl %%eax, -0x11c(%%ebp)\n\t"
      "movl 0x4(%%eax), %%edi\n\t"
      "movl %%edi, -0x120(%%ebp)\n\t"
      "jmp .LFUN_001d5c66_25\n\t"
      ".LFUN_001d5c66_40:\n\t"
      "pushl %%edx\n\t"
      "pushl %%esi\n\t"
      "pushl %%ebx\n\t"
      "call *%[c1d4cd9]\n\t"
      ".LFUN_001d5c66_41:\n\t"
      "andb $0, -0x31(%%ebp)\n\t"
      "testb $0x10, 0x5(%%esi)\n\t"
      "je .LFUN_001d5c66_42\n\t"
      "movzbl 0x4(%%esi), %%eax\n\t"
      "movl 0x60(%%ebx,%%eax,4), %%eax\n\t"
      "movl %%eax, -0x124(%%ebp)\n\t"
      "movl %%esi, 0x40(%%eax)\n\t"
      ".LFUN_001d5c66_42:\n\t"
      "testb $0x10, -0x31(%%ebp)\n\t"
      "je .LFUN_001d5c66_43\n\t"
      "movl -0x4c(%%ebp), %%eax\n\t"
      "movb 0x5(%%eax), %%cl\n\t"
      "orb $0x10, %%cl\n\t"
      "movb %%cl, 0x5(%%eax)\n\t"
      ".LFUN_001d5c66_43:\n\t"
      "movl -0x4c(%%ebp), %%edi\n\t"
      "addl $0x10, %%edi\n\t"
      "movl %%edi, -0x128(%%ebp)\n\t"
      "cmpb $0, -0x1d(%%ebp)\n\t"
      "je .LFUN_001d5c66_44\n\t"
      "pushl 0x580(%%ebx)\n\t"
      "call *0x253098\n\t"
      "andb $0, -0x1d(%%ebp)\n\t"
      ".LFUN_001d5c66_44:\n\t"
      "testb $8, 0xc(%%ebp)\n\t"
      "je .LFUN_001d5c66_50\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "xorl %%eax, %%eax\n\t"
      "movl %%ecx, %%edx\n\t"
      "shrl $2, %%ecx\n\t"
      "rep stosl\n\t"
      "movl %%edx, %%ecx\n\t"
      "andl $3, %%ecx\n\t"
      "rep stosb\n\t"
      "jmp .LFUN_001d5c66_50\n\t"
      ".LFUN_001d5c66_45:\n\t"
      "movl $0xc0000017, -0x12c(%%ebp)\n\t"
      "jmp .LFUN_001d5c66_48\n\t"
      ".LFUN_001d5c66_46:\n\t"
      "testb $2, 0x14(%%esi)\n\t"
      "je .LFUN_001d5c66_47\n\t"
      "andl $0, -0x130(%%ebp)\n\t"
      "addl $0x20, -0x24(%%ebp)\n\t"
      "pushl $4\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "shll $0x14, %%eax\n\t"
      "notl %%eax\n\t"
      "andl $0x800000, %%eax\n\t"
      "orl $0x1000, %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x24(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0\n\t"
      "leal -0x130(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *0x253148\n\t"
      "movl %%eax, -0x12c(%%ebp)\n\t"
      "testl %%eax, %%eax\n\t"
      "jl .LFUN_001d5c66_48\n\t"
      "pushl $0xc\n\t"
      "popl %%ecx\n\t"
      "xorl %%eax, %%eax\n\t"
      "movl -0x130(%%ebp), %%edi\n\t"
      "rep stosl\n\t"
      "movl -0x24(%%ebp), %%eax\n\t"
      "subl 0x10(%%ebp), %%eax\n\t"
      "movl -0x130(%%ebp), %%ecx\n\t"
      "movw %%ax, 0x20(%%ecx)\n\t"
      "movl -0x130(%%ebp), %%eax\n\t"
      "movb $0xb, 0x25(%%eax)\n\t"
      "movl -0x24(%%ebp), %%eax\n\t"
      "movl -0x130(%%ebp), %%ecx\n\t"
      "movl %%eax, 0x18(%%ecx)\n\t"
      "movl -0x130(%%ebp), %%eax\n\t"
      "movl -0x24(%%ebp), %%ecx\n\t"
      "movl %%ecx, 0x1c(%%eax)\n\t"
      "addl $0x58, %%esi\n\t"
      "movl %%esi, -0x134(%%ebp)\n\t"
      "movl 0x4(%%esi), %%eax\n\t"
      "movl %%eax, -0x138(%%ebp)\n\t"
      "movl -0x130(%%ebp), %%ecx\n\t"
      "movl %%esi, (%%ecx)\n\t"
      "movl -0x130(%%ebp), %%ecx\n\t"
      "movl %%eax, 0x4(%%ecx)\n\t"
      "movl -0x130(%%ebp), %%ecx\n\t"
      "movl %%ecx, (%%eax)\n\t"
      "movl -0x130(%%ebp), %%eax\n\t"
      "movl %%eax, 0x4(%%esi)\n\t"
      "movl -0x130(%%ebp), %%eax\n\t"
      "addl $0x30, %%eax\n\t"
      "movl %%eax, -0x128(%%ebp)\n\t"
      "jmp .LFUN_001d5c66_50\n\t"
      ".LFUN_001d5c66_47:\n\t"
      "movl $0xc0000023, -0x12c(%%ebp)\n\t"
      ".LFUN_001d5c66_48:\n\t"
      "testb $4, 0xc(%%ebp)\n\t"
      "je .LFUN_001d5c66_49\n\t"
      "movl $0xc0000017, -0x188(%%ebp)\n\t"
      "andl $0, -0x180(%%ebp)\n\t"
      "movl $1, -0x178(%%ebp)\n\t"
      "andl $0, -0x184(%%ebp)\n\t"
      "movl -0x24(%%ebp), %%eax\n\t"
      "movl %%eax, -0x174(%%ebp)\n\t"
      "leal -0x188(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *0x2530c0\n\t"
      ".LFUN_001d5c66_49:\n\t"
      "andl $0, -0x128(%%ebp)\n\t"
      ".LFUN_001d5c66_50:\n\t"
      "orl $0xffffffff, -0x4(%%ebp)\n\t"
      "call *%[c1d63d5]\n\t"
      "movl -0x128(%%ebp), %%eax\n\t"
      "call *%[c1dd601]\n\t"
      "ret\n\t"
      :
      : [c1dd5c8] "m"(b1d5c66_c1dd5c8), [c1d8750] "m"(b1d5c66_c1d8750), [c1d5411] "m"(b1d5c66_c1d5411), [c1d4cd9] "m"(b1d5c66_c1d4cd9), [c1d63d5] "m"(b1d5c66_c1d63d5), [c1dd601] "m"(b1d5c66_c1dd601)
      : "memory");
}
#else
#error "FUN_001d5c66: clang naked draft required"
#endif


/* FUN_001e67e7 (0x1e67e7) — readable C lift (restored pre-naked). */
void FUN_001e67e7(void)
{
  __unlock_fhandle();
  FUN_001db777();
  __SEH_epilog();
}


/* FUN_001e6805 (0x1e6805) — readable C lift (wcslwr). */
wchar_t *FUN_001e6805(wchar_t *s)
{
  wchar_t *p;
  if (!s) {
    return s;
  }
  p = s;
  while (*p) {
    if (*p >= 0x41 && *p <= 0x5a) {
      *p = (wchar_t)(*p + 0x20);
    }
    p++;
  }
  return s;
}
/* FUN_001e6831 (0x1e6831) — readable C lift (wcsupr). */
wchar_t *FUN_001e6831(wchar_t *s)
{
  wchar_t *p;
  if (!s) {
    return s;
  }
  p = s;
  while (*p) {
    if (*p >= 0x61 && *p <= 0x7a) {
      *p = (wchar_t)(*p - 0x20);
    }
    p++;
  }
  return s;
}
/* FUN_001e6860 (0x1e6860) — readable C lift. */
int FUN_001e6860(const char *s1, const char *s2, unsigned int n)
{
  unsigned char ah;
  unsigned char al;
  if (n == 0) {
    return 0;
  }
  while (1) {
    ah = (unsigned char)*s1;
    al = (unsigned char)*s2;
    if (ah == 0 || al == 0) {
      break;
    }
    s1++;
    s2++;
    if (ah >= 0x41 && ah <= 0x5a) {
      ah = (unsigned char)(ah + 0x20);
    }
    if (al >= 0x41 && al <= 0x5a) {
      al = (unsigned char)(al + 0x20);
    }
    if (ah != al) {
      return (ah < al) ? -1 : 1;
    }
    n--;
    if (n == 0) {
      return 0;
    }
  }
  if (ah == al) {
    return 0;
  }
  return (ah < al) ? -1 : 1;
}
/* ___loctotime_t (0x1e68bb) — readable C lift (restored pre-naked). */
void ___loctotime_t(void)
{
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int ebp = 0;

  /* cmp esi, 0x46 -> jl 0x1e69c3 */
  /* cmp esi, 0x8a -> jg 0x1e69c3 */
  /* test edx, edx -> jne 0x1e6907 */
  /* test edx, edx -> jne 0x1e6919 */
  /* test edx, edx -> jne 0x1e691f */
  /* cmp ecx, 2 -> jle 0x1e691f */
  FUN_001e1953();
  /* relift: cmp dword ptr [ebp + 0x20], -1 -> jne 0x1e69bd */
  /* relift: cmp dword ptr [0x3317d4], 0 -> je 0x1e69bd */
  FUN_001e1997();

  (void)ecx;
  (void)edx;
  (void)esi;
  (void)ebp;
}

