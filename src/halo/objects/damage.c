
/* Initialize a damage_params struct with a damage effect tag index (0x136750).
 * Zeroes 0x54 bytes, sets tag_index at +0x00, and initializes sentinel/default
 * fields to -1 and scale fields at +0x40/+0x44 to 1.0f. */
void damage_data_new(void *damage_params, int tag_index)
{
  csmemset(damage_params, 0, 0x54);
  *(int *)damage_params = tag_index;
  *(int16_t *)((char *)damage_params + 0x4c) = -1;
  *(int *)((char *)damage_params + 0x08) = -1;
  *(int *)((char *)damage_params + 0x0c) = -1;
  *(int16_t *)((char *)damage_params + 0x10) = -1;
  *(int16_t *)((char *)damage_params + 0x18) = -1;
  *(float *)((char *)damage_params + 0x40) = 1.0f;
  *(float *)((char *)damage_params + 0x44) = 1.0f;
}

/* object_restore_body (0x136790) — Check if object body vitality is below full
 * and restore it to 1.0f if so.
 *
 * Returns true (1) if vitality was restored, false (0) if the object has
 * bit 2 of flags byte at +0xb6 set (damage-related flag) or if vitality
 * is already >= 1.0f.
 *
 * Confirmed: object_get_and_verify_type(handle, -1) at 0x136799.
 * Confirmed: TEST AL,0x4 at 0x1367ab checks bit 2 of [obj+0xb6].
 * Confirmed: FLD [ECX+0x90]; FCOMP [0x2533c8] compares vitality with 1.0f.
 * Confirmed: FNSTSW AX; TEST AH,0x5; JP tests "not less than" (>= or NaN).
 * Confirmed: MOV [ECX+0x90],0x3f800000 sets vitality to 1.0f.
 * Confirmed: XOR DL,DL sets default false return before first branch.
 * Confirmed: caller at 0xbd055 tests return with TEST AL,AL (bool).
 */
char object_restore_body(int object_handle)
{
  char *obj;

  obj = (char *)object_get_and_verify_type(object_handle, -1);
  if ((*(unsigned char *)(obj + 0xb6) & 4) != 0)
    return 0;
  if (*(float *)(obj + 0x90) < 1.0f) {
    *(float *)(obj + 0x90) = 1.0f;
    return 1;
  }
  return 0;
}

/* object_double_charge_shield (0x1367e0) — Check if object shield vitality is
 * at or below full and prepare it for shield regeneration if so.
 *
 * If shield vitality > 1.0f, returns false (0).
 * If shield vitality <= 1.0f:
 *   - Sets bit 4 of flags byte at object+0xb6
 *   - If shield vitality == 0.0f, clamps it to 0.01f
 *   - Clears the shield-damage counter word at object+0xb4
 *   - Returns true (1)
 *
 * Confirmed: object_get_and_verify_type(handle, -1) at 0x1367e9.
 * Confirmed: FLD [ECX+0x94]; FCOMP [0x2533c8] compares shield with 1.0f.
 * Confirmed: TEST AH,0x41; JP tests "above" (> 1.0f) → return 0.
 * Confirmed: OR byte [ECX+0xb6],0x10 sets bit 4 of flags byte.
 * Confirmed: FCOMP [0x2533c0]; TEST AH,0x44; JP tests "not equal to 0.0f".
 * Confirmed: MOV [ECX+0x94],0x3c23d70a sets shield to 0.01f.
 * Confirmed: MOV word [ECX+0xb4],0x0 clears shield-damage counter.
 * Confirmed: caller at 0xbd039 tests return with TEST AL,AL (bool).
 */
char object_double_charge_shield(int object_handle)
{
  char *obj;

  obj = (char *)object_get_and_verify_type(object_handle, -1);
  if (*(float *)(obj + 0x94) <= 1.0f) {
    *(unsigned char *)(obj + 0xb6) |= 0x10;
    if (*(float *)(obj + 0x94) == 0.0f) {
      *(float *)(obj + 0x94) = 0.01f;
    }
    *(unsigned short *)(obj + 0xb4) = 0;
    return 1;
  }
  return 0;
}

/* FUN_00136840 (0x136840) — readable C lift from XBE leaf. */
void FUN_00136840(int object_handle)
{
  void *obj;
  int child;
  int sibling;

  obj = object_get_and_verify_type(object_handle, -1);
  child = *(int *)((char *)obj + 0xc8);
  while (child != -1) {
    obj = object_get_and_verify_type(child, -1);
    sibling = *(int *)((char *)obj + 0xc4);
    if (!FUN_0013c740(child)) {
      FUN_00136840(child);
    }
    child = sibling;
  }
}




/* FUN_00136890 (0x136890) — readable C lift. */
int FUN_00136890(int object_index)
{
  int idx;

  idx = object_index;
  if (idx == -1)
    return -1;
  for (;;) {
    if (object_try_and_get_and_verify_type(idx, 3) != NULL)
      return player_index_from_unit_index(idx);
    idx = *(int *)((char *)object_get_and_verify_type(idx, -1) + 0xcc);
    if (idx == -1)
      return -1;
  }
}

/* object_can_take_damage (0x1368e0) — Clear bit 3 of object+0xb7 flags byte for
 * all children/widgets of a given parent handle.
 *
 * Iterates using FUN_000ce450 (first) / FUN_000ce320 (next) to enumerate
 * associated objects. For each, clears bit 3 (AND 0xf7) of the flags byte
 * at offset 0xb7. This is the same byte modified by
 * object_set_ranged_attack_inhibited (bit 0) and
 * object_set_melee_attack_inhibited (bit 7).
 *
 * Confirmed: cdecl, single stack param at [EBP+0x8].
 * Confirmed: object_get_and_verify_type(index, -1) at CALL 0x13d680.
 * Confirmed: AND byte [EAX+0xb7],0xf7 at 0x136908.
 * Confirmed: FUN_000ce450 (first child) at CALL 0xce450.
 * Confirmed: FUN_000ce320 (next child) at CALL 0xce320.
 */
void object_can_take_damage(int player_handle)
{
  int iter_state;
  int object_index;
  char *obj;

  object_index = FUN_000ce450(player_handle, &iter_state);
  while (object_index != -1) {
    obj = (char *)object_get_and_verify_type(object_index, -1);
    *(unsigned char *)(obj + 0xb7) &= 0xf7;
    object_index = FUN_000ce320(player_handle, &iter_state);
  }
}

/* object_get_maximum_body_vitality (0x136930) — Set bit 3 of object+0xb7 flags
 * byte for all children/widgets of a given parent handle.
 *
 * Complement of object_can_take_damage which clears the same bit. Iterates
 * using FUN_000ce450 (first) / FUN_000ce320 (next) to enumerate associated
 * objects. For each, sets bit 3 (OR 0x8) of the flags byte at offset 0xb7.
 *
 * Confirmed: cdecl, single stack param at [EBP+0x8].
 * Confirmed: object_get_and_verify_type(index, -1) at CALL 0x13d680.
 * Confirmed: OR byte [EAX+0xb7],0x8 at 0x136958.
 * Confirmed: FUN_000ce450 (first child) at CALL 0xce450.
 * Confirmed: FUN_000ce320 (next child) at CALL 0xce320.
 */
void object_get_maximum_body_vitality(int player_handle)
{
  int iter_state;
  int object_index;
  char *obj;

  object_index = FUN_000ce450(player_handle, &iter_state);
  while (object_index != -1) {
    obj = (char *)object_get_and_verify_type(object_index, -1);
    *(unsigned char *)(obj + 0xb7) |= 0x8;
    object_index = FUN_000ce320(player_handle, &iter_state);
  }
}

/* object_set_ranged_attack_inhibited (0x136980) — Set or clear the
 * damage-invincible bit on an object.
 *
 * If object_handle is valid (!= -1), gets the object and sets or clears
 * bit 0 of byte at object+0xb7 based on the flag parameter.
 *
 * Confirmed: CMP EAX,-1; JZ skip at 0x136986.
 * Confirmed: object_get_and_verify_type(handle, -1) at 0x13698e.
 * Confirmed: OR byte [EAX+0xb7],0x1 (set) at 0x13699d.
 * Confirmed: AND byte [EAX+0xb7],0xfe (clear) at 0x1369a6.
 * Confirmed: flag at [EBP+0xc] tested via TEST CL,CL at 0x136999.
 */
void object_set_ranged_attack_inhibited(int object_handle, char flag)
{
  char *obj;

  if (object_handle != -1) {
    obj = (char *)object_get_and_verify_type(object_handle, -1);
    if (flag != 0) {
      *(unsigned char *)(obj + 0xb7) |= 1;
      return;
    }
    *(unsigned char *)(obj + 0xb7) &= 0xfe;
  }
}

/* object_set_melee_attack_inhibited (0x1369b0) — Set or clear bit 7 of
 * object+0xb6 flags byte.
 *
 * Confirmed: identical structure to object_set_ranged_attack_inhibited but
 * targets offset 0xb6 bit 7. Confirmed: OR byte [EAX+0xb6],0x80 (set) at
 * 0x1369cd. Confirmed: AND byte [EAX+0xb6],0x7f (clear) at 0x1369d6.
 */
void object_set_melee_attack_inhibited(int object_handle, char flag)
{
  char *obj;

  if (object_handle != -1) {
    obj = (char *)object_get_and_verify_type(object_handle, -1);
    if (flag != 0) {
      *(unsigned char *)(obj + 0xb6) |= 0x80;
      return;
    }
    *(unsigned char *)(obj + 0xb6) &= 0x7f;
  }
}

/* FUN_001369e0 (0x1369e0) — Create effect on object (damage-related wrapper).
 *
 * Wrapper around FUN_0009ec30 (effect creation). Passes the object_handle as
 * both object_handle and parent_handle, marker=-1, and zeros for remaining
 * args.
 *
 * Confirmed: @EAX register arg (object_handle) from both callers:
 *   0x136e13: MOV EAX,EDI; CALL 0x1369e0
 *   0x138717: MOV EAX,EDI; CALL 0x1369e0
 * Confirmed: 8 pushes before CALL 0x0009ec30, ADD ESP,0x20.
 * Confirmed: push order: 0,0,0,0,-1,EAX,EAX,[EBP+8].
 * Confirmed: void return (callers ignore EAX after call).
 */
void FUN_001369e0(int object_handle, int effect_tag_index)
{
  FUN_0009ec30(effect_tag_index, object_handle, object_handle, -1, 0, 0, 0,
               0); /* dup-args-ok: confirmed PUSH EAX,EAX */
}

/* FUN_00136a00 (0x136a00) — readable C lift. */
void FUN_00136a00(int object_handle, char param_1)
{
  char *obj;
  void *obj_tag;
  void *coll_tag;
  int *block;
  int i;
  char *elem;

  obj = (char *)object_get_and_verify_type(object_handle, -1);
  obj_tag = tag_get(0x6f626a65, *(int *)obj);
  coll_tag = tag_get(0x636f6c6c, *(int *)((char *)obj_tag + 0x7c));
  block = (int *)((char *)coll_tag + 0x240);
  for (i = 0; i < block[0]; i++) {
    elem = (char *)tag_block_get_element(block, i, 0x54);
    if ((*(uint8_t *)(elem + 0x20) & 0x10) && *(int *)(elem + 0x48) > 1)
      obj[0x130 + i] = (param_1 == 0);
  }
}

/* object_get_actual_body_vitality (0x136a80) — Compute scaled body vitality for
 * an object.
 *
 * Returns body_vitality * body_max_vitality, optionally scaled by the
 * difficulty modifier for value_type 1 (body vitality) when param_2 is 0.
 * When param_2 is non-zero, no difficulty scaling is applied.
 *
 * Object offsets:
 *   +0x68: team index (uint16_t), passed to FUN_000b55b0 as team arg
 *   +0x88: body vitality (float)
 *   +0x90: body max vitality (float)
 *
 * Confirmed: PUSH -1; PUSH ESI; CALL 0x13d680 => object_get_and_verify_type x2.
 * Confirmed: MOV EAX,[EAX+0x90] stores body_max_vitality in local [EBP-8].
 * Confirmed: FLD [EAX+0x88] loads body_vitality; FST [EBP-4] copies to local.
 * Confirmed: TEST CL,CL branches on param_2.
 * Confirmed: XOR ECX,ECX; MOV CX,[EAX+0x68] zero-extends team to int.
 * Confirmed: PUSH ECX; PUSH 1; CALL 0xb55b0 => FUN_000b55b0(1, team).
 * Confirmed: FMUL [EBP-4] then FMUL [EBP-8] for final result.
 * Confirmed: caller at 0x52211 pushes [PUSH 0; PUSH ECX] => (handle, 0).
 */
float object_get_actual_body_vitality(int object_handle, char param_2)
{
  char *obj;
  float body_max_vitality;
  float body_vitality;
  float scale;

  obj = (char *)object_get_and_verify_type(object_handle, -1);
  body_max_vitality = *(float *)(obj + 0x90);
  obj = (char *)object_get_and_verify_type(object_handle, -1);
  body_vitality = *(float *)(obj + 0x88);
  scale = body_vitality;
  if (param_2 == 0) {
    scale = FUN_000b55b0(1, (int)*(unsigned short *)(obj + 0x68));
    scale = scale * body_vitality;
  }
  return scale * body_max_vitality;
}

/* object_get_actual_shield_vitality (0x136ae0) — Compute scaled shield vitality
 * for an object.
 *
 * Returns shield_vitality * shield_max_vitality, optionally scaled by the
 * difficulty modifier for value_type 2 (shield vitality) when param_2 is 0.
 * When param_2 is non-zero, no difficulty scaling is applied.
 *
 * Object offsets:
 *   +0x68: team index (uint16_t), passed to FUN_000b55b0 as team arg
 *   +0x8c: shield vitality (float)
 *   +0x94: shield max vitality (float)
 *
 * Confirmed: PUSH -1; PUSH ESI; CALL 0x13d680 => object_get_and_verify_type x2.
 * Confirmed: MOV EAX,[EAX+0x94] stores shield_max_vitality in local [EBP-8].
 * Confirmed: FLD [EAX+0x8c] loads shield_vitality; FST [EBP-4] copies to local.
 * Confirmed: TEST CL,CL branches on param_2.
 * Confirmed: XOR ECX,ECX; MOV CX,[EAX+0x68] zero-extends team to int.
 * Confirmed: PUSH ECX; PUSH 2; CALL 0xb55b0 => FUN_000b55b0(2, team).
 * Confirmed: FMUL [EBP-4] then FMUL [EBP-8] for final result.
 * Confirmed: caller at 0x521f5 pushes [PUSH 0; PUSH EDX] => (handle, 0).
 */
float object_get_actual_shield_vitality(int object_handle, char param_2)
{
  char *obj;
  float shield_max_vitality;
  float shield_vitality;
  float scale;

  obj = (char *)object_get_and_verify_type(object_handle, -1);
  shield_max_vitality = *(float *)(obj + 0x94);
  obj = (char *)object_get_and_verify_type(object_handle, -1);
  shield_vitality = *(float *)(obj + 0x8c);
  scale = shield_vitality;
  if (param_2 == 0) {
    scale = FUN_000b55b0(2, (int)*(unsigned short *)(obj + 0x68));
    scale = scale * shield_vitality;
  }
  return scale * shield_max_vitality;
}

/* object_deplete_shield (0x136b40) — One-shot "vitality pool just hit zero"
 * transition for the pool tracked by obj+0x94.
 *
 * Name is INFERRED, not string-proven: this is the paired sibling of the
 * confirmed object_deplete_body (0x137540). FUN_001a7b50 (units.c) contains two
 * adjacent, structurally identical blocks — one calls 0x136b40 when the
 * obj+0x94 ratio transitions to zero, the other calls object_deplete_body when
 * the obj+0x90 ratio does. The two functions differ only in which flag bit they
 * latch (0x8 here vs 0x4) and which 'coll' effect field they fire
 * (coll+0x1a4 here vs coll+0xb4).
 *
 * If bit 3 of the damage flags byte (obj+0xb6) is not already set:
 *   1. Looks up the object's collision model tag (obje+0x7c -> 'coll')
 *   2. If the collision model has an effect reference at coll+0x1a4 (!= -1),
 *      creates that effect on the object via FUN_0009ec30
 *   3. Sets bit 3 of obj+0xb6
 *   4. Clears obj+0x98 (damage-related counter/timer)
 *   5. Calls FUN_00136a00 to set region "cannot be destroyed" bytes
 *
 * Confirmed: cdecl, 1 stack param (object_handle), void return.
 * Confirmed: PUSH -1; PUSH EDI; CALL 0x13d680 => object_get_and_verify_type.
 * Confirmed: TEST AL,0x8 at 0x136b5b checks bit 3 of [ESI+0xb6].
 * Confirmed: tag_get('obje', [ESI]) at CALL 0x1ba140.
 * Confirmed: CMP EAX,-1 at 0x136b72 checks collision model index.
 * Confirmed: tag_get('coll', obje[0x7c]) at second CALL 0x1ba140.
 * Confirmed: 8 pushes [0,0,0,0,-1,EDI,EDI,ECX] before CALL 0x9ec30. The
 *   ADD ESP,0x28 after it is 0x20 (8 args) plus the folded 0x8 cleanup of the
 *   preceding tag_get, so the ARG_COUNT hazard (cleanup=10) is a FALSE POSITIVE
 *   and FUN_0009ec30's 8-param decl is correct.
 * Confirmed: params 5/6 are plain PUSH 0 immediates (no FLD/FSTP), i.e. float
 *   literal zeros, not a push-then-fstp float.
 * Confirmed: OR byte [ESI+0xb6],0x8 at 0x136b9d sets bit 3 (BYTE, not widened).
 * Confirmed: MOV [ESI+0x98],0x0 at 0x136ba8 clears dword.
 * Confirmed: MOV EAX,EDI; CALL 0x136a00 => FUN_00136a00(@EAX=handle, 0).
 */
void object_deplete_shield(int object_handle)
{
  char *obj;
  char *obje_tag;
  char *coll_tag;
  int coll_index;

  obj = (char *)object_get_and_verify_type(object_handle, -1);
  if ((*(unsigned char *)(obj + 0xb6) & 8) == 0) {
    obje_tag = (char *)tag_get(0x6f626a65, *(int *)obj);
    coll_index = *(int *)(obje_tag + 0x7c);
    if (coll_index != -1) {
      coll_tag = (char *)tag_get(0x636f6c6c, coll_index);
      FUN_0009ec30(*(int *)(coll_tag + 0x1a4), object_handle, object_handle, -1,
                   0.0f, 0.0f, 0, 0); /* dup-args-ok: confirmed PUSH EDI,EDI */
    }
    *(unsigned char *)(obj + 0xb6) |= 8;
    *(int *)(obj + 0x98) = 0;
    FUN_00136a00(object_handle, 0);
  }
}

/* FUN_00136f40 (0x136f40) — XBE naked draft (batch 51). */
#if defined(__clang__)
static void *(*const b136f40_get)(int, int) = object_get_and_verify_type;
static void *(*const b136f40_tag)(int, int) = tag_get;
static float (*const b136f40_norm)(float *) = normalize3d;
static void (*const b136f40_cf8ee0)(int projectile_handle, float *acceleration) = projectile_accelerate;
static void (*const b136f40_isetpos)(int, float *, int) = item_set_position;
static void (*const b136f40_c1a4a70)(int handle, float *velocity) = FUN_001a4a70;
static void (*const b136f40_c1b5c90)(int handle, float *velocity) = vehicle_accelerate;
static bool (*const b136f40_ca8e40)(void) = game_engine_can_score;
static void (*const b136f40_cb56e0)(int handle, float vitality, int param_3, int param_4, int param_5) = game_statistics_record_damage;
static void (*const b136f40_cb56f0)(int handle, int param_2, int param_3, int param_4) = FUN_000b56f0;
static int (*const b136f40_cba500)(int) = player_index_from_unit_index;
static void (*const b136f40_caf660)(int killer_handle, int kill_object_handle, int dead_handle, int betrayal) = game_engine_player_killed;
static void (*const b136f40_c1b4dc0)(int handle, void *damage_data, unsigned int flags, float body_vitality, float shield_vitality, int param_6, int param_7) = FUN_001b4dc0;

__attribute__((naked, noinline))
void FUN_00136f40(int object_handle __attribute__((unused)), void *damage_data __attribute__((unused)), unsigned int flags __attribute__((unused)), float body_vitality __attribute__((unused)), float shield_vitality __attribute__((unused)), int param_4 __attribute__((unused)), int param_5 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x20, %%esp\n\t"
      "pushl %%edi\n\t"
      "pushl $-1\n\t"
      "pushl %%ebx\n\t"
      "call *%[get]\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "movl (%%eax), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x6f626a65\n\t"
      "call *%[tag]\n\t"
      "movl (%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x6a707421\n\t"
      "movl %%eax, %%edi\n\t"
      "call *%[tag]\n\t"
      "flds 0x20(%%edi)\n\t"
      "fcomps 0x253f44\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "addl $0x18, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00136f40_7\n\t"
      "leal 0x34(%%esi), %%edx\n\t"
      "movl (%%edx), %%eax\n\t"
      "movl 0x4(%%edx), %%ecx\n\t"
      "movl 0x8(%%edx), %%edx\n\t"
      "movl %%edx, -0x18(%%ebp)\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fadds 0x25614c\n\t"
      "movl %%eax, -0x20(%%ebp)\n\t"
      "leal -0x20(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "movl %%ecx, -0x1c(%%ebp)\n\t"
      "call *%[norm]\n\t"
      "fstp %%st(0)\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "flds 0x1f4(%%edx)\n\t"
      "addl $4, %%esp\n\t"
      "fmuls 0x20(%%edi)\n\t"
      "movl -0x4(%%ebp), %%edi\n\t"
      "movw 0x64(%%edi), %%cx\n\t"
      "movswl %%cx, %%eax\n\t"
      "cmpl $5, %%eax\n\t"
      "fmuls 0x2546a4\n\t"
      "flds -0x20(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "fmuls -0x18(%%ebp)\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "ja .LFUN_00136f40_8\n\t"
      "jmp *.LFUN_00136f40_jt(,%%eax,4)\n\t"
      ".LFUN_00136f40_1:\n\t"
      "leal -0x14(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "call *%[cf8ee0]\n\t"
      "addl $8, %%esp\n\t"
      "jmp .LFUN_00136f40_8\n\t"
      ".LFUN_00136f40_2:\n\t"
      "flds 0x40(%%esi)\n\t"
      "fcomps 0x253398\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00136f40_3\n\t"
      "testb $0x20, 0x1c8(%%edx)\n\t"
      "je .LFUN_00136f40_3\n\t"
      "movl $1, %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x14(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ebx\n\t"
      "call *%[isetpos]\n\t"
      "addl $0xc, %%esp\n\t"
      "jmp .LFUN_00136f40_8\n\t"
      ".LFUN_00136f40_3:\n\t"
      "xorl %%eax, %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x14(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ebx\n\t"
      "call *%[isetpos]\n\t"
      "addl $0xc, %%esp\n\t"
      "jmp .LFUN_00136f40_8\n\t"
      ".LFUN_00136f40_4:\n\t"
      "flds 0x1f4(%%edx)\n\t"
      "fcomps 0x253f44\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00136f40_8\n\t"
      "testl $0x800000, 0x1b4(%%edi)\n\t"
      "jne .LFUN_00136f40_8\n\t"
      "testw %%cx, %%cx\n\t"
      "jne .LFUN_00136f40_5\n\t"
      "leal -0x14(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "call *%[c1a4a70]\n\t"
      "addl $8, %%esp\n\t"
      "jmp .LFUN_00136f40_8\n\t"
      ".LFUN_00136f40_5:\n\t"
      "cmpw $1, %%cx\n\t"
      "jne .LFUN_00136f40_8\n\t"
      "testb $0x20, 0x1c8(%%edx)\n\t"
      "je .LFUN_00136f40_6\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fadd %%st(0), %%st(0)\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fadd %%st(0), %%st(0)\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fadd %%st(0), %%st(0)\n\t"
      "fstps -0xc(%%ebp)\n\t"
      ".LFUN_00136f40_6:\n\t"
      "leal -0x14(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "call *%[c1b5c90]\n\t"
      "addl $8, %%esp\n\t"
      "jmp .LFUN_00136f40_8\n\t"
      ".LFUN_00136f40_7:\n\t"
      "movl -0x4(%%ebp), %%edi\n\t"
      ".LFUN_00136f40_8:\n\t"
      "call *%[ca8e40]\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00136f40_9\n\t"
      "movb 0x4(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "js .LFUN_00136f40_9\n\t"
      "movl 0xc(%%esi), %%eax\n\t"
      "flds 0xc(%%ebp)\n\t"
      "movl 0x8(%%esi), %%ecx\n\t"
      "fadds 0x10(%%ebp)\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x10(%%esi), %%dx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ecx\n\t"
      "fstps (%%esp)\n\t"
      "pushl %%ebx\n\t"
      "call *%[cb56e0]\n\t"
      "movb 0x8(%%ebp), %%al\n\t"
      "addl $0x14, %%esp\n\t"
      "testb $1, %%al\n\t"
      "je .LFUN_00136f40_10\n\t"
      "movl 0xc(%%esi), %%eax\n\t"
      "movl 0x8(%%esi), %%ecx\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x10(%%esi), %%dx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "call *%[cb56f0]\n\t"
      "addl $0x10, %%esp\n\t"
      "jmp .LFUN_00136f40_10\n\t"
      ".LFUN_00136f40_9:\n\t"
      "call *%[ca8e40]\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00136f40_10\n\t"
      "pushl %%ebx\n\t"
      "call *%[cba500]\n\t"
      "pushl $1\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "call *%[caf660]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00136f40_10:\n\t"
      "movb 0x64(%%edi), %%cl\n\t"
      "movl $1, %%edx\n\t"
      "shll %%cl, %%edx\n\t"
      "popl %%edi\n\t"
      "testb $3, %%dl\n\t"
      "je .LFUN_00136f40_11\n\t"
      "movl 0x18(%%ebp), %%eax\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "pushl %%eax\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "pushl %%ecx\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%ebx\n\t"
      "call *%[c1b4dc0]\n\t"
      "addl $0x1c, %%esp\n\t"
      ".LFUN_00136f40_11:\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "nop\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_00136f40_jt:\n\t"
      ".long .LFUN_00136f40_4\n\t"
      ".long .LFUN_00136f40_4\n\t"
      ".long .LFUN_00136f40_2\n\t"
      ".long .LFUN_00136f40_2\n\t"
      ".long .LFUN_00136f40_2\n\t"
      ".long .LFUN_00136f40_1\n\t"
      ".text\n\t"
      :
      : [get] "m"(b136f40_get), [tag] "m"(b136f40_tag), [norm] "m"(b136f40_norm), [cf8ee0] "m"(b136f40_cf8ee0), [isetpos] "m"(b136f40_isetpos), [c1a4a70] "m"(b136f40_c1a4a70), [c1b5c90] "m"(b136f40_c1b5c90), [ca8e40] "m"(b136f40_ca8e40), [cb56e0] "m"(b136f40_cb56e0), [cb56f0] "m"(b136f40_cb56f0), [cba500] "m"(b136f40_cba500), [caf660] "m"(b136f40_caf660), [c1b4dc0] "m"(b136f40_c1b4dc0)
      : "memory");
}
#else
#error "FUN_00136f40: clang naked draft required"
#endif


/* render_debug_object_damage (0x137370) — Damage debug overlay: display damage
 * vitality info for a targeted object, and handle picking a new target via
 * collision ray.
 *
 * When the damage debug flag (DAT_005a90c0) is set, this function:
 * 1. Formats a debug string with the targeted object's body/shield vitality,
 *    current damage, and recent damage values (offsets 0x90..0xa8).
 *    If no object is targeted (DAT_0046f070 == -1), shows "no object to debug".
 * 2. Sets up text drawing style/color and renders the string on screen.
 * 3. Checks if the spacebar (key 0x48) is held; if so, casts a collision ray
 *    from the camera position along a scaled direction to pick a new target.
 *    If the collision hits an object (type == 3), stores it as the new target.
 *
 * Confirmed: SUB ESP,0x864 for stack frame.
 * Confirmed: DAT_005a90c0 is the damage debug enable flag.
 * Confirmed: DAT_0046f070 is the current debug target object handle.
 * Confirmed: object_try_and_get_and_verify_type(handle, -1) at CALL 0x13d640.
 * Confirmed: tag_get_name(*obj) at CALL 0x1ba1f0.
 * Confirmed: strrchr(path, '\\') at CALL 0x1d9710 to get filename part.
 * Confirmed: _snprintf at CALL 0x1d9179 with 0x800 buffer.
 * Confirmed: draw_string_set_style_justify_flags(-1, 0, 0) at CALL 0x19b800.
 * Confirmed: draw_string_set_color(*(void**)0x2ee6c4) at CALL 0x19b640.
 * Confirmed: rasterizer_text_draw(&rect, NULL, NULL, 0, buf) at CALL 0x183e60.
 * Confirmed: input_key_is_down(0x48) = spacebar at CALL 0xcf560.
 * Confirmed: local_player_get_player_index at CALL 0xba3c0.
 * Confirmed: datum_get(*(data_t**)0x5aa6d4, handle) for player data at
 * 0x119320. Confirmed: Player object handle at player+0x34. Confirmed:
 * FUN_0014df70 collision test with 5 args at CALL 0x14df70. Confirmed:
 * collision type == 3 check at CMP word [EBP-0x64],0x3. Confirmed: collision
 * object handle at [EBP-0x2c] (offset 0x38 in result). Confirmed: assert string
 * "collision.type==_collision_result_object" at 0x29af70. Confirmed:
 * display_assert at CALL 0x8d9f0, system_exit at CALL 0x8e2f0.
 */
void render_debug_object_damage(void)
{
  typedef int(__cdecl * fn_snprintf_t)(char *, int, const char *, ...);
  fn_snprintf_t snprintf_fn;

  char string_buffer[2048];
  int16_t collision_result[40];
  float direction[3];
  int16_t rect[4];

  char *obj;
  char *tag_path;
  char *filename;
  int debug_handle;
  int player_index;
  char *player;
  int object_handle;

  if (*(char *)0x5a90c0 == 0)
    return;

  snprintf_fn = (fn_snprintf_t)0x1d9179;

  /* Copy screen rect from globals and adjust y by +0x140 */
  *(int *)&rect[0] = *(int *)0x506584;
  *(int *)&rect[2] = *(int *)0x506588;
  rect[1] = (int16_t)(rect[1] + 0x140);

  debug_handle = *(int *)0x46f070;
  if (debug_handle == -1) {
    /* No object targeted */
    snprintf_fn(string_buffer, 0x800,
                "no object to debug|n(point and press space)");
  } else {
    obj = (char *)object_try_and_get_and_verify_type(debug_handle, -1);
    if (obj == (char *)0) {
      *(int *)0x46f070 = -1;
    } else {
      /* Get tag path for this object's definition tag, extract filename */
      tag_path = (char *)tag_get_name(*(int *)obj);
      filename = strrchr(tag_path, 0x5c);
      snprintf_fn(
        string_buffer, 0x800,
        "%s|nbody %0.3f|n  current %0.3f|n  recent %0.3f|n"
        "shield %0.3f|n  current %0.3f|n  recent %0.3f|n",
        filename, (double)*(float *)(obj + 0x90),
        (double)*(float *)(obj + 0x9c), (double)*(float *)(obj + 0xa8),
        (double)*(float *)(obj + 0x94), (double)*(float *)(obj + 0x98),
        (double)*(float *)(obj + 0xa4));
    }
  }

  /* Set text drawing style: plain, left-justified, no flags */
  draw_string_set_style_justify_flags(-1, 0, 0);

  /* Set text color from global pointer */
  draw_string_set_color(*(void **)0x2ee6c4);

  /* Draw the debug text on screen */
  rasterizer_text_draw(&rect[0], (short *)0, (void *)0, 0, string_buffer);

  /* Check if spacebar is held (key 0x48) to pick a new damage debug target */
  if (input_key_is_down(0x48) == 0)
    return;

  /* Get local player's object handle, default to -1 */
  {
    uint16_t local_player_index;
    local_player_index = *(uint16_t *)0x506548;
    object_handle = -1;
    if ((int16_t)local_player_index != -1) {
      player_index = local_player_get_player_index(local_player_index);
      player = (char *)datum_get(*(data_t **)0x5aa6d4, player_index);
      object_handle = *(int *)(player + 0x34);
    }
  }

  /* Build direction vector: scale camera direction by global factor */
  direction[0] = *(float *)0x50655c * *(float *)0x25acf0;
  direction[1] = *(float *)0x506560 * *(float *)0x25acf0;
  direction[2] = *(float *)0x506564 * *(float *)0x25acf0;

  /* Cast a collision ray from camera position along the scaled direction */
  if (FUN_0014df70(0x81, (float *)0x506550, direction, object_handle,
                   collision_result) == 0)
    return;

  /* Verify collision result is an object hit */
  if (collision_result[0] != 3) {
    display_assert("collision.type==_collision_result_object",
                   "c:\\halo\\SOURCE\\objects\\damage.c", 0x794, 1);
    system_exit(-1);
  }

  /* Store the hit object as the new debug target */
  /* collision_result offset 0x38 = object handle (EBP-0x2c from EBP-0x64 base)
   */
  *(int *)0x46f070 = *(int *)((char *)collision_result + 0x38);
}

/* object_deplete_body (0x137540) — Set "body depleted" flag and detach child
 * units.
 *
 * If bit 2 of the damage flags byte (obj+0xb6) is not already set:
 *   1. Sets bit 2 of obj+0xb6
 *   2. Looks up the object's collision model tag (obje+0x7c -> 'coll')
 *   3. If the collision model has an effect reference at coll+0xb4 (!= -1),
 *      creates that effect on the object via FUN_0009ec30
 *   4. If the object type (obj+0x64) is 1 (biped), iterates the child object
 *      list (starting at obj+0xc8, next-sibling at child+0xc4). For each child
 *      of type 0 (biped) that meets the activation criteria:
 *        - child+0x1c8 == -1, or the global byte at 0x5aa890 is 0
 *        - child+0x2a0 != -1 (short)
 *      calls unit_set_actively_controlled_flag to set the actively-controlled
 *      flag on that child unit
 *   5. Calls object_deplete_shield to trigger the initial body-damage effect
 *
 * Confirmed: cdecl, 1 stack param (object_handle), void return.
 * Confirmed: PUSH -1; PUSH EDI; CALL 0x13d680 => object_get_and_verify_type.
 * Confirmed: TEST AL,0x4 at 0x137561 checks bit 2 of [ESI+0xb6].
 * Confirmed: OR EAX,0x4; MOV [ESI+0xb6],AX sets bit 2.
 * Confirmed: tag_get('obje', [ESI]) at CALL 0x1ba140.
 * Confirmed: MOV EAX,[EAX+0x7c] reads collision model index.
 * Confirmed: tag_get('coll', coll_index) at second CALL 0x1ba140.
 * Confirmed: MOV ECX,[EAX+0xb4] reads effect index from coll tag.
 * Confirmed: 8 pushes [0,0,0,0,EBX,EDI,EDI,ECX] before CALL 0x9ec30.
 * Confirmed: CMP word [ESI+0x64],0x1 checks object type == 1.
 * Confirmed: MOV EDI,[ESI+0xc8] reads first child handle.
 * Confirmed: CMP word [ESI+0x64],0x0 checks child type == 0.
 * Confirmed: CMP [ESI+0x1c8],EBX checks child+0x1c8 == -1.
 * Confirmed: MOV AL,[0x5aa890]; TEST AL,AL checks global byte.
 * Confirmed: CMP word [ESI+0x2a0],BX checks child+0x2a0 != -1.
 * Confirmed: PUSH EDI; CALL 0x1a7f80 => unit_set_actively_controlled_flag.
 * Confirmed: MOV EDI,[ESI+0xc4] reads next sibling.
 * Confirmed: MOV EDI,[EBP+0x8] restores param_1 before object_deplete_shield
 * call. Confirmed: PUSH EDI; CALL 0x136b40 =>
 * object_deplete_shield(object_handle).
 */
void object_deplete_body(int object_handle)
{
  char *obj;
  char *obje_tag;
  char *coll_tag;
  int coll_index;
  int child_handle;
  char *child_obj;

  obj = (char *)object_get_and_verify_type(object_handle, -1);
  if ((*(unsigned short *)(obj + 0xb6) & 4) == 0) {
    *(unsigned short *)(obj + 0xb6) = *(unsigned short *)(obj + 0xb6) | 4;
    obje_tag = (char *)tag_get(0x6f626a65, *(int *)obj);
    coll_index = *(int *)(obje_tag + 0x7c);
    if (coll_index != -1) {
      coll_tag = (char *)tag_get(0x636f6c6c, coll_index);
      FUN_0009ec30(*(int *)(coll_tag + 0xb4), object_handle, object_handle, -1,
                   0, 0, 0, 0); /* dup-args-ok: confirmed PUSH EDI,EDI */
    }
    if (*(short *)(obj + 0x64) == 1) {
      child_handle = *(int *)(obj + 0xc8);
      while (child_handle != -1) {
        child_obj = (char *)object_get_and_verify_type(child_handle, -1);
        if (*(short *)(child_obj + 0x64) == 0 &&
            (*(int *)(child_obj + 0x1c8) == -1 || *(char *)0x5aa890 == 0) &&
            *(short *)(child_obj + 0x2a0) != -1) {
          unit_set_actively_controlled_flag(child_handle);
        }
        child_handle = *(int *)(child_obj + 0xc4);
      }
    }
    object_deplete_shield(object_handle);
  }
}

/* object_destroy (0x137620) — Object death/destruction handler.
 *
 * Called when an object is destroyed (killed). Performs the death sequence:
 *   1. Gets the object's tag definition ('obje') from the object data
 *   2. Calls object_deplete_body to handle death-related flag setting and child
 *      object detachment
 *   3. If the object has a collision model (obje+0x7c != -1), looks up the
 *      collision tag ('coll') and creates the destroy effect from coll+0xc8
 *      on the object via FUN_0009ec30
 *   4. Calls FUN_00136840 to recursively process child objects
 *   5. Calls object_delete for final destruction cleanup
 *
 * Confirmed: cdecl, 1 stack param (object_handle), void return.
 * Confirmed: PUSH -1; PUSH ESI; CALL 0x13d680 => object_get_and_verify_type.
 * Confirmed: MOV EAX,[EAX] dereferences first dword of object (tag index).
 * Confirmed: PUSH EAX; PUSH 0x6f626a65; CALL 0x1ba140 => tag_get('obje', ...).
 * Confirmed: MOV EDI,EAX saves obje_tag in EDI.
 * Confirmed: PUSH ESI; CALL 0x137540 => object_deplete_body(object_handle).
 * Confirmed: MOV EAX,[EDI+0x7c] reads collision model index from obje tag.
 * Confirmed: CMP EAX,-1 at 0x13764b checks collision model presence.
 * Confirmed: tag_get('coll', collision_index) at second CALL 0x1ba140.
 * Confirmed: MOV ECX,[EAX+0xc8] reads destroy effect index from coll tag.
 * Confirmed: 8 pushes [0,0,0,0,-1,ESI,ESI,ECX] before CALL 0x9ec30.
 * Confirmed: PUSH ESI; CALL 0x136840 => FUN_00136840(object_handle).
 * Confirmed: PUSH ESI; CALL 0x140cc0 => object_delete(object_handle).
 */
void object_destroy(int object_handle)
{
  int *obj;
  char *obje_tag;
  char *coll_tag;
  int coll_index;

  obj = (int *)object_get_and_verify_type(object_handle, -1);
  obje_tag = (char *)tag_get(0x6f626a65, *obj);
  object_deplete_body(object_handle);
  coll_index = *(int *)(obje_tag + 0x7c);
  if (coll_index != -1) {
    coll_tag = (char *)tag_get(0x636f6c6c, coll_index);
    FUN_0009ec30(*(int *)(coll_tag + 0xc8), object_handle, object_handle, -1, 0,
                 0, 0, 0); /* dup-args-ok: confirmed PUSH ESI,ESI */
  }
  FUN_00136840(object_handle);
  object_delete(object_handle);
}

/* FUN_00137690 (0x137690) — XBE naked draft (batch 54). */
#if defined(__clang__)
static void *(*const b137690_get)(int, int) = object_get_and_verify_type;
static void *(*const b137690_tag)(int, int) = tag_get;
static void (*const b137690_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b137690_exitfn)(int) = system_exit;
static void *(*const b137690_elem)(void *, int, int) = tag_block_get_element;
static int (*const b137690_o9ec30)(int, int, int, short, float, float, int, int) = FUN_0009ec30;
static void (*const b137690_c1402c0)(int object_handle, const char *marker_name, short region_index, char param_4) = object_permute_region;
static void (*const b137690_c137540)(int object_handle) = object_deplete_body;
static void (*const b137690_c13c6e0)(int object_handle, int region_index, unsigned int flags) = FUN_0013c6e0;

__attribute__((naked, noinline))
void FUN_00137690(int object_handle __attribute__((unused)), short region_index __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ebx\n\t"
      "pushl $-1\n\t"
      "pushl %%edi\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl (%%ebx), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x6f626a65\n\t"
      "call *%[tag]\n\t"
      "movl 0x7c(%%eax), %%eax\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_00137690_9\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "pushl $0x636f6c6c\n\t"
      "call *%[tag]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "testw %%ax, %%ax\n\t"
      "jl .LFUN_00137690_1\n\t"
      "cmpw $8, %%ax\n\t"
      "jl .LFUN_00137690_2\n\t"
      ".LFUN_00137690_1:\n\t"
      "pushl $1\n\t"
      "pushl $0x71a\n\t"
      "pushl $0x29af50\n\t"
      "pushl $0x29b03c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00137690_2:\n\t"
      "movswl %%ax, %%ecx\n\t"
      "movzwl 0x124(%%ebx), %%eax\n\t"
      "movl $1, %%edx\n\t"
      "shll %%cl, %%edx\n\t"
      "testl %%edx, %%eax\n\t"
      "jne .LFUN_00137690_8\n\t"
      "pushl $0x54\n\t"
      "pushl %%ecx\n\t"
      "addl $0x240, %%esi\n\t"
      "pushl %%esi\n\t"
      "call *%[elem]\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl $-1\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x44(%%esi), %%ecx\n\t"
      "pushl %%edi\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "call *%[o9ec30]\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "pushl $1\n\t"
      "pushl %%edx\n\t"
      "pushl $0x29b030\n\t"
      "pushl %%edi\n\t"
      "call *%[c1402c0]\n\t"
      "movb 0x20(%%esi), %%al\n\t"
      "addl $0x3c, %%esp\n\t"
      "testb $0x20, %%al\n\t"
      "movl $0x80, %%ecx\n\t"
      "je .LFUN_00137690_3\n\t"
      "orw %%cx, 0xb6(%%ebx)\n\t"
      ".LFUN_00137690_3:\n\t"
      "testb $0x40, 0x20(%%esi)\n\t"
      "movl $0x100, %%eax\n\t"
      "je .LFUN_00137690_4\n\t"
      "orw %%ax, 0xb6(%%ebx)\n\t"
      ".LFUN_00137690_4:\n\t"
      "testb %%cl, 0x20(%%esi)\n\t"
      "je .LFUN_00137690_5\n\t"
      "orb $2, 0xb7(%%ebx)\n\t"
      ".LFUN_00137690_5:\n\t"
      "testl %%eax, 0x20(%%esi)\n\t"
      "je .LFUN_00137690_6\n\t"
      "orb $4, 0xb7(%%ebx)\n\t"
      ".LFUN_00137690_6:\n\t"
      "testb $2, 0x20(%%esi)\n\t"
      "je .LFUN_00137690_7\n\t"
      "pushl %%edi\n\t"
      "call *%[c137540]\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_00137690_7:\n\t"
      "movswl 0x8(%%ebp), %%ecx\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "movl $1, %%eax\n\t"
      "shll %%cl, %%eax\n\t"
      "orw %%ax, 0x124(%%ebx)\n\t"
      "movl 0x20(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "call *%[c13c6e0]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_00137690_8:\n\t"
      "popl %%esi\n\t"
      ".LFUN_00137690_9:\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "nop\n\t"
      :
      : [get] "m"(b137690_get), [tag] "m"(b137690_tag), [assert] "m"(b137690_assert), [exitfn] "m"(b137690_exitfn), [elem] "m"(b137690_elem), [o9ec30] "m"(b137690_o9ec30), [c1402c0] "m"(b137690_c1402c0), [c137540] "m"(b137690_c137540), [c13c6e0] "m"(b137690_c13c6e0)
      : "memory");
}
#else
#error "FUN_00137690: clang naked draft required"
#endif


/* object_cause_damage (0x137d20) — XBE naked draft (batch 50). */
#if defined(__clang__)
static void *(*const b137d20_tag)(int, int) = tag_get;
static void (*const b137d20_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b137d20_exitfn)(int) = system_exit;
static int *(*const b137d20_gseed)(void) = get_global_random_seed_address;
static float (*const b137d20_rrange)(int *, float, float) = random_real_range;
static void *(*const b137d20_tryget)(int, int) = object_try_and_get_and_verify_type;
static void *(*const b137d20_get)(int, int) = object_get_and_verify_type;
static char (*const b137d20_c3f900)(int player_index, void *damage_params, float *scale) = ai_adjust_damage;
static bool (*const b137d20_gerun)(void) = game_engine_running;
static int (*const b137d20_c136890)(int object_index) = FUN_00136890;
static float (*const b137d20_cad530)(int player_a, int player_b) = game_engine_get_damage_multiplier;
static bool (*const b137d20_ca7a30)(int16_t team_a, int16_t team_b) = game_allegiance_get_team_is_friendly;
static float (*const b137d20_cb5590)(int16_t value_type) = FUN_000b5590;
static void (*const b137d20_c137d20)(void *damage_params, int object_handle, short node_index, short region_index, short permutation_index, unsigned int flags) = object_cause_damage;
static int (*const b137d20_cba3c0)(int16_t local_player_index) = local_player_get_player_index;
static void (*const b137d20_ca3b80)(int player_index, void *damage_params, void *position, float damage_amount, float scale) = FUN_000a3b80;
static void *(*const b137d20_elem)(void *, int, int) = tag_block_get_element;
static char (*const b137d20_c1b1d00)(int object_handle, void *position) = unit_unsuspecting;
static void (*const b137d20_c137540)(int object_handle) = object_deplete_body;
static void (*const b137d20_c136bc0)(int current_object_handle, void *collision_model, void *material, void *damage_effect, void *damage_params, unsigned int *flags, float *shield_damage, float *body_damage) = FUN_00136bc0;
static void (*const b137d20_c1377d0)(int object_handle, int region_index, int node_index, unsigned int param_4, void *collision_model, void *material, void *damage_effect, void *damage_params, unsigned int *flags, float *body_damage, void **param_11, float scale) = FUN_001377d0;
static const char * (*const b137d20_cb5490)(short material_type) = FUN_000b5490;
static const char * (*const b137d20_c1ba1f0)(int tag_index) = tag_get_name;
static char * (*const b137d20_c1d9710)(const char *str, int c) = strrchr;
static void (*const b137d20_cff4d0)(int channel, const char *format, ...) = console_printf;
static void (*const b137d20_c136f40)(int object_handle, void *damage_data, unsigned int flags, float body_vitality, float shield_vitality, int param_4, int param_5) = FUN_00136f40;
static void (*const b137d20_odel)(int) = object_delete;

__attribute__((naked, noinline))
void object_cause_damage(void *damage_params __attribute__((unused)), int object_handle __attribute__((unused)), short node_index __attribute__((unused)), short region_index __attribute__((unused)), short permutation_index __attribute__((unused)), unsigned int flags __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x74, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "movl (%%esi), %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "pushl $0x6a707421\n\t"
      "call *%[tag]\n\t"
      "movl %%eax, %%edi\n\t"
      "movw 0x14(%%ebp), %%ax\n\t"
      "addl $0x1c4, %%edi\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "movl %%edi, -0x18(%%ebp)\n\t"
      "movb $0, 0xb(%%ebp)\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "je .Lobject_cause_damage_2\n\t"
      "testw %%ax, %%ax\n\t"
      "jl .Lobject_cause_damage_1\n\t"
      "cmpw $8, %%ax\n\t"
      "jl .Lobject_cause_damage_2\n\t"
      ".Lobject_cause_damage_1:\n\t"
      "pushl $1\n\t"
      "pushl $0x338\n\t"
      "pushl $0x29af50\n\t"
      "pushl $0x29b138\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lobject_cause_damage_2:\n\t"
      "cmpl $-1, 0x8(%%esi)\n\t"
      "movl 0xc(%%ebp), %%ebx\n\t"
      "je .Lobject_cause_damage_3\n\t"
      "movl %%ebx, 0x46f070\n\t"
      ".Lobject_cause_damage_3:\n\t"
      "movl 0x14(%%edi), %%ecx\n\t"
      "movl 0x10(%%edi), %%edx\n\t"
      "movl %%ecx, %%eax\n\t"
      "movl %%ecx, -0x34(%%ebp)\n\t"
      "pushl %%eax\n\t"
      "movl %%edx, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl %%edx, -0x30(%%ebp)\n\t"
      "call *%[gseed]\n\t"
      "pushl %%eax\n\t"
      "call *%[rrange]\n\t"
      "flds 0x2533c8\n\t"
      "fsubs 0x40(%%esi)\n\t"
      "movl 0xc(%%esi), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "fmuls 0xc(%%edi)\n\t"
      "fxch %%st(1)\n\t"
      "fmuls 0x40(%%esi)\n\t"
      "faddp %%st(1)\n\t"
      "fmuls 0x44(%%esi)\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "je .Lobject_cause_damage_7\n\t"
      "pushl $3\n\t"
      "pushl %%eax\n\t"
      "call *%[tryget]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lobject_cause_damage_7\n\t"
      "movl 0x2d8(%%eax), %%ecx\n\t"
      "cmpl $-1, %%ecx\n\t"
      "je .Lobject_cause_damage_4\n\t"
      "pushl $3\n\t"
      "pushl %%ecx\n\t"
      "call *%[get]\n\t"
      "addl $8, %%esp\n\t"
      ".Lobject_cause_damage_4:\n\t"
      "movl 0x1a8(%%eax), %%ecx\n\t"
      "cmpl $-1, %%ecx\n\t"
      "je .Lobject_cause_damage_5\n\t"
      "movl %%ecx, %%eax\n\t"
      "jmp .Lobject_cause_damage_6\n\t"
      ".Lobject_cause_damage_5:\n\t"
      "movl 0x1a4(%%eax), %%eax\n\t"
      ".Lobject_cause_damage_6:\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lobject_cause_damage_7\n\t"
      "leal -0xc(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "call *%[c3f900]\n\t"
      "addl $0xc, %%esp\n\t"
      ".Lobject_cause_damage_7:\n\t"
      "call *%[gerun]\n\t"
      "testb %%al, %%al\n\t"
      "je .Lobject_cause_damage_8\n\t"
      "movl %%ebx, %%eax\n\t"
      "call *%[c136890]\n\t"
      "pushl %%eax\n\t"
      "movl 0xc(%%esi), %%eax\n\t"
      "call *%[c136890]\n\t"
      "pushl %%eax\n\t"
      "call *%[cad530]\n\t"
      "addl $8, %%esp\n\t"
      "jmp .Lobject_cause_damage_9\n\t"
      ".Lobject_cause_damage_8:\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x10(%%esi), %%ax\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .Lobject_cause_damage_10\n\t"
      "pushl $1\n\t"
      "pushl %%eax\n\t"
      "call *%[ca7a30]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lobject_cause_damage_10\n\t"
      "pushl $0\n\t"
      "call *%[cb5590]\n\t"
      "addl $4, %%esp\n\t"
      "movb $1, 0xb(%%ebp)\n\t"
      ".Lobject_cause_damage_9:\n\t"
      "fmuls -0xc(%%ebp)\n\t"
      "fstps -0xc(%%ebp)\n\t"
      ".Lobject_cause_damage_10:\n\t"
      "movl 0x4(%%esi), %%eax\n\t"
      "xorl %%edi, %%edi\n\t"
      "testb $5, %%al\n\t"
      "movl %%edi, -0x8(%%ebp)\n\t"
      "movb $0, -0x2(%%ebp)\n\t"
      "jne .Lobject_cause_damage_13\n\t"
      "movl 0xc(%%ebp), %%ebx\n\t"
      "cmpl $-1, %%ebx\n\t"
      "je .Lobject_cause_damage_14\n\t"
      "leal (%%esp), %%esp\n\t"
      ".Lobject_cause_damage_11:\n\t"
      "cmpw $0x10, %%di\n\t"
      "jb .Lobject_cause_damage_12\n\t"
      "pushl $1\n\t"
      "pushl $0x37e\n\t"
      "pushl $0x29af50\n\t"
      "pushl $0x29b0f0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lobject_cause_damage_12:\n\t"
      "movswl %%di, %%eax\n\t"
      "pushl $-1\n\t"
      "pushl %%ebx\n\t"
      "movl %%ebx, -0x74(%%ebp,%%eax,4)\n\t"
      "incl %%edi\n\t"
      "call *%[get]\n\t"
      "movl 0xcc(%%eax), %%ebx\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%ebx\n\t"
      "jne .Lobject_cause_damage_11\n\t"
      "movl %%edi, -0x8(%%ebp)\n\t"
      "jmp .Lobject_cause_damage_14\n\t"
      ".Lobject_cause_damage_13:\n\t"
      "movl $1, -0x8(%%ebp)\n\t"
      "movl -0x8(%%ebp), %%edi\n\t"
      "movl %%ebx, -0x74(%%ebp)\n\t"
      ".Lobject_cause_damage_14:\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "pushl $-1\n\t"
      "pushl %%ecx\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl (%%ebx), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x6f626a65\n\t"
      "call *%[tag]\n\t"
      "movl 0x7c(%%eax), %%eax\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lobject_cause_damage_15\n\t"
      "pushl %%eax\n\t"
      "pushl $0x636f6c6c\n\t"
      "call *%[tag]\n\t"
      "movl (%%eax), %%eax\n\t"
      "shrl $4, %%eax\n\t"
      "notb %%al\n\t"
      "addl $8, %%esp\n\t"
      "andb $1, %%al\n\t"
      "movb %%al, -0x1(%%ebp)\n\t"
      ".Lobject_cause_damage_15:\n\t"
      "cmpl $-1, 0xa0(%%ebx)\n\t"
      "je .Lobject_cause_damage_17\n\t"
      "cmpw $0x10, %%di\n\t"
      "jb .Lobject_cause_damage_16\n\t"
      "pushl $1\n\t"
      "pushl $0x397\n\t"
      "pushl $0x29af50\n\t"
      "pushl $0x29b0f0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lobject_cause_damage_16:\n\t"
      "movl 0xa0(%%ebx), %%ecx\n\t"
      "movswl %%di, %%eax\n\t"
      "incl %%edi\n\t"
      "movl %%ecx, -0x74(%%ebp,%%eax,4)\n\t"
      "movl %%edi, -0x8(%%ebp)\n\t"
      ".Lobject_cause_damage_17:\n\t"
      "testb $1, 0x4(%%esi)\n\t"
      "jne .Lobject_cause_damage_24\n\t"
      "cmpw $1, 0x64(%%ebx)\n\t"
      "jne .Lobject_cause_damage_24\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "pushl $3\n\t"
      "pushl %%edx\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl (%%ebx), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x756e6974\n\t"
      "movl %%ebx, -0x34(%%ebp)\n\t"
      "call *%[tag]\n\t"
      "flds 0x2533c8\n\t"
      "movl -0x18(%%ebp), %%ecx\n\t"
      "fsubs 0x18(%%ecx)\n\t"
      "movl 0xc8(%%ebx), %%ebx\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpl $-1, %%ebx\n\t"
      "fmuls 0x184(%%eax)\n\t"
      "fstps 0x44(%%esi)\n\t"
      "je .Lobject_cause_damage_23\n\t"
      "movl %%edi, %%edi\n\t"
      ".Lobject_cause_damage_18:\n\t"
      "pushl $-1\n\t"
      "pushl %%ebx\n\t"
      "call *%[get]\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $0x10, -0x8(%%ebp)\n\t"
      "movl %%eax, %%edi\n\t"
      "jb .Lobject_cause_damage_19\n\t"
      "pushl $1\n\t"
      "pushl $0x3ab\n\t"
      "pushl $0x29af50\n\t"
      "pushl $0x29b0f0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lobject_cause_damage_19:\n\t"
      "cmpw $0, 0x64(%%edi)\n\t"
      "jne .Lobject_cause_damage_22\n\t"
      "pushl $3\n\t"
      "pushl %%ebx\n\t"
      "call *%[get]\n\t"
      "movl 0x1c8(%%eax), %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%ecx\n\t"
      "jne .Lobject_cause_damage_20\n\t"
      "movl -0x34(%%ebp), %%edx\n\t"
      "cmpl 0x2d4(%%edx), %%ebx\n\t"
      "jne .Lobject_cause_damage_22\n\t"
      "movl 0x4(%%esi), %%eax\n\t"
      "orl $0x20, %%eax\n\t"
      "jmp .Lobject_cause_damage_21\n\t"
      ".Lobject_cause_damage_20:\n\t"
      "movl 0x4(%%esi), %%eax\n\t"
      "andl $0xffffffdf, %%eax\n\t"
      ".Lobject_cause_damage_21:\n\t"
      "pushl $0\n\t"
      "pushl $-1\n\t"
      "pushl $-1\n\t"
      "pushl $-1\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl %%eax, 0x4(%%esi)\n\t"
      "call *%[c137d20]\n\t"
      "movl 0x4(%%esi), %%eax\n\t"
      "addl $0x18, %%esp\n\t"
      "andl $0xffffffdf, %%eax\n\t"
      "movl %%eax, 0x4(%%esi)\n\t"
      ".Lobject_cause_damage_22:\n\t"
      "movl 0xc4(%%edi), %%ebx\n\t"
      "cmpl $-1, %%ebx\n\t"
      "jne .Lobject_cause_damage_18\n\t"
      ".Lobject_cause_damage_23:\n\t"
      "movl -0x8(%%ebp), %%edi\n\t"
      "movl $0x3f800000, 0x44(%%esi)\n\t"
      ".Lobject_cause_damage_24:\n\t"
      "testw %%di, %%di\n\t"
      "jle .Lobject_cause_damage_29\n\t"
      "leal -0x74(%%ebp), %%ebx\n\t"
      "movzwl %%di, %%edi\n\t"
      "leal (%%esp), %%esp\n\t"
      ".Lobject_cause_damage_25:\n\t"
      "movl (%%ebx), %%eax\n\t"
      "pushl $3\n\t"
      "pushl %%eax\n\t"
      "call *%[tryget]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lobject_cause_damage_28\n\t"
      "movl 0x1c8(%%eax), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lobject_cause_damage_26\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "movl 0x40(%%esi), %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "leal 0x34(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "jmp .Lobject_cause_damage_27\n\t"
      ".Lobject_cause_damage_26:\n\t"
      "movb 0x5aa895, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lobject_cause_damage_28\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "movl 0x40(%%esi), %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "leal 0x34(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl $0\n\t"
      "call *%[cba3c0]\n\t"
      "addl $4, %%esp\n\t"
      ".Lobject_cause_damage_27:\n\t"
      "pushl %%eax\n\t"
      "call *%[ca3b80]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lobject_cause_damage_28:\n\t"
      "addl $4, %%ebx\n\t"
      "decl %%edi\n\t"
      "jne .Lobject_cause_damage_25\n\t"
      ".Lobject_cause_damage_29:\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lobject_cause_damage_59\n\t"
      "movl %%edi, %%edi\n\t"
      ".Lobject_cause_damage_30:\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movw %%ax, %%dx\n\t"
      "decl %%eax\n\t"
      "testw %%dx, %%dx\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "jle .Lobject_cause_damage_59\n\t"
      "movswl %%ax, %%eax\n\t"
      "movl -0x74(%%ebp,%%eax,4), %%eax\n\t"
      "pushl $-1\n\t"
      "pushl %%eax\n\t"
      "movl %%eax, -0x20(%%ebp)\n\t"
      "call *%[get]\n\t"
      "movl (%%eax), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x6f626a65\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "call *%[tag]\n\t"
      "movl 0x7c(%%eax), %%eax\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "movl $0, -0x28(%%ebp)\n\t"
      "movl $0, -0x24(%%ebp)\n\t"
      "movl $0, -0x34(%%ebp)\n\t"
      "movl $0, -0x10(%%ebp)\n\t"
      "movl $0xffffffff, -0x30(%%ebp)\n\t"
      "je .Lobject_cause_damage_57\n\t"
      "pushl %%eax\n\t"
      "pushl $0x636f6c6c\n\t"
      "call *%[tag]\n\t"
      "movl 0x4(%%esi), %%ebx\n\t"
      "shrl $2, %%ebx\n\t"
      "addl $8, %%esp\n\t"
      "movl %%eax, %%edi\n\t"
      "andb $1, %%bl\n\t"
      "cmpw $0, 0x10(%%ebp)\n\t"
      "movl %%edi, -0x2c(%%ebp)\n\t"
      "jl .Lobject_cause_damage_31\n\t"
      "movswl 0x10(%%ebp), %%ecx\n\t"
      "movl 0x28c(%%edi), %%edx\n\t"
      "cmpl %%edx, %%ecx\n\t"
      "leal 0x28c(%%edi), %%eax\n\t"
      "jge .Lobject_cause_damage_31\n\t"
      "pushl $0x40\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movw 0x32(%%eax), %%dx\n\t"
      "addl $0xc, %%esp\n\t"
      "movw %%dx, -0x30(%%ebp)\n\t"
      ".Lobject_cause_damage_31:\n\t"
      "movb 0xb(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lobject_cause_damage_32\n\t"
      "movl $0x20, -0x10(%%ebp)\n\t"
      ".Lobject_cause_damage_32:\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x10(%%esi), %%ax\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .Lobject_cause_damage_33\n\t"
      "pushl %%eax\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x68(%%eax), %%cx\n\t"
      "pushl %%ecx\n\t"
      "call *%[ca7a30]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lobject_cause_damage_33\n\t"
      "orl $0x10, -0x10(%%ebp)\n\t"
      ".Lobject_cause_damage_33:\n\t"
      "cmpw $0, -0x8(%%ebp)\n\t"
      "jne .Lobject_cause_damage_34\n\t"
      "movw 0x18(%%ebp), %%cx\n\t"
      "testw %%cx, %%cx\n\t"
      "jl .Lobject_cause_damage_34\n\t"
      "movl 0x234(%%edi), %%edx\n\t"
      "leal 0x234(%%edi), %%eax\n\t"
      "movswl %%cx, %%ecx\n\t"
      "cmpl %%edx, %%ecx\n\t"
      "jge .Lobject_cause_damage_34\n\t"
      "pushl $0x48\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "addl $0xc, %%esp\n\t"
      "movl %%eax, -0x1c(%%ebp)\n\t"
      "jmp .Lobject_cause_damage_36\n\t"
      ".Lobject_cause_damage_34:\n\t"
      "movw 0x4(%%edi), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "jl .Lobject_cause_damage_35\n\t"
      "movl 0x234(%%edi), %%edx\n\t"
      "movswl %%ax, %%eax\n\t"
      "cmpl %%edx, %%eax\n\t"
      "leal 0x234(%%edi), %%ecx\n\t"
      "jge .Lobject_cause_damage_35\n\t"
      "pushl $0x48\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[elem]\n\t"
      "addl $0xc, %%esp\n\t"
      "movl %%eax, -0x1c(%%ebp)\n\t"
      "jmp .Lobject_cause_damage_36\n\t"
      ".Lobject_cause_damage_35:\n\t"
      "movl $0x46f028, -0x1c(%%ebp)\n\t"
      ".Lobject_cause_damage_36:\n\t"
      "movl -0x1c(%%ebp), %%edx\n\t"
      "movw 0x24(%%edx), %%ax\n\t"
      "movw %%ax, 0x4c(%%esi)\n\t"
      "movb 0x5aa897, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lobject_cause_damage_37\n\t"
      "cmpl $-1, 0x8(%%esi)\n\t"
      "je .Lobject_cause_damage_37\n\t"
      "movb $1, %%bl\n\t"
      ".Lobject_cause_damage_37:\n\t"
      "movl -0x18(%%ebp), %%ecx\n\t"
      "cmpw $2, (%%ecx)\n\t"
      "jne .Lobject_cause_damage_38\n\t"
      "movl -0x20(%%ebp), %%eax\n\t"
      "leal 0x28(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c1b1d00]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lobject_cause_damage_38\n\t"
      "movl -0x14(%%ebp), %%ecx\n\t"
      "testb $8, 0xb7(%%ecx)\n\t"
      "je .Lobject_cause_damage_39\n\t"
      ".Lobject_cause_damage_38:\n\t"
      "testb %%bl, %%bl\n\t"
      "je .Lobject_cause_damage_40\n\t"
      ".Lobject_cause_damage_39:\n\t"
      "movl -0x14(%%ebp), %%edx\n\t"
      "testb $4, 0xb6(%%edx)\n\t"
      "jne .Lobject_cause_damage_40\n\t"
      "movl -0x20(%%ebp), %%ecx\n\t"
      "movl %%edx, %%eax\n\t"
      "pushl %%ecx\n\t"
      "movl $0, 0x90(%%eax)\n\t"
      "call *%[c137540]\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "addl $4, %%esp\n\t"
      "orl $0x41, %%eax\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      ".Lobject_cause_damage_40:\n\t"
      "testb $0x20, 0x4(%%esi)\n\t"
      "jne .Lobject_cause_damage_42\n\t"
      "movl -0x18(%%ebp), %%edx\n\t"
      "movl 0x4(%%edx), %%eax\n\t"
      "testb $2, %%ah\n\t"
      "jne .Lobject_cause_damage_42\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "flds 0x8c(%%eax)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lobject_cause_damage_42\n\t"
      "cmpw $0, -0x8(%%ebp)\n\t"
      "je .Lobject_cause_damage_41\n\t"
      "testb $1, (%%edi)\n\t"
      "je .Lobject_cause_damage_42\n\t"
      ".Lobject_cause_damage_41:\n\t"
      "movl -0x20(%%ebp), %%edi\n\t"
      "leal -0xc(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl -0x18(%%ebp), %%ecx\n\t"
      "leal -0x28(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl -0x1c(%%ebp), %%edx\n\t"
      "leal -0x10(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl -0x2c(%%ebp), %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c136bc0]\n\t"
      "movl -0x2c(%%ebp), %%edi\n\t"
      "addl $0x1c, %%esp\n\t"
      ".Lobject_cause_damage_42:\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "testw %%dx, %%dx\n\t"
      "je .Lobject_cause_damage_43\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lobject_cause_damage_49\n\t"
      "testb $2, (%%edi)\n\t"
      "je .Lobject_cause_damage_49\n\t"
      ".Lobject_cause_damage_43:\n\t"
      "movl -0x18(%%ebp), %%ecx\n\t"
      "movl 0x4(%%ecx), %%eax\n\t"
      "testb $0x40, %%al\n\t"
      "jne .Lobject_cause_damage_49\n\t"
      "testb $0x20, (%%edi)\n\t"
      "je .Lobject_cause_damage_44\n\t"
      "testb $0x20, %%al\n\t"
      "jne .Lobject_cause_damage_44\n\t"
      "movl $0, -0xc(%%ebp)\n\t"
      ".Lobject_cause_damage_44:\n\t"
      "testw %%dx, %%dx\n\t"
      "jne .Lobject_cause_damage_45\n\t"
      "movswl 0x10(%%ebp), %%ecx\n\t"
      "jmp .Lobject_cause_damage_46\n\t"
      ".Lobject_cause_damage_45:\n\t"
      "orl $0xffffffff, %%ecx\n\t"
      ".Lobject_cause_damage_46:\n\t"
      "testw %%dx, %%dx\n\t"
      "jne .Lobject_cause_damage_47\n\t"
      "movswl 0x14(%%ebp), %%eax\n\t"
      "jmp .Lobject_cause_damage_48\n\t"
      ".Lobject_cause_damage_47:\n\t"
      "orl $0xffffffff, %%eax\n\t"
      ".Lobject_cause_damage_48:\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl 0x1c(%%ebp), %%ebx\n\t"
      "leal -0x34(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x24(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x10(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl -0x18(%%ebp), %%edx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edx\n\t"
      "movl -0x1c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "xorl %%edx, %%edx\n\t"
      "cmpw %%dx, -0x8(%%ebp)\n\t"
      "pushl %%edi\n\t"
      "setne %%dl\n\t"
      "decl %%edx\n\t"
      "andl %%ebx, %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "movl -0x20(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1377d0]\n\t"
      "addl $0x30, %%esp\n\t"
      "movl $0, -0x8(%%ebp)\n\t"
      ".Lobject_cause_damage_49:\n\t"
      "movb -0x2(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lobject_cause_damage_57\n\t"
      "flds -0x28(%%ebp)\n\t"
      "fcomps 0x253f44\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .Lobject_cause_damage_50\n\t"
      "flds -0x24(%%ebp)\n\t"
      "fcomps 0x253f44\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lobject_cause_damage_57\n\t"
      ".Lobject_cause_damage_50:\n\t"
      "flds -0x28(%%ebp)\n\t"
      "fcomps -0x24(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lobject_cause_damage_51\n\t"
      "movw 0xd2(%%edi), %%cx\n\t"
      "movl -0x14(%%ebp), %%edx\n\t"
      "movw %%cx, 0x4c(%%esi)\n\t"
      "movl 0x94(%%edx), %%eax\n\t"
      "movl %%eax, 0x48(%%esi)\n\t"
      "jmp .Lobject_cause_damage_55\n\t"
      ".Lobject_cause_damage_51:\n\t"
      "movl -0x14(%%ebp), %%ecx\n\t"
      "flds 0x90(%%ecx)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lobject_cause_damage_52\n\t"
      "flds 0x2533c0\n\t"
      "jmp .Lobject_cause_damage_54\n\t"
      ".Lobject_cause_damage_52:\n\t"
      "flds 0x90(%%ecx)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lobject_cause_damage_53\n\t"
      "flds 0x2533c8\n\t"
      "jmp .Lobject_cause_damage_54\n\t"
      ".Lobject_cause_damage_53:\n\t"
      "flds 0x90(%%ecx)\n\t"
      ".Lobject_cause_damage_54:\n\t"
      "fstps 0x48(%%esi)\n\t"
      ".Lobject_cause_damage_55:\n\t"
      "movb 0x5a90c0, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lobject_cause_damage_56\n\t"
      "movl -0x20(%%ebp), %%ecx\n\t"
      "cmpl 0x46f070, %%ecx\n\t"
      "jne .Lobject_cause_damage_56\n\t"
      "movl -0x1c(%%ebp), %%eax\n\t"
      "flds -0x24(%%ebp)\n\t"
      "subl $0x18, %%esp\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x24(%%eax), %%dx\n\t"
      "flds -0x28(%%ebp)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds 0x40(%%esi)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl %%eax\n\t"
      "pushl %%edx\n\t"
      "call *%[cb5490]\n\t"
      "addl $4, %%esp\n\t"
      "pushl %%eax\n\t"
      "movl (%%esi), %%eax\n\t"
      "pushl $0x5c\n\t"
      "pushl %%eax\n\t"
      "call *%[c1ba1f0]\n\t"
      "addl $4, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d9710]\n\t"
      "addl $8, %%esp\n\t"
      "incl %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x29b0c4\n\t"
      "pushl $0\n\t"
      "call *%[cff4d0]\n\t"
      "addl $0x2c, %%esp\n\t"
      ".Lobject_cause_damage_56:\n\t"
      "movb $1, -0x2(%%ebp)\n\t"
      ".Lobject_cause_damage_57:\n\t"
      "movl -0x30(%%ebp), %%ecx\n\t"
      "movl -0x34(%%ebp), %%edx\n\t"
      "movl -0x24(%%ebp), %%eax\n\t"
      "movl -0x20(%%ebp), %%ebx\n\t"
      "pushl %%ecx\n\t"
      "movl -0x28(%%ebp), %%ecx\n\t"
      "pushl %%edx\n\t"
      "movl -0x10(%%ebp), %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c136f40]\n\t"
      "movb -0x10(%%ebp), %%al\n\t"
      "addl $0x14, %%esp\n\t"
      "testb $4, %%al\n\t"
      "je .Lobject_cause_damage_58\n\t"
      "pushl %%ebx\n\t"
      "call *%[odel]\n\t"
      "addl $4, %%esp\n\t"
      ".Lobject_cause_damage_58:\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .Lobject_cause_damage_30\n\t"
      ".Lobject_cause_damage_59:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [tag] "m"(b137d20_tag), [assert] "m"(b137d20_assert), [exitfn] "m"(b137d20_exitfn), [gseed] "m"(b137d20_gseed), [rrange] "m"(b137d20_rrange), [tryget] "m"(b137d20_tryget), [get] "m"(b137d20_get), [c3f900] "m"(b137d20_c3f900), [gerun] "m"(b137d20_gerun), [c136890] "m"(b137d20_c136890), [cad530] "m"(b137d20_cad530), [ca7a30] "m"(b137d20_ca7a30), [cb5590] "m"(b137d20_cb5590), [c137d20] "m"(b137d20_c137d20), [cba3c0] "m"(b137d20_cba3c0), [ca3b80] "m"(b137d20_ca3b80), [elem] "m"(b137d20_elem), [c1b1d00] "m"(b137d20_c1b1d00), [c137540] "m"(b137d20_c137540), [c136bc0] "m"(b137d20_c136bc0), [c1377d0] "m"(b137d20_c1377d0), [cb5490] "m"(b137d20_cb5490), [c1ba1f0] "m"(b137d20_c1ba1f0), [c1d9710] "m"(b137d20_c1d9710), [cff4d0] "m"(b137d20_cff4d0), [c136f40] "m"(b137d20_c136f40), [odel] "m"(b137d20_odel)
      : "memory");
}
#else
#error "object_cause_damage: clang naked draft required"
#endif


/* FUN_00137170 (0x137170) — Build damage-effect marker arrays and fire an
 * effect for a damage impact.
 *
 * Sets up 5 forward-direction vectors ("normal", "incident",
 * "negative incident", "reflection", "gravity") and 5 copies of the impact
 * position, then calls either effect_new_attached_from_markers (attached
 * effect) when both the object handle and marker index are valid, or
 * effect_new_unattached_from_markers (unattached effect) otherwise.
 *
 * The incident direction (@EAX) is normalized in-place; if it has zero
 * length, it is replaced by the global forward vector (*(0x31fc3c)).
 * If the surface normal (@ECX/EDI) is NULL, a direction is computed from
 * position minus the object's world position, and if that also has zero
 * length, the object's forward vector (obj+0x24) is used instead.
 *
 * Register args:
 *   @EAX = incident_direction (float[3], normalized in function)
 *   @ECX = surface_normal (float[3], or NULL)
 *   @ESI = object_handle (int)
 * Stack args:
 *   [EBP+0x8]  = effect_tag_index (int, collision model tag index)
 *   [EBP+0xC]  = marker_index (short, -1 for unattached)
 *   [EBP+0x10] = position (float[3], world position of impact)
 *
 * Confirmed: MOV EDI,ECX at 0x13717e saves @ECX (surface_normal) to EDI.
 * Confirmed: TEST EDI,EDI at 0x1371fb branches on NULL surface_normal.
 * Confirmed: MOV EBX,[EBP+0x10] at 0x13717a loads position param.
 * Confirmed: normalize3d at CALL 0x13010 normalizes incident direction.
 * Confirmed: FCOMP [0x2533c0] compares magnitude with 0.0f.
 * Confirmed: FMUL [0x255e94] multiplies by -1.0f for negative incident.
 * Confirmed: object_get_world_position at CALL 0x1412f0 =
 * object_get_world_position. Confirmed: FUN_0010c8e0 at CALL 0x10c8e0 = reflect
 * vector. Confirmed: CMP ESI,-1 at 0x1372f9 + CMP AX,0xffff at 0x137303 gate
 *            between effect_new_attached_from_markers and
 * effect_new_unattached_from_markers. Confirmed: 12 pushes + ADD ESP,0x30 for
 * both effect calls. Confirmed: *(0x31fc50) = global gravity/down vector
 * (0,0,-1). Confirmed: *(0x31fc3c) = global forward vector (1,0,0). Confirmed:
 * *(0x31fc38) = translational velocity ptr for
 * effect_new_unattached_from_markers.
 */
/* Unported: only caller (FUN_001377d0) is unported and passes 3 register
 * args (@<eax>, @<ecx>, @<esi>) that our cdecl C function cannot receive.
 * Original XBE code runs and correctly calls our ported callees. */
#if 1
/* FUN_00137170 (0x137170) — XBE naked draft (batch 54). */
#if defined(__clang__)
static float (*const b137170_norm)(float *) = normalize3d;
static vector3_t * (*const b137170_c1412f0)(int object_handle, vector3_t *out_position) = object_get_world_position;
static void *(*const b137170_get)(int, int) = object_get_and_verify_type;
static void (*const b137170_c10c8e0)(float *v, float *n, float *out) = FUN_0010c8e0;
static int (*const b137170_c9ee40)(int effect_tag_index, int object_index, int attached_object, uint16_t marker_index, short marker_count, void *effect_definition, float *marker_points, float *marker_forwards, float scale_a, float scale_b, float unknown1, float unknown2) = effect_new_attached_from_markers;
static int (*const b137170_c9f0e0)(int effect_tag_index, int object_index, float *translational_velocity, short marker_count, void *effect_definition, float *marker_points, float *marker_forwards, float scale_a, float scale_b, float unknown1, float unknown2, float unknown3) = effect_new_unattached_from_markers;

__attribute__((naked, noinline))
void FUN_00137170(float *incident_direction __attribute__((unused)), float *surface_normal __attribute__((unused)), int object_handle __attribute__((unused)), int effect_tag_index __attribute__((unused)), short marker_index __attribute__((unused)), float *position __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xb0, %%esp\n\t"
      "pushl %%ebx\n\t"
      "movl 0x10(%%ebp), %%ebx\n\t"
      "pushl %%edi\n\t"
      "movl %%ecx, %%edi\n\t"
      "movl 0x31fc50, %%ecx\n\t"
      "movl $0x26b188, -0x2c(%%ebp)\n\t"
      "movl $0x28ab18, -0x28(%%ebp)\n\t"
      "movl $0x28ab04, -0x24(%%ebp)\n\t"
      "movl $0x28aaf8, -0x20(%%ebp)\n\t"
      "movl $0x26ad40, -0x1c(%%ebp)\n\t"
      "movl (%%ecx), %%edx\n\t"
      "movl %%edx, -0x44(%%ebp)\n\t"
      "movl 0x4(%%ecx), %%edx\n\t"
      "movl %%edx, -0x40(%%ebp)\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "movl (%%eax), %%edx\n\t"
      "movl %%ecx, -0x3c(%%ebp)\n\t"
      "movl 0x4(%%eax), %%ecx\n\t"
      "movl %%edx, -0xc(%%ebp)\n\t"
      "movl 0x8(%%eax), %%edx\n\t"
      "leal -0xc(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      "call *%[norm]\n\t"
      "fcomps 0x2533c0\n\t"
      "addl $4, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .LFUN_00137170_1\n\t"
      "movl 0x31fc3c, %%ecx\n\t"
      "movl (%%ecx), %%edx\n\t"
      "movl %%edx, -0xc(%%ebp)\n\t"
      "movl 0x4(%%ecx), %%eax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "movl %%ecx, -0x4(%%ebp)\n\t"
      ".LFUN_00137170_1:\n\t"
      "testl %%edi, %%edi\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fmuls 0x255e94\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "fstps -0x68(%%ebp)\n\t"
      "movl %%edx, -0x5c(%%ebp)\n\t"
      "flds -0x8(%%ebp)\n\t"
      "movl %%eax, -0x58(%%ebp)\n\t"
      "fmuls 0x255e94\n\t"
      "movl %%ecx, -0x54(%%ebp)\n\t"
      "fstps -0x64(%%ebp)\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fmuls 0x255e94\n\t"
      "fstps -0x60(%%ebp)\n\t"
      "jne .LFUN_00137170_3\n\t"
      "leal -0x38(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%esi\n\t"
      "call *%[c1412f0]\n\t"
      "flds (%%ebx)\n\t"
      "fsubs -0x38(%%ebp)\n\t"
      "leal -0x18(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "flds 0x4(%%ebx)\n\t"
      "fsubs -0x34(%%ebp)\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "flds 0x8(%%ebx)\n\t"
      "fsubs -0x30(%%ebp)\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "call *%[norm]\n\t"
      "fcomps 0x2533c0\n\t"
      "addl $0xc, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .LFUN_00137170_2\n\t"
      "pushl $-1\n\t"
      "pushl %%esi\n\t"
      "call *%[get]\n\t"
      "addl $8, %%esp\n\t"
      "addl $0x24, %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "movl %%ecx, -0x18(%%ebp)\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl %%edx, -0x14(%%ebp)\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      ".LFUN_00137170_2:\n\t"
      "movl -0x18(%%ebp), %%ecx\n\t"
      "movl -0x14(%%ebp), %%edx\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "movl %%ecx, -0x74(%%ebp)\n\t"
      "leal -0x50(%%ebp), %%ecx\n\t"
      "movl %%edx, -0x70(%%ebp)\n\t"
      "pushl %%ecx\n\t"
      "leal -0x18(%%ebp), %%edx\n\t"
      "movl %%eax, -0x6c(%%ebp)\n\t"
      "pushl %%edx\n\t"
      "jmp .LFUN_00137170_4\n\t"
      ".LFUN_00137170_3:\n\t"
      "movl %%edi, %%ecx\n\t"
      "movl (%%ecx), %%edx\n\t"
      "movl 0x4(%%ecx), %%eax\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "movl %%edx, -0x74(%%ebp)\n\t"
      "leal -0x50(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl %%eax, -0x70(%%ebp)\n\t"
      "movl %%ecx, -0x6c(%%ebp)\n\t"
      "pushl %%edi\n\t"
      ".LFUN_00137170_4:\n\t"
      "leal -0xc(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c10c8e0]\n\t"
      "addl $0xc, %%esp\n\t"
      "leal -0xb0(%%ebp), %%eax\n\t"
      "movl $5, %%ecx\n\t"
      "jmp .LFUN_00137170_6\n\t"
      ".LFUN_00137170_5:\n\t"
      "movl 0x10(%%ebp), %%ebx\n\t"
      ".LFUN_00137170_6:\n\t"
      "movl (%%ebx), %%edi\n\t"
      "movl %%eax, %%edx\n\t"
      "movl %%edi, (%%edx)\n\t"
      "movl 0x4(%%ebx), %%edi\n\t"
      "movl %%edi, 0x4(%%edx)\n\t"
      "movl 0x8(%%ebx), %%edi\n\t"
      "addl $0xc, %%eax\n\t"
      "decl %%ecx\n\t"
      "movl %%edi, 0x8(%%edx)\n\t"
      "jne .LFUN_00137170_5\n\t"
      "cmpl $-1, %%esi\n\t"
      "popl %%edi\n\t"
      "popl %%ebx\n\t"
      "je .LFUN_00137170_7\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .LFUN_00137170_7\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl $0x3f800000\n\t"
      "leal -0x74(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0xb0(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "leal -0x2c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $5\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%esi\n\t"
      "pushl %%edx\n\t"
      "call *%[c9ee40]\n\t"
      "addl $0x30, %%esp\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00137170_7:\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl $0x3f800000\n\t"
      "leal -0x74(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl 0x31fc38, %%eax\n\t"
      "leal -0xb0(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "leal -0x2c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $5\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%ecx\n\t"
      "call *%[c9f0e0]\n\t"
      "addl $0x30, %%esp\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "nop\n\t"
      :
      : [norm] "m"(b137170_norm), [c1412f0] "m"(b137170_c1412f0), [get] "m"(b137170_get), [c10c8e0] "m"(b137170_c10c8e0), [c9ee40] "m"(b137170_c9ee40), [c9f0e0] "m"(b137170_c9f0e0)
      : "memory");
}
#else
#error "FUN_00137170: clang naked draft required"
#endif

#endif

/* object_damage_update (0x1384e0) — XBE naked draft (batch 51). */
#if defined(__clang__)
static void *(*const b1384e0_get)(int, int) = object_get_and_verify_type;
static void *(*const b1384e0_tag)(int, int) = tag_get;
static void * (*const b1384e0_c18e450)(void) = game_globals_get;
static void *(*const b1384e0_elem)(void *, int, int) = tag_block_get_element;
static void (*const b1384e0_c136750)(void *damage_params, int tag_index) = damage_data_new;
static void (*const b1384e0_c137d20)(void *damage_params, int object_handle, short node_index, short region_index, short permutation_index, unsigned int flags) = object_cause_damage;
static bool (*const b1384e0_gerun)(void) = game_engine_running;
static int (*const b1384e0_cba500)(int) = player_index_from_unit_index;
static void (*const b1384e0_cd7cd0)(int player_handle, float param_2) = FUN_000d7cd0;
static float (*const b1384e0_cb55b0)(short value_type, int team) = FUN_000b55b0;
static void (*const b1384e0_c1369e0)(int object_handle, int effect_tag_index) = FUN_001369e0;
static void (*const b1384e0_c136a00)(int object_handle, char param_1) = FUN_00136a00;

__attribute__((naked, noinline))
void object_damage_update(int object_handle __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x58, %%esp\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "pushl $-1\n\t"
      "pushl %%edi\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl (%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x6f626a65\n\t"
      "call *%[tag]\n\t"
      "movl 0x7c(%%eax), %%eax\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lobject_damage_update_27\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "pushl $0x636f6c6c\n\t"
      "call *%[tag]\n\t"
      "movl %%eax, %%ebx\n\t"
      "addl $8, %%esp\n\t"
      "testl %%ebx, %%ebx\n\t"
      "je .Lobject_damage_update_26\n\t"
      "movw 0xb6(%%esi), %%ax\n\t"
      "testb $0x20, %%ah\n\t"
      "jne .Lobject_damage_update_1\n\t"
      "testb $0x60, %%al\n\t"
      "je .Lobject_damage_update_5\n\t"
      ".Lobject_damage_update_1:\n\t"
      "testb $4, %%al\n\t"
      "jne .Lobject_damage_update_4\n\t"
      "pushl $0x98\n\t"
      "pushl $0\n\t"
      "call *%[c18e450]\n\t"
      "addl $0x188, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl 0x1c(%%eax), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lobject_damage_update_4\n\t"
      "pushl %%eax\n\t"
      "leal -0x58(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c136750]\n\t"
      "movl -0x54(%%ebp), %%edx\n\t"
      "movw 0xb6(%%esi), %%ax\n\t"
      "orl $4, %%edx\n\t"
      "addl $8, %%esp\n\t"
      "testb $0x40, %%al\n\t"
      "movl $0x3f800000, -0x18(%%ebp)\n\t"
      "movl %%edx, -0x54(%%ebp)\n\t"
      "je .Lobject_damage_update_2\n\t"
      "movl %%edx, %%ecx\n\t"
      "orl $0x10, %%ecx\n\t"
      "movl %%ecx, -0x54(%%ebp)\n\t"
      ".Lobject_damage_update_2:\n\t"
      "testb $0x20, %%ah\n\t"
      "je .Lobject_damage_update_3\n\t"
      "orl $0x80, -0x54(%%ebp)\n\t"
      ".Lobject_damage_update_3:\n\t"
      "pushl $0\n\t"
      "pushl $-1\n\t"
      "pushl $-1\n\t"
      "pushl $-1\n\t"
      "leal -0x58(%%ebp), %%edx\n\t"
      "pushl %%edi\n\t"
      "pushl %%edx\n\t"
      "call *%[c137d20]\n\t"
      "addl $0x18, %%esp\n\t"
      ".Lobject_damage_update_4:\n\t"
      "andw $0xdf9f, 0xb6(%%esi)\n\t"
      ".Lobject_damage_update_5:\n\t"
      "flds 0x8c(%%esi)\n\t"
      "andb $0xef, 0xb7(%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "movw 0xb6(%%esi), %%cx\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lobject_damage_update_12\n\t"
      "testb $4, %%cl\n\t"
      "jne .Lobject_damage_update_12\n\t"
      "testb $0x10, %%cl\n\t"
      "flds 0x94(%%esi)\n\t"
      "je .Lobject_damage_update_7\n\t"
      "fadds 0x2546a4\n\t"
      "fsts 0x94(%%esi)\n\t"
      "fcomps 0x254644\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .Lobject_damage_update_6\n\t"
      "andl $0xffef, %%ecx\n\t"
      "movl $0x40400000, 0x94(%%esi)\n\t"
      "movw %%cx, 0xb6(%%esi)\n\t"
      "jmp .Lobject_damage_update_12\n\t"
      ".Lobject_damage_update_6:\n\t"
      "orl $0x1000, %%ecx\n\t"
      "movw %%cx, 0xb6(%%esi)\n\t"
      "jmp .Lobject_damage_update_12\n\t"
      ".Lobject_damage_update_7:\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lobject_damage_update_9\n\t"
      "call *%[gerun]\n\t"
      "testb %%al, %%al\n\t"
      "je .Lobject_damage_update_9\n\t"
      "pushl %%edi\n\t"
      "call *%[cba500]\n\t"
      "flds 0x94(%%esi)\n\t"
      "fsubs 0x2533c8\n\t"
      "movl %%eax, %%ecx\n\t"
      "addl $4, %%esp\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "flds 0x29b18c\n\t"
      "fcomps -0x4(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lobject_damage_update_8\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "movl $0x3f800000, 0x94(%%esi)\n\t"
      "call *%[cd7cd0]\n\t"
      "addl $8, %%esp\n\t"
      "jmp .Lobject_damage_update_12\n\t"
      ".Lobject_damage_update_8:\n\t"
      "flds 0x94(%%esi)\n\t"
      "pushl $0x3a422e45\n\t"
      "fsubs 0x29b18c\n\t"
      "pushl %%ecx\n\t"
      "fstps 0x94(%%esi)\n\t"
      "call *%[cd7cd0]\n\t"
      "addl $8, %%esp\n\t"
      "jmp .Lobject_damage_update_12\n\t"
      ".Lobject_damage_update_9:\n\t"
      "flds 0x94(%%esi)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lobject_damage_update_12\n\t"
      "movw 0xb4(%%esi), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "jne .Lobject_damage_update_11\n\t"
      "movl 0x1c0(%%ebx), %%ecx\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x68(%%esi), %%dx\n\t"
      "movl %%ecx, -0x4(%%ebp)\n\t"
      "pushl %%edx\n\t"
      "pushl $3\n\t"
      "call *%[cb55b0]\n\t"
      "fmuls -0x4(%%ebp)\n\t"
      "movb 0xb6(%%esi), %%al\n\t"
      "addl $8, %%esp\n\t"
      "testb $8, %%al\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "je .Lobject_damage_update_10\n\t"
      "movl 0x1b4(%%ebx), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl %%edi, %%eax\n\t"
      "call *%[c1369e0]\n\t"
      "andb $0xf7, 0xb6(%%esi)\n\t"
      "pushl $1\n\t"
      "movl %%edi, %%eax\n\t"
      "call *%[c136a00]\n\t"
      "addl $8, %%esp\n\t"
      ".Lobject_damage_update_10:\n\t"
      "flds -0x4(%%ebp)\n\t"
      "orb $0x10, 0xb7(%%esi)\n\t"
      "fadds 0x94(%%esi)\n\t"
      "movw 0xb6(%%esi), %%cx\n\t"
      "fsts 0x94(%%esi)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lobject_damage_update_12\n\t"
      "andl $0xefff, %%ecx\n\t"
      "movl $0x3f800000, 0x94(%%esi)\n\t"
      "movw %%cx, 0xb6(%%esi)\n\t"
      "jmp .Lobject_damage_update_12\n\t"
      ".Lobject_damage_update_11:\n\t"
      "decl %%eax\n\t"
      "movw %%ax, 0xb4(%%esi)\n\t"
      ".Lobject_damage_update_12:\n\t"
      "movl 0xb0(%%esi), %%eax\n\t"
      "orl $0xffffffff, %%ecx\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "je .Lobject_damage_update_19\n\t"
      "incl %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%eax, 0xb0(%%esi)\n\t"
      "jl .Lobject_damage_update_13\n\t"
      "flds 0x9c(%%esi)\n\t"
      "fsubs 0x25634c\n\t"
      "fstps 0x9c(%%esi)\n\t"
      ".Lobject_damage_update_13:\n\t"
      "cmpl $0x3c, %%eax\n\t"
      "jl .Lobject_damage_update_14\n\t"
      "flds 0xa8(%%esi)\n\t"
      "fsubs 0x25634c\n\t"
      "fstps 0xa8(%%esi)\n\t"
      ".Lobject_damage_update_14:\n\t"
      "flds 0x2533c0\n\t"
      "fcomps 0x9c(%%esi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lobject_damage_update_15\n\t"
      "flds 0x2533c0\n\t"
      "jmp .Lobject_damage_update_16\n\t"
      ".Lobject_damage_update_15:\n\t"
      "flds 0x9c(%%esi)\n\t"
      ".Lobject_damage_update_16:\n\t"
      "fsts 0x9c(%%esi)\n\t"
      "flds 0x2533c0\n\t"
      "fcomps 0xa8(%%esi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lobject_damage_update_17\n\t"
      "flds 0x2533c0\n\t"
      "jmp .Lobject_damage_update_18\n\t"
      ".Lobject_damage_update_17:\n\t"
      "flds 0xa8(%%esi)\n\t"
      ".Lobject_damage_update_18:\n\t"
      "fsts -0x4(%%ebp)\n\t"
      "fstps 0xa8(%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .Lobject_damage_update_19\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .Lobject_damage_update_19\n\t"
      "movl %%ecx, 0xb0(%%esi)\n\t"
      ".Lobject_damage_update_19:\n\t"
      "movl 0xac(%%esi), %%eax\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "je .Lobject_damage_update_26\n\t"
      "incl %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%eax, 0xac(%%esi)\n\t"
      "jl .Lobject_damage_update_20\n\t"
      "flds 0x98(%%esi)\n\t"
      "fsubs 0x25634c\n\t"
      "fstps 0x98(%%esi)\n\t"
      ".Lobject_damage_update_20:\n\t"
      "cmpl $0x3c, %%eax\n\t"
      "jl .Lobject_damage_update_21\n\t"
      "flds 0xa4(%%esi)\n\t"
      "fsubs 0x25634c\n\t"
      "fstps 0xa4(%%esi)\n\t"
      ".Lobject_damage_update_21:\n\t"
      "flds 0x2533c0\n\t"
      "fcomps 0x98(%%esi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lobject_damage_update_22\n\t"
      "flds 0x2533c0\n\t"
      "jmp .Lobject_damage_update_23\n\t"
      ".Lobject_damage_update_22:\n\t"
      "flds 0x98(%%esi)\n\t"
      ".Lobject_damage_update_23:\n\t"
      "fsts 0x98(%%esi)\n\t"
      "flds 0x2533c0\n\t"
      "fcomps 0xa4(%%esi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lobject_damage_update_24\n\t"
      "flds 0x2533c0\n\t"
      "jmp .Lobject_damage_update_25\n\t"
      ".Lobject_damage_update_24:\n\t"
      "flds 0xa4(%%esi)\n\t"
      ".Lobject_damage_update_25:\n\t"
      "fsts -0x4(%%ebp)\n\t"
      "fstps 0xa4(%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .Lobject_damage_update_26\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .Lobject_damage_update_26\n\t"
      "movl %%ecx, 0xac(%%esi)\n\t"
      ".Lobject_damage_update_26:\n\t"
      "popl %%ebx\n\t"
      ".Lobject_damage_update_27:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
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
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      :
      : [get] "m"(b1384e0_get), [tag] "m"(b1384e0_tag), [c18e450] "m"(b1384e0_c18e450), [elem] "m"(b1384e0_elem), [c136750] "m"(b1384e0_c136750), [c137d20] "m"(b1384e0_c137d20), [gerun] "m"(b1384e0_gerun), [cba500] "m"(b1384e0_cba500), [cd7cd0] "m"(b1384e0_cd7cd0), [cb55b0] "m"(b1384e0_cb55b0), [c1369e0] "m"(b1384e0_c1369e0), [c136a00] "m"(b1384e0_c136a00)
      : "memory");
}
#else
#error "object_damage_update: clang naked draft required"
#endif


/* FUN_00138e30 (0x138e30) — readable C lift. */
void FUN_00138e30(void *damage_params, int target_index)
{
  char *params = (char *)damage_params;
  char *jpt;
  int handles[0x40];
  int16_t count;
  int i;
  (void)target_index;

  jpt = (char *)tag_get(0x6a707421, *(int *)params);
  count = object_find_in_radius(
      0, 0, params + 0x14, (float *)(params + 0x1c), *(float *)(jpt + 4),
      handles, 0x40);
  for (i = 0; i < (int)count; i++)
    FUN_00138900(params, handles[i], 0);
  FUN_00146be0(params);
}



/* FUN_00138eb0 — dispatch object deletion callbacks.
 * Iterates through a table of 3 function pointers at 0x3235f0 and calls
 * each with the object handle. These callbacks clean up references to the
 * object in various subsystems (actors, players, AI, etc.) before deletion.
 *
 * Table at 0x3235f0:
 *   [0] = 0x13d8b0 — clears object references in other objects
 *   [1] = 0x40700  — actor cleanup and player notifications
 *   [2] = 0xbb220  — player object reference cleanup
 */
void FUN_00138eb0(int object_handle)
{
  void (**table)(int);
  int i;

  table = (void (**)(int))0x3235f0;
  i = 3;
  do {
    (*table)(object_handle);
    table++;
    i--;
  } while (i != 0);
}

/* FUN_00138ee0 (0x138ee0) — Texture cache hardware format lookup with RDTSC
 * profiling. Wraps xbox_texture_cache_get_hardware_format(hardware_format, 1,
 * 1) between RDTSC start/stop calls for performance measurement.
 *
 * Confirmed: CALL 0x916e0 (RDTSC start) takes no args.
 * Confirmed: PUSH 1 / PUSH 1 / PUSH [EBP+8] then CALL 0x1bf570 (cdecl, 3 args).
 * Confirmed: ADD ESP,0xc after call (cdecl cleanup for 3 args).
 * Confirmed: CALL 0x91710 (RDTSC stop) takes no args.
 * Confirmed: return value in ESI is the result of
 * xbox_texture_cache_get_hardware_format.
 */
int FUN_00138ee0(int hardware_format)
{
  int result;

  profile_texture_start();
  result =
    (int)xbox_texture_cache_get_hardware_format((void *)hardware_format, 1, 1);
  profile_texture_end();
  return result;
}

/* FUN_00138f10 (0x138f10) — Bilinear interpolation of a scalar.
 * Computes: base + (a - base) * t1 + (b - base) * t2
 * Used to interpolate damage values between thresholds. */
float FUN_00138f10(float base, float a, float b, float t1, float t2)
{
  return base + (a - base) * t1 + (b - base) * t2;
}

/* FUN_001390d0 (0x1390d0) — XBE naked draft (batch 61). */
#if defined(__clang__)
static void (*const b1390d0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1390d0_exitfn)(int) = system_exit;
static void (*const b1390d0_c1805f0)(int *param_1, float *param_2) = FUN_001805f0;
static unsigned int (*const b1390d0_c7dad0)(int bitmap_ref, float *uv, float level, float *out) = bitmap_2d_get_pixel;
static void (*const b1390d0_c7afb0)(unsigned int color, float *dst) = pixel32_to_real_rgb_color;
static char (*const b1390d0_cab9c0)(void) = FUN_000ab9c0;

__attribute__((naked, noinline))
void FUN_001390d0(int material __attribute__((unused)), int bitmap_ref __attribute__((unused)), uint16_t *indices __attribute__((unused)), float bary_u __attribute__((unused)), float bary_v __attribute__((unused)), float *out_rgb __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x20, %%esp\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "movw 0xb0(%%esi), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "pushl %%edi\n\t"
      "je .LFUN_001390d0_1\n\t"
      "cmpw $1, %%ax\n\t"
      "je .LFUN_001390d0_1\n\t"
      "pushl $1\n\t"
      "pushl $0xa7\n\t"
      "pushl $0x29b324\n\t"
      "pushl $0x29b350\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001390d0_1:\n\t"
      "movl 0x10(%%ebp), %%edi\n\t"
      "movzwl (%%edi), %%ecx\n\t"
      "leal -0x20(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl 0xf8(%%esi), %%eax\n\t"
      "shll $5, %%ecx\n\t"
      "addl %%eax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1805f0]\n\t"
      "movzwl 0x2(%%edi), %%eax\n\t"
      "leal -0x18(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl 0xf8(%%esi), %%edx\n\t"
      "shll $5, %%eax\n\t"
      "addl %%edx, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1805f0]\n\t"
      "movzwl 0x4(%%edi), %%edx\n\t"
      "movl 0xf8(%%esi), %%edi\n\t"
      "leal -0x10(%%ebp), %%ecx\n\t"
      "shll $5, %%edx\n\t"
      "pushl %%ecx\n\t"
      "addl %%edi, %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c1805f0]\n\t"
      "movl 0x1c(%%ebp), %%eax\n\t"
      "flds -0x18(%%ebp)\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "fsubs -0x20(%%ebp)\n\t"
      "addl $0x18, %%esp\n\t"
      "pushl %%eax\n\t"
      "fmuls 0x14(%%ebp)\n\t"
      "pushl $0x3e99999a\n\t"
      "flds -0x10(%%ebp)\n\t"
      "leal -0x8(%%ebp), %%ecx\n\t"
      "fsubs -0x20(%%ebp)\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "fmuls 0x18(%%ebp)\n\t"
      "faddp %%st(1)\n\t"
      "fadds -0x20(%%ebp)\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fsubs -0x1c(%%ebp)\n\t"
      "fmuls 0x14(%%ebp)\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fsubs -0x1c(%%ebp)\n\t"
      "fmuls 0x18(%%ebp)\n\t"
      "faddp %%st(1)\n\t"
      "fadds -0x1c(%%ebp)\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "call *%[c7dad0]\n\t"
      "addl $0xc, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[c7afb0]\n\t"
      "addl $8, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "movl 0x46f074, %%eax\n\t"
      "cmpb $0, (%%eax)\n\t"
      "je .LFUN_001390d0_2\n\t"
      "call *%[cab9c0]\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001390d0_2\n\t"
      "movb $1, %%al\n\t"
      "ret\n\t"
      ".LFUN_001390d0_2:\n\t"
      "xorb %%al, %%al\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b1390d0_assert), [exitfn] "m"(b1390d0_exitfn), [c1805f0] "m"(b1390d0_c1805f0), [c7dad0] "m"(b1390d0_c7dad0), [c7afb0] "m"(b1390d0_c7afb0), [cab9c0] "m"(b1390d0_cab9c0)
      : "memory");
}
#else
#error "FUN_001390d0: clang naked draft required"
#endif

/* --- damage.obj batch drafts (2026-07-26) --- */

/* 0x136700 — Maximum shield vitality, optionally scaled by game difficulty. */
float object_get_maximum_shield_vitality(int object_handle,
                                         char use_shield_multiplier)
{
  char *obj = (char *)object_get_and_verify_type(object_handle, -1);
  float maximum = *(float *)(obj + 0x8c);

  if (use_shield_multiplier)
    return maximum;

  return FUN_000b55b0(2, *(int16_t *)(obj + 0x68)) * maximum;
}


/* 0x138f30 — bilinear 2D (out@eax, c@ecx, d@edx, base@esi; u/v cdecl). */
void FUN_00138f30(float *output, float *vertex_c, float *vertex_d, float *base,
                  float u, float v)
{
  output[0] = base[0] + (vertex_d[0] - base[0]) * u + (vertex_c[0] - base[0]) * v;
  output[1] = base[1] + (vertex_d[1] - base[1]) * u + (vertex_c[1] - base[1]) * v;
}


/* 0x138f70 — bilinear 3D (out@eax, c@ecx, d@edx, base@esi; u/v cdecl). */
void FUN_00138f70(float *output, float *vertex_c, float *vertex_d, float *base,
                  float u, float v)
{
  output[0] = base[0] + (vertex_d[0] - base[0]) * u + (vertex_c[0] - base[0]) * v;
  output[1] = base[1] + (vertex_d[1] - base[1]) * u + (vertex_c[1] - base[1]) * v;
  output[2] = base[2] + (vertex_d[2] - base[2]) * u + (vertex_c[2] - base[2]) * v;
}


/* 0x138fd0 — Sample lightmap RGB at barycentric UV on a material surface. */

void FUN_00138fd0(int material, int lightmap, unsigned short *vertex_indices,
                  float u, float v, float *out_rgb)
{
  char *esi = (char *)material;
  unsigned short *edi = vertex_indices;
  int16_t ax = *(int16_t *)(esi + 0xc4);
  int edx = *(int *)(esi + 0xb4);
  int verts_base = *(int *)(esi + 0xf8);
  float v0[2];
  float v1[2];
  float v2[2];
  float uv[2];
  unsigned int pixel;

  if (ax != 2 && ax != 3) {
    display_assert((char *)0x0029b268, (char *)0x0029b324, 0x8f, 1);
    system_exit(-1);
  }

  FUN_001806e0(verts_base + ((int)edi[0] + edx * 4) * 8, v0);
  FUN_001806e0(verts_base + ((int)edi[1] + edx * 4) * 8, v1);
  FUN_001806e0(verts_base + ((int)edi[2] + edx * 4) * 8, v2);

  uv[0] = v0[0] + (v1[0] - v0[0]) * u + (v2[0] - v0[0]) * v;
  uv[1] = v0[1] + (v1[1] - v0[1]) * u + (v2[1] - v0[1]) * v;

  pixel = bitmap_2d_get_pixel(lightmap, uv, 1.0f, out_rgb);
  pixel32_to_real_rgb_color(pixel, out_rgb);
}


/* object_deplete_shield (0x136b40) — One-shot "vitality pool just hit zero"
 * transition for the pool tracked by obj+0x94.
 *
 * Name is INFERRED, not string-proven: this is the paired sibling of the
 * confirmed object_deplete_body (0x137540). FUN_001a7b50 (units.c) contains two
 * adjacent, structurally identical blocks — one calls 0x136b40 when the
 * obj+0x94 ratio transitions to zero, the other calls object_deplete_body when
 * the obj+0x90 ratio does. The two functions differ only in which flag bit they
 * latch (0x8 here vs 0x4) and which 'coll' effect field they fire
 * (coll+0x1a4 here vs coll+0xb4).
 *
 * If bit 3 of the damage flags byte (obj+0xb6) is not already set:
 *   1. Looks up the object's collision model tag (obje+0x7c -> 'coll')
 *   2. If the collision model has an effect reference at coll+0x1a4 (!= -1),
 *      creates that effect on the object via FUN_0009ec30
 *   3. Sets bit 3 of obj+0xb6
 *   4. Clears obj+0x98 (damage-related counter/timer)
 *   5. Calls FUN_00136a00 to set region "cannot be destroyed" bytes
 *
 * Confirmed: cdecl, 1 stack param (object_handle), void return.
 * Confirmed: PUSH -1; PUSH EDI; CALL 0x13d680 => object_get_and_verify_type.
 * Confirmed: TEST AL,0x8 at 0x136b5b checks bit 3 of [ESI+0xb6].
 * Confirmed: tag_get('obje', [ESI]) at CALL 0x1ba140.
 * Confirmed: CMP EAX,-1 at 0x136b72 checks collision model index.
 * Confirmed: tag_get('coll', obje[0x7c]) at second CALL 0x1ba140.
 * Confirmed: 8 pushes [0,0,0,0,-1,EDI,EDI,ECX] before CALL 0x9ec30. The
 *   ADD ESP,0x28 after it is 0x20 (8 args) plus the folded 0x8 cleanup of the
 *   preceding tag_get, so the ARG_COUNT hazard (cleanup=10) is a FALSE POSITIVE
 *   and FUN_0009ec30's 8-param decl is correct.
 * Confirmed: params 5/6 are plain PUSH 0 immediates (no FLD/FSTP), i.e. float
 *   literal zeros, not a push-then-fstp float.
 * Confirmed: OR byte [ESI+0xb6],0x8 at 0x136b9d sets bit 3 (BYTE, not widened).
 * Confirmed: MOV [ESI+0x98],0x0 at 0x136ba8 clears dword.
 * Confirmed: MOV EAX,EDI; CALL 0x136a00 => FUN_00136a00(@EAX=handle, 0).
 */
void FUN_00136b40(int object_handle)
{
  char *obj;
  char *obje_tag;
  char *coll_tag;
  int coll_index;

  obj = (char *)object_get_and_verify_type(object_handle, -1);
  if ((*(unsigned char *)(obj + 0xb6) & 8) == 0) {
    obje_tag = (char *)tag_get(0x6f626a65, *(int *)obj);
    coll_index = *(int *)(obje_tag + 0x7c);
    if (coll_index != -1) {
      coll_tag = (char *)tag_get(0x636f6c6c, coll_index);
      FUN_0009ec30(*(int *)(coll_tag + 0x1a4), object_handle, object_handle, -1,
                   0.0f, 0.0f, 0, 0); /* dup-args-ok: confirmed PUSH EDI,EDI */
    }
    *(unsigned char *)(obj + 0xb6) |= 8;
    *(int *)(obj + 0x98) = 0;
    FUN_00136a00(object_handle, 0);
  }
}


/* 0x136bc0 — Apply shield damage from a collision hit. */
void FUN_00136bc0(int current_object_handle, void *collision_model, void *material,
                  void *damage_effect, void *damage_params, unsigned int *flags,
                  float *shield_damage, float *body_damage)
{
  char *obj;
  char *coll;
  char *mat;
  char *jpt;
  float remaining;
  float shield_apply;
  float max_shield;
  float recharge_frac;
  float scaled;
  float actual;
  char report_shield;
  char friendly_fire;

  (void)damage_params;
  obj = (char *)object_get_and_verify_type(current_object_handle, -1);
  coll = (char *)collision_model;
  mat = (char *)material;
  jpt = (char *)damage_effect;

  remaining = *body_damage;
  shield_apply = remaining;
  report_shield = 0;
  friendly_fire = 0;

  if (!game_engine_running()) {
    if (*(short *)(jpt + 2) == 1 && *(short *)(obj + 0x68) == 1)
      friendly_fire = 1;
  }

  if (!(*(float *)(obj + 0x94) > 0.0f)) {
    /* XBE 0x136ed9: zero shield apply/pool then fall through to outputs. */
    shield_apply = 0.0f;
    *(float *)(obj + 0x94) = 0.0f;
    goto write_outputs;
  }

  /* XBE re-resolves the object before reading max shield. */
  obj = (char *)object_get_and_verify_type(current_object_handle, -1);
  max_shield = *(float *)(obj + 0x8c);
  if (!friendly_fire)
    max_shield = FUN_000b55b0(2, (int)*(unsigned short *)(obj + 0x68)) *
                 max_shield;

  if (max_shield > 0.0f)
    recharge_frac = *(float *)0x2533c8 / max_shield;
  else
    recharge_frac = 0.0f;

  if ((*flags & 0x10) == 0 || (coll[0] & 4) == 0) {
    shield_apply = (*(float *)0x2533c8 - *(float *)(mat + 0x28)) * remaining;
    if (*(float *)(obj + 0x94) > *(float *)(coll + 0xf0) &&
        *(float *)(coll + 0xf0) > 0.0f) {
      float ratio = *(float *)(obj + 0x94) / *(float *)(coll + 0xf0);
      float t = transition_function_evaluate(*(short *)(coll + 0xec), ratio);
      shield_apply *= (*(float *)0x2533c8 - *(float *)(coll + 0xf4)) * t +
                      *(float *)(coll + 0xf4);
    }
  }

  if ((*(unsigned char *)(obj + 0xb6) & 0x10) != 0) {
    shield_apply = remaining;
    remaining = 0.0f;
    goto shield_recharge;
  }

  if (!(shield_apply > 0.0f))
    shield_apply = 0.0f;
  remaining -= shield_apply;

  if ((*flags & 0x30) == 0x30) {
    float diff = FUN_000b5590(0);
    if (diff > 0.0f)
      shield_apply /= diff;
  }

  scaled = shield_apply * *(float *)(mat + 0x2c);
  {
    int16_t shield_mat = *(int16_t *)(coll + 0xd2);
    if (shield_mat < 0 || shield_mat >= 0x21) {
      display_assert((char *)0x0029aee0, (char *)0x0029af50, 0x60e, 1);
      system_exit(-1);
    }
    scaled *= *(float *)((char *)jpt + (int)shield_mat * 4 + 0x3c);
  }
  if (scaled > *(float *)0x253f44)
    report_shield = 1;

  actual = recharge_frac * scaled;
  if (actual > *(float *)(obj + 0x94) || *(short *)jpt == 3) {
    float overflow = scaled - max_shield * *(float *)(obj + 0x94);
    if (overflow >= 0.0f)
      remaining += overflow;
    *(float *)(obj + 0x94) = 0.0f;
    if ((*(unsigned char *)(obj + 0xb6) & 8) == 0) {
      object_deplete_shield(current_object_handle);
      *flags |= 8;
    }
  } else {
    if ((*(unsigned char *)(obj + 0xb6) & 8) == 0)
      *(float *)(obj + 0x94) -= actual;
    if ((*(unsigned char *)(obj + 0xb6) & 2) == 0 &&
        *(float *)(obj + 0x94) <= *(float *)(coll + 0x184)) {
      FUN_001369e0(current_object_handle, *(int *)(coll + 0x194));
      *(unsigned char *)(obj + 0xb6) |= 2;
    }
  }

shield_recharge:
  if (!report_shield) {
    float pool = *body_damage - remaining;
    *(int *)(obj + 0xac) = 0;
    pool *= recharge_frac;
    if ((*(unsigned char *)(obj + 0xb6) & 8) == 0)
      *(float *)(obj + 0x98) = *(float *)0x2533c8;
    *(float *)(obj + 0xa4) += pool;
    if (*(float *)(obj + 0x98) > *(float *)0x2533c8)
      *(float *)(obj + 0x98) = *(float *)0x2533c8;
    if (*(float *)(obj + 0xa4) > *(float *)0x2533c8)
      *(float *)(obj + 0xa4) = *(float *)0x2533c8;
  }

write_outputs:
  /* XBE: stun unless (shield_apply < coll+0x108 AND shield != 0). */
  if (!(shield_apply < *(float *)(coll + 0x108) &&
        *(float *)(obj + 0x94) != 0.0f)) {
    FUN_001d9068();
    *(short *)(obj + 0xb4) =
        (short)(int)(*(float *)(coll + 0x10c) * *(float *)0x253394);
  }
  *shield_damage = shield_apply;
  *body_damage = remaining;
}



/* 0x1377d0 — apply body vitality damage for one hit. */

void FUN_001377d0(int object_handle, int region_index, int node_index,
                  unsigned int param_4, void *collision_model, void *material,
                  void *damage_effect, void *damage_params, unsigned int *flags,
                  float *body_damage, void **param_11, float scale)
{
  char *obj;
  char *coll;
  char *mat;
  char *jpt;
  char *dp;
  float amount;
  float body_scale;
  float max_body;
  float inv_body;
  float recent_a;
  float recent_b;
  char friendly_fire;
  int region;
  unsigned int flag_bits;

  (void)param_4;
  obj = (char *)object_get_and_verify_type(object_handle, -1);
  coll = (char *)collision_model;
  mat = (char *)material;
  jpt = (char *)damage_effect;
  dp = (char *)damage_params;

  /* ebp-4 amount: scale * material+0x3c (pre-normalization). */
  amount = scale * *(float *)(mat + 0x3c);

  /* collision_model flag 0x40 + vehicle with no driver → zero amount. */
  if ((coll[0] & 0x40) != 0 && *(short *)(obj + 0x64) == 1) {
    char *veh = (char *)object_get_and_verify_type(object_handle, 3);
    if (*(int *)(veh + 0x2d4) == -1)
      amount = 0.0f;
  }

  friendly_fire = 0;
  if (!game_engine_running()) {
    if (*(short *)(jpt + 2) == 1 && *(short *)(obj + 0x68) == 1)
      friendly_fire = 1;
  }

  max_body = *(float *)(obj + 0x88);
  if (!friendly_fire)
    max_body = FUN_000b55b0(1, (int)*(unsigned short *)(obj + 0x68)) *
               max_body;

  if (max_body > 0.0f)
    inv_body = *(float *)0x2533c8 / max_body;
  else
    inv_body = 0.0f;

  body_scale = amount;
  flag_bits = *flags;
  /* XBE: (1 - collision_model+0x44) when flags&0x10; difficulty div if &0x20. */
  if ((flag_bits & 0x10) != 0) {
    body_scale = (*(float *)0x2533c8 - *(float *)(coll + 0x44)) * amount;
    if ((flag_bits & 0x20) != 0) {
      float diff = FUN_000b5590(0);
      if (diff > 0.0f)
        body_scale /= diff;
    }
  }

  body_scale *= inv_body;

  {
    int16_t mat_type = *(int16_t *)(mat + 0x24);
    if (mat_type < 0 || mat_type >= 0x21) {
      display_assert((char *)0x0029b078, (char *)0x0029af50, 0x50f, 1);
      system_exit(-1);
    }
    body_scale *= *(float *)((char *)jpt + (int)mat_type * 4 + 0x3c);
  }

  /* Vitality apply skipped when object+0xb7 bit 3 set. Instant-kill uses amount. */
  if ((*(unsigned char *)(obj + 0xb7) & 8) == 0) {
    if (amount > 0.0f && (mat[0x20] & 1) != 0) {
      if ((*(unsigned int *)(jpt + 4) & 2) != 0) {
        if (!game_engine_running() && *(short *)(obj + 0x64) == 0) {
          char *unit =
              (char *)object_get_and_verify_type(object_handle, 3);
          if (*(int *)(unit + 0x1c8) != -1)
            goto subtract_body;
        }
        *(float *)(obj + 0x90) = 0.0f;
        *flags |= 0x40;
        if (game_engine_running())
          *flags |= 0x80;
      } else if ((*(unsigned int *)(jpt + 4) & 0x800) != 0 &&
                 game_engine_running()) {
        body_scale *= 2.0f;
        if (body_scale > *(float *)(obj + 0x90))
          *flags |= 0x80;
      }
    }
  subtract_body:
    *(float *)(obj + 0x90) -= body_scale;
  }

  if ((short)region_index != (short)-1) {
    region = (int)(short)region_index;
    if (((*(unsigned short *)(obj + 0x124) >> region) & 1) == 0) {
      char *region_elem = (char *)tag_block_get_element(
          (int *)(coll + 0x240), region, 0x54);
      float region_damage = body_scale * *(float *)0x2602c8;
      region_damage += (float)(unsigned char)obj[0x128 + region];
      obj[0x128 + region] = (char)(int)region_damage;
      if (*(float *)(region_elem + 0x28) > 0.0f) {
        float threshold =
            (float)(unsigned char)obj[0x128 + region] *
            *(float *)0x261518;
        if (threshold >= *(float *)(region_elem + 0x28)) {
          FUN_00137690(object_handle, region);
          *flags |= 2;
        }
      }
    }
  }

  *(int *)(obj + 0xb0) = 0;
  recent_a = *(float *)(obj + 0x9c) + body_scale;
  recent_b = *(float *)(obj + 0xa8) + body_scale;
  *(float *)(obj + 0x9c) = recent_a;
  *(float *)(obj + 0xa8) = recent_b;
  if (recent_a > *(float *)0x2533c8)
    *(float *)(obj + 0x9c) = *(float *)0x2533c8;
  if (recent_b > *(float *)0x2533c8)
    *(float *)(obj + 0xa8) = *(float *)0x2533c8;

  if (*(char *)0x5aa890 != 0 && *(float *)(obj + 0x90) > 0.0f) {
    char zero_body = 0;
    if (((1 << *(unsigned char *)(obj + 0x64)) & 3) != 0) {
      char *unit =
          (char *)object_get_and_verify_type(object_handle, 3);
      if (*(int *)(unit + 0x1c8) != -1)
        zero_body = 1;
      else if (*(short *)(obj + 0x64) == 1) {
        int child = *(int *)(obj + 0xc8);
        while (child != -1) {
          char *child_obj =
              (char *)object_get_and_verify_type(child, -1);
          if (((1 << *(unsigned char *)(child_obj + 0x64)) & 3) != 0 &&
              *(int *)(child_obj + 0x1c8) != -1) {
            zero_body = 1;
            break;
          }
          child = *(int *)(child_obj + 0xc4);
          if (child == -1)
            break;
        }
      }
    }
    if (zero_body)
      *(float *)(obj + 0x90) = 0.0f;
  }

  {
    float body_vitality = *(float *)(obj + 0x90);
    float threshold =
        FUN_000b55b0(1, (int)*(unsigned short *)(obj + 0x68)) *
        *(float *)(obj + 0x88) * body_vitality;
    /* XBE: absolute threshold / region / effects read collision_model (+0x18). */
    if (*(float *)(coll + 0xb8) > 0.0f &&
        threshold <= *(float *)(coll + 0xb8)) {
      object_destroy(object_handle);
      *flags |= 5;
    } else if (threshold <= 0.0f) {
      if ((*(unsigned char *)(obj + 0xb6) & 4) == 0) {
        int region_count = *(int *)(coll + 0x240);
        int *region_block = (int *)(coll + 0x240);
        int index;
        for (index = 0; index < region_count; index++) {
          char *region_elem = (char *)tag_block_get_element(
              region_block, index, 0x54);
          if ((region_elem[0x20] & 4) != 0)
            FUN_00137690(object_handle, index);
        }
        object_deplete_body(object_handle);
        *flags |= 1;
      }
    } else if (threshold <= *(float *)(coll + 0x94) &&
               (*(unsigned char *)(obj + 0xb6) & 1) == 0) {
      FUN_0009ec30(*(int *)(coll + 0xa4), object_handle, object_handle, -1,
                   0.0f, 0.0f, 0, 0);
      *(unsigned char *)(obj + 0xb6) |= 1;
    }
  }

  if ((dp[4] & 2) != 0) {
    int coll_index = *(int *)(coll + 0x7c);
    if (coll_index != -1) {
      FUN_00137170((float *)(dp + 0x28), (float *)(dp + 0x34),
                   object_handle, coll_index, (short)node_index,
                   (float *)(dp + 0x28));
    }
  }

  if ((dp[4] & 1) != 0 && body_scale > *(float *)(coll + 0x80)) {
    int effect_index = *(int *)(coll + 0x90);
    if (effect_index != -1 && *(short *)(jpt + 2) != 7) {
      FUN_0009ec30(effect_index, object_handle, object_handle, -1, 0.0f,
                   0.0f, 0, 0);
    }
  }

  *body_damage = body_scale;
  if (param_11 != (void **)0)
    *param_11 = (void *)(uintptr_t) *(unsigned int *)(mat + 0x3c);
}



/* FUN_00138900 (0x138900) — Apply area-damage to one object after a radius query. */
#if defined(__clang__)
static void *(*const d38900_get)(int, int) = object_get_and_verify_type;
static void *(*const d38900_tag)(int, int) = tag_get;
static void (*const d38900_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const d38900_exitfn)(int) = system_exit;
static void (*const d38900_perp)(float *, float *) = perpendicular3d;
static float (*const d38900_norm)(float *) = normalize3d;
static int (*const d38900_oroot)(int) = object_get_root_parent;
static bool (*const d38900_ray)(unsigned int, float *, float *, int, short *) = FUN_0014df70;
static bool (*const d38900_galleg)(short, short) = game_allegiance_get_team_is_friendly;
static float (*const d38900_g5590)(short) = FUN_000b5590;
static int *(*const d38900_gseed)(void) = get_global_random_seed_address;
static float (*const d38900_rmreal)(unsigned int *) = random_math_real;
static void (*const d38900_ocdmg)(void *, int, short, short, short, unsigned int) = object_cause_damage;
static void (*const d38900_d38900)(void *, int, char) = FUN_00138900;

__attribute__((naked, noinline))
void FUN_00138900(void *damage_params __attribute__((unused)), int object_handle __attribute__((unused)), char recursive __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x108, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_00138900_1:\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "pushl $-1\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl (%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x6f626a65\n\t"
      "call *%[tag]\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "movl (%%edi), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x6a707421\n\t"
      "movl %%eax, -0x50(%%ebp)\n\t"
      "call *%[tag]\n\t"
      "movb 0x4(%%esi), %%bl\n\t"
      "notb %%bl\n\t"
      "addl $0x18, %%esp\n\t"
      "andb $1, %%bl\n\t"
      "cmpw $0x20, 0x4761d8\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "movb $0, -0x3(%%ebp)\n\t"
      "jl .LFUN_00138900_2\n\t"
      "pushl $1\n\t"
      "pushl $0x259\n\t"
      "pushl $0x29af50\n\t"
      "pushl $0x253440\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00138900_2:\n\t"
      "movw 0x4761d8, %%ax\n\t"
      "movswl %%ax, %%ecx\n\t"
      "incw %%ax\n\t"
      "testb %%bl, %%bl\n\t"
      "movw $0xa, 0x5a8c80(,%%ecx,2)\n\t"
      "movw %%ax, 0x4761d8\n\t"
      "je .LFUN_00138900_14\n\t"
      "movb 0x64(%%esi), %%cl\n\t"
      "movl $1, %%edx\n\t"
      "shll %%cl, %%edx\n\t"
      "testb $3, %%dl\n\t"
      "je .LFUN_00138900_14\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "flds 0x1cc(%%eax)\n\t"
      "fcomps 0x253f44\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00138900_14\n\t"
      "flds 0x50(%%esi)\n\t"
      "addl $0x28, %%edi\n\t"
      "fsubs (%%edi)\n\t"
      "leal -0x18(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x40(%%ebp), %%edx\n\t"
      "fstps -0x40(%%ebp)\n\t"
      "pushl %%edx\n\t"
      "flds 0x54(%%esi)\n\t"
      "movb $1, -0x2(%%ebp)\n\t"
      "fsubs 0x4(%%edi)\n\t"
      "fstps -0x3c(%%ebp)\n\t"
      "flds 0x58(%%esi)\n\t"
      "fsubs 0x8(%%edi)\n\t"
      "fstps -0x38(%%ebp)\n\t"
      "call *%[perp]\n\t"
      "pushl %%eax\n\t"
      "call *%[norm]\n\t"
      "fstp %%st(0)\n\t"
      "flds -0x10(%%ebp)\n\t"
      "leal -0x34(%%ebp), %%eax\n\t"
      "fmuls -0x3c(%%ebp)\n\t"
      "pushl %%eax\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fmuls -0x38(%%ebp)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0x34(%%ebp)\n\t"
      "flds -0x38(%%ebp)\n\t"
      "fmuls -0x18(%%ebp)\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fmuls -0x40(%%ebp)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0x30(%%ebp)\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fmuls -0x40(%%ebp)\n\t"
      "flds -0x3c(%%ebp)\n\t"
      "fmuls -0x18(%%ebp)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0x2c(%%ebp)\n\t"
      "call *%[norm]\n\t"
      "fstp %%st(0)\n\t"
      "addl $0x10, %%esp\n\t"
      "xorl %%eax, %%eax\n\t"
      "movl %%eax, -0x28(%%ebp)\n\t"
      "movl $4, -0xc(%%ebp)\n\t"
      "jmp .LFUN_00138900_4\n\t"
      ".LFUN_00138900_3:\n\t"
      "movl -0x28(%%ebp), %%eax\n\t"
      ".LFUN_00138900_4:\n\t"
      "cmpl $3, %%eax\n\t"
      "ja .LFUN_00138900_12\n\t"
      "jmp *.LFUN_00138900_jt(,%%eax,4)\n\t"
      ".LFUN_00138900_5:\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "flds 0x1cc(%%ecx)\n\t"
      "jmp .LFUN_00138900_7\n\t"
      ".LFUN_00138900_6:\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "flds 0x1cc(%%edx)\n\t"
      "fchs\n\t"
      ".LFUN_00138900_7:\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fstps -0x24(%%ebp)\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fstps -0x20(%%ebp)\n\t"
      "flds -0x10(%%ebp)\n\t"
      "jmp .LFUN_00138900_11\n\t"
      ".LFUN_00138900_8:\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "flds 0x1cc(%%eax)\n\t"
      "jmp .LFUN_00138900_10\n\t"
      ".LFUN_00138900_9:\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "flds 0x1cc(%%ecx)\n\t"
      "fchs\n\t"
      ".LFUN_00138900_10:\n\t"
      "flds -0x34(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fstps -0x24(%%ebp)\n\t"
      "flds -0x30(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fstps -0x20(%%ebp)\n\t"
      "flds -0x2c(%%ebp)\n\t"
      ".LFUN_00138900_11:\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fstps -0x1c(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      ".LFUN_00138900_12:\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "leal -0xb8(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[oroot]\n\t"
      "addl $4, %%esp\n\t"
      "pushl %%eax\n\t"
      "leal -0x24(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edi\n\t"
      "pushl $0xc221\n\t"
      "call *%[ray]\n\t"
      "movl -0xa0(%%ebp), %%edx\n\t"
      "movl -0x9c(%%ebp), %%eax\n\t"
      "movl -0x98(%%ebp), %%ecx\n\t"
      "movl %%edx, -0x4c(%%ebp)\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl %%eax, -0x48(%%ebp)\n\t"
      "movl %%ecx, -0x44(%%ebp)\n\t"
      "call *%[oroot]\n\t"
      "flds 0x50(%%esi)\n\t"
      "fsubs -0x4c(%%ebp)\n\t"
      "leal -0xb8(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "fstps -0x5c(%%ebp)\n\t"
      "leal -0x5c(%%ebp), %%edx\n\t"
      "flds 0x54(%%esi)\n\t"
      "pushl %%edx\n\t"
      "fsubs -0x48(%%ebp)\n\t"
      "leal -0x4c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0xc221\n\t"
      "fstps -0x58(%%ebp)\n\t"
      "flds 0x58(%%esi)\n\t"
      "fsubs -0x44(%%ebp)\n\t"
      "fstps -0x54(%%ebp)\n\t"
      "call *%[ray]\n\t"
      "addl $0x2c, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00138900_13\n\t"
      "movb %%al, -0x2(%%ebp)\n\t"
      ".LFUN_00138900_13:\n\t"
      "movl -0x28(%%ebp), %%ecx\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "incl %%ecx\n\t"
      "decl %%eax\n\t"
      "movl %%ecx, -0x28(%%ebp)\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "jne .LFUN_00138900_3\n\t"
      "movb -0x2(%%ebp), %%al\n\t"
      "jmp .LFUN_00138900_15\n\t"
      ".LFUN_00138900_14:\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[oroot]\n\t"
      "flds 0x50(%%esi)\n\t"
      "fsubs 0x28(%%edi)\n\t"
      "addl $0x28, %%edi\n\t"
      "leal -0x108(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "fstps -0x68(%%ebp)\n\t"
      "pushl %%eax\n\t"
      "flds 0x54(%%esi)\n\t"
      "leal -0x68(%%ebp), %%eax\n\t"
      "fsubs 0x4(%%edi)\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl $0xc221\n\t"
      "fstps -0x64(%%ebp)\n\t"
      "flds 0x58(%%esi)\n\t"
      "fsubs 0x8(%%edi)\n\t"
      "fstps -0x60(%%ebp)\n\t"
      "call *%[ray]\n\t"
      "addl $0x18, %%esp\n\t"
      ".LFUN_00138900_15:\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00138900_16\n\t"
      "xorb %%bl, %%bl\n\t"
      ".LFUN_00138900_16:\n\t"
      "cmpw $1, 0x4761d8\n\t"
      "jg .LFUN_00138900_17\n\t"
      "pushl $1\n\t"
      "pushl $0x294\n\t"
      "pushl $0x29af50\n\t"
      "pushl $0x253418\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00138900_17:\n\t"
      "decw 0x4761d8\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movl 0x1c8(%%ecx), %%eax\n\t"
      "testb $1, %%al\n\t"
      "je .LFUN_00138900_18\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "cmpl 0xc(%%ecx), %%edx\n\t"
      "jne .LFUN_00138900_18\n\t"
      "xorb %%bl, %%bl\n\t"
      ".LFUN_00138900_18:\n\t"
      "testb $8, %%al\n\t"
      "je .LFUN_00138900_19\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x10(%%edx), %%ax\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x68(%%esi), %%cx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[galleg]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00138900_19\n\t"
      "xorb %%bl, %%bl\n\t"
      "jmp .LFUN_00138900_23\n\t"
      ".LFUN_00138900_19:\n\t"
      "testb %%bl, %%bl\n\t"
      "je .LFUN_00138900_23\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "movl 0x1c8(%%edx), %%eax\n\t"
      "testb $0x10, %%ah\n\t"
      "je .LFUN_00138900_23\n\t"
      "movb 0x64(%%esi), %%cl\n\t"
      "movl $1, %%eax\n\t"
      "shll %%cl, %%eax\n\t"
      "xorb %%bl, %%bl\n\t"
      "testb $3, %%al\n\t"
      "je .LFUN_00138900_23\n\t"
      "movl (%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x756e6974\n\t"
      "call *%[tag]\n\t"
      "movl 0x17c(%%eax), %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "testl $0x80000, %%ecx\n\t"
      "je .LFUN_00138900_23\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "cmpl 0xc(%%eax), %%edx\n\t"
      "je .LFUN_00138900_23\n\t"
      "pushl $8\n\t"
      "call *%[g5590]\n\t"
      "fcoms 0x2533c0\n\t"
      "addl $4, %%esp\n\t"
      "fsts -0xc(%%ebp)\n\t"
      "movb $1, %%bl\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .LFUN_00138900_20\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movl 0x1c8(%%ecx), %%eax\n\t"
      "testb $4, %%ah\n\t"
      "je .LFUN_00138900_21\n\t"
      ".LFUN_00138900_20:\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "testb $0x40, 0x4(%%edx)\n\t"
      "je .LFUN_00138900_21\n\t"
      "xorb %%bl, %%bl\n\t"
      ".LFUN_00138900_21:\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00138900_22\n\t"
      "call *%[gseed]\n\t"
      "pushl %%eax\n\t"
      "call *%[rmreal]\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fmuls 0x25337c\n\t"
      "addl $4, %%esp\n\t"
      "fcompp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00138900_22\n\t"
      "xorb %%bl, %%bl\n\t"
      ".LFUN_00138900_22:\n\t"
      "movb $1, -0x3(%%ebp)\n\t"
      ".LFUN_00138900_23:\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "orl $1, %%edx\n\t"
      "testb %%bl, %%bl\n\t"
      "movl %%edx, 0x4(%%eax)\n\t"
      "je .LFUN_00138900_30\n\t"
      "flds 0x50(%%esi)\n\t"
      "addl $0x34, %%eax\n\t"
      "fsubs (%%edi)\n\t"
      "pushl %%eax\n\t"
      "fstps (%%eax)\n\t"
      "flds 0x54(%%esi)\n\t"
      "fsubs 0x4(%%edi)\n\t"
      "fstps 0x4(%%eax)\n\t"
      "flds 0x58(%%esi)\n\t"
      "fsubs 0x8(%%edi)\n\t"
      "fstps 0x8(%%eax)\n\t"
      "call *%[norm]\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "flds 0x4(%%ecx)\n\t"
      "addl $4, %%esp\n\t"
      "fsubs (%%ecx)\n\t"
      "fcoms 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00138900_24\n\t"
      "fxch %%st(1)\n\t"
      "fsubs (%%ecx)\n\t"
      "fdiv %%st(1), %%st(0)\n\t"
      "fsubrs 0x2533c8\n\t"
      "fxch %%st(1)\n\t"
      "fstp %%st(0)\n\t"
      "fcoms 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00138900_25\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c0\n\t"
      "jmp .LFUN_00138900_27\n\t"
      ".LFUN_00138900_24:\n\t"
      "fstp %%st(0)\n\t"
      "jmp .LFUN_00138900_26\n\t"
      ".LFUN_00138900_25:\n\t"
      "fcoms 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00138900_27\n\t"
      ".LFUN_00138900_26:\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c8\n\t"
      ".LFUN_00138900_27:\n\t"
      "testb $1, 0xc(%%ecx)\n\t"
      "jne .LFUN_00138900_28\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "fld %%st(0)\n\t"
      "fstps 0x40(%%eax)\n\t"
      ".LFUN_00138900_28:\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00138900_29\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "pushl $0\n\t"
      "pushl $-1\n\t"
      "pushl $-1\n\t"
      "pushl $-1\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[ocdmg]\n\t"
      "addl $0x18, %%esp\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      ".LFUN_00138900_29:\n\t"
      "movl -0x50(%%ebp), %%eax\n\t"
      "movl 0x7c(%%eax), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_00138900_30\n\t"
      "pushl %%eax\n\t"
      "pushl $0x636f6c6c\n\t"
      "call *%[tag]\n\t"
      "movb (%%eax), %%cl\n\t"
      "addl $8, %%esp\n\t"
      "testb $8, %%cl\n\t"
      "je .LFUN_00138900_30\n\t"
      "movl 0xc8(%%esi), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_00138900_30\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "pushl $1\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[d38900]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_00138900_30:\n\t"
      "movb -0x3(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00138900_32\n\t"
      "testb %%bl, %%bl\n\t"
      "je .LFUN_00138900_31\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00138900_32\n\t"
      ".LFUN_00138900_31:\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "orl $0x40, 0x4(%%eax)\n\t"
      ".LFUN_00138900_32:\n\t"
      "movb 0x10(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00138900_33\n\t"
      "movl 0xc4(%%esi), %%esi\n\t"
      "cmpl $-1, %%esi\n\t"
      "je .LFUN_00138900_33\n\t"
      "movb $1, 0x10(%%ebp)\n\t"
      "movl %%esi, 0xc(%%ebp)\n\t"
      "jmp .LFUN_00138900_1\n\t"
      ".LFUN_00138900_33:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_00138900_jt:\n\t"
      ".long .LFUN_00138900_5\n\t"
      ".long .LFUN_00138900_6\n\t"
      ".long .LFUN_00138900_8\n\t"
      ".long .LFUN_00138900_9\n\t"
      ".text\n\t"
      :
      : [get] "m"(d38900_get), [tag] "m"(d38900_tag), [assert] "m"(d38900_assert), [exitfn] "m"(d38900_exitfn), [perp] "m"(d38900_perp), [norm] "m"(d38900_norm), [oroot] "m"(d38900_oroot), [ray] "m"(d38900_ray), [galleg] "m"(d38900_galleg), [g5590] "m"(d38900_g5590), [gseed] "m"(d38900_gseed), [rmreal] "m"(d38900_rmreal), [ocdmg] "m"(d38900_ocdmg), [d38900] "m"(d38900_d38900)
      : "memory");
}
#else
#error "FUN_00138900: clang naked draft required"
#endif
