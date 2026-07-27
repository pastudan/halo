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

/* FUN_001bdf60 (0x1bdf60) — XBE naked draft (batch 269). */
#if defined(__clang__)
static void *(*const b1bdf60_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static const char * (*const b1bdf60_c1ba1f0)(int tag_index) = tag_get_name;
static char * (*const b1bdf60_c8d9d0)(char *buffer, const char *format, ...) = csprintf;
static void (*const b1bdf60_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1bdf60_exitfn)(int) = system_exit;
static void (*const b1bdf60_c11d8f0)(void *cache, int block_index) = lruv_block_delete;

__attribute__((naked, noinline))
void FUN_001bdf60(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "movl 0x2c(%%esi), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_001bdf60_3\n\t"
      "pushl %%eax\n\t"
      "movl 0x4e9368, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movb 0x4(%%eax), %%cl\n\t"
      "addl $8, %%esp\n\t"
      "testb %%cl, %%cl\n\t"
      "je .LFUN_001bdf60_1\n\t"
      "movl 0x2c(%%esi), %%ecx\n\t"
      "movl 0x4e9368, %%edx\n\t"
      "pushl $1\n\t"
      "pushl $0xad\n\t"
      "pushl $0x2b9288\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[dget]\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl 0x2c(%%esi), %%ecx\n\t"
      "movl 0x4e9368, %%edx\n\t"
      "addl $8, %%esp\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[dget]\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl 0x3c(%%eax), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1ba1f0]\n\t"
      "addl $0xc, %%esp\n\t"
      "pushl %%eax\n\t"
      "pushl $0x2b9320\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x10, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001bdf60_1:\n\t"
      "movl 0x2c(%%esi), %%edx\n\t"
      "movl 0x4e9368, %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movb 0x5(%%eax), %%cl\n\t"
      "addl $8, %%esp\n\t"
      "testb %%cl, %%cl\n\t"
      "je .LFUN_001bdf60_2\n\t"
      "movl 0x2c(%%esi), %%ecx\n\t"
      "movl 0x4e9368, %%edx\n\t"
      "pushl $1\n\t"
      "pushl $0xae\n\t"
      "pushl $0x2b9288\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[dget]\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl 0x2c(%%esi), %%ecx\n\t"
      "movl 0x4e9368, %%edx\n\t"
      "addl $8, %%esp\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[dget]\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl 0x3c(%%eax), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1ba1f0]\n\t"
      "addl $0xc, %%esp\n\t"
      "pushl %%eax\n\t"
      "pushl $0x2b92d0\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x10, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001bdf60_2:\n\t"
      "movl 0x2c(%%esi), %%edx\n\t"
      "movl 0x4e9370, %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c11d8f0]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_001bdf60_3:\n\t"
      "movl $0xffffffff, 0x2c(%%esi)\n\t"
      "movl $0, 0x30(%%esi)\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [dget] "m"(b1bdf60_dget), [c1ba1f0] "m"(b1bdf60_c1ba1f0), [c8d9d0] "m"(b1bdf60_c8d9d0), [assert] "m"(b1bdf60_assert), [exitfn] "m"(b1bdf60_exitfn), [c11d8f0] "m"(b1bdf60_c11d8f0)
      : "memory");
}
#else
#error "FUN_001bdf60: clang naked draft required"
#endif


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

/* sound_cache_request_sound (0x1be550) — XBE naked draft (batch 249). */
#if defined(__clang__)
static void (*const b1be550_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1be550_exitfn)(int) = system_exit;
static void (*const b1be550_c1be2b0)(void *perm_entry) = FUN_001be2b0;
static void (*const b1be550_c11d9d0)(void *cache, int datum_handle) = lruv_debug_to_file;
static void *(*const b1be550_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void (*const b1be550_c1cfb98)(void) = SwitchToThread;
static void (*const b1be550_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;

__attribute__((naked, noinline))
int sound_cache_request_sound(void *permutation __attribute__((unused)), int a2 __attribute__((unused)), int a3 __attribute__((unused)), int a4 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "movb 0x10(%%ebp), %%bl\n\t"
      "testb %%bl, %%bl\n\t"
      "pushl %%esi\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "jne .Lsound_cache_request_sound_2\n\t"
      "movb 0xc(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lsound_cache_request_sound_1\n\t"
      "pushl $1\n\t"
      "pushl $0xc2\n\t"
      "pushl $0x2b9288\n\t"
      "pushl $0x2b9604\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lsound_cache_request_sound_1:\n\t"
      "movb 0x14(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lsound_cache_request_sound_2\n\t"
      "pushl $1\n\t"
      "pushl $0xc4\n\t"
      "pushl $0x2b9288\n\t"
      "pushl $0x2b95f0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lsound_cache_request_sound_2:\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "movl 0x34(%%esi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lsound_cache_request_sound_3\n\t"
      "pushl $1\n\t"
      "pushl $0xc6\n\t"
      "pushl $0x2b9288\n\t"
      "pushl $0x2b95d4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lsound_cache_request_sound_3:\n\t"
      "cmpl $-1, 0x2c(%%esi)\n\t"
      "jne .Lsound_cache_request_sound_4\n\t"
      "testb %%bl, %%bl\n\t"
      "je .Lsound_cache_request_sound_4\n\t"
      "call *%[c1be2b0]\n\t"
      ".Lsound_cache_request_sound_4:\n\t"
      "movl 0x2c(%%esi), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lsound_cache_request_sound_11\n\t"
      "pushl %%eax\n\t"
      "movl 0x4e9370, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c11d9d0]\n\t"
      "addl $8, %%esp\n\t"
      "pushl %%edi\n\t"
      ".Lsound_cache_request_sound_5:\n\t"
      "movl 0x2c(%%esi), %%ecx\n\t"
      "movl 0x4e9368, %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%edi\n\t"
      "movb 0x2(%%edi), %%al\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lsound_cache_request_sound_6\n\t"
      "call *%[c1cfb98]\n\t"
      "movb 0xc(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lsound_cache_request_sound_5\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lsound_cache_request_sound_6:\n\t"
      "movb 0x3(%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lsound_cache_request_sound_7\n\t"
      "movb $1, 0x3(%%edi)\n\t"
      "movb $0, 0x4(%%edi)\n\t"
      "movb $0, 0x5(%%edi)\n\t"
      ".Lsound_cache_request_sound_7:\n\t"
      "movb 0x14(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lsound_cache_request_sound_10\n\t"
      "movb 0x5054ec, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lsound_cache_request_sound_8\n\t"
      "movl 0x8(%%edi), %%eax\n\t"
      "movzbl 0x4(%%edi), %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x2b95c0\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $0x10, %%esp\n\t"
      ".Lsound_cache_request_sound_8:\n\t"
      "cmpb $0xff, 0x4(%%edi)\n\t"
      "jb .Lsound_cache_request_sound_9\n\t"
      "pushl $1\n\t"
      "pushl $0xec\n\t"
      "pushl $0x2b9288\n\t"
      "pushl $0x2b9588\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lsound_cache_request_sound_9:\n\t"
      "incb 0x4(%%edi)\n\t"
      ".Lsound_cache_request_sound_10:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lsound_cache_request_sound_11:\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b1be550_assert), [exitfn] "m"(b1be550_exitfn), [c1be2b0] "m"(b1be550_c1be2b0), [c11d9d0] "m"(b1be550_c11d9d0), [dget] "m"(b1be550_dget), [c1cfb98] "m"(b1be550_c1cfb98), [c8f390] "m"(b1be550_c8f390)
      : "memory");
}
#else
#error "sound_cache_request_sound: clang naked draft required"
#endif


/* FUN_001be6b0 (0x1be6b0) — XBE naked draft (batch 246). */
#if defined(__clang__)


__attribute__((naked, noinline))
void FUN_001be6b0(void)
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
#error "FUN_001be6b0: clang naked draft required"
#endif


/* FUN_001be7b0 (0x1be7b0) — XBE naked draft (batch 247). */
#if defined(__clang__)
static void (*const b1be7b0_c11da60)(void *cache, unsigned char *usage) = lruv_cache_get_page_usage;
static void (*const b1be7b0_c1be6b0)(void) = FUN_001be6b0;
static void (*const b1be7b0_c189270)(char flag, float *point_a, float *point_b, void *color) = FUN_00189270;

__attribute__((naked, noinline))
void FUN_001be7b0(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x454, %%esp\n\t"
      "movb 0x5054e9, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001be7b0_5\n\t"
      "movl 0x2ee6d4, %%ecx\n\t"
      "movl 0x2ee6d8, %%edx\n\t"
      "movl 0x2ee6d0, %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl %%ecx, -0x28(%%ebp)\n\t"
      "pushl %%edi\n\t"
      "leal -0x454(%%ebp), %%ecx\n\t"
      "movl %%edx, -0x24(%%ebp)\n\t"
      "movl 0x4e9370, %%edx\n\t"
      "movl %%eax, -0x2c(%%ebp)\n\t"
      "movl 0x2ee6e0, %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "movl %%eax, -0x20(%%ebp)\n\t"
      "call *%[c11da60]\n\t"
      "addl $8, %%esp\n\t"
      "xorl %%esi, %%esi\n\t"
      "movl %%esi, -0xc(%%ebp)\n\t"
      "jmp .LFUN_001be7b0_1\n\t"
      "leal (%%esp), %%esp\n\t"
      "nop\n\t"
      ".LFUN_001be7b0_1:\n\t"
      "movswl %%si, %%eax\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "leal -0x454(%%ebp,%%eax,1), %%edx\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "movl %%edx, -0x1c(%%ebp)\n\t"
      ".LFUN_001be7b0_2:\n\t"
      "movl -0x1c(%%ebp), %%edx\n\t"
      "movb (%%edx), %%dl\n\t"
      "movl $1, %%eax\n\t"
      "shll %%cl, %%eax\n\t"
      "testb %%al, %%dl\n\t"
      "je .LFUN_001be7b0_4\n\t"
      "movl %%esi, %%eax\n\t"
      "cdq\n\t"
      "movl $0x280, %%esi\n\t"
      "idivl %%esi\n\t"
      "leal -0x3c(%%ebp), %%edi\n\t"
      "leal -0x4c(%%ebp), %%esi\n\t"
      "movl $2, %%ebx\n\t"
      "leal (%%ecx,%%eax,4), %%eax\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      "fildl -0x4(%%ebp)\n\t"
      "leal (%%eax,%%eax,4), %%eax\n\t"
      "shll $1, %%eax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "fsts -0x3c(%%ebp)\n\t"
      "addl $0xa, %%eax\n\t"
      "fildl -0x4(%%ebp)\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "fstps -0x38(%%ebp)\n\t"
      "fstps -0x34(%%ebp)\n\t"
      "fildl -0x4(%%ebp)\n\t"
      "fstps -0x30(%%ebp)\n\t"
      "flds 0x50658c\n\t"
      "fadds 0x255ef8\n\t"
      "fstps -0x4(%%ebp)\n\t"
      ".LFUN_001be7b0_3:\n\t"
      "leal -0x8(%%esi), %%eax\n\t"
      "leal -0x18(%%ebp), %%ecx\n\t"
      "movl %%edi, %%edx\n\t"
      "call *%[c1be6b0]\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fmuls 0x506564\n\t"
      "addl $8, %%edi\n\t"
      "flds 0x506560\n\t"
      "addl $0xc, %%esi\n\t"
      "decl %%ebx\n\t"
      "fmuls -0x14(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds 0x50655c\n\t"
      "fmuls -0x18(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fdivrs -0x4(%%ebp)\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fadds (%%eax)\n\t"
      "fstps (%%eax)\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fadds -0x10(%%esi)\n\t"
      "fstps -0x10(%%esi)\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fadds -0xc(%%esi)\n\t"
      "fstps -0xc(%%esi)\n\t"
      "fstp %%st(0)\n\t"
      "jne .LFUN_001be7b0_3\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movl -0x2c(%%ebp,%%eax,4), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x48(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x54(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $1\n\t"
      "call *%[c189270]\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movl -0xc(%%ebp), %%esi\n\t"
      "addl $0x10, %%esp\n\t"
      ".LFUN_001be7b0_4:\n\t"
      "incl %%ecx\n\t"
      "cmpl $4, %%ecx\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "jl .LFUN_001be7b0_2\n\t"
      "incl %%esi\n\t"
      "cmpl $0x280, %%esi\n\t"
      "movl %%esi, -0xc(%%ebp)\n\t"
      "jl .LFUN_001be7b0_1\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      ".LFUN_001be7b0_5:\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c11da60] "m"(b1be7b0_c11da60), [c1be6b0] "m"(b1be7b0_c1be6b0), [c189270] "m"(b1be7b0_c189270)
      : "memory");
}
#else
#error "FUN_001be7b0: clang naked draft required"
#endif

