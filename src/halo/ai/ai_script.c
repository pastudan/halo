/* --- ai_script.obj batch drafts (2026-07-26) --- */

/* ai_scripting_follow_distance (0x58cc0) — readable C lift. */
void ai_scripting_follow_distance(int encounter_handle, int actor_handle, int seat_list)
{
  char buf[0x100];

  if (*(char *)0x5aca59) {
    FUN_00054220(encounter_handle, global_scenario_get(), buf, 0x100);
    error(2, (const char *)0x25d1d0, hs_runtime_get_executing_thread_name());
    (void)actor_handle;
  }
  FUN_00058af0(seat_list, 1, encounter_handle);
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


/* FUN_00058eb0 (0x58eb0) — XBE naked draft (batch 140). */
#if defined(__clang__)
static data_t * (*const b58eb0_c1bfe10)(char *name, __int16 maximum_count, __int16 size) = game_state_data_new;
static void (*const b58eb0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b58eb0_exitfn)(int) = system_exit;
static void * (*const b58eb0_c1bfbf0)(const char *name, const char *a2, int size) = game_state_malloc;

__attribute__((naked, noinline))
void FUN_00058eb0(void)
{
  __asm__ volatile(
      "pushl $0x6c\n\t"
      "pushl $0x80\n\t"
      "pushl $0x254868\n\t"
      "call *%[c1bfe10]\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%eax, 0x5ab270\n\t"
      "jne .LFUN_00058eb0_1\n\t"
      "pushl $1\n\t"
      "pushl $0x6e\n\t"
      "pushl $0x25d27c\n\t"
      "pushl $0x25d26c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00058eb0_1:\n\t"
      "pushl $0x8000\n\t"
      "pushl $0x25d264\n\t"
      "pushl $0x25d264\n\t"
      "call *%[c1bfbf0]\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%eax, 0x5ab278\n\t"
      "jne .LFUN_00058eb0_2\n\t"
      "pushl $1\n\t"
      "pushl $0x71\n\t"
      "pushl $0x25d27c\n\t"
      "pushl $0x25d258\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00058eb0_2:\n\t"
      "pushl $0x1000\n\t"
      "pushl $0x25d250\n\t"
      "pushl $0x25d250\n\t"
      "call *%[c1bfbf0]\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%eax, 0x5ab274\n\t"
      "jne .LFUN_00058eb0_3\n\t"
      "pushl $1\n\t"
      "pushl $0x74\n\t"
      "pushl $0x25d27c\n\t"
      "pushl $0x25d240\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00058eb0_3:\n\t"
      "pushl $0x28\n\t"
      "pushl $0x100\n\t"
      "pushl $0x25d234\n\t"
      "call *%[c1bfe10]\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%eax, 0x5ab26c\n\t"
      "jne .LFUN_00058eb0_4\n\t"
      "pushl $1\n\t"
      "pushl $0x77\n\t"
      "pushl $0x25d27c\n\t"
      "pushl $0x25d224\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00058eb0_4:\n\t"
      "ret\n\t"
      :
      : [c1bfe10] "m"(b58eb0_c1bfe10), [assert] "m"(b58eb0_assert), [exitfn] "m"(b58eb0_exitfn), [c1bfbf0] "m"(b58eb0_c1bfbf0)
      : "memory");
}
#else
#error "FUN_00058eb0: clang naked draft required"
#endif

