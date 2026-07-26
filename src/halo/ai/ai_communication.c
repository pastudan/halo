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
void ai_conversation_finish(int handle, int a, int b);
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
