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

/* FUN_001b9fa0 (0x1b9fa0) — XBE naked draft (batch 275). */
#if defined(__clang__)
static int (*const b1b9fa0_c1bdd50)(void) = FUN_001bdd50;
static void *(*const b1b9fa0_memset)(void *, int, unsigned int) = csmemset;
static short (*const b1b9fa0_c1bc9e0)(int param_1, int offset, unsigned int size, int buffer, char *completion_flag, char async_flag) = cache_file_read;
static void (*const b1b9fa0_c1cfb98)(void) = (void (*)(void))SwitchToThread;
static unsigned int (*const b1b9fa0_c1cb8e0)(void) = sound_render_time;
static unsigned int (*const b1b9fa0_c8e370)(void) = system_milliseconds;
static void (*const b1b9fa0_c1cf2f0)(void) = (void (*)(void))sound_idle;
static void (*const b1b9fa0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1b9fa0_exitfn)(int) = system_exit;
static void (*const b1b9fa0_c1bcdc0)(void *block) = structure_bsp_header_register_vertex_buffers;
static int * (*const b1b9fa0_c1b9bf0)(int tag_index) = tag_instance_resolve;

__attribute__((naked, noinline))
void FUN_001b9fa0(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c1bdd50]\n\t"
      "movl 0x4e4d18, %%ecx\n\t"
      "movl $0x1600000, %%edx\n\t"
      "subl %%ecx, %%edx\n\t"
      "pushl %%edx\n\t"
      "addl %%eax, %%ecx\n\t"
      "pushl $0xcd\n\t"
      "pushl %%ecx\n\t"
      "call *%[memset]\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "movl 0x8(%%esi), %%ecx\n\t"
      "movl 0x4(%%esi), %%edx\n\t"
      "pushl $1\n\t"
      "leal 0xb(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl (%%esi), %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl $-1\n\t"
      "call *%[c1bc9e0]\n\t"
      "movb 0xb(%%ebp), %%al\n\t"
      "addl $0x24, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_001b9fa0_3\n\t"
      "leal (%%ebx), %%ebx\n\t"
      ".LFUN_001b9fa0_1:\n\t"
      "call *%[c1cfb98]\n\t"
      "call *%[c1cb8e0]\n\t"
      "movl %%eax, %%edi\n\t"
      "call *%[c8e370]\n\t"
      "subl %%edi, %%eax\n\t"
      "cmpl $0x21, %%eax\n\t"
      "jbe .LFUN_001b9fa0_2\n\t"
      "call *%[c1cf2f0]\n\t"
      ".LFUN_001b9fa0_2:\n\t"
      "movb 0xb(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001b9fa0_1\n\t"
      ".LFUN_001b9fa0_3:\n\t"
      "movl 0x8(%%esi), %%eax\n\t"
      "movl %%eax, 0x4e5508\n\t"
      "cmpl $0x73627370, 0x14(%%eax)\n\t"
      "je .LFUN_001b9fa0_4\n\t"
      "pushl $1\n\t"
      "pushl $0xad\n\t"
      "pushl $0x2b7dc8\n\t"
      "pushl $0x2b8128\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "movl 0x4e5508, %%eax\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001b9fa0_4:\n\t"
      "pushl %%eax\n\t"
      "call *%[c1bcdc0]\n\t"
      "movl 0x1c(%%esi), %%edi\n\t"
      "addl $4, %%esp\n\t"
      "call *%[c1b9bf0]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x14(%%esi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_001b9fa0_5\n\t"
      "pushl $1\n\t"
      "pushl $0xb7\n\t"
      "pushl $0x2b7dc8\n\t"
      "pushl $0x2b8108\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001b9fa0_5:\n\t"
      "cmpl $0x73627370, (%%esi)\n\t"
      "je .LFUN_001b9fa0_6\n\t"
      "pushl $1\n\t"
      "pushl $0xb8\n\t"
      "pushl $0x2b7dc8\n\t"
      "pushl $0x2b80dc\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001b9fa0_6:\n\t"
      "movl 0x4e5508, %%ecx\n\t"
      "movl (%%ecx), %%edx\n\t"
      "popl %%edi\n\t"
      "movl %%edx, 0x14(%%esi)\n\t"
      "movb $1, %%al\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c1bdd50] "m"(b1b9fa0_c1bdd50), [memset] "m"(b1b9fa0_memset), [c1bc9e0] "m"(b1b9fa0_c1bc9e0), [c1cfb98] "m"(b1b9fa0_c1cfb98), [c1cb8e0] "m"(b1b9fa0_c1cb8e0), [c8e370] "m"(b1b9fa0_c8e370), [c1cf2f0] "m"(b1b9fa0_c1cf2f0), [assert] "m"(b1b9fa0_assert), [exitfn] "m"(b1b9fa0_exitfn), [c1bcdc0] "m"(b1b9fa0_c1bcdc0), [c1b9bf0] "m"(b1b9fa0_c1b9bf0)
      : "memory");
}
#else
#error "FUN_001b9fa0: clang naked draft required"
#endif


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

/* FUN_001ba2f0 (0x1ba2f0) — XBE naked draft (batch 247). */
#if defined(__clang__)
static int __stdcall (*const b1ba2f0_c1d0336)(int handle, int timeout_ms) = WaitForSingleObject;
static void (*const b1ba2f0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1ba2f0_exitfn)(int) = system_exit;
static unsigned int __stdcall (*const b1ba2f0_c1d1d4a)(int handle, unsigned int *high_size) = GetFileSize;
static char * (*const b1ba2f0_c8dff0)(char *destination, const char *source) = csstrcpy;
static void (*const b1ba2f0_c1cfeca)(void) = (void (*)(void))ResetEvent;
static void *(*const b1ba2f0_memset)(void *, int, unsigned int) = csmemset;
static bool __stdcall (*const b1ba2f0_c1cfeaa)(void *handle) = SetEvent;

__attribute__((naked, noinline))
void FUN_001ba2f0(int buffer __attribute__((unused)), int size __attribute__((unused)), int dest_file __attribute__((unused)), int dest_file_size __attribute__((unused)), const char *source_file_name __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl 0x32ea98, %%eax\n\t"
      "movl 0x954(%%eax), %%ecx\n\t"
      "pushl $0\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1d0336]\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_001ba2f0_13\n\t"
      "movl 0x18(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_001ba2f0_1\n\t"
      "pushl $1\n\t"
      "pushl $0x20c\n\t"
      "pushl $0x2b839c\n\t"
      "pushl $0x2b8388\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001ba2f0_1:\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "movl 0x10(%%ebp), %%edi\n\t"
      "cmpl $-1, %%edi\n\t"
      "jne .LFUN_001ba2f0_2\n\t"
      "pushl $1\n\t"
      "pushl $0x20d\n\t"
      "pushl $0x2b839c\n\t"
      "pushl $0x2b8360\n\t"
      "call *%[assert]\n\t"
      "pushl %%edi\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001ba2f0_2:\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "testl %%ebx, %%ebx\n\t"
      "jne .LFUN_001ba2f0_3\n\t"
      "pushl $1\n\t"
      "pushl $0x20e\n\t"
      "pushl $0x2b839c\n\t"
      "pushl $0x267900\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001ba2f0_3:\n\t"
      "cmpl $0x512000, 0xc(%%ebp)\n\t"
      "jge .LFUN_001ba2f0_4\n\t"
      "pushl $1\n\t"
      "pushl $0x20f\n\t"
      "pushl $0x2b839c\n\t"
      "pushl $0x2b8344\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001ba2f0_4:\n\t"
      "pushl $0\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d1d4a]\n\t"
      "cmpl %%eax, 0x14(%%ebp)\n\t"
      "je .LFUN_001ba2f0_5\n\t"
      "pushl $1\n\t"
      "pushl $0x210\n\t"
      "pushl $0x2b839c\n\t"
      "pushl $0x2b8308\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001ba2f0_5:\n\t"
      "movl 0x32ea98, %%eax\n\t"
      "movl 0x954(%%eax), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "jne .LFUN_001ba2f0_6\n\t"
      "pushl $1\n\t"
      "pushl $0x212\n\t"
      "pushl $0x2b839c\n\t"
      "pushl $0x2b82e4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "movl 0x32ea98, %%eax\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001ba2f0_6:\n\t"
      "movl 0x950(%%eax), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "jne .LFUN_001ba2f0_7\n\t"
      "pushl $1\n\t"
      "pushl $0x213\n\t"
      "pushl $0x2b839c\n\t"
      "pushl $0x2b82c4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "movl 0x32ea98, %%eax\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001ba2f0_7:\n\t"
      "movl 0x94c(%%eax), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "jne .LFUN_001ba2f0_8\n\t"
      "pushl $1\n\t"
      "pushl $0x214\n\t"
      "pushl $0x2b839c\n\t"
      "pushl $0x2b82a4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "movl 0x32ea98, %%eax\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001ba2f0_8:\n\t"
      "movl 0x958(%%eax), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "jne .LFUN_001ba2f0_9\n\t"
      "pushl $1\n\t"
      "pushl $0x215\n\t"
      "pushl $0x2b839c\n\t"
      "pushl $0x2b8280\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "movl 0x32ea98, %%eax\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001ba2f0_9:\n\t"
      "movl 0x95c(%%eax), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "jne .LFUN_001ba2f0_10\n\t"
      "pushl $1\n\t"
      "pushl $0x217\n\t"
      "pushl $0x2b839c\n\t"
      "pushl $0x2b8264\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "movl 0x32ea98, %%eax\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001ba2f0_10:\n\t"
      "movl 0x928(%%eax), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "jne .LFUN_001ba2f0_11\n\t"
      "pushl $1\n\t"
      "pushl $0x219\n\t"
      "pushl $0x2b839c\n\t"
      "pushl $0x2b8244\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "movl 0x32ea98, %%eax\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001ba2f0_11:\n\t"
      "movl 0x92c(%%eax), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "jne .LFUN_001ba2f0_12\n\t"
      "pushl $1\n\t"
      "pushl $0x21a\n\t"
      "pushl $0x2b839c\n\t"
      "pushl $0x2b8224\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "movl 0x32ea98, %%eax\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001ba2f0_12:\n\t"
      "movl 0x18(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl $0, 0x904(%%eax)\n\t"
      "pushl %%eax\n\t"
      "movl %%ebx, 0x960(%%eax)\n\t"
      "call *%[c8dff0]\n\t"
      "movl 0x32ea98, %%eax\n\t"
      "movl %%edi, 0x98c(%%eax)\n\t"
      "movl $0, 0xaa0(%%eax)\n\t"
      "movl 0x954(%%eax), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[c1cfeca]\n\t"
      "movl 0x32ea98, %%ecx\n\t"
      "movl 0x950(%%ecx), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c1cfeca]\n\t"
      "movl 0x32ea98, %%eax\n\t"
      "pushl $0x800\n\t"
      "addl $0x104, %%eax\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "call *%[memset]\n\t"
      "movl 0x32ea98, %%ecx\n\t"
      "movl 0x94c(%%ecx), %%edx\n\t"
      "addl $0xc, %%esp\n\t"
      "pushl %%edx\n\t"
      "call *%[c1cfeaa]\n\t"
      "popl %%edi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001ba2f0_13:\n\t"
      "pushl $1\n\t"
      "pushl $0x234\n\t"
      "pushl $0x2b839c\n\t"
      "pushl $0x2b81fc\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c1d0336] "m"(b1ba2f0_c1d0336), [assert] "m"(b1ba2f0_assert), [exitfn] "m"(b1ba2f0_exitfn), [c1d1d4a] "m"(b1ba2f0_c1d1d4a), [c8dff0] "m"(b1ba2f0_c8dff0), [c1cfeca] "m"(b1ba2f0_c1cfeca), [memset] "m"(b1ba2f0_memset), [c1cfeaa] "m"(b1ba2f0_c1cfeaa)
      : "memory");
}
#else
#error "FUN_001ba2f0: clang naked draft required"
#endif


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

/* FUN_001ba710 (0x1ba710) — XBE naked draft (batch 281). */
#if defined(__clang__)
static void __stdcall (*const b1ba710_c1d371d)(void *addr, unsigned int size, unsigned int protect) = physical_memory_protect;
static void *(*const b1ba710_memset)(void *, int, unsigned int) = csmemset;

__attribute__((naked, noinline))
void FUN_001ba710(void *cache __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x32ea98, %%edi\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x960(%%esi), %%eax\n\t"
      "leal 0x964(%%edi), %%ecx\n\t"
      "movl $8, %%edx\n\t"
      "jmp .LFUN_001ba710_1\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".LFUN_001ba710_1:\n\t"
      "movl %%eax, (%%ecx)\n\t"
      "addl $0x20000, %%eax\n\t"
      "addl $4, %%ecx\n\t"
      "decl %%edx\n\t"
      "jne .LFUN_001ba710_1\n\t"
      "pushl $4\n\t"
      "movl %%eax, 0x984(%%edi)\n\t"
      "movl 0x960(%%esi), %%eax\n\t"
      "pushl $0x512000\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d371d]\n\t"
      "movl 0x960(%%esi), %%ecx\n\t"
      "pushl $0x500000\n\t"
      "pushl $0xfd\n\t"
      "pushl %%ecx\n\t"
      "call *%[memset]\n\t"
      "movl 0x960(%%esi), %%edx\n\t"
      "addl $0xc, %%esp\n\t"
      "pushl $2\n\t"
      "pushl $0x500000\n\t"
      "pushl %%edx\n\t"
      "call *%[c1d371d]\n\t"
      "movl 0x960(%%esi), %%eax\n\t"
      "addl $0x500000, %%eax\n\t"
      "pushl $0x1c0\n\t"
      "movl $0x12000, 0x944(%%esi)\n\t"
      "movl %%eax, 0x940(%%esi)\n\t"
      "movl %%eax, 0x948(%%esi)\n\t"
      "pushl $0xfa\n\t"
      "addl $0x990, %%esi\n\t"
      "pushl %%esi\n\t"
      "call *%[memset]\n\t"
      "addl $0xc, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      :
      : [c1d371d] "m"(b1ba710_c1d371d), [memset] "m"(b1ba710_memset)
      : "memory");
}
#else
#error "FUN_001ba710: clang naked draft required"
#endif

/* cache_copy_initialize_and_fill_with_garbage (0x1ba7c0) — XBE naked draft (batch 282). */
#if defined(__clang__)
static int __stdcall (*const b1ba7c0_c1d1d85)(const char *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t) = CreateFileA;
static unsigned int __stdcall (*const b1ba7c0_c1d1d4a)(int handle, unsigned int *high_size) = GetFileSize;
static void *(*const b1ba7c0_memset)(void *, int, unsigned int) = csmemset;
static void (*const b1ba7c0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1ba7c0_exitfn)(int) = system_exit;

__attribute__((naked, noinline))
void cache_copy_initialize_and_fill_with_garbage(void)
{
  __asm__ volatile(
      "pushl %%edi\n\t"
      "xorl %%edi, %%edi\n\t"
      "pushl %%edi\n\t"
      "pushl $0x60000000\n\t"
      "pushl $3\n\t"
      "pushl %%edi\n\t"
      "pushl %%edi\n\t"
      "pushl $0x80000000\n\t"
      "pushl %%esi\n\t"
      "call *%[c1d1d85]\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "movl %%eax, 0x990(%%esi)\n\t"
      "call *%[c1d1d4a]\n\t"
      "pushl $0xdc\n\t"
      "movl %%eax, 0xa94(%%esi)\n\t"
      "movl %%eax, 0xa8c(%%esi)\n\t"
      "movl %%eax, 0xa90(%%esi)\n\t"
      "leal 0x99c(%%esi), %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[memset]\n\t"
      "movl 0xa94(%%esi), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl $0x800, %%eax\n\t"
      "jae .Lcache_copy_initialize_and_fill_with_garbage_1\n\t"
      "pushl $1\n\t"
      "pushl $0x3c4\n\t"
      "pushl $0x2b839c\n\t"
      "pushl $0x2b845c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lcache_copy_initialize_and_fill_with_garbage_1:\n\t"
      "pushl $4\n\t"
      "leal 0x994(%%esi), %%ecx\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "call *%[memset]\n\t"
      "pushl $4\n\t"
      "leal 0x998(%%esi), %%edx\n\t"
      "pushl %%edi\n\t"
      "pushl %%edx\n\t"
      "call *%[memset]\n\t"
      "orl $0xffffffff, %%eax\n\t"
      "movl %%eax, 0xa78(%%esi)\n\t"
      "movl %%eax, 0xa7c(%%esi)\n\t"
      "movl %%eax, 0xa80(%%esi)\n\t"
      "movl %%eax, 0xa84(%%esi)\n\t"
      "movw $0xffff, 0xa88(%%esi)\n\t"
      "addl $0x18, %%esp\n\t"
      "movw %%di, 0xab8(%%esi)\n\t"
      "movw %%di, 0xaba(%%esi)\n\t"
      "movw %%di, 0xabe(%%esi)\n\t"
      "movw %%di, 0xac0(%%esi)\n\t"
      "movl %%edi, 0xab4(%%esi)\n\t"
      "movw $0xffff, 0xabc(%%esi)\n\t"
      "popl %%edi\n\t"
      "ret\n\t"
      :
      : [c1d1d85] "m"(b1ba7c0_c1d1d85), [c1d1d4a] "m"(b1ba7c0_c1d1d4a), [memset] "m"(b1ba7c0_memset), [assert] "m"(b1ba7c0_assert), [exitfn] "m"(b1ba7c0_exitfn)
      : "memory");
}
#else
#error "cache_copy_initialize_and_fill_with_garbage: clang naked draft required"
#endif


/* FUN_001ba8b0 (0x1ba8b0) — readable C lift. */
void FUN_001ba8b0(char *base)
{
  extern char DAT_002b84a8[];
  extern char DAT_002b839c[];
  extern char DAT_002b8488[];
  int status;
  status = FUN_001d00b9(*(void **)(base + 0x950), 0x1388, 1);
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
  status = FUN_001d00b9(*(void **)((char *)header + 0x950), 0x1388, 1);
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

/* FUN_001bab60 (0x1bab60) — XBE naked draft (batch 273). */
#if defined(__clang__)
static unsigned int __stdcall (*const b1bab60_c1d01c4)(unsigned int milliseconds, int alertable) = SleepEx;
static void (*const b1bab60_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1bab60_exitfn)(int) = system_exit;
static void *(*const b1bab60_memset)(void *, int, unsigned int) = csmemset;

__attribute__((naked, noinline))
void FUN_001bab60(void)
{
  __asm__ volatile(
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl %%eax, %%esi\n\t"
      "movl $0xb, %%edi\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_001bab60_1:\n\t"
      "movl 0x994(%%esi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_001bab60_2\n\t"
      "movw %%di, %%ax\n\t"
      "decl %%edi\n\t"
      "testw %%ax, %%ax\n\t"
      "je .LFUN_001bab60_2\n\t"
      "pushl $1\n\t"
      "pushl $0x1388\n\t"
      "call *%[c1d01c4]\n\t"
      "cmpl $0xc0, %%eax\n\t"
      "je .LFUN_001bab60_1\n\t"
      "pushl $1\n\t"
      "pushl $0x69f\n\t"
      "pushl $0x2b839c\n\t"
      "pushl $0x2b8488\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "jmp .LFUN_001bab60_1\n\t"
      ".LFUN_001bab60_2:\n\t"
      "movl 0x994(%%esi), %%edx\n\t"
      "testl %%edx, %%edx\n\t"
      "setne %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001bab60_3\n\t"
      "pushl $1\n\t"
      "pushl $0x6a3\n\t"
      "pushl $0x2b839c\n\t"
      "pushl $0x2b8610\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001bab60_3:\n\t"
      "pushl $4\n\t"
      "pushl $0\n\t"
      "addl $0x998, %%esi\n\t"
      "pushl %%esi\n\t"
      "call *%[memset]\n\t"
      "addl $0xc, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      :
      : [c1d01c4] "m"(b1bab60_c1d01c4), [assert] "m"(b1bab60_assert), [exitfn] "m"(b1bab60_exitfn), [memset] "m"(b1bab60_memset)
      : "memory");
}
#else
#error "FUN_001bab60: clang naked draft required"
#endif


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
/* FUN_001baca0 (0x1baca0) — XBE naked draft (batch 246). */
#if defined(__clang__)
static void (*const b1baca0_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;

__attribute__((naked, noinline))
void FUN_001baca0(void)
{
  __asm__ volatile(
      "pushl $0x2b87ac\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "fildl 0x4e5614\n\t"
      "fidivl 0x32ea9c\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x2b878c\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "fildl 0x4e5618\n\t"
      "addl $8, %%esp\n\t"
      "fidivl 0x32ea9c\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x2b876c\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "fildl 0x4e561c\n\t"
      "addl $8, %%esp\n\t"
      "fidivl 0x32ea9c\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x2b8750\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "fildl 0x4e5620\n\t"
      "addl $8, %%esp\n\t"
      "fidivl 0x32ea9c\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x2b8724\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "fildl 0x4e5624\n\t"
      "addl $8, %%esp\n\t"
      "fidivl 0x32ea9c\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x2b8700\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "fildl 0x4e5628\n\t"
      "addl $8, %%esp\n\t"
      "fidivl 0x32ea9c\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x2b86d4\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "fildl 0x4e562c\n\t"
      "addl $8, %%esp\n\t"
      "fidivl 0x32ea9c\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x2b86a4\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "fildl 0x4e5630\n\t"
      "addl $8, %%esp\n\t"
      "fidivl 0x32ea9c\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x2b8684\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $0x10, %%esp\n\t"
      "ret\n\t"
      :
      : [c8f390] "m"(b1baca0_c8f390)
      : "memory");
}
#else
#error "FUN_001baca0: clang naked draft required"
#endif


/* cache_copy_get_status (0x1badc0) — XBE naked draft (batch 247). */
#if defined(__clang__)
static void (*const b1badc0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1badc0_exitfn)(int) = system_exit;
static void (*const b1badc0_c1d0362)(void) = (void (*)(void))FUN_001d0362;
static int __stdcall (*const b1badc0_c1d0336)(int handle, int timeout_ms) = WaitForSingleObject;

__attribute__((naked, noinline))
void cache_copy_get_status(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl 0x32ea98, %%eax\n\t"
      "pushl %%ebx\n\t"
      "movl 0x904(%%eax), %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "xorl %%esi, %%esi\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .Lcache_copy_get_status_1\n\t"
      "pushl $1\n\t"
      "pushl $0x23e\n\t"
      "pushl $0x2b839c\n\t"
      "pushl $0x2b87d0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "movl 0x32ea98, %%eax\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lcache_copy_get_status_1:\n\t"
      "movb 0x988(%%eax), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "je .Lcache_copy_get_status_2\n\t"
      "pushl $0x10\n\t"
      "call *%[c1d0362]\n\t"
      "movl 0x32ea98, %%eax\n\t"
      ".Lcache_copy_get_status_2:\n\t"
      "testl %%ebx, %%ebx\n\t"
      "jne .Lcache_copy_get_status_6\n\t"
      "movl 0x95c(%%eax), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .Lcache_copy_get_status_6\n\t"
      "movl 0x10c(%%eax), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "jle .Lcache_copy_get_status_5\n\t"
      "movl 0x954(%%eax), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d0336]\n\t"
      "movl 0x32ea98, %%ecx\n\t"
      "movl 0x958(%%ecx), %%edx\n\t"
      "movl %%eax, %%esi\n\t"
      "negl %%esi\n\t"
      "pushl %%ebx\n\t"
      "sbbl %%esi, %%esi\n\t"
      "pushl %%edx\n\t"
      "addl $4, %%esi\n\t"
      "call *%[c1d0336]\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lcache_copy_get_status_10\n\t"
      "movl 0x32ea98, %%ecx\n\t"
      "flds 0xaa0(%%ecx)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lcache_copy_get_status_3\n\t"
      "flds 0x2533c0\n\t"
      "movw %%si, %%ax\n\t"
      "fstps (%%edi)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lcache_copy_get_status_3:\n\t"
      "flds 0xaa0(%%ecx)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lcache_copy_get_status_4\n\t"
      "flds 0x2533c8\n\t"
      "movw %%si, %%ax\n\t"
      "fstps (%%edi)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lcache_copy_get_status_4:\n\t"
      "flds 0xaa0(%%ecx)\n\t"
      "movw %%si, %%ax\n\t"
      "fstps (%%edi)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lcache_copy_get_status_5:\n\t"
      "movl $0, (%%edi)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl $3, %%eax\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lcache_copy_get_status_6:\n\t"
      "testb $2, %%bl\n\t"
      "je .Lcache_copy_get_status_7\n\t"
      "movl $1, %%esi\n\t"
      "movl $0, (%%edi)\n\t"
      "popl %%edi\n\t"
      "movw %%si, %%ax\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lcache_copy_get_status_7:\n\t"
      "testb $4, %%bl\n\t"
      "je .Lcache_copy_get_status_8\n\t"
      "xorl %%esi, %%esi\n\t"
      "movl %%esi, (%%edi)\n\t"
      "popl %%edi\n\t"
      "movw %%si, %%ax\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lcache_copy_get_status_8:\n\t"
      "testb $1, %%bl\n\t"
      "je .Lcache_copy_get_status_9\n\t"
      "movl $2, %%esi\n\t"
      "movl $0, (%%edi)\n\t"
      "popl %%edi\n\t"
      "movw %%si, %%ax\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lcache_copy_get_status_9:\n\t"
      "pushl $1\n\t"
      "pushl $0x272\n\t"
      "pushl $0x2b839c\n\t"
      "pushl $0x255ee8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "movl $0, (%%edi)\n\t"
      ".Lcache_copy_get_status_10:\n\t"
      "popl %%edi\n\t"
      "movw %%si, %%ax\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b1badc0_assert), [exitfn] "m"(b1badc0_exitfn), [c1d0362] "m"(b1badc0_c1d0362), [c1d0336] "m"(b1badc0_c1d0336)
      : "memory");
}
#else
#error "cache_copy_get_status: clang naked draft required"
#endif


/* FUN_001baf50 (0x1baf50) — XBE naked draft (batch 284). */
#if defined(__clang__)
static int __stdcall (*const b1baf50_c1d0336)(int handle, int timeout_ms) = WaitForSingleObject;
static bool __stdcall (*const b1baf50_c1cfeaa)(void *handle) = SetEvent;

__attribute__((naked, noinline))
void FUN_001baf50(void)
{
  __asm__ volatile(
      "movl 0x32ea98, %%eax\n\t"
      "movl 0x954(%%eax), %%ecx\n\t"
      "pushl $0\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1d0336]\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_001baf50_1\n\t"
      "movl 0x32ea98, %%edx\n\t"
      "movl 0x950(%%edx), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1cfeaa]\n\t"
      "movl 0x32ea98, %%ecx\n\t"
      "movl 0x954(%%ecx), %%edx\n\t"
      "pushl $-1\n\t"
      "pushl %%edx\n\t"
      "call *%[c1d0336]\n\t"
      ".LFUN_001baf50_1:\n\t"
      "movb 0x4e61d0, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001baf50_2\n\t"
      ".byte 0xe9, 0x05, 0xfd, 0xff, 0xff\n\t"
      ".LFUN_001baf50_2:\n\t"
      "ret\n\t"
      :
      : [c1d0336] "m"(b1baf50_c1d0336), [c1cfeaa] "m"(b1baf50_c1cfeaa)
      : "memory");
}
#else
#error "FUN_001baf50: clang naked draft required"
#endif


/* FUN_001bafa0 (0x1bafa0) — XBE naked draft (batch 249). */
#if defined(__clang__)
static bool __stdcall (*const b1bafa0_c1d33e6)(void *counter) = QueryPerformanceCounter;
static void (*const b1bafa0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1bafa0_exitfn)(int) = system_exit;
static void (*const b1bafa0_c1cfeca)(void) = (void (*)(void))ResetEvent;
static bool __stdcall (*const b1bafa0_c1cfeaa)(void *handle) = SetEvent;
static char * (*const b1bafa0_c8d9d0)(char *buffer, const char *format, ...) = csprintf;

__attribute__((naked, noinline))
void FUN_001bafa0(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xc, %%esp\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x32ea98, %%edi\n\t"
      "subl %%edi, %%ecx\n\t"
      "leal 0x998(%%edi), %%eax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "subl $0x99c, %%ecx\n\t"
      "movl $0x66666667, %%eax\n\t"
      "imull %%ecx\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "sarl $3, %%edx\n\t"
      "movl %%edx, %%ecx\n\t"
      "shrl $0x1f, %%ecx\n\t"
      "addl %%ecx, %%edx\n\t"
      "testl %%eax, %%eax\n\t"
      "leal 0x994(%%edi), %%ebx\n\t"
      "movl %%edx, %%esi\n\t"
      "jne .LFUN_001bafa0_5\n\t"
      "testl %%esi, %%esi\n\t"
      "jl .LFUN_001bafa0_3\n\t"
      "cmpl $0xb, %%esi\n\t"
      "jge .LFUN_001bafa0_1\n\t"
      "leal -0xc(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c1d33e6]\n\t"
      "movl %%esi, %%ecx\n\t"
      "andl $0x1f, %%ecx\n\t"
      "movl $1, %%edx\n\t"
      "shll %%cl, %%edx\n\t"
      "movl %%esi, %%eax\n\t"
      "sarl $5, %%eax\n\t"
      "shll $2, %%eax\n\t"
      "movl (%%eax,%%ebx,1), %%edi\n\t"
      "movl %%edx, %%ecx\n\t"
      "notl %%ecx\n\t"
      "andl %%ecx, %%edi\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movl %%edi, (%%eax,%%ebx,1)\n\t"
      "orl %%edx, (%%eax,%%ecx,1)\n\t"
      "movl 0x32ea98, %%edi\n\t"
      ".LFUN_001bafa0_1:\n\t"
      "cmpl $7, %%esi\n\t"
      "jg .LFUN_001bafa0_3\n\t"
      "movl 0xa90(%%edi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jg .LFUN_001bafa0_2\n\t"
      "pushl $1\n\t"
      "pushl $0x50b\n\t"
      "pushl $0x2b839c\n\t"
      "pushl $0x2b882c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "movl 0x32ea98, %%edi\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001bafa0_2:\n\t"
      "movl 0xa90(%%edi), %%ebx\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "subl %%edx, %%ebx\n\t"
      "movl %%ebx, 0xa90(%%edi)\n\t"
      "movl 0x958(%%edi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1cfeca]\n\t"
      "movl 0x32ea98, %%eax\n\t"
      "movl 0x10c(%%eax), %%ecx\n\t"
      "movl 0xa90(%%eax), %%edx\n\t"
      "movl %%ecx, 0x10(%%ebp)\n\t"
      "subl %%edx, %%ecx\n\t"
      "movl %%ecx, 0xc(%%ebp)\n\t"
      "fildl 0xc(%%ebp)\n\t"
      "fidivl 0x10(%%ebp)\n\t"
      "fstps 0xaa0(%%eax)\n\t"
      "movl 0x958(%%eax), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1cfeaa]\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001bafa0_3:\n\t"
      "cmpl $9, %%esi\n\t"
      "jl .LFUN_001bafa0_7\n\t"
      "jg .LFUN_001bafa0_7\n\t"
      "movl 0xa98(%%edi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jg .LFUN_001bafa0_4\n\t"
      "pushl $1\n\t"
      "pushl $0x514\n\t"
      "pushl $0x2b839c\n\t"
      "pushl $0x2b8804\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "movl 0x32ea98, %%edi\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001bafa0_4:\n\t"
      "movl 0xa98(%%edi), %%eax\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "subl %%edx, %%eax\n\t"
      "movl %%eax, 0xa98(%%edi)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001bafa0_5:\n\t"
      "pushl $1\n\t"
      "pushl $0x51a\n\t"
      "pushl $0x2b839c\n\t"
      "pushl %%eax\n\t"
      "pushl $0x2b87dc\n\t"
      "pushl $0x4e5510\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0xc, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "cmpl $9, %%esi\n\t"
      "jl .LFUN_001bafa0_6\n\t"
      "jg .LFUN_001bafa0_6\n\t"
      "movl 0x32ea98, %%eax\n\t"
      "movl 0x904(%%eax), %%ecx\n\t"
      "popl %%edi\n\t"
      "orl $1, %%ecx\n\t"
      "popl %%esi\n\t"
      "movl %%ecx, 0x904(%%eax)\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001bafa0_6:\n\t"
      "movl 0x32ea98, %%eax\n\t"
      "movl 0x904(%%eax), %%edx\n\t"
      "orl $2, %%edx\n\t"
      "movl %%edx, 0x904(%%eax)\n\t"
      ".LFUN_001bafa0_7:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c1d33e6] "m"(b1bafa0_c1d33e6), [assert] "m"(b1bafa0_assert), [exitfn] "m"(b1bafa0_exitfn), [c1cfeca] "m"(b1bafa0_c1cfeca), [c1cfeaa] "m"(b1bafa0_c1cfeaa), [c8d9d0] "m"(b1bafa0_c8d9d0)
      : "memory");
}
#else
#error "FUN_001bafa0: clang naked draft required"
#endif


/* FUN_001bb190 (0x1bb190) — XBE naked draft (batch 255). */
#if defined(__clang__)
static bool __stdcall (*const b1bb190_c1d33e6)(void *counter) = QueryPerformanceCounter;
static void (*const b1bb190_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1bb190_exitfn)(int) = system_exit;
static unsigned int __stdcall (*const b1bb190_c1d01c4)(unsigned int milliseconds, int alertable) = SleepEx;
static void __stdcall (*const b1bb190_c1d2268)(unsigned int error) = SetLastError;
static void (*const b1bb190_c1d19e7)(void) = (void (*)(void))FUN_001d19e7;
static int (*const b1bb190_c1d2240)(void) = xapi_GetLastError;

__attribute__((naked, noinline))
void FUN_001bb190(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xc, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl $0x4e5640\n\t"
      "call *%[c1d33e6]\n\t"
      "movswl 0x14(%%ebp), %%esi\n\t"
      "movl 0x990(%%edi), %%eax\n\t"
      "leal 0x267(%%esi,%%esi,4), %%ecx\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "leal (%%edi,%%ecx,4), %%eax\n\t"
      "movl %%esi, %%ecx\n\t"
      "andl $0x1f, %%ecx\n\t"
      "movl %%esi, %%edx\n\t"
      "sarl $5, %%edx\n\t"
      "movl $1, %%ebx\n\t"
      "shll %%cl, %%ebx\n\t"
      "leal 0x994(%%edi,%%edx,4), %%ecx\n\t"
      "movl (%%ecx), %%edx\n\t"
      "movl %%eax, 0x14(%%ebp)\n\t"
      "testl %%ebx, %%edx\n\t"
      "movl %%ecx, -0x4(%%ebp)\n\t"
      "je .LFUN_001bb190_1\n\t"
      "pushl $1\n\t"
      "pushl $0x536\n\t"
      "pushl $0x2b839c\n\t"
      "pushl $0x2b8878\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001bb190_1:\n\t"
      "orl %%ebx, (%%ecx)\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "leal 0xac8(%%edi,%%esi,8), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl %%esi, 0x10(%%eax)\n\t"
      "movl %%ecx, 0x8(%%eax)\n\t"
      "movl $0, 0xc(%%eax)\n\t"
      "call *%[c1d33e6]\n\t"
      ".LFUN_001bb190_2:\n\t"
      "pushl $1\n\t"
      "pushl $0\n\t"
      "call *%[c1d01c4]\n\t"
      "pushl $0\n\t"
      "call *%[c1d2268]\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "pushl $0x1bafa0\n\t"
      "pushl %%eax\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d19e7]\n\t"
      "movl %%eax, %%esi\n\t"
      "call *%[c1d2240]\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LFUN_001bb190_3\n\t"
      "cmpl $0x6f8, %%eax\n\t"
      "je .LFUN_001bb190_2\n\t"
      "cmpl $8, %%eax\n\t"
      "je .LFUN_001bb190_2\n\t"
      "cmpl $0x5aa, %%eax\n\t"
      "je .LFUN_001bb190_2\n\t"
      "pushl $1\n\t"
      "pushl $0x559\n\t"
      "pushl $0x2b839c\n\t"
      "pushl $0x2b8854\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "movl 0x32ea98, %%eax\n\t"
      "movl 0x904(%%eax), %%ecx\n\t"
      "addl $0x14, %%esp\n\t"
      "orl $2, %%ecx\n\t"
      "movl %%ecx, 0x904(%%eax)\n\t"
      ".LFUN_001bb190_3:\n\t"
      "leal -0xc(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c1d33e6]\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "movl 0x4e5640, %%edx\n\t"
      "movl 0x4e5614, %%ecx\n\t"
      "subl %%edx, %%eax\n\t"
      "addl %%eax, %%ecx\n\t"
      "popl %%esi\n\t"
      "movl %%ecx, 0x4e5614\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c1d33e6] "m"(b1bb190_c1d33e6), [assert] "m"(b1bb190_assert), [exitfn] "m"(b1bb190_exitfn), [c1d01c4] "m"(b1bb190_c1d01c4), [c1d2268] "m"(b1bb190_c1d2268), [c1d19e7] "m"(b1bb190_c1d19e7), [c1d2240] "m"(b1bb190_c1d2240)
      : "memory");
}
#else
#error "FUN_001bb190: clang naked draft required"
#endif


/* FUN_001bb2d0 (0x1bb2d0) — XBE naked draft (batch 242). */
#if defined(__clang__)
static bool __stdcall (*const b1bb2d0_c1d33e6)(void *counter) = QueryPerformanceCounter;
static void (*const b1bb2d0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1bb2d0_exitfn)(int) = system_exit;
static unsigned int __stdcall (*const b1bb2d0_c1d01c4)(unsigned int milliseconds, int alertable) = SleepEx;
static void __stdcall (*const b1bb2d0_c1d2268)(unsigned int error) = SetLastError;
static void (*const b1bb2d0_c1d1a38)(void) = (void (*)(void))FUN_001d1a38;
static int (*const b1bb2d0_c1d2240)(void) = xapi_GetLastError;

__attribute__((naked, noinline))
void FUN_001bb2d0(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xc, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl $0x4e5648\n\t"
      "call *%[c1d33e6]\n\t"
      "movswl 0x14(%%ebp), %%esi\n\t"
      "movl 0x98c(%%edi), %%eax\n\t"
      "addl $9, %%esi\n\t"
      "leal 0x267(%%esi,%%esi,4), %%ecx\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "leal (%%edi,%%ecx,4), %%eax\n\t"
      "movl %%esi, %%ecx\n\t"
      "andl $0x1f, %%ecx\n\t"
      "movl %%esi, %%edx\n\t"
      "sarl $5, %%edx\n\t"
      "movl $1, %%ebx\n\t"
      "shll %%cl, %%ebx\n\t"
      "leal 0x994(%%edi,%%edx,4), %%ecx\n\t"
      "movl (%%ecx), %%edx\n\t"
      "movl %%eax, 0x14(%%ebp)\n\t"
      "testl %%edx, %%ebx\n\t"
      "movl %%ecx, -0x4(%%ebp)\n\t"
      "je .LFUN_001bb2d0_1\n\t"
      "pushl $1\n\t"
      "pushl $0x583\n\t"
      "pushl $0x2b839c\n\t"
      "pushl $0x2b8878\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001bb2d0_1:\n\t"
      "orl %%ebx, (%%ecx)\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "leal 0xac8(%%edi,%%esi,8), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl %%esi, 0x10(%%eax)\n\t"
      "movl %%ecx, 0x8(%%eax)\n\t"
      "movl $0, 0xc(%%eax)\n\t"
      "call *%[c1d33e6]\n\t"
      ".LFUN_001bb2d0_2:\n\t"
      "pushl $1\n\t"
      "pushl $0\n\t"
      "call *%[c1d01c4]\n\t"
      "pushl $0\n\t"
      "call *%[c1d2268]\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "pushl $0x1bafa0\n\t"
      "pushl %%eax\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d1a38]\n\t"
      "movl %%eax, %%esi\n\t"
      "call *%[c1d2240]\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LFUN_001bb2d0_3\n\t"
      "cmpl $0x6f8, %%eax\n\t"
      "je .LFUN_001bb2d0_2\n\t"
      "cmpl $8, %%eax\n\t"
      "je .LFUN_001bb2d0_2\n\t"
      "cmpl $0x5aa, %%eax\n\t"
      "je .LFUN_001bb2d0_2\n\t"
      "pushl $1\n\t"
      "pushl $0x5a1\n\t"
      "pushl $0x2b839c\n\t"
      "pushl $0x2b88c0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "movl 0x32ea98, %%eax\n\t"
      "movl 0x904(%%eax), %%ecx\n\t"
      "addl $0x14, %%esp\n\t"
      "orl $1, %%ecx\n\t"
      "movl %%ecx, 0x904(%%eax)\n\t"
      ".LFUN_001bb2d0_3:\n\t"
      "leal -0xc(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c1d33e6]\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "movl 0x4e5648, %%edx\n\t"
      "movl 0x4e5618, %%ecx\n\t"
      "subl %%edx, %%eax\n\t"
      "addl %%eax, %%ecx\n\t"
      "popl %%esi\n\t"
      "movl %%ecx, 0x4e5618\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c1d33e6] "m"(b1bb2d0_c1d33e6), [assert] "m"(b1bb2d0_assert), [exitfn] "m"(b1bb2d0_exitfn), [c1d01c4] "m"(b1bb2d0_c1d01c4), [c1d2268] "m"(b1bb2d0_c1d2268), [c1d1a38] "m"(b1bb2d0_c1d1a38), [c1d2240] "m"(b1bb2d0_c1d2240)
      : "memory");
}
#else
#error "FUN_001bb2d0: clang naked draft required"
#endif

