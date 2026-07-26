const char *tiff_export(file_ref_t *info, __int16 *bitmap)
{
  const char *error_message = NULL;
  int tiff_format = 0;
  int photometric = 1;
  int samples_per_pixel = 1;
  char path[256];
  int tiff;
  int row_size;
  uint8_t *row_buffer;
  int y;

  switch (*(int16_t *)((char *)bitmap + 0xc)) {
  case 0:
  case 1:
  case 2:
    break;
  case 6:
  case 8:
  case 9:
  case 10:
  case 11:
    tiff_format = 11;
    photometric = 2;
    samples_per_pixel = 4;
    break;
  default:
    return "invalid bitmap encoding for tiff export.";
  }

  file_reference_get_name(info, 0xd, path);
  tiff = FUN_0006d8e0(path, "w");
  if (tiff == 0)
    return "failed to open tiff";

  {
    int bits_per_pixel = bitmap_format_bits_per_pixel((int16_t)tiff_format);
    int width = (int)*(int16_t *)((char *)bitmap + 0x4);
    int row_bits = bits_per_pixel * width;
    row_size = (int)(int16_t)((row_bits + ((row_bits >> 0x1f) & 7)) >> 3);
  }

  row_buffer = (uint8_t *)debug_malloc(
    row_size, 0, "c:\\halo\\SOURCE\\bitmaps\\tiff_file.c", 0x6b);
  if (!row_buffer) {
    FUN_00064ee0(tiff);
    return "out of memory";
  }

  TIFFSetField(tiff, 0x100, (int)*(int16_t *)((char *)bitmap + 0x4));
  TIFFSetField(tiff, 0x101, (int)*(int16_t *)((char *)bitmap + 0x6));
  TIFFSetField(tiff, 0x103, 5);
  TIFFSetField(tiff, 0x106, photometric);
  TIFFSetField(tiff, 0x11c, 1);
  TIFFSetField(tiff, 0x115, samples_per_pixel);
  TIFFSetField(tiff, 0x102, 8);
  TIFFSetField(tiff, 0x112, 1);

  for (y = 0; y < *(int16_t *)((char *)bitmap + 0x6); y++) {
    uint8_t *src_row = (uint8_t *)bitmap_2d_address(bitmap, 0, y, 0);
    int x;

    switch (*(int16_t *)((char *)bitmap + 0xc)) {
    case 6:
      for (x = 0; x < *(int16_t *)((char *)bitmap + 0x4); x++) {
        uint16_t pixel = ((uint16_t *)src_row)[x];
        uint8_t high = (uint8_t)(pixel >> 8);

        row_buffer[x * 4 + 2] =
          ((uint8_t)(pixel >> 2) & 7) | (uint8_t)(pixel << 3);
        row_buffer[x * 4 + 1] = (high >> 1 & 3) | (uint8_t)(pixel >> 5) << 2;
        row_buffer[x * 4 + 0] = (high & 0xf8) | (high >> 5);
        row_buffer[x * 4 + 3] = 0xff;
      }
      break;

    case 8:
      for (x = 0; x < *(int16_t *)((char *)bitmap + 0x4); x++) {
        uint16_t pixel = ((uint16_t *)src_row)[x];
        uint8_t middle = (uint8_t)(pixel >> 5);

        row_buffer[x * 4 + 2] =
          (((uint8_t)pixel & 0x1f) | ((uint8_t)pixel << 1)) << 2;
        row_buffer[x * 4 + 1] = ((middle & 0x1f) | (middle << 1)) << 2;
        row_buffer[x * 4 + 0] =
          (((uint8_t)(pixel >> 7) & 0xfb) | (uint8_t)(pixel >> 8)) & 0xfc;
        row_buffer[x * 4 + 3] = 0xff;
      }
      break;

    case 9:
      for (x = 0; x < *(int16_t *)((char *)bitmap + 0x4); x++) {
        uint16_t pixel = ((uint16_t *)src_row)[x];
        uint8_t high = (uint8_t)(pixel >> 8);
        uint8_t middle = (uint8_t)(pixel >> 4);

        row_buffer[x * 4 + 3] = (high >> 4) | ((high >> 4) << 4);
        row_buffer[x * 4 + 2] = ((uint8_t)pixel & 0xf) | ((uint8_t)pixel << 4);
        row_buffer[x * 4 + 1] = (middle & 0xf) | (middle << 4);
        row_buffer[x * 4 + 0] = (high & 0xf) | (high << 4);
      }
      break;

    case 10:
      for (x = 0; x < *(int16_t *)((char *)bitmap + 0x4); x++) {
        uint32_t pixel = ((uint32_t *)src_row)[x];

        row_buffer[x * 4 + 2] = (uint8_t)pixel;
        row_buffer[x * 4 + 1] = (uint8_t)(pixel >> 8);
        row_buffer[x * 4 + 0] = (uint8_t)(pixel >> 0x10);
        row_buffer[x * 4 + 3] = 0xff;
      }
      break;

    case 11:
      for (x = 0; x < *(int16_t *)((char *)bitmap + 0x4); x++) {
        uint32_t pixel = ((uint32_t *)src_row)[x];

        row_buffer[x * 4 + 3] = (uint8_t)(pixel >> 0x18);
        row_buffer[x * 4 + 2] = (uint8_t)pixel;
        row_buffer[x * 4 + 1] = (uint8_t)(pixel >> 8);
        row_buffer[x * 4 + 0] = (uint8_t)(pixel >> 0x10);
      }
      break;

    default:
      csmemcpy(row_buffer, src_row, row_size);
      break;
    }

    if (TIFFWriteScanline(tiff, row_buffer, y, 0) < 0) {
      error_message = "failed to write scanline";
      break;
    }
  }

  debug_free(row_buffer, "c:\\halo\\SOURCE\\bitmaps\\tiff_file.c", 0xe7);
  FUN_00064ee0(tiff);
  return error_message;
}
/* --- tiff_file.obj batch drafts (2026-07-26) --- */

/* 0x7f3a0 */
void targa_export(void)
{
  int eax = 0;
  int ebx = 0;
  int esi = 0;
  int edi = 0;

  display_assert((char *)0x00265878, (char *)0x00265880, 36, 0);
  system_exit(0);
  /* cmp esi, ebx -> jne 0x7f3f6 */
  display_assert((char *)0x00263768, (char *)0x00265880, 37, 0);
  system_exit(0);
  /* relift: cmp word ptr [esi + 0xa], (int16_t)ebx -> je 0x7f419 */
  display_assert((char *)0x00264334, (char *)0x00265880, 38, 0);
  system_exit(0);
  /* relift: cmp word ptr [esi + 0xc], 0xa -> je 0x7f43d */
  display_assert((char *)0x00265850, (char *)0x00265880, 39, 0);
  system_exit(0);
  FUN_0019a490((void *)(uintptr_t)edi);
  /* test (char)eax, (char)eax -> je 0x7f561 */
  file_open((void *)(uintptr_t)edi, 0);
  /* test (char)eax, (char)eax -> je 0x7f561 */
  csmemset((void *)(uintptr_t)eax, 0, 18);
  file_write();
  /* test (char)eax, (char)eax -> je 0x7f547 */
  bitmap_2d_address((void *)(uintptr_t)esi, 0, 0, 0);
  /* test edi, edi -> jne 0x7f4f6 */
  display_assert((char *)0x00265848, (char *)0x00265880, 67, 0);
  system_exit(0);
  file_write();
  /* test (char)eax, (char)eax -> je 0x7f52a */
  /* cmp ebx, eax -> jl 0x7f4c5 */
  file_close((void *)(uintptr_t)edi);
  file_close((void *)(uintptr_t)edi);
  file_close((void *)(uintptr_t)edi);

  (void)eax;
  (void)ebx;
  (void)esi;
  (void)edi;
}

/* 0x7f570 */
void tiff_get_bounds(void)
{
  int eax = 0;
  int ecx = 0;
  int esi = 0;

  file_reference_get_name((void *)(uintptr_t)ecx, 13, (char *)(uintptr_t)eax);
  FUN_0006d8e0((char *)(uintptr_t)eax, (char *)0);
  /* test esi, esi -> je 0x7f5d5 */
  TIFFGetField();
  TIFFGetField();
  FUN_00064ee0(0);

  (void)eax;
  (void)ecx;
  (void)esi;
}

/* 0x7fa00 */
void FUN_0007fa00(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  file_exists((void *)(uintptr_t)esi);
  /* test (char)eax, (char)eax -> je 0x7ff1d */
  file_reference_get_name((void *)(uintptr_t)esi, 13, (char *)(uintptr_t)eax);
  FUN_0006d8e0((char *)(uintptr_t)eax, (char *)0);
  TIFFScanlineSize();
  FUN_00064ec0();
  FUN_00064ec0();
  FUN_00064ec0();
  TIFFGetField();
  TIFFGetField();
  TIFFGetField();
  TIFFGetField();
  /* cmp eax, ecx -> je 0x7fae1 */
  /* relift: cmp word ptr [ebp - 0x24], (int16_t)edx -> jne 0x7fef8 */
  /* cmp (int16_t)eax, 4 -> je 0x7fb35 */
  /* cmp (int16_t)eax, 3 -> je 0x7fb35 */
  /* cmp (int16_t)eax, 2 -> je 0x7fb35 */
  /* cmp (int16_t)eax, (int16_t)edx -> jne 0x7febf */
  /* cmp (int16_t)eax, 0xffff -> je 0x7fb5f */
  /* cmp (int16_t)eax, 0xb -> je 0x7fb5f */
  FUN_00064ee0(0);
  /* relift: cmp word ptr [ebp - 0x20], (int16_t)edx -> jne 0x7fea5 */
  FUN_00108a10();
  FUN_00108a30();
  /* test (int16_t)esi, (int16_t)esi -> jl 0x7fe8b */
  /* cmp (int16_t)esi, 0x7530 -> jg 0x7fe8b */
  /* test (int16_t)eax, (int16_t)eax -> jl 0x7fe8b */
  /* cmp (int16_t)eax, 0x7530 -> jg 0x7fe8b */
  bitmap_2d_new(0, 0, 0, 11);
  debug_malloc(edi, 0, (char *)0x00265914, 319);
  /* test ebx, ebx -> je 0x7fe4a */
  /* test (int16_t)esi, (int16_t)esi -> jge 0x7fbff */
  /* cmp ecx, eax -> ja 0x7fc0c */
  FUN_0006f040();
  /* test eax, eax -> jl 0x7fe3e */
  /* cmp eax, 3 -> ja 0x7fe11 */
  bitmap_2d_address((void *)(uintptr_t)eax, 0, 0, 0);
  /* relift: cmp (int16_t)ecx, word ptr [ebp - 2] -> jge 0x7fe2e */
  /* test (int16_t)edx, (int16_t)edx -> jge 0x7fc6a */
  /* cmp esi, ecx -> ja 0x7fc77 */
  /* relift: cmp (int16_t)edx, word ptr [ebp - 2] -> jl 0x7fc61 */
  bitmap_2d_address((void *)(uintptr_t)eax, 0, 0, 0);
  /* test (int16_t)edx, (int16_t)edx -> jge 0x7fcdd */
  /* cmp esi, ecx -> ja 0x7fcea */
  /* relift: cmp (int16_t)edx, word ptr [ebp - 2] -> jl 0x7fcd4 */
  bitmap_2d_address((void *)(uintptr_t)eax, 0, 0, 0);
  /* relift: cmp (int16_t)ecx, word ptr [ebp - 2] -> jge 0x7fe2e */
  /* test (int16_t)edx, (int16_t)edx -> jge 0x7fd51 */
  /* cmp esi, ecx -> ja 0x7fd5e */
  /* relift: cmp (int16_t)edx, word ptr [ebp - 2] -> jl 0x7fd48 */
  bitmap_2d_address((void *)(uintptr_t)eax, 0, 0, 0);
  /* test (int16_t)edx, (int16_t)edx -> jge 0x7fdcc */
  /* cmp esi, ecx -> ja 0x7fdd9 */
  /* relift: cmp (int16_t)edx, word ptr [ebp - 2] -> jl 0x7fdc3 */
  display_assert((char *)0, (char *)0x00265914, 406, 0);
  system_exit(0);
  /* test esi, esi -> je 0x7fe5e */
  bitmap_delete((void *)(uintptr_t)esi);
  /* test ebx, ebx -> je 0x7fe75 */
  debug_free((void *)(uintptr_t)ebx, (char *)0x00265914, 422);
  FUN_00064ee0(0);
  FUN_00064ee0(0);
  FUN_00064ee0(0);
  snprintf((char *)0x00334580, 512, (char *)0x00265990);
  FUN_00064ee0(0);
  FUN_00064ee0(0);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x7ff40 */
void FUN_0007ff40(void)
{
  int ebx = 0;
  int edi = 0;

  /* test ebx, ebx -> je 0x7ff5b */
  /* test edi, edi -> jne 0x7ff78 */
  display_assert((char *)0x00265a40, (char *)0x00265a54, 33, 0);
  system_exit(0);

  (void)ebx;
  (void)edi;
}

/* 0x7ffe0 */
void FUN_0007ffe0(void)
{
  int ebx = 0;
  int esi = 0;

  /* test esi, esi -> je 0x7ffeb */
  /* test ebx, ebx -> jne 0x80008 */
  display_assert((char *)0x00265a84, (char *)0x00265a54, 58, 0);
  system_exit(0);
  /* relift: cmp word ptr [esi], 0 -> je 0x8001c */
  /* relift: cmp word ptr [esi + 2], 0 -> je 0x80037 */
  /* relift: cmp word ptr [esi + 4], 0 -> je 0x80052 */

  (void)ebx;
  (void)esi;
}

/* 0x80070 */
void FUN_00080070(void)
{
  int eax = 0;
  int esi = 0;
  int edi = 0;

  /* test edi, edi -> je 0x8008e */
  /* test esi, esi -> je 0x8008e */
  /* test eax, eax -> jne 0x800ab */
  display_assert((char *)0x00265a40, (char *)0x00265a54, 79, 0);
  system_exit(0);
  FUN_0007ffe0();
  FUN_0007ff40();

  (void)eax;
  (void)esi;
  (void)edi;
}

/* 0x800d0 */
void FUN_000800d0(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* test ebx, ebx -> je 0x8011f */
  /* test eax, eax -> jne 0x8013c */
  display_assert((char *)0x00265a40, (char *)0x00265a54, 95, 0);
  system_exit(0);
  /* cmp eax, 4 -> jb 0x80153 */
  /* cmp edi, ebx -> jne 0x80246 */
  display_assert((char *)0x00265a90, (char *)0x00265a54, 124, 0);
  system_exit(0);
  /* cmp eax, 4 -> jb 0x80250 */
  /* cmp ecx, 8 -> jb 0x80280 */
  display_assert((char *)0x00265a40, (char *)0x00265a54, 79, 0);
  system_exit(0);
  FUN_0007ffe0();
  FUN_0007ff40();
  /* test eax, eax -> je 0x80311 */
  /* test eax, eax -> je 0x80320 */
  /* cmp (char)eax, 3 -> je 0x8036a */
  display_assert((char *)0x00265b18, (char *)0x00265b5c, 77, 0);
  system_exit(0);
  FUN_0011aa40(0x002ee588, (void *)(uintptr_t)edx, (char *)(uintptr_t)ecx, (void *)(uintptr_t)eax, (void *)(uintptr_t)edx, (void *)(uintptr_t)ecx, 0);
  encode_packet_group((void *)0x002ee588, (void *)(uintptr_t)ecx, (char *)(uintptr_t)eax, (void *)(uintptr_t)edx, ecx, 0);
  encode_packet_group((void *)0x002ee588, (void *)(uintptr_t)eax, (char *)(uintptr_t)edx, (void *)(uintptr_t)ecx, eax, 0);
  /* test (char)eax, (char)eax -> je 0x8045b */
  create_message(0, 0, eax, 0, 0);
  /* test eax, eax -> je 0x8045d */
  /* test esi, esi -> je 0x80482 */
  /* test ebx, ebx -> je 0x80482 */
  /* test edi, edi -> jne 0x804a2 */
  display_assert((char *)0x00265b90, (char *)0x00265b5c, 162, 0);
  system_exit(0);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}
