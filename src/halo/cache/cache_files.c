#include <stdint.h>
/* --- cache_files.obj batch drafts (2026-07-26) --- */

/* Defined in cache_files_windows.c; missing from generated decl.h. */
bool cache_files_precache_in_progress(void);

/* scenario_tags_unload (0x1b9890) — readable C lift. */
void scenario_tags_unload(void)
{
  sound_cache_close();
  texture_cache_close();
  cache_file_close();
  tags_header_deregister_vertex_and_index_buffers(*(void **)0x4e5504);
  *(unsigned char *)0x4e4d00 = 0;
  *(int *)0x5054f0 = 0;
}
/* 0x1b98c0 */
void tag_files_close(void)
{
  /* relift: no calls detected — manual review */
}

/* tag_groups_checksum (0x1b98d0) — readable C lift. */
void tag_groups_checksum(void)
{
  cache_files_dispose();
}

int FUN_001b9920(void) {
  return *(uint32_t *)0x4e4d68;
}

/* tag_instance_resolve (0x1b9bf0) — readable C lift.
 * tag_index arrives in EDI (@<edi>). Returns pointer to 0x20-byte tag instance. */
int *tag_instance_resolve(int tag_index)
{
  int *table;
  int *entry;
  int count;

  if (*(unsigned char *)0x4e4d00 == 0) {
    display_assert((const char *)0x2b7da8, (const char *)0x2b7dc8, 0x1d3, 1);
    system_exit(-1);
  }
  if (*(int *)0x5054f0 == 0) {
    display_assert((const char *)0x2b7dec, (const char *)0x2b7dc8, 0x1d4, 1);
    system_exit(-1);
  }
  count = *(int *)(*(int *)0x4e5504 + 0xc);
  if ((short)tag_index < 0 || (int)(short)tag_index >= count) {
    csprintf((char *)0x5ab100, (const char *)0x2b8000, tag_index);
    display_assert((const char *)0x5ab100, (const char *)0x2b7dc8, 0x1d7, 1);
    system_exit(-1);
  }
  table = *(int **)0x5054f0;
  entry = (int *)((char *)table + ((int)(short)tag_index << 5));
  if ((tag_index & 0xffff0000) != 0 && entry[3] != tag_index) {
    csprintf((char *)0x5ab100, (const char *)0x2b8000, tag_index);
    display_assert((const char *)0x5ab100, (const char *)0x2b7dc8, 0x1db, 1);
    system_exit(-1);
  }
  return entry;
}

/* cache_file_header_verify (0x1b9ce0) — readable C lift. */
bool cache_file_header_verify(void *header, const char *path, int report_errors)
{
  char *hdr;
  char *map_name;
  char *build;
  int file_size;

  hdr = (char *)header;
  if (*(int *)hdr != 0x68656164 || *(int *)(hdr + 0x7fc) != 0x666f6f74)
    goto bad_header;
  file_size = *(int *)(hdr + 8);
  if (file_size < 0 || file_size > 0x11600000)
    goto bad_header;
  map_name = hdr + 0x20;
  if ((unsigned int)csstrlen(map_name) > 0x1f)
    goto bad_header;
  if (*(int *)(hdr + 4) != 5) {
    if (!report_errors)
      return 0;
    csprintf((char *)0x5ab100, (const char *)0x2b8084, path);
    display_assert((const char *)0x5ab100, (const char *)0x2b7dc8, 0x1f1, 1);
    system_exit(-1);
  }
  build = hdr + 0x40;
  if (csstrcmp(build, (const char *)0x288bdc) == 0)
    return 1;
  if (!report_errors)
    return 0;
  csprintf((char *)0x5ab100, (const char *)0x2b804c, map_name, build);
  display_assert((const char *)0x5ab100, (const char *)0x2b7dc8, 0x1f6, 1);
  system_exit(-1);
  return 0;

bad_header:
  if (!report_errors)
    return 0;
  csprintf((char *)0x5ab100, (const char *)0x2b8024, path);
  display_assert((const char *)0x5ab100, (const char *)0x2b7dc8, 0x1ed, 1);
  system_exit(-1);
  return 0;
}

/* cache_files_give_time_to_precache (0x1b9de0) — readable C lift. */
bool cache_files_give_time_to_precache(const char *name)
{
  float status;
  short st;
  char ok;

  ok = 0;
  if (cache_files_precache_map_loaded((char *)name)) {
    return 1;
  }
  if (cache_files_precache_in_progress()) {
    if (!cache_files_precache_is_copying_map((char *)name)) {
      cache_files_precache_map_end();
    }
  }
  if (cache_files_precache_in_progress()) {
    st = cache_files_precache_map_status(&status);
    if (st == 2) {
      display_error_damaged_media();
      return ok;
    }
    if (st == 1) {
      cache_files_precache_map_end();
      return ok;
    }
    return ok;
  }
  cache_files_precache_set_priority(0);
  if (!cache_files_precache_map_begin((char *)name, 0)) {
    display_error_damaged_media();
  }
  return ok;
}

/* FUN_001b9e70 (0x1b9e70) — readable C lift (restored pre-naked). */
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

