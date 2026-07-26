/* --- cache_files.obj batch drafts (2026-07-26) --- */

/* 0x1b9890 */
void scenario_tags_unload(void)
{
  int eax = 0;

  sound_cache_close();
  texture_cache_close();
  cache_file_close();
  tags_header_deregister_vertex_and_index_buffers((void *)(uintptr_t)eax);
  /* mem[0x005054f0] = eax */

  (void)eax;
}

/* 0x1b98c0 */
void tag_files_close(void)
{
  /* relift: no calls detected — manual review */
}

/* 0x1b98d0 */
void tag_groups_checksum(void)
{
  int eax = 0;

  /* test (char)eax, (char)eax -> jne 0x1b9912 */
  display_assert((char *)0x002b7da8, (char *)0x002b7dc8, 276, 0);
  system_exit(0);

  (void)eax;
}

/* 0x1b9920 */
int FUN_001b9920(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int edi = 0;

  /* test (char)eax, (char)eax -> je 0x1b99d2 */
  /* test eax, eax -> jne 0x1b996f */
  display_assert((char *)0x002b7dec, (char *)0x002b7dc8, 295, 0);
  system_exit(0);
  /* test ecx, ecx -> jle 0x1b99d2 */
  /* relift: cmp edi, dword ptr [eax] -> jne 0x1b99a5 */
  crt_stricmp((char *)(uintptr_t)ebx, (char *)(uintptr_t)edx);
  /* test eax, eax -> je 0x1b99be */
  /* cmp eax, edx -> jl 0x1b9985 */
  physical_memory_protect((void *)0x803a6000, 0x01600000, 0);
  physical_memory_protect((void *)0x803a6000, 0x01600000, 0);
  physical_memory_protect((void *)(uintptr_t)ecx, eax, 0);
  physical_memory_protect((void *)(uintptr_t)eax, edx, 0);
  /* test eax, eax -> je 0x1b9a80 */
  physical_memory_protect((void *)(uintptr_t)edx, ecx, 0);
  physical_memory_protect((void *)(uintptr_t)ecx, eax, 0);
  error(0, (char *)0x002b7e04);
  error(0, (char *)0x002b7e44);
  error(0, (char *)0x002b7e80);
  error(0, (char *)0x002b7ec8);
  error(0, (char *)0x002b7f10);
  error(0, (char *)0x002b7f48);
  error(0, (char *)0x002b7f80);
  error(0, (char *)0x002b7fc0);
  /* cmp ecx, edi -> jge 0x1b9be9 */
  /* cmp edx, -1 -> je 0x1b9be6 */
  /* relift: cmp edx, dword ptr [ecx] -> je 0x1b9be6 */
  /* relift: cmp edx, dword ptr [ecx + 4] -> je 0x1b9be6 */
  /* relift: cmp edx, dword ptr [ecx + 8] -> je 0x1b9be6 */
  /* relift: cmp ecx, dword ptr [edx + 0xc] -> jl 0x1b9ba0 */
  return 0;

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)edi;
}

/* 0x1b9bf0 */
int *tag_instance_resolve(int tag_index)
{
  int eax = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* test (char)eax, (char)eax -> jne 0x1b9c19 */
  display_assert((char *)0x002b7da8, (char *)0x002b7dc8, 467, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x1b9c42 */
  display_assert((char *)0x002b7dec, (char *)0x002b7dc8, 468, 0);
  system_exit(0);
  /* test (int16_t)edi, (int16_t)edi -> jl 0x1b9c57 */
  /* cmp eax, edx -> jl 0x1b9c86 */
  csprintf((char *)0x005ab100, (char *)0x002b8000);
  display_assert((char *)(uintptr_t)eax, (char *)0, 0, 0);
  system_exit(0);
  /* test edi, 0xffff0000 -> je 0x1b9cd1 */
  /* relift: cmp dword ptr [esi + 0xc], edi -> je 0x1b9cd1 */
  csprintf((char *)0x005ab100, (char *)0x002b8000);
  display_assert((char *)(uintptr_t)eax, (char *)0, 0, 0);
  system_exit(0);
  return NULL;

  (void)eax;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x1b9ce0 */
bool cache_file_header_verify(void *header, const char *path, int report_errors)
{
  int eax = 0;
  int esi = 0;
  int edi = 0;

  /* relift: cmp dword ptr [esi + 0x7fc], 0x666f6f74 -> jne 0x1b9d93 */
  /* test eax, eax -> jl 0x1b9d93 */
  /* cmp eax, 0x11600000 -> jg 0x1b9d93 */
  csstrlen((char *)(uintptr_t)edi);
  /* cmp eax, 0x1f -> ja 0x1b9d93 */
  /* relift: cmp dword ptr [esi + 4], 5 -> je 0x1b9d4f */
  /* test (char)eax, (char)eax -> je 0x1b9dcc */
  csstrcmp((char *)(uintptr_t)esi, (char *)0x00288bdc);
  /* test eax, eax -> je 0x1b9d8d */
  /* test (char)eax, (char)eax -> je 0x1b9dcc */
  csprintf((char *)0x005ab100, (char *)0x002b804c);
  /* test (char)eax, (char)eax -> je 0x1b9dcc */
  csprintf((char *)0x005ab100, (char *)0x002b8024);
  display_assert((char *)(uintptr_t)eax, (char *)0, 0, 0);
  system_exit(0);
  return 0;

  (void)eax;
  (void)esi;
  (void)edi;
}

/* 0x1b9de0 */
bool cache_files_give_time_to_precache(const char *name)
{
  int eax = 0;
  int esi = 0;

  cache_files_precache_map_loaded((char *)(uintptr_t)esi);
  /* test (char)eax, (char)eax -> je 0x1b9e00 */
  cache_files_precache_in_progress();
  /* test (char)eax, (char)eax -> je 0x1b9e1b */
  cache_files_precache_is_copying_map((char *)(uintptr_t)esi);
  /* test (char)eax, (char)eax -> jne 0x1b9e1b */
  cache_files_precache_map_end();
  cache_files_precache_in_progress();
  /* test (char)eax, (char)eax -> je 0x1b9e49 */
  cache_files_precache_map_status((float *)(uintptr_t)eax);
  /* cmp (int16_t)eax, 2 -> je 0x1b9e5f */
  /* cmp (int16_t)eax, 1 -> jne 0x1b9e64 */
  cache_files_precache_map_end();
  cache_files_precache_set_priority(0);
  cache_files_precache_map_begin((char *)(uintptr_t)esi, 0);
  /* test (char)eax, (char)eax -> jne 0x1b9e64 */
  display_error_damaged_media();
  return 0;

  (void)eax;
  (void)esi;
}

/* 0x1b9e70 */
void FUN_001b9e70(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  tag_name_strip_path((char *)(uintptr_t)edi);
  texture_cache_open();
  FUN_001bdec0();
  cache_file_open();
  /* test (char)eax, (char)eax -> je 0x1b9f91 */
  FUN_001bdd50();
  cache_file_header_verify((void *)0x004e4d04, (char *)(uintptr_t)edi, 0);
  /* test (char)eax, (char)eax -> je 0x1b9f91 */
  csmemset((void *)(uintptr_t)esi, 205, 0x01600000);
  cache_file_read(0, 0, ecx, 0, (char *)(uintptr_t)eax, 0);
  /* test (char)eax, (char)eax -> jne 0x1b9f0c */
  SwitchToThread();
  /* test (char)eax, (char)eax -> je 0x1b9f00 */
  /* mem[0x004e5504] = eax */
  /* cmp ecx, 0x74616773 -> je 0x1b9f69 */
  csprintf((char *)0x005ab100, (char *)0x002b80ac);
  display_assert((char *)(uintptr_t)eax, (char *)0, 0, 0);
  system_exit(0);
  /* mem[0x005054f0] = ecx */
  tags_header_register_vertex_and_index_buffers((void *)(uintptr_t)eax);
  FUN_001bdd50();
  csmemset((void *)(uintptr_t)ecx, 205, 0);
  cache_file_read(0, 0, edx, 0, (char *)(uintptr_t)eax, 0);
  /* test (char)eax, (char)eax -> jne 0x1ba014 */
  SwitchToThread();
  sound_render_time();
  system_milliseconds();
  /* cmp eax, 0x21 -> jbe 0x1ba00d */
  sound_idle();
  /* test (char)eax, (char)eax -> je 0x1b9ff0 */
  /* mem[0x004e5508] = eax */
  /* relift: cmp dword ptr [eax + 0x14], 0x73627370 -> je 0x1ba04a */
  display_assert((char *)0x002b8128, (char *)0x002b7dc8, 173, 0);
  system_exit(0);
  structure_bsp_header_register_vertex_buffers((void *)(uintptr_t)eax);
  tag_instance_resolve(0);
  /* test eax, eax -> je 0x1ba084 */
  display_assert((char *)0x002b8108, (char *)0x002b7dc8, 183, 0);
  system_exit(0);
  /* relift: cmp dword ptr [esi], 0x73627370 -> je 0x1ba0ac */
  display_assert((char *)0x002b80dc, (char *)0x002b7dc8, 184, 0);
  system_exit(0);
  structure_bsp_header_deregister_vertex_buffers((void *)(uintptr_t)eax);
  tag_instance_resolve(0);
  /* cmp eax, edi -> jne 0x1ba109 */
  display_assert((char *)0x002b8188, (char *)0x002b7dc8, 205, 0);
  system_exit(0);
  /* relift: cmp dword ptr [esi], 0x73627370 -> je 0x1ba131 */
  display_assert((char *)0x002b80dc, (char *)0x002b7dc8, 206, 0);
  system_exit(0);
  /* mem[0x004e5508] = edi */
  tag_instance_resolve(0);
  /* cmp eax, ebx -> je 0x1ba1b1 */
  /* relift: cmp dword ptr [esi + 4], ebx -> je 0x1ba1b1 */
  /* relift: cmp dword ptr [esi + 8], ebx -> je 0x1ba1b1 */
  tag_to_string(eax, (void *)(uintptr_t)ecx);
  tag_to_string(ebx, (void *)(uintptr_t)edx);
  csprintf((char *)0x005ab100, (char *)0x002b81cc);
  display_assert((char *)(uintptr_t)eax, (char *)0, 0, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x1ba1e6 */
  csprintf((char *)0x005ab100, (char *)0x002b81a4);
  display_assert((char *)(uintptr_t)eax, (char *)0, 0, 0);
  system_exit(0);
  tag_instance_resolve(0);
  tag_instance_resolve(0);
  WaitForSingleObject(0, 0);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}
