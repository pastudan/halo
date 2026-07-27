#include <stdint.h>

char *player_effect_get(int16_t local_player_index)
{
  assert_halt(local_player_index >= 0 &&
              local_player_index < MAXIMUM_NUMBER_OF_LOCAL_PLAYERS);
  assert_halt(player_effect_globals);
  return player_effect_globals + local_player_index * 0xec;
}

void player_effect_initialize(void)
{
  player_effect_globals = (char *)game_state_malloc("player effects", 0, 0x3ec);
  assert_halt(player_effect_globals);
}

void player_effect_dispose(void)
{
}

void player_effect_initialize_for_new_map(void)
{
  csmemset(player_effect_globals, 0, 0x3ec);
  *(_WORD *)(player_effect_globals + 0x3c0) = 0xFFFF;
  *(_DWORD *)(player_effect_globals + 0x3e8) = game_time_get();
}

void player_effect_dispose_from_old_map(void)
{
}

void player_effect_update(void)
{
  int16_t local_player_index;
  int player_index;
  void *player;
  char *effect;

  local_player_index = (int16_t)local_player_get_next(-1);
  while (local_player_index != -1) {
    player_index = local_player_get_player_index(local_player_index);
    if (player_index != -1) {
      player = datum_get(player_data,
                         local_player_get_player_index(local_player_index));
      if (*(int *)((char *)player + 0x34) != -1) {
        local_player_index = (int16_t)local_player_get_next(local_player_index);
        continue;
      }
    }
    effect = player_effect_get(local_player_index);
    csmemset(effect + 0xe4, 0, 4);
    csmemset(player_effect_get(local_player_index), 0, 0xec);
    rumble_clear_for_local_player(local_player_index);
    local_player_index = (int16_t)local_player_get_next(local_player_index);
  }
}

/* player_effect_set_from_descriptor -- apply an effect descriptor to a player's
 * effect state. Internal helper at 0xa2ab0.
 *
 * The original binary passes the descriptor in EBX as a register arg;
 * we pass it explicitly since all callers are in this TU.
 *
 * Confirmed: copies 56 bytes (14 dwords) from descriptor to effect+0x18.
 * Confirmed: scales effect+0x28 by intensity_scale.
 * Confirmed: sets effect+0xde to (short)(intensity_scale * effect->field_28).
 * Confirmed: clamps effect+0x3c to [0.0f, max] where max comes from descriptor.
 * Confirmed: sets bit 0 at effect+0xe8.
 */
static void player_effect_set_from_descriptor(int player_index, char *effect,
                                              float intensity,
                                              float intensity_scale,
                                              void *descriptor)
{
  int16_t desc_type = *(int16_t *)descriptor;
  int16_t desc_priority = *((int16_t *)descriptor + 1);
  float desc_duration = *(float *)((char *)descriptor + 0x10);
  float desc_max = *(float *)((char *)descriptor + 0x20);
  float desc_min = *(float *)((char *)descriptor + 0x24);
  int16_t effect_priority = *(int16_t *)(effect + 0x1a);
  int16_t effect_timer = *(int16_t *)(effect + 0xde);
  int16_t *enabled_array = (int16_t *)0x2ef7e0;
  float scaled_duration;
  float clamped_value;

  (void)
    player_index; /* original binary receives this in ESI but never uses it */

  scaled_duration = intensity_scale * desc_duration;

  if (((effect_priority <= desc_priority) ||
       ((float)effect_timer <= scaled_duration)) &&
      (enabled_array[desc_type] != 0)) {
    csmemcpy(effect + 0x18, descriptor, 0x38);

    *(float *)(effect + 0x28) = intensity_scale * *(float *)(effect + 0x28);

    *(int16_t *)(effect + 0xde) = (int16_t)(*(float *)(effect + 0x28));

    clamped_value = 0.0f;
    if (0.0f <= ((1.0f - desc_min) * intensity + desc_min)) {
      if (((1.0f - desc_min) * intensity + desc_min) <= desc_max) {
        clamped_value = (1.0f - desc_min) * intensity + desc_min;
      } else {
        clamped_value = desc_max;
      }
    }
    *(float *)(effect + 0x3c) = clamped_value;
    *(uint8_t *)(effect + 0xe8) |= 1;
  }
}

void player_effect_apply(int player_handle, void *effect_descriptor,
                         float intensity)
{
  int16_t unit_index;
  void *player;
  char *effect;

  if (player_handle == -1)
    return;

  player = datum_get(player_data, player_handle);
  unit_index = *(int16_t *)((char *)player + 2);

  if (unit_index == -1)
    return;

  effect = player_effect_get(unit_index);
  player_effect_set_from_descriptor(unit_index, effect, intensity,
                                    intensity * 30.0f, effect_descriptor);
}

/* FUN_000a3b80 (0xa3b80) — XBE naked draft (batch 110). */
#if defined(__clang__)
static void *(*const ba3b80_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void (*const ba3b80_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const ba3b80_exitfn)(int) = system_exit;
static void (*const ba3b80_c10b090)(void) = (void *)lock_global_random_seed;
static void *(*const ba3b80_tag)(int, int) = tag_get;
static char * (*const ba3b80_ca2690)(int16_t local_player_index) = (void *)player_effect_get;
static void (*const ba3b80_ca2ab0)(void) = (void *)FUN_000a2ab0;
static void (*const ba3b80_ca3890)(int unit_index, float *rumble_def, void *direction, float damage_amount, float scale, float *effect) = (void *)FUN_000a3890;
static void (*const ba3b80_ca2ba0)(int unit_index, float damage_amount, float scale, float *effect_data, void *effect) = (void *)FUN_000a2ba0;
static void (*const ba3b80_cb9bc0)(short unit_index, float *rumble_def, float damage_amount, float scale) = (void *)rumble_player_impulse;
static int (*const ba3b80_c1c7480)(int sound_tag_index, float scale) = (void *)sound_impulse_start;
static void (*const ba3b80_c10b0a0)(void) = (void *)unlock_global_random_seed;
static int (*const ba3b80_cba3c0)(int16_t local_player_index) = (void *)local_player_get_player_index;
static void *(*const ba3b80_tryget)(int, int) = object_try_and_get_and_verify_type;
static void * (*const ba3b80_c8a4e0)(unsigned __int16 local_player_index) = (void *)observer_get_camera;
static void (*const ba3b80_c1a9200)(int object_handle, float *out_position) = (void *)unit_get_head_position;
static vector3_t * (*const ba3b80_c1412f0)(int object_handle, vector3_t *out_position) = (void *)object_get_world_position;
static void (*const ba3b80_cross)(float *, float *, float *) = cross_product3d;
static float (*const ba3b80_norm)(float *) = normalize3d;

__attribute__((naked, noinline))
void FUN_000a3b80(int player_index __attribute__((unused)), void *damage_params __attribute__((unused)), void *position __attribute__((unused)), float damage_amount __attribute__((unused)), float scale __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x28, %%esp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl 0x5aa6d4, %%ecx\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movw 0x2(%%eax), %%di\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_000a3b80_1\n\t"
      "pushl $1\n\t"
      "pushl $0x156\n\t"
      "pushl $0x26ae94\n\t"
      "pushl $0x255554\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000a3b80_1:\n\t"
      "call *%[c10b090]\n\t"
      "cmpw $-1, %%di\n\t"
      "je .LFUN_000a3b80_12\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "movl (%%edx), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "pushl $0x6a707421\n\t"
      "call *%[tag]\n\t"
      "pushl %%edi\n\t"
      "movl %%eax, %%esi\n\t"
      "call *%[ca2690]\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      "pushl $0x3f800000\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "leal 0x24(%%esi), %%ebx\n\t"
      "pushl %%edi\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "call *%[ca2ab0]\n\t"
      "movl 0x14(%%ebp), %%edx\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "movl -0x4(%%ebp), %%ebx\n\t"
      "pushl $0x3f800000\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "leal 0x98(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edi\n\t"
      "movl %%ebx, %%eax\n\t"
      "call *%[ca3890]\n\t"
      "movl 0x14(%%ebp), %%edx\n\t"
      "pushl $0x3f800000\n\t"
      "pushl %%edx\n\t"
      "leal 0xcc(%%esi), %%eax\n\t"
      "pushl %%edi\n\t"
      "call *%[ca2ba0]\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "pushl $0x3f800000\n\t"
      "pushl %%eax\n\t"
      "leal 0x5c(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edi\n\t"
      "call *%[cb9bc0]\n\t"
      "movl 0x120(%%esi), %%eax\n\t"
      "addl $0x4c, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_000a3b80_2\n\t"
      "pushl $0x3f800000\n\t"
      "pushl %%eax\n\t"
      "call *%[c1c7480]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_000a3b80_2:\n\t"
      "flds 0x18(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_000a3b80_11\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "cmpl $-1, 0xc(%%edx)\n\t"
      "je .LFUN_000a3b80_11\n\t"
      "movl 0x1c8(%%esi), %%eax\n\t"
      "testb $1, %%ah\n\t"
      "je .LFUN_000a3b80_3\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movb $1, 0xe6(%%eax)\n\t"
      "call *%[c10b0a0]\n\t"
      "popl %%edi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000a3b80_3:\n\t"
      "pushl %%edi\n\t"
      "call *%[cba3c0]\n\t"
      "addl $4, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "jne .LFUN_000a3b80_4\n\t"
      "orl %%eax, %%esi\n\t"
      "jmp .LFUN_000a3b80_5\n\t"
      ".LFUN_000a3b80_4:\n\t"
      "pushl %%edi\n\t"
      "call *%[cba3c0]\n\t"
      "movl 0x5aa6d4, %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movl 0x34(%%eax), %%esi\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_000a3b80_5:\n\t"
      "pushl $3\n\t"
      "pushl %%esi\n\t"
      "call *%[tryget]\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl 0xc(%%edx), %%eax\n\t"
      "pushl $-1\n\t"
      "pushl %%eax\n\t"
      "call *%[tryget]\n\t"
      "addl $0x10, %%esp\n\t"
      "testl %%ebx, %%ebx\n\t"
      "je .LFUN_000a3b80_11\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_000a3b80_11\n\t"
      "pushl %%edi\n\t"
      "call *%[c8a4e0]\n\t"
      "movl %%eax, %%edi\n\t"
      "addl $4, %%esp\n\t"
      "testl %%edi, %%edi\n\t"
      "je .LFUN_000a3b80_11\n\t"
      "leal -0x28(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "call *%[c1a9200]\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "movl 0xc(%%eax), %%ecx\n\t"
      "leal -0x1c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1412f0]\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fsubs -0x28(%%ebp)\n\t"
      "leal -0x28(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal 0x2c(%%edi), %%esi\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "addl $0x20, %%edi\n\t"
      "flds -0x18(%%ebp)\n\t"
      "pushl %%esi\n\t"
      "fsubs -0x24(%%ebp)\n\t"
      "pushl %%edi\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fsubs -0x20(%%ebp)\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "call *%[cross]\n\t"
      "flds -0x20(%%ebp)\n\t"
      "leal -0x1c(%%ebp), %%eax\n\t"
      "fmuls -0x8(%%ebp)\n\t"
      "pushl %%eax\n\t"
      "flds -0x24(%%ebp)\n\t"
      "fmuls -0xc(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds -0x28(%%ebp)\n\t"
      "fmuls -0x10(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fstps -0x1c(%%ebp)\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fmuls 0x8(%%edi)\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fmuls 0x4(%%edi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fmuls (%%edi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fmuls 0x8(%%esi)\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fmuls 0x4(%%esi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fmuls (%%esi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "call *%[norm]\n\t"
      "fcomps 0x2533c0\n\t"
      "addl $0x20, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .LFUN_000a3b80_11\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fabs\n\t"
      "fcompl 0x25fea8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_000a3b80_7\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_000a3b80_6\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movb $1, 0xe4(%%ecx)\n\t"
      "jmp .LFUN_000a3b80_7\n\t"
      ".LFUN_000a3b80_6:\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "movb $1, 0xe6(%%edx)\n\t"
      ".LFUN_000a3b80_7:\n\t"
      "flds -0x18(%%ebp)\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fpatan\n\t"
      "fld %%st(0)\n\t"
      "fabs\n\t"
      "fstps 0x10(%%ebp)\n\t"
      "fcoms 0x254a58\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .LFUN_000a3b80_8\n\t"
      "fcomps 0x26af48\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_000a3b80_11\n\t"
      "jmp .LFUN_000a3b80_9\n\t"
      ".LFUN_000a3b80_8:\n\t"
      "fstp %%st(0)\n\t"
      ".LFUN_000a3b80_9:\n\t"
      "flds 0x10(%%ebp)\n\t"
      "fcomps 0x2568bc\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_000a3b80_10\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movb $1, 0xe5(%%eax)\n\t"
      "call *%[c10b0a0]\n\t"
      "popl %%edi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000a3b80_10:\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movb $1, 0xe7(%%ecx)\n\t"
      ".LFUN_000a3b80_11:\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      ".LFUN_000a3b80_12:\n\t"
      "call *%[c10b0a0]\n\t"
      "popl %%edi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [dget] "m"(ba3b80_dget), [assert] "m"(ba3b80_assert), [exitfn] "m"(ba3b80_exitfn), [c10b090] "m"(ba3b80_c10b090), [tag] "m"(ba3b80_tag), [ca2690] "m"(ba3b80_ca2690), [ca2ab0] "m"(ba3b80_ca2ab0), [ca3890] "m"(ba3b80_ca3890), [ca2ba0] "m"(ba3b80_ca2ba0), [cb9bc0] "m"(ba3b80_cb9bc0), [c1c7480] "m"(ba3b80_c1c7480), [c10b0a0] "m"(ba3b80_c10b0a0), [cba3c0] "m"(ba3b80_cba3c0), [tryget] "m"(ba3b80_tryget), [c8a4e0] "m"(ba3b80_c8a4e0), [c1a9200] "m"(ba3b80_c1a9200), [c1412f0] "m"(ba3b80_c1412f0), [cross] "m"(ba3b80_cross), [norm] "m"(ba3b80_norm)
      : "memory");
}
#else
#error "FUN_000a3b80: clang naked draft required"
#endif

/* --- player_effects.obj batch drafts (2026-07-26) --- */

/* player_effect_add_continuous_effect (0xa27a0) — XBE naked draft (batch 127). */
#if defined(__clang__)
static void *(*const ba27a0_tag)(int, int) = tag_get;
static char * (*const ba27a0_ca2690)(int16_t local_player_index) = (void *)player_effect_get;
static int (*const ba27a0_gtime)(void) = game_time_get;
static float (*const ba27a0_c10a5e0)(int16_t function_type, float input) = (void *)FUN_0010a5e0;
static void *(*const ba27a0_memset)(void *, int, unsigned int) = csmemset;

__attribute__((naked, noinline))
void player_effect_add_continuous_effect(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "pushl $0x63646d67\n\t"
      "call *%[tag]\n\t"
      "flds 0x10(%%ebp)\n\t"
      "movl %%eax, %%esi\n\t"
      "fcomps 0x4(%%esi)\n\t"
      "addl $8, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lplayer_effect_add_continuous_effect_7\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "call *%[ca2690]\n\t"
      "flds 0x10(%%ebp)\n\t"
      "fsubs (%%esi)\n\t"
      "movl %%eax, %%ebx\n\t"
      "flds (%%esi)\n\t"
      "addl $4, %%esp\n\t"
      "fsubs 0x4(%%esi)\n\t"
      "leal 0xcc(%%ebx), %%edi\n\t"
      ".byte 0xde, 0xf9\n\t"
      "fsubrs 0x2533c8\n\t"
      "fcoms 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lplayer_effect_add_continuous_effect_1\n\t"
      "fstp %%st(0)\n\t"
      "movl $0, 0x10(%%ebp)\n\t"
      "jmp .Lplayer_effect_add_continuous_effect_3\n\t"
      ".Lplayer_effect_add_continuous_effect_1:\n\t"
      "fcoms 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lplayer_effect_add_continuous_effect_2\n\t"
      "fstp %%st(0)\n\t"
      "movl $0x3f800000, 0x10(%%ebp)\n\t"
      "jmp .Lplayer_effect_add_continuous_effect_3\n\t"
      ".Lplayer_effect_add_continuous_effect_2:\n\t"
      "fstps 0x10(%%ebp)\n\t"
      ".Lplayer_effect_add_continuous_effect_3:\n\t"
      "call *%[gtime]\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "fildl -0x4(%%ebp)\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x58(%%esi), %%dx\n\t"
      "pushl %%ecx\n\t"
      "fdivs 0x5c(%%esi)\n\t"
      "fstps (%%esp)\n\t"
      "pushl %%edx\n\t"
      "call *%[c10a5e0]\n\t"
      "flds 0x2533c8\n\t"
      "fsubs 0x60(%%esi)\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $0, 0xdc(%%ebx)\n\t"
      "fxch %%st(1)\n\t"
      "fmuls 0x60(%%esi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fmuls 0x10(%%ebp)\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "jle .Lplayer_effect_add_continuous_effect_4\n\t"
      "pushl $0x10\n\t"
      "pushl $0\n\t"
      "pushl %%edi\n\t"
      "movw $0, 0xdc(%%ebx)\n\t"
      "call *%[memset]\n\t"
      "addl $0xc, %%esp\n\t"
      ".Lplayer_effect_add_continuous_effect_4:\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fmuls 0x44(%%esi)\n\t"
      "fcoms 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .Lplayer_effect_add_continuous_effect_5\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c0\n\t"
      ".Lplayer_effect_add_continuous_effect_5:\n\t"
      "fadds 0x8(%%edi)\n\t"
      "fstps 0x8(%%edi)\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fmuls 0x48(%%esi)\n\t"
      "fcoms 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .Lplayer_effect_add_continuous_effect_6\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c0\n\t"
      ".Lplayer_effect_add_continuous_effect_6:\n\t"
      "fadds 0xc(%%edi)\n\t"
      "fstps 0xc(%%edi)\n\t"
      "flds 0x10(%%ebp)\n\t"
      "fmuls 0x24(%%esi)\n\t"
      "fadds (%%edi)\n\t"
      "fstps (%%edi)\n\t"
      "flds 0x10(%%ebp)\n\t"
      "fmuls 0x28(%%esi)\n\t"
      "fadds 0x4(%%edi)\n\t"
      "fstps 0x4(%%edi)\n\t"
      "popl %%edi\n\t"
      "popl %%ebx\n\t"
      ".Lplayer_effect_add_continuous_effect_7:\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [tag] "m"(ba27a0_tag), [ca2690] "m"(ba27a0_ca2690), [gtime] "m"(ba27a0_gtime), [c10a5e0] "m"(ba27a0_c10a5e0), [memset] "m"(ba27a0_memset)
      : "memory");
}
#else
#error "player_effect_add_continuous_effect: clang naked draft required"
#endif


/* scripted_player_effect_set_rotation (0xa28e0) — readable C lift (deg→rad scale). */
void scripted_player_effect_set_rotation(float yaw, float pitch, float roll)
{
  char *fx;
  float scale;

  fx = *(char **)0x4557ec;
  scale = *(float *)0x253d4c;
  *(float *)(fx + 0x3d0) = yaw * scale;
  *(float *)(fx + 0x3d4) = pitch * scale;
  *(float *)(fx + 0x3d8) = roll * scale;
}

/* scripted_player_effect_set_rumble (0xa2920) — readable C lift. */
void scripted_player_effect_set_rumble(int a0, float a1)
{
  rumble_player_set_scripted_values(a0, a1);
}

/* player_telefrag_effect_stop (0xa2930) — readable C lift. */
void player_telefrag_effect_stop(int player_handle)
{
  void *d = datum_get(*(data_t **)0x5aa6d4, player_handle);
  short idx = *(short *)((char *)d + 2);
  if (idx != -1) {
    player_effect_get(idx);
    rumble_set_direct_motors(idx, 0, 0);
  }
}
/* player_effect_screen_fade_in (0xa2970) — readable C lift. */
void player_effect_screen_fade_in(float a0, int a1, int a2, short a3)
{
  char *p = *(char **)0x4557ec;
  *(float *)(p + 0x3b0) = a0;
  *(int *)(p + 0x3b4) = a1;
  *(int *)(p + 0x3b8) = a2;
  *(short *)(p + 0x3c0) = a3;
  p[0x3c2] = (char)0;
  *(int *)(p + 0x3bc) = game_time_get();
}

/* player_effect_screen_fade_out (0xa29c0) — readable C lift. */
void player_effect_screen_fade_out(float a0, int a1, int a2, short a3)
{
  char *p = *(char **)0x4557ec;
  *(float *)(p + 0x3b0) = a0;
  *(int *)(p + 0x3b4) = a1;
  *(int *)(p + 0x3b8) = a2;
  *(short *)(p + 0x3c0) = a3;
  p[0x3c2] = (char)1;
  *(int *)(p + 0x3bc) = game_time_get();
}

/* player_effect_get_damage_indicators (0xa2a10) — readable C lift. */
void player_effect_get_damage_indicators(int player_index, void *out)
{
  char *p = player_effect_get((int16_t)player_index);
  char *src = p + 0xe4;
  int i;
  csmemcpy(out, src, 4);
  for (i = 0; i < 4; i++) {
    if (src[i] != 0) {
      int v = (int)game_time_get_elapsed() + (unsigned char)src[i];
      if (v >= 0xff)
        src[i] = (char)0xff;
      else
        src[i] = (char)((int)game_time_get_elapsed() + (unsigned char)src[i]);
    }
    src++;
  }
}
/* player_effect_clear_damage_indicators (0xa2a70) — readable C lift. */
void player_effect_clear_damage_indicators(int player_index)
{
  char *p = player_effect_get((int16_t)player_index);
  csmemset(p + 0xe4, 0, 4);
}
/* FUN_000a2a90 (0xa2a90) — readable C lift: lerp(a, 1, t) = a+(1-a)*t. */
float FUN_000a2a90(float a, float t)
{
  return (*(float *)0x2533c8 - a) * t + a;
}

/* FUN_000a2ab0 (0xa2ab0) — readable C lift from XBE leaf.
 * descriptor@ebx; stack: unused, effect*, intensity, scale (pre-*30). */
void FUN_000a2ab0(int unused_player, char *effect, float intensity, float scale,
                  void *descriptor)
{
  float scale30;
  int16_t effect_pri;
  int16_t desc_pri;
  int16_t desc_type;
  float timer_f;
  float scaled_dur;
  float desc_min;
  float desc_max;
  float value;

  (void)unused_player;

  scale30 = scale * *(float *)0x253394;
  effect_pri = *(int16_t *)(effect + 0x1a);
  desc_pri = *(int16_t *)((char *)descriptor + 2);

  if (effect_pri > desc_pri) {
    timer_f = (float)(int)*(int16_t *)(effect + 0xde);
    scaled_dur = scale30 * *(float *)((char *)descriptor + 0x10);
    if (!(scaled_dur < timer_f))
      return;
  }

  desc_type = *(int16_t *)descriptor;
  if (((int16_t *)0x2ef7e0)[desc_type] == 0)
    return;

  {
    int i;
    int *dst = (int *)(effect + 0x18);
    int *src = (int *)descriptor;
    for (i = 0; i < 14; i++)
      dst[i] = src[i];
  }
  *(float *)(effect + 0x28) = scale30 * *(float *)(effect + 0x28);
  {
    float ftmp = *(float *)(effect + 0x28);
    int ftol_result;
    __asm__ volatile(
        "flds %1\n\t"
        "call %P2\n\t"
        "movl %%eax, %0"
        : "=m"(ftol_result)
        : "m"(ftmp), "X"(FUN_001d9068)
        : "eax", "edx", "ecx", "st", "cc", "memory");
    *(int16_t *)(effect + 0xde) = (int16_t)ftol_result;
  }

  desc_min = *(float *)((char *)descriptor + 0x24);
  desc_max = *(float *)((char *)descriptor + 0x20);
  value = (*(float *)0x2533c8 - desc_min) * intensity + desc_min;
  if (value < *(float *)0x2533c0)
    value = *(float *)0x2533c0;
  else if (!(value <= desc_max))
    value = desc_max;

  *(float *)(effect + 0x3c) = value;
  *(uint8_t *)(effect + 0xe8) |= 1;
}


/* FUN_000a2ba0 (0xa2ba0) — readable C lift from XBE leaf.
 * effect_data@eax, effect@ebx; stack: unit_index, damage, scale. */
void FUN_000a2ba0(int unit_index, float damage_amount, float scale,
                  float *effect_data, void *effect)
{
  float scale30;
  float lerp_val;
  float thresh;
  float timer_f;
  float cur;
  char *eff;
  int i;
  int *dst;
  int *src;

  (void)unit_index;
  game_time_get();

  eff = (char *)effect;
  scale30 = scale * *(float *)0x253394;
  lerp_val = (*(float *)0x2533c8 - effect_data[10]) * damage_amount + effect_data[10];
  timer_f = (float)(int)*(int16_t *)(eff + 0xe2);
  thresh = scale30 * effect_data[0];
  cur = *(float *)(eff + 0xac);

  if (!(timer_f < thresh || lerp_val > cur))
    return;

  dst = (int *)(eff + 0x84);
  src = (int *)effect_data;
  for (i = 0; i < 18; i++)
    dst[i] = src[i];
  *(float *)(eff + 0xac) = lerp_val;

  /* fmul/fst/ftol in one asm block so ST0 keeps 80-bit product for _ftol2. */
  __asm__ volatile(
      "flds %0\n\t"
      "fmuls %1\n\t"
      "fsts %1\n\t"
      "call %P2\n\t"
      "movw %%ax, %3\n\t"
      "flds %0\n\t"
      "fmuls %4\n\t"
      "fstps %4\n\t"
      :
      : "m"(scale30), "m"(*(float *)(eff + 0x84)), "X"(FUN_001d9068),
        "m"(*(int16_t *)(eff + 0xe2)), "m"(*(float *)(eff + 0xa4))
      : "eax", "edx", "ecx", "st", "cc", "memory");
  *(uint8_t *)(eff + 0xe8) |= 4;
}


/* FUN_000a2c70 (0xa2c70) — readable C lift. function_type@eax */
float FUN_000a2c70(float scale, float numer, float denom, short function_type)
{
  float t = *(float *)0x2533c8 - (numer / denom);
  return transition_function_evaluate(function_type, t) * scale;
}
/* player_effect_continuous_refresh (0xa2d30) — readable C lift. */
void player_effect_continuous_refresh(void *effect, float *center)
{
  int16_t i;
  int player;
  char *pdata;
  int unit;
  float wpos[3];
  float dx, dy, dz, dist;

  for (i = 0; i < 4; i++) {
    player = local_player_get_player_index(i);
    if (player == -1)
      continue;
    pdata = (char *)datum_get(*(data_t **)0x5aa6d4, player);
    unit = *(int *)(pdata + 0x34);
    if (unit == -1)
      continue;
    object_get_world_position(unit, (vector3_t *)wpos);
    dx = center[0] - wpos[0];
    dy = center[1] - wpos[1];
    dz = center[2] - wpos[2];
    dist = __builtin_sqrtf(dx * dx + dy * dy + dz * dz);
    ((void (*)(int16_t, void *, float))player_effect_add_continuous_effect)(i, effect, dist);
  }
}

/* scripted_player_effect_set_translation (0xa2dc0) — readable C lift. */
void scripted_player_effect_set_translation(int a0, int a1, int a2)
{
  char *g = *(char **)0x4557ec;
  *(int *)(g + 0x3c4) = a0;
  *(int *)(g + 0x3c8) = a1;
  *(int *)(g + 0x3cc) = a2;
}

/* scripted_player_effect_start (0xa2df0) — readable C lift. */
void scripted_player_effect_start(float intensity, float seconds)
{
  char *fx;
  int ticks;
  int flags;

  fx = *(char **)0x4557ec;
  *(float *)(fx + 0x3dc) = intensity;
  ticks = (int)(seconds * *(float *)0x253394);
  *(short *)(fx + 0x3e0) = (short)ticks;
  *(short *)(fx + 0x3e2) = (short)ticks;
  flags = *(int *)(fx + 0x3e4);
  flags = (flags & ~2) | 1;
  *(int *)(fx + 0x3e4) = flags;
}


/* scripted_player_effect_stop (0xa2e40) — readable C lift. */
void scripted_player_effect_stop(float seconds)
{
  char *fx;
  int ticks;

  ticks = (int)(seconds * *(float *)0x253394);
  fx = *(char **)0x4557ec;
  *(short *)(fx + 0x3e0) = (short)ticks;
  *(short *)(fx + 0x3e2) = (short)ticks;
  *(int *)(fx + 0x3e4) |= 2;
}

/* player_telefrag_effect_start (0xa2ed0) — XBE naked draft (batch 136). */
#if defined(__clang__)
static void *(*const ba2ed0_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static char * (*const ba2ed0_ca2690)(int16_t local_player_index) = (void *)player_effect_get;
static void (*const ba2ed0_cb9da0)(short local_player_index, int left_motor, int right_motor) = (void *)rumble_set_direct_motors;
static void (*const ba2ed0_ca2ab0)(void) = (void *)FUN_000a2ab0;
static void (*const ba2ed0_ca2ba0)(int unit_index, float damage_amount, float scale, float *effect_data, void *effect) = (void *)FUN_000a2ba0;

__attribute__((naked, noinline))
void player_telefrag_effect_start(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x84, %%esp\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw $0, -0x3c(%%ebp)\n\t"
      "movl $0xd, %%ecx\n\t"
      "leal -0x3a(%%ebp), %%edi\n\t"
      "rep stosl\n\t"
      "stosw\n\t"
      "xorl %%eax, %%eax\n\t"
      "movl $0x11, %%ecx\n\t"
      "leal -0x80(%%ebp), %%edi\n\t"
      "movl $0, -0x84(%%ebp)\n\t"
      "rep stosl\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl 0x5aa6d4, %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movswl 0x2(%%eax), %%esi\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%esi\n\t"
      "je .Lplayer_telefrag_effect_start_1\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "call *%[ca2690]\n\t"
      "flds 0xc(%%ebp)\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "fmull 0x26aed0\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl 0x2ee6c4, %%eax\n\t"
      "fstps -0x7c(%%ebp)\n\t"
      "movl (%%eax), %%ecx\n\t"
      "movl %%edx, -0x1c(%%ebp)\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl %%ecx, -0x14(%%ebp)\n\t"
      "movl 0x8(%%eax), %%ecx\n\t"
      "pushl %%edi\n\t"
      "movl %%edx, -0x10(%%ebp)\n\t"
      "movl 0xc(%%eax), %%edx\n\t"
      "pushl %%edi\n\t"
      "pushl %%esi\n\t"
      "movl %%ebx, -0x4(%%ebp)\n\t"
      "movl $0x3f800000, -0x84(%%ebp)\n\t"
      "movw $1, -0x3c(%%ebp)\n\t"
      "movw $2, -0x3a(%%ebp)\n\t"
      "movl $0x3f800000, -0x2c(%%ebp)\n\t"
      "movl $0, -0x18(%%ebp)\n\t"
      "movl %%ecx, -0xc(%%ebp)\n\t"
      "movl %%edx, -0x8(%%ebp)\n\t"
      "call *%[cb9da0]\n\t"
      "pushl $0x3f800000\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "leal -0x3c(%%ebp), %%ebx\n\t"
      "call *%[ca2ab0]\n\t"
      "movl -0x4(%%ebp), %%ebx\n\t"
      "pushl $0x3f800000\n\t"
      "pushl %%edi\n\t"
      "pushl %%esi\n\t"
      "leal -0x84(%%ebp), %%eax\n\t"
      "call *%[ca2ba0]\n\t"
      "addl $0x2c, %%esp\n\t"
      "popl %%ebx\n\t"
      ".Lplayer_telefrag_effect_start_1:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [dget] "m"(ba2ed0_dget), [ca2690] "m"(ba2ed0_ca2690), [cb9da0] "m"(ba2ed0_cb9da0), [ca2ab0] "m"(ba2ed0_ca2ab0), [ca2ba0] "m"(ba2ed0_ca2ba0)
      : "memory");
}
#else
#error "player_telefrag_effect_start: clang naked draft required"
#endif


/* player_effect_get_screen_flash (0xa2fc0) — XBE naked draft (batch 113). */
#if defined(__clang__)
static void (*const ba2fc0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const ba2fc0_exitfn)(int) = system_exit;
static bool (*const ba2fc0_cff4c0)(void) = (void *)console_is_active;
static int (*const ba2fc0_gtime)(void) = game_time_get;
static float (*const ba2fc0_c10a710)(short function_type, float t) = (void *)transition_function_evaluate;
static char * (*const ba2fc0_ca2690)(int16_t local_player_index) = (void *)player_effect_get;
static int16_t (*const ba2fc0_cb5ae0)(void) = (void *)game_time_get_elapsed;
static char * (*const ba2fc0_c8d9d0)(char *buffer, const char *format, ...) = (void *)csprintf;

__attribute__((naked, noinline))
void player_effect_get_screen_flash(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%esi\n\t"
      "movl 0xc(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .Lplayer_effect_get_screen_flash_1\n\t"
      "pushl $1\n\t"
      "pushl $0x1e4\n\t"
      "pushl $0x26ae94\n\t"
      "pushl $0x26af30\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lplayer_effect_get_screen_flash_1:\n\t"
      "call *%[cff4c0]\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lplayer_effect_get_screen_flash_17\n\t"
      "movl 0x4557ec, %%eax\n\t"
      "cmpw $-1, 0x3c0(%%eax)\n\t"
      "pushl %%edi\n\t"
      "leal 0x3c0(%%eax), %%edi\n\t"
      "je .Lplayer_effect_get_screen_flash_11\n\t"
      "movb 0x3c2(%%eax), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "jne .Lplayer_effect_get_screen_flash_2\n\t"
      "leal 0x3c0(%%eax), %%edi\n\t"
      "call *%[gtime]\n\t"
      "movl %%eax, %%ecx\n\t"
      "movl 0x4557ec, %%eax\n\t"
      "subl 0x3bc(%%eax), %%ecx\n\t"
      "movswl (%%edi), %%edx\n\t"
      "cmpl %%edx, %%ecx\n\t"
      "jg .Lplayer_effect_get_screen_flash_11\n\t"
      ".Lplayer_effect_get_screen_flash_2:\n\t"
      "movw $1, (%%esi)\n\t"
      "pushl %%ebx\n\t"
      "leal 0x3b0(%%eax), %%ecx\n\t"
      "movl (%%ecx), %%ebx\n\t"
      "leal 0xc(%%esi), %%edx\n\t"
      "movl %%ebx, (%%edx)\n\t"
      "movl 0x4(%%ecx), %%ebx\n\t"
      "movl %%ebx, 0x4(%%edx)\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "movl %%ecx, 0x8(%%edx)\n\t"
      "movl $0x3f800000, 0x8(%%esi)\n\t"
      "cmpw $0, (%%edi)\n\t"
      "popl %%ebx\n\t"
      "jle .Lplayer_effect_get_screen_flash_6\n\t"
      "call *%[gtime]\n\t"
      "movl %%eax, %%edx\n\t"
      "movl 0x4557ec, %%eax\n\t"
      "movl 0x3bc(%%eax), %%ecx\n\t"
      "movswl 0x3c0(%%eax), %%eax\n\t"
      "subl %%ecx, %%edx\n\t"
      "movl %%edx, 0xc(%%ebp)\n\t"
      "fildl 0xc(%%ebp)\n\t"
      "movl %%eax, 0xc(%%ebp)\n\t"
      "fidivl 0xc(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lplayer_effect_get_screen_flash_3\n\t"
      "movl $0, 0xc(%%ebp)\n\t"
      "jmp .Lplayer_effect_get_screen_flash_5\n\t"
      ".Lplayer_effect_get_screen_flash_3:\n\t"
      "call *%[gtime]\n\t"
      "movl %%eax, %%ecx\n\t"
      "movl 0x4557ec, %%eax\n\t"
      "subl 0x3bc(%%eax), %%ecx\n\t"
      "movswl 0x3c0(%%eax), %%edx\n\t"
      "movl %%ecx, 0xc(%%ebp)\n\t"
      "fildl 0xc(%%ebp)\n\t"
      "movl %%edx, 0xc(%%ebp)\n\t"
      "fidivl 0xc(%%ebp)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lplayer_effect_get_screen_flash_4\n\t"
      "movl $0x3f800000, 0xc(%%ebp)\n\t"
      "jmp .Lplayer_effect_get_screen_flash_5\n\t"
      ".Lplayer_effect_get_screen_flash_4:\n\t"
      "call *%[gtime]\n\t"
      "movl %%eax, %%ecx\n\t"
      "movl 0x4557ec, %%eax\n\t"
      "subl 0x3bc(%%eax), %%ecx\n\t"
      "movswl 0x3c0(%%eax), %%edx\n\t"
      "movl %%ecx, 0xc(%%ebp)\n\t"
      "fildl 0xc(%%ebp)\n\t"
      "movl %%edx, 0xc(%%ebp)\n\t"
      "fidivl 0xc(%%ebp)\n\t"
      "fstps 0xc(%%ebp)\n\t"
      ".Lplayer_effect_get_screen_flash_5:\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $5\n\t"
      "call *%[c10a710]\n\t"
      "movl 0x4557ec, %%eax\n\t"
      "addl $8, %%esp\n\t"
      "jmp .Lplayer_effect_get_screen_flash_7\n\t"
      ".Lplayer_effect_get_screen_flash_6:\n\t"
      "flds 0x2533c8\n\t"
      ".Lplayer_effect_get_screen_flash_7:\n\t"
      "fsts 0x4(%%esi)\n\t"
      "movb 0x3c2(%%eax), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "jne .Lplayer_effect_get_screen_flash_8\n\t"
      "flds 0x2533c8\n\t"
      ".byte 0xd8, 0xe1\n\t"
      "fstps 0x4(%%esi)\n\t"
      ".Lplayer_effect_get_screen_flash_8:\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x4(%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lplayer_effect_get_screen_flash_9\n\t"
      "flds 0x2533c0\n\t"
      "fstps 0x4(%%esi)\n\t"
      "jmp .Lplayer_effect_get_screen_flash_16\n\t"
      ".Lplayer_effect_get_screen_flash_9:\n\t"
      "flds 0x4(%%esi)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lplayer_effect_get_screen_flash_10\n\t"
      "flds 0x2533c8\n\t"
      "fstps 0x4(%%esi)\n\t"
      "jmp .Lplayer_effect_get_screen_flash_16\n\t"
      ".Lplayer_effect_get_screen_flash_10:\n\t"
      "flds 0x4(%%esi)\n\t"
      "fstps 0x4(%%esi)\n\t"
      "jmp .Lplayer_effect_get_screen_flash_16\n\t"
      ".Lplayer_effect_get_screen_flash_11:\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .Lplayer_effect_get_screen_flash_16\n\t"
      "pushl %%eax\n\t"
      "call *%[ca2690]\n\t"
      "movl 0x4557ec, %%ecx\n\t"
      "movl %%eax, %%edi\n\t"
      "addl $4, %%esp\n\t"
      "movw $0xffff, 0x3c0(%%ecx)\n\t"
      "cmpw $0, 0xde(%%edi)\n\t"
      "jg .Lplayer_effect_get_screen_flash_12\n\t"
      "testb $1, 0xe8(%%edi)\n\t"
      "je .Lplayer_effect_get_screen_flash_16\n\t"
      ".Lplayer_effect_get_screen_flash_12:\n\t"
      "andb $0xfe, 0xe8(%%edi)\n\t"
      "movswl 0x18(%%edi), %%edx\n\t"
      "movw 0x2ef7e0(,%%edx,2), %%ax\n\t"
      "movw %%ax, (%%esi)\n\t"
      "leal 0x40(%%edi), %%ecx\n\t"
      "movl (%%ecx), %%eax\n\t"
      "leal 0x8(%%esi), %%edx\n\t"
      "movl %%eax, (%%edx)\n\t"
      "movl 0x4(%%ecx), %%eax\n\t"
      "movl %%eax, 0x4(%%edx)\n\t"
      "movl 0x8(%%ecx), %%eax\n\t"
      "movl %%eax, 0x8(%%edx)\n\t"
      "movl 0xc(%%ecx), %%ecx\n\t"
      "movl %%ecx, 0xc(%%edx)\n\t"
      "flds 0x28(%%edi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lplayer_effect_get_screen_flash_13\n\t"
      "movswl 0xde(%%edi), %%edx\n\t"
      "movl %%edx, 0xc(%%ebp)\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x2c(%%edi), %%ax\n\t"
      "fildl 0xc(%%ebp)\n\t"
      "pushl %%ecx\n\t"
      "fdivs 0x28(%%edi)\n\t"
      "fmuls 0x3c(%%edi)\n\t"
      "fstps (%%esp)\n\t"
      "pushl %%eax\n\t"
      "call *%[c10a710]\n\t"
      "fstps 0x4(%%esi)\n\t"
      "addl $8, %%esp\n\t"
      "jmp .Lplayer_effect_get_screen_flash_14\n\t"
      ".Lplayer_effect_get_screen_flash_13:\n\t"
      "movl 0x3c(%%edi), %%ecx\n\t"
      "movl %%ecx, 0x4(%%esi)\n\t"
      ".Lplayer_effect_get_screen_flash_14:\n\t"
      "call *%[cb5ae0]\n\t"
      "subw %%ax, 0xde(%%edi)\n\t"
      "flds 0x4(%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .Lplayer_effect_get_screen_flash_15\n\t"
      "flds 0x4(%%esi)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jnp .Lplayer_effect_get_screen_flash_16\n\t"
      ".Lplayer_effect_get_screen_flash_15:\n\t"
      "pushl $1\n\t"
      "pushl $0x212\n\t"
      "pushl $0x26ae94\n\t"
      "pushl $0x26aef0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lplayer_effect_get_screen_flash_16:\n\t"
      "popl %%edi\n\t"
      ".Lplayer_effect_get_screen_flash_17:\n\t"
      "movl 0x4(%%esi), %%edx\n\t"
      "movl %%edx, %%eax\n\t"
      "andl $0x7f800000, %%eax\n\t"
      "cmpl $0x7f800000, %%eax\n\t"
      "movl %%edx, 0xc(%%ebp)\n\t"
      "jne .Lplayer_effect_get_screen_flash_18\n\t"
      "flds 0x4(%%esi)\n\t"
      "pushl $1\n\t"
      "pushl $0x217\n\t"
      "pushl $0x26ae94\n\t"
      "subl $8, %%esp\n\t"
      "fstpl (%%esp)\n\t"
      "movl %%edx, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x26aed8\n\t"
      "pushl $0x25eb8c\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x18, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lplayer_effect_get_screen_flash_18:\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(ba2fc0_assert), [exitfn] "m"(ba2fc0_exitfn), [cff4c0] "m"(ba2fc0_cff4c0), [gtime] "m"(ba2fc0_gtime), [c10a710] "m"(ba2fc0_c10a710), [ca2690] "m"(ba2fc0_ca2690), [cb5ae0] "m"(ba2fc0_cb5ae0), [c8d9d0] "m"(ba2fc0_c8d9d0)
      : "memory");
}
#else
#error "player_effect_get_screen_flash: clang naked draft required"
#endif


/* FUN_000a32e0 (0xa32e0) — readable C lift. */
void FUN_000a32e0(float *obj, float pitch, float yaw)
{
  float dir[3];
  unsigned int *seed;
  char *base;

  base = (char *)obj;
  if (yaw != 0.0f) {
    seed = random_math_get_local_seed_address();
    random_seed_get_direction3d(seed, dir);
    FUN_001092d0(obj, dir, __builtin_sinf(yaw), __builtin_cosf(yaw));
  }
  if (pitch != 0.0f) {
    seed = random_math_get_local_seed_address();
    random_seed_get_direction3d(seed, dir);
    *(float *)(base + 0x28) = dir[0] * pitch;
    *(float *)(base + 0x2c) = dir[1] * pitch;
    *(float *)(base + 0x30) = dir[2] * pitch;
  }
}

/* player_effect_get_camera_effect_matrix (0xa3370) — XBE naked draft (batch 106). */
#if defined(__clang__)
static void (*const ba3370_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const ba3370_exitfn)(int) = system_exit;
static int (*const ba3370_gtime)(void) = game_time_get;
static int16_t (*const ba3370_cb5ae0)(void) = (void *)game_time_get_elapsed;
static void (*const ba3370_cb9ba0)(float scale) = (void *)rumble_player_set_scale;
static unsigned int *(*const ba3370_lseed)(void) = random_math_get_local_seed_address;
static float (*const ba3370_rrange)(int *, float, float) = random_real_range;
static void (*const ba3370_c109e90)(float *out, float yaw, float pitch, float roll) = (void *)FUN_00109e90;
static char * (*const ba3370_ca2690)(int16_t local_player_index) = (void *)player_effect_get;
static float (*const ba3370_c10a710)(short function_type, float t) = (void *)transition_function_evaluate;
static void (*const ba3370_c1092d0)(float *out_matrix, float *axis, float sine, float cosine) = (void *)FUN_001092d0;
static float (*const ba3370_c10a5e0)(int16_t function_type, float input) = (void *)FUN_0010a5e0;
static void (*const ba3370_ca32e0)(void) = (void *)FUN_000a32e0;
static void (*const ba3370_cb9da0)(short local_player_index, int left_motor, int right_motor) = (void *)rumble_set_direct_motors;
static void *(*const ba3370_memset)(void *, int, unsigned int) = csmemset;
static void (*const ba3370_c109850)(float *a, float *b, float *out) = (void *)matrix4x3_multiply;

__attribute__((naked, noinline))
void player_effect_get_camera_effect_matrix(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x48, %%esp\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .Lplayer_effect_get_camera_effect_matrix_1\n\t"
      "pushl $1\n\t"
      "pushl $0x259\n\t"
      "pushl $0x26ae94\n\t"
      "pushl $0x26af40\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lplayer_effect_get_camera_effect_matrix_1:\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "cmpw $-1, %%si\n\t"
      "je .Lplayer_effect_get_camera_effect_matrix_23\n\t"
      "pushl %%ebx\n\t"
      "call *%[gtime]\n\t"
      "movl 0x4557ec, %%eax\n\t"
      "testb $1, 0x3e4(%%eax)\n\t"
      "je .Lplayer_effect_get_camera_effect_matrix_8\n\t"
      "movl 0x3dc(%%eax), %%ecx\n\t"
      "movl 0x31fc60, %%esi\n\t"
      "leal 0x3c4(%%eax), %%ebx\n\t"
      "movl %%ecx, 0x8(%%ebp)\n\t"
      "movl $0xd, %%ecx\n\t"
      "rep movsl\n\t"
      "movw 0x1c(%%ebx), %%cx\n\t"
      "testw %%cx, %%cx\n\t"
      "jle .Lplayer_effect_get_camera_effect_matrix_3\n\t"
      "testb $2, 0x3e4(%%eax)\n\t"
      "je .Lplayer_effect_get_camera_effect_matrix_2\n\t"
      "movswl 0x1e(%%ebx), %%eax\n\t"
      "movswl %%cx, %%edx\n\t"
      "movl %%edx, -0x8(%%ebp)\n\t"
      "fildl -0x8(%%ebp)\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "fidivl -0x8(%%ebp)\n\t"
      "fmuls 0x8(%%ebp)\n\t"
      "fstps 0x8(%%ebp)\n\t"
      "call *%[cb5ae0]\n\t"
      "subw %%ax, 0x1c(%%ebx)\n\t"
      "jmp .Lplayer_effect_get_camera_effect_matrix_4\n\t"
      ".Lplayer_effect_get_camera_effect_matrix_2:\n\t"
      "movswl 0x1e(%%ebx), %%edx\n\t"
      "movswl %%cx, %%ecx\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "fildl -0x8(%%ebp)\n\t"
      "movl %%edx, -0x8(%%ebp)\n\t"
      "fidivl -0x8(%%ebp)\n\t"
      "fsubrs 0x2533c8\n\t"
      "fmuls 0x8(%%ebp)\n\t"
      "fstps 0x8(%%ebp)\n\t"
      "call *%[cb5ae0]\n\t"
      "subw %%ax, 0x1c(%%ebx)\n\t"
      "jmp .Lplayer_effect_get_camera_effect_matrix_4\n\t"
      ".Lplayer_effect_get_camera_effect_matrix_3:\n\t"
      "movl 0x3e4(%%eax), %%ecx\n\t"
      "testb $2, %%cl\n\t"
      "je .Lplayer_effect_get_camera_effect_matrix_5\n\t"
      "andl $0xfffffffe, %%ecx\n\t"
      "pushl $0\n\t"
      "movl %%ecx, 0x3e4(%%eax)\n\t"
      "call *%[cb9ba0]\n\t"
      "addl $4, %%esp\n\t"
      ".Lplayer_effect_get_camera_effect_matrix_4:\n\t"
      "movl 0x4557ec, %%eax\n\t"
      ".Lplayer_effect_get_camera_effect_matrix_5:\n\t"
      "testb $1, 0x3e4(%%eax)\n\t"
      "je .Lplayer_effect_get_camera_effect_matrix_22\n\t"
      "flds 0x8(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lplayer_effect_get_camera_effect_matrix_6\n\t"
      "movl $0, 0x8(%%ebp)\n\t"
      "jmp .Lplayer_effect_get_camera_effect_matrix_7\n\t"
      ".Lplayer_effect_get_camera_effect_matrix_6:\n\t"
      "flds 0x8(%%ebp)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lplayer_effect_get_camera_effect_matrix_7\n\t"
      "movl $0x3f800000, 0x8(%%ebp)\n\t"
      ".Lplayer_effect_get_camera_effect_matrix_7:\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[cb9ba0]\n\t"
      "addl $4, %%esp\n\t"
      "pushl $0x3f800000\n\t"
      "pushl $0xbf800000\n\t"
      "call *%[lseed]\n\t"
      "pushl %%eax\n\t"
      "call *%[rrange]\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "addl $0xc, %%esp\n\t"
      "pushl $0x3f800000\n\t"
      "pushl $0xbf800000\n\t"
      "call *%[lseed]\n\t"
      "pushl %%eax\n\t"
      "call *%[rrange]\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "addl $0xc, %%esp\n\t"
      "pushl $0x3f800000\n\t"
      "pushl $0xbf800000\n\t"
      "call *%[lseed]\n\t"
      "pushl %%eax\n\t"
      "call *%[rrange]\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fmuls 0x14(%%ebx)\n\t"
      "movl 0xc(%%ebp), %%esi\n\t"
      "fmuls 0x8(%%ebp)\n\t"
      "fstps 0x8(%%esp)\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fmuls 0x10(%%ebx)\n\t"
      "fmuls 0x8(%%ebp)\n\t"
      "fstps 0x4(%%esp)\n\t"
      "fmuls 0xc(%%ebx)\n\t"
      "fmuls 0x8(%%ebp)\n\t"
      "fstps (%%esp)\n\t"
      "pushl %%esi\n\t"
      "call *%[c109e90]\n\t"
      "addl $0x10, %%esp\n\t"
      "pushl $0x3f800000\n\t"
      "pushl $0xbf800000\n\t"
      "call *%[lseed]\n\t"
      "pushl %%eax\n\t"
      "call *%[rrange]\n\t"
      "fstps 0xc(%%ebp)\n\t"
      "addl $0xc, %%esp\n\t"
      "pushl $0x3f800000\n\t"
      "pushl $0xbf800000\n\t"
      "call *%[lseed]\n\t"
      "pushl %%eax\n\t"
      "call *%[rrange]\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "addl $0xc, %%esp\n\t"
      "pushl $0x3f800000\n\t"
      "pushl $0xbf800000\n\t"
      "call *%[lseed]\n\t"
      "pushl %%eax\n\t"
      "call *%[rrange]\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "flds 0xc(%%ebp)\n\t"
      "addl $0xc, %%esp\n\t"
      "fmuls 0x8(%%ebx)\n\t"
      "fmuls 0x8(%%ebp)\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fmuls (%%ebx)\n\t"
      "fmuls 0x8(%%ebp)\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fmuls 0x4(%%ebx)\n\t"
      "popl %%ebx\n\t"
      "popl %%edi\n\t"
      "fmuls 0x8(%%ebp)\n\t"
      "fstps 0x28(%%esi)\n\t"
      "fstps 0x2c(%%esi)\n\t"
      "fstps 0x30(%%esi)\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lplayer_effect_get_camera_effect_matrix_8:\n\t"
      "pushl %%esi\n\t"
      "call *%[ca2690]\n\t"
      "movl %%eax, %%ebx\n\t"
      "movw 0xe0(%%ebx), %%ax\n\t"
      "movb 0xe8(%%ebx), %%dl\n\t"
      "addl $4, %%esp\n\t"
      "testw %%ax, %%ax\n\t"
      "movb $2, %%cl\n\t"
      "jg .Lplayer_effect_get_camera_effect_matrix_9\n\t"
      "testb %%dl, %%cl\n\t"
      "jne .Lplayer_effect_get_camera_effect_matrix_10\n\t"
      "movl 0x31fc60, %%esi\n\t"
      "jmp .Lplayer_effect_get_camera_effect_matrix_13\n\t"
      ".Lplayer_effect_get_camera_effect_matrix_9:\n\t"
      "testb %%dl, %%cl\n\t"
      "je .Lplayer_effect_get_camera_effect_matrix_11\n\t"
      ".Lplayer_effect_get_camera_effect_matrix_10:\n\t"
      "movl $0x3f800000, -0x4(%%ebp)\n\t"
      "jmp .Lplayer_effect_get_camera_effect_matrix_12\n\t"
      ".Lplayer_effect_get_camera_effect_matrix_11:\n\t"
      "flds 0x50(%%ebx)\n\t"
      "movswl %%ax, %%ecx\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "movl 0x68(%%ebx), %%edx\n\t"
      "xorl %%eax, %%eax\n\t"
      "fildl -0x8(%%ebp)\n\t"
      "movw 0x54(%%ebx), %%ax\n\t"
      "pushl %%ecx\n\t"
      "movl %%edx, -0x8(%%ebp)\n\t"
      "fsubrs 0x50(%%ebx)\n\t"
      ".byte 0xd8, 0xf1\n\t"
      "fsubrs 0x2533c8\n\t"
      "fstps (%%esp)\n\t"
      "pushl %%eax\n\t"
      "fstp %%st(0)\n\t"
      "call *%[c10a710]\n\t"
      "fmuls -0x8(%%ebp)\n\t"
      "addl $8, %%esp\n\t"
      "fstps -0x4(%%ebp)\n\t"
      ".Lplayer_effect_get_camera_effect_matrix_12:\n\t"
      "movb 0xe8(%%ebx), %%dl\n\t"
      "flds 0x4(%%ebx)\n\t"
      "andb $0xfd, %%dl\n\t"
      "movb %%dl, 0xe8(%%ebx)\n\t"
      "movl 0x31fc44, %%eax\n\t"
      "fmuls (%%eax)\n\t"
      "subl $8, %%esp\n\t"
      "flds (%%ebx)\n\t"
      "leal -0x48(%%ebp), %%ecx\n\t"
      "fmuls 0x4(%%eax)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "flds 0x8(%%eax)\n\t"
      "fmuls (%%ebx)\n\t"
      "flds 0x8(%%ebx)\n\t"
      "fmuls (%%eax)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "flds 0x8(%%ebx)\n\t"
      "fmuls 0x4(%%eax)\n\t"
      "flds 0x8(%%eax)\n\t"
      "leal -0x14(%%ebp), %%eax\n\t"
      "fmuls 0x4(%%ebx)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fmuls 0x58(%%ebx)\n\t"
      "fld %%st(0)\n\t"
      "fcos\n\t"
      "fstps 0x4(%%esp)\n\t"
      "fsin\n\t"
      "fstps (%%esp)\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1092d0]\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fmuls 0x5c(%%ebx)\n\t"
      "addl $0x10, %%esp\n\t"
      "fld %%st(0)\n\t"
      "fmuls (%%ebx)\n\t"
      "fld %%st(1)\n\t"
      "fmuls 0x4(%%ebx)\n\t"
      "fstps -0x1c(%%ebp)\n\t"
      "fxch %%st(1)\n\t"
      "fmuls 0x8(%%ebx)\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fmuls 0xc(%%ebx)\n\t"
      ".byte 0xd8, 0xc1\n\t"
      "fstps -0x20(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fmuls 0x10(%%ebx)\n\t"
      "fadds -0x1c(%%ebp)\n\t"
      "fstps -0x1c(%%ebp)\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fmuls 0x14(%%ebx)\n\t"
      "fadds -0x18(%%ebp)\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "call *%[cb5ae0]\n\t"
      "subw %%ax, 0xe0(%%ebx)\n\t"
      "leal -0x48(%%ebp), %%esi\n\t"
      ".Lplayer_effect_get_camera_effect_matrix_13:\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "movl $0xd, %%ecx\n\t"
      "rep movsl\n\t"
      "movw 0xe2(%%ebx), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "movb $4, %%dl\n\t"
      "jg .Lplayer_effect_get_camera_effect_matrix_14\n\t"
      "testb %%dl, 0xe8(%%ebx)\n\t"
      "je .Lplayer_effect_get_camera_effect_matrix_22\n\t"
      ".Lplayer_effect_get_camera_effect_matrix_14:\n\t"
      "movl 0x31fc60, %%esi\n\t"
      "movl $0xd, %%ecx\n\t"
      "leal -0x48(%%ebp), %%edi\n\t"
      "rep movsl\n\t"
      "testb %%dl, 0xe8(%%ebx)\n\t"
      "je .Lplayer_effect_get_camera_effect_matrix_15\n\t"
      "movl $0x3f800000, -0x8(%%ebp)\n\t"
      "jmp .Lplayer_effect_get_camera_effect_matrix_16\n\t"
      ".Lplayer_effect_get_camera_effect_matrix_15:\n\t"
      "flds 0x84(%%ebx)\n\t"
      "movswl %%ax, %%edx\n\t"
      "movl %%edx, -0x8(%%ebp)\n\t"
      "movl 0xac(%%ebx), %%eax\n\t"
      "pushl %%ecx\n\t"
      "fildl -0x8(%%ebp)\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x88(%%ebx), %%ax\n\t"
      "fsubrs 0x84(%%ebx)\n\t"
      ".byte 0xd8, 0xf1\n\t"
      "fsubrs 0x2533c8\n\t"
      "fstps (%%esp)\n\t"
      "pushl %%eax\n\t"
      "fstp %%st(0)\n\t"
      "call *%[c10a710]\n\t"
      "fmuls -0x8(%%ebp)\n\t"
      "addl $8, %%esp\n\t"
      "fstps -0x8(%%ebp)\n\t"
      ".Lplayer_effect_get_camera_effect_matrix_16:\n\t"
      "movswl 0xe2(%%ebx), %%ecx\n\t"
      "movl %%ecx, -0x4(%%ebp)\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0xa0(%%ebx), %%dx\n\t"
      "fildl -0x4(%%ebp)\n\t"
      "pushl %%ecx\n\t"
      "fsubrs 0x84(%%ebx)\n\t"
      "fdivs 0xa4(%%ebx)\n\t"
      "fstps (%%esp)\n\t"
      "pushl %%edx\n\t"
      "call *%[c10a5e0]\n\t"
      "fmuls 0xa8(%%ebx)\n\t"
      "flds 0x2533c8\n\t"
      "addl $8, %%esp\n\t"
      "fsubs 0xa8(%%ebx)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fmuls -0x8(%%ebp)\n\t"
      "fld %%st(0)\n\t"
      "fmuls 0x8c(%%ebx)\n\t"
      "fcoms 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lplayer_effect_get_camera_effect_matrix_17\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "jmp .Lplayer_effect_get_camera_effect_matrix_18\n\t"
      ".Lplayer_effect_get_camera_effect_matrix_17:\n\t"
      "fstp %%st(0)\n\t"
      "movl $0, -0x8(%%ebp)\n\t"
      ".Lplayer_effect_get_camera_effect_matrix_18:\n\t"
      "fmuls 0x90(%%ebx)\n\t"
      "fcoms 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lplayer_effect_get_camera_effect_matrix_19\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "jmp .Lplayer_effect_get_camera_effect_matrix_20\n\t"
      ".Lplayer_effect_get_camera_effect_matrix_19:\n\t"
      "fstp %%st(0)\n\t"
      "movl $0, -0x4(%%ebp)\n\t"
      ".Lplayer_effect_get_camera_effect_matrix_20:\n\t"
      "movb 0xe8(%%ebx), %%cl\n\t"
      "flds -0x4(%%ebp)\n\t"
      "andb $0xfb, %%cl\n\t"
      "movb %%cl, 0xe8(%%ebx)\n\t"
      "fadds 0xd8(%%ebx)\n\t"
      "leal 0xcc(%%ebx), %%edi\n\t"
      "subl $8, %%esp\n\t"
      "fstps 0x4(%%esp)\n\t"
      "leal -0x48(%%ebp), %%esi\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fadds 0x8(%%edi)\n\t"
      "fstps (%%esp)\n\t"
      "call *%[ca32e0]\n\t"
      "movl 0x4(%%edi), %%eax\n\t"
      "movl (%%edi), %%ecx\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[cb9da0]\n\t"
      "addl $0x14, %%esp\n\t"
      "call *%[cb5ae0]\n\t"
      "addw %%ax, 0xdc(%%ebx)\n\t"
      "cmpw $0, 0xdc(%%ebx)\n\t"
      "jle .Lplayer_effect_get_camera_effect_matrix_21\n\t"
      "pushl $0x10\n\t"
      "pushl $0\n\t"
      "pushl %%edi\n\t"
      "movw $0, 0xdc(%%ebx)\n\t"
      "call *%[memset]\n\t"
      "addl $0xc, %%esp\n\t"
      ".Lplayer_effect_get_camera_effect_matrix_21:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "leal -0x48(%%ebp), %%esi\n\t"
      "call *%[ca32e0]\n\t"
      "call *%[cb5ae0]\n\t"
      "subw %%ax, 0xe2(%%ebx)\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x48(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c109850]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lplayer_effect_get_camera_effect_matrix_22:\n\t"
      "popl %%ebx\n\t"
      ".Lplayer_effect_get_camera_effect_matrix_23:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(ba3370_assert), [exitfn] "m"(ba3370_exitfn), [gtime] "m"(ba3370_gtime), [cb5ae0] "m"(ba3370_cb5ae0), [cb9ba0] "m"(ba3370_cb9ba0), [lseed] "m"(ba3370_lseed), [rrange] "m"(ba3370_rrange), [c109e90] "m"(ba3370_c109e90), [ca2690] "m"(ba3370_ca2690), [c10a710] "m"(ba3370_c10a710), [c1092d0] "m"(ba3370_c1092d0), [c10a5e0] "m"(ba3370_c10a5e0), [ca32e0] "m"(ba3370_ca32e0), [cb9da0] "m"(ba3370_cb9da0), [memset] "m"(ba3370_memset), [c109850] "m"(ba3370_c109850)
      : "memory");
}
#else
#error "player_effect_get_camera_effect_matrix: clang naked draft required"
#endif


/* FUN_000a3890 (0xa3890) — XBE naked draft (batch 110). */
#if defined(__clang__)
static int (*const ba3890_gtime)(void) = game_time_get;
static float (*const ba3890_norm)(float *) = normalize3d;
static float * (*const ba3890_cb7e30)(int16_t local_player_index) = (void *)player_control_get_facing_angles;
static void (*const ba3890_c10cc40)(float *out, float *angles) = (void *)angles_to_vector;
static void (*const ba3890_c10c3c0)(void) = (void *)FUN_0010c3c0;
static void (*const ba3890_ftol)(void) = FUN_001d9068;
static unsigned int *(*const ba3890_lseed)(void) = random_math_get_local_seed_address;
static float (*const ba3890_rrange)(int *, float, float) = random_real_range;
static void (*const ba3890_rots)(float *, float *, float, float) = rotate_vector3d_by_sincos;
static float * (*const ba3890_cb7f10)(int16_t local_player_index, float *out_direction) = (void *)player_control_get_facing_direction;
static void (*const ba3890_cb8cf0)(int16_t a, float *delta) = (void *)FUN_000b8cf0;

__attribute__((naked, noinline))
void FUN_000a3890(int unit_index __attribute__((unused)), float *rumble_def __attribute__((unused)), void *direction __attribute__((unused)), float damage_amount __attribute__((unused)), float scale __attribute__((unused)), float *effect __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x28, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl %%eax, %%ebx\n\t"
      "call *%[gtime]\n\t"
      "flds 0x18(%%ebp)\n\t"
      "fmuls 0x253394\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "movswl 0xe0(%%ebx), %%eax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "flds 0x18(%%edi)\n\t"
      "flds 0x2533c8\n\t"
      ".byte 0xd8, 0xe1\n\t"
      "fmuls 0x14(%%ebp)\n\t"
      ".byte 0xd8, 0xc1\n\t"
      "fstps 0x18(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "fildl -0x4(%%ebp)\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "flds 0x50(%%ebx)\n\t"
      "fcomps -0x4(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .LFUN_000a3890_1\n\t"
      "flds 0x18(%%ebp)\n\t"
      "fcomps 0x68(%%ebx)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .LFUN_000a3890_1\n\t"
      "flds 0x18(%%ebp)\n\t"
      "fcomps 0x68(%%ebx)\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_000a3890_2\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fmuls (%%edi)\n\t"
      "fcomps -0x4(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_000a3890_2\n\t"
      ".LFUN_000a3890_1:\n\t"
      "movl 0x10(%%ebp), %%esi\n\t"
      "movl %%esi, %%ecx\n\t"
      "movl (%%ecx), %%edx\n\t"
      "movl 0x4(%%ecx), %%eax\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "movl %%edx, -0x1c(%%ebp)\n\t"
      "leal -0x1c(%%ebp), %%edx\n\t"
      "movl %%ecx, -0x14(%%ebp)\n\t"
      "pushl %%edx\n\t"
      "movl %%eax, -0x18(%%ebp)\n\t"
      "movl $0, -0x14(%%ebp)\n\t"
      "call *%[norm]\n\t"
      "fstp %%st(0)\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[cb7e30]\n\t"
      "movl (%%eax), %%ecx\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "leal -0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x28(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      "call *%[c10cc40]\n\t"
      "leal -0x28(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl $0, -0x20(%%ebp)\n\t"
      "call *%[norm]\n\t"
      "fstp %%st(0)\n\t"
      "flds -0x18(%%ebp)\n\t"
      "addl $0x14, %%esp\n\t"
      "fmuls -0x18(%%ebp)\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fmuls -0x1c(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fmuls -0x14(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fsubs 0x2533c8\n\t"
      "fabs\n\t"
      "fcompl 0x2533d0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_000a3890_3\n\t"
      "flds -0x24(%%ebp)\n\t"
      "fmuls -0x24(%%ebp)\n\t"
      "flds -0x28(%%ebp)\n\t"
      "fmuls -0x28(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds -0x20(%%ebp)\n\t"
      "fmuls -0x20(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fsubs 0x2533c8\n\t"
      "fabs\n\t"
      "fcompl 0x2533d0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_000a3890_3\n\t"
      "leal -0x1c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x28(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c10c3c0]\n\t"
      "flds -0xc(%%ebp)\n\t"
      "movl 0x18(%%ebp), %%edx\n\t"
      "movl %%edi, %%esi\n\t"
      "movl $0xd, %%ecx\n\t"
      "leal 0x50(%%ebx), %%edi\n\t"
      "rep movsl\n\t"
      "fmuls 0x50(%%ebx)\n\t"
      "fsts 0x50(%%ebx)\n\t"
      "addl $8, %%esp\n\t"
      "movl %%edx, 0x68(%%ebx)\n\t"
      "call *%[ftol]\n\t"
      "movl 0x60(%%ebx), %%ecx\n\t"
      "fld %%st(0)\n\t"
      "movw %%ax, 0xe0(%%ebx)\n\t"
      "fcos\n\t"
      "movl 0x64(%%ebx), %%eax\n\t"
      "movl %%eax, %%edx\n\t"
      "movl %%eax, 0x18(%%ebp)\n\t"
      "pushl %%edx\n\t"
      "movl %%ecx, %%eax\n\t"
      "pushl %%eax\n\t"
      "movl $0, 0x8(%%ebx)\n\t"
      "movl %%ecx, -0xc(%%ebp)\n\t"
      "fstps (%%ebx)\n\t"
      "fsin\n\t"
      "fstps 0x4(%%ebx)\n\t"
      "call *%[lseed]\n\t"
      "pushl %%eax\n\t"
      "call *%[rrange]\n\t"
      "fstps 0x18(%%ebp)\n\t"
      "addl $0xc, %%esp\n\t"
      "pushl $0x40c90fdb\n\t"
      "pushl $0\n\t"
      "call *%[lseed]\n\t"
      "pushl %%eax\n\t"
      "call *%[rrange]\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "movl 0x31fc44, %%eax\n\t"
      "flds 0x4(%%eax)\n\t"
      "leal 0xc(%%ebx), %%esi\n\t"
      "fmuls (%%ebx)\n\t"
      "pushl %%esi\n\t"
      "flds 0x4(%%ebx)\n\t"
      "fmuls (%%eax)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "flds 0x8(%%ebx)\n\t"
      "fmuls (%%eax)\n\t"
      "flds (%%ebx)\n\t"
      "fmuls 0x8(%%eax)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "flds 0x8(%%eax)\n\t"
      "fmuls 0x4(%%ebx)\n\t"
      "flds 0x4(%%eax)\n\t"
      "fmuls 0x8(%%ebx)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps (%%esi)\n\t"
      "fstps 0x4(%%esi)\n\t"
      "fstps 0x8(%%esi)\n\t"
      "call *%[norm]\n\t"
      "fstp %%st(0)\n\t"
      "addl $8, %%esp\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fcos\n\t"
      "fstps 0x4(%%esp)\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fsin\n\t"
      "fstps (%%esp)\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "call *%[rots]\n\t"
      "flds 0x18(%%ebp)\n\t"
      "fmuls (%%esi)\n\t"
      "addl $0x10, %%esp\n\t"
      "fstps (%%esi)\n\t"
      "flds 0x18(%%ebp)\n\t"
      "fmuls 0x4(%%esi)\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "fstps 0x4(%%esi)\n\t"
      "flds 0x18(%%ebp)\n\t"
      "fmuls 0x8(%%esi)\n\t"
      "fstps 0x8(%%esi)\n\t"
      "movb 0xe8(%%ebx), %%al\n\t"
      "orb $2, %%al\n\t"
      "movb %%al, 0xe8(%%ebx)\n\t"
      ".LFUN_000a3890_2:\n\t"
      "movl 0x10(%%ebp), %%esi\n\t"
      ".LFUN_000a3890_3:\n\t"
      "flds 0x24(%%edi)\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "flds 0x2533c8\n\t"
      "leal -0x28(%%ebp), %%ecx\n\t"
      ".byte 0xd8, 0xe1\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "fmuls 0x14(%%ebp)\n\t"
      ".byte 0xd8, 0xc1\n\t"
      "fstps 0x10(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "call *%[cb7f10]\n\t"
      "movl 0x31fc44, %%eax\n\t"
      "flds -0x20(%%ebp)\n\t"
      "fmuls 0x4(%%eax)\n\t"
      "leal -0x10(%%ebp), %%edx\n\t"
      "flds -0x24(%%ebp)\n\t"
      "pushl %%edx\n\t"
      "fmuls 0x8(%%eax)\n\t"
      "pushl %%ebx\n\t"
      ".byte 0xde, 0xe9\n\t"
      "flds -0x28(%%ebp)\n\t"
      "fmuls 0x8(%%eax)\n\t"
      "flds -0x20(%%ebp)\n\t"
      "fmuls (%%eax)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "flds -0x24(%%ebp)\n\t"
      "fmuls (%%eax)\n\t"
      "flds -0x28(%%ebp)\n\t"
      "fmuls 0x4(%%eax)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fxch %%st(2)\n\t"
      "fmuls (%%esi)\n\t"
      "fxch %%st(2)\n\t"
      "fmuls 0x8(%%esi)\n\t"
      ".byte 0xde, 0xc2\n\t"
      "fmuls 0x4(%%esi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fmuls 0x20(%%edi)\n\t"
      "fmuls 0x10(%%ebp)\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "flds -0x28(%%ebp)\n\t"
      "fmuls (%%esi)\n\t"
      "flds -0x20(%%ebp)\n\t"
      "fmuls 0x8(%%esi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds -0x24(%%ebp)\n\t"
      "fmuls 0x4(%%esi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fmuls 0x20(%%edi)\n\t"
      "fmuls 0x10(%%ebp)\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "call *%[cb8cf0]\n\t"
      "addl $0x10, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [gtime] "m"(ba3890_gtime), [norm] "m"(ba3890_norm), [cb7e30] "m"(ba3890_cb7e30), [c10cc40] "m"(ba3890_c10cc40), [c10c3c0] "m"(ba3890_c10c3c0), [ftol] "m"(ba3890_ftol), [lseed] "m"(ba3890_lseed), [rrange] "m"(ba3890_rrange), [rots] "m"(ba3890_rots), [cb7f10] "m"(ba3890_cb7f10), [cb8cf0] "m"(ba3890_cb8cf0)
      : "memory");
}
#else
#error "FUN_000a3890: clang naked draft required"
#endif

