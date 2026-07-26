
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

/* ai_debug_change_selected_encounter (0x4afa0) — XBE naked draft (batch 125). */
#if defined(__clang__)
static int (*const b4afa0_c1198f0)(data_t *data, int prev_index) = data_next_index;
static unsigned int (*const b4afa0_c119980)(data_t *data, int datum) = data_prev_index;
static int (*const b4afa0_c119270)(data_t *data, int absolute_index) = datum_absolute_index_to_index;
static void (*const b4afa0_cff4d0)(int channel, const char *format, ...) = console_printf;
static void (*const b4afa0_c49220)(int encounter_idx) = ai_debug_select_encounter;
static scenario_t * (*const b4afa0_c18e380)(void) = global_scenario_get;
static void *(*const b4afa0_elem)(void *, int, int) = tag_block_get_element;
static char * (*const b4afa0_c8dff0)(char *destination, const char *source) = csstrcpy;
static int (*const b4afa0_c1d90f0)(char *buffer, const char *format, ...) = crt_sprintf;

__attribute__((naked, noinline))
void ai_debug_change_selected_encounter(int encounter_index __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x200, %%esp\n\t"
      "movb 0x8(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "je .Lai_debug_change_selected_encounter_1\n\t"
      "movl 0x5ac9f4, %%eax\n\t"
      "movl 0x5ab270, %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1198f0]\n\t"
      "jmp .Lai_debug_change_selected_encounter_2\n\t"
      ".Lai_debug_change_selected_encounter_1:\n\t"
      "movl 0x5ac9f4, %%edx\n\t"
      "movl 0x5ab270, %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c119980]\n\t"
      ".Lai_debug_change_selected_encounter_2:\n\t"
      "movl 0x5ab270, %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "movl %%eax, %%ebx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c119270]\n\t"
      "movl %%eax, %%edi\n\t"
      "addl $8, %%esp\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .Lai_debug_change_selected_encounter_3\n\t"
      "pushl $0x25afac\n\t"
      "pushl %%eax\n\t"
      "call *%[cff4d0]\n\t"
      "pushl $-1\n\t"
      "call *%[c49220]\n\t"
      "addl $0xc, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lai_debug_change_selected_encounter_3:\n\t"
      "pushl %%esi\n\t"
      "movl %%ebx, %%edx\n\t"
      "andl $0xffff, %%edx\n\t"
      "pushl $0xb0\n\t"
      "pushl %%edx\n\t"
      "call *%[c18e380]\n\t"
      "addl $0x42c, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl %%eax, %%esi\n\t"
      "movb 0x20(%%esi), %%al\n\t"
      "addl $0xc, %%esp\n\t"
      "testb $0x20, %%al\n\t"
      "je .Lai_debug_change_selected_encounter_4\n\t"
      "leal -0x200(%%ebp), %%eax\n\t"
      "pushl $0x25af9c\n\t"
      "pushl %%eax\n\t"
      "call *%[c8dff0]\n\t"
      "addl $8, %%esp\n\t"
      "jmp .Lai_debug_change_selected_encounter_8\n\t"
      ".Lai_debug_change_selected_encounter_4:\n\t"
      "movw 0x7e(%%esi), %%ax\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "jne .Lai_debug_change_selected_encounter_5\n\t"
      "leal -0x100(%%ebp), %%ecx\n\t"
      "pushl $0x253a04\n\t"
      "pushl %%ecx\n\t"
      "call *%[c8dff0]\n\t"
      "addl $8, %%esp\n\t"
      "jmp .Lai_debug_change_selected_encounter_6\n\t"
      ".Lai_debug_change_selected_encounter_5:\n\t"
      "movswl %%ax, %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x100(%%ebp), %%eax\n\t"
      "pushl $0x25acb8\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d90f0]\n\t"
      "addl $0xc, %%esp\n\t"
      ".Lai_debug_change_selected_encounter_6:\n\t"
      "testb $0x40, 0x20(%%esi)\n\t"
      "movl $0x25af94, %%eax\n\t"
      "jne .Lai_debug_change_selected_encounter_7\n\t"
      "movl $0x25af8c, %%eax\n\t"
      ".Lai_debug_change_selected_encounter_7:\n\t"
      "leal -0x100(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "leal -0x200(%%ebp), %%edx\n\t"
      "pushl $0x25af80\n\t"
      "pushl %%edx\n\t"
      "call *%[c1d90f0]\n\t"
      "addl $0x10, %%esp\n\t"
      ".Lai_debug_change_selected_encounter_8:\n\t"
      "movb 0xd(%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "movl $0x25af78, %%eax\n\t"
      "jne .Lai_debug_change_selected_encounter_9\n\t"
      "movl $0x25af6c, %%eax\n\t"
      ".Lai_debug_change_selected_encounter_9:\n\t"
      "movswl 0x2a(%%edi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x200(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl $0x25af48\n\t"
      "pushl $0\n\t"
      "call *%[cff4d0]\n\t"
      "pushl %%ebx\n\t"
      "call *%[c49220]\n\t"
      "addl $0x1c, %%esp\n\t"
      "popl %%esi\n\t"
      "popl %%edi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c1198f0] "m"(b4afa0_c1198f0), [c119980] "m"(b4afa0_c119980), [c119270] "m"(b4afa0_c119270), [cff4d0] "m"(b4afa0_cff4d0), [c49220] "m"(b4afa0_c49220), [c18e380] "m"(b4afa0_c18e380), [elem] "m"(b4afa0_elem), [c8dff0] "m"(b4afa0_c8dff0), [c1d90f0] "m"(b4afa0_c1d90f0)
      : "memory");
}
#else
#error "ai_debug_change_selected_encounter: clang naked draft required"
#endif


/* ai_debug_change_selected_actor (0x4c170) — XBE naked draft (batch 126). */
#if defined(__clang__)
static int (*const b4c170_c119270)(data_t *data, int absolute_index) = datum_absolute_index_to_index;
static void (*const b4c170_cff4d0)(int channel, const char *format, ...) = console_printf;
static void (*const b4c170_c4b1b0)(int encounter_idx, int param_2) = ai_debug_select_actor;
static void (*const b4c170_c59a00)(int *iter, int clump_handle) = encounter_actor_iterator_new;
static int (*const b4c170_c59a50)(int *iter) = encounter_actor_iterator_next;
static void * (*const b4c170_c59a90)(int *iter) = encounter_actor_iterator_prev;
static char * (*const b4c170_c49ac0)(int actor_handle, int object_handle, char with_actor, char *buf, int buf_size) = ai_debug_describe_actor;

__attribute__((naked, noinline))
void ai_debug_change_selected_actor(int actor_index __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xc, %%esp\n\t"
      "movl 0x5ac9f4, %%eax\n\t"
      "movl 0x5ab270, %%ecx\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c119270]\n\t"
      "movl %%eax, %%edi\n\t"
      "addl $8, %%esp\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .Lai_debug_change_selected_actor_1\n\t"
      "pushl $0x25b0d0\n\t"
      "pushl %%eax\n\t"
      "call *%[cff4d0]\n\t"
      "pushl $-1\n\t"
      "pushl $-1\n\t"
      "call *%[c4b1b0]\n\t"
      "addl $0x10, %%esp\n\t"
      "popl %%edi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lai_debug_change_selected_actor_1:\n\t"
      "movl 0x5ac9f4, %%edx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edx\n\t"
      "leal -0xc(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "xorl %%esi, %%esi\n\t"
      "call *%[c59a00]\n\t"
      "movl 0x5ac9f8, %%eax\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lai_debug_change_selected_actor_3\n\t"
      "leal -0xc(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c59a50]\n\t"
      "addl $4, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lai_debug_change_selected_actor_3\n\t"
      "movl %%edi, %%edi\n\t"
      ".Lai_debug_change_selected_actor_2:\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "cmpl 0x5ac9f8, %%edx\n\t"
      "je .Lai_debug_change_selected_actor_3\n\t"
      "leal -0xc(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "incl %%esi\n\t"
      "call *%[c59a50]\n\t"
      "addl $4, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lai_debug_change_selected_actor_2\n\t"
      ".Lai_debug_change_selected_actor_3:\n\t"
      "movb 0x8(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lai_debug_change_selected_actor_4\n\t"
      "leal -0xc(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c59a50]\n\t"
      "addl $4, %%esp\n\t"
      "incl %%esi\n\t"
      "jmp .Lai_debug_change_selected_actor_5\n\t"
      ".Lai_debug_change_selected_actor_4:\n\t"
      "leal -0xc(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c59a90]\n\t"
      "addl $4, %%esp\n\t"
      "decl %%esi\n\t"
      ".Lai_debug_change_selected_actor_5:\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lai_debug_change_selected_actor_6\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "pushl $0x100\n\t"
      "pushl $0x5ab100\n\t"
      "pushl $1\n\t"
      "pushl $-1\n\t"
      "pushl %%eax\n\t"
      "call *%[c49ac0]\n\t"
      "movswl 0x2a(%%edi), %%ecx\n\t"
      "pushl $0x5ab100\n\t"
      "movswl %%si, %%edx\n\t"
      "pushl %%ecx\n\t"
      "incl %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x25b0c0\n\t"
      "pushl $0\n\t"
      "call *%[cff4d0]\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movl 0x5ac9f4, %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c4b1b0]\n\t"
      "addl $0x30, %%esp\n\t"
      "popl %%esi\n\t"
      "popl %%edi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lai_debug_change_selected_actor_6:\n\t"
      "pushl $0x25b0b0\n\t"
      "pushl $0\n\t"
      "call *%[cff4d0]\n\t"
      "movl 0x5ac9f4, %%edx\n\t"
      "pushl $-1\n\t"
      "pushl %%edx\n\t"
      "call *%[c4b1b0]\n\t"
      "addl $0x10, %%esp\n\t"
      "popl %%esi\n\t"
      "popl %%edi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c119270] "m"(b4c170_c119270), [cff4d0] "m"(b4c170_cff4d0), [c4b1b0] "m"(b4c170_c4b1b0), [c59a00] "m"(b4c170_c59a00), [c59a50] "m"(b4c170_c59a50), [c59a90] "m"(b4c170_c59a90), [c49ac0] "m"(b4c170_c49ac0)
      : "memory");
}
#else
#error "ai_debug_change_selected_actor: clang naked draft required"
#endif


/* FUN_000490C0 (0x490c0) — XBE naked draft (batch 153). */
#if defined(__clang__)


__attribute__((naked, noinline))
void FUN_000490C0(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ebx\n\t"
      "movl 0x331f5c, %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "orl $0xffffffff, %%edi\n\t"
      "orl $0xffffffff, %%esi\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "leal 0x4(%%ebx), %%eax\n\t"
      ".LFUN_000490C0_1:\n\t"
      "movb 0x8(%%eax), %%dl\n\t"
      "testb %%dl, %%dl\n\t"
      "je .LFUN_000490C0_2\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "cmpl %%edx, -0x4(%%eax)\n\t"
      "jne .LFUN_000490C0_2\n\t"
      "movl (%%eax), %%edx\n\t"
      "cmpl %%esi, %%edx\n\t"
      "jle .LFUN_000490C0_2\n\t"
      "movl %%ecx, %%edi\n\t"
      "movl %%edx, %%esi\n\t"
      ".LFUN_000490C0_2:\n\t"
      "incl %%ecx\n\t"
      "addl $0x1ca7c, %%eax\n\t"
      "cmpw $0x20, %%cx\n\t"
      "jl .LFUN_000490C0_1\n\t"
      "cmpw $-1, %%di\n\t"
      "jne .LFUN_000490C0_3\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "xorl %%eax, %%eax\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000490C0_3:\n\t"
      "movswl %%di, %%eax\n\t"
      "imull $0x1ca7c, %%eax, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "addl %%ebx, %%eax\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "FUN_000490C0: clang naked draft required"
#endif


/* FUN_00049280 (0x49280) — XBE naked draft (batch 149). */
#if defined(__clang__)
static void (*const b49280_c189450)(int flag, float *point_a, float *point_b, void *color, float scale) = FUN_00189450;
static void (*const b49280_c1893e0)(int flag, float *point, float *dir, float scale, void *color) = FUN_001893e0;

__attribute__((naked, noinline))
void FUN_00049280(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%esi\n\t"
      "movw 0x8(%%ebp), %%si\n\t"
      "testw %%si, %%si\n\t"
      "pushl %%edi\n\t"
      "jle .LFUN_00049280_1\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "pushl $0x3dcccccd\n\t"
      "pushl %%ebx\n\t"
      "addl $4, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl $1\n\t"
      "call *%[c189450]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00049280_1:\n\t"
      "xorl %%edi, %%edi\n\t"
      "testw %%si, %%si\n\t"
      "jle .LFUN_00049280_4\n\t"
      "movl 0xc(%%ebp), %%esi\n\t"
      "addl $4, %%esi\n\t"
      ".LFUN_00049280_2:\n\t"
      "testw %%di, %%di\n\t"
      "jle .LFUN_00049280_3\n\t"
      "pushl $0x3dcccccd\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "leal -0x10(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $1\n\t"
      "call *%[c189450]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00049280_3:\n\t"
      "movl 0x31fc44, %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl $0x3ca3d70a\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl $1\n\t"
      "call *%[c1893e0]\n\t"
      "addl $0x14, %%esp\n\t"
      "incl %%edi\n\t"
      "addl $0x10, %%esi\n\t"
      "cmpw 0x8(%%ebp), %%di\n\t"
      "jl .LFUN_00049280_2\n\t"
      ".LFUN_00049280_4:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c189450] "m"(b49280_c189450), [c1893e0] "m"(b49280_c1893e0)
      : "memory");
}
#else
#error "FUN_00049280: clang naked draft required"
#endif


/* FUN_00049300 (0x49300) — XBE naked draft (batch 138). */
#if defined(__clang__)
static void *(*const b49300_elem)(void *, int, int) = tag_block_get_element;
static void (*const b49300_c189450)(int flag, float *point_a, float *point_b, void *color, float scale) = FUN_00189450;

__attribute__((naked, noinline))
void FUN_00049300(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xc, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl $0x60\n\t"
      "addl $0xb0, %%eax\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "movl %%eax, %%edi\n\t"
      "pushl $0xc\n\t"
      "pushl %%ecx\n\t"
      "leal 0x3c(%%edi), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[elem]\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fadds 0x25abcc\n\t"
      "movl 0x4(%%eax), %%esi\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "leal 0x48(%%edi), %%eax\n\t"
      "addl $0x18, %%esp\n\t"
      "fstps 0xc(%%ebp)\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "addl $0x54, %%edi\n\t"
      ".LFUN_00049300_1:\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "pushl $0x18\n\t"
      "pushl %%esi\n\t"
      "pushl %%ecx\n\t"
      "call *%[elem]\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x14(%%esi), %%ebx\n\t"
      "movl (%%esi), %%eax\n\t"
      "pushl $0x10\n\t"
      "pushl %%eax\n\t"
      "cmpl %%edx, %%ebx\n\t"
      "pushl %%edi\n\t"
      "sete %%bl\n\t"
      "call *%[elem]\n\t"
      "movl 0x4(%%esi), %%ecx\n\t"
      "pushl $0x10\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edi\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "call *%[elem]\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "pushl %%edx\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl $1\n\t"
      "call *%[c189450]\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "movzbl %%bl, %%eax\n\t"
      "movl 0x8(%%esi,%%eax,4), %%esi\n\t"
      "movl 0x4(%%ecx), %%eax\n\t"
      "addl $0x38, %%esp\n\t"
      "cmpl %%eax, %%esi\n\t"
      "jne .LFUN_00049300_1\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [elem] "m"(b49300_elem), [c189450] "m"(b49300_c189450)
      : "memory");
}
#else
#error "FUN_00049300: clang naked draft required"
#endif


/* 0x493b0 — store float + two dwords into a 12-byte record */
void FUN_000493B0(float *out, float value, int field_4, int field_8)
{
  *out = value;
  *(int *)((char *)out + 4) = field_4;
  *(int *)((char *)out + 8) = field_8;
}

/* ai_debug_lineoffire_addpill (0x49430) — XBE naked draft (batch 150). */
#if defined(__clang__)
static void (*const b49430_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b49430_exitfn)(int) = system_exit;

__attribute__((naked, noinline))
void ai_debug_lineoffire_addpill(float *vec_a __attribute__((unused)), float *vec_b __attribute__((unused)), int param_3 __attribute__((unused)), char param_4 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movb 0x5acab8, %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lai_debug_lineoffire_addpill_1\n\t"
      "pushl $1\n\t"
      "pushl $0xfc4\n\t"
      "pushl $0x25ab74\n\t"
      "pushl $0x25abd0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lai_debug_lineoffire_addpill_1:\n\t"
      "movl 0x5acad4, %%eax\n\t"
      "cmpl $0x10, %%eax\n\t"
      "jge .Lai_debug_lineoffire_addpill_2\n\t"
      "movb 0x14(%%ebp), %%cl\n\t"
      "flds 0x10(%%ebp)\n\t"
      "movb %%cl, 0x5acad8(%%eax)\n\t"
      "movl 0x5acad4, %%eax\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "leal (%%eax,%%eax,2), %%edx\n\t"
      "leal 0x5acae8(,%%edx,4), %%eax\n\t"
      "movl (%%ecx), %%edx\n\t"
      "movl %%edx, (%%eax)\n\t"
      "movl 0x4(%%ecx), %%edx\n\t"
      "movl %%edx, 0x4(%%eax)\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "movl %%ecx, 0x8(%%eax)\n\t"
      "movl 0x5acad4, %%eax\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "leal (%%eax,%%eax,2), %%edx\n\t"
      "leal 0x5acba8(,%%edx,4), %%eax\n\t"
      "movl (%%ecx), %%edx\n\t"
      "movl %%edx, (%%eax)\n\t"
      "movl 0x4(%%ecx), %%edx\n\t"
      "movl %%edx, 0x4(%%eax)\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "movl %%ecx, 0x8(%%eax)\n\t"
      "movl 0x5acad4, %%edx\n\t"
      "fstps 0x5acc68(,%%edx,4)\n\t"
      "movl 0x5acad4, %%eax\n\t"
      "incl %%eax\n\t"
      "movl %%eax, 0x5acad4\n\t"
      ".Lai_debug_lineoffire_addpill_2:\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b49430_assert), [exitfn] "m"(b49430_exitfn)
      : "memory");
}
#else
#error "ai_debug_lineoffire_addpill: clang naked draft required"
#endif


/* FUN_000494e0 (0x494e0) — XBE naked draft (batch 143). */
#if defined(__clang__)
static void (*const b494e0_c189270)(char flag, float *point_a, float *point_b, void *color) = FUN_00189270;
static void (*const b494e0_c189860)(char flag, void *center, void *height_vec, float radius, void *color) = FUN_00189860;

__attribute__((naked, noinline))
void FUN_000494e0(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xc, %%esp\n\t"
      "movb 0x5acab8, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000494e0_5\n\t"
      "flds 0x5acabc\n\t"
      "movb 0x5acab9, %%al\n\t"
      "fadds 0x5acac8\n\t"
      "testb %%al, %%al\n\t"
      "movl 0x2ee6d4, %%eax\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "flds 0x5acac0\n\t"
      "fadds 0x5acacc\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "flds 0x5acac4\n\t"
      "fadds 0x5acad0\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "jne .LFUN_000494e0_1\n\t"
      "movl 0x2ee6d0, %%eax\n\t"
      ".LFUN_000494e0_1:\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "leal -0xc(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x5acabc\n\t"
      "pushl $1\n\t"
      "call *%[c189270]\n\t"
      "movl 0x5acad4, %%eax\n\t"
      "addl $0x10, %%esp\n\t"
      "xorl %%esi, %%esi\n\t"
      "testl %%eax, %%eax\n\t"
      "jle .LFUN_000494e0_4\n\t"
      "pushl %%edi\n\t"
      "movl $0x5acae8, %%edi\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_000494e0_2:\n\t"
      "movb 0x5acad8(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "movl 0x2ee6d0, %%eax\n\t"
      "jne .LFUN_000494e0_3\n\t"
      "movl 0x2ee6d8, %%eax\n\t"
      ".LFUN_000494e0_3:\n\t"
      "movl 0x5acc68(,%%esi,4), %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "leal 0xc0(%%edi), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "pushl $1\n\t"
      "call *%[c189860]\n\t"
      "movl 0x5acad4, %%eax\n\t"
      "addl $0x14, %%esp\n\t"
      "incl %%esi\n\t"
      "addl $0xc, %%edi\n\t"
      "cmpl %%eax, %%esi\n\t"
      "jl .LFUN_000494e0_2\n\t"
      "popl %%edi\n\t"
      ".LFUN_000494e0_4:\n\t"
      "popl %%esi\n\t"
      ".LFUN_000494e0_5:\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c189270] "m"(b494e0_c189270), [c189860] "m"(b494e0_c189860)
      : "memory");
}
#else
#error "FUN_000494e0: clang naked draft required"
#endif


/* FUN_000495b0 (0x495b0) — XBE naked draft (batch 134). */
#if defined(__clang__)
static void (*const b495b0_c189150)(char flag, float *position, float scale, void *color) = FUN_00189150;
static void (*const b495b0_c189320)(int flag, float *point, float *vector, float scale, void *color) = FUN_00189320;
static void (*const b495b0_c189860)(char flag, void *center, void *height_vec, float radius, void *color) = FUN_00189860;
static void (*const b495b0_c189270)(char flag, float *point_a, float *point_b, void *color) = FUN_00189270;

__attribute__((naked, noinline))
void FUN_000495b0(void)
{
  __asm__ volatile(
      "movb 0x5f8cb4, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000495b0_7\n\t"
      "movl 0x2ee6e0, %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "pushl $0x3dcccccd\n\t"
      "pushl $0x5f8cb8\n\t"
      "pushl $1\n\t"
      "call *%[c189150]\n\t"
      "movl 0x2ee6e0, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x3f800000\n\t"
      "pushl $0x5f8cc4\n\t"
      "pushl $0x5f8cb8\n\t"
      "pushl $1\n\t"
      "call *%[c189320]\n\t"
      "movl 0x5f8cd0, %%eax\n\t"
      "addl $0x24, %%esp\n\t"
      "xorl %%esi, %%esi\n\t"
      "testl %%eax, %%eax\n\t"
      "jle .LFUN_000495b0_2\n\t"
      "xorl %%eax, %%eax\n\t"
      "jmp .LFUN_000495b0_1\n\t"
      "leal (%%esp), %%esp\n\t"
      "jmp .LFUN_000495b0_1\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".LFUN_000495b0_1:\n\t"
      "movl 0x2ee6d8, %%edx\n\t"
      "leal (%%eax,%%eax,2), %%ecx\n\t"
      "movl 0x5f8e54(,%%eax,4), %%eax\n\t"
      "pushl %%edx\n\t"
      "shll $2, %%ecx\n\t"
      "pushl %%eax\n\t"
      "leal 0x5f8d94(%%ecx), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal 0x5f8cd4(%%ecx), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $1\n\t"
      "call *%[c189860]\n\t"
      "movl 0x5f8cd0, %%ecx\n\t"
      "addl $0x14, %%esp\n\t"
      "incl %%esi\n\t"
      "movswl %%si, %%eax\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jl .LFUN_000495b0_1\n\t"
      ".LFUN_000495b0_2:\n\t"
      "movl 0x5f8e94, %%ecx\n\t"
      "leal -0x1(%%ecx), %%edx\n\t"
      "xorl %%esi, %%esi\n\t"
      "testl %%edx, %%edx\n\t"
      "jle .LFUN_000495b0_6\n\t"
      "xorl %%eax, %%eax\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_000495b0_3:\n\t"
      "movb 0x5f8cb5, %%dl\n\t"
      "testb %%dl, %%dl\n\t"
      "je .LFUN_000495b0_4\n\t"
      "movl 0x2ee6d4, %%ecx\n\t"
      "jmp .LFUN_000495b0_5\n\t"
      ".LFUN_000495b0_4:\n\t"
      "addl $-2, %%ecx\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "movl 0x2ee6f0, %%ecx\n\t"
      "je .LFUN_000495b0_5\n\t"
      "movl 0x2ee6d0, %%ecx\n\t"
      ".LFUN_000495b0_5:\n\t"
      "leal (%%eax,%%eax,2), %%eax\n\t"
      "pushl %%ecx\n\t"
      "shll $2, %%eax\n\t"
      "leal 0x5f8ea4(%%eax), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal 0x5f8e98(%%eax), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $1\n\t"
      "call *%[c189270]\n\t"
      "movl 0x5f8e94, %%ecx\n\t"
      "addl $0x10, %%esp\n\t"
      "incl %%esi\n\t"
      "movswl %%si, %%eax\n\t"
      "leal -0x1(%%ecx), %%edx\n\t"
      "cmpl %%edx, %%eax\n\t"
      "jl .LFUN_000495b0_3\n\t"
      ".LFUN_000495b0_6:\n\t"
      "popl %%esi\n\t"
      ".LFUN_000495b0_7:\n\t"
      "ret\n\t"
      :
      : [c189150] "m"(b495b0_c189150), [c189320] "m"(b495b0_c189320), [c189860] "m"(b495b0_c189860), [c189270] "m"(b495b0_c189270)
      : "memory");
}
#else
#error "FUN_000495b0: clang naked draft required"
#endif


/* ai_debug_highlight_cluster (0x496c0) — XBE naked draft (batch 134). */
#if defined(__clang__)
static int (*const b496c0_gtime)(void) = game_time_get;
static void (*const b496c0_c58fd0)(int encounter_handle, char update_actor_visibility, int cluster_count, int pvs, char *out_cluster_bv) = FUN_00058fd0;
static void (*const b496c0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b496c0_exitfn)(int) = system_exit;
static void *(*const b496c0_dget)(void *, int) = (void *(*)(void *, int))datum_get;

__attribute__((naked, noinline))
char ai_debug_highlight_cluster(int16_t cluster_index __attribute__((unused)), void *out __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movb 0x5aca6c, %%cl\n\t"
      "xorb %%al, %%al\n\t"
      "testb %%cl, %%cl\n\t"
      "je .Lai_debug_highlight_cluster_6\n\t"
      "cmpl $-1, 0x5ac9f4\n\t"
      "je .Lai_debug_highlight_cluster_6\n\t"
      "call *%[gtime]\n\t"
      "cmpl %%eax, 0x2c8e90\n\t"
      "movl 0x5ac9f4, %%edx\n\t"
      "jne .Lai_debug_highlight_cluster_1\n\t"
      "cmpl %%edx, 0x2c8e8c\n\t"
      "je .Lai_debug_highlight_cluster_2\n\t"
      ".Lai_debug_highlight_cluster_1:\n\t"
      "pushl $0x331f18\n\t"
      "pushl $0\n\t"
      "pushl $0x200\n\t"
      "pushl $0\n\t"
      "pushl %%edx\n\t"
      "call *%[c58fd0]\n\t"
      "addl $0x14, %%esp\n\t"
      "call *%[gtime]\n\t"
      "movl 0x5ac9f4, %%edx\n\t"
      "movl %%eax, 0x2c8e90\n\t"
      "movl %%edx, 0x2c8e8c\n\t"
      ".Lai_debug_highlight_cluster_2:\n\t"
      "pushl %%esi\n\t"
      "movl 0xc(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .Lai_debug_highlight_cluster_3\n\t"
      "pushl $1\n\t"
      "pushl $0x1025\n\t"
      "pushl $0x25ab74\n\t"
      "pushl $0x25abec\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "movl 0x5ac9f4, %%edx\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lai_debug_highlight_cluster_3:\n\t"
      "movswl 0x8(%%ebp), %%eax\n\t"
      "pushl %%edi\n\t"
      "movl %%eax, %%ecx\n\t"
      "andl $0x1f, %%ecx\n\t"
      "movl $1, %%edi\n\t"
      "shll %%cl, %%edi\n\t"
      "sarl $5, %%eax\n\t"
      "testl %%edi, 0x331f18(,%%eax,4)\n\t"
      "popl %%edi\n\t"
      "je .Lai_debug_highlight_cluster_5\n\t"
      "movl 0x5ab270, %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movb 0xd(%%eax), %%cl\n\t"
      "addl $8, %%esp\n\t"
      "testb %%cl, %%cl\n\t"
      "je .Lai_debug_highlight_cluster_4\n\t"
      "movl 0x2ee6e0, %%ecx\n\t"
      "movl %%ecx, (%%esi)\n\t"
      "movb $1, %%al\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lai_debug_highlight_cluster_4:\n\t"
      "movl 0x2ee6d8, %%edx\n\t"
      "movl %%edx, (%%esi)\n\t"
      "movb $1, %%al\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lai_debug_highlight_cluster_5:\n\t"
      "movl 0x2ee6c8, %%eax\n\t"
      "movl %%eax, (%%esi)\n\t"
      "movb $1, %%al\n\t"
      "popl %%esi\n\t"
      ".Lai_debug_highlight_cluster_6:\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [gtime] "m"(b496c0_gtime), [c58fd0] "m"(b496c0_c58fd0), [assert] "m"(b496c0_assert), [exitfn] "m"(b496c0_exitfn), [dget] "m"(b496c0_dget)
      : "memory");
}
#else
#error "ai_debug_highlight_cluster: clang naked draft required"
#endif


/* FUN_000497c0 (0x497c0) — XBE naked draft (batch 133). */
#if defined(__clang__)
static void (*const b497c0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b497c0_exitfn)(int) = system_exit;
static void (*const b497c0_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;

__attribute__((naked, noinline))
void FUN_000497c0(void)
{
  __asm__ volatile(
      "movl 0x5accac, %%ecx\n\t"
      "pushl %%esi\n\t"
      "xorl %%esi, %%esi\n\t"
      "testl %%ecx, %%ecx\n\t"
      "jle .LFUN_000497c0_4\n\t"
      "movl $0x5accb8, %%edx\n\t"
      ".LFUN_000497c0_1:\n\t"
      "cmpw %%bx, 0x5e4cb0(,%%esi,2)\n\t"
      "jne .LFUN_000497c0_2\n\t"
      "flds -0x8(%%edx)\n\t"
      "fsubs (%%edi)\n\t"
      "flds -0x4(%%edx)\n\t"
      "fsubs 0x4(%%edi)\n\t"
      "flds (%%edx)\n\t"
      "fsubs 0x8(%%edi)\n\t"
      "fld %%st(2)\n\t"
      ".byte 0xd8, 0xcb\n\t"
      "fld %%st(2)\n\t"
      ".byte 0xd8, 0xcb\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fld %%st(1)\n\t"
      ".byte 0xd8, 0xca\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fcomps 0x25ac64\n\t"
      "fstp %%st(0)\n\t"
      "fnstsw %%ax\n\t"
      "fstp %%st(0)\n\t"
      "testb $5, %%ah\n\t"
      "fstp %%st(0)\n\t"
      "jnp .LFUN_000497c0_3\n\t"
      ".LFUN_000497c0_2:\n\t"
      "incl %%esi\n\t"
      "addl $0xc, %%edx\n\t"
      "cmpl %%ecx, %%esi\n\t"
      "jl .LFUN_000497c0_1\n\t"
      "jmp .LFUN_000497c0_4\n\t"
      ".LFUN_000497c0_3:\n\t"
      "cmpl %%ecx, %%esi\n\t"
      "jl .LFUN_000497c0_5\n\t"
      ".LFUN_000497c0_4:\n\t"
      "cmpl $0x4000, %%ecx\n\t"
      "jge .LFUN_000497c0_8\n\t"
      "movl %%ecx, %%esi\n\t"
      "incl %%ecx\n\t"
      "movl %%ecx, 0x5accac\n\t"
      "movl (%%edi), %%edx\n\t"
      "leal (%%esi,%%esi,2), %%eax\n\t"
      "leal 0x5accb0(,%%eax,4), %%ecx\n\t"
      "movl %%edx, (%%ecx)\n\t"
      "movl 0x4(%%edi), %%eax\n\t"
      "movl %%eax, 0x4(%%ecx)\n\t"
      "movl 0x8(%%edi), %%edx\n\t"
      "movl %%edx, 0x8(%%ecx)\n\t"
      "movw $0, 0x5dccb0(,%%esi,2)\n\t"
      "movw %%bx, 0x5e4cb0(,%%esi,2)\n\t"
      ".LFUN_000497c0_5:\n\t"
      "cmpl $-1, %%esi\n\t"
      "je .LFUN_000497c0_7\n\t"
      "cmpl $0x7fff, %%esi\n\t"
      "jle .LFUN_000497c0_6\n\t"
      "pushl $1\n\t"
      "pushl $0x107f\n\t"
      "pushl $0x25ab74\n\t"
      "pushl $0x25ac50\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000497c0_6:\n\t"
      "incw 0x5dccb0(,%%esi,2)\n\t"
      ".LFUN_000497c0_7:\n\t"
      "movw %%si, %%ax\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      ".LFUN_000497c0_8:\n\t"
      "movb 0x5acca8, %%al\n\t"
      "orl $0xffffffff, %%esi\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_000497c0_7\n\t"
      "movl 0x5eccb0, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x4000\n\t"
      "pushl $0x25ac00\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $0x10, %%esp\n\t"
      "movw %%si, %%ax\n\t"
      "movb $1, 0x5acca8\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b497c0_assert), [exitfn] "m"(b497c0_exitfn), [c8f390] "m"(b497c0_c8f390)
      : "memory");
}
#else
#error "FUN_000497c0: clang naked draft required"
#endif


/* FUN_000498d0 (0x498d0) — XBE naked draft (batch 145). */
#if defined(__clang__)
static void (*const b498d0_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;

__attribute__((naked, noinline))
void FUN_000498d0(void)
{
  __asm__ volatile(
      "pushl %%esi\n\t"
      "movw %%ax, %%si\n\t"
      "orl $0xffffffff, %%eax\n\t"
      "cmpw $-1, %%si\n\t"
      "je .LFUN_000498d0_8\n\t"
      "cmpw $-1, %%di\n\t"
      "je .LFUN_000498d0_8\n\t"
      "movl 0x5eccb0, %%ecx\n\t"
      "xorl %%eax, %%eax\n\t"
      "testl %%ecx, %%ecx\n\t"
      "jle .LFUN_000498d0_4\n\t"
      "movl $0x5eccb6, %%edx\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_000498d0_1:\n\t"
      "cmpw %%si, -0x2(%%edx)\n\t"
      "jne .LFUN_000498d0_2\n\t"
      "cmpw %%di, (%%edx)\n\t"
      "je .LFUN_000498d0_3\n\t"
      ".LFUN_000498d0_2:\n\t"
      "incl %%eax\n\t"
      "addl $6, %%edx\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jl .LFUN_000498d0_1\n\t"
      "jmp .LFUN_000498d0_4\n\t"
      ".LFUN_000498d0_3:\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jl .LFUN_000498d0_5\n\t"
      ".LFUN_000498d0_4:\n\t"
      "cmpl $0x2000, %%ecx\n\t"
      "jge .LFUN_000498d0_6\n\t"
      "movl %%ecx, %%eax\n\t"
      "incl %%ecx\n\t"
      "movl %%ecx, 0x5eccb0\n\t"
      "leal (%%eax,%%eax,2), %%ecx\n\t"
      "shll $1, %%ecx\n\t"
      "movw %%si, 0x5eccb4(%%ecx)\n\t"
      "movw %%di, 0x5eccb6(%%ecx)\n\t"
      "movw $0, 0x5eccb8(%%ecx)\n\t"
      ".LFUN_000498d0_5:\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_000498d0_8\n\t"
      "leal (%%eax,%%eax,2), %%ecx\n\t"
      "incw 0x5eccb8(,%%ecx,2)\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      ".LFUN_000498d0_6:\n\t"
      "movb 0x5acca8, %%al\n\t"
      "orl $0xffffffff, %%esi\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_000498d0_7\n\t"
      "movl 0x5accac, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x2000\n\t"
      "pushl $0x25ac68\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $0x10, %%esp\n\t"
      "movb $1, 0x5acca8\n\t"
      ".LFUN_000498d0_7:\n\t"
      "movl %%esi, %%eax\n\t"
      ".LFUN_000498d0_8:\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      :
      : [c8f390] "m"(b498d0_c8f390)
      : "memory");
}
#else
#error "FUN_000498d0: clang naked draft required"
#endif


/* FUN_00049990 (0x49990) — XBE naked draft (batch 133). */
#if defined(__clang__)
static int (*const b49990_c1d90f0)(char *buffer, const char *format, ...) = crt_sprintf;
static void (*const b49990_c189cb0)(char flag, void *position, void *string, int color) = FUN_00189cb0;
static void (*const b49990_c189270)(char flag, float *point_a, float *point_b, void *color) = FUN_00189270;

__attribute__((naked, noinline))
void FUN_00049990(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x34, %%esp\n\t"
      "movl 0x5accac, %%eax\n\t"
      "pushl %%esi\n\t"
      "xorl %%esi, %%esi\n\t"
      "testl %%eax, %%eax\n\t"
      "pushl %%edi\n\t"
      "movl $0x2ee6cc, -0x34(%%ebp)\n\t"
      "movl $0x2ee6d8, -0x30(%%ebp)\n\t"
      "movl $0x2ee6ec, -0x2c(%%ebp)\n\t"
      "movl $0x2ee6dc, -0x28(%%ebp)\n\t"
      "movl $0x2ee6d4, -0x24(%%ebp)\n\t"
      "movl $0x2ee6f4, -0x20(%%ebp)\n\t"
      "movl $0x2ee700, -0x1c(%%ebp)\n\t"
      "movl $0x2ee6e8, -0x18(%%ebp)\n\t"
      "movl $0x2ee6e4, -0x14(%%ebp)\n\t"
      "movl $0x2ee6d0, -0x10(%%ebp)\n\t"
      "movl $0x2ee6f0, -0xc(%%ebp)\n\t"
      "movl $0x2ee6e0, -0x8(%%ebp)\n\t"
      "movl $0x2ee6c4, -0x4(%%ebp)\n\t"
      "jle .LFUN_00049990_3\n\t"
      "movl $0x5accb0, %%edi\n\t"
      "jmp .LFUN_00049990_1\n\t"
      "leal (%%esp), %%esp\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_00049990_1:\n\t"
      "movswl 0x5dccb0(,%%esi,2), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x25acb8\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c1d90f0]\n\t"
      "movswl 0x5dccb0(,%%esi,2), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl $0xc, %%eax\n\t"
      "jle .LFUN_00049990_2\n\t"
      "movl $0xc, %%eax\n\t"
      ".LFUN_00049990_2:\n\t"
      "movl -0x34(%%ebp,%%eax,4), %%ecx\n\t"
      "movl (%%ecx), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x5ab100\n\t"
      "pushl %%edi\n\t"
      "pushl $1\n\t"
      "call *%[c189cb0]\n\t"
      "movl 0x5accac, %%eax\n\t"
      "addl $0x10, %%esp\n\t"
      "incl %%esi\n\t"
      "addl $0xc, %%edi\n\t"
      "cmpl %%eax, %%esi\n\t"
      "jl .LFUN_00049990_1\n\t"
      ".LFUN_00049990_3:\n\t"
      "movl 0x5eccb0, %%eax\n\t"
      "xorl %%edi, %%edi\n\t"
      "testl %%eax, %%eax\n\t"
      "jle .LFUN_00049990_6\n\t"
      "movl $0x5eccb8, %%esi\n\t"
      ".LFUN_00049990_4:\n\t"
      "movswl (%%esi), %%eax\n\t"
      "cmpl $0xc, %%eax\n\t"
      "jle .LFUN_00049990_5\n\t"
      "movl $0xc, %%eax\n\t"
      ".LFUN_00049990_5:\n\t"
      "movl -0x34(%%ebp,%%eax,4), %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "movswl -0x2(%%esi), %%eax\n\t"
      "leal (%%eax,%%eax,2), %%edx\n\t"
      "pushl %%ecx\n\t"
      "leal 0x5accb0(,%%edx,4), %%eax\n\t"
      "pushl %%eax\n\t"
      "movswl -0x4(%%esi), %%eax\n\t"
      "leal (%%eax,%%eax,2), %%ecx\n\t"
      "leal 0x5accb0(,%%ecx,4), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $1\n\t"
      "call *%[c189270]\n\t"
      "movl 0x5eccb0, %%eax\n\t"
      "addl $0x10, %%esp\n\t"
      "incl %%edi\n\t"
      "addl $6, %%esi\n\t"
      "cmpl %%eax, %%edi\n\t"
      "jl .LFUN_00049990_4\n\t"
      ".LFUN_00049990_6:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c1d90f0] "m"(b49990_c1d90f0), [c189cb0] "m"(b49990_c189cb0), [c189270] "m"(b49990_c189270)
      : "memory");
}
#else
#error "FUN_00049990: clang naked draft required"
#endif


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

/* FUN_00049c70 (0x49c70) — XBE naked draft (batch 132). */
#if defined(__clang__)
static void * (*const b49c70_c8a4e0)(unsigned __int16 local_player_index) = observer_get_camera;
static int16_t (*const b49c70_c86410)(int16_t local_player_index) = director_get_perspective;
static int (*const b49c70_cba3c0)(int16_t local_player_index) = local_player_get_player_index;
static void *(*const b49c70_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static bool (*const b49c70_ray)(unsigned int, float *, float *, int, short *) = FUN_0014df70;
static void *(*const b49c70_tryget)(int, int) = object_try_and_get_and_verify_type;
static void *(*const b49c70_get)(int, int) = object_get_and_verify_type;

__attribute__((naked, noinline))
void FUN_00049c70(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x5c, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl $0\n\t"
      "orl $0xffffffff, %%ebx\n\t"
      "call *%[c8a4e0]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $4, %%esp\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_00049c70_3\n\t"
      "pushl %%edi\n\t"
      "pushl $0\n\t"
      "orl $0xffffffff, %%edi\n\t"
      "call *%[c86410]\n\t"
      "addl $4, %%esp\n\t"
      "testw %%ax, %%ax\n\t"
      "jne .LFUN_00049c70_1\n\t"
      "pushl $0\n\t"
      "call *%[cba3c0]\n\t"
      "pushl %%eax\n\t"
      "movl 0x5aa6d4, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl 0x34(%%eax), %%edi\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_00049c70_1:\n\t"
      "flds 0x20(%%esi)\n\t"
      "leal -0x5c(%%ebp), %%ecx\n\t"
      "fmuls 0x25acf0\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edi\n\t"
      "leal -0xc(%%ebp), %%edx\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "pushl %%edx\n\t"
      "flds 0x24(%%esi)\n\t"
      "pushl %%esi\n\t"
      "fmuls 0x25acf0\n\t"
      "pushl $0x81\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "flds 0x28(%%esi)\n\t"
      "fmuls 0x25acf0\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "call *%[ray]\n\t"
      "addl $0x14, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "popl %%edi\n\t"
      "je .LFUN_00049c70_3\n\t"
      "cmpw $3, -0x5c(%%ebp)\n\t"
      "jne .LFUN_00049c70_3\n\t"
      "movl -0x24(%%ebp), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_00049c70_3\n\t"
      "pushl $3\n\t"
      "pushl %%eax\n\t"
      "call *%[tryget]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_00049c70_3\n\t"
      "movl 0x1a8(%%eax), %%ecx\n\t"
      "cmpl $-1, %%ecx\n\t"
      "movl %%ecx, %%ebx\n\t"
      "jne .LFUN_00049c70_2\n\t"
      "movl 0x1a4(%%eax), %%ebx\n\t"
      ".LFUN_00049c70_2:\n\t"
      "cmpl $-1, %%ebx\n\t"
      "jne .LFUN_00049c70_3\n\t"
      "movl 0x2d4(%%eax), %%eax\n\t"
      "cmpl %%ebx, %%eax\n\t"
      "je .LFUN_00049c70_3\n\t"
      "pushl $3\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl 0x1a8(%%eax), %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "cmpl %%ebx, %%ecx\n\t"
      "movl %%ecx, %%ebx\n\t"
      "jne .LFUN_00049c70_3\n\t"
      "movl 0x1a4(%%eax), %%ebx\n\t"
      ".LFUN_00049c70_3:\n\t"
      "popl %%esi\n\t"
      "movl %%ebx, %%eax\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c8a4e0] "m"(b49c70_c8a4e0), [c86410] "m"(b49c70_c86410), [cba3c0] "m"(b49c70_cba3c0), [dget] "m"(b49c70_dget), [ray] "m"(b49c70_ray), [tryget] "m"(b49c70_tryget), [get] "m"(b49c70_get)
      : "memory");
}
#else
#error "FUN_00049c70: clang naked draft required"
#endif


/* FUN_00049d60 (0x49d60) — XBE naked draft (batch 120). */
#if defined(__clang__)
static void *(*const b49d60_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void * (*const b49d60_c8a4e0)(unsigned __int16 local_player_index) = observer_get_camera;
static float (*const b49d60_norm)(float *) = normalize3d;
static void (*const b49d60_c27f40)(int actor_handle, void *dir_ptr, void *out1, void *out2) = FUN_00027f40;
static void (*const b49d60_c189320)(int flag, float *point, float *vector, float scale, void *color) = FUN_00189320;

__attribute__((naked, noinline))
void FUN_00049d60(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x10, %%esp\n\t"
      "movl 0x6323b4, %%eax\n\t"
      "movl 0x5ac9f8, %%ecx\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "je .LFUN_00049d60_1\n\t"
      "movl %%ecx, %%eax\n\t"
      "movl %%eax, 0x6323b4\n\t"
      "movb $0, 0x6323b9\n\t"
      "movb $0, 0x6323b8\n\t"
      ".LFUN_00049d60_1:\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_00049d60_8\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "movl 0x6325a4, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "pushl $0\n\t"
      "movl %%eax, %%esi\n\t"
      "call *%[c8a4e0]\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_00049d60_5\n\t"
      "flds (%%eax)\n\t"
      "pushl %%edi\n\t"
      "fsubs 0x120(%%esi)\n\t"
      "leal 0x120(%%esi), %%edi\n\t"
      "leal -0x10(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "flds 0x4(%%eax)\n\t"
      "fsubs 0x4(%%edi)\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "flds 0x8(%%eax)\n\t"
      "fsubs 0x8(%%edi)\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "call *%[norm]\n\t"
      "fcomps 0x2533c0\n\t"
      "addl $4, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00049d60_4\n\t"
      "leal -0x2(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl 0x6323b4, %%edx\n\t"
      "leal -0x1(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x10(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c27f40]\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "movl -0x10(%%ebp), %%ecx\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "addl $0x10, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "je .LFUN_00049d60_2\n\t"
      "movb $1, 0x6323b9\n\t"
      "movl %%ecx, 0x6323c8\n\t"
      "movl %%eax, 0x6323cc\n\t"
      "movl %%edx, 0x6323d0\n\t"
      ".LFUN_00049d60_2:\n\t"
      "cmpb $0, -0x2(%%ebp)\n\t"
      "je .LFUN_00049d60_3\n\t"
      "movb $1, 0x6323b8\n\t"
      "movl %%ecx, 0x6323bc\n\t"
      "movl %%eax, 0x6323c0\n\t"
      "movl %%edx, 0x6323c4\n\t"
      ".LFUN_00049d60_3:\n\t"
      "movl 0x2ee6c4, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x3f800000\n\t"
      "leal -0x10(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edi\n\t"
      "pushl $1\n\t"
      "call *%[c189320]\n\t"
      "movl 0x2ee6d0, %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x3f800000\n\t"
      "leal 0x174(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl $1\n\t"
      "call *%[c189320]\n\t"
      "addl $0x28, %%esp\n\t"
      ".LFUN_00049d60_4:\n\t"
      "popl %%edi\n\t"
      ".LFUN_00049d60_5:\n\t"
      "movb 0x6323b9, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00049d60_6\n\t"
      "movl 0x31fc44, %%eax\n\t"
      "flds (%%eax)\n\t"
      "movl 0x2ee6d4, %%ecx\n\t"
      "fmuls 0x2533e8\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x3f800000\n\t"
      "pushl $0x6323c8\n\t"
      "fadds 0x120(%%esi)\n\t"
      "leal -0x10(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $1\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "flds 0x4(%%eax)\n\t"
      "fmuls 0x2533e8\n\t"
      "fadds 0x124(%%esi)\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "flds 0x8(%%eax)\n\t"
      "fmuls 0x2533e8\n\t"
      "fadds 0x128(%%esi)\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "call *%[c189320]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00049d60_6:\n\t"
      "movb 0x6323b8, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00049d60_7\n\t"
      "movl 0x31fc44, %%eax\n\t"
      "flds (%%eax)\n\t"
      "leal -0x10(%%ebp), %%ecx\n\t"
      "fmuls 0x2533e8\n\t"
      "fadds 0x120(%%esi)\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "flds 0x4(%%eax)\n\t"
      "fmuls 0x2533e8\n\t"
      "fadds 0x124(%%esi)\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "flds 0x8(%%eax)\n\t"
      "movl 0x2ee6d8, %%eax\n\t"
      "fmuls 0x2533e8\n\t"
      "pushl %%eax\n\t"
      "pushl $0x3f800000\n\t"
      "pushl $0x6323bc\n\t"
      "fadds 0x128(%%esi)\n\t"
      "pushl %%ecx\n\t"
      "pushl $1\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "call *%[c189320]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00049d60_7:\n\t"
      "popl %%esi\n\t"
      ".LFUN_00049d60_8:\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [dget] "m"(b49d60_dget), [c8a4e0] "m"(b49d60_c8a4e0), [norm] "m"(b49d60_norm), [c27f40] "m"(b49d60_c27f40), [c189320] "m"(b49d60_c189320)
      : "memory");
}
#else
#error "FUN_00049d60: clang naked draft required"
#endif


/* ai_debug_vocalize (0x49f60) — XBE naked draft (batch 136). */
#if defined(__clang__)
static void *(*const b49f60_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static short (*const b49f60_c1a6cd0)(const char *param_1) = FUN_001a6cd0;
static short (*const b49f60_c1a67e0)(const char *param_1) = FUN_001a67e0;
static short (*const b49f60_c1a68d0)(int unit_handle, short priority, char param_3, char param_4, int *param_5, short *vocalization_type_ref, int *sound_definition_index_ref) = FUN_001a68d0;
static void *(*const b49f60_memset)(void *, int, unsigned int) = csmemset;
static void (*const b49f60_c42d20)(void *packet) = ai_communication_packet_new;
static void (*const b49f60_c1a6ef0)(int actor, short count, void *comm_buf) = FUN_001a6ef0;

__attribute__((naked, noinline))
void ai_debug_vocalize(int a0 __attribute__((unused)), int a1 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x38, %%esp\n\t"
      "movl 0x5ac9f8, %%eax\n\t"
      "pushl %%esi\n\t"
      "orl $0xffffffff, %%esi\n\t"
      "cmpl %%esi, %%eax\n\t"
      "je .Lai_debug_vocalize_2\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "movl 0x6325a4, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%edi\n\t"
      "movb $1, 0x5aca89\n\t"
      "movl 0x18(%%edi), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "cmpl %%esi, %%eax\n\t"
      "je .Lai_debug_vocalize_1\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1a6cd0]\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl %%eax, %%ebx\n\t"
      "call *%[c1a67e0]\n\t"
      "addl $8, %%esp\n\t"
      "testw %%bx, %%bx\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "jle .Lai_debug_vocalize_1\n\t"
      "cmpw %%si, %%ax\n\t"
      "je .Lai_debug_vocalize_1\n\t"
      "movl 0x18(%%edi), %%edx\n\t"
      "leal -0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x4(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0\n\t"
      "pushl $1\n\t"
      "pushl $1\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edx\n\t"
      "movl %%esi, -0x8(%%ebp)\n\t"
      "call *%[c1a68d0]\n\t"
      "addl $0x1c, %%esp\n\t"
      "movl %%eax, %%esi\n\t"
      "testw %%si, %%si\n\t"
      "je .Lai_debug_vocalize_1\n\t"
      "pushl $0x30\n\t"
      "leal -0x38(%%ebp), %%eax\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "call *%[memset]\n\t"
      "movw -0x4(%%ebp), %%cx\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "leal -0x28(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movw %%bx, -0x38(%%ebp)\n\t"
      "movw %%cx, -0x36(%%ebp)\n\t"
      "movl %%edx, -0x34(%%ebp)\n\t"
      "call *%[c42d20]\n\t"
      "movl 0x18(%%edi), %%edx\n\t"
      "leal -0x38(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edx\n\t"
      "call *%[c1a6ef0]\n\t"
      "addl $0x1c, %%esp\n\t"
      ".Lai_debug_vocalize_1:\n\t"
      "popl %%edi\n\t"
      "popl %%ebx\n\t"
      ".Lai_debug_vocalize_2:\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [dget] "m"(b49f60_dget), [c1a6cd0] "m"(b49f60_c1a6cd0), [c1a67e0] "m"(b49f60_c1a67e0), [c1a68d0] "m"(b49f60_c1a68d0), [memset] "m"(b49f60_memset), [c42d20] "m"(b49f60_c42d20), [c1a6ef0] "m"(b49f60_c1a6ef0)
      : "memory");
}
#else
#error "ai_debug_vocalize: clang naked draft required"
#endif


/* FUN_0004a030 (0x4a030) — XBE naked draft (batch 119). */
#if defined(__clang__)
static void *(*const b4a030_tryget)(int, int) = object_try_and_get_and_verify_type;
static short (*const b4a030_c1a68d0)(int unit_handle, short priority, char param_3, char param_4, int *param_5, short *vocalization_type_ref, int *sound_definition_index_ref) = FUN_001a68d0;
static void *(*const b4a030_memset)(void *, int, unsigned int) = csmemset;
static void (*const b4a030_c42d20)(void *packet) = ai_communication_packet_new;
static void (*const b4a030_c1a6ef0)(int actor, short count, void *comm_buf) = FUN_001a6ef0;
static const char * (*const b4a030_c1ba1f0)(int tag_index) = tag_get_name;
static char * (*const b4a030_c1d9690)(const char *haystack, const char *needle) = crt_strstr;
static char * (*const b4a030_c1d95d0)(const char *str, int c) = crt_strchr;
static char * (*const b4a030_c1a67b0)(short param_1, unsigned char param_2) = FUN_001a67b0;
static void (*const b4a030_cff4d0)(int channel, const char *format, ...) = console_printf;
static int (*const b4a030_c8dcb0)(const char *s1, const char *s2) = csstrcmp;

__attribute__((naked, noinline))
void FUN_0004a030(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x38, %%esp\n\t"
      "movb 0x6324e0, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0004a030_10\n\t"
      "movl 0x6324e4, %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_0004a030_10\n\t"
      "pushl $3\n\t"
      "pushl %%eax\n\t"
      "call *%[tryget]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_0004a030_9\n\t"
      "testb $4, 0xb6(%%eax)\n\t"
      "jne .LFUN_0004a030_9\n\t"
      "cmpw $0, 0x338(%%eax)\n\t"
      "jne .LFUN_0004a030_10\n\t"
      "movw 0x6324e8, %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "jle .LFUN_0004a030_1\n\t"
      "decw %%ax\n\t"
      "movw %%ax, 0x6324e8\n\t"
      "testw %%ax, %%ax\n\t"
      ".LFUN_0004a030_1:\n\t"
      "jne .LFUN_0004a030_10\n\t"
      "movw 0x6324ea, %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "jl .LFUN_0004a030_8\n\t"
      "cmpw $0xd1, %%ax\n\t"
      "jge .LFUN_0004a030_7\n\t"
      "movl 0x6324e4, %%edx\n\t"
      "pushl %%esi\n\t"
      "movw %%ax, -0x4(%%ebp)\n\t"
      "leal -0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x4(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl $3\n\t"
      "pushl %%edx\n\t"
      "movl $0xffffffff, -0x8(%%ebp)\n\t"
      "call *%[c1a68d0]\n\t"
      "addl $0x1c, %%esp\n\t"
      "movl %%eax, %%esi\n\t"
      "cmpw $2, %%si\n\t"
      "jl .LFUN_0004a030_2\n\t"
      "pushl $0x30\n\t"
      "leal -0x38(%%ebp), %%eax\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "call *%[memset]\n\t"
      "movw -0x4(%%ebp), %%cx\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "leal -0x28(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movw %%cx, -0x36(%%ebp)\n\t"
      "movl %%edx, -0x34(%%ebp)\n\t"
      "movw $4, -0x38(%%ebp)\n\t"
      "movw $0xf, -0x2c(%%ebp)\n\t"
      "call *%[c42d20]\n\t"
      "movl 0x6324e4, %%edx\n\t"
      "leal -0x38(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edx\n\t"
      "call *%[c1a6ef0]\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "addl $0x1c, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_0004a030_2\n\t"
      "pushl %%eax\n\t"
      "call *%[c1ba1f0]\n\t"
      "movl %%eax, %%esi\n\t"
      "pushl $0x25ad10\n\t"
      "pushl %%esi\n\t"
      "call *%[c1d9690]\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_0004a030_3\n\t"
      "pushl $0x5c\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d95d0]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_0004a030_3\n\t"
      "incl %%eax\n\t"
      "je .LFUN_0004a030_3\n\t"
      "movl %%eax, %%esi\n\t"
      "jmp .LFUN_0004a030_3\n\t"
      ".LFUN_0004a030_2:\n\t"
      "movl $0x25ad08, %%esi\n\t"
      ".LFUN_0004a030_3:\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x6324ea, %%ax\n\t"
      "pushl %%esi\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "call *%[c1a67b0]\n\t"
      "addl $8, %%esp\n\t"
      "pushl %%eax\n\t"
      "pushl $0x259f2c\n\t"
      "pushl $0\n\t"
      "call *%[cff4d0]\n\t"
      "movb 0x6324e1, %%al\n\t"
      "addl $0x10, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "popl %%esi\n\t"
      "je .LFUN_0004a030_5\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x6324ea, %%ax\n\t"
      "movw $0xf, 0x6324e8\n\t"
      ".LFUN_0004a030_4:\n\t"
      "incw %%ax\n\t"
      "pushl $0x25ad00\n\t"
      "pushl $0\n\t"
      "movw %%ax, 0x6324ea\n\t"
      "pushl %%eax\n\t"
      "call *%[c1a67b0]\n\t"
      "addl $8, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[c8dcb0]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_0004a030_6\n\t"
      "movb 0x6324e2, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0004a030_5\n\t"
      "movw 0x6324ea, %%ax\n\t"
      "cmpw $0xd1, %%ax\n\t"
      "jl .LFUN_0004a030_4\n\t"
      "jmp .LFUN_0004a030_7\n\t"
      ".LFUN_0004a030_5:\n\t"
      "movw $0xffff, 0x6324ea\n\t"
      "jmp .LFUN_0004a030_8\n\t"
      ".LFUN_0004a030_6:\n\t"
      "movw 0x6324ea, %%ax\n\t"
      ".LFUN_0004a030_7:\n\t"
      "testw %%ax, %%ax\n\t"
      "jl .LFUN_0004a030_8\n\t"
      "cmpw $0xd1, %%ax\n\t"
      "jl .LFUN_0004a030_10\n\t"
      ".LFUN_0004a030_8:\n\t"
      "pushl $0x25acf4\n\t"
      "pushl $0\n\t"
      "call *%[cff4d0]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_0004a030_9:\n\t"
      "movb $0, 0x6324e0\n\t"
      ".LFUN_0004a030_10:\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [tryget] "m"(b4a030_tryget), [c1a68d0] "m"(b4a030_c1a68d0), [memset] "m"(b4a030_memset), [c42d20] "m"(b4a030_c42d20), [c1a6ef0] "m"(b4a030_c1a6ef0), [c1ba1f0] "m"(b4a030_c1ba1f0), [c1d9690] "m"(b4a030_c1d9690), [c1d95d0] "m"(b4a030_c1d95d0), [c1a67b0] "m"(b4a030_c1a67b0), [cff4d0] "m"(b4a030_cff4d0), [c8dcb0] "m"(b4a030_c8dcb0)
      : "memory");
}
#else
#error "FUN_0004a030: clang naked draft required"
#endif


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

/* ai_debug_speak_list (0x4a290) — XBE naked draft (batch 122). */
#if defined(__clang__)
static void *(*const b4a290_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static int (*const b4a290_c1dd801)(const char *a, const char *b) = crt_stricmp;
static void (*const b4a290_cff4d0)(int channel, const char *format, ...) = console_printf;

__attribute__((naked, noinline))
void ai_debug_speak_list(int a0 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x78, %%esp\n\t"
      "movl 0x5ac9f8, %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lai_debug_speak_list_7\n\t"
      "pushl %%ebx\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "movl 0x6325a4, %%eax\n\t"
      "pushl %%eax\n\t"
      "movl $0x25ae38, -0x78(%%ebp)\n\t"
      "movw %%bx, -0x74(%%ebp)\n\t"
      "movb $1, -0x72(%%ebp)\n\t"
      "movl $0x25ae30, -0x70(%%ebp)\n\t"
      "movw %%bx, -0x6c(%%ebp)\n\t"
      "movb %%bl, -0x6a(%%ebp)\n\t"
      "movl $0x25ae24, -0x68(%%ebp)\n\t"
      "movw $6, -0x64(%%ebp)\n\t"
      "movb %%bl, -0x62(%%ebp)\n\t"
      "movl $0x25ae14, -0x60(%%ebp)\n\t"
      "movw $0x15, -0x5c(%%ebp)\n\t"
      "movb %%bl, -0x5a(%%ebp)\n\t"
      "movl $0x25ae08, -0x58(%%ebp)\n\t"
      "movw $0x1d, -0x54(%%ebp)\n\t"
      "movb %%bl, -0x52(%%ebp)\n\t"
      "movl $0x25adf8, -0x50(%%ebp)\n\t"
      "movw $0x31, -0x4c(%%ebp)\n\t"
      "movb %%bl, -0x4a(%%ebp)\n\t"
      "movl $0x25ade0, -0x48(%%ebp)\n\t"
      "movw $0x50, -0x44(%%ebp)\n\t"
      "movb %%bl, -0x42(%%ebp)\n\t"
      "movl $0x25add0, -0x40(%%ebp)\n\t"
      "movw $0x60, -0x3c(%%ebp)\n\t"
      "movb %%bl, -0x3a(%%ebp)\n\t"
      "movl $0x25adc4, -0x38(%%ebp)\n\t"
      "movw $0x6c, -0x34(%%ebp)\n\t"
      "movb %%bl, -0x32(%%ebp)\n\t"
      "movl $0x25adb0, -0x30(%%ebp)\n\t"
      "movw $0x7b, -0x2c(%%ebp)\n\t"
      "movb %%bl, -0x2a(%%ebp)\n\t"
      "movl $0x25ada8, -0x28(%%ebp)\n\t"
      "movw $0x94, -0x24(%%ebp)\n\t"
      "movb %%bl, -0x22(%%ebp)\n\t"
      "movl $0x25ad98, -0x20(%%ebp)\n\t"
      "movw $0xb1, -0x1c(%%ebp)\n\t"
      "movb %%bl, -0x1a(%%ebp)\n\t"
      "movl $0x25ad84, -0x18(%%ebp)\n\t"
      "movw $0xbc, -0x14(%%ebp)\n\t"
      "movb %%bl, -0x12(%%ebp)\n\t"
      "movl $0x25ad70, -0x10(%%ebp)\n\t"
      "movw $0xc5, -0xc(%%ebp)\n\t"
      "movb %%bl, -0xa(%%ebp)\n\t"
      "movl %%ebx, -0x8(%%ebp)\n\t"
      "movw $0xffff, -0x4(%%ebp)\n\t"
      "movb %%bl, -0x2(%%ebp)\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%edi\n\t"
      "addl $8, %%esp\n\t"
      "leal -0x78(%%ebp), %%esi\n\t"
      "movl $0x25ae38, %%eax\n\t"
      "jmp .Lai_debug_speak_list_1\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".Lai_debug_speak_list_1:\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "call *%[c1dd801]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lai_debug_speak_list_2\n\t"
      "movl 0x8(%%esi), %%eax\n\t"
      "addl $8, %%esi\n\t"
      "cmpl %%ebx, %%eax\n\t"
      "jne .Lai_debug_speak_list_1\n\t"
      "jmp .Lai_debug_speak_list_3\n\t"
      ".Lai_debug_speak_list_2:\n\t"
      "cmpl %%ebx, (%%esi)\n\t"
      "jne .Lai_debug_speak_list_5\n\t"
      ".Lai_debug_speak_list_3:\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x25ad28\n\t"
      "pushl %%ebx\n\t"
      "call *%[cff4d0]\n\t"
      "addl $0xc, %%esp\n\t"
      "leal -0x78(%%ebp), %%esi\n\t"
      "movl $0x25ae38, %%eax\n\t"
      "jmp .Lai_debug_speak_list_4\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".Lai_debug_speak_list_4:\n\t"
      "pushl %%eax\n\t"
      "pushl $0x25ad1c\n\t"
      "pushl %%ebx\n\t"
      "call *%[cff4d0]\n\t"
      "movl 0x8(%%esi), %%eax\n\t"
      "addl $8, %%esi\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl %%ebx, %%eax\n\t"
      "jne .Lai_debug_speak_list_4\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lai_debug_speak_list_5:\n\t"
      "cmpl $-1, 0x18(%%edi)\n\t"
      "je .Lai_debug_speak_list_6\n\t"
      "movw 0x4(%%esi), %%ax\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .Lai_debug_speak_list_6\n\t"
      "movb 0x6(%%esi), %%cl\n\t"
      "movb $1, 0x5aca89\n\t"
      "movb $1, 0x6324e0\n\t"
      "movw %%bx, 0x6324e8\n\t"
      "movb $1, 0x6324e1\n\t"
      "movb %%cl, 0x6324e2\n\t"
      "movl 0x18(%%edi), %%edx\n\t"
      "movl %%edx, 0x6324e4\n\t"
      "movw %%ax, 0x6324ea\n\t"
      ".Lai_debug_speak_list_6:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      ".Lai_debug_speak_list_7:\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [dget] "m"(b4a290_dget), [c1dd801] "m"(b4a290_c1dd801), [cff4d0] "m"(b4a290_cff4d0)
      : "memory");
}
#else
#error "ai_debug_speak_list: clang naked draft required"
#endif


/* FUN_0004a770 (0x4a770) — XBE naked draft (batch 130). */
#if defined(__clang__)
static int (*const b4a770_c119270)(data_t *data, int absolute_index) = datum_absolute_index_to_index;
static char * (*const b4a770_c8d9d0)(char *buffer, const char *format, ...) = csprintf;
static void (*const b4a770_c189cb0)(char flag, void *position, void *string, int color) = FUN_00189cb0;

__attribute__((naked, noinline))
void FUN_0004a770(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xc, %%esp\n\t"
      "movb 0x6323d4, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0004a770_6\n\t"
      "movl 0x6323d8, %%eax\n\t"
      "movl 0x6325a4, %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c119270]\n\t"
      "movl %%eax, %%edi\n\t"
      "addl $8, %%esp\n\t"
      "testl %%edi, %%edi\n\t"
      "je .LFUN_0004a770_5\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "cmpw %%bx, 0x6323dc\n\t"
      "jle .LFUN_0004a770_5\n\t"
      "pushl %%esi\n\t"
      ".LFUN_0004a770_1:\n\t"
      "movl 0x5ab23c, %%eax\n\t"
      "movswl %%bx, %%esi\n\t"
      "shll $2, %%esi\n\t"
      "movl 0x6323e0(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c119270]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_0004a770_4\n\t"
      "movl 0x31fc44, %%ecx\n\t"
      "flds (%%ecx)\n\t"
      "fmuls 0x2533e8\n\t"
      "fadds 0x120(%%edi)\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "flds 0x4(%%ecx)\n\t"
      "fmuls 0x2533e8\n\t"
      "fadds 0x124(%%edi)\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "flds 0x8(%%ecx)\n\t"
      "fmuls 0x2533e8\n\t"
      "fadds 0x128(%%edi)\n\t"
      "flds 0xe0(%%eax)\n\t"
      "fmuls 0x2555d0\n\t"
      "fadds -0xc(%%ebp)\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "flds 0xe4(%%eax)\n\t"
      "fmuls 0x2555d0\n\t"
      "fadds -0x8(%%ebp)\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "flds 0xe8(%%eax)\n\t"
      "movb 0x55c(%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "fmuls 0x2555d0\n\t"
      ".byte 0xd8, 0xc1\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "je .LFUN_0004a770_2\n\t"
      "cmpw $1, 0x56c(%%edi)\n\t"
      "jne .LFUN_0004a770_2\n\t"
      "movl 0x6323e0(%%esi), %%eax\n\t"
      "movl 0x570(%%edi), %%ecx\n\t"
      "cmpl %%eax, %%ecx\n\t"
      "movl 0x2ee6e0, %%eax\n\t"
      "je .LFUN_0004a770_3\n\t"
      ".LFUN_0004a770_2:\n\t"
      "movl 0x2ee6c4, %%eax\n\t"
      ".LFUN_0004a770_3:\n\t"
      "flds 0x632460(%%esi)\n\t"
      "pushl %%eax\n\t"
      "subl $8, %%esp\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x25aec8\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x10, %%esp\n\t"
      "pushl %%eax\n\t"
      "leal -0xc(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $1\n\t"
      "call *%[c189cb0]\n\t"
      "addl $0x10, %%esp\n\t"
      ".LFUN_0004a770_4:\n\t"
      "incl %%ebx\n\t"
      "cmpw 0x6323dc, %%bx\n\t"
      "jl .LFUN_0004a770_1\n\t"
      "popl %%esi\n\t"
      ".LFUN_0004a770_5:\n\t"
      "popl %%edi\n\t"
      "popl %%ebx\n\t"
      ".LFUN_0004a770_6:\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c119270] "m"(b4a770_c119270), [c8d9d0] "m"(b4a770_c8d9d0), [c189cb0] "m"(b4a770_c189cb0)
      : "memory");
}
#else
#error "FUN_0004a770: clang naked draft required"
#endif


/* FUN_0004a8c0 (0x4a8c0) — XBE naked draft (batch 131). */
#if defined(__clang__)
static int (*const b4a8c0_gtime)(void) = game_time_get;
static void (*const b4a8c0_c189540)(char flag, void *center, float radius, void *color) = FUN_00189540;
static char * (*const b4a8c0_c8d9d0)(char *buffer, const char *format, ...) = csprintf;
static void (*const b4a8c0_c189cb0)(char flag, void *position, void *string, int color) = FUN_00189cb0;

__attribute__((naked, noinline))
void FUN_0004a8c0(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x20, %%esp\n\t"
      "call *%[gtime]\n\t"
      "movl 0x632574, %%edx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x130(%%edx), %%cx\n\t"
      "cmpw 0x132(%%edx), %%cx\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "movl %%ecx, -0x4(%%ebp)\n\t"
      "je .LFUN_0004a8c0_5\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "jmp .LFUN_0004a8c0_2\n\t"
      ".LFUN_0004a8c0_1:\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "jmp .LFUN_0004a8c0_2\n\t"
      "leal (%%esp), %%esp\n\t"
      "movl %%edi, %%edi\n\t"
      ".LFUN_0004a8c0_2:\n\t"
      "movswl %%cx, %%eax\n\t"
      "leal (%%eax,%%eax,4), %%eax\n\t"
      "leal 0x134(%%edx,%%eax,4), %%edi\n\t"
      "movw (%%edi), %%ax\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .LFUN_0004a8c0_4\n\t"
      "testw %%ax, %%ax\n\t"
      "movl 0x2ee6c4, %%ebx\n\t"
      "movl $0x2ee6d8, -0x14(%%ebp)\n\t"
      "movl $0x2ee6e0, -0x10(%%ebp)\n\t"
      "movl $0x2ee6d0, -0xc(%%ebp)\n\t"
      "jl .LFUN_0004a8c0_3\n\t"
      "cmpw $3, %%ax\n\t"
      "jge .LFUN_0004a8c0_3\n\t"
      "movswl %%ax, %%ecx\n\t"
      "movl -0x14(%%ebp,%%ecx,4), %%edx\n\t"
      "movl (%%edx), %%ebx\n\t"
      ".LFUN_0004a8c0_3:\n\t"
      "pushl %%ebx\n\t"
      "pushl $0x3e4ccccd\n\t"
      "leal 0x4(%%edi), %%esi\n\t"
      "pushl %%esi\n\t"
      "pushl $1\n\t"
      "call *%[c189540]\n\t"
      "movl 0x31fc44, %%eax\n\t"
      "flds (%%eax)\n\t"
      "movswl 0x2(%%edi), %%ecx\n\t"
      "fmuls 0x2533e4\n\t"
      "addl $0x10, %%esp\n\t"
      "pushl %%ebx\n\t"
      "movl 0x10(%%edi), %%ebx\n\t"
      "fadds (%%esi)\n\t"
      "fstps -0x20(%%ebp)\n\t"
      "flds 0x4(%%eax)\n\t"
      "fmuls 0x2533e4\n\t"
      "fadds 0x4(%%esi)\n\t"
      "fstps -0x1c(%%ebp)\n\t"
      "flds 0x8(%%eax)\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "fmuls 0x2533e4\n\t"
      "subl %%ebx, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "fadds 0x8(%%esi)\n\t"
      "pushl $0x25aed0\n\t"
      "pushl $0x5ab100\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x10, %%esp\n\t"
      "pushl %%eax\n\t"
      "leal -0x20(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $1\n\t"
      "call *%[c189cb0]\n\t"
      "movl 0x632574, %%edx\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "addl $0x10, %%esp\n\t"
      ".LFUN_0004a8c0_4:\n\t"
      "incb %%cl\n\t"
      "andl $0x1f, %%ecx\n\t"
      "movl %%ecx, %%eax\n\t"
      "cmpw 0x132(%%edx), %%ax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "jne .LFUN_0004a8c0_1\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      ".LFUN_0004a8c0_5:\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [gtime] "m"(b4a8c0_gtime), [c189540] "m"(b4a8c0_c189540), [c8d9d0] "m"(b4a8c0_c8d9d0), [c189cb0] "m"(b4a8c0_c189cb0)
      : "memory");
}
#else
#error "FUN_0004a8c0: clang naked draft required"
#endif


/* FUN_0004a9f0 (0x4a9f0) — XBE naked draft (batch 128). */
#if defined(__clang__)
static float (*const b4a9f0_c121a0)(const float *a, const float *b) = distance_squared3d;

__attribute__((naked, noinline))
void FUN_0004a9f0(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xc, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl $1, %%ebx\n\t"
      "xorl %%edi, %%edi\n\t"
      "movl %%ebx, -0x8(%%ebp)\n\t"
      "movl %%edi, -0x4(%%ebp)\n\t"
      "movl $0x20, -0xc(%%ebp)\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".LFUN_0004a9f0_1:\n\t"
      "movl 0x331f5c, %%eax\n\t"
      "addl %%eax, %%edi\n\t"
      "movb 0xc(%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0004a9f0_6\n\t"
      "movb 0xd(%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0004a9f0_6\n\t"
      "cmpw $0x20, %%bx\n\t"
      "jge .LFUN_0004a9f0_6\n\t"
      "jmp .LFUN_0004a9f0_2\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_0004a9f0_2:\n\t"
      "movl 0x331f5c, %%ecx\n\t"
      "movswl %%bx, %%esi\n\t"
      "imull $0x1ca7c, %%esi, %%esi\n\t"
      "movb 0xc(%%esi,%%ecx,1), %%al\n\t"
      "addl %%ecx, %%esi\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0004a9f0_4\n\t"
      "movb 0xd(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0004a9f0_4\n\t"
      "movl (%%esi), %%ecx\n\t"
      "cmpl (%%edi), %%ecx\n\t"
      "jne .LFUN_0004a9f0_4\n\t"
      "flds 0x28(%%esi)\n\t"
      "fsubs 0x28(%%edi)\n\t"
      "flds 0x2c(%%esi)\n\t"
      "fsubs 0x2c(%%edi)\n\t"
      "flds 0x30(%%esi)\n\t"
      "fsubs 0x30(%%edi)\n\t"
      "fld %%st(0)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fld %%st(3)\n\t"
      ".byte 0xd8, 0xcc\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fld %%st(2)\n\t"
      ".byte 0xd8, 0xcb\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fcomps 0x25337c\n\t"
      "fstp %%st(0)\n\t"
      "fnstsw %%ax\n\t"
      "fstp %%st(0)\n\t"
      "testb $5, %%ah\n\t"
      "fstp %%st(0)\n\t"
      "jp .LFUN_0004a9f0_4\n\t"
      "movb 0x60(%%edi), %%al\n\t"
      "cmpb 0x60(%%esi), %%al\n\t"
      "jne .LFUN_0004a9f0_4\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0004a9f0_3\n\t"
      "leal 0x64(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal 0x64(%%edi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c121a0]\n\t"
      "fcomps 0x25337c\n\t"
      "addl $8, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_0004a9f0_4\n\t"
      ".LFUN_0004a9f0_3:\n\t"
      "movl 0x4(%%edi), %%ecx\n\t"
      "cmpl 0x4(%%esi), %%ecx\n\t"
      "jl .LFUN_0004a9f0_5\n\t"
      "movb $0, 0xc(%%esi)\n\t"
      ".LFUN_0004a9f0_4:\n\t"
      "incl %%ebx\n\t"
      "cmpw $0x20, %%bx\n\t"
      "jl .LFUN_0004a9f0_2\n\t"
      "jmp .LFUN_0004a9f0_6\n\t"
      ".LFUN_0004a9f0_5:\n\t"
      "movb $0, 0xc(%%edi)\n\t"
      ".LFUN_0004a9f0_6:\n\t"
      "movl -0x4(%%ebp), %%edi\n\t"
      "movl -0x8(%%ebp), %%ebx\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "addl $0x1ca7c, %%edi\n\t"
      "incl %%ebx\n\t"
      "decl %%eax\n\t"
      "movl %%edi, -0x4(%%ebp)\n\t"
      "movl %%ebx, -0x8(%%ebp)\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "jne .LFUN_0004a9f0_1\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c121a0] "m"(b4a9f0_c121a0)
      : "memory");
}
#else
#error "FUN_0004a9f0: clang naked draft required"
#endif


/* ai_debug_teleport_to (0x4b0f0) — XBE naked draft (batch 137). */
#if defined(__clang__)
static scenario_t * (*const b4b0f0_c18e380)(void) = global_scenario_get;
static void *(*const b4b0f0_elem)(void *, int, int) = tag_block_get_element;
static void (*const b4b0f0_c1197b0)(data_iter_t *iter, data_t *data) = data_iterator_new;
static void * (*const b4b0f0_c119810)(data_iter_t *iterator) = data_iterator_next;
static void (*const b4b0f0_c143ae0)(int object_handle, float *position, float *forward, float *up) = object_set_position;

__attribute__((naked, noinline))
void ai_debug_teleport_to(int actor_index __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x1c, %%esp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lai_debug_teleport_to_4\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "andl $0xffff, %%eax\n\t"
      "pushl $0xb0\n\t"
      "pushl %%eax\n\t"
      "call *%[c18e380]\n\t"
      "addl $0x42c, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "leal 0xa4(%%eax), %%edi\n\t"
      "movl (%%edi), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jle .Lai_debug_teleport_to_3\n\t"
      "movl 0x5aa6d4, %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x1c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "call *%[c1197b0]\n\t"
      "leal -0x1c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c119810]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%esi, %%esi\n\t"
      "je .Lai_debug_teleport_to_3\n\t"
      ".Lai_debug_teleport_to_1:\n\t"
      "cmpl $-1, 0x34(%%esi)\n\t"
      "je .Lai_debug_teleport_to_2\n\t"
      "movswl %%bx, %%eax\n\t"
      "cdq\n\t"
      "idivl (%%edi)\n\t"
      "pushl $0x34\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "call *%[elem]\n\t"
      "flds 0xc(%%eax)\n\t"
      "fcos\n\t"
      "movl 0x34(%%esi), %%edx\n\t"
      "pushl $0\n\t"
      "leal -0xc(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%edx\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "flds 0xc(%%eax)\n\t"
      "fsin\n\t"
      "movl $0, -0x4(%%ebp)\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "call *%[c143ae0]\n\t"
      "addl $0x1c, %%esp\n\t"
      "incl %%ebx\n\t"
      ".Lai_debug_teleport_to_2:\n\t"
      "leal -0x1c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c119810]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $4, %%esp\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .Lai_debug_teleport_to_1\n\t"
      ".Lai_debug_teleport_to_3:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      ".Lai_debug_teleport_to_4:\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c18e380] "m"(b4b0f0_c18e380), [elem] "m"(b4b0f0_elem), [c1197b0] "m"(b4b0f0_c1197b0), [c119810] "m"(b4b0f0_c119810), [c143ae0] "m"(b4b0f0_c143ae0)
      : "memory");
}
#else
#error "ai_debug_teleport_to: clang naked draft required"
#endif


/* FUN_0004b220 (0x4b220) — XBE naked draft (batch 154). */
#if defined(__clang__)
static void * (*const b4b220_c8a4e0)(unsigned __int16 local_player_index) = observer_get_camera;

__attribute__((naked, noinline))
void FUN_0004b220(void)
{
  __asm__ volatile(
      "pushl %%esi\n\t"
      "pushl $0\n\t"
      "movl %%eax, %%esi\n\t"
      "call *%[c8a4e0]\n\t"
      "movl (%%esi), %%ecx\n\t"
      "movl %%ecx, 0x5ac9a0\n\t"
      "movl 0x4(%%esi), %%edx\n\t"
      "movl %%edx, 0x5ac9a4\n\t"
      "movl 0x8(%%esi), %%esi\n\t"
      "addl $4, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%esi, 0x5ac9a8\n\t"
      "movl %%esi, 0x5ac9b8\n\t"
      "movl %%ecx, 0x5ac9b0\n\t"
      "movl %%edx, 0x5ac9b4\n\t"
      "popl %%esi\n\t"
      "je .LFUN_0004b220_1\n\t"
      "flds (%%eax)\n\t"
      "fsubs 0x5ac9a0\n\t"
      "flds 0x4(%%eax)\n\t"
      "fsubs 0x5ac9a4\n\t"
      "flds 0x8(%%eax)\n\t"
      "fsubs 0x5ac9a8\n\t"
      "fld %%st(0)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fld %%st(3)\n\t"
      ".byte 0xd8, 0xcc\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fld %%st(2)\n\t"
      ".byte 0xd8, 0xcb\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fsqrt\n\t"
      "fstp %%st(3)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "fmuls 0x25afc0\n\t"
      "fstps 0x5ac990\n\t"
      "ret\n\t"
      ".LFUN_0004b220_1:\n\t"
      "movl $0x3d4ccccd, 0x5ac990\n\t"
      "ret\n\t"
      :
      : [c8a4e0] "m"(b4b220_c8a4e0)
      : "memory");
}
#else
#error "FUN_0004b220: clang naked draft required"
#endif


/* 0x4b2b0 */
void FUN_0004b2b0(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* FUN_0004b320 (0x4b320) — XBE naked draft (batch 109). */
#if defined(__clang__)
static void * (*const b4b320_c8a4e0)(unsigned __int16 local_player_index) = observer_get_camera;
static void (*const b4b320_c189450)(int flag, float *point_a, float *point_b, void *color, float scale) = FUN_00189450;
static void (*const b4b320_c1893e0)(int flag, float *point, float *dir, float scale, void *color) = FUN_001893e0;
static void (*const b4b320_c49300)(void) = FUN_00049300;
static char * (*const b4b320_c8d9d0)(char *buffer, const char *format, ...) = csprintf;
static void (*const b4b320_c189cb0)(char flag, void *position, void *string, int color) = FUN_00189cb0;
static void (*const b4b320_c189150)(char flag, float *position, float scale, void *color) = FUN_00189150;
static float (*const b4b320_c5f490)(void *path_state, float *node_pos, float *step_pos, float *out_dist) = path_attractor_weight;

__attribute__((naked, noinline))
void FUN_0004b320(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x20, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl $0\n\t"
      "movl %%eax, %%ebx\n\t"
      "call *%[c8a4e0]\n\t"
      "flds (%%edi)\n\t"
      "fadds 0xc(%%ebx)\n\t"
      "leal 0xc(%%ebx), %%esi\n\t"
      "movl %%eax, %%ecx\n\t"
      "movl 0x31fc44, %%eax\n\t"
      "fmuls 0x253398\n\t"
      "addl $4, %%esp\n\t"
      "testl %%ecx, %%ecx\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "flds 0x4(%%esi)\n\t"
      "fadds 0x4(%%edi)\n\t"
      "fmuls 0x253398\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "flds 0x8(%%esi)\n\t"
      "fadds 0x8(%%edi)\n\t"
      "fmuls 0x253398\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "flds (%%eax)\n\t"
      "fmuls 0x25496c\n\t"
      "fadds -0x14(%%ebp)\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "flds 0x4(%%eax)\n\t"
      "fmuls 0x25496c\n\t"
      "fadds -0x10(%%ebp)\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "flds 0x8(%%eax)\n\t"
      "fmuls 0x25496c\n\t"
      "fadds -0xc(%%ebp)\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "je .LFUN_0004b320_1\n\t"
      "flds (%%ecx)\n\t"
      "fsubs -0x14(%%ebp)\n\t"
      "flds 0x4(%%ecx)\n\t"
      "fsubs -0x10(%%ebp)\n\t"
      "flds 0x8(%%ecx)\n\t"
      "fsubs -0xc(%%ebp)\n\t"
      "fld %%st(0)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fld %%st(2)\n\t"
      ".byte 0xd8, 0xcb\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fld %%st(3)\n\t"
      ".byte 0xd8, 0xcc\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fsqrt\n\t"
      "fstp %%st(3)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "fmuls 0x25afc0\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "jmp .LFUN_0004b320_2\n\t"
      ".LFUN_0004b320_1:\n\t"
      "movl $0x3d4ccccd, -0x4(%%ebp)\n\t"
      ".LFUN_0004b320_2:\n\t"
      "movl 0x18(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_0004b320_4\n\t"
      "pushl $0x3cf5c28f\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%esi\n\t"
      "pushl $1\n\t"
      "call *%[c189450]\n\t"
      "movl 0x18(%%ebp), %%eax\n\t"
      "movl 0x31fc44, %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl $0x3ca3d70a\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl $1\n\t"
      "call *%[c1893e0]\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "addl $0x28, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_0004b320_3\n\t"
      "movl 0x18(%%ebp), %%edx\n\t"
      "movl 0x31fc44, %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl $0x3ca3d70a\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl $1\n\t"
      "call *%[c1893e0]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0004b320_3:\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      ".LFUN_0004b320_4:\n\t"
      "movl 0x1c(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_0004b320_5\n\t"
      "movb 0xc(%%ebp), %%dl\n\t"
      "testb %%dl, %%dl\n\t"
      "je .LFUN_0004b320_5\n\t"
      "movl 0x8(%%ebx), %%ecx\n\t"
      "pushl %%eax\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl $0\n\t"
      "pushl %%ecx\n\t"
      "call *%[c49300]\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_0004b320_5:\n\t"
      "movl 0x20(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_0004b320_6\n\t"
      "flds 0x18(%%ebx)\n\t"
      "pushl %%eax\n\t"
      "subl $8, %%esp\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x25afc4\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x10, %%esp\n\t"
      "pushl %%eax\n\t"
      "leal -0x14(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $1\n\t"
      "call *%[c189cb0]\n\t"
      "flds -0x4(%%ebp)\n\t"
      "movl 0x31fc44, %%eax\n\t"
      "fmuls (%%eax)\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "addl $0x10, %%esp\n\t"
      "fadds -0x14(%%ebp)\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fmuls 0x4(%%eax)\n\t"
      "fadds -0x10(%%ebp)\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fmuls 0x8(%%eax)\n\t"
      "fadds -0xc(%%ebp)\n\t"
      "fstps -0xc(%%ebp)\n\t"
      ".LFUN_0004b320_6:\n\t"
      "movl 0x2c(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_0004b320_9\n\t"
      "flds 0x34(%%ebx)\n\t"
      "fcomps 0x2548fc\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_0004b320_9\n\t"
      "testl %%ecx, %%ecx\n\t"
      "leal 0x38(%%ebx), %%eax\n\t"
      "movl (%%eax), %%edx\n\t"
      "movl %%edx, -0x20(%%ebp)\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl %%edx, -0x1c(%%ebp)\n\t"
      "movl %%eax, -0x18(%%ebp)\n\t"
      "je .LFUN_0004b320_7\n\t"
      "flds (%%ecx)\n\t"
      "fsubs -0x20(%%ebp)\n\t"
      "flds 0x4(%%ecx)\n\t"
      "fsubs -0x1c(%%ebp)\n\t"
      "flds 0x8(%%ecx)\n\t"
      "fsubs -0x18(%%ebp)\n\t"
      "fld %%st(0)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fld %%st(2)\n\t"
      ".byte 0xd8, 0xcb\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fld %%st(3)\n\t"
      ".byte 0xd8, 0xcc\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fsqrt\n\t"
      "fstp %%st(3)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "fmuls 0x25afc0\n\t"
      "fstps 0x18(%%ebp)\n\t"
      "jmp .LFUN_0004b320_8\n\t"
      ".LFUN_0004b320_7:\n\t"
      "movl $0x3d4ccccd, 0x18(%%ebp)\n\t"
      ".LFUN_0004b320_8:\n\t"
      "movl 0x2c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x3e19999a\n\t"
      "leal 0x38(%%ebx), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $1\n\t"
      "call *%[c189150]\n\t"
      "flds 0x18(%%ebp)\n\t"
      "fadds 0x256140\n\t"
      "movl 0x31fc44, %%eax\n\t"
      "movl 0x2c(%%ebp), %%edx\n\t"
      "addl $0x10, %%esp\n\t"
      "fld %%st(0)\n\t"
      "fmuls (%%eax)\n\t"
      "pushl %%edx\n\t"
      "subl $8, %%esp\n\t"
      "fadds -0x20(%%ebp)\n\t"
      "fstps -0x20(%%ebp)\n\t"
      "fld %%st(0)\n\t"
      "fmuls 0x4(%%eax)\n\t"
      "fadds -0x1c(%%ebp)\n\t"
      "fstps -0x1c(%%ebp)\n\t"
      "fmuls 0x8(%%eax)\n\t"
      "fadds -0x18(%%ebp)\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "flds 0x34(%%ebx)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x25afc4\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x10, %%esp\n\t"
      "pushl %%eax\n\t"
      "leal -0x20(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $1\n\t"
      "call *%[c189cb0]\n\t"
      "addl $0x10, %%esp\n\t"
      ".LFUN_0004b320_9:\n\t"
      "movl 0x10(%%ebp), %%ebx\n\t"
      "testl %%ebx, %%ebx\n\t"
      "je .LFUN_0004b320_11\n\t"
      "movb 0x24(%%ebx), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0004b320_11\n\t"
      "leal 0x18(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edi\n\t"
      "pushl %%esi\n\t"
      "pushl %%ebx\n\t"
      "movl $0x7f7fffff, 0x18(%%ebp)\n\t"
      "call *%[c5f490]\n\t"
      "fstps 0x2c(%%ebp)\n\t"
      "movl 0x24(%%ebp), %%eax\n\t"
      "addl $0x10, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_0004b320_10\n\t"
      "movl 0x2ee6e0, %%edx\n\t"
      "flds 0x18(%%ebp)\n\t"
      "pushl %%edx\n\t"
      "subl $8, %%esp\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x25afc4\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x10, %%esp\n\t"
      "pushl %%eax\n\t"
      "leal -0x14(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $1\n\t"
      "call *%[c189cb0]\n\t"
      "flds -0x4(%%ebp)\n\t"
      "movl 0x31fc44, %%eax\n\t"
      "fmuls (%%eax)\n\t"
      "addl $0x10, %%esp\n\t"
      "fadds -0x14(%%ebp)\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fmuls 0x4(%%eax)\n\t"
      "fadds -0x10(%%ebp)\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fmuls 0x8(%%eax)\n\t"
      "fadds -0xc(%%ebp)\n\t"
      "fstps -0xc(%%ebp)\n\t"
      ".LFUN_0004b320_10:\n\t"
      "movl 0x28(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_0004b320_11\n\t"
      "flds 0x2c(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_0004b320_11\n\t"
      "movl 0x2ee6d0, %%ecx\n\t"
      "flds 0x3c(%%ebx)\n\t"
      "pushl %%ecx\n\t"
      "subl $8, %%esp\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x25afc4\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x10, %%esp\n\t"
      "pushl %%eax\n\t"
      "leal -0x14(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $1\n\t"
      "call *%[c189cb0]\n\t"
      "addl $0x10, %%esp\n\t"
      ".LFUN_0004b320_11:\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c8a4e0] "m"(b4b320_c8a4e0), [c189450] "m"(b4b320_c189450), [c1893e0] "m"(b4b320_c1893e0), [c49300] "m"(b4b320_c49300), [c8d9d0] "m"(b4b320_c8d9d0), [c189cb0] "m"(b4b320_c189cb0), [c189150] "m"(b4b320_c189150), [c5f490] "m"(b4b320_c5f490)
      : "memory");
}
#else
#error "FUN_0004b320: clang naked draft required"
#endif


/* FUN_0004b670 (0x4b670) — XBE naked draft (batch 131). */
#if defined(__clang__)
static void *(*const b4b670_tryget)(int, int) = object_try_and_get_and_verify_type;
static void (*const b4b670_c1aae0)(int object_handle, float *center, float *radius) = FUN_0001aae0;
static void (*const b4b670_c1a0890)(int unit_handle, vector3_t *out_pos, float *out_height_offset, float *out_camera_height) = biped_get_camera_height_and_offset;
static void (*const b4b670_c189860)(char flag, void *center, void *height_vec, float radius, void *color) = FUN_00189860;
static void (*const b4b670_c189540)(char flag, void *center, float radius, void *color) = FUN_00189540;
static void (*const b4b670_c189150)(char flag, float *position, float scale, void *color) = FUN_00189150;

__attribute__((naked, noinline))
void FUN_0004b670(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x20, %%esp\n\t"
      "pushl %%esi\n\t"
      "pushl $1\n\t"
      "pushl %%edi\n\t"
      "call *%[tryget]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $8, %%esp\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_0004b670_5\n\t"
      "movl 0xcc(%%esi), %%eax\n\t"
      "pushl $3\n\t"
      "pushl %%eax\n\t"
      "call *%[tryget]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_0004b670_1\n\t"
      "cmpl %%edi, 0x2d4(%%eax)\n\t"
      "jne .LFUN_0004b670_1\n\t"
      "movl 0xcc(%%esi), %%eax\n\t"
      "leal -0x4(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x14(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c1aae0]\n\t"
      "addl $0xc, %%esp\n\t"
      "movl $0, -0x8(%%ebp)\n\t"
      "jmp .LFUN_0004b670_2\n\t"
      ".LFUN_0004b670_1:\n\t"
      "leal -0x4(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x8(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x14(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "call *%[c1a0890]\n\t"
      "addl $0x10, %%esp\n\t"
      ".LFUN_0004b670_2:\n\t"
      "movb 0x8(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0004b670_3\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_0004b670_3\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edx\n\t"
      "leal -0x20(%%ebp), %%eax\n\t"
      "movl %%ecx, -0x18(%%ebp)\n\t"
      "pushl %%eax\n\t"
      "leal -0x14(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $1\n\t"
      "movl $0, -0x20(%%ebp)\n\t"
      "movl $0, -0x1c(%%ebp)\n\t"
      "call *%[c189860]\n\t"
      "addl $0x14, %%esp\n\t"
      "jmp .LFUN_0004b670_4\n\t"
      ".LFUN_0004b670_3:\n\t"
      "flds -0x4(%%ebp)\n\t"
      "pushl %%ebx\n\t"
      "fmuls 0x25afcc\n\t"
      "pushl %%ecx\n\t"
      "leal -0x14(%%ebp), %%edx\n\t"
      "fstps (%%esp)\n\t"
      "pushl %%edx\n\t"
      "pushl $1\n\t"
      "call *%[c189540]\n\t"
      "addl $0x10, %%esp\n\t"
      ".LFUN_0004b670_4:\n\t"
      "movb 0x8(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0004b670_5\n\t"
      "flds -0x4(%%ebp)\n\t"
      "pushl %%ebx\n\t"
      "fmuls 0x255154\n\t"
      "pushl %%ecx\n\t"
      "leal -0x14(%%ebp), %%eax\n\t"
      "fstps (%%esp)\n\t"
      "pushl %%eax\n\t"
      "pushl $1\n\t"
      "call *%[c189150]\n\t"
      "addl $0x10, %%esp\n\t"
      ".LFUN_0004b670_5:\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [tryget] "m"(b4b670_tryget), [c1aae0] "m"(b4b670_c1aae0), [c1a0890] "m"(b4b670_c1a0890), [c189860] "m"(b4b670_c189860), [c189540] "m"(b4b670_c189540), [c189150] "m"(b4b670_c189150)
      : "memory");
}
#else
#error "FUN_0004b670: clang naked draft required"
#endif


/* 0x4b770 */
void ai_debug_lineofsight(void)
{
  FUN_000497c0();
  FUN_000497c0();
  FUN_000498d0();
}

/* FUN_0004b7a0 (0x4b7a0) — XBE naked draft (batch 157). */
#if defined(__clang__)
static void (*const b4b7a0_c49c70)(void) = FUN_00049c70;
static void *(*const b4b7a0_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static char * (*const b4b7a0_c49ac0)(int actor_handle, int object_handle, char with_actor, char *buf, int buf_size) = ai_debug_describe_actor;
static void (*const b4b7a0_cff4d0)(int channel, const char *format, ...) = console_printf;
static void (*const b4b7a0_c4b1b0)(int encounter_idx, int param_2) = ai_debug_select_actor;

__attribute__((naked, noinline))
void FUN_0004b7a0(void)
{
  __asm__ volatile(
      "pushl %%esi\n\t"
      "call *%[c49c70]\n\t"
      "movl %%eax, %%esi\n\t"
      "cmpl $-1, %%esi\n\t"
      "je .LFUN_0004b7a0_1\n\t"
      "movl 0x6325a4, %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "pushl $0x100\n\t"
      "pushl $0x5ab100\n\t"
      "pushl $1\n\t"
      "pushl $-1\n\t"
      "pushl %%esi\n\t"
      "movl %%eax, %%edi\n\t"
      "call *%[c49ac0]\n\t"
      "pushl $0x5ab100\n\t"
      "pushl $0x25afd0\n\t"
      "pushl $0\n\t"
      "call *%[cff4d0]\n\t"
      "movl 0x34(%%edi), %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%ecx\n\t"
      "call *%[c4b1b0]\n\t"
      "addl $0x30, %%esp\n\t"
      "popl %%edi\n\t"
      "movb $0, 0x5ac9c1\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      ".LFUN_0004b7a0_1:\n\t"
      "pushl $-1\n\t"
      "pushl $-1\n\t"
      "call *%[c4b1b0]\n\t"
      "addl $8, %%esp\n\t"
      "movb $0, 0x5ac9c1\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      :
      : [c49c70] "m"(b4b7a0_c49c70), [dget] "m"(b4b7a0_dget), [c49ac0] "m"(b4b7a0_c49ac0), [cff4d0] "m"(b4b7a0_cff4d0), [c4b1b0] "m"(b4b7a0_c4b1b0)
      : "memory");
}
#else
#error "FUN_0004b7a0: clang naked draft required"
#endif


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


/* FUN_0004bc70 (0x4bc70) — XBE naked draft (batch 109). */
#if defined(__clang__)
static void *(*const b4bc70_tryget)(int, int) = object_try_and_get_and_verify_type;
static vector3_t * (*const b4bc70_c1412f0)(int object_handle, vector3_t *out_position) = object_get_world_position;
static void (*const b4bc70_c4b220)(void) = FUN_0004b220;
static char * (*const b4bc70_c8d9d0)(char *buffer, const char *format, ...) = csprintf;
static void (*const b4bc70_c4b2b0)(void) = FUN_0004b2b0;
static void (*const b4bc70_c189cb0)(char flag, void *position, void *string, int color) = FUN_00189cb0;
static int (*const b4bc70_c1d90f0)(char *buffer, const char *format, ...) = crt_sprintf;
static char * (*const b4bc70_c8dc30)(char *destination, const char *source) = FUN_0008dc30;
static scenario_t * (*const b4bc70_c18e380)(void) = global_scenario_get;
static void (*const b4bc70_c54220)(unsigned int combined_index, void *scenario, char *buffer, int buffer_size) = FUN_00054220;

__attribute__((naked, noinline))
void FUN_0004bc70(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x180, %%esp\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x632574, %%edi\n\t"
      "xorl %%esi, %%esi\n\t"
      "cmpw %%si, 0x3b6(%%edi)\n\t"
      "jle .LFUN_0004bc70_11\n\t"
      "pushl %%ebx\n\t"
      ".LFUN_0004bc70_1:\n\t"
      "movswl %%si, %%eax\n\t"
      "leal (%%eax,%%eax,4), %%eax\n\t"
      "movl 0x3b8(%%edi,%%eax,8), %%ecx\n\t"
      "leal 0x3b8(%%edi,%%eax,8), %%edi\n\t"
      "pushl $3\n\t"
      "pushl %%ecx\n\t"
      "movl %%edi, -0xc(%%ebp)\n\t"
      "call *%[tryget]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_0004bc70_10\n\t"
      "movl (%%edi), %%eax\n\t"
      "leal -0x18(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c1412f0]\n\t"
      "movl 0x31fc44, %%eax\n\t"
      "flds (%%eax)\n\t"
      "addl $8, %%esp\n\t"
      "fmuls 0x253398\n\t"
      "fadds -0x18(%%ebp)\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "flds 0x4(%%eax)\n\t"
      "fmuls 0x253398\n\t"
      "fadds -0x14(%%ebp)\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "flds 0x8(%%eax)\n\t"
      "leal -0x18(%%ebp), %%eax\n\t"
      "fmuls 0x253398\n\t"
      "fadds -0x10(%%ebp)\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "call *%[c4b220]\n\t"
      "movl 0x2ee6e8, %%ecx\n\t"
      "flds 0x4(%%edi)\n\t"
      "pushl %%ecx\n\t"
      "subl $8, %%esp\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x25b098\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x10, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[c4b2b0]\n\t"
      "pushl %%eax\n\t"
      "pushl $1\n\t"
      "call *%[c189cb0]\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpw $0, 0x8(%%edi)\n\t"
      "je .LFUN_0004bc70_4\n\t"
      "pushl $0x25b090\n\t"
      "pushl $0x5ab100\n\t"
      "movl $0x255244, -0x40(%%ebp)\n\t"
      "movl $0x2569f0, -0x3c(%%ebp)\n\t"
      "movl $0x2598a0, -0x38(%%ebp)\n\t"
      "movl $0x259890, -0x34(%%ebp)\n\t"
      "movl $0x25682c, -0x30(%%ebp)\n\t"
      "movl $0x2569b0, -0x2c(%%ebp)\n\t"
      "movl $0x25b088, -0x28(%%ebp)\n\t"
      "movl $0x25b080, -0x24(%%ebp)\n\t"
      "movl $0x25b078, -0x20(%%ebp)\n\t"
      "movl $0x25b070, -0x1c(%%ebp)\n\t"
      "call *%[c1d90f0]\n\t"
      "leal -0x40(%%ebp), %%edx\n\t"
      "movl $0xa, %%esi\n\t"
      "addl $8, %%esp\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "movl %%edx, -0x8(%%ebp)\n\t"
      "movl %%esi, -0x4(%%ebp)\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_0004bc70_2:\n\t"
      "movl %%ebx, %%ecx\n\t"
      "movl $1, %%eax\n\t"
      "shll %%cl, %%eax\n\t"
      "movswl 0x8(%%edi), %%ecx\n\t"
      "testl %%eax, %%ecx\n\t"
      "je .LFUN_0004bc70_3\n\t"
      "pushl $0x25b06c\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8dc30]\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "movl (%%edx), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8dc30]\n\t"
      "addl $0x10, %%esp\n\t"
      ".LFUN_0004bc70_3:\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "addl $4, %%ecx\n\t"
      "incl %%ebx\n\t"
      "decl %%eax\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "jne .LFUN_0004bc70_2\n\t"
      "movl 0x5ac9b8, %%eax\n\t"
      "flds 0x5ac990\n\t"
      "movl 0x5ac9b0, %%ecx\n\t"
      "movl 0x5ac9b4, %%edx\n\t"
      "movl %%eax, 0x5ac9a8\n\t"
      "movl 0x31fc44, %%eax\n\t"
      "movl %%ecx, 0x5ac9a0\n\t"
      "movl 0x2ee6e8, %%ecx\n\t"
      "movl %%edx, 0x5ac9a4\n\t"
      "fmuls (%%eax)\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x5ab100\n\t"
      "fadds 0x5ac9b0\n\t"
      "pushl $0x5ac9a0\n\t"
      "pushl $1\n\t"
      "fstps 0x5ac9b0\n\t"
      "flds 0x5ac990\n\t"
      "fmuls 0x4(%%eax)\n\t"
      "fadds 0x5ac9a4\n\t"
      "fstps 0x5ac9b4\n\t"
      "flds 0x5ac990\n\t"
      "fmuls 0x8(%%eax)\n\t"
      "fadds 0x5ac9a8\n\t"
      "fstps 0x5ac9b8\n\t"
      "call *%[c189cb0]\n\t"
      "addl $0x10, %%esp\n\t"
      ".LFUN_0004bc70_4:\n\t"
      "cmpw $0, 0xa(%%edi)\n\t"
      "je .LFUN_0004bc70_7\n\t"
      "pushl $0x25b05c\n\t"
      "pushl $0x5ab100\n\t"
      "movl $0x256818, -0x80(%%ebp)\n\t"
      "movl $0x256990, -0x7c(%%ebp)\n\t"
      "movl $0x25689c, -0x78(%%ebp)\n\t"
      "movl $0x2568a4, -0x74(%%ebp)\n\t"
      "movl $0x256820, -0x70(%%ebp)\n\t"
      "movl $0x2569f8, -0x6c(%%ebp)\n\t"
      "movl $0x2569f0, -0x68(%%ebp)\n\t"
      "movl $0x256998, -0x64(%%ebp)\n\t"
      "movl $0x256810, -0x60(%%ebp)\n\t"
      "movl $0x25b050, -0x5c(%%ebp)\n\t"
      "movl $0x25b040, -0x58(%%ebp)\n\t"
      "movl $0x25b030, -0x54(%%ebp)\n\t"
      "movl $0x2569bc, -0x50(%%ebp)\n\t"
      "movl $0x2569b0, -0x4c(%%ebp)\n\t"
      "movl $0x254384, -0x48(%%ebp)\n\t"
      "movl $0x25b020, -0x44(%%ebp)\n\t"
      "call *%[c1d90f0]\n\t"
      "movl $0x10, %%esi\n\t"
      "addl $8, %%esp\n\t"
      "xorl %%edi, %%edi\n\t"
      "leal -0x80(%%ebp), %%ebx\n\t"
      "movl %%esi, -0x4(%%ebp)\n\t"
      ".LFUN_0004bc70_5:\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "movl %%edi, %%ecx\n\t"
      "movl $1, %%edx\n\t"
      "shll %%cl, %%edx\n\t"
      "movswl 0xa(%%eax), %%ecx\n\t"
      "testl %%edx, %%ecx\n\t"
      "je .LFUN_0004bc70_6\n\t"
      "pushl $0x25b06c\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8dc30]\n\t"
      "movl (%%ebx), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8dc30]\n\t"
      "addl $0x10, %%esp\n\t"
      ".LFUN_0004bc70_6:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "incl %%edi\n\t"
      "addl $4, %%ebx\n\t"
      "decl %%eax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "jne .LFUN_0004bc70_5\n\t"
      "movl 0x5ac9b0, %%eax\n\t"
      "flds 0x5ac990\n\t"
      "movl 0x5ac9b4, %%ecx\n\t"
      "movl 0x5ac9b8, %%edx\n\t"
      "movl %%eax, 0x5ac9a0\n\t"
      "movl 0x31fc44, %%eax\n\t"
      "movl %%ecx, 0x5ac9a4\n\t"
      "movl %%edx, 0x5ac9a8\n\t"
      "fmuls (%%eax)\n\t"
      "fadds 0x5ac9b0\n\t"
      "fstps 0x5ac9b0\n\t"
      "flds 0x5ac990\n\t"
      "fmuls 0x4(%%eax)\n\t"
      "fadds 0x5ac9a4\n\t"
      "fstps 0x5ac9b4\n\t"
      "flds 0x5ac990\n\t"
      "fmuls 0x8(%%eax)\n\t"
      "movl 0x2ee6e8, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x5ab100\n\t"
      "fadds 0x5ac9a8\n\t"
      "pushl $0x5ac9a0\n\t"
      "pushl $1\n\t"
      "fstps 0x5ac9b8\n\t"
      "call *%[c189cb0]\n\t"
      "movl -0xc(%%ebp), %%edi\n\t"
      "addl $0x10, %%esp\n\t"
      ".LFUN_0004bc70_7:\n\t"
      "cmpw $0, 0xc(%%edi)\n\t"
      "jle .LFUN_0004bc70_10\n\t"
      "pushl $0x25b018\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c1d90f0]\n\t"
      "xorl %%esi, %%esi\n\t"
      "addl $8, %%esp\n\t"
      "cmpw %%si, 0xc(%%edi)\n\t"
      "jle .LFUN_0004bc70_9\n\t"
      "jmp .LFUN_0004bc70_8\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_0004bc70_8:\n\t"
      "leal -0x180(%%ebp), %%ecx\n\t"
      "pushl $0x100\n\t"
      "pushl %%ecx\n\t"
      "call *%[c18e380]\n\t"
      "movswl %%si, %%edx\n\t"
      "pushl %%eax\n\t"
      "movl 0x10(%%edi,%%edx,4), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c54220]\n\t"
      "pushl $0x25b06c\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8dc30]\n\t"
      "leal -0x180(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8dc30]\n\t"
      "addl $0x20, %%esp\n\t"
      "incl %%esi\n\t"
      "cmpw 0xc(%%edi), %%si\n\t"
      "jl .LFUN_0004bc70_8\n\t"
      ".LFUN_0004bc70_9:\n\t"
      "movl 0x5ac9b4, %%eax\n\t"
      "flds 0x5ac990\n\t"
      "movl 0x5ac9b0, %%edx\n\t"
      "movl 0x5ac9b8, %%ecx\n\t"
      "movl %%eax, 0x5ac9a4\n\t"
      "movl 0x31fc44, %%eax\n\t"
      "movl %%edx, 0x5ac9a0\n\t"
      "movl 0x2ee6e8, %%edx\n\t"
      "movl %%ecx, 0x5ac9a8\n\t"
      "fmuls (%%eax)\n\t"
      "pushl %%edx\n\t"
      "pushl $0x5ab100\n\t"
      "fadds 0x5ac9b0\n\t"
      "pushl $0x5ac9a0\n\t"
      "pushl $1\n\t"
      "fstps 0x5ac9b0\n\t"
      "flds 0x5ac990\n\t"
      "fmuls 0x4(%%eax)\n\t"
      "fadds 0x5ac9a4\n\t"
      "fstps 0x5ac9b4\n\t"
      "flds 0x5ac990\n\t"
      "fmuls 0x8(%%eax)\n\t"
      "fadds 0x5ac9a8\n\t"
      "fstps 0x5ac9b8\n\t"
      "call *%[c189cb0]\n\t"
      "addl $0x10, %%esp\n\t"
      ".LFUN_0004bc70_10:\n\t"
      "movl 0x632574, %%edi\n\t"
      "incl %%esi\n\t"
      "cmpw 0x3b6(%%edi), %%si\n\t"
      "jl .LFUN_0004bc70_1\n\t"
      "popl %%ebx\n\t"
      ".LFUN_0004bc70_11:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [tryget] "m"(b4bc70_tryget), [c1412f0] "m"(b4bc70_c1412f0), [c4b220] "m"(b4bc70_c4b220), [c8d9d0] "m"(b4bc70_c8d9d0), [c4b2b0] "m"(b4bc70_c4b2b0), [c189cb0] "m"(b4bc70_c189cb0), [c1d90f0] "m"(b4bc70_c1d90f0), [c8dc30] "m"(b4bc70_c8dc30), [c18e380] "m"(b4bc70_c18e380), [c54220] "m"(b4bc70_c54220)
      : "memory");
}
#else
#error "FUN_0004bc70: clang naked draft required"
#endif


/* FUN_0004c2a0 (0x4c2a0) — XBE naked draft (batch 110). */
#if defined(__clang__)
static short (*const b4c2a0_c5e7e0)(char *param_1, unsigned int param_2) = path_node_from_hash_table;
static char * (*const b4c2a0_c5e760)(char *param_1, short param_2) = path_get_node;
static void (*const b4c2a0_c4b320)(void) = FUN_0004b320;
static void *(*const b4c2a0_elem)(void *, int, int) = tag_block_get_element;
static void (*const b4c2a0_c189450)(int flag, float *point_a, float *point_b, void *color, float scale) = FUN_00189450;

__attribute__((naked, noinline))
void FUN_0004c2a0(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x38, %%esp\n\t"
      "negb %%cl\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x2ee6f4, %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x2ee6c4, %%edi\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "andl %%esi, %%ecx\n\t"
      "movl %%ecx, -0x1c(%%ebp)\n\t"
      "movl 0x2ee6e0, %%esi\n\t"
      "movb %%al, %%cl\n\t"
      "negb %%cl\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "andl %%edi, %%ecx\n\t"
      "movl %%ecx, -0x18(%%ebp)\n\t"
      "movb %%al, %%cl\n\t"
      "negb %%cl\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "andl %%esi, %%ecx\n\t"
      "negb %%al\n\t"
      "movl %%ecx, -0x14(%%ebp)\n\t"
      "movl 0x2ee6d0, %%ecx\n\t"
      "sbbl %%eax, %%eax\n\t"
      "andl %%ecx, %%eax\n\t"
      "negb %%dl\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "sbbl %%edx, %%edx\n\t"
      "andl %%esi, %%edx\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "movb 0x4c(%%esi), %%al\n\t"
      "incw 0x331f60\n\t"
      "testb %%al, %%al\n\t"
      "movl %%edx, -0xc(%%ebp)\n\t"
      "je .LFUN_0004c2a0_3\n\t"
      "movl 0x5c(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%esi\n\t"
      "xorl %%edi, %%edi\n\t"
      "call *%[c5e7e0]\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .LFUN_0004c2a0_3\n\t"
      ".LFUN_0004c2a0_1:\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[c5e760]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%edi, %%edi\n\t"
      "movl %%eax, %%ebx\n\t"
      "leal 0x50(%%esi), %%eax\n\t"
      "je .LFUN_0004c2a0_2\n\t"
      "leal 0xc(%%edi), %%eax\n\t"
      ".LFUN_0004c2a0_2:\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "movl -0x10(%%ebp), %%edx\n\t"
      "pushl %%ecx\n\t"
      "movl -0x14(%%ebp), %%ecx\n\t"
      "pushl %%edx\n\t"
      "movl -0x18(%%ebp), %%edx\n\t"
      "pushl %%ecx\n\t"
      "movl -0x1c(%%ebp), %%ecx\n\t"
      "pushl %%edx\n\t"
      "movl 0x2ee6d0, %%edx\n\t"
      "pushl %%ecx\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "pushl %%edx\n\t"
      "movl 0x64(%%esi), %%edx\n\t"
      "pushl %%edi\n\t"
      "pushl %%esi\n\t"
      "pushl %%ecx\n\t"
      "movl %%eax, %%edi\n\t"
      "pushl %%edx\n\t"
      "movl %%ebx, %%eax\n\t"
      "call *%[c4b320]\n\t"
      "movw 0x331f60, %%ax\n\t"
      "movw %%ax, 0x32(%%ebx)\n\t"
      "movw 0x2(%%ebx), %%ax\n\t"
      "addl $0x28, %%esp\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "movl %%ebx, %%edi\n\t"
      "jne .LFUN_0004c2a0_1\n\t"
      ".LFUN_0004c2a0_3:\n\t"
      "movb 0x10(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0004c2a0_14\n\t"
      "movl 0x64(%%esi), %%ecx\n\t"
      "pushl $0x60\n\t"
      "addl $0xb0, %%ecx\n\t"
      "pushl $0\n\t"
      "pushl %%ecx\n\t"
      "call *%[elem]\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "movw 0x80(%%esi), %%bx\n\t"
      "addl $0xc, %%esp\n\t"
      "decw %%bx\n\t"
      "testw %%bx, %%bx\n\t"
      "movl %%eax, -0x20(%%ebp)\n\t"
      "movl %%ebx, 0x10(%%ebp)\n\t"
      "jl .LFUN_0004c2a0_14\n\t"
      ".LFUN_0004c2a0_4:\n\t"
      "xorl %%edi, %%edi\n\t"
      "cmpw $-1, %%bx\n\t"
      "movl %%edi, -0x8(%%ebp)\n\t"
      "je .LFUN_0004c2a0_13\n\t"
      "jmp .LFUN_0004c2a0_6\n\t"
      ".LFUN_0004c2a0_5:\n\t"
      "movl -0x8(%%ebp), %%edi\n\t"
      ".LFUN_0004c2a0_6:\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "call *%[c5e760]\n\t"
      "movl %%eax, %%ebx\n\t"
      "movw 0x32(%%ebx), %%dx\n\t"
      "addl $8, %%esp\n\t"
      "cmpw 0x331f60, %%dx\n\t"
      "je .LFUN_0004c2a0_11\n\t"
      "testl %%edi, %%edi\n\t"
      "movl 0x31fc1c, %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "movl %%ecx, -0x38(%%ebp)\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl %%edx, -0x34(%%ebp)\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl %%eax, -0x30(%%ebp)\n\t"
      "jne .LFUN_0004c2a0_9\n\t"
      "movb 0xc(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0004c2a0_8\n\t"
      "movl 0x8(%%ebx), %%ecx\n\t"
      "movl -0x20(%%ebp), %%esi\n\t"
      "pushl $0xc\n\t"
      "pushl %%ecx\n\t"
      "leal 0x3c(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[elem]\n\t"
      "leal 0x48(%%esi), %%ecx\n\t"
      "addl $0xc, %%esp\n\t"
      "addl $0x54, %%esi\n\t"
      "movl %%eax, -0x2c(%%ebp)\n\t"
      "movl 0x4(%%eax), %%eax\n\t"
      "movl %%edi, -0x4(%%ebp)\n\t"
      "movl %%ecx, -0x24(%%ebp)\n\t"
      "movl %%esi, -0x28(%%ebp)\n\t"
      ".LFUN_0004c2a0_7:\n\t"
      "movl -0x24(%%ebp), %%edx\n\t"
      "pushl $0x18\n\t"
      "pushl %%eax\n\t"
      "pushl %%edx\n\t"
      "call *%[elem]\n\t"
      "movl 0x8(%%ebx), %%ecx\n\t"
      "movl -0x28(%%ebp), %%edx\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x14(%%esi), %%eax\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "sete %%al\n\t"
      "movzbl %%al, %%edi\n\t"
      "movl (%%esi,%%edi,4), %%ecx\n\t"
      "pushl $0x10\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[elem]\n\t"
      "movl -0x2c(%%ebp), %%ecx\n\t"
      "flds -0x38(%%ebp)\n\t"
      "addl $0x18, %%esp\n\t"
      "fadds (%%eax)\n\t"
      "fstps -0x38(%%ebp)\n\t"
      "flds -0x34(%%ebp)\n\t"
      "fadds 0x4(%%eax)\n\t"
      "fstps -0x34(%%ebp)\n\t"
      "flds -0x30(%%ebp)\n\t"
      "fadds 0x8(%%eax)\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "incl %%eax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "fstps -0x30(%%ebp)\n\t"
      "movl 0x8(%%esi,%%edi,4), %%eax\n\t"
      "cmpl 0x4(%%ecx), %%eax\n\t"
      "jne .LFUN_0004c2a0_7\n\t"
      "fildl -0x4(%%ebp)\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "movl -0x8(%%ebp), %%edi\n\t"
      "leal -0x38(%%ebp), %%eax\n\t"
      "fdivrs 0x2533c8\n\t"
      "flds -0x38(%%ebp)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fstps -0x38(%%ebp)\n\t"
      "flds -0x34(%%ebp)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fstps -0x34(%%ebp)\n\t"
      "flds -0x30(%%ebp)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fstps -0x30(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "jmp .LFUN_0004c2a0_10\n\t"
      ".LFUN_0004c2a0_8:\n\t"
      "leal 0x38(%%ebx), %%edx\n\t"
      "movl (%%edx), %%eax\n\t"
      "movl 0x4(%%edx), %%ecx\n\t"
      "movl 0x8(%%edx), %%edx\n\t"
      "movl %%eax, -0x38(%%ebp)\n\t"
      "movl %%ecx, -0x34(%%ebp)\n\t"
      "movl %%edx, -0x30(%%ebp)\n\t"
      "leal -0x38(%%ebp), %%eax\n\t"
      "jmp .LFUN_0004c2a0_10\n\t"
      ".LFUN_0004c2a0_9:\n\t"
      "leal 0xc(%%ebx), %%eax\n\t"
      ".LFUN_0004c2a0_10:\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "movl -0x10(%%ebp), %%edx\n\t"
      "pushl %%ecx\n\t"
      "movl -0x14(%%ebp), %%ecx\n\t"
      "pushl %%edx\n\t"
      "movl -0x18(%%ebp), %%edx\n\t"
      "pushl %%ecx\n\t"
      "movl -0x1c(%%ebp), %%ecx\n\t"
      "pushl %%edx\n\t"
      "movl 0x2ee6d8, %%edx\n\t"
      "pushl %%ecx\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "pushl %%edx\n\t"
      "movl 0x64(%%esi), %%edx\n\t"
      "pushl %%edi\n\t"
      "pushl %%esi\n\t"
      "pushl %%ecx\n\t"
      "movl %%eax, %%edi\n\t"
      "pushl %%edx\n\t"
      "movl %%ebx, %%eax\n\t"
      "call *%[c4b320]\n\t"
      "movw 0x331f60, %%ax\n\t"
      "movw %%ax, 0x32(%%ebx)\n\t"
      "movl %%ebx, -0x8(%%ebp)\n\t"
      "movw 0x2(%%ebx), %%bx\n\t"
      "addl $0x28, %%esp\n\t"
      "cmpw $-1, %%bx\n\t"
      "jne .LFUN_0004c2a0_5\n\t"
      "jmp .LFUN_0004c2a0_12\n\t"
      ".LFUN_0004c2a0_11:\n\t"
      "testl %%edi, %%edi\n\t"
      "je .LFUN_0004c2a0_12\n\t"
      "movl 0x2ee6d8, %%ecx\n\t"
      "pushl $0x3dcccccd\n\t"
      "pushl %%ecx\n\t"
      "addl $0xc, %%ebx\n\t"
      "pushl %%ebx\n\t"
      "addl $0xc, %%edi\n\t"
      "pushl %%edi\n\t"
      "pushl $1\n\t"
      "call *%[c189450]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0004c2a0_12:\n\t"
      "movl 0x10(%%ebp), %%ebx\n\t"
      ".LFUN_0004c2a0_13:\n\t"
      "decl %%ebx\n\t"
      "testw %%bx, %%bx\n\t"
      "movl %%ebx, 0x10(%%ebp)\n\t"
      "jge .LFUN_0004c2a0_4\n\t"
      ".LFUN_0004c2a0_14:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c5e7e0] "m"(b4c2a0_c5e7e0), [c5e760] "m"(b4c2a0_c5e760), [c4b320] "m"(b4c2a0_c4b320), [elem] "m"(b4c2a0_elem), [c189450] "m"(b4c2a0_c189450)
      : "memory");
}
#else
#error "FUN_0004c2a0: clang naked draft required"
#endif


/* FUN_0004c560 (0x4c560) — XBE naked draft (batch 111). */
#if defined(__clang__)
static short (*const b4c560_gbspi)(void) = global_structure_bsp_index_get;
static void (*const b4c560_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b4c560_exitfn)(int) = system_exit;
static int (*const b4c560_gtime)(void) = game_time_get;
static char * (*const b4c560_c8d9d0)(char *buffer, const char *format, ...) = csprintf;
static void (*const b4c560_c4b2b0)(void) = FUN_0004b2b0;
static void (*const b4c560_c189cb0)(char flag, void *position, void *string, int color) = FUN_00189cb0;
static void (*const b4c560_c189450)(int flag, float *point_a, float *point_b, void *color, float scale) = FUN_00189450;
static void (*const b4c560_c189150)(char flag, float *position, float scale, void *color) = FUN_00189150;
static void (*const b4c560_c189540)(char flag, void *center, float radius, void *color) = FUN_00189540;
static void (*const b4c560_c49300)(void) = FUN_00049300;
static void (*const b4c560_c49280)(void) = FUN_00049280;
static void (*const b4c560_c62960)(void *obstacles, float radius) = path_obstacles_debug_render;
static void (*const b4c560_c609e0)(void *path) = FUN_000609e0;
static void (*const b4c560_c4c2a0)(void) = FUN_0004c2a0;

__attribute__((naked, noinline))
void FUN_0004c560(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x34, %%esp\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_0004c560_16\n\t"
      "movb 0xc(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0004c560_16\n\t"
      "movl 0x8(%%esi), %%eax\n\t"
      "cmpl 0x5acab4, %%eax\n\t"
      "je .LFUN_0004c560_16\n\t"
      "movl $0x254384, %%edx\n\t"
      "movl $0x25b244, %%ecx\n\t"
      "movl $0x254818, %%eax\n\t"
      "pushl %%ebx\n\t"
      "movl %%edx, -0x34(%%ebp)\n\t"
      "movl $0x25b234, -0x30(%%ebp)\n\t"
      "movl %%ecx, -0x2c(%%ebp)\n\t"
      "movl $0x25b220, -0x28(%%ebp)\n\t"
      "movl $0x25b20c, -0x24(%%ebp)\n\t"
      "movl %%eax, -0x20(%%ebp)\n\t"
      "movl %%edx, -0x1c(%%ebp)\n\t"
      "movl $0x25b1fc, -0x18(%%ebp)\n\t"
      "movl $0x25b1e8, -0x14(%%ebp)\n\t"
      "movl %%ecx, -0x10(%%ebp)\n\t"
      "movl $0x25b1d4, -0xc(%%ebp)\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "call *%[gbspi]\n\t"
      "cmpw %%ax, 0xe(%%esi)\n\t"
      "movw 0x10(%%esi), %%ax\n\t"
      "sete %%bl\n\t"
      "testw %%ax, %%ax\n\t"
      "movb %%bl, -0x4(%%ebp)\n\t"
      "jl .LFUN_0004c560_1\n\t"
      "cmpw $6, %%ax\n\t"
      "jl .LFUN_0004c560_2\n\t"
      ".LFUN_0004c560_1:\n\t"
      "pushl $1\n\t"
      "pushl $0xf68\n\t"
      "pushl $0x25ab74\n\t"
      "pushl $0x25b170\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0004c560_2:\n\t"
      "movw 0x12(%%esi), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "jl .LFUN_0004c560_3\n\t"
      "cmpw $6, %%ax\n\t"
      "jl .LFUN_0004c560_4\n\t"
      ".LFUN_0004c560_3:\n\t"
      "pushl $1\n\t"
      "pushl $0xf69\n\t"
      "pushl $0x25ab74\n\t"
      "pushl $0x25b110\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0004c560_4:\n\t"
      "movl $5, %%eax\n\t"
      "cmpw %%ax, 0x10(%%esi)\n\t"
      "jne .LFUN_0004c560_5\n\t"
      "cmpw %%ax, 0x12(%%esi)\n\t"
      "movl 0x2ee6d4, %%eax\n\t"
      "je .LFUN_0004c560_6\n\t"
      ".LFUN_0004c560_5:\n\t"
      "movl 0x2ee6d0, %%eax\n\t"
      ".LFUN_0004c560_6:\n\t"
      "pushl %%eax\n\t"
      "call *%[gtime]\n\t"
      "movl 0x4(%%esi), %%edx\n\t"
      "movswl 0x12(%%esi), %%ecx\n\t"
      "subl %%edx, %%eax\n\t"
      "movl -0x1c(%%ebp,%%ecx,4), %%edx\n\t"
      "pushl %%eax\n\t"
      "movswl 0x10(%%esi), %%eax\n\t"
      "movl -0x34(%%ebp,%%eax,4), %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x25b100\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x14, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[c4b2b0]\n\t"
      "pushl %%eax\n\t"
      "pushl $1\n\t"
      "call *%[c189cb0]\n\t"
      "movb 0x5acaa4, %%al\n\t"
      "addl $0x10, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0004c560_9\n\t"
      "movb 0x60(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0004c560_8\n\t"
      "movl 0x2ee6e8, %%edx\n\t"
      "pushl %%edi\n\t"
      "pushl $0x3dcccccd\n\t"
      "pushl %%edx\n\t"
      "leal 0x64(%%esi), %%edi\n\t"
      "pushl %%edi\n\t"
      "leal 0x28(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $1\n\t"
      "call *%[c189450]\n\t"
      "movl 0x2ee6d4, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x3e99999a\n\t"
      "pushl %%edi\n\t"
      "pushl $1\n\t"
      "call *%[c189150]\n\t"
      "flds 0x74(%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "addl $0x24, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_0004c560_7\n\t"
      "movl 0x2ee6d4, %%edx\n\t"
      "movl 0x74(%%esi), %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl $1\n\t"
      "call *%[c189540]\n\t"
      "addl $0x10, %%esp\n\t"
      ".LFUN_0004c560_7:\n\t"
      "movl 0x70(%%esi), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "popl %%edi\n\t"
      "je .LFUN_0004c560_9\n\t"
      "testb %%bl, %%bl\n\t"
      "je .LFUN_0004c560_9\n\t"
      "movl 0x2ee6d4, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x3d4ccccd\n\t"
      "pushl %%eax\n\t"
      "movl 0x78(%%esi), %%eax\n\t"
      "call *%[c49300]\n\t"
      "addl $0xc, %%esp\n\t"
      "jmp .LFUN_0004c560_9\n\t"
      ".LFUN_0004c560_8:\n\t"
      "movl 0x2ee6d4, %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x25b0f4\n\t"
      "call *%[c4b2b0]\n\t"
      "pushl %%eax\n\t"
      "pushl $1\n\t"
      "call *%[c189cb0]\n\t"
      "addl $0x10, %%esp\n\t"
      ".LFUN_0004c560_9:\n\t"
      "movb 0x5aca9d, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0004c560_10\n\t"
      "movl 0x2ee6d0, %%ebx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x140fc(%%esi), %%cx\n\t"
      "leal 0x14100(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "leal 0x28(%%esi), %%ecx\n\t"
      "call *%[c49280]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_0004c560_10:\n\t"
      "movb 0x5aca9e, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0004c560_11\n\t"
      "movl 0x2ee6d4, %%ebx\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x14500(%%esi), %%ax\n\t"
      "leal 0x14504(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal 0x28(%%esi), %%ecx\n\t"
      "pushl %%eax\n\t"
      "call *%[c49280]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_0004c560_11:\n\t"
      "movb 0x5aca9f, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0004c560_12\n\t"
      "movl 0x2ee6d8, %%ebx\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x14544(%%esi), %%dx\n\t"
      "leal 0x14548(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal 0x28(%%esi), %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c49280]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_0004c560_12:\n\t"
      "movw 0x5acaa0, %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "popl %%ebx\n\t"
      "jl .LFUN_0004c560_14\n\t"
      "cmpw 0x1458a(%%esi), %%ax\n\t"
      "jge .LFUN_0004c560_14\n\t"
      "movb 0x5acaa2, %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "je .LFUN_0004c560_13\n\t"
      "movswl %%ax, %%eax\n\t"
      "movl %%eax, %%ecx\n\t"
      "imull $0xc08, %%eax, %%eax\n\t"
      "imull $0x1534, %%ecx, %%ecx\n\t"
      "movl 0x175ac(%%ecx,%%esi,1), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal 0x1458c(%%eax,%%esi,1), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c62960]\n\t"
      "movw 0x5acaa0, %%ax\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_0004c560_13:\n\t"
      "movb 0x5acaa3, %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "je .LFUN_0004c560_14\n\t"
      "movb -0x4(%%ebp), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "je .LFUN_0004c560_14\n\t"
      "movswl %%ax, %%ecx\n\t"
      "imull $0x1534, %%ecx, %%ecx\n\t"
      "leal 0x175ac(%%ecx,%%esi,1), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c609e0]\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_0004c560_14:\n\t"
      "movb 0x5acaa5, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0004c560_15\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "xorl %%eax, %%eax\n\t"
      "movb 0x5acaa6, %%al\n\t"
      "leal 0x14(%%esi), %%edx\n\t"
      "pushl %%eax\n\t"
      "movb 0x5acaa8, %%al\n\t"
      "pushl %%ecx\n\t"
      "movb 0x5acaa7, %%cl\n\t"
      "pushl %%edx\n\t"
      "movb 0x5acaa9, %%dl\n\t"
      "call *%[c4c2a0]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_0004c560_15:\n\t"
      "movl 0x5acab4, %%eax\n\t"
      "movl %%eax, 0x8(%%esi)\n\t"
      ".LFUN_0004c560_16:\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [gbspi] "m"(b4c560_gbspi), [assert] "m"(b4c560_assert), [exitfn] "m"(b4c560_exitfn), [gtime] "m"(b4c560_gtime), [c8d9d0] "m"(b4c560_c8d9d0), [c4b2b0] "m"(b4c560_c4b2b0), [c189cb0] "m"(b4c560_c189cb0), [c189450] "m"(b4c560_c189450), [c189150] "m"(b4c560_c189150), [c189540] "m"(b4c560_c189540), [c49300] "m"(b4c560_c49300), [c49280] "m"(b4c560_c49280), [c62960] "m"(b4c560_c62960), [c609e0] "m"(b4c560_c609e0), [c4c2a0] "m"(b4c560_c4c2a0)
      : "memory");
}
#else
#error "FUN_0004c560: clang naked draft required"
#endif


/* FUN_0004c890 (0x4c890) — XBE naked draft (batch 153). */
#if defined(__clang__)
static void (*const b4c890_c189270)(char flag, float *point_a, float *point_b, void *color) = FUN_00189270;
static void (*const b4c890_c4b220)(void) = FUN_0004b220;
static void (*const b4c890_c4c560)(void) = FUN_0004c560;

__attribute__((naked, noinline))
void FUN_0004c890(void)
{
  __asm__ volatile(
      "movb 0x5f91a8, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0004c890_4\n\t"
      "movb 0x5f91c0, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0004c890_4\n\t"
      "movb 0x60d268, %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_0004c890_4\n\t"
      "movb 0x5ac9ff, %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_0004c890_1\n\t"
      "movb 0x5f9228, %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_0004c890_1\n\t"
      "movl 0x2ee6d8, %%eax\n\t"
      "jmp .LFUN_0004c890_3\n\t"
      ".LFUN_0004c890_1:\n\t"
      "movw 0x5f925c, %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "jne .LFUN_0004c890_2\n\t"
      "movl 0x2ee6d4, %%eax\n\t"
      "jmp .LFUN_0004c890_3\n\t"
      ".LFUN_0004c890_2:\n\t"
      "cmpw $0x400, %%ax\n\t"
      "movl 0x2ee6e0, %%eax\n\t"
      "jge .LFUN_0004c890_3\n\t"
      "movl 0x2ee6e8, %%eax\n\t"
      ".LFUN_0004c890_3:\n\t"
      "pushl %%eax\n\t"
      "pushl $0x5f91c4\n\t"
      "pushl $0x5f91ac\n\t"
      "pushl $1\n\t"
      "call *%[c189270]\n\t"
      "addl $0x10, %%esp\n\t"
      ".LFUN_0004c890_4:\n\t"
      "movb 0x60d2d0, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0004c890_5\n\t"
      "pushl %%esi\n\t"
      "movl $0x60d2ec, %%eax\n\t"
      "call *%[c4b220]\n\t"
      "movl $0x60d2c4, %%esi\n\t"
      "call *%[c4c560]\n\t"
      "popl %%esi\n\t"
      ".LFUN_0004c890_5:\n\t"
      "ret\n\t"
      :
      : [c189270] "m"(b4c890_c189270), [c4b220] "m"(b4c890_c4b220), [c4c560] "m"(b4c890_c4c560)
      : "memory");
}
#else
#error "FUN_0004c890: clang naked draft required"
#endif


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

/* FUN_00052ab0 (0x52ab0) — XBE naked draft (batch 145). */
#if defined(__clang__)
static void (*const b52ab0_c4b220)(void) = FUN_0004b220;
static char * (*const b52ab0_c49ac0)(int actor_handle, int object_handle, char with_actor, char *buf, int buf_size) = ai_debug_describe_actor;
static void (*const b52ab0_c4b2b0)(void) = FUN_0004b2b0;
static void (*const b52ab0_c189cb0)(char flag, void *position, void *string, int color) = FUN_00189cb0;
static void (*const b52ab0_c4c560)(void) = FUN_0004c560;

__attribute__((naked, noinline))
void FUN_00052ab0(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x10c, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "xorl %%edi, %%edi\n\t"
      "movl $0x20, %%ebx\n\t"
      ".LFUN_00052ab0_1:\n\t"
      "movl 0x331f5c, %%eax\n\t"
      "leal (%%edi,%%eax,1), %%esi\n\t"
      "movb 0xc(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00052ab0_2\n\t"
      "movb 0xd(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00052ab0_2\n\t"
      "movl 0x31fc44, %%eax\n\t"
      "flds (%%eax)\n\t"
      "fadds 0x28(%%esi)\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "flds 0x4(%%eax)\n\t"
      "fadds 0x2c(%%esi)\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "flds 0x8(%%eax)\n\t"
      "leal -0xc(%%ebp), %%eax\n\t"
      "fadds 0x30(%%esi)\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "call *%[c4b220]\n\t"
      "movl (%%esi), %%edx\n\t"
      "pushl $0x100\n\t"
      "leal -0x10c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $1\n\t"
      "pushl $-1\n\t"
      "pushl %%edx\n\t"
      "call *%[c49ac0]\n\t"
      "movl 0x2ee6d0, %%eax\n\t"
      "addl $0x14, %%esp\n\t"
      "pushl %%eax\n\t"
      "leal -0x10c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c4b2b0]\n\t"
      "pushl %%eax\n\t"
      "pushl $1\n\t"
      "call *%[c189cb0]\n\t"
      "addl $0x10, %%esp\n\t"
      "call *%[c4c560]\n\t"
      ".LFUN_00052ab0_2:\n\t"
      "addl $0x1ca7c, %%edi\n\t"
      "decl %%ebx\n\t"
      "jne .LFUN_00052ab0_1\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c4b220] "m"(b52ab0_c4b220), [c49ac0] "m"(b52ab0_c49ac0), [c4b2b0] "m"(b52ab0_c4b2b0), [c189cb0] "m"(b52ab0_c189cb0), [c4c560] "m"(b52ab0_c4c560)
      : "memory");
}
#else
#error "FUN_00052ab0: clang naked draft required"
#endif


/* FUN_00052b60 (0x52b60) — XBE naked draft (batch 161). */
#if defined(__clang__)
static void (*const b52b60_c59b10)(void *iter, char flag) = encounter_iterator_next;
static int (*const b52b60_c59b50)(void *iter) = FUN_00059b50;
static void (*const b52b60_c4c920)(int actor_handle, char debug_selected, void *debug_context) = FUN_0004c920;

__attribute__((naked, noinline))
void FUN_00052b60(char reverse_iteration __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x1c, %%esp\n\t"
      "testb %%dl, %%dl\n\t"
      "sete %%al\n\t"
      "leal -0x1c(%%ebp), %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c59b10]\n\t"
      "leal -0x1c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c59b50]\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_00052b60_2\n\t"
      ".LFUN_00052b60_1:\n\t"
      "movl 0x5ac9f8, %%ecx\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "sete %%cl\n\t"
      "pushl $0\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "call *%[c4c920]\n\t"
      "leal -0x1c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c59b50]\n\t"
      "addl $0x10, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_00052b60_1\n\t"
      ".LFUN_00052b60_2:\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c59b10] "m"(b52b60_c59b10), [c59b50] "m"(b52b60_c59b50), [c4c920] "m"(b52b60_c4c920)
      : "memory");
}
#else
#error "FUN_00052b60: clang naked draft required"
#endif


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


/* FUN_000534d0 (0x534d0) — XBE naked draft (batch 128). */
#if defined(__clang__)
static void *(*const b534d0_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void (*const b534d0_c4b7a0)(void) = FUN_0004b7a0;
static void (*const b534d0_c494e0)(void) = FUN_000494e0;
static void (*const b534d0_c49990)(void) = FUN_00049990;
static void (*const b534d0_c495b0)(void) = FUN_000495b0;
static void (*const b534d0_c52bb0)(int clump_handle) = FUN_00052bb0;
static void (*const b534d0_c4c920)(int actor_handle, char debug_selected, void *debug_context) = FUN_0004c920;
static void (*const b534d0_c4c890)(void) = FUN_0004c890;
static void (*const b534d0_c52ab0)(void) = FUN_00052ab0;
static void (*const b534d0_c49d60)(void) = FUN_00049d60;
static void (*const b534d0_c52b60)(char reverse_iteration) = FUN_00052b60;
static void (*const b534d0_c4b810)(void) = FUN_0004b810;
static void (*const b534d0_c4a770)(void) = FUN_0004a770;
static void (*const b534d0_c4a8c0)(void) = FUN_0004a8c0;
static void (*const b534d0_c4bc70)(void) = FUN_0004bc70;

__attribute__((naked, noinline))
void FUN_000534d0(void)
{
  __asm__ volatile(
      "movl 0x632574, %%eax\n\t"
      "movb 0x1(%%eax), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "je .LFUN_000534d0_16\n\t"
      "movl 0x325660, %%ecx\n\t"
      "movl 0x5acab4, %%eax\n\t"
      "addl $-0x14, %%ecx\n\t"
      "incl %%eax\n\t"
      "cdq\n\t"
      "movw %%cx, 0x5ac98c\n\t"
      "movl $0x3e8, %%ecx\n\t"
      "idivl %%ecx\n\t"
      "movl 0x5ac9f8, %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "movl %%edx, 0x5acab4\n\t"
      "je .LFUN_000534d0_1\n\t"
      "movl 0x6325a4, %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%edx\n\t"
      "call *%[dget]\n\t"
      "movl 0x34(%%eax), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "movl %%eax, 0x5ac9f4\n\t"
      ".LFUN_000534d0_1:\n\t"
      "movb 0x5ac9c1, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000534d0_2\n\t"
      "call *%[c4b7a0]\n\t"
      ".LFUN_000534d0_2:\n\t"
      "movb 0x5aca65, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000534d0_16\n\t"
      "movb 0x5aca69, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000534d0_3\n\t"
      "call *%[c494e0]\n\t"
      ".LFUN_000534d0_3:\n\t"
      "movb 0x5aca6a, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000534d0_4\n\t"
      "call *%[c49990]\n\t"
      ".LFUN_000534d0_4:\n\t"
      "movb 0x5aca6b, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000534d0_5\n\t"
      "call *%[c495b0]\n\t"
      ".LFUN_000534d0_5:\n\t"
      "movl 0x5ac9f4, %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_000534d0_6\n\t"
      "pushl %%eax\n\t"
      "call *%[c52bb0]\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_000534d0_6:\n\t"
      "movl 0x5ac9f8, %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_000534d0_7\n\t"
      "pushl $0\n\t"
      "pushl $1\n\t"
      "pushl %%eax\n\t"
      "call *%[c4c920]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_000534d0_7:\n\t"
      "movb 0x5ac9fc, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000534d0_8\n\t"
      "call *%[c4c890]\n\t"
      ".LFUN_000534d0_8:\n\t"
      "movb 0x5aca9b, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000534d0_9\n\t"
      "call *%[c52ab0]\n\t"
      ".LFUN_000534d0_9:\n\t"
      "movb 0x5aca88, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000534d0_10\n\t"
      "call *%[c49d60]\n\t"
      ".LFUN_000534d0_10:\n\t"
      "movb 0x5aca66, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000534d0_11\n\t"
      "movb 0x5aca67, %%dl\n\t"
      "call *%[c52b60]\n\t"
      ".LFUN_000534d0_11:\n\t"
      "movb 0x5aca89, %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_000534d0_12\n\t"
      "movb 0x5aca53, %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_000534d0_12\n\t"
      "movb 0x5aca93, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000534d0_13\n\t"
      ".LFUN_000534d0_12:\n\t"
      "call *%[c4b810]\n\t"
      ".LFUN_000534d0_13:\n\t"
      "movb 0x5aca76, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000534d0_14\n\t"
      "call *%[c4a770]\n\t"
      ".LFUN_000534d0_14:\n\t"
      "movb 0x5aca8c, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000534d0_15\n\t"
      "call *%[c4a8c0]\n\t"
      ".LFUN_000534d0_15:\n\t"
      "movb 0x5aca91, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000534d0_16\n\t"
      "jmp .LFUN_000534d0_10000\n\t"
      ".LFUN_000534d0_16:\n\t"
      "ret\n\t"
      ".LFUN_000534d0_10000:\n\t"
      "jmp *%[c4bc70]\n\t"
      :
      : [dget] "m"(b534d0_dget), [c4b7a0] "m"(b534d0_c4b7a0), [c494e0] "m"(b534d0_c494e0), [c49990] "m"(b534d0_c49990), [c495b0] "m"(b534d0_c495b0), [c52bb0] "m"(b534d0_c52bb0), [c4c920] "m"(b534d0_c4c920), [c4c890] "m"(b534d0_c4c890), [c52ab0] "m"(b534d0_c52ab0), [c49d60] "m"(b534d0_c49d60), [c52b60] "m"(b534d0_c52b60), [c4b810] "m"(b534d0_c4b810), [c4a770] "m"(b534d0_c4a770), [c4a8c0] "m"(b534d0_c4a8c0), [c4bc70] "m"(b534d0_c4bc70)
      : "memory");
}
#else
#error "FUN_000534d0: clang naked draft required"
#endif


/* 0x53650 */
void FUN_00053650(void)
{
  csmemset((void *)0x005abaac, 0, 3808);
}

/* FUN_00053680 (0x53680) — XBE naked draft (batch 133). */
#if defined(__clang__)
static void (*const b53680_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b53680_exitfn)(int) = system_exit;

__attribute__((naked, noinline))
void FUN_00053680(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $8, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl $0x2c8e9c, %%ebx\n\t"
      "pushl %%edi\n\t"
      "xorl %%edi, %%edi\n\t"
      "movl $0x5abab8, %%esi\n\t"
      "movl %%ebx, -0x4(%%ebp)\n\t"
      ".LFUN_00053680_1:\n\t"
      "cmpw %%di, -0x4(%%ebx)\n\t"
      "je .LFUN_00053680_2\n\t"
      "pushl $1\n\t"
      "pushl $0x8c\n\t"
      "pushl $0x25c0ac\n\t"
      "pushl $0x25c08c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00053680_2:\n\t"
      "movl (%%ebx), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_00053680_3\n\t"
      "call *%%eax\n\t"
      "movw %%ax, -0xc(%%esi)\n\t"
      ".LFUN_00053680_3:\n\t"
      "movw -0xc(%%esi), %%ax\n\t"
      "movw %%ax, -0xa(%%esi)\n\t"
      "movw (%%esi), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "movw $0, -0xc(%%esi)\n\t"
      "jl .LFUN_00053680_4\n\t"
      "cmpw $0x3c, %%ax\n\t"
      "jl .LFUN_00053680_5\n\t"
      ".LFUN_00053680_4:\n\t"
      "pushl $1\n\t"
      "pushl $0x97\n\t"
      "pushl $0x25c0ac\n\t"
      "pushl $0x25c030\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00053680_5:\n\t"
      "movw (%%esi), %%ax\n\t"
      "cmpw 0x2(%%esi), %%ax\n\t"
      "jge .LFUN_00053680_6\n\t"
      "movswl %%ax, %%ecx\n\t"
      "movswl 0x4(%%esi,%%ecx,2), %%edx\n\t"
      "subl %%edx, -0x4(%%esi)\n\t"
      ".LFUN_00053680_6:\n\t"
      "movw -0xa(%%esi), %%cx\n\t"
      "movswl %%ax, %%eax\n\t"
      "movw %%cx, 0x4(%%esi,%%eax,2)\n\t"
      "movw (%%esi), %%ax\n\t"
      "movw 0x2(%%esi), %%cx\n\t"
      "incw %%ax\n\t"
      "cmpw %%ax, %%cx\n\t"
      "movw %%ax, (%%esi)\n\t"
      "movswl %%cx, %%ecx\n\t"
      "jg .LFUN_00053680_7\n\t"
      "movswl %%ax, %%ecx\n\t"
      ".LFUN_00053680_7:\n\t"
      "movswl %%ax, %%eax\n\t"
      "fildl -0x4(%%esi)\n\t"
      "cdq\n\t"
      "movl $0x3c, %%ebx\n\t"
      "idivl %%ebx\n\t"
      "movl -0x4(%%ebp), %%ebx\n\t"
      "movw %%cx, 0x2(%%esi)\n\t"
      "incl %%edi\n\t"
      "addl $8, %%ebx\n\t"
      "addl $0x88, %%esi\n\t"
      "cmpw $0x1c, %%di\n\t"
      "movl %%ebx, -0x4(%%ebp)\n\t"
      "movw %%dx, -0x88(%%esi)\n\t"
      "movswl %%cx, %%edx\n\t"
      "movl %%edx, -0x8(%%ebp)\n\t"
      "fidivl -0x8(%%ebp)\n\t"
      "fstps -0x90(%%esi)\n\t"
      "jl .LFUN_00053680_1\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b53680_assert), [exitfn] "m"(b53680_exitfn)
      : "memory");
}
#else
#error "FUN_00053680: clang naked draft required"
#endif


/* FUN_00053790 (0x53790) — XBE naked draft (batch 159). */
#if defined(__clang__)
static int (*const b53790_c8df60)(const char *s1) = csstrlen;
static int (*const b53790_c1d90f0)(char *buffer, const char *format, ...) = crt_sprintf;

__attribute__((naked, noinline))
void FUN_00053790(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movswl 0x5abeee, %%eax\n\t"
      "movswl 0x5abd56, %%ecx\n\t"
      "movswl 0x5abdde, %%edx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "pushl $0x300\n\t"
      "pushl %%eax\n\t"
      "movswl 0x5abe66, %%eax\n\t"
      "pushl %%ecx\n\t"
      "movswl 0x5abbbe, %%ecx\n\t"
      "pushl %%edx\n\t"
      "movswl 0x5abc46, %%edx\n\t"
      "pushl %%eax\n\t"
      "movswl 0x5abcce, %%eax\n\t"
      "pushl %%ecx\n\t"
      "movswl 0x5abaae, %%ecx\n\t"
      "pushl %%edx\n\t"
      "movswl 0x5abb36, %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x25c0d0\n\t"
      "pushl %%esi\n\t"
      "call *%[c8df60]\n\t"
      "addl %%esi, %%eax\n\t"
      "addl $4, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d90f0]\n\t"
      "addl $0x30, %%esp\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c8df60] "m"(b53790_c8df60), [c1d90f0] "m"(b53790_c1d90f0)
      : "memory");
}
#else
#error "FUN_00053790: clang naked draft required"
#endif


/* FUN_00053800 (0x53800) — XBE naked draft (batch 149). */
#if defined(__clang__)
static void (*const b53800_cdeda0)(int font_index, int style, int justify, int flags, int color_tag_index, short color_index) = interface_draw_text;
static void (*const b53800_c19b640)(const void *color) = draw_string_set_color;
static void (*const b53800_c19b560)(void *stops, short count) = draw_string_set_tab_stops;
static void (*const b53800_c183e60)(void *screen_pos, short *bounds, const void *color, int flags, const char *text) = rasterizer_text_draw;

__attribute__((naked, noinline))
void FUN_00053800(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x10, %%esp\n\t"
      "pushl %%esi\n\t"
      "movl %%eax, %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "movw 0x5aba80, %%ax\n\t"
      "movw %%ax, -0x10(%%ebp)\n\t"
      "movl $0x7fff, %%eax\n\t"
      "movw $0, -0xe(%%ebp)\n\t"
      "movw %%ax, -0xa(%%ebp)\n\t"
      "movw %%ax, -0xc(%%ebp)\n\t"
      "jne .LFUN_00053800_1\n\t"
      "movl 0x2ee6c4, %%esi\n\t"
      ".LFUN_00053800_1:\n\t"
      "pushl $0\n\t"
      "pushl $5\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl $-1\n\t"
      "pushl $1\n\t"
      "call *%[cdeda0]\n\t"
      "pushl %%esi\n\t"
      "call *%[c19b640]\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c19b560]\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0\n\t"
      "leal -0x8(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x10(%%ebp), %%edx\n\t"
      "pushl $0\n\t"
      "pushl %%edx\n\t"
      "call *%[c183e60]\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "call *%[c19b560]\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "movl -0x6(%%ebp), %%edx\n\t"
      "addl $0x40, %%esp\n\t"
      "subl %%edx, %%eax\n\t"
      "addw %%ax, 0x5aba80\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [cdeda0] "m"(b53800_cdeda0), [c19b640] "m"(b53800_c19b640), [c19b560] "m"(b53800_c19b560), [c183e60] "m"(b53800_c183e60)
      : "memory");
}
#else
#error "FUN_00053800: clang naked draft required"
#endif


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

/* FUN_000538f0 (0x538f0) — XBE naked draft (batch 150). */
#if defined(__clang__)
static void (*const b538f0_c59b10)(void *iter, char flag) = encounter_iterator_next;
static int (*const b538f0_c59b50)(void *iter) = FUN_00059b50;

__attribute__((naked, noinline))
void FUN_000538f0(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x1c, %%esp\n\t"
      "pushl %%esi\n\t"
      "xorl %%esi, %%esi\n\t"
      "leal -0x1c(%%ebp), %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "call *%[c59b10]\n\t"
      "leal -0x1c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c59b50]\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_000538f0_4\n\t"
      ".LFUN_000538f0_1:\n\t"
      "movb 0x6(%%eax), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "je .LFUN_000538f0_2\n\t"
      "movswl 0x1e(%%eax), %%eax\n\t"
      "jmp .LFUN_000538f0_3\n\t"
      ".LFUN_000538f0_2:\n\t"
      "movl $1, %%eax\n\t"
      ".LFUN_000538f0_3:\n\t"
      "leal -0x1c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "addl %%eax, %%esi\n\t"
      "call *%[c59b50]\n\t"
      "addl $4, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_000538f0_1\n\t"
      ".LFUN_000538f0_4:\n\t"
      "movw %%si, %%ax\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c59b10] "m"(b538f0_c59b10), [c59b50] "m"(b538f0_c59b50)
      : "memory");
}
#else
#error "FUN_000538f0: clang naked draft required"
#endif


/* FUN_00053960 (0x53960) — XBE naked draft (batch 151). */
#if defined(__clang__)
static void (*const b53960_c59b10)(void *iter, char flag) = encounter_iterator_next;
static int (*const b53960_c59b50)(void *iter) = FUN_00059b50;

__attribute__((naked, noinline))
void FUN_00053960(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x1c, %%esp\n\t"
      "pushl %%esi\n\t"
      "xorl %%esi, %%esi\n\t"
      "leal -0x1c(%%ebp), %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "call *%[c59b10]\n\t"
      "leal -0x1c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c59b50]\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_00053960_2\n\t"
      ".LFUN_00053960_1:\n\t"
      "movzbw 0x6(%%eax), %%dx\n\t"
      "leal -0x1c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "addl %%edx, %%esi\n\t"
      "call *%[c59b50]\n\t"
      "addl $4, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_00053960_1\n\t"
      ".LFUN_00053960_2:\n\t"
      "movw %%si, %%ax\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c59b10] "m"(b53960_c59b10), [c59b50] "m"(b53960_c59b50)
      : "memory");
}
#else
#error "FUN_00053960: clang naked draft required"
#endif


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

/* FUN_00053af0 (0x53af0) — XBE naked draft (batch 157). */
#if defined(__clang__)
static int (*const b53af0_c1d90f0)(char *buffer, const char *format, ...) = crt_sprintf;
static void (*const b53af0_c53800)(void) = FUN_00053800;

__attribute__((naked, noinline))
void FUN_00053af0(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $8, %%esp\n\t"
      "movswl 0x5ac086, %%eax\n\t"
      "movswl 0x5abffe, %%ecx\n\t"
      "movswl 0x5abf76, %%edx\n\t"
      "pushl %%eax\n\t"
      "movswl 0x5ac3b6, %%eax\n\t"
      "pushl %%ecx\n\t"
      "movswl 0x5ac32e, %%ecx\n\t"
      "pushl %%edx\n\t"
      "movswl 0x5ac2a6, %%edx\n\t"
      "pushl %%eax\n\t"
      "movswl 0x5ac21e, %%eax\n\t"
      "pushl %%ecx\n\t"
      "movswl 0x5ac196, %%ecx\n\t"
      "pushl %%edx\n\t"
      "movswl 0x5ac10e, %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x25c198\n\t"
      "pushl $0x5ab280\n\t"
      "movw $0x96, -0x8(%%ebp)\n\t"
      "movw $0x12c, -0x6(%%ebp)\n\t"
      "movw $0x1c2, -0x4(%%ebp)\n\t"
      "call *%[c1d90f0]\n\t"
      "leal -0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl 0x2ee6c4, %%eax\n\t"
      "pushl $3\n\t"
      "pushl $0x5ab280\n\t"
      "call *%[c53800]\n\t"
      "addl $0x38, %%esp\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c1d90f0] "m"(b53af0_c1d90f0), [c53800] "m"(b53af0_c53800)
      : "memory");
}
#else
#error "FUN_00053af0: clang naked draft required"
#endif

/* --- ai_debug.obj orphan shells (2026-07-26) --- */

/* FUN_0004a460 (0x4a460) — XBE naked draft (batch 116). */
#if defined(__clang__)
static void (*const b4a460_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b4a460_exitfn)(int) = system_exit;
static void *(*const b4a460_memset)(void *, int, unsigned int) = csmemset;
static int (*const b4a460_c8dcb0)(const char *s1, const char *s2) = csstrcmp;
static void (*const b4a460_c108f00)(int16_t bit_vector_size, int v0, int v1, int result_out) = bit_vector_or;
static void (*const b4a460_cff4d0)(int channel, const char *format, ...) = console_printf;
static void (*const b4a460_c108fa0)(int16_t bit_vector_size, int vector, int result_out) = FUN_00108fa0;
static char (*const b4a460_c108e70)(int16_t bit_vector_size, int v0, int v1, int result_out) = bit_vector_and;

__attribute__((naked, noinline))
void FUN_0004a460(int a0 __attribute__((unused)), int a1 __attribute__((unused)), void *buf __attribute__((unused)), int buf_size __attribute__((unused)), int max_entries __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x108, %%esp\n\t"
      "movl 0x18(%%ebp), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "xorl %%edi, %%edi\n\t"
      "cmpl %%edi, %%eax\n\t"
      "movl %%edi, -0x4(%%ebp)\n\t"
      "movl %%edi, -0x8(%%ebp)\n\t"
      "jne .LFUN_0004a460_1\n\t"
      "pushl $1\n\t"
      "pushl $0x1353\n\t"
      "pushl $0x25ab74\n\t"
      "pushl $0x25aea4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0004a460_1:\n\t"
      "movl 0x14(%%ebp), %%ebx\n\t"
      "cmpl $0x800, %%ebx\n\t"
      "jbe .LFUN_0004a460_2\n\t"
      "pushl $1\n\t"
      "pushl $0x1354\n\t"
      "pushl $0x25ab74\n\t"
      "pushl $0x25ae90\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0004a460_2:\n\t"
      "addl $0x1f, %%ebx\n\t"
      "shrl $5, %%ebx\n\t"
      "shll $2, %%ebx\n\t"
      "pushl %%ebx\n\t"
      "leal -0x108(%%ebp), %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[memset]\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl %%edi, %%eax\n\t"
      "jle .LFUN_0004a460_8\n\t"
      "jmp .LFUN_0004a460_3\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".LFUN_0004a460_3:\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "movl (%%ecx,%%edi,4), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *0x18(%%ebp)\n\t"
      "addl $4, %%esp\n\t"
      "movl %%eax, %%esi\n\t"
      "cmpw $-1, %%si\n\t"
      "je .LFUN_0004a460_6\n\t"
      "testw %%si, %%si\n\t"
      "jl .LFUN_0004a460_4\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      "movswl %%si, %%eax\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jb .LFUN_0004a460_5\n\t"
      ".LFUN_0004a460_4:\n\t"
      "pushl $1\n\t"
      "pushl $0x135d\n\t"
      "pushl $0x25ab74\n\t"
      "pushl $0x25ae60\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0004a460_5:\n\t"
      "movswl %%si, %%ecx\n\t"
      "movl %%ecx, %%edx\n\t"
      "sarl $5, %%edx\n\t"
      "leal -0x108(%%ebp,%%edx,4), %%eax\n\t"
      "andl $0x1f, %%ecx\n\t"
      "movl $1, %%edx\n\t"
      "shll %%cl, %%edx\n\t"
      "orl %%edx, (%%eax)\n\t"
      "jmp .LFUN_0004a460_7\n\t"
      ".LFUN_0004a460_6:\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "movl (%%eax,%%edi,4), %%ecx\n\t"
      "pushl $0x25ae38\n\t"
      "pushl %%ecx\n\t"
      "call *%[c8dcb0]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_0004a460_7\n\t"
      "pushl %%ebx\n\t"
      "leal -0x108(%%ebp), %%edx\n\t"
      "pushl $-1\n\t"
      "pushl %%edx\n\t"
      "call *%[memset]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_0004a460_7:\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "incl %%edi\n\t"
      "cmpl %%eax, %%edi\n\t"
      "jl .LFUN_0004a460_3\n\t"
      ".LFUN_0004a460_8:\n\t"
      "movl 0x14(%%ebp), %%edi\n\t"
      "xorl %%esi, %%esi\n\t"
      "testl %%edi, %%edi\n\t"
      "jbe .LFUN_0004a460_13\n\t"
      ".LFUN_0004a460_9:\n\t"
      "movl %%esi, %%ecx\n\t"
      "andl $0x1f, %%ecx\n\t"
      "movl %%esi, %%eax\n\t"
      "movl $1, %%edx\n\t"
      "sarl $5, %%eax\n\t"
      "shll %%cl, %%edx\n\t"
      "shll $2, %%eax\n\t"
      "testl %%edx, -0x108(%%ebp,%%eax,1)\n\t"
      "je .LFUN_0004a460_11\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "testl %%edx, (%%eax,%%ecx,1)\n\t"
      "je .LFUN_0004a460_10\n\t"
      "incl -0x4(%%ebp)\n\t"
      "jmp .LFUN_0004a460_11\n\t"
      ".LFUN_0004a460_10:\n\t"
      "incl -0x8(%%ebp)\n\t"
      ".LFUN_0004a460_11:\n\t"
      "incl %%esi\n\t"
      "cmpl %%edi, %%esi\n\t"
      "jb .LFUN_0004a460_9\n\t"
      "movl -0x8(%%ebp), %%esi\n\t"
      "testw %%si, %%si\n\t"
      "je .LFUN_0004a460_12\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x108(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "call *%[c108f00]\n\t"
      "movswl %%si, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x25ae50\n\t"
      "pushl $0\n\t"
      "call *%[cff4d0]\n\t"
      "addl $0x1c, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0004a460_12:\n\t"
      "movl -0x4(%%ebp), %%esi\n\t"
      "testw %%si, %%si\n\t"
      "je .LFUN_0004a460_13\n\t"
      "leal -0x108(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x108(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "call *%[c108fa0]\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x108(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "call *%[c108e70]\n\t"
      "movswl %%si, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x25ae3c\n\t"
      "pushl $0\n\t"
      "call *%[cff4d0]\n\t"
      "addl $0x28, %%esp\n\t"
      ".LFUN_0004a460_13:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b4a460_assert), [exitfn] "m"(b4a460_exitfn), [memset] "m"(b4a460_memset), [c8dcb0] "m"(b4a460_c8dcb0), [c108f00] "m"(b4a460_c108f00), [cff4d0] "m"(b4a460_cff4d0), [c108fa0] "m"(b4a460_c108fa0), [c108e70] "m"(b4a460_c108e70)
      : "memory");
}
#else
#error "FUN_0004a460: clang naked draft required"
#endif

