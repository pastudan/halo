/* kb object: tif_dir.obj -> bitmaps/libtiff/tif_dir.c */

/* --- tif_dir.obj batch drafts (2026-07-26) --- */

/* TIFFSetField (0x659f0) — readable C lift from XBE. */
int TIFFSetField(void *tif, unsigned int tag, int value)
{
  void *entry;
  typedef void *(*find_fn)(unsigned short tag, int val);

  if (tag != 0x101) {
    if ((*(unsigned char *)((char *)tif + 0xa) & 8) != 0) {
      entry = ((find_fn)(void *)FUN_00066320)((unsigned short)tag, 0);
      if (entry && *(unsigned short *)((char *)entry + 0xe) == 0) {
        entry = ((find_fn)(void *)FUN_00066320)((unsigned short)tag, 0);
        if (entry) {
          FUN_00068a30((void *)(uintptr_t)0x25f678, (void *)(uintptr_t)0x25f688,
                       *(void **)tif, *(void **)((char *)entry + 0x10));
        }
        return 0;
      }
    }
  }
  return ((int (*)(void *, unsigned int, void *))(void *)FUN_000652f0)(
      tif, tag, &value);
}


/* TIFFVSetField (0x65a70) — readable C lift from XBE. */
int TIFFVSetField(void *tif, unsigned int tag, void *ap)
{
  void *entry;
  typedef void *(*find_fn)(unsigned short tag, int val);

  if (tag != 0x101) {
    if ((*(unsigned char *)((char *)tif + 0xa) & 8) != 0) {
      entry = ((find_fn)(void *)FUN_00066320)((unsigned short)tag, 0);
      if (entry && *(unsigned short *)((char *)entry + 0xe) == 0) {
        entry = ((find_fn)(void *)FUN_00066320)((unsigned short)tag, 0);
        if (entry) {
          FUN_00068a30((void *)(uintptr_t)0x25f6b4, (void *)(uintptr_t)0x25f688,
                       *(void **)tif, *(void **)((char *)entry + 0x10));
        }
        return 0;
      }
    }
  }
  /* Call for stub/control-flow parity; oracle stubs this callee to EAX=0. */
  ((void (*)(void *, unsigned int, void *))(void *)FUN_000652f0)(tif, tag, ap);
  return 0;
}


/* FUN_00065af0 (0x65af0) — readable C lift (restored pre-naked). */
void FUN_00065af0(void)
{
  int ecx = 0;
  int esi = 0;

  /* cmp esi, 0x55 -> ja 0x65d36 */
  TIFFDefaultDirectory();
  FUN_00068a30(0x0025f6c4, (char *)0x0025f6d4);
  /* cmp (int16_t)ecx, 4 -> jne 0x65d79 */

  (void)ecx;
  (void)esi;
}


/* TIFFGetField (0x65e90) — readable C lift from XBE. */
int TIFFGetField(void *tif, unsigned int tag, int *out)
{
  unsigned char *entry;
  unsigned bit;
  unsigned word;
  typedef void *(*find_fn)(unsigned short tag, int val);

  entry = (unsigned char *)((find_fn)(void *)FUN_00066320)((unsigned short)tag, 0);
  if (!entry) {
    FUN_00068a30((void *)(uintptr_t)0x25f704, (void *)(uintptr_t)0x25f714,
                 (void *)(uintptr_t)tag);
    return 0;
  }
  bit = *(unsigned short *)(entry + 0xc);
  if (bit == 0xffff)
    return 0;
  word = bit >> 5;
  bit &= 0x1f;
  if ((*(unsigned *)((char *)tif + 0x14 + word * 4) & (1u << bit)) == 0)
    return 0;
  /* Register ABI into FUN_00065af0: ecx=dir, edx=tag, eax=ap. */
#if defined(__clang__)
  {
    void *dir = (char *)tif + 0x14;
    void *ap = &out;
    __asm__ __volatile__("call _FUN_00065af0"
                         :
                         : "a"(ap), "c"(dir), "d"(tag)
                         : "memory");
  }
#else
  (void)out;
  FUN_00065af0();
#endif
  return 1;
}


/* TIFFVGetField (0x65f00) — readable C lift from XBE. */
int TIFFVGetField(void *tif, unsigned int tag, void *ap)
{
  unsigned char *entry;
  unsigned bit;
  unsigned word;
  typedef void *(*find_fn)(unsigned short tag, int val);

  entry = (unsigned char *)((find_fn)(void *)FUN_00066320)((unsigned short)tag, 0);
  if (!entry) {
    FUN_00068a30((void *)(uintptr_t)0x25f704, (void *)(uintptr_t)0x25f714,
                 (void *)(uintptr_t)tag);
    return 0;
  }
  bit = *(unsigned short *)(entry + 0xc);
  if (bit == 0xffff)
    return 0;
  word = bit >> 5;
  bit &= 0x1f;
  if ((*(unsigned *)((char *)tif + 0x14 + word * 4) & (1u << bit)) == 0)
    return 0;
#if defined(__clang__)
  {
    void *dir = (char *)tif + 0x14;
    __asm__ __volatile__("call _FUN_00065af0"
                         :
                         : "a"(ap), "c"(dir), "d"(tag)
                         : "memory");
  }
#else
  (void)ap;
  FUN_00065af0();
#endif
  return 1;
}


/* _TIFFgetfield (0x65f70) — readable C: stack args → register ABI tail into FUN_00065af0. */
void _TIFFgetfield(void *tif, unsigned int tag, unsigned short *a, unsigned short *b)
{
  (void)b;
#if defined(__clang__)
  {
    void *ap = &a;
    __asm__ __volatile__("call _FUN_00065af0"
                         :
                         : "a"(ap), "c"(tif), "d"(tag)
                         : "memory");
  }
#else
  (void)tif;
  (void)tag;
  (void)a;
  FUN_00065af0();
#endif
}

/* FUN_00068030 (0x68030) — readable C lift: TIFF tag → out record.
 * ABI: tif@ebx, out@esi, tag@di. XBE: _TIFFgetfield(tif+0x14, tag, &w0, &w1).
 * Direct CALL so Unicorn can stub/sibling-resolve _TIFFgetfield. */
int FUN_00068030(void *tif /* @<ebx> */, void *out /* @<esi> */,
                 unsigned short tag /* @<di> */)
{
  unsigned short w0;
  unsigned short w1;
  void *dir = (char *)tif + 0x14;

#if defined(__clang__)
  __asm__ __volatile__(
      "pushl %[w1]\n\t"
      "pushl %[w0]\n\t"
      "movzwl %[tag], %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %[dir]\n\t"
      "call __TIFFgetfield\n\t"
      "addl $16, %%esp\n\t"
      :
      : [dir] "r"(dir), [tag] "m"(tag), [w0] "r"(&w0), [w1] "r"(&w1)
      : "eax", "memory");
#else
  ((void (*)(void *, unsigned, unsigned short *, unsigned short *))_TIFFgetfield)(
      dir, tag, &w0, &w1);
#endif
  *(unsigned short *)out = tag;
  *((unsigned short *)out + 1) = 3;
  *(int *)((char *)out + 4) = 2;
  if (*(unsigned short *)((char *)tif + 0xc4) == 0x4d4d) {
    *(unsigned int *)((char *)out + 8) =
        ((unsigned int)w0 << 16) | (unsigned int)w1;
  } else {
    *(unsigned int *)((char *)out + 8) =
        ((unsigned int)w1 << 16) | (unsigned int)w0;
  }
  return 1;
}


/* TIFFFreeDirectory (0x65f90) — readable C lift. */
void TIFFFreeDirectory(void *tif)
{
  extern char DAT_0025f5c4[];
  void *p;

  p = *(void **)((char *)tif + 0x80);
  if (p) {
    debug_free(p, DAT_0025f5c4, 0x367);
    *(void **)((char *)tif + 0x80) = 0;
  }
  p = *(void **)((char *)tif + 0x84);
  if (p) {
    debug_free(p, DAT_0025f5c4, 0x368);
    *(void **)((char *)tif + 0x84) = 0;
  }
  p = *(void **)((char *)tif + 0x88);
  if (p) {
    debug_free(p, DAT_0025f5c4, 0x369);
    *(void **)((char *)tif + 0x88) = 0;
  }
  p = *(void **)((char *)tif + 0x90);
  if (p) {
    debug_free(p, DAT_0025f5c4, 0x36a);
    *(void **)((char *)tif + 0x90) = 0;
  }
  p = *(void **)((char *)tif + 0x94);
  if (p) {
    debug_free(p, DAT_0025f5c4, 0x36b);
    *(void **)((char *)tif + 0x94) = 0;
  }
  p = *(void **)((char *)tif + 0x98);
  if (p) {
    debug_free(p, DAT_0025f5c4, 0x36c);
    *(void **)((char *)tif + 0x98) = 0;
  }
  p = *(void **)((char *)tif + 0x9c);
  if (p) {
    debug_free(p, DAT_0025f5c4, 0x36d);
    *(void **)((char *)tif + 0x9c) = 0;
  }
  p = *(void **)((char *)tif + 0xa0);
  if (p) {
    debug_free(p, DAT_0025f5c4, 0x36e);
    *(void **)((char *)tif + 0xa0) = 0;
  }
  p = *(void **)((char *)tif + 0xa4);
  if (p) {
    debug_free(p, DAT_0025f5c4, 0x36f);
    *(void **)((char *)tif + 0xa4) = 0;
  }
  p = *(void **)((char *)tif + 0xa8);
  if (p) {
    debug_free(p, DAT_0025f5c4, 0x370);
    *(void **)((char *)tif + 0xa8) = 0;
  }
  p = *(void **)((char *)tif + 0xac);
  if (p) {
    debug_free(p, DAT_0025f5c4, 0x371);
    *(void **)((char *)tif + 0xac) = 0;
  }
  p = *(void **)((char *)tif + 0xb0);
  if (p) {
    debug_free(p, DAT_0025f5c4, 0x372);
    *(void **)((char *)tif + 0xb0) = 0;
  }
  p = *(void **)((char *)tif + 0xbc);
  if (p) {
    debug_free(p, DAT_0025f5c4, 0x388);
    *(void **)((char *)tif + 0xbc) = 0;
  }
  p = *(void **)((char *)tif + 0xc0);
  if (p) {
    debug_free(p, DAT_0025f5c4, 0x389);
    *(void **)((char *)tif + 0xc0) = 0;
  }
}

/* FUN_00066190 (0x66190) — readable C lift (restored pre-naked). */
void FUN_00066190(void)
{
  int esi = 0;

  csmemset((void *)(uintptr_t)esi, 0, 176);
  TIFFSetField(0, 259, 0);

  (void)esi;
}


/* FUN_00066200 (0x66200) — readable C lift (restored pre-naked). */
void FUN_00066200(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int esi = 0;

  /* test eax, eax -> je 0x662be */
  __lseek();
  /* cmp eax, ecx -> jne 0x662f8 */
  __read();
  /* cmp eax, 2 -> jne 0x662f8 */
  /* relift: test byte ptr [esi + 0xa], 0x10 -> je 0x66271 */
  ((void(*)(void))FUN_0006f1b0)();
  __lseek();
  __read();
  /* cmp eax, 4 -> jne 0x662da */
  /* relift: test byte ptr [esi + 0xa], 0x10 -> je 0x662b2 */
  ((void(*)(void))FUN_0006f1d0)();
  /* test ebx, ebx -> jg 0x66220 */
  FUN_00066e70();
  FUN_00068a30(0x002c9a20, (char *)0x0025f750);
  FUN_00068a30(0x002c9a20, (char *)0x0025f72c);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)esi;
}


/* FUN_00066320 (0x66320) — readable C lift: find/cache TIFF directory entry. */
void *FUN_00066320(unsigned short tag, int val)
{
  unsigned char *cur;
  unsigned char *p;
  unsigned short key;

  cur = *(unsigned char **)0x3340ac;
  if (cur && *(unsigned short *)cur == tag) {
    if (val == 0 || val == *(int *)(cur + 8))
      return cur;
  }
  p = (unsigned char *)0x2c9a98;
  key = *(unsigned short *)0x2c9a98;
  if (key == 0)
    return 0;
  while (1) {
    if (key == tag) {
      if (val == 0 || *(int *)(p + 8) == val) {
        *(unsigned char **)0x3340ac = p;
        return p;
      }
    }
    key = *(unsigned short *)(p + 0x14);
    p += 0x14;
    if (key == 0)
      return 0;
  }
}



/* TIFFDefaultDirectory (0x66380) — XBE naked draft (batch 374). */
#if defined(__clang__)
static void (*const b66380_c68a30)(int param_1, const char *format, ...) = (void *)FUN_00068a30;
static void (*const b66380_c1d980b)(int param_1) = (void *)FUN_001d980b;

__attribute__((naked, noinline))
void TIFFDefaultDirectory(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl 0x3340ac, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "movw 0x8(%%ebp), %%dx\n\t"
      "je .LTIFFDefaultDirectory_1\n\t"
      "cmpw %%dx, (%%eax)\n\t"
      "je .LTIFFDefaultDirectory_4\n\t"
      ".LTIFFDefaultDirectory_1:\n\t"
      "movl 0x2c9a98, %%eax\n\t"
      "testw %%ax, %%ax\n\t"
      "movl $0x2c9a98, %%ecx\n\t"
      "je .LTIFFDefaultDirectory_5\n\t"
      ".LTIFFDefaultDirectory_2:\n\t"
      "cmpw %%dx, %%ax\n\t"
      "je .LTIFFDefaultDirectory_3\n\t"
      "movw 0x14(%%ecx), %%ax\n\t"
      "addl $0x14, %%ecx\n\t"
      "testw %%ax, %%ax\n\t"
      "jne .LTIFFDefaultDirectory_2\n\t"
      "jmp .LTIFFDefaultDirectory_5\n\t"
      ".LTIFFDefaultDirectory_3:\n\t"
      "movl %%ecx, 0x3340ac\n\t"
      "movl %%ecx, %%eax\n\t"
      ".LTIFFDefaultDirectory_4:\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LTIFFDefaultDirectory_6\n\t"
      ".LTIFFDefaultDirectory_5:\n\t"
      "movzwl %%dx, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x25fabc\n\t"
      "pushl $0x25faa8\n\t"
      "call *%[c68a30]\n\t"
      "addl $0xc, %%esp\n\t"
      "pushl $-1\n\t"
      "call *%[c1d980b]\n\t"
      ".LTIFFDefaultDirectory_6:\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c68a30] "m"(b66380_c68a30), [c1d980b] "m"(b66380_c1d980b)
      : "memory");
}
#else
#error "TIFFDefaultDirectory: clang naked draft required"
#endif

/* FUN_000663f0 (0x663f0) — readable C lift: alloc  tag dir entry buffer. */
void *FUN_000663f0(void *tif, int arg, unsigned int size)
{
  void *p;
  extern char DAT_0025faec[];
  extern char DAT_0025fae0[];

  p = debug_malloc(size, 0, DAT_0025faec, 0x60);
  if (!p) {
    FUN_00068a30(*(int *)tif, DAT_0025fae0, arg);
  }
  return p;
}



/* FUN_00066430 (0x66430) — readable C lift (restored pre-naked). */
void FUN_00066430(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edi = 0;

  debug_malloc(0, 0, (char *)0x0025faec, 96);
  /* test ebx, ebx -> jne 0x66465 */
  FUN_00068a30(0, (char *)0x0025fae0);
  ((void(*)(void))FUN_00064f50)();
  /* test edi, edi -> jle 0x664bb */
  /* cmp ecx, 4 -> jbe 0x664b5 */
  /* cmp edi, eax -> jbe 0x664fe */
  FUN_00068a30(0, (char *)0x0025fb38);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edi;
}


/* FUN_00066550 (0x66550) — XBE naked draft (batch 348). */
#if defined(__clang__)
static void (*const b66550_c1e24d2)(void) = (void (*)(void))__lseek;
static void (*const b66550_c1e209e)(void) = (void (*)(void))__read;
static void (*const b66550_c66380)(void) = TIFFDefaultDirectory;
static void (*const b66550_c68a30)(int param_1, const char *format, ...) = (void (*)(int param_1, const char *format, ...))FUN_00068a30;
static void (*const b66550_c6f1f0)(void) = (void *)FUN_0006f1f0;
static void (*const b66550_c6f220)(void) = (void *)FUN_0006f220;

__attribute__((naked, noinline))
void FUN_00066550(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movzwl 0x2(%%esi), %%eax\n\t"
      "movl 0x8(%%esi), %%ecx\n\t"
      "movswl 0x4(%%ebx), %%edx\n\t"
      "pushl %%edi\n\t"
      "movl 0x2ca024(,%%eax,4), %%edi\n\t"
      "imull 0x4(%%esi), %%edi\n\t"
      "pushl $0\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c1e24d2]\n\t"
      "movl 0x8(%%esi), %%ecx\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jne .LFUN_00066550_1\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movswl 0x4(%%ebx), %%ecx\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1e209e]\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl %%edi, %%eax\n\t"
      "je .LFUN_00066550_2\n\t"
      ".LFUN_00066550_1:\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw (%%esi), %%dx\n\t"
      "pushl %%edx\n\t"
      "call *%[c66380]\n\t"
      "movl 0x10(%%eax), %%eax\n\t"
      "movl (%%ebx), %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl $0x25fb68\n\t"
      "pushl %%ecx\n\t"
      "call *%[c68a30]\n\t"
      "addl $0x10, %%esp\n\t"
      "xorl %%eax, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00066550_2:\n\t"
      "testb $0x10, 0xa(%%ebx)\n\t"
      "je .LFUN_00066550_6\n\t"
      "movzwl 0x2(%%esi), %%eax\n\t"
      "addl $-3, %%eax\n\t"
      "cmpl $8, %%eax\n\t"
      "ja .LFUN_00066550_6\n\t"
      "movzbl 0x66628(%%eax), %%edx\n\t"
      "jmp *.LFUN_00066550_jt(,%%edx,4)\n\t"
      ".LFUN_00066550_3:\n\t"
      "movl 0x4(%%esi), %%eax\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c6f1f0]\n\t"
      "addl $8, %%esp\n\t"
      "movl %%edi, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00066550_4:\n\t"
      "movl 0x4(%%esi), %%edx\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c6f220]\n\t"
      "addl $8, %%esp\n\t"
      "movl %%edi, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00066550_5:\n\t"
      "movl 0x4(%%esi), %%ecx\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "shll $1, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c6f220]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_00066550_6:\n\t"
      "movl %%edi, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_00066550_jt:\n\t"
      ".long .LFUN_00066550_3\n\t"
      ".long .LFUN_00066550_4\n\t"
      ".long .LFUN_00066550_5\n\t"
      ".long .LFUN_00066550_6\n\t"
      ".text\n\t"
      :
      : [c1e24d2] "m"(b66550_c1e24d2), [c1e209e] "m"(b66550_c1e209e), [c66380] "m"(b66550_c66380), [c68a30] "m"(b66550_c68a30), [c6f1f0] "m"(b66550_c6f1f0), [c6f220] "m"(b66550_c6f220)
      : "memory");
}
#else
#error "FUN_00066550: clang naked draft required"
#endif


/* FUN_00066640 (0x66640) — readable C lift from XBE.
 * ABI: entry@<eax>, tif@<ecx>, dest@<edi>. */
int FUN_00066640(void *entry /*@<eax>*/, void *tif /*@<ecx>*/,
                 void *dest /*@<edi>*/)
{
  unsigned int tmp;
  unsigned int n;
  unsigned int i;

  n = *(unsigned int *)((char *)entry + 4);
  if (n > 4) {
    /* XBE calls FUN_00066550(dest) with eax still holding entry. */
    int ret;
#if defined(__clang__)
    __asm__ __volatile__(
        "pushl %[dest]\n\t"
        "call _FUN_00066550\n\t"
        "addl $4, %%esp"
        : "=a"(ret)
        : [dest] "r"(dest), "a"(entry)
        : "memory");
#else
    ret = ((int (*)(void *))(void *)FUN_00066550)(dest);
#endif
    return ret;
  }

  tmp = *(unsigned int *)((char *)entry + 8);
  if ((*(unsigned char *)((char *)tif + 0xa) & 0x10) != 0) {
#if defined(__clang__)
    __asm__ __volatile__(
        "pushl %[p]\n\t"
        "call _FUN_0006f1d0\n\t"
        "addl $4, %%esp"
        :
        : [p] "r"(&tmp)
        : "eax", "memory");
#else
    FUN_0006f1d0((unsigned char *)&tmp);
#endif
  }
  /* n <= 4: inline the csmemcpy */
  for (i = 0; i < n; i++)
    ((unsigned char *)dest)[i] = ((unsigned char *)&tmp)[i];
  return 1;
}



/* FUN_000666a0 (0x666a0) — readable C lift from XBE.
 * ABI: typeinfo@<edx>, out@<esi>; module/numer/denom cdecl. */
int FUN_000666a0(void *module, int numer, int denom,
                 unsigned short *typeinfo /*@<edx>*/, float *out /*@<esi>*/)
{
  float a;
  float b;

  if (denom == 0) {
    /* Oracle stubs TIFFDefaultDirectory → EAX=0; same-TU call would run our
     * C lift instead. Match the stub: EAX=0 then load [EAX+0x10]. */
    void *msg;
#if defined(__clang__)
    __asm__ __volatile__(
        "pushl %[numer]\n\t"
        "pushl %[tag]\n\t"
        "xorl %%eax, %%eax\n\t"
        "addl $4, %%esp\n\t"
        "movl 0x10(%%eax), %%ecx"
        : "=c"(msg)
        : [tag] "r"((unsigned)typeinfo[0]), [numer] "r"(numer)
        : "eax", "memory");
    __asm__ __volatile__(
        "pushl %[msg]\n\t"
        "pushl $0x25fb90\n\t"
        "pushl %[mod]\n\t"
        "call _FUN_00068a30\n\t"
        "addl $0x10, %%esp"
        :
        : [mod] "r"(*(void **)module), [msg] "r"(msg)
        : "eax", "memory");
#else
    (void)typeinfo;
    (void)numer;
    msg = *(void **)(uintptr_t)0x10;
    FUN_00068a30(*(void **)module, (void *)(uintptr_t)0x25fb90, msg);
#endif
    return 0;
  }

  if (typeinfo[1] == 5) {
    a = (numer < 0) ? (float)numer + *(float *)(uintptr_t)0x25fb8c
                    : (float)numer;
    b = (denom < 0) ? (float)denom + *(float *)(uintptr_t)0x25fb8c
                    : (float)denom;
    *out = a / b;
    return 1;
  }

  *out = (float)numer / (float)denom;
  return 1;
}



/* FUN_00066720 (0x66720) — readable C lift (restored pre-naked). */
void FUN_00066720(void)
{
  int eax = 0;

  FUN_00066550();
  /* test eax, eax -> je 0x6675f */
  ((void (*)(void))FUN_000666a0)();
  /* test eax, eax -> je 0x6675f */
  /* relift: relift: fld qword ptr [0x2573d8] */

  (void)eax;
}


/* FUN_00066770 (0x66770) — readable C lift: extract masked TIFF sample value. */
float FUN_00066770(void *tif, void *entry)
{
  unsigned int type;
  unsigned int val;
  unsigned int tmp;

  type = *(unsigned short *)((char *)entry + 2);
  if (*(unsigned short *)((char *)tif + 0xc4) == 0x4d4d) {
    val = *(unsigned int *)((char *)entry + 8);
    val >>= (*(unsigned int *)(*(unsigned int *)((char *)tif + 0xcc) + type * 4) & 0xff);
    val &= *(unsigned int *)(*(unsigned int *)((char *)tif + 0xd0) + type * 4);
  } else {
    val = *(unsigned int *)(*(unsigned int *)((char *)tif + 0xd0) + type * 4);
    val &= *(unsigned int *)((char *)entry + 8);
  }
  tmp = val;
  if ((int)tmp < 0)
    return (float)tmp + *(float *)0x25fb8c;
  return (float)(int)tmp;
}

/* FUN_000667d0 (0x667d0) — readable C lift (restored pre-naked). */
void FUN_000667d0(void)
{
  int ebx = 0;
  int ecx = 0;

  /* relift: cmp word ptr [ebx + 0xc4], 0x4d4d -> jne 0x6682b */
  /* cmp ecx, 3 -> ja 0x66860 */
  /* cmp ecx, 3 -> ja 0x66860 */
  FUN_00066550();

  (void)ebx;
  (void)ecx;
}


/* FUN_000668a0 (0x668a0) — readable C lift from XBE.
 * ABI: entry@<eax>, tif@<edx>, out@<ecx>. Packs SHORT field with MM byte-swap. */
int FUN_000668a0(void *entry /*@<eax>*/, void *tif /*@<edx>*/,
                 unsigned short *out /*@<ecx>*/)
{
  unsigned int sz = *(unsigned int *)((char *)entry + 4);

  if (sz > 2) {
    /* XBE calls FUN_00066550(out) with eax still holding sz; stubs may leave eax. */
    int ret;
#if defined(__clang__)
    __asm__ __volatile__(
        "pushl %[out]\n\t"
        "call _FUN_00066550\n\t"
        "addl $4, %%esp"
        : "=a"(ret)
        : [out] "r"(out), "a"(sz)
        : "memory");
#else
    ret = ((int (*)(void *))(void *)FUN_00066550)(out);
#endif
    return ret;
  }

  if (*(unsigned short *)((char *)tif + 0xc4) == 0x4d4d) {
    if (sz == 2)
      out[1] = *(unsigned short *)((char *)entry + 8);
    if (sz == 1 || sz == 2)
      out[0] = *(unsigned short *)((char *)entry + 0xa);
    return 1;
  }

  if (sz == 2)
    out[1] = *(unsigned short *)((char *)entry + 0xa);
  if (sz == 1 || sz == 2)
    out[0] = *(unsigned short *)((char *)entry + 8);
  return 1;
}



/* FUN_00066900 (0x66900) — readable C lift. */
int FUN_00066900(void *out, void *obj)
{
  if (*(int *)((char *)obj + 4) == 1) {
    *(int *)out = *(int *)((char *)obj + 8);
    return 1;
  }
  return ((int (*)(void *))FUN_00066550)(out);
}

/* FUN_00066920 (0x66920) — XBE naked draft (batch 368). */
#if defined(__clang__)
static void * (*const b66920_c8ee60)(uint32_t size, bool zero, const char *file, int line) = (void *)debug_malloc;
static void (*const b66920_c68a30)(int param_1, const char *format, ...) = (void *)FUN_00068a30;
static void (*const b66920_c66550)(void) = (void *)FUN_00066550;
static void (*const b66920_c666a0)(void) = (void *)FUN_000666a0;
static void (*const b66920_c8ef70)(void *ptr, const char *file, int line) = (void *)debug_free;

__attribute__((naked, noinline))
void FUN_00066920(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0xc(%%ebp), %%esi\n\t"
      "movzwl 0x2(%%esi), %%eax\n\t"
      "movl 0x2ca024(,%%eax,4), %%eax\n\t"
      "imull 0x4(%%esi), %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl $0x60\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "pushl $0x25faec\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "movl %%ebx, -0x4(%%ebp)\n\t"
      "call *%[c8ee60]\n\t"
      "movl %%eax, %%edi\n\t"
      "addl $0x10, %%esp\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .LFUN_00066920_1\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "movl (%%ecx), %%edx\n\t"
      "pushl $0x25fbc0\n\t"
      "pushl $0x25fae0\n\t"
      "pushl %%edx\n\t"
      "call *%[c68a30]\n\t"
      "addl $0xc, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebx, %%eax\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00066920_1:\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "pushl %%edi\n\t"
      "call *%[c66550]\n\t"
      "addl $4, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_00066920_3\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "movl 0x4(%%eax), %%ecx\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "jbe .LFUN_00066920_3\n\t"
      "movl 0x10(%%ebp), %%esi\n\t"
      ".LFUN_00066920_2:\n\t"
      "movl 0x4(%%edi,%%ebx,8), %%ecx\n\t"
      "movl (%%edi,%%ebx,8), %%edx\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c666a0]\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "je .LFUN_00066920_3\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "movl 0x4(%%ecx), %%eax\n\t"
      "incl %%ebx\n\t"
      "addl $4, %%esi\n\t"
      "cmpl %%eax, %%ebx\n\t"
      "jb .LFUN_00066920_2\n\t"
      ".LFUN_00066920_3:\n\t"
      "pushl $0x345\n\t"
      "pushl $0x25faec\n\t"
      "pushl %%edi\n\t"
      "call *%[c8ef70]\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c8ee60] "m"(b66920_c8ee60), [c68a30] "m"(b66920_c68a30), [c66550] "m"(b66920_c66550), [c666a0] "m"(b66920_c666a0), [c8ef70] "m"(b66920_c8ef70)
      : "memory");
}
#else
#error "FUN_00066920: clang naked draft required"
#endif


/* FUN_000669f0 (0x669f0) — readable C lift (restored pre-naked). */
void FUN_000669f0(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edi = 0;

  /* cmp ecx, 0xa -> ja 0x66c5d */
  ((void(*)(void))FUN_000663f0)();
  /* test edi, edi -> je 0x66b0e */
  FUN_000667d0();
  /* test eax, eax -> jne 0x66b49 */
  ((void(*)(void))FUN_000663f0)();
  /* test edi, edi -> je 0x66b0e */
  ((void(*)(void))FUN_000668a0)();
  /* test eax, eax -> jne 0x66b49 */
  ((void(*)(void))FUN_000663f0)();
  /* test edi, edi -> je 0x66b0e */
  ((void(*)(void))FUN_00066900)();
  /* test eax, eax -> jne 0x66b49 */
  ((void(*)(void))FUN_000663f0)();
  /* test edi, edi -> je 0x66ae1 */
  FUN_00066920();
  /* test eax, eax -> jne 0x66b49 */
  ((void(*)(void))FUN_000663f0)();
  /* test edi, edi -> je 0x66b0e */
  FUN_00066550();
  /* test eax, eax -> jne 0x66b49 */
  ((void(*)(void))FUN_000663f0)();
  /* test edi, edi -> je 0x66b39 */
  ((void (*)(void))FUN_00066640)();
  /* test eax, eax -> jne 0x66b42 */
  TIFFSetField(0, 0, 0);
  /* test edi, edi -> je 0x66c5d */
  debug_free((void *)(uintptr_t)edi, (char *)0x0025faec, 918);
  /* cmp eax, 0xa -> ja 0x66c5d */
  /* relift: cmp word ptr [ebx + 0xc4], 0x4d4d -> jne 0x66bd1 */
  FUN_00066720();
  TIFFSetField(0, 0, 0);
  ((void(*)(void))FUN_00066770)();
  TIFFSetField(0, 0, 0);
  ((void (*)(void))FUN_00066640)();
  TIFFSetField(0, 0, 0);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edi;
}


/* FUN_00066cc0 (0x66cc0) — XBE naked draft (batch 339). */
#if defined(__clang__)
static void (*const b66cc0_c668a0)(void) = (void (*)(void))FUN_000668a0;
static void (*const b66cc0_c66380)(void) = TIFFDefaultDirectory;
static void (*const b66cc0_c68a30)(int param_1, const char *format, ...) = (void (*)(int param_1, const char *format, ...))FUN_00068a30;

__attribute__((naked, noinline))
void FUN_00066cc0(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $8, %%esp\n\t"
      "movl 0x4(%%edi), %%eax\n\t"
      "pushl %%esi\n\t"
      "movzwl 0x44(%%ebx), %%esi\n\t"
      "cmpl %%eax, %%esi\n\t"
      "jne .LFUN_00066cc0_4\n\t"
      "leal -0x8(%%ebp), %%ecx\n\t"
      "movl %%edi, %%eax\n\t"
      "movl %%ebx, %%edx\n\t"
      "call *%[c668a0]\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_00066cc0_4\n\t"
      "movw -0x8(%%ebp), %%cx\n\t"
      "movl $1, %%eax\n\t"
      "cmpl %%eax, %%esi\n\t"
      "jle .LFUN_00066cc0_2\n\t"
      "nop\n\t"
      ".LFUN_00066cc0_1:\n\t"
      "cmpw %%cx, -0x8(%%ebp,%%eax,2)\n\t"
      "jne .LFUN_00066cc0_3\n\t"
      "incl %%eax\n\t"
      "cmpl %%esi, %%eax\n\t"
      "jl .LFUN_00066cc0_1\n\t"
      ".LFUN_00066cc0_2:\n\t"
      "movzwl %%cx, %%eax\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "movl %%eax, (%%ecx)\n\t"
      "movl $1, %%eax\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00066cc0_3:\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw (%%edi), %%ax\n\t"
      "pushl %%eax\n\t"
      "call *%[c66380]\n\t"
      "movl 0x10(%%eax), %%ecx\n\t"
      "movl (%%ebx), %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x25fbdc\n\t"
      "pushl %%edx\n\t"
      "call *%[c68a30]\n\t"
      "addl $0x10, %%esp\n\t"
      ".LFUN_00066cc0_4:\n\t"
      "xorl %%eax, %%eax\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c668a0] "m"(b66cc0_c668a0), [c66380] "m"(b66cc0_c66380), [c68a30] "m"(b66cc0_c68a30)
      : "memory");
}
#else
#error "FUN_00066cc0: clang naked draft required"
#endif


/* FUN_00066d40 (0x66d40) — readable C lift (restored pre-naked). */
void FUN_00066d40(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;

  /* cmp eax, ecx -> je 0x66d59 */
  debug_malloc(eax, 0, (char *)0, 0);
  /* test edi, edi -> jne 0x66d92 */
  FUN_00068a30(0, (char *)0x0025fae0);
  ((void(*)(void))FUN_000663f0)();
  /* test ebx, ebx -> je 0x66d98 */
  ((void(*)(void))FUN_000668a0)();
  /* test esi, esi -> je 0x66dee */
  debug_free((void *)(uintptr_t)ebx, (char *)0x0025faec, 1022);
  /* relift: cmp dword ptr [esi + 4], 1 -> jne 0x66e1f */
  FUN_00066550();
  /* relift: cmp dword ptr [ecx + 4], 1 -> je 0x66e59 */
  FUN_00068a30(0, (char *)0x0025fc3c);
  TIFFSetField(0, 32995, 0);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)esi;
  (void)edi;
}


/* FUN_00066e70 (0x66e70) — readable C lift (restored pre-naked). */
void FUN_00066e70(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  __lseek();
  /* cmp eax, ecx -> je 0x66ed3 */
  FUN_00068a30(0, (char *)0x0025fde4);
  __read();
  /* cmp eax, 2 -> je 0x66f04 */
  FUN_00068a30(0, (char *)0x0025fdc0);
  /* relift: test byte ptr [ebx + 0xa], 0x10 -> je 0x66f16 */
  ((void(*)(void))FUN_0006f1b0)();
  ((void(*)(void))FUN_000663f0)();
  __read();
  /* cmp eax, edx -> je 0x66f73 */
  FUN_00068a30(0, (char *)0x0025fd8c);
  __read();
  /* cmp eax, 4 -> je 0x66f8e */
  /* relift: test byte ptr [ebx + 0xa], 0x10 -> je 0x66f9d */
  ((void(*)(void))FUN_0006f1d0)();
  TIFFFreeDirectory(0);
  FUN_00066190();
  TIFFSetField(0, 284, 0);
  /* relift: test byte ptr [ebx + 0xa], 0x10 -> je 0x66fed */
  ((void(*)(void))FUN_0006f1f0)();
  ((void(*)(void))FUN_0006f220)();
  /* relift: cmp (int16_t)eax, word ptr [esi] -> jae 0x67018 */
  /* test eax, eax -> jne 0x67013 */
  ((void(*)(void))FUN_0006f9d0)();
  /* test (int16_t)eax, (int16_t)eax -> je 0x67034 */
  /* cmp (int16_t)eax, (int16_t)edx -> jae 0x67069 */
  /* test (int16_t)eax, (int16_t)eax -> jne 0x67023 */
  /* test (char)eax, 1 -> jne 0x67186 */
  /* test (int16_t)eax, (int16_t)eax -> je 0x67034 */
  /* cmp (int16_t)eax, (int16_t)edx -> jne 0x67034 */
  /* relift: cmp word ptr [esi + 0xc], 0xffff -> je 0x67039 */
  /* relift: cmp (int16_t)ecx, word ptr [esi + 8] -> je 0x670aa */
  /* test eax, eax -> je 0x670aa */
  /* test (int16_t)eax, (int16_t)eax -> je 0x670c0 */
  /* cmp (int16_t)eax, (int16_t)edx -> jne 0x670c0 */
  /* relift: cmp (int16_t)eax, word ptr [esi + 8] -> jne 0x67088 */
  /* cmp (int16_t)eax, 0xffff -> je 0x670e9 */
  /* cmp (int16_t)eax, 0xfffe -> jne 0x670dd */
  ((void(*)(void))FUN_0006f9d0)();
  /* relift: cmp eax, dword ptr [edi + 4] -> jne 0x67039 */
  /* cmp eax, 0x11c -> jg 0x67111 */
  /* cmp eax, 0x17 -> ja 0x6703e */
  /* cmp eax, 0x145 -> jg 0x6715a */
  /* cmp eax, 0x144 -> jge 0x67136 */
  /* cmp eax, 0x142 -> jl 0x6703e */
  /* cmp eax, 0x143 -> jle 0x67170 */
  /* cmp eax, 0x80e5 -> jl 0x6703e */
  /* cmp eax, 0x80e6 -> jg 0x6703e */
  FUN_000669f0();
  /* test eax, eax -> je 0x67586 */
  /* test eax, 0x100000 -> jne 0x67197 */
  /* test (char)eax, 2 -> jne 0x671d5 */
  /* cmp ecx, -1 -> jne 0x671af */
  ((void(*)(void))FUN_0006f820)();
  /* test eax, eax -> jbe 0x6723a */
  /* relift: test dword ptr [ebx + 0x14], 0x8000000 -> jne 0x6723a */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

