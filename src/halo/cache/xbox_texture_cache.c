/* Xbox texture cache: retrieve and block on hardware texture data.
 * Source: c:\halo\SOURCE\cache\xbox_texture_cache.c */
#ifdef HALO_RETAIL64
#define HALO_TEXTURE_CACHE_SIZE 0x800000
#else
#define HALO_TEXTURE_CACHE_SIZE 0x1600000
#endif

#define HALO_TEXTURE_CACHE_PAGE_BITS 0xe
#define HALO_TEXTURE_CACHE_PAGE_SIZE (1 << HALO_TEXTURE_CACHE_PAGE_BITS)
#define HALO_TEXTURE_CACHE_PAGE_COUNT \
  (HALO_TEXTURE_CACHE_SIZE >> HALO_TEXTURE_CACHE_PAGE_BITS)
#define HALO_TEXTURE_CACHE_STEAL_GUARD_SIZE 0x104000
#define HALO_TEXTURE_CACHE_STEAL_GUARD_PAGES \
  (HALO_TEXTURE_CACHE_STEAL_GUARD_SIZE >> HALO_TEXTURE_CACHE_PAGE_BITS)
#define HALO_TEXTURE_CACHE_STEALABLE_PAGES \
  (HALO_TEXTURE_CACHE_PAGE_COUNT - (HALO_TEXTURE_CACHE_STEAL_GUARD_PAGES * 2))

void *xbox_texture_cache_steal_memory(unsigned int size)
{
  int page_count =
    ((int)(size + (((int)size >> 0x1f) & (HALO_TEXTURE_CACHE_PAGE_SIZE - 1))) >>
     HALO_TEXTURE_CACHE_PAGE_BITS) +
    1;
  int remaining_page_count = HALO_TEXTURE_CACHE_STEALABLE_PAGES - page_count;
  char *base = (char *)FUN_001bdd60() +
               (remaining_page_count << HALO_TEXTURE_CACHE_PAGE_BITS);
  int stolen_size = page_count << HALO_TEXTURE_CACHE_PAGE_BITS;

  if (remaining_page_count < 1) {
    display_assert("remaining_page_count>0",
                   "c:\\halo\\SOURCE\\cache\\xbox_texture_cache.c", 0x13f,
                   true);
    system_exit(-1);
  }

  if (*(int8_t *)0x4ea984 != 0) {
    display_assert("!xbox_texture_cache_globals.stolen_memory",
                   "c:\\halo\\SOURCE\\cache\\xbox_texture_cache.c", 0x140,
                   true);
    system_exit(-1);
  }

  lruv_resize(*(void **)0x4ea980, remaining_page_count);
  physical_memory_protect(base + HALO_TEXTURE_CACHE_STEAL_GUARD_SIZE,
                          stolen_size, 4);
  physical_memory_protect(base, HALO_TEXTURE_CACHE_STEAL_GUARD_SIZE, 2);
  physical_memory_protect(base + HALO_TEXTURE_CACHE_STEAL_GUARD_SIZE +
                            stolen_size,
                          HALO_TEXTURE_CACHE_STEAL_GUARD_SIZE, 2);
  *(int8_t *)0x4ea984 = 1;
  return base + HALO_TEXTURE_CACHE_STEAL_GUARD_SIZE;
}

void xbox_texture_cache_return_memory(void)
{
  if (*(int8_t *)0x4ea984 == 0) {
    display_assert("xbox_texture_cache_globals.stolen_memory",
                   "c:\\halo\\SOURCE\\cache\\xbox_texture_cache.c", 0x159,
                   true);
    system_exit(-1);
  }

  lruv_resize(*(void **)0x4ea980, HALO_TEXTURE_CACHE_PAGE_COUNT);
  physical_memory_protect(FUN_001bdd60(), HALO_TEXTURE_CACHE_SIZE, 0x404);
  *(int8_t *)0x4ea984 = 0;
}

/* bitmap_format_to_d3d_linear_format (0x1beba0)
 *
 * Look up the linear D3D texture format code for a bitmap format index.
 * Table at 0x2b9618 maps format indices 0..17 to D3D format codes.
 * If flags bit 0x20 is set and format is 10 or 11 (DXT4/DXT5), returns 0x33. */
int bitmap_format_to_d3d_linear_format(int16_t format, uint16_t flags)
{
  int *table = (int *)0x2b9618;

  if (format < 0 || format >= 0x12) {
    display_assert("format>=0 && format<NUMBER_OF_BITMAP_FORMATS",
                   "c:\\halo\\SOURCE\\cache\\xbox_texture_cache.c", 0x1e1, 1);
    system_exit(-1);
  }

  if (table[format] == -1) {
    display_assert("table[format]!=NONE",
                   "c:\\halo\\SOURCE\\cache\\xbox_texture_cache.c", 0x1e2, 1);
    system_exit(-1);
  }

  if ((flags & 0x20) && (format == 10 || format == 11))
    return 0x33;

  return table[format];
}

/* FUN_001bec30 (0x1bec30)
 *
 * Look up the swizzled D3D texture format code for a bitmap format index.
 * Table at 0x2b9660 maps format indices 0..17 to D3D format codes.
 * If flags bit 0x20 is set and format is 10 or 11 (DXT4/DXT5), returns 0x36. */
int FUN_001bec30(int16_t format, uint16_t flags)
{
  int *table = (int *)0x2b9660;

  if (format < 0 || format >= 0x12) {
    display_assert("format>=0 && format<NUMBER_OF_BITMAP_FORMATS",
                   "c:\\halo\\SOURCE\\cache\\xbox_texture_cache.c", 0x206, 1);
    system_exit(-1);
  }

  if (table[format] == -1) {
    display_assert("table[format]!=NONE",
                   "c:\\halo\\SOURCE\\cache\\xbox_texture_cache.c", 0x207, 1);
    system_exit(-1);
  }

  if ((flags & 0x20) && (format == 10 || format == 11))
    return 0x36;

  return table[format];
}

/* xbox_texture_cache_setup_d3d_texture (0x1bee30)
 *
 * Populate a D3D texture resource header from a bitmap hardware format.
 * Two paths: if bitmap flags bit 0x10 is set, builds a swizzled texture
 * descriptor with pitch-based size encoding; otherwise builds a linear
 * texture descriptor using log2 dimensions and mipmap level count.
 * Finishes by registering the resource with D3DResource_Register.
 *
 * bitmap  is passed in ESI (hardware_format pointer).
 * texture is passed in EDI (D3D texture header, 5 dwords / 20 bytes). */
void xbox_texture_cache_setup_d3d_texture(void *bitmap /* @<esi> */,
                                          void *texture /* @<edi> */)
{
  int *tex = (int *)texture;
  char *bmp = (char *)bitmap;
  int format_bits;
  int pitch;
  int height;
  int width;

  assert_halt(bitmap);
  assert_halt(texture);

  tex[1] = 0;
  tex[2] = 0;
  tex[0] = 0x40001;

  if (*(uint16_t *)(bmp + 0xe) & 0x10) {
    format_bits =
      FUN_001bec30(*(int16_t *)(bmp + 0xc), *(uint16_t *)(bmp + 0xe));
    tex[3] = (format_bits << 8) | 0x10029;

    pitch = bitmap_mipmap_get_row_pitch(bitmap, 0);
    height = (int)*(int16_t *)(bmp + 0x6);
    width = (int)*(int16_t *)(bmp + 0x4);
    tex[4] =
      ((((pitch + ((pitch >> 31) & 0x3f)) >> 6) - 1) << 12 | (height - 1))
        << 12 |
      (width - 1);
  } else {
    int16_t log2_depth = FUN_00108db0((int)*(int16_t *)(bmp + 0x8));
    int16_t log2_height = FUN_00108db0((int)*(int16_t *)(bmp + 0x6));
    int16_t log2_width = FUN_00108db0((int)*(int16_t *)(bmp + 0x4));
    int linear_fmt = bitmap_format_to_d3d_linear_format(
      *(int16_t *)(bmp + 0xc), *(uint16_t *)(bmp + 0xe));
    int16_t mipmap_count = *(int16_t *)(bmp + 0xa);
    int16_t dim_level = FUN_00183120(bitmap);
    int dim_type = (mipmap_count != 1) ? 2 : 3;
    int cubemap_flag = (mipmap_count == 2) ? 4 : 0;

    format_bits = (int)log2_depth;
    format_bits = (format_bits << 4) | (int)log2_height;
    format_bits = (format_bits << 4) | (int)log2_width;
    format_bits = (format_bits << 12) | linear_fmt;
    format_bits = (format_bits << 4) | dim_type;
    format_bits = (format_bits << 4) | (((int)dim_level + 1) << 16);
    format_bits |= cubemap_flag | 0x9;

    tex[4] = 0;
    tex[3] = format_bits;
  }

  D3DResource_Register(texture, *(void **)(bmp + 0x2c));
}

bool xbox_texture_cache_request(void *hardware_format, bool block)
{
  int cache_block_index = FUN_00183290(hardware_format);

  if (cache_block_index <= *(int32_t *)((char *)hardware_format + 0x1c)) {
    cache_block_index = *(int32_t *)((char *)hardware_format + 0x1c);
  }

  cache_block_index = FUN_0011de10(*(void **)0x4ea980, cache_block_index);
  if (cache_block_index != -1) {
    int cache_page_index =
      lruv_block_get_address(*(void **)0x4ea980, cache_block_index) +
      *(int32_t *)0x4ea97c;
    int new_texture_index = data_new_datum(*(void **)0x4ea978, cache_block_index);
    char *cache_entry = datum_get(*(void **)0x4ea978, cache_block_index);

    if (new_texture_index != cache_block_index) {
      display_assert("new_texture_index==cache_block_index",
                     "c:\\halo\\SOURCE\\cache\\xbox_texture_cache.c", 0x1af,
                     true);
      system_exit(-1);
    }

    *(int32_t *)((char *)hardware_format + 0x24) = cache_block_index;
    *(int32_t *)((char *)hardware_format + 0x2c) = cache_page_index;
    *(void **)(cache_entry + 8) = hardware_format;
    xbox_texture_cache_setup_d3d_texture(hardware_format, cache_entry + 0xc);
    *(int16_t *)(cache_entry + 2) =
      cache_file_read(*(int32_t *)((char *)hardware_format + 0x20),
                      *(int32_t *)((char *)hardware_format + 0x18),
                      *(int32_t *)((char *)hardware_format + 0x1c),
                      cache_page_index, cache_entry + 4, block);
    return true;
  }

  return false;
}

void *xbox_texture_cache_get_hardware_format(void *hardware_format, bool block,
                                             bool load)
{
  void *result = NULL;

  if (!load && block) {
    display_assert("load || !block",
                   "c:\\halo\\SOURCE\\cache\\xbox_texture_cache.c", 0xd2, true);
    system_exit(-1);
  }

  if (*(int8_t *)((char *)hardware_format + 0xe) < 0) {
    if (*(int32_t *)((char *)hardware_format + 0x24) == -1 && load) {
      xbox_texture_cache_request(hardware_format, block);
    }
    if (*(int32_t *)((char *)hardware_format + 0x24) != -1) {
      void *entry = datum_get(*(void **)0x4ea978,
                              *(int32_t *)((char *)hardware_format + 0x24));
      lruv_debug_to_file(*(void **)0x4ea980,
                         *(int32_t *)((char *)hardware_format + 0x24));
      if (block) {
        if (*(int8_t *)((char *)entry + 4) != 0)
          goto loaded;
        if (*(uint8_t *)0x4ea98a) {
          const char *name =
            tag_get_name(*(int32_t *)((char *)hardware_format + 0x20));
          console_warning((const char *)0x257984, name);
        }
        cache_files_io_request_enable(*(int16_t *)((char *)entry + 2));
      }
      do {
        if (*(int8_t *)((char *)entry + 4) == 0) {
          unsigned int t0 = sound_render_time();
          unsigned int t1 = system_milliseconds();
          if (t1 - t0 > 0x84u) {
            sound_idle();
          }
          SwitchToThread();
        } else {
        loaded:
          if (*(int8_t *)((char *)entry + 5) == 0) {
            *(int8_t *)((char *)entry + 5) = 1;
          }
          result = (char *)entry + 0xc;
          if (result)
            break;
        }
        if (!block)
          return result;
      } while (true);
    }
  } else {
    result = *(void **)((char *)hardware_format + 0x28);
  }

  if (block && !result) {
    unsigned int now = system_milliseconds();
    if (now - *(unsigned int *)0x4ea98c > 10000u) {
      terminal_output(
        *(void **)0x2ee6f4,
        "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!",
        NULL);
      error(2, "YOU GOT STABBED!!!! double-click \"GETSTABBED.BAT\" on your PC "
               "now!!!");
      terminal_output(
        *(void **)0x2ee6f4,
        "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!",
        NULL);
      FUN_0011db90("d:\\stabbed.txt",
                   tag_get_name(*(int32_t *)((char *)hardware_format + 0x20)),
                   *(int32_t *)((char *)hardware_format + 0x1c),
                   *(void **)0x4ea980, (void *)0x18ef30, (void *)0x1beb70);
      *(unsigned int *)0x4ea98c = system_milliseconds();
    }
    result = rasterizer_get_default_hardware_format(hardware_format);
    if (!result) {
      display_assert("hardware_format",
                     "c:\\halo\\SOURCE\\cache\\xbox_texture_cache.c", 0x127,
                     true);
      system_exit(-1);
    }
  }

  return result;
}
/* --- xbox_texture_cache.obj batch drafts (2026-07-26) --- */

/* 0x1be920 */
void texture_cache_delete(void)
{
  int eax = 0;
  int ecx = 0;

  data_dispose((void *)(uintptr_t)eax);
  lruv_cache_dispose((void *)(uintptr_t)ecx);

  (void)eax;
  (void)ecx;
}

/* 0x1be940 */
void texture_cache_open(void)
{
  int eax = 0;

  data_delete_all((void *)(uintptr_t)eax);

  (void)eax;
}

/* 0x1be950 */
void texture_cache_idle(void)
{
  int eax = 0;

  lruv_idle((void *)(uintptr_t)eax);

  (void)eax;
}

/* 0x1be960 */
void texture_cache_bitmap_new(int tag_index, void *bitmap)
{
  int esi = 0;

  display_assert((char *)0x002b96a8, (char *)0x002b96d8, 157, 0);
  system_exit(0);
  tag_get('mtib', 0);
  bitmap_get_pixel_data_size((void *)(uintptr_t)esi);

  (void)esi;
}

/* 0x1be9f0 */
void texture_cache_bitmap_delete(void)
{
  int eax = 0;

  /* cmp eax, -1 -> je 0x1bea15 */
  lruv_block_delete((void *)(uintptr_t)eax, 0);

  (void)eax;
}

/* 0x1beb70 */
void FUN_001beb70(void)
{
  int ecx = 0;

  datum_get((void *)(uintptr_t)ecx, 0);
  tag_get_name(0);

  (void)ecx;
}

/* 0x1becc0 */
void FUN_001becc0(void)
{
  int eax = 0;
  int ecx = 0;

  FUN_00183290((void *)(uintptr_t)eax);
  FUN_00183290((void *)(uintptr_t)ecx);
  D3DDevice_IsBusy();
  D3DDevice_KickPushBuffer();
  D3DResource_IsBusy((void *)(uintptr_t)eax);
  D3DResource_Register((void *)(uintptr_t)ecx, (void *)(uintptr_t)eax);

  (void)eax;
  (void)ecx;
}

/* 0x1bed30 */
void texture_cache_flush(void)
{
  int eax = 0;

  D3DDevice_KickPushBuffer();
  D3DDevice_IsBusy();
  lruv_cache_dispose_all((void *)(uintptr_t)eax);

  (void)eax;
}

/* 0x1bed50 */
void FUN_001bed50(void)
{
  int eax = 0;
  int ecx = 0;

  datum_get((void *)(uintptr_t)ecx, 0);
  /* test (char)ecx, (char)ecx -> je 0x1bed7c */
  D3DResource_IsBusy((void *)(uintptr_t)eax);
  /* test eax, eax -> jne 0x1bed7c */

  (void)eax;
  (void)ecx;
}

/* 0x1bed90 */
void FUN_001bed90(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;

  datum_get((void *)(uintptr_t)eax, 0);
  datum_get((void *)(uintptr_t)ecx, 0);
  /* test (char)ecx, (char)ecx -> je 0x1bedb0 */
  D3DResource_IsBusy((void *)(uintptr_t)eax);
  /* test eax, eax -> jne 0x1bedb0 */
  /* relift: cmp dword ptr [edx + 0x24], esi -> je 0x1bedfc */
  display_assert((char *)0x002b9788, (char *)0x002b96d8, 391, 0);
  system_exit(0);
  datum_delete((void *)(uintptr_t)edx, 0);

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
}

/* 0x1bef80 */
void FUN_001bef80(void)
{
  /* relift: no calls detected — manual review */
}

/* 0x1bf080 */
void texture_cache_new(void)
{
  int eax = 0;

  data_new((char *)0x002b983c, 1408, 32);
  /* mem[0x004ea978] = eax */
  display_assert((char *)0x002b9818, (char *)0x002b96d8, 98, 0);
  system_exit(0);
  lruv_new(0x002b9804, 1408, 14, 1408, (void *)0x001bed90, (void *)0x001bed50);
  /* mem[0x004ea980] = eax */
  display_assert((char *)0x002b97e0, (char *)0x002b96d8, 102, 0);
  system_exit(0);
  FUN_001bdd60();
  /* mem[0x004ea97c] = eax */
  display_assert((char *)0x002b97b8, (char *)0x002b96d8, 105, 0);
  system_exit(0);

  (void)eax;
}

/* 0x1bf130 */
void texture_cache_close(void)
{
  int eax = 0;
  int ecx = 0;

  /* test (char)eax, (char)eax -> je 0x1bf159 */
  display_assert((char *)0x002b9704, (char *)0x002b96d8, 133, 0);
  system_exit(0);
  D3DDevice_KickPushBuffer();
  D3DDevice_IsBusy();
  lruv_cache_dispose_all((void *)(uintptr_t)eax);
  data_make_invalid((void *)(uintptr_t)ecx);

  (void)eax;
  (void)ecx;
}

/* 0x1bf260 */
void texture_cache_debug_render(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  lruv_cache_get_page_usage((void *)(uintptr_t)ecx, (unsigned char *)(uintptr_t)eax);
  /* test (char)ecx, dl -> je 0x1bf3ef */
  FUN_001bef80();
  FUN_00189270(0, (float *)(uintptr_t)eax, (float *)(uintptr_t)edx, (void *)(uintptr_t)ecx);
  /* cmp ebx, 3 -> jl 0x1bf300 */
  /* test (char)eax, (char)eax -> je 0x1bf55c */
  data_iterator_new((void *)(uintptr_t)edx, (void *)(uintptr_t)ecx);
  data_iterator_next((void *)(uintptr_t)eax);
  /* test eax, eax -> je 0x1bf45b */
  /* relift: cmp dword ptr [eax + 0x20], -1 -> je 0x1bf44b */
  data_iterator_next((void *)(uintptr_t)edx);
  /* test eax, eax -> jne 0x1bf437 */
  FUN_00091ef0((void *)0x004e9378, 0, (void *)0x001becc0);
  interface_get_tag_index(0);
  draw_string_set_tab_stops((void *)(uintptr_t)eax, 0);
  /* cmp edi, -1 -> je 0x1bf4a5 */
  FUN_0019B7E0();
  /* test esi, esi -> jl 0x1bf55c */
  lruv_block_touched((void *)(uintptr_t)eax, 0);
  tag_get_name(0);
  FUN_00183290((void *)(uintptr_t)eax);
  crt_sprintf((char *)(uintptr_t)ecx, (char *)0x002b9874);
  draw_string_set_color((void *)(uintptr_t)ecx);
  rasterizer_text_draw((void *)(uintptr_t)eax, (void *)0, (void *)0, 0, (char *)(uintptr_t)edx);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}
