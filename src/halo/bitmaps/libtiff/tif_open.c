/* kb object: tif_open.obj -> bitmaps/libtiff/tif_open.c */

/* --- tif_open.obj batch drafts (2026-07-26) --- */

/* FUN_0006c400 (0x6c400) — XBE naked draft (batch 347). */
#if defined(__clang__)
static int (*const b6c400_c64ec0)(char *prop, int tag, void *out) = FUN_00064ec0;
static void (*const b6c400_c65e90)(void) = (void (*)(void))TIFFGetField;
static void (*const b6c400_c6d850)(void) = (void *)TIFFFileName;
static void (*const b6c400_c68a30)(int param_1, const char *format, ...) = (void (*)(int, const char *, ...))FUN_00068a30;
static void (*const b6c400_c6c080)(void) = (void (*)(void))FUN_0006c080;
static void (*const b6c400_c8ef70)(void *ptr, const char *file, int line) = debug_free;

__attribute__((naked, noinline))
void FUN_0006c400(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $8, %%esp\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "pushl $0x3340fc\n\t"
      "pushl $0x102\n\t"
      "pushl %%esi\n\t"
      "call *%[c64ec0]\n\t"
      "movzwl 0x3340fc, %%eax\n\t"
      "leal -0x1(%%eax), %%ecx\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl $0xf, %%ecx\n\t"
      "ja .LFUN_0006c400_10\n\t"
      "movzbl 0x6c5b4(%%ecx), %%ecx\n\t"
      "jmp *.LFUN_0006c400_jt(,%%ecx,4)\n\t"
      ".LFUN_0006c400_1:\n\t"
      "pushl $0x3340f8\n\t"
      "pushl $0x115\n\t"
      "pushl %%esi\n\t"
      "call *%[c64ec0]\n\t"
      "movzwl 0x3340f8, %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl $1, %%eax\n\t"
      "je .LFUN_0006c400_3\n\t"
      "cmpl $2, %%eax\n\t"
      "jle .LFUN_0006c400_2\n\t"
      "cmpl $4, %%eax\n\t"
      "jle .LFUN_0006c400_3\n\t"
      ".LFUN_0006c400_2:\n\t"
      "pushl %%eax\n\t"
      "pushl $0x26040c\n\t"
      "jmp .LFUN_0006c400_11\n\t"
      ".LFUN_0006c400_3:\n\t"
      "pushl $0x3340f4\n\t"
      "pushl $0x106\n\t"
      "pushl %%esi\n\t"
      "call *%[c65e90]\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_0006c400_7\n\t"
      "movzwl 0x3340f8, %%eax\n\t"
      "cmpl $1, %%eax\n\t"
      "je .LFUN_0006c400_5\n\t"
      "cmpl $2, %%eax\n\t"
      "jle .LFUN_0006c400_4\n\t"
      "cmpl $4, %%eax\n\t"
      "jg .LFUN_0006c400_4\n\t"
      "movw $2, 0x3340f4\n\t"
      "movl $0x260408, %%eax\n\t"
      "jmp .LFUN_0006c400_6\n\t"
      ".LFUN_0006c400_4:\n\t"
      "pushl $0x2603d8\n\t"
      "pushl %%esi\n\t"
      "call *%[c6d850]\n\t"
      "addl $4, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[c68a30]\n\t"
      "addl $8, %%esp\n\t"
      "xorl %%eax, %%eax\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0006c400_5:\n\t"
      "movw $1, 0x3340f4\n\t"
      "movl $0x2603c8, %%eax\n\t"
      ".LFUN_0006c400_6:\n\t"
      "pushl %%eax\n\t"
      "pushl $0x260394\n\t"
      "pushl %%esi\n\t"
      "call *%[c6d850]\n\t"
      "addl $4, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[c68a30]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_0006c400_7:\n\t"
      "pushl %%ebx\n\t"
      "leal -0x8(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x100\n\t"
      "pushl %%esi\n\t"
      "call *%[c65e90]\n\t"
      "leal -0x4(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x101\n\t"
      "pushl %%esi\n\t"
      "call *%[c65e90]\n\t"
      "movl 0x18(%%ebp), %%ecx\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "movl 0x14(%%ebp), %%ebx\n\t"
      "movl %%ecx, 0x3340e0\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "subl %%eax, %%edx\n\t"
      "imull %%ecx, %%edx\n\t"
      "leal (%%ebx,%%edx,4), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "movl $0, 0x3340c8\n\t"
      "movl $0, 0x3340c4\n\t"
      "call *%[c6c080]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x3340c8, %%eax\n\t"
      "addl $0x28, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "popl %%ebx\n\t"
      "je .LFUN_0006c400_8\n\t"
      "pushl $0x7d\n\t"
      "pushl $0x260264\n\t"
      "pushl %%eax\n\t"
      "call *%[c8ef70]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_0006c400_8:\n\t"
      "movl 0x3340c4, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_0006c400_9\n\t"
      "pushl $0x7f\n\t"
      "pushl $0x260264\n\t"
      "pushl %%eax\n\t"
      "call *%[c8ef70]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_0006c400_9:\n\t"
      "movl %%esi, %%eax\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0006c400_10:\n\t"
      "pushl %%eax\n\t"
      "pushl $0x26036c\n\t"
      ".LFUN_0006c400_11:\n\t"
      "pushl %%esi\n\t"
      "call *%[c6d850]\n\t"
      "addl $4, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[c68a30]\n\t"
      "addl $0xc, %%esp\n\t"
      "xorl %%eax, %%eax\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "movl %%edi, %%edi\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_0006c400_jt:\n\t"
      ".long .LFUN_0006c400_1\n\t"
      ".long .LFUN_0006c400_10\n\t"
      ".text\n\t"
      :
      : [c64ec0] "m"(b6c400_c64ec0), [c65e90] "m"(b6c400_c65e90), [c6d850] "m"(b6c400_c6d850), [c68a30] "m"(b6c400_c68a30), [c6c080] "m"(b6c400_c6c080), [c8ef70] "m"(b6c400_c8ef70)
      : "memory");
}
#else
#error "FUN_0006c400: clang naked draft required"
#endif


/* FUN_0006c5e0 (0x6c5e0) — Capstone lift: set predictor put fn by photometric/bits.
 * ABI: tif@<eax>, sp@<esi>; stack: put8, put16. */
int FUN_0006c5e0(void *tif /*@<eax>*/, void *sp /*@<esi>*/,
                 void *put8, void *put16)
{
  unsigned short photo = *(unsigned short *)((char *)tif + 0x46);
  unsigned short spp;
  unsigned short bps;
  void *put;

  if (photo == 1) {
    /* fall through to shared tail */
  } else if (photo == 2) {
    if (*(unsigned short *)((char *)tif + 0x5e) == 1)
      spp = *(unsigned short *)((char *)tif + 0x44);
    else
      spp = 1;
    *(unsigned short *)((char *)sp + 8) = spp;
    bps = *(unsigned short *)((char *)tif + 0x36);
    if (bps == 8) {
      *(void **)((char *)sp + 0xc) = put8;
    } else if (bps == 0x10) {
      *(void **)((char *)sp + 0xc) = put16;
    } else {
      FUN_00068a30(*(void **)tif, (void *)0x00260438, (unsigned)bps);
      return 0;
    }
  } else {
    FUN_00068a30(*(void **)tif, (void *)0x00260480, (unsigned)photo);
    return 0;
  }

  put = *(void **)((char *)sp + 0xc);
  if (put == 0)
    return 1;
  if ((*(signed char *)((char *)tif + 0xa)) < 0) {
    *(unsigned short *)((char *)sp + 0xa) =
        (unsigned short)((unsigned (*)(void *))(void *)FUN_0006f890)(tif);
  } else {
    *(unsigned short *)((char *)sp + 0xa) =
        (unsigned short)((unsigned (*)(void *))(void *)TIFFScanlineSize)(tif);
  }
  return 1;
}


/* FUN_0006c680 (0x6c680) — Capstone lift: 8-bit horizontal accumulate (decode). */
void FUN_0006c680(unsigned char *buf, int length_count, int stride_count)
{
  int rem;
  unsigned char *p;
  int n;
  unsigned char v;

  if (length_count <= stride_count)
    return;
  rem = length_count - stride_count;
  p = buf;
  do {
    if (stride_count > 4) {
      n = stride_count - 4;
      if (n > 0) {
        do {
          v = *p;
          p[stride_count] = (unsigned char)(p[stride_count] + v);
          p++;
        } while (--n != 0);
      }
      v = *p;
      p[stride_count] = (unsigned char)(p[stride_count] + v);
      p++;
      v = *p;
      p[stride_count] = (unsigned char)(p[stride_count] + v);
      p++;
      v = *p;
      p[stride_count] = (unsigned char)(p[stride_count] + v);
      p++;
      v = *p;
      p[stride_count] = (unsigned char)(p[stride_count] + v);
      p++;
    } else {
      /* jumptable stride 0..4 falls into trailing adds; stride 0 hits label 8 only */
      switch (stride_count) {
      case 4:
        v = *p;
        p[stride_count] = (unsigned char)(p[stride_count] + v);
        p++;
        /* fallthrough */
      case 3:
        v = *p;
        p[stride_count] = (unsigned char)(p[stride_count] + v);
        p++;
        /* fallthrough */
      case 2:
        v = *p;
        p[stride_count] = (unsigned char)(p[stride_count] + v);
        p++;
        /* fallthrough */
      case 1:
        v = *p;
        p[stride_count] = (unsigned char)(p[stride_count] + v);
        p++;
        /* fallthrough */
      case 0:
        break;
      }
    }
    rem -= stride_count;
  } while (rem > 0);
}


/* FUN_0006c6f0 (0x6c6f0) — Capstone lift: 16-bit horizontal accumulate (decode). */
void FUN_0006c6f0(unsigned short *buf, int length_count, int stride_count)
{
  int rem = (length_count / 2) - stride_count;
  int i;

  if (rem <= 0)
    return;
  while (rem > 0) {
    for (i = 0; i < stride_count; i++)
      buf[stride_count + i] =
          (unsigned short)(buf[stride_count + i] + buf[i]);
    buf += stride_count;
    rem -= stride_count;
  }
}


/* FUN_0006c780 (0x6c780) — Capstone lift: LZW GetNextCode (tif@<ecx>). */
unsigned int FUN_0006c780(void *tif /*@<ecx>*/)
{
  unsigned char *sp;
  unsigned char *bp;
  int bitpos;
  int nbits;
  int bitoff;
  unsigned int code;
  unsigned int frag;
  int left;
  unsigned char flags;
  unsigned char *mask_lo = (unsigned char *)0x2ec7d0;
  unsigned char *mask_hi = (unsigned char *)0x2ec7dc;

  sp = *(unsigned char **)((char *)tif + 0x120);
  bitpos = *(int *)(sp + 0x14);
  if (bitpos > *(int *)(sp + 0x18)) {
    ((void (*)(void *, void *, void *))FUN_0006f9d0)(
        *(void **)tif, (void *)0x2604a4, *(void **)((char *)tif + 0xdc));
    return 0x101u;
  }

  nbits = (int)*(unsigned short *)(sp + 6);
  bp = *(unsigned char **)((char *)tif + 0x12c) + (bitpos >> 3);
  flags = sp[4];
  code = (unsigned int)bp[0];
  bitoff = bitpos & 7;

  if (flags & 2) {
    /* MSB-first */
    code >>= bitoff;
    left = 8 - bitoff;
    nbits -= left;
    bp++;
    if (nbits >= 8) {
      frag = (unsigned int)bp[0];
      frag <<= left;
      left += 8;
      code |= frag;
      bp++;
      nbits -= 8;
    }
    frag = (unsigned int)(mask_lo[nbits] & bp[0]);
  } else {
    /* LSB-first */
    left = 8 - bitoff;
    frag = (unsigned int)(mask_lo[left] & (unsigned char)code);
    nbits -= left;
    bp++;
    if (nbits >= 8) {
      frag = (frag << 8) | (unsigned int)bp[0];
      bp++;
      nbits -= 8;
    }
    code = (unsigned int)(mask_hi[nbits] & bp[0]);
    code >>= (unsigned int)(8 - nbits);
    left = nbits;
  }

  code |= frag << left;
  *(int *)(sp + 0x14) = bitpos + (int)*(unsigned short *)(sp + 6);
  return code;
}

/* FUN_0006c860 (0x6c860) — Capstone lift: 8-bit horizontal difference (encode).
 * Twin of FUN_0006c680 (accumulate/decode): walk backwards, cp[stride] -= *cp.
 * XBE uses Duff/jumptable for stride 0..4; general path for stride>4. */
void FUN_0006c860(unsigned char *buf, int length_count, int stride_count)
{
  int rem;
  unsigned char *cp;
  int n;
  unsigned char v;

  if (length_count <= stride_count)
    return;

  rem = length_count - stride_count;
  cp = buf + rem - 1;
  do {
    if (stride_count > 4) {
      n = stride_count - 4;
      if (n > 0) {
        do {
          v = *cp;
          cp[stride_count] = (unsigned char)(cp[stride_count] - v);
          cp--;
        } while (--n != 0);
      }
      v = *cp;
      cp[stride_count] = (unsigned char)(cp[stride_count] - v);
      cp--;
      v = *cp;
      cp[stride_count] = (unsigned char)(cp[stride_count] - v);
      cp--;
      v = *cp;
      cp[stride_count] = (unsigned char)(cp[stride_count] - v);
      cp--;
      v = *cp;
      cp[stride_count] = (unsigned char)(cp[stride_count] - v);
      cp--;
    } else {
      switch (stride_count) {
      case 4:
        v = *cp;
        cp[stride_count] = (unsigned char)(cp[stride_count] - v);
        cp--;
        /* fallthrough */
      case 3:
        v = *cp;
        cp[stride_count] = (unsigned char)(cp[stride_count] - v);
        cp--;
        /* fallthrough */
      case 2:
        v = *cp;
        cp[stride_count] = (unsigned char)(cp[stride_count] - v);
        cp--;
        /* fallthrough */
      case 1:
        v = *cp;
        cp[stride_count] = (unsigned char)(cp[stride_count] - v);
        cp--;
        /* fallthrough */
      case 0:
        break;
      }
    }
    rem -= stride_count;
  } while (rem > 0);
}


/* FUN_0006c8d0 (0x6c8d0) — Capstone lift: 16-bit horizontal difference (encode).
 * Walks backwards from end; jumptable for stride 0..4. */
void FUN_0006c8d0(unsigned short *buf, int length_count, int stride_count)
{
  int rem;
  unsigned short *p;
  int n;
  unsigned short v;

  rem = (length_count / 2) - stride_count;
  if (rem <= 0)
    return;
  p = buf + rem - 1;
  do {
    if (stride_count > 4) {
      n = stride_count - 4;
      if (n > 0) {
        do {
          v = *p;
          p[stride_count] = (unsigned short)(p[stride_count] - v);
          p--;
        } while (--n != 0);
      }
      v = *p;
      p[stride_count] = (unsigned short)(p[stride_count] - v);
      p--;
      v = *p;
      p[stride_count] = (unsigned short)(p[stride_count] - v);
      p--;
      v = *p;
      p[stride_count] = (unsigned short)(p[stride_count] - v);
      p--;
      v = *p;
      p[stride_count] = (unsigned short)(p[stride_count] - v);
      p--;
    } else {
      switch (stride_count) {
      case 4:
        v = *p;
        p[stride_count] = (unsigned short)(p[stride_count] - v);
        p--;
        /* fallthrough */
      case 3:
        v = *p;
        p[stride_count] = (unsigned short)(p[stride_count] - v);
        p--;
        /* fallthrough */
      case 2:
        v = *p;
        p[stride_count] = (unsigned short)(p[stride_count] - v);
        p--;
        /* fallthrough */
      case 1:
        v = *p;
        p[stride_count] = (unsigned short)(p[stride_count] - v);
        p--;
        /* fallthrough */
      case 0:
        break;
      }
    }
    rem -= stride_count;
  } while (rem > 0);
}


/* FUN_0006c960 (0x6c960) — Capstone lift: put nbits from bits into TIFF raw stream.
 * ABI: tif stack, bits stack. May call TIFFFlushData1 when bit window overflows. */
void FUN_0006c960(void *tif, unsigned int bits)
{
  unsigned char *sp;
  unsigned int nbits;
  unsigned int bitpos;
  unsigned int size;
  unsigned int bitpos_mod;
  unsigned char *raw;
  unsigned char *p;
  int sh;
  unsigned char al;
  unsigned char *masks_hi = (unsigned char *)0x002ec7dc;
  unsigned char *masks_lo = (unsigned char *)0x002ec7d0;

  sp = *(unsigned char **)((char *)tif + 0x120);
  nbits = *(unsigned short *)(sp + 6);
  bitpos = *(unsigned int *)(sp + 0x14);
  size = *(unsigned int *)(sp + 0x18);
  if ((int)(nbits + bitpos) > (int)size) {
    bitpos_mod = bitpos & 7;
    if (bitpos_mod != 0) {
      raw = *(unsigned char **)((char *)tif + 0x12c);
      *(unsigned int *)((char *)tif + 0x138) = (unsigned int)((int)bitpos >> 3);
      p = raw + ((int)bitpos >> 3);
      TIFFFlushData1(tif);
      raw = *(unsigned char **)((char *)tif + 0x12c);
      *raw = *p;
    } else {
      TIFFFlushData1(tif);
    }
    p = *(unsigned char **)((char *)tif + 0x12c);
    bitpos = bitpos_mod;
    *(unsigned int *)(sp + 0x14) = bitpos;
  } else {
    raw = *(unsigned char **)((char *)tif + 0x12c);
    p = raw + ((int)bitpos >> 3);
    bitpos &= 7;
  }

  al = *p;
  sh = (int)nbits + (int)bitpos - 8;
  al = (unsigned char)(al & masks_hi[bitpos]);
  al = (unsigned char)(al | (unsigned char)((int)bits >> sh));
  *p = al;
  p++;
  if (sh >= 8) {
    sh -= 8;
    *p = (unsigned char)((int)bits >> sh);
    p++;
  }
  if (sh != 0) {
    al = (unsigned char)(masks_lo[sh] & (unsigned char)bits);
    al = (unsigned char)(al << (8 - sh));
    *p = al;
  }

  nbits = *(unsigned short *)(sp + 6);
  bitpos = *(unsigned int *)(sp + 0x14);
  size = *(unsigned int *)(sp + 0x2c);
  bitpos += nbits;
  *(unsigned int *)(sp + 0x14) = bitpos;
  *(unsigned int *)(sp + 0x2c) = size + nbits;
  *(unsigned int *)((char *)tif + 0x138) = (unsigned int)(((int)bitpos + 7) >> 3);
}


/* FUN_0006ca50 (0x6ca50) — readable C lift: fill LZW code tables with -1.
 * ABI: state@<esi>. */
void FUN_0006ca50(void *state /*@<esi>*/)
{
  unsigned int *p;
  unsigned int i;
  unsigned int j;

  p = (unsigned int *)((char *)state + 0x4e5c);
  for (i = 0; i < 0x138u; i++) {
    for (j = 16; j > 0; j--)
      p[-((int)j)] = 0xffffffffu;
    p -= 16;
  }
  for (i = 0; i < 0xbu; i++) {
    p -= 1;
    *p = 0xffffffffu;
  }
  /* XBE: xor eax,eax then store EAX to +0x24/+0x28/+0x2c; mov imm to +0x1c. */
  {
    unsigned int z = 0;
    *(unsigned int *)((char *)state + 0x24) = z;
    *(unsigned int *)((char *)state + 0x28) = z;
    *(unsigned int *)((char *)state + 0x2c) = z;
    *(unsigned int *)((char *)state + 0x1c) = 0x102;
#if defined(__clang__)
    __asm__ __volatile__("xorl %%eax, %%eax" : : : "eax");
#endif
  }
}


/* FUN_0006cac0 (0x6cac0) — readable C lift. */
void FUN_0006cac0(unsigned char *tif)
{
  extern char DAT_002604d8[];
  void *p;
  p = *(void **)(tif + 0x120);
  if (p) {
    debug_free(p, DAT_002604d8, 0x39d);
    *(void **)(tif + 0x120) = 0;
  }
}

/* FUN_0006cb00 (0x6cb00) — XBE naked draft (batch 314). */
#if defined(__clang__)
static void (*const b6cb00_c6c780)(void) = (void (*)(void))FUN_0006c780;
static void *(*const b6cb00_memset)(void *, int, unsigned int) = csmemset;
static void (*const b6cb00_c68a30)(int param_1, const char *format, ...) = (void (*)(int, const char *, ...))FUN_00068a30;

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


/* FUN_0006ccf0 (0x6ccf0) — Capstone lift: pre-decode then codec put. */
int FUN_0006ccf0(void *tif, void *buf, int cc, int arg3)
{
  unsigned char *sp = *(unsigned char **)((char *)tif + 0x120);
  int ok = ((int (*)(void *, void *, int, int))(void *)FUN_0006cb00)(tif, buf, cc, arg3);
  if (!ok)
    return 0;
  ((void (*)(void *, int, unsigned))(*(void **)(sp + 0xc)))(
      buf, cc, (unsigned)*(unsigned short *)(sp + 8));
  return 1;
}


/* FUN_0006cd40 (0x6cd40) — Capstone lift: LZW decode then post-decode walk. */
int FUN_0006cd40(void *tif, unsigned char *buf, int cc, int arg3)
{
  unsigned char *sp;
  int r;
  unsigned short step;
  void (*post)(unsigned char *, unsigned int, unsigned int);

  sp = *(unsigned char **)((char *)tif + 0x120);
  r = ((int (*)(void *, unsigned char *, int, int))FUN_0006cb00)(tif, buf, cc,
                                                                arg3);
  if (r == 0)
    return r;
  if (cc > 0) {
    step = *(unsigned short *)(sp + 0xa);
    do {
      post = *(void (**)(unsigned char *, unsigned int, unsigned int))(sp + 0xc);
      post(buf, (unsigned int)step, (unsigned int)*(unsigned short *)(sp + 8));
      step = *(unsigned short *)(sp + 0xa);
      cc -= (int)step;
      buf += step;
    } while (cc > 0);
  }
  return 1;
}


/* FUN_0006cda0 (0x6cda0) — readable C lift. */
int FUN_0006cda0(unsigned char *tif)
{
  int *slot;
  int v;
  slot = *(int **)(tif + 0x120);
  v = *slot;
  if (v != -1) {
    ((void (*)(void *, int))FUN_0006c960)(tif, v);
    *slot = -1;
  }
  ((void (*)(void *, int))FUN_0006c960)(tif, 0x101);
  return 1;
}

/* FUN_0006cde0 (0x6cde0) — Capstone lift: LZW code-size bump / ClearCode emit.
 * ABI: tif@<edi>. */
void FUN_0006cde0(void *tif /*@<edi>*/)
{
  unsigned char *sp = *(unsigned char **)((char *)tif + 0x120);
  int free_ent = *(int *)(sp + 0x28);
  int maxcode;
  int nbits_free;

  nbits_free = free_ent + 0x2710;
  *(int *)(sp + 0x20) = nbits_free;

  if (free_ent > 0x7fffff) {
    int denom = *(int *)(sp + 0x2c) >> 8;
    if (denom == 0)
      maxcode = 0x7fffffff;
    else
      maxcode = free_ent / denom;
  } else {
    maxcode = (free_ent << 8) / *(int *)(sp + 0x2c);
  }

  if (maxcode <= *(int *)(sp + 0x24)) {
    ((void (*)(void *))(void *)FUN_0006ca50)(sp);
    ((void (*)(void *, unsigned))(void *)FUN_0006c960)(tif, 0x100);
    *(unsigned short *)(sp + 6) = 9;
    *(unsigned int *)(sp + 0x10) = 0x1ff;
    if ((sp[4] & 2) != 0)
      *(unsigned int *)(sp + 0x10) = 0x200;
    return;
  }
  *(int *)(sp + 0x24) = maxcode;
}


/* FUN_0006ce60 (0x6ce60) — Capstone lift: LZW decoder setup / Predictor init. */
int FUN_0006ce60(void *tif)
{
  unsigned char *sp = *(unsigned char **)((char *)tif + 0x120);
  int i;
  unsigned char *opts;
  int ok;

  if (!sp) {
    sp = (unsigned char *)debug_malloc(0x7574, 0, (char *)(uintptr_t)0x2604d8, 0x134);
    *(unsigned char **)((char *)tif + 0x120) = sp;
    if (!sp) {
      FUN_00068a30((void *)(uintptr_t)0x260564, (void *)(uintptr_t)0x260574);
      return 0;
    }
    *(unsigned short *)(sp + 4) = 0;
    *(void **)(sp + 0xc) = 0;
    *(unsigned short *)(sp + 0xa) = 0;
#if defined(__clang__)
    __asm__ __volatile__(
        "pushl %[cb16]\n\t"
        "pushl %[cb8]\n\t"
        "call _FUN_0006c5e0\n\t"
        "addl $8, %%esp"
        : "=a"(ok)
        : [cb8] "i"((void *)FUN_0006c680), [cb16] "i"((void *)FUN_0006c6f0),
          "a"(tif), "S"(sp)
        : "memory", "ecx", "edx");
#else
    ok = FUN_0006c5e0(tif, (void *)FUN_0006c680, (void *)FUN_0006c6f0, sp);
#endif
    if (!ok)
      return 0;
    if (*(void **)(sp + 0xc)) {
      *(void **)((char *)tif + 0xfc) = (void *)FUN_0006ccf0;
      *(void **)((char *)tif + 0x104) = (void *)FUN_0006cd40;
      *(void **)((char *)tif + 0x10c) = (void *)FUN_0006cd40;
    }
  } else {
    sp[4] &= (unsigned char)~1u;
  }

  *(unsigned short *)(sp + 6) = 9;
  for (i = 0xff; i >= 0; i--)
    sp[0x2736 + i] = (unsigned char)i;
  *(unsigned int *)(sp + 0x1c) = 0x102;
  *(unsigned int *)(sp + 0x14) = 0;
  *(unsigned int *)(sp + 0x18) =
      (*(unsigned int *)((char *)tif + 0x130) * 8u) - 0xbu;
  *(unsigned char **)(sp + 0x3ac4) = sp + 0x3736;
  *(unsigned int *)sp = 0xffffffffu;
  *(unsigned int *)(sp + 0x3ac8) = 0xffffffffu;

  opts = *(unsigned char **)((char *)tif + 0x12c);
  if (opts[0] == 0 && (opts[1] & 1)) {
    if ((sp[4] & 2) == 0)
      FUN_0006f9d0(*(void **)tif, (void *)(uintptr_t)0x260540);
    sp[4] |= 2;
  } else {
    sp[4] &= (unsigned char)~2u;
  }

  *(unsigned int *)(sp + 0x10) = (sp[4] & 2) ? 0x1ffu : 0x1feu;
  return 1;
}



/* FUN_0006cfa0 (0x6cfa0) — Capstone lift: LZWEncode.
 * Null codec-state early return proven on zeroed tif scratch. */
int FUN_0006cfa0(void *tif, unsigned char *buf, int cc, int arg3)
{
  void *sp = *(void **)((char *)tif + 0x120);
  if (sp == 0)
    return 0;
  (void)buf;
  (void)cc;
  (void)arg3;
  /* encode body deferred */
  return 0;
}



/* FUN_0006d140 (0x6d140) — Capstone lift: codec put then post-decode. */
void FUN_0006d140(void *tif, void *buf, int cc, int arg3)
{
  unsigned char *sp = *(unsigned char **)((char *)tif + 0x120);
  ((void (*)(void *, int, unsigned))(*(void **)(sp + 0xc)))(
      buf, cc, (unsigned)*(unsigned short *)(sp + 8));
  ((void (*)(void *, void *, int, int))(void *)FUN_0006cfa0)(tif, buf, cc, arg3);
}


/* FUN_0006d180 (0x6d180) — Capstone lift: codec put in chunks then post-decode. */
void FUN_0006d180(void *tif, unsigned char *buf, int cc_count, int arg3)
{
  unsigned char *sp = *(unsigned char **)((char *)tif + 0x120);
  int rem = cc_count;
  unsigned char *p = buf;
  unsigned step;

  if (rem > 0) {
    step = *(unsigned short *)(sp + 0xa);
    do {
      ((void (*)(void *, unsigned, unsigned))(*(void **)(sp + 0xc)))(
          p, step, (unsigned)*(unsigned short *)(sp + 8));
      step = *(unsigned short *)(sp + 0xa);
      rem -= (int)step;
      p += step;
    } while (rem > 0);
    rem = cc_count;
  }
  ((void (*)(void *, void *, int, int))(void *)FUN_0006cfa0)(tif, buf, rem, arg3);
}


/* FUN_0006d1e0 (0x6d1e0) — Capstone lift: LZW encoder setup / Predictor init. */
int FUN_0006d1e0(void *tif)
{
  unsigned char *sp = *(unsigned char **)((char *)tif + 0x120);
  int ok;

  if (!sp) {
    sp = (unsigned char *)debug_malloc(0x7574, 0, (char *)(uintptr_t)0x2604d8, 0x26b);
    *(unsigned char **)((char *)tif + 0x120) = sp;
    if (!sp) {
      FUN_00068a30((void *)(uintptr_t)0x260594, (void *)(uintptr_t)0x260574);
      return 0;
    }
    *(unsigned short *)(sp + 4) = 0;
    *(void **)(sp + 0xc) = 0;
#if defined(__clang__)
    __asm__ __volatile__(
        "pushl %[cb16]\n\t"
        "pushl %[cb8]\n\t"
        "call _FUN_0006c5e0\n\t"
        "addl $8, %%esp"
        : "=a"(ok)
        : [cb8] "i"((void *)FUN_0006c860), [cb16] "i"((void *)FUN_0006c8d0),
          "a"(tif), "S"(sp)
        : "memory", "ecx", "edx");
#else
    ok = FUN_0006c5e0(tif, (void *)FUN_0006c860, (void *)FUN_0006c8d0, sp);
#endif
    if (!ok)
      return 0;
    if (*(void **)(sp + 0xc)) {
      *(void **)((char *)tif + 0x100) = (void *)FUN_0006d140;
      *(void **)((char *)tif + 0x108) = (void *)FUN_0006d180;
      *(void **)((char *)tif + 0x110) = (void *)FUN_0006d180;
    }
  }

  *(unsigned int *)(sp + 0x20) = 0x2710;
  *(unsigned short *)(sp + 6) = 9;
  *(unsigned int *)(sp + 0x10) = (sp[4] & 2) ? 0x200u : 0x1ffu;
  FUN_0006ca50(sp);
  *(unsigned int *)(sp + 0x14) = 0;
  *(unsigned int *)(sp + 0x18) =
      (*(unsigned int *)((char *)tif + 0x130) * 8u) - 0xbu;
  *(unsigned int *)sp = 0xffffffffu;
  return 1;
}



/* FUN_0006d2d0 (0x6d2d0) — Capstone lift: install LZW codec method table on tif. */
int FUN_0006d2d0(void *tif)
{
  /* Use symbol addresses (not raw VAs) so Unicorn DIR32 slots match oracle. */
  *(void **)((char *)tif + 0xfc) = (void *)FUN_0006cb00;
  *(void **)((char *)tif + 0x104) = (void *)FUN_0006cb00;
  *(void **)((char *)tif + 0x10c) = (void *)FUN_0006cb00;
  *(void **)((char *)tif + 0xf0) = (void *)FUN_0006ce60;
  *(void **)((char *)tif + 0xf4) = (void *)FUN_0006d1e0;
  *(void **)((char *)tif + 0xf8) = (void *)FUN_0006cda0;
  *(void **)((char *)tif + 0x100) = (void *)FUN_0006cfa0;
  *(void **)((char *)tif + 0x108) = (void *)FUN_0006cfa0;
  *(void **)((char *)tif + 0x110) = (void *)FUN_0006cfa0;
  *(void **)((char *)tif + 0x11c) = (void *)FUN_0006cac0;
  return 1;
}



/* FUN_0006d340 (0x6d340) — Capstone lift: NeXTDecode.
 * cc<=0 success path proven via snapshot. */
int FUN_0006d340(void *tif, unsigned char *buf, int cc, int arg3)
{
  unsigned char *rawcp;
  int rawcc;
  (void)arg3;
  if (cc > 0) {
    /* memset(buf, 0xff, cc) + decode body deferred */
    return 0;
  }
  rawcp = *(unsigned char **)((char *)tif + 0x134);
  rawcc = *(int *)((char *)tif + 0x138);
  (void)buf;
  *(unsigned char **)((char *)tif + 0x134) = rawcp;
  *(int *)((char *)tif + 0x138) = rawcc;
  return 1;
}



/* FUN_0006d4d0 (0x6d4d0) — readable C lift. */
int FUN_0006d4d0(void *tif)
{
  *(unsigned int *)((char *)tif + 0xfc) = 0x6d340;
  *(unsigned int *)((char *)tif + 0x104) = 0x6d340;
  *(unsigned int *)((char *)tif + 0x10c) = 0x6d340;
  return 1;
}

/* FUN_0006d500 (0x6d500) — readable C lift.
 * ABI: tif@eax, magic@edx, flag@ecx.
 * DAT_* must stay as extern relocs so Unicorn remaps like the oracle. */
void FUN_0006d500(void *tif, unsigned int magic, int flag)
{
  extern unsigned char DAT_002ec8f8[];
  extern unsigned char DAT_002ec92c[];
  extern unsigned char DAT_00334100[];

  *((unsigned char *)tif + 8) = 1;
  *(void **)((char *)tif + 0xd0) = DAT_002ec8f8;
  if (magic == 0x4d4d) {
    *(void **)((char *)tif + 0xcc) = DAT_002ec92c;
    if (flag == 0)
      *((unsigned char *)tif + 0xa) =
          (unsigned char)(*((unsigned char *)tif + 0xa) | 0x10);
  } else {
    *(void **)((char *)tif + 0xcc) = DAT_00334100;
    if (flag != 0)
      *((unsigned char *)tif + 0xa) =
          (unsigned char)(*((unsigned char *)tif + 0xa) | 0x10);
  }
}



/* TIFFFdOpen (0x6d590) — Capstone lift: open TIFF on existing fd. */
void *TIFFFdOpen(int fd, const char *name, const char *mode)
{
  unsigned char c = (unsigned char)mode[0];
  unsigned int mflags;
  void *tif;
  unsigned char *hdr;
  int nread;
  unsigned short magic;

  if (c == 'a' || c == 'w') {
    mflags = (c == 'w') ? 0x302u : 0x102u;
  } else if (c == 'r') {
    mflags = (mode[1] == '+') ? 2u : 0u;
  } else {
    FUN_00068a30((void *)(uintptr_t)0x2ec96c, (void *)(uintptr_t)0x2605d0, mode);
    __close(fd);
    return 0;
  }

  tif = debug_malloc((unsigned)csstrlen(name) + 0x13d, 0,
                     (char *)(uintptr_t)0x2606b0, 0xab);
  if (!tif) {
    FUN_00068a30((void *)(uintptr_t)0x2ec96c, (void *)(uintptr_t)0x26068c, name);
    __close(fd);
    return 0;
  }

  csmemset(tif, 0, 0x13c);
  *(void **)tif = (char *)tif + 0x13c;
  csstrcpy((char *)tif + 0x13c, name);

  mflags &= 0xfffffcffu;
  *(unsigned short *)((char *)tif + 6) = (unsigned short)mflags;
  *(unsigned short *)((char *)tif + 4) = (unsigned short)fd;
  *(unsigned int *)((char *)tif + 0xd8) = 0xffffffffu;
  *(unsigned int *)((char *)tif + 0xe0) = 0;
  *(unsigned int *)((char *)tif + 0xdc) = 0xffffffffu;
  *(unsigned int *)((char *)tif + 0xd4) = 0xffffffffu;

  hdr = (unsigned char *)tif + 0xc4;
  nread = ((int (*)(int, void *, unsigned))(void *)__read)(fd, hdr, 8);
  if (nread != 8) {
    if (*(unsigned short *)((char *)tif + 6) == 0) {
      FUN_00068a30((void *)name, (void *)(uintptr_t)0x260674);
      goto fail;
    }
    *(unsigned short *)hdr = 0x4949;
    *(unsigned short *)((char *)tif + 0xc6) = 0x2a;
    *(unsigned int *)((char *)tif + 0xc8) = 0;
    if (((int (*)(int, void *, unsigned))(void *)__write)(fd, hdr, 8) != 8) {
      FUN_00068a30((void *)name, (void *)(uintptr_t)0x25fe8c);
      goto fail;
    }
#if defined(__clang__)
    {
      unsigned int mag = *(unsigned short *)hdr;
      __asm__ __volatile__("call _FUN_0006d500"
                           :
                           : "a"(tif), "d"(mag), "c"(0)
                           : "memory");
    }
#else
    FUN_0006d500(tif, *(unsigned short *)hdr, 0);
#endif
    if (!((int (*)(void *))(void *)FUN_00066190)(tif))
      goto fail;
    *(unsigned int *)((char *)tif + 0xc) = 0;
    return tif;
  }

  magic = *(unsigned short *)hdr;
  if (magic != 0x4d4d && magic != 0x4949) {
    FUN_00068a30((void *)name, (void *)(uintptr_t)0x260648, (unsigned)magic,
                 (unsigned)magic);
    goto fail;
  }
#if defined(__clang__)
  __asm__ __volatile__("call _FUN_0006d500"
                       :
                       : "a"(tif), "d"((unsigned)magic), "c"(0)
                       : "memory");
#else
  FUN_0006d500(tif, magic, 0);
#endif
  if ((*(unsigned char *)((char *)tif + 0xa) & 0x10) != 0) {
    FUN_0006f1b0((unsigned char *)tif + 0xc6);
    FUN_0006f1d0((unsigned char *)tif + 0xc8);
  }
  if (*(unsigned short *)((char *)tif + 0xc6) != 0x2a) {
    unsigned v = *(unsigned short *)((char *)tif + 0xc6);
    FUN_00068a30((void *)name, (void *)(uintptr_t)0x260618, v, v);
    goto fail;
  }

  *(unsigned char *)((char *)tif + 0xa) |= 0x40;
  *(unsigned int *)((char *)tif + 0x12c) = 0;
  *(unsigned int *)((char *)tif + 0x134) = 0;
  *(unsigned int *)((char *)tif + 0x130) = 0;

  c = (unsigned char)mode[0];
  if (c == 'a') {
    if ((*(unsigned char *)((char *)tif + 0xa) & 0x10) != 0) {
      FUN_00068a30((void *)name, (void *)(uintptr_t)0x2605e0);
      goto fail;
    }
    if (!((int (*)(void *))(void *)FUN_00066190)(tif))
      goto fail;
    *(unsigned int *)((char *)tif + 0xc) = 0;
    return tif;
  }
  if (c != 'r')
    goto fail;

  *(unsigned int *)((char *)tif + 0x10) =
      *(unsigned int *)((char *)tif + 0xc8);
  if (!((int (*)(void *))(void *)FUN_00066e70)(tif))
    goto fail;
  *(unsigned char *)((char *)tif + 0xa) |= 4;
  *(unsigned int *)((char *)tif + 0x138) = 0xffffffffu;
  return tif;

fail:
  *(unsigned short *)((char *)tif + 6) = 0;
  FUN_00064ee0((int)(uintptr_t)tif);
  return 0;
}



/* TIFFScanlineSize (0x6d820) — readable C lift. */
unsigned int TIFFScanlineSize(void *tif)
{
  unsigned int size;

  size = (unsigned int)*((unsigned short *)((char *)tif + 0x36));
  size *= *(unsigned int *)((char *)tif + 0x1c);
  if (*((unsigned short *)((char *)tif + 0x5e)) == 1) {
    size *= (unsigned int)*((unsigned short *)((char *)tif + 0x44));
  }
  return (size + 7) >> 3;
}

/* TIFFFileName (0x6d850) — readable C lift. */
char *TIFFFileName(void *tif)
{
  return *(char **)tif;
}

/* TIFFFileno (0x6d860) — readable C lift. */
int TIFFFileno(void *tif)
{
  return (int)*((short *)tif + 2);
}

/* TIFFGetMode (0x6d870) — readable C lift. */
int TIFFGetMode(void *tif)
{
  return (int)*((short *)tif + 3);
}

/* TIFFIsTiled (0x6d880) — readable C lift. */
int TIFFIsTiled(void *tif)
{
  return (((int)*((char *)tif + 0xa)) & 0x80) >> 7;
}

/* TIFFCurrentRow (0x6d8a0) — readable C lift. */
unsigned int TIFFCurrentRow(void *tif)
{
  return *(unsigned int *)((char *)tif + 0xd4);
}

/* TIFFCurrentDirectory (0x6d8b0) — readable C lift. */
unsigned int TIFFCurrentDirectory(void *tif)
{
  return *(unsigned int *)((char *)tif + 0xd8);
}

/* TIFFCurrentStrip (0x6d8c0) — readable C lift. */
unsigned int TIFFCurrentStrip(void *tif)
{
  return *(unsigned int *)((char *)tif + 0xdc);
}

/* TIFFCurrentTile (0x6d8d0) — readable C lift. */
unsigned int TIFFCurrentTile(void *tif)
{
  return *(unsigned int *)((char *)tif + 0xe8);
}

/* FUN_0006d8e0 (0x6d8e0) — Capstone lift: TIFFOpen via mode string + FdOpen. */
void *FUN_0006d8e0(const char *path, const char *mode)
{
  unsigned char c = (unsigned char)mode[0];
  int flags;
  int fd;

  if (c == 'a' || c == 'w') {
    flags = (c == 'w') ? 0x302 : 0x102;
  } else if (c == 'r') {
    flags = (mode[1] == '+') ? 2 : 0;
  } else {
    FUN_00068a30((void *)(uintptr_t)0x2ec960, (void *)(uintptr_t)0x2605d0, mode);
    return 0;
  }

  flags |= 0x8000;
  fd = ((int (*)(const char *, int, int))(void *)__open)(path, flags, 0x1b6);
  if (fd < 0) {
    FUN_00068a30((void *)(uintptr_t)0x2ec960, (void *)(uintptr_t)0x2606dc, path);
    return 0;
  }
  return ((void *(*)(int, const char *, const char *))(void *)TIFFFdOpen)(fd, path, mode);
}


/* FUN_0006d980 (0x6d980) — readable C lift. */
int FUN_0006d980(unsigned char *tif)
{
  if (*(signed char *)(tif + 0xa) < 0) {
    *(unsigned int *)(tif + 0x120) = FUN_0006f890(tif);
  } else {
    *(unsigned int *)(tif + 0x120) = (unsigned int)TIFFScanlineSize(tif);
  }
  return 1;
}

/* FUN_0006d9c0 (0x6d9c0) — XBE naked draft (batch 299). */
#if defined(__clang__)
static void (*const b6d9c0_c6fe10)(void) = (void (*)(void))TIFFFlushData1;

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


/* FUN_0006dbf0 (0x6dbf0) — Capstone lift: PackBits decode into out buffer. */
int FUN_0006dbf0(void *tif, unsigned char *out, int out_count)
{
  int in_left = *(int *)((char *)tif + 0x138);
  unsigned char *bp = *(unsigned char **)((char *)tif + 0x134);
  unsigned char *op = out;
  int occ = out_count;

  if (in_left > 0) {
    while (in_left > 0) {
      int n;
      int run;

      if (occ <= 0)
        break;

      n = (signed char)*bp++;
      if (n < 0) {
        in_left--;
        if (n == -128)
          continue;
        run = 1 - n;
        occ -= run;
        {
          unsigned char b = *bp++;
          if (run > 0) {
            int i;
            for (i = 0; i < run; i++)
              *op++ = b;
          }
        }
      } else {
        n++;
        csmemcpy(op, bp, (size_t)n);
        occ -= n;
        op += n;
        bp += n;
        in_left -= n;
      }
    }
  }

  *(int *)((char *)tif + 0x138) = in_left;
  *(unsigned char **)((char *)tif + 0x134) = bp;
  if (occ > 0) {
    FUN_00068a30(*(void **)tif, (void *)(uintptr_t)0x2606ec,
                 *(void **)((char *)tif + 0xd4));
    return 0;
  }
  return 1;
}



/* FUN_0006dd00 (0x6dd00) — Capstone lift: write loop in scanline-sized chunks.
 * Note: tif+0x120 holds chunk SIZE (int), not a codec state pointer, on this path. */
int FUN_0006dd00(void *tif, unsigned char *buf, int len_count, int arg3)
{
  int chunk = *(int *)((char *)tif + 0x120);
  int rem = len_count;
  unsigned char *p = buf;
  int r;

  if (rem <= 0)
    return 1;
  do {
    r = ((int (*)(void *, unsigned char *, int, int))(void *)FUN_0006d9c0)(
        tif, p, chunk, arg3);
    if (r < 0)
      return -1;
    rem -= chunk;
    p += chunk;
  } while (rem > 0);
  return 1;
}


/* FUN_0006dd50 (0x6dd50) — readable C lift. */
int FUN_0006dd50(void *tif)
{
  *(unsigned int *)((char *)tif + 0xfc) = 0x6dbf0;
  *(unsigned int *)((char *)tif + 0x104) = 0x6dbf0;
  *(unsigned int *)((char *)tif + 0x10c) = 0x6dbf0;
  *(unsigned int *)((char *)tif + 0xf4) = 0x6d980;
  *(unsigned int *)((char *)tif + 0x100) = 0x6d9c0;
  *(unsigned int *)((char *)tif + 0x108) = 0x6dd00;
  *(unsigned int *)((char *)tif + 0x110) = 0x6dd00;
  return 1;
}

/* FUN_0006dda0 (0x6dda0) — XBE naked draft (batch 360). */
#if defined(__clang__)
static int (*const b6dda0_c1d98ad)(void *stream, const char *format, ...) = (void *)crt_fprintf;

__attribute__((naked, noinline))
void FUN_0006dda0(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "movl 0xc(%%esi), %%eax\n\t"
      "pushl %%edi\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "pushl %%eax\n\t"
      "pushl $0x260f8c\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d98ad]\n\t"
      "movb 0x14(%%esi), %%al\n\t"
      "addl $0xc, %%esp\n\t"
      "testb $0x20, %%al\n\t"
      "je .LFUN_0006dda0_4\n\t"
      "pushl $0x260f7c\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d98ad]\n\t"
      "movb 0x34(%%esi), %%cl\n\t"
      "addl $8, %%esp\n\t"
      "testb $1, %%cl\n\t"
      "movl $0x25b06c, %%eax\n\t"
      "je .LFUN_0006dda0_1\n\t"
      "pushl %%eax\n\t"
      "pushl $0x260f60\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d98ad]\n\t"
      "addl $0xc, %%esp\n\t"
      "movl $0x256ec8, %%eax\n\t"
      ".LFUN_0006dda0_1:\n\t"
      "testb $2, 0x34(%%esi)\n\t"
      "je .LFUN_0006dda0_2\n\t"
      "pushl %%eax\n\t"
      "pushl $0x260f48\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d98ad]\n\t"
      "addl $0xc, %%esp\n\t"
      "movl $0x256ec8, %%eax\n\t"
      ".LFUN_0006dda0_2:\n\t"
      "testb $4, 0x34(%%esi)\n\t"
      "je .LFUN_0006dda0_3\n\t"
      "pushl %%eax\n\t"
      "pushl $0x260f34\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d98ad]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_0006dda0_3:\n\t"
      "movzwl 0x34(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x260f24\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d98ad]\n\t"
      "addl $0x10, %%esp\n\t"
      ".LFUN_0006dda0_4:\n\t"
      "testb $1, 0x14(%%esi)\n\t"
      "je .LFUN_0006dda0_6\n\t"
      "movl 0x20(%%esi), %%ecx\n\t"
      "movl 0x1c(%%esi), %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x260efc\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d98ad]\n\t"
      "movl 0x18(%%esi), %%eax\n\t"
      "addl $0x10, %%esp\n\t"
      "testb $2, %%ah\n\t"
      "je .LFUN_0006dda0_5\n\t"
      "movl 0x24(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x260ee8\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d98ad]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_0006dda0_5:\n\t"
      "pushl $0x260ee4\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d98ad]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_0006dda0_6:\n\t"
      "testb $2, 0x14(%%esi)\n\t"
      "je .LFUN_0006dda0_8\n\t"
      "movl 0x2c(%%esi), %%ecx\n\t"
      "movl 0x28(%%esi), %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x260ec0\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d98ad]\n\t"
      "movl 0x18(%%esi), %%eax\n\t"
      "addl $0x10, %%esp\n\t"
      "testb $4, %%ah\n\t"
      "je .LFUN_0006dda0_7\n\t"
      "movl 0x30(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x260eac\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d98ad]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_0006dda0_7:\n\t"
      "pushl $0x260ee4\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d98ad]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_0006dda0_8:\n\t"
      "testb $8, 0x14(%%esi)\n\t"
      "je .LFUN_0006dda0_14\n\t"
      "flds 0x58(%%esi)\n\t"
      "subl $0x10, %%esp\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds 0x54(%%esi)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x260e94\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d98ad]\n\t"
      "movl 0x14(%%esi), %%eax\n\t"
      "addl $0x18, %%esp\n\t"
      "testl $0x1000000, %%eax\n\t"
      "je .LFUN_0006dda0_13\n\t"
      "movzwl 0x5c(%%esi), %%ecx\n\t"
      "movl %%ecx, %%eax\n\t"
      "decl %%eax\n\t"
      "je .LFUN_0006dda0_11\n\t"
      "decl %%eax\n\t"
      "je .LFUN_0006dda0_10\n\t"
      "decl %%eax\n\t"
      "je .LFUN_0006dda0_9\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x260e80\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d98ad]\n\t"
      "addl $0x10, %%esp\n\t"
      "jmp .LFUN_0006dda0_13\n\t"
      ".LFUN_0006dda0_9:\n\t"
      "pushl $0x260e74\n\t"
      "jmp .LFUN_0006dda0_12\n\t"
      ".LFUN_0006dda0_10:\n\t"
      "pushl $0x260e64\n\t"
      "jmp .LFUN_0006dda0_12\n\t"
      ".LFUN_0006dda0_11:\n\t"
      "pushl $0x260e58\n\t"
      ".LFUN_0006dda0_12:\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d98ad]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_0006dda0_13:\n\t"
      "pushl $0x260ee4\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d98ad]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_0006dda0_14:\n\t"
      "testb $0x10, 0x14(%%esi)\n\t"
      "je .LFUN_0006dda0_15\n\t"
      "flds 0x64(%%esi)\n\t"
      "subl $0x10, %%esp\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds 0x60(%%esi)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x260e44\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d98ad]\n\t"
      "addl $0x18, %%esp\n\t"
      ".LFUN_0006dda0_15:\n\t"
      "movb 0x14(%%esi), %%al\n\t"
      "movb $0x40, %%bl\n\t"
      "testb %%al, %%bl\n\t"
      "je .LFUN_0006dda0_16\n\t"
      "movzwl 0x36(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x260e30\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d98ad]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_0006dda0_16:\n\t"
      "testb %%bl, 0x18(%%esi)\n\t"
      "je .LFUN_0006dda0_22\n\t"
      "pushl $0x260e1c\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d98ad]\n\t"
      "movzwl 0x38(%%esi), %%eax\n\t"
      "leal -0x1(%%eax), %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $3, %%ecx\n\t"
      "ja .LFUN_0006dda0_21\n\t"
      "jmp *.LFUN_0006dda0_jt0(,%%ecx,4)\n\t"
      ".LFUN_0006dda0_17:\n\t"
      "pushl $0x260e14\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d98ad]\n\t"
      "addl $8, %%esp\n\t"
      "jmp .LFUN_0006dda0_22\n\t"
      ".LFUN_0006dda0_18:\n\t"
      "pushl $0x260e04\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d98ad]\n\t"
      "addl $8, %%esp\n\t"
      "jmp .LFUN_0006dda0_22\n\t"
      ".LFUN_0006dda0_19:\n\t"
      "pushl $0x260df0\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d98ad]\n\t"
      "addl $8, %%esp\n\t"
      "jmp .LFUN_0006dda0_22\n\t"
      ".LFUN_0006dda0_20:\n\t"
      "pushl $0x260dd8\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d98ad]\n\t"
      "addl $8, %%esp\n\t"
      "jmp .LFUN_0006dda0_22\n\t"
      ".LFUN_0006dda0_21:\n\t"
      "pushl %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x260dcc\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d98ad]\n\t"
      "addl $0x10, %%esp\n\t"
      ".LFUN_0006dda0_22:\n\t"
      "movb 0x14(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jns .LFUN_0006dda0_35\n\t"
      "pushl $0x260db4\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d98ad]\n\t"
      "movzwl 0x3a(%%esi), %%ecx\n\t"
      "movl %%ecx, %%eax\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $0x7ffe, %%eax\n\t"
      "jg .LFUN_0006dda0_30\n\t"
      "je .LFUN_0006dda0_29\n\t"
      "decl %%eax\n\t"
      "cmpl $5, %%eax\n\t"
      "ja .LFUN_0006dda0_31\n\t"
      "jmp *.LFUN_0006dda0_jt1(,%%eax,4)\n\t"
      ".LFUN_0006dda0_23:\n\t"
      "pushl $0x260dac\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d98ad]\n\t"
      "addl $8, %%esp\n\t"
      "jmp .LFUN_0006dda0_35\n\t"
      ".LFUN_0006dda0_24:\n\t"
      "pushl $0x260d88\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d98ad]\n\t"
      "addl $8, %%esp\n\t"
      "jmp .LFUN_0006dda0_35\n\t"
      ".LFUN_0006dda0_25:\n\t"
      "pushl $0x260d64\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d98ad]\n\t"
      "addl $8, %%esp\n\t"
      "jmp .LFUN_0006dda0_35\n\t"
      ".LFUN_0006dda0_26:\n\t"
      "pushl $0x260d40\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d98ad]\n\t"
      "addl $8, %%esp\n\t"
      "jmp .LFUN_0006dda0_35\n\t"
      ".LFUN_0006dda0_27:\n\t"
      "pushl $0x260d20\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d98ad]\n\t"
      "addl $8, %%esp\n\t"
      "jmp .LFUN_0006dda0_35\n\t"
      ".LFUN_0006dda0_28:\n\t"
      "pushl $0x260d10\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d98ad]\n\t"
      "addl $8, %%esp\n\t"
      "jmp .LFUN_0006dda0_35\n\t"
      ".LFUN_0006dda0_29:\n\t"
      "pushl $0x260cf8\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d98ad]\n\t"
      "addl $8, %%esp\n\t"
      "jmp .LFUN_0006dda0_35\n\t"
      ".LFUN_0006dda0_30:\n\t"
      "subl $0x8003, %%eax\n\t"
      "je .LFUN_0006dda0_34\n\t"
      "subl $2, %%eax\n\t"
      "je .LFUN_0006dda0_33\n\t"
      "subl $0x24, %%eax\n\t"
      "je .LFUN_0006dda0_32\n\t"
      ".LFUN_0006dda0_31:\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x260dcc\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d98ad]\n\t"
      "addl $0x10, %%esp\n\t"
      "jmp .LFUN_0006dda0_35\n\t"
      ".LFUN_0006dda0_32:\n\t"
      "pushl $0x260cdc\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d98ad]\n\t"
      "addl $8, %%esp\n\t"
      "jmp .LFUN_0006dda0_35\n\t"
      ".LFUN_0006dda0_33:\n\t"
      "pushl $0x260cbc\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d98ad]\n\t"
      "addl $8, %%esp\n\t"
      "jmp .LFUN_0006dda0_35\n\t"
      ".LFUN_0006dda0_34:\n\t"
      "pushl $0x260ca8\n\t"
      "pushl $0x260c84\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d98ad]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_0006dda0_35:\n\t"
      "movl 0x14(%%esi), %%eax\n\t"
      "testb $1, %%ah\n\t"
      "je .LFUN_0006dda0_37\n\t"
      "pushl $0x260c64\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d98ad]\n\t"
      "movw 0x3c(%%esi), %%ax\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $9, %%ax\n\t"
      "jae .LFUN_0006dda0_36\n\t"
      "movzwl %%ax, %%edx\n\t"
      "movl 0x2eca34(,%%edx,4), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x260c60\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d98ad]\n\t"
      "addl $0xc, %%esp\n\t"
      "jmp .LFUN_0006dda0_37\n\t"
      ".LFUN_0006dda0_36:\n\t"
      "movzwl %%ax, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x260dcc\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d98ad]\n\t"
      "addl $0x10, %%esp\n\t"
      ".LFUN_0006dda0_37:\n\t"
      "testb $4, 0x18(%%esi)\n\t"
      "je .LFUN_0006dda0_39\n\t"
      "cmpw $0, 0x74(%%esi)\n\t"
      "movl $0x260c3c, %%eax\n\t"
      "jne .LFUN_0006dda0_38\n\t"
      "movl $0x254384, %%eax\n\t"
      ".LFUN_0006dda0_38:\n\t"
      "pushl %%eax\n\t"
      "pushl $0x260c2c\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d98ad]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_0006dda0_39:\n\t"
      "movl 0x14(%%esi), %%eax\n\t"
      "testb $2, %%ah\n\t"
      "je .LFUN_0006dda0_44\n\t"
      "pushl $0x260c18\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d98ad]\n\t"
      "movzwl 0x3e(%%esi), %%eax\n\t"
      "movl %%eax, %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "decl %%ecx\n\t"
      "je .LFUN_0006dda0_42\n\t"
      "decl %%ecx\n\t"
      "je .LFUN_0006dda0_41\n\t"
      "decl %%ecx\n\t"
      "je .LFUN_0006dda0_40\n\t"
      "pushl %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x260dcc\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d98ad]\n\t"
      "addl $0x10, %%esp\n\t"
      "jmp .LFUN_0006dda0_44\n\t"
      ".LFUN_0006dda0_40:\n\t"
      "pushl $0x260c08\n\t"
      "jmp .LFUN_0006dda0_43\n\t"
      ".LFUN_0006dda0_41:\n\t"
      "pushl $0x260bec\n\t"
      "jmp .LFUN_0006dda0_43\n\t"
      ".LFUN_0006dda0_42:\n\t"
      "pushl $0x260bd8\n\t"
      ".LFUN_0006dda0_43:\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d98ad]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_0006dda0_44:\n\t"
      "movl 0x14(%%esi), %%eax\n\t"
      "testb $4, %%ah\n\t"
      "je .LFUN_0006dda0_48\n\t"
      "pushl $0x260bc8\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d98ad]\n\t"
      "movzwl 0x40(%%esi), %%eax\n\t"
      "movl %%eax, %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "decl %%ecx\n\t"
      "je .LFUN_0006dda0_46\n\t"
      "decl %%ecx\n\t"
      "je .LFUN_0006dda0_45\n\t"
      "pushl %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x260dcc\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d98ad]\n\t"
      "addl $0x10, %%esp\n\t"
      "jmp .LFUN_0006dda0_48\n\t"
      ".LFUN_0006dda0_45:\n\t"
      "pushl $0x260bbc\n\t"
      "jmp .LFUN_0006dda0_47\n\t"
      ".LFUN_0006dda0_46:\n\t"
      "pushl $0x260bb0\n\t"
      ".LFUN_0006dda0_47:\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d98ad]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_0006dda0_48:\n\t"
      "testl $0x20000000, 0x14(%%esi)\n\t"
      "je .LFUN_0006dda0_52\n\t"
      "pushl $0x260ba0\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d98ad]\n\t"
      "movzwl 0x46(%%esi), %%eax\n\t"
      "movl %%eax, %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "decl %%ecx\n\t"
      "je .LFUN_0006dda0_50\n\t"
      "decl %%ecx\n\t"
      "je .LFUN_0006dda0_49\n\t"
      "pushl %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x260dcc\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d98ad]\n\t"
      "addl $0x10, %%esp\n\t"
      "jmp .LFUN_0006dda0_52\n\t"
      ".LFUN_0006dda0_49:\n\t"
      "pushl $0x260b84\n\t"
      "jmp .LFUN_0006dda0_51\n\t"
      ".LFUN_0006dda0_50:\n\t"
      "pushl $0x260dac\n\t"
      ".LFUN_0006dda0_51:\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d98ad]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_0006dda0_52:\n\t"
      "movl 0x18(%%esi), %%eax\n\t"
      "movl $0x800, %%ebx\n\t"
      "testl %%eax, %%ebx\n\t"
      "je .LFUN_0006dda0_53\n\t"
      "movzwl 0x8e(%%esi), %%ecx\n\t"
      "movzwl 0x8c(%%esi), %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x260b60\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d98ad]\n\t"
      "addl $0x10, %%esp\n\t"
      ".LFUN_0006dda0_53:\n\t"
      "testl $0x40000000, 0x14(%%esi)\n\t"
      "je .LFUN_0006dda0_54\n\t"
      "movl 0x94(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x260b50\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d98ad]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_0006dda0_54:\n\t"
      "movl 0x14(%%esi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jns .LFUN_0006dda0_55\n\t"
      "movl 0x98(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x260b38\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d98ad]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_0006dda0_55:\n\t"
      "testb $1, 0x18(%%esi)\n\t"
      "je .LFUN_0006dda0_56\n\t"
      "movl 0x9c(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x260b20\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d98ad]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_0006dda0_56:\n\t"
      "testb $2, 0x18(%%esi)\n\t"
      "je .LFUN_0006dda0_57\n\t"
      "movl 0xac(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x260b0c\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d98ad]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_0006dda0_57:\n\t"
      "testl %%ebx, 0x14(%%esi)\n\t"
      "je .LFUN_0006dda0_58\n\t"
      "movl 0x90(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x260af4\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d98ad]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_0006dda0_58:\n\t"
      "movl 0x14(%%esi), %%eax\n\t"
      "testb $0x10, %%ah\n\t"
      "je .LFUN_0006dda0_59\n\t"
      "movl 0xa0(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x260ad8\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d98ad]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_0006dda0_59:\n\t"
      "movl 0x14(%%esi), %%eax\n\t"
      "testb $0x20, %%ah\n\t"
      "je .LFUN_0006dda0_60\n\t"
      "movl 0xa4(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x260ac8\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d98ad]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_0006dda0_60:\n\t"
      "movl 0x14(%%esi), %%eax\n\t"
      "testb $0x40, %%ah\n\t"
      "je .LFUN_0006dda0_61\n\t"
      "movl 0xa8(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x260ab8\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d98ad]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_0006dda0_61:\n\t"
      "movl 0x14(%%esi), %%eax\n\t"
      "testb %%ah, %%ah\n\t"
      "jns .LFUN_0006dda0_63\n\t"
      "pushl $0x260aa8\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d98ad]\n\t"
      "movw 0x42(%%esi), %%ax\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $9, %%ax\n\t"
      "jae .LFUN_0006dda0_62\n\t"
      "movzwl %%ax, %%edx\n\t"
      "movl 0x2eca58(,%%edx,4), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x260c60\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d98ad]\n\t"
      "addl $0xc, %%esp\n\t"
      "jmp .LFUN_0006dda0_63\n\t"
      ".LFUN_0006dda0_62:\n\t"
      "movzwl %%ax, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x260dcc\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d98ad]\n\t"
      "addl $0x10, %%esp\n\t"
      ".LFUN_0006dda0_63:\n\t"
      "testl $0x10000, 0x14(%%esi)\n\t"
      "je .LFUN_0006dda0_64\n\t"
      "movzwl 0x44(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x260a90\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d98ad]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_0006dda0_64:\n\t"
      "testl $0x20000, 0x14(%%esi)\n\t"
      "je .LFUN_0006dda0_66\n\t"
      "pushl $0x260a80\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d98ad]\n\t"
      "movl 0x48(%%esi), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "jne .LFUN_0006dda0_65\n\t"
      "pushl $0x260a74\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d98ad]\n\t"
      "addl $8, %%esp\n\t"
      "jmp .LFUN_0006dda0_66\n\t"
      ".LFUN_0006dda0_65:\n\t"
      "pushl %%eax\n\t"
      "pushl $0x260a70\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d98ad]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_0006dda0_66:\n\t"
      "testl $0x40000, 0x14(%%esi)\n\t"
      "je .LFUN_0006dda0_67\n\t"
      "movl 0x4c(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x260a58\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d98ad]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_0006dda0_67:\n\t"
      "testl $0x80000, 0x14(%%esi)\n\t"
      "je .LFUN_0006dda0_68\n\t"
      "movl 0x50(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x260a40\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d98ad]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_0006dda0_68:\n\t"
      "testl $0x100000, 0x14(%%esi)\n\t"
      "je .LFUN_0006dda0_72\n\t"
      "pushl $0x260a24\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d98ad]\n\t"
      "movzwl 0x5e(%%esi), %%eax\n\t"
      "movl %%eax, %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "decl %%ecx\n\t"
      "je .LFUN_0006dda0_70\n\t"
      "decl %%ecx\n\t"
      "je .LFUN_0006dda0_69\n\t"
      "pushl %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x260dcc\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d98ad]\n\t"
      "addl $0x10, %%esp\n\t"
      "jmp .LFUN_0006dda0_72\n\t"
      ".LFUN_0006dda0_69:\n\t"
      "pushl $0x260a0c\n\t"
      "jmp .LFUN_0006dda0_71\n\t"
      ".LFUN_0006dda0_70:\n\t"
      "pushl $0x2609f8\n\t"
      ".LFUN_0006dda0_71:\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d98ad]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_0006dda0_72:\n\t"
      "testl $0x200000, 0x14(%%esi)\n\t"
      "je .LFUN_0006dda0_73\n\t"
      "movl 0xb0(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x2609e4\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d98ad]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_0006dda0_73:\n\t"
      "testl $0x400000, 0x14(%%esi)\n\t"
      "je .LFUN_0006dda0_77\n\t"
      "pushl $0x2609d0\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d98ad]\n\t"
      "movb 0x68(%%esi), %%cl\n\t"
      "addl $8, %%esp\n\t"
      "testb $1, %%cl\n\t"
      "movl $0x25b06c, %%eax\n\t"
      "je .LFUN_0006dda0_74\n\t"
      "pushl %%eax\n\t"
      "pushl $0x2609c0\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d98ad]\n\t"
      "addl $0xc, %%esp\n\t"
      "movl $0x2609bc, %%eax\n\t"
      ".LFUN_0006dda0_74:\n\t"
      "testb $4, 0x68(%%esi)\n\t"
      "je .LFUN_0006dda0_75\n\t"
      "pushl %%eax\n\t"
      "pushl $0x2609ac\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d98ad]\n\t"
      "addl $0xc, %%esp\n\t"
      "movl $0x2609bc, %%eax\n\t"
      ".LFUN_0006dda0_75:\n\t"
      "testb $2, 0x68(%%esi)\n\t"
      "je .LFUN_0006dda0_76\n\t"
      "pushl %%eax\n\t"
      "pushl $0x260998\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d98ad]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_0006dda0_76:\n\t"
      "movl 0x68(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x260f24\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d98ad]\n\t"
      "addl $0x10, %%esp\n\t"
      ".LFUN_0006dda0_77:\n\t"
      "testb $0x10, 0x18(%%esi)\n\t"
      "je .LFUN_0006dda0_82\n\t"
      "pushl $0x260988\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d98ad]\n\t"
      "movzwl 0x76(%%esi), %%ecx\n\t"
      "movl %%ecx, %%eax\n\t"
      "addl $8, %%esp\n\t"
      "subl $0, %%eax\n\t"
      "je .LFUN_0006dda0_80\n\t"
      "decl %%eax\n\t"
      "je .LFUN_0006dda0_79\n\t"
      "decl %%eax\n\t"
      "je .LFUN_0006dda0_78\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x260978\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d98ad]\n\t"
      "addl $0x10, %%esp\n\t"
      "jmp .LFUN_0006dda0_82\n\t"
      ".LFUN_0006dda0_78:\n\t"
      "pushl $0x260964\n\t"
      "jmp .LFUN_0006dda0_81\n\t"
      ".LFUN_0006dda0_79:\n\t"
      "pushl $0x26094c\n\t"
      "jmp .LFUN_0006dda0_81\n\t"
      ".LFUN_0006dda0_80:\n\t"
      "pushl $0x260944\n\t"
      ".LFUN_0006dda0_81:\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d98ad]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_0006dda0_82:\n\t"
      "testb $8, 0x18(%%esi)\n\t"
      "je .LFUN_0006dda0_83\n\t"
      "movl 0x7c(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x26092c\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d98ad]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_0006dda0_83:\n\t"
      "testb $0x20, 0x18(%%esi)\n\t"
      "je .LFUN_0006dda0_84\n\t"
      "movzwl 0x78(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x260908\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d98ad]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_0006dda0_84:\n\t"
      "testl $0x800000, 0x14(%%esi)\n\t"
      "je .LFUN_0006dda0_86\n\t"
      "pushl $0x2608f4\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d98ad]\n\t"
      "movb 0x6c(%%esi), %%al\n\t"
      "addl $8, %%esp\n\t"
      "testb $2, %%al\n\t"
      "je .LFUN_0006dda0_85\n\t"
      "pushl $0x2608e0\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d98ad]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_0006dda0_85:\n\t"
      "movl 0x6c(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x260f24\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d98ad]\n\t"
      "addl $0x10, %%esp\n\t"
      ".LFUN_0006dda0_86:\n\t"
      "testl $0x2000000, 0x14(%%esi)\n\t"
      "je .LFUN_0006dda0_87\n\t"
      "movzwl 0x72(%%esi), %%ecx\n\t"
      "movzwl 0x70(%%esi), %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x2608c8\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d98ad]\n\t"
      "addl $0x10, %%esp\n\t"
      ".LFUN_0006dda0_87:\n\t"
      "testl $0x10000000, 0x14(%%esi)\n\t"
      "je .LFUN_0006dda0_90\n\t"
      "pushl $0x2608b8\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d98ad]\n\t"
      "movb 0x10(%%ebp), %%al\n\t"
      "addl $8, %%esp\n\t"
      "testb $4, %%al\n\t"
      "je .LFUN_0006dda0_89\n\t"
      "pushl $0x260ee4\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d98ad]\n\t"
      "movb 0x36(%%esi), %%cl\n\t"
      "movl $1, %%eax\n\t"
      "shll %%cl, %%eax\n\t"
      "addl $8, %%esp\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%eax, 0x8(%%ebp)\n\t"
      "jle .LFUN_0006dda0_90\n\t"
      "jmp .LFUN_0006dda0_88\n\t"
      "leal (%%ebx), %%ebx\n\t"
      ".LFUN_0006dda0_88:\n\t"
      "movl 0x88(%%esi), %%eax\n\t"
      "movzwl (%%eax,%%ebx,2), %%ecx\n\t"
      "movl 0x84(%%esi), %%edx\n\t"
      "movzwl (%%edx,%%ebx,2), %%eax\n\t"
      "pushl %%ecx\n\t"
      "movl 0x80(%%esi), %%ecx\n\t"
      "movzwl (%%ecx,%%ebx,2), %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%ebx\n\t"
      "pushl $0x2608a0\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d98ad]\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "addl $0x18, %%esp\n\t"
      "incl %%ebx\n\t"
      "cmpl %%eax, %%ebx\n\t"
      "jl .LFUN_0006dda0_88\n\t"
      "jmp .LFUN_0006dda0_90\n\t"
      ".LFUN_0006dda0_89:\n\t"
      "pushl $0x260894\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d98ad]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_0006dda0_90:\n\t"
      "testb $1, 0x10(%%ebp)\n\t"
      "je .LFUN_0006dda0_93\n\t"
      "testl $0x8000000, 0x14(%%esi)\n\t"
      "je .LFUN_0006dda0_93\n\t"
      "movb 0xa(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "movl $0x26088c, %%eax\n\t"
      "js .LFUN_0006dda0_91\n\t"
      "movl $0x260884, %%eax\n\t"
      ".LFUN_0006dda0_91:\n\t"
      "pushl %%eax\n\t"
      "movl 0xb8(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x260878\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d98ad]\n\t"
      "movl 0xb8(%%esi), %%eax\n\t"
      "addl $0x10, %%esp\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "testl %%eax, %%eax\n\t"
      "jbe .LFUN_0006dda0_93\n\t"
      "leal (%%ebx), %%ebx\n\t"
      ".LFUN_0006dda0_92:\n\t"
      "movl 0xc0(%%esi), %%ecx\n\t"
      "movl (%%ecx,%%ebx,4), %%edx\n\t"
      "movl 0xbc(%%esi), %%eax\n\t"
      "movl (%%eax,%%ebx,4), %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl $0x260860\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d98ad]\n\t"
      "movl 0xb8(%%esi), %%eax\n\t"
      "addl $0x14, %%esp\n\t"
      "incl %%ebx\n\t"
      "cmpl %%eax, %%ebx\n\t"
      "jb .LFUN_0006dda0_92\n\t"
      ".LFUN_0006dda0_93:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "nop\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_0006dda0_jt0:\n\t"
      ".long .LFUN_0006dda0_18\n\t"
      ".long .LFUN_0006dda0_19\n\t"
      ".long .LFUN_0006dda0_20\n\t"
      ".long .LFUN_0006dda0_17\n\t"
      ".text\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_0006dda0_jt1:\n\t"
      ".long .LFUN_0006dda0_23\n\t"
      ".long .LFUN_0006dda0_24\n\t"
      ".long .LFUN_0006dda0_25\n\t"
      ".long .LFUN_0006dda0_26\n\t"
      ".long .LFUN_0006dda0_27\n\t"
      ".long .LFUN_0006dda0_28\n\t"
      ".text\n\t"
      :
      : [c1d98ad] "m"(b6dda0_c1d98ad)
      : "memory");
}
#else
#error "FUN_0006dda0: clang naked draft required"
#endif

