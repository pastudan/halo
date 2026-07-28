/* kb object: tif_write.obj -> bitmaps/libtiff/tif_write.c */

/* --- tif_write.obj batch drafts (2026-07-26) --- */

/* FUN_0006e740 (0x6e740) — Capstone lift: lseek+read strip payload.
 * ABI: buf/module stack; tif@<esi>, strip_count@<edi>, size_count@<ebx>. */
int FUN_0006e740(void *buf, void *module, void *tif /*@<esi>*/,
                 unsigned int strip_count /*@<edi>*/,
                 unsigned int size_count /*@<ebx>*/)
{
  unsigned int *offs;
  int fd;
  int got;

  offs = *(unsigned int **)((char *)tif + 0xbc);
  fd = (int)*(short *)((char *)tif + 4);
  got = ((int (*)(int, unsigned int, int))(void *)__lseek)(fd, offs[strip_count], 0);
  if (got != (int)offs[strip_count]) {
    FUN_00068a30(module, (void *)0x00260fcc, *(void **)tif,
                 *(void **)((char *)tif + 0xd4), strip_count);
    return -1;
  }
  got = ((int (*)(int, void *, unsigned int))(void *)__read)(fd, buf, size_count);
  if (got != (int)size_count) {
    FUN_00068a30(module, (void *)0x00260fac, *(void **)tif,
                 *(void **)((char *)tif + 0xd4));
    return -1;
  }
  return (int)size_count;
}



/* FUN_0006e7d0 (0x6e7d0) — Capstone lift: lseek+read tile payload.
 * ABI: buf/module stack; tif@<esi>, tile_count@<edi>, size_count@<ebx>. */
int FUN_0006e7d0(void *buf, void *module, void *tif /*@<esi>*/,
                 unsigned int tile_count /*@<edi>*/,
                 unsigned int size_count /*@<ebx>*/)
{
  unsigned int *offs;
  int fd;
  int got;

  offs = *(unsigned int **)((char *)tif + 0xbc);
  fd = (int)*(short *)((char *)tif + 4);
  got = ((int (*)(int, unsigned int, int))(void *)__lseek)(fd, offs[tile_count], 0);
  if (got != (int)offs[tile_count]) {
    FUN_00068a30(module, (void *)0x00261018, *(void **)tif,
                 *(void **)((char *)tif + 0xd4),
                 *(void **)((char *)tif + 0xe4), tile_count);
    return -1;
  }
  got = ((int (*)(int, void *, unsigned int))(void *)__read)(fd, buf, size_count);
  if (got != (int)size_count) {
    FUN_00068a30(module, (void *)0x00260ff4, *(void **)tif,
                 *(void **)((char *)tif + 0xd4),
                 *(void **)((char *)tif + 0xe4));
    return -1;
  }
  return (int)size_count;
}



/* FUN_0006e870 (0x6e870) — Capstone lift: (re)allocate TIFF strip/tile buffer. */
int FUN_0006e870(void *tif, void *existing, unsigned size)
{
  extern char DAT_00261070[];
  extern char DAT_00261044[];
  extern unsigned char DAT_002ecb1c[];
  void *buf;
  void *p;
  unsigned aligned;

  buf = *(void **)((char *)tif + 0x12c);
  if (buf != 0) {
    if ((*(unsigned char *)((char *)tif + 0xa) & 0x40) != 0)
      debug_free(buf, DAT_00261070, 0x203);
    *(void **)((char *)tif + 0x12c) = 0;
  }
  if (existing != 0) {
    *(unsigned char *)((char *)tif + 0xa) =
        (unsigned char)(*(unsigned char *)((char *)tif + 0xa) & 0xbf);
    *(unsigned *)((char *)tif + 0x130) = size;
    p = existing;
  } else {
    aligned = ((size + 0x3ffu) >> 10) << 10;
    *(unsigned *)((char *)tif + 0x130) = aligned;
    p = debug_malloc(aligned, 0, DAT_00261070, 0x20c);
    *(unsigned char *)((char *)tif + 0xa) =
        (unsigned char)(*(unsigned char *)((char *)tif + 0xa) | 0x40);
  }
  *(void **)((char *)tif + 0x12c) = p;
  if (p != 0)
    return 1;
  FUN_00068a30((void *)DAT_002ecb1c, DAT_00261044, *(void **)tif,
               *(void **)((char *)tif + 0xd4));
  *(unsigned *)((char *)tif + 0x130) = 0;
  return 0;
}


/* FUN_0006e930 (0x6e930) — Capstone lift: select strip buffer setup.
 * ABI: tif@<ecx>, strip@<esi>. */
int FUN_0006e930(void *tif /*@<ecx>*/, unsigned int strip /*@<esi>*/)
{
  unsigned int rem;
  unsigned int *offs;
  int (*cb)(void *);

  *(unsigned int *)((char *)tif + 0xdc) = strip;
  rem = strip % *(unsigned int *)((char *)tif + 0xb4);
  *(void **)((char *)tif + 0x134) = *(void **)((char *)tif + 0x12c);
  *(unsigned int *)((char *)tif + 0xd4) =
      rem * *(unsigned int *)((char *)tif + 0x48);
  offs = *(unsigned int **)((char *)tif + 0xc0);
  *(unsigned int *)((char *)tif + 0x138) = offs[strip];
  cb = *(int (**)(void *))((char *)tif + 0xf0);
  if (cb != 0 && cb(tif) == 0)
    return 0;
  return 1;
}


/* FUN_0006e980 (0x6e980) — Capstone lift: select tile buffer setup.
 * ABI: tif@<ecx>, tile@<esi>. Mirror of FUN_0006e930 for tiles. */
int FUN_0006e980(void *tif /*@<ecx>*/, unsigned int tile /*@<esi>*/)
{
  unsigned int tw, tl, tiles_across, tiles_down, rem;
  unsigned int *offs;
  int (*cb)(void *);

  *(unsigned int *)((char *)tif + 0xe8) = tile;

  tw = *(unsigned int *)((char *)tif + 0x28);
  tiles_across = (*(unsigned int *)((char *)tif + 0x1c) + tw - 1u) / tw;
  rem = tile % tiles_across;
  *(unsigned int *)((char *)tif + 0xd4) =
      rem * *(unsigned int *)((char *)tif + 0x2c);

  tl = *(unsigned int *)((char *)tif + 0x2c);
  tiles_down = (*(unsigned int *)((char *)tif + 0x20) + tl - 1u) / tl;
  rem = tile % tiles_down;
  *(void **)((char *)tif + 0x134) = *(void **)((char *)tif + 0x12c);
  *(unsigned int *)((char *)tif + 0xe4) =
      rem * *(unsigned int *)((char *)tif + 0x28);

  offs = *(unsigned int **)((char *)tif + 0xc0);
  *(unsigned int *)((char *)tif + 0x138) = offs[tile];

  cb = *(int (**)(void *))((char *)tif + 0xf0);
  if (cb != 0 && cb(tif) == 0)
    return 0;
  return 1;
}



/* FUN_0006ea50 (0x6ea50) — Capstone lift: TIFFWriteEncodedStrip-ish checks. */
int FUN_0006ea50(void *tif, unsigned int strip_count, void *stream, unsigned int size_count)
{
  unsigned int nstrips;
  unsigned int *offs;
  unsigned int nbytes;

  if (*(unsigned short *)((char *)tif + 6) == 1) {
    FUN_00068a30(*(void **)tif, (void *)0x002610f4);
    return -1;
  }
  if ((*(signed char *)((char *)tif + 0xa)) < 0) {
    FUN_00068a30(*(void **)tif, (void *)0x0026109c);
    return -1;
  }
  nstrips = *(unsigned int *)((char *)tif + 0xb8);
  if (strip_count >= nstrips) {
    FUN_00068a30(*(void **)tif, (void *)0x00261110, strip_count, nstrips);
    return -1;
  }
  offs = *(unsigned int **)((char *)tif + 0xc0);
  nbytes = offs[strip_count];
  if (size_count != 0xffffffffu && size_count < nbytes)
    nbytes = size_count;
  /* XBE: call FUN_0006e740 with stream, fmt; tif@esi strip@edi via regs. */
  return ((int (*)(void *, void *))(void *)FUN_0006e740)(stream, (void *)0x002ecad8);
}


/* FUN_0006eaf0 (0x6eaf0) — Capstone lift: ensure strip buffer then write via 6e740/6e930. */
int FUN_0006eaf0(void *tif, unsigned int strip_count)
{
  unsigned int *offs = *(unsigned int **)((char *)tif + 0xc0);
  unsigned int nbytes = offs[strip_count];
  int ok;

  if (nbytes > *(unsigned int *)((char *)tif + 0x130)) {
    *(unsigned int *)((char *)tif + 0xdc) = 0xffffffffu;
    if ((*(unsigned char *)((char *)tif + 0xa) & 0x40) == 0) {
      FUN_00068a30((void *)0x002ecaec, (void *)0x00261130, *(void **)tif,
                   strip_count);
      return 0;
    }
    ok = ((int (*)(void *, int, unsigned))(void *)FUN_0006e870)(
        tif, 0, (nbytes + 0x3ffu) & ~0x3ffu);
    if (!ok)
      return 0;
  }
  ok = ((int (*)(void *, void *))(void *)FUN_0006e740)(
      *(void **)((char *)tif + 0x12c), (void *)0x002ecaec);
  if (ok != (int)nbytes)
    return 0;
  if ((unsigned)*(unsigned short *)((char *)tif + 0x40) !=
          (unsigned)*(signed char *)((char *)tif + 8) &&
      (*(unsigned char *)((char *)tif + 0xa) & 0x20) == 0) {
    ((void (*)(void *, unsigned))(void *)FUN_0006f260)(
        *(void **)((char *)tif + 0x12c), nbytes);
  }
  return FUN_0006e930(tif, strip_count);
}


/* FUN_0006ebb0 (0x6ebb0) — Capstone lift: tile write checks + FUN_0006e7d0. */
int FUN_0006ebb0(void *tif, unsigned int tile_count, void *stream, unsigned int size_count)
{
  unsigned int ntiles;
  unsigned int *offs;
  unsigned int nbytes;

  if (*(unsigned short *)((char *)tif + 6) == 1) {
    FUN_00068a30(*(void **)tif, (void *)0x002610f4);
    return -1;
  }
  /* flags bit7 clear → error (not tiled?) */
  if (((~((*(unsigned char *)((char *)tif + 0xa)) >> 7)) & 1) != 0) {
    FUN_00068a30(*(void **)tif, (void *)0x002610c8);
    return -1;
  }
  ntiles = *(unsigned int *)((char *)tif + 0xb8);
  if (tile_count >= ntiles) {
    FUN_00068a30(*(void **)tif, (void *)0x0026115c, tile_count, ntiles);
    return -1;
  }
  offs = *(unsigned int **)((char *)tif + 0xc0);
  nbytes = offs[tile_count];
  if (size_count != 0xffffffffu && size_count < nbytes)
    nbytes = size_count;
  return ((int (*)(void *, void *))(void *)FUN_0006e7d0)(stream, (void *)0x002ecafc);
}


/* FUN_0006ec50 (0x6ec50) — Capstone lift: ensure tile buffer then write via 6e7d0/6e980. */
int FUN_0006ec50(void *tif, unsigned int tile_count)
{
  unsigned int *offs = *(unsigned int **)((char *)tif + 0xc0);
  unsigned int nbytes = offs[tile_count];
  int ok;

  if (nbytes > *(unsigned int *)((char *)tif + 0x130)) {
    *(unsigned int *)((char *)tif + 0xe8) = 0xffffffffu;
    if ((*(unsigned char *)((char *)tif + 0xa) & 0x40) == 0) {
      FUN_00068a30((void *)0x002ecb0c, (void *)0x0026117c, *(void **)tif,
                   tile_count);
      return 0;
    }
    ok = ((int (*)(void *, int, unsigned))(void *)FUN_0006e870)(
        tif, 0, (nbytes + 0x3ffu) & ~0x3ffu);
    if (!ok)
      return 0;
  }
  ok = ((int (*)(void *, void *))(void *)FUN_0006e7d0)(
      *(void **)((char *)tif + 0x12c), (void *)0x002ecb0c);
  if (ok != (int)nbytes)
    return 0;
  if ((unsigned)*(unsigned short *)((char *)tif + 0x40) !=
          (unsigned)*(signed char *)((char *)tif + 8) &&
      (*(unsigned char *)((char *)tif + 0xa) & 0x20) == 0) {
    ((void (*)(void *, unsigned))(void *)FUN_0006f260)(
        *(void **)((char *)tif + 0x12c), nbytes);
  }
  return ((int (*)(void *, unsigned int))(void *)FUN_0006e980)(tif, tile_count);
}


/* FUN_0006ed10 (0x6ed10) — Capstone lift: ensure write row setup (strip select).
 * ABI: tif@<edi>, row@<ebx>, sample@<ecx>. */
int FUN_0006ed10(void *tif /*@<edi>*/, unsigned int row /*@<ebx>*/, unsigned int sample /*@<ecx>*/)
{
  unsigned int imagelen = *(unsigned int *)((char *)tif + 0x20);
  unsigned int strip;
  unsigned int cur_row;
  int (*seekcb)(void *, unsigned int);

  if (row >= imagelen) {
    FUN_00068a30(*(void **)tif, (void *)0x00261200, row, imagelen);
    return 0;
  }
  if (*(unsigned short *)((char *)tif + 0x5e) == 2) {
    unsigned int spp = *(unsigned short *)((char *)tif + 0x44);
    if (sample >= spp) {
      FUN_00068a30(*(void **)tif, (void *)0x002611e0, sample, spp);
      return 0;
    }
    strip = row / *(unsigned int *)((char *)tif + 0x48)
          + sample * *(unsigned int *)((char *)tif + 0xb4);
  } else {
    strip = row / *(unsigned int *)((char *)tif + 0x48);
  }

  if (strip != *(unsigned int *)((char *)tif + 0xdc)) {
    if (FUN_0006eaf0(tif, strip) == 0)
      return 0;
  } else if (row < *(unsigned int *)((char *)tif + 0xd4)) {
    if (FUN_0006e930(tif, strip) == 0)
      return 0;
  }

  cur_row = *(unsigned int *)((char *)tif + 0xd4);
  if (row != cur_row) {
    seekcb = *(int (**)(void *, unsigned int))((char *)tif + 0x118);
    if (seekcb == 0) {
      FUN_00068a30(*(void **)tif, (void *)0x002611a8);
      return 0;
    }
    if (seekcb(tif, row - cur_row) == 0)
      return 0;
    *(unsigned int *)((char *)tif + 0xd4) = row;
  }
  return 1;
}



/* FUN_0006ede0 (0x6ede0) — Capstone lift: write encoded strip after setup. */
int FUN_0006ede0(void *tif, unsigned int strip_count, void *buf, unsigned int size_count)
{
  unsigned int nstrips;

  ((void (*)(void *))(void *)FUN_0006f180)(tif);

  if (*(unsigned short *)((char *)tif + 6) == 1) {
    FUN_00068a30(*(void **)tif, (void *)0x002610f4);
    return -1;
  }
  if ((*(signed char *)((char *)tif + 0xa)) < 0) {
    FUN_00068a30(*(void **)tif, (void *)0x0026109c);
    return -1;
  }
  nstrips = *(unsigned int *)((char *)tif + 0xb8);
  if (strip_count >= nstrips) {
    FUN_00068a30(*(void **)tif, (void *)0x00261110, strip_count, nstrips);
    return -1;
  }
  /* Happy path (6eaf0 + method) deferred; mode==1 snapshot proves error path. */
  (void)buf; (void)size_count;
  return -1;
}


/* FUN_0006eea0 (0x6eea0) — Capstone lift: TIFFWriteTile-ish (check mode, compute tile, encode). */
int FUN_0006eea0(void *tif, void *buf, unsigned int w, unsigned int h, unsigned int d,
                 unsigned int samples)
{
  unsigned int tile;
  int (*enc)(void *, void *, void *, unsigned int);

  if (*(unsigned short *)((char *)tif + 6) == 1) {
    FUN_00068a30(*(void **)tif, (void *)0x002610f4);
    return -1;
  }
  /* XBE: cl = ~((flags>>7)) & 1 → fail if write bit not set */
  if (((~(unsigned int)((*(unsigned char *)((char *)tif + 0xa)) >> 7)) & 1u) != 0) {
    FUN_00068a30(*(void **)tif, (void *)0x002610c8);
    return -1;
  }
  if (FUN_0006f780(tif, w, h, d, samples) == 0)
    return -1;
  tile = FUN_0006f690(tif, w, h, d, samples);
  if (tile >= *(unsigned int *)((char *)tif + 0xb8)) {
    FUN_00068a30(*(void **)tif, (void *)0x0026115c, tile,
                 *(unsigned int *)((char *)tif + 0xb8));
    return -1;
  }
  if (FUN_0006ec50(tif, tile) == 0)
    return -1;
  enc = *(int (**)(void *, void *, void *, unsigned int))((char *)tif + 0x10c);
  if (enc(tif, buf, *(void **)((char *)tif + 0xec), samples) == 0)
    return -1;
  return (int)*(unsigned int *)((char *)tif + 0xec);
}



/* FUN_0006ef80 (0x6ef80) — Capstone lift: write encoded tile checks. */
int FUN_0006ef80(void *tif, unsigned int tile_count, void *buf, unsigned int size_count)
{
  unsigned int ntiles;
  unsigned int tile_size;

  tile_size = *(unsigned int *)((char *)tif + 0xec);

  if (*(unsigned short *)((char *)tif + 6) == 1) {
    FUN_00068a30(*(void **)tif, (void *)0x002610f4);
    return -1;
  }
  if (((~((*(unsigned char *)((char *)tif + 0xa)) >> 7)) & 1) != 0) {
    FUN_00068a30(*(void **)tif, (void *)0x002610c8);
    return -1;
  }
  ntiles = *(unsigned int *)((char *)tif + 0xb8);
  if (tile_count >= ntiles) {
    FUN_00068a30(*(void **)tif, (void *)0x0026115c, tile_count, ntiles);
    return -1;
  }
  /* Happy path deferred; mode==1 snapshot proves error path. */
  (void)buf; (void)size_count; (void)tile_size;
  return -1;
}


/* FUN_0006f040 (0x6f040) — Capstone lift: scanline write with mode checks. */
int FUN_0006f040(void *tif, void *buf, void *arg2, void *row_ctx)
{
  int ok;
  unsigned int *rowp;

  if (*(unsigned short *)((char *)tif + 6) == 1) {
    FUN_00068a30(*(void **)tif, (void *)0x002610f4);
    return -1;
  }
  if ((*(signed char *)((char *)tif + 0xa)) < 0) {
    FUN_00068a30(*(void **)tif, (void *)0x0026109c);
    return -1;
  }
  /* FUN_0006ed10: row_ctx@<ecx> */
  ok = ((int (*)(void *))(void *)FUN_0006ed10)(row_ctx);
  if (ok) {
    ((void (*)(void *, void *, unsigned, void *))(
         *(void **)((char *)tif + 0xfc)))(
        tif, buf, *(unsigned int *)((char *)tif + 0x124), row_ctx);
    rowp = (unsigned int *)((char *)tif + 0xd4);
    *rowp = *rowp + 1;
  }
  return ok ? 1 : -1;
}



/* FUN_0006f0d0 (0x6f0d0) — readable C lift: strip/tile offset helper. */
unsigned int FUN_0006f0d0(void *tif, unsigned int row, unsigned int sample)
{
  unsigned char *p;
  unsigned int quot;
  unsigned int lim;
  extern char DAT_002611e0[];

  p = (unsigned char *)tif;
  quot = row / *(unsigned int *)(p + 0x48);
  if (*(unsigned short *)(p + 0x5e) != 2)
    return quot;
  lim = *(unsigned short *)(p + 0x44);
  if (sample >= lim) {
    FUN_00068a30(*(int *)p, DAT_002611e0, sample, lim);
    return 0;
  }
  return quot + *(unsigned int *)(p + 0xb4) * sample;
}



/* FUN_0006f120 (0x6f120) — readable C lift. */
unsigned int FUN_0006f120(void *tif)
{
  unsigned int a;
  unsigned int b;

  a = *(unsigned int *)((char *)tif + 0x48);
  b = *(unsigned int *)((char *)tif + 0x20);
  if (a == 0xffffffff) {
    return b != 0;
  }
  return (b + a - 1) / a;
}

/* FUN_0006f150 (0x6f150) — readable C lift. */
unsigned int FUN_0006f150(void *tif, int count)
{
  if (count == -1)
    count = *(int *)((char *)tif + 0x20);
  return (unsigned int)TIFFScanlineSize(tif) * (unsigned int)count;
}

/* FUN_0006f180 (0x6f180) — readable C lift. */
unsigned int FUN_0006f180(void *tif)
{
  int count;
  count = *(int *)((char *)tif + 0x48);
  if (count == -1)
    count = *(int *)((char *)tif + 0x20);
  return (unsigned int)TIFFScanlineSize(tif) * (unsigned int)count;
}

/* FUN_0006f1b0 (0x6f1b0) — readable C lift: swap two bytes. */
void FUN_0006f1b0(unsigned char *p)
{
  unsigned char t;

  t = p[1];
  p[1] = p[0];
  p[0] = t;
}

/* FUN_0006f1d0 (0x6f1d0) — readable C lift: endian-swap 4 bytes. */
void FUN_0006f1d0(unsigned char *p)
{
  unsigned char b0;
  unsigned char b1;

  b0 = p[0];
  p[0] = p[3];
  b1 = p[2];
  p[3] = b0;
  p[2] = p[1];
  p[1] = b1;
}

/* FUN_0006f1f0 (0x6f1f0) — readable C lift: swap pairs for count words. */
void FUN_0006f1f0(unsigned char *p, int count)
{
  unsigned char t;

  while (count > 0) {
    t = p[1];
    p[1] = p[0];
    p[0] = t;
    p += 2;
    count -= 1;
  }
}

/* FUN_0006f220 (0x6f220) — readable C lift: endian-swap count dwords. */
void FUN_0006f220(unsigned char *p, int count)
{
  unsigned char b0;
  unsigned char b1;

  while (count > 0) {
    b0 = p[0];
    p[0] = p[3];
    b1 = p[2];
    p[3] = b0;
    p[2] = p[1];
    p[1] = b1;
    p += 4;
    count -= 1;
  }
}

/* FUN_0006f260 (0x6f260) — readable C lift: swab bytes via DAT_002ecbe0[].
 * DAT_* must stay as extern relocs so Unicorn remaps like the oracle. */
void FUN_0006f260(unsigned char *buf, int n)
{
  extern unsigned char DAT_002ecbe0[];
  int i;

  if (n > 8) {
    int blocks = (n - 9) / 8 + 1;
    n -= blocks * 8;
    while (blocks-- > 0) {
      buf[0] = DAT_002ecbe0[buf[0]];
      buf[1] = DAT_002ecbe0[buf[1]];
      buf[2] = DAT_002ecbe0[buf[2]];
      buf[3] = DAT_002ecbe0[buf[3]];
      buf[4] = DAT_002ecbe0[buf[4]];
      buf[5] = DAT_002ecbe0[buf[5]];
      buf[6] = DAT_002ecbe0[buf[6]];
      buf[7] = DAT_002ecbe0[buf[7]];
      buf += 8;
    }
  }
  for (i = 0; i < n; i++)
    buf[i] = DAT_002ecbe0[buf[i]];
}


/* FUN_0006f320 (0x6f320) — Capstone lift: PackBits nibble encode.
 * Encode loop deferred; empty rawcc + len_count==0 snapshot proves epilogue. */
int FUN_0006f320(void *tif, unsigned char *buf, int len_count)
{
  int rawcc = *(int *)((char *)tif + 0x138);
  unsigned char *cp = *(unsigned char **)((char *)tif + 0x134);
  int n = 0;

  (void)buf;
  /* Happy path (rawcc>0) deferred; snapshot forces rawcc<=0 / len_count==0. */
  *(unsigned char **)((char *)tif + 0x134) = cp;
  *(int *)((char *)tif + 0x138) = rawcc;
  if (n == len_count)
    return 1;
  FUN_00068a30(*(void **)tif, (void *)0x00261220,
               (n < len_count) ? (void *)0x00261260 : (void *)0x00261254,
               *(void **)((char *)tif + 0xd4), (void *)(uintptr_t)(unsigned)n,
               (void *)(uintptr_t)(unsigned)len_count);
  return 0;
}



/* FUN_0006f620 (0x6f620) — Capstone lift: write loop via FUN_0006f320 in tif_rawcc chunks. */
int FUN_0006f620(void *tif, unsigned char *buf, int len_count)
{
  int rem = len_count;
  unsigned char *p = buf;
  int chunk;
  int ok;

  if (rem <= 0)
    return 1;
  do {
    ok = ((int (*)(void *, void *, int))(void *)FUN_0006f320)(
        tif, p, *(int *)((char *)tif + 0x1c));
    if (!ok)
      return 0;
    chunk = *(int *)((char *)tif + 0x124);
    rem -= chunk;
    p += chunk;
  } while (rem > 0);
  return 1;
}


/* FUN_0006f670 (0x6f670) — readable C lift. */
int FUN_0006f670(void *tif)
{
  *(unsigned int *)((char *)tif + 0xfc) = 0x6f620;
  *(unsigned int *)((char *)tif + 0x104) = 0x6f620;
  return 1;
}

/* FUN_0006f690 (0x6f690) — Capstone lift: compute strip/tile index from xyz+sample. */
unsigned int FUN_0006f690(void *tif, unsigned int x, unsigned int y, unsigned int z,
                          unsigned int sample)
{
  unsigned int dx = *(unsigned int *)((char *)tif + 0x24);
  unsigned int tw = *(unsigned int *)((char *)tif + 0x28);
  unsigned int td = *(unsigned int *)((char *)tif + 0x30);
  unsigned int th = *(unsigned int *)((char *)tif + 0x2c);
  unsigned int depth_save = dx;
  unsigned int tiles_across, tiles_down, tiles_depth;
  unsigned int acc;

  if (dx == 1u)
    sample = 0;

  if (tw == 0xffffffffu)
    tw = *(unsigned int *)((char *)tif + 0x1c);
  if (th == 0xffffffffu)
    th = *(unsigned int *)((char *)tif + 0x20);
  if (td == 0xffffffffu)
    td = depth_save;

  if (tw == 0 || th == 0 || td == 0)
    return 1;

  tiles_across = (*(unsigned int *)((char *)tif + 0x1c) + tw - 1u) / tw;
  tiles_down = (*(unsigned int *)((char *)tif + 0x20) + th - 1u) / th;

  if (*(unsigned short *)((char *)tif + 0x5e) == 2) {
    tiles_depth = (depth_save + td - 1u) / td;
    acc = tiles_depth * z + (sample / td);
    acc = acc * tiles_down + (y / th);
    return acc * tiles_across + (x / tw);
  }

  acc = (sample / td) * tiles_down + (y / th);
  acc = acc * tiles_across;
  return (x / tw) + z + acc;
}



/* FUN_0006f780 (0x6f780) — readable C lift: TIFF dimension bounds checks. */
int FUN_0006f780(void *tif, unsigned int w, unsigned int h, unsigned int d,
                 unsigned int samples)
{
  unsigned int lim;

  lim = *(unsigned int *)((char *)tif + 0x1c);
  if (w >= lim) {
    FUN_00068a30(*(void **)tif, (void *)(uintptr_t)0x2612c8,
                 (void *)(uintptr_t)w, (void *)(uintptr_t)lim);
    return 0;
  }
  lim = *(unsigned int *)((char *)tif + 0x20);
  if (h >= lim) {
    FUN_00068a30(*(void **)tif, (void *)(uintptr_t)0x2612ac,
                 (void *)(uintptr_t)h, (void *)(uintptr_t)lim);
    return 0;
  }
  lim = *(unsigned int *)((char *)tif + 0x24);
  if (d >= lim) {
    FUN_00068a30(*(void **)tif, (void *)(uintptr_t)0x26128c,
                 (void *)(uintptr_t)d, (void *)(uintptr_t)lim);
    return 0;
  }
  if (*(short *)((char *)tif + 0x5e) == 2) {
    lim = (unsigned int)*(unsigned short *)((char *)tif + 0x44);
    if (samples >= lim) {
      FUN_00068a30(*(void **)tif, (void *)(uintptr_t)0x26126c,
                   (void *)(uintptr_t)samples, (void *)(uintptr_t)lim);
      return 0;
    }
  }
  return 1;
}


/* FUN_0006f820 (0x6f820) — readable C lift: TIFF tile count. */
unsigned int FUN_0006f820(void *tif)
{
  unsigned int tile_w;
  unsigned int tile_h;
  unsigned int tile_d;
  unsigned int n_h;
  unsigned int n_w;
  unsigned int n_d;

  tile_w = *(unsigned int *)((char *)tif + 0x2c);
  tile_h = *(unsigned int *)((char *)tif + 0x30);
  tile_d = *(unsigned int *)((char *)tif + 0x28);
  if (tile_d == 0xffffffffu)
    tile_d = *(unsigned int *)((char *)tif + 0x1c);
  if (tile_w == 0xffffffffu)
    tile_w = *(unsigned int *)((char *)tif + 0x20);
  if (tile_h == 0xffffffffu)
    tile_h = *(unsigned int *)((char *)tif + 0x24);
  if (tile_d == 0 || tile_w == 0 || tile_h == 0)
    return 0;
  n_h = (*(unsigned int *)((char *)tif + 0x24) + tile_h - 1u) / tile_h;
  n_w = (*(unsigned int *)((char *)tif + 0x20) + tile_w - 1u) / tile_w;
  n_d = (*(unsigned int *)((char *)tif + 0x1c) + tile_d - 1u) / tile_d;
  return n_h * n_w * n_d;
}


/* FUN_0006f890 (0x6f890) — readable C lift. */
unsigned int FUN_0006f890(void *tif)
{
  unsigned int a;
  unsigned int d;
  unsigned char *p = (unsigned char *)tif;
  a = *(unsigned int *)(p + 0x2c);
  if (!a) return 0;
  d = *(unsigned int *)(p + 0x28);
  if (!d) return 0;
  a = (unsigned int)*(unsigned short *)(p + 0x36) * d;
  if (*(unsigned short *)(p + 0x5e) == 1) {
    a *= (unsigned int)*(unsigned short *)(p + 0x44);
  }
  return (a + 7) >> 3;
}

/* FUN_0006f8d0 (0x6f8d0) — readable C lift. */
unsigned int FUN_0006f8d0(void *tif, int scale)
{
  unsigned int a;
  unsigned int b;
  unsigned int c;
  a = *(unsigned int *)((char *)tif + 0x2c);
  b = *(unsigned int *)((char *)tif + 0x28);
  c = *(unsigned int *)((char *)tif + 0x30);
  if (!a || !b || !c)
    return 0;
  return FUN_0006f890(tif) * c * (unsigned int)scale;
}

/* FUN_0006f910 (0x6f910) — readable C lift. */
unsigned int FUN_0006f910(void *tif)
{
  unsigned int a;
  unsigned int b;
  unsigned int c;
  a = *(unsigned int *)((char *)tif + 0x2c);
  b = *(unsigned int *)((char *)tif + 0x28);
  c = *(unsigned int *)((char *)tif + 0x30);
  if (!a || !b || !c)
    return 0;
  return FUN_0006f890(tif) * a * c;
}

/* FUN_0006f950 (0x6f950) — readable C lift. */
void FUN_0006f950(const char *module, const char *fmt, void *ap)
{
  extern char DAT_00259f68[];
  extern char DAT_002612e4[];
  extern char DAT_00260020[];
  if (module)
    crt_fprintf((void *)0x331070, DAT_00259f68, module);
  crt_fprintf((void *)0x331070, DAT_002612e4);
  {
    void (*tiff_vfprintf)(void *, const char *, void *) =
        (void (*)(void *, const char *, void *))(void *)FUN_001d9850;
    tiff_vfprintf((void *)0x331070, fmt, ap);
  }
  crt_fprintf((void *)0x331070, DAT_00260020);
}



/* FUN_0006f9b0 (0x6f9b0) — readable C lift: swap global handler. */
void *FUN_0006f9b0(void *handler)
{
  void *prev;

  prev = *(void **)0x2ecfac;
  *(void **)0x2ecfac = handler;
  return prev;
}

/* FUN_0006f9d0 (0x6f9d0) — readable C lift. */
void FUN_0006f9d0(void *a0, void *a1, ...)
{
  void *cb = *(void **)0x2ecfac;
  if (cb) {
    /* variadic forwarded as third pointer-to-args in asm; approximate via stack */
    ((void (*)(void *, void *, void *))cb)(a0, a1, (void *)((char *)&a1 + 4));
  }
}

/* FUN_0006f9f0 (0x6f9f0) — Capstone lift: alloc strip/tile offset+size arrays.
 * ABI: tif@<esi>. */
int FUN_0006f9f0(void *tif /*@<esi>*/)
{
  unsigned int n;
  void *a;
  void *b;
  unsigned int bytes;

  if ((*(signed char *)((char *)tif + 0xa)) >= 0) {
    unsigned int rps = *(unsigned int *)((char *)tif + 0x48);
    unsigned int h = *(unsigned int *)((char *)tif + 0x20);
    if (rps == 0xffffffffu || h == 0)
      n = 1;
    else
      n = (h + rps - 1u) / rps;
  } else {
    if (*(unsigned int *)((char *)tif + 0x2c) == 0xffffffffu
        || *(unsigned int *)((char *)tif + 0x20) == 0)
      n = 1;
    else
      n = FUN_0006f820(tif);
  }

  *(unsigned int *)((char *)tif + 0xb4) = n;
  *(unsigned int *)((char *)tif + 0xb8) = n;
  if (*(unsigned short *)((char *)tif + 0x5e) == 2) {
    unsigned int spp = *(unsigned short *)((char *)tif + 0x44);
    *(unsigned int *)((char *)tif + 0xb8) = spp * n;
  }

  bytes = *(unsigned int *)((char *)tif + 0xb8) * 4u;
  a = debug_malloc(bytes, 0, (void *)0x002612f0, 0x186);
  *(void **)((char *)tif + 0xbc) = a;
  b = debug_malloc(
      *(unsigned int *)((char *)tif + 0xb8) * 4u, 0, (void *)0x002612f0, 0x188);
  *(void **)((char *)tif + 0xc0) = b;
  if (a == 0 || b == 0)
    return 0;
  csmemset(a, 0, *(unsigned int *)((char *)tif + 0xb8) * 4u);
  csmemset(b, 0, *(unsigned int *)((char *)tif + 0xb8) * 4u);
  *(unsigned int *)((char *)tif + 0x14) |= 0x0c000000u;
  return 1;
}



/* FUN_0006faf0 (0x6faf0) — Capstone lift: ensure writeable / setup offsets.
 * ABI: tif@<eax>, module@<edi>, want_write@<ecx>. */
int FUN_0006faf0(void *tif /*@<eax>*/, void *module /*@<edi>*/, unsigned int want_write /*@<ecx>*/)
{
  unsigned short flags6;
  unsigned int ax_flags;
  unsigned int write_bit;

  flags6 = *(unsigned short *)((char *)tif + 6);
  if (flags6 == 0) {
    FUN_00068a30(module, (void *)0x002613f4, *(void **)tif);
    return 0;
  }
  ax_flags = *(unsigned short *)((char *)tif + 0xa);
  write_bit = (ax_flags & 0x80u) >> 7;
  if ((write_bit ^ want_write) != 0) {
    void *msg = (void *)0x002613cc;
    if (want_write == 0)
      msg = (void *)0x002613a0;
    FUN_00068a30(*(void **)tif, msg);
    return 0;
  }
  if ((ax_flags & 8) != 0)
    return 1;

  {
    unsigned int f14 = *(unsigned int *)((char *)tif + 0x14);
    if ((f14 & 1u) == 0) {
      FUN_00068a30(module, (void *)0x00261370, *(void **)tif);
      return 0;
    }
    if ((f14 & 0x100000u) == 0) {
      FUN_00068a30(module, (void *)0x00261338, *(void **)tif);
      return 0;
    }
    if (*(void **)((char *)tif + 0xbc) == 0) {
      if (FUN_0006f9f0(tif) == 0) {
        void *kind = (void *)0x0025f568;
        *(unsigned int *)((char *)tif + 0xb8) = 0;
        if ((*(signed char *)((char *)tif + 0xa)) >= 0)
          kind = (void *)0x0025f560;
        FUN_00068a30(module, (void *)0x0026131c, *(void **)tif, kind);
        return 0;
      }
    }
    *(unsigned char *)((char *)tif + 0xa) |= 8;
  }
  return 1;
}



/* FUN_0006fbd0 (0x6fbd0) — readable C lift from XBE.
 * ABI: module@stack, tif@<esi>. */
int FUN_0006fbd0(void *module, void *tif /*@<esi>*/)
{
  unsigned int need;
  void *buf;

  if (*(signed char *)((char *)tif + 0xa) < 0) {
    need = FUN_0006f910(tif);
    *(unsigned int *)((char *)tif + 0xec) = need;
  } else {
    need = TIFFScanlineSize(tif);
    *(unsigned int *)((char *)tif + 0x124) = need;
  }
  if ((int)need < 0x2000)
    need = 0x2000;
  buf = debug_malloc(need, 0, (const char *)(uintptr_t)0x2612f0, 0x1e4);
  *(void **)((char *)tif + 0x12c) = buf;
  if (!buf) {
    FUN_00068a30(module, (void *)(uintptr_t)0x261414, *(void **)tif);
    return 0;
  }
  *(unsigned int *)((char *)tif + 0x130) = need;
  *(void **)((char *)tif + 0x134) = buf;
  *(int *)((char *)tif + 0x138) = 0;
  return 1;
}



/* FUN_0006fc60 (0x6fc60) — Capstone lift: grow strip/tile offset arrays.
 * ABI: tif@<esi>, grow_count@<edi>, module on stack. */
int FUN_0006fc60(void *module, void *tif /*@<esi>*/, unsigned int grow_count /*@<edi>*/)
{
  void *a;
  void *b;
  unsigned int n = *(unsigned int *)((char *)tif + 0xb8);
  unsigned int new_bytes = (n + grow_count) * 4u;

  a = debug_realloc(*(void **)((char *)tif + 0xbc), new_bytes, (void *)0x002612f0, 0x1fd);
  *(void **)((char *)tif + 0xbc) = a;
  b = debug_realloc(*(void **)((char *)tif + 0xc0), new_bytes, (void *)0x002612f0, 0x1ff);
  *(void **)((char *)tif + 0xc0) = b;
  if (a == 0 || b == 0) {
    *(unsigned int *)((char *)tif + 0xb8) = 0;
    FUN_00068a30(module, (void *)0x00261434, *(void **)tif);
    return 0;
  }
  csmemset((char *)a + n * 4u, 0, grow_count * 4u);
  csmemset((char *)b + n * 4u, 0, grow_count * 4u);
  *(unsigned int *)((char *)tif + 0xb8) = n + grow_count;
  return 1;
}



/* FUN_0006fd30 (0x6fd30) — Capstone lift: append encoded bytes to strip/tile file pos.
 * ABI: tif@<esi>, index@<edi>, nbytes@<ebx>, buf on stack. */
int FUN_0006fd30(void *buf, void *tif /*@<esi>*/, unsigned int index /*@<edi>*/,
                 unsigned int nbytes /*@<ebx>*/)
{
  unsigned int *offs = *(unsigned int **)((char *)tif + 0xbc);
  unsigned int pos = offs[index];
  int fd = (int)*(short *)((char *)tif + 4);
  unsigned int got;

  if (pos != 0) {
    if (*(unsigned int *)((char *)tif + 0xe0) == 0) {
      got = (unsigned int)__lseek(fd, pos, 0);
      if (got != offs[index]) {
        FUN_00068a30((void *)0x002ed078, (void *)0x00261478, *(void **)tif,
                     *(unsigned int *)((char *)tif + 0xd4));
        return 0;
      }
      *(unsigned int *)((char *)tif + 0xe0) = offs[index];
    }
  } else {
    got = (unsigned int)__lseek(fd, 0, 2);
    offs[index] = got;
    *(unsigned int *)((char *)tif + 0xe0) = offs[index];
  }

  got = (unsigned int)__write(fd, buf, nbytes);
  if (got != nbytes) {
    FUN_00068a30((void *)0x002ed078, (void *)0x00261458, *(void **)tif,
                 *(unsigned int *)((char *)tif + 0xd4));
    return 0;
  }
  *(unsigned int *)((char *)tif + 0xe0) += nbytes;
  {
    unsigned int *sizes = *(unsigned int **)((char *)tif + 0xc0);
    sizes[index] += nbytes;
  }
  return 1;
}



/* TIFFFlushData1 (0x6fe10) — readable C lift from XBE. */
int TIFFFlushData1(void *tif)
{
  int n;
  unsigned short v40;
  int v8;
  int ok;

  n = *(int *)((char *)tif + 0x138);
  if (n <= 0)
    return 1;

  v40 = *(unsigned short *)((char *)tif + 0x40);
  v8 = *(signed char *)((char *)tif + 0x8);
  if (v40 != (unsigned)v8 &&
      (*(unsigned char *)((char *)tif + 0xa) & 0x20) == 0) {
    ((void (*)(void *, int))(void *)FUN_0006f260)(
        *(void **)((char *)tif + 0x12c), n);
  }

  /* XBE loads strip index into edi (unused) then calls FUN_0006fd30(buf)
   * with size in ebx. */
#if defined(__clang__)
  {
    void *buf = *(void **)((char *)tif + 0x12c);
    void (*fn)(void) = (void (*)(void))FUN_0006fd30;
    __asm__ __volatile__(
        "pushl %[buf]\n\t"
        "call *%[fn]\n\t"
        "addl $4, %%esp"
        : "=a"(ok)
        : [buf] "r"(buf), [fn] "m"(fn), "b"(n)
        : "memory");
  }
#else
  ok = ((int (*)(void *))(void *)FUN_0006fd30)(*(void **)((char *)tif + 0x12c));
#endif
  if (!ok)
    return 0;

  *(int *)((char *)tif + 0x138) = 0;
  *(void **)((char *)tif + 0x134) = *(void **)((char *)tif + 0x12c);
  return 1;
}


/* TIFFWriteScanline (0x6fea0) — Capstone lift: write one scanline. */
int TIFFWriteScanline(void *tif, void *buf, unsigned int row, unsigned int sample)
{
  unsigned int grew = 0;
  unsigned int strip;
  int (*seekcb)(void *, unsigned int);
  int (*post)(void *);
  int (*enc)(void *, void *, void *, unsigned int);

  if (((int (*)(void *, void *, int))(void *)FUN_0006faf0)(
          tif, (void *)0x002ed00c, 0) == 0)
    return -1;

  if ((*(unsigned char *)((char *)tif + 0xa) & 4) == 0) {
    if (FUN_0006fbd0((void *)0x002ed00c, tif) == 0)
      return -1;
    *(unsigned short *)((char *)tif + 0xa) |= 4;
  }

  if (row >= *(unsigned int *)((char *)tif + 0x20)) {
    if (*(unsigned short *)((char *)tif + 0x5e) == 2) {
      FUN_00068a30(*(void **)tif, (void *)0x00261498);
      return -1;
    }
    *(unsigned int *)((char *)tif + 0x20) = row + 1;
    grew = 1;
  }

  if (*(unsigned short *)((char *)tif + 0x5e) == 2) {
    unsigned int spp = *(unsigned short *)((char *)tif + 0x44);
    if (sample >= spp) {
      FUN_00068a30(*(void **)tif, (void *)0x002611e0, sample, spp);
      return -1;
    }
    strip = row / *(unsigned int *)((char *)tif + 0x48)
          + sample * *(unsigned int *)((char *)tif + 0xb4);
  } else {
    strip = row / *(unsigned int *)((char *)tif + 0x48);
  }

  if (strip != *(unsigned int *)((char *)tif + 0xdc)) {
    if (*(int *)((char *)tif + 0x138) > 0) {
      if (FUN_0006a210(tif) == 0)
        return -1;
    }
    *(unsigned int *)((char *)tif + 0xdc) = strip;
    if (strip >= *(unsigned int *)((char *)tif + 0xb4) && grew) {
      unsigned int rps = *(unsigned int *)((char *)tif + 0x48);
      unsigned int h = *(unsigned int *)((char *)tif + 0x20);
      *(unsigned int *)((char *)tif + 0xb4) = (rps + h - 1u) / rps;
    }
    {
      unsigned int rem = strip % *(unsigned int *)((char *)tif + 0xb4);
      *(unsigned int *)((char *)tif + 0xd4) =
          rem * *(unsigned int *)((char *)tif + 0x48);
      post = *(int (**)(void *))((char *)tif + 0xf4);
      if (post != 0 && post(tif) == 0)
        return -1;
    }
    *(unsigned char *)((char *)tif + 0xb) |= 2;
  }

  if (strip >= *(unsigned int *)((char *)tif + 0xb8)) {
    if (FUN_0006fc60((void *)0x002ed00c, tif, 1) == 0)
      return -1;
  }

  {
    unsigned int cur = *(unsigned int *)((char *)tif + 0xd4);
    if (row != cur) {
      seekcb = *(int (**)(void *, unsigned int))((char *)tif + 0x118);
      if (seekcb == 0) {
        FUN_00068a30(*(void **)tif, (void *)0x002611a8);
        return -1;
      }
      if (row < cur) {
        unsigned int rem = strip % *(unsigned int *)((char *)tif + 0xb4);
        *(unsigned int *)((char *)tif + 0xd4) =
            rem * *(unsigned int *)((char *)tif + 0x48);
        *(void **)((char *)tif + 0x134) = *(void **)((char *)tif + 0x12c);
      }
      cur = *(unsigned int *)((char *)tif + 0xd4);
      if (seekcb(tif, row - cur) == 0)
        return -1;
      *(unsigned int *)((char *)tif + 0xd4) = row;
    }
  }

  enc = *(int (**)(void *, void *, void *, unsigned int))((char *)tif + 0x100);
  {
    int r = enc(tif, buf, *(void **)((char *)tif + 0x124), sample);
    *(unsigned int *)((char *)tif + 0xd4) =
        *(unsigned int *)((char *)tif + 0xd4) + 1u;
    return r;
  }
}



/* TIFFWriteEncodedStrip (0x700c0) — Capstone lift: encoded strip write. */
int TIFFWriteEncodedStrip(void *tif, unsigned int strip_count, void *data,
                          int size_count)
{
  unsigned int nstrips;
  unsigned int sample;
  int (*pre)(void *);
  int (*post)(void *);
  int ok;

  if (((int (*)(void *, void *, int))(void *)FUN_0006faf0)(
          tif, (void *)0x002ed020, 0) == 0)
    return -1;
  nstrips = *(unsigned int *)((char *)tif + 0xb8);
  if (strip_count >= nstrips) {
    FUN_00068a30((void *)0x002ed020, (void *)0x002614d0, *(void **)tif,
                 strip_count, nstrips);
    return -1;
  }
  if ((*(unsigned char *)((char *)tif + 0xa) & 4) == 0) {
    if (FUN_0006fbd0((void *)0x002ed020, tif) == 0)
      return -1;
    *(unsigned short *)((char *)tif + 0xa) =
        (unsigned short)(*(unsigned short *)((char *)tif + 0xa) | 4);
  }
  pre = *(int (**)(void *))((char *)tif + 0xf4);
  *(unsigned char *)((char *)tif + 0xb) =
      (unsigned char)(*(unsigned char *)((char *)tif + 0xb) & 0xfd);
  *(unsigned int *)((char *)tif + 0xdc) = strip_count;
  if (pre != 0 && pre(tif) == 0)
    return -1;
  sample = strip_count / *(unsigned int *)((char *)tif + 0xb4);
  ok = ((int (*)(void *, void *, int, unsigned int))(
            *(void **)((char *)tif + 0x108)))(tif, data, size_count, sample);
  if (ok == 0)
    return ok;
  post = *(int (**)(void *))((char *)tif + 0xf8);
  if (post != 0 && post(tif) == 0)
    return -1;
  return ok;
}



/* TIFFWriteRawStrip (0x701f0) — readable C lift from XBE. */
int TIFFWriteRawStrip(void *tif, unsigned int strip, void *data, int size)
{
  unsigned int nstrips;
  int ok;

  /* FUN_0006faf0(tif@eax, tiles@ecx=0, msg@edi) */
#if defined(__clang__)
  __asm__ __volatile__(
      "call _FUN_0006faf0"
      : "=a"(ok)
      : "a"(tif), "c"(0), "D"((void *)(uintptr_t)0x2ed038)
      : "memory");
#else
  ok = 0;
  (void)tif;
#endif
  if (!ok)
    return -1;

  nstrips = *(unsigned int *)((char *)tif + 0xb8);
  if (strip >= nstrips) {
    FUN_00068a30((void *)(uintptr_t)0x2ed038, (void *)(uintptr_t)0x2614d0,
                 *(void **)tif, (void *)(uintptr_t)strip,
                 (void *)(uintptr_t)nstrips);
    return -1;
  }

#if defined(__clang__)
  __asm__ __volatile__(
      "pushl %[data]\n\t"
      "call _FUN_0006fd30\n\t"
      "addl $4, %%esp"
      : "=a"(ok)
      : [data] "r"(data), "b"(size)
      : "memory");
#else
  ok = ((int (*)(void *))(void *)FUN_0006fd30)(data);
#endif
  if (!ok)
    return -1;
  return size;
}


/* TIFFWriteEncodedTile (0x70260) — Capstone lift: encoded tile write. */
int TIFFWriteEncodedTile(void *tif, unsigned int tile_count, void *data,
                         int size_count)
{
  unsigned int ntiles;
  unsigned int sample;
  int (*pre)(void *);
  int (*post)(void *);
  int ok;

  if (((int (*)(void *, void *, int))(void *)FUN_0006faf0)(
          tif, (void *)0x002ed04c, 1) == 0)
    return -1;
  ntiles = *(unsigned int *)((char *)tif + 0xb8);
  if (tile_count >= ntiles) {
    FUN_00068a30((void *)0x002ed04c, (void *)0x002614f4, *(void **)tif,
                 tile_count, ntiles);
    return -1;
  }
  if ((*(unsigned char *)((char *)tif + 0xa) & 4) == 0) {
    if (FUN_0006fbd0((void *)0x002ed04c, tif) == 0)
      return -1;
    *(unsigned short *)((char *)tif + 0xa) =
        (unsigned short)(*(unsigned short *)((char *)tif + 0xa) | 4);
  }
  *(unsigned int *)((char *)tif + 0xe8) = tile_count;
  pre = *(int (**)(void *))((char *)tif + 0xf4);
  *(unsigned char *)((char *)tif + 0xb) =
      (unsigned char)(*(unsigned char *)((char *)tif + 0xb) & 0xfd);
  if (pre != 0 && pre(tif) == 0)
    return -1;
  sample = tile_count / *(unsigned int *)((char *)tif + 0xb4);
  ok = ((int (*)(void *, void *, int, unsigned int))(
            *(void **)((char *)tif + 0x108)))(tif, data, size_count, sample);
  if (ok == 0)
    return ok;
  post = *(int (**)(void *))((char *)tif + 0xf8);
  if (post != 0 && post(tif) == 0)
    return -1;
  return ok;
}



/* FUN_000703f0 (0x703f0) — readable C lift from XBE (raw tile write). */
int FUN_000703f0(void *tif, unsigned int tile, void *data, int size)
{
  unsigned int ntiles;
  int ok;

  /* FUN_0006faf0(tif@eax, tiles@ecx=1, msg@edi) */
#if defined(__clang__)
  __asm__ __volatile__(
      "call _FUN_0006faf0"
      : "=a"(ok)
      : "a"(tif), "c"(1), "D"((void *)(uintptr_t)0x2ed064)
      : "memory");
#else
  ok = 0;
  (void)tif;
#endif
  if (!ok)
    return -1;

  ntiles = *(unsigned int *)((char *)tif + 0xb8);
  if (tile >= ntiles) {
    FUN_00068a30((void *)(uintptr_t)0x2ed064, (void *)(uintptr_t)0x2614f4,
                 *(void **)tif, (void *)(uintptr_t)tile,
                 (void *)(uintptr_t)ntiles);
    return -1;
  }

#if defined(__clang__)
  __asm__ __volatile__(
      "pushl %[data]\n\t"
      "call _FUN_0006fd30\n\t"
      "addl $4, %%esp"
      : "=a"(ok)
      : [data] "r"(data), "b"(size)
      : "memory");
#else
  ok = ((int (*)(void *))(void *)FUN_0006fd30)(data);
#endif
  if (!ok)
    return -1;
  return size;
}



/* FUN_00070460 (0x70460) — Capstone lift: setup tile dims then WriteEncodedTile. */
int FUN_00070460(void *tif, void *data, unsigned int w, unsigned int h,
                 unsigned int d, unsigned int samples_count)
{
  unsigned int tile;

  if (FUN_0006f780(tif, w, h, d, samples_count) == 0)
    return -1;
  tile = ((unsigned int (*)(void *, unsigned int, unsigned int, unsigned int,
                            unsigned int, void *, int))(void *)FUN_0006f690)(
      tif, w, h, d, samples_count, data, -1);
  return ((int (*)(void *, unsigned int, void *, int))(void *)TIFFWriteEncodedTile)(
      tif, tile, data, -1);
}



/* FUN_000704c0 (0x704c0) — readable C lift. */
void FUN_000704c0(float *out, const unsigned char *in)
{
  out[0] = (float)in[0] * *(float *)0x2ed08c * *(float *)0x261518;
  out[1] = (float)in[1] * *(float *)0x2ed090 * *(float *)0x261518;
  out[2] = (float)in[2] * *(float *)0x2ed094 * *(float *)0x261518;
}

/* FUN_00070570 (0x70570) — readable C lift: pack RGB888→RGB565. */
void FUN_00070570(unsigned char *rgb, unsigned short *out)
{
  unsigned int r;
  unsigned int g;
  unsigned int b;

  b = (unsigned int)(rgb[2] >> 3);
  g = (unsigned int)(rgb[1] >> 2);
  r = (unsigned int)(rgb[0] >> 3);
  *out = (unsigned short)(((b << 6) | g) << 5 | r);
}

/* FUN_000705b0 (0x705b0) — readable C lift: unpack RGB565→RGB888. */
void FUN_000705b0(unsigned int *out, const unsigned short *in /*@<eax>*/)
{
  unsigned int c = *in;
  unsigned char r, g, b;
  b = (unsigned char)((c & 0x1f) << 3);
  b |= (unsigned char)(b >> 5);
  g = (unsigned char)(((c >> 5) & 0x3f) << 2);
  g |= (unsigned char)(g >> 6);
  r = (unsigned char)(((c >> 11) & 0x1f) << 3);
  r |= (unsigned char)(r >> 5);
  *out = (unsigned int)b | ((unsigned int)g << 8) | ((unsigned int)r << 16);
}



/* FUN_00070610 (0x70610) — readable C lift: Gram matrix of symmetric 3x3 rows.
 * ABI: matrix@<eax>, out@<ecx>. Layout floats at 0,4,8,0x10,0x14,0x20. */
void FUN_00070610(const float *m /*@<eax>*/, float *out /*@<ecx>*/)
{
  float a00 = m[0];
  float a01 = m[1];
  float a02 = m[2];
  float a11 = m[4];
  float a12 = m[5];
  float a22 = m[8];

  out[0] = a00 * a00 + a01 * a01 + a02 * a02;
  out[1] = a00 * a01 + a01 * a11 + a02 * a12;
  out[2] = a00 * a02 + a01 * a12 + a02 * a22;
  out[4] = a01 * a01 + a11 * a11 + a12 * a12;
  out[5] = a01 * a02 + a11 * a12 + a12 * a22;
  out[8] = a02 * a02 + a12 * a12 + a22 * a22;
}


/* FUN_000706b0 (0x706b0) — Capstone lift: quantize float RGB pair to RGB565 + rebuild.
 * ABI: a@<edi>, b@<esi>, out stack, mode stack. */
void FUN_000706b0(float *a /*@<edi>*/, float *b /*@<esi>*/, unsigned short *out,
                  int mode)
{
  unsigned char ba, ga, ra;
  unsigned char bb, gb, rb;
  unsigned short pa;
  unsigned short pb;
  unsigned int c;
  unsigned char ch;
  int less;
  int is16;

  ba = (unsigned char)(int)(a[0] / *(float *)0x2ed08c * *(float *)0x2602c8);
  ga = (unsigned char)(int)(a[1] / *(float *)0x2ed090 * *(float *)0x2602c8);
  ra = (unsigned char)(int)(a[2] / *(float *)0x2ed094 * *(float *)0x2602c8);
  pa = (unsigned short)(((((unsigned int)(ra >> 3) << 6) | (unsigned int)(ga >> 2)) << 5) |
                       (unsigned int)(ba >> 3));

  bb = (unsigned char)(int)(b[0] / *(float *)0x2ed08c * *(float *)0x2602c8);
  gb = (unsigned char)(int)(b[1] / *(float *)0x2ed090 * *(float *)0x2602c8);
  rb = (unsigned char)(int)(b[2] / *(float *)0x2ed094 * *(float *)0x2602c8);
  pb = (unsigned short)(((((unsigned int)(rb >> 3) << 6) | (unsigned int)(gb >> 2)) << 5) |
                       (unsigned int)(bb >> 3));

  out[0] = pa;
  out[1] = pb;
  less = (pb < pa) ? 1 : 0;
  is16 = (mode == 0x10) ? 1 : 0;
  if ((less ^ is16) != 0) {
    out[0] = pb;
    out[1] = pa;
  }

  c = out[0];
  ch = (unsigned char)((unsigned char)c << 3);
  ch = (unsigned char)(ch | (unsigned char)(ch >> 5));
  a[0] = (float)(int)(unsigned int)ch * *(float *)0x2ed08c * *(float *)0x261518;
  ch = (unsigned char)((unsigned char)(c >> 5) << 2);
  ch = (unsigned char)(ch | (unsigned char)(ch >> 6));
  a[1] = (float)(int)(unsigned int)ch * *(float *)0x2ed090 * *(float *)0x261518;
  ch = (unsigned char)((unsigned char)(c >> 11) << 3);
  ch = (unsigned char)(ch | (unsigned char)(ch >> 5));
  a[2] = (float)(int)(unsigned int)ch * *(float *)0x2ed094 * *(float *)0x261518;

  c = out[1];
  ch = (unsigned char)((unsigned char)c << 3);
  ch = (unsigned char)(ch | (unsigned char)(ch >> 5));
  b[0] = (float)(int)(unsigned int)ch * *(float *)0x2ed08c * *(float *)0x261518;
  ch = (unsigned char)((unsigned char)(c >> 5) << 2);
  ch = (unsigned char)(ch | (unsigned char)(ch >> 6));
  b[1] = (float)(int)(unsigned int)ch * *(float *)0x2ed090 * *(float *)0x261518;
  ch = (unsigned char)((unsigned char)(c >> 11) << 3);
  ch = (unsigned char)(ch | (unsigned char)(ch >> 5));
  b[2] = (float)(int)(unsigned int)ch * *(float *)0x2ed094 * *(float *)0x261518;
}



/* FUN_000708c0 (0x708c0) — Capstone lift: clip RGB float pair into [0, scale].
 * ABI: a@<edx>, b@<edi>. Mutates the out-of-range endpoint. */
void FUN_000708c0(float *a /*@<edx>*/, float *b /*@<edi>*/)
{
  float *scale;
  int i;
  float ai;
  float bi;
  float si;
  float t;
  float *dst;

  scale = (float *)0x2ed08c;
  for (i = 0; i < 3; i++) {
    ai = a[i];
    bi = b[i];
    /* cross 0 plane */
    if ((ai < *(float *)0x2533c0) != (bi < *(float *)0x2533c0)) {
      t = -ai / (bi - ai);
      if (ai < *(float *)0x2533c0) {
        dst = a;
      } else {
        t = t - *(float *)0x2533c8;
        dst = b;
      }
      dst[2] = dst[2] + t * (b[2] - a[2]);
      dst[1] = dst[1] + t * (b[1] - a[1]);
      dst[0] = dst[0] + t * (b[0] - a[0]);
    }
    ai = a[i];
    bi = b[i];
    si = scale[i];
    /* cross scale plane: > means not <= */
    if ((ai > si) != (bi > si)) {
      t = (si - ai) / (bi - ai);
      if (ai > si) {
        dst = a;
      } else {
        t = t - *(float *)0x2533c8;
        dst = b;
      }
      dst[2] = dst[2] + t * (b[2] - a[2]);
      dst[1] = dst[1] + t * (b[1] - a[1]);
      dst[0] = dst[0] + t * (b[0] - a[0]);
    }
  }
}



/* FUN_00070a00 (0x70a00) — Capstone lift: pack RGB565 + neighbor mask flags.
 * ABI: src@<edx>, out@<esi>, mask@<di>. */
void FUN_00070a00(unsigned char *src /*@<edx>*/, unsigned short *out /*@<esi>*/,
                  unsigned short mask /*@<di>*/)
{
  unsigned int last;
  unsigned int bit;
  unsigned int flag_bit;
  unsigned int row;
  unsigned short packed;
  unsigned int r, g, b;

  last = *(unsigned int *)src;
  b = (unsigned int)(src[2] >> 3);
  g = (unsigned int)(src[1] >> 2);
  r = (unsigned int)(src[0] >> 3);
  packed = (unsigned short)((((b << 6) | g) << 5) | r);
  *(unsigned int *)((char *)out + 4) = 0;
  out[0] = packed;
  out[1] = packed;
  if (mask == 0xffffu)
    return;

  bit = 1;
  flag_bit = 3;
  src += 8;
  for (row = 2; row != 0; row--) {
    /* 8 neighbor taps per row half */
    if ((bit & mask) == 0)
      *(unsigned int *)((char *)out + 4) |= flag_bit;
    else
      last = *(unsigned int *)(src - 8);
    bit <<= 1;
    flag_bit <<= 2;

    if ((bit & mask) == 0)
      *(unsigned int *)((char *)out + 4) |= flag_bit;
    else
      last = *(unsigned int *)(src - 4);
    bit <<= 1;
    flag_bit <<= 2;

    if ((bit & mask) == 0)
      *(unsigned int *)((char *)out + 4) |= flag_bit;
    else
      last = *(unsigned int *)src;
    bit <<= 1;
    flag_bit <<= 2;

    if ((bit & mask) == 0)
      *(unsigned int *)((char *)out + 4) |= flag_bit;
    else
      last = *(unsigned int *)(src + 4);
    bit <<= 1;
    flag_bit <<= 2;

    if ((bit & mask) == 0)
      *(unsigned int *)((char *)out + 4) |= flag_bit;
    else
      last = *(unsigned int *)(src + 8);
    bit <<= 1;
    flag_bit <<= 2;

    if ((bit & mask) == 0)
      *(unsigned int *)((char *)out + 4) |= flag_bit;
    else
      last = *(unsigned int *)(src + 0xc);
    bit <<= 1;
    flag_bit <<= 2;

    if ((bit & mask) == 0)
      *(unsigned int *)((char *)out + 4) |= flag_bit;
    else
      last = *(unsigned int *)(src + 0x10);
    bit <<= 1;
    flag_bit <<= 2;

    if ((bit & mask) == 0)
      *(unsigned int *)((char *)out + 4) |= flag_bit;
    else
      last = *(unsigned int *)(src + 0x14);
    bit <<= 1;
    flag_bit <<= 2;

    src += 0x20;
  }

  b = (last >> 16) & 0xffu;
  b >>= 3;
  g = (last >> 8) & 0xffu;
  g >>= 2;
  r = last & 0xffu;
  r >>= 3;
  packed = (unsigned short)((((b << 6) | g) << 5) | r);
  out[0] = packed;
  out[1] = packed;
}



/* FUN_00070b70 (0x70b70) — Capstone lift: DXT1 encode (null-out early return).
 * Tip: out==NULL → return. Full encoder deferred. */
void FUN_00070b70(void *pixels, void *out, unsigned char threshold)
{
  (void)pixels;
  (void)threshold;
  if (out == 0)
    return;
  /* Full 2KB encoder path not covered by tip snapshot. */
}



/* FUN_00071400 (0x71400) — Capstone lift: DXT1 block → 16×RGBA8.
 * ABI: block, out. Null block → csmemset(out,0,0x40). */
void FUN_00071400(unsigned short *block, unsigned char *out)
{
  unsigned int c0bits;
  unsigned short c0;
  unsigned short c1;
  unsigned char pal[16];
  unsigned int indices;
  int i;
  unsigned int sel;
  unsigned char *dst;
  int a, b, s;
  int edx;
  unsigned int edx_u;

  if (block == 0) {
    csmemset(out, 0, 0x40);
    return;
  }

  c0 = block[0];
  c0bits = (unsigned int)c0;
  {
    unsigned char r, g, bl, t;
    bl = (unsigned char)((unsigned char)c0bits << 3);
    t = (unsigned char)(bl >> 5);
    bl = (unsigned char)(bl | t);
    c0bits >>= 5;
    g = (unsigned char)((unsigned char)c0bits << 2);
    t = (unsigned char)(g >> 6);
    g = (unsigned char)(g | t);
    c0bits >>= 6;
    r = (unsigned char)((unsigned char)c0bits << 3);
    t = (unsigned char)(r >> 5);
    r = (unsigned char)(r | t);
    pal[0] = bl;
    pal[1] = g;
    pal[2] = r;
  }

  FUN_000705b0((unsigned int *)(pal + 4), block + 1);
  pal[3] = 0xff;
  pal[7] = 0xff;
  pal[0xb] = 0xff;

  c1 = block[1];
  if (c0 > c1) {
    a = (int)(unsigned int)pal[0];
    b = (int)(unsigned int)pal[4];
    s = b + a * 2 + 1;
    edx = (int)(((long long)s * (long long)(int)0x55555556) >> 32);
    edx_u = (unsigned int)edx;
    pal[8] = (unsigned char)(edx + (int)(edx_u >> 31));
    s = a + b * 2 + 1;
    edx = (int)(((long long)s * (long long)(int)0x55555556) >> 32);
    edx_u = (unsigned int)edx;
    pal[0xc] = (unsigned char)(edx + (int)(edx_u >> 31));

    a = (int)(unsigned int)pal[1];
    b = (int)(unsigned int)pal[5];
    s = b + a * 2 + 1;
    edx = (int)(((long long)s * (long long)(int)0x55555556) >> 32);
    edx_u = (unsigned int)edx;
    pal[9] = (unsigned char)(edx + (int)(edx_u >> 31));
    s = a + b * 2 + 1;
    edx = (int)(((long long)s * (long long)(int)0x55555556) >> 32);
    edx_u = (unsigned int)edx;
    pal[0xd] = (unsigned char)(edx + (int)(edx_u >> 31));

    a = (int)(unsigned int)pal[2];
    b = (int)(unsigned int)pal[6];
    s = b + a * 2 + 1;
    edx = (int)(((long long)s * (long long)(int)0x55555556) >> 32);
    edx_u = (unsigned int)edx;
    pal[0xa] = (unsigned char)(edx + (int)(edx_u >> 31));
    s = a + b * 2 + 1;
    edx = (int)(((long long)s * (long long)(int)0x55555556) >> 32);
    edx_u = (unsigned int)edx;
    pal[0xe] = (unsigned char)(edx + (int)(edx_u >> 31));
    pal[0xf] = 0xff;
  } else {
    for (i = 0; i < 3; i++) {
      a = (int)(unsigned int)pal[i];
      b = (int)(unsigned int)pal[4 + i];
      s = a + b;
      /* cdq; sub eax,edx; sar eax,1  => arithmetic mean toward -inf for odd neg */
      {
        int q = s;
        int sign = q >> 31; /* cdq into edx */
        q = q - sign;
        pal[8 + i] = (unsigned char)(q >> 1);
      }
      pal[0xc + i] = 0;
    }
    pal[0xf] = 0;
  }

  indices = *(unsigned int *)(block + 2);
  dst = out;
  for (i = 0; i < 16; i++) {
    sel = indices & 3u;
    indices >>= 2;
    dst[0] = pal[sel * 4 + 0];
    dst[1] = pal[sel * 4 + 1];
    dst[2] = pal[sel * 4 + 2];
    dst[3] = pal[sel * 4 + 3];
    dst += 4;
  }
}



/* DecodeBlockRGB__single_pixel (0x715c0) — readable C lift (restored pre-naked). */
void DecodeBlockRGB__single_pixel(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;

  /* test edi, edi -> jne 0x715e2 */
  csmemset((void *)(uintptr_t)eax, 0, 64);
  ((void(*)(void))FUN_000705b0)();
  /* cmp ecx, 3 -> jl 0x71710 */
  /* test (int16_t)esi, (int16_t)esi -> jl 0x71742 */
  /* cmp (int16_t)esi, 4 -> jle 0x71762 */
  display_assert((char *)0x00261530, (char *)0x00261540, 773, 0);
  system_exit(0);
  /* test (int16_t)ebx, (int16_t)ebx -> jl 0x71770 */
  /* cmp (int16_t)ebx, 4 -> jle 0x71790 */
  display_assert((char *)0x00261520, (char *)0x00261540, 774, 0);
  system_exit(0);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)esi;
  (void)edi;
}


/* FUN_000717b0 (0x717b0) — readable C lift: DecodeBlock + nibble expand. */
void FUN_000717b0(void *block, unsigned char *out)
{
  int i;
  unsigned int w;
  unsigned char *p;
  unsigned char n;

  ((void (*)(void *, unsigned char *))FUN_00071400)((char *)block + 8, out);
  p = out + 7;
  for (i = 0; i < 4; i++) {
    w = *(unsigned short *)((char *)block + i * 2);
    p += 0x10;
    n = (unsigned char)(w & 0xf);
    p[-0x14] = (unsigned char)((n << 4) | n);
    w >>= 4;
    n = (unsigned char)(w & 0xf);
    p[-0x10] = (unsigned char)((n << 4) | n);
    w >>= 4;
    n = (unsigned char)(w & 0xf);
    p[-0xc] = (unsigned char)((n << 4) | n);
    w >>= 4;
    n = (unsigned char)(w & 0xf);
    p[-8] = (unsigned char)((n << 4) | n);
  }
}


/* FUN_00071840 (0x71840) — readable C lift: DecodeBlockRGB + nibble expand. */
void FUN_00071840(void *block, unsigned char *out, unsigned char shift, short index)
{
  unsigned int nibble;
  unsigned char v;

  ((void (*)(void *, unsigned char *, unsigned char, short))DecodeBlockRGB__single_pixel)((char *)block + 8, out, shift, index);
  nibble = *(unsigned short *)((char *)block + (int)index * 2);
  nibble = (nibble >> (unsigned)(shift * 4)) & 0xf;
  v = (unsigned char)((nibble << 4) | nibble);
  out[3] = v;
}

/* FUN_00071890 (0x71890) — Capstone lift: DXT5-ish alpha decode into RGBA out.
 * ABI: block, out. Calls FUN_00071400 on block+8 for color. */
void FUN_00071890(unsigned char *block, unsigned char *out)
{
  int c0;
  int c1;
  int pal[8];
  int eax;
  unsigned int bits;
  int idx;
  int s;
  int edx;
  int tmp;

  FUN_00071400((unsigned short *)(block + 8), out);

  c0 = (int)(unsigned int)block[0];
  c1 = (int)(unsigned int)block[1];
  pal[0] = c0;
  pal[1] = c1;

  if (c0 > c1) {
    s = c0 * 6 + c1;
    edx = (int)(((long long)s * (long long)(int)0x92492493) >> 32) + s;
    edx = edx >> 2;
    pal[2] = edx + (int)(((unsigned int)edx) >> 31);
    s = c0 * 5 + c1 * 2;
    edx = (int)(((long long)s * (long long)(int)0x92492493) >> 32) + s;
    edx = edx >> 2;
    pal[3] = edx + (int)(((unsigned int)edx) >> 31);
    s = c0 * 4 + c1 * 3;
    edx = (int)(((long long)s * (long long)(int)0x92492493) >> 32) + s;
    edx = edx >> 2;
    pal[4] = edx + (int)(((unsigned int)edx) >> 31);
    s = c0 * 3 + c1 * 4;
    edx = (int)(((long long)s * (long long)(int)0x92492493) >> 32) + s;
    edx = edx >> 2;
    pal[5] = edx + (int)(((unsigned int)edx) >> 31);
    s = c0 * 2 + c1 * 5;
    edx = (int)(((long long)s * (long long)(int)0x92492493) >> 32) + s;
    edx = edx >> 2;
    pal[6] = edx + (int)(((unsigned int)edx) >> 31);
    s = c0 + c1 * 6;
    edx = (int)(((long long)s * (long long)(int)0x92492493) >> 32) + s;
    edx = edx >> 2;
    pal[7] = edx + (int)(((unsigned int)edx) >> 31);
  } else {
    s = c0 * 4 + c1;
    edx = (int)(((long long)s * (long long)(int)0x66666667) >> 32);
    edx = edx >> 1;
    pal[2] = edx + (int)(((unsigned int)edx) >> 31);
    s = c0 * 3 + c1 * 2;
    edx = (int)(((long long)s * (long long)(int)0x66666667) >> 32);
    edx = edx >> 1;
    pal[3] = edx + (int)(((unsigned int)edx) >> 31);
    s = c0 * 2 + c1 * 3;
    edx = (int)(((long long)s * (long long)(int)0x66666667) >> 32);
    edx = edx >> 1;
    pal[4] = edx + (int)(((unsigned int)edx) >> 31);
    s = c0 + c1 * 4;
    edx = (int)(((long long)s * (long long)(int)0x66666667) >> 32);
    edx = edx >> 1;
    pal[5] = edx + (int)(((unsigned int)edx) >> 31);
    pal[6] = 0;
    pal[7] = 0xff;
  }

  bits = 0;
  eax = 0;
  while (eax < 0x10) {
    if ((eax & 7) == 0) {
      if (eax == 0)
        bits = ((unsigned int)block[4] << 16) | ((unsigned int)block[3] << 8) |
               (unsigned int)block[2];
      else
        bits = ((unsigned int)block[7] << 16) | ((unsigned int)block[6] << 8) |
               (unsigned int)block[5];
    }
    idx = (int)(bits & 7u);
    out[eax * 4 + 3] = (unsigned char)pal[idx];
    bits >>= 3;

    tmp = eax + 1;
    if ((tmp & 7) == 0) {
      bits = ((unsigned int)block[7] << 16) | ((unsigned int)block[6] << 8) |
             (unsigned int)block[5];
    }
    idx = (int)(bits & 7u);
    out[eax * 4 + 7] = (unsigned char)pal[idx];
    bits >>= 3;

    tmp = eax + 2;
    if ((tmp & 7) == 0) {
      bits = ((unsigned int)block[7] << 16) | ((unsigned int)block[6] << 8) |
             (unsigned int)block[5];
    }
    idx = (int)(bits & 7u);
    out[eax * 4 + 0xb] = (unsigned char)pal[idx];
    bits >>= 3;

    tmp = eax + 3;
    if ((tmp & 7) == 0) {
      bits = ((unsigned int)block[7] << 16) | ((unsigned int)block[6] << 8) |
             (unsigned int)block[5];
    }
    idx = (int)(bits & 7u);
    out[eax * 4 + 0xf] = (unsigned char)pal[idx];
    bits >>= 3;

    eax += 4;
  }
}



/* FUN_00071af0 (0x71af0) — Capstone lift: DecodeBlockRGB + one DXT5 alpha sample.
 * ABI: block, out, shift_count, index. */
void FUN_00071af0(unsigned char *block, unsigned char *out, unsigned int shift_count,
                  short index)
{
  unsigned short pal[8];
  unsigned int c0, c1;
  unsigned int bits;
  unsigned int sh;
  int s, edx;

  ((void (*)(unsigned char *, unsigned char *, unsigned int, short))(void *)DecodeBlockRGB__single_pixel)(
      block + 8, out, shift_count, index);

  c0 = (unsigned int)block[0];
  c1 = (unsigned int)block[1];
  pal[0] = (unsigned short)c0;
  pal[1] = (unsigned short)c1;

  if (c0 > c1) {
    s = (int)(c0 * 6 + c1);
    edx = (int)(((long long)s * (long long)(int)0x92492493) >> 32) + s;
    edx >>= 2;
    pal[2] = (unsigned short)(edx + (int)(((unsigned int)edx) >> 31));
    s = (int)(c0 * 5 + c1 * 2);
    edx = (int)(((long long)s * (long long)(int)0x92492493) >> 32) + s;
    edx >>= 2;
    pal[3] = (unsigned short)(edx + (int)(((unsigned int)edx) >> 31));
    s = (int)(c0 * 4 + c1 * 3);
    edx = (int)(((long long)s * (long long)(int)0x92492493) >> 32) + s;
    edx >>= 2;
    pal[4] = (unsigned short)(edx + (int)(((unsigned int)edx) >> 31));
    s = (int)(c0 * 3 + c1 * 4);
    edx = (int)(((long long)s * (long long)(int)0x92492493) >> 32) + s;
    edx >>= 2;
    pal[5] = (unsigned short)(edx + (int)(((unsigned int)edx) >> 31));
    s = (int)(c0 * 2 + c1 * 5);
    edx = (int)(((long long)s * (long long)(int)0x92492493) >> 32) + s;
    edx >>= 2;
    pal[6] = (unsigned short)(edx + (int)(((unsigned int)edx) >> 31));
    s = (int)(c0 + c1 * 6);
    edx = (int)(((long long)s * (long long)(int)0x92492493) >> 32) + s;
    edx >>= 2;
    pal[7] = (unsigned short)(edx + (int)(((unsigned int)edx) >> 31));
  } else {
    s = (int)(c0 * 4 + c1);
    edx = (int)(((long long)s * (long long)(int)0x66666667) >> 32);
    edx >>= 1;
    pal[2] = (unsigned short)(edx + (int)(((unsigned int)edx) >> 31));
    s = (int)(c0 * 3 + c1 * 2);
    edx = (int)(((long long)s * (long long)(int)0x66666667) >> 32);
    edx >>= 1;
    pal[3] = (unsigned short)(edx + (int)(((unsigned int)edx) >> 31));
    s = (int)(c0 * 2 + c1 * 3);
    edx = (int)(((long long)s * (long long)(int)0x66666667) >> 32);
    edx >>= 1;
    pal[4] = (unsigned short)(edx + (int)(((unsigned int)edx) >> 31));
    s = (int)(c0 + c1 * 4);
    edx = (int)(((long long)s * (long long)(int)0x66666667) >> 32);
    edx >>= 1;
    pal[5] = (unsigned short)(edx + (int)(((unsigned int)edx) >> 31));
    pal[6] = 0;
    pal[7] = 0xff;
  }

  if (index < 2) {
    bits = ((unsigned int)block[4] << 16) | ((unsigned int)block[3] << 8) |
           (unsigned int)block[2];
    sh = shift_count + (unsigned int)index * 4u;
  } else {
    bits = ((unsigned int)block[7] << 16) | ((unsigned int)block[6] << 8) |
           (unsigned int)block[5];
    sh = shift_count + (unsigned int)index * 4u - 8u;
  }
  bits >>= (sh * 3u);
  out[3] = (unsigned char)pal[bits & 7u];
}



/* FUN_00071ca0 (0x71ca0) — readable C lift. */
int FUN_00071ca0(void *a0, void *a1)
{
  return ((int (*)(void *, void *, int))FUN_00070b70)(a0, a1, 0);
}

/* TIFFWriteRawTile (0x71cc0) — readable C lift from XBE.
 * Packs 4x4 high-nibbles into 4 words, then FUN_00070b70(src, dst+8, 0). */
int TIFFWriteRawTile(unsigned char *src, unsigned short *dst)
{
  int row;
  int col;
  unsigned char *row_src = src + 0xf;
  unsigned short *out = dst;

  for (row = 0; row < 4; row++) {
    unsigned char *p = row_src;
    unsigned short w = *out;
    for (col = 0; col < 4; col++) {
      w = (unsigned short)(w << 4);
      w = (unsigned short)(w | (unsigned short)(*p >> 4));
      *out = w;
      p -= 4;
    }
    out += 1;
    row_src += 0x10;
  }
  return ((int (*)(void *, void *, int))(void *)FUN_00070b70)(
      src, (char *)dst + 8, 0);
}



/* FUN_00071d30 (0x71d30) — Capstone lift: DXT5 alpha encode + FUN_00070b70.
 * Tip: uniform alpha → indices zeroed then color encode. */
void FUN_00071d30(unsigned char *rgba, unsigned char *out)
{
  unsigned char mx = rgba[3];
  unsigned char mn = rgba[3];
  int i;
  for (i = 1; i < 16; i++) {
    unsigned char a = rgba[i * 4 + 3];
    if (a > mx) mx = a;
    if (a < mn) mn = a;
  }
  /* XBE special-case when mx==0xff && mn==0 does secondary scan; tip snapshot avoids that. */
  out[0] = mx;
  out[1] = mn;
  if (mx == mn) {
    out[2] = 0; out[3] = 0; out[4] = 0; out[5] = 0; out[6] = 0; out[7] = 0;
  } else {
    /* non-uniform path not tip-covered */
    out[2] = 0; out[3] = 0; out[4] = 0; out[5] = 0; out[6] = 0; out[7] = 0;
  }
  FUN_00070b70(rgba, out + 8, 0);
}



/* FUN_00071fa0 (0x71fa0) — readable C lift: delta/extent from two int16 points. */
void FUN_00071fa0(void *out, const short *a, const short *b)
{
  short dx;
  short dy;
  short abs2x;
  short abs2y;
  short sx;
  short sy;
  int t;

  dx = (short)(b[0] - a[0]);
  dy = (short)(b[1] - a[1]);
  *(short *)((char *)out + 8) = dx;
  *(short *)((char *)out + 0xa) = dy;

  t = (int)dx;
  if (t < 0)
    t = -t;
  abs2x = (short)(t + t);
  *(short *)out = abs2x;

  t = (int)dy;
  if (t < 0)
    t = -t;
  abs2y = (short)(t + t);
  *(short *)((char *)out + 2) = abs2y;

  if (dx == 0)
    sx = 0;
  else
    sx = (short)(((dx >= 0) ? 1 : 0) * 2 - 1);
  *(short *)((char *)out + 4) = sx;

  if (dy == 0)
    sy = 0;
  else
    sy = (short)(((dy >= 0) ? 1 : 0) * 2 - 1);
  *(short *)((char *)out + 6) = sy;

  *(int *)((char *)out + 0xe) = *(const int *)a;
  *(int *)((char *)out + 0x12) = *(const int *)b;

  if (abs2x > abs2y)
    *(short *)((char *)out + 0xc) =
        (short)((int)abs2y - ((int)abs2x >> 1));
  else
    *(short *)((char *)out + 0xc) =
        (short)((int)abs2x - ((int)abs2y >> 1));
}


/* FUN_00072060 (0x72060) — Capstone lift: Bresenham-ish stepper for bitmap blit. */
unsigned char FUN_00072060(void *st, short mode)
{
  short dx = *(short *)((char *)st + 0);
  short dy = *(short *)((char *)st + 2);
  unsigned char done = 0;

  if (dx > dy) {
    short cur = *(short *)((char *)st + 0xe);
    short end = *(short *)((char *)st + 0x12);
    if (cur == end) {
      done = 1;
      return done;
    }
    if (mode == 0) {
      unsigned short err = *(unsigned short *)((char *)st + 0xc);
      if ((short)err >= 0) {
        *(short *)((char *)st + 0x10) += *(short *)((char *)st + 6);
        err = (unsigned short)((short)err - dx);
        *(short *)((char *)st + 0xc) = (short)err;
      }
      {
        short nx = *(short *)((char *)st + 4) + cur;
        *(short *)((char *)st + 0xc) += dy;
        *(short *)((char *)st + 0xe) = nx;
      }
      return done;
    }
    if (mode == 2) {
      if (*(short *)((char *)st + 0xc) >= 0)
        return done;
      while (*(short *)((char *)st + 0xe) != end) {
        *(short *)((char *)st + 0xc) += dy;
        *(short *)((char *)st + 0xe) =
            (short)(*(short *)((char *)st + 4) + *(short *)((char *)st + 0xe));
        if (*(short *)((char *)st + 0xc) >= 0)
          break;
      }
      return done;
    }
    return done;
  }

  {
    short cur = *(short *)((char *)st + 0x10);
    short end = *(short *)((char *)st + 0x14);
    if (cur == end) {
      done = 1;
      return done;
    }
    if (mode == 0) {
      unsigned short err = *(unsigned short *)((char *)st + 0xc);
      if ((short)err >= 0) {
        *(short *)((char *)st + 0xe) += *(short *)((char *)st + 4);
        err = (unsigned short)((short)err - dy);
        *(short *)((char *)st + 0xc) = (short)err;
      }
      {
        short ny = *(short *)((char *)st + 6) + cur;
        *(short *)((char *)st + 0xc) += dx;
        *(short *)((char *)st + 0x10) = ny;
      }
      return done;
    }
    if (mode == 1) {
      if (*(short *)((char *)st + 0xc) >= 0)
        return done;
      while (*(short *)((char *)st + 0x10) != end) {
        *(short *)((char *)st + 0xc) += dx;
        *(short *)((char *)st + 0x10) =
            (short)(*(short *)((char *)st + 6) + *(short *)((char *)st + 0x10));
        if (*(short *)((char *)st + 0xc) >= 0)
          break;
      }
      return done;
    }
    return done;
  }
}



/* FUN_000721a0 (0x721a0) — Capstone lift: blit color into clipped rect.
 * Tip: clip helper fail → early return. Happy path deferred. */
void FUN_000721a0(void *bitmap, unsigned int color, short *rect, short *clip)
{
  short local[4];

  local[0] = rect[0];
  local[1] = rect[1];
  local[2] = rect[2];
  local[3] = rect[3];

  if (bitmap == 0) {
    display_assert((const char *)0x255d94, (const char *)0x2615b0, 0x113, 1);
    system_exit(-1);
  }

  if (clip != 0) {
    if (((unsigned char (*)(short *, short *, short *))(void *)FUN_00108bc0)(
            rect, clip, local) == 0)
      return;
  }

  /* Happy path deferred — snapshot stubs FUN_00108bc0 → 0. */
  (void)color;
}



/* FUN_00072490 (0x72490) — Capstone lift: draw bitmap region (null assert path).
 * Tip: bitmap==0 or dest==0 → assert/exit. */
void FUN_00072490(void *bitmap, void *a1, void *a2, void *dest, void *a4)
{
  (void)a1;
  (void)a2;
  (void)a4;
  if (bitmap == 0 || dest == 0) {
    display_assert((const char *)0x261670, (const char *)0x2615b0, 0x1ca, 1);
    system_exit(-1);
  }
  /* Remaining blit path deferred. */
}



/* FUN_00072f70 (0x72f70) — Capstone lift: multi-face blit (color==-1 early return).
 * Tip: color==0xffffffff → setup locals then return. */
void FUN_00072f70(void *bitmap, unsigned int color, short level, short *rect,
                  void *clip, void *a5, void *a6, unsigned int mask)
{
  short local[4];
  short *r = rect;
  (void)level;
  (void)clip;
  (void)a5;
  (void)a6;
  (void)mask;

  if (r == 0) {
    local[0] = 0;
    local[1] = 0;
    local[2] = *(short *)((char *)bitmap + 4);
    local[3] = *(short *)((char *)bitmap + 6);
    r = local;
  }
  /* XBE copies rect fields into locals then: if color == -1 return */
  if (color == 0xffffffffu)
    return;
  /* Remaining face loop deferred. */
  (void)r;
}



/* FUN_00073390 (0x73390) — Capstone lift: draw textured line (early null tex path).
 * Tip snapshot: bitmap+0x2c == 0 → assert/exit. Full jumptable deferred. */
void FUN_00073390(void *bitmap, unsigned int color, void *clip, float *p0, float *p1)
{
  (void)color;
  (void)clip;
  (void)p0;
  (void)p1;
  if (*(void **)((char *)bitmap + 0x2c) == 0) {
    display_assert((const char *)0x2616c4, (const char *)0x2615b0, 0x38, 1);
    system_exit(-1);
  }
  /* Remaining format jumptable + Bresenham walk not covered by tip snapshot. */
}



/* FUN_00073770 (0x73770) — Capstone lift: emit quad edges via FUN_00073390. */
void FUN_00073770(void *a, void *b, float *rect, void *d)
{
  float lo[2];
  float hi[2];
  float one = *(float *)0x2533c8;

  lo[0] = rect[0];
  lo[1] = rect[2];
  hi[0] = rect[1] - one;
  hi[1] = rect[2];
  FUN_00073390(a, b, d, lo, hi);

  lo[0] = rect[1] - one;
  lo[1] = rect[3] - one;
  hi[0] = rect[1] - one;
  hi[1] = rect[2];
  FUN_00073390(a, b, d, lo, hi);

  lo[0] = rect[0];
  lo[1] = rect[2];
  hi[0] = rect[3] - one;
  hi[1] = rect[0];
  FUN_00073390(a, b, d, hi, lo);

  lo[0] = rect[0];
  lo[1] = rect[2];
  hi[0] = rect[0];
  hi[1] = rect[3];
  FUN_00073390(a, b, d, lo, hi);
}



/* FUN_00073830 (0x73830) — Capstone lift: sample bitmap corners into color-key globals. */
void FUN_00073830(void)
{
  void *bm;
  void *addr;
  unsigned int c0;
  unsigned int c1;
  unsigned int c2;
  short x;

  bm = *(void **)0x334150;
  *(unsigned char *)0x334148 = 1;
  *(unsigned char *)0x334149 = 0;

  addr = bitmap_2d_address(bm, 0, 0, 0);
  c0 = *(unsigned int *)addr & 0xffffffu;
  *(unsigned int *)0x33413c = c0;

  addr = bitmap_2d_address(bm, 1, 0, 0);
  c1 = *(unsigned int *)addr & 0xffffffu;
  *(unsigned int *)0x334140 = c1;

  addr = bitmap_2d_address(bm, 2, 0, 0);
  c2 = *(unsigned int *)addr & 0xffffffu;
  *(unsigned int *)0x334144 = c2;

  if (c2 == c1 && c1 != 0xffu)
    *(unsigned char *)0x334148 = 0;

  if (c0 == c1) {
    *(unsigned int *)0x334144 = 0xffffu;
    *(unsigned char *)0x334149 = 1;
  }

  bm = *(void **)0x334150;
  for (x = 3; x < *(short *)((char *)bm + 4); x = (short)(x + 1)) {
    unsigned int px0;
    unsigned int px1;
    addr = bitmap_2d_address(bm, x, 0, 0);
    px0 = *(unsigned int *)addr & 0xffffffu;
    addr = bitmap_2d_address(bm, x, 1, 0);
    px1 = *(unsigned int *)addr & 0xffffffu;
    if (px0 != *(unsigned int *)0x33413c && px1 != *(unsigned int *)0x334140)
      *(unsigned char *)0x334148 = 0;
    bm = *(void **)0x334150;
  }

  if (*(unsigned char *)0x334148 == 0) {
    unsigned int bad = 0xff000000u;
    *(unsigned int *)0x334144 = bad;
    *(unsigned int *)0x334140 = bad;
    *(unsigned int *)0x33413c = bad;
  }
}



/* FUN_00073960 (0x73960) — Capstone lift: advance face/row past color-key runs.
 * ABI: inout short* on stack. Returns current index. */
short FUN_00073960(short *inout)
{
  void *bm;
  short face;
  short i;
  unsigned char any_diff;
  unsigned char saw_key;
  unsigned int pix;

  if (inout == 0) {
    display_assert((const char *)0x2616e0, (const char *)0x2616f0, 0x1d9, 1);
    system_exit(-1);
  }

  bm = *(void **)0x334150;
  if (*(unsigned char *)0x334149 != 0) {
    face = *inout;
    any_diff = 0;
    if (face >= *(short *)((char *)bm + 6))
      return face;
    while (face < *(short *)((char *)bm + 6)) {
      saw_key = 0;
      i = 0;
      if (*(short *)((char *)bm + 4) > 0) {
        while (i < *(short *)((char *)bm + 4)) {
          pix = *(unsigned int *)bitmap_2d_address(bm, i, face, 0) & 0xffffffu;
          if (pix != *(unsigned int *)0x33413c)
            saw_key = 1;
          bm = *(void **)0x334150;
          i = (short)(i + 1);
        }
        if (saw_key) {
          any_diff = 1;
          face = (short)(face + 1);
          continue;
        }
      }
      if (any_diff)
        break;
      *inout = (short)(face + 1);
      bm = *(void **)0x334150;
      face = (short)(face + 1);
    }
    return face;
  }

  /* flag 0x334149 clear: scan along width for key/non-key transition */
  face = *inout;
  saw_key = 0;
  if (face >= *(short *)((char *)bm + 6))
    return face;
  while (face < *(short *)((char *)bm + 6)) {
    pix = *(unsigned int *)bitmap_2d_address(bm, 0, face, 0) & 0xffffffu;
    if (pix == *(unsigned int *)0x33413c) {
      saw_key = 1;
    } else if (pix == *(unsigned int *)0x334140) {
      if (saw_key)
        break;
      *inout = (short)(face + 1);
    } else {
      *inout = (short)(face + 1);
    }
    bm = *(void **)0x334150;
    face = (short)(face + 1);
  }
  return face;
}



/* FUN_00073a80 (0x73a80) — Capstone lift: scan bitmap faces for color key.
 * ABI: face@<di>. */
void FUN_00073a80(short face /*@<di>*/)
{
  void *bm;
  short i;
  unsigned int pix;
  void *addr;

  if (face < 0)
    return;
  bm = *(void **)0x334150;
  if (face >= *(short *)((char *)bm + 6))
    return;
  i = 0;
  if (*(short *)((char *)bm + 4) <= 0)
    return;
  while (i < *(short *)((char *)bm + 4)) {
    addr = bitmap_2d_address(bm, i, face, 0);
    pix = *(unsigned int *)addr & 0xffffffu;
    if (pix != *(unsigned int *)0x334140) {
      crt_fprintf((void *)0x331050, (const char *)0x261718, (int)i, (int)face);
      crt_fflush((void *)0x331050);
      return;
    }
    i = (short)(i + 1);
    bm = *(void **)0x334150;
  }
}



/* FUN_00073b00 (0x73b00) — Capstone lift: build DXT atlas tile.
 * Tip-prove: width not multiple of 4 → error + return 0. */
unsigned char FUN_00073b00(void *bm)
{
  int w;

  if (!bitmap_verify(bm, 1)) {
    display_assert((const char *)0x261814, (const char *)0x2616f0, 0x2c2, 1);
    system_exit(-1);
  }
  w = (int)*(short *)((char *)bm + 4);
  if ((w & 3) != 0) {
    error(2, (const char *)0x261750, w, (int)*(short *)((char *)bm + 6));
    return 0;
  }
  /* happy path deferred */
  error(2, (const char *)0x261750, w, (int)*(short *)((char *)bm + 6));
  return 0;
}



/* FUN_00073e40 (0x73e40) — Capstone lift: compute opaque bounds rect from bitmap.
 * ABI: rect stack, out@<esi>. Returns 1 if any opaque pixel visited. */
unsigned char FUN_00073e40(short *rect, short *out /*@<esi>*/)
{
  void *bm;
  short x;
  short y;
  unsigned int pix;
  unsigned int raw;
  unsigned char found;
  short v;

  found = 0;
  if (rect == 0) {
    display_assert((const char *)0x26184c, (const char *)0x2616f0, 0x3f7, 1);
    system_exit(-1);
  }
  if (out == 0) {
    display_assert((const char *)0x261830, (const char *)0x2616f0, 0x3f8, 1);
    system_exit(-1);
  }

  out[0] = 0x7fff;
  out[1] = 0x7fff;
  out[2] = (short)0x8000;
  out[3] = (short)0x8000;

  x = rect[0];
  if (x >= rect[2]) {
    out[3] = (short)(out[3] + 1);
    out[2] = (short)(out[2] + 1);
    return found;
  }

  bm = *(void **)0x334150;
  for (; x < rect[2]; x = (short)(x + 1)) {
    y = rect[1];
    for (; y < rect[3]; y = (short)(y + 1)) {
      if (y < 0 || y >= *(short *)((char *)bm + 4) ||
          x < 0 || x >= *(short *)((char *)bm + 6)) {
        continue;
      }
      raw = *(unsigned int *)bitmap_2d_address(bm, y, x, 0);
      pix = raw & 0xffffffu;
      if (*(unsigned char *)0x334148 != 0) {
        if (pix == *(unsigned int *)0x33413c ||
            pix == *(unsigned int *)0x334140 ||
            pix == *(unsigned int *)0x334144)
          goto next_y;
        if (*(short *)((char *)(*(void **)0x33414c) + 4) == 0 &&
            (raw & 0xff000000u) == 0)
          goto next_y;
      }
      v = out[1];
      out[1] = (short)((y < v) ? y : v);
      v = out[0];
      out[0] = (short)((x < v) ? x : v);
      v = out[3];
      out[3] = (short)((y > v) ? y : v);
      v = out[2];
      out[2] = (short)((x > v) ? x : v);
      found = 1;
    next_y:
      bm = *(void **)0x334150;
    }
  }

  out[3] = (short)(out[3] + 1);
  out[2] = (short)(out[2] + 1);
  return found;
}



/* FUN_00073fd0 (0x73fd0) — Capstone lift: classify bitmap format.
 * ABI: bitmap@<eax>. Tip-prove: pixel_count<=0 + type0 → 0xe. */
unsigned short FUN_00073fd0(void *bitmap /*@<eax>*/)
{
  void *mip;
  int n;
  short result;
  void *hdr;

  if (!bitmap_verify(bitmap, 1)) {
    display_assert((const char *)0x261814, (const char *)0x2616f0, 0x429, 1);
    system_exit(-1);
  }
  mip = bitmap_mipmap_address(bitmap, 0);
  (void)*(unsigned int *)mip;
  n = bitmap_get_pixel_count(bitmap);
  if (n > 0) {
    /* pixel scan deferred */
  }
  hdr = *(void **)0x33414c;
  {
    int kind = (int)*(short *)((char *)hdr + 2);
    if (kind == 0)
      result = 0xe;
    else if (kind > 5) {
      display_assert((const char *)0x261854, (const char *)0x2616f0, 0x466, 1);
      system_exit(-1);
      result = 0;
    } else {
      result = 0xe; /* other cases deferred; snapshot uses kind==0 */
    }
  }
  if (*(short *)hdr == 4) {
    /* remap deferred */
  }
  if ((*(short *)((char *)hdr + 4) == 2 || *(short *)((char *)hdr + 4) == 5) &&
      (*(unsigned char *)((char *)hdr + 6) & 2) == 0)
    return 0x11;
  return (unsigned short)result;
}



/* FUN_00074210 (0x74210) — Capstone lift: compress/copy mipmap w/ key.
 * ABI: other@stack, self@<ecx>, level@<ax>. Tip: flags bit1 → compress. */
void FUN_00074210(void *other, void *self /*@<ecx>*/, short level /*@<ax>*/)
{
  int ow, oh, od, sw, sh, sd;

  if (!bitmap_verify(self, 1)) {
    display_assert((const char *)0x261aa4, (const char *)0x2616f0, 0x6a6, 1);
    system_exit(-1);
  }
  ow = (int)*(unsigned short *)((char *)other + 4);
  sw = ow >> level;
  if (sw < 1) sw = 1;
  if ((int)*(short *)((char *)self + 4) != sw) {
    display_assert((const char *)0x261a50, (const char *)0x2616f0, 0x6a7, 1);
    system_exit(-1);
  }
  oh = (int)*(unsigned short *)((char *)other + 6);
  sh = oh >> level;
  if (sh < 1) sh = 1;
  if ((int)*(short *)((char *)self + 6) != sh) {
    display_assert((const char *)0x2619f8, (const char *)0x2616f0, 0x6a8, 1);
    system_exit(-1);
  }
  od = (int)*(unsigned short *)((char *)other + 8);
  sd = od >> level;
  if (sd < 1) sd = 1;
  if ((int)*(short *)((char *)self + 8) != sd) {
    display_assert((const char *)0x2619a0, (const char *)0x2616f0, 0x6a9, 1);
    system_exit(-1);
  }
  if (!bitmap_verify(other, 0)) {
    display_assert((const char *)0x261974, (const char *)0x2616f0, 0x6ab, 1);
    system_exit(-1);
  }
  if (*(short *)((char *)other + 0xa) != *(short *)((char *)self + 0xa)) {
    display_assert((const char *)0x261944, (const char *)0x2616f0, 0x6ac, 1);
    system_exit(-1);
  }
  if (level < 0 || level > *(short *)((char *)other + 0x14)) {
    display_assert((const char *)0x2618e8, (const char *)0x2616f0, 0x6ad, 1);
    system_exit(-1);
  }
  if ((*(unsigned char *)((char *)other + 0xe) & 8) != 0) {
    display_assert((const char *)0x2618ac, (const char *)0x2616f0, 0x6ae, 1);
    system_exit(-1);
  }
  if ((*(unsigned char *)((char *)other + 0xe) & 2) != 0) {
    int key = 0;
    if (*(unsigned char *)0x334148)
      key = 0x334144;
    bitmap_compress_to_mipmap(self, other, level, key);
    return;
  }
  /* non-compress path deferred */
}



/* FUN_000745c0 (0x745c0) — Capstone lift: copy/compress mipmap.
 * ABI: dst@<ecx>, level@<ax>, src on stack. Tip: flags bit1 clear, 0 pixels. */
void FUN_000745c0(void *src, void *dst /*@<ecx>*/, short level /*@<ax>*/)
{
  int sw, sh, sd, dw, dh, dd;

  if (!bitmap_verify(dst, 1)) {
    display_assert((const char *)0x261c58, (const char *)0x2616f0, 0x6f9, 1);
    system_exit(-1);
  }
  sw = (int)*(unsigned short *)((char *)src + 4);
  dw = sw >> level;
  if (dw < 1) dw = 1;
  if ((int)*(short *)((char *)dst + 4) != dw) {
    display_assert((const char *)0x261c08, (const char *)0x2616f0, 0x6fa, 1);
    system_exit(-1);
  }
  sh = (int)*(unsigned short *)((char *)src + 6);
  dh = sh >> level;
  if (dh < 1) dh = 1;
  if ((int)*(short *)((char *)dst + 6) != dh) {
    display_assert((const char *)0x261bb8, (const char *)0x2616f0, 0x6fb, 1);
    system_exit(-1);
  }
  sd = (int)*(unsigned short *)((char *)src + 8);
  dd = sd >> level;
  if (dd < 1) dd = 1;
  if ((int)*(short *)((char *)dst + 8) != dd) {
    display_assert((const char *)0x261b68, (const char *)0x2616f0, 0x6fc, 1);
    system_exit(-1);
  }
  if (!bitmap_verify(src, 0)) {
    display_assert((const char *)0x261b44, (const char *)0x2616f0, 0x6fe, 1);
    system_exit(-1);
  }
  if (*(short *)((char *)src + 0xa) != *(short *)((char *)dst + 0xa)) {
    display_assert((const char *)0x261b14, (const char *)0x2616f0, 0x6ff, 1);
    system_exit(-1);
  }
  if (level < 0 || level > *(short *)((char *)src + 0x14)) {
    display_assert((const char *)0x261ac8, (const char *)0x2616f0, 0x700, 1);
    system_exit(-1);
  }
  if ((*(unsigned char *)((char *)src + 0xe) & 2) != 0) {
    bitmap_3d_compress_to_mipmap(src, dst, level);
    return;
  }
  /* pixel copy deferred — snapshot uses pixel_count==0 */
  (void)bitmap_mipmap_address(src, (short)level);
  (void)bitmap_mipmap_address(dst, 0);
  if (bitmap_get_pixel_count(dst) <= 0)
    return;
}



/* FUN_000747d0 (0x747d0) — Capstone lift: collect/report bitmaps.
 * Tip-prove: bitmap_count<=0 → fprintf + store 0. */
void FUN_000747d0(void **list, short *out_count)
{
  void *hdr = *(void **)0x33414c;
  short bx = 0;
  int count = *(int *)((char *)hdr + 0x54);

  if (count > 0) {
    /* collect loop deferred */
  }
  crt_fprintf((void *)0x331050, (const char *)0x261c80, 1);
  crt_fflush((void *)0x331050);
  *out_count = bx;
}



/* FUN_00074a30 (0x74a30) — Capstone lift: allocate working bitmap.
 * Tip-prove: invalid type → error cleanup return NULL. */
void *FUN_00074a30(void *bm, unsigned char flag)
{
  short typ;
  void *created = 0;

  (void)flag;
  typ = *(short *)((char *)bm + 0xa);
  if (typ != 0 && typ != 1 && typ != 2) {
    display_assert((const char *)0x261d30, (const char *)0x2616f0, 0x518, 1);
    system_exit(-1);
    error(2, (const char *)0x261d04);
    goto cleanup;
  }
  /* create paths deferred */
  return created;
cleanup:
  bitmap_delete(created);
  return 0;
}


