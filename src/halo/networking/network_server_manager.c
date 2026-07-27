/* Decode a network game message from an encoded buffer.
 * Returns true on success; logs an error on failure.
 * 0x12bce0 / network_server_manager.obj */
bool FUN_0012bce0(int param_1, int param_2, short *param_3, short *param_4,
                  short *param_5, int param_6)
{
  bool cVar1;

  if ((((param_1 == 0 || param_2 == 0) || param_3 == (short *)0) ||
       (*param_3 < 1 || param_4 == (short *)0)) ||
      (*param_4 < 0 || (param_5 == (short *)0 || *param_5 < 1))) {
    display_assert(
      "message_struct && encoded_message && encoded_message_size && "
      "(*encoded_message_size>0) && packet_type && (*packet_type>=0) && "
      "packet_version && (*packet_version>0)",
      "c:\\halo\\SOURCE\\networking\\network_messages.c", 0x139, 1);
    system_exit(-1);
  }
  cVar1 = FUN_0011aa40((int)0x323510, (void *)param_1, (char *)param_2,
                       param_3, param_4, param_5, (short)param_6);
  if (!cVar1) {
    network_game_log("decode_network_game_message() failed");
  }
  return cVar1;
}

/* Update a countdown timer without reading its value.
 * countdown[0] = time_remaining, countdown[1] = last_tick_time.
 * 0x12bd80 / network_server_manager.obj */
void countdown_timer_update(int *param_1)
{
  int now;
  int old;
  int elapsed;

  now = system_milliseconds();
  old = param_1[1];
  param_1[1] = now;
  if (now > old) {
    elapsed = now - old;
    if (elapsed < param_1[0]) {
      param_1[0] -= elapsed;
    } else {
      param_1[0] = 0;
    }
  }
}

/* Tick a millisecond countdown timer. Subtracts elapsed time from
   time_remaining, clamps to zero, and returns the remaining value.
   countdown[0] = time_remaining, countdown[1] = last_tick_time. */
__declspec(noinline) int countdown_timer_get_time_remaining(void *countdown)
{
  int now;
  int elapsed;
  int remaining;
  int *timer = (int *)countdown;

  now = system_milliseconds();
  if (now > timer[1]) {
    elapsed = now - timer[1];
    if (elapsed < timer[0]) {
      timer[0] = timer[0] - elapsed;
    } else {
      timer[0] = 0;
    }
  }
  remaining = timer[0];
  timer[1] = now;
  assert_halt(remaining >= 0);
  return remaining;
}

/* countdown_timer_increment — 0x12be10
 * Ticks the timer forward, then adds param_2 ms clamped to [0, param_3]. */
void countdown_timer_increment(int *param_1, int param_2, int param_3)
{
  int iVar1;
  int iVar2;
  iVar1 = system_milliseconds();
  if (iVar1 > param_1[1]) {
    iVar2 = iVar1 - param_1[1];
    if (iVar2 < *param_1) {
      *param_1 = *param_1 - iVar2;
    } else {
      *param_1 = 0;
    }
  }
  param_1[1] = iVar1;
  if (param_2 < 0) {
    display_assert("adjustment >= 0",
                   "c:\\halo\\SOURCE\\networking\\network_server_manager.c",
                   0x68, 1);
    system_exit(-1);
  }
  iVar1 = *param_1 + param_2;
  if (iVar1 < param_2) {
    *param_1 = param_3;
  } else {
    *param_1 = iVar1;
    if (param_3 < iVar1) {
      iVar1 = param_3;
    }
    *param_1 = iVar1;
  }
  if (*param_1 < 0) {
    display_assert("timer->time_remaining >= 0",
                   "c:\\halo\\SOURCE\\networking\\network_server_manager.c",
                   0x75, 1);
    system_exit(-1);
  }
}

/* countdown_timer_decrement — 0x12bea0
 * Ticks the timer forward, then subtracts param_2 ms (floor at 0). */
void countdown_timer_decrement(int *param_1, int param_2)
{
  int iVar1;
  int iVar2;
  iVar1 = system_milliseconds();
  if (iVar1 > param_1[1]) {
    iVar2 = iVar1 - param_1[1];
    if (iVar2 < *param_1) {
      *param_1 = *param_1 - iVar2;
    } else {
      *param_1 = 0;
    }
  }
  param_1[1] = iVar1;
  if (param_2 < 0) {
    display_assert("adjustment >= 0",
                   "c:\\halo\\SOURCE\\networking\\network_server_manager.c",
                   0x7e, 1);
    system_exit(-1);
  }
  if (param_2 < *param_1) {
    param_2 = *param_1 - param_2;
    *param_1 = param_2;
    if (param_2 < 0) {
      display_assert("timer->time_remaining >= 0",
                     "c:\\halo\\SOURCE\\networking\\network_server_manager.c",
                     0x89, 1);
      system_exit(-1);
    }
    return;
  }
  *param_1 = 0;
}

/* countdown_timer_set_time_remaining — 0x12bf30
 * Resets the timer to param_2 ms and records the current tick time. */
void countdown_timer_set_time_remaining(int *param_1, int param_2)
{
  int iVar1;
  iVar1 = system_milliseconds();
  *param_1 = param_2;
  param_1[1] = iVar1;
  if (param_2 < 0) {
    display_assert("timer->time_remaining >= 0",
                   "c:\\halo\\SOURCE\\networking\\network_server_manager.c",
                   0x95, 1);
    system_exit(-1);
  }
}

/* network_game_server_set_game_name — 0x12bf70
 * Copies up to 15 wchars from param_2 into server->game_name (server+8),
 * then zeros the trailing terminator at server+0x26. Returns '\0'. */
char network_game_server_set_game_name(int param_1, int param_2)
{
  if (param_1 == 0) {
    display_assert("server",
                   "c:\\halo\\SOURCE\\networking\\network_server_manager.c",
                   0x1dd, 1);
    system_exit(-1);
  }
  if (param_2 == 0) {
    display_assert("name",
                   "c:\\halo\\SOURCE\\networking\\network_server_manager.c",
                   0x1de, 1);
    system_exit(-1);
  }
  ustrncpy((wchar_t *)(param_1 + 8), (wchar_t *)param_2, 0xf);
  *(short *)(param_1 + 0x26) = 0;
  return '\0';
}

/* network_game_server_get_game_name — 0x12bfe0
 * Returns a pointer to the server's game name buffer (wchar_t at server+8). */
int network_game_server_get_game_name(int param_1)
{
  if (param_1 == 0) {
    display_assert("server",
                   "c:\\halo\\SOURCE\\networking\\network_server_manager.c",
                   0x1e9, 1);
    system_exit(-1);
  }
  return param_1 + 8;
}

/* network_game_server_get_state — 0x12c020
 * Returns server->state (short at server+4). If param_2 is non-NULL,
 * zeroes *param_2 before returning. */
short network_game_server_get_state(int param_1, short *param_2)
{
  if (param_1 == 0) {
    display_assert("server",
                   "c:\\halo\\SOURCE\\networking\\network_server_manager.c",
                   0x1f2, 1);
    system_exit(-1);
  }
  if (param_2 != NULL) {
    *param_2 = 0;
  }
  return *(short *)(param_1 + 4);
}

/* Open the server's game (0x12c060).
 * Sets bit 0 of the flags byte at server+6 (marking the game as open),
 * then tells the underlying connection to open, and logs "opening game". */
void network_game_server_open_game(void *server)
{
  if (!server) {
    display_assert("server",
                   "c:\\halo\\SOURCE\\networking\\network_server_manager.c",
                   0x1fc, 1);
    system_exit(-1);
  }
  *(uint8_t *)((char *)server + 6) |= 1;
  network_server_allow_client_connections(*(int *)server, 1);
  network_game_log("opening game");
}

/* Close the server's game (0x12c0b0).
 * Clears bit 0 of the flags byte at server+6 (marking the game as closed),
 * then tells the underlying connection to close, and logs "closing game". */
__declspec(noinline) void network_game_server_close_game(void *server)
{
  if (!server) {
    display_assert("server",
                   "c:\\halo\\SOURCE\\networking\\network_server_manager.c",
                   0x208, 1);
    system_exit(-1);
  }
  *(uint8_t *)((char *)server + 6) &= ~1;
  network_server_allow_client_connections(*(int *)server, 0);
  network_game_log("closing game");
}

/* network_game_server_game_is_open (0x12c100) — readable C lift. */
bool network_game_server_game_is_open(void *server)
{
  extern char DAT_00296c34[];
  extern char DAT_00296bf0[];
  extern char DAT_00296c5c[];
  unsigned char bl;
  if (!server) {
    display_assert(DAT_00296c34, DAT_00296bf0, 0x214, 1);
    system_exit(-1);
  }
  bl = *(unsigned char *)((char *)server + 6) & 1;
  if (!bl && bl) {
    display_assert(DAT_00296c5c, DAT_00296bf0, 0x217, 1);
    system_exit(-1);
  }
  return bl;
}

/* network_game_server_game_is_valid (0x12c160) — readable C lift. */
bool network_game_server_game_is_valid(void *server)
{
  extern char DAT_00296c34[];
  extern char DAT_00296bf0[];
  extern char DAT_00296c90[];
  unsigned char bl;
  if (!server) {
    display_assert(DAT_00296c34, DAT_00296bf0, 0x220, 1);
    system_exit(-1);
  }
  bl = (*(unsigned char *)((char *)server + 6) >> 1) & 1;
  if (!bl && bl) {
    display_assert(DAT_00296c90, DAT_00296bf0, 0x223, 1);
    system_exit(-1);
  }
  return bl;
}

/* Handle a client player-removal request while in-game (0x12c1c0).
 * Asserts the server is in state 1 (in-game). Iterates the 16 client
 * entries at server+0x22e (stride 0x20). For each active client whose
 * machine_index byte (+0x1c) matches the machine slot's index (+0xc),
 * copies 0x20 bytes of client data, appends a quit time, and broadcasts
 * a type-0x16 message to all machines. */
void FUN_0012c1c0(int server, int client)
{
  char *s = (char *)server;
  char *ptr;
  char local_buf[0x24];
  int quit_time;
  void *msg;
  int i;

  if (*(short *)(s + 4) != 1) {
    display_assert("_network_game_server_state_ingame == server->state",
                   "c:\\halo\\SOURCE\\networking\\network_server_manager.c",
                   0x267, 1);
    system_exit(-1);
  }

  ptr = s + 0x22e;
  for (i = 0x10; i != 0; i--) {
    if (network_player_is_valid(ptr)) {
      if ((short)*(signed char *)(ptr + 0x1c) ==
          *(short *)((char *)client + 0xc)) {
        csmemcpy(local_buf, ptr, 0x20);
        quit_time = game_time_get() + 0x21;
        *(int *)(local_buf + 0x20) = quit_time;
        error(2, "sending quit out of game, time = %x", quit_time);
        msg = encode_network_game_message(0x16, local_buf, 0x24);
        if (msg) {
          if (!FUN_0012f430((void *)server, msg)) {
            network_game_log(
              "network_game_server_send_message_to_all_machines() failed in "
              "network_game_server_handle_message_client_remove_player_"
              "request_ingame()");
          }
        }
      }
    }
    ptr += 0x20;
  }
}

/* Signal client machines to begin loading for a network game (0x12c290).
 * Copies server game-variant data at server+8 (0x434 bytes) into a local
 * buffer, builds a type-6 message from it and broadcasts it, then builds
 * a type-8 message with a zero payload and broadcasts that too.  On
 * success sets server+0x4b9 (loading flag) to 1.  Always clears
 * server+0x47c and always returns true regardless of success or failure. */
__declspec(noinline) bool FUN_0012c290(void *server)
{
  int data;
  void *msg;
  char local_buf[0x434];

  if (!server) {
    display_assert("server",
                   "c:\\halo\\SOURCE\\networking\\network_server_manager.c",
                   0x2de, 1);
    system_exit(-1);
  }
  if (*(char *)((char *)server + 0x4b9) == 0) {
    data = 0;
    csmemcpy(local_buf, (char *)server + 8, 0x434);
    msg = encode_network_game_message(6, local_buf, 0x434);
    if (msg && FUN_0012f430(server, msg)) {
      msg = encode_network_game_message(8, &data, 4);
      if (msg && FUN_0012f430(server, msg)) {
        network_game_log(
          "signalling client machines to begin loading for network game");
        *(int *)((char *)server + 0x47c) = 0;
        *(char *)((char *)server + 0x4b9) = 1;
        return true;
      }
    }
    network_game_log(
      "failed to signal client machines to begin loading for network game");
  }
  *(int *)((char *)server + 0x47c) = 0;
  return true;
}

/* Xbox kernel sleep wrapper (stdcall, 2 args) */
typedef void(__stdcall *sleep_fn)(int milliseconds, int alertable);
#define XSleep ((sleep_fn)0x1d01c4)

/* Signal game over to all clients (0x12c370).
 * Sets server state from in-game (1) to post-game (2) and broadcasts
 * a _message_type_server_game_over message. */
void network_server_manager_game_over(void *server)
{
  int data;
  void *msg;

  if (!server) {
    display_assert("server",
                   "c:\\halo\\SOURCE\\networking\\network_server_manager.c",
                   0x2ff, 1);
    system_exit(-1);
  }
  if (*(int16_t *)((char *)server + 4) == 1) {
    data = 0;
    *(int16_t *)((char *)server + 4) = 2;
    msg = encode_network_game_message(0x17, &data, 4);
    if (msg) {
      if (FUN_0012f430(server, msg)) {
        network_game_log("server sent message_game_over to all clients");
        return;
      }
      network_game_log(
        "failed to signal all client machines to switch to postgame");
      return;
    }
    network_game_log(
      "failed to create a _message_type_server_game_over message");
  }
}

/* Send a graceful-shutdown message to all clients based on server state
 * (0x12c410). State 0 = pregame: sends message type 9; state 2 = postgame:
 * sends type 0x1f. Other states return false immediately. */
bool network_game_server_graceful_shutdown(void *server)
{
  char *s;
  int data;
  void *msg;
  bool result;
  unsigned short state;

  if (!server) {
    display_assert("server",
                   "c:\\halo\\SOURCE\\networking\\network_server_manager.c",
                   0x39f, 1);
    system_exit(-1);
    display_assert("server",
                   "c:\\halo\\SOURCE\\networking\\network_server_manager.c",
                   0x1f2, 1);
    system_exit(-1);
  }
  s = (char *)server;
  state = (unsigned short)*(short *)(s + 4);
  data = 0;
  switch (state) {
  case 0:
    msg = encode_network_game_message(9, &data, 4);
    if (!msg) {
      network_game_log(
        "failed to create a message_server_graceful_game_exit_pregame");
      return false;
    }
    break;
  case 2:
    msg = encode_network_game_message(0x1f, &data, 4);
    if (!msg) {
      network_game_log(
        "failed to create a message_server_graceful_game_exit_postgame");
      return false;
    }
    break;
  default:
    return false;
  }
  result = FUN_0012f430(server, msg);
  if (result) {
    network_game_log(
      "server closing down; all client machines were properly informed");
    return result;
  }
  network_game_log(
    "server going down, but failed to properly inform all client machines");
  return result;
}

/* Check if a machine is marked as valid/active on this server (0x12c500).
 * Asserts both server and machine are non-null, then returns bit 1 of the
 * flags byte at machine+0xe (shifted right by 1, masked to a bool). */
bool network_game_server_client_machine_is_joined_to_game(int server,
                                                          int machine)
{
  if (!server) {
    display_assert("server",
                   "c:\\halo\\SOURCE\\networking\\network_server_manager.c",
                   0x3cd, 1);
    system_exit(-1);
  }
  if (!machine) {
    display_assert("machine",
                   "c:\\halo\\SOURCE\\networking\\network_server_manager.c",
                   0x3ce, 1);
    system_exit(-1);
  }
  return (*(uint8_t *)((char *)machine + 0xe) >> 1) & 1;
}

/* Accept a client machine into the game and assign it to the next open slot
 * (0x12c560). */
char network_game_server_accept_client_machine_into_game(int server,
                                                         void *machine)
{
  char buf[0x44];
  int i;
  char *slot;
  char result;
  int addr_buf[6];

  result = 0;
  if (!server) {
    display_assert("server",
                   "c:\\halo\\SOURCE\\networking\\network_server_manager.c",
                   0x3da, 1);
    system_exit(-1);
  }
  if (!machine) {
    display_assert("machine",
                   "c:\\halo\\SOURCE\\networking\\network_server_manager.c",
                   0x3db, 1);
    system_exit(-1);
  }
  i = 0;
  slot = (char *)server + 0x15c;
  while (1) {
    if (*slot < 0 || *slot > 3)
      break;
    i++;
    slot += 0x44;
    if (i > 3) {
      if (i == 4)
        network_game_log(
          "network_game_server_accept_client_machine_into_game() failed to "
          "find an available opening for the new machine");
      return result;
    }
  }
  csmemcpy(buf, (char *)server + 0x11c + i * 0x44, 0x44);
  buf[0x40] = (char)i;
  result = network_game_add_machine((void *)(server + 8), (void *)buf);
  if (result == 1) {
    csmemset(addr_buf, 0, sizeof(addr_buf));
    network_connection_get_address(*(int *)machine, addr_buf, 0);
    network_game_log("server added machine @ %s to the game at machine index "
                     "#%d",
                     transport_address_to_string((void *)addr_buf), i);
    *(char *)((char *)machine + 0xe) = *(char *)((char *)machine + 0xe) | 2;
    *(short *)((char *)machine + 0xc) = (short)i;
  } else {
    network_game_log("network_game_add_machine() failed in "
                     "network_game_server_accept_client_machine_into_game()");
  }
  if (i == 4)
    network_game_log(
      "network_game_server_accept_client_machine_into_game() failed to find "
      "an available opening for the new machine");
  return result;
}

/* Check if a player name/identity already exists in the server's player list
 * (0x12c690). Iterates 0x10 player slots at server+0x22e with stride 0x20.
 * Returns false if a matching player is found, true if unique. */
bool FUN_0012c690(int server, int player)
{
  int i;
  char *slot;
  i = 0;
  slot = (char *)server + 0x22e;
  do {
    if (network_player_is_valid((void *)slot)) {
      if (!ustrcmp((const wchar_t *)slot, (const wchar_t *)player))
        return false;
    }
    i++;
    slot += 0x20;
  } while (i < 0x10);
  return true;
}

/* FUN_0012c6d0 — 0x12c6d0
 * Pick a random player name that is not already used by any active player.
 * Iterates up to 0x10 player slots at param_1+0x22e (0x20 bytes each).
 * Retries FUN_0012b5e0 until the returned name does not match any active
 * player's name via ustrcmp. Copies the chosen name to param_2 (0xb wide
 * chars) and writes a null short at param_2+0x16. */
void FUN_0012c6d0(int param_1, int param_2)
{
  wchar_t *name;
  int match_count;
  char *player_slot;
  int slot_count;

  do {
    name = network_game_get_random_player_name();
    player_slot = (char *)param_1 + 0x22e;
    match_count = 0;
    slot_count = 0x10;
    do {
      if (network_player_is_valid((void *)player_slot)) {
        if (ustrcmp((wchar_t *)player_slot, name) == 0) {
          match_count++;
        }
      }
      player_slot += 0x20;
      slot_count--;
    } while (slot_count != 0);
  } while (match_count != 0);

  ustrncpy((wchar_t *)param_2, name, 0xb);
  *(short *)((char *)param_2 + 0x16) = 0;
}

/* FUN_0012c750 — 0x12c750
 * Pick a random team index not already occupied by any active player.
 * For the first 10 retries uses FUN_001c19a0, then FUN_001c19c0.
 * Player slots start at param_1+0x246 (0x20 bytes each, 0x10 slots).
 * network_player_is_valid is called with slot-0x18 (slot base pointer).
 * The team value is a short at slot[0] (= player_base+0x18).
 * Stores the chosen team as a short at param_2+0x18. */
void FUN_0012c750(int param_1, int param_2)
{
  int random_team;
  char unique;
  char *player_slot;
  int retry_count;
  int i;

  retry_count = 0;
  do {
    if (retry_count < 0xa) {
      random_team = FUN_001c19a0();
    } else {
      random_team = FUN_001c19c0();
    }
    unique = 1;
    i = 0;
    player_slot = (char *)param_1 + 0x246;
    do {
      if (network_player_is_valid((void *)(player_slot - 0x18))) {
        if (*(short *)player_slot == (short)random_team) {
          unique = 0;
          break;
        }
      }
      i++;
      player_slot += 0x20;
    } while (i < 0x10);
    retry_count++;
    if (unique) {
      *(short *)((char *)param_2 + 0x18) = (short)random_team;
      return;
    }
  } while (1);
}

/* Add a player to the game after machine/identity validation (0x12c7e0). */
char network_game_server_add_player_to_game(int server, int machine,
                                            void *player)
{
  char *p = (char *)player;
  char result;

  if (!server) {
    display_assert("server",
                   "c:\\halo\\SOURCE\\networking\\network_server_manager.c",
                   0x46c, 1);
    system_exit(-1);
  }
  if (!machine) {
    display_assert("machine",
                   "c:\\halo\\SOURCE\\networking\\network_server_manager.c",
                   0x46d, 1);
    system_exit(-1);
  }
  if (!player) {
    display_assert("player",
                   "c:\\halo\\SOURCE\\networking\\network_server_manager.c",
                   0x46e, 1);
    system_exit(-1);
  }
  if (*(short *)(machine + 0xc) == (short)p[0x1c]) {
    *(char *)(p + 0x1e) = (char)*(int *)0x46eed8;
    *(int *)0x46eed8 = (*(int *)0x46eed8 + 1) & 0x80000001;
    if ((int)*(int *)0x46eed8 < 0) {
      *(int *)0x46eed8 = (*(int *)0x46eed8 - 1 | 0xfffffffe) + 1;
    }
    if (*(short *)p == 0) {
      FUN_0012c6d0(server, (int)player);
    }
    if (!FUN_0012c690(server, (int)player)) {
      FUN_0012c6d0(server, (int)player);
    }
    if (*(short *)(p + 0x18) == -1) {
      FUN_0012c750(server, (int)player);
    }
    result = network_game_add_player((void *)(server + 8), (void *)player);
    if (result == 1) {
      network_game_log("server added player from machine #%d at controller "
                       "index #%d to the game",
                       (int)(short)*(short *)(machine + 0xc),
                       (int)*(char *)(p + 0x1d));
      return result;
    }
    network_game_log("network_game_add_player() failed in "
                     "network_game_server_add_player_to_game()");
    return result;
  }
  network_game_log("client machine tried to add a player with a non-matching "
                   "machine identifier");
  return 0;
}

/* network_game_server_remove_player_from_game — 0x12c920
 * Removes a player from the game if machine IDs match. Asserts server,
 * machine, and player are all non-null. Returns 1 on success. */
char network_game_server_remove_player_from_game(int param_1, int param_2,
                                                 int param_3)
{
  char cVar1;

  if (param_1 == 0) {
    display_assert("server",
                   "c:\\halo\\SOURCE\\networking\\network_server_manager.c",
                   0x4a0, 1);
    system_exit(-1);
  }
  if (param_2 == 0) {
    display_assert("machine",
                   "c:\\halo\\SOURCE\\networking\\network_server_manager.c",
                   0x4a1, 1);
    system_exit(-1);
  }
  if (param_3 == 0) {
    display_assert("player",
                   "c:\\halo\\SOURCE\\networking\\network_server_manager.c",
                   0x4a2, 1);
    system_exit(-1);
  }
  if (*(short *)(param_2 + 0xc) == (short)*(char *)(param_3 + 0x1c)) {
    cVar1 = network_game_remove_player((void *)(param_1 + 8), (void *)param_3);
    if (cVar1 == '\x01') {
      network_game_log("server removed player from machine #%d at controller "
                       "index #%d from the game",
                       (int)*(char *)(param_3 + 0x1c),
                       (int)*(char *)(param_3 + 0x1d));
      return '\x01';
    }
    network_game_log("network_game_remove_player() failed in "
                     "network_game_server_remove_player_from_game()");
    return cVar1;
  }
  network_game_log("client machine tried to remove a player with a "
                   "non-matching machine identifier");
  return '\0';
}

/* FUN_0012ca00 — 0x12ca00
 * Validates and updates machine description if the machine's ID matches.
 * Asserts server, machine, and machine_description non-null. Returns 1
 * on success, or the error code from network_game_update_machine. */
char FUN_0012ca00(int param_1, int param_2, int param_3)
{
  char cVar1;

  if (((param_1 == 0) || (param_2 == 0)) || (param_3 == 0)) {
    display_assert("server && machine && machine_description",
                   "c:\\halo\\SOURCE\\networking\\network_server_manager.c",
                   0x4bf, 1);
    system_exit(-1);
  }
  if (*(short *)(param_2 + 0xc) == (short)*(char *)(param_3 + 0x40)) {
    cVar1 = network_game_update_machine((void *)(param_1 + 8), (void *)param_3);
    if (cVar1 == '\x01') {
      network_game_log("server updated machine #%d settings",
                       (int)*(char *)(param_3 + 0x40));
      return '\x01';
    }
    network_game_log("network_game_update_machine() failed in "
                     "network_game_server_adjust_machine_settings()");
    return cVar1;
  }
  network_game_log("client machine tried to update itself with a non-matching "
                   "machine identifier");
  return '\0';
}

/* Finalize server loading after all machines have loaded (0x12caa0).
 * Sets the server state to 1, clears the timer at +0x484, then copies a
 * "local game data loaded" flag from the client's game-data region into
 * server+0x438.  Asserts if the flag is zero (data not loaded). */
__declspec(noinline) void network_game_server_all_machines_have_loaded(void *server)
{
  char *s = (char *)server;
  void *client;
  void *game_data;
  uint8_t loaded;

  network_game_log("all machines have successfully loaded");
  *(int16_t *)(s + 0x4) = 1;
  *(int32_t *)(s + 0x484) = 0;

  client = network_game_client_get();
  if (client != NULL) {
    game_data =
      network_game_client_get_machine_index(network_game_client_get());
    loaded = *(uint8_t *)((char *)game_data + 0x430);
  } else {
    loaded = 0;
  }

  *(uint8_t *)(s + 0x438) = loaded;
  if (!loaded) {
    display_assert("local game data not loaded",
                   "c:\\halo\\SOURCE\\networking\\network_server_manager.c",
                   0x4e0, 1);
    system_exit(-1);
  }
}

/* Mark machine as loading-complete and check if all machines are loaded.
 * 0x12cb20 / network_server_manager.obj
 */
void network_game_server_client_machine_game_loading_completed(void *server,
                                                               void *machine)
{
  short sVar1;
  bool bVar2;
  short *psVar4;
  int iVar5;

  bVar2 = 1;
  if (!server) {
    display_assert(0, 0, 0x4ed, 1);
    system_exit(-1);
  }
  if (!machine) {
    display_assert(0, 0, 0x4ee, 1);
    system_exit(-1);
  }
  *(unsigned char *)((char *)machine + 0xe) |= 4;
  psVar4 = (short *)((char *)server + 0x448);
  iVar5 = 4;
  do {
    sVar1 = *psVar4;
    if (sVar1 >= 0 && sVar1 < 4 &&
        !(*(unsigned char *)((char *)psVar4 + 2) & 4)) {
      network_game_log("still waiting on machine #%d to finish loading",
                       (int)sVar1);
      bVar2 = 0;
    }
    psVar4 = (short *)((char *)psVar4 + 0x10);
    iVar5--;
  } while (iVar5 != 0);
  if (bVar2) {
    network_game_server_all_machines_have_loaded(server);
  }
  if (*(int *)((char *)server + 0x484) == 0) {
    *(unsigned int *)((char *)server + 0x484) = system_milliseconds();
  }
}

/* network_game_server_client_machine_is_precached — 0x12cbe0 */
void network_game_server_client_machine_is_precached(int param_1, int param_2,
                                                     int param_3)
{
  char *map_name;
  int iVar2;
  map_name = main_get_multiplayer_map_name();
  iVar2 = csstrcmp(map_name, (const char *)param_3);
  if (iVar2 == 0) {
    *(unsigned char *)(param_2 + 0xe) = *(unsigned char *)(param_2 + 0xe) | 8;
  }
}

/* Handle a client update packet (tick sync, player data) from a machine
 * (0x12cc10). */
void network_game_server_handle_client_update_packet(int server, int machine,
                                                     void *message)
{
  short player_count;
  unsigned int tick;
  unsigned int machine_last_tick;
  unsigned int *input_buf[32];
  int i;
  unsigned int *src;
  unsigned int *dst = 0;

  if (!server) {
    display_assert("server",
                   "c:\\halo\\SOURCE\\networking\\network_server_manager.c",
                   0x51e, 1);
    system_exit(-1);
  }
  if (!machine) {
    display_assert("machine",
                   "c:\\halo\\SOURCE\\networking\\network_server_manager.c",
                   0x51f, 1);
    system_exit(-1);
  }
  if (!message) {
    display_assert("message_packet",
                   "c:\\halo\\SOURCE\\networking\\network_server_manager.c",
                   0x520, 1);
    system_exit(-1);
  }
  if (*(int *)message < 0) {
    network_game_log(
      "client machine #%d is out of sync @ game tick #%ld; switching to "
      "post-game",
      (int)*(short *)((char *)machine + 0xc), (int)game_time_get());
    game_engine_switch_to_postgame();
    return;
  }
  tick = *(unsigned int *)message & 0x7fffffff;
  machine_last_tick = *(unsigned int *)((char *)machine + 4);
  if (tick < machine_last_tick) {
    network_game_log("received an outdated client update packet; ignoring "
                     "(#%d / #%d)",
                     tick, machine_last_tick);
    return;
  }
  player_count = *(short *)((char *)message + 6);
  if (player_count >= 0 && player_count < 5) {
    csmemset(input_buf, 0, sizeof(input_buf));
    if (player_count > 0) {
      src = (unsigned int *)((char *)message + 8);
      dst = (unsigned int *)input_buf;
      for (i = (int)player_count << 3; i != 0; i--) {
        *dst = *src;
        src++;
        dst++;
      }
    }
    update_server_apply_actions(*(short *)((char *)machine + 0xc),
                                (void *)input_buf);
    *(unsigned int *)((char *)machine + 4) =
      *(unsigned int *)message & 0x7fffffff;
  } else {
    network_game_log(
      "client update packet from machine #%d had a bad player count; ignoring",
      (int)*(short *)((char *)machine + 0xc));
  }
}

/* network_game_server_switch_machine_from_postgame_to_pregame — 0x12cd60 */
int network_game_server_switch_machine_from_postgame_to_pregame(int param_1,
                                                                int param_2)
{
  if ((param_1 == 0) || (param_2 == 0)) {
    display_assert("server && machine",
                   "c:\\halo\\SOURCE\\networking\\network_server_manager.c",
                   0x547, 1);
    system_exit(-1);
  }
  network_game_log("machine #%d has successfully switched to pregame",
                   (int)*(short *)(param_2 + 0xc));
  *(unsigned char *)(param_2 + 0xe) = *(unsigned char *)(param_2 + 0xe) & 0xfb;
  return 1;
}

/* Main server tick function (0x12cdb0).
 * Sends game state updates, handles pending player additions.
 * tick_count implicitly forwarded from esi context. */
void network_game_server_update_ticks(int server, unsigned short tick_count)
{
  char input_buf[516]; /* [count:2][pad:2][data:512] contiguous */
  char upkt[0x210];
  int tick_out;
  int upkt_random;
  int upkt_time;
  int i;
  unsigned int j;
  short machine_idx;
  char *s;
  char *slot;
  void *msg;
  char result;

  s = (char *)server;
  if (!server) {
    display_assert("server",
                   "c:\\halo\\SOURCE\\networking\\network_server_manager.c",
                   0x553, 1);
    system_exit(-1);
  }
  if (*(short *)(s + 4) == 1) {
    j = (unsigned int)tick_count;
    while (j != 0) {
      tick_out = *(int *)(s + 0x47c);
      *(int *)(s + 0x47c) = tick_out + 1;
      update_server_create_snapshot();
      update_server_get_update(-1, (void *)input_buf, &tick_out);
      upkt_random = get_random_seed();
      upkt_time = game_time_get();
      *(int *)(upkt + 0) = tick_out;
      *(int *)(upkt + 4) = upkt_random;
      *(int *)(upkt + 8) = upkt_time;
      *(unsigned short *)(upkt + 0xe) = *(unsigned short *)input_buf;
      csmemcpy(upkt + 0x10, input_buf + 4,
               (unsigned int)*(unsigned short *)input_buf << 5);
      msg = encode_network_game_message(0x14, upkt, 0x210);
      if (msg && !FUN_0012f430((void *)server, msg))
        network_game_log(
          "server failed to send game update message to all machines; client "
          "machine may be out of sync");
      j--;
    }
    if (*(char *)(s + 0x4b8)) {
      i = 0;
      slot = s + 0x448;
      do {
        machine_idx = *(short *)(s + 0x4b4);
        if (*(short *)slot == machine_idx) {
          int conn = i * 0x10 + 0x43c + server;
          if (conn) {
            result = network_game_server_add_player_to_game(
              server, conn, (void *)(s + 0x498));
            if (result) {
              result = FUN_0012f540(server, (void *)(s + 0x498));
              if (!result)
                network_game_log(
                  "network_game_server_send_player_joined_info_ingame() "
                  "failed in network_game_server_handle_message_client_"
                  "add_player_request_ingame()");
              goto done_add;
            }
          }
          break;
        }
        i++;
        slot += 0x10;
      } while (i < 4);
      network_game_log("server failed to add a network player in-game");
    done_add:
      *(char *)(s + 0x4b8) = 0;
    }
  } else if (*(short *)(s + 4) == 2) {
    game_engine_update();
  }
}

/* network_game_server_queue_player_for_addition — 0x12cf60 */
void network_game_server_queue_player_for_addition(int param_1, int param_2)
{
  char cVar1;
  if ((param_1 == 0) || (param_2 == 0)) {
    display_assert("server && player",
                   "c:\\halo\\SOURCE\\networking\\network_server_manager.c",
                   0x5de, 1);
    system_exit(-1);
  }
  if (*(char *)(param_1 + 0x4b8) == '\0') {
    cVar1 = network_player_is_valid((void *)param_2);
    if (cVar1 != '\0') {
      csmemcpy((void *)(param_1 + 0x498), (void *)param_2, 0x20);
      *(unsigned char *)(param_1 + 0x4b8) = 1;
    }
  }
}

/* network_game_server_begin_game_start_countdown — 0x12cfd0 */
void network_game_server_begin_game_start_countdown(int param_1, int param_2)
{
  if (param_1 == 0) {
    display_assert("server",
                   "c:\\halo\\SOURCE\\networking\\network_server_manager.c",
                   0x5ed, 1);
    system_exit(-1);
  }
  if ((*(char *)(param_1 + 0x494) == '\0') &&
      (*(char *)(param_1 + 0x495) == '\0')) {
    countdown_timer_set_time_remaining((int *)(param_1 + 0x488), param_2);
    *(unsigned char *)(param_1 + 0x496) = 0;
    *(unsigned char *)(param_1 + 0x494) = 1;
    network_game_log("server game start countdown started");
  }
}

/* Check whether any team (0 or 1) has zero active clients among the 16 client
 * slots at server+0x22E..+0x44C (stride 0x20).  Returns true when at least one
 * team is empty, false when both teams have members (0x12d040). */
__declspec(noinline) bool get_unique_random_name(void *server)
{
  char *s;
  char *client_ptr;
  int16_t counts[2];
  signed char team;
  int i, j;

  s = (char *)server;
  if (*(char *)(s + 0xc8) == 0)
    return false;

  counts[0] = 0;
  counts[1] = 0;
  client_ptr = s + 0x24c;
  for (i = 0x10; i != 0; i--) {
    if (network_player_is_valid(client_ptr - 0x1e)) {
      team = *client_ptr;
      if (team >= 0 && team < 2)
        counts[team]++;
    }
    client_ptr += 0x20;
  }

  for (j = 0; j < 2; j++) {
    if (counts[j] == 0)
      return true;
  }
  return false;
}

/* Check that every machine slot with a valid team index has at least one
 * active client on that team (0x12d0c0). Iterates the 4 machine slots at
 * server+0x448 (stride 0x10) and for each valid slot, searches the 16 client
 * entries at server+0x22e (stride 0x20) for a matching team byte. Returns
 * false if any valid slot has no matching active client. */
__declspec(noinline) bool get_unique_random_color(void *server)
{
  char *s = (char *)server;
  short *slot = (short *)(s + 0x448);
  int i, j;

  for (i = 0; i < 4; i++) {
    if (*slot >= 0 && *slot < 4) {
      bool found = false;
      char *client_ptr = s + 0x24a;
      for (j = 0x10; j != 0; j--) {
        if (network_player_is_valid(client_ptr - 0x1c)) {
          if ((signed char)*client_ptr == *slot)
            found = true;
        }
        client_ptr += 0x20;
      }
      if (!found)
        return false;
    }
    slot = (short *)((char *)slot + 0x10);
  }
  return true;
}

/* Check whether enough machine slots have valid team indices (0x12d150).
 * Counts slots in [0,4) across the 4 machine entries at server+0x448
 * (stride 0x10). If network_game_is_splitscreen_local returns true the
 * threshold is 1, otherwise 2. Returns count >= threshold. */
__declspec(noinline) bool server_has_enough_machines(void *server)
{
  char *s = (char *)server;
  int threshold = network_game_is_splitscreen_local() ? 1 : 2;
  int count = 0;

  if (*(int16_t *)(s + 0x448) >= 0 && *(int16_t *)(s + 0x448) < 4)
    count++;
  if (*(int16_t *)(s + 0x458) >= 0 && *(int16_t *)(s + 0x458) < 4)
    count++;
  if (*(int16_t *)(s + 0x468) >= 0 && *(int16_t *)(s + 0x468) < 4)
    count++;
  if (*(int16_t *)(s + 0x478) >= 0 && *(int16_t *)(s + 0x478) < 4)
    count++;

  return count >= threshold;
}

/* Predicate: server is ready to start the countdown (0x12d1c0).
 * Requires enough machines, a valid color, no pending unique-name conflict,
 * and [server+0x22c] >= sign-extended [server+0x115]. */
bool server_ok_to_countdown(void *server)
{
  char *s = (char *)server;

  return server_has_enough_machines(server) &&
         get_unique_random_color(server) && !get_unique_random_name(server) &&
         *(short *)(s + 0x22c) >= (short)*(char *)(s + 0x115);
}

/* Zero out a machine struct (0x44 bytes) and set byte at +0x40 to 0xff.
 * 0x12d210 / network_server_manager.obj
 */
void network_game_server_invalidate_network_machine(void *machine)
{
  if (!machine) {
    display_assert(0, 0, 0x6c9, 1);
    system_exit(-1);
  }
  csmemset(machine, 0, 0x44);
  *(char *)((char *)machine + 0x40) = (char)0xff;
}

/* Generate a 16-byte join token by writing "message in a bot" (0x12d250). */
void network_game_generate_join_game_token(void *join_token)
{
  char buf[0x14];

  buf[0] = 'm';
  buf[1] = 'e';
  buf[2] = 's';
  buf[3] = 's';
  buf[4] = 'a';
  buf[5] = 'g';
  buf[6] = 'e';
  buf[7] = ' ';
  buf[8] = 'i';
  buf[9] = 'n';
  buf[10] = ' ';
  buf[11] = 'a';
  buf[12] = ' ';
  buf[13] = 'b';
  buf[14] = 'o';
  buf[15] = 't';
  buf[16] = 't';
  buf[17] = 'l';
  buf[18] = 'e';
  if (!join_token) {
    display_assert("join_token",
                   "c:\\halo\\SOURCE\\networking\\network_server_manager.c",
                   0x6da, 1);
    system_exit(-1);
  }
  csmemset(join_token, 0, 4);
  csmemcpy(join_token, buf, 0x10);
}

/* Get the copied network-machine slot for a client machine (0x12d2f0).
 * Returns server+0x11c+machine_index*0x44 and writes its index byte to *out. */
int network_game_server_get_client_machine(int server, int machine, int *out)
{
  int result;

  if (!server || !machine) {
    display_assert("server && client_machine",
                   "c:\\halo\\SOURCE\\networking\\network_server_manager.c",
                   0x701, 1);
    system_exit(-1);
  }
  if (*(short *)(machine + 0xc) > 3) {
    display_assert(
      "client_machine->machine_index<MAXIMUM_NETWORK_MACHINE_COUNT",
      "c:\\halo\\SOURCE\\networking\\network_server_manager.c", 0x702, 1);
    system_exit(-1);
  }
  if (out)
    *out = -1;
  result = *(short *)(machine + 0xc) * 0x44 + server + 0x11c;
  if (out)
    *out = (int)*(char *)(result + 0x40);
  return result;
}

/* Return the connection object from the server (server[0]).
 * 0x12d380 / network_server_manager.obj
 */
int network_game_server_get_connection(void *server)
{
  if (!server) {
    display_assert(0, 0, 0x712, 1);
    system_exit(-1);
  }
  return *(int *)server;
}

/* Return the connection handle from a machine struct (0x12d3b0).
 * Returns the first dword at machine+0, or 0 if machine is NULL. */
int network_game_server_adjust_machine_settings(void *machine)
{
  if (machine != NULL)
    return *(int *)machine;
  return 0;
}

/* Return the connection handle for a machine by scanning server+0x43c
 * (0x12d3d0). Finds the slot whose machine_index matches machine+0x40; returns
 * connection or 0. */
int network_game_server_get_machine_connection(int server, int machine)
{
  int i;
  short *slot;
  short machine_idx;
  int result;

  result = 0;
  if (!server || !machine || *(char *)(machine + 0x40) < 0 ||
      !(*(char *)(machine + 0x40) < 4)) {
    display_assert("server && network_machine_is_valid(machine)",
                   "c:\\halo\\SOURCE\\networking\\network_server_manager.c",
                   0x72f, 1);
    system_exit(-1);
  }
  machine_idx = (short)*(char *)(machine + 0x40);
  i = 0;
  slot = (short *)(server + 0x448);
  do {
    if (*slot == machine_idx)
      return *(int *)(i * 0x10 + 0x43c + server);
    i++;
    slot += 8;
  } while (i < 4);
  return result;
}

/* Get a pointer to the machine entry at the given index (0x12d450).
 * Asserts server is non-null and index < MAXIMUM_NETWORK_MACHINE_COUNT (4).
 * Each machine entry is 0x10 bytes, starting at server+0x43c. */
int network_game_server_get_client_machine_at_index(int server,
                                                    int machine_index)
{
  if (!server || machine_index >= 4) {
    display_assert("server && (index<MAXIMUM_NETWORK_MACHINE_COUNT)",
                   "c:\\halo\\SOURCE\\networking\\network_server_manager.c",
                   0x741, 1);
    system_exit(-1);
  }
  return machine_index * 0x10 + 0x43c + server;
}

/* Return a machine entry pointer by scanning for a matching IP address
 * (0x12d4a0). Iterates the 4 connection slots; returns pointer to matching slot
 * or 0. */
int network_game_server_get_client_machine_at_address(int server,
                                                      int ip_address)
{
  int i;
  int *slot;
  int addr_buf[6];
  int result;

  i = 0;
  result = 0;
  if (!server || !ip_address) {
    display_assert("server && ip_address",
                   "c:\\halo\\SOURCE\\networking\\network_server_manager.c",
                   0x74d, 1);
    system_exit(-1);
  }
  slot = (int *)(server + 0x43c);
  do {
    if (*(short *)(slot + 3) >= 0 && *(short *)(slot + 3) < 4) {
      if (!*slot) {
        display_assert("server->client_machines[i].connection",
                       "c:\\halo\\SOURCE\\networking\\network_server_manager.c",
                       0x755, 1);
        system_exit(-1);
      }
      network_connection_get_address(*slot, addr_buf, 0);
      if (addr_buf[0] == ip_address) {
        result = i * 0x10 + 0x43c + server;
        goto done;
      }
    }
    i++;
    slot += 4;
    if (i > 3) {
    done:
      if (i == 4)
        network_game_log("no machine found @ ip #%lX", ip_address);
      return result;
    }
  } while (1);
}

/* Assert server is non-null and return the connection pointer at offset +8
 * (0x12d570). */
int network_game_server_get_game(void *server)
{
  if (!server) {
    display_assert("server",
                   "c:\\halo\\SOURCE\\networking\\network_server_manager.c",
                   0x769, 1);
    system_exit(-1);
  }
  return (int)((char *)server + 8);
}

/* Return the smallest last-update tick across all 4 machine slots that are
 * joined and have a valid update tick. Returns 0xffffffff if none qualify.
 * 0x12d5b0 / network_server_manager.obj */
unsigned int FUN_0012d5b0(int param_1)
{
  unsigned int uVar1;

  uVar1 = 0xffffffff;
  if ((*(short *)(param_1 + 0x448) >= 0) && (*(short *)(param_1 + 0x448) < 4) &&
      (*(unsigned int *)(param_1 + 0x440) != 0xffffffff)) {
    uVar1 = *(unsigned int *)(param_1 + 0x440);
  }
  if ((*(short *)(param_1 + 0x458) >= 0) && (*(short *)(param_1 + 0x458) < 4) &&
      (uVar1 > *(unsigned int *)(param_1 + 0x450))) {
    uVar1 = *(unsigned int *)(param_1 + 0x450);
  }
  if ((*(short *)(param_1 + 0x468) >= 0) && (*(short *)(param_1 + 0x468) < 4) &&
      (uVar1 > *(unsigned int *)(param_1 + 0x460))) {
    uVar1 = *(unsigned int *)(param_1 + 0x460);
  }
  if ((*(short *)(param_1 + 0x478) >= 0) && (*(short *)(param_1 + 0x478) < 4) &&
      (uVar1 > *(unsigned int *)(param_1 + 0x470))) {
    uVar1 = *(unsigned int *)(param_1 + 0x470);
  }
  return uVar1;
}

/* Return true if the server can start counting down (state 0, machines joined).
 * 0x12d640 / network_server_manager.obj
 */
int network_game_server_game_can_start(void *server)
{
  if (!server) {
    display_assert(0, 0, 0x782, 1);
    system_exit(-1);
  }
  if (*(short *)((char *)server + 4) == 0 &&
      *(char *)((char *)server + 0x115) <= *(short *)((char *)server + 0x22c)) {
    return 1;
  }
  return 0;
}

/* Set or clear the countdown pause flag; clear the countdown struct if pausing.
 * 0x12d690 / network_server_manager.obj
 */
void network_game_server_pause_countdown(void *server, char flag)
{
  if (!server) {
    display_assert(0, 0, 0x78c, 1);
    system_exit(-1);
  }
  if (flag == '\x01') {
    csmemset((char *)server + 0x488, 0, 0x10);
  }
  *(char *)((char *)server + 0x495) = flag;
}

/* Set map name, clear preloaded flags on valid machines, notify clients
 * (0x12d6f0). */
void network_game_server_change_map_name(int server, char *map_name)
{
  char *s;

  if (!server || !map_name || !map_name[0]) {
    display_assert("server && map_name && map_name[0]",
                   "c:\\halo\\SOURCE\\networking\\network_server_manager.c",
                   0x79b, 1);
    system_exit(-1);
  }
  if (*(short *)(server + 4) != 0) {
    display_assert("server->state == _network_game_server_state_pregame",
                   "c:\\halo\\SOURCE\\networking\\network_server_manager.c",
                   0x79c, 1);
    system_exit(-1);
  }
  s = (char *)server;
  if (*(short *)(s + 0x448) >= 0 && *(short *)(s + 0x448) < 4)
    *(unsigned short *)(s + 0x44a) &= 0xfff7;
  if (*(short *)(s + 0x458) >= 0 && *(short *)(s + 0x458) < 4)
    *(unsigned short *)(s + 0x45a) &= 0xfff7;
  if (*(short *)(s + 0x468) >= 0 && *(short *)(s + 0x468) < 4)
    *(unsigned short *)(s + 0x46a) &= 0xfff7;
  if (*(short *)(s + 0x478) >= 0 && *(short *)(s + 0x478) < 4)
    *(unsigned short *)(s + 0x47a) &= 0xfff7;
  csstrncpy(s + 0x2c, map_name, 0x7f);
  *(char *)(s + 0xab) = 0;
  if (!FUN_0012f5d0((void *)server))
    network_game_log(
      "network_game_server_change_map_name() failed to send updated game "
      "settings to clients");
}

/* Copy game variant data into server and broadcast it to clients.
 * 0x12d7f0 / network_server_manager.obj
 */
void network_game_server_change_game_variant(void *server, void *variant)
{
  char cVar1;
  if (!server || !variant) {
    display_assert(0, 0, 0x7be, 1);
    system_exit(-1);
  }
  if (*(short *)((char *)server + 4) != 0) {
    display_assert(0, 0, 0x7bf, 1);
    system_exit(-1);
  }
  csmemcpy((char *)server + 0xac, variant, 0x68);
  cVar1 = (char)FUN_0012f5d0(server);
  if (!cVar1) {
    network_game_log("network_game_server_change_game_variant() failed to send "
                     "updated game settings to clients");
  }
}

/* FUN_0012d880 (0x12d880) — XBE naked draft (batch 123). */
#if defined(__clang__)
static void (*const b12d880_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b12d880_exitfn)(int) = system_exit;
static bool (*const b12d880_c12c100)(void *server) = network_game_server_game_is_open;
static void (*const b12d880_c1283c0)(int connection, void *buf, int flag) = network_connection_get_address;
static bool (*const b12d880_c12a160)(void) = network_game_accept_remote_connections;
static const char * (*const b12d880_c81b90)(void *addr) = transport_address_to_string;
static void (*const b12d880_c12b650)(const char *fmt, ...) = network_game_log;
static void (*const b12d880_c12acb0)(void *game, uint16_t machine_index) = network_game_invalidate_machine;
static bool (*const b12d880_c1285c0)(int connection, int new_connection) = network_connection_server_accept_client_connection;

__attribute__((naked, noinline))
bool FUN_0012d880(int server __attribute__((unused)), int new_connection __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x1c, %%esp\n\t"
      "pushl %%ebx\n\t"
      "movl %%eax, %%ebx\n\t"
      "testl %%ebx, %%ebx\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "je .LFUN_0012d880_1\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_0012d880_2\n\t"
      ".LFUN_0012d880_1:\n\t"
      "pushl $1\n\t"
      "pushl $0x7d4\n\t"
      "pushl $0x296bf0\n\t"
      "pushl $0x297a9c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0012d880_2:\n\t"
      "pushl %%ebx\n\t"
      "call *%[c12c100]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0012d880_10\n\t"
      "pushl %%esi\n\t"
      "xorl %%esi, %%esi\n\t"
      "leal 0x448(%%ebx), %%eax\n\t"
      ".LFUN_0012d880_3:\n\t"
      "cmpw $-1, (%%eax)\n\t"
      "je .LFUN_0012d880_4\n\t"
      "incl %%esi\n\t"
      "addl $0x10, %%eax\n\t"
      "cmpl $4, %%esi\n\t"
      "jl .LFUN_0012d880_3\n\t"
      "jmp .LFUN_0012d880_7\n\t"
      ".LFUN_0012d880_4:\n\t"
      "xorl %%eax, %%eax\n\t"
      "movl %%eax, -0x18(%%ebp)\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movl %%ecx, -0xc(%%ebp)\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "pushl %%ecx\n\t"
      "leal -0x1c(%%ebp), %%edx\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "movl $0, -0x1c(%%ebp)\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "call *%[c1283c0]\n\t"
      "movl -0x1c(%%ebp), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_0012d880_6\n\t"
      "call *%[c12a160]\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_0012d880_5\n\t"
      "cmpl $0x7f000001, -0x1c(%%ebp)\n\t"
      "je .LFUN_0012d880_5\n\t"
      "leal -0x1c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c81b90]\n\t"
      "pushl %%eax\n\t"
      "pushl $0x297a38\n\t"
      "call *%[c12b650]\n\t"
      "addl $0xc, %%esp\n\t"
      "jmp .LFUN_0012d880_7\n\t"
      ".LFUN_0012d880_5:\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%edi\n\t"
      "movl %%esi, %%edx\n\t"
      "shll $4, %%edx\n\t"
      "leal 0x8(%%ebx), %%ecx\n\t"
      "leal (%%edx,%%ebx,1), %%edi\n\t"
      "pushl %%esi\n\t"
      "pushl %%ecx\n\t"
      "movl %%eax, 0x43c(%%edi)\n\t"
      "call *%[c12acb0]\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "movw %%si, 0x448(%%edi)\n\t"
      "movw $1, 0x44a(%%edi)\n\t"
      "movl (%%ebx), %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c1285c0]\n\t"
      "addl $0x10, %%esp\n\t"
      "movb %%al, %%bl\n\t"
      "cmpb $1, %%bl\n\t"
      "popl %%edi\n\t"
      "jne .LFUN_0012d880_8\n\t"
      "leal -0x1c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c81b90]\n\t"
      "pushl %%eax\n\t"
      "pushl $0x297a10\n\t"
      "call *%[c12b650]\n\t"
      "addl $0xc, %%esp\n\t"
      "jmp .LFUN_0012d880_8\n\t"
      ".LFUN_0012d880_6:\n\t"
      "pushl $0x2979a8\n\t"
      "call *%[c12b650]\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_0012d880_7:\n\t"
      "movb -0x1(%%ebp), %%bl\n\t"
      ".LFUN_0012d880_8:\n\t"
      "cmpl $4, %%esi\n\t"
      "popl %%esi\n\t"
      "jne .LFUN_0012d880_9\n\t"
      "pushl $0x297950\n\t"
      "call *%[c12b650]\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_0012d880_9:\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0012d880_10:\n\t"
      "pushl $0x297908\n\t"
      "call *%[c12b650]\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "addl $4, %%esp\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b12d880_assert), [exitfn] "m"(b12d880_exitfn), [c12c100] "m"(b12d880_c12c100), [c1283c0] "m"(b12d880_c1283c0), [c12a160] "m"(b12d880_c12a160), [c81b90] "m"(b12d880_c81b90), [c12b650] "m"(b12d880_c12b650), [c12acb0] "m"(b12d880_c12acb0), [c1285c0] "m"(b12d880_c1285c0)
      : "memory");
}
#else
#error "FUN_0012d880: clang naked draft required"
#endif


/* Handle incoming datagrams on the server's public endpoint (0x12d9f0).
 * Loops reading datagrams and dispatching them until none remain. */
bool FUN_0012d9f0(int server)
{
  char *s = (char *)server;
  bool result = true;
  char buffer[0x190];
  char addr[24];
  int size = 0x190;

  if (!server) {
    display_assert("server",
                   "c:\\halo\\SOURCE\\networking\\network_server_manager.c",
                   0x810, 1);
    system_exit(-1);
  }

  do {
    if (!FUN_001298f0(*(int *)s, buffer, &size, addr))
      return result;
    result = FUN_00130270((void *)server, buffer, size, addr);
    if (!result) {
      network_game_log("network_game_server_handle_datagram() failed in "
                       "network_game_server_handle_public_endpoint()");
    }
    size = 0x190;
  } while (result);

  return false;
}

/* FUN_0012da90 (0x12da90) — XBE naked draft (batch 145). */
#if defined(__clang__)
static void (*const b12da90_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b12da90_exitfn)(int) = system_exit;
static void * (*const b12da90_c12b700)(int type, void *data, int16_t message_struct_size) = encode_network_game_message;
static void (*const b12da90_c80c20)(unsigned short *header, int byte_order) = byte_swap_message_header;
static int (*const b12da90_c82f50)(int *ep, const char *buf, int len) = send_endpoint;
static const char * (*const b12da90_c81c80)(int error_code) = FUN_00081c80;
static void (*const b12da90_c12b650)(const char *fmt, ...) = network_game_log;

__attribute__((naked, noinline))
void FUN_0012da90(int endpoint __attribute__((unused)), unsigned short reason __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "testl %%ebx, %%ebx\n\t"
      "movw %%ax, -0x4(%%ebp)\n\t"
      "je .LFUN_0012da90_1\n\t"
      "cmpw $7, %%ax\n\t"
      "jb .LFUN_0012da90_2\n\t"
      ".LFUN_0012da90_1:\n\t"
      "pushl $1\n\t"
      "pushl $0x878\n\t"
      "pushl $0x296bf0\n\t"
      "pushl $0x297bcc\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0012da90_2:\n\t"
      "pushl %%edi\n\t"
      "pushl $2\n\t"
      "leal -0x4(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $5\n\t"
      "call *%[c12b700]\n\t"
      "movl %%eax, %%edi\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%edi, %%edi\n\t"
      "je .LFUN_0012da90_3\n\t"
      "pushl %%esi\n\t"
      "movzwl (%%edi), %%esi\n\t"
      "pushl $1\n\t"
      "pushl %%edi\n\t"
      "shrl $4, %%esi\n\t"
      "call *%[c80c20]\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "call *%[c82f50]\n\t"
      "addl $0x14, %%esp\n\t"
      "cmpl %%esi, %%eax\n\t"
      "popl %%esi\n\t"
      "je .LFUN_0012da90_4\n\t"
      "pushl %%eax\n\t"
      "call *%[c81c80]\n\t"
      "pushl %%eax\n\t"
      "pushl $0x297b88\n\t"
      "call *%[c12b650]\n\t"
      "addl $0xc, %%esp\n\t"
      "popl %%edi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0012da90_3:\n\t"
      "pushl $0x297b18\n\t"
      "call *%[c12b650]\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_0012da90_4:\n\t"
      "popl %%edi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b12da90_assert), [exitfn] "m"(b12da90_exitfn), [c12b700] "m"(b12da90_c12b700), [c80c20] "m"(b12da90_c80c20), [c82f50] "m"(b12da90_c82f50), [c81c80] "m"(b12da90_c81c80), [c12b650] "m"(b12da90_c12b650)
      : "memory");
}
#else
#error "FUN_0012da90: clang naked draft required"
#endif


/* FUN_0012db30 (0x12db30) — readable C lift. */
void FUN_0012db30(int endpoint)
{
  extern char DAT_00297c04[];
  network_game_log(DAT_00297c04);
  FUN_0012da90(endpoint, 4);
}

/* Postgame state handler (0x12db60).
 * Every 5 seconds sends a heartbeat message (type 0xb) to all clients. */
bool FUN_0012db60(int server)
{
  unsigned int now;
  short data;

  now = system_milliseconds();
  if (now > *(unsigned int *)((char *)server + 0x480) + 5000) {
    data = 0;
    FUN_0012f430((void *)server, encode_network_game_message(0xb, &data, 2));
    *(unsigned int *)((char *)server + 0x480) = now;
  }
  return true;
}

/* Check if all connected machines have finished precaching (0x12dbb0).
 * Iterates machine slots at server+0x448 (stride 0x10, 4 max).
 * A machine is "valid" if its short at +0 is in [0,3].
 * If a valid machine has bit 3 of byte at +2 clear, returns false (not done).
 * If all valid machines have bit 3 set, asserts that the map is loaded and
 * returns true. */
bool FUN_0012dbb0(int server)
{
  int i;
  char *slot;

  i = 0;
  slot = (char *)server + 0x448;
  while (i < 4) {
    short conn = *(short *)slot;
    if (conn >= 0 && conn < 4) {
      if (((*(uint8_t *)(slot + 2) >> 3) & 1) == 0)
        return false;
    }
    i++;
    slot += 0x10;
  }
  if (!cache_files_precache_map_loaded(main_get_multiplayer_map_name())) {
    display_assert(
      "!all_machines_have_precached || "
      "cache_files_precache_map_loaded(main_get_multiplayer_map_name())",
      "c:\\halo\\SOURCE\\networking\\network_server_manager.c", 0x8c8, 1);
    system_exit(-1);
  }
  return true;
}

/* FUN_0012dc20 (0x12dc20) — XBE naked draft (batch 132). */
#if defined(__clang__)
static void (*const b12dc20_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b12dc20_exitfn)(int) = system_exit;
static void (*const b12dc20_c12b650)(const char *fmt, ...) = network_game_log;
static bool (*const b12dc20_ca8aa0)(void *game_variant_dst, void *game_variant_src) = game_engine_get_current_stage;
static void (*const b12dc20_c12aaf0)(void *name_buffer) = network_game_generate_local_machine_name;
static wchar_t * (*const b12dc20_c19dc90)(wchar_t *dest, wchar_t *src, size_t count) = ustrncpy;
static void (*const b12dc20_c12c060)(void *server) = network_game_server_open_game;
static void (*const b12dc20_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;

__attribute__((naked, noinline))
bool FUN_0012dc20(int server __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x40, %%esp\n\t"
      "testl %%ebx, %%ebx\n\t"
      "jne .LFUN_0012dc20_1\n\t"
      "pushl $1\n\t"
      "pushl $0x961\n\t"
      "pushl $0x296bf0\n\t"
      "pushl $0x296c34\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0012dc20_1:\n\t"
      "pushl $0x297cd4\n\t"
      "call *%[c12b650]\n\t"
      "leal 0x2c(%%ebx), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal 0xac(%%ebx), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[ca8aa0]\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0012dc20_2\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl $5, %%ecx\n\t"
      "movl $0x281c38, %%esi\n\t"
      "leal -0x40(%%ebp), %%edi\n\t"
      "rep movsl\n\t"
      "leal -0x40(%%ebp), %%edx\n\t"
      "xorl %%eax, %%eax\n\t"
      "movl $0xb, %%ecx\n\t"
      "leal -0x2c(%%ebp), %%edi\n\t"
      "pushl %%edx\n\t"
      "rep stosl\n\t"
      "call *%[c12aaf0]\n\t"
      "pushl $0xf\n\t"
      "leal -0x40(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal 0x8(%%ebx), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c19dc90]\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw %%ax, 0x26(%%ebx)\n\t"
      "movl %%eax, 0x28(%%ebx)\n\t"
      "movb 0xc8(%%ebx), %%al\n\t"
      "testb %%al, %%al\n\t"
      "setne %%dl\n\t"
      "incb %%dl\n\t"
      "pushl %%ebx\n\t"
      "movb $2, 0x115(%%ebx)\n\t"
      "movb $0x10, 0x116(%%ebx)\n\t"
      "movb %%dl, 0x117(%%ebx)\n\t"
      "call *%[c12c060]\n\t"
      "addl $0x14, %%esp\n\t"
      "popl %%edi\n\t"
      "movb $1, %%al\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0012dc20_2:\n\t"
      "pushl $0x297c94\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "xorb %%al, %%al\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b12dc20_assert), [exitfn] "m"(b12dc20_exitfn), [c12b650] "m"(b12dc20_c12b650), [ca8aa0] "m"(b12dc20_ca8aa0), [c12aaf0] "m"(b12dc20_c12aaf0), [c19dc90] "m"(b12dc20_c19dc90), [c12c060] "m"(b12dc20_c12c060), [c8f390] "m"(b12dc20_c8f390)
      : "memory");
}
#else
#error "FUN_0012dc20: clang naked draft required"
#endif


/* Dump network game data fields to the log with a prefix (0x12dd20).
 * Prints machine_count, 4 machine slots (stride 0x44 from game_data+0x154),
 * player_count, 16 player entries (stride 0x20 from game_data+0x226),
 * random seed, and games played. */
void FUN_0012dd20(void *game_data, const char *prefix)
{
  char *s = (char *)game_data;
  char *p;
  int i;

  network_game_log("%snetwork_game_data", prefix);
  network_game_log("%smachine_count %d", prefix, (int)*(int16_t *)(s + 0x112));

  p = s + 0x154;
  for (i = 0; i < 4; i++) {
    network_game_log("\t%smachine %d %x", prefix, i, (int)*(signed char *)p);
    p += 0x44;
  }

  network_game_log("%splayer_count %d", prefix, (int)*(int16_t *)(s + 0x224));

  p = s + 0x243;
  for (i = 0; i < 0x10; i++) {
    network_game_log("%splayer %d", prefix, i);
    network_game_log("%s\tmachine_index %x", prefix,
                     (int)*(signed char *)(p - 1));
    network_game_log("%s\tcontroller_index %x", prefix, (int)*(signed char *)p);
    network_game_log("%s\tteam_index %x", prefix, (int)*(signed char *)(p + 1));
    network_game_log("%s\tplayer_list_index %x", prefix,
                     (int)*(signed char *)(p + 2));
    p += 0x20;
  }

  network_game_log("%snetwork_game_random_seed %x", prefix,
                   *(int *)(s + 0x428));
  network_game_log("%snumber_of_games_played %d", prefix, *(int *)(s + 0x42c));
}

/* Dump the full server state to the network game log for debugging (0x12de20).
 * Prints connection, state, flags, game data, all 4 client machine slots
 * (connection, update sequence, stall time, machine index, flags), and
 * timing fields. */
void FUN_0012de20(void *server)
{
  int i;
  char *slot;
  const char *status;

  network_game_log("*************BEGIN*************");
  network_game_log("\tconnection %x", *(int *)server);
  network_game_log("\tstate %x", (int)*(uint16_t *)((char *)server + 4));
  network_game_log("\tflags %x", (int)*(uint16_t *)((char *)server + 6));
  FUN_0012dd20((char *)server + 8, "\t");
  network_game_log("client_machines:");

  i = 0;
  slot = (char *)server + 0x444;
  do {
    status = "no connection";
    if (*(int *)(slot - 8) != 0) {
      if (network_connection_active(*(int *)(slot - 8)))
        status = "(active)";
      else
        status = "(dead)";
    }
    network_game_log("\tclient %d", i);
    network_game_log("\t\tconnection %x %s", *(int *)(slot - 8), status);
    network_game_log("\t\tlast_received_update_sequence_number %d",
                     *(int *)(slot - 4));
    network_game_log("\t\tstall_start_time %d", *(int *)slot);
    network_game_log("\t\tmachine_index %x", (int)*(short *)(slot + 4));
    network_game_log("\t\tflags %x", (int)*(uint16_t *)(slot + 6));
    i++;
    slot += 0x10;
  } while (i < 4);

  network_game_log("\tnext_update_number %d", *(int *)((char *)server + 0x47c));
  network_game_log("\ttime_of_last_keep_alive %d",
                   *(int *)((char *)server + 0x480));
  network_game_log("\ttime_of_first_client_loading_completion %d",
                   *(int *)((char *)server + 0x484));
  network_game_log("*************END*************");
}

/* Remove a client machine from the server's game (0x12df50).
 * If the server is in-game (state 1), broadcasts a player-removal message.
 * Finds and removes the machine's entry from game data (server+8), then
 * clears the matching machine slot (connection, stall, flags) and sets the
 * machine_index to -1. Returns true if the slot was found. */
__declspec(noinline) bool FUN_0012df50(void *server, void *machine)
{
  char *s = (char *)server;
  char *m = (char *)machine;
  char *ptr;
  int i;

  if (!server) {
    display_assert("server",
                   "c:\\halo\\SOURCE\\networking\\network_server_manager.c",
                   0x22f, 1);
    system_exit(-1);
  }
  if (!machine) {
    display_assert("client",
                   "c:\\halo\\SOURCE\\networking\\network_server_manager.c",
                   0x230, 1);
    system_exit(-1);
  }

  if (*(short *)(s + 4) == 1)
    FUN_0012c1c0((int)server, (int)machine);

  ptr = s + 0x15c;
  for (i = 0; i < 4; i++) {
    if ((short)*(signed char *)ptr == *(short *)(m + 0xc)) {
      if (!network_game_remove_machine((void *)(s + 8), (void *)(s + 0x11c + i * 0x44))) {
        error(
          2, "network_game_server_remove_client_machine_from_game() failed to "
             "remove the offending machine from the server's copy of the game");
      }
      break;
    }
    ptr += 0x44;
  }

  for (i = 0; i < 4; i++) {
    if (s + 0x43c + i * 0x10 == m) {
      if (*(int *)(s + 0x43c + i * 0x10) != 0) {
        if (!FUN_00129130(*(int *)s, *(int *)(s + 0x43c + i * 0x10)))
          network_game_log("server failed to close a client's connection");
      }
      *(int *)(s + 0x440 + i * 0x10) = 0;
      *(int *)(s + 0x43c + i * 0x10) = 0;
      *(int *)(s + 0x444 + i * 0x10) = 0;
      *(uint16_t *)(s + 0x44a + i * 0x10) = 0;
      *(short *)(s + 0x448 + i * 0x10) = -1;
      return true;
    }
  }

  network_game_log(
    "network_game_server_remove_client_machine_from_game() failed to find "
    "the specified machine");
  return false;
}

/* Remove a machine from the server's game by its machine_index (0x12e090).
 * Validates the machine_index byte at player_data+0x40. If valid (0..3),
 * searches the 4 machine slots at server+0x448 (stride 0x10) for a matching
 * index, calls FUN_0012df50 to remove it, then FUN_0012b500 to remove
 * the machine from game data. If the server state is 0 (pre-game),
 * sends updated settings to remaining clients. */
bool FUN_0012e090(void *server, void *player_data)
{
  char *s = (char *)server;
  char *pd = (char *)player_data;
  signed char machine_idx;
  short *ptr;
  bool result;
  int i;

  result = false;

  if (!server) {
    display_assert("server",
                   "c:\\halo\\SOURCE\\networking\\network_server_manager.c",
                   0x299, 1);
    system_exit(-1);
  }

  if (*(signed char *)(pd + 0x40) == -1) {
    network_game_log(
      "network_game_server_remove_machine_from_game called with a "
      "machine_index of NONE");
  }

  machine_idx = *(signed char *)(pd + 0x40);
  if (machine_idx < 0 || machine_idx > 3) {
    network_game_log("attempted to remove an invalid machine from the game in "
                     "network_game_server_remove_machine_from_game()");
    network_game_log("machine name = <not implemented>");
    network_game_log("machine index = %x", (int)*(signed char *)(pd + 0x40));
    FUN_0012de20(server);
    return result;
  }

  ptr = (short *)(s + 0x448);
  for (i = 0; i < 4; i++) {
    if (*ptr == (short)machine_idx) {
      result = FUN_0012df50(server, (void *)(s + 0x43c + i * 0x10));
      if (!result) {
        network_game_log(
          "network_game_server_remove_client_machine_from_game() failed in "
          "network_game_server_remove_machine_from_game()");
      }
      break;
    }
    ptr += 8;
    result = false;
  }

  if (i == 4) {
    network_game_log(
      "network_game_server_remove_machine_from_game() failed to find the "
      "specified machine");
  }

  if (*(signed char *)(pd + 0x40) != -1) {
    result = network_game_remove_machine((void *)(s + 8), (void *)player_data);
    if (!result) {
      network_game_log("network_game_remove_machine() failed in "
                       "network_game_server_remove_machine_from_game()");
    }
  }

  if (*(short *)(s + 4) == 0) {
    if (!FUN_0012f5d0(server)) {
      network_game_log(
        "network_game_server_remove_machine_from_game() failed to send "
        "updated game settings to remaining clients");
      return result;
    }
  }

  return result;
}

/* network_game_server_stalled_on_client (0x12e1d0) — XBE naked draft (batch 83). */
#if defined(__clang__)
static void (*const b12e1d0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b12e1d0_exitfn)(int) = system_exit;
static unsigned int (*const b12e1d0_c8e370)(void) = system_milliseconds;
static char * (*const b12e1d0_c19f3a0)(const wchar_t *unicode, char *ascii, int size) = wide_to_ascii;
static void (*const b12e1d0_c12b650)(const char *fmt, ...) = network_game_log;
static bool (*const b12e1d0_c12df50)(void *server, void *machine) = FUN_0012df50;

__attribute__((naked, noinline))
void network_game_server_stalled_on_client(void *server __attribute__((unused)), bool stalled __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x20, %%esp\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .Lnetwork_game_server_stalled_on_client_1\n\t"
      "pushl $1\n\t"
      "pushl $0x59e\n\t"
      "pushl $0x296bf0\n\t"
      "pushl $0x296c34\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lnetwork_game_server_stalled_on_client_1:\n\t"
      "movb 0xc(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lnetwork_game_server_stalled_on_client_12\n\t"
      "movw 0x448(%%esi), %%cx\n\t"
      "movl $0xffffffff, %%eax\n\t"
      "pushl %%ebx\n\t"
      "orl %%eax, %%ebx\n\t"
      "testw %%cx, %%cx\n\t"
      "jl .Lnetwork_game_server_stalled_on_client_2\n\t"
      "cmpw $4, %%cx\n\t"
      "jge .Lnetwork_game_server_stalled_on_client_2\n\t"
      "movl 0x440(%%esi), %%ecx\n\t"
      "cmpl %%eax, %%ecx\n\t"
      "jae .Lnetwork_game_server_stalled_on_client_2\n\t"
      "movl %%ecx, %%eax\n\t"
      "xorl %%ebx, %%ebx\n\t"
      ".Lnetwork_game_server_stalled_on_client_2:\n\t"
      "movw 0x458(%%esi), %%cx\n\t"
      "testw %%cx, %%cx\n\t"
      "jl .Lnetwork_game_server_stalled_on_client_3\n\t"
      "cmpw $4, %%cx\n\t"
      "jge .Lnetwork_game_server_stalled_on_client_3\n\t"
      "movl 0x450(%%esi), %%ecx\n\t"
      "cmpl %%eax, %%ecx\n\t"
      "jae .Lnetwork_game_server_stalled_on_client_3\n\t"
      "movl %%ecx, %%eax\n\t"
      "movl $1, %%ebx\n\t"
      ".Lnetwork_game_server_stalled_on_client_3:\n\t"
      "movw 0x468(%%esi), %%cx\n\t"
      "testw %%cx, %%cx\n\t"
      "jl .Lnetwork_game_server_stalled_on_client_4\n\t"
      "cmpw $4, %%cx\n\t"
      "jge .Lnetwork_game_server_stalled_on_client_4\n\t"
      "movl 0x460(%%esi), %%ecx\n\t"
      "cmpl %%eax, %%ecx\n\t"
      "jae .Lnetwork_game_server_stalled_on_client_4\n\t"
      "movl %%ecx, %%eax\n\t"
      "movl $2, %%ebx\n\t"
      ".Lnetwork_game_server_stalled_on_client_4:\n\t"
      "movw 0x478(%%esi), %%cx\n\t"
      "testw %%cx, %%cx\n\t"
      "jl .Lnetwork_game_server_stalled_on_client_5\n\t"
      "cmpw $4, %%cx\n\t"
      "jge .Lnetwork_game_server_stalled_on_client_5\n\t"
      "cmpl %%eax, 0x470(%%esi)\n\t"
      "jae .Lnetwork_game_server_stalled_on_client_5\n\t"
      "movl $3, %%ebx\n\t"
      ".Lnetwork_game_server_stalled_on_client_5:\n\t"
      "cmpl $-1, %%ebx\n\t"
      "jne .Lnetwork_game_server_stalled_on_client_6\n\t"
      "pushl $1\n\t"
      "pushl $0x5b1\n\t"
      "pushl $0x296bf0\n\t"
      "pushl $0x298350\n\t"
      "call *%[assert]\n\t"
      "pushl %%ebx\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lnetwork_game_server_stalled_on_client_6:\n\t"
      "movl %%ebx, %%eax\n\t"
      "shll $4, %%eax\n\t"
      "pushl %%edi\n\t"
      "leal (%%eax,%%esi,1), %%edi\n\t"
      "movl 0x444(%%edi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lnetwork_game_server_stalled_on_client_8\n\t"
      "call *%[c8e370]\n\t"
      "subl 0x444(%%edi), %%eax\n\t"
      "cmpl $0x7d0, %%eax\n\t"
      "jb .Lnetwork_game_server_stalled_on_client_9\n\t"
      "movswl 0x448(%%edi), %%edx\n\t"
      "imull $0x44, %%edx, %%edx\n\t"
      "pushl $0x20\n\t"
      "leal -0x20(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal 0x11c(%%edx,%%esi,1), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c19f3a0]\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "leal -0x20(%%ebp), %%eax\n\t"
      "jne .Lnetwork_game_server_stalled_on_client_7\n\t"
      "movl $0x298340, %%eax\n\t"
      ".Lnetwork_game_server_stalled_on_client_7:\n\t"
      "pushl %%eax\n\t"
      "pushl $0x298304\n\t"
      "call *%[c12b650]\n\t"
      "addl $0x43c, %%edi\n\t"
      "pushl %%edi\n\t"
      "pushl %%esi\n\t"
      "call *%[c12df50]\n\t"
      "addl $0x10, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lnetwork_game_server_stalled_on_client_9\n\t"
      "pushl $1\n\t"
      "pushl $0x5c1\n\t"
      "pushl $0x296bf0\n\t"
      "pushl $0x2982fc\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "jmp .Lnetwork_game_server_stalled_on_client_9\n\t"
      ".Lnetwork_game_server_stalled_on_client_8:\n\t"
      "call *%[c8e370]\n\t"
      "movl %%eax, 0x444(%%edi)\n\t"
      ".Lnetwork_game_server_stalled_on_client_9:\n\t"
      "xorl %%eax, %%eax\n\t"
      "leal 0x444(%%esi), %%ecx\n\t"
      "popl %%edi\n\t"
      ".Lnetwork_game_server_stalled_on_client_10:\n\t"
      "cmpl %%ebx, %%eax\n\t"
      "je .Lnetwork_game_server_stalled_on_client_11\n\t"
      "movl $0, (%%ecx)\n\t"
      ".Lnetwork_game_server_stalled_on_client_11:\n\t"
      "incl %%eax\n\t"
      "addl $0x10, %%ecx\n\t"
      "cmpl $4, %%eax\n\t"
      "jl .Lnetwork_game_server_stalled_on_client_10\n\t"
      "popl %%ebx\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lnetwork_game_server_stalled_on_client_12:\n\t"
      "leal 0x444(%%esi), %%eax\n\t"
      "movl $4, %%ecx\n\t"
      ".Lnetwork_game_server_stalled_on_client_13:\n\t"
      "movl $0, (%%eax)\n\t"
      "addl $0x10, %%eax\n\t"
      "decl %%ecx\n\t"
      "jne .Lnetwork_game_server_stalled_on_client_13\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b12e1d0_assert), [exitfn] "m"(b12e1d0_exitfn), [c8e370] "m"(b12e1d0_c8e370), [c19f3a0] "m"(b12e1d0_c19f3a0), [c12b650] "m"(b12e1d0_c12b650), [c12df50] "m"(b12e1d0_c12df50)
      : "memory");
}
#else
#error "network_game_server_stalled_on_client: clang naked draft required"
#endif


/* Update the pre-game countdown state machine (0x12e3a0).
 * Drives the server-side countdown timer based on param_2 (countdown event
 * type: 0=increment, 1=clamp-and-latch, 2=cancel, 3=reset).
 * If the server is already in the waiting-for-clients path (0x494==0),
 * starts or validates a timer and transitions 0x494 to 1 when conditions are
 * met.  If in the active countdown path (0x494==1), advances or cancels the
 * timer based on the event type.  Returns early if the server is NULL or not
 * in pregame state. */
void network_game_server_update_countdown(void *server, short param_2)
{
  char cVar1;
  unsigned int uVar2;
  short *psVar3;
  int iVar4;
  short sVar5;
  int *puVar6;
  int param_1;

  param_1 = (int)server;

  if ((param_1 == 0) || (*(short *)(param_1 + 4) != 0)) {
    display_assert(
      "server && server->state == _network_game_server_state_pregame",
      "c:\\halo\\SOURCE\\networking\\network_server_manager.c", 0x66e, 1);
    system_exit(-1);
  }
  if ((*(unsigned char *)(param_1 + 0x495) == '\0') &&
      ((cVar1 = server_ok_to_countdown((void *)param_1),
        cVar1 != '\0' || (param_2 == 2)))) {
    if (*(unsigned char *)(param_1 + 0x494) == '\x01') {
      if (*(unsigned char *)(param_1 + 0x496) == '\0') {
        switch (param_2) {
        case 0:
          *(unsigned char *)(param_1 + 0x496) = 1;
          countdown_timer_increment((int *)(param_1 + 0x488), 5000, 30999);
          return;
        case 1:
          *(unsigned char *)(param_1 + 0x496) = 1;
          puVar6 = (int *)(param_1 + 0x488);
          iVar4 = countdown_timer_get_time_remaining((void *)puVar6);
          if (iVar4 > 999) {
            countdown_timer_decrement(puVar6, 5000);
            iVar4 = countdown_timer_get_time_remaining((void *)puVar6);
            if (iVar4 < 999) {
              uVar2 = system_milliseconds();
              *puVar6 = 999;
              *(unsigned int *)(param_1 + 0x48c) = uVar2;
              return;
            }
          }
          break;
        case 2:
          *(unsigned char *)(param_1 + 0x494) = 0;
          *(unsigned char *)(param_1 + 0x496) = 1;
          return;
        case 3:
          *(unsigned char *)(param_1 + 0x496) = 1;
          uVar2 = system_milliseconds();
          *(int *)(param_1 + 0x488) = 0;
          *(unsigned int *)(param_1 + 0x48c) = uVar2;
          return;
        }
      }
    } else {
      system_milliseconds();
      if (param_2 == 3) {
        uVar2 = system_milliseconds();
        *(int *)(param_1 + 0x488) = 0;
        *(unsigned int *)(param_1 + 0x48c) = uVar2;
        *(unsigned char *)(param_1 + 0x496) = 0;
        *(unsigned char *)(param_1 + 0x494) = 1;
        return;
      }
      cVar1 = network_game_accept_remote_connections();
      if (cVar1 != '\0') {
        sVar5 = 0;
        psVar3 = (short *)(param_1 + 0x448);
        iVar4 = 4;
        do {
          if ((*(int *)((char *)psVar3 - 12) != 0) && (*psVar3 != -1)) {
            sVar5 = sVar5 + 1;
          }
          psVar3 = psVar3 + 8;
          iVar4 = iVar4 + -1;
        } while (iVar4 != 0);
        if (sVar5 < 2) {
          return;
        }
      }
      cVar1 = network_game_is_splitscreen_local();
      *(unsigned char *)(param_1 + 0x494) = 1;
      countdown_timer_set_time_remaining((int *)(param_1 + 0x488),
                                         (cVar1 != '\0') ? 10711 : 30999);
      *(int *)(param_1 + 0x490) = 0;
      *(unsigned char *)(param_1 + 0x496) = 0;
    }
  }
  return;
}

/* FUN_0012e580 (0x12e580) — XBE naked draft (batch 118). */
#if defined(__clang__)
static void (*const b12e580_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b12e580_exitfn)(int) = system_exit;
static bool (*const b12e580_c128660)(int connection) = network_connection_active;
static bool (*const b12e580_c12e090)(void *server, void *player_data) = FUN_0012e090;
static void (*const b12e580_c12b650)(const char *fmt, ...) = network_game_log;
static void (*const b12e580_c12de20)(void *server) = FUN_0012de20;
static bool (*const b12e580_c129cf0)(int connection, int flag, int *output) = FUN_00129cf0;
static bool (*const b12e580_c128360)(int connection) = network_connection_connected;
static bool (*const b12e580_c1298f0)(int connection, void *buffer, int *size, void *addr) = FUN_001298f0;
static bool (*const b12e580_c130580)(void *server, void *machine, void *buffer, int size) = FUN_00130580;
static bool (*const b12e580_c12df50)(void *server, void *machine) = FUN_0012df50;

__attribute__((naked, noinline))
bool FUN_0012e580(int server __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x808, %%esp\n\t"
      "testl %%ebx, %%ebx\n\t"
      "jne .LFUN_0012e580_1\n\t"
      "pushl $1\n\t"
      "pushl $0x827\n\t"
      "pushl $0x296bf0\n\t"
      "pushl $0x296c34\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0012e580_1:\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl $0, -0x4(%%ebp)\n\t"
      "leal 0x448(%%ebx), %%esi\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_0012e580_2:\n\t"
      "cmpl $4, -0x4(%%ebp)\n\t"
      "jge .LFUN_0012e580_12\n\t"
      "cmpw $-1, (%%esi)\n\t"
      "je .LFUN_0012e580_11\n\t"
      "movl -0xc(%%esi), %%eax\n\t"
      "leal -0xc(%%esi), %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[c128660]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_0012e580_4\n\t"
      "movswl (%%esi), %%ecx\n\t"
      "imull $0x44, %%ecx, %%ecx\n\t"
      "leal 0x11c(%%ecx,%%ebx,1), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ebx\n\t"
      "call *%[c12e090]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0012e580_3\n\t"
      "movswl (%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x298484\n\t"
      "call *%[c12b650]\n\t"
      "pushl %%ebx\n\t"
      "call *%[c12de20]\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "addl $0xc, %%esp\n\t"
      "incl %%ecx\n\t"
      "movl %%ecx, -0x4(%%ebp)\n\t"
      "addl $0x10, %%esi\n\t"
      "jmp .LFUN_0012e580_2\n\t"
      ".LFUN_0012e580_3:\n\t"
      "movswl (%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x298454\n\t"
      "call *%[c12b650]\n\t"
      "pushl %%ebx\n\t"
      "call *%[c12de20]\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "addl $0xc, %%esp\n\t"
      "incl %%ecx\n\t"
      "movl %%ecx, -0x4(%%ebp)\n\t"
      "addl $0x10, %%esi\n\t"
      "jmp .LFUN_0012e580_2\n\t"
      ".LFUN_0012e580_4:\n\t"
      "movl (%%edi), %%edx\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl %%edx\n\t"
      "call *%[c129cf0]\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0012e580_7\n\t"
      "movl (%%edi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c128360]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0012e580_7\n\t"
      ".LFUN_0012e580_5:\n\t"
      "movl (%%edi), %%eax\n\t"
      "pushl $0\n\t"
      "leal -0x8(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x808(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "movl $0x800, -0x8(%%ebp)\n\t"
      "call *%[c1298f0]\n\t"
      "addl $0x10, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0012e580_11\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x808(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "call *%[c130580]\n\t"
      "addl $0x10, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_0012e580_5\n\t"
      "pushl $0x2983f0\n\t"
      "call *%[c12b650]\n\t"
      "movswl (%%esi), %%eax\n\t"
      "imull $0x44, %%eax, %%eax\n\t"
      "leal 0x11c(%%eax,%%ebx,1), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "call *%[c12e090]\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0012e580_6\n\t"
      "movswl (%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x2983cc\n\t"
      "jmp .LFUN_0012e580_10\n\t"
      ".LFUN_0012e580_6:\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "call *%[c12df50]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_0012e580_11\n\t"
      "movswl (%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "jmp .LFUN_0012e580_9\n\t"
      ".LFUN_0012e580_7:\n\t"
      "movswl (%%esi), %%ecx\n\t"
      "imull $0x44, %%ecx, %%ecx\n\t"
      "leal 0x11c(%%ecx,%%ebx,1), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ebx\n\t"
      "call *%[c12e090]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0012e580_8\n\t"
      "movswl (%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x2983cc\n\t"
      "jmp .LFUN_0012e580_10\n\t"
      ".LFUN_0012e580_8:\n\t"
      "movswl (%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      ".LFUN_0012e580_9:\n\t"
      "pushl $0x2983a0\n\t"
      ".LFUN_0012e580_10:\n\t"
      "call *%[c12b650]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_0012e580_11:\n\t"
      "incl -0x4(%%ebp)\n\t"
      "addl $0x10, %%esi\n\t"
      "jmp .LFUN_0012e580_2\n\t"
      ".LFUN_0012e580_12:\n\t"
      "popl %%edi\n\t"
      "movb $1, %%al\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b12e580_assert), [exitfn] "m"(b12e580_exitfn), [c128660] "m"(b12e580_c128660), [c12e090] "m"(b12e580_c12e090), [c12b650] "m"(b12e580_c12b650), [c12de20] "m"(b12e580_c12de20), [c129cf0] "m"(b12e580_c129cf0), [c128360] "m"(b12e580_c128360), [c1298f0] "m"(b12e580_c1298f0), [c130580] "m"(b12e580_c130580), [c12df50] "m"(b12e580_c12df50)
      : "memory");
}
#else
#error "FUN_0012e580: clang naked draft required"
#endif


/* FUN_0012e750 (0x12e750) — XBE naked draft (batch 112). */
#if defined(__clang__)
static unsigned int (*const b12e750_c8e370)(void) = system_milliseconds;
static bool (*const b12e750_c128660)(int connection) = network_connection_active;
static void (*const b12e750_c12b650)(const char *fmt, ...) = network_game_log;
static bool (*const b12e750_c12df50)(void *server, void *machine) = FUN_0012df50;
static bool (*const b12e750_c12d150)(void *server) = server_has_enough_machines;
static bool (*const b12e750_c12d0c0)(void *server) = get_unique_random_color;
static bool (*const b12e750_c12d040)(void *server) = get_unique_random_name;
static int (*const b12e750_c12bdb0)(void *countdown) = countdown_timer_get_time_remaining;
static bool (*const b12e750_c12dbb0)(int server) = FUN_0012dbb0;
static void (*const b12e750_c12c0b0)(void *server) = network_game_server_close_game;
static bool (*const b12e750_c12c290)(void *server) = FUN_0012c290;
static void *(*const b12e750_memset)(void *, int, unsigned int) = csmemset;
static void * (*const b12e750_c12b700)(int type, void *data, int16_t message_struct_size) = encode_network_game_message;
static bool (*const b12e750_c12f430)(void *server, void *message) = FUN_0012f430;
static char * (*const b12e750_c19f3a0)(const wchar_t *unicode, char *ascii, int size) = wide_to_ascii;
static void (*const b12e750_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b12e750_exitfn)(int) = system_exit;
static void (*const b12e750_c12caa0)(void *server) = network_game_server_all_machines_have_loaded;

__attribute__((naked, noinline))
bool FUN_0012e750(int server __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x2c, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "call *%[c8e370]\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "movb 0x4b9(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "jne .LFUN_0012e750_10\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "leal 0x43c(%%esi), %%edi\n\t"
      "leal (%%ebx), %%ebx\n\t"
      ".LFUN_0012e750_1:\n\t"
      "movl (%%edi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_0012e750_2\n\t"
      "pushl %%eax\n\t"
      "call *%[c128660]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_0012e750_2\n\t"
      "pushl %%ebx\n\t"
      "pushl $0x29856c\n\t"
      "call *%[c12b650]\n\t"
      "pushl %%edi\n\t"
      "pushl %%esi\n\t"
      "call *%[c12df50]\n\t"
      "addl $0x10, %%esp\n\t"
      ".LFUN_0012e750_2:\n\t"
      "incl %%ebx\n\t"
      "addl $0x10, %%edi\n\t"
      "cmpl $4, %%ebx\n\t"
      "jl .LFUN_0012e750_1\n\t"
      "cmpb $1, 0x494(%%esi)\n\t"
      "jne .LFUN_0012e750_9\n\t"
      "pushl %%esi\n\t"
      "call *%[c12d150]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0012e750_3\n\t"
      "pushl %%esi\n\t"
      "call *%[c12d0c0]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0012e750_3\n\t"
      "pushl %%esi\n\t"
      "call *%[c12d040]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_0012e750_3\n\t"
      "movsbw 0x115(%%esi), %%ax\n\t"
      "cmpw %%ax, 0x22c(%%esi)\n\t"
      "jl .LFUN_0012e750_3\n\t"
      "leal 0x488(%%esi), %%edi\n\t"
      "pushl %%edi\n\t"
      "movb $1, %%bl\n\t"
      "call *%[c12bdb0]\n\t"
      "addl $4, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_0012e750_4\n\t"
      "movl %%esi, %%eax\n\t"
      "call *%[c12dbb0]\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0012e750_4\n\t"
      "movb 0x495(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_0012e750_4\n\t"
      "pushl %%esi\n\t"
      "call *%[c12c0b0]\n\t"
      "pushl %%esi\n\t"
      "call *%[c12c290]\n\t"
      "addl $8, %%esp\n\t"
      "cmpb %%bl, %%al\n\t"
      "movb %%al, -0x1(%%ebp)\n\t"
      "je .LFUN_0012e750_14\n\t"
      "pushl $0x29853c\n\t"
      "call *%[c12b650]\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "addl $4, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0012e750_3:\n\t"
      "pushl $0x10\n\t"
      "leal 0x488(%%esi), %%edi\n\t"
      "pushl $0\n\t"
      "pushl %%edi\n\t"
      "xorb %%bl, %%bl\n\t"
      "call *%[memset]\n\t"
      "addl $0xc, %%esp\n\t"
      "jmp .LFUN_0012e750_5\n\t"
      ".LFUN_0012e750_4:\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "subl 0x490(%%esi), %%ecx\n\t"
      "cmpl $0x3e8, %%ecx\n\t"
      "jle .LFUN_0012e750_14\n\t"
      ".LFUN_0012e750_5:\n\t"
      "testb %%bl, %%bl\n\t"
      "movb $0, 0x496(%%esi)\n\t"
      "je .LFUN_0012e750_6\n\t"
      "pushl %%edi\n\t"
      "call *%[c12bdb0]\n\t"
      "movl %%eax, %%ecx\n\t"
      "movl $0x10624dd3, %%eax\n\t"
      "imull %%ecx\n\t"
      "sarl $6, %%edx\n\t"
      "movl %%edx, %%eax\n\t"
      "shrl $0x1f, %%eax\n\t"
      "addl $4, %%esp\n\t"
      "addl %%eax, %%edx\n\t"
      "movw %%dx, -0x8(%%ebp)\n\t"
      "jmp .LFUN_0012e750_7\n\t"
      ".LFUN_0012e750_6:\n\t"
      "movw $0xffff, -0x8(%%ebp)\n\t"
      ".LFUN_0012e750_7:\n\t"
      "pushl $2\n\t"
      "leal -0x8(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $7\n\t"
      "call *%[c12b700]\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_0012e750_14\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[c12f430]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0012e750_8\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "popl %%edi\n\t"
      "movl %%edx, 0x490(%%esi)\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0012e750_8:\n\t"
      "pushl $0x2984f8\n\t"
      "call *%[c12b650]\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "addl $4, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0012e750_9:\n\t"
      "movl 0x480(%%esi), %%eax\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "addl $0x1388, %%eax\n\t"
      "cmpl %%eax, %%ecx\n\t"
      "jle .LFUN_0012e750_14\n\t"
      "pushl $2\n\t"
      "leal -0x8(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0xa\n\t"
      "movw $0, -0x8(%%ebp)\n\t"
      "call *%[c12b700]\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[c12f430]\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "addl $0x14, %%esp\n\t"
      "popl %%edi\n\t"
      "movl %%edx, 0x480(%%esi)\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0012e750_10:\n\t"
      "movl 0x484(%%esi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_0012e750_14\n\t"
      "call *%[c8e370]\n\t"
      "subl 0x484(%%esi), %%eax\n\t"
      "cmpl $0x3a98, %%eax\n\t"
      "jb .LFUN_0012e750_14\n\t"
      "leal 0x44a(%%esi), %%edi\n\t"
      "movl $4, %%ebx\n\t"
      ".LFUN_0012e750_11:\n\t"
      "movw (%%edi), %%ax\n\t"
      "testb $1, %%al\n\t"
      "je .LFUN_0012e750_13\n\t"
      "testb $4, %%al\n\t"
      "jne .LFUN_0012e750_13\n\t"
      "movswl -0x2(%%edi), %%ecx\n\t"
      "imull $0x44, %%ecx, %%ecx\n\t"
      "pushl $0x20\n\t"
      "leal -0x2c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal 0x11c(%%ecx,%%esi,1), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c19f3a0]\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "leal -0x2c(%%ebp), %%eax\n\t"
      "jne .LFUN_0012e750_12\n\t"
      "movl $0x298340, %%eax\n\t"
      ".LFUN_0012e750_12:\n\t"
      "pushl %%eax\n\t"
      "pushl $0x2984a8\n\t"
      "call *%[c12b650]\n\t"
      "leal -0xe(%%edi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[c12df50]\n\t"
      "addl $0x10, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_0012e750_13\n\t"
      "pushl $1\n\t"
      "pushl $0x94e\n\t"
      "pushl $0x296bf0\n\t"
      "pushl $0x2982fc\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0012e750_13:\n\t"
      "addl $0x10, %%edi\n\t"
      "decl %%ebx\n\t"
      "jne .LFUN_0012e750_11\n\t"
      "pushl %%esi\n\t"
      "call *%[c12caa0]\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_0012e750_14:\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "popl %%edi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c8e370] "m"(b12e750_c8e370), [c128660] "m"(b12e750_c128660), [c12b650] "m"(b12e750_c12b650), [c12df50] "m"(b12e750_c12df50), [c12d150] "m"(b12e750_c12d150), [c12d0c0] "m"(b12e750_c12d0c0), [c12d040] "m"(b12e750_c12d040), [c12bdb0] "m"(b12e750_c12bdb0), [c12dbb0] "m"(b12e750_c12dbb0), [c12c0b0] "m"(b12e750_c12c0b0), [c12c290] "m"(b12e750_c12c290), [memset] "m"(b12e750_memset), [c12b700] "m"(b12e750_c12b700), [c12f430] "m"(b12e750_c12f430), [c19f3a0] "m"(b12e750_c19f3a0), [assert] "m"(b12e750_assert), [exitfn] "m"(b12e750_exitfn), [c12caa0] "m"(b12e750_c12caa0)
      : "memory");
}
#else
#error "FUN_0012e750: clang naked draft required"
#endif


/* Dispose the network game server (0x12ea00).
 * Sends graceful exit messages based on current state (pregame or postgame),
 * handles remaining client machines, disconnects, clears the server struct,
 * and resets the in-use flag. */
void network_game_client_dispose(void *server)
{
  char *s;
  int16_t state;
  void *msg;
  const char *log_msg;

  s = (char *)server;
  if (!server) {
    display_assert("server",
                   "c:\\halo\\SOURCE\\networking\\network_server_manager.c",
                   0x120, 1);
    system_exit(-1);
  }
  state = *(int16_t *)(s + 4);
  if (state == 0) {
    msg = encode_network_game_message(9, &server, 4);
    if (!msg) {
      log_msg = "failed to create a "
                "_message_type_server_graceful_game_exit_pregame message";
    } else {
      goto broadcast;
    }
  } else if (state == 2) {
    msg = encode_network_game_message(0x1f, &server, 4);
    if (msg) {
      goto broadcast;
    }
    log_msg = "failed to create a "
              "_message_type_server_graceful_game_exit_postgame message";
  } else {
    goto skip_message;
  }
  goto do_log;

broadcast:
  if (FUN_0012f430(server, msg)) {
    log_msg = "notified all clients that we are going down";
  } else {
    log_msg = "failed to notify all clients that we are going down";
  }
do_log:
  network_game_log(log_msg);

skip_message:
  if (!FUN_0012e580((int)server)) {
    error(2, "network_game_server_handle_client_machines() failed inside "
             "network_game_server_dispose()");
  }
  if (*(int *)s != 0) {
    network_connection_delete(*(int *)s);
  }
  XSleep(1000, 0);
  FUN_00082b30();
  csmemset(server, 0, 0x4bc);
  if (!*(char *)0x46eed4) {
    display_assert("network_game_server_memory_do_not_use_directly_in_use",
                   "c:\\halo\\SOURCE\\networking\\network_server_manager.c",
                   0x171, 1);
    system_exit(-1);
  }
  *(char *)0x46eed4 = 0;
  network_game_log("network server disposed");
}

/* network_game_server_start (0x12eb20) — XBE naked draft (batch 118). */
#if defined(__clang__)
static bool (*const b12eb20_c82300)(void) = transport_network_available;
static bool (*const b12eb20_c12a170)(void) = network_game_is_splitscreen_local;
static void (*const b12eb20_ce44d0)(int16_t) = display_error_when_main_menu_loaded;
static void (*const b12eb20_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;
static bool (*const b12eb20_c12c160)(void *server) = network_game_server_game_is_valid;
static bool (*const b12eb20_c129cf0)(int connection, int flag, int *output) = FUN_00129cf0;
static bool (*const b12eb20_c12d880)(int server, int new_connection) = FUN_0012d880;
static void (*const b12eb20_c1283c0)(int connection, void *buf, int flag) = network_connection_get_address;
static const char * (*const b12eb20_c81b90)(void *addr) = transport_address_to_string;
static void (*const b12eb20_c12b650)(const char *fmt, ...) = network_game_log;
static bool (*const b12eb20_c129130)(int conn1, int conn2) = FUN_00129130;
static bool (*const b12eb20_c12d9f0)(int server) = FUN_0012d9f0;
static bool (*const b12eb20_c12e580)(int server) = FUN_0012e580;
static bool (*const b12eb20_c12db60)(int server) = FUN_0012db60;
static bool (*const b12eb20_c12e750)(int server) = FUN_0012e750;

__attribute__((naked, noinline))
bool network_game_server_start(void *server __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x1c, %%esp\n\t"
      "pushl %%ebx\n\t"
      "movb $1, %%bl\n\t"
      "call *%[c82300]\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lnetwork_game_server_start_1\n\t"
      "call *%[c12a170]\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lnetwork_game_server_start_1\n\t"
      "pushl $6\n\t"
      "call *%[ce44d0]\n\t"
      "pushl $0x2893dc\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $0xc, %%esp\n\t"
      "xorb %%bl, %%bl\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lnetwork_game_server_start_1:\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "pushl %%esi\n\t"
      "call *%[c12c160]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lnetwork_game_server_start_9\n\t"
      "movl (%%esi), %%ecx\n\t"
      "leal -0x4(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0\n\t"
      "pushl %%ecx\n\t"
      "movl $0, -0x4(%%ebp)\n\t"
      "call *%[c129cf0]\n\t"
      "movb %%al, %%bl\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpb $1, %%bl\n\t"
      "jne .Lnetwork_game_server_start_8\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lnetwork_game_server_start_3\n\t"
      "pushl %%eax\n\t"
      "movl %%esi, %%eax\n\t"
      "call *%[c12d880]\n\t"
      "addl $4, %%esp\n\t"
      "cmpb %%bl, %%al\n\t"
      "jne .Lnetwork_game_server_start_2\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "pushl $0\n\t"
      "leal -0x1c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c1283c0]\n\t"
      "leal -0x1c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c81b90]\n\t"
      "pushl %%eax\n\t"
      "pushl $0x298830\n\t"
      "call *%[c12b650]\n\t"
      "addl $0x18, %%esp\n\t"
      "jmp .Lnetwork_game_server_start_3\n\t"
      ".Lnetwork_game_server_start_2:\n\t"
      "pushl $0x298800\n\t"
      "call *%[c12b650]\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "movl (%%esi), %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c129130]\n\t"
      "addl $0xc, %%esp\n\t"
      ".Lnetwork_game_server_start_3:\n\t"
      "call *%[c12d9f0]\n\t"
      "movb %%al, %%bl\n\t"
      "testb %%bl, %%bl\n\t"
      "je .Lnetwork_game_server_start_7\n\t"
      "movl %%esi, %%ebx\n\t"
      "call *%[c12e580]\n\t"
      "movb %%al, %%bl\n\t"
      "testb %%bl, %%bl\n\t"
      "je .Lnetwork_game_server_start_6\n\t"
      "movzwl 0x4(%%esi), %%eax\n\t"
      "subl $0, %%eax\n\t"
      "je .Lnetwork_game_server_start_5\n\t"
      "decl %%eax\n\t"
      "je .Lnetwork_game_server_start_10\n\t"
      "decl %%eax\n\t"
      "je .Lnetwork_game_server_start_4\n\t"
      "pushl $0x2987e8\n\t"
      "call *%[c12b650]\n\t"
      "addl $4, %%esp\n\t"
      "xorb %%bl, %%bl\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lnetwork_game_server_start_4:\n\t"
      "call *%[c12db60]\n\t"
      "popl %%esi\n\t"
      "movb %%al, %%bl\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lnetwork_game_server_start_5:\n\t"
      "call *%[c12e750]\n\t"
      "popl %%esi\n\t"
      "movb %%al, %%bl\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lnetwork_game_server_start_6:\n\t"
      "pushl $0x2987b4\n\t"
      "call *%[c12b650]\n\t"
      "addl $4, %%esp\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lnetwork_game_server_start_7:\n\t"
      "pushl $0x298780\n\t"
      "call *%[c12b650]\n\t"
      "addl $4, %%esp\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lnetwork_game_server_start_8:\n\t"
      "pushl $0x29875c\n\t"
      "call *%[c12b650]\n\t"
      "addl $4, %%esp\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lnetwork_game_server_start_9:\n\t"
      "pushl $0x29873c\n\t"
      "call *%[c12b650]\n\t"
      "addl $4, %%esp\n\t"
      ".Lnetwork_game_server_start_10:\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c82300] "m"(b12eb20_c82300), [c12a170] "m"(b12eb20_c12a170), [ce44d0] "m"(b12eb20_ce44d0), [c8f390] "m"(b12eb20_c8f390), [c12c160] "m"(b12eb20_c12c160), [c129cf0] "m"(b12eb20_c129cf0), [c12d880] "m"(b12eb20_c12d880), [c1283c0] "m"(b12eb20_c1283c0), [c81b90] "m"(b12eb20_c81b90), [c12b650] "m"(b12eb20_c12b650), [c129130] "m"(b12eb20_c129130), [c12d9f0] "m"(b12eb20_c12d9f0), [c12e580] "m"(b12eb20_c12e580), [c12db60] "m"(b12eb20_c12db60), [c12e750] "m"(b12eb20_c12e750)
      : "memory");
}
#else
#error "network_game_server_start: clang naked draft required"
#endif


/* network_server_manager_pregame_start (0x12eca0) — XBE naked draft (batch 113). */
#if defined(__clang__)
static void (*const b12eca0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b12eca0_exitfn)(int) = system_exit;
static void *(*const b12eca0_memset)(void *, int, unsigned int) = csmemset;
static void * (*const b12eca0_c12b700)(int type, void *data, int16_t message_struct_size) = encode_network_game_message;
static bool (*const b12eca0_c12f430)(void *server, void *message) = FUN_0012f430;
static void (*const b12eca0_c12b650)(const char *fmt, ...) = network_game_log;
static bool (*const b12eca0_c12ac80)(void *client) = network_player_is_valid;
static void (*const b12eca0_c12abc0)(void *game, bool flag) = network_game_reset_for_next_round;
static bool (*const b12eca0_c12dc20)(int server) = FUN_0012dc20;
static void * (*const b12eca0_c8e0b0)(void *destination, void *source, size_t size) = csmemcpy;
static bool (*const b12eca0_c12e580)(int server) = FUN_0012e580;

__attribute__((naked, noinline))
bool network_server_manager_pregame_start(void *server __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x43c, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "pushl %%edi\n\t"
      "movb %%bl, -0x1(%%ebp)\n\t"
      "movl %%ebx, -0x8(%%ebp)\n\t"
      "jne .Lnetwork_server_manager_pregame_start_1\n\t"
      "pushl $1\n\t"
      "pushl $0x324\n\t"
      "pushl $0x296bf0\n\t"
      "pushl $0x296c34\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lnetwork_server_manager_pregame_start_1:\n\t"
      "pushl $0x10\n\t"
      "leal 0x488(%%esi), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "call *%[memset]\n\t"
      "movl 0x434(%%esi), %%ecx\n\t"
      "addl $0xc, %%esp\n\t"
      "incl %%ecx\n\t"
      "cmpw $2, 0x4(%%esi)\n\t"
      "movl %%ebx, 0x47c(%%esi)\n\t"
      "movl %%ebx, 0x484(%%esi)\n\t"
      "movb %%bl, 0x4b9(%%esi)\n\t"
      "movb %%bl, 0x4b8(%%esi)\n\t"
      "movl %%ecx, 0x434(%%esi)\n\t"
      "jne .Lnetwork_server_manager_pregame_start_11\n\t"
      "pushl $4\n\t"
      "leal -0x8(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x1e\n\t"
      "call *%[c12b700]\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl %%ebx, %%eax\n\t"
      "je .Lnetwork_server_manager_pregame_start_10\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[c12f430]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lnetwork_server_manager_pregame_start_10\n\t"
      "pushl $0x298924\n\t"
      "call *%[c12b650]\n\t"
      "movb 0xc8(%%esi), %%al\n\t"
      "addl $4, %%esp\n\t"
      "cmpb %%bl, %%al\n\t"
      "je .Lnetwork_server_manager_pregame_start_5\n\t"
      "leal 0x24c(%%esi), %%edi\n\t"
      "movl $0x10, 0x8(%%ebp)\n\t"
      "jmp .Lnetwork_server_manager_pregame_start_2\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".Lnetwork_server_manager_pregame_start_2:\n\t"
      "leal -0x1e(%%edi), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c12ac80]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lnetwork_server_manager_pregame_start_4\n\t"
      "movsbl (%%edi), %%eax\n\t"
      "subl %%ebx, %%eax\n\t"
      "je .Lnetwork_server_manager_pregame_start_3\n\t"
      "decl %%eax\n\t"
      "jne .Lnetwork_server_manager_pregame_start_4\n\t"
      "movb %%bl, (%%edi)\n\t"
      "jmp .Lnetwork_server_manager_pregame_start_4\n\t"
      ".Lnetwork_server_manager_pregame_start_3:\n\t"
      "movb $1, (%%edi)\n\t"
      ".Lnetwork_server_manager_pregame_start_4:\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "addl $0x20, %%edi\n\t"
      "decl %%eax\n\t"
      "movl %%eax, 0x8(%%ebp)\n\t"
      "jne .Lnetwork_server_manager_pregame_start_2\n\t"
      ".Lnetwork_server_manager_pregame_start_5:\n\t"
      "leal 0x44a(%%esi), %%eax\n\t"
      "movl $4, %%ecx\n\t"
      "jmp .Lnetwork_server_manager_pregame_start_6\n\t"
      "leal (%%ebx), %%ebx\n\t"
      ".Lnetwork_server_manager_pregame_start_6:\n\t"
      "andb $0xfb, (%%eax)\n\t"
      "movl %%ebx, -0xa(%%eax)\n\t"
      "movl %%ebx, -0x6(%%eax)\n\t"
      "addl $0x10, %%eax\n\t"
      "decl %%ecx\n\t"
      "jne .Lnetwork_server_manager_pregame_start_6\n\t"
      "leal 0x8(%%esi), %%edi\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "call *%[c12abc0]\n\t"
      "addl $8, %%esp\n\t"
      "movl %%esi, %%ebx\n\t"
      "call *%[c12dc20]\n\t"
      "testb %%al, %%al\n\t"
      "je .Lnetwork_server_manager_pregame_start_7\n\t"
      "pushl $0x434\n\t"
      "leal -0x43c(%%ebp), %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[c8e0b0]\n\t"
      "pushl $0x434\n\t"
      "leal -0x43c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $6\n\t"
      "call *%[c12b700]\n\t"
      "addl $0x18, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lnetwork_server_manager_pregame_start_8\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[c12f430]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lnetwork_server_manager_pregame_start_8\n\t"
      "popl %%edi\n\t"
      "movw $0, 0x4(%%esi)\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lnetwork_server_manager_pregame_start_7:\n\t"
      "pushl $4\n\t"
      "leal 0x8(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $9\n\t"
      "movl $0, 0x8(%%ebp)\n\t"
      "call *%[c12b700]\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lnetwork_server_manager_pregame_start_9\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[c12f430]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lnetwork_server_manager_pregame_start_9\n\t"
      "movl %%esi, %%ebx\n\t"
      "call *%[c12e580]\n\t"
      "testb %%al, %%al\n\t"
      "je .Lnetwork_server_manager_pregame_start_9\n\t"
      "pushl $0x2988f8\n\t"
      "call *%[c12b650]\n\t"
      "addl $4, %%esp\n\t"
      ".Lnetwork_server_manager_pregame_start_8:\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lnetwork_server_manager_pregame_start_9:\n\t"
      "pushl $0x2988a8\n\t"
      "call *%[c12b650]\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "addl $4, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lnetwork_server_manager_pregame_start_10:\n\t"
      "pushl $0x298868\n\t"
      "call *%[c12b650]\n\t"
      "addl $4, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lnetwork_server_manager_pregame_start_11:\n\t"
      "movl %%esi, %%ebx\n\t"
      "call *%[c12dc20]\n\t"
      "movb %%al, %%bl\n\t"
      "movb 0xc8(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lnetwork_server_manager_pregame_start_15\n\t"
      "addl $0x24c, %%esi\n\t"
      "movl $0x10, %%edi\n\t"
      ".Lnetwork_server_manager_pregame_start_12:\n\t"
      "leal -0x1e(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c12ac80]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lnetwork_server_manager_pregame_start_14\n\t"
      "movsbl (%%esi), %%eax\n\t"
      "subl $0, %%eax\n\t"
      "je .Lnetwork_server_manager_pregame_start_13\n\t"
      "decl %%eax\n\t"
      "jne .Lnetwork_server_manager_pregame_start_14\n\t"
      "movb $0, (%%esi)\n\t"
      "jmp .Lnetwork_server_manager_pregame_start_14\n\t"
      ".Lnetwork_server_manager_pregame_start_13:\n\t"
      "movb $1, (%%esi)\n\t"
      ".Lnetwork_server_manager_pregame_start_14:\n\t"
      "addl $0x20, %%esi\n\t"
      "decl %%edi\n\t"
      "jne .Lnetwork_server_manager_pregame_start_12\n\t"
      ".Lnetwork_server_manager_pregame_start_15:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b12eca0_assert), [exitfn] "m"(b12eca0_exitfn), [memset] "m"(b12eca0_memset), [c12b700] "m"(b12eca0_c12b700), [c12f430] "m"(b12eca0_c12f430), [c12b650] "m"(b12eca0_c12b650), [c12ac80] "m"(b12eca0_c12ac80), [c12abc0] "m"(b12eca0_c12abc0), [c12dc20] "m"(b12eca0_c12dc20), [c8e0b0] "m"(b12eca0_c8e0b0), [c12e580] "m"(b12eca0_c12e580)
      : "memory");
}
#else
#error "network_server_manager_pregame_start: clang naked draft required"
#endif


/* Initialize the global network server (0x12eef0).
 * Creates a connection, sets up game data, initializes machine slots. */
void *FUN_0012eef0(void)
{
  int *server;
  int i;
  int *slot;

  if (*(char *)0x46eed4) {
    display_assert("!network_game_server_memory_do_not_use_directly_in_use",
                   "c:\\halo\\SOURCE\\networking\\network_server_manager.c",
                   0xe0, 1);
    system_exit(-1);
  }
  *(char *)0x46eed4 = 1;
  server = (int *)0x5a90e0;
  csmemset(server, 0, 0x4bc);
  server[0] = network_connection_new(1, 0x141e);
  if (!server[0]) {
    error(2, "failed to create the server connection");
    network_game_client_dispose((void *)server);
    return (void *)0;
  }
  FUN_00082a90();
  *(short *)((char *)server + 4) = 0;
  *(short *)((char *)server + 6) = 2;
  csmemset((char *)server + 8, 0, 0x434);
  network_connection_set_connection_rejection_procedure(server[0],
                                                        (void *)FUN_0012db30);
  network_game_invalidate((char *)server + 8);
  *(short *)((char *)server + 0x118) = (short)main_get_difficulty();
  *(int *)0x5a9514 = -1;
  i = 0;
  slot = (int *)0x5a9520;
  do {
    slot[-1] = 0;
    slot[0] = 0;
    slot[1] = 0;
    *(unsigned short *)(slot + 2) = 0xffff;
    *(unsigned short *)((char *)(slot + 2) + 2) = 0;
    network_game_invalidate_machine((void *)((char *)server + 8), i);
    slot += 4;
    i++;
  } while ((int)slot < 0x5a9560);
  *(char *)0x5a9599 = 0;
  *(int *)0x5a9564 = 0;
  if (!network_server_manager_pregame_start((void *)server)) {
    error(2, "failed to initialize server pregame settings");
    network_game_client_dispose((void *)server);
    return (void *)0;
  }
  return (void *)server;
}

/* FUN_0012f040 (0x12f040) — readable C lift. */
bool FUN_0012f040(int server, int machine, void *message_data, int message_size)
{
  int size_left;
  short field_size;
  short field_count;
  int value;
  bool ok;

  (void)machine;
  if (network_game_server_get_state(server, (short *)0) != 0) {
    network_game_log((const char *)0x2989d0);
    return 1;
  }
  size_left = message_size - 2;
  field_size = 0x10;
  field_count = 1;
  ok = FUN_0012bce0(
      (int)&value,
      (int)((char *)message_data + 2),
      (short *)&size_left,
      &field_size,
      &field_count,
      3);
  if (ok) {
    network_game_server_update_countdown((void *)server, (short)value);
    return 1;
  }
  network_game_log((const char *)0x298a30);
  return 1;
}

/* FUN_0012f0d0 (0x12f0d0) — readable C lift. */
bool FUN_0012f0d0(int server, int machine, void *message_data, int message_size)
{
  int size_left;
  short field_size;
  short field_count;
  char value[0x100];
  bool ok;

  if (network_game_server_get_state(server, (short *)0) != 0) {
    network_game_log((const char *)0x298a78);
    return 1;
  }
  size_left = message_size - 2;
  field_size = 0x13;
  field_count = 1;
  ok = FUN_0012bce0((int)value, (int)((char *)message_data + 2), (short *)&size_left, &field_size, &field_count, 3);
  if (ok) {
    FUN_0012cbe0((void *)server, machine, value);
    return 1;
  }
  network_game_log((const char *)0x298ae0);
  return 1;
}

/* FUN_0012f170 (0x12f170) — readable C lift. */
bool FUN_0012f170(int server, int machine, void *message_data, int message_size)
{
  int size_left;
  short field_size;
  short field_count;
  int value;
  bool ok;

  if (network_game_server_get_state(server, (short *)0) != 0) {
    network_game_log((const char *)0x298b30);
    return 0;
  }
  size_left = message_size - 2;
  field_size = 0x18;
  field_count = 1;
  ok = FUN_0012bce0(
      (int)&value,
      (int)((char *)message_data + 2),
      (short *)&size_left,
      &field_size,
      &field_count,
      5);
  if (ok) {
    network_game_server_client_machine_game_loading_completed((void *)server, (void *)machine);
    return 1;
  }
  network_game_log((const char *)0x298b88);
  return 0;
}

/* FUN_0012f200 (0x12f200) — readable C lift. */
bool FUN_0012f200(int server, int machine, void *message_data, int message_size)
{
  int size_left;
  short field_size;
  short field_count;
  char value[0x20];
  bool ok;

  (void)machine;
  if (network_game_server_get_state(server, (short *)0) != 1) {
    network_game_log((const char *)0x298bc0);
    return 1;
  }
  size_left = message_size - 2;
  field_size = 0x1a;
  field_count = 1;
  ok = FUN_0012bce0(
      (int)value,
      (int)((char *)message_data + 2),
      (short *)&size_left,
      &field_size,
      &field_count,
      5);
  if (ok) {
    network_game_server_queue_player_for_addition(server, (int)(void *)value);
    return 1;
  }
  network_game_log((const char *)0x298c20);
  return 1;
}

/* FUN_0012f290 (0x12f290) — readable C lift. */
bool FUN_0012f290(int server, int machine, void *message_data, int message_size)
{
  int size_left;
  short field_size;
  short field_count;
  char value[0x20];
  bool ok;

  if (network_game_server_get_state(server, (short *)0) != 2) {
    network_game_log((const char *)0x298c70);
    return 1;
  }
  size_left = message_size - 2;
  field_size = 0x20;
  field_count = 1;
  ok = FUN_0012bce0((int)value, (int)((char *)message_data + 2), (short *)&size_left, &field_size, &field_count, 7);
  if (ok) {
    if (!FUN_0012c920((void *)server, machine, value))
      network_game_log((const char *)0x298d28);
    return 1;
  }
  network_game_log((const char *)0x298cd8);
  return 1;
}

/* FUN_0012f330 (0x12f330) — readable C lift. */
bool FUN_0012f330(int server, int machine, void *message_data, int message_size)
{
  int size_left;
  short field_size;
  short field_count;
  int value;
  bool ok;
  char result;

  result = 1;
  if (network_game_server_get_state(server, (short *)0) != 2) {
    network_game_log((const char *)0x298d60);
    return 1;
  }
  size_left = message_size - 2;
  field_size = 0x21;
  field_count = 1;
  ok = FUN_0012bce0(
      (int)&value,
      (int)((char *)message_data + 2),
      (short *)&size_left,
      &field_size,
      &field_count,
      7);
  if (ok) {
    result = (char)network_game_server_switch_machine_from_postgame_to_pregame(server, machine);
    if (!result)
      network_game_log((const char *)0x298dc0);
    return result != 0;
  }
  network_game_log((const char *)0x298cd8);
  return 1;
}



/* Fastcall wrapper: write message via network_connection_write (0x12f3d0).
 * dest_address, size, reliable, stack: connection,
 * message. */
bool FUN_0012f3d0(int dest_address, unsigned short size, int reliable,
                  void *connection, void *message)
{
  return network_connection_write(connection, message, size, dest_address,
                                  reliable);
}

/* Write a message to a machine's network connection (0x12f3f0).
 * Resolves machine→connection via get_machine_connection, then sends reliably.
 */
int FUN_0012f3f0(int server, int machine, void *message)
{
  int connection;
  unsigned short msg_size;
  int result;

  result = 0;
  connection = network_game_server_get_machine_connection(server, machine);
  if (connection) {
    msg_size = *(unsigned short *)message;
    return (int)network_connection_write((void *)connection, message,
                                         msg_size >> 4, 0, 1);
  }
  return result;
}

/* FUN_0012f430 (0x12f430) — XBE naked draft (batch 262). */
#if defined(__clang__)
static void (*const b12f430_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b12f430_exitfn)(int) = system_exit;
static int (*const b12f430_c12d450)(int server, int machine_index) = network_game_server_get_client_machine_at_index;
static bool (*const b12f430_c12c500)(int server, int machine) = network_game_server_client_machine_is_joined_to_game;
static int (*const b12f430_c12d3b0)(void *machine) = network_game_server_adjust_machine_settings;
static bool (*const b12f430_c128660)(int connection) = network_connection_active;
static void * (*const b12f430_c8e0b0)(void *destination, void *source, size_t size) = csmemcpy;
static bool (*const b12f430_c128e00)(void *connection, void *message, unsigned short size, int dest_address, bool reliable) = network_connection_write;
static void (*const b12f430_c12b650)(const char *fmt, ...) = network_game_log;

__attribute__((naked, noinline))
bool FUN_0012f430(void *server __attribute__((unused)), void *message __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x604, %%esp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "je .LFUN_0012f430_1\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_0012f430_2\n\t"
      ".LFUN_0012f430_1:\n\t"
      "pushl $1\n\t"
      "pushl $0x187\n\t"
      "pushl $0x298ea0\n\t"
      "pushl $0x298e8c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0012f430_2:\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movw (%%eax), %%di\n\t"
      "shrw $4, %%di\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "leal (%%ebx), %%ebx\n\t"
      ".LFUN_0012f430_3:\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c12d450]\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "movl %%eax, %%esi\n\t"
      "pushl %%esi\n\t"
      "pushl %%edx\n\t"
      "call *%[c12c500]\n\t"
      "addl $0x10, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0012f430_5\n\t"
      "pushl %%esi\n\t"
      "call *%[c12d3b0]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $4, %%esp\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_0012f430_5\n\t"
      "pushl %%esi\n\t"
      "call *%[c128660]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0012f430_5\n\t"
      "cmpw $0x600, %%di\n\t"
      "jbe .LFUN_0012f430_4\n\t"
      "pushl $1\n\t"
      "pushl $0x19a\n\t"
      "pushl $0x298ea0\n\t"
      "pushl $0x298e64\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0012f430_4:\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "movzwl %%di, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "leal -0x604(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c8e0b0]\n\t"
      "pushl $1\n\t"
      "pushl $0\n\t"
      "pushl %%edi\n\t"
      "leal -0x604(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[c128e00]\n\t"
      "addl $0x20, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_0012f430_5\n\t"
      "pushl $0x298e08\n\t"
      "call *%[c12b650]\n\t"
      "addl $4, %%esp\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      ".LFUN_0012f430_5:\n\t"
      "incl %%ebx\n\t"
      "cmpl $4, %%ebx\n\t"
      "jl .LFUN_0012f430_3\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b12f430_assert), [exitfn] "m"(b12f430_exitfn), [c12d450] "m"(b12f430_c12d450), [c12c500] "m"(b12f430_c12c500), [c12d3b0] "m"(b12f430_c12d3b0), [c128660] "m"(b12f430_c128660), [c8e0b0] "m"(b12f430_c8e0b0), [c128e00] "m"(b12f430_c128e00), [c12b650] "m"(b12f430_c12b650)
      : "memory");
}
#else
#error "FUN_0012f430: clang naked draft required"
#endif

typedef struct {
  unsigned int w[8];
} player_msg_t;

/* Copy player struct (0x20 bytes) and broadcast a player-joined message
 * (0x12f540). */
bool FUN_0012f540(int server, void *player)
{
  player_msg_t local_buf;
  int msg;
  bool sent;

  if (!server || !player) {
    display_assert(
      "server && player",
      "c:\\halo\\SOURCE\\networking\\network_server_message_handler.c", 0x1b0,
      1);
    system_exit(-1);
  }
  local_buf = *(player_msg_t *)player;
  msg = (int)encode_network_game_message(0x15, &local_buf, 0x20);
  if (!msg) {
    network_game_log(
      "failed to create a message_server_add_player_ingame message");
    return false;
  }
  sent = FUN_0012f430((void *)server, (void *)msg);
  if (!sent)
    network_game_log(
      "network_game_server_send_message_to_all_machines() failed in "
      "network_game_server_send_player_joined_info_ingame()");
  return sent;
}

/* FUN_0012f5d0 (0x12f5d0) — XBE naked draft (batch 139). */
#if defined(__clang__)
static void (*const b12f5d0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b12f5d0_exitfn)(int) = system_exit;
static int (*const b12f5d0_c12d570)(void *server) = network_game_server_get_game;
static void * (*const b12f5d0_c8e0b0)(void *destination, void *source, size_t size) = csmemcpy;
static void * (*const b12f5d0_c12b700)(int type, void *data, int16_t message_struct_size) = encode_network_game_message;
static bool (*const b12f5d0_c12f430)(void *server, void *message) = FUN_0012f430;
static void (*const b12f5d0_c12b650)(const char *fmt, ...) = network_game_log;

__attribute__((naked, noinline))
bool FUN_0012f5d0(void *server __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x434, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "xorb %%bl, %%bl\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LFUN_0012f5d0_1\n\t"
      "pushl $1\n\t"
      "pushl $0x1c8\n\t"
      "pushl $0x298ea0\n\t"
      "pushl $0x296c34\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0012f5d0_1:\n\t"
      "pushl %%esi\n\t"
      "call *%[c12d570]\n\t"
      "addl $4, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_0012f5d0_3\n\t"
      "pushl $0x434\n\t"
      "pushl %%eax\n\t"
      "leal -0x434(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c8e0b0]\n\t"
      "pushl $0x434\n\t"
      "leal -0x434(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $6\n\t"
      "call *%[c12b700]\n\t"
      "addl $0x18, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_0012f5d0_2\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[c12f430]\n\t"
      "movb %%al, %%bl\n\t"
      "addl $8, %%esp\n\t"
      "testb %%bl, %%bl\n\t"
      "jne .LFUN_0012f5d0_4\n\t"
      "pushl $0x299028\n\t"
      "call *%[c12b650]\n\t"
      "addl $4, %%esp\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0012f5d0_2:\n\t"
      "pushl $0x298fe8\n\t"
      "call *%[c12b650]\n\t"
      "addl $4, %%esp\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0012f5d0_3:\n\t"
      "pushl $0x298f90\n\t"
      "call *%[c12b650]\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_0012f5d0_4:\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b12f5d0_assert), [exitfn] "m"(b12f5d0_exitfn), [c12d570] "m"(b12f5d0_c12d570), [c8e0b0] "m"(b12f5d0_c8e0b0), [c12b700] "m"(b12f5d0_c12b700), [c12f430] "m"(b12f5d0_c12f430), [c12b650] "m"(b12f5d0_c12b650)
      : "memory");
}
#else
#error "FUN_0012f5d0: clang naked draft required"
#endif


/* network_game_server_reset_to_pregame (0x12f690) — XBE naked draft (batch 116). */
#if defined(__clang__)
static void (*const b12f690_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b12f690_exitfn)(int) = system_exit;
static int (*const b12f690_c12d570)(void *server) = network_game_server_get_game;
static void * (*const b12f690_c8e0b0)(void *destination, void *source, size_t size) = csmemcpy;
static void (*const b12f690_c81ec0)(void *dst, int bytes) = transport_get_nonce;
static int64_t (*const b12f690_c82090)(void) = transport_get_key_id;
static void * (*const b12f690_c820d0)(void *dst) = transport_get_key;
static void * (*const b12f690_c82060)(void *dst) = (void *)transport_get_xnaddr;
static wchar_t * (*const b12f690_c19dc90)(wchar_t *dest, wchar_t *src, size_t count) = ustrncpy;
static bool (*const b12f690_c12c100)(void *server) = network_game_server_game_is_open;
static void (*const b12f690_c12d250)(void *join_token) = network_game_generate_join_game_token;
static void * (*const b12f690_c12b700)(int type, void *data, int16_t message_struct_size) = encode_network_game_message;
static int (*const b12f690_c12d380)(void *server) = network_game_server_get_connection;
static bool (*const b12f690_c128e00)(void *connection, void *message, unsigned short size, int dest_address, bool reliable) = network_connection_write;
static void (*const b12f690_c12b650)(const char *fmt, ...) = network_game_log;

__attribute__((naked, noinline))
char network_game_server_reset_to_pregame(int server __attribute__((unused)), void *client_message __attribute__((unused)), void *source_address __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x13c, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%ecx, %%ebx\n\t"
      "je .Lnetwork_game_server_reset_to_pregame_1\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lnetwork_game_server_reset_to_pregame_1\n\t"
      "testl %%ebx, %%ebx\n\t"
      "jne .Lnetwork_game_server_reset_to_pregame_2\n\t"
      ".Lnetwork_game_server_reset_to_pregame_1:\n\t"
      "pushl $1\n\t"
      "pushl $0x21f\n\t"
      "pushl $0x298ea0\n\t"
      "pushl $0x299104\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lnetwork_game_server_reset_to_pregame_2:\n\t"
      "cmpw $1, 0x2(%%ebx)\n\t"
      "jne .Lnetwork_game_server_reset_to_pregame_8\n\t"
      "pushl %%esi\n\t"
      "call *%[c12d570]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $4, %%esp\n\t"
      "testl %%esi, %%esi\n\t"
      "je .Lnetwork_game_server_reset_to_pregame_8\n\t"
      "pushl %%edi\n\t"
      "xorl %%eax, %%eax\n\t"
      "movb $0, -0x13c(%%ebp)\n\t"
      "movl $0x44, %%ecx\n\t"
      "leal -0x13b(%%ebp), %%edi\n\t"
      "rep stosl\n\t"
      "stosw\n\t"
      "stosb\n\t"
      "movl $4, %%edi\n\t"
      "pushl $8\n\t"
      "addl %%edi, %%ebx\n\t"
      "leal -0x13c(%%ebp), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "movw %%di, -0x8(%%ebp)\n\t"
      "movl $0xffffffff, -0x18(%%ebp)\n\t"
      "movw $0x141f, -0x6(%%ebp)\n\t"
      "call *%[c8e0b0]\n\t"
      "leal -0x134(%%ebp), %%ecx\n\t"
      "pushl $8\n\t"
      "pushl %%ecx\n\t"
      "call *%[c81ec0]\n\t"
      "call *%[c82090]\n\t"
      "movl %%edx, -0x128(%%ebp)\n\t"
      "leal -0x28(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl %%eax, -0x12c(%%ebp)\n\t"
      "call *%[c820d0]\n\t"
      "movl (%%eax), %%ecx\n\t"
      "movl %%ecx, -0x124(%%ebp)\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl %%edx, -0x120(%%ebp)\n\t"
      "movl 0x8(%%eax), %%ecx\n\t"
      "movl %%ecx, -0x11c(%%ebp)\n\t"
      "movl 0xc(%%eax), %%edx\n\t"
      "leal -0x24(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl %%edx, -0x118(%%ebp)\n\t"
      "call *%[c82060]\n\t"
      "movl (%%eax), %%ecx\n\t"
      "movl %%ecx, -0x114(%%ebp)\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "pushl $0xf\n\t"
      "movl %%edx, -0x110(%%ebp)\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "leal -0x102(%%ebp), %%ecx\n\t"
      "pushl %%esi\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "pushl %%ecx\n\t"
      "movl %%eax, -0x10c(%%ebp)\n\t"
      "movw $0x141e, -0x108(%%ebp)\n\t"
      "movw $1, -0x106(%%ebp)\n\t"
      "movw %%bx, -0x104(%%ebp)\n\t"
      "call *%[c19dc90]\n\t"
      "movw 0xbc(%%esi), %%dx\n\t"
      "pushl $0x84\n\t"
      "leal 0x20(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0xc8(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movw %%dx, -0x44(%%ebp)\n\t"
      "call *%[c8e0b0]\n\t"
      "movw 0x224(%%esi), %%ax\n\t"
      "movw 0x112(%%esi), %%dx\n\t"
      "movsbw 0x10e(%%esi), %%cx\n\t"
      "movw %%ax, -0x40(%%ebp)\n\t"
      "movb 0xc0(%%esi), %%al\n\t"
      "movw %%dx, -0x42(%%ebp)\n\t"
      "movw 0xe4(%%esi), %%dx\n\t"
      "addl $0x34, %%esp\n\t"
      "cmpb $1, %%al\n\t"
      "movw %%cx, -0x3e(%%ebp)\n\t"
      "movw %%dx, -0x3c(%%ebp)\n\t"
      "movw %%bx, -0x3a(%%ebp)\n\t"
      "jne .Lnetwork_game_server_reset_to_pregame_3\n\t"
      "movw %%di, -0x3a(%%ebp)\n\t"
      ".Lnetwork_game_server_reset_to_pregame_3:\n\t"
      "cmpl $3, 0xbc(%%esi)\n\t"
      "movl $2, %%edi\n\t"
      "jne .Lnetwork_game_server_reset_to_pregame_4\n\t"
      "cmpl %%edi, 0x100(%%esi)\n\t"
      "jne .Lnetwork_game_server_reset_to_pregame_4\n\t"
      "orb $8, -0x3a(%%ebp)\n\t"
      ".Lnetwork_game_server_reset_to_pregame_4:\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "pushl %%ebx\n\t"
      "call *%[c12c100]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lnetwork_game_server_reset_to_pregame_5\n\t"
      "orw %%di, -0x3a(%%ebp)\n\t"
      ".Lnetwork_game_server_reset_to_pregame_5:\n\t"
      "leal -0x38(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c12d250]\n\t"
      "pushl $0x114\n\t"
      "leal -0x13c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edi\n\t"
      "call *%[c12b700]\n\t"
      "movl %%eax, %%edi\n\t"
      "addl $0x10, %%esp\n\t"
      "testl %%edi, %%edi\n\t"
      "je .Lnetwork_game_server_reset_to_pregame_7\n\t"
      "movw (%%edi), %%si\n\t"
      "pushl %%ebx\n\t"
      "shrw $4, %%si\n\t"
      "call *%[c12d380]\n\t"
      "pushl $0\n\t"
      "leal -0x18(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[c128e00]\n\t"
      "movb %%al, %%bl\n\t"
      "addl $0x18, %%esp\n\t"
      "testb %%bl, %%bl\n\t"
      "jne .Lnetwork_game_server_reset_to_pregame_6\n\t"
      "pushl $0x2990b0\n\t"
      "call *%[c12b650]\n\t"
      "addl $4, %%esp\n\t"
      ".Lnetwork_game_server_reset_to_pregame_6:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lnetwork_game_server_reset_to_pregame_7:\n\t"
      "pushl $0x299074\n\t"
      "call *%[c12b650]\n\t"
      "addl $4, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lnetwork_game_server_reset_to_pregame_8:\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b12f690_assert), [exitfn] "m"(b12f690_exitfn), [c12d570] "m"(b12f690_c12d570), [c8e0b0] "m"(b12f690_c8e0b0), [c81ec0] "m"(b12f690_c81ec0), [c82090] "m"(b12f690_c82090), [c820d0] "m"(b12f690_c820d0), [c82060] "m"(b12f690_c82060), [c19dc90] "m"(b12f690_c19dc90), [c12c100] "m"(b12f690_c12c100), [c12d250] "m"(b12f690_c12d250), [c12b700] "m"(b12f690_c12b700), [c12d380] "m"(b12f690_c12d380), [c128e00] "m"(b12f690_c128e00), [c12b650] "m"(b12f690_c12b650)
      : "memory");
}
#else
#error "network_game_server_reset_to_pregame: clang naked draft required"
#endif


/* FUN_0012f8d0 (0x12f8d0) — XBE naked draft (batch 136). */
#if defined(__clang__)
static void (*const b12f8d0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b12f8d0_exitfn)(int) = system_exit;
static void * (*const b12f8d0_c12b700)(int type, void *data, int16_t message_struct_size) = encode_network_game_message;
static int (*const b12f8d0_c12d380)(void *server) = network_game_server_get_connection;
static bool (*const b12f8d0_c128e00)(void *connection, void *message, unsigned short size, int dest_address, bool reliable) = network_connection_write;
static void (*const b12f8d0_c12b650)(const char *fmt, ...) = network_game_log;

__attribute__((naked, noinline))
char FUN_0012f8d0(int server __attribute__((unused)), void *decoded_msg __attribute__((unused)), void *client_message __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x1c, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl %%ecx, %%ebx\n\t"
      "testl %%ebx, %%ebx\n\t"
      "pushl %%edi\n\t"
      "movl %%eax, %%esi\n\t"
      "je .LFUN_0012f8d0_1\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_0012f8d0_1\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LFUN_0012f8d0_2\n\t"
      ".LFUN_0012f8d0_1:\n\t"
      "pushl $1\n\t"
      "pushl $0x26a\n\t"
      "pushl $0x298ea0\n\t"
      "pushl $0x299104\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0012f8d0_2:\n\t"
      "movl (%%esi), %%eax\n\t"
      "pushl $4\n\t"
      "leal -0x4(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $3\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "call *%[c12b700]\n\t"
      "movl %%eax, %%edi\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%edi, %%edi\n\t"
      "je .LFUN_0012f8d0_4\n\t"
      "movw 0x4(%%esi), %%cx\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "movl (%%edx), %%eax\n\t"
      "movw (%%edi), %%si\n\t"
      "pushl %%ebx\n\t"
      "movw $4, -0xc(%%ebp)\n\t"
      "movl %%eax, -0x1c(%%ebp)\n\t"
      "movw %%cx, -0xa(%%ebp)\n\t"
      "shrw $4, %%si\n\t"
      "call *%[c12d380]\n\t"
      "pushl $0\n\t"
      "leal -0x1c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[c128e00]\n\t"
      "movb %%al, %%bl\n\t"
      "addl $0x18, %%esp\n\t"
      "testb %%bl, %%bl\n\t"
      "jne .LFUN_0012f8d0_3\n\t"
      "pushl $0x299160\n\t"
      "call *%[c12b650]\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_0012f8d0_3:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0012f8d0_4:\n\t"
      "pushl $0x299130\n\t"
      "call *%[c12b650]\n\t"
      "addl $4, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b12f8d0_assert), [exitfn] "m"(b12f8d0_exitfn), [c12b700] "m"(b12f8d0_c12b700), [c12d380] "m"(b12f8d0_c12d380), [c128e00] "m"(b12f8d0_c128e00), [c12b650] "m"(b12f8d0_c12b650)
      : "memory");
}
#else
#error "FUN_0012f8d0: clang naked draft required"
#endif


/* FUN_0012f990 (0x12f990) — XBE naked draft (batch 107). */
#if defined(__clang__)
static short (*const b12f990_c12c020)(int param_1, short *param_2) = network_game_server_get_state;
static bool (*const b12f990_c12c500)(int server, int machine) = network_game_server_client_machine_is_joined_to_game;
static void (*const b12f990_c12b650)(const char *fmt, ...) = network_game_log;
static bool (*const b12f990_c12bce0)(int param_1, int param_2, short *param_3, short *param_4, short *param_5, int param_6) = FUN_0012bce0;
static int (*const b12f990_c12d3b0)(void *machine) = network_game_server_adjust_machine_settings;
static void (*const b12f990_c1283c0)(int connection, void *buf, int flag) = network_connection_get_address;
static bool (*const b12f990_c12c100)(void *server) = network_game_server_game_is_open;
static void (*const b12f990_c12d250)(void *join_token) = network_game_generate_join_game_token;
static int (*const b12f990_c8da40)(const void *a, const void *b, int size) = csmemcmp;
static char * (*const b12f990_c19f3a0)(const wchar_t *unicode, char *ascii, int size) = wide_to_ascii;
static void * (*const b12f990_c1d9e59)(const char *filename, const char *mode) = crt_fopen;
static char * (*const b12f990_c1daeec)(char *buffer, int max_count, void *stream) = crt_fgets;
static int (*const b12f990_c8df60)(const char *s1) = csstrlen;
static int (*const b12f990_c8ddd0)(char *s1, char *s2, unsigned int size) = csstrncmp;
static int (*const b12f990_c1d9dac)(void *stream) = crt_fclose;
static void * (*const b12f990_c12b700)(int type, void *data, int16_t message_struct_size) = encode_network_game_message;
static bool (*const b12f990_c128e00)(void *connection, void *message, unsigned short size, int dest_address, bool reliable) = network_connection_write;
static char (*const b12f990_c12c560)(int server, void *machine) = network_game_server_accept_client_machine_into_game;
static int (*const b12f990_c12d2f0)(int server, int machine, int *out) = network_game_server_get_client_machine;
static int (*const b12f990_c12d570)(void *server) = network_game_server_get_game;
static void (*const b12f990_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b12f990_exitfn)(int) = system_exit;
static int (*const b12f990_c12a830)(void) = network_game_get_number_of_games_played;
static bool (*const b12f990_c12f5d0)(void *server) = FUN_0012f5d0;
static const char * (*const b12f990_c81b90)(void *addr) = transport_address_to_string;

__attribute__((naked, noinline))
char FUN_0012f990(int server __attribute__((unused)), void *machine __attribute__((unused)), void *message __attribute__((unused)), int message_size __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xac, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "pushl $0\n\t"
      "pushl %%edi\n\t"
      "movb $1, %%bl\n\t"
      "call *%[c12c020]\n\t"
      "addl $8, %%esp\n\t"
      "testw %%ax, %%ax\n\t"
      "jne .LFUN_0012f990_18\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "subl $2, %%edx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl $0xc, -0xc(%%ebp)\n\t"
      "movl $1, -0x8(%%ebp)\n\t"
      "movl %%edx, 0x10(%%ebp)\n\t"
      "call *%[c12c500]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0012f990_1\n\t"
      "pushl $0x2994e0\n\t"
      "call *%[c12b650]\n\t"
      "addl $4, %%esp\n\t"
      "popl %%edi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0012f990_1:\n\t"
      "pushl $3\n\t"
      "leal -0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "leal -0xc(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal 0x10(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "addl $2, %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0xac(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c12bce0]\n\t"
      "addl $0x18, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0012f990_16\n\t"
      "pushl $0\n\t"
      "leal -0x2c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%esi\n\t"
      "call *%[c12d3b0]\n\t"
      "addl $4, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[c1283c0]\n\t"
      "pushl $0\n\t"
      "pushl %%edi\n\t"
      "call *%[c12c020]\n\t"
      "addl $0x14, %%esp\n\t"
      "testw %%ax, %%ax\n\t"
      "jne .LFUN_0012f990_14\n\t"
      "pushl %%edi\n\t"
      "call *%[c12c100]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0012f990_14\n\t"
      "leal -0x5c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c12d250]\n\t"
      "pushl $0x10\n\t"
      "leal -0x5c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x6c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c8da40]\n\t"
      "addl $0x10, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_0012f990_13\n\t"
      "pushl $0x40\n\t"
      "leal -0xac(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0xac(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c19f3a0]\n\t"
      "pushl $0x2658a4\n\t"
      "pushl $0x2994d0\n\t"
      "call *%[c1d9e59]\n\t"
      "movl %%eax, %%ebx\n\t"
      "addl $0x14, %%esp\n\t"
      "testl %%ebx, %%ebx\n\t"
      "je .LFUN_0012f990_6\n\t"
      "movb $0, -0x4c(%%ebp)\n\t"
      "xorl %%eax, %%eax\n\t"
      "movl $7, %%ecx\n\t"
      "leal -0x4b(%%ebp), %%edi\n\t"
      "rep stosl\n\t"
      "pushl %%ebx\n\t"
      "stosw\n\t"
      "leal -0x4c(%%ebp), %%edx\n\t"
      "pushl $0x20\n\t"
      "pushl %%edx\n\t"
      "stosb\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "call *%[c1daeec]\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_0012f990_4\n\t"
      ".LFUN_0012f990_2:\n\t"
      "leal -0xac(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c8df60]\n\t"
      "pushl %%eax\n\t"
      "leal -0x4c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0xac(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c8ddd0]\n\t"
      "addl $0x10, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_0012f990_3\n\t"
      "pushl %%ebx\n\t"
      "leal -0x4c(%%ebp), %%eax\n\t"
      "pushl $0x20\n\t"
      "pushl %%eax\n\t"
      "call *%[c1daeec]\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_0012f990_2\n\t"
      "jmp .LFUN_0012f990_4\n\t"
      ".LFUN_0012f990_3:\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      ".LFUN_0012f990_4:\n\t"
      "pushl %%ebx\n\t"
      "call *%[c1d9dac]\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_0012f990_5\n\t"
      "leal -0xac(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x299490\n\t"
      "movw $6, -0x2(%%ebp)\n\t"
      "call *%[c12b650]\n\t"
      "pushl $2\n\t"
      "leal -0x2(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $5\n\t"
      "call *%[c12b700]\n\t"
      "movl %%eax, %%ebx\n\t"
      "addl $0x14, %%esp\n\t"
      "testl %%ebx, %%ebx\n\t"
      "je .LFUN_0012f990_17\n\t"
      "movw (%%ebx), %%di\n\t"
      "pushl %%esi\n\t"
      "shrw $4, %%di\n\t"
      "call *%[c12d3b0]\n\t"
      "pushl $1\n\t"
      "pushl $0\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "call *%[c128e00]\n\t"
      "addl $0x18, %%esp\n\t"
      "xorb %%bl, %%bl\n\t"
      "popl %%edi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0012f990_5:\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      ".LFUN_0012f990_6:\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c12c560]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0012f990_11\n\t"
      "leal -0x4(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl $0xffffffff, -0x4(%%ebp)\n\t"
      "call *%[c12d2f0]\n\t"
      "pushl %%edi\n\t"
      "movl %%eax, %%ebx\n\t"
      "call *%[c12d570]\n\t"
      "addl $0x10, %%esp\n\t"
      "testl %%ebx, %%ebx\n\t"
      "je .LFUN_0012f990_7\n\t"
      "movb 0x40(%%ebx), %%bl\n\t"
      "testb %%bl, %%bl\n\t"
      "jl .LFUN_0012f990_7\n\t"
      "cmpb $4, %%bl\n\t"
      "jl .LFUN_0012f990_8\n\t"
      ".LFUN_0012f990_7:\n\t"
      "pushl $1\n\t"
      "pushl $0x2ce\n\t"
      "pushl $0x298ea0\n\t"
      "pushl $0x299464\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0012f990_8:\n\t"
      "movw -0x4(%%ebp), %%cx\n\t"
      "movw %%cx, -0x10(%%ebp)\n\t"
      "call *%[c12a830]\n\t"
      "pushl $8\n\t"
      "leal -0x14(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $4\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "call *%[c12b700]\n\t"
      "movl %%eax, %%ebx\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%ebx, %%ebx\n\t"
      "je .LFUN_0012f990_17\n\t"
      "movw (%%ebx), %%di\n\t"
      "pushl %%esi\n\t"
      "shrw $4, %%di\n\t"
      "call *%[c12d3b0]\n\t"
      "pushl $1\n\t"
      "pushl $0\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "call *%[c128e00]\n\t"
      "movb %%al, %%bl\n\t"
      "addl $0x18, %%esp\n\t"
      "testb %%bl, %%bl\n\t"
      "jne .LFUN_0012f990_9\n\t"
      "pushl $0x299400\n\t"
      "call *%[c12b650]\n\t"
      "addl $4, %%esp\n\t"
      "jmp .LFUN_0012f990_10\n\t"
      ".LFUN_0012f990_9:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x2993c0\n\t"
      "call *%[c12b650]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_0012f990_10:\n\t"
      "cmpb $1, %%bl\n\t"
      "jne .LFUN_0012f990_18\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c12f5d0]\n\t"
      "movb %%al, %%bl\n\t"
      "addl $4, %%esp\n\t"
      "testb %%bl, %%bl\n\t"
      "jne .LFUN_0012f990_18\n\t"
      "pushl $0x299348\n\t"
      "call *%[c12b650]\n\t"
      "addl $4, %%esp\n\t"
      "popl %%edi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0012f990_11:\n\t"
      "leal -0x2c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movw $5, -0x2(%%ebp)\n\t"
      "call *%[c81b90]\n\t"
      "pushl %%eax\n\t"
      "leal -0xac(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x299300\n\t"
      "call *%[c12b650]\n\t"
      "pushl $2\n\t"
      "leal -0x2(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $5\n\t"
      "call *%[c12b700]\n\t"
      "movl %%eax, %%ebx\n\t"
      "addl $0x1c, %%esp\n\t"
      "testl %%ebx, %%ebx\n\t"
      "je .LFUN_0012f990_17\n\t"
      ".LFUN_0012f990_12:\n\t"
      "movw (%%ebx), %%di\n\t"
      "pushl %%esi\n\t"
      "shrw $4, %%di\n\t"
      "call *%[c12d3b0]\n\t"
      "pushl $1\n\t"
      "pushl $0\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "call *%[c128e00]\n\t"
      "addl $0x18, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_0012f990_17\n\t"
      "pushl $0x2992b8\n\t"
      "call *%[c12b650]\n\t"
      "addl $4, %%esp\n\t"
      "xorb %%bl, %%bl\n\t"
      "popl %%edi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0012f990_13:\n\t"
      "leal -0x2c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movw $2, -0x2(%%ebp)\n\t"
      "call *%[c81b90]\n\t"
      "pushl %%eax\n\t"
      "leal -0xac(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x299270\n\t"
      "jmp .LFUN_0012f990_15\n\t"
      ".LFUN_0012f990_14:\n\t"
      "leal -0x2c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movw $5, -0x2(%%ebp)\n\t"
      "call *%[c81b90]\n\t"
      "pushl %%eax\n\t"
      "leal -0xac(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x299228\n\t"
      ".LFUN_0012f990_15:\n\t"
      "call *%[c12b650]\n\t"
      "pushl $2\n\t"
      "leal -0x2(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $5\n\t"
      "call *%[c12b700]\n\t"
      "movl %%eax, %%ebx\n\t"
      "addl $0x1c, %%esp\n\t"
      "testl %%ebx, %%ebx\n\t"
      "jne .LFUN_0012f990_12\n\t"
      "pushl $0x2991ec\n\t"
      "call *%[c12b650]\n\t"
      "addl $4, %%esp\n\t"
      "xorb %%bl, %%bl\n\t"
      "popl %%edi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0012f990_16:\n\t"
      "pushl $0x2991a8\n\t"
      "call *%[c12b650]\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_0012f990_17:\n\t"
      "xorb %%bl, %%bl\n\t"
      ".LFUN_0012f990_18:\n\t"
      "popl %%edi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c12c020] "m"(b12f990_c12c020), [c12c500] "m"(b12f990_c12c500), [c12b650] "m"(b12f990_c12b650), [c12bce0] "m"(b12f990_c12bce0), [c12d3b0] "m"(b12f990_c12d3b0), [c1283c0] "m"(b12f990_c1283c0), [c12c100] "m"(b12f990_c12c100), [c12d250] "m"(b12f990_c12d250), [c8da40] "m"(b12f990_c8da40), [c19f3a0] "m"(b12f990_c19f3a0), [c1d9e59] "m"(b12f990_c1d9e59), [c1daeec] "m"(b12f990_c1daeec), [c8df60] "m"(b12f990_c8df60), [c8ddd0] "m"(b12f990_c8ddd0), [c1d9dac] "m"(b12f990_c1d9dac), [c12b700] "m"(b12f990_c12b700), [c128e00] "m"(b12f990_c128e00), [c12c560] "m"(b12f990_c12c560), [c12d2f0] "m"(b12f990_c12d2f0), [c12d570] "m"(b12f990_c12d570), [assert] "m"(b12f990_assert), [exitfn] "m"(b12f990_exitfn), [c12a830] "m"(b12f990_c12a830), [c12f5d0] "m"(b12f990_c12f5d0), [c81b90] "m"(b12f990_c81b90)
      : "memory");
}
#else
#error "FUN_0012f990: clang naked draft required"
#endif

