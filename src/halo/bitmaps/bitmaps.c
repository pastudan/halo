/* Interpolate between two real_rgb_color values.
 *
 * flags:
 *   bit 0 (0x1) -> interpolate in HSV space (otherwise linear RGB).
 *   bit 1 (0x2) -> invert the "shortest hue arc" selection. When the
 *                  absolute hue delta is > 0.5 this bit toggles whether
 *                  to wrap one of the hue endpoints up by +1.0 before
 *                  mixing, so the blend travels the long way around the
 *                  hue circle instead of the short way (or vice versa).
 *
 * out_color, rgb_lower_bound, rgb_upper_bound are real_rgb_color (3 floats).
 * blend is in [0, 1]; t_inv = 1.0f - blend weights the lower bound.
 *
 * Matches c:\\halo\\SOURCE\\bitmaps\\bitmap_utilities.c lines ~0x939..0x95d. */
float *FUN_0007c270(float *out_color, uint32_t flags, float *rgb_lower_bound,
                    float *rgb_upper_bound, float blend)
{
  float t_inv;
  float hsv_lower[3];
  float hsv_upper[3];
  float hsv_result[3];
  float hue_diff;
  int wrap_flag;

  t_inv = *(float *)0x2533c8 - blend;

  if (!valid_real_rgb_color(rgb_lower_bound)) {
    csprintf((char *)0x5ab100, "%s: assert_valid_real_rgb_color(%f, %f, %f)",
             "rgb_lower_bound", (double)rgb_lower_bound[0],
             (double)rgb_lower_bound[1], (double)rgb_lower_bound[2]);
    display_assert((const char *)0x5ab100,
                   "c:\\halo\\SOURCE\\bitmaps\\bitmap_utilities.c", 0x939,
                   true);
    system_exit(-1);
  }

  if (!valid_real_rgb_color(rgb_upper_bound)) {
    csprintf((char *)0x5ab100, "%s: assert_valid_real_rgb_color(%f, %f, %f)",
             "rgb_upper_bound", (double)rgb_upper_bound[0],
             (double)rgb_upper_bound[1], (double)rgb_upper_bound[2]);
    display_assert((const char *)0x5ab100,
                   "c:\\halo\\SOURCE\\bitmaps\\bitmap_utilities.c", 0x93a,
                   true);
    system_exit(-1);
  }

  if ((flags & 1) == 0) {
    /* Linear RGB interpolation. */
    out_color[0] = blend * rgb_upper_bound[0] + t_inv * rgb_lower_bound[0];
    out_color[1] = blend * rgb_upper_bound[1] + t_inv * rgb_lower_bound[1];
    out_color[2] = blend * rgb_upper_bound[2] + t_inv * rgb_lower_bound[2];
  } else {
    /* HSV interpolation. Convert both endpoints to HSV. */
    bitmap_clone(rgb_lower_bound, hsv_lower);
    bitmap_clone(rgb_upper_bound, hsv_upper);

    /* Decide whether to wrap one hue up by +1.0 so the mix takes the
     * short (or long, depending on bit 1) arc around the hue circle. */
    hue_diff = hsv_upper[0] - hsv_lower[0];
    if (hue_diff < 0.0f)
      hue_diff = -hue_diff;
    wrap_flag = (hue_diff > *(double *)0x25fea8) ? 1 : 0;

    if (wrap_flag != (int)((flags >> 1) & 1)) {
      if (hsv_upper[0] <= hsv_lower[0])
        hsv_upper[0] = hsv_upper[0] + *(float *)0x2533c8;
      else
        hsv_lower[0] = hsv_lower[0] + *(float *)0x2533c8;
    }

    hsv_result[0] = hsv_upper[0] * blend + hsv_lower[0] * t_inv;
    if (hsv_result[0] > *(float *)0x2533c8)
      hsv_result[0] = hsv_result[0] - *(float *)0x2533c8;
    hsv_result[1] = hsv_upper[1] * blend + hsv_lower[1] * t_inv;
    hsv_result[2] = hsv_upper[2] * blend + hsv_lower[2] * t_inv;

    real_hsv_color_to_real_rgb_color(hsv_result, out_color);
  }

  if (!valid_real_rgb_color(out_color)) {
    csprintf((char *)0x5ab100, "%s: assert_valid_real_rgb_color(%f, %f, %f)",
             "rgb_result", (double)out_color[0], (double)out_color[1],
             (double)out_color[2]);
    display_assert((const char *)0x5ab100,
                   "c:\\halo\\SOURCE\\bitmaps\\bitmap_utilities.c", 0x95d,
                   true);
    system_exit(-1);
  }

  return out_color;
}

/* FUN_0007c5f0 — apply bump-map height to a bitmap (0x4af in
 * bitmap_utilities.c).
 *
 * Dispatches bump-height processing to the appropriate per-type helper:
 *   type 0 (_bitmap_type_2d)       -> FUN_0007b510 (bitmap in ESI)
 *   type 1 (_bitmap_type_3d)       -> FUN_0007b940 (bitmap in EBX)
 *   type 2 (_bitmap_type_cube_map) -> FUN_00079630 (bitmap in ESI)
 *   other                          -> assert + system_exit
 *
 * bump_height must be > 0.0f (compared against DAT_002533c0 == 0.0f).
 * Confirmed: cdecl, 2 stack args; bitmap loaded into ESI at 0x7c5f4.
 * Confirmed: FID_conflict__fwprintf at 0x1d98ad / crt_fflush at 0x1d9bd2.
 * Source: c:\halo\SOURCE\bitmaps\bitmap_utilities.c, lines 0x4af-0x4bd.
 */
void FUN_0007c5f0(void *bitmap, float bump_height)
{
  short type;

  if (!bitmap_verify(bitmap, 1)) {
    display_assert("bitmap_verify(bitmap, TRUE)",
                   "c:\\halo\\SOURCE\\bitmaps\\bitmap_utilities.c", 0x4af, 1);
    system_exit(-1);
  }

  if (bump_height <= 0.0f) {
    crt_fprintf(
      (void *)0x331050,
      (const char *)0x2648d8); /* L"### WARNING importing special-effect bump
                                  map with zero-height\r\n" */
    crt_fflush((void *)0x331050);
    return;
  }

  type = *(short *)((char *)bitmap + 0xa);
  switch (type) {
  case 0:
    /* _bitmap_type_2d: bitmap passed via ESI (register arg). */
    FUN_0007b510(bump_height, bitmap);
    return;
  case 1:
    /* _bitmap_type_3d: bitmap passed via EBX (register arg). */
    FUN_0007b940(bump_height, bitmap);
    return;
  case 2:
    /* _bitmap_type_cube_map: bitmap passed via ESI (register arg). */
    FUN_00079630(bump_height, bitmap);
    return;
  default:
    break;
  }

  display_assert("### ERROR unsupported bitmap type",
                 "c:\\halo\\SOURCE\\bitmaps\\bitmap_utilities.c", 0x4bd, 1);
  system_exit(-1);
}

/*
 * FUN_0007c6c0 — hardware-upload dispatcher for a bitmap (0x569 in
 * bitmap_utilities.c).
 *
 * Verifies the bitmap, then dispatches to the per-type D3D upload helper:
 *   type 0 (_bitmap_type_2d)       -> FUN_0007ba50 (bitmap in EDI)
 *   type 1 (_bitmap_type_3d)       -> FUN_0007bcb0 (bitmap in ESI)
 *   type 2 (_bitmap_type_cube_map) -> FUN_0007bd90 (bitmap in EBX)
 *   other                          -> assert + system_exit
 *
 * Confirmed: cdecl, 1 stack arg; bitmap in ESI at 0x7c6c4.
 * Confirmed: bitmap_verify(bitmap, TRUE) at 0x7c6ca.
 * Confirmed: type field at bitmap+0xa; dispatch at 0x7c6f6..0x7c74 7.
 * Source: c:\halo\SOURCE\bitmaps\bitmap_utilities.c, line 0x569.
 */
void FUN_0007c6c0(void *bitmap)
{
  int type;

  if (!bitmap_verify(bitmap, 1)) {
    display_assert("bitmap_verify(bitmap, TRUE)",
                   "c:\\halo\\SOURCE\\bitmaps\\bitmap_utilities.c", 0x569, 1);
    system_exit(-1);
  }

  type = (int)*(short *)((char *)bitmap + 0xa);
  switch (type) {
  case 0:
    FUN_0007ba50(bitmap);
    return;
  case 1:
    FUN_0007bcb0(bitmap);
    return;
  case 2:
    FUN_0007bd90(bitmap);
    return;
  default:
    break;
  }

  display_assert("### ERROR unsupported bitmap type",
                 "c:\\halo\\SOURCE\\bitmaps\\bitmap_utilities.c", 0x577, 1);
  system_exit(-1);
}

/*
 * bitmap_type_get_string — return a display string for a bitmap type index
 * (bitmaps.c line 0x50).
 *
 * The string table at 0x2ee4a0 holds three char* pointers:
 *   [0] = "2d texture"
 *   [1] = "3d texture"
 *   [2] = "cube map"
 * Entry [3] (DAT_002ee4ac) must be NULL, confirming NUMBER_OF_BITMAP_TYPES==3.
 *
 * Confirmed: range check type>=0 && type<3 at 0x7c753.
 * Confirmed: sentinel assert at 0x7c763.
 * Confirmed: return (&PTR_s_2d_texture_002ee4a0)[type] at 0x7c772/0x7c784.
 * Source: c:\halo\SOURCE\bitmaps\bitmaps.c, line 0x50.
 */
const char *bitmap_type_get_string(short type)
{
  if (type < 0 || type > 2) {
    display_assert("type>=0 && type<NUMBER_OF_BITMAP_TYPES",
                   "c:\\halo\\SOURCE\\bitmaps\\bitmaps.c", 0x50, 1);
    system_exit(-1);
  }

  if (((const char **)0x2ee4a0)[3] != 0) {
    display_assert("bitmap_type_string_table[NUMBER_OF_BITMAP_TYPES]==NULL",
                   "c:\\halo\\SOURCE\\bitmaps\\bitmaps.c", 0x51, 1);
    system_exit(-1);
  }

  return ((const char **)0x2ee4a0)[type];
}

/*
 * bitmap_format_get_string — return a display string for a bitmap format index
 * (bitmaps.c line 0x86).
 *
 * The string pointer table at 0x2ee4b0 holds 18 char* entries for format
 * indices 0..17 (NUMBER_OF_BITMAP_FORMATS == 18, i.e. 0x12).
 * DAT_002ee4f8 (= &table[18]) must be NULL — used as the sentinel check.
 *
 * Confirmed: range check format<0 || format>0x11 at 0x7c7c6.
 * Confirmed: sentinel at DAT_002ee4f8 (0x2ee4f8 = 0x2ee4b0 + 18*4) at 0x7c7dd.
 * Confirmed: return (&PTR_s_alpha_002ee4b0)[format] at 0x7c7ec.
 * Source: c:\halo\SOURCE\bitmaps\bitmaps.c, line 0x86.
 */
const char *bitmap_format_get_string(short format)
{
  if (format < 0 || format > 0x11) {
    display_assert("format>=0 && format<NUMBER_OF_BITMAP_FORMATS",
                   "c:\\halo\\SOURCE\\bitmaps\\bitmaps.c", 0x86, 1);
    system_exit(-1);
  }

  if (((const char **)0x2ee4b0)[18] != 0) {
    display_assert("bitmap_format_string_table[NUMBER_OF_BITMAP_FORMATS]==NULL",
                   "c:\\halo\\SOURCE\\bitmaps\\bitmaps.c", 0x87, 1);
    system_exit(-1);
  }

  return ((const char **)0x2ee4b0)[format];
}

/* Look up the number of bits per pixel for a given bitmap format index.
 * The format must be in range [0, 18) and the table entry must be non-zero
 * (i.e. the format must be a supported/known type).
 * Table at 0x26491c: {8,8,8,16,0,0,16,0,16,16,32,32,0,0,4,8,8,8} */
short bitmap_format_bits_per_pixel(short format)
{
  static const char bitmap_format_bits_per_pixel_table[18] = {
    8, 8, 8, 16, 0, 0, 16, 0, 16, 16, 32, 32, 0, 0, 4, 8, 8, 8
  };

  assert_halt(format >= 0 && format < 18);
  assert_halt(bitmap_format_bits_per_pixel_table[format] != 0);
  return (short)bitmap_format_bits_per_pixel_table[format];
}

/*
 * bitmap_changed — release the hardware (D3D) texture resources for a bitmap
 * (bitmaps.c line 0x179).
 *
 * Asserts bitmap is non-NULL, then dispatches to FUN_00168b10 which
 * releases the D3D surface by bitmap type (2D/3D/cube map).
 * Called separately from bitmap_delete so the hardware resources can be
 * freed without immediately freeing the bitmap struct itself.
 *
 * Confirmed: cdecl, 1 stack arg (void *bitmap).
 * Confirmed: NULL assert at 0x7c8b9 ("bitmap", bitmaps.c line 0x179).
 * Confirmed: CALL FUN_00168b10 at 0x7c8c9 (rasterizer_xbox_hardware_bitmaps).
 * Source: c:\halo\SOURCE\bitmaps\bitmaps.c, line 0x179.
 */
void bitmap_changed(void *bitmap)
{
  if (bitmap == NULL) {
    display_assert("bitmap", "c:\\halo\\SOURCE\\bitmaps\\bitmaps.c", 0x179, 1);
    system_exit(-1);
  }

  FUN_00168b10(bitmap);
}

/* Release a bitmap's D3D texture resource and free its memory if it
 * was dynamically allocated (flag bit 0x40 at byte offset 0xe). */
void bitmap_delete(void *bitmap)
{
  if (bitmap == NULL)
    return;

  /* release D3D texture */
  ((void (*)(void *))0x168ae0)(bitmap);

  if ((*(uint8_t *)((char *)bitmap + 0xe) & 0x40) != 0) {
    /* free associated pixel data if present */
    if (*(void **)((char *)bitmap + 0x2c) != NULL)
      debug_free(*(void **)((char *)bitmap + 0x2c),
                 "c:\\halo\\SOURCE\\bitmaps\\bitmaps.c", 0x18b);
    /* free the bitmap struct itself */
    debug_free(bitmap, "c:\\halo\\SOURCE\\bitmaps\\bitmaps.c", 0x18e);
  }
}

/* bitmap_2d_address -- bitmap pixel address
 *
 * Computes a pointer to the pixel at (x, y) within a given mipmap level
 * of a 2D bitmap. Accumulates pixel counts for all mipmap levels below
 * the requested one, then adds x + width_at_mipmap * y and converts from
 * pixel offset to byte offset using bits-per-pixel.
 *
 * Confirmed: cdecl, 4 stack args (bitmap, x, y, mipmap_index), returns void*.
 * Confirmed: assert strings at lines 0x1a1-0x1a8 from bitmaps.c.
 * Confirmed: calls bitmap_format_bits_per_pixel at 0x7c840.
 * Confirmed: min_dimension = compressed ? 4 : 1 (same pattern as
 * bitmap_mipmap_width). Confirmed: mipmap loop halves width/height each level,
 * clamping to min_dimension. Confirmed: final offset = (x + accumulated +
 * width_at_mip * y) * bpp / 8 + base_address.
 */
void *bitmap_2d_address(void *bitmap, short x, short y, short mipmap_index)
{
  char *b = (char *)bitmap;
  int pixel_count;
  int min_dim;
  short bpp;
  short width;
  short height;
  int bit_offset;

  pixel_count = 0;

  if (bitmap == NULL) {
    display_assert("bitmap", "c:\\halo\\SOURCE\\bitmaps\\bitmaps.c", 0x1a1, 1);
    system_exit(-1);
  }

  if (*(int *)(b + 0x2c) == 0) {
    display_assert("bitmap->base_address",
                   "c:\\halo\\SOURCE\\bitmaps\\bitmaps.c", 0x1a2, 1);
    system_exit(-1);
  }

  if (*(short *)(b + 0xa) != 0) {
    display_assert("bitmap->type==_bitmap_type_2d",
                   "c:\\halo\\SOURCE\\bitmaps\\bitmaps.c", 0x1a3, 1);
    system_exit(-1);
  }

  if (x < 0 || x >= *(short *)(b + 0x4)) {
    display_assert("x>=0 && x<bitmap->width",
                   "c:\\halo\\SOURCE\\bitmaps\\bitmaps.c", 0x1a4, 1);
    system_exit(-1);
  }

  if (y < 0 || y >= *(short *)(b + 0x6)) {
    display_assert("y>=0 && y<bitmap->height",
                   "c:\\halo\\SOURCE\\bitmaps\\bitmaps.c", 0x1a5, 1);
    system_exit(-1);
  }

  if (mipmap_index < 0 || mipmap_index > *(short *)(b + 0x14)) {
    display_assert("mipmap_index>=0 && mipmap_index<=bitmap->mipmap_count",
                   "c:\\halo\\SOURCE\\bitmaps\\bitmaps.c", 0x1a6, 1);
    system_exit(-1);
  }

  if ((*(uint8_t *)(b + 0xe) & 2) != 0 && (x != 0 || y != 0)) {
    display_assert(
      "!TEST_FLAG(bitmap->flags, _bitmap_compressed_bit) || (x==0 && y==0)",
      "c:\\halo\\SOURCE\\bitmaps\\bitmaps.c", 0x1a7, 1);
    system_exit(-1);
  }

  if ((*(uint8_t *)(b + 0xe) & 8) != 0 && (x != 0 || y != 0)) {
    display_assert(
      "!TEST_FLAG(bitmap->flags, _bitmap_swizzled_bit) || (x==0 && y==0)",
      "c:\\halo\\SOURCE\\bitmaps\\bitmaps.c", 0x1a8, 1);
    system_exit(-1);
  }

  width = *(short *)(b + 0x4);
  height = *(short *)(b + 0x6);
  min_dim = ((*(uint8_t *)(b + 0xe) & 2) != 0) ? 4 : 1;
  bpp = bitmap_format_bits_per_pixel(*(short *)(b + 0xc));

  if (mipmap_index > 0) {
    short mip_count = mipmap_index;
    do {
      short w = width;
      short h = height;
      pixel_count = pixel_count + (int)w * (int)h;
      width =
        ((short)min_dim <= (short)(w >> 1)) ? (short)(w >> 1) : (short)min_dim;
      height =
        ((short)min_dim <= (short)(h >> 1)) ? (short)(h >> 1) : (short)min_dim;
      mip_count--;
    } while (mip_count != 0);
  }

  bit_offset = ((int)x + pixel_count + (int)width * (int)y) * (int)bpp;
  return (void *)(bit_offset / 8 + *(int *)(b + 0x2c));
}

/* 0x7d000 — dispatch bitmap_pixel_address by bitmap type.
 *
 * Asserts that bitmap != NULL and bitmap->base_address (+0x2c) != NULL,
 * then routes to the appropriate typed pixel-address function based on
 * bitmap->type (+0xa): 0=2D (bitmap_2d_address), 1=cube (bitmap_3d_address),
 * 2=3D (bitmap_cube_map_address). Returns the pixel address at (0,0[,0],
 * mipmap_index).
 *
 * Confirmed: TEST ESI,ESI / display_assert("bitmap",...,0x20d,1) at 0x7d007.
 * Confirmed: TEST [ESI+0x2c] / display_assert("bitmap->base_address",...,0x20e)
 * at 0x7d02e. Confirmed: MOVSX+SUB+JZ/DEC/DEC type switch at 0x7d052.
 * Confirmed: bitmap_2d_address(bitmap,0,0,mipmap_index) via PUSH
 * EDX+3×PUSH0+PUSH ESI at 0x7d0b3. Confirmed:
 * bitmap_3d_address(bitmap,0,0,0,mipmap_index) at 0x7d09d. Confirmed:
 * bitmap_cube_map_address(bitmap,0,0,0,mipmap_index) at 0x7d087. Confirmed:
 * display_assert("### ERROR unsupported bitmap type",...,0x21c,1) + return
 * bitmap at 0x7d061.
 */
void *bitmap_mipmap_address(void *bitmap, short mipmap_index)
{
  if (!bitmap) {
    display_assert("bitmap", "c:\\halo\\SOURCE\\bitmaps\\bitmaps.c", 0x20d, 1);
    system_exit(-1);
  }
  if (!*(void **)((char *)bitmap + 0x2c)) {
    display_assert("bitmap->base_address",
                   "c:\\halo\\SOURCE\\bitmaps\\bitmaps.c", 0x20e, 1);
    system_exit(-1);
  }
  switch ((int)*(short *)((char *)bitmap + 0xa)) {
  case 2:
    return bitmap_cube_map_address(bitmap, 0, 0, 0, mipmap_index);
  case 1:
    return bitmap_3d_address(bitmap, 0, 0, 0, mipmap_index);
  case 0:
    return bitmap_2d_address(bitmap, 0, 0, mipmap_index);
  default:
    break;
  }
  display_assert("### ERROR unsupported bitmap type",
                 "c:\\halo\\SOURCE\\bitmaps\\bitmaps.c", 0x21c, 1);
  system_exit(-1);
  return bitmap;
}

/* bitmap_validate_depth (0x7d440)
 *
 * Validate the depth field of a bitmap against its type.
 * - depth must be in the signed 16-bit range (0, 256].
 * - A depth of 1 is always valid.
 * - A depth > 1 is only valid when the bitmap type is 1 (3D texture).
 *
 * depth is passed in EAX (register arg); format is received on the stack
 * but is never read by the original implementation.
 */
bool bitmap_validate_depth(int depth , int format, int type)
{
  int16_t d = (int16_t)depth;
  int16_t t = (int16_t)type;

  (void)format; /* unused by original; stack slot present for ABI parity. */

  if (d > 0 && d <= 0x100 && (d == 1 || t == 1)) {
    return true;
  }
  return false;
}

/* bitmap_verify (0x7d470)
 *
 * Validate a bitmap_data structure for internal consistency: magic tag,
 * type/format ranges, dimension limits, depth, and mipmap count.
 * If check_hardware is set, also validates hardware-import constraints.
 */
bool bitmap_verify(void *bitmap, int check_hardware)
{
  char *b = (char *)bitmap;
  int16_t type, format, width, height, depth, mipmap_count;
  int max_dim;

  assert_halt(bitmap != NULL);

  if (*(int *)b != 0x6269746d)
    goto invalid;
  if ((*(uint16_t *)(b + 0xe) & 0xff00) != 0)
    goto invalid;

  type = *(int16_t *)(b + 0xa);
  if (type < 0 || type >= 3)
    goto invalid;

  format = *(int16_t *)(b + 0xc);
  if (format < 0 || format >= 0x12)
    goto invalid;

  width = *(int16_t *)(b + 0x4);
  if (width <= 0 || width > 0x7530)
    goto invalid;

  height = *(int16_t *)(b + 0x6);
  if (height <= 0 || height > 0x7530)
    goto invalid;

  depth = *(int16_t *)(b + 0x8);
  if (!bitmap_validate_depth(depth, format, type))
    goto invalid;

  mipmap_count = *(int16_t *)(b + 0x14);
  if (mipmap_count < 0)
    goto invalid;

  max_dim = (height > depth) ? (int)height : (int)depth;
  if ((int)width <= max_dim) {
    max_dim = (height > depth) ? (int)height : (int)depth;
  } else {
    max_dim = (int)width;
  }

  if (mipmap_count > FUN_00108db0(max_dim))
    goto invalid;

  if (check_hardware) {
    if (format == 0xb && *(int *)(b + 0x2c) != 0 && mipmap_count == 0 &&
        (*(uint8_t *)(b + 0xe) & 0xe) == 0)
      return true;
    error(2, "### ERROR bitmap @%p (#%dx#%d) appears to be invalid for import",
          bitmap, (int)width, (int)height);
    return false;
  }

  return true;

invalid:
  error(2, "### ERROR bitmap @%p (#%dx#%d) appears to be invalid", bitmap,
        (int)*(int16_t *)(b + 0x4), (int)*(int16_t *)(b + 0x6));
  return false;
}

/* 0x7d5d0 — bitmap init/validate helper.
 *
 * Asserts bitmap != NULL. If bitmap+0x28 is zero, calls FUN_00168370 to
 * set it up. Then calls FUN_00168b10 (hardware finalize), and asserts
 * bitmap_verify(bitmap, FALSE).
 *
 * Confirmed: TEST ESI,ESI / display_assert("bitmap",...,0x163,1) at 0x7d5d7.
 * Confirmed: [ESI+0x28]==0 / CALL FUN_00168370(bitmap) at 0x7d5fb.
 * Confirmed: CALL FUN_00168b10(bitmap) at 0x7d60c (batched ADD ESP,0xc at
 * 0x7d619). Confirmed: bitmap_verify(bitmap,0) /
 * display_assert("bitmap_verify(bitmap, FALSE)",...,0x171) at 0x7d614.
 */
void bitmap_rebuild(void *bitmap)
{
  if (!bitmap) {
    display_assert("bitmap", "c:\\halo\\SOURCE\\bitmaps\\bitmaps.c", 0x163, 1);
    system_exit(-1);
  }
  if (!*(int *)((char *)bitmap + 0x28)) {
    FUN_00168370(bitmap);
  }
  FUN_00168b10(bitmap);
  if (!bitmap_verify(bitmap, 0)) {
    display_assert("bitmap_verify(bitmap, FALSE)",
                   "c:\\halo\\SOURCE\\bitmaps\\bitmaps.c", 0x171, 1);
    system_exit(-1);
  }
}

/* 0x7d650 — compute bitmap mipmap level count from max dimension.
 *
 * Asserts bitmap_verify(bitmap, FALSE). If flag bit 0 at bitmap+0xe is not
 * set, returns 0. Otherwise computes max(+6, +8) as sVar3, compares with +4,
 * and calls FUN_00108db0(max_dimension) in each branch.
 *
 * Confirmed: bitmap_verify(bitmap,0) / display_assert(...,0x368,1) at 0x7d65c.
 * Confirmed: TEST [ESI+0xe],1 / JZ return-0 at 0x7d688.
 * Confirmed: MOV AX,[ESI+6]; MOV CX,[ESI+8]; MOVSX EDI,AX/CX at 0x7d68e.
 * Confirmed: MOVSX EDX,[ESI+4] / CMP EDX,EDI / JLE at 0x7d6a1.
 * Confirmed: MOV AX,DI=0 / RET at 0x7d6d0 for bit-not-set path.
 */
short bitmap_get_max_mipmap_count(void *bitmap)
{
  short sVar1;
  short sVar2;
  int sVar3;
  int iWidth;

  if (!bitmap_verify(bitmap, 0)) {
    display_assert("bitmap_verify(bitmap, FALSE)",
                   "c:\\halo\\SOURCE\\bitmaps\\bitmaps.c", 0x368, 1);
    system_exit(-1);
  }
  if (*(uint8_t *)((char *)bitmap + 0xe) & 1) {
    sVar1 = *(short *)((char *)bitmap + 6);
    sVar2 = *(short *)((char *)bitmap + 8);
    sVar3 = (int)sVar1;
    if (sVar1 <= sVar2) {
      sVar3 = (int)sVar2;
    }
    iWidth = (int)*(short *)((char *)bitmap + 4);
    if (sVar3 < iWidth) {
      return FUN_00108db0(iWidth);
    }
    if (sVar1 <= sVar2) {
      sVar1 = sVar2;
    }
    return FUN_00108db0((int)sVar1);
  }
  return 0;
}

/* bitmap_mipmap_width (0x7d6e0)
 *
 * Compute the width of a bitmap at a given mipmap level.  Clamps to a
 * minimum of 1.  If the compressed flag (bit 1 of +0xe) is set, rounds
 * up to the next multiple of 4 (DXT block alignment).
 */
short bitmap_mipmap_width(void *bitmap, int mipmap_index)
{
  char *b = (char *)bitmap;
  uint16_t width;
  uint16_t result;

  assert_halt(bitmap_verify(bitmap, 0));
  assert_halt((int16_t)mipmap_index >= 0 &&
              (int16_t)mipmap_index <= *(int16_t *)(b + 0x14));

  width = *(uint16_t *)(b + 0x4);
  result = width >> (mipmap_index & 0x1f);
  if (result < 2)
    result = 1;

  if ((*(uint8_t *)(b + 0xe) & 2) != 0)
    result = result + ((-(uint8_t)result) & 3);

  return (short)result;
}

/* bitmap_mipmap_get_height — bitmap_mipmap_height: height counterpart of
 * bitmap_mipmap_width. Returns the pixel height at the given mipmap level,
 * clamped to 1. If the compressed flag (bit 1 of +0xe) is set, rounds up to the
 * next multiple of 4 (DXT block alignment).
 */
short bitmap_mipmap_get_height(void *bitmap, short mipmap_index)
{
  char *b = (char *)bitmap;
  uint16_t height;
  uint16_t result;

  assert_halt(bitmap_verify(bitmap, 0));
  assert_halt(mipmap_index >= 0 && mipmap_index <= *(short *)(b + 0x14));

  height = *(uint16_t *)(b + 0x6);
  result = height >> (mipmap_index & 0x1f);
  if (result < 2)
    result = 1;

  if ((*(uint8_t *)(b + 0xe) & 2) != 0)
    result = result + ((-(uint8_t)result) & 3);

  return (short)result;
}

/* bitmap_mipmap_get_depth — bitmap_mipmap_depth: depth counterpart of
 * bitmap_mipmap_width. Returns the depth at the given mipmap level as a signed
 * 32-bit int, clamped to 1.  No DXT block-alignment rounding (depth is not
 * block-sized). Field +0x8 is the bitmap depth.
 */
int bitmap_mipmap_get_depth(void *bitmap, short mipmap_index)
{
  char *b = (char *)bitmap;
  short depth;

  assert_halt(bitmap_verify(bitmap, 0));
  assert_halt(mipmap_index >= 0 && mipmap_index <= *(short *)(b + 0x14));

  depth = *(short *)(b + 0x8);
  if (1 < depth >> mipmap_index)
    return depth >> mipmap_index;
  return 1;
}

/* bitmap_mipmap_get_pixel_count — total number of texels in one mipmap slice
 * (pixels per face). Returns width * height * depth at the given mipmap level,
 * multiplied by 6 for cube maps (_bitmap_type_cube_map == 2). Field +0xa is the
 * bitmap type; depth at field +0x8.
 */
int bitmap_mipmap_get_pixel_count(void *bitmap, int mipmap_index)
{
  char *b = (char *)bitmap;
  short width;
  short height;
  short depth;
  int result;

  assert_halt(bitmap_verify(bitmap, 0));
  assert_halt((short)mipmap_index >= 0 &&
              (short)mipmap_index <= *(short *)(b + 0x14));

  width = bitmap_mipmap_width(bitmap, mipmap_index);
  height = bitmap_mipmap_get_height(bitmap, mipmap_index);
  depth = (short)bitmap_mipmap_get_depth(bitmap, mipmap_index);
  result = (int)depth * (int)height * (int)width;
  if (*(short *)(b + 0xa) == 2)
    result *= 6;
  return result;
}

/* bitmap_mipmap_get_pixel_data_size — total byte size of one mipmap slice.
 * Multiplies total texels by bits-per-pixel, then ceiling-divides by 8.
 * Uses MSVC CDQ arithmetic rounding: (bits + (bits>>31 & 7)) >> 3.
 * Field +0xc is the bitmap format index passed to bitmap_format_bits_per_pixel.
 */
int bitmap_mipmap_get_pixel_data_size(void *bitmap, int mipmap_index)
{
  char *b = (char *)bitmap;
  int texels;
  short bpp;
  int total_bits;

  assert_halt(bitmap_verify(bitmap, 0));
  assert_halt((short)mipmap_index >= 0 &&
              (short)mipmap_index <= *(short *)(b + 0x14));

  texels = bitmap_mipmap_get_pixel_count(bitmap, mipmap_index);
  bpp = bitmap_format_bits_per_pixel(*(short *)(b + 0xc));
  total_bits = (int)bpp * texels;
  return (total_bits + (total_bits >> 31 & 7)) >> 3;
}

/*
 * bitmap_mipmap_get_row_pitch — compute the byte size of one scanline at a
 * given mipmap level for an uncompressed, unswizzled bitmap.
 *
 * Confirmed: bitmap_verify(bitmap, FALSE) at 0x7d9fb.
 * Confirmed: mipmap_index range check against bitmap+0x14 (mipmap_count).
 * Confirmed: flags byte at +0xe checked for compressed (bit 1) and swizzled
 * (bit 3). Confirmed: bitmap_mipmap_width * bitmap_format_bits_per_pixel / 8.
 */
int bitmap_mipmap_get_row_pitch(void *bitmap, int mipmap_index)
{
  short width;
  short bpp;
  int total_bits;

  if (!bitmap_verify(bitmap, 0)) {
    display_assert("bitmap_verify(bitmap, FALSE)",
                   "c:\\halo\\SOURCE\\bitmaps\\bitmaps.c", 0x3f5, 1);
    system_exit(-1);
  }

  if ((short)mipmap_index < 0 ||
      (short)mipmap_index > *(short *)((char *)bitmap + 0x14)) {
    display_assert("mipmap_index>=0 && mipmap_index<=bitmap->mipmap_count",
                   "c:\\halo\\SOURCE\\bitmaps\\bitmaps.c", 0x3f6, 1);
    system_exit(-1);
  }

  if ((*(uint8_t *)((char *)bitmap + 0xe) & 2) != 0) {
    display_assert("!TEST_FLAG(bitmap->flags, _bitmap_compressed_bit)",
                   "c:\\halo\\SOURCE\\bitmaps\\bitmaps.c", 0x3f7, 1);
    system_exit(-1);
  }

  if ((*(uint8_t *)((char *)bitmap + 0xe) & 8) != 0) {
    display_assert("!TEST_FLAG(bitmap->flags, _bitmap_swizzled_bit)",
                   "c:\\halo\\SOURCE\\bitmaps\\bitmaps.c", 0x3f8, 1);
    system_exit(-1);
  }

  width = bitmap_mipmap_width(bitmap, mipmap_index);
  bpp = bitmap_format_bits_per_pixel(*(short *)((char *)bitmap + 0xc));
  total_bits = (int)bpp * (int)width;
  return total_bits / 8;
}
/* --- bitmaps.obj batch drafts (2026-07-26) --- */

/* bitmap_compress_to_mipmap (0x7be60) — validate then dispatch by source type.
 *
 * Verifies source/dest bitmaps and mip index, checks dest mip dimensions match
 * source, requires dest compressed flag, then:
 *   type 0 -> FUN_000796e0
 *   type 1 -> FUN_000798e0
 *   type 2 -> FUN_00079bb0
 * Source: c:\halo\SOURCE\bitmaps\bitmap_utilities.c, lines 0x619-0x630.
 */
void bitmap_compress_to_mipmap(void *source_bitmap, void *destination_bitmap,
                               short destination_mipmap_index, int unused)
{
  short type;
  unsigned short tmp;
  int value;

  if (!bitmap_verify(source_bitmap, 1)) {
    display_assert("bitmap_verify(source_bitmap, TRUE)",
                   "c:\\halo\\SOURCE\\bitmaps\\bitmap_utilities.c", 0x619, 1);
    system_exit(-1);
  }
  if (!bitmap_verify(destination_bitmap, 0)) {
    display_assert("bitmap_verify(destination_bitmap, FALSE)",
                   "c:\\halo\\SOURCE\\bitmaps\\bitmap_utilities.c", 0x61b, 1);
    system_exit(-1);
  }
  if (destination_mipmap_index < 0 ||
      destination_mipmap_index > *(short *)((char *)destination_bitmap + 0x14)) {
    display_assert("destination_mipmap_index>=0 && destination_mipmap_index<=destination_bitmap->mipmap_count",
                   "c:\\halo\\SOURCE\\bitmaps\\bitmap_utilities.c", 0x61c, 1);
    system_exit(-1);
  }

  tmp = *(unsigned short *)((char *)destination_bitmap + 4);
  if ((short)(tmp >> destination_mipmap_index) < 1)
    value = 1;
  else
    value = (int)(short)tmp >> destination_mipmap_index;
  if (value != (int)*(short *)((char *)source_bitmap + 4)) {
    display_assert("MAX(1, destination_bitmap->width >>destination_mipmap_index)==source_bitmap->width",
                   "c:\\halo\\SOURCE\\bitmaps\\bitmap_utilities.c", 0x61d, 1);
    system_exit(-1);
  }

  tmp = *(unsigned short *)((char *)destination_bitmap + 6);
  if ((short)(tmp >> destination_mipmap_index) < 1)
    value = 1;
  else
    value = (int)(short)tmp >> destination_mipmap_index;
  if (value != (int)*(short *)((char *)source_bitmap + 6)) {
    display_assert("MAX(1, destination_bitmap->height>>destination_mipmap_index)==source_bitmap->height",
                   "c:\\halo\\SOURCE\\bitmaps\\bitmap_utilities.c", 0x61e, 1);
    system_exit(-1);
  }

  tmp = *(unsigned short *)((char *)destination_bitmap + 8);
  if ((short)(tmp >> destination_mipmap_index) < 1)
    value = 1;
  else
    value = (int)(short)tmp >> destination_mipmap_index;
  if (value != (int)*(short *)((char *)source_bitmap + 8)) {
    display_assert("MAX(1, destination_bitmap->depth >>destination_mipmap_index)==source_bitmap->depth",
                   "c:\\halo\\SOURCE\\bitmaps\\bitmap_utilities.c", 0x61f, 1);
    system_exit(-1);
  }

  if ((*(unsigned char *)((char *)destination_bitmap + 0xe) & 2) == 0) {
    display_assert("TEST_FLAG(destination_bitmap->flags, _bitmap_compressed_bit)",
                   "c:\\halo\\SOURCE\\bitmaps\\bitmap_utilities.c", 0x620, 1);
    system_exit(-1);
  }

  type = *(short *)((char *)source_bitmap + 0xa);
  if (type == 0) {
    /* Match XBE: mip@bx, dest@esi, source@edi, unused on stack. */
    register short r_bx asm("bx") = destination_mipmap_index;
    register void *r_esi asm("esi") = destination_bitmap;
    register void *r_edi asm("edi") = source_bitmap;
    {
      void (*fn)(int) = (void (*)(int))(void *)FUN_000796e0;
      fn(unused);
      (void)r_bx;
      (void)r_esi;
      (void)r_edi;
    }
    return;
  }
  if (type == 1) {
    FUN_000798e0(source_bitmap, destination_bitmap, destination_mipmap_index,
                 unused);
    return;
  }
  if (type == 2) {
    FUN_00079bb0(source_bitmap, destination_bitmap, destination_mipmap_index,
                 unused);
    return;
  }
  display_assert("### ERROR unsupported bitmap type",
                 "c:\\halo\\SOURCE\\bitmaps\\bitmap_utilities.c", 0x630, 1);
  system_exit(-1);
}


/* bitmap_3d_compress_to_mipmap (0x7c070) — uncompress-from-mipmap dispatcher.
 *
 * Despite the kb name, XBE validates a compressed source mip and expands into
 * destination, dispatching by source type:
 *   0 -> FUN_00079e70
 *   1 -> FUN_0007a1e0
 *   2 -> bitmap_2d_uncompress_from_mipmap
 * Source: c:\halo\SOURCE\bitmaps\bitmap_utilities.c, lines 0x746-0x75b.
 */
void bitmap_3d_compress_to_mipmap(void *source_bitmap, void *destination_bitmap,
                                  short source_mipmap_index)
{
  short type;
  unsigned short tmp;
  int value;

  if (!bitmap_verify(source_bitmap, 0)) {
    display_assert("bitmap_verify(source_bitmap, FALSE)",
                   "c:\\halo\\SOURCE\\bitmaps\\bitmap_utilities.c", 0x746, 1);
    system_exit(-1);
  }
  if (source_mipmap_index < 0 ||
      source_mipmap_index > *(short *)((char *)source_bitmap + 0x14)) {
    display_assert("source_mipmap_index>=0 && source_mipmap_index<=source_bitmap->mipmap_count",
                   "c:\\halo\\SOURCE\\bitmaps\\bitmap_utilities.c", 0x747, 1);
    system_exit(-1);
  }

  tmp = *(unsigned short *)((char *)source_bitmap + 4);
  if ((short)(tmp >> source_mipmap_index) < 1)
    value = 1;
  else
    value = (int)(short)tmp >> source_mipmap_index;
  if (value != (int)*(short *)((char *)destination_bitmap + 4)) {
    display_assert("MAX(1, source_bitmap->width >>source_mipmap_index)==destination_bitmap->width",
                   "c:\\halo\\SOURCE\\bitmaps\\bitmap_utilities.c", 0x748, 1);
    system_exit(-1);
  }

  tmp = *(unsigned short *)((char *)source_bitmap + 6);
  if ((short)(tmp >> source_mipmap_index) < 1)
    value = 1;
  else
    value = (int)(short)tmp >> source_mipmap_index;
  if (value != (int)*(short *)((char *)destination_bitmap + 6)) {
    display_assert("MAX(1, source_bitmap->height>>source_mipmap_index)==destination_bitmap->height",
                   "c:\\halo\\SOURCE\\bitmaps\\bitmap_utilities.c", 0x749, 1);
    system_exit(-1);
  }

  tmp = *(unsigned short *)((char *)source_bitmap + 8);
  if ((short)(tmp >> source_mipmap_index) < 1)
    value = 1;
  else
    value = (int)(short)tmp >> source_mipmap_index;
  if (value != (int)*(short *)((char *)destination_bitmap + 8)) {
    display_assert("MAX(1, source_bitmap->depth >>source_mipmap_index)==destination_bitmap->depth",
                   "c:\\halo\\SOURCE\\bitmaps\\bitmap_utilities.c", 0x74a, 1);
    system_exit(-1);
  }

  if ((*(unsigned char *)((char *)source_bitmap + 0xe) & 2) == 0) {
    display_assert("TEST_FLAG(source_bitmap->flags, _bitmap_compressed_bit)",
                   "c:\\halo\\SOURCE\\bitmaps\\bitmap_utilities.c", 0x74b, 1);
    system_exit(-1);
  }

  if (!bitmap_verify(destination_bitmap, 1)) {
    display_assert("bitmap_verify(destination_bitmap, TRUE)",
                   "c:\\halo\\SOURCE\\bitmaps\\bitmap_utilities.c", 0x74d, 1);
    system_exit(-1);
  }

  type = *(short *)((char *)source_bitmap + 0xa);
  if (type == 0) {
    FUN_00079e70(source_bitmap, destination_bitmap, source_mipmap_index);
    return;
  }
  if (type == 1) {
    FUN_0007a1e0(source_bitmap, destination_bitmap, source_mipmap_index);
    return;
  }
  if (type == 2) {
    bitmap_2d_uncompress_from_mipmap(source_bitmap, destination_bitmap,
                                     source_mipmap_index);
    return;
  }
  display_assert("### ERROR unsupported bitmap type",
                 "c:\\halo\\SOURCE\\bitmaps\\bitmap_utilities.c", 0x75b, 1);
  system_exit(-1);
}


/* FUN_0007c490 (0x7c490) — XBE naked draft (batch 263). */
#if defined(__clang__)
static float * (*const b7c490_c7c270)(float *out_color, uint32_t flags, float *rgb_lower_bound, float *rgb_upper_bound, float blend) = FUN_0007c270;
static bool (*const b7c490_c7b020)(float *rgb) = valid_real_rgb_color;
static char * (*const b7c490_c8d9d0)(char *buffer, const char *format, ...) = csprintf;
static void (*const b7c490_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b7c490_exitfn)(int) = system_exit;

__attribute__((naked, noinline))
void FUN_0007c490(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl 0x1c(%%ebp), %%eax\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "pushl %%ebx\n\t"
      "movl 0x14(%%ebp), %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "leal 0x4(%%ebx), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "addl $4, %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[c7c270]\n\t"
      "movl 0x18(%%ebp), %%edi\n\t"
      "addl $0x14, %%esp\n\t"
      "testl %%edi, %%edi\n\t"
      "je .LFUN_0007c490_4\n\t"
      "pushl %%edi\n\t"
      "call *%[c7b020]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_0007c490_1\n\t"
      "flds 0x8(%%edi)\n\t"
      "pushl $1\n\t"
      "pushl $0x96e\n\t"
      "pushl $0x2641f0\n\t"
      "subl $0x18, %%esp\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds 0x4(%%edi)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds (%%edi)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x2648c8\n\t"
      "pushl $0x26488c\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x24, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0007c490_1:\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "flds (%%ecx)\n\t"
      "fcomps 0x253f44\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .LFUN_0007c490_2\n\t"
      "flds (%%ebx)\n\t"
      "fcomps 0x253f44\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .LFUN_0007c490_2\n\t"
      "flds (%%esi)\n\t"
      "fmuls (%%edi)\n\t"
      "fstps (%%esi)\n\t"
      "flds 0x4(%%edi)\n\t"
      "fmuls 0x4(%%esi)\n\t"
      "fstps 0x4(%%esi)\n\t"
      "flds 0x8(%%edi)\n\t"
      "fmuls 0x8(%%esi)\n\t"
      "jmp .LFUN_0007c490_3\n\t"
      ".LFUN_0007c490_2:\n\t"
      "flds 0x2533c8\n\t"
      "fsubs 0x1c(%%ebp)\n\t"
      "fmuls (%%ecx)\n\t"
      "flds 0x1c(%%ebp)\n\t"
      "fmuls (%%ebx)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds 0x2533c8\n\t"
      "fsub %%st(1), %%st(0)\n\t"
      "fld %%st(1)\n\t"
      "fmuls (%%esi)\n\t"
      "fld %%st(1)\n\t"
      "fmuls (%%edi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fstps (%%esi)\n\t"
      "fld %%st(0)\n\t"
      "fmuls 0x4(%%edi)\n\t"
      "fld %%st(2)\n\t"
      "fmuls 0x4(%%esi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fstps 0x4(%%esi)\n\t"
      "fmuls 0x8(%%edi)\n\t"
      "fxch %%st(1)\n\t"
      "fmuls 0x8(%%esi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      ".LFUN_0007c490_3:\n\t"
      "fstps 0x8(%%esi)\n\t"
      ".LFUN_0007c490_4:\n\t"
      "pushl %%esi\n\t"
      "call *%[c7b020]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_0007c490_5\n\t"
      "flds 0x8(%%esi)\n\t"
      "pushl $1\n\t"
      "pushl $0x982\n\t"
      "pushl $0x2641f0\n\t"
      "subl $0x18, %%esp\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds 0x4(%%esi)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds (%%esi)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x264870\n\t"
      "pushl $0x26488c\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x24, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0007c490_5:\n\t"
      "popl %%edi\n\t"
      "movl %%esi, %%eax\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c7c270] "m"(b7c490_c7c270), [c7b020] "m"(b7c490_c7b020), [c8d9d0] "m"(b7c490_c8d9d0), [assert] "m"(b7c490_assert), [exitfn] "m"(b7c490_exitfn)
      : "memory");
}
#else
#error "FUN_0007c490: clang naked draft required"
#endif


/* bitmap_format_to_a8r8g8b8 (0x7d0d0) — XBE naked draft (batch 244). */
#if defined(__clang__)
static void (*const b7d0d0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b7d0d0_exitfn)(int) = system_exit;

__attribute__((naked, noinline))
void bitmap_format_to_a8r8g8b8(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%esi\n\t"
      "movl 0xc(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .Lbitmap_format_to_a8r8g8b8_1\n\t"
      "pushl $1\n\t"
      "pushl $0x22b\n\t"
      "pushl $0x264a74\n\t"
      "pushl $0x264cfc\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lbitmap_format_to_a8r8g8b8_1:\n\t"
      "movswl 0x8(%%ebp), %%eax\n\t"
      "cmpl $0x11, %%eax\n\t"
      "ja .Lbitmap_format_to_a8r8g8b8_12\n\t"
      "movzbl 0x7d2dc(%%eax), %%eax\n\t"
      "jmp *.Lbitmap_format_to_a8r8g8b8_jt(,%%eax,4)\n\t"
      ".Lbitmap_format_to_a8r8g8b8_2:\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "movzwl (%%esi,%%ecx,2), %%ecx\n\t"
      "movl %%ecx, %%eax\n\t"
      "andl $0xfffff800, %%eax\n\t"
      "orl $0xffff0000, %%eax\n\t"
      "shll $3, %%eax\n\t"
      "movl %%ecx, %%edx\n\t"
      "andl $0x7e0, %%edx\n\t"
      "orl %%edx, %%eax\n\t"
      "movl %%ecx, %%edx\n\t"
      "andl $0xffffe01f, %%edx\n\t"
      "shll $2, %%eax\n\t"
      "orl %%edx, %%eax\n\t"
      "movl %%ecx, %%edx\n\t"
      "shrl $1, %%edx\n\t"
      "andl $0xe, %%edx\n\t"
      "andl $0x600, %%ecx\n\t"
      "orl %%ecx, %%edx\n\t"
      "shll $3, %%eax\n\t"
      "shrl $1, %%edx\n\t"
      "orl %%edx, %%eax\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lbitmap_format_to_a8r8g8b8_3:\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "movzwl (%%esi,%%eax,2), %%ecx\n\t"
      "movl %%ecx, %%eax\n\t"
      "andl $0x7c00, %%eax\n\t"
      "shll $3, %%eax\n\t"
      "movl %%ecx, %%edx\n\t"
      "andl $0x3e0, %%edx\n\t"
      "orl %%edx, %%eax\n\t"
      "shll $2, %%eax\n\t"
      "movl %%ecx, %%edx\n\t"
      "andl $0x7000, %%edx\n\t"
      "orl %%edx, %%eax\n\t"
      "shll $1, %%eax\n\t"
      "movl %%ecx, %%edx\n\t"
      "andl $0x1f, %%edx\n\t"
      "orl %%edx, %%eax\n\t"
      "movl %%ecx, %%edx\n\t"
      "andl $0x380, %%edx\n\t"
      "shll $2, %%eax\n\t"
      "orl %%edx, %%eax\n\t"
      "movl %%ecx, %%edx\n\t"
      "shrl $0xf, %%ecx\n\t"
      "shrl $2, %%edx\n\t"
      "shll $1, %%eax\n\t"
      "andl $7, %%edx\n\t"
      "negl %%ecx\n\t"
      "orl %%edx, %%eax\n\t"
      "shll $0x18, %%ecx\n\t"
      "orl %%ecx, %%eax\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lbitmap_format_to_a8r8g8b8_4:\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "movzwl (%%esi,%%eax,2), %%edx\n\t"
      "movl %%edx, %%eax\n\t"
      "shrl $8, %%eax\n\t"
      "movl %%eax, %%esi\n\t"
      "andl $0xfffffff0, %%eax\n\t"
      "shll $0xc, %%eax\n\t"
      "orl %%edx, %%eax\n\t"
      "pushl %%edi\n\t"
      "andl $0xf, %%esi\n\t"
      "movl %%edx, %%ecx\n\t"
      "movl %%edx, %%edi\n\t"
      "andl $0xfffff000, %%eax\n\t"
      "movl %%esi, %%edx\n\t"
      "shll $4, %%edx\n\t"
      "orl %%esi, %%edx\n\t"
      "shrl $4, %%ecx\n\t"
      "shll $4, %%edx\n\t"
      "orl %%edx, %%eax\n\t"
      "andl $0xf, %%ecx\n\t"
      "orl %%ecx, %%eax\n\t"
      "shll $4, %%eax\n\t"
      "orl %%ecx, %%eax\n\t"
      "andl $0xf, %%edi\n\t"
      "shll $4, %%eax\n\t"
      "orl %%edi, %%eax\n\t"
      "shll $4, %%eax\n\t"
      "orl %%edi, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lbitmap_format_to_a8r8g8b8_5:\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "movl (%%esi,%%eax,4), %%eax\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lbitmap_format_to_a8r8g8b8_6:\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "movl (%%esi,%%ecx,4), %%eax\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lbitmap_format_to_a8r8g8b8_7:\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "movzbl (%%esi,%%edx,1), %%eax\n\t"
      "shll $0x18, %%eax\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lbitmap_format_to_a8r8g8b8_8:\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "movzbl (%%esi,%%eax,1), %%ecx\n\t"
      "movl %%ecx, %%eax\n\t"
      "orl $0xffffff00, %%eax\n\t"
      "shll $8, %%eax\n\t"
      "orl %%ecx, %%eax\n\t"
      "shll $8, %%eax\n\t"
      "orl %%ecx, %%eax\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lbitmap_format_to_a8r8g8b8_9:\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "movzbl (%%esi,%%ecx,1), %%ecx\n\t"
      "movl %%ecx, %%eax\n\t"
      "shll $8, %%eax\n\t"
      "orl %%ecx, %%eax\n\t"
      "shll $8, %%eax\n\t"
      "orl %%ecx, %%eax\n\t"
      "shll $8, %%eax\n\t"
      "orl %%ecx, %%eax\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lbitmap_format_to_a8r8g8b8_10:\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "movw (%%esi,%%edx,2), %%ax\n\t"
      "movzbl %%al, %%ecx\n\t"
      "movzwl %%ax, %%eax\n\t"
      "andl $0xffffff00, %%eax\n\t"
      "orl %%ecx, %%eax\n\t"
      "shll $8, %%eax\n\t"
      "orl %%ecx, %%eax\n\t"
      "shll $8, %%eax\n\t"
      "orl %%ecx, %%eax\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lbitmap_format_to_a8r8g8b8_11:\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "movzbl (%%esi,%%eax,1), %%ecx\n\t"
      "movl 0x2ee0a0(,%%ecx,4), %%eax\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lbitmap_format_to_a8r8g8b8_12:\n\t"
      "pushl $1\n\t"
      "pushl $0x254\n\t"
      "pushl $0x264a74\n\t"
      "pushl $0x261888\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "addl $0x14, %%esp\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".Lbitmap_format_to_a8r8g8b8_jt:\n\t"
      ".long .Lbitmap_format_to_a8r8g8b8_7\n\t"
      ".long .Lbitmap_format_to_a8r8g8b8_8\n\t"
      ".long .Lbitmap_format_to_a8r8g8b8_9\n\t"
      ".long .Lbitmap_format_to_a8r8g8b8_10\n\t"
      ".long .Lbitmap_format_to_a8r8g8b8_2\n\t"
      ".long .Lbitmap_format_to_a8r8g8b8_3\n\t"
      ".long .Lbitmap_format_to_a8r8g8b8_4\n\t"
      ".long .Lbitmap_format_to_a8r8g8b8_5\n\t"
      ".long .Lbitmap_format_to_a8r8g8b8_6\n\t"
      ".long .Lbitmap_format_to_a8r8g8b8_11\n\t"
      ".long .Lbitmap_format_to_a8r8g8b8_12\n\t"
      ".text\n\t"
      :
      : [assert] "m"(b7d0d0_assert), [exitfn] "m"(b7d0d0_exitfn)
      : "memory");
}
#else
#error "bitmap_format_to_a8r8g8b8: clang naked draft required"
#endif


/* palette_find_closest_match (0x7d300) — readable C lift from XBE leaf. */
unsigned int palette_find_closest_match(unsigned int *palette, unsigned int color)
{
  int best_index;
  unsigned int best_dist;
  int index;
  extern char DAT_00264a74[];
  extern char DAT_00264d0c[];

  if ((color & 0xff000000u) <= 0x80000000u)
    return 0xff;

  best_index = -1;
  best_dist = 0;
  for (index = 0; index < 0x100; index++) {
    unsigned int entry;
    unsigned int pr, pg, pb;
    unsigned int cr, cg, cb;
    unsigned int dr, dg, db;
    unsigned int dist;

    entry = palette[index];
    if (entry == 0)
      break;

    pr = (entry >> 16) & 0xff;
    pg = (entry >> 8) & 0xff;
    pb = entry & 0xff;
    cr = (color >> 16) & 0xff;
    cg = (color >> 8) & 0xff;
    cb = color & 0xff;

    dr = (pr >= cr) ? (pr - cr) : (cr - pr);
    dg = (pg >= cg) ? (pg - cg) : (cg - pg);
    db = (pb >= cb) ? (pb - cb) : (cb - pb);
    dist = db * db + dg * dg + dr * dr;

    if (index == 0 || best_dist > dist) {
      best_dist = dist;
      best_index = index;
    }
  }

  if ((int16_t)best_index == (int16_t)-1) {
    display_assert(DAT_00264d0c, DAT_00264a74, 0x44d, 1);
    system_exit(-1);
  }
  return (unsigned int)best_index;
}



/* bitmap_2d_get_pixel (0x7dad0) — XBE naked draft (batch 241). */
#if defined(__clang__)
static void (*const b7dad0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b7dad0_exitfn)(int) = system_exit;
static short (*const b7dad0_c7d6e0)(void *bitmap, int mipmap_index) = bitmap_mipmap_width;
static short (*const b7dad0_c7d780)(void *bitmap, short mipmap_index) = bitmap_mipmap_get_height;
static void * (*const b7dad0_c7d000)(void *bitmap, short mipmap_index) = bitmap_mipmap_address;
static short (*const b7dad0_c7c840)(short format) = bitmap_format_bits_per_pixel;
static char * (*const b7dad0_c8d9d0)(char *buffer, const char *format, ...) = csprintf;
static void (*const b7dad0_c71af0)(void) = FUN_00071af0;
static void (*const b7dad0_c71840)(void) = FUN_00071840;
static void (*const b7dad0_c715c0)(void) = DecodeBlockRGB__single_pixel;
static void (*const b7dad0_c182690)(short param_1, short param_2, unsigned short param_3, unsigned short param_4, unsigned int *param_5) = rasterizer_swizzle_compute_masks;
static void (*const b7dad0_c7d0d0)(void) = bitmap_format_to_a8r8g8b8;

__attribute__((naked, noinline))
unsigned int bitmap_2d_get_pixel(int bitmap_ref __attribute__((unused)), float *uv __attribute__((unused)), float level __attribute__((unused)), float *out __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x24, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "pushl %%edi\n\t"
      "jne .Lbitmap_2d_get_pixel_1\n\t"
      "pushl $1\n\t"
      "pushl $0x261\n\t"
      "pushl $0x264a74\n\t"
      "pushl $0x263768\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lbitmap_2d_get_pixel_1:\n\t"
      "cmpw $0, 0xa(%%esi)\n\t"
      "je .Lbitmap_2d_get_pixel_2\n\t"
      "pushl $1\n\t"
      "pushl $0x262\n\t"
      "pushl $0x264a74\n\t"
      "pushl $0x264334\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lbitmap_2d_get_pixel_2:\n\t"
      "testb $0x10, 0xe(%%esi)\n\t"
      "je .Lbitmap_2d_get_pixel_3\n\t"
      "pushl $1\n\t"
      "pushl $0x263\n\t"
      "pushl $0x264a74\n\t"
      "pushl $0x264f5c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lbitmap_2d_get_pixel_3:\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lbitmap_2d_get_pixel_4\n\t"
      "pushl $1\n\t"
      "pushl $0x264\n\t"
      "pushl $0x264a74\n\t"
      "pushl $0x25bb20\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lbitmap_2d_get_pixel_4:\n\t"
      "flds 0x10(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .Lbitmap_2d_get_pixel_5\n\t"
      "flds 0x10(%%ebp)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jnp .Lbitmap_2d_get_pixel_6\n\t"
      ".Lbitmap_2d_get_pixel_5:\n\t"
      "pushl $1\n\t"
      "pushl $0x265\n\t"
      "pushl $0x264a74\n\t"
      "pushl $0x264f44\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lbitmap_2d_get_pixel_6:\n\t"
      "movl 0x2c(%%esi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lbitmap_2d_get_pixel_26\n\t"
      "flds 0x10(%%ebp)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lbitmap_2d_get_pixel_8\n\t"
      "movw 0x14(%%esi), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "jle .Lbitmap_2d_get_pixel_8\n\t"
      "flds 0x2533c8\n\t"
      "movswl %%ax, %%eax\n\t"
      "fsubs 0x10(%%ebp)\n\t"
      "movl %%eax, 0x10(%%ebp)\n\t"
      "fimull 0x10(%%ebp)\n\t"
      "fstps 0x10(%%ebp)\n\t"
      "flds 0x10(%%ebp)\n\t"
      "fistps -0x20(%%ebp)\n\t"
      "movl -0x20(%%ebp), %%ebx\n\t"
      "testw %%bx, %%bx\n\t"
      "movl %%ebx, -0x10(%%ebp)\n\t"
      "jl .Lbitmap_2d_get_pixel_7\n\t"
      "cmpw 0x14(%%esi), %%bx\n\t"
      "jle .Lbitmap_2d_get_pixel_9\n\t"
      ".Lbitmap_2d_get_pixel_7:\n\t"
      "pushl $1\n\t"
      "pushl $0x26f\n\t"
      "pushl $0x264a74\n\t"
      "pushl $0x264bc4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "jmp .Lbitmap_2d_get_pixel_9\n\t"
      ".Lbitmap_2d_get_pixel_8:\n\t"
      "movl $0, -0x10(%%ebp)\n\t"
      "movl -0x10(%%ebp), %%ebx\n\t"
      ".Lbitmap_2d_get_pixel_9:\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "call *%[c7d6e0]\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl %%eax, %%edi\n\t"
      "movl %%edi, -0x24(%%ebp)\n\t"
      "call *%[c7d780]\n\t"
      "movswl %%di, %%ebx\n\t"
      "movl %%ebx, 0x10(%%ebp)\n\t"
      "leal -0x1(%%ebx), %%edx\n\t"
      "fildl 0x10(%%ebp)\n\t"
      "movl %%eax, %%ecx\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "addl $0x10, %%esp\n\t"
      "testl %%edx, %%ebx\n\t"
      "fsts -0xc(%%ebp)\n\t"
      "fmuls (%%eax)\n\t"
      "movl %%ecx, -0x1c(%%ebp)\n\t"
      "fsubs 0x253398\n\t"
      "fstps 0x10(%%ebp)\n\t"
      "jne .Lbitmap_2d_get_pixel_10\n\t"
      "flds 0x10(%%ebp)\n\t"
      "fistps -0x20(%%ebp)\n\t"
      "movl -0x20(%%ebp), %%edx\n\t"
      "decl %%edi\n\t"
      "andl %%edx, %%edi\n\t"
      "movl %%edi, 0x10(%%ebp)\n\t"
      "jmp .Lbitmap_2d_get_pixel_11\n\t"
      ".Lbitmap_2d_get_pixel_10:\n\t"
      "flds 0x10(%%ebp)\n\t"
      "fistps -0x20(%%ebp)\n\t"
      "movl -0x20(%%ebp), %%eax\n\t"
      "cdq\n\t"
      "idivl %%ebx\n\t"
      "movl %%edx, %%eax\n\t"
      "addl %%ebx, %%eax\n\t"
      "cdq\n\t"
      "idivl %%ebx\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "movl %%edx, 0x10(%%ebp)\n\t"
      ".Lbitmap_2d_get_pixel_11:\n\t"
      "movswl %%cx, %%ecx\n\t"
      "movl %%ecx, -0x14(%%ebp)\n\t"
      "leal -0x1(%%ecx), %%edx\n\t"
      "testl %%edx, %%ecx\n\t"
      "fildl -0x14(%%ebp)\n\t"
      "fsts -0x8(%%ebp)\n\t"
      "fmuls 0x4(%%eax)\n\t"
      "fsubs 0x253398\n\t"
      "fstps -0x20(%%ebp)\n\t"
      "jne .Lbitmap_2d_get_pixel_12\n\t"
      "flds -0x20(%%ebp)\n\t"
      "fistps -0x4(%%ebp)\n\t"
      "movl -0x1c(%%ebp), %%edi\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "decl %%edi\n\t"
      "andl %%eax, %%edi\n\t"
      "movl %%edi, -0x4(%%ebp)\n\t"
      "jmp .Lbitmap_2d_get_pixel_13\n\t"
      ".Lbitmap_2d_get_pixel_12:\n\t"
      "flds -0x20(%%ebp)\n\t"
      "fistps -0x4(%%ebp)\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "cdq\n\t"
      "idivl %%ecx\n\t"
      "movl %%edx, %%eax\n\t"
      "addl %%ecx, %%eax\n\t"
      "cdq\n\t"
      "idivl %%ecx\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      "movl %%edx, %%edi\n\t"
      ".Lbitmap_2d_get_pixel_13:\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[c7d000]\n\t"
      "movl %%eax, -0x20(%%ebp)\n\t"
      "movw 0xe(%%esi), %%ax\n\t"
      "addl $8, %%esp\n\t"
      "testb $2, %%al\n\t"
      "je .Lbitmap_2d_get_pixel_19\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0xc(%%esi), %%cx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c7c840]\n\t"
      "movswl %%ax, %%eax\n\t"
      "shll $4, %%eax\n\t"
      "cdq\n\t"
      "andl $7, %%edx\n\t"
      "addl %%edx, %%eax\n\t"
      "sarl $3, %%eax\n\t"
      "movswl %%ax, %%edi\n\t"
      "movswl -0x4(%%ebp), %%eax\n\t"
      "cdq\n\t"
      "andl $3, %%edx\n\t"
      "addl %%edx, %%eax\n\t"
      "sarl $2, %%eax\n\t"
      "movswl %%ax, %%eax\n\t"
      "imull %%ebx, %%eax\n\t"
      "cdq\n\t"
      "andl $3, %%edx\n\t"
      "addl %%edx, %%eax\n\t"
      "movl %%eax, %%ecx\n\t"
      "movswl 0x10(%%ebp), %%eax\n\t"
      "cdq\n\t"
      "andl $3, %%edx\n\t"
      "addl %%edx, %%eax\n\t"
      "sarl $2, %%eax\n\t"
      "movswl %%ax, %%edx\n\t"
      "movl -0x20(%%ebp), %%eax\n\t"
      "sarl $2, %%ecx\n\t"
      "addl %%edx, %%ecx\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "imull %%ecx, %%edi\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "addl %%eax, %%edi\n\t"
      "movl $3, %%eax\n\t"
      "andl %%eax, %%edx\n\t"
      "andl %%eax, %%ecx\n\t"
      "movl 0x2c(%%esi), %%eax\n\t"
      "addl $4, %%esp\n\t"
      "cmpl %%eax, %%edi\n\t"
      "movl %%edx, 0x10(%%ebp)\n\t"
      "movl %%ecx, -0x4(%%ebp)\n\t"
      "jae .Lbitmap_2d_get_pixel_14\n\t"
      "flds -0x8(%%ebp)\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "fmuls 0x4(%%eax)\n\t"
      "fsubs 0x253398\n\t"
      "fstps -0x20(%%ebp)\n\t"
      "flds -0x20(%%ebp)\n\t"
      "fistps -0x1c(%%ebp)\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fmuls (%%eax)\n\t"
      "fsubs 0x253398\n\t"
      "fstps -0x20(%%ebp)\n\t"
      "flds -0x20(%%ebp)\n\t"
      "fistps -0x24(%%ebp)\n\t"
      "movswl -0x10(%%ebp), %%eax\n\t"
      "pushl $1\n\t"
      "pushl $0x2a0\n\t"
      "pushl $0x264a74\n\t"
      "pushl %%eax\n\t"
      "movl -0x1c(%%ebp), %%eax\n\t"
      "cdq\n\t"
      "idivl -0x14(%%ebp)\n\t"
      "movl -0x24(%%ebp), %%eax\n\t"
      "movswl 0x14(%%esi), %%ecx\n\t"
      "pushl %%edx\n\t"
      "cdq\n\t"
      "idivl %%ebx\n\t"
      "movswl 0x4(%%esi), %%eax\n\t"
      "pushl %%edx\n\t"
      "movswl 0x6(%%esi), %%edx\n\t"
      "pushl %%ecx\n\t"
      "movl 0x2c(%%esi), %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "subl %%edi, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x264ec8\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x24, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lbitmap_2d_get_pixel_14:\n\t"
      "movl 0x2c(%%esi), %%edx\n\t"
      "addl 0x1c(%%esi), %%edx\n\t"
      "cmpl %%edx, %%edi\n\t"
      "jb .Lbitmap_2d_get_pixel_15\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fmuls 0x4(%%eax)\n\t"
      "fsubs 0x253398\n\t"
      "fstps 0xc(%%ebp)\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fistps -0x24(%%ebp)\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fmuls (%%eax)\n\t"
      "fsubs 0x253398\n\t"
      "fstps 0xc(%%ebp)\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fistps -0x20(%%ebp)\n\t"
      "movswl -0x10(%%ebp), %%eax\n\t"
      "pushl $1\n\t"
      "pushl $0x2a9\n\t"
      "pushl $0x264a74\n\t"
      "pushl %%eax\n\t"
      "movl -0x24(%%ebp), %%eax\n\t"
      "cdq\n\t"
      "idivl -0x14(%%ebp)\n\t"
      "movl -0x20(%%ebp), %%eax\n\t"
      "movswl 0x14(%%esi), %%ecx\n\t"
      "pushl %%edx\n\t"
      "cdq\n\t"
      "idivl %%ebx\n\t"
      "movswl 0x4(%%esi), %%eax\n\t"
      "movl 0x2c(%%esi), %%ebx\n\t"
      "pushl %%edx\n\t"
      "movswl 0x6(%%esi), %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "movl 0x1c(%%esi), %%edx\n\t"
      "movl %%edi, %%ecx\n\t"
      "pushl %%eax\n\t"
      "subl %%ebx, %%ecx\n\t"
      "subl %%edx, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x264e48\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x24, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lbitmap_2d_get_pixel_15:\n\t"
      "movswl 0xc(%%esi), %%eax\n\t"
      "subl $0xe, %%eax\n\t"
      "je .Lbitmap_2d_get_pixel_18\n\t"
      "decl %%eax\n\t"
      "je .Lbitmap_2d_get_pixel_17\n\t"
      "decl %%eax\n\t"
      "je .Lbitmap_2d_get_pixel_16\n\t"
      "pushl $1\n\t"
      "pushl $0x2b7\n\t"
      "pushl $0x264a74\n\t"
      "pushl $0x261888\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "addl $0x14, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lbitmap_2d_get_pixel_16:\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "leal 0x8(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edi\n\t"
      "call *%[c71af0]\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "addl $0x10, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lbitmap_2d_get_pixel_17:\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "leal 0x8(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edi\n\t"
      "call *%[c71840]\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "addl $0x10, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lbitmap_2d_get_pixel_18:\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "leal 0x8(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edi\n\t"
      "call *%[c715c0]\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "addl $0x10, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lbitmap_2d_get_pixel_19:\n\t"
      "testb $8, %%al\n\t"
      "je .Lbitmap_2d_get_pixel_24\n\t"
      "movl 0x10(%%ebp), %%ebx\n\t"
      "testw %%bx, %%bx\n\t"
      "jl .Lbitmap_2d_get_pixel_20\n\t"
      "cmpw $0x1000, %%bx\n\t"
      "jl .Lbitmap_2d_get_pixel_21\n\t"
      ".Lbitmap_2d_get_pixel_20:\n\t"
      "pushl $1\n\t"
      "pushl $0x2c1\n\t"
      "pushl $0x264a74\n\t"
      "pushl $0x264e34\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lbitmap_2d_get_pixel_21:\n\t"
      "testw %%di, %%di\n\t"
      "jl .Lbitmap_2d_get_pixel_22\n\t"
      "cmpw $0x1000, %%di\n\t"
      "jl .Lbitmap_2d_get_pixel_23\n\t"
      ".Lbitmap_2d_get_pixel_22:\n\t"
      "pushl $1\n\t"
      "pushl $0x2c2\n\t"
      "pushl $0x264a74\n\t"
      "pushl $0x264e24\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lbitmap_2d_get_pixel_23:\n\t"
      "movl -0x1c(%%ebp), %%eax\n\t"
      "movl -0x24(%%ebp), %%ecx\n\t"
      "leal -0x18(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c182690]\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "movl -0x18(%%ebp), %%ecx\n\t"
      "addl $0x14, %%esp\n\t"
      "orl %%ecx, %%eax\n\t"
      "jmp .Lbitmap_2d_get_pixel_25\n\t"
      ".Lbitmap_2d_get_pixel_24:\n\t"
      "movswl 0x10(%%ebp), %%edx\n\t"
      "movswl %%di, %%eax\n\t"
      "imull %%ebx, %%eax\n\t"
      "addl %%edx, %%eax\n\t"
      ".Lbitmap_2d_get_pixel_25:\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0xc(%%esi), %%cx\n\t"
      "pushl %%eax\n\t"
      "movl -0x20(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c7d0d0]\n\t"
      "addl $0xc, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lbitmap_2d_get_pixel_26:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "orl $0xffffffff, %%eax\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b7dad0_assert), [exitfn] "m"(b7dad0_exitfn), [c7d6e0] "m"(b7dad0_c7d6e0), [c7d780] "m"(b7dad0_c7d780), [c7d000] "m"(b7dad0_c7d000), [c7c840] "m"(b7dad0_c7c840), [c8d9d0] "m"(b7dad0_c8d9d0), [c71af0] "m"(b7dad0_c71af0), [c71840] "m"(b7dad0_c71840), [c715c0] "m"(b7dad0_c715c0), [c182690] "m"(b7dad0_c182690), [c7d0d0] "m"(b7dad0_c7d0d0)
      : "memory");
}
#else
#error "bitmap_2d_get_pixel: clang naked draft required"
#endif


/* bitmap_get_pixel_count (0x7dfe0) — readable C lift. */
int bitmap_get_pixel_count(void *bitmap)
{
  extern char DAT_00264da0[];
  extern char DAT_00264a74[];
  int total;
  int16_t i;
  int16_t count;

  if (!bitmap_verify(bitmap, 0)) {
    display_assert(DAT_00264da0, DAT_00264a74, 0x378, 1);
    system_exit(-1);
  }
  total = 0;
  count = *(int16_t *)((char *)bitmap + 0x14);
  if (count < 0)
    return 0;
  for (i = 0; i <= count; i++)
    total += bitmap_mipmap_get_pixel_count(bitmap, i);
  return total;
}

/* bitmap_get_pixel_data_size (0x7e040) — readable C lift. */
int bitmap_get_pixel_data_size(void *bitmap)
{
  extern char DAT_00264da0[];
  extern char DAT_00264a74[];
  int pixels;
  int bits;
  int bytes;

  if (!bitmap_verify(bitmap, 0)) {
    display_assert(DAT_00264da0, DAT_00264a74, 0x38a, 1);
    system_exit(-1);
  }
  pixels = bitmap_get_pixel_count(bitmap);
  bits = (int)(int16_t)bitmap_format_bits_per_pixel(*(int16_t *)((char *)bitmap + 0xc));
  bytes = bits * pixels;
  bytes = (bytes + ((bytes >> 31) & 7)) >> 3;
  return bytes;
}

/* 0x7e0b0 */
void *bitmap_2d_new(unsigned short width, unsigned short height, unsigned short mipmap_count, unsigned short format)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* test (int16_t)edi, (int16_t)edi -> jle 0x7e0c6 */
  /* cmp (int16_t)edi, 0x7530 -> jle 0x7e0e6 */
  display_assert((char *)0x00265030, (char *)0x00264a74, 181, 0);
  system_exit(0);
  /* test (int16_t)ebx, (int16_t)ebx -> jle 0x7e0f6 */
  /* cmp (int16_t)ebx, 0x7530 -> jle 0x7e116 */
  display_assert((char *)0x00264fe8, (char *)0x00264a74, 182, 0);
  system_exit(0);
  debug_malloc(48, 0, (char *)0x00264a74, 184);
  /* test esi, esi -> je 0x7e218 */
  csmemset((void *)(uintptr_t)esi, 0, 48);
  /* test eax, edx -> jne 0x7e18d */
  /* cmp (int16_t)ecx, 0xe -> jl 0x7e19d */
  /* cmp (int16_t)ecx, 0x10 -> jg 0x7e19d */
  /* cmp (int16_t)ecx, 0x11 -> jne 0x7e1a7 */
  bitmap_get_pixel_data_size((void *)(uintptr_t)esi);
  debug_malloc(eax, 0, (char *)0, 0);
  bitmap_verify((void *)(uintptr_t)esi, 0);
  /* test (char)eax, (char)eax -> jne 0x7e227 */
  display_assert((char *)0x00264da0, (char *)0x00264a74, 217, 0);
  system_exit(0);
  error(0, (char *)0x00264fb0);
  error(0, (char *)0x00264f8c);
  return NULL;

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x7e230 */
void *bitmap_3d_new(unsigned short width, unsigned short height, unsigned short depth, unsigned short mipmap_count, unsigned short format)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* test (int16_t)edi, (int16_t)edi -> jle 0x7e246 */
  /* cmp (int16_t)edi, 0x7530 -> jle 0x7e266 */
  display_assert((char *)0x002650f8, (char *)0x00264a74, 241, 0);
  system_exit(0);
  /* test (int16_t)eax, (int16_t)eax -> jle 0x7e275 */
  /* cmp (int16_t)eax, 0x7530 -> jle 0x7e295 */
  display_assert((char *)0x002650b0, (char *)0x00264a74, 242, 0);
  system_exit(0);
  /* test (int16_t)ebx, (int16_t)ebx -> jle 0x7e2a5 */
  /* cmp (int16_t)ebx, 0x100 -> jle 0x7e2c5 */
  display_assert((char *)0x00265070, (char *)0x00264a74, 243, 0);
  system_exit(0);
  debug_malloc(48, 0, (char *)0x00264a74, 245);
  /* test esi, esi -> je 0x7e3d3 */
  csmemset((void *)(uintptr_t)esi, 0, 48);
  /* test eax, edx -> jne 0x7e348 */
  /* test eax, edx -> jne 0x7e348 */
  /* cmp (int16_t)ecx, 0xe -> jl 0x7e358 */
  /* cmp (int16_t)ecx, 0x10 -> jg 0x7e358 */
  /* cmp (int16_t)ecx, 0x11 -> jne 0x7e362 */
  bitmap_get_pixel_data_size((void *)(uintptr_t)esi);
  debug_malloc(eax, 0, (char *)0, 0);
  bitmap_verify((void *)(uintptr_t)esi, 0);
  /* test (char)eax, (char)eax -> jne 0x7e3e2 */
  display_assert((char *)0x00264da0, (char *)0x00264a74, 278, 0);
  system_exit(0);
  error(0, (char *)0x00264fb0);
  error(0, (char *)0x00264f8c);
  return NULL;

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x7e3f0 */
void *bitmap_cube_map_new(unsigned short width, unsigned short mipmap_count, unsigned short format)
{
  int eax = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;

  /* test (int16_t)edi, (int16_t)edi -> jle 0x7e405 */
  /* cmp (int16_t)edi, 0x7530 -> jle 0x7e425 */
  display_assert((char *)0x00265150, (char *)0x00264a74, 300, 0);
  system_exit(0);
  /* test eax, ecx -> je 0x7e44f */
  display_assert((char *)0x00265138, (char *)0x00264a74, 301, 0);
  system_exit(0);
  debug_malloc(48, 0, (char *)0x00264a74, 303);
  /* test esi, esi -> je 0x7e53e */
  csmemset((void *)(uintptr_t)esi, 0, 48);
  /* cmp (int16_t)eax, 0x10 -> jg 0x7e4c5 */
  /* cmp (int16_t)eax, 0x11 -> jne 0x7e4cf */
  bitmap_get_pixel_data_size((void *)(uintptr_t)esi);
  debug_malloc(eax, 0, (char *)0, 0);
  bitmap_verify((void *)(uintptr_t)esi, 0);
  /* test (char)eax, (char)eax -> jne 0x7e54d */
  display_assert((char *)0x00264da0, (char *)0x00264a74, 337, 0);
  system_exit(0);
  error(0, (char *)0x00264fb0);
  error(0, (char *)0x00264f8c);
  return NULL;

  (void)eax;
  (void)ecx;
  (void)esi;
  (void)edi;
}

/* bitmap_3d_slice_insert (0x7e560) — XBE naked draft (batch 247). */
#if defined(__clang__)
static bool (*const b7e560_c7d470)(void *bitmap, int check_hardware) = bitmap_verify;
static void (*const b7e560_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b7e560_exitfn)(int) = system_exit;
static int (*const b7e560_c7e040)(void *bitmap_data) = bitmap_get_pixel_data_size;
static void * (*const b7e560_c7cb60)(void *bitmap, short x, short y, short face_index, short mipmap_index) = bitmap_3d_address;
static void * (*const b7e560_c7d000)(void *bitmap, short mipmap_index) = bitmap_mipmap_address;
static void * (*const b7e560_c8e0b0)(void *destination, void *source, size_t size) = csmemcpy;

__attribute__((naked, noinline))
void bitmap_3d_slice_insert(void *bitmap_3d __attribute__((unused)), int mipmap __attribute__((unused)), int slice __attribute__((unused)), void *bitmap_2d __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "pushl $0\n\t"
      "pushl %%edi\n\t"
      "call *%[c7d470]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lbitmap_3d_slice_insert_1\n\t"
      "pushl $1\n\t"
      "pushl $0x2e3\n\t"
      "pushl $0x264a74\n\t"
      "pushl $0x261b44\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lbitmap_3d_slice_insert_1:\n\t"
      "cmpw $1, 0xa(%%edi)\n\t"
      "je .Lbitmap_3d_slice_insert_2\n\t"
      "pushl $1\n\t"
      "pushl $0x2e4\n\t"
      "pushl $0x264a74\n\t"
      "pushl $0x26424c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lbitmap_3d_slice_insert_2:\n\t"
      "movl 0xc(%%ebp), %%ebx\n\t"
      "testw %%bx, %%bx\n\t"
      "jl .Lbitmap_3d_slice_insert_3\n\t"
      "cmpw 0x14(%%edi), %%bx\n\t"
      "jle .Lbitmap_3d_slice_insert_4\n\t"
      ".Lbitmap_3d_slice_insert_3:\n\t"
      "pushl $1\n\t"
      "pushl $0x2e5\n\t"
      "pushl $0x264a74\n\t"
      "pushl $0x261ac8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lbitmap_3d_slice_insert_4:\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "testw %%ax, %%ax\n\t"
      "jl .Lbitmap_3d_slice_insert_5\n\t"
      "cmpw 0x8(%%edi), %%ax\n\t"
      "jl .Lbitmap_3d_slice_insert_6\n\t"
      ".Lbitmap_3d_slice_insert_5:\n\t"
      "pushl $1\n\t"
      "pushl $0x2e6\n\t"
      "pushl $0x264a74\n\t"
      "pushl $0x265338\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lbitmap_3d_slice_insert_6:\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x4(%%edi), %%ax\n\t"
      "movw %%bx, %%cx\n\t"
      "movl %%eax, %%edx\n\t"
      "sarw %%cl, %%dx\n\t"
      "cmpw $1, %%dx\n\t"
      "jge .Lbitmap_3d_slice_insert_7\n\t"
      "movl $1, %%eax\n\t"
      "jmp .Lbitmap_3d_slice_insert_8\n\t"
      ".Lbitmap_3d_slice_insert_7:\n\t"
      "movswl %%ax, %%eax\n\t"
      "movb %%bl, %%cl\n\t"
      "sarl %%cl, %%eax\n\t"
      ".Lbitmap_3d_slice_insert_8:\n\t"
      "movl 0x14(%%ebp), %%ebx\n\t"
      "movswl 0x4(%%ebx), %%ecx\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "je .Lbitmap_3d_slice_insert_9\n\t"
      "pushl $1\n\t"
      "pushl $0x2e7\n\t"
      "pushl $0x264a74\n\t"
      "pushl $0x2652f0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lbitmap_3d_slice_insert_9:\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x6(%%edi), %%ax\n\t"
      "movw %%dx, %%cx\n\t"
      "movl %%eax, %%esi\n\t"
      "sarw %%cl, %%si\n\t"
      "cmpw $1, %%si\n\t"
      "jge .Lbitmap_3d_slice_insert_10\n\t"
      "movl $1, %%eax\n\t"
      "jmp .Lbitmap_3d_slice_insert_11\n\t"
      ".Lbitmap_3d_slice_insert_10:\n\t"
      "movswl %%ax, %%eax\n\t"
      "movb %%dl, %%cl\n\t"
      "sarl %%cl, %%eax\n\t"
      ".Lbitmap_3d_slice_insert_11:\n\t"
      "movswl 0x6(%%ebx), %%edx\n\t"
      "cmpl %%edx, %%eax\n\t"
      "je .Lbitmap_3d_slice_insert_12\n\t"
      "pushl $1\n\t"
      "pushl $0x2e8\n\t"
      "pushl $0x264a74\n\t"
      "pushl $0x2652a0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lbitmap_3d_slice_insert_12:\n\t"
      "testb $8, 0xe(%%edi)\n\t"
      "je .Lbitmap_3d_slice_insert_13\n\t"
      "pushl $1\n\t"
      "pushl $0x2e9\n\t"
      "pushl $0x264a74\n\t"
      "pushl $0x265264\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lbitmap_3d_slice_insert_13:\n\t"
      "pushl $0\n\t"
      "pushl %%ebx\n\t"
      "call *%[c7d470]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lbitmap_3d_slice_insert_14\n\t"
      "pushl $1\n\t"
      "pushl $0x2eb\n\t"
      "pushl $0x264a74\n\t"
      "pushl $0x265240\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lbitmap_3d_slice_insert_14:\n\t"
      "cmpw $0, 0x14(%%ebx)\n\t"
      "je .Lbitmap_3d_slice_insert_15\n\t"
      "pushl $1\n\t"
      "pushl $0x2ec\n\t"
      "pushl $0x264a74\n\t"
      "pushl $0x265220\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lbitmap_3d_slice_insert_15:\n\t"
      "cmpw $0, 0xa(%%ebx)\n\t"
      "je .Lbitmap_3d_slice_insert_16\n\t"
      "pushl $1\n\t"
      "pushl $0x2ed\n\t"
      "pushl $0x264a74\n\t"
      "pushl $0x2651fc\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lbitmap_3d_slice_insert_16:\n\t"
      "movw 0xc(%%ebx), %%ax\n\t"
      "cmpw 0xc(%%edi), %%ax\n\t"
      "je .Lbitmap_3d_slice_insert_17\n\t"
      "pushl $1\n\t"
      "pushl $0x2ee\n\t"
      "pushl $0x264a74\n\t"
      "pushl $0x2651d0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lbitmap_3d_slice_insert_17:\n\t"
      "testb $8, 0xe(%%ebx)\n\t"
      "je .Lbitmap_3d_slice_insert_18\n\t"
      "pushl $1\n\t"
      "pushl $0x2ef\n\t"
      "pushl $0x264a74\n\t"
      "pushl $0x265198\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lbitmap_3d_slice_insert_18:\n\t"
      "pushl %%ebx\n\t"
      "call *%[c7e040]\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl %%edi\n\t"
      "movl %%eax, %%esi\n\t"
      "call *%[c7cb60]\n\t"
      "pushl $0\n\t"
      "pushl %%ebx\n\t"
      "movl %%eax, %%edi\n\t"
      "call *%[c7d000]\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[c8e0b0]\n\t"
      "addl $0x2c, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c7d470] "m"(b7e560_c7d470), [assert] "m"(b7e560_assert), [exitfn] "m"(b7e560_exitfn), [c7e040] "m"(b7e560_c7e040), [c7cb60] "m"(b7e560_c7cb60), [c7d000] "m"(b7e560_c7d000), [c8e0b0] "m"(b7e560_c8e0b0)
      : "memory");
}
#else
#error "bitmap_3d_slice_insert: clang naked draft required"
#endif


/* bitmap_cube_map_face_extract (0x7e7e0) — XBE naked draft (batch 245). */
#if defined(__clang__)
static bool (*const b7e7e0_c7d470)(void *bitmap, int check_hardware) = bitmap_verify;
static void (*const b7e7e0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b7e7e0_exitfn)(int) = system_exit;
static int (*const b7e7e0_c7e040)(void *bitmap_data) = bitmap_get_pixel_data_size;
static void * (*const b7e7e0_c7cb60)(void *bitmap, short x, short y, short face_index, short mipmap_index) = bitmap_3d_address;
static void * (*const b7e7e0_c7d000)(void *bitmap, short mipmap_index) = bitmap_mipmap_address;
static void * (*const b7e7e0_c8e0b0)(void *destination, void *source, size_t size) = csmemcpy;

__attribute__((naked, noinline))
void bitmap_cube_map_face_extract(void *bitmap_2d __attribute__((unused)), void *bitmap_3d __attribute__((unused)), int mipmap __attribute__((unused)), int slice __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl $0\n\t"
      "pushl %%esi\n\t"
      "call *%[c7d470]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lbitmap_cube_map_face_extract_1\n\t"
      "pushl $1\n\t"
      "pushl $0x306\n\t"
      "pushl $0x264a74\n\t"
      "pushl $0x265240\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lbitmap_cube_map_face_extract_1:\n\t"
      "cmpw $0, 0x14(%%esi)\n\t"
      "je .Lbitmap_cube_map_face_extract_2\n\t"
      "pushl $1\n\t"
      "pushl $0x307\n\t"
      "pushl $0x264a74\n\t"
      "pushl $0x265220\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lbitmap_cube_map_face_extract_2:\n\t"
      "cmpw $0, 0xa(%%esi)\n\t"
      "je .Lbitmap_cube_map_face_extract_3\n\t"
      "pushl $1\n\t"
      "pushl $0x308\n\t"
      "pushl $0x264a74\n\t"
      "pushl $0x2651fc\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lbitmap_cube_map_face_extract_3:\n\t"
      "movw 0xc(%%esi), %%ax\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "cmpw 0xc(%%edi), %%ax\n\t"
      "je .Lbitmap_cube_map_face_extract_4\n\t"
      "pushl $1\n\t"
      "pushl $0x309\n\t"
      "pushl $0x264a74\n\t"
      "pushl $0x265480\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lbitmap_cube_map_face_extract_4:\n\t"
      "testb $8, 0xe(%%esi)\n\t"
      "je .Lbitmap_cube_map_face_extract_5\n\t"
      "pushl $1\n\t"
      "pushl $0x30a\n\t"
      "pushl $0x264a74\n\t"
      "pushl $0x265198\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lbitmap_cube_map_face_extract_5:\n\t"
      "pushl $0\n\t"
      "pushl %%edi\n\t"
      "call *%[c7d470]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lbitmap_cube_map_face_extract_6\n\t"
      "pushl $1\n\t"
      "pushl $0x30c\n\t"
      "pushl $0x264a74\n\t"
      "pushl $0x261974\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lbitmap_cube_map_face_extract_6:\n\t"
      "cmpw $1, 0xa(%%edi)\n\t"
      "je .Lbitmap_cube_map_face_extract_7\n\t"
      "pushl $1\n\t"
      "pushl $0x30d\n\t"
      "pushl $0x264a74\n\t"
      "pushl $0x264638\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lbitmap_cube_map_face_extract_7:\n\t"
      "movl 0x10(%%ebp), %%ebx\n\t"
      "testw %%bx, %%bx\n\t"
      "jl .Lbitmap_cube_map_face_extract_8\n\t"
      "cmpw 0x14(%%edi), %%bx\n\t"
      "jle .Lbitmap_cube_map_face_extract_9\n\t"
      ".Lbitmap_cube_map_face_extract_8:\n\t"
      "pushl $1\n\t"
      "pushl $0x30e\n\t"
      "pushl $0x264a74\n\t"
      "pushl $0x2618e8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lbitmap_cube_map_face_extract_9:\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "testw %%ax, %%ax\n\t"
      "jl .Lbitmap_cube_map_face_extract_10\n\t"
      "cmpw 0x8(%%edi), %%ax\n\t"
      "jl .Lbitmap_cube_map_face_extract_11\n\t"
      ".Lbitmap_cube_map_face_extract_10:\n\t"
      "pushl $1\n\t"
      "pushl $0x30f\n\t"
      "pushl $0x264a74\n\t"
      "pushl $0x265430\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lbitmap_cube_map_face_extract_11:\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x4(%%edi), %%ax\n\t"
      "movw %%bx, %%cx\n\t"
      "movl %%eax, %%edx\n\t"
      "sarw %%cl, %%dx\n\t"
      "cmpw $1, %%dx\n\t"
      "jge .Lbitmap_cube_map_face_extract_12\n\t"
      "movl $1, %%eax\n\t"
      "jmp .Lbitmap_cube_map_face_extract_13\n\t"
      ".Lbitmap_cube_map_face_extract_12:\n\t"
      "movswl %%ax, %%eax\n\t"
      "movb %%bl, %%cl\n\t"
      "sarl %%cl, %%eax\n\t"
      ".Lbitmap_cube_map_face_extract_13:\n\t"
      "movswl 0x4(%%esi), %%ecx\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "je .Lbitmap_cube_map_face_extract_14\n\t"
      "pushl $1\n\t"
      "pushl $0x310\n\t"
      "pushl $0x264a74\n\t"
      "pushl $0x2653d8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lbitmap_cube_map_face_extract_14:\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x6(%%edi), %%ax\n\t"
      "movw %%bx, %%cx\n\t"
      "movl %%eax, %%edx\n\t"
      "sarw %%cl, %%dx\n\t"
      "cmpw $1, %%dx\n\t"
      "jge .Lbitmap_cube_map_face_extract_15\n\t"
      "movl $1, %%eax\n\t"
      "jmp .Lbitmap_cube_map_face_extract_16\n\t"
      ".Lbitmap_cube_map_face_extract_15:\n\t"
      "movswl %%ax, %%eax\n\t"
      "movb %%bl, %%cl\n\t"
      "sarl %%cl, %%eax\n\t"
      ".Lbitmap_cube_map_face_extract_16:\n\t"
      "movswl 0x6(%%esi), %%ecx\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "je .Lbitmap_cube_map_face_extract_17\n\t"
      "pushl $1\n\t"
      "pushl $0x311\n\t"
      "pushl $0x264a74\n\t"
      "pushl $0x265380\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lbitmap_cube_map_face_extract_17:\n\t"
      "testb $8, 0xe(%%edi)\n\t"
      "je .Lbitmap_cube_map_face_extract_18\n\t"
      "pushl $1\n\t"
      "pushl $0x312\n\t"
      "pushl $0x264a74\n\t"
      "pushl $0x2618ac\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lbitmap_cube_map_face_extract_18:\n\t"
      "pushl %%esi\n\t"
      "call *%[c7e040]\n\t"
      "movl 0x14(%%ebp), %%edx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edx\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl %%edi\n\t"
      "movl %%eax, %%esi\n\t"
      "call *%[c7cb60]\n\t"
      "movl %%eax, %%edi\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "call *%[c7d000]\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "call *%[c8e0b0]\n\t"
      "addl $0x2c, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c7d470] "m"(b7e7e0_c7d470), [assert] "m"(b7e7e0_assert), [exitfn] "m"(b7e7e0_exitfn), [c7e040] "m"(b7e7e0_c7e040), [c7cb60] "m"(b7e7e0_c7cb60), [c7d000] "m"(b7e7e0_c7d000), [c8e0b0] "m"(b7e7e0_c8e0b0)
      : "memory");
}
#else
#error "bitmap_cube_map_face_extract: clang naked draft required"
#endif


/* FUN_0007ea60 (0x7ea60) — XBE naked draft (batch 247). */
#if defined(__clang__)
static bool (*const b7ea60_c7d470)(void *bitmap, int check_hardware) = bitmap_verify;
static void (*const b7ea60_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b7ea60_exitfn)(int) = system_exit;
static int (*const b7ea60_c7e040)(void *bitmap_data) = bitmap_get_pixel_data_size;
static void * (*const b7ea60_c7cdf0)(void *bitmap, short x, short y, short z, short mipmap_index) = bitmap_cube_map_address;
static void * (*const b7ea60_c7d000)(void *bitmap, short mipmap_index) = bitmap_mipmap_address;
static void * (*const b7ea60_c8e0b0)(void *destination, void *source, size_t size) = csmemcpy;

__attribute__((naked, noinline))
void FUN_0007ea60(void *bitmap_cube __attribute__((unused)), int mipmap __attribute__((unused)), int face __attribute__((unused)), void *bitmap_2d __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "pushl $0\n\t"
      "pushl %%edi\n\t"
      "call *%[c7d470]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_0007ea60_1\n\t"
      "pushl $1\n\t"
      "pushl $0x329\n\t"
      "pushl $0x264a74\n\t"
      "pushl $0x261b44\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0007ea60_1:\n\t"
      "cmpw $2, 0xa(%%edi)\n\t"
      "je .LFUN_0007ea60_2\n\t"
      "pushl $1\n\t"
      "pushl $0x32a\n\t"
      "pushl $0x264a74\n\t"
      "pushl $0x264274\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0007ea60_2:\n\t"
      "movl 0xc(%%ebp), %%ebx\n\t"
      "testw %%bx, %%bx\n\t"
      "jl .LFUN_0007ea60_3\n\t"
      "cmpw 0x14(%%edi), %%bx\n\t"
      "jle .LFUN_0007ea60_4\n\t"
      ".LFUN_0007ea60_3:\n\t"
      "pushl $1\n\t"
      "pushl $0x32b\n\t"
      "pushl $0x264a74\n\t"
      "pushl $0x261ac8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0007ea60_4:\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "testw %%ax, %%ax\n\t"
      "jl .LFUN_0007ea60_5\n\t"
      "cmpw $6, %%ax\n\t"
      "jl .LFUN_0007ea60_6\n\t"
      ".LFUN_0007ea60_5:\n\t"
      "pushl $1\n\t"
      "pushl $0x32c\n\t"
      "pushl $0x264a74\n\t"
      "pushl $0x265610\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0007ea60_6:\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x4(%%edi), %%ax\n\t"
      "movw %%bx, %%cx\n\t"
      "movl %%eax, %%edx\n\t"
      "sarw %%cl, %%dx\n\t"
      "cmpw $1, %%dx\n\t"
      "jge .LFUN_0007ea60_7\n\t"
      "movl $1, %%eax\n\t"
      "jmp .LFUN_0007ea60_8\n\t"
      ".LFUN_0007ea60_7:\n\t"
      "movswl %%ax, %%eax\n\t"
      "movb %%bl, %%cl\n\t"
      "sarl %%cl, %%eax\n\t"
      ".LFUN_0007ea60_8:\n\t"
      "movl 0x14(%%ebp), %%ebx\n\t"
      "movswl 0x4(%%ebx), %%ecx\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "je .LFUN_0007ea60_9\n\t"
      "pushl $1\n\t"
      "pushl $0x32d\n\t"
      "pushl $0x264a74\n\t"
      "pushl $0x2655c8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0007ea60_9:\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x6(%%edi), %%ax\n\t"
      "movw %%dx, %%cx\n\t"
      "movl %%eax, %%esi\n\t"
      "sarw %%cl, %%si\n\t"
      "cmpw $1, %%si\n\t"
      "jge .LFUN_0007ea60_10\n\t"
      "movl $1, %%eax\n\t"
      "jmp .LFUN_0007ea60_11\n\t"
      ".LFUN_0007ea60_10:\n\t"
      "movswl %%ax, %%eax\n\t"
      "movb %%dl, %%cl\n\t"
      "sarl %%cl, %%eax\n\t"
      ".LFUN_0007ea60_11:\n\t"
      "movswl 0x6(%%ebx), %%edx\n\t"
      "cmpl %%edx, %%eax\n\t"
      "je .LFUN_0007ea60_12\n\t"
      "pushl $1\n\t"
      "pushl $0x32e\n\t"
      "pushl $0x264a74\n\t"
      "pushl $0x265580\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0007ea60_12:\n\t"
      "testb $8, 0xe(%%edi)\n\t"
      "je .LFUN_0007ea60_13\n\t"
      "pushl $1\n\t"
      "pushl $0x32f\n\t"
      "pushl $0x264a74\n\t"
      "pushl $0x265264\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0007ea60_13:\n\t"
      "pushl $0\n\t"
      "pushl %%ebx\n\t"
      "call *%[c7d470]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_0007ea60_14\n\t"
      "pushl $1\n\t"
      "pushl $0x331\n\t"
      "pushl $0x264a74\n\t"
      "pushl $0x26555c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0007ea60_14:\n\t"
      "cmpw $0, 0x14(%%ebx)\n\t"
      "je .LFUN_0007ea60_15\n\t"
      "pushl $1\n\t"
      "pushl $0x332\n\t"
      "pushl $0x264a74\n\t"
      "pushl $0x26553c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0007ea60_15:\n\t"
      "cmpw $0, 0xa(%%ebx)\n\t"
      "je .LFUN_0007ea60_16\n\t"
      "pushl $1\n\t"
      "pushl $0x333\n\t"
      "pushl $0x264a74\n\t"
      "pushl $0x265518\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0007ea60_16:\n\t"
      "movw 0xc(%%ebx), %%ax\n\t"
      "cmpw 0xc(%%edi), %%ax\n\t"
      "je .LFUN_0007ea60_17\n\t"
      "pushl $1\n\t"
      "pushl $0x334\n\t"
      "pushl $0x264a74\n\t"
      "pushl $0x2654ec\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0007ea60_17:\n\t"
      "testb $8, 0xe(%%ebx)\n\t"
      "je .LFUN_0007ea60_18\n\t"
      "pushl $1\n\t"
      "pushl $0x335\n\t"
      "pushl $0x264a74\n\t"
      "pushl $0x2654b4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0007ea60_18:\n\t"
      "pushl %%ebx\n\t"
      "call *%[c7e040]\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl %%edi\n\t"
      "movl %%eax, %%esi\n\t"
      "call *%[c7cdf0]\n\t"
      "pushl $0\n\t"
      "pushl %%ebx\n\t"
      "movl %%eax, %%edi\n\t"
      "call *%[c7d000]\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[c8e0b0]\n\t"
      "addl $0x2c, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c7d470] "m"(b7ea60_c7d470), [assert] "m"(b7ea60_assert), [exitfn] "m"(b7ea60_exitfn), [c7e040] "m"(b7ea60_c7e040), [c7cdf0] "m"(b7ea60_c7cdf0), [c7d000] "m"(b7ea60_c7d000), [c8e0b0] "m"(b7ea60_c8e0b0)
      : "memory");
}
#else
#error "FUN_0007ea60: clang naked draft required"
#endif

/* --- bitmaps.obj orphan shells (2026-07-26) --- */

/* FUN_0007ba50 (0x7ba50) — XBE naked draft (batch 247). */
#if defined(__clang__)
static bool (*const b7ba50_c7d470)(void *bitmap, int check_hardware) = bitmap_verify;
static void (*const b7ba50_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b7ba50_exitfn)(int) = system_exit;
static int (*const b7ba50_c7e040)(void *bitmap_data) = bitmap_get_pixel_data_size;
static void * (*const b7ba50_c8ee60)(uint32_t size, bool zero, const char *file, int line) = debug_malloc;
static void * (*const b7ba50_c7c940)(void *bitmap, short x, short y, short mipmap_index) = bitmap_2d_address;
static void * (*const b7ba50_c7d000)(void *bitmap, short mipmap_index) = bitmap_mipmap_address;
static void * (*const b7ba50_c8e0b0)(void *destination, void *source, size_t size) = csmemcpy;
static void (*const b7ba50_c8ef70)(void *ptr, const char *file, int line) = debug_free;
static void (*const b7ba50_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;

__attribute__((naked, noinline))
void FUN_0007ba50(void *bitmap __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x24, %%esp\n\t"
      "pushl $1\n\t"
      "pushl %%edi\n\t"
      "call *%[c7d470]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_0007ba50_1\n\t"
      "pushl $1\n\t"
      "pushl $0x583\n\t"
      "pushl $0x2641f0\n\t"
      "pushl $0x261814\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0007ba50_1:\n\t"
      "cmpw $0, 0xa(%%edi)\n\t"
      "je .LFUN_0007ba50_2\n\t"
      "pushl $1\n\t"
      "pushl $0x584\n\t"
      "pushl $0x2641f0\n\t"
      "pushl $0x264334\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0007ba50_2:\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c7e040]\n\t"
      "pushl $0x587\n\t"
      "pushl $0x2641f0\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "movl %%eax, -0x18(%%ebp)\n\t"
      "call *%[c8ee60]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $0x14, %%esp\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%esi, -0x4(%%ebp)\n\t"
      "je .LFUN_0007ba50_12\n\t"
      "pushl %%ebx\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "cmpw %%bx, 0x6(%%edi)\n\t"
      "jle .LFUN_0007ba50_11\n\t"
      "jmp .LFUN_0007ba50_3\n\t"
      "leal (%%esp), %%esp\n\t"
      "movl %%edi, %%edi\n\t"
      ".LFUN_0007ba50_3:\n\t"
      "xorl %%esi, %%esi\n\t"
      "cmpw %%si, 0x4(%%edi)\n\t"
      "jle .LFUN_0007ba50_10\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_0007ba50_4:\n\t"
      "pushl $0\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c7c940]\n\t"
      "movl (%%eax), %%ecx\n\t"
      "movl %%ecx, %%eax\n\t"
      "shrl $0x10, %%eax\n\t"
      "andl $0xff, %%eax\n\t"
      "addl $0x10, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "fildl -0x8(%%ebp)\n\t"
      "jge .LFUN_0007ba50_5\n\t"
      "fadds 0x25fb8c\n\t"
      ".LFUN_0007ba50_5:\n\t"
      "fmuls 0x26486c\n\t"
      "movl %%ecx, %%edx\n\t"
      "shrl $8, %%edx\n\t"
      "andl $0xff, %%edx\n\t"
      "testl %%edx, %%edx\n\t"
      "fsubs 0x2533c8\n\t"
      "movl %%edx, -0x8(%%ebp)\n\t"
      "fildl -0x8(%%ebp)\n\t"
      "jge .LFUN_0007ba50_6\n\t"
      "fadds 0x25fb8c\n\t"
      ".LFUN_0007ba50_6:\n\t"
      "fmuls 0x26486c\n\t"
      "movl %%ecx, %%eax\n\t"
      "andl $0xff, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "fsubs 0x2533c8\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "fstps -0x20(%%ebp)\n\t"
      "fildl -0x8(%%ebp)\n\t"
      "jge .LFUN_0007ba50_7\n\t"
      "fadds 0x25fb8c\n\t"
      ".LFUN_0007ba50_7:\n\t"
      "fmuls 0x26486c\n\t"
      "fsubs 0x2533c8\n\t"
      "fsts -0x1c(%%ebp)\n\t"
      "fmuls -0x1c(%%ebp)\n\t"
      "flds -0x20(%%ebp)\n\t"
      "fmuls -0x20(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fld %%st(1)\n\t"
      "fmul %%st(2), %%st(0)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fsqrt\n\t"
      "fld %%st(0)\n\t"
      "fabs\n\t"
      "fcompl 0x2533d0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .LFUN_0007ba50_8\n\t"
      "fdivrs 0x2533c8\n\t"
      "fld %%st(0)\n\t"
      ".byte 0xde, 0xca\n\t"
      "flds -0x20(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fstps -0x20(%%ebp)\n\t"
      "fmuls -0x1c(%%ebp)\n\t"
      "fstps -0x1c(%%ebp)\n\t"
      "jmp .LFUN_0007ba50_9\n\t"
      ".LFUN_0007ba50_8:\n\t"
      "fstp %%st(0)\n\t"
      ".LFUN_0007ba50_9:\n\t"
      "fadds 0x2533c8\n\t"
      "fmuls 0x264868\n\t"
      "fadds 0x253398\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fistps -0xc(%%ebp)\n\t"
      "flds -0x20(%%ebp)\n\t"
      "fadds 0x2533c8\n\t"
      "fmuls 0x264868\n\t"
      "fadds 0x253398\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fistps -0x10(%%ebp)\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fadds 0x2533c8\n\t"
      "fmuls 0x264868\n\t"
      "fadds 0x253398\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fistps -0x14(%%ebp)\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "shll $8, %%edx\n\t"
      "orl %%eax, %%edx\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "andl $0xff000000, %%ecx\n\t"
      "shll $8, %%edx\n\t"
      "orl %%ecx, %%edx\n\t"
      "movswl 0x4(%%edi), %%ecx\n\t"
      "orl %%eax, %%edx\n\t"
      "movswl %%bx, %%eax\n\t"
      "imull %%eax, %%ecx\n\t"
      "movswl %%si, %%eax\n\t"
      "addl %%eax, %%ecx\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "incl %%esi\n\t"
      "movl %%edx, (%%eax,%%ecx,4)\n\t"
      "cmpw 0x4(%%edi), %%si\n\t"
      "jl .LFUN_0007ba50_4\n\t"
      ".LFUN_0007ba50_10:\n\t"
      "incl %%ebx\n\t"
      "cmpw 0x6(%%edi), %%bx\n\t"
      "jl .LFUN_0007ba50_3\n\t"
      "movl -0x4(%%ebp), %%esi\n\t"
      ".LFUN_0007ba50_11:\n\t"
      "movl -0x18(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl $0\n\t"
      "pushl %%edi\n\t"
      "call *%[c7d000]\n\t"
      "addl $8, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[c8e0b0]\n\t"
      "pushl $0x5a8\n\t"
      "pushl $0x2641f0\n\t"
      "pushl %%esi\n\t"
      "call *%[c8ef70]\n\t"
      "addl $0x18, %%esp\n\t"
      "popl %%ebx\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0007ba50_12:\n\t"
      "pushl $0x2642f0\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c7d470] "m"(b7ba50_c7d470), [assert] "m"(b7ba50_assert), [exitfn] "m"(b7ba50_exitfn), [c7e040] "m"(b7ba50_c7e040), [c8ee60] "m"(b7ba50_c8ee60), [c7c940] "m"(b7ba50_c7c940), [c7d000] "m"(b7ba50_c7d000), [c8e0b0] "m"(b7ba50_c8e0b0), [c8ef70] "m"(b7ba50_c8ef70), [c8f390] "m"(b7ba50_c8f390)
      : "memory");
}
#else
#error "FUN_0007ba50: clang naked draft required"
#endif


/* FUN_0007bcb0 (0x7bcb0) — 3D bitmap hardware-upload helper.
 *
 * Verifies bitmap (@esi) is type 3D, allocates a temporary 2D bitmap matching
 * width/height/format, then for each depth slice: copy slice into the temp,
 * run the 2D upload helper (FUN_0007ba50 via EDI), copy back. Deletes the temp.
 * Source: c:\halo\SOURCE\bitmaps\bitmap_utilities.c, lines 0x5b7-0x5b8.
 */
void FUN_0007bcb0(void *bitmap /* @<esi> */)
{
  void *temp;
  int slice;
  short depth;

  if (!bitmap_verify(bitmap, 1)) {
    display_assert("bitmap_verify(bitmap, TRUE)",
                   "c:\\halo\\SOURCE\\bitmaps\\bitmap_utilities.c", 0x5b7, 1);
    system_exit(-1);
  }
  if (*(short *)((char *)bitmap + 0xa) != 1) {
    display_assert("bitmap->type==_bitmap_type_3d",
                   "c:\\halo\\SOURCE\\bitmaps\\bitmap_utilities.c", 0x5b8, 1);
    system_exit(-1);
  }

  temp = bitmap_2d_new(*(unsigned short *)((char *)bitmap + 4),
                       *(unsigned short *)((char *)bitmap + 6), 0,
                       *(unsigned short *)((char *)bitmap + 0xc));
  if (temp == 0 || *(void **)((char *)temp + 0x2c) == 0) {
    error(2, "### ERROR failed to allocate temporary bitmap");
    bitmap_delete(temp);
    return;
  }

  depth = *(short *)((char *)bitmap + 8);
  if (depth > 0) {
    for (slice = 0; slice < depth; slice++) {
      bitmap_3d_slice_insert(bitmap, 0, slice, temp);
      FUN_0007ba50(temp);
      bitmap_cube_map_face_extract(temp, bitmap, 0, slice);
    }
  }
  bitmap_delete(temp);
}


/* FUN_0007bd90 (0x7bd90) — cube-map bitmap hardware-upload helper.
 *
 * Verifies bitmap (@ebx) is type cube_map, allocates a temporary 2D bitmap,
 * then for each of 6 faces: FUN_0007ea60 into temp, FUN_0007ba50 (@edi),
 * bitmap_cube_map_face_insert back. Deletes the temp.
 * Source: c:\halo\SOURCE\bitmaps\bitmap_utilities.c, lines 0x5e5-0x5e6.
 */
void FUN_0007bd90(void *bitmap /* @<ebx> */)
{
  void *temp;
  int face;

  if (!bitmap_verify(bitmap, 1)) {
    display_assert("bitmap_verify(bitmap, TRUE)",
                   "c:\\halo\\SOURCE\\bitmaps\\bitmap_utilities.c", 0x5e5, 1);
    system_exit(-1);
  }
  if (*(short *)((char *)bitmap + 0xa) != 2) {
    display_assert("bitmap->type==_bitmap_type_cube_map",
                   "c:\\halo\\SOURCE\\bitmaps\\bitmap_utilities.c", 0x5e6, 1);
    system_exit(-1);
  }

  temp = bitmap_2d_new(*(unsigned short *)((char *)bitmap + 4),
                       *(unsigned short *)((char *)bitmap + 6), 0,
                       *(unsigned short *)((char *)bitmap + 0xc));
  if (temp == 0 || *(void **)((char *)temp + 0x2c) == 0) {
    error(2, "### ERROR failed to allocate temporary bitmap");
    bitmap_delete(temp);
    return;
  }

  for (face = 0; face < 6; face++) {
    FUN_0007ea60(bitmap, 0, face, temp);
    FUN_0007ba50(temp);
    bitmap_cube_map_face_insert(temp, bitmap, 0, face);
  }
  bitmap_delete(temp);
}


/* orphan 0x7cb60 */
void *bitmap_3d_address(void *bitmap, short x, short y, short face_index, short mipmap_index)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  display_assert((char *)0x00263768, (char *)0x00264a74, 455, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x7cbbe */
  display_assert((char *)0x00264c30, (char *)0x00264a74, 456, 0);
  system_exit(0);
  /* relift: cmp word ptr [ebx + 0xa], 1 -> je 0x7cbe5 */
  display_assert((char *)0x00264354, (char *)0x00264a74, 457, 0);
  system_exit(0);
  /* test (int16_t)eax, (int16_t)eax -> jl 0x7cbf4 */
  /* relift: cmp (int16_t)eax, word ptr [ebx + 4] -> jl 0x7cc14 */
  display_assert((char *)0x00264c18, (char *)0x00264a74, 458, 0);
  system_exit(0);
  /* test (int16_t)edi, (int16_t)edi -> jl 0x7cc23 */
  /* relift: cmp (int16_t)edi, word ptr [ebx + 6] -> jl 0x7cc43 */
  display_assert((char *)0x00264bfc, (char *)0x00264a74, 459, 0);
  system_exit(0);
  /* test (int16_t)esi, (int16_t)esi -> jl 0x7cc52 */
  /* relift: cmp (int16_t)esi, word ptr [ebx + 8] -> jl 0x7cc72 */
  display_assert((char *)0x00264ce4, (char *)0x00264a74, 460, 0);
  system_exit(0);
  /* test (int16_t)eax, (int16_t)eax -> jl 0x7cc81 */
  /* relift: cmp (int16_t)eax, word ptr [ebx + 0x14] -> jle 0x7cca1 */
  display_assert((char *)0x00264bc4, (char *)0x00264a74, 461, 0);
  system_exit(0);
  /* relift: test byte ptr [ebx + 0xe], 2 -> je 0x7ccd8 */
  /* relift: cmp word ptr [ebp + 0xc], 0 -> jne 0x7ccb8 */
  /* test (int16_t)edi, (int16_t)edi -> jne 0x7ccb8 */
  /* test (int16_t)esi, (int16_t)esi -> je 0x7ccd8 */
  display_assert((char *)0x00264c98, (char *)0x00264a74, 462, 0);
  system_exit(0);
  /* relift: test byte ptr [ebx + 0xe], 8 -> je 0x7cd0f */
  /* relift: cmp word ptr [ebp + 0xc], 0 -> jne 0x7ccef */
  /* test (int16_t)edi, (int16_t)edi -> jne 0x7ccef */
  /* test (int16_t)esi, (int16_t)esi -> je 0x7cd0f */
  display_assert((char *)0x00264c48, (char *)0x00264a74, 463, 0);
  system_exit(0);
  bitmap_format_bits_per_pixel(0);
  /* test (int16_t)eax, (int16_t)eax -> jle 0x7cdac */
  /* cmp (int16_t)ecx, (int16_t)esi -> jle 0x7cd7d */
  /* cmp (int16_t)ecx, (int16_t)edi -> jle 0x7cd8d */
  /* cmp (int16_t)ebx, 2 -> jge 0x7cda2 */
  return NULL;

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* orphan 0x7cdf0 */
void *bitmap_cube_map_address(void *bitmap, short x, short y, short z, short mipmap_index)
{
  int eax = 0;
  int ebx = 0;
  int esi = 0;
  int edi = 0;

  display_assert((char *)0x00263768, (char *)0x00264a74, 496, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x7ce4c */
  display_assert((char *)0x00264c30, (char *)0x00264a74, 497, 0);
  system_exit(0);
  /* relift: cmp word ptr [ebx + 0xa], 2 -> je 0x7ce73 */
  display_assert((char *)0x0026439c, (char *)0x00264a74, 498, 0);
  system_exit(0);
  /* test (int16_t)edi, (int16_t)edi -> jl 0x7ce82 */
  /* relift: cmp (int16_t)edi, word ptr [ebx + 4] -> jl 0x7cea2 */
  display_assert((char *)0x00264c18, (char *)0x00264a74, 499, 0);
  system_exit(0);
  /* test (int16_t)esi, (int16_t)esi -> jl 0x7ceb1 */
  /* relift: cmp (int16_t)esi, word ptr [ebx + 6] -> jl 0x7ced1 */
  display_assert((char *)0x00264bfc, (char *)0x00264a74, 500, 0);
  system_exit(0);
  /* test (int16_t)eax, (int16_t)eax -> jl 0x7cee0 */
  /* relift: cmp (int16_t)eax, word ptr [ebx + 0x14] -> jle 0x7cf00 */
  display_assert((char *)0x00264bc4, (char *)0x00264a74, 501, 0);
  system_exit(0);
  /* relift: test byte ptr [ebx + 0xe], 2 -> je 0x7cf30 */
  /* test (int16_t)edi, (int16_t)edi -> jne 0x7cf10 */
  /* test (int16_t)esi, (int16_t)esi -> je 0x7cf30 */
  display_assert((char *)0x00264b80, (char *)0x00264a74, 502, 0);
  system_exit(0);
  /* relift: test byte ptr [ebx + 0xe], 8 -> je 0x7cf60 */
  /* test (int16_t)edi, (int16_t)edi -> jne 0x7cf40 */
  /* test (int16_t)esi, (int16_t)esi -> je 0x7cf60 */
  display_assert((char *)0x00264b38, (char *)0x00264a74, 503, 0);
  system_exit(0);
  bitmap_format_bits_per_pixel(0);
  return NULL;

  (void)eax;
  (void)ebx;
  (void)esi;
  (void)edi;
}
