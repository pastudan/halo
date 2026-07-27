#include <stdarg.h>

#define network_machine_is_valid(m) ((m) != NULL && *(char *)((char *)(m) + 0x40) >= 0 && *(char *)((char *)(m) + 0x40) < 4)


bool network_player_is_valid(void *client)
{
  char *c = (char *)client;
  if (c != NULL &&
      c[0x1d] >= 0 && c[0x1d] < 4 &&
      c[0x1c] >= 0 && c[0x1c] < 4) {
    return true;
  }
  return false;
}

wchar_t *network_game_get_random_player_name(void)
{
  int iVar1;
  short *psVar2;
  int uVar3;
  wchar_t *puVar4;

  iVar1 = tag_loaded(0x75737472, "ui\\random_player_names");
  if (iVar1 != -1) {
    psVar2 = (short *)tag_get(0x75737472, iVar1);
    if (psVar2 != NULL) {
      uVar3 = random_range(random_math_get_local_seed_address(), 0, *psVar2 - 1);
      puVar4 = (wchar_t *)FUN_0019d420(iVar1, uVar3);
      return puVar4;
    }
  }
  return (wchar_t *)0x26cdf0;
}

/* network_game_generate_local_machine_name (0x12aaf0) — XBE naked draft (batch 144). */
#if defined(__clang__)
static int __stdcall (*const b12aaf0_c1d29eb)(int param_1, void *param_2, int param_3) = FUN_001d29eb;
static wchar_t * (*const b12aaf0_c12b5e0)(void) = network_game_get_random_player_name;
static wchar_t * (*const b12aaf0_c19dc90)(wchar_t *dest, wchar_t *src, size_t count) = ustrncpy;
static int __stdcall (*const b12aaf0_c1d26f3)(void *param_1, int param_2) = XSetNicknameW;
static char * (*const b12aaf0_c19f3a0)(const wchar_t *unicode, char *ascii, int size) = wide_to_ascii;
static void (*const b12aaf0_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;
static void __stdcall (*const b12aaf0_c1d33a2)(int param_1) = FUN_001d33a2;

__attribute__((naked, noinline))
void network_game_generate_local_machine_name(void *name_buffer __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x20, %%esp\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl $0x20\n\t"
      "pushl %%esi\n\t"
      "xorl %%edi, %%edi\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d29eb]\n\t"
      "cmpl $-1, %%eax\n\t"
      "jne .Lnetwork_game_generate_local_machine_name_2\n\t"
      "pushl $0x20\n\t"
      "call *%[c12b5e0]\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[c19dc90]\n\t"
      "addl $0xc, %%esp\n\t"
      "pushl $1\n\t"
      "pushl %%esi\n\t"
      "movw %%di, 0x3e(%%esi)\n\t"
      "call *%[c1d26f3]\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lnetwork_game_generate_local_machine_name_1\n\t"
      "pushl $0x20\n\t"
      "leal -0x20(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[c19f3a0]\n\t"
      "pushl %%eax\n\t"
      "pushl $0x29596c\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $0x18, %%esp\n\t"
      "movw %%di, 0x3e(%%esi)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lnetwork_game_generate_local_machine_name_1:\n\t"
      "pushl $0x29593c\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "movw %%di, 0x3e(%%esi)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lnetwork_game_generate_local_machine_name_2:\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d33a2]\n\t"
      "movw %%di, 0x3e(%%esi)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c1d29eb] "m"(b12aaf0_c1d29eb), [c12b5e0] "m"(b12aaf0_c12b5e0), [c19dc90] "m"(b12aaf0_c19dc90), [c1d26f3] "m"(b12aaf0_c1d26f3), [c19f3a0] "m"(b12aaf0_c19f3a0), [c8f390] "m"(b12aaf0_c8f390), [c1d33a2] "m"(b12aaf0_c1d33a2)
      : "memory");
}
#else
#error "network_game_generate_local_machine_name: clang naked draft required"
#endif


void network_game_log(const char *format, ...)
{
  va_list args;

  if (format == NULL) {
    display_assert("format", "c:\\halo\\SOURCE\\networking\\network_messages.c", 0x14b, 1);
    system_exit(-1);
  }

  va_start(args, format);
  crt_vsnprintf(error_string_buffer, 0xff, format, args);
  va_end(args);

  error(3, error_string_buffer);
}

void xbox_set_machine_name(const char *name)
{
  wchar_t local_44[32];

  if (name != NULL && *name != '\0') {
    /* Success path is the inline fall-through; MSVC places the ascii_to_wide
     * failure branch out of line after the return, so test != NULL and keep
     * the error() call in the else. */
    if (ascii_to_wide(name, local_44, 0x40) != NULL) {
      local_44[31] = 0;
      if (!XSetNicknameW(local_44, 1)) {
        error(2, "XSetNickname() failed");
      }
    }
    else {
      error(2, "'%s' is not a valid machine name (max. name length= %d characters)", (const char *)local_44, 0x1f);
    }
  }
}

int FUN_0012af00(void *p1, void *p2)
{
  char *player1 = (char *)p1;
  char *player2 = (char *)p2;

  if (player1 == NULL || player2 == NULL) {
    display_assert("p1 && p2", "c:\\halo\\SOURCE\\networking\\network_game_manager.c", 0x142, 1);
    system_exit(-1);
  }

  if (!network_player_is_valid(player1) && !network_player_is_valid(player2)) {
    return 0;
  }
  /* qsort comparator: valid players sort ahead of invalid ones. cmp(p1,p2)
   * returns -1 when p1 should precede p2. Reference (0x12af00): valid(p1) with
   * invalid(p2) jumps to the -1 return (683); invalid(p1) with valid(p2) jumps
   * to the +1 return (645). */
  if (network_player_is_valid(player1) && !network_player_is_valid(player2)) {
    return -1;
  }
  if (!network_player_is_valid(player1) && network_player_is_valid(player2)) {
    return 1;
  }

  /* Both are valid, compare machine indices first */
  if (player1[0x1c] > player2[0x1c]) {
    return 1;
  }
  if (player1[0x1c] < player2[0x1c]) {
    return -1;
  }

  /* Machine indices are equal, compare controller/player indices */
  if (player1[0x1d] > player2[0x1d]) {
    return 1;
  }
  if (player1[0x1d] < player2[0x1d]) {
    return -1;
  }

  display_assert("multiple players on the same machine cannot have the same controller index",
                 "c:\\halo\\SOURCE\\networking\\network_game_manager.c", 0x165, 1);
  system_exit(-1);
  return 0;
}

bool network_game_remove_machine(void *game, void *machine)
{
  char *g = (char *)game;
  char *m = (char *)machine;
  char machine_index;
  int i;

  if (g == NULL || m == NULL) {
    display_assert("game && machine", "c:\\halo\\SOURCE\\networking\\network_game_manager.c", 0x97, 1);
    system_exit(-1);
  }

  machine_index = m[0x40];
  if (machine_index >= 0 && machine_index < 4) {
    char *mach_ptr = g + 0x154;
    for (i = 0; i < 4; i++) {
      if (*mach_ptr == machine_index) {
        char *player = g + 0x226;
        int p;
        for (p = 0; p < 16; p++) {
          /* Check if player slot is valid and matches our machine (inlined player_is_valid) */
          if (player != NULL &&
              player[0x1d] >= 0 && player[0x1d] < 4 &&
              player[0x1c] >= 0 && player[0x1c] < 4 &&
              player[0x1c] == machine_index) {
            if (!network_game_remove_player(g, player)) {
              error(2, "failed to remove a machine's player");
            }
          }
          player += 0x20;
        }
        network_game_invalidate_machine(g, (short)machine_index);
        *(short *)(g + 0x112) -= 1;
        return true;
      }
      mach_ptr += 0x44;
    }
  }
  return false;
}

bool network_game_add_machine(void *game, void *machine)
{
  char *g = (char *)game;
  char *m = (char *)machine;
  int i;
  char *mach_ptr;

  if (g == NULL || m == NULL || !network_machine_is_valid(m)) {
    display_assert("game && machine && network_machine_is_valid(machine)",
                   "c:\\halo\\SOURCE\\networking\\network_game_manager.c", 0x6a, 1);
    system_exit(-1);
  }

  for (i = 0; i < 4; i++) {
    if (!network_machine_is_valid(g + 0x114 + i * 0x44)) {
      break;
    }
  }

  if (i >= 4) {
    return false;
  }

  /* Original computes the target slot from the loop index (imul i,0x44 +
   * lea 0x114) rather than a running pointer carried out of the loop. */
  mach_ptr = g + 0x114 + i * 0x44;
  csmemcpy(mach_ptr, m, 0x44);
  *(short *)(g + 0x112) += 1;
  return true;
}

/* network_game_update_machine (0x12a9f0) — readable C lift. */
bool network_game_update_machine(void *game, void *machine)
{
  extern char DAT_002958a8[];
  extern char DAT_00295874[];
  char *g;
  char *m;
  signed char idx;
  int i;
  char *slot;
  g = (char *)game;
  m = (char *)machine;
  if (!g || !m || (signed char)m[0x40] < 0 || (signed char)m[0x40] >= 4) {
    display_assert(DAT_002958a8, DAT_00295874, 0x81, 1);
    system_exit(-1);
  }
  idx = m[0x40];
  slot = g + 0x154;
  for (i = 0; i < 4; i++) {
    if (slot[0] == idx) {
      csmemcpy(g + 0x114 + i * 0x44, m, 0x44);
      return 1;
    }
    slot += 0x44;
  }
  return 0;
}
void network_game_end_and_load_ui(void *game)
{
  char *g = (char *)game;
  if (g[0x430] != '\0') {
    main_load_ui_scenario(true);
  }
  csmemset(g + 0x430, 0, 4);
}

void network_game_reset_for_next_round(void *game, bool flag)
{
  char *g = (char *)game;

  if (g == NULL) {
    display_assert("game", "c:\\halo\\SOURCE\\networking\\network_game_manager.c", 0x22d, 1);
    system_exit(-1);
  }

  if (!flag || g[0x430] == '\0') {
    csmemset(g + 0x430, 0, 4);
  }
  else {
    main_load_ui_scenario(true);
    csmemset(g + 0x430, 0, 4);
    if (network_game_server_get() != NULL) {
      set_game_connection(2);
      game_time_end();
      return;
    }
    if (network_game_client_get() != NULL) {
      set_game_connection(1);
      game_time_end();
      return;
    }
  }
  game_time_end();
}

void network_game_invalidate_machine(void *game, uint16_t machine_index)
{
  char *g = (char *)game;
  int i;
  char *controller_ptr;

  if (g == NULL || machine_index >= 4) {
    display_assert("game && (machine_index<MAXIMUM_NETWORK_MACHINE_COUNT)",
                   "c:\\halo\\SOURCE\\networking\\network_game_manager.c", 0x40, 1);
    system_exit(-1);
  }

  g[0x154 + machine_index * 0x44] = (char)0xff;
  *(short *)(g + 0x114 + machine_index * 0x44) = 0;

  controller_ptr = g + 0x226 + 0x1d;
  for (i = 0; i < 16; i++) {
    if ((uint16_t)(char)controller_ptr[-1] == machine_index) {
      if (controller_ptr - 0x1d == NULL) {
        display_assert("player", "c:\\halo\\SOURCE\\networking\\network_game_manager.c", 0x58, 1);
        system_exit(-1);
      }
      controller_ptr[-1] = (char)0xff;
      controller_ptr[0] = (char)0xff;
      controller_ptr[1] = (char)0xff;
      controller_ptr[2] = (char)0xff;
      *(short *)(controller_ptr - 0x1d) = 0;
    }
    controller_ptr += 0x20;
  }
}

bool network_game_add_player(void *game, void *player)
{
  char *g = (char *)game;
  char *p = (char *)player;
  char machine_index;
  char controller_index;
  int i;
  int empty_slot = -1;

  if (g == NULL || p == NULL) {
    display_assert("game && player", "c:\\halo\\SOURCE\\networking\\network_game_manager.c", 0xbb, 1);
    system_exit(-1);
  }

  if (*(short *)(g + 0x224) < (short)g[0x10e]) {
    machine_index = p[0x1c];
    if (machine_index >= 0 && machine_index < 4) {
      controller_index = p[0x1d];
      if (controller_index >= 0 && controller_index < 4) {
        /* Check for duplicates */
        char *player_slot = g + 0x226;
        for (i = 0; i < 16; i++) {
          if (player_slot[0x1c] == machine_index &&
              player_slot[0x1d] == controller_index) {
            break;
          }
          player_slot += 0x20;
        }

        if (i == 16 && network_player_is_valid(p)) {
          /* Find empty slot (player_index == -1) */
          player_slot = g + 0x226;
          for (i = 0; i < 16; i++) {
            if (player_slot[0x1f] == (char)-1) {
              empty_slot = i;
              break;
            }
            player_slot += 0x20;
          }

          if (empty_slot != -1 &&
              (p[0x1f] == (char)-1 || p[0x1f] == (char)empty_slot)) {
            p[0x1f] = (char)empty_slot;
            csmemcpy(g + 0x226 + empty_slot * 0x20, p, 0x20);
            *(short *)(g + 0x224) += 1;
            return true;
          }
        }
      }
    }
  }
  else {
    error(2, "game is already at maximum players; can't add new player");
  }
  return false;
}

bool network_game_spawn_player(void *player)
{
  char *p = (char *)player;
  bool is_local;
  int16_t controller;
  int player_index;

  if (!network_player_is_valid(p)) {
    display_assert("network_player_is_valid(player)",
                   "c:\\halo\\SOURCE\\networking\\network_game_manager.c", 0x1bc, 1);
    system_exit(-1);
  }

  is_local = network_game_player_is_local(p);
  if (!is_local) {
    controller = -1;
  }
  else {
    controller = (int16_t)p[0x1d];
  }

  player_index = player_new((int)p[0x1c], 0xffffffff, controller, p);
  if (player_index != -1) {
    p[0x1f] = (char)player_index;
    return true;
  }
  return false;
}


void network_game_invalidate(void *game)
{
  char *g = (char *)game;
  int i;

  if (g == NULL) {
    display_assert("game", "c:\\halo\\SOURCE\\networking\\network_game_manager.c", 0x23, 1);
    system_exit(-1);
  }

  csmemset(g, 0, 0x434);
  csmemset(g + 0x20, 0, 0x84);
  *(short *)(g + 0x112) = 0;
  *(short *)(g + 0x224) = 0;

  for (i = 0; i < 4; i++) {
    network_game_invalidate_machine(g, i);
  }

  csmemset(g + 0x226, 0xff, 0x200);
  g[0x10d] = 2;
  g[0x10e] = 16;
  g[0x430] = 0;
}

bool network_game_update_player(void *game, void *player)
{
  char *g = (char *)game;
  char *p = (char *)player;
  int player_index;
  char *player_slot;

  if (g == NULL || p == NULL) {
    display_assert("game && player", "c:\\halo\\SOURCE\\networking\\network_game_manager.c", 0x101, 1);
    system_exit(-1);
  }

  if (network_game_player_is_valid(p, g)) {
    player_index = (int)p[0x1f];
    player_slot = g + 0x226 + player_index * 0x20;
    if (player_slot[0x1d] == p[0x1d] && player_slot[0x1c] == p[0x1c]) {
      csmemcpy(player_slot, p, 0x20);
      return true;
    }
  }

  error(2, "tried to update a player with indvalid data");
  return false;
}

bool network_game_remove_player(void *game, void *player)
{
  char *g = (char *)game;
  char *p = (char *)player;
  int i;
  char *player_slot;

  if (g == NULL || p == NULL) {
    display_assert("game && player", "c:\\halo\\SOURCE\\networking\\network_game_manager.c", 0x120, 1);
    system_exit(-1);
  }

  if (network_game_player_is_valid(p, g)) {
    player_slot = g + 0x226;
    for (i = 0; i < 16; i++) {
      if (player_slot != NULL && player_slot[0x1d] >= 0 && player_slot[0x1d] < 4) {
        if (player_slot[0x1c] >= 0 && player_slot[0x1c] < 4) {
          if (player_slot[0x1c] == p[0x1c] && player_slot[0x1d] == p[0x1d]) {
            network_player_reset((uint8_t *)player_slot);
            *(short *)(g + 0x224) -= 1;
            return true;
          }
        }
      }
      player_slot += 0x20;
    }
    return false;
  }

  error(2, "tried to remove a player with indvalid data");
  return false;
}

bool network_game_create_game_objects(void *game)
{
  char *g = (char *)game;
  int i;
  char *player;
  game_options_t options;
  int16_t conn;

  if (g == NULL) {
    display_assert("game", "c:\\halo\\SOURCE\\networking\\network_game_manager.c", 0x170, 1);
    system_exit(-1);
  }

  /* Initialize game options. 0x12b350 calls game_options_new (the game_options_t
   * constructor), not a plain memset — it seeds non-zero option defaults. */
  game_options_new(&options);
  csstrncpy(options.map_name, g + 0x24, 0x7f);
  options.difficulty = *(int16_t *)(g + 0x110);

  conn = game_connection();
  if (conn > 0) {
    if (conn < 3) {
      options.random_seed = network_game_get_number_of_games_played();
    }
    else if (conn == 3) {
      options.random_seed = *(uint32_t *)(g + 0x428);
    }
    else {
      /* Reference asserts on any connection type > 3 (cmp 3 / jne assert). */
      display_assert("!\"bad game connection\"", "c:\\halo\\SOURCE\\networking\\network_game_manager.c", 0x17f, 1);
      system_exit(-1);
    }
  }
  else {
    display_assert("!\"bad game connection\"", "c:\\halo\\SOURCE\\networking\\network_game_manager.c", 0x17f, 1);
    system_exit(-1);
  }

  game_precache_new_map(options.map_name, 1);
  main_menu_unload();
  if (game_in_progress()) {
    game_dispose_from_old_map();
    game_unload();
  }

  if (*(int *)(g + 0xbc) != 0) {
    game_set_game_variant((game_variant_t *)(g + 0xa4));
  }

  if (!game_load(&options)) {
    error(0, "game_load() failed.");
    return g[0x430] != 0;
  }

  g[0x430] = 1;
  game_initialize_for_new_map();
  qsort(g + 0x226, 16, 32, (int (*)(const void *, const void *))FUN_0012af00);

  player = g + 0x226;
  for (i = 0; i < 16; i++) {
    if (player[0x1d] < 0 || player[0x1d] > 3) break;
    if (player[0x1c] < 0 || player[0x1c] > 3) break;
    if (!network_game_spawn_player(player)) {
      g[0x430] = 0;
      return false;
    }
    player += 0x20;
  }

  return g[0x430] != 0;
}

/* network_game_message_encode (0x12b6b0) — XBE naked draft (batch 95). */
#if defined(__clang__)
static void (*const b12b6b0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b12b6b0_exitfn)(int) = system_exit;
static bool (*const b12b6b0_c11aca0)(group_definition *group, void *data, char *encoded_buf, int32_t *encoded_size, int16_t type, int one) = encode_packet_group;

__attribute__((naked, noinline))
bool network_game_message_encode(void *message_struct __attribute__((unused)), char *encoded_message __attribute__((unused)), int16_t *encoded_message_size __attribute__((unused)), int16_t type __attribute__((unused)), int one __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "testl %%edi, %%edi\n\t"
      "je .Lnetwork_game_message_encode_1\n\t"
      "testl %%ebx, %%ebx\n\t"
      "je .Lnetwork_game_message_encode_1\n\t"
      "testl %%esi, %%esi\n\t"
      "je .Lnetwork_game_message_encode_1\n\t"
      "cmpw $0, (%%esi)\n\t"
      "jg .Lnetwork_game_message_encode_2\n\t"
      ".Lnetwork_game_message_encode_1:\n\t"
      "pushl $1\n\t"
      "pushl $0x161\n\t"
      "pushl $0x296108\n\t"
      "pushl $0x296138\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lnetwork_game_message_encode_2:\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "pushl $0x323510\n\t"
      "call *%[c11aca0]\n\t"
      "addl $0x18, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b12b6b0_assert), [exitfn] "m"(b12b6b0_exitfn), [c11aca0] "m"(b12b6b0_c11aca0)
      : "memory");
}
#else
#error "network_game_message_encode: clang naked draft required"
#endif

/* --- network_game_manager.obj batch drafts (2026-07-26) --- */

/* network_game_player_is_valid (0x12b0c0) — readable C lift from XBE leaf. */
bool network_game_player_is_valid(void *player, void *game)
{
  extern char DAT_00295a5c[];
  extern char DAT_00295874[];
  signed char team;
  signed char index;
  int i;
  unsigned char *slot;

  if (player == 0 || game == 0) {
    display_assert(DAT_00295a5c, DAT_00295874, 0x247, true);
    system_exit(-1);
  }
  if (player == 0)
    return 0;
  index = *(signed char *)((char *)player + 0x1d);
  if (index < 0 || index >= 4)
    return 0;
  team = *(signed char *)((char *)player + 0x1c);
  if (team < 0 || team >= 4)
    return 0;
  slot = (unsigned char *)game + 0x243;
  for (i = 0; i < 0x10; i++) {
    if (slot[-1] == (unsigned char)team && slot[0] == (unsigned char)index)
      return 1;
    slot += 0x20;
  }
  return 0;
}


