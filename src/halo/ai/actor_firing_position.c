#include <stdint.h>
/* --- actor_firing_position.obj batch drafts (2026-07-26) --- */

/* FUN_00024000 (0x24000) — XBE naked draft (batch 160). */
#if defined(__clang__)
static void (*const b24000_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b24000_exitfn)(int) = system_exit;

__attribute__((naked, noinline))
void FUN_00024000(void *ctx __attribute__((unused)), float score __attribute__((unused)), int type __attribute__((unused)), void *position __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_00024000_1\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fcomps 0x254cb8\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .LFUN_00024000_2\n\t"
      ".LFUN_00024000_1:\n\t"
      "pushl $1\n\t"
      "pushl $0x81\n\t"
      "pushl $0x254c8c\n\t"
      "pushl $0x254c5c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00024000_2:\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fadds 0x38(%%esi)\n\t"
      "fstps 0x38(%%esi)\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b24000_assert), [exitfn] "m"(b24000_exitfn)
      : "memory");
}
#else
#error "FUN_00024000: clang naked draft required"
#endif


/* FUN_00024060 (0x24060) — XBE naked draft (batch 139). */
#if defined(__clang__)
static void (*const b24060_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b24060_exitfn)(int) = system_exit;

__attribute__((naked, noinline))
void FUN_00024060(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movw 0x10(%%ebp), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "jle .LFUN_00024060_6\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x14(%%ebp), %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "addl $8, %%esi\n\t"
      "movzwl %%ax, %%ebx\n\t"
      "nop\n\t"
      ".LFUN_00024060_1:\n\t"
      "movb 0x28(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00024060_5\n\t"
      "flds 0x18(%%edi)\n\t"
      "movl $0, 0x10(%%ebp)\n\t"
      "fmuls 0x253398\n\t"
      "fstps 0x14(%%ebp)\n\t"
      "flds (%%esi)\n\t"
      "fcomps 0x14(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00024060_2\n\t"
      "movl $0x41000000, 0x10(%%ebp)\n\t"
      "jmp .LFUN_00024060_4\n\t"
      ".LFUN_00024060_2:\n\t"
      "flds (%%esi)\n\t"
      "fcomps 0x18(%%edi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00024060_4\n\t"
      "flds 0x18(%%edi)\n\t"
      "fsubs (%%esi)\n\t"
      "flds 0x2533c8\n\t"
      "fdivs 0x14(%%ebp)\n\t"
      ".byte 0xde, 0xc9\n\t"
      "fmuls 0x253f78\n\t"
      "fsts 0x10(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_00024060_3\n\t"
      "flds 0x10(%%ebp)\n\t"
      "fcomps 0x254cb8\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .LFUN_00024060_4\n\t"
      ".LFUN_00024060_3:\n\t"
      "pushl $1\n\t"
      "pushl $0x81\n\t"
      "pushl $0x254c8c\n\t"
      "pushl $0x254c5c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00024060_4:\n\t"
      "flds 0x10(%%ebp)\n\t"
      "fadds 0x30(%%esi)\n\t"
      "fstps 0x30(%%esi)\n\t"
      ".LFUN_00024060_5:\n\t"
      "addl $0x3c, %%esi\n\t"
      "decl %%ebx\n\t"
      "jne .LFUN_00024060_1\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      ".LFUN_00024060_6:\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b24060_assert), [exitfn] "m"(b24060_exitfn)
      : "memory");
}
#else
#error "FUN_00024060: clang naked draft required"
#endif


/* FUN_00024130 (0x24130) — XBE naked draft (batch 115). */
#if defined(__clang__)
static void *(*const b24130_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static char * (*const b24130_c211f0)(int actor_handle) = actor_combat_get_firing_variant_definition;
static void (*const b24130_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b24130_exitfn)(int) = system_exit;
static void (*const b24130_c30b80)(void) = actor_perception_aiming_vector_test_blockage;

__attribute__((naked, noinline))
void FUN_00024130(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xc, %%esp\n\t"
      "movl 0x6325a4, %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "pushl %%esi\n\t"
      "call *%[c211f0]\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "movw 0x10(%%ebp), %%bx\n\t"
      "movl %%eax, %%ecx\n\t"
      "movb 0x5fc(%%edx), %%al\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "movl $0x41000000, -0x4(%%ebp)\n\t"
      "je .LFUN_00024130_1\n\t"
      "flds 0x600(%%edx)\n\t"
      "fcomps 0x74(%%ecx)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .LFUN_00024130_7\n\t"
      "flds 0x600(%%edx)\n\t"
      "fdivs 0x74(%%ecx)\n\t"
      "fsubrs 0x2533c8\n\t"
      "fmuls 0x253f78\n\t"
      "fsts -0x4(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00024130_7\n\t"
      ".LFUN_00024130_1:\n\t"
      "testw %%bx, %%bx\n\t"
      "jle .LFUN_00024130_7\n\t"
      "movl 0x14(%%ebp), %%esi\n\t"
      "addl $8, %%esi\n\t"
      "movzwl %%bx, %%edi\n\t"
      "leal (%%ebx), %%ebx\n\t"
      ".LFUN_00024130_2:\n\t"
      "movb 0x28(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00024130_6\n\t"
      "flds (%%esi)\n\t"
      "fcomps 0x18(%%edx)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00024130_6\n\t"
      "flds (%%esi)\n\t"
      "fdivs 0x18(%%edx)\n\t"
      "fsubrs 0x2533c8\n\t"
      "flds 0x2533c0\n\t"
      "fcomp %%st(1)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00024130_3\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c0\n\t"
      ".LFUN_00024130_3:\n\t"
      "fmuls -0x4(%%ebp)\n\t"
      "fsts -0x8(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_00024130_4\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fcomps 0x254cb8\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .LFUN_00024130_5\n\t"
      ".LFUN_00024130_4:\n\t"
      "pushl $1\n\t"
      "pushl $0x81\n\t"
      "pushl $0x254c8c\n\t"
      "pushl $0x254c5c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00024130_5:\n\t"
      "flds -0x8(%%ebp)\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "fadds 0x30(%%esi)\n\t"
      "fstps 0x30(%%esi)\n\t"
      ".LFUN_00024130_6:\n\t"
      "addl $0x3c, %%esi\n\t"
      "decl %%edi\n\t"
      "jne .LFUN_00024130_2\n\t"
      ".LFUN_00024130_7:\n\t"
      "cmpw $0, 0x256(%%edx)\n\t"
      "jle .LFUN_00024130_20\n\t"
      "testw %%bx, %%bx\n\t"
      "jle .LFUN_00024130_20\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "movzwl %%bx, %%ecx\n\t"
      "addl $0x38, %%eax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "movl %%ecx, -0xc(%%ebp)\n\t"
      ".LFUN_00024130_8:\n\t"
      "movb -0x8(%%eax), %%cl\n\t"
      "xorl %%edi, %%edi\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "testb %%cl, %%cl\n\t"
      "movl %%edi, -0x4(%%ebp)\n\t"
      "je .LFUN_00024130_19\n\t"
      "cmpw %%di, 0x254(%%edx)\n\t"
      "jle .LFUN_00024130_17\n\t"
      ".LFUN_00024130_9:\n\t"
      "movswl %%di, %%eax\n\t"
      "imull $0x1c, %%eax, %%eax\n\t"
      "leal (%%eax,%%edx,1), %%esi\n\t"
      "movw 0x25c(%%esi), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "je .LFUN_00024130_10\n\t"
      "cmpw $1, %%ax\n\t"
      "jne .LFUN_00024130_13\n\t"
      ".LFUN_00024130_10:\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movl -0x38(%%ecx), %%edx\n\t"
      "pushl $0\n\t"
      "pushl %%edx\n\t"
      "leal 0x26c(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal 0x260(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c30b80]\n\t"
      "movw 0x25c(%%esi), %%si\n\t"
      "addl $0x10, %%esp\n\t"
      "testw %%si, %%si\n\t"
      "jne .LFUN_00024130_12\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "cmpw %%ax, %%cx\n\t"
      "jle .LFUN_00024130_11\n\t"
      "movl %%ecx, -0x4(%%ebp)\n\t"
      "jmp .LFUN_00024130_13\n\t"
      ".LFUN_00024130_11:\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "jmp .LFUN_00024130_13\n\t"
      ".LFUN_00024130_12:\n\t"
      "cmpw $1, %%si\n\t"
      "jne .LFUN_00024130_13\n\t"
      "cmpw %%ax, %%bx\n\t"
      "jg .LFUN_00024130_13\n\t"
      "movl %%eax, %%ebx\n\t"
      ".LFUN_00024130_13:\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "incl %%edi\n\t"
      "cmpw 0x254(%%edx), %%di\n\t"
      "jl .LFUN_00024130_9\n\t"
      "cmpw $2, %%bx\n\t"
      "jl .LFUN_00024130_14\n\t"
      "flds 0x2533c0\n\t"
      "jmp .LFUN_00024130_18\n\t"
      ".LFUN_00024130_14:\n\t"
      "cmpw $1, %%bx\n\t"
      "jl .LFUN_00024130_15\n\t"
      "flds 0x2533ec\n\t"
      "jmp .LFUN_00024130_18\n\t"
      ".LFUN_00024130_15:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "cmpw $2, %%ax\n\t"
      "jl .LFUN_00024130_16\n\t"
      "flds 0x254640\n\t"
      "jmp .LFUN_00024130_18\n\t"
      ".LFUN_00024130_16:\n\t"
      "cmpw $1, %%ax\n\t"
      "jl .LFUN_00024130_17\n\t"
      "flds 0x254cbc\n\t"
      "jmp .LFUN_00024130_18\n\t"
      ".LFUN_00024130_17:\n\t"
      "flds 0x253f34\n\t"
      ".LFUN_00024130_18:\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "fadds (%%eax)\n\t"
      "fstps (%%eax)\n\t"
      ".LFUN_00024130_19:\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "addl $0x3c, %%eax\n\t"
      "decl %%ecx\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "movl %%ecx, -0xc(%%ebp)\n\t"
      "jne .LFUN_00024130_8\n\t"
      ".LFUN_00024130_20:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [dget] "m"(b24130_dget), [c211f0] "m"(b24130_c211f0), [assert] "m"(b24130_assert), [exitfn] "m"(b24130_exitfn), [c30b80] "m"(b24130_c30b80)
      : "memory");
}
#else
#error "FUN_00024130: clang naked draft required"
#endif


/* FUN_00024370 (0x24370) — XBE naked draft (batch 132). */
#if defined(__clang__)
static void *(*const b24370_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void *(*const b24370_tag)(int, int) = tag_get;
static char (*const b24370_c2b720)(int actor_handle, float *dest_pos, float *dist_out) = actor_path_3d_available;
static void * (*const b24370_c18e3c0)(void) = scenario_get;
static char (*const b24370_c5e830)(int param_1, int *param_2, int param_3, int *param_4, unsigned char *param_5, float *param_6) = path_3d_available;
static void (*const b24370_c24000)(void *ctx, float score, int type, void *position) = FUN_00024000;

__attribute__((naked, noinline))
void FUN_00024370(void)
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
      "movl 0x58(%%edi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x61637472\n\t"
      "call *%[tag]\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "movb 0x44(%%eax), %%cl\n\t"
      "movl 0x10(%%ebp), %%esi\n\t"
      "addl $0x10, %%esp\n\t"
      "testb %%cl, %%cl\n\t"
      "je .LFUN_00024370_3\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LFUN_00024370_1\n\t"
      "flds 0x660(%%eax)\n\t"
      "popl %%edi\n\t"
      "fadds 0x254cc0\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "fstps 0x660(%%eax)\n\t"
      "movl $1, %%eax\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00024370_1:\n\t"
      "movl (%%esi), %%eax\n\t"
      "leal 0x10(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "movl $0, 0x10(%%ebp)\n\t"
      "call *%[c2b720]\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00024370_2\n\t"
      "movl (%%esi), %%ecx\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "addl $0x12c, %%edi\n\t"
      "pushl %%edi\n\t"
      "call *%[c18e3c0]\n\t"
      "pushl %%eax\n\t"
      "call *%[c5e830]\n\t"
      "addl $0x18, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00024370_2\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "pushl $0x19\n\t"
      "pushl $0x41700000\n\t"
      "pushl %%eax\n\t"
      "call *%[c24000]\n\t"
      "addl $0xc, %%esp\n\t"
      "jmp .LFUN_00024370_3\n\t"
      ".LFUN_00024370_2:\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "movb $1, 0x31(%%esi)\n\t"
      "movb 0x14(%%ecx), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00024370_3\n\t"
      "movb $0, 0x30(%%esi)\n\t"
      ".LFUN_00024370_3:\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LFUN_00024370_4\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl $1, %%eax\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00024370_4:\n\t"
      "movzbl 0x30(%%esi), %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [dget] "m"(b24370_dget), [tag] "m"(b24370_tag), [c2b720] "m"(b24370_c2b720), [c18e3c0] "m"(b24370_c18e3c0), [c5e830] "m"(b24370_c5e830), [c24000] "m"(b24370_c24000)
      : "memory");
}
#else
#error "FUN_00024370: clang naked draft required"
#endif


/* FUN_00024450 (0x24450) — XBE naked draft (batch 120). */
#if defined(__clang__)
static void *(*const b24450_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static int (*const b24450_gtime)(void) = game_time_get;
static char (*const b24450_c5b5e0)(int encounter_handle, int position_hash, int16_t pursuit_index, int min_time) = encounter_mark_examined_pursuit_position;
static char (*const b24450_c5b6e0)(int encounter_handle, int position_hash, int16_t pursuit_index, int min_time, int16_t *out_count, int *out_time) = encounter_pursuit_position_already_examined;
static void (*const b24450_c24000)(void *ctx, float score, int type, void *position) = FUN_00024000;

__attribute__((naked, noinline))
void FUN_00024450(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x10, %%esp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl 0x6325a4, %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "addl $8, %%esp\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "call *%[gtime]\n\t"
      "movl 0x10(%%ebp), %%esi\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "xorl %%eax, %%eax\n\t"
      "cmpl %%eax, %%esi\n\t"
      "movl $0xffffffff, -0x4(%%ebp)\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "je .LFUN_00024450_10\n\t"
      "cmpw %%ax, 0x6(%%esi)\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "movb $1, %%bl\n\t"
      "jne .LFUN_00024450_1\n\t"
      "flds 0x8(%%esi)\n\t"
      "fcomps 0x254640\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00024450_1\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "movl 0xc(%%edi), %%edx\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x4(%%esi), %%ax\n\t"
      "pushl %%edx\n\t"
      "movl -0x10(%%ebp), %%edx\n\t"
      "pushl %%eax\n\t"
      "movl 0x34(%%edx), %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "call *%[c5b5e0]\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movl %%eax, %%ecx\n\t"
      "addl $0x10, %%esp\n\t"
      "movl %%ecx, -0x4(%%ebp)\n\t"
      "movl $7, -0xc(%%ebp)\n\t"
      "jmp .LFUN_00024450_2\n\t"
      ".LFUN_00024450_1:\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "movl 0xc(%%edi), %%eax\n\t"
      "leal -0x4(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x4(%%esi), %%cx\n\t"
      "leal -0xc(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "pushl %%eax\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "pushl %%ecx\n\t"
      "movl 0x34(%%eax), %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c5b6e0]\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "addl $0x18, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "je .LFUN_00024450_3\n\t"
      ".LFUN_00024450_2:\n\t"
      "xorb %%bl, %%bl\n\t"
      ".LFUN_00024450_3:\n\t"
      "movb 0x10(%%edi), %%dl\n\t"
      "testb %%dl, %%dl\n\t"
      "je .LFUN_00024450_4\n\t"
      "testb %%bl, %%bl\n\t"
      "je .LFUN_00024450_5\n\t"
      "pushl $7\n\t"
      "pushl $0x41700000\n\t"
      "pushl %%edi\n\t"
      "call *%[c24000]\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "jmp .LFUN_00024450_5\n\t"
      ".LFUN_00024450_4:\n\t"
      "testb %%bl, %%bl\n\t"
      "jne .LFUN_00024450_5\n\t"
      "movb $1, 0x31(%%esi)\n\t"
      "movb 0x14(%%edi), %%dl\n\t"
      "testb %%dl, %%dl\n\t"
      "jne .LFUN_00024450_5\n\t"
      "movb %%bl, 0x30(%%esi)\n\t"
      ".LFUN_00024450_5:\n\t"
      "movb 0x30(%%esi), %%dl\n\t"
      "testb %%dl, %%dl\n\t"
      "je .LFUN_00024450_9\n\t"
      "cmpl $-1, %%ecx\n\t"
      "movl $0, 0x10(%%ebp)\n\t"
      "je .LFUN_00024450_6\n\t"
      "leal 0x12c(%%ecx), %%edx\n\t"
      "cmpl %%eax, %%edx\n\t"
      "jl .LFUN_00024450_6\n\t"
      "cmpl %%eax, %%ecx\n\t"
      "jge .LFUN_00024450_7\n\t"
      "subl %%ecx, %%eax\n\t"
      "movl %%eax, 0x10(%%ebp)\n\t"
      "fildl 0x10(%%ebp)\n\t"
      "fmuls 0x2546a4\n\t"
      "fstps 0x10(%%ebp)\n\t"
      "jmp .LFUN_00024450_7\n\t"
      ".LFUN_00024450_6:\n\t"
      "movl $0x41200000, 0x10(%%ebp)\n\t"
      ".LFUN_00024450_7:\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "pushl $5\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "call *%[c24000]\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpw $4, %%ax\n\t"
      "movl $0, 0x10(%%ebp)\n\t"
      "jge .LFUN_00024450_8\n\t"
      "movswl %%ax, %%ecx\n\t"
      "movl $4, %%edx\n\t"
      "subl %%ecx, %%edx\n\t"
      "movl %%edx, 0x10(%%ebp)\n\t"
      "fildl 0x10(%%ebp)\n\t"
      "fmuls 0x254cc4\n\t"
      "fstps 0x10(%%ebp)\n\t"
      ".LFUN_00024450_8:\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "pushl $6\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "call *%[c24000]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_00024450_9:\n\t"
      "movzbl 0x30(%%esi), %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%ebx\n\t"
      ".LFUN_00024450_10:\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [dget] "m"(b24450_dget), [gtime] "m"(b24450_gtime), [c5b5e0] "m"(b24450_c5b5e0), [c5b6e0] "m"(b24450_c5b6e0), [c24000] "m"(b24450_c24000)
      : "memory");
}
#else
#error "FUN_00024450: clang naked draft required"
#endif


/* post_evaluator_hide (0x245d0) — XBE naked draft (batch 135). */
#if defined(__clang__)
static void (*const b245d0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b245d0_exitfn)(int) = system_exit;
static void (*const b245d0_c24000)(void *ctx, float score, int type, void *position) = FUN_00024000;

__attribute__((naked, noinline))
void post_evaluator_hide(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%esi\n\t"
      "movl 0x10(%%ebp), %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "movb 0x5fc(%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lpost_evaluator_hide_9\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .Lpost_evaluator_hide_1\n\t"
      "flds 0x660(%%edi)\n\t"
      "movl $1, %%eax\n\t"
      "fadds 0x254cc8\n\t"
      "fstps 0x660(%%edi)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lpost_evaluator_hide_1:\n\t"
      "movswl 0x6(%%esi), %%eax\n\t"
      "cmpl $4, %%eax\n\t"
      "movl $0, 0xc(%%ebp)\n\t"
      "ja .Lpost_evaluator_hide_7\n\t"
      "jmp *.Lpost_evaluator_hide_jt(,%%eax,4)\n\t"
      ".Lpost_evaluator_hide_2:\n\t"
      "movl $0x41400000, 0xc(%%ebp)\n\t"
      "jmp .Lpost_evaluator_hide_8\n\t"
      ".Lpost_evaluator_hide_3:\n\t"
      "movl $0x41200000, 0xc(%%ebp)\n\t"
      "jmp .Lpost_evaluator_hide_8\n\t"
      ".Lpost_evaluator_hide_4:\n\t"
      "movb 0x8(%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lpost_evaluator_hide_6\n\t"
      "movl $0x40c00000, 0xc(%%ebp)\n\t"
      "jmp .Lpost_evaluator_hide_8\n\t"
      ".Lpost_evaluator_hide_5:\n\t"
      "movl $0x40800000, 0xc(%%ebp)\n\t"
      "jmp .Lpost_evaluator_hide_8\n\t"
      ".Lpost_evaluator_hide_6:\n\t"
      "movb $1, 0x31(%%esi)\n\t"
      "movb 0x14(%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lpost_evaluator_hide_8\n\t"
      "movb $0, 0x30(%%esi)\n\t"
      "jmp .Lpost_evaluator_hide_8\n\t"
      ".Lpost_evaluator_hide_7:\n\t"
      "pushl $1\n\t"
      "pushl $0x45d\n\t"
      "pushl $0x254c8c\n\t"
      "pushl $0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lpost_evaluator_hide_8:\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "pushl $0x12\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "call *%[c24000]\n\t"
      "addl $0xc, %%esp\n\t"
      ".Lpost_evaluator_hide_9:\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .Lpost_evaluator_hide_10\n\t"
      "popl %%edi\n\t"
      "movl $1, %%eax\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lpost_evaluator_hide_10:\n\t"
      "movzbl 0x30(%%esi), %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".Lpost_evaluator_hide_jt:\n\t"
      ".long .Lpost_evaluator_hide_6\n\t"
      ".long .Lpost_evaluator_hide_4\n\t"
      ".long .Lpost_evaluator_hide_2\n\t"
      ".long .Lpost_evaluator_hide_5\n\t"
      ".long .Lpost_evaluator_hide_3\n\t"
      ".text\n\t"
      :
      : [assert] "m"(b245d0_assert), [exitfn] "m"(b245d0_exitfn), [c24000] "m"(b245d0_c24000)
      : "memory");
}
#else
#error "post_evaluator_hide: clang naked draft required"
#endif


/* FUN_000246b0 (0x246b0) — XBE naked draft (batch 141). */
#if defined(__clang__)
static void (*const b246b0_c24000)(void *ctx, float score, int type, void *position) = FUN_00024000;

__attribute__((naked, noinline))
void FUN_000246b0(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "movb 0x5fc(%%ecx), %%al\n\t"
      "testb %%al, %%al\n\t"
      "pushl %%esi\n\t"
      "movl 0x10(%%ebp), %%esi\n\t"
      "je .LFUN_000246b0_7\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LFUN_000246b0_1\n\t"
      "flds 0x660(%%ecx)\n\t"
      "movl $1, %%eax\n\t"
      "fadds 0x254cd0\n\t"
      "popl %%esi\n\t"
      "fstps 0x660(%%ecx)\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000246b0_1:\n\t"
      "movswl 0x6(%%esi), %%eax\n\t"
      "subl $0, %%eax\n\t"
      "movl $0, 0xc(%%ebp)\n\t"
      "je .LFUN_000246b0_5\n\t"
      "decl %%eax\n\t"
      "je .LFUN_000246b0_4\n\t"
      "flds 0x600(%%ecx)\n\t"
      "fsubs 0x254ccc\n\t"
      "fcoms 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .LFUN_000246b0_2\n\t"
      "fld %%st(0)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "flds 0x2c(%%esi)\n\t"
      "fcompp\n\t"
      "fnstsw %%ax\n\t"
      "fstp %%st(0)\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_000246b0_6\n\t"
      "jmp .LFUN_000246b0_3\n\t"
      ".LFUN_000246b0_2:\n\t"
      "fstp %%st(0)\n\t"
      ".LFUN_000246b0_3:\n\t"
      "movb $1, 0x31(%%esi)\n\t"
      "movb 0x14(%%ecx), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_000246b0_6\n\t"
      "movb $0, 0x30(%%esi)\n\t"
      "jmp .LFUN_000246b0_6\n\t"
      ".LFUN_000246b0_4:\n\t"
      "movl $0x41200000, 0xc(%%ebp)\n\t"
      "jmp .LFUN_000246b0_6\n\t"
      ".LFUN_000246b0_5:\n\t"
      "movl $0x41a00000, 0xc(%%ebp)\n\t"
      ".LFUN_000246b0_6:\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "pushl $0x14\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c24000]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_000246b0_7:\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LFUN_000246b0_8\n\t"
      "movl $1, %%eax\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000246b0_8:\n\t"
      "movzbl 0x30(%%esi), %%eax\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c24000] "m"(b246b0_c24000)
      : "memory");
}
#else
#error "FUN_000246b0: clang naked draft required"
#endif


/* FUN_00024770 (0x24770) — XBE naked draft (batch 138). */
#if defined(__clang__)
static void (*const b24770_c24000)(void *ctx, float score, int type, void *position) = FUN_00024000;

__attribute__((naked, noinline))
void FUN_00024770(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "movb 0x5fc(%%eax), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "pushl %%esi\n\t"
      "movl 0x10(%%ebp), %%esi\n\t"
      "je .LFUN_00024770_7\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LFUN_00024770_2\n\t"
      "movb 0x628(%%eax), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "je .LFUN_00024770_1\n\t"
      "flds 0x254640\n\t"
      "popl %%esi\n\t"
      "fadds 0x660(%%eax)\n\t"
      "fstps 0x660(%%eax)\n\t"
      "movl $1, %%eax\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00024770_1:\n\t"
      "flds 0x254cc0\n\t"
      "popl %%esi\n\t"
      "fadds 0x660(%%eax)\n\t"
      "fstps 0x660(%%eax)\n\t"
      "movl $1, %%eax\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00024770_2:\n\t"
      "movswl 0x6(%%esi), %%ecx\n\t"
      "subl $0, %%ecx\n\t"
      "movl $0, 0xc(%%ebp)\n\t"
      "je .LFUN_00024770_5\n\t"
      "decl %%ecx\n\t"
      "movb 0x628(%%eax), %%cl\n\t"
      "je .LFUN_00024770_3\n\t"
      "testb %%cl, %%cl\n\t"
      "jne .LFUN_00024770_6\n\t"
      "movb $1, 0x31(%%esi)\n\t"
      "movb 0x14(%%eax), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "jne .LFUN_00024770_6\n\t"
      "movb $0, 0x30(%%esi)\n\t"
      "jmp .LFUN_00024770_6\n\t"
      ".LFUN_00024770_3:\n\t"
      "testb %%cl, %%cl\n\t"
      "je .LFUN_00024770_4\n\t"
      "movl $0x40200000, 0xc(%%ebp)\n\t"
      "jmp .LFUN_00024770_6\n\t"
      ".LFUN_00024770_4:\n\t"
      "movl $0x40a00000, 0xc(%%ebp)\n\t"
      "jmp .LFUN_00024770_6\n\t"
      ".LFUN_00024770_5:\n\t"
      "movb 0x628(%%eax), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "movl $0x40c00000, 0xc(%%ebp)\n\t"
      "jne .LFUN_00024770_6\n\t"
      "movl $0x41700000, 0xc(%%ebp)\n\t"
      ".LFUN_00024770_6:\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "pushl $0xe\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "call *%[c24000]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_00024770_7:\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LFUN_00024770_8\n\t"
      "movl $1, %%eax\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00024770_8:\n\t"
      "movzbl 0x30(%%esi), %%eax\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c24000] "m"(b24770_c24000)
      : "memory");
}
#else
#error "FUN_00024770: clang naked draft required"
#endif


/* FUN_00024850 (0x24850) — readable C lift.
 * actor@edi state@ebx. */
void FUN_00024850(int actor_handle, int flag, char *actor, void *state)
{
  void **entry = (void **)0x254bf8;

  if (!*entry)
    return;
  for (; *entry; entry = (void **)((char *)entry + 8)) {
    unsigned bit = 1u << (unsigned char)actor[4];
    if ((bit & (unsigned)(int)*(short *)((char *)entry - 4)) == 0)
      continue;
    ((void (*)(int, char *, void *, void *))*entry)(actor_handle, actor, flag, state);
  }
}
/* FUN_00024890 (0x24890) — XBE naked draft (batch 152). */
#if defined(__clang__)
static void (*const b24890_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b24890_exitfn)(int) = system_exit;

__attribute__((naked, noinline))
char FUN_00024890(int actor_handle __attribute__((unused)), void *state __attribute__((unused)), char *actor __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movb $1, %%bl\n\t"
      "movl $0x254c30, %%esi\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_00024890_1:\n\t"
      "movl (%%esi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_00024890_3\n\t"
      "movb 0x4(%%edi), %%cl\n\t"
      "movl $1, %%edx\n\t"
      "shll %%cl, %%edx\n\t"
      "movswl -0x4(%%esi), %%ecx\n\t"
      "testl %%edx, %%ecx\n\t"
      "je .LFUN_00024890_2\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "call *%%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "movb %%al, %%bl\n\t"
      ".LFUN_00024890_2:\n\t"
      "addl $8, %%esi\n\t"
      "testb %%bl, %%bl\n\t"
      "jne .LFUN_00024890_1\n\t"
      ".LFUN_00024890_3:\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "cmpb %%bl, 0x30(%%edx)\n\t"
      "je .LFUN_00024890_4\n\t"
      "pushl $1\n\t"
      "pushl $0x4ee\n\t"
      "pushl $0x254c8c\n\t"
      "pushl $0x254cd4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00024890_4:\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b24890_assert), [exitfn] "m"(b24890_exitfn)
      : "memory");
}
#else
#error "FUN_00024890: clang naked draft required"
#endif


/* FUN_00024900 (0x24900) — readable C lift.
 * query_buf@edi. */
char FUN_00024900(int actor_handle, void *query_buf)
{
  char *qb = (char *)query_buf;
  void **entry;
  char ok = 1;

  *(int *)(qb + 0x660) = 0;
  for (entry = (void **)0x254c30; *entry; entry = (void **)((char *)entry + 8)) {
    unsigned bit = 1u << (unsigned char)qb[4];
    if (bit & (unsigned)(int)*(short *)((char *)entry - 4)) {
      ok = ((char (*)(int, void *, int))*entry)(actor_handle, query_buf, 0);
    }
    if (!ok)
      break;
  }
  return ok;
}
/* FUN_00024950 (0x24950) — XBE naked draft (batch 127). */
#if defined(__clang__)
static void (*const b24950_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b24950_exitfn)(int) = system_exit;

__attribute__((naked, noinline))
int FUN_00024950(int index1 __attribute__((unused)), int index2 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl 0x331f04, %%eax\n\t"
      "pushl %%ebx\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "movl %%ebx, %%esi\n\t"
      "imull $0x3c, %%edi, %%edi\n\t"
      "imull $0x3c, %%esi, %%esi\n\t"
      "addl %%eax, %%esi\n\t"
      "addl %%eax, %%edi\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_00024950_1\n\t"
      "pushl $1\n\t"
      "pushl $0x50f\n\t"
      "pushl $0x254c8c\n\t"
      "pushl $0x254d88\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00024950_1:\n\t"
      "testl %%ebx, %%ebx\n\t"
      "jl .LFUN_00024950_2\n\t"
      "movswl 0x331f00, %%eax\n\t"
      "cmpl %%eax, %%ebx\n\t"
      "jl .LFUN_00024950_3\n\t"
      ".LFUN_00024950_2:\n\t"
      "pushl $1\n\t"
      "pushl $0x510\n\t"
      "pushl $0x254c8c\n\t"
      "pushl $0x254d40\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00024950_3:\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jl .LFUN_00024950_4\n\t"
      "movswl 0x331f00, %%ecx\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jl .LFUN_00024950_5\n\t"
      ".LFUN_00024950_4:\n\t"
      "pushl $1\n\t"
      "pushl $0x511\n\t"
      "pushl $0x254c8c\n\t"
      "pushl $0x254cf8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00024950_5:\n\t"
      "movb 0x30(%%esi), %%al\n\t"
      "cmpb 0x30(%%edi), %%al\n\t"
      "je .LFUN_00024950_6\n\t"
      "xorl %%edx, %%edx\n\t"
      "testb %%al, %%al\n\t"
      "sete %%dl\n\t"
      "popl %%edi\n\t"
      "xorl %%eax, %%eax\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "leal -0x1(%%edx,%%edx,1), %%edx\n\t"
      "testl %%edx, %%edx\n\t"
      "setg %%al\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00024950_6:\n\t"
      "movb 0x31(%%esi), %%al\n\t"
      "cmpb 0x31(%%edi), %%al\n\t"
      "je .LFUN_00024950_7\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "testb %%al, %%al\n\t"
      "setne %%cl\n\t"
      "popl %%edi\n\t"
      "xorl %%eax, %%eax\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "leal -0x1(%%ecx,%%ecx,1), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "setg %%al\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00024950_7:\n\t"
      "flds 0x38(%%esi)\n\t"
      "fcomps 0x38(%%edi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .LFUN_00024950_8\n\t"
      "flds 0x38(%%esi)\n\t"
      "fcomps 0x38(%%edi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00024950_8\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00024950_8:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b24950_assert), [exitfn] "m"(b24950_exitfn)
      : "memory");
}
#else
#error "FUN_00024950: clang naked draft required"
#endif


/* actor_get_firing_position_group (0x24a60) — XBE naked draft (batch 128). */
#if defined(__clang__)
static void *(*const b24a60_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static scenario_t * (*const b24a60_c18e380)(void) = global_scenario_get;
static void *(*const b24a60_elem)(void *, int, int) = tag_block_get_element;
static void (*const b24a60_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b24a60_exitfn)(int) = system_exit;

__attribute__((naked, noinline))
int actor_get_firing_position_group(int actor_handle __attribute__((unused)), short param_2 __attribute__((unused)), int param_3 __attribute__((unused)))
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
      "movl %%eax, %%esi\n\t"
      "movl 0x34(%%esi), %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "xorl %%eax, %%eax\n\t"
      "cmpl $-1, %%ecx\n\t"
      "je .Lactor_get_firing_position_group_11\n\t"
      "pushl %%edi\n\t"
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
      "movb 0x98(%%esi), %%cl\n\t"
      "movl %%eax, %%edi\n\t"
      "movswl 0x10(%%ebp), %%eax\n\t"
      "addl $0x18, %%esp\n\t"
      "decl %%eax\n\t"
      "je .Lactor_get_firing_position_group_1\n\t"
      "decl %%eax\n\t"
      "jne .Lactor_get_firing_position_group_2\n\t"
      "xorb %%cl, %%cl\n\t"
      "jmp .Lactor_get_firing_position_group_2\n\t"
      ".Lactor_get_firing_position_group_1:\n\t"
      "movb $1, %%cl\n\t"
      ".Lactor_get_firing_position_group_2:\n\t"
      "movw 0xc(%%ebp), %%ax\n\t"
      "cmpw $1, %%ax\n\t"
      "jne .Lactor_get_firing_position_group_3\n\t"
      "movl $5, %%esi\n\t"
      "movswl %%si, %%ecx\n\t"
      "movl 0x54(%%edi,%%ecx,4), %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lactor_get_firing_position_group_3:\n\t"
      "cmpw $4, %%ax\n\t"
      "jne .Lactor_get_firing_position_group_4\n\t"
      "movb 0x374(%%esi), %%al\n\t"
      "negb %%al\n\t"
      "sbbl %%eax, %%eax\n\t"
      "andl $3, %%eax\n\t"
      "addl $2, %%eax\n\t"
      "jmp .Lactor_get_firing_position_group_7\n\t"
      ".Lactor_get_firing_position_group_4:\n\t"
      "cmpw $5, %%ax\n\t"
      "jne .Lactor_get_firing_position_group_5\n\t"
      "movl $6, %%esi\n\t"
      "movswl %%si, %%ecx\n\t"
      "movl 0x54(%%edi,%%ecx,4), %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lactor_get_firing_position_group_5:\n\t"
      "movb 0x374(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_get_firing_position_group_6\n\t"
      "xorl %%edx, %%edx\n\t"
      "testb %%cl, %%cl\n\t"
      "setne %%dl\n\t"
      "addl $3, %%edx\n\t"
      "movl %%edx, %%esi\n\t"
      "jmp .Lactor_get_firing_position_group_8\n\t"
      ".Lactor_get_firing_position_group_6:\n\t"
      "xorl %%eax, %%eax\n\t"
      "testb %%cl, %%cl\n\t"
      "setne %%al\n\t"
      ".Lactor_get_firing_position_group_7:\n\t"
      "movl %%eax, %%esi\n\t"
      ".Lactor_get_firing_position_group_8:\n\t"
      "testw %%si, %%si\n\t"
      "jl .Lactor_get_firing_position_group_9\n\t"
      "cmpw $7, %%si\n\t"
      "jl .Lactor_get_firing_position_group_10\n\t"
      ".Lactor_get_firing_position_group_9:\n\t"
      "pushl $1\n\t"
      "pushl $0x584\n\t"
      "pushl $0x254c8c\n\t"
      "pushl $0x254db4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lactor_get_firing_position_group_10:\n\t"
      "movswl %%si, %%ecx\n\t"
      "movl 0x54(%%edi,%%ecx,4), %%eax\n\t"
      "popl %%edi\n\t"
      ".Lactor_get_firing_position_group_11:\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [dget] "m"(b24a60_dget), [c18e380] "m"(b24a60_c18e380), [elem] "m"(b24a60_elem), [assert] "m"(b24a60_assert), [exitfn] "m"(b24a60_exitfn)
      : "memory");
}
#else
#error "actor_get_firing_position_group: clang naked draft required"
#endif


/* actor_clear_discarded_firing_positions (0x24b80) — readable C lift (ai campaign). */
void actor_clear_discarded_firing_positions(int actor_handle, int param2)
{
  unsigned char *a = (unsigned char *)datum_get(*(void **)0x6325a4, actor_handle);
  *(uint16_t *)(a + 0x3c6) = 0;
  uint16_t *slot = (uint16_t *)(a + 0x3ca);
  for (int i = 0; i < 4; i++)
    slot[i] = 0xffff;
  if (a[0x3d8]) {
    if (!param2 || a[0x3d9])
      a[0x3d8] = 0;
  }
}


/* FUN_00024be0 (0x24be0) — readable C lift. */
void FUN_00024be0(int actor_handle, short param_2, char param_3)
{
  char *actor;
  int idx;
  int next;
  void *block;
  float *pos;

  if (param_2 == (short)-1)
    return;
  actor = (char *)datum_get(*(data_t **)0x6325a4, actor_handle);
  idx = *(int16_t *)(actor + 0x3c6);
  actor[0x3c8 + idx * 4] = param_3;
  *(int16_t *)(actor + 0x3ca + idx * 4) = param_2;
  next = idx + 1;
  next &= 0x80000003;
  if (next < 0)
    next = ((next - 1) | -4) + 1;
  *(int16_t *)(actor + 0x3c6) = (int16_t)next;
  block = tag_block_get_element(
      (char *)global_scenario_get() + 0x42c,
      *(unsigned short *)(actor + 0x34),
      0xb0);
  pos = (float *)tag_block_get_element((char *)block + 0x98, param_2, 0x18);
  actor[0x3d9] = param_3;
  actor[0x3d8] = 1;
  *(float *)(actor + 0x3dc) = pos[0];
  *(float *)(actor + 0x3e0) = pos[1];
  *(float *)(actor + 0x3e4) = pos[2];
}



