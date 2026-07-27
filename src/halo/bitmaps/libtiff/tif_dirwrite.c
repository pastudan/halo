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
