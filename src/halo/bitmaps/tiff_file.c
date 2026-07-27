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

/* targa_export (0x7f3a0) — XBE naked draft (batch 245). */
#if defined(__clang__)
static void (*const b7f3a0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b7f3a0_exitfn)(int) = system_exit;
static bool (*const b7f3a0_c19a490)(file_ref_t *info) = FUN_0019a490;
static bool (*const b7f3a0_c19a7a0)(file_ref_t *info, int flags) = file_open;
static void *(*const b7f3a0_memset)(void *, int, unsigned int) = csmemset;
static void (*const b7f3a0_c19ac00)(void) = file_write;
static void * (*const b7f3a0_c7c940)(void *bitmap, short x, short y, short mipmap_index) = bitmap_2d_address;
static bool (*const b7f3a0_c19a930)(file_ref_t *info) = file_close;

__attribute__((naked, noinline))
void targa_export(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x18, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "cmpl %%ebx, %%edi\n\t"
      "movl %%ebx, -0x4(%%ebp)\n\t"
      "jne .Ltarga_export_1\n\t"
      "pushl $1\n\t"
      "pushl $0x24\n\t"
      "pushl $0x265880\n\t"
      "pushl $0x265878\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Ltarga_export_1:\n\t"
      "movl 0xc(%%ebp), %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "jne .Ltarga_export_2\n\t"
      "pushl $1\n\t"
      "pushl $0x25\n\t"
      "pushl $0x265880\n\t"
      "pushl $0x263768\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Ltarga_export_2:\n\t"
      "cmpw %%bx, 0xa(%%esi)\n\t"
      "je .Ltarga_export_3\n\t"
      "pushl $1\n\t"
      "pushl $0x26\n\t"
      "pushl $0x265880\n\t"
      "pushl $0x264334\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Ltarga_export_3:\n\t"
      "cmpw $0xa, 0xc(%%esi)\n\t"
      "je .Ltarga_export_4\n\t"
      "pushl $1\n\t"
      "pushl $0x27\n\t"
      "pushl $0x265880\n\t"
      "pushl $0x265850\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Ltarga_export_4:\n\t"
      "pushl %%edi\n\t"
      "call *%[c19a490]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Ltarga_export_10\n\t"
      "pushl $2\n\t"
      "pushl %%edi\n\t"
      "call *%[c19a7a0]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Ltarga_export_10\n\t"
      "pushl $0x12\n\t"
      "leal -0x18(%%ebp), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "call *%[memset]\n\t"
      "movw 0x4(%%esi), %%cx\n\t"
      "movw 0x6(%%esi), %%dx\n\t"
      "leal -0x18(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x12\n\t"
      "pushl %%edi\n\t"
      "movb $0, -0x18(%%ebp)\n\t"
      "movb $0, -0x17(%%ebp)\n\t"
      "movb $2, -0x16(%%ebp)\n\t"
      "movw %%bx, -0x10(%%ebp)\n\t"
      "movw %%bx, -0xe(%%ebp)\n\t"
      "movw %%cx, -0xc(%%ebp)\n\t"
      "movw %%dx, -0xa(%%ebp)\n\t"
      "movb $0x20, -0x8(%%ebp)\n\t"
      "movb $0x28, -0x7(%%ebp)\n\t"
      "call *%[c19ac00]\n\t"
      "addl $0x18, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Ltarga_export_8\n\t"
      "movswl 0x4(%%esi), %%eax\n\t"
      "shll $2, %%eax\n\t"
      "cmpw $0, 0x6(%%esi)\n\t"
      "movl %%eax, 0xc(%%ebp)\n\t"
      "jle .Ltarga_export_9\n\t"
      ".Ltarga_export_5:\n\t"
      "pushl $0\n\t"
      "pushl %%ebx\n\t"
      "pushl $0\n\t"
      "pushl %%esi\n\t"
      "call *%[c7c940]\n\t"
      "movl %%eax, %%edi\n\t"
      "addl $0x10, %%esp\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .Ltarga_export_6\n\t"
      "pushl $1\n\t"
      "pushl $0x43\n\t"
      "pushl $0x265880\n\t"
      "pushl $0x265848\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Ltarga_export_6:\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c19ac00]\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Ltarga_export_7\n\t"
      "movswl 0x6(%%esi), %%eax\n\t"
      "incl %%ebx\n\t"
      "cmpl %%eax, %%ebx\n\t"
      "jl .Ltarga_export_5\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "pushl %%edi\n\t"
      "call *%[c19a930]\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "addl $4, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Ltarga_export_7:\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "pushl %%edi\n\t"
      "movl $0x265834, -0x4(%%ebp)\n\t"
      "call *%[c19a930]\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "addl $4, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Ltarga_export_8:\n\t"
      "movl $0x26581c, -0x4(%%ebp)\n\t"
      ".Ltarga_export_9:\n\t"
      "pushl %%edi\n\t"
      "call *%[c19a930]\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "addl $4, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Ltarga_export_10:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl $0x265808, %%eax\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b7f3a0_assert), [exitfn] "m"(b7f3a0_exitfn), [c19a490] "m"(b7f3a0_c19a490), [c19a7a0] "m"(b7f3a0_c19a7a0), [memset] "m"(b7f3a0_memset), [c19ac00] "m"(b7f3a0_c19ac00), [c7c940] "m"(b7f3a0_c7c940), [c19a930] "m"(b7f3a0_c19a930)
      : "memory");
}
#else
#error "targa_export: clang naked draft required"
#endif


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

/* FUN_0007fa00 (0x7fa00) — XBE naked draft (batch 241). */
#if defined(__clang__)
static bool (*const b7fa00_c19a640)(file_ref_t *info) = file_exists;
static char * (*const b7fa00_c199810)(file_ref_t *info, int flags, char *name_out) = file_reference_get_name;
static int (*const b7fa00_c6d8e0)(const char *path, const char *mode) = FUN_0006d8e0;
static void (*const b7fa00_c6d820)(void) = (void *)TIFFScanlineSize;
static int (*const b7fa00_c64ec0)(char *prop, int tag, void *out) = FUN_00064ec0;
static void (*const b7fa00_c65e90)(void) = TIFFGetField;
static void (*const b7fa00_c64ee0)(int file) = FUN_00064ee0;
static void (*const b7fa00_c108a10)(void) = (void *)FUN_00108a10;
static void (*const b7fa00_c108a30)(void) = (void *)FUN_00108a30;
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


