#include "x87_math.h"

/* Check if an actor has a swarm component or its unit is in a vehicle seat. */
int FUN_0002a360(int actor_handle)
{
  char *actor = (char *)datum_get(actor_data, actor_handle);
  if (*(short *)(actor + 0x418) != -1)
    return 1;
  if (*(int *)(actor + 0x18) != -1 && unit_is_busy(*(int *)(actor + 0x18)))
    return 1;
  return 0;
}

/* Clear 100 bytes of actor state at offset 0x2ec (action decision state). */
void FUN_00036860(int actor_handle)
{
  char *actor = (char *)datum_get(actor_data, actor_handle);
  csmemset(actor + 0x2ec, 0, 0x64);
}

/* 0x36890 — Post a movement directive to an actor's directive fields
 * (actor+0x312..0x348). Updates the actor's priority and position-pair
 * directive only if the actor state (actor+0x6a) is below 3 AND the incoming
 * priority is >= the current stored priority. position_a and position_b may
 * independently be NULL; the corresponding valid flag byte is cleared when NULL
 * is passed. Confirmed ABI: actor_handle @<eax>, position_a @<ecx> (float[3] or
 * NULL), priority @<edx> (short), position_b @<ebx> (float[3] or NULL), plus 6
 * cdecl stack args.
 */
void FUN_00036890(int actor_handle, int *position_a, short priority,
                  int *position_b, int param5, int param6, int param7,
                  int param8, int param9, char param10)
{
  int actor;
  float *pa;
  float *pb;

  actor = (int)datum_get(actor_data, actor_handle);
  if (*(short *)(actor + 0x6a) >= 3) {
    return;
  }
  if (priority < *(short *)(actor + 0x312)) {
    return;
  }

  *(short *)(actor + 0x312) = priority;

  pa = (float *)position_a;
  if (pa == (float *)0) {
    *(char *)(actor + 0x314) = 0;
  } else {
    *(char *)(actor + 0x314) = 1;
    *(float *)(actor + 0x318) = pa[0];
    *(float *)(actor + 0x31c) = pa[1];
    *(float *)(actor + 0x320) = pa[2];
    *(int *)(actor + 0x324) = param5;
    *(int *)(actor + 0x328) = param6;
  }

  pb = (float *)position_b;
  if (pb == (float *)0) {
    *(char *)(actor + 0x32c) = 0;
  } else {
    *(char *)(actor + 0x32c) = 1;
    *(float *)(actor + 0x330) = pb[0];
    *(float *)(actor + 0x334) = pb[1];
    *(float *)(actor + 0x338) = pb[2];
  }

  *(int *)(actor + 0x33c) = param7;
  *(int *)(actor + 0x340) = param8;
  *(int *)(actor + 0x344) = param9;
  *(char *)(actor + 0x348) = param10;
}

/* FUN_00036960 (0x36960) — post direction/position stimulus at a given
 * priority.
 *
 * Resolves actor via datum_get(actor_data, actor_handle).
 * actor+0x2ee (short) holds the current best priority; actor+0x2f4 (int)
 * holds param3; actor+0x2f8 (byte) is a direction-valid flag;
 * actor+0x2fc..0x304 (3 ints) holds the direction vector.
 *
 * Only updates when the incoming priority strictly exceeds the stored one
 * (JLE skips the body). No equal-case handling.
 *
 * When direction is NULL the flag byte is cleared (CL=0, from ECX=0 after
 * TEST ECX,ECX); when non-NULL the flag is set to 1 and three dwords are
 * copied from the direction array.
 *
 * Confirmed: cdecl, ADD ESP,0x10 after call sites in FUN_000374f0.
 * Confirmed: comparison is signed CMP CX,[EAX+0x2ee] / JLE skip.
 * Confirmed: fields actor+0x2ee (short priority), +0x2f4 (int param3),
 *   +0x2f8 (byte flag), +0x2fc/+0x300/+0x304 (direction[0..2]).
 * Confirmed: NULL-direction path writes CL (=0) to flag byte via
 *   MOV byte ptr [EAX+0x2f8],CL — not a literal 0 immediate. */
void FUN_00036960(int actor_handle, short priority, int param3, int *direction)
{
  char *actor;

  actor = (char *)datum_get(actor_data, actor_handle);
  if (*(short *)(actor + 0x2ee) < priority) {
    *(short *)(actor + 0x2ee) = priority;
    *(int *)(actor + 0x2f4) = param3;
    if (direction == 0) {
      *(char *)(actor + 0x2f8) = 0;
      return;
    }
    *(char *)(actor + 0x2f8) = 1;
    *(int *)(actor + 0x2fc) = direction[0];
    *(int *)(actor + 0x300) = direction[1];
    *(int *)(actor + 0x304) = direction[2];
  }
}

/* FUN_000369c0 (0x369c0) — post scalar stimulus value at a given priority.
 *
 * Resolves actor via datum_get(actor_data, actor_handle).
 * actor+0x34a (short) holds the current best priority; actor+0x34c (int)
 * holds the associated value.
 *
 * If the incoming priority strictly exceeds the stored one, unconditionally
 * replace both the priority and value.  If they are equal, keep the maximum
 * of the stored and incoming values.  If the stored priority is higher, do
 * nothing.
 *
 * Confirmed: cdecl, ADD ESP,0xc after FUN_000369c0 at call sites.
 * Confirmed: comparison is signed CMP CX,DX / JGE; equal-path uses CMP/JG
 *   then MOV ECX,EDX to take the max.
 * Confirmed: fields at actor+0x34a (short priority) and actor+0x34c (int
 *   value) directly from disassembly MOV/CMP at those offsets. */
void FUN_000369c0(int actor_handle, short priority, int value)
{
  char *actor;
  int stored_value;

  actor = (char *)datum_get(actor_data, actor_handle);
  if (*(short *)(actor + 0x34a) < priority) {
    *(short *)(actor + 0x34a) = priority;
    *(int *)(actor + 0x34c) = value;
    return;
  }
  if (*(short *)(actor + 0x34a) == priority) {
    stored_value = *(int *)(actor + 0x34c);
    if (stored_value <= value) {
      stored_value = value;
    }
    *(int *)(actor + 0x34c) = stored_value;
  }
}

/* 0x36a20 — Notify an actor's unit of a communication stimulus from an
 * encounter. Checks that the encounter is active (+0x60) and not excluded
 * (+0x127), and that the actor has a unit. If so, calls FUN_00046f10 with type
 * 4 (if param_3) or 5 (otherwise), using the actor's unit handle and the
 * encounter's object. */
void FUN_00036a20(int actor_handle, int encounter_handle, char param_3)
{
  char *actor;
  char *encounter;

  actor = (char *)datum_get(actor_data, actor_handle);
  encounter = (char *)datum_get(*(data_t **)0x5ab23c, encounter_handle);
  if (*(char *)(encounter + 0x127) == 0 && *(int *)(actor + 0x18) != -1 &&
      *(char *)(encounter + 0x60) != 0) {
    FUN_00046f10(param_3 != '\0' ? 4 : 5, *(int *)(actor + 0x18),
                 *(int *)(encounter + 0x18), 3, -1, -1, 0);
  }
}

/* FUN_00036a90 (0x36a90) — actor seek-prop approach: record timestamp,
 * find pathfinding location, post priority-2 move stimulus toward prop+0xf0.
 * Stack args to FUN_00036890 (orig 0x36a90 push order, right-to-left):
 *   param5=prop->0xec, param6=1.5f, param7=90 (0x5a), param8=prop_handle,
 *   param9=90, param10=1.  param7->actor+0x33c, param8->actor+0x340
 *   (combat_transition_prop_index). Disasm: 0x36adb push 0x5a (param7);
 *   0x36ada push edi=prop_handle (param8). */
void FUN_00036a90(int actor_handle, int prop_handle)
{
  char *actor;
  char *prop;
  int game_time;

  actor = (char *)datum_get(actor_data, actor_handle);
  prop = (char *)datum_get(prop_data, prop_handle);
  game_time = game_time_get();
  *(int *)(actor + 0x3a0) = game_time;
  actor_perception_find_prop_pathfinding_location(actor_handle, prop_handle);
  FUN_00036890(actor_handle, (int *)(prop + 0xf0), 2, NULL,
               *(int *)(prop + 0xec), 0x3fc00000, 0x5a, prop_handle, 0x5a, 1);
}

/* FUN_00036b10 (0x36b10) — actor prop-approach stimulus, priority 6.
 * Like FUN_00036b50 but priority 6; stack args: -1, 0, 90, prop_handle, 150, 0.
 */
void FUN_00036b10(int actor_handle, int prop_handle)
{
  char *prop;

  prop = (char *)datum_get(prop_data, prop_handle);
  FUN_00036890(actor_handle, NULL, 6, (int *)(prop + 0xe0), -1, 0, 0x5a,
               prop_handle, 0x96, 0);
}

/*
 * FUN_00036b50 — trigger a swarm damage/retreat reaction.
 *
 * Looks up the swarm component datum for param_2, then fires stimulus
 * FUN_00036890 to the actor (param_1) at priority 1 referencing the
 * swarm component data block. If the component has a linked secondary handle
 * (field_0x1c) and the secondary datum's field_0x74 (short) is positive,
 * also fires a scalar stimulus via FUN_000369c0 with value 0x1c2 (450).
 *
 * Globals: 0x5ab23c = encounter data; actor_data (0x6325a4) for secondary.
 *
 * 0x36b50 / actors.obj
 */
void FUN_00036b50(int param_1, int param_2)
{
  char *iVar1;
  char *iVar2;

  iVar1 = (char *)datum_get(*(data_t **)0x5ab23c, param_2);
  FUN_00036890(param_1, NULL, 1, (int *)(iVar1 + 0xe0), -1, 0, 0x5a, param_2,
               0x96, 0);
  if (*(int *)(iVar1 + 0x1c) != -1) {
    iVar2 = (char *)datum_get(actor_data, *(int *)(iVar1 + 0x1c));
    if (*(short *)(iVar2 + 0x74) > 0) {
      FUN_000369c0(param_1, *(short *)(iVar2 + 0x74), 0x1c2);
    }
  }
}

/* 0x36bd0 — Post an object-look stimulus (type 5, priority 1) to an actor.
 * Builds a look_buf with word 0x1 and passes param_2 (object handle) adjacent
 * so FUN_00027a60 can read it as part of the buffer. */
void FUN_00036bd0(int actor_handle, int param_2)
{
  short look_buf[4]; /* [0]=1, [2..3]=param_2 as int overlay */

  look_buf[0] = 1;
  *(int *)(&look_buf[2]) = param_2;
  FUN_00027a60(actor_handle, 5, 1, look_buf);
}

/* FUN_00036c00 (0x36c00) — flee/scatter look reaction.
 *
 * Resolves the actor record via datum_get(actor_data, actor_handle).
 * If actor+0x6a (short state) != 1, posts a position-look directive to the
 * actor by building a 16-byte look buffer { type=3, pad, float pos[3] } from
 * the caller's position vector and dispatching it through FUN_00027a60
 * (actor_handle, 1, 1, look_buf).
 *
 * The object_handle and count parameters are present in the calling
 * convention (see actors_handle_spatial_effect dispatch) but unused by this
 * variant — only the flee position is forwarded as a look target.
 *
 * Confirmed: 4 cdecl args (caller passes actor_handle, object_handle,
 *   position, count); ADD ESP,0x8 after datum_get; ADD ESP,0x10 after
 *   FUN_00027a60.
 * Confirmed: state field check is CMP word ptr [EAX+0x6a],0x1 / JZ skip.
 * Confirmed: look_buf layout — word 0x3 at +0x00, position[0..2] at +0x04.
 * Confirmed: FUN_00027a60(actor_handle, 1, 1, look_buf) — look_type=1,
 *   priority=1. */
void FUN_00036c00(int actor_handle, int object_handle, float *position,
                  short count)
{
  char *actor;
  short look_buf[8]; /* 16 bytes: [0]=type word, [2..7]=position data */

  (void)object_handle;
  (void)count;

  actor = (char *)datum_get(actor_data, actor_handle);
  if (*(short *)(actor + 0x6a) != 1) {
    look_buf[0] = 3;
    *(float *)&look_buf[2] = position[0];
    *(float *)&look_buf[4] = position[1];
    *(float *)&look_buf[6] = position[2];
    FUN_00027a60(actor_handle, 1, 1, look_buf);
  }
}

/* FUN_00036c50 (0x36c50) — actor prop-reaction: if prop is "active" (field_0x60
 * != 0), post priority-6 stimulus to prop+0xe0. Otherwise call FUN_00036b50,
 * then check linked player/actor handles for perception and team-friendliness.
 * Always finishes with a look-at-prop stimulus (type 7, priority 1) via
 * FUN_00027a60. */
void FUN_00036c50(int actor_handle, int prop_handle)
{
  char *prop;
  char *obj;
  char *player_datum;
  char *actor;
  char *actor_2;
  char *obj_type2;
  int related_handle;
  int game_time;
  short look_buf[8];

  prop = (char *)datum_get(prop_data, prop_handle);
  if (*(char *)(prop + 0x60) != 0) {
    prop = (char *)datum_get(prop_data, prop_handle);
    FUN_00036890(actor_handle, NULL, 6, (int *)(prop + 0xe0), -1, 0, 0x5a,
                 prop_handle, 0x96, 0);
    goto exit_look;
  }
  obj = (char *)object_get_and_verify_type(*(int *)(prop + 0x18), 3);
  FUN_00036b50(actor_handle, prop_handle);
  related_handle = *(int *)(obj + 0x1c8);
  if (related_handle != -1) {
    player_datum = (char *)datum_get(player_data, related_handle);
    if (*(int *)(player_datum + 0x40) != -1) {
      game_time = game_time_get();
      if (*(int *)(player_datum + 0x44) + 0x5a >= game_time) {
        actor = (char *)datum_get(actor_data, actor_handle);
        obj_type2 =
          (char *)object_get_and_verify_type(*(int *)(player_datum + 0x40), 3);
        if (game_allegiance_get_team_is_friendly(
              *(int16_t *)(actor + 0x3e), *(int16_t *)(obj_type2 + 0x68))) {
          actor_perception_create_orphan_from_friend(
            actor_handle, *(int *)(player_datum + 0x40), -1, -1);
        }
      }
    }
    goto exit_look;
  }
  if (*(int *)(obj + 0x1a4) == -1)
    goto exit_look;
  actor_2 = (char *)datum_get(actor_data, *(int *)(obj + 0x1a4));
  if (*(short *)(actor_2 + 0x6e) < 4)
    goto exit_look;
  actor_derive_target_information(actor_handle, *(int *)(obj + 0x1a4));
exit_look:
  look_buf[0] = 1;
  *(int *)&look_buf[2] = prop_handle;
  FUN_00027a60(actor_handle, 7, 1, look_buf);
}

/* 0x36da0 — Set actor stimulus-received flag at offset +0x2f0 to 1. */
void FUN_00036da0(int actor_handle)
{
  char *actor;

  actor = (char *)datum_get(actor_data, actor_handle);
  *(char *)(actor + 0x2f0) = 1;
}

/* FUN_00036dc0 (0x36dc0)
 * Notify an actor's unit of a combat stimulus and optionally clamp
 * the actor's "recently perceived threat" counter.
 *
 * If the actor has an associated unit (actor+0x18 != -1) this calls
 * FUN_00046f10 (ai_communication) with type 0x16 when flags_bit1 is
 * set, or type 0x17 when flags_bit1 is clear. The remaining six args
 * are (unit_handle, -1, -1, -1, -1, 0).
 *
 * If flags_bit0 is set and actor->field_0x308 (int16) is less than 6,
 * the field is clamped to 6 and actor->field_0x30c is set to -1.
 *
 * Confirmed: 3 cdecl args, void return, ADD ESP,0xc at all three call
 * sites (0x560af, 0x56499, 0x5dd9b). */
void FUN_00036dc0(int actor_handle, char flags_bit1, char flags_bit0)
{
  char *actor;
  int unit_handle;
  int type;

  actor = (char *)datum_get(actor_data, actor_handle);
  unit_handle = *(int *)(actor + 0x18);
  if (unit_handle != -1) {
    type = flags_bit1 ? 0x16 : 0x17;
    FUN_00046f10(type, unit_handle, -1, -1, -1, -1, 0);
  }
  if (flags_bit0 && *(short *)(actor + 0x308) < 6) {
    *(short *)(actor + 0x308) = 6;
    *(int *)(actor + 0x30c) = -1;
  }
}

/* FUN_00036e30 (0x36e30)
 * Mark an actor as having an active approach. Looks up the actor
 * record in actor_data and sets the byte flag at offset +0x2ed to 1.
 * Called from ai_handle_unit_approach when a non-friendly unit is
 * within approach range and the caller's flag parameter is set.
 * Confirmed: 1 cdecl arg (ADD ESP,4 at call site), void return,
 * single datum_get call followed by byte store. */
void FUN_00036e30(int ai_handle)
{
  char *actor;

  actor = (char *)datum_get(actor_data, ai_handle);
  *(char *)(actor + 0x2ed) = 1;
}

/* FUN_00036e50 (0x36e50) — handle actor flight-duration countdown.
 *
 * If actor+0x358 (flight-active bool) is set AND the actor's actr tag field
 * at +0x334 exceeds the global zero constant (0x2533c0), clears the bool and:
 *   1. Converts (tag+0x334 * [0x253394]) to short → stores at actor+0x35a.
 *      (Ghidra shows _ftol2 call; disassembly: FLD [tag+0x334] / FMUL
 * [0x253394] / CALL _ftol2 at 0x36ea1-0x36ead.)
 *   2. If actor+0x270 (encounter handle) != -1:
 *        datum_get(0x5ab23c, encounter_handle) → encounter.
 *        If encounter+0x11c < [0x2533d8]:
 *          If actor+0x354 > [0x255154]:
 *            actor+0x354 = [0x255154]  (cap / floor to constant).
 *          Else:
 *            actor+0x354 = actor+0x354  (FPU precision normalize no-op).
 *
 * Confirmed: FLD [ECX+0x334] / FCOMP [0x2533c0] / FNSTSW / TEST AH,0x41 / JNZ
 * at 0x36e87-0x36e98; FLD [ECX+0x334] / FMUL [0x253394] / CALL 0x1d9068 at
 * 0x36ea1-0x36ead; CMP [ESI+0x270],-1 / JZ at 0x36ebf-0x36ec2; FLD/FCOMP/TEST
 * AH,0x5 / JP at 0x36ed0-0x36ee4; FLD/FCOMP/TEST AH,0x41/JNZ for the +0x354 cap
 * at 0x36ee6-0x36ef7. */
#ifdef __clang__
__attribute__((target("arch=i486")))
#endif
void FUN_00036e50(int actor_handle)
{
  char *actor;
  char *actor_tag;
  char *encounter;
  int encounter_handle;

  actor = (char *)datum_get(actor_data, actor_handle);
  actor_tag = (char *)tag_get(0x61637472, *(int *)(actor + 0x58));
  if (*(char *)(actor + 0x358) != 0 &&
      *(float *)(actor_tag + 0x334) > *(float *)0x2533c0) {
    *(char *)(actor + 0x358) = 0;
    *(short *)(actor + 0x35a) =
      (short)(*(float *)(actor_tag + 0x334) * TICKS_PER_SECOND);
    encounter_handle = *(int *)(actor + 0x270);
    if (encounter_handle != -1) {
      encounter = (char *)datum_get(*(data_t **)0x5ab23c, encounter_handle);
      if (*(float *)(encounter + 0x11c) < *(float *)0x2533d8) {
        if (*(float *)(actor + 0x354) > *(float *)0x255154) {
          float tmp;
          tmp = *(float *)(actor + 0x354);
          *(volatile float *)(actor + 0x354) = tmp;
        } else {
          *(float *)(actor + 0x354) = *(float *)0x255154;
        }
      }
    }
  }
}

/* FUN_00036f20 (0x36f20) — XBE naked draft (batch 69). */
#if defined(__clang__)
static void *(*const b36f20_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void *(*const b36f20_tag)(int, int) = tag_get;
static int (*const b36f20_c27a60)(int actor_handle, short look_type, short priority, short *look_buf) = FUN_00027a60;
static const char * (*const b36f20_c3a760)(int16_t actor_type) = FUN_0003a760;
static void (*const b36f20_cff4d0)(int channel, const char *format, ...) = console_printf;
static void (*const b36f20_c36960)(int actor_handle, short priority, int param3, int *direction) = FUN_00036960;
static void (*const b36f20_c46f10)(int16_t type, int unit_handle, int param3, int param4, int16_t param5, int16_t param6, int16_t param7) = FUN_00046f10;
static void (*const b36f20_c3cf10)(int actor_handle, char by_player, char no_delete) = actor_kill;

__attribute__((naked, noinline))
void FUN_00036f20(int actor_handle __attribute__((unused)), int prop_handle __attribute__((unused)), int param_3 __attribute__((unused)), char param_4 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x38, %%esp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl 0x6325a4, %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl 0x58(%%ebx), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x61637472\n\t"
      "movl %%ebx, -0x18(%%ebp)\n\t"
      "call *%[tag]\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "movl 0x5ab23c, %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%esi\n\t"
      "movb 0x127(%%esi), %%al\n\t"
      "addl $0x18, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00036f20_17\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "leal -0x28(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $1\n\t"
      "pushl $4\n\t"
      "pushl %%edx\n\t"
      "movw $1, -0x28(%%ebp)\n\t"
      "movl %%edi, -0x24(%%ebp)\n\t"
      "call *%[c27a60]\n\t"
      "movb 0x60(%%esi), %%al\n\t"
      "addl $0x10, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00036f20_17\n\t"
      "flds 0xe8(%%esi)\n\t"
      "xorl %%edi, %%edi\n\t"
      "fmuls 0x17c(%%ebx)\n\t"
      "flds 0xe4(%%esi)\n\t"
      "fmuls 0x178(%%ebx)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds 0xe0(%%esi)\n\t"
      "fmuls 0x174(%%ebx)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fcomps 0x253398\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00036f20_1\n\t"
      "movb $1, %%dl\n\t"
      "jmp .LFUN_00036f20_2\n\t"
      ".LFUN_00036f20_1:\n\t"
      "xorb %%dl, %%dl\n\t"
      ".LFUN_00036f20_2:\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x6e(%%ebx), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "jne .LFUN_00036f20_4\n\t"
      "cmpw $3, 0x6a(%%ebx)\n\t"
      "movb %%al, 0x14(%%ebp)\n\t"
      "jge .LFUN_00036f20_6\n\t"
      "movb 0x12f(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00036f20_3\n\t"
      "movl $1, %%edi\n\t"
      ".LFUN_00036f20_3:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "flds 0x11c(%%esi)\n\t"
      "fcomps 0x2b0(%%eax)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00036f20_6\n\t"
      "cmpw $3, %%di\n\t"
      "jg .LFUN_00036f20_6\n\t"
      "movl $3, %%edi\n\t"
      "jmp .LFUN_00036f20_6\n\t"
      ".LFUN_00036f20_4:\n\t"
      "cmpw $5, %%ax\n\t"
      "jl .LFUN_00036f20_5\n\t"
      "testb %%dl, %%dl\n\t"
      "jne .LFUN_00036f20_5\n\t"
      "movb $1, 0x14(%%ebp)\n\t"
      "jmp .LFUN_00036f20_8\n\t"
      ".LFUN_00036f20_5:\n\t"
      "movb 0x14(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00036f20_8\n\t"
      ".LFUN_00036f20_6:\n\t"
      "movb 0x12f(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00036f20_8\n\t"
      "flds 0x11c(%%esi)\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "fcomps 0x2b0(%%ecx)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00036f20_8\n\t"
      "testb %%dl, %%dl\n\t"
      "je .LFUN_00036f20_7\n\t"
      "cmpw $7, %%di\n\t"
      "jg .LFUN_00036f20_8\n\t"
      "movl $7, %%edi\n\t"
      "jmp .LFUN_00036f20_8\n\t"
      ".LFUN_00036f20_7:\n\t"
      "cmpw $6, %%di\n\t"
      "jg .LFUN_00036f20_8\n\t"
      "movl $6, %%edi\n\t"
      ".LFUN_00036f20_8:\n\t"
      "movb 0x5aca5a, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00036f20_15\n\t"
      "movb 0x12e(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00036f20_15\n\t"
      "flds 0x11c(%%esi)\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "fcomps 0x2b0(%%ecx)\n\t"
      "movl $0x254384, -0x38(%%ebp)\n\t"
      "movl $0x2567d0, -0x34(%%ebp)\n\t"
      "movl $0x2551cc, -0x30(%%ebp)\n\t"
      "movl $0x2567c4, -0x2c(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "movl $0x2567bc, -0x28(%%ebp)\n\t"
      "movl $0x255180, -0x24(%%ebp)\n\t"
      "testb $5, %%ah\n\t"
      "movl $0x2567a8, -0x20(%%ebp)\n\t"
      "movl $0x256794, -0x1c(%%ebp)\n\t"
      "movl $0x3c, -0x8(%%ebp)\n\t"
      "jnp .LFUN_00036f20_9\n\t"
      "movl $0x3e, -0x8(%%ebp)\n\t"
      ".LFUN_00036f20_9:\n\t"
      "flds 0x11c(%%esi)\n\t"
      "movl $0x25678c, -0xc(%%ebp)\n\t"
      "fcomps 0x2b0(%%ecx)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .LFUN_00036f20_10\n\t"
      "movl $0x256788, -0xc(%%ebp)\n\t"
      ".LFUN_00036f20_10:\n\t"
      "movb 0x12f(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "movl $0x25386f, %%ecx\n\t"
      "movl %%ecx, -0x10(%%ebp)\n\t"
      "jne .LFUN_00036f20_11\n\t"
      "movl $0x256784, -0x10(%%ebp)\n\t"
      ".LFUN_00036f20_11:\n\t"
      "testb %%dl, %%dl\n\t"
      "movl $0x25677c, %%edx\n\t"
      "jne .LFUN_00036f20_12\n\t"
      "movl $0x256774, %%edx\n\t"
      ".LFUN_00036f20_12:\n\t"
      "movb 0x14(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00036f20_13\n\t"
      "movl $0x253e94, %%ecx\n\t"
      ".LFUN_00036f20_13:\n\t"
      "cmpw $0, -0x14(%%ebp)\n\t"
      "movl $0x25676c, %%eax\n\t"
      "je .LFUN_00036f20_14\n\t"
      "movl $0x253b24, %%eax\n\t"
      ".LFUN_00036f20_14:\n\t"
      "movl -0x4(%%ebp), %%ebx\n\t"
      "flds 0x2b0(%%ebx)\n\t"
      "movl -0x8(%%ebp), %%ebx\n\t"
      "subl $8, %%esp\n\t"
      "fstpl (%%esp)\n\t"
      "pushl %%ebx\n\t"
      "flds 0x11c(%%esi)\n\t"
      "movl -0xc(%%ebp), %%ebx\n\t"
      "subl $8, %%esp\n\t"
      "fstpl (%%esp)\n\t"
      "pushl %%ebx\n\t"
      "movl -0x10(%%ebp), %%ebx\n\t"
      "pushl %%ebx\n\t"
      "movl -0x18(%%ebp), %%ebx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ecx\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "pushl %%eax\n\t"
      "movswl %%di, %%edx\n\t"
      "movl -0x38(%%ebp,%%edx,4), %%eax\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x4(%%ebx), %%dx\n\t"
      "pushl %%eax\n\t"
      "andl $0xffff, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c3a760]\n\t"
      "addl $4, %%esp\n\t"
      "pushl %%eax\n\t"
      "pushl $0x256734\n\t"
      "pushl $0\n\t"
      "call *%[cff4d0]\n\t"
      "addl $0x3c, %%esp\n\t"
      ".LFUN_00036f20_15:\n\t"
      "testw %%di, %%di\n\t"
      "jle .LFUN_00036f20_16\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "leal 0xe0(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "call *%[c36960]\n\t"
      "addl $0x10, %%esp\n\t"
      ".LFUN_00036f20_16:\n\t"
      "cmpw $3, 0x6e(%%ebx)\n\t"
      "jge .LFUN_00036f20_17\n\t"
      "movb 0x14(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00036f20_17\n\t"
      "cmpw $2, 0x32(%%esi)\n\t"
      "jge .LFUN_00036f20_17\n\t"
      "movl 0x18(%%ebx), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_00036f20_17\n\t"
      "movl 0x18(%%esi), %%edx\n\t"
      "pushl $0\n\t"
      "pushl $-1\n\t"
      "pushl $-1\n\t"
      "pushl $3\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl $6\n\t"
      "call *%[c46f10]\n\t"
      "addl $0x1c, %%esp\n\t"
      ".LFUN_00036f20_17:\n\t"
      "movb 0x12e(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00036f20_18\n\t"
      "movb 0x60(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00036f20_18\n\t"
      "movb 0x127(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00036f20_18\n\t"
      "cmpw $0xf, 0x4(%%ebx)\n\t"
      "je .LFUN_00036f20_18\n\t"
      "movb 0x5aa896, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00036f20_18\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl $1\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "call *%[c3cf10]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_00036f20_18:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [dget] "m"(b36f20_dget), [tag] "m"(b36f20_tag), [c27a60] "m"(b36f20_c27a60), [c3a760] "m"(b36f20_c3a760), [cff4d0] "m"(b36f20_cff4d0), [c36960] "m"(b36f20_c36960), [c46f10] "m"(b36f20_c46f10), [c3cf10] "m"(b36f20_c3cf10)
      : "memory");
}
#else
#error "FUN_00036f20: clang naked draft required"
#endif


/* FUN_00037240 (0x37240) — post prop or direction stimulus to an actor.
 *
 * If prop_handle != -1, resolves the prop datum (asserts type in [2,3]),
 * sets position_b = prop+0xe0. Otherwise if position is non-NULL and its
 * magnitude > 0x25337c, normalizes (scaled by [0x255e94]) to local_dir and
 * sets position_b = local_dir, has_direction = 1.
 * Always sets actor+0x2ec = 1.
 * If (no prop OR prop+0x60 != 0) AND actor+0x6a < 3:
 *   calls FUN_00036960(actor, 5, prop_handle, position_b)
 *   calls FUN_00036890(actor, NULL, 5, position_b,
 * -1,0,0x5a,prop_handle,0x96,0) Then builds a type-1 (prop) or type-4
 * (direction) look buf and calls FUN_00027a60(actor, 0xb, 1, buf). Source:
 * c:\halo\SOURCE\ai\actor_stimulus.c line ~0x154. */
void FUN_00037240(int actor_handle, int prop_handle, int unused_param_3,
                  float *position)
{
  char *actor;
  char *prop;
  int *position_b;
  float dot;
  float inv_len;
  float local_dir[3];
  short local_buf[8];
  char has_direction;

  actor = (char *)datum_get(actor_data, actor_handle);
  position_b = NULL;
  prop = NULL;
  has_direction = 0;

  if (prop_handle != -1) {
    prop = (char *)datum_get(prop_data, prop_handle);
    if (*(short *)(prop + 0x24) < 2 || *(short *)(prop + 0x24) > 3) {
      display_assert("prop_acknowledged(prop)",
                     "c:\\halo\\SOURCE\\ai\\actor_stimulus.c", 0x154, 1);
      system_exit(-1);
    }
    position_b = (int *)(prop + 0xe0);
  } else {
    if (position != NULL) {
      dot = position[0] * position[0] + position[1] * position[1] +
            position[2] * position[2];
      if (*(float *)0x25337c < dot) {
        inv_len = *(float *)0x255e94 / sqrtf(dot);
        local_dir[0] = inv_len * position[0];
        local_dir[1] = inv_len * position[1];
        local_dir[2] = inv_len * position[2];
        position_b = (int *)local_dir;
        has_direction = 1;
      }
    }
  }

  *(char *)(actor + 0x2ec) = 1;

  if ((prop == NULL || *(char *)(prop + 0x60) != 0) &&
      *(short *)(actor + 0x6a) < 3) {
    FUN_00036960(actor_handle, 5, prop_handle, position_b);
    FUN_00036890(actor_handle, NULL, 5, position_b, -1, 0, 0x5a, prop_handle,
                 0x96, 0);
  }

  if (prop_handle != -1) {
    local_buf[0] = 1;
    *(int *)((char *)local_buf + 4) = prop_handle;
  } else {
    if (!has_direction)
      return;
    local_buf[0] = 4;
    *(unsigned int *)((char *)local_buf + 4) = *(unsigned int *)&local_dir[0];
    *(unsigned int *)((char *)local_buf + 8) = *(unsigned int *)&local_dir[1];
    *(unsigned int *)((char *)local_buf + 12) = *(unsigned int *)&local_dir[2];
  }

  FUN_00027a60(actor_handle, 0xb, 1, local_buf);
}

/* FUN_000373b0 (0x373b0) — charge effect dispatch (audible AI broadcast).
 *
 * Dispatched from actors_handle_spatial_effect with effect_type=1 (charge) when
 * an actor is audible to a broadcast source. Resolves the actor record via
 * datum_get(actor_data, actor_handle) and the actor's type definition via
 * tag_get('actr', actor->actv_index@0x58).
 *
 * Behavior split:
 *   1) If the actor is already in a charge state with a matching target
 *      object_handle (actor[0x280] > 0 && actor[0x28c] == object_handle &&
 *      actor[0x284] > 0), forward the event as command type 10 via
 *      ai_communication (FUN_00046f10) on the actor's unit (actor+0x18),
 *      with five trailing -1 placeholders and a trailing 0 byte.
 *
 *   2) Otherwise, build delta = (broadcast_position - actor_position@0x120).
 *      Run normalize3d (normalize3d); if the resulting length magnitude is
 *      below the epsilon double at 0x002533d0 (~1e-4) — i.e. the actor is
 *      essentially on top of the broadcast — the direction is replaced
 *      with the actor's facing vector at actor+0x174..0x17c.
 *
 *      If the actor's state field (actor+0x6a) is below 3 AND the length is
 *      below the actor-type charge range (actr_def+0x2b0), post a look at
 *      direction via FUN_00036960 (look_type=2, priority -1).
 *
 *      Then unconditionally drive the charge command via FUN_00036890
 *      (actor_handle@<eax>, NULL@<ecx>, 3@<edx> as a short, &direction@<ebx>,
 *      followed by stack args -1, 0, 0x5a, -1, 0, 0).
 *
 * Finally, write a 16-byte look_buf { word 3, float pos[3] } from the raw
 * broadcast position and dispatch it as a look directive via
 * FUN_00027a60(actor_handle, 3, 1, look_buf) — look_type=3, priority=1.
 *
 * Confirmed: ADD ESP,0x10 cleans datum_get(2) + tag_get(2). Tag id 'actr'.
 * Confirmed: 4-arg cdecl signature at caller (actors_handle_spatial_effect
 * dispatch). Confirmed: FUN_00036890 register-arg order EAX/ECX/EDX/EBX from
 *   LEA EBX,[EBP-0xc]; XOR ECX,ECX; MOV EDX,0x3; MOV EAX,EDI.
 * Confirmed: FUN_00036890 callee reads DI from DX (low 16 bits are the
 *   priority short).
 * Confirmed: small-delta override copies actor+0x174..0x17c (vec3) via three
 *   MOV reg reg pairs into local_10 at the same offsets.
 * Confirmed: FCOMP [0x2533d0] is double-precision epsilon (~1e-4) against
 *   |normalize3d result|; FSTP ST0 fall-through cleans FPU when state>=3.
 * Inferred: parameter names — count is unused here (per FUN_00036c00
 *   sibling); object_handle gates the early-return communication branch.
 */
void FUN_000373b0(int actor_handle, int object_handle, float *position,
                  short count)
{
  char *actor;
  char *actr_def;
  int unit_handle;
  float length;
  float direction[3]; /* EBP-0xc..EBP-0x4 */
  short look_buf[8]; /* 16 bytes: EBP-0x10..EBP-0x1; word[0]=type, [2..7]=pos */

  (void)count;

  actor = (char *)datum_get(actor_data, actor_handle);
  actr_def = (char *)tag_get(0x61637472 /* 'actr' */, *(int *)(actor + 0x58));
  if (*(short *)(actor + 0x280) > 0 &&
      *(int *)(actor + 0x28c) == object_handle &&
      *(short *)(actor + 0x284) > 0) {
    unit_handle = *(int *)(actor + 0x18);
    FUN_00046f10(10, unit_handle, -1, -1, -1, -1, 0);
  } else {
    direction[0] = position[0] - *(float *)(actor + 0x120);
    direction[1] = position[1] - *(float *)(actor + 0x124);
    direction[2] = position[2] - *(float *)(actor + 0x128);
    length = normalize3d(direction);
    if (length < 0.0001f && length > -0.0001f) {
      direction[0] = *(float *)(actor + 0x174);
      direction[1] = *(float *)(actor + 0x178);
      direction[2] = *(float *)(actor + 0x17c);
    }
    if (*(short *)(actor + 0x6a) < 3) {
      if (length < *(float *)(actr_def + 0x2b0)) {
        FUN_00036960(actor_handle, 2, -1, (int *)direction);
      }
    }
    FUN_00036890(actor_handle, (int *)0, 3, (int *)direction, -1, 0, 0x5a, -1,
                 0, 0);
  }

  look_buf[0] = 3;
  *(float *)&look_buf[2] = position[0];
  *(float *)&look_buf[4] = position[1];
  *(float *)&look_buf[6] = position[2];
  FUN_00027a60(actor_handle, 3, 1, look_buf);
}

/* FUN_000374f0 (0x374f0) — cover/take-cover look reaction.
 *
 * Resolves the actor record via datum_get(actor_data, actor_handle) and
 * the actor type tag via tag_get('actr', actor+0x58). Computes the delta
 * from the actor's world position (actor+0x120 vec3) to the input
 * position; if the resulting magnitude is < (float)*(double *)0x2533d0
 * (epsilon), substitutes the actor's facing vector (actor+0x174) for the
 * delta. If the actor's state field (actor+0x6a) is < 3 AND the magnitude
 * is < tag+0x2b0 (range float), posts a priority-4 stimulus via
 * FUN_00036960(actor_handle, 4, -1, &delta). Then unconditionally posts
 * a priority-3 alert stimulus via FUN_00036890 with NULL primary vector,
 * the delta as the secondary vector, and stack args (-1, 0, 0x5a, -1, 0,
 * 0 byte). If object_handle != -1, resolves the object's type via
 * object_get_and_verify_type(object_handle, -1) and checks team
 * friendliness via game_allegiance_get_team_is_friendly(actor+0x3e,
 * obj+0x68); when friendly, posts FUN_000369c0(actor_handle, 2, 900).
 * Finally posts a position-look at priority-1, look_type=6 with the
 * original input position via FUN_00027a60.
 *
 * Confirmed: 4 cdecl args matching dispatch in actors_handle_spatial_effect;
 * ESP cleanup ADD ESP,0x14 after datum_get+tag_get; ADD ESP,0x10 after
 * FUN_00036960; ADD ESP,0x18 after FUN_00036890; ADD ESP,0x10 after
 * game_allegiance_get_team_is_friendly; ADD ESP,0xc after FUN_000369c0; ADD ESP,0x10 after
 * FUN_00027a60. Confirmed: FUN_00036890 reg ABI — @ecx=vec1, @eax=actor,
 * @edx=priority,
 *   @ebx=vec2; verified against sibling FUN_000373b0 call site at 0x374b4.
 * Confirmed: epsilon constant at 0x2533d0 (double, ~0.0001).
 * Confirmed: look_buf layout — short type at +0x00, then float pos[3] at
 *   +0x04; matches FUN_00036c00 look_buf shape. */
void FUN_000374f0(int actor_handle, int object_handle, float *position,
                  short count)
{
  char *actor;
  char *actor_tag;
  char *object;
  float delta[3];
  float mag;
  short look_buf[8]; /* 16 bytes: [0]=type word, [2..7]=position data */

  (void)count;

  actor = (char *)datum_get(actor_data, actor_handle);
  actor_tag = (char *)tag_get(0x61637472, *(int *)(actor + 0x58));
  delta[0] = position[0] - *(float *)(actor + 0x120);
  delta[1] = position[1] - *(float *)(actor + 0x124);
  delta[2] = position[2] - *(float *)(actor + 0x128);
  mag = normalize3d(delta);
  if (mag < (float)*(double *)0x2533d0) {
    delta[0] = *(float *)(actor + 0x174);
    delta[1] = *(float *)(actor + 0x178);
    delta[2] = *(float *)(actor + 0x17c);
  }
  if (*(short *)(actor + 0x6a) < 3 && mag < *(float *)(actor_tag + 0x2b0)) {
    FUN_00036960(actor_handle, 4, -1, (int *)delta);
  }
  FUN_00036890(actor_handle, (int *)0, 3, (int *)delta, -1, 0, 0x5a, -1, 0, 0);
  if (object_handle != -1) {
    object = (char *)object_get_and_verify_type(object_handle, -1);
    if (game_allegiance_get_team_is_friendly(*(short *)(actor + 0x3e),
                                             *(short *)(object + 0x68))) {
      FUN_000369c0(actor_handle, 2, 900);
    }
  }
  look_buf[0] = 3;
  *(float *)&look_buf[2] = position[0];
  *(float *)&look_buf[4] = position[1];
  *(float *)&look_buf[6] = position[2];
  FUN_00027a60(actor_handle, 6, 1, look_buf);
}

/* FUN_00037630 (0x37630) — actor surprise-encounter update.
 *
 * Marks actor field_0x8d = 1. Bails if prop is "active" (field_0x60 != 0).
 * Re-fetches actor + tag. Calls actor_perception_find_killer_prop_index to
 * find the associated killer prop handle. If prop->field_10 matches the tag's
 * field_0x2a4 (encounter threshold) and actor's emotion priority < 8, does a
 * random roll vs tag->field_0x2a8 and sets priority to 8.
 *
 * Then checks the killer prop: if out of range (prop->field_11c >= global
 * 0x253f78), or no killer prop (handle==-1), or killer not active
 * (killer_prop->field_60 == 0): bail.
 *
 * If killer_prop->field_32 > 0 and field_122 <= 2: optionally gates via
 * game_time_get() > actor->field_39c + tag bit5, then calls FUN_00030d10
 * (chance scaler). Falls back to a random roll vs the (possibly scaled)
 * chance. On success, sets emotion priority to 3 with killer prop handle.
 *
 * Always checks killer_prop->field_a4; if set, increments field_a6 and
 * sets field_a8 = 0x2ee. */
void FUN_00037630(int actor_handle, int prop_handle)
{
  char *actor;
  char *prop;
  char *tag;
  int killer_handle;
  float chance;

  actor = (char *)datum_get(actor_data, actor_handle);
  prop = (char *)datum_get(prop_data, prop_handle);
  *(char *)(actor + 0x8d) = 1;
  if (*(char *)(prop + 0x60) != 0)
    return;

  actor = (char *)datum_get(actor_data, actor_handle);
  tag = (char *)tag_get(0x61637472, *(int *)(actor + 0x58));
  killer_handle =
    actor_perception_find_killer_prop_index(actor_handle, prop_handle, 1);

  if (*(int16_t *)(prop + 0x10) == *(int16_t *)(tag + 0x2a4) &&
      *(int16_t *)(actor + 0x308) < 8) {
    if (random_math_real((unsigned int *)get_global_random_seed_address()) <
        *(float *)(tag + 0x2a8)) {
      *(int16_t *)(actor + 0x308) = 8;
      *(int *)(actor + 0x30c) = killer_handle;
    }
  }

  if (*(float *)(prop + 0x11c) >= *(float *)0x253f78)
    return;
  if (killer_handle == -1)
    return;

  prop = (char *)datum_get(prop_data, killer_handle);
  if (*(char *)(prop + 0x60) == 0)
    return;

  if (*(int16_t *)(prop + 0x32) > 0 && *(char *)(prop + 0x122) <= 2) {
    chance = *(float *)(tag + 0x2a0);
    if ((*(unsigned char *)(tag + 4) & 0x20) &&
        game_time_get() > *(int *)(actor + 0x39c)) {
      if (FUN_00030d10(actor_handle, &chance))
        goto set_alert;
    }
    if (chance <=
        random_math_real((unsigned int *)get_global_random_seed_address()))
      goto lab_a2;
  set_alert:
    if (*(int16_t *)(actor + 0x308) < 3) {
      *(int16_t *)(actor + 0x308) = 3;
      *(int *)(actor + 0x30c) = killer_handle;
    }
  }
lab_a2:
  if (*(char *)(prop + 0xa4) != 0) {
    *(int16_t *)(prop + 0xa6) += 1;
    *(int16_t *)(prop + 0xa8) = 0x2ee;
  }
}

/* FUN_000377d0 (0x377d0) — actor reaction to a flee-effect from a prop.
 *
 * Case-4 handler from FUN_0003c1c0 (effect dispatch). Given an actor handle
 * (param_1) and a prop handle (param_2), checks whether the actor's tag
 * permits this reaction (actor_tag+0x4 bit 5) and that the prop has not been
 * consumed (prop+0x60 == 0). If still in cooldown (game_time_get() <=
 * actor+0x39c), bail. Computes a chance roll via FUN_00030d10 which may
 * scale the per-tag chance (actor_tag+0x2a0) in-place; if it returns false,
 * roll a random float and bail when random >= scaled_chance. If the actor's
 * current emotion priority at +0x308 is below 3, set the new emotion to 2
 * with payload = either *(actor+0x270) or, when the prop's linked actor
 * (prop+0x1c) is itself a vehicle (+0x6c == 4) with a valid prop
 * (+0xb8 != -1), the prop_get_active_by_unit_index lookup on that vehicle.
 * Skips the write entirely when prop+0x1c == -1.
 *
 * Confirmed: cdecl(actor_handle, prop_handle); pushes at 0x377d4/0x377ff.
 * Confirmed: datum_get(actor_data, param_1) -> ESI; tag_get('actr',
 *   actor+0x58) -> EBX (actor_tag); datum_get(prop_data, param_2) -> EDI.
 * Confirmed: TEST byte [EBX+4],0x20 (0x37819); CMP EAX,[ESI+0x39c] after
 *   game_time_get (0x37828).
 * Confirmed: FUN_00030d10(actor_handle, &local_8) cdecl, local_8 seeded
 *   with *(actor_tag+0x2a0).
 * Confirmed: FCOMP [EBP-4]; FNSTSW AX; TEST AH,5; JP -> ret when
 *   random >= local_8 (continues only when random < local_8).
 * Confirmed: CMP word [ESI+0x308],3; JGE skip-write at 0x37871.
 * Confirmed: MOV EBX,[ESI+0x270] BEFORE the prop+0x1c == -1 check
 *   (0x37879); JZ at 0x3787f returns without writing when prop+0x1c == -1.
 * Confirmed: nested datum_get(actor_data, prop+0x1c); CMP word [EAX+0x6c],4
 *   then CMP [EAX+0xb8],-1; datum_get(prop_data, EAX+0xb8); push
 *   *(other_prop+0x18) then actor_handle to prop_get_active_by_unit_index
 *   (prop_get_active_by_unit_index).
 * Confirmed: writes word 2 at ESI+0x308 and dword EBX at ESI+0x30c. */
void FUN_000377d0(int actor_handle, int prop_handle)
{
  char *actor;
  char *actor_tag;
  char *prop;
  char *other_actor;
  char *other_prop;
  int new_payload;
  int other_actor_handle;
  float chance;
  char preempt;

  actor = (char *)datum_get(actor_data, actor_handle);
  actor_tag = (char *)tag_get(0x61637472, *(int *)(actor + 0x58));
  prop = (char *)datum_get(prop_data, prop_handle);
  if (*(char *)(prop + 0x60) != 0)
    return;
  if ((*(unsigned char *)(actor_tag + 4) & 0x20) == 0)
    return;
  if (game_time_get() <= *(int *)(actor + 0x39c))
    return;

  chance = *(float *)(actor_tag + 0x2a0);
  preempt = (char)FUN_00030d10(actor_handle, &chance);
  if (preempt == 0) {
    if (chance <=
        random_math_real((unsigned int *)get_global_random_seed_address())) {
      return;
    }
  }

  if (*(int16_t *)(actor + 0x308) >= 3)
    return;

  other_actor_handle = *(int *)(prop + 0x1c);
  new_payload = *(int *)(actor + 0x270);
  if (other_actor_handle == -1)
    return;

  other_actor = (char *)datum_get(actor_data, other_actor_handle);
  if (*(int16_t *)(other_actor + 0x6c) == 4 &&
      *(int *)(other_actor + 0xb8) != -1) {
    other_prop = (char *)datum_get(prop_data, *(int *)(other_actor + 0xb8));
    new_payload =
      prop_get_active_by_unit_index(actor_handle, *(int *)(other_prop + 0x18));
  }
  *(int16_t *)(actor + 0x308) = 2;
  *(int *)(actor + 0x30c) = new_payload;
}

/* FUN_000378e0 (0x378e0) — actor prop-reaction: impact/projectile look.
 *
 * If actor has a linked unit (actor+0x18 != -1):
 *   - When param_2 == 2: maps param_3 (0→3, 1→2, 2→1, else -1) to a
 *     communication type and broadcasts via FUN_00046f10(0xb, unit, -1,
 *     type, -1, -1, 0).
 *   - Computes delta from param_5 (position) to actor world position
 *     (actor+0x120), normalizes it via normalize3d.
 *   - If state < 3 AND magnitude < tag->field_0x2b0 AND param_2 == 2:
 *     posts a priority-4 alert stimulus via FUN_00036960.
 *   - Always posts FUN_00036890 with priority 4, delta as secondary
 *     vector, and stack args (-1, 0, 0, -1, 0, 0).
 * param_4 is unused (dispatch table padding). */
void FUN_000378e0(int actor_handle, short param_2, short param_3, int param_4,
                  float *param_5)
{
  char *actor;
  char *tag;
  float delta[3];
  float mag;
  int unit_handle;
  int type;

  (void)param_4;

  actor = (char *)datum_get(actor_data, actor_handle);
  tag = (char *)tag_get(0x61637472, *(int *)(actor + 0x58));
  unit_handle = *(int *)(actor + 0x18);
  if (unit_handle == -1)
    return;

  if (param_2 == 2) {
    type = -1;
    if (param_3 == 0)
      type = 3;
    else if (param_3 == 1)
      type = 2;
    else if (param_3 == 2)
      type = 1;
    FUN_00046f10(0xb, unit_handle, -1, type, -1, -1, 0);
  }

  delta[0] = param_5[0] - *(float *)(actor + 0x120);
  delta[1] = param_5[1] - *(float *)(actor + 0x124);
  delta[2] = param_5[2] - *(float *)(actor + 0x128);
  mag = normalize3d(delta);
  if (*(short *)(actor + 0x6a) < 3 && mag < *(float *)(tag + 0x2b0) &&
      param_2 == 2) {
    FUN_00036960(actor_handle, 4, -1, (int *)delta);
  }
  FUN_00036890(actor_handle, NULL, 4, (int *)delta, -1, 0, 0, -1, 0, 0);
}

/* FUN_000379f0 (0x379f0) — actor action state-machine tick (basic).
 *
 * A lighter variant of FUN_00038b10. Calls the standard action preamble
 * (initial_action, pending_command_list, surprise with type 4), then if
 * actor_action_deny_transition returns false, runs the berserking helpers and
 * combat transition. After that, dispatches per-state behavior based on
 * *(short *)(actor + 0x6c):
 *
 *   3, 10: handle_combat_status(actor, 1, 0). If both that and
 *          handle_combat_failure return false, call handle_evasion and return.
 *   4:     If actor+0xaa, handle_combat_status(actor, 1, 1) and return.
 *          Else handle_done_fleeing and return.
 *   5,7,8: handle_combat_status(actor, 1, 0). If false, handle_exit_pursuit.
 *   6:     can_stop_guarding(actor,3,6,0) result → handle_combat_status(actor,
 *          result, actor_handle [MSVC batch-cleanup residue]).
 *   0xb:   handle_combat_status(actor, actor+0x9e, actor+0xa1).
 *
 * Confirmed: tag_get(0x61637472, actor+0x58) called but result unused (cache
 * warm); SUB not needed; batch ADD ESP,0x24 covers datum_get×2+calls at
 * 0x37a2e; MOVSX EAX,word[EDI+0x6c] / ADD -3 / CMP 8 / JA → switch table at
 * 0x37a58-0x37a68; case 6 uses push-residue 3rd arg (actor_handle) at
 * 0x37aa2-0x37ab8. */
void FUN_000379f0(int actor_handle)
{
  char *actor;
  char cVar1;
  int uVar3;

  actor = (char *)datum_get(actor_data, actor_handle);
  (void)tag_get(0x61637472, *(int *)(actor + 0x58));
  actor_action_handle_initial_action(actor_handle);
  actor_action_handle_pending_command_list(actor_handle);
  actor_action_handle_surprise(actor_handle, 4);
  cVar1 = actor_action_deny_transition(actor_handle);
  if (cVar1 == '\0') {
    actor_action_handle_berserking_from_attacking_mode(actor_handle);
    actor_action_handle_berserking_from_damage(actor_handle);
    actor_action_handle_berserking_from_proximity(actor_handle);
    actor_action_handle_berserk_transition(actor_handle, 1);
    actor_action_handle_combat_transition(actor_handle);
  }
  switch (*(short *)(actor + 0x6c)) {
  case 3:
  case 10:
    cVar1 = actor_action_handle_combat_status(actor_handle, 1, 0);
    if (cVar1 == '\0' &&
        (cVar1 = actor_action_handle_combat_failure(actor_handle),
         cVar1 == '\0')) {
      actor_action_handle_evasion(actor_handle);
      return;
    }
    break;
  case 6:
    /* PUSH 0x0 at 0x37aa2 is pre-positioned residue for handle_combat_status
     * 3rd arg; actor_action_can_stop_guarding takes 3 args (ADD ESP,0xc at
     * 0x37aae cleans 3). */
    uVar3 = actor_action_can_stop_guarding(actor_handle, 3, 6);
    actor_action_handle_combat_status(actor_handle, uVar3, 0);
    return;
  case 4:
    if (*(char *)(actor + 0xaa) != '\0') {
      actor_action_handle_combat_status(actor_handle, 1, 1);
      return;
    }
    actor_action_handle_done_fleeing(actor_handle);
    return;
  case 5:
  case 7:
  case 8:
    cVar1 = actor_action_handle_combat_status(actor_handle, 1, 0);
    if (cVar1 == '\0') {
      actor_action_handle_exit_pursuit(actor_handle);
      return;
    }
    break;
  case 0xb:
    actor_action_handle_combat_status(actor_handle,
                                      *(unsigned char *)(actor + 0x9e),
                                      *(unsigned char *)(actor + 0xa1));
    break;
  }
}

/* FUN_00037b50 (0x37b50) — actor action state-machine tick (panic/surprise
 * variant).
 *
 * Sibling of FUN_00038000. Preamble: datum_get, handle_initial_action,
 * handle_pending_command_list, handle_surprise(1), deny_transition check.
 * If deny=false: panic helpers including panic_from_surprise (absent from
 * FUN_00038000), panic_transition(1,0,9), combat_transition, FUN_00020990
 * (no grenade_throwing). Switch identical to FUN_00038000. */
void FUN_00037b50(int actor_handle)
{
  char *actor;
  char cVar1;
  int uVar3;
  unsigned char bVar1;
  unsigned char bVar2;

  actor = (char *)datum_get(actor_data, actor_handle);
  actor_action_handle_initial_action(actor_handle);
  actor_action_handle_pending_command_list(actor_handle);
  actor_action_handle_surprise(actor_handle, 1);
  cVar1 = actor_action_deny_transition(actor_handle);
  if (cVar1 == '\0') {
    actor_action_handle_panic_from_surprise(actor_handle);
    actor_action_handle_panic_from_damage(actor_handle);
    actor_action_handle_panic_from_attached_projectiles(actor_handle);
    actor_action_handle_panic_from_attached_melee_attackers(actor_handle);
    actor_action_handle_panic_from_burning_to_death(actor_handle);
    actor_action_handle_panic_transition(actor_handle, 1, 0, 9);
    actor_action_handle_combat_transition(actor_handle);
    FUN_00020990(actor_handle);
  }
  switch (*(short *)(actor + 0x6c)) {
  case 3:
  case 10:
    cVar1 = actor_action_handle_combat_status(actor_handle, 1, 0);
    if (cVar1 != '\0') {
      return;
    }
    cVar1 = actor_action_handle_combat_failure(actor_handle);
    if (cVar1 != '\0') {
      return;
    }
    actor_action_handle_evasion(actor_handle);
    return;
  case 6:
    uVar3 = actor_action_can_stop_guarding(actor_handle, 3, 6);
    actor_action_handle_combat_status(actor_handle, uVar3, 0);
    return;
  case 4:
    if (*(char *)(actor + 0xaa) != '\0') {
      break;
    }
    actor_action_handle_done_fleeing(actor_handle);
    return;
  case 5:
  case 7:
  case 8:
    cVar1 = actor_action_handle_combat_status(actor_handle, 1, 0);
    if (cVar1 != '\0') {
      return;
    }
    actor_action_handle_exit_pursuit(actor_handle);
    return;
  case 9:
    if (*(char *)(actor + 0xa5) != '\0') {
      break;
    }
    if (*(char *)(actor + 0xa6) == '\0') {
      return;
    }
    actor_action_handle_combat_status(actor_handle, 1, 1);
    return;
  case 0xb:
    bVar2 = *(unsigned char *)(actor + 0x9e);
    bVar1 = *(unsigned char *)(actor + 0xa1);
    actor_action_handle_combat_status(actor_handle, bVar2, bVar1);
    return;
  case 0xc:
    if (*(char *)(actor + 0xa0) == '\0' && *(int *)(actor + 0x1dc) != -1) {
      uVar3 = actor_action_can_stop_conversing(actor_handle, 0);
      actor_action_handle_combat_status(actor_handle, uVar3, 0);
      return;
    }
    uVar3 = actor_action_can_stop_conversing(actor_handle, 1);
    actor_action_handle_combat_status(actor_handle, uVar3, 1);
    return;
  case 0xd:
    if (*(short *)(actor + 0x280) != 0) {
      return;
    }
    break;
  default:
    return;
  }
  actor_action_handle_combat_status(actor_handle, 1, 1);
}

/* FUN_00037d50 (0x37d50) — XBE naked draft (batch 69). */
#if defined(__clang__)
static void *(*const b37d50_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void *(*const b37d50_tag)(int, int) = tag_get;
static char (*const b37d50_c1dab0)(int actor_handle) = actor_action_handle_initial_action;
static char (*const b37d50_c1daf0)(int actor_handle) = actor_action_handle_pending_command_list;
static char (*const b37d50_c1db90)(int actor_handle, short type) = actor_action_handle_surprise;
static char (*const b37d50_c1ca90)(int actor_handle) = actor_action_deny_transition;
static char (*const b37d50_c1c8d0)(int actor_handle) = actor_action_handle_berserking_from_attacking_mode;
static char (*const b37d50_c1ca00)(int actor_handle) = actor_action_handle_berserking_from_damage;
static char (*const b37d50_c1c940)(int actor_handle) = actor_action_handle_berserking_from_proximity;
static char (*const b37d50_c1dea0)(int actor_handle) = actor_action_handle_combat_targeting;
static char (*const b37d50_c20470)(int actor_handle, short param_2) = actor_action_handle_berserk_transition;
static int (*const b37d50_c1c7f0)(int actor_handle) = actor_action_handle_panic_from_attached_projectiles;
static char (*const b37d50_c1c880)(int actor_handle) = actor_action_handle_panic_from_attached_melee_attackers;
static char (*const b37d50_c1dd40)(int actor_handle, short param_2, char param_3, short param_4) = actor_action_handle_panic_transition;
static char (*const b37d50_c204f0)(int actor_handle) = actor_action_handle_combat_transition;
static char (*const b37d50_c1e700)(int actor_handle, char param2, int param3) = actor_action_handle_active_cover_seeking;
static char (*const b37d50_c1dfa0)(int actor_handle) = actor_action_handle_vehicle_entry;
static char (*const b37d50_c1cb70)(int actor_handle) = actor_action_handle_vehicle_exit;
static char (*const b37d50_c205a0)(int actor_handle) = actor_action_handle_grenade_throwing;
static char (*const b37d50_c20990)(int actor_handle) = FUN_00020990;
static char (*const b37d50_c1f770)(int actor_handle, int param2, int param3) = actor_action_handle_combat_status;
static char (*const b37d50_c1f920)(int actor_handle) = actor_action_handle_combat_failure;
static char (*const b37d50_c20670)(int actor_handle) = actor_action_handle_evasion;
static char (*const b37d50_c1cf10)(int actor_handle, short min_state, short max_state) = actor_action_can_stop_guarding;
static char (*const b37d50_c1f6e0)(int actor_handle) = actor_action_handle_done_fleeing;
static char (*const b37d50_c1f9a0)(int actor_handle) = actor_action_handle_exit_pursuit;
static int (*const b37d50_c1cfa0)(int actor_handle, int flag) = actor_action_can_stop_conversing;

__attribute__((naked, noinline))
void FUN_00037d50(int actor_handle __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl 0x6325a4, %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%edi\n\t"
      "movl 0x58(%%edi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x61637472\n\t"
      "call *%[tag]\n\t"
      "pushl %%esi\n\t"
      "movl %%eax, %%ebx\n\t"
      "call *%[c1dab0]\n\t"
      "pushl %%esi\n\t"
      "call *%[c1daf0]\n\t"
      "pushl $4\n\t"
      "pushl %%esi\n\t"
      "call *%[c1db90]\n\t"
      "pushl %%esi\n\t"
      "call *%[c1ca90]\n\t"
      "addl $0x24, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00037d50_2\n\t"
      "pushl %%esi\n\t"
      "call *%[c1c8d0]\n\t"
      "pushl %%esi\n\t"
      "call *%[c1ca00]\n\t"
      "pushl %%esi\n\t"
      "call *%[c1c940]\n\t"
      "pushl %%esi\n\t"
      "call *%[c1dea0]\n\t"
      "pushl $1\n\t"
      "pushl %%esi\n\t"
      "call *%[c20470]\n\t"
      "movb 0x378(%%edi), %%al\n\t"
      "addl $0x18, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00037d50_1\n\t"
      "pushl %%esi\n\t"
      "call *%[c1c7f0]\n\t"
      "pushl %%esi\n\t"
      "call *%[c1c880]\n\t"
      "pushl $0xb\n\t"
      "pushl $0\n\t"
      "pushl $9\n\t"
      "pushl %%esi\n\t"
      "call *%[c1dd40]\n\t"
      "addl $0x18, %%esp\n\t"
      ".LFUN_00037d50_1:\n\t"
      "pushl %%esi\n\t"
      "call *%[c204f0]\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl %%esi\n\t"
      "call *%[c1e700]\n\t"
      "pushl %%esi\n\t"
      "call *%[c1dfa0]\n\t"
      "pushl %%esi\n\t"
      "call *%[c1cb70]\n\t"
      "pushl %%esi\n\t"
      "call *%[c205a0]\n\t"
      "pushl %%esi\n\t"
      "call *%[c20990]\n\t"
      "addl $0x20, %%esp\n\t"
      ".LFUN_00037d50_2:\n\t"
      "movswl 0x6c(%%edi), %%eax\n\t"
      "addl $-3, %%eax\n\t"
      "cmpl $0xa, %%eax\n\t"
      "ja .LFUN_00037d50_17\n\t"
      "jmp *.LFUN_00037d50_jt(,%%eax,4)\n\t"
      ".LFUN_00037d50_3:\n\t"
      "pushl $0\n\t"
      "pushl $1\n\t"
      "pushl %%esi\n\t"
      "call *%[c1f770]\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00037d50_17\n\t"
      "pushl %%esi\n\t"
      "call *%[c1f920]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00037d50_17\n\t"
      "pushl %%esi\n\t"
      "call *%[c20670]\n\t"
      "addl $4, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00037d50_4:\n\t"
      "movb 0xa4(%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00037d50_8\n\t"
      "movb 0xa5(%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00037d50_8\n\t"
      "movb 0xa6(%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00037d50_8\n\t"
      "cmpw $4, 0x6e(%%edi)\n\t"
      "jl .LFUN_00037d50_5\n\t"
      "flds 0x2e0(%%ebx)\n\t"
      "jmp .LFUN_00037d50_6\n\t"
      ".LFUN_00037d50_5:\n\t"
      "flds 0x2e4(%%ebx)\n\t"
      ".LFUN_00037d50_6:\n\t"
      "fcomps 0x1bc(%%edi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00037d50_7\n\t"
      "movb $1, 0xa4(%%edi)\n\t"
      "movw $0x1e, 0xa8(%%edi)\n\t"
      "jmp .LFUN_00037d50_8\n\t"
      ".LFUN_00037d50_7:\n\t"
      "movb $0, 0xa4(%%edi)\n\t"
      "movw $0, 0xa8(%%edi)\n\t"
      ".LFUN_00037d50_8:\n\t"
      "pushl $0\n\t"
      "pushl $6\n\t"
      "pushl $3\n\t"
      "pushl %%esi\n\t"
      "call *%[c1cf10]\n\t"
      "addl $0xc, %%esp\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[c1f770]\n\t"
      "addl $0xc, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00037d50_9:\n\t"
      "movb 0xaa(%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00037d50_16\n\t"
      "pushl %%esi\n\t"
      "call *%[c1f6e0]\n\t"
      "addl $4, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00037d50_10:\n\t"
      "pushl $0\n\t"
      "pushl $1\n\t"
      "pushl %%esi\n\t"
      "call *%[c1f770]\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00037d50_17\n\t"
      "pushl %%esi\n\t"
      "call *%[c1f9a0]\n\t"
      "addl $4, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00037d50_11:\n\t"
      "movb 0xa5(%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00037d50_16\n\t"
      "movb 0xa6(%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00037d50_17\n\t"
      "pushl $1\n\t"
      "pushl $1\n\t"
      "pushl %%esi\n\t"
      "call *%[c1f770]\n\t"
      "addl $0xc, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00037d50_12:\n\t"
      "xorl %%edx, %%edx\n\t"
      "movb 0xa1(%%edi), %%dl\n\t"
      "xorl %%eax, %%eax\n\t"
      "movb 0x9e(%%edi), %%al\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[c1f770]\n\t"
      "addl $0xc, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00037d50_13:\n\t"
      "movb 0xa0(%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00037d50_14\n\t"
      "cmpl $-1, 0x1dc(%%edi)\n\t"
      "je .LFUN_00037d50_14\n\t"
      "xorl %%eax, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[c1cfa0]\n\t"
      "addl $4, %%esp\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[c1f770]\n\t"
      "addl $0xc, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00037d50_14:\n\t"
      "movl $1, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[c1cfa0]\n\t"
      "addl $4, %%esp\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[c1f770]\n\t"
      "addl $0xc, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00037d50_15:\n\t"
      "cmpw $0, 0x280(%%edi)\n\t"
      "jne .LFUN_00037d50_17\n\t"
      ".LFUN_00037d50_16:\n\t"
      "pushl $1\n\t"
      "pushl $1\n\t"
      "pushl %%esi\n\t"
      "call *%[c1f770]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_00037d50_17:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_00037d50_jt:\n\t"
      ".long .LFUN_00037d50_3\n\t"
      ".long .LFUN_00037d50_9\n\t"
      ".long .LFUN_00037d50_10\n\t"
      ".long .LFUN_00037d50_4\n\t"
      ".long .LFUN_00037d50_10\n\t"
      ".long .LFUN_00037d50_10\n\t"
      ".long .LFUN_00037d50_11\n\t"
      ".long .LFUN_00037d50_3\n\t"
      ".long .LFUN_00037d50_12\n\t"
      ".long .LFUN_00037d50_13\n\t"
      ".long .LFUN_00037d50_15\n\t"
      ".text\n\t"
      :
      : [dget] "m"(b37d50_dget), [tag] "m"(b37d50_tag), [c1dab0] "m"(b37d50_c1dab0), [c1daf0] "m"(b37d50_c1daf0), [c1db90] "m"(b37d50_c1db90), [c1ca90] "m"(b37d50_c1ca90), [c1c8d0] "m"(b37d50_c1c8d0), [c1ca00] "m"(b37d50_c1ca00), [c1c940] "m"(b37d50_c1c940), [c1dea0] "m"(b37d50_c1dea0), [c20470] "m"(b37d50_c20470), [c1c7f0] "m"(b37d50_c1c7f0), [c1c880] "m"(b37d50_c1c880), [c1dd40] "m"(b37d50_c1dd40), [c204f0] "m"(b37d50_c204f0), [c1e700] "m"(b37d50_c1e700), [c1dfa0] "m"(b37d50_c1dfa0), [c1cb70] "m"(b37d50_c1cb70), [c205a0] "m"(b37d50_c205a0), [c20990] "m"(b37d50_c20990), [c1f770] "m"(b37d50_c1f770), [c1f920] "m"(b37d50_c1f920), [c20670] "m"(b37d50_c20670), [c1cf10] "m"(b37d50_c1cf10), [c1f6e0] "m"(b37d50_c1f6e0), [c1f9a0] "m"(b37d50_c1f9a0), [c1cfa0] "m"(b37d50_c1cfa0)
      : "memory");
}
#else
#error "FUN_00037d50: clang naked draft required"
#endif


/* FUN_00038000 (0x38000) — actor action state-machine tick (panic/ambush
 * variant).
 *
 * Sibling of FUN_000379f0 but with an expanded deny=false block (panic helpers
 * + grenade/evasion setup) and a wider switch covering states 3–0xd.  No
 * tag_get warm-up call (unlike FUN_000379f0).
 *
 * Preamble: datum_get, handle_initial_action, handle_pending_command_list,
 * handle_surprise(1), deny_transition check.  If deny=false: panic helpers
 * (from_damage, from_attached_projectiles, from_attached_melee_attackers,
 * from_burning_to_death), handle_panic_transition(1,0,9),
 * handle_combat_transition, handle_grenade_throwing, FUN_00020990.
 *
 * Switch physical layout (from jump table at 0x381c8, EAX=value-3):
 *   3,10 → 0x38087; 6 → 0x380ba; 4 → 0x380d7; 5,7,8 → 0x380f2;
 *   9 → 0x38114; 0xb → 0x38141; 0xc → 0x38160; 0xd → 0x381aa.
 * Shared tail at 0x381b4: handle_combat_status(actor_handle,1,1).
 *
 * Case 6: actor_action_can_stop_guarding(actor_handle,3,6,0) — 4 args
 *   (ADD ESP,0xc at 0x380c6 cleans 3; 4th arg 0 is PUSH residue
 * pre-positioned). Case 0xc: actor_action_can_stop_conversing(actor_handle,
 * flag) — batch-cleanup residue pattern (ADD ESP,0x4 cleans only flag; ESI
 * cleaned by later ADD ESP,0xc). Case 0xb: XOR+MOV pattern for unsigned byte
 * loads at actor+0xa1, actor+0x9e. Confirmed: disassembly 0x38000–0x381c4
 * cross-checked. */
void FUN_00038000(int actor_handle)
{
  char *actor;
  char cVar1;
  int uVar3;
  unsigned char bVar1;
  unsigned char bVar2;

  actor = (char *)datum_get(actor_data, actor_handle);
  actor_action_handle_initial_action(actor_handle);
  actor_action_handle_pending_command_list(actor_handle);
  actor_action_handle_surprise(actor_handle, 1);
  cVar1 = actor_action_deny_transition(actor_handle);
  if (cVar1 == '\0') {
    actor_action_handle_panic_from_damage(actor_handle);
    actor_action_handle_panic_from_attached_projectiles(actor_handle);
    actor_action_handle_panic_from_attached_melee_attackers(actor_handle);
    actor_action_handle_panic_from_burning_to_death(actor_handle);
    actor_action_handle_panic_transition(actor_handle, 1, 0, 9);
    actor_action_handle_combat_transition(actor_handle);
    actor_action_handle_grenade_throwing(actor_handle);
    FUN_00020990(actor_handle);
  }
  switch (*(short *)(actor + 0x6c)) {
  case 3:
  case 10:
    cVar1 = actor_action_handle_combat_status(actor_handle, 1, 0);
    if (cVar1 != '\0') {
      return;
    }
    cVar1 = actor_action_handle_combat_failure(actor_handle);
    if (cVar1 != '\0') {
      return;
    }
    actor_action_handle_evasion(actor_handle);
    return;
  case 6:
    /* PUSH 0x0 at 0x380ba is pre-positioned residue for handle_combat_status
     * 3rd arg; ADD ESP,0xc at 0x380c6 cleans 3 args for can_stop_guarding. */
    uVar3 = actor_action_can_stop_guarding(actor_handle, 3, 6);
    actor_action_handle_combat_status(actor_handle, uVar3, 0);
    return;
  case 4:
    if (*(char *)(actor + 0xaa) == '\0') {
      actor_action_handle_done_fleeing(actor_handle);
      return;
    }
    break;
  case 5:
  case 7:
  case 8:
    cVar1 = actor_action_handle_combat_status(actor_handle, 1, 0);
    if (cVar1 != '\0') {
      return;
    }
    actor_action_handle_exit_pursuit(actor_handle);
    return;
  case 9:
    if (*(char *)(actor + 0xa5) != '\0') {
      break;
    }
    if (*(char *)(actor + 0xa6) == '\0') {
      return;
    }
    actor_action_handle_combat_status(actor_handle, 1, 1);
    return;
  case 0xb:
    bVar2 = *(unsigned char *)(actor + 0x9e);
    bVar1 = *(unsigned char *)(actor + 0xa1);
    actor_action_handle_combat_status(actor_handle, bVar2, bVar1);
    return;
  case 0xc:
    if (*(char *)(actor + 0xa0) == '\0' && *(int *)(actor + 0x1dc) != -1) {
      uVar3 = actor_action_can_stop_conversing(actor_handle, 0);
      actor_action_handle_combat_status(actor_handle, uVar3, 0);
      return;
    }
    uVar3 = actor_action_can_stop_conversing(actor_handle, 1);
    actor_action_handle_combat_status(actor_handle, uVar3, 1);
    return;
  case 0xd:
    if (*(short *)(actor + 0x280) != 0) {
      return;
    }
    break;
  default:
    return;
  }
  actor_action_handle_combat_status(actor_handle, 1, 1);
}

/* FUN_00038200 (0x38200) — actor action state-machine tick (berserking/guarding
 * variant).
 *
 * Sibling of FUN_00038000. Preamble: datum_get, tag_get(0x61637472,actor+0x58)
 * result unused (cache warm), handle_initial_action,
 * handle_pending_command_list, handle_surprise(actor_handle,4), deny_transition
 * check. If deny=false: handle_berserking_from_damage,
 * handle_berserk_transition(3), handle_combat_transition, FUN_00020990.
 *
 * Switch physical layout (EAX = *(short*)(actor+0x6c)-3, range 0–0xa):
 *   3,10 → 0x38279; 4 → 0x382ac; 6 → 0x382c3; 5,7,8 → 0x382e0;
 *   0xb → 0x382fe; 0xd → 0x3831d. Shared tail 0x38327: combat_status(1,1).
 *   States 9 and 0xc are absent → default (just return).
 *
 * Case 4: when actor+0xaa!=0, JNZ to 0x38327 shared tail (combat_status(1,1)).
 *   When actor+0xaa==0: handle_done_fleeing and return.
 * Case 6: PUSH 0x0 at 0x382c3 is pre-positioned residue for combat_status 3rd
 *   arg; ADD ESP,0xc at 0x382cf cleans 3 args for can_stop_guarding.
 * Case 0xb: XOR+MOV pattern loads zero-extended unsigned bytes actor+0xa1 (EDX)
 *   and actor+0x9e (EAX) for the 3rd and 2nd args of combat_status.
 * Confirmed: disassembly 0x38200–0x38337 cross-checked. */
void FUN_00038200(int actor_handle)
{
  char *actor;
  char cVar1;
  int uVar3;
  unsigned char bVar1;
  unsigned char bVar2;

  actor = (char *)datum_get(actor_data, actor_handle);
  (void)tag_get(0x61637472, *(int *)(actor + 0x58));
  actor_action_handle_initial_action(actor_handle);
  actor_action_handle_pending_command_list(actor_handle);
  actor_action_handle_surprise(actor_handle, 4);
  cVar1 = actor_action_deny_transition(actor_handle);
  if (cVar1 == '\0') {
    actor_action_handle_berserking_from_damage(actor_handle);
    actor_action_handle_berserk_transition(actor_handle, 3);
    actor_action_handle_combat_transition(actor_handle);
    FUN_00020990(actor_handle);
  }
  switch (*(short *)(actor + 0x6c)) {
  case 3:
  case 10:
    cVar1 = actor_action_handle_combat_status(actor_handle, 1, 0);
    if (cVar1 == '\0' &&
        (cVar1 = actor_action_handle_combat_failure(actor_handle),
         cVar1 == '\0')) {
      actor_action_handle_evasion(actor_handle);
      return;
    }
    break;
  case 4:
    if (*(char *)(actor + 0xaa) == '\0') {
      actor_action_handle_done_fleeing(actor_handle);
      return;
    }
    /* fall through to shared tail */
    goto shared_tail;
  case 6:
    /* PUSH 0x0 at 0x382c3 is pre-positioned residue for combat_status 3rd arg;
     * ADD ESP,0xc at 0x382cf cleans 3 args for can_stop_guarding. */
    uVar3 = actor_action_can_stop_guarding(actor_handle, 3, 6);
    actor_action_handle_combat_status(actor_handle, uVar3, 0);
    return;
  case 5:
  case 7:
  case 8:
    cVar1 = actor_action_handle_combat_status(actor_handle, 1, 0);
    if (cVar1 == '\0') {
      actor_action_handle_exit_pursuit(actor_handle);
      return;
    }
    break;
  case 0xb:
    bVar2 = *(unsigned char *)(actor + 0x9e);
    bVar1 = *(unsigned char *)(actor + 0xa1);
    actor_action_handle_combat_status(actor_handle, bVar2, bVar1);
    return;
  case 0xd:
    if (*(short *)(actor + 0x280) != 0) {
      return;
    }
    goto shared_tail;
  default:
    return;
  }
  return;
shared_tail:
  actor_action_handle_combat_status(actor_handle, 1, 1);
}

/* FUN_00038370 (0x38370) — XBE naked draft (batch 69). */
#if defined(__clang__)
static void *(*const b38370_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void *(*const b38370_tag)(int, int) = tag_get;
static char * (*const b38370_c211f0)(int actor_handle) = actor_combat_get_firing_variant_definition;
static bool (*const b38370_c1a9ad0)(int unit_handle) = unit_is_busy;
static char (*const b38370_c2a3d0)(int actor_handle) = FUN_0002a3d0;
static void *(*const b38370_get)(int, int) = object_get_and_verify_type;
static bool (*const b38370_c3b320)(int actor_handle) = actor_has_ranged_weapon;
static void (*const b38370_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b38370_exitfn)(int) = system_exit;
static void (*const b38370_c64540)(int *out, int actor_handle) = FUN_00064540;
static int (*const b38370_c64570)(int *iter) = FUN_00064570;
static void (*const b38370_c12140)(float *a, float *b, float *result) = FUN_00012140;
static int *(*const b38370_gseed)(void) = get_global_random_seed_address;
static float (*const b38370_rmreal)(unsigned int *) = random_math_real;
static float (*const b38370_rrange)(int *, float, float) = random_real_range;
static void (*const b38370_ftol)(void) = FUN_001d9068;

__attribute__((naked, noinline))
char FUN_00038370(int actor_handle __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x24, %%esp\n\t"
      "movl 0x6325a4, %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x5c(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x61637476\n\t"
      "call *%[tag]\n\t"
      "pushl %%edi\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "call *%[c211f0]\n\t"
      "movl 0x18(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "call *%[c1a9ad0]\n\t"
      "addl $0x18, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00038370_1\n\t"
      "pushl %%edi\n\t"
      "call *%[c2a3d0]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00038370_8\n\t"
      ".LFUN_00038370_1:\n\t"
      "cmpw $3, 0x6a(%%esi)\n\t"
      "jl .LFUN_00038370_8\n\t"
      "cmpw $5, 0x6e(%%esi)\n\t"
      "jl .LFUN_00038370_9\n\t"
      "movl 0x18(%%esi), %%eax\n\t"
      "pushl $3\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl 0x270(%%esi), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "jne .LFUN_00038370_2\n\t"
      "xorl %%edi, %%edi\n\t"
      "jmp .LFUN_00038370_3\n\t"
      ".LFUN_00038370_2:\n\t"
      "movl 0x5ab23c, %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "addl $8, %%esp\n\t"
      "movl %%eax, %%edi\n\t"
      ".LFUN_00038370_3:\n\t"
      "cmpb $0x17, 0x253(%%ebx)\n\t"
      "jne .LFUN_00038370_4\n\t"
      "movb 0x378(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00038370_8\n\t"
      ".LFUN_00038370_4:\n\t"
      "testl %%edi, %%edi\n\t"
      "je .LFUN_00038370_5\n\t"
      "flds 0x11c(%%edi)\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "fcomps 0x74(%%edx)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .LFUN_00038370_9\n\t"
      ".LFUN_00038370_5:\n\t"
      "movb 0x378(%%esi), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "je .LFUN_00038370_6\n\t"
      "testl %%edi, %%edi\n\t"
      "je .LFUN_00038370_6\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "flds 0x11c(%%edi)\n\t"
      "fcomps 0x16c(%%eax)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .LFUN_00038370_9\n\t"
      ".LFUN_00038370_6:\n\t"
      "movb 0xb6(%%ebx), %%al\n\t"
      "testb %%al, %%al\n\t"
      "js .LFUN_00038370_8\n\t"
      "testb %%cl, %%cl\n\t"
      "jne .LFUN_00038370_9\n\t"
      "cmpw $0xa, 0x6c(%%esi)\n\t"
      "jne .LFUN_00038370_7\n\t"
      "movw 0xa0(%%esi), %%ax\n\t"
      "cmpw $2, %%ax\n\t"
      "je .LFUN_00038370_9\n\t"
      "cmpw $3, %%ax\n\t"
      "je .LFUN_00038370_9\n\t"
      ".LFUN_00038370_7:\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "pushl %%ebx\n\t"
      "call *%[c3b320]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00038370_9\n\t"
      "movb 0x15d(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00038370_9\n\t"
      "movl -0x10(%%ebp), %%ecx\n\t"
      "movw 0x4c(%%ecx), %%ax\n\t"
      "xorl %%edx, %%edx\n\t"
      "cmpw %%dx, %%ax\n\t"
      "je .LFUN_00038370_9\n\t"
      "cmpw $1, %%ax\n\t"
      "je .LFUN_00038370_8\n\t"
      "cmpl %%edx, %%edi\n\t"
      "je .LFUN_00038370_10\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "flds 0x11c(%%edi)\n\t"
      "fcomps 0xa0(%%eax)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00038370_10\n\t"
      ".LFUN_00038370_8:\n\t"
      "popl %%edi\n\t"
      "movb $0, 0x362(%%esi)\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00038370_9:\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%edi\n\t"
      "movb %%al, 0x362(%%esi)\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00038370_10:\n\t"
      "movb 0x362(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00038370_22\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x366(%%esi), %%ax\n\t"
      "cmpw %%dx, %%ax\n\t"
      "jle .LFUN_00038370_11\n\t"
      "decl %%eax\n\t"
      "movw %%ax, 0x366(%%esi)\n\t"
      "jmp .LFUN_00038370_19\n\t"
      ".LFUN_00038370_11:\n\t"
      "testb $8, (%%ecx)\n\t"
      "je .LFUN_00038370_19\n\t"
      "movb 0x245(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jle .LFUN_00038370_19\n\t"
      "cmpl $-1, 0x270(%%esi)\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      "movl %%edx, -0x8(%%ebp)\n\t"
      "movl %%edx, -0xc(%%ebp)\n\t"
      "jne .LFUN_00038370_12\n\t"
      "pushl $1\n\t"
      "pushl $0xc9\n\t"
      "pushl $0x256874\n\t"
      "pushl $0x254524\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00038370_12:\n\t"
      "movl 0x270(%%esi), %%ecx\n\t"
      "movl 0x5ab23c, %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%edi\n\t"
      "leal -0x18(%%ebp), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "call *%[c64540]\n\t"
      "leal -0x18(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c64570]\n\t"
      "movl -0xc(%%ebp), %%ebx\n\t"
      "movl %%eax, %%ecx\n\t"
      "addl $0x14, %%esp\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .LFUN_00038370_17\n\t"
      "nop\n\t"
      ".LFUN_00038370_13:\n\t"
      "movw 0x24(%%ecx), %%ax\n\t"
      "cmpw $2, %%ax\n\t"
      "jl .LFUN_00038370_16\n\t"
      "cmpw $3, %%ax\n\t"
      "jg .LFUN_00038370_16\n\t"
      "movb 0x60(%%ecx), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00038370_16\n\t"
      "movb 0x127(%%ecx), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00038370_16\n\t"
      "flds 0x11c(%%ecx)\n\t"
      "fcomps 0x254cc0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00038370_16\n\t"
      "movl 0x1c(%%ecx), %%ecx\n\t"
      "cmpl $-1, %%ecx\n\t"
      "je .LFUN_00038370_16\n\t"
      "movl 0x6325a4, %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[dget]\n\t"
      "movb 0x362(%%eax), %%cl\n\t"
      "addl $8, %%esp\n\t"
      "testb %%cl, %%cl\n\t"
      "je .LFUN_00038370_16\n\t"
      "leal -0x24(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "addl $0x12c, %%eax\n\t"
      "pushl %%eax\n\t"
      "leal 0x12c(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c12140]\n\t"
      "flds -0x20(%%ebp)\n\t"
      "fmuls 0xe4(%%edi)\n\t"
      "addl $0xc, %%esp\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fmuls 0xe8(%%edi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds -0x24(%%ebp)\n\t"
      "fmuls 0xe0(%%edi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fcoms 0x256870\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00038370_14\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "fstp %%st(0)\n\t"
      "incl %%eax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "jmp .LFUN_00038370_16\n\t"
      ".LFUN_00038370_14:\n\t"
      "fcomps 0x25686c\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00038370_15\n\t"
      "incl %%ebx\n\t"
      "jmp .LFUN_00038370_16\n\t"
      ".LFUN_00038370_15:\n\t"
      "incl -0x8(%%ebp)\n\t"
      ".LFUN_00038370_16:\n\t"
      "leal -0x18(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c64570]\n\t"
      "movl %%eax, %%ecx\n\t"
      "addl $4, %%esp\n\t"
      "testl %%ecx, %%ecx\n\t"
      "jne .LFUN_00038370_13\n\t"
      "movl %%ebx, -0xc(%%ebp)\n\t"
      ".LFUN_00038370_17:\n\t"
      "movb 0x363(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00038370_18\n\t"
      "testw %%bx, %%bx\n\t"
      "jne .LFUN_00038370_19\n\t"
      "movw -0x8(%%ebp), %%cx\n\t"
      "cmpw %%cx, -0x4(%%ebp)\n\t"
      "jle .LFUN_00038370_19\n\t"
      "testb %%al, %%al\n\t"
      "sete %%al\n\t"
      "jmp .LFUN_00038370_29\n\t"
      ".LFUN_00038370_18:\n\t"
      "cmpw $0, -0x4(%%ebp)\n\t"
      "jne .LFUN_00038370_19\n\t"
      "movw -0x8(%%ebp), %%dx\n\t"
      "cmpw %%dx, -0xc(%%ebp)\n\t"
      "jg .LFUN_00038370_21\n\t"
      ".LFUN_00038370_19:\n\t"
      "cmpw $0, 0x364(%%esi)\n\t"
      "jg .LFUN_00038370_20\n\t"
      "pushl $1\n\t"
      "pushl $0x100\n\t"
      "pushl $0x256874\n\t"
      "pushl $0x256838\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00038370_20:\n\t"
      "decw 0x364(%%esi)\n\t"
      "cmpw $0, 0x364(%%esi)\n\t"
      "jne .LFUN_00038370_33\n\t"
      ".LFUN_00038370_21:\n\t"
      "movb 0x363(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "sete %%al\n\t"
      "jmp .LFUN_00038370_29\n\t"
      ".LFUN_00038370_22:\n\t"
      "movb 0x200(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "movl 0x50(%%ecx), %%ecx\n\t"
      "movl %%ecx, -0x4(%%ebp)\n\t"
      "jle .LFUN_00038370_27\n\t"
      "leal -0x18(%%ebp), %%edx\n\t"
      "pushl %%ebx\n\t"
      "xorl %%edi, %%edi\n\t"
      "pushl %%edx\n\t"
      "movl %%edi, -0xc(%%ebp)\n\t"
      "call *%[c64540]\n\t"
      "leal -0x18(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c64570]\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_00038370_26\n\t"
      "movl $5, %%ebx\n\t"
      ".LFUN_00038370_23:\n\t"
      "movw 0x24(%%eax), %%cx\n\t"
      "cmpw $2, %%cx\n\t"
      "jl .LFUN_00038370_25\n\t"
      "cmpw $3, %%cx\n\t"
      "jg .LFUN_00038370_25\n\t"
      "movb 0x60(%%eax), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "jne .LFUN_00038370_25\n\t"
      "movb 0x127(%%eax), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "jne .LFUN_00038370_25\n\t"
      "movl 0x1c(%%eax), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_00038370_25\n\t"
      "movl 0x6325a4, %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movw 0x4(%%eax), %%dx\n\t"
      "addl $8, %%esp\n\t"
      "cmpw 0x4(%%esi), %%dx\n\t"
      "jne .LFUN_00038370_25\n\t"
      "cmpw %%bx, 0x6e(%%eax)\n\t"
      "jl .LFUN_00038370_25\n\t"
      "movb 0x358(%%eax), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "je .LFUN_00038370_24\n\t"
      "incl -0xc(%%ebp)\n\t"
      "jmp .LFUN_00038370_25\n\t"
      ".LFUN_00038370_24:\n\t"
      "incl %%edi\n\t"
      ".LFUN_00038370_25:\n\t"
      "leal -0x18(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c64570]\n\t"
      "addl $4, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_00038370_23\n\t"
      ".LFUN_00038370_26:\n\t"
      "movswl -0xc(%%ebp), %%ecx\n\t"
      "flds 0x2533c8\n\t"
      "fsubs -0x4(%%ebp)\n\t"
      "movl %%ecx, -0xc(%%ebp)\n\t"
      "movswl %%di, %%edx\n\t"
      "fimull -0xc(%%ebp)\n\t"
      "movl %%edx, -0xc(%%ebp)\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fchs\n\t"
      "fimull -0xc(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fmuls 0x253398\n\t"
      "fsubrs -0x4(%%ebp)\n\t"
      "fstps -0x4(%%ebp)\n\t"
      ".LFUN_00038370_27:\n\t"
      "call *%[gseed]\n\t"
      "pushl %%eax\n\t"
      "call *%[rmreal]\n\t"
      "fcomps -0x4(%%ebp)\n\t"
      "addl $4, %%esp\n\t"
      "movb $1, 0x362(%%esi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00038370_28\n\t"
      "movl $1, %%eax\n\t"
      "jmp .LFUN_00038370_29\n\t"
      ".LFUN_00038370_28:\n\t"
      "xorl %%eax, %%eax\n\t"
      ".LFUN_00038370_29:\n\t"
      "movb %%al, 0x363(%%esi)\n\t"
      "testb %%al, %%al\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "je .LFUN_00038370_30\n\t"
      "movl 0x58(%%eax), %%ecx\n\t"
      "movl 0x54(%%eax), %%edx\n\t"
      "movl %%ecx, %%eax\n\t"
      "movl %%ecx, -0x10(%%ebp)\n\t"
      "pushl %%eax\n\t"
      "movl %%edx, %%ecx\n\t"
      "movl %%edx, -0xc(%%ebp)\n\t"
      "pushl %%ecx\n\t"
      "jmp .LFUN_00038370_31\n\t"
      ".LFUN_00038370_30:\n\t"
      "movl 0x60(%%eax), %%edx\n\t"
      "movl 0x5c(%%eax), %%eax\n\t"
      "movl %%edx, %%ecx\n\t"
      "movl %%edx, -0x10(%%ebp)\n\t"
      "pushl %%ecx\n\t"
      "movl %%eax, %%edx\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "pushl %%edx\n\t"
      ".LFUN_00038370_31:\n\t"
      "call *%[gseed]\n\t"
      "pushl %%eax\n\t"
      "call *%[rrange]\n\t"
      "fmuls 0x253394\n\t"
      "addl $0xc, %%esp\n\t"
      "fcoms 0x256834\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .LFUN_00038370_32\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x256834\n\t"
      ".LFUN_00038370_32:\n\t"
      "call *%[ftol]\n\t"
      "movw %%ax, 0x364(%%esi)\n\t"
      "movw $0x1e, 0x366(%%esi)\n\t"
      ".LFUN_00038370_33:\n\t"
      "movb 0x363(%%esi), %%al\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [dget] "m"(b38370_dget), [tag] "m"(b38370_tag), [c211f0] "m"(b38370_c211f0), [c1a9ad0] "m"(b38370_c1a9ad0), [c2a3d0] "m"(b38370_c2a3d0), [get] "m"(b38370_get), [c3b320] "m"(b38370_c3b320), [assert] "m"(b38370_assert), [exitfn] "m"(b38370_exitfn), [c64540] "m"(b38370_c64540), [c64570] "m"(b38370_c64570), [c12140] "m"(b38370_c12140), [gseed] "m"(b38370_gseed), [rmreal] "m"(b38370_rmreal), [rrange] "m"(b38370_rrange), [ftol] "m"(b38370_ftol)
      : "memory");
}
#else
#error "FUN_00038370: clang naked draft required"
#endif


/* FUN_00038880 (0x38880) — XBE naked draft (batch 69). */
#if defined(__clang__)
static void *(*const b38880_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static char (*const b38880_c1dab0)(int actor_handle) = actor_action_handle_initial_action;
static char (*const b38880_c1daf0)(int actor_handle) = actor_action_handle_pending_command_list;
static char (*const b38880_c1db90)(int actor_handle, short type) = actor_action_handle_surprise;
static char (*const b38880_c1ca90)(int actor_handle) = actor_action_deny_transition;
static int (*const b38880_c1c5a0)(int actor_handle) = actor_action_handle_panic_from_surprise;
static char (*const b38880_c1c660)(int actor_handle) = actor_action_handle_panic_from_damage;
static int (*const b38880_c1c7f0)(int actor_handle) = actor_action_handle_panic_from_attached_projectiles;
static char (*const b38880_c1c880)(int actor_handle) = actor_action_handle_panic_from_attached_melee_attackers;
static int (*const b38880_c1c750)(int actor_handle) = actor_action_handle_panic_from_burning_to_death;
static char (*const b38880_c1dd40)(int actor_handle, short param_2, char param_3, short param_4) = actor_action_handle_panic_transition;
static char (*const b38880_c204f0)(int actor_handle) = actor_action_handle_combat_transition;
static char (*const b38880_c1dfa0)(int actor_handle) = actor_action_handle_vehicle_entry;
static char (*const b38880_c1cb70)(int actor_handle) = actor_action_handle_vehicle_exit;
static char (*const b38880_c205a0)(int actor_handle) = actor_action_handle_grenade_throwing;
static char (*const b38880_c20990)(int actor_handle) = FUN_00020990;
static char (*const b38880_c1f770)(int actor_handle, int param2, int param3) = actor_action_handle_combat_status;
static char (*const b38880_c1f920)(int actor_handle) = actor_action_handle_combat_failure;
static char (*const b38880_c20670)(int actor_handle) = actor_action_handle_evasion;
static char (*const b38880_c1cf10)(int actor_handle, short min_state, short max_state) = actor_action_can_stop_guarding;
static int (*const b38880_c15020)(short param_1) = FUN_00015020;
static char (*const b38880_c1f6e0)(int actor_handle) = actor_action_handle_done_fleeing;
static char (*const b38880_c1fb80)(int actor_handle) = actor_action_consider_grenade;
static char (*const b38880_c1f9a0)(int actor_handle) = actor_action_handle_exit_pursuit;
static int (*const b38880_c1cfa0)(int actor_handle, int flag) = actor_action_can_stop_conversing;

__attribute__((naked, noinline))
void FUN_00038880(int actor_handle __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "movl 0x6325a4, %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%edi\n\t"
      "movb 0x203(%%edi), %%bl\n\t"
      "movb 0x247(%%edi), %%dl\n\t"
      "testb %%bl, %%bl\n\t"
      "setg %%cl\n\t"
      "testb %%dl, %%dl\n\t"
      "pushl %%esi\n\t"
      "movb %%cl, -0x4(%%ebp)\n\t"
      "setg %%bl\n\t"
      "call *%[c1dab0]\n\t"
      "pushl %%esi\n\t"
      "call *%[c1daf0]\n\t"
      "pushl $1\n\t"
      "pushl %%esi\n\t"
      "call *%[c1db90]\n\t"
      "pushl %%esi\n\t"
      "call *%[c1ca90]\n\t"
      "addl $0x1c, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00038880_1\n\t"
      "pushl %%esi\n\t"
      "call *%[c1c5a0]\n\t"
      "pushl %%esi\n\t"
      "call *%[c1c660]\n\t"
      "pushl %%esi\n\t"
      "call *%[c1c7f0]\n\t"
      "pushl %%esi\n\t"
      "call *%[c1c880]\n\t"
      "pushl %%esi\n\t"
      "call *%[c1c750]\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "pushl $7\n\t"
      "pushl %%edx\n\t"
      "pushl $1\n\t"
      "pushl %%esi\n\t"
      "call *%[c1dd40]\n\t"
      "pushl %%esi\n\t"
      "call *%[c204f0]\n\t"
      "pushl %%esi\n\t"
      "call *%[c1dfa0]\n\t"
      "pushl %%esi\n\t"
      "call *%[c1cb70]\n\t"
      "pushl %%esi\n\t"
      "call *%[c205a0]\n\t"
      "pushl %%esi\n\t"
      "call *%[c20990]\n\t"
      "addl $0x38, %%esp\n\t"
      ".LFUN_00038880_1:\n\t"
      "movswl 0x6c(%%edi), %%eax\n\t"
      "addl $-3, %%eax\n\t"
      "cmpl $0xa, %%eax\n\t"
      "ja .LFUN_00038880_13\n\t"
      "jmp *.LFUN_00038880_jt(,%%eax,4)\n\t"
      ".LFUN_00038880_2:\n\t"
      "pushl $0\n\t"
      "pushl $1\n\t"
      "pushl %%esi\n\t"
      "call *%[c1f770]\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00038880_13\n\t"
      "pushl %%esi\n\t"
      "call *%[c1f920]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00038880_13\n\t"
      "pushl %%esi\n\t"
      "call *%[c20670]\n\t"
      "addl $4, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00038880_3:\n\t"
      "pushl $0\n\t"
      "pushl $6\n\t"
      "pushl $3\n\t"
      "pushl %%esi\n\t"
      "call *%[c1cf10]\n\t"
      "addl $0xc, %%esp\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[c1f770]\n\t"
      "addl $0xc, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00038880_4:\n\t"
      "testb %%bl, %%bl\n\t"
      "je .LFUN_00038880_5\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0xa8(%%edi), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "jle .LFUN_00038880_5\n\t"
      "pushl %%eax\n\t"
      "call *%[c15020]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00038880_5\n\t"
      "movb $1, 0xab(%%edi)\n\t"
      ".LFUN_00038880_5:\n\t"
      "movb 0xaa(%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00038880_12\n\t"
      "pushl %%esi\n\t"
      "call *%[c1f6e0]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00038880_13\n\t"
      "cmpw $0, 0xa8(%%edi)\n\t"
      "jne .LFUN_00038880_13\n\t"
      "cmpw $5, 0x6e(%%edi)\n\t"
      "jl .LFUN_00038880_13\n\t"
      "pushl %%esi\n\t"
      "call *%[c1fb80]\n\t"
      "addl $4, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00038880_6:\n\t"
      "pushl $0\n\t"
      "pushl $1\n\t"
      "pushl %%esi\n\t"
      "call *%[c1f770]\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00038880_13\n\t"
      "pushl %%esi\n\t"
      "call *%[c1f9a0]\n\t"
      "addl $4, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00038880_7:\n\t"
      "movb 0xa5(%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00038880_12\n\t"
      "movb 0xa6(%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00038880_13\n\t"
      "pushl $1\n\t"
      "pushl $1\n\t"
      "pushl %%esi\n\t"
      "call *%[c1f770]\n\t"
      "addl $0xc, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00038880_8:\n\t"
      "xorl %%eax, %%eax\n\t"
      "movb 0xa1(%%edi), %%al\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movb 0x9e(%%edi), %%cl\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "call *%[c1f770]\n\t"
      "addl $0xc, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00038880_9:\n\t"
      "movb 0xa0(%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00038880_10\n\t"
      "cmpl $-1, 0x1dc(%%edi)\n\t"
      "je .LFUN_00038880_10\n\t"
      "xorl %%eax, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[c1cfa0]\n\t"
      "addl $4, %%esp\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[c1f770]\n\t"
      "addl $0xc, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00038880_10:\n\t"
      "movl $1, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[c1cfa0]\n\t"
      "addl $4, %%esp\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[c1f770]\n\t"
      "addl $0xc, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00038880_11:\n\t"
      "cmpw $0, 0x280(%%edi)\n\t"
      "jne .LFUN_00038880_13\n\t"
      ".LFUN_00038880_12:\n\t"
      "pushl $1\n\t"
      "pushl $1\n\t"
      "pushl %%esi\n\t"
      "call *%[c1f770]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_00038880_13:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_00038880_jt:\n\t"
      ".long .LFUN_00038880_2\n\t"
      ".long .LFUN_00038880_4\n\t"
      ".long .LFUN_00038880_6\n\t"
      ".long .LFUN_00038880_3\n\t"
      ".long .LFUN_00038880_6\n\t"
      ".long .LFUN_00038880_6\n\t"
      ".long .LFUN_00038880_7\n\t"
      ".long .LFUN_00038880_2\n\t"
      ".long .LFUN_00038880_8\n\t"
      ".long .LFUN_00038880_9\n\t"
      ".long .LFUN_00038880_11\n\t"
      ".text\n\t"
      :
      : [dget] "m"(b38880_dget), [c1dab0] "m"(b38880_c1dab0), [c1daf0] "m"(b38880_c1daf0), [c1db90] "m"(b38880_c1db90), [c1ca90] "m"(b38880_c1ca90), [c1c5a0] "m"(b38880_c1c5a0), [c1c660] "m"(b38880_c1c660), [c1c7f0] "m"(b38880_c1c7f0), [c1c880] "m"(b38880_c1c880), [c1c750] "m"(b38880_c1c750), [c1dd40] "m"(b38880_c1dd40), [c204f0] "m"(b38880_c204f0), [c1dfa0] "m"(b38880_c1dfa0), [c1cb70] "m"(b38880_c1cb70), [c205a0] "m"(b38880_c205a0), [c20990] "m"(b38880_c20990), [c1f770] "m"(b38880_c1f770), [c1f920] "m"(b38880_c1f920), [c20670] "m"(b38880_c20670), [c1cf10] "m"(b38880_c1cf10), [c15020] "m"(b38880_c15020), [c1f6e0] "m"(b38880_c1f6e0), [c1fb80] "m"(b38880_c1fb80), [c1f9a0] "m"(b38880_c1f9a0), [c1cfa0] "m"(b38880_c1cfa0)
      : "memory");
}
#else
#error "FUN_00038880: clang naked draft required"
#endif


/* FUN_00038b10 (0x38b10) — actor action state-machine tick for fighter/retreat
 * type. Handles initial action, combat targeting, berserk transitions, and
 * behavior dispatch. Confirmed from disassembly: switch on
 * *(short*)(actor+0x6c); actor_action_can_stop_conversing takes 2 params (flag
 * 0/1); case 0xb loads bytes via local unsigned char vars (XOR+MOV pattern);
 * case 0xc uses batched-cleanup residue: 3rd arg to handle_combat_status is
 * the flag (0/1) pushed before can_stop_conversing and partially cleaned. */
void FUN_00038b10(int actor_handle)
{
  char *actor;
  char cVar1;
  int uVar3;
  unsigned char bVar1;
  unsigned char bVar2;

  actor = (char *)datum_get(actor_data, actor_handle);
  actor_action_handle_initial_action(actor_handle);
  actor_action_handle_pending_command_list(actor_handle);
  cVar1 = actor_action_deny_transition(actor_handle);
  if (cVar1 == '\0') {
    actor_action_handle_berserking_from_damage(actor_handle);
    actor_action_handle_combat_targeting(actor_handle);
    actor_action_handle_berserk_transition(actor_handle, 3);
    actor_action_handle_combat_transition(actor_handle);
    FUN_00020990(actor_handle);
  }
  switch (*(short *)(actor + 0x6c)) {
  case 3:
  case 4:
  case 6:
  case 10:
    cVar1 = actor_action_handle_combat_status(actor_handle, 1, 0);
    if (cVar1 == '\0') {
      actor_action_handle_combat_failure(actor_handle);
      return;
    }
    break;
  case 5:
  case 7:
  case 8:
    cVar1 = actor_action_handle_combat_status(actor_handle, 1, 0);
    if (cVar1 == '\0') {
      actor_action_handle_exit_pursuit(actor_handle);
      return;
    }
    break;
  case 0xb:
    bVar1 = *(unsigned char *)(actor + 0x9e);
    bVar2 = *(unsigned char *)(actor + 0xa1);
    actor_action_handle_combat_status(actor_handle, bVar1, bVar2);
    return;
  case 0xc:
    if (*(char *)(actor + 0xa0) == '\0' && *(int *)(actor + 0x1dc) != -1) {
      uVar3 = actor_action_can_stop_conversing(actor_handle, 0);
      actor_action_handle_combat_status(actor_handle, uVar3, 0);
      return;
    }
    uVar3 = actor_action_can_stop_conversing(actor_handle, 1);
    actor_action_handle_combat_status(actor_handle, uVar3, 1);
    return;
  case 0xd:
    if (*(short *)(actor + 0x280) == 0) {
      actor_action_handle_combat_status(actor_handle, 1, 1);
    }
  }
}

/* FUN_00038c70 (0x38c70) — actor action state-machine tick (combat-only
 * variant). Preamble: datum_get, tag_get(0x61637472, actor+0x58) (cache warm),
 * handle_initial_action, handle_pending_command_list, deny_transition.
 * If deny==false: handle_combat_transition only (no
 * berserking/panic/targeting). Switch on actor+0x6c: cases 3,10 →
 * combat_status(1,0)+combat_failure; case 4 → if actor+0xaa!=0:
 * combat_status(1,1), else done_fleeing; cases 5,7,8 →
 * combat_status(1,0)+exit_pursuit; case 6 →
 * can_stop_guarding(3,6)+combat_status(result,0); case 11 →
 * combat_status(actor+0x9e, actor+0xa1); case 9 → return. */
void FUN_00038c70(int actor_handle)
{
  char *actor;
  char cVar1;
  int uVar3;
  unsigned char bVar1;
  unsigned char bVar2;

  actor = (char *)datum_get(actor_data, actor_handle);
  (void)tag_get(0x61637472, *(int *)(actor + 0x58));
  actor_action_handle_initial_action(actor_handle);
  actor_action_handle_pending_command_list(actor_handle);
  cVar1 = actor_action_deny_transition(actor_handle);
  if (cVar1 == '\0') {
    actor_action_handle_combat_transition(actor_handle);
  }
  switch (*(short *)(actor + 0x6c)) {
  case 3:
  case 10:
    cVar1 = actor_action_handle_combat_status(actor_handle, 1, 0);
    if (cVar1 != '\0') {
      return;
    }
    actor_action_handle_combat_failure(actor_handle);
    return;
  case 4:
    if (*(char *)(actor + 0xaa) != '\0') {
      actor_action_handle_combat_status(actor_handle, 1, 1);
      return;
    }
    actor_action_handle_done_fleeing(actor_handle);
    return;
  case 6:
    uVar3 = actor_action_can_stop_guarding(actor_handle, 3, 6);
    actor_action_handle_combat_status(actor_handle, uVar3, 0);
    return;
  case 5:
  case 7:
  case 8:
    cVar1 = actor_action_handle_combat_status(actor_handle, 1, 0);
    if (cVar1 != '\0') {
      return;
    }
    actor_action_handle_exit_pursuit(actor_handle);
    return;
  case 11:
    bVar2 = *(unsigned char *)(actor + 0xa1);
    bVar1 = *(unsigned char *)(actor + 0x9e);
    actor_action_handle_combat_status(actor_handle, bVar1, bVar2);
    return;
  default:
    return;
  }
}

/*
 * FUN_00038da0 -- actor timer for unit-effect durations (main set).
 *
 * Returns a random tick count scaled by DAT_00253394 for the given hit type.
 * unit_effect 1 → [4.0, 5.0]s, 2 → [2.0, 2.8]s, 3 → [0.4, 1.0]s.
 * Falls back to *(float*)0x2533c8 for unknown types.
 * Clamps result to 255.
 *
 * Disassembly: DEC/JZ/DEC/JZ/DEC/JNZ chain; default float FLD'd first,
 * popped (FSTP ST0) at merge.  Multiplied by [0x253394], _ftol2, CMP
 * AX,0xff / JLE clamp, MOVSX EAX,AX return.
 */
int FUN_00038da0(short unit_effect /* @<eax> */)
{
  float timer_raw;
  short final_val;

  switch (unit_effect) {
  case 1:
    timer_raw = random_real_range(get_global_random_seed_address(), 4.0f, 5.0f);
    goto compute;
  case 2:
    timer_raw = random_real_range(get_global_random_seed_address(), 2.0f, 2.8f);
    goto compute;
  case 3:
    timer_raw = random_real_range(get_global_random_seed_address(), 0.4f, 1.0f);
    goto compute;
  default:
    timer_raw = *(float *)0x2533c8;
    goto compute;
  }
compute:
  final_val = (short)(int)(timer_raw * TICKS_PER_SECOND);
  if (final_val > 0xff)
    return 0xff;
  return final_val;
}

/*
 * FUN_00038e00 -- actor timer for unit-effect durations (secondary set).
 *
 * unit_effect 1 → [1.0, 2.5]s, 2-3 → [0.6, 1.8]s.
 * Falls back to *(float*)0x2533c8 for other types.
 * Clamps result to 255.
 *
 * Disassembly: FLD default → MOVSX → CMP AX,1 / JZ case_1 / JLE skip /
 * CMP AX,3 / JG skip; matching ranges FSTP ST0 + random; others keep
 * default on x87 stack.  FMUL [0x253394], _ftol2, CMP AX,0xff / JLE,
 * MOVSX EAX,AX return.
 */
int FUN_00038e00(short unit_effect /* @<eax> */)
{
  float timer_raw;
  short final_val;

  timer_raw = *(float *)0x2533c8;
  if (unit_effect == 1) {
    timer_raw = random_real_range(get_global_random_seed_address(), 1.0f, 2.5f);
  } else if (unit_effect <= 1) {
    goto scale;
  } else if (unit_effect > 3) {
    goto scale;
  } else {
    timer_raw = random_real_range(get_global_random_seed_address(), 0.6f, 1.8f);
  }
scale:
  final_val = (short)(int)(timer_raw * TICKS_PER_SECOND);
  if (final_val > 0xff)
    return 0xff;
  return final_val;
}

/* FUN_00038e60 (0x38e60) — XBE naked draft (batch 69). */
#if defined(__clang__)
static void *(*const b38e60_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void *(*const b38e60_tag)(int, int) = tag_get;
static int *(*const b38e60_gseed)(void) = get_global_random_seed_address;
static float (*const b38e60_rrange)(int *, float, float) = random_real_range;
static void (*const b38e60_ftol)(void) = FUN_001d9068;
static int16_t (*const b38e60_c10b2d0)(unsigned int *seed, int16_t min, int16_t max) = random_range;
static void *(*const b38e60_get)(int, int) = object_get_and_verify_type;
static void (*const b38e60_c64540)(int *out, int actor_handle) = FUN_00064540;
static int (*const b38e60_c64570)(int *iter) = FUN_00064570;
static int (*const b38e60_gtime)(void) = game_time_get;
static void (*const b38e60_c1aa5c0)(int object_handle) = unit_detach_from_parent;
static void *(*const b38e60_memset)(void *, int, unsigned int) = csmemset;
static int (*const b38e60_c38da0)(short unit_effect /* */) = FUN_00038da0;
static float (*const b38e60_c121e0)(float min, float max) = FUN_000121e0;
static void (*const b38e60_rots)(float *, float *, float, float) = rotate_vector3d_by_sincos;
static int (*const b38e60_c38e00)(short unit_effect /* */) = FUN_00038e00;
static void (*const b38e60_c12140)(float *a, float *b, float *result) = FUN_00012140;
static float (*const b38e60_c12170)(float *vector) = FUN_00012170;
static void (*const b38e60_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b38e60_exitfn)(int) = system_exit;
static void (*const b38e60_cross)(float *, float *, float *) = cross_product3d;
static bool (*const b38e60_c1a9ad0)(int unit_handle) = unit_is_busy;
static float (*const b38e60_norm)(float *) = normalize3d;
static void (*const b38e60_c1af990)(int unit_handle, void *unit_control) = unit_set_control;

__attribute__((naked, noinline))
void FUN_00038e60(int actor_handle __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xe8, %%esp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl 0x6325a4, %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x5c(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x61637476\n\t"
      "movl %%esi, -0x6c(%%ebp)\n\t"
      "call *%[tag]\n\t"
      "movl 0x6325a0, %%ecx\n\t"
      "movl %%eax, -0x74(%%ebp)\n\t"
      "movl 0x28(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%edi\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x8(%%edi), %%ax\n\t"
      "addl $0x18, %%esp\n\t"
      "testw %%ax, %%ax\n\t"
      "movl %%edi, -0x5c(%%ebp)\n\t"
      "movl $0xffffffff, -0x70(%%ebp)\n\t"
      "jle .LFUN_00038e60_1\n\t"
      "decl %%eax\n\t"
      "movw %%ax, 0x8(%%edi)\n\t"
      "jmp .LFUN_00038e60_4\n\t"
      ".LFUN_00038e60_1:\n\t"
      "movswl 0x6c(%%esi), %%eax\n\t"
      "cmpl $7, %%eax\n\t"
      "je .LFUN_00038e60_2\n\t"
      "cmpl $0xa, %%eax\n\t"
      "jne .LFUN_00038e60_4\n\t"
      ".LFUN_00038e60_2:\n\t"
      "movw 0x2(%%edi), %%si\n\t"
      "pushl $0x41000000\n\t"
      "pushl $0x40c00000\n\t"
      "call *%[gseed]\n\t"
      "pushl %%eax\n\t"
      "call *%[rrange]\n\t"
      "movswl %%si, %%edx\n\t"
      "movl %%edx, -0x60(%%ebp)\n\t"
      "addl $0xc, %%esp\n\t"
      "fidivl -0x60(%%ebp)\n\t"
      "fmuls 0x253394\n\t"
      "fcoms 0x254640\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .LFUN_00038e60_3\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x254640\n\t"
      ".LFUN_00038e60_3:\n\t"
      "call *%[ftol]\n\t"
      "pushl %%esi\n\t"
      "pushl $0\n\t"
      "movw %%ax, 0x8(%%edi)\n\t"
      "call *%[gseed]\n\t"
      "pushl %%eax\n\t"
      "call *%[c10b2d0]\n\t"
      "addl $0xc, %%esp\n\t"
      "movl %%eax, -0x70(%%ebp)\n\t"
      ".LFUN_00038e60_4:\n\t"
      "cmpw $0, 0x2(%%edi)\n\t"
      "movl $0, -0x4c(%%ebp)\n\t"
      "jle .LFUN_00038e60_90\n\t"
      "pushl %%ebx\n\t"
      "jmp .LFUN_00038e60_6\n\t"
      ".LFUN_00038e60_5:\n\t"
      "movl -0x5c(%%ebp), %%edi\n\t"
      ".LFUN_00038e60_6:\n\t"
      "movswl -0x4c(%%ebp), %%esi\n\t"
      "movl 0x18(%%edi,%%esi,4), %%eax\n\t"
      "pushl $3\n\t"
      "pushl %%eax\n\t"
      "movl %%eax, -0x64(%%ebp)\n\t"
      "call *%[get]\n\t"
      "movl 0x63259c, %%ecx\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl 0x58(%%edi,%%esi,4), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "movl %%ebx, -0x28(%%ebp)\n\t"
      "call *%[dget]\n\t"
      "leal 0x30(%%ebx), %%edx\n\t"
      "movl %%eax, %%esi\n\t"
      "movl (%%edx), %%eax\n\t"
      "movl %%eax, -0x24(%%ebp)\n\t"
      "movl 0x4(%%edx), %%ecx\n\t"
      "movl %%ecx, -0x20(%%ebp)\n\t"
      "movl 0x8(%%edx), %%edx\n\t"
      "addl $0x10, %%esp\n\t"
      "movl %%edx, -0x1c(%%ebp)\n\t"
      "cmpw $0, 0x64(%%ebx)\n\t"
      "movl $0, -0x18(%%ebp)\n\t"
      "movl $0xffffffff, -0x30(%%ebp)\n\t"
      "movl $3, -0x38(%%ebp)\n\t"
      "movl $1, -0x60(%%ebp)\n\t"
      "movb $0, -0x29(%%ebp)\n\t"
      "movb $0, -0x11(%%ebp)\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "movb $0, -0x2b(%%ebp)\n\t"
      "movb $0, -0x2a(%%ebp)\n\t"
      "jne .LFUN_00038e60_8\n\t"
      "cmpl $-1, 0x430(%%ebx)\n\t"
      "je .LFUN_00038e60_7\n\t"
      "leal 0x46c(%%ebx), %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "movl %%ecx, -0x24(%%ebp)\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl %%edx, -0x20(%%ebp)\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl %%eax, -0x1c(%%ebp)\n\t"
      ".LFUN_00038e60_7:\n\t"
      "movb 0x424(%%ebx), %%al\n\t"
      "andb $1, %%al\n\t"
      "movb %%al, -0x2a(%%ebp)\n\t"
      ".LFUN_00038e60_8:\n\t"
      "movl -0x6c(%%ebp), %%ecx\n\t"
      "cmpw $3, 0x6e(%%ecx)\n\t"
      "jl .LFUN_00038e60_18\n\t"
      "movl -0x74(%%ebp), %%edx\n\t"
      "movl 0xa0(%%edx), %%eax\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x84(%%ebp), %%edx\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "pushl %%edx\n\t"
      "movl %%eax, -0x68(%%ebp)\n\t"
      "orl $0xffffffff, %%edi\n\t"
      "movl %%ebx, -0x7c(%%ebp)\n\t"
      "movl %%ebx, -0x78(%%ebp)\n\t"
      "call *%[c64540]\n\t"
      "leal -0x84(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c64570]\n\t"
      "movl %%eax, %%ecx\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .LFUN_00038e60_16\n\t"
      "jmp .LFUN_00038e60_9\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_00038e60_9:\n\t"
      "flds 0x50(%%ecx)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00038e60_15\n\t"
      "flds 0x4(%%esi)\n\t"
      "fsubs 0xbc(%%ecx)\n\t"
      "flds 0x8(%%esi)\n\t"
      "fsubs 0xc0(%%ecx)\n\t"
      "flds 0xc(%%esi)\n\t"
      "fsubs 0xc4(%%ecx)\n\t"
      "fld %%st(1)\n\t"
      ".byte 0xd8, 0xca\n\t"
      "fld %%st(1)\n\t"
      ".byte 0xd8, 0xca\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fld %%st(3)\n\t"
      ".byte 0xd8, 0xcc\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fsqrt\n\t"
      "fstp %%st(3)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c0\n\t"
      "fld %%st(1)\n\t"
      "fcomps -0x68(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00038e60_10\n\t"
      "fstp %%st(0)\n\t"
      "flds -0x68(%%ebp)\n\t"
      ".byte 0xd8, 0xf9\n\t"
      "fsubrs 0x2533c8\n\t"
      "fmuls 0x253f34\n\t"
      ".LFUN_00038e60_10:\n\t"
      "movw 0x24(%%ecx), %%ax\n\t"
      "cmpw $2, %%ax\n\t"
      "movl -0x84(%%ebp), %%edx\n\t"
      "jl .LFUN_00038e60_13\n\t"
      "cmpw $3, %%ax\n\t"
      "jg .LFUN_00038e60_13\n\t"
      "cmpl 0x14(%%esi), %%edx\n\t"
      "jne .LFUN_00038e60_11\n\t"
      "fadds 0x2548f4\n\t"
      "jmp .LFUN_00038e60_12\n\t"
      ".LFUN_00038e60_11:\n\t"
      "fadds 0x254cc4\n\t"
      ".LFUN_00038e60_12:\n\t"
      "movb 0x125(%%ecx), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00038e60_13\n\t"
      "fadds 0x254cc4\n\t"
      ".LFUN_00038e60_13:\n\t"
      "fcoms -0x7c(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00038e60_14\n\t"
      "fstps -0x7c(%%ebp)\n\t"
      "movl %%ecx, %%ebx\n\t"
      "movl %%edx, %%edi\n\t"
      "fstps -0x78(%%ebp)\n\t"
      "jmp .LFUN_00038e60_15\n\t"
      ".LFUN_00038e60_14:\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      ".LFUN_00038e60_15:\n\t"
      "leal -0x84(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c64570]\n\t"
      "movl %%eax, %%ecx\n\t"
      "addl $4, %%esp\n\t"
      "testl %%ecx, %%ecx\n\t"
      "jne .LFUN_00038e60_9\n\t"
      ".LFUN_00038e60_16:\n\t"
      "cmpl $-1, %%edi\n\t"
      "movl %%edi, 0x14(%%esi)\n\t"
      "je .LFUN_00038e60_17\n\t"
      "flds -0x78(%%ebp)\n\t"
      "movl -0x74(%%ebp), %%edx\n\t"
      "fcomps 0x160(%%edx)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00038e60_17\n\t"
      "movw 0x24(%%ebx), %%ax\n\t"
      "cmpw $2, %%ax\n\t"
      "jl .LFUN_00038e60_17\n\t"
      "cmpw $3, %%ax\n\t"
      "jg .LFUN_00038e60_17\n\t"
      "movb $1, -0x11(%%ebp)\n\t"
      ".LFUN_00038e60_17:\n\t"
      "movl %%ebx, -0x48(%%ebp)\n\t"
      "jmp .LFUN_00038e60_19\n\t"
      ".LFUN_00038e60_18:\n\t"
      "movl $0xffffffff, 0x14(%%esi)\n\t"
      "movl $0, -0x48(%%ebp)\n\t"
      ".LFUN_00038e60_19:\n\t"
      "movl -0x6c(%%ebp), %%edx\n\t"
      "movw 0x6c(%%edx), %%ax\n\t"
      "movswl %%ax, %%ecx\n\t"
      "decl %%ecx\n\t"
      "cmpl $0xa, %%ecx\n\t"
      "ja .LFUN_00038e60_29\n\t"
      "jmp *.LFUN_00038e60_jt0(,%%ecx,4)\n\t"
      ".LFUN_00038e60_20:\n\t"
      "xorl %%eax, %%eax\n\t"
      "movl %%eax, -0x18(%%ebp)\n\t"
      "movl %%eax, -0x38(%%ebp)\n\t"
      "jmp .LFUN_00038e60_29\n\t"
      ".LFUN_00038e60_21:\n\t"
      "movl $1, %%eax\n\t"
      "movl %%eax, -0x18(%%ebp)\n\t"
      "movl %%eax, -0x38(%%ebp)\n\t"
      "jmp .LFUN_00038e60_29\n\t"
      ".LFUN_00038e60_22:\n\t"
      "movl $2, -0x18(%%ebp)\n\t"
      "movl $1, -0x38(%%ebp)\n\t"
      "jmp .LFUN_00038e60_29\n\t"
      ".LFUN_00038e60_23:\n\t"
      "cmpw $0, 0xa4(%%edx)\n\t"
      "jne .LFUN_00038e60_24\n\t"
      "movl 0x270(%%edx), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_00038e60_24\n\t"
      "movl $4, -0x18(%%ebp)\n\t"
      "movl %%eax, -0x30(%%ebp)\n\t"
      "movl $3, -0x38(%%ebp)\n\t"
      "jmp .LFUN_00038e60_29\n\t"
      ".LFUN_00038e60_24:\n\t"
      "movl $3, -0x18(%%ebp)\n\t"
      "movl $3, -0x38(%%ebp)\n\t"
      "jmp .LFUN_00038e60_29\n\t"
      ".LFUN_00038e60_25:\n\t"
      "xorl %%eax, %%eax\n\t"
      "cmpw %%ax, 0xa8(%%edx)\n\t"
      "setg %%al\n\t"
      "leal 0x3(%%eax,%%eax,1), %%eax\n\t"
      "movl %%eax, -0x38(%%ebp)\n\t"
      "movl 0xb8(%%edx), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_00038e60_29\n\t"
      "movl $5, -0x18(%%ebp)\n\t"
      "movl %%eax, -0x30(%%ebp)\n\t"
      "jmp .LFUN_00038e60_29\n\t"
      ".LFUN_00038e60_26:\n\t"
      "cmpw $0xb, %%ax\n\t"
      "movl $3, %%ecx\n\t"
      "movl %%ecx, -0x38(%%ebp)\n\t"
      "jne .LFUN_00038e60_27\n\t"
      "testb $8, 0x2(%%esi)\n\t"
      "je .LFUN_00038e60_27\n\t"
      "movl $6, -0x18(%%ebp)\n\t"
      "jmp .LFUN_00038e60_29\n\t"
      ".LFUN_00038e60_27:\n\t"
      "movl 0x14(%%esi), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_00038e60_28\n\t"
      "movb 0x1a(%%esi), %%bl\n\t"
      "movl %%eax, -0x30(%%ebp)\n\t"
      "xorb %%al, %%al\n\t"
      "cmpb %%bl, %%al\n\t"
      "movl $0, -0x60(%%ebp)\n\t"
      "sbbl %%eax, %%eax\n\t"
      "negl %%eax\n\t"
      "addl $4, %%eax\n\t"
      "movl %%eax, -0x18(%%ebp)\n\t"
      "jmp .LFUN_00038e60_29\n\t"
      ".LFUN_00038e60_28:\n\t"
      "movl %%ecx, -0x18(%%ebp)\n\t"
      ".LFUN_00038e60_29:\n\t"
      "movl -0x28(%%ebp), %%ecx\n\t"
      "movl 0xcc(%%ecx), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "jne .LFUN_00038e60_30\n\t"
      "movb 0x1a(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "movb $0, 0x18(%%esi)\n\t"
      "jbe .LFUN_00038e60_38\n\t"
      "decb %%al\n\t"
      "movb %%al, 0x1a(%%esi)\n\t"
      "jmp .LFUN_00038e60_38\n\t"
      ".LFUN_00038e60_30:\n\t"
      "pushl $3\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%edi\n\t"
      "movb 0xb6(%%edi), %%bl\n\t"
      "movb 0x18(%%esi), %%al\n\t"
      "shrb $2, %%bl\n\t"
      "addl $8, %%esp\n\t"
      "andb $1, %%bl\n\t"
      "cmpb $0xff, %%al\n\t"
      "jae .LFUN_00038e60_31\n\t"
      "incb %%al\n\t"
      "movb %%al, 0x18(%%esi)\n\t"
      ".LFUN_00038e60_31:\n\t"
      "testb %%bl, %%bl\n\t"
      "je .LFUN_00038e60_33\n\t"
      "cmpl $-1, 0x3cc(%%edi)\n\t"
      "je .LFUN_00038e60_32\n\t"
      "call *%[gtime]\n\t"
      "movl 0x3cc(%%edi), %%edx\n\t"
      "addl $0x4b, %%edx\n\t"
      "cmpl %%eax, %%edx\n\t"
      "jge .LFUN_00038e60_32\n\t"
      "movl -0x48(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_00038e60_32\n\t"
      "movl 0x18(%%eax), %%ecx\n\t"
      "movl -0x28(%%ebp), %%edx\n\t"
      "cmpl 0xcc(%%edx), %%ecx\n\t"
      "je .LFUN_00038e60_32\n\t"
      "movl -0x48(%%ebp), %%eax\n\t"
      "movw 0x24(%%eax), %%ax\n\t"
      "cmpw $2, %%ax\n\t"
      "jl .LFUN_00038e60_32\n\t"
      "cmpw $3, %%ax\n\t"
      "jle .LFUN_00038e60_35\n\t"
      ".LFUN_00038e60_32:\n\t"
      "orb $2, 0x2(%%esi)\n\t"
      "xorl %%eax, %%eax\n\t"
      "testb %%bl, %%bl\n\t"
      "movw 0x2(%%esi), %%ax\n\t"
      "jne .LFUN_00038e60_36\n\t"
      "orl $1, %%eax\n\t"
      "jmp .LFUN_00038e60_37\n\t"
      ".LFUN_00038e60_33:\n\t"
      "movl (%%edi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x756e6974\n\t"
      "call *%[tag]\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $0, 0x64(%%edi)\n\t"
      "jne .LFUN_00038e60_34\n\t"
      "movl 0x17c(%%eax), %%ecx\n\t"
      "testb %%ch, %%ch\n\t"
      "jns .LFUN_00038e60_32\n\t"
      ".LFUN_00038e60_34:\n\t"
      "cmpb $0x2d, 0x18(%%esi)\n\t"
      "jbe .LFUN_00038e60_32\n\t"
      "movb $0x2d, 0x1a(%%esi)\n\t"
      ".LFUN_00038e60_35:\n\t"
      "movl -0x64(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c1aa5c0]\n\t"
      "addl $4, %%esp\n\t"
      "andb $0xfc, 0x2(%%esi)\n\t"
      "jmp .LFUN_00038e60_38\n\t"
      ".LFUN_00038e60_36:\n\t"
      "andl $0xfffffffe, %%eax\n\t"
      ".LFUN_00038e60_37:\n\t"
      "movw %%ax, 0x2(%%esi)\n\t"
      ".LFUN_00038e60_38:\n\t"
      "movl -0x28(%%ebp), %%eax\n\t"
      "cmpl $-1, 0xcc(%%eax)\n\t"
      "jne .LFUN_00038e60_74\n\t"
      "movb -0x2a(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00038e60_39\n\t"
      "andb $0xfd, 0x2(%%esi)\n\t"
      "movb $0, 0x19(%%esi)\n\t"
      "jmp .LFUN_00038e60_74\n\t"
      ".LFUN_00038e60_39:\n\t"
      "movb 0x19(%%esi), %%al\n\t"
      "cmpb $0xff, %%al\n\t"
      "jae .LFUN_00038e60_40\n\t"
      "incb %%al\n\t"
      "movb %%al, 0x19(%%esi)\n\t"
      ".LFUN_00038e60_40:\n\t"
      "movswl -0x18(%%ebp), %%eax\n\t"
      "andb $0xfc, 0x2(%%esi)\n\t"
      "movw 0x2(%%esi), %%cx\n\t"
      "decl %%eax\n\t"
      "cmpl $5, %%eax\n\t"
      "ja .LFUN_00038e60_74\n\t"
      "jmp *.LFUN_00038e60_jt1(,%%eax,4)\n\t"
      ".LFUN_00038e60_41:\n\t"
      "testb $4, %%cl\n\t"
      "jne .LFUN_00038e60_42\n\t"
      "pushl $0x14\n\t"
      "leal 0x1c(%%esi), %%ecx\n\t"
      "pushl $0\n\t"
      "pushl %%ecx\n\t"
      "call *%[memset]\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x2(%%esi), %%dx\n\t"
      "addl $0xc, %%esp\n\t"
      "andl $0xfffffff7, %%edx\n\t"
      "orl $4, %%edx\n\t"
      "movw %%dx, 0x2(%%esi)\n\t"
      ".LFUN_00038e60_42:\n\t"
      "movb 0x1d(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jbe .LFUN_00038e60_44\n\t"
      "decb %%al\n\t"
      "movb %%al, 0x1d(%%esi)\n\t"
      "jne .LFUN_00038e60_43\n\t"
      "movl -0x18(%%ebp), %%eax\n\t"
      "call *%[c38da0]\n\t"
      "movb %%al, 0x1c(%%esi)\n\t"
      "jmp .LFUN_00038e60_49\n\t"
      ".LFUN_00038e60_43:\n\t"
      "flds 0x2c(%%esi)\n\t"
      "pushl $0x3cab92a6\n\t"
      "fmuls 0x256984\n\t"
      "pushl $0xbcab92a6\n\t"
      "fstps -0x30(%%ebp)\n\t"
      "call *%[c121e0]\n\t"
      "fadds 0x2c(%%esi)\n\t"
      "leal -0x24(%%ebp), %%eax\n\t"
      "leal 0x20(%%esi), %%ecx\n\t"
      "fadds -0x30(%%ebp)\n\t"
      "fsts 0x2c(%%esi)\n\t"
      "fld %%st(0)\n\t"
      "fcos\n\t"
      "fstps 0x4(%%esp)\n\t"
      "fsin\n\t"
      "fstps (%%esp)\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[rots]\n\t"
      "jmp .LFUN_00038e60_48\n\t"
      ".LFUN_00038e60_44:\n\t"
      "movb 0x1c(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jbe .LFUN_00038e60_45\n\t"
      "decb %%al\n\t"
      "movb %%al, 0x1c(%%esi)\n\t"
      ".LFUN_00038e60_45:\n\t"
      "movb 0x1c(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00038e60_49\n\t"
      "movl -0x18(%%ebp), %%eax\n\t"
      "call *%[c38e00]\n\t"
      "movb %%al, 0x1d(%%esi)\n\t"
      "movl -0x5c(%%ebp), %%eax\n\t"
      "leal -0xe8(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "addl $0xc, %%eax\n\t"
      "pushl %%eax\n\t"
      "leal 0x4(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c12140]\n\t"
      "leal -0xe8(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c12170]\n\t"
      "fcoms 0x25337c\n\t"
      "addl $0x10, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00038e60_46\n\t"
      "pushl $0x40490fdb\n\t"
      "fstp %%st(0)\n\t"
      "pushl $0xc0490fdb\n\t"
      "call *%[c121e0]\n\t"
      "fld %%st(0)\n\t"
      "fcos\n\t"
      "movl -0x28(%%ebp), %%ecx\n\t"
      "addl $0x24, %%ecx\n\t"
      "movl (%%ecx), %%edi\n\t"
      "leal 0x20(%%esi), %%eax\n\t"
      "movl %%eax, %%edx\n\t"
      "movl %%edi, (%%edx)\n\t"
      "movl 0x4(%%ecx), %%edi\n\t"
      "movl %%edi, 0x4(%%edx)\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "movl %%ecx, 0x8(%%edx)\n\t"
      "leal -0x24(%%ebp), %%edx\n\t"
      "fstps 0x4(%%esp)\n\t"
      "fsin\n\t"
      "fstps (%%esp)\n\t"
      "pushl %%edx\n\t"
      "jmp .LFUN_00038e60_47\n\t"
      ".LFUN_00038e60_46:\n\t"
      "fsqrt\n\t"
      "fdivrs 0x253398\n\t"
      "fmuls 0x256980\n\t"
      "fstps -0x30(%%ebp)\n\t"
      "movl -0x30(%%ebp), %%eax\n\t"
      "flds -0x30(%%ebp)\n\t"
      "pushl %%eax\n\t"
      "fchs\n\t"
      "pushl %%ecx\n\t"
      "fstps (%%esp)\n\t"
      "call *%[c121e0]\n\t"
      "fld %%st(0)\n\t"
      "movl -0xe8(%%ebp), %%edx\n\t"
      "fcos\n\t"
      "leal 0x20(%%esi), %%eax\n\t"
      "movl %%eax, %%ecx\n\t"
      "movl %%edx, (%%ecx)\n\t"
      "movl -0xe4(%%ebp), %%edx\n\t"
      "movl %%edx, 0x4(%%ecx)\n\t"
      "movl -0xe0(%%ebp), %%edx\n\t"
      "movl %%edx, 0x8(%%ecx)\n\t"
      "leal -0x24(%%ebp), %%ecx\n\t"
      "fstps 0x4(%%esp)\n\t"
      "fsin\n\t"
      "fstps (%%esp)\n\t"
      "pushl %%ecx\n\t"
      ".LFUN_00038e60_47:\n\t"
      "pushl %%eax\n\t"
      "call *%[rots]\n\t"
      "movl $0, 0x2c(%%esi)\n\t"
      ".LFUN_00038e60_48:\n\t"
      "addl $0x10, %%esp\n\t"
      ".LFUN_00038e60_49:\n\t"
      "movb 0x1d(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00038e60_51\n\t"
      "movb 0x1c(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00038e60_50\n\t"
      "pushl $1\n\t"
      "pushl $0x1ed\n\t"
      "pushl $0x256954\n\t"
      "pushl $0x256908\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00038e60_50:\n\t"
      "movb 0x1d(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00038e60_74\n\t"
      ".LFUN_00038e60_51:\n\t"
      "leal 0x20(%%esi), %%edx\n\t"
      "movl (%%edx), %%eax\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "movl 0x4(%%edx), %%ecx\n\t"
      "movl %%ecx, -0xc(%%ebp)\n\t"
      "movl 0x8(%%edx), %%edx\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "movl %%edx, -0x8(%%ebp)\n\t"
      "jmp .LFUN_00038e60_61\n\t"
      ".LFUN_00038e60_52:\n\t"
      "movl -0x30(%%ebp), %%eax\n\t"
      "movl 0x5ab23c, %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "flds 0xbc(%%eax)\n\t"
      "fsubs 0x4(%%esi)\n\t"
      "addl $0xbc, %%eax\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $5, -0x18(%%ebp)\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "flds 0x4(%%eax)\n\t"
      "fsubs 0x8(%%esi)\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "flds 0x8(%%eax)\n\t"
      "fsubs 0xc(%%esi)\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "jne .LFUN_00038e60_53\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fchs\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fchs\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fchs\n\t"
      "fstps -0x8(%%ebp)\n\t"
      ".LFUN_00038e60_53:\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "jmp .LFUN_00038e60_61\n\t"
      ".LFUN_00038e60_54:\n\t"
      "testb $8, %%cl\n\t"
      "jne .LFUN_00038e60_55\n\t"
      "pushl $1\n\t"
      "pushl $0x204\n\t"
      "pushl $0x256954\n\t"
      "pushl $0x2568c4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00038e60_55:\n\t"
      "testb $1, 0x21(%%esi)\n\t"
      "je .LFUN_00038e60_58\n\t"
      "movswl 0x24(%%esi), %%eax\n\t"
      "cmpl $2, %%eax\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "jl .LFUN_00038e60_56\n\t"
      "cmpl $3, %%eax\n\t"
      "jg .LFUN_00038e60_56\n\t"
      "leal -0x10(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal 0x28(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x24(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[cross]\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpw $3, 0x24(%%esi)\n\t"
      "jmp .LFUN_00038e60_57\n\t"
      ".LFUN_00038e60_56:\n\t"
      "leal 0x28(%%esi), %%edx\n\t"
      "movl (%%edx), %%eax\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "movl 0x4(%%edx), %%ecx\n\t"
      "movl %%ecx, -0xc(%%ebp)\n\t"
      "movl 0x8(%%edx), %%edx\n\t"
      "movl %%edx, -0x8(%%ebp)\n\t"
      "cmpw $1, 0x24(%%esi)\n\t"
      ".LFUN_00038e60_57:\n\t"
      "jne .LFUN_00038e60_58\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fchs\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fchs\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fchs\n\t"
      "fstps -0x8(%%ebp)\n\t"
      ".LFUN_00038e60_58:\n\t"
      "movb 0x21(%%esi), %%al\n\t"
      "testb $4, %%al\n\t"
      "je .LFUN_00038e60_60\n\t"
      "testb $8, %%al\n\t"
      "jne .LFUN_00038e60_59\n\t"
      "cmpw $0, 0x24(%%esi)\n\t"
      "jne .LFUN_00038e60_59\n\t"
      "movl -0x64(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1a9ad0]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00038e60_59\n\t"
      "movb 0x21(%%esi), %%al\n\t"
      "orb $0x10, 0x2(%%esi)\n\t"
      "orb $8, %%al\n\t"
      "movb %%al, 0x21(%%esi)\n\t"
      ".LFUN_00038e60_59:\n\t"
      "movl -0x28(%%ebp), %%ecx\n\t"
      "addl $0x24, %%ecx\n\t"
      "movl (%%ecx), %%edx\n\t"
      "movl %%edx, -0x10(%%ebp)\n\t"
      "movl 0x4(%%ecx), %%eax\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "jmp .LFUN_00038e60_61\n\t"
      ".LFUN_00038e60_60:\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00038e60_74\n\t"
      ".LFUN_00038e60_61:\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fmuls -0x8(%%ebp)\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fmuls -0xc(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fmuls -0x10(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fsqrt\n\t"
      "fld %%st(0)\n\t"
      "fabs\n\t"
      "fcompl 0x2533d0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .LFUN_00038e60_62\n\t"
      "fdivrs 0x2533c8\n\t"
      "flds -0x10(%%ebp)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "flds -0xc(%%ebp)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "flds -0x8(%%ebp)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fstps -0x8(%%ebp)\n\t"
      ".LFUN_00038e60_62:\n\t"
      "fstp %%st(0)\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fmuls -0x8(%%ebp)\n\t"
      "flds -0x20(%%ebp)\n\t"
      "fmuls -0xc(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds -0x24(%%ebp)\n\t"
      "fmuls -0x10(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fcoms 0x2555d0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00038e60_63\n\t"
      "movb $1, -0x29(%%ebp)\n\t"
      ".LFUN_00038e60_63:\n\t"
      "fcomps 0x2568c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00038e60_64\n\t"
      "movl -0x28(%%ebp), %%edx\n\t"
      "addl $0x24, %%edx\n\t"
      "movl (%%edx), %%eax\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "movl 0x4(%%edx), %%ecx\n\t"
      "movl %%ecx, -0xc(%%ebp)\n\t"
      "movl 0x8(%%edx), %%edx\n\t"
      "movl %%edx, -0x8(%%ebp)\n\t"
      "jmp .LFUN_00038e60_65\n\t"
      ".LFUN_00038e60_64:\n\t"
      "flds -0x20(%%ebp)\n\t"
      "leal -0x10(%%ebp), %%eax\n\t"
      "fmuls -0x8(%%ebp)\n\t"
      "pushl %%eax\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fmuls -0xc(%%ebp)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fmuls -0x10(%%ebp)\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fmuls -0x24(%%ebp)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fmuls -0x24(%%ebp)\n\t"
      "flds -0x20(%%ebp)\n\t"
      "fmuls -0x10(%%ebp)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fld %%st(1)\n\t"
      "fmuls -0x1c(%%ebp)\n\t"
      "fld %%st(1)\n\t"
      "fmuls -0x20(%%ebp)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "fmuls -0x24(%%ebp)\n\t"
      "flds -0x1c(%%ebp)\n\t"
      ".byte 0xd8, 0xcb\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "flds -0x20(%%ebp)\n\t"
      ".byte 0xd8, 0xca\n\t"
      "fxch %%st(1)\n\t"
      "fmuls -0x24(%%ebp)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "call *%[norm]\n\t"
      "fcomps 0x2533c0\n\t"
      "addl $4, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .LFUN_00038e60_65\n\t"
      "movl -0x28(%%ebp), %%ecx\n\t"
      "addl $0x24, %%ecx\n\t"
      "movl (%%ecx), %%edx\n\t"
      "movl %%edx, -0x10(%%ebp)\n\t"
      "movl 0x4(%%ecx), %%eax\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      ".LFUN_00038e60_65:\n\t"
      "cmpw $6, -0x18(%%ebp)\n\t"
      "je .LFUN_00038e60_73\n\t"
      "flds -0x10(%%ebp)\n\t"
      "movl -0x5c(%%ebp), %%ebx\n\t"
      "fmuls 0x2549d4\n\t"
      "xorl %%edi, %%edi\n\t"
      "cmpw %%di, 0x2(%%ebx)\n\t"
      "movl $0, -0x34(%%ebp)\n\t"
      "fsubrs 0x4(%%esi)\n\t"
      "fstps -0x9c(%%ebp)\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fmuls 0x2549d4\n\t"
      "fsubrs 0x8(%%esi)\n\t"
      "fstps -0x98(%%ebp)\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fmuls 0x2549d4\n\t"
      "fsubrs 0xc(%%esi)\n\t"
      "fstps -0x94(%%ebp)\n\t"
      "flds -0x20(%%ebp)\n\t"
      "fmuls -0x8(%%ebp)\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fmuls -0xc(%%ebp)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0x90(%%ebp)\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fmuls -0x10(%%ebp)\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fmuls -0x24(%%ebp)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0x8c(%%ebp)\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fmuls -0x24(%%ebp)\n\t"
      "flds -0x20(%%ebp)\n\t"
      "fmuls -0x10(%%ebp)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0x88(%%ebp)\n\t"
      "jle .LFUN_00038e60_73\n\t"
      "jmp .LFUN_00038e60_66\n\t"
      "leal (%%ebx), %%ebx\n\t"
      ".LFUN_00038e60_66:\n\t"
      "cmpw -0x4c(%%ebp), %%di\n\t"
      "je .LFUN_00038e60_69\n\t"
      "movl 0x63259c, %%ecx\n\t"
      "movswl %%di, %%edx\n\t"
      "movl 0x58(%%ebx,%%edx,4), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "addl $4, %%eax\n\t"
      "addl $8, %%esp\n\t"
      "flds (%%eax)\n\t"
      "fsubs -0x9c(%%ebp)\n\t"
      "fstps -0x58(%%ebp)\n\t"
      "flds 0x4(%%eax)\n\t"
      "fsubs -0x98(%%ebp)\n\t"
      "fstps -0x54(%%ebp)\n\t"
      "flds 0x8(%%eax)\n\t"
      "fsubs -0x94(%%ebp)\n\t"
      "fsts -0x50(%%ebp)\n\t"
      "fmuls -0x50(%%ebp)\n\t"
      "flds -0x54(%%ebp)\n\t"
      "fmuls -0x54(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds -0x58(%%ebp)\n\t"
      "fmuls -0x58(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fcoms 0x253dc8\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00038e60_68\n\t"
      "flds -0x50(%%ebp)\n\t"
      "fmuls -0x8(%%ebp)\n\t"
      "flds -0x54(%%ebp)\n\t"
      "fmuls -0xc(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds -0x58(%%ebp)\n\t"
      "fmuls -0x10(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fxch %%st(1)\n\t"
      "fsqrt\n\t"
      "fxch %%st(1)\n\t"
      "fxch %%st(1)\n\t"
      ".byte 0xde, 0xf9\n\t"
      "fcoms 0x253398\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00038e60_68\n\t"
      "flds -0x50(%%ebp)\n\t"
      "fmuls -0x88(%%ebp)\n\t"
      "flds -0x54(%%ebp)\n\t"
      "fmuls -0x8c(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds -0x58(%%ebp)\n\t"
      "fmuls -0x90(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fcomps 0x2533c0\n\t"
      "fsubs 0x253398\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "fmuls 0x253398\n\t"
      "jne .LFUN_00038e60_67\n\t"
      "fsubrs -0x34(%%ebp)\n\t"
      "fstps -0x34(%%ebp)\n\t"
      "jmp .LFUN_00038e60_69\n\t"
      ".LFUN_00038e60_67:\n\t"
      "fadds -0x34(%%ebp)\n\t"
      "fstps -0x34(%%ebp)\n\t"
      "jmp .LFUN_00038e60_69\n\t"
      ".LFUN_00038e60_68:\n\t"
      "fstp %%st(0)\n\t"
      ".LFUN_00038e60_69:\n\t"
      "incl %%edi\n\t"
      "cmpw 0x2(%%ebx), %%di\n\t"
      "jl .LFUN_00038e60_66\n\t"
      "flds -0x34(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .LFUN_00038e60_73\n\t"
      "flds -0x34(%%ebp)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00038e60_70\n\t"
      "flds 0x2568bc\n\t"
      "jmp .LFUN_00038e60_72\n\t"
      ".LFUN_00038e60_70:\n\t"
      "flds -0x34(%%ebp)\n\t"
      "fcomps 0x255e94\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00038e60_71\n\t"
      "flds 0x2568b8\n\t"
      "jmp .LFUN_00038e60_72\n\t"
      ".LFUN_00038e60_71:\n\t"
      "flds -0x34(%%ebp)\n\t"
      "fmuls 0x2568bc\n\t"
      ".LFUN_00038e60_72:\n\t"
      "fld %%st(0)\n\t"
      "subl $8, %%esp\n\t"
      "fcos\n\t"
      "leal -0x24(%%ebp), %%edx\n\t"
      "leal -0x10(%%ebp), %%eax\n\t"
      "fstps 0x4(%%esp)\n\t"
      "fsin\n\t"
      "fstps (%%esp)\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[rots]\n\t"
      "addl $0x10, %%esp\n\t"
      ".LFUN_00038e60_73:\n\t"
      "flds -0x20(%%ebp)\n\t"
      "fmuls -0x8(%%ebp)\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fmuls -0xc(%%ebp)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0x44(%%ebp)\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fmuls -0x10(%%ebp)\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fmuls -0x24(%%ebp)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0x40(%%ebp)\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fmuls -0x24(%%ebp)\n\t"
      "flds -0x20(%%ebp)\n\t"
      "fmuls -0x10(%%ebp)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fsts -0x3c(%%ebp)\n\t"
      "fmuls -0x3c(%%ebp)\n\t"
      "flds -0x40(%%ebp)\n\t"
      "fmuls -0x40(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds -0x44(%%ebp)\n\t"
      "fmuls -0x44(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fsqrt\n\t"
      "fld %%st(0)\n\t"
      "fabs\n\t"
      "fcompl 0x2533d0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .LFUN_00038e60_75\n\t"
      "flds 0x2533c8\n\t"
      ".byte 0xd8, 0xf1\n\t"
      "flds -0x44(%%ebp)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fstps -0x44(%%ebp)\n\t"
      "flds -0x40(%%ebp)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fstps -0x40(%%ebp)\n\t"
      "flds -0x3c(%%ebp)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fstps -0x3c(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .LFUN_00038e60_76\n\t"
      "flds -0x40(%%ebp)\n\t"
      "fmuls -0x1c(%%ebp)\n\t"
      "flds -0x3c(%%ebp)\n\t"
      "fmuls -0x20(%%ebp)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "flds -0x3c(%%ebp)\n\t"
      "fmuls -0x24(%%ebp)\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fmuls -0x44(%%ebp)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "flds -0x20(%%ebp)\n\t"
      "fmuls -0x44(%%ebp)\n\t"
      "flds -0x40(%%ebp)\n\t"
      "fmuls -0x24(%%ebp)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0x8(%%ebp)\n\t"
      ".LFUN_00038e60_74:\n\t"
      "movw 0x2(%%esi), %%cx\n\t"
      "testb $0x10, %%cl\n\t"
      "je .LFUN_00038e60_77\n\t"
      "movb $1, %%al\n\t"
      "jmp .LFUN_00038e60_81\n\t"
      ".LFUN_00038e60_75:\n\t"
      "fstp %%st(0)\n\t"
      ".LFUN_00038e60_76:\n\t"
      "movl -0x28(%%ebp), %%ecx\n\t"
      "addl $0x24, %%ecx\n\t"
      "movl (%%ecx), %%edx\n\t"
      "movl %%edx, -0x10(%%ebp)\n\t"
      "movl 0x4(%%ecx), %%eax\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "jmp .LFUN_00038e60_74\n\t"
      ".LFUN_00038e60_77:\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00038e60_80\n\t"
      "cmpb $0x2d, 0x19(%%esi)\n\t"
      "jb .LFUN_00038e60_80\n\t"
      "movw -0x4c(%%ebp), %%dx\n\t"
      "cmpw -0x70(%%ebp), %%dx\n\t"
      "jne .LFUN_00038e60_78\n\t"
      "movb $1, %%al\n\t"
      "jmp .LFUN_00038e60_81\n\t"
      ".LFUN_00038e60_78:\n\t"
      "movb -0x11(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00038e60_79\n\t"
      "movb $1, %%al\n\t"
      "jmp .LFUN_00038e60_81\n\t"
      ".LFUN_00038e60_79:\n\t"
      "movb -0x29(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "movb $1, %%al\n\t"
      "jne .LFUN_00038e60_81\n\t"
      ".LFUN_00038e60_80:\n\t"
      "movb -0x2b(%%ebp), %%al\n\t"
      ".LFUN_00038e60_81:\n\t"
      "testb $2, %%cl\n\t"
      "je .LFUN_00038e60_82\n\t"
      "movl -0x28(%%ebp), %%edi\n\t"
      "andb $1, %%cl\n\t"
      "shlb $2, %%cl\n\t"
      "movb %%cl, 0x239(%%edi)\n\t"
      "jmp .LFUN_00038e60_87\n\t"
      ".LFUN_00038e60_82:\n\t"
      "movb -0x11(%%ebp), %%dl\n\t"
      "testb %%dl, %%dl\n\t"
      "je .LFUN_00038e60_83\n\t"
      "movb 0x1a(%%esi), %%dl\n\t"
      "testb %%dl, %%dl\n\t"
      "jne .LFUN_00038e60_83\n\t"
      "orl $1, %%ecx\n\t"
      "jmp .LFUN_00038e60_84\n\t"
      ".LFUN_00038e60_83:\n\t"
      "andl $0xfffffffe, %%ecx\n\t"
      ".LFUN_00038e60_84:\n\t"
      "testb $1, %%cl\n\t"
      "movl -0x28(%%ebp), %%edi\n\t"
      "movw %%cx, 0x2(%%esi)\n\t"
      "je .LFUN_00038e60_86\n\t"
      "movl -0x48(%%ebp), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "movb $3, 0x239(%%edi)\n\t"
      "jne .LFUN_00038e60_85\n\t"
      "orl $0xffffffff, %%ecx\n\t"
      "movl %%ecx, 0x44c(%%edi)\n\t"
      "jmp .LFUN_00038e60_87\n\t"
      ".LFUN_00038e60_85:\n\t"
      "movl 0x18(%%ecx), %%ecx\n\t"
      "movl %%ecx, 0x44c(%%edi)\n\t"
      "jmp .LFUN_00038e60_87\n\t"
      ".LFUN_00038e60_86:\n\t"
      "movb $0, 0x239(%%edi)\n\t"
      ".LFUN_00038e60_87:\n\t"
      "negb %%al\n\t"
      "pushl $0x40\n\t"
      "pushl $0\n\t"
      "sbbl %%eax, %%eax\n\t"
      "andl $2, %%eax\n\t"
      "movl %%eax, %%esi\n\t"
      "leal -0xdc(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[memset]\n\t"
      "movb -0x38(%%ebp), %%cl\n\t"
      "movb -0x60(%%ebp), %%dl\n\t"
      "orl $0xffffffff, %%eax\n\t"
      "movw %%ax, -0xd8(%%ebp)\n\t"
      "movw %%ax, -0xd6(%%ebp)\n\t"
      "movw %%ax, -0xd4(%%ebp)\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "movw %%si, -0xda(%%ebp)\n\t"
      "movl $0, -0xc4(%%ebp)\n\t"
      "movb %%cl, -0xdc(%%ebp)\n\t"
      "movb %%dl, -0xdb(%%ebp)\n\t"
      "je .LFUN_00038e60_88\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "movl $0x3f800000, -0xd0(%%ebp)\n\t"
      "movl $0, -0xcc(%%ebp)\n\t"
      "movl $0, -0xc8(%%ebp)\n\t"
      "jmp .LFUN_00038e60_89\n\t"
      ".LFUN_00038e60_88:\n\t"
      "movl 0x31fc38, %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "movl %%ecx, -0xd0(%%ebp)\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl %%edx, -0xcc(%%ebp)\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "addl $0x24, %%edi\n\t"
      "movl %%eax, -0xc8(%%ebp)\n\t"
      "movl (%%edi), %%eax\n\t"
      "movl 0x4(%%edi), %%ecx\n\t"
      "movl 0x8(%%edi), %%edx\n\t"
      ".LFUN_00038e60_89:\n\t"
      "movl %%ecx, -0xbc(%%ebp)\n\t"
      "movl %%ecx, -0xb0(%%ebp)\n\t"
      "movl %%ecx, -0xa4(%%ebp)\n\t"
      "leal -0xdc(%%ebp), %%ecx\n\t"
      "movl %%edx, -0xb8(%%ebp)\n\t"
      "movl %%edx, -0xac(%%ebp)\n\t"
      "movl %%edx, -0xa0(%%ebp)\n\t"
      "movl -0x64(%%ebp), %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "movl %%eax, -0xc0(%%ebp)\n\t"
      "movl %%eax, -0xb4(%%ebp)\n\t"
      "movl %%eax, -0xa8(%%ebp)\n\t"
      "call *%[c1af990]\n\t"
      "movl -0x4c(%%ebp), %%eax\n\t"
      "movl -0x5c(%%ebp), %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "incl %%eax\n\t"
      "cmpw 0x2(%%ecx), %%ax\n\t"
      "movl %%eax, -0x4c(%%ebp)\n\t"
      "jl .LFUN_00038e60_5\n\t"
      "popl %%ebx\n\t"
      ".LFUN_00038e60_90:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_00038e60_jt0:\n\t"
      ".long .LFUN_00038e60_20\n\t"
      ".long .LFUN_00038e60_21\n\t"
      ".long .LFUN_00038e60_29\n\t"
      ".long .LFUN_00038e60_25\n\t"
      ".long .LFUN_00038e60_29\n\t"
      ".long .LFUN_00038e60_22\n\t"
      ".long .LFUN_00038e60_23\n\t"
      ".long .LFUN_00038e60_29\n\t"
      ".long .LFUN_00038e60_29\n\t"
      ".long .LFUN_00038e60_26\n\t"
      ".long .LFUN_00038e60_26\n\t"
      ".text\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_00038e60_jt1:\n\t"
      ".long .LFUN_00038e60_41\n\t"
      ".long .LFUN_00038e60_41\n\t"
      ".long .LFUN_00038e60_41\n\t"
      ".long .LFUN_00038e60_52\n\t"
      ".long .LFUN_00038e60_52\n\t"
      ".long .LFUN_00038e60_54\n\t"
      ".text\n\t"
      :
      : [dget] "m"(b38e60_dget), [tag] "m"(b38e60_tag), [gseed] "m"(b38e60_gseed), [rrange] "m"(b38e60_rrange), [ftol] "m"(b38e60_ftol), [c10b2d0] "m"(b38e60_c10b2d0), [get] "m"(b38e60_get), [c64540] "m"(b38e60_c64540), [c64570] "m"(b38e60_c64570), [gtime] "m"(b38e60_gtime), [c1aa5c0] "m"(b38e60_c1aa5c0), [memset] "m"(b38e60_memset), [c38da0] "m"(b38e60_c38da0), [c121e0] "m"(b38e60_c121e0), [rots] "m"(b38e60_rots), [c38e00] "m"(b38e60_c38e00), [c12140] "m"(b38e60_c12140), [c12170] "m"(b38e60_c12170), [assert] "m"(b38e60_assert), [exitfn] "m"(b38e60_exitfn), [cross] "m"(b38e60_cross), [c1a9ad0] "m"(b38e60_c1a9ad0), [norm] "m"(b38e60_norm), [c1af990] "m"(b38e60_c1af990)
      : "memory");
}
#else
#error "FUN_00038e60: clang naked draft required"
#endif


/* FUN_00039c80 (0x39c80) — XBE naked draft (batch 69). */
#if defined(__clang__)
static void *(*const b39c80_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void *(*const b39c80_get)(int, int) = object_get_and_verify_type;
static char (*const b39c80_cf80a0)(float speed, float gravity, float *origin, float *target, int param_5, float *param_6, float *param_7, char param_8, float *aim_vector, float *param_10, float *param_11, float *param_12, float *param_13, float *param_14) = projectile_aim_ballistic;
static float (*const b39c80_mag)(float *) = magnitude3d;

__attribute__((naked, noinline))
void FUN_00039c80(int actor_handle __attribute__((unused)), int object_handle __attribute__((unused)), float speed __attribute__((unused)), float *out_velocity __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x30, %%esp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl 0x6325a4, %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, -0x1c(%%ebp)\n\t"
      "movl 0x28(%%eax), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_00039c80_12\n\t"
      "movl 0x6325a0, %%edx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "pushl %%edx\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%ebx\n\t"
      "xorl %%eax, %%eax\n\t"
      "addl $8, %%esp\n\t"
      "cmpw %%ax, 0x2(%%ebx)\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "jle .LFUN_00039c80_11\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_00039c80_1:\n\t"
      "movswl %%ax, %%esi\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "cmpl %%eax, 0x18(%%ebx,%%esi,4)\n\t"
      "jne .LFUN_00039c80_10\n\t"
      "pushl $3\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl 0x63259c, %%ecx\n\t"
      "movl %%eax, %%edi\n\t"
      "movl 0x58(%%ebx,%%esi,4), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%esi\n\t"
      "movw 0x2(%%esi), %%ax\n\t"
      "addl $0x10, %%esp\n\t"
      "testb $1, %%al\n\t"
      "je .LFUN_00039c80_5\n\t"
      "movl 0x14(%%esi), %%ecx\n\t"
      "cmpl $-1, %%ecx\n\t"
      "je .LFUN_00039c80_5\n\t"
      "movl 0x5ab23c, %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[dget]\n\t"
      "flds 0x10(%%ebp)\n\t"
      "fcomps 0x25698c\n\t"
      "movl %%eax, %%edi\n\t"
      "addl $8, %%esp\n\t"
      "movl $0x3d75c28f, -0x18(%%ebp)\n\t"
      "movl $0x3f4ccccd, -0x14(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .LFUN_00039c80_2\n\t"
      "movl $0x3df5c28f, 0x10(%%ebp)\n\t"
      ".LFUN_00039c80_2:\n\t"
      "leal -0xc(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x8(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "leal -0x30(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "leal -0x14(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "leal -0x18(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal 0xc8(%%edi), %%edx\n\t"
      "pushl %%edx\n\t"
      "addl $4, %%esi\n\t"
      "pushl %%esi\n\t"
      "pushl $0x3f800000\n\t"
      "pushl %%eax\n\t"
      "call *%[cf80a0]\n\t"
      "addl $0x38, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00039c80_10\n\t"
      "leal -0x30(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[mag]\n\t"
      "fcomps 0x2533c0\n\t"
      "addl $4, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .LFUN_00039c80_3\n\t"
      "movl -0x1c(%%ebp), %%edx\n\t"
      "addl $0x174, %%edx\n\t"
      "movl (%%edx), %%eax\n\t"
      "movl 0x4(%%edx), %%ecx\n\t"
      "movl 0x8(%%edx), %%edx\n\t"
      "movl %%eax, -0x30(%%ebp)\n\t"
      "leal -0x30(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl %%ecx, -0x2c(%%ebp)\n\t"
      "movl %%edx, -0x28(%%ebp)\n\t"
      "call *%[mag]\n\t"
      "fcomps 0x2533c0\n\t"
      "addl $4, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .LFUN_00039c80_3\n\t"
      "movl 0x31fc3c, %%ecx\n\t"
      "movl (%%ecx), %%edx\n\t"
      "movl %%edx, -0x30(%%ebp)\n\t"
      "movl 0x4(%%ecx), %%eax\n\t"
      "movl %%eax, -0x2c(%%ebp)\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "movl %%ecx, -0x28(%%ebp)\n\t"
      ".LFUN_00039c80_3:\n\t"
      "movb 0x130(%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00039c80_4\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fcomps 0x256988\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00039c80_4\n\t"
      "movl $0x3d99999a, -0x8(%%ebp)\n\t"
      ".LFUN_00039c80_4:\n\t"
      "flds -0x30(%%ebp)\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      "fmuls -0xc(%%ebp)\n\t"
      "fld %%st(0)\n\t"
      "fstps (%%ecx)\n\t"
      "flds -0x2c(%%ebp)\n\t"
      "fmuls -0xc(%%ebp)\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "flds -0x8(%%ebp)\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "fsts 0x8(%%ecx)\n\t"
      "movl %%edx, 0x4(%%ecx)\n\t"
      "fld %%st(0)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fmuls -0x4(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fld %%st(2)\n\t"
      ".byte 0xd8, 0xcb\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds 0x10(%%ebp)\n\t"
      "fmuls 0x10(%%ebp)\n\t"
      "fld %%st(1)\n\t"
      "fcompp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00039c80_8\n\t"
      "fsqrt\n\t"
      "fdivrs 0x10(%%ebp)\n\t"
      "fxch %%st(2)\n\t"
      ".byte 0xd8, 0xca\n\t"
      "fstps (%%ecx)\n\t"
      "flds -0x4(%%ebp)\n\t"
      ".byte 0xd8, 0xca\n\t"
      "fstps 0x4(%%ecx)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fstps 0x8(%%ecx)\n\t"
      "jmp .LFUN_00039c80_9\n\t"
      ".LFUN_00039c80_5:\n\t"
      "testb $8, %%al\n\t"
      "je .LFUN_00039c80_10\n\t"
      "testb $0x10, %%al\n\t"
      "je .LFUN_00039c80_10\n\t"
      "movb 0x21(%%esi), %%al\n\t"
      "testb $4, %%al\n\t"
      "je .LFUN_00039c80_7\n\t"
      "testb $0x10, %%al\n\t"
      "je .LFUN_00039c80_7\n\t"
      "movl 0x24(%%edi), %%eax\n\t"
      "movl 0x28(%%edi), %%ecx\n\t"
      "leal -0x24(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl %%eax, -0x24(%%ebp)\n\t"
      "movl %%ecx, -0x20(%%ebp)\n\t"
      "call *%[mag]\n\t"
      "fcomps 0x2533c0\n\t"
      "addl $4, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .LFUN_00039c80_6\n\t"
      "movl 0x30(%%edi), %%eax\n\t"
      "movl 0x34(%%edi), %%ecx\n\t"
      "leal -0x24(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl %%eax, -0x24(%%ebp)\n\t"
      "movl %%ecx, -0x20(%%ebp)\n\t"
      "call *%[mag]\n\t"
      "fcomps 0x2533c0\n\t"
      "addl $4, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .LFUN_00039c80_6\n\t"
      "movl 0x31fc0c, %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl %%ecx, -0x24(%%ebp)\n\t"
      "movl %%edx, -0x20(%%ebp)\n\t"
      ".LFUN_00039c80_6:\n\t"
      "flds 0x2c(%%esi)\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "flds -0x20(%%ebp)\n\t"
      "fmuls 0x28(%%esi)\n\t"
      "flds -0x24(%%ebp)\n\t"
      "fmuls 0x28(%%esi)\n\t"
      "fstps (%%eax)\n\t"
      "fstps 0x4(%%eax)\n\t"
      "fstps 0x8(%%eax)\n\t"
      ".LFUN_00039c80_7:\n\t"
      "andb $0xef, 0x2(%%esi)\n\t"
      "jmp .LFUN_00039c80_10\n\t"
      ".LFUN_00039c80_8:\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      ".LFUN_00039c80_9:\n\t"
      "fstp %%st(0)\n\t"
      ".LFUN_00039c80_10:\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "incl %%eax\n\t"
      "cmpw 0x2(%%ebx), %%ax\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "jl .LFUN_00039c80_1\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      ".LFUN_00039c80_11:\n\t"
      "popl %%ebx\n\t"
      ".LFUN_00039c80_12:\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [dget] "m"(b39c80_dget), [get] "m"(b39c80_get), [cf80a0] "m"(b39c80_cf80a0), [mag] "m"(b39c80_mag)
      : "memory");
}
#else
#error "FUN_00039c80: clang naked draft required"
#endif


/* FUN_00039f30 (0x39f30) — XBE naked draft (batch 69). */
#if defined(__clang__)
static void *(*const b39f30_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void *(*const b39f30_tag)(int, int) = tag_get;
static char (*const b39f30_c1dab0)(int actor_handle) = actor_action_handle_initial_action;
static char (*const b39f30_c1daf0)(int actor_handle) = actor_action_handle_pending_command_list;
static char (*const b39f30_c1db90)(int actor_handle, short type) = actor_action_handle_surprise;
static char (*const b39f30_c1ca90)(int actor_handle) = actor_action_deny_transition;
static int (*const b39f30_c1c5a0)(int actor_handle) = actor_action_handle_panic_from_surprise;
static char (*const b39f30_c1c660)(int actor_handle) = actor_action_handle_panic_from_damage;
static int (*const b39f30_c1c7f0)(int actor_handle) = actor_action_handle_panic_from_attached_projectiles;
static char (*const b39f30_c1c880)(int actor_handle) = actor_action_handle_panic_from_attached_melee_attackers;
static int (*const b39f30_c1c750)(int actor_handle) = actor_action_handle_panic_from_burning_to_death;
static char (*const b39f30_c1dd40)(int actor_handle, short param_2, char param_3, short param_4) = actor_action_handle_panic_transition;
static char (*const b39f30_c204f0)(int actor_handle) = actor_action_handle_combat_transition;
static char (*const b39f30_c1e700)(int actor_handle, char param2, int param3) = actor_action_handle_active_cover_seeking;
static char (*const b39f30_c1dfa0)(int actor_handle) = actor_action_handle_vehicle_entry;
static char (*const b39f30_c1cb70)(int actor_handle) = actor_action_handle_vehicle_exit;
static char (*const b39f30_c20990)(int actor_handle) = FUN_00020990;
static char (*const b39f30_c1f770)(int actor_handle, int param2, int param3) = actor_action_handle_combat_status;
static char (*const b39f30_c1f920)(int actor_handle) = actor_action_handle_combat_failure;
static char (*const b39f30_c20670)(int actor_handle) = actor_action_handle_evasion;
static char (*const b39f30_c1cf10)(int actor_handle, short min_state, short max_state) = actor_action_can_stop_guarding;
static char (*const b39f30_c1f6e0)(int actor_handle) = actor_action_handle_done_fleeing;
static char (*const b39f30_c1f9a0)(int actor_handle) = actor_action_handle_exit_pursuit;
static int (*const b39f30_c1cfa0)(int actor_handle, int flag) = actor_action_can_stop_conversing;

__attribute__((naked, noinline))
void FUN_00039f30(int actor_handle __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl 0x6325a4, %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%edi\n\t"
      "movl 0x58(%%edi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x61637472\n\t"
      "call *%[tag]\n\t"
      "pushl %%esi\n\t"
      "movl %%eax, %%ebx\n\t"
      "call *%[c1dab0]\n\t"
      "pushl %%esi\n\t"
      "call *%[c1daf0]\n\t"
      "pushl $1\n\t"
      "pushl %%esi\n\t"
      "call *%[c1db90]\n\t"
      "pushl %%esi\n\t"
      "call *%[c1ca90]\n\t"
      "addl $0x24, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00039f30_1\n\t"
      "pushl %%esi\n\t"
      "call *%[c1c5a0]\n\t"
      "pushl %%esi\n\t"
      "call *%[c1c660]\n\t"
      "pushl %%esi\n\t"
      "call *%[c1c7f0]\n\t"
      "pushl %%esi\n\t"
      "call *%[c1c880]\n\t"
      "pushl %%esi\n\t"
      "call *%[c1c750]\n\t"
      "pushl $4\n\t"
      "pushl $0\n\t"
      "pushl $1\n\t"
      "pushl %%esi\n\t"
      "call *%[c1dd40]\n\t"
      "pushl %%esi\n\t"
      "call *%[c204f0]\n\t"
      "pushl $1\n\t"
      "pushl $1\n\t"
      "pushl %%esi\n\t"
      "call *%[c1e700]\n\t"
      "pushl %%esi\n\t"
      "call *%[c1dfa0]\n\t"
      "pushl %%esi\n\t"
      "call *%[c1cb70]\n\t"
      "pushl %%esi\n\t"
      "call *%[c20990]\n\t"
      "addl $0x40, %%esp\n\t"
      ".LFUN_00039f30_1:\n\t"
      "movswl 0x6c(%%edi), %%eax\n\t"
      "addl $-3, %%eax\n\t"
      "cmpl $0xa, %%eax\n\t"
      "ja .LFUN_00039f30_15\n\t"
      "jmp *.LFUN_00039f30_jt(,%%eax,4)\n\t"
      ".LFUN_00039f30_2:\n\t"
      "pushl $0\n\t"
      "pushl $1\n\t"
      "pushl %%esi\n\t"
      "call *%[c1f770]\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00039f30_15\n\t"
      "pushl %%esi\n\t"
      "call *%[c1f920]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00039f30_15\n\t"
      "pushl %%esi\n\t"
      "call *%[c20670]\n\t"
      "addl $4, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00039f30_3:\n\t"
      "movb 0xa4(%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00039f30_7\n\t"
      "movb 0xa5(%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00039f30_7\n\t"
      "movb 0xa6(%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00039f30_7\n\t"
      "cmpw $4, 0x6e(%%edi)\n\t"
      "jl .LFUN_00039f30_4\n\t"
      "flds 0x2e0(%%ebx)\n\t"
      "jmp .LFUN_00039f30_5\n\t"
      ".LFUN_00039f30_4:\n\t"
      "flds 0x2e4(%%ebx)\n\t"
      ".LFUN_00039f30_5:\n\t"
      "fcomps 0x1bc(%%edi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00039f30_6\n\t"
      "movb $1, 0xa4(%%edi)\n\t"
      "movw $0x1e, 0xa8(%%edi)\n\t"
      "jmp .LFUN_00039f30_7\n\t"
      ".LFUN_00039f30_6:\n\t"
      "movb $0, 0xa4(%%edi)\n\t"
      "movw $0, 0xa8(%%edi)\n\t"
      ".LFUN_00039f30_7:\n\t"
      "pushl $0\n\t"
      "pushl $6\n\t"
      "pushl $3\n\t"
      "pushl %%esi\n\t"
      "call *%[c1cf10]\n\t"
      "addl $0xc, %%esp\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[c1f770]\n\t"
      "addl $0xc, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00039f30_8:\n\t"
      "movb 0xaa(%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00039f30_14\n\t"
      "pushl %%esi\n\t"
      "call *%[c1f6e0]\n\t"
      "addl $4, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00039f30_9:\n\t"
      "pushl $0\n\t"
      "pushl $1\n\t"
      "pushl %%esi\n\t"
      "call *%[c1f770]\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00039f30_15\n\t"
      "pushl %%esi\n\t"
      "call *%[c1f9a0]\n\t"
      "addl $4, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00039f30_10:\n\t"
      "xorl %%edx, %%edx\n\t"
      "movb 0xa1(%%edi), %%dl\n\t"
      "xorl %%eax, %%eax\n\t"
      "movb 0x9e(%%edi), %%al\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[c1f770]\n\t"
      "addl $0xc, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00039f30_11:\n\t"
      "movb 0xa0(%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00039f30_12\n\t"
      "cmpl $-1, 0x1dc(%%edi)\n\t"
      "je .LFUN_00039f30_12\n\t"
      "xorl %%eax, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[c1cfa0]\n\t"
      "addl $4, %%esp\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[c1f770]\n\t"
      "addl $0xc, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00039f30_12:\n\t"
      "movl $1, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[c1cfa0]\n\t"
      "addl $4, %%esp\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[c1f770]\n\t"
      "addl $0xc, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00039f30_13:\n\t"
      "cmpw $0, 0x280(%%edi)\n\t"
      "jne .LFUN_00039f30_15\n\t"
      ".LFUN_00039f30_14:\n\t"
      "pushl $1\n\t"
      "pushl $1\n\t"
      "pushl %%esi\n\t"
      "call *%[c1f770]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_00039f30_15:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_00039f30_jt:\n\t"
      ".long .LFUN_00039f30_2\n\t"
      ".long .LFUN_00039f30_8\n\t"
      ".long .LFUN_00039f30_9\n\t"
      ".long .LFUN_00039f30_3\n\t"
      ".long .LFUN_00039f30_9\n\t"
      ".long .LFUN_00039f30_9\n\t"
      ".long .LFUN_00039f30_15\n\t"
      ".long .LFUN_00039f30_2\n\t"
      ".long .LFUN_00039f30_10\n\t"
      ".long .LFUN_00039f30_11\n\t"
      ".long .LFUN_00039f30_13\n\t"
      ".text\n\t"
      :
      : [dget] "m"(b39f30_dget), [tag] "m"(b39f30_tag), [c1dab0] "m"(b39f30_c1dab0), [c1daf0] "m"(b39f30_c1daf0), [c1db90] "m"(b39f30_c1db90), [c1ca90] "m"(b39f30_c1ca90), [c1c5a0] "m"(b39f30_c1c5a0), [c1c660] "m"(b39f30_c1c660), [c1c7f0] "m"(b39f30_c1c7f0), [c1c880] "m"(b39f30_c1c880), [c1c750] "m"(b39f30_c1c750), [c1dd40] "m"(b39f30_c1dd40), [c204f0] "m"(b39f30_c204f0), [c1e700] "m"(b39f30_c1e700), [c1dfa0] "m"(b39f30_c1dfa0), [c1cb70] "m"(b39f30_c1cb70), [c20990] "m"(b39f30_c20990), [c1f770] "m"(b39f30_c1f770), [c1f920] "m"(b39f30_c1f920), [c20670] "m"(b39f30_c20670), [c1cf10] "m"(b39f30_c1cf10), [c1f6e0] "m"(b39f30_c1f6e0), [c1f9a0] "m"(b39f30_c1f9a0), [c1cfa0] "m"(b39f30_c1cfa0)
      : "memory");
}
#else
#error "FUN_00039f30: clang naked draft required"
#endif


/* FUN_0003a190 (0x3a190) — actor action state-machine tick (berserking
 * variant). No tag_get. Preamble: datum_get, initial_action,
 * pending_command_list, handle_surprise(1), deny_transition. If deny==false:
 * panic_from_damage, panic_from_attached (2x), panic_from_burning,
 * panic_transition(1,0,0xe), berserking_from_damage, berserk_transition(type),
 * combat_transition, vehicle_entry/exit, grenade_throwing, FUN_00020990. Type =
 * actor[0x20a]>2?5:3. Switch on actor+0x6c cases: 3/10 →
 * status+failure+evasion; 6 → stop_guarding; 4 → aa/done_fleeing; 5/7/8 →
 * status+exit_pursuit; 9 → a5/a6 flags; 11 → status(9e,a1); 12 →
 * can_stop_conversing; 13 → a280/status(1,1). */
void FUN_0003a190(int actor_handle)
{
  char *actor;
  char cVar1;
  int uVar3;
  unsigned char bVar1;
  unsigned char bVar2;

  actor = (char *)datum_get(actor_data, actor_handle);
  actor_action_handle_initial_action(actor_handle);
  actor_action_handle_pending_command_list(actor_handle);
  actor_action_handle_surprise(actor_handle, 1);
  cVar1 = actor_action_deny_transition(actor_handle);
  if (cVar1 == '\0') {
    actor_action_handle_panic_from_damage(actor_handle);
    actor_action_handle_panic_from_attached_projectiles(actor_handle);
    actor_action_handle_panic_from_attached_melee_attackers(actor_handle);
    actor_action_handle_panic_from_burning_to_death(actor_handle);
    actor_action_handle_panic_transition(actor_handle, 1, 0, 0xe);
    actor_action_handle_berserking_from_damage(actor_handle);
    actor_action_handle_berserk_transition(
      actor_handle, (signed char)actor[0x20a] > 2 ? 5 : 3);
    actor_action_handle_combat_transition(actor_handle);
    actor_action_handle_vehicle_entry(actor_handle);
    actor_action_handle_vehicle_exit(actor_handle);
    actor_action_handle_grenade_throwing(actor_handle);
    FUN_00020990(actor_handle);
  }
  switch (*(short *)(actor + 0x6c)) {
  case 3:
  case 10:
    cVar1 = actor_action_handle_combat_status(actor_handle, 1, 0);
    if (cVar1 != '\0') {
      return;
    }
    cVar1 = actor_action_handle_combat_failure(actor_handle);
    if (cVar1 != '\0') {
      return;
    }
    actor_action_handle_evasion(actor_handle);
    return;
  case 6:
    uVar3 = actor_action_can_stop_guarding(actor_handle, 3, 6);
    actor_action_handle_combat_status(actor_handle, uVar3, 0);
    return;
  case 4:
    if (*(char *)(actor + 0xaa) != '\0') {
      actor_action_handle_combat_status(actor_handle, 1, 1);
      return;
    }
    actor_action_handle_done_fleeing(actor_handle);
    return;
  case 5:
  case 7:
  case 8:
    cVar1 = actor_action_handle_combat_status(actor_handle, 1, 0);
    if (cVar1 != '\0') {
      return;
    }
    actor_action_handle_exit_pursuit(actor_handle);
    return;
  case 9:
    if (*(char *)(actor + 0xa5) != '\0') {
      actor_action_handle_combat_status(actor_handle, 1, 1);
      return;
    }
    if (*(char *)(actor + 0xa6) == '\0') {
      return;
    }
    actor_action_handle_combat_status(actor_handle, 1, 1);
    return;
  case 11:
    bVar2 = *(unsigned char *)(actor + 0xa1);
    bVar1 = *(unsigned char *)(actor + 0x9e);
    actor_action_handle_combat_status(actor_handle, bVar1, bVar2);
    return;
  case 12:
    if (*(char *)(actor + 0xa0) == '\0' && *(int *)(actor + 0x1dc) != -1) {
      uVar3 = actor_action_can_stop_conversing(actor_handle, 0);
      actor_action_handle_combat_status(actor_handle, uVar3, 0);
    } else {
      uVar3 = actor_action_can_stop_conversing(actor_handle, 1);
      actor_action_handle_combat_status(actor_handle, uVar3, 1);
    }
    return;
  case 13:
    if (*(short *)(actor + 0x280) != 0) {
      return;
    }
    actor_action_handle_combat_status(actor_handle, 1, 1);
    return;
  default:
    return;
  }
}

/* 0x3a3b0
 *
 * actor_action_handle_status_change
 *
 * Processes an actor's action status: handles initial action, pending command
 * lists, potential combat transitions, and status-dependent behavior based on
 * the actor's current action type (field +0x6c).
 */
void FUN_0003a3b0(int actor_handle)
{
  char *actor;
  char cVar1;

  actor = (char *)datum_get(actor_data, actor_handle);
  actor_action_handle_initial_action(actor_handle);
  actor_action_handle_pending_command_list(actor_handle);
  cVar1 = actor_action_deny_transition(actor_handle);
  if (cVar1 == '\0') {
    actor_action_handle_combat_transition(actor_handle);
  }
  switch (*(short *)(actor + 0x6c)) {
  case 3:
  case 4:
  case 6:
  case 10:
    cVar1 = actor_action_handle_combat_status(actor_handle, 1, 0);
    if (cVar1 == '\0') {
      actor_action_handle_combat_failure(actor_handle);
      return;
    }
    break;
  case 5:
  case 7:
  case 8:
    cVar1 = actor_action_handle_combat_status(actor_handle, 1, 0);
    if (cVar1 == '\0') {
      actor_action_handle_exit_pursuit(actor_handle);
      return;
    }
    break;
  case 11:
    actor_action_handle_combat_status(actor_handle,
                                      (int)*(unsigned char *)(actor + 0x9e),
                                      (int)*(unsigned char *)(actor + 0xa1));
    break;
  default:
    break;
  }
}

/* FUN_0003a480 (0x3a480) — actor action state-machine tick (combat-only,
 * no berserking/panic). Preamble: datum_get, initial_action,
 * pending_command_list, handle_surprise(1), deny_transition. If deny==false:
 * handle_combat_transition + FUN_00020990 only. Switch on actor+0x6c:
 * cases 3/10 → combat_status+failure+evasion; case 6 → guard check;
 * case 4 → aa-check+done_fleeing or combat_status(1,1);
 * cases 5/7/8 → pursuit; case 11 → combat_status(9e,a1); case 13 → a280;
 * case 12 → can_stop_conversing+combat_status(flag,flag). */
void FUN_0003a480(int actor_handle)
{
  char *actor;
  char cVar1;
  int uVar2;
  int uVar3;
  unsigned char bVar1;
  unsigned char bVar2;

  actor = (char *)datum_get(actor_data, actor_handle);
  actor_action_handle_initial_action(actor_handle);
  actor_action_handle_pending_command_list(actor_handle);
  actor_action_handle_surprise(actor_handle, 1);
  cVar1 = actor_action_deny_transition(actor_handle);
  if (cVar1 == '\0') {
    actor_action_handle_combat_transition(actor_handle);
    FUN_00020990(actor_handle);
  }
  switch (*(short *)(actor + 0x6c)) {
  case 3:
  case 10:
    cVar1 = actor_action_handle_combat_status(actor_handle, 1, 0);
    if (cVar1 != '\0') {
      return;
    }
    cVar1 = actor_action_handle_combat_failure(actor_handle);
    if (cVar1 != '\0') {
      return;
    }
    actor_action_handle_evasion(actor_handle);
    return;
  case 6:
    uVar3 = actor_action_can_stop_guarding(actor_handle, 3, 6);
    actor_action_handle_combat_status(actor_handle, uVar3, 0);
    return;
  case 4:
    if (*(char *)(actor + 0xaa) != '\0') {
      actor_action_handle_combat_status(actor_handle, 1, 1);
      return;
    }
    actor_action_handle_done_fleeing(actor_handle);
    return;
  case 5:
  case 7:
  case 8:
    cVar1 = actor_action_handle_combat_status(actor_handle, 1, 0);
    if (cVar1 != '\0') {
      return;
    }
    actor_action_handle_exit_pursuit(actor_handle);
    return;
  case 11:
    bVar2 = *(unsigned char *)(actor + 0xa1);
    bVar1 = *(unsigned char *)(actor + 0x9e);
    actor_action_handle_combat_status(actor_handle, bVar1, bVar2);
    return;
  case 13:
    if (*(short *)(actor + 0x280) != 0) {
      return;
    }
    actor_action_handle_combat_status(actor_handle, 1, 1);
    return;
  case 12:
    uVar3 = (*(char *)(actor + 0xa0) != '\0' || *(int *)(actor + 0x1dc) == -1) ?
              1 :
              0;
    uVar2 = actor_action_can_stop_conversing(actor_handle, uVar3);
    actor_action_handle_combat_status(actor_handle, uVar2, uVar3);
    return;
  default:
    return;
  }
}

void *FUN_0003a600(short actor_type /* @<ax> */)
{
  void **actor_type_definitions = (void **)0x2c86a8;
  char *def;

  if (actor_type < 0 || actor_type > 0xf) {
    display_assert("actor_type>=0 && actor_type<NUMBER_OF_ACTOR_TYPES",
                   "c:\\halo\\source\\ai\\actor_type_definitions.h", 0x2e, 1);
    system_exit(-1);
  }
  if (actor_type_definitions[actor_type] == 0) {
    display_assert("actor_type_definitions[actor_type]",
                   "c:\\halo\\source\\ai\\actor_type_definitions.h", 0x2f, 1);
    system_exit(-1);
  }
  def = (char *)actor_type_definitions[actor_type];
  if (*(int *)(def + 0) == 0) {
    display_assert("actor_type_definitions[actor_type]->name",
                   "c:\\halo\\source\\ai\\actor_type_definitions.h", 0x32, 1);
    system_exit(-1);
  }
  if (*(int *)(def + 0x14) == 0) {
    display_assert("actor_type_definitions[actor_type]->decide_action",
                   "c:\\halo\\source\\ai\\actor_type_definitions.h", 0x33, 1);
    system_exit(-1);
  }
  if (*(short *)(def + 6) > 2) {
    display_assert("actor_type_definitions[actor_type]->when_to_search_at_"
                   "target < NUMBER_OF_ACTOR_PURSUIT_SETTINGS",
                   "c:\\halo\\source\\ai\\actor_type_definitions.h", 0x35, 1);
    system_exit(-1);
  }
  if (*(short *)(def + 8) > 2) {
    display_assert("actor_type_definitions[actor_type]->when_to_pursue < "
                   "NUMBER_OF_ACTOR_PURSUIT_SETTINGS",
                   "c:\\halo\\source\\ai\\actor_type_definitions.h", 0x35, 1);
    system_exit(-1);
  }
  if (*(short *)(def + 10) > 2) {
    display_assert("actor_type_definitions[actor_type]->when_to_search_pursuit "
                   "< NUMBER_OF_ACTOR_PURSUIT_SETTINGS",
                   "c:\\halo\\source\\ai\\actor_type_definitions.h", 0x37, 1);
    system_exit(-1);
  }
  return actor_type_definitions[actor_type];
}

void FUN_0003a740(void)
{
  short i;
  for (i = 0; i < 0x10; i++) {
    FUN_0003a600(i);
  }
}

/* Return the name string for an actor type definition. */
const char *FUN_0003a760(int16_t actor_type)
{
  return *(const char **)FUN_0003a600(actor_type);
}

int16_t FUN_0003a770(int16_t actor_type)
{
  return *(int16_t *)((char *)FUN_0003a600(actor_type) + 4);
}

int16_t FUN_0003a790(int16_t actor_type)
{
  return *(int16_t *)((char *)FUN_0003a600(actor_type) + 6);
}

int16_t FUN_0003a7b0(int16_t actor_type)
{
  return *(int16_t *)((char *)FUN_0003a600(actor_type) + 8);
}

int16_t FUN_0003a7d0(int16_t actor_type)
{
  return *(int16_t *)((char *)FUN_0003a600(actor_type) + 10);
}

unsigned char FUN_0003a7f0(int16_t actor_type)
{
  return *(unsigned char *)((char *)FUN_0003a600(actor_type) + 12);
}

/* FUN_0003a800 (0x3a800) — actor_type_is_swarm
 * Returns the swarm flag byte (offset 0xd) from the actor type definition
 * for the given actor_type. Used to test whether an actor type uses swarm
 * control before dispatching swarm callbacks. */
int FUN_0003a800(int16_t actor_type)
{
  char *type_def;
  type_def = (char *)FUN_0003a600(actor_type);
  return (int)(unsigned char)type_def[0xd];
}

/* FUN_0003a810 (0x3a810) — actor_type_init_dispatch
 * Looks up the actor datum by handle, reads the actor_type field (int16_t at
 * offset 4), retrieves the actor type definition, and calls the type-specific
 * init callback (function pointer at type_def+0x10) if it is non-null.
 * Called at the end of actor_new (FUN_0003c410) to perform per-type
 * initialization of a newly allocated actor. */
void FUN_0003a810(int actor_handle)
{
  char *actor;
  char *type_def;
  void (*init_cb)(int);

  actor = (char *)datum_get(actor_data, actor_handle);
  type_def = (char *)FUN_0003a600(*(short *)(actor + 0x4));
  init_cb = *(void (**)(int))(type_def + 0x10);
  if (init_cb != NULL) {
    init_cb(actor_handle);
  }
}

/* Dispatch the actor-type-specific decide_action function for a given actor. */
void FUN_0003a840(int actor_handle)
{
  char *actor;
  void *type_def;

  actor = (char *)datum_get(actor_data, actor_handle);
  type_def = FUN_0003a600(*(short *)(actor + 4));

  if (*(int *)((char *)type_def + 0x14) == 0) {
    display_assert("actor_type_definition->decide_action",
                   "c:\\halo\\SOURCE\\ai\\actor_types.c", 0x81, 1);
    system_exit(-1);
  }
  (*(void (**)(int))((char *)type_def + 0x14))(actor_handle);
}

/* FUN_0003a8a0 (0x3a8a0) — actor_swarm_control_dispatch
 *
 * Dispatch the actor-type-specific swarm control function for a given actor.
 * Retrieves the actor datum, reads its actor_type (int16_t at offset 4),
 * looks up the actor type definition, asserts the definition describes a
 * swarm actor (byte at +0xd) and that the swarm_control function pointer
 * (at +0x18) is non-null, then calls it with actor_handle.
 *
 * Assert strings confirm source: c:\halo\SOURCE\ai\actor_types.c, lines
 * 0x8d–0x8e.
 *
 * Confirmed: datum_get(actor_data, actor_handle) at 0x3a8af.
 * Confirmed: MOV AX,[EAX+4] loads actor_type for @<ax> register call at
 * 0x3a8b4. Confirmed: FUN_0003a600(@<ax>) returns type_def pointer in EAX ->
 * ESI at 0x3a8bb. Confirmed: type_def->swarm (byte at +0xd) tested at
 * 0x3a8c2-0x3a8c7. Confirmed: type_def->swarm_control (int * at +0x18) tested
 * at 0x3a8e9-0x3a8ee. Confirmed: CALL dword ptr [ESI+0x18] dispatches
 * swarm_control(actor_handle) at 0x3a911. */
void FUN_0003a8a0(int actor_handle)
{
  char *actor;
  void *type_def;

  actor = (char *)datum_get(actor_data, actor_handle);
  type_def = FUN_0003a600(*(short *)(actor + 4));

  if (*(char *)((char *)type_def + 0xd) == 0) {
    display_assert("actor_type_definition->swarm",
                   "c:\\halo\\SOURCE\\ai\\actor_types.c", 0x8d, 1);
    system_exit(-1);
  }
  if (*(int *)((char *)type_def + 0x18) == 0) {
    display_assert("actor_type_definition->swarm_control",
                   "c:\\halo\\SOURCE\\ai\\actor_types.c", 0x8e, 1);
    system_exit(-1);
  }

  (*(void (*)(int)) * (int *)((char *)type_def + 0x18))(actor_handle);
}

void FUN_0003a920(int actor_handle, int a2, float a3, float *a4)
{
  char *actor;
  char *type_def;
  void (*fn)(int, int, float, float *);

  actor = (char *)datum_get(actor_data, actor_handle);
  type_def = (char *)FUN_0003a600(*(short *)(actor + 4));
  if (*(char *)(type_def + 0xd) == 0) {
    display_assert("actor_type_definition->swarm",
                   "c:\\halo\\SOURCE\\ai\\actor_types.c", 0x9d, 1);
    system_exit(-1);
  }
  fn = (void (*)(int, int, float, float *)) * (int *)(type_def + 0x1c);
  if (fn != NULL) {
    fn(actor_handle, a2, a3, a4);
  }
}

/* actors.c — AI actor/swarm data lifecycle.
 *
 * Corresponds to actors.obj (XBE address range ~0x3a990–0x3aab7).
 * Implements actors_dispose_from_old_map. Binary strings at
 * actors_initialize confirm the source path "c:\halo\SOURCE\ai\actors.c"
 * and the three global data tables: actor_data (name "actor",
 * 0x100 entries * 0x724 bytes), swarm_data (name "swarm", 0x20 *
 * 0x98), and swarm_component_data (name "swarm component", 0x100 *
 * 0x40). actors_dispose (0x3aa50) is a single-RET stub in the
 * original binary — empty function, no operation.
 */

/* actors_initialize (0x3a990)
 * Allocate actor_data, swarm_data, and swarm_component_data tables
 * via game_state_data_new. Asserts each allocation succeeded. */
void actors_initialize(void)
{
  FUN_0003a740();
  actor_data = game_state_data_new("actor", 0x100, 0x724);
  assert_halt(actor_data);
  swarm_data = game_state_data_new("swarm", 0x20, 0x98);
  assert_halt(swarm_data);
  swarm_component_data = game_state_data_new("swarm component", 0x100, 0x40);
  assert_halt(swarm_component_data);
}

/* actors_dispose: empty stub in the original binary (single RET).
 * Confirmed: 0x3aa50 contains only a RET instruction. */
void actors_dispose(void)
{
}

/* actor_in_combat (0x3aa60)
 * Delete all entries from the three actor data tables. */
void actor_in_combat(void)
{
  data_delete_all(actor_data);
  data_delete_all(swarm_data);
  data_delete_all(swarm_component_data);
}

/* actors_dispose_from_old_map: invalidate the three actor data
 * tables when leaving a map. Calls data_make_invalid on
 * actor_data, swarm_data, swarm_component_data in that order.
 * Confirmed: three MOV r32,[global] / PUSH r32 / CALL 0x119550
 * sequences followed by ADD ESP,0xC / RET. */
void actors_dispose_from_old_map(void)
{
  data_make_invalid(actor_data);
  data_make_invalid(swarm_data);
  data_make_invalid(swarm_component_data);
}

/* actor_set_team (0x3aac0) — set team index on all units belonging to an actor.
 *
 * Resolves the actor record via actor_data and writes param team_index to the
 * team field (offset +0x68) of every unit object associated with the actor.
 * Three cases are handled based on the swarm flag (actor+0x6) and the swarm
 * handle (actor+0x28):
 *
 *   1. Non-swarm actor (actor[6] == 0):
 *      If actor->unit_handle (actor+0x18) != -1, write team_index to
 *      unit[0x68] via object_get_and_verify_type.
 *
 *   2. Swarm actor with swarm handle (actor[0x28] != -1):
 *      Resolve the swarm record via swarm_data. Iterate all member handles
 *      stored at swarm[0x18 + i*4] (count = swarm[2], short) and write
 *      team_index to each unit[0x68].
 *
 *   3. Swarm actor without swarm handle (actor[0x28] == -1):
 *      Walk the linked list starting at actor[0x24], following unit[0x1ac]
 *      until -1, writing team_index to each unit[0x68].
 *
 * Confirmed: datum_get(actor_data, actor_handle) at 0x3aad0.
 * Confirmed: actor[6] swarm-flag test at 0x3aadb-0x3aadd.
 * Confirmed: non-swarm path — actor[0x18] guard + object_get_and_verify_type
 *   at 0x3ab52-0x3ab62; write DX=[EBP+0xc] to [EAX+0x68] at 0x3ab66-0x3ab69.
 * Confirmed: swarm-handle path — datum_get(swarm_data, actor[0x28]) at
 *   0x3aaef; loop over swarm[2] entries at 0x3ab01-0x3ab27; BX=[EBP+0xc]
 *   stored to [EAX+0x68] at 0x3ab19.
 * Confirmed: linked-list path — actor[0x24] at 0x3ab28; loop via unit[0x1ac]
 *   at 0x3ab34-0x3ab4c; SI=[EBP+0xc] stored to [EAX+0x68] at 0x3ab3c. */
void actor_set_team(int actor_handle, int16_t team_index)
{
  char *actor;
  char *swarm;
  char *unit;
  int unit_handle;
  short i;

  actor = (char *)datum_get(actor_data, actor_handle);
  if (*(char *)(actor + 6) == 0) {
    /* Non-swarm actor: set team on the single associated unit */
    unit_handle = *(int *)(actor + 0x18);
    if (unit_handle != -1) {
      unit = (char *)object_get_and_verify_type(unit_handle, 3);
      *(int16_t *)(unit + 0x68) = team_index;
    }
  } else if (*(int *)(actor + 0x28) == -1) {
    /* Swarm actor with no swarm handle: walk the unit linked list */
    unit_handle = *(int *)(actor + 0x24);
    while (unit_handle != -1) {
      unit = (char *)object_get_and_verify_type(unit_handle, 3);
      *(int16_t *)(unit + 0x68) = team_index;
      unit_handle = *(int *)(unit + 0x1ac);
    }
  } else {
    /* Swarm actor with swarm handle: iterate swarm member array */
    swarm = (char *)datum_get(swarm_data, *(int *)(actor + 0x28));
    i = 0;
    while (i < *(short *)(swarm + 2)) {
      unit = (char *)object_get_and_verify_type(
        *(int *)(swarm + 0x18 + (int)i * 4), 3);
      i++;
      *(int16_t *)(unit + 0x68) = team_index;
    }
  }
}

/* actor_activation_debug_color (0x3ab80) — return a debug color representing
 * actor state.
 *
 * Returns one of five color pointers based on the actor's current status:
 *   - Active actor (actor+8 != 0):
 *     - actor+0x13 != 0: return *(void**)0x2ee6d8
 *     - actor+0x12 == 0: return *(void**)0x2ee6c4
 *     - actor+0x14 < 1: return *(void**)0x2ee6e0
 *     - else: return *(void**)0x2ee6d4
 *   - Inactive/dormant actor (actor+8 == 0):
 *     - actor+0x34 != -1 (has encounter):
 *       look up encounter definition via tag_block_get_element; if
 *       enc_def[0x7e] (short) is not -1 and not the current BSP index:
 *       return *(void**)0x2ee6d0 (actor in different BSP)
 *     - else: return *(void**)0x2ee6f4 (default inactive color)
 *
 * Confirmed: MOV EAX,[EBP+0x8] at 0x3ab83 — cdecl stack param.
 * Confirmed: datum_get(actor_data=[0x6325a4], actor_handle) at 0x3ab8e.
 * Confirmed: TEST CL,CL / JZ 0x3abce at 0x3ab99 — actor+8 check.
 * Confirmed: AND EAX,0xffff at 0x3abd6 masks encounter handle lower 16 bits.
 * Confirmed: PUSH 0xb0; PUSH EAX; CALL global_scenario_get (0 args, pre-push);
 *   ADD EAX,0x42c; PUSH EAX; CALL tag_block_get_element at 0x3abdb–0x3abec.
 * Confirmed: MOV EAX,[0x326a0c] = global_structure_bsp_index compare at
 * 0x3abfe. Confirmed: return [0x2ee6d0] via JNZ 0x3ac11; [0x2ee6f4] via
 * fall-through. */
void *actor_activation_debug_color(int actor_handle)
{
  char *actor;
  char *enc_def;
  int encounter_idx;

  actor = (char *)datum_get(actor_data, actor_handle);
  if (*(char *)(actor + 0x8) != 0) {
    /* Active actor: color based on state flags */
    if (*(char *)(actor + 0x13) != 0) {
      return *(void **)0x2ee6d8;
    }
    if (*(char *)(actor + 0x12) != 0) {
      if (*(short *)(actor + 0x14) > 0) {
        return *(void **)0x2ee6d4;
      }
      return *(void **)0x2ee6e0;
    }
    return *(void **)0x2ee6c4;
  }
  /* Inactive/dormant actor: color based on encounter BSP */
  if (*(unsigned int *)(actor + 0x34) != 0xffffffff) {
    encounter_idx = (int)(*(unsigned int *)(actor + 0x34) & 0xffff);
    enc_def = (char *)tag_block_get_element(
      (char *)global_scenario_get() + 0x42c, encounter_idx, 0xb0);
    if (*(short *)(enc_def + 0x7e) != -1 &&
        *(short *)(enc_def + 0x7e) != *(short *)0x326a0c) {
      return *(void **)0x2ee6d0;
    }
  }
  return *(void **)0x2ee6f4;
}

/* FUN_0003ac20 (0x3ac20) — actor_check_unit_activation_logic
 *
 * Validates that a unit's activation state is consistent with the actor's
 * dormancy flag. For top-level objects only (parent_object_index == -1): if
 * the unit was deactivated more than 30 ticks ago and its active-flag differs
 * from what the actor expects, fires an activation-logic error.
 *
 * Parameters:
 *   actor_handle — cdecl stack arg: actor datum handle
 *   reason       — cdecl stack arg: string label used in the error message
 *   obj_handle   — @<eax> register arg: handle of the unit/object to check
 *
 * Confirmed: MOV ESI,EAX at 0x3ac25 captures register arg.
 * Confirmed: datum_get(*(data_t**)0x5a8d50, obj_handle) at 0x3ac2f → header.
 * Confirmed: object_get_and_verify_type(obj_handle, 3) at 0x3ac39 → obj ptr.
 * Confirmed: datum_get(actor_data, actor_handle) at 0x3ac4b → actor ptr.
 * Confirmed: [obj+0xcc] == -1 guard (parent_object_index) at 0x3ac5b.
 * Confirmed: game_time_get() at 0x3ac60; [obj+0x2dc]+0x1e compared at 0x3ac6e.
 * Confirmed: [actor+0x13] vs (~[header+0x2])&1 mismatch check at 0x3ac7f.
 * Confirmed: error(2, "%s unit activation logic error", reason) at 0x3ac8e. */
void FUN_0003ac20(int actor_handle, const char *reason,
                  int obj_handle /* @<eax> */)
{
  char *header;
  char *obj;
  char *actor;
  int now;

  /* Resolve object header and full object pointer */
  header = (char *)datum_get(*(data_t **)0x5a8d50, obj_handle);
  obj = (char *)object_get_and_verify_type(obj_handle, 3);
  actor = (char *)datum_get(actor_data, actor_handle);

  /* Only check top-level objects (no parent) */
  if (*(int *)(obj + 0xcc) != -1) {
    return;
  }

  /* Only flag if the unit has been deactivated long enough */
  now = game_time_get();
  if (*(int *)(obj + 0x2dc) + 0x1e >= now) {
    return;
  }

  /* Check: actor's active-flag must match what the object header reports.
   * header->unk_2 bit0 == 0 means active; actor+0x13 == 0 means dormant.
   * If (~header->unk_2 & 1) != actor->active then it's a logic error. */
  if (*(unsigned char *)(actor + 0x13) !=
      ((~*(unsigned char *)(header + 0x2)) & 1u)) {
    error(2, "%s unit activation logic error", reason);
  }
}

/* actor_verify_activation (0x3aca0) — actor_check_dormancy_logic
 *
 * Validates dormancy/activation consistency for all units controlled by an
 * actor. Asserts at least one of the two dormancy flags (actor+0x8 = has_unit,
 * actor+0x13 = active) is set. Then dispatches to FUN_0003ac20 for each
 * unit depending on actor type:
 *
 *   Non-swarm (actor+0x6 == 0): checks the single unit at actor+0x18.
 *   Swarm with no handle (actor+0x28 == -1): walks the singly-linked list
 *     starting at actor+0x24, following obj+0x1ac, checking each object.
 *   Swarm with handle (actor+0x28 != -1): looks up the swarm record via
 *     swarm_data and checks each member handle in swarm->members[].
 *
 * Confirmed: datum_get(actor_data, actor_handle) at 0x3acb0.
 * Confirmed: actor+0x8 and actor+0x13 both-zero assert at 0x3acbf/0x3acc6.
 * Confirmed: actor+0x6 branch at 0x3acda.
 * Confirmed: actor+0x18 (unit handle, individual path) checked at 0x3ad5d.
 * Confirmed: actor+0x28 (swarm handle) checked at 0x3ace4.
 * Confirmed: datum_get(swarm_data, actor+0x28) at 0x3acee (active swarm).
 * Confirmed: swarm->count at [swarm+0x2] (int16_t); member handles at
 *   [swarm+0x18+i*4]; loop counter ESI is int16 (CMP SI, word ptr).
 * Confirmed: linked-list path: actor+0x24 head, obj+0x1ac next ptr.
 * Confirmed: object_get_and_verify_type(handle, 3) before FUN_0003ac20 on
 *   linked list path (EDI = obj ptr used to read next ptr at 0x3ad47).
 * Confirmed: FUN_0003ac20 called with @EAX=obj_handle, all three paths. */
void actor_verify_activation(int actor_handle)
{
  char *actor;
  char *swarm;
  char *obj;
  int obj_handle;
  int16_t i;

  actor = (char *)datum_get(actor_data, actor_handle);

  /* At least one of has_unit or active must be set */
  if (*(char *)(actor + 0x8) == 0 && *(char *)(actor + 0x13) == 0) {
    error(2, "actor dormancy logic error");
  }

  if (*(char *)(actor + 0x6) == 0) {
    /* Non-swarm: single unit */
    if (*(int *)(actor + 0x18) != -1) {
      /* @<eax> = unit handle */
      int unit_handle = *(int *)(actor + 0x18);
      FUN_0003ac20(actor_handle, "individual", unit_handle /* @<eax> */);
    }
  } else if (*(int *)(actor + 0x28) == -1) {
    /* Swarm with no swarm-data handle: walk linked list from actor+0x24 */
    obj_handle = *(int *)(actor + 0x24);
    while (obj_handle != -1) {
      obj = (char *)object_get_and_verify_type(obj_handle, 3);
      FUN_0003ac20(actor_handle, "inactive swarm", obj_handle /* @<eax> */);
      obj_handle = *(int *)(obj + 0x1ac);
    }
  } else {
    /* Swarm with swarm-data handle: iterate members array */
    swarm = (char *)datum_get(swarm_data, *(int *)(actor + 0x28));
    for (i = 0; i < *(int16_t *)(swarm + 0x2); i++) {
      int member = *(int *)(swarm + 0x18 + (int)i * 4);
      FUN_0003ac20(actor_handle, "active swarm", member /* @<eax> */);
    }
  }
}

/* actor_detach_from_unit (0x3ad80) — actor_clear_unit
 *
 * Clear the unit reference from an actor. Sets unit flags, clears the unit's
 * actor_index, decrements the encounter's unique_leader_count if the actor
 * was a unique leader, and finally clears actor->unit_handle and the unique
 * leader flag.
 *
 * Confirmed: datum_get(actor_data, actor_handle) at 0x3ad8f.
 * Confirmed: actor+0x18 (unit_handle) checked against -1 at 0x3ad9c.
 * Confirmed: object_get_and_verify_type(unit_handle, 3) at 0x3ada9.
 * Confirmed: object_set_automatic_deactivation(unit_handle, 1) at 0x3adb6.
 * Confirmed: unit_set_actively_controlled(unit_handle, 0) at 0x3adc1.
 * Confirmed: assert unit+0x1a4 == actor_handle at 0x3adcf.
 * Confirmed: unit+0x1a4 = -1 at 0x3adf6.
 * Confirmed: actor+0x1c (unique leader flag) checked at 0x3adfc.
 * Confirmed: datum_get(encounter_data, actor+0x34) at 0x3ae11.
 * Confirmed: assert encounter+0x1c > 0 at 0x3ae1b.
 * Confirmed: encounter+0x1c decremented at 0x3ae41.
 * Confirmed: actor+0x18 = -1, actor+0x1c = 0 at 0x3ae45-0x3ae48. */
void actor_detach_from_unit(int actor_handle)
{
  char *actor;
  char *unit;
  char *encounter;

  actor = (char *)datum_get(actor_data, actor_handle);

  if (*(int *)(actor + 0x18) == -1) {
    return;
  }

  unit = (char *)object_get_and_verify_type(*(int *)(actor + 0x18), 3);
  object_set_automatic_deactivation(*(int *)(actor + 0x18), 1);
  unit_set_actively_controlled(*(int *)(actor + 0x18), 0);

  /* Assert unit's actor_index matches */
  if (*(int *)(unit + 0x1a4) != actor_handle) {
    display_assert("unit->unit.actor_index == actor_index",
                   "c:\\halo\\SOURCE\\ai\\actors.c", 0x55e, 1);
    system_exit(-1);
  }

  *(int *)(unit + 0x1a4) = -1;

  /* If actor was a unique leader, decrement encounter's count */
  if (*(char *)(actor + 0x1c) != 0 && *(int *)(actor + 0x34) != -1) {
    encounter = (char *)datum_get(*(data_t **)0x5ab270, *(int *)(actor + 0x34));
    if (*(short *)(encounter + 0x1c) <= 0) {
      display_assert("encounter->unique_leader_count > 0",
                     "c:\\halo\\SOURCE\\ai\\actors.c", 0x565, 1);
      system_exit(-1);
    }
    *(short *)(encounter + 0x1c) = *(short *)(encounter + 0x1c) - 1;
  }

  *(int *)(actor + 0x18) = -1;
  *(char *)(actor + 0x1c) = 0;
}

/* actor_swarm_detach_from_unit (0x3ae60) — actor_detach_unit
 *
 * Detach a unit from an actor. This removes the unit from the actor's unit
 * list, updates the unit linked-list pointers (unit+0x1ac/0x1b0), and if the
 * actor is a swarm, removes the unit from the swarm's component arrays.
 *
 * Confirmed: datum_get(actor_data, actor_handle) at 0x3ae71.
 * Confirmed: object_get_and_verify_type(unit_handle, 3) at 0x3ae7f.
 * Confirmed: unit+0x1a8 == actor_handle check at 0x3ae8f.
 * Confirmed: assert actor+0x1e > 0 (swarm_unit_count) at 0x3aea2.
 * Confirmed: object_set_automatic_deactivation(unit_handle, 1) at 0x3aec7.
 * Confirmed: unit_set_actively_controlled(unit_handle, 0) at 0x3aecf.
 * Confirmed: swarm lookup via datum_get(swarm_data, actor+0x28) at 0x3aeed.
 * Confirmed: swarm+0x18 array holds unit handles, swarm+0x58 holds component
 * handles. Confirmed: datum_delete(swarm_component_data, component_handle) at
 * 0x3afdd. Confirmed: linked list update via unit+0x1ac (prev) and unit+0x1b0
 * (next). Confirmed: unit+0x1a8 = -1 at end, actor+0x1e decremented. */
void actor_swarm_detach_from_unit(int actor_handle, int unit_handle)
{
  char *actor;
  char *unit;
  char *swarm;
  short i;
  int component_handle;
  short unit_count;

  actor = (char *)datum_get(actor_data, actor_handle);
  unit = (char *)object_get_and_verify_type(unit_handle, 3);

  /* Only proceed if this unit belongs to this actor */
  if (*(int *)(unit + 0x1a8) != actor_handle) {
    return;
  }

  /* Assert swarm_unit_count > 0 */
  if (*(short *)(actor + 0x1e) <= 0) {
    display_assert("actor->meta.swarm_unit_count > 0",
                   "c:\\halo\\SOURCE\\ai\\actors.c", 0x579, 1);
    system_exit(-1);
  }

  /* Set unit flags and update weapon state */
  object_set_automatic_deactivation(unit_handle, 1);
  unit_set_actively_controlled(unit_handle, 0);

  /* If actor has a swarm, remove unit from swarm arrays */
  if (*(int *)(actor + 0x28) != -1) {
    swarm = (char *)datum_get(swarm_data, *(int *)(actor + 0x28));

    /* Assert swarm->actor_index == actor_index */
    if (*(int *)(swarm + 4) != actor_handle) {
      display_assert("swarm->actor_index == actor_index",
                     "c:\\halo\\SOURCE\\ai\\actors.c", 0x585, 1);
      system_exit(-1);
    }

    /* Assert swarm->unit_count == actor->meta.swarm_unit_count */
    if (*(short *)(swarm + 2) != *(short *)(actor + 0x1e)) {
      display_assert("swarm->unit_count == actor->meta.swarm_unit_count",
                     "c:\\halo\\SOURCE\\ai\\actors.c", 0x586, 1);
      system_exit(-1);
    }

    /* Search for unit in swarm array and remove it */
    for (i = 0; i < *(short *)(swarm + 2); i++) {
      if (*(int *)(swarm + 0x18 + i * 4) == unit_handle) {
        /* Save component handle before removing */
        component_handle = *(int *)(swarm + 0x58 + i * 4);

        /* Decrement count */
        unit_count = *(short *)(swarm + 2) - 1;
        *(short *)(swarm + 2) = unit_count;

        /* Compact arrays if not last element */
        if (i < unit_count) {
          *(int *)(swarm + 0x18 + i * 4) =
            *(int *)(swarm + 0x18 + unit_count * 4);
          *(int *)(swarm + 0x58 + i * 4) =
            *(int *)(swarm + 0x58 + *(short *)(swarm + 2) * 4);
        }

        /* Delete the swarm component */
        datum_delete(swarm_component_data, component_handle);
        goto update_linked_list;
      }
    }

    /* Unit not found in swarm - assert */
    display_assert("found", "c:\\halo\\SOURCE\\ai\\actors.c", 0x59c, 1);
    system_exit(-1);
  }

update_linked_list:
  /* Update linked list of units */
  if (*(int *)(unit + 0x1b0) == -1) {
    /* No next unit - update actor's first unit pointer */
    *(int *)(actor + 0x24) = *(int *)(unit + 0x1ac);
  } else {
    /* Update next unit's prev pointer */
    char *next_unit =
      (char *)object_get_and_verify_type(*(int *)(unit + 0x1b0), 3);
    *(int *)(next_unit + 0x1ac) = *(int *)(unit + 0x1ac);
  }

  if (*(int *)(unit + 0x1ac) != -1) {
    /* Update prev unit's next pointer */
    char *prev_unit =
      (char *)object_get_and_verify_type(*(int *)(unit + 0x1ac), 3);
    *(int *)(prev_unit + 0x1b0) = *(int *)(unit + 0x1b0);
  }

  /* Clear unit's actor reference and decrement count */
  *(int *)(unit + 0x1a8) = -1;
  *(short *)(actor + 0x1e) = *(short *)(actor + 0x1e) - 1;
}

/* actor_swarm_cache_delete (0x3b030) — actor_delete_swarm
 *
 * Delete swarm data for an actor. Iterates all swarm components and deletes
 * them from swarm_component_data, then deletes the swarm from swarm_data and
 * clears actor+0x28.
 *
 * Confirmed: datum_get(actor_data, actor_handle) at 0x3b03f.
 * Confirmed: actor+0x28 (swarm_handle) checked against -1 at 0x3b04c.
 * Confirmed: datum_get(swarm_data, swarm_handle) at 0x3b05b.
 * Confirmed: loop over swarm+2 (count), deleting swarm+0x58[i] components.
 * Confirmed: datum_delete(swarm_component_data, component) at 0x3b07f.
 * Confirmed: datum_delete(swarm_data, actor+0x28) at 0x3b099.
 * Confirmed: actor+0x28 = -1 at 0x3b0a2. */
void actor_swarm_cache_delete(int actor_handle)
{
  char *actor;
  char *swarm;
  short i;

  actor = (char *)datum_get(actor_data, actor_handle);

  if (*(int *)(actor + 0x28) == -1) {
    return;
  }

  swarm = (char *)datum_get(swarm_data, *(int *)(actor + 0x28));

  /* Delete all swarm components */
  for (i = 0; i < *(short *)(swarm + 2); i++) {
    datum_delete(swarm_component_data, *(int *)(swarm + 0x58 + i * 4));
  }

  /* Delete the swarm itself */
  datum_delete(swarm_data, *(int *)(actor + 0x28));
  *(int *)(actor + 0x28) = -1;
}

/* actor_switch_props (0x3b0b0) — swarm_component_update_position
 *
 * Update one swarm component's cached position and target state from its
 * corresponding unit object. Fetches the unit pointer via
 * object_get_and_verify_type (type_mask 3 = biped/vehicle) and the swarm
 * component record from swarm_component_data. Writes the unit's world position
 * into swarm_component+4 (vector3_t). Stores unit+0x430 (target handle) into
 * swarm_component+0x10 if unit+0x64 (short state flag) is zero, otherwise
 * stores -1.
 *
 * Confirmed: object_get_and_verify_type(unit_handle, 3) at 0x3b0bc.
 * Confirmed: datum_get(swarm_component_data, swarm_component_handle) at
 * 0x3b0ce. Confirmed: ADD ESP,0x10 at 0x3b0d3 cleans both call frames (4 pushes
 * total). Confirmed: OR EDI,0xffffffff at 0x3b0d6 (default EDI = -1 before
 * CMP). Confirmed: CMP word ptr [ESI+0x64],0 at 0x3b0d9 (ESI = unit ptr).
 * Confirmed: MOV EDI,[ESI+0x430] at 0x3b0e2 (conditional on ZF).
 * Confirmed: object_get_world_position(unit_handle, swarm_component+4) at
 * 0x3b0f0. Confirmed: MOV [EBX+0x10],EDI at 0x3b0f8 (EBX = swarm_component
 * ptr). */
void actor_switch_props(int unit_handle, int swarm_component_handle)
{
  char *unit;
  char *swarm_component;
  int target_handle;

  unit = (char *)object_get_and_verify_type(unit_handle, 3);
  swarm_component =
    (char *)datum_get(swarm_component_data, swarm_component_handle);
  target_handle = -1;
  if (*(short *)(unit + 0x64) == 0) {
    target_handle = *(int *)(unit + 0x430);
  }
  object_get_world_position(unit_handle, (vector3_t *)(swarm_component + 4));
  *(int *)(swarm_component + 0x10) = target_handle;
}

/* 0x3b100 — Return true if actor has fewer than 3 active slots (field +0x6a).
 */
bool actor_is_noncombat(int actor_handle)
{
  return *(int16_t *)((char *)datum_get(actor_data, actor_handle) + 0x6a) < 3;
}

/* FUN_0003b120 (0x3b120)
 * Test whether an actor is in mode 3 with its active-slot count
 * exceeding capacity.  Returns 1 (true) when actor->field_0x6a == 3
 * AND actor->field_0x6e > actor->field_0x72; 0 otherwise.
 * Called by encounter_update_status to accumulate the dead/fleeing
 * counter at encounter+0x2e.
 *
 * Confirmed: datum_get(actor_data, actor_handle) at 0x3b12e.
 * Confirmed: CMP word ptr [EAX+0x6a],3 at 0x3b136.
 * Confirmed: MOV DX,[EAX+0x6e]; CMP DX,[EAX+0x72] at 0x3b13d/0x3b141.
 * Confirmed: JLE 0x3b14b (return 0 if +0x6e <= +0x72) at 0x3b145.
 * Confirmed: MOV AL,1 / XOR AL,AL at 0x3b147/0x3b14b. */
char FUN_0003b120(int actor_handle)
{
  char *actor;

  actor = (char *)datum_get(actor_data, actor_handle);
  if (*(short *)(actor + 0x6a) == 3 &&
      *(short *)(actor + 0x6e) > *(short *)(actor + 0x72)) {
    return 1;
  }
  return 0;
}

/* actor_is_fighting (0x3b150)
 * Test whether an actor has at least 7 active slots (field +0x6e) and is
 * NOT simultaneously in mode 4 with a positive counter at +0xa8.
 * Returns 1 when actor->field_0x6e >= 7, unless actor->field_0x6c == 4
 * AND actor->field_0xa8 > 0, in which case it returns 0.
 *
 * Confirmed: datum_get(actor_data, actor_handle) at 0x3b15e (EAX=handle,
 * ECX=table from DAT_006325a4; cdecl).
 * Confirmed: CMP word ptr [ECX+0x6e],0x7 / SETGE AL at 0x3b168/0x3b16d
 * materializes the boolean into AL rather than branching.
 * Confirmed: TEST AL,AL / JZ end at 0x3b170 short-circuits when AL==0.
 * Confirmed: CMP word ptr [ECX+0x6c],0x4 / JNZ end at 0x3b174/0x3b179.
 * Confirmed: CMP word ptr [ECX+0xa8],0x0 / JLE end at 0x3b17b/0x3b183.
 * Confirmed: XOR AL,AL at 0x3b185 clears the boolean before RET. */
char actor_is_fighting(int actor_handle)
{
  char *actor;
  char result;

  actor = (char *)datum_get(actor_data, actor_handle);
  result = (char)(*(short *)(actor + 0x6e) >= 7);
  if (result && *(short *)(actor + 0x6c) == 4 && *(short *)(actor + 0xa8) > 0) {
    result = 0;
  }
  return result;
}

/* 0x3b190 — Get actor attack vector (3-float) if actively in cover type 4.
 * Asserts attack_vector_out is non-null, then if attack intensity > 8 and
 * the action type is 4 (cover): copies the script-set vector (+0x180) or the
 * burst-fire target vector (+0x63c) into attack_vector_out. Returns 1 on
 * success, 0 if no attack vector is available. */
int FUN_0003b190(int actor_handle, int *attack_vector_out)
{
  char *actor;
  int16_t mode;

  actor = (char *)datum_get(actor_data, actor_handle);
  if (attack_vector_out == 0) {
    display_assert("attack_vector", "c:\\halo\\SOURCE\\ai\\actors.c", 0x698, 1);
    system_exit(-1);
  }
  if (*(int16_t *)(actor + 0x268) > 8) {
    mode = actor_action_try_to_panic(actor_handle);
    if (mode == 4) {
      if (*(char *)(actor + 0x6a0)) {
        attack_vector_out[0] = *(int *)(actor + 0x180);
        attack_vector_out[1] = *(int *)(actor + 0x184);
        attack_vector_out[2] = *(int *)(actor + 0x188);
        return 1;
      }
      if (*(int16_t *)(actor + 0x60c) > 0) {
        attack_vector_out[0] = *(int *)(actor + 0x63c);
        attack_vector_out[1] = *(int *)(actor + 0x640);
        attack_vector_out[2] = *(int *)(actor + 0x644);
        return 1;
      }
    }
  }
  return 0;
}

/* 0x3b240 — Return true if actor is in mode 10 and FUN_00012e50 says so.
 * Checks actor->mode (field +0x6c) == 10; if so, delegates to FUN_00012e50.
 * Otherwise returns false. */
bool actor_is_leaping(int actor_handle)
{
  char *actor;

  actor = (char *)datum_get(actor_data, actor_handle);
  if (*(int16_t *)(actor + 0x6c) == 10)
    return FUN_00012e50(actor_handle);
  return false;
}

/* actor_attacking_target (0x3b270)
 * Get the current weapon handle for an actor. First checks if the actor has
 * a held-weapon unit (offset 0x158, guarded by byte at 0x161). If that path
 * yields a weapon, return it immediately. Otherwise falls back to the actor's
 * own unit (offset 0x18), checking the actor variant tag ('actv' at offset
 * 0x5c) for flag 0x40 — if clear, returns the weapon from that unit.
 * Returns -1 if no weapon found.
 *
 * Confirmed: datum_get(actor_data, actor_handle) at 0x3b280.
 * Confirmed: object_get_and_verify_type with type_mask 3 at 0x3b2a5, 0x3b2ee.
 * Confirmed: unit_get_weapon at 0x3b2bb, 0x3b2ff.
 * Confirmed: tag_get(0x61637476, actor+0x5c) at 0x3b2d9.
 * Confirmed: first path uses XOR EDX,EDX; MOV DX (zero-extend) for
 * weapon_index. Confirmed: second path uses MOVSX (sign-extend) for
 * weapon_index. */
int actor_attacking_target(int actor_handle)
{
  char *actor;
  char *unit;
  int result;

  actor = (char *)datum_get(actor_data, actor_handle);
  result = -1;

  if (*(char *)(actor + 0x161) != 0 && *(int *)(actor + 0x158) != -1) {
    unit = (char *)object_get_and_verify_type(*(int *)(actor + 0x158), 3);
    result = unit_get_weapon(*(int *)(actor + 0x158),
                             (int)(uint16_t)(*(int16_t *)(unit + 0x2a2)));
    if (result != -1) {
      return result;
    }
  }

  if (*(int *)(actor + 0x18) != -1) {
    char *actv = (char *)tag_get(0x61637476, *(int *)(actor + 0x5c));
    if ((*(unsigned char *)actv & 0x40) == 0) {
      unit = (char *)object_get_and_verify_type(*(int *)(actor + 0x18), 3);
      return unit_get_weapon(*(int *)(actor + 0x18),
                             (int)(*(int16_t *)(unit + 0x2a2)));
    }
  }

  return result;
}

bool actor_has_ranged_weapon(int actor_handle)
{
  char *actor = (char *)datum_get(actor_data, actor_handle);
  int weapon_handle = actor_attacking_target(actor_handle);
  bool has_weapon = (weapon_handle != -1);
  if (has_weapon && *(int *)(actor + 0x18) != -1) {
    char *unit = (char *)object_get_and_verify_type(*(int *)(actor + 0x18), 3);
    if (*(unsigned char *)(unit + 0xb7) & 1) {
      return false;
    }
  }
  return has_weapon;
}

/* 0x3b380 — Get actor's current encounter's team handle (encounter+0x18).
 * Returns -1 if actor has no encounter. */
int actor_target_unit_index(int actor_handle)
{
  char *actor;
  char *encounter;

  actor = (char *)datum_get(actor_data, actor_handle);
  if (*(int *)(actor + 0x270) != -1) {
    encounter =
      (char *)datum_get(*(data_t **)0x5ab23c, *(int *)(actor + 0x270));
    return *(int *)(encounter + 0x18);
  }
  return -1;
}

/* 0x3b3c0 — Forward param_1 and encounter context to
 * actor_perception_create_orphan_from_friend. Looks up the actor's encounter
 * handle (+0x270); if valid, calls actor_perception_create_orphan_from_friend
 * with the encounter's team handle and both actor/encounter handles. */
void actor_derive_target_information(int param_1, int actor_handle)
{
  char *actor;
  int encounter_handle;
  char *encounter;

  actor = (char *)datum_get(actor_data, actor_handle);
  encounter_handle = *(int *)(actor + 0x270);
  if (encounter_handle != -1) {
    encounter = (char *)datum_get(*(data_t **)0x5ab23c, encounter_handle);
    actor_perception_create_orphan_from_friend(
      param_1, *(int *)(encounter + 0x18), actor_handle, encounter_handle);
  }
}

/* FUN_0003b410 (0x3b410) — actor_replace_prop_reference
 *
 * Replace all references to old_prop with new_prop in actor fields. Updates
 * multiple prop reference fields at various offsets in the actor structure.
 * Also updates swarm component prop references if the actor is a swarm.
 * Finally calls actor_action_replace_prop to dispatch to action-specific prop
 * replacement.
 *
 * Confirmed: datum_get(actor_data, actor_handle) at 0x3b421.
 * Confirmed: actor+0x270 prop reference with special clear of +0x268 if new=-1.
 * Confirmed: actor+0x610 prop with special clear of +0x60c if new=-1 and
 * +0x60c==1. Confirmed: actor+0x6b4, +0x2f4, +0x30c, +0x340, +0x3ac, +0x1d0,
 * +0x1e8 prop refs. Confirmed: actor+0x3a8 cleared when +0x3ac matched and
 * new=-1. Confirmed: actor+0x1e4 cleared when +0x1e8 matched and new=-1.
 * Confirmed: actor+0x46c (action state 5) with +0x470 prop, clears +0x480 if
 * new=-1. Confirmed: actor+0x54c, +0x56c, +0x57c (action state 1) with
 * +0x550/0x570/0x580. Confirmed: swarm component +0x14 prop updated for each
 * component. Confirmed: actor_action_replace_prop(actor_handle, old_prop,
 * new_prop) at 0x3b5c4. */
void FUN_0003b410(int actor_handle, int old_prop, int new_prop)
{
  char *actor;
  char *swarm;
  char *component;
  short i;

  actor = (char *)datum_get(actor_data, actor_handle);

  /* Update prop reference at +0x270 */
  if (*(int *)(actor + 0x270) == old_prop) {
    *(int *)(actor + 0x270) = new_prop;
    if (new_prop == -1) {
      *(short *)(actor + 0x268) = 0;
    }
  }

  /* Update prop reference at +0x610 (only if +0x60c == 1) */
  if (*(short *)(actor + 0x60c) == 1 && *(int *)(actor + 0x610) == old_prop) {
    *(int *)(actor + 0x610) = new_prop;
    if (new_prop == -1) {
      *(short *)(actor + 0x60c) = 0;
    }
  }

  /* Update simple prop references */
  if (*(int *)(actor + 0x6b4) == old_prop) {
    *(int *)(actor + 0x6b4) = new_prop;
  }
  if (*(int *)(actor + 0x2f4) == old_prop) {
    *(int *)(actor + 0x2f4) = new_prop;
  }
  if (*(int *)(actor + 0x30c) == old_prop) {
    *(int *)(actor + 0x30c) = new_prop;
  }
  if (*(int *)(actor + 0x340) == old_prop) {
    *(int *)(actor + 0x340) = new_prop;
  }

  /* Update prop reference at +0x3ac with special +0x3a8 clear */
  if (*(int *)(actor + 0x3ac) == old_prop) {
    if (new_prop == -1) {
      *(short *)(actor + 0x3a8) = 0;
    }
    *(int *)(actor + 0x3ac) = new_prop;
  }

  /* Update prop reference at +0x1d0 */
  if (*(int *)(actor + 0x1d0) == old_prop) {
    *(int *)(actor + 0x1d0) = new_prop;
  }

  /* Update prop reference at +0x1e8 with special +0x1e4 clear */
  if (*(int *)(actor + 0x1e8) == old_prop) {
    *(int *)(actor + 0x1e8) = new_prop;
    if (new_prop == -1) {
      *(short *)(actor + 0x1e4) = 0;
    }
  }

  /* Update prop reference at +0x470 (only if action state +0x46c == 5) */
  if (*(short *)(actor + 0x46c) == 5 && *(int *)(actor + 0x470) == old_prop) {
    if (new_prop == -1) {
      *(short *)(actor + 0x46c) = 0;
      *(int *)(actor + 0x480) = -1;
    } else {
      *(int *)(actor + 0x470) = new_prop;
    }
  }

  /* Update prop references at +0x550, +0x570, +0x580 (if action state == 1) */
  if (*(short *)(actor + 0x54c) == 1 && *(int *)(actor + 0x550) == old_prop) {
    *(int *)(actor + 0x550) = new_prop;
  }
  if (*(short *)(actor + 0x56c) == 1 && *(int *)(actor + 0x570) == old_prop) {
    *(int *)(actor + 0x570) = new_prop;
  }
  if (*(short *)(actor + 0x57c) == 1 && *(int *)(actor + 0x580) == old_prop) {
    *(int *)(actor + 0x580) = new_prop;
  }

  /* Update swarm component prop references if this is a swarm actor */
  if (*(char *)(actor + 6) != 0 && *(int *)(actor + 0x28) != -1) {
    swarm = (char *)datum_get(swarm_data, *(int *)(actor + 0x28));
    for (i = 0; i < *(short *)(swarm + 2); i++) {
      component =
        (char *)datum_get(swarm_component_data, *(int *)(swarm + 0x58 + i * 4));
      if (*(int *)(component + 0x14) == old_prop) {
        *(int *)(component + 0x14) = new_prop;
      }
    }
  }

  /* Dispatch to action-specific prop replacement */
  actor_action_replace_prop(actor_handle, old_prop, new_prop);
}

/* actor_flush_position_indices (0x3b5e0) — actor_reset_action_state
 *
 * Resets the actor's action-related state and dispatches to the current
 * action's update function. Unconditionally clears the word at actor+0x3b8
 * to 0xffff (a "no-action" or invalid sentinel). If the current action state
 * (actor+0x46c, int16_t) is 3 or 4, resets it to 0 and sets actor+0x480
 * (action timer/handle) to -1. Finally calls
 * actor_action_flush_position_indices to dispatch to the action-specific
 * handler indexed by actor+0x6c (state.action).
 *
 * Confirmed: datum_get(actor_data, actor_handle) at 0x3b5ee.
 * Confirmed: MOV CX,[EAX+0x46c] — int16_t compare at 0x3b5f3.
 * Confirmed: OR EDX,-1 then MOV word [EAX+0x3b8],DX — unconditional store
 *   of 0xffff at 0x3b604 (before the branch, not inside it).
 * Confirmed: MOV word [EAX+0x46c],0x0 and MOV dword [EAX+0x480],EDX at
 *   0x3b613/0x3b61c — conditional on CX==3||CX==4.
 * Confirmed: actor_action_flush_position_indices(actor_handle) at 0x3b623
 * (cdecl, 1 arg). */
void actor_flush_position_indices(int actor_handle)
{
  char *actor;
  int16_t action_state;

  actor = (char *)datum_get(actor_data, actor_handle);

  /* Unconditional: clear action sentinel (0xffff = no action pending) */
  *(int16_t *)(actor + 0x3b8) = (int16_t)0xffff;

  /* If action state is 3 or 4, reset it and clear the action handle */
  action_state = *(int16_t *)(actor + 0x46c);
  if (action_state == 3 || action_state == 4) {
    *(int16_t *)(actor + 0x46c) = 0;
    *(int *)(actor + 0x480) = -1;
  }

  /* Dispatch to the current action's update function */
  actor_action_flush_position_indices(actor_handle);
}

/* actor_flush_structure_indices (0x3b630) — actor_reset_targeting_state
 *
 * Resets an actor's targeting/combat handles to -1 (none) and clears
 * swarm-component target slots. Performs the following:
 *   1. Resolves actor via datum_get(actor_data, actor_handle).
 *   2. Unconditionally sets:
 *        actor+0x148 (int16_t) = -1  (short handle/index)
 *        actor+0x144 (int32_t) = -1  (target handle)
 *        actor+0x164 (int32_t) = -1  (preferred weapon handle)
 *        actor+0x324 (int32_t) = -1
 *   3. If *(short*)(actor+0x400) == 2: sets actor+0x410 (int32_t) = -1
 *   4. If *(short*)(actor+0x46c) == 2: sets actor+0x47c (int32_t) = -1
 *   5. Sets actor+0x494 (int32_t) = -1
 *   6. If actor+0x6 != 0 AND actor+0x28 != -1 (swarm actor with valid swarm):
 *        Gets swarm record via datum_get(swarm_data, actor+0x28).
 *        Loops over each component (count at swarm+2, handles at
 * swarm+0x58[i]): datum_get(swarm_component_data, handle) → sets comp+0x10 = -1
 *   7. Tail-calls actor_action_flush_structure_indices().
 *
 * Confirmed: PUSH EBP; MOV EBP,ESP; MOV EAX,[EBP+8] at 0x3b630.
 * Confirmed: PUSH [0x6325a4] (actor_data), PUSH EAX (actor_handle) →
 *   CALL 0x119320 (datum_get); ADD ESP,0x8 at 0x3b636–0x3b64c.
 * Confirmed: OR EBX,0xffffffff; MOV ECX,0x2 at 0x3b644–0x3b647.
 * Confirmed: MOV word [EAX+0x148],BX (unconditional) at 0x3b656.
 * Confirmed: MOV dword [EAX+0x144],EBX at 0x3b65d.
 * Confirmed: MOV dword [EAX+0x164],EBX at 0x3b663.
 * Confirmed: MOV dword [EAX+0x324],EBX at 0x3b669.
 * Confirmed: CMP word [EAX+0x400],CX; JNZ; MOV dword [EAX+0x410],EBX at
 *   0x3b64f/0x3b66f–0x3b671.
 * Confirmed: CMP word [EAX+0x46c],CX; JNZ; MOV dword [EAX+0x47c],EBX at
 *   0x3b677–0x3b680.
 * Confirmed: MOV dword [EAX+0x494],EBX (unconditional) at 0x3b68b.
 * Confirmed: MOV CL,[EAX+6]; TEST CL,CL; JZ at 0x3b686–0x3b691.
 * Confirmed: MOV EAX,[EAX+0x28]; CMP EAX,EBX; JZ at 0x3b693–0x3b698.
 * Confirmed: datum_get(swarm_data, actor+0x28) at 0x3b69a–0x3b6a9; EDI=swarm.
 * Confirmed: XOR ESI,ESI; CMP word [EDI+2],SI; JLE 0x3b6b4 at 0x3b6ab–0x3b6b4.
 * Confirmed: MOVSX EAX,SI; MOV ECX,[EDI+EAX*4+0x58]; datum_get(swarm_comp_data)
 *   at 0x3b6c6–0x3b6d4; MOV dword [EAX+0x10],EBX at 0x3b6d8.
 * Confirmed: INC ESI; CMP SI,word [EDI+2]; JL at 0x3b6d7–0x3b6df.
 * Confirmed: JMP 0x1c530 (tail call to actor_action_flush_structure_indices) at
 * 0x3b6e5. */
void actor_flush_structure_indices(int actor_handle)
{
  char *actor;
  char *swarm;
  char *comp;
  short i;

  actor = (char *)datum_get(actor_data, actor_handle);
  *(int16_t *)(actor + 0x148) = (int16_t)0xffff;
  *(int *)(actor + 0x144) = -1;
  *(int *)(actor + 0x164) = -1;
  *(int *)(actor + 0x324) = -1;
  if (*(int16_t *)(actor + 0x400) == 2) {
    *(int *)(actor + 0x410) = -1;
  }
  if (*(int16_t *)(actor + 0x46c) == 2) {
    *(int *)(actor + 0x47c) = -1;
  }
  *(int *)(actor + 0x494) = -1;
  if (*(char *)(actor + 6) != '\0' && *(int *)(actor + 0x28) != -1) {
    swarm = (char *)datum_get(swarm_data, *(int *)(actor + 0x28));
    for (i = 0; i < *(short *)(swarm + 2); i++) {
      comp =
        (char *)datum_get(swarm_component_data, *(int *)(swarm + 0x58 + i * 4));
      *(int *)(comp + 0x10) = -1;
    }
  }
  actor_action_flush_structure_indices(actor_handle);
}

/* 0x3b6f0 — Always returns true (actor type capability stub). */
bool actor_has_unlimited_grenades(void)
{
  return true;
}

/* actor_handle_damage (0x3b700) — actor_notify_prop
 *
 * Notifies a prop (and its child prop) that time has passed, setting
 * activity flags and accumulating elapsed time. Then dispatches to
 * FUN_00037240 (actor_stimulus) with the resolved prop handle.
 *
 * 1. If prop_handle == -1, do nothing (early return after tail call).
 * 2. Calls FUN_00064b40(param_1, prop_handle, 1, 1) → prop_handle2.
 * 3. If prop_handle2 != -1:
 *    a. datum_get(prop_data, prop_handle2) → prop record.
 *    b. prop+0x70 += param_3  (accumulated time)
 *    c. prop+0x6c = 0         (clear word field)
 *    d. prop+0x74 = 1         (set active byte)
 *    e. Assert prop state (prop+0x24) is NOT 4 or 5 (!prop_orphaned).
 *    f. If prop+0xc != -1 (child handle valid):
 *         datum_get(prop_data, prop+0xc) → child record.
 *         child+0x6c = 0
 *         child+0x74 = 1
 *         child+0x70 += param_3
 *    g. If state < 2 or state > 3: set prop_handle2 = -1.
 * 4. FUN_00037240(param_1, prop_handle2, param_3, param_4).
 *
 * Confirmed: MOV EAX,[EBP+0xC]; CMP EAX,-1; JZ exit at 0x3b703-0x3b709.
 * Confirmed: PUSH 1; PUSH 1; PUSH EAX(param_2); PUSH EAX(param_1);
 *   CALL 0x64b40; MOV EDI,EAX at 0x3b710-0x3b71e.
 * Confirmed: MOV ECX,[0x5ab23c]; PUSH ESI; PUSH EDI; PUSH ECX;
 *   CALL 0x119320 (datum_get); MOV ESI,EAX at 0x3b72c-0x3b73d.
 * Confirmed: FLD [EBP+0x10]; FADD [ESI+0x70]; FSTP [ESI+0x70] at
 *   0x3b73a-0x3b74d (before word/byte stores).
 * Confirmed: MOV word [ESI+0x6c],0; MOV byte [ESI+0x74],1 at 0x3b750-0x3b756.
 * Confirmed: CMP AX,4; JL; CMP AX,5; JG → assert if state in [4,5] at
 *   0x3b749-0x3b760.
 * Confirmed: MOV EAX,[ESI+0xc]; CMP EAX,-1; JZ at 0x3b782-0x3b788.
 * Confirmed: datum_get(prop_data, child) → EAX; MOV word [EAX+0x6c],0;
 *   MOV byte [EAX+0x74],1; FLD/FADD/FSTP at 0x3b78a-0x3b7aa (byte stores
 *   before float store for child).
 * Confirmed: MOV SI,[ESI+0x24]; CMP SI,2; JL; CMP SI,3; JLE; OR EDI,-1 at
 *   0x3b7ad-0x3b7bd.
 * Confirmed: PUSH [EBP+0x14]; PUSH [EBP+0x10]; PUSH EDI; PUSH [EBP+0x8];
 *   CALL 0x37240 at 0x3b7c1-0x3b7ce. */
void actor_handle_damage(int param_1, int prop_handle, float param_3,
                         int param_4)
{
  int prop_handle2;
  char *prop;
  char *child;
  int16_t state;

  if (prop_handle != -1) {
    prop_handle2 = FUN_00064b40(param_1, prop_handle, 1, 1);
    if (prop_handle2 != -1) {
      prop = (char *)datum_get(prop_data, prop_handle2);
      *(float *)(prop + 0x70) = param_3 + *(float *)(prop + 0x70);
      *(int16_t *)(prop + 0x6c) = 0;
      *(int8_t *)(prop + 0x74) = 1;
      if (*(int16_t *)(prop + 0x24) >= 4 && *(int16_t *)(prop + 0x24) <= 5) {
        display_assert("!prop_orphaned(prop)", "c:\\halo\\SOURCE\\ai\\actors.c",
                       0x7f6, 1);
        system_exit(-1);
      }
      if (*(int *)(prop + 0xc) != -1) {
        child = (char *)datum_get(prop_data, *(int *)(prop + 0xc));
        *(int16_t *)(child + 0x6c) = 0;
        *(int8_t *)(child + 0x74) = 1;
        *(float *)(child + 0x70) = param_3 + *(float *)(child + 0x70);
      }
      state = *(int16_t *)(prop + 0x24);
      if (state < 2 || state > 3) {
        prop_handle2 = -1;
      }
    }
    FUN_00037240(param_1, prop_handle2, param_3, (float *)param_4);
  }
}

/* FUN_0003b7e0 (0x3b7e0)
 * Reset a unit's control state. Builds a default unit_control_t (0x40 bytes):
 * animation_state=1, aiming_speed=1, control_flags=0, weapon/grenade/zoom=-1,
 * throttle from global zero vector, then fills facing/aiming/looking vectors
 * from the unit's current state. Applies via unit_set_control and
 * unit_set_actively_controlled.
 *
 * Confirmed: csmemset(&control, 0, 0x40) at 0x3b7ee.
 * Confirmed: global zero vector ptr at [0x31fc38] copied to throttle.
 * Confirmed: ESI = unit_handle (register arg), stack param = actor_handle
 * (unused). Confirmed: units_debug_get_closest_unit(ESI, &facing) at 0x3b82c.
 * Confirmed: unit_scripting_unit_driver(ESI, &aiming) at 0x3b836. Confirmed:
 * unit_scripting_unit_gunner(ESI, &looking) at 0x3b840. Confirmed:
 * unit_set_control(ESI, &control) at 0x3b84a. Confirmed:
 * unit_set_actively_controlled(ESI, 0) at 0x3b852. */
void FUN_0003b7e0(int actor_handle, int unit_handle /* @<esi> */)
{
  char control[0x40];
  float *global_origin;

  csmemset(control, 0, 0x40);

  global_origin = *(float **)0x31fc38;

  /* animation_state = 1, aiming_speed = 1 */
  *(char *)(control + 0x00) = 1;
  *(char *)(control + 0x01) = 1;

  /* control_flags = 0 */
  *(int16_t *)(control + 0x02) = 0;

  /* weapon_index = -1, grenade_index = -1, zoom_level = -1 */
  *(int16_t *)(control + 0x04) = -1;
  *(int16_t *)(control + 0x06) = -1;
  *(int16_t *)(control + 0x08) = -1;

  /* throttle = global zero vector */
  *(float *)(control + 0x0c) = global_origin[0];
  *(float *)(control + 0x10) = global_origin[1];
  *(float *)(control + 0x14) = global_origin[2];

  /* Fill facing, aiming, looking vectors from unit's current state */
  units_debug_get_closest_unit(unit_handle, control + 0x1c);
  unit_scripting_unit_driver(unit_handle, control + 0x28);
  unit_scripting_unit_gunner(unit_handle, control + 0x34);

  /* Apply the control and update weapon state */
  unit_set_control(unit_handle, control);
  unit_set_actively_controlled(unit_handle, 0);
}

/* FUN_0003b860 (0x3b860)
 * Reset control state for an actor's unit(s). For non-swarm actors (byte at
 * actor+6 == 0), resets the single unit at actor+0x18. For swarm actors,
 * iterates over swarm components and resets each unit. Sets actor+7 = 1
 * when done (marks as control-reset).
 *
 * Confirmed: datum_get(actor_data, actor_handle) at 0x3b870.
 * Confirmed: actor+6 test at 0x3b87d (JZ to simple path).
 * Confirmed: datum_get(swarm_data, actor+0x28) at 0x3b895.
 * Confirmed: loop counter is 16-bit (DI), compared against word at swarm+2.
 * Confirmed: FUN_0003b7e0 called with ESI=unit_handle, stack=actor_handle.
 * Confirmed: actor+7 set to 1 at all exit paths. */
void FUN_0003b860(int actor_handle)
{
  char *actor;
  char *swarm;
  short i;

  actor = (char *)datum_get(actor_data, actor_handle);

  if (*(char *)(actor + 6) == 0) {
    /* Non-swarm: reset the single unit */
    FUN_0003b7e0(actor_handle, *(int *)(actor + 0x18));
  } else if (*(int *)(actor + 0x28) != -1) {
    /* Swarm: iterate over swarm components */
    swarm = (char *)datum_get(swarm_data, *(int *)(actor + 0x28));
    for (i = 0; i < *(short *)(swarm + 2); i++) {
      FUN_0003b7e0(actor_handle, *(int *)(swarm + 0x18 + (int)i * 4));
    }
  }

  *(char *)(actor + 7) = 1;
}

void actors_freeze(void)
{
  char iter[0x1c];
  encounter_iterator_next(iter, 1);
  while (FUN_00059b50(iter)) {
    FUN_0003b860(*(int *)(iter + 0x14));
  }
}

/* FUN_0003b940 (0x3b940)
 * Idle-update a unit's control state. Builds a default unit_control_t (0x40
 * bytes): animation_state=3, aiming_speed=1, control_flags=0,
 * weapon/grenade/zoom=-1, throttle from global forward vector. Gets the
 * unit's current facing via units_debug_get_closest_unit, then rotates it 30
 * degrees around the up axis via rotate_vector3d_by_sincos. Copies the rotated
 * facing to aiming and looking. Every 5th tick (based on game_time_get() +
 * unit_object_index mod 5), sets control_flags |= 0x0800 and
 * primary_trigger = 1.0f. Applies via unit_set_control and
 * unit_set_actively_controlled.
 *
 * Confirmed: csmemset(&control, 0, 0x40) at 0x3b94e.
 * Confirmed: global forward vector ptr at [0x31fc3c] copied to throttle.
 * Confirmed: ESI = unit_object_index (register arg), stack param = actor_handle
 * (unused). Confirmed: units_debug_get_closest_unit(ESI, &facing) at 0x3b98c.
 * Confirmed: rotate_vector3d_by_sincos(&facing, *(float**)0x31fc44, 0.5f,
 * 0.866f) at 0x3b9a5. Confirmed: facing copied to aiming and looking at
 * 0x3b9b6-0x3b9c5. Confirmed: game_time_get() at 0x3b9c8, (result+ESI)%5==0
 * triggers flag set. Confirmed: unit_set_control(ESI, &control) at 0x3b9eb.
 * Confirmed: unit_set_actively_controlled(ESI, 0) at 0x3b9f3. */
void FUN_0003b940(int actor_handle, int unit_object_index /* @<esi> */)
{
  char control[0x40];
  float *global_forward;
  float *up_axis;

  csmemset(control, 0, 0x40);

  global_forward = *(float **)0x31fc3c;

  /* animation_state = 3, aiming_speed = 1 */
  *(char *)(control + 0x00) = 3;
  *(char *)(control + 0x01) = 1;

  /* control_flags = 0 */
  *(int16_t *)(control + 0x02) = 0;

  /* weapon_index = -1, grenade_index = -1, zoom_level = -1 */
  *(int16_t *)(control + 0x04) = -1;
  *(int16_t *)(control + 0x06) = -1;
  *(int16_t *)(control + 0x08) = -1;

  /* throttle = global forward vector */
  *(float *)(control + 0x0c) = global_forward[0];
  *(float *)(control + 0x10) = global_forward[1];
  *(float *)(control + 0x14) = global_forward[2];

  /* Get unit's current facing vector */
  units_debug_get_closest_unit(unit_object_index, control + 0x1c);

  /* Rotate facing 30 degrees around the up axis */
  up_axis = *(float **)0x31fc44;
  rotate_vector3d_by_sincos((float *)(control + 0x1c), up_axis, 0.5f,
                            0.866025388f);

  /* Copy rotated facing to aiming and looking */
  *(float *)(control + 0x28) = *(float *)(control + 0x1c);
  *(float *)(control + 0x2c) = *(float *)(control + 0x20);
  *(float *)(control + 0x30) = *(float *)(control + 0x24);
  *(float *)(control + 0x34) = *(float *)(control + 0x1c);
  *(float *)(control + 0x38) = *(float *)(control + 0x20);
  *(float *)(control + 0x3c) = *(float *)(control + 0x24);

  /* Every 5th tick, fire the weapon */
  if ((game_time_get() + unit_object_index) % 5 == 0) {
    *(int16_t *)(control + 0x02) |= 0x0800;
    *(float *)(control + 0x18) = 1.0f;
  }

  /* Apply the control and update weapon state */
  unit_set_control(unit_object_index, control);
  unit_set_actively_controlled(unit_object_index, 0);
}

/* actors_move_randomly (0x3ba00) — actors_idle_update
 *
 * Iterates all active actors via the standard iterator
 * (encounter_iterator_next/FUN_00059b50). For each actor record:
 *   - If record->field_6 == 0 (non-swarm): calls FUN_0003b940 once with the
 *     actor's unit object index from record->field_18.
 *   - If record->field_6 != 0 and record->field_28 (swarm handle) is valid:
 *     looks up the swarm via datum_get(swarm_data, swarm_handle), then iterates
 *     over swarm->count (field_2) entries, calling FUN_0003b940 for each
 *     component's unit object index from the swarm array at offset 0x18.
 *
 * Confirmed: called only from ai_update (0x41180) with no arguments.
 * Confirmed: iter+0x14 ([EBP-0x8]) holds the actor datum handle.
 * Confirmed: ESI is set before each call to FUN_0003b940 (register arg).
 * Confirmed: FUN_0003b940 stack arg is iter+0x14 (actor datum handle).
 * Confirmed: inner loop counter is 16-bit (DI), compared against word at
 * swarm+2.
 */
void actors_move_randomly(void)
{
  char iter[0x1c];
  char *record;
  int actor_handle;

  encounter_iterator_next(iter, 1);
  record = (char *)FUN_00059b50(iter);
  while (record != NULL) {
    actor_handle = *(int *)(iter + 0x14);
    if (*(char *)(record + 6) == 0) {
      /* Non-swarm actor: single unit object index at record+0x18 */
      FUN_0003b940(actor_handle, *(int *)(record + 0x18));
    } else if (*(int *)(record + 0x28) != -1) {
      /* Swarm actor: iterate over swarm component entries */
      char *swarm = (char *)datum_get(swarm_data, *(int *)(record + 0x28));
      short i;
      for (i = 0; i < *(short *)(swarm + 2); i++) {
        FUN_0003b940(actor_handle, *(int *)(swarm + 0x18 + i * 4));
      }
    }
    record = (char *)FUN_00059b50(iter);
  }
}

/* Reassign an actor to a new encounter/squad, detaching from the old one. */
void FUN_0003baa0(int actor_handle, int encounter_handle, int16_t squad_index)
{
  char *actor = (char *)datum_get(actor_data, actor_handle);
  actor_flush_position_indices(actor_handle);

  if (*(char *)(actor + 9) != 0) {
    encounterless_detach_actor(actor_handle);
  } else {
    if (*(int *)(actor + 0x34) != -1) {
      encounter_detach_actor(actor_handle, 0);
    }
  }

  if (encounter_handle == -1) {
    encounterless_attach_actor(actor_handle);
    return;
  }
  encounter_attach_actor(actor_handle, encounter_handle, squad_index, 1);
}

/* FUN_0003bb50 (0x3bb50) — actor_update_cognition_score
 *
 * Updates a per-actor cognition score (field +0x4a) and compares it against
 * thresholds stored in the AI globals struct at 0x632574. If the threshold is
 * exceeded, resets the score to zero and sets alarm flags; otherwise tracks
 * the running maximum.
 *
 * Algorithm:
 *   increment = 1 if actor->field_0x6c != 10 or field_0xa0 not in {2,3,4,5}
 *               3 if actor->field_0x6c == 10 AND field_0xa0 in {2,3,4,5}
 *   actor->field_0x4a += increment
 *   score = actor->field_0x4a
 *   if (ai_globals[3] == 0 && score > ai_globals[+4] && score > 15):
 *       actor->field_0x4a = 0
 *       ai_globals[+3] = 1
 *       actor->field_0x4c = 1     (alarm triggered)
 *       return
 *   if (score > ai_globals[+6]):
 *       ai_globals[+6] = score    (update running max)
 *   actor->field_0x4c = 0         (no alarm)
 *
 * actor->field_0x6c: int16 — actor mode/state (10 = some firing mode)
 * actor->field_0xa0: int16 — some sub-state (2–5 = active sub-states)
 * actor->field_0x4a: int16 — cognition score accumulator
 * actor->field_0x4c: byte  — alarm flag
 * ai_globals+3:      byte  — global alarm triggered flag
 * ai_globals+4:      int16 — score threshold
 * ai_globals+6:      int16 — running max score
 *
 * Confirmed: datum_get(actor_data, actor_handle) at 0x3bb59.
 * Confirmed: CMP [ECX+0x6c], 0xa; then MOV SI,[ECX+0xa0]; CMP SI,{2,3,4,5} at
 *   0x3bb67–0x3bb8d.
 * Confirmed: LEA EBX,[EBX+EBX*1+1] computes increment (1 or 3) at 0x3bb97.
 * Confirmed: ADD [ECX+0x4a], BX at 0x3bb9b.
 * Confirmed: MOV ESI,[0x632574] loads AI globals ptr at 0x3bb9f.
 * Confirmed: BL = ai_globals[+3] at 0x3bba5; TEST BL,BL / JNZ at
 * 0x3bbac–0x3bbaf. Confirmed: CMP DX,[ESI+4] / CMP DX,0xf at 0x3bbb1–0x3bbb7.
 * Confirmed: reset path: [ECX+0x4a]=0; [EDX+3]=1; [ECX+0x4c]=1 at
 * 0x3bbbd–0x3bbce. Confirmed: max-tracking: CMP DX,[ESI+6] / MOV [ESI+6],DX at
 * 0x3bbd3–0x3bbd9. Confirmed: [ECX+0x4c]=0 (AL=0 from XOR AL,AL at 0x3bb63, not
 * reassigned) at 0x3bbdd. */
void FUN_0003bb50(int actor_handle /* @<eax> */)
{
  char *actor;
  char *ai_globals;
  short score;
  int increment;

  actor = (char *)datum_get(actor_data, actor_handle);
  ai_globals = *(char **)0x632574;

  increment = 1;
  if (*(short *)(actor + 0x6c) == 10) {
    short sub = *(short *)(actor + 0xa0);
    if (sub == 2 || sub == 3 || sub == 4 || sub == 5) {
      increment = 3;
    }
  }

  *(short *)(actor + 0x4a) += (short)increment;
  score = *(short *)(actor + 0x4a);

  if (*(char *)(ai_globals + 3) == 0 && score > *(short *)(ai_globals + 4) &&
      score > 0xf) {
    *(short *)(actor + 0x4a) = 0;
    *(char *)(*(char **)0x632574 + 3) = 1;
    *(char *)(actor + 0x4c) = 1;
    return;
  }

  if (score > *(short *)(ai_globals + 6)) {
    *(short *)(ai_globals + 6) = score;
  }
  *(char *)(actor + 0x4c) = 0;
}

/* FUN_0003bbf0 (0x3bbf0)
 *
 * Initializes actor perception/tracking fields on re-activation. Copies
 * three vector3_t values from actor+0x174..0x18c into actor+0x6fc..0x714,
 * zeroes actor+0x6d0 and actor+0x720, copies the global zero vector
 * (*(float**)0x31fc38) into actor+0x6e0, and sets actor+0x6ec = 0xffff.
 *
 * Confirmed: datum_get(actor_data, actor_handle) at 0x3bbf9 (EAX=handle,
 * ECX=actor_data). Confirmed: three 12-byte copies actor+0x174→+0x6fc,
 * +0x180→+0x708, +0x18c→+0x714 at 0x3bbfe–0x3bc4f. Confirmed: actor+0x6d0
 * zeroed at 0x3bc54, actor+0x720 zeroed at 0x3bc5a. Confirmed: global zero
 * vector *(float**)0x31fc38 copied 12 bytes → actor+0x6e0 at 0x3bc60–0x3bc7c.
 * Confirmed: actor+0x6ec = 0xffff at 0x3bc7f.
 * Confirmed: called with MOV EAX,ESI / CALL 0x3bbf0 from FUN_0003ec80 at
 * 0x3ed62–0x3ed64. */
void FUN_0003bbf0(int actor_handle /* @<eax> */)
{
  char *actor;
  float *zero_vec;

  actor = (char *)datum_get(actor_data, actor_handle);

  /* copy three facing/aiming/look vectors into tracking slots */
  *(vector3_t *)(actor + 0x6fc) = *(vector3_t *)(actor + 0x174);
  *(vector3_t *)(actor + 0x708) = *(vector3_t *)(actor + 0x180);
  *(vector3_t *)(actor + 0x714) = *(vector3_t *)(actor + 0x18c);

  *(int *)(actor + 0x6d0) = 0;
  *(int *)(actor + 0x720) = 0;

  zero_vec = *(float **)0x31fc38;
  *(float *)(actor + 0x6e0) = zero_vec[0];
  *(float *)(actor + 0x6e4) = zero_vec[1];
  *(float *)(actor + 0x6e8) = zero_vec[2];

  *(short *)(actor + 0x6ec) = (short)0xffff;
}

/* actor_find_pathfinding_location (0x3bc90) — Try to acquire a navigation path
 * for the actor.
 *
 * If the actor already has a path slot (actor[0x164] != -1), returns
 * immediately. Otherwise copies actor[0x12c..0x134] (3 floats, actor position)
 * to actor[0x168..0x170] as the starting position. If the actor is not paused
 * for path (actor[0x99] == 0):
 *   - If not in a vehicle (actor[0x158] == -1): calls
 *     object_try_and_get_and_verify_type(actor[0x18], 1) to verify the unit
 *     exists; if so calls biped_find_pathfinding_surface_index(actor[0x18],
 * actor+0x168) and stores the resulting path slot in actor[0x164].
 *   - If in a vehicle and vehicle_count (int16_t actor[0x15e]) is 2 or 3:
 *     calls vehicle_get_estimated_position(actor[0x158], actor+0x168) and
 *     stores the result in actor[0x164], then returns immediately.
 *
 * Confirmed: datum_get(actors_globals, actor_handle) at 0x3bc9f.
 * Confirmed: tag_get('actr', actor[0x58]) result discarded at 0x3bcaf.
 * Confirmed: actor[0x164] != -1 guard at 0x3bcbd.
 * Confirmed: 3-dword copy [0x12c..0x134] → [0x168..0x170] at 0x3bcc9-0x3bcde.
 * Confirmed: actor[0x99] test at 0x3bce1.
 * Confirmed: CMP vehicle_count,2; JL skip; CMP,3; JG skip at 0x3bcfd-0x3bd05.
 */
void actor_find_pathfinding_location(int actor_handle)
{
  char *actor;
  int *src;
  vector3_t *pos;
  int vehicle;
  int vehicle_count;

  actor = (char *)datum_get(*(void **)0x6325a4, actor_handle);
  tag_get(0x61637472, *(int *)(actor + 0x58));
  if (*(int *)(actor + 0x164) != -1)
    goto done;

  src = (int *)(actor + 0x12c);
  pos = (vector3_t *)(actor + 0x168);
  ((int *)pos)[0] = src[0];
  ((int *)pos)[1] = src[1];
  ((int *)pos)[2] = src[2];

  if (*(char *)(actor + 0x99) != 0)
    goto done;

  vehicle = *(int *)(actor + 0x158);
  if (vehicle != -1) {
    vehicle_count = *(int16_t *)(actor + 0x15e);
    if (vehicle_count > 1 && vehicle_count < 4) {
      *(int *)(actor + 0x164) = vehicle_get_estimated_position(vehicle, pos);
      return;
    }
    goto done;
  }

  if (object_try_and_get_and_verify_type(*(int *)(actor + 0x18), 1) != 0)
    *(int *)(actor + 0x164) =
      biped_find_pathfinding_surface_index(*(int *)(actor + 0x18), pos);

done:;
}

/*
 * actor_destination_tolerance (0x3bd50) — Compute the destination arrival
 * tolerance radius for an actor.
 *
 * Loads the default tolerance from the global at 0x253398. If the actor has
 * a vehicle (actor+0x158 != -1), overrides by reading the vehicle's unit tag
 * (tag_get('vehi', unit[0])) and taking the float at tag+0x384.
 *
 * Special cases:
 *   actor_type (actor+0x6c) == 0xb AND actor+0xf0 != 0 → return actor+0xf4
 *   actor_type == 9 → return constant at 0x2533c4 (water/flood override)
 *
 * Clamps result to minimum at 0x2549d4 before returning.
 *
 * Confirmed: datum_get(actor_data, actor_handle) at 0x3bd5f.
 * Confirmed: FLD [0x253398] default at 0x3bd64; FSTP ST0 discard at 0x3bd7c.
 * Confirmed: object_get_and_verify_type(actor+0x158, 2) at 0x3bd7f.
 * Confirmed: tag_get(0x76656869, unit_obj[0]) at 0x3bd8c.
 * Confirmed: FLD [EAX+0x384] at 0x3bd91 (tag offset 900 = 0x384).
 * Confirmed: CMP AX,0xb / CMP AX,0x9 actor_type tests at 0x3bd9e/0x3bdb6.
 * Confirmed: FCOM [0x2549d4] / TEST AH,0x41 / JZ keep at 0x3bdc7.
 * actors.obj / actors.c
 */
float actor_destination_tolerance(int actor_handle)
{
  char *actor;
  char *unit_obj;
  char *tag;
  float result;

  actor = (char *)datum_get(actor_data, actor_handle);
  result = *(float *)0x253398;
  if (*(int *)(actor + 0x158) != -1) {
    unit_obj = (char *)object_get_and_verify_type(*(int *)(actor + 0x158), 2);
    tag = (char *)tag_get(0x76656869, *(int *)unit_obj);
    result = *(float *)(tag + 0x384);
  }
  if ((*(short *)(actor + 0x6c) == 0xb) && (*(char *)(actor + 0xf0) != '\0')) {
    return *(float *)(actor + 0xf4);
  }
  if (*(short *)(actor + 0x6c) == 9) {
    return *(float *)0x2533c4;
  }
  if (result < *(float *)0x2549d4) {
    result = *(float *)0x2549d4;
  }
  return result;
}

/* FUN_0003bde0 (0x3bde0) — actor_fill_unit_input_block
 *
 * Populates an input block structure with the unit's world position,
 * velocity vector from object+0x24, physics position via
 * unit_get_head_position, root location, and root parent's object+0x48/0x4c
 * fields.
 *
 * Confirmed: object_get_and_verify_type(unit_handle, 3) at 0x3bdec.
 * Confirmed: object_get_world_position(unit_handle, input_block+0xc) at
 * 0x3bdfb. Confirmed: 12-byte copy from obj+0x24 to input_block+0x18 at
 * 0x3be03. Confirmed: unit_get_head_position(unit_handle, input_block) at
 * 0x3be18. Confirmed: object_get_root_location(unit_handle, input_block+0x2c,
 * 0) at 0x3be24. Confirmed: object_get_root_parent(unit_handle) at 0x3be2a.
 * Confirmed: object_get_and_verify_type(root, -1) at 0x3be32.
 * Confirmed: root_obj+0x48/0x4c copied to input_block+0x24/0x28. */
void FUN_0003bde0(int actor_handle, int unit_handle, char *input_block)
{
  char *unit_obj;
  char *root_obj;
  int root_handle;

  unit_obj = (char *)object_get_and_verify_type(unit_handle, 3);

  object_get_world_position(unit_handle, (vector3_t *)(input_block + 0xc));

  *(int *)(input_block + 0x18) = *(int *)(unit_obj + 0x24);
  *(int *)(input_block + 0x1c) = *(int *)(unit_obj + 0x28);
  *(int *)(input_block + 0x20) = *(int *)(unit_obj + 0x2c);

  unit_get_head_position(unit_handle, (float *)input_block);

  object_get_root_location(unit_handle, (float *)(input_block + 0x2c), 0);

  root_handle = object_get_root_parent(unit_handle);
  root_obj = (char *)object_get_and_verify_type(root_handle, -1);

  *(int *)(input_block + 0x24) = *(int *)(root_obj + 0x48);
  *(int *)(input_block + 0x28) = *(int *)(root_obj + 0x4c);
}

/* FUN_0003be90 (0x3be90) — actor run internal logic / infinite-loop watchdog
 *
 * Runs the actor's decision loop up to 10 times, recording the last 5 action
 * indices in a ring buffer. Each iteration: stores actor->state.action in the
 * ring, increments a counter, advances the ring index mod 5, clears the
 * action-changed flag (actor+0x70), dispatches the actor-type decide_action
 * callback (FUN_0003a840), then clears perception state (FUN_00036860).
 *
 * Loop exit paths:
 *   (a) Normal: BL (previous action-executed result) != 0 AND actor+0x70 == 0
 *       → action completed without requesting a new action.
 *   (b) Hard limit: counter >= 10 → break (error reported below).
 *   (c) Normal: actor_action_perform returns 0 AND actor+0x70 == 0 → clean
 * return.
 *
 * After loop: if counter < 10, logs "actor-type %s internal logic error (%s)"
 *   with the current action name and encounter/squad path.
 * If counter >= 10, logs each of the last 5 ring-buffer actions plus an
 *   "infinite decision loop" message.
 * Both paths call display_assert at line 0xd6c, then error() at priority 2,
 * then actor_action_change(actor_handle, 0, 0) to force-set action 0 (recover).
 *
 * Confirmed: SUB ESP,0x510 → 1296-byte frame; local_514[1024] at EBP-0x510,
 *   local_114[256] at EBP-0x110, short local_14[5] at EBP-0x10, int local_8
 *   (counter) at EBP-0x4.
 * Confirmed: csmemset(local_14, 0xff, 10) at 0x3bebd (pre-fills ring with -1).
 * Confirmed: ESI = datum_get result (actor record ptr); EDI = ring index (mod
 * 5). Confirmed: BL = result of actor_action_perform; XOR BL,BL at 0x3beb8 → BL
 * starts 0. Confirmed: loop stored at EBP-0x4 (local_8), incremented at
 * 0x3bedc. Confirmed: MOV EDI,EDX at 0x3beef sets new ring index from IDIV
 * remainder. Confirmed: break-on-BL-nonzero test at 0x3bf06–0x3bf0f. Confirmed:
 * break-on-count>=10 test at 0x3bf11–0x3bf15. Confirmed: actor_action_perform
 * called at 0x3bf1b; result into BL at 0x3bf20. Confirmed: early-return (BL==0
 * && actor[0x70]==0) at 0x3bf25–0x3bf36. Confirmed: global_scenario_get() takes
 * 0 args; PUSH 0xb0, PUSH encounter_idx at 0x3bf5a–0x3bf5f remain on stack for
 * tag_block_get_element call at 0x3bf6b. Confirmed: ADD ESP,0x28 at 0x3bf9b
 * cleans 10 dwords from encounter-path calls. Confirmed: infinite-loop
 * ring-dump loop: ESI=EDI (start index), advances mod 5, terminates when ESI
 * wraps back to EDI. Confirmed: actor_action_change(actor_handle, 0, 0) at
 * 0x3c0a5 with PUSH 0,0,EAX. Confirmed: ADD ESP,0x24 at 0x3c0aa cleans
 * display_assert(4) + error(2) + action_set(3). Inferred: actor+0x6c =
 * state.action (short); actor+0x70 = action-changed flag (byte). Inferred:
 * actor+0x34 = encounter handle (int); actor+0x3a = squad index (short).
 * Inferred: actor+0x4 = actor type index (short). Inferred:
 * actor_action_perform = actor_execute_current_action (dispatches via action
 * table). Inferred: FUN_0003a840 = actor_type_decide_action (calls
 * type->decide_action fn ptr). Inferred: FUN_00036860 =
 * actor_clear_perception_state (csmemset actor+0x2ec, 0, 100). Inferred:
 * actor_action_change = actor_set_action (sets action to param_2, clears
 * changed flag). Inferred: FUN_0003a760 = actor_type_get_name (returns actor
 * type name string). Inferred: actor_action_name = actor_action_get_name
 * (returns action name string). */
void FUN_0003be90(int actor_handle)
{
  char *actor;
  short local_14[5]; /* ring buffer of last 5 action indices */
  int local_8; /* loop counter */
  char local_114[256]; /* encounter name buffer */
  char local_514[1024]; /* error message buffer */
  int edi; /* ring buffer index (mod 5) */
  char bl; /* result of actor_action_perform */
  int encounter_idx;
  void *encounter_elem;
  void *squad_elem;
  const char *actor_type_name;
  const char *action_name;
  int i;

  actor = (char *)datum_get(actor_data, actor_handle);
  edi = 0;
  bl = 0;
  local_8 = 0;
  csmemset(local_14, 0xff, 10);

  /* Decision loop: run until action settles or limit hit */
  for (;;) {
    local_14[edi] = *(short *)(actor + 0x6c);
    local_8++;
    edi = (edi + 1) % 5;
    *(char *)(actor + 0x70) = 0;
    FUN_0003a840(actor_handle);
    FUN_00036860(actor_handle);

    /* (a) Previous action completed without requesting change */
    if (bl != 0 && *(char *)(actor + 0x70) == 0) {
      break;
    }
    /* (b) Hard iteration limit */
    if (local_8 >= 10) {
      break;
    }
    /* Execute current action; check if it changed state */
    bl = (char)actor_action_perform(actor_handle);
    /* (c) No action ran and no change requested → clean return */
    if (bl == 0 && *(char *)(actor + 0x70) == 0) {
      return;
    }
  }

  /* --- Error reporting: build encounter/squad path string --- */
  if (*(int *)(actor + 0x34) == -1) {
    csstrcpy(local_114, "<no encounter>");
  } else {
    encounter_idx = (int)(*(unsigned int *)(actor + 0x34) & 0xffff);
    encounter_elem = tag_block_get_element(
      (char *)global_scenario_get() + 0x42c, encounter_idx, 0xb0);
    squad_elem = tag_block_get_element((char *)encounter_elem + 0x80,
                                       (int)*(short *)(actor + 0x3a), 0xe8);
    crt_sprintf(local_114, "%s/%s", encounter_elem, squad_elem);
  }

  if (local_8 < 10) {
    /* Logic error: action did not converge */
    action_name = (const char *)actor_action_name(*(short *)(actor + 0x6c));
    actor_type_name = (const char *)FUN_0003a760(*(short *)(actor + 0x4));
    crt_sprintf(local_514, "actor-type %s %s internal logic error (%s)",
                actor_type_name, action_name, local_114);
  } else {
    /* Infinite decision loop: dump ring buffer */
    actor_type_name = (const char *)FUN_0003a760(*(short *)(actor + 0x4));
    crt_sprintf(local_514, "actor-type %s ", actor_type_name);
    i = edi;
    do {
      if (local_14[i] != (short)-1) {
        action_name = (const char *)actor_action_name(local_14[i]);
        FUN_0008dc30(local_514, action_name);
        FUN_0008dc30(local_514, (const char *)0x256ec8);
      }
      i = (i + 1) % 5;
    } while (i != edi);
    crt_sprintf((char *)0x5ab100, " infinite decision loop (%s)", local_114);
    FUN_0008dc30(local_514, (const char *)0x5ab100);
  }

  display_assert(local_514, "c:\\halo\\SOURCE\\ai\\actors.c", 0xd6c, 0);
  error(2, "AI error condition detected, attempting to recover (please tell "
           "butcher)...");
  actor_action_change(actor_handle, 0, 0);
}

/* actors_handle_spatial_effect (0x3c0c0) — broadcast an AI effect to all
 * audible actors. Iterates over every actor via the encounter iterator. For
 * each actor whose type field (actor+0x6e) is < 7, resolves the nearest swarm
 * unit position via actor_perception_find_sense_position and tests sound
 * audibility via actor_audibility_at_point (range factor 1.0f, flags 0). If the
 * audibility result >= 2, dispatches one of three effect functions by
 * effect_type: 0 -> FUN_00036c00 (flee/scatter) 1 -> FUN_000373b0 (charge) 2 ->
 * FUN_000374f0 (cover) Asserts on unknown effect_type.
 *
 * Confirmed: [EBP+0x08]=object_handle (->EDI), [EBP+0x0C]=effect_type,
 *   [EBP+0x10]=position (->ESI), [EBP+0x14]=volume, [EBP+0x18]=count (->EBX).
 * Confirmed: location [EBP-0x08] 8 bytes; iter [EBP-0x24] 20 bytes;
 *   actor_handle [EBP-0x10] = iter+0x14 (set by FUN_00059b50);
 *   input_block [EBP-0x5C] 56 bytes.
 * Confirmed: CMP word ptr [EAX+0x6e],0x7 / JGE skip at 0x3c105.
 * Confirmed: ADD ESP,0x2c at 0x3c138 cleans
 * actor_perception_find_sense_position(4)+actor_audibility_at_point(7)=44.
 * Confirmed: ADD ESP,0x10 at 0x3c197 cleans 4-arg effect dispatch.
 * Confirmed: CMP AX,0x2 / JL skip at 0x3c13b checks audibility >= 2.
 * Confirmed: assert filepath "c:\halo\SOURCE\ai\actors.c" line 0xdaa=3498.
 */
void actors_handle_spatial_effect(int object_handle, short effect_type,
                                  float *position, short volume, short count)
{
  /* MSVC frame layout (SUB ESP,0x5c = 92 bytes):
   *   [EBP-0x5C] input_block  56 bytes
   *   [EBP-0x24] iter         28 bytes (includes actor_handle at +0x14)
   *   [EBP-0x08] location      8 bytes
   * Use a single buffer to match the original layout exactly — callees
   * may depend on the relative positions (MSVC stack overlap hazard). */
  char frame[0x5c];
  char *input_block = frame;
  char *iter = frame + 0x38;
  char *location = frame + 0x54;
  char *actor_record;
  int actor_handle;
  short audibility;

  scenario_location_from_point(location, position);
  encounter_iterator_next(iter, 1);
  actor_record = (char *)FUN_00059b50(iter);
  while (actor_record != NULL) {
    actor_handle = *(int *)(iter + 0x14);
    if (*(short *)(actor_record + 0x6e) < 7) {
      actor_perception_find_sense_position(actor_handle, position, -1,
                                           input_block);
      audibility = (short)actor_audibility_at_point(
        actor_handle, input_block, position, location, volume, 0x3f800000, 0);
      if (audibility >= 2) {
        if (effect_type == 0) {
          FUN_00036c00(actor_handle, object_handle, position, count);
        } else if (effect_type == 1) {
          FUN_000373b0(actor_handle, object_handle, position, count);
        } else if (effect_type == 2) {
          FUN_000374f0(actor_handle, object_handle, position, count);
        } else {
          display_assert(0, "c:\\halo\\SOURCE\\ai\\actors.c", 0xdaa, 1);
          system_exit(-1);
        }
      }
    }
    actor_record = (char *)FUN_00059b50(iter);
  }
}

/* FUN_0003c1c0 (0x3c1c0) — dispatch actor stimulus by effect type.
 *
 * Dispatched from actors_handle_spatial_effect. Routes the incoming effect (a
 * struct pointer with type at +0x14 and index at +0x18) to one of three
 * handlers: type 2 -> FUN_00036b50(param_1, param_2) type 3 -> look up prop
 * record via datum_get(prop_data, param_2); if its field +0x1c != -1, call
 * datum_absolute_index_to_index on the effect index; if the resulting record is
 * non-NULL, call actor_perception_create_orphan_from_friend(param_1,
 * record+0x18, prop+0x1c, effect+0x18) type 4 -> FUN_000377d0(param_1, param_2)
 *
 * Confirmed: [EBP+0x08]=param_1 (actor handle), [EBP+0x0C]=param_2 (prop
 *   handle), [EBP+0x10]=param_3 (effect struct pointer).
 * Confirmed: MOVSX EAX,word ptr [ESI+0x14] at 0x3c1d0 (type field).
 * Confirmed: SUB EAX,2 / JZ / DEC / JZ / DEC / JNZ dispatch pattern.
 * Confirmed: datum_get uses DAT_005ab23c (prop_data) for param_2 lookup.
 * Confirmed: datum_absolute_index_to_index(prop_data, effect+0x18) at 0x3c21a.
 * Confirmed: actor_perception_create_orphan_from_friend push order
 * (first->last): param_1, iVar3+0x18, iVar2+0x1c, param_3+0x18; ADD ESP,0x10 at
 * 0x3c23b.
 */
void FUN_0003c1c0(int param_1, int param_2, int param_3)
{
  char *iVar2;
  char *iVar3;

  if (param_3 == 0)
    return;

  switch (*(short *)(param_3 + 0x14)) {
  case 2:
    FUN_00036b50(param_1, param_2);
    break;
  case 3:
    iVar2 = (char *)datum_get(*(data_t **)0x5ab23c, param_2);
    if (*(int *)(iVar2 + 0x1c) != -1) {
      iVar3 = (char *)(int)datum_absolute_index_to_index(
        *(data_t **)0x5ab23c, *(int *)(param_3 + 0x18));
      if (iVar3 != 0) {
        actor_perception_create_orphan_from_friend(
          param_1, *(int *)(iVar3 + 0x18), *(int *)(iVar2 + 0x1c),
          *(int *)(param_3 + 0x18));
        return;
      }
    }
    break;
  case 4:
    FUN_000377d0(param_1, param_2);
    return;
  }
}

/* 0x3c260 — Set or clear bit 0 in actor flags (field +0x6d0). */
void actor_unit_control_crouch(int actor_handle, char flag)
{
  char *actor;

  actor = (char *)datum_get(actor_data, actor_handle);
  if (flag)
    *(unsigned int *)(actor + 0x6d0) |= 1u;
  else
    *(unsigned int *)(actor + 0x6d0) &= ~1u;
}

/* 0x3c2a0 — Set bit 1 in actor flags (field +0x6d0). */
void actor_unit_control_jump(int actor_handle)
{
  char *actor;

  actor = (char *)datum_get(actor_data, actor_handle);
  *(unsigned int *)(actor + 0x6d0) |= 2u;
}

/* Set or clear bit 0x800 in actor flags at +0x6d0, and store target at +0x720.
 */
void actor_unit_control_primary_trigger(int actor_handle, char flag, int target)
{
  char *actor = (char *)datum_get(actor_data, actor_handle);
  if (flag) {
    *(uint32_t *)(actor + 0x6d0) |= 0x800;
  } else {
    *(uint32_t *)(actor + 0x6d0) &= ~0x800u;
  }
  *(int *)(actor + 0x720) = target;
}

/* Set or clear bit 0x1000 in actor flags at +0x6d0. */
void actor_unit_control_secondary_trigger(int actor_handle, char flag)
{
  char *actor = (char *)datum_get(actor_data, actor_handle);
  if (flag) {
    *(uint32_t *)(actor + 0x6d0) |= 0x1000;
  } else {
    *(uint32_t *)(actor + 0x6d0) &= ~0x1000u;
  }
}

/* Set bit 0x2000 in actor flags at +0x6d0. */
void actor_handle_communication(int actor_handle)
{
  char *actor = (char *)datum_get(actor_data, actor_handle);
  *(uint32_t *)(actor + 0x6d0) |= 0x2000;
}

/* 0x3c3a0 — Set or clear bit 0x20 in actor flags (field +0x6d0). */
void actor_unit_control_exact_facing(int actor_handle, char flag)
{
  char *actor;

  actor = (char *)datum_get(actor_data, actor_handle);
  if (flag)
    *(unsigned int *)(actor + 0x6d0) |= 0x20u;
  else
    *(unsigned int *)(actor + 0x6d0) &= ~0x20u;
}

/* 0x3c3e0 — Clear the actor's vehicle-leaving counter field at offset +0x6ec.
 */
void actor_unit_control_stop_animation_impulse(int actor_handle)
{
  char *actor;

  actor = (char *)datum_get(actor_data, actor_handle);
  *(int16_t *)(actor + 0x6ec) = -1;
}

/* FUN_0003c410 (0x3c410) — XBE naked draft (batch 69). */
#if defined(__clang__)
static void *(*const b3c410_tag)(int, int) = tag_get;
static int (*const b3c410_c119610)(data_t *data) = data_new_at_index;
static void *(*const b3c410_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void *(*const b3c410_memset)(void *, int, unsigned int) = csmemset;
static int *(*const b3c410_gseed)(void) = get_global_random_seed_address;
static float (*const b3c410_rmreal)(unsigned int *) = random_math_real;
static void (*const b3c410_c24b80)(int actor_handle, int param2) = actor_clear_discarded_firing_positions;
static void (*const b3c410_c3a810)(int actor_handle) = FUN_0003a810;

__attribute__((naked, noinline))
int FUN_0003c410(int actv_tag_index __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $8, %%esp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "orl $0xffffffff, %%edi\n\t"
      "cmpl %%edi, %%eax\n\t"
      "je .LFUN_0003c410_4\n\t"
      "pushl %%eax\n\t"
      "pushl $0x61637476\n\t"
      "call *%[tag]\n\t"
      "movl 0x10(%%eax), %%ebx\n\t"
      "addl $8, %%esp\n\t"
      "cmpl %%edi, %%ebx\n\t"
      "je .LFUN_0003c410_4\n\t"
      "pushl %%ebx\n\t"
      "pushl $0x61637472\n\t"
      "call *%[tag]\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "movl 0x6325a4, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c119610]\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl %%edi, %%eax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "je .LFUN_0003c410_5\n\t"
      "movl 0x6325a4, %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movl (%%eax), %%edx\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "shrl $0x1a, %%edx\n\t"
      "andb $1, %%dl\n\t"
      "movl %%ecx, 0x5c(%%esi)\n\t"
      "movb %%dl, 0x6(%%esi)\n\t"
      "movl %%ebx, 0x58(%%esi)\n\t"
      "movw 0x14(%%eax), %%dx\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "movw %%dx, 0x4(%%esi)\n\t"
      "movl %%edi, 0x18(%%esi)\n\t"
      "movb %%bl, 0x1c(%%esi)\n\t"
      "movl %%edi, 0x34(%%esi)\n\t"
      "movw %%di, 0x3a(%%esi)\n\t"
      "movw %%di, 0x3c(%%esi)\n\t"
      "movb %%bl, 0x9(%%esi)\n\t"
      "movl %%edi, 0x30(%%esi)\n\t"
      "movw %%di, 0x38(%%esi)\n\t"
      "movw %%bx, 0x1e(%%esi)\n\t"
      "movw %%bx, 0x20(%%esi)\n\t"
      "movl %%edi, 0x24(%%esi)\n\t"
      "movl %%edi, 0x28(%%esi)\n\t"
      "movb $1, 0x7(%%esi)\n\t"
      "movb %%bl, 0x8(%%esi)\n\t"
      "movl %%edi, 0xc(%%esi)\n\t"
      "movb $1, 0x13(%%esi)\n\t"
      "movb $1, 0x12(%%esi)\n\t"
      "movw %%bx, 0x4a(%%esi)\n\t"
      "movl %%edi, 0x50(%%esi)\n\t"
      "movl %%edi, 0x54(%%esi)\n\t"
      "movw %%di, 0x3b8(%%esi)\n\t"
      "movw %%di, 0x60(%%esi)\n\t"
      "movw %%di, 0x62(%%esi)\n\t"
      "movl %%edi, 0x64(%%esi)\n\t"
      "movb %%bl, 0x8e(%%esi)\n\t"
      "movw %%di, 0x90(%%esi)\n\t"
      "movl %%edi, 0x94(%%esi)\n\t"
      "movw %%bx, 0x6c(%%esi)\n\t"
      "movw $2, 0x6a(%%esi)\n\t"
      "movw %%bx, 0x6e(%%esi)\n\t"
      "movw %%bx, 0x72(%%esi)\n\t"
      "movw %%bx, 0x74(%%esi)\n\t"
      "movl %%edi, 0x88(%%esi)\n\t"
      "movb %%bl, 0x98(%%esi)\n\t"
      "movl (%%eax), %%ecx\n\t"
      "pushl $0x68\n\t"
      "shrl $0x15, %%ecx\n\t"
      "leal 0x350(%%esi), %%edx\n\t"
      "andb $1, %%cl\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edx\n\t"
      "movb %%cl, 0x99(%%esi)\n\t"
      "movl %%edi, 0x164(%%esi)\n\t"
      "movl %%edi, 0x158(%%esi)\n\t"
      "movb %%bl, 0x1c9(%%esi)\n\t"
      "movb %%bl, 0x1cc(%%esi)\n\t"
      "movl %%edi, 0x1d0(%%esi)\n\t"
      "movw %%bx, 0x1d4(%%esi)\n\t"
      "movl %%edi, 0x1dc(%%esi)\n\t"
      "call *%[memset]\n\t"
      "addl $0x14, %%esp\n\t"
      "movl %%edi, 0x370(%%esi)\n\t"
      "movl %%edi, 0x37c(%%esi)\n\t"
      "movl %%edi, 0x380(%%esi)\n\t"
      "movl %%edi, 0x36c(%%esi)\n\t"
      "movl %%edi, 0x384(%%esi)\n\t"
      "movl %%edi, 0x388(%%esi)\n\t"
      "movl %%edi, 0x398(%%esi)\n\t"
      "movl %%edi, 0x3a0(%%esi)\n\t"
      "movl %%edi, 0x3a4(%%esi)\n\t"
      "movl %%edi, 0x3ac(%%esi)\n\t"
      "movl %%edi, 0x3b0(%%esi)\n\t"
      "movl $0x3f800000, 0x3b4(%%esi)\n\t"
      "movl %%edi, 0x390(%%esi)\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movl %%edi, 0x394(%%esi)\n\t"
      "movl %%edi, 0x39c(%%esi)\n\t"
      "flds 0x90(%%eax)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_0003c410_3\n\t"
      "call *%[gseed]\n\t"
      "pushl %%eax\n\t"
      "call *%[rmreal]\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "fcomps 0x90(%%ecx)\n\t"
      "addl $4, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_0003c410_1\n\t"
      "movl $1, %%eax\n\t"
      "jmp .LFUN_0003c410_2\n\t"
      ".LFUN_0003c410_1:\n\t"
      "xorl %%eax, %%eax\n\t"
      ".LFUN_0003c410_2:\n\t"
      "movb %%al, 0x376(%%esi)\n\t"
      ".LFUN_0003c410_3:\n\t"
      "pushl $0x5c\n\t"
      "leal 0x4a8(%%esi), %%edx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edx\n\t"
      "movw %%bx, 0x3e8(%%esi)\n\t"
      "movw %%bx, 0x400(%%esi)\n\t"
      "movw %%bx, 0x46c(%%esi)\n\t"
      "movl %%edi, 0x480(%%esi)\n\t"
      "movl %%edi, 0x494(%%esi)\n\t"
      "call *%[memset]\n\t"
      "pushl $0x10\n\t"
      "leal 0x5c8(%%esi), %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "movb %%bl, 0x504(%%esi)\n\t"
      "movb %%bl, 0x505(%%esi)\n\t"
      "movw $1, 0x5f2(%%esi)\n\t"
      "movw %%bx, 0x5f4(%%esi)\n\t"
      "movw %%bx, 0x5f6(%%esi)\n\t"
      "movw %%bx, 0x5f8(%%esi)\n\t"
      "movw %%bx, 0x5fa(%%esi)\n\t"
      "movl %%ebx, 0x61c(%%esi)\n\t"
      "movl %%edi, 0x610(%%esi)\n\t"
      "movl %%edi, 0x6a4(%%esi)\n\t"
      "movl %%edi, 0x6b4(%%esi)\n\t"
      "call *%[memset]\n\t"
      "movw %%di, 0x5d8(%%esi)\n\t"
      "movw %%di, 0x5f0(%%esi)\n\t"
      "movw %%bx, 0x544(%%esi)\n\t"
      "movw %%bx, 0x548(%%esi)\n\t"
      "movl 0x31fc3c, %%edx\n\t"
      "movl (%%edx), %%eax\n\t"
      "leal 0x5b0(%%esi), %%ecx\n\t"
      "movl %%eax, (%%ecx)\n\t"
      "movl 0x4(%%edx), %%eax\n\t"
      "movl %%eax, 0x4(%%ecx)\n\t"
      "movl 0x8(%%edx), %%edx\n\t"
      "movl %%edx, 0x8(%%ecx)\n\t"
      "movl 0x31fc3c, %%ecx\n\t"
      "movl (%%ecx), %%edx\n\t"
      "leal 0x5a4(%%esi), %%eax\n\t"
      "movl %%edx, (%%eax)\n\t"
      "movl 0x4(%%ecx), %%edx\n\t"
      "movl %%edx, 0x4(%%eax)\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "movl %%ecx, 0x8(%%eax)\n\t"
      "movl 0x31fc3c, %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "leal 0x5bc(%%esi), %%edx\n\t"
      "movl %%ecx, (%%edx)\n\t"
      "movl 0x4(%%eax), %%ecx\n\t"
      "movl %%ecx, 0x4(%%edx)\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ecx\n\t"
      "movl %%eax, 0x8(%%edx)\n\t"
      "movb %%bl, 0x6cc(%%esi)\n\t"
      "movw $0x1e, 0x6ce(%%esi)\n\t"
      "movw %%bx, 0x268(%%esi)\n\t"
      "movl %%edi, 0x270(%%esi)\n\t"
      "movl %%edi, 0x26c(%%esi)\n\t"
      "movl %%edi, 0x278(%%esi)\n\t"
      "call *%[c24b80]\n\t"
      "movl %%edi, 0x3c0(%%esi)\n\t"
      "movl -0x8(%%ebp), %%esi\n\t"
      "movl 0x331f58, %%edx\n\t"
      "andl $0xffff, %%esi\n\t"
      "imull $0x657c, %%esi, %%esi\n\t"
      "pushl $0x657c\n\t"
      "addl %%edx, %%esi\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "call *%[memset]\n\t"
      "movl %%edi, 0x4(%%esi)\n\t"
      "movl %%edi, 0x5c(%%esi)\n\t"
      "movl %%edi, 0xc4(%%esi)\n\t"
      "movl %%edi, 0x104(%%esi)\n\t"
      "movl %%edi, 0x150(%%esi)\n\t"
      "movl %%edi, 0x168(%%esi)\n\t"
      "movl %%edi, 0x18c(%%esi)\n\t"
      "movl %%edi, 0x19c(%%esi)\n\t"
      "movl %%edi, 0x656c(%%esi)\n\t"
      "movw %%di, 0x6578(%%esi)\n\t"
      "movl -0x8(%%ebp), %%esi\n\t"
      "pushl %%esi\n\t"
      "call *%[c3a810]\n\t"
      "addl $0x30, %%esp\n\t"
      "movl %%esi, %%eax\n\t"
      "popl %%esi\n\t"
      "popl %%edi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0003c410_4:\n\t"
      "movl %%edi, %%eax\n\t"
      ".LFUN_0003c410_5:\n\t"
      "popl %%edi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [tag] "m"(b3c410_tag), [c119610] "m"(b3c410_c119610), [dget] "m"(b3c410_dget), [memset] "m"(b3c410_memset), [gseed] "m"(b3c410_gseed), [rmreal] "m"(b3c410_rmreal), [c24b80] "m"(b3c410_c24b80), [c3a810] "m"(b3c410_c3a810)
      : "memory");
}
#else
#error "FUN_0003c410: clang naked draft required"
#endif


/* actor_customize_unit (0x3c7c0) — actor_variant_setup_unit
 * Initializes a newly created unit from its actor variant (actv) tag data.
 * Sets perception ranges, grenade type, change colors, initial weapon,
 * grenade count, initial equipment, and deaf/blind flags. */
void actor_customize_unit(int actv_tag_index, int unit_index)
{
  char *actv_data;
  char *actr_data;
  char *unit_data;
  char *element;
  char *eqip_data;
  char placement[136];
  int object_handle;
  int i;
  int count;
  int *seed;
  float blend;
  float *out_color;
  float *copy_dest;

  actv_data = (char *)tag_get(0x61637476, actv_tag_index);
  actr_data = (char *)tag_get(0x61637472, *(int *)(actv_data + 0x10));
  unit_data = (char *)object_get_and_verify_type(unit_index, 3);

  if (*(float *)(actv_data + 0x200) > 0.0f ||
      *(float *)(actv_data + 0x204) > 0.0f) {
    FUN_001365d0(unit_index, (float *)(actv_data + 0x200),
                 (float *)(actv_data + 0x204));
  }

  if (*(short *)(actv_data + 0x20c) != 0) {
    *(short *)(unit_data + 0x126) = *(short *)(actv_data + 0x20c);
  }

  count = 0;
  for (i = 0; (short)i < *(int *)(actv_data + 0x22c); i = (int)(short)(count)) {
    element = (char *)tag_block_get_element(actv_data + 0x22c, i, 0x20);
    if ((short)count < 4) {
      out_color = (float *)(unit_data + (i * 3 + 0x4e) * 4);
      seed = get_global_random_seed_address();
      blend = random_math_real((unsigned int *)seed);
      FUN_0007c270(out_color, 1, (float *)element, (float *)(element + 0xc),
                   blend);
      copy_dest = (float *)(unit_data + (i * 3 + 0x5a) * 4);
      copy_dest[0] = out_color[0];
      copy_dest[1] = out_color[1];
      copy_dest[2] = out_color[2];
    }
    count = count + 1;
  }

  if (*(int *)(actv_data + 0x70) != -1) {
    object_placement_data_new(placement, *(int *)(actv_data + 0x70),
                              unit_index);
    object_handle = object_new(placement);
    if (object_handle != -1) {
      if (!unit_enter_seat(unit_index, object_handle, 2)) {
        object_delete(object_handle);
      }
    }
  }

  if (*(short *)(actv_data + 0x180) != -1) {
    seed = get_global_random_seed_address();
    unit_set_grenade_count(unit_index, *(short *)(actv_data + 0x180),
                           random_range((unsigned int *)seed,
                                        *(short *)(actv_data + 0x1d0),
                                        *(short *)(actv_data + 0x1d2) + 1));
  }

  if (*(int *)(actv_data + 0x1cc) != -1) {
    eqip_data = (char *)tag_get(0x65716970, *(int *)(actv_data + 0x1cc));
    if (*(short *)(eqip_data + 0x308) == 0 ||
        *(short *)(eqip_data + 0x308) == 6) {
      error(2, "cannot add grenades or non-powerups to an actor's inventory "
               "as equipment... try using the 'grenade' fields maybe?");
    } else {
      object_placement_data_new(placement, *(int *)(actv_data + 0x1cc),
                                unit_index);
      object_handle = object_new(placement);
      if (object_handle != -1) {
        if (!unit_pickup_equipment(unit_index, object_handle, 1)) {
          object_delete(object_handle);
        }
      }
    }
  }

  if ((*(unsigned char *)actv_data & 0x30) != 0) {
    if ((*(unsigned char *)actv_data & 0x20) != 0) {
      *(unsigned int *)(unit_data + 0x1b4) |= 0x20;
    }
    *(unsigned int *)(unit_data + 0x1b4) |= 0x10;
    *(float *)(unit_data + 0x32c) = 1.0f;
    if ((*(unsigned char *)actr_data & 0x20) != 0) {
      *(float *)(unit_data + 0x330) = 1.0f;
      return;
    }
    *(float *)(unit_data + 0x330) = 0.0f;
  }
}

/* actor_set_dormant (0x3ca40) — actor_set_object_activation
 *
 * Sets activation state on the actor's associated objects. Depending on
 * actor type (single-object vs swarm leader), activates/deactivates one
 * object, a linked list of objects, or all swarm member objects.
 * Always calls actor_verify_activation at the end regardless of path taken.
 *
 * Confirmed: datum_get(actor_data, actor_handle) at 0x3ca50.
 * Confirmed: actor+0x8 != 0 guard at 0x3ca5d.
 * Confirmed: actor+0x13 != flag guard at 0x3ca6b.
 * Confirmed: actor+0x6 branches single vs multi at 0x3ca72.
 * Confirmed: actor+0x18 = unit handle (single path) at 0x3cb23.
 * Confirmed: actor+0x24 = object list head, linked via obj+0x1ac.
 * Confirmed: actor+0x28 = swarm handle; datum_get(swarm_data, ...) at 0x3ca8b.
 * Confirmed: swarm+0x2 = count (int16); swarm+0x18[i*4] = handles.
 * Confirmed: object_activate (0x13fb30) when flag==0; object_deactivate when
 * flag!=0. Confirmed: actor+0x13 = flag written at 0x3cad0. Confirmed:
 * actor+0x14 = 0 (int16) when flag==0 at 0x3cad5. Confirmed:
 * actor_verify_activation(actor_handle) always called at 0x3cae0. */
void actor_set_dormant(int actor_handle, char flag)
{
  char *actor;
  char *swarm;
  char *obj;
  int obj_handle;
  int16_t i;

  actor = (char *)datum_get(actor_data, actor_handle);

  if (*(char *)(actor + 0x8) != 0 && *(char *)(actor + 0x13) != flag) {
    if (*(char *)(actor + 0x6) == 0) {
      if (*(int *)(actor + 0x18) != -1) {
        if (flag == 0) {
          object_activate(*(int *)(actor + 0x18));
        } else {
          object_deactivate(*(int *)(actor + 0x18));
        }
      }
    } else if (*(int *)(actor + 0x28) == -1) {
      obj_handle = *(int *)(actor + 0x24);
      while (obj_handle != -1) {
        obj = (char *)object_get_and_verify_type(obj_handle, 3);
        if (flag == 0) {
          object_activate(obj_handle);
        } else {
          object_deactivate(obj_handle);
        }
        obj_handle = *(int *)(obj + 0x1ac);
      }
    } else {
      swarm = (char *)datum_get(swarm_data, *(int *)(actor + 0x28));
      i = 0;
      while (i < *(int16_t *)(swarm + 0x2)) {
        if (flag == 0) {
          object_activate(*(int *)(swarm + 0x18 + (int)i * 4));
        } else {
          object_deactivate(*(int *)(swarm + 0x18 + (int)i * 4));
        }
        i++;
      }
    }
    *(char *)(actor + 0x13) = flag;
    if (flag == 0) {
      *(int16_t *)(actor + 0x14) = 0;
    }
  }

  actor_verify_activation(actor_handle);
}

/* 0x3cb50 — Register a new unit_index+swarm_component pair into the swarm
 * record's unit table.
 * Clears component+0x14 (existing unit reference), appends unit_index to
 * swarm unit array at swarm+0x18[count] and swarm_component_handle to the
 * component array at swarm+0x58[count], increments swarm+0x2 (unit_count),
 * then calls actor_switch_props to link the unit/component.
 * Asserts unit_count < 16 before insertion.
 * Confirmed ABI: swarm_handle @<eax>, swarm_component_handle @<edi>,
 *                unit_index @<ebx>.
 */
void FUN_0003cb50(int swarm_handle, int swarm_component_handle, int unit_index)
{
  char *swarm;
  char *component;
  short count;

  swarm = (char *)datum_get(swarm_data, swarm_handle);
  component = (char *)datum_get(swarm_component_data, swarm_component_handle);
  *(int *)(component + 0x14) = -1;

  if (*(short *)(swarm + 0x2) >= 16) {
    display_assert("swarm->unit_count < MAXIMUM_NUMBER_OF_UNITS_PER_SWARM",
                   "c:\\halo\\SOURCE\\ai\\actors.c", 0x4dc, 1);
    system_exit(-1);
  }

  count = *(short *)(swarm + 0x2);
  *(int *)(swarm + 0x18 + (int)count * 4) = unit_index;
  count = *(short *)(swarm + 0x2);
  *(int *)(swarm + 0x58 + (int)count * 4) = swarm_component_handle;
  *(short *)(swarm + 0x2) = *(short *)(swarm + 0x2) + 1;

  actor_switch_props(unit_index, swarm_component_handle);
}

/* actor_delete_props (0x3cbc0) — actor_clean_props
 *
 * Clean up all props associated with an actor. Iterates actor+0x50 linked list,
 * calling FUN_0003b410 to clear prop references and prop_iterator_next to
 * delete each prop, until the list is empty.
 *
 * Confirmed: datum_get(actor_data, actor_handle) at 0x3cbcf.
 * Confirmed: actor+0x50 (prop list head) checked against -1 at 0x3cbdc.
 * Confirmed: FUN_0003b410(actor_handle, prop, -1) at 0x3cbe5.
 * Confirmed: prop_iterator_next(actor_handle, actor+0x50) at 0x3cbef.
 * Confirmed: loop continues while actor+0x50 != -1 at 0x3cbfd. */
void actor_delete_props(int actor_handle)
{
  char *actor;
  int prop_handle;

  actor = (char *)datum_get(actor_data, actor_handle);
  prop_handle = *(int *)(actor + 0x50);

  while (prop_handle != -1) {
    FUN_0003b410(actor_handle, prop_handle, -1);
    prop_iterator_next(actor_handle, *(int *)(actor + 0x50));
    prop_handle = *(int *)(actor + 0x50);
  }
}

/* actor_delete (0x3cc10) — actor_delete
 *
 * Delete an actor and clean up all references. Asserts the actor is not the
 * currently updating actor. Clears global references if they match, removes
 * the actor from encounter or encounterless list, detaches all units, cleans
 * up props, clears prop actor references, and finally deletes the actor datum.
 *
 * Confirmed: datum_get(actor_data, actor_handle) at 0x3cc23.
 * Confirmed: assert actor_index != global_updating_actor_index at 0x3cc37.
 * Confirmed: DAT_005ac9f8 and DAT_006323b4 cleared if equal to actor_handle.
 * Confirmed: actor+9 flag selects encounterless_detach_actor (encounterless) vs
 * encounter_detach_actor. Confirmed: actor+6 flag selects
 * actor_swarm_cache_delete+loop vs actor_detach_from_unit path. Confirmed:
 * actor_delete_props at 0x3cccc, data_iterator on DAT_005ab23c at 0x3ccdc.
 * Confirmed: ai_debug_actor_deleted at 0x3cd0a, ai_conversation_actor_deleted
 * at 0x3cd10. Confirmed: datum_delete(actor_data, actor_handle) at 0x3cd1c. */
void actor_delete(int actor_handle, int flag)
{
  char *actor;
  char iter[0x10];
  char *prop;
  int unit_handle;

  actor = (char *)datum_get(actor_data, actor_handle);

  /* Assert not deleting the currently updating actor */
  if (actor_handle == *(int *)0x2c8728) {
    display_assert("actor_index != global_updating_actor_index",
                   "c:\\halo\\SOURCE\\ai\\actors.c", 0x5d0, 1);
    system_exit(-1);
  }

  /* Clear global references if they match */
  if (*(int *)0x5ac9f8 == actor_handle) {
    *(int *)0x5ac9f8 = -1;
  }
  if (*(int *)0x6323b4 == actor_handle) {
    *(int *)0x6323b4 = -1;
  }

  /* Remove from encounter or encounterless list */
  if (*(char *)(actor + 9) == 0) {
    encounter_detach_actor(actor_handle, (char)flag);
  } else {
    encounterless_detach_actor(actor_handle);
  }

  /* Detach units */
  if (*(char *)(actor + 6) == 0) {
    /* Non-swarm: single unit detach */
    actor_detach_from_unit(actor_handle);
  } else {
    /* Swarm: delete swarm data and detach all units */
    actor_swarm_cache_delete(actor_handle);
    unit_handle = *(int *)(actor + 0x24);
    while (unit_handle != -1) {
      actor_swarm_detach_from_unit(actor_handle, unit_handle);
      unit_handle = *(int *)(actor + 0x24);
    }
  }

  /* Clean up props */
  actor_delete_props(actor_handle);

  /* Clear prop actor references */
  data_iterator_new((data_iter_t *)iter, *(data_t **)0x5ab23c);
  prop = (char *)data_iterator_next((data_iter_t *)iter);
  while (prop != NULL) {
    if (*(int *)(prop + 0x1c) == actor_handle) {
      *(int *)(prop + 0x1c) = -1;
    }
    prop = (char *)data_iterator_next((data_iter_t *)iter);
  }

  /* Final cleanup */
  ai_debug_actor_deleted(actor_handle);
  ai_conversation_actor_deleted(actor_handle);

  /* Delete the actor record */
  datum_delete(actor_data, actor_handle);
}

/* actor_swarm_cache_new (0x3cd30) — actor_allocate_swarm_components
 *
 * Allocate a swarm record and swarm-component slots for a swarm actor.
 * Called by actor_set_active when activating a swarm actor
 * (actor+0x6 != 0). Idempotent: returns early if actor+0x28 (swarm
 * cache handle) is already set.
 *
 * Steps:
 *   1. datum_get(actor_data, actor_handle) -> actor ptr.
 *   2. If actor+0x28 != -1, return (already allocated).
 *   3. data_new_at_index(swarm_data) -> swarm_handle; store at actor+0x28.
 *      On failure, log "exceeded MAXIMUM_NUMBER_OF_ACTIVE_SWARMS (32)".
 *   4. datum_get(swarm_data, swarm_handle) -> swarm ptr.
 *   5. Assert actor+0x1e (swarm_unit_count, short) <= 0x10.
 *   6. Init swarm: swarm+4 = actor_handle, swarm+2 = 0 (unit count).
 *   7. Walk unit chain from actor+0x24. For each unit:
 *      a. object_get_and_verify_type(unit_handle, 3) -> unit ptr.
 *      b. data_new_at_index(swarm_component_data) -> component_handle.
 *         On failure, log "unable to create any more swarm components
 *         (max 256)" and break.
 *      c. FUN_0003cb50(swarm_handle @eax, component_handle @edi,
 *         unit_handle @ebx) — initialize the component slot.
 *      d. Advance to next unit: unit_ptr+0x1ac.
 *
 * Confirmed: datum_get(actor_data=DAT_006325a4, actor_handle) at 0x3cd42.
 * Confirmed: actor+0x28 == -1 guard at 0x3cd49-0x3cd52.
 * Confirmed: data_new_at_index(swarm_data=DAT_006325a0) at 0x3cd5f; result
 *   stored at actor+0x28 (0x3cd6a). Confirmed: error("exceeded
 *   MAXIMUM_NUMBER_OF_ACTIVE_SWARMS (%d)", 0x20) at 0x3cd78 on failure.
 * Confirmed: datum_get(swarm_data, swarm_handle) at 0x3cd91.
 * Confirmed: unit chain head from actor+0x24 at 0x3cd96.
 * Confirmed: assert (word ptr [ESI+0x1e]) <= 0x10 at 0x3cd9c; display_assert
 *   at 0x3cdb6 + system_exit(-1) at 0x3cdbd on violation (line 0x622).
 * Confirmed: swarm+4 = actor_handle at 0x3cdcb; swarm+2 = 0 at 0x3cdce.
 * Confirmed: unit chain -1 guard (JZ to return) at 0x3cdd4.
 * Confirmed: object_get_and_verify_type(unit_handle, 3) at 0x3cdd9; result
 *   stored local at [EBP-4] (0x3cde5).
 * Confirmed: data_new_at_index(swarm_component_data=DAT_0063259c) at 0x3cde8;
 *   -1 check at 0x3cdf0; JZ to error at 0x3ce17.
 * Confirmed: EDI=component_handle (0x3cdf5), EAX=swarm_handle from
 *   actor+0x28 (0x3cdf7), CALL FUN_0003cb50 at 0x3cdfa.
 * Confirmed: next unit from [EBP-4]+0x1ac at 0x3cdff-0x3ce02; loop back
 *   at 0x3ce0b if != -1; return at 0x3ce0d-0x3ce16 when chain ends.
 * Confirmed: error("unable to create any more swarm components (max %d)",
 *   0x100) at 0x3ce23 when component alloc fails. */
void actor_swarm_cache_new(int actor_handle)
{
  char *actor;
  int swarm_handle;
  char *swarm;
  int unit_handle;
  char *unit;
  int component_handle;

  actor = (char *)datum_get(actor_data, actor_handle);

  if (*(int *)(actor + 0x28) == -1) {
    swarm_handle = data_new_at_index(swarm_data);
    *(int *)(actor + 0x28) = swarm_handle;
    if (swarm_handle == -1) {
      error(2, "exceeded MAXIMUM_NUMBER_OF_ACTIVE_SWARMS (%d)", 0x20);
      return;
    }

    swarm = (char *)datum_get(swarm_data, swarm_handle);
    unit_handle = *(int *)(actor + 0x24);

    if (*(short *)(actor + 0x1e) > 0x10) {
      display_assert(
        "actor->meta.swarm_unit_count <= MAXIMUM_NUMBER_OF_UNITS_PER_SWARM",
        "c:\\halo\\SOURCE\\ai\\actors.c", 0x622, 1);
      system_exit(-1);
    }

    *(int *)(swarm + 4) = actor_handle;
    *(short *)(swarm + 2) = 0;

    if (unit_handle != -1) {
      while (1) {
        unit = (char *)object_get_and_verify_type(unit_handle, 3);
        component_handle = data_new_at_index(swarm_component_data);
        if (component_handle == -1) {
          error(2, "unable to create any more swarm components (max %d)",
                0x100);
          return;
        }
        FUN_0003cb50(swarm_handle, component_handle, unit_handle);
        unit_handle = *(int *)(unit + 0x1ac);
        if (unit_handle == -1) {
          return;
        }
      }
    }
  }
}

/*
 * actor_get_running_blind_vector (0x3ce40) — compute the run-blind direction
 * for an actor and normalize it.
 *
 * Asserts vector_out != NULL (display_assert + system_exit if NULL).
 * If actor[6] != 0 (swarm): return 0 immediately (no vector).
 * If actor[0x504] != 0: integer-copy the 3 floats at actor+0x518 to vector_out.
 * Else if actor[0x4a8] != 0: compute difference
 *   actor+0x488/0x48c/0x490 minus actor+0x12c/0x130/0x134.
 * Else: return 0 immediately (no blind target).
 * Then: normalize3d(vector_out); if length == 0, return 1 (degenerate).
 * On successful normalization, return 0.
 *
 * Confirmed: datum_get(actor_data, actor_handle) at 0x3ce51.
 * Confirmed: NULL assert with display_assert("run_vector", ..., 0x7ae, 1)
 *   + system_exit(-1) at 0x3ce75/0x3ce7c.
 * Confirmed: TEST [ESI+6] / JNZ 0x3cf04 at 0x3ce84/0x3ce89 (swarm guard).
 * Confirmed: TEST [ESI+0x504] / JZ 0x3ceaf at 0x3ce8b/0x3ce93.
 * Confirmed: MOV EAX/ECX/EAX integer copy from ESI+0x518 at 0x3ce9b-0x3ceaa.
 * Confirmed: FLD/FSUB/FSTP triples for 0x488-0x12c, 0x48c-0x130, 0x490-0x134
 *   at 0x3ceb9-0x3cee2.
 * Confirmed: CALL normalize3d(0x13010) at 0x3cee8.
 * Confirmed: FCOMP [0x2533c0] / TEST AH,0x44 / JP 0x3cf04 at 0x3ceed-0x3cefb.
 * Confirmed: XOR AL,AL at 0x3ceff (return 0 = normalized ok).
 * Confirmed: MOV AL,BL at 0x3cf06 (return BL = initial 0 or 1 after normalize).
 * actors.obj / actors.c
 */
char actor_get_running_blind_vector(int actor_handle, float *vector_out)
{
  char *actor;

  actor = (char *)datum_get(actor_data, actor_handle);
  if (vector_out == NULL) {
    display_assert("run_vector", "c:\\halo\\SOURCE\\ai\\actors.c", 0x7ae, 1);
    system_exit(-1);
  }
  if (*(char *)(actor + 6) != '\0') {
    return 0;
  }
  if (*(char *)(actor + 0x504) != '\0') {
    ((int *)vector_out)[0] = *(int *)(actor + 0x518);
    ((int *)vector_out)[1] = *(int *)(actor + 0x51c);
    ((int *)vector_out)[2] = *(int *)(actor + 0x520);
  } else {
    if (*(char *)(actor + 0x4a8) == '\0') {
      return 0;
    }
    vector_out[0] = *(float *)(actor + 0x488) - *(float *)(actor + 0x12c);
    vector_out[1] = *(float *)(actor + 0x48c) - *(float *)(actor + 0x130);
    vector_out[2] = *(float *)(actor + 0x490) - *(float *)(actor + 0x134);
  }
  if (normalize3d(vector_out) != *(float *)0x2533c0) {
    return 0;
  }
  return 1;
}

/* actor_kill (0x3cf10) — actor_set_unit_dead_flag
 *
 * Marks actor's unit(s) with a "dead" flag in the unit's flags byte at
 * offset 0xb6, then triggers actor_delete and encounter status update.
 * If param_2 is non-zero, sets bit 0x40 (killed by player?); otherwise
 * sets bit 0x20 (killed by AI?). If param_3 is non-zero, only sets the
 * flag without performing deletion/encounter update.
 *
 * For non-swarm actors (actor+0x6 == 0): operates on the single unit at
 * actor+0x18, then calls actor_detach_from_unit.
 * For swarm actors (actor+0x6 != 0): iterates the swarm unit chain
 * starting at actor+0x24, following unit+0x1ac links, calling
 * actor_swarm_detach_from_unit for each unless param_3 is set.
 *
 * Confirmed: datum_get(actor_data, actor_handle) at 0x3cf20.
 * Confirmed: actor+0x6 (swarm flag) tested at 0x3cf2e.
 * Confirmed: actor+0x34 stored as encounter_handle at 0x3cf28/0x3cf30.
 * Confirmed: actor+0x18 (unit_handle) for non-swarm path at 0x3cfae.
 * Confirmed: actor+0x24 (first swarm unit) for swarm path at 0x3cf36.
 * Confirmed: unit+0xb6 OR 0x20 or 0x40 at 0x3cf52/0x3cf5b/0x3cfc3/0x3cfcc.
 * Confirmed: unit+0x1ac (next swarm unit link) at 0x3cf76.
 * Confirmed: actor_swarm_detach_from_unit(actor_handle, unit_handle) at
 * 0x3cf6e. Confirmed: actor_detach_from_unit(actor_handle) at 0x3cfdb.
 * Confirmed: actor_delete(actor_handle, 1) at 0x3cf92.
 * Confirmed: encounter_update_status(encounter_handle) at 0x3cfa0 if != -1. */
void actor_kill(int actor_handle, char by_player, char no_delete)
{
  char *actor;
  int encounter_handle;

  actor = (char *)datum_get(actor_data, actor_handle);
  encounter_handle = *(int *)(actor + 0x34);

  if (*(char *)(actor + 0x6) != 0) {
    /* Swarm: iterate unit chain */
    int unit_handle = *(int *)(actor + 0x24);
    while (unit_handle != -1) {
      char *unit = (char *)object_get_and_verify_type(unit_handle, 3);
      if (by_player != 0) {
        *(unsigned char *)(unit + 0xb6) |= (unsigned char)0x40;
      } else {
        *(unsigned char *)(unit + 0xb6) |= (unsigned char)0x20;
      }
      if (no_delete == 0) {
        actor_swarm_detach_from_unit(actor_handle, unit_handle);
      }
      unit_handle = *(int *)(unit + 0x1ac);
    }
    if (no_delete != 0) {
      return;
    }
  } else {
    /* Non-swarm: single unit */
    char *unit = (char *)object_get_and_verify_type(*(int *)(actor + 0x18), 3);
    if (by_player != 0) {
      *(unsigned char *)(unit + 0xb6) |= 0x40;
    } else {
      *(unsigned char *)(unit + 0xb6) |= 0x20;
    }
    if (no_delete != 0) {
      return;
    }
    actor_detach_from_unit(actor_handle);
  }
  actor_delete(actor_handle, 1);
  if (encounter_handle != -1) {
    encounter_update_status(encounter_handle);
  }
}

/* actor_died (0x3cff0) — actor_update_weapon_state
 *
 * Update weapon firing state for an actor. If the actor is in combat state 3
 * (attacking) with burst count > 1, performs accuracy-based random firing
 * check. Also handles weapon ammo distribution and magazine rounds for the
 * actor's weapon. Calls actor_delete to mark actor as needing cleanup, and if
 * actor has an encounter, calls encounter_update_status to update encounter
 * state.
 *
 * Confirmed: datum_get(actor_data, actor_handle) at 0x3d004.
 * Confirmed: tag_get(0x61637476, actor+0x5c) at 0x3d014.
 * Confirmed: actor+0x34 stored for encounter_handle check at end.
 * Confirmed: actor+0x6a == 3 and actor+0x6e > 1 condition at 0x3d021-0x3d034.
 * Confirmed: object_get_and_verify_type(actor+0x18, 3) at 0x3d040, 0x3d064.
 * Confirmed: unit_is_alive(actor+0x18) at 0x3d04e.
 * Confirmed: unit_get_weapon(actor+0x18, unit+0x2a2) at 0x3d077.
 * Confirmed: accuracy clamping to [0.1f, 0.6f] at 0x3d096-0x3d0d7.
 * Confirmed: accuracy boost by 1.5x under certain conditions at
 * 0x3d0fe-0x3d12d. Confirmed: random check against accuracy at 0x3d12f-0x3d145.
 * Confirmed: burst duration from tag+0x98, clamped to [0.05f, 2.0f], * 30.0f.
 * Confirmed: unit_persistent_control(unit, ticks, 0x800) at 0x3d1c8.
 * Confirmed: actor_delete(actor_handle, 1) at 0x3d304.
 * Confirmed: encounter_update_status(encounter_handle) at 0x3d318 if actor+0x34
 * != -1. */
void actor_died(int actor_handle)
{
  char *actor;
  char *tag;
  char *unit;
  char *unit2;
  char *ai_globals;
  int encounter_handle;
  int weapon_handle;
  float accuracy;
  float boosted;
  float burst_duration;
  float random_val;
  float ammo_fraction;
  int ticks;
  int *seed;

  actor = (char *)datum_get(actor_data, actor_handle);
  tag = (char *)tag_get(0x61637476, *(int *)(actor + 0x5c));
  encounter_handle = *(int *)(actor + 0x34);

  /* Combat state 3 with burst count > 1: perform firing logic */
  if (*(short *)(actor + 0x6a) == 3 && *(short *)(actor + 0x6e) > 1) {
    unit = (char *)object_get_and_verify_type(*(int *)(actor + 0x18), 3);

    if (unit_is_alive(*(int *)(actor + 0x18))) {
      char *unit2 =
        (char *)object_get_and_verify_type(*(int *)(actor + 0x18), 3);
      weapon_handle = unit_get_weapon(
        *(int *)(actor + 0x18), (int)(uint16_t)(*(int16_t *)(unit2 + 0x2a2)));

      if (weapon_handle != -1 && *(char *)(unit + 0x23c) > 0) {
        /* Clamp accuracy to [0.1f, 0.6f] */
        if (*(float *)(tag + 0x94) < 0.1f) {
          accuracy = 0.1f;
        } else if (*(float *)(tag + 0x94) > 0.6f) {
          accuracy = 0.6f;
        } else {
          accuracy = *(float *)(tag + 0x94);
        }

        /* Accuracy boost under certain conditions */
        if (*(char *)(actor + 0x378) != 0 ||
            (*(short *)(actor + 0x60c) > 0 &&
             *(float *)(actor + 0x648) < *(float *)0x254644)) {
          boosted = accuracy * 1.5f;
          if (boosted > 0.6f) {
            boosted = 0.6f;
          }
          if (boosted > accuracy) {
            accuracy = boosted;
          }
        }

        /* Random check against accuracy */
        seed = get_global_random_seed_address();
        if (random_math_real((unsigned int *)seed) < accuracy) {
          /* Calculate burst duration in ticks */
          if (*(float *)(tag + 0x98) == 0.0f) {
            FUN_000121e0(0.8f, 1.3f);
          }

          /* Clamp burst_seconds to [0.05f, 2.0f] */
          if (*(float *)(tag + 0x98) < 0.05f) {
            burst_duration = 0.05f;
          } else if (*(float *)(tag + 0x98) > 2.0f) {
            burst_duration = 2.0f;
          } else {
            burst_duration = *(float *)(tag + 0x98);
          }

          /* Convert to ticks (30 ticks per second) */
          ticks = (int)(burst_duration * 30.0f);
          unit_persistent_control(*(int *)(actor + 0x18), ticks, 0x800);
          *(char *)(unit + 0x23c) = (char)ticks;
        }
      }
    }
  }

  /* Update weapon ammo state */
  unit = (char *)object_get_and_verify_type(*(int *)(actor + 0x18), 3);

  seed = get_global_random_seed_address();
  random_val = random_math_real((unsigned int *)seed);

  unit2 = (char *)object_get_and_verify_type(*(int *)(actor + 0x18), 3);
  weapon_handle =
    unit_get_weapon(*(int *)(actor + 0x18), (int)(*(int16_t *)(unit2 + 0x2a2)));

  /* Check global flag for clearing weapon state */
  ai_globals = *(char **)0x632574;
  if (*(char *)(ai_globals + 0x3b4) == 0 ||
      random_val < *(float *)(tag + 0x1d4)) {
    csmemset(unit + 0x2ce, 0, 2);
  }

  if (weapon_handle != -1) {
    /* Set weapon ammo fraction if tag defines it */
    if (*(float *)(tag + 0x1d8) > 0.0f || *(float *)(tag + 0x1dc) > 0.0f) {
      seed = get_global_random_seed_address();
      ammo_fraction = random_real_range(seed, *(float *)(tag + 0x1d8),
                                        *(float *)(tag + 0x1dc));
      weapon_set_current_amount(weapon_handle, ammo_fraction);
    }

    /* Set magazine rounds if tag defines it */
    if (*(short *)(tag + 0x1e0) > 0 || *(short *)(tag + 0x1e2) > 0) {
      int16_t rounds = 0;
      seed = get_global_random_seed_address();
      rounds = random_range((unsigned int *)seed, *(short *)(tag + 0x1e0),
                            *(short *)(tag + 0x1e2) + 1);
      weapon_set_total_rounds(weapon_handle, &rounds);
    }
  }

  actor_delete(actor_handle, 1);

  if (encounter_handle != -1) {
    encounter_update_status(encounter_handle);
  }
}

/* actor_swarm_unit_died (0x3d330) — actor_swarm_unit_detach_and_delete
 *
 * Detaches a swarm unit from its actor and, if the swarm is now empty (no
 * remaining units), deletes the actor and updates the encounter state.
 *
 * Asserts that the actor is a swarm type (actor+6 != 0). Calls
 * actor_swarm_detach_from_unit(actor_handle, unit_handle) to remove the unit.
 * If swarm_unit_count (actor+0x1e) drops to zero, asserts that
 * swarm_unit_index (actor+0x24) == NONE, then calls actor_delete to delete
 * the actor and, if encounter handle (actor+0x34) is valid, calls
 * encounter_update_status.
 *
 * Confirmed: cdecl 2-arg (actor_handle at EBP+8, unit_handle at EBP+C).
 * Confirmed: datum_get(actor_data, actor_handle) at 0x3d33f.
 * Confirmed: swarm check byte[ESI+6] at 0x3d346; assert "actor->meta.swarm"
 *   actors.c line 0x8e0; system_exit(-1).
 * Confirmed: actor_swarm_detach_from_unit(actor_handle, unit_handle) at
 * 0x3d375. Confirmed: swarm_unit_count check word[ESI+0x1e] at 0x3d37d; JNZ
 * exits. Confirmed: assert "actor->meta.swarm_unit_index == NONE" for
 * int[ESI+0x24] at 0x3d384; actors.c line 0x8e7; system_exit(-1). Confirmed:
 * encounter_handle = int[ESI+0x34] at 0x3d389. Confirmed:
 * actor_delete(actor_handle, 1) at 0x3d3b1. Confirmed:
 * encounter_update_status(encounter_handle) at 0x3d3bf if != -1. */
void actor_swarm_unit_died(int actor_handle, int unit_handle)
{
  char *actor;
  int encounter_handle;

  actor = (char *)datum_get(actor_data, actor_handle);
  if (*(char *)(actor + 6) == '\0') {
    display_assert("actor->meta.swarm", "c:\\halo\\SOURCE\\ai\\actors.c", 0x8e0,
                   1);
    system_exit(-1);
  }
  actor_swarm_detach_from_unit(actor_handle, unit_handle);
  if (*(int16_t *)(actor + 0x1e) == 0) {
    encounter_handle = *(int *)(actor + 0x34);
    if (*(int *)(actor + 0x24) != -1) {
      display_assert("actor->meta.swarm_unit_index == NONE",
                     "c:\\halo\\SOURCE\\ai\\actors.c", 0x8e7, 1);
      system_exit(-1);
    }
    actor_delete(actor_handle, 1);
    if (encounter_handle != -1) {
      encounter_update_status(encounter_handle);
    }
  }
}

/* FUN_0003d9f0 (0x3d9f0) — actor_pre_activate_check
 *
 * Validates an actor before activation and updates per-tick AI counters.
 * Returns 1 if the actor may proceed to full activation, 0 if it was erased.
 *
 * Per-tick counter updates (always, before any early-outs):
 *   - word[0x5abc44]++ : total actor count increment
 *   - if actor+0x13 == 0: word[0x5abccc]++  (non-dormant actor count)
 *   - if actor+6 == 0: word[0x5abddc]++ (non-swarm count), else add
 *     short[actor+0x1e] (swarm_unit_count) to word[0x5abddc]
 *   - same conditional logic for word[0x5abe64] gated on actor+0x13==0
 *
 * Error path (swarm actor without swarm cache at actor+0x28 == -1):
 *   - Fires csprintf assert at actors.c line 0xaad (2733).
 *   - Calls actor_erase(actor_handle, 0) to erase units.
 *   - Returns 0.
 *
 * Counter reset block (executed before dormancy/activation checks):
 *   - byte[actor+0x4a4] = 0
 *   - if int[actor+0x78] > 0: decrement; if reaches 0, clear word[actor+0x74]
 *   - if short[actor+0x92] > 0: decrement
 *
 * Activation readiness checks (return 1 to allow activation):
 *   - If actor+0x12 == 0 (no player-presence?) OR combined flags != 0:
 *       call actor_set_dormant(actor_handle, 0); return 1.
 *   - If actor+0x13 != 0 (dormant): return 1 (dormant actors always pass).
 *   - If actor_action_try_to_panic(actor_handle) returns 2 (action already in
 * flight): return 1.
 *   - Encounter validity check: if actor+0x270 != -1:
 *       datum_get(DAT_005ab23c, actor+0x270); check +0x12e, +0x60, +0x127;
 *       if valid encounter and action type in [2,3] → return 1;
 *       if action type in [4,5] and actor_action_try_to_panic returned 3 →
 * return 1.
 *   - FUN_0002a3d0(actor_handle) checks byte at actor+0x4a8 (non-zero =
 * vehicle?): if mode==3 and actor+0x6c==6 and biped+0x62==1 → return 1. if
 * mode==5 and encounter+0x12e!=0 → return 1.
 *   - Increment word[actor+0x14] (idle ticks); if > 0x3b (59): deactivate and
 * return 1.
 *
 * Classification evidence: references actors.c string at 0x3da76 (line 0xaad).
 *   Called by FUN_0003ec80 (actor_activate) at 0x3ecc3; result tested with
 *   TEST AL,AL; JZ 0x3edae.
 *
 * Confirmed: cdecl, single stack arg actor_handle. Return via AL.
 * Confirmed: [EBP-1] initialised to 1 at 0x3da16; set to 0 at 0x3daa3 only.
 *   All exits load AL from [EBP-1], so default return is 1.
 * Confirmed: ESI = datum_get result (actor record pointer) throughout.
 * Confirmed: EDI = actor_handle (from [EBP+0x8]) at 0x3d9fb; preserved until
 *   overwritten by actor_action_try_to_panic return at 0x3db2a, then restored
 * at 0x3db92. Confirmed: encounter data table at DAT_005ab23c (0x5ab23c).
 * Confirmed: actor_set_dormant(actor_handle, flag) cdecl 2 args — ADD ESP,0x8.
 * Confirmed: actor_action_try_to_panic(actor_handle) cdecl 1 arg → short action
 * type in AX. Return stored in DI; compared as 16-bit (CMP DI,0x2 / CMP
 * DI,0x3). Confirmed: FUN_0002a3d0(actor_handle) cdecl 1 arg → byte at
 * actor+0x4a8. Confirmed: mode==3 path: CMP word[ESI+0x6c],6; CMP
 * word[EBX+0x62],1 (biped rec). EBX = DAT_005ab270 datum_get result (biped
 * record), set at 0x3daf7. Confirmed: mode==5 path: datum_get(DAT_005ab23c,
 * actor+0x470) → check +0x12e. Confirmed: ADD ESP,0x18 at 0x3da9c cleans
 * csprintf(3)+display_assert(1)+ actor_erase(2) = 6 dwords after partial ADD
 * ESP,0xc at 0x3da8b. Inferred: actor+0x13 = dormant flag (byte); actor+6 =
 * swarm flag (byte). Inferred: actor+0x28 = swarm cache handle (int); -1 = no
 * cache. Inferred: actor+0x1e = swarm unit count (short). Inferred: actor+0x78
 * = timer/countdown int; actor+0x74 = associated mode word. Inferred:
 * actor+0x92 = secondary tick countdown (short). Inferred: actor+0x34 = biped
 * handle (int); DAT_005ab270 = biped data table. Inferred: actor+0xa = actor
 * flags byte; biped+0xc = biped flags byte. Inferred: actor+0x12 =
 * player-proximity or targeting flag (byte). Inferred: actor+0x14 = idle tick
 * counter (short); threshold 0x3b (59 ticks). Inferred: actor+0x270 = encounter
 * handle (int). Inferred: encounter+0x12e = scripted flag (char);
 * encounter+0x60 = active (char); encounter+0x127 = some exclusion flag (char);
 * encounter+0x24 = type/state short. Inferred: actor+0x4a8 = in-vehicle or
 * mounted flag (byte, read by FUN_0002a3d0). Inferred: actor+0x46c = activation
 * mode (short); 3=biped-ride, 5=encounter-board. Inferred: actor+0x470 =
 * secondary encounter handle (int) used with mode==5. */
/* 0x3d3d0 — Set or restore actor dormancy state and fields +0x6a/+0x6c.
 * If param_2 is non-zero: clears +0x6a and +0x6c, calls actor_delete_props,
 * FUN_0003b860, and actor_set_dormant(0). Otherwise sets +0x6a to 2 if it was
 * previously 0. */
void actor_braindead(int actor_handle, char param_2)
{
  char *actor;

  actor = (char *)datum_get(actor_data, actor_handle);
  if (param_2 != '\0') {
    *(int16_t *)(actor + 0x6a) = 0;
    *(int16_t *)(actor + 0x6c) = 0;
    actor_delete_props(actor_handle);
    FUN_0003b860(actor_handle);
    actor_set_dormant(actor_handle, 0);
    return;
  }
  if (*(int16_t *)(actor + 0x6a) == 0)
    *(int16_t *)(actor + 0x6a) = 2;
}

void actor_handle_unit_effect(int actor_handle, int prop_handle,
                              int16_t unit_effect)
{
  char *actor;
  char *prop;
  char local_1;

  actor = (char *)datum_get(actor_data, actor_handle);
  prop = (char *)datum_get(prop_data, prop_handle);

  if (*(int *)(actor + 0x34) != -1) {
    local_1 = *(
      char *)((char *)datum_get(*(data_t **)0x5ab270, *(int *)(actor + 0x34)) +
              0x41);
  } else {
    local_1 = 0;
  }

  if (game_connection() == 0 && *(char *)0x5ac9cc != 0) {
    local_1 = 1;
  }

  if (*(int16_t *)(prop + 0x66) == (int16_t)-1 ||
      unit_effect >= *(int16_t *)(prop + 0x66)) {
    *(int16_t *)(prop + 0x66) = unit_effect;
    *(int16_t *)(prop + 0x68) =
      (unit_effect == 3) ? (int16_t)0x96 : (int16_t)0x1e;
  }

  switch (unit_effect) {
  case 1:
    if (local_1 != 0)
      return;
    if (*(char *)(prop + 0x133) != 0)
      return;
    *(char *)(prop + 0x12f) = 1;
    *(int16_t *)(prop + 0x34) = 3;
    *(int16_t *)(prop + 0x30) = 3;
    *(char *)(prop + 0x64) = 1;
    if (*(char *)(prop + 0x12e) != 0) {
      actor_set_dormant(actor_handle, 0);
    }
    FUN_00036c50(actor_handle, prop_handle);
    return;
  case 2:
    if (local_1 != 0)
      return;
    if (*(char *)(prop + 0x133) != 0)
      return;
    *(char *)(prop + 0x127) = 1;
    *(int16_t *)(prop + 0x34) = 3;
    *(int16_t *)(prop + 0x30) = 3;
    *(char *)(prop + 0x64) = 1;
    if (*(char *)(prop + 0x12e) != 0) {
      actor_set_dormant(actor_handle, 0);
    }
    FUN_00037630(actor_handle, prop_handle);
    return;
  case 0:
    if (*(char *)(prop + 0x133) != 0)
      return;
    *(int16_t *)(prop + 0x36) = 3;
    *(int16_t *)(prop + 0x30) = 3;
    *(char *)(prop + 0x64) = 1;
    FUN_00036bd0(actor_handle, prop_handle);
    return;
  case 3:
    if (*(char *)(prop + 0x133) != 0)
      return;
    *(int16_t *)(prop + 0x36) = 3;
    *(int16_t *)(prop + 0x30) = 3;
    *(char *)(prop + 0x64) = 1;
    if (*(char *)(prop + 0x12e) != 0) {
      actor_set_dormant(actor_handle, 0);
    }
    actor_perception_become_acknowledged(actor_handle, prop_handle, 0);
    return;
  default:
    return;
  }
}

/* actor_set_active (0x3d5f0) — actor_set_activation_state
 *
 * Transition an actor between active (1) and inactive (0) states.
 * Always calls actor_verify_activation on entry. Returns early (1) if the
 * actor is already in the requested state. On deactivation: calls
 * actor_delete_props, actor_swarm_cache_delete, actor_set_dormant(1), clears
 * actor+0x8, and stamps actor+0xc with the current game time. On activation:
 * if actor is a swarm (actor+0x6 != 0), calls actor_swarm_cache_new to allocate
 * swarm components; if actor+0x28 == -1 after that (allocation failed), logs an
 * error, sets the erase flag at actor+0xb, calls actor_verify_activation, and
 * returns 0. If activation succeeds, sets actor+0x8 = 1; if actor+0x6a == 0,
 * calls actor_set_dormant(0) and actor_verify_activation, then returns 1. Falls
 * through to actor_verify_activation and returns 1 on all other success paths.
 *
 * Confirmed: datum_get(actor_data, actor_handle) at 0x3d600.
 * Confirmed: actor_verify_activation(actor_handle) at entry (0x3d60a).
 * Confirmed: actor+0x8 compared to param_2 at 0x3d612-0x3d61a.
 * Confirmed: actor_delete_props(actor_handle) at 0x3d662 (deactivate path).
 * Confirmed: actor_swarm_cache_delete(actor_handle) at 0x3d668.
 * Confirmed: actor_set_dormant(actor_handle, 1) at 0x3d673.
 * Confirmed: actor+0x8 = 0 at 0x3d67b; game_time_get() stored at actor+0xc at
 * 0x3d67f-0x3d684. Confirmed: actor+0x6 (swarm byte) tested at 0x3d620.
 * Confirmed: actor_swarm_cache_new(actor_handle) (swarm component allocator) at
 * 0x3d628. Confirmed: actor+0x28 == -1 check at 0x3d633 (swarm failed).
 * Confirmed: error(2, "swarm tried to become active but couldn't, erasing %d
 * units", ...) at 0x3d644. Confirmed: actor+0xb = 1 (erase flag) at 0x3d64c;
 * actor_verify_activation; return 0 at 0x3d650-0x3d660. Confirmed: actor+0x8 =
 * 1 at 0x3d69c (activate). Confirmed: actor+0x6a (short) == 0 check at 0x3d697;
 * if true: actor_set_dormant(0) at 0x3d6a5, actor_verify_activation at 0x3d6ae,
 * return 1 at 0x3d6b8. Confirmed: actor_verify_activation at 0x3d688 for
 * remaining paths; return 1. BL = 1 throughout (set at 0x3d608); XOR BL,BL only
 * on swarm-fail path.
 */
char actor_set_active(int actor_handle, char active)
{
  char *actor;
  char result;

  actor = (char *)datum_get(actor_data, actor_handle);
  result = 1;
  actor_verify_activation(actor_handle);

  if (*(char *)(actor + 0x8) != active) {
    if (active) {
      if (*(char *)(actor + 0x6) != '\0') {
        actor_swarm_cache_new(actor_handle);
        if (*(int *)(actor + 0x28) == -1) {
          error(2,
                "swarm tried to become active but couldn't, erasing %d units",
                (int)*(short *)(actor + 0x1e));
          *(char *)(actor + 0xb) = 1;
          result = 0;
          actor_verify_activation(actor_handle);
          return result;
        }
      }
      *(char *)(actor + 0x8) = 1;
      if (*(short *)(actor + 0x6a) == 0) {
        actor_set_dormant(actor_handle, 0);
        actor_verify_activation(actor_handle);
        return result;
      }
    } else {
      actor_delete_props(actor_handle);
      actor_swarm_cache_delete(actor_handle);
      actor_set_dormant(actor_handle, 1);
      *(char *)(actor + 0x8) = 0;
      *(int *)(actor + 0xc) = game_time_get();
    }
  }
  actor_verify_activation(actor_handle);
  return result;
}

/* actor_swarm_attach_unit (0x3d6c0) — actor_link_swarm_unit
 *
 * Link a unit into an actor's swarm unit list. If the unit is already linked
 * to this actor as its swarm actor, returns true immediately (no-op).
 * Otherwise, detaches any existing swarm/actor linkage on the unit, validates
 * preconditions, inserts the unit at the head of the actor's swarm-unit linked
 * list, allocates a swarm component if the actor belongs to an encounter swarm,
 * updates encounter bookkeeping, assigns team affiliation, and activates the
 * unit object.
 *
 * Confirmed: datum_get(actor_data, actor_handle) at 0x3d6d4.
 * Confirmed: object_get_and_verify_type(unit_index, 3) at 0x3d6e1.
 * Confirmed: early-out if unit->swarm_actor_index == actor_handle at
 * 0x3d6f1-0x3d6fe. Confirmed: data_new_at_index(swarm_component_data) if
 * actor->swarm_index != -1 at 0x3d719. Confirmed: error(2, "unable to create
 * any more swarm components...", 0x100) at 0x3d73d. Confirmed:
 * actor_swarm_detach_from_unit(unit->swarm_actor_index, unit_index) to detach
 * old swarm at 0x3d75c. Confirmed: actor_delete(unit->actor_index, 0) to detach
 * old actor at 0x3d772. Confirmed: actor_detach_from_unit(actor_handle) to
 * detach actor's existing unit at 0x3d784. Confirmed: assert checks
 * (actor->meta.swarm byte at +6, unit counts) at 0x3d78c-0x3d84f. Confirmed:
 * unit->swarm_actor_index = actor_handle at 0x3d855. Confirmed:
 * unit->swarm_next_unit = actor->first_unit at 0x3d85e (unit+0x1ac =
 * actor+0x24). Confirmed: unit->swarm_prev_unit = -1 at 0x3d864 (unit+0x1b0).
 * Confirmed: first_unit->swarm_prev_unit = unit_index if first_unit != -1 at
 * 0x3d879-0x3d8b1. Confirmed: actor->first_unit = unit_index at 0x3d8bf
 * (ESI+0x24 = EBX). Confirmed: FUN_0003cb50(actor->swarm_index@eax, new_sc@edi,
 * unit_index@ebx) at 0x3d8c7. Confirmed: actor->swarm_unit_count (short at
 * +0x1e) incremented at 0x3d8d2. Confirmed: short at actor+0x20 incremented at
 * 0x3d8d9. Confirmed: encounter encounter_attach_unit(actor->encounter_index,
 * unit_index) at 0x3d8f9. Confirmed: unit->team (word at unit+0x68) set from
 * encounter biped data+2 at 0x3d8fe/0x3d908. Confirmed: actor->team (word at
 * actor+0x3e) = unit->team at 0x3d913. Confirmed:
 * object_set_automatic_deactivation(unit_index, 0) at 0x3d917. Confirmed:
 * object_activate(unit_index) or object_deactivate(unit_index) at
 * 0x3d92e/0x3d927. Confirmed: unit_set_actively_controlled(unit_index, 1) at
 * 0x3d939.
 */
int actor_swarm_attach_unit(int actor_handle, int unit_index)
{
  char *actor;
  char *unit;
  int swarm_component_handle;
  char *first_unit;
  char *biped;
  char result;

  actor = (char *)datum_get(actor_data, actor_handle);
  unit = (char *)object_get_and_verify_type(unit_index, 3);

  /* Early-out: unit is already linked to this actor as swarm actor. */
  if (*(int *)(unit + 0x1a8) == actor_handle) {
    return 1;
  }

  swarm_component_handle = -1;

  /* Allocate swarm component if actor belongs to an encounter swarm. */
  if (*(int *)(actor + 0x28) != -1) {
    swarm_component_handle = data_new_at_index(*(data_t **)0x63259c);
    result = (swarm_component_handle != -1);
    if (!result) {
      error(2, "unable to create any more swarm components (max %d)", 0x100);
      return result;
    }
  }

  /* Detach unit from its old swarm actor if it had one. */
  if (*(int *)(unit + 0x1a8) != -1) {
    actor_swarm_detach_from_unit(*(int *)(unit + 0x1a8), unit_index);
  }

  /* Detach unit from its old actor if it had one. */
  if (*(int *)(unit + 0x1a4) != -1) {
    actor_delete(*(int *)(unit + 0x1a4), 0);
  }

  /* Detach actor's current unit if it had one. */
  if (*(int *)(actor + 0x18) != -1) {
    actor_detach_from_unit(actor_handle);
  }

  /* Precondition assertions (source line 0x513-0x519). */
  if (*(char *)(actor + 6) == 0) {
    display_assert("actor->meta.swarm", "c:\\halo\\SOURCE\\ai\\actors.c", 0x513,
                   1);
    system_exit(-1);
  }
  if (*(int *)(actor + 0x18) != -1) {
    display_assert("actor->meta.unit_index == NONE",
                   "c:\\halo\\SOURCE\\ai\\actors.c", 0x514, 1);
    system_exit(-1);
  }
  if (*(int *)(unit + 0x1a4) != -1) {
    display_assert("unit->unit.actor_index == NONE",
                   "c:\\halo\\SOURCE\\ai\\actors.c", 0x515, 1);
    system_exit(-1);
  }
  if (*(int *)(unit + 0x1a8) != -1) {
    display_assert("unit->unit.swarm_actor_index == NONE",
                   "c:\\halo\\SOURCE\\ai\\actors.c", 0x516, 1);
    system_exit(-1);
  }
  if (*(short *)(actor + 0x1e) >= 0x10) {
    display_assert(
      "actor->meta.swarm_unit_count < MAXIMUM_NUMBER_OF_UNITS_PER_SWARM",
      "c:\\halo\\SOURCE\\ai\\actors.c", 0x519, 1);
    system_exit(-1);
  }

  /* Link unit into actor's swarm list at the head. */
  *(int *)(unit + 0x1a8) = actor_handle;
  *(int *)(unit + 0x1ac) =
    *(int *)(actor + 0x24); /* unit->swarm_next = old first */
  *(int *)(unit + 0x1b0) = -1; /* unit->swarm_prev = NONE */

  /* If there was a previous first unit, point its prev back to this unit. */
  if (*(int *)(actor + 0x24) != -1) {
    first_unit = (char *)object_get_and_verify_type(*(int *)(actor + 0x24), 3);
    if (*(int *)(first_unit + 0x1b0) != -1) {
      display_assert("swarm_first_unit->unit.swarm_prev_unit_index == NONE",
                     "c:\\halo\\SOURCE\\ai\\actors.c", 0x524, 1);
      system_exit(-1);
    }
    *(int *)(first_unit + 0x1b0) = unit_index;
  }

  /* Update actor's first unit pointer. */
  *(int *)(actor + 0x24) = unit_index;

  /* Register swarm component if allocated. */
  if (*(int *)(actor + 0x28) != -1) {
    FUN_0003cb50(*(int *)(actor + 0x28), swarm_component_handle, unit_index);
  }

  /* Increment swarm unit counts. */
  *(short *)(actor + 0x1e) += 1;
  *(short *)(actor + 0x20) += 1;

  /* Sync encounter data and set team affiliation. */
  if (*(int *)(actor + 0x34) != -1) {
    biped = (char *)datum_get(*(data_t **)0x5ab270, *(int *)(actor + 0x34));
    encounter_attach_unit(*(int *)(actor + 0x34), unit_index);
    *(short *)(unit + 0x68) = *(short *)(biped + 2);
  }
  *(short *)(actor + 0x3e) = *(short *)(unit + 0x68);

  object_set_automatic_deactivation(unit_index, 0);

  /* Activate unit: if actor is in "active" mode, use deferred activation. */
  if (*(char *)(actor + 0x13) != 0) {
    object_deactivate(unit_index);
  } else {
    object_activate(unit_index);
  }

  unit_set_actively_controlled(unit_index, 1);

  return 1;
}

/* actor_erase (0x3d950) — actor_erase_units
 *
 * Erase all units owned by an actor. For swarm actors (byte at actor+6 != 0),
 * iterates the linked-list of unit handles starting at actor+0x24, detaching
 * each unit via actor_swarm_detach_from_unit and deleting it. For non-swarm
 * actors, handles the single unit at actor+0x18 via actor_died. The flag
 * parameter controls whether units are deleted with object_delete (flag=0) or
 * objects_garbage_collection (flag!=0, a softer detach-and-delete path).
 *
 * Classification evidence: callee actor_swarm_detach_from_unit references
 * actors.c asserts at 0x3aeab/0x3af05/0x3af32/0x3af6d. Callee actor_delete
 * references actors.c assert at 0x3cc40. Callee actor_died calls
 * actor_delete. Caller FUN_0003d9f0 references actors.c string at 0x3da76. All
 * confirm actors.c TU.
 *
 * Confirmed: cdecl, two stack args (actor_handle, flag).
 * Confirmed: datum_get(actor_data, actor_handle) at 0x3d95f.
 * Confirmed: swarm check at actor+6 (0x3d966), branch at 0x3d96e.
 * Confirmed: loop reads actor+0x24 each iteration (0x3d971, 0x3d99e).
 * Confirmed: actor_swarm_detach_from_unit(actor_handle, unit_handle) at
 * 0x3d982. Confirmed: flag test at 0x3d98d selects object_delete vs
 * objects_garbage_collection. Confirmed: actor_delete(actor_handle, 1) at
 * 0x3d9ac. Confirmed: non-swarm path loads actor+0x18 into EDI at 0x3d9b9.
 * Confirmed: actor_died(actor_handle) at 0x3d9bd. */
void actor_erase(int actor_handle, char flag)
{
  char *actor;
  int unit_handle;

  actor = (char *)datum_get(actor_data, actor_handle);

  if (*(char *)(actor + 0x6) != 0) {
    /* Swarm actor: detach and delete all units in linked list */
    unit_handle = *(int *)(actor + 0x24);
    while (unit_handle != -1) {
      actor_swarm_detach_from_unit(actor_handle, unit_handle);
      if (flag != 0) {
        objects_garbage_collection(unit_handle);
      } else {
        object_delete(unit_handle);
      }
      unit_handle = *(int *)(actor + 0x24);
    }
    actor_delete(actor_handle, 1);
    return;
  }

  /* Non-swarm actor: handle single unit */
  unit_handle = *(int *)(actor + 0x18);
  actor_died(actor_handle);
  if (flag != 0) {
    objects_garbage_collection(unit_handle);
  } else {
    object_delete(unit_handle);
  }
}

char FUN_0003d9f0(int actor_handle)
{
  char *actor;
  char *biped;
  char *encounter;
  char flags;
  short action_type;
  char in_vehicle;
  char ret;

  actor = (char *)datum_get(actor_data, actor_handle);

  ret = 1;

  /* Per-tick counter updates */
  (*(short *)0x5abc44)++;
  if (*(char *)(actor + 0x13) == 0) {
    (*(short *)0x5abccc)++;
  }
  if (*(char *)(actor + 0x6) == 0) {
    (*(short *)0x5abddc)++;
    if (*(char *)(actor + 0x13) == 0) {
      (*(short *)0x5abe64)++;
    }
  } else {
    *(short *)0x5abddc += *(short *)(actor + 0x1e);
    if (*(char *)(actor + 0x13) == 0) {
      *(short *)0x5abe64 += *(short *)(actor + 0x1e);
    }
  }

  /* Swarm actor without a swarm cache: error, erase and bail.
   * NOTE: The binary shares filepath/lineno/halt args across csprintf and
   * display_assert via a partial-cleanup trick (ADD ESP,0xc after csprintf
   * leaves 3 args on stack; PUSH EAX adds reason; CALL display_assert sees 4).
   * In C we write both calls explicitly; the compiler may or may not fold them.
   */
  if (*(char *)(actor + 0x6) != 0 && *(int *)(actor + 0x28) == -1) {
    csprintf(
      (char *)0x5ab100,
      "tried to update a swarm actor without a swarm cache, erasing %d units",
      (int)*(short *)(actor + 0x1e));
    display_assert((char *)0x5ab100, "c:\\halo\\SOURCE\\ai\\actors.c", 0xaad,
                   0);
    actor_erase(actor_handle, 0);
    ret = 0;
    return ret;
  }

  /* Reset per-tick counters on actor */
  *(char *)(actor + 0x4a4) = 0;
  if (*(int *)(actor + 0x78) > 0) {
    *(int *)(actor + 0x78) -= 1;
    if (*(int *)(actor + 0x78) == 0) {
      *(short *)(actor + 0x74) = 0;
    }
  }
  if (*(short *)(actor + 0x92) > 0) {
    *(short *)(actor + 0x92) -= 1;
  }

  /* Resolve biped record if actor has a biped handle */
  biped = 0;
  if (*(int *)(actor + 0x34) != -1) {
    biped = (char *)datum_get(*(data_t **)0x5ab270, *(int *)(actor + 0x34));
  }

  /* Combined flags: actor own flags OR biped flags */
  flags = *(char *)(actor + 0xa);
  if (biped != 0) {
    flags |= *(char *)(biped + 0xc);
  }

  /* Deactivate if no player present or combined flags set */
  if (*(char *)(actor + 0x12) == 0 || flags != 0) {
    actor_set_dormant(actor_handle, 0);
    return ret;
  }

  /* Dormant actors pass immediately */
  if (*(char *)(actor + 0x13) != 0) {
    return ret;
  }

  /* Check current action type */
  action_type = (short)actor_action_try_to_panic(actor_handle);
  if (action_type == 2) {
    return ret;
  }

  /* Encounter validity check */
  if (*(int *)(actor + 0x270) != -1) {
    encounter =
      (char *)datum_get(*(data_t **)0x5ab23c, *(int *)(actor + 0x270));
    if (*(char *)(encounter + 0x12e) != 0 && *(char *)(encounter + 0x60) != 0 &&
        *(char *)(encounter + 0x127) == 0) {
      short enc_state = *(short *)(encounter + 0x24);
      if (enc_state >= 2 && enc_state <= 3) {
        return ret;
      }
      if (enc_state >= 4 && enc_state <= 5 && action_type == 3) {
        return ret;
      }
    }
  }

  /* Check in-vehicle / mounted flag */
  in_vehicle = FUN_0002a3d0(actor_handle);
  if (in_vehicle != 0) {
    if (*(short *)(actor + 0x46c) == 3) {
      /* Biped-ride mode: check biped action state */
      if (*(short *)(actor + 0x6c) == 6 && *(short *)(biped + 0x62) == 1) {
        return ret;
      }
    } else if (*(short *)(actor + 0x46c) == 5) {
      /* Encounter-board mode: check encounter scripted flag */
      encounter =
        (char *)datum_get(*(data_t **)0x5ab23c, *(int *)(actor + 0x470));
      if (*(char *)(encounter + 0x12e) != 0) {
        return ret;
      }
    }
  }

  /* Idle tick counter: if exceeded threshold, force deactivation */
  *(short *)(actor + 0x14) += 1;
  if (*(short *)(actor + 0x14) > 0x3b) {
    actor_set_dormant(actor_handle, 1);
    return ret;
  }

  return ret;
}

/* FUN_0003dc20 (0x3dc20) — XBE naked draft (batch 69). */
#if defined(__clang__)
static void *(*const b3dc20_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void *(*const b3dc20_tag)(int, int) = tag_get;
static void *(*const b3dc20_get)(int, int) = object_get_and_verify_type;
static vector3_t * (*const b3dc20_c1412f0)(int object_handle, vector3_t *out_position) = object_get_world_position;
static void *(*const b3dc20_memset)(void *, int, unsigned int) = csmemset;
static void (*const b3dc20_c3bde0)(int actor_handle, int unit_handle, char *input_block) = FUN_0003bde0;
static void (*const b3dc20_c1a9520)(int object_handle, float *out_position) = FUN_001a9520;
static bool (*const b3dc20_c18f3e0)(void *location, void *position, int16_t *out_sky_index) = FUN_0018f3e0;
static char * (*const b3dc20_c211f0)(int actor_handle) = actor_combat_get_firing_variant_definition;
static char * (*const b3dc20_c1c270)(char *encounter, int16_t squad_index) = encounter_get_squad;
static void (*const b3dc20_c3baa0)(int actor_handle, int encounter_handle, int16_t squad_index) = FUN_0003baa0;
static scenario_t * (*const b3dc20_c18e380)(void) = global_scenario_get;
static void *(*const b3dc20_elem)(void *, int, int) = tag_block_get_element;
static const char * (*const b3dc20_c1ba1f0)(int tag_index) = tag_get_name;
static void (*const b3dc20_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;
static bool (*const b3dc20_ca7a30)(int16_t team_a, int16_t team_b) = game_allegiance_get_team_is_friendly;
static void (*const b3dc20_c1a9960)(int unit_handle, void *out_facing) = units_debug_get_closest_unit;
static float (*const b3dc20_mag)(float *) = magnitude3d;
static float (*const b3dc20_norm)(float *) = normalize3d;
static bool (*const b3dc20_c21fb0)(float *v) = valid_real_normal3d;
static char * (*const b3dc20_c8d9d0)(char *buffer, const char *format, ...) = csprintf;
static void (*const b3dc20_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b3dc20_exitfn)(int) = system_exit;
static int (*const b3dc20_c28610)(float *v) = valid_real_normal2d;

__attribute__((naked, noinline))
void FUN_0003dc20(int actor_handle __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x24, %%esp\n\t"
      "movl 0x6325a4, %%eax\n\t"
      "pushl %%ebx\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x58(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x61637472\n\t"
      "call *%[tag]\n\t"
      "movl %%eax, -0x18(%%ebp)\n\t"
      "movb 0x6(%%esi), %%al\n\t"
      "addl $0x10, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0003dc20_5\n\t"
      "movl 0x28(%%esi), %%edx\n\t"
      "movl 0x6325a0, %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl 0x31fc1c, %%ecx\n\t"
      "movl (%%ecx), %%edx\n\t"
      "movl %%eax, %%edi\n\t"
      "leal 0xc(%%edi), %%eax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "movl %%edx, (%%eax)\n\t"
      "movl 0x4(%%ecx), %%edx\n\t"
      "movl %%edx, 0x4(%%eax)\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $0, 0x2(%%edi)\n\t"
      "movl %%ecx, 0x8(%%eax)\n\t"
      "movl $0, -0x4(%%ebp)\n\t"
      "jle .LFUN_0003dc20_3\n\t"
      "jmp .LFUN_0003dc20_1\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".LFUN_0003dc20_1:\n\t"
      "movswl -0x4(%%ebp), %%ebx\n\t"
      "movl 0x58(%%edi,%%ebx,4), %%edx\n\t"
      "movl 0x63259c, %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl 0x58(%%edi,%%ebx,4), %%ecx\n\t"
      "movl 0x18(%%edi,%%ebx,4), %%ebx\n\t"
      "pushl $3\n\t"
      "pushl %%ebx\n\t"
      "movl %%eax, -0x18(%%ebp)\n\t"
      "movl %%ecx, -0xc(%%ebp)\n\t"
      "call *%[get]\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "movl 0x63259c, %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl -0x10(%%ebp), %%ecx\n\t"
      "addl $0x18, %%esp\n\t"
      "cmpw $0, 0x64(%%ecx)\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "movl $0xffffffff, -0xc(%%ebp)\n\t"
      "jne .LFUN_0003dc20_2\n\t"
      "movl 0x430(%%ecx), %%ecx\n\t"
      "movl %%ecx, -0xc(%%ebp)\n\t"
      ".LFUN_0003dc20_2:\n\t"
      "addl $4, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "call *%[c1412f0]\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "movl -0x18(%%ebp), %%ecx\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "movl %%edx, 0x10(%%eax)\n\t"
      "flds 0x4(%%ecx)\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "fadds (%%eax)\n\t"
      "addl $8, %%esp\n\t"
      "fstps (%%eax)\n\t"
      "flds 0x8(%%ecx)\n\t"
      "fadds 0x4(%%eax)\n\t"
      "fstps 0x4(%%eax)\n\t"
      "flds 0xc(%%ecx)\n\t"
      "fadds 0x8(%%eax)\n\t"
      "fstps 0x8(%%eax)\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "incl %%eax\n\t"
      "cmpw 0x2(%%edi), %%ax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "jl .LFUN_0003dc20_1\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      ".LFUN_0003dc20_3:\n\t"
      "movw 0x2(%%edi), %%di\n\t"
      "testw %%di, %%di\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "jle .LFUN_0003dc20_4\n\t"
      "movswl %%di, %%ecx\n\t"
      "movl %%ecx, -0x18(%%ebp)\n\t"
      "fildl -0x18(%%ebp)\n\t"
      "fdivrs 0x2533c8\n\t"
      "fld %%st(0)\n\t"
      "fmuls (%%eax)\n\t"
      "fstps (%%eax)\n\t"
      "fld %%st(0)\n\t"
      "fmuls 0x4(%%eax)\n\t"
      "fstps 0x4(%%eax)\n\t"
      "fmuls 0x8(%%eax)\n\t"
      "fstps 0x8(%%eax)\n\t"
      ".LFUN_0003dc20_4:\n\t"
      "pushl $0xa8\n\t"
      "leal 0x120(%%esi), %%edi\n\t"
      "pushl $0\n\t"
      "pushl %%edi\n\t"
      "call *%[memset]\n\t"
      "orl $0xffffffff, %%eax\n\t"
      "movl %%eax, 0x158(%%esi)\n\t"
      "movl %%eax, 0x164(%%esi)\n\t"
      "movl 0x24(%%esi), %%esi\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl %%eax, %%esi\n\t"
      "je .LFUN_0003dc20_42\n\t"
      "pushl %%edi\n\t"
      "pushl %%esi\n\t"
      "pushl %%ebx\n\t"
      "call *%[c3bde0]\n\t"
      "addl $0xc, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0003dc20_5:\n\t"
      "movl 0x18(%%esi), %%edx\n\t"
      "pushl $3\n\t"
      "pushl %%edx\n\t"
      "call *%[get]\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "movl 0xcc(%%eax), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "jne .LFUN_0003dc20_6\n\t"
      "xorl %%edi, %%edi\n\t"
      "jmp .LFUN_0003dc20_7\n\t"
      ".LFUN_0003dc20_6:\n\t"
      "pushl $-1\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "addl $8, %%esp\n\t"
      "movl %%eax, %%edi\n\t"
      ".LFUN_0003dc20_7:\n\t"
      "movl 0x18(%%esi), %%ecx\n\t"
      "leal 0x120(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "call *%[c3bde0]\n\t"
      "movl 0x18(%%esi), %%eax\n\t"
      "leal -0x24(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c1a9520]\n\t"
      "pushl $0\n\t"
      "leal -0x24(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal 0x144(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c18f3e0]\n\t"
      "movb %%al, 0x15d(%%esi)\n\t"
      "movl -0x18(%%ebp), %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "shrl $0x15, %%ecx\n\t"
      "andb $1, %%cl\n\t"
      "addl $0x20, %%esp\n\t"
      "testl %%edi, %%edi\n\t"
      "movb %%cl, 0x99(%%esi)\n\t"
      "je .LFUN_0003dc20_15\n\t"
      "cmpw $1, 0x64(%%edi)\n\t"
      "jne .LFUN_0003dc20_15\n\t"
      "movl (%%edi), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x76656869\n\t"
      "call *%[tag]\n\t"
      "movl -0x14(%%ebp), %%ecx\n\t"
      "movl %%ecx, 0x158(%%esi)\n\t"
      "movl 0x18(%%esi), %%ecx\n\t"
      "movb $0, 0x161(%%esi)\n\t"
      "movb $0, 0x162(%%esi)\n\t"
      "movw $0, 0x15e(%%esi)\n\t"
      "movl 0x2d4(%%edi), %%edx\n\t"
      "addl $8, %%esp\n\t"
      "cmpl %%ecx, %%edx\n\t"
      "jne .LFUN_0003dc20_9\n\t"
      "movw $1, 0x15e(%%esi)\n\t"
      "movl 0x2f0(%%eax), %%eax\n\t"
      "testb $8, %%ah\n\t"
      "je .LFUN_0003dc20_9\n\t"
      "testb $0x10, %%ah\n\t"
      "je .LFUN_0003dc20_8\n\t"
      "movw $4, 0x15e(%%esi)\n\t"
      "movb $1, 0x99(%%esi)\n\t"
      "jmp .LFUN_0003dc20_9\n\t"
      ".LFUN_0003dc20_8:\n\t"
      "testb $0x20, %%ah\n\t"
      "je .LFUN_0003dc20_9\n\t"
      "shrl $0xe, %%eax\n\t"
      "notb %%al\n\t"
      "andl $1, %%eax\n\t"
      "orl $2, %%eax\n\t"
      "movw %%ax, 0x15e(%%esi)\n\t"
      ".LFUN_0003dc20_9:\n\t"
      "cmpl %%ecx, 0x2d8(%%edi)\n\t"
      "jne .LFUN_0003dc20_12\n\t"
      "pushl %%ebx\n\t"
      "movb $1, 0x161(%%esi)\n\t"
      "call *%[c211f0]\n\t"
      "flds 0x14c(%%eax)\n\t"
      "fcomps 0x2533c0\n\t"
      "addl $4, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_0003dc20_10\n\t"
      "movl $1, %%eax\n\t"
      "jmp .LFUN_0003dc20_11\n\t"
      ".LFUN_0003dc20_10:\n\t"
      "xorl %%eax, %%eax\n\t"
      ".LFUN_0003dc20_11:\n\t"
      "movb %%al, 0x162(%%esi)\n\t"
      ".LFUN_0003dc20_12:\n\t"
      "cmpw $1, 0x15e(%%esi)\n\t"
      "setle %%dl\n\t"
      "movb %%dl, 0x160(%%esi)\n\t"
      "movw 0x2e4(%%edi), %%ax\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .LFUN_0003dc20_17\n\t"
      "movl 0x34(%%esi), %%ecx\n\t"
      "movl %%ecx, %%edx\n\t"
      "movswl %%ax, %%eax\n\t"
      "andl $0xffff, %%edx\n\t"
      "cmpl %%eax, %%edx\n\t"
      "jne .LFUN_0003dc20_13\n\t"
      "movw 0x2e6(%%edi), %%ax\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .LFUN_0003dc20_17\n\t"
      "cmpw %%ax, 0x3a(%%esi)\n\t"
      "je .LFUN_0003dc20_17\n\t"
      "pushl %%ecx\n\t"
      "movl 0x5ab270, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $0, 0x62(%%eax)\n\t"
      "movl %%eax, -0x18(%%ebp)\n\t"
      "jle .LFUN_0003dc20_13\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x3a(%%esi), %%dx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c1c270]\n\t"
      "movl -0x18(%%ebp), %%ecx\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x2e6(%%edi), %%ax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1c270]\n\t"
      "movl -0x14(%%ebp), %%edx\n\t"
      "movb 0x10(%%edx), %%cl\n\t"
      "addl $0x10, %%esp\n\t"
      "testb %%cl, %%cl\n\t"
      "je .LFUN_0003dc20_13\n\t"
      "movb 0x10(%%eax), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "jne .LFUN_0003dc20_17\n\t"
      ".LFUN_0003dc20_13:\n\t"
      "movb 0x40(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_0003dc20_14\n\t"
      "movl 0x34(%%esi), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "movw 0x3a(%%esi), %%cx\n\t"
      "movl %%eax, 0x44(%%esi)\n\t"
      "movw %%cx, 0x48(%%esi)\n\t"
      "movb $1, 0x40(%%esi)\n\t"
      "je .LFUN_0003dc20_14\n\t"
      "movl 0x5ab270, %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%edx\n\t"
      "call *%[dget]\n\t"
      "addl $8, %%esp\n\t"
      "movb $1, 0x1e(%%eax)\n\t"
      ".LFUN_0003dc20_14:\n\t"
      "movswl 0x2e4(%%edi), %%ecx\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x2e6(%%edi), %%ax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "call *%[c3baa0]\n\t"
      "jmp .LFUN_0003dc20_16\n\t"
      ".LFUN_0003dc20_15:\n\t"
      "movb 0x40(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "movl $0xffffffff, 0x158(%%esi)\n\t"
      "movw $0, 0x15e(%%esi)\n\t"
      "movb $0, 0x160(%%esi)\n\t"
      "movb $0, 0x161(%%esi)\n\t"
      "je .LFUN_0003dc20_17\n\t"
      "movl 0x44(%%esi), %%eax\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x48(%%esi), %%dx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "call *%[c3baa0]\n\t"
      "movb $0, 0x40(%%esi)\n\t"
      ".LFUN_0003dc20_16:\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_0003dc20_17:\n\t"
      "movl 0x34(%%esi), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_0003dc20_22\n\t"
      "movl 0x331f58, %%ecx\n\t"
      "andl $0xffff, %%ebx\n\t"
      "imull $0x657c, %%ebx, %%ebx\n\t"
      "andl $0xffff, %%eax\n\t"
      "pushl $0xb0\n\t"
      "pushl %%eax\n\t"
      "addl %%ecx, %%ebx\n\t"
      "call *%[c18e380]\n\t"
      "addl $0x42c, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movb 0x99(%%esi), %%cl\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%cl, %%cl\n\t"
      "movb $0x20, %%dl\n\t"
      "je .LFUN_0003dc20_18\n\t"
      "testb %%dl, 0x20(%%eax)\n\t"
      "je .LFUN_0003dc20_19\n\t"
      "testb %%cl, %%cl\n\t"
      "jne .LFUN_0003dc20_21\n\t"
      ".LFUN_0003dc20_18:\n\t"
      "testb %%dl, 0x20(%%eax)\n\t"
      "je .LFUN_0003dc20_21\n\t"
      ".LFUN_0003dc20_19:\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x657a(%%ebx), %%cx\n\t"
      "cmpw $0x96, %%cx\n\t"
      "jge .LFUN_0003dc20_22\n\t"
      "incl %%ecx\n\t"
      "cmpw $0x96, %%cx\n\t"
      "movw %%cx, 0x657a(%%ebx)\n\t"
      "jne .LFUN_0003dc20_22\n\t"
      "movb 0x99(%%esi), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "pushl %%eax\n\t"
      "je .LFUN_0003dc20_20\n\t"
      "movl 0x58(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1ba1f0]\n\t"
      "addl $4, %%esp\n\t"
      "pushl %%eax\n\t"
      "pushl $0x257300\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $0x10, %%esp\n\t"
      "jmp .LFUN_0003dc20_22\n\t"
      ".LFUN_0003dc20_20:\n\t"
      "movl 0x58(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c1ba1f0]\n\t"
      "addl $4, %%esp\n\t"
      "pushl %%eax\n\t"
      "pushl $0x2572b0\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $0x10, %%esp\n\t"
      "jmp .LFUN_0003dc20_22\n\t"
      ".LFUN_0003dc20_21:\n\t"
      "movw $0, 0x657a(%%ebx)\n\t"
      ".LFUN_0003dc20_22:\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movb 0x23b(%%eax), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "seta %%cl\n\t"
      "movb %%cl, 0x1b5(%%esi)\n\t"
      "movb $0, 0x1b4(%%esi)\n\t"
      "movl $0xffffffff, 0x1b0(%%esi)\n\t"
      "movl 0xc8(%%eax), %%edi\n\t"
      "cmpl $-1, %%edi\n\t"
      "je .LFUN_0003dc20_27\n\t"
      ".LFUN_0003dc20_23:\n\t"
      "pushl $-1\n\t"
      "pushl %%edi\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%ebx\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $0, 0x64(%%ebx)\n\t"
      "jne .LFUN_0003dc20_24\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x68(%%ebx), %%dx\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x3e(%%esi), %%ax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[ca7a30]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0003dc20_24\n\t"
      "movb $1, 0x1b4(%%esi)\n\t"
      "jmp .LFUN_0003dc20_26\n\t"
      ".LFUN_0003dc20_24:\n\t"
      "cmpw $5, 0x64(%%ebx)\n\t"
      "jne .LFUN_0003dc20_26\n\t"
      "movb 0x1dc(%%ebx), %%al\n\t"
      "testb %%al, %%al\n\t"
      "js .LFUN_0003dc20_25\n\t"
      "cmpw $2, 0x280(%%esi)\n\t"
      "jne .LFUN_0003dc20_26\n\t"
      "cmpl 0x28c(%%esi), %%edi\n\t"
      "jne .LFUN_0003dc20_26\n\t"
      ".LFUN_0003dc20_25:\n\t"
      "movl %%edi, 0x1b0(%%esi)\n\t"
      ".LFUN_0003dc20_26:\n\t"
      "movl 0xc4(%%ebx), %%edi\n\t"
      "cmpl $-1, %%edi\n\t"
      "jne .LFUN_0003dc20_23\n\t"
      ".LFUN_0003dc20_27:\n\t"
      "movl -0x8(%%ebp), %%ebx\n\t"
      "orl $0xffffffff, %%eax\n\t"
      "movb $0, 0x15c(%%esi)\n\t"
      "movl %%eax, 0x164(%%esi)\n\t"
      "cmpw $0, 0x64(%%ebx)\n\t"
      "jne .LFUN_0003dc20_29\n\t"
      "cmpl %%eax, 0x158(%%esi)\n\t"
      "jne .LFUN_0003dc20_29\n\t"
      "movl 0x18(%%esi), %%ecx\n\t"
      "pushl $1\n\t"
      "pushl %%ecx\n\t"
      "call *%[get]\n\t"
      "movb 0x459(%%eax), %%cl\n\t"
      "addl $8, %%esp\n\t"
      "cmpb $6, %%cl\n\t"
      "jl .LFUN_0003dc20_28\n\t"
      "movb $1, 0x15c(%%esi)\n\t"
      ".LFUN_0003dc20_28:\n\t"
      "movl 0x434(%%eax), %%edx\n\t"
      "addl $0x438, %%eax\n\t"
      "movl %%edx, 0x164(%%esi)\n\t"
      "movl (%%eax), %%edx\n\t"
      "leal 0x168(%%esi), %%ecx\n\t"
      "movl %%edx, (%%ecx)\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl %%edx, 0x4(%%ecx)\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl %%eax, 0x8(%%ecx)\n\t"
      ".LFUN_0003dc20_29:\n\t"
      "cmpw $0, 0x15e(%%esi)\n\t"
      "leal 0x174(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "jle .LFUN_0003dc20_30\n\t"
      "movl 0x158(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "jmp .LFUN_0003dc20_31\n\t"
      ".LFUN_0003dc20_30:\n\t"
      "movl 0x18(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      ".LFUN_0003dc20_31:\n\t"
      "call *%[c1a9960]\n\t"
      "movb 0x99(%%esi), %%al\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_0003dc20_33\n\t"
      "leal 0x174(%%esi), %%edi\n\t"
      "pushl %%edi\n\t"
      "call *%[mag]\n\t"
      "fcomps 0x2533c0\n\t"
      "addl $4, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_0003dc20_32\n\t"
      "movl $0, 0x17c(%%esi)\n\t"
      "jmp .LFUN_0003dc20_33\n\t"
      ".LFUN_0003dc20_32:\n\t"
      "movl 0x31fc3c, %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "movl %%ecx, (%%edi)\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl %%edx, 0x4(%%edi)\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl %%eax, 0x8(%%edi)\n\t"
      ".LFUN_0003dc20_33:\n\t"
      "movb 0x161(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0003dc20_35\n\t"
      "movl 0x158(%%esi), %%ecx\n\t"
      "pushl $2\n\t"
      "pushl %%ecx\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%edi\n\t"
      "movl (%%edi), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x76656869\n\t"
      "call *%[tag]\n\t"
      "movl 0x2f0(%%eax), %%ecx\n\t"
      "addl $0x10, %%esp\n\t"
      "testb $1, %%ch\n\t"
      "leal 0x180(%%esi), %%eax\n\t"
      "je .LFUN_0003dc20_34\n\t"
      "pushl %%eax\n\t"
      "movl 0x18(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1a9960]\n\t"
      "addl $8, %%esp\n\t"
      "jmp .LFUN_0003dc20_36\n\t"
      ".LFUN_0003dc20_34:\n\t"
      "addl $0x1ec, %%edi\n\t"
      "movl (%%edi), %%ecx\n\t"
      "movl %%ecx, (%%eax)\n\t"
      "movl 0x4(%%edi), %%edx\n\t"
      "movl %%edx, 0x4(%%eax)\n\t"
      "movl 0x8(%%edi), %%ecx\n\t"
      "movl %%ecx, 0x8(%%eax)\n\t"
      "jmp .LFUN_0003dc20_36\n\t"
      ".LFUN_0003dc20_35:\n\t"
      "leal 0x1ec(%%ebx), %%edx\n\t"
      "movl (%%edx), %%ecx\n\t"
      "leal 0x180(%%esi), %%eax\n\t"
      "movl %%ecx, (%%eax)\n\t"
      "movl 0x4(%%edx), %%ecx\n\t"
      "movl %%ecx, 0x4(%%eax)\n\t"
      "movl 0x8(%%edx), %%edx\n\t"
      "movl %%edx, 0x8(%%eax)\n\t"
      ".LFUN_0003dc20_36:\n\t"
      "leal 0x18c(%%esi), %%edi\n\t"
      "addl $0x210, %%ebx\n\t"
      "movl (%%ebx), %%ecx\n\t"
      "movl %%edi, %%eax\n\t"
      "movl %%ecx, (%%eax)\n\t"
      "movl 0x4(%%ebx), %%edx\n\t"
      "movl %%edx, 0x4(%%eax)\n\t"
      "movl 0x8(%%ebx), %%ecx\n\t"
      "movl %%ecx, 0x8(%%eax)\n\t"
      "flds 0x4(%%edi)\n\t"
      "movl 0x31fc44, %%eax\n\t"
      "fmuls (%%eax)\n\t"
      "leal 0x198(%%esi), %%ebx\n\t"
      "flds 0x4(%%eax)\n\t"
      "pushl %%ebx\n\t"
      "fmuls (%%edi)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "flds 0x8(%%eax)\n\t"
      "fmuls (%%edi)\n\t"
      "flds 0x8(%%edi)\n\t"
      "fmuls (%%eax)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "flds 0x8(%%edi)\n\t"
      "fmuls 0x4(%%eax)\n\t"
      "flds 0x8(%%eax)\n\t"
      "fmuls 0x4(%%edi)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps (%%ebx)\n\t"
      "fstps 0x4(%%ebx)\n\t"
      "fstps 0x8(%%ebx)\n\t"
      "call *%[norm]\n\t"
      "fstp %%st(0)\n\t"
      "flds (%%edi)\n\t"
      "fmuls 0x4(%%ebx)\n\t"
      "flds 0x4(%%edi)\n\t"
      "fmuls (%%ebx)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "flds (%%ebx)\n\t"
      "fmuls 0x8(%%edi)\n\t"
      "flds (%%edi)\n\t"
      "fmuls 0x8(%%ebx)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "flds 0x4(%%edi)\n\t"
      "fmuls 0x8(%%ebx)\n\t"
      "flds 0x8(%%edi)\n\t"
      "fmuls 0x4(%%ebx)\n\t"
      "leal 0x174(%%esi), %%ebx\n\t"
      "pushl %%ebx\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps 0x1a4(%%esi)\n\t"
      "fstps 0x1a8(%%esi)\n\t"
      "fstps 0x1ac(%%esi)\n\t"
      "call *%[c21fb0]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_0003dc20_37\n\t"
      "flds 0x17c(%%esi)\n\t"
      "pushl $1\n\t"
      "pushl $0xcf1\n\t"
      "pushl $0x256ce8\n\t"
      "subl $0x18, %%esp\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds 0x178(%%esi)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds (%%ebx)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x255efc\n\t"
      "pushl $0x254a24\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x24, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0003dc20_37:\n\t"
      "leal 0x180(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c21fb0]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_0003dc20_38\n\t"
      "flds 0x188(%%esi)\n\t"
      "pushl $1\n\t"
      "pushl $0xcf2\n\t"
      "pushl $0x256ce8\n\t"
      "subl $0x18, %%esp\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds 0x184(%%esi)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds 0x180(%%esi)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x257294\n\t"
      "pushl $0x254a24\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x24, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0003dc20_38:\n\t"
      "pushl %%edi\n\t"
      "call *%[c21fb0]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_0003dc20_39\n\t"
      "flds 0x194(%%esi)\n\t"
      "pushl $1\n\t"
      "pushl $0xcf3\n\t"
      "pushl $0x256ce8\n\t"
      "subl $0x18, %%esp\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds 0x190(%%esi)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds (%%edi)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x257274\n\t"
      "pushl $0x254a24\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x24, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0003dc20_39:\n\t"
      "movb 0x99(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_0003dc20_41\n\t"
      "pushl %%ebx\n\t"
      "call *%[c28610]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_0003dc20_40\n\t"
      "flds 0x178(%%esi)\n\t"
      "pushl $1\n\t"
      "pushl $0xcf6\n\t"
      "pushl $0x256ce8\n\t"
      "subl $0x10, %%esp\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds (%%ebx)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x257244\n\t"
      "pushl $0x2555d4\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x1c, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0003dc20_40:\n\t"
      "flds 0x17c(%%esi)\n\t"
      "fabs\n\t"
      "fcompl 0x2533d0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .LFUN_0003dc20_41\n\t"
      "pushl $1\n\t"
      "pushl $0xcf7\n\t"
      "pushl $0x256ce8\n\t"
      "pushl $0x257218\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0003dc20_41:\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movl 0x90(%%eax), %%edx\n\t"
      "movl %%edx, 0x1b8(%%esi)\n\t"
      "movl 0x94(%%eax), %%ecx\n\t"
      "movl %%ecx, 0x1bc(%%esi)\n\t"
      "movl 0xa8(%%eax), %%edx\n\t"
      "movl %%edx, 0x1c0(%%esi)\n\t"
      "movl 0xa4(%%eax), %%eax\n\t"
      "movl %%eax, 0x1c4(%%esi)\n\t"
      ".LFUN_0003dc20_42:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [dget] "m"(b3dc20_dget), [tag] "m"(b3dc20_tag), [get] "m"(b3dc20_get), [c1412f0] "m"(b3dc20_c1412f0), [memset] "m"(b3dc20_memset), [c3bde0] "m"(b3dc20_c3bde0), [c1a9520] "m"(b3dc20_c1a9520), [c18f3e0] "m"(b3dc20_c18f3e0), [c211f0] "m"(b3dc20_c211f0), [c1c270] "m"(b3dc20_c1c270), [c3baa0] "m"(b3dc20_c3baa0), [c18e380] "m"(b3dc20_c18e380), [elem] "m"(b3dc20_elem), [c1ba1f0] "m"(b3dc20_c1ba1f0), [c8f390] "m"(b3dc20_c8f390), [ca7a30] "m"(b3dc20_ca7a30), [c1a9960] "m"(b3dc20_c1a9960), [mag] "m"(b3dc20_mag), [norm] "m"(b3dc20_norm), [c21fb0] "m"(b3dc20_c21fb0), [c8d9d0] "m"(b3dc20_c8d9d0), [assert] "m"(b3dc20_assert), [exitfn] "m"(b3dc20_exitfn), [c28610] "m"(b3dc20_c28610)
      : "memory");
}
#else
#error "FUN_0003dc20: clang naked draft required"
#endif


/* actors_handle_unit_effect (0x3e570) — propagate a unit effect (damage/sound)
 * to nearby encounters. Builds a bitfield of audible BSP clusters, then
 * iterates encounters checking if they can hear the effect via
 * actor_audibility_at_point. If audible, finds a prop and dispatches
 * actor_handle_unit_effect. */
void actors_handle_unit_effect(int unit_handle, short unit_effect, int param_3)
{
  char *unit_obj;
  char *node;
  char *scenario;
  char *prop;
  int encounter_handle;
  int prop_handle;
  float position[3];
  float sense_block[14];
  int encounter_iter[8];
  unsigned int cluster_bits[16];
  int encounter_actor;
  int local_c;
  short sVar2;
  int iVar3;
  int i;

  unit_obj = (char *)object_get_and_verify_type(unit_handle, 3);
  encounter_handle = *(int *)(unit_obj + 0x1a8);
  node = unit_obj + 0x48;
  if (encounter_handle == -1) {
    encounter_handle = *(int *)(unit_obj + 0x1a4);
  }
  if (*(int *)(unit_obj + 0xcc) != -1) {
    iVar3 = object_get_root_parent(unit_handle);
    node = (char *)object_get_and_verify_type(iVar3, -1) + 0x48;
  }
  scenario = (char *)scenario_get();
  csmemset(cluster_bits, 0, ((*(int *)(scenario + 0x134) + 0x1f) >> 5) << 2);
  if (*(short *)(node + 4) != -1 && *(int *)(scenario + 0x134) > 0) {
    i = 0;
    do {
      iVar3 = (int)(short)i;
      sVar2 = structure_bsp_cluster_sound_encoding(scenario,
                                                   *(short *)(node + 4), iVar3);
      if ((char)sVar2 >= 0) {
        local_c = (int)(sVar2 & 0x7f);
        if ((float)local_c * *(float *)0x256148 < *(float *)0x257350) {
          cluster_bits[iVar3 >> 5] =
            cluster_bits[iVar3 >> 5] | (1 << (iVar3 & 0x1f));
        }
      }
      i = i + 1;
      iVar3 = (int)(short)i;
    } while (iVar3 < *(int *)(scenario + 0x134));
  }
  object_get_world_position(unit_handle, (vector3_t *)position);
  encounter_iterator_next(encounter_iter, 1);
  iVar3 = FUN_00059b50(encounter_iter);
  while (iVar3 != 0) {
    encounter_actor = *(int *)((char *)encounter_iter + 0x14);
    if (encounter_actor != encounter_handle) {
      sVar2 = *(short *)(iVar3 + 0x148);
      if (sVar2 != -1 &&
          (cluster_bits[(int)sVar2 >> 5] & (1 << ((int)sVar2 & 0x1f))) != 0) {
        actor_perception_find_sense_position(encounter_actor, position, -1,
                                             sense_block);
        sVar2 = actor_audibility_at_point(encounter_actor, sense_block,
                                          position, node, param_3, 1.0f, 0);
        if (sVar2 >= 2) {
          prop_handle = FUN_00064b40(encounter_actor, unit_handle, 1, 1);
          if (prop_handle != -1) {
            prop = (char *)datum_get(prop_data, prop_handle);
            sVar2 = actor_audibility_at_point(
              encounter_actor, sense_block, (float *)(prop + 0xbc), prop + 0xfc,
              param_3, 1.0f, *(short *)(prop + 0x38));
            if (sVar2 >= 2) {
              actor_handle_unit_effect(encounter_actor, prop_handle,
                                       unit_effect);
            }
          }
        }
      }
    }
    iVar3 = FUN_00059b50(encounter_iter);
  }
}

/* FUN_0003e7a0 (0x3e7a0) — XBE naked draft (batch 69). */
#if defined(__clang__)
static void *(*const b3e7a0_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void *(*const b3e7a0_get)(int, int) = object_get_and_verify_type;
static int (*const b3e7a0_c28610)(float *v) = valid_real_normal2d;
static char * (*const b3e7a0_c8d9d0)(char *buffer, const char *format, ...) = csprintf;
static void (*const b3e7a0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b3e7a0_exitfn)(int) = system_exit;
static bool (*const b3e7a0_c21fb0)(float *v) = valid_real_normal3d;
static bool (*const b3e7a0_cba6f0)(void) = player_input_enabled;
static void (*const b3e7a0_c1adf10)(int unit_handle, char param_2) = unit_set_actively_controlled;
static void (*const b3e7a0_c1af990)(int unit_handle, void *unit_control) = unit_set_control;
static bool (*const b3e7a0_c1b1a20)(int unit_handle, int anim_index, void *anim_data) = unit_apply_animation_impulse;
static void (*const b3e7a0_c1a8190)(int unit_handle, int animation_ticks, int control_flags) = unit_persistent_control;

__attribute__((naked, noinline))
void FUN_0003e7a0(int actor_handle /* */ __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x40, %%esp\n\t"
      "movl 0x6325a4, %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x18(%%esi), %%edx\n\t"
      "pushl $3\n\t"
      "pushl %%edx\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%ebx\n\t"
      "movswl 0x6dc(%%esi), %%eax\n\t"
      "movb 0x256c94(,%%eax,2), %%cl\n\t"
      "movb %%cl, -0x40(%%ebp)\n\t"
      "movw 0x6d0(%%esi), %%dx\n\t"
      "movw %%dx, -0x3e(%%ebp)\n\t"
      "movl 0x720(%%esi), %%eax\n\t"
      "movl %%eax, -0x28(%%ebp)\n\t"
      "leal 0x6e0(%%esi), %%ecx\n\t"
      "movl (%%ecx), %%edx\n\t"
      "movl %%edx, -0x34(%%ebp)\n\t"
      "movl 0x4(%%ecx), %%eax\n\t"
      "movl %%eax, -0x30(%%ebp)\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "movl %%ecx, -0x2c(%%ebp)\n\t"
      "movb 0x6f8(%%esi), %%dl\n\t"
      "movb %%dl, -0x3f(%%ebp)\n\t"
      "leal 0x6fc(%%esi), %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "movl %%ecx, -0x24(%%ebp)\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl %%edx, -0x20(%%ebp)\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl %%eax, -0x1c(%%ebp)\n\t"
      "leal 0x708(%%esi), %%ecx\n\t"
      "movl (%%ecx), %%edx\n\t"
      "movl %%edx, -0x18(%%ebp)\n\t"
      "movl 0x4(%%ecx), %%eax\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "movl %%ecx, -0x10(%%ebp)\n\t"
      "leal 0x714(%%esi), %%edx\n\t"
      "movl (%%edx), %%eax\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "movl 0x4(%%edx), %%ecx\n\t"
      "orl $0xffffffff, %%edi\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "movl 0x8(%%edx), %%edx\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      "movw %%di, -0x3c(%%ebp)\n\t"
      "movw %%di, -0x3a(%%ebp)\n\t"
      "movw %%di, -0x38(%%ebp)\n\t"
      "movb 0x99(%%esi), %%al\n\t"
      "addl $0x10, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_0003e7a0_1\n\t"
      "leal -0x24(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c28610]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_0003e7a0_1\n\t"
      "flds -0x20(%%ebp)\n\t"
      "pushl $1\n\t"
      "pushl $0xf06\n\t"
      "pushl $0x256ce8\n\t"
      "subl $0x10, %%esp\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds -0x24(%%ebp)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x257438\n\t"
      "pushl $0x2555d4\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x1c, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl %%edi\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0003e7a0_1:\n\t"
      "leal -0x24(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c21fb0]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_0003e7a0_2\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "pushl $1\n\t"
      "pushl $0xf08\n\t"
      "pushl $0x256ce8\n\t"
      "subl $0x18, %%esp\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds -0x20(%%ebp)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds -0x24(%%ebp)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x25741c\n\t"
      "pushl $0x254a24\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x24, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl %%edi\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0003e7a0_2:\n\t"
      "leal -0x18(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c21fb0]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_0003e7a0_3\n\t"
      "flds -0x10(%%ebp)\n\t"
      "pushl $1\n\t"
      "pushl $0xf09\n\t"
      "pushl $0x256ce8\n\t"
      "subl $0x18, %%esp\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x257400\n\t"
      "pushl $0x254a24\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x24, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl %%edi\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0003e7a0_3:\n\t"
      "leal -0xc(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c21fb0]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_0003e7a0_4\n\t"
      "flds -0x4(%%ebp)\n\t"
      "pushl $1\n\t"
      "pushl $0xf0a\n\t"
      "pushl $0x256ce8\n\t"
      "subl $0x18, %%esp\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x2573e0\n\t"
      "pushl $0x254a24\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x24, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl %%edi\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0003e7a0_4:\n\t"
      "flds -0x34(%%ebp)\n\t"
      "fabs\n\t"
      "fcompl 0x2573d8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .LFUN_0003e7a0_5\n\t"
      "flds -0x30(%%ebp)\n\t"
      "fabs\n\t"
      "fcompl 0x2573d8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .LFUN_0003e7a0_5\n\t"
      "flds -0x2c(%%ebp)\n\t"
      "fabs\n\t"
      "fcompl 0x2573d8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jnp .LFUN_0003e7a0_6\n\t"
      ".LFUN_0003e7a0_5:\n\t"
      "pushl $1\n\t"
      "pushl $0xf0b\n\t"
      "pushl $0x256ce8\n\t"
      "pushl $0x257358\n\t"
      "call *%[assert]\n\t"
      "pushl %%edi\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0003e7a0_6:\n\t"
      "cmpl %%edi, 0x1c8(%%ebx)\n\t"
      "je .LFUN_0003e7a0_7\n\t"
      "call *%[cba6f0]\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_0003e7a0_10\n\t"
      ".LFUN_0003e7a0_7:\n\t"
      "movb 0x7(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0003e7a0_8\n\t"
      "movl 0x18(%%esi), %%ecx\n\t"
      "pushl $1\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1adf10]\n\t"
      "addl $8, %%esp\n\t"
      "movb $0, 0x7(%%esi)\n\t"
      ".LFUN_0003e7a0_8:\n\t"
      "movl 0x18(%%esi), %%eax\n\t"
      "leal -0x40(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c1af990]\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x6ec(%%esi), %%ax\n\t"
      "addl $8, %%esp\n\t"
      "cmpw %%di, %%ax\n\t"
      "je .LFUN_0003e7a0_9\n\t"
      "movl 0x18(%%esi), %%edx\n\t"
      "leal 0x6f0(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%edx\n\t"
      "call *%[c1b1a20]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_0003e7a0_9:\n\t"
      "movw 0x6d4(%%esi), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "jle .LFUN_0003e7a0_10\n\t"
      "movl 0x6d8(%%esi), %%ecx\n\t"
      "movswl %%ax, %%edx\n\t"
      "movl 0x18(%%esi), %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c1a8190]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_0003e7a0_10:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [dget] "m"(b3e7a0_dget), [get] "m"(b3e7a0_get), [c28610] "m"(b3e7a0_c28610), [c8d9d0] "m"(b3e7a0_c8d9d0), [assert] "m"(b3e7a0_assert), [exitfn] "m"(b3e7a0_exitfn), [c21fb0] "m"(b3e7a0_c21fb0), [cba6f0] "m"(b3e7a0_cba6f0), [c1adf10] "m"(b3e7a0_c1adf10), [c1af990] "m"(b3e7a0_c1af990), [c1b1a20] "m"(b3e7a0_c1b1a20), [c1a8190] "m"(b3e7a0_c1a8190)
      : "memory");
}
#else
#error "FUN_0003e7a0: clang naked draft required"
#endif


/* actor_attach_unit (0x3eab0) — link an individual (non-swarm) unit to an
 * actor.
 *
 * Detaches any prior actor-unit associations (both directions) before
 * establishing the new link.  If the actor already holds a unit, that unit is
 * detached via actor_detach_from_unit.  If the unit already belongs to a
 * different actor, that actor is notified via actor_swarm_detach_from_unit
 * (swarm path) and actor_delete. After checks the function writes: actor+0x18 =
 * unit_index  (actor->meta.unit_index) unit+0x1a4  = actor_handle
 * (unit->unit.actor_index) If actor is part of an encounter (actor+0x34 != -1)
 * it syncs the encounter biped data via encounter_attach_unit and copies the
 * team word (encounter_datum+2) into unit+0x68.  actor+0x3e is then set to
 * unit+0x68 (actor->team = unit->team). If unit health (unit+0x6e) >= 100 the
 * actor "fully_alive" byte (actor+0x1c) is set to 1, and if an encounter exists
 * its alive-unit counter (short at encounter+0x1c) is incremented. Runs actor
 * input update (FUN_0003dc20), object_set_automatic_deactivation, and activates
 * the unit (object_activate or object_deactivate depending on actor+0x13
 * dormant flag). Calls unit_set_actively_controlled(unit_index, 1).  Always
 * ends with actor_verify_activation(actor_handle).
 *
 * Confirmed: datum_get(actor_data, actor_handle) at 0x3eac1.
 * Confirmed: object_get_and_verify_type(unit_index, 3) at 0x3eace.
 * Confirmed: early-out if unit->actor_index == actor_handle at 0x3ead5-0x3eae3.
 * Confirmed: actor_swarm_detach_from_unit(unit->swarm_actor_index, unit_index)
 * at 0x3eaf6. Confirmed: actor_delete(unit->actor_index, 0) at 0x3eb0c.
 * Confirmed: actor_detach_from_unit(actor_handle) if actor->unit_index != -1 at
 * 0x3eb1e. Confirmed: 4× display_assert + system_exit guard block at
 * 0x3eb2b-0x3ebc4. Confirmed: actor+0x18 = unit_index (EBX) at 0x3ebc8.
 * Confirmed: unit+0x1a4 = actor_handle at 0x3ebcb.
 * Confirmed: datum_get(encounter_data, actor->encounter_handle) +
 * encounter_attach_unit at 0x3ebe1/0x3ebf0; unit+0x68 = encounter_datum+2 at
 * 0x3ebff. Confirmed: actor+0x3e = unit+0x68 at 0x3ec07. Confirmed: unit+0x6e
 * >= 100 → actor+0x1c = 1 at 0x3ec18 (scheduler hoisted). Confirmed:
 * encounter+0x1c incremented when encounter != -1 at 0x3ec2e. Confirmed:
 * FUN_0003dc20(actor_handle) at 0x3ec36. Confirmed:
 * object_set_automatic_deactivation(unit_index, 0) at 0x3ec3e. Confirmed:
 * actor+0x13 selects object_deactivate vs object_activate at 0x3ec4e/0x3ec55.
 * Confirmed: unit_set_actively_controlled(unit_index, 1) at 0x3ec60. Confirmed:
 * actor_verify_activation(actor_handle) always called at 0x3ec6c. */
void actor_attach_unit(int actor_handle, int unit_index)
{
  char *actor;
  char *unit;
  char *encounter_datum;

  actor = (char *)datum_get(actor_data, actor_handle);
  unit = (char *)object_get_and_verify_type(unit_index, 3);

  /* Early-out: unit already linked to this actor. */
  if (*(int *)(unit + 0x1a4) == actor_handle) {
    actor_verify_activation(actor_handle);
    return;
  }

  /* Detach unit from its current swarm actor (if any). */
  if (*(int *)(unit + 0x1a8) != -1) {
    actor_swarm_detach_from_unit(*(int *)(unit + 0x1a8), unit_index);
  }

  /* Detach unit from its current individual actor (if any). */
  if (*(int *)(unit + 0x1a4) != -1) {
    actor_delete(*(int *)(unit + 0x1a4), 0);
  }

  /* Detach actor's existing unit (if any). */
  if (*(int *)(actor + 0x18) != -1) {
    actor_detach_from_unit(actor_handle);
  }

  /* Consistency checks: actor must not be a swarm, and both sides must now be
   * unlinked before we form the new association. */
  if (*(char *)(actor + 0x6) != '\0') {
    display_assert("!actor->meta.swarm", "c:\\halo\\SOURCE\\ai\\actors.c",
                   0x364, 1);
    system_exit(-1);
  }
  if (*(int *)(actor + 0x18) != -1) {
    display_assert("actor->meta.unit_index == NONE",
                   "c:\\halo\\SOURCE\\ai\\actors.c", 0x365, 1);
    system_exit(-1);
  }
  if (*(int *)(unit + 0x1a4) != -1) {
    display_assert("unit->unit.actor_index == NONE",
                   "c:\\halo\\SOURCE\\ai\\actors.c", 0x366, 1);
    system_exit(-1);
  }
  if (*(int *)(unit + 0x1a8) != -1) {
    display_assert("unit->unit.swarm_actor_index == NONE",
                   "c:\\halo\\SOURCE\\ai\\actors.c", 0x367, 1);
    system_exit(-1);
  }

  /* Establish the actor <-> unit link. */
  *(int *)(actor + 0x18) = unit_index;
  *(int *)(unit + 0x1a4) = actor_handle;

  /* Sync encounter biped data and team affiliation. */
  if (*(int *)(actor + 0x34) != -1) {
    encounter_datum =
      (char *)datum_get(*(data_t **)0x5ab270, *(int *)(actor + 0x34));
    encounter_attach_unit(*(int *)(actor + 0x34), unit_index);
    *(short *)(unit + 0x68) = *(short *)(encounter_datum + 2);
  }
  *(short *)(actor + 0x3e) = *(short *)(unit + 0x68);

  /* If unit is at full health, mark actor fully alive and bump encounter
   * counter (MSVC hoisted the actor+0x1c store before the encounter_handle
   * branch). */
  if (*(short *)(unit + 0x6e) >= 100) {
    *(char *)(actor + 0x1c) = 1;
    if (*(int *)(actor + 0x34) != -1) {
      encounter_datum =
        (char *)datum_get(*(data_t **)0x5ab270, *(int *)(actor + 0x34));
      *(short *)(encounter_datum + 0x1c) += 1;
    }
  }

  /* Update actor input state, finalize unit flags, and activate unit. */
  FUN_0003dc20(actor_handle);
  object_set_automatic_deactivation(unit_index, 0);
  if (*(char *)(actor + 0x13) != '\0') {
    object_deactivate(unit_index);
  } else {
    object_activate(unit_index);
  }
  unit_set_actively_controlled(unit_index, 1);

  actor_verify_activation(actor_handle);
}

/* FUN_0003ec80 (0x3ec80) — actor_activate (full AI init sequence for one actor)
 *
 * Called from FUN_0003f5f0 (ai.obj) when actor+0x6a > 0 (activation counter
 * exhausted) and the actor has not yet been activated. Runs all per-actor
 * AI subsystem initialization in sequence.
 *
 * Classification evidence: caller FUN_0003f5f0 is in ai.obj; all callees
 * (FUN_0003d9f0, FUN_0003dc20, FUN_0003bb50, FUN_0003bbf0, FUN_0003be90,
 * FUN_0003e7a0) live in the actors.obj address range (~0x3b000-0x3e9aa) and
 * operate exclusively on actor_data. Function is placed at the end of
 * actors.obj (follows actor_erase at 0x3d950).
 *
 * Confirmed: actor_handle passed in ESI (register arg @<esi>).
 *   MOV ESI,[EBP-8]; CALL 0x3ec80 at caller 0x3f652/0x3f655.
 * Confirmed: first datum_get(actor_data, actor_handle) at 0x3ec8b.
 *   Result stored in [EBP-4] for use as iVar2/actor record.
 * Confirmed: DAT_002c8728 = actor_handle at 0x3ecaa (before any branch).
 * Confirmed: debug block byte[0x5ac9c0] cleared if actor_handle == [0x5ac9f8]
 *   at 0x3ecb2/0x3ecba.
 * Confirmed: FUN_0003d9f0(actor_handle) cdecl at 0x3ecc3; returns bool/char.
 *   ADD ESP,4 at 0x3ecc8. Return tested; JZ 0x3edae → early out.
 * Confirmed: FUN_0003bb50(actor_handle@<eax>) at 0x3ecd6 (MOV EAX,ESI).
 * Confirmed: FUN_0003dc20(actor_handle) cdecl at 0x3ecdc.
 * Confirmed: FUN_0003355f0(actor_handle) cdecl at 0x3ece2.
 * Confirmed: actor_situation_update(actor_handle) cdecl at 0x3ece8.
 * Confirmed: actor_emotion_update(actor_handle) cdecl at 0x3ecee.
 * Confirmed: second datum_get(actor_data, actor_handle) at 0x3ecfb; result
 *   in EDI, used as iVar3/actor record for memset+field init.
 * Confirmed: csmemset(actor+0x3e8, 0, 0x84) at 0x3ed10.
 * Confirmed: word[actor+0x418]=0xffff, [0x42c]=0xffff, [0x42e]=0xffff at
 *   0x3ed19/0x3ed20/0x3ed27. EBX = 0xffffffff set by OR EBX,0xffffffff.
 * Confirmed: FUN_0003be90(actor_handle) cdecl at 0x3ed2e (PUSH ESI at 0x3ed18).
 * Confirmed: actor_action_update(actor_handle) cdecl at 0x3ed34.
 * Confirmed: ADD ESP,0x2c at 0x3ed3f cleans 11 cdecl args.
 * Confirmed: iVar2/actor+0x13 checked at 0x3ed3c; JNZ → skip subsystem init.
 * Confirmed: iVar2/actor+6 checked at 0x3ed47; JNZ (swarm actor) → call
 *   FUN_0003a8a0(actor_handle) then return.
 * Confirmed: FUN_0003bbf0(actor_handle@<eax>) at 0x3ed64 (MOV EAX,ESI).
 * Confirmed: 8 cdecl calls follow (0x1c3e0, 0x43db0, 0x14540, 0x2d350,
 *   0x2a2b0, 0x2e560, 0x29040, 0x22dc0); ADD ESP,0x20 at 0x3ed99.
 * Confirmed: FUN_0003e7a0(actor_handle@<eax>) at 0x3ed9e (MOV EAX,ESI).
 * Confirmed: DAT_002c8728 = EBX (0xffffffff) at 0x3eda3 (normal exit).
 * Confirmed: DAT_002c8728 = 0xffffffff at 0x3edae (early-out path, literal).
 * Inferred: DAT_002c8728 holds the "currently activating actor" handle;
 *   reset to -1 on all exit paths including early bail-out.
 * Inferred: byte[0x5ac9c0] is an AI debug focused-actor flag (see ai_debug.c).
 *   Cleared here to prevent stale display after actor is re-activated.
 * Inferred: actor+0x13 is a "don't initialize" or dormant flag;
 *   non-zero skips all subsystem init and just resets DAT_002c8728.
 * Inferred: actor+6 distinguishes swarm vs. normal actor type; swarm actors
 *   take a shortened init path via FUN_0003a8a0. */
void FUN_0003ec80(int actor_handle /* @<esi> */)
{
  char *actor;
  char *actor2;
  char ok;

  /* Record first datum_get result (iVar2) for field checks below */
  actor = (char *)datum_get(actor_data, actor_handle);
  /* Unused second call result discarded by compiler — both use same handle */
  datum_get(actor_data, actor_handle);

  /* Track which actor is being activated */
  *(int *)0x2c8728 = actor_handle;

  /* Clear AI debug focus flag if it points at this actor */
  if (*(char *)0x5ac9c0 != 0 && *(int *)0x5ac9f8 == actor_handle) {
    *(char *)0x5ac9c0 = 0;
  }

  /* Run actor validation/pre-init; bail if not ready */
  ok = FUN_0003d9f0(actor_handle);
  if (ok == 0) {
    *(int *)0x2c8728 = -1;
    return;
  }

  /* --- actor is ready for activation --- */

  /* Subsystem pre-init */
  FUN_0003bb50(actor_handle);
  FUN_0003dc20(actor_handle);
  FUN_000355f0(actor_handle);
  actor_situation_update(actor_handle);
  actor_emotion_update(actor_handle);

  /* Reload actor record (EDI path for memset+field writes) */
  actor2 = (char *)datum_get(actor_data, actor_handle);

  /* Zero 0x84 bytes of actor state starting at offset 0x3e8 */
  csmemset(actor2 + 0x3e8, 0, 0x84);

  /* Initialize handle sentinel fields to 0xffff */
  *(short *)(actor2 + 0x418) = (short)0xffff;
  *(short *)(actor2 + 0x42c) = (short)0xffff;
  *(short *)(actor2 + 0x42e) = (short)0xffff;

  /* More subsystem init */
  FUN_0003be90(actor_handle);
  actor_action_update(actor_handle);

  /* Check dormant/don't-activate flag at actor+0x13 */
  if (*(char *)(actor + 0x13) != 0) {
    *(int *)0x2c8728 = -1;
    return;
  }

  /* Swarm actor: shortened init path */
  if (*(char *)(actor + 0x6) != 0) {
    FUN_0003a8a0(actor_handle);
    *(int *)0x2c8728 = -1;
    return;
  }

  /* Normal actor: full subsystem init sequence */
  FUN_0003bbf0(actor_handle);
  actor_action_control(actor_handle);
  actor_communication_update(actor_handle);
  FUN_00014540(actor_handle);
  actor_destination_update(actor_handle);
  FUN_0002a2b0(actor_handle);
  actor_move_update(actor_handle);
  actor_look_update(actor_handle);
  FUN_00022dc0(actor_handle);
  FUN_0003e7a0(actor_handle);

  *(int *)0x2c8728 = -1;
}

/* actor_create_for_unit (0x3edc0) — allocate and initialize an actor record,
 * then link it to its unit.
 *
 * For individual (non-swarm) actors (flags==0): verifies the unit can accept an
 * actor (object_try_and_get_and_verify_type succeeds and bit 2 at +0xb6 is
 * clear). For swarm actors (flags!=0): iterates the encounter's actor list
 * looking for an existing swarm actor that has the same actv_tag, is not at the
 * exclude handle, has fewer than 16 swarm units, and (if param6==0) matches the
 * squad index.
 *
 * Then creates a fresh actor datum via FUN_0003c410 (which allocates from
 * actor_data and initializes all fields). Sets encounter/squad assignment via
 * encounterless_attach_actor (no encounter) or encounter_attach_actor (with
 * encounter). Sets the encounter_flag, squad starting location index, squad
 * position index, swarm-flag, and marker byte on the actor record.
 *
 * Validates that the actor variant's swarm flag matches the actor type's swarm
 * flag (from the actor_type field at actor+4 via FUN_0003a800). On mismatch,
 * prints a warning and destroys the allocated actor.
 *
 * Finally links the unit to the actor: actor_attach_unit for individual,
 * actor_swarm_attach_unit for swarm. On swarm link failure, destroys the actor
 * if it has no swarm units.
 *
 * Returns actor handle, or -1 on failure.
 *
 * Confirmed: 12 cdecl args (ADD ESP,0x30 at 0x3f2a1 in FUN_0003f030).
 * Confirmed: iter[3] at [EBP-0xc]: encounter_actor_iterator_new writes
 * iter[0..2], encounter_actor_iterator_next returns
 * datum_get(actor_data,iter[1]) and advances iter[2] to next handle. Confirmed:
 * actor_data (DAT_006325a4) at 0x3ee88, encounter_data (0x5ab270) at 0x3eeaa.
 * Confirmed: handle-tag construction (MOVSX+SHL+OR) at 0x3eec2-0x3eece.
 * Confirmed: FUN_0003a800 takes int16_t actor_type, returns char swarm flag.
 * Confirmed: strings "swarm" at 0x256cd4, "individual" at 0x256d2c, format
 * string at 0x257468. */
int actor_create_for_unit(char flags, int unit_index, int actv_tag_index,
                          int encounter_index, int squad_index, char param6,
                          int exclude_actor_handle, char encounter_flag,
                          short starting_location_index,
                          short squad_position_index, unsigned short param11,
                          char param12)
{
  char *actor;
  char actor_is_swarm;
  char type_is_swarm;
  char *encounter_ptr;
  int actor_handle;
  int iter[3];
  int current_actor;
  short default_pos;
  const char *type_str;
  const char *variant_name;

  if (unit_index == -1 || actv_tag_index == -1) {
    return -1;
  }

  if (flags == 0) {
    /* Individual actor: check the unit is valid and can accept an actor. */
    actor = (char *)object_try_and_get_and_verify_type(unit_index, 1);
    if (actor == NULL || (*(unsigned char *)(actor + 0xb6) & 4) != 0) {
      return -1;
    }
  } else {
    /* Swarm actor: search existing encounter actors for a matching swarm actor
     * to attach to. */
    encounter_actor_iterator_new(iter, encounter_index);
    actor = (char *)encounter_actor_iterator_next(iter);
    current_actor = iter[1];
    while (actor != 0) {
      if (*(char *)(actor + 0x6) != 0 &&
          current_actor != exclude_actor_handle &&
          *(short *)(actor + 0x1e) < 0x10 &&
          *(int *)(actor + 0x5c) == actv_tag_index &&
          (param6 != 0 || *(short *)(actor + 0x3a) == (short)squad_index)) {
        if (current_actor != -1) {
          actor_handle = current_actor;
          goto actor_found;
        }
        break;
      }
      actor = (char *)encounter_actor_iterator_next(iter);
      current_actor = iter[1];
    }
  }

  /* Allocate a new actor datum from actor_data. */
  actor_handle = FUN_0003c410(actv_tag_index);
  if (actor_handle == -1) {
    return -1;
  }
  actor = (char *)datum_get(actor_data, actor_handle);

  /* Assign encounter/squad. */
  if (encounter_index == -1) {
    encounterless_attach_actor(actor_handle);
  } else {
    encounter_ptr = (char *)datum_get(*(data_t **)0x5ab270, encounter_index);
    if ((encounter_index & 0xffff0000) == 0) {
      encounter_index =
        (encounter_index & 0xffff) | ((int)*(short *)encounter_ptr << 0x10);
    }
    encounter_attach_actor(actor_handle, encounter_index, squad_index, 0);
  }

  /* Set encounter membership flag and handle special init for encounter actors.
   */
  if (encounter_flag != 0) {
    *(short *)(actor + 0x6a) = 0;
    if (*(char *)(actor + 8) != 0) {
      actor_set_dormant(actor_handle, 0);
    }
  } else {
    *(short *)(actor + 0x6a) = 2;
  }

  /* Set squad starting location and position indices. */
  *(short *)(actor + 0x60) = starting_location_index;
  *(short *)(actor + 0x62) = squad_position_index;
  if (squad_position_index == -1 || squad_position_index == 0) {
    default_pos =
      (short)actor_action_get_default_state(starting_location_index);
    *(short *)(actor + 0x62) = default_pos;
  }

  /* Store remaining actor fields. */
  actor_is_swarm = *(char *)(actor + 0x6);
  *(char *)(actor + 0x8e) = 0;
  *(short *)(actor + 0x92) = 2;
  *(short *)(actor + 0x90) = (short)param11;
  *(char *)(actor + 0x68) = param12;

  /* Validate swarm flag matches actor type. */
  type_is_swarm = FUN_0003a800((int16_t) * (short *)(actor + 0x4));
  if (actor_is_swarm != type_is_swarm) {
    type_str = "swarm";
    if (actor_is_swarm == 0) {
      type_str = "individual";
    }
    variant_name = tag_name_strip_path(tag_get_name(actv_tag_index));
    error(2,
          "%s actor variant %s cannot have type %s (swarm flag does not match)",
          type_str, variant_name);
    actor_delete(actor_handle, 0);
    return -1;
  }

actor_found:
  /* Link unit to actor. */
  if (flags == 0) {
    actor_attach_unit(actor_handle, unit_index);
  } else {
    if (actor_swarm_attach_unit(actor_handle, unit_index) == 0) {
      actor = (char *)datum_get(actor_data, actor_handle);
      if (*(short *)(actor + 0x1e) == 0) {
        actor_delete(actor_handle, 0);
      }
      actor_verify_activation(-1);
      return -1;
    }
  }
  actor_verify_activation(actor_handle);
  return actor_handle;
}

/* FUN_0003f030 (0x3f030) — XBE naked draft (batch 69). */
#if defined(__clang__)
static void (*const b3f030_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b3f030_exitfn)(int) = system_exit;
static void (*const b3f030_c144b50)(void) = objects_garbage_collect_tick;
static void *(*const b3f030_tag)(int, int) = tag_get;
static void (*const b3f030_opnew)(void *, int, int) = object_placement_data_new;
static void (*const b3f030_c10cc70)(float *output, float angle) = vector3d_from_angle;
static int (*const b3f030_onew)(void *) = object_new;
static char * (*const b3f030_c8dff0)(char *destination, const char *source) = csstrcpy;
static scenario_t * (*const b3f030_c18e380)(void) = global_scenario_get;
static void (*const b3f030_c54220)(unsigned int combined_index, void *scenario, char *buffer, int buffer_size) = FUN_00054220;
static const char * (*const b3f030_c1ba1f0)(int tag_index) = tag_get_name;
static const char * (*const b3f030_c19b0d0)(const char *tag_name) = tag_name_strip_path;
static void (*const b3f030_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;
static void *(*const b3f030_elem)(void *, int, int) = tag_block_get_element;
static void (*const b3f030_c3c7c0)(int actv_tag_index, int unit_index) = actor_customize_unit;
static int (*const b3f030_c3edc0)(char flags, int unit_index, int actv_tag_index, int encounter_index, int squad_index, char param6, int exclude_actor_handle, char encounter_flag, short starting_location_index, short squad_position_index, unsigned short param11, char param12) = actor_create_for_unit;
static void (*const b3f030_odel)(int) = object_delete;
static void (*const b3f030_c3aca0)(int actor_handle) = actor_verify_activation;

__attribute__((naked, noinline))
int FUN_0003f030(int actv_tag_index __attribute__((unused)), int encounter_index __attribute__((unused)), int squad_index __attribute__((unused)), void *starting_location __attribute__((unused)), char use_major_variant __attribute__((unused)), int16_t team __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x190, %%esp\n\t"
      "pushl %%ebx\n\t"
      "movl 0x14(%%ebp), %%ebx\n\t"
      "testl %%ebx, %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "jne .LFUN_0003f030_1\n\t"
      "pushl $1\n\t"
      "pushl $0x25b\n\t"
      "pushl $0x256ce8\n\t"
      "pushl $0x257534\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0003f030_1:\n\t"
      "call *%[c144b50]\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x61637476\n\t"
      "call *%[tag]\n\t"
      "movl %%eax, %%esi\n\t"
      "movb 0x18(%%ebp), %%al\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0003f030_3\n\t"
      "movl 0x30(%%esi), %%esi\n\t"
      "cmpl $-1, %%esi\n\t"
      "movl %%esi, 0x8(%%ebp)\n\t"
      "jne .LFUN_0003f030_2\n\t"
      "pushl $1\n\t"
      "pushl $0x265\n\t"
      "pushl $0x256ce8\n\t"
      "pushl $0x25750c\n\t"
      "call *%[assert]\n\t"
      "pushl %%esi\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0003f030_2:\n\t"
      "pushl %%esi\n\t"
      "pushl $0x61637476\n\t"
      "call *%[tag]\n\t"
      "addl $8, %%esp\n\t"
      "movl %%eax, %%esi\n\t"
      ".LFUN_0003f030_3:\n\t"
      "movl 0x10(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x61637472\n\t"
      "call *%[tag]\n\t"
      "movl 0x20(%%esi), %%edx\n\t"
      "pushl $-1\n\t"
      "movl %%eax, %%edi\n\t"
      "pushl %%edx\n\t"
      "leal -0x90(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[opnew]\n\t"
      "movl %%ebx, %%ecx\n\t"
      "movl (%%ecx), %%edx\n\t"
      "movl 0x4(%%ecx), %%eax\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "movl %%edx, -0x78(%%ebp)\n\t"
      "movl 0xc(%%ebx), %%edx\n\t"
      "movl %%eax, -0x74(%%ebp)\n\t"
      "pushl %%edx\n\t"
      "leal -0x5c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl %%ecx, -0x70(%%ebp)\n\t"
      "call *%[c10cc70]\n\t"
      "movw 0x1c(%%ebp), %%cx\n\t"
      "leal -0x90(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movw %%cx, -0x7a(%%ebp)\n\t"
      "call *%[onew]\n\t"
      "movl 0xc(%%ebp), %%esi\n\t"
      "addl $0x20, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "movl %%eax, 0x1c(%%ebp)\n\t"
      "jne .LFUN_0003f030_6\n\t"
      "cmpl %%eax, %%esi\n\t"
      "jne .LFUN_0003f030_4\n\t"
      "leal -0x190(%%ebp), %%eax\n\t"
      "pushl $0x2574fc\n\t"
      "pushl %%eax\n\t"
      "call *%[c8dff0]\n\t"
      "addl $8, %%esp\n\t"
      "jmp .LFUN_0003f030_5\n\t"
      ".LFUN_0003f030_4:\n\t"
      "leal -0x190(%%ebp), %%ecx\n\t"
      "pushl $0x100\n\t"
      "pushl %%ecx\n\t"
      "call *%[c18e380]\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "andl $0xff, %%edx\n\t"
      "orl $0xffff8000, %%edx\n\t"
      "shll $0x10, %%edx\n\t"
      "andl $0xffff, %%esi\n\t"
      "pushl %%eax\n\t"
      "orl %%esi, %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c54220]\n\t"
      "addl $0x10, %%esp\n\t"
      ".LFUN_0003f030_5:\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "leal -0x190(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1ba1f0]\n\t"
      "pushl %%eax\n\t"
      "call *%[c19b0d0]\n\t"
      "addl $8, %%esp\n\t"
      "pushl %%eax\n\t"
      "pushl $0x2574d0\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $0x10, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "orl $0xffffffff, %%eax\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0003f030_6:\n\t"
      "cmpl $-1, %%esi\n\t"
      "movl 0x10(%%ebp), %%ebx\n\t"
      "je .LFUN_0003f030_7\n\t"
      "movl %%esi, %%edx\n\t"
      "andl $0xffff, %%edx\n\t"
      "pushl $0xb0\n\t"
      "pushl %%edx\n\t"
      "call *%[c18e380]\n\t"
      "addl $0x42c, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_0003f030_7\n\t"
      "pushl $0xe8\n\t"
      "addl $0x80, %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_0003f030_7:\n\t"
      "movl (%%edi), %%eax\n\t"
      "movl 0x1c(%%ebp), %%ecx\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "shrl $0x1a, %%eax\n\t"
      "pushl %%ecx\n\t"
      "andb $1, %%al\n\t"
      "xorl %%edi, %%edi\n\t"
      "pushl %%edx\n\t"
      "movb %%al, -0x8(%%ebp)\n\t"
      "movb $0, -0x4(%%ebp)\n\t"
      "movl %%edi, 0x18(%%ebp)\n\t"
      "call *%[c3c7c0]\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%esi\n\t"
      "je .LFUN_0003f030_8\n\t"
      "movl %%esi, %%eax\n\t"
      "andl $0xffff, %%eax\n\t"
      "pushl $0xb0\n\t"
      "pushl %%eax\n\t"
      "call *%[c18e380]\n\t"
      "addl $0x42c, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl %%eax, %%edi\n\t"
      "pushl $0xe8\n\t"
      "leal 0x80(%%edi), %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ecx\n\t"
      "call *%[elem]\n\t"
      "movl 0x20(%%edi), %%edx\n\t"
      "movw 0x24(%%eax), %%cx\n\t"
      "movw 0x26(%%eax), %%di\n\t"
      "shrl $4, %%edx\n\t"
      "addl $0x18, %%esp\n\t"
      "andb $1, %%dl\n\t"
      "movb %%dl, -0x4(%%ebp)\n\t"
      "movw %%cx, 0x18(%%ebp)\n\t"
      ".LFUN_0003f030_8:\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x16(%%eax), %%cx\n\t"
      "testw %%cx, %%cx\n\t"
      "jle .LFUN_0003f030_9\n\t"
      "movl %%ecx, 0x18(%%ebp)\n\t"
      ".LFUN_0003f030_9:\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x14(%%eax), %%cx\n\t"
      "testw %%cx, %%cx\n\t"
      "jle .LFUN_0003f030_10\n\t"
      "movl %%ecx, %%edi\n\t"
      ".LFUN_0003f030_10:\n\t"
      "movl 0x18(%%ebp), %%edx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x1a(%%eax), %%cx\n\t"
      "movsbw 0x12(%%eax), %%ax\n\t"
      "pushl %%eax\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "pushl %%ecx\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "pushl %%edi\n\t"
      "pushl %%edx\n\t"
      "movl 0x1c(%%ebp), %%edx\n\t"
      "pushl %%eax\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "pushl $-1\n\t"
      "pushl $0\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c3edc0]\n\t"
      "movl %%eax, %%edi\n\t"
      "addl $0x30, %%esp\n\t"
      "cmpl $-1, %%edi\n\t"
      "jne .LFUN_0003f030_13\n\t"
      "cmpl %%eax, %%esi\n\t"
      "jne .LFUN_0003f030_11\n\t"
      "leal -0x190(%%ebp), %%ecx\n\t"
      "pushl $0x2574fc\n\t"
      "pushl %%ecx\n\t"
      "call *%[c8dff0]\n\t"
      "addl $8, %%esp\n\t"
      "jmp .LFUN_0003f030_12\n\t"
      ".LFUN_0003f030_11:\n\t"
      "leal -0x190(%%ebp), %%edx\n\t"
      "pushl $0x100\n\t"
      "pushl %%edx\n\t"
      "call *%[c18e380]\n\t"
      "andl $0xff, %%ebx\n\t"
      "orl $0xffff8000, %%ebx\n\t"
      "shll $0x10, %%ebx\n\t"
      "andl $0xffff, %%esi\n\t"
      "pushl %%eax\n\t"
      "orl %%esi, %%ebx\n\t"
      "pushl %%ebx\n\t"
      "call *%[c54220]\n\t"
      "addl $0x10, %%esp\n\t"
      ".LFUN_0003f030_12:\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "leal -0x190(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1ba1f0]\n\t"
      "pushl %%eax\n\t"
      "call *%[c19b0d0]\n\t"
      "addl $8, %%esp\n\t"
      "pushl %%eax\n\t"
      "pushl $0x2574ac\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "movl 0x1c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[odel]\n\t"
      "addl $0x14, %%esp\n\t"
      "movl %%edi, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0003f030_13:\n\t"
      "pushl %%edi\n\t"
      "call *%[c3aca0]\n\t"
      "addl $4, %%esp\n\t"
      "movl %%edi, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b3f030_assert), [exitfn] "m"(b3f030_exitfn), [c144b50] "m"(b3f030_c144b50), [tag] "m"(b3f030_tag), [opnew] "m"(b3f030_opnew), [c10cc70] "m"(b3f030_c10cc70), [onew] "m"(b3f030_onew), [c8dff0] "m"(b3f030_c8dff0), [c18e380] "m"(b3f030_c18e380), [c54220] "m"(b3f030_c54220), [c1ba1f0] "m"(b3f030_c1ba1f0), [c19b0d0] "m"(b3f030_c19b0d0), [c8f390] "m"(b3f030_c8f390), [elem] "m"(b3f030_elem), [c3c7c0] "m"(b3f030_c3c7c0), [c3edc0] "m"(b3f030_c3edc0), [odel] "m"(b3f030_odel), [c3aca0] "m"(b3f030_c3aca0)
      : "memory");
}
#else
#error "FUN_0003f030: clang naked draft required"
#endif

