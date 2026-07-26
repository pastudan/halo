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
  int16_t flags = FUN_0003a770(*(int16_t *)(actor_data + 4));

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
