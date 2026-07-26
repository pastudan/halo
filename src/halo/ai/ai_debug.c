
/* ai_debug_dispose (0x48f50) — XBE naked draft (batch 99). */
#if defined(__clang__)
static void (*const b48f50_c8ef70)(void *ptr, const char *file, int line) = debug_free;

__attribute__((naked, noinline))
void ai_debug_dispose(void)
{
  __asm__ volatile(
      "movl 0x331f58, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lai_debug_dispose_1\n\t"
      "pushl $0xa0\n\t"
      "pushl $0x25ab74\n\t"
      "pushl %%eax\n\t"
      "call *%[c8ef70]\n\t"
      "addl $0xc, %%esp\n\t"
      "movl $0, 0x331f58\n\t"
      ".Lai_debug_dispose_1:\n\t"
      "movl 0x331f5c, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lai_debug_dispose_2\n\t"
      "pushl $0xa6\n\t"
      "pushl $0x25ab74\n\t"
      "pushl %%eax\n\t"
      "call *%[c8ef70]\n\t"
      "addl $0xc, %%esp\n\t"
      "movl $0, 0x331f5c\n\t"
      ".Lai_debug_dispose_2:\n\t"
      "ret\n\t"
      :
      : [c8ef70] "m"(b48f50_c8ef70)
      : "memory");
}
#else
#error "ai_debug_dispose: clang naked draft required"
#endif


/* ai_debug_dispose_from_old_map (0x48fa0) — XBE naked draft (batch 97). */
#if defined(__clang__)
static void * (*const b48fa0_c18e3b0)(void) = FUN_0018e3b0;
static void *(*const b48fa0_elem)(void *, int, int) = tag_block_get_element;
static void * (*const b48fa0_c8de70)(char *destination, const char *source, size_t size) = csstrncpy;
static char * (*const b48fa0_c8dff0)(char *destination, const char *source) = csstrcpy;

__attribute__((naked, noinline))
void ai_debug_dispose_from_old_map(void)
{
  __asm__ volatile(
      "call *%[c18e3b0]\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lai_debug_dispose_from_old_map_1\n\t"
      "movl 0x5ac9f4, %%ecx\n\t"
      "cmpl $-1, %%ecx\n\t"
      "je .Lai_debug_dispose_from_old_map_1\n\t"
      "pushl $0xb0\n\t"
      "andl $0xffff, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "addl $0x42c, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "pushl $0x20\n\t"
      "pushl %%eax\n\t"
      "pushl $0x5ac9d2\n\t"
      "call *%[c8de70]\n\t"
      "addl $0x18, %%esp\n\t"
      "movb $0, 0x5ac9f1\n\t"
      "ret\n\t"
      ".Lai_debug_dispose_from_old_map_1:\n\t"
      "pushl $0x25386f\n\t"
      "pushl $0x5ac9d2\n\t"
      "call *%[c8dff0]\n\t"
      "addl $8, %%esp\n\t"
      "ret\n\t"
      :
      : [c18e3b0] "m"(b48fa0_c18e3b0), [elem] "m"(b48fa0_elem), [c8de70] "m"(b48fa0_c8de70), [c8dff0] "m"(b48fa0_c8dff0)
      : "memory");
}
#else
#error "ai_debug_dispose_from_old_map: clang naked draft required"
#endif


/* ai_debug_clear_storage (0x49000) — XBE naked draft (batch 94). */
#if defined(__clang__)
static void (*const b49000_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b49000_exitfn)(int) = system_exit;
static void *(*const b49000_memset)(void *, int, unsigned int) = csmemset;

__attribute__((naked, noinline))
void ai_debug_clear_storage(void)
{
  __asm__ volatile(
      "movl 0x331f58, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lai_debug_clear_storage_1\n\t"
      "pushl $1\n\t"
      "pushl $0xd0\n\t"
      "pushl $0x25ab74\n\t"
      "pushl $0x25abac\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lai_debug_clear_storage_1:\n\t"
      "movl 0x331f58, %%eax\n\t"
      "pushl $0x657c00\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "call *%[memset]\n\t"
      "movl 0x331f5c, %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lai_debug_clear_storage_2\n\t"
      "pushl $1\n\t"
      "pushl $0xd3\n\t"
      "pushl $0x25ab74\n\t"
      "pushl $0x25ab94\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lai_debug_clear_storage_2:\n\t"
      "movl 0x331f5c, %%ecx\n\t"
      "pushl $0x394f80\n\t"
      "pushl $0\n\t"
      "pushl %%ecx\n\t"
      "call *%[memset]\n\t"
      "addl $0xc, %%esp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b49000_assert), [exitfn] "m"(b49000_exitfn), [memset] "m"(b49000_memset)
      : "memory");
}
#else
#error "ai_debug_clear_storage: clang naked draft required"
#endif


/* ai_debug_actor_deleted (0x49080) — XBE naked draft (batch 96). */
#if defined(__clang__)


__attribute__((naked, noinline))
void ai_debug_actor_deleted(int actor_handle __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl 0x331f5c, %%edx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movl $0x20, %%esi\n\t"
      ".Lai_debug_actor_deleted_1:\n\t"
      "movb 0xc(%%ecx,%%edx,1), %%bl\n\t"
      "testb %%bl, %%bl\n\t"
      "leal 0xc(%%ecx,%%edx,1), %%eax\n\t"
      "je .Lai_debug_actor_deleted_2\n\t"
      "cmpl %%edi, (%%ecx,%%edx,1)\n\t"
      "jne .Lai_debug_actor_deleted_2\n\t"
      "movb $0, (%%eax)\n\t"
      "movl 0x331f5c, %%edx\n\t"
      ".Lai_debug_actor_deleted_2:\n\t"
      "addl $0x1ca7c, %%ecx\n\t"
      "decl %%esi\n\t"
      "jne .Lai_debug_actor_deleted_1\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "ai_debug_actor_deleted: clang naked draft required"
#endif


/* ai_debug_get_path_storage (0x49120) — XBE naked draft (batch 86). */
#if defined(__clang__)
static void (*const b49120_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b49120_exitfn)(int) = system_exit;
static void *(*const b49120_memset)(void *, int, unsigned int) = csmemset;
static int (*const b49120_gtime)(void) = game_time_get;

__attribute__((naked, noinline))
void * ai_debug_get_path_storage(int actor_handle __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $8, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "orl $0xffffffff, %%edx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "pushl %%edi\n\t"
      "movl %%edi, %%edi\n\t"
      ".Lai_debug_get_path_storage_1:\n\t"
      "movl 0x331f5c, %%ebx\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "movswl %%cx, %%eax\n\t"
      "imull $0x1ca7c, %%eax, %%eax\n\t"
      "movl (%%eax,%%ebx,1), %%edi\n\t"
      "addl %%ebx, %%eax\n\t"
      "cmpl %%esi, %%edi\n\t"
      "jne .Lai_debug_get_path_storage_2\n\t"
      "movb 0xd(%%eax), %%bl\n\t"
      "testb %%bl, %%bl\n\t"
      "je .Lai_debug_get_path_storage_4\n\t"
      ".Lai_debug_get_path_storage_2:\n\t"
      "cmpw $-1, %%dx\n\t"
      "jne .Lai_debug_get_path_storage_3\n\t"
      "movb 0xc(%%eax), %%bl\n\t"
      "testb %%bl, %%bl\n\t"
      "jne .Lai_debug_get_path_storage_3\n\t"
      "movl %%ecx, %%edx\n\t"
      ".Lai_debug_get_path_storage_3:\n\t"
      "incl %%ecx\n\t"
      "cmpw $0x20, %%cx\n\t"
      "jl .Lai_debug_get_path_storage_1\n\t"
      "jmp .Lai_debug_get_path_storage_5\n\t"
      ".Lai_debug_get_path_storage_4:\n\t"
      "movl %%ecx, %%edx\n\t"
      ".Lai_debug_get_path_storage_5:\n\t"
      "cmpw $-1, %%dx\n\t"
      "jne .Lai_debug_get_path_storage_9\n\t"
      "xorl %%edi, %%edi\n\t"
      "movl $0xffffffff, -0x8(%%ebp)\n\t"
      "movl $0x7fffffff, -0x4(%%ebp)\n\t"
      "xorl %%ebx, %%ebx\n\t"
      ".Lai_debug_get_path_storage_6:\n\t"
      "movl 0x331f5c, %%eax\n\t"
      "leal (%%ebx,%%eax,1), %%esi\n\t"
      "movb 0xc(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lai_debug_get_path_storage_7\n\t"
      "pushl $1\n\t"
      "pushl $0x123\n\t"
      "pushl $0x25ab74\n\t"
      "pushl $0x25abc0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lai_debug_get_path_storage_7:\n\t"
      "movl 0x4(%%esi), %%eax\n\t"
      "cmpl -0x4(%%ebp), %%eax\n\t"
      "jge .Lai_debug_get_path_storage_8\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "movl %%edi, -0x8(%%ebp)\n\t"
      ".Lai_debug_get_path_storage_8:\n\t"
      "incl %%edi\n\t"
      "addl $0x1ca7c, %%ebx\n\t"
      "cmpw $0x20, %%di\n\t"
      "jl .Lai_debug_get_path_storage_6\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "cmpw $-1, %%dx\n\t"
      "je .Lai_debug_get_path_storage_10\n\t"
      ".Lai_debug_get_path_storage_9:\n\t"
      "movl 0x331f5c, %%ebx\n\t"
      "movswl %%dx, %%esi\n\t"
      "imull $0x1ca7c, %%esi, %%esi\n\t"
      "pushl $0x1ca7c\n\t"
      "addl %%ebx, %%esi\n\t"
      "pushl $0\n\t"
      "pushl %%esi\n\t"
      "call *%[memset]\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "addl $0xc, %%esp\n\t"
      "movb $1, 0xc(%%esi)\n\t"
      "movl %%ecx, (%%esi)\n\t"
      "call *%[gtime]\n\t"
      "movl %%eax, 0x4(%%esi)\n\t"
      "popl %%edi\n\t"
      "movl %%esi, %%eax\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lai_debug_get_path_storage_10:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "xorl %%eax, %%eax\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b49120_assert), [exitfn] "m"(b49120_exitfn), [memset] "m"(b49120_memset), [gtime] "m"(b49120_gtime)
      : "memory");
}
#else
#error "ai_debug_get_path_storage: clang naked draft required"
#endif


/* ai_debug_select_encounter: reset debug encounter state when encounter_idx
 * changes. Checks if the current encounter index (0x5ac9f4) differs from
 * encounter_idx; if so, updates the index, clears the debug-state byte at
 * 0x629d40, zeroes the 0x670-byte block at 0x629d44 and the 0x8000-byte block
 * at 0x62a3b4, then calls ai_debug_select_actor(encounter_idx, -1) to
 * reinitialize secondary state.
 *
 * No __FILE__ string.  Called from ai_debug_select_actor,
 * ai_debug_initialize_for_new_map, ai_debug_change_selected_encounter,
 * FUN_00054e40.
 *
 * Calling convention verified (ADD ESP,0x20 at 0x49267 covers 8 dwords):
 *   3 args to csmemset(0x629d44,...) + 3 args to csmemset(0x62a3b4,...) +
 *   2 args to ai_debug_select_actor = 8 dwords. ai_debug_select_actor is cdecl.
 *
 * Call-site verification:
 *   ai_debug_initialize_for_new_map @ 0x4c116: PUSH ESI (enc_idx) ->
 * encounter_idx [match] ai_debug_select_actor @ 0x4b1ca: PUSH EAX (param_1) ->
 * encounter_idx [match] */
void ai_debug_select_actor(int encounter_idx, int param_2);

/* ai_debug_select_encounter (0x49220) — XBE naked draft (batch 97). */
#if defined(__clang__)
static void *(*const b49220_memset)(void *, int, unsigned int) = csmemset;
static void (*const b49220_c4b1b0)(int encounter_idx, int param_2) = ai_debug_select_actor;

__attribute__((naked, noinline))
void ai_debug_select_encounter(int encounter_idx __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl 0x5ac9f4, %%eax\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "cmpl %%esi, %%eax\n\t"
      "je .Lai_debug_select_encounter_1\n\t"
      "pushl $0x670\n\t"
      "pushl $0\n\t"
      "pushl $0x629d44\n\t"
      "movl %%esi, 0x5ac9f4\n\t"
      "movb $0, 0x629d40\n\t"
      "call *%[memset]\n\t"
      "pushl $0x8000\n\t"
      "pushl $0\n\t"
      "pushl $0x62a3b4\n\t"
      "call *%[memset]\n\t"
      "pushl $-1\n\t"
      "pushl %%esi\n\t"
      "call *%[c4b1b0]\n\t"
      "addl $0x20, %%esp\n\t"
      ".Lai_debug_select_encounter_1:\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [memset] "m"(b49220_memset), [c4b1b0] "m"(b49220_c4b1b0)
      : "memory");
}
#else
#error "ai_debug_select_encounter: clang naked draft required"
#endif


/* FUN_000494d0: set debug ray-test success flag.
 *
 * No __FILE__ string. Called from ai_debug_get_last_path (ray setup) and
 * FUN_000494e0 (ray render). */
void FUN_000494d0(char success)
{
  *(uint8_t *)0x5acab9 = success;
}

/* ai_debug_update (0x4ab10) — XBE naked draft (batch 107). */
#if defined(__clang__)
static int (*const b4ab10_cb6870)(int16_t local_player_index) = player_control_get_unit_index;
static void *(*const b4ab10_tryget)(int, int) = object_try_and_get_and_verify_type;
static int (*const b4ab10_c1a1bc0)(int unit_handle, vector3_t *pos) = biped_find_pathfinding_surface_index;
static void * (*const b4ab10_c8a4e0)(unsigned __int16 local_player_index) = observer_get_camera;
static bool (*const b4ab10_ray)(unsigned int, float *, float *, int, short *) = FUN_0014df70;
static void (*const b4ab10_c5dfc0)(void *param_1, unsigned int param_2, unsigned char param_3, int param_4) = path_input_new;
static void (*const b4ab10_c5e000)(void *param_1, float *param_2, int param_3) = path_input_set_start;
static void (*const b4ab10_c5e070)(void *param_1, int param_2) = path_input_set_search_bounds;
static void *(*const b4ab10_get)(int, int) = object_get_and_verify_type;
static vector3_t * (*const b4ab10_c1412f0)(int object_handle, vector3_t *out_position) = object_get_world_position;
static void (*const b4ab10_c5e030)(void *param_1, float *param_2, float param_3, unsigned int param_4, float param_5) = path_input_set_attractor;
static void (*const b4ab10_c5e090)(void *param_1, void *param_2, void *param_3) = path_state_new;
static void (*const b4ab10_c5e0d0)(void *param_1, float *param_2, int param_3, int param_4) = FUN_0005e0d0;
static char (*const b4ab10_c5ff70)(unsigned int *path_buf) = FUN_0005ff70;
static char (*const b4ab10_c5eae0)(unsigned int path_buf, unsigned int *nav_state_out) = path_state_build_path;
static int (*const b4ab10_gtime)(void) = game_time_get;
static bool (*const b4ab10_c977f0)(void) = game_in_editor;
static scenario_t * (*const b4ab10_c18e380)(void) = global_scenario_get;
static void *(*const b4ab10_elem)(void *, int, int) = tag_block_get_element;
static void (*const b4ab10_cff4d0)(int channel, const char *format, ...) = console_printf;
static void (*const b4ab10_c4a030)(void) = FUN_0004a030;
static void (*const b4ab10_c4a9f0)(void) = FUN_0004a9f0;

__attribute__((naked, noinline))
void ai_debug_update(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x6c, %%esp\n\t"
      "movb 0x5aca6a, %%al\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "xorl %%edi, %%edi\n\t"
      "testb %%al, %%al\n\t"
      "je .Lai_debug_update_1\n\t"
      "movl %%edi, 0x5accac\n\t"
      "movl %%edi, 0x5eccb0\n\t"
      ".Lai_debug_update_1:\n\t"
      "movb 0x5ac9fc, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lai_debug_update_12\n\t"
      "movb 0x5ac9fd, %%al\n\t"
      "testb %%al, %%al\n\t"
      "movl $1, %%ebx\n\t"
      "jne .Lai_debug_update_2\n\t"
      "pushl %%edi\n\t"
      "call *%[cb6870]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $4, %%esp\n\t"
      "cmpl $-1, %%esi\n\t"
      "je .Lai_debug_update_2\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "call *%[tryget]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lai_debug_update_2\n\t"
      "leal -0x1c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[c1a1bc0]\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lai_debug_update_2\n\t"
      "movl -0x1c(%%ebp), %%ecx\n\t"
      "movl -0x18(%%ebp), %%edx\n\t"
      "movl %%eax, 0x5f91b8\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "movl %%ecx, 0x5f91ac\n\t"
      "movl %%edx, 0x5f91b0\n\t"
      "movl %%eax, 0x5f91b4\n\t"
      "movl %%esi, 0x5f91bc\n\t"
      "movb %%bl, 0x5f91a8\n\t"
      ".Lai_debug_update_2:\n\t"
      "movb 0x5ac9fe, %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lai_debug_update_3\n\t"
      "pushl %%edi\n\t"
      "call *%[c8a4e0]\n\t"
      "addl $4, %%esp\n\t"
      "cmpl %%edi, %%eax\n\t"
      "je .Lai_debug_update_3\n\t"
      "movl 0x31fc50, %%ecx\n\t"
      "incw 0x5ac5d4\n\t"
      "flds (%%ecx)\n\t"
      "fmuls 0x254cb8\n\t"
      "leal -0x1c(%%ebp), %%edx\n\t"
      "fstps -0x1c(%%ebp)\n\t"
      "flds 0x4(%%ecx)\n\t"
      "fmuls 0x254cb8\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "flds 0x8(%%ecx)\n\t"
      "leal -0x6c(%%ebp), %%ecx\n\t"
      "fmuls 0x254cb8\n\t"
      "pushl %%ecx\n\t"
      "pushl $-1\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "pushl $0x21\n\t"
      "call *%[ray]\n\t"
      "addl $0x14, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lai_debug_update_3\n\t"
      "movl -0x54(%%ebp), %%eax\n\t"
      "movl -0x50(%%ebp), %%ecx\n\t"
      "movl -0x4c(%%ebp), %%edx\n\t"
      "movl %%eax, 0x5f91c4\n\t"
      "movl -0x28(%%ebp), %%eax\n\t"
      "movb %%bl, 0x5f91c0\n\t"
      "movl %%ecx, 0x5f91c8\n\t"
      "movl %%edx, 0x5f91cc\n\t"
      "movl %%eax, 0x5f91d0\n\t"
      "movl $0, 0x5f91d4\n\t"
      ".Lai_debug_update_3:\n\t"
      "movb 0x5f91a8, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lai_debug_update_12\n\t"
      "movl 0x5f91bc, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edi\n\t"
      "leal -0x64(%%ebp), %%edx\n\t"
      "pushl $0x3e4ccccd\n\t"
      "pushl %%edx\n\t"
      "call *%[c5dfc0]\n\t"
      "movl 0x5f91b8, %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x64(%%ebp), %%ecx\n\t"
      "pushl $0x5f91ac\n\t"
      "pushl %%ecx\n\t"
      "call *%[c5e000]\n\t"
      "flds 0x5aca00\n\t"
      "fcomps 0x2533c0\n\t"
      "addl $0x1c, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lai_debug_update_4\n\t"
      "movl 0x5aca00, %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x64(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c5e070]\n\t"
      "addl $8, %%esp\n\t"
      ".Lai_debug_update_4:\n\t"
      "movb 0x5aca04, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lai_debug_update_9\n\t"
      "pushl %%edi\n\t"
      "call *%[cb6870]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $4, %%esp\n\t"
      "cmpl $-1, %%esi\n\t"
      "je .Lai_debug_update_9\n\t"
      "pushl $3\n\t"
      "pushl %%esi\n\t"
      "call *%[get]\n\t"
      "leal -0x1c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "call *%[c1412f0]\n\t"
      "flds 0x5aca0c\n\t"
      "fcomps 0x2533c0\n\t"
      "addl $0x10, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .Lai_debug_update_5\n\t"
      "movl $0x41a00000, -0x4(%%ebp)\n\t"
      "jmp .Lai_debug_update_6\n\t"
      ".Lai_debug_update_5:\n\t"
      "movl 0x5aca0c, %%edx\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      ".Lai_debug_update_6:\n\t"
      "flds 0x5aca08\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .Lai_debug_update_7\n\t"
      "movl $0x41000000, -0x8(%%ebp)\n\t"
      "jmp .Lai_debug_update_8\n\t"
      ".Lai_debug_update_7:\n\t"
      "movl 0x5aca08, %%eax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      ".Lai_debug_update_8:\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl $-1\n\t"
      "pushl %%edx\n\t"
      "leal -0x1c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x64(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c5e030]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lai_debug_update_9:\n\t"
      "pushl $0x60d2c4\n\t"
      "leal -0x64(%%ebp), %%edx\n\t"
      "pushl $0x5f91dc\n\t"
      "pushl %%edx\n\t"
      "call *%[c5e090]\n\t"
      "movb 0x5f91c0, %%al\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lai_debug_update_10\n\t"
      "movb 0x5ac9ff, %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lai_debug_update_10\n\t"
      "movl 0x5aca10, %%eax\n\t"
      "movl 0x5f91d0, %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x5f91c4\n\t"
      "pushl $0x5f91dc\n\t"
      "call *%[c5e0d0]\n\t"
      "addl $0x10, %%esp\n\t"
      ".Lai_debug_update_10:\n\t"
      "pushl $0x5f91dc\n\t"
      "call *%[c5ff70]\n\t"
      "movb 0x5f91c0, %%al\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lai_debug_update_11\n\t"
      "movb 0x5ac9ff, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lai_debug_update_11\n\t"
      "movl 0x5aca10, %%edx\n\t"
      "movl 0x5f91d0, %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl $0x5f91c4\n\t"
      "pushl $0x5f91dc\n\t"
      "call *%[c5e0d0]\n\t"
      "addl $0x10, %%esp\n\t"
      ".Lai_debug_update_11:\n\t"
      "pushl $0x60d268\n\t"
      "pushl $0x5f91dc\n\t"
      "call *%[c5eae0]\n\t"
      "addl $8, %%esp\n\t"
      "movb %%bl, 0x5f91d8\n\t"
      "movb %%bl, 0x60d2d0\n\t"
      "call *%[gtime]\n\t"
      "movl %%eax, 0x60d2c8\n\t"
      "movl $0xffffffff, 0x60d2c4\n\t"
      ".Lai_debug_update_12:\n\t"
      "movb 0x5ac9c2, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lai_debug_update_18\n\t"
      "call *%[c977f0]\n\t"
      "testb %%al, %%al\n\t"
      "je .Lai_debug_update_18\n\t"
      "call *%[c18e380]\n\t"
      "leal 0x42c(%%eax), %%ebx\n\t"
      "cmpl %%edi, (%%ebx)\n\t"
      "movl %%edi, -0x4(%%ebp)\n\t"
      "movl %%edi, -0x8(%%ebp)\n\t"
      "movl %%ebx, -0xc(%%ebp)\n\t"
      "jle .Lai_debug_update_17\n\t"
      "xorl %%eax, %%eax\n\t"
      "jmp .Lai_debug_update_13\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".Lai_debug_update_13:\n\t"
      "pushl $0xb0\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "call *%[elem]\n\t"
      "leal 0x80(%%eax), %%esi\n\t"
      "movl (%%esi), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl %%edi, %%eax\n\t"
      "jle .Lai_debug_update_16\n\t"
      "xorl %%eax, %%eax\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".Lai_debug_update_14:\n\t"
      "pushl $0xe8\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[elem]\n\t"
      "addl $0xc, %%esp\n\t"
      "leal 0x6c(%%eax), %%ecx\n\t"
      "movl $4, %%edx\n\t"
      ".Lai_debug_update_15:\n\t"
      "movl -0x4(%%ecx), %%ebx\n\t"
      "movl %%ebx, (%%ecx)\n\t"
      "addl $-4, %%ecx\n\t"
      "decl %%edx\n\t"
      "jne .Lai_debug_update_15\n\t"
      "movl -0x4(%%ebp), %%ebx\n\t"
      "movl 0x54(%%eax), %%ecx\n\t"
      "incl %%ebx\n\t"
      "incl %%edi\n\t"
      "movl %%ecx, 0x5c(%%eax)\n\t"
      "movl (%%esi), %%ecx\n\t"
      "movswl %%di, %%eax\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "movl %%ebx, -0x4(%%ebp)\n\t"
      "jl .Lai_debug_update_14\n\t"
      "movl -0xc(%%ebp), %%ebx\n\t"
      "xorl %%edi, %%edi\n\t"
      ".Lai_debug_update_16:\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movl (%%ebx), %%ecx\n\t"
      "incl %%eax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "movswl %%ax, %%eax\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jl .Lai_debug_update_13\n\t"
      ".Lai_debug_update_17:\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x25af18\n\t"
      "pushl %%edi\n\t"
      "call *%[cff4d0]\n\t"
      "addl $0xc, %%esp\n\t"
      "movb $0, 0x5ac9c2\n\t"
      ".Lai_debug_update_18:\n\t"
      "movb 0x5ac9c3, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lai_debug_update_25\n\t"
      "call *%[c977f0]\n\t"
      "testb %%al, %%al\n\t"
      "je .Lai_debug_update_25\n\t"
      "call *%[c18e380]\n\t"
      "leal 0x42c(%%eax), %%esi\n\t"
      "cmpl %%edi, (%%esi)\n\t"
      "movl %%edi, -0x4(%%ebp)\n\t"
      "movl %%edi, -0xc(%%ebp)\n\t"
      "movl %%esi, -0x10(%%ebp)\n\t"
      "jle .Lai_debug_update_24\n\t"
      "xorl %%eax, %%eax\n\t"
      "nop\n\t"
      ".Lai_debug_update_19:\n\t"
      "pushl $0xb0\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[elem]\n\t"
      "leal 0x80(%%eax), %%ebx\n\t"
      "movl (%%ebx), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%edi, -0x8(%%ebp)\n\t"
      "jle .Lai_debug_update_23\n\t"
      "xorl %%eax, %%eax\n\t"
      ".Lai_debug_update_20:\n\t"
      "pushl $0xe8\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "call *%[elem]\n\t"
      "leal 0xd0(%%eax), %%esi\n\t"
      "movl (%%esi), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "xorl %%edi, %%edi\n\t"
      "testl %%eax, %%eax\n\t"
      "jle .Lai_debug_update_22\n\t"
      "xorl %%eax, %%eax\n\t"
      "nop\n\t"
      ".Lai_debug_update_21:\n\t"
      "pushl $0x1c\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[elem]\n\t"
      "movw $0xffff, 0x18(%%eax)\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movl (%%esi), %%ecx\n\t"
      "addl $0xc, %%esp\n\t"
      "incl %%eax\n\t"
      "incl %%edi\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "movswl %%di, %%eax\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jl .Lai_debug_update_21\n\t"
      ".Lai_debug_update_22:\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movl (%%ebx), %%ecx\n\t"
      "incl %%eax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "movswl %%ax, %%eax\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jl .Lai_debug_update_20\n\t"
      "movl -0x10(%%ebp), %%esi\n\t"
      ".Lai_debug_update_23:\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "movl (%%esi), %%ecx\n\t"
      "incl %%eax\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "movswl %%ax, %%eax\n\t"
      "xorl %%edi, %%edi\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jl .Lai_debug_update_19\n\t"
      ".Lai_debug_update_24:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x25aed8\n\t"
      "pushl %%edi\n\t"
      "call *%[cff4d0]\n\t"
      "addl $0xc, %%esp\n\t"
      "movb $0, 0x5ac9c3\n\t"
      ".Lai_debug_update_25:\n\t"
      "call *%[c4a030]\n\t"
      "call *%[c4a9f0]\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [cb6870] "m"(b4ab10_cb6870), [tryget] "m"(b4ab10_tryget), [c1a1bc0] "m"(b4ab10_c1a1bc0), [c8a4e0] "m"(b4ab10_c8a4e0), [ray] "m"(b4ab10_ray), [c5dfc0] "m"(b4ab10_c5dfc0), [c5e000] "m"(b4ab10_c5e000), [c5e070] "m"(b4ab10_c5e070), [get] "m"(b4ab10_get), [c1412f0] "m"(b4ab10_c1412f0), [c5e030] "m"(b4ab10_c5e030), [c5e090] "m"(b4ab10_c5e090), [c5e0d0] "m"(b4ab10_c5e0d0), [c5ff70] "m"(b4ab10_c5ff70), [c5eae0] "m"(b4ab10_c5eae0), [gtime] "m"(b4ab10_gtime), [c977f0] "m"(b4ab10_c977f0), [c18e380] "m"(b4ab10_c18e380), [elem] "m"(b4ab10_elem), [cff4d0] "m"(b4ab10_cff4d0), [c4a030] "m"(b4ab10_c4a030), [c4a9f0] "m"(b4ab10_c4a9f0)
      : "memory");
}
#else
#error "ai_debug_update: clang naked draft required"
#endif


/* ai_debug_select_encounter: reset debug encounter state when encounter_idx
 * changes. Checks if the current encounter index (0x5ac9f4) differs from
 * encounter_idx; if so, updates the index, clears the debug-state byte at
 * 0x629d40, zeroes the 0x670-byte block at 0x629d44 and the 0x8000-byte block
 * at 0x62a3b4, then calls ai_debug_select_actor(encounter_idx, -1) to
 * reinitialize secondary state.
 *
 * No __FILE__ string.  Called from ai_debug_select_actor,
 * ai_debug_initialize_for_new_map, ai_debug_change_selected_encounter,
 * FUN_00054e40.
 *
 * Call-site verification:
 *   ai_debug_initialize_for_new_map @ 0x4c116: PUSH ESI (enc_idx, int) ->
 * encounter_idx [match] ai_debug_select_actor @ 0x4b1ca: PUSH EAX (param_1,
 * int) -> encounter_idx [match]
 *
 * Stack cleanup: ADD ESP,0x20 (0x49267) covers 8 dwords:
 *   3 args to csmemset(0x629d44,...) + 3 args to csmemset(0x62a3b4,...) +
 *   2 args to ai_debug_select_actor = 8 dwords = 0x20 bytes. */

/* ai_debug_select_actor (0x4b1b0) — XBE naked draft (batch 94). */
#if defined(__clang__)
static void (*const b4b1b0_c49220)(int encounter_idx) = ai_debug_select_encounter;

__attribute__((naked, noinline))
void ai_debug_select_actor(int encounter_idx __attribute__((unused)), int param_2 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "cmpl %%eax, 0x5ac9f4\n\t"
      "pushl %%esi\n\t"
      "movl 0xc(%%ebp), %%esi\n\t"
      "jne .Lai_debug_select_actor_1\n\t"
      "cmpl %%esi, 0x5ac9f8\n\t"
      "je .Lai_debug_select_actor_3\n\t"
      ".Lai_debug_select_actor_1:\n\t"
      "pushl %%eax\n\t"
      "call *%[c49220]\n\t"
      "addl $4, %%esp\n\t"
      "xorl %%edx, %%edx\n\t"
      "movl %%esi, 0x5ac9f8\n\t"
      "movb %%dl, 0x629d40\n\t"
      "movl $0x62a3b5, %%eax\n\t"
      "movl $0x200, %%ecx\n\t"
      "jmp .Lai_debug_select_actor_2\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".Lai_debug_select_actor_2:\n\t"
      "movb %%dl, (%%eax)\n\t"
      "addl $0x40, %%eax\n\t"
      "decl %%ecx\n\t"
      "jne .Lai_debug_select_actor_2\n\t"
      "cmpl $-1, %%esi\n\t"
      "setne %%al\n\t"
      "movb %%al, 0x6323d4\n\t"
      "movl %%esi, 0x6323d8\n\t"
      "movw %%dx, 0x6323dc\n\t"
      ".Lai_debug_select_actor_3:\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c49220] "m"(b4b1b0_c49220)
      : "memory");
}
#else
#error "ai_debug_select_actor: clang naked draft required"
#endif


/* ai_debug_initialize_for_new_map (0x4c0f0) — XBE naked draft (batch 95). */
#if defined(__clang__)
static int (*const b4c0f0_c59930)(char *name) = encounter_get_by_name;
static void (*const b4c0f0_c49000)(void) = ai_debug_clear_storage;
static void (*const b4c0f0_c49220)(int encounter_idx) = ai_debug_select_encounter;

__attribute__((naked, noinline))
void ai_debug_initialize_for_new_map(void)
{
  __asm__ volatile(
      "pushl %%esi\n\t"
      "pushl $0x5ac9d2\n\t"
      "call *%[c59930]\n\t"
      "addl $4, %%esp\n\t"
      "movl %%eax, %%esi\n\t"
      "call *%[c49000]\n\t"
      "cmpl %%esi, 0x5ac9f4\n\t"
      "jne .Lai_debug_initialize_for_new_map_1\n\t"
      "cmpl $-1, 0x5ac9f8\n\t"
      "je .Lai_debug_initialize_for_new_map_3\n\t"
      ".Lai_debug_initialize_for_new_map_1:\n\t"
      "pushl %%esi\n\t"
      "call *%[c49220]\n\t"
      "addl $4, %%esp\n\t"
      "xorl %%edx, %%edx\n\t"
      "movl $0xffffffff, 0x5ac9f8\n\t"
      "movb %%dl, 0x629d40\n\t"
      "movl $0x62a3b5, %%eax\n\t"
      "movl $0x200, %%ecx\n\t"
      "jmp .Lai_debug_initialize_for_new_map_2\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".Lai_debug_initialize_for_new_map_2:\n\t"
      "movb %%dl, (%%eax)\n\t"
      "addl $0x40, %%eax\n\t"
      "decl %%ecx\n\t"
      "jne .Lai_debug_initialize_for_new_map_2\n\t"
      "movb %%dl, 0x6323d4\n\t"
      "movl $0xffffffff, 0x6323d8\n\t"
      "movw %%dx, 0x6323dc\n\t"
      ".Lai_debug_initialize_for_new_map_3:\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      :
      : [c59930] "m"(b4c0f0_c59930), [c49000] "m"(b4c0f0_c49000), [c49220] "m"(b4c0f0_c49220)
      : "memory");
}
#else
#error "ai_debug_initialize_for_new_map: clang naked draft required"
#endif


/* --- ai_debug.obj batch drafts (2026-07-26) --- */
void ai_debug_sound_point_set(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}
void ai_debug_lineoffire_success(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}
void ai_debug_lineofsight_reset(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

void set_real_point3d(void)
{
  csmemset((void *)0x5abaa0, 0, 0xeec);
  *(char *)0x5abaa4 = 1;
}

void ai_debug_get_last_path(float *vec_a, float *vec_b)
{
  *(char *)0x5acab8 = 1;
  *(char *)0x5acab9 = 0;
  *(uint32_t *)0x5acabc = *(uint32_t *)vec_a;
  *(uint32_t *)0x5acac0 = *(uint32_t *)((char *)vec_a + 4);
  *(uint32_t *)0x5acac4 = *(uint32_t *)((char *)vec_a + 8);
  *(uint32_t *)0x5acac8 = *(uint32_t *)vec_b;
  *(uint32_t *)0x5acacc = *(uint32_t *)((char *)vec_b + 4);
  *(uint32_t *)0x5acad0 = *(uint32_t *)((char *)vec_b + 8);
  *(uint32_t *)0x5acad4 = 0;
}

void ai_debug_communication_suppress(int a0, int a1)
{
  FUN_0004a460(a0, a1, (void *)0x5aca14, 0x39, 0x42ce0);
}

void ai_debug_communication_ignore(int a0, int a1)
{
  FUN_0004a460(a0, a1, (void *)0x5aca1c, 0x39, 0x42ce0);
}

void ai_debug_communication_focus(int a0, int a1)
{
  FUN_0004a460(a0, a1, (void *)0x5aca24, 0xd1, 0x1a67e0);
}

void ai_debug_idle_look_clear(int actor_handle)
{
  *(char *)0x6323d4 = (actor_handle != -1);
  *(int32_t *)0x6323d8 = actor_handle;
  *(uint16_t *)0x6323dc = 0;
}

void ai_debug_idle_look_addprop(int index, float value)
{
  if (index < 0 || index >= 0x200) {
    display_assert("index>=0 && index<MAXIMUM_AI_DEBUG_IDLE_LOOK_PROPS",
                   "c:\\halo\\SOURCE\\ai\\ai_debug.c", 0x2a1, 1);
    system_exit(-1);
  }
  *(float *)(0x62a3b8 + index * 0x40) = value;
}

void ai_debug_change_selected_encounter(int encounter_index)
{
  ai_debug_select_encounter(encounter_index);
}

void ai_debug_change_selected_actor(int actor_index)
{
  ai_debug_select_actor(*(int32_t *)0x5ac9f4, actor_index);
}

/* 0x490c0 */
void FUN_000490C0(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x49280 */
void FUN_00049280(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  FUN_00189450(0, (float *)(uintptr_t)ecx, (float *)(uintptr_t)eax, (void *)0, 0.0f);
  /* test (int16_t)esi, (int16_t)esi -> jle 0x492ee */
  /* test (int16_t)edi, (int16_t)edi -> jle 0x492cd */
  FUN_00189450(0, (float *)(uintptr_t)edx, (float *)(uintptr_t)esi, (void *)(uintptr_t)ebx, 0.0f);
  FUN_001893e0(0, (float *)(uintptr_t)esi, (float *)(uintptr_t)eax, 0.0f, (void *)(uintptr_t)ebx);
  /* relift: cmp (int16_t)edi, word ptr [ebp + 8] -> jl 0x492b3 */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x49300 */
void FUN_00049300(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  tag_block_get_element((void *)(uintptr_t)edx, 0, 12);
  tag_block_get_element((void *)(uintptr_t)ecx, 0, 24);
  tag_block_get_element((void *)0, 0, 0);
  tag_block_get_element((void *)(uintptr_t)edi, 0, 16);
  FUN_00189450(0, (float *)(uintptr_t)edx, (float *)(uintptr_t)eax, (void *)(uintptr_t)ecx, 0.0f);
  /* cmp esi, eax -> jne 0x49347 */

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x493b0 — store float + two dwords into a 12-byte record */
void FUN_000493B0(float *out, float value, int field_4, int field_8)
{
  *out = value;
  *(int *)((char *)out + 4) = field_4;
  *(int *)((char *)out + 8) = field_8;
}

/* 0x49430 */
void ai_debug_lineoffire_addpill(float *vec_a, float *vec_b, int param_3, char param_4)
{
  int eax = 0;

  /* test (char)eax, (char)eax -> jne 0x4945c */
  display_assert((char *)0x0025abd0, (char *)0x0025ab74, 4036, 0);
  system_exit(0);
  /* cmp eax, 0x10 -> jge 0x494ce */
  /* mem[0x005acad4] = eax */

  (void)eax;
}

/* 0x494e0 */
void FUN_000494e0(void)
{
  int eax = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* relift: relift: mov (char)eax, byte ptr [0x5acab8] */
  /* test (char)eax, (char)eax -> je 0x4959e */
  /* relift: relift: fld dword ptr [0x5acabc] */
  /* relift: relift: mov (char)eax, byte ptr [0x5acab9] */
  /* relift: relift: fld dword ptr [0x5acac0] */
  /* relift: relift: fld dword ptr [0x5acac4] */
  FUN_00189270(0, (void *)0x005acabc, (float *)(uintptr_t)eax, (void *)(uintptr_t)eax);
  /* test eax, eax -> jle 0x4959d */
  FUN_00189860(0, (void *)(uintptr_t)edi, (void *)(uintptr_t)edx, 0.0f, (void *)(uintptr_t)eax);
  /* cmp esi, eax -> jl 0x49560 */
  (void)eax;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x495b0 */
void FUN_000495b0(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;

  /* test (char)eax, (char)eax -> je 0x496b6 */
  FUN_00189150(0, (void *)0x005f8cb8, 0.0f, (void *)(uintptr_t)eax);
  FUN_00189320(0, (void *)0x005f8cb8, (void *)0x005f8cc4, 0.0f, (void *)(uintptr_t)ecx);
  /* test eax, eax -> jle 0x4964b */
  FUN_00189860(0, (void *)(uintptr_t)eax, (void *)(uintptr_t)edx, 0.0f, (void *)0);
  /* cmp eax, ecx -> jl 0x49610 */
  /* test edx, edx -> jle 0x496b5 */
  /* test dl, dl -> je 0x49672 */
  FUN_00189270(0, (float *)(uintptr_t)edx, (float *)(uintptr_t)ecx, (void *)0);
  /* cmp eax, edx -> jl 0x49660 */

  (void)eax;
  (void)ecx;
  (void)edx;
}

/* 0x496c0 */
char ai_debug_highlight_cluster(int16_t cluster_index, void *out)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;

  /* test (char)ecx, (char)ecx -> je 0x497ae */
  /* relift: cmp dword ptr [0x5ac9f4], -1 -> je 0x497ae */
  game_time_get();
  /* relift: cmp dword ptr [0x2c8e8c], edx -> je 0x49728 */
  FUN_00058fd0(0, 0, 512, 0, (char *)0x00331f18);
  game_time_get();
  /* mem[0x002c8e90] = eax */
  /* mem[0x002c8e8c] = edx */
  /* test esi, esi -> jne 0x49756 */
  display_assert((char *)0x0025abec, (char *)0x0025ab74, 4133, 0);
  system_exit(0);
  datum_get((void *)(uintptr_t)eax, 0);
  /* test (char)ecx, (char)ecx -> je 0x49797 */
  /* mem[0x005accac] = eax */
  /* mem[0x005eccb0] = eax */
  return 0;

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
}

/* 0x497c0 */
void FUN_000497c0(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int esi = 0;

  /* test ecx, ecx -> jle 0x4981d */
  /* relift: cmp word ptr [esi*2 + 0x5e4cb0], (int16_t)ebx -> jne 0x4980f */
  /* cmp esi, ecx -> jl 0x497d2 */
  /* cmp esi, ecx -> jl 0x4985a */
  /* cmp ecx, 0x4000 -> jge 0x49894 */
  /* mem[0x005accac] = ecx */
  /* cmp esi, -1 -> je 0x4988f */
  /* cmp esi, 0x7fff -> jle 0x49887 */
  display_assert((char *)0x0025ac50, (char *)0x0025ab74, 4223, 0);
  system_exit(0);
  /* test (char)eax, (char)eax -> jne 0x4988f */
  error(0, (char *)0x0025ac00);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)esi;
}

/* 0x498d0 */
void FUN_000498d0(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* cmp (int16_t)esi, -1 -> je 0x49987 */
  /* cmp (int16_t)edi, -1 -> je 0x49987 */
  /* test ecx, ecx -> jle 0x49919 */
  /* relift: cmp word ptr [edx - 2], (int16_t)esi -> jne 0x4990b */
  /* relift: cmp word ptr [edx], (int16_t)edi -> je 0x49915 */
  /* cmp eax, ecx -> jl 0x49900 */
  /* cmp eax, ecx -> jl 0x49946 */
  /* cmp ecx, 0x2000 -> jge 0x49958 */
  /* mem[0x005eccb0] = ecx */
  /* cmp eax, -1 -> je 0x49987 */
  /* test (char)eax, (char)eax -> jne 0x49985 */
  error(0, (char *)0x0025ac68);

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x49990 */
void FUN_00049990(void)
{
  int eax = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  crt_sprintf((char *)0x005ab100, (char *)0x0025acb8);
  /* cmp eax, 0xc -> jle 0x49a3d */
  FUN_00189cb0(0, (void *)(uintptr_t)edi, (void *)0x005ab100, 0);
  /* cmp esi, eax -> jl 0x49a10 */
  /* test eax, eax -> jle 0x49aba */
  /* cmp eax, 0xc -> jle 0x49a7e */
  FUN_00189270(0, (float *)(uintptr_t)edx, (float *)0, (void *)0);
  /* cmp edi, eax -> jl 0x49a71 */

  (void)eax;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x49ac0 */
char *ai_debug_describe_actor(int actor_handle, int object_handle, char with_actor, char *buf, int buf_size)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  csstrcpy((char *)(uintptr_t)eax, (char *)0x0025386f);
  /* test (char)eax, (char)eax -> je 0x49bbe */
  /* cmp eax, -1 -> je 0x49bbe */
  datum_get((void *)(uintptr_t)ecx, 0);
  csstrcpy((char *)(uintptr_t)eax, (char *)0x0025ace0);
  global_scenario_get();
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  tag_block_get_element((void *)(uintptr_t)edx, 0, 232);
  tag_block_get_element((void *)(uintptr_t)ecx, 0, 172);
  /* test eax, eax -> jne 0x49ba6 */
  crt_sprintf((char *)(uintptr_t)edx, (char *)0x0025acd8);
  crt_sprintf((char *)(uintptr_t)eax, (char *)0x0025accc);
  csstrcpy((char *)(uintptr_t)ecx, (char *)(uintptr_t)edi);
  /* cmp eax, -1 -> je 0x49c35 */
  object_get_and_verify_type(0, 0);
  tag_get('tinu', 0);
  tag_name_strip_path((char *)(uintptr_t)eax);
  global_scenario_get();
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  crt_sprintf((char *)(uintptr_t)edx, (char *)0x0025acc4);
  snprintf((char *)(uintptr_t)esi, edx, (char *)0x0025acbc);
  return NULL;

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x49c70 */
void FUN_00049c70(void)
{
  int eax = 0;
  int ebx = 0;
  int esi = 0;
  int ebp = 0;

  observer_get_camera(0);
  /* test esi, esi -> je 0x49d58 */
  director_get_perspective(0);
  /* test (int16_t)eax, (int16_t)eax -> jne 0x49cbb */
  local_player_get_player_index(0);
  datum_get((void *)(uintptr_t)eax, 0);
  FUN_0014df70(0, (float *)0, (float *)0, 0, (void *)0);
  /* relift: cmp word ptr [ebp - 0x5c], 3 -> jne 0x49d58 */
  /* cmp eax, -1 -> je 0x49d58 */
  object_try_and_get_and_verify_type(0, 0);
  /* test eax, eax -> je 0x49d58 */
  /* cmp ebx, -1 -> jne 0x49d58 */
  /* cmp eax, ebx -> je 0x49d58 */
  object_get_and_verify_type(0, 0);

  (void)eax;
  (void)ebx;
  (void)esi;
  (void)ebp;
}

/* 0x49d60 */
void FUN_00049d60(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int edi = 0;
  int ebp = 0;

  /* cmp eax, ecx -> je 0x49d8a */
  /* mem[0x006323b4] = eax */
  /* cmp eax, -1 -> je 0x49f50 */
  datum_get((void *)(uintptr_t)eax, 0);
  observer_get_camera(0);
  /* test eax, eax -> je 0x49e8c */
  normalize3d((float *)0);
  /* test (char)eax, 0x41 -> jne 0x49e8b */
  FUN_00027f40(0, (void *)(uintptr_t)ecx, (void *)(uintptr_t)eax, (void *)(uintptr_t)edx);
  /* mem[0x006323c8] = ecx */
  /* mem[0x006323cc] = eax */
  /* mem[0x006323d0] = edx */
  /* relift: cmp byte ptr [ebp - 2], 0 -> je 0x49e56 */
  /* mem[0x006323bc] = ecx */
  /* mem[0x006323c0] = eax */
  /* mem[0x006323c4] = edx */
  FUN_00189320(0, (float *)(uintptr_t)edi, (float *)(uintptr_t)ecx, 0.0f, (void *)(uintptr_t)eax);
  FUN_00189320(0, (float *)(uintptr_t)edi, (float *)(uintptr_t)eax, 0.0f, (void *)(uintptr_t)edx);
  /* test (char)eax, (char)eax -> je 0x49eee */
  FUN_00189320(0, (float *)0, (float *)0, 0.0f, (void *)0);
  /* test (char)eax, (char)eax -> je 0x49f4f */
  FUN_00189320(0, (float *)0, (float *)0, 0.0f, (void *)0);

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)edi;
  (void)ebp;
}

/* 0x49f60 */
void ai_debug_vocalize(int a0, int a1)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;

  /* cmp eax, esi -> je 0x4a020 */
  datum_get((void *)(uintptr_t)eax, 0);
  /* cmp eax, esi -> je 0x4a01e */
  FUN_001a6cd0((char *)(uintptr_t)ecx);
  FUN_001a67e0((char *)(uintptr_t)edx);
  /* cmp (int16_t)eax, (int16_t)esi -> je 0x4a01e */
  FUN_001a68d0(0, 0, 0, 0, (void *)0, (void *)(uintptr_t)ecx, (void *)(uintptr_t)eax);
  /* test (int16_t)esi, (int16_t)esi -> je 0x4a01e */
  csmemset((void *)(uintptr_t)eax, 0, 48);
  ai_communication_packet_new((void *)(uintptr_t)eax);
  FUN_001a6ef0(0, 0, (void *)(uintptr_t)ecx);

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
}

/* 0x4a030 */
void FUN_0004a030(void)
{
  int eax = 0;
  int ecx = 0;
  int esi = 0;

  /* test (char)eax, (char)eax -> je 0x4a215 */
  /* cmp eax, -1 -> je 0x4a215 */
  object_try_and_get_and_verify_type(0, 0);
  /* test eax, eax -> je 0x4a20e */
  /* relift: test byte ptr [eax + 0xb6], 4 -> jne 0x4a20e */
  /* relift: cmp word ptr [eax + 0x338], 0 -> jne 0x4a215 */
  /* test (int16_t)eax, (int16_t)eax -> jle 0x4a095 */
  /* test (int16_t)eax, (int16_t)eax -> jne 0x4a215 */
  /* test (int16_t)eax, (int16_t)eax -> jl 0x4a1ff */
  /* cmp (int16_t)eax, 0xd1 -> jge 0x4a1f4 */
  FUN_001a68d0(0, 0, 0, 0, (void *)0, (void *)(uintptr_t)ecx, (void *)(uintptr_t)eax);
  /* cmp (int16_t)esi, 2 -> jl 0x4a163 */
  csmemset((void *)(uintptr_t)eax, 0, 48);
  ai_communication_packet_new((void *)(uintptr_t)eax);
  FUN_001a6ef0(0, 0, (void *)(uintptr_t)ecx);
  /* cmp eax, -1 -> je 0x4a163 */
  tag_get_name(0);
  crt_strstr((char *)(uintptr_t)esi, (char *)0x0025ad10);
  /* test eax, eax -> je 0x4a168 */
  crt_strchr((char *)(uintptr_t)eax, 92);
  /* test eax, eax -> je 0x4a168 */
  FUN_001a67b0(0, 0);
  console_printf(0, (char *)0x00259f2c);
  FUN_001a67b0(0, 0);
  csstrcmp((char *)(uintptr_t)eax, (char *)0);
  /* test eax, eax -> jne 0x4a1ee */
  /* test (char)eax, (char)eax -> je 0x4a1e3 */
  /* cmp (int16_t)eax, 0xd1 -> jl 0x4a1a7 */
  /* test (int16_t)eax, (int16_t)eax -> jl 0x4a1ff */
  /* cmp (int16_t)eax, 0xd1 -> jl 0x4a215 */
  console_printf(0, (char *)0x0025acf4);

  (void)eax;
  (void)ecx;
  (void)esi;
}

/* 0x4a220 */
void ai_debug_speak(int a0)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;

  /* cmp eax, -1 -> je 0x4a283 */
  datum_get((void *)(uintptr_t)eax, 0);
  FUN_001a67e0((char *)(uintptr_t)ecx);
  /* cmp ecx, -1 -> je 0x4a282 */
  /* cmp (int16_t)eax, 0xffff -> je 0x4a282 */
  /* mem[0x006324e4] = edx */

  (void)eax;
  (void)ecx;
  (void)edx;
}

/* 0x4a290 */
void ai_debug_speak_list(int a0)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* cmp eax, -1 -> je 0x4a457 */
  datum_get((void *)(uintptr_t)eax, 0);
  crt_stricmp((char *)(uintptr_t)eax, (char *)(uintptr_t)ecx);
  /* test eax, eax -> je 0x4a3cd */
  /* cmp eax, ebx -> jne 0x4a3b0 */
  /* relift: cmp dword ptr [esi], ebx -> jne 0x4a410 */
  console_printf(0, (char *)0x0025ad28);
  console_printf(0, (char *)0x0025ad1c);
  /* cmp eax, ebx -> jne 0x4a3f0 */
  /* relift: cmp dword ptr [edi + 0x18], -1 -> je 0x4a454 */
  /* cmp (int16_t)eax, 0xffff -> je 0x4a454 */
  /* mem[0x006324e4] = edx */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x4a770 */
void FUN_0004a770(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int edi = 0;

  /* test (char)eax, (char)eax -> je 0x4a8b3 */
  datum_absolute_index_to_index((void *)(uintptr_t)ecx, 0);
  /* test edi, edi -> je 0x4a8b1 */
  /* relift: cmp word ptr [0x6323dc], (int16_t)ebx -> jle 0x4a8b1 */
  datum_absolute_index_to_index((void *)(uintptr_t)eax, 0);
  /* test eax, eax -> je 0x4a8a2 */
  /* relift: cmp word ptr [edi + 0x56c], 1 -> jne 0x4a86f */
  csprintf((char *)0x005ab100, (char *)0x0025aec8);
  FUN_00189cb0(0, (void *)(uintptr_t)edx, (void *)(uintptr_t)eax, 0);
  /* relift: cmp (int16_t)ebx, word ptr [0x6323dc] -> jl 0x4a7b4 */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)edi;
}

/* 0x4a8c0 */
void FUN_0004a8c0(void)
{
  int eax = 0;
  int ebx = 0;
  int edx = 0;
  int esi = 0;

  game_time_get();
  /* cmp (int16_t)eax, 0xffff -> je 0x4a9c6 */
  /* cmp (int16_t)eax, 3 -> jge 0x4a949 */
  FUN_00189540(0, (void *)(uintptr_t)esi, 0.0f, (void *)(uintptr_t)ebx);
  csprintf((char *)0, (char *)0);
  FUN_00189cb0(0, (void *)(uintptr_t)edx, (void *)(uintptr_t)eax, 0);

  (void)eax;
  (void)ebx;
  (void)edx;
  (void)esi;
}

/* 0x4a9f0 */
void FUN_0004a9f0(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* test (char)eax, (char)eax -> je 0x4aae1 */
  /* test (char)eax, (char)eax -> je 0x4aae1 */
  /* cmp (int16_t)ebx, 0x20 -> jge 0x4aae1 */
  /* test (char)eax, (char)eax -> je 0x4aad0 */
  /* test (char)eax, (char)eax -> je 0x4aad0 */
  /* relift: cmp ecx, dword ptr [edi] -> jne 0x4aad0 */
  /* relift: cmp (char)eax, byte ptr [esi + 0x60] -> jne 0x4aad0 */
  /* test (char)eax, (char)eax -> je 0x4aac4 */
  distance_squared3d((float *)(uintptr_t)eax, (float *)(uintptr_t)edx);
  /* relift: cmp ecx, dword ptr [esi + 4] -> jl 0x4aadd */
  /* cmp (int16_t)ebx, 0x20 -> jl 0x4aa40 */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x4b0f0 */
void ai_debug_teleport_to(int actor_index)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* cmp eax, -1 -> je 0x4b1a7 */
  global_scenario_get();
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  /* test eax, eax -> jle 0x4b1a4 */
  data_iterator_new((void *)(uintptr_t)ecx, (void *)(uintptr_t)eax);
  data_iterator_next((void *)(uintptr_t)edx);
  /* test esi, esi -> je 0x4b1a4 */
  /* relift: cmp dword ptr [esi + 0x34], -1 -> je 0x4b192 */
  tag_block_get_element((void *)(uintptr_t)edi, 0, 52);
  object_set_position(0, (float *)0, (float *)0, (float *)0);
  data_iterator_next((void *)(uintptr_t)eax);
  /* test esi, esi -> jne 0x4b152 */

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x4b220 */
void FUN_0004b220(void)
{
  int ecx = 0;
  int edx = 0;
  int esi = 0;

  observer_get_camera(0);
  /* mem[0x005ac9a0] = ecx */
  /* mem[0x005ac9a4] = edx */
  /* mem[0x005ac9a8] = esi */
  /* mem[0x005ac9b8] = esi */
  /* mem[0x005ac9b0] = ecx */
  /* mem[0x005ac9b4] = edx */
  /* mem[0x005ac990] = 0x3d4ccccd */

  (void)ecx;
  (void)edx;
  (void)esi;
}

/* 0x4b2b0 */
void FUN_0004b2b0(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x4b320 */
void FUN_0004b320(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  observer_get_camera(0);
  /* test eax, eax -> je 0x4b42d */
  FUN_00189450(0, (float *)(uintptr_t)esi, (float *)(uintptr_t)edi, (void *)(uintptr_t)eax, 0.0f);
  FUN_001893e0(0, (float *)(uintptr_t)esi, (float *)(uintptr_t)ecx, 0.0f, (void *)(uintptr_t)eax);
  /* test eax, eax -> jne 0x4b42a */
  FUN_001893e0(0, (float *)(uintptr_t)edi, (float *)(uintptr_t)eax, 0.0f, (void *)(uintptr_t)edx);
  /* test eax, eax -> je 0x4b450 */
  /* test dl, dl -> je 0x4b450 */
  FUN_00049300();
  /* test eax, eax -> je 0x4b4ad */
  csprintf((char *)0x005ab100, (char *)0x0025afc4);
  FUN_00189cb0(0, (void *)(uintptr_t)edx, (void *)(uintptr_t)eax, 0);
  /* test eax, eax -> je 0x4b590 */
  FUN_00189150(0, (float *)(uintptr_t)eax, 0.0f, (void *)(uintptr_t)ecx);
  csprintf((char *)0x005ab100, (char *)0x0025afc4);
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)(uintptr_t)eax, 0);
  /* test ebx, ebx -> je 0x4b667 */
  /* test (char)eax, (char)eax -> je 0x4b667 */
  /* relift: path_attractor_weight(...) */
  /* test eax, eax -> je 0x4b61f */
  csprintf((char *)0x005ab100, (char *)0x0025afc4);
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)(uintptr_t)eax, 0);
  /* test eax, eax -> je 0x4b667 */
  /* test (char)eax, 0x41 -> jne 0x4b667 */
  csprintf((char *)0x005ab100, (char *)0x0025afc4);
  FUN_00189cb0(0, (void *)(uintptr_t)edx, (void *)(uintptr_t)eax, 0);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x4b670 */
void FUN_0004b670(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  object_try_and_get_and_verify_type(0, 0);
  /* test esi, esi -> je 0x4b761 */
  object_try_and_get_and_verify_type(0, 0);
  /* test eax, eax -> je 0x4b6c9 */
  /* relift: cmp dword ptr [eax + 0x2d4], edi -> jne 0x4b6c9 */
  FUN_0001aae0(0, (float *)(uintptr_t)edx, (float *)(uintptr_t)ecx);
  biped_get_camera_height_and_offset(0, (void *)(uintptr_t)eax, (float *)(uintptr_t)edx, (float *)(uintptr_t)ecx);
  /* test (char)eax, (char)eax -> je 0x4b722 */
  /* test (char)eax, 0x41 -> jne 0x4b722 */
  FUN_00189860(0, (void *)(uintptr_t)ecx, (void *)(uintptr_t)eax, 0.0f, (void *)(uintptr_t)ebx);
  FUN_00189540(0, (void *)(uintptr_t)edx, 0.0f, (void *)0);
  /* test (char)eax, (char)eax -> je 0x4b761 */
  FUN_00189150(0, (float *)(uintptr_t)eax, 0.0f, (void *)0);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x4b770 */
void ai_debug_lineofsight(void)
{
  FUN_000497c0();
  FUN_000497c0();
  FUN_000498d0();
}

/* 0x4b7a0 */
void FUN_0004b7a0(void)
{
  int eax = 0;
  int esi = 0;

  FUN_00049c70();
  /* cmp esi, -1 -> je 0x4b7f8 */
  datum_get((void *)(uintptr_t)eax, 0);
  ai_debug_describe_actor(0, 0, 0, (char *)0x005ab100, 256);
  console_printf(0, (char *)0x0025afd0);
  ai_debug_select_actor(0, 0);
  ai_debug_select_actor(0, 0);

  (void)eax;
  (void)esi;
}

/* FUN_0004b810 (0x4b810) — XBE naked draft (batch 108). */
#if defined(__clang__)
static void (*const b4b810_c13d6f0)(void *iter, int type_mask, int flags) = object_iterator_new;
static void * (*const b4b810_c13d730)(void *iter) = object_iterator_next;
static void (*const b4b810_c1a9200)(int object_handle, float *out_position) = unit_get_head_position;
static void (*const b4b810_c4b220)(void) = FUN_0004b220;
static void *(*const b4b810_tag)(int, int) = tag_get;
static void *(*const b4b810_elem)(void *, int, int) = tag_block_get_element;
static const char * (*const b4b810_c1ba1f0)(int tag_index) = tag_get_name;
static const char * (*const b4b810_c19b0d0)(const char *tag_name) = tag_name_strip_path;
static char * (*const b4b810_c8d9d0)(char *buffer, const char *format, ...) = csprintf;
static void (*const b4b810_c189cb0)(char flag, void *position, void *string, int color) = FUN_00189cb0;
static char * (*const b4b810_c1a67b0)(short param_1, unsigned char param_2) = FUN_001a67b0;
static char * (*const b4b810_c1a6ca0)(short param_1) = FUN_001a6ca0;
static char * (*const b4b810_c1a6d10)(int unit_handle, char full_path, int16_t max_len, char *output) = FUN_001a6d10;
static void (*const b4b810_c4b2b0)(void) = FUN_0004b2b0;

__attribute__((naked, noinline))
void FUN_0004b810(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x230, %%esp\n\t"
      "pushl %%esi\n\t"
      "pushl $0\n\t"
      "leal -0x30(%%ebp), %%eax\n\t"
      "pushl $3\n\t"
      "pushl %%eax\n\t"
      "call *%[c13d6f0]\n\t"
      "leal -0x30(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c13d730]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $0x10, %%esp\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_0004b810_22\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "nop\n\t"
      ".LFUN_0004b810_1:\n\t"
      "movl -0x28(%%ebp), %%eax\n\t"
      "leal -0x14(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c1a9200]\n\t"
      "movl 0x31fc44, %%eax\n\t"
      "flds (%%eax)\n\t"
      "addl $8, %%esp\n\t"
      "fmuls 0x25496c\n\t"
      "fadds -0x14(%%ebp)\n\t"
      "fstps -0x20(%%ebp)\n\t"
      "flds 0x4(%%eax)\n\t"
      "fmuls 0x25496c\n\t"
      "fadds -0x10(%%ebp)\n\t"
      "fstps -0x1c(%%ebp)\n\t"
      "flds 0x8(%%eax)\n\t"
      "leal -0x20(%%ebp), %%eax\n\t"
      "fmuls 0x25496c\n\t"
      "fadds -0xc(%%ebp)\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "call *%[c4b220]\n\t"
      "movb 0x5aca93, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0004b810_6\n\t"
      "movl (%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x756e6974\n\t"
      "call *%[tag]\n\t"
      "leal 0x2b4(%%eax), %%edi\n\t"
      "movl (%%edi), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jle .LFUN_0004b810_6\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "testl %%eax, %%eax\n\t"
      "movl $0x25ad08, -0x4(%%ebp)\n\t"
      "movl $0xffffffff, -0x8(%%ebp)\n\t"
      "jle .LFUN_0004b810_4\n\t"
      "xorl %%eax, %%eax\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_0004b810_2:\n\t"
      "pushl $0x18\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "call *%[elem]\n\t"
      "movl 0x14(%%eax), %%edx\n\t"
      "movl 0x334(%%esi), %%ecx\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl %%ecx, %%edx\n\t"
      "je .LFUN_0004b810_3\n\t"
      "movl (%%edi), %%ecx\n\t"
      "incl %%ebx\n\t"
      "movswl %%bx, %%eax\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jl .LFUN_0004b810_2\n\t"
      "jmp .LFUN_0004b810_4\n\t"
      ".LFUN_0004b810_3:\n\t"
      "movw (%%eax), %%ax\n\t"
      "movw %%ax, -0x8(%%ebp)\n\t"
      ".LFUN_0004b810_4:\n\t"
      "movl 0x334(%%esi), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_0004b810_5\n\t"
      "pushl %%eax\n\t"
      "call *%[c1ba1f0]\n\t"
      "pushl %%eax\n\t"
      "call *%[c19b0d0]\n\t"
      "addl $8, %%esp\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      ".LFUN_0004b810_5:\n\t"
      "movl 0x5ac9b8, %%eax\n\t"
      "flds 0x5ac990\n\t"
      "movl 0x5ac9b0, %%ecx\n\t"
      "movl 0x5ac9b4, %%edx\n\t"
      "movl %%eax, 0x5ac9a8\n\t"
      "movl 0x31fc44, %%eax\n\t"
      "movl %%edx, 0x5ac9a4\n\t"
      "movl %%ecx, 0x5ac9a0\n\t"
      "fmuls (%%eax)\n\t"
      "movl 0x2ee6e8, %%ecx\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "fadds 0x5ac9b0\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "fstps 0x5ac9b0\n\t"
      "flds 0x5ac990\n\t"
      "fmuls 0x4(%%eax)\n\t"
      "fadds 0x5ac9a4\n\t"
      "fstps 0x5ac9b4\n\t"
      "flds 0x5ac990\n\t"
      "fmuls 0x8(%%eax)\n\t"
      "movswl -0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "fadds 0x5ac9a8\n\t"
      "fstps 0x5ac9b8\n\t"
      "movswl 0x6e(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x25affc\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x14, %%esp\n\t"
      "pushl %%eax\n\t"
      "pushl $0x5ac9a0\n\t"
      "pushl $1\n\t"
      "call *%[c189cb0]\n\t"
      "addl $0x10, %%esp\n\t"
      ".LFUN_0004b810_6:\n\t"
      "movb 0x5aca89, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0004b810_16\n\t"
      "cmpw $0, 0x338(%%esi)\n\t"
      "jle .LFUN_0004b810_11\n\t"
      "movl 0x33c(%%esi), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "jne .LFUN_0004b810_7\n\t"
      "movl $0x253a04, %%edi\n\t"
      "jmp .LFUN_0004b810_8\n\t"
      ".LFUN_0004b810_7:\n\t"
      "pushl %%eax\n\t"
      "call *%[c1ba1f0]\n\t"
      "pushl %%eax\n\t"
      "call *%[c19b0d0]\n\t"
      "addl $8, %%esp\n\t"
      "movl %%eax, %%edi\n\t"
      ".LFUN_0004b810_8:\n\t"
      "movw 0x33a(%%esi), %%ax\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "jne .LFUN_0004b810_9\n\t"
      "movl $0x253a04, %%eax\n\t"
      "jmp .LFUN_0004b810_10\n\t"
      ".LFUN_0004b810_9:\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "call *%[c1a67b0]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_0004b810_10:\n\t"
      "movl 0x5ac9b0, %%edx\n\t"
      "flds 0x5ac990\n\t"
      "movl 0x5ac9b4, %%ecx\n\t"
      "movl %%edx, 0x5ac9a0\n\t"
      "movl 0x5ac9b8, %%edx\n\t"
      "movl %%ecx, 0x5ac9a4\n\t"
      "movl 0x31fc44, %%ecx\n\t"
      "movl %%edx, 0x5ac9a8\n\t"
      "fmuls (%%ecx)\n\t"
      "fadds 0x5ac9b0\n\t"
      "fstps 0x5ac9b0\n\t"
      "flds 0x5ac990\n\t"
      "fmuls 0x4(%%ecx)\n\t"
      "fadds 0x5ac9a4\n\t"
      "fstps 0x5ac9b4\n\t"
      "flds 0x5ac990\n\t"
      "fmuls 0x8(%%ecx)\n\t"
      "movl 0x2ee6c4, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "fadds 0x5ac9a8\n\t"
      "fstps 0x5ac9b8\n\t"
      "movswl 0x3ae(%%esi), %%edx\n\t"
      "movswl 0x3aa(%%esi), %%ecx\n\t"
      "pushl %%edx\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x338(%%esi), %%dx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "pushl %%edx\n\t"
      "call *%[c1a6ca0]\n\t"
      "addl $4, %%esp\n\t"
      "pushl %%eax\n\t"
      "pushl $0x25afe8\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x1c, %%esp\n\t"
      "pushl %%eax\n\t"
      "pushl $0x5ac9a0\n\t"
      "pushl $1\n\t"
      "call *%[c189cb0]\n\t"
      "addl $0x10, %%esp\n\t"
      ".LFUN_0004b810_11:\n\t"
      "cmpw $0, 0x368(%%esi)\n\t"
      "jle .LFUN_0004b810_16\n\t"
      "movl 0x36c(%%esi), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "jne .LFUN_0004b810_12\n\t"
      "movl $0x253a04, %%edi\n\t"
      "jmp .LFUN_0004b810_13\n\t"
      ".LFUN_0004b810_12:\n\t"
      "pushl %%eax\n\t"
      "call *%[c1ba1f0]\n\t"
      "pushl %%eax\n\t"
      "call *%[c19b0d0]\n\t"
      "addl $8, %%esp\n\t"
      "movl %%eax, %%edi\n\t"
      ".LFUN_0004b810_13:\n\t"
      "movw 0x36a(%%esi), %%ax\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "jne .LFUN_0004b810_14\n\t"
      "movl $0x253a04, %%eax\n\t"
      "jmp .LFUN_0004b810_15\n\t"
      ".LFUN_0004b810_14:\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "call *%[c1a67b0]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_0004b810_15:\n\t"
      "movl 0x5ac9b0, %%ecx\n\t"
      "flds 0x5ac990\n\t"
      "movl 0x5ac9b4, %%edx\n\t"
      "movl %%ecx, 0x5ac9a0\n\t"
      "movl 0x5ac9b8, %%ecx\n\t"
      "movl %%ecx, 0x5ac9a8\n\t"
      "movl 0x31fc44, %%ecx\n\t"
      "movl %%edx, 0x5ac9a4\n\t"
      "fmuls (%%ecx)\n\t"
      "movl 0x2ee6e0, %%edx\n\t"
      "pushl %%edx\n\t"
      "fadds 0x5ac9b0\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "xorl %%eax, %%eax\n\t"
      "fstps 0x5ac9b0\n\t"
      "flds 0x5ac990\n\t"
      "fmuls 0x4(%%ecx)\n\t"
      "fadds 0x5ac9a4\n\t"
      "fstps 0x5ac9b4\n\t"
      "flds 0x5ac990\n\t"
      "fmuls 0x8(%%ecx)\n\t"
      "fadds 0x5ac9a8\n\t"
      "fstps 0x5ac9b8\n\t"
      "movw 0x368(%%esi), %%ax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1a6ca0]\n\t"
      "addl $4, %%esp\n\t"
      "pushl %%eax\n\t"
      "pushl $0x25afdc\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x14, %%esp\n\t"
      "pushl %%eax\n\t"
      "pushl $0x5ac9a0\n\t"
      "pushl $1\n\t"
      "call *%[c189cb0]\n\t"
      "addl $0x10, %%esp\n\t"
      ".LFUN_0004b810_16:\n\t"
      "movb 0x5aca53, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0004b810_21\n\t"
      "movb 0x5aca89, %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_0004b810_21\n\t"
      "movw 0x338(%%esi), %%si\n\t"
      "testw %%si, %%si\n\t"
      "jle .LFUN_0004b810_21\n\t"
      "movswl %%si, %%eax\n\t"
      "addl $-2, %%eax\n\t"
      "cmpl $8, %%eax\n\t"
      "ja .LFUN_0004b810_19\n\t"
      "movzbl 0x4bc60(%%eax), %%ecx\n\t"
      "jmp *.LFUN_0004b810_jt(,%%ecx,4)\n\t"
      ".LFUN_0004b810_17:\n\t"
      "movl 0x2ee6d0, %%eax\n\t"
      "jmp .LFUN_0004b810_20\n\t"
      ".LFUN_0004b810_18:\n\t"
      "movl 0x2ee6d8, %%eax\n\t"
      "jmp .LFUN_0004b810_20\n\t"
      ".LFUN_0004b810_19:\n\t"
      "movl 0x2ee6c4, %%eax\n\t"
      ".LFUN_0004b810_20:\n\t"
      "pushl %%eax\n\t"
      "movl -0x28(%%ebp), %%eax\n\t"
      "leal -0x230(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x200\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "call *%[c1a6d10]\n\t"
      "addl $0x10, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[c4b2b0]\n\t"
      "pushl %%eax\n\t"
      "pushl $1\n\t"
      "call *%[c189cb0]\n\t"
      "addl $0x10, %%esp\n\t"
      ".LFUN_0004b810_21:\n\t"
      "leal -0x30(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c13d730]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $4, %%esp\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LFUN_0004b810_1\n\t"
      "popl %%edi\n\t"
      "popl %%ebx\n\t"
      ".LFUN_0004b810_22:\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_0004b810_jt:\n\t"
      ".long .LFUN_0004b810_17\n\t"
      ".long .LFUN_0004b810_18\n\t"
      ".long .LFUN_0004b810_19\n\t"
      ".text\n\t"
      :
      : [c13d6f0] "m"(b4b810_c13d6f0), [c13d730] "m"(b4b810_c13d730), [c1a9200] "m"(b4b810_c1a9200), [c4b220] "m"(b4b810_c4b220), [tag] "m"(b4b810_tag), [elem] "m"(b4b810_elem), [c1ba1f0] "m"(b4b810_c1ba1f0), [c19b0d0] "m"(b4b810_c19b0d0), [c8d9d0] "m"(b4b810_c8d9d0), [c189cb0] "m"(b4b810_c189cb0), [c1a67b0] "m"(b4b810_c1a67b0), [c1a6ca0] "m"(b4b810_c1a6ca0), [c1a6d10] "m"(b4b810_c1a6d10), [c4b2b0] "m"(b4b810_c4b2b0)
      : "memory");
}
#else
#error "FUN_0004b810: clang naked draft required"
#endif


/* 0x4bc70 */
void FUN_0004bc70(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* relift: cmp word ptr [edi + 0x3b6], (int16_t)esi -> jle 0x4c0de */
  object_try_and_get_and_verify_type(0, 0);
  /* test eax, eax -> je 0x4c0c9 */
  object_get_world_position(0, (void *)(uintptr_t)edx);
  FUN_0004b220();
  csprintf((char *)0x005ab100, (char *)0x0025b098);
  FUN_0004b2b0();
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)0, 0);
  /* relift: cmp word ptr [edi + 8], 0 -> je 0x4be76 */
  crt_sprintf((char *)0x005ab100, (char *)0x0025b090);
  /* test ecx, eax -> je 0x4bde3 */
  FUN_0008dc30((char *)0x005ab100, (char *)0x0025b06c);
  FUN_0008dc30((char *)0x005ab100, (char *)(uintptr_t)eax);
  /* mem[0x005ac9a8] = eax */
  /* mem[0x005ac9a0] = ecx */
  /* mem[0x005ac9a4] = edx */
  FUN_00189cb0(0, (void *)0, (void *)0, 0);
  /* relift: cmp word ptr [edi + 0xa], 0 -> je 0x4bfd2 */
  crt_sprintf((char *)0x005ab100, (char *)0x0025b05c);
  /* test ecx, edx -> je 0x4bf43 */
  FUN_0008dc30((char *)0x005ab100, (char *)0x0025b06c);
  FUN_0008dc30((char *)0x005ab100, (char *)(uintptr_t)edx);
  /* mem[0x005ac9a0] = eax */
  /* mem[0x005ac9a4] = ecx */
  /* mem[0x005ac9a8] = edx */
  FUN_00189cb0(0, (void *)0, (void *)0, 0);
  /* relift: cmp word ptr [edi + 0xc], 0 -> jle 0x4c0c9 */
  crt_sprintf((char *)0x005ab100, (char *)0x0025b018);
  /* relift: cmp word ptr [edi + 0xc], (int16_t)esi -> jle 0x4c049 */
  global_scenario_get();
  FUN_00054220(eax, (void *)(uintptr_t)eax, (char *)0, 0);
  FUN_0008dc30((char *)0x005ab100, (char *)0x0025b06c);
  FUN_0008dc30((char *)0x005ab100, (char *)(uintptr_t)ecx);
  /* relift: cmp (int16_t)esi, word ptr [edi + 0xc] -> jl 0x4c000 */
  /* mem[0x005ac9a4] = eax */
  /* mem[0x005ac9a0] = edx */
  /* mem[0x005ac9a8] = ecx */
  FUN_00189cb0(0, (void *)0, (void *)0, 0);
  /* relift: cmp (int16_t)esi, word ptr [edi + 0x3b6] -> jl 0x4bc91 */

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x4c2a0 */
void FUN_0004c2a0(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  path_node_from_hash_table((char *)(uintptr_t)esi, edx);
  /* cmp (int16_t)eax, 0xffff -> je 0x4c375 */
  path_get_node((char *)(uintptr_t)esi, 0);
  FUN_0004b320();
  /* test (char)eax, (char)eax -> je 0x4c559 */
  tag_block_get_element((void *)(uintptr_t)ecx, 0, 0);
  path_get_node((char *)(uintptr_t)esi, 0);
  /* relift: cmp (int16_t)edx, word ptr [0x331f60] -> je 0x4c527 */
  /* test (char)eax, (char)eax -> je 0x4c4bd */
  tag_block_get_element((void *)(uintptr_t)edx, 0, 12);
  tag_block_get_element((void *)(uintptr_t)edx, 0, 24);
  tag_block_get_element((void *)(uintptr_t)edx, 0, 16);
  /* relift: cmp eax, dword ptr [ecx + 4] -> jne 0x4c434 */
  FUN_0004b320();
  /* cmp (int16_t)ebx, -1 -> jne 0x4c3c1 */
  /* test edi, edi -> je 0x4c549 */
  FUN_00189450(0, (float *)(uintptr_t)edi, (float *)0, (void *)0, 0.0f);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x4c560 */
void FUN_0004c560(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* test esi, esi -> je 0x4c884 */
  /* test (char)eax, (char)eax -> je 0x4c884 */
  /* relift: cmp eax, dword ptr [0x5acab4] -> je 0x4c884 */
  global_structure_bsp_index_get();
  /* cmp (int16_t)eax, 6 -> jl 0x4c612 */
  display_assert((char *)0x0025b170, (char *)0x0025ab74, 3944, 0);
  system_exit(0);
  /* test (int16_t)eax, (int16_t)eax -> jl 0x4c621 */
  /* cmp (int16_t)eax, 6 -> jl 0x4c641 */
  display_assert((char *)0x0025b110, (char *)0x0025ab74, 3945, 0);
  system_exit(0);
  /* relift: cmp word ptr [esi + 0x10], (int16_t)eax -> jne 0x4c657 */
  game_time_get();
  csprintf((char *)0x005ab100, (char *)0x0025b100);
  FUN_0004b2b0();
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)0, 0);
  /* test (char)eax, (char)eax -> je 0x4c751 */
  /* test (char)eax, (char)eax -> je 0x4c735 */
  FUN_00189450(0, (float *)(uintptr_t)eax, (float *)(uintptr_t)edi, (void *)(uintptr_t)edx, 0.0f);
  FUN_00189150(0, (float *)(uintptr_t)edi, 0.0f, (void *)(uintptr_t)ecx);
  /* test (char)eax, 0x41 -> jne 0x4c70e */
  FUN_00189540(0, (void *)(uintptr_t)edi, 0.0f, (void *)(uintptr_t)edx);
  /* test (char)ebx, (char)ebx -> je 0x4c751 */
  FUN_00049300();
  FUN_0004b2b0();
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)0, 0);
  /* test (char)eax, (char)eax -> je 0x4c77c */
  FUN_00049280();
  /* test (char)eax, (char)eax -> je 0x4c7a7 */
  FUN_00049280();
  /* test (char)eax, (char)eax -> je 0x4c7d2 */
  FUN_00049280();
  /* relift: cmp (int16_t)eax, word ptr [esi + 0x1458a] -> jge 0x4c84a */
  /* test (char)ecx, (char)ecx -> je 0x4c820 */
  path_obstacles_debug_render((void *)(uintptr_t)eax, 0.0f);
  /* test (char)ecx, (char)ecx -> je 0x4c84a */
  /* test (char)ecx, (char)ecx -> je 0x4c84a */
  FUN_000609e0((void *)(uintptr_t)edx);
  /* test (char)eax, (char)eax -> je 0x4c87c */
  FUN_0004c2a0();

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x4c890 */
void FUN_0004c890(void)
{
  int eax = 0;

  /* test (char)eax, (char)eax -> je 0x4c8fb */
  /* test (char)eax, (char)eax -> je 0x4c8fb */
  /* test (char)eax, (char)eax -> jne 0x4c8fb */
  /* test (char)eax, (char)eax -> jne 0x4c8c4 */
  /* test (char)eax, (char)eax -> jne 0x4c8c4 */
  /* test (int16_t)eax, (int16_t)eax -> jne 0x4c8d6 */
  FUN_00189270(0, (void *)0x005f91ac, (void *)0x005f91c4, (void *)(uintptr_t)eax);
  /* test (char)eax, (char)eax -> je 0x4c91a */
  FUN_0004b220();
  FUN_0004c560();

  (void)eax;
}

/* 0x4c920 */
void FUN_0004c920(int actor_handle, char debug_selected, void *debug_context)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  (void)debug_selected;
  (void)debug_context;

  datum_get((void *)(uintptr_t)eax, 0);
  tag_get('rtca', 0);
  tag_get('vtca', 0);
  FUN_000490C0();
  object_get_and_verify_type(0, 0);
  tag_get('tinu', 0);
  /* test edi, edi -> je 0x4ca0a */
  /* relift: cmp word ptr [esi + 0x6e], 2 -> jl 0x4ca0a */
  /* cmp eax, -1 -> je 0x4ca0a */
  datum_get((void *)(uintptr_t)eax, 0);
  /* cmp ecx, -1 -> je 0x4ca05 */
  /* relift: cmp dword ptr [eax + 0x7c], ecx -> jge 0x4ca0a */
  FUN_0004b220();
  /* test (char)eax, (char)eax -> je 0x4cac4 */
  /* cmp eax, -1 -> je 0x4cade */
  datum_get((void *)(uintptr_t)edx, 0);
  actor_action_debug_color(0);
  FUN_0004b670();
  actor_action_debug_color(0);
  FUN_0004b670();
  /* test (char)eax, (char)eax -> je 0x4cbd0 */
  /* relift: test dword ptr [edx], 0xc0000000 -> je 0x4cbd0 */
  /* test (char)eax, (char)eax -> jne 0x4cb18 */
  /* test (char)ecx, (char)ecx -> jne 0x4cb22 */
  /* test (char)ecx, (char)ecx -> je 0x4cb79 */
  /* test (char)ecx, (char)ecx -> je 0x4cb29 */
  /* test dl, dl -> je 0x4cb3f */
  csprintf((char *)0x005ab100, (char *)0x0025bf84);
  FUN_0004b2b0();
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)0, 0);
  /* test (char)eax, (char)eax -> jne 0x4cb91 */
  /* relift: cmp word ptr [esi + 0x360], 0 -> jle 0x4cbd0 */
  /* test (char)eax, (char)eax -> je 0x4cb98 */
  csprintf((char *)0x005ab100, (char *)0x0025bf60);
  FUN_0004b2b0();
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)0, 0);
  /* test (char)eax, (char)eax -> je 0x4cccb */
  FUN_00064540((void *)(uintptr_t)ecx, 0);
  FUN_00064570((void *)(uintptr_t)edx);
  /* test edi, edi -> je 0x4cccb */
  /* cmp (int16_t)eax, 2 -> jl 0x4cc60 */
  /* cmp (int16_t)eax, 3 -> jg 0x4cc60 */
  /* test (char)eax, (char)eax -> jne 0x4cc60 */
  /* test (char)eax, (char)eax -> je 0x4cc60 */
  unit_scripting_unit_driver(0, (void *)(uintptr_t)eax);
  actor_perception_aiming_vector_test_blockage();
  /* cmp (int16_t)ebx, (int16_t)eax -> jg 0x4cc60 */
  FUN_00064570((void *)(uintptr_t)ecx);
  /* test edi, edi -> jne 0x4cc05 */
  /* test (char)eax, (char)eax -> je 0x4cccb */
  FUN_0004b2b0();
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)0, 0);
  /* test (char)eax, (char)eax -> je 0x4d665 */
  /* relift: cmp dword ptr [eax + 0x19c], -1 -> je 0x4d665 */
  game_time_get();
  /* cmp edx, eax -> jle 0x4d665 */
  /* test (char)eax, (char)eax -> je 0x4ce7b */
  FUN_00189270(0, (float *)0, (float *)0, (void *)0);
  FUN_00189150(0, (float *)(uintptr_t)edx, 0.0f, (void *)(uintptr_t)ebx);
  FUN_00189270(0, (float *)(uintptr_t)ecx, (float *)(uintptr_t)eax, (void *)(uintptr_t)ebx);
  /* test (char)eax, (char)eax -> je 0x4ce59 */
  csprintf((char *)0x005ab100, (char *)0x0025bf04);
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)(uintptr_t)eax, 0);
  FUN_00189320(0, (float *)(uintptr_t)edx, (float *)(uintptr_t)ecx, 0.0f, (void *)0);
  /* test (char)eax, (char)eax -> je 0x4d0f1 */
  /* test (int16_t)ecx, (int16_t)ecx -> jle 0x4d015 */
  FUN_00189270(0, (float *)0, (float *)0, (void *)0);
  FUN_00189150(0, (float *)(uintptr_t)ecx, 0.0f, (void *)(uintptr_t)ebx);
  FUN_00189270(0, (float *)(uintptr_t)eax, (float *)(uintptr_t)edx, (void *)(uintptr_t)ebx);
  /* test (char)eax, (char)eax -> je 0x4d0f1 */
  csprintf((char *)0x005ab100, (char *)0x0025bf04);
  FUN_00189320(0, (float *)(uintptr_t)eax, (float *)(uintptr_t)ebx, 0.0f, (void *)0);
  /* test (char)eax, (char)eax -> je 0x4d0f1 */
  csprintf((char *)0, (char *)0);
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)(uintptr_t)eax, 0);
  /* relift: cmp word ptr [ebp - 0x30], 1 -> jne 0x4d1aa */
  csprintf((char *)0x005ab100, (char *)0x0025bef4);
  FUN_00189cb0(0, (void *)(uintptr_t)ecx, (void *)(uintptr_t)eax, 0);
  /* test (char)eax, (char)eax -> je 0x4d206 */
  FUN_00189320(0, (float *)(uintptr_t)ebx, (float *)(uintptr_t)edx, 0.0f, (void *)(uintptr_t)ecx);
  FUN_00189320(0, (float *)(uintptr_t)ebx, (float *)(uintptr_t)ecx, 0.0f, (void *)(uintptr_t)eax);
  actor_move_get_avoidance_vector(0, 0.0f, (float *)0);
  csprintf((char *)0x005ab100, (char *)0x0025bee4);
  FUN_0004b2b0();
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)0, 0);
  FUN_00189320(0, (float *)(uintptr_t)ebx, (float *)(uintptr_t)edx, 0.0f, (void *)(uintptr_t)ecx);
  actor_move_get_avoidance_vector(0, 0.0f, (float *)(uintptr_t)eax);
  csprintf((char *)0x005ab100, (char *)0x0025bed0);
  FUN_0004b2b0();
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)0, 0);
  FUN_00189320(0, (float *)(uintptr_t)ebx, (float *)(uintptr_t)ecx, 0.0f, (void *)(uintptr_t)eax);
  csprintf((char *)0x005ab100, (char *)0x0025beb4);
  FUN_0004b2b0();
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)0, 0);
  /* test (char)eax, (char)eax -> je 0x4d40a */
  actor_move_transform_avoidance_vector(0, (float *)(uintptr_t)ecx, (float *)(uintptr_t)eax);
  FUN_00189320(0, (float *)(uintptr_t)ebx, (float *)(uintptr_t)eax, 0.0f, (void *)(uintptr_t)edx);
  csprintf((char *)0x005ab100, (char *)0x0025be8c);
  FUN_0004b2b0();
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)0, 0);
  /* test (char)eax, (char)eax -> je 0x4d473 */
  /* relift: cmp word ptr [edi + 0x1dc], (int16_t)ebx -> jle 0x4d473 */
  FUN_00189860(0, (void *)0, (void *)0, 0.0f, (void *)0);
  /* relift: cmp (int16_t)ebx, word ptr [edi + 0x1dc] -> jl 0x4d420 */
  /* cmp eax, 7 -> ja 0x4d574 */
  crt_sprintf((char *)0x005ab100, (char *)0x0025be6c);
  crt_sprintf((char *)0x005ab100, (char *)0x0025be54);
  crt_sprintf((char *)0x005ab100, (char *)0x0025be34);
  crt_sprintf((char *)0x005ab100, (char *)0x0025be24);
  crt_sprintf((char *)0x005ab100, (char *)0x0025be14);
  crt_sprintf((char *)0x005ab100, (char *)0x0025be00);
  crt_sprintf((char *)0x005ab100, (char *)0x0025bdf0);
  crt_sprintf((char *)0x005ab100, (char *)0x00253b58);
  /* mem[0x005ac9a4] = eax */
  /* mem[0x005ac9a0] = edx */
  /* mem[0x005ac9a8] = ecx */
  FUN_00189cb0(0, (void *)0, (void *)0, 0);
  /* test (char)ebx, (char)ebx -> je 0x4d665 */
  FUN_00189320(0, (float *)(uintptr_t)edx, (float *)(uintptr_t)ecx, 0.0f, (void *)(uintptr_t)eax);
  csprintf((char *)0x005ab100, (char *)0x0025bddc);
  FUN_0004b2b0();
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)0, 0);
  /* test (char)eax, (char)eax -> je 0x4dcc9 */
  /* cmp eax, -1 -> je 0x4d71d */
  global_scenario_get();
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  datum_get((void *)(uintptr_t)edx, 0);
  /* cmp (int16_t)eax, 0xffff -> jne 0x4d6d4 */
  crt_sprintf((char *)(uintptr_t)eax, (char *)0x0025bdd0);
  crt_sprintf((char *)0, (char *)0);
  /* test (char)ecx, (char)ecx -> je 0x4d709 */
  /* test (char)ebx, (char)ebx -> je 0x4d715 */
  crt_sprintf((char *)(uintptr_t)ecx, (char *)0x0025bdb4);
  /* mem[0x005ac9a4] = eax */
  /* mem[0x005ac9a0] = edx */
  /* mem[0x005ac9a8] = ecx */
  FUN_00189cb0(0, (void *)0, (void *)0, 0);
  actor_activation_debug_color(0);
  observer_get_camera(eax);
  players_get_combined_pvs();
  /* test (char)eax, (char)eax -> je 0x4d800 */
  /* cmp eax, -1 -> je 0x4d800 */
  datum_get((void *)(uintptr_t)ecx, 0);
  /* cmp ebx, -1 -> je 0x4dca2 */
  unit_get_head_position(0, (float *)(uintptr_t)edx);
  object_get_root_parent(0);
  object_get_and_verify_type(0, 0);
  /* cmp (int16_t)eax, 0xffff -> jne 0x4da42 */
  FUN_00189270(0, (float *)0, (float *)0, (void *)0);
  FUN_00189270(0, (float *)(uintptr_t)edx, (float *)(uintptr_t)ecx, (void *)(uintptr_t)edi);
  FUN_00189270(0, (float *)(uintptr_t)ecx, (float *)(uintptr_t)eax, (void *)(uintptr_t)edi);
  FUN_00189270(0, (float *)(uintptr_t)eax, (float *)(uintptr_t)edx, (void *)(uintptr_t)edi);
  /* relift: test dword ptr [ecx + eax*4], edx -> je 0x4dba1 */
  FUN_00189270(0, (float *)0, (float *)0, (void *)0);
  FUN_00189270(0, (float *)(uintptr_t)edx, (float *)(uintptr_t)ecx, (void *)(uintptr_t)edi);
  FUN_00189270(0, (float *)(uintptr_t)ecx, (float *)(uintptr_t)eax, (void *)(uintptr_t)edi);
  FUN_00189270(0, (float *)(uintptr_t)eax, (float *)(uintptr_t)edx, (void *)(uintptr_t)edi);
  FUN_00189270(0, (float *)0, (float *)0, (void *)0);
  FUN_00189270(0, (float *)(uintptr_t)ecx, (float *)(uintptr_t)eax, (void *)(uintptr_t)edi);
  /* test eax, eax -> je 0x4dcc9 */
  /* relift: cmp (int16_t)edx, word ptr [eax + 2] -> jge 0x4dcc9 */
  /* test (char)eax, (char)eax -> je 0x4ddf5 */
  /* cmp eax, -1 -> je 0x4dd0b */
  datum_get((void *)(uintptr_t)eax, 0);
  /* relift: cmp word ptr [ebx + 2], 0 -> jle 0x4ddf5 */
  /* cmp edi, -1 -> je 0x4ddf5 */
  object_try_and_get_and_verify_type(0, 0);
  /* test eax, eax -> je 0x4dd40 */
  /* cmp eax, -1 -> je 0x4dd40 */
  object_get_world_position(0, (void *)(uintptr_t)edx);
  FUN_00189540(0, (void *)(uintptr_t)ecx, 0.0f, (void *)(uintptr_t)eax);
  /* test (char)eax, (char)eax -> jne 0x4ddd1 */
  /* relift: cmp dword ptr [esi + 0x164], -1 -> jne 0x4dd98 */
  FUN_00189540(0, (void *)(uintptr_t)eax, 0.0f, (void *)(uintptr_t)edx);
  FUN_00189540(0, (void *)(uintptr_t)edx, 0.0f, (void *)(uintptr_t)ecx);
  scenario_get();
  FUN_00049300();
  /* relift: cmp (int16_t)edx, word ptr [ebx + 2] -> jge 0x4ddf5 */
  /* cmp edi, -1 -> jne 0x4dd17 */
  /* test (char)eax, (char)eax -> je 0x4de94 */
  /* test (char)eax, 0x41 -> jne 0x4de4b */
  csprintf((char *)0x005ab100, (char *)0x0025bda8);
  FUN_0004b2b0();
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)0, 0);
  /* test (char)eax, 0x41 -> jne 0x4de94 */
  csprintf((char *)0x005ab100, (char *)0x0025bd9c);
  FUN_0004b2b0();
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)0, 0);
  /* test (char)eax, (char)eax -> je 0x4df32 */
  /* test (char)eax, 0x41 -> jne 0x4dee9 */
  csprintf((char *)0x005ab100, (char *)0x0025bd90);
  FUN_0004b2b0();
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)0, 0);
  /* test (char)eax, 0x41 -> jne 0x4df32 */
  csprintf((char *)0x005ab100, (char *)0x0025bd84);
  FUN_0004b2b0();
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)0, 0);
  /* test (char)eax, (char)eax -> je 0x4dfee */
  /* test (char)eax, (char)eax -> je 0x4dfee */
  csprintf((char *)0x005ab100, (char *)0x0025bd28);
  FUN_0004b2b0();
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)0, 0);
  /* test (char)eax, (char)eax -> je 0x4e237 */
  /* test (char)eax, (char)eax -> je 0x4e237 */
  csprintf((char *)0x005ab100, (char *)0x0025bd1c);
  FUN_0004b2b0();
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)0, 0);
  /* test (char)eax, (char)eax -> je 0x4e077 */
  csprintf((char *)0x005ab100, (char *)0x0025bd10);
  FUN_0004b2b0();
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)0, 0);
  /* test (char)eax, (char)eax -> je 0x4e0b7 */
  csprintf((char *)0x005ab100, (char *)0x0025bd00);
  FUN_0004b2b0();
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)0, 0);
  /* test (char)eax, (char)eax -> je 0x4e0f7 */
  csprintf((char *)0x005ab100, (char *)0x0025bcf0);
  FUN_0004b2b0();
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)0, 0);
  /* test (char)eax, (char)eax -> je 0x4e137 */
  csprintf((char *)0x005ab100, (char *)0x0025bce4);
  FUN_0004b2b0();
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)0, 0);
  /* test (char)eax, (char)eax -> je 0x4e177 */
  csprintf((char *)0x005ab100, (char *)0x0025bcd4);
  FUN_0004b2b0();
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)0, 0);
  /* test (char)eax, (char)eax -> je 0x4e1b7 */
  csprintf((char *)0x005ab100, (char *)0x0025bcc4);
  FUN_0004b2b0();
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)0, 0);
  /* test (char)eax, (char)eax -> je 0x4e1f7 */
  csprintf((char *)0x005ab100, (char *)0x0025bcb4);
  FUN_0004b2b0();
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)0, 0);
  /* test (char)eax, (char)eax -> je 0x4e237 */
  csprintf((char *)0x005ab100, (char *)0x0025bca4);
  FUN_0004b2b0();
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)0, 0);
  /* test (char)eax, (char)eax -> je 0x4e432 */
  /* mem[0x005ac9a8] = eax */
  /* mem[0x005ac9a0] = ecx */
  /* mem[0x005ac9a4] = edx */
  csprintf((char *)0x005ab100, (char *)0x0025bc90);
  FUN_00189cb0(0, (void *)0x005ac9a0, (void *)(uintptr_t)eax, 0);
  /* relift: cmp word ptr [esi + 0x3a8], 0 -> jle 0x4e38c */
  datum_get((void *)(uintptr_t)eax, 0);
  csprintf((char *)0, (char *)0);
  FUN_0004b2b0();
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)0, 0);
  FUN_00189270(0, (float *)(uintptr_t)ecx, (float *)(uintptr_t)edi, (void *)0);
  /* relift: test dword ptr [edx], 0x20000000 -> je 0x4e435 */
  /* test (char)eax, (char)eax -> je 0x4e3f1 */
  FUN_0004b2b0();
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)0, 0);
  FUN_00189320(0, (float *)(uintptr_t)ebx, (float *)(uintptr_t)edx, 0.0f, (void *)(uintptr_t)ecx);
  csprintf((char *)0x005ab100, (char *)0x0025bc44);
  FUN_0004b2b0();
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)0, 0);
  /* test (char)eax, (char)eax -> je 0x4e53b */
  /* mem[0x005ac9a0] = eax */
  /* mem[0x005ac9a8] = eax */
  /* mem[0x005ac9a4] = edx */
  FUN_00189cb0(0, (void *)0, (void *)0, 0);
  /* test (char)eax, (char)eax -> je 0x4e59c */
  /* cmp eax, -1 -> je 0x4e59c */
  ai_communication_get_player_rating(0, 0, (void *)0, (void *)0);
  csprintf((char *)0x005ab100, (char *)0x0025afc4);
  FUN_0004b2b0();
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)0, 0);
  /* test (char)eax, (char)eax -> je 0x4e681 */
  /* test (char)eax, (char)eax -> je 0x4e681 */
  /* test (int16_t)eax, (int16_t)eax -> jne 0x4e5d5 */
  /* cmp (int16_t)eax, 1 -> jne 0x4e5eb */
  crt_sprintf((char *)(uintptr_t)eax, (char *)0x0025bc28);
  /* cmp eax, 0xbf800000 -> je 0x4e666 */
  csprintf((char *)0x005ab100, (char *)0x0025bc18);
  FUN_0008dc30((char *)(uintptr_t)ecx, (char *)(uintptr_t)eax);
  FUN_0004b2b0();
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)0, 0);
  /* test (char)eax, (char)eax -> jne 0x4e697 */
  /* test (char)eax, (char)eax -> je 0x4ee7f */
  FUN_00064540((void *)0, 0);
  FUN_00064570((void *)(uintptr_t)eax);
  /* test edi, edi -> je 0x4ed04 */
  /* cmp (int16_t)eax, 4 -> jl 0x4e752 */
  /* cmp (int16_t)eax, 5 -> jg 0x4e752 */
  /* test (char)eax, (char)eax -> jne 0x4e74d */
  display_assert((char *)0x0025bc0c, (char *)0x0025ab74, 2230, 0);
  system_exit(0);
  /* test (char)eax, (char)eax -> je 0x4e75e */
  /* test (char)eax, (char)eax -> jne 0x4e775 */
  /* test (char)eax, (char)eax -> je 0x4ecee */
  /* test (char)eax, (char)eax -> jne 0x4e789 */
  /* test (char)eax, (char)eax -> jne 0x4ecee */
  FUN_00189270(0, (float *)(uintptr_t)eax, (float *)(uintptr_t)edx, (void *)(uintptr_t)ecx);
  FUN_00189270(0, (float *)0, (float *)0, (void *)0);
  FUN_00189270(0, (float *)(uintptr_t)ecx, (float *)(uintptr_t)eax, (void *)(uintptr_t)edx);
  FUN_00189270(0, (float *)(uintptr_t)ecx, (float *)(uintptr_t)eax, (void *)(uintptr_t)edx);
  FUN_00189270(0, (float *)(uintptr_t)ecx, (float *)(uintptr_t)eax, (void *)(uintptr_t)eax);
  /* test (char)eax, (char)eax -> jne 0x4e91a */
  FUN_00189540(0, (void *)0, 0.0f, (void *)0);
  FUN_00189320(0, (float *)(uintptr_t)edx, (float *)(uintptr_t)ecx, 0.0f, (void *)(uintptr_t)ebx);
  /* test (int16_t)eax, (int16_t)eax -> jg 0x4e971 */
  /* cmp (int16_t)ecx, 4 -> jl 0x4ea5b */
  /* cmp (int16_t)ecx, 5 -> jg 0x4ea5b */
  /* test (int16_t)eax, (int16_t)eax -> jle 0x4e989 */
  crt_sprintf((char *)0x005ab100, (char *)0x0025bc00);
  csstrcpy((char *)0x005ab100, (char *)0x0025386f);
  /* cmp (int16_t)eax, 4 -> jl 0x4e9da */
  /* cmp (int16_t)eax, 5 -> jg 0x4e9da */
  csstrcpy((char *)(uintptr_t)ecx, (char *)0x005ab100);
  crt_sprintf((char *)0x005ab100, (char *)0x0025bbf8);
  /* relift: cmp word ptr [edi + 0x24], 4 -> jne 0x4ea10 */
  csstrcpy((char *)(uintptr_t)ecx, (char *)0x005ab100);
  crt_sprintf((char *)0x005ab100, (char *)0x0025bbf0);
  FUN_00189cb0(0, (void *)(uintptr_t)edx, (void *)0x005ab100, 0);
  /* test (char)eax, (char)eax -> je 0x4eb41 */
  /* test (char)eax, (char)eax -> je 0x4ea79 */
  csprintf((char *)0x005ab100, (char *)0x0025aec8);
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)(uintptr_t)eax, 0);
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)0x00253e8c, 0);
  /* test (char)eax, (char)eax -> je 0x4ebd8 */
  /* relift: cmp word ptr [edi + 0x9c], 0 -> jle 0x4ebd8 */
  /* cmp ecx, eax -> je 0x4eb76 */
  game_time_get();
  csprintf((char *)0x005ab100, (char *)0x0025bbe4);
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)(uintptr_t)eax, 0);
  /* test (char)eax, (char)eax -> je 0x4ecee */
  /* test (char)eax, (char)eax -> je 0x4ecee */
  crt_sprintf((char *)0x005ab100, (char *)0x0025bbd0);
  /* relift: cmp word ptr [edi + 0xac], 0 -> jle 0x4ec5c */
  crt_sprintf((char *)(uintptr_t)eax, (char *)0x0025bbc8);
  FUN_0008dc30((char *)0x005ab100, (char *)(uintptr_t)ecx);
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)0x005ab100, 0);
  FUN_00189270(0, (float *)0, (float *)0, (void *)0);
  FUN_00064570((void *)(uintptr_t)ecx);
  /* test edi, edi -> jne 0x4e700 */
  /* test (char)eax, (char)eax -> je 0x4edb0 */
  /* relift: cmp word ptr [esi + 0x3a8], 0 -> jle 0x4edb0 */
  datum_get((void *)(uintptr_t)eax, 0);
  csprintf((char *)0, (char *)0);
  FUN_0004b2b0();
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)0, 0);
  FUN_00189270(0, (float *)(uintptr_t)ecx, (float *)(uintptr_t)edi, (void *)0);
  /* test (char)eax, (char)eax -> jne 0x4edd9 */
  /* test (char)eax, (char)eax -> jne 0x4edd9 */
  crt_sprintf((char *)0x005ab100, (char *)0x0025acb8);
  crt_sprintf((char *)0x005ab100, (char *)0x0025bbb8);
  /* mem[0x005ac9a8] = eax */
  /* mem[0x005ac9a0] = ecx */
  /* mem[0x005ac9a4] = edx */
  FUN_00189cb0(0, (void *)0, (void *)0, 0);
  /* test (char)eax, (char)eax -> je 0x4f0cb */
  /* test (int16_t)eax, (int16_t)eax -> jle 0x4f0cb */
  csprintf((char *)0x005ab100, (char *)0x0025bb14);
  FUN_0004b2b0();
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)0, 0);
  /* cmp eax, 3 -> ja 0x4f0cb */
  datum_get((void *)(uintptr_t)ecx, 0);
  FUN_00189270(0, (float *)(uintptr_t)ebx, (float *)(uintptr_t)eax, (void *)0);
  /* cmp eax, -1 -> je 0x4f0cb */
  datum_get((void *)(uintptr_t)eax, 0);
  FUN_00189270(0, (float *)(uintptr_t)ebx, (float *)0, (void *)0);
  /* test (char)eax, (char)eax -> je 0x4f145 */
  actor_get_pursuit_location(actor_handle);
  /* test edi, edi -> je 0x4f145 */
  /* test (int16_t)ecx, (int16_t)ecx -> jne 0x4f126 */
  /* cmp eax, -1 -> je 0x4f126 */
  datum_get((void *)(uintptr_t)ecx, 0);
  actor_action_debug_color(0);
  FUN_00189270(0, (float *)(uintptr_t)ebx, (float *)(uintptr_t)edi, (void *)0);
  /* cmp (int16_t)ecx, 1 -> jne 0x4f145 */
  actor_action_debug_color(0);
  FUN_00189270(0, (float *)(uintptr_t)ebx, (float *)(uintptr_t)edi, (void *)0);
  /* test (char)eax, (char)eax -> je 0x4f516 */
  /* test (char)eax, (char)eax -> je 0x4f516 */
  /* relift: cmp dword ptr [esi + 0x18], -1 -> je 0x4f516 */
  FUN_00189270(0, (float *)0, (float *)0, (void *)0);
  FUN_00189270(0, (float *)0, (float *)0, (void *)0);
  FUN_00189270(0, (float *)0, (float *)0, (void *)0);
  units_debug_get_closest_unit(0, (void *)0);
  FUN_00189320(0, (float *)(uintptr_t)edx, (float *)(uintptr_t)ecx, 0.0f, (void *)(uintptr_t)eax);
  FUN_00189320(0, (float *)(uintptr_t)edx, (float *)(uintptr_t)ecx, 0.0f, (void *)(uintptr_t)eax);
  FUN_00189320(0, (float *)(uintptr_t)edx, (float *)(uintptr_t)ecx, 0.0f, (void *)(uintptr_t)eax);
  /* relift: cmp word ptr [edi + 0x64], 0 -> jne 0x4f516 */
  /* relift: cmp dword ptr [edi + 0xcc], -1 -> jne 0x4f516 */
  tag_get('dpib', 0);
  units_debug_get_closest_unit(0, (void *)(uintptr_t)ecx);
  /* test (char)eax, 4 -> je 0x4f46b */
  biped_build_flying_axes((float *)(uintptr_t)edx, (float *)(uintptr_t)ecx, (float *)(uintptr_t)eax);
  FUN_00189320(0, (float *)0, (float *)0, 0.0f, (void *)0);
  /* test (char)eax, (char)eax -> je 0x4f6d6 */
  /* cmp edx, -1 -> je 0x4f6d6 */
  /* test (char)eax, 0x41 -> jne 0x4f59b */
  /* test eax, eax -> jne 0x4f69a */
  unit_estimate_position(0, 0, (void *)(uintptr_t)ecx, (void *)(uintptr_t)eax, (void *)(uintptr_t)eax, (void *)(uintptr_t)ecx);
  FUN_00189320(0, (float *)(uintptr_t)edx, (float *)(uintptr_t)eax, 0.0f, (void *)(uintptr_t)edi);
  /* test (char)eax, (char)eax -> jne 0x4f6ec */
  /* test (char)eax, (char)eax -> je 0x4f8e9 */
  /* relift: cmp word ptr [esi + 0x268], 0 -> je 0x4f8e9 */
  /* cmp eax, -1 -> je 0x4f8e9 */
  datum_get((void *)(uintptr_t)eax, 0);
  display_assert((char *)0, (char *)0x0025ab74, 2653, 0);
  system_exit(0);
  FUN_00189270(0, (float *)0, (float *)0, (void *)0);
  /* test (char)eax, (char)eax -> je 0x4f880 */
  /* relift: cmp dword ptr [edi + 0x8c], -1 -> je 0x4f880 */
  FUN_00189540(0, (void *)(uintptr_t)edx, 0.0f, (void *)(uintptr_t)ecx);
  /* relift: cmp word ptr [edi + 0x9c], 0 -> jle 0x4f8e9 */
  /* test (char)eax, (char)eax -> je 0x4f89c */
  /* test (char)eax, (char)eax -> jne 0x4f8e9 */
  /* cmp ecx, eax -> je 0x4f8b6 */
  game_time_get();
  csprintf((char *)0x005ab100, (char *)0x0025bbe4);
  FUN_0004b2b0();
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)0, 0);
  /* test (char)eax, (char)eax -> je 0x4f945 */
  observer_get_camera(0);
  /* test eax, eax -> je 0x4f945 */
  actor_action_debug_color(0);
  FUN_00189270(0, (float *)(uintptr_t)ecx, (float *)(uintptr_t)ebx, (void *)(uintptr_t)eax);
  /* test (char)eax, (char)eax -> je 0x5020b */
  /* cmp eax, -1 -> je 0x4fa13 */
  datum_get((void *)(uintptr_t)edx, 0);
  global_scenario_get();
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  encounter_get_squad((char *)(uintptr_t)edi, edx);
  /* test (int16_t)ecx, (int16_t)ecx -> jle 0x4fa13 */
  /* test dl, dl -> je 0x4f9e4 */
  csprintf((char *)0x005ab100, (char *)0x0025bb00);
  /* relift: test byte ptr [ebx + 0x28], 8 -> je 0x4f9f8 */
  FUN_0004b2b0();
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)0, 0);
  /* cmp eax, 8 -> ja 0x5020b */
  /* test (char)eax, (char)eax -> je 0x5020b */
  actor_action_debug_color(0);
  FUN_00189540(0, (void *)(uintptr_t)edx, 0.0f, (void *)(uintptr_t)eax);
  /* relift: cmp word ptr [esi + 0x9c], 0 -> jle 0x5020b */
  actor_action_debug_color(0);
  csprintf((char *)0x005ab100, (char *)0x0025bad0);
  actor_action_debug_color(0);
  csprintf((char *)0x005ab100, (char *)0x0025bac8);
  FUN_0004b2b0();
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)0, 0);
  /* relift: cmp word ptr [esi + 0x9e], 0 -> jle 0x4fb19 */
  actor_action_debug_color(0);
  csprintf((char *)0x005ab100, (char *)0x0025bac0);
  FUN_0004b2b0();
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)0, 0);
  /* test (char)eax, (char)eax -> je 0x4fb9d */
  /* test (char)eax, (char)eax -> je 0x4fb53 */
  actor_action_debug_color(0);
  csprintf((char *)0x005ab100, (char *)0x0025bab4);
  actor_action_debug_color(0);
  csprintf((char *)0x005ab100, (char *)0x0025baa4);
  FUN_0004b2b0();
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)0, 0);
  /* test (char)eax, (char)eax -> je 0x5020b */
  actor_action_debug_color(0);
  FUN_00189320(0, (float *)(uintptr_t)edx, (float *)(uintptr_t)ecx, 0.0f, (void *)(uintptr_t)eax);
  actor_get_pursuit_location(actor_handle);
  display_assert((char *)0x0025ba88, (char *)0x0025ab74, 2773, 0);
  system_exit(0);
  actor_action_debug_color(0);
  csprintf((char *)0x005ab100, (char *)0x0025ba7c);
  /* cmp (int16_t)edi, 1 -> jne 0x4fc5f */
  csprintf((char *)0x005ab100, (char *)0x0025ba74);
  FUN_0004b2b0();
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)0, 0);
  /* cmp (int16_t)eax, 5 -> jne 0x4fc86 */
  /* cmp (int16_t)eax, 7 -> jne 0x4fca7 */
  /* cmp eax, edi -> jg 0x4fcaa */
  actor_action_debug_color(0);
  csprintf((char *)0x005ab100, (char *)0x0025ba68);
  /* test (char)eax, (char)eax -> je 0x4fce8 */
  csstrcpy((char *)(uintptr_t)eax, (char *)0x0025386f);
  /* test (char)eax, (char)eax -> je 0x4fd1a */
  FUN_0008dc30((char *)(uintptr_t)ecx, (char *)0x0025ba50);
  /* test (char)eax, (char)eax -> je 0x4fd38 */
  FUN_0008dc30((char *)(uintptr_t)edx, (char *)0x0025ba44);
  /* test (int16_t)eax, (int16_t)eax -> jle 0x4fd67 */
  csprintf((char *)0x005ab100, (char *)0x0025ba34);
  FUN_0008dc30((char *)(uintptr_t)ecx, (char *)(uintptr_t)eax);
  FUN_0002a3d0(0);
  /* test (char)eax, (char)eax -> je 0x4fdac */
  FUN_0002a3f0(0);
  /* test (char)eax, (char)eax -> je 0x4fd98 */
  FUN_0008dc30((char *)(uintptr_t)edx, (char *)0x0025ba24);
  FUN_0008dc30((char *)(uintptr_t)eax, (char *)0x0025ba1c);
  /* test (char)eax, (char)eax -> je 0x4fdca */
  FUN_0008dc30((char *)(uintptr_t)ecx, (char *)0x0025ba14);
  FUN_0004b2b0();
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)0, 0);
  FUN_00189270(0, (float *)(uintptr_t)edx, (float *)(uintptr_t)edi, (void *)(uintptr_t)ecx);
  FUN_00189320(0, (float *)(uintptr_t)edi, (float *)(uintptr_t)ecx, 0.0f, (void *)(uintptr_t)eax);
  /* cmp eax, 5 -> ja 0x4fee0 */
  csprintf((char *)0x005ab100, (char *)0x0025b9e4);
  FUN_0004b2b0();
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)0, 0);
  /* test (char)eax, (char)eax -> je 0x5020b */
  /* cmp (int16_t)eax, 0xffff -> je 0x5020b */
  global_scenario_get();
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  /* test (char)eax, (char)eax -> jne 0x5020b */
  csprintf((char *)0x005ab100, (char *)0x0025b9ac);
  FUN_0004b2b0();
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)0, 0);
  /* cmp eax, ecx -> jge 0x4ff92 */
  tag_block_get_element((void *)(uintptr_t)edi, 0, 32);
  /* relift: test byte ptr [esi + 0xa8], 2 -> je 0x4ffb7 */
  FUN_0004b2b0();
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)0, 0);
  /* test ebx, ebx -> je 0x5020b */
  /* test (char)eax, (char)eax -> je 0x50029 */
  /* test (char)eax, (char)eax -> je 0x50003 */
  FUN_00189540(0, (void *)(uintptr_t)eax, 0.0f, (void *)(uintptr_t)ecx);
  /* test (int16_t)edi, (int16_t)edi -> jl 0x500a1 */
  /* relift: cmp eax, dword ptr [ecx] -> jge 0x500a1 */
  tag_block_get_element((void *)(uintptr_t)ecx, 0, 20);
  FUN_00189270(0, (float *)(uintptr_t)edx, (float *)(uintptr_t)edi, (void *)(uintptr_t)ecx);
  vector3d_scale_add((float *)(uintptr_t)edi, (float *)(uintptr_t)ecx, 0.0f, (float *)(uintptr_t)eax);
  csprintf((char *)0x005ab100, (char *)0x0025acb8);
  /* test dl, dl -> je 0x500f8 */
  /* test (char)eax, 1 -> jne 0x500f8 */
  vector3d_from_angle((float *)(uintptr_t)eax, 0.0f);
  FUN_00189320(0, (float *)(uintptr_t)eax, (float *)(uintptr_t)edx, 0.0f, (void *)(uintptr_t)ecx);
  csprintf((char *)0x005ab100, (char *)0x0025b978);
  FUN_0004b2b0();
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)0, 0);
  /* test (char)eax, (char)eax -> je 0x501d7 */
  /* test (int16_t)edx, (int16_t)edx -> jl 0x501a9 */
  /* cmp eax, edi -> jge 0x501a9 */
  tag_block_get_element((void *)(uintptr_t)ecx, 0, 20);
  FUN_00189270(0, (float *)(uintptr_t)ecx, (float *)(uintptr_t)edi, (void *)(uintptr_t)eax);
  vector3d_scale_add((float *)(uintptr_t)edi, (float *)(uintptr_t)eax, 0.0f, (float *)(uintptr_t)edx);
  csprintf((char *)0x005ab100, (char *)0x0025acb8);
  csprintf((char *)0x005ab100, (char *)0x0025b950);
  FUN_0004b2b0();
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)0, 0);
  global_scenario_get();
  FUN_00017120((void *)(uintptr_t)eax, (void *)0, (char *)0, 0);
  FUN_0004b2b0();
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)0, 0);
  /* test (char)eax, (char)eax -> je 0x50528 */
  /* relift: cmp word ptr [edi + 8], 3 -> je 0x50427 */
  FUN_0002a360(0);
  csprintf((char *)0x005ab100, (char *)0x0025b924);
  FUN_0004b2b0();
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)0, 0);
  /* test (char)eax, (char)eax -> je 0x502a8 */
  /* test (char)eax, (char)eax -> je 0x502e8 */
  csprintf((char *)0x005ab100, (char *)0x0025b914);
  /* test (char)eax, (char)eax -> je 0x5030e */
  FUN_0004b2b0();
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)0, 0);
  /* cmp eax, 4 -> ja 0x5040a */
  csprintf((char *)0x005ab100, (char *)0x0025ba68);
  FUN_0004b2b0();
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)0, 0);
  csprintf((char *)0x005ab100, (char *)0x0025b908);
  FUN_0004b2b0();
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)0, 0);
  csprintf((char *)0x005ab100, (char *)0x0025b8fc);
  FUN_0004b2b0();
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)0, 0);
  csprintf((char *)0x005ab100, (char *)0x0025b8f0);
  FUN_0004b2b0();
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)0, 0);
  display_assert((char *)0, (char *)0x0025ab74, 3081, 0);
  system_exit(0);
  /* test (int16_t)eax, (int16_t)eax -> jl 0x50528 */
  /* cmp (int16_t)eax, 0x14 -> jge 0x50528 */
  FUN_0004b2b0();
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)0, 0);
  /* relift: cmp dword ptr [edi + 0x150], -1 -> je 0x50667 */
  game_time_get();
  /* cmp ecx, eax -> jl 0x50667 */
  /* cmp eax, 0xa -> ja 0x50639 */
  crt_sprintf((char *)0x005ab100, (char *)0x0025b7a0);
  crt_sprintf((char *)0x005ab100, (char *)0x0025b780);
  crt_sprintf((char *)0x005ab100, (char *)0x0025b76c);
  crt_sprintf((char *)0x005ab100, (char *)0x0025b750);
  csstrcpy((char *)0x005ab100, (char *)0x0025b724);
  FUN_0004b2b0();
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)0, 0);
  /* test (char)eax, (char)eax -> je 0x506d9 */
  /* test eax, eax -> jne 0x5067d */
  /* cmp eax, -1 -> je 0x506a0 */
  unit_is_busy(0);
  csprintf((char *)0x005ab100, (char *)0x0025b704);
  FUN_0004b2b0();
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)0, 0);
  /* test (char)eax, (char)eax -> je 0x50a07 */
  /* relift: cmp word ptr [esi + 0x280], 0 -> jle 0x50a07 */
  /* test (char)eax, (char)eax -> je 0x5072a */
  /* relift: cmp word ptr [esi + 0x284], 0 -> jle 0x50710 */
  /* test (char)eax, (char)eax -> je 0x50722 */
  FUN_00189270(0, (float *)(uintptr_t)edx, (float *)(uintptr_t)edi, (void *)(uintptr_t)ebx);
  FUN_00189540(0, (void *)(uintptr_t)edi, 0.0f, (void *)(uintptr_t)eax);
  FUN_00189320(0, (float *)(uintptr_t)edi, (float *)(uintptr_t)eax, 0.0f, (void *)(uintptr_t)edx);
  FUN_00189540(0, (void *)(uintptr_t)eax, 0.0f, (void *)(uintptr_t)ecx);
  /* relift: cmp word ptr [esi + 0x280], 2 -> jne 0x507d3 */
  /* cmp (int16_t)eax, 0xffff -> jne 0x507b0 */
  csprintf((char *)0x005ab100, (char *)0x0025acb8);
  FUN_00189cb0(0, (void *)(uintptr_t)edi, (void *)(uintptr_t)eax, 0);
  /* relift: cmp word ptr [esi + 0x280], 1 -> jne 0x50814 */
  /* cmp (int16_t)eax, 0xffff -> jne 0x507f1 */
  csprintf((char *)0x005ab100, (char *)0x0025acb8);
  FUN_00189cb0(0, (void *)(uintptr_t)edi, (void *)(uintptr_t)eax, 0);
  /* relift: cmp dword ptr [eax + 0x168], -1 -> je 0x50982 */
  game_time_get();
  /* cmp ecx, eax -> jl 0x50985 */
  /* test (char)eax, (char)eax -> je 0x50863 */
  FUN_0004b2b0();
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)0, 0);
  /* cmp eax, 0xd -> ja 0x50953 */
  crt_sprintf((char *)0x005ab100, (char *)0x0025b6d0);
  crt_sprintf((char *)0x005ab100, (char *)0x0025b6b8);
  /* relift: cmp dword ptr [edi + 0x180], 0x7f7fffff -> jne 0x50910 */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x52ab0 */
void FUN_00052ab0(void)
{
  int eax = 0;
  int ecx = 0;

  /* test (char)eax, (char)eax -> je 0x52b3d */
  /* test (char)eax, (char)eax -> je 0x52b3d */
  FUN_0004b220();
  ai_debug_describe_actor(0, 0, 0, (char *)(uintptr_t)ecx, 256);
  FUN_0004b2b0();
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)0, 0);
  FUN_0004c560();

  (void)eax;
  (void)ecx;
}

/* 0x52b60 */
void FUN_00052b60(char reverse_iteration)
{
  char iter[0x1c];
  int actor_handle;
  char selected;

  encounter_iterator_next(iter, reverse_iteration);
  if (FUN_00059b50(iter) == 0)
    return;

  do {
    actor_handle = *(int *)(iter + 0x14);
    selected = (char)(actor_handle == *(int *)0x5ac9f8);
    FUN_0004c920(actor_handle, selected, 0);
  } while (FUN_00059b50(iter) != 0);
}

/* FUN_00052bb0 (0x52bb0) — XBE naked draft (batch 104). */
#if defined(__clang__)
static void *(*const b52bb0_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static scenario_t * (*const b52bb0_c18e380)(void) = global_scenario_get;
static void *(*const b52bb0_elem)(void *, int, int) = tag_block_get_element;
static void (*const b52bb0_c59a00)(int *iter, int clump_handle) = encounter_actor_iterator_new;
static int (*const b52bb0_c59a50)(int *iter) = encounter_actor_iterator_next;
static void (*const b52bb0_c4c920)(int actor_handle, char debug_selected, void *debug_context) = FUN_0004c920;
static void (*const b52bb0_c5b4b0)(int encounter_handle, int *firing_position_owner_actor_indices) = encounter_build_firing_position_owner_actor_indices;
static void *(*const b52bb0_memset)(void *, int, unsigned int) = csmemset;
static bool (*const b52bb0_c977f0)(void) = game_in_editor;
static void (*const b52bb0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b52bb0_exitfn)(int) = system_exit;
static void * (*const b52bb0_c1d620)(int actor_handle) = actor_action_debug_color;
static void (*const b52bb0_c188a90)(float *points, short count, void *color) = FUN_00188a90;
static void (*const b52bb0_c189270)(char flag, float *point_a, float *point_b, void *color) = FUN_00189270;
static void (*const b52bb0_c189ba0)(float *points, short count, void *color) = FUN_00189ba0;
static void (*const b52bb0_c4b220)(void) = FUN_0004b220;
static char * (*const b52bb0_c8d9d0)(char *buffer, const char *format, ...) = csprintf;
static void (*const b52bb0_c4b2b0)(void) = FUN_0004b2b0;
static void (*const b52bb0_c189cb0)(char flag, void *position, void *string, int color) = FUN_00189cb0;
static void * (*const b52bb0_c1d4f0)(int actor_handle) = actor_get_pursuit_location;
static char (*const b52bb0_c5b6e0)(int encounter_handle, int position_hash, int16_t pursuit_index, int min_time, int16_t *out_count, int *out_time) = encounter_pursuit_position_already_examined;

__attribute__((naked, noinline))
void FUN_00052bb0(int clump_handle __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x8ec, %%esp\n\t"
      "movl 0x5ab270, %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "addl $8, %%esp\n\t"
      "movl %%esi, %%ecx\n\t"
      "andl $0xffff, %%ecx\n\t"
      "pushl $0xb0\n\t"
      "pushl %%ecx\n\t"
      "call *%[c18e380]\n\t"
      "addl $0x42c, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "leal -0x38(%%ebp), %%edx\n\t"
      "pushl %%esi\n\t"
      "orl $0xffffffff, %%edi\n\t"
      "pushl %%edx\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl %%edi, -0x3c(%%ebp)\n\t"
      "call *%[c59a00]\n\t"
      "leal -0x38(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c59a50]\n\t"
      "addl $0x18, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_00052bb0_4\n\t"
      "movl %%edi, %%edi\n\t"
      ".LFUN_00052bb0_1:\n\t"
      "movl 0x5ac9f8, %%ecx\n\t"
      "movl -0x34(%%ebp), %%edx\n\t"
      "cmpl %%edx, %%ecx\n\t"
      "sete %%al\n\t"
      "testb %%al, %%al\n\t"
      "movb %%al, -0x24(%%ebp)\n\t"
      "jne .LFUN_00052bb0_2\n\t"
      "cmpl %%edi, %%ecx\n\t"
      "je .LFUN_00052bb0_2\n\t"
      "movb 0x5aca66, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00052bb0_3\n\t"
      ".LFUN_00052bb0_2:\n\t"
      "movl -0x24(%%ebp), %%eax\n\t"
      "leal -0x3c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%edx\n\t"
      "call *%[c4c920]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_00052bb0_3:\n\t"
      "leal -0x38(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c59a50]\n\t"
      "addl $4, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_00052bb0_1\n\t"
      ".LFUN_00052bb0_4:\n\t"
      "cmpl %%edi, 0x2c8e5c\n\t"
      "jne .LFUN_00052bb0_7\n\t"
      "flds 0x25aa28\n\t"
      "xorl %%edx, %%edx\n\t"
      "fcomps 0x2533c8\n\t"
      "movl %%edx, 0x2c8e5c\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .LFUN_00052bb0_7\n\t"
      "movl $0x25aa30, %%ecx\n\t"
      "jmp .LFUN_00052bb0_5\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".LFUN_00052bb0_5:\n\t"
      "flds -0x4(%%ecx)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .LFUN_00052bb0_6\n\t"
      "flds (%%ecx)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .LFUN_00052bb0_6\n\t"
      "flds 0x4(%%ecx)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .LFUN_00052bb0_6\n\t"
      "flds 0x8(%%ecx)\n\t"
      "addl $0x10, %%ecx\n\t"
      "fcomps 0x2533c8\n\t"
      "incl %%edx\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jnp .LFUN_00052bb0_5\n\t"
      ".LFUN_00052bb0_6:\n\t"
      "movl %%edx, 0x2c8e5c\n\t"
      ".LFUN_00052bb0_7:\n\t"
      "leal -0x8ec(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%esi\n\t"
      "call *%[c5b4b0]\n\t"
      "movl 0x98(%%ebx), %%edx\n\t"
      "leal 0x98(%%ebx), %%eax\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "cmpl %%ecx, %%edx\n\t"
      "movl %%ecx, -0x28(%%ebp)\n\t"
      "movl %%eax, -0x24(%%ebp)\n\t"
      "jle .LFUN_00052bb0_39\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "jmp .LFUN_00052bb0_9\n\t"
      ".LFUN_00052bb0_8:\n\t"
      "movl -0x24(%%ebp), %%eax\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".LFUN_00052bb0_9:\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "pushl $0x18\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl %%eax, %%edi\n\t"
      "flds 0x8(%%edi)\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "fadds 0x2533e8\n\t"
      "pushl $8\n\t"
      "leal -0x74(%%ebp), %%edx\n\t"
      "pushl %%ebx\n\t"
      "fsts -0x40(%%ebp)\n\t"
      "pushl %%edx\n\t"
      "fsts -0x4c(%%ebp)\n\t"
      "movl %%ebx, -0x4(%%ebp)\n\t"
      "fsts -0x58(%%ebp)\n\t"
      "fstps -0x64(%%ebp)\n\t"
      "flds (%%edi)\n\t"
      "fsubs 0x25337c\n\t"
      "fsts -0x48(%%ebp)\n\t"
      "fstps -0x6c(%%ebp)\n\t"
      "flds (%%edi)\n\t"
      "fadds 0x25337c\n\t"
      "fsts -0x54(%%ebp)\n\t"
      "fstps -0x60(%%ebp)\n\t"
      "flds 0x4(%%edi)\n\t"
      "fsubs 0x25337c\n\t"
      "fsts -0x5c(%%ebp)\n\t"
      "fstps -0x68(%%ebp)\n\t"
      "flds 0x4(%%edi)\n\t"
      "fadds 0x25337c\n\t"
      "fsts -0x44(%%ebp)\n\t"
      "fstps -0x50(%%ebp)\n\t"
      "call *%[memset]\n\t"
      "movl 0x5ac9f8, %%eax\n\t"
      "addl $0x18, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_00052bb0_10\n\t"
      "pushl %%eax\n\t"
      "movl 0x6325a4, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl 0x34(%%eax), %%ecx\n\t"
      "movl 0x5ac9f4, %%eax\n\t"
      "addl $8, %%esp\n\t"
      "cmpl %%eax, %%ecx\n\t"
      "je .LFUN_00052bb0_11\n\t"
      ".LFUN_00052bb0_10:\n\t"
      "call *%[c977f0]\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00052bb0_20\n\t"
      "movswl 0xc(%%edi), %%eax\n\t"
      "cdq\n\t"
      "idivl 0x2c8e5c\n\t"
      "movl $1, %%ebx\n\t"
      "shll $4, %%edx\n\t"
      "addl $0x25aa28, %%edx\n\t"
      "movl %%edx, -0xbc(%%ebp)\n\t"
      "jmp .LFUN_00052bb0_20\n\t"
      ".LFUN_00052bb0_11:\n\t"
      "movl 0x5ac9f8, %%edx\n\t"
      "movl $0x2ee6d4, %%eax\n\t"
      "movl %%eax, -0x94(%%ebp)\n\t"
      "movl %%eax, -0x88(%%ebp)\n\t"
      "movl 0x6325a4, %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "movl $0x2ee6d0, -0x9c(%%ebp)\n\t"
      "movl $0x2ee6f0, -0x98(%%ebp)\n\t"
      "movl $0x2ee6d8, -0x90(%%ebp)\n\t"
      "movl $0x2ee6ec, -0x8c(%%ebp)\n\t"
      "movl $0x2ee6f8, -0x84(%%ebp)\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x34(%%esi), %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "andl $0xffff, %%ecx\n\t"
      "pushl $0xb0\n\t"
      "pushl %%ecx\n\t"
      "call *%[c18e380]\n\t"
      "addl $0x42c, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movswl 0x3a(%%esi), %%edx\n\t"
      "pushl $0xe8\n\t"
      "pushl %%edx\n\t"
      "addl $0x80, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movb 0xc(%%edi), %%cl\n\t"
      "movl $1, %%edx\n\t"
      "shll %%cl, %%edx\n\t"
      "movb 0x374(%%esi), %%cl\n\t"
      "movb %%cl, %%bl\n\t"
      "addl $0x18, %%esp\n\t"
      "negb %%bl\n\t"
      "sbbl %%ebx, %%ebx\n\t"
      "andl $3, %%ebx\n\t"
      "addl $2, %%ebx\n\t"
      "movswl %%bx, %%ebx\n\t"
      "testl %%edx, 0x54(%%eax,%%ebx,4)\n\t"
      "je .LFUN_00052bb0_12\n\t"
      "movl 0x2ee6d4, %%ebx\n\t"
      "movl %%ebx, -0xbc(%%ebp)\n\t"
      "movl $1, -0x4(%%ebp)\n\t"
      ".LFUN_00052bb0_12:\n\t"
      "movb %%cl, %%bl\n\t"
      "negb %%bl\n\t"
      "sbbl %%ebx, %%ebx\n\t"
      "andl $3, %%ebx\n\t"
      "negb %%cl\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "andl $3, %%ecx\n\t"
      "incl %%ecx\n\t"
      "cmpb $0, 0x98(%%esi)\n\t"
      "je .LFUN_00052bb0_13\n\t"
      "movl %%ecx, %%esi\n\t"
      "movl %%ebx, %%ecx\n\t"
      "jmp .LFUN_00052bb0_14\n\t"
      ".LFUN_00052bb0_13:\n\t"
      "movl %%ebx, %%esi\n\t"
      ".LFUN_00052bb0_14:\n\t"
      "movswl %%si, %%esi\n\t"
      "testl %%edx, 0x54(%%eax,%%esi,4)\n\t"
      "movl -0x4(%%ebp), %%ebx\n\t"
      "je .LFUN_00052bb0_15\n\t"
      "movl -0x9c(%%ebp,%%esi,4), %%ecx\n\t"
      "jmp .LFUN_00052bb0_16\n\t"
      ".LFUN_00052bb0_15:\n\t"
      "movswl %%cx, %%ecx\n\t"
      "testl %%edx, 0x54(%%eax,%%ecx,4)\n\t"
      "je .LFUN_00052bb0_17\n\t"
      "movl -0x9c(%%ebp,%%ecx,4), %%ecx\n\t"
      "movb $1, -0x74(%%ebp,%%ebx,1)\n\t"
      ".LFUN_00052bb0_16:\n\t"
      "movl (%%ecx), %%edx\n\t"
      "movl %%edx, -0xbc(%%ebp,%%ebx,4)\n\t"
      "incl %%ebx\n\t"
      ".LFUN_00052bb0_17:\n\t"
      "movb 0xc(%%edi), %%cl\n\t"
      "movl $1, %%edx\n\t"
      "shll %%cl, %%edx\n\t"
      "testl %%edx, 0x6c(%%eax)\n\t"
      "je .LFUN_00052bb0_18\n\t"
      "movl 0x2ee6f8, %%eax\n\t"
      "movl %%eax, -0xbc(%%ebp,%%ebx,4)\n\t"
      "incl %%ebx\n\t"
      ".LFUN_00052bb0_18:\n\t"
      "testl %%ebx, %%ebx\n\t"
      "jne .LFUN_00052bb0_19\n\t"
      "movl 0x2ee6c4, %%ecx\n\t"
      "movl %%ecx, -0xbc(%%ebp)\n\t"
      "movl $1, %%ebx\n\t"
      "jmp .LFUN_00052bb0_20\n\t"
      ".LFUN_00052bb0_19:\n\t"
      "cmpl $8, %%ebx\n\t"
      "jl .LFUN_00052bb0_20\n\t"
      "pushl $1\n\t"
      "pushl $0x3c4\n\t"
      "pushl $0x25ab74\n\t"
      "pushl $0x25bfd0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00052bb0_20:\n\t"
      "movl -0x8(%%ebp), %%esi\n\t"
      "movl -0x8ec(%%ebp,%%esi,4), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "leal -0x8ec(%%ebp,%%esi,4), %%esi\n\t"
      "movl %%esi, -0x4(%%ebp)\n\t"
      "je .LFUN_00052bb0_21\n\t"
      "movl 0x6325a4, %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%edx\n\t"
      "call *%[dget]\n\t"
      "flds 0x8(%%edi)\n\t"
      "fadds 0x2533e8\n\t"
      "movl (%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "fsts -0xc0(%%ebp)\n\t"
      "fsts -0xcc(%%ebp)\n\t"
      "fsts -0xd8(%%ebp)\n\t"
      "fstps -0xe4(%%ebp)\n\t"
      "flds (%%edi)\n\t"
      "fsubs 0x25bfc8\n\t"
      "fsts -0xc8(%%ebp)\n\t"
      "fstps -0xec(%%ebp)\n\t"
      "flds (%%edi)\n\t"
      "fadds 0x25bfc8\n\t"
      "fsts -0xd4(%%ebp)\n\t"
      "fstps -0xe0(%%ebp)\n\t"
      "flds 0x4(%%edi)\n\t"
      "fsubs 0x25bfc8\n\t"
      "fsts -0xdc(%%ebp)\n\t"
      "fstps -0xe8(%%ebp)\n\t"
      "flds 0x4(%%edi)\n\t"
      "fadds 0x25bfc8\n\t"
      "fsts -0xc4(%%ebp)\n\t"
      "fstps -0xd0(%%ebp)\n\t"
      "call *%[c1d620]\n\t"
      "pushl %%eax\n\t"
      "leal -0xec(%%ebp), %%ecx\n\t"
      "pushl $4\n\t"
      "pushl %%ecx\n\t"
      "call *%[c188a90]\n\t"
      "addl $0x18, %%esp\n\t"
      ".LFUN_00052bb0_21:\n\t"
      "movb 0x5aca8d, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00052bb0_23\n\t"
      "cmpl $-1, 0x14(%%edi)\n\t"
      "movl 0x2ee6d0, %%esi\n\t"
      "je .LFUN_00052bb0_22\n\t"
      "movl 0x2ee6c4, %%esi\n\t"
      ".LFUN_00052bb0_22:\n\t"
      "movl %%edi, %%edx\n\t"
      "movl (%%edx), %%eax\n\t"
      "movl 0x4(%%edx), %%ecx\n\t"
      "movl 0x8(%%edx), %%edx\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "movl %%ecx, -0x10(%%ebp)\n\t"
      "movl %%edx, -0xc(%%ebp)\n\t"
      "movl %%edi, %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl %%eax, -0x18(%%ebp)\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fadds 0x253398\n\t"
      "movl %%ecx, -0x20(%%ebp)\n\t"
      "pushl %%esi\n\t"
      "leal -0x14(%%ebp), %%ecx\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "movl %%edx, -0x1c(%%ebp)\n\t"
      "flds -0xc(%%ebp)\n\t"
      "pushl %%ecx\n\t"
      "fsubs 0x253398\n\t"
      "leal -0x20(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $1\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "call *%[c189270]\n\t"
      "flds -0x18(%%ebp)\n\t"
      "pushl %%esi\n\t"
      "fsubs 0x253398\n\t"
      "leal -0x14(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x20(%%ebp), %%ecx\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "pushl %%ecx\n\t"
      "flds -0xc(%%ebp)\n\t"
      "pushl $1\n\t"
      "fadds 0x253398\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "flds -0x20(%%ebp)\n\t"
      "fsubs 0x25496c\n\t"
      "fstps -0x20(%%ebp)\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fadds 0x25496c\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "call *%[c189270]\n\t"
      "flds -0x20(%%ebp)\n\t"
      "pushl %%esi\n\t"
      "fadds 0x25496c\n\t"
      "leal -0x14(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x20(%%ebp), %%eax\n\t"
      "fstps -0x20(%%ebp)\n\t"
      "pushl %%eax\n\t"
      "flds -0x14(%%ebp)\n\t"
      "pushl $1\n\t"
      "fsubs 0x25496c\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fsubs 0x25496c\n\t"
      "fstps -0x1c(%%ebp)\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fadds 0x25496c\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "call *%[c189270]\n\t"
      "addl $0x30, %%esp\n\t"
      ".LFUN_00052bb0_23:\n\t"
      "xorl %%esi, %%esi\n\t"
      "testl %%ebx, %%ebx\n\t"
      "jle .LFUN_00052bb0_27\n\t"
      "jmp .LFUN_00052bb0_24\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".LFUN_00052bb0_24:\n\t"
      "flds -0x64(%%ebp)\n\t"
      "movb -0x74(%%ebp,%%esi,1), %%al\n\t"
      "testb %%al, %%al\n\t"
      "fadds 0x2533e8\n\t"
      "fsts -0x40(%%ebp)\n\t"
      "fsts -0x4c(%%ebp)\n\t"
      "fsts -0x58(%%ebp)\n\t"
      "fstps -0x64(%%ebp)\n\t"
      "je .LFUN_00052bb0_25\n\t"
      "movl -0xbc(%%ebp,%%esi,4), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x54(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x6c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $1\n\t"
      "call *%[c189270]\n\t"
      "movl -0xbc(%%ebp,%%esi,4), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x48(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x60(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $1\n\t"
      "call *%[c189270]\n\t"
      "addl $0x20, %%esp\n\t"
      "jmp .LFUN_00052bb0_26\n\t"
      ".LFUN_00052bb0_25:\n\t"
      "movl -0xbc(%%ebp,%%esi,4), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x6c(%%ebp), %%eax\n\t"
      "pushl $4\n\t"
      "pushl %%eax\n\t"
      "call *%[c189ba0]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_00052bb0_26:\n\t"
      "incl %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "jl .LFUN_00052bb0_24\n\t"
      ".LFUN_00052bb0_27:\n\t"
      "movl 0x31fc44, %%eax\n\t"
      "flds (%%eax)\n\t"
      "fmuls 0x2549d4\n\t"
      "fadds (%%edi)\n\t"
      "fstps -0x80(%%ebp)\n\t"
      "flds 0x4(%%eax)\n\t"
      "fmuls 0x2549d4\n\t"
      "fadds 0x4(%%edi)\n\t"
      "fstps -0x7c(%%ebp)\n\t"
      "flds 0x8(%%eax)\n\t"
      "leal -0x80(%%ebp), %%eax\n\t"
      "fmuls 0x2549d4\n\t"
      "fadds 0x8(%%edi)\n\t"
      "fstps -0x78(%%ebp)\n\t"
      "call *%[c4b220]\n\t"
      "movb 0x5aca84, %%al\n\t"
      "testb %%al, %%al\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "je .LFUN_00052bb0_34\n\t"
      "movl %%eax, %%esi\n\t"
      "shll $6, %%esi\n\t"
      "movb 0x62a3b4(%%esi), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "je .LFUN_00052bb0_34\n\t"
      "movl 0x5ac9f8, %%eax\n\t"
      "xorb %%bl, %%bl\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_00052bb0_30\n\t"
      "movb 0x62a3e8(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "movl 0x2ee6c4, %%eax\n\t"
      "jne .LFUN_00052bb0_28\n\t"
      "movl 0x2ee6d0, %%eax\n\t"
      ".LFUN_00052bb0_28:\n\t"
      "flds 0x62a3f0(%%esi)\n\t"
      "pushl %%eax\n\t"
      "subl $8, %%esp\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x25bfc0\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x10, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[c4b2b0]\n\t"
      "pushl %%eax\n\t"
      "pushl $1\n\t"
      "call *%[c189cb0]\n\t"
      "movl 0x5ac9f8, %%eax\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_00052bb0_30\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d4f0]\n\t"
      "addl $4, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_00052bb0_29\n\t"
      "cmpw $1, (%%eax)\n\t"
      "jne .LFUN_00052bb0_29\n\t"
      "movw 0x2(%%eax), %%cx\n\t"
      "cmpw -0x28(%%ebp), %%cx\n\t"
      "jne .LFUN_00052bb0_29\n\t"
      "movb $1, %%bl\n\t"
      "jmp .LFUN_00052bb0_30\n\t"
      ".LFUN_00052bb0_29:\n\t"
      "xorb %%bl, %%bl\n\t"
      ".LFUN_00052bb0_30:\n\t"
      "movl -0x3c(%%ebp), %%eax\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "cmpl $-1, %%eax\n\t"
      "sete %%cl\n\t"
      "pushl $0\n\t"
      "leal -0x2c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl -0x28(%%ebp), %%edx\n\t"
      "decl %%ecx\n\t"
      "andl %%eax, %%ecx\n\t"
      "movl 0x5ac9f8, %%eax\n\t"
      "pushl %%ecx\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c5b6e0]\n\t"
      "movl 0x5ac9f8, %%ecx\n\t"
      "addl $0x18, %%esp\n\t"
      "cmpl $-1, %%ecx\n\t"
      "jne .LFUN_00052bb0_31\n\t"
      "xorb %%al, %%al\n\t"
      ".LFUN_00052bb0_31:\n\t"
      "testb %%bl, %%bl\n\t"
      "je .LFUN_00052bb0_32\n\t"
      "movl 0x2ee6e0, %%ecx\n\t"
      "jmp .LFUN_00052bb0_33\n\t"
      ".LFUN_00052bb0_32:\n\t"
      "testb %%al, %%al\n\t"
      "movl 0x2ee6d8, %%ecx\n\t"
      "jne .LFUN_00052bb0_33\n\t"
      "movl 0x2ee6c4, %%ecx\n\t"
      ".LFUN_00052bb0_33:\n\t"
      "movl 0x5ac9b0, %%edx\n\t"
      "flds 0x5ac990\n\t"
      "movl 0x5ac9b4, %%eax\n\t"
      "movl %%eax, 0x5ac9a4\n\t"
      "movl 0x31fc44, %%eax\n\t"
      "movl %%edx, 0x5ac9a0\n\t"
      "movl 0x5ac9b8, %%edx\n\t"
      "movl %%edx, 0x5ac9a8\n\t"
      "fmuls (%%eax)\n\t"
      "pushl %%ecx\n\t"
      "fadds 0x5ac9b0\n\t"
      "fstps 0x5ac9b0\n\t"
      "flds 0x5ac990\n\t"
      "fmuls 0x4(%%eax)\n\t"
      "fadds 0x5ac9a4\n\t"
      "fstps 0x5ac9b4\n\t"
      "flds 0x5ac990\n\t"
      "fmuls 0x8(%%eax)\n\t"
      "movswl -0x2c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x25acb8\n\t"
      "fadds 0x5ac9a8\n\t"
      "pushl $0x5ab100\n\t"
      "fstps 0x5ac9b8\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0xc, %%esp\n\t"
      "pushl %%eax\n\t"
      "pushl $0x5ac9a0\n\t"
      "pushl $1\n\t"
      "call *%[c189cb0]\n\t"
      "movb 0x629d40, %%al\n\t"
      "addl $0x10, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00052bb0_38\n\t"
      "movb 0x62a340, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00052bb0_38\n\t"
      "movb 0x629d87, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00052bb0_38\n\t"
      "movb 0x62a3b5(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00052bb0_38\n\t"
      "movb 0x62a3e8(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00052bb0_38\n\t"
      "flds 0x62a348\n\t"
      "movl 0x2ee6e0, %%ecx\n\t"
      "fadds 0x62a3d8(%%esi)\n\t"
      "pushl %%ecx\n\t"
      "leal -0x38(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "fstps -0x38(%%ebp)\n\t"
      "pushl $0x62a348\n\t"
      "flds 0x62a34c\n\t"
      "pushl $1\n\t"
      "fadds 0x62a3dc(%%esi)\n\t"
      "fstps -0x34(%%ebp)\n\t"
      "flds 0x62a350\n\t"
      "fadds 0x62a3e0(%%esi)\n\t"
      "fstps -0x30(%%ebp)\n\t"
      "call *%[c189270]\n\t"
      "movl 0x2ee6d4, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "leal -0x38(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $1\n\t"
      "call *%[c189270]\n\t"
      "addl $0x20, %%esp\n\t"
      "jmp .LFUN_00052bb0_38\n\t"
      ".LFUN_00052bb0_34:\n\t"
      "movb 0x5aca83, %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "je .LFUN_00052bb0_38\n\t"
      "shll $6, %%eax\n\t"
      "movl %%eax, %%esi\n\t"
      "movb 0x62a3b5(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00052bb0_38\n\t"
      "movb 0x62a3b4(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00052bb0_38\n\t"
      "movl 0x5ac9f8, %%ecx\n\t"
      "cmpl $-1, %%ecx\n\t"
      "je .LFUN_00052bb0_38\n\t"
      "movb 0x62a3e8(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00052bb0_35\n\t"
      "movl 0x2ee6d0, %%edi\n\t"
      "jmp .LFUN_00052bb0_37\n\t"
      ".LFUN_00052bb0_35:\n\t"
      "flds 0x62a3ec(%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00052bb0_41\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "cmpl %%ecx, (%%edx)\n\t"
      "movl 0x2ee6c4, %%eax\n\t"
      "jne .LFUN_00052bb0_40\n\t"
      "movl 0x2ee6e0, %%edi\n\t"
      ".LFUN_00052bb0_36:\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_00052bb0_37\n\t"
      "flds 0x62a3ec(%%esi)\n\t"
      "pushl %%eax\n\t"
      "subl $8, %%esp\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x25bfc0\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x10, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[c4b2b0]\n\t"
      "pushl %%eax\n\t"
      "pushl $1\n\t"
      "call *%[c189cb0]\n\t"
      "addl $0x10, %%esp\n\t"
      ".LFUN_00052bb0_37:\n\t"
      "flds 0x62a3f0(%%esi)\n\t"
      "pushl %%edi\n\t"
      "subl $8, %%esp\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x25bfc0\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x10, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[c4b2b0]\n\t"
      "pushl %%eax\n\t"
      "pushl $1\n\t"
      "call *%[c189cb0]\n\t"
      "addl $0x10, %%esp\n\t"
      ".LFUN_00052bb0_38:\n\t"
      "movl -0x28(%%ebp), %%eax\n\t"
      "movl -0x24(%%ebp), %%ecx\n\t"
      "movl (%%ecx), %%edx\n\t"
      "incl %%eax\n\t"
      "movl %%eax, -0x28(%%ebp)\n\t"
      "movswl %%ax, %%eax\n\t"
      "cmpl %%edx, %%eax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "jl .LFUN_00052bb0_8\n\t"
      ".LFUN_00052bb0_39:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00052bb0_40:\n\t"
      "movl 0x2ee6d8, %%edi\n\t"
      "jmp .LFUN_00052bb0_36\n\t"
      ".LFUN_00052bb0_41:\n\t"
      "movl 0x2ee6c4, %%edi\n\t"
      "jmp .LFUN_00052bb0_37\n\t"
      :
      : [dget] "m"(b52bb0_dget), [c18e380] "m"(b52bb0_c18e380), [elem] "m"(b52bb0_elem), [c59a00] "m"(b52bb0_c59a00), [c59a50] "m"(b52bb0_c59a50), [c4c920] "m"(b52bb0_c4c920), [c5b4b0] "m"(b52bb0_c5b4b0), [memset] "m"(b52bb0_memset), [c977f0] "m"(b52bb0_c977f0), [assert] "m"(b52bb0_assert), [exitfn] "m"(b52bb0_exitfn), [c1d620] "m"(b52bb0_c1d620), [c188a90] "m"(b52bb0_c188a90), [c189270] "m"(b52bb0_c189270), [c189ba0] "m"(b52bb0_c189ba0), [c4b220] "m"(b52bb0_c4b220), [c8d9d0] "m"(b52bb0_c8d9d0), [c4b2b0] "m"(b52bb0_c4b2b0), [c189cb0] "m"(b52bb0_c189cb0), [c1d4f0] "m"(b52bb0_c1d4f0), [c5b6e0] "m"(b52bb0_c5b6e0)
      : "memory");
}
#else
#error "FUN_00052bb0: clang naked draft required"
#endif


/* 0x534d0 */
void FUN_000534d0(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;

  /* test (char)ecx, (char)ecx -> je 0x5361d */
  /* mem[0x005acab4] = edx */
  datum_get((void *)(uintptr_t)edx, 0);
  /* mem[0x005ac9f4] = eax */
  /* test (char)eax, (char)eax -> je 0x53534 */
  FUN_0004b7a0();
  /* test (char)eax, (char)eax -> je 0x5361d */
  /* test (char)eax, (char)eax -> je 0x5354f */
  FUN_000494e0();
  /* test (char)eax, (char)eax -> je 0x5355d */
  FUN_00049990();
  /* test (char)eax, (char)eax -> je 0x5356b */
  FUN_000495b0();
  /* cmp eax, -1 -> je 0x5357e */
  FUN_00052bb0(eax);
  /* cmp eax, -1 -> je 0x53595 */
  FUN_0004c920(*(int *)0x5ac9f8, 1, 0);
  /* test (char)eax, (char)eax -> je 0x535a3 */
  FUN_0004c890();
  /* test (char)eax, (char)eax -> je 0x535b1 */
  FUN_00052ab0();
  /* test (char)eax, (char)eax -> je 0x535bf */
  FUN_00049d60();
  /* test (char)eax, (char)eax -> je 0x535d3 */
  FUN_00052b60(0);
  /* test (char)eax, (char)eax -> jne 0x535ee */
  /* test (char)eax, (char)eax -> jne 0x535ee */
  /* test (char)eax, (char)eax -> je 0x535f3 */
  FUN_0004b810();
  /* test (char)eax, (char)eax -> je 0x53601 */
  FUN_0004a770();
  /* test (char)eax, (char)eax -> je 0x5360f */
  FUN_0004a8c0();
  /* test (char)eax, (char)eax -> je 0x5361d */

  (void)eax;
  (void)ecx;
  (void)edx;
}

/* 0x53650 */
void FUN_00053650(void)
{
  csmemset((void *)0x005abaac, 0, 3808);
}

/* 0x53680 */
void FUN_00053680(void)
{
  int eax = 0;
  int ebx = 0;
  int esi = 0;
  int edi = 0;

  /* relift: cmp word ptr [ebx - 4], (int16_t)edi -> je 0x536be */
  display_assert((char *)0x0025c08c, (char *)0x0025c0ac, 140, 0);
  system_exit(0);
  /* test eax, eax -> je 0x536ca */
  /* cmp (int16_t)eax, 0x3c -> jl 0x53706 */
  display_assert((char *)0x0025c030, (char *)0x0025c0ac, 151, 0);
  system_exit(0);
  /* relift: cmp (int16_t)eax, word ptr [esi + 2] -> jge 0x5371a */

  (void)eax;
  (void)ebx;
  (void)esi;
  (void)edi;
}

/* 0x53790 */
void FUN_00053790(void)
{
  int eax = 0;
  int esi = 0;

  csstrlen((char *)(uintptr_t)esi);
  crt_sprintf((char *)(uintptr_t)eax, (char *)0);

  (void)eax;
  (void)esi;
}

/* 0x53800 */
void FUN_00053800(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;

  interface_draw_text(0, 0, 0, 0, 0, 0);
  draw_string_set_color((void *)(uintptr_t)esi);
  draw_string_set_tab_stops((void *)(uintptr_t)edx, 0);
  rasterizer_text_draw((void *)(uintptr_t)edx, (void *)0, (void *)(uintptr_t)ecx, 0, (char *)(uintptr_t)eax);
  draw_string_set_tab_stops((void *)0, 0);

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
}

/* 0x53890 */
void FUN_00053890(void)
{
  console_printf(0, (void *)0x0025c120);
}

/* 0x538d0 — read debug widget field at +0x30 */
int16_t FUN_000538d0(void)
{
  return *(int16_t *)(*(int *)0x5ab270 + 0x30);
}

/* 0x538f0 */
void FUN_000538f0(void)
{
  int eax = 0;
  int ecx = 0;
  int esi = 0;

  encounter_iterator_next((void *)(uintptr_t)eax, esi);
  FUN_00059b50((void *)(uintptr_t)ecx);
  /* test eax, eax -> je 0x53937 */
  /* test (char)ecx, (char)ecx -> je 0x53920 */
  FUN_00059b50((void *)0);
  /* test eax, eax -> jne 0x53913 */

  (void)eax;
  (void)ecx;
  (void)esi;
}

/* 0x53960 */
void FUN_00053960(void)
{
  int eax = 0;
  int ecx = 0;
  int esi = 0;

  encounter_iterator_next((void *)(uintptr_t)eax, esi);
  FUN_00059b50((void *)(uintptr_t)ecx);
  /* test eax, eax -> je 0x5399a */
  FUN_00059b50((void *)0);
  /* test eax, eax -> jne 0x53983 */

  (void)eax;
  (void)ecx;
  (void)esi;
}

/* 0x539c0 */
void FUN_000539c0(void)
{
  crt_sprintf((void *)0x005ab280, (void *)0x0025c134);
  FUN_00053800();
}

/* 0x53a20 */
void FUN_00053a20(void)
{
  crt_sprintf((void *)0x005ab280, (void *)0x0025c154);
  FUN_00053800();
}

/* 0x53a90 */
void FUN_00053a90(void)
{
  crt_sprintf((void *)0x005ab280, (void *)0x0025c174);
  FUN_00053800();
}

/* 0x53af0 */
void FUN_00053af0(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  crt_sprintf((char *)0x005ab280, (char *)0x0025c198);
  FUN_00053800();
  crt_sprintf((char *)0x005ab280, (char *)0x0025c1d8);
  FUN_00053800();
  crt_sprintf((char *)0x005ab280, (char *)0x0025c218);
  FUN_00053800();
  observer_get_camera(0);
  /* test (int16_t)ecx, (int16_t)ecx -> jle 0x53d91 */
  /* test eax, eax -> je 0x53d91 */
  encounter_iterator_next((void *)0, 0);
  FUN_00059b50((void *)(uintptr_t)edx);
  /* test eax, eax -> je 0x53d91 */
  datum_get((void *)(uintptr_t)ecx, 0);
  actor_activation_debug_color(0);
  actor_action_debug_color(0);
  /* test ebx, ebx -> je 0x53d7a */
  /* test (char)eax, (char)eax -> je 0x53d64 */
  /* cmp esi, -1 -> je 0x53d7a */
  object_get_and_verify_type(0, 0);
  unit_get_head_position(0, (float *)(uintptr_t)ecx);
  FUN_00189270(0, (float *)(uintptr_t)eax, (float *)(uintptr_t)edx, (void *)(uintptr_t)ebx);
  /* cmp esi, -1 -> jne 0x53d30 */
  FUN_00189270(0, (float *)(uintptr_t)ecx, (float *)(uintptr_t)esi, (void *)0);
  FUN_00059b50((void *)(uintptr_t)edx);
  /* test eax, eax -> jne 0x53ce0 */
  FUN_00053c50();
  /* test (char)eax, (char)eax -> je 0x53e10 */
  /* test (char)eax, (char)eax -> je 0x53dca */
  /* relift: tail-call FUN_00053af0(); */
  /* test (char)eax, (char)eax -> je 0x53dd8 */
  FUN_00053b80();
  /* test (char)eax, (char)eax -> je 0x53de6 */
  FUN_00053bf0();
  /* test (char)eax, (char)eax -> je 0x53df4 */
  FUN_00053a90();
  /* test (char)eax, (char)eax -> je 0x53e02 */
  FUN_00053a20();
  /* test (char)eax, (char)eax -> je 0x53e10 */
  /* test ecx, ecx -> jle 0x53e6e */
  tag_block_get_element((void *)(uintptr_t)edi, 0, 176);
  __strnicmp((char *)(uintptr_t)eax, (char *)(uintptr_t)ebx, 32);
  /* test eax, eax -> je 0x53e6c */
  /* cmp esi, eax -> jl 0x53e41 */
  /* test ecx, ecx -> jle 0x53ece */
  tag_block_get_element((void *)(uintptr_t)edi, 0, 232);
  __strnicmp((char *)(uintptr_t)eax, (char *)(uintptr_t)ebx, 32);
  /* test eax, eax -> je 0x53ecc */
  /* cmp esi, eax -> jl 0x53ea1 */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}
/* --- ai_debug.obj orphan shells (2026-07-26) --- */

/* orphan 0x4a460 */
void FUN_0004a460(int a0, int a1, void *buf, int buf_size, int max_entries)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  display_assert((char *)0x0025aea4, (char *)0x0025ab74, 4947, 0);
  system_exit(0);
  /* cmp ebx, 0x800 -> jbe 0x4a4c6 */
  display_assert((char *)0x0025ae90, (char *)0x0025ab74, 4948, 0);
  system_exit(0);
  csmemset((void *)(uintptr_t)eax, 0, ebx);
  /* cmp eax, edi -> jle 0x4a587 */
  /* cmp (int16_t)esi, -1 -> je 0x4a551 */
  /* test (int16_t)esi, (int16_t)esi -> jl 0x4a514 */
  /* cmp eax, ecx -> jb 0x4a534 */
  display_assert((char *)0x0025ae60, (char *)0x0025ab74, 4957, 0);
  system_exit(0);
  csstrcmp((char *)(uintptr_t)ecx, (char *)0x0025ae38);
  /* test eax, eax -> jne 0x4a57b */
  csmemset((void *)(uintptr_t)edx, 0, ebx);
  /* cmp edi, eax -> jl 0x4a4f0 */
  /* test edi, edi -> jbe 0x4a63b */
  /* relift: test dword ptr [ebp + eax - 0x108], edx -> je 0x4a5c1 */
  /* relift: test dword ptr [eax + ecx], edx -> je 0x4a5be */
  /* cmp esi, edi -> jb 0x4a594 */
  /* test (int16_t)esi, (int16_t)esi -> je 0x4a5fa */
  bit_vector_or(edi, 0, 0, 0);
  console_printf(0, (char *)0x0025ae50);
  /* test (int16_t)esi, (int16_t)esi -> je 0x4a63b */
  FUN_00108fa0(edi, 0, 0);
  bit_vector_and(edi, 0, 0, 0);
  console_printf(0, (char *)0x0025ae3c);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}
