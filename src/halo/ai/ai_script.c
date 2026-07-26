/* --- ai_script.obj batch drafts (2026-07-26) --- */

/* 0x58cc0 */
void ai_scripting_follow_distance(int a0, int a1, int a2)
{
  int eax = 0;
  int edi = 0;

  global_scenario_get();
  FUN_00054220(edi, (void *)(uintptr_t)eax, (char *)0, 0);
  hs_runtime_get_executing_thread_name();
  error(0, (char *)0x0025d1d0);
  FUN_00058af0(0, 0, (void *)0, 0);

  (void)eax;
  (void)edi;
}

/* FUN_00058d40 (0x58d40) — XBE naked draft (batch 124). */
#if defined(__clang__)
static scenario_t * (*const b58d40_c18e380)(void) = global_scenario_get;
static void (*const b58d40_c54220)(unsigned int combined_index, void *scenario, char *buffer, int buffer_size) = FUN_00054220;
static const char * (*const b58d40_ccb980)(void) = hs_runtime_get_executing_thread_name;
static void (*const b58d40_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;
static void (*const b58d40_c54680)(unsigned int combined_index, void *iter) = FUN_00054680;
static int (*const b58d40_c54750)(void *iter) = FUN_00054750;
static void *(*const b58d40_tag)(int, int) = tag_get;
static void *(*const b58d40_get)(int, int) = object_get_and_verify_type;
static int *(*const b58d40_gseed)(void) = get_global_random_seed_address;
static int16_t (*const b58d40_c10b2d0)(unsigned int *seed, int16_t min, int16_t max) = random_range;
static int16_t (*const b58d40_c1aaee0)(int unit_handle) = unit_get_current_grenade_type;
static int16_t (*const b58d40_c1aae70)(int unit_handle, int16_t grenade_type) = unit_get_grenade_count;
static int16_t (*const b58d40_c1aaa90)(int unit_handle, int16_t grenade_type, int16_t grenade_count) = unit_set_grenade_count;

__attribute__((naked, noinline))
void FUN_00058d40(int a0 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x118, %%esp\n\t"
      "movb 0x5aca59, %%al\n\t"
      "testb %%al, %%al\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "je .LFUN_00058d40_1\n\t"
      "leal -0x118(%%ebp), %%eax\n\t"
      "pushl $0x100\n\t"
      "pushl %%eax\n\t"
      "call *%[c18e380]\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[c54220]\n\t"
      "leal -0x118(%%ebp), %%ecx\n\t"
      "addl $0x10, %%esp\n\t"
      "pushl %%ecx\n\t"
      "call *%[ccb980]\n\t"
      "pushl %%eax\n\t"
      "pushl $0x25d1fc\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $0x10, %%esp\n\t"
      ".LFUN_00058d40_1:\n\t"
      "leal -0x18(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%esi\n\t"
      "call *%[c54680]\n\t"
      "leal -0x18(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c54750]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_00058d40_8\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "nop\n\t"
      ".LFUN_00058d40_2:\n\t"
      "movl 0x18(%%esi), %%eax\n\t"
      "orl $0xffffffff, %%edi\n\t"
      "cmpl %%edi, %%eax\n\t"
      "je .LFUN_00058d40_7\n\t"
      "movl 0x5c(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x61637476\n\t"
      "call *%[tag]\n\t"
      "movl 0x18(%%esi), %%edx\n\t"
      "pushl $3\n\t"
      "pushl %%edx\n\t"
      "movl %%eax, %%ebx\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%ecx\n\t"
      "flds 0x88(%%ecx)\n\t"
      "addl $0x10, %%esp\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00058d40_3\n\t"
      "flds 0x2533c8\n\t"
      "jmp .LFUN_00058d40_4\n\t"
      ".LFUN_00058d40_3:\n\t"
      "flds 0x2533c0\n\t"
      ".LFUN_00058d40_4:\n\t"
      "fstps 0x90(%%ecx)\n\t"
      "flds 0x8c(%%ecx)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00058d40_5\n\t"
      "flds 0x2533c8\n\t"
      "jmp .LFUN_00058d40_6\n\t"
      ".LFUN_00058d40_5:\n\t"
      "flds 0x2533c0\n\t"
      ".LFUN_00058d40_6:\n\t"
      "fstps 0x94(%%ecx)\n\t"
      "cmpw %%di, 0x180(%%ebx)\n\t"
      "je .LFUN_00058d40_7\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x1d2(%%ebx), %%ax\n\t"
      "incw %%ax\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x1d0(%%ebx), %%cx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[gseed]\n\t"
      "pushl %%eax\n\t"
      "call *%[c10b2d0]\n\t"
      "movl %%eax, %%edi\n\t"
      "movl 0x18(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1aaee0]\n\t"
      "movl 0x18(%%esi), %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1aae70]\n\t"
      "addl $0x18, %%esp\n\t"
      "cmpw %%di, %%ax\n\t"
      "jge .LFUN_00058d40_7\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x180(%%ebx), %%dx\n\t"
      "subl %%eax, %%edi\n\t"
      "movl 0x18(%%esi), %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c1aaa90]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_00058d40_7:\n\t"
      "leal -0x18(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c54750]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $4, %%esp\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LFUN_00058d40_2\n\t"
      "popl %%edi\n\t"
      "popl %%ebx\n\t"
      ".LFUN_00058d40_8:\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c18e380] "m"(b58d40_c18e380), [c54220] "m"(b58d40_c54220), [ccb980] "m"(b58d40_ccb980), [c8f390] "m"(b58d40_c8f390), [c54680] "m"(b58d40_c54680), [c54750] "m"(b58d40_c54750), [tag] "m"(b58d40_tag), [get] "m"(b58d40_get), [gseed] "m"(b58d40_gseed), [c10b2d0] "m"(b58d40_c10b2d0), [c1aaee0] "m"(b58d40_c1aaee0), [c1aae70] "m"(b58d40_c1aae70), [c1aaa90] "m"(b58d40_c1aaa90)
      : "memory");
}
#else
#error "FUN_00058d40: clang naked draft required"
#endif


/* 0x58eb0 */
void FUN_00058eb0(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  game_state_data_new((char *)0x00254868, 128, 108);
  /* mem[0x005ab270] = eax */
  display_assert((char *)0x0025d26c, (char *)0x0025d27c, 110, 0);
  system_exit(0);
  game_state_malloc((char *)0x0025d264, (char *)0x0025d264, 32768);
  /* mem[0x005ab278] = eax */
  display_assert((char *)0x0025d258, (char *)0x0025d27c, 113, 0);
  system_exit(0);
  game_state_malloc((char *)0x0025d250, (char *)0x0025d250, 4096);
  /* mem[0x005ab274] = eax */
  display_assert((char *)0x0025d240, (char *)0x0025d27c, 116, 0);
  system_exit(0);
  game_state_data_new((char *)0x0025d234, 256, 40);
  /* mem[0x005ab26c] = eax */
  display_assert((char *)0x0025d224, (char *)0x0025d27c, 119, 0);
  system_exit(0);
  data_make_invalid((void *)(uintptr_t)eax);
  data_make_invalid((void *)(uintptr_t)ecx);
  scenario_get();
  datum_get((void *)(uintptr_t)eax, 0);
  global_scenario_get();
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  display_assert((char *)0x0025d390, (char *)0x0025d27c, 355, 0);
  system_exit(0);
  csmemset((void *)(uintptr_t)ebx, 0, edx);
  /* cmp edi, -1 -> je 0x59477 */
  datum_get((void *)(uintptr_t)ecx, 0);
  /* cmp esi, -1 -> je 0x592b8 */
  object_get_and_verify_type(0, 0);
  object_get_root_parent(0);
  object_get_and_verify_type(0, 0);
  /* cmp (int16_t)esi, -1 -> je 0x59122 */
  /* test (int16_t)esi, (int16_t)esi -> jl 0x590da */
  /* cmp edx, eax -> jl 0x590fa */
  display_assert((char *)0x0025d354, (char *)0x0025d27c, 382, 0);
  system_exit(0);
  /* test ecx, ecx -> je 0x59122 */
  /* relift: test dword ptr [eax + ecx], edx -> je 0x59122 */
  /* cmp esi, -1 -> jne 0x590a6 */
  object_get_and_verify_type(0, 0);
  object_get_root_parent(0);
  object_get_and_verify_type(0, 0);
  /* cmp (int16_t)esi, -1 -> je 0x591b9 */
  /* test (int16_t)esi, (int16_t)esi -> jl 0x59171 */
  /* cmp eax, ecx -> jl 0x59191 */
  display_assert((char *)0x0025d354, (char *)0x0025d27c, 408, 0);
  system_exit(0);
  /* test ecx, ecx -> je 0x591b9 */
  /* relift: test dword ptr [eax + ecx], edx -> je 0x591b9 */
  /* test (char)eax, (char)eax -> je 0x592b8 */
  /* cmp (int16_t)eax, 3 -> jne 0x59229 */
  /* relift: cmp word ptr [esi + 0x6e], 2 -> jl 0x591f0 */
  actor_get_firing_position_group(0, 0, 0);
  /* cmp (int16_t)eax, 6 -> je 0x59223 */
  /* cmp (int16_t)eax, 4 -> je 0x59223 */
  /* cmp (int16_t)eax, 3 -> je 0x5920c */
  /* cmp (int16_t)eax, 5 -> jne 0x5924b */
  actor_get_firing_position_group(0, 0, 0);
  /* cmp (int16_t)eax, 2 -> jne 0x5924b */
  /* relift: cmp word ptr [esi + 0x9c], 0 -> je 0x5924b */
  /* cmp eax, -1 -> je 0x592b8 */
  datum_get((void *)(uintptr_t)eax, 0);
  /* cmp (int16_t)esi, -1 -> je 0x592b8 */
  /* test (int16_t)esi, (int16_t)esi -> jl 0x59281 */
  /* cmp ecx, eax -> jl 0x592a1 */
  display_assert((char *)0x0025d354, (char *)0x0025d27c, 448, 0);
  system_exit(0);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}
