#include <stdint.h>
/* --- xbox_sound_cache.obj batch drafts (2026-07-26) --- */

/* xbox_sound_cache_idle (0x1bded0) — readable C lift. */
void xbox_sound_cache_idle(void)
{
  lruv_idle(*(void **)0x4e9370);
  if (*(int16_t *)0x5054ea != 0) {
    display_assert((const char *)0x2b9260, (const char *)0x2b9288, 0x94, 1);
    system_exit(-1);
  }
}
/* sound_cache_sound_new (0x1bdf10) — readable C lift. */
void sound_cache_sound_new(void *unused, char *entry)
{
  extern char DAT_002b9288[];
  extern char DAT_002b92b0[];
  (void)unused;
  if (*(int *)(entry + 0x30) != 0) {
    display_assert(DAT_002b92b0, DAT_002b9288, 0x9e, 1);
    system_exit(-1);
  }
  *(int *)(entry + 0x2c) = -1;
  *(int *)(entry + 0x30) = 0;
  *(void **)(entry + 0x34) = unused;
}

/* FUN_001bdf60 (0x1bdf60) — readable C lift (restored pre-naked). */
void FUN_001bdf60(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* cmp eax, -1 -> je 0x1be07e */
  datum_get((void *)(uintptr_t)eax, 0);
  /* test (char)ecx, (char)ecx -> je 0x1bdfee */
  datum_get((void *)(uintptr_t)edx, 0);
  datum_get((void *)(uintptr_t)edx, 0);
  tag_get_name(0);
  csprintf((char *)0x005ab100, (char *)0x002b9320);
  display_assert((char *)(uintptr_t)eax, (char *)0, 0, 0);
  system_exit(0);
  datum_get((void *)(uintptr_t)eax, 0);
  /* test (char)ecx, (char)ecx -> je 0x1be06c */
  datum_get((void *)(uintptr_t)edx, 0);
  datum_get((void *)(uintptr_t)edx, 0);
  tag_get_name(0);
  csprintf((char *)0x005ab100, (char *)0x002b92d0);
  display_assert((char *)(uintptr_t)eax, (char *)0, 0, 0);
  system_exit(0);
  lruv_block_delete((void *)(uintptr_t)eax, 0);
  datum_get((void *)(uintptr_t)edx, 0);
  /* test (char)eax, (char)eax -> je 0x1be0cd */
  error(0, (char *)0x002b9394);
  /* test (char)eax, (char)eax -> jne 0x1be0f4 */
  display_assert((char *)0x002b936c, (char *)0x002b9288, 263, 0);
  system_exit(0);
  datum_get((void *)(uintptr_t)edx, 0);
  /* cmp (char)ecx, 0xff -> jae 0x1be128 */
  datum_get((void *)(uintptr_t)edx, 0);
  /* test (char)ecx, (char)ecx -> je 0x1be167 */
  datum_get((void *)(uintptr_t)ecx, 0);
  /* test (char)ecx, (char)ecx -> je 0x1be19f */
  /* test (char)ecx, (char)ecx -> jne 0x1be19f */
  /* test (char)ecx, (char)ecx -> jne 0x1be19f */
  datum_get((void *)(uintptr_t)eax, 0);
  /* test (char)eax, (char)eax -> jne 0x1be1d7 */
  /* test (char)eax, (char)eax -> je 0x1be216 */
  tag_get_name(0);
  csprintf((char *)0x005ab100, (char *)0x002b93e0);
  display_assert((char *)(uintptr_t)eax, (char *)0, 0, 0);
  system_exit(0);
  /* relift: cmp dword ptr [edx + 0x2c], edi -> je 0x1be23e */
  display_assert((char *)0x002b93a8, (char *)0x002b9288, 324, 0);
  system_exit(0);
  datum_delete((void *)(uintptr_t)edx, 0);
  datum_get((void *)(uintptr_t)ecx, 0);
  tag_get_name(0);
  crt_sprintf((char *)0x004e9268, (char *)0x002b9424);
  FUN_0011de10((void *)(uintptr_t)ecx, eax);
  /* cmp edi, -1 -> je 0x1be361 */
  lruv_block_get_address((void *)(uintptr_t)edx, 0);
  data_new_datum((void *)(uintptr_t)eax, 0);
  datum_get((void *)(uintptr_t)ecx, 0);
  display_assert((char *)0x002b94cc, (char *)0x002b9288, 368, 0);
  system_exit(0);
  cache_file_read(0, 0, edx, 0, (char *)(uintptr_t)eax, 0);
  system_milliseconds();
  /* cmp eax, 0x2710 -> jbe 0x1be3cd */
  terminal_output((void *)(uintptr_t)edx, (char *)0x002b9488, (char *)0);
  error(0, (char *)0x002b9440);
  terminal_output((void *)(uintptr_t)eax, (char *)0x002b9488, (char *)0);
  FUN_0011db90((char *)0x002b942c, (char *)(uintptr_t)esi, 0, (void *)(uintptr_t)ecx, (void *)0x0018ef30, (void *)0x001be270);
  system_milliseconds();
  /* mem[0x004e9374] = eax */

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}


/* sound_cache_new (0x1be3e0) — readable C lift. */
void sound_cache_new(void)
{
  void *data;
  void *lruv;
  int mem;

  data = data_new((char *)0x2b957c, 0x200, 0xc);
  *(void **)0x4e9368 = data;
  if (data == NULL) {
    display_assert((const char *)0x2b9554, (const char *)0x2b9288, 0x45, 1);
    system_exit(-1);
  }
  lruv = lruv_new((int)0x2b9540, 0x400, 0xc, 0x200,
                  (void (*)(int))FUN_001be1b0, (int (*)(int))FUN_001be170);
  *(void **)0x4e9370 = lruv;
  if (lruv == NULL) {
    display_assert((const char *)0x2b9520, (const char *)0x2b9288, 0x49, 1);
    system_exit(-1);
  }
  mem = FUN_001bdd70();
  *(int *)0x4e936c = mem;
  if (mem == 0) {
    display_assert((const char *)0x2b94f8, (const char *)0x2b9288, 0x4c, 1);
    system_exit(-1);
  }
}

/* sound_cache_flush (0x1be490) — readable C lift. */
void sound_cache_flush(void)
{
  data_iter_t iter;
  void *entry;

  data_iterator_new(&iter, *(data_t **)0x4e9368);
  for (entry = data_iterator_next(&iter); entry != 0; entry = data_iterator_next(&iter)) {
    if (*(unsigned char *)((char *)entry + 4) != 0)
      continue;
    if (*(unsigned char *)((char *)entry + 5) != 0)
      continue;
    ((void (*)(void *))FUN_001bdf60)(*(void **)((char *)entry + 8));
  }
}

/* sound_cache_close (0x1be4f0) — readable C lift. */
void sound_cache_close(void)
{
  data_iter_t iter;
  void *entry;

  data_iterator_new(&iter, *(data_t **)0x4e9368);
  for (entry = data_iterator_next(&iter); entry != 0; entry = data_iterator_next(&iter))
    ((void (*)(void *))FUN_001bdf60)(*(void **)((char *)entry + 8));
  data_make_invalid(*(data_t **)0x4e9368);
}

/* sound_cache_request_sound (0x1be550) — Capstone tip: !load && force → assert.
 * When a3==0 and a2!=0: display_assert(..., 0xc2) + exit. */
int sound_cache_request_sound(void *permutation, int a2, int a3, int a4)
{
  (void)permutation;
  (void)a4;
  if (a3 == 0 && a2 != 0) {
    display_assert((const char *)0x2b9604, (const char *)0x2b9288, 0xc2, true);
    system_exit(-1);
  }
  return 0;
}



/* FUN_001be6b0 (0x1be6b0) — readable C lift.
 * out_a@eax, out_c@ecx, uv@edx */
void FUN_001be6b0(float *out_a, float *out_c, float *uv)
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

/* FUN_001be7b0 (0x1be7b0) — readable C lift (restored pre-naked). */
void FUN_001be7b0(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;

  /* test (char)eax, (char)eax -> je 0x1be91c */
  lruv_cache_get_page_usage((void *)(uintptr_t)edx, (unsigned char *)(uintptr_t)ecx);
  /* test dl, (char)eax -> je 0x1be8fc */
  ((void(*)(void))FUN_001be6b0)();
  FUN_00189270(0, (float *)(uintptr_t)eax, (float *)(uintptr_t)edx, (void *)(uintptr_t)ecx);
  data_dispose((void *)(uintptr_t)eax);
  lruv_cache_dispose((void *)(uintptr_t)ecx);
  data_delete_all((void *)(uintptr_t)eax);
  lruv_idle((void *)(uintptr_t)eax);
  display_assert((char *)0x002b96a8, (char *)0x002b96d8, 157, 0);
  system_exit(0);
  tag_get('mtib', 0);
  bitmap_get_pixel_data_size((void *)(uintptr_t)esi);
  /* cmp eax, -1 -> je 0x1bea15 */
  lruv_block_delete((void *)(uintptr_t)eax, 0);
  FUN_001bdd60();
  display_assert((char *)0x002b9730, (char *)0x002b96d8, 319, 0);
  system_exit(0);
  /* test (char)eax, (char)eax -> je 0x1beab7 */
  display_assert((char *)0x002b9704, (char *)0x002b96d8, 320, 0);
  system_exit(0);
  lruv_resize((void *)(uintptr_t)edx, 0);
  physical_memory_protect((void *)(uintptr_t)esi, esi, 0);
  physical_memory_protect((void *)(uintptr_t)ebx, 0x00104000, 0);
  physical_memory_protect((void *)(uintptr_t)eax, 0x00104000, 0);
  /* test (char)eax, (char)eax -> jne 0x1beb39 */
  display_assert((char *)0x002b9748, (char *)0x002b96d8, 345, 0);
  system_exit(0);
  lruv_resize((void *)(uintptr_t)eax, 1408);
  FUN_001bdd60();
  physical_memory_protect((void *)(uintptr_t)eax, 0, 0);
  datum_get((void *)(uintptr_t)ecx, 0);
  tag_get_name(0);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
}


