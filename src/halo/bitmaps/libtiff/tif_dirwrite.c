/* kb object: tif_dirwrite.obj -> bitmaps/libtiff/tif_dirwrite.c
 * Original path: c:\halo\SOURCE\bitmaps\libtiff\tif_dirwrite.c
 */

/* FUN_00067760 (0x67760) — write TIFF field payload; advance 0x3340b0 cursor.
 * ABI: out@<edi>, typeinfo@<ebx>, data cdecl. */
int FUN_00067760(void *out /*@<edi>*/, void *typeinfo /*@<ebx>*/, void *data)
{
  unsigned int cursor;
  unsigned int type;
  unsigned int nbytes;
  int fd;
  int got;

  cursor = *(unsigned int *)0x3340b0;
  type = *(unsigned short *)((char *)out + 2);
  *((unsigned int *)((char *)out + 8)) = cursor;
  fd = (int)*(short *)((char *)typeinfo + 4);
  nbytes = (*(unsigned int *)(0x2ca024 + type * 4)) *
           (*(unsigned int *)((char *)out + 4));
  got = ((int (*)(int, unsigned int, int))__lseek)(fd, cursor, 0);
  if (got != (int)cursor)
    goto fail;
  got = ((int (*)(int, void *, unsigned int))__write)(fd, data, nbytes);
  if (got != (int)nbytes)
    goto fail;
  nbytes = (nbytes + 1u) & ~1u;
  *(unsigned int *)0x3340b0 = cursor + nbytes;
  return 1;

fail:
  {
    void *info;
    info = ((void *(*)(unsigned int))TIFFDefaultDirectory)(
        (unsigned int)*(unsigned short *)out);
    FUN_00068a30(*(void **)typeinfo, (void *)0x25fe08,
                 *(void **)((char *)info + 0x10));
    return 0;
  }
}

/* FUN_000679f0 (0x679f0) — pack SHORT array field via FUN_00067760.
 * ABI: tag@<ax>, tif@<edx>, out@<ecx>; count/items cdecl. */
int FUN_000679f0(unsigned short tag /*@<ax>*/, void *tif /*@<edx>*/,
                 void *out /*@<ecx>*/, int count, void **items)
{
  unsigned int saved;
  unsigned int bits;
  int i;

  *(unsigned short *)out = tag;
  *((unsigned short *)out + 1) = 3;
  bits = 1u << *(unsigned char *)((char *)tif + 0x36);
  saved = *(unsigned int *)0x3340b0;
  *((unsigned int *)out + 1) = bits;
  for (i = 0; i < count; i++) {
    if (!FUN_00067760(out, tif, items[i]))
      return 0;
  }
  *((unsigned int *)out + 1) = bits * (unsigned int)count;
  *((unsigned int *)out + 2) = saved;
  return 1;
}

/* FUN_00067b80 (0x67b80) — Capstone lift: write RATIONAL float-array tag.
 * ABI: count@<eax>, tag@<cx>; typeinfo/type/out/values cdecl.
 * Tip: count==0 (snapshot arg_overrides) skips convert/ftol loop. */
int FUN_00067b80(unsigned int count /*@<eax>*/, unsigned short tag /*@<cx>*/,
                 void *typeinfo, unsigned short type, void *out, float *values)
{
  void *buf;
  int ok;

  (void)values;
  *(unsigned short *)out = tag;
  *((unsigned short *)out + 1) = type;
  *((unsigned int *)out + 1) = count;
  buf = debug_malloc(count * 8u, 0, (const char *)0x0025fefc, 0x27a);
  ok = FUN_00067760(out, typeinfo, buf);
  debug_free(buf, (const char *)0x0025fefc, 0x281);
  return ok;
}


/* FUN_00067f70 (0x67f70) — Capstone lift: write SHORT spp field.
 * ABI: out@<esi>; tif/tag cdecl. Tip: *(tif+0x44)==0 pack path. */
int FUN_00067f70(void *out /*@<esi>*/, void *tif, unsigned short tag)
{
  unsigned short local[6] = {0};
  unsigned short got = 0;
  unsigned int spp;
  unsigned int packed;

  ((void (*)(void *, unsigned int, unsigned short *))_TIFFgetfield)(
      (char *)tif + 0x14, (unsigned int)tag, &got);
  spp = *(unsigned short *)((char *)tif + 0x44);
  if ((int)spp > 0) {
    unsigned int fill = ((unsigned int)got << 16) | (unsigned int)got;
    unsigned int words = spp;
    unsigned int *dst = (unsigned int *)local;
    unsigned int n = words >> 1;
    while (n--)
      *dst++ = fill;
    if (words & 1u)
      *(unsigned short *)dst = got;
  }
  *(unsigned short *)out = tag;
  *((unsigned short *)out + 1) = 3;
  *((unsigned int *)out + 1) = spp;
  if ((int)spp > 2) {
    return FUN_00067760(out, tif, local);
  }
  packed = (unsigned int)local[0];
  if (*(unsigned short *)((char *)tif + 0xc4) == 0x4d4d) {
    packed <<= 16;
    *((unsigned int *)out + 2) = packed;
    if (spp == 2u)
      *((unsigned int *)out + 2) = packed | (unsigned int)local[1];
  } else {
    *((unsigned int *)out + 2) = packed;
    if (spp == 2u)
      *((unsigned int *)out + 2) = packed | ((unsigned int)local[1] << 16);
  }
  return 1;
}

