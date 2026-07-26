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

/* ai_communication_initialize (0x42a30) — XBE naked draft (batch 85). */
#if defined(__clang__)
static void * (*const b42a30_c1bfbf0)(const char *name, const char *a2, int size) = game_state_malloc;
static void (*const b42a30_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b42a30_exitfn)(int) = system_exit;
static data_t * (*const b42a30_c1bfe10)(char *name, __int16 maximum_count, __int16 size) = game_state_data_new;

__attribute__((naked, noinline))
void ai_communication_initialize(void)
{
  __asm__ volatile(
      "xorw %%cx, %%cx\n\t"
      "movl $0x257e48, %%eax\n\t"
      "jmp .Lai_communication_initialize_1\n\t"
      "leal (%%ebx), %%ebx\n\t"
      ".Lai_communication_initialize_1:\n\t"
      "addl $0x28, %%eax\n\t"
      "incw %%cx\n\t"
      "cmpw $-1, (%%eax)\n\t"
      "jne .Lai_communication_initialize_1\n\t"
      "movl 0x331f0c, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "movw %%cx, 0x331f08\n\t"
      "jne .Lai_communication_initialize_2\n\t"
      "movswl %%cx, %%eax\n\t"
      "shll $4, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0\n\t"
      "pushl $0x2599dc\n\t"
      "call *%[c1bfbf0]\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%eax, 0x331f0c\n\t"
      "jne .Lai_communication_initialize_2\n\t"
      "pushl $1\n\t"
      "pushl $0x286\n\t"
      "pushl $0x2599b4\n\t"
      "pushl $0x259968\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lai_communication_initialize_2:\n\t"
      "xorw %%cx, %%cx\n\t"
      "movl $0x258eb0, %%eax\n\t"
      ".Lai_communication_initialize_3:\n\t"
      "addl $0x24, %%eax\n\t"
      "incw %%cx\n\t"
      "cmpw $-1, (%%eax)\n\t"
      "jne .Lai_communication_initialize_3\n\t"
      "movl 0x331f14, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "movw %%cx, 0x331f10\n\t"
      "jne .Lai_communication_initialize_4\n\t"
      "movswl %%cx, %%ecx\n\t"
      "shll $4, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0\n\t"
      "pushl $0x259948\n\t"
      "call *%[c1bfbf0]\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%eax, 0x331f14\n\t"
      "jne .Lai_communication_initialize_4\n\t"
      "pushl $1\n\t"
      "pushl $0x293\n\t"
      "pushl $0x2599b4\n\t"
      "pushl $0x259900\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lai_communication_initialize_4:\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "xorl %%edi, %%edi\n\t"
      "movl $0x632500, %%esi\n\t"
      "jmp .Lai_communication_initialize_5\n\t"
      "leal (%%esp), %%esp\n\t"
      "movl %%edi, %%edi\n\t"
      ".Lai_communication_initialize_5:\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw $0xffff, (%%esi)\n\t"
      "movl $0x257e48, %%ecx\n\t"
      "xorl %%eax, %%eax\n\t"
      "movl %%edi, %%edi\n\t"
      ".Lai_communication_initialize_6:\n\t"
      "cmpw %%di, %%ax\n\t"
      "je .Lai_communication_initialize_7\n\t"
      "movw 0x28(%%ecx), %%ax\n\t"
      "addl $0x28, %%ecx\n\t"
      "incl %%edx\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "jne .Lai_communication_initialize_6\n\t"
      "jmp .Lai_communication_initialize_8\n\t"
      ".Lai_communication_initialize_7:\n\t"
      "movw %%dx, (%%esi)\n\t"
      ".Lai_communication_initialize_8:\n\t"
      "incl %%edi\n\t"
      "addl $2, %%esi\n\t"
      "cmpw $0x39, %%di\n\t"
      "jl .Lai_communication_initialize_5\n\t"
      "pushl $0x64\n\t"
      "pushl $8\n\t"
      "pushl $0x2598f0\n\t"
      "call *%[c1bfe10]\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "popl %%edi\n\t"
      "movl %%eax, 0x6324ec\n\t"
      "popl %%esi\n\t"
      "jne .Lai_communication_initialize_9\n\t"
      "pushl $1\n\t"
      "pushl $0x2a8\n\t"
      "pushl $0x2599b4\n\t"
      "pushl $0x2598dc\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lai_communication_initialize_9:\n\t"
      "ret\n\t"
      :
      : [c1bfbf0] "m"(b42a30_c1bfbf0), [assert] "m"(b42a30_assert), [exitfn] "m"(b42a30_exitfn), [c1bfe10] "m"(b42a30_c1bfe10)
      : "memory");
}
#else
#error "ai_communication_initialize: clang naked draft required"
#endif


/* ai_communication_dispose: no-op stub.
 * Called from ai_dispose (0x3f6f0). Binary is a single RET instruction. */
void ai_communication_dispose(void)
{
}

/* ai_communication_initialize_for_new_map (0x42b90) — XBE naked draft (batch 87). */
#if defined(__clang__)
static void *(*const b42b90_memset)(void *, int, unsigned int) = csmemset;
static void (*const b42b90_c119b20)(data_t *data) = data_delete_all;

__attribute__((naked, noinline))
void ai_communication_initialize_for_new_map(void)
{
  __asm__ volatile(
      "movl 0x632574, %%eax\n\t"
      "pushl %%edi\n\t"
      "movb $1, 0x10(%%eax)\n\t"
      "movl 0x632574, %%ecx\n\t"
      "pushl $8\n\t"
      "addl $0x14, %%ecx\n\t"
      "pushl $0\n\t"
      "pushl %%ecx\n\t"
      "call *%[memset]\n\t"
      "movl 0x632574, %%edx\n\t"
      "pushl $8\n\t"
      "addl $0x1c, %%edx\n\t"
      "pushl $0\n\t"
      "pushl %%edx\n\t"
      "call *%[memset]\n\t"
      "movl 0x632574, %%eax\n\t"
      "pushl $8\n\t"
      "addl $0x24, %%eax\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "call *%[memset]\n\t"
      "movswl 0x331f08, %%eax\n\t"
      "shll $1, %%eax\n\t"
      "addl $0x24, %%esp\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "orl $0xffffffff, %%edx\n\t"
      "testl %%eax, %%eax\n\t"
      "jle .Lai_communication_initialize_for_new_map_2\n\t"
      "xorl %%eax, %%eax\n\t"
      "leal (%%esp), %%esp\n\t"
      ".Lai_communication_initialize_for_new_map_1:\n\t"
      "movl 0x331f0c, %%edi\n\t"
      "movl %%edx, 0x4(%%edi,%%eax,8)\n\t"
      "movl 0x331f0c, %%edi\n\t"
      "movl %%edx, (%%edi,%%eax,8)\n\t"
      "movswl 0x331f08, %%edi\n\t"
      "incl %%ecx\n\t"
      "movswl %%cx, %%eax\n\t"
      "shll $1, %%edi\n\t"
      "cmpl %%edi, %%eax\n\t"
      "jl .Lai_communication_initialize_for_new_map_1\n\t"
      ".Lai_communication_initialize_for_new_map_2:\n\t"
      "movswl 0x331f10, %%eax\n\t"
      "shll $1, %%eax\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "testl %%eax, %%eax\n\t"
      "jle .Lai_communication_initialize_for_new_map_4\n\t"
      "xorl %%eax, %%eax\n\t"
      "jmp .Lai_communication_initialize_for_new_map_3\n\t"
      "leal (%%esp), %%esp\n\t"
      "movl %%edi, %%edi\n\t"
      ".Lai_communication_initialize_for_new_map_3:\n\t"
      "movl 0x331f14, %%edi\n\t"
      "movl %%edx, 0x4(%%edi,%%eax,8)\n\t"
      "movl 0x331f14, %%edi\n\t"
      "movl %%edx, (%%edi,%%eax,8)\n\t"
      "movswl 0x331f10, %%edi\n\t"
      "incl %%ecx\n\t"
      "movswl %%cx, %%eax\n\t"
      "shll $1, %%edi\n\t"
      "cmpl %%edi, %%eax\n\t"
      "jl .Lai_communication_initialize_for_new_map_3\n\t"
      ".Lai_communication_initialize_for_new_map_4:\n\t"
      "movl 0x632574, %%ecx\n\t"
      "movw $0, 0x2c(%%ecx)\n\t"
      "movl 0x632574, %%edx\n\t"
      "movw $0, 0x2e(%%edx)\n\t"
      "movl 0x632574, %%eax\n\t"
      "pushl $0x100\n\t"
      "addl $0x30, %%eax\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "call *%[memset]\n\t"
      "movl 0x6324ec, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c119b20]\n\t"
      "addl $0x10, %%esp\n\t"
      "popl %%edi\n\t"
      "ret\n\t"
      :
      : [memset] "m"(b42b90_memset), [c119b20] "m"(b42b90_c119b20)
      : "memory");
}
#else
#error "ai_communication_initialize_for_new_map: clang naked draft required"
#endif


/* ai_communication_dispose_from_old_map (0x42ca0) — XBE naked draft (batch 102). */
#if defined(__clang__)
static void (*const b42ca0_c119550)(data_t *data) = data_make_invalid;

__attribute__((naked, noinline))
void ai_communication_dispose_from_old_map(void)
{
  __asm__ volatile(
      "movl 0x6324ec, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c119550]\n\t"
      "popl %%ecx\n\t"
      "ret\n\t"
      :
      : [c119550] "m"(b42ca0_c119550)
      : "memory");
}
#else
#error "ai_communication_dispose_from_old_map: clang naked draft required"
#endif


/* ai_conversation_advance (0x43520) — XBE naked draft (batch 91). */
#if defined(__clang__)
static void (*const b43520_c1197b0)(data_iter_t *iter, data_t *data) = data_iterator_new;
static void * (*const b43520_c119810)(data_iter_t *iterator) = data_iterator_next;
static scenario_t * (*const b43520_c18e380)(void) = global_scenario_get;
static void *(*const b43520_elem)(void *, int, int) = tag_block_get_element;
static void (*const b43520_cff4d0)(int channel, const char *format, ...) = console_printf;

__attribute__((naked, noinline))
void ai_conversation_advance(short param_1 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x10, %%esp\n\t"
      "movl 0x6324ec, %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "leal -0x10(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1197b0]\n\t"
      "leal -0x10(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c119810]\n\t"
      "movl %%eax, %%edi\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%edi, %%edi\n\t"
      "je .Lai_conversation_advance_4\n\t"
      "pushl %%esi\n\t"
      "movw 0x8(%%ebp), %%si\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".Lai_conversation_advance_1:\n\t"
      "cmpw %%si, 0x2(%%edi)\n\t"
      "jne .Lai_conversation_advance_3\n\t"
      "movb 0x5aca5f, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lai_conversation_advance_2\n\t"
      "movswl %%si, %%eax\n\t"
      "pushl $0x74\n\t"
      "pushl %%eax\n\t"
      "call *%[c18e380]\n\t"
      "addl $0x468, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "pushl %%eax\n\t"
      "pushl $0x259aa0\n\t"
      "pushl $0\n\t"
      "call *%[cff4d0]\n\t"
      "addl $0x18, %%esp\n\t"
      ".Lai_conversation_advance_2:\n\t"
      "movb $1, 0x9(%%edi)\n\t"
      ".Lai_conversation_advance_3:\n\t"
      "leal -0x10(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c119810]\n\t"
      "movl %%eax, %%edi\n\t"
      "addl $4, %%esp\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .Lai_conversation_advance_1\n\t"
      "popl %%esi\n\t"
      ".Lai_conversation_advance_4:\n\t"
      "popl %%edi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c1197b0] "m"(b43520_c1197b0), [c119810] "m"(b43520_c119810), [c18e380] "m"(b43520_c18e380), [elem] "m"(b43520_elem), [cff4d0] "m"(b43520_cff4d0)
      : "memory");
}
#else
#error "ai_conversation_advance: clang naked draft required"
#endif

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


/* ai_conversation_find_participant (0x447d0) — XBE naked draft (batch 104). */
#if defined(__clang__)
static void *(*const b447d0_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static scenario_t * (*const b447d0_c18e380)(void) = global_scenario_get;
static void *(*const b447d0_elem)(void *, int, int) = tag_block_get_element;
static void (*const b447d0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b447d0_exitfn)(int) = system_exit;
static void *(*const b447d0_memset)(void *, int, unsigned int) = csmemset;
static int (*const b447d0_c140720)(int16_t index) = object_name_list_get_handle;
static void (*const b447d0_c54680)(unsigned int combined_index, void *iter) = FUN_00054680;
static void (*const b447d0_c59b10)(void *iter, char flag) = encounter_iterator_next;
static void *(*const b447d0_tryget)(int, int) = object_try_and_get_and_verify_type;
static int (*const b447d0_c54750)(void *iter) = FUN_00054750;
static int (*const b447d0_c59b50)(void *iter) = FUN_00059b50;
static float (*const b447d0_c441c0)(int unit, char use_teams, int *out_unit, int *out_handle) = ai_communication_get_player_rating;
static void *(*const b447d0_get)(int, int) = object_get_and_verify_type;
static bool (*const b447d0_ca7a30)(int16_t team_a, int16_t team_b) = game_allegiance_get_team_is_friendly;
static int *(*const b447d0_gseed)(void) = get_global_random_seed_address;
static int16_t (*const b447d0_c10b2d0)(unsigned int *seed, int16_t min, int16_t max) = random_range;
static void (*const b447d0_c54220)(unsigned int combined_index, void *scenario, char *buffer, int buffer_size) = FUN_00054220;
static char * (*const b447d0_c8dff0)(char *destination, const char *source) = csstrcpy;
static void (*const b447d0_cff4d0)(int channel, const char *format, ...) = console_printf;
static int (*const b447d0_c8df60)(const char *s1) = csstrlen;
static int (*const b447d0_c1d90f0)(char *buffer, const char *format, ...) = crt_sprintf;

__attribute__((naked, noinline))
void ai_conversation_find_participant(int conversation_handle __attribute__((unused)), int16_t participant_index __attribute__((unused)), char *found_out __attribute__((unused)), char *required_out __attribute__((unused)), float *rating_out __attribute__((unused)), int *handle_out __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x41c, %%esp\n\t"
      "movl 0x6324ec, %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movswl 0x2(%%eax), %%edx\n\t"
      "addl $8, %%esp\n\t"
      "pushl $0x74\n\t"
      "pushl %%edx\n\t"
      "movl %%eax, -0x48(%%ebp)\n\t"
      "call *%[c18e380]\n\t"
      "addl $0x468, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl %%eax, %%edi\n\t"
      "movswl 0x8(%%ebp), %%eax\n\t"
      "pushl $0x54\n\t"
      "pushl %%eax\n\t"
      "leal 0x50(%%edi), %%esi\n\t"
      "pushl %%esi\n\t"
      "movl %%edi, -0x40(%%ebp)\n\t"
      "call *%[elem]\n\t"
      "movl %%eax, %%ebx\n\t"
      "orl $0xffffffff, %%eax\n\t"
      "addl $0x18, %%esp\n\t"
      "testl %%edi, %%edi\n\t"
      "movl %%ebx, -0x1c(%%ebp)\n\t"
      "movl %%eax, -0x38(%%ebp)\n\t"
      "movl %%eax, -0x54(%%ebp)\n\t"
      "movl $0x7f7fffff, -0x4c(%%ebp)\n\t"
      "movb $0, -0x5(%%ebp)\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "jne .Lai_conversation_find_participant_1\n\t"
      "pushl $1\n\t"
      "pushl $0x127a\n\t"
      "pushl $0x2599b4\n\t"
      "pushl $0x259f04\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lai_conversation_find_participant_1:\n\t"
      "cmpw $1, 0x4(%%ebx)\n\t"
      "jne .Lai_conversation_find_participant_3\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "movb -0x1(%%ebp), %%bl\n\t"
      "movl $0, -0x38(%%ebp)\n\t"
      ".Lai_conversation_find_participant_2:\n\t"
      "movswl 0x8(%%ebp), %%ecx\n\t"
      "movl -0x48(%%ebp), %%eax\n\t"
      "movl 0x14(%%eax), %%esi\n\t"
      "movl $1, %%edx\n\t"
      "shll %%cl, %%edx\n\t"
      "orl %%edx, %%esi\n\t"
      "movl -0x54(%%ebp), %%edx\n\t"
      "movl %%esi, 0x14(%%eax)\n\t"
      "movw -0x38(%%ebp), %%si\n\t"
      "movl %%edx, 0x28(%%eax,%%ecx,4)\n\t"
      "movw %%si, 0x18(%%eax,%%ecx,2)\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lai_conversation_find_participant_64\n\t"
      "cmpl $-1, %%edx\n\t"
      "jmp .Lai_conversation_find_participant_63\n\t"
      ".Lai_conversation_find_participant_3:\n\t"
      "xorl %%edi, %%edi\n\t"
      "pushl $0xe\n\t"
      "leal -0x34(%%ebp), %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "movb $0, -0x4(%%ebp)\n\t"
      "movb $0, -0x2(%%ebp)\n\t"
      "movb $0, -0x3(%%ebp)\n\t"
      "movl $0xffffffff, -0x44(%%ebp)\n\t"
      "movl $0, -0x50(%%ebp)\n\t"
      "movl %%edi, -0x3c(%%ebp)\n\t"
      "call *%[memset]\n\t"
      "movw 0x4(%%ebx), %%ax\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpw $6, %%ax\n\t"
      "je .Lai_conversation_find_participant_4\n\t"
      "cmpw $7, %%ax\n\t"
      "jne .Lai_conversation_find_participant_5\n\t"
      ".Lai_conversation_find_participant_4:\n\t"
      "movb $1, -0x4(%%ebp)\n\t"
      ".Lai_conversation_find_participant_5:\n\t"
      "cmpl %%edi, (%%esi)\n\t"
      "movl %%edi, -0x20(%%ebp)\n\t"
      "movl %%edi, -0x14(%%ebp)\n\t"
      "jle .Lai_conversation_find_participant_9\n\t"
      "xorl %%eax, %%eax\n\t"
      "nop\n\t"
      ".Lai_conversation_find_participant_6:\n\t"
      "movl -0x48(%%ebp), %%ecx\n\t"
      "movl 0x28(%%ecx,%%eax,4), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lai_conversation_find_participant_8\n\t"
      "movl 0x6325a4, %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%edx\n\t"
      "call *%[dget]\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $8, -0x20(%%ebp)\n\t"
      "movl %%eax, %%edi\n\t"
      "jl .Lai_conversation_find_participant_7\n\t"
      "pushl $1\n\t"
      "pushl $0x12ad\n\t"
      "pushl $0x2599b4\n\t"
      "pushl $0x259ec8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lai_conversation_find_participant_7:\n\t"
      "movl -0x20(%%ebp), %%ecx\n\t"
      "movswl %%cx, %%eax\n\t"
      "leal (%%eax,%%eax,2), %%eax\n\t"
      "leal -0x11c(%%ebp,%%eax,4), %%edx\n\t"
      "addl $0x12c, %%edi\n\t"
      "movl (%%edi), %%eax\n\t"
      "movl %%eax, (%%edx)\n\t"
      "movl 0x4(%%edi), %%eax\n\t"
      "movl %%eax, 0x4(%%edx)\n\t"
      "movl 0x8(%%edi), %%eax\n\t"
      "incl %%ecx\n\t"
      "movl %%eax, 0x8(%%edx)\n\t"
      "movl %%ecx, -0x20(%%ebp)\n\t"
      ".Lai_conversation_find_participant_8:\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "movl (%%esi), %%ecx\n\t"
      "incl %%eax\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "movswl %%ax, %%eax\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jl .Lai_conversation_find_participant_6\n\t"
      "xorl %%edi, %%edi\n\t"
      ".Lai_conversation_find_participant_9:\n\t"
      "cmpw %%di, -0x20(%%ebp)\n\t"
      "sete -0x5c(%%ebp)\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x8(%%ebx), %%ax\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .Lai_conversation_find_participant_10\n\t"
      "pushl %%eax\n\t"
      "call *%[c140720]\n\t"
      "addl $4, %%esp\n\t"
      "movl %%eax, -0x44(%%ebp)\n\t"
      "movb $1, -0x2(%%ebp)\n\t"
      "jmp .Lai_conversation_find_participant_13\n\t"
      ".Lai_conversation_find_participant_10:\n\t"
      "movl 0x44(%%ebx), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lai_conversation_find_participant_11\n\t"
      "leal -0xa0(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "call *%[c54680]\n\t"
      "movb $1, -0x3(%%ebp)\n\t"
      "jmp .Lai_conversation_find_participant_12\n\t"
      ".Lai_conversation_find_participant_11:\n\t"
      "leal -0xbc(%%ebp), %%edx\n\t"
      "pushl $1\n\t"
      "pushl %%edx\n\t"
      "call *%[c59b10]\n\t"
      ".Lai_conversation_find_participant_12:\n\t"
      "addl $8, %%esp\n\t"
      ".Lai_conversation_find_participant_13:\n\t"
      "movb -0x2(%%ebp), %%al\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "testb %%al, %%al\n\t"
      "movl $0, -0xc(%%ebp)\n\t"
      "movl $0x7f7fffff, -0x58(%%ebp)\n\t"
      "movl %%ebx, -0x18(%%ebp)\n\t"
      "je .Lai_conversation_find_participant_15\n\t"
      "movl -0x44(%%ebp), %%eax\n\t"
      "pushl $3\n\t"
      "pushl %%eax\n\t"
      "call *%[tryget]\n\t"
      "orl $0xffffffff, %%edi\n\t"
      "addl $8, %%esp\n\t"
      "xorl %%esi, %%esi\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%edi, -0x14(%%ebp)\n\t"
      "je .Lai_conversation_find_participant_14\n\t"
      "movl 0x1a4(%%eax), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lai_conversation_find_participant_14\n\t"
      "movl 0x6325a4, %%ecx\n\t"
      "movl %%eax, %%edi\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "movl %%edi, -0x14(%%ebp)\n\t"
      "call *%[dget]\n\t"
      "addl $8, %%esp\n\t"
      "movl %%eax, %%esi\n\t"
      ".Lai_conversation_find_participant_14:\n\t"
      "movl $0xffffffff, -0x44(%%ebp)\n\t"
      "jmp .Lai_conversation_find_participant_18\n\t"
      ".Lai_conversation_find_participant_15:\n\t"
      "movb -0x3(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lai_conversation_find_participant_16\n\t"
      "leal -0xa0(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c54750]\n\t"
      "movl -0x90(%%ebp), %%edi\n\t"
      "jmp .Lai_conversation_find_participant_17\n\t"
      ".Lai_conversation_find_participant_16:\n\t"
      "leal -0xbc(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c59b50]\n\t"
      "movl -0xa8(%%ebp), %%edi\n\t"
      ".Lai_conversation_find_participant_17:\n\t"
      "addl $4, %%esp\n\t"
      "movl %%eax, %%esi\n\t"
      "movl %%edi, -0x14(%%ebp)\n\t"
      ".Lai_conversation_find_participant_18:\n\t"
      "testl %%esi, %%esi\n\t"
      "je .Lai_conversation_find_participant_53\n\t"
      "movl -0x3c(%%ebp), %%ecx\n\t"
      "movl 0x18(%%esi), %%eax\n\t"
      "incl %%ecx\n\t"
      "cmpl $-1, %%eax\n\t"
      "movl %%ecx, -0x3c(%%ebp)\n\t"
      "jne .Lai_conversation_find_participant_19\n\t"
      "incw -0x34(%%ebp)\n\t"
      "jmp .Lai_conversation_find_participant_13\n\t"
      ".Lai_conversation_find_participant_19:\n\t"
      "movw 0x4(%%esi), %%cx\n\t"
      "movl -0x1c(%%ebp), %%edx\n\t"
      "cmpw 0x6(%%edx), %%cx\n\t"
      "je .Lai_conversation_find_participant_20\n\t"
      "incw -0x32(%%ebp)\n\t"
      "jmp .Lai_conversation_find_participant_13\n\t"
      ".Lai_conversation_find_participant_20:\n\t"
      "movl -0x40(%%ebp), %%eax\n\t"
      "movl 0x50(%%eax), %%edx\n\t"
      "addl $0x50, %%eax\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "testl %%edx, %%edx\n\t"
      "jle .Lai_conversation_find_participant_23\n\t"
      "xorl %%eax, %%eax\n\t"
      "movl %%edi, %%edi\n\t"
      ".Lai_conversation_find_participant_21:\n\t"
      "movl -0x48(%%ebp), %%ebx\n\t"
      "cmpl 0x28(%%ebx,%%eax,4), %%edi\n\t"
      "je .Lai_conversation_find_participant_22\n\t"
      "incl %%ecx\n\t"
      "movswl %%cx, %%eax\n\t"
      "cmpl %%edx, %%eax\n\t"
      "jl .Lai_conversation_find_participant_21\n\t"
      ".Lai_conversation_find_participant_22:\n\t"
      "movl -0x18(%%ebp), %%ebx\n\t"
      ".Lai_conversation_find_participant_23:\n\t"
      "movswl %%cx, %%eax\n\t"
      "cmpl %%edx, %%eax\n\t"
      "jge .Lai_conversation_find_participant_24\n\t"
      "incw -0x30(%%ebp)\n\t"
      "jmp .Lai_conversation_find_participant_13\n\t"
      ".Lai_conversation_find_participant_24:\n\t"
      "movl -0x5c(%%ebp), %%eax\n\t"
      "leal -0x58(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x60(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "movl 0x18(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c441c0]\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "movl -0x60(%%ebp), %%eax\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "jne .Lai_conversation_find_participant_25\n\t"
      "movb -0x4(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lai_conversation_find_participant_26\n\t"
      "incw -0x2e(%%ebp)\n\t"
      "movb $1, -0x5(%%ebp)\n\t"
      "jmp .Lai_conversation_find_participant_13\n\t"
      ".Lai_conversation_find_participant_25:\n\t"
      "movl -0x18(%%ebp), %%ecx\n\t"
      "pushl $3\n\t"
      "pushl %%eax\n\t"
      "movl %%ecx, -0xc(%%ebp)\n\t"
      "call *%[get]\n\t"
      "addl $8, %%esp\n\t"
      "movl %%eax, %%ebx\n\t"
      ".Lai_conversation_find_participant_26:\n\t"
      "movl -0x1c(%%ebp), %%edx\n\t"
      "movswl 0x4(%%edx), %%eax\n\t"
      "cmpl $7, %%eax\n\t"
      "ja .Lai_conversation_find_participant_32\n\t"
      "jmp *.Lai_conversation_find_participant_jt(,%%eax,4)\n\t"
      ".Lai_conversation_find_participant_27:\n\t"
      "testl %%ebx, %%ebx\n\t"
      "je .Lai_conversation_find_participant_32\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x68(%%ebx), %%ax\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x3e(%%esi), %%cx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[ca7a30]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      ".Lai_conversation_find_participant_28:\n\t"
      "je .Lai_conversation_find_participant_32\n\t"
      ".Lai_conversation_find_participant_29:\n\t"
      "incw -0x2c(%%ebp)\n\t"
      "jmp .Lai_conversation_find_participant_13\n\t"
      ".Lai_conversation_find_participant_30:\n\t"
      "testl %%ebx, %%ebx\n\t"
      "je .Lai_conversation_find_participant_29\n\t"
      "movl 0xcc(%%ebx), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lai_conversation_find_participant_29\n\t"
      "cmpl %%eax, 0x158(%%esi)\n\t"
      "jne .Lai_conversation_find_participant_29\n\t"
      "movb 0x161(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lai_conversation_find_participant_32\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fadds 0x2533c8\n\t"
      ".Lai_conversation_find_participant_31:\n\t"
      "fstps -0xc(%%ebp)\n\t"
      ".Lai_conversation_find_participant_32:\n\t"
      "movb -0x5c(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lai_conversation_find_participant_35\n\t"
      "movb -0x4(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lai_conversation_find_participant_35\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fcomps 0x253f40\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lai_conversation_find_participant_35\n\t"
      "movl -0x40(%%ebp), %%edx\n\t"
      "flds 0x28(%%edx)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .Lai_conversation_find_participant_35\n\t"
      "incw -0x2a(%%ebp)\n\t"
      "movb $1, -0x5(%%ebp)\n\t"
      "jmp .Lai_conversation_find_participant_13\n\t"
      ".Lai_conversation_find_participant_33:\n\t"
      "cmpl $-1, 0x158(%%esi)\n\t"
      "jmp .Lai_conversation_find_participant_28\n\t"
      ".Lai_conversation_find_participant_34:\n\t"
      "movb 0x1c(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lai_conversation_find_participant_32\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fadds 0x2533ec\n\t"
      "jmp .Lai_conversation_find_participant_31\n\t"
      ".Lai_conversation_find_participant_35:\n\t"
      "movl -0x20(%%ebp), %%eax\n\t"
      "testw %%ax, %%ax\n\t"
      "jle .Lai_conversation_find_participant_39\n\t"
      "movl $0x7f7fffff, -0x24(%%ebp)\n\t"
      "leal -0x114(%%ebp), %%ecx\n\t"
      "movzwl %%ax, %%edx\n\t"
      "leal (%%ebx), %%ebx\n\t"
      ".Lai_conversation_find_participant_36:\n\t"
      "flds -0x8(%%ecx)\n\t"
      "fsubs 0x12c(%%esi)\n\t"
      "flds -0x4(%%ecx)\n\t"
      "fsubs 0x130(%%esi)\n\t"
      "flds (%%ecx)\n\t"
      "fsubs 0x134(%%esi)\n\t"
      "fld %%st(0)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fld %%st(3)\n\t"
      ".byte 0xd8, 0xcc\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fld %%st(2)\n\t"
      ".byte 0xd8, 0xcb\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fstp %%st(3)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "flds -0x24(%%ebp)\n\t"
      "fcomp %%st(1)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lai_conversation_find_participant_37\n\t"
      "fstps -0x24(%%ebp)\n\t"
      "jmp .Lai_conversation_find_participant_38\n\t"
      ".Lai_conversation_find_participant_37:\n\t"
      "fstp %%st(0)\n\t"
      ".Lai_conversation_find_participant_38:\n\t"
      "addl $0xc, %%ecx\n\t"
      "decl %%edx\n\t"
      "jne .Lai_conversation_find_participant_36\n\t"
      "flds -0x24(%%ebp)\n\t"
      "fcomps 0x259ec4\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lai_conversation_find_participant_39\n\t"
      "flds -0x24(%%ebp)\n\t"
      "fsqrt\n\t"
      "fsubs 0x2533ec\n\t"
      "fmuls 0x259ec0\n\t"
      "fsubrs 0x2533c8\n\t"
      "fadds -0xc(%%ebp)\n\t"
      "fstps -0xc(%%ebp)\n\t"
      ".Lai_conversation_find_participant_39:\n\t"
      "movl 0x18(%%esi), %%eax\n\t"
      "pushl $3\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movw 0x6e(%%eax), %%cx\n\t"
      "movw %%cx, -0x18(%%ebp)\n\t"
      "movl -0x18(%%ebp), %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "xorl %%edi, %%edi\n\t"
      "orl $0xffffffff, %%ebx\n\t"
      "movb $0, -0xd(%%ebp)\n\t"
      "xorl %%esi, %%esi\n\t"
      "leal (%%ebx), %%ebx\n\t"
      ".Lai_conversation_find_participant_40:\n\t"
      "movl -0x1c(%%ebp), %%eax\n\t"
      "movswl %%si, %%edx\n\t"
      "movw 0x18(%%eax,%%edx,2), %%ax\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .Lai_conversation_find_participant_43\n\t"
      "cmpw %%cx, %%ax\n\t"
      "je .Lai_conversation_find_participant_46\n\t"
      "testw %%ax, %%ax\n\t"
      "jne .Lai_conversation_find_participant_41\n\t"
      "movl %%esi, %%ebx\n\t"
      "movb $1, -0xd(%%ebp)\n\t"
      "jmp .Lai_conversation_find_participant_43\n\t"
      ".Lai_conversation_find_participant_41:\n\t"
      "cmpw $0x64, %%cx\n\t"
      "jge .Lai_conversation_find_participant_43\n\t"
      "cmpw $0x64, %%ax\n\t"
      "jge .Lai_conversation_find_participant_43\n\t"
      "cmpw $6, %%di\n\t"
      "jl .Lai_conversation_find_participant_42\n\t"
      "pushl $1\n\t"
      "pushl $0x13af\n\t"
      "pushl $0x2599b4\n\t"
      "pushl $0x259e68\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "movl -0x18(%%ebp), %%ecx\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lai_conversation_find_participant_42:\n\t"
      "movswl %%di, %%edx\n\t"
      "movw %%si, -0x88(%%ebp,%%edx,2)\n\t"
      "incl %%edi\n\t"
      ".Lai_conversation_find_participant_43:\n\t"
      "incl %%esi\n\t"
      "cmpw $6, %%si\n\t"
      "jl .Lai_conversation_find_participant_40\n\t"
      "movb -0xd(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lai_conversation_find_participant_47\n\t"
      ".Lai_conversation_find_participant_44:\n\t"
      "cmpw $-1, %%bx\n\t"
      "jne .Lai_conversation_find_participant_45\n\t"
      "pushl $1\n\t"
      "pushl $0x13b8\n\t"
      "pushl $0x2599b4\n\t"
      "pushl $0x259e48\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lai_conversation_find_participant_45:\n\t"
      "flds -0xc(%%ebp)\n\t"
      "movl %%ebx, %%esi\n\t"
      "fadds 0x2533c4\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "jmp .Lai_conversation_find_participant_51\n\t"
      ".Lai_conversation_find_participant_46:\n\t"
      "movl %%esi, %%ebx\n\t"
      "jmp .Lai_conversation_find_participant_44\n\t"
      ".Lai_conversation_find_participant_47:\n\t"
      "testw %%di, %%di\n\t"
      "jle .Lai_conversation_find_participant_52\n\t"
      "cmpw $1, %%di\n\t"
      "jne .Lai_conversation_find_participant_48\n\t"
      "movl -0x88(%%ebp), %%esi\n\t"
      "jmp .Lai_conversation_find_participant_49\n\t"
      ".Lai_conversation_find_participant_48:\n\t"
      "pushl %%edi\n\t"
      "pushl $0\n\t"
      "call *%[gseed]\n\t"
      "pushl %%eax\n\t"
      "call *%[c10b2d0]\n\t"
      "movswl %%ax, %%eax\n\t"
      "movw -0x88(%%ebp,%%eax,2), %%si\n\t"
      "addl $0xc, %%esp\n\t"
      ".Lai_conversation_find_participant_49:\n\t"
      "testw %%si, %%si\n\t"
      "jl .Lai_conversation_find_participant_50\n\t"
      "cmpw $6, %%si\n\t"
      "jl .Lai_conversation_find_participant_51\n\t"
      ".Lai_conversation_find_participant_50:\n\t"
      "pushl $1\n\t"
      "pushl $0x13c7\n\t"
      "pushl $0x2599b4\n\t"
      "pushl $0x259dd8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lai_conversation_find_participant_51:\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fcomps -0x50(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lai_conversation_find_participant_13\n\t"
      "movl -0x14(%%ebp), %%ecx\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "movl -0x58(%%ebp), %%eax\n\t"
      "movl %%ecx, -0x54(%%ebp)\n\t"
      "movl %%edx, -0x50(%%ebp)\n\t"
      "movl %%eax, -0x4c(%%ebp)\n\t"
      "movl %%esi, -0x38(%%ebp)\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "jmp .Lai_conversation_find_participant_13\n\t"
      ".Lai_conversation_find_participant_52:\n\t"
      "incw -0x28(%%ebp)\n\t"
      "jmp .Lai_conversation_find_participant_13\n\t"
      ".Lai_conversation_find_participant_53:\n\t"
      "movb -0x1(%%ebp), %%bl\n\t"
      "testb %%bl, %%bl\n\t"
      "jne .Lai_conversation_find_participant_2\n\t"
      "movb 0x5aca5f, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lai_conversation_find_participant_62\n\t"
      "movl -0x1c(%%ebp), %%ecx\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x8(%%ecx), %%ax\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "movl $0x254384, %%edi\n\t"
      "jne .Lai_conversation_find_participant_54\n\t"
      "movw 0xa(%%ecx), %%ax\n\t"
      ".Lai_conversation_find_participant_54:\n\t"
      "testw %%ax, %%ax\n\t"
      "jl .Lai_conversation_find_participant_55\n\t"
      "movswl %%ax, %%esi\n\t"
      "call *%[c18e380]\n\t"
      "cmpl 0x204(%%eax), %%esi\n\t"
      "jge .Lai_conversation_find_participant_55\n\t"
      "pushl $0x24\n\t"
      "pushl %%esi\n\t"
      "call *%[c18e380]\n\t"
      "addl $0x204, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "addl $0xc, %%esp\n\t"
      "movl %%eax, %%edi\n\t"
      ".Lai_conversation_find_participant_55:\n\t"
      "movb -0x2(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lai_conversation_find_participant_56\n\t"
      "pushl $0x259dc4\n\t"
      "leal -0x21c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "jmp .Lai_conversation_find_participant_58\n\t"
      ".Lai_conversation_find_participant_56:\n\t"
      "movb -0x3(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "leal -0x21c(%%ebp), %%edx\n\t"
      "je .Lai_conversation_find_participant_57\n\t"
      "pushl $0x100\n\t"
      "pushl %%edx\n\t"
      "call *%[c18e380]\n\t"
      "pushl %%eax\n\t"
      "movl -0x1c(%%ebp), %%eax\n\t"
      "movl 0x44(%%eax), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c54220]\n\t"
      "addl $0x10, %%esp\n\t"
      "jmp .Lai_conversation_find_participant_59\n\t"
      ".Lai_conversation_find_participant_57:\n\t"
      "pushl $0x259db8\n\t"
      "pushl %%edx\n\t"
      ".Lai_conversation_find_participant_58:\n\t"
      "call *%[c8dff0]\n\t"
      "addl $8, %%esp\n\t"
      ".Lai_conversation_find_participant_59:\n\t"
      "movl -0x3c(%%ebp), %%esi\n\t"
      "movl -0x40(%%ebp), %%edx\n\t"
      "movswl %%si, %%eax\n\t"
      "pushl %%eax\n\t"
      "movswl 0x8(%%ebp), %%eax\n\t"
      "leal -0x21c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl $0x259d84\n\t"
      "pushl $0\n\t"
      "call *%[cff4d0]\n\t"
      "addl $0x1c, %%esp\n\t"
      "testw %%si, %%si\n\t"
      "jle .Lai_conversation_find_participant_62\n\t"
      "leal -0x41c(%%ebp), %%eax\n\t"
      "pushl $0x259d78\n\t"
      "pushl %%eax\n\t"
      "movl $0x256cd4, -0x7c(%%ebp)\n\t"
      "movl $0x259d6c, -0x78(%%ebp)\n\t"
      "movl $0x259d58, -0x74(%%ebp)\n\t"
      "movl $0x259d44, -0x70(%%ebp)\n\t"
      "movl $0x259d38, -0x6c(%%ebp)\n\t"
      "movl $0x259d28, -0x68(%%ebp)\n\t"
      "movl $0x259d14, -0x64(%%ebp)\n\t"
      "call *%[c8dff0]\n\t"
      "addl $8, %%esp\n\t"
      "leal -0x7c(%%ebp), %%edi\n\t"
      "leal -0x34(%%ebp), %%esi\n\t"
      "movl $7, %%ebx\n\t"
      ".Lai_conversation_find_participant_60:\n\t"
      "movw (%%esi), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "jle .Lai_conversation_find_participant_61\n\t"
      "movl (%%edi), %%edx\n\t"
      "movswl %%ax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "leal -0x41c(%%ebp), %%eax\n\t"
      "pushl $0x259d0c\n\t"
      "pushl %%eax\n\t"
      "call *%[c8df60]\n\t"
      "leal -0x41c(%%ebp,%%eax,1), %%ecx\n\t"
      "addl $4, %%esp\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1d90f0]\n\t"
      "addl $0x10, %%esp\n\t"
      ".Lai_conversation_find_participant_61:\n\t"
      "addl $2, %%esi\n\t"
      "addl $4, %%edi\n\t"
      "decl %%ebx\n\t"
      "jne .Lai_conversation_find_participant_60\n\t"
      "leal -0x41c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0\n\t"
      "call *%[cff4d0]\n\t"
      "movb -0x1(%%ebp), %%bl\n\t"
      "addl $8, %%esp\n\t"
      ".Lai_conversation_find_participant_62:\n\t"
      "movl -0x1c(%%ebp), %%eax\n\t"
      "testb $2, 0x2(%%eax)\n\t"
      "je .Lai_conversation_find_participant_64\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      ".Lai_conversation_find_participant_63:\n\t"
      "je .Lai_conversation_find_participant_64\n\t"
      "movb $1, (%%eax)\n\t"
      ".Lai_conversation_find_participant_64:\n\t"
      "movb -0x5(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lai_conversation_find_participant_65\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lai_conversation_find_participant_65\n\t"
      "movb $1, (%%eax)\n\t"
      ".Lai_conversation_find_participant_65:\n\t"
      "movl 0x18(%%ebp), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .Lai_conversation_find_participant_66\n\t"
      "flds (%%ecx)\n\t"
      "fcomps -0x4c(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "movb %%bl, %%al\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lai_conversation_find_participant_67\n\t"
      "movl -0x4c(%%ebp), %%edx\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%edx, (%%ecx)\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lai_conversation_find_participant_66:\n\t"
      "movb %%bl, %%al\n\t"
      ".Lai_conversation_find_participant_67:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".Lai_conversation_find_participant_jt:\n\t"
      ".long .Lai_conversation_find_participant_27\n\t"
      ".long .Lai_conversation_find_participant_32\n\t"
      ".long .Lai_conversation_find_participant_30\n\t"
      ".long .Lai_conversation_find_participant_33\n\t"
      ".long .Lai_conversation_find_participant_34\n\t"
      ".long .Lai_conversation_find_participant_32\n\t"
      ".long .Lai_conversation_find_participant_27\n\t"
      ".long .Lai_conversation_find_participant_34\n\t"
      ".text\n\t"
      :
      : [dget] "m"(b447d0_dget), [c18e380] "m"(b447d0_c18e380), [elem] "m"(b447d0_elem), [assert] "m"(b447d0_assert), [exitfn] "m"(b447d0_exitfn), [memset] "m"(b447d0_memset), [c140720] "m"(b447d0_c140720), [c54680] "m"(b447d0_c54680), [c59b10] "m"(b447d0_c59b10), [tryget] "m"(b447d0_tryget), [c54750] "m"(b447d0_c54750), [c59b50] "m"(b447d0_c59b50), [c441c0] "m"(b447d0_c441c0), [get] "m"(b447d0_get), [ca7a30] "m"(b447d0_ca7a30), [gseed] "m"(b447d0_gseed), [c10b2d0] "m"(b447d0_c10b2d0), [c54220] "m"(b447d0_c54220), [c8dff0] "m"(b447d0_c8dff0), [cff4d0] "m"(b447d0_cff4d0), [c8df60] "m"(b447d0_c8df60), [c1d90f0] "m"(b447d0_c1d90f0)
      : "memory");
}
#else
#error "ai_conversation_find_participant: clang naked draft required"
#endif


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

/* FUN_00046f10 (0x46f10) — XBE naked draft (batch 75). */
#if defined(__clang__)
static void (*const b46f10_chkstk)(void) = FUN_001d90e0;
static int (*const b46f10_gtime)(void) = game_time_get;
static void (*const b46f10_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b46f10_exitfn)(int) = system_exit;
static void *(*const b46f10_get)(int, int) = object_get_and_verify_type;
static int (*const b46f10_c41040)(short param_1) = ai_get_race_from_team_index;
static void *(*const b46f10_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static int16_t (*const b46f10_c3a770)(int16_t actor_type) = FUN_0003a770;
static bool (*const b46f10_ca7a90)(int16_t team_a, int16_t team_b) = game_team_is_ally;
static int (*const b46f10_c458f0)(int comm_type, int unit, int16_t subtype, int16_t index, int stack_a, int stack_b, float max_dist, int mode) = ai_communication_find_global_actor_to_talk;
static void (*const b46f10_cff4d0)(int channel, const char *format, ...) = console_printf;
static bool (*const b46f10_ca8040)(int16_t team_a, int16_t team_b, int16_t action, bool *out_changed) = game_allegiance_bump;
static void (*const b46f10_c40150)(int16_t team_a, int16_t team_b, char print_message) = ai_handle_allegiance_broken_notification;
static int16_t (*const b46f10_ca7b40)(int16_t team_a, int16_t team_b, int16_t *out_threshold) = game_allegiance_get_incidents;
static bool (*const b46f10_ca7a30)(int16_t team_a, int16_t team_b) = game_allegiance_get_team_is_friendly;
static int (*const b46f10_c1d90f0)(char *buffer, const char *format, ...) = crt_sprintf;
static char * (*const b46f10_c8d970)(char *s) = strupr;
static char * (*const b46f10_c8dff0)(char *destination, const char *source) = csstrcpy;
static void *(*const b46f10_memset)(void *, int, unsigned int) = csmemset;
static void (*const b46f10_ftol)(void) = FUN_001d9068;
static char * (*const b46f10_c8dc30)(char *destination, const char *source) = FUN_0008dc30;
static void (*const b46f10_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;
static short (*const b46f10_cfff80)(void) = game_connection;
static char * (*const b46f10_c1a67b0)(short param_1, unsigned char param_2) = FUN_001a67b0;
static char * (*const b46f10_c8d9d0)(char *buffer, const char *format, ...) = csprintf;
static char (*const b46f10_c1cb990)(void) = sound_scripted_dialog_is_playing;
static int (*const b46f10_c45830)(int type /* */, int unit /* */, int actor /* */, int target /* */, int16_t subtype, int16_t index, float max_dist) = FUN_00045830;
static void (*const b46f10_c460e0)(int actor /* */, int stack_a, float *pos, int stack_c, float radius, float rating, int16_t anim_a, int16_t anim_b, int stack_d, int stack_e, char flags) = FUN_000460e0;
static float (*const b46f10_c441c0)(int unit, char use_teams, int *out_unit, int *out_handle) = ai_communication_get_player_rating;
static int16_t (*const b46f10_c430d0)(void *packet /* */, int unit /* */, int param /* */, int stack_a, int16_t dialogue_type, int16_t start_tick, int stack_b, char flag, float *timer, char *out_buf) = ai_communication_consider_speech;
static uint32_t (*const b46f10_c1a97c0)(int unit_handle, int impulse_index) = unit_test_animation_impulse;
static int16_t (*const b46f10_c1d6d0)(int actor_handle) = actor_action_try_to_panic;
static int *(*const b46f10_gseed)(void) = get_global_random_seed_address;
static float (*const b46f10_rmreal)(unsigned int *) = random_math_real;
static void (*const b46f10_c44fd0)(int unit_handle, uint16_t priority, uint16_t type, void *comm_data) = FUN_00044fd0;
static void (*const b46f10_c45290)(int unit_handle, uint16_t priority, uint16_t type, void *comm_data) = FUN_00045290;
static void (*const b46f10_c46530)(int unit_handle, uint16_t priority, uint16_t type, int unk, int unk2, void *comm_data) = FUN_00046530;
static void (*const b46f10_c1a6ef0)(int actor, short count, void *comm_buf) = FUN_001a6ef0;
static void (*const b46f10_c1a9200)(int object_handle, float *out_position) = unit_get_head_position;
static bool (*const b46f10_c1b1a20)(int unit_handle, int anim_index, void *anim_data) = unit_apply_animation_impulse;
static void *(*const b46f10_tryget)(int, int) = object_try_and_get_and_verify_type;
static int (*const b46f10_c64ab0)(int actor_handle, int object_handle) = prop_get_active_by_unit_index;
static int (*const b46f10_c27a60)(int actor_handle, short look_type, short priority, short *look_buf) = FUN_00027a60;
static void (*const b46f10_c43f20)(int unit /* */, int16_t type, int a, int16_t dialogue_index, int16_t reply_index) = ai_communication_update_speech_timers;
static void * (*const b46f10_c8ee60)(uint32_t size, bool zero, const char *file, int line) = debug_malloc;
static void (*const b46f10_c8ef70)(void *ptr, const char *file, int line) = debug_free;
static void * (*const b46f10_c18e3b0)(void) = FUN_0018e3b0;
static void *(*const b46f10_elem)(void *, int, int) = tag_block_get_element;
static void * (*const b46f10_c8de70)(char *destination, const char *source, size_t size) = csstrncpy;

__attribute__((naked, noinline))
void FUN_00046f10(int16_t type __attribute__((unused)), int unit_handle __attribute__((unused)), int param3 __attribute__((unused)), int param4 __attribute__((unused)), int16_t param5 __attribute__((unused)), int16_t param6 __attribute__((unused)), int16_t param7 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl $0x126c, %%eax\n\t"
      "call *%[chkstk]\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[gtime]\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "orl $0xffffffff, %%esi\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "movl %%eax, -0xa0(%%ebp)\n\t"
      "xorl %%eax, %%eax\n\t"
      "xorl %%edi, %%edi\n\t"
      "cmpw %%ax, %%cx\n\t"
      "movl %%eax, -0xa4(%%ebp)\n\t"
      "movl %%eax, -0x44(%%ebp)\n\t"
      "movb %%al, -0x36(%%ebp)\n\t"
      "movl %%esi, -0x90(%%ebp)\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "movl %%esi, -0x8c(%%ebp)\n\t"
      "movl %%eax, -0x88(%%ebp)\n\t"
      "movl %%esi, -0xbc(%%ebp)\n\t"
      "movl %%eax, -0xc0(%%ebp)\n\t"
      "movl %%esi, -0x80(%%ebp)\n\t"
      "movl %%esi, -0xb0(%%ebp)\n\t"
      "movl %%esi, -0x98(%%ebp)\n\t"
      "movl %%esi, -0x20(%%ebp)\n\t"
      "movl %%eax, -0x84(%%ebp)\n\t"
      "movl %%eax, -0x9c(%%ebp)\n\t"
      "movb $1, -0xa(%%ebp)\n\t"
      "movb $1, -0x29(%%ebp)\n\t"
      "movb %%bl, -0x35(%%ebp)\n\t"
      "movb %%bl, -0x9(%%ebp)\n\t"
      "movb %%bl, -0x2(%%ebp)\n\t"
      "jl .LFUN_00046f10_1\n\t"
      "cmpw $0x39, %%cx\n\t"
      "jl .LFUN_00046f10_2\n\t"
      ".LFUN_00046f10_1:\n\t"
      "pushl $1\n\t"
      "pushl $0x34e\n\t"
      "pushl $0x2599b4\n\t"
      "pushl $0x25a960\n\t"
      "call *%[assert]\n\t"
      "pushl %%esi\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "xorl %%eax, %%eax\n\t"
      ".LFUN_00046f10_2:\n\t"
      "cmpw %%si, 0x14(%%ebp)\n\t"
      "jne .LFUN_00046f10_3\n\t"
      "movl %%eax, 0x14(%%ebp)\n\t"
      ".LFUN_00046f10_3:\n\t"
      "cmpw %%si, 0x18(%%ebp)\n\t"
      "jne .LFUN_00046f10_4\n\t"
      "movl %%eax, 0x18(%%ebp)\n\t"
      ".LFUN_00046f10_4:\n\t"
      "movw %%ax, -0x30(%%ebp)\n\t"
      "movw %%ax, -0x28(%%ebp)\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "cmpl %%esi, %%eax\n\t"
      "je .LFUN_00046f10_9\n\t"
      "pushl $3\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%edi\n\t"
      "movl 0x1a4(%%edi), %%eax\n\t"
      "movl %%eax, -0x8c(%%ebp)\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x68(%%edi), %%ax\n\t"
      "pushl %%eax\n\t"
      "movl %%eax, -0x98(%%ebp)\n\t"
      "call *%[c41040]\n\t"
      "addl $0xc, %%esp\n\t"
      "movl %%eax, -0x84(%%ebp)\n\t"
      "movl -0x8c(%%ebp), %%eax\n\t"
      "cmpl %%esi, %%eax\n\t"
      "je .LFUN_00046f10_8\n\t"
      "movl 0x6325a4, %%edx\n\t"
      "movl %%eax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x34(%%esi), %%eax\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x4(%%esi), %%cx\n\t"
      "movl %%esi, -0x88(%%ebp)\n\t"
      "movl %%eax, -0x90(%%ebp)\n\t"
      "pushl %%ecx\n\t"
      "call *%[c3a770]\n\t"
      "addl $0xc, %%esp\n\t"
      "movl %%eax, -0x84(%%ebp)\n\t"
      "movb 0x245(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jle .LFUN_00046f10_5\n\t"
      "movb $1, -0x27(%%ebp)\n\t"
      "jmp .LFUN_00046f10_6\n\t"
      ".LFUN_00046f10_5:\n\t"
      "movb 0x200(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jle .LFUN_00046f10_7\n\t"
      "movb $0, -0x27(%%ebp)\n\t"
      ".LFUN_00046f10_6:\n\t"
      "movb $1, -0x28(%%ebp)\n\t"
      ".LFUN_00046f10_7:\n\t"
      "movl -0x90(%%ebp), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_00046f10_9\n\t"
      "movl %%eax, %%edx\n\t"
      "movl 0x5ab270, %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "addl $8, %%esp\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "jmp .LFUN_00046f10_9\n\t"
      ".LFUN_00046f10_8:\n\t"
      "cmpl %%esi, 0x1c8(%%edi)\n\t"
      "je .LFUN_00046f10_9\n\t"
      "movl $1, -0x84(%%ebp)\n\t"
      ".LFUN_00046f10_9:\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_00046f10_12\n\t"
      "movl %%eax, %%ecx\n\t"
      "pushl $3\n\t"
      "pushl %%ecx\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl 0x1a4(%%ebx), %%esi\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x68(%%ebx), %%ax\n\t"
      "movl %%esi, -0xbc(%%ebp)\n\t"
      "pushl %%eax\n\t"
      "movl %%eax, -0x20(%%ebp)\n\t"
      "call *%[c41040]\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl $-1, %%esi\n\t"
      "movl %%eax, -0x9c(%%ebp)\n\t"
      "je .LFUN_00046f10_11\n\t"
      "movl 0x6325a4, %%edx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edx\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%esi\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x4(%%esi), %%ax\n\t"
      "movl %%esi, -0xc0(%%ebp)\n\t"
      "pushl %%eax\n\t"
      "call *%[c3a770]\n\t"
      "addl $0xc, %%esp\n\t"
      "movl %%eax, -0x9c(%%ebp)\n\t"
      "movb 0x245(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jle .LFUN_00046f10_10\n\t"
      "movb $1, -0x30(%%ebp)\n\t"
      "movb $1, -0x2f(%%ebp)\n\t"
      "jmp .LFUN_00046f10_12\n\t"
      ".LFUN_00046f10_10:\n\t"
      "movb 0x200(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jle .LFUN_00046f10_12\n\t"
      "movb $1, -0x30(%%ebp)\n\t"
      "movb $0, -0x2f(%%ebp)\n\t"
      "jmp .LFUN_00046f10_12\n\t"
      ".LFUN_00046f10_11:\n\t"
      "cmpl $-1, 0x1c8(%%ebx)\n\t"
      "je .LFUN_00046f10_12\n\t"
      "movl $1, -0x9c(%%ebp)\n\t"
      ".LFUN_00046f10_12:\n\t"
      "testl %%edi, %%edi\n\t"
      "je .LFUN_00046f10_29\n\t"
      "testl %%ebx, %%ebx\n\t"
      "je .LFUN_00046f10_29\n\t"
      "movl -0x98(%%ebp), %%esi\n\t"
      "cmpw -0x20(%%ebp), %%si\n\t"
      "je .LFUN_00046f10_29\n\t"
      "movl -0x20(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "call *%[ca7a90]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00046f10_29\n\t"
      "cmpw $0, 0x8(%%ebp)\n\t"
      "movb $0, -0x7(%%ebp)\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "jne .LFUN_00046f10_28\n\t"
      "cmpw $3, 0x14(%%ebp)\n\t"
      "jne .LFUN_00046f10_13\n\t"
      "movb $1, -0x7(%%ebp)\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "jmp .LFUN_00046f10_20\n\t"
      ".LFUN_00046f10_13:\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_00046f10_15\n\t"
      "movb 0x46(%%eax), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "jne .LFUN_00046f10_14\n\t"
      "movl 0x50(%%eax), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_00046f10_14\n\t"
      "cmpl $0x10e, %%eax\n\t"
      "movb $0, -0x7(%%ebp)\n\t"
      "jl .LFUN_00046f10_15\n\t"
      ".LFUN_00046f10_14:\n\t"
      "movb $1, -0x7(%%ebp)\n\t"
      ".LFUN_00046f10_15:\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "pushl $0\n\t"
      "pushl $-1\n\t"
      "pushl $-1\n\t"
      "pushl $-1\n\t"
      "pushl $6\n\t"
      "pushl $0\n\t"
      "pushl $0x41900000\n\t"
      "pushl %%edx\n\t"
      "pushl $0\n\t"
      "movl %%esi, %%ebx\n\t"
      "call *%[c458f0]\n\t"
      "addl $0x24, %%esp\n\t"
      "xorb %%dl, %%dl\n\t"
      "cmpl $-1, %%eax\n\t"
      "movl %%eax, -0x80(%%ebp)\n\t"
      "je .LFUN_00046f10_16\n\t"
      "movb %%dl, -0xa(%%ebp)\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      ".LFUN_00046f10_16:\n\t"
      "movl 0x18(%%ebp), %%ecx\n\t"
      "movswl %%cx, %%eax\n\t"
      "cmpl $3, %%eax\n\t"
      "jl .LFUN_00046f10_18\n\t"
      "cmpl $4, %%eax\n\t"
      "jle .LFUN_00046f10_17\n\t"
      "cmpl $9, %%eax\n\t"
      "jne .LFUN_00046f10_18\n\t"
      ".LFUN_00046f10_17:\n\t"
      "cmpb %%dl, -0x7(%%ebp)\n\t"
      "jne .LFUN_00046f10_18\n\t"
      "movb %%dl, -0x1(%%ebp)\n\t"
      ".LFUN_00046f10_18:\n\t"
      "cmpw $3, %%cx\n\t"
      "jne .LFUN_00046f10_19\n\t"
      "movb %%dl, -0x7(%%ebp)\n\t"
      "jmp .LFUN_00046f10_21\n\t"
      ".LFUN_00046f10_19:\n\t"
      "cmpb %%dl, -0x7(%%ebp)\n\t"
      "je .LFUN_00046f10_21\n\t"
      ".LFUN_00046f10_20:\n\t"
      "movl $4, 0x14(%%ebp)\n\t"
      ".LFUN_00046f10_21:\n\t"
      "movb 0x5aca55, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00046f10_24\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "movl $0x25a954, %%ecx\n\t"
      "jne .LFUN_00046f10_22\n\t"
      "movl $0x25a948, %%ecx\n\t"
      ".LFUN_00046f10_22:\n\t"
      "movb -0x7(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "movl $0x25a93c, %%eax\n\t"
      "jne .LFUN_00046f10_23\n\t"
      "movl $0x25a930, %%eax\n\t"
      ".LFUN_00046f10_23:\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "movswl -0x20(%%ebp), %%eax\n\t"
      "movl 0x2efdf8(,%%eax,4), %%ecx\n\t"
      "movswl %%si, %%edx\n\t"
      "movl 0x2efdf8(,%%edx,4), %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl $0x25a904\n\t"
      "pushl $0\n\t"
      "call *%[cff4d0]\n\t"
      "addl $0x18, %%esp\n\t"
      ".LFUN_00046f10_24:\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00046f10_28\n\t"
      "movb -0x7(%%ebp), %%al\n\t"
      "movl -0x20(%%ebp), %%edi\n\t"
      "xorl %%edx, %%edx\n\t"
      "testb %%al, %%al\n\t"
      "setne %%dl\n\t"
      "leal -0x1(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "pushl %%edx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[ca8040]\n\t"
      "movb %%al, %%bl\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "addl $0x10, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "movb %%bl, -0x3c(%%ebp)\n\t"
      "je .LFUN_00046f10_25\n\t"
      "movl -0x3c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c40150]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_00046f10_25:\n\t"
      "movb 0x5aca55, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00046f10_28\n\t"
      "testb %%bl, %%bl\n\t"
      "jne .LFUN_00046f10_28\n\t"
      "movl -0x20(%%ebp), %%edx\n\t"
      "leal -0x8(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edx\n\t"
      "call *%[ca7b40]\n\t"
      "movw -0x8(%%ebp), %%cx\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpw $-1, %%cx\n\t"
      "jne .LFUN_00046f10_26\n\t"
      "movl $0x3e7, %%ecx\n\t"
      "jmp .LFUN_00046f10_27\n\t"
      ".LFUN_00046f10_26:\n\t"
      "movswl %%cx, %%ecx\n\t"
      ".LFUN_00046f10_27:\n\t"
      "pushl %%ecx\n\t"
      "movswl %%ax, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x25a8f8\n\t"
      "pushl $0x25a8cc\n\t"
      "pushl $0\n\t"
      "call *%[cff4d0]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00046f10_28:\n\t"
      "movl -0x20(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "call *%[ca7a30]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00046f10_29\n\t"
      "movl $4, 0x14(%%ebp)\n\t"
      ".LFUN_00046f10_29:\n\t"
      "movb 0x5aca4f, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00046f10_30\n\t"
      "movswl 0x14(%%ebp), %%edx\n\t"
      "movswl 0x8(%%ebp), %%ecx\n\t"
      "movb $0x6e, -0x64(%%ebp)\n\t"
      "movb $0x73, -0x63(%%ebp)\n\t"
      "movb $0x66, -0x62(%%ebp)\n\t"
      "movb $0x65, -0x61(%%ebp)\n\t"
      "movb $0x74, -0x60(%%ebp)\n\t"
      "movsbl -0x64(%%ebp,%%edx,1), %%eax\n\t"
      "movl 0x2c8d78(,%%ecx,4), %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%edx\n\t"
      "leal -0xa6c(%%ebp), %%eax\n\t"
      "pushl $0x25a8c4\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d90f0]\n\t"
      "leal -0xa6c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c8d970]\n\t"
      "leal -0x106c(%%ebp), %%edx\n\t"
      "pushl $0x25386f\n\t"
      "pushl %%edx\n\t"
      "call *%[c8dff0]\n\t"
      "addl $0x1c, %%esp\n\t"
      ".LFUN_00046f10_30:\n\t"
      "movl -0x88(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_00046f10_31\n\t"
      "movl $0x1010101, %%eax\n\t"
      "movl %%eax, -0x1c(%%ebp)\n\t"
      "movw %%ax, -0x18(%%ebp)\n\t"
      "jmp .LFUN_00046f10_55\n\t"
      ".LFUN_00046f10_31:\n\t"
      "movl -0x14(%%ebp), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "jne .LFUN_00046f10_40\n\t"
      "movb 0x274(%%eax), %%dl\n\t"
      "testb %%dl, %%dl\n\t"
      "movb 0x27c(%%eax), %%dl\n\t"
      "sete %%cl\n\t"
      "testb %%dl, %%dl\n\t"
      "movb %%cl, -0x1c(%%ebp)\n\t"
      "jne .LFUN_00046f10_32\n\t"
      "cmpl $-1, 0x278(%%eax)\n\t"
      "movb $1, -0x1b(%%ebp)\n\t"
      "jne .LFUN_00046f10_33\n\t"
      ".LFUN_00046f10_32:\n\t"
      "movb $0, -0x1b(%%ebp)\n\t"
      ".LFUN_00046f10_33:\n\t"
      "cmpl $-1, 0x270(%%eax)\n\t"
      "je .LFUN_00046f10_34\n\t"
      "movl 0x278(%%eax), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_00046f10_34\n\t"
      "cmpl $0xb4, %%eax\n\t"
      "movb $0, -0x1a(%%ebp)\n\t"
      "jl .LFUN_00046f10_35\n\t"
      ".LFUN_00046f10_34:\n\t"
      "movb $1, -0x1a(%%ebp)\n\t"
      ".LFUN_00046f10_35:\n\t"
      "movl -0x88(%%ebp), %%esi\n\t"
      "movw 0x6e(%%esi), %%cx\n\t"
      "cmpw $3, %%cx\n\t"
      "jge .LFUN_00046f10_38\n\t"
      "movl 0x278(%%esi), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_00046f10_36\n\t"
      "cmpl $0x4b, %%eax\n\t"
      "jl .LFUN_00046f10_38\n\t"
      ".LFUN_00046f10_36:\n\t"
      "testb %%dl, %%dl\n\t"
      "jne .LFUN_00046f10_37\n\t"
      "testw %%cx, %%cx\n\t"
      "jle .LFUN_00046f10_38\n\t"
      ".LFUN_00046f10_37:\n\t"
      "movb $1, -0x19(%%ebp)\n\t"
      "jmp .LFUN_00046f10_39\n\t"
      ".LFUN_00046f10_38:\n\t"
      "movb $0, -0x19(%%ebp)\n\t"
      ".LFUN_00046f10_39:\n\t"
      "cmpw $6, %%cx\n\t"
      "setl %%al\n\t"
      "cmpw $0xa, 0x268(%%esi)\n\t"
      "movb %%al, -0x18(%%ebp)\n\t"
      "jl .LFUN_00046f10_54\n\t"
      "testb %%dl, %%dl\n\t"
      "jmp .LFUN_00046f10_53\n\t"
      ".LFUN_00046f10_40:\n\t"
      "movb 0x274(%%eax), %%bl\n\t"
      "movl 0x50(%%ecx), %%eax\n\t"
      "testb %%bl, %%bl\n\t"
      "sete %%dl\n\t"
      "cmpl $-1, %%eax\n\t"
      "movb %%dl, -0x1c(%%ebp)\n\t"
      "je .LFUN_00046f10_41\n\t"
      "movb 0x44(%%ecx), %%dl\n\t"
      "testb %%dl, %%dl\n\t"
      "movb $1, -0x1b(%%ebp)\n\t"
      "je .LFUN_00046f10_42\n\t"
      ".LFUN_00046f10_41:\n\t"
      "movb $0, -0x1b(%%ebp)\n\t"
      ".LFUN_00046f10_42:\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_00046f10_43\n\t"
      "cmpl $0xb4, %%eax\n\t"
      "jl .LFUN_00046f10_44\n\t"
      ".LFUN_00046f10_43:\n\t"
      "movb 0x44(%%ecx), %%dl\n\t"
      "testb %%dl, %%dl\n\t"
      "movb $1, -0x1a(%%ebp)\n\t"
      "jne .LFUN_00046f10_45\n\t"
      ".LFUN_00046f10_44:\n\t"
      "movb $0, -0x1a(%%ebp)\n\t"
      ".LFUN_00046f10_45:\n\t"
      "movl -0x88(%%ebp), %%ecx\n\t"
      "movw 0x6e(%%ecx), %%cx\n\t"
      "cmpw $3, %%cx\n\t"
      "jge .LFUN_00046f10_48\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_00046f10_46\n\t"
      "cmpl $0x4b, %%eax\n\t"
      "jl .LFUN_00046f10_48\n\t"
      ".LFUN_00046f10_46:\n\t"
      "movl -0x14(%%ebp), %%edx\n\t"
      "movb 0x44(%%edx), %%bl\n\t"
      "testb %%bl, %%bl\n\t"
      "jne .LFUN_00046f10_47\n\t"
      "testw %%cx, %%cx\n\t"
      "jle .LFUN_00046f10_48\n\t"
      ".LFUN_00046f10_47:\n\t"
      "movb $1, -0x19(%%ebp)\n\t"
      "jmp .LFUN_00046f10_49\n\t"
      ".LFUN_00046f10_48:\n\t"
      "movl -0x14(%%ebp), %%edx\n\t"
      "movb $0, -0x19(%%ebp)\n\t"
      ".LFUN_00046f10_49:\n\t"
      "cmpw $6, %%cx\n\t"
      "jge .LFUN_00046f10_51\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_00046f10_50\n\t"
      "cmpl $0x4b, %%eax\n\t"
      "jl .LFUN_00046f10_51\n\t"
      ".LFUN_00046f10_50:\n\t"
      "movb $1, -0x18(%%ebp)\n\t"
      "jmp .LFUN_00046f10_52\n\t"
      ".LFUN_00046f10_51:\n\t"
      "movb $0, -0x18(%%ebp)\n\t"
      ".LFUN_00046f10_52:\n\t"
      "movb 0x45(%%edx), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00046f10_54\n\t"
      "movb 0x44(%%edx), %%al\n\t"
      "testb %%al, %%al\n\t"
      ".LFUN_00046f10_53:\n\t"
      "movb $1, -0x17(%%ebp)\n\t"
      "jne .LFUN_00046f10_55\n\t"
      ".LFUN_00046f10_54:\n\t"
      "movb $0, -0x17(%%ebp)\n\t"
      ".LFUN_00046f10_55:\n\t"
      "pushl $5\n\t"
      "xorl %%esi, %%esi\n\t"
      "leal -0xac(%%ebp), %%edx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edx\n\t"
      "call *%[memset]\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .LFUN_00046f10_56\n\t"
      "cmpw $4, %%ax\n\t"
      "movswl %%ax, %%ecx\n\t"
      "movb $1, -0xac(%%ebp,%%ecx,1)\n\t"
      "jne .LFUN_00046f10_56\n\t"
      "movb $1, -0xa9(%%ebp)\n\t"
      ".LFUN_00046f10_56:\n\t"
      "pushl $0x40\n\t"
      "leal -0x1ec(%%ebp), %%edx\n\t"
      "pushl $-1\n\t"
      "pushl %%edx\n\t"
      "call *%[memset]\n\t"
      "pushl $0x20\n\t"
      "leal -0x16c(%%ebp), %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "call *%[memset]\n\t"
      "pushl $0x40\n\t"
      "leal -0x1ac(%%ebp), %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%ecx\n\t"
      "call *%[memset]\n\t"
      "movl 0x632574, %%eax\n\t"
      "addl $0x24, %%esp\n\t"
      "leal -0x16b(%%ebp), %%edx\n\t"
      "addl $0x1c, %%eax\n\t"
      "movl $4, -0x4c(%%ebp)\n\t"
      "movl %%edx, -0x14(%%ebp)\n\t"
      "movl %%eax, -0x48(%%ebp)\n\t"
      "movl %%esi, -0x5c(%%ebp)\n\t"
      "movl %%esi, -0x58(%%ebp)\n\t"
      "movl $2, -0x74(%%ebp)\n\t"
      ".LFUN_00046f10_57:\n\t"
      "movl -0xa0(%%ebp), %%edi\n\t"
      "movl -0x48(%%ebp), %%esi\n\t"
      "movl 0x8(%%esi), %%ecx\n\t"
      "movl (%%esi), %%ebx\n\t"
      "movl %%edi, %%eax\n\t"
      "subl %%ecx, %%eax\n\t"
      "movl $0, %%ecx\n\t"
      "sets %%cl\n\t"
      "movl -0x5c(%%ebp), %%edx\n\t"
      "movl $5, -0x78(%%ebp)\n\t"
      "decl %%ecx\n\t"
      "andl %%eax, %%ecx\n\t"
      "movl %%edi, %%eax\n\t"
      "subl %%ebx, %%eax\n\t"
      "movl $0, %%ebx\n\t"
      "sets %%bl\n\t"
      "movw %%cx, 0x14(%%ebp,%%edx,1)\n\t"
      "movswl %%cx, %%ecx\n\t"
      "movl %%ecx, 0x14(%%ebp)\n\t"
      "movl -0x58(%%ebp), %%ecx\n\t"
      "fildl 0x14(%%ebp)\n\t"
      "decl %%ebx\n\t"
      "flds 0x2546a4\n\t"
      "andl %%eax, %%ebx\n\t"
      "movl %%ebx, %%esi\n\t"
      "movl %%edi, %%eax\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "movl -0x48(%%ebp), %%edi\n\t"
      "movl -0x8(%%edi), %%ebx\n\t"
      "subl %%ebx, %%eax\n\t"
      "fstps -0xe8(%%ebp,%%ecx,1)\n\t"
      "movl $0, %%ebx\n\t"
      "sets %%bl\n\t"
      "movw %%si, -0x64(%%ebp,%%edx,1)\n\t"
      "movl $0x257cfc, %%edi\n\t"
      "decl %%ebx\n\t"
      "andl %%ebx, %%eax\n\t"
      "movw %%ax, -0xb4(%%ebp,%%edx,1)\n\t"
      "movswl %%si, %%edx\n\t"
      "movl %%edx, 0x14(%%ebp)\n\t"
      "movswl %%ax, %%eax\n\t"
      "fildl 0x14(%%ebp)\n\t"
      "flds 0x2546a4\n\t"
      "movl %%eax, 0x14(%%ebp)\n\t"
      "movl -0x4c(%%ebp), %%eax\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fstps -0xfc(%%ebp,%%ecx,1)\n\t"
      "fildl 0x14(%%ebp)\n\t"
      "flds 0x2546a4\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fstps -0x11c(%%ebp,%%ecx,1)\n\t"
      "movl -0x14(%%ebp), %%ecx\n\t"
      "movb $1, -0x1(%%ecx)\n\t"
      "movb $1, (%%ecx)\n\t"
      "incl %%ecx\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".LFUN_00046f10_58:\n\t"
      "movl %%ecx, -0x50(%%ebp)\n\t"
      "movl %%eax, -0x54(%%ebp)\n\t"
      "movl $2, -0x7c(%%ebp)\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".LFUN_00046f10_59:\n\t"
      "flds -0x4(%%edi)\n\t"
      "xorb %%bl, %%bl\n\t"
      "fcomps 0x2533c0\n\t"
      "xorl %%esi, %%esi\n\t"
      "movl $0xffffffff, 0x14(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00046f10_60\n\t"
      "flds -0x4(%%edi)\n\t"
      "fmuls 0x253394\n\t"
      ".byte 0xd8, 0xe1\n\t"
      "call *%[ftol]\n\t"
      "testw %%ax, %%ax\n\t"
      "jle .LFUN_00046f10_60\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "testw %%ax, %%ax\n\t"
      "setl %%cl\n\t"
      "movl %%esi, 0x14(%%ebp)\n\t"
      "movb $1, %%bl\n\t"
      "decl %%ecx\n\t"
      "andl %%eax, %%ecx\n\t"
      "movl %%ecx, %%esi\n\t"
      ".LFUN_00046f10_60:\n\t"
      "flds (%%edi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00046f10_61\n\t"
      "flds (%%edi)\n\t"
      "fmuls 0x253394\n\t"
      ".byte 0xd8, 0xe2\n\t"
      "call *%[ftol]\n\t"
      "testw %%ax, %%ax\n\t"
      "jle .LFUN_00046f10_61\n\t"
      "cmpw %%ax, %%si\n\t"
      "movb $1, %%bl\n\t"
      "movl $1, 0x14(%%ebp)\n\t"
      "jg .LFUN_00046f10_61\n\t"
      "movl %%eax, %%esi\n\t"
      ".LFUN_00046f10_61:\n\t"
      "flds 0x8(%%edi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00046f10_62\n\t"
      "flds 0x8(%%edi)\n\t"
      "fmuls 0x253394\n\t"
      ".byte 0xd8, 0xe3\n\t"
      "call *%[ftol]\n\t"
      "testw %%ax, %%ax\n\t"
      "jle .LFUN_00046f10_62\n\t"
      "cmpw %%ax, %%si\n\t"
      "movb $1, %%bl\n\t"
      "movl $2, 0x14(%%ebp)\n\t"
      "jg .LFUN_00046f10_63\n\t"
      "movl %%eax, %%esi\n\t"
      "jmp .LFUN_00046f10_63\n\t"
      ".LFUN_00046f10_62:\n\t"
      "testb %%bl, %%bl\n\t"
      "je .LFUN_00046f10_64\n\t"
      ".LFUN_00046f10_63:\n\t"
      "flds 0xc(%%edi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00046f10_64\n\t"
      "movl -0x54(%%ebp), %%edx\n\t"
      "movswl -0x1ac(%%ebp,%%edx,1), %%eax\n\t"
      "movl %%eax, -0x3c(%%ebp)\n\t"
      "fildl -0x3c(%%ebp)\n\t"
      "flds 0xc(%%edi)\n\t"
      "fmuls 0x253394\n\t"
      "fcompp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00046f10_64\n\t"
      "xorb %%bl, %%bl\n\t"
      ".LFUN_00046f10_64:\n\t"
      "movl -0x54(%%ebp), %%eax\n\t"
      "movl -0x50(%%ebp), %%ecx\n\t"
      "movw 0x14(%%ebp), %%dx\n\t"
      "movw %%dx, -0x1ec(%%ebp,%%eax,1)\n\t"
      "movl -0x7c(%%ebp), %%edx\n\t"
      "addl $2, %%eax\n\t"
      "movw %%si, -0x1ae(%%ebp,%%eax,1)\n\t"
      "addl $0x14, %%edi\n\t"
      "movb %%bl, (%%ecx)\n\t"
      "incl %%ecx\n\t"
      "decl %%edx\n\t"
      "movl %%eax, -0x54(%%ebp)\n\t"
      "movl %%ecx, -0x50(%%ebp)\n\t"
      "movl %%edx, -0x7c(%%ebp)\n\t"
      "jne .LFUN_00046f10_59\n\t"
      "decl -0x78(%%ebp)\n\t"
      "jne .LFUN_00046f10_58\n\t"
      "movl -0x48(%%ebp), %%edi\n\t"
      "fstp %%st(0)\n\t"
      "movl -0x58(%%ebp), %%esi\n\t"
      "fstp %%st(0)\n\t"
      "movl -0x5c(%%ebp), %%ebx\n\t"
      "fstp %%st(0)\n\t"
      "movl -0x4c(%%ebp), %%edx\n\t"
      "movl -0x14(%%ebp), %%ecx\n\t"
      "movl $4, %%eax\n\t"
      "addl %%eax, %%edi\n\t"
      "addl %%eax, %%esi\n\t"
      "movl -0x74(%%ebp), %%eax\n\t"
      "addl $2, %%ebx\n\t"
      "addl $0x20, %%edx\n\t"
      "addl $0x10, %%ecx\n\t"
      "decl %%eax\n\t"
      "movl %%ebx, -0x5c(%%ebp)\n\t"
      "movl %%edi, -0x48(%%ebp)\n\t"
      "movl %%esi, -0x58(%%ebp)\n\t"
      "movl %%edx, -0x4c(%%ebp)\n\t"
      "movl %%ecx, -0x14(%%ebp)\n\t"
      "movl %%eax, -0x74(%%ebp)\n\t"
      "jne .LFUN_00046f10_57\n\t"
      "movl 0x632574, %%eax\n\t"
      "movb 0x10(%%eax), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "jne .LFUN_00046f10_65\n\t"
      "movb 0x5aca4f, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00046f10_194\n\t"
      "leal -0xa6c(%%ebp), %%ecx\n\t"
      "pushl $0x25a8b8\n\t"
      "pushl %%ecx\n\t"
      "call *%[c8dc30]\n\t"
      "leal -0xa6c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $0x10, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00046f10_65:\n\t"
      "movswl 0x8(%%ebp), %%esi\n\t"
      "xorl %%edi, %%edi\n\t"
      "movw 0x632500(,%%esi,2), %%di\n\t"
      "movl %%esi, -0x64(%%ebp)\n\t"
      "movl %%edi, -0x10(%%ebp)\n\t"
      "call *%[cfff80]\n\t"
      "testw %%ax, %%ax\n\t"
      "jne .LFUN_00046f10_66\n\t"
      "movl %%esi, %%ecx\n\t"
      "andl $0x1f, %%ecx\n\t"
      "movl $1, %%eax\n\t"
      "shll %%cl, %%eax\n\t"
      "movl %%esi, %%ecx\n\t"
      "sarl $5, %%ecx\n\t"
      "testl %%eax, 0x5aca14(,%%ecx,4)\n\t"
      "je .LFUN_00046f10_66\n\t"
      "movl $0xffffffff, -0x10(%%ebp)\n\t"
      "movl -0x10(%%ebp), %%edi\n\t"
      "movb $1, -0x7(%%ebp)\n\t"
      "jmp .LFUN_00046f10_67\n\t"
      ".LFUN_00046f10_66:\n\t"
      "movl %%esi, %%ecx\n\t"
      "andl $0x1f, %%ecx\n\t"
      "movl $1, %%edx\n\t"
      "shll %%cl, %%edx\n\t"
      "sarl $5, %%esi\n\t"
      "testl %%edx, 0x5aca1c(,%%esi,4)\n\t"
      "setne -0x7(%%ebp)\n\t"
      ".LFUN_00046f10_67:\n\t"
      "movb 0x5aca44, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00046f10_68\n\t"
      "movb $1, -0x7(%%ebp)\n\t"
      ".LFUN_00046f10_68:\n\t"
      "cmpw $-1, %%di\n\t"
      "je .LFUN_00046f10_167\n\t"
      "testw %%di, %%di\n\t"
      "jl .LFUN_00046f10_69\n\t"
      "cmpw 0x331f08, %%di\n\t"
      "jl .LFUN_00046f10_70\n\t"
      ".LFUN_00046f10_69:\n\t"
      "pushl $1\n\t"
      "pushl $0x4c3\n\t"
      "pushl $0x2599b4\n\t"
      "pushl $0x25a870\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00046f10_70:\n\t"
      "movswl -0x10(%%ebp), %%eax\n\t"
      "leal (%%eax,%%eax,4), %%esi\n\t"
      "movw 0x8(%%ebp), %%ax\n\t"
      "cmpw %%ax, 0x257e48(,%%esi,8)\n\t"
      "leal 0x257e48(,%%esi,8), %%esi\n\t"
      "movl %%esi, -0x3c(%%ebp)\n\t"
      "jne .LFUN_00046f10_167\n\t"
      ".LFUN_00046f10_71:\n\t"
      "movb 0x5aca44, %%al\n\t"
      "testb %%al, %%al\n\t"
      "movw 0x2(%%esi), %%cx\n\t"
      "movw %%cx, -0x24(%%ebp)\n\t"
      "je .LFUN_00046f10_72\n\t"
      "movswl 0x4(%%esi), %%eax\n\t"
      "movl %%eax, %%ecx\n\t"
      "andl $0x1f, %%ecx\n\t"
      "movl $1, %%edx\n\t"
      "shll %%cl, %%edx\n\t"
      "sarl $5, %%eax\n\t"
      "testl %%edx, 0x5aca24(,%%eax,4)\n\t"
      "je .LFUN_00046f10_72\n\t"
      "movb $0, -0x7(%%ebp)\n\t"
      ".LFUN_00046f10_72:\n\t"
      "movw 0x1c(%%esi), %%ax\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .LFUN_00046f10_73\n\t"
      "movswl %%ax, %%eax\n\t"
      "movb -0xac(%%ebp,%%eax,1), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "jne .LFUN_00046f10_73\n\t"
      "movb 0x5aca4f, %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "je .LFUN_00046f10_76\n\t"
      "movswl -0x10(%%ebp), %%ecx\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x4(%%esi), %%dx\n\t"
      "movl $0x254384, -0x114(%%ebp)\n\t"
      "movl $0x25a864, -0x110(%%ebp)\n\t"
      "movl $0x25a85c, -0x10c(%%ebp)\n\t"
      "movl $0x25a854, -0x108(%%ebp)\n\t"
      "movl $0x25a84c, -0x104(%%ebp)\n\t"
      "movl -0x114(%%ebp,%%eax,4), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl $1\n\t"
      "pushl %%edx\n\t"
      "call *%[c1a67b0]\n\t"
      "addl $8, %%esp\n\t"
      "pushl %%eax\n\t"
      "pushl $0x25a838\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "pushl %%eax\n\t"
      "leal -0x106c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c8dc30]\n\t"
      "addl $0x1c, %%esp\n\t"
      "movb $1, -0x9(%%ebp)\n\t"
      "jmp .LFUN_00046f10_165\n\t"
      ".LFUN_00046f10_73:\n\t"
      "call *%[c1cb990]\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00046f10_75\n\t"
      "cmpw $6, 0x2(%%esi)\n\t"
      "jge .LFUN_00046f10_75\n\t"
      "testb $0x40, 0x18(%%esi)\n\t"
      "jne .LFUN_00046f10_75\n\t"
      "movb 0x5aca4f, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00046f10_74\n\t"
      "leal -0x106c(%%ebp), %%ecx\n\t"
      "pushl $0x25a1ec\n\t"
      "pushl %%ecx\n\t"
      "call *%[c8dc30]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_00046f10_74:\n\t"
      "movb $1, -0x9(%%ebp)\n\t"
      "jmp .LFUN_00046f10_165\n\t"
      ".LFUN_00046f10_75:\n\t"
      "movw 0x1e(%%esi), %%ax\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .LFUN_00046f10_77\n\t"
      "movswl %%ax, %%eax\n\t"
      "movb -0x1c(%%ebp,%%eax,1), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "jne .LFUN_00046f10_77\n\t"
      "movb 0x5aca4f, %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "je .LFUN_00046f10_76\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x4(%%esi), %%cx\n\t"
      "movl $0x2565d0, -0xd8(%%ebp)\n\t"
      "movl $0x25a830, -0xd4(%%ebp)\n\t"
      "movl $0x25a828, -0xd0(%%ebp)\n\t"
      "movl $0x25a820, -0xcc(%%ebp)\n\t"
      "movl $0x25a814, -0xc8(%%ebp)\n\t"
      "movl $0x25a810, -0xc4(%%ebp)\n\t"
      "movl -0xd8(%%ebp,%%eax,4), %%edx\n\t"
      "movswl -0x10(%%ebp), %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl $1\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1a67b0]\n\t"
      "addl $8, %%esp\n\t"
      "pushl %%eax\n\t"
      "pushl $0x25a7fc\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "pushl %%eax\n\t"
      "leal -0x106c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c8dc30]\n\t"
      "addl $0x1c, %%esp\n\t"
      ".LFUN_00046f10_76:\n\t"
      "movb $1, -0x9(%%ebp)\n\t"
      "jmp .LFUN_00046f10_165\n\t"
      ".LFUN_00046f10_77:\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x20(%%esi), %%ax\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .LFUN_00046f10_79\n\t"
      "cmpl $-1, 0xc(%%ebp)\n\t"
      "je .LFUN_00046f10_78\n\t"
      "andl -0x84(%%ebp), %%eax\n\t"
      "testw %%ax, %%ax\n\t"
      "jne .LFUN_00046f10_79\n\t"
      ".LFUN_00046f10_78:\n\t"
      "movb 0x5aca4f, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00046f10_82\n\t"
      "movswl -0x10(%%ebp), %%eax\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x4(%%esi), %%cx\n\t"
      "pushl %%eax\n\t"
      "pushl $1\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1a67b0]\n\t"
      "addl $8, %%esp\n\t"
      "pushl %%eax\n\t"
      "pushl $0x25a7e8\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "pushl %%eax\n\t"
      "leal -0x106c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c8dc30]\n\t"
      "addl $0x18, %%esp\n\t"
      "movb $1, -0x9(%%ebp)\n\t"
      "jmp .LFUN_00046f10_165\n\t"
      ".LFUN_00046f10_79:\n\t"
      "movl 0x10(%%ebp), %%edi\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x22(%%esi), %%ax\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .LFUN_00046f10_81\n\t"
      "cmpl $-1, %%edi\n\t"
      "je .LFUN_00046f10_80\n\t"
      "andl -0x9c(%%ebp), %%eax\n\t"
      "testw %%ax, %%ax\n\t"
      "jne .LFUN_00046f10_81\n\t"
      ".LFUN_00046f10_80:\n\t"
      "movb 0x5aca4f, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00046f10_82\n\t"
      "movswl -0x10(%%ebp), %%eax\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x4(%%esi), %%cx\n\t"
      "pushl %%eax\n\t"
      "pushl $1\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1a67b0]\n\t"
      "addl $8, %%esp\n\t"
      "pushl %%eax\n\t"
      "pushl $0x25a7d4\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "pushl %%eax\n\t"
      "leal -0x106c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c8dc30]\n\t"
      "addl $0x18, %%esp\n\t"
      "movb $1, -0x9(%%ebp)\n\t"
      "jmp .LFUN_00046f10_165\n\t"
      ".LFUN_00046f10_81:\n\t"
      "movw 0x24(%%esi), %%ax\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .LFUN_00046f10_83\n\t"
      "cmpw 0x18(%%ebp), %%ax\n\t"
      "je .LFUN_00046f10_83\n\t"
      "movb 0x5aca4f, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00046f10_82\n\t"
      "movswl -0x10(%%ebp), %%eax\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x4(%%esi), %%cx\n\t"
      "pushl %%eax\n\t"
      "pushl $1\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1a67b0]\n\t"
      "addl $8, %%esp\n\t"
      "pushl %%eax\n\t"
      "pushl $0x25a7c4\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "pushl %%eax\n\t"
      "leal -0x106c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c8dc30]\n\t"
      "addl $0x18, %%esp\n\t"
      ".LFUN_00046f10_82:\n\t"
      "movb $1, -0x9(%%ebp)\n\t"
      "jmp .LFUN_00046f10_165\n\t"
      ".LFUN_00046f10_83:\n\t"
      "movswl -0x24(%%ebp), %%eax\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "movw 0x257c68(,%%eax,2), %%bx\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "xorl %%eax, %%eax\n\t"
      "orl $0xffffffff, %%ecx\n\t"
      "movl %%eax, -0x68(%%ebp)\n\t"
      "movl %%eax, -0x4c(%%ebp)\n\t"
      "movl %%eax, -0x74(%%ebp)\n\t"
      "movl %%eax, -0x40(%%ebp)\n\t"
      "movb %%al, 0x17(%%ebp)\n\t"
      "movl %%eax, -0x50(%%ebp)\n\t"
      "leal -0x66c(%%ebp), %%eax\n\t"
      "pushl $0x25a7bc\n\t"
      "pushl %%eax\n\t"
      "movl %%ebx, -0x58(%%ebp)\n\t"
      "movl %%ecx, -0x20(%%ebp)\n\t"
      "movl %%ecx, -0x34(%%ebp)\n\t"
      "movl %%ecx, -0x6c(%%ebp)\n\t"
      "movl %%ecx, -0xb8(%%ebp)\n\t"
      "movl $0x3f800000, -0x70(%%ebp)\n\t"
      "movl $0x3f800000, -0x78(%%ebp)\n\t"
      "call *%[c8dff0]\n\t"
      "movswl 0x8(%%esi), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $4, %%eax\n\t"
      "ja .LFUN_00046f10_100\n\t"
      "jmp *.LFUN_00046f10_jt0(,%%eax,4)\n\t"
      ".LFUN_00046f10_84:\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "movl -0x8c(%%ebp), %%eax\n\t"
      "leal -0x28(%%ebp), %%ecx\n\t"
      "movl %%ecx, -0x40(%%ebp)\n\t"
      "movl -0x88(%%ebp), %%ecx\n\t"
      "movl %%edx, -0x34(%%ebp)\n\t"
      "movl %%eax, -0x20(%%ebp)\n\t"
      "movl %%ecx, -0x68(%%ebp)\n\t"
      "movl %%edi, -0x6c(%%ebp)\n\t"
      "jmp .LFUN_00046f10_101\n\t"
      ".LFUN_00046f10_85:\n\t"
      "movl -0xbc(%%ebp), %%eax\n\t"
      "movl -0xc0(%%ebp), %%ecx\n\t"
      "leal -0x30(%%ebp), %%edx\n\t"
      "movl %%edx, -0x40(%%ebp)\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "movl %%edi, -0x34(%%ebp)\n\t"
      "movl %%eax, -0x20(%%ebp)\n\t"
      "movl %%ecx, -0x68(%%ebp)\n\t"
      "movl %%edx, -0x6c(%%ebp)\n\t"
      "jmp .LFUN_00046f10_101\n\t"
      ".LFUN_00046f10_86:\n\t"
      "movb -0xa(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "movl %%edi, -0x6c(%%ebp)\n\t"
      "je .LFUN_00046f10_92\n\t"
      "movw 0x18(%%esi), %%cx\n\t"
      "movsbl %%cl, %%eax\n\t"
      "andl $1, %%eax\n\t"
      "orl $2, %%eax\n\t"
      "testb $0x10, %%cl\n\t"
      "je .LFUN_00046f10_87\n\t"
      "orl $4, %%eax\n\t"
      "jmp .LFUN_00046f10_88\n\t"
      ".LFUN_00046f10_87:\n\t"
      "andl $0xfffffffb, %%eax\n\t"
      ".LFUN_00046f10_88:\n\t"
      "testb $0x20, %%cl\n\t"
      "je .LFUN_00046f10_89\n\t"
      "orl $8, %%eax\n\t"
      "jmp .LFUN_00046f10_90\n\t"
      ".LFUN_00046f10_89:\n\t"
      "andl $0xfffffff7, %%eax\n\t"
      ".LFUN_00046f10_90:\n\t"
      "movl -0x90(%%ebp), %%ecx\n\t"
      "orl $0x10, %%eax\n\t"
      "pushl %%eax\n\t"
      "xorl %%eax, %%eax\n\t"
      "cmpl $-1, %%ecx\n\t"
      "movw 0x6(%%esi), %%ax\n\t"
      "pushl %%eax\n\t"
      "movl -0x24(%%ebp), %%eax\n\t"
      "je .LFUN_00046f10_91\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x4(%%esi), %%dx\n\t"
      "movl %%edi, %%esi\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "pushl %%edx\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "pushl %%edx\n\t"
      "movl %%ecx, %%eax\n\t"
      "pushl $0x41200000\n\t"
      "andl $0xffff, %%eax\n\t"
      "call *%[c45830]\n\t"
      "movl -0x3c(%%ebp), %%esi\n\t"
      "addl $0x1c, %%esp\n\t"
      "movl %%eax, -0x80(%%ebp)\n\t"
      "movb $0, -0xa(%%ebp)\n\t"
      "jmp .LFUN_00046f10_93\n\t"
      ".LFUN_00046f10_91:\n\t"
      "movl -0x58(%%ebp), %%edx\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "movl -0x98(%%ebp), %%ebx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x4(%%esi), %%cx\n\t"
      "pushl %%ecx\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "pushl %%edx\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x41200000\n\t"
      "pushl %%edx\n\t"
      "pushl $1\n\t"
      "call *%[c458f0]\n\t"
      "addl $0x24, %%esp\n\t"
      "movl %%eax, -0x80(%%ebp)\n\t"
      "movb $0, -0xa(%%ebp)\n\t"
      "jmp .LFUN_00046f10_93\n\t"
      ".LFUN_00046f10_92:\n\t"
      "movl -0x80(%%ebp), %%eax\n\t"
      ".LFUN_00046f10_93:\n\t"
      "cmpl $-1, %%eax\n\t"
      "movl %%eax, -0x20(%%ebp)\n\t"
      "je .LFUN_00046f10_101\n\t"
      "pushl %%eax\n\t"
      "movl 0x6325a4, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl 0x18(%%eax), %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "movl %%eax, -0x68(%%ebp)\n\t"
      "movl %%ecx, -0x34(%%ebp)\n\t"
      "jmp .LFUN_00046f10_101\n\t"
      ".LFUN_00046f10_94:\n\t"
      "movb -0x29(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "movl %%edi, -0x6c(%%ebp)\n\t"
      "je .LFUN_00046f10_99\n\t"
      "movw 0x18(%%esi), %%cx\n\t"
      "movsbl %%cl, %%eax\n\t"
      "andl $1, %%eax\n\t"
      "orl $2, %%eax\n\t"
      "testb $0x10, %%cl\n\t"
      "je .LFUN_00046f10_95\n\t"
      "orl $4, %%eax\n\t"
      "jmp .LFUN_00046f10_96\n\t"
      ".LFUN_00046f10_95:\n\t"
      "andl $0xfffffffb, %%eax\n\t"
      ".LFUN_00046f10_96:\n\t"
      "testb $0x20, %%cl\n\t"
      "je .LFUN_00046f10_97\n\t"
      "orl $8, %%eax\n\t"
      "jmp .LFUN_00046f10_98\n\t"
      ".LFUN_00046f10_97:\n\t"
      "andl $0xfffffff7, %%eax\n\t"
      ".LFUN_00046f10_98:\n\t"
      "movl -0x58(%%ebp), %%ecx\n\t"
      "pushl %%eax\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "movl -0x98(%%ebp), %%ebx\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x6(%%esi), %%dx\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x4(%%esi), %%ax\n\t"
      "pushl %%edx\n\t"
      "movl -0x24(%%ebp), %%edx\n\t"
      "pushl %%eax\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%ecx\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl $0x41400000\n\t"
      "pushl %%ecx\n\t"
      "pushl $2\n\t"
      "call *%[c458f0]\n\t"
      "addl $0x24, %%esp\n\t"
      "movl %%eax, -0xb0(%%ebp)\n\t"
      "movb $0, -0x29(%%ebp)\n\t"
      ".LFUN_00046f10_99:\n\t"
      "movl -0xb0(%%ebp), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "movl %%eax, -0x20(%%ebp)\n\t"
      "je .LFUN_00046f10_101\n\t"
      "movl 0x6325a4, %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%edx\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, -0x68(%%ebp)\n\t"
      "movl 0x18(%%eax), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "movl %%eax, -0x34(%%ebp)\n\t"
      "jmp .LFUN_00046f10_101\n\t"
      ".LFUN_00046f10_100:\n\t"
      "pushl $1\n\t"
      "pushl $0x594\n\t"
      "pushl $0x2599b4\n\t"
      "pushl $0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00046f10_101:\n\t"
      "movl -0x34(%%ebp), %%eax\n\t"
      "xorb %%bl, %%bl\n\t"
      "cmpl $-1, %%eax\n\t"
      "movl %%eax, %%edi\n\t"
      "je .LFUN_00046f10_102\n\t"
      "pushl $3\n\t"
      "pushl %%edi\n\t"
      "call *%[get]\n\t"
      "movb 0xb6(%%eax), %%cl\n\t"
      "addl $8, %%esp\n\t"
      "testb $4, %%cl\n\t"
      "jne .LFUN_00046f10_102\n\t"
      "cmpw $1, 0x64(%%eax)\n\t"
      "je .LFUN_00046f10_102\n\t"
      "movl 0x1c8(%%eax), %%edx\n\t"
      "orl $0xffffffff, %%ecx\n\t"
      "cmpl %%ecx, %%edx\n\t"
      "je .LFUN_00046f10_103\n\t"
      "cmpl %%ecx, 0x1a4(%%eax)\n\t"
      "jne .LFUN_00046f10_103\n\t"
      "testb $8, 0x18(%%esi)\n\t"
      "je .LFUN_00046f10_102\n\t"
      "movb $1, 0x17(%%ebp)\n\t"
      "movb $1, -0x35(%%ebp)\n\t"
      "jmp .LFUN_00046f10_103\n\t"
      ".LFUN_00046f10_102:\n\t"
      "movb $1, %%bl\n\t"
      ".LFUN_00046f10_103:\n\t"
      "movl -0x68(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_00046f10_104\n\t"
      "cmpw $0, 0x6a(%%eax)\n\t"
      "je .LFUN_00046f10_105\n\t"
      "cmpw $0xb, 0x6c(%%eax)\n\t"
      "jne .LFUN_00046f10_104\n\t"
      "movb 0xa0(%%eax), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "je .LFUN_00046f10_105\n\t"
      ".LFUN_00046f10_104:\n\t"
      "testb %%bl, %%bl\n\t"
      "je .LFUN_00046f10_110\n\t"
      ".LFUN_00046f10_105:\n\t"
      "movb 0x5aca4f, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00046f10_164\n\t"
      "movw 0x8(%%esi), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "jne .LFUN_00046f10_106\n\t"
      "movb $0x73, %%al\n\t"
      "jmp .LFUN_00046f10_109\n\t"
      ".LFUN_00046f10_106:\n\t"
      "cmpw $1, %%ax\n\t"
      "jne .LFUN_00046f10_107\n\t"
      "movb $0x63, %%al\n\t"
      "jmp .LFUN_00046f10_109\n\t"
      ".LFUN_00046f10_107:\n\t"
      "cmpw $2, %%ax\n\t"
      "jne .LFUN_00046f10_108\n\t"
      "movb $0x66, %%al\n\t"
      "jmp .LFUN_00046f10_109\n\t"
      ".LFUN_00046f10_108:\n\t"
      "cmpw $4, %%ax\n\t"
      "setne %%al\n\t"
      "decb %%al\n\t"
      "andb $0x26, %%al\n\t"
      "addb $0x3f, %%al\n\t"
      ".LFUN_00046f10_109:\n\t"
      "movswl -0x10(%%ebp), %%edx\n\t"
      "movsbl %%al, %%ecx\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x4(%%esi), %%ax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl $1\n\t"
      "pushl %%eax\n\t"
      "call *%[c1a67b0]\n\t"
      "addl $8, %%esp\n\t"
      "pushl %%eax\n\t"
      "pushl $0x25a7a8\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "pushl %%eax\n\t"
      "leal -0xa6c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c8dc30]\n\t"
      "addl $0x1c, %%esp\n\t"
      "jmp .LFUN_00046f10_164\n\t"
      ".LFUN_00046f10_110:\n\t"
      "movb 0x17(%%ebp), %%bl\n\t"
      "testb %%bl, %%bl\n\t"
      "je .LFUN_00046f10_112\n\t"
      "movl 0x18(%%ebp), %%eax\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x4(%%esi), %%cx\n\t"
      "leal -0x78(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl -0x6c(%%ebp), %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "call *%[c460e0]\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "addl $0x14, %%esp\n\t"
      "cmpl %%ecx, %%edi\n\t"
      "movl %%eax, -0xb8(%%ebp)\n\t"
      "jne .LFUN_00046f10_111\n\t"
      "movb $0, -0xa(%%ebp)\n\t"
      "movl %%eax, -0x80(%%ebp)\n\t"
      ".LFUN_00046f10_111:\n\t"
      "cmpl $-1, %%eax\n\t"
      "jne .LFUN_00046f10_112\n\t"
      "movb 0x5aca4f, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00046f10_164\n\t"
      "movswl -0x10(%%ebp), %%eax\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x4(%%esi), %%cx\n\t"
      "pushl %%eax\n\t"
      "pushl $1\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1a67b0]\n\t"
      "addl $8, %%esp\n\t"
      "pushl %%eax\n\t"
      "pushl $0x25a794\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "pushl %%eax\n\t"
      "leal -0xa6c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c8dc30]\n\t"
      "addl $0x18, %%esp\n\t"
      "jmp .LFUN_00046f10_164\n\t"
      ".LFUN_00046f10_112:\n\t"
      "movw 0x1a(%%esi), %%ax\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .LFUN_00046f10_115\n\t"
      "movl -0x40(%%ebp), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .LFUN_00046f10_115\n\t"
      "movswl %%ax, %%edx\n\t"
      "cmpb $0, (%%edx,%%ecx,1)\n\t"
      "jne .LFUN_00046f10_115\n\t"
      "movb 0x5aca4f, %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "je .LFUN_00046f10_164\n\t"
      "testw %%ax, %%ax\n\t"
      "jne .LFUN_00046f10_113\n\t"
      "movb $0x65, %%al\n\t"
      "jmp .LFUN_00046f10_114\n\t"
      ".LFUN_00046f10_113:\n\t"
      "cmpw $1, %%ax\n\t"
      "setne %%al\n\t"
      "decb %%al\n\t"
      "andb $0x35, %%al\n\t"
      "addb $0x3f, %%al\n\t"
      ".LFUN_00046f10_114:\n\t"
      "movswl -0x10(%%ebp), %%ecx\n\t"
      "movsbl %%al, %%eax\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x4(%%esi), %%dx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl $1\n\t"
      "pushl %%edx\n\t"
      "call *%[c1a67b0]\n\t"
      "addl $8, %%esp\n\t"
      "pushl %%eax\n\t"
      "pushl $0x25a780\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "pushl %%eax\n\t"
      "leal -0xa6c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c8dc30]\n\t"
      "addl $0x1c, %%esp\n\t"
      "jmp .LFUN_00046f10_164\n\t"
      ".LFUN_00046f10_115:\n\t"
      "testb %%bl, %%bl\n\t"
      "je .LFUN_00046f10_119\n\t"
      "movl -0x14(%%ebp), %%ecx\n\t"
      "movw 0x257cb8(,%%ecx,2), %%dx\n\t"
      "movw %%dx, -0x24(%%ebp)\n\t"
      "movl $0x40000000, -0x48(%%ebp)\n\t"
      "pushl $0x2569f0\n\t"
      ".LFUN_00046f10_116:\n\t"
      "leal -0x66c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c8dff0]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_00046f10_117:\n\t"
      "movswl 0x8(%%esi), %%eax\n\t"
      "flds 0x257e10(,%%eax,4)\n\t"
      "fmuls 0x253394\n\t"
      "call *%[ftol]\n\t"
      "movl $1, %%edi\n\t"
      "cmpw %%di, -0x84(%%ebp)\n\t"
      "jne .LFUN_00046f10_118\n\t"
      "movb 0x17(%%ebp), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "jne .LFUN_00046f10_118\n\t"
      "addl $0x1e, %%eax\n\t"
      ".LFUN_00046f10_118:\n\t"
      "testb $4, 0x18(%%esi)\n\t"
      "je .LFUN_00046f10_142\n\t"
      "flds 0x2533c0\n\t"
      "jmp .LFUN_00046f10_143\n\t"
      ".LFUN_00046f10_119:\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl $1\n\t"
      "pushl %%edi\n\t"
      "call *%[c441c0]\n\t"
      "fsts -0x48(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "addl $0x10, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .LFUN_00046f10_120\n\t"
      "movb 0x5aca4f, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00046f10_164\n\t"
      "movswl -0x10(%%ebp), %%ecx\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x4(%%esi), %%dx\n\t"
      "pushl %%ecx\n\t"
      "pushl $1\n\t"
      "pushl %%edx\n\t"
      "call *%[c1a67b0]\n\t"
      "addl $8, %%esp\n\t"
      "pushl %%eax\n\t"
      "pushl $0x25a76c\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "pushl %%eax\n\t"
      "leal -0xa6c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c8dc30]\n\t"
      "addl $0x18, %%esp\n\t"
      "jmp .LFUN_00046f10_164\n\t"
      ".LFUN_00046f10_120:\n\t"
      "flds -0x48(%%ebp)\n\t"
      "fcomps 0x257e44\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00046f10_121\n\t"
      "movb $1, %%bl\n\t"
      "jmp .LFUN_00046f10_122\n\t"
      ".LFUN_00046f10_121:\n\t"
      "xorb %%bl, %%bl\n\t"
      ".LFUN_00046f10_122:\n\t"
      "movl -0x20(%%ebp), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "movb %%bl, -0x1(%%ebp)\n\t"
      "je .LFUN_00046f10_125\n\t"
      "movl 0x6325a4, %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x4(%%eax), %%dx\n\t"
      "pushl %%edx\n\t"
      "call *%[c3a770]\n\t"
      "addl $0xc, %%esp\n\t"
      "orl $0xffffffff, %%edi\n\t"
      "testb $2, %%al\n\t"
      "je .LFUN_00046f10_123\n\t"
      "xorl %%edi, %%edi\n\t"
      "jmp .LFUN_00046f10_124\n\t"
      ".LFUN_00046f10_123:\n\t"
      "testb $4, %%al\n\t"
      "je .LFUN_00046f10_124\n\t"
      "movl $1, %%edi\n\t"
      ".LFUN_00046f10_124:\n\t"
      "cmpw $-1, %%di\n\t"
      "jne .LFUN_00046f10_126\n\t"
      ".LFUN_00046f10_125:\n\t"
      "pushl $0x25a760\n\t"
      "jmp .LFUN_00046f10_116\n\t"
      ".LFUN_00046f10_126:\n\t"
      "testw %%di, %%di\n\t"
      "jl .LFUN_00046f10_127\n\t"
      "cmpw $2, %%di\n\t"
      "jl .LFUN_00046f10_128\n\t"
      ".LFUN_00046f10_127:\n\t"
      "pushl $1\n\t"
      "pushl $0x62b\n\t"
      "pushl $0x2599b4\n\t"
      "pushl $0x25a708\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00046f10_128:\n\t"
      "movl -0x24(%%ebp), %%eax\n\t"
      "testw %%ax, %%ax\n\t"
      "jle .LFUN_00046f10_129\n\t"
      "cmpw $8, %%ax\n\t"
      "jl .LFUN_00046f10_130\n\t"
      ".LFUN_00046f10_129:\n\t"
      "pushl $1\n\t"
      "pushl $0x62e\n\t"
      "pushl $0x2599b4\n\t"
      "pushl $0x25a688\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00046f10_130:\n\t"
      "testb %%bl, %%bl\n\t"
      "movl $0x25a684, %%ecx\n\t"
      "jne .LFUN_00046f10_131\n\t"
      "movl $0x25a680, %%ecx\n\t"
      ".LFUN_00046f10_131:\n\t"
      "movl -0x14(%%ebp), %%edx\n\t"
      "movl 0x2c8d48(,%%edx,4), %%eax\n\t"
      "pushl %%ecx\n\t"
      "movsbl 0x2(%%eax), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movsbl 0x1(%%eax), %%ecx\n\t"
      "movsbl (%%eax), %%eax\n\t"
      "pushl %%ecx\n\t"
      "movswl %%di, %%edi\n\t"
      "movl 0x2c8d6c(,%%edi,8), %%ecx\n\t"
      "leal 0x2c8d6c(,%%edi,8), %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "movl %%edx, -0x94(%%ebp)\n\t"
      "leal -0x66c(%%ebp), %%edx\n\t"
      "pushl $0x25a674\n\t"
      "pushl %%edx\n\t"
      "call *%[c1d90f0]\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "movzbl -0x1(%%ebp), %%ebx\n\t"
      "leal (%%eax,%%edi,8), %%ecx\n\t"
      "leal (%%ebx,%%ecx,2), %%eax\n\t"
      "movb -0x16c(%%ebp,%%eax,1), %%cl\n\t"
      "addl $0x1c, %%esp\n\t"
      "testb %%cl, %%cl\n\t"
      "movl %%eax, -0x50(%%ebp)\n\t"
      "je .LFUN_00046f10_137\n\t"
      "cmpw $6, -0x24(%%ebp)\n\t"
      "jl .LFUN_00046f10_132\n\t"
      "pushl $1\n\t"
      "pushl $0x639\n\t"
      "pushl $0x2599b4\n\t"
      "pushl $0x25a638\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00046f10_132:\n\t"
      "movb 0x5aca4f, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00046f10_164\n\t"
      "movl -0x50(%%ebp), %%edx\n\t"
      "movw -0x1ec(%%ebp,%%edx,2), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "jne .LFUN_00046f10_133\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "leal (%%ebx,%%eax,2), %%eax\n\t"
      "leal (%%eax,%%eax,4), %%ecx\n\t"
      "flds 0x257cd0(,%%ecx,4)\n\t"
      "subl $0x10, %%esp\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "leal -0xc6c(%%ebp), %%edx\n\t"
      "flds -0x11c(%%ebp,%%edi,4)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x25a628\n\t"
      "pushl %%edx\n\t"
      "call *%[c1d90f0]\n\t"
      "addl $0x18, %%esp\n\t"
      "jmp .LFUN_00046f10_136\n\t"
      ".LFUN_00046f10_133:\n\t"
      "cmpw $1, %%ax\n\t"
      "jne .LFUN_00046f10_134\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "leal (%%ebx,%%eax,2), %%eax\n\t"
      "leal (%%eax,%%eax,4), %%ecx\n\t"
      "flds 0x257cd4(,%%ecx,4)\n\t"
      "subl $0x10, %%esp\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "leal -0xc6c(%%ebp), %%edx\n\t"
      "flds -0xfc(%%ebp,%%edi,4)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x25a618\n\t"
      "pushl %%edx\n\t"
      "call *%[c1d90f0]\n\t"
      "addl $0x18, %%esp\n\t"
      "jmp .LFUN_00046f10_136\n\t"
      ".LFUN_00046f10_134:\n\t"
      "cmpw $2, %%ax\n\t"
      "jne .LFUN_00046f10_135\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "leal (%%ebx,%%eax,2), %%eax\n\t"
      "leal (%%eax,%%eax,4), %%ecx\n\t"
      "flds 0x257cdc(,%%ecx,4)\n\t"
      "subl $0x10, %%esp\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "leal -0xc6c(%%ebp), %%edx\n\t"
      "flds -0xe8(%%ebp,%%edi,4)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x25a608\n\t"
      "pushl %%edx\n\t"
      "call *%[c1d90f0]\n\t"
      "addl $0x18, %%esp\n\t"
      "jmp .LFUN_00046f10_136\n\t"
      ".LFUN_00046f10_135:\n\t"
      "leal -0xc6c(%%ebp), %%eax\n\t"
      "pushl $0x25a7bc\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d90f0]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_00046f10_136:\n\t"
      "movswl -0x10(%%ebp), %%eax\n\t"
      "leal -0xc6c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x4(%%esi), %%cx\n\t"
      "leal -0x66c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl $1\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1a67b0]\n\t"
      "addl $8, %%esp\n\t"
      "pushl %%eax\n\t"
      "pushl $0x25a5f8\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "pushl %%eax\n\t"
      "leal -0xa6c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c8dc30]\n\t"
      "addl $0x20, %%esp\n\t"
      "jmp .LFUN_00046f10_164\n\t"
      ".LFUN_00046f10_137:\n\t"
      "cmpw $7, -0x24(%%ebp)\n\t"
      "movl -0x50(%%ebp), %%eax\n\t"
      "movw -0x1ac(%%ebp,%%eax,2), %%cx\n\t"
      "movw %%cx, -0x50(%%ebp)\n\t"
      "jge .LFUN_00046f10_117\n\t"
      "movswl -0x10(%%ebp), %%ebx\n\t"
      "movl 0x331f0c, %%eax\n\t"
      "leal (%%edi,%%ebx,2), %%edx\n\t"
      "leal (%%eax,%%edx,8), %%edi\n\t"
      "movl (%%edi), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_00046f10_139\n\t"
      "movl -0xa0(%%ebp), %%ecx\n\t"
      "subl %%eax, %%ecx\n\t"
      "movl %%ecx, -0x3c(%%ebp)\n\t"
      "fildl -0x3c(%%ebp)\n\t"
      "fmuls 0x25620c\n\t"
      "fsts -0x70(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00046f10_138\n\t"
      "movl $0, -0x70(%%ebp)\n\t"
      "jmp .LFUN_00046f10_139\n\t"
      ".LFUN_00046f10_138:\n\t"
      "flds -0x70(%%ebp)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00046f10_139\n\t"
      "movl $0x3f800000, -0x70(%%ebp)\n\t"
      ".LFUN_00046f10_139:\n\t"
      "call *%[cfff80]\n\t"
      "testw %%ax, %%ax\n\t"
      "jne .LFUN_00046f10_140\n\t"
      "movb 0x5aca46, %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00046f10_117\n\t"
      ".LFUN_00046f10_140:\n\t"
      "movl 0x4(%%edi), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_00046f10_117\n\t"
      "movl -0xa0(%%ebp), %%edx\n\t"
      "movb -0x1(%%ebp), %%cl\n\t"
      "subl %%edx, %%eax\n\t"
      "testb %%cl, %%cl\n\t"
      "je .LFUN_00046f10_141\n\t"
      "addl $0x1e, %%eax\n\t"
      ".LFUN_00046f10_141:\n\t"
      "testl %%eax, %%eax\n\t"
      "jle .LFUN_00046f10_117\n\t"
      "movb 0x5aca4f, %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "je .LFUN_00046f10_164\n\t"
      "movl -0x94(%%ebp), %%edx\n\t"
      "pushl %%eax\n\t"
      "movl (%%edx), %%eax\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x4(%%esi), %%cx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl $1\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1a67b0]\n\t"
      "addl $8, %%esp\n\t"
      "pushl %%eax\n\t"
      "pushl $0x25a5e0\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "pushl %%eax\n\t"
      "leal -0xa6c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c8dc30]\n\t"
      "addl $0x20, %%esp\n\t"
      "jmp .LFUN_00046f10_164\n\t"
      ".LFUN_00046f10_142:\n\t"
      "movswl -0x24(%%ebp), %%ecx\n\t"
      "flds 0x257c78(,%%ecx,4)\n\t"
      "fmuls 0x253394\n\t"
      ".LFUN_00046f10_143:\n\t"
      "movl -0x50(%%ebp), %%ebx\n\t"
      "addl %%ebx, %%eax\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "call *%[ftol]\n\t"
      "addl %%ebx, %%eax\n\t"
      "movl %%eax, -0xb4(%%ebp)\n\t"
      "movswl 0xc(%%esi), %%eax\n\t"
      "decl %%eax\n\t"
      "cmpl $3, %%eax\n\t"
      "ja .LFUN_00046f10_151\n\t"
      "jmp *.LFUN_00046f10_jt1(,%%eax,4)\n\t"
      ".LFUN_00046f10_144:\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_00046f10_151\n\t"
      "movl %%edi, -0x4c(%%ebp)\n\t"
      "jmp .LFUN_00046f10_149\n\t"
      ".LFUN_00046f10_145:\n\t"
      "movl -0x34(%%ebp), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_00046f10_151\n\t"
      "movl %%edi, -0x4c(%%ebp)\n\t"
      "jmp .LFUN_00046f10_149\n\t"
      ".LFUN_00046f10_146:\n\t"
      "movl -0x6c(%%ebp), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_00046f10_151\n\t"
      "movl %%edi, -0x4c(%%ebp)\n\t"
      "jmp .LFUN_00046f10_149\n\t"
      ".LFUN_00046f10_147:\n\t"
      "movl -0x8c(%%ebp), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_00046f10_151\n\t"
      "movl 0x6325a4, %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%edx\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%ebx\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $0, 0x280(%%ebx)\n\t"
      "jle .LFUN_00046f10_151\n\t"
      "cmpl $-1, 0x28c(%%ebx)\n\t"
      "jne .LFUN_00046f10_148\n\t"
      "pushl %%edi\n\t"
      "pushl $0x6b0\n\t"
      "pushl $0x2599b4\n\t"
      "pushl $0x25a5b0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00046f10_148:\n\t"
      "movl 0x28c(%%ebx), %%eax\n\t"
      "movl $2, -0x4c(%%ebp)\n\t"
      ".LFUN_00046f10_149:\n\t"
      "movl %%eax, -0x5c(%%ebp)\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0xe(%%esi), %%ax\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "movl %%eax, -0x74(%%ebp)\n\t"
      "je .LFUN_00046f10_150\n\t"
      "cmpw %%di, %%ax\n\t"
      "jne .LFUN_00046f10_151\n\t"
      ".LFUN_00046f10_150:\n\t"
      "movswl -0x24(%%ebp), %%ecx\n\t"
      "movw 0x257ca8(,%%ecx,2), %%dx\n\t"
      "movw %%dx, -0x74(%%ebp)\n\t"
      ".LFUN_00046f10_151:\n\t"
      "movw 0xa(%%esi), %%bx\n\t"
      "cmpw $-1, %%bx\n\t"
      "je .LFUN_00046f10_152\n\t"
      "cmpw %%di, %%bx\n\t"
      "jne .LFUN_00046f10_153\n\t"
      ".LFUN_00046f10_152:\n\t"
      "movswl -0x24(%%ebp), %%eax\n\t"
      "movw 0x257c98(,%%eax,2), %%bx\n\t"
      ".LFUN_00046f10_153:\n\t"
      "movb 0x17(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "movw 0x4(%%esi), %%cx\n\t"
      "movw 0x6(%%esi), %%dx\n\t"
      "movw %%cx, -0x94(%%ebp)\n\t"
      "movw %%dx, -0x40(%%ebp)\n\t"
      "movl $0xffffffff, -0x3c(%%ebp)\n\t"
      "movl $0x3f800000, -0x54(%%ebp)\n\t"
      "movl $0x3f800000, -0x7c(%%ebp)\n\t"
      "jne .LFUN_00046f10_158\n\t"
      "xorl %%edx, %%edx\n\t"
      "movb 0x18(%%esi), %%dl\n\t"
      "leal -0x126c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "leal -0x54(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl -0x24(%%ebp), %%ecx\n\t"
      "pushl $0\n\t"
      "andl $0xffffff01, %%edx\n\t"
      "pushl %%edx\n\t"
      "movl -0x34(%%ebp), %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "movl -0x58(%%ebp), %%edx\n\t"
      "leal -0x3c(%%ebp), %%eax\n\t"
      "leal -0x94(%%ebp), %%ecx\n\t"
      "call *%[c430d0]\n\t"
      "addl $0x1c, %%esp\n\t"
      "movl %%eax, %%edi\n\t"
      "testw %%di, %%di\n\t"
      "movl %%edi, -0xf4(%%ebp)\n\t"
      "jne .LFUN_00046f10_155\n\t"
      "movb 0x5aca4f, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00046f10_164\n\t"
      "flds -0x54(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "movl $0x25a244, %%eax\n\t"
      "je .LFUN_00046f10_154\n\t"
      "movl $0x25a240, %%eax\n\t"
      ".LFUN_00046f10_154:\n\t"
      "movswl -0x10(%%ebp), %%edx\n\t"
      "leal -0x126c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x4(%%esi), %%ax\n\t"
      "pushl %%edx\n\t"
      "pushl $1\n\t"
      "pushl %%eax\n\t"
      "call *%[c1a67b0]\n\t"
      "addl $8, %%esp\n\t"
      "pushl %%eax\n\t"
      "pushl $0x25a59c\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "pushl %%eax\n\t"
      "leal -0xa6c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c8dc30]\n\t"
      "addl $0x20, %%esp\n\t"
      "jmp .LFUN_00046f10_164\n\t"
      ".LFUN_00046f10_155:\n\t"
      "cmpw $-1, -0x40(%%ebp)\n\t"
      "je .LFUN_00046f10_159\n\t"
      "movl -0x40(%%ebp), %%edx\n\t"
      "movl -0x34(%%ebp), %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c1a97c0]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00046f10_159\n\t"
      "cmpl $-1, -0x20(%%ebp)\n\t"
      "je .LFUN_00046f10_157\n\t"
      "movl -0x68(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_00046f10_156\n\t"
      "pushl $1\n\t"
      "pushl $0x6f2\n\t"
      "pushl $0x2599b4\n\t"
      "pushl $0x25a588\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00046f10_156:\n\t"
      "movl -0x20(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1d6d0]\n\t"
      "addl $4, %%esp\n\t"
      "cmpw $2, %%ax\n\t"
      "je .LFUN_00046f10_159\n\t"
      "movl -0x68(%%ebp), %%edx\n\t"
      "cmpw $1, 0x6a(%%edx)\n\t"
      "je .LFUN_00046f10_159\n\t"
      ".LFUN_00046f10_157:\n\t"
      "movl $0x40000000, -0x7c(%%ebp)\n\t"
      "jmp .LFUN_00046f10_159\n\t"
      ".LFUN_00046f10_158:\n\t"
      "movl -0xf4(%%ebp), %%edi\n\t"
      ".LFUN_00046f10_159:\n\t"
      "flds -0x7c(%%ebp)\n\t"
      "fmuls -0x54(%%ebp)\n\t"
      "fmuls -0x48(%%ebp)\n\t"
      "fmuls 0x10(%%esi)\n\t"
      "fmuls -0x78(%%ebp)\n\t"
      "fmuls -0x70(%%ebp)\n\t"
      "fsts -0x40(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00046f10_165\n\t"
      "movl -0xa4(%%ebp), %%edx\n\t"
      "cmpw $0x10, %%dx\n\t"
      "jge .LFUN_00046f10_166\n\t"
      "movw -0x10(%%ebp), %%cx\n\t"
      "flds -0x40(%%ebp)\n\t"
      "movswl %%dx, %%eax\n\t"
      "imull $0x38, %%eax, %%eax\n\t"
      "movw %%cx, -0x538(%%ebp,%%eax,1)\n\t"
      "movb 0x17(%%ebp), %%cl\n\t"
      "movb %%cl, -0x567(%%ebp,%%eax,1)\n\t"
      "fstps -0x56c(%%ebp,%%eax,1)\n\t"
      "movl -0x34(%%ebp), %%ecx\n\t"
      "movl %%ecx, -0x558(%%ebp,%%eax,1)\n\t"
      "movl -0x20(%%ebp), %%ecx\n\t"
      "movl %%ecx, -0x554(%%ebp,%%eax,1)\n\t"
      "movw 0x6(%%esi), %%cx\n\t"
      "movw %%cx, -0x562(%%ebp,%%eax,1)\n\t"
      "movl -0x6c(%%ebp), %%ecx\n\t"
      "movl %%ecx, -0x550(%%ebp,%%eax,1)\n\t"
      "movl -0xb8(%%ebp), %%ecx\n\t"
      "movl %%ecx, -0x54c(%%ebp,%%eax,1)\n\t"
      "movw -0x58(%%ebp), %%cx\n\t"
      "movw %%cx, -0x564(%%ebp,%%eax,1)\n\t"
      "movw -0x14(%%ebp), %%cx\n\t"
      "movw %%cx, -0x55e(%%ebp,%%eax,1)\n\t"
      "movw -0xb4(%%ebp), %%cx\n\t"
      "movw %%cx, -0x55c(%%ebp,%%eax,1)\n\t"
      "movw -0x94(%%ebp), %%cx\n\t"
      "movw %%cx, -0x566(%%ebp,%%eax,1)\n\t"
      "movl -0x3c(%%ebp), %%ecx\n\t"
      "movl %%ecx, -0x53c(%%ebp,%%eax,1)\n\t"
      "movw -0x74(%%ebp), %%cx\n\t"
      "movw %%cx, -0x546(%%ebp,%%eax,1)\n\t"
      "movw -0x4c(%%ebp), %%cx\n\t"
      "movw %%cx, -0x544(%%ebp,%%eax,1)\n\t"
      "movl -0x5c(%%ebp), %%ecx\n\t"
      "movl %%ecx, -0x540(%%ebp,%%eax,1)\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movb 0x18(%%esi), %%cl\n\t"
      "movw %%di, -0x560(%%ebp,%%eax,1)\n\t"
      "movw %%bx, -0x548(%%ebp,%%eax,1)\n\t"
      "shrl $1, %%ecx\n\t"
      "andb $1, %%cl\n\t"
      "movb %%cl, -0x568(%%ebp,%%eax,1)\n\t"
      "je .LFUN_00046f10_160\n\t"
      "movb $1, -0x36(%%ebp)\n\t"
      ".LFUN_00046f10_160:\n\t"
      "movb 0x5aca4f, %%al\n\t"
      "incl %%edx\n\t"
      "testb %%al, %%al\n\t"
      "movl %%edx, -0xa4(%%ebp)\n\t"
      "je .LFUN_00046f10_163\n\t"
      "movb 0x17(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "movl $0x25a580, %%edi\n\t"
      "jne .LFUN_00046f10_161\n\t"
      "movl $0x25386f, %%edi\n\t"
      ".LFUN_00046f10_161:\n\t"
      "movswl %%dx, %%eax\n\t"
      "imull $0x38, %%eax, %%eax\n\t"
      "movb -0x5a0(%%ebp,%%eax,1), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "movl $0x25a57c, %%ecx\n\t"
      "jne .LFUN_00046f10_162\n\t"
      "movl $0x25386f, %%ecx\n\t"
      ".LFUN_00046f10_162:\n\t"
      "flds -0x5a4(%%ebp,%%eax,1)\n\t"
      "subl $0x20, %%esp\n\t"
      "fstpl 0x18(%%esp)\n\t"
      "movswl -0x50(%%ebp), %%edx\n\t"
      "flds -0x78(%%ebp)\n\t"
      "leal -0x66c(%%ebp), %%eax\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds -0x70(%%ebp)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds -0x7c(%%ebp)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl %%edi\n\t"
      "flds -0x48(%%ebp)\n\t"
      "subl $0x10, %%esp\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds -0x54(%%ebp)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl %%ecx\n\t"
      "flds 0x10(%%esi)\n\t"
      "movswl -0x10(%%ebp), %%ecx\n\t"
      "subl $8, %%esp\n\t"
      "fstpl (%%esp)\n\t"
      "pushl %%edx\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x4(%%esi), %%dx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl $1\n\t"
      "pushl %%edx\n\t"
      "call *%[c1a67b0]\n\t"
      "addl $8, %%esp\n\t"
      "pushl %%eax\n\t"
      "pushl $0x25a538\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "pushl %%eax\n\t"
      "leal -0xa6c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c8dc30]\n\t"
      "addl $0x60, %%esp\n\t"
      ".LFUN_00046f10_163:\n\t"
      "flds -0x40(%%ebp)\n\t"
      "fadds -0x44(%%ebp)\n\t"
      "fstps -0x44(%%ebp)\n\t"
      ".LFUN_00046f10_164:\n\t"
      "movb $1, -0x2(%%ebp)\n\t"
      ".LFUN_00046f10_165:\n\t"
      "movl -0x10(%%ebp), %%ecx\n\t"
      "addl $0x28, %%esi\n\t"
      "incl %%ecx\n\t"
      "movl %%ecx, -0x10(%%ebp)\n\t"
      "movw 0x8(%%ebp), %%cx\n\t"
      "cmpw %%cx, (%%esi)\n\t"
      "movl %%esi, -0x3c(%%ebp)\n\t"
      "je .LFUN_00046f10_71\n\t"
      "jmp .LFUN_00046f10_167\n\t"
      ".LFUN_00046f10_166:\n\t"
      "movl -0x64(%%ebp), %%eax\n\t"
      "movl 0x2c8d78(,%%eax,4), %%edx\n\t"
      "pushl $0x10\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl $0x25a4d8\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00046f10_167:\n\t"
      "movb 0x5aca50, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00046f10_168\n\t"
      "movb -0x35(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00046f10_168\n\t"
      "movb $1, -0x7(%%ebp)\n\t"
      ".LFUN_00046f10_168:\n\t"
      "movl -0xa4(%%ebp), %%esi\n\t"
      "testw %%si, %%si\n\t"
      "jle .LFUN_00046f10_191\n\t"
      "movb -0x36(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "leal -0x56c(%%ebp), %%ebx\n\t"
      "je .LFUN_00046f10_174\n\t"
      "movl -0x44(%%ebp), %%eax\n\t"
      "xorl %%edi, %%edi\n\t"
      "testw %%si, %%si\n\t"
      "movl %%eax, 0xc(%%ebp)\n\t"
      "movl %%edi, -0x44(%%ebp)\n\t"
      "jle .LFUN_00046f10_172\n\t"
      "leal -0x56c(%%ebp), %%eax\n\t"
      "movzwl %%si, %%ecx\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".LFUN_00046f10_169:\n\t"
      "movb 0x4(%%eax), %%dl\n\t"
      "testb %%dl, %%dl\n\t"
      "je .LFUN_00046f10_170\n\t"
      "incl %%edi\n\t"
      "jmp .LFUN_00046f10_171\n\t"
      ".LFUN_00046f10_170:\n\t"
      "movl $0, (%%eax)\n\t"
      ".LFUN_00046f10_171:\n\t"
      "flds -0x44(%%ebp)\n\t"
      "addl $0x38, %%eax\n\t"
      "decl %%ecx\n\t"
      "fadds -0x38(%%eax)\n\t"
      "fstps -0x44(%%ebp)\n\t"
      "jne .LFUN_00046f10_169\n\t"
      "flds -0x44(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .LFUN_00046f10_173\n\t"
      ".LFUN_00046f10_172:\n\t"
      "pushl $1\n\t"
      "pushl $0x76e\n\t"
      "pushl $0x2599b4\n\t"
      "pushl $0x25a4b8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00046f10_173:\n\t"
      "movb 0x5aca4f, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00046f10_174\n\t"
      "flds -0x44(%%ebp)\n\t"
      "subl $8, %%esp\n\t"
      "fstpl (%%esp)\n\t"
      "movswl %%di, %%ecx\n\t"
      "flds 0xc(%%ebp)\n\t"
      "pushl %%ecx\n\t"
      "subl $8, %%esp\n\t"
      "movswl %%si, %%edx\n\t"
      "fstpl (%%esp)\n\t"
      "pushl %%edx\n\t"
      "pushl $0x25a49c\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "pushl %%eax\n\t"
      "leal -0xa6c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c8dc30]\n\t"
      "addl $0x28, %%esp\n\t"
      ".LFUN_00046f10_174:\n\t"
      "cmpw $1, %%si\n\t"
      "jle .LFUN_00046f10_178\n\t"
      "movl $0, 0xc(%%ebp)\n\t"
      "call *%[gseed]\n\t"
      "pushl %%eax\n\t"
      "call *%[rmreal]\n\t"
      "fmuls -0x44(%%ebp)\n\t"
      "flds 0xc(%%ebp)\n\t"
      "movswl %%si, %%eax\n\t"
      "leal -0x1(%%eax), %%edx\n\t"
      "addl $4, %%esp\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "testl %%edx, %%edx\n\t"
      "jle .LFUN_00046f10_176\n\t"
      "xorl %%eax, %%eax\n\t"
      ".LFUN_00046f10_175:\n\t"
      "imull $0x38, %%eax, %%eax\n\t"
      "fadds -0x56c(%%ebp,%%eax,1)\n\t"
      ".byte 0xd8, 0xd1\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "je .LFUN_00046f10_176\n\t"
      "incl %%ecx\n\t"
      "movswl %%cx, %%eax\n\t"
      "cmpl %%edx, %%eax\n\t"
      "jl .LFUN_00046f10_175\n\t"
      ".LFUN_00046f10_176:\n\t"
      "movswl %%cx, %%eax\n\t"
      "movl %%eax, %%ecx\n\t"
      "imull $0x38, %%ecx, %%ecx\n\t"
      "leal -0x56c(%%ebp,%%ecx,1), %%ebx\n\t"
      "movb 0x5aca4f, %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "je .LFUN_00046f10_177\n\t"
      "pushl %%eax\n\t"
      "subl $0x18, %%esp\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds -0x44(%%ebp)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x25a47c\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "pushl %%eax\n\t"
      "leal -0xa6c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c8dc30]\n\t"
      "addl $0x2c, %%esp\n\t"
      "jmp .LFUN_00046f10_178\n\t"
      ".LFUN_00046f10_177:\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      ".LFUN_00046f10_178:\n\t"
      "movw 0x8(%%ebp), %%ax\n\t"
      "movw 0x18(%%ebp), %%cx\n\t"
      "movw 0x26(%%ebx), %%dx\n\t"
      "movw %%ax, -0xdc(%%ebp)\n\t"
      "movl 0x1c(%%ebx), %%eax\n\t"
      "movl %%eax, 0xc(%%ebp)\n\t"
      "movl %%eax, -0xe0(%%ebp)\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x34(%%ebx), %%ax\n\t"
      "movw %%ax, -0xda(%%ebp)\n\t"
      "movw %%dx, -0xd4(%%ebp)\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw %%cx, -0xd8(%%ebp)\n\t"
      "movl 0x2c(%%ebx), %%ecx\n\t"
      "movb $1, -0xd6(%%ebp)\n\t"
      "movl %%eax, 0x18(%%ebp)\n\t"
      "movw 0x28(%%ebx), %%ax\n\t"
      "movw %%ax, -0xd2(%%ebp)\n\t"
      "movl 0x1c(%%ebp), %%eax\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "sete %%dl\n\t"
      "movl %%ecx, -0xd0(%%ebp)\n\t"
      "decl %%edx\n\t"
      "andl %%eax, %%edx\n\t"
      "movl 0x20(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "movw %%dx, -0xcc(%%ebp)\n\t"
      "jne .LFUN_00046f10_179\n\t"
      "pushl $8\n\t"
      "pushl %%eax\n\t"
      "leal -0xc8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[memset]\n\t"
      "addl $0xc, %%esp\n\t"
      "jmp .LFUN_00046f10_180\n\t"
      ".LFUN_00046f10_179:\n\t"
      "movl (%%eax), %%ecx\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl %%ecx, -0xc8(%%ebp)\n\t"
      "movl %%edx, -0xc4(%%ebp)\n\t"
      ".LFUN_00046f10_180:\n\t"
      "movb 0x5(%%ebx), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00046f10_182\n\t"
      "movl 0x20(%%ebx), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "movl %%eax, 0xc(%%ebp)\n\t"
      "jne .LFUN_00046f10_181\n\t"
      "pushl $1\n\t"
      "pushl $0x7a7\n\t"
      "pushl $0x2599b4\n\t"
      "pushl $0x25a440\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00046f10_181:\n\t"
      "xorl %%esi, %%esi\n\t"
      "movw 0x6(%%ebx), %%si\n\t"
      "xorl %%edi, %%edi\n\t"
      "movw 0x8(%%ebx), %%di\n\t"
      "movl 0x14(%%ebx), %%ebx\n\t"
      "leal -0xe0(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "call *%[c44fd0]\n\t"
      "leal -0xe0(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "call *%[c45290]\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "leal -0xe0(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl $1\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "call *%[c46530]\n\t"
      "addl $0x38, %%esp\n\t"
      "jmp .LFUN_00046f10_190\n\t"
      ".LFUN_00046f10_182:\n\t"
      "movw 0xe(%%ebx), %%dx\n\t"
      "movl 0x30(%%ebx), %%ecx\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x8(%%ebx), %%ax\n\t"
      "movw %%ax, -0x14c(%%ebp)\n\t"
      "movw %%dx, -0x144(%%ebp)\n\t"
      "movl %%ecx, -0x148(%%ebp)\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0xc(%%ebx), %%dx\n\t"
      "movw $0x18, -0x140(%%ebp)\n\t"
      "movl %%eax, -0x64(%%ebp)\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x6(%%ebx), %%ax\n\t"
      "movw %%ax, -0x14a(%%ebp)\n\t"
      "movl $8, %%ecx\n\t"
      "leal -0xe0(%%ebp), %%esi\n\t"
      "leal -0x13c(%%ebp), %%edi\n\t"
      "movl %%eax, 0x14(%%ebp)\n\t"
      "movw 0x10(%%ebx), %%ax\n\t"
      "movw %%ax, -0x142(%%ebp)\n\t"
      "rep movsl\n\t"
      "movl 0x14(%%ebx), %%edi\n\t"
      "leal -0x14c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "call *%[c1a6ef0]\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpw $-1, 0xa(%%ebx)\n\t"
      "je .LFUN_00046f10_186\n\t"
      "pushl $3\n\t"
      "pushl %%edi\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x24(%%esi), %%eax\n\t"
      "movl %%eax, -0x1c(%%ebp)\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "movl 0x28(%%esi), %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "movl %%ecx, -0x18(%%ebp)\n\t"
      "je .LFUN_00046f10_185\n\t"
      "leal -0x100(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "call *%[c1a9200]\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "leal -0xec(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1a9200]\n\t"
      "flds -0xec(%%ebp)\n\t"
      "fsubs -0x100(%%ebp)\n\t"
      "addl $0x10, %%esp\n\t"
      "fstps -0x1c(%%ebp)\n\t"
      "flds -0xe8(%%ebp)\n\t"
      "fsubs -0xfc(%%ebp)\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fmuls -0x1c(%%ebp)\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fmuls -0x18(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fsqrt\n\t"
      "fld %%st(0)\n\t"
      "fabs\n\t"
      "fcompl 0x2533d0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .LFUN_00046f10_183\n\t"
      "flds 0x2533c8\n\t"
      ".byte 0xd8, 0xf1\n\t"
      "flds -0x1c(%%ebp)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fstps -0x1c(%%ebp)\n\t"
      "flds -0x18(%%ebp)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .LFUN_00046f10_185\n\t"
      "jmp .LFUN_00046f10_184\n\t"
      ".LFUN_00046f10_183:\n\t"
      "fstp %%st(0)\n\t"
      ".LFUN_00046f10_184:\n\t"
      "movl 0x24(%%esi), %%edx\n\t"
      "movl %%edx, -0x1c(%%ebp)\n\t"
      "movl 0x28(%%esi), %%eax\n\t"
      "movl %%eax, -0x18(%%ebp)\n\t"
      ".LFUN_00046f10_185:\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0xa(%%ebx), %%ax\n\t"
      "leal -0x1c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "call *%[c1b1a20]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_00046f10_186:\n\t"
      "movl 0x18(%%ebx), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "movl %%eax, 0x8(%%ebp)\n\t"
      "je .LFUN_00046f10_189\n\t"
      "movswl 0x24(%%ebx), %%ebx\n\t"
      "testw %%bx, %%bx\n\t"
      "movl %%ebx, 0x10(%%ebp)\n\t"
      "jle .LFUN_00046f10_189\n\t"
      "movl 0xc(%%ebp), %%esi\n\t"
      "cmpl $-1, %%esi\n\t"
      "je .LFUN_00046f10_189\n\t"
      "pushl $3\n\t"
      "pushl %%esi\n\t"
      "call *%[tryget]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_00046f10_189\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edx\n\t"
      "call *%[c64ab0]\n\t"
      "movl %%eax, %%ebx\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%ebx\n\t"
      "je .LFUN_00046f10_187\n\t"
      "movl 0x5ab23c, %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movw 0x24(%%eax), %%ax\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $2, %%ax\n\t"
      "jl .LFUN_00046f10_187\n\t"
      "cmpw $3, %%ax\n\t"
      "jg .LFUN_00046f10_187\n\t"
      "movw $1, -0xf0(%%ebp)\n\t"
      "movl %%ebx, -0xec(%%ebp)\n\t"
      "jmp .LFUN_00046f10_188\n\t"
      ".LFUN_00046f10_187:\n\t"
      "leal -0xec(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "movw $3, -0xf0(%%ebp)\n\t"
      "call *%[c1a9200]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_00046f10_188:\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "leal -0xf0(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl $9\n\t"
      "pushl %%ecx\n\t"
      "call *%[c27a60]\n\t"
      "addl $0x10, %%esp\n\t"
      ".LFUN_00046f10_189:\n\t"
      "movl 0x18(%%ebp), %%edx\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "movl -0x64(%%ebp), %%ecx\n\t"
      "pushl $-1\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "movl %%edi, %%eax\n\t"
      "call *%[c43f20]\n\t"
      "movl 0x14(%%ebp), %%esi\n\t"
      "addl $0x10, %%esp\n\t"
      ".LFUN_00046f10_190:\n\t"
      "movb 0x5aca4f, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00046f10_194\n\t"
      "pushl $1\n\t"
      "pushl %%esi\n\t"
      "call *%[c1a67b0]\n\t"
      "pushl %%eax\n\t"
      "pushl $0x25a218\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "pushl %%eax\n\t"
      "call *%[c8d970]\n\t"
      "pushl %%eax\n\t"
      "leal -0xa6c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c8dc30]\n\t"
      "movb -0x7(%%ebp), %%al\n\t"
      "addl $0x20, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00046f10_194\n\t"
      "leal -0xa6c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00046f10_191:\n\t"
      "movb 0x5aca4f, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00046f10_194\n\t"
      "movb -0x9(%%ebp), %%bl\n\t"
      "testb %%bl, %%bl\n\t"
      "je .LFUN_00046f10_192\n\t"
      "movb -0x2(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00046f10_192\n\t"
      "leal -0x106c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0xa6c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c8dc30]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_00046f10_192:\n\t"
      "movb 0x5aca44, %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00046f10_193\n\t"
      "testb %%bl, %%bl\n\t"
      "je .LFUN_00046f10_193\n\t"
      "movb -0x2(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00046f10_194\n\t"
      ".LFUN_00046f10_193:\n\t"
      "leal -0xa6c(%%ebp), %%eax\n\t"
      "pushl $0x253a04\n\t"
      "pushl %%eax\n\t"
      "call *%[c8dc30]\n\t"
      "movb -0x7(%%ebp), %%al\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00046f10_194\n\t"
      "leal -0xa6c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_00046f10_194:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "leal (%%ecx), %%ecx\n\t"
      "pushl $0x85b2c\n\t"
      "pushl $0\n\t"
      "pushl $0x5ac9c0\n\t"
      "call *%[memset]\n\t"
      "movl 0x331f58, %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "movl $0xffffffff, 0x5ac9f8\n\t"
      "movl $0xffffffff, 0x5ac9f4\n\t"
      "movl $1, 0x5acab4\n\t"
      "movb $1, 0x5aca65\n\t"
      "jne .LFUN_00046f10_195\n\t"
      "pushl $0x93\n\t"
      "pushl $0x25ab74\n\t"
      "pushl $0\n\t"
      "pushl $0x657c00\n\t"
      "call *%[c8ee60]\n\t"
      "addl $0x10, %%esp\n\t"
      "movl %%eax, 0x331f58\n\t"
      ".LFUN_00046f10_195:\n\t"
      "movl 0x331f5c, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_00046f10_196\n\t"
      "pushl $0x94\n\t"
      "pushl $0x25ab74\n\t"
      "pushl %%eax\n\t"
      "pushl $0x394f80\n\t"
      "call *%[c8ee60]\n\t"
      "addl $0x10, %%esp\n\t"
      "movl %%eax, 0x331f5c\n\t"
      ".LFUN_00046f10_196:\n\t"
      "movl 0x331f58, %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .LFUN_00046f10_197\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_00046f10_198\n\t"
      ".LFUN_00046f10_197:\n\t"
      "pushl $1\n\t"
      "pushl $0x96\n\t"
      "pushl $0x25ab74\n\t"
      "pushl $0x25ab48\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00046f10_198:\n\t"
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
      "movl 0x331f58, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_00046f10_199\n\t"
      "pushl $0xa0\n\t"
      "pushl $0x25ab74\n\t"
      "pushl %%eax\n\t"
      "call *%[c8ef70]\n\t"
      "addl $0xc, %%esp\n\t"
      "movl $0, 0x331f58\n\t"
      ".LFUN_00046f10_199:\n\t"
      "movl 0x331f5c, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_00046f10_200\n\t"
      "pushl $0xa6\n\t"
      "pushl $0x25ab74\n\t"
      "pushl %%eax\n\t"
      "call *%[c8ef70]\n\t"
      "addl $0xc, %%esp\n\t"
      "movl $0, 0x331f5c\n\t"
      ".LFUN_00046f10_200:\n\t"
      "ret\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "call *%[c18e3b0]\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_00046f10_201\n\t"
      "movl 0x5ac9f4, %%ecx\n\t"
      "cmpl $-1, %%ecx\n\t"
      "je .LFUN_00046f10_201\n\t"
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
      ".LFUN_00046f10_201:\n\t"
      "pushl $0x25386f\n\t"
      "pushl $0x5ac9d2\n\t"
      "call *%[c8dff0]\n\t"
      "addl $8, %%esp\n\t"
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
      "movl 0x331f58, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_00046f10_202\n\t"
      "pushl $1\n\t"
      "pushl $0xd0\n\t"
      "pushl $0x25ab74\n\t"
      "pushl $0x25abac\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00046f10_202:\n\t"
      "movl 0x331f58, %%eax\n\t"
      "pushl $0x657c00\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "call *%[memset]\n\t"
      "movl 0x331f5c, %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_00046f10_203\n\t"
      "pushl $1\n\t"
      "pushl $0xd3\n\t"
      "pushl $0x25ab74\n\t"
      "pushl $0x25ab94\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00046f10_203:\n\t"
      "movl 0x331f5c, %%ecx\n\t"
      "pushl $0x394f80\n\t"
      "pushl $0\n\t"
      "pushl %%ecx\n\t"
      "call *%[memset]\n\t"
      "addl $0xc, %%esp\n\t"
      "ret\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_00046f10_jt0:\n\t"
      ".long .LFUN_00046f10_84\n\t"
      ".long .LFUN_00046f10_85\n\t"
      ".long .LFUN_00046f10_86\n\t"
      ".long .LFUN_00046f10_100\n\t"
      ".long .LFUN_00046f10_94\n\t"
      ".text\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_00046f10_jt1:\n\t"
      ".long .LFUN_00046f10_144\n\t"
      ".long .LFUN_00046f10_145\n\t"
      ".long .LFUN_00046f10_146\n\t"
      ".long .LFUN_00046f10_147\n\t"
      ".text\n\t"
      :
      : [chkstk] "m"(b46f10_chkstk), [gtime] "m"(b46f10_gtime), [assert] "m"(b46f10_assert), [exitfn] "m"(b46f10_exitfn), [get] "m"(b46f10_get), [c41040] "m"(b46f10_c41040), [dget] "m"(b46f10_dget), [c3a770] "m"(b46f10_c3a770), [ca7a90] "m"(b46f10_ca7a90), [c458f0] "m"(b46f10_c458f0), [cff4d0] "m"(b46f10_cff4d0), [ca8040] "m"(b46f10_ca8040), [c40150] "m"(b46f10_c40150), [ca7b40] "m"(b46f10_ca7b40), [ca7a30] "m"(b46f10_ca7a30), [c1d90f0] "m"(b46f10_c1d90f0), [c8d970] "m"(b46f10_c8d970), [c8dff0] "m"(b46f10_c8dff0), [memset] "m"(b46f10_memset), [ftol] "m"(b46f10_ftol), [c8dc30] "m"(b46f10_c8dc30), [c8f390] "m"(b46f10_c8f390), [cfff80] "m"(b46f10_cfff80), [c1a67b0] "m"(b46f10_c1a67b0), [c8d9d0] "m"(b46f10_c8d9d0), [c1cb990] "m"(b46f10_c1cb990), [c45830] "m"(b46f10_c45830), [c460e0] "m"(b46f10_c460e0), [c441c0] "m"(b46f10_c441c0), [c430d0] "m"(b46f10_c430d0), [c1a97c0] "m"(b46f10_c1a97c0), [c1d6d0] "m"(b46f10_c1d6d0), [gseed] "m"(b46f10_gseed), [rmreal] "m"(b46f10_rmreal), [c44fd0] "m"(b46f10_c44fd0), [c45290] "m"(b46f10_c45290), [c46530] "m"(b46f10_c46530), [c1a6ef0] "m"(b46f10_c1a6ef0), [c1a9200] "m"(b46f10_c1a9200), [c1b1a20] "m"(b46f10_c1b1a20), [tryget] "m"(b46f10_tryget), [c64ab0] "m"(b46f10_c64ab0), [c27a60] "m"(b46f10_c27a60), [c43f20] "m"(b46f10_c43f20), [c8ee60] "m"(b46f10_c8ee60), [c8ef70] "m"(b46f10_c8ef70), [c18e3b0] "m"(b46f10_c18e3b0), [elem] "m"(b46f10_elem), [c8de70] "m"(b46f10_c8de70)
      : "memory");
}
#else
#error "FUN_00046f10: clang naked draft required"
#endif

/* --- ai_communication.obj orphan shells (2026-07-26) --- */

/* ai_debug_initialize (0x48e90) — XBE naked draft (batch 92). */
#if defined(__clang__)
static void *(*const b48e90_memset)(void *, int, unsigned int) = csmemset;
static void * (*const b48e90_c8ee60)(uint32_t size, bool zero, const char *file, int line) = debug_malloc;
static void (*const b48e90_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b48e90_exitfn)(int) = system_exit;

__attribute__((naked, noinline))
void ai_debug_initialize(void)
{
  __asm__ volatile(
      "pushl $0x85b2c\n\t"
      "pushl $0\n\t"
      "pushl $0x5ac9c0\n\t"
      "call *%[memset]\n\t"
      "movl 0x331f58, %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "movl $0xffffffff, 0x5ac9f8\n\t"
      "movl $0xffffffff, 0x5ac9f4\n\t"
      "movl $1, 0x5acab4\n\t"
      "movb $1, 0x5aca65\n\t"
      "jne .Lai_debug_initialize_1\n\t"
      "pushl $0x93\n\t"
      "pushl $0x25ab74\n\t"
      "pushl $0\n\t"
      "pushl $0x657c00\n\t"
      "call *%[c8ee60]\n\t"
      "addl $0x10, %%esp\n\t"
      "movl %%eax, 0x331f58\n\t"
      ".Lai_debug_initialize_1:\n\t"
      "movl 0x331f5c, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lai_debug_initialize_2\n\t"
      "pushl $0x94\n\t"
      "pushl $0x25ab74\n\t"
      "pushl %%eax\n\t"
      "pushl $0x394f80\n\t"
      "call *%[c8ee60]\n\t"
      "addl $0x10, %%esp\n\t"
      "movl %%eax, 0x331f5c\n\t"
      ".Lai_debug_initialize_2:\n\t"
      "movl 0x331f58, %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .Lai_debug_initialize_3\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lai_debug_initialize_4\n\t"
      ".Lai_debug_initialize_3:\n\t"
      "pushl $1\n\t"
      "pushl $0x96\n\t"
      "pushl $0x25ab74\n\t"
      "pushl $0x25ab48\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lai_debug_initialize_4:\n\t"
      "ret\n\t"
      :
      : [memset] "m"(b48e90_memset), [c8ee60] "m"(b48e90_c8ee60), [assert] "m"(b48e90_assert), [exitfn] "m"(b48e90_exitfn)
      : "memory");
}
#else
#error "ai_debug_initialize: clang naked draft required"
#endif

