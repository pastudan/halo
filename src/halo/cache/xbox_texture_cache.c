#include <stdint.h>
/* Xbox texture cache: retrieve and block on hardware texture data.
 * Source: c:\halo\SOURCE\cache\xbox_texture_cache.c */

/* Defined in memory/lruv_cache.c; missing from generated decl.h. */
void *lruv_new(int name, int page_count, int page_size_bits,
               int maximum_block_count, void (*delete_cb)(int),
               int (*query_cb)(int));

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


/* xbox_texture_cache_return_memory (0x1beb10) — readable C lift. */
void xbox_texture_cache_return_memory(void)
{
  extern char DAT_002b96d8[];
  extern char DAT_002b9748[];
  void *addr;
  if (!*(unsigned char *)0x4ea984) {
    display_assert(DAT_002b9748, DAT_002b96d8, 0x159, true);
    system_exit(-1);
  }
  lruv_resize(*(void **)0x4ea980, 0x580);
  addr = FUN_001bdd60();
  physical_memory_protect(addr, 0x1600000u, 0x404u);
  *(unsigned char *)0x4ea984 = 0;
}

/* bitmap_format_to_d3d_linear_format (0x1beba0) — readable C lift. */
int bitmap_format_to_d3d_linear_format(int16_t format, uint16_t flags)
{
  extern char DAT_00264ad4[];
  extern char DAT_002b96d8[];
  extern char DAT_002b9774[];
  int *table = (int *)0x2b9618;

  if (format < 0 || format >= 0x12) {
    display_assert(DAT_00264ad4, DAT_002b96d8, 0x1e1, 1);
    system_exit(-1);
  }
  if (table[format] == -1) {
    display_assert(DAT_002b9774, DAT_002b96d8, 0x1e2, 1);
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
void xbox_texture_cache_setup_d3d_texture(void *bitmap ,
                                          void *texture )
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
    int new_texture_index =
      data_new_datum(*(void **)0x4ea978, cache_block_index);
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

/* texture_cache_delete (0x1be920) — readable C lift. */
void texture_cache_delete(void)
{
  data_dispose(*(void **)0x4ea978);
  lruv_cache_dispose(*(void **)0x4ea980);
}

/* texture_cache_open (0x1be940) — readable C lift. */
void texture_cache_open(void)
{
  data_delete_all(*(data_t **)0x4ea978);
}

/* texture_cache_idle (0x1be950) — readable C lift. */
void texture_cache_idle(void)
{
  lruv_idle(*(void **)0x4ea980);
}

/* texture_cache_bitmap_new (0x1be960) — readable C lift. */
void texture_cache_bitmap_new(int tag_index, void *bitmap)
{
  char *entry = (char *)bitmap;
  void *tag;
  int size;

  if ((entry[0xe] & 0x80) != 0) {
    display_assert((const char *)0x2b96a8, (const char *)0x2b96d8, 0x9d, 1);
    system_exit(-1);
  }
  *(unsigned short *)(entry + 0xe) |= 0x80;
  *(int *)(entry + 0x24) = -1;
  *(int *)(entry + 0x2c) = 0;
  *(int *)(entry + 0x28) = 0;
  tag = tag_get(0x6269746d, tag_index);
  *(int *)(entry + 0x18) += *(int *)((char *)tag + 0x38);
  size = bitmap_get_pixel_data_size(entry);
  *(int *)(entry + 0x20) = tag_index;
  *(int *)(entry + 0x2c) = 0;
  *(int *)(entry + 0x28) = 0;
  *(int *)(entry + 0x1c) = size;
  *(int *)(entry + 0x24) = -1;
}

/* texture_cache_bitmap_delete (0x1be9f0) — readable C lift. */
void texture_cache_bitmap_delete(void *entry)
{
  if ((*(unsigned char *)((char *)entry + 0xe) & 0x80) == 0)
    return;
  if (*(int *)((char *)entry + 0x24) != -1)
    lruv_block_delete(*(void **)0x4ea980, *(int *)((char *)entry + 0x24));
  *(unsigned char *)((char *)entry + 0xe) &= 0x7f;
  *(int *)((char *)entry + 0x24) = -1;
  *(int *)((char *)entry + 0x2c) = 0;
}
/* FUN_001beb70 (0x1beb70) — readable C lift. */
const char *FUN_001beb70(int handle)
{
  void *entry;
  entry = datum_get(*(data_t **)0x4ea978, handle);
  return tag_get_name(*(int *)(*(char **)((char *)entry + 8) + 0x20));
}


/* FUN_001becc0 (0x1becc0) — readable C lift. */
int FUN_001becc0(void *a, void *b)
{
  int da;
  int db;
  da = FUN_00183290(a);
  db = FUN_00183290(b);
  return da > db;
}

/* texture_cache_flush (0x1bed30) — readable C lift. */
void texture_cache_flush(void)
{
  D3DDevice_KickPushBuffer(0);
  D3DDevice_IsBusy();
  lruv_cache_dispose_all(*(void **)0x4ea980);
}

/* FUN_001bed50 (0x1bed50) — readable C lift. */
int FUN_001bed50(int handle)
{
  void *entry;
  entry = datum_get(*(data_t **)0x4ea978, handle);
  if (*(unsigned char *)((char *)entry + 4) != 0) {
    if (D3DResource_IsBusy((char *)entry + 0xc) == 0)
      return 0;
  }
  return 1;
}
/* FUN_001bed90 (0x1bed90) — XBE naked draft (batch 261). */
#if defined(__clang__)
static void *(*const b1bed90_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static int __stdcall (*const b1bed90_c1ed980)(void *resource) = D3DResource_IsBusy;
static void (*const b1bed90_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1bed90_exitfn)(int) = system_exit;
static void (*const b1bed90_c1196d0)(data_t *data, int datum_handle) = datum_delete;

__attribute__((naked, noinline))
void FUN_001bed90(int cache_handle)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl 0x4ea978, %%eax\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "addl $8, %%esp\n\t"
      "movl %%eax, %%edi\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_001bed90_1:\n\t"
      "movl 0x4ea978, %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movb 0x4(%%eax), %%cl\n\t"
      "addl $8, %%esp\n\t"
      "testb %%cl, %%cl\n\t"
      "je .LFUN_001bed90_1\n\t"
      "addl $0xc, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1ed980]\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_001bed90_1\n\t"
      "movl 0x8(%%edi), %%edx\n\t"
      "cmpl %%esi, 0x24(%%edx)\n\t"
      "je .LFUN_001bed90_2\n\t"
      "pushl $1\n\t"
      "pushl $0x187\n\t"
      "pushl $0x2b96d8\n\t"
      "pushl $0x2b9788\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001bed90_2:\n\t"
      "movl 0x8(%%edi), %%eax\n\t"
      "movl $0xffffffff, 0x24(%%eax)\n\t"
      "movl 0x8(%%edi), %%ecx\n\t"
      "movl $0, 0x2c(%%ecx)\n\t"
      "movl 0x4ea978, %%edx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edx\n\t"
      "call *%[c1196d0]\n\t"
      "addl $8, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [dget] "m"(b1bed90_dget), [c1ed980] "m"(b1bed90_c1ed980), [assert] "m"(b1bed90_assert), [exitfn] "m"(b1bed90_exitfn), [c1196d0] "m"(b1bed90_c1196d0)
      : "memory");
}
#else
#error "FUN_001bed90: clang naked draft required"
#endif


/* FUN_001bef80 (0x1bef80) — readable C lift.
 * out_a@eax, out_c@ecx, uv@edx (twin of FUN_001be6b0). */
void FUN_001bef80_lift(float *out_a, float *out_c, float *uv)
{
  float *origin;
  float su, sv;
  float d0x, d0y, d0z;
  float d1x, d1y, d1z;
  float px, py, pz;

  su = uv[0] * *(float *)0x2a41b8;
  sv = *(float *)0x2533c8 - uv[1] * *(float *)0x2a41b4;
  origin = *(float **)0x31fc38;
  out_a[0] = *(float *)0x5066b4 + origin[0];
  out_a[1] = *(float *)0x5066b8 + origin[1];
  out_a[2] = *(float *)0x5066bc + origin[2];

  d0x = *(float *)0x506690 - *(float *)0x506684;
  d0y = *(float *)0x506694 - *(float *)0x506688;
  d0z = *(float *)0x506698 - *(float *)0x50668c;
  d1x = *(float *)0x50669c - *(float *)0x506684;
  d1y = *(float *)0x5066a0 - *(float *)0x506688;
  d1z = *(float *)0x5066a4 - *(float *)0x50668c;

  px = d0x * su + *(float *)0x506684;
  py = d0y * su + *(float *)0x506688;
  pz = d0z * su + *(float *)0x50668c;
  px = d1x * sv + px;
  py = d1y * sv + py;
  pz = d1z * sv + pz;

  out_c[0] = px - out_a[0];
  out_c[1] = py - out_a[1];
  out_c[2] = pz - out_a[2];
}

/* texture_cache_new (0x1bf080) — readable C lift. */
void texture_cache_new(void)
{
  void *data;
  void *lruv;
  void *predicted;

  data = data_new((char *)0x2b983c, 0x580, 0x20);
  *(void **)0x4ea978 = data;
  if (data == NULL) {
    display_assert((const char *)0x2b9818, (const char *)0x2b96d8, 0x62, true);
    system_exit(-1);
  }
  lruv = lruv_new((int)0x2b9804, 0x580, 0xe, 0x580,
                  (void (*)(int))FUN_001bed90, (int (*)(int))0x1bed50);
  *(void **)0x4ea980 = lruv;
  if (lruv == NULL) {
    display_assert((const char *)0x2b97e0, (const char *)0x2b96d8, 0x66, true);
    system_exit(-1);
  }
  predicted = FUN_001bdd60();
  *(void **)0x4ea97c = predicted;
  if (predicted == NULL) {
    display_assert((const char *)0x2b97b8, (const char *)0x2b96d8, 0x69, true);
    system_exit(-1);
  }
}

/* texture_cache_close (0x1bf130) — readable C lift. */
void texture_cache_close(void)
{
  extern char DAT_002b96d8[];
  extern char DAT_002b9704[];
  if (*(unsigned char *)0x4ea984) {
    display_assert(DAT_002b9704, DAT_002b96d8, 0x85, true);
    system_exit(-1);
  }
  D3DDevice_KickPushBuffer(0);
  D3DDevice_IsBusy();
  lruv_cache_dispose_all(*(void **)0x4ea980);
  data_make_invalid(*(data_t **)0x4ea978);
}

/* texture_cache_debug_render (0x1bf260) — readable C lift (restored pre-naked). */
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
  ((void(*)(void))FUN_0019B7E0)();
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


