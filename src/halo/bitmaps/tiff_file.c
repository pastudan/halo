#include <stdint.h>
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

/* targa_export (0x7f3a0) — readable C lift (restored pre-naked). */
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
  ((void(*)(void))file_write)();
  /* test (char)eax, (char)eax -> je 0x7f547 */
  bitmap_2d_address((void *)(uintptr_t)esi, 0, 0, 0);
  /* test edi, edi -> jne 0x7f4f6 */
  display_assert((char *)0x00265848, (char *)0x00265880, 67, 0);
  system_exit(0);
  ((void(*)(void))file_write)();
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

/* tiff_get_bounds (0x7f570) — readable C lift from XBE leaf.
 * Open TIFF via file_ref, read ImageWidth/ImageLength, close. */
char tiff_get_bounds(void *file_ref, void *width_out, void *height_out)
{
  char name[0x100];
  int tiff;
  void (*get_field)(int, int, void *) = (void (*)(int, int, void *))TIFFGetField;

  file_reference_get_name((file_ref_t *)file_ref, 0xd, name);
  tiff = FUN_0006d8e0(name, (const char *)0x2658a4);
  if (!tiff)
    return 0;
  get_field(tiff, 0x100, width_out);
  get_field(tiff, 0x101, height_out);
  FUN_00064ee0(tiff);
  return 1;
}

/* FUN_0007fa00 (0x7fa00) — readable C lift (restored pre-naked). */
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
  ((void(*)(void))TIFFScanlineSize)();
  FUN_00064ec0(0, 0, 0);
  FUN_00064ec0(0, 0, 0);
  FUN_00064ec0(0, 0, 0);
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
  ((void(*)(void))FUN_00108a10)();
  ((void(*)(void))FUN_00108a30)();
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

/* FUN_0007ff40 (0x7ff40) — readable C lift. */
void FUN_0007ff40(const unsigned short *a, const unsigned short *b, unsigned short *out)
{
  extern char DAT_00265a40[];
  extern char DAT_00265a54[];
  unsigned int sum;
  unsigned int carry;

  if (a == 0 || b == 0 || out == 0) {
    display_assert(DAT_00265a40, DAT_00265a54, 0x21, 1);
    system_exit(-1);
  }
  sum = (unsigned int)a[0] + (unsigned int)b[0];
  carry = (sum > 0xffffu) ? 1u : 0u;
  out[0] = (unsigned short)sum;
  sum = (unsigned int)a[1] + (unsigned int)b[1] + carry;
  carry = (sum > 0xffffu) ? 1u : 0u;
  out[1] = (unsigned short)sum;
  sum = (unsigned int)a[2] + (unsigned int)b[2] + carry;
  carry = (sum > 0xffffu) ? 1u : 0u;
  out[2] = (unsigned short)sum;
  sum = (unsigned int)a[3] + (unsigned int)b[3] + carry;
  out[3] = (unsigned short)sum;
}
/* FUN_0007ffe0 (0x7ffe0) — readable C lift (esi=src, ebx=dst register ABI). */
void FUN_0007ffe0(void)
{
  extern char DAT_00265a54[];
  extern char DAT_00265a84[];
  const unsigned short *src;
  unsigned short *dst;
  unsigned short flag;
  unsigned int tmp;

  __asm__ volatile("movl %%esi, %0" : "=r"(src));
  __asm__ volatile("movl %%ebx, %0" : "=r"(dst));
  flag = 0;
  if (src == 0 || dst == 0) {
    display_assert(DAT_00265a84, DAT_00265a54, 0x3a, 1);
    system_exit(-1);
  }
  dst[0] = (unsigned short)(-(short)src[0]);
  if (src[0] != 0)
    flag = 1;
  tmp = (unsigned int)src[1] + flag;
  dst[1] = (unsigned short)(-(int)tmp);
  if (src[1] != 0)
    flag = 1;
  tmp = (unsigned int)src[2] + flag;
  dst[2] = (unsigned short)(-(int)tmp);
  if (src[2] != 0)
    flag = 1;
  tmp = (unsigned int)src[3] + flag;
  dst[3] = (unsigned short)(-(int)tmp);
}
/* FUN_00080070 (0x80070) — readable C lift. */
void FUN_00080070(const unsigned short *a, const unsigned short *b, unsigned short *out)
{
  extern char DAT_00265a40[];
  extern char DAT_00265a54[];
  unsigned short tmp[4];
  unsigned short flag;
  unsigned int t;

  if (a == 0 || b == 0 || out == 0) {
    display_assert(DAT_00265a40, DAT_00265a54, 0x4f, 1);
    system_exit(-1);
  }
  /* inlined FUN_0007ffe0(esi=b, ebx=tmp) */
  flag = 0;
  tmp[0] = (unsigned short)(-(short)b[0]);
  if (b[0] != 0)
    flag = 1;
  t = (unsigned int)b[1] + flag;
  tmp[1] = (unsigned short)(-(int)t);
  if (b[1] != 0)
    flag = 1;
  t = (unsigned int)b[2] + flag;
  tmp[2] = (unsigned short)(-(int)t);
  if (b[2] != 0)
    flag = 1;
  t = (unsigned int)b[3] + flag;
  tmp[3] = (unsigned short)(-(int)t);
  FUN_0007ff40(a, tmp, out);
}
/* FUN_000800d0 (0x800d0) — readable C lift from XBE leaf. */
void FUN_000800d0(unsigned short *vec, unsigned short *mat, unsigned short *out)
{
  unsigned int acc[7];
  unsigned int m00, m01, m10, m11;
  unsigned int i;
  extern char DAT_00265a54[];
  extern char DAT_00265a40[];

  if (vec == 0 || mat == 0 || out == 0) {
    display_assert(DAT_00265a40, DAT_00265a54, 0x5f, 1);
    system_exit(-1);
  }

  for (i = 0; i < 7; i++)
    acc[i] = i;

  m00 = mat[0];
  m01 = mat[1];
  m10 = mat[2];
  m11 = mat[3];

  for (i = 0; i < 4; i++) {
    unsigned int v = vec[i];
    unsigned int p;
    unsigned int lo;
    unsigned int hi;

    p = v * m00;
    lo = p & 0xffffu;
    hi = p >> 16;
    acc[i] += lo;
    acc[i + 1] += hi;

    p = v * m01;
    lo = p & 0xffffu;
    hi = p >> 16;
    acc[i + 1] += lo;
    acc[i + 2] += hi;

    p = v * m10;
    lo = p & 0xffffu;
    hi = p >> 16;
    acc[i + 2] += lo;
    acc[i + 3] += hi;

    p = v * m11;
    lo = p & 0xffffu;
    hi = p >> 16;
    acc[i + 3] += lo;
    acc[i + 4] += hi;
  }

  out[0] = (unsigned short)acc[0];
  out[1] = (unsigned short)acc[1];
  out[2] = (unsigned short)acc[2];
  out[3] = (unsigned short)acc[3];
}


