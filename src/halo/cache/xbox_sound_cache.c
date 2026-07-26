/* --- xbox_sound_cache.obj batch drafts (2026-07-26) --- */

/* 0x1bded0 */
void xbox_sound_cache_idle(void)
{
  int eax = 0;

  lruv_idle((void *)(uintptr_t)eax);
  /* relift: cmp word ptr [0x5054ea], 0 -> je 0x1bdf08 */
  display_assert((char *)0x002b9260, (char *)0x002b9288, 148, 0);
  system_exit(0);

  (void)eax;
}

/* 0x1bdf10 */
void sound_cache_sound_new(void)
{
  int eax = 0;

  /* test eax, eax -> je 0x1bdf3e */
  display_assert((char *)0x002b92b0, (char *)0x002b9288, 158, 0);
  system_exit(0);

  (void)eax;
}

/* 0x1bdf60 */
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

/* 0x1be3e0 */
void sound_cache_new(void)
{
  int eax = 0;

  data_new((char *)0x002b957c, 512, 12);
  /* mem[0x004e9368] = eax */
  display_assert((char *)0x002b9554, (char *)0x002b9288, 69, 0);
  system_exit(0);
  lruv_new(0x002b9540, 1024, 12, 512, (void *)0x001be1b0, (void *)0x001be170);
  /* mem[0x004e9370] = eax */
  display_assert((char *)0x002b9520, (char *)0x002b9288, 73, 0);
  system_exit(0);
  FUN_001bdd70();
  /* mem[0x004e936c] = eax */
  display_assert((char *)0x002b94f8, (char *)0x002b9288, 76, 0);
  system_exit(0);

  (void)eax;
}

/* 0x1be490 */
void sound_cache_flush(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;

  data_iterator_new((void *)(uintptr_t)ecx, (void *)(uintptr_t)eax);
  data_iterator_next((void *)(uintptr_t)edx);
  /* test eax, eax -> je 0x1be4df */
  /* test (char)ecx, (char)ecx -> jne 0x1be4cf */
  /* test (char)ecx, (char)ecx -> jne 0x1be4cf */
  FUN_001bdf60();
  data_iterator_next((void *)(uintptr_t)ecx);
  /* test eax, eax -> jne 0x1be4b5 */

  (void)eax;
  (void)ecx;
  (void)edx;
}

/* 0x1be4f0 */
void sound_cache_close(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;

  data_iterator_new((void *)(uintptr_t)ecx, (void *)(uintptr_t)eax);
  data_iterator_next((void *)(uintptr_t)edx);
  /* test eax, eax -> je 0x1be52e */
  FUN_001bdf60();
  data_iterator_next((void *)(uintptr_t)ecx);
  /* test eax, eax -> jne 0x1be515 */
  data_make_invalid((void *)(uintptr_t)edx);

  (void)eax;
  (void)ecx;
  (void)edx;
}

/* 0x1be550 */
int sound_cache_request_sound(void *permutation, int a2, int a3, int a4)
{
  int eax = 0;
  int ebx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* test (char)eax, (char)eax -> je 0x1be588 */
  display_assert((char *)0x002b9604, (char *)0x002b9288, 194, 0);
  system_exit(0);
  /* test (char)eax, (char)eax -> je 0x1be5af */
  display_assert((char *)0x002b95f0, (char *)0x002b9288, 196, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x1be5d9 */
  display_assert((char *)0x002b95d4, (char *)0x002b9288, 198, 0);
  system_exit(0);
  /* relift: cmp dword ptr [esi + 0x2c], -1 -> jne 0x1be5e8 */
  /* test (char)ebx, (char)ebx -> je 0x1be5e8 */
  FUN_001be2b0((void *)0);
  /* cmp eax, -1 -> je 0x1be6a3 */
  lruv_debug_to_file((void *)(uintptr_t)eax, 0);
  datum_get((void *)(uintptr_t)edx, 0);
  /* test (char)eax, (char)eax -> jne 0x1be636 */
  SwitchToThread();
  /* test (char)eax, (char)eax -> jne 0x1be604 */
  /* test (char)eax, (char)eax -> jne 0x1be649 */
  /* test (char)eax, (char)eax -> je 0x1be69a */
  /* test (char)eax, (char)eax -> je 0x1be671 */
  error(0, (char *)0x002b95c0);
  /* relift: cmp byte ptr [edi + 4], 0xff -> jb 0x1be697 */
  display_assert((char *)0x002b9588, (char *)0x002b9288, 236, 0);
  system_exit(0);
  return 0;

  (void)eax;
  (void)ebx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x1be6b0 */
void FUN_001be6b0(void)
{
  /* relift: no calls detected — manual review */
}

/* 0x1be7b0 */
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
  FUN_001be6b0();
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
