#include <stdint.h>
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

/* ai_communication_initialize (0x42a30) — readable C lift from XBE.
 * Count dialogue/vocalization table entries, allocate scratch, build
 * type→index map at 0x632500, create conversation data array.
 */
void ai_communication_initialize(void)
{
  unsigned short count;
  unsigned short i;
  unsigned short dx;
  unsigned short ax;
  char *p;
  char *map;
  void *mem;
  data_t *data;

  count = 0;
  p = (char *)0x257e48;
  do {
    p += 0x28;
    count = (unsigned short)(count + 1);
  } while (*(short *)p != (short)-1);
  *(unsigned short *)0x331f08 = count;
  if (*(int *)0x331f0c == 0) {
    mem = game_state_malloc((const char *)0x2599dc, 0, (int)count << 4);
    *(void **)0x331f0c = mem;
    if (mem == 0) {
      display_assert((const char *)0x259968, (const char *)0x2599b4, 0x286, 1);
      system_exit(-1);
    }
  }

  count = 0;
  p = (char *)0x258eb0;
  do {
    p += 0x24;
    count = (unsigned short)(count + 1);
  } while (*(short *)p != (short)-1);
  *(unsigned short *)0x331f10 = count;
  if (*(int *)0x331f14 == 0) {
    mem = game_state_malloc((const char *)0x259948, 0, (int)count << 4);
    *(void **)0x331f14 = mem;
    if (mem == 0) {
      display_assert((const char *)0x259900, (const char *)0x2599b4, 0x293, 1);
      system_exit(-1);
    }
  }

  map = (char *)0x632500;
  for (i = 0; (short)i < 0x39; i++) {
    *(unsigned short *)map = 0xffff;
    p = (char *)0x257e48;
    dx = 0;
    ax = 0;
    for (;;) {
      if (ax == i) {
        *(unsigned short *)map = dx;
        break;
      }
      ax = *(unsigned short *)(p + 0x28);
      p += 0x28;
      dx = (unsigned short)(dx + 1);
      if (ax == 0xffff)
        break;
    }
    map += 2;
  }

  data = game_state_data_new((char *)0x2598f0, 8, 0x64);
  *(data_t **)0x6324ec = data;
  if (data == 0) {
    display_assert((const char *)0x2598dc, (const char *)0x2599b4, 0x2a8, 1);
    system_exit(-1);
  }
}

/* ai_communication_dispose: no-op stub.
 * Called from ai_dispose (0x3f6f0). Binary is a single RET instruction. */
void ai_communication_dispose(void)
{
}

/* ai_communication_initialize_for_new_map (0x42b90) — readable C lift from XBE leaf. */
void ai_communication_initialize_for_new_map(void)
{
  void *globals;
  int n;
  int i;
  int *table;

  globals = *(void **)0x632574;
  *((unsigned char *)globals + 0x10) = 1;
  csmemset((char *)globals + 0x14, 0, 8);
  csmemset((char *)globals + 0x1c, 0, 8);
  csmemset((char *)globals + 0x24, 0, 8);

  n = (int)*(short *)0x331f08 * 2;
  table = *(int **)0x331f0c;
  for (i = 0; i < n; i++) {
    table[i * 2 + 1] = -1;
    table[i * 2] = -1;
  }

  n = (int)*(short *)0x331f10 * 2;
  table = *(int **)0x331f14;
  for (i = 0; i < n; i++) {
    table[i * 2 + 1] = -1;
    table[i * 2] = -1;
  }

  *(short *)((char *)globals + 0x2c) = 0;
  *(short *)((char *)globals + 0x2e) = 0;
  csmemset((char *)globals + 0x30, 0, 0x100);
  data_delete_all(*(data_t **)0x6324ec);
}


/* ai_conversation_advance (0x43520) — readable C lift.
 * Marks matching conversation records to advance; optional debug print. */
void ai_conversation_advance(short param_1)
{
  data_iter_t iter;
  char *rec;
  void *elem;

  data_iterator_new(&iter, *(data_t **)0x6324ec);
  for (rec = (char *)data_iterator_next(&iter); rec != NULL;
       rec = (char *)data_iterator_next(&iter)) {
    if (*(int16_t *)(rec + 2) != param_1)
      continue;
    if (*(char *)0x5aca5f != 0) {
      elem = tag_block_get_element((char *)global_scenario_get() + 0x468,
                                  (int)param_1, 0x74);
      console_printf(0, (const char *)0x259aa0, elem);
    }
    rec[9] = 1;
  }
}

/* --- ai_communication.obj batch1 drafts (2026-07-26) --- */

char actor_is_fighting(int actor_handle);
char FUN_0003b120(int actor);
void ai_conversation_finish(int handle, char param_b, char param_c);
int FUN_00064b40(int actor_handle, int unit_handle, char create_if_needed,
                 char refresh_flag);
int16_t FUN_0003a770(int16_t actor_type);

const char *ai_communication_get_type_name(int16_t type)
{
  if (type >= 0 && type < 0x39)
    return *(const char **)((char *)0x2c8d78 + (int)type * 4);
  return (const char *)0x253b58;
}

/* ai_communication_get_type_by_name (0x42ce0) — readable C lift (ai campaign). */
int16_t ai_communication_get_type_by_name(const char *name)
{
  int16_t found = -1;
  const char **table = (const char **)0x2c8d78;
  for (int16_t i = 0; i < 0x39; i++) {
    if (csstrcmp(table[i], name) == 0)
      found = i;
  }
  return found;
}

/* ai_communication_packet_new (0x42d20) — readable C lift (assert wrapper). */
void ai_communication_packet_new(void *packet)
{
  if (packet == NULL) {
    display_assert((const char *)0x2599f8, (const char *)0x2599b4, 0x300, 1);
    system_exit(-1);
  }
  csmemset(packet, 0, 0x20);
  *(uint32_t *)((char *)packet + 0x0) = (uint32_t)0xffffffff;
  *(uint16_t *)((char *)packet + 0x4) = (uint16_t)0xffff;
  *(uint16_t *)((char *)packet + 0x6) = (uint16_t)0xffff;
  *(uint16_t *)((char *)packet + 0x8) = (uint16_t)0xffff;
}

/* FUN_00042d80 (0x42d80) — readable C lift. */
char FUN_00042d80(int actor, int unit, int prop)
{
  int handle;
  char *p;
  short w;

  (void)unit;
  if (prop == -1)
    return 0;
  handle = FUN_00064b40(prop, actor, 1, 1);
  if (handle == -1)
    return 0;
  p = (char *)datum_get(*(data_t **)0x5ab23c, handle);
  if (!(*(float *)(p + 0x11c) < *(float *)0x254cc4))
    return 0;
  w = *(short *)(p + 0x38);
  if (w == 0 || w == 1)
    return 1;
  return 0;
}
/* FUN_00042df0 (0x42df0) — readable C lift. */
char FUN_00042df0(int actor, int unit, int prop)
{
  int handle;
  char *p;
  short w;

  (void)unit;
  if (prop == -1)
    return 0;
  handle = FUN_00064b40(prop, actor, 1, 1);
  if (handle == -1)
    return 0;
  p = (char *)datum_get(*(data_t **)0x5ab23c, handle);
  if (!(*(float *)(p + 0x11c) <= *(float *)0x254cc4))
    return 1;
  w = *(short *)(p + 0x38);
  if (w == 0 || w == 1)
    return 0;
  return 1;
}


/* FUN_00042e60 (0x42e60) — readable C lift (ai campaign). */
char FUN_00042e60(int actor, int unit, int prop)
{
  (void)actor; (void)unit;
  if (prop == -1)
    return 0;
  void *p = datum_get(*(void **)0x6325a4, prop);
  int st = (int)*(int16_t *)((char *)p + 0x6c);
  if (st == 5)
    return *(int16_t *)((char *)p + 0xa4) == 1;
  if (st == 7)
    return 1;
  return 0;
}

/* FUN_00042eb0 (0x42eb0) — readable C lift. */
char FUN_00042eb0(int actor, int unit, int prop)
{
  void *obj;
  int other_actor;
  char *a;
  char *b;

  if (!FUN_00042d80(actor, unit, prop))
    return 0;
  obj = object_get_and_verify_type(actor, 3);
  other_actor = *(int *)((char *)obj + 0x1a4);
  if (other_actor == -1 || prop == -1)
    return 0;
  a = (char *)datum_get(*(data_t **)0x6325a4, other_actor);
  b = (char *)datum_get(*(data_t **)0x6325a4, prop);
  if (*(int *)(a + 0x34) == -1)
    return 0;
  if (*(int *)(a + 0x34) != *(int *)(b + 0x34))
    return 0;
  if (*(short *)(a + 0x3c) != *(short *)(b + 0x3c))
    return 0;
  return 1;
}
/* FUN_00042f40 (0x42f40) — readable C lift: thin wrapper. */
char FUN_00042f40(int a, int b, int actor)
{
  (void)a;
  (void)b;
  return actor_is_fighting(actor);
}

/* FUN_00042f60 (0x42f60) — readable C lift. */
char FUN_00042f60(int actor, int unit, int prop)
{
  if (!FUN_00042d80(actor, unit, prop))
    return 0;
  if (!actor_is_fighting(prop))
    return 0;
  return 1;
}

/* FUN_00042fa0 (0x42fa0) — readable C lift. */
char FUN_00042fa0(int actor, int unit, int prop)
{
  void *obj;
  int other_actor;
  char *a;
  char *b;
  int p1;
  int p2;
  char *prop1;
  char *prop2;

  if (!FUN_00042d80(actor, unit, prop))
    return 0;
  obj = object_get_and_verify_type(actor, 3);
  other_actor = *(int *)((char *)obj + 0x1a4);
  if (other_actor == -1 || prop == -1)
    return 0;
  a = (char *)datum_get(*(data_t **)0x6325a4, other_actor);
  b = (char *)datum_get(*(data_t **)0x6325a4, prop);
  p1 = *(int *)(a + 0x270);
  p2 = *(int *)(b + 0x270);
  if (p1 == -1 || p2 == -1)
    return 0;
  prop1 = (char *)datum_get(*(data_t **)0x5ab23c, p1);
  prop2 = (char *)datum_get(*(data_t **)0x5ab23c, p2);
  return (*(int *)(prop1 + 0x18) == *(int *)(prop2 + 0x18)) ? 1 : 0;
}
/* FUN_00043050 (0x43050) — readable C lift (ai campaign). */
char FUN_00043050(int actor, int unit, int prop)
{
  (void)actor; (void)unit;
  if (prop == -1)
    return 0;
  void *p = datum_get(*(void **)0x6325a4, prop);
  if (*(int16_t *)((char *)p + 0x6a) != 3)
    return 0;
  if (*(int16_t *)((char *)p + 0x6e) < 4)
    return 1;
  return 0;
}

/* FUN_00043090 (0x43090) — readable C lift (ai campaign). */
char FUN_00043090(int actor, int unit, int prop)
{
  (void)actor; (void)unit;
  if (!actor_is_fighting(prop))
    return 0;
  void *p = datum_get(*(void **)0x6325a4, prop);
  if (*(int16_t *)((char *)p + 4) == 0)
    return 1;
  return 0;
}

/* actor_communication_team (0x43270) — readable C lift (ai campaign). */
int actor_communication_team(int actor)
{
  void *a = datum_get(*(void **)0x6325a4, actor);
  unsigned short t = *(unsigned short *)((char *)a + 4);
  int flags = (int)(short)FUN_0003a770((short)t);
  if (flags & 2)
    return 0;
  if (flags & 4)
    return 1;
  return (flags & ~0xFFFF) | 0xFFFF;
}

/* ai_conversation_line (0x434c0) — readable C lift. */
int16_t ai_conversation_line(int conversation_index)
{
  data_iter_t iter;
  void *item;
  int16_t key = (int16_t)conversation_index;

  data_iterator_new(&iter, *(data_t **)0x6324ec);
  for (item = data_iterator_next(&iter); item; item = data_iterator_next(&iter)) {
    if (*(int16_t *)((char *)item + 2) == key)
      return *(int16_t *)((char *)item + 0x48);
  }
  return 0x3e7;
}
/* ai_conversation_stop (0x44500) — readable C lift. */
void ai_conversation_stop(int conversation_index)
{
  data_iter_t iter;
  char *rec;
  int16_t key = (int16_t)conversation_index;
  data_iterator_new(&iter, *(data_t **)0x6324ec);
  for (rec = (char *)data_iterator_next(&iter); rec; rec = (char *)data_iterator_next(&iter)) {
    if (*(int16_t *)(rec + 2) != key) continue;
    if (*(char *)0x5aca5f) {
      void *elem = tag_block_get_element((char *)global_scenario_get() + 0x468, key, 0x74);
      console_printf(0, (const char *)0x259cd4, elem);
    }
    ai_conversation_finish((int)iter.datum_handle, 0, 0);
  }
}



/* ai_conversation_actor_deleted (0x44590) — readable C lift. */
void ai_conversation_actor_deleted(int actor_handle)
{
  data_iter_t iter; char *rec; char *conv; int16_t i; int count;
  data_iterator_new(&iter, *(data_t **)0x6324ec);
  for (rec = (char *)data_iterator_next(&iter); rec; rec = (char *)data_iterator_next(&iter)) {
    conv = (char *)tag_block_get_element((char *)global_scenario_get() + 0x468, *(int16_t *)(rec + 2), 0x74);
    count = *(int *)(conv + 0x50);
    if (count <= 0) continue;
    for (i = 0; i < count; i++) {
      if (*(int *)(rec + 0x28 + (int)i * 4) != actor_handle) continue;
      if (conv[0x20] & 1) { ai_conversation_finish((int)iter.datum_handle, 0, 0); break; }
      *(int *)(rec + 0x14) &= ~(1 << i);
      *(int *)(rec + 0x28 + (int)i * 4) = -1;
      if (*(int16_t *)(rec + 0x4a) == 0) rec[0x63] = 1;
    }
  }
}


/* --- ai_communication.obj batch2 drafts (2026-07-26) --- */

#include "../../x87_math.h"

static __attribute__((unused)) short ftol2(float value)
{
  return (short)(int)value;
}

char actor_is_fighting(int actor_handle);
char FUN_0003b120(int actor);
int FUN_00064b40(int actor_handle, int unit_handle, char create_if_needed,
                 char refresh_flag);
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
    int talker /*@<edi>*/, int16_t team /*@<bx>*/, int16_t mode, int target,
    int p0, int p1, int p2, int p3, int p4, int p5, int p6);
int FUN_00045830(int type, int actor, int target, int p0, int p1, int p2,
                 int p3, int p4, int p5, int p6);

/* ai_communication_consider_speech (0x430d0) — readable C lift (restored pre-naked). */
int16_t ai_communication_consider_speech(void *packet /*  */, int unit /*  */, int param /*  */, int stack_a, int16_t dialogue_type, int16_t start_tick, int stack_b, char flag, float *timer, char *out_buf)
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
/* FUN_000432b0 (0x432b0) — readable C lift.
 * unit@ebx actor@eax target@edi; stack: look_arg, priority. */
void FUN_000432b0(int look_arg, short priority, int unit, int actor, int target)
{
  short buf[8];
  if (unit == -1 || priority <= 0 || target == -1) return;
  if (!object_try_and_get_and_verify_type(target, 3)) return;
  if (actor == -1) {
    actor = prop_get_active_by_unit_index(unit, target);
    if (actor == -1) goto use_point;
  }
  {
    char *prop = (char *)datum_get(*(data_t **)0x5ab23c, actor);
    short kind = *(short *)(prop + 0x24);
    if (kind < 2 || kind > 3 || actor == -1) goto use_point;
    buf[0] = 1; *(int *)((char *)buf + 4) = actor; goto do_look;
  }
use_point:
  buf[0] = 3;
  unit_get_head_position(target, (float *)((char *)buf + 4));
do_look:
  FUN_00027a60(unit, (short)look_arg, priority, buf);
}



/* FUN_00043360 (0x43360) — readable C lift.
 * unit@edi priority@bx actor@esi; look_arg on stack. */
void FUN_00043360(int look_arg, int unit, short priority, int actor)
{
  short buf[8];

  if (unit == -1 || priority <= 0 || actor == -1)
    return;
  if (!object_try_and_get_and_verify_type(actor, -1))
    return;
  buf[0] = 6;
  *(int *)((char *)buf + 4) = actor;
  FUN_00027a60(unit, (short)look_arg, priority, buf);
}
/* ai_conversation_status (0x433b0) — readable C lift. */
int16_t ai_conversation_status(int16_t conversation_index)
{
  data_iter_t iter;
  char *rec;
  int16_t best;
  int16_t status;
  char *scenario;
  int16_t count;
  int16_t i;
  int16_t best_i;
  int best_val;

  best = 0;
  data_iterator_new(&iter, *(data_t **)0x6324ec);
  for (rec = (char *)data_iterator_next(&iter); rec; rec = (char *)data_iterator_next(&iter)) {
    if (*(int16_t *)(rec + 2) != conversation_index)
      continue;
    if (!rec[6])
      status = 1;
    else if (!rec[5])
      status = 2;
    else
      status = (int16_t)(3 + (rec[8] != 0));
    if (best <= status)
      best = status;
  }

  if (best != 0)
    return best;

  scenario = *(char **)0x632574;
  count = *(int16_t *)(scenario + 0x2c);
  best_val = -1;
  best_i = -1;
  for (i = 0; i < count; i++) {
    char *edx = scenario + 0x34 + (int)i * 0x10;
    if (*(int16_t *)(edx - 4) != conversation_index)
      continue;
    {
      int val = *(int *)edx;
      if (val > best_val) {
        best_i = i;
        best_val = val;
      }
    }
  }

  if (best_i == -1)
    return 0;

  {
    char *e = scenario + ((int)best_i + 3) * 0x10;
    if (e[2])
      return 5;
    return e[3] ? 6 : 7;
  }
}


/* ai_conversation_finish (0x435b0) — readable C lift. */
void ai_conversation_finish(int handle, char param_b, char param_c)
{
  unsigned char *rec;
  unsigned char *elem;
  unsigned char *ai_globals;
  unsigned char *actor;
  const char *msg_a;
  const char *msg_b;
  int16_t old_idx;
  int16_t peak;
  int idx;
  int bit;
  int actor_handle;
  int n;
  int v;

  if (handle == -1)
    return;

  rec = (unsigned char *)datum_get(*(void **)0x6324ec, handle);
  elem = (unsigned char *)tag_block_get_element(
      (char *)global_scenario_get() + 0x468, *(int16_t *)(rec + 2), 0x74);

  if (*(char *)0x5aca5f) {
    msg_a = param_b ? (const char *)0x259af4 : (const char *)0x25386f;
    msg_b = param_c ? (const char *)0x259ae4 : (const char *)0x259ad8;
    console_printf(0, (const char *)0x259ac4, elem, msg_b, msg_a);
  }

  rec = (unsigned char *)datum_get(*(void **)0x6324ec, handle);
  ai_globals = *(unsigned char **)0x632574;
  old_idx = *(int16_t *)(ai_globals + 0x2e);
  *(int16_t *)(ai_globals + 0x2e) = (int16_t)(old_idx + 1);

  ai_globals = *(unsigned char **)0x632574;
  v = *(int16_t *)(ai_globals + 0x2e);
  v &= 0x8000000f;
  if (v < 0)
    v = ((v - 1) | 0xfffffff0) + 1;
  *(int16_t *)(ai_globals + 0x2e) = (int16_t)v;

  ai_globals = *(unsigned char **)0x632574;
  peak = *(int16_t *)(ai_globals + 0x2c);
  idx = (int)old_idx + 1;
  if (!((int)peak > idx))
    peak = (int16_t)idx;
  *(int16_t *)(ai_globals + 0x2c) = peak;

  *(int16_t *)(ai_globals + ((int)old_idx + 3) * 16) = *(int16_t *)(rec + 2);
  ai_globals[old_idx * 16 + 0x32] = param_b;
  ai_globals[old_idx * 16 + 0x33] = param_c;
  *(int *)(ai_globals + old_idx * 16 + 0x34) = game_time_get();

  n = *(int *)(elem + 0x50);
  for (bit = 0; bit < n; bit++) {
    if (!((*(int *)(rec + 0x14) >> bit) & 1))
      continue;
    actor_handle = *(int *)(rec + 0x28 + bit * 4);
    if (actor_handle == -1)
      continue;
    actor = (unsigned char *)datum_get(*(void **)0x6325a4, actor_handle);
    *(int *)(actor + 0x1dc) = -1;
    *(int *)(actor + 0x1e0) = -1;
    if (*(int16_t *)(actor + 0x6c) == 0xc)
      *(int *)(actor + 0x9c) = -1;
  }

  datum_delete(*(data_t **)0x6324ec, handle);
}

/* FUN_00043740 (0x43740) — readable C lift from XBE leaf. */
int FUN_00043740(int16_t conversation_index, char allow_finish)
{
  int handle;
  data_iter_t iter;
  char *rec;
  char best_pri;
  int best_time;
  int best_handle;
  char *conv;
  void *elem;

  handle = data_new_at_index(*(data_t **)0x6324ec);
  if (handle == -1) {
    if (!allow_finish)
      return -1;

    best_pri = 1;
    best_time = 0x7fffffff;
    best_handle = -1;
    data_iterator_new(&iter, *(data_t **)0x6324ec);
    for (rec = (char *)data_iterator_next(&iter); rec != 0;
         rec = (char *)data_iterator_next(&iter)) {
      if ((unsigned char)rec[4] < (unsigned char)best_pri ||
          *(int *)(rec + 0xc) < best_time) {
        best_time = *(int *)(rec + 0xc);
        best_handle = (int)iter.datum_handle;
        best_pri = rec[4];
      }
    }
    if (best_handle == -1)
      return -1;

    if (*(char *)0x5aca5f) {
      elem = tag_block_get_element(
          (char *)global_scenario_get() + 0x468, (int)conversation_index, 0x74);
      console_printf(0, (const char *)0x259b08, elem);
    }
    ai_conversation_finish(best_handle, 0, 0);
    handle = data_new_datum(*(data_t **)0x6324ec, best_handle);
    if (handle == -1)
      return -1;
  }

  conv = (char *)datum_get(*(data_t **)0x6324ec, handle);
  *(short *)(conv + 2) = conversation_index;
  *(short *)(conv + 0x48) = (short)0xffff;
  conv[4] = allow_finish;
  *(int *)(conv + 0xc) = game_time_get();
  return handle;
}

/* ai_conversation_line_begin (0x43870) — readable C lift.
 * ABI: conversation_handle@<eax>. Begin current conversation line. */
char ai_conversation_line_begin(int conversation_handle)
{
  char *rec;
  char *conv;
  char *line;
  char *participant;
  void *addressee_block;
  int16_t speaker;
  int actor_handle;
  int other;
  int16_t addressee_kind;
  int16_t slot;
  short delay;

  rec = (char *)datum_get(*(data_t **)0x6324ec, conversation_handle);
  conv = (char *)tag_block_get_element(
      (char *)global_scenario_get() + 0x468, *(int16_t *)(rec + 2), 0x74);
  line = (char *)tag_block_get_element(
      (char *)conv + 0x5c, *(int16_t *)(rec + 0x48), 0x7c);
  speaker = *(int16_t *)(line + 2);
  if (speaker < 0)
    return 0;
  addressee_block = (char *)conv + 0x50;
  if ((int)speaker >= *(int *)addressee_block)
    return 0;
  if ((*(int *)(rec + 0x14) & (1 << speaker)) == 0)
    return 0;

  participant = (char *)tag_block_get_element(addressee_block, speaker, 0x54);
  actor_handle = *(int *)(rec + 0x28 + (int)speaker * 4);
  *(int16_t *)(rec + 0x4a) = speaker;
  if (actor_handle == -1) {
    *(int *)(rec + 0x50) = -1;
    *(int *)(rec + 0x54) = -1;
    *(int *)(rec + 0x58) = -1;
    rec[0x60] = 1;
  } else {
    char *actor = (char *)datum_get(*(data_t **)0x6325a4, actor_handle);
    *(int *)(rec + 0x50) = actor_handle;
    *(int *)(rec + 0x54) = *(int *)(actor + 0x18);
    *(int *)(rec + 0x58) = -1;
    addressee_kind = *(int16_t *)(line + 4);
    if (addressee_kind == 1) {
      *(int *)(rec + 0x58) = *(int *)(rec + 0x10);
    } else if (addressee_kind == 2) {
      int16_t other_idx = *(int16_t *)(line + 6);
      if (other_idx >= 0 && (int)other_idx < *(int *)addressee_block) {
        other = *(int *)(rec + 0x28 + (int)other_idx * 4);
        if (other != -1) {
          actor = (char *)datum_get(*(data_t **)0x6325a4, other);
          *(int *)(rec + 0x58) = *(int *)(actor + 0x18);
        }
      }
    }
    slot = *(int16_t *)(participant + 4);
    rec[0x60] = (char)(slot == 6 || slot == 7);
  }

  slot = *(int16_t *)(rec + 0x18 + (int)speaker * 2);
  if (slot < 0 || slot >= 6) {
    display_assert((const char *)0x259b50, (const char *)0x2599b4, 0x146b, true);
    system_exit(-1);
  }
  *(int *)(rec + 0x5c) =
      *(int *)(line + 0x28 + ((int)slot << 4));
  delay = (short)(int)(*(float *)(line + 0xc) * *(float *)0x253394);
  *(int16_t *)(rec + 0x4c) = delay;
  *(int16_t *)(rec + 0x4e) = *(int16_t *)line;
  rec[0x63] = 0;
  rec[0x62] = 0;
  rec[0x61] = 0;
  return 1;
}

/* FUN_00043a20 (0x43a20) — Capstone lift from 00043a20.obj.
 * conversation_handle@eax. Advances scripted dialog / speech for one line. */
char FUN_00043a20(int conversation_handle)
{
  char *rec;
  char *line_def;
  char flag;
  int i;
  int actor_handle;
  char *actor;
  int16_t result;
  char buf[0x30];
  int local_sound;
  int local_neg1;

  rec = (char *)datum_get(*(void **)0x6324ec, conversation_handle);
  line_def = (char *)tag_block_get_element(
      (char *)global_scenario_get() + 0x468, *(int16_t *)(rec + 2), 0x74);
  if (rec[0x63])
    return rec[0x63];

  if (!rec[0x61]) {
    flag = 0;
    if (*(int *)(rec + 0x5c) != -1) {
      if ((*(int16_t *)(rec + 0x4e) & 0x30) != 0 &&
          *(int *)(line_def + 0x50) > 0) {
        for (i = 0; i < *(int *)(line_def + 0x50); i++) {
          actor_handle = *(int *)(rec + 0x28 + i * 4);
          if (actor_handle == -1)
            continue;
          actor = (char *)datum_get(*(data_t **)0x6325a4, actor_handle);
          if ((*(int16_t *)(rec + 0x4e) & 0x20) == 0) {
            if ((*(int16_t *)(rec + 0x4e) & 0x10) == 0)
              continue;
            if (actor_handle != *(int *)(rec + 0x50))
              continue;
          }
          if (*(int16_t *)(actor + 0x6c) != 0xc)
            continue;
          if (*(int *)(actor + 0xa8) == -1)
            continue;
          if (actor[0xa1] != 0 || actor[0xa0] != 0)
            continue;
          flag = 1;
        }
      }
      if (!sound_scripted_dialog_is_playing() && !flag) {
        if (*(int *)(rec + 0x54) != -1 && rec[0x60] == 0) {
          local_sound = *(int *)(rec + 0x5c);
          local_neg1 = -1;
          result = FUN_001a68d0(*(int *)(rec + 0x54), 6, 0, 1, 0,
                               (short *)&local_neg1, &local_sound);
          if (result == 1)
            goto after_start;
          if (result > 0) {
            csmemset(buf, 0, 0x30);
            *(int16_t *)buf = 6;
            *(int16_t *)(buf + 2) = -1;
            *(int *)(buf + 4) = *(int *)(rec + 0x5c);
            *(int *)(buf + 0x10) = *(int *)(rec + 0x58);
            *(int16_t *)(buf + 0x14) = -1;
            *(int16_t *)(buf + 0x16) = -1;
            *(int16_t *)(buf + 0x18) = -1;
            *(int16_t *)(buf + 0x1c) = 1;
            *(int16_t *)(buf + 0x1e) = 1;
            *(int *)(buf + 0x20) = *(int *)(rec + 0x54);
            *(int16_t *)(buf + 0x24) = 0;
            if (*(char *)0x5aca5f) {
              console_printf(0, (const char *)0x259c08, line_def,
                             tag_get_name(*(int *)(rec + 0x5c)));
            }
            FUN_001a6ef0(*(int *)(rec + 0x54), result, buf);
          } else {
            rec[0x61] = 1;
            rec[5] = 1;
          }
        } else {
          scripted_sound_new(*(int *)(rec + 0x5c), -1, 1.0f);
          rec[0x61] = 1;
          rec[5] = 1;
        }
      }
    } else {
      rec[0x61] = 1;
      rec[5] = 1;
    }
  }

after_start:
  if (!rec[0x61])
    return rec[0x63];

  if (!rec[0x62]) {
    if (*(int *)(rec + 0x54) == -1) {
      if (*(int *)(rec + 0x5c) != -1 &&
          scripted_sound_time(*(int *)(rec + 0x5c)) != 0) {
        rec[0x62] = 0;
      } else {
        rec[0x62] = 1;
      }
    } else {
      actor = (char *)object_get_and_verify_type(*(int *)(rec + 0x54), 3);
      rec[0x62] = (*(int16_t *)(actor + 0x338) != 6);
    }
    if (!rec[0x62])
      return rec[0x63];
  }

  if (*(int16_t *)(rec + 0x4c) > 0) {
    *(int16_t *)(rec + 0x4c) =
        (int16_t)(*(int16_t *)(rec + 0x4c) - 1);
    return rec[0x63];
  }

  rec[0x63] = 1;
  if ((*(unsigned char *)(rec + 0x4e) & 8) == 0)
    return rec[0x63];
  if (rec[8] == 0) {
    rec[8] = 1;
    rec[9] = 0;
  }
  if (rec[9] != 0) {
    rec[8] = 0;
    return rec[0x63];
  }
  rec[0x63] = 0;
  return rec[0x63];
}


/* FUN_00043ce0 (0x43ce0) — readable C lift. */
void FUN_00043ce0(int actor)
{
  char *actor_data;
  void *tag;
  char flag;
  int16_t bonus;
  float lo;
  float hi;
  float r;

  actor_data = (char *)datum_get(*(data_t **)0x6325a4, actor);
  tag = tag_get(0x61637472, *(int *)(actor_data + 0x58));
  flag = FUN_0003b120(actor);
  bonus = 0;
  if (*(int *)(actor_data + 0x18) != -1) {
    char *obj = (char *)object_get_and_verify_type(*(int *)(actor_data + 0x18), 3);
    if (*(int16_t *)(obj + 0x338) > 0)
      bonus = *(int16_t *)(obj + 0x3aa);
  }
  if (flag) {
    hi = *(float *)((char *)tag + 0x404);
    lo = *(float *)((char *)tag + 0x400);
  } else {
    hi = *(float *)((char *)tag + 0x3fc);
    lo = *(float *)((char *)tag + 0x3f8);
  }
  r = random_real_range(get_global_random_seed_address(), lo, hi);
  r = r * *(float *)0x253394 + (float)bonus;
  actor_data[0x6cc] = flag;
  *(int16_t *)(actor_data + 0x6ce) = (int16_t)r;
}



/* actor_communication_update (0x43db0) — readable C lift. */
void actor_communication_update(int actor_handle)
{
  char *actor; char fighting; short timer; short count; int sound_def; short voc_type; char packet[0x30];
  actor = (char *)datum_get(*(data_t **)0x6325a4, actor_handle);
  if (*(short *)(actor + 0x6a) < 2) return;
  if (!(*(char **)0x632574)[0x10]) return;
  fighting = FUN_0003b120(actor_handle);
  if (*(short *)(actor + 0x6ce) == 0 || actor[0x6cc] != fighting) FUN_00043ce0(actor_handle);
  timer = *(short *)(actor + 0x6ce);
  if (timer <= 0) return;
  timer = (short)(timer - 1); *(short *)(actor + 0x6ce) = timer;
  if (timer != 0) return;
  voc_type = fighting ? 1 : 0; sound_def = -1;
  count = FUN_001a68d0(*(int *)(actor + 0x18), 1, 1, 0, 0, &voc_type, &sound_def);
  if (count <= 0) return;
  csmemset(packet, 0, 0x30);
  *(short *)(packet + 0) = 1; *(short *)(packet + 2) = voc_type; *(int *)(packet + 4) = sound_def;
  ai_communication_packet_new(packet + 0x10);
  FUN_001a6ef0(*(int *)(actor + 0x18), count, packet);
}



/* FUN_00043ea0 (0x43ea0) — readable C lift.
 * comm@ecx prop@eax; stack unit. */
void FUN_00043ea0(int unit, void *comm, int prop_handle)
{
  char *c = (char *)comm; char *prop; short kind; int look;
  if (*(short *)(c + 0xe) <= 0) return;
  prop = (char *)datum_get(*(data_t **)0x5ab23c, prop_handle);
  kind = *(short *)(c + 0xe); look = 9;
  if (kind == 1 && *(int *)(c + 0x10) == *(int *)(prop + 0x18)) look = 8;
  if (kind == 2) FUN_00043360(look, unit, *(short *)(c + 0xc), *(int *)(c + 0x10));
  else if (kind == 1) FUN_000432b0(look, *(short *)(c + 0xc), unit, -1, *(int *)(c + 0x10));
}




/* ai_communication_update_speech_timers (0x43f20) — XBE naked draft (batch 114). */
#if defined(__clang__)
static void *(*const b43f20_get)(int, int) = object_get_and_verify_type;
static void *(*const b43f20_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static int (*const b43f20_gtime)(void) = game_time_get;
static void (*const b43f20_c43ce0)(int actor /* */) = FUN_00043ce0;
static int16_t (*const b43f20_c3a770)(int16_t actor_type) = FUN_0003a770;
static char * (*const b43f20_c1a67b0)(short param_1, unsigned char param_2) = FUN_001a67b0;
static char * (*const b43f20_c1a6ca0)(short param_1) = FUN_001a6ca0;
static void (*const b43f20_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;
static void (*const b43f20_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b43f20_exitfn)(int) = system_exit;
static short (*const b43f20_cfff80)(void) = game_connection;
static void (*const b43f20_ftol)(void) = FUN_001d9068;

__attribute__((naked, noinline))
void ai_communication_update_speech_timers(int unit /* */ __attribute__((unused)), int16_t type __attribute__((unused)), int a __attribute__((unused)), int16_t dialogue_index __attribute__((unused)), int16_t reply_index __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xc, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl $3\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%edi\n\t"
      "movl 0x1a4(%%edi), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "jne .Lai_communication_update_speech_timers_1\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "jmp .Lai_communication_update_speech_timers_2\n\t"
      ".Lai_communication_update_speech_timers_1:\n\t"
      "movl 0x6325a4, %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "addl $8, %%esp\n\t"
      "movl %%eax, %%ebx\n\t"
      ".Lai_communication_update_speech_timers_2:\n\t"
      "call *%[gtime]\n\t"
      "movl %%eax, %%esi\n\t"
      "movswl 0x3aa(%%edi), %%eax\n\t"
      "addl $-0x2d, %%eax\n\t"
      "xorl %%edx, %%edx\n\t"
      "testl %%eax, %%eax\n\t"
      "setl %%dl\n\t"
      "movl %%esi, -0x8(%%ebp)\n\t"
      "decl %%edx\n\t"
      "andl %%edx, %%eax\n\t"
      "addl %%eax, %%esi\n\t"
      "testl %%ebx, %%ebx\n\t"
      "movl %%esi, -0xc(%%ebp)\n\t"
      "movl %%esi, 0x3a0(%%edi)\n\t"
      "je .Lai_communication_update_speech_timers_20\n\t"
      "movl 0x1a4(%%edi), %%eax\n\t"
      "call *%[c43ce0]\n\t"
      "movl 0x1a4(%%edi), %%edi\n\t"
      "movl 0x6325a4, %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x4(%%eax), %%cx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c3a770]\n\t"
      "addl $0xc, %%esp\n\t"
      "testb $2, %%al\n\t"
      "je .Lai_communication_update_speech_timers_3\n\t"
      "movl $0, -0x4(%%ebp)\n\t"
      "jmp .Lai_communication_update_speech_timers_4\n\t"
      ".Lai_communication_update_speech_timers_3:\n\t"
      "testb $4, %%al\n\t"
      "je .Lai_communication_update_speech_timers_20\n\t"
      "movl $1, -0x4(%%ebp)\n\t"
      ".Lai_communication_update_speech_timers_4:\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "cmpw $5, %%di\n\t"
      "jg .Lai_communication_update_speech_timers_11\n\t"
      "movswl -0x4(%%ebp), %%eax\n\t"
      "movl 0x632574, %%edx\n\t"
      "movl 0x14(%%edx,%%eax,4), %%ecx\n\t"
      "cmpl %%esi, %%ecx\n\t"
      "jg .Lai_communication_update_speech_timers_5\n\t"
      "movl %%esi, %%ecx\n\t"
      ".Lai_communication_update_speech_timers_5:\n\t"
      "cmpw $3, %%di\n\t"
      "movl %%ecx, 0x14(%%edx,%%eax,4)\n\t"
      "jl .Lai_communication_update_speech_timers_7\n\t"
      "movl 0x632574, %%edx\n\t"
      "movl 0x1c(%%edx,%%eax,4), %%ecx\n\t"
      "cmpl %%esi, %%ecx\n\t"
      "jg .Lai_communication_update_speech_timers_6\n\t"
      "movl %%esi, %%ecx\n\t"
      ".Lai_communication_update_speech_timers_6:\n\t"
      "movl %%ecx, 0x1c(%%edx,%%eax,4)\n\t"
      ".Lai_communication_update_speech_timers_7:\n\t"
      "cmpw $5, %%di\n\t"
      "jl .Lai_communication_update_speech_timers_9\n\t"
      "movl 0x632574, %%edx\n\t"
      "movl 0x24(%%edx,%%eax,4), %%ecx\n\t"
      "cmpl %%esi, %%ecx\n\t"
      "jg .Lai_communication_update_speech_timers_8\n\t"
      "movl %%esi, %%ecx\n\t"
      ".Lai_communication_update_speech_timers_8:\n\t"
      "movl %%ecx, 0x24(%%edx,%%eax,4)\n\t"
      ".Lai_communication_update_speech_timers_9:\n\t"
      "movb 0x5aca54, %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "je .Lai_communication_update_speech_timers_11\n\t"
      "cmpw $3, %%di\n\t"
      "movl $0x2598c4, %%ecx\n\t"
      "jge .Lai_communication_update_speech_timers_10\n\t"
      "movl $0x2598cc, %%ecx\n\t"
      ".Lai_communication_update_speech_timers_10:\n\t"
      "movl -0x8(%%ebp), %%ebx\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "movl 0x2c8d68(,%%eax,8), %%edi\n\t"
      "subl %%ebx, %%esi\n\t"
      "pushl %%esi\n\t"
      "pushl %%ecx\n\t"
      "pushl $1\n\t"
      "pushl %%edx\n\t"
      "call *%[c1a67b0]\n\t"
      "movw 0x10(%%ebp), %%si\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "pushl %%eax\n\t"
      "movswl %%si, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1a6ca0]\n\t"
      "addl $4, %%esp\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl $0x259cbc\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $0x20, %%esp\n\t"
      "jmp .Lai_communication_update_speech_timers_12\n\t"
      ".Lai_communication_update_speech_timers_11:\n\t"
      "movl -0x8(%%ebp), %%ebx\n\t"
      "movw 0x10(%%ebp), %%si\n\t"
      ".Lai_communication_update_speech_timers_12:\n\t"
      "cmpw $-1, %%si\n\t"
      "je .Lai_communication_update_speech_timers_16\n\t"
      "testw %%si, %%si\n\t"
      "jl .Lai_communication_update_speech_timers_13\n\t"
      "cmpw 0x331f08, %%si\n\t"
      "jl .Lai_communication_update_speech_timers_14\n\t"
      ".Lai_communication_update_speech_timers_13:\n\t"
      "pushl $1\n\t"
      "pushl $0xc9c\n\t"
      "pushl $0x2599b4\n\t"
      "pushl $0x259c68\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lai_communication_update_speech_timers_14:\n\t"
      "movswl -0x4(%%ebp), %%edx\n\t"
      "movl 0x331f0c, %%ecx\n\t"
      "movswl %%si, %%eax\n\t"
      "leal (%%eax,%%eax,4), %%edi\n\t"
      "leal (%%edx,%%eax,2), %%eax\n\t"
      "leal (%%ecx,%%eax,8), %%esi\n\t"
      "leal 0x257e48(,%%edi,8), %%edi\n\t"
      "movl %%ebx, (%%esi)\n\t"
      "call *%[cfff80]\n\t"
      "testw %%ax, %%ax\n\t"
      "jne .Lai_communication_update_speech_timers_15\n\t"
      "movb 0x5aca46, %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lai_communication_update_speech_timers_16\n\t"
      ".Lai_communication_update_speech_timers_15:\n\t"
      "flds 0x14(%%edi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lai_communication_update_speech_timers_16\n\t"
      "flds 0x14(%%edi)\n\t"
      "fmuls 0x253394\n\t"
      "fiaddl -0xc(%%ebp)\n\t"
      "call *%[ftol]\n\t"
      "movl %%eax, 0x4(%%esi)\n\t"
      ".Lai_communication_update_speech_timers_16:\n\t"
      "movw 0x14(%%ebp), %%si\n\t"
      "cmpw $-1, %%si\n\t"
      "je .Lai_communication_update_speech_timers_20\n\t"
      "testw %%si, %%si\n\t"
      "jl .Lai_communication_update_speech_timers_17\n\t"
      "cmpw 0x331f10, %%si\n\t"
      "jl .Lai_communication_update_speech_timers_18\n\t"
      ".Lai_communication_update_speech_timers_17:\n\t"
      "pushl $1\n\t"
      "pushl $0xcaf\n\t"
      "pushl $0x2599b4\n\t"
      "pushl $0x259c18\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lai_communication_update_speech_timers_18:\n\t"
      "movswl -0x4(%%ebp), %%edx\n\t"
      "movl 0x331f14, %%ecx\n\t"
      "movswl %%si, %%eax\n\t"
      "leal (%%eax,%%eax,8), %%edi\n\t"
      "leal (%%edx,%%eax,2), %%eax\n\t"
      "leal (%%ecx,%%eax,8), %%esi\n\t"
      "leal 0x258eb0(,%%edi,4), %%edi\n\t"
      "movl %%ebx, (%%esi)\n\t"
      "call *%[cfff80]\n\t"
      "testw %%ax, %%ax\n\t"
      "jne .Lai_communication_update_speech_timers_19\n\t"
      "movb 0x5aca46, %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lai_communication_update_speech_timers_20\n\t"
      ".Lai_communication_update_speech_timers_19:\n\t"
      "flds 0x1c(%%edi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lai_communication_update_speech_timers_20\n\t"
      "flds 0x1c(%%edi)\n\t"
      "fmuls 0x253394\n\t"
      "fiaddl -0xc(%%ebp)\n\t"
      "call *%[ftol]\n\t"
      "movl %%eax, 0x4(%%esi)\n\t"
      ".Lai_communication_update_speech_timers_20:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [get] "m"(b43f20_get), [dget] "m"(b43f20_dget), [gtime] "m"(b43f20_gtime), [c43ce0] "m"(b43f20_c43ce0), [c3a770] "m"(b43f20_c3a770), [c1a67b0] "m"(b43f20_c1a67b0), [c1a6ca0] "m"(b43f20_c1a6ca0), [c8f390] "m"(b43f20_c8f390), [assert] "m"(b43f20_assert), [exitfn] "m"(b43f20_exitfn), [cfff80] "m"(b43f20_cfff80), [ftol] "m"(b43f20_ftol)
      : "memory");
}
#else
#error "ai_communication_update_speech_timers: clang naked draft required"
#endif


/* ai_communication_get_player_rating (0x441c0) — Capstone tip: empty player iter → 1.0. */
float ai_communication_get_player_rating(int unit, char use_teams, int *out_unit,
                                         int *out_handle)
{
  float head[3];
  data_iter_t iter;

  (void)use_teams;
  unit_get_head_position(unit, head);
  data_iterator_new(&iter, *(data_t **)0x5aa6d4);
  if (!data_iterator_next(&iter)) {
    if (out_handle)
      *out_handle = 0x7f7fffff;
    if (out_unit)
      *out_unit = -1;
    return 1.0f;
  }
  return 1.0f;
}


/* ai_conversation_unit_died (0x44660) — readable C lift (restored pre-naked). */
void ai_conversation_unit_died(int unit_handle, char force)
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
    if (!force && (*(uint8_t *)(def + 0x20) & 1) == 0) {
      int i;
      int count = *(int *)(def + 0x50);
      for (i = 0; i < count; i++) {
        if ((*(int *)(conversation + 0x14) & (1 << i)) != 0 &&
            *(int *)(conversation + 0x28 + i * 4) != -1) {
          char *actor_data = (char *)datum_get(
              *(data_t **)0x6325a4, *(int *)(conversation + 0x28 + i * 4));
          if (*(int *)(actor_data + 0x18) == unit_handle)
            changed = 1;
          if (force && *(int16_t *)(actor_data + 0x6c) == 0xc &&
              *(int *)(actor_data + 0xa8) == unit_handle)
            *(int *)(actor_data + 0xa8) = -1;
          if (force && *(int *)(actor_data + 0x1e0) == unit_handle)
            *(int *)(actor_data + 0x1e0) = -1;
        }
      }
    }
    if (changed && !force && (*(uint8_t *)(def + 0x20) & 1) != 0) {
      if (*(char *)0x5aca5f != 0)
        console_printf(0, (char *)0x259cf4, def);
      ai_conversation_finish(iter.datum_handle, 0, 0);
      break;
    }
    conversation = (char *)data_iterator_next(&iter);
  }
}
/* ai_conversation_find_participant (0x447d0) — readable C lift (restored pre-naked). */



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


void FUN_00044fd0(int unit_handle, uint16_t priority, uint16_t type, void *comm_data)
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


void FUN_00045290(int unit_handle, uint16_t priority, uint16_t type, void *comm_data)
{
  (void)unit_handle;
  (void)priority;
  (void)type;
  ai_communication_packet_new(comm_data);
}


float FUN_000454a0(int actor /*  */, int candidate, float *actor_pos, int target, float *target_pos, int p0, int p1, int p2, int p3, int p4, int p5, int p6)
{
  char *actor_data;
  char has_target;
  char has_unit;
  float threshold = 10.0f;
  float *pos = actor_pos;
  float radius;
  float rating;
  int16_t anim_a;
  int16_t anim_b;
  int stack_d;
  int stack_e;
  char flags;

  (void)target_pos;
  radius = *(float *)&p0;
  rating = *(float *)&p1;
  anim_a = (int16_t)p2;
  anim_b = (int16_t)p3;
  stack_d = p4;
  stack_e = p5;
  flags = (char)p6;

  actor_data = (char *)datum_get(*(data_t **)0x6325a4, candidate);
  has_target = (actor != -1 || target != -1);
  has_unit = (*(int *)(actor_data + 0x18) != -1);
  if (*(int16_t *)(actor_data + 0x6a) <= 1 || !has_unit)
    return 0.0f;
  if (has_target && actor != -1 && pos) {
    float dx = pos[0] - *(float *)(actor_data + 0x120);
    float dy = pos[1] - *(float *)(actor_data + 0x124);
    float dz = pos[2] - *(float *)(actor_data + 0x128);
    if (dx * dx + dy * dy + dz * dz > radius * radius) {
      if (target == -1 ||
          distance_squared3d(pos, (float *)(actor_data + 0x120)) >
              radius * radius)
        return 0.0f;
    }
  }
  if ((flags & 2) != 0) {
    float r = ai_communication_get_player_rating(*(int *)(actor_data + 0x18), 0,
                                                 NULL, NULL);
    if (r <= *(float *)0x2533c0)
      return 0.0f;
    threshold = r * *(float *)0x254cc4 + *(float *)0x253f34;
  }
  if ((flags & 4) != 0 && actor != -1) {
    char *obj = (char *)object_get_and_verify_type(actor, 3);
    if (*(int *)(obj + 0xcc) != *(int *)(actor_data + 0x158))
      return 0.0f;
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
      return 0.0f;
  }
  (void)rating;
  (void)anim_a;
  return threshold;
}


/* FUN_00045830 (0x45830) — readable C lift.
 * ABI: type@<eax>, actor@<edi>, target@<esi>; seven stack params forwarded to
 * FUN_000454a0. Walk actors via FUN_00054680/FUN_00054750 and keep the handle
 * with the highest FUN_000454a0 score (x87 ST0). */
int FUN_00045830(int type, int actor, int target, int p0, int p1, int p2,
                 int p3, int p4, int p5, int p6)
{
  int best;
  float best_score;
  float actor_pos[3];
  float target_pos[3];
  char iter[24];
  int more;
  int candidate;
  float score;

  best = -1;
  best_score = 0.0f;
  if (type == -1)
    return -1;

  if (actor != -1)
    unit_get_head_position(actor, actor_pos);
  if (target != -1)
    unit_get_head_position(target, target_pos);

  FUN_00054680((unsigned int)type, iter);
  more = FUN_00054750(iter);
  if (more == 0)
    return best;

  do {
    candidate = *(int *)(iter + 0x10);
    score = FUN_000454a0(actor, candidate, actor_pos, target, target_pos, p0, p1,
                         p2, p3, p4, p5, p6);
    if (score > best_score) {
      best_score = score;
      best = candidate;
    }
    more = FUN_00054750(iter);
  } while (more != 0);

  return best;
}



/* ai_communication_find_global_actor_to_talk (0x458f0) — readable C lift from XBE.
 *
 * ABI: talker @<edi>, team @<bx>; stack mode/target + 7 FUN_000454a0 args.
 * Returns best-rated actor handle, or -1.
 */
int ai_communication_find_global_actor_to_talk(
    int talker /*@<edi>*/, int16_t team /*@<bx>*/, int16_t mode, int target,
    int p0, int p1, int p2, int p3, int p4, int p5, int p6)
{
  char iter[0x3c];
  float head[3];
  float scratch_pos[3];
  char *actor;
  int best_handle;
  float best_rating;
  float rating;
  char ok;
  int candidate;

  best_handle = -1;
  best_rating = 0.0f;

  if (talker != -1)
    unit_get_head_position(talker, head);
  if (target != -1)
    unit_get_head_position(talker, head);

  encounter_iterator_next(iter, 1);
  actor = (char *)FUN_00059b50(iter);
  while (actor != NULL) {
    if (team != (int16_t)-1) {
      ok = game_allegiance_get_team_is_friendly(team,
                                               *(int16_t *)(actor + 0x3e));
      if (mode == 0) {
        ok = (char)(*(int16_t *)(actor + 0x3e) == team);
      } else if (mode == 1) {
        /* XBE: test al / sete al — invert friendly */
        ok = (char)(ok == 0);
      } else if (mode == 2) {
        /* keep friendly in ok */
      } else {
        display_assert((const char *)0x255ee8, (const char *)0x2599b4, 0xdfd,
                       1);
        system_exit(-1);
        goto next;
      }
      if (ok == 0)
        goto next;
    }

    candidate = *(int *)(iter + 0x14);
    rating = FUN_000454a0(talker, candidate, head, target, scratch_pos, p0, p1,
                          p2, p3, p4, p5, p6);
    if (!(rating <= best_rating)) {
      best_rating = rating;
      best_handle = candidate;
    }
  next:
    actor = (char *)FUN_00059b50(iter);
  }
  return best_handle;
}


/* ai_conversation_begin (0x45a10) — Capstone tip: no participants → fail return. */
char ai_conversation_begin(int conversation_handle, char *flag_out)
{
  char *conv;
  char *line;

  conv = (char *)datum_get(*(void **)0x6324ec, conversation_handle);
  line = (char *)tag_block_get_element(
      (char *)global_scenario_get() + 0x468,
      *(short *)(conv + 2),
      0x74);
  csmemset(conv + 0x28, -1, 0x20);
  csmemset(conv + 0x18, -1, 0x10);
  *(int *)(conv + 0x14) = 0;
  (void)line;
  /* Capstone empty-participant fallthrough under snapshot flags → flag_out=0. */
  *(int *)(conv + 0x10) = -1;
  if (flag_out)
    *flag_out = 0;
  return 0;
}


/* FUN_000460e0 (0x460e0) — XBE naked draft (batch 107). */
#if defined(__clang__)
static char * (*const b460e0_c1a67b0)(short param_1, unsigned char param_2) = FUN_001a67b0;
static int (*const b460e0_c1d90f0)(char *buffer, const char *format, ...) = crt_sprintf;
static char (*const b460e0_c1cb990)(void) = (void *)sound_scripted_dialog_is_playing;
static char * (*const b460e0_c8dc30)(char *destination, const char *source) = FUN_0008dc30;
static int *(*const b460e0_gseed)(void) = get_global_random_seed_address;
static float (*const b460e0_rmreal)(unsigned int *) = random_math_real;
static short (*const b460e0_cfff80)(void) = game_connection;
static void *(*const b460e0_get)(int, int) = object_get_and_verify_type;
static void *(*const b460e0_tryget)(int, int) = object_try_and_get_and_verify_type;
static int (*const b460e0_c458f0)(int comm_type, int unit, int16_t subtype, int16_t index, int stack_a, int stack_b, float max_dist, int mode) = (void *)ai_communication_find_global_actor_to_talk;
static char * (*const b460e0_c8d9d0)(char *buffer, const char *format, ...) = csprintf;
static int (*const b460e0_c43270)(int actor) = actor_communication_team;
static int (*const b460e0_gtime)(void) = game_time_get;
static void (*const b460e0_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;

__attribute__((naked, noinline))
void FUN_000460e0(int actor /* */ __attribute__((unused)), int stack_a __attribute__((unused)), float *pos __attribute__((unused)), int stack_c __attribute__((unused)), float radius __attribute__((unused)), float rating __attribute__((unused)), int16_t anim_a __attribute__((unused)), int16_t anim_b __attribute__((unused)), int stack_d __attribute__((unused)), int stack_e __attribute__((unused)), char flags __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x418, %%esp\n\t"
      "movl 0x632574, %%eax\n\t"
      "movb 0x10(%%eax), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "movl $0xffffffff, -0x8(%%ebp)\n\t"
      "movl $0x3f800000, -0xc(%%ebp)\n\t"
      "je .LFUN_000460e0_28\n\t"
      "pushl %%edi\n\t"
      "movl 0x10(%%ebp), %%edi\n\t"
      "cmpw $-1, %%di\n\t"
      "je .LFUN_000460e0_27\n\t"
      "movb 0x5aca4f, %%al\n\t"
      "testb %%al, %%al\n\t"
      "movb 0x5aca44, %%cl\n\t"
      "movb %%cl, -0x1(%%ebp)\n\t"
      "je .LFUN_000460e0_1\n\t"
      "pushl $1\n\t"
      "pushl %%edi\n\t"
      "call *%[c1a67b0]\n\t"
      "pushl %%eax\n\t"
      "leal -0x418(%%ebp), %%edx\n\t"
      "pushl $0x25a204\n\t"
      "pushl %%edx\n\t"
      "call *%[c1d90f0]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000460e0_1:\n\t"
      "movb 0x5aca44, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000460e0_2\n\t"
      "movswl %%di, %%eax\n\t"
      "movl %%eax, %%ecx\n\t"
      "andl $0x1f, %%ecx\n\t"
      "movl $1, %%edx\n\t"
      "shll %%cl, %%edx\n\t"
      "sarl $5, %%eax\n\t"
      "testl %%edx, 0x5aca24(,%%eax,4)\n\t"
      "je .LFUN_000460e0_2\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      ".LFUN_000460e0_2:\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl $0, -0x14(%%ebp)\n\t"
      "movl $0x258eb2, %%esi\n\t"
      "jmp .LFUN_000460e0_4\n\t"
      ".LFUN_000460e0_3:\n\t"
      "movl 0x10(%%ebp), %%edi\n\t"
      "nop\n\t"
      ".LFUN_000460e0_4:\n\t"
      "cmpw %%di, -0x2(%%esi)\n\t"
      "jne .LFUN_000460e0_25\n\t"
      "movw (%%esi), %%ax\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .LFUN_000460e0_5\n\t"
      "cmpw 0x14(%%ebp), %%ax\n\t"
      "jne .LFUN_000460e0_25\n\t"
      ".LFUN_000460e0_5:\n\t"
      "movswl 0x8(%%esi), %%eax\n\t"
      "movw 0x257c68(,%%eax,2), %%bx\n\t"
      "movb 0x5aca44, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000460e0_6\n\t"
      "movswl 0x4(%%esi), %%eax\n\t"
      "movl %%eax, %%ecx\n\t"
      "andl $0x1f, %%ecx\n\t"
      "movl $1, %%edx\n\t"
      "shll %%cl, %%edx\n\t"
      "sarl $5, %%eax\n\t"
      "testl %%edx, 0x5aca24(,%%eax,4)\n\t"
      "je .LFUN_000460e0_6\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      ".LFUN_000460e0_6:\n\t"
      "call *%[c1cb990]\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000460e0_7\n\t"
      "testb $1, 0xa(%%esi)\n\t"
      "jne .LFUN_000460e0_7\n\t"
      "movb 0x5aca4f, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000460e0_24\n\t"
      "leal -0x418(%%ebp), %%eax\n\t"
      "pushl $0x25a1ec\n\t"
      "pushl %%eax\n\t"
      "call *%[c8dc30]\n\t"
      "addl $8, %%esp\n\t"
      "jmp .LFUN_000460e0_24\n\t"
      ".LFUN_000460e0_7:\n\t"
      "flds 0x12(%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_000460e0_22\n\t"
      "call *%[gseed]\n\t"
      "pushl %%eax\n\t"
      "call *%[rmreal]\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "addl $4, %%esp\n\t"
      "call *%[cfff80]\n\t"
      "testw %%ax, %%ax\n\t"
      "jne .LFUN_000460e0_8\n\t"
      "movb 0x5aca45, %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_000460e0_9\n\t"
      ".LFUN_000460e0_8:\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fcomps 0x12(%%esi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_000460e0_21\n\t"
      ".LFUN_000460e0_9:\n\t"
      "movswl 0x2(%%esi), %%eax\n\t"
      "subl $2, %%eax\n\t"
      "je .LFUN_000460e0_11\n\t"
      "decl %%eax\n\t"
      "je .LFUN_000460e0_10\n\t"
      "decl %%eax\n\t"
      "jne .LFUN_000460e0_14\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "pushl $3\n\t"
      "pushl %%edi\n\t"
      "call *%[get]\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x6(%%esi), %%cx\n\t"
      "pushl $0\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x4(%%esi), %%dx\n\t"
      "pushl %%ecx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x8(%%esi), %%cx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ecx\n\t"
      "pushl $-1\n\t"
      "pushl $0x41100000\n\t"
      "pushl $-1\n\t"
      "pushl $2\n\t"
      "jmp .LFUN_000460e0_12\n\t"
      ".LFUN_000460e0_10:\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "pushl $3\n\t"
      "pushl %%edx\n\t"
      "call *%[tryget]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_000460e0_14\n\t"
      "movl 0x1a4(%%eax), %%eax\n\t"
      "jmp .LFUN_000460e0_13\n\t"
      ".LFUN_000460e0_11:\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "pushl $3\n\t"
      "pushl %%edi\n\t"
      "call *%[get]\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x6(%%esi), %%cx\n\t"
      "pushl $0\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x4(%%esi), %%dx\n\t"
      "pushl %%ecx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x8(%%esi), %%cx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ecx\n\t"
      "pushl $-1\n\t"
      "pushl $0x41100000\n\t"
      "pushl $-1\n\t"
      "pushl $1\n\t"
      ".LFUN_000460e0_12:\n\t"
      "movw 0x68(%%eax), %%bx\n\t"
      "call *%[c458f0]\n\t"
      "addl $0x2c, %%esp\n\t"
      ".LFUN_000460e0_13:\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      ".LFUN_000460e0_14:\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "jne .LFUN_000460e0_15\n\t"
      "movb 0x5aca4f, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000460e0_25\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x4(%%esi), %%dx\n\t"
      "pushl $1\n\t"
      "pushl %%edx\n\t"
      "call *%[c1a67b0]\n\t"
      "pushl %%eax\n\t"
      "pushl $0x25a1dc\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "pushl %%eax\n\t"
      "leal -0x418(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c8dc30]\n\t"
      "addl $0x1c, %%esp\n\t"
      "jmp .LFUN_000460e0_25\n\t"
      ".LFUN_000460e0_15:\n\t"
      "pushl %%eax\n\t"
      "call *%[c43270]\n\t"
      "addl $4, %%esp\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .LFUN_000460e0_20\n\t"
      "movswl -0x14(%%ebp), %%ecx\n\t"
      "movswl %%ax, %%edi\n\t"
      "movl 0x331f14, %%eax\n\t"
      "leal (%%edi,%%ecx,2), %%edx\n\t"
      "leal (%%eax,%%edx,8), %%ebx\n\t"
      "call *%[gtime]\n\t"
      "movl %%eax, %%ecx\n\t"
      "movl (%%ebx), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "movl %%ecx, -0x18(%%ebp)\n\t"
      "je .LFUN_000460e0_17\n\t"
      "subl %%eax, %%ecx\n\t"
      "movl %%ecx, -0x10(%%ebp)\n\t"
      "fildl -0x10(%%ebp)\n\t"
      "fmuls 0x25620c\n\t"
      "fsts -0xc(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_000460e0_16\n\t"
      "movl $0, -0xc(%%ebp)\n\t"
      "jmp .LFUN_000460e0_17\n\t"
      ".LFUN_000460e0_16:\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_000460e0_17\n\t"
      "movl $0x3f800000, -0xc(%%ebp)\n\t"
      ".LFUN_000460e0_17:\n\t"
      "call *%[cfff80]\n\t"
      "testw %%ax, %%ax\n\t"
      "jne .LFUN_000460e0_18\n\t"
      "movb 0x5aca46, %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_000460e0_20\n\t"
      ".LFUN_000460e0_18:\n\t"
      "movl 0x4(%%ebx), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_000460e0_20\n\t"
      "subl -0x18(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jle .LFUN_000460e0_20\n\t"
      "movb 0x5aca4f, %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "je .LFUN_000460e0_19\n\t"
      "movl 0x2c8d6c(,%%edi,8), %%ecx\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x4(%%esi), %%dx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl $1\n\t"
      "pushl %%edx\n\t"
      "call *%[c1a67b0]\n\t"
      "addl $8, %%esp\n\t"
      "pushl %%eax\n\t"
      "pushl $0x25a1c8\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "pushl %%eax\n\t"
      "leal -0x418(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c8dc30]\n\t"
      "addl $0x1c, %%esp\n\t"
      ".LFUN_000460e0_19:\n\t"
      "movl $0xffffffff, -0x8(%%ebp)\n\t"
      "jmp .LFUN_000460e0_25\n\t"
      ".LFUN_000460e0_20:\n\t"
      "movb 0x5aca4f, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000460e0_24\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x4(%%esi), %%cx\n\t"
      "pushl $1\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1a67b0]\n\t"
      "pushl %%eax\n\t"
      "pushl $0x25a1b4\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "pushl %%eax\n\t"
      "leal -0x418(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "jmp .LFUN_000460e0_23\n\t"
      ".LFUN_000460e0_21:\n\t"
      "movb 0x5aca4f, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000460e0_24\n\t"
      "flds 0x12(%%esi)\n\t"
      "subl $0x10, %%esp\n\t"
      "xorl %%eax, %%eax\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "movw 0x4(%%esi), %%ax\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $1\n\t"
      "pushl %%eax\n\t"
      "call *%[c1a67b0]\n\t"
      "addl $8, %%esp\n\t"
      "pushl %%eax\n\t"
      "pushl $0x25a1a0\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "pushl %%eax\n\t"
      "leal -0x418(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c8dc30]\n\t"
      "addl $0x24, %%esp\n\t"
      "jmp .LFUN_000460e0_24\n\t"
      ".LFUN_000460e0_22:\n\t"
      "movb 0x5aca4f, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000460e0_24\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x4(%%esi), %%dx\n\t"
      "pushl $1\n\t"
      "pushl %%edx\n\t"
      "call *%[c1a67b0]\n\t"
      "pushl %%eax\n\t"
      "pushl $0x25a188\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "pushl %%eax\n\t"
      "leal -0x418(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      ".LFUN_000460e0_23:\n\t"
      "call *%[c8dc30]\n\t"
      "addl $0x1c, %%esp\n\t"
      ".LFUN_000460e0_24:\n\t"
      "cmpl $-1, -0x8(%%ebp)\n\t"
      "jne .LFUN_000460e0_26\n\t"
      ".LFUN_000460e0_25:\n\t"
      "movl -0x14(%%ebp), %%ecx\n\t"
      "addl $0x24, %%esi\n\t"
      "incl %%ecx\n\t"
      "cmpw $-1, -0x2(%%esi)\n\t"
      "movl %%ecx, -0x14(%%ebp)\n\t"
      "jne .LFUN_000460e0_3\n\t"
      ".LFUN_000460e0_26:\n\t"
      "movb 0x5aca4f, %%al\n\t"
      "testb %%al, %%al\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "je .LFUN_000460e0_27\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_000460e0_27\n\t"
      "leal -0x418(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_000460e0_27:\n\t"
      "popl %%edi\n\t"
      ".LFUN_000460e0_28:\n\t"
      "movl 0x18(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_000460e0_29\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "movl %%edx, (%%eax)\n\t"
      ".LFUN_000460e0_29:\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c1a67b0] "m"(b460e0_c1a67b0), [c1d90f0] "m"(b460e0_c1d90f0), [c1cb990] "m"(b460e0_c1cb990), [c8dc30] "m"(b460e0_c8dc30), [gseed] "m"(b460e0_gseed), [rmreal] "m"(b460e0_rmreal), [cfff80] "m"(b460e0_cfff80), [get] "m"(b460e0_get), [tryget] "m"(b460e0_tryget), [c458f0] "m"(b460e0_c458f0), [c8d9d0] "m"(b460e0_c8d9d0), [c43270] "m"(b460e0_c43270), [gtime] "m"(b460e0_gtime), [c8f390] "m"(b460e0_c8f390)
      : "memory");
}
#else
#error "FUN_000460e0: clang naked draft required"
#endif


/* FUN_00046530 (0x46530) — restored pre-naked C. */
void FUN_00046530(int unit_handle, uint16_t priority, uint16_t type, int unk,
                  int unk2, void *comm_data)
{
  FUN_00044fd0(unit_handle, priority, type, comm_data);
  (void)unk;
  (void)unk2;
}

/* FUN_00046b60 (0x46b60) — readable C lift. */
char FUN_00046b60(int16_t conversation_index, char allow_finish)
{
  char *scenario;
  int handle;
  char began;
  char flag;

  scenario = (char *)global_scenario_get();
  if (conversation_index < 0 ||
      (int)conversation_index >= *(int *)(scenario + 0x468))
    return 0;

  handle = FUN_00043740(conversation_index, allow_finish);
  if (*(char *)0x5aca5f) {
    console_printf(
        0,
        (const char *)0x25a3b8,
        tag_block_get_element(scenario + 0x468, (int)conversation_index, 0x74));
  }
  if (handle == -1) {
    error(2, (const char *)0x25a360, 0x80);
    return 0;
  }

  flag = 0;
  began = ai_conversation_begin(handle, &flag);
  if (began) {
    if (*(char *)0x5aca5f) {
      console_printf(
          0,
          (const char *)0x25a344,
          tag_block_get_element(scenario + 0x468, (int)conversation_index, 0x74));
    }
    return 1;
  }
  if (flag) {
    if (*(char *)0x5aca5f) {
      console_printf(
          0,
          (const char *)0x25a308,
          tag_block_get_element(scenario + 0x468, (int)conversation_index, 0x74));
    }
    return 1;
  }
  if (*(char *)0x5aca5f) {
    console_printf(
        0,
        (const char *)0x25a2c0,
        tag_block_get_element(scenario + 0x468, (int)conversation_index, 0x74));
  }
  ai_conversation_finish(handle, 1, 0);
  return 0;
}

/* ai_conversation_update (0x46cb0) — readable C lift (restored pre-naked). */


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


/* FUN_00046f10 (0x46f10) — Capstone tip: speech type not in [0,0x39) → assert. */
void FUN_00046f10(int16_t type, int unit_handle, int param3, int param4, int16_t param5, int16_t param6, int16_t param7)
{
  (void)unit_handle; (void)param3; (void)param4; (void)param5; (void)param6; (void)param7;
  FUN_001d90e0();
  game_time_get();
  if (type < 0 || type >= 0x39) {
    display_assert((const char *)0x25a960, (const char *)0x2599b4, 0x34e, true);
    system_exit(-1);
  }
}


/* --- ai_communication.obj orphan shells (2026-07-26) --- */

/* ai_debug_initialize (0x48e90) — readable C lift. */
void ai_debug_initialize(void)
{
  csmemset((void *)0x5ac9c0, 0, 0x85b2c);
  *(int *)0x5ac9f8 = -1;
  *(int *)0x5ac9f4 = -1;
  *(int *)0x5acab4 = 1;
  *(char *)0x5aca65 = 1;

  if (!*(void **)0x331f58)
    *(void **)0x331f58 = debug_malloc(0x657c00, false, (const char *)0x25ab74, 0x93);

  if (!*(void **)0x331f5c)
    *(void **)0x331f5c = debug_malloc(0x394f80, false, (const char *)0x25ab74, 0x94);

  if (!*(void **)0x331f58 || !*(void **)0x331f5c) {
    display_assert((const char *)0x25ab48, (const char *)0x25ab74, 0x96, true);
    system_exit(-1);
  }
}

