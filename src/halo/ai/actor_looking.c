/* actor_looking.c — AI actor looking/targeting subsystem.
 *
 * Corresponds to actor_looking.obj (or the actor_looking portion of the
 * compiled AI module).
 * Assertion path: c:\halo\SOURCE\ai\actor_looking.c
 */

#include "../../common.h"
#include "../../x87_math.h"

/* Cross-object callee declarations */
extern float distance_squared3d(const float *a, const float *b);
extern float actor_destination_tolerance(int actor_handle);
extern char *actor_combat_get_firing_variant_definition(int actor_handle);
extern void actor_find_pathfinding_location(int actor_handle);

/* Kept for reference after FUN_00013dd0 naked draft (batch 75). */
__attribute__((unused)) __declspec(noinline) static int
s_actor_charge_estimate_target(char *actor, float *target_pos)
{
  if (!*(char *)(actor + 0x4a8))
    return 0;
  unit_estimate_position(*(int *)(actor + 0x18), 1,
                         (vector3_t *)(actor + 0x4ac), NULL, NULL,
                         (vector3_t *)target_pos);
  return 1;
}

/* FUN_00013dd0 (0x13dd0) — XBE naked draft (batch 75). */
#if defined(__clang__)
static void *(*const b13dd0_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void (*const b13dd0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b13dd0_exitfn)(int) = system_exit;
static bool (*const b13dd0_ray)(unsigned int, float *, float *, int, short *) = FUN_0014df70;
static void (*const b13dd0_c1a93e0)(int unit_handle, int16_t estimate_mode, vector3_t *body_position, vector3_t *desired_facing, vector3_t *desired_gun_offset, vector3_t *out_position) = unit_estimate_position;

__attribute__((naked, noinline))
int FUN_00013dd0(int actor_handle __attribute__((unused)), float *source_pos __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x68, %%esp\n\t"
      "movl 0x6325a4, %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movb 0x484(%%eax), %%cl\n\t"
      "addl $8, %%esp\n\t"
      "testb %%cl, %%cl\n\t"
      "movl $1, %%ebx\n\t"
      "je .LFUN_00013dd0_4\n\t"
      "addl $0x120, %%eax\n\t"
      "movl (%%eax), %%edx\n\t"
      "movl %%edx, -0xc(%%ebp)\n\t"
      "movl 0x4(%%eax), %%ecx\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "movl 0x8(%%eax), %%edx\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      ".LFUN_00013dd0_1:\n\t"
      "cmpw $0x20, 0x4761d8\n\t"
      "jl .LFUN_00013dd0_2\n\t"
      "pushl %%ebx\n\t"
      "pushl $0x379\n\t"
      "pushl $0x2533f4\n\t"
      "pushl $0x253440\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00013dd0_2:\n\t"
      "movw 0x4761d8, %%ax\n\t"
      "movswl %%ax, %%ecx\n\t"
      "movw $5, 0x5a8c80(,%%ecx,2)\n\t"
      "incw %%ax\n\t"
      "movw %%ax, 0x4761d8\n\t"
      "leal -0x68(%%ebp), %%edx\n\t"
      "flds (%%esi)\n\t"
      "pushl %%edx\n\t"
      "fsubs -0xc(%%ebp)\n\t"
      "pushl $-1\n\t"
      "leal -0x18(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "leal -0xc(%%ebp), %%ecx\n\t"
      "flds 0x4(%%esi)\n\t"
      "pushl %%ecx\n\t"
      "fsubs -0x8(%%ebp)\n\t"
      "pushl $0x33\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "flds 0x8(%%esi)\n\t"
      "fsubs -0x4(%%ebp)\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "call *%[ray]\n\t"
      "addl $0x14, %%esp\n\t"
      "cmpw %%bx, 0x4761d8\n\t"
      "jg .LFUN_00013dd0_3\n\t"
      "pushl %%ebx\n\t"
      "pushl $0x381\n\t"
      "pushl $0x2533f4\n\t"
      "pushl $0x253418\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00013dd0_3:\n\t"
      "decw 0x4761d8\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00013dd0_4:\n\t"
      "movb 0x4a8(%%eax), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "je .LFUN_00013dd0_5\n\t"
      "leal -0xc(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "leal 0x4ac(%%eax), %%edx\n\t"
      "movl 0x18(%%eax), %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "call *%[c1a93e0]\n\t"
      "addl $0x18, %%esp\n\t"
      "jmp .LFUN_00013dd0_1\n\t"
      ".LFUN_00013dd0_5:\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [dget] "m"(b13dd0_dget), [assert] "m"(b13dd0_assert), [exitfn] "m"(b13dd0_exitfn), [ray] "m"(b13dd0_ray), [c1a93e0] "m"(b13dd0_c1a93e0)
      : "memory");
}
#else
#error "FUN_00013dd0: clang naked draft required"
#endif


/* FUN_00013ef0 (0x13ef0) — XBE naked draft (batch 69). */
#if defined(__clang__)
static void *(*const b13ef0_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void *(*const b13ef0_tag)(int, int) = tag_get;
static int (*const b13ef0_gtime)(void) = game_time_get;
static void (*const b13ef0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b13ef0_exitfn)(int) = system_exit;
static void *(*const b13ef0_memset)(void *, int, unsigned int) = csmemset;
static void *(*const b13ef0_get)(int, int) = object_get_and_verify_type;
static int *(*const b13ef0_gseed)(void) = get_global_random_seed_address;
static float (*const b13ef0_rmreal)(unsigned int *) = random_math_real;
static char (*const b13ef0_c1a83e0)(int unit_handle, char is_secondary, int *out_tick_count, float *out_attack_time, int16_t *out_frame_count, float *out_damage_time) = unit_get_melee_range_and_ticks;
static void (*const b13ef0_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;
static float (*const b13ef0_c12ad0)(int actor_handle, int action_type, void *charge_state) = FUN_00012ad0;
static char (*const b13ef0_c2d9b0)(int actor_handle, int encounter_handle, float distance) = actor_move_to_prop;
static void (*const b13ef0_c2a330)(int actor_handle) = FUN_0002a330;
static int (*const b13ef0_c13dd0)(int actor_handle, float *source_pos) = FUN_00013dd0;

__attribute__((naked, noinline))
char FUN_00013ef0(int actor_handle __attribute__((unused)), int action_type __attribute__((unused)), void *charge_state __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x20, %%esp\n\t"
      "movl 0x6325a4, %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x58(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x61637472\n\t"
      "movl %%esi, -0x1c(%%ebp)\n\t"
      "call *%[tag]\n\t"
      "movl 0x331f58, %%ecx\n\t"
      "andl $0xffff, %%edi\n\t"
      "imull $0x657c, %%edi, %%edi\n\t"
      "movl %%eax, %%ebx\n\t"
      "addl $0x10, %%esp\n\t"
      "movl %%ebx, -0xc(%%ebp)\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "addl %%ecx, %%edi\n\t"
      "call *%[gtime]\n\t"
      "movl %%eax, 0x18c(%%edi)\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_00013ef0_1\n\t"
      "pushl $1\n\t"
      "pushl $0x2f\n\t"
      "pushl $0x2533f4\n\t"
      "pushl $0x25334c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00013ef0_1:\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "pushl $0x38\n\t"
      "pushl $0\n\t"
      "pushl %%edx\n\t"
      "call *%[memset]\n\t"
      "addl $0xc, %%esp\n\t"
      "call *%[gtime]\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "movl %%eax, (%%ecx)\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "cmpw $5, %%ax\n\t"
      "je .LFUN_00013ef0_24\n\t"
      "cmpw $4, %%ax\n\t"
      "je .LFUN_00013ef0_24\n\t"
      "cmpw $2, %%ax\n\t"
      "jne .LFUN_00013ef0_22\n\t"
      "movb 0x6(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00013ef0_2\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "movw $2, 0x190(%%edi)\n\t"
      "jmp .LFUN_00013ef0_25\n\t"
      ".LFUN_00013ef0_2:\n\t"
      "movl 0x18(%%esi), %%edx\n\t"
      "pushl $3\n\t"
      "pushl %%edx\n\t"
      "call *%[get]\n\t"
      "movb 0xb6(%%eax), %%cl\n\t"
      "addl $8, %%esp\n\t"
      "testb %%cl, %%cl\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "jns .LFUN_00013ef0_3\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "movw $3, 0x190(%%edi)\n\t"
      "jmp .LFUN_00013ef0_25\n\t"
      ".LFUN_00013ef0_3:\n\t"
      "movl 0x270(%%esi), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "jne .LFUN_00013ef0_4\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "movw $4, 0x190(%%edi)\n\t"
      "jmp .LFUN_00013ef0_25\n\t"
      ".LFUN_00013ef0_4:\n\t"
      "pushl %%eax\n\t"
      "movl 0x5ab23c, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "flds 0x388(%%ecx)\n\t"
      "movl %%eax, %%ebx\n\t"
      "fcomps 0x2533c0\n\t"
      "addl $8, %%esp\n\t"
      "movl %%ebx, -0x20(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .LFUN_00013ef0_8\n\t"
      "flds 0x390(%%ecx)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .LFUN_00013ef0_8\n\t"
      "movb 0x130(%%ebx), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00013ef0_7\n\t"
      "cmpw $0, 0x9c(%%ebx)\n\t"
      "jg .LFUN_00013ef0_7\n\t"
      "call *%[gseed]\n\t"
      "pushl %%eax\n\t"
      "call *%[rmreal]\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "fcomps 0x390(%%edx)\n\t"
      "addl $4, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00013ef0_5\n\t"
      "movl $1, %%ecx\n\t"
      "jmp .LFUN_00013ef0_6\n\t"
      ".LFUN_00013ef0_5:\n\t"
      "xorl %%ecx, %%ecx\n\t"
      ".LFUN_00013ef0_6:\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "movb %%cl, 0xa(%%eax)\n\t"
      "flds 0x11c(%%ebx)\n\t"
      "fcomps 0x384(%%edx)\n\t"
      "movb %%cl, -0x8(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00013ef0_9\n\t"
      "xorb %%cl, %%cl\n\t"
      "movb %%cl, -0x8(%%ebp)\n\t"
      "jmp .LFUN_00013ef0_11\n\t"
      ".LFUN_00013ef0_7:\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "movb $1, 0xa(%%ecx)\n\t"
      "movb $1, %%cl\n\t"
      "movb %%cl, -0x8(%%ebp)\n\t"
      "jmp .LFUN_00013ef0_10\n\t"
      ".LFUN_00013ef0_8:\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "xorb %%cl, %%cl\n\t"
      "movb $0, 0xa(%%edx)\n\t"
      "movb %%cl, -0x8(%%ebp)\n\t"
      "jmp .LFUN_00013ef0_11\n\t"
      ".LFUN_00013ef0_9:\n\t"
      "testb %%cl, %%cl\n\t"
      "je .LFUN_00013ef0_11\n\t"
      ".LFUN_00013ef0_10:\n\t"
      "movl $3, 0xc(%%ebp)\n\t"
      ".LFUN_00013ef0_11:\n\t"
      "movb %%cl, 0x198(%%edi)\n\t"
      "leal -0x14(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x6(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "leal -0x18(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl 0x18(%%esi), %%edx\n\t"
      "leal -0x10(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c1a83e0]\n\t"
      "addl $0x18, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00013ef0_21\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "testl $0x8000000, (%%eax)\n\t"
      "je .LFUN_00013ef0_12\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "movw -0x6(%%ebp), %%cx\n\t"
      "movw %%cx, 0x32(%%eax)\n\t"
      "movl $0, 0x34(%%eax)\n\t"
      "movb $1, 0x30(%%eax)\n\t"
      "jmp .LFUN_00013ef0_15\n\t"
      ".LFUN_00013ef0_12:\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "testw %%ax, %%ax\n\t"
      "jne .LFUN_00013ef0_14\n\t"
      "movl 0x5c(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x61637476\n\t"
      "call *%[tag]\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_00013ef0_13\n\t"
      "pushl %%eax\n\t"
      "pushl $0x25348c\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_00013ef0_13:\n\t"
      "movswl -0x6(%%ebp), %%eax\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fmuls 0x253398\n\t"
      "cdq\n\t"
      "subl %%edx, %%eax\n\t"
      "sarl $1, %%eax\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      ".LFUN_00013ef0_14:\n\t"
      "flds -0x14(%%ebp)\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "fsubs -0x18(%%ebp)\n\t"
      "movw %%ax, 0x32(%%ecx)\n\t"
      "movl %%ecx, %%eax\n\t"
      "fstps 0x34(%%ecx)\n\t"
      ".LFUN_00013ef0_15:\n\t"
      "movl 0xc(%%ebp), %%esi\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "pushl %%eax\n\t"
      "call *%[c12ad0]\n\t"
      "fsts -0xc(%%ebp)\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "addl $4, %%esp\n\t"
      "fstps 0x2c(%%eax)\n\t"
      "cmpw $3, %%si\n\t"
      "jne .LFUN_00013ef0_16\n\t"
      "flds 0x2533d8\n\t"
      "jmp .LFUN_00013ef0_17\n\t"
      ".LFUN_00013ef0_16:\n\t"
      "flds 0x2533ec\n\t"
      ".LFUN_00013ef0_17:\n\t"
      "fcoms -0xc(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00013ef0_18\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "jmp .LFUN_00013ef0_19\n\t"
      ".LFUN_00013ef0_18:\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "fstp %%st(0)\n\t"
      "movl %%ecx, -0xc(%%ebp)\n\t"
      ".LFUN_00013ef0_19:\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "movl -0x1c(%%ebp), %%eax\n\t"
      "movl 0x270(%%eax), %%ecx\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "call *%[c2d9b0]\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00013ef0_20\n\t"
      "pushl %%ebx\n\t"
      "call *%[c2a330]\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "movl -0x20(%%ebp), %%esi\n\t"
      "addl $0xc8, %%esi\n\t"
      "pushl %%edx\n\t"
      "movl %%ebx, %%eax\n\t"
      "call *%[c13dd0]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00013ef0_20\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "movw $7, 0x190(%%edi)\n\t"
      "jmp .LFUN_00013ef0_25\n\t"
      ".LFUN_00013ef0_20:\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "movw $6, 0x190(%%edi)\n\t"
      "movl %%eax, 0x194(%%edi)\n\t"
      "jmp .LFUN_00013ef0_25\n\t"
      ".LFUN_00013ef0_21:\n\t"
      "movw $5, 0x190(%%edi)\n\t"
      "jmp .LFUN_00013ef0_25\n\t"
      ".LFUN_00013ef0_22:\n\t"
      "testw %%ax, %%ax\n\t"
      "jne .LFUN_00013ef0_23\n\t"
      "testl $0x20000, (%%ebx)\n\t"
      "je .LFUN_00013ef0_23\n\t"
      "cmpw $5, 0x6e(%%esi)\n\t"
      "jl .LFUN_00013ef0_23\n\t"
      "movb 0x378(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00013ef0_23\n\t"
      "movl $1, 0xc(%%ebp)\n\t"
      "movw $8, 0x190(%%edi)\n\t"
      "jmp .LFUN_00013ef0_25\n\t"
      ".LFUN_00013ef0_23:\n\t"
      "movw $9, 0x190(%%edi)\n\t"
      "jmp .LFUN_00013ef0_25\n\t"
      ".LFUN_00013ef0_24:\n\t"
      "cmpw $1, 0x15e(%%esi)\n\t"
      "setg %%al\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "testb %%al, %%al\n\t"
      "sete %%cl\n\t"
      "movb %%al, -0x1(%%ebp)\n\t"
      "movw %%cx, 0x190(%%edi)\n\t"
      ".LFUN_00013ef0_25:\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "movw 0xc(%%ebp), %%dx\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movw %%dx, 0x4(%%eax)\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [dget] "m"(b13ef0_dget), [tag] "m"(b13ef0_tag), [gtime] "m"(b13ef0_gtime), [assert] "m"(b13ef0_assert), [exitfn] "m"(b13ef0_exitfn), [memset] "m"(b13ef0_memset), [get] "m"(b13ef0_get), [gseed] "m"(b13ef0_gseed), [rmreal] "m"(b13ef0_rmreal), [c1a83e0] "m"(b13ef0_c1a83e0), [c8f390] "m"(b13ef0_c8f390), [c12ad0] "m"(b13ef0_c12ad0), [c2d9b0] "m"(b13ef0_c2d9b0), [c2a330] "m"(b13ef0_c2a330), [c13dd0] "m"(b13ef0_c13dd0)
      : "memory");
}
#else
#error "FUN_00013ef0: clang naked draft required"
#endif


/* FUN_000142a0 (0x142a0)
 * Conversation action initializer (action_converse.c, line 0x21).
 * Validates actor, looks up the conversation datum via 0x6324ec, fetches the
 * scenario conversation entry at scenario+0x468[*(short*)(action_ref+2)],
 * and populates state_data (20 bytes): [0]=action_handle, float@+8 from
 * tag+0x28, [3]=speaker_handle (if float==REAL_NONE) else -1, [4]=-1,
 * byte@+5=0. Returns 1 always.
 *
 * Confirmed: first datum_get(actor_data, actor_handle) result is discarded.
 * Confirmed: FCOMP+TEST AH,0x44+JP at 0x1432f — JP taken when PF=1 (NOT
 * equal/NaN) → speaker handle; fall-through (equal) → -1. */
char FUN_000142a0(int actor_handle, int action_handle, int *state_data)
{
  char *action_ref;
  char *tag_elem;
  float fVar1;
  int speaker;

  datum_get(actor_data, actor_handle);
  action_ref = (char *)datum_get(*(data_t **)0x6324ec, action_handle);
  tag_elem =
    (char *)tag_block_get_element((char *)global_scenario_get() + 0x468,
                                  (int)*(int16_t *)(action_ref + 2), 0x74);
  if (state_data == (int *)0) {
    display_assert("state_data", "c:\\halo\\SOURCE\\ai\\action_converse.c",
                   0x21, 1);
    system_exit(-1);
  }
  csmemset(state_data, 0, 0x14);
  *state_data = action_handle;
  fVar1 = *(float *)(tag_elem + 0x28);
  *(float *)((char *)state_data + 8) = fVar1;
  if (fVar1 == *(float *)0x2533c0) {
    speaker = -1;
  } else {
    speaker = *(int *)(action_ref + 0x10);
  }
  state_data[3] = speaker;
  state_data[4] = -1;
  *(char *)((char *)state_data + 5) = 0;
  return 1;
}

/* actor_update_prop_desire (0x14360) — XBE naked draft (batch 87). */
#if defined(__clang__)
static void *(*const b14360_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static int (*const b14360_c64b40)(int actor_handle, int unit_handle, char create_if_needed, char refresh_flag) = FUN_00064b40;
static void (*const b14360_c2f1a0)(int actor_handle) = FUN_0002f1a0;
static char (*const b14360_c2d9b0)(int actor_handle, int encounter_handle, float distance) = actor_move_to_prop;

__attribute__((naked, noinline))
char actor_update_prop_desire(int actor_handle __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl 0x6325a4, %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%esi\n\t"
      "movb 0x4c(%%esi), %%al\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_update_prop_desire_7\n\t"
      "cmpl $-1, 0xac(%%esi)\n\t"
      "movl $1, %%ebx\n\t"
      "jne .Lactor_update_prop_desire_1\n\t"
      "movl 0xa8(%%esi), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lactor_update_prop_desire_1\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "call *%[c64b40]\n\t"
      "addl $0x10, %%esp\n\t"
      "movl %%eax, 0xac(%%esi)\n\t"
      ".Lactor_update_prop_desire_1:\n\t"
      "movl 0xac(%%esi), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lactor_update_prop_desire_6\n\t"
      "movb 0xa1(%%esi), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "jne .Lactor_update_prop_desire_4\n\t"
      "movl 0x5ab23c, %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $2, 0x32(%%ecx)\n\t"
      "jl .Lactor_update_prop_desire_2\n\t"
      "flds 0x11c(%%ecx)\n\t"
      "fcomps 0xa4(%%esi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .Lactor_update_prop_desire_3\n\t"
      ".Lactor_update_prop_desire_2:\n\t"
      "flds 0x11c(%%ecx)\n\t"
      "fcomps 0x2533c4\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lactor_update_prop_desire_4\n\t"
      ".Lactor_update_prop_desire_3:\n\t"
      "movb %%bl, 0xa1(%%esi)\n\t"
      ".Lactor_update_prop_desire_4:\n\t"
      "movb 0xa1(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_update_prop_desire_5\n\t"
      "pushl %%edi\n\t"
      "call *%[c2f1a0]\n\t"
      "movb 0xa0(%%esi), %%al\n\t"
      "addl $4, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lactor_update_prop_desire_5:\n\t"
      "movl 0xa4(%%esi), %%edx\n\t"
      "movl 0xac(%%esi), %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "call *%[c2d9b0]\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lactor_update_prop_desire_7\n\t"
      ".Lactor_update_prop_desire_6:\n\t"
      "movb %%bl, 0xa0(%%esi)\n\t"
      ".Lactor_update_prop_desire_7:\n\t"
      "movb 0xa0(%%esi), %%al\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [dget] "m"(b14360_dget), [c64b40] "m"(b14360_c64b40), [c2f1a0] "m"(b14360_c2f1a0), [c2d9b0] "m"(b14360_c2d9b0)
      : "memory");
}
#else
#error "actor_update_prop_desire: clang naked draft required"
#endif


/* FUN_00014460 (0x14460)
 * Validate actor handle by performing a datum lookup (result discarded). */
void FUN_00014460(int actor_handle)
{
  datum_get(actor_data, actor_handle);
}

/* FUN_00014480 (0x14480) — readable C lift from XBE leaf. */
void FUN_00014480(int actor_handle)
{
  char *actor;
  char *prop;
  int target;
  int unit_index;

  actor = (char *)datum_get(*(void **)0x6325a4, actor_handle);
  prop = 0;
  target = -1;
  if (*(int *)(actor + 0x9c) != -1) {
    prop = (char *)datum_get(*(void **)0x6324ec, *(int *)(actor + 0x9c));
  }
  if (*(int *)(actor + 0xac) != -1) {
    target = *(int *)(actor + 0xac);
  } else if (prop != 0) {
    unit_index = *(int *)(prop + 0x10);
    if (unit_index != -1) {
      target = prop_get_active_by_unit_index(actor_handle, unit_index);
    }
  }
  *(short *)(actor + 0x3fc) = 1;
  if (target != -1) {
    *(short *)(actor + 0x3e8) = 3;
    *(short *)(actor + 0x3ec) = 1;
    *(int *)(actor + 0x3f0) = target;
  }
}




/* actor_set_prop_if_match (0x14510) — readable C lift. */
void actor_set_prop_if_match(int actor_handle, int old_prop, int new_prop)
{
  char *actor;

  actor = (char *)datum_get(*(void **)0x6325a4, actor_handle);
  if (*(int *)(actor + 0xac) == old_prop) {
    *(int *)(actor + 0x9c + 0x10) = new_prop;
  }
}

/* FUN_00014540 (0x14540) — XBE naked draft (batch 76). */
#if defined(__clang__)
static void *(*const b14540_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static int (*const b14540_c64ab0)(int actor_handle, int object_handle) = prop_get_active_by_unit_index;
static void (*const b14540_c1a9200)(int object_handle, float *out_position) = unit_get_head_position;
static int (*const b14540_c27a60)(int actor_handle, short look_type, short priority, short *look_buf) = FUN_00027a60;

__attribute__((naked, noinline))
void FUN_00014540(int actor_handle __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x10, %%esp\n\t"
      "movl 0x6325a4, %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x1dc(%%esi), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_00014540_3\n\t"
      "movl 0x1e0(%%esi), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_00014540_3\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "call *%[c64ab0]\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_00014540_1\n\t"
      "movw $1, -0x10(%%ebp)\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "jmp .LFUN_00014540_2\n\t"
      ".LFUN_00014540_1:\n\t"
      "movl 0x1e0(%%esi), %%edx\n\t"
      "leal -0xc(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "movw $3, -0x10(%%ebp)\n\t"
      "call *%[c1a9200]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_00014540_2:\n\t"
      "leal -0x10(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $5\n\t"
      "pushl $8\n\t"
      "pushl %%edi\n\t"
      "call *%[c27a60]\n\t"
      "addl $0x10, %%esp\n\t"
      ".LFUN_00014540_3:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [dget] "m"(b14540_dget), [c64ab0] "m"(b14540_c64ab0), [c1a9200] "m"(b14540_c1a9200), [c27a60] "m"(b14540_c27a60)
      : "memory");
}
#else
#error "FUN_00014540: clang naked draft required"
#endif


/* FUN_000145c0 (0x145c0)
 * Stop any active conversation for this actor.
 *
 * Reads the actor's conversation handle at actor+0x1dc.  If it is not -1
 * (i.e. there is an active conversation), calls ai_conversation_finish with
 * that handle, no advance (0), and no explicit end (0).
 *
 * Confirmed: datum_get(actor_data, actor_handle) pattern from disassembly.
 * Confirmed: guard on [actor+0x1dc] != -1 before call.
 * Confirmed: ADD ESP,0xC after call — 3 cdecl args.
 * Confirmed: ai_conversation_finish(*(int *)(actor+0x1dc), 0, 0). */
void FUN_000145c0(int actor_handle)
{
  char *actor;
  actor = (char *)datum_get(actor_data, actor_handle);
  if (*(int *)(actor + 0x1dc) != -1) {
    ai_conversation_finish(*(int *)(actor + 0x1dc), 0, 0);
  }
}

/* FUN_000145f0 (0x145f0)
 * Stop any active conversation for this actor (second variant).
 *
 * Structurally identical to FUN_000145c0.  Two separate functions exist in
 * the binary at distinct addresses; both read actor+0x1dc and call
 * ai_conversation_finish if a conversation is active.
 *
 * Confirmed: identical decompile to FUN_000145c0 at 0x145f0.
 * Inferred: two entry points probably correspond to different calling
 *   contexts (e.g. voluntary vs forced conversation stop). */
void FUN_000145f0(int actor_handle)
{
  char *actor;
  actor = (char *)datum_get(actor_data, actor_handle);
  if (*(int *)(actor + 0x1dc) != -1) {
    ai_conversation_finish(*(int *)(actor + 0x1dc), 0, 0);
  }
}

/* FUN_00014620 (0x14620) — readable C lift. */
extern char DAT_002534e0[];
extern char DAT_0025334c[];
char FUN_00014620(int actor_handle, void *state_data)
{
  (void)actor_handle;
  if (state_data == 0) {
    display_assert(DAT_0025334c, DAT_002534e0, 0x1e, 1);
    system_exit(-1);
  }
  csmemset(state_data, 0, 4);
  return 1;
}

/* FUN_00014680 (0x14680)
 * Countdown timer for actor action state: decrements actor+0x9c when flag
 * actor+0x484 is set; when the counter hits zero and a pending action state
 * exists (actor+0x3b8 != -1) with no transition in progress (actor+0x3ba == 0),
 * dispatches the state via FUN_00024be0.
 */
void FUN_00014680(int actor_handle)
{
  char *actor;
  short cnt;
  short state;

  actor = (char *)datum_get(actor_data, actor_handle);
  if (*(short *)(actor + 0x9c) > 0 && *(char *)(actor + 0x484) != '\0') {
    cnt = *(short *)(actor + 0x9c) - 1;
    *(short *)(actor + 0x9c) = cnt;
    if (cnt == 0) {
      state = *(short *)(actor + 0x3b8);
      if (state != -1 && *(char *)(actor + 0x3ba) == '\0') {
        FUN_00024be0(actor_handle, state, 0);
      }
    }
  }
}

/* FUN_000146f0 (0x146f0)
 * Initialize actor scripted-look state (type 5 target, scripted look mode).
 *
 * Copies the scripted-look timer seed from actor+0x358 to actor+0x426.
 * Sets look priority (actor+0x3e8) to 5, look-spec type (actor+0x3ec) to 2,
 * another look field (actor+0x3fc) to 4, and clears four flag bytes starting
 * at actor+0x424.
 *
 * If the actor's behavior type (actor+0x15e) is not 4 AND the actor's team
 * type (actor+0x6e) is > 4, also sets actor+0x454 = 1 and raises the look
 * priority to 7.
 *
 * Confirmed: datum_get(actor_data, actor_handle) from decompile.
 * Inferred: actor+0x3e8 = look priority (int16_t); actor+0x3ec = look spec
 *   type (int16_t); actor+0x3fc = look frame type (int16_t).
 * Inferred: actor+0x424..0x428 = look state flags (char[5]).
 * Inferred: actor+0x15e = behavior type (int16_t); actor+0x6e = team (int16_t).
 * Inferred: actor+0x454 = scripted look override flag (char). */
void FUN_000146f0(int actor_handle)
{
  char *actor;
  actor = (char *)datum_get(actor_data, actor_handle);
  *(char *)(actor + 0x426) = *(char *)(actor + 0x358);
  *(short *)(actor + 1000) = 5; /* actor+0x3e8 = look priority */
  *(short *)(actor + 0x3ec) = 2; /* look spec type */
  *(short *)(actor + 0x3fc) = 4; /* look frame type */
  *(char *)(actor + 0x427) = 0;
  *(char *)(actor + 0x428) = 0;
  *(char *)(actor + 0x424) = 0;
  *(char *)(actor + 0x425) = 0;
  if ((*(short *)(actor + 0x15e) != 4) && (*(short *)(actor + 0x6e) >= 4)) {
    *(char *)(actor + 0x454) = 1;
    *(short *)(actor + 1000) = 7; /* raise look priority */
  }
}

/* FUN_00014770 (0x14770) — XBE naked draft (batch 69). */
#if defined(__clang__)
static void (*const b14770_chkstk)(void) = FUN_001d90e0;
static void *(*const b14770_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void (*const b14770_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b14770_exitfn)(int) = system_exit;
static void *(*const b14770_tag)(int, int) = tag_get;
static char * (*const b14770_c211f0)(int actor_handle) = actor_combat_get_firing_variant_definition;
static void (*const b14770_c3bc90)(int actor_handle) = actor_find_pathfinding_location;
static char (*const b14770_c25a00)(int actor_handle, float *position, int surface_index, int group_mask) = actor_has_accessible_firing_position;
static scenario_t * (*const b14770_c18e380)(void) = global_scenario_get;
static void *(*const b14770_elem)(void *, int, int) = tag_block_get_element;
static float (*const b14770_c3bd50)(int actor_handle) = actor_destination_tolerance;
static float (*const b14770_c121a0)(const float *a, const float *b) = distance_squared3d;
static void (*const b14770_c2f1a0)(int actor_handle) = FUN_0002f1a0;
static void *(*const b14770_memset)(void *, int, unsigned int) = csmemset;
static short (*const b14770_c27090)(int actor_handle, void *param_2, void *param_3, void *param_4, void *param_5, void *param_6) = FUN_00027090;
static short (*const b14770_c272d0)(int actor_handle, short param_2, void *param_3, int param_4, unsigned int param_5, char param_6) = FUN_000272d0;
static int *(*const b14770_gseed)(void) = get_global_random_seed_address;
static float (*const b14770_rrange)(int *, float, float) = random_real_range;
static void *(*const b14770_get)(int, int) = object_get_and_verify_type;
static void (*const b14770_ftol)(void) = FUN_001d9068;
static bool (*const b14770_c3b320)(int actor_handle) = actor_has_ranged_weapon;
static void (*const b14770_c32ac0)(int actor_handle, int prop_handle, char flag) = actor_perception_unreachable;

__attribute__((naked, noinline))
unsigned int FUN_00014770(int actor_handle __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl $0x1474c, %%eax\n\t"
      "call *%[chkstk]\n\t"
      "movl 0x6325a4, %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%esi\n\t"
      "movb 0x6(%%esi), %%al\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00014770_1\n\t"
      "pushl $1\n\t"
      "pushl $0x37\n\t"
      "pushl $0x2534e0\n\t"
      "pushl $0x253380\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00014770_1:\n\t"
      "movb 0x4c(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00014770_11\n\t"
      "movl 0x58(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x61637472\n\t"
      "call *%[tag]\n\t"
      "movl %%eax, %%ebx\n\t"
      "pushl %%edi\n\t"
      "movl %%ebx, -0x4(%%ebp)\n\t"
      "call *%[c211f0]\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "movb 0x160(%%esi), %%al\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00014770_8\n\t"
      "movb 0x358(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00014770_5\n\t"
      "testb $0x20, (%%ebx)\n\t"
      "je .LFUN_00014770_5\n\t"
      "pushl %%edi\n\t"
      "call *%[c3bc90]\n\t"
      "movl 0x164(%%esi), %%edx\n\t"
      "pushl $0\n\t"
      "pushl %%edx\n\t"
      "leal 0x168(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "call *%[c25a00]\n\t"
      "addl $0x14, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00014770_5\n\t"
      "movl 0x34(%%esi), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "movb $0, -0x5(%%ebp)\n\t"
      "je .LFUN_00014770_2\n\t"
      "cmpw $-1, 0x3b8(%%esi)\n\t"
      "je .LFUN_00014770_2\n\t"
      "andl $0xffff, %%eax\n\t"
      "pushl $0xb0\n\t"
      "pushl %%eax\n\t"
      "call *%[c18e380]\n\t"
      "addl $0x42c, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movswl 0x3b8(%%esi), %%ecx\n\t"
      "pushl $0x18\n\t"
      "pushl %%ecx\n\t"
      "addl $0x98, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "pushl %%edi\n\t"
      "movl %%eax, %%ebx\n\t"
      "call *%[c3bd50]\n\t"
      "leal 0x12c(%%esi), %%edx\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edx\n\t"
      "call *%[c121a0]\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fmuls -0x4(%%ebp)\n\t"
      "addl $0x24, %%esp\n\t"
      "fcompp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00014770_2\n\t"
      "movb $1, -0x5(%%ebp)\n\t"
      ".LFUN_00014770_2:\n\t"
      "movb 0x504(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00014770_3\n\t"
      "movb 0x1fc(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00014770_3\n\t"
      "movl 0x270(%%esi), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_00014770_8\n\t"
      "pushl %%eax\n\t"
      "movl 0x5ab23c, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "flds 0x11c(%%eax)\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "fcomps 0xa0(%%ecx)\n\t"
      "addl $8, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00014770_8\n\t"
      "jmp .LFUN_00014770_4\n\t"
      ".LFUN_00014770_3:\n\t"
      "movb -0x5(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00014770_8\n\t"
      ".LFUN_00014770_4:\n\t"
      "pushl %%edi\n\t"
      "movw $0xffff, 0x3b8(%%esi)\n\t"
      "call *%[c2f1a0]\n\t"
      "addl $4, %%esp\n\t"
      "jmp .LFUN_00014770_8\n\t"
      ".LFUN_00014770_5:\n\t"
      "movw 0x3b8(%%esi), %%bx\n\t"
      "pushl $0x670\n\t"
      "leal -0x6c0(%%ebp), %%edx\n\t"
      "pushl $0\n\t"
      "pushl %%edx\n\t"
      "call *%[memset]\n\t"
      "leal -0xc(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x1474c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x14(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x50(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x6c0(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edi\n\t"
      "movw $0, -0x6bc(%%ebp)\n\t"
      "call *%[c27090]\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl -0x14(%%ebp), %%edx\n\t"
      "leal -0x1474c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "leal -0x50(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "call *%[c272d0]\n\t"
      "addl $0x3c, %%esp\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "jne .LFUN_00014770_6\n\t"
      "movw $0, 0x9c(%%esi)\n\t"
      "jmp .LFUN_00014770_8\n\t"
      ".LFUN_00014770_6:\n\t"
      "cmpw %%bx, %%ax\n\t"
      "je .LFUN_00014770_8\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movl 0x3c4(%%eax), %%edx\n\t"
      "movl 0x3c0(%%eax), %%eax\n\t"
      "movl %%edx, %%ecx\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      "pushl %%ecx\n\t"
      "movl %%eax, %%edx\n\t"
      "pushl %%edx\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "call *%[gseed]\n\t"
      "pushl %%eax\n\t"
      "call *%[rrange]\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpw $0, 0x15e(%%esi)\n\t"
      "jle .LFUN_00014770_7\n\t"
      "movl 0x158(%%esi), %%eax\n\t"
      "pushl $2\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl (%%eax), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x76656869\n\t"
      "call *%[tag]\n\t"
      "movl %%eax, %%ecx\n\t"
      "flds 0x3a8(%%ecx)\n\t"
      "addl $0x10, %%esp\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00014770_7\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fcomps 0x3a8(%%ecx)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00014770_7\n\t"
      "movl 0x3a8(%%ecx), %%edx\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      ".LFUN_00014770_7:\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fmuls 0x253394\n\t"
      "call *%[ftol]\n\t"
      "movw %%ax, 0x9c(%%esi)\n\t"
      ".LFUN_00014770_8:\n\t"
      "cmpw $7, 0x268(%%esi)\n\t"
      "jl .LFUN_00014770_11\n\t"
      "movl 0x270(%%esi), %%eax\n\t"
      "movl 0x5ab23c, %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%ebx\n\t"
      "pushl %%edi\n\t"
      "movl %%ebx, -0x10(%%ebp)\n\t"
      "movb $1, -0x4(%%ebp)\n\t"
      "call *%[c3b320]\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00014770_10\n\t"
      "flds 0x11c(%%ebx)\n\t"
      "fcomps 0x608(%%esi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .LFUN_00014770_9\n\t"
      "movl 0x34(%%esi), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_00014770_10\n\t"
      "cmpw $-1, 0x3b8(%%esi)\n\t"
      "je .LFUN_00014770_10\n\t"
      "andl $0xffff, %%eax\n\t"
      "pushl $0xb0\n\t"
      "pushl %%eax\n\t"
      "call *%[c18e380]\n\t"
      "addl $0x42c, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movswl 0x3b8(%%esi), %%edx\n\t"
      "pushl $0x18\n\t"
      "pushl %%edx\n\t"
      "addl $0x98, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "pushl %%edi\n\t"
      "movl %%eax, %%ebx\n\t"
      "call *%[c3bd50]\n\t"
      "leal 0x12c(%%esi), %%eax\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "call *%[c121a0]\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fmuls -0xc(%%ebp)\n\t"
      "addl $0x24, %%esp\n\t"
      "fcompp\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00014770_10\n\t"
      "movl -0x10(%%ebp), %%edx\n\t"
      "movl 0x608(%%esi), %%ecx\n\t"
      "addl $0xbc, %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ebx\n\t"
      "movl %%ecx, -0xc(%%ebp)\n\t"
      "call *%[c121a0]\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fmuls -0xc(%%ebp)\n\t"
      "addl $8, %%esp\n\t"
      "fcompp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00014770_10\n\t"
      ".LFUN_00014770_9:\n\t"
      "movb $0, -0x4(%%ebp)\n\t"
      ".LFUN_00014770_10:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movl 0x270(%%esi), %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edi\n\t"
      "call *%[c32ac0]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_00014770_11:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [chkstk] "m"(b14770_chkstk), [dget] "m"(b14770_dget), [assert] "m"(b14770_assert), [exitfn] "m"(b14770_exitfn), [tag] "m"(b14770_tag), [c211f0] "m"(b14770_c211f0), [c3bc90] "m"(b14770_c3bc90), [c25a00] "m"(b14770_c25a00), [c18e380] "m"(b14770_c18e380), [elem] "m"(b14770_elem), [c3bd50] "m"(b14770_c3bd50), [c121a0] "m"(b14770_c121a0), [c2f1a0] "m"(b14770_c2f1a0), [memset] "m"(b14770_memset), [c27090] "m"(b14770_c27090), [c272d0] "m"(b14770_c272d0), [gseed] "m"(b14770_gseed), [rrange] "m"(b14770_rrange), [get] "m"(b14770_get), [ftol] "m"(b14770_ftol), [c3b320] "m"(b14770_c3b320), [c32ac0] "m"(b14770_c32ac0)
      : "memory");
}
#else
#error "FUN_00014770: clang naked draft required"
#endif


/* FUN_00014b40 (0x14b40)
 * Stop the actor's host unit from running blindly.
 *
 * Reads the unit handle at actor+0x18.  If valid (not -1), calls
 * unit_stop_running_blindly with that unit handle, clearing the blindly-running
 * flag on the unit.
 *
 * Confirmed: datum_get(actor_data, actor_handle) from decompile.
 * Confirmed: guard on [actor+0x18] != -1.
 * Confirmed: unit_stop_running_blindly(*(int *)(actor+0x18)) — single cdecl
 * arg. Inferred: actor+0x18 = unit datum handle. */
void FUN_00014b40(int actor_handle)
{
  char *actor;
  actor = (char *)datum_get(actor_data, actor_handle);
  if (*(int *)(actor + 0x18) != -1) {
    unit_stop_running_blindly(*(int *)(actor + 0x18));
  }
}

/* FUN_00014b70 (0x14b70)
 * Mark actor as controlled (scripted look override active).
 *
 * Sets the actor's control word at actor+0xa4 to 0xffff (all bits set) and
 * sets the controlled flag byte at actor+0xa2 to 1.
 *
 * Confirmed: datum_get(actor_data, actor_handle) from decompile.
 * Inferred: actor+0xa4 = control/override handle (int16_t, 0xffff = all).
 * Inferred: actor+0xa2 = controlled flag (char). */
void FUN_00014b70(int actor_handle)
{
  char *actor;
  actor = (char *)datum_get(actor_data, actor_handle);
  *(short *)(actor + 0xa4) = (short)0xffff;
  *(char *)(actor + 0xa2) = 1;
}

/* FUN_00014ba0 (0x14ba0) — readable C lift. */
void FUN_00014ba0(int actor_handle, int *param_2)
{
  unsigned char *actor;
  int *src;
  int i;

  actor = (unsigned char *)datum_get(*(void **)0x6325a4, actor_handle) + 0x9c;
  if (*(int16_t *)(actor + 0xc) > 0)
    src = *(int **)0x2ee6e0;
  else
    src = *(int **)0x2ee6d4;
  for (i = 0; i < 4; i++)
    param_2[i] = src[i];
}



/* FUN_00014c10 (0x14c10)
 * Firing-position state update for look/fight actor actions.
 *
 * Initialises state_data (zeroes it, fills the FP query buffer, queries
 * the best firing position via FUN_00025c10 + FUN_000272d0), then if a
 * valid FP and secondary target exist evaluates path accessibility via
 * the path_input / path_state pipeline.
 *
 * Register args:
 *   EBX = actor_handle
 *   ESI = state_data (output block, written throughout)
 * Stack arg:
 *   param_3 (int) DEAD: no [EBP+8] access in disasm.
 *
 * state_data field writes (all confirmed from disasm):
 *   +0x8  (short): fp_index; FUN_00025c10 ret written first (0x14d54),
 *                  then overwritten by FUN_000272d0 return (0x14d64)
 *   +0xa  (bool):  1 iff fp_index != -1 && (char)out3_int == 0 (0x14d7e)
 *   +0x20 (char):  0 always (0x14d81), conditionally path_state_approach_point
 *                  return (0x14e79)
 *   +0x6  (char):  always 0 at exit (0x14e7c)
 *
 * Stack-local layout (_chkstk EAX=0x28820 = 165920-byte frame):
 *   EBP-0x1    local_byte (char output from path_state_approach_point)
 *   EBP-0x5    out3_int (int written by FUN_00025c10 *out3; low byte used)
 *   EBP-0xc    tag_ptr
 *   EBP-0x10   actor_ptr
 *   EBP-0x14   out2 (int written by FUN_00025c10 *out2)
 *   EBP-0x50   fp_result_ptr (void* output from FUN_00025c10 *out1;
 *                used as struct ptr via [EBP-0x50]+0x14 accesses)
 *   EBP-0x98   path_buf (0x98 bytes)
 *   EBP-0x708  query_buf (0x670 bytes, csmemset confirmed)
 *   EBP-0x14794 path_state_buf (up to 0x146fc bytes)
 *   EBP-0x28820 huge_buf (0x1408c bytes raw FP candidate data)
 *
 * Confirmed: swarm assert action_flee.c:0x20a (522).
 * Confirmed: PUSH EDI at 0x14c22 is callee-save, not a datum_get arg.
 * Confirmed: datum_get(actor_data, actor_handle) global at 0x6325a4.
 * Confirmed: secondary target: datum_get(prop_data, state_data->0x1c).
 * Confirmed: fp_result_ptr is pointer output from FUN_00025c10; disasm
 *   0x14e2e MOV EAX,[EBP-0x50] then 0x14e31 MOV ECX,[EAX+0x14] proves it.
 * Confirmed: FUN_000272d0 param_3 = LEA [EBP-0x50] = &fp_result_ptr.
 * Confirmed: FUN_000272d0 param_5 = LEA [EBP-0x28820] = (uint)addr of huge_buf.
 */
void FUN_00014c10(int actor_handle, void *state_data, int param_3)
{
  char *actor;
  char *tag;
  char *sec_target;
  int fp_result_ptr[15]; /* 0x3c-byte record buffer: FUN_00025c10 memcpy's
                          * 0xf*4 = 60 bytes here and FUN_000272d0 reads it.
                          * Was void* (4 bytes) -> 56-byte stack overflow.
                          * Original reserves [ebp-0x50]..[ebp-0x14] = 0x3c. */
  short fp_index_tmp;
  short fp_index;
  int out2;
  int out3_int;
  char local_byte;
  int target_pos;
  unsigned char valid;
  char path_buf[0x98];
  char path_state_buf[0x146fc];
  char huge_buf[0x1408c];
  char query_buf[0x670];
  short group_type;

  (void)param_3; /* DEAD: no [EBP+8] access in disasm */

  actor = (char *)datum_get(actor_data, actor_handle);
  tag = (char *)tag_get(0x61637472, *(int *)(actor + 0x58));

  /* assert(!actor->meta.swarm) action_flee.c:0x20a */
  if (*(char *)(actor + 0x6) != 0) {
    display_assert("!actor->meta.swarm", "c:\\halo\\SOURCE\\ai\\action_flee.c",
                   0x20a, 1);
    system_exit(-1);
  }

  csmemset(query_buf, 0, 0x670);

  /* query_buf[0x41] = state_data+4; set before branch (0x14c7d, 0x14c88) */
  query_buf[0x41] = *(char *)((char *)state_data + 0x4);

  if (*(short *)((char *)state_data + 0xc) > 0) {
    /* Swarm actor: group_type = 1 */
    group_type = 1;
    if (*(short *)((char *)state_data) > 0) {
      query_buf[0x14] = 1;
      query_buf[0x15] = 1;
    }
    query_buf[0x36] = 1;
    *(float *)(query_buf + 0x38) = 10.0f;
    *(float *)(query_buf + 0x3c) = 6.0f;
  } else {
    /* Normal actor: group_type = 2 */
    query_buf[0x8] = *(char *)((char *)state_data + 0x5);
    group_type = 2;
    /* FPU: tag->0x320 > 0.0f (FCOMP [0x2533c0]=0.0; TEST AH,0x41; JNZ=6.0) */
    if (*(float *)(tag + 0x320) > 0.0f) {
      *(float *)(query_buf + 0x1c) = *(float *)(tag + 0x320);
    } else {
      *(float *)(query_buf + 0x1c) = 6.0f;
    }
  }

  *(short *)(query_buf + 0x4) = group_type;

  /* Store group handle at query_buf+0 (0x14d24), search firing positions */
  *(int *)query_buf =
    actor_get_firing_position_group(actor_handle, (int)group_type, 0);

  /*
   * FUN_00025c10 returns a short (AX = fp candidate count/index).
   * Writes pointer to fp results into fp_result_ptr via *out1 (EBP-0x50).
   * Writes out2 int via *out2 (EBP-0x14).
   * Writes out3 int via *out3 (EBP-0x5); low byte = exclusion flag.
   */
  fp_index_tmp = (short)FUN_00025c10(
    actor_handle, query_buf, fp_result_ptr, &out2, huge_buf, &out3_int);

  /* Temporary write (0x14d54); overwritten by FUN_000272d0 return */
  *(short *)((char *)state_data + 0x8) = fp_index_tmp;

  /*
   * FUN_000272d0:
   *   param_3 = &fp_result_ptr (address of pointer storage, void **)
   *   param_5 = (unsigned int) address of huge_buf (pointer as uint)
   */
  fp_index = FUN_000272d0(actor_handle, fp_index_tmp, fp_result_ptr, out2,
                          (unsigned int)(int)huge_buf, (char)out3_int);
  *(short *)((char *)state_data + 0x8) = fp_index;

  /* valid = 1 iff fp_index != -1 AND out3 low byte == 0 */
  valid = (fp_index != (short)-1) && ((char)out3_int == 0) ? 1 : 0;
  *(char *)((char *)state_data + 0xa) = (char)valid;
  *(char *)((char *)state_data + 0x20) = 0;

  if (fp_index != (short)-1 && *(int *)((char *)state_data + 0x1c) != -1) {
    sec_target =
      (char *)datum_get(prop_data, *(int *)((char *)state_data + 0x1c));

    /* If sec_target type (field_0x24) is 2 or 3: find prop pathfinding loc */
    if (*(short *)(sec_target + 0x24) >= 2 &&
        *(short *)(sec_target + 0x24) <= 3) {
      actor_perception_find_prop_pathfinding_location(
        actor_handle, *(int *)((char *)state_data + 0x1c));
    }

    /* Resolve target pos: sec_target->0x110 if not -1, else ->0x18 */
    if (*(int *)(sec_target + 0x110) != -1) {
      target_pos = *(int *)(sec_target + 0x110);
    } else {
      target_pos = *(int *)(sec_target + 0x18);
    }

    /* Path accessibility pipeline for the firing position */
    path_input_new(path_buf, *(unsigned int *)(tag + 0x8c), 0, target_pos);
    path_input_set_start(path_buf, (float *)(sec_target + 0xf0),
                         *(int *)(sec_target + 0xec));
    paths_dispose(path_buf, *(int *)(actor + 0x18));
    path_state_new(path_buf, path_state_buf, 0);
    /* fp_result_ptr->field_0x14 = *(int*)((char*)fp_result_ptr + 0x14) */
    FUN_0005e0d0(path_state_buf, (float *)fp_result_ptr,
                 *(int *)((char *)fp_result_ptr + 0x14), 0);
    if (FUN_0005ff70((unsigned int *)path_state_buf)) {
      *(char *)((char *)state_data + 0x20) =
        path_state_approach_point(path_state_buf, (float *)fp_result_ptr,
                                  *(int *)((char *)fp_result_ptr + 0x14),
                                  &local_byte, (char *)state_data + 0x24);
    }
  }

  *(char *)((char *)state_data + 0x6) = 0;
}

/* FUN_00014e90 (0x14e90) — XBE naked draft (batch 69). */
#if defined(__clang__)
static void *(*const b14e90_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void (*const b14e90_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b14e90_exitfn)(int) = system_exit;
static scenario_t * (*const b14e90_c18e380)(void) = global_scenario_get;
static void *(*const b14e90_elem)(void *, int, int) = tag_block_get_element;
static void (*const b14e90_c1a93e0)(int unit_handle, int16_t estimate_mode, vector3_t *body_position, vector3_t *desired_facing, vector3_t *desired_gun_offset, vector3_t *out_position) = unit_estimate_position;
static int (*const b14e90_c416e0)(float *origin, int bsp, float *target, int param_4, short param_5, char param_6, int param_7, char param_8) = ai_test_line_of_sight;

__attribute__((naked, noinline))
char FUN_00014e90(int actor_handle __attribute__((unused)), char *state_data __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x10, %%esp\n\t"
      "movl 0x6325a4, %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%edi\n\t"
      "movb 0x6(%%edi), %%al\n\t"
      "xorb %%bl, %%bl\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "movb %%bl, -0x1(%%ebp)\n\t"
      "je .LFUN_00014e90_1\n\t"
      "pushl $1\n\t"
      "pushl $0x265\n\t"
      "pushl $0x253504\n\t"
      "pushl $0x253380\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00014e90_1:\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "movl 0x1c(%%esi), %%eax\n\t"
      "orl $0xffffffff, %%ecx\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "je .LFUN_00014e90_6\n\t"
      "movl 0x34(%%edi), %%eax\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "je .LFUN_00014e90_6\n\t"
      "cmpw %%cx, 0x8(%%esi)\n\t"
      "je .LFUN_00014e90_6\n\t"
      "andl $0xffff, %%eax\n\t"
      "pushl $0xb0\n\t"
      "pushl %%eax\n\t"
      "call *%[c18e380]\n\t"
      "addl $0x42c, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl 0x1c(%%esi), %%edx\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl 0x5ab23c, %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "movswl 0x8(%%ecx), %%edx\n\t"
      "pushl $0x18\n\t"
      "pushl %%edx\n\t"
      "addl $0x98, %%ebx\n\t"
      "pushl %%ebx\n\t"
      "movl %%eax, %%esi\n\t"
      "call *%[elem]\n\t"
      "movl 0x18(%%edi), %%ecx\n\t"
      "movl %%eax, %%ebx\n\t"
      "leal -0x10(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl %%ebx\n\t"
      "pushl $2\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1a93e0]\n\t"
      "movl 0x158(%%edi), %%ecx\n\t"
      "movl 0x110(%%esi), %%eax\n\t"
      "cmpl $-1, %%ecx\n\t"
      "setne %%dl\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x100(%%esi), %%cx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl $0\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0xe(%%ebx), %%ax\n\t"
      "pushl $1\n\t"
      "pushl %%ecx\n\t"
      "leal 0x104(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x10(%%ebp), %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c416e0]\n\t"
      "movw 0x24(%%esi), %%cx\n\t"
      "addl $0x58, %%esp\n\t"
      "cmpw $2, %%cx\n\t"
      "jl .LFUN_00014e90_2\n\t"
      "cmpw $3, %%cx\n\t"
      "jg .LFUN_00014e90_2\n\t"
      "testw %%ax, %%ax\n\t"
      "sete %%cl\n\t"
      "jmp .LFUN_00014e90_3\n\t"
      ".LFUN_00014e90_2:\n\t"
      "movb -0x1(%%ebp), %%cl\n\t"
      ".LFUN_00014e90_3:\n\t"
      "testw %%ax, %%ax\n\t"
      "je .LFUN_00014e90_4\n\t"
      "cmpw $3, %%ax\n\t"
      "jne .LFUN_00014e90_5\n\t"
      ".LFUN_00014e90_4:\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movb $1, 0x20(%%eax)\n\t"
      "addl $0xbc, %%esi\n\t"
      "movl (%%esi), %%edx\n\t"
      "addl $0x24, %%eax\n\t"
      "movl %%edx, (%%eax)\n\t"
      "movl 0x4(%%esi), %%edx\n\t"
      "movl %%edx, 0x4(%%eax)\n\t"
      "movl 0x8(%%esi), %%edx\n\t"
      "movl %%edx, 0x8(%%eax)\n\t"
      ".LFUN_00014e90_5:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb %%cl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00014e90_6:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [dget] "m"(b14e90_dget), [assert] "m"(b14e90_assert), [exitfn] "m"(b14e90_exitfn), [c18e380] "m"(b14e90_c18e380), [elem] "m"(b14e90_elem), [c1a93e0] "m"(b14e90_c1a93e0), [c416e0] "m"(b14e90_c416e0)
      : "memory");
}
#else
#error "FUN_00014e90: clang naked draft required"
#endif


/* FUN_00014ff0 (0x14ff0)
 * Conditionally update the actor's look-frame field.
 *
 * If the current look-frame value at actor+0xb8 equals param_2, replaces
 * it with param_3.  This acts as a guarded transition — only fires if the
 * actor is in the expected look state.
 *
 * Confirmed: datum_get(actor_data, actor_handle) from decompile.
 * Confirmed: compare [actor+0xb8] == param_2 before write.
 * Inferred: actor+0xb8 = look frame / look state id (int). */
void FUN_00014ff0(int actor_handle, int param_2, int param_3)
{
  char *actor;
  actor = (char *)datum_get(actor_data, actor_handle);
  if (*(int *)(actor + 0xb8) == param_2) {
    *(int *)(actor + 0xb8) = param_3;
  }
}

/* FUN_00015020 (0x15020)
 * Test whether a look-state value is in the scripted-look priority range
 * [9,12].
 *
 * Returns 1 (true) if param_1 is in the half-open interval (8, 0xD), i.e.
 * 9 <= param_1 <= 12, else returns 0.
 *
 * Confirmed: 16-bit load via MOV AX,WORD PTR[EBP+8] at 0x15023 — param is
 *   a signed 16-bit short pushed as a dword.
 * Confirmed: CMP AX,9 / JL; CMP AX,0xC / JG; return 1 else return 0. */
int FUN_00015020(short param_1)
{
  if (param_1 >= 9 && param_1 <= 0xc) {
    return 1;
  }
  return 0;
}

/* FUN_00015040 (0x15040) — XBE naked draft (batch 69). */
#if defined(__clang__)
static void *(*const b15040_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void (*const b15040_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b15040_exitfn)(int) = system_exit;
static void *(*const b15040_memset)(void *, int, unsigned int) = csmemset;
static void (*const b15040_c308e0)(int actor_handle, int target) = actor_situation_try_new_target;
static int *(*const b15040_gseed)(void) = get_global_random_seed_address;
static float (*const b15040_rmreal)(unsigned int *) = random_math_real;
static void (*const b15040_c14c10)(int actor_handle, void *state_data, int param_3) = FUN_00014c10;

__attribute__((naked, noinline))
char FUN_00015040(int actor_handle __attribute__((unused)), short param_2 __attribute__((unused)), int param_3 __attribute__((unused)), char param_4 __attribute__((unused)), char param_5 __attribute__((unused)), char param_6 __attribute__((unused)), short *param_7 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $8, %%esp\n\t"
      "movl 0x6325a4, %%eax\n\t"
      "pushl %%ebx\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movb 0x160(%%eax), %%dl\n\t"
      "xorb %%cl, %%cl\n\t"
      "addl $8, %%esp\n\t"
      "testb %%dl, %%dl\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "movb %%cl, -0x1(%%ebp)\n\t"
      "jne .LFUN_00015040_6\n\t"
      "movl 0x20(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LFUN_00015040_1\n\t"
      "pushl $1\n\t"
      "pushl $0x2c\n\t"
      "pushl $0x253504\n\t"
      "pushl $0x25334c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00015040_1:\n\t"
      "pushl $0x30\n\t"
      "pushl $0\n\t"
      "pushl %%esi\n\t"
      "call *%[memset]\n\t"
      "movb 0x14(%%ebp), %%cl\n\t"
      "movb 0x1c(%%ebp), %%al\n\t"
      "movw 0xc(%%ebp), %%di\n\t"
      "movb 0x18(%%ebp), %%dl\n\t"
      "addl $0xc, %%esp\n\t"
      "negb %%cl\n\t"
      "movb %%al, 0x5(%%esi)\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "movw $0xffff, 0x8(%%esi)\n\t"
      "movw %%di, 0xc(%%esi)\n\t"
      "movb %%dl, 0x4(%%esi)\n\t"
      "movl %%eax, 0x1c(%%esi)\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "andl $0xb4, %%ecx\n\t"
      "cmpl $-1, %%eax\n\t"
      "movw %%cx, (%%esi)\n\t"
      "je .LFUN_00015040_2\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "call *%[c308e0]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_00015040_2:\n\t"
      "cmpw $9, %%di\n\t"
      "jl .LFUN_00015040_4\n\t"
      "cmpw $0xc, %%di\n\t"
      "jg .LFUN_00015040_4\n\t"
      "call *%[gseed]\n\t"
      "pushl %%eax\n\t"
      "call *%[rmreal]\n\t"
      "fcomps 0x253524\n\t"
      "addl $4, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00015040_4\n\t"
      "movw $0x2d, 0x2(%%esi)\n\t"
      ".LFUN_00015040_3:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00015040_4:\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movb 0x6(%%ecx), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00015040_5\n\t"
      "pushl $0\n\t"
      "call *%[c14c10]\n\t"
      "addl $4, %%esp\n\t"
      "cmpw $-1, 0x8(%%esi)\n\t"
      "jne .LFUN_00015040_3\n\t"
      "movb $0, 0xe(%%esi)\n\t"
      ".LFUN_00015040_5:\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00015040_6:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb %%cl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [dget] "m"(b15040_dget), [assert] "m"(b15040_assert), [exitfn] "m"(b15040_exitfn), [memset] "m"(b15040_memset), [c308e0] "m"(b15040_c308e0), [gseed] "m"(b15040_gseed), [rmreal] "m"(b15040_rmreal), [c14c10] "m"(b15040_c14c10)
      : "memory");
}
#else
#error "FUN_00015040: clang naked draft required"
#endif


/* FUN_00015150 (0x15150) — readable C lift. */
void FUN_00015150(int actor_handle)
{
  char *actor = (char *)datum_get(*(void **)0x6325a4, actor_handle);
  *(uint32_t *)(actor + 0xb4) = 0;
  if (*(int16_t *)(actor + 0xa8) > 0) {
    actor[0x98] = 0;
  }
  if (*(int16_t *)(actor + 0x9e) == 0) {
    int unit = *(int *)(actor + 0x18);
    int16_t mode = *(int16_t *)(actor + 0xa8);
    if (unit != -1 && mode >= 9 && mode <= 0xc) {
      unit_start_running_blindly(unit);
    }
  }
}

/* FUN_000151b0 (0x151b0) — readable C lift from XBE leaf. */
void FUN_000151b0(int actor_handle)
{
  char *actor;
  unsigned short timer;
  short action;

  actor = (char *)datum_get(*(void **)0x6325a4, actor_handle);
  *(int *)(actor + 0xb4) += 1;
  timer = *(unsigned short *)(actor + 0x9c);
  if ((short)timer > 0) {
    *(unsigned short *)(actor + 0x9c) = (unsigned short)(timer - 1);
  }
  timer = *(unsigned short *)(actor + 0x9e);
  if ((short)timer > 0) {
    timer = (unsigned short)(timer - 1);
    *(unsigned short *)(actor + 0x9e) = timer;
    if (timer == 0) {
      if (*(int *)(actor + 0x18) != -1) {
        action = *(short *)(actor + 0xa8);
        if (action >= 9 && action <= 0xc) {
          unit_start_running_blindly(*(int *)(actor + 0x18));
        }
      }
    }
  }
  if (*(short *)(actor + 0xa8) > 0) {
    *(int *)(actor + 0x39c) = game_time_get() + 0x2ee;
  }
}




/* FUN_00015250 (0x15250)
 * Classify the actor's current looking state and configure the firing-position
 * state block fields from live actor data.
 *
 * First, selects a look-mode value written to actor+0x3e8 (the enum field at
 * offset 1000).  Priority order:
 *   1. If actor+0xa8 >= 1 (has props? look-state > 0):
 *        mode=6, actor+0x3ec=0, actor+0x456=1.
 *   2. Else if actor+0x270 != -1 and prop_data[actor+0x270]+0x32 > 0:
 *        mode=7, actor+0x3ec=2, actor+0x454=1.  (forward goto to shared tail)
 *   3. Else if actor+0xb8 == -1:
 *        mode=0.
 *   4. Else:
 *        mode=3, actor+0x3ec=1, actor+0x3f0 = actor+0xb8.
 *
 * Shared tail (always executed):
 *   - actor+0x3fc = 4
 *   - actor+0x428 = (actor+0xa8 > 0) (bool byte)
 *   - actor+0x429 = (actor+0xa8 in [9,12])
 *   - actor+0x426 = 1, actor+0x427 = 0
 *   - actor+0x424 = 1, actor+0x425 = 0
 *
 * Then dispatches the look target:
 *   - If actor+0xa4 == -1: call FUN_0002f1a0 and return.
 *   - If actor+0x4c != 0: try actor_move_to_firing_position.
 *     On success: copy actor+0xa4..0xa6 into actor+0x3b8..0x3ba and return.
 *     On failure: if actor+0x3b8 != -1, dispatch FUN_00024be0 + FUN_0002f1a0
 *                 and clear 0x3b8.  Then set actor+0xa4=-1, actor+0xa2=1.
 *
 * Note: The original has a goto from branch 2 to the shared tail, bypassing
 * branches 3 and 4.  Restructured here with a `handled` flag (no C89 goto).
 * This produces TEST+JNZ instead of a JMP in VC71, which is a known structural
 * ceiling.  Disassembly cross-check not performed (Ghidra MCP unavailable at
 * lift time).
 *
 * Confirmed (decompilation): datum_get(actor_data, actor_handle) at entry;
 *   prop_data lookup at actor+0x270; sentinel comparisons -1 on actor+0xb8,
 *   actor+0xa4, actor+0x3b8.
 * Inferred: actor+0xa8 = look state (int16_t); actor+0x270 = prop handle (int);
 *   actor+0x4c = is_vehicle/prop flag (byte); actor+0x3b8 = cached look target;
 *   actor+0x3ec, 0x3fc = look-mode sub-fields; 0x424-0x429 = look flags. */
void FUN_00015250(int actor_handle)
{
  char *actor;
  char *prop;
  char move_result;

  actor = (char *)datum_get(actor_data, actor_handle);

  if (*(short *)(actor + 0xa8) > 0) {
    *(short *)(actor + 0x3e8) = 6;
    *(short *)(actor + 0x3ec) = 0;
    *(char *)(actor + 0x456) = 1;
  } else {
    if (*(int *)(actor + 0x270) != -1) {
      prop = (char *)datum_get(prop_data, *(int *)(actor + 0x270));
      if (*(short *)(prop + 0x32) > 0) {
        *(short *)(actor + 0x3e8) = 7;
        *(short *)(actor + 0x3ec) = 2;
        *(char *)(actor + 0x454) = 1;
        goto FUN_00015250_tail;
      }
    }
    if (*(int *)(actor + 0xb8) != -1) {
      *(short *)(actor + 0x3e8) = 3;
      *(short *)(actor + 0x3ec) = 1;
      *(int *)(actor + 0x3f0) = *(int *)(actor + 0xb8);
    } else {
      *(short *)(actor + 0x3e8) = 0;
    }
  }
FUN_00015250_tail:

  *(short *)(actor + 0x3fc) = 4;
  *(char *)(actor + 0x428) = *(short *)(actor + 0xa8) > 0;
  if (*(short *)(actor + 0xa8) >= 9 && *(short *)(actor + 0xa8) <= 0xc) {
    *(char *)(actor + 0x429) = 1;
  } else {
    *(char *)(actor + 0x429) = 0;
  }
  *(char *)(actor + 0x426) = 1;
  *(char *)(actor + 0x427) = 0;
  *(char *)(actor + 0x424) = 1;
  *(char *)(actor + 0x425) = 0;

  if (*(short *)(actor + 0xa4) == -1) {
    FUN_0002f1a0(actor_handle);
    return;
  }
  if (*(char *)(actor + 0x4c) != 0) {
    move_result =
      actor_move_to_firing_position(actor_handle, *(short *)(actor + 0xa4), 0);
    if (move_result != 0) {
      *(short *)(actor + 0x3b8) = *(short *)(actor + 0xa4);
      *(char *)(actor + 0x3ba) = *(char *)(actor + 0xa6);
      return;
    }
    if (*(short *)(actor + 0x3b8) != -1) {
      FUN_00024be0(actor_handle, *(short *)(actor + 0x3b8), 0);
      FUN_0002f1a0(actor_handle);
      *(short *)(actor + 0x3b8) = -1;
    }
    *(short *)(actor + 0xa4) = -1;
    *(char *)(actor + 0xa2) = 1;
  }
}

/* FUN_000153e0 (0x153e0) — XBE naked draft (batch 75). */
#if defined(__clang__)
static void *(*const b153e0_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void (*const b153e0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b153e0_exitfn)(int) = system_exit;
static scenario_t * (*const b153e0_c18e380)(void) = global_scenario_get;
static void *(*const b153e0_elem)(void *, int, int) = tag_block_get_element;
static int (*const b153e0_c2a3f0)(int actor_handle) = FUN_0002a3f0;
static float (*const b153e0_c3bd50)(int actor_handle) = actor_destination_tolerance;

__attribute__((naked, noinline))
bool FUN_000153e0(int actor_handle __attribute__((unused)))
{
  __asm__ volatile(
      "movl 0x6325a4, %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%esi\n\t"
      "movb 0x6(%%esi), %%al\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000153e0_1\n\t"
      "pushl $1\n\t"
      "pushl $0x1d6\n\t"
      "pushl $0x253504\n\t"
      "pushl $0x253380\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000153e0_1:\n\t"
      "movl 0x34(%%esi), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_000153e0_5\n\t"
      "cmpw $-1, 0x3b8(%%esi)\n\t"
      "je .LFUN_000153e0_5\n\t"
      "andl $0xffff, %%eax\n\t"
      "pushl $0xb0\n\t"
      "pushl %%eax\n\t"
      "call *%[c18e380]\n\t"
      "addl $0x42c, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movswl 0x3b8(%%esi), %%ecx\n\t"
      "pushl $0x18\n\t"
      "pushl %%ecx\n\t"
      "addl $0x98, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "pushl %%ebx\n\t"
      "movl %%eax, %%edi\n\t"
      "call *%[c2a3f0]\n\t"
      "addl $0x1c, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000153e0_2\n\t"
      "cmpw $3, 0x46c(%%esi)\n\t"
      "jne .LFUN_000153e0_2\n\t"
      "movw 0x470(%%esi), %%dx\n\t"
      "cmpw 0x3b8(%%esi), %%dx\n\t"
      "jne .LFUN_000153e0_2\n\t"
      "popl %%edi\n\t"
      "movb $1, %%al\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      ".LFUN_000153e0_2:\n\t"
      "pushl %%ebx\n\t"
      "call *%[c3bd50]\n\t"
      "flds (%%edi)\n\t"
      "fsubs 0x12c(%%esi)\n\t"
      "addl $4, %%esp\n\t"
      "flds 0x4(%%edi)\n\t"
      "fsubs 0x130(%%esi)\n\t"
      "flds 0x8(%%edi)\n\t"
      "fsubs 0x134(%%esi)\n\t"
      "fld %%st(2)\n\t"
      ".byte 0xd8, 0xcb\n\t"
      "fld %%st(2)\n\t"
      ".byte 0xd8, 0xcb\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fld %%st(1)\n\t"
      ".byte 0xd8, 0xca\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fld %%st(4)\n\t"
      ".byte 0xd8, 0xcd\n\t"
      "fcompp\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "fnstsw %%ax\n\t"
      "xorb %%al, %%al\n\t"
      "fstp %%st(0)\n\t"
      "testb $0x41, %%ah\n\t"
      "fstp %%st(0)\n\t"
      "jne .LFUN_000153e0_6\n\t"
      "movl 0xb8(%%esi), %%esi\n\t"
      "cmpl $-1, %%esi\n\t"
      "je .LFUN_000153e0_4\n\t"
      "movl 0x5ab23c, %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movw 0x38(%%eax), %%ax\n\t"
      "addl $8, %%esp\n\t"
      "testw %%ax, %%ax\n\t"
      "je .LFUN_000153e0_3\n\t"
      "cmpw $1, %%ax\n\t"
      "je .LFUN_000153e0_3\n\t"
      "xorb %%al, %%al\n\t"
      "testb %%al, %%al\n\t"
      "popl %%edi\n\t"
      "sete %%al\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      ".LFUN_000153e0_3:\n\t"
      "movb $1, %%al\n\t"
      ".LFUN_000153e0_4:\n\t"
      "testb %%al, %%al\n\t"
      "popl %%edi\n\t"
      "sete %%al\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      ".LFUN_000153e0_5:\n\t"
      "xorb %%al, %%al\n\t"
      ".LFUN_000153e0_6:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      :
      : [dget] "m"(b153e0_dget), [assert] "m"(b153e0_assert), [exitfn] "m"(b153e0_exitfn), [c18e380] "m"(b153e0_c18e380), [elem] "m"(b153e0_elem), [c2a3f0] "m"(b153e0_c2a3f0), [c3bd50] "m"(b153e0_c3bd50)
      : "memory");
}
#else
#error "FUN_000153e0: clang naked draft required"
#endif


/* FUN_00015520 (0x15520) — XBE naked draft (batch 69). */
#if defined(__clang__)
static void *(*const b15520_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static bool (*const b15520_c153e0)(int actor_handle) = FUN_000153e0;
static void (*const b15520_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b15520_exitfn)(int) = system_exit;
static void (*const b15520_c300b0)(int actor_handle) = actor_situation_update_target_status;
static void (*const b15520_c302b0)(int actor_handle) = actor_situation_combat_status_update;
static char (*const b15520_c14e90)(int actor_handle, char *state_data) = FUN_00014e90;
static void (*const b15520_c14c10)(int actor_handle, void *state_data, int param_3) = FUN_00014c10;
static int (*const b15520_gtime)(void) = game_time_get;
static int (*const b15520_c1a6bc0)(int param_1) = FUN_001a6bc0;
static void (*const b15520_c46f10)(int16_t type, int unit_handle, int param3, int param4, int16_t param5, int16_t param6, int16_t param7) = FUN_00046f10;
static char (*const b15520_c1a74d0)(int unit_handle, int scream_type) = FUN_001a74d0;

__attribute__((naked, noinline))
int FUN_00015520(int actor_handle __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl 0x6325a4, %%eax\n\t"
      "pushl %%ebx\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%edi\n\t"
      "movb 0x6(%%edi), %%al\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "leal 0x9c(%%edi), %%esi\n\t"
      "jne .LFUN_00015520_18\n\t"
      "movw 0xc(%%esi), %%ax\n\t"
      "cmpw $9, %%ax\n\t"
      "jl .LFUN_00015520_1\n\t"
      "cmpw $0xc, %%ax\n\t"
      "jg .LFUN_00015520_1\n\t"
      "movw $0xb4, (%%esi)\n\t"
      ".LFUN_00015520_1:\n\t"
      "cmpw $0, 0x2(%%esi)\n\t"
      "jle .LFUN_00015520_2\n\t"
      "movw $0xffff, 0x8(%%esi)\n\t"
      "jmp .LFUN_00015520_8\n\t"
      ".LFUN_00015520_2:\n\t"
      "orl $0xffffffff, %%eax\n\t"
      "cmpw %%ax, 0x8(%%esi)\n\t"
      "jne .LFUN_00015520_3\n\t"
      "movb $1, 0x6(%%esi)\n\t"
      "jmp .LFUN_00015520_8\n\t"
      ".LFUN_00015520_3:\n\t"
      "cmpw %%ax, 0x3b8(%%edi)\n\t"
      "jne .LFUN_00015520_4\n\t"
      "movw %%ax, 0x8(%%esi)\n\t"
      "movb $1, 0x6(%%esi)\n\t"
      "jmp .LFUN_00015520_8\n\t"
      ".LFUN_00015520_4:\n\t"
      "call *%[c153e0]\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00015520_8\n\t"
      "cmpw $-1, 0x3b8(%%edi)\n\t"
      "jne .LFUN_00015520_5\n\t"
      "pushl $1\n\t"
      "pushl $0x98\n\t"
      "pushl $0x253504\n\t"
      "pushl $0x253600\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00015520_5:\n\t"
      "cmpw $0, (%%esi)\n\t"
      "je .LFUN_00015520_6\n\t"
      "movb $1, 0x6(%%esi)\n\t"
      "jmp .LFUN_00015520_8\n\t"
      ".LFUN_00015520_6:\n\t"
      "movw 0x3b8(%%edi), %%cx\n\t"
      "movl 0x1c(%%esi), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "movw %%cx, 0x8(%%esi)\n\t"
      "movb 0x3ba(%%edi), %%dl\n\t"
      "movb %%dl, 0xa(%%esi)\n\t"
      "movb $1, 0xf(%%esi)\n\t"
      "movb $0, 0x6(%%esi)\n\t"
      "je .LFUN_00015520_8\n\t"
      "pushl %%eax\n\t"
      "movl 0x5ab23c, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movw 0x34(%%eax), %%cx\n\t"
      "movw 0x36(%%eax), %%dx\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "addl $8, %%esp\n\t"
      "cmpw %%dx, %%cx\n\t"
      "movw %%bx, 0x32(%%eax)\n\t"
      "movswl %%cx, %%ecx\n\t"
      "jg .LFUN_00015520_7\n\t"
      "movswl %%dx, %%ecx\n\t"
      ".LFUN_00015520_7:\n\t"
      "movb %%bl, 0x74(%%eax)\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "pushl %%ebx\n\t"
      "movw %%cx, 0x30(%%eax)\n\t"
      "movw $2, 0x38(%%eax)\n\t"
      "call *%[c300b0]\n\t"
      "pushl %%ebx\n\t"
      "call *%[c302b0]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_00015520_8:\n\t"
      "movswl 0xc(%%esi), %%eax\n\t"
      "addl $-9, %%eax\n\t"
      "cmpl $3, %%eax\n\t"
      "ja .LFUN_00015520_14\n\t"
      "jmp *.LFUN_00015520_jt(,%%eax,4)\n\t"
      ".LFUN_00015520_9:\n\t"
      "cmpl $-1, 0x1b0(%%edi)\n\t"
      "jmp .LFUN_00015520_13\n\t"
      ".LFUN_00015520_10:\n\t"
      "movb 0x1b4(%%edi), %%al\n\t"
      "jmp .LFUN_00015520_12\n\t"
      ".LFUN_00015520_11:\n\t"
      "movb 0x1b5(%%edi), %%al\n\t"
      ".LFUN_00015520_12:\n\t"
      "testb %%al, %%al\n\t"
      ".LFUN_00015520_13:\n\t"
      "jne .LFUN_00015520_14\n\t"
      "movb $1, 0xf(%%esi)\n\t"
      ".LFUN_00015520_14:\n\t"
      "movb 0x4c(%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00015520_18\n\t"
      "movb 0xf(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00015520_18\n\t"
      "orl $0xffffffff, %%ebx\n\t"
      "cmpw %%bx, 0x8(%%esi)\n\t"
      "je .LFUN_00015520_15\n\t"
      "cmpw $0, (%%esi)\n\t"
      "jne .LFUN_00015520_15\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[c14e90]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00015520_15\n\t"
      "movw %%bx, 0x8(%%esi)\n\t"
      "movb $1, 0x6(%%esi)\n\t"
      ".LFUN_00015520_15:\n\t"
      "movb 0x160(%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00015520_16\n\t"
      "movb $0, 0x6(%%esi)\n\t"
      "jmp .LFUN_00015520_17\n\t"
      ".LFUN_00015520_16:\n\t"
      "movb 0x6(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00015520_18\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "pushl $1\n\t"
      "call *%[c14c10]\n\t"
      "addl $4, %%esp\n\t"
      "cmpw $-1, 0x8(%%esi)\n\t"
      "jne .LFUN_00015520_18\n\t"
      ".LFUN_00015520_17:\n\t"
      "movb $1, 0xe(%%esi)\n\t"
      "call *%[gtime]\n\t"
      "movl %%eax, 0x398(%%edi)\n\t"
      ".LFUN_00015520_18:\n\t"
      "movw 0xc(%%esi), %%ax\n\t"
      "cmpw $9, %%ax\n\t"
      "jl .LFUN_00015520_19\n\t"
      "cmpw $0xc, %%ax\n\t"
      "jg .LFUN_00015520_19\n\t"
      "movl 0x18(%%edi), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_00015520_19\n\t"
      "pushl %%eax\n\t"
      "call *%[c1a6bc0]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00015520_19\n\t"
      "movb %%al, 0x10(%%esi)\n\t"
      ".LFUN_00015520_19:\n\t"
      "cmpw $0, 0xc(%%esi)\n\t"
      "jle .LFUN_00015520_27\n\t"
      "orl $0xffffffff, %%eax\n\t"
      "cmpw %%ax, 0x8(%%esi)\n\t"
      "je .LFUN_00015520_27\n\t"
      "movb 0xe(%%esi), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "jne .LFUN_00015520_27\n\t"
      "cmpl %%eax, 0x18(%%edi)\n\t"
      "je .LFUN_00015520_27\n\t"
      "call *%[gtime]\n\t"
      "movl %%eax, %%ebx\n\t"
      "movb 0x10(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00015520_20\n\t"
      "movl 0x14(%%esi), %%ecx\n\t"
      "addl $0x3c, %%ecx\n\t"
      "cmpl %%ebx, %%ecx\n\t"
      "jl .LFUN_00015520_27\n\t"
      ".LFUN_00015520_20:\n\t"
      "movw 0xc(%%esi), %%ax\n\t"
      "cmpw $0xc, %%ax\n\t"
      "je .LFUN_00015520_24\n\t"
      "cmpw $0xb, %%ax\n\t"
      "je .LFUN_00015520_24\n\t"
      "cmpw $9, %%ax\n\t"
      "je .LFUN_00015520_23\n\t"
      "cmpw $0xa, %%ax\n\t"
      "je .LFUN_00015520_23\n\t"
      "movl 0x1c(%%esi), %%ecx\n\t"
      "orl $0xffffffff, %%eax\n\t"
      "cmpl $-1, %%ecx\n\t"
      "je .LFUN_00015520_21\n\t"
      "movl 0x5ab23c, %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[dget]\n\t"
      "movl 0x18(%%eax), %%eax\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_00015520_21:\n\t"
      "movb 0x10(%%esi), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "pushl $0\n\t"
      "jne .LFUN_00015520_22\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "cmpw $8, 0xc(%%esi)\n\t"
      "pushl $4\n\t"
      "pushl $-1\n\t"
      "sete %%cl\n\t"
      "pushl $-1\n\t"
      "pushl %%eax\n\t"
      "movl 0x18(%%edi), %%eax\n\t"
      "pushl %%eax\n\t"
      "addl $0x1f, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c46f10]\n\t"
      "addl $0x1c, %%esp\n\t"
      "movb $1, 0x10(%%esi)\n\t"
      "jmp .LFUN_00015520_26\n\t"
      ".LFUN_00015520_22:\n\t"
      "movl 0x18(%%edi), %%edx\n\t"
      "pushl $-1\n\t"
      "pushl $-1\n\t"
      "pushl $-1\n\t"
      "pushl %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl $0x21\n\t"
      "call *%[c46f10]\n\t"
      "addl $0x1c, %%esp\n\t"
      "jmp .LFUN_00015520_26\n\t"
      ".LFUN_00015520_23:\n\t"
      "movl 0x18(%%edi), %%eax\n\t"
      "pushl $1\n\t"
      "pushl %%eax\n\t"
      "jmp .LFUN_00015520_25\n\t"
      ".LFUN_00015520_24:\n\t"
      "movl 0x18(%%edi), %%ecx\n\t"
      "pushl $2\n\t"
      "pushl %%ecx\n\t"
      ".LFUN_00015520_25:\n\t"
      "call *%[c1a74d0]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_00015520_26:\n\t"
      "movl %%ebx, 0x14(%%esi)\n\t"
      ".LFUN_00015520_27:\n\t"
      "movb 0x6(%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00015520_29\n\t"
      "movb 0x4c(%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00015520_28\n\t"
      "movb 0x6(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00015520_29\n\t"
      ".LFUN_00015520_28:\n\t"
      "cmpw $0, 0x2(%%esi)\n\t"
      "jg .LFUN_00015520_29\n\t"
      "cmpw $-1, 0x8(%%esi)\n\t"
      "jne .LFUN_00015520_29\n\t"
      "movb 0xe(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00015520_30\n\t"
      "movb 0xf(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00015520_29\n\t"
      "pushl $1\n\t"
      "pushl $0x12e\n\t"
      "pushl $0x253504\n\t"
      "pushl $0x253528\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00015520_29:\n\t"
      "movb 0xe(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00015520_30\n\t"
      "movb 0xf(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00015520_30\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "xorl %%eax, %%eax\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00015520_30:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl $1, %%eax\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_00015520_jt:\n\t"
      ".long .LFUN_00015520_9\n\t"
      ".long .LFUN_00015520_9\n\t"
      ".long .LFUN_00015520_10\n\t"
      ".long .LFUN_00015520_11\n\t"
      ".text\n\t"
      :
      : [dget] "m"(b15520_dget), [c153e0] "m"(b15520_c153e0), [assert] "m"(b15520_assert), [exitfn] "m"(b15520_exitfn), [c300b0] "m"(b15520_c300b0), [c302b0] "m"(b15520_c302b0), [c14e90] "m"(b15520_c14e90), [c14c10] "m"(b15520_c14c10), [gtime] "m"(b15520_gtime), [c1a6bc0] "m"(b15520_c1a6bc0), [c46f10] "m"(b15520_c46f10), [c1a74d0] "m"(b15520_c1a74d0)
      : "memory");
}
#else
#error "FUN_00015520: clang naked draft required"
#endif


/* FUN_00015880 (0x15880) — readable C lift from XBE leaf. */
int FUN_00015880(int actor_handle, char *state_data)
{
  char *actor;
  int *vec;

  actor = (char *)datum_get(*(void **)0x6325a4, actor_handle);
  if (state_data == 0) {
    display_assert((const char *)0x25334c, (const char *)0x253638, 0x72, 1);
    system_exit(-1);
  }
  csmemset(state_data, 0, 0x44);
  *(short *)(state_data + 0x24) = 1;
  state_data[0x14] = 1;
  vec = (int *)(actor + 0x174);
  *(int *)(state_data + 0x18) = vec[0];
  *(int *)(state_data + 0x1c) = vec[1];
  *(int *)(state_data + 0x20) = vec[2];
  *(int *)(state_data + 0x3c) = -1;
  return 1;
}




/* FUN_00015900 (0x15900) — XBE naked draft (batch 78). */
#if defined(__clang__)
static void *(*const b15900_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void (*const b15900_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b15900_exitfn)(int) = system_exit;
static void *(*const b15900_memset)(void *, int, unsigned int) = csmemset;

__attribute__((naked, noinline))
int FUN_00015900(int actor_handle __attribute__((unused)), short param_2 __attribute__((unused)), char *state_data __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl 0x6325a4, %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movl 0x10(%%ebp), %%esi\n\t"
      "addl $8, %%esp\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%eax, %%edi\n\t"
      "movl $1, %%ebx\n\t"
      "jne .LFUN_00015900_1\n\t"
      "pushl %%ebx\n\t"
      "pushl $0x86\n\t"
      "pushl $0x253638\n\t"
      "pushl $0x25334c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00015900_1:\n\t"
      "pushl $0x44\n\t"
      "pushl $0\n\t"
      "pushl %%esi\n\t"
      "call *%[memset]\n\t"
      "movb 0x160(%%edi), %%al\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00015900_3\n\t"
      "movb 0x6(%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00015900_3\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "testw %%ax, %%ax\n\t"
      "movw %%ax, (%%esi)\n\t"
      "jne .LFUN_00015900_2\n\t"
      "popl %%edi\n\t"
      "movb %%bl, 0xe(%%esi)\n\t"
      "movw %%ax, 0x24(%%esi)\n\t"
      "movl $0xffffffff, 0x3c(%%esi)\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00015900_2:\n\t"
      "movw %%bx, 0x24(%%esi)\n\t"
      "movb %%bl, 0x14(%%esi)\n\t"
      "addl $0x174, %%edi\n\t"
      "movl (%%edi), %%eax\n\t"
      "leal 0x18(%%esi), %%edx\n\t"
      "movl %%eax, (%%edx)\n\t"
      "movl 0x4(%%edi), %%ecx\n\t"
      "movl %%ecx, 0x4(%%edx)\n\t"
      "movl 0x8(%%edi), %%eax\n\t"
      "popl %%edi\n\t"
      "movl $0xffffffff, 0x3c(%%esi)\n\t"
      "movl %%eax, 0x8(%%edx)\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00015900_3:\n\t"
      "popl %%edi\n\t"
      "movw %%bx, 0x24(%%esi)\n\t"
      "movl $0xffffffff, 0x3c(%%esi)\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [dget] "m"(b15900_dget), [assert] "m"(b15900_assert), [exitfn] "m"(b15900_exitfn), [memset] "m"(b15900_memset)
      : "memory");
}
#else
#error "FUN_00015900: clang naked draft required"
#endif


/* FUN_000159d0 (0x159d0) — XBE naked draft (batch 75). */
#if defined(__clang__)
static void *(*const b159d0_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void (*const b159d0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b159d0_exitfn)(int) = system_exit;
static void *(*const b159d0_memset)(void *, int, unsigned int) = csmemset;
static void (*const b159d0_c2f910)(int actor_handle, int prop_handle) = actor_perception_find_prop_pathfinding_location;

__attribute__((naked, noinline))
char FUN_000159d0(int actor_handle __attribute__((unused)), short *state_data __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl 0x6325a4, %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movl 0xc(%%ebp), %%esi\n\t"
      "addl $8, %%esp\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%eax, %%edi\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "jne .LFUN_000159d0_1\n\t"
      "pushl $1\n\t"
      "pushl $0xac\n\t"
      "pushl $0x253638\n\t"
      "pushl $0x25334c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000159d0_1:\n\t"
      "pushl $0x44\n\t"
      "pushl $0\n\t"
      "pushl %%esi\n\t"
      "call *%[memset]\n\t"
      "addl $0xc, %%esp\n\t"
      "movw $0x78, (%%esi)\n\t"
      "movw $1, 0x24(%%esi)\n\t"
      "movb $1, 0x5(%%esi)\n\t"
      "movl $0xffffffff, 0x3c(%%esi)\n\t"
      "cmpw $4, 0x15e(%%edi)\n\t"
      "jne .LFUN_000159d0_2\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000159d0_2:\n\t"
      "movb 0x160(%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_000159d0_8\n\t"
      "movb 0x6(%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_000159d0_8\n\t"
      "movl 0x1e8(%%edi), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_000159d0_8\n\t"
      "movl 0x5ab23c, %%edx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "pushl %%edx\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl 0x1e8(%%edi), %%eax\n\t"
      "movl %%eax, 0x3c(%%esi)\n\t"
      "movw $0x78, 0x2(%%esi)\n\t"
      "movb $1, 0x40(%%esi)\n\t"
      "movswl 0x1e4(%%edi), %%eax\n\t"
      "addl $-6, %%eax\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $3, %%eax\n\t"
      "ja .LFUN_000159d0_7\n\t"
      "jmp *.LFUN_000159d0_jt(,%%eax,4)\n\t"
      ".LFUN_000159d0_3:\n\t"
      "movl $0x40000000, 0x38(%%esi)\n\t"
      "jmp .LFUN_000159d0_6\n\t"
      ".LFUN_000159d0_4:\n\t"
      "movl $0x3f800000, 0x38(%%esi)\n\t"
      "jmp .LFUN_000159d0_6\n\t"
      ".LFUN_000159d0_5:\n\t"
      "movl $0x3fc00000, 0x38(%%esi)\n\t"
      ".LFUN_000159d0_6:\n\t"
      "movl 0x1e8(%%edi), %%ecx\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c2f910]\n\t"
      "movw $2, 0x24(%%esi)\n\t"
      "leal 0xf0(%%ebx), %%eax\n\t"
      "movl (%%eax), %%edx\n\t"
      "leal 0x28(%%esi), %%ecx\n\t"
      "movl %%edx, (%%ecx)\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl %%edx, 0x4(%%ecx)\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl %%eax, 0x8(%%ecx)\n\t"
      "movl 0xec(%%ebx), %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "movl %%ecx, 0x34(%%esi)\n\t"
      ".LFUN_000159d0_7:\n\t"
      "popl %%ebx\n\t"
      ".LFUN_000159d0_8:\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_000159d0_jt:\n\t"
      ".long .LFUN_000159d0_3\n\t"
      ".long .LFUN_000159d0_4\n\t"
      ".long .LFUN_000159d0_4\n\t"
      ".long .LFUN_000159d0_5\n\t"
      ".text\n\t"
      :
      : [dget] "m"(b159d0_dget), [assert] "m"(b159d0_assert), [exitfn] "m"(b159d0_exitfn), [memset] "m"(b159d0_memset), [c2f910] "m"(b159d0_c2f910)
      : "memory");
}
#else
#error "FUN_000159d0: clang naked draft required"
#endif


/* FUN_00015b30 (0x15b30) */
void FUN_00015b30(int actor_handle)
{
  char *actor;
  actor = (char *)datum_get(actor_data, actor_handle);
  actor_perception_forget_recent_damage(actor_handle);
  *(char *)(actor + 0x98) = 0;
  if (*(char *)(actor + 0xa6) != '\0') {
    actor_perception_retreat_successful(actor_handle);
  }
}

/* actor_clear_guard_state (0x15b70) — readable C lift. */
void actor_clear_guard_state(int actor_handle)
{
  char *actor;

  actor = (char *)datum_get(*(void **)0x6325a4, actor_handle);
  if (*(char *)(actor + 0xa1)) {
    *(short *)(actor + 0x1e4) = 0;
    *(int *)(actor + 0x1e8) = -1;
  }
}

/* FUN_00015cf0 (0x15cf0) — XBE naked draft (batch 78). */
#if defined(__clang__)
static void *(*const b15cf0_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void (*const b15cf0_c15bb0)(int actor_handle /* */) = FUN_00015bb0;
static void (*const b15cf0_c3ca40)(int actor_handle, char flag) = actor_set_dormant;
static int (*const b15cf0_c3b380)(int actor_handle) = actor_target_unit_index;
static void (*const b15cf0_c46f10)(int16_t type, int unit_handle, int param3, int param4, int16_t param5, int16_t param6, int16_t param7) = FUN_00046f10;
static void (*const b15cf0_c24be0)(int actor_handle, short param_2, char param_3) = FUN_00024be0;

__attribute__((naked, noinline))
void FUN_00015cf0(int actor_handle __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl 0x6325a4, %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%esi\n\t"
      "movb 0x13(%%esi), %%al\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "addl $8, %%esp\n\t"
      "cmpb %%bl, %%al\n\t"
      "jne .LFUN_00015cf0_2\n\t"
      "cmpb %%bl, 0x484(%%esi)\n\t"
      "je .LFUN_00015cf0_2\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x9c(%%esi), %%ax\n\t"
      "cmpw %%bx, %%ax\n\t"
      "jle .LFUN_00015cf0_2\n\t"
      "decl %%eax\n\t"
      "cmpw %%bx, %%ax\n\t"
      "movw %%ax, 0x9c(%%esi)\n\t"
      "jne .LFUN_00015cf0_2\n\t"
      "cmpb %%bl, 0x160(%%esi)\n\t"
      "jne .LFUN_00015cf0_2\n\t"
      "cmpb %%bl, 0x6(%%esi)\n\t"
      "jne .LFUN_00015cf0_2\n\t"
      "cmpb %%bl, 0xa1(%%esi)\n\t"
      "je .LFUN_00015cf0_1\n\t"
      "movl %%edi, %%eax\n\t"
      "call *%[c15bb0]\n\t"
      "orl $0xffffffff, %%eax\n\t"
      "movw %%bx, 0x1e4(%%esi)\n\t"
      "movl %%eax, 0x1e8(%%esi)\n\t"
      "movb %%bl, 0xa1(%%esi)\n\t"
      "movb %%bl, 0xa3(%%esi)\n\t"
      "movl %%eax, 0xd8(%%esi)\n\t"
      ".LFUN_00015cf0_1:\n\t"
      "movb $1, 0xaa(%%esi)\n\t"
      ".LFUN_00015cf0_2:\n\t"
      "movw 0x9e(%%esi), %%ax\n\t"
      "cmpw %%bx, %%ax\n\t"
      "jle .LFUN_00015cf0_4\n\t"
      "cmpb %%bl, 0xdc(%%esi)\n\t"
      "je .LFUN_00015cf0_3\n\t"
      "cmpb %%bl, 0x484(%%esi)\n\t"
      "je .LFUN_00015cf0_4\n\t"
      ".LFUN_00015cf0_3:\n\t"
      "decl %%eax\n\t"
      "cmpw %%bx, %%ax\n\t"
      "movw %%ax, 0x9e(%%esi)\n\t"
      "jne .LFUN_00015cf0_4\n\t"
      "movl $0xffffffff, 0xd8(%%esi)\n\t"
      ".LFUN_00015cf0_4:\n\t"
      "cmpb %%bl, 0xa0(%%esi)\n\t"
      "je .LFUN_00015cf0_9\n\t"
      "cmpb %%bl, 0x484(%%esi)\n\t"
      "je .LFUN_00015cf0_9\n\t"
      "cmpb %%bl, 0xa6(%%esi)\n\t"
      "je .LFUN_00015cf0_5\n\t"
      "cmpw %%bx, 0x3a8(%%esi)\n\t"
      "setg %%al\n\t"
      "movb %%al, 0xa6(%%esi)\n\t"
      "cmpb %%bl, %%al\n\t"
      "jmp .LFUN_00015cf0_6\n\t"
      ".LFUN_00015cf0_5:\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0xa8(%%esi), %%ax\n\t"
      "cmpw %%bx, %%ax\n\t"
      "jle .LFUN_00015cf0_9\n\t"
      "decl %%eax\n\t"
      "movw %%ax, 0xa8(%%esi)\n\t"
      "cmpw %%bx, %%ax\n\t"
      ".LFUN_00015cf0_6:\n\t"
      "sete %%al\n\t"
      "cmpb %%bl, %%al\n\t"
      "je .LFUN_00015cf0_9\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "call *%[c3ca40]\n\t"
      "addl $8, %%esp\n\t"
      "movb %%bl, 0xa4(%%esi)\n\t"
      "movb %%bl, 0xa5(%%esi)\n\t"
      "movb %%bl, 0xa6(%%esi)\n\t"
      "movw %%bx, 0xa8(%%esi)\n\t"
      "cmpw $2, 0x6e(%%esi)\n\t"
      "jl .LFUN_00015cf0_7\n\t"
      "cmpl $-1, 0x18(%%esi)\n\t"
      "je .LFUN_00015cf0_7\n\t"
      "pushl %%ebx\n\t"
      "pushl $-1\n\t"
      "pushl $-1\n\t"
      "pushl $-1\n\t"
      "pushl %%edi\n\t"
      "call *%[c3b380]\n\t"
      "movl 0x18(%%esi), %%ecx\n\t"
      "addl $4, %%esp\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x23\n\t"
      "call *%[c46f10]\n\t"
      "addl $0x1c, %%esp\n\t"
      ".LFUN_00015cf0_7:\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0xc4(%%esi), %%dx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "call *%[c24be0]\n\t"
      "orl $0xffffffff, %%eax\n\t"
      "movw %%ax, 0x3b8(%%esi)\n\t"
      "movw %%ax, 0xc4(%%esi)\n\t"
      "movb 0x160(%%esi), %%al\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpb %%bl, %%al\n\t"
      "je .LFUN_00015cf0_8\n\t"
      "popl %%edi\n\t"
      "movw $1, 0xc0(%%esi)\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00015cf0_8:\n\t"
      "movw %%bx, 0xc0(%%esi)\n\t"
      "movb $1, 0xaa(%%esi)\n\t"
      ".LFUN_00015cf0_9:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [dget] "m"(b15cf0_dget), [c15bb0] "m"(b15cf0_c15bb0), [c3ca40] "m"(b15cf0_c3ca40), [c3b380] "m"(b15cf0_c3b380), [c46f10] "m"(b15cf0_c46f10), [c24be0] "m"(b15cf0_c24be0)
      : "memory");
}
#else
#error "FUN_00015cf0: clang naked draft required"
#endif


/* actor_reset_action_state (0x15eb0) — readable C lift. */
void actor_reset_action_state(int actor_handle)
{
  unsigned char *actor;
  int16_t state;

  actor = (unsigned char *)datum_get(*(void **)0x6325a4, actor_handle);
  if (actor[0xa4] != 0 && *(int16_t *)(actor + 0xc0) == 3) {
    actor[0xa4] = 0;
    *(int16_t *)(actor + 0xa8) = 0;
    actor[0xa6] = 0;
  }
  state = *(int16_t *)(actor + 0xc0);
  if (state == 3 || (state == 1 && actor[0x160] == 0)) {
    *(int16_t *)(actor + 0xc0) = 0;
    *(int16_t *)(actor + 0xc4) = (int16_t)0xffff;
    actor[0xaa] = 1;
  }
}



/* actor_clear_flee_target (0x15f30) — readable C lift. */
void actor_clear_flee_target(int actor_handle)
{
  char *actor;

  actor = (char *)datum_get(*(void **)0x6325a4, actor_handle) + 0x9c;
  if (*(short *)(actor + 0x24) == 2) {
    *(int *)(actor + 0x34) = -1;
  }
}

/* FUN_00015f60 (0x15f60) — readable C lift from XBE leaf. */
void FUN_00015f60(int actor_handle, int *param_2)
{
  char *actor;
  char *look;
  int *src;

  actor = (char *)datum_get(*(void **)0x6325a4, actor_handle);
  look = actor + 0x9c;
  if (actor[0xa4] == 0) {
    src = *(int **)0x2ee700;
  } else if (look[0xa] != 0) {
    src = *(int **)0x2ee704;
    param_2[0] = src[0];
    param_2[1] = src[1];
    param_2[2] = src[2];
    param_2[3] = src[3];
    return;
  } else if (look[9] != 0) {
    src = *(int **)0x2ee6e8;
    param_2[0] = src[0];
    param_2[1] = src[1];
    param_2[2] = src[2];
    param_2[3] = src[3];
    return;
  } else {
    src = *(int **)0x2ee6f4;
  }
  param_2[0] = src[0];
  param_2[1] = src[1];
  param_2[2] = src[2];
  param_2[3] = src[3];
}




/* actor_replace_prop_handle (0x16000) — readable C lift. */
void actor_replace_prop_handle(int actor_handle, int old_handle, int new_handle)
{
  char *actor = (char *)datum_get(*(void **)0x6325a4, actor_handle);
  char *meta = actor + 0x9c;
  if (*(int *)(actor + 0xd8) == old_handle) {
    *(int *)(meta + 0x3c) = new_handle;
  }
  if (*(int *)(meta + 0x10) == old_handle) {
    *(int *)(meta + 0x10) = new_handle;
    if (new_handle == -1) {
      meta[0xf] = 0;
    }
  }
}

/* FUN_00016050 (0x16050) — XBE naked draft (batch 75). */
#if defined(__clang__)
static void *(*const b16050_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void (*const b16050_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b16050_exitfn)(int) = system_exit;
static void *(*const b16050_memset)(void *, int, unsigned int) = csmemset;
static char (*const b16050_c25a00)(int actor_handle, float *position, int surface_index, int group_mask) = actor_has_accessible_firing_position;
static float (*const b16050_norm)(float *) = normalize3d;

__attribute__((naked, noinline))
int FUN_00016050(int actor_handle __attribute__((unused)), short *param_2 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl 0x6325a4, %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movl 0xc(%%ebp), %%esi\n\t"
      "addl $8, %%esp\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%eax, %%edi\n\t"
      "jne .LFUN_00016050_1\n\t"
      "pushl $1\n\t"
      "pushl $0x20\n\t"
      "pushl $0x253638\n\t"
      "pushl $0x25334c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00016050_1:\n\t"
      "pushl %%ebx\n\t"
      "pushl $0x44\n\t"
      "pushl $0\n\t"
      "pushl %%esi\n\t"
      "call *%[memset]\n\t"
      "movw 0x33c(%%edi), %%dx\n\t"
      "movw %%dx, (%%esi)\n\t"
      "movb 0x160(%%edi), %%al\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00016050_5\n\t"
      "movb 0x6(%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00016050_5\n\t"
      "cmpw $0, 0x312(%%edi)\n\t"
      "jne .LFUN_00016050_2\n\t"
      "pushl $1\n\t"
      "pushl $0x2d\n\t"
      "pushl $0x253638\n\t"
      "pushl $0x2536a8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00016050_2:\n\t"
      "movb 0x314(%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00016050_3\n\t"
      "movl 0x324(%%edi), %%eax\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "pushl $1\n\t"
      "pushl %%eax\n\t"
      "leal 0x318(%%edi), %%ebx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c25a00]\n\t"
      "addl $0x10, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00016050_3\n\t"
      "movw $2, 0x24(%%esi)\n\t"
      "movl (%%ebx), %%eax\n\t"
      "leal 0x28(%%esi), %%edx\n\t"
      "movl %%eax, (%%edx)\n\t"
      "movl 0x4(%%ebx), %%ecx\n\t"
      "movl %%ecx, 0x4(%%edx)\n\t"
      "movl 0x8(%%ebx), %%eax\n\t"
      "movl %%eax, 0x8(%%edx)\n\t"
      "movl 0x324(%%edi), %%ecx\n\t"
      "movl %%ecx, 0x34(%%esi)\n\t"
      "movl 0x328(%%edi), %%edx\n\t"
      "movl %%edx, 0x38(%%esi)\n\t"
      "jmp .LFUN_00016050_6\n\t"
      ".LFUN_00016050_3:\n\t"
      "cmpw $0, (%%esi)\n\t"
      "jle .LFUN_00016050_4\n\t"
      "movw $1, 0x24(%%esi)\n\t"
      "movb 0x32c(%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "movb %%al, 0x14(%%esi)\n\t"
      "movb $0, 0x15(%%esi)\n\t"
      "je .LFUN_00016050_6\n\t"
      "leal 0x18(%%esi), %%eax\n\t"
      "leal 0x330(%%edi), %%ecx\n\t"
      "movl (%%ecx), %%ebx\n\t"
      "movl %%eax, %%edx\n\t"
      "movl %%ebx, (%%edx)\n\t"
      "movl 0x4(%%ecx), %%ebx\n\t"
      "movl %%ebx, 0x4(%%edx)\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "pushl %%eax\n\t"
      "movl %%ecx, 0x8(%%edx)\n\t"
      "call *%[norm]\n\t"
      "fcomps 0x2533c0\n\t"
      "addl $4, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .LFUN_00016050_6\n\t"
      "movb $0, 0x14(%%esi)\n\t"
      "jmp .LFUN_00016050_6\n\t"
      ".LFUN_00016050_4:\n\t"
      "movw $0, 0x24(%%esi)\n\t"
      "movb $1, 0xe(%%esi)\n\t"
      "jmp .LFUN_00016050_6\n\t"
      ".LFUN_00016050_5:\n\t"
      "movw $1, 0x24(%%esi)\n\t"
      ".LFUN_00016050_6:\n\t"
      "cmpw $2, 0x312(%%edi)\n\t"
      "popl %%ebx\n\t"
      "jne .LFUN_00016050_8\n\t"
      "cmpl $-1, 0x340(%%edi)\n\t"
      "jne .LFUN_00016050_7\n\t"
      "pushl $1\n\t"
      "pushl $0x5a\n\t"
      "pushl $0x253638\n\t"
      "pushl $0x253674\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00016050_7:\n\t"
      "movb $1, 0xf(%%esi)\n\t"
      "movl 0x340(%%edi), %%edx\n\t"
      "movl %%edx, 0x10(%%esi)\n\t"
      ".LFUN_00016050_8:\n\t"
      "movl 0x340(%%edi), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "movl %%eax, 0x3c(%%esi)\n\t"
      "je .LFUN_00016050_9\n\t"
      "movw 0x344(%%edi), %%ax\n\t"
      "movw %%ax, 0x2(%%esi)\n\t"
      "movb 0x348(%%edi), %%cl\n\t"
      "movb %%cl, 0x40(%%esi)\n\t"
      ".LFUN_00016050_9:\n\t"
      "popl %%edi\n\t"
      "movb $1, %%al\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [dget] "m"(b16050_dget), [assert] "m"(b16050_assert), [exitfn] "m"(b16050_exitfn), [memset] "m"(b16050_memset), [c25a00] "m"(b16050_c25a00), [norm] "m"(b16050_norm)
      : "memory");
}
#else
#error "FUN_00016050: clang naked draft required"
#endif


/* FUN_00016210 (0x16210) — XBE naked draft (batch 69). */
#if defined(__clang__)
static void *(*const b16210_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void *(*const b16210_tag)(int, int) = tag_get;
static void (*const b16210_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b16210_exitfn)(int) = system_exit;
static void *(*const b16210_memset)(void *, int, unsigned int) = csmemset;
static int *(*const b16210_gseed)(void) = get_global_random_seed_address;
static float (*const b16210_rrange)(int *, float, float) = random_real_range;
static void (*const b16210_ftol)(void) = FUN_001d9068;
static float (*const b16210_norm)(float *) = normalize3d;

__attribute__((naked, noinline))
char FUN_00016210(int actor_handle __attribute__((unused)), int param_2 __attribute__((unused)), short *param_3 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl 0x6325a4, %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%edi\n\t"
      "movl 0x58(%%edi), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x61637472\n\t"
      "call *%[tag]\n\t"
      "movl 0x10(%%ebp), %%esi\n\t"
      "addl $0x10, %%esp\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "jne .LFUN_00016210_1\n\t"
      "pushl $1\n\t"
      "pushl $0xed\n\t"
      "pushl $0x253638\n\t"
      "pushl $0x25334c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00016210_1:\n\t"
      "pushl $0x44\n\t"
      "pushl $0\n\t"
      "pushl %%esi\n\t"
      "call *%[memset]\n\t"
      "movb 0x160(%%edi), %%al\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00016210_8\n\t"
      "movb 0x6(%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00016210_8\n\t"
      "movl 0xc(%%ebp), %%ebx\n\t"
      "movw $0, (%%esi)\n\t"
      "movb $1, 0x8(%%esi)\n\t"
      "movw $0, 0xc(%%esi)\n\t"
      "cmpw $0, 0xc(%%ebx)\n\t"
      "setg %%al\n\t"
      "movb %%al, 0x9(%%esi)\n\t"
      "cmpw $0, 0x3a8(%%edi)\n\t"
      "jle .LFUN_00016210_2\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00016210_2\n\t"
      "movl $1, %%eax\n\t"
      "jmp .LFUN_00016210_3\n\t"
      ".LFUN_00016210_2:\n\t"
      "xorl %%eax, %%eax\n\t"
      ".LFUN_00016210_3:\n\t"
      "testb %%al, %%al\n\t"
      "movb %%al, 0xa(%%esi)\n\t"
      "jne .LFUN_00016210_6\n\t"
      "movb 0x9(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "je .LFUN_00016210_4\n\t"
      "movl 0x29c(%%eax), %%ecx\n\t"
      "movl 0x298(%%eax), %%edx\n\t"
      "movl %%ecx, %%eax\n\t"
      "movl %%ecx, 0x10(%%ebp)\n\t"
      "pushl %%eax\n\t"
      "movl %%edx, %%ecx\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      "pushl %%ecx\n\t"
      "jmp .LFUN_00016210_5\n\t"
      ".LFUN_00016210_4:\n\t"
      "movl 0x2d4(%%eax), %%edx\n\t"
      "movl 0x2d0(%%eax), %%eax\n\t"
      "movl %%edx, %%ecx\n\t"
      "movl %%edx, 0x10(%%ebp)\n\t"
      "pushl %%ecx\n\t"
      "movl %%eax, %%edx\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "pushl %%edx\n\t"
      ".LFUN_00016210_5:\n\t"
      "call *%[gseed]\n\t"
      "pushl %%eax\n\t"
      "call *%[rrange]\n\t"
      "fmuls 0x253394\n\t"
      "addl $0xc, %%esp\n\t"
      "call *%[ftol]\n\t"
      "movw %%ax, 0xc(%%esi)\n\t"
      ".LFUN_00016210_6:\n\t"
      "cmpw $-1, 0x8(%%ebx)\n\t"
      "jne .LFUN_00016210_7\n\t"
      "popl %%edi\n\t"
      "movb $1, 0xe(%%esi)\n\t"
      "movw $0, 0x24(%%esi)\n\t"
      "movl $0xffffffff, 0x3c(%%esi)\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00016210_7:\n\t"
      "movb $0, 0xe(%%esi)\n\t"
      "movw $3, 0x24(%%esi)\n\t"
      "movw 0x8(%%ebx), %%ax\n\t"
      "movw %%ax, 0x28(%%esi)\n\t"
      "movb 0x20(%%ebx), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00016210_9\n\t"
      "movb $1, 0x14(%%esi)\n\t"
      "movb $1, 0x15(%%esi)\n\t"
      "flds 0x24(%%ebx)\n\t"
      "fsubs 0x12c(%%edi)\n\t"
      "leal 0x18(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "fstps (%%eax)\n\t"
      "flds 0x28(%%ebx)\n\t"
      "fsubs 0x130(%%edi)\n\t"
      "fstps 0x4(%%eax)\n\t"
      "flds 0x2c(%%ebx)\n\t"
      "fsubs 0x134(%%edi)\n\t"
      "fstps 0x8(%%eax)\n\t"
      "call *%[norm]\n\t"
      "fcomps 0x2533c0\n\t"
      "addl $4, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .LFUN_00016210_9\n\t"
      "popl %%edi\n\t"
      "movb $0, 0x14(%%esi)\n\t"
      "movl $0xffffffff, 0x3c(%%esi)\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00016210_8:\n\t"
      "movw $1, 0x24(%%esi)\n\t"
      ".LFUN_00016210_9:\n\t"
      "popl %%edi\n\t"
      "movl $0xffffffff, 0x3c(%%esi)\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [dget] "m"(b16210_dget), [tag] "m"(b16210_tag), [assert] "m"(b16210_assert), [exitfn] "m"(b16210_exitfn), [memset] "m"(b16210_memset), [gseed] "m"(b16210_gseed), [rrange] "m"(b16210_rrange), [ftol] "m"(b16210_ftol), [norm] "m"(b16210_norm)
      : "memory");
}
#else
#error "FUN_00016210: clang naked draft required"
#endif


/* FUN_000163d0 (0x163d0) — Firing-position combat state evaluator.
 *
 * Evaluates the actor's firing-position combat state and advances the
 * state machine. Three early-exit conditions (swarm, field_160, reset).
 * Main path: if field_4c is active and field_aa is flagged, runs
 * the firing-position evaluation pipeline (FUN_00024be0, actor_get_firing_position_group,
 * FUN_00025c10, FUN_000272d0), then selects a randomized delay timer
 * from the actor tag's min/max range, scaled by 30.0 Hz.
 *
 * Confirmed: cdecl, single stack arg (actor_handle).
 * Confirmed: _chkstk with 0x14748 (83784 bytes) at 0x163d3/0x163d8.
 * Confirmed: datum_get(actor_data=DAT_006325a4, actor_handle) at
 * 0x163e4/0x163e9. Confirmed: tag_get('actr', actor->field_58) at
 * 0x163f0/0x163f9. Confirmed: three early-return paths for
 * swarm/field_160/reset at 0x16407/0x16422/0x16443. Confirmed: main evaluation
 * pipeline: FUN_00024be0 at 0x1649b, csmemset(0x670) at 0x164b1, actor_get_firing_position_group
 * at 0x164c4, FUN_00025c10 at 0x164f1, FUN_000272d0 at 0x1650b. Confirmed:
 * random timer: random_real_range(seed, tag_min, tag_max) at 0x16563, FMUL
 * [0x253394]=30.0f at 0x16568, _ftol2 at 0x16571, store to actor->field_9c at
 * 0x16576. Inferred: actor+0xc0 = firing-position action state (int16_t).
 *   actor+0xc4 = firing-position target (int16_t).
 *   actor+0x9c = combat timer (int16_t). */
unsigned int FUN_000163d0(int actor_handle)
{
  char *actor;
  char *tag;
  /* Stack (per original/MSVC): the `static` clang workaround for the broken
     _chkstk (bare-ret) is obsolete now that _chkstk reserves the frame, and
     `static` shared these buffers across actors -> re-entrancy aliasing. */
  char large_buf[0x670];
  char huge_buf[0x1474c];
  short result;
  int seed_ret;
  float timer;

  actor = (char *)datum_get(actor_data, actor_handle);
  tag = (char *)tag_get(0x61637472, *(int *)(actor + 0x58));

  if (*(char *)(actor + 0x6) != '\0') {
    *(short *)(actor + 0xc0) = 1;
    return 0;
  }

  if (*(char *)(actor + 0x160) != '\0') {
    *(short *)(actor + 0xc0) = 1;
    *(char *)(actor + 0xaa) = 1;
    return 0;
  }

  if (*(short *)(actor + 0xc0) == 3 && *(short *)(actor + 0x3b8) == -1) {
    *(short *)(actor + 0xc0) = 0;
    *(char *)(actor + 0xaa) = 1;
  }

  if (*(char *)(actor + 0x4c) != '\0' && *(char *)(actor + 0xaa) != '\0') {
    short saved_3b8;
    int ret_24a60;
    int local_10;
    int local_c;
    int local_50[15]; /* FUN_00025c10 memcpy's 0xf*4 = 60 bytes (0x3c) here;
                       * original reserves [ebp-0x4c]..[ebp-0x10] = 0x3c bytes.
                       * Was [12] (48 bytes) -> 12-byte stack overflow. */
    int ret_25c10;

    if (*(short *)(actor + 0xc0) == 3 &&
        (saved_3b8 = *(short *)(actor + 0x3b8)) != -1) {
      FUN_00024be0(actor_handle, (int)saved_3b8, 0);
    }

    csmemset(large_buf, 0, 0x670);
    *(short *)(large_buf + 4) = 4;
    ret_24a60 = actor_get_firing_position_group(actor_handle, 4, 0);
    *(int *)large_buf = ret_24a60;
    large_buf[0x19] = 1;

    ret_25c10 = (int)FUN_00025c10(actor_handle, large_buf, local_50, &local_c,
                                  huge_buf, &local_10);
    result = FUN_000272d0(actor_handle, (short)ret_25c10, local_50, local_c,
                          (unsigned int)(int)huge_buf, (char)local_10);

    *(char *)(actor + 0xaa) = 0;
    *(char *)(actor + 0xb0) = 0;

    if (result == -1) {
      *(short *)(actor + 0xc0) = 1;
    } else {
      *(short *)(actor + 0xc0) = 3;
      *(short *)(actor + 0xc4) = result;
    }

    seed_ret = (int)get_global_random_seed_address();
    timer = random_real_range((int *)seed_ret, *(float *)(tag + 0x3b8),
                              *(float *)(tag + 0x3bc));
    return (unsigned int)((int)(timer * *(float *)0x253394) & 0xffffff00);
  }

  return 0;
}

/* FUN_00016590 (0x16590) — XBE naked draft (batch 69). */
#if defined(__clang__)
static void *(*const b16590_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void *(*const b16590_tag)(int, int) = tag_get;
static void (*const b16590_c2f1a0)(int actor_handle) = FUN_0002f1a0;
static float (*const b16590_c121a0)(const float *a, const float *b) = distance_squared3d;
static char (*const b16590_c2d720)(int actor_handle, float *destination, int param_3, int param_4) = actor_move_to_point;
static char (*const b16590_c2d900)(int actor_handle, int16_t param_2, void *param_3) = actor_move_to_firing_position;
static void (*const b16590_c24be0)(int actor_handle, short param_2, char param_3) = FUN_00024be0;
static void (*const b16590_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b16590_exitfn)(int) = system_exit;
static void (*const b16590_c369c0)(int actor_handle, short priority, int value) = FUN_000369c0;
static void (*const b16590_c46f10)(int16_t type, int unit_handle, int param3, int param4, int16_t param5, int16_t param6, int16_t param7) = FUN_00046f10;
static void (*const b16590_c15bb0)(int actor_handle /* */) = FUN_00015bb0;

__attribute__((naked, noinline))
void FUN_00016590(int actor_handle __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "movl 0x6325a4, %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x58(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x61637472\n\t"
      "call *%[tag]\n\t"
      "movb (%%eax), %%cl\n\t"
      "addl $0x10, %%esp\n\t"
      "testb $0x40, %%cl\n\t"
      "je .LFUN_00016590_1\n\t"
      "cmpw $0, 0x6e(%%esi)\n\t"
      "jne .LFUN_00016590_1\n\t"
      "movb $1, 0x426(%%esi)\n\t"
      "movb $1, 0x427(%%esi)\n\t"
      "jmp .LFUN_00016590_6\n\t"
      ".LFUN_00016590_1:\n\t"
      "movb $0, 0x427(%%esi)\n\t"
      "movb 0xa4(%%esi), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "je .LFUN_00016590_3\n\t"
      "movb 0xa6(%%esi), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "je .LFUN_00016590_2\n\t"
      "movl (%%eax), %%edx\n\t"
      "shrl $0x17, %%edx\n\t"
      "andb $1, %%dl\n\t"
      "movb %%dl, 0x426(%%esi)\n\t"
      "jmp .LFUN_00016590_6\n\t"
      ".LFUN_00016590_2:\n\t"
      "movb $1, 0x426(%%esi)\n\t"
      "jmp .LFUN_00016590_6\n\t"
      ".LFUN_00016590_3:\n\t"
      "cmpb $0, (%%eax)\n\t"
      "jns .LFUN_00016590_4\n\t"
      "cmpw $0, 0x6e(%%esi)\n\t"
      "jle .LFUN_00016590_4\n\t"
      "movl $1, %%eax\n\t"
      "jmp .LFUN_00016590_5\n\t"
      ".LFUN_00016590_4:\n\t"
      "xorl %%eax, %%eax\n\t"
      ".LFUN_00016590_5:\n\t"
      "movb %%al, 0x426(%%esi)\n\t"
      ".LFUN_00016590_6:\n\t"
      "movb 0x4c(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "movb $0, 0x428(%%esi)\n\t"
      "movb $0, 0x424(%%esi)\n\t"
      "movb $0, 0x425(%%esi)\n\t"
      "je .LFUN_00016590_19\n\t"
      "movb 0x6(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00016590_19\n\t"
      "movswl 0xc0(%%esi), %%eax\n\t"
      "pushl %%ebx\n\t"
      "xorb %%bl, %%bl\n\t"
      "cmpl $3, %%eax\n\t"
      "ja .LFUN_00016590_15\n\t"
      "jmp *.LFUN_00016590_jt(,%%eax,4)\n\t"
      ".LFUN_00016590_7:\n\t"
      "pushl %%edi\n\t"
      "call *%[c2f1a0]\n\t"
      "addl $4, %%esp\n\t"
      "movb $1, %%bl\n\t"
      "jmp .LFUN_00016590_16\n\t"
      ".LFUN_00016590_8:\n\t"
      "leal 0xc4(%%esi), %%ebx\n\t"
      "leal 0x12c(%%esi), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "call *%[c121a0]\n\t"
      "fsts -0x4(%%ebp)\n\t"
      "flds 0xd4(%%esi)\n\t"
      "addl $8, %%esp\n\t"
      "fld %%st(0)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fxch %%st(1)\n\t"
      "fxch %%st(2)\n\t"
      "fcompp\n\t"
      "fnstsw %%ax\n\t"
      "fstp %%st(0)\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00016590_9\n\t"
      "pushl %%edi\n\t"
      "call *%[c2f1a0]\n\t"
      "addl $4, %%esp\n\t"
      "jmp .LFUN_00016590_10\n\t"
      ".LFUN_00016590_9:\n\t"
      "movl 0xd0(%%esi), %%ecx\n\t"
      "pushl $-1\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "call *%[c2d720]\n\t"
      "addl $0x10, %%esp\n\t"
      ".LFUN_00016590_10:\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fcomps 0x2536cc\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00016590_14\n\t"
      ".LFUN_00016590_11:\n\t"
      "movb $1, %%bl\n\t"
      "jmp .LFUN_00016590_16\n\t"
      ".LFUN_00016590_12:\n\t"
      "movw 0xc4(%%esi), %%ax\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .LFUN_00016590_13\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw %%ax, %%dx\n\t"
      "pushl $0\n\t"
      "movw %%ax, 0x3b8(%%esi)\n\t"
      "movb $0, 0x3ba(%%esi)\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "call *%[c2d900]\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00016590_13\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0xc4(%%esi), %%ax\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "call *%[c24be0]\n\t"
      "addl $0xc, %%esp\n\t"
      "movw $0xffff, 0x3b8(%%esi)\n\t"
      ".LFUN_00016590_13:\n\t"
      "movb 0x4a8(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00016590_11\n\t"
      "leal 0x12c(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal 0x4ac(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c121a0]\n\t"
      "fcomps 0x2536cc\n\t"
      "addl $8, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .LFUN_00016590_11\n\t"
      ".LFUN_00016590_14:\n\t"
      "xorb %%bl, %%bl\n\t"
      "jmp .LFUN_00016590_16\n\t"
      ".LFUN_00016590_15:\n\t"
      "pushl $1\n\t"
      "pushl $0x2a9\n\t"
      "pushl $0x253638\n\t"
      "pushl $0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00016590_16:\n\t"
      "testb %%bl, %%bl\n\t"
      "movb $1, 0xa0(%%esi)\n\t"
      "je .LFUN_00016590_18\n\t"
      "movb 0xab(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00016590_17\n\t"
      "movl 0xac(%%esi), %%eax\n\t"
      "movl 0x5ab23c, %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "pushl $0x258\n\t"
      "pushl $2\n\t"
      "pushl %%edi\n\t"
      "movl %%eax, %%ebx\n\t"
      "movb $0, 0xab(%%esi)\n\t"
      "movl $0xffffffff, 0xac(%%esi)\n\t"
      "call *%[c369c0]\n\t"
      "movl 0x18(%%ebx), %%edx\n\t"
      "movl 0x18(%%esi), %%eax\n\t"
      "pushl $0\n\t"
      "pushl $2\n\t"
      "pushl $-1\n\t"
      "pushl $-1\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl $7\n\t"
      "call *%[c46f10]\n\t"
      "addl $0x30, %%esp\n\t"
      ".LFUN_00016590_17:\n\t"
      "movb 0xa1(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00016590_18\n\t"
      "movl %%edi, %%eax\n\t"
      "call *%[c15bb0]\n\t"
      "cmpw $9, 0x1e4(%%esi)\n\t"
      "jne .LFUN_00016590_18\n\t"
      "cmpw $2, 0xc0(%%esi)\n\t"
      "jne .LFUN_00016590_18\n\t"
      "movb $1, 0xa3(%%esi)\n\t"
      ".LFUN_00016590_18:\n\t"
      "popl %%ebx\n\t"
      ".LFUN_00016590_19:\n\t"
      "movb 0xa3(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "movl $4, %%ecx\n\t"
      "je .LFUN_00016590_20\n\t"
      "movw $7, 0x3e8(%%esi)\n\t"
      "movw $2, 0x3ec(%%esi)\n\t"
      "movb $1, 0x454(%%esi)\n\t"
      "movb $1, 0x45d(%%esi)\n\t"
      "movl 0x31fc44, %%eax\n\t"
      "flds (%%eax)\n\t"
      "fmuls 0x2533e8\n\t"
      "fadds 0xc4(%%esi)\n\t"
      "fstps 0x460(%%esi)\n\t"
      "flds 0x4(%%eax)\n\t"
      "fmuls 0x2533e8\n\t"
      "fadds 0xc8(%%esi)\n\t"
      "fstps 0x464(%%esi)\n\t"
      "flds 0x8(%%eax)\n\t"
      "fmuls 0x2533e8\n\t"
      "fadds 0xcc(%%esi)\n\t"
      "fstps 0x468(%%esi)\n\t"
      "jmp .LFUN_00016590_24\n\t"
      ".LFUN_00016590_20:\n\t"
      "cmpl $-1, 0xd8(%%esi)\n\t"
      "je .LFUN_00016590_21\n\t"
      "movw $5, 0x3e8(%%esi)\n\t"
      "movw $1, 0x3ec(%%esi)\n\t"
      "movl 0xd8(%%esi), %%edx\n\t"
      "movl %%edx, 0x3f0(%%esi)\n\t"
      "jmp .LFUN_00016590_24\n\t"
      ".LFUN_00016590_21:\n\t"
      "movb 0xb0(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00016590_22\n\t"
      "movb 0xb1(%%esi), %%dl\n\t"
      "xorl %%eax, %%eax\n\t"
      "testb %%dl, %%dl\n\t"
      "setne %%al\n\t"
      "movw %%cx, 0x3ec(%%esi)\n\t"
      "leal 0xb4(%%esi), %%edx\n\t"
      "leal 0x3(%%eax,%%eax,1), %%eax\n\t"
      "movw %%ax, 0x3e8(%%esi)\n\t"
      "movl (%%edx), %%edi\n\t"
      "leal 0x3f0(%%esi), %%eax\n\t"
      "movl %%edi, (%%eax)\n\t"
      "movl 0x4(%%edx), %%edi\n\t"
      "movl %%edi, 0x4(%%eax)\n\t"
      "movl 0x8(%%edx), %%edx\n\t"
      "movl %%edx, 0x8(%%eax)\n\t"
      "jmp .LFUN_00016590_24\n\t"
      ".LFUN_00016590_22:\n\t"
      "cmpw $0, 0x6e(%%esi)\n\t"
      "jle .LFUN_00016590_23\n\t"
      "movl 0x270(%%esi), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_00016590_23\n\t"
      "movw $3, 0x3e8(%%esi)\n\t"
      "movw $1, 0x3ec(%%esi)\n\t"
      "movl %%eax, 0x3f0(%%esi)\n\t"
      "jmp .LFUN_00016590_24\n\t"
      ".LFUN_00016590_23:\n\t"
      "movw $0, 0x3e8(%%esi)\n\t"
      ".LFUN_00016590_24:\n\t"
      "xorl %%eax, %%eax\n\t"
      "cmpw %%cx, 0x6e(%%esi)\n\t"
      "popl %%edi\n\t"
      "setge %%al\n\t"
      "leal 0x2(%%eax,%%eax,1), %%eax\n\t"
      "movw %%ax, 0x3fc(%%esi)\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_00016590_jt:\n\t"
      ".long .LFUN_00016590_7\n\t"
      ".long .LFUN_00016590_7\n\t"
      ".long .LFUN_00016590_8\n\t"
      ".long .LFUN_00016590_12\n\t"
      ".text\n\t"
      :
      : [dget] "m"(b16590_dget), [tag] "m"(b16590_tag), [c2f1a0] "m"(b16590_c2f1a0), [c121a0] "m"(b16590_c121a0), [c2d720] "m"(b16590_c2d720), [c2d900] "m"(b16590_c2d900), [c24be0] "m"(b16590_c24be0), [assert] "m"(b16590_assert), [exitfn] "m"(b16590_exitfn), [c369c0] "m"(b16590_c369c0), [c46f10] "m"(b16590_c46f10), [c15bb0] "m"(b16590_c15bb0)
      : "memory");
}
#else
#error "FUN_00016590: clang naked draft required"
#endif


/* FUN_00016960 (0x16960)
 * Three-way float comparator: -1 if *a < *b, 1 if *a > *b, 0 if equal.
 *
 * Confirmed: FLD [ECX] / FCOMP [EDX] for both comparisons (param_1=ECX,
 * param_2=EDX). First: TEST AH,0x5; JP (jump if not-less). Second: TEST
 * AH,0x41; JNZ (jump if equal-or-less → return 0). Fall-through → return 1.
 * Confirmed: MOV EAX,0xffffffff / MOV EAX,0x1 / XOR EAX,EAX returns. */
int FUN_00016960(float *param_1, float *param_2)
{
  if (*param_1 < *param_2) {
    return -1;
  }
  if (*param_1 > *param_2) {
    return 1;
  }
  return 0;
}

/* FUN_000169a0 (0x169a0) — XBE naked draft (batch 69). */
#if defined(__clang__)
static void *(*const b169a0_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static scenario_t * (*const b169a0_c18e380)(void) = global_scenario_get;
static void *(*const b169a0_elem)(void *, int, int) = tag_block_get_element;
static void (*const b169a0_c2f1a0)(int actor_handle) = FUN_0002f1a0;
static char * (*const b169a0_c49ac0)(int actor_handle, int object_handle, char with_actor, char *buf, int buf_size) = ai_debug_describe_actor;
static void (*const b169a0_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;
static void *(*const b169a0_tryget)(int, int) = object_try_and_get_and_verify_type;
static void (*const b169a0_c27870)(int actor_handle) = FUN_00027870;

__attribute__((naked, noinline))
void FUN_000169a0(int actor_handle __attribute__((unused)), int unit_handle __attribute__((unused)), short scenario_idx __attribute__((unused)), int param_4 __attribute__((unused)), char *out_index __attribute__((unused)), void *state_ptr __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x200, %%esp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl 0x6325a4, %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movswl 0x10(%%ebp), %%edx\n\t"
      "addl $8, %%esp\n\t"
      "pushl $0x60\n\t"
      "pushl %%edx\n\t"
      "movl %%eax, %%ebx\n\t"
      "call *%[c18e380]\n\t"
      "addl $0x438, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movzbl (%%esi), %%ecx\n\t"
      "movl %%eax, %%edi\n\t"
      "movl 0x30(%%edi), %%edx\n\t"
      "leal 0x30(%%edi), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl %%edx, %%ecx\n\t"
      "jge .LFUN_000169a0_13\n\t"
      "pushl $0x20\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movswl (%%eax), %%ecx\n\t"
      "addl $0xc, %%esp\n\t"
      "decl %%ecx\n\t"
      "cmpl $0x18, %%ecx\n\t"
      "ja .LFUN_000169a0_13\n\t"
      "movzbl 0x16bac(%%ecx), %%ecx\n\t"
      "jmp *.LFUN_000169a0_jt(,%%ecx,4)\n\t"
      ".LFUN_000169a0_1:\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "cmpl 0x18(%%ebx), %%edx\n\t"
      "jne .LFUN_000169a0_2\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c2f1a0]\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_000169a0_2:\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "je .LFUN_000169a0_13\n\t"
      "popl %%edi\n\t"
      "movb %%cl, 0x4(%%eax)\n\t"
      "movb %%cl, 0x18(%%eax)\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000169a0_3:\n\t"
      "movb 0x5(%%esi), %%al\n\t"
      "andb $0xfe, %%al\n\t"
      "popl %%edi\n\t"
      "movb %%al, 0x5(%%esi)\n\t"
      "movw $0xffff, 0x8(%%esi)\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000169a0_4:\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "je .LFUN_000169a0_13\n\t"
      "popl %%edi\n\t"
      "movb %%cl, 0x36(%%eax)\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000169a0_5:\n\t"
      "movb 0x5(%%esi), %%al\n\t"
      "andb $0xfb, %%al\n\t"
      "popl %%edi\n\t"
      "movb %%al, 0x5(%%esi)\n\t"
      "movw $0, 0x8(%%esi)\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000169a0_6:\n\t"
      "cmpw $1, 0x2(%%eax)\n\t"
      "jne .LFUN_000169a0_7\n\t"
      "movb 0x4(%%esi), %%dl\n\t"
      "movb %%dl, %%cl\n\t"
      "shrb $3, %%cl\n\t"
      "notb %%cl\n\t"
      "andb $1, %%cl\n\t"
      "andb $0xf7, %%dl\n\t"
      "testb %%cl, %%cl\n\t"
      "movb %%dl, 0x4(%%esi)\n\t"
      "je .LFUN_000169a0_8\n\t"
      "orb $0x10, %%dl\n\t"
      "movb %%dl, 0x4(%%esi)\n\t"
      ".LFUN_000169a0_7:\n\t"
      "movzbl (%%esi), %%ecx\n\t"
      "cmpw %%cx, 0x16(%%eax)\n\t"
      "jne .LFUN_000169a0_9\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl $0x200\n\t"
      "leal -0x200(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $1\n\t"
      "pushl $-1\n\t"
      "pushl %%eax\n\t"
      "call *%[c49ac0]\n\t"
      "movzbl (%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edi\n\t"
      "leal -0x200(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x25370c\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $0x28, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000169a0_8:\n\t"
      "andb $0xef, %%dl\n\t"
      "popl %%edi\n\t"
      "movb %%dl, 0x4(%%esi)\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000169a0_9:\n\t"
      "cmpb $0xa, 0x1(%%esi)\n\t"
      "jb .LFUN_000169a0_10\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "pushl $0x200\n\t"
      "leal -0x200(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $1\n\t"
      "pushl $-1\n\t"
      "pushl %%ecx\n\t"
      "call *%[c49ac0]\n\t"
      "movzbl (%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "leal -0x200(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x2536d0\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $0x28, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000169a0_10:\n\t"
      "movb 0x16(%%eax), %%cl\n\t"
      "movl 0x18(%%ebp), %%edx\n\t"
      "movb %%cl, (%%edx)\n\t"
      "movb 0x1(%%esi), %%al\n\t"
      "incb %%al\n\t"
      "popl %%edi\n\t"
      "movb %%al, 0x1(%%esi)\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000169a0_11:\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "pushl $1\n\t"
      "pushl %%eax\n\t"
      "call *%[tryget]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_000169a0_13\n\t"
      "movl 0x424(%%eax), %%ecx\n\t"
      "andl $0xfffffff3, %%ecx\n\t"
      "popl %%edi\n\t"
      "movl %%ecx, 0x424(%%eax)\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000169a0_12:\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "cmpl 0x18(%%ebx), %%ecx\n\t"
      "jne .LFUN_000169a0_13\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c27870]\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_000169a0_13:\n\t"
      "popl %%edi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_000169a0_jt:\n\t"
      ".long .LFUN_000169a0_1\n\t"
      ".long .LFUN_000169a0_3\n\t"
      ".long .LFUN_000169a0_12\n\t"
      ".long .LFUN_000169a0_4\n\t"
      ".long .LFUN_000169a0_5\n\t"
      ".long .LFUN_000169a0_11\n\t"
      ".long .LFUN_000169a0_6\n\t"
      ".long .LFUN_000169a0_13\n\t"
      ".text\n\t"
      :
      : [dget] "m"(b169a0_dget), [c18e380] "m"(b169a0_c18e380), [elem] "m"(b169a0_elem), [c2f1a0] "m"(b169a0_c2f1a0), [c49ac0] "m"(b169a0_c49ac0), [c8f390] "m"(b169a0_c8f390), [tryget] "m"(b169a0_tryget), [c27870] "m"(b169a0_c27870)
      : "memory");
}
#else
#error "FUN_000169a0: clang naked draft required"
#endif


/* actor_look_secondary_stop (0x16bd0) — readable C lift from XBE leaf. */
void actor_look_secondary_stop(int param_1, int param_2, int param_3, char *param_4,
                               int param_5, char *param_6)
{
  (void)param_1;
  (void)param_2;
  (void)param_3;
  csmemset(param_4, 0, 0x24);
  *param_4 = (char)0xff;
  if (param_6 == 0) {
    display_assert((const char *)0x253744, (const char *)0x253758, 0x550, 1);
    system_exit(-1);
  }
  if (*param_6 != 0) {
    param_4[4] = (char)(param_4[4] | 1);
  } else {
    param_4[4] = (char)(param_4[4] & ~1);
  }
  if (param_5 != 0) {
    csmemset((void *)param_5, 0, 0x58);
    *(short *)((char *)param_5 + 2) = (short)0xffff;
  }
}




/* FUN_00016c40 (0x16c40) */
void FUN_00016c40(int param_1, int param_2, short param_3, char *param_4)
{
  int iVar1;
  iVar1 = (int)tag_block_get_element((char *)global_scenario_get() + 0x438,
                                     (int)param_3, 0x60);
  if ((int)(unsigned char)*param_4 >= *(int *)(iVar1 + 0x30)) {
    *param_4 = (char)0xff;
  }
}

/* FUN_00016c80 (0x16c80) — Scenario encounter guard-zone boundary callback.
 * Checks if the encounter element at param_3 has the 0x10 flag set at +0x20.
 * If so, sets bit 0x1000 in the object's flags at +0x1b4. */
void FUN_00016c80(int param_1, int param_2, short param_3)
{
  char *elem;
  char *obj;
  elem = (char *)tag_block_get_element((char *)global_scenario_get() + 0x438,
                                       (int)param_3, 0x60);
  if ((*(unsigned char *)(elem + 0x20) & 0x10) != 0) {
    obj = (char *)object_get_and_verify_type(param_2, 3);
    *(unsigned int *)(obj + 0x1b4) = *(unsigned int *)(obj + 0x1b4) | 0x1000;
  }
}

/* FUN_00016cd0 (0x16cd0) — Prop-interest reset callback.
 * Sets bit 3 (0x08) and clears bit 4 (0x10) in byte at param_4+4.
 * Called by actor_look_compute_prop_interest as the reset callback.
 * Dispatcher passes: (actor_handle, object_handle, index, state_data_ptr, ...)
 */
void FUN_00016cd0(int param_1, int param_2, int param_3, char *param_4)
{
  param_4[4] = (param_4[4] & (char)0xef) | 8;
}

/* FUN_00016cf0 (0x16cf0) — readable C lift from XBE leaf. */
void FUN_00016cf0(int param_1, int param_2, short param_3, int param_4, int param_5)
{
  void *unit;
  char *out_index;

  unit = object_get_and_verify_type(param_2, 3);
  if ((*(unsigned char *)((char *)param_4 + 4) & 2) == 0) {
    out_index = (char *)&param_4 + 3;
    /* state_ptr arrives in esi in the XBE; pass as 6th for cdecl callee stub. */
    FUN_000169a0(param_1, param_2, param_3, param_5, out_index, (void *)param_4);
  }
  *(int *)((char *)unit + 0x1b4) &= ~0x1000;
}




/* actor_look_compute_prop_interest (0x16d40) — XBE naked draft (batch 78). */
#if defined(__clang__)
static void *(*const b16d40_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void (*const b16d40_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b16d40_exitfn)(int) = system_exit;
static void *(*const b16d40_memset)(void *, int, unsigned int) = csmemset;

__attribute__((naked, noinline))
void actor_look_compute_prop_interest(int actor_handle __attribute__((unused)), int param_2 __attribute__((unused)), short *param_3 __attribute__((unused)), void (*callback)(void) __attribute__((unused)), int param_5 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "movl 0x6325a4, %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%esi\n\t"
      "movb 0x6(%%esi), %%al\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_look_compute_prop_interest_5\n\t"
      "cmpl $-1, 0x28(%%esi)\n\t"
      "jne .Lactor_look_compute_prop_interest_1\n\t"
      "pushl $1\n\t"
      "pushl $0x611\n\t"
      "pushl $0x253758\n\t"
      "pushl $0x253778\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lactor_look_compute_prop_interest_1:\n\t"
      "movb 0x6(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_look_compute_prop_interest_5\n\t"
      "movl 0x28(%%esi), %%ecx\n\t"
      "movl 0x6325a0, %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%ebx\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $0, 0x2(%%ebx)\n\t"
      "movl $0, -0x4(%%ebp)\n\t"
      "jle .Lactor_look_compute_prop_interest_6\n\t"
      "movl %%edi, %%edi\n\t"
      ".Lactor_look_compute_prop_interest_2:\n\t"
      "movswl -0x4(%%ebp), %%edi\n\t"
      "movl 0x58(%%ebx,%%edi,4), %%eax\n\t"
      "movl 0x63259c, %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%esi\n\t"
      "movb 0xc(%%ebp), %%al\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_look_compute_prop_interest_3\n\t"
      "pushl $0x24\n\t"
      "leal 0x1c(%%esi), %%edx\n\t"
      "pushl $0\n\t"
      "pushl %%edx\n\t"
      "call *%[memset]\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x2(%%esi), %%ax\n\t"
      "addl $0xc, %%esp\n\t"
      "andl $0xfffffffb, %%eax\n\t"
      "orl $8, %%eax\n\t"
      "movw %%ax, 0x2(%%esi)\n\t"
      ".Lactor_look_compute_prop_interest_3:\n\t"
      "testb $8, 0x2(%%esi)\n\t"
      "je .Lactor_look_compute_prop_interest_4\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "movl 0x18(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl 0x18(%%ebx,%%edi,4), %%ecx\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw (%%edx), %%ax\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "pushl $0\n\t"
      "addl $0x1c, %%esi\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *0x14(%%ebp)\n\t"
      "addl $0x18, %%esp\n\t"
      ".Lactor_look_compute_prop_interest_4:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "incl %%eax\n\t"
      "cmpw 0x2(%%ebx), %%ax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "jl .Lactor_look_compute_prop_interest_2\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lactor_look_compute_prop_interest_5:\n\t"
      "movl 0x18(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "leal 0x2c(%%eax), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl 0x18(%%esi), %%ecx\n\t"
      "leal 0x8(%%eax), %%edx\n\t"
      "movswl (%%eax), %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edi\n\t"
      "call *0x14(%%ebp)\n\t"
      "addl $0x18, %%esp\n\t"
      ".Lactor_look_compute_prop_interest_6:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [dget] "m"(b16d40_dget), [assert] "m"(b16d40_assert), [exitfn] "m"(b16d40_exitfn), [memset] "m"(b16d40_memset)
      : "memory");
}
#else
#error "actor_look_compute_prop_interest: clang naked draft required"
#endif


/* FUN_00016e70 (0x16e70)
 * Initialize a command-list execution state for an actor.
 *
 * Validates the command-list index against the scenario encounter table,
 * checks BSP compatibility, extracts command flags, optionally stops
 * scripted look, and dispatches initialization via
 * actor_look_compute_prop_interest with the actor_look_secondary_stop callback.
 *
 * Confirmed: datum_get(actor_data, actor_handle) → actor.
 * Confirmed: global_scenario_get, tag_block_get_element(scenario+0x438,
 * cmd_idx, 0x60). Confirmed: command flags extracted from iVar3[0x20] (bits
 * 0-3). */
int FUN_00016e70(int actor_handle, short param_2, char *param_3)
{
  char *actor;
  char *scenario;
  char *cmd_entry;
  unsigned int flags;
  char bit0;
  char bit1;
  char stop_look;
  char bit3;
  char local_10c[256];

  actor = (char *)datum_get(actor_data, actor_handle);
  scenario = (char *)global_scenario_get();
  if (param_3 == (char *)0) {
    display_assert("state_data", "c:\\halo\\SOURCE\\ai\\action_obey.c", 0x63d,
                   1);
    system_exit(-1);
  }
  csmemset(param_3, 0, 0x84);
  if (param_2 >= 0) {
    if ((int)param_2 < *(int *)(scenario + 0x438)) {
      cmd_entry =
        (char *)tag_block_get_element(scenario + 0x438, (int)param_2, 0x60);
      if (*(char *)(actor + 6) == '\0' || *(int *)(actor + 0x28) != -1) {
        if (*(short *)(cmd_entry + 0x2e) != -1 &&
            *(short *)(cmd_entry + 0x2e) != *(short *)0x326a0c) {
          error(2, "wrong structure bsp, cannot execute command list %s",
                (int)cmd_entry);
          return 0;
        }
        *(short *)param_3 = param_2;
        flags = *(unsigned int *)(cmd_entry + 0x20);
        bit0 = *(char *)(cmd_entry + 0x20) & 1;
        bit1 = (char)((flags >> 1) & 1);
        stop_look = ~(char)(flags >> 2) & 1;
        bit3 = ~(char)(flags >> 3) & 1;
        if (stop_look == 0) {
          FUN_00027870(actor_handle);
        }
        *(char *)(param_3 + 2) = bit0;
        param_3[3] = stop_look;
        *(char *)(param_3 + 4) = bit3;
        actor_look_compute_prop_interest(
          actor_handle, 1, (short *)param_3,
          (void (*)(void))actor_look_secondary_stop, (int)&bit1);
        return 1;
      }
      if (*(char *)(actor + 8) == '\0') {
        *(short *)(actor + 0x90) = param_2;
        return 0;
      }
      ai_debug_describe_actor(actor_handle, -1, 1, local_10c, 0x100);
      error(
        2,
        "swarm actor %s cannot execute command list, ran out of swarm caches",
        (int)local_10c);
    }
  }
  return 0;
}

/* FUN_00016ff0 (0x16ff0) — readable C lift from XBE leaf. */
void FUN_00016ff0(int actor_handle)
{
  void *actor;
  short *look_state;
  scenario_t *scenario;

  actor = datum_get(*(void **)0x6325a4, actor_handle);
  look_state = (short *)((char *)actor + 0x9c);
  scenario = global_scenario_get();
  if (*look_state >= 0 && (int)*look_state < *(int *)((char *)scenario + 0x438)) {
    actor_look_compute_prop_interest(actor_handle, 0, look_state,
                                     (void (*)(void))0x16c40, 0);
    return;
  }
  *look_state = (short)0xffff;
  *((unsigned char *)look_state + 5) = 1;
  actor_action_change(actor_handle, 0, 0);
}




/* actor_clear_aim_target (0x17060) — readable C lift. */
void actor_clear_aim_target(int actor_handle)
{
  char *actor;

  actor = (char *)datum_get(*(void **)0x6325a4, actor_handle);
  if (*(char *)(actor + 0xcc)) {
    *(int *)(actor + 0x9c + 0x40) = -1;
  }
}

/* FUN_00017090 (0x17090) — readable C lift. */
void FUN_00017090(int actor_handle)
{
  char *actor = (char *)datum_get(*(void **)0x6325a4, actor_handle);
  actor_look_compute_prop_interest(actor_handle, 0, (short *)(actor + 0x9c),
                                   (void (*)(void))0x16cd0, 0);
}

/* FUN_000170c0 (0x170c0)
 * Compute actor prop-interest for the prop list at actor+0x9c using the
 * guard-zone boundary callback (FUN_00016c80).
 *
 * Same pattern as FUN_00017090 but selects the guard-specific callback.
 *
 * Confirmed: datum_get(actor_data, actor_handle);
 * actor_look_compute_prop_interest with callback=FUN_00016c80, reset=0,
 * prop_state=actor+0x9c, param_5=0. */
void FUN_000170c0(int actor_handle)
{
  char *actor;
  actor = (char *)datum_get(actor_data, actor_handle);
  actor_look_compute_prop_interest(actor_handle, 0, (short *)(actor + 0x9c),
                                   (void (*)(void))FUN_00016c80, 0);
}

/* FUN_000170f0 (0x170f0)
 * Compute actor prop-interest for the prop list at actor+0x9c using the
 * danger-zone update callback (FUN_00016cf0).
 *
 * Same pattern as FUN_00017090 but selects the danger-update callback.
 *
 * Confirmed: datum_get(actor_data, actor_handle);
 * actor_look_compute_prop_interest with callback=FUN_00016cf0, reset=0,
 * prop_state=actor+0x9c, param_5=0. */
void FUN_000170f0(int actor_handle)
{
  char *actor;
  actor = (char *)datum_get(actor_data, actor_handle);
  actor_look_compute_prop_interest(actor_handle, 0, (short *)(actor + 0x9c),
                                   (void (*)(void))FUN_00016cf0, 0);
}

/* FUN_00017120 (0x17120) — XBE naked draft (batch 69). */
#if defined(__clang__)
static int (*const b17120_c1d9179)(char *str, size_t size, const char *format, ...) = snprintf;
static void *(*const b17120_elem)(void *, int, int) = tag_block_get_element;
static char * (*const b17120_c1a67b0)(short param_1, unsigned char param_2) = FUN_001a67b0;
static char * (*const b17120_c8dff0)(char *destination, const char *source) = csstrcpy;
static int (*const b17120_c1d90f0)(char *buffer, const char *format, ...) = crt_sprintf;

__attribute__((naked, noinline))
void FUN_00017120(void *scenario_data __attribute__((unused)), short *cmd __attribute__((unused)), char *out_buf __attribute__((unused)), int out_size __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x140, %%esp\n\t"
      "pushl %%esi\n\t"
      "movl 0xc(%%ebp), %%esi\n\t"
      "movswl (%%esi), %%eax\n\t"
      "cmpl $0x1b, %%eax\n\t"
      "pushl %%edi\n\t"
      "movl $0x253d04, -0x14(%%ebp)\n\t"
      "movl $0x253cf0, -0x10(%%ebp)\n\t"
      "movl $0x253cdc, -0xc(%%ebp)\n\t"
      "movl $0x253cc8, -0x8(%%ebp)\n\t"
      "movl $0x253cb4, -0x4(%%ebp)\n\t"
      "ja .LFUN_00017120_42\n\t"
      "jmp *.LFUN_00017120_jt(,%%eax,4)\n\t"
      ".LFUN_00017120_1:\n\t"
      "flds 0x4(%%esi)\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "subl $8, %%esp\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x253ca8\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1d9179]\n\t"
      "addl $0x14, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00017120_2:\n\t"
      "movswl 0x2(%%esi), %%edx\n\t"
      "movswl 0xc(%%esi), %%ecx\n\t"
      "movl $0x253c98, -0x8(%%ebp)\n\t"
      "movl $0x253c8c, -0x4(%%ebp)\n\t"
      "movl -0x8(%%ebp,%%edx,4), %%eax\n\t"
      "movl 0x14(%%ebp), %%edx\n\t"
      "pushl %%eax\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x253c7c\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d9179]\n\t"
      "addl $0x14, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00017120_3:\n\t"
      "movswl 0xe(%%esi), %%ecx\n\t"
      "movswl 0xc(%%esi), %%edx\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "pushl %%ecx\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x253c60\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1d9179]\n\t"
      "addl $0x14, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00017120_4:\n\t"
      "movw 0xc(%%esi), %%ax\n\t"
      "flds 0x4(%%esi)\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "movl $0x253c54, -0x14(%%ebp)\n\t"
      "movl $0x253c4c, -0x10(%%ebp)\n\t"
      "movl $0x253c44, -0xc(%%ebp)\n\t"
      "movl $0x253c38, -0x8(%%ebp)\n\t"
      "movl $0x253c2c, -0x4(%%ebp)\n\t"
      "jne .LFUN_00017120_5\n\t"
      "movswl 0x2(%%esi), %%edx\n\t"
      "movl -0x14(%%ebp,%%edx,4), %%eax\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "subl $0x10, %%esp\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds 0x8(%%esi)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl %%eax\n\t"
      "pushl $0x253c08\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c1d9179]\n\t"
      "addl $0x20, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00017120_5:\n\t"
      "movswl 0x2(%%esi), %%ecx\n\t"
      "movl -0x14(%%ebp,%%ecx,4), %%edx\n\t"
      "subl $8, %%esp\n\t"
      "movswl %%ax, %%eax\n\t"
      "fstpl (%%esp)\n\t"
      "pushl %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl $0x253be4\n\t"
      "jmp .LFUN_00017120_20\n\t"
      ".LFUN_00017120_6:\n\t"
      "movswl 0x2(%%esi), %%edx\n\t"
      "flds 0x4(%%esi)\n\t"
      "subl $8, %%esp\n\t"
      "movl $0x253c54, -0x10(%%ebp)\n\t"
      "movl $0x253c4c, -0xc(%%ebp)\n\t"
      "movl $0x253c44, -0x8(%%ebp)\n\t"
      "fstpl (%%esp)\n\t"
      "movl $0x253c38, -0x4(%%ebp)\n\t"
      "movl -0x10(%%ebp,%%edx,4), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x253bcc\n\t"
      "jmp .LFUN_00017120_15\n\t"
      ".LFUN_00017120_7:\n\t"
      "movswl 0xc(%%esi), %%eax\n\t"
      "flds 0x4(%%esi)\n\t"
      "movswl 0x2(%%esi), %%ecx\n\t"
      "movl -0x14(%%ebp,%%ecx,4), %%edx\n\t"
      "subl $8, %%esp\n\t"
      "fstpl (%%esp)\n\t"
      "pushl %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl $0x253bb0\n\t"
      "jmp .LFUN_00017120_20\n\t"
      ".LFUN_00017120_8:\n\t"
      "flds 0x8(%%esi)\n\t"
      "movswl 0xe(%%esi), %%edx\n\t"
      "movswl 0xc(%%esi), %%eax\n\t"
      "movswl 0x2(%%esi), %%ecx\n\t"
      "subl $0x10, %%esp\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds 0x4(%%esi)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl %%edx\n\t"
      "movl -0x14(%%ebp,%%ecx,4), %%edx\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "pushl %%eax\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl $0x253b7c\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1d9179]\n\t"
      "addl $0x28, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00017120_9:\n\t"
      "movswl 0x2(%%esi), %%edx\n\t"
      "flds 0x4(%%esi)\n\t"
      "movl -0x14(%%ebp,%%edx,4), %%eax\n\t"
      "subl $8, %%esp\n\t"
      "fstpl (%%esp)\n\t"
      "pushl %%eax\n\t"
      "pushl $0x253b60\n\t"
      "jmp .LFUN_00017120_15\n\t"
      ".LFUN_00017120_10:\n\t"
      "movw 0x18(%%esi), %%cx\n\t"
      "testw %%cx, %%cx\n\t"
      "movl $0x253b58, %%eax\n\t"
      "jl .LFUN_00017120_11\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "movl 0x204(%%edx), %%edi\n\t"
      "addl $0x204, %%edx\n\t"
      "movswl %%cx, %%ecx\n\t"
      "cmpl %%edi, %%ecx\n\t"
      "jge .LFUN_00017120_11\n\t"
      "pushl $0x24\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[elem]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_00017120_11:\n\t"
      "flds 0x4(%%esi)\n\t"
      "movl 0x14(%%ebp), %%edx\n\t"
      "subl $8, %%esp\n\t"
      "fstpl (%%esp)\n\t"
      "pushl %%eax\n\t"
      "movswl 0x2(%%esi), %%eax\n\t"
      "movl -0x14(%%ebp,%%eax,4), %%ecx\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x253b40\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d9179]\n\t"
      "addl $0x1c, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00017120_12:\n\t"
      "movswl 0x2(%%esi), %%ecx\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "movl $0x253b34, -0x10(%%ebp)\n\t"
      "movl $0x253b2c, -0xc(%%ebp)\n\t"
      "movl $0x253b24, -0x8(%%ebp)\n\t"
      "movl $0x253b1c, -0x4(%%ebp)\n\t"
      "movl -0x10(%%ebp,%%ecx,4), %%edx\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x253b08\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1d9179]\n\t"
      "addl $0x10, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00017120_13:\n\t"
      "movswl 0x2(%%esi), %%edx\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      "movl $0x253b00, -0x8(%%ebp)\n\t"
      "movl $0x253af8, -0x4(%%ebp)\n\t"
      "movl -0x8(%%ebp,%%edx,4), %%eax\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl $0x253aec\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c1d9179]\n\t"
      "addl $0x10, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00017120_14:\n\t"
      "movswl 0xc(%%esi), %%eax\n\t"
      "flds 0x4(%%esi)\n\t"
      "subl $8, %%esp\n\t"
      "fstpl (%%esp)\n\t"
      "pushl %%eax\n\t"
      "pushl $0x253ad4\n\t"
      ".LFUN_00017120_15:\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c1d9179]\n\t"
      "addl $0x18, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00017120_16:\n\t"
      "movswl 0xc(%%esi), %%eax\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl $0x253abc\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c1d9179]\n\t"
      "addl $0x10, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00017120_17:\n\t"
      "movswl 0x2(%%esi), %%eax\n\t"
      "flds 0x4(%%esi)\n\t"
      "movl 0x14(%%ebp), %%edx\n\t"
      "subl $8, %%esp\n\t"
      "movl $0x253aac, -0x14(%%ebp)\n\t"
      "movl $0x253aa4, -0x10(%%ebp)\n\t"
      "fstpl (%%esp)\n\t"
      "movl $0x253a98, -0xc(%%ebp)\n\t"
      "movl $0x253a90, -0x8(%%ebp)\n\t"
      "movl $0x253a84, -0x4(%%ebp)\n\t"
      "movl -0x14(%%ebp,%%eax,4), %%ecx\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x253a60\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d9179]\n\t"
      "addl $0x18, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00017120_18:\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "pushl $0x253a50\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c1d9179]\n\t"
      "addl $0xc, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00017120_19:\n\t"
      "flds 0x8(%%esi)\n\t"
      "subl $0x10, %%esp\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds 0x4(%%esi)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x253a30\n\t"
      ".LFUN_00017120_20:\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1d9179]\n\t"
      "addl $0x1c, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00017120_21:\n\t"
      "movw 0x12(%%esi), %%cx\n\t"
      "cmpw $-1, %%cx\n\t"
      "movl $0x253a20, -0x8(%%ebp)\n\t"
      "movl $0x253a0c, -0x4(%%ebp)\n\t"
      "movl $0x253b58, %%eax\n\t"
      "jne .LFUN_00017120_22\n\t"
      "movl $0x253a04, %%eax\n\t"
      "jmp .LFUN_00017120_23\n\t"
      ".LFUN_00017120_22:\n\t"
      "testw %%cx, %%cx\n\t"
      "jl .LFUN_00017120_23\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "movl 0x450(%%edx), %%edi\n\t"
      "addl $0x450, %%edx\n\t"
      "movswl %%cx, %%ecx\n\t"
      "cmpl %%edi, %%ecx\n\t"
      "jge .LFUN_00017120_23\n\t"
      "pushl $0x28\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[elem]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_00017120_23:\n\t"
      "movswl 0x2(%%esi), %%edx\n\t"
      "movl -0x8(%%ebp,%%edx,4), %%ecx\n\t"
      "movl 0x14(%%ebp), %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "pushl $0x2539f4\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d9179]\n\t"
      "addl $0x14, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00017120_24:\n\t"
      "movw 0x10(%%esi), %%si\n\t"
      "cmpw $-1, %%si\n\t"
      "movl $0x253b58, %%eax\n\t"
      "jne .LFUN_00017120_25\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "movl $0x253a04, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x2539e8\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c1d9179]\n\t"
      "addl $0x10, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00017120_25:\n\t"
      "testw %%si, %%si\n\t"
      "jl .LFUN_00017120_26\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "movswl %%si, %%ecx\n\t"
      "movl 0x444(%%edx), %%esi\n\t"
      "addl $0x444, %%edx\n\t"
      "cmpl %%esi, %%ecx\n\t"
      "jge .LFUN_00017120_26\n\t"
      "pushl $0x3c\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[elem]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_00017120_26:\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl $0x2539e8\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c1d9179]\n\t"
      "addl $0x10, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00017120_27:\n\t"
      "movw 0x14(%%esi), %%si\n\t"
      "cmpw $-1, %%si\n\t"
      "movl $0x253b58, %%eax\n\t"
      "jne .LFUN_00017120_28\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "movl $0x253a04, %%eax\n\t"
      "pushl %%eax\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "pushl $0x2539d4\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1d9179]\n\t"
      "addl $0x10, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00017120_28:\n\t"
      "testw %%si, %%si\n\t"
      "jl .LFUN_00017120_29\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "movswl %%si, %%ecx\n\t"
      "movl 0x45c(%%edx), %%esi\n\t"
      "addl $0x45c, %%edx\n\t"
      "cmpl %%esi, %%ecx\n\t"
      "jge .LFUN_00017120_29\n\t"
      "pushl $0x28\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[elem]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_00017120_29:\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "pushl %%eax\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "pushl $0x2539d4\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1d9179]\n\t"
      "addl $0x10, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00017120_30:\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x2(%%esi), %%dx\n\t"
      "pushl $0\n\t"
      "pushl %%edx\n\t"
      "call *%[c1a67b0]\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "pushl %%eax\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "pushl $0x2539c8\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1d9179]\n\t"
      "addl $0x18, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00017120_31:\n\t"
      "movswl 0x2(%%esi), %%edx\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      "movl $0x253af8, -0x8(%%ebp)\n\t"
      "movl $0x253b00, -0x4(%%ebp)\n\t"
      "movl -0x8(%%ebp,%%edx,4), %%eax\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl $0x2539b8\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c1d9179]\n\t"
      "addl $0x10, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00017120_32:\n\t"
      "movswl 0x2(%%esi), %%eax\n\t"
      "movl $0x2539b0, -0x40(%%ebp)\n\t"
      "movl $0x2539a0, -0x3c(%%ebp)\n\t"
      "movl $0x253990, -0x38(%%ebp)\n\t"
      "movl $0x253984, -0x34(%%ebp)\n\t"
      "movl $0x253978, -0x30(%%ebp)\n\t"
      "movl $0x25396c, -0x2c(%%ebp)\n\t"
      "movl $0x253960, -0x28(%%ebp)\n\t"
      "movl $0x253954, -0x24(%%ebp)\n\t"
      "movl $0x253948, -0x20(%%ebp)\n\t"
      "movl $0x253938, -0x1c(%%ebp)\n\t"
      "movl $0x253928, -0x18(%%ebp)\n\t"
      "movl -0x40(%%ebp,%%eax,4), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x25391c\n\t"
      "jmp .LFUN_00017120_43\n\t"
      ".LFUN_00017120_33:\n\t"
      "movswl 0x2(%%esi), %%ecx\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "movl $0x253af8, -0x8(%%ebp)\n\t"
      "movl $0x253b00, -0x4(%%ebp)\n\t"
      "movl -0x8(%%ebp,%%ecx,4), %%edx\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x25390c\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1d9179]\n\t"
      "addl $0x10, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00017120_34:\n\t"
      "movswl 0x2(%%esi), %%edx\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      "movl $0x2538fc, -0xc(%%ebp)\n\t"
      "movl $0x2538e8, -0x8(%%ebp)\n\t"
      "movl $0x2538d0, -0x4(%%ebp)\n\t"
      "movl -0xc(%%ebp,%%edx,4), %%eax\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl $0x2538c8\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c1d9179]\n\t"
      "addl $0x10, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00017120_35:\n\t"
      "movw 0x16(%%esi), %%ax\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "movl $0x2538c0, -0x8(%%ebp)\n\t"
      "movl $0x2538a4, -0x4(%%ebp)\n\t"
      "jne .LFUN_00017120_36\n\t"
      "movswl 0x2(%%esi), %%eax\n\t"
      "movl -0x8(%%ebp,%%eax,4), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x253890\n\t"
      "jmp .LFUN_00017120_43\n\t"
      ".LFUN_00017120_36:\n\t"
      "movswl 0x2(%%esi), %%ecx\n\t"
      "movl -0x8(%%ebp,%%ecx,4), %%edx\n\t"
      "movswl %%ax, %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl $0x253880\n\t"
      "jmp .LFUN_00017120_40\n\t"
      ".LFUN_00017120_37:\n\t"
      "flds 0x4(%%esi)\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "subl $8, %%esp\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x253870\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1d9179]\n\t"
      "addl $0x14, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00017120_38:\n\t"
      "leal -0x140(%%ebp), %%edx\n\t"
      "pushl $0x25386f\n\t"
      "pushl %%edx\n\t"
      "call *%[c8dff0]\n\t"
      "movw 0xe(%%esi), %%ax\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .LFUN_00017120_39\n\t"
      "movswl %%ax, %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x140(%%ebp), %%ecx\n\t"
      "pushl $0x25385c\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1d90f0]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_00017120_39:\n\t"
      "movswl 0xc(%%esi), %%eax\n\t"
      "leal -0x140(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl $0x253848\n\t"
      ".LFUN_00017120_40:\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c1d9179]\n\t"
      "addl $0x14, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00017120_41:\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "pushl $0x253844\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1d9179]\n\t"
      "addl $0xc, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00017120_42:\n\t"
      "pushl %%eax\n\t"
      "pushl $0x253834\n\t"
      ".LFUN_00017120_43:\n\t"
      "movl 0x14(%%ebp), %%edx\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d9179]\n\t"
      "addl $0x10, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_00017120_jt:\n\t"
      ".long .LFUN_00017120_1\n\t"
      ".long .LFUN_00017120_2\n\t"
      ".long .LFUN_00017120_3\n\t"
      ".long .LFUN_00017120_4\n\t"
      ".long .LFUN_00017120_7\n\t"
      ".long .LFUN_00017120_12\n\t"
      ".long .LFUN_00017120_13\n\t"
      ".long .LFUN_00017120_14\n\t"
      ".long .LFUN_00017120_16\n\t"
      ".long .LFUN_00017120_17\n\t"
      ".long .LFUN_00017120_18\n\t"
      ".long .LFUN_00017120_19\n\t"
      ".long .LFUN_00017120_21\n\t"
      ".long .LFUN_00017120_24\n\t"
      ".long .LFUN_00017120_27\n\t"
      ".long .LFUN_00017120_32\n\t"
      ".long .LFUN_00017120_30\n\t"
      ".long .LFUN_00017120_31\n\t"
      ".long .LFUN_00017120_33\n\t"
      ".long .LFUN_00017120_34\n\t"
      ".long .LFUN_00017120_35\n\t"
      ".long .LFUN_00017120_41\n\t"
      ".long .LFUN_00017120_6\n\t"
      ".long .LFUN_00017120_8\n\t"
      ".long .LFUN_00017120_9\n\t"
      ".long .LFUN_00017120_10\n\t"
      ".long .LFUN_00017120_37\n\t"
      ".long .LFUN_00017120_38\n\t"
      ".text\n\t"
      :
      : [c1d9179] "m"(b17120_c1d9179), [elem] "m"(b17120_elem), [c1a67b0] "m"(b17120_c1a67b0), [c8dff0] "m"(b17120_c8dff0), [c1d90f0] "m"(b17120_c1d90f0)
      : "memory");
}
#else
#error "FUN_00017120: clang naked draft required"
#endif


/* FUN_000178b0 (0x178b0)
 * Subtract two 2D vectors: result = b - a.
 * Confirmed: cdecl, 3 stack params. FLD [ECX]/FSUB [EDX]/FSTP [EAX] twice. */
void FUN_000178b0(float *a, float *b, float *result)
{
  result[0] = b[0] - a[0];
  result[1] = b[1] - a[1];
}

/* Compute the cross product of two 3D vectors: out = a x b.
 *
 * Ref: z computed first, then y, then x; all three FPU results held on the
 * x87 stack before the first FSTP (aliasing safe when b==out). */
void cross_product3d(float *a, float *b, float *out)
{
  float z = a[0] * b[1] - a[1] * b[0];
  float y = a[2] * b[0] - a[0] * b[2];
  float x = a[1] * b[2] - a[2] * b[1];
  out[0] = x;
  out[1] = y;
  out[2] = z;
}

/* FUN_00017910 (0x17910)
 * Negate a 3D vector: result = -a.
 * Confirmed: cdecl, 2 stack params. FCHS on each component. */
void FUN_00017910(float *a, float *result)
{
  result[0] = -a[0];
  result[1] = -a[1];
  result[2] = -a[2];
}

/* FUN_00017940 (0x17940)
 * Draw a random int16_t in [min, max] using the global random seed.
 *
 * Calls get_global_random_seed_address() to obtain a pointer to the global
 * RNG seed, then passes it together with min and max to random_range.
 *
 * Note: MSVC pre-pushed min/max before calling get_global_random_seed_address
 * (which is void), reusing that stack space.  The seed pointer (EAX) is then
 * pushed last, making it the first C argument to random_range.
 *
 * Confirmed: PUSH EAX (max); PUSH ECX (min); CALL 0x10b0d0
 *   (get_global_random_seed_address, takes no params); PUSH EAX (seed);
 *   CALL 0x10b2d0 (random_range); ADD ESP,0xc. */
int16_t FUN_00017940(int16_t min, int16_t max)
{
  return random_range((unsigned int *)get_global_random_seed_address(), min,
                      max);
}

/* FUN_00017960 (0x17960) — Resolve look-direction vector into state_data.
 *
 * Writes a normalized look-direction vec3 to state_data+0xc..+0x14 based
 * on the look_type field at state_data+8.
 *
 * look_type 0: copy actor's current facing (actor+0x174..0x17c)
 * look_type 1: negate the actor's current facing
 * look_type 2/3: cross product of world forward vector (*(float**)0x31fc44)
 *   with the actor facing; if zero-length, fallback to object forward
 *   (object+0x30); if still zero, use world default (*(float**)0x31fc3c).
 *   look_type 2 stores positive, look_type 3 stores negative.
 *
 * Register args: ECX=state_data, EAX=actor_handle, EDI=object_handle.
 * Confirmed: ESI=state_data; actor+0x18=object_handle check. */
void FUN_00017960(char *state_data, int actor_handle, int object_handle)
{
  char *actor;
  float facing[3];
  float cross[3];
  char *obj;

  actor = (char *)datum_get(actor_data, actor_handle);
  if (object_handle == *(int *)(actor + 0x18)) {
    facing[0] = *(float *)(actor + 0x174);
    facing[1] = *(float *)(actor + 0x178);
    facing[2] = *(float *)(actor + 0x17c);
  } else {
    units_debug_get_closest_unit(object_handle, &facing[0]);
  }

  switch (*(short *)(state_data + 8)) {
  case 0:
    *(float *)(state_data + 0xc) = facing[0];
    *(float *)(state_data + 0x10) = facing[1];
    *(float *)(state_data + 0x14) = facing[2];
    return;
  case 1:
    *(float *)(state_data + 0xc) = -facing[0];
    *(float *)(state_data + 0x10) = -facing[1];
    *(float *)(state_data + 0x14) = -facing[2];
    return;
  case 2:
  case 3:
    cross_product3d(*(float **)0x31fc44, &facing[0], &cross[0]);
    if (normalize3d(&cross[0]) == 0.0f) {
      obj = (char *)object_get_and_verify_type(object_handle, 0x3);
      cross_product3d((float *)(obj + 0x30), &facing[0], &cross[0]);
      if (normalize3d(&cross[0]) == 0.0f) {
        cross[0] = *(float *)(*(int *)0x31fc3c);
        cross[1] = *(float *)(*(int *)0x31fc3c + 4);
        cross[2] = *(float *)(*(int *)0x31fc3c + 8);
      }
    }
    if (*(short *)(state_data + 8) == 2) {
      *(float *)(state_data + 0xc) = cross[0];
      *(float *)(state_data + 0x10) = cross[1];
      *(float *)(state_data + 0x14) = cross[2];
      return;
    }
    *(float *)(state_data + 0xc) = -cross[0];
    *(float *)(state_data + 0x10) = -cross[1];
    *(float *)(state_data + 0x14) = -cross[2];
    return;
  default:
    return;
  }
}

/* FUN_00017ab0 (0x17ab0) — Execute one command-list atom for an actor.
 *
 * Dispatches on the atom type (28 cases, jump table at 0x18adc) from the
 * scenario command list block (scenario+0x438, stride 0x60; atoms at
 * cmd_list+0x30, stride 0x20; points at cmd_list+0x3c, stride 0x14).
 * Returns 1 when the atom executed/queued successfully, 0 otherwise.
 * When the AI command-debug flag (0x5aca5b) is set, prints
 * "<encounter/squad>: <list> #<n>[ FAILED]: <describe>" via error().
 *
 * Confirmed: cdecl(actor_handle, scenario_idx, state_data) plus
 *   cmd_param@<eax>, unit_handle@<ecx>; frame SUB ESP,0x174.
 * Confirmed: misgrouped Ghidra calls are really
 *   tag_block_get_element(scenario+0x438, scenario_idx, 0x60),
 *   tag_block_get_element(scenario+0x450/0x444/0x45c, idx, stride) and
 *   FUN_00017120(scenario, atom, 0x5ab100, 0x100).
 * Confirmed: FUN_00017960(state_data@<ecx>, actor_handle@<eax>,
 *   unit_handle@<edi>) at 0x18113 (EDI still holds entry ECX).
 * Confirmed: qsort(near_list, count, 8, FUN_00016960) at 0x185ea.
 * Confirmed: case 0x10 reuses the state_data arg slot for the seat short
 *   and case 0x1b reuses the scenario_idx slot for the point element
 *   (separate locals here).
 * Confirmed: case 0x1b non-flying branch zeroes the actr-definition local
 *   (dead store kept for parity, decomp local_1c = 0). */
bool FUN_00017ab0(int actor_handle, short scenario_idx, char *state_data,
                  int cmd_param, int unit_handle)
{
  char *actor;
  char *actr_def;
  char *actv_def;
  char *cmd_list;
  short *atom;
  int *elem;
  int *elem2;
  char *obj;
  char *bipd;
  char *ent;
  char *enc;
  int bipd_null;
  char *sq;
  const char *status;
  int prop;
  short cmd_type;
  short mode;
  short mode2;
  short anim_idx;
  short count;
  short i;
  short seat_count;
  unsigned short umode;
  int atom_seq;
  int fp_index;
  int prop_handle;
  int object_index;
  int style;
  int anim_tag;
  int do_flag;
  int vmode;
  int seat_slot;
  int unit_out;
  int t;
  char loop_flag;
  char aim_flag;
  char flag;
  char result;
  int elem_z;
  float radius;
  float best;
  float d;
  int prop_iter[2];
  int obj_iter[4];
  data_iter_t iter;
  float pos[3];
  float near_list[32];
  char look_target[0x10];
  char comm[0x30];
  char name_buf[128];

  actor = (char *)datum_get(actor_data, actor_handle);
  actr_def = (char *)tag_get(0x61637472, *(int *)(actor + 0x58));
  actv_def = (char *)tag_get(0x61637476, *(int *)(actor + 0x5c));
  cmd_list = (char *)tag_block_get_element(
    (char *)global_scenario_get() + 0x438, (int)scenario_idx, 0x60);
  result = 0;
  if ((int)(unsigned char)*state_data >= *(int *)(cmd_list + 0x30)) {
    return 0;
  }
  atom = (short *)tag_block_get_element(cmd_list + 0x30,
                                        (int)(unsigned char)*state_data, 0x20);
  atom_seq = (int)(unsigned char)*state_data + 1;
  cmd_type = *atom;

  switch (cmd_type) {
  case 0:
    *(short *)(state_data + 2) =
      (short)(int)(*(float *)(atom + 2) * *(float *)0x253394);
    result = 1;
    break;

  case 1:
  case 2:
    if (cmd_param != 0 && (mode = atom[6], mode >= 0)) {
      if ((int)mode < *(int *)(cmd_list + 0x3c)) {
        elem = (int *)tag_block_get_element(cmd_list + 0x3c, (int)mode, 0x14);
        *(short *)(state_data + 2) = 0;
        *(char *)(cmd_param + 4) = 1;
        elem_z = elem[2];
        *(char *)(cmd_param + 5) = (atom[1] == 1);
        *(int *)(cmd_param + 8) = elem[0];
        *(int *)(cmd_param + 0xc) = elem[1];
        *(int *)(cmd_param + 0x10) = elem_z;
        *(int *)(cmd_param + 0x14) = elem[3];
        result = actor_move_to_point(actor_handle, (float *)(cmd_param + 8),
                                     elem[3], -1);
        if (result != 0) {
          if (*(char *)(cmd_param + 5) != 0) {
            FUN_0002a330(actor_handle);
          }
          if (*atom == 2 && (mode = atom[7], mode >= 0)) {
            if ((int)mode < *(int *)(cmd_list + 0x3c)) {
              elem =
                (int *)tag_block_get_element(cmd_list + 0x3c, (int)mode, 0x14);
              *(char *)(cmd_param + 0x18) = 1;
              *(int *)(cmd_param + 0x1c) = elem[0];
              *(int *)(cmd_param + 0x20) = elem[1];
              *(int *)(cmd_param + 0x24) = elem[2];
            }
          }
        }
      }
    }
    break;

  case 4:
  case 0x17:
  case 0x18:
  case 0x19:
    if (cmd_param == 0) {
      break;
    }
    radius = *(float *)(atom + 2);
    fp_index = -1;
    prop_handle = -1;
    object_index = -1;
    if (cmd_type == 4) {
      mode = atom[6];
      if (mode >= 0 && (int)mode < *(int *)(cmd_list + 0x3c)) {
        radius = *(float *)(atom + 2);
        fp_index = mode;
      }
    } else if (cmd_type == 0x17) {
      mode = atom[6];
      if (mode >= 0 && (int)mode < *(int *)(cmd_list + 0x3c)) {
        mode2 = atom[7];
        if (mode2 >= 0 && (int)mode2 < *(int *)(cmd_list + 0x3c)) {
          fp_index = FUN_00017940(mode, (short)(mode2 + 1));
          if (*(float *)(atom + 2) == *(float *)0x2533c0 &&
              *(float *)(atom + 4) == *(float *)0x2533c0) {
            radius = FUN_000121e0(*(float *)(actr_def + 0xec),
                                  *(float *)(actr_def + 0xf0));
          } else {
            radius = FUN_000121e0(*(float *)(atom + 2), *(float *)(atom + 4));
          }
        }
      }
    } else if (cmd_type == 0x18) {
      best = 3.4028235e+38f;
      FUN_00064540(prop_iter, actor_handle);
      prop = FUN_00064570(prop_iter);
      if (prop != 0) {
        do {
          if (*(short *)(prop + 0x24) >= 2 && *(short *)(prop + 0x24) <= 3 &&
              *(char *)(prop + 0x12e) != 0 && *(float *)(prop + 0x11c) < best) {
            best = *(float *)(prop + 0x11c);
            prop_handle = prop_iter[0];
          }
          prop = FUN_00064570(prop_iter);
        } while (prop != 0);
        if (prop_handle != -1) {
          goto LAB_look_merge;
        }
      }
      best = 3.4028235e+38f;
      data_iterator_new(&iter, player_data);
      ent = (char *)data_iterator_next(&iter);
      while (ent != 0) {
        if (*(int *)(ent + 0x34) != -1) {
          unit_get_head_position(*(int *)(ent + 0x34), pos);
          d = distance_squared3d(pos, (float *)(actor + 0x120));
          if (d < best) {
            object_index = *(int *)(ent + 0x34);
            best = d;
          }
        }
        ent = (char *)data_iterator_next(&iter);
      }
    } else { /* 0x19 */
      mode = atom[0xc];
      if (mode >= 0 &&
          (int)mode < *(int *)((char *)global_scenario_get() + 0x204)) {
        t = object_name_list_get_handle(mode);
        if (object_try_and_get_and_verify_type(t, 3) != 0) {
          prop_handle = prop_get_active_by_unit_index(actor_handle, t);
          object_index = t;
        }
      }
    }
  LAB_look_merge:
    if (radius > *(float *)0x2533c0 &&
        (prop_handle != -1 || object_index != -1 ||
         ((short)fp_index >= 0 &&
          (int)(short)fp_index < *(int *)(cmd_list + 0x3c)))) {
      mode = atom[1];
      style = 1;
      if (mode == 1) {
        style = 5;
      } else if (mode == 2) {
        style = 2;
      } else if (mode == 4) {
        style = 7;
      } else if (mode == 3) {
        style = 8;
      }
      if (prop_handle == -1) {
        if (object_index == -1) {
          elem = (int *)tag_block_get_element(cmd_list + 0x3c,
                                              (int)(short)fp_index, 0x14);
          *(short *)look_target = 3;
          *(int *)(look_target + 4) = elem[0];
          *(int *)(look_target + 8) = elem[1];
          *(int *)(look_target + 0xc) = elem[2];
        } else {
          *(short *)look_target = 3;
          unit_get_head_position(object_index, (float *)(look_target + 4));
        }
      } else {
        *(short *)look_target = 1;
        *(int *)(look_target + 4) = prop_handle;
      }
      FUN_00027a60(actor_handle, 0xd, (short)style, (short *)look_target);
      *(short *)(state_data + 2) = (short)(int)(radius * *(float *)0x253394);
      result = 1;
    }
    break;

  case 3:
    if (unit_handle == *(int *)(actor + 0x18)) {
      *(int *)(state_data + 0x18) = *(int *)(actor + 0x12c);
      *(int *)(state_data + 0x1c) = *(int *)(actor + 0x130);
      *(int *)(state_data + 0x20) = *(int *)(actor + 0x134);
    } else {
      object_get_world_position(unit_handle, (vector3_t *)(state_data + 0x18));
    }
    mode = atom[6];
    if (mode >= 0) {
      if ((int)mode >= *(int *)(cmd_list + 0x3c)) {
        goto LAB_move_angle;
      }
      elem = (int *)tag_block_get_element(cmd_list + 0x3c, (int)mode, 0x14);
      FUN_00012140((float *)(state_data + 0x18), (float *)elem,
                   (float *)(state_data + 0xc));
      if (!(normalize3d((float *)(state_data + 0xc)) > *(float *)0x2533c0)) {
        result = 0;
        break;
      }
    } else {
    LAB_move_angle:
      if (*(float *)(atom + 4) < *(float *)0x2533c0 ||
          *(float *)0x253d50 <= *(float *)(atom + 4)) {
        break;
      }
      vector3d_from_angle((float *)(state_data + 0xc),
                          *(float *)(atom + 4) * *(float *)0x253d4c);
    }
    mode = atom[1];
    result = 1;
    if (mode < 0 || mode > 3) {
      *(short *)(state_data + 8) = -1;
    } else {
      *(short *)(state_data + 8) = mode;
    }
    if (unit_handle == *(int *)(actor + 0x18)) {
      FUN_0002f1a0(actor_handle);
    }
    state_data[5] = (char)((state_data[5] & 0xfd) | 1);
    break;

  case 0x16:
    mode = atom[1];
    if (mode < 0 || mode > 3) {
      *(short *)(state_data + 8) = 0;
    } else {
      *(short *)(state_data + 8) = mode;
    }
    FUN_00017960(state_data, actor_handle, unit_handle);
    *(short *)(state_data + 2) =
      (short)(int)(*(float *)(atom + 2) * *(float *)0x253394);
    state_data[5] = state_data[5] | 3;
    result = 1;
    break;

  case 10:
    if (unit_handle == *(int *)(actor + 0x18) &&
        *(int *)(actor + 0x158) != -1) {
      break;
    }
    state_data[5] = (char)((state_data[5] & 0xe7) | 4);
    if (unit_handle == *(int *)(actor + 0x18)) {
      if (*(char *)(actor + 0x504) == 0) {
        flag = 0;
      } else {
        flag = (*(short *)(actor + 0x50a) == 0);
      }
    } else {
      obj = (char *)object_get_and_verify_type(unit_handle, 3);
      if (*(int *)(obj + 0xcc) == -1) {
        flag = (FUN_00013070((float *)(obj + 0x18), (float *)(obj + 0x24)) >
                *(float *)0x253d48);
      } else {
        flag = 0;
      }
    }
    *(short *)(state_data + 2) = 0x3c;
    *(unsigned short *)(state_data + 8) =
      (unsigned short)(((flag != 0) - 1) & 10);
    result = 1;
    break;

  case 0xb:
    if (unit_handle == *(int *)(actor + 0x18) &&
        *(int *)(actor + 0x158) != -1) {
      break;
    }
    state_data[5] = (char)((state_data[5] & 0xf7) | 0x14);
    *(short *)(state_data + 8) = 0;
    *(int *)(state_data + 0xc) = *(int *)(atom + 2);
    *(int *)(state_data + 0x10) = *(int *)(atom + 4);
    *(short *)(state_data + 2) = 0x3c;
    result = 1;
    break;

  case 5:
    if (cmd_param == 0 || (mode = atom[1], mode < 0) || mode > 3) {
      break;
    }
    *(short *)(cmd_param + 2) = mode;
    result = 1;
    break;

  case 6:
    if (cmd_param != 0) {
      result = 1;
      *(char *)cmd_param = (atom[1] == 1);
    }
    break;

  case 0x11:
    if (atom[1] == 0) {
      state_data[4] = state_data[4] | 1;
      result = 1;
    } else {
      state_data[4] = (char)(state_data[4] & 0xfe);
      result = 1;
    }
    break;

  case 0x12:
    if (unit_handle != *(int *)(actor + 0x18)) {
      break;
    }
    *(char *)(actor + 0x9e) = (atom[1] == 0);
    result = 1;
    break;

  case 0x13:
    result = 1;
    break;

  case 0x1a:
    if (cmd_param != 0 && *(float *)(atom + 2) > *(float *)0x2533c0) {
      *(char *)(cmd_param + 0x28) = 1;
      *(int *)(cmd_param + 0x2c) = *(int *)(atom + 2);
      result = 1;
    }
    break;

  case 0xf:
    if (cmd_param == 0) {
      break;
    }
    *(char *)(cmd_param + 0x30) = 0;
    switch (atom[1]) {
    case 0:
      *(char *)(cmd_param + 0x30) = 1;
      result = *(char *)(cmd_param + 0x30);
      *(short *)(cmd_param + 0x32) = 0;
      *(short *)(cmd_param + 0x34) = 0x2a;
      break;
    case 1:
      *(char *)(cmd_param + 0x30) = 1;
      result = *(char *)(cmd_param + 0x30);
      *(short *)(cmd_param + 0x32) = 4;
      *(short *)(cmd_param + 0x34) = 0x29;
      break;
    case 2:
      *(char *)(cmd_param + 0x30) = 1;
      result = *(char *)(cmd_param + 0x30);
      *(short *)(cmd_param + 0x32) = 5;
      *(short *)(cmd_param + 0x34) = 0x29;
      break;
    case 3:
      *(char *)(cmd_param + 0x30) = 1;
      result = *(char *)(cmd_param + 0x30);
      *(short *)(cmd_param + 0x32) = 6;
      *(short *)(cmd_param + 0x34) = -1;
      break;
    case 4:
      *(char *)(cmd_param + 0x30) = 1;
      result = *(char *)(cmd_param + 0x30);
      *(short *)(cmd_param + 0x32) = 7;
      *(short *)(cmd_param + 0x34) = -1;
      break;
    case 5:
      *(char *)(cmd_param + 0x30) = 1;
      result = *(char *)(cmd_param + 0x30);
      *(short *)(cmd_param + 0x32) = 8;
      *(short *)(cmd_param + 0x34) = 0x2c;
      break;
    case 6:
      *(char *)(cmd_param + 0x30) = 1;
      result = *(char *)(cmd_param + 0x30);
      *(short *)(cmd_param + 0x32) = 9;
      *(short *)(cmd_param + 0x34) = 0x2c;
      break;
    case 7:
      *(char *)(cmd_param + 0x30) = 1;
      result = *(char *)(cmd_param + 0x30);
      *(short *)(cmd_param + 0x32) = 10;
      *(short *)(cmd_param + 0x34) = 0x2c;
      break;
    case 8:
      *(char *)(cmd_param + 0x30) = 1;
      result = *(char *)(cmd_param + 0x30);
      *(short *)(cmd_param + 0x32) = 0xb;
      *(short *)(cmd_param + 0x34) = 0x2c;
      break;
    case 9:
      *(short *)(cmd_param + 0x34) = 0x26;
      goto LAB_cue_common;
    case 10:
      *(short *)(cmd_param + 0x34) = 0x27;
    LAB_cue_common:
      *(short *)(cmd_param + 0x32) = -1;
      *(char *)(cmd_param + 0x30) = 1;
      /* FALLTHROUGH */
    default:
      result = *(char *)(cmd_param + 0x30);
      break;
    }
    break;

  case 7:
    if (cmd_param != 0 && (mode = atom[6], mode >= 0)) {
      if ((int)mode < *(int *)(cmd_list + 0x3c)) {
        elem = (int *)tag_block_get_element(cmd_list + 0x3c, (int)mode, 0x14);
        *(char *)(cmd_param + 0x36) = 1;
        *(int *)(cmd_param + 0x38) = elem[0];
        *(int *)(cmd_param + 0x3c) = elem[1];
        *(int *)(cmd_param + 0x40) = elem[2];
        *(int *)(cmd_param + 0x44) = *(int *)(atom + 2);
        result = 1;
      }
    }
    break;

  case 8:
    if (cmd_param == 0 || *(short *)(actv_def + 0x180) == -1 ||
        (mode = atom[6], mode < 0)) {
      break;
    }
    if ((int)mode >= *(int *)(cmd_list + 0x3c)) {
      break;
    }
    elem = (int *)tag_block_get_element(cmd_list + 0x3c, (int)mode, 0x14);
    unit_set_grenade_count(*(int *)(actor + 0x18),
                           *(unsigned short *)(actv_def + 0x180), 1);
    *(char *)(cmd_param + 0x49) = 0;
    *(char *)(cmd_param + 0x48) = 0;
    *(int *)(cmd_param + 0x4c) = elem[0];
    *(int *)(cmd_param + 0x50) = elem[1];
    *(int *)(cmd_param + 0x54) = elem[2];
    *(short *)(cmd_param + 0x4a) = 0;
    mode = atom[1];
    if (mode >= 0 && mode < 3) {
      *(short *)(cmd_param + 0x4a) = mode;
    }
    *(short *)(state_data + 2) = 0x3c;
    result = 1;
    break;

  case 9:
    if (unit_handle == *(int *)(actor + 0x18)) {
      count = 0;
      vmode = -1;
      object_iterator_new(obj_iter, 2, 0);
      if (object_iterator_next(obj_iter) != 0) {
        do {
          object_get_world_position(obj_iter[2], (vector3_t *)pos);
          d = distance_squared3d((float *)(actor + 0x12c), pos);
          if (*(float *)(atom + 2) == *(float *)0x2533c0 ||
              d < *(float *)(atom + 2) * *(float *)(atom + 2)) {
            near_list[count * 2] = d;
            *(int *)&near_list[count * 2 + 1] = obj_iter[2];
            count = (short)(count + 1);
            if (count >= 16) {
              break;
            }
          }
        } while (object_iterator_next(obj_iter) != 0);
        if (count > 1) {
          qsort(near_list, (int)count, 8,
                (int (*)(const void *, const void *))FUN_00016960);
        }
      }
      umode = *(unsigned short *)(atom + 1);
      if ((short)umode >= 0 && (short)umode < 5) {
        vmode = umode;
      }
      i = 0;
      if (count > 0) {
        do {
          if (actor_action_try_to_enter_vehicle(actor_handle,
                                                *(int *)&near_list[i * 2 + 1],
                                                (int)"", vmode, 0, 0) != 0) {
            state_data[4] = state_data[4] | 4;
            result = 1;
            goto LAB_done;
          }
          i = (short)(i + 1);
        } while (i < count);
      }
    }
    break;

  case 0xd:
    mode = atom[8];
    if (mode == -1) {
      break;
    }
    elem = (int *)tag_block_get_element((char *)global_scenario_get() + 0x444,
                                        (int)mode, 0x3c);
    anim_tag = elem[0xb];
    loop_flag = 0;
    aim_flag = 0;
    do_flag = 1;
    if (anim_tag == -1) {
      obj = (char *)object_get_and_verify_type(unit_handle, 3);
      anim_tag = *(int *)((char *)tag_get(0x756e6974, *(int *)obj) + 0x44);
    }
    switch (atom[1]) {
    case 1:
      loop_flag = 1;
      break;
    case 2:
      aim_flag = 1;
      loop_flag = 1;
      break;
    case 3:
      do_flag = 0;
      break;
    case 4:
      do_flag = 0;
      loop_flag = 1;
      break;
    case 5:
      do_flag = 0;
      aim_flag = 1;
      loop_flag = 1;
      break;
    default:
      break;
    }
    if (FUN_001ac180(unit_handle, anim_tag, elem, do_flag) == 0) {
      break;
    }
    obj = (char *)object_try_and_get_and_verify_type(unit_handle, 1);
    if (obj != 0) {
      if (loop_flag != 0) {
        *(unsigned int *)(obj + 0x424) = *(unsigned int *)(obj + 0x424) | 4;
      } else {
        *(unsigned int *)(obj + 0x424) =
          *(unsigned int *)(obj + 0x424) & 0xfffffffb;
      }
      if (aim_flag != 0) {
        *(unsigned int *)(obj + 0x424) = *(unsigned int *)(obj + 0x424) | 8;
      } else {
        *(unsigned int *)(obj + 0x424) =
          *(unsigned int *)(obj + 0x424) & 0xfffffff7;
      }
    }
    result = 1;
    break;

  case 0xe:
    if (atom[10] >= 0) {
      mode = atom[10];
      if ((int)mode < *(int *)((char *)global_scenario_get() + 0x45c)) {
        anim_idx = FUN_000936b0(
          global_scenario_get(),
          tag_block_get_element((char *)global_scenario_get() + 0x45c,
                                (int)mode, 0x28));
        if (anim_idx != -1) {
          result = recorded_animation_play(unit_handle, anim_idx);
        }
      }
    }
    break;

  case 0xc:
    if (atom[9] >= 0) {
      mode = atom[9];
      if ((int)mode < *(int *)((char *)global_scenario_get() + 0x450)) {
        result = hs_wake_by_name(tag_block_get_element(
          (char *)global_scenario_get() + 0x450, (int)mode, 0x28));
      }
    }
    break;

  case 0x14:
    mode = atom[0xb];
    if (mode < 0 || (int)mode >= *(int *)(cmd_list + 0x30) ||
        (int)mode == (int)(unsigned char)*state_data) {
      break;
    }
    result = 1;
    break;

  case 0x15:
    obj = (char *)object_get_and_verify_type(unit_handle, 3);
    if (atom[1] == 1) {
      *(unsigned char *)(obj + 0xb6) = *(unsigned char *)(obj + 0xb6) | 0x40;
      result = 1;
    } else {
      *(unsigned char *)(obj + 0xb6) = *(unsigned char *)(obj + 0xb6) | 0x20;
      result = 1;
    }
    break;

  case 0x10:
    seat_slot = *(unsigned short *)(atom + 1);
    unit_out = -1;
    seat_count =
      FUN_001a68d0(unit_handle, 6, 1, 1, 0, (short *)&seat_slot, &unit_out);
    if (seat_count < 1) {
      break;
    }
    csmemset(comm, 0, 0x30);
    *(short *)(comm + 2) = (short)seat_slot;
    *(int *)(comm + 4) = unit_out;
    *(short *)comm = 6;
    ai_communication_packet_new(comm + 0x10);
    FUN_001a6ef0(unit_handle, seat_count, comm);
    result = 1;
    break;

  case 0x1b:
    mode = atom[6];
    if (mode < 0) {
      break;
    }
    if ((int)mode >= *(int *)(cmd_list + 0x3c)) {
      break;
    }
    elem = (int *)tag_block_get_element(cmd_list + 0x3c, (int)mode, 0x14);
    units_debug_get_closest_unit(unit_handle, pos);
    mode = atom[7];
    if (mode >= 0 && (int)mode < *(int *)(cmd_list + 0x3c)) {
      elem2 = (int *)tag_block_get_element(cmd_list + 0x3c, (int)mode, 0x14);
      obj = (char *)object_try_and_get_and_verify_type(unit_handle, 1);
      if (obj == 0) {
        bipd = 0;
      } else {
        bipd = (char *)tag_get(0x62697064, *(int *)obj);
      }
      bipd_null = (bipd == 0);
      FUN_00012140((float *)elem, (float *)elem2, pos);
      if (bipd_null || (*(unsigned char *)(bipd + 0x2f4) & 0x44) == 0) {
        actr_def = 0;
        if (magnitude3d(pos) == *(float *)0x2533c0) {
          goto LAB_teleport_face;
        }
      } else {
        if (normalize3d(pos) == *(float *)0x2533c0) {
        LAB_teleport_face:
          units_debug_get_closest_unit(unit_handle, pos);
        }
      }
    }
    object_set_position(unit_handle, (float *)elem, pos, 0);
    object_reset(unit_handle);
    object_update_children_recursive(unit_handle);
    if (unit_handle == *(int *)(actor + 0x18)) {
      FUN_0003bde0(actor_handle, *(int *)(actor + 0x18), actor + 0x120);
      FUN_0002f1a0(actor_handle);
    }
    result = 1;
    break;

  default:
    break;
  }

LAB_done:
  if (*(char *)0x5aca5b == 0) {
    return result;
  }
  if (*(unsigned int *)(actor + 0x34) == 0xffffffff) {
    csstrcpy(name_buf, "<no encounter>");
  } else {
    enc = (char *)tag_block_get_element(
      (char *)global_scenario_get() + 0x42c,
      (int)(*(unsigned int *)(actor + 0x34) & 0xffff), 0xb0);
    sq = (char *)tag_block_get_element(enc + 0x80,
                                       (int)*(short *)(actor + 0x3a), 0xe8);
    crt_sprintf(name_buf, "%s/%s", enc, sq);
  }
  FUN_00017120(global_scenario_get(), atom, (char *)0x5ab100, 0x100);
  status = "";
  if (result == 0) {
    status = " FAILED";
  }
  error(2, "%s: %s #%d%s: %s", name_buf, cmd_list, (int)(short)atom_seq, status,
        (char *)0x5ab100);
  return result;
}

/* FUN_00018b90 (0x18b90) — XBE naked draft (batch 69). */
#if defined(__clang__)
static void *(*const b18b90_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static scenario_t * (*const b18b90_c18e380)(void) = global_scenario_get;
static void *(*const b18b90_elem)(void *, int, int) = tag_block_get_element;
static int (*const b18b90_c2a3f0)(int actor_handle) = FUN_0002a3f0;
static float (*const b18b90_c3bd50)(int actor_handle) = actor_destination_tolerance;
static void (*const b18b90_c12140)(float *a, float *b, float *result) = FUN_00012140;
static float (*const b18b90_c12170)(float *vector) = FUN_00012170;
static void *(*const b18b90_get)(int, int) = object_get_and_verify_type;
static void (*const b18b90_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b18b90_exitfn)(int) = system_exit;
static float (*const b18b90_norm)(float *) = normalize3d;
static float (*const b18b90_mag)(float *) = magnitude3d;
static void (*const b18b90_c2f1a0)(int actor_handle) = FUN_0002f1a0;
static vector3_t * (*const b18b90_c1412f0)(int object_handle, vector3_t *out_position) = object_get_world_position;
static float (*const b18b90_c121a0)(const float *a, const float *b) = distance_squared3d;
static void *(*const b18b90_tag)(int, int) = tag_get;
static void (*const b18b90_ftol)(void) = FUN_001d9068;
static char (*const b18b90_c1ac650)(int unit_handle) = unit_flying_through_air;
static bool (*const b18b90_c1a9ad0)(int unit_handle) = unit_is_busy;
static char (*const b18b90_c21e50)(int actor_handle, short param_2, float *param_3, int param_4, int param_5) = FUN_00021e50;
static char (*const b18b90_c94ff0)(int unit_handle) = recorded_animation_controlling_unit;

__attribute__((naked, noinline))
bool FUN_00018b90(int unit_handle __attribute__((unused)), int actor_handle __attribute__((unused)), short scenario_index __attribute__((unused)), char *output __attribute__((unused)), void *command __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x20, %%esp\n\t"
      "movl 0x6325a4, %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl %%eax, %%edi\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movswl 0xc(%%ebp), %%edx\n\t"
      "addl $8, %%esp\n\t"
      "pushl $0x60\n\t"
      "pushl %%edx\n\t"
      "movl %%eax, %%esi\n\t"
      "call *%[c18e380]\n\t"
      "addl $0x438, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "movzbl (%%ecx), %%ecx\n\t"
      "movl 0x30(%%eax), %%edx\n\t"
      "addl $0x30, %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl %%edx, %%ecx\n\t"
      "movb $1, %%bl\n\t"
      "jge .LFUN_00018b90_33\n\t"
      "pushl $0x20\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movswl (%%eax), %%ecx\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl $0x1b, %%ecx\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "ja .LFUN_00018b90_33\n\t"
      "movzbl 0x190f0(%%ecx), %%edx\n\t"
      "jmp *.LFUN_00018b90_jt(,%%edx,4)\n\t"
      ".LFUN_00018b90_1:\n\t"
      "cmpl 0x18(%%esi), %%edi\n\t"
      "jne .LFUN_00018b90_32\n\t"
      "movl 0x14(%%ebp), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "je .LFUN_00018b90_32\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c2a3f0]\n\t"
      "movb %%al, %%bl\n\t"
      "addl $4, %%esp\n\t"
      "testb %%bl, %%bl\n\t"
      "jne .LFUN_00018b90_4\n\t"
      "movb 0x5(%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00018b90_4\n\t"
      "movb 0x4(%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00018b90_4\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c3bd50]\n\t"
      "fstps 0xc(%%ebp)\n\t"
      "leal -0x14(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal 0x8(%%edi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal 0x12c(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c12140]\n\t"
      "leal -0x14(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c12170]\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fmuls 0xc(%%ebp)\n\t"
      "addl $0x14, %%esp\n\t"
      "fld %%st(1)\n\t"
      "fcompp\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00018b90_2\n\t"
      "fstp %%st(0)\n\t"
      "jmp .LFUN_00018b90_3\n\t"
      ".LFUN_00018b90_2:\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fadds 0x253398\n\t"
      "fld %%st(0)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fxch %%st(1)\n\t"
      "fxch %%st(2)\n\t"
      "fcompp\n\t"
      "fnstsw %%ax\n\t"
      "fstp %%st(0)\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00018b90_4\n\t"
      "movl 0x18(%%esi), %%ecx\n\t"
      "pushl $3\n\t"
      "pushl %%ecx\n\t"
      "call *%[get]\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fmuls 0x1c(%%eax)\n\t"
      "addl $0x18, %%eax\n\t"
      "flds -0xc(%%ebp)\n\t"
      "addl $8, %%esp\n\t"
      "fmuls 0x8(%%eax)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fmuls (%%eax)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00018b90_4\n\t"
      ".LFUN_00018b90_3:\n\t"
      "movb $1, %%bl\n\t"
      ".LFUN_00018b90_4:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "cmpw $2, (%%eax)\n\t"
      "je .LFUN_00018b90_5\n\t"
      "cmpw $0, 0x2(%%eax)\n\t"
      "jne .LFUN_00018b90_7\n\t"
      ".LFUN_00018b90_5:\n\t"
      "movb 0x504(%%esi), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "je .LFUN_00018b90_6\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "movw $0xa, 0x2(%%edx)\n\t"
      ".LFUN_00018b90_6:\n\t"
      "testb %%bl, %%bl\n\t"
      "je .LFUN_00018b90_30\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "cmpw $0, 0x2(%%ecx)\n\t"
      "jne .LFUN_00018b90_30\n\t"
      "movb $1, %%bl\n\t"
      "jmp .LFUN_00018b90_8\n\t"
      ".LFUN_00018b90_7:\n\t"
      "testb %%bl, %%bl\n\t"
      "je .LFUN_00018b90_33\n\t"
      ".LFUN_00018b90_8:\n\t"
      "movb 0x18(%%edi), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "je .LFUN_00018b90_12\n\t"
      "cmpw $2, (%%eax)\n\t"
      "je .LFUN_00018b90_9\n\t"
      "pushl $1\n\t"
      "pushl $0x3d7\n\t"
      "pushl $0x253758\n\t"
      "pushl $0x253d58\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00018b90_9:\n\t"
      "movb 0x99(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00018b90_10\n\t"
      "leal -0x14(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "addl $0x1c, %%edi\n\t"
      "leal 0x12c(%%esi), %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[c12140]\n\t"
      "leal -0x14(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[norm]\n\t"
      "fcomps 0x2533c0\n\t"
      "addl $0x10, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00018b90_12\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fmuls 0x178(%%esi)\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fmuls 0x17c(%%esi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds -0x14(%%ebp)\n\t"
      "jmp .LFUN_00018b90_11\n\t"
      ".LFUN_00018b90_10:\n\t"
      "flds 0x1c(%%edi)\n\t"
      "leal -0x8(%%ebp), %%edx\n\t"
      "fsubs 0x12c(%%esi)\n\t"
      "pushl %%edx\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "flds 0x20(%%edi)\n\t"
      "fsubs 0x130(%%esi)\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "call *%[mag]\n\t"
      "fcomps 0x2533c0\n\t"
      "addl $4, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00018b90_12\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fmuls 0x178(%%esi)\n\t"
      "flds -0x8(%%ebp)\n\t"
      ".LFUN_00018b90_11:\n\t"
      "fmuls 0x174(%%esi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fcomps 0x253d54\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .LFUN_00018b90_30\n\t"
      ".LFUN_00018b90_12:\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c2f1a0]\n\t"
      "addl $4, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00018b90_13:\n\t"
      "cmpl 0x18(%%esi), %%edi\n\t"
      "jne .LFUN_00018b90_14\n\t"
      "addl $0x12c, %%esi\n\t"
      "movl (%%esi), %%ecx\n\t"
      "movl 0x4(%%esi), %%edx\n\t"
      "movl 0x8(%%esi), %%eax\n\t"
      "movl %%ecx, -0x14(%%ebp)\n\t"
      "movl %%edx, -0x10(%%ebp)\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "jmp .LFUN_00018b90_15\n\t"
      ".LFUN_00018b90_14:\n\t"
      "leal -0x14(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edi\n\t"
      "call *%[c1412f0]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_00018b90_15:\n\t"
      "movl 0x10(%%ebp), %%esi\n\t"
      "leal -0x20(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x14(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal 0x18(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c12140]\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fmuls 0x10(%%esi)\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "flds -0x18(%%ebp)\n\t"
      "addl $0xc, %%esp\n\t"
      "fmuls 0x14(%%esi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds -0x20(%%ebp)\n\t"
      "fmuls 0xc(%%esi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fcomps 0x4(%%edx)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .LFUN_00018b90_32\n\t"
      "popl %%edi\n\t"
      "xorb %%bl, %%bl\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00018b90_16:\n\t"
      "cmpl 0x18(%%esi), %%edi\n\t"
      "jne .LFUN_00018b90_32\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_00018b90_32\n\t"
      "cmpw $2, 0x60c(%%esi)\n\t"
      "jne .LFUN_00018b90_17\n\t"
      "leal 0x610(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "addl $0x38, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c121a0]\n\t"
      "fcomps 0x25337c\n\t"
      "addl $8, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .LFUN_00018b90_19\n\t"
      ".LFUN_00018b90_17:\n\t"
      "movl 0x5c(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x61637476\n\t"
      "call *%[tag]\n\t"
      "flds 0x84(%%eax)\n\t"
      "fmuls 0x253394\n\t"
      "addl $8, %%esp\n\t"
      "call *%[ftol]\n\t"
      "cmpw $0x3c, %%ax\n\t"
      "movswl %%ax, %%eax\n\t"
      "jg .LFUN_00018b90_18\n\t"
      "movl $0x3c, %%eax\n\t"
      ".LFUN_00018b90_18:\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "movw %%ax, 0x2(%%ecx)\n\t"
      ".LFUN_00018b90_19:\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "cmpw $0, 0x2(%%edx)\n\t"
      "popl %%edi\n\t"
      "sete %%bl\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00018b90_20:\n\t"
      "movl 0x10(%%ebp), %%ebx\n\t"
      "testb $4, 0x5(%%ebx)\n\t"
      "je .LFUN_00018b90_32\n\t"
      "cmpl 0x18(%%esi), %%edi\n\t"
      "jne .LFUN_00018b90_21\n\t"
      "movb 0x15c(%%esi), %%al\n\t"
      "jmp .LFUN_00018b90_22\n\t"
      ".LFUN_00018b90_21:\n\t"
      "pushl %%edi\n\t"
      "call *%[c1ac650]\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_00018b90_22:\n\t"
      "testb $8, 0x5(%%ebx)\n\t"
      "je .LFUN_00018b90_23\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00018b90_23\n\t"
      "movw $0, 0x2(%%ebx)\n\t"
      ".LFUN_00018b90_23:\n\t"
      "cmpw $0, 0x2(%%ebx)\n\t"
      "popl %%edi\n\t"
      "sete %%bl\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00018b90_24:\n\t"
      "cmpl 0x18(%%esi), %%edi\n\t"
      "jne .LFUN_00018b90_32\n\t"
      "movl 0x14(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_00018b90_32\n\t"
      "movb 0x49(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00018b90_25\n\t"
      "pushl $3\n\t"
      "pushl %%edi\n\t"
      "call *%[get]\n\t"
      "movb 0x23d(%%eax), %%al\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "negb %%al\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "sbbl %%eax, %%eax\n\t"
      "andl $0x1e, %%eax\n\t"
      "movw %%ax, 0x2(%%ecx)\n\t"
      "movl %%ecx, %%eax\n\t"
      "cmpw $0, 0x2(%%eax)\n\t"
      "sete %%bl\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00018b90_25:\n\t"
      "pushl %%edi\n\t"
      "call *%[c1a9ad0]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00018b90_26\n\t"
      "leal 0x4c(%%esi), %%edx\n\t"
      "movl (%%edx), %%eax\n\t"
      "movl 0x4(%%edx), %%ecx\n\t"
      "movl 0x8(%%edx), %%edx\n\t"
      "movl %%ecx, -0x1c(%%ebp)\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x4a(%%esi), %%cx\n\t"
      "pushl $-1\n\t"
      "movl %%eax, -0x20(%%ebp)\n\t"
      "pushl $-1\n\t"
      "leal -0x20(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl %%edx, -0x18(%%ebp)\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c21e50]\n\t"
      "addl $0x14, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00018b90_26\n\t"
      "movb $1, 0x48(%%esi)\n\t"
      ".LFUN_00018b90_26:\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "cmpw $0, 0x2(%%eax)\n\t"
      "popl %%edi\n\t"
      "sete %%bl\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00018b90_27:\n\t"
      "pushl $3\n\t"
      "pushl %%edi\n\t"
      "call *%[get]\n\t"
      "movb 0x253(%%eax), %%cl\n\t"
      "addl $8, %%esp\n\t"
      "cmpb $0x1c, %%cl\n\t"
      "popl %%edi\n\t"
      "setne %%bl\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00018b90_28:\n\t"
      "pushl %%edi\n\t"
      "call *%[c94ff0]\n\t"
      "addl $4, %%esp\n\t"
      "movb %%al, %%bl\n\t"
      "negb %%bl\n\t"
      "sbbb %%bl, %%bl\n\t"
      "popl %%edi\n\t"
      "incb %%bl\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00018b90_29:\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_00018b90_32\n\t"
      "movb 0x30(%%eax), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "je .LFUN_00018b90_32\n\t"
      ".LFUN_00018b90_30:\n\t"
      "popl %%edi\n\t"
      "xorb %%bl, %%bl\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00018b90_31:\n\t"
      "movswl 0x2(%%eax), %%eax\n\t"
      "subl $0, %%eax\n\t"
      "je .LFUN_00018b90_36\n\t"
      "decl %%eax\n\t"
      "je .LFUN_00018b90_35\n\t"
      "decl %%eax\n\t"
      "jne .LFUN_00018b90_32\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "movb 0x4(%%ecx), %%al\n\t"
      "testb $8, %%al\n\t"
      "je .LFUN_00018b90_34\n\t"
      "andb $0xe7, %%al\n\t"
      "movb %%al, 0x4(%%ecx)\n\t"
      ".LFUN_00018b90_32:\n\t"
      "movb $1, %%bl\n\t"
      ".LFUN_00018b90_33:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00018b90_34:\n\t"
      "orb $0x10, %%al\n\t"
      "popl %%edi\n\t"
      "xorb %%bl, %%bl\n\t"
      "movb %%al, 0x4(%%ecx)\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00018b90_35:\n\t"
      "cmpw $7, 0x6e(%%esi)\n\t"
      "popl %%edi\n\t"
      "setge %%bl\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00018b90_36:\n\t"
      "cmpw $0, 0x6e(%%esi)\n\t"
      "popl %%edi\n\t"
      "setg %%bl\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00018b90_37:\n\t"
      "pushl $3\n\t"
      "pushl %%edi\n\t"
      "call *%[get]\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $6, 0x338(%%eax)\n\t"
      "popl %%edi\n\t"
      "setne %%bl\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_00018b90_jt:\n\t"
      ".long .LFUN_00018b90_26\n\t"
      ".long .LFUN_00018b90_1\n\t"
      ".long .LFUN_00018b90_13\n\t"
      ".long .LFUN_00018b90_32\n\t"
      ".long .LFUN_00018b90_16\n\t"
      ".long .LFUN_00018b90_24\n\t"
      ".long .LFUN_00018b90_20\n\t"
      ".long .LFUN_00018b90_27\n\t"
      ".long .LFUN_00018b90_28\n\t"
      ".long .LFUN_00018b90_29\n\t"
      ".long .LFUN_00018b90_37\n\t"
      ".long .LFUN_00018b90_31\n\t"
      ".text\n\t"
      :
      : [dget] "m"(b18b90_dget), [c18e380] "m"(b18b90_c18e380), [elem] "m"(b18b90_elem), [c2a3f0] "m"(b18b90_c2a3f0), [c3bd50] "m"(b18b90_c3bd50), [c12140] "m"(b18b90_c12140), [c12170] "m"(b18b90_c12170), [get] "m"(b18b90_get), [assert] "m"(b18b90_assert), [exitfn] "m"(b18b90_exitfn), [norm] "m"(b18b90_norm), [mag] "m"(b18b90_mag), [c2f1a0] "m"(b18b90_c2f1a0), [c1412f0] "m"(b18b90_c1412f0), [c121a0] "m"(b18b90_c121a0), [tag] "m"(b18b90_tag), [ftol] "m"(b18b90_ftol), [c1ac650] "m"(b18b90_c1ac650), [c1a9ad0] "m"(b18b90_c1a9ad0), [c21e50] "m"(b18b90_c21e50), [c94ff0] "m"(b18b90_c94ff0)
      : "memory");
}
#else
#error "FUN_00018b90: clang naked draft required"
#endif


/* FUN_00019110 (0x19110)
 * Action-obey command-list step callback (prop-interest update).
 *
 * Called by actor_look_compute_prop_interest via FUN_000192b0.
 * Steps through atoms in the encounter's command list:
 *   - Validates the current atom via FUN_00018b90 (if cVar5 set).
 *   - If validated, advances the atom index and calls FUN_000169a0 to execute
 *     the atom step.
 *   - Sets the exhausted flag (state_data[4] | 0x2) when the index reaches
 *     the atom count.
 *   - When the loop exits without exhausting, writes 0 to *finished_ref.
 *     Asserts if finished_ref is NULL.
 *
 * Confirmed: param_1=actor_handle (EDI), param_2=unit_handle (EAX@<eax> of
 *   18b90/17ab0 call via [EBP+0xc]), param_3=scenario_idx (EBX, sign-extended
 *   short), param_4=state_data (ESI, loaded at 0x19142), param_5=cmd_param
 *   ([EBP+0x18]), param_6=finished_ref ([EBP+0x1c]).
 * Confirmed: FUN_00018b90 @<eax>=unit_handle, cdecl(actor_handle,
 *   scenario_idx, state_data, cmd_param).
 * Confirmed: FUN_000169a0 @<esi>=state_data, cdecl(actor_handle, unit_handle,
 *   scenario_idx, cmd_param, &out_index).
 * Confirmed: FUN_00017ab0 @<eax>=cmd_param, @<ecx>=unit_handle,
 *   cdecl(actor_handle, scenario_idx, state_data).
 * Confirmed: out_index local at [EBP+0x17]; cVar5 (loop-continue) stored at
 *   [EBP+0x13]; loop exits on (state_data[4] & 4). */
void FUN_00019110(int actor_handle, int unit_handle, short scenario_idx,
                  char *state_data, int cmd_param, char *finished_ref)
{
  char *atom_table;
  char cVar5;
  char out_index;
  bool validated;

  atom_table = (char *)tag_block_get_element(
    (char *)global_scenario_get() + 0x438, (int)scenario_idx, 0x60);

  if ((state_data[4] & 2) != 0)
    goto LAB_check_finished;

  cVar5 = (int)(unsigned char)state_data[0] < *(int *)(atom_table + 0x30);
  state_data[1] = 0;

  do {
    if (cVar5 != 0) {
      validated = FUN_00018b90(unit_handle, actor_handle, scenario_idx,
                               state_data, (void *)cmd_param);
      if (validated == 0)
        break;
    }

    if (state_data[0] == (char)0xff) {
      out_index = 0;
    } else {
      out_index = state_data[0] + 1;
    }

    if (cVar5 != 0) {
      FUN_000169a0(actor_handle, unit_handle, scenario_idx, cmd_param,
                   &out_index, state_data);
    }

    if (*(int *)(atom_table + 0x30) <= (int)(unsigned char)out_index) {
      state_data[4] = state_data[4] | 2;
      break;
    }

    state_data[0] = out_index;
    cVar5 = FUN_00017ab0(actor_handle, scenario_idx, state_data, cmd_param,
                         unit_handle);
  } while ((state_data[4] & 4) == 0);

LAB_check_finished:
  if ((state_data[4] & 2) != 0)
    return;

  if (finished_ref == NULL) {
    display_assert("finished_reference", "c:\\halo\\SOURCE\\ai\\action_obey.c",
                   0x595, 1);
    system_exit(-1);
  }
  *finished_ref = 0;
}

/* FUN_00019230 (0x19230)
 * Scripted-look prop-interest update callback.
 *
 * Decrements state_data timers.  If the flags byte at state_data+5 has
 * both bit 0 and bit 1 set, invokes FUN_00017960 to compute the look-at
 * direction and store it into state_data+0xc..0x14.
 *
 * Confirmed: 4 cdecl stack args — actor_handle, object_handle, unused,
 *   state_data_ptr.
 * Confirmed: state_data+0x2 = short countdown; state_data+0x5 = flags;
 *   state_data+0x8 = short secondary countdown.
 * Confirmed: FUN_00017960(state_data@<ecx>, actor_handle@<eax>,
 *   object_handle@<edi>). */
void FUN_00019230(int actor_handle, int object_handle, int unused,
                  char *state_data)
{
  short counter;
  char flags;

  counter = *(short *)(state_data + 2);
  if (counter > 0) {
    *(short *)(state_data + 2) = (short)(counter - 1);
  }

  flags = *(char *)(state_data + 5);
  if (flags & 4) {
    counter = *(short *)(state_data + 8);
    if (counter > 0) {
      *(short *)(state_data + 8) = (short)(counter - 1);
    }
  }

  if (!(flags & 1))
    return;
  if (!(flags & 2))
    return;

  FUN_00017960(state_data, actor_handle, object_handle);
}

/* FUN_00019280 (0x19280)
 * Compute actor prop-interest for the prop list at actor+0x9c using the
 * scripted-look update callback (FUN_00019230).
 *
 * Same pattern as FUN_00017090 but selects the scripted-look callback.
 *
 * Confirmed: datum_get(actor_data, actor_handle);
 * actor_look_compute_prop_interest with callback=FUN_00019230, reset=0,
 * prop_state=actor+0x9c, param_5=0. */
void FUN_00019280(int actor_handle)
{
  char *actor;
  actor = (char *)datum_get(actor_data, actor_handle);
  actor_look_compute_prop_interest(actor_handle, 0, (short *)(actor + 0x9c),
                                   (void (*)(void))FUN_00019230, 0);
}

/* FUN_000192b0 (0x192b0) — XBE naked draft (batch 69). */
#if defined(__clang__)
static void *(*const b192b0_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void (*const b192b0_c16d40)(int actor_handle, int param_2, short *param_3, void (*callback)(void), int param_5) = actor_look_compute_prop_interest;
static scenario_t * (*const b192b0_c18e380)(void) = global_scenario_get;
static void *(*const b192b0_elem)(void *, int, int) = tag_block_get_element;
static void *(*const b192b0_tag)(int, int) = tag_get;
static int (*const b192b0_gtime)(void) = game_time_get;

__attribute__((naked, noinline))
int FUN_000192b0(int actor_handle __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "movl 0x6325a4, %%eax\n\t"
      "pushl %%ebx\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "leal -0x1(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl %%eax, %%edi\n\t"
      "pushl $0x19110\n\t"
      "leal 0x9c(%%edi), %%esi\n\t"
      "pushl %%esi\n\t"
      "pushl $0\n\t"
      "pushl %%ebx\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "call *%[c16d40]\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "addl $0x1c, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000192b0_2\n\t"
      "movb 0x5(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_000192b0_2\n\t"
      "movswl (%%esi), %%edx\n\t"
      "pushl $0x60\n\t"
      "pushl %%edx\n\t"
      "call *%[c18e380]\n\t"
      "addl $0x438, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movb 0x20(%%eax), %%cl\n\t"
      "addl $0xc, %%esp\n\t"
      "testb $0x10, %%cl\n\t"
      "je .LFUN_000192b0_1\n\t"
      "movb 0x15c(%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000192b0_1\n\t"
      "movl 0x58(%%edi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x61637472\n\t"
      "call *%[tag]\n\t"
      "movl (%%eax), %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "testl $0x200000, %%ecx\n\t"
      "je .LFUN_000192b0_2\n\t"
      ".LFUN_000192b0_1:\n\t"
      "call *%[gtime]\n\t"
      "movl %%eax, 0x94(%%edi)\n\t"
      "movb $1, 0x5(%%esi)\n\t"
      ".LFUN_000192b0_2:\n\t"
      "cmpw $0xb, 0x6c(%%edi)\n\t"
      "jne .LFUN_000192b0_3\n\t"
      "movb 0x5(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000192b0_3\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl $1, %%eax\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000192b0_3:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "xorl %%eax, %%eax\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [dget] "m"(b192b0_dget), [c16d40] "m"(b192b0_c16d40), [c18e380] "m"(b192b0_c18e380), [elem] "m"(b192b0_elem), [tag] "m"(b192b0_tag), [gtime] "m"(b192b0_gtime)
      : "memory");
}
#else
#error "FUN_000192b0: clang naked draft required"
#endif


/* FUN_00019370 (0x19370) — XBE naked draft (batch 69). */
#if defined(__clang__)
static void *(*const b19370_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void (*const b19370_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b19370_exitfn)(int) = system_exit;
static int (*const b19370_c2a3f0)(int actor_handle) = FUN_0002a3f0;
static int (*const b19370_c2a360)(int actor_handle) = FUN_0002a360;
static float (*const b19370_mag)(float *) = magnitude3d;
static int (*const b19370_c2a7e0)(int actor_handle, int16_t param_2, int *param_3) = actor_move_animation_impulse;
static void (*const b19370_c46f10)(int16_t type, int unit_handle, int param3, int param4, int16_t param5, int16_t param6, int16_t param7) = FUN_00046f10;
static bool (*const b19370_c1a9ad0)(int unit_handle) = unit_is_busy;

__attribute__((naked, noinline))
void FUN_00019370(int actor_handle __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $8, %%esp\n\t"
      "movl 0x6325a4, %%eax\n\t"
      "pushl %%ebx\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%esi\n\t"
      "movb 0x6(%%esi), %%al\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00019370_1\n\t"
      "pushl $1\n\t"
      "pushl $0x6f1\n\t"
      "pushl $0x253758\n\t"
      "pushl $0x253380\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00019370_1:\n\t"
      "movb 0xfe(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00019370_2\n\t"
      "movw $7, 0x3e8(%%esi)\n\t"
      "movw $2, 0x3ec(%%esi)\n\t"
      "movw $4, 0x3fc(%%esi)\n\t"
      "movb $1, 0x454(%%esi)\n\t"
      "movb $1, 0x457(%%esi)\n\t"
      "movb $1, 0x45d(%%esi)\n\t"
      "leal 0x100(%%esi), %%ecx\n\t"
      "movl (%%ecx), %%eax\n\t"
      "leal 0x460(%%esi), %%edx\n\t"
      "movl %%eax, (%%edx)\n\t"
      "movl 0x4(%%ecx), %%eax\n\t"
      "movl %%eax, 0x4(%%edx)\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "movl %%ecx, 0x8(%%edx)\n\t"
      "movl 0x10c(%%esi), %%edx\n\t"
      "movl %%edx, 0x458(%%esi)\n\t"
      "jmp .LFUN_00019370_8\n\t"
      ".LFUN_00019370_2:\n\t"
      "movb 0xe0(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00019370_4\n\t"
      "pushl %%ebx\n\t"
      "call *%[c2a3f0]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00019370_4\n\t"
      "movw $4, 0x3e8(%%esi)\n\t"
      "movl $3, %%ecx\n\t"
      "movw %%cx, 0x3ec(%%esi)\n\t"
      "leal 0xe4(%%esi), %%eax\n\t"
      "movl (%%eax), %%edi\n\t"
      "leal 0x3f0(%%esi), %%edx\n\t"
      "movl %%edi, (%%edx)\n\t"
      "movl 0x4(%%eax), %%edi\n\t"
      "movl %%edi, 0x4(%%edx)\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl %%eax, 0x8(%%edx)\n\t"
      "movb 0x99(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00019370_3\n\t"
      "movl 0x128(%%esi), %%edx\n\t"
      "movl %%edx, 0x3f8(%%esi)\n\t"
      ".LFUN_00019370_3:\n\t"
      "xorl %%eax, %%eax\n\t"
      "cmpw %%cx, 0x6a(%%esi)\n\t"
      "setl %%al\n\t"
      "decl %%eax\n\t"
      "andl %%ecx, %%eax\n\t"
      "incl %%eax\n\t"
      "jmp .LFUN_00019370_7\n\t"
      ".LFUN_00019370_4:\n\t"
      "movw 0xca(%%esi), %%ax\n\t"
      "movl $3, %%ecx\n\t"
      "cmpw %%cx, %%ax\n\t"
      "je .LFUN_00019370_6\n\t"
      "cmpw $1, %%ax\n\t"
      "je .LFUN_00019370_6\n\t"
      "cmpw $5, 0x6e(%%esi)\n\t"
      "jl .LFUN_00019370_5\n\t"
      "testb $1, 0xa8(%%esi)\n\t"
      "je .LFUN_00019370_5\n\t"
      "movw $7, 0x3e8(%%esi)\n\t"
      "movw $2, 0x3ec(%%esi)\n\t"
      "movw $4, 0x3fc(%%esi)\n\t"
      "movb $1, 0x454(%%esi)\n\t"
      "jmp .LFUN_00019370_8\n\t"
      ".LFUN_00019370_5:\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw %%ax, 0x3e8(%%esi)\n\t"
      "movb 0x9f(%%esi), %%dl\n\t"
      "testb %%dl, %%dl\n\t"
      "je .LFUN_00019370_7\n\t"
      "xorl %%edx, %%edx\n\t"
      "cmpw %%cx, 0x6a(%%esi)\n\t"
      "setl %%dl\n\t"
      "decl %%edx\n\t"
      "andl %%ecx, %%edx\n\t"
      "incl %%edx\n\t"
      "movw %%dx, 0x3fc(%%esi)\n\t"
      "jmp .LFUN_00019370_8\n\t"
      ".LFUN_00019370_6:\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw $7, 0x3e8(%%esi)\n\t"
      "movw %%ax, 0x3ec(%%esi)\n\t"
      ".LFUN_00019370_7:\n\t"
      "movw %%ax, 0x3fc(%%esi)\n\t"
      ".LFUN_00019370_8:\n\t"
      "movb 0x110(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00019370_9\n\t"
      "movb $1, 0x45c(%%esi)\n\t"
      "movb $0, 0x110(%%esi)\n\t"
      ".LFUN_00019370_9:\n\t"
      "movb 0xc8(%%esi), %%al\n\t"
      "movb %%al, 0x426(%%esi)\n\t"
      "movb 0xc8(%%esi), %%cl\n\t"
      "movb %%cl, 0x427(%%esi)\n\t"
      "movw 0xca(%%esi), %%dx\n\t"
      "movw %%dx, 0x42c(%%esi)\n\t"
      "movb 0xf8(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00019370_12\n\t"
      "pushl %%ebx\n\t"
      "call *%[c2a360]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00019370_12\n\t"
      "movw 0xfa(%%esi), %%di\n\t"
      "cmpw $-1, %%di\n\t"
      "je .LFUN_00019370_10\n\t"
      "movl 0x5a4(%%esi), %%eax\n\t"
      "movl 0x5a8(%%esi), %%ecx\n\t"
      "leal -0x8(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "movl %%ecx, -0x4(%%ebp)\n\t"
      "call *%[mag]\n\t"
      "fstp %%st(0)\n\t"
      "leal -0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "call *%[c2a7e0]\n\t"
      "addl $0x10, %%esp\n\t"
      ".LFUN_00019370_10:\n\t"
      "movw 0xfc(%%esi), %%ax\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .LFUN_00019370_11\n\t"
      "movl 0x18(%%esi), %%ecx\n\t"
      "pushl $0\n\t"
      "pushl $-1\n\t"
      "pushl $-1\n\t"
      "pushl $-1\n\t"
      "pushl $-1\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "call *%[c46f10]\n\t"
      "addl $0x1c, %%esp\n\t"
      ".LFUN_00019370_11:\n\t"
      "movb $0, 0xf8(%%esi)\n\t"
      ".LFUN_00019370_12:\n\t"
      "testb $1, 0xa9(%%esi)\n\t"
      "je .LFUN_00019370_13\n\t"
      "movb $1, 0x430(%%esi)\n\t"
      "leal 0xb0(%%esi), %%edx\n\t"
      "movl (%%edx), %%ecx\n\t"
      "leal 0x434(%%esi), %%eax\n\t"
      "movl %%ecx, (%%eax)\n\t"
      "movl 0x4(%%edx), %%ecx\n\t"
      "movl %%ecx, 0x4(%%eax)\n\t"
      "movl 0x8(%%edx), %%edx\n\t"
      "movl %%edx, 0x8(%%eax)\n\t"
      "movw 0xac(%%esi), %%ax\n\t"
      "movw %%ax, 0x42e(%%esi)\n\t"
      ".LFUN_00019370_13:\n\t"
      "movb 0xa9(%%esi), %%al\n\t"
      "testb $4, %%al\n\t"
      "je .LFUN_00019370_15\n\t"
      "testb $8, %%al\n\t"
      "je .LFUN_00019370_16\n\t"
      "cmpw $0, 0xac(%%esi)\n\t"
      "setg %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00019370_15\n\t"
      ".LFUN_00019370_14:\n\t"
      "leal 0x174(%%esi), %%eax\n\t"
      "movl (%%eax), %%edx\n\t"
      "leal 0x434(%%esi), %%ecx\n\t"
      "movl %%edx, (%%ecx)\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl %%edx, 0x4(%%ecx)\n\t"
      "movb $1, 0x430(%%esi)\n\t"
      "movl %%eax, 0x8(%%ecx)\n\t"
      "movw $0, 0x42e(%%esi)\n\t"
      ".LFUN_00019370_15:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00019370_16:\n\t"
      "cmpw $0, 0xac(%%esi)\n\t"
      "jne .LFUN_00019370_14\n\t"
      "movb 0x15c(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00019370_14\n\t"
      "movl 0x18(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1a9ad0]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00019370_14\n\t"
      "movl 0x174(%%esi), %%edx\n\t"
      "movl 0x178(%%esi), %%eax\n\t"
      "leal -0x8(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl %%edx, -0x8(%%ebp)\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "call *%[mag]\n\t"
      "fcomps 0x2533c0\n\t"
      "addl $4, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .LFUN_00019370_17\n\t"
      "movl 0x31fc0c, %%eax\n\t"
      "movl (%%eax), %%edx\n\t"
      "movl 0x4(%%eax), %%ecx\n\t"
      "jmp .LFUN_00019370_18\n\t"
      ".LFUN_00019370_17:\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      ".LFUN_00019370_18:\n\t"
      "movb $1, 0x440(%%esi)\n\t"
      "flds 0xb0(%%esi)\n\t"
      "fmuls 0x2533c4\n\t"
      "fcomps 0xb4(%%esi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00019370_19\n\t"
      "movl $1, %%eax\n\t"
      "jmp .LFUN_00019370_20\n\t"
      ".LFUN_00019370_19:\n\t"
      "xorl %%eax, %%eax\n\t"
      ".LFUN_00019370_20:\n\t"
      "movb %%al, 0x441(%%esi)\n\t"
      "movb 0xa9(%%esi), %%al\n\t"
      "shrb $4, %%al\n\t"
      "andb $1, %%al\n\t"
      "movb %%al, 0x442(%%esi)\n\t"
      "movl %%ecx, 0x448(%%esi)\n\t"
      "movl %%edx, 0x444(%%esi)\n\t"
      "movl 0xb0(%%esi), %%ecx\n\t"
      "movl %%ecx, 0x44c(%%esi)\n\t"
      "movl 0xb4(%%esi), %%edx\n\t"
      "movl %%edx, 0x450(%%esi)\n\t"
      "movb 0xa9(%%esi), %%cl\n\t"
      "orb $8, %%cl\n\t"
      "movb %%cl, %%al\n\t"
      "testb $0x10, %%al\n\t"
      "movb %%cl, 0xa9(%%esi)\n\t"
      "jne .LFUN_00019370_15\n\t"
      "popl %%edi\n\t"
      "movw $0xf, 0xac(%%esi)\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [dget] "m"(b19370_dget), [assert] "m"(b19370_assert), [exitfn] "m"(b19370_exitfn), [c2a3f0] "m"(b19370_c2a3f0), [c2a360] "m"(b19370_c2a360), [mag] "m"(b19370_mag), [c2a7e0] "m"(b19370_c2a7e0), [c46f10] "m"(b19370_c46f10), [c1a9ad0] "m"(b19370_c1a9ad0)
      : "memory");
}
#else
#error "FUN_00019370: clang naked draft required"
#endif


/* FUN_00019750 (0x19750)
 * Initialize action_search state for a non-retreating actor (type 0).
 *
 * Validates state_data != NULL, zeros the 0x2c-byte buffer, then if the
 * actor is not in retreat (actor+0x160 == 0) fills in the initial state:
 * type=0 at state_data+8, param flag at state_data+5, and marks actor
 * as active (actor+0x98 = 1). Returns 1 on success, 0 if retreating.
 *
 * Confirmed: display_assert "state_data", action_search.c line 0x21.
 * Confirmed: csmemset(state_data, 0, 0x2c); actor+0x160 branch. */
int FUN_00019750(int actor_handle, char param_2, char *state_data)
{
  char *actor;
  actor = (char *)datum_get(actor_data, actor_handle);
  if (state_data == NULL) {
    display_assert("state_data", "c:\\halo\\SOURCE\\ai\\action_search.c", 0x21,
                   1);
    system_exit(-1);
  }
  csmemset(state_data, 0, 0x2c);
  if (*(char *)(actor + 0x160) == '\0') {
    *(short *)(state_data + 8) = 0;
    *(char *)(state_data + 5) = param_2;
    *(char *)(actor + 0x98) = 1;
    return 1;
  }
  return 0;
}

/* FUN_000197d0 (0x197d0) — XBE naked draft (batch 78). */
#if defined(__clang__)
static void *(*const b197d0_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void (*const b197d0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b197d0_exitfn)(int) = system_exit;
static void *(*const b197d0_memset)(void *, int, unsigned int) = csmemset;
static scenario_t * (*const b197d0_c18e380)(void) = global_scenario_get;
static void *(*const b197d0_elem)(void *, int, int) = tag_block_get_element;

__attribute__((naked, noinline))
int FUN_000197d0(int actor_handle __attribute__((unused)), short param_2 __attribute__((unused)), char param_3 __attribute__((unused)), char *state_data __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl 0x6325a4, %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movl 0x14(%%ebp), %%esi\n\t"
      "addl $8, %%esp\n\t"
      "xorb %%bl, %%bl\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%eax, %%edi\n\t"
      "jne .LFUN_000197d0_1\n\t"
      "pushl $1\n\t"
      "pushl $0x38\n\t"
      "pushl $0x253da4\n\t"
      "pushl $0x25334c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000197d0_1:\n\t"
      "pushl $0x2c\n\t"
      "pushl $0\n\t"
      "pushl %%esi\n\t"
      "call *%[memset]\n\t"
      "movb 0x160(%%edi), %%al\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_000197d0_2\n\t"
      "movb 0x6(%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_000197d0_2\n\t"
      "movl 0x34(%%edi), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_000197d0_2\n\t"
      "movw 0xc(%%ebp), %%bx\n\t"
      "cmpw $-1, %%bx\n\t"
      "je .LFUN_000197d0_3\n\t"
      "andl $0xffff, %%eax\n\t"
      "pushl $0xb0\n\t"
      "pushl %%eax\n\t"
      "call *%[c18e380]\n\t"
      "addl $0x42c, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movswl %%bx, %%edx\n\t"
      "pushl $0x18\n\t"
      "pushl %%edx\n\t"
      "addl $0x98, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movb 0x10(%%ebp), %%cl\n\t"
      "movb %%cl, 0x4(%%esi)\n\t"
      "movw %%bx, 0xa(%%esi)\n\t"
      "movw $1, 0x8(%%esi)\n\t"
      "movl %%eax, %%ecx\n\t"
      "movl (%%ecx), %%ebx\n\t"
      "leal 0x14(%%esi), %%edx\n\t"
      "movl %%ebx, (%%edx)\n\t"
      "movl 0x4(%%ecx), %%ebx\n\t"
      "movl %%ebx, 0x4(%%edx)\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "movl %%ecx, 0x8(%%edx)\n\t"
      "movl 0x14(%%eax), %%edx\n\t"
      "movl %%edx, 0x10(%%esi)\n\t"
      "movw 0xe(%%eax), %%ax\n\t"
      "movw %%ax, 0xc(%%esi)\n\t"
      "addl $0x18, %%esp\n\t"
      "movb $1, %%al\n\t"
      "movb %%al, 0x98(%%edi)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000197d0_2:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000197d0_3:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [dget] "m"(b197d0_dget), [assert] "m"(b197d0_assert), [exitfn] "m"(b197d0_exitfn), [memset] "m"(b197d0_memset), [c18e380] "m"(b197d0_c18e380), [elem] "m"(b197d0_elem)
      : "memory");
}
#else
#error "FUN_000197d0: clang naked draft required"
#endif


/* FUN_000198d0 (0x198d0)
 * Initialize action_search state for a berserk actor (type 2).
 *
 * Validates state_data != NULL, zeros the 0x2c-byte buffer, then if the
 * actor is berserk (actor+6 != 0) sets state type=2 at state_data+8 and
 * marks actor as active (actor+0x98 = 1). Returns 1 on success, 0 if
 * not berserk.
 *
 * Confirmed: display_assert "state_data", action_search.c line 0x57.
 * Confirmed: csmemset(state_data, 0, 0x2c); actor+6 branch; type=2. */
int FUN_000198d0(int actor_handle, int param_2, char *state_data)
{
  char *actor;
  actor = (char *)datum_get(actor_data, actor_handle);
  if (state_data == NULL) {
    display_assert("state_data", "c:\\halo\\SOURCE\\ai\\action_search.c", 0x57,
                   1);
    system_exit(-1);
  }
  csmemset(state_data, 0, 0x2c);
  if (*(char *)(actor + 6) != '\0') {
    *(short *)(state_data + 8) = 2;
    *(char *)(actor + 0x98) = 1;
    return 1;
  }
  return 0;
}

/* FUN_00019940 (0x19940) — XBE naked draft (batch 69). */
#if defined(__clang__)
static void *(*const b19940_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void *(*const b19940_tag)(int, int) = tag_get;
static int (*const b19940_c3b380)(int actor_handle) = actor_target_unit_index;
static void (*const b19940_c46f10)(int16_t type, int unit_handle, int param3, int param4, int16_t param5, int16_t param6, int16_t param7) = FUN_00046f10;

__attribute__((naked, noinline))
void FUN_00019940(int actor_handle __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl 0x6325a4, %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%esi\n\t"
      "movb 0x9c(%%esi), %%al\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00019940_9\n\t"
      "movl 0x58(%%esi), %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x61637472\n\t"
      "call *%[tag]\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $4, 0x2f8(%%eax)\n\t"
      "movb $1, %%bl\n\t"
      "je .LFUN_00019940_1\n\t"
      "movb $0, 0x9f(%%esi)\n\t"
      "testb $2, (%%eax)\n\t"
      "je .LFUN_00019940_2\n\t"
      "cmpw $0, 0xa4(%%esi)\n\t"
      "jne .LFUN_00019940_2\n\t"
      "cmpw $5, 0x268(%%esi)\n\t"
      "jne .LFUN_00019940_2\n\t"
      "movl 0x270(%%esi), %%edx\n\t"
      "movl 0x5ab23c, %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movb 0x121(%%eax), %%cl\n\t"
      "addl $8, %%esp\n\t"
      "cmpb $2, %%cl\n\t"
      "jg .LFUN_00019940_2\n\t"
      ".LFUN_00019940_1:\n\t"
      "movb %%bl, 0x9f(%%esi)\n\t"
      ".LFUN_00019940_2:\n\t"
      "movb 0x9e(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00019940_7\n\t"
      "movl 0xc0(%%esi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jle .LFUN_00019940_3\n\t"
      "decl %%eax\n\t"
      "movl %%eax, 0xc0(%%esi)\n\t"
      ".LFUN_00019940_3:\n\t"
      "movl 0xc0(%%esi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_00019940_4\n\t"
      "movb %%bl, 0x9c(%%esi)\n\t"
      ".LFUN_00019940_4:\n\t"
      "cmpl $-1, 0x18(%%esi)\n\t"
      "je .LFUN_00019940_8\n\t"
      "cmpw $0, 0xa4(%%esi)\n\t"
      "jne .LFUN_00019940_6\n\t"
      "movb 0x3bd(%%esi), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "jne .LFUN_00019940_8\n\t"
      "movb 0x9c(%%esi), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "jne .LFUN_00019940_5\n\t"
      "movl 0xbc(%%esi), %%ecx\n\t"
      "addl $0x5a, %%eax\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jge .LFUN_00019940_8\n\t"
      ".LFUN_00019940_5:\n\t"
      "pushl $0\n\t"
      "pushl $-1\n\t"
      "pushl $-1\n\t"
      "pushl $-1\n\t"
      "pushl %%edi\n\t"
      "call *%[c3b380]\n\t"
      "movl 0x18(%%esi), %%ecx\n\t"
      "addl $4, %%esp\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl $0xd\n\t"
      "call *%[c46f10]\n\t"
      "addl $0x1c, %%esp\n\t"
      "movb %%bl, 0x3bd(%%esi)\n\t"
      "popl %%ebx\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00019940_6:\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_00019940_8\n\t"
      "pushl %%eax\n\t"
      "pushl $-1\n\t"
      "pushl $-1\n\t"
      "pushl $-1\n\t"
      "pushl %%edi\n\t"
      "call *%[c3b380]\n\t"
      "movl 0x18(%%esi), %%edx\n\t"
      "addl $4, %%esp\n\t"
      "pushl %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl $0x12\n\t"
      "call *%[c46f10]\n\t"
      "addl $0x1c, %%esp\n\t"
      "popl %%ebx\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00019940_7:\n\t"
      "movb 0x504(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00019940_8\n\t"
      "movb 0x6(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00019940_8\n\t"
      "movl 0xc4(%%esi), %%ecx\n\t"
      "incl %%ecx\n\t"
      "movl %%ecx, %%eax\n\t"
      "cmpl $0x78, %%eax\n\t"
      "movl %%ecx, 0xc4(%%esi)\n\t"
      "jle .LFUN_00019940_8\n\t"
      "movb %%bl, 0x9d(%%esi)\n\t"
      "movb %%bl, 0x9c(%%esi)\n\t"
      ".LFUN_00019940_8:\n\t"
      "popl %%ebx\n\t"
      ".LFUN_00019940_9:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [dget] "m"(b19940_dget), [tag] "m"(b19940_tag), [c3b380] "m"(b19940_c3b380), [c46f10] "m"(b19940_c46f10)
      : "memory");
}
#else
#error "FUN_00019940: clang naked draft required"
#endif


/* FUN_00019ac0 (0x19ac0)
 * Mark actor look-state as interrupted (target type 1 path).
 *
 * If the look-target type word at actor+0xa4 equals 1, clears the
 * target-acquired index at actor+0xa6 (set to 0xffff = none) and
 * sets the look-state byte at actor+0x9c to 1.
 *
 * Confirmed: ADD EAX,0x9c after datum_get; CMP word [EAX+0x8],0x1;
 *   MOV word [EAX+0xa],0xffff; MOV byte [EAX],0x1. */
void FUN_00019ac0(int actor_handle)
{
  char *actor;
  actor = (char *)datum_get(actor_data, actor_handle);
  if (*(short *)(actor + 0xa4) == 1) {
    *(short *)(actor + 0xa6) = (short)0xffff;
    *(char *)(actor + 0x9c) = 1;
  }
}

/* FUN_00019af0 (0x19af0)
 * Reset actor look-target handles to invalid (-1).
 *
 * Unconditionally clears actor+0xa8 (int16_t) and actor+0xac (int32_t)
 * to -1 (all-bits-set via OR ECX,0xffffffff).
 *
 * Confirmed: ADD EAX,0x9c after datum_get; OR ECX,0xffffffff;
 *   MOV word [EAX+0xc],CX (actor+0xa8); MOV dword [EAX+0x10],ECX (actor+0xac).
 */
void FUN_00019af0(int actor_handle)
{
  char *actor;
  actor = (char *)datum_get(actor_data, actor_handle);
  *(short *)(actor + 0xa8) = -1;
  *(int *)(actor + 0xac) = -1;
}

/* FUN_00019b20 (0x19b20) — XBE naked draft (batch 75). */
#if defined(__clang__)
static void *(*const b19b20_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void *(*const b19b20_tag)(int, int) = tag_get;

__attribute__((naked, noinline))
void FUN_00019b20(int actor_handle __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl 0x6325a4, %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x58(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x61637472\n\t"
      "call *%[tag]\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "movb 0x504(%%esi), %%al\n\t"
      "addl $0x10, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "movl $3, %%edi\n\t"
      "je .LFUN_00019b20_1\n\t"
      "movw %%di, 0x3e8(%%esi)\n\t"
      "movw $0, 0x3ec(%%esi)\n\t"
      "jmp .LFUN_00019b20_5\n\t"
      ".LFUN_00019b20_1:\n\t"
      "movl 0xbc(%%esi), %%ecx\n\t"
      "movl $0x55555556, %%eax\n\t"
      "imull %%ecx\n\t"
      "movl %%edx, %%eax\n\t"
      "shrl $0x1f, %%eax\n\t"
      "addl %%eax, %%edx\n\t"
      "cmpl $0x5a, %%edx\n\t"
      "jg .LFUN_00019b20_2\n\t"
      "movl $0x5a, %%edx\n\t"
      ".LFUN_00019b20_2:\n\t"
      "subl 0xc0(%%esi), %%ecx\n\t"
      "cmpl %%edx, %%ecx\n\t"
      "jge .LFUN_00019b20_4\n\t"
      "movw 0xa4(%%esi), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "jne .LFUN_00019b20_3\n\t"
      "movw %%di, 0x3e8(%%esi)\n\t"
      "movw $2, 0x3ec(%%esi)\n\t"
      "jmp .LFUN_00019b20_5\n\t"
      ".LFUN_00019b20_3:\n\t"
      "cmpw $1, %%ax\n\t"
      "jne .LFUN_00019b20_4\n\t"
      "movw %%di, 0x3e8(%%esi)\n\t"
      "movw %%di, 0x3ec(%%esi)\n\t"
      "leal 0xb0(%%esi), %%ecx\n\t"
      "movl (%%ecx), %%eax\n\t"
      "leal 0x3f0(%%esi), %%edx\n\t"
      "movl %%eax, (%%edx)\n\t"
      "movl 0x4(%%ecx), %%eax\n\t"
      "movl %%eax, 0x4(%%edx)\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "movl %%ecx, 0x8(%%edx)\n\t"
      "jmp .LFUN_00019b20_5\n\t"
      ".LFUN_00019b20_4:\n\t"
      "movw $1, 0x3e8(%%esi)\n\t"
      ".LFUN_00019b20_5:\n\t"
      "movw %%di, 0x3fc(%%esi)\n\t"
      "cmpw $0, 0xa4(%%esi)\n\t"
      "jne .LFUN_00019b20_7\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "testb $0x10, (%%edx)\n\t"
      "je .LFUN_00019b20_6\n\t"
      "cmpw $5, 0x268(%%esi)\n\t"
      "setge %%al\n\t"
      "movb %%al, 0x454(%%esi)\n\t"
      "jmp .LFUN_00019b20_7\n\t"
      ".LFUN_00019b20_6:\n\t"
      "cmpw $6, 0x268(%%esi)\n\t"
      "setge %%cl\n\t"
      "movb %%cl, 0x454(%%esi)\n\t"
      ".LFUN_00019b20_7:\n\t"
      "movb 0x9f(%%esi), %%dl\n\t"
      "movb %%dl, 0x426(%%esi)\n\t"
      "movb 0x9f(%%esi), %%al\n\t"
      "popl %%edi\n\t"
      "movb %%al, 0x427(%%esi)\n\t"
      "movb $0, 0x428(%%esi)\n\t"
      "movb $0, 0x424(%%esi)\n\t"
      "movb $1, 0x425(%%esi)\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [dget] "m"(b19b20_dget), [tag] "m"(b19b20_tag)
      : "memory");
}
#else
#error "FUN_00019b20: clang naked draft required"
#endif


/* FUN_00019c70 (0x19c70) — XBE naked draft (batch 69). */
#if defined(__clang__)
static void *(*const b19c70_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void *(*const b19c70_tag)(int, int) = tag_get;
static int *(*const b19c70_gseed)(void) = get_global_random_seed_address;
static float (*const b19c70_rrange)(int *, float, float) = random_real_range;
static void (*const b19c70_ftol)(void) = FUN_001d9068;

__attribute__((naked, noinline))
void FUN_00019c70(int actor_handle __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $8, %%esp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl 0x6325a4, %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x58(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x61637472\n\t"
      "call *%[tag]\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpw $0, 0xa4(%%esi)\n\t"
      "jne .LFUN_00019c70_1\n\t"
      "movl 0x348(%%eax), %%ecx\n\t"
      "movl 0x344(%%eax), %%edx\n\t"
      "movl %%ecx, %%eax\n\t"
      "movl %%ecx, -0x4(%%ebp)\n\t"
      "pushl %%eax\n\t"
      "movl %%edx, %%ecx\n\t"
      "movl %%edx, -0x8(%%ebp)\n\t"
      "pushl %%ecx\n\t"
      "jmp .LFUN_00019c70_2\n\t"
      ".LFUN_00019c70_1:\n\t"
      "movl 0x350(%%eax), %%edx\n\t"
      "movl 0x34c(%%eax), %%eax\n\t"
      "movl %%edx, %%ecx\n\t"
      "movl %%edx, -0x8(%%ebp)\n\t"
      "pushl %%ecx\n\t"
      "movl %%eax, %%edx\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "pushl %%edx\n\t"
      ".LFUN_00019c70_2:\n\t"
      "call *%[gseed]\n\t"
      "pushl %%eax\n\t"
      "call *%[rrange]\n\t"
      "fmuls 0x253394\n\t"
      "addl $0xc, %%esp\n\t"
      "call *%[ftol]\n\t"
      "movl %%eax, 0xbc(%%esi)\n\t"
      "movl %%eax, 0xc0(%%esi)\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [dget] "m"(b19c70_dget), [tag] "m"(b19c70_tag), [gseed] "m"(b19c70_gseed), [rrange] "m"(b19c70_rrange), [ftol] "m"(b19c70_ftol)
      : "memory");
}
#else
#error "FUN_00019c70: clang naked draft required"
#endif


/* actor_look_secondary (0x19d00) — Secondary actor aim/fire target evaluation.
 *
 * Evaluates whether the actor should engage a secondary aim target when the
 * primary look-target condition (field_9e) is not met.  Branches:
 *   1. field_a4==0 && field_270!=-1: distance check against threat obj.
 *   2. field_a4==1 && field_a6!=-1: distance/window check with LOS test.
 *   3. field_9e==0 && field_a1==0: iterate nearby actors (field_24 in [2,3])
 *      and count/assess proximity for retreat/support decisions.
 *   4. Fallback: actor_move_to_prop for type-0, actor_move_to_firing_position for type-1.
 *
 * Confirmed: cdecl, single stack arg (actor_handle).
 * Confirmed: datum_get(actor_data, actor_handle) at 0x19d10/0x19d12.
 * Confirmed: check swarm/field_4c/field_9c early-exit at
 * 0x19d1f/0x19d2c/0x19d38. Confirmed: field_a4==0 branch: datum_get(prop_data,
 * field_270) at 0x19d5f/0x19d67, squared-distance comparison at
 * 0x19d91-0x19d9f. Confirmed: field_a4==1 branch: squared-distance to field_b0
 * at 0x19ddf/0x19de4, FCOM [0x253dd0] / FCOMP [0x253dcc] at 0x19de4/0x19dff,
 *   unit_estimate_position + ai_test_line_of_sight at 0x19e24/0x19e59.
 * Confirmed: actor iteration with FUN_00064540/FUN_00064570 at 0x19e97/0x19ea0,
 *   loop head at 0x19eb2, actors_searching_same_position at 0x19ee0, inner datum_get at 0x19ef7.
 * Confirmed: encounter support encounter_mark_examined_pursuit_position at 0x19fac.
 * Confirmed: fallback actor_move_to_prop(actor_handle, field_270, 3.0f) at 0x19feb.
 *   or actor_move_to_firing_position(actor_handle, field_a6, 0) at 0x19fa2a.
 * Confirmed: FUN_0002f1a0(actor_handle) call at 0x1a035. */
int actor_look_secondary(int actor_handle)
{
  char *actor;
  char *threat;
  float dist_sq_threshold;
  float offset_radius[3];
  int iter_ctx[2];
  char *iter_actor;
  short los_result;
  int found_count;
  int nearby_count;
  int enc_handle;
  int ret;

  actor = (char *)datum_get(actor_data, actor_handle);

  if (*(char *)(actor + 6) != '\0')
    return *(int *)(actor + 0x9c);
  if (*(char *)(actor + 0x4c) == '\0')
    return *(int *)(actor + 0x9c);
  if (*(char *)(actor + 0x9c) != '\0')
    return *(int *)(actor + 0x9c);

  *(char *)(actor + 0x9e) = 1;

  if (*(short *)(actor + 0xa4) == 0) {
    if (*(int *)(actor + 0x270) != -1) {
      threat = (char *)datum_get(*(data_t **)0x5ab23c, *(int *)(actor + 0x270));
      dist_sq_threshold = 1.7f;
      if (*(short *)(threat + 0x38) != 0) {
        dist_sq_threshold = 0.7f;
      }
      if (distance_squared3d((float *)(threat + 0xbc),
                             (float *)(actor + 0x12c)) <
          dist_sq_threshold * dist_sq_threshold) {
        *(char *)(actor + 0x9e) = 1;
      } else {
        *(char *)(actor + 0x9e) = 0;
      }
    }
  } else if (*(short *)(actor + 0xa4) == 1) {
    if (*(short *)(actor + 0xa6) != -1) {
      if (distance_squared3d((float *)(actor + 0xb0),
                             (float *)(actor + 0x12c)) < *(float *)0x253dd0) {
        *(char *)(actor + 0x9e) = 1;
      } else if (distance_squared3d((float *)(actor + 0xb0),
                                    (float *)(actor + 0x12c)) <
                 *(float *)0x253dcc) {
        unit_estimate_position(*(int *)(actor + 0x18), 1,
                               (vector3_t *)(actor + 0xb0), NULL, NULL,
                               (vector3_t *)offset_radius);
        los_result = (short)ai_test_line_of_sight(
          (float *)(actor + 0x120), (int)*(uint16_t *)(actor + 0x148),
          offset_radius, (int)*(uint16_t *)(actor + 0xa8), 0, 0, -1,
          (char)(*(int *)(actor + 0x158) != -1));
        *(char *)(actor + 0x9e) = (char)(los_result == 0);
      } else {
        *(char *)(actor + 0x9e) = 0;
      }
    }
  }

  if (*(char *)(actor + 0x9e) == '\0' && *(char *)(actor + 0xa1) == '\0') {
    found_count = 0;
    nearby_count = 0;
    FUN_00064540((void *)iter_ctx, actor_handle);
    iter_actor = (char *)FUN_00064570((void *)iter_ctx);
    while (iter_actor != NULL) {
      if (*(short *)(iter_actor + 0x24) >= 2 &&
          *(short *)(iter_actor + 0x24) <= 3 &&
          *(char *)(iter_actor + 0x60) == '\0' &&
          *(char *)(iter_actor + 0x127) == '\0' &&
          *(int *)(iter_actor + 0x1c) != -1 &&
          actors_searching_same_position(actor_handle,
                                         *(int *)(iter_actor + 0x1c))) {
        iter_actor = (char *)datum_get(actor_data, *(int *)(iter_actor + 0x1c));
        found_count = found_count + 1;
        if (*(char *)(iter_actor + 6) == '\0' &&
            *(char *)(iter_actor + 0x504) == '\0' &&
            distance_squared3d((float *)(actor + 0x12c),
                               (float *)(iter_actor + 0x12c)) <
              *(float *)0x253dc8) {
          nearby_count = nearby_count + 1;
        }
      }
      iter_actor = (char *)FUN_00064570((void *)iter_ctx);
    }

    if (*(char *)(actor + 0xa0) == '\0' &&
        found_count >= (short)((*(short *)(actor + 0xa4) != 1) * 2 + 2)) {
      *(char *)(actor + 0x9c) = 1;
      enc_handle = -1;
      if (*(int *)(actor + 0x270) != -1) {
        threat =
          (char *)datum_get(*(data_t **)0x5ab23c, *(int *)(actor + 0x270));
        enc_handle = *(int *)(threat + 0x7c);
      }
      if (*(int *)(actor + 0x34) != -1) {
        encounter_mark_examined_pursuit_position(
          *(int *)(actor + 0x34), actor_handle, *(short *)(actor + 0xa6),
          enc_handle);
      }
    } else if (nearby_count > 0) {
      *(char *)(actor + 0x9e) = 1;
    }
  }

  if (*(char *)(actor + 0x9e) == '\0') {
    if (*(short *)(actor + 0xa4) == 0) {
      ret = actor_move_to_prop(actor_handle, *(int *)(actor + 0x270), 3.0f);
      if (!ret) {
        *(char *)(actor + 0x9c) = 1;
        *(char *)(actor + 0x9d) = 1;
        return *(int *)(actor + 0x9c);
      }
    } else if (*(short *)(actor + 0xa4) == 1) {
      *(short *)(actor + 0x3b8) = -1;
      ret = actor_move_to_firing_position(actor_handle,
                                          *(short *)(actor + 0xa6), 0);
      if (!ret) {
        *(char *)(actor + 0x9c) = 1;
        *(char *)(actor + 0x9d) = 1;
        return *(int *)(actor + 0x9c);
      }
    }
  }

  FUN_0002f1a0(actor_handle);
  return *(int *)(actor + 0x9c);
}

/* FUN_0001a050 (0x1a050)
 * Clear the look-spec type word at actor+0x3fc.
 *
 * Sets actor+0x3fc to 0 (int16_t write, zero-extending).
 *
 * Confirmed: CALL datum_get; ADD ESP,0x8;
 *   MOV word [EAX+0x3fc],0x0. */
void FUN_0001a050(int actor_handle)
{
  char *actor;
  actor = (char *)datum_get(actor_data, actor_handle);
  *(short *)(actor + 0x3fc) = 0;
}

/* FUN_0001a080 (0x1a080) — XBE naked draft (batch 69). */
#if defined(__clang__)
static void *(*const b1a080_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void (*const b1a080_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1a080_exitfn)(int) = system_exit;
static void *(*const b1a080_memset)(void *, int, unsigned int) = csmemset;

__attribute__((naked, noinline))
int FUN_0001a080(int actor_handle __attribute__((unused)), char param_2 __attribute__((unused)), char *state_data __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl 0x6325a4, %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movl 0x10(%%ebp), %%esi\n\t"
      "addl $8, %%esp\n\t"
      "xorb %%bl, %%bl\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%eax, %%edi\n\t"
      "jne .LFUN_0001a080_1\n\t"
      "pushl $1\n\t"
      "pushl $0x22\n\t"
      "pushl $0x253dd4\n\t"
      "pushl $0x25334c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0001a080_1:\n\t"
      "pushl $0x34\n\t"
      "pushl $0\n\t"
      "pushl %%esi\n\t"
      "call *%[memset]\n\t"
      "movb 0x160(%%edi), %%al\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_0001a080_2\n\t"
      "movb 0x6(%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_0001a080_2\n\t"
      "movb 0xc(%%ebp), %%dl\n\t"
      "popl %%edi\n\t"
      "movw $0, 0x8(%%esi)\n\t"
      "movb %%dl, 0x3(%%esi)\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0001a080_2:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [dget] "m"(b1a080_dget), [assert] "m"(b1a080_assert), [exitfn] "m"(b1a080_exitfn), [memset] "m"(b1a080_memset)
      : "memory");
}
#else
#error "FUN_0001a080: clang naked draft required"
#endif


/* FUN_0001a100 (0x1a100)
 * Initialize uncover action state from a firing-position record.
 *
 * Validates state_data, zeros it, then if actor is not suppressed/berserk and
 * has an encounter (actor+0x34 != -1) AND param_2 != -1: looks up the firing
 * position in the scenario tag, fills state_data with the position data and
 * marks actor+0x98 as "new firing position chosen". Returns 1 on success, 0 if
 * actor has no encounter or param_2 == -1.
 *
 * Confirmed: datum_get(actor_data, actor_handle) at 0x1a108.
 * Confirmed: assert on state_data (action_uncover.c:0x38).
 * Confirmed: csmemset 0x34 bytes. tag_block_get_element stride 0x18.
 * Confirmed: pos[5] = *(int*)((char*)pos+0x14) stored at state_data+0x10. */
int FUN_0001a100(int actor_handle, short param_2, char *state_data)
{
  char *actor;
  char *enc;
  int *pos;

  actor = (char *)datum_get(actor_data, actor_handle);
  if (state_data == NULL) {
    display_assert("state_data", "c:\\halo\\SOURCE\\ai\\action_uncover.c", 0x38,
                   1);
    system_exit(-1);
  }
  csmemset(state_data, 0, 0x34);
  if ((*(char *)(actor + 0x160) == '\0') && (*(char *)(actor + 6) == '\0') &&
      (*(unsigned int *)(actor + 0x34) != 0xffffffff)) {
    if (param_2 != -1) {
      enc = (char *)tag_block_get_element(
        (char *)global_scenario_get() + 0x42c,
        *(unsigned int *)(actor + 0x34) & 0xffff, 0xb0);
      pos = (int *)tag_block_get_element(enc + 0x98, (int)param_2, 0x18);
      *(short *)(state_data + 10) = param_2;
      *(short *)(state_data + 8) = 1;
      *(int *)(state_data + 0x14) = pos[0];
      *(int *)(state_data + 0x18) = pos[1];
      *(int *)(state_data + 0x1c) = pos[2];
      *(int *)(state_data + 0x10) = pos[5];
      *(short *)(state_data + 0xc) = *(short *)((char *)pos + 0xe);
      *(char *)(state_data + 0x20) = 0;
      *(char *)(state_data + 3) = 1;
      *(char *)(actor + 0x98) = 1;
      return 1;
    }
    return 0;
  }
  return 0;
}

/* FUN_0001a200 (0x1a200) — Run actor uncover-action look-target search.
 *
 * Source file: c:\halo\SOURCE\ai\action_uncover.c (assert line 0x84).
 *
 * Checks three gating flags on the actor record (swarm-assert, flag+0x4c,
 * flag+0x160, flag+0x9d), then builds a 0x670-byte look-state buffer and
 * calls FUN_00027090 to find a look target.  If a target is found:
 *   - If actor+0xa4==0 and look-result (local_48+6) is not 0 or 1:
 *       sets actor+0xa0=1 (with optional ai_debug log when +0xa0 was 0).
 *   - If actor+0xa4==1 and look-result==0:
 *       if distance (local_48+8) < actor_destination_tolerance:
 *         sets actor+0xbc=1 (with optional ai_debug log when +0xbc was 0).
 * Then always calls FUN_000272d0 to find firing position.
 * If firing position == -1: sets actor+0x9e=1.
 * Always returns 0.
 *
 * Confirmed: datum_get(actor_data, actor_handle) stores ESI at 0x1a21e.
 * Confirmed: swarm assert at action_uncover.c:0x84 (flag at actor+6).
 * Confirmed: csmemset 0x670 bytes at 0x1a271-0x1a284.
 * Confirmed: look_type = 3 at state_buf+0x4 (short).
 * Confirmed: store offsets from disasm (buf base EBP-0x7b4).
 * Confirmed: XOR AL,AL at 0x1a40e — always returns 0.
 */
char FUN_0001a200(int actor_handle)
{
  char *actor;
  char state_buf[0x670];
  char big_buf[0x14840];
  char local_48[0x44];
  int local_4;
  int local_8;
  short result;
  short look_result;
  float dist;
  float tol;
  char desc_buf[0x100];
  short fire_result;

  actor = (char *)datum_get(actor_data, actor_handle);
  if (*(char *)(actor + 6) != '\0') {
    display_assert("!actor->meta.swarm",
                   "c:\\halo\\SOURCE\\ai\\action_uncover.c", 0x84, 1);
    system_exit(-1);
  }
  if (*(char *)(actor + 0x4c) == '\0')
    return 0;
  if (*(char *)(actor + 0x160) != '\0')
    return 0;
  if (*(char *)(actor + 0x9d) != '\0')
    return 0;

  csmemset(state_buf, 0, 0x670);
  *(short *)(state_buf + 0x4) = 3;

  if (*(short *)(actor + 0xa4) == 1) {
    *(char *)(state_buf + 0x20) = 1;
    *(int *)(state_buf + 0x24) = *(int *)(actor + 0xb0);
    *(int *)(state_buf + 0x28) = *(int *)(actor + 0xb4);
    *(int *)(state_buf + 0x2c) = *(int *)(actor + 0xb8);
    *(int *)(state_buf + 0x30) = *(int *)(actor + 0xac);
    *(short *)(state_buf + 0x34) = *(short *)(actor + 0xa8);
  } else {
    *(char *)(state_buf + 0x41) = *(char *)(actor + 0xa0);
  }

  result = (short)FUN_00027090(actor_handle, state_buf, local_48, &local_8,
                               big_buf, &local_4);
  if (result != -1) {
    if (*(short *)(actor + 0xa4) == 0) {
      look_result = *(short *)(local_48 + 6);
      if ((look_result != 0) && (look_result != 1)) {
        if ((*(char *)(actor + 0xa0) == '\0') && (*(char *)0x5aca64 != '\0')) {
          ai_debug_describe_actor(actor_handle, -1, 1, desc_buf, 0x100);
          error(2, "%s: unable to see target's current location", desc_buf);
        }
        *(char *)(actor + 0xa0) = 1;
      }
    } else {
      if (*(short *)(local_48 + 6) == 0) {
        dist = *(float *)(local_48 + 8);
        tol = actor_destination_tolerance(actor_handle);
        if (dist < tol) {
          if ((*(char *)(actor + 0xbc) == '\0') &&
              (*(char *)0x5aca64 != '\0')) {
            ai_debug_describe_actor(actor_handle, -1, 1, desc_buf, 0x100);
            error(2, "%s: inspected pursuit location", desc_buf);
          }
          *(char *)(actor + 0xbc) = 1;
        }
      }
    }
  }

  fire_result = (short)FUN_000272d0(actor_handle, result, local_48, local_8,
                                    (unsigned int)big_buf, (char)local_4);
  if (fire_result == -1) {
    *(char *)(actor + 0x9e) = 1;
  }
  return 0;
}

/* FUN_0001a420 (0x1a420) — XBE naked draft (batch 75). */
#if defined(__clang__)
static void *(*const b1a420_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void *(*const b1a420_tag)(int, int) = tag_get;

__attribute__((naked, noinline))
void FUN_0001a420(int actor_handle __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl 0x6325a4, %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x58(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x61637472\n\t"
      "call *%[tag]\n\t"
      "movl %%eax, %%edi\n\t"
      "movl 0x270(%%esi), %%eax\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_0001a420_12\n\t"
      "pushl %%eax\n\t"
      "movl 0x5ab23c, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "addl $8, %%esp\n\t"
      "xorb %%dl, %%dl\n\t"
      "cmpw $0, 0xa4(%%esi)\n\t"
      "jne .LFUN_0001a420_4\n\t"
      "movb 0x162(%%esi), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "je .LFUN_0001a420_1\n\t"
      "movb $1, 0x454(%%esi)\n\t"
      "movb $1, 0x455(%%esi)\n\t"
      "movb $1, %%dl\n\t"
      "jmp .LFUN_0001a420_4\n\t"
      ".LFUN_0001a420_1:\n\t"
      "testb $0x10, (%%edi)\n\t"
      "je .LFUN_0001a420_2\n\t"
      "cmpw $5, 0x268(%%esi)\n\t"
      "jmp .LFUN_0001a420_3\n\t"
      ".LFUN_0001a420_2:\n\t"
      "cmpw $6, 0x268(%%esi)\n\t"
      ".LFUN_0001a420_3:\n\t"
      "setge %%cl\n\t"
      "movb %%cl, 0x454(%%esi)\n\t"
      ".LFUN_0001a420_4:\n\t"
      "movb 0x454(%%esi), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "movl $2, %%edi\n\t"
      "je .LFUN_0001a420_5\n\t"
      "movw 0x38(%%eax), %%cx\n\t"
      "testw %%cx, %%cx\n\t"
      "je .LFUN_0001a420_6\n\t"
      "cmpw $1, %%cx\n\t"
      "je .LFUN_0001a420_6\n\t"
      ".LFUN_0001a420_5:\n\t"
      "testb %%dl, %%dl\n\t"
      "je .LFUN_0001a420_7\n\t"
      ".LFUN_0001a420_6:\n\t"
      "movw $7, 0x3e8(%%esi)\n\t"
      "jmp .LFUN_0001a420_10\n\t"
      ".LFUN_0001a420_7:\n\t"
      "cmpw $5, 0x268(%%esi)\n\t"
      "jge .LFUN_0001a420_8\n\t"
      "movw $3, 0x3e8(%%esi)\n\t"
      "jmp .LFUN_0001a420_10\n\t"
      ".LFUN_0001a420_8:\n\t"
      "movw 0x38(%%eax), %%ax\n\t"
      "cmpw %%di, %%ax\n\t"
      "je .LFUN_0001a420_9\n\t"
      "cmpw $4, %%ax\n\t"
      "je .LFUN_0001a420_9\n\t"
      "movw $5, 0x3e8(%%esi)\n\t"
      "jmp .LFUN_0001a420_10\n\t"
      ".LFUN_0001a420_9:\n\t"
      "movw %%di, 0x3e8(%%esi)\n\t"
      ".LFUN_0001a420_10:\n\t"
      "movw 0xa4(%%esi), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "jne .LFUN_0001a420_11\n\t"
      "movw %%di, 0x3ec(%%esi)\n\t"
      "jmp .LFUN_0001a420_12\n\t"
      ".LFUN_0001a420_11:\n\t"
      "cmpw $1, %%ax\n\t"
      "jne .LFUN_0001a420_12\n\t"
      "movw $3, 0x3ec(%%esi)\n\t"
      "leal 0xb0(%%esi), %%edx\n\t"
      "movl (%%edx), %%ecx\n\t"
      "leal 0x3f0(%%esi), %%eax\n\t"
      "movl %%ecx, (%%eax)\n\t"
      "movl 0x4(%%edx), %%ecx\n\t"
      "movl %%ecx, 0x4(%%eax)\n\t"
      "movl 0x8(%%edx), %%edx\n\t"
      "movl %%edx, 0x8(%%eax)\n\t"
      ".LFUN_0001a420_12:\n\t"
      "movw $3, 0x3fc(%%esi)\n\t"
      "movb 0x9c(%%esi), %%al\n\t"
      "movb %%al, 0x426(%%esi)\n\t"
      "movb 0x9c(%%esi), %%cl\n\t"
      "popl %%edi\n\t"
      "movb %%cl, 0x427(%%esi)\n\t"
      "movb $0, 0x428(%%esi)\n\t"
      "movb $0, 0x424(%%esi)\n\t"
      "movb $1, 0x425(%%esi)\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [dget] "m"(b1a420_dget), [tag] "m"(b1a420_tag)
      : "memory");
}
#else
#error "FUN_0001a420: clang naked draft required"
#endif


/* FUN_0001a590 (0x1a590)
 * Mark actor look-state as interrupted (target type 1 path, byte +0x9d).
 *
 * If the look-target type word at actor+0xa4 equals 1, clears the
 * target-acquired index at actor+0xa6 (set to 0xffff = none) and
 * sets the look-state byte at actor+0x9d to 1.  Differs from FUN_00019ac0
 * only in the byte offset written: 0x9d vs 0x9c.
 *
 * Confirmed: ADD EAX,0x9c; MOV ECX,0x1; CMP word [EAX+0x8],CX;
 *   MOV word [EAX+0xa],0xffff; MOV byte [EAX+0x1],CL. */
void FUN_0001a590(int actor_handle)
{
  char *actor;
  actor = (char *)datum_get(actor_data, actor_handle);
  if (*(short *)(actor + 0xa4) == 1) {
    *(short *)(actor + 0xa6) = (short)0xffff;
    *(char *)(actor + 0x9d) = 1;
  }
}

/* FUN_0001a5d0 (0x1a5d0)
 * Reset actor look-target handles to invalid (-1).
 *
 * Identical body to FUN_00019af0: clears actor+0xa8 (int16_t) and
 * actor+0xac (int32_t) to -1.  Compiled as a separate function at a
 * different address.
 *
 * Confirmed: ADD EAX,0x9c; OR ECX,0xffffffff;
 *   MOV word [EAX+0xc],CX (actor+0xa8); MOV dword [EAX+0x10],ECX (actor+0xac).
 */
void FUN_0001a5d0(int actor_handle)
{
  char *actor;
  actor = (char *)datum_get(actor_data, actor_handle);
  *(short *)(actor + 0xa8) = -1;
  *(int *)(actor + 0xac) = -1;
}

/* FUN_0001a600 (0x1a600) — readable C lift. */
void FUN_0001a600(int actor_handle, int *param_2)
{
  unsigned char *actor;
  int *src;
  int i;

  actor = (unsigned char *)datum_get(*(void **)0x6325a4, actor_handle);
  if (actor[0x9c] != 0)
    src = *(int **)0x2ee6d8;
  else
    src = *(int **)0x2ee6ec;
  for (i = 0; i < 4; i++)
    param_2[i] = src[i];
}



/* FUN_0001a670 (0x1a670) — XBE naked draft (batch 78). */
#if defined(__clang__)
static void *(*const b1a670_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void *(*const b1a670_tag)(int, int) = tag_get;
static int *(*const b1a670_gseed)(void) = get_global_random_seed_address;
static float (*const b1a670_rrange)(int *, float, float) = random_real_range;
static void (*const b1a670_ftol)(void) = FUN_001d9068;
static char * (*const b1a670_c49ac0)(int actor_handle, int object_handle, char with_actor, char *buf, int buf_size) = ai_debug_describe_actor;
static void (*const b1a670_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;
static void (*const b1a670_c46f10)(int16_t type, int unit_handle, int param3, int param4, int16_t param5, int16_t param6, int16_t param7) = FUN_00046f10;

__attribute__((naked, noinline))
void FUN_0001a670(int actor_handle __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x10c, %%esp\n\t"
      "movl 0x6325a4, %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x58(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x61637472\n\t"
      "call *%[tag]\n\t"
      "movl %%eax, %%ecx\n\t"
      "movl 0x340(%%ecx), %%eax\n\t"
      "movl 0x33c(%%ecx), %%edx\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "movb 0x9f(%%esi), %%al\n\t"
      "addl $0x10, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      "jne .LFUN_0001a670_2\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fcomps 0x344(%%ecx)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .LFUN_0001a670_1\n\t"
      "movl 0x344(%%ecx), %%edx\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      ".LFUN_0001a670_1:\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fcomps 0x348(%%ecx)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .LFUN_0001a670_2\n\t"
      "movl 0x348(%%ecx), %%eax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      ".LFUN_0001a670_2:\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[gseed]\n\t"
      "pushl %%eax\n\t"
      "call *%[rrange]\n\t"
      "fsts -0xc(%%ebp)\n\t"
      "fmuls 0x253394\n\t"
      "addl $0xc, %%esp\n\t"
      "call *%[ftol]\n\t"
      "movl %%eax, 0xc4(%%esi)\n\t"
      "movl %%eax, 0xc8(%%esi)\n\t"
      "movb 0x5aca64, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0001a670_5\n\t"
      "pushl $0x100\n\t"
      "leal -0x10c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $1\n\t"
      "pushl $-1\n\t"
      "pushl %%edi\n\t"
      "call *%[c49ac0]\n\t"
      "movb 0x9f(%%esi), %%al\n\t"
      "addl $0x14, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "movl $0x25386f, %%ecx\n\t"
      "jne .LFUN_0001a670_3\n\t"
      "movl $0x253e94, %%ecx\n\t"
      ".LFUN_0001a670_3:\n\t"
      "cmpw $0, 0xa4(%%esi)\n\t"
      "movl $0x253e8c, %%eax\n\t"
      "je .LFUN_0001a670_4\n\t"
      "movl $0x253e84, %%eax\n\t"
      ".LFUN_0001a670_4:\n\t"
      "flds -0xc(%%ebp)\n\t"
      "pushl %%ecx\n\t"
      "subl $0x18, %%esp\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "leal -0x10c(%%ebp), %%ecx\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x253e44\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $0x2c, %%esp\n\t"
      ".LFUN_0001a670_5:\n\t"
      "cmpw $0, 0xa4(%%esi)\n\t"
      "jne .LFUN_0001a670_6\n\t"
      "movl 0x270(%%esi), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_0001a670_6\n\t"
      "cmpw $3, 0x6e(%%esi)\n\t"
      "jge .LFUN_0001a670_6\n\t"
      "movl 0x5ab23c, %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%edx\n\t"
      "call *%[dget]\n\t"
      "movl 0x18(%%eax), %%eax\n\t"
      "movl 0x18(%%esi), %%ecx\n\t"
      "pushl $0\n\t"
      "pushl $-1\n\t"
      "pushl $-1\n\t"
      "pushl $-1\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x15\n\t"
      "call *%[c46f10]\n\t"
      "addl $0x24, %%esp\n\t"
      ".LFUN_0001a670_6:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [dget] "m"(b1a670_dget), [tag] "m"(b1a670_tag), [gseed] "m"(b1a670_gseed), [rrange] "m"(b1a670_rrange), [ftol] "m"(b1a670_ftol), [c49ac0] "m"(b1a670_c49ac0), [c8f390] "m"(b1a670_c8f390), [c46f10] "m"(b1a670_c46f10)
      : "memory");
}
#else
#error "FUN_0001a670: clang naked draft required"
#endif


/* FUN_0001a7e0 (0x1a7e0) — XBE naked draft (batch 69). */
#if defined(__clang__)
static void *(*const b1a7e0_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void *(*const b1a7e0_tag)(int, int) = tag_get;
static float (*const b1a7e0_c121a0)(const float *a, const float *b) = distance_squared3d;
static void (*const b1a7e0_c24be0)(int actor_handle, short param_2, char param_3) = FUN_00024be0;
static char * (*const b1a7e0_c49ac0)(int actor_handle, int object_handle, char with_actor, char *buf, int buf_size) = ai_debug_describe_actor;
static int (*const b1a7e0_c1d90f0)(char *buffer, const char *format, ...) = crt_sprintf;
static char * (*const b1a7e0_c8dff0)(char *destination, const char *source) = csstrcpy;
static void (*const b1a7e0_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;

__attribute__((naked, noinline))
void FUN_0001a7e0(int actor_handle __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x204, %%esp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl 0x6325a4, %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%esi\n\t"
      "movb 0x9d(%%esi), %%al\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_0001a7e0_26\n\t"
      "movl 0x58(%%esi), %%edx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x61637472\n\t"
      "call *%[tag]\n\t"
      "movw 0xa4(%%esi), %%cx\n\t"
      "addl $8, %%esp\n\t"
      "testw %%cx, %%cx\n\t"
      "movb $1, %%bl\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "movb $0, 0x9c(%%esi)\n\t"
      "jne .LFUN_0001a7e0_2\n\t"
      "cmpw $4, 0x2f8(%%eax)\n\t"
      "jne .LFUN_0001a7e0_1\n\t"
      "cmpw $6, 0x268(%%esi)\n\t"
      "setne %%al\n\t"
      "movb %%al, 0x9c(%%esi)\n\t"
      "jmp .LFUN_0001a7e0_4\n\t"
      ".LFUN_0001a7e0_1:\n\t"
      "testb $2, (%%eax)\n\t"
      "je .LFUN_0001a7e0_4\n\t"
      "cmpw $5, 0x268(%%esi)\n\t"
      "jne .LFUN_0001a7e0_4\n\t"
      "movl 0x270(%%esi), %%ecx\n\t"
      "movl 0x5ab23c, %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[dget]\n\t"
      "movb 0x121(%%eax), %%cl\n\t"
      "addl $8, %%esp\n\t"
      "cmpb $2, %%cl\n\t"
      "jg .LFUN_0001a7e0_4\n\t"
      "jmp .LFUN_0001a7e0_3\n\t"
      ".LFUN_0001a7e0_2:\n\t"
      "cmpw $1, %%cx\n\t"
      "jne .LFUN_0001a7e0_4\n\t"
      "cmpw $4, 0x2f8(%%eax)\n\t"
      "je .LFUN_0001a7e0_3\n\t"
      "testb $4, (%%eax)\n\t"
      "je .LFUN_0001a7e0_4\n\t"
      "leal 0xb0(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal 0x12c(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c121a0]\n\t"
      "fcomps 0x253f00\n\t"
      "addl $8, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_0001a7e0_4\n\t"
      ".LFUN_0001a7e0_3:\n\t"
      "movb $1, 0x9c(%%esi)\n\t"
      ".LFUN_0001a7e0_4:\n\t"
      "movb 0x504(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0001a7e0_5\n\t"
      "movl $0, 0xc0(%%esi)\n\t"
      "jmp .LFUN_0001a7e0_6\n\t"
      ".LFUN_0001a7e0_5:\n\t"
      "movl 0xc0(%%esi), %%edx\n\t"
      "incl %%edx\n\t"
      "cmpw $0, 0xa4(%%esi)\n\t"
      "movl %%edx, 0xc0(%%esi)\n\t"
      "movl %%edx, %%eax\n\t"
      "jne .LFUN_0001a7e0_8\n\t"
      "cmpl $0x1e, %%eax\n\t"
      "jl .LFUN_0001a7e0_6\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x3b8(%%esi), %%dx\n\t"
      "pushl $0\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c24be0]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_0001a7e0_6:\n\t"
      "cmpw $0, 0xa4(%%esi)\n\t"
      "jne .LFUN_0001a7e0_8\n\t"
      "movl 0x270(%%esi), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_0001a7e0_9\n\t"
      "movl 0x5ab23c, %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $0, 0x32(%%eax)\n\t"
      "setg %%al\n\t"
      "testb %%al, %%al\n\t"
      "movb %%al, -0x1(%%ebp)\n\t"
      "je .LFUN_0001a7e0_7\n\t"
      "cmpw $5, 0x268(%%esi)\n\t"
      "jge .LFUN_0001a7e0_7\n\t"
      "xorb %%bl, %%bl\n\t"
      "jmp .LFUN_0001a7e0_9\n\t"
      ".LFUN_0001a7e0_7:\n\t"
      "movb $1, %%bl\n\t"
      "jmp .LFUN_0001a7e0_9\n\t"
      ".LFUN_0001a7e0_8:\n\t"
      "movb 0xbc(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "sete %%bl\n\t"
      ".LFUN_0001a7e0_9:\n\t"
      "cmpw $-1, 0x3b8(%%esi)\n\t"
      "jne .LFUN_0001a7e0_13\n\t"
      "movb $1, 0x9e(%%esi)\n\t"
      ".LFUN_0001a7e0_10:\n\t"
      "movl 0xc8(%%esi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jle .LFUN_0001a7e0_11\n\t"
      "decl %%eax\n\t"
      "movl %%eax, 0xc8(%%esi)\n\t"
      ".LFUN_0001a7e0_11:\n\t"
      "incl 0xcc(%%esi)\n\t"
      ".LFUN_0001a7e0_12:\n\t"
      "movl 0xc8(%%esi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_0001a7e0_15\n\t"
      "cmpl $0x168, 0xcc(%%esi)\n\t"
      "jge .LFUN_0001a7e0_15\n\t"
      "xorb %%bl, %%bl\n\t"
      "jmp .LFUN_0001a7e0_16\n\t"
      ".LFUN_0001a7e0_13:\n\t"
      "testb %%bl, %%bl\n\t"
      "je .LFUN_0001a7e0_10\n\t"
      "movb 0x162(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_0001a7e0_14\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_0001a7e0_14\n\t"
      "movb 0x504(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0001a7e0_10\n\t"
      ".LFUN_0001a7e0_14:\n\t"
      "movl 0xc4(%%esi), %%edx\n\t"
      "movl %%edx, 0xc8(%%esi)\n\t"
      "jmp .LFUN_0001a7e0_12\n\t"
      ".LFUN_0001a7e0_15:\n\t"
      "movb $1, %%bl\n\t"
      ".LFUN_0001a7e0_16:\n\t"
      "cmpw $1, 0xa4(%%esi)\n\t"
      "jne .LFUN_0001a7e0_17\n\t"
      "movb 0xbc(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0001a7e0_17\n\t"
      "movb $1, %%bl\n\t"
      "jmp .LFUN_0001a7e0_18\n\t"
      ".LFUN_0001a7e0_17:\n\t"
      "testb %%bl, %%bl\n\t"
      "je .LFUN_0001a7e0_25\n\t"
      ".LFUN_0001a7e0_18:\n\t"
      "movb 0x5aca64, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0001a7e0_25\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "pushl $0x100\n\t"
      "leal -0x204(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $1\n\t"
      "pushl $-1\n\t"
      "pushl %%ecx\n\t"
      "call *%[c49ac0]\n\t"
      "movl 0xc8(%%esi), %%eax\n\t"
      "addl $0x14, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_0001a7e0_19\n\t"
      "movl 0xc4(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x104(%%ebp), %%eax\n\t"
      "pushl $0x253eec\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d90f0]\n\t"
      "addl $0xc, %%esp\n\t"
      "jmp .LFUN_0001a7e0_23\n\t"
      ".LFUN_0001a7e0_19:\n\t"
      "movl 0xcc(%%esi), %%eax\n\t"
      "cmpl $0x168, %%eax\n\t"
      "jl .LFUN_0001a7e0_20\n\t"
      "pushl %%eax\n\t"
      "leal -0x104(%%ebp), %%ecx\n\t"
      "pushl $0x253ed8\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1d90f0]\n\t"
      "addl $0xc, %%esp\n\t"
      "jmp .LFUN_0001a7e0_23\n\t"
      ".LFUN_0001a7e0_20:\n\t"
      "cmpw $1, 0xa4(%%esi)\n\t"
      "jne .LFUN_0001a7e0_21\n\t"
      "movb 0xbc(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0001a7e0_21\n\t"
      "pushl $0x253ec4\n\t"
      "leal -0x104(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "jmp .LFUN_0001a7e0_22\n\t"
      ".LFUN_0001a7e0_21:\n\t"
      "pushl $0x253eb0\n\t"
      "leal -0x104(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      ".LFUN_0001a7e0_22:\n\t"
      "call *%[c8dff0]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_0001a7e0_23:\n\t"
      "cmpw $0, 0xa4(%%esi)\n\t"
      "movl $0x253e8c, %%eax\n\t"
      "je .LFUN_0001a7e0_24\n\t"
      "movl $0x253e84, %%eax\n\t"
      ".LFUN_0001a7e0_24:\n\t"
      "leal -0x104(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "leal -0x204(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x253e98\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0001a7e0_25:\n\t"
      "movb %%bl, 0x9d(%%esi)\n\t"
      "popl %%ebx\n\t"
      ".LFUN_0001a7e0_26:\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [dget] "m"(b1a7e0_dget), [tag] "m"(b1a7e0_tag), [c121a0] "m"(b1a7e0_c121a0), [c24be0] "m"(b1a7e0_c24be0), [c49ac0] "m"(b1a7e0_c49ac0), [c1d90f0] "m"(b1a7e0_c1d90f0), [c8dff0] "m"(b1a7e0_c8dff0), [c8f390] "m"(b1a7e0_c8f390)
      : "memory");
}
#else
#error "FUN_0001a7e0: clang naked draft required"
#endif


/* FUN_0001aae0 (0x1aae0)
 * Get an object's bounding sphere (center and radius).
 *
 * Resolves the object via object_get_and_verify_type with type_mask=0xffffffff
 * (all types accepted).  Asserts that center and radius pointers are non-NULL.
 * Copies the three-float center position from object+0x50..0x58 and the scalar
 * radius from object+0x5c.
 *
 * Confirmed: PUSH -0x1; PUSH param_1; CALL 0x13d680
 * (object_get_and_verify_type). Confirmed: MOV ESI,[EBP+0xc] (center); TEST
 * ESI,ESI; JNZ ok; display_assert("center","..\\objects\\objects.h",0x217,1);
 * system_exit(-1). Confirmed: MOV EBX,[EBP+0x10] (radius); TEST EBX,EBX; JNZ
 * ok; display_assert("radius","..\\objects\\objects.h",0x218,1);
 * system_exit(-1). Confirmed: LEA ECX,[EDI+0x50]; MOV EDX,[ECX]; MOV [ESI],EDX;
 *   MOV EAX,[ECX+0x4]; MOV [ESI+0x4],EAX; MOV ECX,[ECX+0x8]; MOV [ESI+0x8],ECX;
 *   MOV EDX,[EDI+0x5c]; MOV [EBX],EDX. */
void FUN_0001aae0(int object_handle, float *center, float *radius)
{
  char *obj;
  obj = (char *)object_get_and_verify_type(object_handle, 0xffffffff);
  if (center == NULL) {
    display_assert("center", "..\\objects\\objects.h", 0x217, 1);
    system_exit(-1);
  }
  if (radius == NULL) {
    display_assert("radius", "..\\objects\\objects.h", 0x218, 1);
    system_exit(-1);
  }
  center[0] = *(float *)(obj + 0x50);
  center[1] = *(float *)(obj + 0x54);
  center[2] = *(float *)(obj + 0x58);
  *radius = *(float *)(obj + 0x5c);
}

/* FUN_0001ab70 (0x1ab70) — Initialize actor look-at snapshot.
 * Clears the look-at timer (actor+0xaa), records current game time at
 * actor+0xac, and copies the 3-float vector at actor+0x12c into actor+0xb0. */
void FUN_0001ab70(int actor_handle)
{
  char *actor;
  char *src;
  int t;
  int v;
  actor = (char *)datum_get(actor_data, actor_handle);
  *(short *)(actor + 0xaa) = 0;
  t = game_time_get();
  *(int *)(actor + 0xac) = t;
  src = actor + 0x12c;
  v = *(int *)src;
  actor += 0xb0;
  *(int *)actor = v;
  *(int *)(actor + 4) = *(int *)(src + 4);
  *(int *)(actor + 8) = *(int *)(src + 8);
}

/* FUN_0001abd0 (0x1abd0)
 * Clear actor look-at target: set the 32-bit field at actor+0xe4 to -1
 * (null/invalid handle sentinel).
 */
void FUN_0001abd0(int actor_handle)
{
  char *actor;
  actor = (char *)datum_get(actor_data, actor_handle);
  *(int *)(actor + 0xe4) = -1;
}

/* FUN_0001ac00 (0x1ac00) — XBE naked draft (batch 69). */
#if defined(__clang__)
static void *(*const b1ac00_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static char (*const b1ac00_c2a3d0)(int actor_handle) = FUN_0002a3d0;

__attribute__((naked, noinline))
void FUN_0001ac00(int actor_handle __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl 0x6325a4, %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%esi\n\t"
      "movb 0xc8(%%esi), %%al\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "addl $8, %%esp\n\t"
      "cmpb %%bl, %%al\n\t"
      "je .LFUN_0001ac00_1\n\t"
      "movl $4, %%eax\n\t"
      "movw %%ax, 0x3e8(%%esi)\n\t"
      "movw %%ax, 0x3ec(%%esi)\n\t"
      "leal 0xd8(%%esi), %%ecx\n\t"
      "movl (%%ecx), %%eax\n\t"
      "leal 0x3f0(%%esi), %%edx\n\t"
      "movl %%eax, (%%edx)\n\t"
      "movl 0x4(%%ecx), %%eax\n\t"
      "movl %%eax, 0x4(%%edx)\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "movl %%ecx, 0x8(%%edx)\n\t"
      "jmp .LFUN_0001ac00_3\n\t"
      ".LFUN_0001ac00_1:\n\t"
      "pushl %%edi\n\t"
      "call *%[c2a3d0]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0001ac00_2\n\t"
      "movw $3, 0x3e8(%%esi)\n\t"
      "movw %%bx, 0x3ec(%%esi)\n\t"
      "jmp .LFUN_0001ac00_3\n\t"
      ".LFUN_0001ac00_2:\n\t"
      "movw %%bx, 0x3e8(%%esi)\n\t"
      ".LFUN_0001ac00_3:\n\t"
      "popl %%edi\n\t"
      "movb %%bl, 0x454(%%esi)\n\t"
      "movb %%bl, 0x426(%%esi)\n\t"
      "movb %%bl, 0x427(%%esi)\n\t"
      "movb %%bl, 0x428(%%esi)\n\t"
      "movb %%bl, 0x424(%%esi)\n\t"
      "movb %%bl, 0x425(%%esi)\n\t"
      "movw $4, 0x3fc(%%esi)\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [dget] "m"(b1ac00_dget), [c2a3d0] "m"(b1ac00_c2a3d0)
      : "memory");
}
#else
#error "FUN_0001ac00: clang naked draft required"
#endif


/* FUN_00024ca0 (0x24ca0) — readable C lift. */
char FUN_00024ca0(int actor_handle, short param_2)
{
  char *actor;
  int i;

  actor = (char *)datum_get(*(void **)0x6325a4, actor_handle);
  if (param_2 == -1)
    return 0;
  for (i = 0; i < 4; i++) {
    if (param_2 == *(short *)(actor + 0x3ca + i * 4))
      return 1;
  }
  return 0;
}

/* FUN_00024cf0 (0x24cf0) — XBE naked draft (batch 69). */
#if defined(__clang__)
static void *(*const b24cf0_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static char (*const b24cf0_c24ca0)(int actor_handle, short param_2) = FUN_00024ca0;
static void (*const b24cf0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b24cf0_exitfn)(int) = system_exit;
static float (*const b24cf0_c10cd40)(float *p1, float *p2, float *p3) = FUN_0010cd40;
static void (*const b24cf0_c24000)(void *ctx, float score, int type, void *position) = FUN_00024000;
static float (*const b24cf0_c10ce10)(float *p1, float *p2, float *p3, float *p4) = vector_to_line_distance_squared3d;
static void *(*const b24cf0_get)(int, int) = object_get_and_verify_type;
static vector3_t * (*const b24cf0_c1412f0)(int object_handle, vector3_t *out_position) = object_get_world_position;

__attribute__((naked, noinline))
void FUN_00024cf0(int actor_handle __attribute__((unused)), char *eval_state __attribute__((unused)), unsigned short fp_count __attribute__((unused)), char *fp_array __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x3c, %%esp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl 0x6325a4, %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%edi\n\t"
      "movw 0x10(%%ebp), %%ax\n\t"
      "addl $8, %%esp\n\t"
      "testw %%ax, %%ax\n\t"
      "jle .LFUN_00024cf0_21\n\t"
      "movl 0x14(%%ebp), %%esi\n\t"
      "movzwl %%ax, %%edx\n\t"
      "addl $0x14, %%esi\n\t"
      "movl %%esi, -0x4(%%ebp)\n\t"
      "movl %%edx, -0x20(%%ebp)\n\t"
      "leal (%%ebx), %%ebx\n\t"
      ".LFUN_00024cf0_1:\n\t"
      "movb 0x1c(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00024cf0_20\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw -0x10(%%esi), %%ax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c24ca0]\n\t"
      "movl 0xc(%%ebp), %%ebx\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00024cf0_2\n\t"
      "movb $1, 0x1d(%%esi)\n\t"
      "movb 0x14(%%ebx), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00024cf0_2\n\t"
      "movb $0, 0x1c(%%esi)\n\t"
      "jmp .LFUN_00024cf0_20\n\t"
      ".LFUN_00024cf0_2:\n\t"
      "movb 0x40(%%ebx), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00024cf0_10\n\t"
      "cmpw $0, 0x280(%%edi)\n\t"
      "jle .LFUN_00024cf0_3\n\t"
      "movb 0x287(%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00024cf0_4\n\t"
      ".LFUN_00024cf0_3:\n\t"
      "pushl $1\n\t"
      "pushl $0xba\n\t"
      "pushl $0x254c8c\n\t"
      "pushl $0x254e08\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00024cf0_4:\n\t"
      "flds 0x2c8(%%edi)\n\t"
      "movl -0x14(%%esi), %%ecx\n\t"
      "fsubs 0x2b0(%%edi)\n\t"
      "leal 0x2b0(%%edi), %%ebx\n\t"
      "leal -0x14(%%esi), %%eax\n\t"
      "movl %%eax, -0x24(%%ebp)\n\t"
      "fstps -0x3c(%%ebp)\n\t"
      "flds 0x2cc(%%edi)\n\t"
      "fsubs 0x4(%%ebx)\n\t"
      "fstps -0x38(%%ebp)\n\t"
      "flds 0x2d0(%%edi)\n\t"
      "fsubs 0x8(%%ebx)\n\t"
      "fstps -0x34(%%ebp)\n\t"
      "flds (%%ecx)\n\t"
      "fsubs 0x2dc(%%edi)\n\t"
      "flds 0x4(%%ecx)\n\t"
      "fsubs 0x2e0(%%edi)\n\t"
      "flds 0x8(%%ecx)\n\t"
      "fsubs 0x2e4(%%edi)\n\t"
      "flds 0x2d8(%%edi)\n\t"
      "fadds 0x254e04\n\t"
      "fld %%st(1)\n\t"
      ".byte 0xd8, 0xca\n\t"
      "fld %%st(3)\n\t"
      ".byte 0xd8, 0xcc\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fld %%st(4)\n\t"
      ".byte 0xd8, 0xcd\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fld %%st(1)\n\t"
      ".byte 0xd8, 0xca\n\t"
      "fcompp\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "fnstsw %%ax\n\t"
      "fstp %%st(0)\n\t"
      "testb $0x41, %%ah\n\t"
      "fstp %%st(0)\n\t"
      "jne .LFUN_00024cf0_8\n\t"
      "leal -0x3c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c10cd40]\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "flds 0x294(%%edi)\n\t"
      "addl $0xc, %%esp\n\t"
      "fld %%st(0)\n\t"
      "movl $0, -0x14(%%ebp)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fcompp\n\t"
      "fnstsw %%ax\n\t"
      "fstp %%st(0)\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00024cf0_5\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "movb $1, 0x1d(%%esi)\n\t"
      "movb 0x14(%%eax), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "jne .LFUN_00024cf0_7\n\t"
      "movb $0, 0x1c(%%esi)\n\t"
      "jmp .LFUN_00024cf0_20\n\t"
      ".LFUN_00024cf0_5:\n\t"
      "flds 0x294(%%edi)\n\t"
      "fadds 0x254e04\n\t"
      "fld %%st(0)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fcompp\n\t"
      "fnstsw %%ax\n\t"
      "fstp %%st(0)\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00024cf0_6\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fsqrt\n\t"
      "fsubs 0x294(%%edi)\n\t"
      "fmuls 0x253f78\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "jmp .LFUN_00024cf0_7\n\t"
      ".LFUN_00024cf0_6:\n\t"
      "movl $0x41a00000, -0x14(%%ebp)\n\t"
      ".LFUN_00024cf0_7:\n\t"
      "movl -0x14(%%ebp), %%ecx\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "movl -0x24(%%ebp), %%esi\n\t"
      "pushl $0x17\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c24000]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_00024cf0_8:\n\t"
      "flds 0x12c(%%edi)\n\t"
      "leal 0x12c(%%edi), %%esi\n\t"
      "fsubs 0x2dc(%%edi)\n\t"
      "flds 0x4(%%esi)\n\t"
      "fsubs 0x2e0(%%edi)\n\t"
      "flds 0x8(%%esi)\n\t"
      "fsubs 0x2e4(%%edi)\n\t"
      "flds 0x2d8(%%edi)\n\t"
      "fadds 0x254644\n\t"
      "fld %%st(1)\n\t"
      ".byte 0xd8, 0xca\n\t"
      "fld %%st(3)\n\t"
      ".byte 0xd8, 0xcc\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fld %%st(4)\n\t"
      ".byte 0xd8, 0xcd\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fld %%st(1)\n\t"
      ".byte 0xd8, 0xca\n\t"
      "fcompp\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "fnstsw %%ax\n\t"
      "fstp %%st(0)\n\t"
      "testb $0x41, %%ah\n\t"
      "fstp %%st(0)\n\t"
      "jne .LFUN_00024cf0_9\n\t"
      "flds 0x2d4(%%edi)\n\t"
      "fcomps 0x294(%%edi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00024cf0_9\n\t"
      "leal -0x3c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "call *%[c10cd40]\n\t"
      "flds 0x294(%%edi)\n\t"
      "fld %%st(0)\n\t"
      "addl $0xc, %%esp\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fxch %%st(1)\n\t"
      "fxch %%st(2)\n\t"
      "fcompp\n\t"
      "fnstsw %%ax\n\t"
      "fstp %%st(0)\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00024cf0_9\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "flds -0x8(%%eax)\n\t"
      "fmuls 0x254644\n\t"
      "fstps -0x30(%%ebp)\n\t"
      "flds -0x4(%%eax)\n\t"
      "fmuls 0x254644\n\t"
      "fstps -0x2c(%%ebp)\n\t"
      "flds (%%eax)\n\t"
      "fmuls 0x254644\n\t"
      "fsts -0x28(%%ebp)\n\t"
      "fmuls -0x28(%%ebp)\n\t"
      "flds -0x2c(%%ebp)\n\t"
      "fmuls -0x2c(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds -0x30(%%ebp)\n\t"
      "fmuls -0x30(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fcomps 0x253f44\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00024cf0_9\n\t"
      "movl 0x294(%%edi), %%ecx\n\t"
      "leal -0x3c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ebx\n\t"
      "leal -0x30(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "movl %%ecx, -0x1c(%%ebp)\n\t"
      "call *%[c10ce10]\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fmuls -0x1c(%%ebp)\n\t"
      "addl $0x10, %%esp\n\t"
      "fcompp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00024cf0_9\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "movb $1, 0x1d(%%ecx)\n\t"
      "movb 0x14(%%edx), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00024cf0_9\n\t"
      "movl %%ecx, %%eax\n\t"
      "movb $0, 0x1c(%%eax)\n\t"
      "movl %%ecx, %%esi\n\t"
      "jmp .LFUN_00024cf0_20\n\t"
      ".LFUN_00024cf0_9:\n\t"
      "movl -0x4(%%ebp), %%esi\n\t"
      "movl 0xc(%%ebp), %%ebx\n\t"
      ".LFUN_00024cf0_10:\n\t"
      "movl -0x14(%%esi), %%ecx\n\t"
      "movb 0xc(%%ecx), %%cl\n\t"
      "movl 0x48(%%ebx), %%eax\n\t"
      "movl $1, %%edx\n\t"
      "shll %%cl, %%edx\n\t"
      "testl %%edx, %%eax\n\t"
      "je .LFUN_00024cf0_13\n\t"
      "movl 0x4c(%%ebx), %%eax\n\t"
      "movl %%eax, -0x18(%%ebp)\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_00024cf0_11\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fcomps 0x254cb8\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .LFUN_00024cf0_12\n\t"
      ".LFUN_00024cf0_11:\n\t"
      "pushl $1\n\t"
      "pushl $0x81\n\t"
      "pushl $0x254c8c\n\t"
      "pushl $0x254c5c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00024cf0_12:\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fadds 0x24(%%esi)\n\t"
      "fstps 0x24(%%esi)\n\t"
      ".LFUN_00024cf0_13:\n\t"
      "movl 0x50(%%ebx), %%ebx\n\t"
      "testl %%ebx, %%ebx\n\t"
      "jle .LFUN_00024cf0_20\n\t"
      "xorl %%edx, %%edx\n\t"
      "testl %%ebx, %%ebx\n\t"
      "movl $0x3f800000, -0x8(%%ebp)\n\t"
      "jle .LFUN_00024cf0_17\n\t"
      "movl -0x14(%%esi), %%ecx\n\t"
      "xorl %%eax, %%eax\n\t"
      ".LFUN_00024cf0_14:\n\t"
      "movl 0xc(%%ebp), %%esi\n\t"
      "shll $4, %%eax\n\t"
      "flds 0x58(%%eax,%%esi,1)\n\t"
      "addl %%esi, %%eax\n\t"
      "fsubs (%%ecx)\n\t"
      "flds 0x5c(%%eax)\n\t"
      "fsubs 0x4(%%ecx)\n\t"
      "flds 0x60(%%eax)\n\t"
      "fsubs 0x8(%%ecx)\n\t"
      "flds 0x54(%%eax)\n\t"
      "fld %%st(1)\n\t"
      ".byte 0xd8, 0xca\n\t"
      "fld %%st(3)\n\t"
      ".byte 0xd8, 0xcc\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fld %%st(4)\n\t"
      ".byte 0xd8, 0xcd\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fld %%st(1)\n\t"
      ".byte 0xd8, 0xca\n\t"
      ".byte 0xde, 0xf9\n\t"
      "fstp %%st(4)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "fcoms -0x8(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00024cf0_15\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "jmp .LFUN_00024cf0_16\n\t"
      ".LFUN_00024cf0_15:\n\t"
      "fstp %%st(0)\n\t"
      ".LFUN_00024cf0_16:\n\t"
      "incl %%edx\n\t"
      "movswl %%dx, %%eax\n\t"
      "cmpl %%ebx, %%eax\n\t"
      "jl .LFUN_00024cf0_14\n\t"
      "movl -0x4(%%ebp), %%esi\n\t"
      ".LFUN_00024cf0_17:\n\t"
      "flds -0x8(%%ebp)\n\t"
      "movl $0x41200000, -0xc(%%ebp)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00024cf0_19\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fsqrt\n\t"
      "fmuls 0x253f34\n\t"
      "fsts -0xc(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_00024cf0_18\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fcomps 0x254cb8\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .LFUN_00024cf0_19\n\t"
      ".LFUN_00024cf0_18:\n\t"
      "pushl $1\n\t"
      "pushl $0x81\n\t"
      "pushl $0x254c8c\n\t"
      "pushl $0x254c5c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00024cf0_19:\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fadds 0x24(%%esi)\n\t"
      "fstps 0x24(%%esi)\n\t"
      ".LFUN_00024cf0_20:\n\t"
      "movl -0x20(%%ebp), %%eax\n\t"
      "addl $0x3c, %%esi\n\t"
      "decl %%eax\n\t"
      "movl %%esi, -0x4(%%ebp)\n\t"
      "movl %%eax, -0x20(%%ebp)\n\t"
      "jne .LFUN_00024cf0_1\n\t"
      ".LFUN_00024cf0_21:\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "movb 0x45(%%ecx), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00024cf0_30\n\t"
      "movl 0x158(%%edi), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_00024cf0_30\n\t"
      "pushl $2\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "leal -0x3c(%%ebp), %%edx\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl 0x158(%%edi), %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c1412f0]\n\t"
      "movw 0x10(%%ebp), %%ax\n\t"
      "addl $0x10, %%esp\n\t"
      "testw %%ax, %%ax\n\t"
      "jle .LFUN_00024cf0_30\n\t"
      "movl 0x14(%%ebp), %%esi\n\t"
      "addl $0x30, %%esi\n\t"
      "movzwl %%ax, %%edi\n\t"
      "jmp .LFUN_00024cf0_22\n\t"
      "leal (%%ebx), %%ebx\n\t"
      ".LFUN_00024cf0_22:\n\t"
      "cmpb $0, (%%esi)\n\t"
      "je .LFUN_00024cf0_29\n\t"
      "movl -0x30(%%esi), %%eax\n\t"
      "flds (%%eax)\n\t"
      "fsubs -0x3c(%%ebp)\n\t"
      "fstps -0x30(%%ebp)\n\t"
      "flds 0x4(%%eax)\n\t"
      "fsubs -0x38(%%ebp)\n\t"
      "fstps -0x2c(%%ebp)\n\t"
      "flds 0x8(%%eax)\n\t"
      "fsubs -0x34(%%ebp)\n\t"
      "fsts -0x28(%%ebp)\n\t"
      "fmuls -0x28(%%ebp)\n\t"
      "flds -0x2c(%%ebp)\n\t"
      "fmuls -0x2c(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds -0x30(%%ebp)\n\t"
      "fmuls -0x30(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fsts -0xc(%%ebp)\n\t"
      "fabs\n\t"
      "fcompl 0x2533d0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .LFUN_00024cf0_29\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fcomps 0x254e00\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00024cf0_29\n\t"
      "flds -0x28(%%ebp)\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "fmuls 0x2c(%%ebx)\n\t"
      "movb 0x46(%%ecx), %%al\n\t"
      "testb %%al, %%al\n\t"
      "flds -0x2c(%%ebp)\n\t"
      "fmuls 0x28(%%ebx)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds -0x30(%%ebp)\n\t"
      "fmuls 0x24(%%ebx)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fsqrt\n\t"
      ".byte 0xde, 0xf9\n\t"
      "fstps 0x10(%%ebp)\n\t"
      "jne .LFUN_00024cf0_23\n\t"
      "flds 0x20(%%ebx)\n\t"
      "flds 0x1c(%%ebx)\n\t"
      "flds 0x18(%%ebx)\n\t"
      "fld %%st(0)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fld %%st(2)\n\t"
      ".byte 0xd8, 0xcb\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fld %%st(3)\n\t"
      ".byte 0xd8, 0xcc\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fcomps 0x254dfc\n\t"
      "fstp %%st(0)\n\t"
      "fnstsw %%ax\n\t"
      "fstp %%st(0)\n\t"
      "testb $0x41, %%ah\n\t"
      "fstp %%st(0)\n\t"
      "jne .LFUN_00024cf0_24\n\t"
      ".LFUN_00024cf0_23:\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fcomps 0x254df8\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00024cf0_24\n\t"
      "flds 0x10(%%ebp)\n\t"
      "fcomps 0x254b50\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00024cf0_24\n\t"
      "movb $1, 0x1(%%esi)\n\t"
      "movb 0x14(%%ecx), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00024cf0_24\n\t"
      "movb $0, (%%esi)\n\t"
      "jmp .LFUN_00024cf0_29\n\t"
      ".LFUN_00024cf0_24:\n\t"
      "flds 0x10(%%ebp)\n\t"
      "movl $0x41700000, 0x14(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "flds 0x10(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00024cf0_25\n\t"
      "fmuls 0x254df4\n\t"
      "fsubrs 0x254cc0\n\t"
      "jmp .LFUN_00024cf0_26\n\t"
      ".LFUN_00024cf0_25:\n\t"
      "fcomps 0x2533dc\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00024cf0_28\n\t"
      "flds 0x10(%%ebp)\n\t"
      "fsubs 0x2533dc\n\t"
      "fmuls 0x254df0\n\t"
      "fadds 0x254cc0\n\t"
      ".LFUN_00024cf0_26:\n\t"
      "fstps 0x14(%%ebp)\n\t"
      "flds 0x14(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_00024cf0_27\n\t"
      "flds 0x14(%%ebp)\n\t"
      "fcomps 0x254cb8\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .LFUN_00024cf0_28\n\t"
      ".LFUN_00024cf0_27:\n\t"
      "pushl $1\n\t"
      "pushl $0x81\n\t"
      "pushl $0x254c8c\n\t"
      "pushl $0x254c5c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00024cf0_28:\n\t"
      "flds 0x14(%%ebp)\n\t"
      "fadds 0x8(%%esi)\n\t"
      "fstps 0x8(%%esi)\n\t"
      ".LFUN_00024cf0_29:\n\t"
      "addl $0x3c, %%esi\n\t"
      "decl %%edi\n\t"
      "jne .LFUN_00024cf0_22\n\t"
      ".LFUN_00024cf0_30:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [dget] "m"(b24cf0_dget), [c24ca0] "m"(b24cf0_c24ca0), [assert] "m"(b24cf0_assert), [exitfn] "m"(b24cf0_exitfn), [c10cd40] "m"(b24cf0_c10cd40), [c24000] "m"(b24cf0_c24000), [c10ce10] "m"(b24cf0_c10ce10), [get] "m"(b24cf0_get), [c1412f0] "m"(b24cf0_c1412f0)
      : "memory");
}
#else
#error "FUN_00024cf0: clang naked draft required"
#endif


/* FUN_00025340 (0x25340) — Firing-position ideal-range scorer.
 *
 * Iterates over a firing-position array and scores each active position
 * based on its range relative to the context's ideal range. If the
 * context has a target, also applies weapon-optimal-range and
 * facing-alignment bonuses.
 *
 * Confirmed: cdecl, 4 stack args.
 * Confirmed: loop at 0x25340+0xd, count >= 0 check.
 * Confirmed: display_assert guards on eval thresholds. */
void FUN_00025340(int actor_handle, void *ctx, unsigned short count,
                  void *positions)
{
  char *pos;
  float eval;
  float range;
  unsigned int n;

  if (0 >= (short)count)
    return;

  n = (unsigned int)count;
  pos = (char *)positions + 8;
  do {
    if (*(char *)(pos + 10) != '\0') {
      eval = 0.0f;
      range = *(float *)((char *)ctx + 0x18) * 0.5f;
      if (range <= *(float *)pos) {
        if (*(float *)pos < *(float *)((char *)ctx + 0x18)) {
          eval = (2.0f / range) *
                 (*(float *)((char *)ctx + 0x18) - *(float *)pos) * 10.0f;
          if (eval < 0.0f || eval >= 1000.0f) {
            display_assert("(evaluation >= 0.0f) && (evaluation < 1e+03f)",
                           "c:\\halo\\SOURCE\\ai\\actor_firing_position.c",
                           0x81, 1);
            system_exit(-1);
          }
        }
      } else {
        eval = 5.0f;
      }
      *(float *)(pos + 0xc) = eval + *(float *)(pos + 0xc);

      if (*(char *)((char *)ctx + 0x5fc) != '\0') {
        if (*(float *)(pos + 0x10) < *(float *)0x254cd0) {
          range = (*(float *)0x254cd0 - *(float *)(pos + 0x10)) * 0.5f;
          if (range < 0.0f || range >= 1000.0f) {
            display_assert("(evaluation >= 0.0f) && (evaluation < 1e+03f)",
                           "c:\\halo\\SOURCE\\ai\\actor_firing_position.c",
                           0x81, 1);
            system_exit(-1);
          }
          *(float *)(pos + 0xc) = range + *(float *)(pos + 0xc);
        }
        if (*(char *)((char *)ctx + 0x43) != '\0' &&
            *(char *)((char *)ctx + 0x648) != '\0') {
          float dot;
          float score;
          dot = *(float *)(pos + 0x18) * *(float *)((char *)ctx + 0x64c) +
                *(float *)((char *)ctx + 0x650) * *(float *)(pos + 0x1c) +
                *(float *)(pos + 0x20) * *(float *)((char *)ctx + 0x654);
          if (dot <= 0.0f) {
            score = dot * (-1.0f);
            if (score < 0.0f)
              score = 0.0f;
            score = score * 10.0f;
          } else {
            score = 10.0f;
          }
          /* @<esi> = position element base (original 0x254ed LEA ESI,[EDI-8]);
           * 24000 accumulates score into [esi+0x38] = pos+0x30. */
          FUN_00024000(NULL, score, 3, pos - 8, ctx);
        }
      }
    }
    pos = pos + 0x3c;
    n = n - 1;
  } while (n != 0);
}

/* FUN_00025510 (0x25510) — Firing-position occlusion/long-range scorer.
 *
 * Iterates firing positions and scores each by its distance from the
 * context's desired range. Penalizes positions out of range
 * (too close to ideal, or ambiguous dot-product), and awards
 * 'in-view' bonuses. Clamps evaluations via display_assert guards.
 *
 * Confirmed: cdecl, 4 stack args.
 * Confirmed: loop structure at 0x25510, position stride 0x3c.
 * Confirmed: display_assert guards on evaluation. */
void FUN_00025510(int actor_handle, void *ctx, unsigned short count,
                  void *positions)
{
  char *pos;
  float eval;
  unsigned int n;

  if (0 >= (short)count)
    return;

  n = (unsigned int)count;
  pos = (char *)positions + 8;
  do {
    if (*(char *)(pos + 0x28) != '\0') {
      if (*(float *)0x2533d8 <= *(float *)pos) {
        eval = 0.0f;
        if (*(float *)0x253f78 <= *(float *)pos) {
          if (*(float *)pos < *(float *)((char *)ctx + 0x18)) {
            eval = ((*(float *)((char *)ctx + 0x18) - *(float *)pos) *
                    *(float *)0x253f78) /
                   (*(float *)((char *)ctx + 0x18) - *(float *)0x253f78);
            goto LAB_eval_guard;
          }
        } else {
          eval = *(float *)pos - *(float *)0x2533d8;
          eval = eval + eval;
        LAB_eval_guard:
          if (eval < 0.0f || eval >= 1000.0f) {
            display_assert("(evaluation >= 0.0f) && (evaluation < 1e+03f)",
                           "c:\\halo\\SOURCE\\ai\\actor_firing_position.c",
                           0x81, 1);
            system_exit(-1);
          }
        }
        *(float *)(pos + 0x30) = eval + *(float *)(pos + 0x30);
      } else {
        pos[0x29] = 1;
        if (*(char *)((char *)ctx + 0x14) == '\0') {
          *(char *)(pos + 0x28) = 0;
          goto LAB_next;
        }
      }
      if (*(char *)((char *)ctx + 0x5fc) != '\0') {
        if (*(float *)0x254e74 <= *(float *)(pos + 0x24) ||
            (*(char *)(pos + 0x29) = 1,
             *(char *)((char *)ctx + 0x14) != '\0')) {
          eval = 0.0f;
          if (*(float *)0x254e74 <= *(float *)(pos + 0x24) &&
              (eval = *(float *)0x253f34,
               *(float *)(pos + 0x24) < *(float *)0x254e70 &&
                 (eval =
                    (xbox_sqrtf(*(float *)(pos + 0x24)) - *(float *)0x2533d8) *
                    *(float *)0x254e6c,
                  (eval < 0.0f || eval >= 1000.0f)))) {
            display_assert("(evaluation >= 0.0f) && (evaluation < 1e+03f)",
                           "c:\\halo\\SOURCE\\ai\\actor_firing_position.c",
                           0x81, 1);
            system_exit(-1);
          }
          *(float *)(pos + 0x30) = eval + *(float *)(pos + 0x30);
          if ((*(float *)(pos + 0x14) < *(float *)0x2548fc &&
               0.0f < *(float *)((char *)ctx + 0x600) &&
               *(float *)((char *)ctx + 0x600) < *(float *)0x2548fc)) {
            eval = *(float *)0x2533c8 -
                   *(float *)(pos + 0x14) /
                     (*(float *)((char *)ctx + 0x600) * *(float *)0x2533f0);
            if (eval <= 0.5f ||
                !(pos[0x29] = 1, *(char *)((char *)ctx + 0x14) == '\0')) {
              float bonus;
              bonus = 0.0f;
              if (0.0f <= eval) {
                bonus = eval;
                if (*(float *)0x2533c8 < eval)
                  bonus = *(float *)0x2533c8;
              }
              /* @<esi> = position element base (original 0x2576b). */
              FUN_00024000(NULL, (*(float *)0x2533c8 - bonus) * *(float *)0x253f78,
                           10, pos - 8, ctx);
            } else {
              *(char *)(pos + 0x28) = 0;
            }
          }
        } else {
          *(char *)(pos + 0x28) = 0;
        }
      }
    }
  LAB_next:
    pos = pos + 0x3c;
    n = n - 1;
  } while (n != 0);
}

/* FUN_000257a0 (0x257a0) — Firing-position evaluation per-position updater.
 *
 * Evaluates aim/LoS targeting for a single firing position within the
 * actor's firing-position evaluation. Two branches:
 *   1. mode==5 (burst check): checks state[+8] against a threshold,
 *      applies a short-duration offset-radius, and tests LOS.
 *   2. Other modes: determines type/position/facing args, estimates
 *      unit position, and tests LOS with varying parameters.
 *
 * Register args: @eax=actor_handle, @edi=state, @ecx=actor.
 * Calls datum_get, unit_estimate_position, ai_test_line_of_sight,
 * magnitude3d, display_assert, system_exit.
 *
 * Confirmed: PUSH at 0x257b0/0x257b1 → datum_get(actor_data, actor_handle).
 * Confirmed: CMP word [ESI+4],5 / JNZ at 0x257ea/0x257ee.
 * Confirmed: FCOMP [0x254640] / FNSTSW / TEST at 0x257f3/0x257fb.
 * Confirmed: 2x CALL 001a93e0 (unit_estimate_position) and 2x CALL 000416e0
 *   (ai_test_line_of_sight).
 * Confirmed: MOV word [EDI+6],AX at 0x2584d/0x25857/0x2595e. */
void FUN_000257a0(int actor_handle, void *state, char *actor)
{
  char *d;
  short mode;
  float diff[3];
  float len_sq;
  float *position_ptr;
  void *direction_ptr;
  int type;
  int flag;
  short los_result;
  void *state_pos;
  float offset_radius[3];
  float offset_radius2[3];

  position_ptr = NULL;
  direction_ptr = NULL;

  d = (char *)datum_get(actor_data, actor_handle);

  if (*(char *)(actor + 0x5fc) == '\0') {
    display_assert("has_target",
                   "c:\\halo\\SOURCE\\ai\\actor_firing_position.c", 0x33c, 1);
    system_exit(-1);
  }

  mode = *(short *)(actor + 4);

  if (mode == 5) {
    state_pos = *(void **)state;
    if (*(float *)((char *)state + 8) < *(float *)0x254640) {
      unit_estimate_position(*(int *)(d + 0x18), 1, (vector3_t *)state_pos,
                             NULL, NULL, (vector3_t *)offset_radius);
      los_result = (short)ai_test_line_of_sight(
        (float *)(d + 0x120), (int)*(uint16_t *)(d + 0x148), offset_radius,
        (int)*(uint16_t *)((char *)state_pos + 0xe), 0, 0, -1,
        (char)(*(int *)(d + 0x158) != -1));
      *(short *)((char *)state + 6) = los_result;
      return;
    }
    *(short *)((char *)state + 6) = 4;
    return;
  }

  flag = 0;
  direction_ptr = NULL;

  if (mode == 1 || mode == 2) {
    type = 2;
  } else if (*(char *)(actor + 0x5dc) != '\0') {
    state_pos = *(void **)state;
    diff[0] = *(float *)(actor + 0x610) - *(float *)state_pos;
    diff[1] = *(float *)(actor + 0x614) - *(float *)((char *)state_pos + 4);
    diff[2] = *(float *)(actor + 0x618) - *(float *)((char *)state_pos + 8);
    type = 3;
    direction_ptr = (void *)(actor + 0x5e0);
    len_sq = magnitude3d(diff);
    if (len_sq <= *(float *)0x2533c0) {
      position_ptr = (float *)(d + 0x174);
    } else {
      diff[2] = 0.0f;
      position_ptr = diff;
    }
  } else {
    type = 1;
    position_ptr = NULL;
  }

  state_pos = *(void **)state;
  unit_estimate_position(*(int *)(d + 0x18), type, (vector3_t *)state_pos,
                         (vector3_t *)position_ptr, (vector3_t *)direction_ptr,
                         (vector3_t *)offset_radius2);

  if (mode >= 1 && mode <= 3)
    flag = 1;

  los_result = (short)ai_test_line_of_sight(
    offset_radius2, (int)*(uint16_t *)((char *)state_pos + 0xe),
    (float *)(actor + 0x61c), (int)*(uint16_t *)(actor + 0x640), flag, 1,
    *(int *)(actor + 0x62c), (char)(*(int *)(d + 0x158) != -1));

  *(short *)((char *)state + 6) = los_result;
}

/* FUN_00025970 (0x25970) — Firing-position evaluation state updater.
 * Advances the per-position evaluation state machine.
 *
 * Confirmed: EAX=state_ptr@<eax>, ESI=actor_ptr@<esi>, EBP+8=actor_handle.
 *   (actor was wrongly a stack param before 2026-06-10 — original callers
 *   at 0x26d2f/0x2728f push only the handle; the rvthunk fed garbage.)
 *   Calls FUN_00024850, FUN_000257a0, FUN_00024890.
 * Confirmed: FUN_00024850 takes actor@<edi> + state@<ebx> pass-throughs —
 *   original 0x25988 MOV EDI,ESI and 0x25974 MOV EBX,EAX before the call;
 *   24850/24890 gate hook tables (0x254bf8/0x254c30) on 1<<[actor+4]
 *   (actor type index) and forward (handle, actor, state) to each hook.
 * Confirmed: state+0x30/0x31/0x34/0x38 accessed; actor+0x668/0x66a/0x66c
 *   debug counters. */
char FUN_00025970(void *state, int actor_handle, char *actor)
{
  char result;

  *(int *)((char *)state + 0x38) = 0;
  *(int *)((char *)state + 0x34) = 0;
  *(char *)((char *)state + 0x31) = 0;
  *(char *)((char *)state + 0x30) = 1;

  FUN_00024850(actor_handle, 1, actor, state);

  if (*(char *)((char *)state + 0x30) != 0)
    *(short *)(actor + 0x668) = *(short *)(actor + 0x668) + 1;

  if (*(char *)((char *)state + 0x31) == 0)
    *(short *)(actor + 0x66a) = *(short *)(actor + 0x66a) + 1;

  if (*(char *)((char *)state + 0x30) != 0) {
    if (*(char *)(actor + 0x5fc) != 0)
      FUN_000257a0(actor_handle, state, actor);
    *(int *)((char *)state + 0x34) = *(int *)((char *)state + 0x38);
    result = FUN_00024890(actor_handle, state, actor);
    *(char *)((char *)state + 0x30) = result;
    *(short *)(actor + 0x66c) = *(short *)(actor + 0x66c) + 1;
  }

  return *(char *)((char *)state + 0x30);
}

/* actor_has_accessible_firing_position (0x25a00) — actor_has_accessible_firing_position
 * Tests whether the given position is an accessible firing position for the
 * actor.  Checks that the position belongs to the actor's encounter's firing-
 * position list, is within range, and (for non-swarm actors) is reachable via
 * a path-state ray cast.
 *
 * Confirmed: param_1=actor_handle, param_2=position (float *),
 *   param_3=surface_index (-1 = none), param_4=group_mask (bitfield).
 * Confirmed: actor+0x99 = is_swarm flag; actor+0x34 = encounter handle;
 *   actor+0x3a = firing_position_index (short); actor+0x58 = tag_index.
 * Confirmed: actor_get_firing_position_group = actor_get_firing_position_group (3 args).
 * Confirmed: path_state_estimated_distance = path_state_estimated_distance (6 args cdecl,
 *   ADD ESP,0x18 at 0x25bb6/all sites; output via arg4 float*, args 5/6 are
 *   optional out-pointers — this site shares two PUSH 0 with the 0x5e830
 *   branch, so it passes NULL/NULL); NOT an ESI-output function — unaff_ESI
 *   in Ghidra is an artifact of inlining; result is at [EBP-0x8] after the
 *   call.  arg3 is a raw int load (MOV ECX,[EDX+0x14]), not a float-to-int
 *   conversion.
 * Confirmed: threshold at 0x2533d8 = 4.0f; dist_sq threshold at 0x254e74 =
 *   16.0f.
 * Confirmed: huge path-state buffer at EBP-0x140e0 (82080 bytes); ray-init
 *   struct at EBP-0x54 (84 bytes).
 * Source file string: c:\halo\SOURCE\ai\actor_firing_position.c */
char actor_has_accessible_firing_position(int actor_handle, float *position,
                                          int surface_index, int group_mask)
{
  /* C89: all declarations at top */
  char *actor;
  char *tag;
  void *bsp;
  char *encounter_elem;
  unsigned int mask;
  char *fp_block;
  float *fp_elem;
  float dx;
  float dy;
  float dz;
  float dist_sq;
  float hit_dist;
  int i;
  int fp_count;
  char vis;
  unsigned char huge_buf[0x140e0];
  unsigned char ray_init[0x54];

  actor = (char *)datum_get(actor_data, actor_handle);
  tag = (char *)tag_get(0x61637472, *(int *)(actor + 0x58));

  if (*(char *)(actor + 0x99) == 0) {
    /* not a swarm: validate surface_index */
    if (surface_index != -1) {
      bsp = global_collision_bsp_get();
      if (surface_index < 0 || surface_index >= *(int *)((char *)bsp + 0x3c)) {
        display_assert("(test_surface_index >= 0) && (test_surface_index < "
                       "collision_bsp->surfaces.count)",
                       "c:\\halo\\SOURCE\\ai\\actor_firing_position.c", 0x59a,
                       1);
        system_exit(-1);
      }
    }
    if (*(char *)(actor + 0x99) == 0 && surface_index == -1) {
      return 0;
    }
  }

  if (*(int *)(actor + 0x34) == -1) {
    return 0;
  }

  /* actor has an encounter — get firing-position group mask */
  encounter_elem = (char *)tag_block_get_element(
    (char *)global_scenario_get() + 0x42c,
    *(unsigned int *)(actor + 0x34) & 0xffff, 0xb0);
  mask =
    (unsigned int)actor_get_firing_position_group(actor_handle, 0, group_mask);

  /* for non-swarm: set up path-state ray */
  if (*(char *)(actor + 0x99) == 0) {
    path_input_new((void *)ray_init, *(unsigned int *)((char *)tag + 0x8c), 1,
                   -1);
    path_input_set_start((void *)ray_init, position, surface_index);
    path_input_set_search_bounds((void *)ray_init, 0x40800000);
    path_state_new((void *)ray_init, (void *)huge_buf, (void *)0);
    FUN_0005ff70((unsigned int *)huge_buf);
  }

  /* iterate over encounter's firing positions */
  fp_block = encounter_elem + 0x98;
  fp_count = *(int *)(encounter_elem + 0x98);
  i = 0;
  if (fp_count <= 0) {
    return 0;
  }
  do {
    fp_elem = (float *)tag_block_get_element((void *)fp_block, i, 0x18);

    /* check group bit */
    if (mask & (1u << (*(unsigned char *)((char *)fp_elem + 0xc) & 0x1f))) {
      /* check squared distance */
      dx = fp_elem[0] - position[0];
      dy = fp_elem[1] - position[1];
      dz = fp_elem[2] - position[2];
      dist_sq = dx * dx + dy * dy + dz * dz;

      if (dist_sq < 16.0f) {
        if (*(char *)(actor + 0x99) == 0) {
          /* non-swarm: ray-cast check */
          hit_dist = 0.0f;
          path_state_estimated_distance((void *)huge_buf, (void *)fp_elem,
                                        *(int *)(fp_elem + 5), &hit_dist,
                                        (float *)0, (float *)0);
          if (hit_dist < 4.0f) {
            return 1;
          }
        } else {
          /* swarm: simple 3D visibility check */
          vis =
            path_3d_available((int)scenario_get(), (int *)position, 0,
                              (int *)fp_elem, (unsigned char *)0, (float *)0);
          if (vis != 0) {
            return 1;
          }
        }
      }
    }

    i++;
  } while (i < fp_count);

  return 0;
}

/* FUN_00025c10 (0x25c10) — XBE naked draft (batch 75). */
#if defined(__clang__)
static void (*const b25c10_chkstk)(void) = FUN_001d90e0;
static void *(*const b25c10_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void *(*const b25c10_tag)(int, int) = tag_get;
static scenario_t * (*const b25c10_c18e380)(void) = global_scenario_get;
static void *(*const b25c10_elem)(void *, int, int) = tag_block_get_element;
static void (*const b25c10_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b25c10_exitfn)(int) = system_exit;
static void (*const b25c10_c5b4b0)(int encounter_handle, int *firing_position_owner_actor_indices) = encounter_build_firing_position_owner_actor_indices;
static void (*const b25c10_c1a93e0)(int unit_handle, int16_t estimate_mode, vector3_t *body_position, vector3_t *desired_facing, vector3_t *desired_gun_offset, vector3_t *out_position) = unit_estimate_position;
static void (*const b25c10_c2f910)(int actor_handle, int prop_handle) = actor_perception_find_prop_pathfinding_location;
static void (*const b25c10_c64540)(int *out, int actor_handle) = FUN_00064540;
static int (*const b25c10_c64570)(int *iter) = FUN_00064570;
static char (*const b25c10_c309d0)(int actor_handle, int iter_handle, float *out_pos) = actor_perception_friend_prop_is_attacking;
static void (*const b25c10_c1a9900)(int unit_handle, void *out_aiming) = unit_scripting_unit_driver;
static char (*const b25c10_c25a00)(int actor_handle, float *position, int surface_index, int group_mask) = actor_has_accessible_firing_position;
static void (*const b25c10_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;
static void * (*const b25c10_c18e3c0)(void) = (void *(*)(void))global_scenario_get;
static char (*const b25c10_c5e830)(int param_1, int *param_2, int param_3, int *param_4, unsigned char *param_5, float *param_6) = path_3d_available;
static float (*const b25c10_norm)(float *) = normalize3d;
static void (*const b25c10_c5dfc0)(void *param_1, unsigned int param_2, unsigned char param_3, int param_4) = path_input_new;
static void (*const b25c10_c5e000)(void *param_1, float *param_2, int param_3) = path_input_set_start;
static void (*const b25c10_c5e070)(void *param_1, int param_2) = path_input_set_search_bounds;
static void (*const b25c10_c5e090)(void *param_1, void *param_2, void *param_3) = path_state_new;
static char (*const b25c10_c5ff70)(unsigned int *path_buf) = FUN_0005ff70;
static char (*const b25c10_c5f550)(void *path_state, void *fp_element, int surface_index, float *result, float *opt_min_clearance, float *opt_out_vec) = path_state_estimated_distance;
static void (*const b25c10_c2a470)(int actor_handle, char *nav_state_out) = actor_path_input_new;
static void (*const b25c10_c5e030)(void *param_1, float *param_2, float param_3, unsigned int param_4, float param_5) = path_input_set_attractor;
static void * (*const b25c10_c49120)(int actor_handle) = ai_debug_get_path_storage;
static float (*const b25c10_c10cd40)(float *p1, float *p2, float *p3) = FUN_0010cd40;
static int *(*const b25c10_gseed)(void) = get_global_random_seed_address;
static int16_t (*const b25c10_c10b2d0)(unsigned int *seed, int16_t min, int16_t max) = random_range;
static char (*const b25c10_c25970)(void *state, int actor_handle, char *actor) = FUN_00025970;
static void (*const b25c10_c91ef0)(int *keys, int count, int (*cmp)(int, int)) = (void *)FUN_00091ef0;
static char (*const b25c10_c24900)(int actor_handle, void *query_buf) = FUN_00024900;
static short (*const b25c10_cfff80)(void) = game_connection;
static void (*const b25c10_c257a0)(int actor_handle, void *state, char *actor) = FUN_000257a0;
static char (*const b25c10_c24890)(int actor_handle, void *state, char *actor) = FUN_00024890;

__attribute__((naked, noinline))
short FUN_00025c10(int actor_handle __attribute__((unused)), void *eval_ctx __attribute__((unused)), int *out_record __attribute__((unused)), int *out_owner __attribute__((unused)), void *huge_buf __attribute__((unused)), int *out_found __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl $0x1c91c, %%eax\n\t"
      "call *%[chkstk]\n\t"
      "movl 0x6325a4, %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl 0x5ac9f4, %%edx\n\t"
      "movl 0xc(%%ebp), %%ebx\n\t"
      "movl %%eax, %%edi\n\t"
      "movl 0x34(%%edi), %%ecx\n\t"
      "orl $0xffffffff, %%eax\n\t"
      "addl $8, %%esp\n\t"
      "cmpl %%edx, %%ecx\n\t"
      "movl %%edi, -0x2c(%%ebp)\n\t"
      "movl %%eax, -0x30(%%ebp)\n\t"
      "movl $0, -0x24(%%ebp)\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "jne .LFUN_00025c10_3\n\t"
      "movl 0x5ac9f8, %%edx\n\t"
      "cmpl $-1, %%edx\n\t"
      "je .LFUN_00025c10_1\n\t"
      "cmpl %%esi, %%edx\n\t"
      "jne .LFUN_00025c10_3\n\t"
      ".LFUN_00025c10_1:\n\t"
      "movb 0x5aca83, %%dl\n\t"
      "testb %%dl, %%dl\n\t"
      "je .LFUN_00025c10_2\n\t"
      "cmpw $5, 0x4(%%ebx)\n\t"
      "je .LFUN_00025c10_2\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      ".LFUN_00025c10_2:\n\t"
      "movb 0x5aca84, %%dl\n\t"
      "testb %%dl, %%dl\n\t"
      "je .LFUN_00025c10_3\n\t"
      "cmpw $5, 0x4(%%ebx)\n\t"
      "jne .LFUN_00025c10_3\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      ".LFUN_00025c10_3:\n\t"
      "cmpl $-1, %%ecx\n\t"
      "je .LFUN_00025c10_62\n\t"
      "movl 0x58(%%edi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x61637472\n\t"
      "call *%[tag]\n\t"
      "movl 0x5c(%%edi), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl %%eax, %%esi\n\t"
      "pushl $0x61637476\n\t"
      "movl %%esi, -0x28(%%ebp)\n\t"
      "call *%[tag]\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "movl 0x34(%%edi), %%eax\n\t"
      "addl $0x10, %%esp\n\t"
      "andl $0xffff, %%eax\n\t"
      "pushl $0xb0\n\t"
      "pushl %%eax\n\t"
      "call *%[c18e380]\n\t"
      "addl $0x42c, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "movb 0x160(%%edi), %%al\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "movl $0, -0x8(%%ebp)\n\t"
      "movb $0, -0x2(%%ebp)\n\t"
      "je .LFUN_00025c10_4\n\t"
      "pushl $1\n\t"
      "pushl $0x610\n\t"
      "pushl $0x254c8c\n\t"
      "pushl $0x254fe8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00025c10_4:\n\t"
      "incw 0x5ac904\n\t"
      "movl 0x34(%%edi), %%edx\n\t"
      "leal -0x890(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c5b4b0]\n\t"
      "movw 0x3b8(%%edi), %%ax\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .LFUN_00025c10_5\n\t"
      "movswl %%ax, %%eax\n\t"
      "movl $0xffffffff, -0x890(%%ebp,%%eax,4)\n\t"
      ".LFUN_00025c10_5:\n\t"
      "cmpw $0, 0x15e(%%edi)\n\t"
      "jne .LFUN_00025c10_6\n\t"
      "flds 0x254cc0\n\t"
      "jmp .LFUN_00025c10_7\n\t"
      ".LFUN_00025c10_6:\n\t"
      "flds 0x254fe4\n\t"
      ".LFUN_00025c10_7:\n\t"
      "fsts 0x18(%%ebx)\n\t"
      "flds 0x1c(%%ebx)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .LFUN_00025c10_8\n\t"
      "fstps 0x1c(%%ebx)\n\t"
      "jmp .LFUN_00025c10_9\n\t"
      ".LFUN_00025c10_8:\n\t"
      "fstp %%st(0)\n\t"
      ".LFUN_00025c10_9:\n\t"
      "cmpw $5, 0x4(%%ebx)\n\t"
      "movb 0x20(%%ebx), %%al\n\t"
      "sete %%cl\n\t"
      "testb %%al, %%al\n\t"
      "movb %%cl, 0x42(%%ebx)\n\t"
      "movb $0, 0x5fc(%%ebx)\n\t"
      "je .LFUN_00025c10_10\n\t"
      "leal 0x24(%%ebx), %%ecx\n\t"
      "leal 0x604(%%ebx), %%eax\n\t"
      "movl %%ecx, %%edx\n\t"
      "movl (%%edx), %%edi\n\t"
      "movl %%eax, %%esi\n\t"
      "movl %%edi, (%%esi)\n\t"
      "movl 0x4(%%edx), %%edi\n\t"
      "movl 0x8(%%edx), %%edx\n\t"
      "movl %%edi, 0x4(%%esi)\n\t"
      "movl -0x2c(%%ebp), %%edi\n\t"
      "movl %%edx, 0x8(%%esi)\n\t"
      "movl (%%ecx), %%esi\n\t"
      "leal 0x634(%%ebx), %%edx\n\t"
      "movl %%esi, (%%edx)\n\t"
      "movl 0x4(%%ecx), %%esi\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "movl %%esi, 0x4(%%edx)\n\t"
      "movl %%ecx, 0x8(%%edx)\n\t"
      "movl 0x30(%%ebx), %%edx\n\t"
      "movw 0x34(%%ebx), %%cx\n\t"
      "movw %%cx, 0x640(%%ebx)\n\t"
      "movb $1, 0x5fc(%%ebx)\n\t"
      "movl %%edx, 0x630(%%ebx)\n\t"
      "flds (%%eax)\n\t"
      "fsubs 0x12c(%%edi)\n\t"
      "leal 0x610(%%ebx), %%esi\n\t"
      "flds 0x4(%%eax)\n\t"
      "pushl %%esi\n\t"
      "fsubs 0x130(%%edi)\n\t"
      "pushl $0\n\t"
      "flds 0x8(%%eax)\n\t"
      "pushl $0\n\t"
      "fsubs 0x134(%%edi)\n\t"
      "orl $0xffffffff, %%ecx\n\t"
      "pushl %%eax\n\t"
      "movl %%ecx, 0x644(%%ebx)\n\t"
      "fld %%st(2)\n\t"
      "movl %%ecx, 0x62c(%%ebx)\n\t"
      ".byte 0xd8, 0xcb\n\t"
      "movl $0, 0x658(%%ebx)\n\t"
      "fld %%st(2)\n\t"
      "pushl $1\n\t"
      ".byte 0xd8, 0xcb\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fld %%st(1)\n\t"
      ".byte 0xd8, 0xca\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fsqrt\n\t"
      "fstps 0x600(%%ebx)\n\t"
      "movl 0x18(%%edi), %%edx\n\t"
      "pushl %%edx\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "call *%[c1a93e0]\n\t"
      "movl (%%esi), %%ecx\n\t"
      "movl 0x4(%%esi), %%edx\n\t"
      "leal 0x61c(%%ebx), %%eax\n\t"
      "movl %%ecx, (%%eax)\n\t"
      "movl 0x8(%%esi), %%ecx\n\t"
      "movl %%edx, 0x4(%%eax)\n\t"
      "addl $0x18, %%esp\n\t"
      "movl %%ecx, 0x8(%%eax)\n\t"
      "jmp .LFUN_00025c10_19\n\t"
      ".LFUN_00025c10_10:\n\t"
      "cmpw $4, 0x6c(%%edi)\n\t"
      "jne .LFUN_00025c10_11\n\t"
      "movl 0xb8(%%edi), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "jne .LFUN_00025c10_12\n\t"
      ".LFUN_00025c10_11:\n\t"
      "movl 0x270(%%edi), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_00025c10_20\n\t"
      ".LFUN_00025c10_12:\n\t"
      "cmpl $-1, %%eax\n\t"
      "movl %%eax, -0x20(%%ebp)\n\t"
      "je .LFUN_00025c10_20\n\t"
      "movl %%eax, %%edx\n\t"
      "movl 0x5ab23c, %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%esi\n\t"
      "movb 0x42(%%ebx), %%al\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00025c10_13\n\t"
      "movw 0x24(%%esi), %%ax\n\t"
      "cmpw $2, %%ax\n\t"
      "jl .LFUN_00025c10_13\n\t"
      "cmpw $3, %%ax\n\t"
      "jg .LFUN_00025c10_13\n\t"
      "movl -0x20(%%ebp), %%ecx\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c2f910]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_00025c10_13:\n\t"
      "movb $1, 0x5fc(%%ebx)\n\t"
      "leal 0xbc(%%esi), %%eax\n\t"
      "movl (%%eax), %%edx\n\t"
      "leal 0x604(%%ebx), %%ecx\n\t"
      "movl %%edx, (%%ecx)\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl %%edx, 0x4(%%ecx)\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl %%eax, 0x8(%%ecx)\n\t"
      "leal 0xf0(%%esi), %%ecx\n\t"
      "movl (%%ecx), %%eax\n\t"
      "leal 0x634(%%ebx), %%edx\n\t"
      "movl %%eax, (%%edx)\n\t"
      "movl 0x4(%%ecx), %%eax\n\t"
      "movl %%eax, 0x4(%%edx)\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "movl %%ecx, 0x8(%%edx)\n\t"
      "movl 0xec(%%esi), %%edx\n\t"
      "movl %%edx, 0x630(%%ebx)\n\t"
      "movw 0x100(%%esi), %%ax\n\t"
      "movl -0x20(%%ebp), %%edx\n\t"
      "movw %%ax, 0x640(%%ebx)\n\t"
      "movl 0x11c(%%esi), %%ecx\n\t"
      "movl %%ecx, 0x600(%%ebx)\n\t"
      "movl %%edx, 0x644(%%ebx)\n\t"
      "leal 0x104(%%esi), %%eax\n\t"
      "movl (%%eax), %%edx\n\t"
      "leal 0x610(%%ebx), %%ecx\n\t"
      "movl %%edx, (%%ecx)\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl %%edx, 0x4(%%ecx)\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl %%eax, 0x8(%%ecx)\n\t"
      "movl 0x110(%%esi), %%ecx\n\t"
      "movb 0x41(%%ebx), %%al\n\t"
      "testb %%al, %%al\n\t"
      "movl %%ecx, 0x62c(%%ebx)\n\t"
      "movl 0x20(%%esi), %%edx\n\t"
      "movl %%edx, 0x658(%%ebx)\n\t"
      "je .LFUN_00025c10_14\n\t"
      "cmpl $-1, 0x8c(%%esi)\n\t"
      "je .LFUN_00025c10_14\n\t"
      "leal 0x90(%%esi), %%eax\n\t"
      "movl (%%eax), %%edx\n\t"
      "leal 0x61c(%%ebx), %%ecx\n\t"
      "movl %%edx, (%%ecx)\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl %%edx, 0x4(%%ecx)\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl %%eax, 0x8(%%ecx)\n\t"
      "jmp .LFUN_00025c10_15\n\t"
      ".LFUN_00025c10_14:\n\t"
      "movl 0x104(%%esi), %%edx\n\t"
      "leal 0x61c(%%ebx), %%ecx\n\t"
      "movl %%edx, (%%ecx)\n\t"
      "movl 0x108(%%esi), %%eax\n\t"
      "movl %%eax, 0x4(%%ecx)\n\t"
      "movl 0x10c(%%esi), %%edx\n\t"
      "movl %%edx, 0x8(%%ecx)\n\t"
      ".LFUN_00025c10_15:\n\t"
      "movw 0x24(%%esi), %%ax\n\t"
      "cmpw $4, %%ax\n\t"
      "jl .LFUN_00025c10_16\n\t"
      "cmpw $5, %%ax\n\t"
      "jg .LFUN_00025c10_16\n\t"
      "movb $1, 0x648(%%ebx)\n\t"
      "addl $0x40, %%esi\n\t"
      "movl (%%esi), %%ecx\n\t"
      "leal 0x64c(%%ebx), %%eax\n\t"
      "movl %%ecx, (%%eax)\n\t"
      "movl 0x4(%%esi), %%edx\n\t"
      "movl %%edx, 0x4(%%eax)\n\t"
      "movl 0x8(%%esi), %%ecx\n\t"
      "movl %%ecx, 0x8(%%eax)\n\t"
      ".LFUN_00025c10_16:\n\t"
      "movw 0x4(%%ebx), %%ax\n\t"
      "cmpw $4, %%ax\n\t"
      "je .LFUN_00025c10_17\n\t"
      "cmpw $6, %%ax\n\t"
      "je .LFUN_00025c10_17\n\t"
      "xorl %%eax, %%eax\n\t"
      "jmp .LFUN_00025c10_18\n\t"
      ".LFUN_00025c10_17:\n\t"
      "movl $1, %%eax\n\t"
      ".LFUN_00025c10_18:\n\t"
      "movb %%al, 0x628(%%ebx)\n\t"
      ".LFUN_00025c10_19:\n\t"
      "movl -0x28(%%ebp), %%esi\n\t"
      ".LFUN_00025c10_20:\n\t"
      "movl -0x10(%%ebp), %%ecx\n\t"
      "flds 0xac(%%ecx)\n\t"
      "flds 0xa8(%%ecx)\n\t"
      "flds 0xa4(%%ecx)\n\t"
      "fld %%st(0)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fld %%st(2)\n\t"
      ".byte 0xd8, 0xcb\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fld %%st(3)\n\t"
      ".byte 0xd8, 0xcc\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fcomps 0x253f44\n\t"
      "fstp %%st(0)\n\t"
      "fnstsw %%ax\n\t"
      "fstp %%st(0)\n\t"
      "testb $0x41, %%ah\n\t"
      "fstp %%st(0)\n\t"
      "jne .LFUN_00025c10_21\n\t"
      "movb $1, 0x5dc(%%ebx)\n\t"
      "movl 0xa4(%%ecx), %%eax\n\t"
      "leal 0x5e0(%%ebx), %%edx\n\t"
      "movl %%eax, (%%edx)\n\t"
      "movl 0xa8(%%ecx), %%eax\n\t"
      "movl %%eax, 0x4(%%edx)\n\t"
      "movl 0xac(%%ecx), %%eax\n\t"
      "movl %%eax, 0x8(%%edx)\n\t"
      "jmp .LFUN_00025c10_23\n\t"
      ".LFUN_00025c10_21:\n\t"
      "flds 0x3c(%%esi)\n\t"
      "flds 0x38(%%esi)\n\t"
      "flds 0x34(%%esi)\n\t"
      "fld %%st(0)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fld %%st(2)\n\t"
      ".byte 0xd8, 0xcb\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fld %%st(3)\n\t"
      ".byte 0xd8, 0xcc\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fcomps 0x253f44\n\t"
      "fstp %%st(0)\n\t"
      "fnstsw %%ax\n\t"
      "fstp %%st(0)\n\t"
      "testb $0x41, %%ah\n\t"
      "fstp %%st(0)\n\t"
      "jne .LFUN_00025c10_22\n\t"
      "movb $1, 0x5dc(%%ebx)\n\t"
      "movl 0x34(%%esi), %%eax\n\t"
      "leal 0x5e0(%%ebx), %%edx\n\t"
      "movl %%eax, (%%edx)\n\t"
      "movl 0x38(%%esi), %%eax\n\t"
      "movl %%eax, 0x4(%%edx)\n\t"
      "movl 0x3c(%%esi), %%eax\n\t"
      "movl %%eax, 0x8(%%edx)\n\t"
      "jmp .LFUN_00025c10_23\n\t"
      ".LFUN_00025c10_22:\n\t"
      "movb $0, 0x5dc(%%ebx)\n\t"
      ".LFUN_00025c10_23:\n\t"
      "flds 0xb8(%%ecx)\n\t"
      "addl $0xb0, %%ecx\n\t"
      "flds 0x4(%%ecx)\n\t"
      "flds (%%ecx)\n\t"
      "fld %%st(0)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fld %%st(2)\n\t"
      ".byte 0xd8, 0xcb\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fld %%st(3)\n\t"
      ".byte 0xd8, 0xcc\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fcomps 0x253f44\n\t"
      "fstp %%st(0)\n\t"
      "fnstsw %%ax\n\t"
      "fstp %%st(0)\n\t"
      "testb $0x41, %%ah\n\t"
      "fstp %%st(0)\n\t"
      "jne .LFUN_00025c10_24\n\t"
      "movb $1, 0x5ec(%%ebx)\n\t"
      "movl (%%ecx), %%eax\n\t"
      "leal 0x5f0(%%ebx), %%edx\n\t"
      "movl %%eax, (%%edx)\n\t"
      "movl 0x4(%%ecx), %%eax\n\t"
      "movl %%eax, 0x4(%%edx)\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "movl %%ecx, 0x8(%%edx)\n\t"
      "jmp .LFUN_00025c10_26\n\t"
      ".LFUN_00025c10_24:\n\t"
      "flds 0x48(%%esi)\n\t"
      "flds 0x44(%%esi)\n\t"
      "flds 0x40(%%esi)\n\t"
      "fld %%st(0)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fld %%st(2)\n\t"
      ".byte 0xd8, 0xcb\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fld %%st(3)\n\t"
      ".byte 0xd8, 0xcc\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fcomps 0x253f44\n\t"
      "fstp %%st(0)\n\t"
      "fnstsw %%ax\n\t"
      "fstp %%st(0)\n\t"
      "testb $0x41, %%ah\n\t"
      "fstp %%st(0)\n\t"
      "jne .LFUN_00025c10_25\n\t"
      "movb $1, 0x5ec(%%ebx)\n\t"
      "movl 0x40(%%esi), %%eax\n\t"
      "leal 0x5f0(%%ebx), %%edx\n\t"
      "movl %%eax, (%%edx)\n\t"
      "movl 0x44(%%esi), %%ecx\n\t"
      "movl %%ecx, 0x4(%%edx)\n\t"
      "movl 0x48(%%esi), %%eax\n\t"
      "movl %%eax, 0x8(%%edx)\n\t"
      "jmp .LFUN_00025c10_26\n\t"
      ".LFUN_00025c10_25:\n\t"
      "movb $0, 0x5ec(%%ebx)\n\t"
      ".LFUN_00025c10_26:\n\t"
      "cmpw $0, 0x280(%%edi)\n\t"
      "jle .LFUN_00025c10_27\n\t"
      "movb 0x287(%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00025c10_27\n\t"
      "flds 0x2d8(%%edi)\n\t"
      "fadds 0x254644\n\t"
      "fcomps 0x2d4(%%edi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00025c10_27\n\t"
      "movb $1, 0x40(%%ebx)\n\t"
      ".LFUN_00025c10_27:\n\t"
      "movb 0x99(%%edi), %%cl\n\t"
      "movb %%cl, 0x44(%%ebx)\n\t"
      "cmpw $4, 0x15e(%%edi)\n\t"
      "jne .LFUN_00025c10_28\n\t"
      "movb $1, 0x45(%%ebx)\n\t"
      "movb $1, 0x46(%%ebx)\n\t"
      ".LFUN_00025c10_28:\n\t"
      "movl $0, 0x50(%%ebx)\n\t"
      "movb 0x3d8(%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00025c10_29\n\t"
      "leal 0x3dc(%%edi), %%edx\n\t"
      "movl (%%edx), %%ecx\n\t"
      "leal 0x58(%%ebx), %%eax\n\t"
      "movl %%ecx, (%%eax)\n\t"
      "movl 0x4(%%edx), %%ecx\n\t"
      "movl %%ecx, 0x4(%%eax)\n\t"
      "movl 0x8(%%edx), %%edx\n\t"
      "movl %%edx, 0x8(%%eax)\n\t"
      "movl 0x50(%%ebx), %%eax\n\t"
      "movl 0x3c8(%%esi), %%ecx\n\t"
      "shll $4, %%eax\n\t"
      "movl %%ecx, 0x54(%%eax,%%ebx,1)\n\t"
      "incl 0x50(%%ebx)\n\t"
      ".LFUN_00025c10_29:\n\t"
      "movl -0x28(%%ebp), %%edx\n\t"
      "flds 0x3cc(%%edx)\n\t"
      "movl $0x20, %%esi\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00025c10_33\n\t"
      "movswl 0x4(%%ebx), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_00025c10_30\n\t"
      "cmpl $3, %%eax\n\t"
      "je .LFUN_00025c10_30\n\t"
      "cmpl $6, %%eax\n\t"
      "jne .LFUN_00025c10_33\n\t"
      ".LFUN_00025c10_30:\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x14(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c64540]\n\t"
      "movl 0x50(%%ebx), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "cmpl %%esi, %%eax\n\t"
      "jge .LFUN_00025c10_33\n\t"
      "leal (%%ebx), %%ebx\n\t"
      ".LFUN_00025c10_31:\n\t"
      "leal -0x14(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c64570]\n\t"
      "addl $4, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_00025c10_33\n\t"
      "movw 0x24(%%eax), %%cx\n\t"
      "cmpw $2, %%cx\n\t"
      "jl .LFUN_00025c10_32\n\t"
      "cmpw $3, %%cx\n\t"
      "jg .LFUN_00025c10_32\n\t"
      "movb 0x60(%%eax), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "jne .LFUN_00025c10_32\n\t"
      "movb 0x127(%%eax), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "jne .LFUN_00025c10_32\n\t"
      "movb 0x12e(%%eax), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "jne .LFUN_00025c10_32\n\t"
      "movl 0x50(%%ebx), %%ecx\n\t"
      "shll $4, %%ecx\n\t"
      "addl $0xbc, %%eax\n\t"
      "leal 0x58(%%ecx,%%ebx,1), %%edx\n\t"
      "movl (%%eax), %%ecx\n\t"
      "movl %%ecx, (%%edx)\n\t"
      "movl 0x4(%%eax), %%ecx\n\t"
      "movl %%ecx, 0x4(%%edx)\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl %%eax, 0x8(%%edx)\n\t"
      "movl 0x50(%%ebx), %%ecx\n\t"
      "movl -0x28(%%ebp), %%edx\n\t"
      "movl 0x3cc(%%edx), %%eax\n\t"
      "shll $4, %%ecx\n\t"
      "movl %%eax, 0x54(%%ecx,%%ebx,1)\n\t"
      "incl 0x50(%%ebx)\n\t"
      ".LFUN_00025c10_32:\n\t"
      "cmpl %%esi, 0x50(%%ebx)\n\t"
      "jl .LFUN_00025c10_31\n\t"
      ".LFUN_00025c10_33:\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw %%ax, 0x254(%%ebx)\n\t"
      "movw %%ax, 0x256(%%ebx)\n\t"
      "movw %%ax, 0x258(%%ebx)\n\t"
      "movl -0x28(%%ebp), %%eax\n\t"
      "movl (%%eax), %%edx\n\t"
      "xorb %%cl, %%cl\n\t"
      "testl %%edx, %%edx\n\t"
      "jns .LFUN_00025c10_34\n\t"
      "cmpw $3, 0x6e(%%edi)\n\t"
      "jl .LFUN_00025c10_34\n\t"
      "movb 0x200(%%edi), %%dl\n\t"
      "testb %%dl, %%dl\n\t"
      "jle .LFUN_00025c10_34\n\t"
      "movb $1, %%cl\n\t"
      ".LFUN_00025c10_34:\n\t"
      "testb $1, 0x4(%%eax)\n\t"
      "je .LFUN_00025c10_35\n\t"
      "cmpw $3, 0x6e(%%edi)\n\t"
      "jl .LFUN_00025c10_35\n\t"
      "movb $1, %%cl\n\t"
      ".LFUN_00025c10_35:\n\t"
      "movswl 0x4(%%ebx), %%eax\n\t"
      "cmpl $6, %%eax\n\t"
      "ja .LFUN_00025c10_45\n\t"
      "movzbl 0x27084(%%eax), %%edx\n\t"
      "jmp *.LFUN_00025c10_jt(,%%edx,4)\n\t"
      ".LFUN_00025c10_36:\n\t"
      "testb %%cl, %%cl\n\t"
      "je .LFUN_00025c10_45\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x14(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c64540]\n\t"
      "addl $8, %%esp\n\t"
      "cmpw %%si, 0x254(%%ebx)\n\t"
      "jge .LFUN_00025c10_45\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_00025c10_37:\n\t"
      "leal -0x14(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c64570]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $4, %%esp\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_00025c10_45\n\t"
      "movw 0x24(%%esi), %%ax\n\t"
      "cmpw $2, %%ax\n\t"
      "jl .LFUN_00025c10_44\n\t"
      "cmpw $3, %%ax\n\t"
      "jg .LFUN_00025c10_44\n\t"
      "movb 0x127(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00025c10_44\n\t"
      "movb 0x60(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00025c10_40\n\t"
      "movb 0x12e(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00025c10_38\n\t"
      "cmpl $-1, 0x110(%%esi)\n\t"
      "jne .LFUN_00025c10_39\n\t"
      ".LFUN_00025c10_38:\n\t"
      "movl -0x14(%%ebp), %%ecx\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "leal -0x3c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c309d0]\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00025c10_39\n\t"
      "movb 0x12e(%%esi), %%dl\n\t"
      "movswl 0x254(%%ebx), %%ecx\n\t"
      "xorl %%eax, %%eax\n\t"
      "testb %%dl, %%dl\n\t"
      "setne %%al\n\t"
      "imull $0x1c, %%ecx, %%ecx\n\t"
      "movw %%ax, 0x25c(%%ecx,%%ebx,1)\n\t"
      "movswl 0x254(%%ebx), %%eax\n\t"
      "imull $0x1c, %%eax, %%eax\n\t"
      "leal 0x260(%%eax,%%ebx,1), %%ecx\n\t"
      "leal 0xbc(%%esi), %%edx\n\t"
      "movl (%%edx), %%eax\n\t"
      "movl %%eax, (%%ecx)\n\t"
      "movl 0x4(%%edx), %%eax\n\t"
      "movl %%eax, 0x4(%%ecx)\n\t"
      "movl 0x8(%%edx), %%edx\n\t"
      "movl %%edx, 0x8(%%ecx)\n\t"
      "movswl 0x254(%%ebx), %%eax\n\t"
      "movl -0x3c(%%ebp), %%edx\n\t"
      "imull $0x1c, %%eax, %%eax\n\t"
      "leal 0x26c(%%eax,%%ebx,1), %%ecx\n\t"
      "movl %%edx, (%%ecx)\n\t"
      "movl -0x38(%%ebp), %%eax\n\t"
      "movl %%eax, 0x4(%%ecx)\n\t"
      "movl -0x34(%%ebp), %%edx\n\t"
      "movl %%edx, 0x8(%%ecx)\n\t"
      "incw 0x254(%%ebx)\n\t"
      "incw 0x256(%%ebx)\n\t"
      ".LFUN_00025c10_39:\n\t"
      "movb 0x60(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00025c10_44\n\t"
      ".LFUN_00025c10_40:\n\t"
      "movl -0x28(%%ebp), %%eax\n\t"
      "movb 0x4(%%eax), %%al\n\t"
      "movb 0xa4(%%esi), %%cl\n\t"
      "andb $1, %%al\n\t"
      "testb %%cl, %%cl\n\t"
      "je .LFUN_00025c10_41\n\t"
      "movb 0x12e(%%esi), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "jne .LFUN_00025c10_42\n\t"
      "movb 0x12f(%%esi), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "jne .LFUN_00025c10_42\n\t"
      ".LFUN_00025c10_41:\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00025c10_44\n\t"
      ".LFUN_00025c10_42:\n\t"
      "movl 0x110(%%esi), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "jne .LFUN_00025c10_43\n\t"
      "movl 0x18(%%esi), %%eax\n\t"
      ".LFUN_00025c10_43:\n\t"
      "movswl 0x254(%%ebx), %%ecx\n\t"
      "imull $0x1c, %%ecx, %%ecx\n\t"
      "movw $2, 0x25c(%%ecx,%%ebx,1)\n\t"
      "movswl 0x254(%%ebx), %%edx\n\t"
      "imull $0x1c, %%edx, %%edx\n\t"
      "leal 0x260(%%edx,%%ebx,1), %%ecx\n\t"
      "addl $0xbc, %%esi\n\t"
      "movl (%%esi), %%edx\n\t"
      "movl %%edx, (%%ecx)\n\t"
      "movl 0x4(%%esi), %%edx\n\t"
      "movl %%edx, 0x4(%%ecx)\n\t"
      "movl 0x8(%%esi), %%edx\n\t"
      "movl %%edx, 0x8(%%ecx)\n\t"
      "movswl 0x254(%%ebx), %%ecx\n\t"
      "imull $0x1c, %%ecx, %%ecx\n\t"
      "leal 0x26c(%%ecx,%%ebx,1), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c1a9900]\n\t"
      "addl $8, %%esp\n\t"
      "incw 0x254(%%ebx)\n\t"
      "incw 0x258(%%ebx)\n\t"
      ".LFUN_00025c10_44:\n\t"
      "cmpw $0x20, 0x254(%%ebx)\n\t"
      "jl .LFUN_00025c10_37\n\t"
      ".LFUN_00025c10_45:\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "xorl %%esi, %%esi\n\t"
      "testb %%al, %%al\n\t"
      "movw %%si, 0x66e(%%ebx)\n\t"
      "movw %%si, 0x66c(%%ebx)\n\t"
      "movw %%si, 0x66a(%%ebx)\n\t"
      "movw %%si, 0x668(%%ebx)\n\t"
      "movw %%si, 0x666(%%ebx)\n\t"
      "movw %%si, 0x664(%%ebx)\n\t"
      "je .LFUN_00025c10_46\n\t"
      "movl $0x19c, %%ecx\n\t"
      "movl %%ebx, %%esi\n\t"
      "movl $0x629d44, %%edi\n\t"
      "movb $1, 0x629d40\n\t"
      "rep movsl\n\t"
      "xorl %%esi, %%esi\n\t"
      ".LFUN_00025c10_46:\n\t"
      "movl 0x1c(%%ebp), %%edi\n\t"
      "cmpl %%esi, %%edi\n\t"
      "jne .LFUN_00025c10_47\n\t"
      "pushl $1\n\t"
      "pushl $0x726\n\t"
      "pushl $0x254c8c\n\t"
      "pushl $0x254fcc\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00025c10_47:\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "addl $0x98, %%eax\n\t"
      "movb $0, (%%edi)\n\t"
      "cmpl %%esi, (%%eax)\n\t"
      "movb $0, -0x19(%%ebp)\n\t"
      "movl %%esi, -0x10(%%ebp)\n\t"
      "movl %%eax, -0x20(%%ebp)\n\t"
      "jle .LFUN_00025c10_58\n\t"
      "xorl %%edi, %%edi\n\t"
      ".LFUN_00025c10_48:\n\t"
      "movl -0x20(%%ebp), %%eax\n\t"
      "pushl $0x18\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl %%eax, %%esi\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00025c10_49\n\t"
      "movl %%edi, %%ecx\n\t"
      "shll $6, %%ecx\n\t"
      "movb $0, 0x62a3b5(%%ecx)\n\t"
      ".LFUN_00025c10_49:\n\t"
      "movb 0xc(%%esi), %%cl\n\t"
      "movl (%%ebx), %%eax\n\t"
      "movl $1, %%edx\n\t"
      "shll %%cl, %%edx\n\t"
      "testl %%edx, %%eax\n\t"
      "je .LFUN_00025c10_57\n\t"
      "movl -0x2c(%%ebp), %%eax\n\t"
      "movl 0x34(%%eax), %%ecx\n\t"
      "cmpl 0x5ac9f4, %%ecx\n\t"
      "jne .LFUN_00025c10_50\n\t"
      "cmpw $5, 0x4(%%ebx)\n\t"
      "movl %%edi, %%eax\n\t"
      "sete %%dl\n\t"
      "shll $6, %%eax\n\t"
      "movb %%dl, 0x62a3b4(%%eax)\n\t"
      ".LFUN_00025c10_50:\n\t"
      "movb 0x44(%%ebx), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00025c10_51\n\t"
      "cmpl $-1, 0x14(%%esi)\n\t"
      "je .LFUN_00025c10_57\n\t"
      ".LFUN_00025c10_51:\n\t"
      "cmpw $5, 0x4(%%ebx)\n\t"
      "jne .LFUN_00025c10_52\n\t"
      "movl 0x14(%%esi), %%ecx\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "pushl $1\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edx\n\t"
      "call *%[c25a00]\n\t"
      "addl $0x10, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00025c10_57\n\t"
      ".LFUN_00025c10_52:\n\t"
      "movl -0x890(%%ebp,%%edi,4), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "leal -0x890(%%ebp,%%edi,4), %%edi\n\t"
      "je .LFUN_00025c10_54\n\t"
      "cmpw $4, 0x4(%%ebx)\n\t"
      "jne .LFUN_00025c10_53\n\t"
      "movl 0x50(%%ebx), %%eax\n\t"
      "cmpl $0x20, %%eax\n\t"
      "jge .LFUN_00025c10_53\n\t"
      "shll $4, %%eax\n\t"
      "leal 0x58(%%eax,%%ebx,1), %%eax\n\t"
      "movl %%esi, %%ecx\n\t"
      "movl (%%ecx), %%edx\n\t"
      "movl %%edx, (%%eax)\n\t"
      "movl 0x4(%%ecx), %%edx\n\t"
      "movl %%edx, 0x4(%%eax)\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "movl %%ecx, 0x8(%%eax)\n\t"
      "movl 0x50(%%ebx), %%edx\n\t"
      "shll $4, %%edx\n\t"
      "movl $0x40800000, 0x54(%%edx,%%ebx,1)\n\t"
      "incl 0x50(%%ebx)\n\t"
      ".LFUN_00025c10_53:\n\t"
      "movl (%%edi), %%eax\n\t"
      "movl 0x6325a4, %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "flds (%%esi)\n\t"
      "fsubs 0x12c(%%eax)\n\t"
      "addl $0x12c, %%eax\n\t"
      "flds 0x4(%%esi)\n\t"
      "addl $8, %%esp\n\t"
      "fsubs 0x4(%%eax)\n\t"
      "flds 0x8(%%esi)\n\t"
      "fsubs 0x8(%%eax)\n\t"
      "movl -0x2c(%%ebp), %%eax\n\t"
      "fld %%st(2)\n\t"
      ".byte 0xde, 0xcb\n\t"
      "fld %%st(0)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      ".byte 0xde, 0xc3\n\t"
      "fld %%st(1)\n\t"
      ".byte 0xd8, 0xca\n\t"
      ".byte 0xde, 0xc3\n\t"
      "fxch %%st(2)\n\t"
      "fsqrt\n\t"
      "fstp %%st(2)\n\t"
      "fstp %%st(0)\n\t"
      "flds (%%esi)\n\t"
      "fsubs 0x12c(%%eax)\n\t"
      "flds 0x4(%%esi)\n\t"
      "fsubs 0x130(%%eax)\n\t"
      "flds 0x8(%%esi)\n\t"
      "fsubs 0x134(%%eax)\n\t"
      "fld %%st(3)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .LFUN_00025c10_56\n\t"
      "fld %%st(2)\n\t"
      ".byte 0xde, 0xcb\n\t"
      "fld %%st(0)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      ".byte 0xde, 0xc3\n\t"
      "fld %%st(1)\n\t"
      ".byte 0xd8, 0xca\n\t"
      ".byte 0xde, 0xc3\n\t"
      "fxch %%st(2)\n\t"
      "fsqrt\n\t"
      "fstp %%st(2)\n\t"
      "fstp %%st(0)\n\t"
      ".byte 0xdc, 0xc0\n\t"
      "fxch %%st(1)\n\t"
      "fcompp\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .LFUN_00025c10_57\n\t"
      ".LFUN_00025c10_54:\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "cmpw $0x200, %%ax\n\t"
      "jge .LFUN_00025c10_55\n\t"
      "movl 0x31fc38, %%ecx\n\t"
      "movw -0x10(%%ebp), %%dx\n\t"
      "movswl %%ax, %%eax\n\t"
      "imull $0x3c, %%eax, %%eax\n\t"
      "movw %%dx, -0x888c(%%ebp,%%eax,1)\n\t"
      "movl %%esi, -0x8890(%%ebp,%%eax,1)\n\t"
      "movw $0, -0x888a(%%ebp,%%eax,1)\n\t"
      "movl $0x7f7fffff, -0x8888(%%ebp,%%eax,1)\n\t"
      "movl %%ecx, %%esi\n\t"
      "movl (%%esi), %%edi\n\t"
      "leal -0x8884(%%ebp,%%eax,1), %%edx\n\t"
      "movl %%edi, (%%edx)\n\t"
      "movl 0x4(%%esi), %%edi\n\t"
      "movl %%edi, 0x4(%%edx)\n\t"
      "movl 0x8(%%esi), %%esi\n\t"
      "movl %%esi, 0x8(%%edx)\n\t"
      "movl $0x7f7fffff, %%edx\n\t"
      "movl %%edx, -0x8878(%%ebp,%%eax,1)\n\t"
      "movl %%edx, -0x8874(%%ebp,%%eax,1)\n\t"
      "movl (%%ecx), %%esi\n\t"
      "leal -0x8870(%%ebp,%%eax,1), %%edx\n\t"
      "movl %%esi, (%%edx)\n\t"
      "movl 0x4(%%ecx), %%esi\n\t"
      "movl %%esi, 0x4(%%edx)\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "movl %%ecx, 0x8(%%edx)\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movl %%ecx, -0x8864(%%ebp,%%eax,1)\n\t"
      "movl %%ecx, -0x885c(%%ebp,%%eax,1)\n\t"
      "movl %%ecx, -0x8858(%%ebp,%%eax,1)\n\t"
      "movb $1, -0x8860(%%ebp,%%eax,1)\n\t"
      "movb %%cl, -0x885f(%%ebp,%%eax,1)\n\t"
      "incl -0x8(%%ebp)\n\t"
      "jmp .LFUN_00025c10_57\n\t"
      ".LFUN_00025c10_55:\n\t"
      "movb -0x19(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00025c10_57\n\t"
      "movl -0x20(%%ebp), %%edx\n\t"
      "movl (%%edx), %%eax\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "pushl $0x200\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x254f94\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $0x14, %%esp\n\t"
      "movb $1, -0x19(%%ebp)\n\t"
      "jmp .LFUN_00025c10_57\n\t"
      ".LFUN_00025c10_56:\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      ".LFUN_00025c10_57:\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "incl %%eax\n\t"
      "movswl %%ax, %%edi\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "movl 0x98(%%eax), %%ecx\n\t"
      "addl $0x98, %%eax\n\t"
      "cmpl %%ecx, %%edi\n\t"
      "movl %%eax, -0x20(%%ebp)\n\t"
      "jl .LFUN_00025c10_48\n\t"
      "jmp .LFUN_00025c10_59\n\t"
      ".LFUN_00025c10_58:\n\t"
      "movl -0x20(%%ebp), %%eax\n\t"
      ".LFUN_00025c10_59:\n\t"
      "movw (%%eax), %%dx\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "testw %%ax, %%ax\n\t"
      "movw %%dx, 0x664(%%ebx)\n\t"
      "movw %%ax, 0x666(%%ebx)\n\t"
      "jne .LFUN_00025c10_63\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl 0x6325a4, %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "addl $8, %%esp\n\t"
      "movw $0, 0x3c6(%%eax)\n\t"
      "leal 0x3ca(%%eax), %%ecx\n\t"
      "movl $4, %%edx\n\t"
      ".LFUN_00025c10_60:\n\t"
      "movw $0xffff, (%%ecx)\n\t"
      "addl $4, %%ecx\n\t"
      "decl %%edx\n\t"
      "jne .LFUN_00025c10_60\n\t"
      "movb 0x3d8(%%eax), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "je .LFUN_00025c10_61\n\t"
      "movb $0, 0x3d8(%%eax)\n\t"
      ".LFUN_00025c10_61:\n\t"
      "movw -0x30(%%ebp), %%ax\n\t"
      ".LFUN_00025c10_62:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00025c10_63:\n\t"
      "movb 0x5fc(%%ebx), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00025c10_70\n\t"
      "movb 0x42(%%ebx), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00025c10_70\n\t"
      "movb 0x44(%%ebx), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00025c10_66\n\t"
      "call *%[c18e3c0]\n\t"
      "cmpw $0, -0x8(%%ebp)\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "jle .LFUN_00025c10_70\n\t"
      "movzwl -0x8(%%ebp), %%edx\n\t"
      "leal 0x604(%%ebx), %%esi\n\t"
      "leal -0x8890(%%ebp), %%edi\n\t"
      "movl %%edx, -0xc(%%ebp)\n\t"
      ".LFUN_00025c10_64:\n\t"
      "movl (%%edi), %%ecx\n\t"
      "flds (%%ecx)\n\t"
      "fsubs (%%esi)\n\t"
      "fstps -0x3c(%%ebp)\n\t"
      "flds 0x4(%%ecx)\n\t"
      "fsubs 0x4(%%esi)\n\t"
      "fstps -0x38(%%ebp)\n\t"
      "flds 0x8(%%ecx)\n\t"
      "fsubs 0x8(%%esi)\n\t"
      "fstps -0x34(%%ebp)\n\t"
      "flds -0x3c(%%ebp)\n\t"
      "fmuls -0x3c(%%ebp)\n\t"
      "flds -0x34(%%ebp)\n\t"
      "fmuls -0x34(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds -0x38(%%ebp)\n\t"
      "fmuls -0x38(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fcomps 0x254f90\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00025c10_65\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl %%ecx\n\t"
      "pushl $0\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "call *%[c5e830]\n\t"
      "addl $0x18, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00025c10_65\n\t"
      "leal -0x3c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[norm]\n\t"
      "fstps 0x18(%%edi)\n\t"
      "movb 0x43(%%ebx), %%al\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00025c10_65\n\t"
      "movl -0x3c(%%ebp), %%edx\n\t"
      "movl -0x38(%%ebp), %%eax\n\t"
      "movl -0x34(%%ebp), %%ecx\n\t"
      "movl %%edx, 0x20(%%edi)\n\t"
      "movl %%eax, 0x24(%%edi)\n\t"
      "movl %%ecx, 0x28(%%edi)\n\t"
      ".LFUN_00025c10_65:\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "addl $0x3c, %%edi\n\t"
      "decl %%eax\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "jne .LFUN_00025c10_64\n\t"
      "jmp .LFUN_00025c10_70\n\t"
      ".LFUN_00025c10_66:\n\t"
      "cmpl $-1, 0x630(%%ebx)\n\t"
      "je .LFUN_00025c10_70\n\t"
      "movl -0x2c(%%ebp), %%edx\n\t"
      "movl -0x28(%%ebp), %%ecx\n\t"
      "xorl %%eax, %%eax\n\t"
      "movb 0x376(%%edx), %%al\n\t"
      "movl 0x8c(%%ecx), %%edx\n\t"
      "pushl $-1\n\t"
      "pushl %%eax\n\t"
      "pushl %%edx\n\t"
      "leal -0x90(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c5dfc0]\n\t"
      "movl 0x630(%%ebx), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal 0x634(%%ebx), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x90(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c5e000]\n\t"
      "leal -0x90(%%ebp), %%ecx\n\t"
      "pushl $0x41a00000\n\t"
      "pushl %%ecx\n\t"
      "call *%[c5e070]\n\t"
      "pushl $0\n\t"
      "leal -0x1c91c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x90(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c5e090]\n\t"
      "leal -0x1c91c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c5ff70]\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "addl $0x34, %%esp\n\t"
      "testw %%ax, %%ax\n\t"
      "jle .LFUN_00025c10_70\n\t"
      "leal -0x8890(%%ebp), %%esi\n\t"
      "movzwl %%ax, %%edi\n\t"
      ".LFUN_00025c10_67:\n\t"
      "movb 0x43(%%ebx), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00025c10_68\n\t"
      "leal 0x20(%%esi), %%ecx\n\t"
      "jmp .LFUN_00025c10_69\n\t"
      ".LFUN_00025c10_68:\n\t"
      "xorl %%ecx, %%ecx\n\t"
      ".LFUN_00025c10_69:\n\t"
      "movl (%%esi), %%eax\n\t"
      "pushl %%ecx\n\t"
      "movl 0x14(%%eax), %%ecx\n\t"
      "pushl $0\n\t"
      "leal 0x18(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "leal -0x1c91c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c5f550]\n\t"
      "addl $0x18, %%esp\n\t"
      "addl $0x3c, %%esi\n\t"
      "decl %%edi\n\t"
      "jne .LFUN_00025c10_67\n\t"
      ".LFUN_00025c10_70:\n\t"
      "movb 0x44(%%ebx), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00025c10_75\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "leal -0x90(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "call *%[c2a470]\n\t"
      "movl 0x1c(%%ebx), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x90(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c5e070]\n\t"
      "movb 0x36(%%ebx), %%al\n\t"
      "addl $0x10, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00025c10_72\n\t"
      "movb 0x5fc(%%ebx), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00025c10_72\n\t"
      "movl 0x644(%%ebx), %%eax\n\t"
      "orl $0xffffffff, %%ecx\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_00025c10_71\n\t"
      "pushl %%eax\n\t"
      "movl 0x5ab23c, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl 0x18(%%eax), %%ecx\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_00025c10_71:\n\t"
      "movl 0x38(%%ebx), %%edx\n\t"
      "movl 0x3c(%%ebx), %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "leal 0x604(%%ebx), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x90(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c5e030]\n\t"
      "movl -0x2c(%%ebp), %%esi\n\t"
      "jmp .LFUN_00025c10_73\n\t"
      ".LFUN_00025c10_72:\n\t"
      "movl -0x2c(%%ebp), %%esi\n\t"
      "cmpw $0, 0x280(%%esi)\n\t"
      "jle .LFUN_00025c10_74\n\t"
      "movl -0x28(%%ebp), %%eax\n\t"
      "testb $0x10, 0x4(%%eax)\n\t"
      "jne .LFUN_00025c10_74\n\t"
      "movl 0x28c(%%esi), %%ecx\n\t"
      "movl 0x294(%%esi), %%edx\n\t"
      "pushl $0x41200000\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "leal 0x2b0(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x90(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c5e030]\n\t"
      ".LFUN_00025c10_73:\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00025c10_74:\n\t"
      "pushl %%edi\n\t"
      "call *%[c49120]\n\t"
      "movl 0x18(%%ebp), %%edi\n\t"
      "pushl %%eax\n\t"
      "leal -0x90(%%ebp), %%edx\n\t"
      "pushl %%edi\n\t"
      "pushl %%edx\n\t"
      "call *%[c5e090]\n\t"
      "pushl %%edi\n\t"
      "call *%[c5ff70]\n\t"
      "addl $0x14, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00025c10_76\n\t"
      "movl 0x1c(%%ebp), %%eax\n\t"
      "movb $1, (%%eax)\n\t"
      "jmp .LFUN_00025c10_76\n\t"
      ".LFUN_00025c10_75:\n\t"
      "movl -0x2c(%%ebp), %%esi\n\t"
      ".LFUN_00025c10_76:\n\t"
      "cmpw $0, -0x8(%%ebp)\n\t"
      "jle .LFUN_00025c10_85\n\t"
      "movzwl -0x8(%%ebp), %%ecx\n\t"
      "leal 0x12c(%%esi), %%edi\n\t"
      "leal -0x8884(%%ebp), %%esi\n\t"
      "movl %%ecx, -0xc(%%ebp)\n\t"
      ".LFUN_00025c10_77:\n\t"
      "movb 0x5fc(%%ebx), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00025c10_78\n\t"
      "movl -0xc(%%esi), %%eax\n\t"
      "flds (%%eax)\n\t"
      "fsubs 0x604(%%ebx)\n\t"
      "flds 0x4(%%eax)\n\t"
      "fsubs 0x608(%%ebx)\n\t"
      "flds 0x8(%%eax)\n\t"
      "fsubs 0x60c(%%ebx)\n\t"
      "fld %%st(0)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fld %%st(2)\n\t"
      ".byte 0xd8, 0xcb\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fld %%st(3)\n\t"
      ".byte 0xd8, 0xcc\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fstps 0x20(%%esi)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      ".LFUN_00025c10_78:\n\t"
      "movl -0xc(%%esi), %%ecx\n\t"
      "flds (%%ecx)\n\t"
      "fsubs (%%edi)\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "flds 0x4(%%ecx)\n\t"
      "fsubs 0x4(%%edi)\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "flds 0x8(%%ecx)\n\t"
      "fsubs 0x8(%%edi)\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "flds 0x1c(%%ebx)\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fmuls -0x10(%%ebp)\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fmuls -0x14(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fmuls -0x18(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fld %%st(1)\n\t"
      ".byte 0xd8, 0xca\n\t"
      "fcompp\n\t"
      "fnstsw %%ax\n\t"
      "fstp %%st(0)\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00025c10_82\n\t"
      "movb 0x44(%%ebx), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00025c10_81\n\t"
      "leal -0x18(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal 0x604(%%ebx), %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[c10cd40]\n\t"
      "fsqrt\n\t"
      "addl $0xc, %%esp\n\t"
      "fstps 0x10(%%esi)\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fmuls -0x10(%%ebp)\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fmuls -0x14(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fmuls -0x18(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fsqrt\n\t"
      "fld %%st(0)\n\t"
      "fabs\n\t"
      "fcompl 0x2533d0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .LFUN_00025c10_79\n\t"
      "flds 0x2533c8\n\t"
      ".byte 0xd8, 0xf1\n\t"
      "flds -0x18(%%ebp)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "flds -0x14(%%ebp)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "flds -0x10(%%ebp)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "jmp .LFUN_00025c10_80\n\t"
      ".LFUN_00025c10_79:\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c0\n\t"
      ".LFUN_00025c10_80:\n\t"
      "movb 0x40(%%ebx), %%al\n\t"
      "fstps -0x4(%%esi)\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00025c10_82\n\t"
      "movl -0x18(%%ebp), %%edx\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "movl %%esi, %%ecx\n\t"
      "movl %%edx, (%%ecx)\n\t"
      "movl -0x10(%%ebp), %%edx\n\t"
      "movl %%eax, 0x4(%%ecx)\n\t"
      "movl %%edx, 0x8(%%ecx)\n\t"
      "jmp .LFUN_00025c10_82\n\t"
      ".LFUN_00025c10_81:\n\t"
      "movb 0x40(%%ebx), %%al\n\t"
      "negb %%al\n\t"
      "leal -0x4(%%esi), %%edx\n\t"
      "sbbl %%eax, %%eax\n\t"
      "andl %%esi, %%eax\n\t"
      "pushl %%eax\n\t"
      "leal 0x10(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl 0x14(%%ecx), %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "movl 0x18(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c5f550]\n\t"
      "addl $0x18, %%esp\n\t"
      ".LFUN_00025c10_82:\n\t"
      "flds -0x4(%%esi)\n\t"
      "fcomps 0x1c(%%ebx)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00025c10_83\n\t"
      "movb $1, -0x2(%%ebp)\n\t"
      "jmp .LFUN_00025c10_84\n\t"
      ".LFUN_00025c10_83:\n\t"
      "movb $0, 0x24(%%esi)\n\t"
      ".LFUN_00025c10_84:\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "addl $0x3c, %%esi\n\t"
      "decl %%eax\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "jne .LFUN_00025c10_77\n\t"
      ".LFUN_00025c10_85:\n\t"
      "movb 0x15(%%ebx), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00025c10_90\n\t"
      "movb -0x2(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00025c10_90\n\t"
      "cmpw $0, -0x8(%%ebp)\n\t"
      "jg .LFUN_00025c10_86\n\t"
      "pushl $1\n\t"
      "pushl $0x83c\n\t"
      "pushl $0x254c8c\n\t"
      "pushl $0x254f74\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00025c10_86:\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0\n\t"
      "call *%[gseed]\n\t"
      "pushl %%eax\n\t"
      "call *%[c10b2d0]\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "pushl %%edi\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x1c(%%ebp), %%eax\n\t"
      "movb $0, (%%eax)\n\t"
      "movl 0x6325a4, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl %%esi, -0x30(%%ebp)\n\t"
      "call *%[dget]\n\t"
      "addl $0x14, %%esp\n\t"
      "movw $0, 0x3c6(%%eax)\n\t"
      "leal 0x3ca(%%eax), %%ecx\n\t"
      "movl $4, %%edx\n\t"
      "nop\n\t"
      ".LFUN_00025c10_87:\n\t"
      "movw $0xffff, (%%ecx)\n\t"
      "addl $4, %%ecx\n\t"
      "decl %%edx\n\t"
      "jne .LFUN_00025c10_87\n\t"
      "movb 0x3d8(%%eax), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "je .LFUN_00025c10_88\n\t"
      "movb $0, 0x3d8(%%eax)\n\t"
      ".LFUN_00025c10_88:\n\t"
      "movswl %%si, %%eax\n\t"
      "imull $0x3c, %%eax, %%eax\n\t"
      "leal -0x8890(%%ebp,%%eax,1), %%eax\n\t"
      "pushl %%edi\n\t"
      "movl %%ebx, %%esi\n\t"
      "movl %%eax, -0x24(%%ebp)\n\t"
      "call *%[c25970]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00025c10_89\n\t"
      "movl $0xffffffff, -0x30(%%ebp)\n\t"
      ".LFUN_00025c10_89:\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00025c10_110\n\t"
      "movl -0x24(%%ebp), %%esi\n\t"
      "movswl 0x4(%%esi), %%eax\n\t"
      "shll $6, %%eax\n\t"
      "leal 0x62a3b8(%%eax), %%edi\n\t"
      "movl $0xf, %%ecx\n\t"
      "movb $1, 0x62a3b5(%%eax)\n\t"
      "rep movsl\n\t"
      "jmp .LFUN_00025c10_110\n\t"
      ".LFUN_00025c10_90:\n\t"
      "movl 0x254bf8, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "movb $0, -0x2(%%ebp)\n\t"
      "je .LFUN_00025c10_93\n\t"
      "movl $0x254bf8, %%esi\n\t"
      ".LFUN_00025c10_91:\n\t"
      "movb 0x4(%%ebx), %%cl\n\t"
      "movswl -0x4(%%esi), %%eax\n\t"
      "movl $1, %%edx\n\t"
      "shll %%cl, %%edx\n\t"
      "testl %%edx, %%eax\n\t"
      "je .LFUN_00025c10_92\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "leal -0x8890(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "call *(%%esi)\n\t"
      "addl $0x10, %%esp\n\t"
      ".LFUN_00025c10_92:\n\t"
      "movl 0x8(%%esi), %%eax\n\t"
      "addl $8, %%esi\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_00025c10_91\n\t"
      ".LFUN_00025c10_93:\n\t"
      "cmpw $0, -0x8(%%ebp)\n\t"
      "jle .LFUN_00025c10_95\n\t"
      "movzwl -0x8(%%ebp), %%edx\n\t"
      "xorl %%eax, %%eax\n\t"
      "leal -0x1090(%%ebp), %%ecx\n\t"
      ".LFUN_00025c10_94:\n\t"
      "movl %%eax, (%%ecx)\n\t"
      "incl %%eax\n\t"
      "addl $4, %%ecx\n\t"
      "decl %%edx\n\t"
      "jne .LFUN_00025c10_94\n\t"
      ".LFUN_00025c10_95:\n\t"
      "movl -0x8(%%ebp), %%esi\n\t"
      "movswl %%si, %%edx\n\t"
      "pushl $0x24950\n\t"
      "pushl %%edx\n\t"
      "leal -0x1090(%%ebp), %%eax\n\t"
      "leal -0x8890(%%ebp), %%ecx\n\t"
      "pushl %%eax\n\t"
      "movw %%si, 0x331f00\n\t"
      "movl %%ecx, 0x331f04\n\t"
      "call *%[c91ef0]\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl %%ebx, %%edi\n\t"
      "call *%[c24900]\n\t"
      "addl $0x10, %%esp\n\t"
      "testw %%si, %%si\n\t"
      "movb %%al, 0x65c(%%ebx)\n\t"
      "movl $0, -0xc(%%ebp)\n\t"
      "jle .LFUN_00025c10_107\n\t"
      "movl %%edi, %%edi\n\t"
      ".LFUN_00025c10_96:\n\t"
      "movl -0xc(%%ebp), %%edi\n\t"
      "movswl %%di, %%edx\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw -0x1090(%%ebp,%%edx,4), %%ax\n\t"
      "movswl %%ax, %%esi\n\t"
      "imull $0x3c, %%esi, %%esi\n\t"
      "leal -0x8890(%%ebp,%%esi,1), %%esi\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "movb 0x30(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00025c10_97\n\t"
      "incw 0x668(%%ebx)\n\t"
      ".LFUN_00025c10_97:\n\t"
      "movb 0x31(%%esi), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "jne .LFUN_00025c10_98\n\t"
      "incw 0x66a(%%ebx)\n\t"
      ".LFUN_00025c10_98:\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00025c10_99\n\t"
      "movb 0x65c(%%ebx), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00025c10_100\n\t"
      "flds 0x38(%%esi)\n\t"
      "fadds 0x660(%%ebx)\n\t"
      "fcomps -0x24(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .LFUN_00025c10_100\n\t"
      ".LFUN_00025c10_99:\n\t"
      "call *%[cfff80]\n\t"
      "testw %%ax, %%ax\n\t"
      "jne .LFUN_00025c10_104\n\t"
      "movb 0x5ac9c5, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00025c10_104\n\t"
      "movb $1, -0x2(%%ebp)\n\t"
      ".LFUN_00025c10_100:\n\t"
      "movb 0x30(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00025c10_103\n\t"
      "movb 0x5fc(%%ebx), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00025c10_101\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl %%esi, %%edi\n\t"
      "movl %%ebx, %%ecx\n\t"
      "call *%[c257a0]\n\t"
      ".LFUN_00025c10_101:\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "movl 0x38(%%esi), %%eax\n\t"
      "incw 0x66c(%%ebx)\n\t"
      "pushl %%esi\n\t"
      "pushl %%ecx\n\t"
      "movl %%ebx, %%edi\n\t"
      "movl %%eax, 0x34(%%esi)\n\t"
      "call *%[c24890]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00025c10_103\n\t"
      "flds 0x38(%%esi)\n\t"
      "fcomps -0x24(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00025c10_103\n\t"
      "movb -0x2(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00025c10_102\n\t"
      "pushl $1\n\t"
      "pushl $0x8c3\n\t"
      "pushl $0x254c8c\n\t"
      "pushl $0x254f5c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00025c10_102:\n\t"
      "movl -0x10(%%ebp), %%edx\n\t"
      "movl 0x38(%%esi), %%eax\n\t"
      "movl %%edx, -0x30(%%ebp)\n\t"
      "movl %%eax, -0x24(%%ebp)\n\t"
      ".LFUN_00025c10_103:\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "incl %%eax\n\t"
      "cmpw -0x8(%%ebp), %%ax\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "jl .LFUN_00025c10_96\n\t"
      "jmp .LFUN_00025c10_107\n\t"
      ".LFUN_00025c10_104:\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "cmpw %%cx, %%di\n\t"
      "jge .LFUN_00025c10_107\n\t"
      "movswl %%di, %%eax\n\t"
      "subl %%edi, %%ecx\n\t"
      "leal -0x1090(%%ebp,%%eax,4), %%eax\n\t"
      "movzwl %%cx, %%ecx\n\t"
      ".LFUN_00025c10_105:\n\t"
      "movl (%%eax), %%edx\n\t"
      "imull $0x3c, %%edx, %%edx\n\t"
      "cmpb $0, -0x8860(%%ebp,%%edx,1)\n\t"
      "je .LFUN_00025c10_106\n\t"
      "incw 0x668(%%ebx)\n\t"
      "incw 0x66e(%%ebx)\n\t"
      ".LFUN_00025c10_106:\n\t"
      "addl $4, %%eax\n\t"
      "decl %%ecx\n\t"
      "jne .LFUN_00025c10_105\n\t"
      ".LFUN_00025c10_107:\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00025c10_109\n\t"
      "cmpw $0, -0x8(%%ebp)\n\t"
      "jle .LFUN_00025c10_109\n\t"
      "movzwl -0x8(%%ebp), %%eax\n\t"
      "leal -0x888c(%%ebp), %%edx\n\t"
      "movl %%eax, -0x24(%%ebp)\n\t"
      ".LFUN_00025c10_108:\n\t"
      "movswl (%%edx), %%eax\n\t"
      "shll $6, %%eax\n\t"
      "movb $1, 0x62a3b5(%%eax)\n\t"
      "leal 0x62a3b8(%%eax), %%edi\n\t"
      "movl -0x24(%%ebp), %%eax\n\t"
      "leal -0x4(%%edx), %%esi\n\t"
      "addl $0x3c, %%edx\n\t"
      "movl $0xf, %%ecx\n\t"
      "decl %%eax\n\t"
      "rep movsl\n\t"
      "movl %%eax, -0x24(%%ebp)\n\t"
      "jne .LFUN_00025c10_108\n\t"
      ".LFUN_00025c10_109:\n\t"
      "movb 0x5aca4e, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00025c10_110\n\t"
      "movswl 0x66e(%%ebx), %%ecx\n\t"
      "movswl 0x66c(%%ebx), %%edx\n\t"
      "movswl 0x66a(%%ebx), %%eax\n\t"
      "pushl %%ecx\n\t"
      "movswl 0x668(%%ebx), %%ecx\n\t"
      "pushl %%edx\n\t"
      "movswl 0x666(%%ebx), %%edx\n\t"
      "pushl %%eax\n\t"
      "movswl 0x664(%%ebx), %%eax\n\t"
      "pushl %%ecx\n\t"
      "movswl 0x4(%%ebx), %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "movl $0x25436c, -0x48(%%ebp)\n\t"
      "movl $0x253b1c, -0x44(%%ebp)\n\t"
      "movl $0x254f54, -0x40(%%ebp)\n\t"
      "movl $0x25435c, -0x3c(%%ebp)\n\t"
      "movl $0x254354, -0x38(%%ebp)\n\t"
      "movl $0x254f4c, -0x34(%%ebp)\n\t"
      "movl -0x48(%%ebp,%%ecx,4), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x254ef0\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $0x24, %%esp\n\t"
      ".LFUN_00025c10_110:\n\t"
      "movl -0x30(%%ebp), %%eax\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .LFUN_00025c10_62\n\t"
      "movl 0x10(%%ebp), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "je .LFUN_00025c10_111\n\t"
      "movswl %%ax, %%esi\n\t"
      "imull $0x3c, %%esi, %%esi\n\t"
      "leal -0x8890(%%ebp,%%esi,1), %%esi\n\t"
      "movl $0xf, %%ecx\n\t"
      "rep movsl\n\t"
      ".LFUN_00025c10_111:\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      "movswl %%ax, %%eax\n\t"
      "imull $0x3c, %%eax, %%eax\n\t"
      "testl %%ecx, %%ecx\n\t"
      "movw -0x888c(%%ebp,%%eax,1), %%ax\n\t"
      "je .LFUN_00025c10_62\n\t"
      "movswl %%ax, %%edx\n\t"
      "movl -0x890(%%ebp,%%edx,4), %%edx\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%edx, (%%ecx)\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_00025c10_jt:\n\t"
      ".long .LFUN_00025c10_36\n\t"
      ".long .LFUN_00025c10_45\n\t"
      ".text\n\t"
      :
      : [chkstk] "m"(b25c10_chkstk), [dget] "m"(b25c10_dget), [tag] "m"(b25c10_tag), [c18e380] "m"(b25c10_c18e380), [elem] "m"(b25c10_elem), [assert] "m"(b25c10_assert), [exitfn] "m"(b25c10_exitfn), [c5b4b0] "m"(b25c10_c5b4b0), [c1a93e0] "m"(b25c10_c1a93e0), [c2f910] "m"(b25c10_c2f910), [c64540] "m"(b25c10_c64540), [c64570] "m"(b25c10_c64570), [c309d0] "m"(b25c10_c309d0), [c1a9900] "m"(b25c10_c1a9900), [c25a00] "m"(b25c10_c25a00), [c8f390] "m"(b25c10_c8f390), [c18e3c0] "m"(b25c10_c18e3c0), [c5e830] "m"(b25c10_c5e830), [norm] "m"(b25c10_norm), [c5dfc0] "m"(b25c10_c5dfc0), [c5e000] "m"(b25c10_c5e000), [c5e070] "m"(b25c10_c5e070), [c5e090] "m"(b25c10_c5e090), [c5ff70] "m"(b25c10_c5ff70), [c5f550] "m"(b25c10_c5f550), [c2a470] "m"(b25c10_c2a470), [c5e030] "m"(b25c10_c5e030), [c49120] "m"(b25c10_c49120), [c10cd40] "m"(b25c10_c10cd40), [gseed] "m"(b25c10_gseed), [c10b2d0] "m"(b25c10_c10b2d0), [c25970] "m"(b25c10_c25970), [c91ef0] "m"(b25c10_c91ef0), [c24900] "m"(b25c10_c24900), [cfff80] "m"(b25c10_cfff80), [c257a0] "m"(b25c10_c257a0), [c24890] "m"(b25c10_c24890)
      : "memory");
}
#else
#error "FUN_00025c10: clang naked draft required"
#endif


/* FUN_00027090 (0x27090) — XBE naked draft (batch 69). */
#if defined(__clang__)
static void *(*const b27090_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static int (*const b27090_c24a60)(int actor_handle, short param_2, int param_3) = actor_get_firing_position_group;
static void (*const b27090_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b27090_exitfn)(int) = system_exit;
static short (*const b27090_c25c10)(int actor_handle, void *eval_ctx, int *out_record, int *out_owner, void *huge_buf, int *out_found) = FUN_00025c10;
static scenario_t * (*const b27090_c18e380)(void) = global_scenario_get;
static void *(*const b27090_elem)(void *, int, int) = tag_block_get_element;
static float (*const b27090_c121a0)(const float *a, const float *b) = distance_squared3d;
static char (*const b27090_c25970)(void *state, int actor_handle, char *actor) = FUN_00025970;

__attribute__((naked, noinline))
short FUN_00027090(int actor_handle __attribute__((unused)), void *param_2 __attribute__((unused)), void *param_3 __attribute__((unused)), void *param_4 __attribute__((unused)), void *param_5 __attribute__((unused)), void *param_6 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xc, %%esp\n\t"
      "movl 0x6325a4, %%eax\n\t"
      "pushl %%ebx\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl 0x34(%%eax), %%edx\n\t"
      "orl $0xffffffff, %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "cmpl %%ecx, %%edx\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "je .LFUN_00027090_11\n\t"
      "pushl %%esi\n\t"
      "movl 0xc(%%ebp), %%esi\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x4(%%esi), %%cx\n\t"
      "pushl %%edi\n\t"
      "pushl $0\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "call *%[c24a60]\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x4(%%esi), %%dx\n\t"
      "pushl $2\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "pushl %%edx\n\t"
      "pushl %%ebx\n\t"
      "call *%[c24a60]\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x4(%%esi), %%ax\n\t"
      "pushl $1\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "call *%[c24a60]\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "movl %%eax, %%edi\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "orl %%edx, %%edi\n\t"
      "addl $0x24, %%esp\n\t"
      "cmpl %%eax, %%edi\n\t"
      "jbe .LFUN_00027090_2\n\t"
      "movl %%edi, %%ecx\n\t"
      "andl %%eax, %%ecx\n\t"
      "cmpl %%eax, %%ecx\n\t"
      "movl %%eax, 0x48(%%esi)\n\t"
      "movl $0x41000000, 0x4c(%%esi)\n\t"
      "je .LFUN_00027090_1\n\t"
      "pushl $1\n\t"
      "pushl $0x907\n\t"
      "pushl $0x254c8c\n\t"
      "pushl $0x255008\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00027090_1:\n\t"
      "movl %%edi, (%%esi)\n\t"
      "jmp .LFUN_00027090_3\n\t"
      ".LFUN_00027090_2:\n\t"
      "movl %%eax, (%%esi)\n\t"
      ".LFUN_00027090_3:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "cmpw $-1, 0x3b8(%%eax)\n\t"
      "je .LFUN_00027090_4\n\t"
      "movb 0x3ba(%%eax), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "je .LFUN_00027090_4\n\t"
      "movb $0, 0x15(%%esi)\n\t"
      "jmp .LFUN_00027090_5\n\t"
      ".LFUN_00027090_4:\n\t"
      "movb $1, 0x15(%%esi)\n\t"
      ".LFUN_00027090_5:\n\t"
      "movl 0x1c(%%ebp), %%edx\n\t"
      "movl 0x18(%%ebp), %%eax\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      "movl 0x10(%%ebp), %%edi\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edi\n\t"
      "pushl %%esi\n\t"
      "pushl %%ebx\n\t"
      "movb $1, 0x14(%%esi)\n\t"
      "call *%[c25c10]\n\t"
      "addl $0x18, %%esp\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "je .LFUN_00027090_7\n\t"
      "movl (%%edi), %%edx\n\t"
      "movb 0xc(%%edx), %%cl\n\t"
      "movl $1, %%esi\n\t"
      "shll %%cl, %%esi\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "testl %%esi, %%ecx\n\t"
      "jne .LFUN_00027090_6\n\t"
      "movl 0x6325a4, %%edx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edx\n\t"
      "call *%[dget]\n\t"
      "movb 0x98(%%eax), %%cl\n\t"
      "addl $8, %%esp\n\t"
      "testb %%cl, %%cl\n\t"
      "sete %%cl\n\t"
      "movb %%cl, 0x98(%%eax)\n\t"
      "movw -0xc(%%ebp), %%ax\n\t"
      ".LFUN_00027090_6:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00027090_7:\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "movw 0x3b8(%%ecx), %%bx\n\t"
      "cmpw $-1, %%bx\n\t"
      "je .LFUN_00027090_6\n\t"
      "movb 0x3ba(%%ecx), %%dl\n\t"
      "testb %%dl, %%dl\n\t"
      "je .LFUN_00027090_6\n\t"
      "movl %%ecx, %%edx\n\t"
      "movl 0x34(%%edx), %%eax\n\t"
      "andl $0xffff, %%eax\n\t"
      "pushl $0xb0\n\t"
      "pushl %%eax\n\t"
      "call *%[c18e380]\n\t"
      "addl $0x42c, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movswl %%bx, %%ecx\n\t"
      "pushl $0x18\n\t"
      "pushl %%ecx\n\t"
      "addl $0x98, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl %%eax, (%%edi)\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "movw %%bx, 0x4(%%edi)\n\t"
      "movw $0, 0x6(%%edi)\n\t"
      "movl $0x7f7fffff, %%eax\n\t"
      "movl %%eax, 0x8(%%edi)\n\t"
      "movl %%eax, 0x18(%%edi)\n\t"
      "movl %%eax, 0x1c(%%edi)\n\t"
      "movl 0x31fc38, %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "leal 0x20(%%edi), %%edx\n\t"
      "movl %%ecx, (%%edx)\n\t"
      "movl 0x4(%%eax), %%ecx\n\t"
      "movl %%ecx, 0x4(%%edx)\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl %%eax, 0x8(%%edx)\n\t"
      "movl 0x31fc38, %%edx\n\t"
      "movl (%%edx), %%eax\n\t"
      "leal 0xc(%%edi), %%ecx\n\t"
      "movl %%eax, (%%ecx)\n\t"
      "movl 0x4(%%edx), %%eax\n\t"
      "movl %%eax, 0x4(%%ecx)\n\t"
      "movl 0x8(%%edx), %%edx\n\t"
      "movl %%edx, 0x8(%%ecx)\n\t"
      "movb 0x5fc(%%esi), %%al\n\t"
      "addl $0x18, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00027090_8\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal 0x604(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c121a0]\n\t"
      "fstps 0x2c(%%edi)\n\t"
      "addl $8, %%esp\n\t"
      "jmp .LFUN_00027090_9\n\t"
      ".LFUN_00027090_8:\n\t"
      "movl $0, 0x2c(%%edi)\n\t"
      ".LFUN_00027090_9:\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl %%edi, %%eax\n\t"
      "call *%[c25970]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00027090_10\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "orl $0xffffffff, %%ebx\n\t"
      "movw %%bx, 0x3b8(%%eax)\n\t"
      ".LFUN_00027090_10:\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      "movl 0x1c(%%ebp), %%edx\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl $0xffffffff, (%%ecx)\n\t"
      "movw %%bx, %%ax\n\t"
      "movb $0, (%%edx)\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00027090_11:\n\t"
      "movw %%cx, %%ax\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [dget] "m"(b27090_dget), [c24a60] "m"(b27090_c24a60), [assert] "m"(b27090_assert), [exitfn] "m"(b27090_exitfn), [c25c10] "m"(b27090_c25c10), [c18e380] "m"(b27090_c18e380), [elem] "m"(b27090_elem), [c121a0] "m"(b27090_c121a0), [c25970] "m"(b27090_c25970)
      : "memory");
}
#else
#error "FUN_00027090: clang naked draft required"
#endif


/* FUN_000272d0 (0x272d0) — XBE naked draft (batch 69). */
#if defined(__clang__)
static void *(*const b272d0_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void (*const b272d0_c2f1a0)(int actor_handle) = FUN_0002f1a0;
static void (*const b272d0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b272d0_exitfn)(int) = system_exit;
static void (*const b272d0_c24be0)(int actor_handle, short param_2, char param_3) = FUN_00024be0;
static char (*const b272d0_c2d900)(int actor_handle, int16_t param_2, void *param_3) = actor_move_to_firing_position;
static void (*const b272d0_c5b370)(int encounter_handle) = encounter_verify_firing_position_owner_actor_indices;

__attribute__((naked, noinline))
short FUN_000272d0(int actor_handle __attribute__((unused)), short param_2 __attribute__((unused)), void *param_3 __attribute__((unused)), int param_4 __attribute__((unused)), unsigned int param_5 __attribute__((unused)), char param_6 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "movl 0x6325a4, %%eax\n\t"
      "pushl %%ebx\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $-1, %%di\n\t"
      "movl %%eax, %%esi\n\t"
      "jne .LFUN_000272d0_1\n\t"
      "pushl %%ebx\n\t"
      "call *%[c2f1a0]\n\t"
      "addl $4, %%esp\n\t"
      "jmp .LFUN_000272d0_6\n\t"
      ".LFUN_000272d0_1:\n\t"
      "cmpl $-1, 0x34(%%esi)\n\t"
      "jne .LFUN_000272d0_2\n\t"
      "pushl $1\n\t"
      "pushl $0x97b\n\t"
      "pushl $0x254c8c\n\t"
      "pushl $0x255070\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000272d0_2:\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x3b8(%%esi), %%ax\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .LFUN_000272d0_3\n\t"
      "cmpw %%di, %%ax\n\t"
      "je .LFUN_000272d0_3\n\t"
      "pushl $1\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "call *%[c24be0]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_000272d0_3:\n\t"
      "movl 0x14(%%ebp), %%edi\n\t"
      "cmpl $-1, %%edi\n\t"
      "je .LFUN_000272d0_5\n\t"
      "movl 0x6325a4, %%ecx\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "addl $8, %%esp\n\t"
      "cmpl %%edi, %%ebx\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "jne .LFUN_000272d0_4\n\t"
      "pushl $1\n\t"
      "pushl $0x988\n\t"
      "pushl $0x254c8c\n\t"
      "pushl $0x255050\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000272d0_4:\n\t"
      "pushl %%edi\n\t"
      "call *%[c2f1a0]\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "addl $4, %%esp\n\t"
      "movw $0xffff, 0x3b8(%%edx)\n\t"
      ".LFUN_000272d0_5:\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "cmpw %%di, 0x3b8(%%esi)\n\t"
      "je .LFUN_000272d0_7\n\t"
      "movb 0x1c(%%ebp), %%al\n\t"
      "movl 0x18(%%ebp), %%edx\n\t"
      "testb %%al, %%al\n\t"
      "sete %%cl\n\t"
      "negb %%al\n\t"
      "movw %%di, 0x3b8(%%esi)\n\t"
      "movb %%cl, 0x3ba(%%esi)\n\t"
      "movb $0, 0x3bb(%%esi)\n\t"
      "sbbl %%eax, %%eax\n\t"
      "andl %%edx, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "call *%[c2d900]\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_000272d0_7\n\t"
      ".LFUN_000272d0_6:\n\t"
      "movw $0xffff, 0x3b8(%%esi)\n\t"
      ".LFUN_000272d0_7:\n\t"
      "movl 0x34(%%esi), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_000272d0_8\n\t"
      "pushl %%eax\n\t"
      "call *%[c5b370]\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_000272d0_8:\n\t"
      "movw 0x3b8(%%esi), %%ax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [dget] "m"(b272d0_dget), [c2f1a0] "m"(b272d0_c2f1a0), [assert] "m"(b272d0_assert), [exitfn] "m"(b272d0_exitfn), [c24be0] "m"(b272d0_c24be0), [c2d900] "m"(b272d0_c2d900), [c5b370] "m"(b272d0_c5b370)
      : "memory");
}
#else
#error "FUN_000272d0: clang naked draft required"
#endif


/* FUN_00027410 (0x27410) — XBE naked draft (batch 69). */
#if defined(__clang__)
static void *(*const b27410_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static char * (*const b27410_c211f0)(int actor_handle) = actor_combat_get_firing_variant_definition;
static void (*const b27410_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b27410_exitfn)(int) = system_exit;
static char * (*const b27410_c210f0)(int actor_handle) = FUN_000210f0;
static void (*const b27410_c24000)(void *ctx, float score, int type, void *position) = (void *)FUN_00024000;
static char * (*const b27410_c8d9d0)(char *buffer, const char *format, ...) = csprintf;

__attribute__((naked, noinline))
void FUN_00027410(int actor_handle __attribute__((unused)), void *ctx __attribute__((unused)), unsigned short fp_count __attribute__((unused)), void *fp_array __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x34, %%esp\n\t"
      "movl 0x6325a4, %%eax\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "pushl %%esi\n\t"
      "movl %%eax, -0x28(%%ebp)\n\t"
      "call *%[c211f0]\n\t"
      "movl %%eax, %%edx\n\t"
      "movw 0x10(%%ebp), %%ax\n\t"
      "addl $0xc, %%esp\n\t"
      "testw %%ax, %%ax\n\t"
      "movl %%edx, -0x14(%%ebp)\n\t"
      "jle .LFUN_00027410_26\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      "movzwl %%ax, %%eax\n\t"
      "pushl %%ebx\n\t"
      "movl 0xc(%%ebp), %%ebx\n\t"
      "addl $0x38, %%ecx\n\t"
      "pushl %%edi\n\t"
      "movl %%ecx, 0x14(%%ebp)\n\t"
      "movl %%eax, -0x24(%%ebp)\n\t"
      "jmp .LFUN_00027410_2\n\t"
      ".LFUN_00027410_1:\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".LFUN_00027410_2:\n\t"
      "movb -0x8(%%ecx), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00027410_25\n\t"
      "movb 0x5fc(%%ebx), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00027410_15\n\t"
      "flds -0xc(%%ecx)\n\t"
      "fsqrt\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "flds 0x74(%%edx)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00027410_6\n\t"
      "flds 0x74(%%edx)\n\t"
      "fmuls 0x2533f0\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fcomp %%st(1)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00027410_3\n\t"
      "fstp %%st(0)\n\t"
      "movl $0x41200000, -0xc(%%ebp)\n\t"
      "jmp .LFUN_00027410_5\n\t"
      ".LFUN_00027410_3:\n\t"
      "fdivs -0x4(%%ebp)\n\t"
      "fmuls 0x253f34\n\t"
      "fsts -0xc(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_00027410_4\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fcomps 0x254cb8\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .LFUN_00027410_5\n\t"
      ".LFUN_00027410_4:\n\t"
      "pushl $1\n\t"
      "pushl $0x81\n\t"
      "pushl $0x254c8c\n\t"
      "pushl $0x254c5c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      "movl -0x14(%%ebp), %%edx\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00027410_5:\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fadds (%%ecx)\n\t"
      "fstps (%%ecx)\n\t"
      ".LFUN_00027410_6:\n\t"
      "flds 0xa0(%%edx)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00027410_15\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fcomps 0xa0(%%edx)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00027410_15\n\t"
      "movl -0x28(%%ebp), %%ecx\n\t"
      "movb 0x378(%%ecx), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00027410_7\n\t"
      "flds 0x168(%%edx)\n\t"
      "movl 0x16c(%%edx), %%edx\n\t"
      "movl %%edx, -0x20(%%ebp)\n\t"
      "jmp .LFUN_00027410_8\n\t"
      ".LFUN_00027410_7:\n\t"
      "movl 0xa0(%%edx), %%eax\n\t"
      "flds 0x9c(%%edx)\n\t"
      "movl %%eax, -0x20(%%ebp)\n\t"
      ".LFUN_00027410_8:\n\t"
      "fsts 0x10(%%ebp)\n\t"
      "fcomps 0x658(%%ebx)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .LFUN_00027410_9\n\t"
      "movl 0x658(%%ebx), %%ecx\n\t"
      "movl %%ecx, 0x10(%%ebp)\n\t"
      ".LFUN_00027410_9:\n\t"
      "pushl %%esi\n\t"
      "call *%[c210f0]\n\t"
      "movl %%eax, %%ecx\n\t"
      "addl $4, %%esp\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .LFUN_00027410_10\n\t"
      "flds 0x40c(%%ecx)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00027410_10\n\t"
      "flds 0x10(%%ebp)\n\t"
      "fcomps 0x40c(%%ecx)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .LFUN_00027410_10\n\t"
      "movl 0x40c(%%ecx), %%edx\n\t"
      "movl %%edx, 0x10(%%ebp)\n\t"
      ".LFUN_00027410_10:\n\t"
      "flds -0x20(%%ebp)\n\t"
      "fsubs -0x4(%%ebp)\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "flds 0x10(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00027410_12\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fsubs 0x10(%%ebp)\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fcomp %%st(1)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00027410_11\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "jmp .LFUN_00027410_12\n\t"
      ".LFUN_00027410_11:\n\t"
      "fstp %%st(0)\n\t"
      ".LFUN_00027410_12:\n\t"
      "flds -0x8(%%ebp)\n\t"
      "movl $0, -0x1c(%%ebp)\n\t"
      "fcomps 0x253f40\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00027410_13\n\t"
      "movl $0x41a00000, -0x1c(%%ebp)\n\t"
      "jmp .LFUN_00027410_14\n\t"
      ".LFUN_00027410_13:\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00027410_14\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fmuls 0x253398\n\t"
      "fmuls 0x254cd0\n\t"
      "fstps -0x1c(%%ebp)\n\t"
      ".LFUN_00027410_14:\n\t"
      "movl -0x1c(%%ebp), %%eax\n\t"
      "movl 0x14(%%ebp), %%esi\n\t"
      "pushl $0xd\n\t"
      "pushl %%eax\n\t"
      "addl $-0x38, %%esi\n\t"
      "pushl %%ebx\n\t"
      "call *%[c24000]\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      "movl -0x14(%%ebp), %%edx\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_00027410_15:\n\t"
      "cmpw $0, 0x258(%%ebx)\n\t"
      "jle .LFUN_00027410_25\n\t"
      "xorl %%edi, %%edi\n\t"
      "cmpw %%di, 0x254(%%ebx)\n\t"
      "movl $0x7f7fffff, -0x10(%%ebp)\n\t"
      "jle .LFUN_00027410_22\n\t"
      "jmp .LFUN_00027410_16\n\t"
      "leal (%%esp), %%esp\n\t"
      "nop\n\t"
      ".LFUN_00027410_16:\n\t"
      "movswl %%di, %%eax\n\t"
      "imull $0x1c, %%eax, %%eax\n\t"
      "cmpw $2, 0x25c(%%eax,%%ebx,1)\n\t"
      "leal (%%eax,%%ebx,1), %%esi\n\t"
      "jne .LFUN_00027410_21\n\t"
      "flds 0x274(%%esi)\n\t"
      "flds 0x270(%%esi)\n\t"
      "flds 0x26c(%%esi)\n\t"
      "fld %%st(0)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fld %%st(2)\n\t"
      ".byte 0xd8, 0xcb\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fld %%st(3)\n\t"
      ".byte 0xd8, 0xcc\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fsubs 0x2533c8\n\t"
      "fstp %%st(3)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "fsts 0x10(%%ebp)\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "andl $0x7f800000, %%eax\n\t"
      "cmpl $0x7f800000, %%eax\n\t"
      "je .LFUN_00027410_17\n\t"
      "fabs\n\t"
      "fcompl 0x2549d8\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .LFUN_00027410_19\n\t"
      "jmp .LFUN_00027410_18\n\t"
      ".LFUN_00027410_17:\n\t"
      "fstp %%st(0)\n\t"
      ".LFUN_00027410_18:\n\t"
      "flds 0x274(%%esi)\n\t"
      "pushl $1\n\t"
      "pushl $0x291\n\t"
      "pushl $0x254c8c\n\t"
      "subl $0x18, %%esp\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds 0x270(%%esi)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds 0x26c(%%esi)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x255098\n\t"
      "pushl $0x254a24\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x24, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      "movl -0x14(%%ebp), %%edx\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00027410_19:\n\t"
      "movl -0x38(%%ecx), %%eax\n\t"
      "flds (%%eax)\n\t"
      "fsubs 0x260(%%esi)\n\t"
      "fstps -0x34(%%ebp)\n\t"
      "flds 0x4(%%eax)\n\t"
      "fsubs 0x264(%%esi)\n\t"
      "fstps -0x30(%%ebp)\n\t"
      "flds 0x8(%%eax)\n\t"
      "fsubs 0x268(%%esi)\n\t"
      "fstps -0x2c(%%ebp)\n\t"
      "flds -0x30(%%ebp)\n\t"
      "fmuls 0x270(%%esi)\n\t"
      "flds -0x2c(%%ebp)\n\t"
      "fmuls 0x274(%%esi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds -0x34(%%ebp)\n\t"
      "fmuls 0x26c(%%esi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fcoms 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00027410_20\n\t"
      "fchs\n\t"
      "fld %%st(0)\n\t"
      "fmuls 0x26c(%%esi)\n\t"
      "fadds -0x34(%%ebp)\n\t"
      "fld %%st(1)\n\t"
      "fmuls 0x270(%%esi)\n\t"
      "fadds -0x30(%%ebp)\n\t"
      "fxch %%st(2)\n\t"
      "fmuls 0x274(%%esi)\n\t"
      "fadds -0x2c(%%ebp)\n\t"
      "fld %%st(2)\n\t"
      ".byte 0xd8, 0xcb\n\t"
      "fld %%st(1)\n\t"
      ".byte 0xd8, 0xca\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fld %%st(2)\n\t"
      ".byte 0xd8, 0xcb\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fxch %%st(3)\n\t"
      "fstp %%st(1)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "fcoms -0x10(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00027410_20\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "jmp .LFUN_00027410_21\n\t"
      ".LFUN_00027410_20:\n\t"
      "fstp %%st(0)\n\t"
      ".LFUN_00027410_21:\n\t"
      "incl %%edi\n\t"
      "cmpw 0x254(%%ebx), %%di\n\t"
      "jl .LFUN_00027410_16\n\t"
      ".LFUN_00027410_22:\n\t"
      "flds -0x10(%%ebp)\n\t"
      "movl $0x40c00000, -0x18(%%ebp)\n\t"
      "fcomps 0x255094\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00027410_24\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fsqrt\n\t"
      "fmuls 0x25337c\n\t"
      "fsts -0x18(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_00027410_23\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fcomps 0x254cb8\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .LFUN_00027410_24\n\t"
      ".LFUN_00027410_23:\n\t"
      "pushl $1\n\t"
      "pushl $0x81\n\t"
      "pushl $0x254c8c\n\t"
      "pushl $0x254c5c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      "movl -0x14(%%ebp), %%edx\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00027410_24:\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fadds (%%ecx)\n\t"
      "fstps (%%ecx)\n\t"
      ".LFUN_00027410_25:\n\t"
      "movl -0x24(%%ebp), %%eax\n\t"
      "addl $0x3c, %%ecx\n\t"
      "decl %%eax\n\t"
      "movl %%ecx, 0x14(%%ebp)\n\t"
      "movl %%eax, -0x24(%%ebp)\n\t"
      "jne .LFUN_00027410_1\n\t"
      "popl %%edi\n\t"
      "popl %%ebx\n\t"
      ".LFUN_00027410_26:\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [dget] "m"(b27410_dget), [c211f0] "m"(b27410_c211f0), [assert] "m"(b27410_assert), [exitfn] "m"(b27410_exitfn), [c210f0] "m"(b27410_c210f0), [c24000] "m"(b27410_c24000), [c8d9d0] "m"(b27410_c8d9d0)
      : "memory");
}
#else
#error "FUN_00027410: clang naked draft required"
#endif


/* FUN_00027870 (0x27870) — readable C lift from XBE leaf. */
void FUN_00027870(int actor_handle)
{
  void *actor;
  char *desc;

  actor = datum_get(*(void **)0x6325a4, actor_handle);
  if (*(short *)((char *)actor + 0x544) > 0 && *(unsigned char *)0x5aca5d != 0) {
    desc = ai_debug_describe_actor(actor_handle, -1, 0, (char *)0x5ab100, 0x100);
    console_printf(0, (const char *)0x255144, desc);
  }
  *(short *)((char *)actor + 0x546) = 0;
  *(short *)((char *)actor + 0x544) = 0;
  *(short *)((char *)actor + 0x548) = 0;
}




/* FUN_000278e0 (0x278e0) — XBE naked draft (batch 75). */
#if defined(__clang__)
static void *(*const b278e0_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void *(*const b278e0_tag)(int, int) = tag_get;

__attribute__((naked, noinline))
float FUN_000278e0(int actor_handle __attribute__((unused)), int prop_handle __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl 0x6325a4, %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x5ab23c, %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "flds 0x2533c0\n\t"
      "movw 0x24(%%eax), %%cx\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpw $2, %%cx\n\t"
      "jl .LFUN_000278e0_4\n\t"
      "cmpw $3, %%cx\n\t"
      "jg .LFUN_000278e0_4\n\t"
      "movb 0x127(%%eax), %%cl\n\t"
      "fstp %%st(0)\n\t"
      "testb %%cl, %%cl\n\t"
      "je .LFUN_000278e0_2\n\t"
      "cmpw $0xd2, 0x76(%%eax)\n\t"
      "jge .LFUN_000278e0_1\n\t"
      "flds 0x255154\n\t"
      "jmp .LFUN_000278e0_5\n\t"
      ".LFUN_000278e0_1:\n\t"
      "flds 0x253524\n\t"
      "jmp .LFUN_000278e0_5\n\t"
      ".LFUN_000278e0_2:\n\t"
      "movb 0x60(%%eax), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "je .LFUN_000278e0_3\n\t"
      "flds 0x253f40\n\t"
      "jmp .LFUN_000278e0_5\n\t"
      ".LFUN_000278e0_3:\n\t"
      "flds 0x2533c8\n\t"
      "jmp .LFUN_000278e0_5\n\t"
      ".LFUN_000278e0_4:\n\t"
      "movb 0x60(%%eax), %%dl\n\t"
      "testb %%dl, %%dl\n\t"
      "je .LFUN_000278e0_5\n\t"
      "cmpw $4, %%cx\n\t"
      "jl .LFUN_000278e0_5\n\t"
      "cmpw $5, %%cx\n\t"
      "jg .LFUN_000278e0_5\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533ec\n\t"
      ".LFUN_000278e0_5:\n\t"
      "movl 0x158(%%esi), %%ecx\n\t"
      "cmpl %%ecx, 0x18(%%eax)\n\t"
      "popl %%esi\n\t"
      "je .LFUN_000278e0_6\n\t"
      "cmpl %%ecx, 0x110(%%eax)\n\t"
      "jne .LFUN_000278e0_7\n\t"
      ".LFUN_000278e0_6:\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c0\n\t"
      ".LFUN_000278e0_7:\n\t"
      "cmpl $-1, 0x110(%%eax)\n\t"
      "je .LFUN_000278e0_8\n\t"
      "flds 0x2533ec\n\t"
      "jmp .LFUN_000278e0_9\n\t"
      ".LFUN_000278e0_8:\n\t"
      "flds 0x2533c8\n\t"
      ".LFUN_000278e0_9:\n\t"
      "movsbl 0x123(%%eax), %%ecx\n\t"
      "decl %%ecx\n\t"
      "je .LFUN_000278e0_11\n\t"
      "decl %%ecx\n\t"
      "je .LFUN_000278e0_10\n\t"
      "decl %%ecx\n\t"
      "jne .LFUN_000278e0_13\n\t"
      "fld %%st(0)\n\t"
      ".byte 0xd8, 0xc1\n\t"
      "jmp .LFUN_000278e0_12\n\t"
      ".LFUN_000278e0_10:\n\t"
      "fld %%st(0)\n\t"
      "jmp .LFUN_000278e0_12\n\t"
      ".LFUN_000278e0_11:\n\t"
      "flds 0x253398\n\t"
      ".byte 0xd8, 0xc9\n\t"
      ".LFUN_000278e0_12:\n\t"
      ".byte 0xde, 0xc2\n\t"
      ".LFUN_000278e0_13:\n\t"
      "movb 0x12f(%%eax), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "je .LFUN_000278e0_14\n\t"
      ".byte 0xdc, 0xc0\n\t"
      ".byte 0xde, 0xc1\n\t"
      "jmp .LFUN_000278e0_15\n\t"
      ".LFUN_000278e0_14:\n\t"
      "fstp %%st(0)\n\t"
      ".LFUN_000278e0_15:\n\t"
      "movsbl 0x121(%%eax), %%eax\n\t"
      "decl %%eax\n\t"
      "je .LFUN_000278e0_17\n\t"
      "subl $2, %%eax\n\t"
      "je .LFUN_000278e0_16\n\t"
      "decl %%eax\n\t"
      "jne .LFUN_000278e0_18\n\t"
      "fmuls 0x2549d4\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000278e0_16:\n\t"
      "fmuls 0x253524\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000278e0_17:\n\t"
      "fmuls 0x253f3c\n\t"
      ".LFUN_000278e0_18:\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "movl 0x6325a4, %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x58(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x61637472\n\t"
      "call *%[tag]\n\t"
      "movswl 0x3fc(%%esi), %%ecx\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpl $2, %%ecx\n\t"
      "popl %%esi\n\t"
      "je .LFUN_000278e0_20\n\t"
      "jle .LFUN_000278e0_19\n\t"
      "cmpl $4, %%ecx\n\t"
      "jg .LFUN_000278e0_19\n\t"
      "addl $0x10c, %%eax\n\t"
      "ret\n\t"
      ".LFUN_000278e0_19:\n\t"
      "addl $0xdc, %%eax\n\t"
      "ret\n\t"
      ".LFUN_000278e0_20:\n\t"
      "addl $0xf4, %%eax\n\t"
      "ret\n\t"
      :
      : [dget] "m"(b278e0_dget), [tag] "m"(b278e0_tag)
      : "memory");
}
#else
#error "FUN_000278e0: clang naked draft required"
#endif


/* FUN_00027a10 (0x27a10) — readable C lift. */
int FUN_00027a10(int actor_handle)
{
  char *actor;
  char *tag;
  int type;

  actor = (char *)datum_get(*(void **)0x6325a4, actor_handle);
  tag = (char *)tag_get(0x61637472, *(int *)(actor + 0x58));
  type = *(short *)(actor + 0x3fc);
  if (type == 2)
    return (int)(tag + 0xf4);
  if (type > 2 && type <= 4)
    return (int)(tag + 0x10c);
  return (int)(tag + 0xdc);
}

/* FUN_00027a60 (0x27a60) — XBE naked draft (batch 75). */
#if defined(__clang__)
static void *(*const b27a60_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void *(*const b27a60_tag)(int, int) = tag_get;
static void (*const b27a60_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b27a60_exitfn)(int) = system_exit;
static int (*const b27a60_c119270)(data_t *data, int absolute_index) = datum_absolute_index_to_index;
static int (*const b27a60_gtime)(void) = game_time_get;
static int *(*const b27a60_gseed)(void) = get_global_random_seed_address;
static float (*const b27a60_rrange)(int *, float, float) = random_real_range;
static char * (*const b27a60_c49ac0)(int actor_handle, int object_handle, char with_actor, char *buf, int buf_size) = ai_debug_describe_actor;
static void (*const b27a60_cff4d0)(int channel, const char *format, ...) = console_printf;

__attribute__((naked, noinline))
int FUN_00027a60(int actor_handle __attribute__((unused)), short look_type __attribute__((unused)), short priority __attribute__((unused)), short *look_buf __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x64, %%esp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl 0x6325a4, %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x58(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x61637472\n\t"
      "call *%[tag]\n\t"
      "movw 0xc(%%ebp), %%bx\n\t"
      "addl $0x10, %%esp\n\t"
      "testw %%bx, %%bx\n\t"
      "movl %%eax, %%edi\n\t"
      "movl %%edi, -0x8(%%ebp)\n\t"
      "jl .LFUN_00027a60_1\n\t"
      "cmpw $0xe, %%bx\n\t"
      "jl .LFUN_00027a60_2\n\t"
      ".LFUN_00027a60_1:\n\t"
      "pushl $1\n\t"
      "pushl $0x87\n\t"
      "pushl $0x255284\n\t"
      "pushl $0x25524c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00027a60_2:\n\t"
      "cmpw $1, 0x6a(%%esi)\n\t"
      "jg .LFUN_00027a60_3\n\t"
      "cmpw $0xd, %%bx\n\t"
      "jl .LFUN_00027a60_9\n\t"
      ".LFUN_00027a60_3:\n\t"
      "cmpw %%bx, 0x544(%%esi)\n\t"
      "jg .LFUN_00027a60_9\n\t"
      "cmpw $7, 0x3e8(%%esi)\n\t"
      "setge %%al\n\t"
      "cmpw $0xd, %%bx\n\t"
      "movb %%al, -0x1(%%ebp)\n\t"
      "jge .LFUN_00027a60_4\n\t"
      "cmpw $0xb, 0x6c(%%esi)\n\t"
      "jne .LFUN_00027a60_4\n\t"
      "movb 0x9f(%%esi), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "je .LFUN_00027a60_9\n\t"
      ".LFUN_00027a60_4:\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00027a60_5\n\t"
      "cmpw $4, %%bx\n\t"
      "jl .LFUN_00027a60_9\n\t"
      ".LFUN_00027a60_5:\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "cmpw $1, (%%eax)\n\t"
      "jne .LFUN_00027a60_14\n\t"
      "movl 0x4(%%eax), %%eax\n\t"
      "movl 0x5ab23c, %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c119270]\n\t"
      "movl %%eax, %%edi\n\t"
      "addl $8, %%esp\n\t"
      "testl %%edi, %%edi\n\t"
      "je .LFUN_00027a60_9\n\t"
      "cmpw $8, %%bx\n\t"
      "jge .LFUN_00027a60_13\n\t"
      "movb 0x60(%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00027a60_6\n\t"
      "movb 0x127(%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00027a60_7\n\t"
      ".LFUN_00027a60_6:\n\t"
      "movb 0x127(%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00027a60_13\n\t"
      "cmpw $3, 0x6a(%%esi)\n\t"
      "jl .LFUN_00027a60_13\n\t"
      ".LFUN_00027a60_7:\n\t"
      "call *%[gtime]\n\t"
      "movb -0x1(%%ebp), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "jne .LFUN_00027a60_9\n\t"
      "movb 0x12e(%%edi), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "je .LFUN_00027a60_8\n\t"
      "cmpw $4, %%bx\n\t"
      "jge .LFUN_00027a60_10\n\t"
      ".LFUN_00027a60_8:\n\t"
      "movl 0x5c(%%edi), %%ecx\n\t"
      "cmpl $-1, %%ecx\n\t"
      "je .LFUN_00027a60_10\n\t"
      "addl $0x258, %%ecx\n\t"
      "cmpl %%eax, %%ecx\n\t"
      "jle .LFUN_00027a60_10\n\t"
      ".LFUN_00027a60_9:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00027a60_10:\n\t"
      "flds 0x58(%%edi)\n\t"
      "movl %%eax, 0x5c(%%edi)\n\t"
      "fcomps 0x54(%%edi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00027a60_11\n\t"
      "flds 0x58(%%edi)\n\t"
      "jmp .LFUN_00027a60_12\n\t"
      ".LFUN_00027a60_11:\n\t"
      "flds 0x54(%%edi)\n\t"
      ".LFUN_00027a60_12:\n\t"
      "fstps 0x58(%%edi)\n\t"
      ".LFUN_00027a60_13:\n\t"
      "movl -0x8(%%ebp), %%edi\n\t"
      ".LFUN_00027a60_14:\n\t"
      "cmpw $3, 0x6a(%%esi)\n\t"
      "movswl %%bx, %%eax\n\t"
      "flds 0x25510c(,%%eax,4)\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "jl .LFUN_00027a60_15\n\t"
      "cmpw $0, 0x6e(%%esi)\n\t"
      "jne .LFUN_00027a60_16\n\t"
      ".LFUN_00027a60_15:\n\t"
      "flds -0x8(%%ebp)\n\t"
      ".byte 0xdc, 0xc0\n\t"
      "fstps -0x8(%%ebp)\n\t"
      ".LFUN_00027a60_16:\n\t"
      "flds 0xd4(%%edi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .LFUN_00027a60_17\n\t"
      "flds 0xd8(%%edi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .LFUN_00027a60_22\n\t"
      ".LFUN_00027a60_17:\n\t"
      "flds 0xd4(%%edi)\n\t"
      "fcomps 0x253398\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00027a60_18\n\t"
      "movl 0xd4(%%edi), %%edx\n\t"
      "movl %%edx, -0x10(%%ebp)\n\t"
      "jmp .LFUN_00027a60_19\n\t"
      ".LFUN_00027a60_18:\n\t"
      "movl $0x3f000000, -0x10(%%ebp)\n\t"
      ".LFUN_00027a60_19:\n\t"
      "flds 0xd8(%%edi)\n\t"
      "fcomps 0x253f40\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00027a60_20\n\t"
      "movl $0x40000000, -0xc(%%ebp)\n\t"
      "jmp .LFUN_00027a60_21\n\t"
      ".LFUN_00027a60_20:\n\t"
      "movl 0xd8(%%edi), %%eax\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      ".LFUN_00027a60_21:\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "movl -0x10(%%ebp), %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[gseed]\n\t"
      "pushl %%eax\n\t"
      "call *%[rrange]\n\t"
      "fmuls -0x8(%%ebp)\n\t"
      "addl $0xc, %%esp\n\t"
      "fstps -0x8(%%ebp)\n\t"
      ".LFUN_00027a60_22:\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fmuls 0x253394\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fistps -0xc(%%ebp)\n\t"
      "movl -0xc(%%ebp), %%ebx\n\t"
      "cmpl $0x7fff, %%ebx\n\t"
      "jle .LFUN_00027a60_23\n\t"
      "movl $0x7fff, %%ebx\n\t"
      ".LFUN_00027a60_23:\n\t"
      "movl 0x10(%%ebp), %%edi\n\t"
      "cmpw $1, %%di\n\t"
      "jne .LFUN_00027a60_24\n\t"
      "cmpw $4, 0x6e(%%esi)\n\t"
      "setge %%al\n\t"
      "movzbl %%al, %%ecx\n\t"
      "movswl 0xc(%%ebp), %%eax\n\t"
      "leal (%%ecx,%%eax,2), %%edx\n\t"
      "movw 0x2550d4(,%%edx,2), %%di\n\t"
      ".LFUN_00027a60_24:\n\t"
      "movb 0x5aca5d, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00027a60_25\n\t"
      "movl $0x254384, %%eax\n\t"
      "movl %%eax, -0x34(%%ebp)\n\t"
      "movl %%eax, -0x64(%%ebp)\n\t"
      "movswl %%bx, %%eax\n\t"
      "pushl %%eax\n\t"
      "movswl 0xc(%%ebp), %%eax\n\t"
      "movswl %%di, %%ecx\n\t"
      "movl $0x255244, -0x30(%%ebp)\n\t"
      "movl $0x255238, -0x2c(%%ebp)\n\t"
      "movl $0x25522c, -0x28(%%ebp)\n\t"
      "movl $0x255228, -0x24(%%ebp)\n\t"
      "movl $0x255218, -0x20(%%ebp)\n\t"
      "movl $0x255208, -0x1c(%%ebp)\n\t"
      "movl $0x2551fc, -0x18(%%ebp)\n\t"
      "movl $0x2551ec, -0x14(%%ebp)\n\t"
      "movl -0x34(%%ebp,%%ecx,4), %%edx\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "pushl %%edx\n\t"
      "movl $0x2551e0, -0x60(%%ebp)\n\t"
      "movl $0x2551d4, -0x5c(%%ebp)\n\t"
      "movl $0x2551cc, -0x58(%%ebp)\n\t"
      "movl $0x2551c0, -0x54(%%ebp)\n\t"
      "movl $0x2551b0, -0x50(%%ebp)\n\t"
      "movl $0x2551a4, -0x4c(%%ebp)\n\t"
      "movl $0x255194, -0x48(%%ebp)\n\t"
      "movl $0x255188, -0x44(%%ebp)\n\t"
      "movl $0x255180, -0x40(%%ebp)\n\t"
      "movl $0x255178, -0x3c(%%ebp)\n\t"
      "movl $0x25516c, -0x38(%%ebp)\n\t"
      "movl -0x64(%%ebp,%%eax,4), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x100\n\t"
      "pushl $0x5ab100\n\t"
      "pushl $0\n\t"
      "pushl $-1\n\t"
      "pushl %%ecx\n\t"
      "call *%[c49ac0]\n\t"
      "addl $0x14, %%esp\n\t"
      "pushl %%eax\n\t"
      "pushl $0x255158\n\t"
      "pushl $0\n\t"
      "call *%[cff4d0]\n\t"
      "addl $0x18, %%esp\n\t"
      ".LFUN_00027a60_25:\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "movw 0xc(%%ebp), %%dx\n\t"
      "movw %%di, 0x546(%%esi)\n\t"
      "movw %%bx, 0x548(%%esi)\n\t"
      "movw %%dx, 0x544(%%esi)\n\t"
      "movl (%%eax), %%ecx\n\t"
      "addl $0x54c, %%esi\n\t"
      "movl %%ecx, (%%esi)\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl %%edx, 0x4(%%esi)\n\t"
      "movl 0x8(%%eax), %%ecx\n\t"
      "movl %%ecx, 0x8(%%esi)\n\t"
      "movl 0xc(%%eax), %%edx\n\t"
      "popl %%edi\n\t"
      "movl %%edx, 0xc(%%esi)\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [dget] "m"(b27a60_dget), [tag] "m"(b27a60_tag), [assert] "m"(b27a60_assert), [exitfn] "m"(b27a60_exitfn), [c119270] "m"(b27a60_c119270), [gtime] "m"(b27a60_gtime), [gseed] "m"(b27a60_gseed), [rrange] "m"(b27a60_rrange), [c49ac0] "m"(b27a60_c49ac0), [cff4d0] "m"(b27a60_cff4d0)
      : "memory");
}
#else
#error "FUN_00027a60: clang naked draft required"
#endif


/* FUN_00027dd0 (0x27dd0)
 * Returns true if the dot product of a normalized 2D direction vector
 * and a comparison direction exceeds a threshold.
 *
 * Confirmed: EAX=dir (float* 2D), EDX=vec2 (float* 2D), stack=threshold.
 *   Leaf function, no callee calls. FSQRT/FDIV/FMUL/FADDP/FCOMPP chain. */
bool FUN_00027dd0(float *dir, float *vec2, float threshold)
{
  float dx;
  float dy;
  float len;

  dx = dir[0];
  dy = dir[1];
  len = xbox_sqrtf(dx * dx + dy * dy);

  if (!(len >= 0.0001f))
    return 0;

  dx = (1.0f / len) * dx;
  dy = (1.0f / len) * dy;

  if (!(len > 0.0f))
    return 0;

  if (!(dx * vec2[0] + dy * vec2[1] > threshold))
    return 0;

  return 1;
}

/* FUN_00027e50 (0x27e50)
 * Vector normalization + dot/cross comparison against two thresholds.
 *
 * Confirmed: EAX=dir, ECX=vec2, EDX=limit, EBP+8=threshold,
 *   EBP+0xC=output.  FSQRT/FDIV/FMUL/FCOMPP + magnitude3d. */
bool FUN_00027e50(float *dir, float *vec2, float *limit, float threshold,
                  float *output)
{
  float dx;
  float dy;
  float len;
  float vx;
  float vy;
  float mag;
  float cross;
  float dot;
  int idx;

  dx = dir[0];
  dy = dir[1];
  vx = vec2[0];
  vy = vec2[1];

  len = xbox_sqrtf(dx * dx + dy * dy);

  if (xbox_fabsf(len) < 0.0001f)
    return 0;

  dx = (1.0f / len) * dx;
  dy = (1.0f / len) * dy;

  if (!(dx * limit[0] + dy * limit[1] > threshold))
    return 0;

  {
    float tmp[3];
    tmp[0] = vx;
    tmp[1] = vy;
    tmp[2] = dx;
    mag = magnitude3d(tmp);
  }
  if (!(mag > 0.0f))
    return 0;

  cross = vy * dx - vx * dy;
  idx = 0;
  if (cross > 0.0f)
    idx = 1;

  dot = dx * vx + dy * vy;
  if (!(dot > output[idx]))
    return 0;

  return 1;
}

/* FUN_00027f40 (0x27f40) — Actor look-at angle constraint evaluator.
 * Gets actor tag, computes pitch/yaw cosines based on combat state,
 * and invokes FUN_00027dd0/FUN_00027e50 to fill two output flags.
 *
 * Confirmed: EDI=actor, EBX=dir_ptr, out1/out2 at EBP+0x10/0x14. */
void FUN_00027f40(int actor_handle, void *dir_ptr, void *out1, void *out2)
{
  char *actor;
  char *tag_data;
  float cos_angles[2];

  actor = (char *)datum_get(actor_data, actor_handle);
  tag_data = (char *)tag_get(0x61637472, *(int *)(actor + 0x58));

  *((char *)out1) = (char)FUN_00027dd0(
    (float *)dir_ptr, (float *)(actor + 0x174), *(float *)(tag_data + 0x12c));

  if (*(short *)(actor + 0x6a) == 3) {
    cos_angles[0] = x87_fcos(*(float *)(tag_data + 0xbc));
    cos_angles[1] = *(float *)(tag_data + 0xc0);
  } else {
    cos_angles[0] = x87_fcos(*(float *)(tag_data + 0xb4));
    cos_angles[1] = *(float *)(tag_data + 0xb8);
  }
  cos_angles[1] = x87_fcos(cos_angles[1]);

  *((char *)out2) = (char)FUN_00027e50(
    (float *)dir_ptr, (float *)(actor + 0x180), (float *)(actor + 0x174),
    *(float *)(tag_data + 0x134), cos_angles);
}

/* FUN_00027ff0 (0x27ff0) — XBE naked draft (batch 69). */
#if defined(__clang__)
static void *(*const b27ff0_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void *(*const b27ff0_tag)(int, int) = tag_get;
static int (*const b27ff0_gtime)(void) = game_time_get;
static void (*const b27ff0_c4a6e0)(int actor_handle) = ai_debug_idle_look_clear;
static void (*const b27ff0_c64540)(int *out, int actor_handle) = FUN_00064540;
static int (*const b27ff0_c64570)(int *iter) = FUN_00064570;
static void (*const b27ff0_c4a710)(int index, float value) = ai_debug_idle_look_addprop;
static bool (*const b27ff0_c27dd0)(float *dir, float *vec2, float threshold) = FUN_00027dd0;
static bool (*const b27ff0_c27e50)(float *dir, float *vec2, float *limit, float threshold, float *output) = FUN_00027e50;

__attribute__((naked, noinline))
char FUN_00027ff0(int actor_handle __attribute__((unused)), char param_2 __attribute__((unused)), char param_3 __attribute__((unused)), short *output __attribute__((unused)), char *out_flag __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x30, %%esp\n\t"
      "movl 0x6325a4, %%eax\n\t"
      "pushl %%ebx\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%edi\n\t"
      "movl 0x58(%%edi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x61637472\n\t"
      "call *%[tag]\n\t"
      "addl $0x10, %%esp\n\t"
      "movl %%eax, %%esi\n\t"
      "movl $0xffffffff, -0x10(%%ebp)\n\t"
      "movl $0, -0xc(%%ebp)\n\t"
      "movl $0, -0x18(%%ebp)\n\t"
      "movb $0, -0x2(%%ebp)\n\t"
      "call *%[gtime]\n\t"
      "cmpw $3, 0x6a(%%edi)\n\t"
      "movl 0x12c(%%esi), %%edx\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "movl 0x134(%%esi), %%eax\n\t"
      "movl %%edx, -0x1c(%%ebp)\n\t"
      "movl %%eax, -0x20(%%ebp)\n\t"
      "jne .LFUN_00027ff0_1\n\t"
      "flds 0xbc(%%esi)\n\t"
      "fcos\n\t"
      "fstps -0x28(%%ebp)\n\t"
      "flds 0xc0(%%esi)\n\t"
      "jmp .LFUN_00027ff0_2\n\t"
      ".LFUN_00027ff0_1:\n\t"
      "flds 0xb4(%%esi)\n\t"
      "fcos\n\t"
      "fstps -0x28(%%ebp)\n\t"
      "flds 0xb8(%%esi)\n\t"
      ".LFUN_00027ff0_2:\n\t"
      "fcos\n\t"
      "cmpl 0x5ac9f8, %%ebx\n\t"
      "fstps -0x24(%%ebp)\n\t"
      "jne .LFUN_00027ff0_3\n\t"
      "pushl %%ebx\n\t"
      "call *%[c4a6e0]\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_00027ff0_3:\n\t"
      "leal -0x30(%%ebp), %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c64540]\n\t"
      "leal -0x30(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c64570]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_00027ff0_17\n\t"
      ".LFUN_00027ff0_4:\n\t"
      "movw 0x24(%%esi), %%ax\n\t"
      "xorb %%bl, %%bl\n\t"
      "cmpw $2, %%ax\n\t"
      "movl $0, -0x8(%%ebp)\n\t"
      "movb %%bl, -0x1(%%ebp)\n\t"
      "jl .LFUN_00027ff0_9\n\t"
      "cmpw $3, %%ax\n\t"
      "jg .LFUN_00027ff0_9\n\t"
      "cmpw $0, 0x32(%%esi)\n\t"
      "je .LFUN_00027ff0_9\n\t"
      "flds 0x54(%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00027ff0_10\n\t"
      "movl 0x5c(%%esi), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "jne .LFUN_00027ff0_5\n\t"
      "flds 0x2533c8\n\t"
      "jmp .LFUN_00027ff0_6\n\t"
      ".LFUN_00027ff0_5:\n\t"
      "fildl -0x14(%%ebp)\n\t"
      "fisubl -0x8(%%ebp)\n\t"
      "fmuls 0x2552a8\n\t"
      "fsubs 0x2533c8\n\t"
      ".LFUN_00027ff0_6:\n\t"
      "flds 0x54(%%esi)\n\t"
      "fsubs 0x58(%%esi)\n\t"
      "fdivs 0x54(%%esi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fcoms 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00027ff0_7\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c8\n\t"
      ".LFUN_00027ff0_7:\n\t"
      "fmuls 0x54(%%esi)\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "flds 0x54(%%esi)\n\t"
      "fcomps 0x58(%%esi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00027ff0_8\n\t"
      "movb $1, %%bl\n\t"
      "movb %%bl, -0x1(%%ebp)\n\t"
      "jmp .LFUN_00027ff0_10\n\t"
      ".LFUN_00027ff0_8:\n\t"
      "xorb %%bl, %%bl\n\t"
      "movb %%bl, -0x1(%%ebp)\n\t"
      "jmp .LFUN_00027ff0_10\n\t"
      ".LFUN_00027ff0_9:\n\t"
      "movl $0, 0x58(%%esi)\n\t"
      ".LFUN_00027ff0_10:\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "cmpl 0x5ac9f8, %%eax\n\t"
      "jne .LFUN_00027ff0_11\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movl -0x30(%%ebp), %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c4a710]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_00027ff0_11:\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00027ff0_16\n\t"
      "movb 0x10(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00027ff0_13\n\t"
      "movb 0xc(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00027ff0_12\n\t"
      "testb %%bl, %%bl\n\t"
      "jne .LFUN_00027ff0_15\n\t"
      ".LFUN_00027ff0_12:\n\t"
      "movl -0x1c(%%ebp), %%ecx\n\t"
      "leal 0xe0(%%esi), %%eax\n\t"
      "leal 0x5a4(%%edi), %%edx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c27dd0]\n\t"
      "addl $4, %%esp\n\t"
      "jmp .LFUN_00027ff0_14\n\t"
      ".LFUN_00027ff0_13:\n\t"
      "leal -0x28(%%ebp), %%ebx\n\t"
      "pushl %%ebx\n\t"
      "movl -0x20(%%ebp), %%ebx\n\t"
      "leal 0xe0(%%esi), %%eax\n\t"
      "leal 0x5b0(%%edi), %%ecx\n\t"
      "leal 0x5a4(%%edi), %%edx\n\t"
      "pushl %%ebx\n\t"
      "call *%[c27e50]\n\t"
      "movb -0x1(%%ebp), %%bl\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_00027ff0_14:\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00027ff0_16\n\t"
      ".LFUN_00027ff0_15:\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fcomps -0xc(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00027ff0_16\n\t"
      "movl -0x30(%%ebp), %%edx\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movl %%esi, -0x18(%%ebp)\n\t"
      "movl %%edx, -0x10(%%ebp)\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "movb %%bl, -0x2(%%ebp)\n\t"
      ".LFUN_00027ff0_16:\n\t"
      "leal -0x30(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c64570]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $4, %%esp\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LFUN_00027ff0_4\n\t"
      "movl -0x10(%%ebp), %%ecx\n\t"
      "cmpl $-1, %%ecx\n\t"
      "je .LFUN_00027ff0_17\n\t"
      "movl -0x18(%%ebp), %%eax\n\t"
      "movl -0x14(%%ebp), %%edx\n\t"
      "movl %%edx, 0x5c(%%eax)\n\t"
      "movl 0x54(%%eax), %%edx\n\t"
      "movl %%edx, 0x58(%%eax)\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "movl %%ecx, 0x4(%%eax)\n\t"
      "movb -0x2(%%ebp), %%cl\n\t"
      "movw $1, (%%eax)\n\t"
      "movl 0x18(%%ebp), %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb %%cl, (%%eax)\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00027ff0_17:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [dget] "m"(b27ff0_dget), [tag] "m"(b27ff0_tag), [gtime] "m"(b27ff0_gtime), [c4a6e0] "m"(b27ff0_c4a6e0), [c64540] "m"(b27ff0_c64540), [c64570] "m"(b27ff0_c64570), [c4a710] "m"(b27ff0_c4a710), [c27dd0] "m"(b27ff0_c27dd0), [c27e50] "m"(b27ff0_c27e50)
      : "memory");
}
#else
#error "FUN_00027ff0: clang naked draft required"
#endif


/* FUN_00028cc0 (0x28cc0)
 * Primary look update: evaluates whether the actor should be looking/aiming
 * at a target within angular constraints, then writes the constrained direction
 * to actor+0x570 and updates the look-spec via FUN_00028250.
 *
 * Confirmed: EAX = actor_handle (register arg, invisible to Ghidra);
 *   look_vectors = param_1 (float*); dir_vec = param_2 (float*);
 *   look_mode = param_3 (char); is_aim = param_4 (char);
 *   is_secondary = param_5 (char).
 *   The is_secondary param slot [EBP+0x18] is REUSED as az_range float storage
 *   by MSVC — local az_range variable avoids the slot reuse in C89.
 *   FUN_000283b0 called with @<eax>=local_dir (copy of *dir_vec);
 *   FUN_00028250 called with @<esi>=actor_handle (preserved ESI),
 * @<edi>=look_type. look_type = is_aim ? 1 : 2 (computed via SETZ+INC in disasm
 * at 0x28e8a-0x28e92). Original branch layout: is_aim!=0 (combat) is
 * fallthrough at 0x28d3b; is_aim==0 (idle) is the taken JZ branch to 0x28dd7.
 *   actor+0x55c = primary look valid flag; actor+0x55d = is_aim copy;
 *   actor+0x56c = 4 (short, look type slot set before FUN_000283b0 call);
 *   actor+0x564 = FUN_00028250 result; actor+0x570 = output look direction
 * vec3. Returns 1 (char) if FUN_00028250 found a valid look target, 0
 * otherwise. */
char FUN_00028cc0(float *look_vectors, float *dir_vec, char look_mode,
                  char is_aim, char is_secondary, int actor_handle)
{
  char *actor;
  int tag_data;
  float local_dir[3];
  float el_min;
  char local_c;
  float el_max;
  float az_range;
  int look_type;
  int fp_result;

  actor = (char *)datum_get(actor_data, actor_handle);
  tag_data = (int)tag_get('actr', *(int *)(actor + 0x58));
  local_c = 0;
  *(char *)(actor + 0x55c) = 0;

  if (is_secondary != '\0' ||
      FUN_00027ff0(actor_handle, look_mode, is_aim, (short *)(actor + 0x56c),
                   &local_c) == '\0') {
    local_dir[0] = dir_vec[0];
    local_dir[1] = dir_vec[1];
    local_dir[2] = dir_vec[2];

    /* Original branch layout: is_aim != 0 (combat) is fallthrough (JZ to idle
     * path taken at 0x28d3b), is_aim == 0 (idle) is the JZ-taken branch */
    if (is_aim != '\0') {
      /* Combat/aim angular constraints from tag */
      if (look_mode != '\0') {
        /* Full 180-degree horizontal range */
        az_range = 3.1415927f;
      } else {
        if (*(float *)(tag_data + 0xa4) <= *(float *)(tag_data + 0xc4)) {
          az_range = *(float *)(tag_data + 0xa4);
        } else {
          az_range = *(float *)(tag_data + 0xc4);
        }
      }
      if (*(float *)(tag_data + 0xa8) <= *(float *)(tag_data + 0xc8)) {
        el_max = *(float *)(tag_data + 0xa8);
      } else {
        el_max = *(float *)(tag_data + 0xc8);
      }
      local_dir[2] = 0.0f;
      if (normalize3d(local_dir) == 0.0f) {
        local_dir[0] = *(float *)(*(int *)0x0031fc3c);
        local_dir[1] = *(float *)(*(int *)0x0031fc3c + 4);
        local_dir[2] = *(float *)(*(int *)0x0031fc3c + 8);
      }
    } else {
      /* Idle angular constraints from tag */
      if (*(float *)(tag_data + 0xac) <= *(float *)(tag_data + 0xcc)) {
        az_range = *(float *)(tag_data + 0xac);
      } else {
        az_range = *(float *)(tag_data + 0xcc);
      }
      if (*(float *)(tag_data + 0xb0) <= *(float *)(tag_data + 0xd0)) {
        el_max = *(float *)(tag_data + 0xb0);
      } else {
        el_max = *(float *)(tag_data + 0xd0);
      }
    }

    el_min = -el_max;
    if (*(char *)(actor + 0x161) != '\0') {
      el_min = el_min * *(float *)0x00253398;
    }
    *(short *)(actor + 0x56c) = 4;
    if (!FUN_000283b0((float *)(actor + 0x120), 1, -az_range, az_range, el_min,
                      el_max, (float *)(actor + 0x570), local_dir)) {
      return local_c;
    }
  }

  look_type = is_aim ? 1 : 2;
  fp_result = FUN_00028250(look_vectors, local_c, actor_handle, look_type);
  *(int *)(actor + 0x564) = fp_result;
  if (fp_result == 0) {
    return local_c;
  }
  *(char *)(actor + 0x55c) = 1;
  *(char *)(actor + 0x55d) = is_aim;
  return local_c;
}

/* FUN_00028ed0 (0x28ed0)
 * Idle-minor look update: selects a randomised look direction within the
 * actor's angular constraints and writes a new idle-minor look-spec if one
 * is found, then evaluates the current look state via FUN_00028250.
 *
 * Called from actor_look_update when the idle-minor timer has expired.
 *
 * Confirmed: EAX = actor_handle (register arg); param_1 = look_vectors
 * (float*); param_2 = idle_direction (float*, passed as @<eax> to
 * FUN_000283b0); FUN_000283b0 called with 7 cdecl + 1 @<eax> = idle_direction;
 *   FUN_00028250 called with ESI=actor_handle (preserved), EDI=2, cdecl
 *   (look_vectors, flag_byte). Output vec3 written to actor+0x580/584/588. */
void FUN_00028ed0(float *look_vectors, float *idle_direction, int actor_handle)
{
  char *actor;
  int tag_data;
  float az_range;
  float el_range;
  float *pfVar4;
  float az_min;
  float az_max;
  float out_vec3[3];
  char flag_byte;
  char look_found;

  actor = (char *)datum_get(actor_data, actor_handle);
  tag_data = (int)tag_get('actr', *(int *)(actor + 0x58));
  flag_byte = 0;
  *(char *)(actor + 0x55f) = 0;

  look_found =
    FUN_00027ff0(actor_handle, 0, 0, (short *)(actor + 0x57c), &flag_byte);
  if (!look_found) {
    /* az_range = min(tag[0xac], tag[0xcc]) */
    if (*(float *)(tag_data + 0xac) <= *(float *)(tag_data + 0xcc)) {
      az_range = *(float *)(tag_data + 0xac);
    } else {
      az_range = *(float *)(tag_data + 0xcc);
    }
    /* el_range = min(tag[0xb0], tag[0xd0]) */
    if (*(float *)(tag_data + 0xb0) <= *(float *)(tag_data + 0xd0)) {
      el_range = *(float *)(tag_data + 0xb0);
    } else {
      el_range = *(float *)(tag_data + 0xd0);
    }
    /* select azimuth limit table: crouching (state==3) vs standing */
    if (*(short *)(actor + 0x6a) == 3) {
      pfVar4 = (float *)(tag_data + 0xbc);
    } else {
      pfVar4 = (float *)(tag_data + 0xb4);
    }
    /* az_min = max(-az_range, -pfVar4[0]) */
    az_min = -*pfVar4;
    if (az_min < -az_range) {
      az_min = -az_range;
    }
    /* az_max = min(az_range, pfVar4[1]) */
    az_max = az_range;
    if (pfVar4[1] < az_range) {
      az_max = pfVar4[1];
    }
    if (!FUN_000283b0((float *)(actor + 0x120), 0, az_min, az_max, -el_range,
                      el_range, out_vec3, idle_direction)) {
      /* Original 0x28fe7 `je 0x29033`: when no idle look direction is found,
         RETURN early — do NOT call FUN_00028250 or arm the look gate. The
         prior lift dropped this early-out and fell through, arming +0x55f
         over a stale +0x57c==4 / (0,0,0) +0x580. That degenerate look-spec
         was later copied by FUN_00028660 case 4 (actor_looking.c:8894),
         bypassing its magnitude gate, and halted at
         actor_looking.c:529 assert_valid_real_normal3d(0,0,0) during PoA
         combat actor activation. */
      return;
    }
    *(float *)(actor + 0x580) = out_vec3[0];
    *(float *)(actor + 0x584) = out_vec3[1];
    *(float *)(actor + 0x588) = out_vec3[2];
    *(short *)(actor + 0x57c) = 4;
    flag_byte = 0;
  }

  *(int *)(actor + 0x568) =
    FUN_00028250(look_vectors, flag_byte, actor_handle, 2);
  if (*(int *)(actor + 0x568) != 0) {
    *(char *)(actor + 0x55f) = 1;
  }
}

/* look_spec_28660_safe — wrapper around FUN_00028660 that guards against the
   actor_looking.c:529 halt on a degenerate (0,0,0) look-spec.

   FUN_00028660 builds a look direction from a look-spec. Its NORMALIZE cases
   (type 0/1/3/5/6) pass a (0,0,0) through normalize3d, whose magnitude gate
   makes 28660 silently return 0. But its COPY cases — type 2 (actor+0x68c /
   actor+0x63c) and type 4 (look_spec+4) — copy the stored vector directly,
   bypassing that gate, and a (0,0,0) there reaches assert_valid_real_normal3d
   and HALTS at line 529.

   Such a degenerate copy-case look-spec arises during actor activation: the
   idle look producer FUN_00028cc0 sets the look-spec type (e.g. +0x56c=4)
   BEFORE calling FUN_000283b0, which writes the look vector ONLY on success.
   When 283b0's collision raycast (FUN_0014df70) finds no clear direction in
   any of its attempts it returns false and leaves the vector unwritten — so a
   never-initialised (0,0,0) survives with the type already armed. The slot is
   then copied (+0x56c -> +0x57c) and consumed by 28660 case 4 (line 8894).

   In a RELEASE build 28660 would simply return 0 here (valid_real_normal3d
   fails, asserts compiled out); we replicate exactly that — return 0 ("no
   valid look this tick") for a degenerate copy-case vector — so the debug
   build does not halt on a state the shipping engine tolerates. The caller's
   28660-returned-0 path disarms the look gate and falls through to the
   snap-to-original handling, which is the intended no-look behaviour.

   NOTE (upstream): the root reason +0x570 carries a bad vector (live: an
   uninitialized X = 0xffffffff with valid Y/Z, i.e. NaN; sometimes (0,0,0))
   is FUN_000283b0 / FUN_0014df70 reporting every idle-look candidate blocked
   at activation and returning 0 without writing +0x570, leaving its prior /
   uninitialized contents; that raycast lift should be re-validated
   separately. */
/* Kept after actor_look_update naked draft (batch 78). */
__attribute__((unused)) static char look_spec_28660_safe(int actor_handle, char *actor,
                                 short *look_spec, float *out_vec)
{
  int cs;
  float *tgt;

  cs = (int)*look_spec;
  tgt = 0;
  if (cs == 2) {
    if (*(short *)(actor + 0x5f2) == 2)
      tgt = (float *)(actor + 0x68c);
    else if (*(char *)(actor + 0x628) != '\0')
      tgt = (float *)(actor + 0x63c);
  } else if (cs == 4) {
    tgt = (float *)((char *)look_spec + 4);
  }
  if (tgt != 0) {
    /* Replicate FUN_00028660's own valid_real_normal3d (0x21fb0) gate exactly:
       skip (return 0, "no valid look this tick") unless the copy-case vector is
       a true unit normal -- |dot(v,v) - 1| < 0.001 and not NaN/Inf. The earlier
       `!(m2 >= 1e-8f)` form only closed the LOWER bound: it rejected
       (0,0,0)/tiny/NaN but PASSED a finite-but-huge uninitialized component
       (live: +0x570 X = -3.5e31), whose squared length overflows to +inf,
       satisfies `inf >= 1e-8f`, and reached assert_valid_real_normal3d at #529
       -> HALT. Any vector this predicate rejects, 28660 itself rejects (it
       calls the same check), so this is byte-faithful to the release path and
       value-agnostic to whatever garbage the stale slot carries. */
    if (!valid_real_normal3d(tgt))
      return 0;
  }
  return FUN_00028660(actor_handle, look_spec, out_vec);
}

/* actor_look_update (0x29040) — XBE naked draft (batch 78). */
#if defined(__clang__)
static void *(*const b29040_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void *(*const b29040_tag)(int, int) = tag_get;
static bool (*const b29040_c21fb0)(float *v) = valid_real_normal3d;
static char * (*const b29040_c8d9d0)(char *buffer, const char *format, ...) = csprintf;
static void (*const b29040_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b29040_exitfn)(int) = system_exit;
static int (*const b29040_c3b270)(int actor_handle) = actor_attacking_target;
static bool (*const b29040_c210b0)(int actor_handle) = FUN_000210b0;
static char (*const b29040_c28660)(int actor_handle, short *look_spec, float *direction) = FUN_00028660;
static int16_t (*const b29040_c1d6d0)(int actor_handle) = actor_action_try_to_panic;
static char * (*const b29040_c49ac0)(int actor_handle, int object_handle, char with_actor, char *buf, int buf_size) = ai_debug_describe_actor;
static void (*const b29040_cff4d0)(int channel, const char *format, ...) = console_printf;
static bool (*const b29040_c27dd0)(float *dir, float *vec2, float threshold) = FUN_00027dd0;
static int (*const b29040_c2a860)(int actor_handle) = actor_move_force_stop;
static bool (*const b29040_c27e50)(float *dir, float *vec2, float *limit, float threshold, float *output) = FUN_00027e50;
static int (*const b29040_c27a10)(int actor_handle /* */) = FUN_00027a10;
static int (*const b29040_c28250)(float *look_vectors, char is_secondary, int actor_handle, int look_type) = FUN_00028250;
static char (*const b29040_c28cc0)(float *look_vectors, float *dir_vec, char look_mode, char param4, char is_secondary, int actor_handle) = FUN_00028cc0;
static void (*const b29040_c28ed0)(float *look_vectors, float *idle_direction, int actor_handle) = FUN_00028ed0;
static bool (*const b29040_c1a9ad0)(int unit_handle) = unit_is_busy;
static float (*const b29040_mag)(float *) = magnitude3d;
static int (*const b29040_c28610)(float *v) = valid_real_normal2d;
static float (*const b29040_c13070)(float *a, float *b) = FUN_00013070;
static void (*const b29040_c36e50)(int actor_handle) = FUN_00036e50;
static void (*const b29040_c3c3a0)(int actor_handle, char flag) = actor_unit_control_exact_facing;

__attribute__((naked, noinline))
void actor_look_update(int actor_handle __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x58, %%esp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl 0x6325a4, %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x58(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x61637472\n\t"
      "movl %%esi, -0x28(%%ebp)\n\t"
      "call *%[tag]\n\t"
      "leal 0x5a4(%%esi), %%edi\n\t"
      "pushl %%edi\n\t"
      "movl %%eax, -0x40(%%ebp)\n\t"
      "movb $0, -0x9(%%ebp)\n\t"
      "movl %%edi, -0x14(%%ebp)\n\t"
      "call *%[c21fb0]\n\t"
      "addl $0x14, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lactor_look_update_1\n\t"
      "flds 0x5ac(%%esi)\n\t"
      "pushl $1\n\t"
      "pushl $0x44f\n\t"
      "pushl $0x255284\n\t"
      "subl $0x18, %%esp\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds 0x5a8(%%esi)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds (%%edi)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x255750\n\t"
      "pushl $0x254a24\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x24, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lactor_look_update_1:\n\t"
      "pushl %%ebx\n\t"
      "leal 0x5b0(%%esi), %%ebx\n\t"
      "pushl %%ebx\n\t"
      "movl %%ebx, -0x10(%%ebp)\n\t"
      "call *%[c21fb0]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lactor_look_update_2\n\t"
      "flds 0x5b8(%%esi)\n\t"
      "pushl $1\n\t"
      "pushl $0x450\n\t"
      "pushl $0x255284\n\t"
      "subl $0x18, %%esp\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds 0x5b4(%%esi)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds (%%ebx)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x255728\n\t"
      "pushl $0x254a24\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x24, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lactor_look_update_2:\n\t"
      "leal 0x5bc(%%esi), %%ebx\n\t"
      "pushl %%ebx\n\t"
      "movl %%ebx, -0x18(%%ebp)\n\t"
      "call *%[c21fb0]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lactor_look_update_3\n\t"
      "flds 0x5c4(%%esi)\n\t"
      "pushl $1\n\t"
      "pushl $0x451\n\t"
      "pushl $0x255284\n\t"
      "subl $0x18, %%esp\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds 0x5c0(%%esi)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds (%%ebx)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x255700\n\t"
      "pushl $0x254a24\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x24, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lactor_look_update_3:\n\t"
      "movw 0x6dc(%%esi), %%ax\n\t"
      "cmpw $1, %%ax\n\t"
      "je .Lactor_look_update_7\n\t"
      "movb 0x161(%%esi), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "je .Lactor_look_update_5\n\t"
      "movb $1, -0x4(%%ebp)\n\t"
      ".Lactor_look_update_4:\n\t"
      "cmpw $3, 0x6a(%%esi)\n\t"
      "movb -0x4(%%ebp), %%al\n\t"
      "movb 0x58d(%%esi), %%dl\n\t"
      "movb 0x58e(%%esi), %%cl\n\t"
      "movb %%al, -0x2(%%ebp)\n\t"
      "movl -0x40(%%ebp), %%eax\n\t"
      "movb %%dl, -0x3(%%ebp)\n\t"
      "movl 0x12c(%%eax), %%edx\n\t"
      "movb %%cl, -0x6(%%ebp)\n\t"
      "movl 0x134(%%eax), %%ecx\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "movb $0, -0x8(%%ebp)\n\t"
      "movb $0, -0x5(%%ebp)\n\t"
      "movl %%edx, -0x20(%%ebp)\n\t"
      "movl %%ecx, -0x2c(%%ebp)\n\t"
      "jne .Lactor_look_update_8\n\t"
      "flds 0xbc(%%eax)\n\t"
      "fcos\n\t"
      "fstps -0x4c(%%ebp)\n\t"
      "flds 0xc0(%%eax)\n\t"
      "jmp .Lactor_look_update_9\n\t"
      ".Lactor_look_update_5:\n\t"
      "testw %%ax, %%ax\n\t"
      "je .Lactor_look_update_6\n\t"
      "cmpw $2, %%ax\n\t"
      "je .Lactor_look_update_6\n\t"
      "movb $0, -0x4(%%ebp)\n\t"
      "jmp .Lactor_look_update_4\n\t"
      ".Lactor_look_update_6:\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c3b270]\n\t"
      "addl $4, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "setne -0x4(%%ebp)\n\t"
      "jmp .Lactor_look_update_4\n\t"
      ".Lactor_look_update_7:\n\t"
      "movl -0x10(%%ebp), %%edx\n\t"
      "movl %%edi, %%ecx\n\t"
      "movl (%%ecx), %%eax\n\t"
      "movl %%eax, (%%edx)\n\t"
      "movl 0x4(%%ecx), %%eax\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "movl %%eax, 0x4(%%edx)\n\t"
      "movl %%ecx, 0x8(%%edx)\n\t"
      "movl (%%edi), %%edx\n\t"
      "movl 0x4(%%edi), %%eax\n\t"
      "movl 0x8(%%edi), %%ecx\n\t"
      "movl %%edx, (%%ebx)\n\t"
      "movl %%eax, 0x4(%%ebx)\n\t"
      "movl %%ecx, 0x8(%%ebx)\n\t"
      "movl -0x10(%%ebp), %%ebx\n\t"
      "jmp .Lactor_look_update_93\n\t"
      ".Lactor_look_update_8:\n\t"
      "flds 0xb4(%%eax)\n\t"
      "fcos\n\t"
      "fstps -0x4c(%%ebp)\n\t"
      "flds 0xb8(%%eax)\n\t"
      ".Lactor_look_update_9:\n\t"
      "fcos\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "fstps -0x48(%%ebp)\n\t"
      "call *%[c210b0]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_look_update_10\n\t"
      "movb 0x456(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lactor_look_update_10\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x58(%%ebp), %%edi\n\t"
      "leal -0x3c(%%ebp), %%ebx\n\t"
      "movw $2, -0x3c(%%ebp)\n\t"
      "call *%[c28660]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_look_update_10\n\t"
      "movl $7, -0x24(%%ebp)\n\t"
      "movb $1, -0x9(%%ebp)\n\t"
      "jmp .Lactor_look_update_12\n\t"
      ".Lactor_look_update_10:\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x3e8(%%esi), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "movl %%eax, -0x24(%%ebp)\n\t"
      "je .Lactor_look_update_12\n\t"
      "cmpw $1, %%ax\n\t"
      "je .Lactor_look_update_12\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "leal 0x3ec(%%esi), %%ebx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x58(%%ebp), %%edi\n\t"
      "call *%[c28660]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_look_update_11\n\t"
      "cmpw $2, (%%ebx)\n\t"
      "sete -0x9(%%ebp)\n\t"
      "jmp .Lactor_look_update_12\n\t"
      ".Lactor_look_update_11:\n\t"
      "movl $0, -0x24(%%ebp)\n\t"
      ".Lactor_look_update_12:\n\t"
      "cmpw $0, 0x544(%%esi)\n\t"
      "movl $0, -0x1c(%%ebp)\n\t"
      "jl .Lactor_look_update_13\n\t"
      "cmpw $0, 0x548(%%esi)\n\t"
      "jle .Lactor_look_update_13\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "leal 0x54c(%%esi), %%ebx\n\t"
      "pushl %%edx\n\t"
      "leal -0x38(%%ebp), %%edi\n\t"
      "call *%[c28660]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_look_update_13\n\t"
      "movw 0x546(%%esi), %%ax\n\t"
      "movw %%ax, -0x1c(%%ebp)\n\t"
      ".Lactor_look_update_13:\n\t"
      "movb 0x504(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_look_update_14\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1d6d0]\n\t"
      "addl $4, %%esp\n\t"
      "cmpw $2, %%ax\n\t"
      "jne .Lactor_look_update_14\n\t"
      "movl -0x1c(%%ebp), %%eax\n\t"
      "cmpw $5, %%ax\n\t"
      "movl $5, -0x1c(%%ebp)\n\t"
      "jg .Lactor_look_update_14\n\t"
      "movl %%eax, -0x1c(%%ebp)\n\t"
      ".Lactor_look_update_14:\n\t"
      "movl -0x24(%%ebp), %%edi\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "cmpw %%bx, %%di\n\t"
      "je .Lactor_look_update_15\n\t"
      "cmpw $1, %%di\n\t"
      "je .Lactor_look_update_15\n\t"
      "leal -0x58(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c21fb0]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lactor_look_update_15\n\t"
      "flds -0x50(%%ebp)\n\t"
      "pushl $1\n\t"
      "pushl $0x4ca\n\t"
      "pushl $0x255284\n\t"
      "subl $0x18, %%esp\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds -0x54(%%ebp)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds -0x58(%%ebp)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x2556f0\n\t"
      "pushl $0x254a24\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x24, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lactor_look_update_15:\n\t"
      "cmpw %%bx, -0x1c(%%ebp)\n\t"
      "je .Lactor_look_update_16\n\t"
      "leal -0x38(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c21fb0]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lactor_look_update_16\n\t"
      "flds -0x30(%%ebp)\n\t"
      "pushl $1\n\t"
      "pushl $0x4ce\n\t"
      "pushl $0x255284\n\t"
      "subl $0x18, %%esp\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds -0x34(%%ebp)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds -0x38(%%ebp)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x2556dc\n\t"
      "pushl $0x254a24\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x24, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lactor_look_update_16:\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x548(%%esi), %%ax\n\t"
      "cmpw %%bx, %%ax\n\t"
      "jle .Lactor_look_update_18\n\t"
      "decl %%eax\n\t"
      "cmpw %%bx, %%ax\n\t"
      "movw %%ax, 0x548(%%esi)\n\t"
      "jne .Lactor_look_update_18\n\t"
      "movb 0x5aca5d, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_look_update_17\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "pushl $0x100\n\t"
      "pushl $0x5ab100\n\t"
      "pushl %%ebx\n\t"
      "pushl $-1\n\t"
      "pushl %%ecx\n\t"
      "call *%[c49ac0]\n\t"
      "pushl %%eax\n\t"
      "pushl $0x2556c4\n\t"
      "pushl %%ebx\n\t"
      "call *%[cff4d0]\n\t"
      "addl $0x20, %%esp\n\t"
      ".Lactor_look_update_17:\n\t"
      "movw %%bx, 0x544(%%esi)\n\t"
      "movw %%bx, 0x546(%%esi)\n\t"
      ".Lactor_look_update_18:\n\t"
      "cmpw $2, %%di\n\t"
      "movl -0x54(%%ebp), %%ebx\n\t"
      "movb $0, 0x58c(%%esi)\n\t"
      "jl .Lactor_look_update_26\n\t"
      "cmpw $5, %%di\n\t"
      "jl .Lactor_look_update_19\n\t"
      "movb -0x3(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lactor_look_update_20\n\t"
      "movl -0x20(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl -0x14(%%ebp), %%edx\n\t"
      "leal -0x58(%%ebp), %%eax\n\t"
      "call *%[c27dd0]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lactor_look_update_20\n\t"
      ".Lactor_look_update_19:\n\t"
      "cmpw $3, %%di\n\t"
      "jl .Lactor_look_update_21\n\t"
      "movb -0x6(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_look_update_21\n\t"
      "movb $0, -0x6(%%ebp)\n\t"
      "movb $1, -0x3(%%ebp)\n\t"
      ".Lactor_look_update_20:\n\t"
      "cmpw $7, %%di\n\t"
      "movl -0x10(%%ebp), %%edx\n\t"
      "movl -0x58(%%ebp), %%eax\n\t"
      "movl -0x50(%%ebp), %%ecx\n\t"
      "movl %%eax, (%%edx)\n\t"
      "movl %%ebx, 0x4(%%edx)\n\t"
      "movl %%ecx, 0x8(%%edx)\n\t"
      "movb -0x4(%%ebp), %%dl\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "movb %%dl, -0x2(%%ebp)\n\t"
      "jl .Lactor_look_update_21\n\t"
      "testb %%dl, %%dl\n\t"
      "movb $1, -0x5(%%ebp)\n\t"
      "je .Lactor_look_update_21\n\t"
      "movl -0x18(%%ebp), %%edx\n\t"
      "movl %%eax, (%%edx)\n\t"
      "movl %%ebx, 0x4(%%edx)\n\t"
      "movl %%ecx, 0x8(%%edx)\n\t"
      ".Lactor_look_update_21:\n\t"
      "cmpw $2, %%di\n\t"
      "jne .Lactor_look_update_22\n\t"
      "movb -0x3(%%ebp), %%al\n\t"
      "negb %%al\n\t"
      "sbbl %%eax, %%eax\n\t"
      "andl $5, %%eax\n\t"
      "movl %%eax, %%edi\n\t"
      "movl %%edi, -0x24(%%ebp)\n\t"
      ".Lactor_look_update_22:\n\t"
      "movb -0x3(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_look_update_23\n\t"
      "movl -0x14(%%ebp), %%ecx\n\t"
      "movl -0x58(%%ebp), %%edx\n\t"
      "movl -0x50(%%ebp), %%eax\n\t"
      "movl %%edx, (%%ecx)\n\t"
      "movl %%ebx, 0x4(%%ecx)\n\t"
      "movl %%eax, 0x8(%%ecx)\n\t"
      "movb 0x591(%%esi), %%al\n\t"
      "cmpw $4, %%di\n\t"
      "sete %%cl\n\t"
      "orb %%cl, %%al\n\t"
      "movb $0, -0x3(%%ebp)\n\t"
      "movb $0, -0x6(%%ebp)\n\t"
      "movb %%al, 0x591(%%esi)\n\t"
      ".Lactor_look_update_23:\n\t"
      "movb 0x58d(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lactor_look_update_24\n\t"
      "movb 0x58e(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_look_update_25\n\t"
      ".Lactor_look_update_24:\n\t"
      "cmpw $6, %%di\n\t"
      "movb $0, -0x8(%%ebp)\n\t"
      "jl .Lactor_look_update_26\n\t"
      ".Lactor_look_update_25:\n\t"
      "movb $1, -0x8(%%ebp)\n\t"
      ".Lactor_look_update_26:\n\t"
      "movswl -0x1c(%%ebp), %%eax\n\t"
      "addl $-2, %%eax\n\t"
      "cmpl $6, %%eax\n\t"
      "ja .Lactor_look_update_46\n\t"
      "movzbl 0x2a290(%%eax), %%edx\n\t"
      "jmp *.Lactor_look_update_jt0(,%%edx,4)\n\t"
      ".Lactor_look_update_27:\n\t"
      "movl -0x20(%%ebp), %%eax\n\t"
      "movl -0x14(%%ebp), %%ebx\n\t"
      "pushl %%eax\n\t"
      "leal -0x38(%%ebp), %%eax\n\t"
      "movl %%ebx, %%edx\n\t"
      "call *%[c27dd0]\n\t"
      "movb %%al, -0x7(%%ebp)\n\t"
      "movb -0x8(%%ebp), %%al\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "movb -0x5(%%ebp), %%al\n\t"
      "jne .Lactor_look_update_33\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lactor_look_update_37\n\t"
      "movl -0x1c(%%ebp), %%edi\n\t"
      "cmpw $6, %%di\n\t"
      "jl .Lactor_look_update_28\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c2a860]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lactor_look_update_30\n\t"
      ".Lactor_look_update_28:\n\t"
      "cmpw $5, %%di\n\t"
      "jl .Lactor_look_update_29\n\t"
      "movb -0x6(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lactor_look_update_30\n\t"
      "movb 0x58d(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lactor_look_update_30\n\t"
      ".Lactor_look_update_29:\n\t"
      "cmpw $4, %%di\n\t"
      "jl .Lactor_look_update_34\n\t"
      "movb -0x7(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lactor_look_update_35\n\t"
      "movb -0x3(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_look_update_37\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_look_update_37\n\t"
      ".Lactor_look_update_30:\n\t"
      "movb 0x591(%%esi), %%al\n\t"
      "movl -0x38(%%ebp), %%ecx\n\t"
      "movl -0x30(%%ebp), %%edi\n\t"
      "testb %%al, %%al\n\t"
      "movl -0x34(%%ebp), %%eax\n\t"
      "je .Lactor_look_update_31\n\t"
      "movb -0x7(%%ebp), %%dl\n\t"
      "testb %%dl, %%dl\n\t"
      "jne .Lactor_look_update_32\n\t"
      ".Lactor_look_update_31:\n\t"
      "movl %%ecx, (%%ebx)\n\t"
      "movl %%eax, 0x4(%%ebx)\n\t"
      "movl %%edi, 0x8(%%ebx)\n\t"
      "movb $0, 0x591(%%esi)\n\t"
      ".Lactor_look_update_32:\n\t"
      "movl -0x10(%%ebp), %%edx\n\t"
      "movl %%ecx, (%%edx)\n\t"
      "movl %%eax, 0x4(%%edx)\n\t"
      "movl %%edi, 0x8(%%edx)\n\t"
      "movl -0x18(%%ebp), %%edx\n\t"
      "movl %%ecx, (%%edx)\n\t"
      "movl %%eax, 0x4(%%edx)\n\t"
      "movb -0x4(%%ebp), %%al\n\t"
      "movl %%edi, 0x8(%%edx)\n\t"
      "movb %%al, -0x2(%%ebp)\n\t"
      "jmp .Lactor_look_update_43\n\t"
      ".Lactor_look_update_33:\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lactor_look_update_37\n\t"
      "movl -0x1c(%%ebp), %%edi\n\t"
      ".Lactor_look_update_34:\n\t"
      "movb -0x7(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_look_update_37\n\t"
      ".Lactor_look_update_35:\n\t"
      "cmpw $5, %%di\n\t"
      "jge .Lactor_look_update_36\n\t"
      "cmpw $3, %%di\n\t"
      "jl .Lactor_look_update_37\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_look_update_37\n\t"
      ".Lactor_look_update_36:\n\t"
      "movl -0x38(%%ebp), %%eax\n\t"
      "movl -0x10(%%ebp), %%edi\n\t"
      "movl -0x34(%%ebp), %%ecx\n\t"
      "movl -0x30(%%ebp), %%edx\n\t"
      "movl %%eax, (%%edi)\n\t"
      "movl %%ecx, 0x4(%%edi)\n\t"
      "movl %%edx, 0x8(%%edi)\n\t"
      "movl -0x18(%%ebp), %%edi\n\t"
      "movl %%eax, (%%edi)\n\t"
      "movl %%ecx, 0x4(%%edi)\n\t"
      "movb -0x4(%%ebp), %%cl\n\t"
      "movl %%edx, 0x8(%%edi)\n\t"
      "movb %%cl, -0x2(%%ebp)\n\t"
      "jmp .Lactor_look_update_44\n\t"
      ".Lactor_look_update_37:\n\t"
      "movb -0x4(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_look_update_38\n\t"
      "movl -0x2c(%%ebp), %%eax\n\t"
      "movl -0x10(%%ebp), %%ecx\n\t"
      "leal -0x4c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "leal -0x38(%%ebp), %%eax\n\t"
      "movl %%ebx, %%edx\n\t"
      "call *%[c27e50]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_look_update_38\n\t"
      "movl -0x38(%%ebp), %%edx\n\t"
      "movl -0x18(%%ebp), %%ecx\n\t"
      "movl -0x34(%%ebp), %%eax\n\t"
      "movl %%edx, (%%ecx)\n\t"
      "movl -0x30(%%ebp), %%edx\n\t"
      "movl %%eax, 0x4(%%ecx)\n\t"
      "movl %%edx, 0x8(%%ecx)\n\t"
      "movb $0, -0x2(%%ebp)\n\t"
      "jmp .Lactor_look_update_46\n\t"
      ".Lactor_look_update_38:\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_look_update_46\n\t"
      "movb -0x7(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_look_update_46\n\t"
      "movl -0x38(%%ebp), %%eax\n\t"
      "movl -0x10(%%ebp), %%edi\n\t"
      "movl -0x34(%%ebp), %%ecx\n\t"
      "movl -0x30(%%ebp), %%edx\n\t"
      "movl %%eax, (%%edi)\n\t"
      "movl %%ecx, 0x4(%%edi)\n\t"
      "movl %%edx, 0x8(%%edi)\n\t"
      "movl -0x18(%%ebp), %%edi\n\t"
      "movl %%eax, (%%edi)\n\t"
      "movl %%ecx, 0x4(%%edi)\n\t"
      "movl %%edx, 0x8(%%edi)\n\t"
      "movb $1, -0x2(%%ebp)\n\t"
      "jmp .Lactor_look_update_45\n\t"
      ".Lactor_look_update_39:\n\t"
      "cmpw $8, -0x1c(%%ebp)\n\t"
      "movl -0x34(%%ebp), %%edi\n\t"
      "movl -0x38(%%ebp), %%ebx\n\t"
      "sete %%al\n\t"
      "movb %%al, -0xa(%%ebp)\n\t"
      "movb %%al, -0x8(%%ebp)\n\t"
      "movb 0x58d(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lactor_look_update_41\n\t"
      "movl -0x20(%%ebp), %%eax\n\t"
      "movl -0x14(%%ebp), %%edx\n\t"
      "pushl %%eax\n\t"
      "leal -0x38(%%ebp), %%eax\n\t"
      "call *%[c27dd0]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lactor_look_update_40\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c2a860]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_look_update_46\n\t"
      "movb $1, -0x8(%%ebp)\n\t"
      "jmp .Lactor_look_update_41\n\t"
      ".Lactor_look_update_40:\n\t"
      "movb -0xa(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_look_update_42\n\t"
      ".Lactor_look_update_41:\n\t"
      "movl -0x14(%%ebp), %%edx\n\t"
      "movl -0x30(%%ebp), %%eax\n\t"
      "movb -0x8(%%ebp), %%cl\n\t"
      "movl %%ebx, (%%edx)\n\t"
      "movl %%edi, 0x4(%%edx)\n\t"
      "movl %%eax, 0x8(%%edx)\n\t"
      "movb %%cl, 0x591(%%esi)\n\t"
      ".Lactor_look_update_42:\n\t"
      "movl -0x10(%%ebp), %%edx\n\t"
      "movl -0x30(%%ebp), %%eax\n\t"
      "movl -0x18(%%ebp), %%ecx\n\t"
      "movl %%ebx, (%%edx)\n\t"
      "movl %%edi, 0x4(%%edx)\n\t"
      "movl %%ebx, (%%ecx)\n\t"
      "movl %%eax, 0x8(%%edx)\n\t"
      "movb -0x4(%%ebp), %%dl\n\t"
      "movl %%edi, 0x4(%%ecx)\n\t"
      "movl %%eax, 0x8(%%ecx)\n\t"
      "movb %%dl, -0x2(%%ebp)\n\t"
      ".Lactor_look_update_43:\n\t"
      "movb $0, -0x3(%%ebp)\n\t"
      ".Lactor_look_update_44:\n\t"
      "movb $1, 0x58c(%%esi)\n\t"
      "movb $0, -0x5(%%ebp)\n\t"
      ".Lactor_look_update_45:\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      ".Lactor_look_update_46:\n\t"
      "movl -0x24(%%ebp), %%edi\n\t"
      "cmpw $2, %%di\n\t"
      "jne .Lactor_look_update_48\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_look_update_48\n\t"
      "movl -0x20(%%ebp), %%eax\n\t"
      "movl -0x14(%%ebp), %%edx\n\t"
      "pushl %%eax\n\t"
      "leal -0x58(%%ebp), %%eax\n\t"
      "call *%[c27dd0]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_look_update_48\n\t"
      "movl -0x10(%%ebp), %%ebx\n\t"
      "movl -0x58(%%ebp), %%ecx\n\t"
      "movl -0x54(%%ebp), %%eax\n\t"
      "movl -0x50(%%ebp), %%edx\n\t"
      "movl %%ecx, (%%ebx)\n\t"
      "movl %%eax, 0x4(%%ebx)\n\t"
      "movl %%edx, 0x8(%%ebx)\n\t"
      "movb -0x2(%%ebp), %%bl\n\t"
      "testb %%bl, %%bl\n\t"
      "je .Lactor_look_update_47\n\t"
      "movl -0x18(%%ebp), %%ebx\n\t"
      "movl %%ecx, (%%ebx)\n\t"
      "movl %%eax, 0x4(%%ebx)\n\t"
      "movl %%edx, 0x8(%%ebx)\n\t"
      ".Lactor_look_update_47:\n\t"
      "movb $0, 0x58c(%%esi)\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      ".Lactor_look_update_48:\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "call *%[c27a10]\n\t"
      "movl %%eax, %%ebx\n\t"
      "flds 0x4(%%ebx)\n\t"
      "movl %%ebx, -0x1c(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lactor_look_update_49\n\t"
      "movb $1, %%cl\n\t"
      "movb %%cl, -0x8(%%ebp)\n\t"
      "jmp .Lactor_look_update_50\n\t"
      ".Lactor_look_update_49:\n\t"
      "movb $0, -0x8(%%ebp)\n\t"
      "movb -0x8(%%ebp), %%cl\n\t"
      ".Lactor_look_update_50:\n\t"
      "flds 0xc(%%ebx)\n\t"
      "movb $1, -0x7(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .Lactor_look_update_51\n\t"
      "movb $0, -0x7(%%ebp)\n\t"
      ".Lactor_look_update_51:\n\t"
      "flds 0x14(%%ebx)\n\t"
      "movb $1, -0x6(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .Lactor_look_update_52\n\t"
      "movb $0, -0x6(%%ebp)\n\t"
      ".Lactor_look_update_52:\n\t"
      "cmpw $0, 0x3fc(%%esi)\n\t"
      "jle .Lactor_look_update_85\n\t"
      "movb -0x5(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lactor_look_update_85\n\t"
      "movb -0x1(%%ebp), %%dl\n\t"
      "testb %%dl, %%dl\n\t"
      "jne .Lactor_look_update_53\n\t"
      "movb -0x2(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_look_update_85\n\t"
      ".Lactor_look_update_53:\n\t"
      "testb %%cl, %%cl\n\t"
      "jne .Lactor_look_update_54\n\t"
      "movb -0x7(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lactor_look_update_54\n\t"
      "movb -0x6(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_look_update_85\n\t"
      ".Lactor_look_update_54:\n\t"
      "testb %%cl, %%cl\n\t"
      "movb $0, -0xa(%%ebp)\n\t"
      "movb $0, -0x5(%%ebp)\n\t"
      "je .Lactor_look_update_55\n\t"
      "movb -0x3(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_look_update_55\n\t"
      "cmpw $1, %%di\n\t"
      "jne .Lactor_look_update_55\n\t"
      "movl 0x560(%%esi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "movb $1, -0x24(%%ebp)\n\t"
      "je .Lactor_look_update_56\n\t"
      ".Lactor_look_update_55:\n\t"
      "movb $0, -0x24(%%ebp)\n\t"
      ".Lactor_look_update_56:\n\t"
      "movl 0x560(%%esi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jle .Lactor_look_update_57\n\t"
      "decl %%eax\n\t"
      "movl %%eax, 0x560(%%esi)\n\t"
      ".Lactor_look_update_57:\n\t"
      "movb 0x55c(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_look_update_59\n\t"
      "movb 0x55d(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_look_update_58\n\t"
      "testb %%dl, %%dl\n\t"
      "jne .Lactor_look_update_58\n\t"
      "movb $1, 0x55c(%%esi)\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "pushl $1\n\t"
      "pushl %%ebx\n\t"
      "movl $2, %%edi\n\t"
      "call *%[c28250]\n\t"
      "movl -0x28(%%ebp), %%ecx\n\t"
      "movl -0x10(%%ebp), %%edx\n\t"
      "movl -0x28(%%ebp), %%esi\n\t"
      "movl %%eax, 0x564(%%ecx)\n\t"
      "movl (%%edx), %%eax\n\t"
      "movw $4, 0x56c(%%ecx)\n\t"
      "addl $8, %%esp\n\t"
      "addl $0x570, %%ecx\n\t"
      "movl %%eax, (%%ecx)\n\t"
      "movl 0x4(%%edx), %%eax\n\t"
      "movl 0x8(%%edx), %%edx\n\t"
      "movl %%eax, 0x4(%%ecx)\n\t"
      "movl %%edx, 0x8(%%ecx)\n\t"
      "movb -0x1(%%ebp), %%dl\n\t"
      ".Lactor_look_update_58:\n\t"
      "movb 0x55c(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_look_update_59\n\t"
      "movl 0x564(%%esi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lactor_look_update_66\n\t"
      ".Lactor_look_update_59:\n\t"
      "testb %%dl, %%dl\n\t"
      "movb $1, %%al\n\t"
      "movb %%al, -0x30(%%ebp)\n\t"
      "je .Lactor_look_update_60\n\t"
      "movb -0x7(%%ebp), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "jne .Lactor_look_update_62\n\t"
      ".Lactor_look_update_60:\n\t"
      "movb -0x2(%%ebp), %%cl\n\t"
      "xorb %%al, %%al\n\t"
      "testb %%cl, %%cl\n\t"
      "movb %%al, -0x30(%%ebp)\n\t"
      "je .Lactor_look_update_66\n\t"
      "movb -0x6(%%ebp), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "je .Lactor_look_update_66\n\t"
      ".Lactor_look_update_61:\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_look_update_63\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "jmp .Lactor_look_update_64\n\t"
      ".Lactor_look_update_62:\n\t"
      "movb -0x2(%%ebp), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "je .Lactor_look_update_61\n\t"
      "movb -0x6(%%ebp), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "je .Lactor_look_update_61\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "movl $1, %%ecx\n\t"
      "jmp .Lactor_look_update_64\n\t"
      ".Lactor_look_update_63:\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      ".Lactor_look_update_64:\n\t"
      "movl -0x24(%%ebp), %%edx\n\t"
      "pushl %%ecx\n\t"
      "movl -0x30(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%ebx\n\t"
      "call *%[c28cc0]\n\t"
      "movb %%al, 0x55e(%%esi)\n\t"
      "movb 0x55c(%%esi), %%al\n\t"
      "addl $0x14, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_look_update_65\n\t"
      "movl 0x564(%%esi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jg .Lactor_look_update_65\n\t"
      "pushl $1\n\t"
      "pushl $0x5dd\n\t"
      "pushl $0x255284\n\t"
      "pushl $0x255678\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lactor_look_update_65:\n\t"
      "movb $1, -0xa(%%ebp)\n\t"
      ".Lactor_look_update_66:\n\t"
      "movb 0x55c(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_look_update_78\n\t"
      "movl 0x564(%%esi), %%ebx\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "decl %%ebx\n\t"
      "movl %%ebx, 0x564(%%esi)\n\t"
      "leal 0x56c(%%esi), %%ebx\n\t"
      "pushl %%eax\n\t"
      "leal -0x58(%%ebp), %%edi\n\t"
      "movl %%ebx, -0x30(%%ebp)\n\t"
      "call *%[c28660]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_look_update_78\n\t"
      "leal -0x58(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c21fb0]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lactor_look_update_67\n\t"
      "flds -0x50(%%ebp)\n\t"
      "pushl $1\n\t"
      "pushl $0x5e8\n\t"
      "pushl $0x255284\n\t"
      "subl $0x18, %%esp\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds -0x54(%%ebp)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds -0x58(%%ebp)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x255664\n\t"
      "pushl $0x254a24\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x24, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lactor_look_update_67:\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_look_update_71\n\t"
      "movb -0x3(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_look_update_68\n\t"
      "movb -0x8(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_look_update_68\n\t"
      "movb 0x99(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_look_update_68\n\t"
      "movb $1, -0x24(%%ebp)\n\t"
      "movb $1, -0x5(%%ebp)\n\t"
      "jmp .Lactor_look_update_69\n\t"
      ".Lactor_look_update_68:\n\t"
      "movb -0x24(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_look_update_70\n\t"
      ".Lactor_look_update_69:\n\t"
      "movl -0x58(%%ebp), %%eax\n\t"
      "movl -0x14(%%ebp), %%edi\n\t"
      "movl -0x54(%%ebp), %%ecx\n\t"
      "movl -0x50(%%ebp), %%edx\n\t"
      "movl -0x10(%%ebp), %%ebx\n\t"
      "movl %%eax, (%%edi)\n\t"
      "movl %%ecx, 0x4(%%edi)\n\t"
      "movl %%edx, 0x8(%%edi)\n\t"
      "movl %%ebx, %%edi\n\t"
      "movl %%eax, (%%edi)\n\t"
      "movl %%ecx, 0x4(%%edi)\n\t"
      "movl %%edx, 0x8(%%edi)\n\t"
      "movb $1, 0x58c(%%esi)\n\t"
      "jmp .Lactor_look_update_72\n\t"
      ".Lactor_look_update_70:\n\t"
      "movl -0x20(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl -0x14(%%ebp), %%edx\n\t"
      "leal -0x58(%%ebp), %%eax\n\t"
      "call *%[c27dd0]\n\t"
      "movl -0x10(%%ebp), %%ebx\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_look_update_79\n\t"
      "movl -0x58(%%ebp), %%ecx\n\t"
      "movl -0x54(%%ebp), %%edx\n\t"
      "movl %%ebx, %%eax\n\t"
      "movl %%ecx, (%%eax)\n\t"
      "movl -0x50(%%ebp), %%ecx\n\t"
      "movl %%edx, 0x4(%%eax)\n\t"
      "movl %%ecx, 0x8(%%eax)\n\t"
      "movb $1, 0x58c(%%esi)\n\t"
      "jmp .Lactor_look_update_72\n\t"
      ".Lactor_look_update_71:\n\t"
      "movl -0x2c(%%ebp), %%eax\n\t"
      "movl -0x10(%%ebp), %%ebx\n\t"
      "leal -0x4c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl -0x14(%%ebp), %%edx\n\t"
      "pushl %%eax\n\t"
      "leal -0x58(%%ebp), %%eax\n\t"
      "movl %%ebx, %%ecx\n\t"
      "call *%[c27e50]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_look_update_79\n\t"
      "movl -0x58(%%ebp), %%edx\n\t"
      "movl -0x18(%%ebp), %%ecx\n\t"
      "movl -0x54(%%ebp), %%eax\n\t"
      "movl %%edx, (%%ecx)\n\t"
      "movl -0x50(%%ebp), %%edx\n\t"
      "movl %%eax, 0x4(%%ecx)\n\t"
      "movl %%edx, 0x8(%%ecx)\n\t"
      ".Lactor_look_update_72:\n\t"
      "movb -0xa(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_look_update_74\n\t"
      "movb -0x6(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_look_update_74\n\t"
      "movl -0x1c(%%ebp), %%ecx\n\t"
      "xorl %%eax, %%eax\n\t"
      "movb 0x55e(%%esi), %%al\n\t"
      "movb $1, 0x55f(%%esi)\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "movl $2, %%edi\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c28250]\n\t"
      "movl -0x28(%%ebp), %%ecx\n\t"
      "movl %%eax, 0x568(%%ecx)\n\t"
      "movl -0x30(%%ebp), %%eax\n\t"
      "movl (%%eax), %%edx\n\t"
      "addl $0x57c, %%ecx\n\t"
      "movl %%edx, (%%ecx)\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl %%edx, 0x4(%%ecx)\n\t"
      "movl 0x8(%%eax), %%edx\n\t"
      "movl 0xc(%%eax), %%eax\n\t"
      "movl %%edx, 0x8(%%ecx)\n\t"
      "movl %%eax, 0xc(%%ecx)\n\t"
      "movb -0x24(%%ebp), %%al\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_look_update_73\n\t"
      "movl -0x28(%%ebp), %%ebx\n\t"
      "movl -0x1c(%%ebp), %%edx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movb 0x55e(%%ebx), %%cl\n\t"
      "xorl %%edi, %%edi\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c28250]\n\t"
      "addl $8, %%esp\n\t"
      "movl %%eax, 0x560(%%ebx)\n\t"
      ".Lactor_look_update_73:\n\t"
      "movl -0x28(%%ebp), %%esi\n\t"
      "movl -0x10(%%ebp), %%ebx\n\t"
      ".Lactor_look_update_74:\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_look_update_84\n\t"
      "movb -0x2(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_look_update_75\n\t"
      "movb -0x6(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lactor_look_update_76\n\t"
      ".Lactor_look_update_75:\n\t"
      "movb -0x5(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_look_update_84\n\t"
      "movb -0x7(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_look_update_84\n\t"
      ".Lactor_look_update_76:\n\t"
      "movl 0x568(%%esi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lactor_look_update_77\n\t"
      "movl -0x1c(%%ebp), %%edx\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "leal -0x58(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c28ed0]\n\t"
      "movl 0x568(%%esi), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jg .Lactor_look_update_77\n\t"
      "pushl $1\n\t"
      "pushl $0x62d\n\t"
      "pushl $0x255284\n\t"
      "pushl $0x255640\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lactor_look_update_77:\n\t"
      "movl 0x568(%%esi), %%ecx\n\t"
      "movb 0x55f(%%esi), %%al\n\t"
      "decl %%ecx\n\t"
      "testb %%al, %%al\n\t"
      "movl %%ecx, 0x568(%%esi)\n\t"
      "je .Lactor_look_update_88\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "leal 0x57c(%%esi), %%ebx\n\t"
      "pushl %%eax\n\t"
      "leal -0x58(%%ebp), %%edi\n\t"
      "call *%[c28660]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_look_update_86\n\t"
      "movb -0x5(%%ebp), %%bl\n\t"
      "testb %%bl, %%bl\n\t"
      "je .Lactor_look_update_80\n\t"
      "movl -0x20(%%ebp), %%ecx\n\t"
      "movl -0x14(%%ebp), %%edx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x58(%%ebp), %%eax\n\t"
      "call *%[c27dd0]\n\t"
      "addl $4, %%esp\n\t"
      "jmp .Lactor_look_update_81\n\t"
      ".Lactor_look_update_78:\n\t"
      "movl -0x10(%%ebp), %%ebx\n\t"
      ".Lactor_look_update_79:\n\t"
      "movl %%ebx, %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movb $0, 0x55c(%%esi)\n\t"
      "movl %%ecx, -0x58(%%ebp)\n\t"
      "movl %%edx, -0x54(%%ebp)\n\t"
      "movl %%eax, -0x50(%%ebp)\n\t"
      "jmp .Lactor_look_update_74\n\t"
      ".Lactor_look_update_80:\n\t"
      "movl -0x2c(%%ebp), %%eax\n\t"
      "movl -0x10(%%ebp), %%ecx\n\t"
      "leal -0x4c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl -0x14(%%ebp), %%edx\n\t"
      "pushl %%eax\n\t"
      "leal -0x58(%%ebp), %%eax\n\t"
      "call *%[c27e50]\n\t"
      "addl $8, %%esp\n\t"
      ".Lactor_look_update_81:\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_look_update_86\n\t"
      "leal -0x58(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c21fb0]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lactor_look_update_82\n\t"
      "flds -0x50(%%ebp)\n\t"
      "pushl $1\n\t"
      "pushl $0x645\n\t"
      "pushl $0x255284\n\t"
      "subl $0x18, %%esp\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds -0x54(%%ebp)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds -0x58(%%ebp)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x25562c\n\t"
      "pushl $0x254a24\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x24, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lactor_look_update_82:\n\t"
      "testb %%bl, %%bl\n\t"
      "movl -0x54(%%ebp), %%eax\n\t"
      "movl -0x58(%%ebp), %%ecx\n\t"
      "movl -0x50(%%ebp), %%edx\n\t"
      "je .Lactor_look_update_83\n\t"
      "movl -0x10(%%ebp), %%edi\n\t"
      "movl %%ecx, (%%edi)\n\t"
      "movl %%eax, 0x4(%%edi)\n\t"
      "movl %%edx, 0x8(%%edi)\n\t"
      ".Lactor_look_update_83:\n\t"
      "movl -0x18(%%ebp), %%edi\n\t"
      "movl %%ecx, (%%edi)\n\t"
      "movl %%eax, 0x4(%%edi)\n\t"
      "movl %%edx, 0x8(%%edi)\n\t"
      "jmp .Lactor_look_update_87\n\t"
      ".Lactor_look_update_84:\n\t"
      "movb $0, 0x55f(%%esi)\n\t"
      "jmp .Lactor_look_update_88\n\t"
      ".Lactor_look_update_85:\n\t"
      "movb $0, 0x55c(%%esi)\n\t"
      "movb $0, 0x55e(%%esi)\n\t"
      ".Lactor_look_update_86:\n\t"
      "movb $0, 0x55f(%%esi)\n\t"
      ".Lactor_look_update_87:\n\t"
      "movl -0x10(%%ebp), %%ebx\n\t"
      ".Lactor_look_update_88:\n\t"
      "movb 0x504(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lactor_look_update_91\n\t"
      "movb 0x505(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lactor_look_update_91\n\t"
      "movl 0x18(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c1a9ad0]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lactor_look_update_91\n\t"
      "cmpl $-1, 0x158(%%esi)\n\t"
      "jne .Lactor_look_update_91\n\t"
      "movl -0x20(%%ebp), %%edi\n\t"
      "movl -0x14(%%ebp), %%edx\n\t"
      "pushl %%edi\n\t"
      "movl %%ebx, %%eax\n\t"
      "call *%[c27dd0]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_look_update_89\n\t"
      "leal 0x174(%%esi), %%edx\n\t"
      "pushl %%edi\n\t"
      "movl %%ebx, %%eax\n\t"
      "call *%[c27dd0]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_look_update_90\n\t"
      ".Lactor_look_update_89:\n\t"
      "movb -0x4(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_look_update_92\n\t"
      "movl -0x2c(%%ebp), %%edi\n\t"
      "movl -0x14(%%ebp), %%edx\n\t"
      "leal -0x4c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl -0x18(%%ebp), %%eax\n\t"
      "pushl %%edi\n\t"
      "movl %%ebx, %%ecx\n\t"
      "call *%[c27e50]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_look_update_91\n\t"
      "movl -0x18(%%ebp), %%eax\n\t"
      "leal -0x4c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal 0x174(%%esi), %%edx\n\t"
      "pushl %%edi\n\t"
      "movl %%ebx, %%ecx\n\t"
      "call *%[c27e50]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lactor_look_update_91\n\t"
      ".Lactor_look_update_90:\n\t"
      "movb $1, 0x591(%%esi)\n\t"
      ".Lactor_look_update_91:\n\t"
      "movb -0x4(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lactor_look_update_93\n\t"
      ".Lactor_look_update_92:\n\t"
      "movl -0x18(%%ebp), %%eax\n\t"
      "movl %%ebx, %%edx\n\t"
      "movl (%%edx), %%ecx\n\t"
      "movl %%ecx, (%%eax)\n\t"
      "movl 0x4(%%edx), %%ecx\n\t"
      "movl 0x8(%%edx), %%edx\n\t"
      "movl %%ecx, 0x4(%%eax)\n\t"
      "movl %%edx, 0x8(%%eax)\n\t"
      ".Lactor_look_update_93:\n\t"
      "movb 0x99(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lactor_look_update_95\n\t"
      "flds 0x5ac(%%esi)\n\t"
      "fabs\n\t"
      "fcompl 0x2533d0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .Lactor_look_update_94\n\t"
      "movl -0x14(%%ebp), %%edi\n\t"
      "pushl %%edi\n\t"
      "movl $0, 0x5ac(%%esi)\n\t"
      "call *%[mag]\n\t"
      "fcomps 0x2533c0\n\t"
      "addl $4, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .Lactor_look_update_94\n\t"
      "leal 0x174(%%esi), %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl %%ecx, (%%edi)\n\t"
      "movl %%edx, 0x4(%%edi)\n\t"
      "movl %%eax, 0x8(%%edi)\n\t"
      ".Lactor_look_update_94:\n\t"
      "leal 0x6fc(%%esi), %%edi\n\t"
      "pushl %%edi\n\t"
      "call *%[c28610]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lactor_look_update_95\n\t"
      "flds 0x700(%%esi)\n\t"
      "pushl $1\n\t"
      "pushl $0x689\n\t"
      "pushl $0x255284\n\t"
      "subl $0x10, %%esp\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds (%%edi)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x2555fc\n\t"
      "pushl $0x2555d4\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x1c, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lactor_look_update_95:\n\t"
      "movb 0x58f(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_look_update_100\n\t"
      "movb 0x590(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lactor_look_update_96\n\t"
      "movb 0x504(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lactor_look_update_101\n\t"
      "flds 0x188(%%esi)\n\t"
      "fmuls 0x8(%%ebx)\n\t"
      "flds 0x184(%%esi)\n\t"
      "fmuls 0x4(%%ebx)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds 0x180(%%esi)\n\t"
      "fmuls (%%ebx)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fcomps 0x2555d0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lactor_look_update_101\n\t"
      "movl -0x14(%%ebp), %%edx\n\t"
      "movl (%%edx), %%eax\n\t"
      "leal 0x598(%%esi), %%ecx\n\t"
      "movl %%eax, (%%ecx)\n\t"
      "movl 0x4(%%edx), %%eax\n\t"
      "movl 0x8(%%edx), %%edx\n\t"
      "movl %%eax, 0x4(%%ecx)\n\t"
      "movb $1, 0x590(%%esi)\n\t"
      "movl %%edx, 0x8(%%ecx)\n\t"
      "jmp .Lactor_look_update_101\n\t"
      ".Lactor_look_update_96:\n\t"
      "movl -0x40(%%ebp), %%ecx\n\t"
      "flds 0x330(%%ecx)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lactor_look_update_101\n\t"
      "flds 0x330(%%ecx)\n\t"
      "movb 0x99(%%esi), %%al\n\t"
      "fcos\n\t"
      "testb %%al, %%al\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "fstps -0x2c(%%ebp)\n\t"
      "je .Lactor_look_update_97\n\t"
      "flds 0x8(%%eax)\n\t"
      "leal 0x598(%%esi), %%ecx\n\t"
      "fmuls 0x8(%%ecx)\n\t"
      "flds 0x4(%%eax)\n\t"
      "fmuls 0x4(%%ecx)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds (%%eax)\n\t"
      "fmuls (%%ecx)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fcomps -0x2c(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lactor_look_update_99\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "call *%[c13070]\n\t"
      "addl $8, %%esp\n\t"
      "jmp .Lactor_look_update_98\n\t"
      ".Lactor_look_update_97:\n\t"
      "movl (%%eax), %%ecx\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl (%%ebx), %%eax\n\t"
      "movl %%ecx, -0x44(%%ebp)\n\t"
      "movl 0x4(%%ebx), %%ecx\n\t"
      "movl %%ecx, -0x30(%%ebp)\n\t"
      "movl %%edx, -0x40(%%ebp)\n\t"
      "movl 0x598(%%esi), %%edx\n\t"
      "movl %%eax, -0x34(%%ebp)\n\t"
      "movl 0x59c(%%esi), %%eax\n\t"
      "leal -0x44(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl %%edx, -0x4c(%%ebp)\n\t"
      "movl %%eax, -0x48(%%ebp)\n\t"
      "call *%[mag]\n\t"
      "fcomps 0x2533c0\n\t"
      "addl $4, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .Lactor_look_update_99\n\t"
      "leal -0x34(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[mag]\n\t"
      "fcomps 0x2533c0\n\t"
      "addl $4, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .Lactor_look_update_99\n\t"
      "leal -0x4c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[mag]\n\t"
      "fcomps 0x2533c0\n\t"
      "addl $4, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .Lactor_look_update_99\n\t"
      "flds -0x48(%%ebp)\n\t"
      "fmuls -0x40(%%ebp)\n\t"
      "flds -0x4c(%%ebp)\n\t"
      "fmuls -0x44(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fcomps -0x2c(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lactor_look_update_99\n\t"
      "flds -0x30(%%ebp)\n\t"
      "fmuls -0x48(%%ebp)\n\t"
      "flds -0x34(%%ebp)\n\t"
      "fmuls -0x4c(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      ".Lactor_look_update_98:\n\t"
      "fcomps -0x2c(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .Lactor_look_update_101\n\t"
      ".Lactor_look_update_99:\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movb $0, 0x590(%%esi)\n\t"
      "call *%[c36e50]\n\t"
      "addl $4, %%esp\n\t"
      "jmp .Lactor_look_update_101\n\t"
      ".Lactor_look_update_100:\n\t"
      "movb $0, 0x590(%%esi)\n\t"
      ".Lactor_look_update_101:\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "leal 0x6fc(%%esi), %%edi\n\t"
      "movl %%edi, %%edx\n\t"
      "movl %%ecx, (%%edx)\n\t"
      "movl 0x4(%%eax), %%ecx\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl %%ecx, 0x4(%%edx)\n\t"
      "movl (%%ebx), %%ecx\n\t"
      "movl %%eax, 0x8(%%edx)\n\t"
      "movl 0x4(%%ebx), %%edx\n\t"
      "leal 0x708(%%esi), %%eax\n\t"
      "movl %%ecx, (%%eax)\n\t"
      "movl 0x8(%%ebx), %%ecx\n\t"
      "movl %%edx, 0x4(%%eax)\n\t"
      "movl %%ecx, 0x8(%%eax)\n\t"
      "movl -0x18(%%ebp), %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "leal 0x714(%%esi), %%ebx\n\t"
      "movl %%ebx, %%edx\n\t"
      "movl %%ecx, (%%edx)\n\t"
      "movl 0x4(%%eax), %%ecx\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl %%ecx, 0x4(%%edx)\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movb 0x591(%%esi), %%cl\n\t"
      "movl %%eax, 0x8(%%edx)\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c3c3a0]\n\t"
      "pushl %%edi\n\t"
      "call *%[c21fb0]\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lactor_look_update_102\n\t"
      "flds 0x704(%%esi)\n\t"
      "pushl $1\n\t"
      "pushl $0x6c8\n\t"
      "pushl $0x255284\n\t"
      "subl $0x18, %%esp\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds 0x700(%%esi)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds (%%edi)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x2555b0\n\t"
      "pushl $0x254a24\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x24, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lactor_look_update_102:\n\t"
      "leal 0x708(%%esi), %%edi\n\t"
      "pushl %%edi\n\t"
      "call *%[c21fb0]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lactor_look_update_103\n\t"
      "flds 0x710(%%esi)\n\t"
      "pushl $1\n\t"
      "pushl $0x6c9\n\t"
      "pushl $0x255284\n\t"
      "subl $0x18, %%esp\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds 0x70c(%%esi)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds (%%edi)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x255590\n\t"
      "pushl $0x254a24\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x24, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lactor_look_update_103:\n\t"
      "pushl %%ebx\n\t"
      "call *%[c21fb0]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lactor_look_update_104\n\t"
      "flds 0x71c(%%esi)\n\t"
      "pushl $1\n\t"
      "pushl $0x6ca\n\t"
      "pushl $0x255284\n\t"
      "subl $0x18, %%esp\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds 0x718(%%esi)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds (%%ebx)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x255570\n\t"
      "pushl $0x254a24\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x24, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lactor_look_update_104:\n\t"
      "movb -0x9(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "popl %%ebx\n\t"
      "jne .Lactor_look_update_105\n\t"
      "cmpw $4, 0x3fc(%%esi)\n\t"
      "je .Lactor_look_update_105\n\t"
      "movswl 0x544(%%esi), %%eax\n\t"
      "addl $-3, %%eax\n\t"
      "cmpl $9, %%eax\n\t"
      "ja .Lactor_look_update_106\n\t"
      "movzbl 0x2a2a0(%%eax), %%eax\n\t"
      "jmp *.Lactor_look_update_jt1(,%%eax,4)\n\t"
      ".Lactor_look_update_105:\n\t"
      "popl %%edi\n\t"
      "movw $0, 0x6f8(%%esi)\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lactor_look_update_106:\n\t"
      "popl %%edi\n\t"
      "movw $1, 0x6f8(%%esi)\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".Lactor_look_update_jt0:\n\t"
      ".long .Lactor_look_update_27\n\t"
      ".long .Lactor_look_update_39\n\t"
      ".text\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".Lactor_look_update_jt1:\n\t"
      ".long .Lactor_look_update_105\n\t"
      ".long .Lactor_look_update_106\n\t"
      ".text\n\t"
      :
      : [dget] "m"(b29040_dget), [tag] "m"(b29040_tag), [c21fb0] "m"(b29040_c21fb0), [c8d9d0] "m"(b29040_c8d9d0), [assert] "m"(b29040_assert), [exitfn] "m"(b29040_exitfn), [c3b270] "m"(b29040_c3b270), [c210b0] "m"(b29040_c210b0), [c28660] "m"(b29040_c28660), [c1d6d0] "m"(b29040_c1d6d0), [c49ac0] "m"(b29040_c49ac0), [cff4d0] "m"(b29040_cff4d0), [c27dd0] "m"(b29040_c27dd0), [c2a860] "m"(b29040_c2a860), [c27e50] "m"(b29040_c27e50), [c27a10] "m"(b29040_c27a10), [c28250] "m"(b29040_c28250), [c28cc0] "m"(b29040_c28cc0), [c28ed0] "m"(b29040_c28ed0), [c1a9ad0] "m"(b29040_c1a9ad0), [mag] "m"(b29040_mag), [c28610] "m"(b29040_c28610), [c13070] "m"(b29040_c13070), [c36e50] "m"(b29040_c36e50), [c3c3a0] "m"(b29040_c3c3a0)
      : "memory");
}
#else
#error "actor_look_update: clang naked draft required"
#endif


/* FUN_0002a2b0 (0x2a2b0) — readable C lift from XBE leaf. */
void FUN_0002a2b0(int actor_handle)
{
  void *actor;
  short *look_spec;
  float *direction;
  char ok;

  actor = datum_get(*(void **)0x6325a4, actor_handle);
  look_spec = (short *)((char *)actor + 0x3ec);
  if (*look_spec == 0) {
    if (!FUN_0002a3d0(actor_handle)) {
      *(short *)((char *)actor + 0x3e8) = 0;
    }
  }
  if (*(short *)((char *)actor + 0x3e8) >= 3 && *look_spec != 0) {
    direction = (float *)((char *)actor + 0x524);
    /* Match XBE: look_spec@ebx, direction@edi, actor on stack. */
    {
      char (*fn)(int) = (char (*)(int))(void *)FUN_00028660;
      register short *b asm("ebx") = look_spec;
      register float *d asm("edi") = direction;
      ok = fn(actor_handle);
      (void)b;
      (void)d;
    }
    if (ok) {
      *(unsigned char *)((char *)actor + 0x505) = 1;
      return;
    }
  }
  *(unsigned char *)((char *)actor + 0x505) = 0;
}




/* FUN_0002a330 (0x2a330) — Set actor 'looking' active flags.
 * Sets the byte at actor+0x402 and actor+0x46e both to 1. */
void FUN_0002a330(int actor_handle)
{
  char *actor;
  actor = (char *)datum_get(actor_data, actor_handle);
  *(char *)(actor + 0x402) = 1;
  *(char *)(actor + 0x46e) = 1;
}

/* FUN_0002a3d0 (0x2a3d0)
 * Return the in-vehicle / mounted flag byte for the actor.
 *
 * Looks up the actor record via datum_get(actor_data, actor_handle) and
 * returns the byte at actor+0x4a8.  Non-zero means the actor is currently
 * mounted in or on a vehicle.
 *
 * Confirmed: cdecl, single stack arg (actor_handle).
 * Confirmed: datum_get(actor_data=DAT_006325a4, actor_handle) at 0x2a3de.
 * Confirmed: MOV AL,byte ptr [EAX+0x4a8] at 0x2a3e3; ADD ESP,0x8; RET. */
char FUN_0002a3d0(int actor_handle)
{
  char *actor = (char *)datum_get(actor_data, actor_handle);
  return actor[0x4a8];
}

/* FUN_0002a3f0 (0x2a3f0) — Check if actor can move (not on active path and
 * is_moving). Returns 0 if path_active (+0x4a8) is set AND is_moving (+0x484)
 * is clear, else 1. */
int FUN_0002a3f0(int actor_handle)
{
  char *actor;

  actor = (char *)datum_get(actor_data, actor_handle);
  if (*(char *)(actor + 0x4a8) != 0 && *(char *)(actor + 0x484) == 0)
    return 0;
  return 1;
}

/* FUN_0002a430 (0x2a430) — Get actor activation value if activation state is 3.
 * Returns actor[+0x470] (short) if actor[+0x46c] == 3, else -1. */
short FUN_0002a430(int actor_handle)
{
  char *actor;

  actor = (char *)datum_get(actor_data, actor_handle);
  if (*(short *)(actor + 0x46c) == 3)
    return *(short *)(actor + 0x470);
  return -1;
}
