/* Freestanding TU compile: SleepEx lives in xdk_stubs_rt.c. */
unsigned int __stdcall SleepEx(unsigned int milliseconds, int alertable);

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
    error(2, "expected tag group %08x but got %08x for datum %08x", group_tag,
          entry[0], tag_index);
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
/* FUN_001b9fa0 (0x1b9fa0) — Capstone tip: structure_bsp tag mismatch → assert. */
char FUN_001b9fa0(void *ctx)
{
  unsigned int *slot;
  (void)ctx;
  slot = *(unsigned int **)0x4e5508;
  if (slot[5] != 0x73627370u) {
    display_assert((const char *)0x2b8128, (const char *)0x2b7dc8, 0xad, true);
    system_exit(-1);
  }
  return 1;
}


/* FUN_001ba0c0 (0x1ba0c0) — readable C lift. */
void FUN_001ba0c0(void *element)
{
  extern char DAT_002b8188[];
  extern char DAT_002b7dc8[];
  extern char DAT_002b80dc[];
  int *inst;

  structure_bsp_header_deregister_vertex_buffers(*(void **)0x4e5508);
  inst = tag_instance_resolve(*(int *)((char *)element + 0x1c));
  if (!inst[5]) {
    display_assert(DAT_002b8188, DAT_002b7dc8, 0xcd, 1);
    system_exit(-1);
  }
  if (inst[0] != 0x73627370) {
    display_assert(DAT_002b80dc, DAT_002b7dc8, 0xce, 1);
    system_exit(-1);
  }
  inst[5] = 0;
  *(int *)0x4e5508 = 0;
}


/* FUN_001ba250 (0x1ba250) — readable C lift. */
void *FUN_001ba250(unsigned char enable)
{
  char *base = *(char **)0x32ea98;
  base[0x988] = (char)enable;
  if (enable) {
    SetThreadPriority(*(int *)(base + 0x95c), 1);
  } else {
    SetThreadPriority(*(int *)(base + 0x95c), 0);
  }
  return (void *)0x512000;
}

/* FUN_001ba290 (0x1ba290) — readable C lift. */
void FUN_001ba290(unsigned char enable)
{
  char *base = *(char **)0x32ea98;
  base[0x988] = (char)enable;
  if (enable) {
    SetThreadPriority(*(int *)(base + 0x95c), 1);
  } else {
    SetThreadPriority(*(int *)(base + 0x95c), 0);
  }
}

/* FUN_001ba2f0 (0x1ba2f0) — readable C lift (restored pre-naked). */
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
  ((void(*)(void))ResetEvent)();
  ((void(*)(void))ResetEvent)();
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



/* FUN_001ba5d0 (0x1ba5d0) — readable C lift. */
void FUN_001ba5d0(void)
{
  char *base = *(char **)0x32ea98;
  if (WaitForSingleObject(*(int *)(base + 0x954), 0) != 0) {
    SetEvent(*(void **)(base + 0x950));
  }
}

/* cache_copy_compressed_alloc (0x1ba660) — readable C lift. */
void *cache_copy_compressed_alloc(int unused, int a, int b)
{
  extern char DAT_002b83d8[];
  extern char DAT_002b839c[];
  char *base = *(char **)0x32ea98;
  int old;
  int total;
  (void)unused;
  old = *(int *)(base + 0x948);
  total = old + a * b;
  *(int *)(base + 0x948) = total;
  if (total - *(int *)(base + 0x940) >= *(int *)(base + 0x944)) {
    display_assert(DAT_002b83d8, DAT_002b839c, 0x2bd, 1);
    system_exit(-1);
  }
  return (void *)(uintptr_t)old;
}

/* FUN_001ba6c0 (0x1ba6c0) — readable C lift. */
void FUN_001ba6c0(int unused, unsigned int value)
{
  extern char DAT_002b842c[];
  extern char DAT_002b839c[];
  char *base = *(char **)0x32ea98;
  (void)unused;
  if (value > *(unsigned int *)(base + 0x948)) {
    display_assert(DAT_002b842c, DAT_002b839c, 0x2c6, 1);
    system_exit(-1);
    base = *(char **)0x32ea98;
  }
  *(unsigned int *)(base + 0x948) = value;
}

/* FUN_001ba710 (0x1ba710) — readable C lift from XBE leaf.
 * cache@eax: init 8x 128KB page slots on global copy state, protect/fill
 * 5MB cache buffer with 0xfd, then zero a 0x1c0 trailer with 0xfa.
 * Delinked per-fn oracle keeps size/0x12000 as immediates (not DIR32). */
void FUN_001ba710(void *cache)
{
  unsigned char *g;
  unsigned int base;
  unsigned int *slot;
  int i;
  unsigned int end;

  g = *(unsigned char **)0x32ea98;
  base = *(unsigned int *)((char *)cache + 0x960);
  slot = (unsigned int *)(g + 0x964);
  for (i = 0; i < 8; i++) {
    slot[i] = base;
    base += 0x20000u;
  }
  *(unsigned int *)(g + 0x984) = base;

  base = *(unsigned int *)((char *)cache + 0x960);
  physical_memory_protect((void *)base, 0x512000u, 4u);
  csmemset((void *)base, 0xfd, 0x500000u);
  physical_memory_protect((void *)base, 0x500000u, 2u);

  end = base + 0x500000u;
  *(unsigned int *)((char *)cache + 0x944) = 0x12000u;
  *(unsigned int *)((char *)cache + 0x940) = end;
  *(unsigned int *)((char *)cache + 0x948) = end;
  csmemset((char *)cache + 0x990, 0xfa, 0x1c0u);
}

/* cache_copy_initialize_and_fill_with_garbage (0x1ba7c0) — readable C lift from XBE leaf.
 * ctx@esi: CreateFileA(path=ctx), record size, zero IO state fields. */
void cache_copy_initialize_and_fill_with_garbage(char *ctx)
{
  int handle;
  unsigned int size;

  handle = CreateFileA(ctx, 0x80000000u, 0u, 0, 3u, 0x60000000u, 0);
  *(int *)(ctx + 0x990) = handle;
  size = GetFileSize(handle, 0);
  *(unsigned int *)(ctx + 0xa94) = size;
  *(unsigned int *)(ctx + 0xa8c) = size;
  *(unsigned int *)(ctx + 0xa90) = size;
  csmemset(ctx + 0x99c, 0, 0xdcu);
  if (size < 0x800u) {
    display_assert((const char *)0x2b845c, (const char *)0x2b839c, 0x3c4, true);
    system_exit(-1);
  }
  csmemset(ctx + 0x994, 0, 4u);
  csmemset(ctx + 0x998, 0, 4u);
  *(unsigned int *)(ctx + 0xa78) = 0xffffffffu;
  *(unsigned int *)(ctx + 0xa7c) = 0xffffffffu;
  *(unsigned int *)(ctx + 0xa80) = 0xffffffffu;
  *(unsigned int *)(ctx + 0xa84) = 0xffffffffu;
  *(unsigned short *)(ctx + 0xa88) = 0xffffu;
  *(unsigned short *)(ctx + 0xab8) = 0;
  *(unsigned short *)(ctx + 0xaba) = 0;
  *(unsigned short *)(ctx + 0xabe) = 0;
  *(unsigned short *)(ctx + 0xac0) = 0;
  *(unsigned int *)(ctx + 0xab4) = 0;
  *(unsigned short *)(ctx + 0xabc) = 0xffffu;
}


/* FUN_001ba8b0 (0x1ba8b0) — readable C lift. */
void FUN_001ba8b0(char *base)
{
  extern char DAT_002b84a8[];
  extern char DAT_002b839c[];
  extern char DAT_002b8488[];
  int status;
  status = FUN_001d00b9((int)(uintptr_t)*(void **)(base + 0x950), 0x1388, 1);
  if ((*(unsigned int *)(base + 0x994) >> 8) & 1) {
    display_assert(DAT_002b84a8, DAT_002b839c, 0x5ca, 1);
    system_exit(-1);
  }
  if (status != 0xc0) {
    display_assert(DAT_002b8488, DAT_002b839c, 0x5cb, 1);
    system_exit(-1);
  }
  *(unsigned int *)(base + 0x994) &= 0xfffffeffu;
}

/* FUN_001ba930 (0x1ba930) — readable C lift from XBE leaf.
 * Wait for overlapped I/O on cache header @ESI; clear busy bit. */
void FUN_001ba930(void *header)
{
  extern char DAT_002b839c[];
  extern char DAT_002b8538[];
  extern char DAT_002b84f0[];
  extern char DAT_002b8488[];
  unsigned int flags;
  int status;

  flags = *(unsigned int *)((char *)header + 0x994);
  if ((flags & 0x400u) == 0) {
    display_assert(DAT_002b8538, DAT_002b839c, 0x5d6, 1);
    system_exit(-1);
  }
  status = FUN_001d00b9((int)(uintptr_t)*(void **)((char *)header + 0x950), 0x1388, 1);
  flags = *(unsigned int *)((char *)header + 0x994);
  if ((flags & 0x400u) != 0) {
    display_assert(DAT_002b84f0, DAT_002b839c, 0x5da, 1);
    system_exit(-1);
  }
  if (status != 0xc0) {
    display_assert(DAT_002b8488, DAT_002b839c, 0x5db, 1);
    system_exit(-1);
  }
  *(unsigned int *)((char *)header + 0x994) &= 0xfffffbffu;
}


/* FUN_001ba9d0 (0x1ba9d0) — readable C lift. */
void *FUN_001ba9d0(void *header, int16_t value)
{
  int i;
  int bit;
  int word;
  void *addr;

  for (i = 0; i < 8; i++) {
    if (*(int16_t *)((char *)header + 0xa78 + i * 2) != value)
      continue;
    bit = i & 0x1f;
    word = i >> 5;
    if ((*(unsigned int *)((char *)header + 0x998 + word * 4) & (1u << bit)) == 0)
      continue;
    addr = *(void **)((char *)header + 0x964 + i * 4);
    physical_memory_protect(addr, 0x20000u, 2u);
    return (char *)header + 0xa78 + i * 2;
  }
  return 0;
}
/* FUN_001baa50 (0x1baa50) — readable C lift. */
int FUN_001baa50(char *base, int ptr)
{
  extern char DAT_002b8580[];
  extern char DAT_002b839c[];
  int idx = (ptr - (int)(uintptr_t)base - 0xa78) >> 1;
  if ((int16_t)idx < 0 || (int16_t)idx >= 8) {
    display_assert(DAT_002b8580, DAT_002b839c, 0x646, 1);
    system_exit(-1);
  }
  return *(int *)(base + 0x964 + ((int16_t)idx) * 4);
}

/* FUN_001bab60 (0x1bab60) — readable C lift: wait for tag IO then clear slot. */
void FUN_001bab60(void *ctx)
{
  extern char DAT_002b839c[];
  extern char DAT_002b8488[];
  extern char DAT_002b8610[];
  int tries;
  unsigned int status;

  tries = 0xb;
  while (*(int *)((char *)ctx + 0x994) != 0) {
    short left = (short)tries;
    tries -= 1;
    if (left == 0)
      break;
    status = SleepEx(0x1388, 1);
    if (status == 0xc0)
      continue;
    display_assert(DAT_002b8488, DAT_002b839c, 0x69f, 1);
    system_exit(-1);
  }
  if (*(int *)((char *)ctx + 0x994) != 0) {
    display_assert(DAT_002b8610, DAT_002b839c, 0x6a3, 1);
    system_exit(-1);
  }
  csmemset((char *)ctx + 0x998, 0, 4);
}



/* FUN_001bac00 (0x1bac00) — readable C lift. */
void FUN_001bac00(unsigned char bit)
{
  char *base = *(char **)0x32ea98;
  *(unsigned int *)(base + 0x904) |= (1u << bit);
}

/* FUN_001bac70 (0x1bac70) — readable C lift. */
void FUN_001bac70(int index)
{
  unsigned int counter[2];
  QueryPerformanceCounter(counter);
  *(int *)(0x4e5610 + index * 4) += (int)counter[0] - *(int *)(0x4e5638 + index * 8);
}
/* FUN_001baca0 (0x1baca0) — readable C lift. */
void FUN_001baca0(void)
{
  static const unsigned int fmts[8] = {
    0x2b878c, 0x2b876c, 0x2b8750, 0x2b8724,
    0x2b8700, 0x2b86d4, 0x2b86a4, 0x2b8684
  };
  int i;
  double v;

  error(2, (const char *)0x2b87ac);
  for (i = 0; i < 8; i++) {
    v = (double)*(int *)(0x4e5614 + 4 * i) / (double)*(int *)0x32ea9c;
    error(2, (const char *)fmts[i], v);
  }
}

/* cache_copy_get_status (0x1badc0) — readable C lift (restored pre-naked). */
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
  ((void(*)(void))FUN_001d0362)();
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



/* FUN_001baf50 (0x1baf50) — readable C lift. */
void FUN_001baf50(void)
{
  char *globals;
  int handle;

  globals = *(char **)0x32ea98;
  handle = *(int *)(globals + 0x954);
  if (WaitForSingleObject(handle, 0) != 0) {
    SetEvent(*(void **)(*(char **)0x32ea98 + 0x950));
    WaitForSingleObject(*(int *)(*(char **)0x32ea98 + 0x954), -1);
  }
  if (*(unsigned char *)0x4e61d0)
    FUN_001baca0();
}

/* FUN_001bafa0 (0x1bafa0) — readable C lift (restored pre-naked). */
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
  ((void(*)(void))ResetEvent)();
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



/* FUN_001bb190 (0x1bb190) — Capstone tip: slot bit already set → assert. */
void FUN_001bb190(void *cache /*@<edi>*/, int a, int b, int c, short index)
{
  unsigned int bit;
  unsigned int *word;
  (void)a; (void)b; (void)c;
  QueryPerformanceCounter((void *)0x4e5640);
  bit = 1u << (index & 31);
  word = (unsigned int *)((char *)cache + 0x994 + 4 * (index >> 5));
  if (*word & bit) {
    display_assert((const char *)0x2b8878, (const char *)0x2b839c, 0x536, true);
    system_exit(-1);
  }
}


/* FUN_001bb2d0 (0x1bb2d0) — Capstone tip: slot bit (index+9) set → assert.
 * Uses cache@edi; index from stack; QPC @ 0x4e5648; assert line 0x583. */
void FUN_001bb2d0(void *cache /*@<edi>*/, int a, int b, int c, short index)
{
  unsigned int bit;
  unsigned int *word;
  int slot;
  (void)a; (void)b; (void)c;
  QueryPerformanceCounter((void *)0x4e5648);
  slot = (int)index + 9;
  bit = 1u << (slot & 31);
  word = (unsigned int *)((char *)cache + 0x994 + 4 * (slot >> 5));
  if (*word & bit) {
    display_assert((const char *)0x2b8878, (const char *)0x2b839c, 0x583, true);
    system_exit(-1);
  }
}


