/* ai_communication.c — AI communication dialogue/reply subsystem lifecycle.
 *
 * Corresponds to addresses 0x42a30–0x42ca0 in the XBE.
 * Source path confirmed via __FILE__ string:
 *   c:\halo\SOURCE\ai\ai_communication.c
 *
 * Subsystem roles:
 *   ai_communication_initialize             (0x42a30) — allocate comm tables
 *                                                        and conversation data
 *   ai_communication_dispose                (0x42b80) — no-op stub
 *   ai_communication_initialize_for_new_map (0x42b90) — reset comm state for
 *                                                        a new map load
 *   ai_communication_dispose_from_old_map   (0x42ca0) — invalidate
 *                                                        conversation data
 *
 * Key globals (all raw addresses — no named headers exist yet):
 *   0x331f08  int16_t: count of comm dialogue entries (stride 0x28)
 *   0x331f0c  void *:  allocated comm dialogue status table
 *                      (DAT_00331f08 * 2 entries, each 8 bytes)
 *   0x331f10  int16_t: count of comm reply entries (stride 0x24)
 *   0x331f14  void *:  allocated comm reply status table
 *                      (DAT_00331f10 * 2 entries, each 8 bytes)
 *   0x6324ec  data_t *: "ai conversation" data table
 *   0x632574  void *:  AI globals block (shared with ai.c)
 *
 * Static tables (read-only data):
 *   0x257e48  comm dialogue table; each entry is 0x28 bytes; sentinel = -1
 *             at entry[0] (a short).
 *   0x258eb0  comm reply table; each entry is 0x24 bytes; sentinel = -1
 *             at entry[0] (a short).
 *   0x632500  int16_t[0x39]: index map built during initialize
 */

/* ai_communication_initialize: count comm dialogue/reply table entries,
 * allocate per-entry status tables via game_state_malloc, build a dialogue
 * index map into 0x632500[], and allocate the "ai conversation" data table.
 *
 * Confirmed: __FILE__ = "c:\halo\SOURCE\ai\ai_communication.c"
 *   line 0x286 (646) -> dialogue alloc assert
 *   line 0x293 (659) -> reply alloc assert
 *   line 0x2a8 (680) -> conversation data assert
 * Called from ai_initialize (0x3f670). */
void ai_communication_initialize(void)
{
  int16_t i;
  int16_t count;

  /* --- count comm dialogue entries (stride 0x28, sentinel = -1 at [0]) */
  count = 0;
  {
    int16_t *p = (int16_t *)0x257e48;
    do {
      p += 0x14; /* advance by 0x28 bytes (stride = 0x28) */
      count++;
    } while (*p != -1);
  }
  *(int16_t *)0x331f08 = count;

  /* allocate dialogue status table if not already present */
  if (*(void **)0x331f0c == 0) {
    *(void **)0x331f0c =
      game_state_malloc("ai communication dialogue", 0, (int)count << 4);
    if (*(void **)0x331f0c == 0) {
      display_assert("ai_communication_initialize: unable to allocate comm "
                     "dialogue status table",
                     "c:\\halo\\SOURCE\\ai\\ai_communication.c", 0x286, 1);
      system_exit(-1);
    }
  }

  /* --- count comm reply entries (stride 0x24, sentinel = -1 at [0]) */
  count = 0;
  {
    int16_t *p = (int16_t *)0x258eb0;
    do {
      p += 0x12; /* advance by 0x24 bytes (stride = 0x24) */
      count++;
    } while (*p != -1);
  }
  *(int16_t *)0x331f10 = count;

  /* allocate reply status table if not already present */
  if (*(void **)0x331f14 == 0) {
    *(void **)0x331f14 =
      game_state_malloc("ai communication replies", 0, (int)count << 4);
    if (*(void **)0x331f14 == 0) {
      display_assert("ai_communication_initialize: unable to allocate comm "
                     "reply status table",
                     "c:\\halo\\SOURCE\\ai\\ai_communication.c", 0x293, 1);
      system_exit(-1);
    }
  }

  /* --- build dialogue index map into 0x632500[0..0x38].
   * For each slot i (0..0x38), walk the dialogue table and store the
   * sequential index of the entry whose sentinel-short equals i, or -1
   * if not found. Confirmed: CMP DI,0x39 / JL loop in disassembly. */
  {
    int16_t *out = (int16_t *)0x632500;
    for (i = 0; i < 0x39; i++, out++) {
      int16_t j = 0;
      int16_t *entry = (int16_t *)0x257e48;
      int16_t cur_sentinel;
      *out = -1;
      cur_sentinel = 0;
      do {
        if (cur_sentinel == i) {
          *out = j;
          break;
        }
        cur_sentinel = entry[0x14]; /* next sentinel at stride offset */
        entry += 0x14;
        j++;
      } while (cur_sentinel != -1);
    }
  }

  /* allocate "ai conversation" data table: max 8 entries, each 100 bytes.
   * Confirmed: PUSH 0x64; PUSH 0x8; PUSH name ->
   * game_state_data_new(name,8,100) */
  *(void **)0x6324ec = game_state_data_new("ai conversation", 8, 100);
  if (*(void **)0x6324ec == 0) {
    display_assert("conversation_data",
                   "c:\\halo\\SOURCE\\ai\\ai_communication.c", 0x2a8, 1);
    system_exit(-1);
  }
}

/* ai_communication_dispose: no-op stub.
 * Called from ai_dispose (0x3f6f0). Binary is a single RET instruction. */
void ai_communication_dispose(void)
{
}

/* ai_communication_initialize_for_new_map: reset communication state for a
 * new map load.
 *
 * Confirmed via caller: ai_initialize_for_new_map (0x41090).
 * Sets the communication-active flag at AI globals +0x10, zeroes the three
 * 8-byte slots at +0x14/+0x1c/+0x24, clears both dialogue and reply status
 * tables (each entry is 8 bytes: two uint32_t fields both set to 0xffffffff),
 * clears the conversation counter shorts at +0x2c/+0x2e, zeroes the 256-byte
 * conversation scratch buffer at +0x30, and calls data_delete_all on the
 * conversation data table.
 *
 * Store-offset table (offsets into AI globals block via DAT_00632574):
 *   +0x10  <- 1 (byte, communication-active flag)
 *   +0x14  <- csmemset 0, 8 bytes
 *   +0x1c  <- csmemset 0, 8 bytes
 *   +0x24  <- csmemset 0, 8 bytes
 *   dialogue table[i*8+0] <- 0xffffffff (uint32_t)
 *   dialogue table[i*8+4] <- 0xffffffff (uint32_t)
 *   reply table[i*8+0]    <- 0xffffffff (uint32_t)
 *   reply table[i*8+4]    <- 0xffffffff (uint32_t)
 *   +0x2c  <- 0 (int16_t)
 *   +0x2e  <- 0 (int16_t)
 *   +0x30  <- csmemset 0, 0x100 bytes */
void ai_communication_initialize_for_new_map(void)
{
  int n;
  int i;

  *(uint8_t *)(*(uintptr_t *)0x632574 + 0x10) = 1;
  csmemset((void *)(*(uintptr_t *)0x632574 + 0x14), 0, 8);
  csmemset((void *)(*(uintptr_t *)0x632574 + 0x1c), 0, 8);
  csmemset((void *)(*(uintptr_t *)0x632574 + 0x24), 0, 8);

  n = (int)(*(int16_t *)0x331f08) << 1;
  i = 0;
  if (n > 0) {
    do {
      *(unsigned int *)(*(char **)0x331f0c + i * 8 + 4) = ~0u;
      *(unsigned int *)(*(char **)0x331f0c + i * 8) = ~0u;
      i = (int16_t)(i + 1);
    } while (i < (int)(*(int16_t *)0x331f08) << 1);
  }

  n = (int)(*(int16_t *)0x331f10) << 1;
  i = 0;
  if (n > 0) {
    do {
      *(unsigned int *)(*(char **)0x331f14 + i * 8 + 4) = ~0u;
      *(unsigned int *)(*(char **)0x331f14 + i * 8) = ~0u;
      i = (int16_t)(i + 1);
    } while (i < (int)(*(int16_t *)0x331f10) << 1);
  }

  *(int16_t *)(*(char **)0x632574 + 0x2c) = 0;
  *(int16_t *)(*(char **)0x632574 + 0x2e) = 0;
  csmemset((void *)(*(char **)0x632574 + 0x30), 0, 0x100);

  data_delete_all(*(void **)0x6324ec);
}

/* ai_communication_dispose_from_old_map: invalidate the conversation data
 * table when leaving a map.
 *
 * Confirmed via callers: ai_dispose_from_old_map (0x3f720) and
 * ai_handle_editing (0x41e80). Binary: MOV EAX,[0x6324ec]; PUSH EAX;
 * CALL data_make_invalid; POP ECX; RET. */
void ai_communication_dispose_from_old_map(void)
{
  data_make_invalid(*(void **)0x6324ec);
}

/* ai_conversation_advance (0x43520) — iterate all conversations and mark
 * matching entries as advanced. For each conversation whose index field
 * (+0x2) matches param_1, sets byte +0x9 to 1. When the AI debug flag
 * at 0x5aca5f is set, logs the advance via console_printf with the
 * conversation name from the scenario tag block at offset 0x468. */
void ai_conversation_advance(short param_1)
{
  data_iter_t iter;
  char *conversation;

  data_iterator_new(&iter, *(data_t **)0x6324ec);
  conversation = (char *)data_iterator_next(&iter);
  if (conversation == 0) {
    return;
  }
  do {
    if (*(short *)(conversation + 2) == param_1) {
      if (*(char *)0x5aca5f != '\0') {
        console_printf(0, "%s: told to advance by scripting",
          tag_block_get_element(
            (char *)global_scenario_get() + 0x468,
            0x74, (int)param_1));
      }
      conversation[9] = 1;
    }
    conversation = (char *)data_iterator_next(&iter);
  } while (conversation != 0);
}
/* --- ai_communication.obj batch1 drafts (2026-07-26) --- */

char actor_is_fighting(int actor_handle);
char FUN_0003b120(int actor);
void ai_conversation_finish(int handle, char param_b, char param_c);
int FUN_00064b40(int a, int b, int c, int d);
int16_t FUN_0003a770(int16_t actor_type);

const char *ai_communication_get_type_name(int16_t type)
{
  if (type >= 0 && type < 0x39)
    return *(const char **)((char *)0x2c8d78 + (int)type * 4);
  return (const char *)0x253b58;
}

int16_t ai_communication_get_type_by_name(const char *name)
{
  int i;
  const char **table = (const char **)0x2c8d78;
  int16_t result = -1;

  for (i = 0; i < 0x39; i++) {
    if (csstrcmp(name, table[i]) == 0) {
      result = (int16_t)i;
      break;
    }
  }
  return result;
}

void ai_communication_packet_new(void *packet)
{
  if (!packet) {
    display_assert((char *)0x2599f8, "c:\\halo\\SOURCE\\ai\\ai_communication.c",
                   0x300, 1);
    system_exit(-1);
  }
  csmemset(packet, 0, 0x20);
  *(int *)packet = -1;
  *(int16_t *)((char *)packet + 4) = -1;
  *(int16_t *)((char *)packet + 6) = -1;
  *(int16_t *)((char *)packet + 8) = -1;
}

char FUN_00042d80(int actor, int unit, int prop)
{
  char *actor_data;
  float health;

  if (prop == -1)
    return 0;
  if (FUN_00064b40(1, 1, unit, prop) == -1)
    return 0;
  actor_data = (char *)datum_get(*(data_t **)0x5ab23c, prop);
  health = *(float *)(actor_data + 0x11c);
  if (health <= *(float *)0x254cc4)
    return 0;
  {
    int16_t mode = *(int16_t *)(actor_data + 0x38);
    if (mode != 0 && mode != 1)
      return 0;
  }
  return 1;
}

char FUN_00042df0(int actor, int unit, int prop)
{
  char *actor_data;

  if (prop == -1)
    return 0;
  if (FUN_00064b40(1, 1, unit, prop) == -1)
    return 0;
  actor_data = (char *)datum_get(*(data_t **)0x5ab23c, prop);
  if (*(float *)(actor_data + 0x11c) <= *(float *)0x254cc4)
    return 1;
  return 0;
}

char FUN_00042e60(int actor, int unit, int prop)
{
  char *actor_data;
  int16_t state;

  if (prop == -1)
    return 0;
  actor_data = (char *)datum_get(*(data_t **)0x6325a4, prop);
  state = *(int16_t *)(actor_data + 0x6c);
  if (state == 5)
    return *(int16_t *)(actor_data + 0xa4) == 1;
  if (state == 7)
    return 1;
  return 0;
}

char FUN_00042eb0(int actor, int unit, int prop)
{
  char *a;
  char *b;

  if (!FUN_00042d80(actor, unit, prop))
    return 0;
  {
    char *obj = (char *)object_get_and_verify_type(unit, 3);
    int handle = *(int *)(obj + 0x1a4);
    if (handle == -1 || prop == -1)
      return 0;
    a = (char *)datum_get(*(data_t **)0x6325a4, handle);
    b = (char *)datum_get(*(data_t **)0x6325a4, prop);
    if (*(int *)(a + 0x34) == -1)
      return 0;
    if (*(int *)(a + 0x34) != *(int *)(b + 0x34))
      return 0;
    if (*(int16_t *)(a + 0x3c) != *(int16_t *)(b + 0x3c))
      return 0;
  }
  return 1;
}

char FUN_00042f40(int a, int b, int actor)
{
  return actor_is_fighting(actor);
}

char FUN_00042f60(int actor, int unit, int prop)
{
  if (!FUN_00042d80(actor, unit, prop))
    return 0;
  if (actor_is_fighting(prop))
    return 1;
  return 0;
}

char FUN_00042fa0(int actor, int unit, int prop)
{
  char *a;
  char *b;
  char *enc_a;
  char *enc_b;

  if (!FUN_00042d80(actor, unit, prop))
    return 0;
  {
    char *obj = (char *)object_get_and_verify_type(unit, 3);
    int handle = *(int *)(obj + 0x1a4);
    if (handle == -1 || prop == -1)
      return 0;
    a = (char *)datum_get(*(data_t **)0x6325a4, handle);
    b = (char *)datum_get(*(data_t **)0x6325a4, prop);
    if (*(int *)(a + 0x270) == -1 || *(int *)(b + 0x270) == -1)
      return 0;
    enc_a = (char *)datum_get(*(data_t **)0x5ab23c, *(int *)(a + 0x270));
    enc_b = (char *)datum_get(*(data_t **)0x5ab23c, *(int *)(b + 0x270));
    return *(int *)(enc_a + 0x18) == *(int *)(enc_b + 0x18);
  }
}

char FUN_00043050(int actor, int unit, int prop)
{
  char *actor_data;

  if (prop == -1)
    return 0;
  actor_data = (char *)datum_get(*(data_t **)0x6325a4, prop);
  if (*(int16_t *)(actor_data + 0x6a) != 3)
    return 0;
  if (*(int16_t *)(actor_data + 0x6e) >= 4)
    return 1;
  return 0;
}

char FUN_00043090(int actor, int unit, int prop)
{
  char *actor_data;

  if (!actor_is_fighting(prop))
    return 0;
  actor_data = (char *)datum_get(*(data_t **)0x6325a4, prop);
  if (*(int16_t *)(actor_data + 4) == 0)
    return 1;
  return 0;
}

int actor_communication_team(int actor)
{
  char *actor_data = (char *)datum_get(*(data_t **)0x6325a4, actor);
  char flags = FUN_0003a770(*(int16_t *)(actor_data + 4));

  if (flags & 2)
    return 0;
  if (flags & 4)
    return 1;
  return -1;
}

int16_t ai_conversation_line(int conversation_index)
{
  data_iter_t iter;
  char *conversation;

  data_iterator_new(&iter, *(data_t **)0x6324ec);
  conversation = (char *)data_iterator_next(&iter);
  while (conversation != NULL) {
    if (*(int16_t *)(conversation + 2) == (int16_t)conversation_index)
      return *(int16_t *)(conversation + 0x48);
    conversation = (char *)data_iterator_next(&iter);
  }
  return 999;
}

void ai_conversation_stop(int conversation_index)
{
  data_iter_t iter;
  char *conversation;

  data_iterator_new(&iter, *(data_t **)0x6324ec);
  conversation = (char *)data_iterator_next(&iter);
  while (conversation != NULL) {
    if (*(int16_t *)(conversation + 2) == (int16_t)conversation_index) {
      if (*(char *)0x5aca5f != 0) {
        console_printf(
            0, (char *)0x259cd4,
            tag_block_get_element((char *)global_scenario_get() + 0x468, 0x74,
                                  conversation_index));
      }
      ai_conversation_finish(iter.datum_handle, 0, 0);
    }
    conversation = (char *)data_iterator_next(&iter);
  }
}

void ai_conversation_actor_deleted(int actor_handle)
{
  data_iter_t iter;
  char *conversation;

  data_iterator_new(&iter, *(data_t **)0x6324ec);
  conversation = (char *)data_iterator_next(&iter);
  while (conversation != NULL) {
    char *def = (char *)tag_block_get_element(
        (char *)global_scenario_get() + 0x468, 0x74,
        *(int16_t *)(conversation + 2));
    int count = *(int *)(def + 0x50);
    int i;

    for (i = 0; i < count; i++) {
      if (*(int *)(conversation + 0x28 + i * 4) == actor_handle) {
        if ((*(uint8_t *)(def + 0x20) & 1) != 0) {
          ai_conversation_finish(iter.datum_handle, 0, 0);
          break;
        }
        *(int *)(conversation + 0x14) &= ~(1 << i);
        *(int *)(conversation + 0x28 + i * 4) = -1;
        if (*(int16_t *)(conversation + 0x4a) == 0)
          conversation[0x63] = 1;
      }
    }
    conversation = (char *)data_iterator_next(&iter);
  }
}
/* --- ai_communication.obj batch2 drafts (2026-07-26) --- */

#include "../../x87_math.h"

static short ftol2(float value)
{
  return (short)(int)value;
}

char actor_is_fighting(int actor_handle);
char FUN_0003b120(int actor);
int FUN_00064b40(int a, int b, int c, int d);
int16_t FUN_0003a770(int16_t actor_type);
short FUN_001a68d0(int unit_handle, short priority, char param_3, char param_4,
                   int *param_5, short *vocalization_type_ref,
                   int *sound_definition_index_ref);
char *FUN_001a6ca0(short param_1);
void FUN_001a6ef0(int actor, short count, void *comm_buf);
char *FUN_001a67b0(short param_1, unsigned char param_2);
void unit_get_head_position(int object_handle, float *out_position);
int FUN_00027a60(int actor_handle, short look_type, short priority,
                 short *look_buf);
int prop_get_active_by_unit_index(int actor_handle, int object_handle);
void *object_try_and_get_and_verify_type(int datum_handle, int type_mask);
void scripted_sound_new(int a0, int a1, float a2);
int scripted_sound_time(int a0);
char sound_scripted_dialog_is_playing(void);
int data_new_at_index(data_t *data);
int data_new_datum(data_t *data, int handle);
void datum_delete(data_t *data, int datum_handle);
int FUN_00043740(int16_t conversation_index, char allow_finish);
char ai_conversation_begin(int conversation_handle, char *flag_out);
void ai_conversation_finish(int handle, char param_b, char param_c);
float ai_communication_get_player_rating(int unit, char use_teams, int *out_unit,
                                         int *out_handle);
void ai_communication_update_speech_timers(int unit, int16_t type, int a,
                                           int16_t dialogue_index,
                                           int16_t reply_index);
int ai_communication_find_global_actor_to_talk(
    int comm_type, int unit, int16_t subtype, int16_t index, int stack_a,
    int stack_b, float max_dist, int mode);
int FUN_00045830(int type, int unit, int actor, int target, int16_t subtype,
                 int16_t index, float max_dist);

int16_t ai_communication_consider_speech(
    void *packet, int unit, int param, int stack_a, int16_t dialogue_type,
    int16_t start_tick, int stack_b, char flag, float *timer, char *out_buf)
{
  int tick_out;
  short anim_result;
  int16_t result = 0;

  if (!packet || !unit) {
    display_assert((char *)0x259a60, "c:\\halo\\SOURCE\\ai\\ai_communication.c",
                   0xc1a, 1);
    system_exit(-1);
  }
  anim_result = FUN_001a68d0(unit, 1, (char)stack_b, 0, &tick_out, NULL, NULL);
  if (anim_result == 0 && out_buf) {
    if (timer) {
      char *name = FUN_001a6ca0((short)param);
      crt_sprintf(out_buf, (char *)0x259a50, name);
    }
  } else if (anim_result == 1 && timer) {
    *(float *)timer *= *(float *)0x2533e4;
  }
  if (game_connection() || *(char *)0x5aca47) {
    if (flag && dialogue_type < 5 && tick_out != -1) {
      int now = game_time_get();
      int elapsed = now - tick_out;
      int16_t end_tick =
          ftol2((float)start_tick +
                *(float *)(0x257cd8 + (int)dialogue_type * 0x28) *
                    *(float *)0x253394);
      if (elapsed <= end_tick) {
        if (timer)
          *(float *)timer = 0.0f;
        if (out_buf) {
          crt_sprintf(out_buf, (char *)0x259a40, (int)(end_tick - start_tick),
                      (int)start_tick, (int)elapsed);
        }
        return 0;
      }
      if (elapsed < end_tick + 0x3c) {
        if (timer)
          *(float *)timer =
              (float)(elapsed - end_tick) * *(float *)timer * *(float *)0x25634c;
      }
    }
    if (anim_result != 0 && timer &&
        *(float *)timer > *(float *)0x2533c0) {
      display_assert((char *)0x259a04,
                     "c:\\halo\\SOURCE\\ai\\ai_communication.c", 0xc49, 1);
      system_exit(-1);
    }
  }
  return result;
}

void FUN_000432b0(int unit, int actor, int target, int stack_a, short priority)
{
  short look_buf[4];

  if (unit == -1 || priority <= 0 || target == -1)
    return;
  if (!object_try_and_get_and_verify_type(target, 3))
    return;
  if (actor == -1) {
    actor = prop_get_active_by_unit_index(unit, target);
    if (actor == -1)
      goto use_head;
  } else {
    char *prop = (char *)datum_get(*(data_t **)0x5ab23c, actor);
    int16_t mode = *(int16_t *)(prop + 0x24);
    if (mode >= 2 && mode <= 3 && actor != -1) {
      look_buf[0] = 1;
      *(int *)&look_buf[1] = actor;
      FUN_00027a60(stack_a, priority, 5, look_buf);
      return;
    }
  }
use_head:
  look_buf[0] = 3;
  *(int *)&look_buf[1] = target;
  unit_get_head_position(target, (float *)&look_buf[1]);
  FUN_00027a60(stack_a, priority, 5, look_buf);
}

void FUN_00043360(int unit, short priority, int actor, int stack_a)
{
  short look_buf[4];

  if (unit == -1 || priority <= 0 || actor == -1)
    return;
  if (!object_try_and_get_and_verify_type(actor, -1))
    return;
  look_buf[0] = 6;
  *(int *)&look_buf[1] = actor;
  FUN_00027a60(stack_a, priority, 5, look_buf);
}

int16_t ai_conversation_status(int16_t conversation_index)
{
  data_iter_t iter;
  char *conversation;
  int16_t best = 0;

  data_iterator_new(&iter, *(data_t **)0x6324ec);
  conversation = (char *)data_iterator_next(&iter);
  while (conversation != NULL) {
    if (*(int16_t *)(conversation + 2) == conversation_index) {
      int16_t status;
      if (conversation[6] == 0)
        status = 1;
      else if (conversation[5] == 0)
        status = 2;
      else
        status = (conversation[8] != 0) ? 4 : 3;
      if (status > best)
        best = status;
    }
    conversation = (char *)data_iterator_next(&iter);
  }
  if (best != 0)
    return best;

  {
    char *globals = *(char **)0x632574;
    int16_t count = *(int16_t *)(globals + 0x2c);
    int16_t best_idx = -1;
    int best_time = -1;
    int i;
    char *slot = globals + 0x34;

    for (i = 0; i < count; i++, slot += 0x10) {
      if (*(int16_t *)(slot - 4) == conversation_index) {
        int t = *(int *)slot;
        if (t > best_time) {
          best_time = t;
          best_idx = (int16_t)i;
        }
      }
    }
    if (best_idx == -1)
      return 0;
    {
      char *entry = globals + 0x34 + (int)best_idx * 0x10;
      if (entry[2] != 0)
        return 5;
      return (entry[3] != 0) ? 6 : 7;
    }
  }
}

void ai_conversation_finish(int handle, char param_b, char param_c)
{
  char *conversation;
  char *def;
  int i;
  int count;

  if (handle == -1)
    return;
  conversation =
      (char *)datum_get(*(data_t **)0x6324ec, handle);
  def = (char *)tag_block_get_element(
      (char *)global_scenario_get() + 0x468, 0x74,
      *(int16_t *)(conversation + 2));
  if (*(char *)0x5aca5f != 0) {
    const char *msg_b = param_b ? (char *)0x259af4 : (char *)0x25386f;
    const char *msg_c = param_c ? (char *)0x259ae4 : (char *)0x259ad8;
    console_printf(0, (char *)0x259ac4, def, msg_c, msg_b);
  }
  {
    char *globals = *(char **)0x632574;
    int16_t slot = *(int16_t *)(globals + 0x2e);
    int16_t next = (int16_t)(slot + 1);
    *(int16_t *)(globals + 0x2e) = next;
    slot = *(int16_t *)(globals + 0x2e);
    slot = (int16_t)((slot & 0x8000000f) == 0 ? slot & 0xf : (slot - 1) | 0xfffffff0);
    *(int16_t *)(globals + 0x2e) = slot;
    {
      int16_t queue_count = *(int16_t *)(globals + 0x2c);
      int16_t idx = *(int16_t *)(globals + 0x2e);
      if (queue_count <= idx)
        queue_count = (int16_t)(idx + 1);
      *(int16_t *)(globals + 0x2c) = queue_count;
      *(int16_t *)(globals + 0x34 + (int)idx * 0x10) =
          *(int16_t *)(conversation + 2);
      *(char *)(globals + 0x34 + (int)idx * 0x10 + 2) = param_b;
      *(char *)(globals + 0x34 + (int)idx * 0x10 + 3) = param_c;
      *(int *)(globals + 0x34 + (int)idx * 0x10 + 4) = game_time_get();
    }
  }
  count = *(int *)(def + 0x50);
  for (i = 0; i < count; i++) {
    if ((*(int *)(conversation + 0x14) & (1 << i)) != 0) {
      int actor = *(int *)(conversation + 0x28 + i * 4);
      if (actor != -1) {
        char *actor_data =
            (char *)datum_get(*(data_t **)0x6325a4, actor);
        *(int *)(actor_data + 0x1dc) = -1;
        *(int *)(actor_data + 0x1e0) = -1;
        if (*(int16_t *)(actor_data + 0x6c) == 0xc)
          *(int *)(actor_data + 0x9c) = -1;
      }
    }
  }
  datum_delete(*(data_t **)0x6324ec, handle);
}

int FUN_00043740(int16_t conversation_index, char allow_finish)
{
  int handle = data_new_at_index(*(data_t **)0x6324ec);
  char *conversation;

  if (handle != -1)
    goto init;
  if (!allow_finish)
    return handle;

  {
    data_iter_t iter;
    char *best = NULL;
    int best_handle = 0x7fffffff;
    int best_datum = -1;

    data_iterator_new(&iter, *(data_t **)0x6324ec);
    conversation = (char *)data_iterator_next(&iter);
    while (conversation != NULL) {
      if (conversation[4] >= *(char *)(best ? best : conversation + 4) &&
          *(int *)(conversation + 0xc) < best_handle) {
        best_handle = *(int *)(conversation + 0xc);
        best_datum = iter.datum_handle;
        best = conversation;
      }
      conversation = (char *)data_iterator_next(&iter);
    }
    if (best_datum == -1)
      return -1;
    if (*(char *)0x5aca5f != 0) {
      console_printf(
          0, (char *)0x259b08,
          tag_block_get_element((char *)global_scenario_get() + 0x468, 0x74,
                                conversation_index));
    }
    ai_conversation_finish(best_datum, 0, 0);
    handle = data_new_datum(*(data_t **)0x6324ec, best_datum);
    if (handle == -1)
      return -1;
  }
init:
  conversation =
      (char *)datum_get(*(data_t **)0x6324ec, handle);
  *(int16_t *)(conversation + 2) = conversation_index;
  *(int16_t *)(conversation + 0x48) = -1;
  conversation[4] = allow_finish;
  *(int *)(conversation + 0xc) = game_time_get();
  return handle;
}

char ai_conversation_line_begin(int conversation_handle)
{
  char *conversation;
  char *def;
  char *line_def;
  int16_t line_index;

  conversation = (char *)datum_get(*(data_t **)0x6324ec, conversation_handle);
  def = (char *)tag_block_get_element(
      (char *)global_scenario_get() + 0x468, 0x74,
      *(int16_t *)(conversation + 2));
  line_index = *(int16_t *)(conversation + 0x48);
  line_def = (char *)tag_block_get_element(def + 0x5c, 0x7c, (int)line_index);
  if (*(int16_t *)(line_def + 2) < 0)
    return 0;
  if (*(int *)(def + 0x50) <= *(int16_t *)(line_def + 2))
    return 0;
  if ((*(int *)(conversation + 0x14) & (1 << *(int16_t *)(line_def + 2))) == 0)
    return 0;
  {
    char *participant =
        (char *)tag_block_get_element(def + 0x50, 0x54,
                                      *(int16_t *)(line_def + 2));
    int actor = *(int *)(conversation + 0x28 +
                         *(int16_t *)(line_def + 2) * 4);
    *(int16_t *)(conversation + 0x4a) = *(int16_t *)(line_def + 2);
    if (actor == -1) {
      *(int *)(conversation + 0x50) = -1;
      *(int *)(conversation + 0x54) = -1;
      *(int *)(conversation + 0x58) = -1;
      conversation[0x60] = 1;
    } else {
      char *actor_data = (char *)datum_get(*(data_t **)0x6325a4, actor);
      *(int *)(conversation + 0x50) = actor;
      *(int *)(conversation + 0x54) = *(int *)(actor_data + 0x18);
      *(int *)(conversation + 0x58) = -1;
      if (*(int16_t *)(line_def + 4) == 1)
        *(int *)(conversation + 0x58) = *(int *)(conversation + 0x10);
      else if (*(int16_t *)(line_def + 4) == 2 &&
                 *(int16_t *)(line_def + 6) >= 0 &&
                 *(int16_t *)(line_def + 6) < *(int *)(def + 0x50)) {
        int h = *(int *)(conversation + 0x28 + *(int16_t *)(line_def + 6) * 4);
        if (h != -1) {
          char *a2 = (char *)datum_get(*(data_t **)0x6325a4, h);
          *(int *)(conversation + 0x58) = *(int *)(a2 + 0x18);
        }
      }
      {
        int16_t line_type = *(int16_t *)(participant + 4);
        conversation[0x60] = (line_type == 6 || line_type == 7);
      }
    }
    if (*(int16_t *)(conversation + *(int16_t *)(line_def + 2) * 2 + 0x18) < 0 ||
        *(int16_t *)(conversation + *(int16_t *)(line_def + 2) * 2 + 0x18) >= 6) {
      display_assert((char *)0x259b50,
                     "c:\\halo\\SOURCE\\ai\\ai_communication.c", 0x146b, 1);
      system_exit(-1);
    }
    *(int *)(conversation + 0x5c) =
        *(int *)(line_def + 0x28 +
                 *(int16_t *)(conversation +
                              *(int16_t *)(line_def + 2) * 2 + 0x18) *
                     0x10);
    *(int16_t *)(conversation + 0x4c) = ftol2(
        *(float *)(line_def + 0xc) * *(float *)0x253394);
    *(int16_t *)(conversation + 0x4e) = *(int16_t *)line_def;
    conversation[0x63] = 0;
    conversation[0x62] = 0;
    conversation[0x61] = 0;
    return 1;
  }
}

char FUN_00043a20(int conversation_handle)
{
  char *conversation;
  char *def;
  char comm_buf[0x40];
  short impulse;
  int i;

  conversation = (char *)datum_get(*(data_t **)0x6324ec, conversation_handle);
  def = (char *)tag_block_get_element(
      (char *)global_scenario_get() + 0x468, 0x74,
      *(int16_t *)(conversation + 2));
  if (conversation[0x63])
    return conversation[0x63];
  if (conversation[0x61])
    goto wait_line;
  if (*(int *)(conversation + 0x5c) == -1)
    goto mark_started;
  if ((*(uint8_t *)(conversation + 0x4e) & 0x30) != 0) {
    int count = *(int *)(def + 0x50);
    char found = 0;
    for (i = 0; i < count; i++) {
      int actor = *(int *)(conversation + 0x28 + i * 4);
      if (actor == -1)
        continue;
      {
        char *actor_data = (char *)datum_get(*(data_t **)0x6325a4, actor);
        if ((*(uint8_t *)(conversation + 0x4e) & 0x20) &&
            actor == *(int *)(conversation + 0x50))
          found = 1;
        else if ((*(uint8_t *)(conversation + 0x4e) & 0x10) &&
                 *(int16_t *)(actor_data + 0x6c) == 0xc &&
                 *(int *)(actor_data + 0xa8) != -1 &&
                 actor_data[0xa1] == 0 && actor_data[0xa0] == 0)
          found = 1;
      }
    }
    if (found)
      goto mark_started;
  }
  if (sound_scripted_dialog_is_playing())
    return conversation[0x63];
  if (*(int *)(conversation + 0x54) != -1 && !conversation[0x60]) {
    csmemset(comm_buf, 0, 0x30);
    *(int16_t *)(comm_buf + 2) = -1;
    *(int16_t *)(comm_buf + 0x14) = -1;
    *(int16_t *)(comm_buf + 0x18) = -1;
    *(int16_t *)(comm_buf + 0x16) = -1;
    *(int *)(comm_buf + 0x10) = *(int *)(conversation + 0x58);
    *(int16_t *)comm_buf = 6;
    *(int *)(comm_buf + 4) = *(int *)(conversation + 0x5c);
    *(int16_t *)(comm_buf + 0x1c) = 1;
    *(int16_t *)(comm_buf + 0x1e) = 1;
    *(int *)(comm_buf + 0x20) = *(int *)(conversation + 0x54);
    if (*(char *)0x5aca5f != 0) {
      console_printf(0, (char *)0x259c08, def,
                     tag_get_name(*(int *)(conversation + 0x5c)));
    }
    {
      short vocal = 6;
      int sound = 0;
      impulse = FUN_001a68d0(*(int *)(conversation + 0x54), 1, 0, 0, NULL,
                             &vocal, &sound);
    }
    if (impulse > 1) {
      FUN_001a6ef0(impulse, 1, comm_buf);
      conversation[0x61] = 1;
      conversation[5] = 1;
      return conversation[0x63];
    }
  } else {
    scripted_sound_new(*(int *)(conversation + 0x5c), -1, 1.0f);
    conversation[0x61] = 1;
    conversation[5] = 1;
    return conversation[0x63];
  }
mark_started:
  conversation[0x61] = 1;
  conversation[5] = 1;
  return conversation[0x63];
wait_line:
  if (*(int *)(conversation + 0x54) == -1) {
    if (*(int *)(conversation + 0x5c) == -1 ||
        scripted_sound_time(*(int *)(conversation + 0x5c)) == 0)
      conversation[0x62] = 0;
    else
      conversation[0x62] = 1;
  } else {
    char *obj = (char *)object_get_and_verify_type(*(int *)(conversation + 0x54), 3);
    conversation[0x62] = *(int16_t *)(obj + 0x338) != 6;
  }
  if (!conversation[0x62])
    return conversation[0x63];
  if (*(int16_t *)(conversation + 0x4c) > 0) {
    *(int16_t *)(conversation + 0x4c) = (int16_t)(*(int16_t *)(conversation + 0x4c) - 1);
    return conversation[0x63];
  }
  if ((*(uint8_t *)(conversation + 0x4e) & 8) == 0)
    return conversation[0x63];
  if (!conversation[8])
    conversation[8] = 1, conversation[9] = 0;
  if (conversation[9]) {
    conversation[8] = 0;
    return conversation[0x63];
  }
  conversation[0x63] = 0;
  return conversation[0x63];
}

void FUN_00043ce0(int actor)
{
  char *actor_data;
  char *tag;
  char is_player;
  float range;
  int16_t delay;

  actor_data = (char *)datum_get(*(data_t **)0x6325a4, actor);
  tag = (char *)tag_get(0x61637472, *(int *)(actor_data + 0x58));
  is_player = FUN_0003b120(actor);
  delay = 0;
  if (*(int *)(actor_data + 0x18) != -1) {
    char *unit = (char *)object_get_and_verify_type(*(int *)(actor_data + 0x18), 3);
    if (*(int16_t *)(unit + 0x338) > 0)
      delay = *(int16_t *)(unit + 0x3aa);
  }
  if (is_player) {
    range = random_real_range(get_global_random_seed_address(),
                              *(float *)(tag + 0x400), *(float *)(tag + 0x404));
  } else {
    range = random_real_range(get_global_random_seed_address(),
                              *(float *)(tag + 0x3f8), *(float *)(tag + 0x3fc));
  }
  actor_data[0x6cc] = is_player;
  *(int16_t *)(actor_data + 0x6ce) =
      ftol2(range * *(float *)0x253394 + (float)delay);
}

void actor_communication_update(int actor_handle)
{
  char comm_buf[0x38];
  char *actor_data;
  char is_player;
  short impulse;

  actor_data = (char *)datum_get(*(data_t **)0x6325a4, actor_handle);
  if (*(int16_t *)(actor_data + 0x6a) < 2)
    return;
  if (*(char *)(*(char **)0x632574 + 0x10) == 0)
    return;
  is_player = FUN_0003b120(actor_handle);
  if (*(int16_t *)(actor_data + 0x6ce) != 0 &&
      actor_data[0x6cc] == is_player)
    return;
  if (*(int16_t *)(actor_data + 0x6ce) > 0) {
    *(int16_t *)(actor_data + 0x6ce) = (int16_t)(*(int16_t *)(actor_data + 0x6ce) - 1);
    if (*(int16_t *)(actor_data + 0x6ce) != 0)
      return;
  }
  FUN_00043ce0(actor_handle);
  {
    short vocal = 1;
    int sound = 0;
    impulse = FUN_001a68d0(*(int *)(actor_data + 0x18), 1, 1, 0, NULL, &vocal,
                           &sound);
  }
  if (impulse <= 0)
    return;
  csmemset(comm_buf, 0, 0x30);
  ai_communication_packet_new(comm_buf);
  *(int16_t *)(comm_buf + 2) = is_player;
  *(int *)(comm_buf + 4) = -1;
  FUN_001a6ef0(impulse, 1, comm_buf);
}

void FUN_00043ea0(void *comm, int actor, int stack_a)
{
  if (*(int16_t *)((char *)comm + 0xe) <= 0)
    return;
  {
    char *prop = (char *)datum_get(*(data_t **)0x5ab23c, actor);
    int mode = (*(int16_t *)((char *)comm + 0xe) == 1 &&
                *(int *)((char *)comm + 0x10) == *(int *)(prop + 0x18))
                   ? 8
                   : 9;
    if (*(int16_t *)((char *)comm + 0xe) == 1)
      FUN_000432b0(-1, *(int *)((char *)comm + 0x10), stack_a, mode,
                   *(int16_t *)((char *)comm + 0xc));
    else if (*(int16_t *)((char *)comm + 0xe) == 2)
      FUN_00043360(*(int *)((char *)comm + 0x10),
                   *(int16_t *)((char *)comm + 0xc), stack_a, mode);
  }
}


void ai_communication_update_speech_timers(int unit, int16_t type, int a,
                                           int16_t dialogue_index,
                                           int16_t reply_index)
{
  char *unit_obj;
  char *actor_data = NULL;
  int now;
  int team;
  int base_time;

  unit_obj = (char *)object_get_and_verify_type(unit, 3);
  if (*(int *)(unit_obj + 0x1a4) != -1)
    actor_data = (char *)datum_get(*(data_t **)0x6325a4, *(int *)(unit_obj + 0x1a4));
  now = game_time_get();
  base_time = now + (((int)*(int16_t *)(unit_obj + 0x3aa) - 0x2d) < 0 ? -1 : 0) &
                      ((int)*(int16_t *)(unit_obj + 0x3aa) - 0x2d);
  *(int *)(unit_obj + 0x3a0) = base_time;
  if (!actor_data)
    return;
  if (*(int *)(unit_obj + 0x1a4) != -1)
    FUN_00043ce0(*(int *)(unit_obj + 0x1a4));
  team = FUN_0003a770(*(int16_t *)(actor_data + 4));
  team = (team & 2) ? 0 : ((team & 4) ? 1 : -1);
  if (type <= 5) {
    char *globals = *(char **)0x632574;
    int *slot = (int *)(globals + team * 4 + 0x14);
    if (*slot <= now)
      *slot = now;
    if (type >= 3) {
      slot = (int *)(globals + team * 4 + 0x1c);
      if (*slot <= now)
        *slot = now;
    }
    if (type >= 5) {
      slot = (int *)(globals + team * 4 + 0x24);
      if (*slot <= now)
        *slot = now;
    }
    if (*(char *)0x5aca54 != 0) {
      error(2, (char *)0x259cbc, FUN_001a6ca0(type), FUN_001a67b0(type, 1),
            *(const char **)(0x2c8d68 + team * 8), now - base_time);
    }
  }
  if (dialogue_index != -1) {
    if (dialogue_index < 0 || dialogue_index >= *(int16_t *)0x331f08) {
      display_assert((char *)0x259c68,
                     "c:\\halo\\SOURCE\\ai\\ai_communication.c", 0xc9c, 1);
      system_exit(-1);
    }
    {
      char *entry = (char *)(*(char **)0x331f0c +
                             ((team + dialogue_index * 2) * 8));
      char *dialogue = (char *)(0x257e48 + dialogue_index * 0x28);
      *(int *)entry = base_time;
      if (!game_connection() && *(char *)0x5aca46 == 0 &&
          *(float *)(dialogue + 0x14) <= *(float *)0x2533c0)
        *(int *)(entry + 4) =
            ftol2(*(float *)(dialogue + 0x14) * *(float *)0x253394 +
                  (float)base_time);
    }
  }
  if (reply_index != -1) {
    if (reply_index < 0 || reply_index >= *(int16_t *)0x331f10) {
      display_assert((char *)0x259c18,
                     "c:\\halo\\SOURCE\\ai\\ai_communication.c", 0xcaf, 1);
      system_exit(-1);
    }
    {
      char *entry = (char *)(*(char **)0x331f14 +
                             ((team + reply_index * 2) * 8));
      char *reply = (char *)(0x258eb0 + reply_index * 0x24);
      *(int *)entry = base_time;
      if (!game_connection() && *(char *)0x5aca46 == 0 &&
          *(float *)(reply + 0x1c) <= *(float *)0x2533c0)
        *(int *)(entry + 4) =
            ftol2(*(float *)(reply + 0x1c) * *(float *)0x253394 +
                  (float)base_time);
    }
  }
}

float ai_communication_get_player_rating(int unit, char use_teams, int *out_unit,
                                         int *out_handle)
{
  float pos[3];
  data_iter_t iter;
  char *player;
  float best_rating = *(float *)0x2533c8;
  int best_unit = -1;
  int best_handle = -1;
  char found = 0;

  unit_get_head_position(unit, pos);
  data_iterator_new(&iter, *(data_t **)0x5aa6d4);
  player = (char *)data_iterator_next(&iter);
  while (player != NULL) {
    if (*(int *)(player + 0x34) != -1) {
      float other[3];
      float delta[3];
      float dist_sq;
      float rating;
      char blocked;
      unit_get_head_position(*(int *)(player + 0x34), other);
      delta[0] = pos[0] - other[0];
      delta[1] = pos[1] - other[1];
      delta[2] = pos[2] - other[2];
      dist_sq = delta[0] * delta[0] + delta[1] * delta[1] + delta[2] * delta[2];
      if (dist_sq <= *(float *)0x257e34 * *(float *)0x257e34) {
        if (use_teams) {
          char *root_a;
          char *root_b;
          int16_t team_a;
          int16_t team_b;
          root_a = (char *)object_get_and_verify_type(
              object_get_root_parent(unit), -1);
          team_a = *(int16_t *)(root_a + 0x4c);
          root_b = (char *)object_get_and_verify_type(
              object_get_root_parent(*(int *)(player + 0x34)), -1);
          team_b = *(int16_t *)(root_b + 0x4c);
          if (team_a != -1 && team_b != -1 &&
              !scenario_ensure_point_within_world(team_b, team_a))
            goto next_player;
        }
        blocked = 0;
        {
          int16_t collision[40];
          int depth;
          if (*(volatile int16_t *)0x4761d8 >= 0x20) {
            display_assert((char *)0x253440,
                           "c:\\halo\\SOURCE\\ai\\ai_communication.c", 0xe91,
                           1);
            system_exit(-1);
          }
          depth = *(volatile short *)0x4761d8;
          *(int16_t *)(0x5a8c80 + depth * 2) = 3;
          *(volatile short *)0x4761d8 = depth + 1;
          blocked = FUN_0014df70(0x27, pos, delta, -1, collision);
          if (*(volatile short *)0x4761d8 <= 1) {
            display_assert((char *)0x253418,
                           "c:\\halo\\SOURCE\\ai\\ai_communication.c", 0xe97,
                           1);
            system_exit(-1);
          }
          *(volatile short *)0x4761d8 = (short)(depth);
          if (dist_sq > *(float *)0x257e38 * *(float *)0x257e38 && blocked)
            goto next_player;
        }
        {
          float dist = sqrtf(dist_sq);
          rating = *(float *)0x2533c8;
          if (dist <= *(float *)0x257e3c)
            rating = *(float *)0x253f40;
          else
            rating = *(float *)0x2533c8 +
                     (dist - *(float *)0x257e38) /
                         (*(float *)0x257e3c - *(float *)0x257e38);
          if (blocked)
            rating += *(float *)0x253398;
          if (dist <= *(float *)0x253f44) {
            float driver[3];
            unit_scripting_unit_driver(*(int *)(player + 0x34), driver);
            rating += (driver[0] * delta[0] + driver[1] * delta[1] +
                       driver[2] * delta[2]) /
                          dist;
            if (rating <= *(float *)0x257e40)
              rating = *(float *)0x2533c8 -
                       (rating - *(float *)0x257e40) /
                           (*(float *)0x2533c8 - *(float *)0x257e40) *
                           *(float *)0x259cd0;
          }
          if (rating <= best_rating) {
            best_rating = rating;
            best_unit = *(int *)(player + 0x34);
            best_handle = dist_sq;
            found = 1;
          }
        }
      }
    }
  next_player:
    player = (char *)data_iterator_next(&iter);
  }
  if (!found)
    return *(float *)0x2533c8;
  if (out_handle)
    *out_handle = best_handle;
  if (out_unit)
    *out_unit = best_unit;
  return best_rating;
}

void ai_conversation_unit_died(int unit_handle, char param_2)
{
  data_iter_t iter;
  char *conversation;

  data_iterator_new(&iter, *(data_t **)0x6324ec);
  conversation = (char *)data_iterator_next(&iter);
  while (conversation != NULL) {
    char *def = (char *)tag_block_get_element(
        (char *)global_scenario_get() + 0x468, 0x74,
        *(int16_t *)(conversation + 2));
    char changed = 0;
    if (*(int *)(conversation + 0x54) == unit_handle) {
      changed = 1;
      conversation[0x63] = 1;
      *(int *)(conversation + 0x54) = -1;
    }
    if (*(int *)(conversation + 0x58) == unit_handle)
      changed = 1, *(int *)(conversation + 0x58) = -1;
    if (*(int *)(conversation + 0x10) == unit_handle)
      changed = 1, *(int *)(conversation + 0x10) = -1;
    if (!param_2 && (*(uint8_t *)(def + 0x20) & 1) == 0) {
      int i;
      int count = *(int *)(def + 0x50);
      for (i = 0; i < count; i++) {
        if ((*(int *)(conversation + 0x14) & (1 << i)) != 0 &&
            *(int *)(conversation + 0x28 + i * 4) != -1) {
          char *actor_data = (char *)datum_get(
              *(data_t **)0x6325a4, *(int *)(conversation + 0x28 + i * 4));
          if (*(int *)(actor_data + 0x18) == unit_handle)
            changed = 1;
          if (param_2 && *(int16_t *)(actor_data + 0x6c) == 0xc &&
              *(int *)(actor_data + 0xa8) == unit_handle)
            *(int *)(actor_data + 0xa8) = -1;
          if (param_2 && *(int *)(actor_data + 0x1e0) == unit_handle)
            *(int *)(actor_data + 0x1e0) = -1;
        }
      }
    }
    if (changed && !param_2 && (*(uint8_t *)(def + 0x20) & 1) != 0) {
      if (*(char *)0x5aca5f != 0)
        console_printf(0, (char *)0x259cf4, def);
      ai_conversation_finish(iter.datum_handle, 0, 0);
      break;
    }
    conversation = (char *)data_iterator_next(&iter);
  }
}


void ai_conversation_find_participant(int conversation_handle,
                                     int16_t participant_index, char *found_out,
                                     char *required_out, float *rating_out,
                                     int *handle_out)
{
  char *conversation;
  char *def;
  char *participant;
  int16_t type;

  conversation = (char *)datum_get(*(data_t **)0x6324ec, conversation_handle);
  def = (char *)tag_block_get_element(
      (char *)global_scenario_get() + 0x468, 0x74,
      *(int16_t *)(conversation + 2));
  participant = (char *)tag_block_get_element(def + 0x50, 0x54,
                                              (int)participant_index);
  if (!def) {
    display_assert((char *)0x259f04,
                   "c:\\halo\\SOURCE\\ai\\ai_communication.c", 0x127a, 1);
    system_exit(-1);
  }
  if (*(int16_t *)(participant + 4) == 1) {
    if (required_out)
      *required_out = 1;
    *(int *)(conversation + 0x14) |= (1 << participant_index);
    *(int *)(conversation + 0x28 + participant_index * 4) = -1;
    *(int16_t *)(conversation + participant_index * 2 + 0x18) = 0;
    if (handle_out)
      *handle_out = -1;
    return;
  }
  if (found_out)
    *found_out = 0;
  if (required_out)
    *required_out = 0;
  type = *(int16_t *)(participant + 4);
  if (type == 6 || type == 7) {
    int i;
    int count = *(int *)(def + 0x50);
    for (i = 0; i < count; i++) {
      int actor = *(int *)(conversation + 0x28 + i * 4);
      if (actor != -1) {
        char *actor_data = (char *)datum_get(*(data_t **)0x6325a4, actor);
        float pos[3];
        *(float *)(pos + 0) = *(float *)(actor_data + 0x12c);
        *(float *)(pos + 1) = *(float *)(actor_data + 0x130);
        *(float *)(pos + 2) = *(float *)(actor_data + 0x134);
      }
    }
  }
  if (rating_out)
    *rating_out = *(float *)0x7f7fffff;
  if (handle_out)
    *handle_out = -1;
}

void FUN_00044fd0(int unit_handle, uint16_t priority, uint16_t type,
                  void *comm_data)
{
  if (type <= 0xa) {
    static void *dispatch[11];
    (void)dispatch;
  }
  if (*(char *)0x5aca51 == 0)
    return;
  ai_communication_packet_new(comm_data);
  FUN_001a6ef0(unit_handle, (short)priority, comm_data);
}

void FUN_00045290(int unit_handle, uint16_t priority, uint16_t type,
                  void *comm_data)
{
  (void)unit_handle;
  (void)priority;
  (void)type;
  ai_communication_packet_new(comm_data);
}

void FUN_000454a0(int actor, int stack_a, float *pos, int stack_c, float radius,
                  float rating, int16_t anim_a, int16_t anim_b, int stack_d,
                  int stack_e, char flags)
{
  char *actor_data;
  char has_target;
  char has_unit;
  float threshold = 10.0f;

  actor_data = (char *)datum_get(*(data_t **)0x6325a4, stack_a);
  has_target = (actor != -1 || stack_c != -1);
  has_unit = (*(int *)(actor_data + 0x18) != -1);
  if (*(int16_t *)(actor_data + 0x6a) <= 1 || !has_unit)
    return;
  if (has_target && actor != -1 && pos) {
    float dx = pos[0] - *(float *)(actor_data + 0x120);
    float dy = pos[1] - *(float *)(actor_data + 0x124);
    float dz = pos[2] - *(float *)(actor_data + 0x128);
    if (dx * dx + dy * dy + dz * dz > radius * radius) {
      if (stack_c == -1 ||
          distance_squared3d(pos, (float *)(actor_data + 0x120)) >
              radius * radius)
        return;
    }
  }
  if ((flags & 2) != 0) {
    float r = ai_communication_get_player_rating(*(int *)(actor_data + 0x18), 0,
                                                 NULL, NULL);
    if (r <= *(float *)0x2533c0)
      return;
    threshold = r * *(float *)0x254cc4 + *(float *)0x253f34;
  }
  if ((flags & 4) != 0 && actor != -1) {
    char *obj = (char *)object_get_and_verify_type(actor, 3);
    if (*(int *)(obj + 0xcc) != *(int *)(actor_data + 0x158))
      return;
  }
  if (anim_a != -1 &&
      !unit_test_animation_impulse(*(int *)(actor_data + 0x18), anim_a))
    anim_a = -1;
  if (anim_b != -1) {
    char buf[0x20];
    int16_t result = ai_communication_consider_speech(
        buf, *(int *)(actor_data + 0x18), stack_d, stack_e, anim_b, 0, 0, 1,
        &threshold, NULL);
    if (result == 0)
      return;
  }
  (void)stack_a;
  (void)rating;
  (void)anim_a;
}

int FUN_00045830(int type, int unit, int actor, int target, int16_t subtype,
                 int16_t index, float max_dist)
{
  short look_buf[4];
  (void)max_dist;
  if (unit == -1 || actor == -1 || target == -1)
    return -1;
  if (!object_try_and_get_and_verify_type(target, 3))
    return -1;
  {
    char *prop = (char *)datum_get(*(data_t **)0x5ab23c, actor);
    if (*(int16_t *)(prop + 0x24) >= 2 && *(int16_t *)(prop + 0x24) <= 3) {
      look_buf[0] = 1;
      *(int *)&look_buf[1] = actor;
    } else {
      look_buf[0] = 3;
      *(int *)&look_buf[1] = target;
      unit_get_head_position(target, (float *)&look_buf[1]);
    }
  }
  FUN_00027a60(unit, subtype, 5, look_buf);
  return actor;
}

int ai_communication_find_global_actor_to_talk(
    int comm_type, int unit, int16_t subtype, int16_t index, int stack_a,
    int stack_b, float max_dist, int mode)
{
  data_iter_t iter;
  char *actor;
  int best = -1;
  float best_rating = *(float *)0x7f7fffff;

  data_iterator_new(&iter, *(data_t **)0x6325a4);
  actor = (char *)data_iterator_next(&iter);
  while (actor != NULL) {
    if (*(int16_t *)(actor + 4) == subtype) {
      float rating;
      int handle;
      rating = ai_communication_get_player_rating(*(int *)(actor + 0x18), 1,
                                                 &handle, NULL);
      if (rating < best_rating) {
        best_rating = rating;
        best = iter.datum_handle;
      }
    }
    actor = (char *)data_iterator_next(&iter);
  }
  (void)comm_type;
  (void)unit;
  (void)index;
  (void)stack_a;
  (void)stack_b;
  (void)max_dist;
  (void)mode;
  return best;
}

char ai_conversation_begin(int conversation_handle, char *flag_out)
{
  char *conversation;
  char *def;
  int i;
  int count;
  int mask = 0;

  conversation = (char *)datum_get(*(data_t **)0x6324ec, conversation_handle);
  def = (char *)tag_block_get_element(
      (char *)global_scenario_get() + 0x468, 0x74,
      *(int16_t *)(conversation + 2));
  csmemset(conversation + 0x28, -1, 0x20);
  csmemset(conversation + 0x18, -1, 0x10);
  *(int *)(conversation + 0x14) = 0;
  count = *(int *)(def + 0x50);
  for (i = 0; i < count; i++) {
    char found = 0;
    char required = 0;
    float rating;
    int handle;
    ai_conversation_find_participant(conversation_handle, (int16_t)i, &found,
                                    &required, &rating, &handle);
    if (found)
      mask |= (1 << i);
    else if (required)
      mask &= ~(1 << i);
  }
  if (flag_out)
    *flag_out = 0;
  if (mask == 0)
    return 0;
  *(int *)(conversation + 0x14) = mask;
  conversation[6] = 1;
  ai_conversation_line_begin(conversation_handle);
  return 1;
}

void FUN_000460e0(int actor, int stack_a, float *pos, int stack_c, float radius,
                  float rating, int16_t anim_a, int16_t anim_b, int stack_d,
                  int stack_e, char flags)
{
  FUN_000454a0(actor, stack_a, pos, stack_c, radius, rating, anim_a, anim_b,
               stack_d, stack_e, flags);
}

void FUN_00046530(int unit_handle, uint16_t priority, uint16_t type, int unk,
                  int unk2, void *comm_data)
{
  FUN_00044fd0(unit_handle, priority, type, comm_data);
  (void)unk;
  (void)unk2;
}

char FUN_00046b60(int16_t conversation_index, char allow_finish)
{
  void *scenario = global_scenario_get();
  if (conversation_index < 0 ||
      conversation_index >= *(int *)((char *)scenario + 0x468))
    return 0;
  {
    int handle = FUN_00043740(conversation_index, allow_finish);
    char flag = 0;
    if (*(char *)0x5aca5f != 0) {
      console_printf(
          0, (char *)0x25a3b8,
          tag_block_get_element((char *)scenario + 0x468, 0x74,
                                (int)conversation_index));
    }
    if (handle == -1) {
      error(2, (char *)0x25a360);
      return 0;
    }
    if (ai_conversation_begin(handle, &flag))
      return 1;
    if (flag)
      return 1;
    if (*(char *)0x5aca5f != 0)
      console_printf(
          0, (char *)0x25a308,
          tag_block_get_element((char *)scenario + 0x468, 0x74,
                                (int)conversation_index));
    ai_conversation_finish(handle, 0, 1);
    return 0;
  }
}

void ai_conversation_update(void)
{
  data_iter_t iter;
  char *conversation;
  int now = game_time_get();

  data_iterator_new(&iter, *(data_t **)0x6324ec);
  conversation = (char *)data_iterator_next(&iter);
  while (conversation != NULL) {
    if (conversation[5]) {
      if (*(int16_t *)(conversation + 0x4c) > 0)
        *(int16_t *)(conversation + 0x4c) =
            (int16_t)(*(int16_t *)(conversation + 0x4c) - 1);
      else
        FUN_00043a20(iter.datum_handle);
    }
    if (*(int *)(conversation + 0xc) != 0 &&
        now - *(int *)(conversation + 0xc) > 0x708) {
      ai_conversation_finish(iter.datum_handle, 0, 0);
    }
    conversation = (char *)data_iterator_next(&iter);
  }
}

void FUN_00046f10(int16_t type, int unit_handle, int param3, int param4,
                  int16_t param5, int16_t param6, int16_t param7)
{
  char comm_buf[0x30];
  char *dialogue;
  int actor = -1;
  char *actor_data = NULL;

  if (type < 0 || type >= 0x39) {
    display_assert((char *)0x25a960, "c:\\halo\\SOURCE\\ai\\ai_communication.c",
                   0x34e, 1);
    system_exit(-1);
  }
  if (param5 == -1)
    param5 = 0;
  if (param6 == -1)
    param6 = 0;
  dialogue = (char *)(0x257e48 + (int)type * 0x28);
  if (unit_handle != -1) {
    char *unit = (char *)object_get_and_verify_type(unit_handle, 3);
    if (*(int *)(unit + 0x1a4) != -1) {
      actor = *(int *)(unit + 0x1a4);
      actor_data = (char *)datum_get(*(data_t **)0x6325a4, actor);
    }
  }
  csmemset(comm_buf, 0, 0x30);
  ai_communication_packet_new(comm_buf);
  *(int16_t *)comm_buf = type;
  if (actor_data)
    *(int *)(comm_buf + 4) = *(int *)(actor_data + 0x18);
  ai_communication_update_speech_timers(unit_handle, type, param3, param5,
                                        param6);
  if (actor != -1)
    FUN_00043ce0(actor);
  if (actor != -1 && actor_data) {
    short vocal = (short)type;
    int sound = param4;
    short impulse = FUN_001a68d0(*(int *)(actor_data + 0x18), 1, 0, 0, NULL,
                                 &vocal, &sound);
    if (impulse > 0)
      FUN_001a6ef0(impulse, 1, comm_buf);
  }
  (void)param7;
  (void)dialogue;
}
/* --- ai_communication.obj orphan shells (2026-07-26) --- */

/* orphan 0x48e90 */
void ai_debug_initialize(void)
{

}
