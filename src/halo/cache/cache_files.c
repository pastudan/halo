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



/* cache_files_give_time_to_precache (0x1b9de0) — XBE naked draft (batch 281). */
#if defined(__clang__)
static bool (*const b1b9de0_c1bd8e0)(char *map_name) = cache_files_precache_map_loaded;
static bool (*const b1b9de0_c1bc6b0)(void) = (bool (*)(void))cache_files_precache_in_progress;
static bool (*const b1b9de0_c1bc6c0)(char *map_name) = cache_files_precache_is_copying_map;
static void (*const b1b9de0_c1bda30)(void) = cache_files_precache_map_end;
static __int16 (*const b1b9de0_c1bcf00)(float *) = cache_files_precache_map_status;
static void (*const b1b9de0_c1bc6a0)(bool) = cache_files_precache_set_priority;
static bool (*const b1b9de0_c1bd910)(char *map_name, bool) = cache_files_precache_map_begin;
static void (*const b1b9de0_ce8d20)(void) = display_error_damaged_media;

__attribute__((naked, noinline))
bool cache_files_give_time_to_precache(const char *name __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "pushl %%esi\n\t"
      "xorb %%bl, %%bl\n\t"
      "call *%[c1bd8e0]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lcache_files_give_time_to_precache_1\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lcache_files_give_time_to_precache_1:\n\t"
      "call *%[c1bc6b0]\n\t"
      "testb %%al, %%al\n\t"
      "je .Lcache_files_give_time_to_precache_2\n\t"
      "pushl %%esi\n\t"
      "call *%[c1bc6c0]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lcache_files_give_time_to_precache_2\n\t"
      "call *%[c1bda30]\n\t"
      ".Lcache_files_give_time_to_precache_2:\n\t"
      "call *%[c1bc6b0]\n\t"
      "testb %%al, %%al\n\t"
      "je .Lcache_files_give_time_to_precache_3\n\t"
      "leal -0x4(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1bcf00]\n\t"
      "addl $4, %%esp\n\t"
      "cmpw $2, %%ax\n\t"
      "je .Lcache_files_give_time_to_precache_4\n\t"
      "cmpw $1, %%ax\n\t"
      "jne .Lcache_files_give_time_to_precache_5\n\t"
      "call *%[c1bda30]\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lcache_files_give_time_to_precache_3:\n\t"
      "pushl $0\n\t"
      "call *%[c1bc6a0]\n\t"
      "pushl $0\n\t"
      "pushl %%esi\n\t"
      "call *%[c1bd910]\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lcache_files_give_time_to_precache_5\n\t"
      ".Lcache_files_give_time_to_precache_4:\n\t"
      "call *%[ce8d20]\n\t"
      ".Lcache_files_give_time_to_precache_5:\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c1bd8e0] "m"(b1b9de0_c1bd8e0), [c1bc6b0] "m"(b1b9de0_c1bc6b0), [c1bc6c0] "m"(b1b9de0_c1bc6c0), [c1bda30] "m"(b1b9de0_c1bda30), [c1bcf00] "m"(b1b9de0_c1bcf00), [c1bc6a0] "m"(b1b9de0_c1bc6a0), [c1bd910] "m"(b1b9de0_c1bd910), [ce8d20] "m"(b1b9de0_ce8d20)
      : "memory");
}
#else
#error "cache_files_give_time_to_precache: clang naked draft required"
#endif


/* FUN_001b9e70 (0x1b9e70) — XBE naked draft (batch 250). */
#if defined(__clang__)
static const char * (*const b1b9e70_c19b0d0)(const char *tag_name) = tag_name_strip_path;
static void (*const b1b9e70_c1be940)(void) = texture_cache_open;
static void (*const b1b9e70_c1bdec0)(void) = FUN_001bdec0;
static void (*const b1b9e70_c1bd4d0)(void) = cache_file_open;
static int (*const b1b9e70_c1bdd50)(void) = FUN_001bdd50;
static bool (*const b1b9e70_c1b9ce0)(void *header, const char *path, int report_errors) = cache_file_header_verify;
static void *(*const b1b9e70_memset)(void *, int, unsigned int) = csmemset;
static short (*const b1b9e70_c1bc9e0)(int param_1, int offset, unsigned int size, int buffer, char *completion_flag, char async_flag) = cache_file_read;
static void (*const b1b9e70_c1cfb98)(void) = SwitchToThread;
static char * (*const b1b9e70_c8d9d0)(char *buffer, const char *format, ...) = csprintf;
static void (*const b1b9e70_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1b9e70_exitfn)(int) = system_exit;
static void (*const b1b9e70_c1bccb0)(void *block) = tags_header_register_vertex_and_index_buffers;

__attribute__((naked, noinline))
void FUN_001b9e70(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "pushl %%edi\n\t"
      "call *%[c19b0d0]\n\t"
      "movl %%eax, %%esi\n\t"
      "orl $0xffffffff, %%ebx\n\t"
      "call *%[c1be940]\n\t"
      "call *%[c1bdec0]\n\t"
      "pushl $0x4e4d04\n\t"
      "pushl %%esi\n\t"
      "call *%[c1bd4d0]\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001b9e70_4\n\t"
      "call *%[c1bdd50]\n\t"
      "pushl $1\n\t"
      "pushl %%edi\n\t"
      "pushl $0x4e4d04\n\t"
      "movl %%eax, %%esi\n\t"
      "call *%[c1b9ce0]\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001b9e70_4\n\t"
      "pushl $0x1600000\n\t"
      "pushl $0xcd\n\t"
      "pushl %%esi\n\t"
      "call *%[memset]\n\t"
      "movl 0x4e4d18, %%ecx\n\t"
      "movl 0x4e4d14, %%edx\n\t"
      "pushl $1\n\t"
      "leal -0x1(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl $-1\n\t"
      "call *%[c1bc9e0]\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "addl $0x24, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_001b9e70_2\n\t"
      "leal (%%ebx), %%ebx\n\t"
      ".LFUN_001b9e70_1:\n\t"
      "call *%[c1cfb98]\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001b9e70_1\n\t"
      ".LFUN_001b9e70_2:\n\t"
      "movl %%esi, %%eax\n\t"
      "movl %%eax, 0x4e5504\n\t"
      "movl 0x20(%%esi), %%ecx\n\t"
      "cmpl $0x74616773, %%ecx\n\t"
      "je .LFUN_001b9e70_3\n\t"
      "movsbl 0x22(%%esi), %%edx\n\t"
      "pushl $1\n\t"
      "pushl $0x61\n\t"
      "pushl $0x2b7dc8\n\t"
      "pushl $0x73\n\t"
      "pushl $0x67\n\t"
      "pushl $0x61\n\t"
      "pushl $0x74\n\t"
      "movsbl %%cl, %%eax\n\t"
      "movsbl 0x21(%%esi), %%ecx\n\t"
      "pushl %%eax\n\t"
      "movsbl 0x23(%%esi), %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl $0x2b80ac\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x28, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "movl 0x4e5504, %%eax\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001b9e70_3:\n\t"
      "movl (%%eax), %%ecx\n\t"
      "pushl %%eax\n\t"
      "movl %%ecx, 0x5054f0\n\t"
      "call *%[c1bccb0]\n\t"
      "movl 0x4e5504, %%edx\n\t"
      "addl $4, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb $1, 0x4e4d00\n\t"
      "movl 0x4(%%edx), %%eax\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001b9e70_4:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebx, %%eax\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c19b0d0] "m"(b1b9e70_c19b0d0), [c1be940] "m"(b1b9e70_c1be940), [c1bdec0] "m"(b1b9e70_c1bdec0), [c1bd4d0] "m"(b1b9e70_c1bd4d0), [c1bdd50] "m"(b1b9e70_c1bdd50), [c1b9ce0] "m"(b1b9e70_c1b9ce0), [memset] "m"(b1b9e70_memset), [c1bc9e0] "m"(b1b9e70_c1bc9e0), [c1cfb98] "m"(b1b9e70_c1cfb98), [c8d9d0] "m"(b1b9e70_c8d9d0), [assert] "m"(b1b9e70_assert), [exitfn] "m"(b1b9e70_exitfn), [c1bccb0] "m"(b1b9e70_c1bccb0)
      : "memory");
}
#else
#error "FUN_001b9e70: clang naked draft required"
#endif

