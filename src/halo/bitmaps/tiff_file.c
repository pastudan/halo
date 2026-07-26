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

/* FUN_0007fa00 (0x7fa00) — XBE naked draft (batch 241). */
#if defined(__clang__)
static bool (*const b7fa00_c19a640)(file_ref_t *info) = file_exists;
static char * (*const b7fa00_c199810)(file_ref_t *info, int flags, char *name_out) = file_reference_get_name;
static int (*const b7fa00_c6d8e0)(const char *path, const char *mode) = FUN_0006d8e0;
static void (*const b7fa00_c6d820)(void) = TIFFScanlineSize;
static int (*const b7fa00_c64ec0)(char *prop, int tag, void *out) = FUN_00064ec0;
static void (*const b7fa00_c65e90)(void) = TIFFGetField;
static void (*const b7fa00_c64ee0)(int file) = FUN_00064ee0;
static void (*const b7fa00_c108a10)(void) = FUN_00108a10;
static void (*const b7fa00_c108a30)(void) = FUN_00108a30;
static void * (*const b7fa00_c7e0b0)(unsigned short width, unsigned short height, unsigned short mipmap_count, unsigned short format) = bitmap_2d_new;
static void * (*const b7fa00_c8ee60)(uint32_t size, bool zero, const char *file, int line) = debug_malloc;
static void (*const b7fa00_c6f040)(void) = FUN_0006f040;
static void * (*const b7fa00_c7c940)(void *bitmap, short x, short y, short mipmap_index) = bitmap_2d_address;
static void (*const b7fa00_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b7fa00_exitfn)(int) = system_exit;
static void (*const b7fa00_c7c8f0)(void *) = bitmap_delete;
static void (*const b7fa00_c8ef70)(void *ptr, const char *file, int line) = debug_free;
static int (*const b7fa00_c1d9179)(char *str, size_t size, const char *format, ...) = snprintf;

__attribute__((naked, noinline))
void FUN_0007fa00(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x134, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "pushl %%esi\n\t"
      "movl $0, -0xc(%%ebp)\n\t"
      "call *%[c19a640]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0007fa00_36\n\t"
      "pushl $0x2658a4\n\t"
      "leal -0x134(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0xd\n\t"
      "pushl %%esi\n\t"
      "call *%[c199810]\n\t"
      "addl $0xc, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[c6d8e0]\n\t"
      "movl %%eax, %%ebx\n\t"
      "addl $8, %%esp\n\t"
      "testl %%ebx, %%ebx\n\t"
      "movl %%ebx, -0x28(%%ebp)\n\t"
      "je .LFUN_0007fa00_35\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "call *%[c6d820]\n\t"
      "leal -0x2c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x102\n\t"
      "pushl %%ebx\n\t"
      "movl %%eax, %%edi\n\t"
      "call *%[c64ec0]\n\t"
      "leal -0x24(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x112\n\t"
      "pushl %%ebx\n\t"
      "call *%[c64ec0]\n\t"
      "leal -0x1c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x115\n\t"
      "pushl %%ebx\n\t"
      "call *%[c64ec0]\n\t"
      "leal -0x20(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x11c\n\t"
      "pushl %%ebx\n\t"
      "call *%[c65e90]\n\t"
      "leal -0x34(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x106\n\t"
      "pushl %%ebx\n\t"
      "call *%[c65e90]\n\t"
      "addl $0x40, %%esp\n\t"
      "leal -0x10(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x100\n\t"
      "pushl %%ebx\n\t"
      "call *%[c65e90]\n\t"
      "leal -0x30(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x101\n\t"
      "pushl %%ebx\n\t"
      "call *%[c65e90]\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "addl $0x18, %%esp\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "je .LFUN_0007fa00_1\n\t"
      "movl (%%eax), %%edx\n\t"
      "movl 0x4(%%eax), %%eax\n\t"
      "movl %%edx, -0x8(%%ebp)\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "jmp .LFUN_0007fa00_2\n\t"
      ".LFUN_0007fa00_1:\n\t"
      "movw -0x30(%%ebp), %%dx\n\t"
      "movw %%cx, -0x8(%%ebp)\n\t"
      "movw %%cx, -0x6(%%ebp)\n\t"
      "movw -0x10(%%ebp), %%cx\n\t"
      "movw %%cx, -0x2(%%ebp)\n\t"
      "movw %%dx, -0x4(%%ebp)\n\t"
      ".LFUN_0007fa00_2:\n\t"
      "movl $1, %%edx\n\t"
      "cmpw %%dx, -0x24(%%ebp)\n\t"
      "jne .LFUN_0007fa00_34\n\t"
      "movw -0x2c(%%ebp), %%cx\n\t"
      "cmpw $8, %%cx\n\t"
      "movw -0x1c(%%ebp), %%ax\n\t"
      "jne .LFUN_0007fa00_33\n\t"
      "cmpw $4, %%ax\n\t"
      "je .LFUN_0007fa00_3\n\t"
      "cmpw $3, %%ax\n\t"
      "je .LFUN_0007fa00_3\n\t"
      "cmpw $2, %%ax\n\t"
      "je .LFUN_0007fa00_3\n\t"
      "cmpw %%dx, %%ax\n\t"
      "jne .LFUN_0007fa00_33\n\t"
      ".LFUN_0007fa00_3:\n\t"
      "movw 0x14(%%ebp), %%ax\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .LFUN_0007fa00_4\n\t"
      "cmpw $0xb, %%ax\n\t"
      "je .LFUN_0007fa00_4\n\t"
      "pushl %%ebx\n\t"
      "movl $0x265a2c, -0xc(%%ebp)\n\t"
      "call *%[c64ee0]\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "addl $4, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0007fa00_4:\n\t"
      "cmpw %%dx, -0x20(%%ebp)\n\t"
      "jne .LFUN_0007fa00_32\n\t"
      "leal -0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c108a10]\n\t"
      "leal -0x8(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl %%eax, %%esi\n\t"
      "call *%[c108a30]\n\t"
      "addl $8, %%esp\n\t"
      "testw %%si, %%si\n\t"
      "jl .LFUN_0007fa00_31\n\t"
      "cmpw $0x7530, %%si\n\t"
      "jg .LFUN_0007fa00_31\n\t"
      "testw %%ax, %%ax\n\t"
      "jl .LFUN_0007fa00_31\n\t"
      "cmpw $0x7530, %%ax\n\t"
      "jg .LFUN_0007fa00_31\n\t"
      "pushl $0xb\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[c7e0b0]\n\t"
      "pushl $0x13f\n\t"
      "pushl $0x265914\n\t"
      "movl %%eax, %%esi\n\t"
      "pushl $0\n\t"
      "pushl %%edi\n\t"
      "movl %%esi, -0x18(%%ebp)\n\t"
      "call *%[c8ee60]\n\t"
      "addl $0x20, %%esp\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%eax, %%ebx\n\t"
      "je .LFUN_0007fa00_27\n\t"
      "testl %%ebx, %%ebx\n\t"
      "je .LFUN_0007fa00_27\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "movl %%esi, (%%edx)\n\t"
      "movl -0x8(%%ebp), %%esi\n\t"
      "movw %%si, %%ax\n\t"
      "cmpw -0x4(%%ebp), %%ax\n\t"
      "movl %%esi, -0x14(%%ebp)\n\t"
      "jge .LFUN_0007fa00_29\n\t"
      ".LFUN_0007fa00_5:\n\t"
      "testw %%si, %%si\n\t"
      "jge .LFUN_0007fa00_6\n\t"
      "xorl %%eax, %%eax\n\t"
      "jmp .LFUN_0007fa00_7\n\t"
      ".LFUN_0007fa00_6:\n\t"
      "movl -0x30(%%ebp), %%eax\n\t"
      "movswl %%si, %%ecx\n\t"
      "decl %%eax\n\t"
      "cmpl %%eax, %%ecx\n\t"
      "ja .LFUN_0007fa00_7\n\t"
      "movl %%ecx, %%eax\n\t"
      ".LFUN_0007fa00_7:\n\t"
      "movl -0x28(%%ebp), %%ecx\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c6f040]\n\t"
      "addl $0x10, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jl .LFUN_0007fa00_26\n\t"
      "movzwl -0x1c(%%ebp), %%eax\n\t"
      "decl %%eax\n\t"
      "cmpl $3, %%eax\n\t"
      "ja .LFUN_0007fa00_24\n\t"
      "jmp *.LFUN_0007fa00_jt(,%%eax,4)\n\t"
      ".LFUN_0007fa00_8:\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movl -0x18(%%ebp), %%eax\n\t"
      "pushl $0\n\t"
      "movl %%esi, %%edx\n\t"
      "subl %%ecx, %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "call *%[c7c940]\n\t"
      "movl -0x6(%%ebp), %%edx\n\t"
      "movw %%dx, %%cx\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpw -0x2(%%ebp), %%cx\n\t"
      "jge .LFUN_0007fa00_25\n\t"
      ".LFUN_0007fa00_9:\n\t"
      "testw %%dx, %%dx\n\t"
      "jge .LFUN_0007fa00_10\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "jmp .LFUN_0007fa00_11\n\t"
      ".LFUN_0007fa00_10:\n\t"
      "movl -0x10(%%ebp), %%ecx\n\t"
      "movswl %%dx, %%esi\n\t"
      "decl %%ecx\n\t"
      "cmpl %%ecx, %%esi\n\t"
      "ja .LFUN_0007fa00_11\n\t"
      "movl %%esi, %%ecx\n\t"
      ".LFUN_0007fa00_11:\n\t"
      "movswl -0x6(%%ebp), %%edi\n\t"
      "movswl %%cx, %%ecx\n\t"
      "movzbl (%%ecx,%%ebx,1), %%ecx\n\t"
      "movl %%ecx, %%esi\n\t"
      "shll $8, %%esi\n\t"
      "orl %%ecx, %%esi\n\t"
      "shll $8, %%esi\n\t"
      "orl %%ecx, %%esi\n\t"
      "shll $8, %%esi\n\t"
      "orl %%ecx, %%esi\n\t"
      "movswl %%dx, %%ecx\n\t"
      "subl %%edi, %%ecx\n\t"
      "incl %%edx\n\t"
      "movl %%esi, (%%eax,%%ecx,4)\n\t"
      "cmpw -0x2(%%ebp), %%dx\n\t"
      "jl .LFUN_0007fa00_9\n\t"
      "movl -0x14(%%ebp), %%esi\n\t"
      "jmp .LFUN_0007fa00_25\n\t"
      ".LFUN_0007fa00_12:\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movl -0x18(%%ebp), %%eax\n\t"
      "pushl $0\n\t"
      "movl %%esi, %%edx\n\t"
      "subl %%ecx, %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "call *%[c7c940]\n\t"
      "movl -0x6(%%ebp), %%edx\n\t"
      "movw %%dx, %%cx\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpw -0x2(%%ebp), %%cx\n\t"
      "movl %%eax, %%edi\n\t"
      "jge .LFUN_0007fa00_25\n\t"
      ".LFUN_0007fa00_13:\n\t"
      "testw %%dx, %%dx\n\t"
      "jge .LFUN_0007fa00_14\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "jmp .LFUN_0007fa00_15\n\t"
      ".LFUN_0007fa00_14:\n\t"
      "movl -0x10(%%ebp), %%ecx\n\t"
      "movswl %%dx, %%esi\n\t"
      "decl %%ecx\n\t"
      "cmpl %%ecx, %%esi\n\t"
      "ja .LFUN_0007fa00_15\n\t"
      "movl %%esi, %%ecx\n\t"
      ".LFUN_0007fa00_15:\n\t"
      "movswl %%cx, %%eax\n\t"
      "movzbl (%%ebx,%%eax,2), %%ecx\n\t"
      "leal (%%ebx,%%eax,2), %%esi\n\t"
      "xorl %%eax, %%eax\n\t"
      "movb 0x1(%%esi), %%ah\n\t"
      "movswl -0x6(%%ebp), %%esi\n\t"
      "orl %%ecx, %%eax\n\t"
      "shll $8, %%eax\n\t"
      "orl %%ecx, %%eax\n\t"
      "shll $8, %%eax\n\t"
      "orl %%ecx, %%eax\n\t"
      "movswl %%dx, %%ecx\n\t"
      "subl %%esi, %%ecx\n\t"
      "incl %%edx\n\t"
      "movl %%eax, (%%edi,%%ecx,4)\n\t"
      "cmpw -0x2(%%ebp), %%dx\n\t"
      "jl .LFUN_0007fa00_13\n\t"
      "movl -0x14(%%ebp), %%esi\n\t"
      "jmp .LFUN_0007fa00_25\n\t"
      ".LFUN_0007fa00_16:\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movl -0x18(%%ebp), %%eax\n\t"
      "pushl $0\n\t"
      "movl %%esi, %%edx\n\t"
      "subl %%ecx, %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "call *%[c7c940]\n\t"
      "movl -0x6(%%ebp), %%edx\n\t"
      "movw %%dx, %%cx\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpw -0x2(%%ebp), %%cx\n\t"
      "jge .LFUN_0007fa00_25\n\t"
      ".LFUN_0007fa00_17:\n\t"
      "testw %%dx, %%dx\n\t"
      "jge .LFUN_0007fa00_18\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "jmp .LFUN_0007fa00_19\n\t"
      ".LFUN_0007fa00_18:\n\t"
      "movl -0x10(%%ebp), %%ecx\n\t"
      "movswl %%dx, %%esi\n\t"
      "decl %%ecx\n\t"
      "cmpl %%ecx, %%esi\n\t"
      "ja .LFUN_0007fa00_19\n\t"
      "movl %%esi, %%ecx\n\t"
      ".LFUN_0007fa00_19:\n\t"
      "movswl %%cx, %%ecx\n\t"
      "leal (%%ebx,%%ecx,2), %%esi\n\t"
      "movzbl 0x1(%%ecx,%%esi,1), %%edi\n\t"
      "addl %%esi, %%ecx\n\t"
      "movzbl (%%ecx), %%esi\n\t"
      "movzbl 0x2(%%ecx), %%ecx\n\t"
      "orl $0xffffff00, %%esi\n\t"
      "shll $8, %%esi\n\t"
      "orl %%edi, %%esi\n\t"
      "movswl -0x6(%%ebp), %%edi\n\t"
      "shll $8, %%esi\n\t"
      "orl %%ecx, %%esi\n\t"
      "movswl %%dx, %%ecx\n\t"
      "subl %%edi, %%ecx\n\t"
      "incl %%edx\n\t"
      "movl %%esi, (%%eax,%%ecx,4)\n\t"
      "cmpw -0x2(%%ebp), %%dx\n\t"
      "jl .LFUN_0007fa00_17\n\t"
      "movl -0x14(%%ebp), %%esi\n\t"
      "jmp .LFUN_0007fa00_25\n\t"
      ".LFUN_0007fa00_20:\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movl -0x18(%%ebp), %%eax\n\t"
      "pushl $0\n\t"
      "movl %%esi, %%edx\n\t"
      "subl %%ecx, %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "call *%[c7c940]\n\t"
      "movl -0x6(%%ebp), %%edx\n\t"
      "movw %%dx, %%cx\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpw -0x2(%%ebp), %%cx\n\t"
      "movl %%eax, %%edi\n\t"
      "jge .LFUN_0007fa00_25\n\t"
      ".LFUN_0007fa00_21:\n\t"
      "testw %%dx, %%dx\n\t"
      "jge .LFUN_0007fa00_22\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "jmp .LFUN_0007fa00_23\n\t"
      ".LFUN_0007fa00_22:\n\t"
      "movl -0x10(%%ebp), %%ecx\n\t"
      "movswl %%dx, %%esi\n\t"
      "decl %%ecx\n\t"
      "cmpl %%ecx, %%esi\n\t"
      "ja .LFUN_0007fa00_23\n\t"
      "movl %%esi, %%ecx\n\t"
      ".LFUN_0007fa00_23:\n\t"
      "movswl %%cx, %%eax\n\t"
      "movzbl 0x1(%%ebx,%%eax,4), %%esi\n\t"
      "leal (%%ebx,%%eax,4), %%ecx\n\t"
      "xorl %%eax, %%eax\n\t"
      "movb 0x3(%%ecx), %%ah\n\t"
      "movb (%%ecx), %%al\n\t"
      "movzbl 0x2(%%ecx), %%ecx\n\t"
      "shll $8, %%eax\n\t"
      "orl %%esi, %%eax\n\t"
      "movswl -0x6(%%ebp), %%esi\n\t"
      "shll $8, %%eax\n\t"
      "orl %%ecx, %%eax\n\t"
      "movswl %%dx, %%ecx\n\t"
      "subl %%esi, %%ecx\n\t"
      "incl %%edx\n\t"
      "movl %%eax, (%%edi,%%ecx,4)\n\t"
      "cmpw -0x2(%%ebp), %%dx\n\t"
      "jl .LFUN_0007fa00_21\n\t"
      "movl -0x14(%%ebp), %%esi\n\t"
      "jmp .LFUN_0007fa00_25\n\t"
      ".LFUN_0007fa00_24:\n\t"
      "pushl $1\n\t"
      "pushl $0x196\n\t"
      "pushl $0x265914\n\t"
      "pushl $0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0007fa00_25:\n\t"
      "incl %%esi\n\t"
      "cmpw -0x4(%%ebp), %%si\n\t"
      "movl %%esi, -0x14(%%ebp)\n\t"
      "jl .LFUN_0007fa00_5\n\t"
      "jmp .LFUN_0007fa00_29\n\t"
      ".LFUN_0007fa00_26:\n\t"
      "movl -0x18(%%ebp), %%esi\n\t"
      "movl $0x265a0c, -0xc(%%ebp)\n\t"
      "jmp .LFUN_0007fa00_28\n\t"
      ".LFUN_0007fa00_27:\n\t"
      "movl $0x2658bc, -0xc(%%ebp)\n\t"
      ".LFUN_0007fa00_28:\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_0007fa00_29\n\t"
      "pushl %%esi\n\t"
      "call *%[c7c8f0]\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_0007fa00_29:\n\t"
      "testl %%ebx, %%ebx\n\t"
      "je .LFUN_0007fa00_30\n\t"
      "pushl $0x1a6\n\t"
      "pushl $0x265914\n\t"
      "pushl %%ebx\n\t"
      "call *%[c8ef70]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_0007fa00_30:\n\t"
      "movl -0x28(%%ebp), %%ebx\n\t"
      "pushl %%ebx\n\t"
      "call *%[c64ee0]\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "addl $4, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0007fa00_31:\n\t"
      "pushl %%ebx\n\t"
      "movl $0x2659fc, -0xc(%%ebp)\n\t"
      "call *%[c64ee0]\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "addl $4, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0007fa00_32:\n\t"
      "pushl %%ebx\n\t"
      "movl $0x2659c8, -0xc(%%ebp)\n\t"
      "call *%[c64ee0]\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "addl $4, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0007fa00_33:\n\t"
      "movzwl %%ax, %%edx\n\t"
      "pushl %%edx\n\t"
      "movzwl %%cx, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x265990\n\t"
      "pushl $0x200\n\t"
      "pushl $0x334580\n\t"
      "call *%[c1d9179]\n\t"
      "addl $0x14, %%esp\n\t"
      "pushl %%ebx\n\t"
      "movl $0x334580, -0xc(%%ebp)\n\t"
      "call *%[c64ee0]\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "addl $4, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0007fa00_34:\n\t"
      "pushl %%ebx\n\t"
      "movl $0x265960, -0xc(%%ebp)\n\t"
      "call *%[c64ee0]\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "addl $4, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0007fa00_35:\n\t"
      "popl %%esi\n\t"
      "movl $0x265950, %%eax\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0007fa00_36:\n\t"
      "popl %%esi\n\t"
      "movl $0x26593c, %%eax\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_0007fa00_jt:\n\t"
      ".long .LFUN_0007fa00_8\n\t"
      ".long .LFUN_0007fa00_12\n\t"
      ".long .LFUN_0007fa00_16\n\t"
      ".long .LFUN_0007fa00_20\n\t"
      ".text\n\t"
      :
      : [c19a640] "m"(b7fa00_c19a640), [c199810] "m"(b7fa00_c199810), [c6d8e0] "m"(b7fa00_c6d8e0), [c6d820] "m"(b7fa00_c6d820), [c64ec0] "m"(b7fa00_c64ec0), [c65e90] "m"(b7fa00_c65e90), [c64ee0] "m"(b7fa00_c64ee0), [c108a10] "m"(b7fa00_c108a10), [c108a30] "m"(b7fa00_c108a30), [c7e0b0] "m"(b7fa00_c7e0b0), [c8ee60] "m"(b7fa00_c8ee60), [c6f040] "m"(b7fa00_c6f040), [c7c940] "m"(b7fa00_c7c940), [assert] "m"(b7fa00_assert), [exitfn] "m"(b7fa00_exitfn), [c7c8f0] "m"(b7fa00_c7c8f0), [c8ef70] "m"(b7fa00_c8ef70), [c1d9179] "m"(b7fa00_c1d9179)
      : "memory");
}
#else
#error "FUN_0007fa00: clang naked draft required"
#endif


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
