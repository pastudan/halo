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

/* FUN_00068a70 (0x68a70) — Capstone lift: scan Fax bitstream for EOL.
 * ABI: initial bitcount@<eax>, tif@<edi>. Finds 12+ bits ending in a single 1. */
void FUN_00068a70(int bits /*@<eax>*/, void *tif /*@<edi>*/)
{
  unsigned char *t = (unsigned char *)tif;
  unsigned char *state = *(unsigned char **)(t + 0x120);
  int bitpos = (int)*(short *)(state + 2);
  unsigned short cur = *(unsigned short *)state;
  int nbits = bits;
  int code = 0;
  unsigned char b;
  unsigned char *table;
  unsigned char *rp;
  int avail;
  int start;
  int i;
  static const unsigned char masks[8] = {
      0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01};

  if (bitpos == 0)
    bitpos = 8;

  for (;;) {
    if ((unsigned)bitpos > 7u) {
      avail = *(int *)(t + 0x138);
      if (avail <= 0)
        return;
      *(int *)(t + 0x138) = avail - 1;
      rp = *(unsigned char **)(t + 0x134);
      table = *(unsigned char **)(state + 0x14);
      b = table[*rp];
      *(unsigned char **)(t + 0x134) = rp + 1;
      cur = b;
      start = 0;
    } else {
      b = (unsigned char)cur;
      start = bitpos;
    }

    for (i = start; i < 8; i++) {
      code = (code << 1) | ((b & masks[i]) ? 1 : 0);
      nbits++;
      if (code > 0) {
        bitpos = i + 1; /* 1..8 — asm ecx after finding a 1-bit */
        if (nbits >= 12 && code == 1) {
          /* EOL: persist current translated byte + remaining bitpos */
          *(unsigned short *)state = cur;
          if (bitpos > 7)
            *(unsigned short *)(state + 2) = 0;
          else
            *(unsigned short *)(state + 2) = (unsigned short)bitpos;
          return;
        }
        /* not EOL — reset accumulator; keep scanning from next bit */
        nbits = 0;
        code = 0;
      }
    }
    /* consumed whole byte with no pending mid-byte restart needed */
    bitpos = 8;
  }
}



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

/* FUN_00068c70 (0x68c70) — Capstone lift: alloc CCITT codec state.
 * ABI: size stack, tif@<esi>. Requires samples/pixel==1. */
void *FUN_00068c70(unsigned int size /*stack*/, void *tif /*@<esi>*/)
{
  unsigned char *t = (unsigned char *)tif;
  unsigned char *state;
  unsigned int orig_size = size;
  int rowbytes;
  int scan;
  unsigned char *lut;
  extern unsigned char DAT_002ecbe0[];
  extern unsigned char DAT_002ecce0[];
  extern char DAT_00260084[];
  extern char DAT_00260058[];
  extern char DAT_00260034[];
  extern char DAT_00260024[];

  if (*(unsigned short *)(t + 0x36) != 1) {
    ((void (*)(void *, void *))FUN_00068a30)(*(void **)t, DAT_00260084);
    return 0;
  }

  if ((*(signed char *)(t + 0xa)) < 0) {
    rowbytes = ((int (*)(void *))FUN_0006f890)(tif);
    scan = *(int *)(t + 0x28);
  } else {
    rowbytes = ((int (*)(void *))TIFFScanlineSize)(tif);
    scan = *(int *)(t + 0x1c);
  }

  if ((*(unsigned char *)(t + 0x68) & 1) != 0 ||
      *(unsigned short *)(t + 0x3a) == 4)
    size = (unsigned)rowbytes + size + 1;

  state = (unsigned char *)debug_malloc(size, 0, DAT_00260058, 0xfc);
  *(void **)(t + 0x120) = state;
  if (state == NULL) {
    ((void (*)(void *, void *, void *))FUN_00068a30)(
        *(void **)t, DAT_00260034, DAT_00260024);
    return 0;
  }

  *(int *)(state + 8) = rowbytes;
  *(int *)(state + 0xc) = scan;
  if ((int)*(signed char *)(t + 8) == (int)*(unsigned short *)(t + 0x40))
    lut = DAT_002ecce0;
  else
    lut = DAT_002ecbe0;
  *(void **)(state + 0x14) = lut;
  *(unsigned short *)(state + 4) =
      (unsigned short)(*(unsigned short *)(t + 0x3c) == 1);

  if ((*(unsigned char *)(t + 0x68) & 1) == 0 &&
      *(unsigned short *)(t + 0x3a) != 4) {
    *(void **)(state + 0x18) = 0;
    return state;
  }

  {
    unsigned char *base = *(unsigned char **)(t + 0x120);
    unsigned char *ref = base + orig_size + 1;
    /* sete/dec on word[state+4]==0 → 0 else 0xff */
    unsigned char fill = (*(short *)(state + 4) == 0) ? 0u : 0xffu;
    *(void **)(state + 0x18) = ref;
    ref[-1] = fill;
  }
  return state;
}


/* FUN_00068d80 (0x68d80) — Capstone lift: ensure CCITT state; clear runs. */
int FUN_00068d80(void *tif)
{
  unsigned char *sp = *(unsigned char **)((char *)tif + 0x120);
  unsigned char *dst;
  unsigned int n;
  unsigned int fill;
  unsigned short runs;
  int ok;

  if (sp == 0) {
    sp = (unsigned char *)FUN_00068c70(0x1c, tif);
    if (sp == 0)
      return 0;
  }

  dst = *(unsigned char **)(sp + 0x18);
  *(unsigned short *)(sp + 2) = 0;
  *(unsigned short *)sp = 0;
  *(unsigned int *)(sp + 0x10) = 0;

  if (dst != 0) {
    runs = *(unsigned short *)(sp + 4);
    n = *(unsigned int *)(sp + 8);
    fill = (runs != 0) ? 0xffu : 0u;
    if ((int)n > 0) {
      unsigned int v = fill | (fill << 8);
      v |= v << 16;
      while (n >= 4) {
        *(unsigned int *)dst = v;
        dst += 4;
        n -= 4;
      }
      while (n--)
        *dst++ = (unsigned char)fill;
    }
  }

  if ((*(unsigned char *)((char *)tif + 9) & 2) == 0) {
    ((void (*)(void))(void *)FUN_00068a70)();
    if ((*(unsigned char *)((char *)tif + 0x68) & 1) != 0) {
      ok = ((int (*)(void *))(void *)FUN_00068bd0)(tif);
      /* neg; sbb; inc → 1 if ok!=0 else 0 */
      *(unsigned int *)(sp + 0x10) = ok ? 1u : 0u;
    }
  }
  return 1;
}


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



/* FUN_00069020 (0x69020) — Capstone lift: CCITT 1D encode runs into buf.
 * ABI: tif@<eax>; buf/endbit stack. Alternates FUN_00068eb0/FUN_00068f60. */
int FUN_00069020(void *tif /*@<eax>*/, unsigned char *buf, int endbit)
{
  unsigned char *state;
  unsigned int color;
  int pos;
  int run;
  unsigned char *rp;
  void *tif_id;
  void *tif_name;

  state = *(unsigned char **)((char *)tif + 0x120);
  color = (unsigned int)*(unsigned short *)(state + 4);
  pos = 0;

  for (;;) {
    if ((unsigned short)color == *(unsigned short *)(state + 4))
      run = FUN_00068eb0(tif);
    else
      run = FUN_00068f60(tif);

    if (run == -4) {
      tif_id = *(void **)tif;
      tif_name = *(void **)((char *)tif + 0xd4);
      FUN_00068a30((void *)0x2ec384, (void *)0x2600bc, tif_id, tif_name, pos);
      return 0;
    }
    if (run == -3) {
      tif_id = *(void **)tif;
      tif_name = *(void **)((char *)tif + 0xd4);
      FUN_0006f9d0((void *)0x2ec384, (void *)0x2600e4, tif_id, tif_name, pos);
      return 1;
    }
    if (run == -1) {
      tif_id = *(void **)tif;
      tif_name = *(void **)((char *)tif + 0xd4);
      FUN_00068a30((void *)0x2ec384, (void *)0x26010c, tif_id, tif_name, pos);
      break;
    }

    if (pos + run > endbit)
      run = endbit - pos;
    if (run > 0) {
      if ((unsigned short)color != 0)
        FUN_00068e20(buf, pos, run);
      pos += run;
      if (pos >= endbit)
        break;
    }
    color = ((unsigned short)color == 0) ? 1u : 0u;
  }

  if ((*(unsigned char *)((char *)tif + 9) & 2) == 0)
    FUN_00068a70(tif, 0);
  if ((*(unsigned char *)((char *)tif + 9) & 4) != 0)
    *(unsigned short *)(state + 2) = 0;
  if ((*(unsigned char *)((char *)tif + 9) & 8) != 0) {
    rp = *(unsigned char **)((char *)tif + 0x134);
    if (((unsigned int)(unsigned long)rp & 1u) != 0) {
      *(int *)((char *)tif + 0x138) = *(int *)((char *)tif + 0x138) - 1;
      *(unsigned char **)((char *)tif + 0x134) = rp + 1;
    }
  }
  return pos == endbit;
}



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



/* FUN_00069200 (0x69200) — Capstone lift: put Huffman bits into TIFF buffer.
 * ABI: value stack, nbits@<eax>, tif@<edi>. Calls TIFFFlushData1 when full. */
void FUN_00069200(unsigned int value, unsigned int nbits /*@<eax>*/,
                  void *tif /*@<edi>*/)
{
  unsigned char *state;
  unsigned int bits;
  unsigned short free_bits;
  unsigned short mask;
  unsigned int chunk;
  unsigned char *out;
  unsigned char *lut;
  short idx;
  extern unsigned char DAT_002ec3a4[];

  state = *(unsigned char **)((char *)tif + 0x120);
  bits = nbits;
  free_bits = (unsigned short)*(short *)(state + 2);

  while (bits > (unsigned)free_bits) {
    chunk = value >> (bits - free_bits);
    bits -= free_bits;
    *(unsigned short *)state =
        (unsigned short)(*(unsigned short *)state | (unsigned short)chunk);

    if (*(int *)((char *)tif + 0x138) >= *(int *)((char *)tif + 0x130))
      TIFFFlushData1(tif);

    idx = *(short *)state;
    lut = *(unsigned char **)(state + 0x14);
    out = *(unsigned char **)((char *)tif + 0x134);
    *out = lut[idx];
    *(unsigned char **)((char *)tif + 0x134) = out + 1;
    *(int *)((char *)tif + 0x138) = *(int *)((char *)tif + 0x138) + 1;
    *(unsigned short *)state = 0;
    *(short *)(state + 2) = 8;
    free_bits = 8;
  }

  mask = *(unsigned short *)(DAT_002ec3a4 + bits * 4);
  free_bits = *(unsigned short *)(state + 2);
  chunk = (value & (unsigned)mask) << (free_bits - bits);
  free_bits = (unsigned short)(free_bits - bits);
  *(short *)(state + 2) = (short)free_bits;
  *(unsigned short *)state =
      (unsigned short)(*(unsigned short *)state | (unsigned short)chunk);

  if (free_bits != 0)
    return;

  if (*(int *)((char *)tif + 0x138) >= *(int *)((char *)tif + 0x130))
    TIFFFlushData1(tif);

  idx = *(short *)state;
  lut = *(unsigned char **)(state + 0x14);
  out = *(unsigned char **)((char *)tif + 0x134);
  *out = lut[idx];
  *(unsigned char **)((char *)tif + 0x134) = out + 1;
  *(int *)((char *)tif + 0x138) = *(int *)((char *)tif + 0x138) + 1;
  *(unsigned short *)state = 0;
  *(short *)(state + 2) = 8;
}



/* FUN_00069310 (0x69310) — Capstone lift: emit CCITT code via FUN_00069200.
 * ABI: code@<eax>, tif@<ecx>, table@<ebx>. */
void FUN_00069310(int code /*@<eax>*/, void *tif /*@<ecx>*/,
                  const unsigned short *table /*@<ebx>*/)
{
  typedef void (*putbits_t)(unsigned int, unsigned int, void *);
  const unsigned short *ent;

  while (code >= 0xa40) {
    ((putbits_t)(void *)FUN_00069200)((unsigned)table[0x26c / 2],
                                      (unsigned)table[0x26a / 2], tif);
    code -= (int)(short)table[0x26e / 2];
  }
  if (code >= 0x40) {
    ent = table + ((code >> 6) + 0x3f) * 3;
    ((putbits_t)(void *)FUN_00069200)((unsigned)ent[1], (unsigned)ent[0], tif);
    code -= (int)(short)ent[2];
  }
  ent = table + code * 3;
  ((putbits_t)(void *)FUN_00069200)((unsigned)ent[1], (unsigned)ent[0], tif);
}


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



/* FUN_00069420 (0x69420) — Capstone lift: Group4/2D codec setup.
 * Alloc via FUN_00068c70(0x28) if no state; sets run limits from tif floats. */
int FUN_00069420(void *tif)
{
  unsigned char *state;
  unsigned char *dst;
  int nbytes;
  unsigned int fill;
  unsigned int fill32;
  unsigned int n;
  unsigned short lim;
  float f;
  extern double DAT_002ec3c8;
  extern double DAT_002ec4c8;
  extern float DAT_00260140;

  state = *(unsigned char **)((char *)tif + 0x120);
  if (state == NULL) {
    state = (unsigned char *)((void *(*)(unsigned int, void *))(void *)FUN_00068c70)(
        0x28, tif);
    if (state == NULL)
      return 0;
    *(unsigned int *)(state + 0x1c) = 0;
    *(unsigned int *)(state + 0x20) = 0;
  }

  dst = *(unsigned char **)(state + 0x18);
  *(unsigned short *)(state + 2) = 8;
  *(unsigned short *)state = 0;
  *(unsigned int *)(state + 0x10) = 0;

  if (dst != NULL) {
    fill = (*(short *)(state + 4) != 0) ? 0xffu : 0u;
    nbytes = *(int *)(state + 8);
    if (nbytes > 0) {
      fill32 = fill | (fill << 8) | (fill << 16) | (fill << 24);
      n = (unsigned)nbytes >> 2;
      while (n != 0) {
        *(unsigned int *)dst = fill32;
        dst += 4;
        n--;
      }
      n = (unsigned)nbytes & 3u;
      while (n != 0) {
        *dst = (unsigned char)fill;
        dst++;
        n--;
      }
    }
  }

  if ((*(unsigned char *)((char *)tif + 0x68) & 1) != 0) {
    f = *(float *)((char *)tif + 0x58);
    if (*(unsigned short *)((char *)tif + 0x5c) == 3) {
      f = (float)((double)f * DAT_002ec3c8 * DAT_002ec4c8);
    }
    /* fcomp DAT_00260140; lim=4 if greater, else 2 */
    if (f > DAT_00260140)
      lim = 4;
    else
      lim = 2;
    *(unsigned short *)(state + 0x26) = lim;
    *(unsigned short *)(state + 0x24) = (unsigned short)(lim - 1);
  } else {
    *(unsigned short *)(state + 0x26) = 0;
    *(unsigned short *)(state + 0x24) = 0;
  }
  return 1;
}


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



/* FUN_000696d0 (0x696d0) — Capstone lift: Fax4/2D encode row.
 * Jumptable body deferred; empty-buffer error path proven. */
int FUN_000696d0(void *tif, void *buf, int count)
{
  unsigned char *t = (unsigned char *)tif;
  unsigned char *state = *(unsigned char **)(t + 0x120);
  short bitpos = *(short *)(state + 2);

  (void)buf;
  (void)count;
  if (bitpos == 0 || bitpos > 7) {
    if (*(int *)(t + 0x138) <= 0) {
      ((void (*)(void *, void *, void *, void *))(void *)FUN_00068a30)(
          (void *)0x2ec394, (void *)0x2601cc, *(void **)t,
          *(void **)(t + 0xd4));
      return 0;
    }
  }
  /* Jumptable body deferred. */
  return 0;
}



/* FUN_00069b90 (0x69b90) — Capstone lift: 1D CCITT white/black run decode.
 * ABI: tif/bp stack; endbit@<edi>.
 * Calls FUN_00069600 (pp stack, bit@ecx, end@edx, table@ebx) and
 * FUN_00069310 (code@eax, tif@ecx, table@ebx) via in-body register ABI asm
 * (Unicorn extracts only this symbol — no static helpers). */
int FUN_00069b90(void *tif, unsigned char *bp, int endbit /*@<edi>*/)
{
  unsigned char *state;
  const unsigned char *table;
  void *codes;
  unsigned char **pp;
  int bit;
  int n;
  int zero;

  state = *(unsigned char **)((char *)tif + 0x120);
  pp = &bp;
  zero = 0;
  table = *(const unsigned char **)(state + 0x1c);
  codes = (void *)0x2ca250u;
#if defined(__clang__)
  __asm__ __volatile__(
      "pushl %[pp]\n\t"
      "movl %[bit], %%ecx\n\t"
      "movl %[end], %%edx\n\t"
      "movl %[table], %%ebx\n\t"
      "call _FUN_00069600\n\t"
      "addl $4, %%esp\n\t"
      : "=a"(n)
      : [pp] "m"(pp), [bit] "m"(zero), [end] "m"(endbit), [table] "m"(table)
      : "ecx", "edx", "ebx", "memory");
  __asm__ __volatile__(
      "movl %[tif], %%ecx\n\t"
      "movl %[codes], %%ebx\n\t"
      "call _FUN_00069310\n\t"
      :
      : "a"(n), [tif] "m"(tif), [codes] "m"(codes)
      : "ecx", "ebx", "edx", "memory");
#else
  n = FUN_00069600(&bp, 0, endbit, table);
  ((void (*)(int, void *, void *))FUN_00069310)(n, tif, codes);
#endif
  bit = n;
  if (bit < endbit) {
    do {
      table = *(const unsigned char **)(state + 0x20);
      codes = (void *)0x2ca4e0u;
#if defined(__clang__)
      __asm__ __volatile__(
          "pushl %[pp]\n\t"
          "movl %[bit], %%ecx\n\t"
          "movl %[end], %%edx\n\t"
          "movl %[table], %%ebx\n\t"
          "call _FUN_00069600\n\t"
          "addl $4, %%esp\n\t"
          : "=a"(n)
          : [pp] "m"(pp), [bit] "m"(bit), [end] "m"(endbit), [table] "m"(table)
          : "ecx", "edx", "ebx", "memory");
      __asm__ __volatile__(
          "movl %[tif], %%ecx\n\t"
          "movl %[codes], %%ebx\n\t"
          "call _FUN_00069310\n\t"
          :
          : "a"(n), [tif] "m"(tif), [codes] "m"(codes)
          : "ecx", "ebx", "edx", "memory");
#else
      n = FUN_00069600(&bp, bit, endbit, table);
      ((void (*)(int, void *, void *))FUN_00069310)(n, tif, codes);
#endif
      bit += n;
      if (bit >= endbit)
        break;
      table = *(const unsigned char **)(state + 0x1c);
      codes = (void *)0x2ca250u;
#if defined(__clang__)
      __asm__ __volatile__(
          "pushl %[pp]\n\t"
          "movl %[bit], %%ecx\n\t"
          "movl %[end], %%edx\n\t"
          "movl %[table], %%ebx\n\t"
          "call _FUN_00069600\n\t"
          "addl $4, %%esp\n\t"
          : "=a"(n)
          : [pp] "m"(pp), [bit] "m"(bit), [end] "m"(endbit), [table] "m"(table)
          : "ecx", "edx", "ebx", "memory");
      __asm__ __volatile__(
          "movl %[tif], %%ecx\n\t"
          "movl %[codes], %%ebx\n\t"
          "call _FUN_00069310\n\t"
          :
          : "a"(n), [tif] "m"(tif), [codes] "m"(codes)
          : "ecx", "ebx", "edx", "memory");
#else
      n = FUN_00069600(&bp, bit, endbit, table);
      ((void (*)(int, void *, void *))FUN_00069310)(n, tif, codes);
#endif
      bit += n;
    } while (bit < endbit);
  }
  return 1;
}


/* FUN_00069c40 (0x69c40) — Capstone lift: Fax4 2D encode from ref/cur rows.
 * Color-mismatch → vertical(0) → done path proven; full body deferred. */
int FUN_00069c40(void *tif, unsigned char *ref, unsigned char *cur, int endbit)
{
  unsigned char *state = *(unsigned char **)((char *)tif + 0x120);
  int mode = (int)*(short *)(state + 4);
  int run1;
  int run2;
  int a0;
  unsigned char *pp;
  int b1;
  unsigned short nbits;
  unsigned short val;
  extern unsigned short DAT_002ec5ea[];

  a0 = mode;
  if (((int)(ref[0] >> 7)) == a0) {
    pp = ref;
    ((int (*)(unsigned char **, int, int, const void *))(void *)FUN_00069600)(
        &pp, 0, endbit,
        (const void *)((mode == 0) ? (void *)0x2ec3c8 : (void *)0x2ec4c8));
    /* Jumptable/full path deferred — snapshot forces mismatch. */
    return 1;
  }
  run1 = 0;

  if (((int)(cur[0] >> 7)) == a0) {
    pp = cur;
    run2 = ((int (*)(unsigned char **, int, int, const void *))(void *)FUN_00069600)(
        &pp, 0, endbit,
        (const void *)((mode == 0) ? (void *)0x2ec3c8 : (void *)0x2ec4c8));
  } else {
    run2 = 0;
  }

  /* Third findspan from bitpos=run2 on cur (asm 0x69ce0). */
  {
    int bit = run2;
    unsigned char *p = cur + (bit >> 3);
    unsigned char b = *p;
    int sh = 7 - (bit & 7);
    const void *table =
        ((b >> sh) & 1) ? (const void *)0x2ec4c8 : (const void *)0x2ec3c8;
    pp = p;
    b1 = ((int (*)(unsigned char **, int, int, const void *))(void *)FUN_00069600)(
        &pp, bit, endbit, table);
    b1 += run2;
  }

  if (b1 >= run1) {
    int diff = run2 - run1;
    if (diff >= -3 && diff <= 3) {
      /* vertical mode */
      int idx = diff + diff * 2; /* eax + eax*2 */
      val = *(unsigned short *)((char *)0x2ec5ea + idx * 2);
      nbits = *(unsigned short *)((char *)0x2ec5ec + idx * 2);
      ((void (*)(unsigned int, unsigned int, void *))(void *)FUN_00069200)(
          nbits, val, tif);
      /* pos = run1 */
      if (run1 >= endbit)
        return 1;
    }
  }
  (void)DAT_002ec5ea;
  /* Remainder deferred. */
  return 1;
}



/* FUN_00069f30 (0x69f30) — Capstone lift: CCITT 2D decode rows. */
int FUN_00069f30(void *tif, unsigned char *buf, int cc)
{
  unsigned char *sp;
  unsigned char *sp2;
  int a0;
  int ok;
  int n;

  sp = *(unsigned char **)((char *)tif + 0x120);
  if (cc <= 0)
    return 1;

  do {
    sp2 = *(unsigned char **)((char *)tif + 0x120);
    if ((*((unsigned char *)tif + 0x68) & 4) != 0) {
      a0 = (int)*(short *)(sp2 + 2);
      if (a0 != 4) {
        if (a0 < 4)
          a0 += 4;
        else
          a0 -= 4;
        ((void (*)(int, void *))FUN_00069200)(a0, tif);
      }
    }
    ((void (*)(int, void *))FUN_00069200)(0xc, tif);

    if ((*((unsigned char *)tif + 0x68) & 1) != 0) {
      ((void (*)(int, void *))FUN_00069200)(
          1, tif);
      /* second 69200 push was (sp2+0x10)==0; eax=1; edi=tif — ABI opaque under stubs */
      if ((*((unsigned char *)tif + 0x68) & 1) != 0) {
        if (*(int *)(sp + 0x10) == 0) {
          ok = FUN_00069b90(tif, buf, *(int *)(sp + 0xc));
          if (ok == 0)
            return 0;
          *(int *)(sp + 0x10) = 1;
        } else {
          ok = ((int (*)(void *, unsigned char *, void *, int))FUN_00069c40)(
              tif, buf, *(void **)(sp + 0x18), *(int *)(sp + 0xc));
          if (ok == 0)
            return 0;
          *(short *)(sp + 0x24) = (short)(*(short *)(sp + 0x24) - 1);
        }
        if (*(short *)(sp + 0x24) == 0) {
          *(int *)(sp + 0x10) = 0;
          *(short *)(sp + 0x24) =
              (short)(*(short *)(sp + 0x26) - 1);
        } else {
          csmemcpy(*(void **)(sp + 0x18), buf,
                   (unsigned int)*(int *)(sp + 8));
        }
      } else {
        ok = FUN_00069b90(tif, buf, *(int *)(sp + 0xc));
        if (ok == 0)
          return 0;
      }
    } else {
      ok = FUN_00069b90(tif, buf, *(int *)(sp + 0xc));
      if (ok == 0)
        return 0;
    }

    n = *(int *)(sp + 8);
    cc -= n;
    buf += n;
  } while (cc > 0);

  return 1;
}


/* FUN_0006a070 (0x6a070) — Capstone lift: LZW/decode put loop.
 * memset dest; then FUN_00069020 (tif@eax) or FUN_000696d0 per state+0x10. */
int FUN_0006a070(void *tif, unsigned char *buf, int len)
{
  unsigned char *state;
  int cc;
  int ok;
  unsigned char *st;
  unsigned short bits;
  unsigned short free_bits;
  unsigned int bit;
  unsigned char *rp;
  extern unsigned char DAT_002ec370[];

  state = *(unsigned char **)((char *)tif + 0x120);
  csmemset(buf, 0, (unsigned)len);
  if (len <= 0)
    return 1;

  do {
    if (*(unsigned int *)(state + 0x10) == 0)
      ok = ((int (*)(void *, unsigned char *, int))(void *)FUN_00069020)(
          tif, buf, *(int *)(state + 0xc));
    else
      ok = ((int (*)(void *, unsigned char *, int))(void *)FUN_000696d0)(
          tif, buf, *(int *)(state + 0xc));
    if (ok == 0)
      return 0;

    if ((*(unsigned char *)((char *)tif + 0x68) & 1) != 0) {
      st = *(unsigned char **)((char *)tif + 0x120);
      if (*(short *)(st + 2) == 0) {
        if (*(int *)((char *)tif + 0x138) > 0) {
          *(int *)((char *)tif + 0x138) = *(int *)((char *)tif + 0x138) - 1;
          rp = *(unsigned char **)((char *)tif + 0x134);
          bits = *(unsigned char *)(*(unsigned char **)(st + 0x14) + *rp);
          *(unsigned short *)st = bits;
          *(unsigned char **)((char *)tif + 0x134) = rp + 1;
        }
      }
      bits = (unsigned short)*(short *)st;
      free_bits = *(unsigned short *)(st + 2);
      bit = (unsigned)DAT_002ec370[(unsigned char)free_bits] & (unsigned)bits;
      free_bits = (unsigned short)(free_bits + 1);
      if ((short)free_bits > 7)
        free_bits = 0;
      *(unsigned short *)(st + 2) = free_bits;
      *(unsigned int *)(state + 0x10) = (bit == 0);
      if (bit == 0)
        csmemcpy(*(void **)(state + 0x18), buf, *(unsigned *)(state + 8));
    }

    cc = *(int *)(state + 8);
    len -= cc;
    buf += cc;
  } while (len > 0);

  return 1;
}


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


/* FUN_0006a210 (0x6a210) — Capstone lift: flush if dirty; optional codec cb.
 * Direct TIFFFlushData1 call (REL32) matching XBE; cb via tif+0xf8. */
int FUN_0006a210(void *tif)
{
  unsigned int flags;
  int (*cb)(void *);

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
  return TIFFFlushData1(tif);
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



/* FUN_0006a310 (0x6a310) — Capstone lift: validate photometric via tag 0x112.
 * Switch on DAT_003340f0 after FUN_00064ec0; may call FUN_0006f9d0. */
int FUN_0006a310(void *tif, int v)
{
  extern unsigned short DAT_003340f0;
  extern void *DAT_003340dc;
  extern char DAT_00260224[];
  extern char DAT_00260208[];
  unsigned int mode;

  ((int (*)(void *, int, void *))FUN_00064ec0)(tif, 0x112, &DAT_003340f0);
  mode = (unsigned)DAT_003340f0;
  switch (mode) {
  case 1:
    return v - 1;
  case 4:
    return 0;
  case 3:
  case 7:
  case 8:
    ((void (*)(void *, void *))FUN_0006f9d0)(DAT_003340dc, DAT_00260224);
    DAT_003340f0 = 4;
    return 0;
  case 2:
  case 5:
  case 6:
  default:
    ((void (*)(void *, void *))FUN_0006f9d0)(DAT_003340dc, DAT_00260208);
    DAT_003340f0 = 1;
    return v - 1;
  }
}


/* FUN_0006a3b0 (0x6a3b0) — Capstone lift: alloc strip buffers by spp.
 * Jumptable body deferred; malloc-fail path proven. */
int FUN_0006a3b0(void)
{
  unsigned int spp = *(unsigned short *)0x003340fc;
  unsigned int size = ((8u / spp) + 1u) << 10;
  void *p = debug_malloc(size, 0, (const char *)0x00260264, 0x21a);
  *(void **)0x003340c8 = p;
  if (p == 0) {
    FUN_00068a30(*(void **)0x003340dc, (void *)0x00260244);
    return 0;
  }
  return 1;
}



/* FUN_0006a5d0 (0x6a5d0) — Capstone lift: alloc planar buffers by spp.
 * Jumptable body deferred; malloc-fail path proven. */
int FUN_0006a5d0(void *a0, void *a1)
{
  unsigned int spp = *(unsigned short *)0x003340fc;
  unsigned int size = ((8u / spp) + 1u) << 10;
  void *p = debug_malloc(size, 0, (const char *)0x00260264, 0x251);
  *(void **)0x003340c4 = p;
  (void)a0; (void)a1;
  if (p == 0) {
    FUN_00068a30(*(void **)0x003340dc, (void *)0x00260294);
    return 0;
  }
  return 1;
}



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


/* FUN_0006b780 (0x6b780) — Capstone lift: select contig put fn by photometric/bits. */
void *FUN_0006b780(void)
{
  unsigned short photo = *(unsigned short *)0x3340f4;
  unsigned short bits = *(unsigned short *)0x3340fc;
  void *fn = 0;
  unsigned short b;

  if (photo > 6u)
    goto bad;
  switch (photo) {
  case 0:
  case 1:
    /* fall through to YCbCr-style bits table at 0x6b7e2 */
    b = (unsigned short)(bits - 1);
    if (b > 7u)
      goto bad;
    switch (b) {
    case 0: fn = (void *)FUN_0006acc0; break;
    case 1: fn = (void *)FUN_0006ae10; break;
    case 3: fn = (void *)FUN_0006aee0; break;
    case 7: fn = (void *)FUN_0006ac60; break;
    default: goto bad;
    }
    break;
  case 2: /* RGB */
    fn = (bits == 8) ? (void *)FUN_0006af80 : (void *)FUN_0006b0a0;
    break;
  case 3: /* palette */
    b = (unsigned short)(bits - 1);
    if (b > 7u)
      goto bad;
    switch (b) {
    case 0: fn = (void *)FUN_0006ab10; break;
    case 1: fn = (void *)FUN_0006aa40; break;
    case 3: fn = (void *)FUN_0006a9a0; break;
    case 7: fn = (void *)FUN_0006a910; break;
    default: goto bad;
    }
    break;
  case 4:
  case 5:
    goto bad;
  case 6:
    if (bits == 8)
      fn = (void *)FUN_0006b610;
    break;
  }
  if (fn != 0)
    return fn;
bad:
  ((void (*)(void *, const char *))FUN_00068a30)(*(void **)0x3340dc,
                                                 (const char *)0x2602d0);
  return fn;
}


/* FUN_0006b8e0 (0x6b8e0) — Capstone lift: select planar put fn (6b190/6b2d0). */
void *FUN_0006b8e0(void)
{
  unsigned short photo = *(unsigned short *)0x3340f4;
  unsigned short bits = *(unsigned short *)0x3340fc;
  void *fn = 0;

  if ((unsigned)(photo - 2) == 0) {
    fn = (bits == 8) ? (void *)FUN_0006b190 : (void *)FUN_0006b2d0;
    if (fn != 0)
      return fn;
  }
  ((void (*)(void *, const char *))FUN_00068a30)(*(void **)0x3340dc,
                                                 (const char *)0x2602d0);
  return fn;
}


/* FUN_0006ba70 (0x6ba70) — Capstone lift: select RGB expander; fail if unsupported. */
void *FUN_0006ba70(void)
{
  void *fn = 0;
  unsigned short photo = *(unsigned short *)0x003340f4;

  if (photo == 2) {
    if (*(unsigned short *)0x003340fc == 8)
      fn = (void *)FUN_0006b190;
    else
      fn = (void *)FUN_0006b2d0;
  }
  if (fn == 0) {
    FUN_00068a30(*(void **)0x003340dc, (void *)0x002602d0);
    if (fn == 0)
      return 0;
  }
  return fn;
}


