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

/* texture_cache_bitmap_new (0x1be960) — XBE naked draft (batch 265). */
#if defined(__clang__)
static void (*const b1be960_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1be960_exitfn)(int) = system_exit;
static void *(*const b1be960_tag)(int, int) = tag_get;
static int (*const b1be960_c7e040)(void *bitmap_data) = bitmap_get_pixel_data_size;

__attribute__((naked, noinline))
void texture_cache_bitmap_new(int tag_index __attribute__((unused)), void *bitmap __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0xc(%%ebp), %%esi\n\t"
      "movb 0xe(%%esi), %%al\n\t"
      "movl $0x80, %%ebx\n\t"
      "testb %%al, %%bl\n\t"
      "pushl %%edi\n\t"
      "je .Ltexture_cache_bitmap_new_1\n\t"
      "pushl $1\n\t"
      "pushl $0x9d\n\t"
      "pushl $0x2b96d8\n\t"
      "pushl $0x2b96a8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Ltexture_cache_bitmap_new_1:\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "orw %%bx, 0xe(%%esi)\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "pushl %%edi\n\t"
      "pushl $0x6269746d\n\t"
      "movl $0xffffffff, 0x24(%%esi)\n\t"
      "movl %%ebx, 0x2c(%%esi)\n\t"
      "movl %%ebx, 0x28(%%esi)\n\t"
      "call *%[tag]\n\t"
      "movl 0x38(%%eax), %%eax\n\t"
      "movl 0x18(%%esi), %%ecx\n\t"
      "addl %%eax, %%ecx\n\t"
      "pushl %%esi\n\t"
      "movl %%ecx, 0x18(%%esi)\n\t"
      "call *%[c7e040]\n\t"
      "addl $0xc, %%esp\n\t"
      "movl %%edi, 0x20(%%esi)\n\t"
      "popl %%edi\n\t"
      "movl %%ebx, 0x2c(%%esi)\n\t"
      "movl %%ebx, 0x28(%%esi)\n\t"
      "movl %%eax, 0x1c(%%esi)\n\t"
      "movl $0xffffffff, 0x24(%%esi)\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b1be960_assert), [exitfn] "m"(b1be960_exitfn), [tag] "m"(b1be960_tag), [c7e040] "m"(b1be960_c7e040)
      : "memory");
}
#else
#error "texture_cache_bitmap_new: clang naked draft required"
#endif


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
  D3DDevice_KickPushBuffer();
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
void FUN_001bed90(void)
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


/* FUN_001bef80 (0x1bef80) — XBE naked draft (batch 246). */
#if defined(__clang__)


__attribute__((naked, noinline))
void FUN_001bef80(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x24, %%esp\n\t"
      "flds (%%edx)\n\t"
      "fmuls 0x2a41b8\n\t"
      "flds 0x4(%%edx)\n\t"
      "movl 0x31fc38, %%edx\n\t"
      "fmuls 0x2a41b4\n\t"
      "fsubrs 0x2533c8\n\t"
      "flds 0x5066b4\n\t"
      "fadds (%%edx)\n\t"
      "fstps (%%eax)\n\t"
      "flds 0x5066b8\n\t"
      "fadds 0x4(%%edx)\n\t"
      "fstps 0x4(%%eax)\n\t"
      "flds 0x5066bc\n\t"
      "fadds 0x8(%%edx)\n\t"
      "fstps 0x8(%%eax)\n\t"
      "flds 0x506690\n\t"
      "fsubs 0x506684\n\t"
      "flds 0x506694\n\t"
      "fsubs 0x506688\n\t"
      "flds 0x506698\n\t"
      "fsubs 0x50668c\n\t"
      "fstps -0x1c(%%ebp)\n\t"
      "flds 0x50669c\n\t"
      "fsubs 0x506684\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "flds 0x5066a0\n\t"
      "fsubs 0x506688\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "flds 0x5066a4\n\t"
      "fsubs 0x50668c\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "fxch %%st(1)\n\t"
      "fmul %%st(3), %%st(0)\n\t"
      "fadds 0x506684\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "fmul %%st(2), %%st(0)\n\t"
      "fadds 0x506688\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fmul %%st(3), %%st(0)\n\t"
      "fadds 0x50668c\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fmul %%st(2), %%st(0)\n\t"
      "fadds -0xc(%%ebp)\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fmul %%st(2), %%st(0)\n\t"
      "fadd %%st(1), %%st(0)\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fadds -0x4(%%ebp)\n\t"
      "fstp %%st(2)\n\t"
      "fstp %%st(0)\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fsubs (%%eax)\n\t"
      "fstps (%%ecx)\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fsubs 0x4(%%eax)\n\t"
      "fstps 0x4(%%ecx)\n\t"
      "fsubs 0x8(%%eax)\n\t"
      "fstps 0x8(%%ecx)\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "FUN_001bef80: clang naked draft required"
#endif


/* texture_cache_new (0x1bf080) — XBE naked draft (batch 267). */
#if defined(__clang__)
static data_t * (*const b1bf080_c1194d0)(char *name, int16_t maximum_count, int16_t size) = data_new;
static void (*const b1bf080_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1bf080_exitfn)(int) = system_exit;
static void * (*const b1bf080_c11dd60)(int name, int page_count, int page_size_bits, int maximum_block_count, void (*delete_cb)(int), int (*query_cb)(int)) = lruv_new;
static void * (*const b1bf080_c1bdd60)(void) = FUN_001bdd60;

__attribute__((naked, noinline))
void texture_cache_new(void)
{
  __asm__ volatile(
      "pushl $0x20\n\t"
      "pushl $0x580\n\t"
      "pushl $0x2b983c\n\t"
      "call *%[c1194d0]\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%eax, 0x4ea978\n\t"
      "jne .Ltexture_cache_new_1\n\t"
      "pushl $1\n\t"
      "pushl $0x62\n\t"
      "pushl $0x2b96d8\n\t"
      "pushl $0x2b9818\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Ltexture_cache_new_1:\n\t"
      "pushl $0x1bed50\n\t"
      "pushl $0x1bed90\n\t"
      "pushl $0x580\n\t"
      "pushl $0xe\n\t"
      "pushl $0x580\n\t"
      "pushl $0x2b9804\n\t"
      "call *%[c11dd60]\n\t"
      "addl $0x18, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%eax, 0x4ea980\n\t"
      "jne .Ltexture_cache_new_2\n\t"
      "pushl $1\n\t"
      "pushl $0x66\n\t"
      "pushl $0x2b96d8\n\t"
      "pushl $0x2b97e0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Ltexture_cache_new_2:\n\t"
      "call *%[c1bdd60]\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%eax, 0x4ea97c\n\t"
      "jne .Ltexture_cache_new_3\n\t"
      "pushl $1\n\t"
      "pushl $0x69\n\t"
      "pushl $0x2b96d8\n\t"
      "pushl $0x2b97b8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Ltexture_cache_new_3:\n\t"
      "ret\n\t"
      :
      : [c1194d0] "m"(b1bf080_c1194d0), [assert] "m"(b1bf080_assert), [exitfn] "m"(b1bf080_exitfn), [c11dd60] "m"(b1bf080_c11dd60), [c1bdd60] "m"(b1bf080_c1bdd60)
      : "memory");
}
#else
#error "texture_cache_new: clang naked draft required"
#endif



/* texture_cache_close (0x1bf130) — readable C lift. */
void texture_cache_close(void)
{
  extern char DAT_002b96d8[];
  extern char DAT_002b9704[];
  if (*(unsigned char *)0x4ea984) {
    display_assert(DAT_002b9704, DAT_002b96d8, 0x85, true);
    system_exit(-1);
  }
  D3DDevice_KickPushBuffer();
  D3DDevice_IsBusy();
  lruv_cache_dispose_all(*(void **)0x4ea980);
  data_make_invalid(*(data_t **)0x4ea978);
}

/* texture_cache_debug_render (0x1bf260) — XBE naked draft (batch 244). */
#if defined(__clang__)
static void (*const b1bf260_c11da60)(void *cache, unsigned char *usage) = lruv_cache_get_page_usage;
static void (*const b1bf260_c1bef80)(void) = FUN_001bef80;
static void (*const b1bf260_c189270)(char flag, float *point_a, float *point_b, void *color) = FUN_00189270;
static void (*const b1bf260_c1197b0)(data_iter_t *iter, data_t *data) = data_iterator_new;
static void * (*const b1bf260_c119810)(data_iter_t *iterator) = data_iterator_next;
static void (*const b1bf260_c91ef0)(int *keys, int count, int (*cmp)(int, int)) = FUN_00091ef0;
static int (*const b1bf260_cdeca0)(int interface_tag_index) = interface_get_tag_index;
static void (*const b1bf260_c19b560)(void *stops, short count) = draw_string_set_tab_stops;
static void (*const b1bf260_c19b7e0)(void) = FUN_0019B7E0;
static bool (*const b1bf260_c11da30)(void *lruv, int block_index) = lruv_block_touched;
static const char * (*const b1bf260_c1ba1f0)(int tag_index) = tag_get_name;
static int (*const b1bf260_c183290)(void *bitmap) = FUN_00183290;
static int (*const b1bf260_c1d90f0)(char *buffer, const char *format, ...) = crt_sprintf;
static void (*const b1bf260_c19b640)(const void *color) = draw_string_set_color;
static void (*const b1bf260_c183e60)(void *screen_pos, short *bounds, const void *color, int flags, const char *text) = rasterizer_text_draw;

__attribute__((naked, noinline))
void texture_cache_debug_render(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x5e0, %%esp\n\t"
      "movb 0x4ea988, %%al\n\t"
      "testb %%al, %%al\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "je .Ltexture_cache_debug_render_5\n\t"
      "movl 0x2ee6d4, %%ecx\n\t"
      "movl 0x2ee6d8, %%edx\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x50658a, %%ax\n\t"
      "subw 0x506586, %%ax\n\t"
      "movl %%ecx, -0x30(%%ebp)\n\t"
      "movl 0x4ea980, %%ecx\n\t"
      "movl %%edx, -0x2c(%%ebp)\n\t"
      "movl $0, -0x28(%%ebp)\n\t"
      "movl %%eax, -0x20(%%ebp)\n\t"
      "movl 0x2ee6d0, %%eax\n\t"
      "movl %%eax, -0x34(%%ebp)\n\t"
      "leal -0x5e0(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c11da60]\n\t"
      "addl $8, %%esp\n\t"
      "xorl %%eax, %%eax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "jmp .Ltexture_cache_debug_render_1\n\t"
      "leal (%%esp), %%esp\n\t"
      ".Ltexture_cache_debug_render_1:\n\t"
      "movl 0x506584, %%esi\n\t"
      "movl 0x50657c, %%edx\n\t"
      "xorl %%edi, %%edi\n\t"
      "movw 0x506586, %%di\n\t"
      "subw 0x50657e, %%di\n\t"
      "subl %%edx, %%esi\n\t"
      "shll $2, %%esi\n\t"
      "movl %%esi, -0xc(%%ebp)\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "movl %%edi, -0x38(%%ebp)\n\t"
      "leal (%%esp), %%esp\n\t"
      ".Ltexture_cache_debug_render_2:\n\t"
      "movl %%ebx, %%ecx\n\t"
      "movl $1, %%edx\n\t"
      "shll %%cl, %%edx\n\t"
      "movb -0x5e0(%%ebp,%%eax,1), %%cl\n\t"
      "testb %%dl, %%cl\n\t"
      "je .Ltexture_cache_debug_render_4\n\t"
      "movswl -0x20(%%ebp), %%ecx\n\t"
      "cdq\n\t"
      "idivl %%ecx\n\t"
      "movswl %%di, %%ecx\n\t"
      "leal -0x48(%%ebp), %%edi\n\t"
      "leal (%%ebx,%%eax,4), %%eax\n\t"
      "addl %%edx, %%ecx\n\t"
      "leal (%%eax,%%eax,4), %%edx\n\t"
      "movswl %%si, %%eax\n\t"
      "movl %%ecx, -0x4(%%ebp)\n\t"
      "leal (%%eax,%%edx,2), %%eax\n\t"
      "leal -0x58(%%ebp), %%esi\n\t"
      "fildl -0x4(%%ebp)\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "addl $0xa, %%eax\n\t"
      "fsts -0x48(%%ebp)\n\t"
      "fildl -0x4(%%ebp)\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "fstps -0x44(%%ebp)\n\t"
      "fstps -0x40(%%ebp)\n\t"
      "fildl -0x4(%%ebp)\n\t"
      "movl $2, -0x4(%%ebp)\n\t"
      "fstps -0x3c(%%ebp)\n\t"
      "flds 0x50658c\n\t"
      "fadds 0x255ef8\n\t"
      "fstps -0x24(%%ebp)\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".Ltexture_cache_debug_render_3:\n\t"
      "leal -0x8(%%esi), %%eax\n\t"
      "leal -0x1c(%%ebp), %%ecx\n\t"
      "movl %%edi, %%edx\n\t"
      "call *%[c1bef80]\n\t"
      "flds 0x506564\n\t"
      "fmuls -0x14(%%ebp)\n\t"
      "addl $8, %%edi\n\t"
      "flds 0x506560\n\t"
      "addl $0xc, %%esi\n\t"
      "fmuls -0x18(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds 0x50655c\n\t"
      "fmuls -0x1c(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fdivrs -0x24(%%ebp)\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fadds (%%eax)\n\t"
      "fstps (%%eax)\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "flds -0x18(%%ebp)\n\t"
      "decl %%eax\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "fadds -0x10(%%esi)\n\t"
      "fstps -0x10(%%esi)\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fadds -0xc(%%esi)\n\t"
      "fstps -0xc(%%esi)\n\t"
      "fstp %%st(0)\n\t"
      "jne .Ltexture_cache_debug_render_3\n\t"
      "movl -0x34(%%ebp,%%ebx,4), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x54(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x60(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $1\n\t"
      "call *%[c189270]\n\t"
      "movl -0x38(%%ebp), %%edi\n\t"
      "movl -0xc(%%ebp), %%esi\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "addl $0x10, %%esp\n\t"
      ".Ltexture_cache_debug_render_4:\n\t"
      "incl %%ebx\n\t"
      "cmpl $3, %%ebx\n\t"
      "jl .Ltexture_cache_debug_render_2\n\t"
      "incl %%eax\n\t"
      "cmpl $0x580, %%eax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "jl .Ltexture_cache_debug_render_1\n\t"
      ".Ltexture_cache_debug_render_5:\n\t"
      "movb 0x4ea989, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Ltexture_cache_debug_render_12\n\t"
      "movl 0x4ea978, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x34(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "call *%[c1197b0]\n\t"
      "leal -0x34(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c119810]\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Ltexture_cache_debug_render_8\n\t"
      ".Ltexture_cache_debug_render_6:\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "cmpl $-1, 0x20(%%eax)\n\t"
      "je .Ltexture_cache_debug_render_7\n\t"
      "movswl %%bx, %%ecx\n\t"
      "movl %%eax, 0x4e9378(,%%ecx,4)\n\t"
      "incl %%ebx\n\t"
      ".Ltexture_cache_debug_render_7:\n\t"
      "leal -0x34(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c119810]\n\t"
      "addl $4, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Ltexture_cache_debug_render_6\n\t"
      ".Ltexture_cache_debug_render_8:\n\t"
      "movswl %%bx, %%esi\n\t"
      "pushl $0x1becc0\n\t"
      "pushl %%esi\n\t"
      "pushl $0x4e9378\n\t"
      "call *%[c91ef0]\n\t"
      "pushl $1\n\t"
      "call *%[cdeca0]\n\t"
      "movl %%eax, %%edi\n\t"
      "movw 0x32565e, %%ax\n\t"
      "movw %%ax, -0x8(%%ebp)\n\t"
      "addw $0x6e, %%ax\n\t"
      "movw %%ax, -0x6(%%ebp)\n\t"
      "leal -0x8(%%ebp), %%eax\n\t"
      "pushl $2\n\t"
      "pushl %%eax\n\t"
      "call *%[c19b560]\n\t"
      "addl $0x18, %%esp\n\t"
      "cmpl $-1, %%edi\n\t"
      "je .Ltexture_cache_debug_render_9\n\t"
      "pushl %%edi\n\t"
      "call *%[c19b7e0]\n\t"
      "addl $4, %%esp\n\t"
      ".Ltexture_cache_debug_render_9:\n\t"
      "decl %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jl .Ltexture_cache_debug_render_12\n\t"
      "movl %%edi, %%edi\n\t"
      ".Ltexture_cache_debug_render_10:\n\t"
      "movl 0x4e9378(,%%esi,4), %%ecx\n\t"
      "movl 0x24(%%ecx), %%edx\n\t"
      "movl 0x4ea980, %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c11da30]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "movl $0x25386f, %%edi\n\t"
      "jne .Ltexture_cache_debug_render_11\n\t"
      "movl $0x2686f4, %%edi\n\t"
      ".Ltexture_cache_debug_render_11:\n\t"
      "movl 0x4e9378(,%%esi,4), %%ecx\n\t"
      "movl 0x20(%%ecx), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c1ba1f0]\n\t"
      "addl $4, %%esp\n\t"
      "pushl %%eax\n\t"
      "movl 0x4e9378(,%%esi,4), %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[c183290]\n\t"
      "addl $4, %%esp\n\t"
      "pushl %%eax\n\t"
      "leal -0x460(%%ebp), %%ecx\n\t"
      "pushl $0x2b9874\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1d90f0]\n\t"
      "movl 0x2ee6e0, %%ecx\n\t"
      "movl %%ebx, %%eax\n\t"
      "subl %%esi, %%eax\n\t"
      "leal (%%eax,%%eax,4), %%edx\n\t"
      "leal 0x23(%%edx,%%edx,1), %%eax\n\t"
      "movw %%ax, -0x10(%%ebp)\n\t"
      "movl $0x7fff, %%eax\n\t"
      "pushl %%ecx\n\t"
      "movw $0xa, -0xe(%%ebp)\n\t"
      "movw %%ax, -0xa(%%ebp)\n\t"
      "movw %%ax, -0xc(%%ebp)\n\t"
      "call *%[c19b640]\n\t"
      "leal -0x460(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "leal -0x10(%%ebp), %%eax\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "call *%[c183e60]\n\t"
      "addl $0x2c, %%esp\n\t"
      "decl %%esi\n\t"
      "jns .Ltexture_cache_debug_render_10\n\t"
      ".Ltexture_cache_debug_render_12:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c11da60] "m"(b1bf260_c11da60), [c1bef80] "m"(b1bf260_c1bef80), [c189270] "m"(b1bf260_c189270), [c1197b0] "m"(b1bf260_c1197b0), [c119810] "m"(b1bf260_c119810), [c91ef0] "m"(b1bf260_c91ef0), [cdeca0] "m"(b1bf260_cdeca0), [c19b560] "m"(b1bf260_c19b560), [c19b7e0] "m"(b1bf260_c19b7e0), [c11da30] "m"(b1bf260_c11da30), [c1ba1f0] "m"(b1bf260_c1ba1f0), [c183290] "m"(b1bf260_c183290), [c1d90f0] "m"(b1bf260_c1d90f0), [c19b640] "m"(b1bf260_c19b640), [c183e60] "m"(b1bf260_c183e60)
      : "memory");
}
#else
#error "texture_cache_debug_render: clang naked draft required"
#endif

