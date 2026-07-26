/* 0x1b9930 — tag_loaded: linear search for a loaded tag by group/name.
 * Returns tag index from tag instance +0x0c on match; otherwise -1.
 * Requires cache tags to be available (byte flag at 0x4e4d00). If the
 * global tag-instance table pointer (0x5054f0) is NULL while tags are
 * enabled, asserts and exits. Comparison uses case-insensitive CRT
 * string compare (__stricmp). */
int tag_loaded(int group_tag, const char *name, ...)
{
  int tag_count;
  int *entry;
  short index;

  if (*(uint8_t *)0x4e4d00 == 0) {
    return -1;
  }

  if (*(int **)0x5054f0 == 0) {
    display_assert("global_tag_instances",
                   "c:\\halo\\SOURCE\\cache\\cache_files.c", 0x127, true);
    system_exit(-1);
  }

  tag_count = *(int *)(*(int *)0x4e5504 + 0xc);
  if (tag_count <= 0) {
    return -1;
  }

  index = 0;
  do {
    entry = (int *)((int)*(int **)0x5054f0 + ((int)index << 5));
    if (entry[0] == group_tag &&
        crt_stricmp(name, (const char *)entry[4]) == 0) {
      return entry[3];
    }

    index = (short)(index + 1);
  } while ((int)index < tag_count);

  return -1;
}

/* 0x1ba140 — tag_get: resolve a tag handle and return its base/data
 * pointer. Calls 0x1b9bf0 (tag_instance_resolve) with the 16-bit tag
 * index in EDI (hidden register param); that helper returns a pointer
 * to the tag instance record. The record stores the tag's own group
 * at +0, parent group at +4, grandparent group at +8, and data pointer
 * at +0x14. The group check accepts a match at any of the three levels
 * (supports parent-group lookups). Asserts if the group doesn't match
 * or if the data pointer is NULL. */
void *tag_get(int group_tag, int tag_index)
{
  int _edi = tag_index;
  int *entry;

  asm volatile("movl $0x1b9bf0, %%ecx\n\t"
               "call *%%ecx"
               : "+D"(_edi), "=a"(entry)
               :
               : "ecx", "edx", "memory", "cc");

  if (entry[0] != group_tag && entry[1] != group_tag && entry[2] != group_tag) {
    error(2, "expected tag group %08x but got %08x for datum %08x",
          group_tag, entry[0], tag_index);
    display_assert("expected tag group mismatch",
                   "c:\\halo\\SOURCE\\cache\\cache_files.c", 0xf7, true);
    system_exit(-1);
  }
  if (entry[5] == 0) {
    display_assert("can't get() a tag with a base address!",
                   "c:\\halo\\SOURCE\\cache\\cache_files.c", 0xfb, true);
    system_exit(-1);
  }
  return (void *)entry[5];
}

/* 0x1ba1f0 — tag_get_name: return the name string for a tag by index.
 * Calls tag_instance_resolve (0x1b9bf0) with the tag index in EDI,
 * then reads the name pointer at offset +0x10 of the tag instance record. */
const char *tag_get_name(int tag_index)
{
  int _edi = tag_index;
  int *entry;

  asm volatile("movl $0x1b9bf0, %%ecx\n\t"
               "call *%%ecx"
               : "+D"(_edi), "=a"(entry)
               :
               : "ecx", "edx", "memory", "cc");

  return (const char *)entry[4];
}

/* 0x1ba210 — tag_get_group_tag: return the primary group tag (4CC class
 * identifier) for a tag by index. Calls tag_instance_resolve (0x1b9bf0)
 * with the tag index in EDI, then reads the group tag at offset +0x00
 * of the tag instance record. */
int tag_get_group_tag(int tag_index)
{
  int *entry;

  entry = tag_instance_resolve(tag_index);
  return entry[0];
}
/* --- tags.obj batch drafts (2026-07-26) --- */

/* 0x1b9fa0 */
void FUN_001b9fa0(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;

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

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
}

/* 0x1ba0c0 */
void FUN_001ba0c0(void *element)
{
  int eax = 0;
  int esi = 0;
  int edi = 0;

  structure_bsp_header_deregister_vertex_buffers((void *)(uintptr_t)eax);
  tag_instance_resolve(0);
  /* cmp eax, edi -> jne 0x1ba109 */
  display_assert((char *)0x002b8188, (char *)0x002b7dc8, 205, 0);
  system_exit(0);
  /* relift: cmp dword ptr [esi], 0x73627370 -> je 0x1ba131 */
  display_assert((char *)0x002b80dc, (char *)0x002b7dc8, 206, 0);
  system_exit(0);
  /* mem[0x004e5508] = edi */

  (void)eax;
  (void)esi;
  (void)edi;
}

/* 0x1ba250 */
void FUN_001ba250(void)
{
  SetThreadPriority(0, 0);
  SetThreadPriority(0, 0);
}

/* 0x1ba290 */
void FUN_001ba290(void)
{
  SetThreadPriority(0, 0);
  SetThreadPriority(0, 0);
  WaitForSingleObject(0, 0);
}

/* 0x1ba2f0 */
void FUN_001ba2f0(int buffer, int size, int dest_file, int dest_file_size, const char *source_file_name)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int edi = 0;
  int ebp = 0;

  WaitForSingleObject(0, 0);
  /* test eax, eax -> jne 0x1ba5a9 */
  /* test eax, eax -> jne 0x1ba335 */
  display_assert((char *)0x002b8388, (char *)0x002b839c, 524, 0);
  system_exit(0);
  /* cmp edi, -1 -> jne 0x1ba35e */
  display_assert((char *)0x002b8360, (char *)0x002b839c, 525, 0);
  system_exit(0);
  /* test ebx, ebx -> jne 0x1ba385 */
  display_assert((char *)0x00267900, (char *)0x002b839c, 526, 0);
  system_exit(0);
  /* relift: cmp dword ptr [ebp + 0xc], 0x512000 -> jge 0x1ba3ae */
  display_assert((char *)0x002b8344, (char *)0x002b839c, 527, 0);
  system_exit(0);
  GetFileSize(0, (void *)0);
  /* relift: cmp dword ptr [ebp + 0x14], eax -> je 0x1ba3db */
  display_assert((char *)0x002b8308, (char *)0x002b839c, 528, 0);
  system_exit(0);
  /* test ecx, ecx -> jne 0x1ba40f */
  display_assert((char *)0x002b82e4, (char *)0x002b839c, 530, 0);
  system_exit(0);
  /* test ecx, ecx -> jne 0x1ba43e */
  display_assert((char *)0x002b82c4, (char *)0x002b839c, 531, 0);
  system_exit(0);
  /* test ecx, ecx -> jne 0x1ba46d */
  display_assert((char *)0x002b82a4, (char *)0x002b839c, 532, 0);
  system_exit(0);
  /* test ecx, ecx -> jne 0x1ba49c */
  display_assert((char *)0x002b8280, (char *)0x002b839c, 533, 0);
  system_exit(0);
  /* test ecx, ecx -> jne 0x1ba4cb */
  display_assert((char *)0x002b8264, (char *)0x002b839c, 535, 0);
  system_exit(0);
  /* test ecx, ecx -> jne 0x1ba4fa */
  display_assert((char *)0x002b8244, (char *)0x002b839c, 537, 0);
  system_exit(0);
  /* test ecx, ecx -> jne 0x1ba529 */
  display_assert((char *)0x002b8224, (char *)0x002b839c, 538, 0);
  system_exit(0);
  csstrcpy((char *)(uintptr_t)eax, (char *)(uintptr_t)edx);
  ResetEvent();
  ResetEvent();
  csmemset((void *)(uintptr_t)eax, 0, 0);
  SetEvent((void *)(uintptr_t)edx);
  display_assert((char *)0x002b81fc, (char *)0x002b839c, 564, 0);
  system_exit(0);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)edi;
  (void)ebp;
}

/* 0x1ba5d0 */
void FUN_001ba5d0(void)
{
  int eax = 0;

  WaitForSingleObject(0, 0);
  /* test eax, eax -> je 0x1ba5f9 */
  SetEvent((void *)(uintptr_t)eax);
  FUN_001155c0(0, (char *)0x0028ce40, 56);
  FUN_00115430(0);

  (void)eax;
}

/* 0x1ba660 */
void cache_copy_compressed_alloc(void)
{
  int eax = 0;
  int ecx = 0;

  /* relift: cmp eax, dword ptr [ecx + 0x944] -> jl 0x1ba6ad */
  display_assert((char *)0x002b83d8, (char *)0x002b839c, 701, 0);
  system_exit(0);

  (void)eax;
  (void)ecx;
}

/* 0x1ba6c0 */
void FUN_001ba6c0(void)
{
  int ecx = 0;
  int esi = 0;

  /* cmp esi, ecx -> jbe 0x1ba6fb */
  display_assert((char *)0x002b842c, (char *)0x002b839c, 710, 0);
  system_exit(0);

  (void)ecx;
  (void)esi;
}

/* 0x1ba710 */
void FUN_001ba710(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;

  physical_memory_protect((void *)(uintptr_t)eax, 0x00512000, 0);
  csmemset((void *)(uintptr_t)ecx, 253, 0x00500000);
  physical_memory_protect((void *)(uintptr_t)edx, 0x00500000, 0);
  csmemset((void *)(uintptr_t)esi, 0, 0);

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
}

/* 0x1ba7c0 */
void cache_copy_initialize_and_fill_with_garbage(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  CreateFileA((char *)(uintptr_t)esi, 0x80000000, edi, edi, 0, 0x60000000, edi);
  GetFileSize(0, (void *)(uintptr_t)edi);
  csmemset((void *)(uintptr_t)eax, 0, 220);
  /* cmp eax, 0x800 -> jae 0x1ba839 */
  display_assert((char *)0x002b845c, (char *)0x002b839c, 964, 0);
  system_exit(0);
  csmemset((void *)(uintptr_t)ecx, 0, 0);
  csmemset((void *)(uintptr_t)edx, 0, 0);

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x1ba8b0 */
void FUN_001ba8b0(void)
{
  int eax = 0;

  FUN_001d00b9();
  /* test (char)eax, 1 -> je 0x1ba8f1 */
  display_assert((char *)0x002b84a8, (char *)0x002b839c, 1482, 0);
  system_exit(0);
  display_assert((char *)0x002b8488, (char *)0x002b839c, 1483, 0);
  system_exit(0);

  (void)eax;
}

/* 0x1ba930 */
void FUN_001ba930(void)
{
  int eax = 0;

  /* test (char)eax, 4 -> jne 0x1ba95b */
  display_assert((char *)0x002b8538, (char *)0x002b839c, 1494, 0);
  system_exit(0);
  FUN_001d00b9();
  /* test (char)eax, 4 -> je 0x1ba99c */
  display_assert((char *)0x002b84f0, (char *)0x002b839c, 1498, 0);
  system_exit(0);
  display_assert((char *)0x002b8488, (char *)0x002b839c, 1499, 0);
  system_exit(0);

  (void)eax;
}

/* 0x1ba9d0 */
void FUN_001ba9d0(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* relift: cmp word ptr [esi + edx*2 + 0xa78], (int16_t)ebx -> jne 0x1baa05 */
  /* relift: test dword ptr [esi + edx*4 + 0x998], eax -> jne 0x1baa13 */
  /* cmp (int16_t)edi, 8 -> jl 0x1ba9e0 */
  physical_memory_protect((void *)(uintptr_t)ecx, 0x00020000, 0);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x1baa50 */
void FUN_001baa50(void)
{
  int eax = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;

  /* test (int16_t)esi, (int16_t)esi -> jl 0x1baa67 */
  /* cmp (int16_t)esi, 8 -> jl 0x1baa93 */
  display_assert((char *)0x002b8580, (char *)0x002b839c, 1606, 0);
  system_exit(0);
  /* test (int16_t)esi, (int16_t)esi -> jl 0x1baaab */
  /* cmp (int16_t)esi, 1 -> jl 0x1baad6 */
  display_assert((char *)0x002b85c8, (char *)0x002b839c, 1633, 0);
  system_exit(0);
  /* test (int16_t)eax, (int16_t)eax -> jl 0x1baafb */
  /* cmp (int16_t)eax, 1 -> jl 0x1bab1b */
  display_assert((char *)0x002b85c8, (char *)0x002b839c, 1642, 0);
  system_exit(0);
  /* test esi, esi -> jle 0x1bab58 */
  /* test (char)eax, (char)eax -> jne 0x1bab4e */
  /* relift: cmp dword ptr [edi + ecx*4], 0 -> jne 0x1bab4e */
  /* cmp ecx, esi -> jl 0x1bab40 */

  (void)eax;
  (void)ecx;
  (void)esi;
  (void)edi;
}

/* 0x1bab60 */
void FUN_001bab60(void)
{
  int eax = 0;
  int esi = 0;

  /* test eax, eax -> je 0x1babb8 */
  /* test (int16_t)eax, (int16_t)eax -> je 0x1babb8 */
  SleepEx(5000, 0);
  /* cmp eax, 0xc0 -> je 0x1bab70 */
  display_assert((char *)0x002b8488, (char *)0x002b839c, 1695, 0);
  system_exit(0);
  /* test (char)eax, (char)eax -> je 0x1babe7 */
  display_assert((char *)0x002b8610, (char *)0x002b839c, 1699, 0);
  system_exit(0);
  csmemset((void *)(uintptr_t)esi, 0, 0);

  (void)eax;
  (void)esi;
}

/* 0x1bac00 */
void FUN_001bac00(void)
{
  int ecx = 0;

  csmemset((void *)0x004e5610, 0, 36);
  QueryPerformanceCounter((void *)(uintptr_t)ecx);

  (void)ecx;
}

/* 0x1bac70 */
void FUN_001bac70(void)
{
  int eax = 0;

  QueryPerformanceCounter((void *)(uintptr_t)eax);

  (void)eax;
}

/* 0x1baca0 */
void FUN_001baca0(void)
{
  int ecx = 0;

  error(0, (char *)0x002b87ac);
  error(0, (char *)0x002b878c);
  error(0, (char *)0x002b876c);
  error(0, (char *)0x002b8750);
  error(0, (char *)0x002b8724);
  error(0, (char *)0x002b8700);
  error(0, (char *)0x002b86d4);
  error(0, (char *)0x002b86a4);
  error(0, (char *)0x002b8684);
  /* test (char)ecx, (char)ecx -> jne 0x1badb4 */

  (void)ecx;
}

/* 0x1badc0 */
void cache_copy_get_status(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edi = 0;

  /* test edi, edi -> jne 0x1badff */
  display_assert((char *)0x002b87d0, (char *)0x002b839c, 574, 0);
  system_exit(0);
  /* test (char)ecx, (char)ecx -> je 0x1bae15 */
  FUN_001d0362();
  /* test ebx, ebx -> jne 0x1baed6 */
  /* test ecx, ecx -> je 0x1baed6 */
  /* test ecx, ecx -> jle 0x1baec6 */
  WaitForSingleObject(0, 0);
  WaitForSingleObject(0, 0);
  /* test eax, eax -> jne 0x1baf3d */
  /* test (char)eax, 0x41 -> jne 0x1baeb6 */
  /* test (char)ebx, 2 -> je 0x1baeee */
  /* test (char)ebx, 4 -> je 0x1baeff */
  /* test (char)ebx, 1 -> je 0x1baf17 */
  display_assert((char *)0x00255ee8, (char *)0x002b839c, 626, 0);
  system_exit(0);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edi;
}

/* 0x1baf50 */
void FUN_001baf50(void)
{
  int eax = 0;

  WaitForSingleObject(0, 0);
  /* test eax, eax -> je 0x1baf8d */
  SetEvent((void *)(uintptr_t)eax);
  WaitForSingleObject(0, 0);
  /* test (char)eax, (char)eax -> je 0x1baf9b */

  (void)eax;
}

/* 0x1bafa0 */
void FUN_001bafa0(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;

  /* test esi, esi -> jl 0x1bb0b9 */
  /* cmp esi, 0xb -> jge 0x1bb029 */
  QueryPerformanceCounter((void *)(uintptr_t)edx);
  /* cmp esi, 7 -> jg 0x1bb0b9 */
  /* test eax, eax -> jg 0x1bb062 */
  display_assert((char *)0x002b882c, (char *)0x002b839c, 1291, 0);
  system_exit(0);
  ResetEvent();
  SetEvent((void *)(uintptr_t)ecx);
  /* cmp esi, 9 -> jl 0x1bb179 */
  /* test eax, eax -> jg 0x1bb0f8 */
  display_assert((char *)0x002b8804, (char *)0x002b839c, 1300, 0);
  system_exit(0);
  csprintf((char *)0x004e5510, (char *)0x002b87dc);
  display_assert((char *)(uintptr_t)eax, (char *)0, 0, 0);
  system_exit(0);
  /* cmp esi, 9 -> jl 0x1bb165 */

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
}

/* 0x1bb190 */
void FUN_001bb190(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;

  QueryPerformanceCounter((void *)0x004e5640);
  display_assert((char *)0x002b8878, (char *)0x002b839c, 1334, 0);
  system_exit(0);
  QueryPerformanceCounter((void *)(uintptr_t)edx);
  SleepEx(0, 0);
  SetLastError(0);
  FUN_001d19e7();
  xapi_GetLastError();
  /* test esi, esi -> jne 0x1bb29e */
  /* cmp eax, 0x6f8 -> je 0x1bb222 */
  /* cmp eax, 8 -> je 0x1bb222 */
  /* cmp eax, 0x5aa -> je 0x1bb222 */
  display_assert((char *)0x002b8854, (char *)0x002b839c, 1369, 0);
  system_exit(0);
  QueryPerformanceCounter((void *)(uintptr_t)edx);
  /* mem[0x004e5614] = ecx */

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
}

/* 0x1bb2d0 */
void FUN_001bb2d0(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  QueryPerformanceCounter((void *)0x004e5648);
  display_assert((char *)0x002b8878, (char *)0x002b839c, 1411, 0);
  system_exit(0);
  QueryPerformanceCounter((void *)(uintptr_t)edx);
  SleepEx(0, 0);
  SetLastError(0);
  FUN_001d1a38();
  xapi_GetLastError();
  /* test esi, esi -> jne 0x1bb3e1 */
  /* cmp eax, 0x6f8 -> je 0x1bb365 */
  /* cmp eax, 8 -> je 0x1bb365 */
  /* cmp eax, 0x5aa -> je 0x1bb365 */
  display_assert((char *)0x002b88c0, (char *)0x002b839c, 1441, 0);
  system_exit(0);
  QueryPerformanceCounter((void *)(uintptr_t)edx);
  /* mem[0x004e5618] = ecx */
  FUN_001bb190();
  /* relift: tail-call FUN_001bb2d0(); */
  FUN_001baa50();
  /* test (int16_t)eax, (int16_t)eax -> jl 0x1bb463 */
  /* cmp (int16_t)eax, 8 -> jl 0x1bb483 */
  display_assert((char *)0x002b8580, (char *)0x002b839c, 1516, 0);
  system_exit(0);
  /* relift: cmp word ptr [eax], -1 -> je 0x1bb4ac */
  display_assert((char *)0x002b8918, (char *)0x002b839c, 1517, 0);
  system_exit(0);
  physical_memory_protect((void *)(uintptr_t)ebx, esi, 0);
  FUN_001bb190();
  display_assert((char *)0x002b88e8, (char *)0x002b839c, 1537, 0);
  system_exit(0);
  FUN_001bb430();
  /* cmp (int16_t)esi, 8 -> jl 0x1bb586 */
  display_assert((char *)0x002b8580, (char *)0x002b839c, 1561, 0);
  system_exit(0);
  FUN_001bb430();
  /* cmp (int16_t)esi, 8 -> jl 0x1bb5e1 */
  display_assert((char *)0x002b8580, (char *)0x002b839c, 1618, 0);
  system_exit(0);
  /* relift: test dword ptr [ebx], edi -> jne 0x1bb61e */
  display_assert((char *)0x002b8940, (char *)0x002b839c, 1619, 0);
  system_exit(0);
  FUN_001bb430();
  /* cmp (int16_t)esi, 1 -> jl 0x1bb678 */
  display_assert((char *)0x002b85c8, (char *)0x002b839c, 1633, 0);
  system_exit(0);
  /* cmp (int16_t)esi, 1 -> jl 0x1bb6ba */
  display_assert((char *)0x002b85c8, (char *)0x002b839c, 1642, 0);
  system_exit(0);
  /* cmp ebx, 0x400000 -> jl 0x1bb6f8 */
  /* test (int16_t)esi, (int16_t)esi -> jl 0x1bb6d3 */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}
