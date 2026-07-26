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
bool bitmap_validate_depth(int depth /* @<eax> */, int format, int type)
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

/* 0x7be60 */
void bitmap_compress_to_mipmap(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  bitmap_verify((void *)(uintptr_t)edi, 0);
  /* test (char)eax, (char)eax -> jne 0x7be98 */
  display_assert((char *)0x00261aa4, (char *)0x002641f0, 1561, 0);
  system_exit(0);
  bitmap_verify((void *)(uintptr_t)esi, 0);
  /* test (char)eax, (char)eax -> jne 0x7beca */
  display_assert((char *)0x00261974, (char *)0x002641f0, 1563, 0);
  system_exit(0);
  /* test (int16_t)ebx, (int16_t)ebx -> jl 0x7bed8 */
  /* relift: cmp (int16_t)ebx, word ptr [esi + 0x14] -> jle 0x7bef8 */
  display_assert((char *)0x002618e8, (char *)0x002641f0, 1564, 0);
  system_exit(0);
  /* cmp (int16_t)edx, 1 -> jge 0x7bf13 */
  /* cmp eax, ecx -> je 0x7bf42 */
  display_assert((char *)0x002645b8, (char *)0x002641f0, 1565, 0);
  system_exit(0);
  /* cmp (int16_t)edx, 1 -> jge 0x7bf5d */
  /* cmp eax, ecx -> je 0x7bf8c */
  display_assert((char *)0x00264560, (char *)0x002641f0, 1566, 0);
  system_exit(0);
  /* cmp (int16_t)edx, 1 -> jge 0x7bfa7 */
  /* cmp eax, ecx -> je 0x7bfd6 */
  display_assert((char *)0x00264508, (char *)0x002641f0, 1567, 0);
  system_exit(0);
  /* relift: test byte ptr [esi + 0xe], 2 -> jne 0x7bffc */
  display_assert((char *)0x002644c4, (char *)0x002641f0, 1568, 0);
  system_exit(0);
  display_assert((char *)0x00261d30, (char *)0x002641f0, 1584, 0);
  system_exit(0);
  FUN_00079bb0();
  FUN_000798e0();
  FUN_000796e0();

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x7c070 */
void bitmap_3d_compress_to_mipmap(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  bitmap_verify((void *)(uintptr_t)esi, 0);
  /* test (char)eax, (char)eax -> jne 0x7c0a8 */
  display_assert((char *)0x00261b44, (char *)0x002641f0, 1862, 0);
  system_exit(0);
  /* test (int16_t)ebx, (int16_t)ebx -> jl 0x7c0b6 */
  /* relift: cmp (int16_t)ebx, word ptr [esi + 0x14] -> jle 0x7c0d6 */
  display_assert((char *)0x00261ac8, (char *)0x002641f0, 1863, 0);
  system_exit(0);
  /* cmp (int16_t)edx, 1 -> jge 0x7c0f1 */
  /* cmp eax, ecx -> je 0x7c123 */
  display_assert((char *)0x00264770, (char *)0x002641f0, 1864, 0);
  system_exit(0);
  /* cmp (int16_t)edx, 1 -> jge 0x7c13e */
  /* cmp eax, ecx -> je 0x7c16d */
  display_assert((char *)0x00264720, (char *)0x002641f0, 1865, 0);
  system_exit(0);
  /* cmp (int16_t)edx, 1 -> jge 0x7c188 */
  /* cmp eax, ecx -> je 0x7c1b7 */
  display_assert((char *)0x002646d0, (char *)0x002641f0, 1866, 0);
  system_exit(0);
  /* relift: test byte ptr [esi + 0xe], 2 -> jne 0x7c1dd */
  display_assert((char *)0x00264694, (char *)0x002641f0, 1867, 0);
  system_exit(0);
  bitmap_verify((void *)(uintptr_t)edi, 0);
  /* test (char)eax, (char)eax -> jne 0x7c20c */
  display_assert((char *)0x00261c58, (char *)0x002641f0, 1869, 0);
  system_exit(0);
  display_assert((char *)0x00261d30, (char *)0x002641f0, 1883, 0);
  system_exit(0);
  bitmap_2d_uncompress_from_mipmap();
  FUN_0007a1e0();
  FUN_00079e70();

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x7c490 */
void FUN_0007c490(void)
{
  int eax = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  FUN_0007c270((float *)(uintptr_t)esi, eax, (float *)(uintptr_t)edx, (float *)0, 0.0f);
  /* test edi, edi -> je 0x7c593 */
  valid_real_rgb_color((float *)(uintptr_t)edi);
  /* test (char)eax, (char)eax -> jne 0x7c519 */
  csprintf((char *)0x005ab100, (char *)0x0026488c);
  display_assert((char *)(uintptr_t)eax, (char *)0, 0, 0);
  system_exit(0);
  /* test (char)eax, 0x41 -> je 0x7c551 */
  /* test (char)eax, 0x41 -> je 0x7c551 */
  valid_real_rgb_color((float *)(uintptr_t)esi);
  /* test (char)eax, (char)eax -> jne 0x7c5e9 */
  csprintf((char *)0x005ab100, (char *)0x0026488c);
  display_assert((char *)(uintptr_t)eax, (char *)0, 0, 0);
  system_exit(0);

  (void)eax;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x7d0d0 */
void bitmap_format_to_a8r8g8b8(void)
{
  int eax = 0;
  int esi = 0;

  /* test esi, esi -> jne 0x7d0fb */
  display_assert((char *)0x00264cfc, (char *)0x00264a74, 555, 0);
  system_exit(0);
  /* cmp eax, 0x11 -> ja 0x7d287 */
  display_assert((char *)0x00261888, (char *)0x00264a74, 596, 0);
  system_exit(0);

  (void)eax;
  (void)esi;
}

/* 0x7d300 */
void palette_find_closest_match(void)
{
  int eax = 0;
  int ecx = 0;
  int ebp = 0;

  /* test (int16_t)ecx, (int16_t)ecx -> je 0x7d3ad */
  /* relift: cmp dword ptr [ebp - 8], eax -> jle 0x7d3b3 */
  display_assert((char *)0x00264d0c, (char *)0x00264a74, 1101, 0);
  system_exit(0);
  /* test (int16_t)eax, (int16_t)eax -> jle 0x7d411 */
  /* cmp (int16_t)eax, 0x7530 -> jg 0x7d411 */
  /* test (int16_t)eax, (int16_t)eax -> jle 0x7d431 */
  /* cmp (int16_t)eax, 0x7530 -> jg 0x7d431 */

  (void)eax;
  (void)ecx;
  (void)ebp;
}

/* 0x7dad0 */
unsigned int bitmap_2d_get_pixel(int bitmap_ref, float *uv, float level, float *out)
{
  int eax = 0;
  int ebx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  display_assert((char *)0x00263768, (char *)0x00264a74, 609, 0);
  system_exit(0);
  /* relift: cmp word ptr [esi + 0xa], 0 -> je 0x7db27 */
  display_assert((char *)0x00264334, (char *)0x00264a74, 610, 0);
  system_exit(0);
  /* relift: test byte ptr [esi + 0xe], 0x10 -> je 0x7db4d */
  display_assert((char *)0x00264f5c, (char *)0x00264a74, 611, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x7db74 */
  display_assert((char *)0x0025bb20, (char *)0x00264a74, 612, 0);
  system_exit(0);
  /* test (char)eax, 1 -> jne 0x7db94 */
  display_assert((char *)0x00264f44, (char *)0x00264a74, 613, 0);
  system_exit(0);
  /* test eax, eax -> je 0x7dfcd */
  /* test (int16_t)eax, (int16_t)eax -> jle 0x7dc26 */
  /* relift: cmp (int16_t)ebx, word ptr [esi + 0x14] -> jle 0x7dc30 */
  display_assert((char *)0x00264bc4, (char *)0x00264a74, 623, 0);
  system_exit(0);
  bitmap_mipmap_width((void *)(uintptr_t)esi, 0);
  bitmap_mipmap_get_height((void *)(uintptr_t)esi, 0);
  bitmap_mipmap_address((void *)(uintptr_t)esi, 0);
  /* test (char)eax, 2 -> je 0x7df27 */
  bitmap_format_bits_per_pixel(0);
  csprintf((char *)0x005ab100, (char *)0x00264ec8);
  display_assert((char *)(uintptr_t)eax, (char *)0, 0, 0);
  system_exit(0);
  /* cmp edi, edx -> jb 0x7de91 */
  csprintf((char *)0x005ab100, (char *)0x00264e48);
  display_assert((char *)(uintptr_t)eax, (char *)0, 0, 0);
  system_exit(0);
  display_assert((char *)0x00261888, (char *)0x00264a74, 695, 0);
  system_exit(0);
  FUN_00071af0();
  FUN_00071840();
  DecodeBlockRGB__single_pixel();
  /* test (char)eax, 8 -> je 0x7dfa6 */
  /* test (int16_t)ebx, (int16_t)ebx -> jl 0x7df3a */
  /* cmp (int16_t)ebx, 0x1000 -> jl 0x7df5a */
  display_assert((char *)0x00264e34, (char *)0x00264a74, 705, 0);
  system_exit(0);
  /* test (int16_t)edi, (int16_t)edi -> jl 0x7df66 */
  /* cmp (int16_t)edi, 0x1000 -> jl 0x7df86 */
  display_assert((char *)0x00264e24, (char *)0x00264a74, 706, 0);
  system_exit(0);
  rasterizer_swizzle_compute_masks(0, 0, 0, 0, (void *)(uintptr_t)edx);
  bitmap_format_to_a8r8g8b8();
  return 0;

  (void)eax;
  (void)ebx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x7dfe0 */
int bitmap_get_pixel_count(void *bitmap)
{
  int eax = 0;
  int esi = 0;
  int edi = 0;

  bitmap_verify((void *)(uintptr_t)edi, 0);
  /* test (char)eax, (char)eax -> jne 0x7e019 */
  display_assert((char *)0x00264da0, (char *)0x00264a74, 888, 0);
  system_exit(0);
  /* relift: cmp word ptr [edi + 0x14], (int16_t)esi -> jl 0x7e034 */
  bitmap_mipmap_get_pixel_count((void *)(uintptr_t)edi, 0);
  /* relift: cmp (int16_t)esi, word ptr [edi + 0x14] -> jle 0x7e021 */
  return 0;

  (void)eax;
  (void)esi;
  (void)edi;
}

/* 0x7e040 */
int bitmap_get_pixel_data_size(void *bitmap_data)
{
  int eax = 0;
  int esi = 0;

  bitmap_verify((void *)(uintptr_t)esi, 0);
  /* test (char)eax, (char)eax -> jne 0x7e077 */
  display_assert((char *)0x00264da0, (char *)0x00264a74, 906, 0);
  system_exit(0);
  bitmap_get_pixel_count((void *)(uintptr_t)esi);
  bitmap_format_bits_per_pixel(0);
  return 0;

  (void)eax;
  (void)esi;
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

/* 0x7e560 */
void bitmap_3d_slice_insert(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  bitmap_verify((void *)(uintptr_t)edi, 0);
  /* test (char)eax, (char)eax -> jne 0x7e598 */
  display_assert((char *)0x00261b44, (char *)0x00264a74, 739, 0);
  system_exit(0);
  /* relift: cmp word ptr [edi + 0xa], 1 -> je 0x7e5bf */
  display_assert((char *)0x0026424c, (char *)0x00264a74, 740, 0);
  system_exit(0);
  /* test (int16_t)ebx, (int16_t)ebx -> jl 0x7e5cd */
  /* relift: cmp (int16_t)ebx, word ptr [edi + 0x14] -> jle 0x7e5ed */
  display_assert((char *)0x00261ac8, (char *)0x00264a74, 741, 0);
  system_exit(0);
  /* test (int16_t)eax, (int16_t)eax -> jl 0x7e5fb */
  /* relift: cmp (int16_t)eax, word ptr [edi + 8] -> jl 0x7e61b */
  display_assert((char *)0x00265338, (char *)0x00264a74, 742, 0);
  system_exit(0);
  /* cmp (int16_t)edx, 1 -> jge 0x7e636 */
  /* cmp eax, ecx -> je 0x7e668 */
  display_assert((char *)0x002652f0, (char *)0x00264a74, 743, 0);
  system_exit(0);
  /* cmp (int16_t)esi, 1 -> jge 0x7e686 */
  /* cmp eax, edx -> je 0x7e6b5 */
  display_assert((char *)0x002652a0, (char *)0x00264a74, 744, 0);
  system_exit(0);
  /* relift: test byte ptr [edi + 0xe], 8 -> je 0x7e6db */
  display_assert((char *)0x00265264, (char *)0x00264a74, 745, 0);
  system_exit(0);
  bitmap_verify((void *)(uintptr_t)ebx, 0);
  /* test (char)eax, (char)eax -> jne 0x7e70a */
  display_assert((char *)0x00265240, (char *)0x00264a74, 747, 0);
  system_exit(0);
  /* relift: cmp word ptr [ebx + 0x14], 0 -> je 0x7e731 */
  display_assert((char *)0x00265220, (char *)0x00264a74, 748, 0);
  system_exit(0);
  /* relift: cmp word ptr [ebx + 0xa], 0 -> je 0x7e758 */
  display_assert((char *)0x002651fc, (char *)0x00264a74, 749, 0);
  system_exit(0);
  /* relift: cmp (int16_t)eax, word ptr [edi + 0xc] -> je 0x7e782 */
  display_assert((char *)0x002651d0, (char *)0x00264a74, 750, 0);
  system_exit(0);
  /* relift: test byte ptr [ebx + 0xe], 8 -> je 0x7e7a8 */
  display_assert((char *)0x00265198, (char *)0x00264a74, 751, 0);
  system_exit(0);
  bitmap_get_pixel_data_size((void *)(uintptr_t)ebx);
  bitmap_3d_address((void *)(uintptr_t)edi, 0, 0, 0, 0);
  bitmap_mipmap_address((void *)(uintptr_t)ebx, 0);
  csmemcpy((void *)(uintptr_t)eax, (void *)(uintptr_t)edi, esi);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x7e7e0 */
void bitmap_cube_map_face_extract(void *src_bitmap, void *dst_bitmap, int face, int slice)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  bitmap_verify((void *)(uintptr_t)esi, 0);
  /* test (char)eax, (char)eax -> jne 0x7e818 */
  display_assert((char *)0x00265240, (char *)0x00264a74, 774, 0);
  system_exit(0);
  /* relift: cmp word ptr [esi + 0x14], 0 -> je 0x7e83f */
  display_assert((char *)0x00265220, (char *)0x00264a74, 775, 0);
  system_exit(0);
  /* relift: cmp word ptr [esi + 0xa], 0 -> je 0x7e866 */
  display_assert((char *)0x002651fc, (char *)0x00264a74, 776, 0);
  system_exit(0);
  /* relift: cmp (int16_t)eax, word ptr [edi + 0xc] -> je 0x7e893 */
  display_assert((char *)0x00265480, (char *)0x00264a74, 777, 0);
  system_exit(0);
  /* relift: test byte ptr [esi + 0xe], 8 -> je 0x7e8b9 */
  display_assert((char *)0x00265198, (char *)0x00264a74, 778, 0);
  system_exit(0);
  bitmap_verify((void *)(uintptr_t)edi, 0);
  /* test (char)eax, (char)eax -> jne 0x7e8e8 */
  display_assert((char *)0x00261974, (char *)0x00264a74, 780, 0);
  system_exit(0);
  /* relift: cmp word ptr [edi + 0xa], 1 -> je 0x7e90f */
  display_assert((char *)0x00264638, (char *)0x00264a74, 781, 0);
  system_exit(0);
  /* test (int16_t)ebx, (int16_t)ebx -> jl 0x7e91d */
  /* relift: cmp (int16_t)ebx, word ptr [edi + 0x14] -> jle 0x7e93d */
  display_assert((char *)0x002618e8, (char *)0x00264a74, 782, 0);
  system_exit(0);
  /* test (int16_t)eax, (int16_t)eax -> jl 0x7e94b */
  /* relift: cmp (int16_t)eax, word ptr [edi + 8] -> jl 0x7e96b */
  display_assert((char *)0x00265430, (char *)0x00264a74, 783, 0);
  system_exit(0);
  /* cmp (int16_t)edx, 1 -> jge 0x7e986 */
  /* cmp eax, ecx -> je 0x7e9b5 */
  display_assert((char *)0x002653d8, (char *)0x00264a74, 784, 0);
  system_exit(0);
  /* cmp (int16_t)edx, 1 -> jge 0x7e9d0 */
  /* cmp eax, ecx -> je 0x7e9ff */
  display_assert((char *)0x00265380, (char *)0x00264a74, 785, 0);
  system_exit(0);
  /* relift: test byte ptr [edi + 0xe], 8 -> je 0x7ea25 */
  display_assert((char *)0x002618ac, (char *)0x00264a74, 786, 0);
  system_exit(0);
  bitmap_get_pixel_data_size((void *)(uintptr_t)esi);
  bitmap_3d_address((void *)(uintptr_t)edi, 0, 0, 0, 0);
  bitmap_mipmap_address((void *)(uintptr_t)eax, 0);
  csmemcpy((void *)(uintptr_t)edi, (void *)(uintptr_t)eax, esi);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x7ea60 */
void FUN_0007ea60(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  bitmap_verify((void *)(uintptr_t)edi, 0);
  /* test (char)eax, (char)eax -> jne 0x7ea98 */
  display_assert((char *)0x00261b44, (char *)0x00264a74, 809, 0);
  system_exit(0);
  /* relift: cmp word ptr [edi + 0xa], 2 -> je 0x7eabf */
  display_assert((char *)0x00264274, (char *)0x00264a74, 810, 0);
  system_exit(0);
  /* test (int16_t)ebx, (int16_t)ebx -> jl 0x7eacd */
  /* relift: cmp (int16_t)ebx, word ptr [edi + 0x14] -> jle 0x7eaed */
  display_assert((char *)0x00261ac8, (char *)0x00264a74, 811, 0);
  system_exit(0);
  /* test (int16_t)eax, (int16_t)eax -> jl 0x7eafb */
  /* cmp (int16_t)eax, 6 -> jl 0x7eb1b */
  display_assert((char *)0x00265610, (char *)0x00264a74, 812, 0);
  system_exit(0);
  /* cmp (int16_t)edx, 1 -> jge 0x7eb36 */
  /* cmp eax, ecx -> je 0x7eb68 */
  display_assert((char *)0x002655c8, (char *)0x00264a74, 813, 0);
  system_exit(0);
  /* cmp (int16_t)esi, 1 -> jge 0x7eb86 */
  /* cmp eax, edx -> je 0x7ebb5 */
  display_assert((char *)0x00265580, (char *)0x00264a74, 814, 0);
  system_exit(0);
  /* relift: test byte ptr [edi + 0xe], 8 -> je 0x7ebdb */
  display_assert((char *)0x00265264, (char *)0x00264a74, 815, 0);
  system_exit(0);
  bitmap_verify((void *)(uintptr_t)ebx, 0);
  /* test (char)eax, (char)eax -> jne 0x7ec0a */
  display_assert((char *)0x0026555c, (char *)0x00264a74, 817, 0);
  system_exit(0);
  /* relift: cmp word ptr [ebx + 0x14], 0 -> je 0x7ec31 */
  display_assert((char *)0x0026553c, (char *)0x00264a74, 818, 0);
  system_exit(0);
  /* relift: cmp word ptr [ebx + 0xa], 0 -> je 0x7ec58 */
  display_assert((char *)0x00265518, (char *)0x00264a74, 819, 0);
  system_exit(0);
  /* relift: cmp (int16_t)eax, word ptr [edi + 0xc] -> je 0x7ec82 */
  display_assert((char *)0x002654ec, (char *)0x00264a74, 820, 0);
  system_exit(0);
  /* relift: test byte ptr [ebx + 0xe], 8 -> je 0x7eca8 */
  display_assert((char *)0x002654b4, (char *)0x00264a74, 821, 0);
  system_exit(0);
  bitmap_get_pixel_data_size((void *)(uintptr_t)ebx);
  bitmap_cube_map_address((void *)(uintptr_t)edi, 0, 0, 0, 0);
  bitmap_mipmap_address((void *)(uintptr_t)ebx, 0);
  csmemcpy((void *)(uintptr_t)eax, (void *)(uintptr_t)edi, esi);
  bitmap_verify((void *)(uintptr_t)esi, 0);
  /* test (char)eax, (char)eax -> jne 0x7ed18 */
  display_assert((char *)0x0026555c, (char *)0x00264a74, 844, 0);
  system_exit(0);
  /* relift: cmp word ptr [esi + 0x14], 0 -> je 0x7ed3f */
  display_assert((char *)0x0026553c, (char *)0x00264a74, 845, 0);
  system_exit(0);
  /* relift: cmp word ptr [esi + 0xa], 0 -> je 0x7ed66 */
  display_assert((char *)0x00265518, (char *)0x00264a74, 846, 0);
  system_exit(0);
  /* relift: cmp (int16_t)eax, word ptr [edi + 0xc] -> je 0x7ed93 */
  display_assert((char *)0x00265758, (char *)0x00264a74, 847, 0);
  system_exit(0);
  /* relift: test byte ptr [esi + 0xe], 8 -> je 0x7edb9 */
  display_assert((char *)0x002654b4, (char *)0x00264a74, 848, 0);
  system_exit(0);
  bitmap_verify((void *)(uintptr_t)edi, 0);
  /* test (char)eax, (char)eax -> jne 0x7ede8 */
  display_assert((char *)0x00261974, (char *)0x00264a74, 850, 0);
  system_exit(0);
  /* relift: cmp word ptr [edi + 0xa], 2 -> je 0x7ee0f */
  display_assert((char *)0x00264664, (char *)0x00264a74, 851, 0);
  system_exit(0);
  /* test (int16_t)ebx, (int16_t)ebx -> jl 0x7ee1d */
  /* relift: cmp (int16_t)ebx, word ptr [edi + 0x14] -> jle 0x7ee3d */
  display_assert((char *)0x002618e8, (char *)0x00264a74, 852, 0);
  system_exit(0);
  /* test (int16_t)eax, (int16_t)eax -> jl 0x7ee4b */
  /* cmp (int16_t)eax, 6 -> jl 0x7ee6b */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}
/* --- bitmaps.obj orphan shells (2026-07-26) --- */

/* orphan 0x7ba50 */
void FUN_0007ba50(void *bitmap)
{
  int eax = 0;
  int ebx = 0;
  int esi = 0;
  int edi = 0;

  bitmap_verify((void *)(uintptr_t)edi, 0);
  /* test (char)eax, (char)eax -> jne 0x7ba85 */
  display_assert((char *)0x00261814, (char *)0x002641f0, 1411, 0);
  system_exit(0);
  /* relift: cmp word ptr [edi + 0xa], 0 -> je 0x7baac */
  display_assert((char *)0x00264334, (char *)0x002641f0, 1412, 0);
  system_exit(0);
  bitmap_get_pixel_data_size((void *)(uintptr_t)edi);
  debug_malloc(eax, 0, (char *)0x002641f0, 1415);
  /* relift: cmp word ptr [edi + 6], (int16_t)ebx -> jle 0x7bc65 */
  /* relift: cmp word ptr [edi + 4], (int16_t)esi -> jle 0x7bc57 */
  bitmap_2d_address((void *)(uintptr_t)edi, 0, 0, 0);
  /* relift: relift: fcomp qword ptr [0x2533d0] */
  /* relift: cmp (int16_t)esi, word ptr [edi + 4] -> jl 0x7bb00 */
  /* relift: cmp (int16_t)ebx, word ptr [edi + 6] -> jl 0x7baf0 */
  bitmap_mipmap_address((void *)(uintptr_t)edi, 0);
  csmemcpy((void *)(uintptr_t)eax, (void *)0, 0);
  debug_free((void *)(uintptr_t)esi, (char *)0x002641f0, 1448);
  error(0, (char *)0x002642f0);

  (void)eax;
  (void)ebx;
  (void)esi;
  (void)edi;
}

/* orphan 0x7bcb0 */
void FUN_0007bcb0(void *bitmap)
{
  int eax = 0;
  int ebx = 0;
  int esi = 0;
  int edi = 0;

  bitmap_verify((void *)(uintptr_t)esi, 0);
  /* test (char)eax, (char)eax -> jne 0x7bcdf */
  display_assert((char *)0x00261814, (char *)0x002641f0, 1463, 0);
  system_exit(0);
  /* relift: cmp word ptr [esi + 0xa], 1 -> je 0x7bd06 */
  display_assert((char *)0x00264354, (char *)0x002641f0, 1464, 0);
  system_exit(0);
  bitmap_2d_new(0, 0, 0, 0);
  /* test edi, edi -> je 0x7bd6f */
  /* test eax, eax -> je 0x7bd6f */
  /* relift: cmp word ptr [esi + 8], (int16_t)ebx -> jle 0x7bd7e */
  bitmap_3d_slice_insert();
  FUN_0007ba50((void *)0);
  bitmap_cube_map_face_extract((void *)(uintptr_t)edi, (void *)(uintptr_t)esi, 0, 0);
  /* relift: cmp (int16_t)ebx, word ptr [esi + 8] -> jl 0x7bd40 */
  bitmap_delete((void *)(uintptr_t)edi);
  error(0, (char *)0x00264194);
  bitmap_delete((void *)(uintptr_t)edi);

  (void)eax;
  (void)ebx;
  (void)esi;
  (void)edi;
}

/* orphan 0x7bd90 */
void FUN_0007bd90(void *bitmap)
{
  int eax = 0;
  int ebx = 0;
  int esi = 0;
  int edi = 0;

  bitmap_verify((void *)(uintptr_t)ebx, 0);
  /* test (char)eax, (char)eax -> jne 0x7bdbf */
  display_assert((char *)0x00261814, (char *)0x002641f0, 1509, 0);
  system_exit(0);
  /* relift: cmp word ptr [ebx + 0xa], 2 -> je 0x7bde6 */
  display_assert((char *)0x0026439c, (char *)0x002641f0, 1510, 0);
  system_exit(0);
  bitmap_2d_new(0, 0, 0, 0);
  /* test edi, edi -> je 0x7be45 */
  /* test eax, eax -> je 0x7be45 */
  FUN_0007ea60();
  FUN_0007ba50((void *)0);
  bitmap_cube_map_face_insert();
  /* cmp (int16_t)esi, 6 -> jl 0x7be16 */
  bitmap_delete((void *)(uintptr_t)edi);
  error(0, (char *)0x00264194);
  bitmap_delete((void *)(uintptr_t)edi);

  (void)eax;
  (void)ebx;
  (void)esi;
  (void)edi;
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
