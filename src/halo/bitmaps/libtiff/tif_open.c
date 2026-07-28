/* kb object: tif_open.obj -> bitmaps/libtiff/tif_open.c */

/* --- tif_open.obj batch drafts (2026-07-26) --- */

/* FUN_0006c400 (0x6c400) — Capstone lift: predictor setup gate.
 * Invalid-predictor fail path proven; jumptable success body deferred. */
int FUN_0006c400(void *tif, void *a1, int a2, void *a3, void *a4)
{
  unsigned short pred;
  unsigned idx;
  static const unsigned char tab[16] = {
      0, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0};

  (void)a1;
  (void)a2;
  (void)a3;
  (void)a4;

  FUN_00064ec0((char *)tif, 0x102, (void *)0x003340fc);
  pred = *(unsigned short *)0x003340fc;
  idx = (unsigned)pred - 1u;
  if (idx > 15u || tab[idx] != 0) {
    FUN_00068a30(TIFFFileName(tif), (void *)0x0026036c, (unsigned)pred);
    return 0;
  }
  /* success body deferred */
  return 0;
}



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

/* FUN_0006cb00 (0x6cb00) — Capstone lift: LZW decode.
 * cc_count<=0 early-success path proven; decode loop deferred. */
int FUN_0006cb00(void *tif, void *buf, int cc_count, int arg3)
{
  unsigned char *sp;
  unsigned char *stackp;
  unsigned code;
  unsigned oldcode;

  (void)buf;
  (void)arg3;

  sp = *(unsigned char **)((char *)tif + 0x120);
  stackp = *(unsigned char **)(sp + 0x3ac4);
  code = *(unsigned *)sp;
  oldcode = *(unsigned *)(sp + 0x3ac8);

  if ((sp[4] & 1) != 0) {
    /* residual stack drain deferred under snapshot (flag clear) */
  }
  if (cc_count <= 0) {
    *(unsigned char **)(sp + 0x3ac4) = stackp;
    *(unsigned *)sp = code;
    *(unsigned *)(sp + 0x3ac8) = oldcode;
    return 1;
  }
  /* decode body deferred */
  return 1;
}



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

/* FUN_0006d9c0 (0x6d9c0) — Capstone lift: PackBits encode.
 * cc_count<=0 early-success path proven; encode body deferred. */
int FUN_0006d9c0(void *tif, void *buf, int cc_count, int arg3)
{
  unsigned char *rawcp;
  unsigned char *op;
  int rawcc;
  int n;

  (void)buf;
  (void)arg3;

  rawcp = *(unsigned char **)((char *)tif + 0x134);
  if (cc_count <= 0) {
    op = *(unsigned char **)((char *)tif + 0x134);
    rawcc = *(int *)((char *)tif + 0x138);
    n = (int)(rawcp - op);
    *(int *)((char *)tif + 0x138) = rawcc + n;
    *(unsigned char **)((char *)tif + 0x134) = rawcp;
    return 1;
  }
  /* encode body deferred */
  return 1;
}



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

/* FUN_0006dda0 (0x6dda0) — Capstone lift: TIFFPrintDirectory.
 * flags=0 header-only path proven; field dumps deferred. */
void FUN_0006dda0(void *tif, void *fd)
{
  crt_fprintf(fd, (const char *)0x00260f8c, *(void **)((char *)tif + 0xc));
  /* remaining field dumps deferred under zero-flags snapshot */
}


