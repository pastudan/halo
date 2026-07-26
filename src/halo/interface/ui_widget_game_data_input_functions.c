void ui_widget_game_data_function_invoke(
  void *widget, unsigned __int16 game_data_input_reference_function)
{
  assert_halt(widget);

  if (game_data_input_reference_function > 40u) {
    error(2, "invalid game_data_input_reference_function");
  } else {
    ui_widget_game_data_function_table[game_data_input_reference_function](
      widget);
  }
}

void ui_widget_game_data_build_version(int widget)
{
  wchar_t *v1, *v2; // eax

  if (!ui_widget_game_data_build_version_wide_str[0]) {
    ascii_to_wide(
#if DECOMP_CUSTOM
      build_ui_widget_text,
#else
      "01.10.12.2276",
#endif
      ui_widget_game_data_build_version_wide_str,
      sizeof(ui_widget_game_data_build_version_wide_str));
  }

  if (!*(uint32_t *)(widget + 60)) {
    v1 =
      ui_widget_realloc(0, sizeof(ui_widget_game_data_build_version_wide_str),
                        __FILE__, __LINE__);
    *(uint32_t *)(widget + 60) = (uint32_t)v1;
    if (v1) {
      csmemset(v1, 0, sizeof(ui_widget_game_data_build_version_wide_str));
    }
  }
  v2 = *(wchar_t **)(widget + 60);
  if (v2) {
    ustrncpy(v2, ui_widget_game_data_build_version_wide_str, 0x3Fu);
    *(wchar_t *)(*(uint32_t *)(widget + 60) + 126) = 0;
  }
}
/* --- ui_widget_game_data_input_functions.obj batch (2026-07-26) --- */

/* FUN_000edcd0 (0xedcd0) — XBE naked draft (batch 110). */
#if defined(__clang__)
static void (*const bedcd0_ce0ec0)(void) = player_ui_get_edit_playlist_profile;
static void (*const bedcd0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const bedcd0_exitfn)(int) = system_exit;
static void (*const bedcd0_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;

__attribute__((naked, noinline))
void FUN_000edcd0(void *widget __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[ce0ec0]\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "cmpw $3, 0xe(%%esi)\n\t"
      "movl %%eax, %%edi\n\t"
      "movl %%edi, -0x4(%%ebp)\n\t"
      "je .LFUN_000edcd0_1\n\t"
      "pushl $1\n\t"
      "pushl $0xc5a\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x287b1c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000edcd0_1:\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "cmpl %%ebx, %%edi\n\t"
      "je .LFUN_000edcd0_32\n\t"
      "movl 0x34(%%esi), %%edi\n\t"
      "cmpl %%ebx, %%edi\n\t"
      "jne .LFUN_000edcd0_2\n\t"
      "pushl $1\n\t"
      "pushl $0xc62\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x2871d8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000edcd0_2:\n\t"
      "movl 0x34(%%edi), %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "je .LFUN_000edcd0_4\n\t"
      ".LFUN_000edcd0_3:\n\t"
      "movl $2, %%ecx\n\t"
      "cmpw %%cx, 0xe(%%esi)\n\t"
      "je .LFUN_000edcd0_5\n\t"
      "movl 0x2c(%%esi), %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "jne .LFUN_000edcd0_3\n\t"
      ".LFUN_000edcd0_4:\n\t"
      "pushl $1\n\t"
      "pushl $0xc64\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x2871ac\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "movl $2, %%ecx\n\t"
      ".LFUN_000edcd0_5:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movl 0x50(%%eax), %%eax\n\t"
      "subl %%ebx, %%eax\n\t"
      "je .LFUN_000edcd0_7\n\t"
      "decl %%eax\n\t"
      "je .LFUN_000edcd0_6\n\t"
      "decl %%eax\n\t"
      "jne .LFUN_000edcd0_7\n\t"
      "movw %%cx, 0x3c(%%esi)\n\t"
      "jmp .LFUN_000edcd0_8\n\t"
      ".LFUN_000edcd0_6:\n\t"
      "movw $1, 0x3c(%%esi)\n\t"
      "jmp .LFUN_000edcd0_8\n\t"
      ".LFUN_000edcd0_7:\n\t"
      "movw %%bx, 0x3c(%%esi)\n\t"
      ".LFUN_000edcd0_8:\n\t"
      "movl 0x2c(%%edi), %%edi\n\t"
      "cmpl %%ebx, %%edi\n\t"
      "jne .LFUN_000edcd0_9\n\t"
      "pushl $1\n\t"
      "pushl $0xc6e\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x28714c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "movl $2, %%ecx\n\t"
      ".LFUN_000edcd0_9:\n\t"
      "movl 0x34(%%edi), %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "je .LFUN_000edcd0_11\n\t"
      "nop\n\t"
      ".LFUN_000edcd0_10:\n\t"
      "cmpw %%cx, 0xe(%%esi)\n\t"
      "je .LFUN_000edcd0_12\n\t"
      "movl 0x2c(%%esi), %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "jne .LFUN_000edcd0_10\n\t"
      ".LFUN_000edcd0_11:\n\t"
      "pushl $1\n\t"
      "pushl $0xc70\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x287120\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "movl $2, %%ecx\n\t"
      ".LFUN_000edcd0_12:\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "movl 0x4c(%%edx), %%eax\n\t"
      "subl %%ebx, %%eax\n\t"
      "je .LFUN_000edcd0_14\n\t"
      "decl %%eax\n\t"
      "je .LFUN_000edcd0_13\n\t"
      "decl %%eax\n\t"
      "jne .LFUN_000edcd0_14\n\t"
      "movw %%cx, 0x3c(%%esi)\n\t"
      "jmp .LFUN_000edcd0_15\n\t"
      ".LFUN_000edcd0_13:\n\t"
      "movw $1, 0x3c(%%esi)\n\t"
      "jmp .LFUN_000edcd0_15\n\t"
      ".LFUN_000edcd0_14:\n\t"
      "movw %%bx, 0x3c(%%esi)\n\t"
      ".LFUN_000edcd0_15:\n\t"
      "movl 0x2c(%%edi), %%edi\n\t"
      "cmpl %%ebx, %%edi\n\t"
      "jne .LFUN_000edcd0_16\n\t"
      "pushl $1\n\t"
      "pushl $0xc7a\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x2870c8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "movl $2, %%ecx\n\t"
      ".LFUN_000edcd0_16:\n\t"
      "movl 0x34(%%edi), %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "je .LFUN_000edcd0_18\n\t"
      ".LFUN_000edcd0_17:\n\t"
      "cmpw %%cx, 0xe(%%esi)\n\t"
      "je .LFUN_000edcd0_19\n\t"
      "movl 0x2c(%%esi), %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "jne .LFUN_000edcd0_17\n\t"
      ".LFUN_000edcd0_18:\n\t"
      "pushl $1\n\t"
      "pushl $0xc7c\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x28709c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "movl $2, %%ecx\n\t"
      ".LFUN_000edcd0_19:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movl 0x40(%%eax), %%eax\n\t"
      "decl %%eax\n\t"
      "cmpl $0x18, %%eax\n\t"
      "ja .LFUN_000edcd0_25\n\t"
      "movzbl 0xedf8c(%%eax), %%edx\n\t"
      "jmp *.LFUN_000edcd0_jt(,%%edx,4)\n\t"
      ".LFUN_000edcd0_20:\n\t"
      "movw $1, 0x3c(%%esi)\n\t"
      "jmp .LFUN_000edcd0_26\n\t"
      ".LFUN_000edcd0_21:\n\t"
      "movw %%cx, 0x3c(%%esi)\n\t"
      "jmp .LFUN_000edcd0_26\n\t"
      ".LFUN_000edcd0_22:\n\t"
      "movw $3, 0x3c(%%esi)\n\t"
      "jmp .LFUN_000edcd0_26\n\t"
      ".LFUN_000edcd0_23:\n\t"
      "movw $4, 0x3c(%%esi)\n\t"
      "jmp .LFUN_000edcd0_26\n\t"
      ".LFUN_000edcd0_24:\n\t"
      "movw $5, 0x3c(%%esi)\n\t"
      "jmp .LFUN_000edcd0_26\n\t"
      ".LFUN_000edcd0_25:\n\t"
      "movw %%bx, 0x3c(%%esi)\n\t"
      ".LFUN_000edcd0_26:\n\t"
      "movl 0x2c(%%edi), %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "jne .LFUN_000edcd0_27\n\t"
      "pushl $1\n\t"
      "pushl $0xc89\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x286950\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "movl $2, %%ecx\n\t"
      ".LFUN_000edcd0_27:\n\t"
      "movl 0x34(%%esi), %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "je .LFUN_000edcd0_29\n\t"
      ".LFUN_000edcd0_28:\n\t"
      "cmpw %%cx, 0xe(%%esi)\n\t"
      "je .LFUN_000edcd0_30\n\t"
      "movl 0x2c(%%esi), %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "jne .LFUN_000edcd0_28\n\t"
      ".LFUN_000edcd0_29:\n\t"
      "pushl $1\n\t"
      "pushl $0xc8b\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x286928\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000edcd0_30:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movzbl 0x1c(%%eax), %%eax\n\t"
      "subl %%ebx, %%eax\n\t"
      "je .LFUN_000edcd0_31\n\t"
      "popl %%edi\n\t"
      "movw %%bx, 0x3c(%%esi)\n\t"
      "popl %%esi\n\t"
      "decl %%eax\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000edcd0_31:\n\t"
      "popl %%edi\n\t"
      "movw $1, 0x3c(%%esi)\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000edcd0_32:\n\t"
      "pushl $0x286550\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_000edcd0_jt:\n\t"
      ".long .LFUN_000edcd0_25\n\t"
      ".long .LFUN_000edcd0_20\n\t"
      ".long .LFUN_000edcd0_21\n\t"
      ".long .LFUN_000edcd0_22\n\t"
      ".long .LFUN_000edcd0_23\n\t"
      ".long .LFUN_000edcd0_24\n\t"
      ".long .LFUN_000edcd0_25\n\t"
      ".text\n\t"
      :
      : [ce0ec0] "m"(bedcd0_ce0ec0), [assert] "m"(bedcd0_assert), [exitfn] "m"(bedcd0_exitfn), [c8f390] "m"(bedcd0_c8f390)
      : "memory");
}
#else
#error "FUN_000edcd0: clang naked draft required"
#endif


/* FUN_000edfb0 (0xedfb0) — XBE naked draft (batch 106). */
#if defined(__clang__)
static void (*const bedfb0_ce0ec0)(void) = player_ui_get_edit_playlist_profile;
static void (*const bedfb0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const bedfb0_exitfn)(int) = system_exit;
static void (*const bedfb0_ftol)(void) = FUN_001d9068;
static void (*const bedfb0_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;

__attribute__((naked, noinline))
void FUN_000edfb0(void *widget __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[ce0ec0]\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "cmpw $3, 0xe(%%esi)\n\t"
      "movl %%eax, %%edi\n\t"
      "movl %%edi, -0x4(%%ebp)\n\t"
      "je .LFUN_000edfb0_1\n\t"
      "pushl $1\n\t"
      "pushl $0xca5\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x287b1c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000edfb0_1:\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "cmpl %%ebx, %%edi\n\t"
      "je .LFUN_000edfb0_64\n\t"
      "movl 0x34(%%esi), %%edi\n\t"
      "cmpl %%ebx, %%edi\n\t"
      "jne .LFUN_000edfb0_2\n\t"
      "pushl $1\n\t"
      "pushl $0xcad\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x287654\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000edfb0_2:\n\t"
      "movl 0x34(%%edi), %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "movl $2, %%ecx\n\t"
      "je .LFUN_000edfb0_4\n\t"
      ".LFUN_000edfb0_3:\n\t"
      "cmpw %%cx, 0xe(%%esi)\n\t"
      "je .LFUN_000edfb0_5\n\t"
      "movl 0x2c(%%esi), %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "jne .LFUN_000edfb0_3\n\t"
      ".LFUN_000edfb0_4:\n\t"
      "pushl $1\n\t"
      "pushl $0xcaf\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x287624\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "movl $2, %%ecx\n\t"
      ".LFUN_000edfb0_5:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movl 0x38(%%eax), %%eax\n\t"
      "cmpl $5, %%eax\n\t"
      "ja .LFUN_000edfb0_9\n\t"
      "jmp *.LFUN_000edfb0_jt0(,%%eax,4)\n\t"
      ".LFUN_000edfb0_6:\n\t"
      "movw $1, 0x3c(%%esi)\n\t"
      "jmp .LFUN_000edfb0_10\n\t"
      ".LFUN_000edfb0_7:\n\t"
      "movw %%cx, 0x3c(%%esi)\n\t"
      "jmp .LFUN_000edfb0_10\n\t"
      ".LFUN_000edfb0_8:\n\t"
      "movw $3, 0x3c(%%esi)\n\t"
      "jmp .LFUN_000edfb0_10\n\t"
      ".LFUN_000edfb0_9:\n\t"
      "movw %%bx, 0x3c(%%esi)\n\t"
      ".LFUN_000edfb0_10:\n\t"
      "movl 0x2c(%%edi), %%edi\n\t"
      "cmpl %%ebx, %%edi\n\t"
      "jne .LFUN_000edfb0_11\n\t"
      "pushl $1\n\t"
      "pushl $0xcba\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x2875b8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "movl $2, %%ecx\n\t"
      ".LFUN_000edfb0_11:\n\t"
      "movl 0x34(%%edi), %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "je .LFUN_000edfb0_13\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_000edfb0_12:\n\t"
      "cmpw %%cx, 0xe(%%esi)\n\t"
      "je .LFUN_000edfb0_14\n\t"
      "movl 0x2c(%%esi), %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "jne .LFUN_000edfb0_12\n\t"
      ".LFUN_000edfb0_13:\n\t"
      "pushl $1\n\t"
      "pushl $0xcbc\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x287588\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000edfb0_14:\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "flds 0x3c(%%ecx)\n\t"
      "fmuls 0x287b78\n\t"
      "call *%[ftol]\n\t"
      "movl $0xfffffffb, %%ecx\n\t"
      "subl %%eax, %%ecx\n\t"
      "cmpl $0x23, %%ecx\n\t"
      "ja .LFUN_000edfb0_20\n\t"
      "movzbl 0xee4d8(%%ecx), %%edx\n\t"
      "jmp *.LFUN_000edfb0_jt1(,%%edx,4)\n\t"
      ".LFUN_000edfb0_15:\n\t"
      "movw $1, 0x3c(%%esi)\n\t"
      "jmp .LFUN_000edfb0_21\n\t"
      ".LFUN_000edfb0_16:\n\t"
      "movw $2, 0x3c(%%esi)\n\t"
      "jmp .LFUN_000edfb0_21\n\t"
      ".LFUN_000edfb0_17:\n\t"
      "movw $3, 0x3c(%%esi)\n\t"
      "jmp .LFUN_000edfb0_21\n\t"
      ".LFUN_000edfb0_18:\n\t"
      "movw $4, 0x3c(%%esi)\n\t"
      "jmp .LFUN_000edfb0_21\n\t"
      ".LFUN_000edfb0_19:\n\t"
      "movw $5, 0x3c(%%esi)\n\t"
      "jmp .LFUN_000edfb0_21\n\t"
      ".LFUN_000edfb0_20:\n\t"
      "movw %%bx, 0x3c(%%esi)\n\t"
      ".LFUN_000edfb0_21:\n\t"
      "movl 0x2c(%%edi), %%edi\n\t"
      "cmpl %%ebx, %%edi\n\t"
      "jne .LFUN_000edfb0_22\n\t"
      "pushl $1\n\t"
      "pushl $0xcc9\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x287530\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000edfb0_22:\n\t"
      "movl 0x34(%%edi), %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "je .LFUN_000edfb0_24\n\t"
      "movl $2, %%eax\n\t"
      ".LFUN_000edfb0_23:\n\t"
      "cmpw %%ax, 0xe(%%esi)\n\t"
      "je .LFUN_000edfb0_25\n\t"
      "movl 0x2c(%%esi), %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "jne .LFUN_000edfb0_23\n\t"
      ".LFUN_000edfb0_24:\n\t"
      "pushl $1\n\t"
      "pushl $0xccb\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x287508\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000edfb0_25:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movl 0x20(%%eax), %%eax\n\t"
      "shrl $3, %%eax\n\t"
      "andl $1, %%eax\n\t"
      "subl %%ebx, %%eax\n\t"
      "je .LFUN_000edfb0_26\n\t"
      "decl %%eax\n\t"
      "jne .LFUN_000edfb0_26\n\t"
      "movw $1, 0x3c(%%esi)\n\t"
      "jmp .LFUN_000edfb0_27\n\t"
      ".LFUN_000edfb0_26:\n\t"
      "movw %%bx, 0x3c(%%esi)\n\t"
      ".LFUN_000edfb0_27:\n\t"
      "movl 0x2c(%%edi), %%edi\n\t"
      "cmpl %%ebx, %%edi\n\t"
      "jne .LFUN_000edfb0_28\n\t"
      "pushl $1\n\t"
      "pushl $0xcd5\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x2874ac\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000edfb0_28:\n\t"
      "movl 0x34(%%edi), %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "je .LFUN_000edfb0_30\n\t"
      "movl $2, %%eax\n\t"
      ".LFUN_000edfb0_29:\n\t"
      "cmpw %%ax, 0xe(%%esi)\n\t"
      "je .LFUN_000edfb0_31\n\t"
      "movl 0x2c(%%esi), %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "jne .LFUN_000edfb0_29\n\t"
      ".LFUN_000edfb0_30:\n\t"
      "pushl $1\n\t"
      "pushl $0xcd7\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x287480\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000edfb0_31:\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movl 0x30(%%ecx), %%eax\n\t"
      "cmpl $0x12c, %%eax\n\t"
      "jg .LFUN_000edfb0_33\n\t"
      "je .LFUN_000edfb0_32\n\t"
      "cmpl %%ebx, %%eax\n\t"
      "je .LFUN_000edfb0_34\n\t"
      "cmpl $0x96, %%eax\n\t"
      "jne .LFUN_000edfb0_34\n\t"
      "movw $1, 0x3c(%%esi)\n\t"
      "jmp .LFUN_000edfb0_36\n\t"
      ".LFUN_000edfb0_32:\n\t"
      "movw $2, 0x3c(%%esi)\n\t"
      "jmp .LFUN_000edfb0_36\n\t"
      ".LFUN_000edfb0_33:\n\t"
      "cmpl $0x1c2, %%eax\n\t"
      "je .LFUN_000edfb0_35\n\t"
      ".LFUN_000edfb0_34:\n\t"
      "movw %%bx, 0x3c(%%esi)\n\t"
      "jmp .LFUN_000edfb0_36\n\t"
      ".LFUN_000edfb0_35:\n\t"
      "movw $3, 0x3c(%%esi)\n\t"
      ".LFUN_000edfb0_36:\n\t"
      "movl 0x2c(%%edi), %%edi\n\t"
      "cmpl %%ebx, %%edi\n\t"
      "jne .LFUN_000edfb0_37\n\t"
      "pushl $1\n\t"
      "pushl $0xce2\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x28741c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000edfb0_37:\n\t"
      "movl 0x34(%%edi), %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "je .LFUN_000edfb0_39\n\t"
      "movl $2, %%eax\n\t"
      ".LFUN_000edfb0_38:\n\t"
      "cmpw %%ax, 0xe(%%esi)\n\t"
      "je .LFUN_000edfb0_40\n\t"
      "movl 0x2c(%%esi), %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "jne .LFUN_000edfb0_38\n\t"
      ".LFUN_000edfb0_39:\n\t"
      "pushl $1\n\t"
      "pushl $0xce4\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x2873e8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000edfb0_40:\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "movl 0x2c(%%edx), %%eax\n\t"
      "cmpl $0x12c, %%eax\n\t"
      "jg .LFUN_000edfb0_42\n\t"
      "je .LFUN_000edfb0_41\n\t"
      "cmpl %%ebx, %%eax\n\t"
      "je .LFUN_000edfb0_43\n\t"
      "cmpl $0x96, %%eax\n\t"
      "jne .LFUN_000edfb0_43\n\t"
      "movw $1, 0x3c(%%esi)\n\t"
      "jmp .LFUN_000edfb0_45\n\t"
      ".LFUN_000edfb0_41:\n\t"
      "movw $2, 0x3c(%%esi)\n\t"
      "jmp .LFUN_000edfb0_45\n\t"
      ".LFUN_000edfb0_42:\n\t"
      "cmpl $0x1c2, %%eax\n\t"
      "je .LFUN_000edfb0_44\n\t"
      ".LFUN_000edfb0_43:\n\t"
      "movw %%bx, 0x3c(%%esi)\n\t"
      "jmp .LFUN_000edfb0_45\n\t"
      ".LFUN_000edfb0_44:\n\t"
      "movw $3, 0x3c(%%esi)\n\t"
      ".LFUN_000edfb0_45:\n\t"
      "movl 0x2c(%%edi), %%edi\n\t"
      "cmpl %%ebx, %%edi\n\t"
      "jne .LFUN_000edfb0_46\n\t"
      "pushl $1\n\t"
      "pushl $0xcef\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x287380\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000edfb0_46:\n\t"
      "movl 0x34(%%edi), %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "je .LFUN_000edfb0_48\n\t"
      "movl $2, %%eax\n\t"
      ".LFUN_000edfb0_47:\n\t"
      "cmpw %%ax, 0xe(%%esi)\n\t"
      "je .LFUN_000edfb0_49\n\t"
      "movl 0x2c(%%esi), %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "jne .LFUN_000edfb0_47\n\t"
      ".LFUN_000edfb0_48:\n\t"
      "pushl $1\n\t"
      "pushl $0xcf1\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x287354\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000edfb0_49:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movzbl 0x28(%%eax), %%eax\n\t"
      "subl %%ebx, %%eax\n\t"
      "je .LFUN_000edfb0_50\n\t"
      "movw %%bx, 0x3c(%%esi)\n\t"
      "jmp .LFUN_000edfb0_51\n\t"
      ".LFUN_000edfb0_50:\n\t"
      "movw $1, 0x3c(%%esi)\n\t"
      ".LFUN_000edfb0_51:\n\t"
      "movl 0x2c(%%edi), %%edi\n\t"
      "cmpl %%ebx, %%edi\n\t"
      "jne .LFUN_000edfb0_52\n\t"
      "pushl $1\n\t"
      "pushl $0xcfa\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x2872f0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000edfb0_52:\n\t"
      "movl 0x34(%%edi), %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "je .LFUN_000edfb0_54\n\t"
      "movl $2, %%eax\n\t"
      ".LFUN_000edfb0_53:\n\t"
      "cmpw %%ax, 0xe(%%esi)\n\t"
      "je .LFUN_000edfb0_55\n\t"
      "movl 0x2c(%%esi), %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "jne .LFUN_000edfb0_53\n\t"
      ".LFUN_000edfb0_54:\n\t"
      "pushl $1\n\t"
      "pushl $0xcfc\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x2872bc\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000edfb0_55:\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movl 0x20(%%ecx), %%eax\n\t"
      "shrl $4, %%eax\n\t"
      "andl $1, %%eax\n\t"
      "subl %%ebx, %%eax\n\t"
      "je .LFUN_000edfb0_56\n\t"
      "movw %%bx, 0x3c(%%esi)\n\t"
      "jmp .LFUN_000edfb0_57\n\t"
      ".LFUN_000edfb0_56:\n\t"
      "movw $1, 0x3c(%%esi)\n\t"
      ".LFUN_000edfb0_57:\n\t"
      "movl 0x2c(%%edi), %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "jne .LFUN_000edfb0_58\n\t"
      "pushl $1\n\t"
      "pushl $0xd07\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x287b58\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000edfb0_58:\n\t"
      "movl 0x34(%%esi), %%eax\n\t"
      "cmpl %%ebx, %%eax\n\t"
      "movl $2, %%edx\n\t"
      "je .LFUN_000edfb0_60\n\t"
      ".LFUN_000edfb0_59:\n\t"
      "cmpw %%dx, 0xe(%%eax)\n\t"
      "je .LFUN_000edfb0_60\n\t"
      "movl 0x2c(%%eax), %%eax\n\t"
      "cmpl %%ebx, %%eax\n\t"
      "jne .LFUN_000edfb0_59\n\t"
      ".LFUN_000edfb0_60:\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movl 0x34(%%ecx), %%ecx\n\t"
      "cmpl $0x12c, %%ecx\n\t"
      "jg .LFUN_000edfb0_63\n\t"
      "je .LFUN_000edfb0_62\n\t"
      "cmpl %%ebx, %%ecx\n\t"
      "je .LFUN_000edfb0_61\n\t"
      "cmpl $0x96, %%ecx\n\t"
      "jne .LFUN_000edfb0_61\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movw $1, 0x3c(%%eax)\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000edfb0_61:\n\t"
      "popl %%edi\n\t"
      "movw %%bx, 0x3c(%%eax)\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000edfb0_62:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movw %%dx, 0x3c(%%eax)\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000edfb0_63:\n\t"
      "cmpl $0x1c2, %%ecx\n\t"
      "jne .LFUN_000edfb0_61\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movw $3, 0x3c(%%eax)\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000edfb0_64:\n\t"
      "pushl $0x286550\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_000edfb0_jt0:\n\t"
      ".long .LFUN_000edfb0_9\n\t"
      ".long .LFUN_000edfb0_6\n\t"
      ".long .LFUN_000edfb0_9\n\t"
      ".long .LFUN_000edfb0_7\n\t"
      ".long .LFUN_000edfb0_9\n\t"
      ".long .LFUN_000edfb0_8\n\t"
      ".text\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_000edfb0_jt1:\n\t"
      ".long .LFUN_000edfb0_20\n\t"
      ".long .LFUN_000edfb0_15\n\t"
      ".long .LFUN_000edfb0_16\n\t"
      ".long .LFUN_000edfb0_17\n\t"
      ".long .LFUN_000edfb0_18\n\t"
      ".long .LFUN_000edfb0_19\n\t"
      ".long .LFUN_000edfb0_20\n\t"
      ".text\n\t"
      :
      : [ce0ec0] "m"(bedfb0_ce0ec0), [assert] "m"(bedfb0_assert), [exitfn] "m"(bedfb0_exitfn), [ftol] "m"(bedfb0_ftol), [c8f390] "m"(bedfb0_c8f390)
      : "memory");
}
#else
#error "FUN_000edfb0: clang naked draft required"
#endif


/* FUN_000ee500 (0xee500) — XBE naked draft (batch 110). */
#if defined(__clang__)
static void (*const bee500_ce0ec0)(void) = player_ui_get_edit_playlist_profile;
static void (*const bee500_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const bee500_exitfn)(int) = system_exit;
static void (*const bee500_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;

__attribute__((naked, noinline))
void FUN_000ee500(void *widget __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[ce0ec0]\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "cmpw $3, 0xe(%%esi)\n\t"
      "movl %%eax, %%edi\n\t"
      "movl %%edi, -0x4(%%ebp)\n\t"
      "je .LFUN_000ee500_1\n\t"
      "pushl $1\n\t"
      "pushl $0xd26\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x287b1c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000ee500_1:\n\t"
      "testl %%edi, %%edi\n\t"
      "je .LFUN_000ee500_40\n\t"
      "movl 0x34(%%esi), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .LFUN_000ee500_2\n\t"
      "pushl $1\n\t"
      "pushl $0xd2e\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x2878a8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000ee500_2:\n\t"
      "movl 0x34(%%edi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_000ee500_4\n\t"
      ".LFUN_000ee500_3:\n\t"
      "cmpw $2, 0xe(%%esi)\n\t"
      "je .LFUN_000ee500_5\n\t"
      "movl 0x2c(%%esi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LFUN_000ee500_3\n\t"
      ".LFUN_000ee500_4:\n\t"
      "pushl $1\n\t"
      "pushl $0xd30\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x287874\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000ee500_5:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movl 0x20(%%eax), %%eax\n\t"
      "shrl $2, %%eax\n\t"
      "andl $1, %%eax\n\t"
      "subl $0, %%eax\n\t"
      "je .LFUN_000ee500_6\n\t"
      "movw $0, 0x3c(%%esi)\n\t"
      "jmp .LFUN_000ee500_7\n\t"
      ".LFUN_000ee500_6:\n\t"
      "movw $1, 0x3c(%%esi)\n\t"
      ".LFUN_000ee500_7:\n\t"
      "movl 0x2c(%%edi), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .LFUN_000ee500_8\n\t"
      "pushl $1\n\t"
      "pushl $0xd3a\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x28780c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000ee500_8:\n\t"
      "movl 0x34(%%edi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_000ee500_10\n\t"
      "movl $2, %%eax\n\t"
      ".LFUN_000ee500_9:\n\t"
      "cmpw %%ax, 0xe(%%esi)\n\t"
      "je .LFUN_000ee500_11\n\t"
      "movl 0x2c(%%esi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LFUN_000ee500_9\n\t"
      ".LFUN_000ee500_10:\n\t"
      "pushl $1\n\t"
      "pushl $0xd3c\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x2877e0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000ee500_11:\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movl 0x48(%%ecx), %%eax\n\t"
      "cmpl $4, %%eax\n\t"
      "ja .LFUN_000ee500_16\n\t"
      "jmp *.LFUN_000ee500_jt0(,%%eax,4)\n\t"
      ".LFUN_000ee500_12:\n\t"
      "movw $1, 0x3c(%%esi)\n\t"
      "jmp .LFUN_000ee500_17\n\t"
      ".LFUN_000ee500_13:\n\t"
      "movw $2, 0x3c(%%esi)\n\t"
      "jmp .LFUN_000ee500_17\n\t"
      ".LFUN_000ee500_14:\n\t"
      "movw $3, 0x3c(%%esi)\n\t"
      "jmp .LFUN_000ee500_17\n\t"
      ".LFUN_000ee500_15:\n\t"
      "movw $4, 0x3c(%%esi)\n\t"
      "jmp .LFUN_000ee500_17\n\t"
      ".LFUN_000ee500_16:\n\t"
      "movw $0, 0x3c(%%esi)\n\t"
      ".LFUN_000ee500_17:\n\t"
      "movl 0x2c(%%edi), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .LFUN_000ee500_18\n\t"
      "pushl $1\n\t"
      "pushl $0xd48\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x287784\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000ee500_18:\n\t"
      "movl 0x34(%%edi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_000ee500_20\n\t"
      "movl $2, %%eax\n\t"
      ".LFUN_000ee500_19:\n\t"
      "cmpw %%ax, 0xe(%%esi)\n\t"
      "je .LFUN_000ee500_21\n\t"
      "movl 0x2c(%%esi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LFUN_000ee500_19\n\t"
      ".LFUN_000ee500_20:\n\t"
      "pushl $1\n\t"
      "pushl $0xd4a\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x287758\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000ee500_21:\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "movl 0x44(%%edx), %%eax\n\t"
      "cmpl $0xa, %%eax\n\t"
      "ja .LFUN_000ee500_32\n\t"
      "jmp *.LFUN_000ee500_jt1(,%%eax,4)\n\t"
      ".LFUN_000ee500_22:\n\t"
      "movw $1, 0x3c(%%esi)\n\t"
      "jmp .LFUN_000ee500_33\n\t"
      ".LFUN_000ee500_23:\n\t"
      "movw $2, 0x3c(%%esi)\n\t"
      "jmp .LFUN_000ee500_33\n\t"
      ".LFUN_000ee500_24:\n\t"
      "movw $3, 0x3c(%%esi)\n\t"
      "jmp .LFUN_000ee500_33\n\t"
      ".LFUN_000ee500_25:\n\t"
      "movw $4, 0x3c(%%esi)\n\t"
      "jmp .LFUN_000ee500_33\n\t"
      ".LFUN_000ee500_26:\n\t"
      "movw $5, 0x3c(%%esi)\n\t"
      "jmp .LFUN_000ee500_33\n\t"
      ".LFUN_000ee500_27:\n\t"
      "movw $6, 0x3c(%%esi)\n\t"
      "jmp .LFUN_000ee500_33\n\t"
      ".LFUN_000ee500_28:\n\t"
      "movw $7, 0x3c(%%esi)\n\t"
      "jmp .LFUN_000ee500_33\n\t"
      ".LFUN_000ee500_29:\n\t"
      "movw $8, 0x3c(%%esi)\n\t"
      "jmp .LFUN_000ee500_33\n\t"
      ".LFUN_000ee500_30:\n\t"
      "movw $9, 0x3c(%%esi)\n\t"
      "jmp .LFUN_000ee500_33\n\t"
      ".LFUN_000ee500_31:\n\t"
      "movw $0xa, 0x3c(%%esi)\n\t"
      "jmp .LFUN_000ee500_33\n\t"
      ".LFUN_000ee500_32:\n\t"
      "movw $0, 0x3c(%%esi)\n\t"
      ".LFUN_000ee500_33:\n\t"
      "movl 0x2c(%%edi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LFUN_000ee500_34\n\t"
      "pushl $1\n\t"
      "pushl $0xd5d\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x2876f8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000ee500_34:\n\t"
      "movl 0x34(%%esi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_000ee500_36\n\t"
      "movl $2, %%eax\n\t"
      ".LFUN_000ee500_35:\n\t"
      "cmpw %%ax, 0xe(%%esi)\n\t"
      "je .LFUN_000ee500_37\n\t"
      "movl 0x2c(%%esi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LFUN_000ee500_35\n\t"
      ".LFUN_000ee500_36:\n\t"
      "pushl $1\n\t"
      "pushl $0xd5f\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x287b7c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000ee500_37:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movl 0x20(%%eax), %%eax\n\t"
      "shrl $5, %%eax\n\t"
      "andl $1, %%eax\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "subl %%ecx, %%eax\n\t"
      "je .LFUN_000ee500_39\n\t"
      "decl %%eax\n\t"
      "movb $1, %%al\n\t"
      "je .LFUN_000ee500_38\n\t"
      "popl %%edi\n\t"
      "movw %%cx, 0x3c(%%esi)\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000ee500_38:\n\t"
      "popl %%edi\n\t"
      "movw $1, 0x3c(%%esi)\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000ee500_39:\n\t"
      "popl %%edi\n\t"
      "movw %%cx, 0x3c(%%esi)\n\t"
      "movb $1, %%al\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000ee500_40:\n\t"
      "pushl $0x286550\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "popl %%edi\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_000ee500_jt0:\n\t"
      ".long .LFUN_000ee500_16\n\t"
      ".long .LFUN_000ee500_12\n\t"
      ".long .LFUN_000ee500_13\n\t"
      ".long .LFUN_000ee500_14\n\t"
      ".long .LFUN_000ee500_15\n\t"
      ".text\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_000ee500_jt1:\n\t"
      ".long .LFUN_000ee500_32\n\t"
      ".long .LFUN_000ee500_22\n\t"
      ".long .LFUN_000ee500_23\n\t"
      ".long .LFUN_000ee500_24\n\t"
      ".long .LFUN_000ee500_25\n\t"
      ".long .LFUN_000ee500_26\n\t"
      ".long .LFUN_000ee500_27\n\t"
      ".long .LFUN_000ee500_28\n\t"
      ".long .LFUN_000ee500_29\n\t"
      ".long .LFUN_000ee500_30\n\t"
      ".long .LFUN_000ee500_31\n\t"
      ".text\n\t"
      :
      : [ce0ec0] "m"(bee500_ce0ec0), [assert] "m"(bee500_assert), [exitfn] "m"(bee500_exitfn), [c8f390] "m"(bee500_c8f390)
      : "memory");
}
#else
#error "FUN_000ee500: clang naked draft required"
#endif


/* FUN_000ee810 (0xee810) — XBE naked draft (batch 116). */
#if defined(__clang__)
static void (*const bee810_ce0ec0)(void) = player_ui_get_edit_playlist_profile;
static void (*const bee810_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const bee810_exitfn)(int) = system_exit;
static void (*const bee810_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;

__attribute__((naked, noinline))
void FUN_000ee810(void *widget __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[ce0ec0]\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "cmpw $3, 0xe(%%esi)\n\t"
      "movl %%eax, %%edi\n\t"
      "movl %%edi, -0x4(%%ebp)\n\t"
      "je .LFUN_000ee810_1\n\t"
      "pushl $1\n\t"
      "pushl $0xd7a\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x287b1c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000ee810_1:\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "cmpl %%ebx, %%edi\n\t"
      "je .LFUN_000ee810_20\n\t"
      "movl 0x34(%%esi), %%edi\n\t"
      "cmpl %%ebx, %%edi\n\t"
      "jne .LFUN_000ee810_2\n\t"
      "pushl $1\n\t"
      "pushl $0xd82\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x287a8c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000ee810_2:\n\t"
      "movl 0x34(%%edi), %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "je .LFUN_000ee810_4\n\t"
      ".LFUN_000ee810_3:\n\t"
      "movl $2, %%ecx\n\t"
      "cmpw %%cx, 0xe(%%esi)\n\t"
      "je .LFUN_000ee810_5\n\t"
      "movl 0x2c(%%esi), %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "jne .LFUN_000ee810_3\n\t"
      ".LFUN_000ee810_4:\n\t"
      "pushl $1\n\t"
      "pushl $0xd84\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x287a5c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "movl $2, %%ecx\n\t"
      ".LFUN_000ee810_5:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movl 0x24(%%eax), %%eax\n\t"
      "subl %%ebx, %%eax\n\t"
      "je .LFUN_000ee810_7\n\t"
      "decl %%eax\n\t"
      "je .LFUN_000ee810_6\n\t"
      "decl %%eax\n\t"
      "jne .LFUN_000ee810_7\n\t"
      "movw %%cx, 0x3c(%%esi)\n\t"
      "jmp .LFUN_000ee810_8\n\t"
      ".LFUN_000ee810_6:\n\t"
      "movw $1, 0x3c(%%esi)\n\t"
      "jmp .LFUN_000ee810_8\n\t"
      ".LFUN_000ee810_7:\n\t"
      "movw %%bx, 0x3c(%%esi)\n\t"
      ".LFUN_000ee810_8:\n\t"
      "movl 0x2c(%%edi), %%edi\n\t"
      "cmpl %%ebx, %%edi\n\t"
      "jne .LFUN_000ee810_9\n\t"
      "pushl $1\n\t"
      "pushl $0xd8e\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x2879f0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "movl $2, %%ecx\n\t"
      ".LFUN_000ee810_9:\n\t"
      "movl 0x34(%%edi), %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "je .LFUN_000ee810_11\n\t"
      "nop\n\t"
      ".LFUN_000ee810_10:\n\t"
      "cmpw %%cx, 0xe(%%esi)\n\t"
      "je .LFUN_000ee810_12\n\t"
      "movl 0x2c(%%esi), %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "jne .LFUN_000ee810_10\n\t"
      ".LFUN_000ee810_11:\n\t"
      "pushl $1\n\t"
      "pushl $0xd90\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x2879b8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "movl $2, %%ecx\n\t"
      ".LFUN_000ee810_12:\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "movl 0x20(%%edx), %%eax\n\t"
      "andl $1, %%eax\n\t"
      "subl %%ebx, %%eax\n\t"
      "je .LFUN_000ee810_13\n\t"
      "movw %%bx, 0x3c(%%esi)\n\t"
      "jmp .LFUN_000ee810_14\n\t"
      ".LFUN_000ee810_13:\n\t"
      "movw $1, 0x3c(%%esi)\n\t"
      ".LFUN_000ee810_14:\n\t"
      "movl 0x2c(%%edi), %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "jne .LFUN_000ee810_15\n\t"
      "pushl $1\n\t"
      "pushl $0xd9a\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x287948\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "movl $2, %%ecx\n\t"
      ".LFUN_000ee810_15:\n\t"
      "movl 0x34(%%esi), %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "je .LFUN_000ee810_17\n\t"
      "movl %%edi, %%edi\n\t"
      ".LFUN_000ee810_16:\n\t"
      "cmpw %%cx, 0xe(%%esi)\n\t"
      "je .LFUN_000ee810_18\n\t"
      "movl 0x2c(%%esi), %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "jne .LFUN_000ee810_16\n\t"
      ".LFUN_000ee810_17:\n\t"
      "pushl $1\n\t"
      "pushl $0xd9c\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x287914\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000ee810_18:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movl 0x20(%%eax), %%eax\n\t"
      "shrl $1, %%eax\n\t"
      "andl $1, %%eax\n\t"
      "subl %%ebx, %%eax\n\t"
      "je .LFUN_000ee810_19\n\t"
      "popl %%edi\n\t"
      "movw %%bx, 0x3c(%%esi)\n\t"
      "popl %%esi\n\t"
      "decl %%eax\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000ee810_19:\n\t"
      "popl %%edi\n\t"
      "movw $1, 0x3c(%%esi)\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000ee810_20:\n\t"
      "pushl $0x286550\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [ce0ec0] "m"(bee810_ce0ec0), [assert] "m"(bee810_assert), [exitfn] "m"(bee810_exitfn), [c8f390] "m"(bee810_c8f390)
      : "memory");
}
#else
#error "FUN_000ee810: clang naked draft required"
#endif


/* 0xeea10 */
void playlist_profile_initialize_name(void *widget)
{
  int eax = 0;
  int ebx = 0;

  /* test eax, eax -> jne 0xeea3d */
  display_assert((char *)0x00286184, (char *)0x002859a4, 3510, 0);
  system_exit(0);
  player_ui_edit_profile_is_dirty();
  /* test (char)eax, (char)eax -> je 0xeea94 */
  player_ui_edit_profile_is_default_profile();
  /* test (char)eax, (char)eax -> je 0xeea75 */
  player_ui_edit_profile_name_is_dirty();
  /* test (char)eax, (char)eax -> jne 0xeea75 */
  player_ui_prompt_user_to_rename_edit_profile();
  /* test (char)eax, (char)eax -> jne 0xeeabd */
  error(0, (char *)0x00287c24);
  player_ui_save_profile();
  /* test (char)ebx, (char)ebx -> jne 0xeeabd */
  error(0, (char *)0x00287bec);
  error(0, (char *)0x00287bb0);
  player_ui_end_editing_profile();
  ui_widget_get_last_child((void *)(uintptr_t)eax);
  ui_widget_close((void *)(uintptr_t)eax);

  (void)eax;
  (void)ebx;
}

/* playlist_profile_initialize_ctf_rules (0xeead0) — XBE naked draft (batch 128). */
#if defined(__clang__)
static unsigned short (*const beead0_c1c0ed0)(void) = FUN_001c0ed0;
static void (*const beead0_ce0ea0)(void) = player_ui_get_edit_player_profile;
static void *(*const beead0_tag)(int, int) = tag_get;
static void (*const beead0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const beead0_exitfn)(int) = system_exit;
static void * (*const beead0_ce3d20)(int a1, unsigned short a2, const char *a3, unsigned int a4) = ui_widget_realloc;
static void (*const beead0_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;

__attribute__((naked, noinline))
void playlist_profile_initialize_ctf_rules(void *widget __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c1c0ed0]\n\t"
      "movl %%eax, %%ebx\n\t"
      "call *%[ce0ea0]\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "movl (%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x44654c61\n\t"
      "call *%[tag]\n\t"
      "movl %%eax, %%edi\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $2, (%%edi)\n\t"
      "je .Lplaylist_profile_initialize_ctf_rules_1\n\t"
      "pushl $1\n\t"
      "pushl $0xdf8\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x287cb0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lplaylist_profile_initialize_ctf_rules_1:\n\t"
      "cmpl $3, 0x3e0(%%edi)\n\t"
      "je .Lplaylist_profile_initialize_ctf_rules_2\n\t"
      "pushl $1\n\t"
      "pushl $0xdf9\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x287c74\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lplaylist_profile_initialize_ctf_rules_2:\n\t"
      "movl 0x40(%%esi), %%ecx\n\t"
      "pushl $0xdfd\n\t"
      "pushl $0x2859a4\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ecx\n\t"
      "call *%[ce3d20]\n\t"
      "addl $0x10, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%eax, 0x40(%%esi)\n\t"
      "je .Lplaylist_profile_initialize_ctf_rules_5\n\t"
      "movzwl %%bx, %%ecx\n\t"
      "xorl %%eax, %%eax\n\t"
      "testl %%ecx, %%ecx\n\t"
      "jle .Lplaylist_profile_initialize_ctf_rules_4\n\t"
      ".Lplaylist_profile_initialize_ctf_rules_3:\n\t"
      "movl 0x40(%%esi), %%edx\n\t"
      "movb %%al, (%%eax,%%edx,1)\n\t"
      "incl %%eax\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jl .Lplaylist_profile_initialize_ctf_rules_3\n\t"
      ".Lplaylist_profile_initialize_ctf_rules_4:\n\t"
      "movw %%bx, 0x44(%%esi)\n\t"
      ".Lplaylist_profile_initialize_ctf_rules_5:\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "testl %%edx, %%edx\n\t"
      "je .Lplaylist_profile_initialize_ctf_rules_8\n\t"
      "movw 0x18(%%edx), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "jge .Lplaylist_profile_initialize_ctf_rules_6\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw %%ax, 0x18(%%edx)\n\t"
      "popl %%edi\n\t"
      "movw %%ax, 0x3c(%%esi)\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lplaylist_profile_initialize_ctf_rules_6:\n\t"
      "movzwl %%bx, %%ecx\n\t"
      "movswl %%ax, %%eax\n\t"
      "decl %%ecx\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jle .Lplaylist_profile_initialize_ctf_rules_7\n\t"
      "movl %%ecx, %%eax\n\t"
      ".Lplaylist_profile_initialize_ctf_rules_7:\n\t"
      "movw %%ax, 0x18(%%edx)\n\t"
      "popl %%edi\n\t"
      "movw %%ax, 0x3c(%%esi)\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lplaylist_profile_initialize_ctf_rules_8:\n\t"
      "pushl $0x287c4c\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c1c0ed0] "m"(beead0_c1c0ed0), [ce0ea0] "m"(beead0_ce0ea0), [tag] "m"(beead0_tag), [assert] "m"(beead0_assert), [exitfn] "m"(beead0_exitfn), [ce3d20] "m"(beead0_ce3d20), [c8f390] "m"(beead0_c8f390)
      : "memory");
}
#else
#error "playlist_profile_initialize_ctf_rules: clang naked draft required"
#endif


/* 0xeebe0 */
void FUN_000eebe0(void *widget)
{
  int eax = 0;

  /* test eax, eax -> je 0xeebfe */
  widget_free((void *)(uintptr_t)eax);

  (void)eax;
}

/* 0xeec10 */
void FUN_000eec10(void *widget)
{
  int eax = 0;
  int ebx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  player_ui_get_edit_player_profile();
  /* relift: cmp word ptr [esi + 0xe], 2 -> je 0xeec4d */
  display_assert((char *)0x00287d78, (char *)0x002859a4, 3630, 0);
  system_exit(0);
  tag_get(0x44654c61, 0);
  /* relift: cmp word ptr [edi], 2 -> je 0xeec86 */
  display_assert((char *)0x00287cb0, (char *)0x002859a4, 3637, 0);
  system_exit(0);
  display_assert((char *)0x00287c74, (char *)0x002859a4, 3638, 0);
  system_exit(0);
  /* relift: cmp word ptr [esi + 0x3c], 0 -> jl 0xeecc7 */
  FUN_001c0ed0();
  /* cmp eax, edx -> jl 0xeece7 */
  display_assert((char *)0x00287d48, (char *)0x002859a4, 3644, 0);
  system_exit(0);
  /* test ebx, ebx -> je 0xeecf9 */
  error(0, (char *)0x00287cf8);

  (void)eax;
  (void)ebx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* FUN_000eed10 (0xeed10) — XBE naked draft (batch 117). */
#if defined(__clang__)
static void (*const beed10_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const beed10_exitfn)(int) = system_exit;
static void *(*const beed10_tag)(int, int) = tag_get;
static void (*const beed10_ce1500)(void) = player_ui_begin_editing_profile;
static void (*const beed10_ce4500)(int16_t error_handle, int16_t local_player_index, char a3, char a4) = display_error_deferred;
static void (*const beed10_ce5ab0)(int16_t sound_selector) = ui_play_audio_feedback_sound;

__attribute__((naked, noinline))
void FUN_000eed10(void *widget __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "xorb %%bl, %%bl\n\t"
      "cmpw $0, 0xe(%%esi)\n\t"
      "je .LFUN_000eed10_1\n\t"
      "pushl $1\n\t"
      "pushl $0xe53\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x287e10\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000eed10_1:\n\t"
      "movl 0x34(%%esi), %%eax\n\t"
      "movl (%%eax), %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "pushl $0x44654c61\n\t"
      "movl $0xffffffff, 0x31e494\n\t"
      "call *%[tag]\n\t"
      "movl %%eax, %%edi\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $2, (%%edi)\n\t"
      "je .LFUN_000eed10_2\n\t"
      "pushl $1\n\t"
      "pushl $0xe5d\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x286320\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000eed10_2:\n\t"
      "cmpl $3, 0x3e0(%%edi)\n\t"
      "popl %%edi\n\t"
      "je .LFUN_000eed10_3\n\t"
      "pushl $1\n\t"
      "pushl $0xe5e\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x2862e8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000eed10_3:\n\t"
      "movl 0x34(%%esi), %%esi\n\t"
      "movw 0x3c(%%esi), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "jl .LFUN_000eed10_4\n\t"
      "movzwl 0x44(%%esi), %%ecx\n\t"
      "movswl %%ax, %%edx\n\t"
      "cmpl %%ecx, %%edx\n\t"
      "jl .LFUN_000eed10_5\n\t"
      ".LFUN_000eed10_4:\n\t"
      "pushl $1\n\t"
      "pushl $0xe67\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x287dc8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000eed10_5:\n\t"
      "movswl 0x3c(%%esi), %%eax\n\t"
      "movl 0x40(%%esi), %%ecx\n\t"
      "movl (%%ecx,%%eax,4), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_000eed10_7\n\t"
      "testl %%eax, %%eax\n\t"
      "jns .LFUN_000eed10_6\n\t"
      "pushl %%eax\n\t"
      "call *%[ce1500]\n\t"
      "addl $4, %%esp\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000eed10_6:\n\t"
      "pushl $0\n\t"
      "pushl $1\n\t"
      "pushl $-1\n\t"
      "pushl $0x1f\n\t"
      "call *%[ce4500]\n\t"
      "pushl $4\n\t"
      "call *%[ce5ab0]\n\t"
      "addl $0x14, %%esp\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000eed10_7:\n\t"
      "pushl $4\n\t"
      "call *%[ce5ab0]\n\t"
      "addl $4, %%esp\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(beed10_assert), [exitfn] "m"(beed10_exitfn), [tag] "m"(beed10_tag), [ce1500] "m"(beed10_ce1500), [ce4500] "m"(beed10_ce4500), [ce5ab0] "m"(beed10_ce5ab0)
      : "memory");
}
#else
#error "FUN_000eed10: clang naked draft required"
#endif


/* 0xeeeb0 */
void FUN_000eeeb0(void *widget)
{
  int eax = 0;
  int ebx = 0;

  /* test eax, eax -> jne 0xeeedd */
  display_assert((char *)0x00286184, (char *)0x002859a4, 3759, 0);
  system_exit(0);
  player_ui_edit_profile_is_dirty();
  /* test (char)eax, (char)eax -> je 0xeeef8 */
  player_ui_save_profile();
  /* test (char)ebx, (char)ebx -> jne 0xeef24 */
  error(0, (char *)0x00287ebc);
  player_ui_end_editing_profile();
  ui_widget_get_last_child((void *)(uintptr_t)eax);
  ui_widget_close((void *)(uintptr_t)eax);

  (void)eax;
  (void)ebx;
}

/* FUN_000eef30 (0xeef30) — XBE naked draft (batch 117). */
#if defined(__clang__)
static void (*const beef30_ce0ea0)(void) = player_ui_get_edit_player_profile;
static void (*const beef30_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const beef30_exitfn)(int) = system_exit;
static void (*const beef30_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;

__attribute__((naked, noinline))
void FUN_000eef30(void *widget __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[ce0ea0]\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "cmpw $3, 0xe(%%esi)\n\t"
      "movl %%eax, %%edi\n\t"
      "movl %%edi, -0x4(%%ebp)\n\t"
      "movb $1, %%bl\n\t"
      "je .LFUN_000eef30_1\n\t"
      "pushl $1\n\t"
      "pushl $0xed1\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x287fd0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000eef30_1:\n\t"
      "testl %%edi, %%edi\n\t"
      "je .LFUN_000eef30_20\n\t"
      "movl 0x34(%%esi), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .LFUN_000eef30_2\n\t"
      "pushl $1\n\t"
      "pushl $0xed9\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x287fa8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000eef30_2:\n\t"
      "movl 0x34(%%edi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_000eef30_4\n\t"
      ".LFUN_000eef30_3:\n\t"
      "movl $2, %%ecx\n\t"
      "cmpw %%cx, 0xe(%%esi)\n\t"
      "je .LFUN_000eef30_5\n\t"
      "movl 0x2c(%%esi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LFUN_000eef30_3\n\t"
      ".LFUN_000eef30_4:\n\t"
      "pushl $1\n\t"
      "pushl $0xedb\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x287f78\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "movl $2, %%ecx\n\t"
      ".LFUN_000eef30_5:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movzbl 0x29(%%eax), %%eax\n\t"
      "cmpl $3, %%eax\n\t"
      "ja .LFUN_000eef30_9\n\t"
      "jmp *.LFUN_000eef30_jt0(,%%eax,4)\n\t"
      ".LFUN_000eef30_6:\n\t"
      "movw $1, 0x3c(%%esi)\n\t"
      "jmp .LFUN_000eef30_10\n\t"
      ".LFUN_000eef30_7:\n\t"
      "movw %%cx, 0x3c(%%esi)\n\t"
      "jmp .LFUN_000eef30_10\n\t"
      ".LFUN_000eef30_8:\n\t"
      "movw $3, 0x3c(%%esi)\n\t"
      "jmp .LFUN_000eef30_10\n\t"
      ".LFUN_000eef30_9:\n\t"
      "movw $0, 0x3c(%%esi)\n\t"
      ".LFUN_000eef30_10:\n\t"
      "movl 0x2c(%%edi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LFUN_000eef30_11\n\t"
      "pushl $1\n\t"
      "pushl $0xee6\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x287f54\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "movl $2, %%ecx\n\t"
      ".LFUN_000eef30_11:\n\t"
      "movl 0x34(%%esi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_000eef30_13\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_000eef30_12:\n\t"
      "cmpw %%cx, 0xe(%%esi)\n\t"
      "je .LFUN_000eef30_14\n\t"
      "movl 0x2c(%%esi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LFUN_000eef30_12\n\t"
      ".LFUN_000eef30_13:\n\t"
      "pushl $1\n\t"
      "pushl $0xee8\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x287f24\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "movl $2, %%ecx\n\t"
      ".LFUN_000eef30_14:\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "movzbl 0x28(%%edx), %%eax\n\t"
      "cmpl $4, %%eax\n\t"
      "ja .LFUN_000eef30_15\n\t"
      "jmp *.LFUN_000eef30_jt1(,%%eax,4)\n\t"
      ".LFUN_000eef30_15:\n\t"
      "popl %%edi\n\t"
      "movw $0, 0x3c(%%esi)\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000eef30_16:\n\t"
      "popl %%edi\n\t"
      "movw $1, 0x3c(%%esi)\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000eef30_17:\n\t"
      "popl %%edi\n\t"
      "movw %%cx, 0x3c(%%esi)\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000eef30_18:\n\t"
      "popl %%edi\n\t"
      "movw $3, 0x3c(%%esi)\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000eef30_19:\n\t"
      "popl %%edi\n\t"
      "movw $4, 0x3c(%%esi)\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000eef30_20:\n\t"
      "pushl $0x287e54\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_000eef30_jt0:\n\t"
      ".long .LFUN_000eef30_9\n\t"
      ".long .LFUN_000eef30_6\n\t"
      ".long .LFUN_000eef30_7\n\t"
      ".long .LFUN_000eef30_8\n\t"
      ".text\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_000eef30_jt1:\n\t"
      ".long .LFUN_000eef30_15\n\t"
      ".long .LFUN_000eef30_16\n\t"
      ".long .LFUN_000eef30_17\n\t"
      ".long .LFUN_000eef30_18\n\t"
      ".long .LFUN_000eef30_19\n\t"
      ".text\n\t"
      :
      : [ce0ea0] "m"(beef30_ce0ea0), [assert] "m"(beef30_assert), [exitfn] "m"(beef30_exitfn), [c8f390] "m"(beef30_c8f390)
      : "memory");
}
#else
#error "FUN_000eef30: clang naked draft required"
#endif


/* FUN_000ef110 (0xef110) — XBE naked draft (batch 111). */
#if defined(__clang__)
static void (*const bef110_ce0ea0)(void) = player_ui_get_edit_player_profile;
static void (*const bef110_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const bef110_exitfn)(int) = system_exit;
static void (*const bef110_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;

__attribute__((naked, noinline))
void FUN_000ef110(void *widget __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[ce0ea0]\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "cmpw $3, 0xe(%%esi)\n\t"
      "movl %%eax, %%edi\n\t"
      "movl %%edi, -0x4(%%ebp)\n\t"
      "je .LFUN_000ef110_1\n\t"
      "pushl $1\n\t"
      "pushl $0xf04\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x2881c4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000ef110_1:\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "cmpl %%ebx, %%edi\n\t"
      "je .LFUN_000ef110_31\n\t"
      "movl 0x34(%%esi), %%edi\n\t"
      "cmpl %%ebx, %%edi\n\t"
      "jne .LFUN_000ef110_2\n\t"
      "pushl $1\n\t"
      "pushl $0xf0c\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x28819c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000ef110_2:\n\t"
      "movl 0x34(%%edi), %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "je .LFUN_000ef110_4\n\t"
      ".LFUN_000ef110_3:\n\t"
      "cmpw $2, 0xe(%%esi)\n\t"
      "je .LFUN_000ef110_5\n\t"
      "movl 0x2c(%%esi), %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "jne .LFUN_000ef110_3\n\t"
      ".LFUN_000ef110_4:\n\t"
      "pushl $1\n\t"
      "pushl $0xf0e\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x28816c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000ef110_5:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movzbl 0x2b(%%eax), %%eax\n\t"
      "subl %%ebx, %%eax\n\t"
      "je .LFUN_000ef110_6\n\t"
      "movw %%bx, 0x3c(%%esi)\n\t"
      "jmp .LFUN_000ef110_7\n\t"
      ".LFUN_000ef110_6:\n\t"
      "movw $1, 0x3c(%%esi)\n\t"
      ".LFUN_000ef110_7:\n\t"
      "movl 0x2c(%%edi), %%edi\n\t"
      "cmpl %%ebx, %%edi\n\t"
      "jne .LFUN_000ef110_8\n\t"
      "pushl $1\n\t"
      "pushl $0xf17\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x288144\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000ef110_8:\n\t"
      "movl 0x34(%%edi), %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "je .LFUN_000ef110_10\n\t"
      "movl $2, %%eax\n\t"
      "jmp .LFUN_000ef110_9\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".LFUN_000ef110_9:\n\t"
      "cmpw %%ax, 0xe(%%esi)\n\t"
      "je .LFUN_000ef110_11\n\t"
      "movl 0x2c(%%esi), %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "jne .LFUN_000ef110_9\n\t"
      ".LFUN_000ef110_10:\n\t"
      "pushl $1\n\t"
      "pushl $0xf19\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x288114\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000ef110_11:\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movb 0x2a(%%ecx), %%al\n\t"
      "cmpb %%bl, %%al\n\t"
      "jbe .LFUN_000ef110_12\n\t"
      "cmpb $0xa, %%al\n\t"
      "ja .LFUN_000ef110_12\n\t"
      "movzbw %%al, %%dx\n\t"
      "decl %%edx\n\t"
      "movw %%dx, 0x3c(%%esi)\n\t"
      "jmp .LFUN_000ef110_13\n\t"
      ".LFUN_000ef110_12:\n\t"
      "movw %%bx, 0x3c(%%esi)\n\t"
      ".LFUN_000ef110_13:\n\t"
      "movl 0x2c(%%edi), %%edi\n\t"
      "cmpl %%ebx, %%edi\n\t"
      "jne .LFUN_000ef110_14\n\t"
      "pushl $1\n\t"
      "pushl $0xf2c\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x2880e8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000ef110_14:\n\t"
      "movl 0x34(%%edi), %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "je .LFUN_000ef110_16\n\t"
      "movl $2, %%eax\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".LFUN_000ef110_15:\n\t"
      "cmpw %%ax, 0xe(%%esi)\n\t"
      "je .LFUN_000ef110_17\n\t"
      "movl 0x2c(%%esi), %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "jne .LFUN_000ef110_15\n\t"
      ".LFUN_000ef110_16:\n\t"
      "pushl $1\n\t"
      "pushl $0xf2e\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x2880b4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000ef110_17:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movzbl 0x2c(%%eax), %%eax\n\t"
      "subl %%ebx, %%eax\n\t"
      "je .LFUN_000ef110_18\n\t"
      "decl %%eax\n\t"
      "jne .LFUN_000ef110_18\n\t"
      "movw $1, 0x3c(%%esi)\n\t"
      "jmp .LFUN_000ef110_19\n\t"
      ".LFUN_000ef110_18:\n\t"
      "movw %%bx, 0x3c(%%esi)\n\t"
      ".LFUN_000ef110_19:\n\t"
      "movl 0x2c(%%edi), %%edi\n\t"
      "cmpl %%ebx, %%edi\n\t"
      "jne .LFUN_000ef110_20\n\t"
      "pushl $1\n\t"
      "pushl $0xf37\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x288088\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000ef110_20:\n\t"
      "movl 0x34(%%edi), %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "je .LFUN_000ef110_22\n\t"
      "movl $2, %%eax\n\t"
      "leal (%%ebx), %%ebx\n\t"
      ".LFUN_000ef110_21:\n\t"
      "cmpw %%ax, 0xe(%%esi)\n\t"
      "je .LFUN_000ef110_23\n\t"
      "movl 0x2c(%%esi), %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "jne .LFUN_000ef110_21\n\t"
      ".LFUN_000ef110_22:\n\t"
      "pushl $1\n\t"
      "pushl $0xf39\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x288050\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000ef110_23:\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movzbl 0x2d(%%ecx), %%eax\n\t"
      "subl %%ebx, %%eax\n\t"
      "je .LFUN_000ef110_24\n\t"
      "movw %%bx, 0x3c(%%esi)\n\t"
      "jmp .LFUN_000ef110_25\n\t"
      ".LFUN_000ef110_24:\n\t"
      "movw $1, 0x3c(%%esi)\n\t"
      ".LFUN_000ef110_25:\n\t"
      "movl 0x2c(%%edi), %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "jne .LFUN_000ef110_26\n\t"
      "pushl $1\n\t"
      "pushl $0xf42\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x288030\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000ef110_26:\n\t"
      "movl 0x34(%%esi), %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "je .LFUN_000ef110_28\n\t"
      "movl $2, %%eax\n\t"
      ".LFUN_000ef110_27:\n\t"
      "cmpw %%ax, 0xe(%%esi)\n\t"
      "je .LFUN_000ef110_29\n\t"
      "movl 0x2c(%%esi), %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "jne .LFUN_000ef110_27\n\t"
      ".LFUN_000ef110_28:\n\t"
      "pushl $1\n\t"
      "pushl $0xf44\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x288004\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000ef110_29:\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "movzbl 0x2e(%%edx), %%eax\n\t"
      "subl %%ebx, %%eax\n\t"
      "je .LFUN_000ef110_30\n\t"
      "popl %%edi\n\t"
      "movw %%bx, 0x3c(%%esi)\n\t"
      "popl %%esi\n\t"
      "decl %%eax\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000ef110_30:\n\t"
      "popl %%edi\n\t"
      "movw $1, 0x3c(%%esi)\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000ef110_31:\n\t"
      "pushl $0x287e54\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [ce0ea0] "m"(bef110_ce0ea0), [assert] "m"(bef110_assert), [exitfn] "m"(bef110_exitfn), [c8f390] "m"(bef110_c8f390)
      : "memory");
}
#else
#error "FUN_000ef110: clang naked draft required"
#endif


/* FUN_000ef3f0 (0xef3f0) — XBE naked draft (batch 117). */
#if defined(__clang__)
static void (*const bef3f0_ce0ea0)(void) = player_ui_get_edit_player_profile;
static void (*const bef3f0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const bef3f0_exitfn)(int) = system_exit;
static void (*const bef3f0_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;

__attribute__((naked, noinline))
void FUN_000ef3f0(void *widget __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[ce0ea0]\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "cmpw $3, 0xe(%%esi)\n\t"
      "movl %%eax, %%edi\n\t"
      "je .LFUN_000ef3f0_1\n\t"
      "pushl $1\n\t"
      "pushl $0xf5d\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x287fd0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000ef3f0_1:\n\t"
      "testl %%edi, %%edi\n\t"
      "je .LFUN_000ef3f0_22\n\t"
      "pushl %%ebx\n\t"
      "movl 0x34(%%esi), %%ebx\n\t"
      "testl %%ebx, %%ebx\n\t"
      "jne .LFUN_000ef3f0_2\n\t"
      "pushl $1\n\t"
      "pushl $0xf65\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x287fa8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000ef3f0_2:\n\t"
      "movl 0x34(%%ebx), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_000ef3f0_4\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".LFUN_000ef3f0_3:\n\t"
      "cmpw $2, 0xe(%%esi)\n\t"
      "je .LFUN_000ef3f0_5\n\t"
      "movl 0x2c(%%esi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LFUN_000ef3f0_3\n\t"
      ".LFUN_000ef3f0_4:\n\t"
      "pushl $1\n\t"
      "pushl $0xf67\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x287f78\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000ef3f0_5:\n\t"
      "movswl 0x3c(%%esi), %%eax\n\t"
      "cmpl $3, %%eax\n\t"
      "ja .LFUN_000ef3f0_10\n\t"
      "jmp *.LFUN_000ef3f0_jt0(,%%eax,4)\n\t"
      ".LFUN_000ef3f0_6:\n\t"
      "movb $0, 0x29(%%edi)\n\t"
      "jmp .LFUN_000ef3f0_11\n\t"
      ".LFUN_000ef3f0_7:\n\t"
      "movb $1, 0x29(%%edi)\n\t"
      "jmp .LFUN_000ef3f0_11\n\t"
      ".LFUN_000ef3f0_8:\n\t"
      "movb $2, 0x29(%%edi)\n\t"
      "jmp .LFUN_000ef3f0_11\n\t"
      ".LFUN_000ef3f0_9:\n\t"
      "movb $3, 0x29(%%edi)\n\t"
      "jmp .LFUN_000ef3f0_11\n\t"
      ".LFUN_000ef3f0_10:\n\t"
      "pushl $0x28822c\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_000ef3f0_11:\n\t"
      "movl 0x2c(%%ebx), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "popl %%ebx\n\t"
      "jne .LFUN_000ef3f0_12\n\t"
      "pushl $1\n\t"
      "pushl $0xf72\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x287f54\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000ef3f0_12:\n\t"
      "movl 0x34(%%esi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_000ef3f0_14\n\t"
      "movl $2, %%eax\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_000ef3f0_13:\n\t"
      "cmpw %%ax, 0xe(%%esi)\n\t"
      "je .LFUN_000ef3f0_15\n\t"
      "movl 0x2c(%%esi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LFUN_000ef3f0_13\n\t"
      ".LFUN_000ef3f0_14:\n\t"
      "pushl $1\n\t"
      "pushl $0xf74\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x287f24\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000ef3f0_15:\n\t"
      "movswl 0x3c(%%esi), %%eax\n\t"
      "cmpl $4, %%eax\n\t"
      "ja .LFUN_000ef3f0_21\n\t"
      "jmp *.LFUN_000ef3f0_jt1(,%%eax,4)\n\t"
      ".LFUN_000ef3f0_16:\n\t"
      "movb $0, 0x28(%%edi)\n\t"
      "popl %%edi\n\t"
      "movb $1, %%al\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000ef3f0_17:\n\t"
      "movb $1, 0x28(%%edi)\n\t"
      "popl %%edi\n\t"
      "movb $1, %%al\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000ef3f0_18:\n\t"
      "movb $2, 0x28(%%edi)\n\t"
      "popl %%edi\n\t"
      "movb $1, %%al\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000ef3f0_19:\n\t"
      "movb $3, 0x28(%%edi)\n\t"
      "popl %%edi\n\t"
      "movb $1, %%al\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000ef3f0_20:\n\t"
      "movb $4, 0x28(%%edi)\n\t"
      "popl %%edi\n\t"
      "movb $1, %%al\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000ef3f0_21:\n\t"
      "pushl $0x288204\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "popl %%edi\n\t"
      "movb $1, %%al\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000ef3f0_22:\n\t"
      "pushl $0x287e54\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "popl %%edi\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_000ef3f0_jt0:\n\t"
      ".long .LFUN_000ef3f0_6\n\t"
      ".long .LFUN_000ef3f0_7\n\t"
      ".long .LFUN_000ef3f0_8\n\t"
      ".long .LFUN_000ef3f0_9\n\t"
      ".text\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_000ef3f0_jt1:\n\t"
      ".long .LFUN_000ef3f0_16\n\t"
      ".long .LFUN_000ef3f0_17\n\t"
      ".long .LFUN_000ef3f0_18\n\t"
      ".long .LFUN_000ef3f0_19\n\t"
      ".long .LFUN_000ef3f0_20\n\t"
      ".text\n\t"
      :
      : [ce0ea0] "m"(bef3f0_ce0ea0), [assert] "m"(bef3f0_assert), [exitfn] "m"(bef3f0_exitfn), [c8f390] "m"(bef3f0_c8f390)
      : "memory");
}
#else
#error "FUN_000ef3f0: clang naked draft required"
#endif


/* playlist_profile_initialize_racing_rules (0xef5c0) — XBE naked draft (batch 109). */
#if defined(__clang__)
static void (*const bef5c0_ce0ea0)(void) = player_ui_get_edit_player_profile;
static void (*const bef5c0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const bef5c0_exitfn)(int) = system_exit;
static void (*const bef5c0_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;

__attribute__((naked, noinline))
void playlist_profile_initialize_racing_rules(void *widget __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[ce0ea0]\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "cmpw $3, 0xe(%%esi)\n\t"
      "movl %%eax, %%edi\n\t"
      "movl %%edi, -0x4(%%ebp)\n\t"
      "je .Lplaylist_profile_initialize_racing_rules_1\n\t"
      "pushl $1\n\t"
      "pushl $0xf90\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x2881c4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lplaylist_profile_initialize_racing_rules_1:\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "cmpl %%ebx, %%edi\n\t"
      "je .Lplaylist_profile_initialize_racing_rules_35\n\t"
      "movl 0x34(%%esi), %%edi\n\t"
      "cmpl %%ebx, %%edi\n\t"
      "jne .Lplaylist_profile_initialize_racing_rules_2\n\t"
      "pushl $1\n\t"
      "pushl $0xf98\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x28819c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lplaylist_profile_initialize_racing_rules_2:\n\t"
      "movl 0x34(%%edi), %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "je .Lplaylist_profile_initialize_racing_rules_4\n\t"
      ".Lplaylist_profile_initialize_racing_rules_3:\n\t"
      "cmpw $2, 0xe(%%esi)\n\t"
      "je .Lplaylist_profile_initialize_racing_rules_5\n\t"
      "movl 0x2c(%%esi), %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "jne .Lplaylist_profile_initialize_racing_rules_3\n\t"
      ".Lplaylist_profile_initialize_racing_rules_4:\n\t"
      "pushl $1\n\t"
      "pushl $0xf9a\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x28816c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lplaylist_profile_initialize_racing_rules_5:\n\t"
      "movswl 0x3c(%%esi), %%eax\n\t"
      "subl %%ebx, %%eax\n\t"
      "je .Lplaylist_profile_initialize_racing_rules_7\n\t"
      "decl %%eax\n\t"
      "je .Lplaylist_profile_initialize_racing_rules_6\n\t"
      "pushl $0x28833c\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "jmp .Lplaylist_profile_initialize_racing_rules_8\n\t"
      ".Lplaylist_profile_initialize_racing_rules_6:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movb %%bl, 0x2b(%%eax)\n\t"
      "jmp .Lplaylist_profile_initialize_racing_rules_8\n\t"
      ".Lplaylist_profile_initialize_racing_rules_7:\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movb $1, 0x2b(%%ecx)\n\t"
      ".Lplaylist_profile_initialize_racing_rules_8:\n\t"
      "movl 0x2c(%%edi), %%edi\n\t"
      "cmpl %%ebx, %%edi\n\t"
      "jne .Lplaylist_profile_initialize_racing_rules_9\n\t"
      "pushl $1\n\t"
      "pushl $0xfa3\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x288144\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lplaylist_profile_initialize_racing_rules_9:\n\t"
      "movl 0x34(%%edi), %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "je .Lplaylist_profile_initialize_racing_rules_11\n\t"
      "movl $2, %%eax\n\t"
      "nop\n\t"
      ".Lplaylist_profile_initialize_racing_rules_10:\n\t"
      "cmpw %%ax, 0xe(%%esi)\n\t"
      "je .Lplaylist_profile_initialize_racing_rules_12\n\t"
      "movl 0x2c(%%esi), %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "jne .Lplaylist_profile_initialize_racing_rules_10\n\t"
      ".Lplaylist_profile_initialize_racing_rules_11:\n\t"
      "pushl $1\n\t"
      "pushl $0xfa5\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x288114\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lplaylist_profile_initialize_racing_rules_12:\n\t"
      "movswl 0x3c(%%esi), %%eax\n\t"
      "cmpl %%ebx, %%eax\n\t"
      "jl .Lplaylist_profile_initialize_racing_rules_13\n\t"
      "cmpl $9, %%eax\n\t"
      "jg .Lplaylist_profile_initialize_racing_rules_13\n\t"
      "movb 0x3c(%%esi), %%dl\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "incb %%dl\n\t"
      "movb %%dl, 0x2a(%%eax)\n\t"
      "jmp .Lplaylist_profile_initialize_racing_rules_14\n\t"
      ".Lplaylist_profile_initialize_racing_rules_13:\n\t"
      "pushl $0x28830c\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      ".Lplaylist_profile_initialize_racing_rules_14:\n\t"
      "movl 0x2c(%%edi), %%edi\n\t"
      "cmpl %%ebx, %%edi\n\t"
      "jne .Lplaylist_profile_initialize_racing_rules_15\n\t"
      "pushl $1\n\t"
      "pushl $0xfb8\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x2880e8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lplaylist_profile_initialize_racing_rules_15:\n\t"
      "movl 0x34(%%edi), %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "je .Lplaylist_profile_initialize_racing_rules_17\n\t"
      "movl $2, %%eax\n\t"
      "leal (%%esp), %%esp\n\t"
      ".Lplaylist_profile_initialize_racing_rules_16:\n\t"
      "cmpw %%ax, 0xe(%%esi)\n\t"
      "je .Lplaylist_profile_initialize_racing_rules_18\n\t"
      "movl 0x2c(%%esi), %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "jne .Lplaylist_profile_initialize_racing_rules_16\n\t"
      ".Lplaylist_profile_initialize_racing_rules_17:\n\t"
      "pushl $1\n\t"
      "pushl $0xfba\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x2880b4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lplaylist_profile_initialize_racing_rules_18:\n\t"
      "movswl 0x3c(%%esi), %%eax\n\t"
      "subl %%ebx, %%eax\n\t"
      "je .Lplaylist_profile_initialize_racing_rules_20\n\t"
      "decl %%eax\n\t"
      "je .Lplaylist_profile_initialize_racing_rules_19\n\t"
      "pushl $0x2882d8\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "jmp .Lplaylist_profile_initialize_racing_rules_21\n\t"
      ".Lplaylist_profile_initialize_racing_rules_19:\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movb $1, 0x2c(%%ecx)\n\t"
      "jmp .Lplaylist_profile_initialize_racing_rules_21\n\t"
      ".Lplaylist_profile_initialize_racing_rules_20:\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "movb %%bl, 0x2c(%%edx)\n\t"
      ".Lplaylist_profile_initialize_racing_rules_21:\n\t"
      "movl 0x2c(%%edi), %%edi\n\t"
      "cmpl %%ebx, %%edi\n\t"
      "jne .Lplaylist_profile_initialize_racing_rules_22\n\t"
      "pushl $1\n\t"
      "pushl $0xfc3\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x288088\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lplaylist_profile_initialize_racing_rules_22:\n\t"
      "movl 0x34(%%edi), %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "je .Lplaylist_profile_initialize_racing_rules_24\n\t"
      "movl $2, %%eax\n\t"
      "jmp .Lplaylist_profile_initialize_racing_rules_23\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".Lplaylist_profile_initialize_racing_rules_23:\n\t"
      "cmpw %%ax, 0xe(%%esi)\n\t"
      "je .Lplaylist_profile_initialize_racing_rules_25\n\t"
      "movl 0x2c(%%esi), %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "jne .Lplaylist_profile_initialize_racing_rules_23\n\t"
      ".Lplaylist_profile_initialize_racing_rules_24:\n\t"
      "pushl $1\n\t"
      "pushl $0xfc5\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x288050\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lplaylist_profile_initialize_racing_rules_25:\n\t"
      "movswl 0x3c(%%esi), %%eax\n\t"
      "subl %%ebx, %%eax\n\t"
      "je .Lplaylist_profile_initialize_racing_rules_27\n\t"
      "decl %%eax\n\t"
      "je .Lplaylist_profile_initialize_racing_rules_26\n\t"
      "pushl $0x288290\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "jmp .Lplaylist_profile_initialize_racing_rules_28\n\t"
      ".Lplaylist_profile_initialize_racing_rules_26:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movb %%bl, 0x2d(%%eax)\n\t"
      "jmp .Lplaylist_profile_initialize_racing_rules_28\n\t"
      ".Lplaylist_profile_initialize_racing_rules_27:\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movb $1, 0x2d(%%ecx)\n\t"
      ".Lplaylist_profile_initialize_racing_rules_28:\n\t"
      "movl 0x2c(%%edi), %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "jne .Lplaylist_profile_initialize_racing_rules_29\n\t"
      "pushl $1\n\t"
      "pushl $0xfce\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x288030\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lplaylist_profile_initialize_racing_rules_29:\n\t"
      "movl 0x34(%%esi), %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "je .Lplaylist_profile_initialize_racing_rules_31\n\t"
      "movl $2, %%eax\n\t"
      "jmp .Lplaylist_profile_initialize_racing_rules_30\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".Lplaylist_profile_initialize_racing_rules_30:\n\t"
      "cmpw %%ax, 0xe(%%esi)\n\t"
      "je .Lplaylist_profile_initialize_racing_rules_32\n\t"
      "movl 0x2c(%%esi), %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "jne .Lplaylist_profile_initialize_racing_rules_30\n\t"
      ".Lplaylist_profile_initialize_racing_rules_31:\n\t"
      "pushl $1\n\t"
      "pushl $0xfd0\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x288004\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lplaylist_profile_initialize_racing_rules_32:\n\t"
      "movswl 0x3c(%%esi), %%eax\n\t"
      "subl %%ebx, %%eax\n\t"
      "je .Lplaylist_profile_initialize_racing_rules_34\n\t"
      "decl %%eax\n\t"
      "je .Lplaylist_profile_initialize_racing_rules_33\n\t"
      "pushl $0x288258\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lplaylist_profile_initialize_racing_rules_33:\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb %%bl, 0x2e(%%edx)\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lplaylist_profile_initialize_racing_rules_34:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb $1, 0x2e(%%eax)\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lplaylist_profile_initialize_racing_rules_35:\n\t"
      "pushl $0x287e54\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [ce0ea0] "m"(bef5c0_ce0ea0), [assert] "m"(bef5c0_assert), [exitfn] "m"(bef5c0_exitfn), [c8f390] "m"(bef5c0_c8f390)
      : "memory");
}
#else
#error "playlist_profile_initialize_racing_rules: clang naked draft required"
#endif


/* 0xef900 */
void FUN_000ef900(void *widget)
{
  int esi = 0;

  /* test esi, esi -> je 0xef91a */
  /* test (int16_t)eax, (int16_t)eax -> jl 0xef91a */
  /* cmp (int16_t)eax, 4 -> jl 0xef93a */
  display_assert((char *)0x00288368, (char *)0x002859a4, 4073, 0);
  system_exit(0);
  network_game_client_local_player_quit(0);
  set_game_connection(0);
  main_menu_switch_to_single_player();
  player_ui_remember_player1_profile(0);

  (void)esi;
}

/* 0xef970 */
void FUN_000ef970(void *widget)
{
  int eax = 0;
  int edx = 0;
  int edi = 0;

  tag_get(0x44654c61, 0);
  /* relift: cmp word ptr [eax], 0 -> jne 0xef996 */
  /* relift: cmp dword ptr [eax + 0x3e0], 3 -> jge 0xef9b6 */
  display_assert((char *)0x00286500, (char *)0x002859a4, 4111, 0);
  system_exit(0);
  tag_get(0x44654c61, 0);
  /* relift: cmp word ptr [edi], 2 -> je 0xef9f2 */
  display_assert((char *)0x00286070, (char *)0x002859a4, 4114, 0);
  system_exit(0);
  display_assert((char *)0x00286034, (char *)0x002859a4, 4115, 0);
  system_exit(0);
  /* test (int16_t)eax, (int16_t)eax -> jl 0xefa33 */
  /* cmp eax, edx -> jl 0xefa53 */
  display_assert((char *)0x00285fe0, (char *)0x002859a4, 4124, 0);
  system_exit(0);
  /* mem[0x0031e494] = eax */
  ui_play_audio_feedback_sound(0);

  (void)eax;
  (void)edx;
  (void)edi;
}

/* FUN_000efa80 (0xefa80) — XBE naked draft (batch 114). */
#if defined(__clang__)
static void *(*const befa80_tag)(int, int) = tag_get;
static void (*const befa80_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const befa80_exitfn)(int) = system_exit;
static void (*const befa80_ce4500)(int16_t error_handle, int16_t local_player_index, char a3, char a4) = display_error_deferred;
static void (*const befa80_ce5ab0)(int16_t sound_selector) = ui_play_audio_feedback_sound;

__attribute__((naked, noinline))
void FUN_000efa80(void *widget __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "movl (%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x44654c61\n\t"
      "xorb %%bl, %%bl\n\t"
      "call *%[tag]\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $0, (%%eax)\n\t"
      "jne .LFUN_000efa80_1\n\t"
      "cmpl $3, 0x3e0(%%eax)\n\t"
      "jge .LFUN_000efa80_2\n\t"
      ".LFUN_000efa80_1:\n\t"
      "pushl $1\n\t"
      "pushl $0x103d\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x288430\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000efa80_2:\n\t"
      "movl 0x34(%%esi), %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x44654c61\n\t"
      "call *%[tag]\n\t"
      "movl %%eax, %%edi\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $2, (%%edi)\n\t"
      "je .LFUN_000efa80_3\n\t"
      "pushl $1\n\t"
      "pushl $0x1040\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x2883e8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000efa80_3:\n\t"
      "cmpl $3, 0x3e0(%%edi)\n\t"
      "popl %%edi\n\t"
      "je .LFUN_000efa80_4\n\t"
      "pushl $1\n\t"
      "pushl $0x1041\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x2883ac\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000efa80_4:\n\t"
      "movl 0x34(%%esi), %%esi\n\t"
      "movw 0x3c(%%esi), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "jl .LFUN_000efa80_5\n\t"
      "movzwl 0x44(%%esi), %%edx\n\t"
      "movswl %%ax, %%eax\n\t"
      "cmpl %%edx, %%eax\n\t"
      "jl .LFUN_000efa80_6\n\t"
      ".LFUN_000efa80_5:\n\t"
      "pushl $1\n\t"
      "pushl $0x1049\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x285fe0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000efa80_6:\n\t"
      "movswl 0x3c(%%esi), %%ecx\n\t"
      "movl 0x40(%%esi), %%edx\n\t"
      "movl (%%edx,%%ecx,4), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "movl %%eax, 0x31e494\n\t"
      "je .LFUN_000efa80_8\n\t"
      "testl $0x40000000, %%eax\n\t"
      "je .LFUN_000efa80_7\n\t"
      "pushl $0\n\t"
      "pushl $1\n\t"
      "pushl $-1\n\t"
      "pushl $0x1a\n\t"
      "call *%[ce4500]\n\t"
      "pushl $4\n\t"
      "call *%[ce5ab0]\n\t"
      "addl $0x14, %%esp\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000efa80_7:\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000efa80_8:\n\t"
      "pushl $4\n\t"
      "call *%[ce5ab0]\n\t"
      "addl $4, %%esp\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [tag] "m"(befa80_tag), [assert] "m"(befa80_assert), [exitfn] "m"(befa80_exitfn), [ce4500] "m"(befa80_ce4500), [ce5ab0] "m"(befa80_ce5ab0)
      : "memory");
}
#else
#error "FUN_000efa80: clang naked draft required"
#endif


/* FUN_000efc60 (0xefc60) — XBE naked draft (batch 122). */
#if defined(__clang__)
static void (*const befc60_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const befc60_exitfn)(int) = system_exit;
static void (*const befc60_c1c29c0)(void) = saved_game_file_get_useable_untitled_profile_name;
static void (*const befc60_c1c1e20)(void) = FUN_001c1e20;
static void (*const befc60_ce1500)(void) = player_ui_begin_editing_profile;
static void (*const befc60_ce0ec0)(void) = player_ui_get_edit_playlist_profile;
static game_variant_t * (*const befc60_caa190)(game_variant_t *out) = game_engine_slayer_default;
static void * (*const befc60_c8e0b0)(void *destination, void *source, size_t size) = csmemcpy;
static wchar_t * (*const befc60_c19dc90)(wchar_t *dest, wchar_t *src, size_t count) = ustrncpy;
static bool (*const befc60_cf5500)(wchar_t *text_buffer, unsigned short buffer_size, short caption_index) = virtual_keyboard_set_validation;
static void (*const befc60_c1c4da0)(void) = FUN_001c4da0;
static void (*const befc60_c1c2e00)(void) = saved_game_file_remember_last_used_multiplayer_variant_directory;
static void (*const befc60_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;
static void (*const befc60_ce1760)(void) = player_ui_end_editing_profile;
static void (*const befc60_ce4500)(int16_t error_handle, int16_t local_player_index, char a3, char a4) = display_error_deferred;
static void (*const befc60_ce5ab0)(int16_t sound_selector) = ui_play_audio_feedback_sound;

__attribute__((naked, noinline))
void FUN_000efc60(void *widget __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x2d4, %%esp\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "movw 0x2(%%eax), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "jl .LFUN_000efc60_1\n\t"
      "cmpw $4, %%ax\n\t"
      "jl .LFUN_000efc60_2\n\t"
      ".LFUN_000efc60_1:\n\t"
      "pushl $1\n\t"
      "pushl $0x10b0\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x2885a8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000efc60_2:\n\t"
      "leal -0x16c(%%ebp), %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1c29c0]\n\t"
      "addl $4, %%esp\n\t"
      "cmpw $0, -0x16c(%%ebp)\n\t"
      "je .LFUN_000efc60_6\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x8(%%eax), %%cx\n\t"
      "leal -0x16c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1c1e20]\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "movl %%eax, 0xc(%%ebp)\n\t"
      "je .LFUN_000efc60_5\n\t"
      "pushl %%eax\n\t"
      "call *%[ce1500]\n\t"
      "addl $4, %%esp\n\t"
      "call *%[ce0ec0]\n\t"
      "movl %%eax, %%ebx\n\t"
      "testl %%ebx, %%ebx\n\t"
      "je .LFUN_000efc60_4\n\t"
      "pushl %%esi\n\t"
      "leal -0x1d4(%%ebp), %%edx\n\t"
      "pushl %%edi\n\t"
      "pushl %%edx\n\t"
      "call *%[caa190]\n\t"
      "movl %%eax, %%esi\n\t"
      "pushl $0x68\n\t"
      "leal -0x6c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl $0x1a, %%ecx\n\t"
      "leal -0x6c(%%ebp), %%edi\n\t"
      "pushl %%ebx\n\t"
      "rep movsl\n\t"
      "call *%[c8e0b0]\n\t"
      "pushl $0xb\n\t"
      "leal -0x16c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "xorl %%esi, %%esi\n\t"
      "pushl %%ebx\n\t"
      "movw %%si, 0x64(%%ebx)\n\t"
      "call *%[c19dc90]\n\t"
      "pushl $9\n\t"
      "pushl $0x18\n\t"
      "pushl %%ebx\n\t"
      "movw %%si, 0x16(%%ebx)\n\t"
      "call *%[cf5500]\n\t"
      "addl $0x28, %%esp\n\t"
      "movb %%al, %%bl\n\t"
      "cmpb $1, %%bl\n\t"
      "popl %%edi\n\t"
      "movb %%bl, -0x1(%%ebp)\n\t"
      "popl %%esi\n\t"
      "jne .LFUN_000efc60_7\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "leal -0x2d4(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c1c4da0]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000efc60_3\n\t"
      "leal -0x2d4(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1c2e00]\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_000efc60_3:\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000efc60_4:\n\t"
      "pushl $0x288574\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "call *%[ce1760]\n\t"
      "jmp .LFUN_000efc60_8\n\t"
      ".LFUN_000efc60_5:\n\t"
      "pushl $0x28853c\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "jmp .LFUN_000efc60_8\n\t"
      ".LFUN_000efc60_6:\n\t"
      "pushl $0x288514\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "jmp .LFUN_000efc60_8\n\t"
      ".LFUN_000efc60_7:\n\t"
      "testb %%bl, %%bl\n\t"
      "jne .LFUN_000efc60_9\n\t"
      ".LFUN_000efc60_8:\n\t"
      "pushl $0\n\t"
      "pushl $1\n\t"
      "pushl $-1\n\t"
      "pushl $0x26\n\t"
      "call *%[ce4500]\n\t"
      "pushl $4\n\t"
      "call *%[ce5ab0]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000efc60_9:\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(befc60_assert), [exitfn] "m"(befc60_exitfn), [c1c29c0] "m"(befc60_c1c29c0), [c1c1e20] "m"(befc60_c1c1e20), [ce1500] "m"(befc60_ce1500), [ce0ec0] "m"(befc60_ce0ec0), [caa190] "m"(befc60_caa190), [c8e0b0] "m"(befc60_c8e0b0), [c19dc90] "m"(befc60_c19dc90), [cf5500] "m"(befc60_cf5500), [c1c4da0] "m"(befc60_c1c4da0), [c1c2e00] "m"(befc60_c1c2e00), [c8f390] "m"(befc60_c8f390), [ce1760] "m"(befc60_ce1760), [ce4500] "m"(befc60_ce4500), [ce5ab0] "m"(befc60_ce5ab0)
      : "memory");
}
#else
#error "FUN_000efc60: clang naked draft required"
#endif


/* 0xefde0 */
void FUN_000efde0(void *widget)
{
  int eax = 0;
  int ebx = 0;
  int esi = 0;
  int ebp = 0;

  /* cmp (int16_t)esi, -1 -> jne 0xefdfc */
  saved_game_file_get_useable_untitled_profile_name();
  /* relift: cmp word ptr [ebp - 0x100], 0 -> je 0xefeb0 */
  FUN_001c1720();
  /* cmp eax, -1 -> je 0xefe9f */
  player_ui_begin_editing_profile();
  player_ui_get_edit_player_profile();
  /* test esi, esi -> je 0xefe89 */
  ustrncpy((wchar_t *)(uintptr_t)esi, (wchar_t *)(uintptr_t)eax, 11);
  virtual_keyboard_set_validation((wchar_t *)(uintptr_t)esi, 24, 0);
  /* test (char)ebx, (char)ebx -> jne 0xefe81 */
  display_error_deferred(37, 0, 0, 0);
  ui_play_audio_feedback_sound(0);
  error(0, (char *)0x0028860c);
  player_ui_end_editing_profile();
  error(0, (char *)0x002885e4);
  error(0, (char *)0x00288514);

  (void)eax;
  (void)ebx;
  (void)esi;
  (void)ebp;
}

/* 0xefed0 */
void FUN_000efed0(void *widget)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int edi = 0;
  int ebp = 0;

  network_game_client_get();
  /* test ebx, ebx -> je 0xeff58 */
  network_game_client_get_machine_index((void *)(uintptr_t)ebx);
  FUN_00124c40((void *)(uintptr_t)ebx);
  network_player_is_valid((void *)(uintptr_t)eax);
  /* test (char)eax, (char)eax -> je 0xeff28 */
  /* relift: cmp (int16_t)ecx, word ptr [ebp - 4] -> jne 0xeff28 */
  /* relift: cmp (int16_t)edx, word ptr [eax + 2] -> je 0xeff3a */
  /* cmp edi, 0x10 -> jl 0xeff00 */
  FUN_00125b90((void *)(uintptr_t)ebx, 0);
  /* test (char)eax, (char)eax -> jne 0xeff58 */
  error(0, (char *)0x00288638);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)edi;
  (void)ebp;
}

/* FUN_000eff70 (0xeff70) — XBE naked draft (batch 123). */
#if defined(__clang__)
static void * (*const beff70_c12a240)(void) = network_game_client_get;
static void * (*const beff70_c1257a0)(void *client) = network_game_client_get_machine_index;
static uint16_t (*const beff70_c124c40)(void *client) = FUN_00124c40;
static bool (*const beff70_c12ac80)(void *client) = network_player_is_valid;
static char (*const beff70_c125b90)(void *client, short request_type) = FUN_00125b90;
static void (*const beff70_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;

__attribute__((naked, noinline))
void FUN_000eff70(void *widget __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c12a240]\n\t"
      "movl %%eax, %%ebx\n\t"
      "testl %%ebx, %%ebx\n\t"
      "je .LFUN_000eff70_4\n\t"
      "pushl %%ebx\n\t"
      "call *%[c1257a0]\n\t"
      "pushl %%ebx\n\t"
      "movl %%eax, %%esi\n\t"
      "call *%[c124c40]\n\t"
      "addl $8, %%esp\n\t"
      "xorl %%edi, %%edi\n\t"
      "addl $0x242, %%esi\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "movl %%edi, %%edi\n\t"
      ".LFUN_000eff70_1:\n\t"
      "leal -0x1c(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c12ac80]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000eff70_2\n\t"
      "movsbw (%%esi), %%cx\n\t"
      "cmpw -0x4(%%ebp), %%cx\n\t"
      "jne .LFUN_000eff70_2\n\t"
      "movsbw 0x1(%%esi), %%dx\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "cmpw 0x2(%%eax), %%dx\n\t"
      "je .LFUN_000eff70_3\n\t"
      ".LFUN_000eff70_2:\n\t"
      "incl %%edi\n\t"
      "addl $0x20, %%esi\n\t"
      "cmpl $0x10, %%edi\n\t"
      "jl .LFUN_000eff70_1\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000eff70_3:\n\t"
      "pushl $0\n\t"
      "pushl %%ebx\n\t"
      "call *%[c125b90]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_000eff70_4\n\t"
      "pushl $0x288638\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_000eff70_4:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c12a240] "m"(beff70_c12a240), [c1257a0] "m"(beff70_c1257a0), [c124c40] "m"(beff70_c124c40), [c12ac80] "m"(beff70_c12ac80), [c125b90] "m"(beff70_c125b90), [c8f390] "m"(beff70_c8f390)
      : "memory");
}
#else
#error "FUN_000eff70: clang naked draft required"
#endif


/* 0xf0070 */
void FUN_000f0070(void *widget)
{
  int eax = 0;

  xbox_demos_available();
  /* test (char)eax, (char)eax -> jne 0xf0087 */
  main_run_demos();
  player_ui_reset_single_player_local_player_controllers();

  (void)eax;
}

/* 0xf00b0 */
void FUN_000f00b0(void *widget)
{
  int esi = 0;

  /* test esi, esi -> jne 0xf00db */
  display_assert((char *)0x00288670, (char *)0x002859a4, 4537, 0);
  system_exit(0);
  player_ui_set_single_player_local_player_controller();

  (void)esi;
}

/* 0xf0100 */
void FUN_000f0100(void *widget)
{
  int esi = 0;

  /* test esi, esi -> jne 0xf012b */
  display_assert((char *)0x00288670, (char *)0x002859a4, 4551, 0);
  system_exit(0);
  player_ui_get_single_player_local_player_controller(0);
  /* cmp (int16_t)esi, (int16_t)eax -> jne 0xf0159 */
  ui_widget_display_error(18, 0, 0, 0);
  player_ui_set_single_player_local_player_controller();

  (void)esi;
}

/* 0xf0170 */
void FUN_000f0170(void *widget)
{
  int ebx = 0;

  transport_network_available();
  display_assert((char *)0x00286184, (char *)0x002859a4, 4575, 0);
  system_exit(0);
  /* test (char)ebx, (char)ebx -> jne 0xf01bc */
  ui_widget_display_error(0, 0, 0, 0);

  (void)ebx;
}

/* 0xf01d0 */
void player_profile_end_editing(void *widget)
{
  int eax = 0;
  int ecx = 0;
  int esi = 0;

  /* relift: cmp word ptr [esi + 0xe], 3 -> je 0xf0201 */
  display_assert((char *)0x002886c8, (char *)0x002859a4, 4593, 0);
  system_exit(0);
  /* relift: cmp word ptr [esi + 0x44], 0 -> jne 0xf0238 */
  network_game_client_get();
  /* test eax, eax -> je 0xf0247 */
  network_game_client_get_state((void *)(uintptr_t)eax, (void *)(uintptr_t)ecx);
  /* test (int16_t)eax, (int16_t)eax -> jne 0xf0247 */
  FUN_000E9D40();
  error(0, (char *)0x00288680);

  (void)eax;
  (void)ecx;
  (void)esi;
}

/* player_profile_save_changes (0xf0250) — XBE naked draft (batch 120). */
#if defined(__clang__)
static void * (*const bf0250_c12a240)(void) = network_game_client_get;
static int16_t (*const bf0250_c124a30)(void *server, void *out_param) = network_game_client_get_state;
static void * (*const bf0250_c1257a0)(void *client) = network_game_client_get_machine_index;
static short (*const bf0250_c12a690)(void) = network_game_client_get_local_machine_index;
static bool (*const bf0250_c12ac80)(void *client) = network_player_is_valid;
static void (*const bf0250_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const bf0250_exitfn)(int) = system_exit;
static char (*const bf0250_c1263a0)(void *client, void *record) = network_game_client_request_remove_player;
static void (*const bf0250_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;
static void (*const bf0250_ce08e0)(void) = player_ui_clear_multiplayer_autojoin_for_local_player;
static void * (*const bf0250_c12a1d0)(void) = network_game_server_get;
static bool (*const bf0250_c12a160)(void) = network_game_accept_remote_connections;
static void (*const bf0250_c12d690)(void *server, char flag) = network_game_server_pause_countdown;
static void (*const bf0250_ce0930)(void) = player_ui_autojoin_players_to_next_multiplayer_game;
static void (*const bf0250_c12a2a0)(void) = dispose_global_network_game_server;
static void (*const bf0250_c12a1e0)(void) = dispose_global_network_game_client;

__attribute__((naked, noinline))
void player_profile_save_changes(void *widget __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x10, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movb $1, %%bl\n\t"
      "call *%[c12a240]\n\t"
      "movl %%eax, %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%esi, -0x10(%%ebp)\n\t"
      "je .Lplayer_profile_save_changes_10\n\t"
      "leal -0x4(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[c124a30]\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $2, %%ax\n\t"
      "jne .Lplayer_profile_save_changes_9\n\t"
      "pushl %%edi\n\t"
      "pushl %%esi\n\t"
      "call *%[c1257a0]\n\t"
      "addl $4, %%esp\n\t"
      "movl %%eax, %%esi\n\t"
      "xorl %%edi, %%edi\n\t"
      "call *%[c12a690]\n\t"
      "movl %%edi, -0x8(%%ebp)\n\t"
      "movl %%eax, %%ebx\n\t"
      "cmpw $-1, %%bx\n\t"
      "je .Lplayer_profile_save_changes_11\n\t"
      "addl $0x226, %%esi\n\t"
      "movl $0x10, -0xc(%%ebp)\n\t"
      ".Lplayer_profile_save_changes_1:\n\t"
      "pushl %%esi\n\t"
      "call *%[c12ac80]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lplayer_profile_save_changes_3\n\t"
      "movsbw 0x1c(%%esi), %%cx\n\t"
      "cmpw %%bx, %%cx\n\t"
      "jne .Lplayer_profile_save_changes_3\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "incl %%edx\n\t"
      "movl %%edx, -0x8(%%ebp)\n\t"
      "movsbw 0x1d(%%esi), %%dx\n\t"
      "cmpw 0x2(%%eax), %%dx\n\t"
      "jne .Lplayer_profile_save_changes_3\n\t"
      "testl %%edi, %%edi\n\t"
      "je .Lplayer_profile_save_changes_2\n\t"
      "pushl $1\n\t"
      "pushl $0x1226\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x288768\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lplayer_profile_save_changes_2:\n\t"
      "movl %%esi, %%edi\n\t"
      ".Lplayer_profile_save_changes_3:\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "addl $0x20, %%esi\n\t"
      "decl %%eax\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "jne .Lplayer_profile_save_changes_1\n\t"
      "movl -0x8(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jle .Lplayer_profile_save_changes_11\n\t"
      "testl %%edi, %%edi\n\t"
      "je .Lplayer_profile_save_changes_5\n\t"
      "movl -0x10(%%ebp), %%ecx\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1263a0]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lplayer_profile_save_changes_4\n\t"
      "pushl $0x288744\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      ".Lplayer_profile_save_changes_4:\n\t"
      "movsbw 0x1d(%%edi), %%dx\n\t"
      "pushl %%edx\n\t"
      "call *%[ce08e0]\n\t"
      "addl $4, %%esp\n\t"
      ".Lplayer_profile_save_changes_5:\n\t"
      "cmpl $1, %%esi\n\t"
      "jne .Lplayer_profile_save_changes_8\n\t"
      "call *%[c12a1d0]\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lplayer_profile_save_changes_6\n\t"
      "call *%[c12a160]\n\t"
      "cmpb $1, %%al\n\t"
      "jne .Lplayer_profile_save_changes_6\n\t"
      "call *%[c12a1d0]\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lplayer_profile_save_changes_7\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "call *%[c12d690]\n\t"
      "addl $8, %%esp\n\t"
      "movb $1, %%bl\n\t"
      "call *%[ce0930]\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lplayer_profile_save_changes_6:\n\t"
      "call *%[c12a2a0]\n\t"
      "call *%[c12a1e0]\n\t"
      ".Lplayer_profile_save_changes_7:\n\t"
      "movb $1, %%bl\n\t"
      "call *%[ce0930]\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lplayer_profile_save_changes_8:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lplayer_profile_save_changes_9:\n\t"
      "pushl $0x2886f0\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      ".Lplayer_profile_save_changes_10:\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lplayer_profile_save_changes_11:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c12a240] "m"(bf0250_c12a240), [c124a30] "m"(bf0250_c124a30), [c1257a0] "m"(bf0250_c1257a0), [c12a690] "m"(bf0250_c12a690), [c12ac80] "m"(bf0250_c12ac80), [assert] "m"(bf0250_assert), [exitfn] "m"(bf0250_exitfn), [c1263a0] "m"(bf0250_c1263a0), [c8f390] "m"(bf0250_c8f390), [ce08e0] "m"(bf0250_ce08e0), [c12a1d0] "m"(bf0250_c12a1d0), [c12a160] "m"(bf0250_c12a160), [c12d690] "m"(bf0250_c12d690), [ce0930] "m"(bf0250_ce0930), [c12a2a0] "m"(bf0250_c12a2a0), [c12a1e0] "m"(bf0250_c12a1e0)
      : "memory");
}
#else
#error "player_profile_save_changes: clang naked draft required"
#endif


/* 0xf03d0 */
void FUN_000F03D0(void *widget)
{
  int eax = 0;

  player_ui_get_edit_player_profile();
  /* test eax, eax -> jne 0xf0413 */
  player_ui_get_edit_playlist_profile();
  /* test eax, eax -> jne 0xf0413 */
  ui_widget_get_last_child((void *)(uintptr_t)eax);
  error(0, (char *)0x0028878c);
  FUN_000e0570();

  (void)eax;
}

/* 0xf0430 */
void player_profile_initialize_advanced_controller_settings(void *widget)
{
  int ecx = 0;
  int esi = 0;

  /* test esi, esi -> jne 0xf0461 */
  display_assert((char *)0x00286184, (char *)0x002859a4, 4741, 0);
  system_exit(0);
  saved_game_file_get_useable_untitled_profile_name();
  ustrncpy((wchar_t *)0x0046ccd0, (wchar_t *)(uintptr_t)ecx, 11);
  virtual_keyboard_set_validation((wchar_t *)0x0046ccd0, 24, 0);
  error(0, (char *)0x002887d0);

  (void)ecx;
  (void)esi;
}

/* FUN_000f04c0 (0xf04c0) — XBE naked draft (batch 126). */
#if defined(__clang__)
static char (*const bf04c0_cf5650)(void) = FUN_000f5650;
static void (*const bf04c0_ce0740)(void) = player_ui_set_single_player_local_player_controller;
static void (*const bf04c0_c1c1720)(void) = FUN_001c1720;
static void (*const bf04c0_c1c29c0)(void) = saved_game_file_get_useable_untitled_profile_name;
static wchar_t * (*const bf04c0_c19dc90)(wchar_t *dest, wchar_t *src, size_t count) = ustrncpy;
static void (*const bf04c0_c1c18f0)(void) = player_profile_new;
static void (*const bf04c0_ce1490)(void) = player_ui_set_active_player_profile;
static void (*const bf04c0_cfffa0)(const char *name) = main_set_map_name;
static void (*const bf04c0_c100000)(void) = main_defer_map_map_change;
static void (*const bf04c0_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;
static void (*const bf04c0_c100620)(void) = main_goto_main_menu;
static void (*const bf04c0_ce4500)(int16_t error_handle, int16_t local_player_index, char a3, char a4) = display_error_deferred;
static void (*const bf04c0_ce5ab0)(int16_t sound_selector) = ui_play_audio_feedback_sound;

__attribute__((naked, noinline))
void FUN_000f04c0(void *widget __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x130, %%esp\n\t"
      "pushl %%ebx\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "cmpw $-1, 0x31e4fc\n\t"
      "je .LFUN_000f04c0_7\n\t"
      "pushl %%esi\n\t"
      "call *%[cf5650]\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000f04c0_6\n\t"
      "cmpw %%bx, 0x46ccd0\n\t"
      "je .LFUN_000f04c0_5\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x31e4fc, %%ax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "call *%[ce0740]\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x31e4fc, %%cx\n\t"
      "pushl $0x46ccd0\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1c1720]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpl $-1, %%esi\n\t"
      "jne .LFUN_000f04c0_1\n\t"
      "leal -0x130(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c1c29c0]\n\t"
      "pushl $0xb\n\t"
      "leal -0x130(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x46ccd0\n\t"
      "call *%[c19dc90]\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x31e4fc, %%cx\n\t"
      "pushl $0x46ccd0\n\t"
      "movw %%bx, 0x46cce6\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1c1720]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $0x18, %%esp\n\t"
      "cmpl $-1, %%esi\n\t"
      "je .LFUN_000f04c0_4\n\t"
      ".LFUN_000f04c0_1:\n\t"
      "leal -0x30(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%esi\n\t"
      "call *%[c1c18f0]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000f04c0_2\n\t"
      "leal -0x30(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%ebx\n\t"
      "call *%[ce1490]\n\t"
      "movl 0x31e498, %%ecx\n\t"
      "addl $0xc, %%esp\n\t"
      "pushl %%ecx\n\t"
      "movb $1, %%bl\n\t"
      "call *%[cfffa0]\n\t"
      "addl $4, %%esp\n\t"
      "call *%[c100000]\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "movw $0xffff, 0x31e4fc\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000f04c0_2:\n\t"
      "pushl $0x28886c\n\t"
      ".LFUN_000f04c0_3:\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "call *%[c100620]\n\t"
      "pushl %%ebx\n\t"
      "pushl $1\n\t"
      "pushl $-1\n\t"
      "pushl $0x25\n\t"
      "call *%[ce4500]\n\t"
      "pushl $4\n\t"
      "call *%[ce5ab0]\n\t"
      "addl $0x14, %%esp\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "movw $0xffff, 0x31e4fc\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000f04c0_4:\n\t"
      "pushl $0x288848\n\t"
      "jmp .LFUN_000f04c0_3\n\t"
      ".LFUN_000f04c0_5:\n\t"
      "pushl $0x288818\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "pushl $4\n\t"
      "call *%[ce5ab0]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_000f04c0_6:\n\t"
      "movw $0xffff, 0x31e4fc\n\t"
      "popl %%esi\n\t"
      ".LFUN_000f04c0_7:\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [cf5650] "m"(bf04c0_cf5650), [ce0740] "m"(bf04c0_ce0740), [c1c1720] "m"(bf04c0_c1c1720), [c1c29c0] "m"(bf04c0_c1c29c0), [c19dc90] "m"(bf04c0_c19dc90), [c1c18f0] "m"(bf04c0_c1c18f0), [ce1490] "m"(bf04c0_ce1490), [cfffa0] "m"(bf04c0_cfffa0), [c100000] "m"(bf04c0_c100000), [c8f390] "m"(bf04c0_c8f390), [c100620] "m"(bf04c0_c100620), [ce4500] "m"(bf04c0_ce4500), [ce5ab0] "m"(bf04c0_ce5ab0)
      : "memory");
}
#else
#error "FUN_000f04c0: clang naked draft required"
#endif


/* 0xf0620 */
void FUN_000f0620(void *widget)
{
  ui_widgets_pop_stack(0);
}

/* 0xf0640 */
void FUN_000f0640(void *widget)
{
  int eax = 0;
  int esi = 0;
  int edi = 0;

  display_assert((char *)0x002888c4, (char *)0x002859a4, 4860, 0);
  system_exit(0);
  /* relift: cmp byte ptr [0x46ce3b], 1 -> jne 0xf06da */
  main_get_map_name();
  crt_stricmp((char *)0x0046cd38, (char *)(uintptr_t)eax);
  /* test eax, eax -> jne 0xf06da */
  widget_instance_get_nth_child((void *)(uintptr_t)esi, 0);
  /* test edi, edi -> jne 0xf06c6 */
  display_assert((char *)0x0028889c, (char *)0x002859a4, 4865, 0);
  system_exit(0);
  widget_instance_get_nth_child((void *)(uintptr_t)esi, 0);
  /* test edi, edi -> jne 0xf070b */
  display_assert((char *)0x0028889c, (char *)0x002859a4, 4871, 0);
  system_exit(0);
  ui_widget_get_attract_mode_flag();
  /* test (char)eax, (char)eax -> je 0xf072e */
  ui_widget_stop_attract_mode();

  (void)eax;
  (void)esi;
  (void)edi;
}

/* 0xf0740 */
void FUN_000f0740(void *widget)
{
  int ecx = 0;
  int ebp = 0;

  FUN_001c0d50();
  /* relift: cmp word ptr [ebp - 4], 0 -> jle 0xf076e */
  player_profile_initialize_advanced_controller_settings((void *)(uintptr_t)ecx);

  (void)ecx;
  (void)ebp;
}

/* FUN_000f0790 (0xf0790) — XBE naked draft (batch 113). */
#if defined(__clang__)
static void *(*const bf0790_memset)(void *, int, unsigned int) = csmemset;
static char (*const bf0790_ce98c0)(void *widget) = FUN_000e98c0;
static void (*const bf0790_ce09e0)(void) = player_ui_get_active_player_profile_index;
static int (*const bf0790_c1bf920)(char *header, int16_t *flags, int param_3) = game_state_test_persistent_storage;
static void (*const bf0790_ce0980)(void) = player_ui_get_active_player_profile;
static void (*const bf0790_c1c0f70)(void *profile, short *out_level, short *out_difficulty) = player_profile_save_last_level_played;
static void *(*const bf0790_tag)(int, int) = tag_get;
static void (*const bf0790_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const bf0790_exitfn)(int) = system_exit;
static void (*const bf0790_ce0a10)(void) = player_ui_get_last_single_player_level_played;
static int (*const bf0790_c1dd801)(const char *a, const char *b) = crt_stricmp;
static void (*const bf0790_ce4500)(int16_t error_handle, int16_t local_player_index, char a3, char a4) = display_error_deferred;

__attribute__((naked, noinline))
void FUN_000f0790(void *widget __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x38, %%esp\n\t"
      "cmpw $2, 0x31fa94\n\t"
      "jl .LFUN_000f0790_1\n\t"
      "pushl $0x106\n\t"
      "pushl $0\n\t"
      "pushl $0x46cd38\n\t"
      "call *%[memset]\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[ce98c0]\n\t"
      "addl $0x18, %%esp\n\t"
      "movb $1, %%al\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000f0790_1:\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl $0\n\t"
      "call *%[ce09e0]\n\t"
      "pushl $0x50\n\t"
      "pushl $0\n\t"
      "pushl $0x46cce8\n\t"
      "movl %%eax, %%esi\n\t"
      "call *%[memset]\n\t"
      "movl 0x31e4c0, %%eax\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpl %%eax, %%esi\n\t"
      "je .LFUN_000f0790_2\n\t"
      "pushl $0x106\n\t"
      "pushl $0\n\t"
      "pushl $0x46cd38\n\t"
      "call *%[memset]\n\t"
      "pushl $0x46ce3c\n\t"
      "pushl $0x46ce38\n\t"
      "pushl $0x46cd38\n\t"
      "call *%[c1bf920]\n\t"
      "addl $0x18, %%esp\n\t"
      "movb %%al, 0x46ce3b\n\t"
      "movl %%esi, 0x31e4c0\n\t"
      ".LFUN_000f0790_2:\n\t"
      "leal -0x38(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0\n\t"
      "call *%[ce0980]\n\t"
      "leal -0x8(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x4(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x38(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1c0f70]\n\t"
      "movw -0x4(%%ebp), %%si\n\t"
      "addl $0x14, %%esp\n\t"
      "xorl %%eax, %%eax\n\t"
      "jmp .LFUN_000f0790_3\n\t"
      "leal (%%ebx), %%ebx\n\t"
      ".LFUN_000f0790_3:\n\t"
      "movl 0x31e498(,%%eax,4), %%ecx\n\t"
      "movl %%ecx, 0x46cce8(,%%eax,8)\n\t"
      "movb -0x1c(%%ebp,%%eax,1), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "jne .LFUN_000f0790_4\n\t"
      "movswl %%si, %%edx\n\t"
      "incl %%edx\n\t"
      "cmpl %%edx, %%eax\n\t"
      "je .LFUN_000f0790_4\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_000f0790_5\n\t"
      ".LFUN_000f0790_4:\n\t"
      "movsbl %%cl, %%ecx\n\t"
      "movl %%ecx, %%edx\n\t"
      "shrl $1, %%edx\n\t"
      "andb $1, %%dl\n\t"
      "movb %%dl, 0x46cced(,%%eax,8)\n\t"
      "movl %%ecx, %%edx\n\t"
      "shrl $2, %%edx\n\t"
      "andb $1, %%dl\n\t"
      "shrl $3, %%ecx\n\t"
      "andb $1, %%cl\n\t"
      "movb $1, 0x46ccec(,%%eax,8)\n\t"
      "movb %%dl, 0x46ccee(,%%eax,8)\n\t"
      "movb %%cl, 0x46ccef(,%%eax,8)\n\t"
      ".LFUN_000f0790_5:\n\t"
      "incl %%eax\n\t"
      "cmpl $0xa, %%eax\n\t"
      "jl .LFUN_000f0790_3\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "movl (%%ebx), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x44654c61\n\t"
      "call *%[tag]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $2, (%%esi)\n\t"
      "je .LFUN_000f0790_6\n\t"
      "pushl $1\n\t"
      "pushl $0x25b\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x285a18\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000f0790_6:\n\t"
      "cmpl $3, 0x3e0(%%esi)\n\t"
      "je .LFUN_000f0790_7\n\t"
      "pushl $1\n\t"
      "pushl $0x25c\n\t"
      "pushl $0x2859a4\n\t"
      "pushl $0x2859e4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000f0790_7:\n\t"
      "pushl $0\n\t"
      "movl $0x46cce8, 0x40(%%ebx)\n\t"
      "movw $0xa, 0x44(%%ebx)\n\t"
      "call *%[ce0a10]\n\t"
      "addl $4, %%esp\n\t"
      "testw %%ax, %%ax\n\t"
      "jge .LFUN_000f0790_8\n\t"
      "xorl %%eax, %%eax\n\t"
      "jmp .LFUN_000f0790_10\n\t"
      ".LFUN_000f0790_8:\n\t"
      "pushl $0\n\t"
      "call *%[ce0a10]\n\t"
      "addl $4, %%esp\n\t"
      "cmpw $9, %%ax\n\t"
      "jle .LFUN_000f0790_9\n\t"
      "movl $9, %%eax\n\t"
      "jmp .LFUN_000f0790_10\n\t"
      ".LFUN_000f0790_9:\n\t"
      "pushl $0\n\t"
      "call *%[ce0a10]\n\t"
      "addl $4, %%esp\n\t"
      "movswl %%ax, %%eax\n\t"
      ".LFUN_000f0790_10:\n\t"
      "movw %%ax, 0x3c(%%ebx)\n\t"
      "cmpb $1, 0x46ce3b\n\t"
      "jne .LFUN_000f0790_15\n\t"
      "movb $0, 0x46ce37\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "jmp .LFUN_000f0790_11\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".LFUN_000f0790_11:\n\t"
      "movl 0x31e498(,%%ebx,4), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x46cd38\n\t"
      "call *%[c1dd801]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_000f0790_12\n\t"
      "incl %%ebx\n\t"
      "cmpl $0xa, %%ebx\n\t"
      "jl .LFUN_000f0790_11\n\t"
      "jmp .LFUN_000f0790_14\n\t"
      ".LFUN_000f0790_12:\n\t"
      "movw 0x46ce38, %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "movb %%bl, 0x46ce3a\n\t"
      "jge .LFUN_000f0790_13\n\t"
      "movw $0, 0x46ce38\n\t"
      "jmp .LFUN_000f0790_14\n\t"
      ".LFUN_000f0790_13:\n\t"
      "cmpw $3, %%ax\n\t"
      "movw $3, 0x46ce38\n\t"
      "jg .LFUN_000f0790_14\n\t"
      "movw %%ax, 0x46ce38\n\t"
      ".LFUN_000f0790_14:\n\t"
      "cmpl $0xa, %%ebx\n\t"
      "movb $1, %%al\n\t"
      "jne .LFUN_000f0790_18\n\t"
      "popl %%esi\n\t"
      "movb $0, 0x46ce3b\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000f0790_15:\n\t"
      "cmpb $1, 0x46ce3c\n\t"
      "jne .LFUN_000f0790_17\n\t"
      "pushl $0\n\t"
      "call *%[ce09e0]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $4, %%esp\n\t"
      "cmpl $-1, %%esi\n\t"
      "je .LFUN_000f0790_17\n\t"
      "cmpl $-1, 0x31e4c4\n\t"
      "jne .LFUN_000f0790_16\n\t"
      "pushl $0\n\t"
      "pushl $1\n\t"
      "pushl $-1\n\t"
      "pushl $0x27\n\t"
      "call *%[ce4500]\n\t"
      "addl $0x10, %%esp\n\t"
      "movl %%esi, 0x31e4c4\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000f0790_16:\n\t"
      "movl $0xffffffff, 0x31e4c4\n\t"
      ".LFUN_000f0790_17:\n\t"
      "movb $1, %%al\n\t"
      ".LFUN_000f0790_18:\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [memset] "m"(bf0790_memset), [ce98c0] "m"(bf0790_ce98c0), [ce09e0] "m"(bf0790_ce09e0), [c1bf920] "m"(bf0790_c1bf920), [ce0980] "m"(bf0790_ce0980), [c1c0f70] "m"(bf0790_c1c0f70), [tag] "m"(bf0790_tag), [assert] "m"(bf0790_assert), [exitfn] "m"(bf0790_exitfn), [ce0a10] "m"(bf0790_ce0a10), [c1dd801] "m"(bf0790_c1dd801), [ce4500] "m"(bf0790_ce4500)
      : "memory");
}
#else
#error "FUN_000f0790: clang naked draft required"
#endif


/* 0xf0aa0 */
void FUN_000f0aa0(void *widget)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;

  tag_get(0x44654c61, 0);
  /* test eax, eax -> je 0xf0acc */
  /* test eax, eax -> jne 0xf0aec */
  display_assert((char *)0x00288a5c, (char *)0x00288938, 300, 0);
  system_exit(0);
  /* relift: cmp dword ptr [edi + 0x3e0], 2 -> je 0xf0b15 */
  display_assert((char *)0x00288a24, (char *)0x00288938, 301, 0);
  system_exit(0);
  /* test eax, eax -> je 0xf0b42 */
  /* cmp eax, esi -> je 0xf0b3c */
  /* test eax, eax -> jne 0xf0b30 */
  /* cmp (int16_t)edi, -1 -> je 0xf0b9e */
  /* relift: cmp word ptr [ebx + 0xe], 0 -> je 0xf0b69 */
  display_assert((char *)0x002889d0, (char *)0x00288938, 312, 0);
  system_exit(0);
  /* relift: cmp word ptr [ecx + 0xe], 1 -> je 0xf0b93 */
  display_assert((char *)0x00288978, (char *)0x00288938, 313, 0);
  system_exit(0);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)esi;
  (void)edi;
}

/* 0xf0bb0 */
void FUN_000f0bb0(void *widget)
{
  int eax = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;

  /* test edi, edi -> je 0xf0bca */
  /* test eax, eax -> je 0xf0bca */
  /* test eax, eax -> jne 0xf0bea */
  display_assert((char *)0x00288a5c, (char *)0x00288938, 333, 0);
  system_exit(0);
  /* test eax, eax -> je 0xf0c08 */
  /* cmp eax, ecx -> je 0xf0c02 */
  /* test eax, eax -> jne 0xf0bf6 */
  /* cmp (int16_t)esi, -1 -> je 0xf0c57 */
  tag_get('aLeD', 0);
  /* cmp ecx, 2 -> je 0xf0c46 */
  display_assert((char *)0x00288aa0, (char *)0x00288938, 347, 0);
  system_exit(0);

  (void)eax;
  (void)ecx;
  (void)esi;
  (void)edi;
}

/* 0xf0c60 */
void FUN_000f0c60(void *widget)
{
  int eax = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;

  /* test edi, edi -> je 0xf0c7a */
  /* test eax, eax -> je 0xf0c7a */
  /* test eax, eax -> jne 0xf0c9a */
  display_assert((char *)0x00288a5c, (char *)0x00288938, 371, 0);
  system_exit(0);
  /* test eax, eax -> je 0xf0cb8 */
  /* cmp eax, ecx -> je 0xf0cb2 */
  /* test eax, eax -> jne 0xf0ca6 */
  /* cmp (int16_t)esi, -1 -> je 0xf0d07 */
  tag_get('aLeD', 0);
  /* cmp ecx, 2 -> je 0xf0cf6 */
  display_assert((char *)0x00288aa0, (char *)0x00288938, 385, 0);
  system_exit(0);

  (void)eax;
  (void)ecx;
  (void)esi;
  (void)edi;
}

/* 0xf0d10 */
void playlist_settings_menu_update_extended_description(void *widget)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;

  /* test esi, esi -> je 0xf0d37 */
  /* test eax, eax -> je 0xf0d37 */
  /* test eax, eax -> je 0xf0d37 */
  /* test eax, eax -> je 0xf0d37 */
  /* test ecx, ecx -> jne 0xf0d57 */
  display_assert((char *)0x00288a5c, (char *)0x00288938, 422, 0);
  system_exit(0);
  /* test eax, eax -> je 0xf0d75 */
  /* cmp eax, edx -> je 0xf0d6f */
  /* test eax, eax -> jne 0xf0d63 */
  /* cmp (int16_t)ecx, -1 -> je 0xf0d8c */

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
}

/* 0xf0d90 */
void FUN_000f0d90(void *widget)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;

  tag_get(0x44654c61, 0);
  /* test eax, eax -> je 0xf0dbc */
  /* test eax, eax -> jne 0xf0ddc */
  display_assert((char *)0x00288a5c, (char *)0x00288938, 567, 0);
  system_exit(0);
  /* relift: cmp dword ptr [edi + 0x3e0], 2 -> je 0xf0e05 */
  display_assert((char *)0x00288ba0, (char *)0x00288938, 568, 0);
  system_exit(0);
  /* test eax, eax -> je 0xf0e32 */
  /* cmp eax, esi -> je 0xf0e2c */
  /* test eax, eax -> jne 0xf0e20 */
  /* cmp (int16_t)edi, -1 -> je 0xf0e8e */
  /* relift: cmp word ptr [ebx + 0xe], 0 -> je 0xf0e59 */
  display_assert((char *)0x00288b50, (char *)0x00288938, 579, 0);
  system_exit(0);
  /* relift: cmp word ptr [ecx + 0xe], 1 -> je 0xf0e83 */
  display_assert((char *)0x00288b00, (char *)0x00288938, 580, 0);
  system_exit(0);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)esi;
  (void)edi;
}

/* FUN_000f0f30 (0xf0f30) — XBE naked draft (batch 105). */
#if defined(__clang__)
static void * (*const bf0f30_c12a240)(void) = network_game_client_get;
static void *(*const bf0f30_memset)(void *, int, unsigned int) = csmemset;
static void *(*const bf0f30_tag)(int, int) = tag_get;
static void * (*const bf0f30_c124c80)(void *client) = FUN_00124c80;
static void (*const bf0f30_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const bf0f30_exitfn)(int) = system_exit;
static char (*const bf0f30_c125cb0)(void *game) = network_game_client_advertised_game_is_valid;
static void * (*const bf0f30_ce3d20)(int a1, unsigned short a2, const char *a3, unsigned int a4) = ui_widget_realloc;
static wchar_t * (*const bf0f30_c19dc90)(wchar_t *dest, wchar_t *src, size_t count) = ustrncpy;
static int (*const bf0f30_c1b9930)(int group_tag, const char *name, ...) = tag_loaded;
static int (*const bf0f30_c19d420)(int param_1, int param_2) = FUN_0019d420;
static void (*const bf0f30_c19e9f0)(wchar_t *buffer, int buffer_size, const wchar_t *format, ...) = unicode_sprintf;
static unsigned int (*const bf0f30_c8e370)(void) = system_milliseconds;
static char * (*const bf0f30_c1d9690)(const char *haystack, const char *needle) = crt_strstr;

__attribute__((naked, noinline))
void FUN_000f0f30(void *widget __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x28, %%esp\n\t"
      "pushl %%esi\n\t"
      "call *%[c12a240]\n\t"
      "pushl $0x24\n\t"
      "pushl $0\n\t"
      "pushl $0x46ce40\n\t"
      "movl %%eax, %%esi\n\t"
      "movl $0, -0x4(%%ebp)\n\t"
      "call *%[memset]\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_000f0f30_70\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x44654c61\n\t"
      "call *%[tag]\n\t"
      "pushl %%esi\n\t"
      "movl %%eax, %%edi\n\t"
      "call *%[c124c80]\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpw $3, (%%edi)\n\t"
      "movl %%eax, %%esi\n\t"
      "jne .LFUN_000f0f30_1\n\t"
      "cmpl $9, 0x3e0(%%edi)\n\t"
      "je .LFUN_000f0f30_2\n\t"
      ".LFUN_000f0f30_1:\n\t"
      "pushl $1\n\t"
      "pushl $0x297\n\t"
      "pushl $0x288938\n\t"
      "pushl $0x288dd4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000f0f30_2:\n\t"
      "movl %%esi, %%edi\n\t"
      "movl $9, %%ebx\n\t"
      ".LFUN_000f0f30_3:\n\t"
      "pushl %%edi\n\t"
      "call *%[c125cb0]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000f0f30_4\n\t"
      "cmpw $0, 0xde(%%edi)\n\t"
      "jne .LFUN_000f0f30_4\n\t"
      "movb 0xe0(%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000f0f30_4\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movl %%edi, 0x46ce40(,%%eax,4)\n\t"
      "incl %%eax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      ".LFUN_000f0f30_4:\n\t"
      "addl $0xe4, %%edi\n\t"
      "decl %%ebx\n\t"
      "jne .LFUN_000f0f30_3\n\t"
      "movl -0x4(%%ebp), %%ebx\n\t"
      "movl $9, %%edi\n\t"
      ".LFUN_000f0f30_5:\n\t"
      "pushl %%esi\n\t"
      "call *%[c125cb0]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000f0f30_6\n\t"
      "cmpw $0, 0xde(%%esi)\n\t"
      "jne .LFUN_000f0f30_6\n\t"
      "movb 0xe0(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_000f0f30_6\n\t"
      "movl %%esi, 0x46ce40(,%%ebx,4)\n\t"
      "incl %%ebx\n\t"
      ".LFUN_000f0f30_6:\n\t"
      "addl $0xe4, %%esi\n\t"
      "decl %%edi\n\t"
      "jne .LFUN_000f0f30_5\n\t"
      "movl %%ebx, -0x4(%%ebp)\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "movswl 0x3c(%%ebx), %%eax\n\t"
      "leal -0x1(%%edx), %%ecx\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "movl $0x46ce40, 0x40(%%ebx)\n\t"
      "movw %%dx, 0x44(%%ebx)\n\t"
      "jle .LFUN_000f0f30_7\n\t"
      "movl %%ecx, %%eax\n\t"
      ".LFUN_000f0f30_7:\n\t"
      "movl 0x34(%%ebx), %%esi\n\t"
      "xorl %%edi, %%edi\n\t"
      "testl %%esi, %%esi\n\t"
      "movw %%ax, 0x3c(%%ebx)\n\t"
      "je .LFUN_000f0f30_12\n\t"
      ".LFUN_000f0f30_8:\n\t"
      "cmpl %%edx, %%edi\n\t"
      "jge .LFUN_000f0f30_12\n\t"
      "movl 0x3c(%%esi), %%edx\n\t"
      "pushl $0x2c5\n\t"
      "pushl $0x288938\n\t"
      "pushl $0x40\n\t"
      "pushl %%edx\n\t"
      "call *%[ce3d20]\n\t"
      "addl $0x10, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%eax, 0x3c(%%esi)\n\t"
      "je .LFUN_000f0f30_11\n\t"
      "movl 0x46ce40(,%%edi,4), %%ecx\n\t"
      "cmpb $1, 0xe0(%%ecx)\n\t"
      "jne .LFUN_000f0f30_9\n\t"
      "pushl $0x1f\n\t"
      "addl $0x30, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "call *%[c19dc90]\n\t"
      "addl $0xc, %%esp\n\t"
      "jmp .LFUN_000f0f30_10\n\t"
      ".LFUN_000f0f30_9:\n\t"
      "pushl $0x288db8\n\t"
      "pushl $0x75737472\n\t"
      "call *%[c1b9930]\n\t"
      "pushl $0x13\n\t"
      "pushl %%eax\n\t"
      "call *%[c19d420]\n\t"
      "movl 0x46ce40(,%%edi,4), %%ecx\n\t"
      "movl 0x3c(%%esi), %%edx\n\t"
      "addl $0x30, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl $0x288dac\n\t"
      "pushl $0x1f\n\t"
      "pushl %%edx\n\t"
      "call *%[c19e9f0]\n\t"
      "addl $0x24, %%esp\n\t"
      ".LFUN_000f0f30_10:\n\t"
      "movl 0x3c(%%esi), %%eax\n\t"
      "movw $0, 0x3e(%%eax)\n\t"
      ".LFUN_000f0f30_11:\n\t"
      "movl 0x2c(%%esi), %%esi\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "incl %%edi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LFUN_000f0f30_8\n\t"
      ".LFUN_000f0f30_12:\n\t"
      "testl %%edx, %%edx\n\t"
      "jle .LFUN_000f0f30_13\n\t"
      "cmpw $0, 0x3c(%%ebx)\n\t"
      "jge .LFUN_000f0f30_13\n\t"
      "movw $0, 0x3c(%%ebx)\n\t"
      ".LFUN_000f0f30_13:\n\t"
      "call *%[c8e370]\n\t"
      "subl 0x18(%%ebx), %%eax\n\t"
      "movl 0x48(%%ebx), %%ecx\n\t"
      "movl (%%ecx), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x44654c61\n\t"
      "movl %%eax, -0x28(%%ebp)\n\t"
      "call *%[tag]\n\t"
      "movl 0x3e0(%%eax), %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $5, %%ecx\n\t"
      "je .LFUN_000f0f30_14\n\t"
      "pushl $1\n\t"
      "pushl $0x2f7\n\t"
      "pushl $0x288938\n\t"
      "pushl $0x288d68\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000f0f30_14:\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl 0x48(%%eax), %%ecx\n\t"
      "movl 0x34(%%ecx), %%eax\n\t"
      "movl 0x2c(%%eax), %%ebx\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "movl 0x2c(%%ebx), %%eax\n\t"
      "movl 0x34(%%eax), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "movl 0x2c(%%eax), %%edx\n\t"
      "movl %%edx, -0x1c(%%ebp)\n\t"
      "movl %%edi, -0x14(%%ebp)\n\t"
      "movl $1, %%esi\n\t"
      "je .LFUN_000f0f30_15\n\t"
      "cmpw %%si, 0xe(%%edi)\n\t"
      "je .LFUN_000f0f30_16\n\t"
      ".LFUN_000f0f30_15:\n\t"
      "pushl %%esi\n\t"
      "pushl $0x2ff\n\t"
      "pushl $0x288938\n\t"
      "pushl $0x288d40\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000f0f30_16:\n\t"
      "movl 0x2c(%%edi), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "movl %%edi, -0x18(%%ebp)\n\t"
      "je .LFUN_000f0f30_17\n\t"
      "cmpw %%si, 0xe(%%edi)\n\t"
      "je .LFUN_000f0f30_18\n\t"
      ".LFUN_000f0f30_17:\n\t"
      "pushl %%esi\n\t"
      "pushl $0x301\n\t"
      "pushl $0x288938\n\t"
      "pushl $0x288d24\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000f0f30_18:\n\t"
      "movl 0x2c(%%edi), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "movl %%edi, -0x8(%%ebp)\n\t"
      "je .LFUN_000f0f30_19\n\t"
      "cmpw %%si, 0xe(%%edi)\n\t"
      "je .LFUN_000f0f30_20\n\t"
      ".LFUN_000f0f30_19:\n\t"
      "pushl %%esi\n\t"
      "pushl $0x303\n\t"
      "pushl $0x288938\n\t"
      "pushl $0x288d08\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000f0f30_20:\n\t"
      "movl 0x2c(%%edi), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "movl %%edi, -0x20(%%ebp)\n\t"
      "je .LFUN_000f0f30_21\n\t"
      "cmpw %%si, 0xe(%%edi)\n\t"
      "je .LFUN_000f0f30_22\n\t"
      ".LFUN_000f0f30_21:\n\t"
      "pushl %%esi\n\t"
      "pushl $0x305\n\t"
      "pushl $0x288938\n\t"
      "pushl $0x288ce8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000f0f30_22:\n\t"
      "movl 0x2c(%%edi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%esi, -0x24(%%ebp)\n\t"
      "je .LFUN_000f0f30_23\n\t"
      "cmpw $1, 0xe(%%esi)\n\t"
      "je .LFUN_000f0f30_24\n\t"
      ".LFUN_000f0f30_23:\n\t"
      "pushl $1\n\t"
      "pushl $0x307\n\t"
      "pushl $0x288938\n\t"
      "pushl $0x288cc0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000f0f30_24:\n\t"
      "movl 0x2c(%%esi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "je .LFUN_000f0f30_25\n\t"
      "cmpw $1, 0xe(%%eax)\n\t"
      "je .LFUN_000f0f30_26\n\t"
      ".LFUN_000f0f30_25:\n\t"
      "pushl $1\n\t"
      "pushl $0x309\n\t"
      "pushl $0x288938\n\t"
      "pushl $0x288ca0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000f0f30_26:\n\t"
      "movl 0x2c(%%eax), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "je .LFUN_000f0f30_27\n\t"
      "cmpw $1, 0xe(%%eax)\n\t"
      "je .LFUN_000f0f30_28\n\t"
      ".LFUN_000f0f30_27:\n\t"
      "pushl $1\n\t"
      "pushl $0x30b\n\t"
      "pushl $0x288938\n\t"
      "pushl $0x288c7c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000f0f30_28:\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movw 0x3c(%%eax), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "jl .LFUN_000f0f30_66\n\t"
      "movswl %%ax, %%ecx\n\t"
      "movl 0x46ce40(,%%ecx,4), %%esi\n\t"
      "movswl 0xd4(%%esi), %%eax\n\t"
      "decl %%eax\n\t"
      "cmpl $4, %%eax\n\t"
      "ja .LFUN_000f0f30_34\n\t"
      "jmp *.LFUN_000f0f30_jt0(,%%eax,4)\n\t"
      ".LFUN_000f0f30_29:\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "movw $0, 0x50(%%edx)\n\t"
      "jmp .LFUN_000f0f30_35\n\t"
      ".LFUN_000f0f30_30:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movw $2, 0x50(%%eax)\n\t"
      "jmp .LFUN_000f0f30_35\n\t"
      ".LFUN_000f0f30_31:\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movw $3, 0x50(%%ecx)\n\t"
      "jmp .LFUN_000f0f30_35\n\t"
      ".LFUN_000f0f30_32:\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "movw $1, 0x50(%%edx)\n\t"
      "jmp .LFUN_000f0f30_35\n\t"
      ".LFUN_000f0f30_33:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movw $4, 0x50(%%eax)\n\t"
      "jmp .LFUN_000f0f30_35\n\t"
      ".LFUN_000f0f30_34:\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movw $5, 0x50(%%ecx)\n\t"
      ".LFUN_000f0f30_35:\n\t"
      "leal 0x54(%%esi), %%edi\n\t"
      "pushl $0x288c70\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d9690]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_000f0f30_36\n\t"
      "movw $0, 0x50(%%ebx)\n\t"
      "jmp .LFUN_000f0f30_49\n\t"
      ".LFUN_000f0f30_36:\n\t"
      "pushl $0x288c64\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d9690]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_000f0f30_37\n\t"
      "movw $1, 0x50(%%ebx)\n\t"
      "jmp .LFUN_000f0f30_49\n\t"
      ".LFUN_000f0f30_37:\n\t"
      "pushl $0x288c58\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d9690]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_000f0f30_38\n\t"
      "movw $2, 0x50(%%ebx)\n\t"
      "jmp .LFUN_000f0f30_49\n\t"
      ".LFUN_000f0f30_38:\n\t"
      "pushl $0x288c50\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d9690]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_000f0f30_39\n\t"
      "movw $3, 0x50(%%ebx)\n\t"
      "jmp .LFUN_000f0f30_49\n\t"
      ".LFUN_000f0f30_39:\n\t"
      "pushl $0x288c44\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d9690]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_000f0f30_40\n\t"
      "movw $4, 0x50(%%ebx)\n\t"
      "jmp .LFUN_000f0f30_49\n\t"
      ".LFUN_000f0f30_40:\n\t"
      "pushl $0x288c38\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d9690]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_000f0f30_41\n\t"
      "movw $5, 0x50(%%ebx)\n\t"
      "jmp .LFUN_000f0f30_49\n\t"
      ".LFUN_000f0f30_41:\n\t"
      "pushl $0x288c2c\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d9690]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_000f0f30_42\n\t"
      "movw $6, 0x50(%%ebx)\n\t"
      "jmp .LFUN_000f0f30_49\n\t"
      ".LFUN_000f0f30_42:\n\t"
      "pushl $0x288c20\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d9690]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_000f0f30_43\n\t"
      "movw $7, 0x50(%%ebx)\n\t"
      "jmp .LFUN_000f0f30_49\n\t"
      ".LFUN_000f0f30_43:\n\t"
      "pushl $0x288c10\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d9690]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_000f0f30_44\n\t"
      "movw $8, 0x50(%%ebx)\n\t"
      "jmp .LFUN_000f0f30_49\n\t"
      ".LFUN_000f0f30_44:\n\t"
      "pushl $0x288c04\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d9690]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_000f0f30_45\n\t"
      "movw $9, 0x50(%%ebx)\n\t"
      "jmp .LFUN_000f0f30_49\n\t"
      ".LFUN_000f0f30_45:\n\t"
      "pushl $0x288bfc\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d9690]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_000f0f30_46\n\t"
      "movw $0xa, 0x50(%%ebx)\n\t"
      "jmp .LFUN_000f0f30_49\n\t"
      ".LFUN_000f0f30_46:\n\t"
      "pushl $0x288bf4\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d9690]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_000f0f30_47\n\t"
      "movw $0xb, 0x50(%%ebx)\n\t"
      "jmp .LFUN_000f0f30_49\n\t"
      ".LFUN_000f0f30_47:\n\t"
      "pushl $0x288bec\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d9690]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_000f0f30_48\n\t"
      "movw $0xc, 0x50(%%ebx)\n\t"
      "jmp .LFUN_000f0f30_49\n\t"
      ".LFUN_000f0f30_48:\n\t"
      "movw $0xd, 0x50(%%ebx)\n\t"
      ".LFUN_000f0f30_49:\n\t"
      "movb 0xe0(%%esi), %%al\n\t"
      "xorl %%edx, %%edx\n\t"
      "cmpb $1, %%al\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "setne %%dl\n\t"
      "addl $0x14, %%edx\n\t"
      "movw %%dx, 0x40(%%eax)\n\t"
      "movw 0x50(%%ebx), %%cx\n\t"
      "movl -0x18(%%ebp), %%edx\n\t"
      "movw %%cx, 0x40(%%edx)\n\t"
      "movswl 0xd4(%%esi), %%eax\n\t"
      "decl %%eax\n\t"
      "cmpl $4, %%eax\n\t"
      "ja .LFUN_000f0f30_55\n\t"
      "jmp *.LFUN_000f0f30_jt1(,%%eax,4)\n\t"
      ".LFUN_000f0f30_50:\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movw $3, 0x40(%%eax)\n\t"
      "jmp .LFUN_000f0f30_56\n\t"
      ".LFUN_000f0f30_51:\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movw $4, 0x40(%%ecx)\n\t"
      "jmp .LFUN_000f0f30_56\n\t"
      ".LFUN_000f0f30_52:\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "movw $5, 0x40(%%edx)\n\t"
      "jmp .LFUN_000f0f30_56\n\t"
      ".LFUN_000f0f30_53:\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movw $6, 0x40(%%eax)\n\t"
      "jmp .LFUN_000f0f30_56\n\t"
      ".LFUN_000f0f30_54:\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movw $7, 0x40(%%ecx)\n\t"
      "jmp .LFUN_000f0f30_56\n\t"
      ".LFUN_000f0f30_55:\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "movw $8, 0x40(%%edx)\n\t"
      ".LFUN_000f0f30_56:\n\t"
      "movb 0xe2(%%esi), %%bl\n\t"
      "movl -0x20(%%ebp), %%ecx\n\t"
      "movl -0x24(%%ebp), %%edi\n\t"
      "xorl %%eax, %%eax\n\t"
      "cmpb $1, %%bl\n\t"
      "setne %%al\n\t"
      "pushl $0x364\n\t"
      "pushl $0x288938\n\t"
      "pushl $8\n\t"
      "addl $0xc, %%eax\n\t"
      "movw %%ax, 0x40(%%ecx)\n\t"
      "movl 0x3c(%%edi), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[ce3d20]\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpl %%ebx, %%eax\n\t"
      "movl %%eax, 0x3c(%%edi)\n\t"
      "je .LFUN_000f0f30_57\n\t"
      "movzwl 0xd8(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x26c118\n\t"
      "pushl $3\n\t"
      "pushl %%eax\n\t"
      "call *%[c19e9f0]\n\t"
      "movl 0x3c(%%edi), %%edx\n\t"
      "addl $0x10, %%esp\n\t"
      "movw %%bx, 0x6(%%edx)\n\t"
      ".LFUN_000f0f30_57:\n\t"
      "movl -0x10(%%ebp), %%edi\n\t"
      "movl 0x3c(%%edi), %%eax\n\t"
      "pushl $0x369\n\t"
      "pushl $0x288938\n\t"
      "pushl $8\n\t"
      "pushl %%eax\n\t"
      "call *%[ce3d20]\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpl %%ebx, %%eax\n\t"
      "movl %%eax, 0x3c(%%edi)\n\t"
      "je .LFUN_000f0f30_58\n\t"
      "movswl 0xdc(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x26c118\n\t"
      "pushl $3\n\t"
      "pushl %%eax\n\t"
      "call *%[c19e9f0]\n\t"
      "movl 0x3c(%%edi), %%edx\n\t"
      "addl $0x10, %%esp\n\t"
      "movw %%bx, 0x6(%%edx)\n\t"
      ".LFUN_000f0f30_58:\n\t"
      "movswl 0xd4(%%esi), %%eax\n\t"
      "decl %%eax\n\t"
      "cmpl $4, %%eax\n\t"
      "ja .LFUN_000f0f30_64\n\t"
      "jmp *.LFUN_000f0f30_jt2(,%%eax,4)\n\t"
      ".LFUN_000f0f30_59:\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "movw $0x16, 0x40(%%eax)\n\t"
      "jmp .LFUN_000f0f30_65\n\t"
      ".LFUN_000f0f30_60:\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "movw $0x18, 0x40(%%ecx)\n\t"
      "jmp .LFUN_000f0f30_65\n\t"
      ".LFUN_000f0f30_61:\n\t"
      "movb 0xe3(%%esi), %%dl\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "decb %%dl\n\t"
      "negb %%dl\n\t"
      "sbbl %%edx, %%edx\n\t"
      "addl $0x18, %%edx\n\t"
      "movw %%dx, 0x40(%%eax)\n\t"
      "jmp .LFUN_000f0f30_65\n\t"
      ".LFUN_000f0f30_62:\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "movw $0x17, 0x40(%%ecx)\n\t"
      "jmp .LFUN_000f0f30_65\n\t"
      ".LFUN_000f0f30_63:\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "movw $0x19, 0x40(%%edx)\n\t"
      "jmp .LFUN_000f0f30_65\n\t"
      ".LFUN_000f0f30_64:\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "movw $1, 0x40(%%eax)\n\t"
      ".LFUN_000f0f30_65:\n\t"
      "movl -0x1c(%%ebp), %%eax\n\t"
      "movw $2, 0x40(%%eax)\n\t"
      "movb $0, 0x10(%%eax)\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "cmpl %%ebx, 0x38(%%eax)\n\t"
      "jne .LFUN_000f0f30_69\n\t"
      "movl 0x34(%%eax), %%ecx\n\t"
      "popl %%edi\n\t"
      "movw %%bx, 0x3c(%%eax)\n\t"
      "popl %%ebx\n\t"
      "movl %%ecx, 0x38(%%eax)\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000f0f30_66:\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "movl -0x14(%%ebp), %%ecx\n\t"
      "movw $5, 0x50(%%edx)\n\t"
      "movl -0x18(%%ebp), %%edx\n\t"
      "movw $0xd, 0x50(%%ebx)\n\t"
      "movl $1, %%eax\n\t"
      "movw %%ax, 0x40(%%ecx)\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movw $0xe, 0x40(%%edx)\n\t"
      "pushl $0x3a3\n\t"
      "movw %%ax, 0x40(%%ecx)\n\t"
      "pushl $0x288938\n\t"
      "movw %%ax, 0x40(%%edi)\n\t"
      "movl 0x3c(%%esi), %%edx\n\t"
      "pushl $8\n\t"
      "pushl %%edx\n\t"
      "call *%[ce3d20]\n\t"
      "addl $0x10, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%eax, 0x3c(%%esi)\n\t"
      "je .LFUN_000f0f30_67\n\t"
      "movw $0, (%%eax)\n\t"
      ".LFUN_000f0f30_67:\n\t"
      "movl -0x10(%%ebp), %%esi\n\t"
      "movl 0x3c(%%esi), %%eax\n\t"
      "pushl $0x3a7\n\t"
      "pushl $0x288938\n\t"
      "pushl $8\n\t"
      "pushl %%eax\n\t"
      "call *%[ce3d20]\n\t"
      "addl $0x10, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%eax, 0x3c(%%esi)\n\t"
      "je .LFUN_000f0f30_68\n\t"
      "movw $0, (%%eax)\n\t"
      ".LFUN_000f0f30_68:\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "movl -0x1c(%%ebp), %%eax\n\t"
      "movw $1, 0x40(%%ecx)\n\t"
      "cmpl $0x3e8, -0x28(%%ebp)\n\t"
      "sbbl %%edx, %%edx\n\t"
      "incl %%edx\n\t"
      "movw %%dx, 0x40(%%eax)\n\t"
      "movb $1, 0x10(%%eax)\n\t"
      ".LFUN_000f0f30_69:\n\t"
      "popl %%edi\n\t"
      "popl %%ebx\n\t"
      ".LFUN_000f0f30_70:\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_000f0f30_jt0:\n\t"
      ".long .LFUN_000f0f30_29\n\t"
      ".long .LFUN_000f0f30_30\n\t"
      ".long .LFUN_000f0f30_31\n\t"
      ".long .LFUN_000f0f30_32\n\t"
      ".long .LFUN_000f0f30_33\n\t"
      ".text\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_000f0f30_jt1:\n\t"
      ".long .LFUN_000f0f30_50\n\t"
      ".long .LFUN_000f0f30_51\n\t"
      ".long .LFUN_000f0f30_52\n\t"
      ".long .LFUN_000f0f30_53\n\t"
      ".long .LFUN_000f0f30_54\n\t"
      ".text\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_000f0f30_jt2:\n\t"
      ".long .LFUN_000f0f30_59\n\t"
      ".long .LFUN_000f0f30_60\n\t"
      ".long .LFUN_000f0f30_61\n\t"
      ".long .LFUN_000f0f30_62\n\t"
      ".long .LFUN_000f0f30_63\n\t"
      ".text\n\t"
      :
      : [c12a240] "m"(bf0f30_c12a240), [memset] "m"(bf0f30_memset), [tag] "m"(bf0f30_tag), [c124c80] "m"(bf0f30_c124c80), [assert] "m"(bf0f30_assert), [exitfn] "m"(bf0f30_exitfn), [c125cb0] "m"(bf0f30_c125cb0), [ce3d20] "m"(bf0f30_ce3d20), [c19dc90] "m"(bf0f30_c19dc90), [c1b9930] "m"(bf0f30_c1b9930), [c19d420] "m"(bf0f30_c19d420), [c19e9f0] "m"(bf0f30_c19e9f0), [c8e370] "m"(bf0f30_c8e370), [c1d9690] "m"(bf0f30_c1d9690)
      : "memory");
}
#else
#error "FUN_000f0f30: clang naked draft required"
#endif


/* FUN_000f1710 (0xf1710) — update network pregame/status item widget texts and visibility. */
#if defined(__clang__)
static int (*const f1710_n2a0a0)(void) = FUN_0012a0a0;
static void *(*const f1710_tag)(int, int) = tag_get;
static void (*const f1710_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const f1710_exitfn)(int) = system_exit;
static void *(*const f1710_ngcli)(void) = network_game_client_get;
static unsigned short (*const f1710_n24c40)(void *) = FUN_00124c40;
static void *(*const f1710_uirealloc)(int, unsigned short, const char *, unsigned int) = ui_widget_realloc;
static short (*const f1710_n24d00)(void *) = FUN_00124d00;
static void *(*const f1710_ngsrv)(void) = network_game_server_get;
static wchar_t *(*const f1710_xucpy)(wchar_t *, wchar_t *, unsigned int) = ustrncpy;
static void (*const f1710_usprintf)(wchar_t *, int, const wchar_t *, ...) = unicode_sprintf;
static void *(*const f1710_ngmach)(void *) = network_game_client_get_machine;
static void *(*const f1710_memset)(void *, int, unsigned int) = csmemset;
static bool (*const f1710_npval)(void *) = network_player_is_valid;
static int (*const f1710_xulen)(const unsigned short *) = ustrlen;
static void (*const f1710_wvis)(void *, char) = widget_instance_set_visibility_recursive;

__attribute__((naked, noinline))
void FUN_000f1710(void *widget __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x54, %%esp\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[n2a0a0]\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "movl %%eax, %%edi\n\t"
      "movl (%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x44654c61\n\t"
      "movl %%edi, -0x8(%%ebp)\n\t"
      "call *%[tag]\n\t"
      "movl 0x3e0(%%eax), %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $6, %%ecx\n\t"
      "je .LFUN_000f1710_1\n\t"
      "pushl $1\n\t"
      "pushl $0x3fc\n\t"
      "pushl $0x288938\n\t"
      "pushl $0x288f28\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000f1710_1:\n\t"
      "testl %%edi, %%edi\n\t"
      "je .LFUN_000f1710_57\n\t"
      "pushl %%ebx\n\t"
      "call *%[ngcli]\n\t"
      "pushl %%eax\n\t"
      "call *%[n24c40]\n\t"
      "movl 0x34(%%esi), %%ebx\n\t"
      "pushl $0x40b\n\t"
      "pushl $0x288938\n\t"
      "pushl $0x20\n\t"
      "movl %%ebx, -0x14(%%ebp)\n\t"
      "movl %%eax, -0x18(%%ebp)\n\t"
      "movl 0x2c(%%ebx), %%eax\n\t"
      "movl %%eax, -0x1c(%%ebp)\n\t"
      "movl 0x2c(%%eax), %%eax\n\t"
      "movl %%eax, -0x20(%%ebp)\n\t"
      "movl 0x2c(%%eax), %%eax\n\t"
      "movl 0x2c(%%eax), %%edi\n\t"
      "movl 0x2c(%%edi), %%esi\n\t"
      "movl 0x3c(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl %%eax, -0x24(%%ebp)\n\t"
      "call *%[uirealloc]\n\t"
      "addl $0x14, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%eax, 0x3c(%%esi)\n\t"
      "je .LFUN_000f1710_11\n\t"
      "call *%[ngcli]\n\t"
      "pushl %%eax\n\t"
      "call *%[n24d00]\n\t"
      "addl $4, %%esp\n\t"
      "movl %%eax, %%ebx\n\t"
      "call *%[ngsrv]\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_000f1710_2\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "cmpw $2, 0x112(%%edx)\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "jl .LFUN_000f1710_3\n\t"
      ".LFUN_000f1710_2:\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      ".LFUN_000f1710_3:\n\t"
      "movl 0x3c(%%esi), %%eax\n\t"
      "pushl $0xf\n\t"
      "pushl $0x288f1c\n\t"
      "pushl %%eax\n\t"
      "call *%[xucpy]\n\t"
      "addl $0xc, %%esp\n\t"
      "testw %%bx, %%bx\n\t"
      "movb $1, 0x10(%%edi)\n\t"
      "movw $0, 0x40(%%edi)\n\t"
      "movb $1, 0x10(%%esi)\n\t"
      "jne .LFUN_000f1710_4\n\t"
      "movw $1, 0x40(%%edi)\n\t"
      "jmp .LFUN_000f1710_9\n\t"
      ".LFUN_000f1710_4:\n\t"
      "jle .LFUN_000f1710_7\n\t"
      "cmpw $0x3c, %%bx\n\t"
      "movswl %%bx, %%ecx\n\t"
      "jge .LFUN_000f1710_5\n\t"
      "movl 0x3c(%%esi), %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x288f0c\n\t"
      "pushl $0xf\n\t"
      "pushl %%edx\n\t"
      "call *%[usprintf]\n\t"
      "addl $0x10, %%esp\n\t"
      "jmp .LFUN_000f1710_10\n\t"
      ".LFUN_000f1710_5:\n\t"
      "cmpw $0xe10, %%bx\n\t"
      "jge .LFUN_000f1710_6\n\t"
      "movl $0x88888889, %%eax\n\t"
      "imull %%ecx\n\t"
      "addl %%ecx, %%edx\n\t"
      "sarl $5, %%edx\n\t"
      "movl %%edx, %%eax\n\t"
      "shrl $0x1f, %%eax\n\t"
      "addl %%eax, %%edx\n\t"
      "movl %%edx, %%eax\n\t"
      "imull $0x3c, %%eax, %%eax\n\t"
      "subl %%eax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl 0x3c(%%esi), %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x288ef8\n\t"
      "pushl $0xf\n\t"
      "pushl %%ecx\n\t"
      "call *%[usprintf]\n\t"
      "addl $0x14, %%esp\n\t"
      "jmp .LFUN_000f1710_10\n\t"
      ".LFUN_000f1710_6:\n\t"
      "movl $0x91a2b3c5, %%eax\n\t"
      "imull %%ecx\n\t"
      "addl %%ecx, %%edx\n\t"
      "sarl $0xb, %%edx\n\t"
      "movl %%edx, %%eax\n\t"
      "shrl $0x1f, %%eax\n\t"
      "addl %%eax, %%edx\n\t"
      "movl %%edx, %%ebx\n\t"
      "imull $0xe10, %%edx, %%edx\n\t"
      "movl %%ecx, %%edi\n\t"
      "subl %%edx, %%edi\n\t"
      "movl $0x88888889, %%eax\n\t"
      "imull %%edi\n\t"
      "addl %%edi, %%edx\n\t"
      "sarl $5, %%edx\n\t"
      "movl %%edx, %%eax\n\t"
      "shrl $0x1f, %%eax\n\t"
      "addl %%eax, %%edx\n\t"
      "movl %%ebx, %%eax\n\t"
      "imull $0x3c, %%eax, %%eax\n\t"
      "addl %%edx, %%eax\n\t"
      "imull $0x3c, %%eax, %%eax\n\t"
      "subl %%eax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl 0x3c(%%esi), %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ebx\n\t"
      "pushl $0x288edc\n\t"
      "pushl $0xf\n\t"
      "pushl %%ecx\n\t"
      "call *%[usprintf]\n\t"
      "addl $0x18, %%esp\n\t"
      "jmp .LFUN_000f1710_10\n\t"
      ".LFUN_000f1710_7:\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_000f1710_8\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "cmpb $1, 0xc0(%%edx)\n\t"
      "jne .LFUN_000f1710_10\n\t"
      ".LFUN_000f1710_8:\n\t"
      "movb $0, 0x10(%%edi)\n\t"
      ".LFUN_000f1710_9:\n\t"
      "movb $0, 0x10(%%esi)\n\t"
      ".LFUN_000f1710_10:\n\t"
      "movl 0x3c(%%esi), %%eax\n\t"
      "movl -0x14(%%ebp), %%ebx\n\t"
      "movw $0, 0x1e(%%eax)\n\t"
      ".LFUN_000f1710_11:\n\t"
      "movl (%%ebx), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x44654c61\n\t"
      "call *%[tag]\n\t"
      "movl 0x3e0(%%eax), %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $6, %%ecx\n\t"
      "je .LFUN_000f1710_12\n\t"
      "pushl $1\n\t"
      "pushl $0x44c\n\t"
      "pushl $0x288938\n\t"
      "pushl $0x288f28\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000f1710_12:\n\t"
      "movl 0x34(%%ebx), %%ebx\n\t"
      "movl %%ebx, -0x10(%%ebp)\n\t"
      "movl 0x2c(%%ebx), %%ebx\n\t"
      "movl 0x2c(%%ebx), %%eax\n\t"
      "movl %%eax, -0x44(%%ebp)\n\t"
      "movl 0x2c(%%eax), %%eax\n\t"
      "movl %%eax, -0x40(%%ebp)\n\t"
      "movl 0x2c(%%eax), %%eax\n\t"
      "movl 0x2c(%%eax), %%edx\n\t"
      "movl %%eax, -0x3c(%%ebp)\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "addl $0x154, %%eax\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "movl $0x288ed8, -0x14(%%ebp)\n\t"
      "movl %%ebx, -0xc(%%ebp)\n\t"
      "movl %%edx, -0x38(%%ebp)\n\t"
      "movl %%eax, -0x28(%%ebp)\n\t"
      "movl %%eax, %%esi\n\t"
      "movl $4, %%edi\n\t"
      ".LFUN_000f1710_13:\n\t"
      "leal -0x40(%%esi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_000f1710_15\n\t"
      "movb (%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jl .LFUN_000f1710_15\n\t"
      "cmpb $4, %%al\n\t"
      "jge .LFUN_000f1710_15\n\t"
      "movsbw %%al, %%cx\n\t"
      "cmpw -0x18(%%ebp), %%cx\n\t"
      "jne .LFUN_000f1710_15\n\t"
      "call *%[ngcli]\n\t"
      "pushl %%eax\n\t"
      "call *%[ngmach]\n\t"
      "addl $4, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_000f1710_14\n\t"
      "cmpw $0, (%%eax)\n\t"
      "je .LFUN_000f1710_14\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      ".LFUN_000f1710_14:\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      ".LFUN_000f1710_15:\n\t"
      "addl $0x44, %%esi\n\t"
      "decl %%edi\n\t"
      "jne .LFUN_000f1710_13\n\t"
      "pushl $0x10\n\t"
      "leal -0x54(%%ebp), %%edx\n\t"
      "pushl $-1\n\t"
      "pushl %%edx\n\t"
      "call *%[memset]\n\t"
      "movl -0x8(%%ebp), %%esi\n\t"
      "addl $0xc, %%esp\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "xorl %%edi, %%edi\n\t"
      "addl $0x242, %%esi\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".LFUN_000f1710_16:\n\t"
      "leal -0x1c(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[npval]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000f1710_17\n\t"
      "movsbw (%%esi), %%cx\n\t"
      "cmpw -0x18(%%ebp), %%cx\n\t"
      "jne .LFUN_000f1710_17\n\t"
      "movsbl 0x1(%%esi), %%edx\n\t"
      "incl %%ebx\n\t"
      "cmpl $4, %%ebx\n\t"
      "movl %%edi, -0x54(%%ebp,%%edx,4)\n\t"
      "je .LFUN_000f1710_18\n\t"
      ".LFUN_000f1710_17:\n\t"
      "incl %%edi\n\t"
      "addl $0x20, %%esi\n\t"
      "cmpl $0x10, %%edi\n\t"
      "jl .LFUN_000f1710_16\n\t"
      ".LFUN_000f1710_18:\n\t"
      "movl -0x14(%%ebp), %%ebx\n\t"
      "pushl %%ebx\n\t"
      "call *%[xulen]\n\t"
      "movl -0x10(%%ebp), %%edi\n\t"
      "movl 0x3c(%%edi), %%ecx\n\t"
      "pushl $0x47b\n\t"
      "movl %%eax, %%esi\n\t"
      "pushl $0x288938\n\t"
      "leal 0x2(%%esi,%%esi,1), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[uirealloc]\n\t"
      "addl $0x14, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%eax, 0x3c(%%edi)\n\t"
      "je .LFUN_000f1710_19\n\t"
      "pushl %%esi\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "call *%[xucpy]\n\t"
      "movl 0x3c(%%edi), %%edx\n\t"
      "addl $0xc, %%esp\n\t"
      "movw $0, (%%edx,%%esi,2)\n\t"
      ".LFUN_000f1710_19:\n\t"
      "movb -0x1(%%ebp), %%cl\n\t"
      "xorl %%eax, %%eax\n\t"
      "testb %%cl, %%cl\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "setne %%al\n\t"
      "movl $0x2888f5, -0x14(%%ebp)\n\t"
      "movl $0, -0xc(%%ebp)\n\t"
      "movw %%ax, 0x50(%%ecx)\n\t"
      ".LFUN_000f1710_20:\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "movl -0x44(%%ebp,%%edx,1), %%esi\n\t"
      "movl (%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x44654c61\n\t"
      "call *%[tag]\n\t"
      "movl 0x3e0(%%eax), %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $3, %%ecx\n\t"
      "je .LFUN_000f1710_21\n\t"
      "pushl $1\n\t"
      "pushl $0x485\n\t"
      "pushl $0x288938\n\t"
      "pushl $0x288f28\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000f1710_21:\n\t"
      "movl 0x34(%%esi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%esi, -0x10(%%ebp)\n\t"
      "je .LFUN_000f1710_22\n\t"
      "cmpw $0, 0xe(%%esi)\n\t"
      "je .LFUN_000f1710_23\n\t"
      ".LFUN_000f1710_22:\n\t"
      "pushl $1\n\t"
      "pushl $0x48b\n\t"
      "pushl $0x288938\n\t"
      "pushl $0x288e98\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000f1710_23:\n\t"
      "movl 0x2c(%%esi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_000f1710_24\n\t"
      "cmpw $1, 0xe(%%esi)\n\t"
      "je .LFUN_000f1710_25\n\t"
      ".LFUN_000f1710_24:\n\t"
      "pushl $1\n\t"
      "pushl $0x48d\n\t"
      "pushl $0x288938\n\t"
      "pushl $0x288e68\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000f1710_25:\n\t"
      "movl 0x2c(%%esi), %%ebx\n\t"
      "testl %%ebx, %%ebx\n\t"
      "je .LFUN_000f1710_26\n\t"
      "cmpw $2, 0xe(%%ebx)\n\t"
      "je .LFUN_000f1710_27\n\t"
      ".LFUN_000f1710_26:\n\t"
      "pushl $1\n\t"
      "pushl $0x48f\n\t"
      "pushl $0x288938\n\t"
      "pushl $0x288e30\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000f1710_27:\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movb 0xc0(%%ecx), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_000f1710_28\n\t"
      "pushl $0\n\t"
      "jmp .LFUN_000f1710_29\n\t"
      ".LFUN_000f1710_28:\n\t"
      "pushl $1\n\t"
      ".LFUN_000f1710_29:\n\t"
      "pushl %%ebx\n\t"
      "call *%[wvis]\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "movl -0x54(%%ebp,%%edx,1), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "jne .LFUN_000f1710_31\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "pushl $0x49d\n\t"
      "pushl $0x288938\n\t"
      "movw $0, 0x50(%%eax)\n\t"
      "movl 0x3c(%%esi), %%ecx\n\t"
      "pushl $2\n\t"
      "pushl %%ecx\n\t"
      "call *%[uirealloc]\n\t"
      "addl $0x10, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%eax, 0x3c(%%esi)\n\t"
      "je .LFUN_000f1710_30\n\t"
      "movw $0, (%%eax)\n\t"
      ".LFUN_000f1710_30:\n\t"
      "movw $2, 0x3c(%%ebx)\n\t"
      "jmp .LFUN_000f1710_36\n\t"
      ".LFUN_000f1710_31:\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "shll $5, %%eax\n\t"
      "leal 0x226(%%eax,%%edx,1), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[xulen]\n\t"
      "movl 0x3c(%%esi), %%edx\n\t"
      "pushl $0x4a6\n\t"
      "movl %%eax, %%edi\n\t"
      "pushl $0x288938\n\t"
      "leal 0x2(%%edi,%%edi,1), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[uirealloc]\n\t"
      "addl $0x14, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%eax, 0x3c(%%esi)\n\t"
      "je .LFUN_000f1710_32\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "movl -0x54(%%ebp,%%ecx,1), %%edx\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "shll $5, %%edx\n\t"
      "pushl %%edi\n\t"
      "leal 0x226(%%edx,%%ecx,1), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[xucpy]\n\t"
      "movl 0x3c(%%esi), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "movw $0, (%%eax,%%edi,2)\n\t"
      ".LFUN_000f1710_32:\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movb 0xc0(%%eax), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "jne .LFUN_000f1710_33\n\t"
      "movl -0x10(%%ebp), %%ecx\n\t"
      "movw $1, 0x50(%%ecx)\n\t"
      "jmp .LFUN_000f1710_36\n\t"
      ".LFUN_000f1710_33:\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "movl -0x54(%%ebp,%%edx,1), %%ecx\n\t"
      "movl -0x14(%%ebp), %%edx\n\t"
      "shll $5, %%ecx\n\t"
      "movsbl 0x244(%%ecx,%%eax,1), %%eax\n\t"
      "subl $0, %%eax\n\t"
      "movl -0x10(%%ebp), %%ecx\n\t"
      "je .LFUN_000f1710_35\n\t"
      "decl %%eax\n\t"
      "je .LFUN_000f1710_34\n\t"
      "movzbw -0x1(%%edx), %%ax\n\t"
      "movw %%ax, 0x50(%%ecx)\n\t"
      "movw $2, 0x3c(%%ebx)\n\t"
      "jmp .LFUN_000f1710_36\n\t"
      ".LFUN_000f1710_34:\n\t"
      "movzbw (%%edx), %%ax\n\t"
      "movw %%ax, 0x50(%%ecx)\n\t"
      "movw $1, 0x3c(%%ebx)\n\t"
      "jmp .LFUN_000f1710_36\n\t"
      ".LFUN_000f1710_35:\n\t"
      "movzbw 0x1(%%edx), %%ax\n\t"
      "movw %%ax, 0x50(%%ecx)\n\t"
      "movw $0, 0x3c(%%ebx)\n\t"
      ".LFUN_000f1710_36:\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "movl -0xc(%%ebp), %%esi\n\t"
      "addl $3, %%eax\n\t"
      "addl $4, %%esi\n\t"
      "cmpl $0x288901, %%eax\n\t"
      "movl %%esi, -0xc(%%ebp)\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "jl .LFUN_000f1710_20\n\t"
      "movl -0x1c(%%ebp), %%edx\n\t"
      "movl -0x20(%%ebp), %%eax\n\t"
      "movl -0x24(%%ebp), %%ecx\n\t"
      "pushl $0xc\n\t"
      "movl %%edx, -0x40(%%ebp)\n\t"
      "leal -0x34(%%ebp), %%edx\n\t"
      "pushl $-1\n\t"
      "pushl %%edx\n\t"
      "movl %%eax, -0x3c(%%ebp)\n\t"
      "movl %%ecx, -0x38(%%ebp)\n\t"
      "call *%[memset]\n\t"
      "movl -0x28(%%ebp), %%edi\n\t"
      "addl $0xc, %%esp\n\t"
      "xorl %%esi, %%esi\n\t"
      "xorl %%ebx, %%ebx\n\t"
      ".LFUN_000f1710_37:\n\t"
      "leal -0x40(%%edi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_000f1710_39\n\t"
      "movb (%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jl .LFUN_000f1710_39\n\t"
      "cmpb $4, %%al\n\t"
      "jge .LFUN_000f1710_39\n\t"
      "movsbw %%al, %%cx\n\t"
      "cmpw -0x18(%%ebp), %%cx\n\t"
      "je .LFUN_000f1710_39\n\t"
      "cmpl $3, %%ebx\n\t"
      "jl .LFUN_000f1710_38\n\t"
      "pushl $1\n\t"
      "pushl $0x4d4\n\t"
      "pushl $0x288938\n\t"
      "pushl $0x288e0c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000f1710_38:\n\t"
      "movl %%esi, -0x34(%%ebp,%%ebx,4)\n\t"
      "incl %%ebx\n\t"
      ".LFUN_000f1710_39:\n\t"
      "incl %%esi\n\t"
      "addl $0x44, %%edi\n\t"
      "cmpl $4, %%esi\n\t"
      "jl .LFUN_000f1710_37\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "movl %%ebx, -0x14(%%ebp)\n\t"
      "jmp .LFUN_000f1710_41\n\t"
      ".LFUN_000f1710_40:\n\t"
      "movl -0x14(%%ebp), %%ebx\n\t"
      ".LFUN_000f1710_41:\n\t"
      "movl -0x40(%%ebp,%%ebx,1), %%esi\n\t"
      "movl (%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x44654c61\n\t"
      "call *%[tag]\n\t"
      "movl 0x3e0(%%eax), %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $6, %%ecx\n\t"
      "je .LFUN_000f1710_42\n\t"
      "pushl $1\n\t"
      "pushl $0x4dd\n\t"
      "pushl $0x288938\n\t"
      "pushl $0x288f28\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000f1710_42:\n\t"
      "cmpl $-1, -0x34(%%ebp,%%ebx,1)\n\t"
      "movl 0x34(%%esi), %%eax\n\t"
      "movl 0x2c(%%eax), %%esi\n\t"
      "jne .LFUN_000f1710_45\n\t"
      "pushl $0x4e7\n\t"
      "pushl $0x288938\n\t"
      "movw $0, 0x50(%%eax)\n\t"
      "movl 0x3c(%%esi), %%eax\n\t"
      "pushl $2\n\t"
      "pushl %%eax\n\t"
      "call *%[uirealloc]\n\t"
      "addl $0x10, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%eax, 0x3c(%%esi)\n\t"
      "je .LFUN_000f1710_43\n\t"
      "movw $0, (%%eax)\n\t"
      ".LFUN_000f1710_43:\n\t"
      "movl 0x2c(%%esi), %%esi\n\t"
      "xorl %%eax, %%eax\n\t"
      ".LFUN_000f1710_44:\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_000f1710_56\n\t"
      "incl %%eax\n\t"
      "cmpl $4, %%eax\n\t"
      "movw $2, 0x50(%%esi)\n\t"
      "movl 0x2c(%%esi), %%esi\n\t"
      "jl .LFUN_000f1710_44\n\t"
      "jmp .LFUN_000f1710_56\n\t"
      ".LFUN_000f1710_45:\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "movw $1, 0x50(%%eax)\n\t"
      "movl -0x34(%%ebp,%%ebx,1), %%ecx\n\t"
      "imull $0x44, %%ecx, %%ecx\n\t"
      "leal 0x114(%%ecx,%%edx,1), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[xulen]\n\t"
      "movl 0x3c(%%esi), %%edx\n\t"
      "pushl $0x4f4\n\t"
      "movl %%eax, %%edi\n\t"
      "pushl $0x288938\n\t"
      "leal 0x2(%%edi,%%edi,1), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[uirealloc]\n\t"
      "addl $0x14, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%eax, 0x3c(%%esi)\n\t"
      "je .LFUN_000f1710_46\n\t"
      "movl -0x34(%%ebp,%%ebx,1), %%ecx\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "imull $0x44, %%ecx, %%ecx\n\t"
      "pushl %%edi\n\t"
      "leal 0x114(%%ecx,%%edx,1), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "call *%[xucpy]\n\t"
      "movl 0x3c(%%esi), %%edx\n\t"
      "addl $0xc, %%esp\n\t"
      "movw $0, (%%edx,%%edi,2)\n\t"
      ".LFUN_000f1710_46:\n\t"
      "pushl $0x10\n\t"
      "leal -0x54(%%ebp), %%eax\n\t"
      "pushl $-1\n\t"
      "pushl %%eax\n\t"
      "call *%[memset]\n\t"
      "movl -0x8(%%ebp), %%edi\n\t"
      "addl $0xc, %%esp\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "addl $0x242, %%edi\n\t"
      ".LFUN_000f1710_47:\n\t"
      "leal -0x1c(%%edi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[npval]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000f1710_48\n\t"
      "movl -0x14(%%ebp), %%edx\n\t"
      "movl -0x34(%%ebp,%%edx,1), %%eax\n\t"
      "movb (%%edi), %%cl\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "addl $5, %%eax\n\t"
      "imull $0x44, %%eax, %%eax\n\t"
      "cmpb (%%eax,%%edx,1), %%cl\n\t"
      "jne .LFUN_000f1710_48\n\t"
      "movsbl 0x1(%%edi), %%eax\n\t"
      "movl %%ebx, -0x54(%%ebp,%%eax,4)\n\t"
      ".LFUN_000f1710_48:\n\t"
      "incl %%ebx\n\t"
      "addl $0x20, %%edi\n\t"
      "cmpl $0x10, %%ebx\n\t"
      "jl .LFUN_000f1710_47\n\t"
      "movl 0x2c(%%esi), %%eax\n\t"
      "movl $0x2888f4, %%edx\n\t"
      "leal -0x54(%%ebp), %%edi\n\t"
      ".LFUN_000f1710_49:\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_000f1710_56\n\t"
      "movl (%%edi), %%ecx\n\t"
      "cmpl $-1, %%ecx\n\t"
      "jne .LFUN_000f1710_50\n\t"
      "movw $2, 0x50(%%eax)\n\t"
      "jmp .LFUN_000f1710_55\n\t"
      ".LFUN_000f1710_50:\n\t"
      "movl -0x8(%%ebp), %%esi\n\t"
      "movb 0xc0(%%esi), %%bl\n\t"
      "testb %%bl, %%bl\n\t"
      "jne .LFUN_000f1710_51\n\t"
      "movzbw (%%edx), %%cx\n\t"
      "jmp .LFUN_000f1710_54\n\t"
      ".LFUN_000f1710_51:\n\t"
      "shll $5, %%ecx\n\t"
      "movsbl 0x244(%%ecx,%%esi,1), %%ecx\n\t"
      "subl $0, %%ecx\n\t"
      "je .LFUN_000f1710_53\n\t"
      "decl %%ecx\n\t"
      "je .LFUN_000f1710_52\n\t"
      "movzbw (%%edx), %%cx\n\t"
      "jmp .LFUN_000f1710_54\n\t"
      ".LFUN_000f1710_52:\n\t"
      "movzbw 0x1(%%edx), %%cx\n\t"
      "jmp .LFUN_000f1710_54\n\t"
      ".LFUN_000f1710_53:\n\t"
      "movzbw 0x2(%%edx), %%cx\n\t"
      ".LFUN_000f1710_54:\n\t"
      "movw %%cx, 0x50(%%eax)\n\t"
      ".LFUN_000f1710_55:\n\t"
      "movl 0x2c(%%eax), %%eax\n\t"
      "addl $3, %%edx\n\t"
      "addl $4, %%edi\n\t"
      "cmpl $0x288900, %%edx\n\t"
      "jl .LFUN_000f1710_49\n\t"
      ".LFUN_000f1710_56:\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "addl $4, %%eax\n\t"
      "cmpl $0xc, %%eax\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "jl .LFUN_000f1710_40\n\t"
      "popl %%ebx\n\t"
      ".LFUN_000f1710_57:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [n2a0a0] "m"(f1710_n2a0a0), [tag] "m"(f1710_tag), [assert] "m"(f1710_assert), [exitfn] "m"(f1710_exitfn), [ngcli] "m"(f1710_ngcli), [n24c40] "m"(f1710_n24c40), [uirealloc] "m"(f1710_uirealloc), [n24d00] "m"(f1710_n24d00), [ngsrv] "m"(f1710_ngsrv), [xucpy] "m"(f1710_xucpy), [usprintf] "m"(f1710_usprintf), [ngmach] "m"(f1710_ngmach), [memset] "m"(f1710_memset), [npval] "m"(f1710_npval), [xulen] "m"(f1710_xulen), [wvis] "m"(f1710_wvis)
      : "memory");
}
#else
#error "FUN_000f1710: clang naked draft required"
#endif

/* network_pregame_status_screen_update (0xf1ed0) — XBE naked draft (batch 106). */
#if defined(__clang__)
static int (*const bf1ed0_c12a0a0)(void) = FUN_0012a0a0;
static void *(*const bf1ed0_tag)(int, int) = tag_get;
static void (*const bf1ed0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const bf1ed0_exitfn)(int) = system_exit;
static void * (*const bf1ed0_c12a240)(void) = network_game_client_get;
static uint16_t (*const bf1ed0_c124c40)(void *client) = FUN_00124c40;
static void * (*const bf1ed0_ce3d20)(int a1, unsigned short a2, const char *a3, unsigned int a4) = ui_widget_realloc;
static int16_t (*const bf1ed0_c124d00)(void *client) = FUN_00124d00;
static wchar_t * (*const bf1ed0_c19dc90)(wchar_t *dest, wchar_t *src, size_t count) = ustrncpy;
static void (*const bf1ed0_c19e9f0)(wchar_t *buffer, int buffer_size, const wchar_t *format, ...) = unicode_sprintf;
static void * (*const bf1ed0_c124c10)(void *client) = network_game_client_get_machine;
static void *(*const bf1ed0_memset)(void *, int, unsigned int) = csmemset;
static bool (*const bf1ed0_c12ac80)(void *client) = network_player_is_valid;
static int (*const bf1ed0_c19d8c0)(const unsigned short *s) = ustrlen;
static void (*const bf1ed0_ce4370)(void *widget, char visible) = widget_instance_set_visibility_recursive;

__attribute__((naked, noinline))
void network_pregame_status_screen_update(void *widget __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x38, %%esp\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c12a0a0]\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "movl %%eax, %%edi\n\t"
      "movl (%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x44654c61\n\t"
      "movl %%edi, -0xc(%%ebp)\n\t"
      "call *%[tag]\n\t"
      "movl 0x3e0(%%eax), %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $3, %%ecx\n\t"
      "je .Lnetwork_pregame_status_screen_update_1\n\t"
      "pushl $1\n\t"
      "pushl $0x550\n\t"
      "pushl $0x288938\n\t"
      "pushl $0x288f28\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lnetwork_pregame_status_screen_update_1:\n\t"
      "testl %%edi, %%edi\n\t"
      "je .Lnetwork_pregame_status_screen_update_30\n\t"
      "pushl %%ebx\n\t"
      "call *%[c12a240]\n\t"
      "pushl %%eax\n\t"
      "call *%[c124c40]\n\t"
      "movl 0x34(%%esi), %%ebx\n\t"
      "movl 0x2c(%%ebx), %%edi\n\t"
      "movl 0x2c(%%edi), %%esi\n\t"
      "movl 0x3c(%%esi), %%ecx\n\t"
      "pushl $0x55c\n\t"
      "pushl $0x288938\n\t"
      "pushl $0x20\n\t"
      "pushl %%ecx\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "movl %%ebx, -0x10(%%ebp)\n\t"
      "call *%[ce3d20]\n\t"
      "addl $0x14, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%eax, 0x3c(%%esi)\n\t"
      "je .Lnetwork_pregame_status_screen_update_9\n\t"
      "call *%[c12a240]\n\t"
      "pushl %%eax\n\t"
      "call *%[c124d00]\n\t"
      "movl 0x3c(%%esi), %%edx\n\t"
      "pushl $0xf\n\t"
      "pushl $0x288f1c\n\t"
      "pushl %%edx\n\t"
      "movl %%eax, %%ebx\n\t"
      "call *%[c19dc90]\n\t"
      "addl $0x10, %%esp\n\t"
      "testw %%bx, %%bx\n\t"
      "movb $1, 0x10(%%edi)\n\t"
      "movw $0, 0x40(%%edi)\n\t"
      "movb $1, 0x10(%%esi)\n\t"
      "jne .Lnetwork_pregame_status_screen_update_2\n\t"
      "movw $1, 0x40(%%edi)\n\t"
      "jmp .Lnetwork_pregame_status_screen_update_7\n\t"
      ".Lnetwork_pregame_status_screen_update_2:\n\t"
      "jle .Lnetwork_pregame_status_screen_update_5\n\t"
      "cmpw $0x3c, %%bx\n\t"
      "jge .Lnetwork_pregame_status_screen_update_3\n\t"
      "movl 0x3c(%%esi), %%ecx\n\t"
      "movswl %%bx, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x288f0c\n\t"
      "pushl $0xf\n\t"
      "pushl %%ecx\n\t"
      "call *%[c19e9f0]\n\t"
      "addl $0x10, %%esp\n\t"
      "jmp .Lnetwork_pregame_status_screen_update_8\n\t"
      ".Lnetwork_pregame_status_screen_update_3:\n\t"
      "cmpw $0xe10, %%bx\n\t"
      "movswl %%bx, %%ecx\n\t"
      "jge .Lnetwork_pregame_status_screen_update_4\n\t"
      "movl $0x88888889, %%eax\n\t"
      "imull %%ecx\n\t"
      "addl %%ecx, %%edx\n\t"
      "sarl $5, %%edx\n\t"
      "movl %%edx, %%eax\n\t"
      "shrl $0x1f, %%eax\n\t"
      "addl %%eax, %%edx\n\t"
      "movl %%edx, %%eax\n\t"
      "imull $0x3c, %%eax, %%eax\n\t"
      "subl %%eax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl 0x3c(%%esi), %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x288ef8\n\t"
      "pushl $0xf\n\t"
      "pushl %%ecx\n\t"
      "call *%[c19e9f0]\n\t"
      "addl $0x14, %%esp\n\t"
      "jmp .Lnetwork_pregame_status_screen_update_8\n\t"
      ".Lnetwork_pregame_status_screen_update_4:\n\t"
      "movl $0x91a2b3c5, %%eax\n\t"
      "imull %%ecx\n\t"
      "addl %%ecx, %%edx\n\t"
      "sarl $0xb, %%edx\n\t"
      "movl %%edx, %%eax\n\t"
      "shrl $0x1f, %%eax\n\t"
      "addl %%eax, %%edx\n\t"
      "movl %%edx, %%ebx\n\t"
      "imull $0xe10, %%edx, %%edx\n\t"
      "movl %%ecx, %%edi\n\t"
      "subl %%edx, %%edi\n\t"
      "movl $0x88888889, %%eax\n\t"
      "imull %%edi\n\t"
      "addl %%edi, %%edx\n\t"
      "sarl $5, %%edx\n\t"
      "movl %%edx, %%eax\n\t"
      "shrl $0x1f, %%eax\n\t"
      "addl %%eax, %%edx\n\t"
      "movl %%ebx, %%eax\n\t"
      "imull $0x3c, %%eax, %%eax\n\t"
      "addl %%edx, %%eax\n\t"
      "imull $0x3c, %%eax, %%eax\n\t"
      "subl %%eax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl 0x3c(%%esi), %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ebx\n\t"
      "pushl $0x288edc\n\t"
      "pushl $0xf\n\t"
      "pushl %%ecx\n\t"
      "call *%[c19e9f0]\n\t"
      "addl $0x18, %%esp\n\t"
      "jmp .Lnetwork_pregame_status_screen_update_8\n\t"
      ".Lnetwork_pregame_status_screen_update_5:\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "cmpw $2, 0x224(%%eax)\n\t"
      "jl .Lnetwork_pregame_status_screen_update_6\n\t"
      "cmpb $1, 0xc0(%%eax)\n\t"
      "jne .Lnetwork_pregame_status_screen_update_8\n\t"
      ".Lnetwork_pregame_status_screen_update_6:\n\t"
      "movb $0, 0x10(%%edi)\n\t"
      ".Lnetwork_pregame_status_screen_update_7:\n\t"
      "movb $0, 0x10(%%esi)\n\t"
      ".Lnetwork_pregame_status_screen_update_8:\n\t"
      "movl 0x3c(%%esi), %%edx\n\t"
      "movl -0x10(%%ebp), %%ebx\n\t"
      "movw $0, 0x1e(%%edx)\n\t"
      ".Lnetwork_pregame_status_screen_update_9:\n\t"
      "movl (%%ebx), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x44654c61\n\t"
      "call *%[tag]\n\t"
      "movl 0x3e0(%%eax), %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $6, %%ecx\n\t"
      "je .Lnetwork_pregame_status_screen_update_10\n\t"
      "pushl $1\n\t"
      "pushl $0x592\n\t"
      "pushl $0x288938\n\t"
      "pushl $0x288f28\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lnetwork_pregame_status_screen_update_10:\n\t"
      "movl 0x34(%%ebx), %%ebx\n\t"
      "movl -0xc(%%ebp), %%esi\n\t"
      "movl %%ebx, -0x8(%%ebp)\n\t"
      "movl 0x2c(%%ebx), %%ebx\n\t"
      "movl 0x2c(%%ebx), %%eax\n\t"
      "movl %%eax, -0x28(%%ebp)\n\t"
      "movl 0x2c(%%eax), %%eax\n\t"
      "movl %%eax, -0x24(%%ebp)\n\t"
      "movl 0x2c(%%eax), %%eax\n\t"
      "movl 0x2c(%%eax), %%ecx\n\t"
      "movl %%eax, -0x20(%%ebp)\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "movl $0x288ed8, -0x10(%%ebp)\n\t"
      "movl %%ebx, -0x18(%%ebp)\n\t"
      "movl %%ecx, -0x1c(%%ebp)\n\t"
      "xorl %%edx, %%edx\n\t"
      "leal 0x154(%%esi), %%eax\n\t"
      "leal (%%esp), %%esp\n\t"
      ".Lnetwork_pregame_status_screen_update_11:\n\t"
      "leal -0x40(%%eax), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .Lnetwork_pregame_status_screen_update_12\n\t"
      "movb (%%eax), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "jl .Lnetwork_pregame_status_screen_update_12\n\t"
      "cmpb $4, %%cl\n\t"
      "jge .Lnetwork_pregame_status_screen_update_12\n\t"
      "movsbw %%cl, %%cx\n\t"
      "cmpw -0x14(%%ebp), %%cx\n\t"
      "je .Lnetwork_pregame_status_screen_update_13\n\t"
      ".Lnetwork_pregame_status_screen_update_12:\n\t"
      "incl %%edx\n\t"
      "addl $0x44, %%eax\n\t"
      "cmpl $4, %%edx\n\t"
      "jl .Lnetwork_pregame_status_screen_update_11\n\t"
      "jmp .Lnetwork_pregame_status_screen_update_15\n\t"
      ".Lnetwork_pregame_status_screen_update_13:\n\t"
      "call *%[c12a240]\n\t"
      "pushl %%eax\n\t"
      "call *%[c124c10]\n\t"
      "addl $4, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lnetwork_pregame_status_screen_update_14\n\t"
      "cmpw $0, (%%eax)\n\t"
      "je .Lnetwork_pregame_status_screen_update_14\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      ".Lnetwork_pregame_status_screen_update_14:\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      ".Lnetwork_pregame_status_screen_update_15:\n\t"
      "pushl $0x10\n\t"
      "leal -0x38(%%ebp), %%edx\n\t"
      "pushl $-1\n\t"
      "pushl %%edx\n\t"
      "call *%[memset]\n\t"
      "addl $0xc, %%esp\n\t"
      "xorl %%edi, %%edi\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "addl $0x242, %%esi\n\t"
      ".Lnetwork_pregame_status_screen_update_16:\n\t"
      "leal -0x1c(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c12ac80]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lnetwork_pregame_status_screen_update_17\n\t"
      "movsbw (%%esi), %%cx\n\t"
      "cmpw -0x14(%%ebp), %%cx\n\t"
      "jne .Lnetwork_pregame_status_screen_update_17\n\t"
      "movsbl 0x1(%%esi), %%edx\n\t"
      "incl %%edi\n\t"
      "cmpl $4, %%edi\n\t"
      "movl %%ebx, -0x38(%%ebp,%%edx,4)\n\t"
      "je .Lnetwork_pregame_status_screen_update_18\n\t"
      ".Lnetwork_pregame_status_screen_update_17:\n\t"
      "incl %%ebx\n\t"
      "addl $0x20, %%esi\n\t"
      "cmpl $0x10, %%ebx\n\t"
      "jl .Lnetwork_pregame_status_screen_update_16\n\t"
      ".Lnetwork_pregame_status_screen_update_18:\n\t"
      "movl -0x10(%%ebp), %%ebx\n\t"
      "pushl %%ebx\n\t"
      "call *%[c19d8c0]\n\t"
      "movl -0x8(%%ebp), %%edi\n\t"
      "movl 0x3c(%%edi), %%ecx\n\t"
      "pushl $0x5c2\n\t"
      "movl %%eax, %%esi\n\t"
      "pushl $0x288938\n\t"
      "leal 0x2(%%esi,%%esi,1), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[ce3d20]\n\t"
      "addl $0x14, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%eax, 0x3c(%%edi)\n\t"
      "je .Lnetwork_pregame_status_screen_update_19\n\t"
      "pushl %%esi\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "call *%[c19dc90]\n\t"
      "movl 0x3c(%%edi), %%edx\n\t"
      "addl $0xc, %%esp\n\t"
      "movw $0, (%%edx,%%esi,2)\n\t"
      ".Lnetwork_pregame_status_screen_update_19:\n\t"
      "movb -0x1(%%ebp), %%cl\n\t"
      "xorl %%eax, %%eax\n\t"
      "testb %%cl, %%cl\n\t"
      "movl -0x18(%%ebp), %%ecx\n\t"
      "setne %%al\n\t"
      "movl $0x288902, -0x10(%%ebp)\n\t"
      "movl $0, -0x8(%%ebp)\n\t"
      "movw %%ax, 0x50(%%ecx)\n\t"
      ".Lnetwork_pregame_status_screen_update_20:\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "movl -0x28(%%ebp,%%edx,1), %%esi\n\t"
      "movl (%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x44654c61\n\t"
      "call *%[tag]\n\t"
      "movl 0x3e0(%%eax), %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $3, %%ecx\n\t"
      "je .Lnetwork_pregame_status_screen_update_21\n\t"
      "pushl $1\n\t"
      "pushl $0x5cc\n\t"
      "pushl $0x288938\n\t"
      "pushl $0x288f28\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lnetwork_pregame_status_screen_update_21:\n\t"
      "movl 0x34(%%esi), %%ebx\n\t"
      "movl -0xc(%%ebp), %%edi\n\t"
      "movl 0x2c(%%ebx), %%esi\n\t"
      "movb 0xc0(%%edi), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "movl 0x2c(%%esi), %%eax\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "jne .Lnetwork_pregame_status_screen_update_22\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "call *%[ce4370]\n\t"
      "addl $8, %%esp\n\t"
      ".Lnetwork_pregame_status_screen_update_22:\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movl -0x38(%%ebp,%%ecx,1), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "jne .Lnetwork_pregame_status_screen_update_24\n\t"
      "pushl $0x5db\n\t"
      "xorl %%edi, %%edi\n\t"
      "pushl $0x288938\n\t"
      "movw %%di, 0x50(%%ebx)\n\t"
      "movl 0x3c(%%esi), %%edx\n\t"
      "pushl $2\n\t"
      "pushl %%edx\n\t"
      "call *%[ce3d20]\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpl %%edi, %%eax\n\t"
      "movl %%eax, 0x3c(%%esi)\n\t"
      "je .Lnetwork_pregame_status_screen_update_23\n\t"
      "movw %%di, (%%eax)\n\t"
      ".Lnetwork_pregame_status_screen_update_23:\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "movw %%di, 0x3c(%%eax)\n\t"
      "jmp .Lnetwork_pregame_status_screen_update_29\n\t"
      ".Lnetwork_pregame_status_screen_update_24:\n\t"
      "shll $5, %%eax\n\t"
      "leal 0x226(%%eax,%%edi,1), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c19d8c0]\n\t"
      "movl %%eax, %%edi\n\t"
      "movl 0x3c(%%esi), %%eax\n\t"
      "pushl $0x5e4\n\t"
      "pushl $0x288938\n\t"
      "leal 0x2(%%edi,%%edi,1), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[ce3d20]\n\t"
      "addl $0x14, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%eax, 0x3c(%%esi)\n\t"
      "je .Lnetwork_pregame_status_screen_update_25\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movl -0x38(%%ebp,%%ecx,1), %%edx\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "shll $5, %%edx\n\t"
      "pushl %%edi\n\t"
      "leal 0x226(%%edx,%%ecx,1), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c19dc90]\n\t"
      "movl 0x3c(%%esi), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "movw $0, (%%eax,%%edi,2)\n\t"
      ".Lnetwork_pregame_status_screen_update_25:\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "movb 0xc0(%%eax), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "jne .Lnetwork_pregame_status_screen_update_26\n\t"
      "movw $1, 0x50(%%ebx)\n\t"
      "jmp .Lnetwork_pregame_status_screen_update_29\n\t"
      ".Lnetwork_pregame_status_screen_update_26:\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movl -0x38(%%ebp,%%ecx,1), %%edx\n\t"
      "shll $5, %%edx\n\t"
      "movsbl 0x244(%%edx,%%eax,1), %%eax\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "subl %%ecx, %%eax\n\t"
      "je .Lnetwork_pregame_status_screen_update_28\n\t"
      "decl %%eax\n\t"
      "je .Lnetwork_pregame_status_screen_update_27\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "movzbw -0x2(%%eax), %%dx\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "movw %%dx, 0x50(%%ebx)\n\t"
      "movw %%cx, 0x3c(%%eax)\n\t"
      "jmp .Lnetwork_pregame_status_screen_update_29\n\t"
      ".Lnetwork_pregame_status_screen_update_27:\n\t"
      "movl -0x10(%%ebp), %%ecx\n\t"
      "movzbw (%%ecx), %%dx\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "movw %%dx, 0x50(%%ebx)\n\t"
      "movw $1, 0x3c(%%eax)\n\t"
      "jmp .Lnetwork_pregame_status_screen_update_29\n\t"
      ".Lnetwork_pregame_status_screen_update_28:\n\t"
      "movl -0x10(%%ebp), %%edx\n\t"
      "movzbw -0x1(%%edx), %%ax\n\t"
      "movl -0x14(%%ebp), %%edx\n\t"
      "movw %%ax, 0x50(%%ebx)\n\t"
      "movw %%cx, 0x3c(%%edx)\n\t"
      ".Lnetwork_pregame_status_screen_update_29:\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "movl -0x8(%%ebp), %%esi\n\t"
      "addl $3, %%eax\n\t"
      "addl $4, %%esi\n\t"
      "cmpl $0x28890e, %%eax\n\t"
      "movl %%esi, -0x8(%%ebp)\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "jl .Lnetwork_pregame_status_screen_update_20\n\t"
      "popl %%ebx\n\t"
      ".Lnetwork_pregame_status_screen_update_30:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c12a0a0] "m"(bf1ed0_c12a0a0), [tag] "m"(bf1ed0_tag), [assert] "m"(bf1ed0_assert), [exitfn] "m"(bf1ed0_exitfn), [c12a240] "m"(bf1ed0_c12a240), [c124c40] "m"(bf1ed0_c124c40), [ce3d20] "m"(bf1ed0_ce3d20), [c124d00] "m"(bf1ed0_c124d00), [c19dc90] "m"(bf1ed0_c19dc90), [c19e9f0] "m"(bf1ed0_c19e9f0), [c124c10] "m"(bf1ed0_c124c10), [memset] "m"(bf1ed0_memset), [c12ac80] "m"(bf1ed0_c12ac80), [c19d8c0] "m"(bf1ed0_c19d8c0), [ce4370] "m"(bf1ed0_ce4370)
      : "memory");
}
#else
#error "network_pregame_status_screen_update: clang naked draft required"
#endif


/* FUN_000f2390 (0xf2390) — XBE naked draft (batch 129). */
#if defined(__clang__)
static void * (*const bf2390_c12a240)(void) = network_game_client_get;
static int16_t (*const bf2390_c124a30)(void *server, void *out_param) = network_game_client_get_state;
static int (*const bf2390_c12a0a0)(void) = FUN_0012a0a0;
static void (*const bf2390_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const bf2390_exitfn)(int) = system_exit;
static void (*const bf2390_ce0890)(void) = player_ui_local_player_wants_to_play_multiplayer;
static bool (*const bf2390_c12ac80)(void *client) = network_player_is_valid;
static bool (*const bf2390_c12a0d0)(void *player) = network_game_player_is_local;
static char (*const bf2390_c1258a0)(void *client, int16_t local_player_index) = network_game_client_add_player;
static void (*const bf2390_c12b650)(const char *fmt, ...) = network_game_log;

__attribute__((naked, noinline))
void FUN_000f2390(void *widget __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $8, %%esp\n\t"
      "pushl %%edi\n\t"
      "call *%[c12a240]\n\t"
      "movl %%eax, %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "je .LFUN_000f2390_9\n\t"
      "leal -0x4(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "call *%[c124a30]\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $2, %%ax\n\t"
      "jne .LFUN_000f2390_9\n\t"
      "pushl %%esi\n\t"
      "call *%[c12a0a0]\n\t"
      "movl %%eax, %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LFUN_000f2390_1\n\t"
      "pushl $1\n\t"
      "pushl $0x614\n\t"
      "pushl $0x288938\n\t"
      "pushl $0x2861a8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000f2390_1:\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movl %%ecx, -0x4(%%ebp)\n\t"
      "movl %%edi, %%edi\n\t"
      ".LFUN_000f2390_2:\n\t"
      "pushl %%ecx\n\t"
      "call *%[ce0890]\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "addl $4, %%esp\n\t"
      "movswl %%cx, %%edx\n\t"
      "incl %%ecx\n\t"
      "cmpw $4, %%cx\n\t"
      "movb %%al, -0x8(%%ebp,%%edx,1)\n\t"
      "movl %%ecx, -0x4(%%ebp)\n\t"
      "jl .LFUN_000f2390_2\n\t"
      "xorl %%eax, %%eax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      ".LFUN_000f2390_3:\n\t"
      "movswl %%ax, %%eax\n\t"
      "shll $5, %%eax\n\t"
      "leal 0x226(%%eax,%%esi,1), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c12ac80]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000f2390_4\n\t"
      "movswl -0x4(%%ebp), %%edx\n\t"
      "shll $5, %%edx\n\t"
      "leal 0x226(%%edx,%%esi,1), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c12a0d0]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000f2390_4\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movswl %%ax, %%ecx\n\t"
      "shll $5, %%ecx\n\t"
      "movsbl 0x243(%%ecx,%%esi,1), %%edx\n\t"
      "movb $0, -0x8(%%ebp,%%edx,1)\n\t"
      "jmp .LFUN_000f2390_5\n\t"
      ".LFUN_000f2390_4:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      ".LFUN_000f2390_5:\n\t"
      "incl %%eax\n\t"
      "cmpw $0x10, %%ax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "jl .LFUN_000f2390_3\n\t"
      "xorl %%eax, %%eax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "popl %%esi\n\t"
      ".LFUN_000f2390_6:\n\t"
      "movswl %%ax, %%ecx\n\t"
      "movb -0x8(%%ebp,%%ecx,1), %%dl\n\t"
      "testb %%dl, %%dl\n\t"
      "je .LFUN_000f2390_8\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "call *%[c1258a0]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_000f2390_7\n\t"
      "pushl $0x28618c\n\t"
      "call *%[c12b650]\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_000f2390_7:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      ".LFUN_000f2390_8:\n\t"
      "incl %%eax\n\t"
      "cmpw $4, %%ax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "jl .LFUN_000f2390_6\n\t"
      ".LFUN_000f2390_9:\n\t"
      "popl %%edi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c12a240] "m"(bf2390_c12a240), [c124a30] "m"(bf2390_c124a30), [c12a0a0] "m"(bf2390_c12a0a0), [assert] "m"(bf2390_assert), [exitfn] "m"(bf2390_exitfn), [ce0890] "m"(bf2390_ce0890), [c12ac80] "m"(bf2390_c12ac80), [c12a0d0] "m"(bf2390_c12a0d0), [c1258a0] "m"(bf2390_c1258a0), [c12b650] "m"(bf2390_c12b650)
      : "memory");
}
#else
#error "FUN_000f2390: clang naked draft required"
#endif


/* 0xf24b0 */
void mutliplayer_settings_select_list_update_displayed_items(void *widget)
{
  int eax = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;

  /* test edi, edi -> je 0xf24ca */
  /* test eax, eax -> je 0xf24ca */
  /* test eax, eax -> jne 0xf24ea */
  display_assert((char *)0x00288a5c, (char *)0x00288938, 2102, 0);
  system_exit(0);
  /* test eax, eax -> je 0xf2508 */
  /* cmp eax, ecx -> je 0xf2502 */
  /* test eax, eax -> jne 0xf24f6 */
  /* cmp (int16_t)esi, -1 -> je 0xf2557 */
  tag_get('aLeD', 0);
  /* cmp ecx, 2 -> je 0xf2546 */
  display_assert((char *)0x00288f68, (char *)0x00288938, 2116, 0);
  system_exit(0);

  (void)eax;
  (void)ecx;
  (void)esi;
  (void)edi;
}

/* FUN_000f2560 (0xf2560) — XBE naked draft (batch 126). */
#if defined(__clang__)
static void (*const bf2560_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const bf2560_exitfn)(int) = system_exit;
static void *(*const bf2560_tag)(int, int) = tag_get;

__attribute__((naked, noinline))
void FUN_000f2560(void *widget __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "cmpw $3, 0xe(%%esi)\n\t"
      "pushl %%edi\n\t"
      "je .LFUN_000f2560_1\n\t"
      "pushl $1\n\t"
      "pushl $0x8f5\n\t"
      "pushl $0x288938\n\t"
      "pushl $0x2890bc\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000f2560_1:\n\t"
      "movl 0x48(%%esi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_000f2560_2\n\t"
      "cmpw $1, 0xe(%%eax)\n\t"
      "je .LFUN_000f2560_3\n\t"
      ".LFUN_000f2560_2:\n\t"
      "pushl $1\n\t"
      "pushl $0x8f8\n\t"
      "pushl $0x288938\n\t"
      "pushl $0x289070\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000f2560_3:\n\t"
      "movl (%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x44654c61\n\t"
      "call *%[tag]\n\t"
      "movl 0x3e0(%%eax), %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "testl %%ecx, %%ecx\n\t"
      "jg .LFUN_000f2560_4\n\t"
      "pushl $1\n\t"
      "pushl $0x8fe\n\t"
      "pushl $0x288938\n\t"
      "pushl $0x289034\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000f2560_4:\n\t"
      "movl 0x38(%%esi), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "movl 0x48(%%esi), %%eax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "je .LFUN_000f2560_11\n\t"
      "movl 0x34(%%esi), %%edi\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "testl %%edi, %%edi\n\t"
      "je .LFUN_000f2560_10\n\t"
      "nop\n\t"
      ".LFUN_000f2560_5:\n\t"
      "movl 0x34(%%edi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_000f2560_7\n\t"
      ".LFUN_000f2560_6:\n\t"
      "cmpw $2, 0xe(%%esi)\n\t"
      "je .LFUN_000f2560_8\n\t"
      "movl 0x2c(%%esi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LFUN_000f2560_6\n\t"
      ".LFUN_000f2560_7:\n\t"
      "pushl $1\n\t"
      "pushl $0x90c\n\t"
      "pushl $0x288938\n\t"
      "pushl $0x288fd8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000f2560_8:\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "cmpl 0x38(%%ecx), %%edi\n\t"
      "je .LFUN_000f2560_9\n\t"
      "movzwl 0x44(%%esi), %%edx\n\t"
      "movl 0x2c(%%edi), %%edi\n\t"
      "addl %%edx, %%ebx\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .LFUN_000f2560_5\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movw %%bx, 0x40(%%eax)\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000f2560_9:\n\t"
      "movswl 0x3c(%%esi), %%ecx\n\t"
      "addl %%ecx, %%ebx\n\t"
      ".LFUN_000f2560_10:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movw %%bx, 0x40(%%eax)\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000f2560_11:\n\t"
      "movw 0x8(%%ebp), %%dx\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movw %%dx, 0x40(%%eax)\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(bf2560_assert), [exitfn] "m"(bf2560_exitfn), [tag] "m"(bf2560_tag)
      : "memory");
}
#else
#error "FUN_000f2560: clang naked draft required"
#endif


/* 0xf2690 */
void FUN_000f2690(void *widget)
{
  int eax = 0;
  int ebx = 0;
  int esi = 0;
  int edi = 0;

  hud_messaging_get_objective();
  /* test ebx, ebx -> je 0xf26b4 */
  /* relift: cmp word ptr [ebx], 0 -> je 0xf26b4 */
  ustrlen((void *)(uintptr_t)ebx);
  /* relift: cmp word ptr [edi + 0xe], 1 -> je 0xf26e0 */
  display_assert((char *)0x002890f4, (char *)0x00288938, 2340, 0);
  system_exit(0);
  /* test esi, esi -> jle 0xf271a */
  ui_widget_realloc(0, 0, (char *)0x00288938, 2344);
  ustrncpy((wchar_t *)(uintptr_t)eax, (wchar_t *)(uintptr_t)ebx, esi);

  (void)eax;
  (void)ebx;
  (void)esi;
  (void)edi;
}

/* FUN_000f2720 (0xf2720) — XBE naked draft (batch 126). */
#if defined(__clang__)
static void (*const bf2720_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const bf2720_exitfn)(int) = system_exit;
static void *(*const bf2720_tag)(int, int) = tag_get;

__attribute__((naked, noinline))
void FUN_000f2720(void *widget __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "cmpw $3, 0xe(%%esi)\n\t"
      "pushl %%edi\n\t"
      "je .LFUN_000f2720_1\n\t"
      "pushl $1\n\t"
      "pushl $0x980\n\t"
      "pushl $0x288938\n\t"
      "pushl $0x28919c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000f2720_1:\n\t"
      "movl 0x48(%%esi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_000f2720_2\n\t"
      "cmpw $0, 0xe(%%eax)\n\t"
      "je .LFUN_000f2720_3\n\t"
      ".LFUN_000f2720_2:\n\t"
      "pushl $1\n\t"
      "pushl $0x983\n\t"
      "pushl $0x288938\n\t"
      "pushl $0x289150\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000f2720_3:\n\t"
      "movl (%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x44654c61\n\t"
      "call *%[tag]\n\t"
      "movl 0x3e0(%%eax), %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "testl %%ecx, %%ecx\n\t"
      "jg .LFUN_000f2720_4\n\t"
      "pushl $1\n\t"
      "pushl $0x988\n\t"
      "pushl $0x288938\n\t"
      "pushl $0x28911c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000f2720_4:\n\t"
      "movl 0x38(%%esi), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "movl 0x48(%%esi), %%eax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "je .LFUN_000f2720_11\n\t"
      "movl 0x34(%%esi), %%edi\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "testl %%edi, %%edi\n\t"
      "je .LFUN_000f2720_10\n\t"
      "nop\n\t"
      ".LFUN_000f2720_5:\n\t"
      "movl 0x34(%%edi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_000f2720_7\n\t"
      ".LFUN_000f2720_6:\n\t"
      "cmpw $2, 0xe(%%esi)\n\t"
      "je .LFUN_000f2720_8\n\t"
      "movl 0x2c(%%esi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LFUN_000f2720_6\n\t"
      ".LFUN_000f2720_7:\n\t"
      "pushl $1\n\t"
      "pushl $0x996\n\t"
      "pushl $0x288938\n\t"
      "pushl $0x288fd8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000f2720_8:\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "cmpl 0x38(%%ecx), %%edi\n\t"
      "je .LFUN_000f2720_9\n\t"
      "movzwl 0x44(%%esi), %%edx\n\t"
      "movl 0x2c(%%edi), %%edi\n\t"
      "addl %%edx, %%ebx\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .LFUN_000f2720_5\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movw %%bx, 0x50(%%eax)\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000f2720_9:\n\t"
      "movswl 0x3c(%%esi), %%ecx\n\t"
      "addl %%ecx, %%ebx\n\t"
      ".LFUN_000f2720_10:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movw %%bx, 0x50(%%eax)\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000f2720_11:\n\t"
      "movw 0x8(%%ebp), %%dx\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movw %%dx, 0x50(%%eax)\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(bf2720_assert), [exitfn] "m"(bf2720_exitfn), [tag] "m"(bf2720_tag)
      : "memory");
}
#else
#error "FUN_000f2720: clang naked draft required"
#endif


/* 0xf2850 */
void FUN_000f2850(void *widget)
{
  int eax = 0;
  int esi = 0;

  /* relift: cmp word ptr [esi + 0xe], 3 -> je 0xf287e */
  display_assert((char *)0x00289218, (char *)0x00288938, 2475, 0);
  system_exit(0);
  /* test eax, eax -> je 0xf288c */
  /* relift: cmp word ptr [eax + 0xe], 0 -> je 0xf28ac */
  display_assert((char *)0x002891c8, (char *)0x00288938, 2478, 0);
  system_exit(0);
  /* test (int16_t)eax, (int16_t)eax -> jge 0xf28cc */

  (void)eax;
  (void)esi;
}

/* 0xf28e0 */
void FUN_000f28e0(void *widget)
{
  int eax = 0;
  int ecx = 0;
  int esi = 0;

  /* relift: cmp word ptr [esi + 0xe], 1 -> je 0xf2911 */
  display_assert((char *)0x00289284, (char *)0x00288938, 2540, 0);
  system_exit(0);
  /* test (int16_t)eax, (int16_t)eax -> jl 0xf2920 */
  /* cmp (int16_t)eax, 4 -> jl 0xf2940 */
  display_assert((char *)0x00289248, (char *)0x00288938, 2542, 0);
  system_exit(0);
  player_ui_get_active_player_profile();
  ui_widget_realloc(0, 24, (char *)0x00288938, 2544);
  ustrncpy((wchar_t *)(uintptr_t)eax, (wchar_t *)(uintptr_t)ecx, 11);

  (void)eax;
  (void)ecx;
  (void)esi;
}

/* 0xf2990 */
void FUN_000f2990(void *widget)
{
  int eax = 0;
  int edi = 0;

  display_assert((char *)0x00289284, (char *)0x00288938, 2558, 0);
  system_exit(0);
  /* test (int16_t)eax, (int16_t)eax -> jl 0xf29ce */
  /* cmp (int16_t)eax, 4 -> jl 0xf29ee */
  display_assert((char *)0x00289248, (char *)0x00288938, 2560, 0);
  system_exit(0);
  player_ui_get_edit_player_profile();
  /* test edi, edi -> je 0xf2a2d */
  ui_widget_realloc(0, 24, (char *)0x00288938, 2564);
  ustrncpy((wchar_t *)(uintptr_t)eax, (wchar_t *)(uintptr_t)edi, 11);

  (void)eax;
  (void)edi;
}

/* 0xf2a40 */
void FUN_000f2a40(void *widget)
{
  int eax = 0;
  int edi = 0;

  display_assert((char *)0x00289284, (char *)0x00288938, 2579, 0);
  system_exit(0);
  /* test (int16_t)eax, (int16_t)eax -> jl 0xf2a7e */
  /* cmp (int16_t)eax, 4 -> jl 0xf2a9e */
  display_assert((char *)0x00289248, (char *)0x00288938, 2581, 0);
  system_exit(0);
  player_ui_get_edit_playlist_profile();
  /* test edi, edi -> je 0xf2ae1 */
  ui_widget_realloc(0, 24, (char *)0x00288938, 2585);
  ustrncpy((wchar_t *)(uintptr_t)eax, (wchar_t *)(uintptr_t)edi, 11);
  error(0, (char *)0x002892b8);

  (void)eax;
  (void)edi;
}

/* 0xf2b00 */
void FUN_000f2b00(void *widget)
{
  int edx = 0;
  int edi = 0;

  /* test (int16_t)eax, (int16_t)eax -> jl 0xf2b19 */
  /* cmp (int16_t)eax, 4 -> jl 0xf2b39 */
  display_assert((char *)0x002892e0, (char *)0x00288938, 2605, 0);
  system_exit(0);
  player_ui_get_active_player_profile();
  /* test (int16_t)eax, (int16_t)eax -> jge 0xf2b60 */
  FUN_001c0ed0();
  /* cmp edi, edx -> jle 0xf2b84 */
  FUN_001c0ed0();

  (void)edx;
  (void)edi;
}

/* FUN_000f2b90 (0xf2b90) — XBE naked draft (batch 116). */
#if defined(__clang__)
static void (*const bf2b90_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const bf2b90_exitfn)(int) = system_exit;
static int (*const bf2b90_c12a0a0)(void) = FUN_0012a0a0;
static char * (*const bf2b90_c1d9690)(const char *haystack, const char *needle) = crt_strstr;
static void (*const bf2b90_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;

__attribute__((naked, noinline))
void FUN_000f2b90(void *widget __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "cmpw $1, 0xe(%%edi)\n\t"
      "je .LFUN_000f2b90_1\n\t"
      "pushl $1\n\t"
      "pushl $0xa39\n\t"
      "pushl $0x288938\n\t"
      "pushl $0x28932c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000f2b90_1:\n\t"
      "call *%[c12a0a0]\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_000f2b90_14\n\t"
      "leal 0x24(%%eax), %%esi\n\t"
      "pushl $0x288c70\n\t"
      "pushl %%esi\n\t"
      "call *%[c1d9690]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_000f2b90_2\n\t"
      "movw $0, 0x40(%%edi)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000f2b90_2:\n\t"
      "pushl $0x288c64\n\t"
      "pushl %%esi\n\t"
      "call *%[c1d9690]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_000f2b90_3\n\t"
      "movw $1, 0x40(%%edi)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000f2b90_3:\n\t"
      "pushl $0x288c58\n\t"
      "pushl %%esi\n\t"
      "call *%[c1d9690]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_000f2b90_4\n\t"
      "movw $2, 0x40(%%edi)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000f2b90_4:\n\t"
      "pushl $0x288c50\n\t"
      "pushl %%esi\n\t"
      "call *%[c1d9690]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_000f2b90_5\n\t"
      "movw $3, 0x40(%%edi)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000f2b90_5:\n\t"
      "pushl $0x288c44\n\t"
      "pushl %%esi\n\t"
      "call *%[c1d9690]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_000f2b90_6\n\t"
      "movw $4, 0x40(%%edi)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000f2b90_6:\n\t"
      "pushl $0x288c38\n\t"
      "pushl %%esi\n\t"
      "call *%[c1d9690]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_000f2b90_7\n\t"
      "movw $5, 0x40(%%edi)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000f2b90_7:\n\t"
      "pushl $0x288c2c\n\t"
      "pushl %%esi\n\t"
      "call *%[c1d9690]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_000f2b90_8\n\t"
      "movw $6, 0x40(%%edi)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000f2b90_8:\n\t"
      "pushl $0x288c20\n\t"
      "pushl %%esi\n\t"
      "call *%[c1d9690]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_000f2b90_9\n\t"
      "movw $7, 0x40(%%edi)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000f2b90_9:\n\t"
      "pushl $0x288c10\n\t"
      "pushl %%esi\n\t"
      "call *%[c1d9690]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_000f2b90_10\n\t"
      "movw $8, 0x40(%%edi)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000f2b90_10:\n\t"
      "pushl $0x288c04\n\t"
      "pushl %%esi\n\t"
      "call *%[c1d9690]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_000f2b90_11\n\t"
      "movw $9, 0x40(%%edi)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000f2b90_11:\n\t"
      "pushl $0x288bfc\n\t"
      "pushl %%esi\n\t"
      "call *%[c1d9690]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_000f2b90_12\n\t"
      "movw $0xa, 0x40(%%edi)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000f2b90_12:\n\t"
      "pushl $0x288bf4\n\t"
      "pushl %%esi\n\t"
      "call *%[c1d9690]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_000f2b90_13\n\t"
      "movw $0xb, 0x40(%%edi)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000f2b90_13:\n\t"
      "pushl $0x288bec\n\t"
      "pushl %%esi\n\t"
      "call *%[c1d9690]\n\t"
      "addl $8, %%esp\n\t"
      "negl %%eax\n\t"
      "sbbl %%eax, %%eax\n\t"
      "addl $0xd, %%eax\n\t"
      "movw %%ax, 0x40(%%edi)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000f2b90_14:\n\t"
      "pushl $0x28931c\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(bf2b90_assert), [exitfn] "m"(bf2b90_exitfn), [c12a0a0] "m"(bf2b90_c12a0a0), [c1d9690] "m"(bf2b90_c1d9690), [c8f390] "m"(bf2b90_c8f390)
      : "memory");
}
#else
#error "FUN_000f2b90: clang naked draft required"
#endif


/* FUN_000f2d50 (0xf2d50) — XBE naked draft (batch 129). */
#if defined(__clang__)
static void (*const bf2d50_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const bf2d50_exitfn)(int) = system_exit;
static int (*const bf2d50_c12a0a0)(void) = FUN_0012a0a0;
static void (*const bf2d50_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;

__attribute__((naked, noinline))
void FUN_000f2d50(void *widget __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "cmpw $1, 0xe(%%esi)\n\t"
      "je .LFUN_000f2d50_1\n\t"
      "pushl $1\n\t"
      "pushl $0xa59\n\t"
      "pushl $0x288938\n\t"
      "pushl $0x28932c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000f2d50_1:\n\t"
      "call *%[c12a0a0]\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_000f2d50_12\n\t"
      "movl 0xbc(%%eax), %%ecx\n\t"
      "decl %%ecx\n\t"
      "cmpl $4, %%ecx\n\t"
      "ja .LFUN_000f2d50_11\n\t"
      "jmp *.LFUN_000f2d50_jt(,%%ecx,4)\n\t"
      ".LFUN_000f2d50_2:\n\t"
      "cmpb $1, 0xf0(%%eax)\n\t"
      "jne .LFUN_000f2d50_3\n\t"
      "movl 0xf4(%%eax), %%eax\n\t"
      "negl %%eax\n\t"
      "sbbl %%eax, %%eax\n\t"
      "addl $0x1d, %%eax\n\t"
      "movw %%ax, 0x40(%%esi)\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000f2d50_3:\n\t"
      "movl 0xf4(%%eax), %%ecx\n\t"
      "negl %%ecx\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "andl $0x1b, %%ecx\n\t"
      "addl $3, %%ecx\n\t"
      "movw %%cx, 0x40(%%esi)\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000f2d50_4:\n\t"
      "movw $4, 0x40(%%esi)\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000f2d50_5:\n\t"
      "movl 0x100(%%eax), %%eax\n\t"
      "decl %%eax\n\t"
      "je .LFUN_000f2d50_7\n\t"
      "decl %%eax\n\t"
      "je .LFUN_000f2d50_6\n\t"
      "movw $5, 0x40(%%esi)\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000f2d50_6:\n\t"
      "movw $0x20, 0x40(%%esi)\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000f2d50_7:\n\t"
      "movw $0x1f, 0x40(%%esi)\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000f2d50_8:\n\t"
      "movw $6, 0x40(%%esi)\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000f2d50_9:\n\t"
      "movl 0xf0(%%eax), %%eax\n\t"
      "subl $2, %%eax\n\t"
      "je .LFUN_000f2d50_10\n\t"
      "movw $7, 0x40(%%esi)\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000f2d50_10:\n\t"
      "movw $0x21, 0x40(%%esi)\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000f2d50_11:\n\t"
      "movw $8, 0x40(%%esi)\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000f2d50_12:\n\t"
      "pushl $0x28931c\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_000f2d50_jt:\n\t"
      ".long .LFUN_000f2d50_2\n\t"
      ".long .LFUN_000f2d50_4\n\t"
      ".long .LFUN_000f2d50_5\n\t"
      ".long .LFUN_000f2d50_8\n\t"
      ".long .LFUN_000f2d50_9\n\t"
      ".text\n\t"
      :
      : [assert] "m"(bf2d50_assert), [exitfn] "m"(bf2d50_exitfn), [c12a0a0] "m"(bf2d50_c12a0a0), [c8f390] "m"(bf2d50_c8f390)
      : "memory");
}
#else
#error "FUN_000f2d50: clang naked draft required"
#endif


/* 0xf2e60 */
void FUN_000f2e60(void *widget)
{
  int eax = 0;
  int esi = 0;

  /* relift: cmp word ptr [esi + 0xe], 1 -> je 0xf2e8e */
  display_assert((char *)0x0028932c, (char *)0x00288938, 2730, 0);
  system_exit(0);
  FUN_0012a0a0();
  /* test eax, eax -> je 0xf2eaf */
  error(0, (char *)0x0028931c);

  (void)eax;
  (void)esi;
}

/* 0xf2ed0 */
void FUN_000f2ed0(void *widget)
{
  int eax = 0;
  int edi = 0;

  display_assert((char *)0x0028932c, (char *)0x00288938, 2755, 0);
  system_exit(0);
  FUN_0012a0a0();
  /* test edi, edi -> je 0xf2f4d */
  ui_widget_realloc(0, 16, (char *)0x00288938, 2760);
  unicode_sprintf((wchar_t *)(uintptr_t)eax, 0, (wchar_t *)0x0026c118);
  error(0, (char *)0x0028931c);

  (void)eax;
  (void)edi;
}

/* 0xf2f60 */
void FUN_000f2f60(void *widget)
{
  int eax = 0;
  int ecx = 0;
  int esi = 0;

  /* relift: cmp word ptr [esi + 0xe], 1 -> je 0xf2f8e */
  display_assert((char *)0x0028932c, (char *)0x00288938, 2780, 0);
  system_exit(0);
  FUN_0012a0a0();
  /* test eax, eax -> je 0xf2fe6 */
  /* cmp ecx, 4 -> ja 0xf2fb3 */
  error(0, (char *)0x0028931c);

  (void)eax;
  (void)ecx;
  (void)esi;
}

/* solo_game_objective_text (0xf3010) — XBE naked draft (batch 116). */
#if defined(__clang__)
static void (*const bf3010_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const bf3010_exitfn)(int) = system_exit;
static int (*const bf3010_c12a0a0)(void) = FUN_0012a0a0;
static char * (*const bf3010_c1d9690)(const char *haystack, const char *needle) = crt_strstr;
static void (*const bf3010_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;

__attribute__((naked, noinline))
void solo_game_objective_text(void *widget __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "cmpw $0, 0xe(%%edi)\n\t"
      "je .Lsolo_game_objective_text_1\n\t"
      "pushl $1\n\t"
      "pushl $0xb09\n\t"
      "pushl $0x288938\n\t"
      "pushl $0x289360\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lsolo_game_objective_text_1:\n\t"
      "call *%[c12a0a0]\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lsolo_game_objective_text_14\n\t"
      "leal 0x24(%%eax), %%esi\n\t"
      "pushl $0x288c70\n\t"
      "pushl %%esi\n\t"
      "call *%[c1d9690]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lsolo_game_objective_text_2\n\t"
      "movw $0, 0x50(%%edi)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lsolo_game_objective_text_2:\n\t"
      "pushl $0x288c64\n\t"
      "pushl %%esi\n\t"
      "call *%[c1d9690]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lsolo_game_objective_text_3\n\t"
      "movw $1, 0x50(%%edi)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lsolo_game_objective_text_3:\n\t"
      "pushl $0x288c58\n\t"
      "pushl %%esi\n\t"
      "call *%[c1d9690]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lsolo_game_objective_text_4\n\t"
      "movw $2, 0x50(%%edi)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lsolo_game_objective_text_4:\n\t"
      "pushl $0x288c50\n\t"
      "pushl %%esi\n\t"
      "call *%[c1d9690]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lsolo_game_objective_text_5\n\t"
      "movw $3, 0x50(%%edi)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lsolo_game_objective_text_5:\n\t"
      "pushl $0x288c44\n\t"
      "pushl %%esi\n\t"
      "call *%[c1d9690]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lsolo_game_objective_text_6\n\t"
      "movw $4, 0x50(%%edi)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lsolo_game_objective_text_6:\n\t"
      "pushl $0x288c38\n\t"
      "pushl %%esi\n\t"
      "call *%[c1d9690]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lsolo_game_objective_text_7\n\t"
      "movw $5, 0x50(%%edi)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lsolo_game_objective_text_7:\n\t"
      "pushl $0x288c2c\n\t"
      "pushl %%esi\n\t"
      "call *%[c1d9690]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lsolo_game_objective_text_8\n\t"
      "movw $6, 0x50(%%edi)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lsolo_game_objective_text_8:\n\t"
      "pushl $0x288c20\n\t"
      "pushl %%esi\n\t"
      "call *%[c1d9690]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lsolo_game_objective_text_9\n\t"
      "movw $7, 0x50(%%edi)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lsolo_game_objective_text_9:\n\t"
      "pushl $0x288c10\n\t"
      "pushl %%esi\n\t"
      "call *%[c1d9690]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lsolo_game_objective_text_10\n\t"
      "movw $8, 0x50(%%edi)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lsolo_game_objective_text_10:\n\t"
      "pushl $0x288c04\n\t"
      "pushl %%esi\n\t"
      "call *%[c1d9690]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lsolo_game_objective_text_11\n\t"
      "movw $9, 0x50(%%edi)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lsolo_game_objective_text_11:\n\t"
      "pushl $0x288bfc\n\t"
      "pushl %%esi\n\t"
      "call *%[c1d9690]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lsolo_game_objective_text_12\n\t"
      "movw $0xa, 0x50(%%edi)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lsolo_game_objective_text_12:\n\t"
      "pushl $0x288bf4\n\t"
      "pushl %%esi\n\t"
      "call *%[c1d9690]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lsolo_game_objective_text_13\n\t"
      "movw $0xb, 0x50(%%edi)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lsolo_game_objective_text_13:\n\t"
      "pushl $0x288bec\n\t"
      "pushl %%esi\n\t"
      "call *%[c1d9690]\n\t"
      "addl $8, %%esp\n\t"
      "negl %%eax\n\t"
      "sbbl %%eax, %%eax\n\t"
      "addl $0xd, %%eax\n\t"
      "movw %%ax, 0x50(%%edi)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lsolo_game_objective_text_14:\n\t"
      "pushl $0x28931c\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(bf3010_assert), [exitfn] "m"(bf3010_exitfn), [c12a0a0] "m"(bf3010_c12a0a0), [c1d9690] "m"(bf3010_c1d9690), [c8f390] "m"(bf3010_c8f390)
      : "memory");
}
#else
#error "solo_game_objective_text: clang naked draft required"
#endif


/* 0xf31d0 */
void color_picker_get_string(void *widget)
{
  int eax = 0;
  int esi = 0;

  /* relift: cmp word ptr [esi + 0xe], 0 -> je 0xf31fe */
  display_assert((char *)0x00289360, (char *)0x00288938, 2856, 0);
  system_exit(0);
  FUN_0012a0a0();
  /* test eax, eax -> je 0xf3250 */
  /* cmp eax, 4 -> ja 0xf3247 */
  error(0, (char *)0x0028931c);

  (void)eax;
  (void)esi;
}

/* 0xf3280 */
void FUN_000f3280(void *widget)
{
  int eax = 0;
  int edi = 0;

  display_assert((char *)0x0028932c, (char *)0x00288938, 2894, 0);
  system_exit(0);
  FUN_0012a0a0();
  /* test edi, edi -> je 0xf32fe */
  ui_widget_realloc(0, 0, (char *)0x00288938, 2902);
  unicode_sprintf((wchar_t *)(uintptr_t)eax, 0, (wchar_t *)0x0026c118);
  error(0, (char *)0x0028931c);

  (void)eax;
  (void)edi;
}

/* 0xf3320 */
void FUN_000f3320(void *widget)
{
  int eax = 0;
  int esi = 0;

  /* relift: cmp word ptr [esi + 0xe], 1 -> je 0xf334e */
  display_assert((char *)0x00289398, (char *)0x00288938, 2921, 0);
  system_exit(0);
  player_ui_get_edit_playlist_profile();
  /* test eax, eax -> je 0xf339d */
  /* cmp eax, 4 -> ja 0xf3394 */
  error(0, (char *)0x002892b8);

  (void)eax;
  (void)esi;
}

/* game_options_menu_update_pic_desc (0xf3400) — XBE naked draft (batch 124). */
#if defined(__clang__)
static int (*const bf3400_c12a0a0)(void) = FUN_0012a0a0;
static void * (*const bf3400_c12a1d0)(void) = network_game_server_get;
static void (*const bf3400_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const bf3400_exitfn)(int) = system_exit;
static bool (*const bf3400_c12a170)(void) = network_game_is_splitscreen_local;
static void * (*const bf3400_c12a240)(void) = network_game_client_get;
static int16_t (*const bf3400_c124d00)(void *client) = FUN_00124d00;
static bool (*const bf3400_c12ac80)(void *client) = network_player_is_valid;

__attribute__((naked, noinline))
void game_options_menu_update_pic_desc(void *widget __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c12a0a0]\n\t"
      "movl %%eax, %%esi\n\t"
      "call *%[c12a1d0]\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "cmpw $1, 0xe(%%ebx)\n\t"
      "movl %%eax, %%edi\n\t"
      "je .Lgame_options_menu_update_pic_desc_1\n\t"
      "pushl $1\n\t"
      "pushl $0xbad\n\t"
      "pushl $0x288938\n\t"
      "pushl $0x2893fc\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lgame_options_menu_update_pic_desc_1:\n\t"
      "testl %%edi, %%edi\n\t"
      "je .Lgame_options_menu_update_pic_desc_4\n\t"
      "call *%[c12a170]\n\t"
      "testb %%al, %%al\n\t"
      "movl $2, %%edi\n\t"
      "jne .Lgame_options_menu_update_pic_desc_2\n\t"
      "testl %%esi, %%esi\n\t"
      "je .Lgame_options_menu_update_pic_desc_2\n\t"
      "cmpw %%di, 0x112(%%esi)\n\t"
      "jl .Lgame_options_menu_update_pic_desc_3\n\t"
      ".Lgame_options_menu_update_pic_desc_2:\n\t"
      "call *%[c12a170]\n\t"
      "testb %%al, %%al\n\t"
      "je .Lgame_options_menu_update_pic_desc_4\n\t"
      "testl %%esi, %%esi\n\t"
      "je .Lgame_options_menu_update_pic_desc_9\n\t"
      "cmpw %%di, 0x224(%%esi)\n\t"
      "jge .Lgame_options_menu_update_pic_desc_4\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movw $0x23, 0x40(%%ebx)\n\t"
      "movb $1, 0x10(%%ebx)\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lgame_options_menu_update_pic_desc_3:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movw $0x22, 0x40(%%ebx)\n\t"
      "movb $1, 0x10(%%ebx)\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lgame_options_menu_update_pic_desc_4:\n\t"
      "testl %%esi, %%esi\n\t"
      "je .Lgame_options_menu_update_pic_desc_9\n\t"
      "cmpb $1, 0xc0(%%esi)\n\t"
      "jne .Lgame_options_menu_update_pic_desc_9\n\t"
      "call *%[c12a240]\n\t"
      "pushl %%eax\n\t"
      "call *%[c124d00]\n\t"
      "addl $4, %%esp\n\t"
      "testw %%ax, %%ax\n\t"
      "jge .Lgame_options_menu_update_pic_desc_9\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "movl %%ebx, -0x4(%%ebp)\n\t"
      "addl $0x244, %%esi\n\t"
      "movl $0x10, %%edi\n\t"
      ".Lgame_options_menu_update_pic_desc_5:\n\t"
      "leal -0x1e(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c12ac80]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lgame_options_menu_update_pic_desc_7\n\t"
      "movsbl (%%esi), %%eax\n\t"
      "subl $0, %%eax\n\t"
      "je .Lgame_options_menu_update_pic_desc_6\n\t"
      "decl %%eax\n\t"
      "jne .Lgame_options_menu_update_pic_desc_7\n\t"
      "incl -0x4(%%ebp)\n\t"
      "jmp .Lgame_options_menu_update_pic_desc_7\n\t"
      ".Lgame_options_menu_update_pic_desc_6:\n\t"
      "incl %%ebx\n\t"
      ".Lgame_options_menu_update_pic_desc_7:\n\t"
      "addl $0x20, %%esi\n\t"
      "decl %%edi\n\t"
      "jne .Lgame_options_menu_update_pic_desc_5\n\t"
      "testl %%ebx, %%ebx\n\t"
      "je .Lgame_options_menu_update_pic_desc_8\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lgame_options_menu_update_pic_desc_8\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "popl %%edi\n\t"
      "movl %%ecx, %%eax\n\t"
      "popl %%esi\n\t"
      "movw $0x1a, 0x40(%%ecx)\n\t"
      "movb $1, 0x10(%%eax)\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lgame_options_menu_update_pic_desc_8:\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "popl %%edi\n\t"
      "movl %%edx, %%eax\n\t"
      "popl %%esi\n\t"
      "movw $0x1b, 0x40(%%edx)\n\t"
      "movb $1, 0x10(%%eax)\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lgame_options_menu_update_pic_desc_9:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb $0, 0x10(%%ebx)\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c12a0a0] "m"(bf3400_c12a0a0), [c12a1d0] "m"(bf3400_c12a1d0), [assert] "m"(bf3400_assert), [exitfn] "m"(bf3400_exitfn), [c12a170] "m"(bf3400_c12a170), [c12a240] "m"(bf3400_c12a240), [c124d00] "m"(bf3400_c124d00), [c12ac80] "m"(bf3400_c12ac80)
      : "memory");
}
#else
#error "game_options_menu_update_pic_desc: clang naked draft required"
#endif


/* 0xf3540 */
void mp_level_select_list_update_displayed_items(void *widget)
{
  int esi = 0;

  FUN_0012a0a0();
  display_assert((char *)0x00289430, (char *)0x00288938, 3068, 0);
  system_exit(0);
  /* test esi, esi -> je 0xf358c */

  (void)esi;
}

/* 0xf3590 */
void get_editable_player_profile_display_name(void *widget)
{
  int eax = 0;
  int esi = 0;
  int edi = 0;

  /* relift: cmp word ptr [esi + 0xe], 3 -> je 0xf35c6 */
  display_assert((char *)0x002894c0, (char *)0x00288938, 3103, 0);
  system_exit(0);
  /* test edi, edi -> je 0xf35d4 */
  /* relift: cmp word ptr [edi + 0xe], 1 -> je 0xf35f4 */
  display_assert((char *)0x00289470, (char *)0x00288938, 3107, 0);
  system_exit(0);
  /* relift: cmp byte ptr [0x46ce3b], 1 -> jne 0xf3629 */
  main_get_map_name();
  crt_stricmp((char *)0x0046cd38, (char *)(uintptr_t)eax);
  /* test eax, eax -> jne 0xf3629 */

  (void)eax;
  (void)esi;
  (void)edi;
}

/* 0xf3640 */
void get_editable_playlist_profile_display_name(void *widget)
{
  int eax = 0;
  int esi = 0;

  /* relift: cmp word ptr [esi + 0xe], 1 -> je 0xf366e */
  display_assert((char *)0x002894f4, (char *)0x00288938, 3132, 0);
  system_exit(0);
  transport_network_available();
  /* test (char)eax, (char)eax -> je 0xf3681 */

  (void)eax;
  (void)esi;
}

/* 0xf3690 — collect up to 3 child widget text handles for item UI sync. */
/* 0xf3690 — resolve three neighboring list indices for a widget spinner. */
void FUN_000f3690(int *out_handles /* @<eax> */, void *widget /* @<ecx> */)
{
  char *w = (char *)widget;
  char *related;
  int count;
  int a;
  int b;
  int c;

  related = *(char **)(w + 0x34);
  if (*(int *)(w + 0x38) == (int)related) {
    a = (int)*(int16_t *)(w + 0x3c);
    b = a + 1;
    count = (int)*(uint16_t *)(w + 0x44);
    if (b == count)
      b = 0;
    c = b + 1;
    if (c == count)
      c = 0;
  } else if (*(int *)(w + 0x38) == *(int *)(related + 0x2c)) {
    b = (int)*(int16_t *)(w + 0x3c);
    a = b - 1;
    if (a < 0)
      a = (int)*(uint16_t *)(w + 0x44) - 1;
    c = b + 1;
    count = (int)*(uint16_t *)(w + 0x44);
    if (c == count)
      c = 0;
  } else {
    c = (int)*(int16_t *)(w + 0x3c);
    b = c - 1;
    if (b < 0)
      b = (int)*(uint16_t *)(w + 0x44) - 1;
    a = b - 1;
    if (a < 0)
      a = (int)*(uint16_t *)(w + 0x44) - 1;
  }

  count = (int)*(uint16_t *)(w + 0x44);
  out_handles[0] = (a < count) ? a : -1;
  out_handles[1] = (b < count) ? b : -1;
  out_handles[2] = (c < count) ? c : -1;
}

/* multiplayer_game_set_text_box_for_game_ruleset (0xf3740) — XBE naked draft (batch 129). */
#if defined(__clang__)
static void (*const bf3740_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const bf3740_exitfn)(int) = system_exit;
static void (*const bf3740_c1c18f0)(void) = player_profile_new;
static void (*const bf3740_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;

__attribute__((naked, noinline))
void multiplayer_game_set_text_box_for_game_ruleset(int *handles __attribute__((unused)), int count __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "xorl %%esi, %%esi\n\t"
      "pushl %%edi\n\t"
      "movb $0, -0x4(%%ebp)\n\t"
      "movw %%si, -0x3(%%ebp)\n\t"
      "movl $0x5aa3c0, %%edx\n\t"
      ".Lmultiplayer_game_set_text_box_for_game_ruleset_1:\n\t"
      "movl (%%edx), %%ecx\n\t"
      "cmpl $-1, %%ecx\n\t"
      "je .Lmultiplayer_game_set_text_box_for_game_ruleset_4\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "xorl %%eax, %%eax\n\t"
      "testl %%edi, %%edi\n\t"
      "jle .Lmultiplayer_game_set_text_box_for_game_ruleset_4\n\t"
      ".Lmultiplayer_game_set_text_box_for_game_ruleset_2:\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "cmpl (%%ebx,%%eax,4), %%ecx\n\t"
      "je .Lmultiplayer_game_set_text_box_for_game_ruleset_3\n\t"
      "incl %%eax\n\t"
      "cmpl %%edi, %%eax\n\t"
      "jl .Lmultiplayer_game_set_text_box_for_game_ruleset_2\n\t"
      "jmp .Lmultiplayer_game_set_text_box_for_game_ruleset_4\n\t"
      ".Lmultiplayer_game_set_text_box_for_game_ruleset_3:\n\t"
      "movb $1, -0x4(%%ebp,%%esi,1)\n\t"
      ".Lmultiplayer_game_set_text_box_for_game_ruleset_4:\n\t"
      "addl $0x34, %%edx\n\t"
      "incl %%esi\n\t"
      "cmpl $0x5aa45c, %%edx\n\t"
      "jl .Lmultiplayer_game_set_text_box_for_game_ruleset_1\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "testl %%eax, %%eax\n\t"
      "jle .Lmultiplayer_game_set_text_box_for_game_ruleset_13\n\t"
      ".Lmultiplayer_game_set_text_box_for_game_ruleset_5:\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl (%%eax,%%ebx,4), %%edx\n\t"
      "cmpl $-1, %%edx\n\t"
      "je .Lmultiplayer_game_set_text_box_for_game_ruleset_12\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movl $0x5aa3c0, %%eax\n\t"
      "leal (%%esp), %%esp\n\t"
      ".Lmultiplayer_game_set_text_box_for_game_ruleset_6:\n\t"
      "cmpl (%%eax), %%edx\n\t"
      "je .Lmultiplayer_game_set_text_box_for_game_ruleset_7\n\t"
      "addl $0x34, %%eax\n\t"
      "incl %%ecx\n\t"
      "cmpl $0x5aa45c, %%eax\n\t"
      "jl .Lmultiplayer_game_set_text_box_for_game_ruleset_6\n\t"
      ".Lmultiplayer_game_set_text_box_for_game_ruleset_7:\n\t"
      "cmpl $3, %%ecx\n\t"
      "jne .Lmultiplayer_game_set_text_box_for_game_ruleset_12\n\t"
      "xorl %%esi, %%esi\n\t"
      ".Lmultiplayer_game_set_text_box_for_game_ruleset_8:\n\t"
      "cmpb $1, -0x4(%%ebp,%%esi,1)\n\t"
      "jne .Lmultiplayer_game_set_text_box_for_game_ruleset_10\n\t"
      "cmpl $3, %%esi\n\t"
      "jl .Lmultiplayer_game_set_text_box_for_game_ruleset_9\n\t"
      "pushl $1\n\t"
      "pushl $0xca2\n\t"
      "pushl $0x288938\n\t"
      "pushl $0x289550\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lmultiplayer_game_set_text_box_for_game_ruleset_9:\n\t"
      "incl %%esi\n\t"
      "cmpl $3, %%esi\n\t"
      "jl .Lmultiplayer_game_set_text_box_for_game_ruleset_8\n\t"
      ".Lmultiplayer_game_set_text_box_for_game_ruleset_10:\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "movl (%%edx,%%ebx,4), %%eax\n\t"
      "movl %%esi, %%edi\n\t"
      "imull $0x34, %%edi, %%edi\n\t"
      "leal 0x5aa3c4(%%edi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "call *%[c1c18f0]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lmultiplayer_game_set_text_box_for_game_ruleset_11\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "movl (%%ecx,%%ebx,4), %%edx\n\t"
      "movl %%edx, 0x5aa3c0(%%edi)\n\t"
      "movb $1, -0x4(%%ebp,%%esi,1)\n\t"
      "jmp .Lmultiplayer_game_set_text_box_for_game_ruleset_12\n\t"
      ".Lmultiplayer_game_set_text_box_for_game_ruleset_11:\n\t"
      "pushl $0x289530\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      ".Lmultiplayer_game_set_text_box_for_game_ruleset_12:\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "incl %%ebx\n\t"
      "cmpl %%eax, %%ebx\n\t"
      "jl .Lmultiplayer_game_set_text_box_for_game_ruleset_5\n\t"
      ".Lmultiplayer_game_set_text_box_for_game_ruleset_13:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(bf3740_assert), [exitfn] "m"(bf3740_exitfn), [c1c18f0] "m"(bf3740_c1c18f0), [c8f390] "m"(bf3740_c8f390)
      : "memory");
}
#else
#error "multiplayer_game_set_text_box_for_game_ruleset: clang naked draft required"
#endif


/* multiplayer_game_set_text_box_for_teams_noteams (0xf3850) — XBE naked draft (batch 129). */
#if defined(__clang__)
static void (*const bf3850_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const bf3850_exitfn)(int) = system_exit;
static void (*const bf3850_c1c26f0)(void) = playlist_profile_delete;
static void (*const bf3850_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;

__attribute__((naked, noinline))
void multiplayer_game_set_text_box_for_teams_noteams(void *widget __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "xorl %%esi, %%esi\n\t"
      "pushl %%edi\n\t"
      "movb $0, -0x4(%%ebp)\n\t"
      "movw %%si, -0x3(%%ebp)\n\t"
      "movl $0x5aa260, %%edx\n\t"
      ".Lmultiplayer_game_set_text_box_for_teams_noteams_1:\n\t"
      "movl (%%edx), %%ecx\n\t"
      "cmpl $-1, %%ecx\n\t"
      "je .Lmultiplayer_game_set_text_box_for_teams_noteams_4\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "xorl %%eax, %%eax\n\t"
      "testl %%edi, %%edi\n\t"
      "jle .Lmultiplayer_game_set_text_box_for_teams_noteams_4\n\t"
      ".Lmultiplayer_game_set_text_box_for_teams_noteams_2:\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "cmpl (%%ebx,%%eax,4), %%ecx\n\t"
      "je .Lmultiplayer_game_set_text_box_for_teams_noteams_3\n\t"
      "incl %%eax\n\t"
      "cmpl %%edi, %%eax\n\t"
      "jl .Lmultiplayer_game_set_text_box_for_teams_noteams_2\n\t"
      "jmp .Lmultiplayer_game_set_text_box_for_teams_noteams_4\n\t"
      ".Lmultiplayer_game_set_text_box_for_teams_noteams_3:\n\t"
      "movb $1, -0x4(%%ebp,%%esi,1)\n\t"
      ".Lmultiplayer_game_set_text_box_for_teams_noteams_4:\n\t"
      "addl $0x6c, %%edx\n\t"
      "incl %%esi\n\t"
      "cmpl $0x5aa3a4, %%edx\n\t"
      "jl .Lmultiplayer_game_set_text_box_for_teams_noteams_1\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "testl %%eax, %%eax\n\t"
      "jle .Lmultiplayer_game_set_text_box_for_teams_noteams_13\n\t"
      ".Lmultiplayer_game_set_text_box_for_teams_noteams_5:\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl (%%eax,%%ebx,4), %%edx\n\t"
      "cmpl $-1, %%edx\n\t"
      "je .Lmultiplayer_game_set_text_box_for_teams_noteams_12\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movl $0x5aa260, %%eax\n\t"
      "leal (%%esp), %%esp\n\t"
      ".Lmultiplayer_game_set_text_box_for_teams_noteams_6:\n\t"
      "cmpl (%%eax), %%edx\n\t"
      "je .Lmultiplayer_game_set_text_box_for_teams_noteams_7\n\t"
      "addl $0x6c, %%eax\n\t"
      "incl %%ecx\n\t"
      "cmpl $0x5aa3a4, %%eax\n\t"
      "jl .Lmultiplayer_game_set_text_box_for_teams_noteams_6\n\t"
      ".Lmultiplayer_game_set_text_box_for_teams_noteams_7:\n\t"
      "cmpl $3, %%ecx\n\t"
      "jne .Lmultiplayer_game_set_text_box_for_teams_noteams_12\n\t"
      "xorl %%esi, %%esi\n\t"
      ".Lmultiplayer_game_set_text_box_for_teams_noteams_8:\n\t"
      "cmpb $1, -0x4(%%ebp,%%esi,1)\n\t"
      "jne .Lmultiplayer_game_set_text_box_for_teams_noteams_10\n\t"
      "cmpl $3, %%esi\n\t"
      "jl .Lmultiplayer_game_set_text_box_for_teams_noteams_9\n\t"
      "pushl $1\n\t"
      "pushl $0xcd5\n\t"
      "pushl $0x288938\n\t"
      "pushl $0x289550\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lmultiplayer_game_set_text_box_for_teams_noteams_9:\n\t"
      "incl %%esi\n\t"
      "cmpl $3, %%esi\n\t"
      "jl .Lmultiplayer_game_set_text_box_for_teams_noteams_8\n\t"
      ".Lmultiplayer_game_set_text_box_for_teams_noteams_10:\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "movl (%%edx,%%ebx,4), %%eax\n\t"
      "movl %%esi, %%edi\n\t"
      "imull $0x6c, %%edi, %%edi\n\t"
      "leal 0x5aa264(%%edi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "call *%[c1c26f0]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lmultiplayer_game_set_text_box_for_teams_noteams_11\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "movl (%%ecx,%%ebx,4), %%edx\n\t"
      "movl %%edx, 0x5aa260(%%edi)\n\t"
      "movb $1, -0x4(%%ebp,%%esi,1)\n\t"
      "jmp .Lmultiplayer_game_set_text_box_for_teams_noteams_12\n\t"
      ".Lmultiplayer_game_set_text_box_for_teams_noteams_11:\n\t"
      "pushl $0x28956c\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      ".Lmultiplayer_game_set_text_box_for_teams_noteams_12:\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "incl %%ebx\n\t"
      "cmpl %%eax, %%ebx\n\t"
      "jl .Lmultiplayer_game_set_text_box_for_teams_noteams_5\n\t"
      ".Lmultiplayer_game_set_text_box_for_teams_noteams_13:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(bf3850_assert), [exitfn] "m"(bf3850_exitfn), [c1c26f0] "m"(bf3850_c1c26f0), [c8f390] "m"(bf3850_c8f390)
      : "memory");
}
#else
#error "multiplayer_game_set_text_box_for_teams_noteams: clang naked draft required"
#endif


/* 0xf3960 */
void FUN_000f3960(void *widget)
{
  int eax = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;

  /* cmp eax, ecx -> je 0xf3986 */
  /* cmp eax, -1 -> jne 0xf3986 */
  qsort((void *)(uintptr_t)edi, esi, 0, (void *)0x000f3960);
  /* test esi, esi -> jle 0xf39b2 */
  /* relift: cmp dword ptr [edi + eax*4], -1 -> je 0xf39b2 */
  /* cmp eax, esi -> jl 0xf39a7 */

  (void)eax;
  (void)ecx;
  (void)esi;
  (void)edi;
}

/* FUN_000f39c0 (0xf39c0) — XBE naked draft (batch 113). */
#if defined(__clang__)
static void (*const bf39c0_ce0980)(void) = player_ui_get_active_player_profile;
static void (*const bf39c0_c1c0f70)(void *profile, short *out_level, short *out_difficulty) = player_profile_save_last_level_played;
static void *(*const bf39c0_tag)(int, int) = tag_get;
static void (*const bf39c0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const bf39c0_exitfn)(int) = system_exit;
static void (*const bf39c0_cf3690)(int *out_handles /* */, void *widget /* */) = FUN_000f3690;
static void * (*const bf39c0_ce3cd0)(void *widget, int index) = widget_instance_get_nth_child;

__attribute__((naked, noinline))
void FUN_000f39c0(void *widget __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x54, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "leal -0x54(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0\n\t"
      "call *%[ce0980]\n\t"
      "leal -0x4(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x8(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x54(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1c0f70]\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "movl (%%edi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x44654c61\n\t"
      "call *%[tag]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $0x1c, %%esp\n\t"
      "cmpw $2, (%%esi)\n\t"
      "je .LFUN_000f39c0_1\n\t"
      "pushl $1\n\t"
      "pushl $0x1e0\n\t"
      "pushl $0x288938\n\t"
      "pushl $0x28974c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000f39c0_1:\n\t"
      "cmpl $3, 0x3e0(%%esi)\n\t"
      "je .LFUN_000f39c0_2\n\t"
      "pushl $1\n\t"
      "pushl $0x1e1\n\t"
      "pushl $0x288938\n\t"
      "pushl $0x289710\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000f39c0_2:\n\t"
      "leal -0x24(%%ebp), %%eax\n\t"
      "movl %%edi, %%ecx\n\t"
      "call *%[cf3690]\n\t"
      "xorl %%eax, %%eax\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "jmp .LFUN_000f39c0_4\n\t"
      ".LFUN_000f39c0_3:\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      ".LFUN_000f39c0_4:\n\t"
      "cmpl $-1, -0x24(%%ebp,%%eax,4)\n\t"
      "je .LFUN_000f39c0_14\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "call *%[ce3cd0]\n\t"
      "movl 0x34(%%eax), %%edi\n\t"
      "movl 0x2c(%%edi), %%ebx\n\t"
      "movl 0x2c(%%ebx), %%esi\n\t"
      "movl 0x2c(%%esi), %%ecx\n\t"
      "movl (%%eax), %%eax\n\t"
      "movl %%ecx, -0x18(%%ebp)\n\t"
      "movl 0x2c(%%ecx), %%ecx\n\t"
      "movl 0x2c(%%ecx), %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl $0x44654c61\n\t"
      "movl %%ecx, -0x10(%%ebp)\n\t"
      "movl %%edx, -0x14(%%ebp)\n\t"
      "call *%[tag]\n\t"
      "movl 0x3e0(%%eax), %%ecx\n\t"
      "addl $0x10, %%esp\n\t"
      "testl %%ecx, %%ecx\n\t"
      "jne .LFUN_000f39c0_5\n\t"
      "pushl $1\n\t"
      "pushl $0x1f6\n\t"
      "pushl $0x288938\n\t"
      "pushl $0x2896d0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000f39c0_5:\n\t"
      "movl (%%edi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x44654c61\n\t"
      "call *%[tag]\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $1, (%%eax)\n\t"
      "je .LFUN_000f39c0_6\n\t"
      "pushl $1\n\t"
      "pushl $0x1f8\n\t"
      "pushl $0x288938\n\t"
      "pushl $0x289688\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000f39c0_6:\n\t"
      "movl (%%ebx), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x44654c61\n\t"
      "call *%[tag]\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $0, (%%eax)\n\t"
      "je .LFUN_000f39c0_7\n\t"
      "pushl $1\n\t"
      "pushl $0x1fa\n\t"
      "pushl $0x288938\n\t"
      "pushl $0x289640\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000f39c0_7:\n\t"
      "movl (%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x44654c61\n\t"
      "call *%[tag]\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $1, (%%eax)\n\t"
      "je .LFUN_000f39c0_8\n\t"
      "pushl $1\n\t"
      "pushl $0x1fc\n\t"
      "pushl $0x288938\n\t"
      "pushl $0x2895f0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000f39c0_8:\n\t"
      "movl -0x18(%%ebp), %%edx\n\t"
      "movl -0x10(%%ebp), %%ecx\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "movw $1, 0x50(%%edx)\n\t"
      "movw $2, 0x50(%%ecx)\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "movw $3, 0x50(%%eax)\n\t"
      "movl -0x24(%%ebp,%%ecx,4), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jl .LFUN_000f39c0_9\n\t"
      "cmpl $0xa, %%eax\n\t"
      "jl .LFUN_000f39c0_10\n\t"
      ".LFUN_000f39c0_9:\n\t"
      "pushl $1\n\t"
      "pushl $0x204\n\t"
      "pushl $0x288938\n\t"
      "pushl $0x289590\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "movl -0x18(%%ebp), %%edx\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000f39c0_10:\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "movl -0x24(%%ebp,%%eax,4), %%ecx\n\t"
      "movb 0x46ccec(,%%ecx,8), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_000f39c0_11\n\t"
      "movb 0x46cced(,%%ecx,8), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_000f39c0_11\n\t"
      "movb 0x46ccee(,%%ecx,8), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_000f39c0_11\n\t"
      "movb 0x46ccef(,%%ecx,8), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_000f39c0_11\n\t"
      "movl -0x10(%%ebp), %%ecx\n\t"
      "movl $0xa, %%eax\n\t"
      "movw %%ax, 0x40(%%edi)\n\t"
      "movw %%ax, 0x50(%%ebx)\n\t"
      "movw %%ax, 0x40(%%esi)\n\t"
      "movb $0, 0x10(%%edx)\n\t"
      "movl -0x14(%%ebp), %%edx\n\t"
      "movb $0, 0x10(%%ecx)\n\t"
      "movb $0, 0x10(%%edx)\n\t"
      "jmp .LFUN_000f39c0_13\n\t"
      ".LFUN_000f39c0_11:\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "movw -0x24(%%ebp,%%eax,4), %%ax\n\t"
      "movw %%ax, 0x40(%%edi)\n\t"
      "movw %%ax, 0x50(%%ebx)\n\t"
      "movw %%ax, 0x40(%%esi)\n\t"
      "movl 0x46ce3a, %%eax\n\t"
      "cmpb $1, %%ah\n\t"
      "jne .LFUN_000f39c0_12\n\t"
      "movsbl %%al, %%eax\n\t"
      "cmpl %%eax, %%ecx\n\t"
      "jne .LFUN_000f39c0_12\n\t"
      "movw $0xb, 0x40(%%esi)\n\t"
      ".LFUN_000f39c0_12:\n\t"
      "movb 0x46cced(,%%ecx,8), %%al\n\t"
      "movb %%al, 0x10(%%edx)\n\t"
      "movb 0x46ccee(,%%ecx,8), %%dl\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "movb %%dl, 0x10(%%eax)\n\t"
      "movb 0x46ccef(,%%ecx,8), %%cl\n\t"
      "movl -0x14(%%ebp), %%edx\n\t"
      "movb %%cl, 0x10(%%edx)\n\t"
      ".LFUN_000f39c0_13:\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "incl %%eax\n\t"
      "cmpl $3, %%eax\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "jl .LFUN_000f39c0_3\n\t"
      ".LFUN_000f39c0_14:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [ce0980] "m"(bf39c0_ce0980), [c1c0f70] "m"(bf39c0_c1c0f70), [tag] "m"(bf39c0_tag), [assert] "m"(bf39c0_assert), [exitfn] "m"(bf39c0_exitfn), [cf3690] "m"(bf39c0_cf3690), [ce3cd0] "m"(bf39c0_ce3cd0)
      : "memory");
}
#else
#error "FUN_000f39c0: clang naked draft required"
#endif

